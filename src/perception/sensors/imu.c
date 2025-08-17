// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/msg/msg.h>
#include <nturt/sys/sys.h>

LOG_MODULE_REGISTER(vcu_sensor_imu);

/* macro ---------------------------------------------------------------------*/
#define SENSOR_IMU_PERIOD K_MSEC(10)

/* static function declaration -----------------------------------------------*/
static int init();

static void read_work(struct k_work *work);

/* static variable -----------------------------------------------------------*/
static const struct device *imu = DEVICE_DT_GET(DT_CHOSEN(nturt_imu));

static struct k_work_delayable dwork = Z_WORK_DELAYABLE_INITIALIZER(read_work);

SYS_INIT(init, APPLICATION, CONFIG_VCU_SENSORS_INIT_PRIORITY);

/* static function definition ------------------------------------------------*/
static int init() {
  if (!device_is_ready(imu)) {
    LOG_ERR("IMU device not ready");
    return -ENODEV;
  }

  sys_work_schedule(&dwork, SENSOR_IMU_PERIOD);

  return 0;
}

static void read_work(struct k_work *work) {
  (void)work;

  struct msg_sensor_imu msg;
  struct sensor_value val[3];

  int ret = sensor_sample_fetch(imu);
  if (ret < 0) {
    LOG_ERR("Failed to fetch IMU data: %d", ret);
  }

  ret = sensor_channel_get(imu, SENSOR_CHAN_ACCEL_XYZ, &val[0]);
  if (ret < 0) {
    LOG_ERR("Failed to get accelerometer data: %d", ret);
  }

  for (int i = 0; i < 3; i++) {
    msg.accel.values[i] = sensor_value_to_float(&val[i]);
  }

  ret = sensor_channel_get(imu, SENSOR_CHAN_GYRO_XYZ, &val[0]);
  if (ret < 0) {
    LOG_ERR("Failed to get gyroscope data: %d", ret);
  }

  for (int i = 0; i < 3; i++) {
    msg.gyro.values[i] = sensor_value_to_float(&val[i]);
  }

  msg_header_init(&msg.header);
  zbus_chan_pub(&msg_sensor_imu_chan, &msg, K_MSEC(5));

  sys_work_reschedule(&dwork, SENSOR_IMU_PERIOD);
}
