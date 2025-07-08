// zephyr includes
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gnss.h>
#include <zephyr/logging/log.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/msg/msg.h>

LOG_MODULE_REGISTER(sensors_gnss);

/* static variable -----------------------------------------------------------*/
static const struct device *gnss = DEVICE_DT_GET(DT_CHOSEN(nturt_gnss));
