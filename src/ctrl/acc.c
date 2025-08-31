// zephyr includes
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/err/err.h>
#include <nturt/sys/sys.h>

// project includes
#include "vcu/ctrl/params.h"
#include "vcu/msg/msg.h"

LOG_MODULE_REGISTER(vcu_ctrl_acc);

/* macro ---------------------------------------------------------------------*/
#define STATUS_WORD_OK BIT(0)
#define STATUS_WORD_FULL BIT(1)
#define STATUS_WORD_COMM_ERROR BIT(2)

/* type ----------------------------------------------------------------------*/
struct ctrl_acc_ctx {
  struct k_work_delayable comm_error_work;
};

/* static function declaration -----------------------------------------------*/
static void msg_cb(const struct zbus_channel *chan);
static void comm_error_work(struct k_work *work);

/* static variable -----------------------------------------------------------*/
static struct ctrl_acc_ctx g_ctx = {
    .comm_error_work = Z_WORK_DELAYABLE_INITIALIZER(comm_error_work),
};

ZBUS_LISTENER_DEFINE(ctrl_acc_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_ts_acc_chan, ctrl_acc_listener, 0);

ERR_DEFINE(acc, ERR_CODE_ACC, ERR_SEV_FATAL, "Accumulator error");
ERR_DEFINE(acc_comm, ERR_CODE_ACC_COMM, ERR_SEV_ERROR,
           "Accumulator communication error");

/* static function definition ------------------------------------------------*/
static void msg_cb(const struct zbus_channel *chan) {
  const struct msg_ts_acc *msg = zbus_chan_const_msg(chan);

  err_report(ERR_CODE_ACC, (msg->status & STATUS_WORD_OK) == 0);

  if (msg->status & STATUS_WORD_COMM_ERROR) {
    sys_work_schedule(&g_ctx.comm_error_work, K_SECONDS(60));

  } else {
    k_work_cancel_delayable(&g_ctx.comm_error_work);
    err_report(ERR_CODE_ACC_COMM, false);
  }
}

static void comm_error_work(struct k_work *work) {
  err_report(ERR_CODE_ACC_COMM, true);
}
