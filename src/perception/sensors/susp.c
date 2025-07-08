// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/msg/msg.h>

LOG_MODULE_REGISTER(sensors_susp);

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
