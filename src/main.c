// glibc includes
#include <stdbool.h>
#include <stdio.h>

// zephyr includes
#include <zephyr/drivers/auxdisplay.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

// nturt includes
#include <nturt/canbus/canopen.h>
#include <nturt/telemetry.h>

// project includes
#include "vcu/telemetry.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main() {
  while (true) {
    k_sleep(K_MSEC(100));
  }

  return 0;
}

static void imu_data_cb(const struct zbus_channel *chan) {
  const struct msg_imu_data *msg = zbus_chan_const_msg(chan);

  printk(
      "IMU data:\n\tTimestamp: %llu ns\n\tAccel: [%.2f, %.2f, %.2f] "
      "m/s^2\n\tGyro: [%.2f, %.2f, %.2f] rad/s\n\tOrient: [%.2f, %.2f, %.2f] "
      "deg\n",
      msg->header.timestamp_ns, (double)msg->accel.x, (double)msg->accel.y,
      (double)msg->accel.z, (double)msg->gyro.x, (double)msg->gyro.y,
      (double)msg->gyro.z, (double)msg->orient.x, (double)msg->orient.y,
      (double)msg->orient.z);

  TM_DATA_UPDATE(inv_rl_target_torque, msg->accel.x);
}

ZBUS_LISTENER_DEFINE(imu_data_listener, imu_data_cb);
ZBUS_CHAN_ADD_OBS(msg_imu_data_chan, imu_data_listener, 0);
