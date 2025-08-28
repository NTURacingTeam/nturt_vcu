// glibc includes
#include <stddef.h>

// zephyr includes
#include <zephyr/kernel.h>

// canopennode includes
#include <canopennode.h>

// nturt includes
#include <nturt/canbus/canopen.h>
#include <nturt/canbus/convert.h>
#include <nturt/msg/msg.h>

// project includes
#include "vcu/canbus/convert.h"
#include "vcu/msg/msg.h"

// clang-format off

CANOPEN_OD_TO_AGG_DEFINE(0x2210, &msg_sensor_wheel_agg, struct msg_sensor_wheel,
    OD_TO_AGG_DATA(0x1, int16_t, ANGULAR_VELOCITY_CAN_TO_PHY, speed.fl)
);

CANOPEN_OD_TO_AGG_DEFINE(0x2211, &msg_sensor_wheel_agg, struct msg_sensor_wheel,
    OD_TO_AGG_DATA(0x1, int16_t, ANGULAR_VELOCITY_CAN_TO_PHY, speed.fr)
);

CANOPEN_OD_TO_AGG_DEFINE(0x2133, &msg_sensor_wheel_agg, struct msg_sensor_wheel,
    OD_TO_AGG_DATA(0x1, int16_t, INV_TORQUE_CAN_TO_WHEEL_PHY_L, torque.rl),
    OD_TO_AGG_DATA(0x2, int16_t, INV_SPEED_CAN_TO_WHEEL_PHY_L, speed.rl)
);
CANOPEN_OD_TO_AGG_DEFINE(0x2143, &msg_sensor_wheel_agg, struct msg_sensor_wheel,
    OD_TO_AGG_DATA(0x1, int16_t, INV_TORQUE_CAN_TO_WHEEL_PHY_R, torque.rr),
    OD_TO_AGG_DATA(0x2, int16_t, INV_SPEED_CAN_TO_WHEEL_PHY_R, speed.rr)
);

CANOPEN_OD_TO_MSG_DEFINE(msg_ts_acc,
    AGG_DATA_INIT(0), K_MSEC(100), K_MSEC(80), K_MSEC(30), 0,
    OD_TO_MSG_ENTRY(0x2100, OD_TO_MSG_DATA(0x0, uint8_t, IDENTITY, AGG_MEMBER(ok))),
    OD_TO_MSG_ENTRY(0x2101, OD_TO_MSG_DATA(0x0, uint32_t, ACC_VOLT_CAN_TO_PHY, AGG_MEMBER(volt))),
    OD_TO_MSG_ENTRY(0x2102, OD_TO_MSG_DATA(0x0, int16_t, ACC_CURRENT_CAN_TO_PHY, AGG_MEMBER(current))),
    OD_TO_MSG_ENTRY(0x2103, OD_TO_MSG_DATA(0x0, int16_t, ACC_TEMP_CAN_TO_PHY, AGG_MEMBER(temp))),
    OD_TO_MSG_ENTRY(0x2104, OD_TO_MSG_DATA(0x0, uint8_t, IDENTITY, AGG_MEMBER(soc))),
    OD_TO_MSG_ENTRY(0x2105, OD_TO_MSG_DATA(0x0, int16_t, ACC_CAPACITY_CAN_TO_PHY, AGG_MEMBER(capacity)))
);

CANOPEN_OD_TO_MSG_DEFINE(msg_ts_inv,
    AGG_DATA_INIT(0), K_MSEC(100), K_MSEC(80), K_MSEC(30), 0,
    OD_TO_MSG_ENTRY(0x2131, OD_TO_MSG_DATA(0x0, uint16_t, IDENTITY, AGG_MEMBER(status.rl))),
    OD_TO_MSG_ENTRY(0x2134,
        OD_TO_MSG_DATA(0x1, uint16_t, INV_VOLT_CAN_TO_PHY, AGG_MEMBER(volt.rl)),
        OD_TO_MSG_DATA(0x2, uint16_t, INV_CURRENT_CAN_TO_PHY, AGG_MEMBER(current.rl))
    ),
    OD_TO_MSG_ENTRY(0x2135,
        OD_TO_MSG_DATA(0x1, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(inv_temp.rl)),
        OD_TO_MSG_DATA(0x2, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(motor_temp.rl)),
        OD_TO_MSG_DATA(0x3, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(mcu_temp.rl))
    ),

    OD_TO_MSG_ENTRY(0x2141, OD_TO_MSG_DATA(0x0, uint16_t, IDENTITY, AGG_MEMBER(status.rr))),
    OD_TO_MSG_ENTRY(0x2144,
        OD_TO_MSG_DATA(0x1, uint16_t, INV_VOLT_CAN_TO_PHY, AGG_MEMBER(volt.rr)),
        OD_TO_MSG_DATA(0x2, uint16_t, INV_CURRENT_CAN_TO_PHY, AGG_MEMBER(current.rr))
    ),
    OD_TO_MSG_ENTRY(0x2145,
        OD_TO_MSG_DATA(0x1, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(inv_temp.rr)),
        OD_TO_MSG_DATA(0x2, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(motor_temp.rr)),
        OD_TO_MSG_DATA(0x3, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(mcu_temp.rr))
    )
);

CANOPEN_OD_TO_MSG_DEFINE(msg_ctrl_cmd,
    AGG_DATA_INIT(0), K_MSEC(10), K_MSEC(8), K_MSEC(3), 0,
    OD_TO_MSG_ENTRY(0x2088,
        OD_TO_MSG_DATA(0x1, uint8_t, IDENTITY, AGG_MEMBER(rtd)),
        OD_TO_MSG_DATA(0x2, uint8_t, IDENTITY, AGG_MEMBER(emcy_stop))
    )
);

#ifdef CONFIG_VCU_SOURCE_COCKPIT_CANOPEN

CANOPEN_OD_TO_MSG_DEFINE(msg_sensor_cockpit,
    AGG_DATA_INIT(0), K_MSEC(10), K_MSEC(8), K_MSEC(3), 0,
    OD_TO_MSG_ENTRY(0x2080,
        OD_TO_MSG_DATA(0x0, int16_t, STEER_CAN_TO_PHY, AGG_MEMBER(steer))
    ),
    OD_TO_MSG_ENTRY(0x2081,
        OD_TO_MSG_DATA(0x1, uint8_t, PEDAL_TRAV_CAN_TO_PHY, AGG_MEMBER(accel))
    ),
    OD_TO_MSG_ENTRY(0x2082,
        OD_TO_MSG_DATA(0x1, uint8_t, PEDAL_TRAV_CAN_TO_PHY, AGG_MEMBER(brake))
    )
);

#endif // CONFIG_VCU_VCU_SOURCE_COCKPIT_CANOPEN

#ifdef CONFIG_VCU_SOURCE_IMU_CANOPEN

CANOPEN_OD_TO_MSG_DEFINE(msg_sensor_imu,
    AGG_DATA_INIT(0), K_MSEC(10), K_MSEC(8), K_MSEC(3), 0,
    OD_TO_MSG_ENTRY(0x2240,
        OD_TO_MSG_DATA(0x1, int16_t, IMU_ACCEL_CAN_TO_PHY, AGG_MEMBER(accel.x)),
        OD_TO_MSG_DATA(0x2, int16_t, IMU_ACCEL_CAN_TO_PHY, AGG_MEMBER(accel.y)),
        OD_TO_MSG_DATA(0x3, int16_t, IMU_ACCEL_CAN_TO_PHY, AGG_MEMBER(accel.z))
    ),
    OD_TO_MSG_ENTRY(0x2241,
        OD_TO_MSG_DATA(0x1, int16_t, IMU_GYRO_CAN_TO_PHY, AGG_MEMBER(gyro.x)),
        OD_TO_MSG_DATA(0x2, int16_t, IMU_GYRO_CAN_TO_PHY, AGG_MEMBER(gyro.y)),
        OD_TO_MSG_DATA(0x3, int16_t, IMU_GYRO_CAN_TO_PHY, AGG_MEMBER(gyro.z))
    ),
    OD_TO_MSG_ENTRY(0x2244,
        OD_TO_MSG_DATA(0x1, int16_t, IMU_ORIENT_CAN_TO_PHY, AGG_MEMBER(orient.w)),
        OD_TO_MSG_DATA(0x2, int16_t, IMU_ORIENT_CAN_TO_PHY, AGG_MEMBER(orient.x)),
        OD_TO_MSG_DATA(0x3, int16_t, IMU_ORIENT_CAN_TO_PHY, AGG_MEMBER(orient.y)),
        OD_TO_MSG_DATA(0x4, int16_t, IMU_ORIENT_CAN_TO_PHY, AGG_MEMBER(orient.z))
    )
);

#endif // CONFIG_VCU_SOURCE_IMU_CANOPEN

#ifdef CONFIG_VCU_SOURCE_GPS_CANOPEN

CANOPEN_OD_TO_MSG_DEFINE(msg_sensor_gps,
    AGG_DATA_INIT(0), K_MSEC(200), K_MSEC(160), K_MSEC(60), 0,
    OD_TO_MSG_ENTRY(0x2250,
        OD_TO_MSG_DATA(0x1, int32_t, GPS_LONGITUDE_CAN_TO_PHY, AGG_MEMBER(longitude)),
        OD_TO_MSG_DATA(0x2, int32_t, GPS_LATITUDE_CAN_TO_PHY, AGG_MEMBER(latitude))
    )
);

#endif // CONFIG_VCU_SOURCE_GPS_CANOPEN

#ifdef CONFIG_VCU_SOURCE_VEHICLE_STATE_CANOPEN

CANOPEN_OD_TO_MSG_DEFINE(msg_ctrl_vehicle_state,
    AGG_DATA_INIT(0), K_MSEC(10), K_MSEC(8), K_MSEC(3), 0,
    OD_TO_MSG_ENTRY(0x2090,
        OD_TO_MSG_DATA(0x1, int16_t, VELOCITY_CAN_TO_PHY, AGG_MEMBER(velocity.x)),
        OD_TO_MSG_DATA(0x2, int16_t, VELOCITY_CAN_TO_PHY, AGG_MEMBER(velocity.y))
    )
);

#endif // CONFIG_VCU_SOURCE_VEHICLE_STATE_CANOPEN

// clang-format on
