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

// nturt includes
#include <nturt/sys/sys.h>

// project includes
#include "vcu/dashboard.h"

/* type ----------------------------------------------------------------------*/
enum dashboard_test_state {
  ACTIVE,

  NUM_STATES,
};

struct dashboard_test_ctx {
  struct k_mutex lock;

  bool states[NUM_STATES];
  int counter;
  int pressed;

  struct k_work_delayable test_dwork;
};

/* static function declaration -----------------------------------------------*/
static void input_cb(struct input_event *evt, void *user_data);
static void test_work(struct k_work *work);

/* static variable -----------------------------------------------------------*/
static const struct device *speed_display =
    DEVICE_DT_GET(DT_NODELABEL(speed_display));

static struct dashboard_test_ctx g_ctx = {
    .lock = Z_MUTEX_INITIALIZER(g_ctx.lock),
    .states = {0},
    .counter = 0,
    .pressed = -1,
    .test_dwork = Z_WORK_DELAYABLE_INITIALIZER(test_work),
};

INPUT_CALLBACK_DEFINE(NULL, input_cb, &g_ctx);

/* function definition -------------------------------------------------------*/
void dashboard_test_start() {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.states[ACTIVE] = true;
  g_ctx.counter = 0;

  if (IN_RANGE(g_ctx.pressed, 0, NUM_LED - 1)) {
    dashboard_led_set(g_ctx.pressed, true);
  }

  sys_work_schedule(&g_ctx.test_dwork, K_NO_WAIT);

  k_mutex_unlock(&g_ctx.lock);
}

void dashboard_test_stop() {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.states[ACTIVE] = false;

  k_work_cancel_delayable(&g_ctx.test_dwork);

  k_mutex_unlock(&g_ctx.lock);
}

/* static function definition ------------------------------------------------*/
static void input_cb(struct input_event *evt, void *user_data) {
  struct dashboard_test_ctx *ctx = user_data;

  k_mutex_lock(&ctx->lock, K_FOREVER);

  if (!ctx->states[ACTIVE] || evt->type != INPUT_EV_KEY) {
    goto out;
  }

  if (IN_RANGE(evt->code, INPUT_BTN_1, INPUT_BTN_7)) {
    if (IN_RANGE(ctx->pressed, 0, NUM_LED - 1)) {
      dashboard_led_set(ctx->pressed, false);
    }

    ctx->pressed += (evt->value ? 1 : -1) * (evt->code - INPUT_BTN_0);

    if (IN_RANGE(ctx->pressed, 0, NUM_LED - 1)) {
      dashboard_led_set(ctx->pressed, true);
    }
  }

out:
  k_mutex_unlock(&ctx->lock);
}

static void test_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct dashboard_test_ctx *ctx =
      CONTAINER_OF(dwork, struct dashboard_test_ctx, test_dwork);

  ctx->counter = (ctx->counter + 1) % 100;

  auxdisplay_brightness_set(speed_display, ctx->counter);
  for (int j = 0; j < NUM_DASHBOARD_DISPLAY; j++) {
    dashboard_set_level(j, j % 2 == 0 ? ctx->counter : 100 - ctx->counter);
  }

  sys_work_reschedule(&ctx->test_dwork, HOLD_MODIFY_INTERVAL);
}
