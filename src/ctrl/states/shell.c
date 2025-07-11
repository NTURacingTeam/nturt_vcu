// glibc includes
#include <stddef.h>
#include <string.h>

// zephyr includes
#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <zephyr/sys/util.h>

// project includes
#include "vcu/ctrl/states.h"

/* static function declaration -----------------------------------------------*/
static void states_trans_get_handler(size_t idx,
                                     struct shell_static_entry *entry);
static int states_get_cmd_handler(const struct shell *sh, size_t argc,
                                  char **argv, void *data);
static int states_trans_cmd_handler(const struct shell *sh, size_t argc,
                                    char **argv, void *data);

/* static variable -----------------------------------------------------------*/
SHELL_DYNAMIC_CMD_CREATE(states_trans_subcmd, states_trans_get_handler);

SHELL_STATIC_SUBCMD_SET_CREATE(
    states_cmd,
    SHELL_CMD_ARG(get, NULL, "Get the current state.", states_get_cmd_handler,
                  1, 0),
    SHELL_CMD_ARG(
        trans, &states_trans_subcmd,
        "Execute a state transition command to to transition to a new state.\n"
        "Usage: trans <transition>",
        states_trans_cmd_handler, 2, 0),
    SHELL_SUBCMD_SET_END);
SHELL_CMD_REGISTER(states, &states_cmd,
                   "Control system state machine commands.\n"
                   "Usage: states <subcommand>",
                   NULL);

/* static function definition ------------------------------------------------*/
static void states_trans_get_handler(size_t idx,
                                     struct shell_static_entry *entry) {
  for (enum states_trans_cmd cmd = 0; cmd < NUM_TRANS_CMD; cmd++) {
    if (states_valid_transition(cmd)) {
      if (idx == 0) {
        const struct states_trans_cmd_info *info = states_trans_cmd_info(cmd);
        entry->syntax = info->name;
        entry->handler = NULL;
        entry->subcmd = NULL;
        entry->help = info->desc;
        return;

      } else {
        idx--;
      }
    }
  }

  entry->syntax = NULL;
}

static int states_get_cmd_handler(const struct shell *sh, size_t argc,
                                  char **argv, void *data) {
  (void)argc;
  (void)argv;
  (void)data;

  char buf[100];
  states_t states = states_get();
  states_states_str(buf, sizeof(buf), states);
  shell_print(sh, "Current states: 0x%X (%s)", states, buf);

  return 0;
}

static int states_trans_cmd_handler(const struct shell *sh, size_t argc,
                                    char **argv, void *data) {
  (void)argc;

  enum states_trans_cmd cmd = TRANS_CMD_INVALID;
  for (enum states_trans_cmd i = 0; i < NUM_TRANS_CMD; i++) {
    if (!strcmp(states_trans_cmd_info(i)->name, argv[1])) {
      cmd = i;
      break;
    }
  }

  if (cmd == TRANS_CMD_INVALID) {
    shell_error(sh, "Unknown command: %s", argv[1]);
    return -ENOENT;

  } else if (!states_valid_transition(cmd)) {
    const struct states_trans_cmd_info *info = states_trans_cmd_info(cmd);

    shell_error(sh, "Transition %s requires state %s, which is not satisfied.",
                info->name, states_state_str(info->src));

    char buf[100];
    states_t states = states_get();
    states_states_str(buf, sizeof(buf), states);
    shell_print(sh, "Note current states: 0x%X (%s)", states, buf);

    return -EINVAL;
  }

  states_transition(cmd);
  return 0;
}
