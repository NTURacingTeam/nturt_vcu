#include "vcu/dashboard.h"

// glibc includes
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// zephyr includes
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>
#include <zephyr/sys/util.h>

LOG_MODULE_DECLARE(vcu_dashboard);

/* macro ---------------------------------------------------------------------*/
#define _DASHBOARD_SETTINGS_ROOT dashboard
#define DASHBOARD_SETTINGS_ROOT STRINGIFY(_DASHBOARD_SETTINGS_ROOT)

/* static function definition ------------------------------------------------*/
static int dashboard_settings_load(const char* key, size_t len_rd,
                                   settings_read_cb read_cb, void* cb_arg);

/* static variable -----------------------------------------------------------*/
SETTINGS_STATIC_HANDLER_DEFINE(_DASHBOARD_SETTINGS_ROOT,
                               DASHBOARD_SETTINGS_ROOT, NULL,
                               dashboard_settings_load, NULL, NULL);

/* function definition -------------------------------------------------------*/
int dashboard_settings_save() {
  int ret = settings_save_subtree(DASHBOARD_SETTINGS_ROOT);
  if (ret < 0) {
    LOG_ERR("settings_save_subtree failed: %s", strerror(-ret));
    return ret;
  }

  return 0;
}

/* static function definition ------------------------------------------------*/
static int dashboard_settings_load(const char* key, size_t len,
                                   settings_read_cb read_cb, void* cb_arg) {
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

static int dashboard_settings_export(int (*export_func)(const char* name,
                                                        const void* val,
                                                        size_t val_len)) {
  const char* path = DASHBOARD_SETTINGS_ROOT "/brightness";
  uint8_t brightness = dashboard_brightness_get();

  int ret = export_func(path, &brightness, sizeof(uint8_t));
  if (ret < 0) {
    LOG_ERR("Failed to export %s: %s", path, strerror(-ret));
    return ret;
  }

  return 0;
}
