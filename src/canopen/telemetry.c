// glibc includes
#include <stddef.h>

// zephyr includes
#include <zephyr/kernel.h>

// nturt includes
#include <nturt/canbus/canopen.h>

// project includes
#include "vcu/telemetry.h"

// clang-format off

CANOPEN_TM_TO_TPDO_DEFINE(states,
    K_MSEC(100), K_MSEC(80), K_MSEC(10), 0,
    TPDO_DATA(vcu_states, 0x2000, 0x0)
);

CANOPEN_TM_TO_TPDO_DEFINE(inv_rl,
    K_MSEC(10), K_MSEC(8), K_MSEC(1), AGG_FLAG_ALWAYS_PUBLISH,
    TPDO_DATA(inv_rl_ctrl_word, 0x2130, 0x0, AGG_MEMBER_FLAG_OPTIONAL),
    TPDO_DATA(inv_rl_target_torque, 0x2132, 0x0)
);

CANOPEN_TM_TO_TPDO_DEFINE(inv_rr,
    K_MSEC(10), K_MSEC(8), K_MSEC(1), AGG_FLAG_ALWAYS_PUBLISH,
    TPDO_DATA(inv_rr_ctrl_word, 0x2140, 0x0, AGG_MEMBER_FLAG_OPTIONAL),
    TPDO_DATA(inv_rr_target_torque, 0x2142, 0x0)
);

#ifndef CONFIG_VCU_SOURCE_COCKPIT_CANOPEN

CANOPEN_TM_TO_TPDO_DEFINE(cockpit,
    K_MSEC(10), K_MSEC(8), K_MSEC(1), 0,
    TPDO_DATA(steer, 0x2080, 0x0),
    TPDO_DATA(accel, 0x2081, 0x1),
    TPDO_DATA(apps1, 0x2081, 0x2),
    TPDO_DATA(apps2, 0x2081, 0x3),
    TPDO_DATA(brake, 0x2082, 0x1),
    TPDO_DATA(bse1, 0x2082, 0x2),
    TPDO_DATA(bse2, 0x2082, 0x3)
);

#endif // CONFIG_VCU_VCU_SOURCE_COCKPIT_CANOPEN

// clang-format on
