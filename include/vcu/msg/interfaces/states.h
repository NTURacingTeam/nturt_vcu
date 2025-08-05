/**
 * @file
 * @brief Control system state machine message type definitions.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-07-19
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef VCU_MSG_INTERFACES_STATES_H_
#define VCU_MSG_INTERFACES_STATES_H_

// nturt includes
#include <nturt/msg/interfaces/common.h>

// project includes
#include "vcu/ctrl/states.h"

/**
 * @defgroup msg_if_states State Machine Messages
 * @brief Control system state machine message type definitions.
 *
 * @ingroup msg_if
 * @{
 */

/* macro ---------------------------------------------------------------------*/
/// @brief List of state messages.
#define MSG_STATES_LIST msg_states

/**
 * @addtogroup msg_if_pri_states State Machine Message Printing
 * @brief State machine message printing format strings.
 *
 * @ingroup msg_if_pri
 * @{
 */

/// @brief Insert @ref msg_states printf format string.
#define PRImsg_states PRImsg_header "\n\r\tTODO"

/**
 * @brief Insert @ref msg_states arguments to printf format.
 *
 * @param[in] data The control system state message data.
 */
#define PRImsg_states_arg(data) PRImsg_header_arg((data).header)

/**
 * @} // msg_if_pri_states
 */

/**
 * @defgroup msg_if_csv_states State Machine Message CSV
 * @brief State machine message CSV format strings.
 *
 * @ingroup msg_if_csv
 * @{
 */

/// @brief CSV header for @ref msg_states.
#define CSV_PRImsg_states_header CSV_PRImsg_header_header ",cmd,before,after"

/// @brief Insert @ref msg_states CSV format string.
#define CSV_PRImsg_states CSV_PRImsg_header ",%d,%d,%d"

/**
 * @brief Insert @ref msg_states arguments to CSV print format.
 *
 * @param[in] data The control system state message data.
 */
#define CSV_PRImsg_states_arg(data) \
  CSV_PRImsg_header_arg((data).header), (data).cmd, (data).before, (data).after

/**
 * @} // msg_if_csv_states
 */

/* type ----------------------------------------------------------------------*/
/// @brief VCU control system state message.
struct msg_states {
  /** Message header. */
  struct msg_header header;

  /** Processed state transition command. */
  enum states_trans_cmd cmd;

  /** States before processing the command. */
  states_t before;

  /** States after processing the command. */
  states_t after;
};

/**
 * @} // msg_if_states
 */

#endif  // VCU_MSG_INTERFACES_STATES_H_
