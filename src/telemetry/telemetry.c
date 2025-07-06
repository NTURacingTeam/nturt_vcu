#include "vcu/telemetry.h"

// glibc includes
#include <stddef.h>
#include <stdint.h>

// project includes
#include "nturt/telemetry.h"

TM_DATA_DEFINE(inv_rl_ctrl_word, uint16_t, TM_INV_RL_CTRL_WORD);
TM_DATA_DEFINE(inv_rl_target_torque, int16_t, TM_INV_RL_TARGET_TORQUE);

TM_DATA_DEFINE(inv_rr_ctrl_word, uint16_t, TM_INV_RR_CTRL_WORD);
TM_DATA_DEFINE(inv_rr_target_torque, int16_t, TM_INV_RR_TARGET_TORQUE);
