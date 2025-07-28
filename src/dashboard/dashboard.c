#include "vcu/dashboard.h"

#include "modes/modes.h"

// glibc includes
#include <stdint.h>
#include <stdio.h>
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
#include <zephyr/sys/util.h>

// project includes
#include "vcu/ctrl/states.h"

LOG_MODULE_REGISTER(vcu_dashboard);

/* macro ---------------------------------------------------------------------*/
#define BRIGHTNESS_DEFAULT 100
#define MODE_DEFAULT DASHBOARD_NORMAL

/* type ----------------------------------------------------------------------*/
struct dashboard_ctx {
  const struct dashboard_mode_info* mode_infos;

  struct k_mutex lock;
  uint8_t brightness;
  struct led_rgb accel_rgb[LED_STRIP_LEN];
  struct led_rgb brake_rgb[LED_STRIP_LEN];
  enum dashboard_mode mode;
};

/* static function declaration -----------------------------------------------*/
static void auxdisplay_set_level(const struct device* auxdisplay, int level);
static void rgb_set_level(struct led_rgb* rgb, int len, int level);

/**
 * @brief Set rgb struct to error pattern, which is a five-zone pattern with the
 * second and fourth zones lit up.
 */
static void rgb_set_error(struct led_rgb* rgb, int len);
static void rgb_apply_selected(struct led_rgb* rgb, int len);
static void dashboard_reset();

static int init();

static void input_cb(struct input_event* evt, void* user_data);
static void states_cb(enum states_state state, bool is_entry, void* user_data);

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

static struct dashboard_ctx g_ctx = {
    .mode_infos =
        (const struct dashboard_mode_info[]){
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
        },
    .lock = Z_MUTEX_INITIALIZER(g_ctx.lock),
    .brightness = BRIGHTNESS_DEFAULT,
    .mode = MODE_DEFAULT,
};

SYS_INIT(init, APPLICATION, CONFIG_VCU_DASHBOARD_INIT_PRIORITY);

INPUT_CALLBACK_DEFINE(NULL, input_cb, NULL);

STATES_CALLBACK_DEFINE(STATE_RTD_SOUND, states_cb, NULL);

/* function definition -------------------------------------------------------*/
int dashboard_brightness_get() { return g_ctx.brightness; }

void dashboard_brightness_set(int brightness) {
  brightness = CLAMP(brightness, 0, 100);

  g_ctx.brightness = brightness;
  int ret = auxdisplay_brightness_set(speed_display, brightness);
  if (ret < 0) {
    LOG_ERR("auxdisplay_brightness_set failed: %s", strerror(-ret));
  }
}

void dashboard_led_set(int led, bool set) {
  if (set) {
    led_on(leds, led);
  } else {
    led_off(leds, led);
  }
}

void dashboard_clear(enum dashboard_component display) {
  static const char* clear_str = "  ";

  switch (display) {
    case DASHBOARD_SPEED:
      auxdisplay_write(speed_display, clear_str, strlen(clear_str));
      break;

    case DASHBOARD_BATTERY:
      auxdisplay_write(battery_display, clear_str, strlen(clear_str));
      break;

    case DASHBOARD_ACCEL:
    case DASHBOARD_BRAKE:
      dashboard_set_level(display, 0);
      break;

    default:
      __ASSERT(false, "Invalid dashboard display: %d", display);
      break;
  }
}

void dashboard_set_level(enum dashboard_component display, int level) {
  switch (display) {
    case DASHBOARD_SPEED:
      auxdisplay_set_level(speed_display, level);
      break;

    case DASHBOARD_BATTERY:
      auxdisplay_set_level(battery_display, level);
      break;

    case DASHBOARD_ACCEL: {
      rgb_set_level(g_ctx.accel_rgb, LED_STRIP_LEN, level);
      led_strip_update_rgb(accel_display, g_ctx.accel_rgb, LED_STRIP_LEN);
      break;
    }

    case DASHBOARD_BRAKE: {
      rgb_set_level(g_ctx.brake_rgb, LED_STRIP_LEN, level);
      led_strip_update_rgb(brake_display, g_ctx.brake_rgb, LED_STRIP_LEN);
      break;
    }

    default:
      __ASSERT(false, "Invalid dashboard display: %d", display);
      break;
  }
}

void dashboard_set_error(enum dashboard_component display) {
  static const char* err_str = "Er";

  switch (display) {
    case DASHBOARD_SPEED:
      auxdisplay_write(speed_display, err_str, strlen(err_str));
      break;

    case DASHBOARD_BATTERY:
      auxdisplay_write(battery_display, err_str, strlen(err_str));
      break;

    case DASHBOARD_ACCEL:
      rgb_set_error(g_ctx.accel_rgb, LED_STRIP_LEN);
      led_strip_update_rgb(accel_display, g_ctx.accel_rgb, LED_STRIP_LEN);
      break;

    case DASHBOARD_BRAKE:
      rgb_set_error(g_ctx.brake_rgb, LED_STRIP_LEN);
      led_strip_update_rgb(brake_display, g_ctx.brake_rgb, LED_STRIP_LEN);
      break;

    default:
      __ASSERT(false, "Invalid dashboard display: %d", display);
      break;
  }
}

void dashboard_apply_selected(enum dashboard_component display) {
  switch (display) {
    case DASHBOARD_SPEED:
    case DASHBOARD_BATTERY:
      dashboard_clear(display);
      break;

    case DASHBOARD_ACCEL:
      rgb_apply_selected(g_ctx.accel_rgb, LED_STRIP_LEN);
      led_strip_update_rgb(accel_display, g_ctx.accel_rgb, LED_STRIP_LEN);
      break;

    case DASHBOARD_BRAKE:
      rgb_apply_selected(g_ctx.brake_rgb, LED_STRIP_LEN);
      led_strip_update_rgb(brake_display, g_ctx.brake_rgb, LED_STRIP_LEN);
      break;

    default:
      __ASSERT(false, "Invalid dashboard display: %d", display);
      break;
  }
}

enum dashboard_mode dashboard_mode_get() { return g_ctx.mode; }

void dashboard_mode_set(enum dashboard_mode mode) {
  if (mode == g_ctx.mode) {
    return;
  }

  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.mode_infos[g_ctx.mode].stop();
  dashboard_reset();

  g_ctx.mode_infos[mode].start();
  g_ctx.mode = mode;

  k_mutex_unlock(&g_ctx.lock);

  LOG_INF("Set dashboard mode to: %s", dashboard_mode_info(mode)->name);
}

const struct dashboard_mode_info* dashboard_mode_info(
    enum dashboard_mode mode) {
  __ASSERT(mode < NUM_DASHBOARD_MODE, "Invalid mode: %d", mode);

  return &g_ctx.mode_infos[mode];
}

/* static function definition ------------------------------------------------*/
static void auxdisplay_set_level(const struct device* auxdisplay, int level) {
  // longer to prevent compiler warnings
  static char buf[20];

  if (level >= 100) {
    snprintf(buf, sizeof(buf), "00");
  } else {
    snprintf(buf, sizeof(buf), "%2d", MAX(level, -9));
  }

  int ret = auxdisplay_write(auxdisplay, buf, strlen(buf));
  if (ret < 0) {
    LOG_ERR("auxdisplay_write failed: %s", strerror(-ret));
  }
}

static void rgb_set_level(struct led_rgb* rgb, int len, int level) {
  level = DIV_ROUND_CLOSEST(level * len, 100);
  level = CLAMP(level, 0, len);

  for (int i = 0; i < level; i++) {
    rgb[i].r = 1;
  }

  for (int i = level; i < len; i++) {
    rgb[i].r = 0;
  }
}

static void rgb_set_error(struct led_rgb* rgb, int len) {
  int start = 0;
  for (int zone = 0; zone < 5; zone++) {
    int zone_size = len / 5 + ((zone < len % 5) ? 1 : 0);
    int end = start + zone_size;

    for (int i = start; i < end; ++i) {
      rgb[i].r = (zone == 1 || zone == 3) ? 1 : 0;
    }

    start = end;
  }
}

static void rgb_apply_selected(struct led_rgb* rgb, int len) {
  rgb[0].r = !rgb[0].r;
  rgb[len - 1].r = !rgb[len - 1].r;
}

static void dashboard_reset() {
  dashboard_brightness_set(g_ctx.brightness);

  for (int i = 0; i < NUM_LED; i++) {
    dashboard_led_set(i, false);
  }

  for (int i = 0; i < NUM_DASHBOARD_DISPLAY; i++) {
    dashboard_clear(i);
  }
}

static int init() {
  dashboard_reset();
  g_ctx.mode_infos[g_ctx.mode].start();

  return 0;
}

static void input_cb(struct input_event* evt, void* user_data) {
  (void)user_data;

  if (evt->type == INPUT_EV_KEY && evt->code == INPUT_BTN_MODE && evt->value &&
      !(states_get() & (STATE_RTD_SOUND | STATE_RUNNING))) {
    enum dashboard_mode next_mode =
        (dashboard_mode_get() + 1) % NUM_DASHBOARD_MODE;
    dashboard_mode_set(next_mode);
  }
}

static void states_cb(enum states_state state, bool is_entry, void* user_data) {
  (void)user_data;

  if (is_entry && dashboard_mode_get() != DASHBOARD_NORMAL) {
    dashboard_mode_set(DASHBOARD_NORMAL);
  }
}
