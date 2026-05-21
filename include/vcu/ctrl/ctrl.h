/**
 * @file
 * @brief Control system.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-02-24
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef VCU_CTRL_H_
#define VCU_CTRL_H_

// project includes
#include "vcu/ctrl/params.h"

/**
 * @defgroup ctrl Control
 * @brief Control system.
 *
 * @{
 */

/**
 * @brief Save current control parameter settings.
 *
 * @return 0 on success, negative error code on failure.
 */
int ctrl_settings_save();

/**
 * @brief Change the gear of the vehicle (forward/reverse).
 * @author chicken0709 (brianliang0709@gmail.com)
 * @date 2026-05-11
 * @return 1 on success, 0 on failure 
 */
int ctrl_ctrl_change_gear();

/**
 * @} // ctrl
 */

#endif  // VCU_CTRL_H_
