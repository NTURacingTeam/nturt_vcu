// glibc includes
#include <stddef.h>

// zephyr includes
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/zbus/zbus.h>

// project includes
#include "vcu/ctrl/states.h"
#include "vcu/msg/msg.h"

LOG_MODULE_REGISTER(vcu_ctrl);

/* static function declaration -----------------------------------------------*/
static void msg_cb(const struct zbus_channel *chan);

static void thread(void *arg1, void *arg2, void *arg3);

/* static variable -----------------------------------------------------------*/
ZBUS_LISTENER_DEFINE(ctrl_listener, msg_cb);
ZBUS_CHAN_ADD_OBS(msg_sensor_cockpit_chan, ctrl_listener, 0);

K_THREAD_DEFINE(ctrl_thread, 1024, thread, NULL, NULL, NULL, 0, 0, 0);

/* static function definition ------------------------------------------------*/
static void msg_cb(const struct zbus_channel *chan) {
  if (chan == &msg_sensor_cockpit_chan) {
  }
}

static void thread(void *arg1, void *arg2, void *arg3) {
  (void)arg1;
  (void)arg2;
  (void)arg3;

  while (true) {
    struct msg_sensor_cockpit _msg;
    zbus_chan_read(&msg_sensor_cockpit_chan, &_msg, K_MSEC(5));

    struct msg_ctrl_torque msg;
    msg_header_init(&msg.header);

    for (int i = 0; i < 4; i++) {
      if (states_get() & STATE_RUNNING) {
        msg.torque.values[i] =
            (i % 2 == 0 ? -0.5F : 0.5F) * _msg.accel_pedal_plaus;
      } else {
        msg.torque.values[i] = 0.0F;
      }
    }

    zbus_chan_pub(&msg_ctrl_torque_chan, &msg, K_MSEC(5));
    k_sleep(K_MSEC(10));
  }
}
