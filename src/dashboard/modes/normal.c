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
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/err/err.h>
#include <nturt/msg/msg.h>

// project includes
#include "vcu/ctrl/states.h"

/* type ----------------------------------------------------------------------*/
enum {
  ACTIVE,

  ERROR_ACCEL,
  ERROR_BRAKE,
  ERROR_PEDAL_PLAUS,
  ERROR_INV_RL,
  ERROR_INV_RR,
  ERROR_ACC,

  RUNNING,
  ERR,

  NUM_DASHBOARD_STATE,
};

struct dashboard_normal_ctx {
  const char *const err_str;

  struct led_rgb err_rgb[LED_STRIP_LEN];

  struct k_mutex lock;

  bool states[NUM_DASHBOARD_STATE];
};

/* static function declaraion ------------------------------------------------*/
static void led_set(const struct device *dev, int led, bool set);
static void dashboard_state_update(struct dashboard_normal_ctx *ctx, int state,
                                   bool set);

static int init();

static void msg_cb(const struct zbus_channel *chan);
static void err_cb(uint32_t errcode, bool set, void *user_data);
static void states_cb(enum states_state state, bool is_entry, void *user_data);

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

static struct dashboard_normal_ctx g_ctx = {
    .err_str = "Er",
    .lock = Z_MUTEX_INITIALIZER(g_ctx.lock),
    .states = {0},
};

ZBUS_LISTENER_DEFINE(dashboard_normal_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_cockpit_data_chan, dashboard_normal_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_wheel_data_chan, dashboard_normal_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_acc_chan, dashboard_normal_listener, 0);

ERR_CALLBACK_DEFINE(err_cb, &g_ctx,
                    ERR_FILTER_CODE(ERR_CODE_ACCEL, ERR_CODE_BRAKE,
                                    ERR_CODE_PEDAL_PLAUS, ERR_CODE_HB_INV_RL,
                                    ERR_CODE_HB_INV_RR, ERR_CODE_HB_ACC));

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
static void led_set(const struct device *dev, int led, bool set) {
  if (set) {
    led_on(dev, led);
  } else {
    led_off(dev, led);
  }
}

static void dashboard_state_update(struct dashboard_normal_ctx *ctx, int state,
                                   bool set) {
  ctx->states[state] = set;

  if (!ctx->states[ACTIVE]) {
    return;
  }

  switch (state) {
    case ERROR_ACCEL:
      if (set) {
        led_strip_update_rgb(accel_display, ctx->err_rgb, LED_STRIP_LEN);
      }
      break;

    case ERROR_BRAKE:
      if (set) {
        led_strip_update_rgb(brake_display, ctx->err_rgb, LED_STRIP_LEN);
      }
      break;

    case ERROR_PEDAL_PLAUS:
      led_set(leds, LED_NUM_PEDAL_PLAUS, set);
      break;

    case ERROR_INV_RL:
    case ERROR_INV_RR:
      if (g_ctx.states[ERROR_INV_RL] || g_ctx.states[ERROR_INV_RR]) {
        auxdisplay_write(speed_display, ctx->err_str, strlen(ctx->err_str));
      }
      break;

    case ERROR_ACC:
      if (set) {
        auxdisplay_write(battery_display, ctx->err_str, strlen(ctx->err_str));
      }
      break;

    case RUNNING:
      led_set(leds, LED_NUM_RUNNING, set);
      break;

    case ERR:
      led_set(leds, LED_NUM_ERROR, set);
      break;

    default:
      __ASSERT(false, "Invalid state: %d", state);
  }
}

static int init() {
  rgb_set_error(g_ctx.err_rgb, LED_STRIP_LEN);

  return 0;
}

static void msg_cb(const struct zbus_channel *chan) {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  if (!g_ctx.states[ACTIVE]) {
    k_mutex_unlock(&g_ctx.lock);
    return;
  }

  // longer to prevent compiler warnings
  char buf[20];
  struct led_rgb rgb[LED_STRIP_LEN];

  if (chan == &msg_cockpit_data_chan) {
    const struct msg_cockpit_data *msg = zbus_chan_const_msg(chan);

    if (!g_ctx.states[ERROR_ACCEL]) {
      rgb_set_level(rgb, LED_STRIP_LEN, msg->accel);
      led_strip_update_rgb(accel_display, rgb, LED_STRIP_LEN);
    }

    if (!g_ctx.states[ERROR_BRAKE]) {
      rgb_set_level(rgb, LED_STRIP_LEN, msg->brake);
      led_strip_update_rgb(brake_display, rgb, LED_STRIP_LEN);
    }

  } else if (chan == &msg_wheel_data_chan) {
    const struct msg_wheel_data *msg = zbus_chan_const_msg(chan);

    if (!g_ctx.states[ERROR_INV_RL] && !g_ctx.states[ERROR_INV_RR]) {
      int speed = RPM_TO_SPEED((msg->speed.rl + msg->speed.rr) / 2.0F);
      snprintf(buf, sizeof(buf), "%2d", CLAMP(speed, -9, 99));
      auxdisplay_write(speed_display, buf, strlen(buf));
    }

  } else if (chan == &msg_acc_chan) {
    const struct msg_acc *msg = zbus_chan_const_msg(chan);

    if (!g_ctx.states[ERROR_ACC]) {
      snprintf(buf, sizeof(buf), "%2d", CLAMP(msg->soc, -9, 99));
      auxdisplay_write(battery_display, buf, strlen(buf));
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
      dashboard_state_update(ctx, ERROR_INV_RL, set);
      break;

    case ERR_CODE_HB_INV_RR:
      dashboard_state_update(ctx, ERROR_INV_RR, set);
      break;

    case ERR_CODE_HB_ACC:
      dashboard_state_update(ctx, ERROR_ACC, set);
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
      dashboard_state_update(ctx, RUNNING, is_entry);
      break;

    case STATE_ERR:
      dashboard_state_update(ctx, ERR, is_entry);
      break;

    default:
      return;
  }

  k_mutex_unlock(&ctx->lock);
}
