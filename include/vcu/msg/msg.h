/**
 * @file
 * @brief Inter-thread communication support.
 *
 * @author quantumspawner
 * @version 0.0.1
 * @date 2025-07-19
 * @copyright Copyright (c) 2025 NTU Racing Team
 */

#ifndef VCU_MSG_MSG_H_
#define VCU_MSG_MSG_H_

// nturt includes
#include <nturt/msg/msg.h>
#include <nturt/msg/aggregation.h>

// project includes
#include "vcu/msg/interfaces/interfaces.h"

/**
 * @addtogroup msg
 * @{
 */

/* macro ---------------------------------------------------------------------*/
/// @brief List of all VCU messages.
#define MSG_VCU_LIST MSG_CTRL_LIST, MSG_STATES_LIST

/* exported variable ---------------------------------------------------------*/
MSG_CHAN_DECLARE(MSG_VCU_LIST);

extern struct agg_typed msg_sensor_wheel_agg;

/**
 * @} // msg
 */

#endif  // VCU_MSG_MSG_H_
