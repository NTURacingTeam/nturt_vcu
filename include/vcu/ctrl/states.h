/**
 * @file
 * @brief Control system state machine.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-02-24
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef VCU_CTRL_STATES_H_
#define VCU_CTRL_STATES_H_

// glibc includes
#include <stdbool.h>
#include <stdint.h>

// zephyr includes
#include <zephyr/sys/iterable_sections.h>
#include <zephyr/sys/util.h>

/**
 * @addtogroup stat States
 * @brief Control system state machine.
 *
 * @ingroup ctrl
 * @{
 */

/* macro ---------------------------------------------------------------------*/
/**
 * @brief Same as @ref STATES_CALLBACK_DEFINE, but with a custom name for the
 * callback.
 */
#define STATES_CALLBACK_DEFINE_NAMED(_name, _states, _handler, _user_data) \
  static const STRUCT_SECTION_ITERABLE(states_callback, _name) = {         \
      .states = _states,                                                   \
      .handler = _handler,                                                 \
      .user_data = _user_data,                                             \
  }

/**
 * @brief Define a callback for state transition.
 *
 * @param[in] states When transition from/to what states to call the callback.
 * Multiple @ref states_state can be specified using bitwise OR operator (|).
 * @param[in] handler Handler of the state transition.
 * @param[in] user_data Pointer to custom data for the callback.
 *
 * @note Since the name of the callback is derived from the name of @p handler ,
 * if the same handler is used for multiple callbacks,
 * @ref STATES_CALLBACK_DEFINE_NAMED can be used instead to prevent linker
 * errors.
 */
#define STATES_CALLBACK_DEFINE(states, handler, user_data)                 \
  STATES_CALLBACK_DEFINE_NAMED(CONCAT(__states_handler_, handler), states, \
                               handler, user_data)

/* type ----------------------------------------------------------------------*/
enum states_state;

/// @brief State machine states type, where each bit represents a state defined
/// in @ref states_state.
typedef uint32_t states_t;

/**
 * @brief State transition handler type.
 *
 * @param[in] state to transition from/to.
 * @param[in] is_entry True when transitioning to the state. False when
 * transition from.
 * @param[in,out] user_data Pointer to custom data for the callback provided by
 * @ref STATES_CALLBACK_DEFINE.
 */
typedef void (*states_handler_t)(enum states_state state, bool is_entry,
                                 void *user_data);

/// @brief State machine states.
enum states_state {
  STATE_INVALID = 0,

  STATE_READY = BIT(0),
  STATE_RTD_BLINK = BIT(1),
  STATE_RTD_STEADY = BIT(2),
  STATE_RTD_READY = BIT(3),
  STATE_RTD_SOUND = BIT(4),

  STATE_RUNNING = BIT(5),
  STATE_RUNNING_OK = BIT(6),
  STATE_RUNNING_ERROR = BIT(7),

  STATE_ERROR = BIT(8),

  STATE_ALL = UINT32_MAX,

  NUM_STATE = 9,
};

/// @brief State transition commands.
enum states_trans_cmd {
  TRANS_CMD_INVALID = 0,
  TRANS_CMD_PEDAL,
  TRANS_CMD_PEDAL_CLEAR,
  TRANS_CMD_RTD,
  TRANS_CMD_RTD_FORCED,
  TRANS_CMD_RTD_FINISH,
  TRANS_CMD_ERROR,
  TRANS_CMD_ERROR_CLEARED,
  TRANS_CMD_ERROR_RUNNING,
  TRANS_CMD_ERROR_CLEARED_RUNNING,
  TRANS_CMD_FATAL_ERROR,
  TRANS_CMD_DISABLE,

  NUM_TRANS_CMD,
};

/// @brief State transition command information.
struct states_trans_cmd_info {
  /** Source states to transition from. */
  states_t src;

  /** Destination state to transition to. */
  enum states_state dst;

  /** String representation of the command. */
  const char *name;

  /** Description of the command. */
  const char *desc;
};

/// @brief State transition callback.
struct states_callback {
  /** When transition from/to what states to call the callback. */
  states_t states;

  /** State transition handler. */
  states_handler_t handler;

  /** User data for the callback functions. */
  void *user_data;
};

/* function declaration ------------------------------------------------------*/
/**
 * @brief Get the current states.
 *
 * @return states_t Current states.
 */
states_t states_get();

/**
 * @brief Test if a state transition command is valid.
 *
 * @param[in] cmd State transition command.
 *
 * @retval true If the command can be executed.
 * @retval false If the command cannot be executed.
 */
bool states_valid_transition(enum states_trans_cmd cmd);

/**
 * @brief Check if a state transition is currently pending.
 *
 * @return true If a state transition is pending.
 * @return false If no state transition is pending.
 */
bool states_transition_pending();

/**
 * @brief Execute a state transition command to transition to a new state.
 *
 * @param[in] cmd State transition command.
 *
 * @warning Must not be called from an ISR or within a state transition
 * callback.
 */
void states_transition(enum states_trans_cmd cmd);

/**
 * @brief Get the string representation of a state.
 *
 * @param[in] state State.
 * @return const char* String representation.
 */
const char *states_state_str(enum states_state state);

/**
 * @brief Get the string representation of states separated by commas in the
 * same semantic as snprintf.
 *
 * @param[out] buf Buffer to store the string representation.
 * @param[in] size Size of the buffer.
 * @param[in] states States.
 * @return int Number of bytes written to the buffer, excluding the null
 * terminator which would be written if the buffer is large enough.
 */
int states_states_str(char *buf, size_t size, states_t states);

/**
 * @brief Get the information of a state transition.
 *
 * @param[in] cmd State transition command.
 * @return const struct states_trans_cmd_info* Pointer to the state transition
 * command information.
 */
const struct states_trans_cmd_info *states_transition_info(
    enum states_trans_cmd cmd);

/**
 * @} // stat
 */

#endif  // VCU_CTRL_STATES_H_
