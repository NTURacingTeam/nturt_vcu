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

// glibc includes
#include <stdint.h>

// zephyr includes
#include <zephyr/devicetree.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/kernel.h>

// project includes
#include "vcu/dt-bindings/dashboard.h"

/* macro ---------------------------------------------------------------------*/
#define NUM_LED DT_CHILD_NUM_STATUS_OKAY(DT_CHOSEN(nturt_leds))

#define LED_STRIP_LEN DT_PROP(DT_CHOSEN(nturt_accel_display), chain_length)

#define LED_BLINK_PERIOD K_MSEC(250)

/// @todo
#define RPM_TO_SPEED(rpm) (rpm)

/* type ----------------------------------------------------------------------*/
typedef void (*dashboard_mode_trans_t)();

enum dashboard_mode {
  DASHBOARD_NORMAL,
  DASHBOARD_SETTING,
  DASHBOARD_TEST,

  NUM_DASHBOARD_MODE,
};

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
uint8_t dashboard_brightness_get();
void dashboard_brightness_set(uint8_t brightness);

enum dashboard_mode dashboard_mode_get();
void dashboard_mode_set(enum dashboard_mode mode);

int dashboard_settings_save();

void dashboard_normal_start();
void dashboard_normal_stop();

void dashboard_setting_start();
void dashboard_setting_stop();

void dashboard_test_start();
void dashboard_test_stop();

const struct dashboard_mode_info* dashboard_mode_info(enum dashboard_mode mode);

void rgb_set_level(struct led_rgb* rgb, int len, int level);

/**
 * @brief Set rgb struct to error pattern, which is a five-zone pattern with the
 * second and fourth zones lit up.
 */
void rgb_set_error(struct led_rgb* rgb, int len);

void rgb_apply_selected(struct led_rgb* rgb, int len);

#endif  // DASHBOARD_H_
