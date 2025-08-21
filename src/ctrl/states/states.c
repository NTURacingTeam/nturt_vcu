#include "vcu/ctrl/states.h"

// libc includes
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// zephyr includes
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/smf.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/sys/iterable_sections.h>
#include <zephyr/sys/util.h>
#include <zephyr/zbus/zbus.h>

// nturt includes
#include <nturt/sys/sys.h>

// project includes
#include "vcu/msg/msg.h"

LOG_MODULE_REGISTER(vcu_states);

BUILD_ASSERT(NUM_STATE <= 32, "Number of states must not exceed 32");

/* macro ---------------------------------------------------------------------*/
/// @brief Token to use if a state does not have a parent state or initial
/// transition when defining states using @ref SMF_STATES_DEFINE.
#define NO_STATE 0

/**
 * @brief Specify a state machine state. Used in @ref SMF_STATES_DEFINE.
 *
 * If the parent state or the initial transition is not defined,
 * @ref NO_STATE should be used.
 *
 * @param[in] state State.
 * @param[in] parent Parent state.
 * @param[in] init_trans Child state to initially transition to.
 */
#define SMF_STATE(state, parent, init_trans) (state, parent, init_trans)

#define _SMF_STATE_STATE(state) GET_ARG_N(1, __DEBRACKET state)
#define _SMF_STATE_PARENT(state) GET_ARG_N(2, __DEBRACKET state)
#define _SMF_STATE_INIT_TRANS(state) GET_ARG_N(3, __DEBRACKET state)

#define _SMF_STATE_ENTRY(state) CONCAT(__, state, _, entry)
#define _SMF_STATE_RUN(state) CONCAT(__, state, _, run)
#define _SMF_STATE_EXIT(state) CONCAT(__, state, _, exit)

#define _SMF_STATE_FUNCTIONS_DEFINE(_state)                        \
  static void _SMF_STATE_ENTRY(_state)(void *obj) {                \
    struct states_ctx *ctx = obj;                                  \
                                                                   \
    ctx->states |= _state;                                         \
                                                                   \
    states_process_trans(ctx, _state, true);                       \
  }                                                                \
                                                                   \
  static enum smf_state_result _SMF_STATE_RUN(_state)(void *obj) { \
    struct states_ctx *ctx = obj;                                  \
                                                                   \
    return states_process_cmd(ctx, _state);                        \
  }                                                                \
                                                                   \
  static void _SMF_STATE_EXIT(_state)(void *obj) {                 \
    struct states_ctx *ctx = obj;                                  \
                                                                   \
    ctx->states &= ~_state;                                        \
                                                                   \
    states_process_trans(ctx, _state, false);                      \
  }

#define _SMF_STATE(state, name)                                     \
  [LOG2(_SMF_STATE_STATE(state))] = SMF_CREATE_STATE(               \
      _SMF_STATE_ENTRY(_SMF_STATE_STATE(state)),                    \
      _SMF_STATE_RUN(_SMF_STATE_STATE(state)),                      \
      _SMF_STATE_EXIT(_SMF_STATE_STATE(state)),                     \
      COND_CODE_0(IS_EQ(_SMF_STATE_PARENT(state), NO_STATE),        \
                  (&name[LOG2(_SMF_STATE_PARENT(state))]), (NULL)), \
      COND_CODE_0(IS_EQ(_SMF_STATE_INIT_TRANS(state), NO_STATE),    \
                  (&name[LOG2(_SMF_STATE_INIT_TRANS(state))]), (NULL)))

#define _STATE_STR(state) \
  [LOG2(_SMF_STATE_STATE(state))] = STRINGIFY(_SMF_STATE_STATE(state))

/**
 * @brief Define state machine framework states and its string representation.
 *
 * @param name Name of the state machine framework states.
 * @param str_name Name of the states' string representations.
 * @param ... States in the the state machine, must be specified by
 * @ref SMF_STATE.
 */
#define SMF_STATES_DEFINE(name, str_name, ...)                  \
  FOR_EACH(_SMF_STATE_FUNCTIONS_DEFINE, (),                     \
           FOR_EACH(_SMF_STATE_STATE, (, ), __VA_ARGS__));      \
                                                                \
  static const struct smf_state name[] = {                      \
      FOR_EACH_FIXED_ARG(_SMF_STATE, (, ), name, __VA_ARGS__)}; \
                                                                \
  static const char *str_name[] = {                             \
      FOR_EACH(_STATE_STR, (, ), __VA_ARGS__),                  \
  }

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

  bool deferred;

  struct k_sem sem;

  /** Current states of the state machine. */
  states_t states;

  /** Transition command to be executed, @ref TRANS_CMD_INVALID if none. */
  enum states_trans_cmd cmd;

  struct k_work run_state_work;
};

/* static function declaration -----------------------------------------------*/
static void states_init(struct states_ctx *ctx);
static enum smf_state_result states_process_cmd(struct states_ctx *ctx,
                                                enum states_state state);
static void states_process_trans(struct states_ctx *ctx,
                                 enum states_state state, bool is_entry);
static void states_run_state(struct states_ctx *ctx);

static int init();

static void run_state_work(struct k_work *work);

/* static varaible -----------------------------------------------------------*/
// clang-format off

/// @brief State transition informations.
static const struct states_trans_cmd_info g_trans_cmd_infos[] = {
    TRANS_CMD_INFO(TRANS_CMD_INVALID,
        STATE_INVALID, STATE_INVALID,
        "Invalid state stransition command, internal use only."
    ),
    TRANS_CMD_INFO(TRANS_CMD_PEDAL,
        STATE_RTD_BLINK, STATE_RTD_STEADY,
        "Brake pressed and accelerator released."
    ),
    TRANS_CMD_INFO(TRANS_CMD_PEDAL_CLEAR,
        STATE_RTD_STEADY, STATE_RTD_BLINK,
        "Brake released or accelerator pressed."
    ),
    TRANS_CMD_INFO(TRANS_CMD_RTD,
        STATE_RTD_STEADY, STATE_RTD_SOUND,
        "Start RTD process."
    ),
    TRANS_CMD_INFO(TRANS_CMD_RTD_FORCED,
        STATE_RTD_BLINK | STATE_RTD_READY | STATE_ERROR, STATE_RTD_SOUND,
        "Forcely start RTD process."
    ),
    TRANS_CMD_INFO(TRANS_CMD_RTD_FINISH,
        STATE_RTD_SOUND, STATE_RUNNING,
        "RTD process finished."
    ),
    TRANS_CMD_INFO(TRANS_CMD_ERROR,
        STATE_READY, STATE_ERROR,
        "Error happened."
    ),
    TRANS_CMD_INFO(TRANS_CMD_ERROR_CLEARED,
        STATE_ERROR, STATE_READY,
        "Error cleared."
    ),
    TRANS_CMD_INFO(TRANS_CMD_ERROR_RUNNING,
        STATE_RUNNING_OK, STATE_RUNNING_ERROR,
        "Error happened during running state."
    ),
    TRANS_CMD_INFO(TRANS_CMD_ERROR_CLEARED_RUNNING,
        STATE_RUNNING_ERROR, STATE_RUNNING_OK,
        "Error cleared during running state."
    ),
    TRANS_CMD_INFO(TRANS_CMD_FATAL_ERROR,
        STATE_READY | STATE_RUNNING, STATE_ERROR,
        "Fatal error happened."
    ),
    TRANS_CMD_INFO(TRANS_CMD_DISABLE,
        STATE_RUNNING, STATE_READY,
        "Disable system."
    ),
};

/// @brief State machine framework states and their names.
SMF_STATES_DEFINE(g_smf_states, g_state_names,
    SMF_STATE(STATE_READY,
        NO_STATE,
        COND_CODE_1(CONFIG_VCU_STATES_CHECK_PEDAL, (STATE_RTD_BLINK), (STATE_RTD_STEADY))
    ),
    SMF_STATE(STATE_RTD_BLINK, STATE_READY, NO_STATE),
    SMF_STATE(STATE_RTD_STEADY, STATE_READY, STATE_RTD_READY),
    SMF_STATE(STATE_RTD_READY, STATE_RTD_STEADY, NO_STATE),
    SMF_STATE(STATE_RTD_SOUND, STATE_RTD_STEADY, NO_STATE),

    SMF_STATE(STATE_RUNNING, NO_STATE, STATE_RUNNING_OK),
    SMF_STATE(STATE_RUNNING_OK, STATE_RUNNING, NO_STATE),
    SMF_STATE(STATE_RUNNING_ERROR, STATE_RUNNING, NO_STATE),

    SMF_STATE(STATE_ERROR, NO_STATE, NO_STATE)
);

// clang-format on

/// @brief State module context.
static struct states_ctx g_ctx = {
    .initialized = false,
    .deferred = false,
    .sem = Z_SEM_INITIALIZER(g_ctx.sem, 1, 1),
    .states = 0,
    .cmd = TRANS_CMD_INVALID,
    .run_state_work = Z_WORK_INITIALIZER(run_state_work),
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
  __ASSERT(g_ctx.initialized, "States module not yet initialized");

  if (IS_ENABLED(CONFIG_VCU_STATES_TRANS_SYNC)) {
    __ASSERT(!k_is_in_isr(), "Must not be called from ISR");
  }

  k_sem_take(&g_ctx.sem, K_FOREVER);

  if (!states_valid_transition(cmd)) {
    LOG_ERR("Invalid command: %s", states_transition_info(cmd)->name);
    k_sem_give(&g_ctx.sem);
    return;
  }

  g_ctx.cmd = cmd;

  if (IS_ENABLED(CONFIG_VCU_STATES_TRANS_SYNC) || !g_ctx.deferred) {
    states_run_state(&g_ctx);
  } else {
    sys_work_submit(&g_ctx.run_state_work);
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

const struct states_trans_cmd_info *states_transition_info(
    enum states_trans_cmd cmd) {
  __ASSERT(cmd < NUM_TRANS_CMD, "Invalid transition command: %d", cmd);

  return &g_trans_cmd_infos[cmd];
}

/* static function definition ------------------------------------------------*/
static void states_init(struct states_ctx *ctx) {
  // this also runs all entry functions
  smf_set_initial(&ctx->smf_ctx, &g_smf_states[STATE_READY]);

  ctx->initialized = true;
}

static enum smf_state_result states_process_cmd(struct states_ctx *ctx,
                                                enum states_state state) {
  if (ctx->cmd == TRANS_CMD_INVALID) {
    return SMF_EVENT_HANDLED;

  } else if (g_trans_cmd_infos[ctx->cmd].src & state) {
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

  smf_run_state(&ctx->smf_ctx);

  states_t after = ctx->states;

  if (IS_ENABLED(CONFIG_VCU_STATES_MSG)) {
    struct msg_states msg = {
        .cmd = cmd,
        .before = before,
        .after = after,
    };
    msg_header_init(&msg.header);

    zbus_chan_pub(&msg_states_chan, &msg, K_FOREVER);
  }

  LOG_INF("Processed transition command %s: 0x%X -> 0x%X",
          states_transition_info(cmd)->name, before, after);

  char buf[100];
  states_states_str(buf, sizeof(buf), before & ~after);
  LOG_DBG("\tFrom: 0x%X (%s)", before & ~after, buf);

  states_states_str(buf, sizeof(buf), after & ~before);
  LOG_DBG("\tTo:   0x%X (%s)", after & ~before, buf);

  states_states_str(buf, sizeof(buf), before & after);
  LOG_DBG("\tSame: 0x%X (%s)", before & after, buf);

  k_sem_give(&ctx->sem);
}

static int init() {
  states_init(&g_ctx);

  return 0;
}

static void run_state_work(struct k_work *work) {
  struct states_ctx *ctx =
      CONTAINER_OF(work, struct states_ctx, run_state_work);

  states_run_state(ctx);
}

#ifndef CONFIG_VCU_STATES_TRANS_SYNC

static int defer_init() {
  g_ctx.deferred = true;

  return 0;
}

SYS_INIT(defer_init, APPLICATION, CONFIG_VCU_STATES_TRANS_DEFER_PRIORITY);

#endif  // CONFIG_VCU_STATES_TRANS_SYNC
