/**
 * @file
 * @brief State machine.
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
 * @addtogroup States States
 * @ingroup Ctrl
 * @{
 */

/* macro ---------------------------------------------------------------------*/

/**
 * @brief Define a callback for state transition with custom name.
 *
 * Same as @ref STATES_CALLBACK_DEFINE, but with a custom name for the callback.
 */
#define STATES_CALLBACK_DEFINE_NAMED(_name, _state, _handler, _user_data) \
  const STRUCT_SECTION_ITERABLE(states_callback, _name) = {               \
      .state = _state,                                                    \
      .handler = _handler,                                                \
      .user_data = _user_data,                                            \
  }

/**
 * @brief Define a callback for state transition.
 *
 * @param[in] state State at which to call the callback or @ref STATE_ALL to
 * always call the callback.
 * @param[in] handler Handler of the state transition.
 * @param[in] user_data Pointer to custom data for the callback.
 *
 * @note Since the name of the callback is derived from @p handler , if the same
 * handler is used for multiple callbacks, @ref STATES_CALLBACK_DEFINE_NAMED can
 * be used instead to prevent linker errors.
 */
#define STATES_CALLBACK_DEFINE(state, handler, user_data)                 \
  STATES_CALLBACK_DEFINE_NAMED(CONCAT(__states_handler_, handler), state, \
                               handler, user_data)

/* type ----------------------------------------------------------------------*/
enum states_state;

/// @brief State machine states type, where each bit represents a state defined
/// in @ref states_state.
typedef uint32_t states_t;

/// @brief State transition handler type.
typedef void (*states_handler_t)(enum states_state state, bool is_entry,
                                 void *user_data);

/// @brief State machine states.
enum states_state {
  STATE_ALL = 0,
  STATE_ERR_FREE,
  STATE_READY,
  STATE_RTD_BLINK,
  STATE_RTD_STEADY,
  STATE_RTD_READY,
  STATE_RTD_SOUND,
  STATE_RUNNING,
  STATE_ERROR,

  NUM_STATE,
};

/// @brief State transition commands.
enum states_trans_cmd {
  TRANS_CMD_INVALID = 0,
  TRANS_CMD_ERR,
  TRANS_CMD_ERR_CLEAR,
  TRANS_CMD_PEDAL,
  TRANS_CMD_PEDAL_CLEAR,
  TRANS_CMD_RTD,
  TRANS_CMD_RTD_FINISH,
  TRANS_CMD_DISABLE,

  NUM_TRANS_CMD,
};

/// @brief State transition callback.
struct states_callback {
  /**
   * At what state transition to call the callback or @ref STATE_ALL to always
   * call the callback.
   */
  enum states_state state;

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
 * @param cmd Transition command to test.
 * @retval true If the transition command can be executed.
 * @retval false If the transition command cannot be executed.
 */
bool states_valid_transition(enum states_trans_cmd cmd);

/**
 * @brief Transition to a new state.
 *
 * @param cmd Transition command to execute.
 */
void states_transition(enum states_trans_cmd cmd);

/**
 * @brief Get the string representation of a state.
 *
 * @param state State to get the string representation for.
 * @return const char* String representation of the state.
 */
const char *states_state_str(enum states_state state);

/**
 * @brief Get the string representation of a state transition command.
 *
 * @param cmd State transition command to get the string representation for.
 * @return const char* String representation of the state transition command.
 */
const char *states_trans_cmd_str(enum states_trans_cmd cmd);

/**
 * @} // States
 */

#endif  // VCU_CTRL_STATES_H_
