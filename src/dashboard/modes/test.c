#include "modes.h"

// glibc incldes
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/auxdisplay.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

// project includes
#include "vcu/dashboard.h"

/* type ----------------------------------------------------------------------*/
struct dashboard_test_ctx {
  int pressed;

  k_tid_t tid;
  struct k_thread thread;
};

/* static function declaration -----------------------------------------------*/
static void input_cb(struct input_event *evt, void *user_data);
static void dashboard_test_thread(void *arg1, void *arg2, void *arg3);

/* static variable -----------------------------------------------------------*/
static const struct device *speed_display =
    DEVICE_DT_GET(DT_NODELABEL(speed_display));

static struct dashboard_test_ctx g_ctx = {
    .pressed = -1,
    .tid = NULL,
};

K_THREAD_STACK_DEFINE(dashboard_test_thread_stack, 512);

INPUT_CALLBACK_DEFINE(NULL, input_cb, &g_ctx);

/* function definition -------------------------------------------------------*/
void dashboard_test_start() {
  if (g_ctx.pressed != -1 && g_ctx.pressed < NUM_LED) {
    dashboard_led_set(g_ctx.pressed, true);
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
static void input_cb(struct input_event *evt, void *user_data) {
  struct dashboard_test_ctx *ctx = user_data;

  if (evt->type == INPUT_EV_KEY && evt->code >= INPUT_BTN_1 &&
      evt->code <= INPUT_BTN_7) {
    if (ctx->tid != NULL && ctx->pressed != -1 && ctx->pressed < NUM_LED) {
      dashboard_led_set(ctx->pressed, false);
    }

    ctx->pressed += (evt->value ? 1 : -1) * (evt->code - INPUT_BTN_0);

    if (ctx->tid != NULL && ctx->pressed != -1 && ctx->pressed < NUM_LED) {
      dashboard_led_set(ctx->pressed, true);
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
    for (int j = 0; j < NUM_DASHBOARD_DISPLAY; j++) {
      dashboard_set_level(j, j % 2 == 0 ? i : 100 - i);
    }

    k_sleep(K_MSEC(100));
  }
}
