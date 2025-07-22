// glibc includes
#include <stdbool.h>
#include <string.h>

// zephyr includes
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/err/err.h>

// project includes
#include "vcu/ctrl/states.h"
#include "vcu/msg/msg.h"

LOG_MODULE_REGISTER(vcu_ctrl_inv);

/* macro ---------------------------------------------------------------------*/
#define STATUS_WORD_READY BIT(1)
#define STATUS_WORD_ENABLED BIT(2)
#define STATUS_WORD_FAULT BIT(3)
#define STATUS_WORD_POWER BIT(4)

#define CTRL_WORD_ENABLE BIT(3)
#define CTRL_WORD_FAULT_RESET BIT(5)

#define CTRL_RESET_BIT_HOLD_TIME K_MSEC(100)

/* type ----------------------------------------------------------------------*/
struct ctrl_inv_ctx {
  struct k_work_delayable fault_reset_work;

  struct k_mutex lock;

  struct msg_ctrl_word msg;
};

/* static function declaration -----------------------------------------------*/
static void ctrl_inv_word_set_and_pub(struct ctrl_inv_ctx *ctx, uint16_t flags,
                                      bool is_set);

static void msg_cb(const struct zbus_channel *chan);
static void err_cb(uint32_t errcode, bool set, void *user_data);
static void states_cb(enum states_state state, bool is_entry, void *user_data);
static void fault_reset_work(struct k_work *work);

/* static variable -----------------------------------------------------------*/
static struct ctrl_inv_ctx g_ctx = {
    .fault_reset_work = Z_WORK_DELAYABLE_INITIALIZER(fault_reset_work),
    .lock = Z_MUTEX_INITIALIZER(g_ctx.lock),
};

ZBUS_LISTENER_DEFINE(ctrl_inv_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_ts_inv_chan, ctrl_inv_listener, 0);

ERR_DEFINE(inv_fl, ERR_CODE_INV_FL, ERR_SEV_FATAL, "Inverter FL error");
ERR_DEFINE(inv_fr, ERR_CODE_INV_FR, ERR_SEV_FATAL, "Inverter FR error");
ERR_DEFINE(inv_rl, ERR_CODE_INV_RL, ERR_SEV_FATAL, "Inverter RL error");
ERR_DEFINE(inv_rr, ERR_CODE_INV_RR, ERR_SEV_FATAL, "Inverter RR error");

ERR_DEFINE(inv_fl_no_power, ERR_CODE_INV_FL_HV_LOW, ERR_SEV_WARN,
           "Inverter FL HV low voltage");
ERR_DEFINE(inv_fr_no_power, ERR_CODE_INV_FR_HV_LOW, ERR_SEV_WARN,
           "Inverter FR HV low voltage");
ERR_DEFINE(inv_rl_no_power, ERR_CODE_INV_RL_HV_LOW, ERR_SEV_WARN,
           "Inverter RL HV low voltage");
ERR_DEFINE(inv_rr_no_power, ERR_CODE_INV_RR_HV_LOW, ERR_SEV_WARN,
           "Inverter RR HV low voltage");

ERR_CALLBACK_DEFINE(err_cb, NULL,
                    ERR_FILTER_CODE(ERR_CODE_INV_FL_HV_LOW, ERR_CODE_INV_FR_HV_LOW,
                                    ERR_CODE_INV_RL_HV_LOW,
                                    ERR_CODE_INV_RR_HV_LOW));

STATES_CALLBACK_DEFINE(STATE_RUNNING, states_cb, &g_ctx);

/* function definition -------------------------------------------------------*/
int ctrl_inv_fault_reset() {
  if (states_get() & STATE_RUNNING) {
    LOG_ERR("Cannot reset inverter fault while running");
    return -EBUSY;
  }

  ctrl_inv_word_set_and_pub(&g_ctx, CTRL_WORD_FAULT_RESET, true);

  k_work_reschedule(&g_ctx.fault_reset_work, CTRL_RESET_BIT_HOLD_TIME);

  return 0;
}

/* static function definition ------------------------------------------------*/
static void ctrl_inv_word_set_and_pub(struct ctrl_inv_ctx *ctx, uint16_t flags,
                                      bool is_set) {
  k_mutex_lock(&ctx->lock, K_FOREVER);

  for (int i = 0; i < 4; i++) {
    if (is_set) {
      ctx->msg.ctrl.values[i] |= flags;
    } else {
      ctx->msg.ctrl.values[i] &= ~flags;
    }
  }

  msg_header_init(&ctx->msg.header);

  int ret = zbus_chan_pub(&msg_ctrl_word_chan, &ctx->msg, K_MSEC(5));
  if (ret < 0) {
    LOG_ERR("Failed to publish control word message: %s", strerror(-ret));
  }

  k_mutex_unlock(&ctx->lock);
}

static void msg_cb(const struct zbus_channel *chan) {
  const struct msg_ts_inv *msg = zbus_chan_const_msg(chan);

  for (int i = 2; i < 4; i++) {
    if (!err_is_set(ERR_CODE_HB_INV_FL + i)) {
      err_report(ERR_CODE_INV_FL + i,
                 msg->status.values[i] & STATUS_WORD_FAULT);
      err_report(ERR_CODE_INV_FL_HV_LOW + i,
                 !(msg->status.values[i] & STATUS_WORD_POWER));
    }
  }
}

static void err_cb(uint32_t errcode, bool set, void *user_data) {
  (void)user_data;

  if (set && states_get() & STATE_RUNNING) {
    LOG_INF("Disable due to inverter no power");
    states_transition(TRANS_CMD_DISABLE);
  }
}

static void states_cb(enum states_state state, bool is_entry, void *user_data) {
  (void)state;

  struct ctrl_inv_ctx *ctx = user_data;

  ctrl_inv_word_set_and_pub(ctx, CTRL_WORD_ENABLE, is_entry);
}

static void fault_reset_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct ctrl_inv_ctx *ctx =
      CONTAINER_OF(dwork, struct ctrl_inv_ctx, fault_reset_work);

  ctrl_inv_word_set_and_pub(ctx, CTRL_WORD_FAULT_RESET, false);
}
