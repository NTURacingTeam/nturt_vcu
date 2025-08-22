// glibc includes
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// zephyr includes
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>
#include <zephyr/sys/util.h>

// nturt includes
#include <nturt/sys/util.h>

// project includes
#include "vcu/ctrl/ctrl.h"

LOG_MODULE_DECLARE(vcu_ctrl);

/* macro ---------------------------------------------------------------------*/
#define CTRL_SETTINGS_ROOT "ctrl"

/* static function definition ------------------------------------------------*/
static int ctrl_settings_load(const char* key, size_t len_rd,
                              settings_read_cb read_cb, void* cb_arg);
static int ctrl_settings_export(int (*export_func)(const char* name,
                                                   const void* val,
                                                   size_t val_len));

/* static variable -----------------------------------------------------------*/
SETTINGS_STATIC_HANDLER_DEFINE(ctrl, CTRL_SETTINGS_ROOT, NULL,
                               ctrl_settings_load, NULL, ctrl_settings_export);

/* function definition -------------------------------------------------------*/
int ctrl_settings_save() {
  int ret = settings_save_subtree(CTRL_SETTINGS_ROOT);
  if (ret < 0) {
    LOG_ERR("settings_save_subtree failed: %s", strerror(-ret));
    return ret;
  }

  return 0;
}

/* static function definition ------------------------------------------------*/
#define _CTRL_SETTINGS_LOAD(param)                                     \
  else if (settings_name_steq(key, STRINGIFY(_CTRL_PARAM_NAME(param)), \
                              &next) &&                                \
           !next) {                                                    \
    if (len != sizeof(_CTRL_PARAM_TYPE(param))) {                      \
      return -EINVAL;                                                  \
    }                                                                  \
                                                                       \
    _CTRL_PARAM_TYPE(param) val;                                       \
    ret = read_cb(cb_arg, &val, len);                                  \
    if (ret < 0) {                                                     \
      return ret;                                                      \
    }                                                                  \
                                                                       \
    _CTRL_PARAM_SET(_CTRL_PARAM_NAME(param))(val);                     \
  }

static int ctrl_settings_load(const char* key, size_t len,
                              settings_read_cb read_cb, void* cb_arg) {
  const char* next;
  int ret;

  if (false) {
  }

  FOR_EACH(_CTRL_SETTINGS_LOAD, (), CTRL_PARAM_LIST)

  else {
    return -ENOENT;
  }

  return 0;
}

#define _CTRL_SETTINGS_EXPORT(param)                                          \
  do {                                                                        \
    strcpy(p, "/" STRINGIFY(_CTRL_PARAM_NAME(param)));                        \
    _CTRL_PARAM_TYPE(param) val = _CTRL_PARAM_GET(_CTRL_PARAM_NAME(param))(); \
                                                                              \
    ret = export_func(path, &val, sizeof(_CTRL_PARAM_TYPE(param)));           \
    if (ret < 0) {                                                            \
      LOG_ERR("Failed to export %s: %s", path, strerror(-ret));               \
      return ret;                                                             \
    }                                                                         \
  } while (0)

static int ctrl_settings_export(int (*export_func)(const char* name,
                                                   const void* val,
                                                   size_t val_len)) {
  int ret;
  char path[SETTINGS_MAX_NAME_LEN + 1];
  char* p = stpcpy(path, CTRL_SETTINGS_ROOT);

  N_FOR_EACH(_CTRL_SETTINGS_EXPORT, (;), CTRL_PARAM_LIST);

  return 0;
}
