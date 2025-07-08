#include "dashboard.h"

// glibc incldes
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/auxdisplay.h>
#include <zephyr/drivers/led.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/err/err.h>
#include <nturt/msg/msg.h>

/* type ----------------------------------------------------------------------*/
enum {
  ACTIVE,

  ERROR_BATTERY,
  ERROR_ACCEL,
  ERROR_BRAKE,

  NUM_DASHBOARD_STATE,
};

struct dashboard_normal_ctx {
  struct k_mutex lock;

  bool states[NUM_DASHBOARD_STATE];
};

/* static function declaraion ------------------------------------------------*/
static void rgb_set_level(struct led_rgb *rgb, int len, int level);

/// @brief Set the LEDs to error pattern, which is a five-zone pattern with the
/// second and fourth zones lit up.
static void rgb_set_error_pattern(struct led_rgb *rgb, int len);

static void msg_cb(const struct zbus_channel *chan);
static void input_cb(struct input_event *evt, void *user_data);
static void err_cb(uint32_t errcode, bool set, void *user_data);

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
    .lock = Z_MUTEX_INITIALIZER(g_ctx.lock),
    .states = {0},
};

ZBUS_LISTENER_DEFINE(dashboard_normal_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_cockpit_data_chan, dashboard_normal_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_wheel_data_chan, dashboard_normal_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_acc_chan, dashboard_normal_listener, 0);

INPUT_CALLBACK_DEFINE(NULL, input_cb, &g_ctx);

ERR_CALLBACK_DEFINE(err_cb, &g_ctx,
                    ERR_FILTER_CODE(ERR_CODE_ACCEL, ERR_CODE_BRAKE));

/* function definition -------------------------------------------------------*/
void dashboard_normal_start() {
  static const char *err_str = "Er";
  struct led_rgb rgb[LED_STRIP_LEN];

  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.states[ACTIVE] = true;

  // auxdisplay_write(speed_display, err_str, strlen(err_str));

  if (g_ctx.states[ERROR_BATTERY]) {
    auxdisplay_write(battery_display, err_str, strlen(err_str));
  }

  if (g_ctx.states[ERROR_ACCEL]) {
    rgb_set_error_pattern(rgb, LED_STRIP_LEN);
    led_strip_update_rgb(accel_display, rgb, LED_STRIP_LEN);
  }

  if (g_ctx.states[ERROR_BRAKE]) {
    rgb_set_error_pattern(rgb, LED_STRIP_LEN);
    led_strip_update_rgb(brake_display, rgb, LED_STRIP_LEN);
  }

  k_mutex_unlock(&g_ctx.lock);
}

void dashboard_normal_stop() {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);
  g_ctx.states[ACTIVE] = false;
  k_mutex_unlock(&g_ctx.lock);
}

/* static function definition ------------------------------------------------*/
static void rgb_set_level(struct led_rgb *rgb, int len, int level) {
  level = DIV_ROUND_CLOSEST(level * len, 100);

  for (int i = 0; i < level; i++) {
    rgb[i].r = 1;
  }

  for (int i = level; i < len; i++) {
    rgb[i].r = 0;
  }
}

static void rgb_set_error_pattern(struct led_rgb *rgb, int len) {
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
      rgb_set_level(rgb, ARRAY_SIZE(rgb), msg->accel);
      led_strip_update_rgb(accel_display, rgb, LED_STRIP_LEN);
    }

    if (!g_ctx.states[ERROR_BRAKE]) {
      rgb_set_level(rgb, ARRAY_SIZE(rgb), msg->brake);
      led_strip_update_rgb(brake_display, rgb, LED_STRIP_LEN);
    }

  } else if (chan == &msg_wheel_data_chan) {
    const struct msg_wheel_data *msg = zbus_chan_const_msg(chan);

    /// @todo check error
    int speed = RPM_TO_SPEED((msg->speed.rl + msg->speed.rr) / 2.0F);
    snprintf(buf, sizeof(buf), "%2d", speed > 99 ? 99 : speed);
    auxdisplay_write(speed_display, buf, strlen(buf));

  } else if (chan == &msg_acc_chan) {
    const struct msg_acc *msg = zbus_chan_const_msg(chan);

    if (!g_ctx.states[ERROR_BATTERY]) {
      snprintf(buf, sizeof(buf), "%2d", msg->soc > 99 ? 99 : msg->soc);
      auxdisplay_write(battery_display, buf, strlen(buf));
    }
  }

  k_mutex_unlock(&g_ctx.lock);
}

static void input_cb(struct input_event *evt, void *user_data) {}

static void err_cb(uint32_t errcode, bool set, void *user_data) {
  struct dashboard_normal_ctx *ctx = user_data;

  static const char *err_str = "Er";
  struct led_rgb rgb[LED_STRIP_LEN];

  k_mutex_lock(&ctx->lock, K_FOREVER);

  switch (errcode) {
    case ERR_CODE_ACCEL:
      ctx->states[ERROR_ACCEL] = set;

      if (ctx->states[ACTIVE] && set) {
        rgb_set_error_pattern(rgb, LED_STRIP_LEN);
        led_strip_update_rgb(accel_display, rgb, LED_STRIP_LEN);
      }

      break;

    case ERR_CODE_BRAKE:
      ctx->states[ERROR_BRAKE] = set;

      if (ctx->states[ACTIVE] && set) {
        rgb_set_error_pattern(rgb, LED_STRIP_LEN);
        led_strip_update_rgb(brake_display, rgb, LED_STRIP_LEN);
      }

      break;

    default:
      /// @todo
      if (ctx->states[ACTIVE] && set) {
        auxdisplay_write(speed_display, err_str, strlen(err_str));
      }

      if (ctx->states[ACTIVE] && set) {
        auxdisplay_write(battery_display, err_str, strlen(err_str));
      }

      break;
  }

  k_mutex_unlock(&ctx->lock);
}
