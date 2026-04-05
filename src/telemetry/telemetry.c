#include "vcu/telemetry.h"

// glibc includes
#include <stdint.h>

// nturt includes
#include <nturt/telemetry.h>

// cockpit
TM_DATA_DEFINE(steer, int16_t, TM_STEER_ANGLE);
TM_DATA_DEFINE(accel, uint8_t, TM_ACCELERATOR);
TM_DATA_DEFINE(apps1, int8_t, TM_APPS1);
TM_DATA_DEFINE(apps2, int8_t, TM_APPS2);
TM_DATA_DEFINE(brake, uint8_t, TM_BRAKE);
TM_DATA_DEFINE(bse1, uint8_t, TM_BSE1);
TM_DATA_DEFINE(bse2, uint8_t, TM_BSE2);

// sensors
TM_DATA_DEFINE(susp_travel_fl, int16_t, TM_SUSP_TRAVEL_FL);
TM_DATA_DEFINE(susp_travel_fr, int16_t, TM_SUSP_TRAVEL_FR);
TM_DATA_DEFINE(susp_travel_rl, int16_t, TM_SUSP_TRAVEL_RL);
TM_DATA_DEFINE(susp_travel_rr, int16_t, TM_SUSP_TRAVEL_RR);

// states
TM_DATA_DEFINE(vcu_states, uint16_t, TM_VCU_STATES);
TM_DATA_DEFINE(velocity_x, uint16_t, TM_VELOCITY_X);

// control
TM_DATA_DEFINE(slip_ratio_l, int16_t, TM_SLIP_RATIO_L);
TM_DATA_DEFINE(slip_ratio_r, int16_t, TM_SLIP_RATIO_R);
TM_DATA_DEFINE(yaw_rate, int16_t, TM_YAW_RATE);
TM_DATA_DEFINE(yaw_rate_reference, int16_t, TM_YAW_RATE_REFERENCE);

// inverter
TM_DATA_DEFINE(inv_rl_ctrl_word, uint16_t, TM_INV_RL_CTRL_WORD);
TM_DATA_DEFINE(inv_rl_target_torque, int16_t, TM_INV_RL_TARGET_TORQUE);

TM_DATA_DEFINE(inv_rr_ctrl_word, uint16_t, TM_INV_RR_CTRL_WORD);
TM_DATA_DEFINE(inv_rr_target_torque, int16_t, TM_INV_RR_TARGET_TORQUE);
