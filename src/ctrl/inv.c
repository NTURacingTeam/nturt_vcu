// glibc includes
#include <stdbool.h>
#include <string.h>

// zephyr includes
#include <zephyr/drivers/can.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/err/err.h>
#include <nturt/sys/sys.h>

// project includes
#include "vcu/ctrl/params.h"
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
#define CTRL_SET_PARAM_INTERVAL K_MSEC(100)

/* type ----------------------------------------------------------------------*/
struct ctrl_inv_ctx {
  struct k_work_delayable fault_reset_work;

  struct k_work_delayable set_param_work;

  int set_param_count;

  struct k_mutex lock;

  struct msg_ctrl_word msg;
};

/* static function declaration -----------------------------------------------*/
static void ctrl_inv_word_set_and_pub(struct ctrl_inv_ctx *ctx, uint16_t flags,
                                      bool is_set);

static int init();

static void msg_cb(const struct zbus_channel *chan);
static void err_cb(uint32_t errcode, bool set, void *user_data);
static void states_cb(enum states_state state, bool is_entry, void *user_data);
static void fault_reset_work(struct k_work *work);
static void set_param_work(struct k_work *work);

/* static variable -----------------------------------------------------------*/
static const struct device *can_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_canbus));

static struct ctrl_inv_ctx g_ctx = {
    .fault_reset_work = Z_WORK_DELAYABLE_INITIALIZER(fault_reset_work),
    .set_param_work = Z_WORK_DELAYABLE_INITIALIZER(set_param_work),
    .set_param_count = 0,
    .lock = Z_MUTEX_INITIALIZER(g_ctx.lock),
};

SYS_INIT(init, APPLICATION, CONFIG_VCU_CTRL_INIT_PRIORITY);

ZBUS_LISTENER_DEFINE(ctrl_inv_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_ts_inv_chan, ctrl_inv_listener, 0);

ERR_DEFINE(inv_fl, ERR_CODE_INV_FL, ERR_SEV_ERROR, "Inverter FL error");
ERR_DEFINE(inv_fr, ERR_CODE_INV_FR, ERR_SEV_ERROR, "Inverter FR error");
ERR_DEFINE(inv_rl, ERR_CODE_INV_RL, ERR_SEV_ERROR, "Inverter RL error");
ERR_DEFINE(inv_rr, ERR_CODE_INV_RR, ERR_SEV_ERROR, "Inverter RR error");

ERR_DEFINE(inv_fl_no_power, ERR_CODE_INV_FL_HV_LOW, ERR_SEV_FATAL,
           "Inverter FL HV low voltage");
ERR_DEFINE(inv_fr_no_power, ERR_CODE_INV_FR_HV_LOW, ERR_SEV_FATAL,
           "Inverter FR HV low voltage");
ERR_DEFINE(inv_rl_no_power, ERR_CODE_INV_RL_HV_LOW, ERR_SEV_FATAL,
           "Inverter RL HV low voltage");
ERR_DEFINE(inv_rr_no_power, ERR_CODE_INV_RR_HV_LOW, ERR_SEV_FATAL,
           "Inverter RR HV low voltage");

ERR_CALLBACK_DEFINE(err_cb, NULL,
                    ERR_FILTER_SEV(ERR_CODE_INV_FL, ERR_CODE_INV_FR,
                                   ERR_CODE_INV_RL, ERR_CODE_INV_RR));

STATES_CALLBACK_DEFINE(STATE_RUNNING_OK, states_cb, &g_ctx);

/* function definition -------------------------------------------------------*/
int ctrl_inv_fault_reset() {
  // if (states_get() & STATE_RUNNING) {
  //   LOG_ERR("Cannot reset inverter fault while running");
  //   return -EBUSY;
  // }

  ctrl_inv_word_set_and_pub(&g_ctx, CTRL_WORD_FAULT_RESET, true);

  sys_work_reschedule(&g_ctx.fault_reset_work, CTRL_RESET_BIT_HOLD_TIME);

  return 0;
}

/* static function definition ------------------------------------------------*/
static int init() {
  sys_work_schedule(&g_ctx.set_param_work, CTRL_SET_PARAM_INTERVAL);

  return 0;
}

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
  (void)errcode;
  (void)set;
  (void)user_data;

  ctrl_inv_fault_reset();
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

static void set_param_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct ctrl_inv_ctx *ctx =
      CONTAINER_OF(dwork, struct ctrl_inv_ctx, set_param_work);

  struct can_frame frame = {
      .id = 0x200,
      .dlc = 5,
      .flags = 0,
  };

  switch (ctx->set_param_count) {
    case 0:
      // 3.0
      memcpy(&frame.data[0], (uint8_t[]){0x02, 0x00, 0x00, 0xF0, 0x41}, 5);
      break;
    case 1:
      // 3.0
      memcpy(&frame.data[0], (uint8_t[]){0x12, 0x00, 0x00, 0xF0, 0x41}, 5);
      break;
    case 2:
      // 4.8 0x4099999a
      memcpy(&frame.data[0], (uint8_t[]){0x01, 0x9A, 0x99, 0x99, 0x40}, 5);
      break;
    case 3:
      // 3.84 0x4075c28f
      memcpy(&frame.data[0], (uint8_t[]){0x11, 0x8F, 0xC2, 0x75, 0x40}, 5);
      break;
    default:
      break;
  }

  int ret = can_send(can_dev, &frame, K_MSEC(200), NULL, NULL);
  if (ret < 0) {
    LOG_ERR("Failed to send CAN frame to set inverter parameter: %s",
            strerror(-ret));
  }

  ctx->set_param_count = (ctx->set_param_count + 1) % 4;

  sys_work_reschedule(&ctx->set_param_work, CTRL_SET_PARAM_INTERVAL);
}
