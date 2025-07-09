#include "vcu/dashboard.h"

// glibc includes
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// zephyr includes
#include <zephyr/shell/shell.h>
#include <zephyr/sys/util.h>

/* static function -----------------------------------------------------------*/
static int dashboard_brightness_get_cmd_handler(const struct shell *sh,
                                                size_t argc, char **argv,
                                                void *data);
static int dashboard_brightness_set_cmd_handler(const struct shell *sh,
                                                size_t argc, char **argv,
                                                void *data);

static void dashboard_mode_set_get_handler(size_t idx,
                                           struct shell_static_entry *entry);
static int dashboard_mode_get_cmd_handler(const struct shell *sh, size_t argc,
                                          char **argv, void *data);
static int dashboard_mode_set_cmd_handler(const struct shell *sh, size_t argc,
                                          char **argv, void *data);

/* static variable -----------------------------------------------------------*/
SHELL_STATIC_SUBCMD_SET_CREATE(
    dashboard_brightness_cmd,
    SHELL_CMD_ARG(get, NULL, "Get brightness level.",
                  dashboard_brightness_get_cmd_handler, 0, 0),
    SHELL_CMD_ARG(set, NULL, "Set brightness level.",
                  dashboard_brightness_set_cmd_handler, 1, 0),
    SHELL_SUBCMD_SET_END);

SHELL_DYNAMIC_CMD_CREATE(dashboard_mode_set_subcmd,
                         dashboard_mode_set_get_handler);

SHELL_STATIC_SUBCMD_SET_CREATE(
    dashboard_mode_cmd,
    SHELL_CMD_ARG(get, NULL, "Get current dashboard mode.",
                  dashboard_mode_get_cmd_handler, 0, 0),
    SHELL_CMD_ARG(set, &dashboard_mode_set_subcmd, "Set dashboard mode.",
                  dashboard_mode_set_cmd_handler, 1, 0),
    SHELL_SUBCMD_SET_END);

SHELL_STATIC_SUBCMD_SET_CREATE(
    dashboard_cmd,
    SHELL_CMD_ARG(brightness, &dashboard_brightness_cmd,
                  "Dashboard brightness control.", NULL, 1, 1),
    SHELL_CMD_ARG(mode, &dashboard_mode_cmd, "Dashboard mode control.", NULL, 1,
                  1),
    SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(dashboard, &dashboard_cmd, "Dashboard and display.", NULL);

/* function definition -------------------------------------------------------*/
static int dashboard_brightness_get_cmd_handler(const struct shell *sh,
                                                size_t argc, char **argv,
                                                void *data) {
  (void)argc;
  (void)argv;
  (void)data;

  shell_print(sh, "Current brightness: %hu", dashboard_brightness_get());

  return 0;
}

static int dashboard_brightness_set_cmd_handler(const struct shell *sh,
                                                size_t argc, char **argv,
                                                void *data) {
  (void)argc;
  (void)data;

  char *endptr;
  long brightness = strtol(argv[1], &endptr, 10);
  if (endptr == argv[1]) {
    shell_error(sh, "Invalid brightness value: %s", argv[1]);
    return -EINVAL;

  } else if (brightness < 0 || brightness > 100) {
    shell_error(sh, "Brightness must be between 0 and 100.");
    return -ERANGE;
  }

  dashboard_brightness_set(brightness);

  if (IS_ENABLED(CONFIG_VCU_DASHBOARD_SETTINGS)) {
    dashboard_settings_save();
  }

  return 0;
}

static void dashboard_mode_set_get_handler(size_t idx,
                                           struct shell_static_entry *entry) {
  if (idx >= NUM_DASHBOARD_MODE) {
    entry->syntax = NULL;
    return;
  }

  const struct dashboard_mode_info *mode_info =
      dashboard_mode_info((enum dashboard_mode)idx);
  entry->syntax = mode_info->name;
  entry->handler = NULL;
  entry->subcmd = NULL;
  entry->help = mode_info->desc;
}

static int dashboard_mode_get_cmd_handler(const struct shell *sh, size_t argc,
                                          char **argv, void *data) {
  (void)argc;
  (void)argv;
  (void)data;

  enum dashboard_mode mode = dashboard_mode_get();
  const struct dashboard_mode_info *mode_info = dashboard_mode_info(mode);

  shell_print(sh, "Current mode: %s", mode_info->name);

  return 0;
}

static int dashboard_mode_set_cmd_handler(const struct shell *sh, size_t argc,
                                          char **argv, void *data) {
  (void)argc;
  (void)data;

  enum dashboard_mode mode = -1;
  for (enum dashboard_mode i = 0; i < NUM_DASHBOARD_MODE; i++) {
    if (!strcmp(dashboard_mode_info(i)->name, argv[1])) {
      mode = i;
      break;
    }
  }

  if (mode == -1) {
    shell_error(sh, "Unknown mode: %s", argv[1]);
    return -ENOENT;
  }

  dashboard_mode_set(mode);

  return 0;
}
