/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode V4

    This file was automatically generated by CANopenEditor v4.2.3-0-gc1071ab+c1071ab3197f9bbf718123ec5bbabf449b2f7bab

    https://github.com/CANopenNode/CANopenNode
    https://github.com/CANopenNode/CANopenEditor

    DON'T EDIT THIS FILE MANUALLY !!!!
********************************************************************************

    File info:
        File Names:   OD.h; OD.c
        Project File: nturt_vcu.xdd
        File Version: 0

        Created:      2024/6/10 上午 09:31:00
        Created By:   National Taiwan University Racing Team
        Modified:     2025/7/13 下午 04:14:09
        Modified By:  National Taiwan University Racing Team

    Device Info:
        Vendor Name:  National Taiwan University Racing Team
        Vendor ID:    0
        Product Name: NTURT Vehicle Control Unit (VCU)
        Product ID:   0

        Description:  
*******************************************************************************/

#ifndef OD_H
#define OD_H
/*******************************************************************************
    Counters of OD objects
*******************************************************************************/
#define OD_CNT_NMT 1
#define OD_CNT_EM 1
#define OD_CNT_SYNC 1
#define OD_CNT_SYNC_PROD 1
#define OD_CNT_STORAGE 1
#define OD_CNT_TIME 1
#define OD_CNT_EM_PROD 1
#define OD_CNT_HB_CONS 1
#define OD_CNT_HB_PROD 1
#define OD_CNT_SDO_SRV 1
#define OD_CNT_SDO_CLI 1
#define OD_CNT_RPDO 15
#define OD_CNT_TPDO 6


/*******************************************************************************
    Sizes of OD arrays
*******************************************************************************/
#define OD_CNT_ARR_1003 16
#define OD_CNT_ARR_1010 4
#define OD_CNT_ARR_1011 4
#define OD_CNT_ARR_1016 3
#define OD_CNT_ARR_2001 16
#define OD_CNT_ARR_2240 3
#define OD_CNT_ARR_2241 3
#define OD_CNT_ARR_2243 3


/*******************************************************************************
    OD data declaration of all groups
*******************************************************************************/
typedef struct {
    uint32_t x1000_deviceType;
    char x1008_manufacturerDeviceName[10];
    char x1009_manufacturerHardwareVersion[7];
    char x100A_manufacturerSoftwareVersion[7];
} OD_ROM_t;

typedef struct {
    uint8_t x1001_errorRegister;
    uint8_t x1010_storeParameters_sub0;
    int32_t x1010_storeParameters[OD_CNT_ARR_1010];
    uint8_t x1011_restoreDefaultParameters_sub0;
    int32_t x1011_restoreDefaultParameters[OD_CNT_ARR_1011];
    uint32_t x2000_VCUStates;
    uint8_t x2001_VCUErrors_sub0;
    uint32_t x2001_VCUErrors[OD_CNT_ARR_2001];
    int16_t x2080_steerAngle;
    struct {
        uint8_t highestSub_indexSupported;
        uint8_t travel;
        int8_t raw1;
        int8_t raw2;
    } x2081_accelerator;
    struct {
        uint8_t highestSub_indexSupported;
        uint8_t travel;
        uint8_t raw1;
        uint8_t raw2;
    } x2082_brake;
    int16_t x2090_speed;
    uint8_t x2100_accumulatorStatus;
    uint32_t x2101_accumulatorVoltage;
    int16_t x2102_accumulatorCurrent;
    int16_t x2103_accumulatorTemperature;
    uint8_t x2104_accumulatorStateOfCharge;
    int16_t x2105_accumulatorCapacity;
    uint16_t x2130_invRLControlWord;
    uint16_t x2131_invRLStatusWord;
    int16_t x2132_invRLTargetTorque;
    struct {
        uint8_t highestSub_indexSupported;
        int16_t feedbackTorque;
        int16_t speed;
    } x2133_invRL_Motor;
    struct {
        uint8_t highestSub_indexSupported;
        uint16_t voltage;
        uint16_t current;
    } x2134_invRL_DCBus;
    struct {
        uint8_t highestSub_indexSupported;
        int16_t inverter;
        int16_t motor;
        int16_t microcontroller;
    } x2135_invRLTemperature;
    uint16_t x2140_invRRControlWord;
    uint16_t x2141_invRRStatusWord;
    int16_t x2142_invRRTargetTorque;
    struct {
        uint8_t highestSub_indexSupported;
        int16_t feedbackTorque;
        int16_t speed;
    } x2143_invRR_Motor;
    struct {
        uint8_t highestSub_indexSupported;
        uint16_t voltage;
        uint16_t current;
    } x2144_invRR_DCBus;
    struct {
        uint8_t highestSub_indexSupported;
        int16_t inverter;
        int16_t motor;
        int16_t microcontroller;
    } x2145_invRRTemperature;
    struct {
        uint8_t highestSub_indexSupported;
        uint8_t V_24;
        uint8_t I_24;
        uint8_t I_5;
        uint8_t I_5rpi;
    } x2200_power;
    struct {
        uint8_t highestSub_indexSupported;
        int16_t speed;
        int16_t torque;
        uint8_t tireTemperature;
    } x2212_wheelRL;
    struct {
        uint8_t highestSub_indexSupported;
        int16_t speed;
        int16_t torque;
        uint8_t tireTemperature;
    } x2213_wheelRR;
    struct {
        uint8_t highestSub_indexSupported;
        uint8_t dive;
        uint8_t roll;
    } x2220_suspensionF;
    struct {
        uint8_t highestSub_indexSupported;
        uint8_t dive;
        uint8_t roll;
    } x2221_suspensionR;
    uint8_t x2240_IMUAcceleration_sub0;
    int16_t x2240_IMUAcceleration[OD_CNT_ARR_2240];
    uint8_t x2241_IMUGyration_sub0;
    int16_t x2241_IMUGyration[OD_CNT_ARR_2241];
    uint8_t x2243_IMUEuler_sub0;
    int16_t x2243_IMUEuler[OD_CNT_ARR_2243];
    struct {
        uint8_t highestSub_indexSupported;
        int32_t latitude;
        int32_t longitude;
        int16_t altitude;
    } x2250_GPSPosition;
    struct {
        uint8_t highestSub_indexSupported;
        int16_t x;
        int16_t y;
    } x2251_GPSVelocity;
} OD_RAM_t;

typedef struct {
    uint32_t x1005_COB_ID_SYNCMessage;
    uint32_t x1006_communicationCyclePeriod;
    uint32_t x1007_synchronousWindowLength;
    uint32_t x1012_COB_IDTimeStampObject;
    uint32_t x1014_COB_ID_EMCY;
    uint16_t x1015_inhibitTimeEMCY;
    uint8_t x1016_consumerHeartbeatTime_sub0;
    uint32_t x1016_consumerHeartbeatTime[OD_CNT_ARR_1016];
    uint16_t x1017_producerHeartbeatTime;
    uint8_t x1019_synchronousCounterOverflowValue;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDClientToServer;
        uint32_t COB_IDServerToClient;
    } x1200_SDOServerParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDClientToServer;
        uint32_t COB_IDServerToClient;
        uint8_t node_IDOfTheSDOServer;
    } x1280_SDOClientParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1400_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1401_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1402_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1403_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1404_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1405_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1406_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1407_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1408_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1409_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x140A_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x140B_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x140C_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x140D_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x140E_RPDOCommunicationParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1600_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1601_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1602_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1603_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1604_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1605_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1606_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1607_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1608_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1609_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x160A_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x160B_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x160C_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x160D_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x160E_RPDOMappingParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1800_TPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1801_TPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1802_TPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1803_TPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1804_TPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1805_TPDOCommunicationParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1A00_TPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1A01_TPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1A02_TPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1A03_TPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1A04_TPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject1;
        uint32_t applicationObject2;
        uint32_t applicationObject3;
        uint32_t applicationObject4;
        uint32_t applicationObject5;
        uint32_t applicationObject6;
        uint32_t applicationObject7;
        uint32_t applicationObject8;
    } x1A05_TPDOMappingParameter;
} OD_PERSIST_COMM_t;

#ifndef OD_ATTR_ROM
#define OD_ATTR_ROM
#endif
extern OD_ATTR_ROM OD_ROM_t OD_ROM;

#ifndef OD_ATTR_RAM
#define OD_ATTR_RAM
#endif
extern OD_ATTR_RAM OD_RAM_t OD_RAM;

#ifndef OD_ATTR_PERSIST_COMM
#define OD_ATTR_PERSIST_COMM
#endif
extern OD_ATTR_PERSIST_COMM OD_PERSIST_COMM_t OD_PERSIST_COMM;

#ifndef OD_ATTR_OD
#define OD_ATTR_OD
#endif
extern OD_ATTR_OD OD_t *OD;


/*******************************************************************************
    Object dictionary entries - shortcuts
*******************************************************************************/
#define OD_ENTRY_H1000 &OD->list[0]
#define OD_ENTRY_H1001 &OD->list[1]
#define OD_ENTRY_H1003 &OD->list[2]
#define OD_ENTRY_H1005 &OD->list[3]
#define OD_ENTRY_H1006 &OD->list[4]
#define OD_ENTRY_H1007 &OD->list[5]
#define OD_ENTRY_H1008 &OD->list[6]
#define OD_ENTRY_H1009 &OD->list[7]
#define OD_ENTRY_H100A &OD->list[8]
#define OD_ENTRY_H1010 &OD->list[9]
#define OD_ENTRY_H1011 &OD->list[10]
#define OD_ENTRY_H1012 &OD->list[11]
#define OD_ENTRY_H1014 &OD->list[12]
#define OD_ENTRY_H1015 &OD->list[13]
#define OD_ENTRY_H1016 &OD->list[14]
#define OD_ENTRY_H1017 &OD->list[15]
#define OD_ENTRY_H1019 &OD->list[16]
#define OD_ENTRY_H1200 &OD->list[17]
#define OD_ENTRY_H1280 &OD->list[18]
#define OD_ENTRY_H1400 &OD->list[19]
#define OD_ENTRY_H1401 &OD->list[20]
#define OD_ENTRY_H1402 &OD->list[21]
#define OD_ENTRY_H1403 &OD->list[22]
#define OD_ENTRY_H1404 &OD->list[23]
#define OD_ENTRY_H1405 &OD->list[24]
#define OD_ENTRY_H1406 &OD->list[25]
#define OD_ENTRY_H1407 &OD->list[26]
#define OD_ENTRY_H1408 &OD->list[27]
#define OD_ENTRY_H1409 &OD->list[28]
#define OD_ENTRY_H140A &OD->list[29]
#define OD_ENTRY_H140B &OD->list[30]
#define OD_ENTRY_H140C &OD->list[31]
#define OD_ENTRY_H140D &OD->list[32]
#define OD_ENTRY_H140E &OD->list[33]
#define OD_ENTRY_H1600 &OD->list[34]
#define OD_ENTRY_H1601 &OD->list[35]
#define OD_ENTRY_H1602 &OD->list[36]
#define OD_ENTRY_H1603 &OD->list[37]
#define OD_ENTRY_H1604 &OD->list[38]
#define OD_ENTRY_H1605 &OD->list[39]
#define OD_ENTRY_H1606 &OD->list[40]
#define OD_ENTRY_H1607 &OD->list[41]
#define OD_ENTRY_H1608 &OD->list[42]
#define OD_ENTRY_H1609 &OD->list[43]
#define OD_ENTRY_H160A &OD->list[44]
#define OD_ENTRY_H160B &OD->list[45]
#define OD_ENTRY_H160C &OD->list[46]
#define OD_ENTRY_H160D &OD->list[47]
#define OD_ENTRY_H160E &OD->list[48]
#define OD_ENTRY_H1800 &OD->list[49]
#define OD_ENTRY_H1801 &OD->list[50]
#define OD_ENTRY_H1802 &OD->list[51]
#define OD_ENTRY_H1803 &OD->list[52]
#define OD_ENTRY_H1804 &OD->list[53]
#define OD_ENTRY_H1805 &OD->list[54]
#define OD_ENTRY_H1A00 &OD->list[55]
#define OD_ENTRY_H1A01 &OD->list[56]
#define OD_ENTRY_H1A02 &OD->list[57]
#define OD_ENTRY_H1A03 &OD->list[58]
#define OD_ENTRY_H1A04 &OD->list[59]
#define OD_ENTRY_H1A05 &OD->list[60]
#define OD_ENTRY_H2000 &OD->list[61]
#define OD_ENTRY_H2001 &OD->list[62]
#define OD_ENTRY_H2080 &OD->list[63]
#define OD_ENTRY_H2081 &OD->list[64]
#define OD_ENTRY_H2082 &OD->list[65]
#define OD_ENTRY_H2090 &OD->list[66]
#define OD_ENTRY_H2100 &OD->list[67]
#define OD_ENTRY_H2101 &OD->list[68]
#define OD_ENTRY_H2102 &OD->list[69]
#define OD_ENTRY_H2103 &OD->list[70]
#define OD_ENTRY_H2104 &OD->list[71]
#define OD_ENTRY_H2105 &OD->list[72]
#define OD_ENTRY_H2130 &OD->list[73]
#define OD_ENTRY_H2131 &OD->list[74]
#define OD_ENTRY_H2132 &OD->list[75]
#define OD_ENTRY_H2133 &OD->list[76]
#define OD_ENTRY_H2134 &OD->list[77]
#define OD_ENTRY_H2135 &OD->list[78]
#define OD_ENTRY_H2140 &OD->list[79]
#define OD_ENTRY_H2141 &OD->list[80]
#define OD_ENTRY_H2142 &OD->list[81]
#define OD_ENTRY_H2143 &OD->list[82]
#define OD_ENTRY_H2144 &OD->list[83]
#define OD_ENTRY_H2145 &OD->list[84]
#define OD_ENTRY_H2200 &OD->list[85]
#define OD_ENTRY_H2212 &OD->list[86]
#define OD_ENTRY_H2213 &OD->list[87]
#define OD_ENTRY_H2220 &OD->list[88]
#define OD_ENTRY_H2221 &OD->list[89]
#define OD_ENTRY_H2240 &OD->list[90]
#define OD_ENTRY_H2241 &OD->list[91]
#define OD_ENTRY_H2243 &OD->list[92]
#define OD_ENTRY_H2250 &OD->list[93]
#define OD_ENTRY_H2251 &OD->list[94]


/*******************************************************************************
    Object dictionary entries - shortcuts with names
*******************************************************************************/
#define OD_ENTRY_H1000_deviceType &OD->list[0]
#define OD_ENTRY_H1001_errorRegister &OD->list[1]
#define OD_ENTRY_H1003_pre_definedErrorField &OD->list[2]
#define OD_ENTRY_H1005_COB_ID_SYNCMessage &OD->list[3]
#define OD_ENTRY_H1006_communicationCyclePeriod &OD->list[4]
#define OD_ENTRY_H1007_synchronousWindowLength &OD->list[5]
#define OD_ENTRY_H1008_manufacturerDeviceName &OD->list[6]
#define OD_ENTRY_H1009_manufacturerHardwareVersion &OD->list[7]
#define OD_ENTRY_H100A_manufacturerSoftwareVersion &OD->list[8]
#define OD_ENTRY_H1010_storeParameters &OD->list[9]
#define OD_ENTRY_H1011_restoreDefaultParameters &OD->list[10]
#define OD_ENTRY_H1012_COB_IDTimeStampObject &OD->list[11]
#define OD_ENTRY_H1014_COB_ID_EMCY &OD->list[12]
#define OD_ENTRY_H1015_inhibitTimeEMCY &OD->list[13]
#define OD_ENTRY_H1016_consumerHeartbeatTime &OD->list[14]
#define OD_ENTRY_H1017_producerHeartbeatTime &OD->list[15]
#define OD_ENTRY_H1019_synchronousCounterOverflowValue &OD->list[16]
#define OD_ENTRY_H1200_SDOServerParameter &OD->list[17]
#define OD_ENTRY_H1280_SDOClientParameter &OD->list[18]
#define OD_ENTRY_H1400_RPDOCommunicationParameter &OD->list[19]
#define OD_ENTRY_H1401_RPDOCommunicationParameter &OD->list[20]
#define OD_ENTRY_H1402_RPDOCommunicationParameter &OD->list[21]
#define OD_ENTRY_H1403_RPDOCommunicationParameter &OD->list[22]
#define OD_ENTRY_H1404_RPDOCommunicationParameter &OD->list[23]
#define OD_ENTRY_H1405_RPDOCommunicationParameter &OD->list[24]
#define OD_ENTRY_H1406_RPDOCommunicationParameter &OD->list[25]
#define OD_ENTRY_H1407_RPDOCommunicationParameter &OD->list[26]
#define OD_ENTRY_H1408_RPDOCommunicationParameter &OD->list[27]
#define OD_ENTRY_H1409_RPDOCommunicationParameter &OD->list[28]
#define OD_ENTRY_H140A_RPDOCommunicationParameter &OD->list[29]
#define OD_ENTRY_H140B_RPDOCommunicationParameter &OD->list[30]
#define OD_ENTRY_H140C_RPDOCommunicationParameter &OD->list[31]
#define OD_ENTRY_H140D_RPDOCommunicationParameter &OD->list[32]
#define OD_ENTRY_H140E_RPDOCommunicationParameter &OD->list[33]
#define OD_ENTRY_H1600_RPDOMappingParameter &OD->list[34]
#define OD_ENTRY_H1601_RPDOMappingParameter &OD->list[35]
#define OD_ENTRY_H1602_RPDOMappingParameter &OD->list[36]
#define OD_ENTRY_H1603_RPDOMappingParameter &OD->list[37]
#define OD_ENTRY_H1604_RPDOMappingParameter &OD->list[38]
#define OD_ENTRY_H1605_RPDOMappingParameter &OD->list[39]
#define OD_ENTRY_H1606_RPDOMappingParameter &OD->list[40]
#define OD_ENTRY_H1607_RPDOMappingParameter &OD->list[41]
#define OD_ENTRY_H1608_RPDOMappingParameter &OD->list[42]
#define OD_ENTRY_H1609_RPDOMappingParameter &OD->list[43]
#define OD_ENTRY_H160A_RPDOMappingParameter &OD->list[44]
#define OD_ENTRY_H160B_RPDOMappingParameter &OD->list[45]
#define OD_ENTRY_H160C_RPDOMappingParameter &OD->list[46]
#define OD_ENTRY_H160D_RPDOMappingParameter &OD->list[47]
#define OD_ENTRY_H160E_RPDOMappingParameter &OD->list[48]
#define OD_ENTRY_H1800_TPDOCommunicationParameter &OD->list[49]
#define OD_ENTRY_H1801_TPDOCommunicationParameter &OD->list[50]
#define OD_ENTRY_H1802_TPDOCommunicationParameter &OD->list[51]
#define OD_ENTRY_H1803_TPDOCommunicationParameter &OD->list[52]
#define OD_ENTRY_H1804_TPDOCommunicationParameter &OD->list[53]
#define OD_ENTRY_H1805_TPDOCommunicationParameter &OD->list[54]
#define OD_ENTRY_H1A00_TPDOMappingParameter &OD->list[55]
#define OD_ENTRY_H1A01_TPDOMappingParameter &OD->list[56]
#define OD_ENTRY_H1A02_TPDOMappingParameter &OD->list[57]
#define OD_ENTRY_H1A03_TPDOMappingParameter &OD->list[58]
#define OD_ENTRY_H1A04_TPDOMappingParameter &OD->list[59]
#define OD_ENTRY_H1A05_TPDOMappingParameter &OD->list[60]
#define OD_ENTRY_H2000_VCUStates &OD->list[61]
#define OD_ENTRY_H2001_VCUErrors &OD->list[62]
#define OD_ENTRY_H2080_steerAngle &OD->list[63]
#define OD_ENTRY_H2081_accelerator &OD->list[64]
#define OD_ENTRY_H2082_brake &OD->list[65]
#define OD_ENTRY_H2090_speed &OD->list[66]
#define OD_ENTRY_H2100_accumulatorStatus &OD->list[67]
#define OD_ENTRY_H2101_accumulatorVoltage &OD->list[68]
#define OD_ENTRY_H2102_accumulatorCurrent &OD->list[69]
#define OD_ENTRY_H2103_accumulatorTemperature &OD->list[70]
#define OD_ENTRY_H2104_accumulatorStateOfCharge &OD->list[71]
#define OD_ENTRY_H2105_accumulatorCapacity &OD->list[72]
#define OD_ENTRY_H2130_invRLControlWord &OD->list[73]
#define OD_ENTRY_H2131_invRLStatusWord &OD->list[74]
#define OD_ENTRY_H2132_invRLTargetTorque &OD->list[75]
#define OD_ENTRY_H2133_invRL_Motor &OD->list[76]
#define OD_ENTRY_H2134_invRL_DCBus &OD->list[77]
#define OD_ENTRY_H2135_invRLTemperature &OD->list[78]
#define OD_ENTRY_H2140_invRRControlWord &OD->list[79]
#define OD_ENTRY_H2141_invRRStatusWord &OD->list[80]
#define OD_ENTRY_H2142_invRRTargetTorque &OD->list[81]
#define OD_ENTRY_H2143_invRR_Motor &OD->list[82]
#define OD_ENTRY_H2144_invRR_DCBus &OD->list[83]
#define OD_ENTRY_H2145_invRRTemperature &OD->list[84]
#define OD_ENTRY_H2200_power &OD->list[85]
#define OD_ENTRY_H2212_wheelRL &OD->list[86]
#define OD_ENTRY_H2213_wheelRR &OD->list[87]
#define OD_ENTRY_H2220_suspensionF &OD->list[88]
#define OD_ENTRY_H2221_suspensionR &OD->list[89]
#define OD_ENTRY_H2240_IMUAcceleration &OD->list[90]
#define OD_ENTRY_H2241_IMUGyration &OD->list[91]
#define OD_ENTRY_H2243_IMUEuler &OD->list[92]
#define OD_ENTRY_H2250_GPSPosition &OD->list[93]
#define OD_ENTRY_H2251_GPSVelocity &OD->list[94]


/*******************************************************************************
    OD config structure
*******************************************************************************/
#ifdef CO_MULTIPLE_OD
#define OD_INIT_CONFIG(config) {\
    (config).CNT_NMT = OD_CNT_NMT;\
    (config).ENTRY_H1017 = OD_ENTRY_H1017;\
    (config).CNT_HB_CONS = OD_CNT_HB_CONS;\
    (config).CNT_ARR_1016 = OD_CNT_ARR_1016;\
    (config).ENTRY_H1016 = OD_ENTRY_H1016;\
    (config).CNT_EM = OD_CNT_EM;\
    (config).ENTRY_H1001 = OD_ENTRY_H1001;\
    (config).ENTRY_H1014 = OD_ENTRY_H1014;\
    (config).ENTRY_H1015 = OD_ENTRY_H1015;\
    (config).CNT_ARR_1003 = OD_CNT_ARR_1003;\
    (config).ENTRY_H1003 = OD_ENTRY_H1003;\
    (config).CNT_SDO_SRV = OD_CNT_SDO_SRV;\
    (config).ENTRY_H1200 = OD_ENTRY_H1200;\
    (config).CNT_SDO_CLI = OD_CNT_SDO_CLI;\
    (config).ENTRY_H1280 = OD_ENTRY_H1280;\
    (config).CNT_TIME = OD_CNT_TIME;\
    (config).ENTRY_H1012 = OD_ENTRY_H1012;\
    (config).CNT_SYNC = OD_CNT_SYNC;\
    (config).ENTRY_H1005 = OD_ENTRY_H1005;\
    (config).ENTRY_H1006 = OD_ENTRY_H1006;\
    (config).ENTRY_H1007 = OD_ENTRY_H1007;\
    (config).ENTRY_H1019 = OD_ENTRY_H1019;\
    (config).CNT_RPDO = OD_CNT_RPDO;\
    (config).ENTRY_H1400 = OD_ENTRY_H1400;\
    (config).ENTRY_H1600 = OD_ENTRY_H1600;\
    (config).CNT_TPDO = OD_CNT_TPDO;\
    (config).ENTRY_H1800 = OD_ENTRY_H1800;\
    (config).ENTRY_H1A00 = OD_ENTRY_H1A00;\
    (config).CNT_LEDS = 0;\
    (config).CNT_GFC = 0;\
    (config).ENTRY_H1300 = NULL;\
    (config).CNT_SRDO = 0;\
    (config).ENTRY_H1301 = NULL;\
    (config).ENTRY_H1381 = NULL;\
    (config).ENTRY_H13FE = NULL;\
    (config).ENTRY_H13FF = NULL;\
    (config).CNT_LSS_SLV = 0;\
    (config).CNT_LSS_MST = 0;\
    (config).CNT_GTWA = 0;\
    (config).CNT_TRACE = 0;\
}
#endif

#endif /* OD_H */
