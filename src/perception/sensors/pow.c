#include "sensor.h"

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/msg/msg.h>

// project includes
#include "vcu/msg/msg.h"

LOG_MODULE_REGISTER(vcu_sensor_pow);

/* static function declaration -----------------------------------------------*/
static int init();

static void read_work(struct k_work *work);

/* static variable -----------------------------------------------------------*/
#ifdef CONFIG_VCU_HAS_POW_IN_VOLT
static const struct device *pow_in_volt =
    DEVICE_DT_GET(DT_CHOSEN(nturt_pow_in_volt));
#endif

#ifdef CONFIG_VCU_HAS_POW_5V_CURR
static const struct device *pow_5v_curr =
    DEVICE_DT_GET(DT_CHOSEN(nturt_pow_5v_curr));
#endif

#ifdef CONFIG_VCU_HAS_POW_5V_RPI_CURR
static const struct device *pow_5v_rpi_curr =
    DEVICE_DT_GET(DT_CHOSEN(nturt_pow_5v_rpi_curr));
#endif

static struct k_work_delayable dwork = Z_WORK_DELAYABLE_INITIALIZER(read_work);

SYS_INIT(init, APPLICATION, CONFIG_VCU_SENSORS_INIT_PRIORITY);

/* static function definition ------------------------------------------------*/
static int init() {
#ifdef CONFIG_VCU_HAS_POW_IN_VOLT
  if (!device_is_ready(pow_in_volt)) {
    LOG_ERR("Power input voltage device not ready");
    return -ENODEV;
  }
#endif

#ifdef CONFIG_VCU_HAS_POW_5V_CURR
  if (!device_is_ready(pow_5v_curr)) {
    LOG_ERR("Power 5V current device not ready");
    return -ENODEV;
  }
#endif

#ifdef CONFIG_VCU_HAS_POW_5V_RPI_CURR
  if (!device_is_ready(pow_5v_rpi_curr)) {
    LOG_ERR("Power 5V Raspberry Pi current device not ready");
    return -ENODEV;
  }
#endif

  k_work_schedule_for_queue(sensor_work_q, &dwork, SENSOR_POW_PERIOD);

  return 0;
}

static void read_work(struct k_work *work) {
  (void)work;

  struct msg_sensor_pow msg;

  int ret;
  struct sensor_value val;

#ifdef CONFIG_VCU_HAS_POW_IN_VOLT
  ret = sensor_sample_fetch(pow_in_volt);
  if (ret < 0) {
    LOG_ERR("Failed to fetch power input voltage: %d", ret);
  }

  ret = sensor_channel_get(pow_in_volt, SENSOR_CHAN_VOLTAGE, &val);
  if (ret < 0) {
    LOG_ERR("Failed to get power input voltage: %d", ret);
  }

  msg.in_volt = sensor_value_to_float(&val);
#endif

#ifdef CONFIG_VCU_HAS_POW_5V_CURR
  ret = sensor_sample_fetch(pow_5v_curr);
  if (ret < 0) {
    LOG_ERR("Failed to fetch power 5V current: %d", ret);
  }

  ret = sensor_channel_get(pow_5v_curr, SENSOR_CHAN_CURRENT, &val);
  if (ret < 0) {
    LOG_ERR("Failed to get power 5V current: %d", ret);
  }

  msg.v5_curr = sensor_value_to_float(&val);
#endif

#ifdef CONFIG_VCU_HAS_POW_5V_RPI_CURR
  ret = sensor_sample_fetch(pow_5v_rpi_curr);
  if (ret < 0) {
    LOG_ERR("Failed to fetch power 5V Raspberry Pi current: %d", ret);
  }

  ret = sensor_channel_get(pow_5v_rpi_curr, SENSOR_CHAN_CURRENT, &val);
  if (ret < 0) {
    LOG_ERR("Failed to get power 5V Raspberry Pi current: %d", ret);
  }

  msg.v5_rpi_curr = sensor_value_to_float(&val);
#endif

  msg_header_init(&msg.header);
  zbus_chan_pub(&msg_sensor_pow_chan, &msg, K_MSEC(5));

  k_work_reschedule_for_queue(sensor_work_q, &dwork, SENSOR_POW_PERIOD);
}
