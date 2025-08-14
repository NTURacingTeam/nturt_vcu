/**
 * @file
 * @brief Dashboard and display system.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-07-07
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef DASHBOARD_H_
#define DASHBOARD_H_

// zephyr includes
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>

// project includes
#include "vcu/dt-bindings/dashboard.h"

/**
 * @defgroup dashboard Dashboard
 * @brief Dashboard and display system.
 *
 * @{
 */

/* macro ---------------------------------------------------------------------*/
/// @brief Number of LEDs in the dashboard.
#define NUM_LED DT_CHILD_NUM_STATUS_OKAY(DT_CHOSEN(nturt_leds))

/// @brief Length of the LED strips.
#define LED_STRIP_LEN DT_PROP(DT_CHOSEN(nturt_accel_display), chain_length)

/// @brief Period for a blinking LED to switch state.
#define LED_BLINK_PERIOD K_MSEC(250)

/// @brief Interval between two modifications when holding.
#define HOLD_MODIFY_INTERVAL K_MSEC(100)

/* type ----------------------------------------------------------------------*/
typedef void (*dashboard_mode_trans_t)();

/// @brief Components of the dashboard.
enum dashboard_component {
  DASHBOARD_SPEED,
  DASHBOARD_BATTERY,
  DASHBOARD_ACCEL,
  DASHBOARD_BRAKE,

  NUM_DASHBOARD_DISPLAY,
};

/// @brief Dashboard modes.
enum dashboard_mode {
  DASHBOARD_NORMAL,
  DASHBOARD_SETTING,
  DASHBOARD_TEST,

  NUM_DASHBOARD_MODE,
};

/// @brief Information about a dashboard mode.
struct dashboard_mode_info {
  /** Function to start the mode. */
  dashboard_mode_trans_t start;

  /** Function to stop the mode. */
  dashboard_mode_trans_t stop;

  /** String representation of the command. */
  const char* name;

  /** Description of the command. */
  const char* desc;
};

/* function declaration ------------------------------------------------------*/
/**
 * @brief Get the current brightness of the dashboard.
 *
 * @return int Current brightness level in [0, 100].
 */
int dashboard_brightness_get();

/**
 * @brief Set the brightness of the dashboard.
 *
 * @param brightness The brightness level to set in [0, 100]. If the value is
 * outside this range, it will be clamped.
 */
void dashboard_brightness_set(int brightness);

/**
 * @brief Set the LED state.
 *
 * @param led The LED number to set.
 * @param set True to turn on the LED, false to turn it off.
 */
void dashboard_led_set(int led, bool set);

/**
 * @brief Clear the display for a component.
 *
 * @param display The component to clear.
 */
void dashboard_clear(enum dashboard_component display);

/**
 * @brief Set the level for a component.
 *
 * @param display The component to set.
 * @param level The level to set, clamped to the range of the component.
 */
void dashboard_set_level(enum dashboard_component display, int level);

/**
 * @brief Set error state for a component.
 *
 * @param display The component to set the error for.
 */
void dashboard_set_error(enum dashboard_component display);

/**
 * @brief Apply the selected state for a component.
 *
 * @param display The component to apply the selected state for.
 */
void dashboard_apply_selected(enum dashboard_component display);

/**
 * @brief Get the current dashboard mode.
 *
 * @return enum dashboard_mode The current mode.
 */
enum dashboard_mode dashboard_mode_get();

/**
 * @brief Set the  dashboard mode.
 *
 * @param mode The mode to set.
 */
void dashboard_mode_set(enum dashboard_mode mode);

/**
 * @brief Get the information about a dashboard mode.
 *
 * @param mode The mode to get information for.
 * @return const struct dashboard_mode_info* Pointer to the mode information.
 */
const struct dashboard_mode_info* dashboard_mode_info(enum dashboard_mode mode);

/**
 * @brief Save the current dashboard settings.
 *
 * @return int 0 on success, negative error code on failure.
 */
int dashboard_settings_save();

/**
 * @} // dashboard
 */

#endif  // DASHBOARD_H_
