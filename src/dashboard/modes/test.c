#include "vcu/dashboard.h"

// glibc incldes
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/auxdisplay.h>
#include <zephyr/drivers/led.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

/* type ----------------------------------------------------------------------*/
struct dashboard_test_ctx {
  int pressed;

  k_tid_t tid;
  struct k_thread thread;
};

/* static function declaration -----------------------------------------------*/
static char *num_char(int i);
static void rgb_set_level(struct led_rgb *rgb, int len, int level);

static void input_cb(struct input_event *evt, void *user_data);
static void dashboard_test_thread(void *arg1, void *arg2, void *arg3);

/* static variable -----------------------------------------------------------*/
static const struct device *leds = DEVICE_DT_GET(DT_CHOSEN(nturt_leds));

static const struct device *speed_display =
    DEVICE_DT_GET(DT_NODELABEL(speed_display));
static const struct device *battery_display =
    DEVICE_DT_GET(DT_NODELABEL(battery_display));

static const struct device *accel_display =
    DEVICE_DT_GET(DT_NODELABEL(accel_display));
static const struct device *brake_display =
    DEVICE_DT_GET(DT_NODELABEL(brake_display));

static struct dashboard_test_ctx g_ctx = {
    .pressed = -1,
    .tid = NULL,
};

K_THREAD_STACK_DEFINE(dashboard_test_thread_stack, 512);

INPUT_CALLBACK_DEFINE(NULL, input_cb, &g_ctx);

/* function definition -------------------------------------------------------*/
void dashboard_test_start() {
  if (g_ctx.pressed != -1 && g_ctx.pressed < NUM_LED) {
    led_on(leds, g_ctx.pressed);
  }

  g_ctx.tid =
      k_thread_create(&g_ctx.thread, dashboard_test_thread_stack,
                      K_THREAD_STACK_SIZEOF(dashboard_test_thread_stack),
                      dashboard_test_thread, NULL, NULL, NULL, 5, 0, K_NO_WAIT);
  k_thread_name_set(g_ctx.tid, "dashboard_test");
}

void dashboard_test_stop() {
  k_thread_abort(g_ctx.tid);
  g_ctx.tid = NULL;
}

/* static function definition ------------------------------------------------*/
static char *num_char(int i) {
  static char buf[20];
  if (i < 10) {
    snprintf(buf, sizeof(buf), ".%d", i);
  } else if (i == 100) {
    snprintf(buf, sizeof(buf), "00.");
  } else {
    snprintf(buf, sizeof(buf), "%2d.", i);
  }

  return buf;
}

static void rgb_set_level(struct led_rgb *rgb, int len, int level) {
  level = DIV_ROUND_CLOSEST(level * len, 100);

  for (int i = 0; i < level; i++) {
    rgb[i].r = 1;
  }

  for (int i = level; i < len; i++) {
    rgb[i].r = 0;
  }
}

static void input_cb(struct input_event *evt, void *user_data) {
  struct dashboard_test_ctx *ctx = user_data;

  if (evt->type == INPUT_EV_KEY && evt->code >= INPUT_BTN_1 &&
      evt->code <= INPUT_BTN_7) {
    if (ctx->tid != NULL && ctx->pressed != -1 && ctx->pressed < NUM_LED) {
      led_off(leds, ctx->pressed);
    }

    ctx->pressed += (evt->value ? 1 : -1) * (evt->code - INPUT_BTN_0);

    if (ctx->tid != NULL && ctx->pressed != -1 && ctx->pressed < NUM_LED) {
      led_on(leds, ctx->pressed);
    }
  }
}

static void dashboard_test_thread(void *arg1, void *arg2, void *arg3) {
  (void)arg1;
  (void)arg2;
  (void)arg3;

  int i = 0;

  while (true) {
    i = (i + 1) % 100;

    auxdisplay_brightness_set(speed_display, i);

    char *num_str = num_char(i);
    auxdisplay_write(speed_display, num_str, strlen(num_str));

    num_str = num_char(100 - i);
    auxdisplay_write(battery_display, num_str, strlen(num_str));

    struct led_rgb rgb[LED_STRIP_LEN];
    rgb_set_level(rgb, ARRAY_SIZE(rgb), i);
    led_strip_update_rgb(accel_display, rgb, LED_STRIP_LEN);

    rgb_set_level(rgb, ARRAY_SIZE(rgb), 100 - i);
    led_strip_update_rgb(brake_display, rgb, LED_STRIP_LEN);

    k_sleep(K_MSEC(100));
  }
}
