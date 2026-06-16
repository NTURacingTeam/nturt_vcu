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
/// @brief Front left inverter torque physical data in Nm (double), convert to
/// 0.001 rated torque (int16_t).
#define INV_TORQUE_PHY_TO_CAN_FL(phy) \
  INV_TORQ_PHY_TO_CAN(PARAM_MOTOR_DIR_FL*(phy / PARAM_MOTOR_RATED_TORQUE))

/// @brief Front right inverter torque physical data in Nm (double), convert to
/// 0.001 rated torque (int16_t).
#define INV_TORQUE_PHY_TO_CAN_FR(phy) \
  INV_TORQ_PHY_TO_CAN(PARAM_MOTOR_DIR_FR*(phy / PARAM_MOTOR_RATED_TORQUE))

/// @brief Rear left inverter torque physical data in Nm (double), convert to
/// 0.001 rated torque (int16_t).
#define INV_TORQUE_PHY_TO_CAN_RL(phy) \
  INV_TORQ_PHY_TO_CAN(PARAM_MOTOR_DIR_RL*(phy / PARAM_MOTOR_RATED_TORQUE))

/// @brief Rear right inverter torque physical data in Nm (double), convert to
/// 0.001 rated torque (int16_t).
#define INV_TORQUE_PHY_TO_CAN_RR(phy) \
  INV_TORQ_PHY_TO_CAN(PARAM_MOTOR_DIR_RR*(phy / PARAM_MOTOR_RATED_TORQUE))

/* CAN to physical -----------------------------------------------------------*/
/// @brief Front left inverter speed CAN data in RPM (int16_t), convert to wheel
/// speed in RPM (double) after reduction.
#define INV_SPEED_CAN_TO_WHEEL_PHY_FL(can)                 \
  (PARAM_MOTOR_DIR_FL * ANGULAR_VELOCITY_CAN_TO_PHY(can) / \
   PARAM_MOTOR_REDUCTION_RATIO)

/// @brief Front right inverter speed CAN data in RPM (int16_t), convert to
/// wheel speed in RPM (double) after reduction.
#define INV_SPEED_CAN_TO_WHEEL_PHY_FR(can)                 \
  (PARAM_MOTOR_DIR_FR * ANGULAR_VELOCITY_CAN_TO_PHY(can) / \
   PARAM_MOTOR_REDUCTION_RATIO)

/// @brief Rear left inverter speed CAN data in RPM (int16_t), convert to wheel
/// speed in RPM (double) after reduction.
#define INV_SPEED_CAN_TO_WHEEL_PHY_RL(can)                 \
  (PARAM_MOTOR_DIR_RL * ANGULAR_VELOCITY_CAN_TO_PHY(can) / \
   PARAM_MOTOR_REDUCTION_RATIO)

/// @brief Rear right inverter speed CAN data in RPM (int16_t), convert to wheel
/// speed in RPM (double) after reduction.
#define INV_SPEED_CAN_TO_WHEEL_PHY_RR(can)                 \
  (PARAM_MOTOR_DIR_RR * ANGULAR_VELOCITY_CAN_TO_PHY(can) / \
   PARAM_MOTOR_REDUCTION_RATIO)

/// @brief Front left inverter torque CAN data in 0.001 rated torque (int16_t),
/// convert to wheel torque in Nm (double).
#define INV_TORQUE_CAN_TO_WHEEL_PHY_FL(can)           \
  (PARAM_MOTOR_DIR_FL * PARAM_MOTOR_REDUCTION_RATIO * \
   PARAM_MOTOR_RATED_TORQUE * INV_TORQUE_CAN_TO_PHY(can))

/// @brief Front right inverter torque CAN data in 0.001 rated torque (int16_t),
/// convert to wheel torque in Nm (double).
#define INV_TORQUE_CAN_TO_WHEEL_PHY_FR(can)           \
  (PARAM_MOTOR_DIR_FR * PARAM_MOTOR_REDUCTION_RATIO * \
   PARAM_MOTOR_RATED_TORQUE * INV_TORQUE_CAN_TO_PHY(can))

/// @brief Rear left inverter torque CAN data in 0.001 rated torque (int16_t),
/// convert to wheel torque in Nm (double).
#define INV_TORQUE_CAN_TO_WHEEL_PHY_RL(can)           \
  (PARAM_MOTOR_DIR_RL * PARAM_MOTOR_REDUCTION_RATIO * \
   PARAM_MOTOR_RATED_TORQUE * INV_TORQUE_CAN_TO_PHY(can))

/// @brief Rear right inverter torque CAN data in 0.001 rated torque (int16_t),
/// convert to wheel torque in Nm (double).
#define INV_TORQUE_CAN_TO_WHEEL_PHY_RR(can)           \
  (PARAM_MOTOR_DIR_RR * PARAM_MOTOR_REDUCTION_RATIO * \
   PARAM_MOTOR_RATED_TORQUE * INV_TORQUE_CAN_TO_PHY(can))

/**
 * @}
 */

#endif  // VCU_CANBUS_CONVERT_H_
