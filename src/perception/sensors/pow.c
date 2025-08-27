// glibc includes
#include <string.h>

// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/msg/msg.h>
#include <nturt/sys/sys.h>

// project includes
#include "vcu/msg/msg.h"

LOG_MODULE_REGISTER(vcu_sensor_pow);

/* macro ---------------------------------------------------------------------*/
#define SENSOR_POW_PERIOD K_MSEC(100)

/* type ----------------------------------------------------------------------*/
struct sensor_pow_ctx {
  struct k_work_delayable read_dwork;
  struct gpio_callback gpio_cb;
  struct k_work shutdown_work;
};

/* static function declaration -----------------------------------------------*/
static void gpio_cb(const struct device *dev, struct gpio_callback *cb,
                    uint32_t pins);

static int init();

static void read_work(struct k_work *work);
static void shutdown_work(struct k_work *work);

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

#ifdef CONFIG_VCU_HAS_POW_LOW

static const struct gpio_dt_spec pow_low =
    GPIO_DT_SPEC_GET(DT_CHOSEN(nturt_pow_low), gpios);

static void gpio_cb(const struct device *dev, struct gpio_callback *cb,
                    uint32_t pins) {
  (void)dev;
  (void)pins;

  struct sensor_pow_ctx *ctx = CONTAINER_OF(cb, struct sensor_pow_ctx, gpio_cb);

  k_work_submit(&ctx->shutdown_work);
}

#endif  // CONFIG_VCU_HAS_POW_LOW

static struct sensor_pow_ctx g_ctx = {
    .read_dwork = Z_WORK_DELAYABLE_INITIALIZER(read_work),
    .shutdown_work = Z_WORK_INITIALIZER(shutdown_work),
};

SYS_INIT(init, APPLICATION, CONFIG_VCU_SENSORS_INIT_PRIORITY);

/* static function definition ------------------------------------------------*/
static int init() {
  int ret;
  (void)ret;

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

#ifdef CONFIG_VCU_HAS_POW_LOW
  if (!device_is_ready(pow_low.port)) {
    LOG_ERR("Power low trigger pin port not ready");
    return -ENODEV;
  }

  ret = gpio_pin_configure_dt(&pow_low, GPIO_INPUT);
  if (ret < 0) {
    LOG_ERR("Failed to configure power low trigger pin: %d", ret);
    return ret;
  }

  gpio_init_callback(&g_ctx.gpio_cb, gpio_cb, BIT(pow_low.pin));

  ret = gpio_add_callback(pow_low.port, &g_ctx.gpio_cb);
  if (ret < 0) {
    LOG_ERR("Failed to add gpio callback: %s", strerror(-ret));
    return ret;
  }

  ret = gpio_pin_interrupt_configure_dt(&pow_low, GPIO_INT_EDGE_TO_ACTIVE);
  if (ret < 0) {
    LOG_ERR("Failed to configure power low trigger pin interrupt: %s",
            strerror(-ret));
    return ret;
  }

#endif

  sys_work_schedule(&g_ctx.read_dwork, SENSOR_POW_PERIOD);

  return 0;
}

static void read_work(struct k_work *work) {
  struct k_work_delayable *dwork = k_work_delayable_from_work(work);
  struct sensor_pow_ctx *ctx =
      CONTAINER_OF(dwork, struct sensor_pow_ctx, read_dwork);

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

  sys_work_reschedule(&ctx->read_dwork, SENSOR_POW_PERIOD);
}

static void shutdown_work(struct k_work *work) {
  (void)work;

  sys_shutdown();
}
