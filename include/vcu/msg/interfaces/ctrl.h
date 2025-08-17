/**
 * @file
 * @brief Control message type definitions.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-07-13
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef VCU_MSG_INTERFACES_CTRL_H_
#define VCU_MSG_INTERFACES_CTRL_H_

// nturt includes
#include <nturt/msg/interfaces/common.h>

/**
 * @defgroup msg_if_ctrl Control Message
 * @brief Control message type definitions.
 *
 * @ingroup msg_if
 * @{
 */

/* macro ---------------------------------------------------------------------*/
#define MSG_CTRL_LIST msg_ctrl_word, msg_ctrl_torque

/**
 * @defgroup msg_if_pri_ctrl Control Message Printing
 * @brief Control message printing format strings.
 *
 * @ingroup msg_if_pri
 * @{
 */

/// @brief Insert @ref msg_ctrl_word printf format string.
#define PRImsg_ctrl_word \
  PRImsg_header "\n\r\tcontrol word: %" PRImsg_4wheel_flags

/**
 * @brief Insert @ref msg_ctrl_word arguments to printf format.
 *
 * @param[in] data The control word message data.
 */
#define PRImsg_ctrl_word_arg(data) \
  PRImsg_header_arg((data).header), PRImsg_4wheel_flags_arg((data).ctrl)

/// @brief Insert @ref msg_ctrl_torque printf format string.
#define PRImsg_ctrl_torque \
  PRImsg_header "\n\r\ttarget torque: %" PRImsg_4wheel_data

/**
 * @brief Insert @ref msg_ctrl_torque arguments to printf format.
 *
 * @param[in] data The target torque message data.
 */
#define PRImsg_ctrl_torque_arg(data) \
  PRImsg_header_arg((data).header), PRImsg_4wheel_data_arg((data).torque)

/**
 * @} // msg_if_pri_ctrl
 */

/**
 * @defgroup msg_if_csv_ctrl Control Message CSV
 * @brief Control message CSV format strings.
 *
 * @ingroup msg_if_csv
 * @{
 */

/// @brief CSV header for @ref msg_ctrl_word.
#define CSV_PRImsg_ctrl_word_header \
  CSV_PRImsg_header_header "," CSV_PRImsg_4wheel_flags_header(ctrl)

/// @brief Insert @ref msg_ctrl_word CSV format string.
#define CSV_PRImsg_ctrl_word \
  CSV_PRImsg_header ",%" CSV_PRImsg_4wheel_flags

/**
 * @brief Insert @ref msg_ctrl_word arguments to CSV print format.
 *
 * @param[in] data The control word message data.
 */
#define CSV_PRImsg_ctrl_word_arg(data) \
  CSV_PRImsg_header_arg((data).header), CSV_PRImsg_4wheel_flags_arg((data).ctrl)

/// @brief CSV header for @ref msg_ctrl_torque.
#define CSV_PRImsg_ctrl_torque_header \
  CSV_PRImsg_header_header "," CSV_PRImsg_4wheel_data_header(torque)

/// @brief Insert @ref msg_ctrl_torque CSV format string.
#define CSV_PRImsg_ctrl_torque \
  CSV_PRImsg_header ",%" CSV_PRImsg_4wheel_data

/**
 * @brief Insert @ref msg_ctrl_torque arguments to CSV print format.
 *
 * @param[in] data The target torque message data.
 */
#define CSV_PRImsg_ctrl_torque_arg(data) \
  CSV_PRImsg_header_arg((data).header),  \
      CSV_PRImsg_4wheel_data_arg((data).torque)

/**
 * @} // msg_if_csv_ctrl
 */

/* type ----------------------------------------------------------------------*/
/// @brief Inverter control word message.
struct msg_ctrl_word {
  struct msg_header header;

  /** Inverter control word. */
  union msg_4wheel_flags ctrl;
};

/// @brief Inverter target torque message.
struct msg_ctrl_torque {
  struct msg_header header;

  /** Inverter target torque. Unit: Nm */
  union msg_4wheel_data torque;
};

/**
 * @} // msg_if_ctrl
 */

#endif  // VCU_MSG_INTERFACES_CTRL_H_
