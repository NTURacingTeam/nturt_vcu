#include "modes.h"

// glibc incldes
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// zephyr includes
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/err/err.h>
#include <nturt/msg/msg.h>

// project includes
#include "vcu/ctrl/inv.h"
#include "vcu/ctrl/states.h"
#include "vcu/dashboard.h"

/* type ----------------------------------------------------------------------*/
enum dashboard_normal_state {
  ACTIVE,

  ERROR_ACCEL,
  ERROR_BRAKE,
  ERROR_PEDAL_PLAUS,
  ERROR_HB_INV_RL,
  ERROR_HB_INV_RR,
  ERROR_HB_ACC,
  ERROR_INV_RL,
  ERROR_INV_RR,

  STAT_RUNNING,
  STAT_ERROR,

  NUM_DASHBOARD_STATE,
};

struct dashboard_normal_ctx {
  struct k_mutex lock;

  bool states[NUM_DASHBOARD_STATE];
};

/* static function declaraion ------------------------------------------------*/
static void dashboard_state_update(struct dashboard_normal_ctx *ctx, int state,
                                   bool set);

static void input_cb(struct input_event *evt, void *user_data);
static void msg_cb(const struct zbus_channel *chan);
static void err_cb(uint32_t errcode, bool set, void *user_data);
static void states_cb(enum states_state state, bool is_entry, void *user_data);

/* static variable -----------------------------------------------------------*/
static struct dashboard_normal_ctx g_ctx = {
    .lock = Z_MUTEX_INITIALIZER(g_ctx.lock),
    .states = {0},
};

INPUT_CALLBACK_DEFINE(NULL, input_cb, &g_ctx);

ZBUS_LISTENER_DEFINE(dashboard_normal_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_sensor_cockpit_chan, dashboard_normal_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_sensor_wheel_chan, dashboard_normal_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_ts_acc_chan, dashboard_normal_listener, 0);

ERR_CALLBACK_DEFINE(err_cb, &g_ctx,
                    ERR_FILTER_CODE(ERR_CODE_ACCEL, ERR_CODE_BRAKE,
                                    ERR_CODE_PEDAL_PLAUS, ERR_CODE_HB_INV_RL,
                                    ERR_CODE_HB_INV_RR, ERR_CODE_HB_ACC,
                                    ERR_CODE_INV_RL, ERR_CODE_INV_RR));

STATES_CALLBACK_DEFINE(STATE_RUNNING | STATE_ERR, states_cb, &g_ctx);

/* function definition -------------------------------------------------------*/
void dashboard_normal_start() {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  dashboard_state_update(&g_ctx, ACTIVE, true);

  for (int state = ACTIVE + 1; state < NUM_DASHBOARD_STATE; state++) {
    dashboard_state_update(&g_ctx, state, g_ctx.states[state]);
  }

  k_mutex_unlock(&g_ctx.lock);
}

void dashboard_normal_stop() {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);
  dashboard_state_update(&g_ctx, ACTIVE, false);
  k_mutex_unlock(&g_ctx.lock);
}

/* static function definition ------------------------------------------------*/
static void dashboard_state_update(struct dashboard_normal_ctx *ctx, int state,
                                   bool set) {
  ctx->states[state] = set;

  if (!ctx->states[ACTIVE]) {
    return;
  }

  switch (state) {
    case ERROR_ACCEL:
      if (set) {
        dashboard_set_error(DASHBOARD_ACCEL);
      }
      break;

    case ERROR_BRAKE:
      if (set) {
        dashboard_set_error(DASHBOARD_BRAKE);
      }
      break;

    case ERROR_PEDAL_PLAUS:
      dashboard_led_set(LED_NUM_PEDAL_PLAUS, set);
      break;

    case ERROR_HB_INV_RL:
    case ERROR_HB_INV_RR:
      if (g_ctx.states[ERROR_HB_INV_RL] || g_ctx.states[ERROR_HB_INV_RR]) {
        dashboard_set_error(DASHBOARD_SPEED);
      }
      break;

    case ERROR_HB_ACC:
      if (set) {
        dashboard_set_error(DASHBOARD_BATTERY);
      }
      break;

    case ERROR_INV_RL:
      dashboard_led_set(LED_NUM_INV_RL, set);
      break;

    case ERROR_INV_RR:
      dashboard_led_set(LED_NUM_INV_RR, set);
      break;

    case STAT_RUNNING:
      dashboard_led_set(LED_NUM_RUNNING, set);
      break;

    case STAT_ERROR:
      dashboard_led_set(LED_NUM_ERROR, set);
      break;

    default:
      break;
  }
}

static void input_cb(struct input_event *evt, void *user_data) {
  struct dashboard_normal_ctx *ctx = user_data;

  k_mutex_lock(&ctx->lock, K_FOREVER);

  if (!ctx->states[ACTIVE] || evt->type != INPUT_EV_KEY) {
    k_mutex_unlock(&ctx->lock);
    return;
  }

  if (evt->value && evt->code == INPUT_BTN_FAULT_RESET) {
    ctrl_inv_fault_reset();
  }

  k_mutex_unlock(&ctx->lock);
}

static void msg_cb(const struct zbus_channel *chan) {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  if (!g_ctx.states[ACTIVE]) {
    k_mutex_unlock(&g_ctx.lock);
    return;
  }

  if (chan == &msg_sensor_cockpit_chan) {
    const struct msg_sensor_cockpit *msg = zbus_chan_const_msg(chan);

    if (!g_ctx.states[ERROR_ACCEL]) {
      dashboard_set_level(DASHBOARD_ACCEL, msg->accel);
    }

    if (!g_ctx.states[ERROR_BRAKE]) {
      dashboard_set_level(DASHBOARD_BRAKE, msg->brake);
    }

  } else if (chan == &msg_sensor_wheel_chan) {
    const struct msg_sensor_wheel *msg = zbus_chan_const_msg(chan);

    if (!g_ctx.states[ERROR_HB_INV_RL] && !g_ctx.states[ERROR_HB_INV_RR]) {
      int speed = roundf((-msg->speed.rl + msg->speed.rr) / 2.0F * 0.00736F);
      dashboard_set_level(DASHBOARD_SPEED, speed);
    }

  } else if (chan == &msg_ts_acc_chan) {
    const struct msg_ts_acc *msg = zbus_chan_const_msg(chan);

    if (!g_ctx.states[ERROR_HB_ACC]) {
      dashboard_set_level(DASHBOARD_BATTERY, msg->soc);
    }
  }

  k_mutex_unlock(&g_ctx.lock);
}

static void err_cb(uint32_t errcode, bool set, void *user_data) {
  struct dashboard_normal_ctx *ctx = user_data;

  k_mutex_lock(&ctx->lock, K_FOREVER);

  switch (errcode) {
    case ERR_CODE_ACCEL:
      dashboard_state_update(ctx, ERROR_ACCEL, set);
      break;

    case ERR_CODE_BRAKE:
      dashboard_state_update(ctx, ERROR_BRAKE, set);
      break;

    case ERR_CODE_PEDAL_PLAUS:
      dashboard_state_update(ctx, ERROR_PEDAL_PLAUS, set);
      break;

    case ERR_CODE_HB_INV_RL:
      dashboard_state_update(ctx, ERROR_HB_INV_RL, set);
      break;

    case ERR_CODE_HB_INV_RR:
      dashboard_state_update(ctx, ERROR_HB_INV_RR, set);
      break;

    case ERR_CODE_HB_ACC:
      dashboard_state_update(ctx, ERROR_HB_ACC, set);
      break;

    case ERR_CODE_INV_RL:
      dashboard_state_update(ctx, ERROR_INV_RL, set);
      break;

    case ERR_CODE_INV_RR:
      dashboard_state_update(ctx, ERROR_INV_RR, set);
      break;

    default:
      break;
  }

  k_mutex_unlock(&ctx->lock);
}

static void states_cb(enum states_state state, bool is_entry, void *user_data) {
  struct dashboard_normal_ctx *ctx = user_data;

  k_mutex_lock(&ctx->lock, K_FOREVER);

  switch (state) {
    case STATE_RUNNING:
      dashboard_state_update(ctx, STAT_RUNNING, is_entry);
      break;

    case STATE_ERR:
      dashboard_state_update(ctx, STAT_ERROR, is_entry);
      break;

    default:
      return;
  }

  k_mutex_unlock(&ctx->lock);
}
