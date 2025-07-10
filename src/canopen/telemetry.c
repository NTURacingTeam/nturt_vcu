// glibc includes
#include <stddef.h>

// zephyr includes
#include <zephyr/kernel.h>

// nturt includes
#include <nturt/canbus/canopen.h>

// project includes
#include "vcu/telemetry.h"

// clang-format off

CANOPEN_TM_TO_TPDO_DEFINE(inv_rl,
    K_MSEC(10), K_MSEC(8), K_MSEC(3),
    TPDO_DATA(inv_rl_ctrl_word, 0x2130, 0x0, AGG_FLAG_OPTIONAL),
    TPDO_DATA(inv_rl_target_torque, 0x2132, 0x0)
);

CANOPEN_TM_TO_TPDO_DEFINE(inv_rr,
    K_MSEC(10), K_MSEC(8), K_MSEC(3),
    TPDO_DATA(inv_rr_ctrl_word, 0x2140, 0x0, AGG_FLAG_OPTIONAL),
    TPDO_DATA(inv_rr_target_torque, 0x2142, 0x0)
);

// clang-format on
