#include "vcu/msg/msg.h"

// zephyr includes
#include <zephyr/logging/log.h>

// nturt includes
#include <nturt/msg/msg.h>

LOG_MODULE_REGISTER(vcu_msg);

/* static variable -----------------------------------------------------------*/
MSG_CHAN_DEFINE(MSG_VCU_LIST);

// clang-format off

MSG_AGG_TO_MSG_DEFINE(msg_sensor_wheel_agg,
    msg_sensor_wheel, AGG_DATA_INIT(0),
    K_MSEC(10), K_MSEC(8), K_MSEC(3), 0,

    AGG_MEMBER(speed.fl), AGG_MEMBER(speed.fr), AGG_MEMBER(speed.rl), AGG_MEMBER(speed.rr),
    AGG_MEMBER(torque.rl), AGG_MEMBER(torque.rr),
    AGG_MEMBER(susp_travel.fl), AGG_MEMBER(susp_travel.rl)
);

// clang-format on
