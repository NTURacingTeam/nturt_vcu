/**
 * @file
 * @brief Inverter control.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-07-15
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef NTURT_VCU_CTRL_INV_H_
#define NTURT_VCU_CTRL_INV_H_

/**
 * @defgroup ctrl_inv Inverter Control
 * @brief Inverter control.
 *
 * @ingroup ctrl
 * @{
 */

/* function definition -------------------------------------------------------*/

/** @brief Reset the inverter fault state.
 *
 * @retval 0 If successful.
 * @retval -EBUSY If the inverter is currently enabled.
 */
int ctrl_inv_fault_reset();

/**
 * @} // ctrl_inv
 */

#endif  // NTURT_VCU_CTRL_INV_H_
