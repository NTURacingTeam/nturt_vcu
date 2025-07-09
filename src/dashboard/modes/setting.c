#include "vcu/dashboard.h"

// glibc incldes
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/auxdisplay.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

/* type ----------------------------------------------------------------------*/
enum {
  ACTIVE,

  INCREASING,

  NUM_STATE,
};

struct dashboard_setting_ctx {
  bool states[NUM_STATE];
  struct k_work_delayable modify_dwork;
};

/* static function declaration -----------------------------------------------*/
static void show_brightness(uint8_t brightness);
static void modify_brightness(bool increase);

static void input_cb(struct input_event *evt, void *user_data);
static void modify_work(struct k_work *work);

/* static variable -----------------------------------------------------------*/
static const struct device *speed_display =
    DEVICE_DT_GET(DT_NODELABEL(speed_display));

static struct dashboard_setting_ctx g_ctx = {
    .states = {0},
    .modify_dwork = Z_WORK_DELAYABLE_INITIALIZER(modify_work),
};

INPUT_CALLBACK_DEFINE(NULL, input_cb, &g_ctx);

/* function definition -------------------------------------------------------*/
void dashboard_setting_start() {
  g_ctx.states[ACTIVE] = true;

  uint8_t brightness = dashboard_brightness_get();
  show_brightness(brightness);
}

void dashboard_setting_stop() {
  g_ctx.states[ACTIVE] = false;

  k_work_cancel_delayable(&g_ctx.modify_dwork);
}

/* static function definition ------------------------------------------------*/
static void show_brightness(uint8_t brightness) {
  // longer to prevent compiler warnings
  char buf[20];
  snprintf(buf, sizeof(buf), "%2hu", CLAMP(brightness, 0, 99));

  auxdisplay_write(speed_display, buf, strlen(buf));
}

static void modify_brightness(bool increase) {
  uint8_t brightness = dashboard_brightness_get();
  brightness += increase ? 1 : -1;
  brightness = CLAMP(brightness, 0, 100);

  dashboard_brightness_set(brightness);
  show_brightness(brightness);
}

static void input_cb(struct input_event *evt, void *user_data) {
  struct dashboard_setting_ctx *ctx = user_data;

  if (!ctx->states[ACTIVE] && evt->type != INPUT_EV_KEY) {
    return;
  }

  if (evt->value) {
    switch (evt->code) {
      case INPUT_BTN_UP:
        modify_brightness(true);
        break;

      case INPUT_BTN_DOWN:
        modify_brightness(false);
        break;

      case INPUT_BTN_UP_HOLD:
        ctx->states[INCREASING] = true;
        k_work_schedule(&ctx->modify_dwork, K_NO_WAIT);
        break;

      case INPUT_BTN_DOWN_HOLD:
        ctx->states[INCREASING] = false;
        k_work_schedule(&ctx->modify_dwork, K_NO_WAIT);
        break;

      default:
        break;
    }

  } else if (evt->code == INPUT_BTN_UP_HOLD ||
             evt->code == INPUT_BTN_DOWN_HOLD) {
    k_work_cancel_delayable(&ctx->modify_dwork);
  }
}

static void modify_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct dashboard_setting_ctx *ctx =
      CONTAINER_OF(dwork, struct dashboard_setting_ctx, modify_dwork);

  modify_brightness(ctx->states[INCREASING]);

  k_work_reschedule(&ctx->modify_dwork, K_MSEC(100));
}
