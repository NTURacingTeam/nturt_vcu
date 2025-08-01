/**
 * @file
 * @brief Telemetry support.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-07-05
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef VCU_TELEMETRY_H_
#define VCU_TELEMETRY_H_

// glibc includes
#include <stdint.h>

// nturt includes
#include <nturt/telemetry.h>

/**
 * @defgroup tm_vcu VCU Telemetry
 * @brief VCU telemetry support.
 *
 * @ingroup tm
 * @{
 */

/* type ----------------------------------------------------------------------*/
/// @brief Telemetry data address for VCU. Currently the addresses are not used
/// and can be changed to match those used in future protocols.
enum vcu_td_data_addr {
  TM_STEER_ANGLE,
  TM_ACCELERATOR,
  TM_APPS1,
  TM_APPS2,
  TM_BRAKE,
  TM_BSE1,
  TM_BSE2,

  TM_INV_RL_CTRL_WORD,
  TM_INV_RL_TARGET_TORQUE,

  TM_INV_RR_CTRL_WORD,
  TM_INV_RR_TARGET_TORQUE,
};

TM_DATA_DECLARE(steer, int16_t);
TM_DATA_DECLARE(accel, uint8_t);
TM_DATA_DECLARE(apps1, int8_t);
TM_DATA_DECLARE(apps2, int8_t);
TM_DATA_DECLARE(brake, uint8_t);
TM_DATA_DECLARE(bse1, uint8_t);
TM_DATA_DECLARE(bse2, uint8_t);

TM_DATA_DECLARE(inv_rl_ctrl_word, uint16_t);
TM_DATA_DECLARE(inv_rl_target_torque, int16_t);

TM_DATA_DECLARE(inv_rr_ctrl_word, uint16_t);
TM_DATA_DECLARE(inv_rr_target_torque, int16_t);

/**
 * @} // tm_vcu
 */

#endif  // VCU_TELEMETRY_H_
