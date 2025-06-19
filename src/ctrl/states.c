#include "vcu/ctrl/states.h"

// libc includes
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// zephyr includes
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>
#include <zephyr/smf.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/sys/iterable_sections.h>
#include <zephyr/sys/util.h>

// nturt includes
#include <nturt/err.h>

LOG_MODULE_DECLARE(ctrl);

BUILD_ASSERT(NUM_STATE <= 32, "Number of states must not exceed 32");

/* macro ---------------------------------------------------------------------*/
/// @brief Token to use if a state does not have a parent state or initial
/// transition when defining states using @ref SMF_STATES_DEFINE.
#define NO_STATE 0

#define __SMF_STATE_FUNCTIONS_DEFINE(_state)            \
  static void CONCAT(__, _state, _, entry)(void *obj) { \
    struct states_ctx *ctx = obj;                       \
                                                        \
    ctx->states |= BIT(_state);                         \
                                                        \
    states_process_trans(ctx, _state, true);            \
  }                                                     \
                                                        \
  static void CONCAT(__, _state, _, run)(void *obj) {   \
    struct states_ctx *ctx = obj;                       \
                                                        \
    states_process_cmd(ctx, _state);                    \
  }                                                     \
                                                        \
  static void CONCAT(__, _state, _, exit)(void *obj) {  \
    struct states_ctx *ctx = obj;                       \
                                                        \
    ctx->states &= ~BIT(_state);                        \
                                                        \
    states_process_trans(ctx, _state, false);           \
  }

#define _SMF_STATE_FUNCTIONS_DEFINE(args) \
  __SMF_STATE_FUNCTIONS_DEFINE(GET_ARG_N(1, __DEBRACKET args))

#define __SMF_STATE(name, state, parent, initial)                    \
  [state] = SMF_CREATE_STATE(                                        \
      CONCAT(__, state, _, entry), CONCAT(__, state, _, run),        \
      CONCAT(__, state, _, exit),                                    \
      COND_CODE_0(IS_EQ(parent, NO_STATE), (&name[parent]), (NULL)), \
      COND_CODE_0(IS_EQ(initial, NO_STATE), (&name[initial]), (NULL)))

#define _SMF_STATE(args, name)                      \
  __SMF_STATE(name, GET_ARG_N(1, __DEBRACKET args), \
              GET_ARG_N(2, __DEBRACKET args), GET_ARG_N(3, __DEBRACKET args))

#define __STATE_STR(state) [state] = #state

#define _STATE_STR(args) __STATE_STR(GET_ARG_N(1, __DEBRACKET args))

/**
 * @brief Define state machine framework states and its name for the control
 * system.
 *
 * @param name Name of the state machine framework states.
 * @param str_name Name of the state as strings.
 * @param ... List of states in the format (state, parent state, initial
 * transition). If the parent state or the initial transition is not defined,
 * @ref NO_STATE should be used.
 */
#define SMF_STATES_DEFINE(name, str_name, ...)                  \
  FOR_EACH(_SMF_STATE_FUNCTIONS_DEFINE, (), __VA_ARGS__);       \
                                                                \
  static const struct smf_state name[] = {                      \
      FOR_EACH_FIXED_ARG(_SMF_STATE, (, ), name, __VA_ARGS__)}; \
                                                                \
  static const char *str_name[] = {FOR_EACH(_STATE_STR, (, ), __VA_ARGS__)}

/**
 * @brief Define a state transition table entry.
 *
 * @param _cmd Transition command.
 * @param _src Source state to transition from.
 * @param _dst Destination state to transition to.
 */
#define TRANS_TBL_ENTRY(_cmd, _src, _dst) \
  [_cmd] = {                              \
      .name = #_cmd,                      \
      .src = _src,                        \
      .dst = _dst,                        \
  }

/* type ----------------------------------------------------------------------*/
/// @brief State module context.
struct states_ctx {
  /** State machine framework context, must be the first member. */
  struct smf_ctx smf_ctx;

  bool initialized;

  struct k_sem sem;

  struct k_event event;

  /** Current states of the state machine. */
  states_t states;

  /** Transition command to be executed, @ref TRANS_CMD_INVALID if none. */
  enum states_trans_cmd cmd;
};

/// @brief State transition table entry.
struct state_trans_tbl_entry {
  /** Name of the transition. */
  const char *name;

  /** Source state to transition from. */
  enum states_state src;

  /** Destination state to transition to. */
  enum states_state dst;
};

/* static function declaration -----------------------------------------------*/
static void states_init(struct states_ctx *ctx);
static void states_process_cmd(struct states_ctx *ctx, enum states_state state);
static void states_process_trans(struct states_ctx *ctx,
                                 enum states_state state, bool is_entry);

static int init();

/* static varaible -----------------------------------------------------------*/
/// @brief State transition table.
static const struct state_trans_tbl_entry g_trans_tbl[] = {
    TRANS_TBL_ENTRY(TRANS_CMD_ERR, STATE_ERR_FREE, STATE_ERROR),
    TRANS_TBL_ENTRY(TRANS_CMD_ERR_CLEAR, STATE_ERROR, STATE_ERR_FREE),
    TRANS_TBL_ENTRY(TRANS_CMD_PEDAL, STATE_RTD_BLINK, STATE_RTD_STEADY),
    TRANS_TBL_ENTRY(TRANS_CMD_PEDAL_CLEAR, STATE_RTD_STEADY, STATE_RTD_BLINK),
    TRANS_TBL_ENTRY(TRANS_CMD_RTD, STATE_RTD_STEADY, STATE_RTD_SOUND),
    TRANS_TBL_ENTRY(TRANS_CMD_RTD_FINISH, STATE_RTD_SOUND, STATE_RUNNING),
    TRANS_TBL_ENTRY(TRANS_CMD_DISABLE, STATE_RUNNING, STATE_READY),
};

/// @brief State machine framework states and their names.
SMF_STATES_DEFINE(g_smf_states, g_state_names,
                  (STATE_ERR_FREE, NO_STATE, STATE_READY),
                  (STATE_READY, STATE_ERR_FREE, STATE_RTD_BLINK),
                  (STATE_RTD_BLINK, STATE_READY, NO_STATE),
                  (STATE_RTD_STEADY, STATE_READY, STATE_RTD_READY),
                  (STATE_RTD_READY, STATE_RTD_STEADY, NO_STATE),
                  (STATE_RTD_SOUND, STATE_RTD_STEADY, NO_STATE),
                  (STATE_RUNNING, STATE_ERR_FREE, NO_STATE),
                  (STATE_ERROR, NO_STATE, NO_STATE));

/// @brief State module context.
static struct states_ctx g_ctx = {
    .initialized = false,
    .states = 0,
    .cmd = TRANS_CMD_INVALID,
};

SYS_INIT(init, APPLICATION, CONFIG_VCU_STATES_INIT_PRIORITY);

/* function definition -------------------------------------------------------*/
states_t states_get() { return g_ctx.states; }

bool states_valid_transition(enum states_trans_cmd cmd) {
  if (cmd >= NUM_TRANS_CMD) {
    return false;
  }

  return g_ctx.states & BIT(g_trans_tbl[cmd].src);
}

void states_transition(enum states_trans_cmd cmd) {
  __ASSERT(!k_is_in_isr(), "Must not be called from ISR");

  k_sem_take(&g_ctx.sem, K_FOREVER);

  if (!states_valid_transition(cmd)) {
    LOG_ERR("Invalid transition");
    k_sem_give(&g_ctx.sem);
    return;
  }

  g_ctx.cmd = cmd;

  if (IS_ENABLED(CONFIG_VCU_STATES_TRANS_SYNC)) {
    smf_run_state(&g_ctx.smf_ctx);
    k_sem_give(&g_ctx.sem);

  } else if (IS_ENABLED(CONFIG_VCU_STATES_TRANS_THREAD)) {
    k_event_set(&g_ctx.event, true);
  }
}

const char *states_state_str(enum states_state state) {
  if (state == STATE_ALL || state >= NUM_STATE) {
    return "";
  }

  return g_state_names[state];
}

const char *states_trans_cmd_str(enum states_trans_cmd cmd) {
  if (cmd == TRANS_CMD_INVALID || cmd >= NUM_TRANS_CMD) {
    return "";
  }

  return g_trans_tbl[cmd].name;
}

/* static function definition ------------------------------------------------*/
static void states_init(struct states_ctx *ctx) {
  k_sem_init(&ctx->sem, 1, 1);
  k_event_init(&ctx->event);

  // also runs all entry functions
  smf_set_initial(&ctx->smf_ctx, &g_smf_states[STATE_ERR_FREE]);

  ctx->initialized = true;
}

static void states_process_cmd(struct states_ctx *ctx,
                               enum states_state state) {
  if (ctx->cmd == TRANS_CMD_INVALID) {
    return;
  }

  if (g_trans_tbl[ctx->cmd].src == state) {
    smf_set_state(&ctx->smf_ctx, &g_smf_states[g_trans_tbl[ctx->cmd].dst]);
    ctx->cmd = TRANS_CMD_INVALID;
  }
}

static void states_process_trans(struct states_ctx *ctx,
                                 enum states_state state, bool is_entry) {
  STRUCT_SECTION_FOREACH(states_callback, callback) {
    if (callback->state == STATE_ALL || callback->state == state) {
      callback->handler(state, is_entry, callback->user_data);
    }
  }
}

static int init() {
  states_init(&g_ctx);

  return 0;
}

#if CONFIG_VCU_STATES_TRANS_THREAD

static void thread(void *arg1, void *arg2, void *arg3) {
  (void)arg2;
  (void)arg3;

  struct states_ctx *ctx = arg1;

  while (true) {
    k_event_wait(&ctx->event, true, true, K_FOREVER);

    smf_run_state(&ctx->smf_ctx);
    k_sem_give(&ctx->sem);
  }
}

K_THREAD_DEFINE(states, CONFIG_VCU_STATES_THREAD_STACK_SIZE, thread, &g_ctx,
                NULL, NULL, CONFIG_VCU_STATES_THREAD_PRIORITY, 0, 0);

#endif  // CONFIG_VCU_STATE_TRANS_THREAD

#if CONFIG_VCU_CTRL_SHELL

static void states_trans_get_handler(size_t idx,
                                     struct shell_static_entry *entry) {
  for (enum states_trans_cmd cmd = 0; cmd < NUM_TRANS_CMD; cmd++) {
    if (states_valid_transition(cmd)) {
      if (idx == 0) {
        entry->syntax = states_trans_cmd_str(cmd);
        entry->handler = NULL;
        entry->subcmd = NULL;
        entry->help = NULL;
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

  states_t states = states_get();
  shell_fprintf(sh, SHELL_INFO, "Current states: 0x%X (", states);

  while (states != 0) {
    enum states_state state = find_lsb_set(states) - 1;
    states &= ~BIT(state);

    shell_fprintf(sh, SHELL_INFO, "%s", states_state_str(state));
    if (states != 0) {
      shell_fprintf(sh, SHELL_INFO, ", ");
    }
  }

  shell_fprintf(sh, SHELL_INFO, ")\n");

  return 0;
}

static int states_trans_cmd_handler(const struct shell *sh, size_t argc,
                                    char **argv, void *data) {
  (void)argc;

  enum states_trans_cmd cmd = TRANS_CMD_INVALID;
  for (enum states_trans_cmd i = 0; i < NUM_TRANS_CMD; i++) {
    if (!strcmp(states_trans_cmd_str(i), argv[1])) {
      cmd = i;
      break;
    }
  }

  if (cmd == TRANS_CMD_INVALID) {
    shell_error(sh, "Unknown command: %s", argv[1]);
    return -ENOENT;

  } else if (!states_valid_transition(cmd)) {
    shell_error(sh, "Transition %s requires state %s, which is not satisfied.",
                states_trans_cmd_str(cmd),
                states_state_str(g_trans_tbl[cmd].src));

    shell_fprintf(sh, SHELL_INFO, "Note: ");
    states_get_cmd_handler(sh, 0, NULL, data);

    return -EINVAL;
  }

  states_transition(cmd);
  return 0;
}

SHELL_DYNAMIC_CMD_CREATE(states_trans_subcmd, states_trans_get_handler);

SHELL_STATIC_SUBCMD_SET_CREATE(states_cmd,
                               SHELL_CMD_ARG(get, NULL,
                                             "Get the current state.",
                                             states_get_cmd_handler, 1, 0),
                               SHELL_CMD_ARG(trans, &states_trans_subcmd,
                                             "Transition to a new state.",
                                             states_trans_cmd_handler, 2, 0),
                               SHELL_SUBCMD_SET_END);
SHELL_CMD_REGISTER(states, &states_cmd, "Control system states.", NULL);

#endif  // CONFIG_VCU_CTRL_SHELL
