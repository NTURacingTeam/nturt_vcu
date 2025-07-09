#include "vcu/dashboard.h"

// glibc includes
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// zephyr includes
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>

LOG_MODULE_DECLARE(vcu_dashboard);

/* macro ---------------------------------------------------------------------*/
#define DASHBOARD_SETTINGS_ROOT "dashboard"

/* static function definition ------------------------------------------------*/
static int calib_load(const char* key, size_t len_rd, settings_read_cb read_cb,
                      void* cb_arg);

/* static variable -----------------------------------------------------------*/
SETTINGS_STATIC_HANDLER_DEFINE(dashboard, DASHBOARD_SETTINGS_ROOT, NULL,
                               calib_load, NULL, NULL);

/* function definition -------------------------------------------------------*/
int dashboard_settings_save() {
  int ret;

  uint8_t brightness = dashboard_brightness_get();
  ret = settings_save_one(DASHBOARD_SETTINGS_ROOT "/brightness", &brightness,
                          sizeof(uint8_t));
  if (ret < 0) {
    LOG_ERR("settings_save failed: %s", strerror(-ret));
  }

  return 0;
}

/* static function definition ------------------------------------------------*/
static int calib_load(const char* key, size_t len, settings_read_cb read_cb,
                      void* cb_arg) {
  const char* next;
  int ret;

  if (settings_name_steq(key, "brightness", &next) && !next) {
    if (len != sizeof(uint8_t)) {
      return -EINVAL;
    }

    uint8_t brightness;
    ret = read_cb(cb_arg, &brightness, len);
    if (ret < 0) {
      return ret;
    }

    dashboard_brightness_set(brightness);

  } else {
    return -ENOENT;
  }

  return 0;
}
