/**
 * @file
 * @brief VCU CAN bus data conversion macros.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-08-24
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef VCU_CANBUS_CONVERT_H_
#define VCU_CANBUS_CONVERT_H_

// glibc includes
#include <stdint.h>

/**
 * @defgroup can_convert_vcu VCU CAN bus data conversion.
 * @brief VCU CAN bus data conversion macros.
 *
 * @ingroup can_convert
 * @{
 */

// nturt includes
#include <nturt/canbus/convert.h>

// project includes
#include "vcu/ctrl/params.h"

/* Physical to CAN -----------------------------------------------------------*/
/// @brief Left inverter torque physical data in Nm (float), convert to 0.001
/// rated torque (int16_t).
#define INV_TORQUE_PHY_TO_CAN_L(phy) \
  INV_TORQ_PHY_TO_CAN(PARAM_MOTOR_DIR_L*(phy / PARAM_MOTOR_RATED_TORQUE))

/// @brief Right inverter torque physical data in Nm (float), convert to 0.001
/// rated torque (int16_t).
#define INV_TORQUE_PHY_TO_CAN_R(phy) \
  INV_TORQ_PHY_TO_CAN(PARAM_MOTOR_DIR_R*(phy / PARAM_MOTOR_RATED_TORQUE))

/* CAN to physical -----------------------------------------------------------*/
/// @brief Left inverter speed CAN data in RPM (int16_t), convert to wheel speed
/// in RPM (float) after reduction.
#define INV_SPEED_CAN_TO_WHEEL_PHY_L(can)                 \
  (PARAM_MOTOR_DIR_L * ANGULAR_VELOCITY_CAN_TO_PHY(can) / \
   PARAM_MOTOR_REDUCTION_RATIO)

/// @brief Right inverter speed CAN data in RPM (int16_t), convert to wheel
/// speed in RPM (float) after reduction.
#define INV_SPEED_CAN_TO_WHEEL_PHY_R(can)                 \
  (PARAM_MOTOR_DIR_R * ANGULAR_VELOCITY_CAN_TO_PHY(can) / \
   PARAM_MOTOR_REDUCTION_RATIO)

/// @brief Left inverter torque CAN data in 0.001 rated torque (int16_t),
/// convert to wheel torque in Nm (float).
#define INV_TORQUE_CAN_TO_WHEEL_PHY_L(can)           \
  (PARAM_MOTOR_DIR_L * PARAM_MOTOR_REDUCTION_RATIO * \
   PARAM_MOTOR_RATED_TORQUE * INV_TORQUE_CAN_TO_PHY(can))

/// @brief Right inverter torque CAN data in 0.001 rated torque (int16_t),
/// convert to wheel torque in Nm (float).
#define INV_TORQUE_CAN_TO_WHEEL_PHY_R(can)           \
  (PARAM_MOTOR_DIR_R * PARAM_MOTOR_REDUCTION_RATIO * \
   PARAM_MOTOR_RATED_TORQUE * INV_TORQUE_CAN_TO_PHY(can))

/**
 * @}
 */

#endif  // VCU_CANBUS_CONVERT_H_
