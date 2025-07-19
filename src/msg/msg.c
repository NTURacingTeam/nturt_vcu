#include "vcu/msg/msg.h"

// zephyr includes
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

// nturt includes
#include <nturt/msg/msg.h>

LOG_MODULE_REGISTER(vcu_msg);

/* static variable -----------------------------------------------------------*/
MSG_ZBUS_CHAN_DEFINE(MSG_VCU_LIST);
MSG_SHELL_DEFINE(MSG_VCU_LIST);
