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

// glibc includes
#include <stdint.h>

/**
 * @defgroup ctrl Ctrl
 * @brief Control system.
 *
 * @{
 */

uint8_t ctrl_inv_torq_fl_get();
uint8_t ctrl_inv_torq_fr_get();
uint8_t ctrl_inv_torq_rl_get();
uint8_t ctrl_inv_torq_rr_get();

void ctrl_inv_torq_fl_set(uint8_t torq);
void ctrl_inv_torq_fl_set(uint8_t torq);
void ctrl_inv_torq_rl_set(uint8_t torq);
void ctrl_inv_torq_rr_set(uint8_t torq);

int ctrl_settings_save();

/**
 * @} // ctrl
 */

#endif  // VCU_CTRL_H_
