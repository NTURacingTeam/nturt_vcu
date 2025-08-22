#include "modes.h"

// glibc incldes
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/input/sensor_axis.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/err/err.h>
#include <nturt/msg/msg.h>
#include <nturt/sys/sys.h>

// project includes
#include "vcu/ctrl/ctrl.h"
#include "vcu/dashboard.h"

/* macro ---------------------------------------------------------------------*/
#define DEFAULT_MODE SET_BRIGHTNESS

#define CALIB_TIMES 10
#define CALIB_INTERVAL K_MSEC(10)

/* type ----------------------------------------------------------------------*/
enum dashboard_setting_state {
  ACTIVE,

  ERROR_STEER,
  ERROR_ACCEL,
  ERROR_BRAKE,

  MODIFY_UP,
  MODIFY_HOLDING,
  BLINK_OFF,

  NUM_STATES,
};

enum dashboard_setting_mode {
  SET_BRIGHTNESS,
  SET_INV_RL,
  SET_INV_RR,
  SET_STEER,
  SET_ACCEL,
  SET_BRAKE,

  NUM_MODE,
};

struct dashboard_setting_ctx {
  struct k_mutex lock;

  bool states[NUM_STATES];
  enum dashboard_setting_mode mode;

  int steer;
  int accel;
  int brake;

  struct k_work_delayable modify_dwork;
  struct k_work_delayable blink_dwork;
};

/* static function declaration -----------------------------------------------*/
static void dashboard_display(const struct dashboard_setting_ctx *ctx);
static void dashboard_modify(const struct dashboard_setting_ctx *ctx,
                             enum dashboard_setting_mode mode, bool is_up);

static void input_cb(struct input_event *evt, void *user_data);
static void err_cb(uint32_t errcode, bool set, void *user_data);
static void msg_cb(const struct zbus_channel *chan);

static void blink_work(struct k_work *work);
static void modify_work(struct k_work *work);

/* static variable -----------------------------------------------------------*/
static const struct device *steer = DEVICE_DT_GET(DT_NODELABEL(steer));
static const struct device *accel = DEVICE_DT_GET(DT_NODELABEL(accel));
static const struct device *brake = DEVICE_DT_GET(DT_NODELABEL(brake));

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
                    ERR_FILTER_CODE(ERR_CODE_STEER, ERR_CODE_ACCEL,
                                    ERR_CODE_BRAKE));

/* function definition -------------------------------------------------------*/
void dashboard_setting_start() {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.states[ACTIVE] = true;
  g_ctx.states[MODIFY_HOLDING] = false;
  g_ctx.mode = DEFAULT_MODE;
  dashboard_display(&g_ctx);

  sys_work_schedule(&g_ctx.blink_dwork, K_NO_WAIT);

  k_mutex_unlock(&g_ctx.lock);
}

void dashboard_setting_stop() {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.states[ACTIVE] = false;

  k_work_cancel_delayable(&g_ctx.blink_dwork);
  k_work_cancel_delayable(&g_ctx.modify_dwork);

  k_mutex_unlock(&g_ctx.lock);
}

/* static function definition ------------------------------------------------*/
static void dashboard_display(const struct dashboard_setting_ctx *ctx) {
  if (!ctx->states[ACTIVE]) {
    return;
  }

  // display brightness
  dashboard_set_level(DASHBOARD_BATTERY, dashboard_brightness_get());

  // display inv_rl, inv_rr, steer
  dashboard_led_set(LED_NUM_INV_RL, false);
  dashboard_led_set(LED_NUM_INV_RR, false);

  switch (ctx->mode) {
    case SET_INV_RL:
      dashboard_led_set(LED_NUM_INV_RL, true);
      dashboard_set_level(DASHBOARD_SPEED, ctrl_torq_rl_get());
      break;

    case SET_INV_RR:
      dashboard_led_set(LED_NUM_INV_RR, true);
      dashboard_set_level(DASHBOARD_SPEED, ctrl_torq_rr_get());
      break;

    default:
      if (ctx->states[ERROR_STEER]) {
        dashboard_set_error(DASHBOARD_SPEED);
      } else {
        dashboard_set_level(DASHBOARD_SPEED, ctx->steer);
      }

      break;
  }

  // display accelerator
  if (ctx->states[ERROR_ACCEL]) {
    dashboard_set_error(DASHBOARD_ACCEL);
  } else {
    dashboard_set_level(DASHBOARD_ACCEL, ctx->accel);
  }

  // display brake
  if (ctx->states[ERROR_BRAKE]) {
    dashboard_set_error(DASHBOARD_BRAKE);
  } else {
    dashboard_set_level(DASHBOARD_BRAKE, ctx->brake);
  }

  if (ctx->states[BLINK_OFF]) {
    switch (ctx->mode) {
      case SET_BRIGHTNESS:
        dashboard_apply_selected(DASHBOARD_BATTERY);
        break;

      case SET_INV_RL:
      case SET_INV_RR:
      case SET_STEER:
        dashboard_apply_selected(DASHBOARD_SPEED);
        break;

      case SET_ACCEL:
        dashboard_apply_selected(DASHBOARD_ACCEL);
        break;

      case SET_BRAKE:
        dashboard_apply_selected(DASHBOARD_BRAKE);
        break;

      default:
        break;
    }
  }
}

static void dashboard_modify(const struct dashboard_setting_ctx *ctx,
                             enum dashboard_setting_mode mode, bool is_up) {
  switch (mode) {
    case SET_BRIGHTNESS: {
      int brightness = dashboard_brightness_get();
      brightness += is_up ? 1 : -1;
      dashboard_brightness_set(CLAMP(brightness, 0, 100));

      if (IS_ENABLED(CONFIG_VCU_DASHBOARD_SETTINGS)) {
        dashboard_settings_save();
      }

      break;
    }

    case SET_INV_RL: {
      int torq = ctrl_torq_rl_get();
      torq += is_up ? 1 : -1;
      ctrl_torq_rl_set(CLAMP(torq, 0, 100));

      ctrl_settings_save();

      break;
    }

    case SET_INV_RR: {
      int torq = ctrl_torq_rr_get();
      torq += is_up ? 1 : -1;
      ctrl_torq_rr_set(CLAMP(torq, 0, 100));

      ctrl_settings_save();

      break;
    }

    case SET_STEER:
      if (is_up) {
        sensor_axis_channel_range_set_curr(steer, CALIB_TIMES, CALIB_INTERVAL,
                                           false);
      } else {
        sensor_axis_channel_center_set_curr(steer, CALIB_TIMES, CALIB_INTERVAL);
      }

      if (IS_ENABLED(CONFIG_INPUT_SENSOR_AXIS_SETTINGS)) {
        sensor_axis_channel_calib_save(steer);
      }

      break;

    case SET_ACCEL:
      if (is_up) {
        sensor_axis_channel_max_set_curr(accel, CALIB_TIMES, CALIB_INTERVAL);
      } else {
        sensor_axis_channel_min_set_curr(accel, CALIB_TIMES, CALIB_INTERVAL);
      }

      if (IS_ENABLED(CONFIG_INPUT_SENSOR_AXIS_SETTINGS)) {
        sensor_axis_channel_calib_save(accel);
      }

      break;

    case SET_BRAKE:
      if (is_up) {
        sensor_axis_channel_max_set_curr(brake, CALIB_TIMES, CALIB_INTERVAL);
      } else {
        sensor_axis_channel_min_set_curr(brake, CALIB_TIMES, CALIB_INTERVAL);
      }

      if (IS_ENABLED(CONFIG_INPUT_SENSOR_AXIS_SETTINGS)) {
        sensor_axis_channel_calib_save(brake);
      }

      break;

    default:
      break;
  }

  dashboard_display(ctx);
}

static void input_cb(struct input_event *evt, void *user_data) {
  struct dashboard_setting_ctx *ctx = user_data;

  k_mutex_lock(&ctx->lock, K_FOREVER);

  if (!ctx->states[ACTIVE] || evt->type != INPUT_EV_KEY) {
    goto out;
  }

  if (evt->value) {
    switch (evt->code) {
      case INPUT_BTN_LEFT:
      case INPUT_BTN_RIGHT:
        if (evt->code == INPUT_BTN_RIGHT) {
          g_ctx.mode = (g_ctx.mode - 1 + NUM_MODE) % NUM_MODE;
        } else {
          g_ctx.mode = (g_ctx.mode + 1) % NUM_MODE;
        }

        ctx->states[MODIFY_HOLDING] = false;
        k_work_cancel_delayable(&ctx->modify_dwork);
        dashboard_display(ctx);

        break;

      case INPUT_BTN_UP_HOLD:
        ctx->states[MODIFY_HOLDING] = true;

      case INPUT_BTN_UP:
        ctx->states[MODIFY_UP] = true;
        sys_work_schedule(&ctx->modify_dwork, K_NO_WAIT);
        break;

      case INPUT_BTN_DOWN_HOLD:
        ctx->states[MODIFY_HOLDING] = true;

      case INPUT_BTN_DOWN:
        ctx->states[MODIFY_UP] = false;
        sys_work_schedule(&ctx->modify_dwork, K_NO_WAIT);
        break;

      default:
        break;
    }

  } else {
    switch (evt->code) {
      case INPUT_BTN_UP_HOLD:
      case INPUT_BTN_DOWN_HOLD:
        ctx->states[MODIFY_HOLDING] = false;
        k_work_cancel_delayable(&ctx->modify_dwork);
        break;

      default:
        break;
    }
  }

out:
  k_mutex_unlock(&ctx->lock);
}

static void msg_cb(const struct zbus_channel *chan) {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  const struct msg_sensor_cockpit *msg = zbus_chan_const_msg(chan);

  g_ctx.steer = roundf(msg->steer);
  g_ctx.accel = msg->accel;
  g_ctx.brake = msg->brake;
  dashboard_display(&g_ctx);

  k_mutex_unlock(&g_ctx.lock);
}

static void err_cb(uint32_t errcode, bool set, void *user_data) {
  struct dashboard_setting_ctx *ctx = user_data;

  k_mutex_lock(&ctx->lock, K_FOREVER);

  switch (errcode) {
    case ERR_CODE_STEER:
      ctx->states[ERROR_STEER] = set;
      break;

    case ERR_CODE_ACCEL:
      ctx->states[ERROR_ACCEL] = set;
      break;

    case ERR_CODE_BRAKE:
      ctx->states[ERROR_BRAKE] = set;
      break;

    default:
      break;
  }

  dashboard_display(ctx);

  k_mutex_unlock(&ctx->lock);
}

static void blink_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct dashboard_setting_ctx *ctx =
      CONTAINER_OF(dwork, struct dashboard_setting_ctx, blink_dwork);

  k_mutex_lock(&ctx->lock, K_FOREVER);

  ctx->states[BLINK_OFF] = !ctx->states[BLINK_OFF];
  dashboard_display(ctx);

  sys_work_reschedule(&ctx->blink_dwork, LED_BLINK_PERIOD);

  k_mutex_unlock(&ctx->lock);
}

static void modify_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct dashboard_setting_ctx *ctx =
      CONTAINER_OF(dwork, struct dashboard_setting_ctx, modify_dwork);

  k_mutex_lock(&ctx->lock, K_FOREVER);

  dashboard_modify(ctx, ctx->mode, ctx->states[MODIFY_UP]);

  if (ctx->states[MODIFY_HOLDING]) {
    sys_work_reschedule(&ctx->modify_dwork, HOLD_MODIFY_INTERVAL);
  }

  k_mutex_unlock(&ctx->lock);
}
