#include "vcu/telemetry.h"

// glibc includes
#include <stdint.h>

// nturt includes
#include <nturt/telemetry.h>

TM_DATA_DEFINE(steer, int16_t, TM_STEER_ANGLE);
TM_DATA_DEFINE(accel, uint8_t, TM_ACCELERATOR);
TM_DATA_DEFINE(apps1, int8_t, TM_APPS1);
TM_DATA_DEFINE(apps2, int8_t, TM_APPS2);
TM_DATA_DEFINE(brake, uint8_t, TM_BRAKE);
TM_DATA_DEFINE(bse1, uint8_t, TM_BSE1);
TM_DATA_DEFINE(bse2, uint8_t, TM_BSE2);

TM_DATA_DEFINE(vcu_states, uint16_t, TM_VCU_STATES);

TM_DATA_DEFINE(susp_travel_fl, int16_t, TM_SUSP_TRAVEL_FL);
TM_DATA_DEFINE(susp_travel_rl, int16_t, TM_SUSP_TRAVEL_RL);

TM_DATA_DEFINE(inv_rl_ctrl_word, uint16_t, TM_INV_RL_CTRL_WORD);
TM_DATA_DEFINE(inv_rl_target_torque, int16_t, TM_INV_RL_TARGET_TORQUE);

TM_DATA_DEFINE(inv_rr_ctrl_word, uint16_t, TM_INV_RR_CTRL_WORD);
TM_DATA_DEFINE(inv_rr_target_torque, int16_t, TM_INV_RR_TARGET_TORQUE);
