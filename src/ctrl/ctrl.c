#include "vcu/ctrl/ctrl.h"

// glibc includes
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// zephyr includes
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/err/err.h>

// project includes
#include "vcu/ctrl/states.h"
#include "vcu/msg/msg.h"

LOG_MODULE_REGISTER(vcu_ctrl);

/* macro ---------------------------------------------------------------------*/
#define INV_TORQ_DEFAULT 50
#define INV_TORQ_SETTINGS_ROOT "inv_torq"

/* type ----------------------------------------------------------------------*/
struct ctrl_ctx {
  struct k_mutex lock;

  uint8_t torq[4];
};

/* static function declaration -----------------------------------------------*/
static int ctrl_settings_load(const char *key, size_t len_rd,
                              settings_read_cb read_cb, void *cb_arg);

static void msg_cb(const struct zbus_channel *chan);

static void thread(void *arg1, void *arg2, void *arg3);

/* static variable -----------------------------------------------------------*/
static struct ctrl_ctx g_ctx = {
    .lock = Z_MUTEX_INITIALIZER(g_ctx.lock),
    .torq = {INV_TORQ_DEFAULT, INV_TORQ_DEFAULT, INV_TORQ_DEFAULT,
             INV_TORQ_DEFAULT},
};

SETTINGS_STATIC_HANDLER_DEFINE(inv_torq, INV_TORQ_SETTINGS_ROOT, NULL,
                               ctrl_settings_load, NULL, NULL);

ZBUS_LISTENER_DEFINE(ctrl_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_sensor_cockpit_chan, ctrl_listener, 0);

K_THREAD_DEFINE(ctrl_thread, 1024, thread, &g_ctx, NULL, NULL, 0, 0, 0);

/* function definition -------------------------------------------------------*/
uint8_t ctrl_inv_torq_fl_get() { return g_ctx.torq[0]; }
uint8_t ctrl_inv_torq_fr_get() { return g_ctx.torq[1]; }
uint8_t ctrl_inv_torq_rl_get() { return g_ctx.torq[2]; }
uint8_t ctrl_inv_torq_rr_get() { return g_ctx.torq[3]; }

void ctrl_inv_torq_fl_set(uint8_t torq) {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.torq[0] = torq;

  k_mutex_unlock(&g_ctx.lock);
}

void ctrl_inv_torq_fr_set(uint8_t torq) {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.torq[1] = torq;

  k_mutex_unlock(&g_ctx.lock);
}

void ctrl_inv_torq_rl_set(uint8_t torq) {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.torq[2] = torq;

  k_mutex_unlock(&g_ctx.lock);
}

void ctrl_inv_torq_rr_set(uint8_t torq) {
  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  g_ctx.torq[3] = torq;

  k_mutex_unlock(&g_ctx.lock);
}

int ctrl_settings_save() {
  int ret;

  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  ret = settings_save_one(INV_TORQ_SETTINGS_ROOT "/fl", &g_ctx.torq[0],
                          sizeof(uint8_t));
  if (ret < 0) {
    goto err;
  }

  ret = settings_save_one(INV_TORQ_SETTINGS_ROOT "/fr", &g_ctx.torq[1],
                          sizeof(uint8_t));
  if (ret < 0) {
    goto err;
  }

  ret = settings_save_one(INV_TORQ_SETTINGS_ROOT "/rl", &g_ctx.torq[2],
                          sizeof(uint8_t));
  if (ret < 0) {
    goto err;
  }

  ret = settings_save_one(INV_TORQ_SETTINGS_ROOT "/rr", &g_ctx.torq[3],
                          sizeof(uint8_t));
  if (ret < 0) {
    goto err;
  }

  goto out;

err:
  LOG_ERR("settings_save failed: %s", strerror(-ret));

out:
  k_mutex_unlock(&g_ctx.lock);
  return ret;
}

/* static function definition ------------------------------------------------*/
static int ctrl_settings_load(const char *key, size_t len,
                              settings_read_cb read_cb, void *cb_arg) {
  const char *next;
  int ret;

  k_mutex_lock(&g_ctx.lock, K_FOREVER);

  uint8_t *target;
  if (settings_name_steq(key, "fl", &next) && !next) {
    target = &g_ctx.torq[0];
  } else if (settings_name_steq(key, "fr", &next) && !next) {
    target = &g_ctx.torq[1];
  } else if (settings_name_steq(key, "rl", &next) && !next) {
    target = &g_ctx.torq[2];
  } else if (settings_name_steq(key, "rr", &next) && !next) {
    target = &g_ctx.torq[3];
  } else {
    ret = -ENOENT;
    goto out;
  }

  if (len != sizeof(uint8_t)) {
    ret = -EINVAL;
    goto out;
  }

  ret = read_cb(cb_arg, &target, len);

out:
  k_mutex_unlock(&g_ctx.lock);
  return ret;
}

static void msg_cb(const struct zbus_channel *chan) {
  if (chan == &msg_sensor_cockpit_chan) {
  }
}

static void thread(void *arg1, void *arg2, void *arg3) {
  struct ctrl_ctx *ctx = arg1;

  (void)arg2;
  (void)arg3;

  while (true) {
    k_sleep(K_MSEC(10));

    struct msg_sensor_cockpit _msg;
    zbus_chan_read(&msg_sensor_cockpit_chan, &_msg, K_MSEC(5));

    struct msg_ctrl_torque msg;
    msg_header_init(&msg.header);

    int ret = k_mutex_lock(&ctx->lock, K_MSEC(5));
    if (ret < 0) {
      LOG_WRN("Failed to lock: %s", strerror(-ret));
      continue;
    }

    for (int i = 0; i < 4; i++) {
      if (states_get() & STATE_RUNNING) {
        msg.torque.values[i] =
            (float)(i % 2 == 0 ? -ctx->torq[i] : ctx->torq[i]) / 100.0F *
            _msg.accel_pedal_plaus;
      } else {
        msg.torque.values[i] = 0.0F;
      }
    }

    zbus_chan_pub(&msg_ctrl_torque_chan, &msg, K_MSEC(5));
  }
}
