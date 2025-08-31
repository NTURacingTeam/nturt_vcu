#include "vcu/ctrl/ctrl.h"

// glibc includes
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// zephyr includes
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/canbus/convert.h>
#include <nturt/err/err.h>

// project includes
#ifdef CONFIG_VCU_SOURCE_VEHICLE_STATE_FUSION
#include "simulink/sensor_fusion.h"
#endif
#include "simulink/vehicle_control.h"
#include "vcu/ctrl/states.h"
#include "vcu/msg/msg.h"

LOG_MODULE_REGISTER(vcu_ctrl);

/* macro ---------------------------------------------------------------------*/
#define _CTRL_PARAM_DEFINE(param)                                              \
  volatile _CTRL_PARAM_TYPE(param) _CTRL_PARAM_NAME(param) =                   \
      _CTRL_PARAM_DEFAULT(param);                                              \
                                                                               \
  void _CTRL_PARAM_SET(_CTRL_PARAM_NAME(param))(_CTRL_PARAM_TYPE(param) val) { \
    k_mutex_lock(&g_ctx.lock, K_FOREVER);                                      \
                                                                               \
    _CTRL_PARAM_NAME(param) = val;                                             \
                                                                               \
    k_mutex_unlock(&g_ctx.lock);                                               \
  }                                                                            \
                                                                               \
  _CTRL_PARAM_TYPE(param) _CTRL_PARAM_GET(_CTRL_PARAM_NAME(param))() {         \
    return _CTRL_PARAM_NAME(param);                                            \
  }

/**
 * @brief Define control parameters and their getter/setter functions.
 *
 * @param[in] ... Control parameters to define, must be specified by
 * @ref CTRL_PARAM.
 */
#define CTRL_PARAM_DEFINE(list) FOR_EACH(_CTRL_PARAM_DEFINE, (), list)

/* type ----------------------------------------------------------------------*/
enum ctrl_state {
  CTRL_STATE_IDLE,
  CTRL_STATE_OK,
  CTRL_STATE_ERROR,

  NUM_CTRL_STATE,
};

struct ctrl_ctx {
  struct k_mutex lock;

  enum ctrl_state state;

  struct msg_sensor_cockpit cockpit;
  struct msg_sensor_wheel wheel;
  struct msg_sensor_imu imu;
  struct msg_sensor_gps gps;
  struct msg_ctrl_vehicle_state vehicle_state;

  struct msg_ctrl_cmd cmd_last;

#ifdef CONFIG_VCU_SOURCE_VEHICLE_STATE_FUSION
  sensor_fusion_RT_MODEL sensor_fusion_model;
#endif

  vehicle_control_RT_MODEL vehicle_control_model;
};

/* static function declaration -----------------------------------------------*/
static void ctrl_init(struct ctrl_ctx *ctx);

static int init();

static void msg_cb(const struct zbus_channel *chan);
static void states_cb(enum states_state state, bool is_entry, void *user_data);
static void thread(void *arg1, void *arg2, void *arg3);

/* static variable -----------------------------------------------------------*/
static struct ctrl_ctx g_ctx = {
    .lock = Z_MUTEX_INITIALIZER(g_ctx.lock),
    .state = CTRL_STATE_IDLE,
};

SYS_INIT(init, APPLICATION, CONFIG_VCU_CTRL_INIT_PRIORITY);
K_THREAD_DEFINE(ctrl_thread, CONFIG_VCU_CTRL_STACK_SIZE, thread, &g_ctx, NULL,
                NULL, CONFIG_VCU_CTRL_THREAD_PRIORITY, 0, 0);

ZBUS_LISTENER_DEFINE(ctrl_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_sensor_cockpit_chan, ctrl_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_sensor_wheel_chan, ctrl_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_sensor_imu_chan, ctrl_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_sensor_gps_chan, ctrl_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_ctrl_vehicle_state_chan, ctrl_listener, 0);

ZBUS_CHAN_ADD_OBS(msg_ctrl_cmd_chan, ctrl_listener, 0);

ERR_DEFINE(emcy_stop, ERR_CODE_EMCY_STOP, ERR_SEV_FATAL, "Emergency stop");

STATES_CALLBACK_DEFINE(STATE_RUNNING | STATE_RUNNING_OK | STATE_RUNNING_ERROR,
                       states_cb, &g_ctx);

/* function definition -------------------------------------------------------*/
CTRL_PARAM_DEFINE(CTRL_PARAM_LIST);

/* static function definition ------------------------------------------------*/
static void ctrl_init(struct ctrl_ctx *ctx) {
#ifdef CONFIG_VCU_SOURCE_VEHICLE_STATE_FUSION
  sensor_fusion_initialize(&ctx->sensor_fusion_model);
#endif

  // send torque command once to start publishing
  struct msg_ctrl_torque msg = {0};
  msg_header_init(&msg.header);

  zbus_chan_pub(&msg_ctrl_torque_chan, &msg, K_FOREVER);
}

static int init() {
  ctrl_init(&g_ctx);

  return 0;
}

static void thread(void *arg1, void *arg2, void *arg3) {
  struct ctrl_ctx *ctx = arg1;

  (void)arg2;
  (void)arg3;

  while (true) {
    k_sleep(K_MSEC(10));

    int ret = k_mutex_lock(&ctx->lock, K_MSEC(5));
    if (ret < 0) {
      LOG_WRN("Failed to lock: %s", strerror(-ret));
      continue;
    }

#ifdef CONFIG_VCU_SOURCE_VEHICLE_STATE_FUSION

    sensor_fusion_ExtU input = {
        .cockpit = ctx->cockpit,
        .wheel = ctx->wheel,
        .imu = ctx->imu,
        .gps = ctx->gps,
    };
    sensor_fusion_ExtY output;
    sensor_fusion_step(&ctx->sensor_fusion_model, &input, &output);

    struct msg_ctrl_vehicle_state *msg = &output.vehicle_state;
    msg_header_init(&msg->header);

    zbus_chan_pub(&msg_ctrl_vehicle_state_chan, msg, K_MSEC(5));

#endif  // CONFIG_VCU_SOURCE_VEHICLE_STATE_FUSION

    if (ctx->state != CTRL_STATE_IDLE) {
      vehicle_control_ExtU input = {
          .vehicle_state = ctx->vehicle_state,
          .cockpit = ctx->cockpit,
          .wheel = ctx->wheel,
          .imu = ctx->imu,
          .gps = ctx->gps,
      };

      if (ctx->state == CTRL_STATE_ERROR) {
        input.cockpit.accel = 0.0F;
      }

      vehicle_control_ExtY output;
      vehicle_control_step(&ctx->vehicle_control_model, &input, &output);

      struct msg_ctrl_torque *msg = &output.torq;
      if (ctx->state == CTRL_STATE_ERROR) {
        ARRAY_FOR_EACH_PTR(msg->torque.values, val) { *val = 0.0; }
      }
      msg_header_init(&msg->header);

      zbus_chan_pub(&msg_ctrl_torque_chan, msg, K_MSEC(5));
    }

    k_mutex_unlock(&ctx->lock);
  }
}

static void msg_cb(const struct zbus_channel *chan) {
  if (chan == &msg_sensor_cockpit_chan) {
    g_ctx.cockpit =
        *(const struct msg_sensor_cockpit *)zbus_chan_const_msg(chan);
  } else if (chan == &msg_sensor_wheel_chan) {
    g_ctx.wheel = *(const struct msg_sensor_wheel *)zbus_chan_const_msg(chan);
  } else if (chan == &msg_sensor_imu_chan) {
    g_ctx.imu = *(const struct msg_sensor_imu *)zbus_chan_const_msg(chan);
  } else if (chan == &msg_sensor_gps_chan) {
    g_ctx.gps = *(const struct msg_sensor_gps *)zbus_chan_const_msg(chan);
  } else if (chan == &msg_ctrl_cmd_chan) {
    const struct msg_ctrl_cmd *msg = zbus_chan_const_msg(chan);

    if (g_ctx.cmd_last.rtd != msg->rtd && msg->rtd) {
      if (states_valid_transition(TRANS_CMD_RTD_FORCED)) {
        states_transition(TRANS_CMD_RTD_FORCED);
      }
    }

    if (g_ctx.cmd_last.emcy_stop != msg->emcy_stop) {
      err_report(ERR_CODE_EMCY_STOP, msg->emcy_stop);
    }

    g_ctx.cmd_last = *msg;
  }
}

static void states_cb(enum states_state state, bool is_entry, void *user_data) {
  struct ctrl_ctx *ctx = user_data;

  k_mutex_lock(&ctx->lock, K_FOREVER);

  switch (state) {
    case STATE_RUNNING:
      if (is_entry) {
        vehicle_control_initialize(&ctx->vehicle_control_model);

      } else {
        struct msg_ctrl_torque msg = {0};
        msg_header_init(&msg.header);

        zbus_chan_pub(&msg_ctrl_torque_chan, &msg, K_FOREVER);

        ctx->state = CTRL_STATE_IDLE;
      }
      break;

    case STATE_RUNNING_OK:
      if (is_entry) {
        ctx->state = CTRL_STATE_OK;
      }
      break;

    case STATE_RUNNING_ERROR:
      if (is_entry) {
        ctx->state = CTRL_STATE_ERROR;
      }
      break;

    default:
      break;
  }

  k_mutex_unlock(&ctx->lock);
}
