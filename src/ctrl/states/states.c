#include "vcu/ctrl/states.h"

// libc includes
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// zephyr includes
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zephyr/smf.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/sys/iterable_sections.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include "nturt/msg/msg.h"

LOG_MODULE_REGISTER(vcu_states);

BUILD_ASSERT(NUM_STATE <= 32, "Number of states must not exceed 32");

/* macro ---------------------------------------------------------------------*/
/// @brief Token to use if a state does not have a parent state or initial
/// transition when defining states using @ref SMF_STATES_DEFINE.
#define NO_STATE 0

#define __SMF_STATE_FUNCTIONS_DEFINE(_state)                           \
  static void CONCAT(__, _state, _, entry)(void *obj) {                \
    struct states_ctx *ctx = obj;                                      \
                                                                       \
    ctx->states |= _state;                                             \
                                                                       \
    states_process_trans(ctx, _state, true);                           \
  }                                                                    \
                                                                       \
  static enum smf_state_result CONCAT(__, _state, _, run)(void *obj) { \
    struct states_ctx *ctx = obj;                                      \
                                                                       \
    return states_process_cmd(ctx, _state);                            \
  }                                                                    \
                                                                       \
  static void CONCAT(__, _state, _, exit)(void *obj) {                 \
    struct states_ctx *ctx = obj;                                      \
                                                                       \
    ctx->states &= ~_state;                                            \
                                                                       \
    states_process_trans(ctx, _state, false);                          \
  }

#define _SMF_STATE_FUNCTIONS_DEFINE(args) \
  __SMF_STATE_FUNCTIONS_DEFINE(GET_ARG_N(1, __DEBRACKET args))

#define __SMF_STATE(name, state, parent, initial)                          \
  [LOG2(state)] = SMF_CREATE_STATE(                                        \
      CONCAT(__, state, _, entry), CONCAT(__, state, _, run),              \
      CONCAT(__, state, _, exit),                                          \
      COND_CODE_0(IS_EQ(parent, NO_STATE), (&name[LOG2(parent)]), (NULL)), \
      COND_CODE_0(IS_EQ(initial, NO_STATE), (&name[LOG2(initial)]), (NULL)))

#define _SMF_STATE(args, name)                      \
  __SMF_STATE(name, GET_ARG_N(1, __DEBRACKET args), \
              GET_ARG_N(2, __DEBRACKET args), GET_ARG_N(3, __DEBRACKET args))

#define __STATE_STR(state) [LOG2(state)] = STRINGIFY(state)

#define _STATE_STR(args) __STATE_STR(GET_ARG_N(1, __DEBRACKET args))

/**
 * @brief Define state machine framework states and its string representation.
 *
 * @param name Name of the state machine framework states.
 * @param str_name Name of the states' string representations.
 * @param ... List of states in the format of (state, parent state, initial
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
 * @brief Define a state transition command info.
 *
 * @param _cmd State transition command.
 * @param _src Source state to transition from.
 * @param _dst Destination state to transition to.
 * @param _desc Description of the command.
 */
#define TRANS_CMD_INFO(_cmd, _src, _dst, _desc) \
  [_cmd] = {                                    \
      .src = _src,                              \
      .dst = _dst,                              \
      .name = STRINGIFY(_cmd),                  \
      .desc = _desc,                            \
  }

/* type ----------------------------------------------------------------------*/
/// @brief State module context.
struct states_ctx {
  /** State machine framework context, must be the first member. */
  struct smf_ctx smf_ctx;

  bool initialized;

  /**
   * Thread ID currently processing transition command. Used to prevent
   * transition callbacks from requesting state transitions.
   */
  k_tid_t transitiong_thread;

  struct k_sem sem;

  struct k_event event;

  /** Current states of the state machine. */
  states_t states;

  /** Transition command to be executed, @ref TRANS_CMD_INVALID if none. */
  enum states_trans_cmd cmd;
};

/* static function declaration -----------------------------------------------*/
static void states_init(struct states_ctx *ctx);
static enum smf_state_result states_process_cmd(struct states_ctx *ctx,
                                                enum states_state state);
static void states_process_trans(struct states_ctx *ctx,
                                 enum states_state state, bool is_entry);
static void states_run_state(struct states_ctx *ctx);

static int init();

/* static varaible -----------------------------------------------------------*/
/// @brief State transition informations.
static const struct states_trans_cmd_info g_trans_cmd_infos[] = {
    TRANS_CMD_INFO(TRANS_CMD_INVALID, STATE_INVALID, STATE_INVALID,
                   "Invalid state stransition command, internal use only."),
    TRANS_CMD_INFO(TRANS_CMD_ERR, STATE_ERR_FREE, STATE_ERR, "Error happened."),
    TRANS_CMD_INFO(TRANS_CMD_ERR_CLEAR, STATE_ERR, STATE_ERR_FREE,
                   "Error cleared."),
    TRANS_CMD_INFO(TRANS_CMD_PEDAL, STATE_RTD_BLINK, STATE_RTD_STEADY,
                   "Brake pressed and accelerator released."),
    TRANS_CMD_INFO(TRANS_CMD_PEDAL_CLEAR, STATE_RTD_STEADY, STATE_RTD_BLINK,
                   "Brake released or accelerator pressed."),
    TRANS_CMD_INFO(TRANS_CMD_RTD, STATE_RTD_STEADY, STATE_RTD_SOUND,
                   "Start RTD sound."),
    TRANS_CMD_INFO(TRANS_CMD_RTD_FINISH, STATE_RTD_SOUND, STATE_RUNNING,
                   "RTD sound finished."),
    TRANS_CMD_INFO(TRANS_CMD_DISABLE, STATE_RUNNING, STATE_READY,
                   "Disable system."),
};

/// @brief State machine framework states and their names.
SMF_STATES_DEFINE(g_smf_states, g_state_names,
                  (STATE_ERR_FREE, NO_STATE, STATE_READY),
                  (STATE_READY, STATE_ERR_FREE,
                   COND_CODE_1(CONFIG_VCU_STATES_CHECK_PEDAL, (STATE_RTD_BLINK),
                               (STATE_RTD_STEADY))),
                  (STATE_RTD_BLINK, STATE_READY, NO_STATE),
                  (STATE_RTD_STEADY, STATE_READY, STATE_RTD_READY),
                  (STATE_RTD_READY, STATE_RTD_STEADY, NO_STATE),
                  (STATE_RTD_SOUND, STATE_RTD_STEADY, NO_STATE),
                  (STATE_RUNNING, STATE_ERR_FREE, NO_STATE),
                  (STATE_ERR, NO_STATE, NO_STATE));

/// @brief State module context.
static struct states_ctx g_ctx = {
    .initialized = false,
    .transitiong_thread = NULL,
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

  return g_ctx.states & g_trans_cmd_infos[cmd].src;
}

void states_transition(enum states_trans_cmd cmd) {
  __ASSERT(!k_is_in_isr(), "Must not be called from ISR");
  __ASSERT(g_ctx.initialized, "States module not yet initialized");
  __ASSERT(
      !g_ctx.transitiong_thread || k_current_get() != g_ctx.transitiong_thread,
      "Transition must not be requested wthin state transition callbacks");

  k_sem_take(&g_ctx.sem, K_FOREVER);

  if (!states_valid_transition(cmd)) {
    LOG_ERR("Invalid command: %s", states_trans_cmd_info(cmd)->name);
    k_sem_give(&g_ctx.sem);
    return;
  }

  g_ctx.cmd = cmd;

  if (IS_ENABLED(CONFIG_VCU_STATES_TRANS_SYNC)) {
    states_run_state(&g_ctx);

  } else if (IS_ENABLED(CONFIG_VCU_STATES_TRANS_THREAD)) {
    k_event_set(&g_ctx.event, true);
  }
}

const char *states_state_str(enum states_state state) {
  __ASSERT(IS_POWER_OF_TWO(state) && LOG2(state) < NUM_STATE,
           "Invalid state: %d", state);

  return g_state_names[LOG2(state)];
}

int states_states_str(char *buf, size_t size, states_t states) {
  buf[0] = '\0';

  char *p = buf;
  int n = 0;
  for (int i = find_lsb_set(states) - 1; i >= 0;
       i = find_lsb_set(states & ~BIT_MASK(i + 1)) - 1) {
    enum states_state state = BIT(i);
    n += snprintf(p, size - (p - buf), "%s%s", p == buf ? "" : ", ",
                  states_state_str(state));
    p += strlen(p);
  }

  return n;
}

const struct states_trans_cmd_info *states_trans_cmd_info(
    enum states_trans_cmd cmd) {
  __ASSERT(cmd < NUM_TRANS_CMD, "Invalid transition command: %d", cmd);

  return &g_trans_cmd_infos[cmd];
}

/* static function definition ------------------------------------------------*/
static void states_init(struct states_ctx *ctx) {
  k_sem_init(&ctx->sem, 1, 1);
  k_event_init(&ctx->event);

  // also runs all entry functions
  smf_set_initial(&ctx->smf_ctx, &g_smf_states[STATE_ERR_FREE]);

  ctx->initialized = true;
}

static enum smf_state_result states_process_cmd(struct states_ctx *ctx,
                                                enum states_state state) {
  if (ctx->cmd == TRANS_CMD_INVALID) {
    return SMF_EVENT_HANDLED;

  } else if (g_trans_cmd_infos[ctx->cmd].src == state) {
    smf_set_state(&ctx->smf_ctx,
                  &g_smf_states[LOG2(g_trans_cmd_infos[ctx->cmd].dst)]);
    ctx->cmd = TRANS_CMD_INVALID;
    return SMF_EVENT_HANDLED;

  } else {
    return SMF_EVENT_PROPAGATE;
  }
}

static void states_process_trans(struct states_ctx *ctx,
                                 enum states_state state, bool is_entry) {
  STRUCT_SECTION_FOREACH(states_callback, callback) {
    if (callback->states & state) {
      callback->handler(state, is_entry, callback->user_data);
    }
  }
}

static void states_run_state(struct states_ctx *ctx) {
  states_t before = ctx->states;
  enum states_trans_cmd cmd = ctx->cmd;

  ctx->transitiong_thread = k_current_get();
  smf_run_state(&ctx->smf_ctx);

  states_t after = ctx->states;

  struct msg_states msg = {
      .cmd = cmd,
      .before = before,
      .after = after,
  };
  msg_header_init(&msg.header);

  zbus_chan_pub(&msg_states_chan, &msg, K_FOREVER);

  LOG_INF("Processed transition command %s: 0x%X -> 0x%X",
          states_trans_cmd_info(cmd)->name, before, after);

  char buf[100];
  states_states_str(buf, sizeof(buf), before & ~after);
  LOG_INF("\tFrom: 0x%X (%s)", before & ~after, buf);

  states_states_str(buf, sizeof(buf), after & ~before);
  LOG_INF("\tTo:   0x%X (%s)", after & ~before, buf);

  states_states_str(buf, sizeof(buf), before & after);
  LOG_INF("\tSame: 0x%X (%s)", before & after, buf);

  ctx->transitiong_thread = NULL;
  k_sem_give(&ctx->sem);
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

    states_run_state(ctx);
  }
}

K_THREAD_DEFINE(states_thread, CONFIG_VCU_STATES_THREAD_STACK_SIZE, thread,
                &g_ctx, NULL, NULL, CONFIG_VCU_STATES_THREAD_PRIORITY, 0, 0);

#endif  // CONFIG_VCU_STATE_TRANS_THREAD
