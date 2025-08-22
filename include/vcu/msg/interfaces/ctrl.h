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
#define MSG_CTRL_LIST \
  msg_ctrl_vehicle_state, msg_ctrl_word, msg_ctrl_torque, msg_ctrl_cmd

/**
 * @defgroup msg_if_pri_ctrl Control Message Printing
 * @brief Control message printing format strings.
 *
 * @ingroup msg_if_pri
 * @{
 */

/// @brief Insert @ref msg_ctrl_vehicle_state printf format string.
#define PRImsg_ctrl_vehicle_state \
  PRImsg_header "\n\r\tvelocity (m/s): %" PRImsg_2d_data

/**
 * @brief Insert @ref msg_ctrl_vehicle_state arguments to printf format.
 *
 * @param[in] data The vehicle state message data.
 */
#define PRImsg_ctrl_vehicle_state_arg(data) \
  PRImsg_header_arg((data).header), PRImsg_2d_data_arg((data).velocity)

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
  PRImsg_header "\n\r\ttarget torque (Nm): %" PRImsg_4wheel_data

/**
 * @brief Insert @ref msg_ctrl_torque arguments to printf format.
 *
 * @param[in] data The target torque message data.
 */
#define PRImsg_ctrl_torque_arg(data) \
  PRImsg_header_arg((data).header), PRImsg_4wheel_data_arg((data).torque)

/**
 * @brief Insert @ref msg_ctrl_cmd printf format string.
 *
 * @param[in] data The control command message data.
 */
#define PRImsg_ctrl_cmd PRImsg_header "\n\r\trtd: %hu, emcy_stop: %hu"

/**
 * @brief Insert @ref msg_ctrl_cmd arguments to printf format.
 *
 * @param[in] data The control command message data.
 */
#define PRImsg_ctrl_cmd_arg(data) \
  PRImsg_header_arg((data).header), (data).rtd, (data).emcy_stop

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

/// @brief CSV header for @ref msg_ctrl_vehicle_state.
#define CSV_PRImsg_ctrl_vehicle_state_header \
  CSV_PRImsg_header_header "," CSV_PRImsg_2d_data_header(velocity)

/// @brief Insert @ref msg_ctrl_vehicle_state CSV format string.
#define CSV_PRImsg_ctrl_vehicle_state CSV_PRImsg_header ",%" CSV_PRImsg_2d_data

/**
 * @brief Insert @ref msg_ctrl_vehicle_state arguments to CSV print format.
 *
 * @param[in] data The vehicle state message data.
 */
#define CSV_PRImsg_ctrl_vehicle_state_arg(data) \
  CSV_PRImsg_header_arg((data).header), CSV_PRImsg_2d_data_arg((data).velocity)

/// @brief CSV header for @ref msg_ctrl_word.
#define CSV_PRImsg_ctrl_word_header \
  CSV_PRImsg_header_header "," CSV_PRImsg_4wheel_flags_header(ctrl)

/// @brief Insert @ref msg_ctrl_word CSV format string.
#define CSV_PRImsg_ctrl_word CSV_PRImsg_header ",%" CSV_PRImsg_4wheel_flags

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
#define CSV_PRImsg_ctrl_torque CSV_PRImsg_header ",%" CSV_PRImsg_4wheel_data

/**
 * @brief Insert @ref msg_ctrl_torque arguments to CSV print format.
 *
 * @param[in] data The target torque message data.
 */
#define CSV_PRImsg_ctrl_torque_arg(data) \
  CSV_PRImsg_header_arg((data).header),  \
      CSV_PRImsg_4wheel_data_arg((data).torque)

/// @brief CSV header for @ref msg_ctrl_cmd.
#define CSV_PRImsg_ctrl_cmd_header CSV_PRImsg_header_header ",rtd,emcy_stop"

/// @brief Insert @ref msg_ctrl_cmd CSV format string.
#define CSV_PRImsg_ctrl_cmd CSV_PRImsg_header ",%hu,%hu"

/**
 * @brief Insert @ref msg_ctrl_cmd arguments to CSV print format.
 *
 * @param[in] data The control command message data.
 */
#define CSV_PRImsg_ctrl_cmd_arg(data) \
  CSV_PRImsg_header_arg((data).header), (data).rtd, (data).emcy_stop

/**
 * @} // msg_if_csv_ctrl
 */

/* type ----------------------------------------------------------------------*/
/// @brief Vehicle state message.
struct msg_ctrl_vehicle_state {
  /** Message header. */
  struct msg_header header;

  /** Vehicle velocity. Unit: m/s */
  union msg_2d_data velocity;
};

/// @brief Inverter control word message.
struct msg_ctrl_word {
  /** Message header. */
  struct msg_header header;

  /** Inverter control word. */
  union msg_4wheel_flags ctrl;
};

/// @brief Inverter target torque message.
struct msg_ctrl_torque {
  /** Message header. */
  struct msg_header header;

  /** Inverter target torque. Unit: Nm */
  union msg_4wheel_data torque;
};

/// @brief Control command message.
struct msg_ctrl_cmd {
  /** Message header. */
  struct msg_header header;

  /** RTD button, 1: pressed, 0: not. */
  uint8_t rtd;

  /** Emergency stop button, 1: pressed, 0: not. */
  uint8_t emcy_stop;
};

/**
 * @} // msg_if_ctrl
 */

#endif  // VCU_MSG_INTERFACES_CTRL_H_
