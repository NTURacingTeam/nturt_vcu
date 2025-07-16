#include "vcu/telemetry.h"

// glibc includes
#include <stdint.h>

// zephyr includes
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/canbus/convert.h>
#include <nturt/msg/msg.h>
#include <nturt/telemetry.h>

/* static function declaration -----------------------------------------------*/
static void msg_cb(const struct zbus_channel *chan);

/* static variable -----------------------------------------------------------*/
ZBUS_LISTENER_DEFINE(telemetry_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_cockpit_data_chan, telemetry_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_ctrl_word_chan, telemetry_listener, 0);
ZBUS_CHAN_ADD_OBS(msg_ctrl_torque_chan, telemetry_listener, 0);

/* static function definition ------------------------------------------------*/
static void msg_cb(const struct zbus_channel *chan) {
  if (chan == &msg_cockpit_data_chan) {
    const struct msg_cockpit_data *msg = zbus_chan_const_msg(chan);

    TM_DATA_UPDATE(steer, STEER_PHY_TO_CAN(msg->steer));
    TM_DATA_UPDATE(accel, PEDAL_TRAV_PHY_TO_CAN(msg->accel));
    TM_DATA_UPDATE(apps1, APPS_RAW_PHY_TO_CAN(msg->apps1));
    TM_DATA_UPDATE(apps2, APPS_RAW_PHY_TO_CAN(msg->apps2));
    TM_DATA_UPDATE(brake, PEDAL_TRAV_PHY_TO_CAN(msg->brake));
    TM_DATA_UPDATE(bse1, BSE_RAW_PHY_TO_CAN(msg->bse1));
    TM_DATA_UPDATE(bse2, BSE_RAW_PHY_TO_CAN(msg->bse2));

  } else if (chan == &msg_ctrl_word_chan) {
    const struct msg_ctrl_word *msg = zbus_chan_const_msg(chan);

    TM_DATA_UPDATE(inv_rl_ctrl_word, msg->ctrl.rl);
    TM_DATA_UPDATE(inv_rr_ctrl_word, msg->ctrl.rr);

  } else if (chan == &msg_ctrl_torque_chan) {
    const struct msg_ctrl_torque *msg = zbus_chan_const_msg(chan);

    TM_DATA_UPDATE(inv_rl_target_torque, TORQUE_PHY_TO_CAN(msg->torque.rl));
    TM_DATA_UPDATE(inv_rr_target_torque, TORQUE_PHY_TO_CAN(msg->torque.rr));
  }
}
