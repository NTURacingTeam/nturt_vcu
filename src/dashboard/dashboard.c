#include "vcu/dashboard.h"

// glibc includes
#include <stdint.h>
#include <string.h>

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/auxdisplay.h>
#include <zephyr/drivers/led.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/init.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>
#include <zephyr/sys/__assert.h>

LOG_MODULE_REGISTER(vcu_dashboard);

/* macro ---------------------------------------------------------------------*/
#define BRIGHTNESS_DEFAULT 100
#define MODE_DEFAULT DASHBOARD_NORMAL

/* type ----------------------------------------------------------------------*/
struct dashboard_ctx {
  struct k_mutex lock;
  uint8_t brightness;
  enum dashboard_mode mode;
};

/* static function declaration -----------------------------------------------*/
static void dashboard_clear();

static int init();

static void input_cb(struct input_event* evt, void* user_data);

/* static variable -----------------------------------------------------------*/
static const struct device* leds = DEVICE_DT_GET(DT_CHOSEN(nturt_leds));

static const struct device* speed_display =
    DEVICE_DT_GET(DT_NODELABEL(speed_display));
static const struct device* battery_display =
    DEVICE_DT_GET(DT_NODELABEL(battery_display));

static const struct device* accel_display =
    DEVICE_DT_GET(DT_NODELABEL(accel_display));
static const struct device* brake_display =
    DEVICE_DT_GET(DT_NODELABEL(brake_display));

static const struct dashboard_mode_info g_mode_infos[] = {
    [DASHBOARD_NORMAL] =
        {
            .start = dashboard_normal_start,
            .stop = dashboard_normal_stop,
            .name = "normal",
            .desc = "Normal dashboard operations",
        },
    [DASHBOARD_SETTING] =
        {
            .start = dashboard_setting_start,
            .stop = dashboard_setting_stop,
            .name = "setting",
            .desc = "Dashboard settings mode",
        },
    [DASHBOARD_TEST] =
        {
            .start = dashboard_test_start,
            .stop = dashboard_test_stop,
            .name = "test",
            .desc = "Test dashboard functions",
        },
};

static struct dashboard_ctx g_ctx = {
    .lock = Z_MUTEX_INITIALIZER(g_ctx.lock),
    .brightness = BRIGHTNESS_DEFAULT,
    .mode = MODE_DEFAULT,
};

SYS_INIT(init, APPLICATION, CONFIG_VCU_DASHBOARD_INIT_PRIORITY);

INPUT_CALLBACK_DEFINE(NULL, input_cb, NULL);

/* function definition -------------------------------------------------------*/
uint8_t dashboard_brightness_get() { return g_ctx.brightness; }

void dashboard_brightness_set(uint8_t brightness) {
  g_ctx.brightness = brightness;

  int ret = auxdisplay_brightness_set(speed_display, brightness);
  if (ret < 0) {
    LOG_ERR("auxdisplay_brightness_set failed: %s", strerror(-ret));
  }
}

enum dashboard_mode dashboard_mode_get() { return g_ctx.mode; }

void dashboard_mode_set(enum dashboard_mode mode) {
  if (mode == g_ctx.mode) {
    return;
  }

  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_mode_infos[g_ctx.mode].stop();
  dashboard_clear();
  g_mode_infos[mode].start();

  g_ctx.mode = mode;

  k_mutex_unlock(&g_ctx.lock);

  LOG_INF("Set dashboard mode to: %s", dashboard_mode_info(mode)->name);
}

const struct dashboard_mode_info* dashboard_mode_info(
    enum dashboard_mode mode) {
  __ASSERT(mode < NUM_DASHBOARD_MODE, "Invalid mode: %d", mode);

  return &g_mode_infos[mode];
}

/* static function definition ------------------------------------------------*/
static void dashboard_clear() {
  static const char* empty_str = "  ";
  struct led_rgb rgb[LED_STRIP_LEN] = {0};

  dashboard_brightness_set(g_ctx.brightness);

  for (int i = 0; i < NUM_LED; i++) {
    led_off(leds, i);
  }

  auxdisplay_write(speed_display, empty_str, strlen(empty_str));
  auxdisplay_write(battery_display, empty_str, strlen(empty_str));

  led_strip_update_rgb(accel_display, rgb, LED_STRIP_LEN);
  led_strip_update_rgb(brake_display, rgb, LED_STRIP_LEN);
}

static int init() {
  dashboard_clear();
  g_mode_infos[g_ctx.mode].start();

  return 0;
}

static void input_cb(struct input_event* evt, void* user_data) {
  (void)user_data;

  if (evt->type == INPUT_EV_KEY && evt->code == INPUT_BTN_MODE) {
    enum dashboard_mode next_mode =
        (dashboard_mode_get() + 1) % NUM_DASHBOARD_MODE;
    dashboard_mode_set(next_mode);
  }
}
