// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/msg/msg.h>

// project includes
#include "vcu/msg/msg.h"

/* static variable -----------------------------------------------------------*/
#ifdef CONFIG_VCU_HAS_POW_IN_VOLT
static const struct device *pow_in_volt =
    DEVICE_DT_GET(DT_CHOSEN(nturt_pow_in_volt));
#endif  // CONFIG_VCU_HAS_POW_IN_VOLT

#ifdef CONFIG_VCU_HAS_POW_5V_CURR
static const struct device *pow_5v_curr =
    DEVICE_DT_GET(DT_CHOSEN(nturt_pow_5v_curr));
#endif  // CONFIG_VCU_HAS_POW_5V_CURR

#ifdef CONFIG_VCU_HAS_POW_5V_RPI_CURR
static const struct device *pow_5v_rpi_curr =
    DEVICE_DT_GET(DT_CHOSEN(nturt_pow_5v_rpi_curr));
#endif  // CONFIG_VCU_HAS_POW_5V_RPI_CURR
