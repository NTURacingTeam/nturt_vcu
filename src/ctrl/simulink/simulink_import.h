#ifndef SIMULINK_TYPES_H_
#define SIMULINK_TYPES_H_

// glibc includes
#include <stdint.h>

// nturt includes
#include <nturt/msg/interfaces/interfaces.h>

// project includes
#include "vcu/ctrl/ctrl.h"
#include "vcu/msg/interfaces/interfaces.h"

/* type ----------------------------------------------------------------------*/
// common
typedef struct msg_header msg_header;
typedef union msg_2d_data msg_2d_data;
typedef union msg_3d_data msg_3d_data;
typedef union msg_4wheel_data msg_4wheel_data;

// sensor
typedef struct msg_sensor_cockpit msg_sensor_cockpit;
typedef struct msg_sensor_wheel msg_sensor_wheel;
typedef struct msg_sensor_imu msg_sensor_imu;
typedef struct msg_sensor_gps msg_sensor_gps;

// ctrl
typedef struct msg_ctrl_vehicle_state msg_ctrl_vehicle_state;
typedef struct msg_ctrl_torque msg_ctrl_torque;
typedef struct msg_ctrl_tc msg_ctrl_tc;
typedef struct msg_ctrl_tc_in msg_ctrl_tc_in;

/* exported variable ---------------------------------------------------------*/
CTRL_PARAM_EXTERN(CTRL_PARAM_LIST);

#endif  // SIMULINK_TYPES_H_
