// glibc includes
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// zephyr includes
#include <zephyr/shell/shell.h>
#include <zephyr/sys/util.h>

// nturt includes
#include <nturt/sys/util.h>

// project includes
#include "vcu/ctrl/ctrl.h"
#include "vcu/ctrl/inv.h"

/* static function -----------------------------------------------------------*/
static void ctrl_param_get_get_handler(size_t idx,
                                       struct shell_static_entry *entry);
static void ctrl_param_set_get_handler(size_t idx,
                                       struct shell_static_entry *entry);

static int ctrl_param_list_cmd_handler(const struct shell *sh, size_t argc,
                                       char **argv, void *data);
static int ctrl_param_get_cmd_handler(const struct shell *sh, size_t argc,
                                      char **argv, void *data);
static int ctrl_param_set_cmd_handler(const struct shell *sh, size_t argc,
                                      char **argv, void *data);

static int ctrl_inv_fault_reset_cmd_handler(const struct shell *sh, size_t argc,
                                            char **argv, void *data);

/* static variable -----------------------------------------------------------*/
SHELL_DYNAMIC_CMD_CREATE(ctrl_param_get_subcmd, ctrl_param_get_get_handler);
SHELL_DYNAMIC_CMD_CREATE(ctrl_param_set_subcmd, ctrl_param_set_get_handler);

SHELL_STATIC_SUBCMD_SET_CREATE(
    ctrl_param_cmd,
    SHELL_CMD_ARG(list, NULL,
                  "List the values of control parameters.\n"
                  "Usage: list",
                  ctrl_param_list_cmd_handler, 1, 0),
    SHELL_CMD_ARG(get, &ctrl_param_get_subcmd,
                  "Get the value of a control parameter.\n"
                  "Usage: get <param>",
                  ctrl_param_get_cmd_handler, 2, 0),
    SHELL_CMD_ARG(set, &ctrl_param_set_subcmd,
                  "Set the value of a control parameter.\n"
                  "Usage: set <param> <value>",
                  ctrl_param_set_cmd_handler, 3, 0),
    SHELL_SUBCMD_SET_END);

SHELL_STATIC_SUBCMD_SET_CREATE(ctrl_inv_cmd,
                               SHELL_CMD_ARG(fault_reset, NULL,
                                             "Reset inverter fault.",
                                             ctrl_inv_fault_reset_cmd_handler,
                                             1, 0),
                               SHELL_SUBCMD_SET_END);

SHELL_STATIC_SUBCMD_SET_CREATE(ctrl_cmd,
                               SHELL_CMD(param, &ctrl_param_cmd,
                                         "Control system parameters control.",
                                         NULL),
                               SHELL_CMD(inv, &ctrl_inv_cmd,
                                         "Inverter control.", NULL),
                               SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(ctrl, &ctrl_cmd,
                   "Control system commands.\n"
                   "Usage: ctrl <subcommand>",
                   NULL);

/* function definition -------------------------------------------------------*/
#define _CTRL_PARAM_GET_GET(idx, param)                 \
  case idx:                                             \
    entry->syntax = STRINGIFY(_CTRL_PARAM_NAME(param)); \
    break

static void ctrl_param_get_get_handler(size_t idx,
                                       struct shell_static_entry *entry) {
  if (idx >= NUM_VA_ARGS(CTRL_PARAM_LIST)) {
    entry->syntax = NULL;
    return;
  }

  switch (idx) {
    FOR_EACH_IDX(_CTRL_PARAM_GET_GET, (;), CTRL_PARAM_LIST);

    default:
      break;
  }

  entry->handler = NULL;
  entry->subcmd = NULL;
  entry->help = NULL;
}

#define _CTRL_PARAM_SET_GET(idx, param)                 \
  case idx:                                             \
    entry->syntax = STRINGIFY(_CTRL_PARAM_NAME(param)); \
    entry->help = STRINGIFY(_CTRL_PARAM_TYPE(param));   \
    break

static void ctrl_param_set_get_handler(size_t idx,
                                       struct shell_static_entry *entry) {
  if (idx >= NUM_VA_ARGS(CTRL_PARAM_LIST)) {
    entry->syntax = NULL;
    return;
  }

  switch (idx) {
    FOR_EACH_IDX(_CTRL_PARAM_SET_GET, (;), CTRL_PARAM_LIST);

    default:
      break;
  }

  entry->handler = NULL;
  entry->subcmd = NULL;
}

#define _CTRL_PARAM_LIST_CMD(param)                                           \
  do {                                                                        \
    _CTRL_PARAM_TYPE(param) val = _CTRL_PARAM_GET(_CTRL_PARAM_NAME(param))(); \
    shell_fprintf(sh, SHELL_NORMAL, STRINGIFY(_CTRL_PARAM_NAME(param)) ": "); \
    shell_fprintf(sh, SHELL_NORMAL, PRI(val), PRI_arg(val));                  \
    shell_fprintf(sh, SHELL_NORMAL,                                           \
                  " (" STRINGIFY(_CTRL_PARAM_TYPE(param)) ")\n");             \
  } while (0)

static int ctrl_param_list_cmd_handler(const struct shell *sh, size_t argc,
                                       char **argv, void *data) {
  (void)argc;
  (void)argv;
  (void)data;

  FOR_EACH(_CTRL_PARAM_LIST_CMD, (;), CTRL_PARAM_LIST);

  return 0;
}

#define _CTRL_PARAM_GET_CMD(param)                                            \
  else if (strcmp(argv[1], STRINGIFY(_CTRL_PARAM_NAME(param))) == 0) {        \
    _CTRL_PARAM_TYPE(param) val = _CTRL_PARAM_GET(_CTRL_PARAM_NAME(param))(); \
    shell_fprintf(sh, SHELL_NORMAL, PRI(val), PRI_arg(val));                  \
    shell_fprintf(sh, SHELL_NORMAL,                                           \
                  " (" STRINGIFY(_CTRL_PARAM_TYPE(param)) ")\n");             \
  }

static int ctrl_param_get_cmd_handler(const struct shell *sh, size_t argc,
                                      char **argv, void *data) {
  (void)argc;
  (void)data;

  if (false) {
  }

  FOR_EACH(_CTRL_PARAM_GET_CMD, (), CTRL_PARAM_LIST)

  else {
    shell_error(sh, "Unknown parameter: %s", argv[1]);
    return -ENOENT;
  }

  return 0;
}

#define _CTRL_PARAM_SET_CMD(param)                                           \
  else if (strcmp(argv[1], STRINGIFY(_CTRL_PARAM_NAME(param))) == 0) {       \
    _CTRL_PARAM_TYPE(param) val;                                             \
    if (sscanf(argv[2], PRI(val), &val) != 1) {                              \
      shell_error(sh,                                                        \
                  "Invalid " STRINGIFY(_CTRL_PARAM_NAME(param)) "value: %s", \
                  argv[2]);                                                  \
      return -EINVAL;                                                        \
    }                                                                        \
                                                                             \
    _CTRL_PARAM_SET(_CTRL_PARAM_NAME(param))(val);                           \
  }

static int ctrl_param_set_cmd_handler(const struct shell *sh, size_t argc,
                                      char **argv, void *data) {
  (void)argc;
  (void)data;

  if (false) {
  }

  FOR_EACH(_CTRL_PARAM_SET_CMD, (), CTRL_PARAM_LIST)

  else {
    shell_error(sh, "Unknown parameter: %s", argv[1]);
    return -ENOENT;
  }

  if (IS_ENABLED(CONFIG_VCU_CTRL_SETTINGS)) {
    ctrl_settings_save();
  }

  return 0;
}

static int ctrl_inv_fault_reset_cmd_handler(const struct shell *sh, size_t argc,
                                            char **argv, void *data) {
  (void)argc;
  (void)argv;
  (void)data;

  ctrl_inv_fault_reset();

  return 0;
}
