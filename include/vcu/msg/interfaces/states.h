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

/* macro ---------------------------------------------------------------------*/
/// @brief List of state messages.
#define MSG_STATES_LIST msg_states

#define PRImsg_states PRImsg_header "\n\r\tTODO"

#define PRImsg_states_arg(data) PRImsg_header_arg((data).header)

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

#endif  // VCU_MSG_INTERFACES_STATES_H_
