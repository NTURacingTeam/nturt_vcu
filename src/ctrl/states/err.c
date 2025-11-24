// zephyr includes
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/err/err.h>

// project includes
#include "vcu/ctrl/params.h"
#include "vcu/ctrl/states.h"
#include "vcu/msg/msg.h"

/* macro ---------------------------------------------------------------------*/
#ifdef CONFIG_VCU_STATES_TRANS_TO_ERROR_ON_FATAL
#define FILTERED_ERRORS ERR_SEV_FATAL
#elif defined(CONFIG_VCU_STATES_TRANS_TO_ERROR_ON_ERROR)
#define FILTERED_ERRORS ERR_SEV_FATAL, ERR_SEV_ERROR
#elif defined(CONFIG_VCU_STATES_TRANS_TO_ERROR_ON_WARNING)
#define FILTERED_ERRORS ERR_SEV_FATAL, ERR_SEV_ERROR, ERR_SEV_WARNING
#endif

#define ON_SEVERITY (FOR_EACH(IDENTITY, (|), FILTERED_ERRORS))

/* type ----------------------------------------------------------------------*/
struct err_ctx {
  double accel;
};

/* static function declaration -----------------------------------------------*/
static void msg_cb(const struct zbus_channel* chan);
static void err_cb(uint32_t errcode, bool set, void* user_data);

/* static variable -----------------------------------------------------------*/
static struct err_ctx g_ctx = {
    .accel = 0.0,
};

ZBUS_LISTENER_DEFINE(states_err_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_sensor_cockpit_chan, states_err_listener, 0);

ERR_CALLBACK_DEFINE(err_cb, NULL, ERR_FILTER_SEV(FILTERED_ERRORS));

/* static function definition ------------------------------------------------*/
static void msg_cb(const struct zbus_channel* chan) {
  const struct msg_sensor_cockpit* msg = zbus_chan_const_msg(chan);

  g_ctx.accel = msg->accel;

  if (msg->accel > 0.0) {
    return;
  }

  int max_severity = 0;

  struct err* err;
  ERR_FOREACH_SET(err) {
    max_severity = MAX(max_severity, err->flags & ON_SEVERITY);
  }

  if (max_severity == 0 &&
      states_valid_transition(TRANS_CMD_ERROR_CLEARED_RUNNING) &&
      !states_transition_pending()) {
    states_transition(TRANS_CMD_ERROR_CLEARED_RUNNING);
  }
}

static void err_cb(uint32_t errcode, bool set, void* user_data) {
  (void)errcode;
  (void)set;
  (void)user_data;

  /// @todo Fix this, may require architecture overhaul
  if (states_transition_pending()) {
    return;
  }

  int max_severity = 0;

  struct err* err;
  ERR_FOREACH_SET(err) {
    max_severity = MAX(max_severity, err->flags & ON_SEVERITY);
  }

  if (max_severity == ERR_SEV_FATAL) {
    if (states_valid_transition(TRANS_CMD_FATAL_ERROR)) {
      states_transition(TRANS_CMD_FATAL_ERROR);
    }

  } else if (max_severity != 0) {
    if (states_valid_transition(TRANS_CMD_ERROR)) {
      states_transition(TRANS_CMD_ERROR);
    } else if (states_valid_transition(TRANS_CMD_ERROR_RUNNING)) {
      states_transition(TRANS_CMD_ERROR_RUNNING);
    }

  } else {
    if (states_valid_transition(TRANS_CMD_ERROR_CLEARED)) {
      states_transition(TRANS_CMD_ERROR_CLEARED);
    } else if (states_valid_transition(TRANS_CMD_ERROR_CLEARED_RUNNING) && g_ctx.accel == 0.0) {
      states_transition(TRANS_CMD_ERROR_CLEARED_RUNNING);
    }
  }
}
