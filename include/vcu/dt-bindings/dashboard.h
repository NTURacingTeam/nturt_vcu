/**
 * @file
 * @brief Dashboard and display device tree binding constants.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-07-08
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef VCU_DT_BINDINGS_DASHBOARD_H_
#define VCU_DT_BINDINGS_DASHBOARD_H_

#include <zephyr/dt-bindings/input/input-event-codes.h>

#define LED_NUM_RUNNING 8
#define LED_NUM_ERROR 12
#define LED_NUM_PEDAL_PLAUS 4

#define INPUT_BTN_RTD INPUT_BTN_2
#define INPUT_BTN_UP INPUT_BTN_4
#define INPUT_BTN_DOWN INPUT_BTN_6

#define INPUT_BTN_MODIFIER_DOUBLE_TAP 0x1000

#define INPUT_BTN_DISABLE (INPUT_BTN_RTD | INPUT_BTN_MODIFIER_DOUBLE_TAP)

#define INPUT_BTN_MODIFIER_HOLD 0x2000

#define INPUT_BTN_RESET (INPUT_BTN_RTD | INPUT_BTN_MODIFIER_HOLD)
#define INPUT_BTN_UP_HOLD (INPUT_BTN_UP | INPUT_BTN_MODIFIER_HOLD)
#define INPUT_BTN_DOWN_HOLD (INPUT_BTN_DOWN | INPUT_BTN_MODIFIER_HOLD)

#endif  // VCU_DT_BINDINGS_DASHBOARD_H_
