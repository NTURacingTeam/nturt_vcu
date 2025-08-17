// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/msg/aggregation.h>
#include <nturt/sys/sys.h>

// project includes
#include "vcu/msg/msg.h"

LOG_MODULE_REGISTER(vcu_sensor_susp);

/* macro ---------------------------------------------------------------------*/
#define SENSOR_SUSP_PERIOD K_MSEC(10)

/* static function declaration -----------------------------------------------*/
static int init();

static void read_work(struct k_work *work);

/* static variable -----------------------------------------------------------*/
#ifdef CONFIG_VCU_HAS_SUSP_FL
static const struct device *susp_fl = DEVICE_DT_GET(DT_CHOSEN(nturt_susp_fl));
#endif  // CONFIG_VCU_HAS_SUSP_FL

#ifdef CONFIG_VCU_HAS_SUSP_FR
static const struct device *susp_fr = DEVICE_DT_GET(DT_CHOSEN(nturt_susp_fr));
#endif  // CONFIG_VCU_HAS_SUSP_FR

#ifdef CONFIG_VCU_HAS_SUSP_RL
static const struct device *susp_rl = DEVICE_DT_GET(DT_CHOSEN(nturt_susp_rl));
#endif  // CONFIG_VCU_HAS_SUSP_RL

#ifdef CONFIG_VCU_HAS_SUSP_RR
static const struct device *susp_rr = DEVICE_DT_GET(DT_CHOSEN(nturt_susp_rr));
#endif  // CONFIG_VCU_HAS_SUSP_RR

static struct k_work_delayable dwork = Z_WORK_DELAYABLE_INITIALIZER(read_work);

SYS_INIT(init, APPLICATION, CONFIG_VCU_SENSORS_INIT_PRIORITY);

/* static function definition ------------------------------------------------*/
static int init() {
#ifdef CONFIG_VCU_HAS_SUSP_FL
  if (!device_is_ready(susp_fl)) {
    LOG_ERR("Suspension front left device not ready");
    return -ENODEV;
  }
#endif  // CONFIG_VCU_HAS_SUSP_FL

#ifdef CONFIG_VCU_HAS_SUSP_FR
  if (!device_is_ready(susp_fr)) {
    LOG_ERR("Suspension front right device not ready");
    return -ENODEV;
  }
#endif  // CONFIG_VCU_HAS_SUSP_FR

#ifdef CONFIG_VCU_HAS_SUSP_RL
  if (!device_is_ready(susp_rl)) {
    LOG_ERR("Suspension rear left device not ready");
    return -ENODEV;
  }
#endif  // CONFIG_VCU_HAS_SUSP_RL

#ifdef CONFIG_VCU_HAS_SUSP_RR
  if (!device_is_ready(susp_rr)) {
    LOG_ERR("Suspension rear right device not ready");
    return -ENODEV;
  }
#endif  // CONFIG_VCU_HAS_SUSP_RR

  sys_work_schedule(&dwork, SENSOR_SUSP_PERIOD);

  return 0;
}

static void read_work(struct k_work *work) {
  (void)work;

  int ret;
  struct sensor_value val;

#ifdef CONFIG_VCU_HAS_SUSP_FL
  ret = sensor_sample_fetch(susp_fl);
  if (ret < 0) {
    LOG_ERR("Failed to fetch suspension front left data: %d", ret);
  }

  ret = sensor_channel_get(susp_fl, SENSOR_CHAN_DISTANCE, &val);
  if (ret < 0) {
    LOG_ERR("Failed to get suspension front left travel data: %d", ret);
  }

  AGG_TYPED_UPDATE(&msg_sensor_wheel_agg, struct msg_sensor_wheel,
                   susp_travel.fl, sensor_value_to_float(&val));
#endif  // CONFIG_VCU_HAS_SUSP_FL

#ifdef CONFIG_VCU_HAS_SUSP_FR
  ret = sensor_sample_fetch(susp_fr);
  if (ret < 0) {
    LOG_ERR("Failed to fetch suspension front right data: %d", ret);
  }

  ret = sensor_channel_get(susp_fr, SENSOR_CHAN_DISTANCE, &val);
  if (ret < 0) {
    LOG_ERR("Failed to get suspension front right travel data: %d", ret);
  }

  AGG_TYPED_UPDATE(&msg_sensor_wheel_agg, struct msg_sensor_wheel,
                   susp_travel.fr, sensor_value_to_float(&val));
#endif  // CONFIG_VCU_HAS_SUSP_FR

#ifdef CONFIG_VCU_HAS_SUSP_RL
  ret = sensor_sample_fetch(susp_rl);
  if (ret < 0) {
    LOG_ERR("Failed to fetch suspension rear left data: %d", ret);
  }

  ret = sensor_channel_get(susp_rl, SENSOR_CHAN_DISTANCE, &val);
  if (ret < 0) {
    LOG_ERR("Failed to get suspension rear left travel data: %d", ret);
  }

  AGG_TYPED_UPDATE(&msg_sensor_wheel_agg, struct msg_sensor_wheel,
                   susp_travel.rl, sensor_value_to_float(&val));
#endif  // CONFIG_VCU_HAS_SUSP_RL

#ifdef CONFIG_VCU_HAS_SUSP_RR
  ret = sensor_sample_fetch(susp_rr);
  if (ret < 0) {
    LOG_ERR("Failed to fetch suspension rear right data: %d", ret);
  }

  ret = sensor_channel_get(susp_rr, SENSOR_CHAN_DISTANCE, &val);
  if (ret < 0) {
    LOG_ERR("Failed to get suspension rear right travel data: %d", ret);
  }

  AGG_TYPED_UPDATE(&msg_sensor_wheel_agg, struct msg_sensor_wheel,
                   susp_travel.rr, sensor_value_to_float(&val));
#endif  // CONFIG_VCU_HAS_SUSP_RR

  sys_work_reschedule(&dwork, SENSOR_SUSP_PERIOD);
}
