// glibc includes
#include <stddef.h>

// zephyr includes
#include <zephyr/kernel.h>

// canopennode includes
#include <canopennode.h>

// nturt includes
#include <nturt/canbus/canopen.h>
#include <nturt/canbus/convert.h>

// clang-format off

CANOPEN_OD_AGG_TO_MSG_DEFINE(msg_imu_data,
    AGG_DATA_INIT(0), K_MSEC(10), K_MSEC(8), K_MSEC(3),
    OD_AGG_ENTRY(0x2240,
        OD_AGG_DATA(0x1, int16_t, IMU_ACCEL_CAN_TO_PHY, AGG_MEMBER(accel.x)),
        OD_AGG_DATA(0x2, int16_t, IMU_ACCEL_CAN_TO_PHY, AGG_MEMBER(accel.y)),
        OD_AGG_DATA(0x3, int16_t, IMU_ACCEL_CAN_TO_PHY, AGG_MEMBER(accel.z))
    ),
    OD_AGG_ENTRY(0x2241,
        OD_AGG_DATA(0x1, int16_t, IMU_GYRO_CAN_TO_PHY, AGG_MEMBER(gyro.x)),
        OD_AGG_DATA(0x2, int16_t, IMU_GYRO_CAN_TO_PHY, AGG_MEMBER(gyro.y)),
        OD_AGG_DATA(0x3, int16_t, IMU_GYRO_CAN_TO_PHY, AGG_MEMBER(gyro.z))
    ),
    OD_AGG_ENTRY(0x2243,
        OD_AGG_DATA(0x1, int16_t, IMU_ORIENT_CAN_TO_PHY, AGG_MEMBER(orient.x)),
        OD_AGG_DATA(0x2, int16_t, IMU_ORIENT_CAN_TO_PHY, AGG_MEMBER(orient.y)),
        OD_AGG_DATA(0x3, int16_t, IMU_ORIENT_CAN_TO_PHY, AGG_MEMBER(orient.z))
    )
);

CANOPEN_OD_AGG_TO_MSG_DEFINE(msg_wheel_data,
    AGG_DATA_INIT(0), K_MSEC(10), K_MSEC(8), K_MSEC(3),
    OD_AGG_ENTRY(0x2133,
        OD_AGG_DATA(0x1, int16_t, INV_SPEED_CAN_TO_PHY, AGG_MEMBER(speed.rl)),
        OD_AGG_DATA(0x2, int16_t, INV_TORQUE_CAN_TO_PHY, AGG_MEMBER(speed.rl))
    ),

    OD_AGG_ENTRY(0x2143,
        OD_AGG_DATA(0x1, int16_t, INV_SPEED_CAN_TO_PHY, AGG_MEMBER(speed.rr)),
        OD_AGG_DATA(0x2, int16_t, INV_TORQUE_CAN_TO_PHY, AGG_MEMBER(speed.rr))
    )
);

CANOPEN_OD_AGG_TO_MSG_DEFINE(msg_acc,
    AGG_DATA_INIT(0), K_MSEC(100), K_MSEC(80), K_MSEC(30),
    OD_AGG_ENTRY(0x2100, OD_AGG_DATA(0x0, uint8_t, IDENTITY, AGG_MEMBER(ok))),
    OD_AGG_ENTRY(0x2101, OD_AGG_DATA(0x0, uint32_t, ACC_VOLT_CAN_TO_PHY, AGG_MEMBER(volt))),
    OD_AGG_ENTRY(0x2102, OD_AGG_DATA(0x0, int16_t, ACC_CURRENT_CAN_TO_PHY, AGG_MEMBER(current))),
    OD_AGG_ENTRY(0x2103, OD_AGG_DATA(0x0, int16_t, ACC_TEMP_CAN_TO_PHY, AGG_MEMBER(temp))),
    OD_AGG_ENTRY(0x2104, OD_AGG_DATA(0x0, uint8_t, IDENTITY, AGG_MEMBER(soc))),
    OD_AGG_ENTRY(0x2105, OD_AGG_DATA(0x0, int16_t, ACC_CAPACITY_CAN_TO_PHY, AGG_MEMBER(capacity)))
);

CANOPEN_OD_AGG_TO_MSG_DEFINE(msg_inv,
    AGG_DATA_INIT(0), K_MSEC(100), K_MSEC(80), K_MSEC(30),
    OD_AGG_ENTRY(0x2131, OD_AGG_DATA(0x0, uint16_t, IDENTITY, AGG_MEMBER(status.rl))),
    OD_AGG_ENTRY(0x2134,
        OD_AGG_DATA(0x1, uint16_t, INV_VOLT_CAN_TO_PHY, AGG_MEMBER(volt.rl)),
        OD_AGG_DATA(0x2, uint16_t, INV_CURRENT_CAN_TO_PHY, AGG_MEMBER(current.rl))
    ),
    OD_AGG_ENTRY(0x2135,
        OD_AGG_DATA(0x1, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(inv_temp.rl)),
        OD_AGG_DATA(0x2, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(motor_temp.rl)),
        OD_AGG_DATA(0x3, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(mcu_temp.rl))
    ),

    OD_AGG_ENTRY(0x2141, OD_AGG_DATA(0x0, uint16_t, IDENTITY, AGG_MEMBER(status.rr))),
    OD_AGG_ENTRY(0x2144,
        OD_AGG_DATA(0x1, uint16_t, INV_VOLT_CAN_TO_PHY, AGG_MEMBER(volt.rr)),
        OD_AGG_DATA(0x2, uint16_t, INV_CURRENT_CAN_TO_PHY, AGG_MEMBER(current.rr))
    ),
    OD_AGG_ENTRY(0x2145,
        OD_AGG_DATA(0x1, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(inv_temp.rr)),
        OD_AGG_DATA(0x2, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(motor_temp.rr)),
        OD_AGG_DATA(0x3, int16_t, INV_TEMP_CAN_TO_PHY, AGG_MEMBER(mcu_temp.rr))
    )
);

// clang-format on
