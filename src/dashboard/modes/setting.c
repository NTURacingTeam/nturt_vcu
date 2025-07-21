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
#include <zephyr/drivers/input/sensor_axis.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/err/err.h>
#include <nturt/msg/msg.h>

/* macro ---------------------------------------------------------------------*/
#define DEFAULT_MODE SET_BRIGHTNESS

/* type ----------------------------------------------------------------------*/
enum {
  ACTIVE,

  ERROR_ACCEL,
  ERROR_BRAKE,

  MODIFY_INCREASING,
  BLINK_OFF,

  NUM_STATES,
};

enum dashboard_setting_mode {
  SET_BRIGHTNESS,
  SET_ACCEL,
  SET_BRAKE,

  NUM_MODE,
};

struct dashboard_setting_ctx {
  struct k_mutex lock;

  bool states[NUM_STATES];
  enum dashboard_setting_mode mode;

  int accel;
  int brake;

  struct k_work_delayable modify_dwork;
  struct k_work_delayable blink_dwork;
};

/* static function declaration -----------------------------------------------*/
static void dashboard_display(const struct dashboard_setting_ctx *ctx);
static void dashboard_modify_brightness(const struct dashboard_setting_ctx *ctx,
                                        bool increase);

static void input_cb(struct input_event *evt, void *user_data);
static void err_cb(uint32_t errcode, bool set, void *user_data);
static void msg_cb(const struct zbus_channel *chan);

static void blink_work(struct k_work *work);
static void modify_work(struct k_work *work);

/* static variable -----------------------------------------------------------*/
static const struct device *speed_display =
    DEVICE_DT_GET(DT_NODELABEL(speed_display));
static const struct device *accel_display =
    DEVICE_DT_GET(DT_NODELABEL(accel_display));
static const struct device *brake_display =
    DEVICE_DT_GET(DT_NODELABEL(brake_display));

static const struct device *apps1 =
    DEVICE_DT_GET(DT_NODELABEL(apps1_sensor_axis));
static const struct device *apps2 =
    DEVICE_DT_GET(DT_NODELABEL(apps2_sensor_axis));

static const struct device *bse1 =
    DEVICE_DT_GET(DT_NODELABEL(bse1_sensor_axis));
static const struct device *bse2 =
    DEVICE_DT_GET(DT_NODELABEL(bse2_sensor_axis));

static struct dashboard_setting_ctx g_ctx = {
    .lock = Z_MUTEX_INITIALIZER(g_ctx.lock),
    .states = {0},
    .mode = DEFAULT_MODE,
    .accel = 0,
    .brake = 0,
    .modify_dwork = Z_WORK_DELAYABLE_INITIALIZER(modify_work),
    .blink_dwork = Z_WORK_DELAYABLE_INITIALIZER(blink_work),
};

INPUT_CALLBACK_DEFINE(NULL, input_cb, &g_ctx);

ZBUS_LISTENER_DEFINE(dashboard_setting_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_sensor_cockpit_chan, dashboard_setting_listener, 0);

ERR_CALLBACK_DEFINE(err_cb, &g_ctx,
                    ERR_FILTER_CODE(ERR_CODE_ACCEL, ERR_CODE_BRAKE));

/* function definition -------------------------------------------------------*/
void dashboard_setting_start() {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.states[ACTIVE] = true;
  g_ctx.mode = DEFAULT_MODE;
  dashboard_display(&g_ctx);

  k_work_schedule(&g_ctx.blink_dwork, K_NO_WAIT);

  k_mutex_unlock(&g_ctx.lock);
}

void dashboard_setting_stop() {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.states[ACTIVE] = false;

  k_work_cancel_delayable(&g_ctx.blink_dwork);
  k_work_cancel_delayable(&g_ctx.modify_dwork);

  if (IS_ENABLED(CONFIG_VCU_DASHBOARD_SETTINGS)) {
    dashboard_settings_save();
  }

  k_mutex_unlock(&g_ctx.lock);
}

/* static function definition ------------------------------------------------*/
static void dashboard_display(const struct dashboard_setting_ctx *ctx) {
  if (!ctx->states[ACTIVE]) {
    return;
  }

  // longer to prevent compiler warnings
  char buf[20];
  struct led_rgb rgb[LED_STRIP_LEN];

  // display brightness
  if (ctx->mode == SET_BRIGHTNESS && ctx->states[BLINK_OFF]) {
    snprintf(buf, sizeof(buf), "  ");

  } else {
    int brightness = dashboard_brightness_get();
    if (brightness == 100) {
      snprintf(buf, sizeof(buf), "00");
    } else {
      snprintf(buf, sizeof(buf), "%2hu", brightness);
    }
  }

  auxdisplay_write(speed_display, buf, strlen(buf));

  // display accelerator
  if (ctx->states[ERROR_ACCEL]) {
    rgb_set_error(rgb, LED_STRIP_LEN);
  } else {
    rgb_set_level(rgb, LED_STRIP_LEN, ctx->accel);
  }

  if (ctx->mode == SET_ACCEL && ctx->states[BLINK_OFF]) {
    rgb_apply_selected(rgb, LED_STRIP_LEN);
  }

  led_strip_update_rgb(accel_display, rgb, LED_STRIP_LEN);

  // display brake
  if (ctx->states[ERROR_BRAKE]) {
    rgb_set_error(rgb, LED_STRIP_LEN);
  } else {
    rgb_set_level(rgb, LED_STRIP_LEN, ctx->brake);
  }

  if (ctx->mode == SET_BRAKE && ctx->states[BLINK_OFF]) {
    rgb_apply_selected(rgb, LED_STRIP_LEN);
  }

  led_strip_update_rgb(brake_display, rgb, LED_STRIP_LEN);
}

static void dashboard_modify_brightness(const struct dashboard_setting_ctx *ctx,
                                        bool increase) {
  int brightness = dashboard_brightness_get();
  brightness += increase ? 1 : -1;
  brightness = CLAMP(brightness, 0, 100);

  dashboard_brightness_set(brightness);
  dashboard_display(ctx);
}

static void input_cb(struct input_event *evt, void *user_data) {
  struct dashboard_setting_ctx *ctx = user_data;

  k_mutex_lock(&ctx->lock, K_FOREVER);

  if (!ctx->states[ACTIVE] || evt->type != INPUT_EV_KEY) {
    goto out;
  }

  // change mode
  if (evt->value &&
      (evt->code == INPUT_BTN_LEFT || evt->code == INPUT_BTN_RIGHT)) {
    if (evt->code == INPUT_BTN_RIGHT) {
      g_ctx.mode = (g_ctx.mode - 1 + NUM_MODE) % NUM_MODE;
    } else {
      g_ctx.mode = (g_ctx.mode + 1) % NUM_MODE;
    }

    k_work_cancel_delayable(&ctx->modify_dwork);
    dashboard_display(ctx);
    goto out;
  }

  switch (ctx->mode) {
    case SET_BRIGHTNESS:
      if (evt->value) {
        switch (evt->code) {
          case INPUT_BTN_UP:
            dashboard_modify_brightness(ctx, true);
            break;

          case INPUT_BTN_DOWN:
            dashboard_modify_brightness(ctx, false);
            break;

          case INPUT_BTN_UP_HOLD:
            ctx->states[MODIFY_INCREASING] = true;
            k_work_schedule(&ctx->modify_dwork, K_NO_WAIT);
            break;

          case INPUT_BTN_DOWN_HOLD:
            ctx->states[MODIFY_INCREASING] = false;
            k_work_schedule(&ctx->modify_dwork, K_NO_WAIT);
            break;

          default:
            break;
        }

      } else if (evt->code == INPUT_BTN_UP_HOLD ||
                 evt->code == INPUT_BTN_DOWN_HOLD) {
        k_work_cancel_delayable(&ctx->modify_dwork);
      }

      break;

    case SET_ACCEL:
      if (evt->value) {
        if (evt->code == INPUT_BTN_UP) {
          sensor_axis_sensor_max_set_curr(apps1, 10, K_MSEC(10));
          sensor_axis_sensor_max_set_curr(apps2, 10, K_MSEC(10));

        } else if (evt->code == INPUT_BTN_DOWN) {
          sensor_axis_sensor_min_set_curr(apps1, 10, K_MSEC(10));
          sensor_axis_sensor_min_set_curr(apps2, 10, K_MSEC(10));
        }

        sensor_axis_sensor_calib_save(apps1);
        sensor_axis_sensor_calib_save(apps2);
      }

      break;

    case SET_BRAKE:
      if (evt->value) {
        if (evt->code == INPUT_BTN_UP) {
          sensor_axis_sensor_max_set_curr(bse1, 10, K_MSEC(10));
          sensor_axis_sensor_max_set_curr(bse2, 10, K_MSEC(10));

        } else if (evt->code == INPUT_BTN_DOWN) {
          sensor_axis_sensor_min_set_curr(bse1, 10, K_MSEC(10));
          sensor_axis_sensor_min_set_curr(bse2, 10, K_MSEC(10));
        }

        sensor_axis_sensor_calib_save(bse1);
        sensor_axis_sensor_calib_save(bse2);
      }
      break;

    default:
      break;
  }

out:
  k_mutex_unlock(&ctx->lock);
}

static void msg_cb(const struct zbus_channel *chan) {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  const struct msg_sensor_cockpit *msg = zbus_chan_const_msg(chan);

  g_ctx.accel = msg->accel;
  g_ctx.brake = msg->brake;
  dashboard_display(&g_ctx);

  k_mutex_unlock(&g_ctx.lock);
}

static void err_cb(uint32_t errcode, bool set, void *user_data) {
  struct dashboard_setting_ctx *ctx = user_data;

  k_mutex_lock(&ctx->lock, K_FOREVER);

  switch (errcode) {
    case ERR_CODE_ACCEL:
      ctx->states[ERROR_ACCEL] = set;
      dashboard_display(ctx);
      break;

    case ERR_CODE_BRAKE:
      ctx->states[ERROR_BRAKE] = set;
      dashboard_display(ctx);
      break;

    default:
      break;
  }

  k_mutex_unlock(&ctx->lock);
}

static void blink_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct dashboard_setting_ctx *ctx =
      CONTAINER_OF(dwork, struct dashboard_setting_ctx, blink_dwork);

  k_mutex_lock(&ctx->lock, K_FOREVER);

  ctx->states[BLINK_OFF] = !ctx->states[BLINK_OFF];
  dashboard_display(ctx);

  k_work_reschedule(&ctx->blink_dwork, LED_BLINK_PERIOD);
  k_mutex_unlock(&ctx->lock);
}

static void modify_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct dashboard_setting_ctx *ctx =
      CONTAINER_OF(dwork, struct dashboard_setting_ctx, modify_dwork);

  k_mutex_lock(&ctx->lock, K_FOREVER);

  dashboard_modify_brightness(ctx, ctx->states[MODIFY_INCREASING]);

  k_work_reschedule(&ctx->modify_dwork, K_MSEC(100));
  k_mutex_unlock(&ctx->lock);
}
