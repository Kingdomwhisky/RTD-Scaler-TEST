/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : TypeC_Pmic_SILERGY_SY9329.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"

#if(_TYPE_C_PMIC_TYPE == _PMIC_SY9329)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC SY9329
//--------------------------------------------------
#define _SY9329_SUBADDR_LENGTH                      0x01
#define _SY9329_CTRL_REG1                           0x00
#define _SY9329_CTRL_REG2                           0x01
#define _SY9329_PROTECT_REG1                        0x02
#define _SY9329_PROTECT_REG2                        0x03
#define _SY9329_STATE_REG                           0x04
#define _SY9329_INT_REG                             0x05
#define _SY9329_BAT_VALUE_REG                       0x06
#define _SY9329_VBUS_VALUE_REG                      0x07
#define _SY9329_CURRENT_VALUE_REG                   0x08

//--------------------------------------------------
// Definitions of Voltage(10mV) and Current(10mA)
//--------------------------------------------------
#define _VBUS_VOLTAGE_5V                            500
#define _VBUS_VOLTAGE_7V                            700
#define _VBUS_VOLTAGE_9V                            900
#define _VBUS_VOLTAGE_12V                           1200
#define _VBUS_VOLTAGE_15V                           1500
#define _VBUS_VOLTAGE_20V                           2000

//--------------------------------------------------
// Definitions of Pmic SY9329 Control
//--------------------------------------------------
#define _TUNE_RISE                                  0
#define _TUNE_FALL                                  1
#define _PMIC_SOURCE                                0
#define _PMIC_SINK                                  1

//--------------------------------------------------
// Macros of PMIC STATUS
//--------------------------------------------------


//--------------------------------------------------
// Initial Setting
//--------------------------------------------------
#define _SY9329_ADDR_00_REGULATOR_ENABLE            0x00 // Disable
#define _SY9329_ADDR_00_LOWBATTERY_VOLTAGE          0x00 // 10.2V
#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#define _SY9329_ADDR_00_ADC_ACTIVE                  0x01 // Active
#define _SY9329_ADDR_00_ADC_MODE                    0x01 // Auto Detect Mode
#else
#define _SY9329_ADDR_00_ADC_ACTIVE                  0x00 // Inactive
#define _SY9329_ADDR_00_ADC_MODE                    0x00 // Single Detect Mode
#endif
#define _SY9329_ADDR_00_VBUS_DISCHARGE              0x01 // Inactive Discharge

#define _SY9329_ADDR_01_SWITCH_FREQ                 0x01 // 500kHz
#define _SY9329_ADDR_01_VOLTAGE_SETTING             0x00 // 5V
#define _SY9329_ADDR_01_VOLTAGE_ADJUST              0x02 // +-0%

#define _SY9329_ADDR_02_CURRENT_LIMIT               0x03 // 33mV
#define _SY9329_ADDR_02_VBUS_OVP_SETTING            0x02 // 120%
#define _SY9329_ADDR_02_VBUS_UVP_SETTING            0x02 // 70%

#define _SY9329_ADDR_03_LOCP_SETTING                0x00 // 6A
#define _SY9329_ADDR_03_LOCP_MODE                   0x00 // Latch-off
#define _SY9329_ADDR_03_VBUS_UVP_MODE               0x00 // Latch-off
#define _SY9329_ADDR_03_OTP_MODE                    0x00 // Latch-off
#define _SY9329_ADDR_03_BIDIRECTIONAL_MODE          0x00 // Source Mode


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1CR1Reserved : 1;
    BYTE b1VBUSDischarge : 1;
    BYTE b1ADCMode : 1;
    BYTE b1ADCEnable : 1;
    BYTE b3LowBATVoltageSetting : 3;
    BYTE b1PMICEnable : 1;

    BYTE b3VBUSAdjust : 3;
    BYTE b3VBUSSetting : 3;
    BYTE b2SwitchFreq : 2;

    BYTE b1PS1Reserved : 1;
    BYTE b2UVPSetting : 2;
    BYTE b2OVPSetting : 2;
    BYTE b3VOCPSetting : 3;

    BYTE b2PS2Reserved : 2;
    BYTE b1BiDirSetting : 1;
    BYTE b1OTPMode : 1;
    BYTE b1UVPMode : 1;
    BYTE b1LOCPMode : 1;
    BYTE b2LOCPSetting : 2;

    BYTE b5SRReserved : 5;
    BYTE b1BATStatus : 1;
    BYTE b1BATVBUSRelation : 1;
    BYTE b1PowerGoodState : 1;

    BYTE b3IRReserved : 3;
    BYTE b1OTPFlag : 1;
    BYTE b1UVPFlag : 1;
    BYTE b1LOCPFlag : 1;
    BYTE b1VOCPFlag : 1;
    BYTE b1ADCReady : 1;

    BYTE ucBATValue;
    BYTE ucVBUSValue;
    BYTE ucVBUSCurrentValue;
} StructSY9329RegisterMap;

//****************************************************************************
// CODE TABLES
//****************************************************************************
StructSY9329RegisterMap code g_stPmicInitialData =
{
    0x00,                               // Reserved
    _SY9329_ADDR_00_VBUS_DISCHARGE,     // Discharge Disable
    _SY9329_ADDR_00_ADC_MODE,           // ADC Mode select single detect mode
    _SY9329_ADDR_00_ADC_ACTIVE,         // ADC Disable
    _SY9329_ADDR_00_LOWBATTERY_VOLTAGE, // Low Battery setting by define
    _SY9329_ADDR_00_REGULATOR_ENABLE,   // Regulator Disable

    _SY9329_ADDR_01_VOLTAGE_ADJUST,     // VBUS Adjust 0%
    _SY9329_ADDR_01_VOLTAGE_SETTING,    // VBUS Output 5V
    _SY9329_ADDR_01_SWITCH_FREQ,        // Switching Freq by define

    0x00,                               // Reserved
    _SY9329_ADDR_02_VBUS_UVP_SETTING,   // UVP Threshold by define
    _SY9329_ADDR_02_VBUS_OVP_SETTING,   // OVP Threshold by define
    _SY9329_ADDR_02_CURRENT_LIMIT,      // OCP 2.5A

    0x00,                               // Reserved
    _SY9329_ADDR_03_BIDIRECTIONAL_MODE, // Direction is source mode
    _SY9329_ADDR_03_OTP_MODE,           // OTP mode by define
    _SY9329_ADDR_03_VBUS_UVP_MODE,      // UVP mode by define
    _SY9329_ADDR_03_LOCP_MODE,          // LOCP mode by define
    _SY9329_ADDR_03_LOCP_SETTING,       // LOCP by define

    0x00,                               // Reserved
    0x00,                               // BAT Power status (Read Only)
    0x00,                               // BAT/VBUS relation (Read Only)
    0x00,                               // Power Good Status (Read Only)

    0x00,                               // Reserved
    0x00,                               // OTP Flag (Read Only)
    0x00,                               // UVP Flag (Read Only)
    0x00,                               // LOCP Flag (Read Only)
    0x00,                               // OCP Flag (Read Only)
    0x00,                               // ADC Data Ready (Read Only)

    0x00,                               // BAT Voltage Value (Read Only)
    0x00,                               // VBUS Voltage Value (Read Only)
    0x00,                               // VBUS Current Value (Read Only)
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSY9329RegisterMap g_stPMICData;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ExternalDeviceInterfaceTypeCPmicACOnInitial(void);
void ExternalDeviceInterfaceTypeCPmicUnattachReset(void);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff(void);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0(void);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT(void);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge(EnumTypeCPmicDischarge enumEn);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(EnumTypeCPmicDischarge enumEn);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_WDINT(EnumTypeCPmicDischarge enumEn);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_EXINT0(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_WDINT(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_EXINT0(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_WDINT(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType);
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicReadPpsOperationModeStatus_EXINT0(void);
#endif
#if(_TYPE_C_PMIC_DEBUG == _ON)
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicDebugCheckStatus(void);
#endif
#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
WORD ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PMIC Initial Settings
// Input Value  : ucSlaveAddr : I2C Slave Address
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicACOnInitial(void)
{
    // Set PMIC Data initial value
    g_stPMICData = g_stPmicInitialData;

    PCB_PMIC_POWER(_POWER_ON);

    // Initial Pmic Value
    ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1);
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : ucSlaveAddr : I2C Slave Address
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicUnattachReset(void)
{
    // Set PMIC Data initial value
    g_stPMICData = g_stPmicInitialData;

    PCB_PMIC_POWER(_POWER_OFF);
    ScalerTimerDelayXms(5);

    PCB_PMIC_POWER(_POWER_ON);
    ScalerTimerDelayXms(10);

    // Initial Pmic Value
    ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1);
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    g_stPMICData.b1BiDirSetting = !enumPowerDirection;

    // Set VBUS Voltage
    switch(usVoltage)
    {
        case _VBUS_VOLTAGE_5V:
            g_stPMICData.b3VBUSSetting = 0x00;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 5;
            break;

        case _VBUS_VOLTAGE_7V:
            g_stPMICData.b3VBUSSetting = 0x03;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_9V:
            g_stPMICData.b3VBUSSetting = 0x04;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_12V:
            g_stPMICData.b3VBUSSetting = 0x05;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_15V:
            g_stPMICData.b3VBUSSetting = 0x06;
            g_stPMICData.b2SwitchFreq = 0x00;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_20V:
            g_stPMICData.b3VBUSSetting = 0x07;
            g_stPMICData.b2SwitchFreq = 0x00;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        default:

            break;
    }

    // Set VBUS Current Limit
    if(usCurrent <= 100)
    {
        g_stPMICData.b3VOCPSetting = 0x00;
    }
    else if(usCurrent <= 150)
    {
        g_stPMICData.b3VOCPSetting = 0x01;
    }
    else if(usCurrent <= 200)
    {
        g_stPMICData.b3VOCPSetting = 0x02;
    }
    else if(usCurrent <= 250)
    {
        g_stPMICData.b3VOCPSetting = 0x03;
    }
    else if(usCurrent <= 300)
    {
        g_stPMICData.b3VOCPSetting = 0x04;
    }
    else if(usCurrent <= 400)
    {
        g_stPMICData.b3VOCPSetting = 0x05;
    }
    else
    {
        g_stPMICData.b3VOCPSetting = 0x06;
    }

    if(g_stPMICData.b1PMICEnable == _OFF)
    {
        g_stPMICData.b1PMICEnable = _ON;

        // Enable PMIC
        if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }
    else
    {
        if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG2, _SY9329_SUBADDR_LENGTH, 3, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG2) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff(void)
{
    g_stPMICData.b1PMICEnable = _OFF;

    // Disable PMIC
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent) using 1
{
    g_stPMICData.b1BiDirSetting = !enumPowerDirection;

    // Set VBUS Voltage
    switch(usVoltage)
    {
        case _VBUS_VOLTAGE_5V:
            g_stPMICData.b3VBUSSetting = 0x00;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 5;
            break;

        case _VBUS_VOLTAGE_7V:
            g_stPMICData.b3VBUSSetting = 0x03;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_9V:
            g_stPMICData.b3VBUSSetting = 0x04;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_12V:
            g_stPMICData.b3VBUSSetting = 0x05;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_15V:
            g_stPMICData.b3VBUSSetting = 0x06;
            g_stPMICData.b2SwitchFreq = 0x00;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_20V:
            g_stPMICData.b3VBUSSetting = 0x07;
            g_stPMICData.b2SwitchFreq = 0x00;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        default:

            break;
    }

    // Set VBUS Current Limit
    if(usCurrent <= 100)
    {
        g_stPMICData.b3VOCPSetting = 0x00;
    }
    else if(usCurrent <= 150)
    {
        g_stPMICData.b3VOCPSetting = 0x01;
    }
    else if(usCurrent <= 200)
    {
        g_stPMICData.b3VOCPSetting = 0x02;
    }
    else if(usCurrent <= 250)
    {
        g_stPMICData.b3VOCPSetting = 0x03;
    }
    else if(usCurrent <= 300)
    {
        g_stPMICData.b3VOCPSetting = 0x04;
    }
    else if(usCurrent <= 400)
    {
        g_stPMICData.b3VOCPSetting = 0x05;
    }
    else
    {
        g_stPMICData.b3VOCPSetting = 0x06;
    }

    if(g_stPMICData.b1PMICEnable == _OFF)
    {
        g_stPMICData.b1PMICEnable = _ON;

        // Enable PMIC
        if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }
    else
    {
        if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG2, _SY9329_SUBADDR_LENGTH, 3, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG2) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0(void) using 1
{
    g_stPMICData.b1PMICEnable = _OFF;

    // Disable PMIC
    if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent) using 3
{
    g_stPMICData.b1BiDirSetting = !enumPowerDirection;

    // Set VBUS Voltage
    switch(usVoltage)
    {
        case _VBUS_VOLTAGE_5V:
            g_stPMICData.b3VBUSSetting = 0x00;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 5;
            break;

        case _VBUS_VOLTAGE_7V:
            g_stPMICData.b3VBUSSetting = 0x03;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_9V:
            g_stPMICData.b3VBUSSetting = 0x04;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_12V:
            g_stPMICData.b3VBUSSetting = 0x05;
            g_stPMICData.b2SwitchFreq = 0x01;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_15V:
            g_stPMICData.b3VBUSSetting = 0x06;
            g_stPMICData.b2SwitchFreq = 0x00;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        case _VBUS_VOLTAGE_20V:
            g_stPMICData.b3VBUSSetting = 0x07;
            g_stPMICData.b2SwitchFreq = 0x00;
            g_stPMICData.b3VBUSAdjust = 2;
            break;

        default:

            break;
    }

    // Set VBUS Current Limit
    if(usCurrent <= 100)
    {
        g_stPMICData.b3VOCPSetting = 0x00;
    }
    else if(usCurrent <= 150)
    {
        g_stPMICData.b3VOCPSetting = 0x01;
    }
    else if(usCurrent <= 200)
    {
        g_stPMICData.b3VOCPSetting = 0x02;
    }
    else if(usCurrent <= 250)
    {
        g_stPMICData.b3VOCPSetting = 0x03;
    }
    else if(usCurrent <= 300)
    {
        g_stPMICData.b3VOCPSetting = 0x04;
    }
    else if(usCurrent <= 400)
    {
        g_stPMICData.b3VOCPSetting = 0x05;
    }
    else
    {
        g_stPMICData.b3VOCPSetting = 0x06;
    }

    if(g_stPMICData.b1PMICEnable == _OFF)
    {
        g_stPMICData.b1PMICEnable = _ON;

        // Enable PMIC
        if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }
    else
    {
        if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG2, _SY9329_SUBADDR_LENGTH, 3, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG2) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT(void) using 3
{
    g_stPMICData.b1PMICEnable = _OFF;

    // Disable PMIC
    if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : ucSlaveAddr : I2C Slave Address
//                bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge(EnumTypeCPmicDischarge enumEn)
{
    // Set PMIC VBUS Discharge status
    g_stPMICData.b1VBUSDischarge = !enumEn;

    // PCB Control
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_ON);
    }
    else
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_OFF);
    }

    // Disable Pmic VBUS Discharge
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _SUCCESS)
    {
        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }
    else
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : ucSlaveAddr : I2C Slave Address
//                bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(EnumTypeCPmicDischarge enumEn) using 1
{
    // Set PMIC VBUS Discharge status
    g_stPMICData.b1VBUSDischarge = !enumEn;

    // PCB Control
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_ON);
    }
    else
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_OFF);
    }

    // Disable Pmic VBUS Discharge
    if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _SUCCESS)
    {
        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }
    else
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : ucSlaveAddr : I2C Slave Address
//                bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_WDINT(EnumTypeCPmicDischarge enumEn) using 3
{
    // Set PMIC VBUS Discharge status
    g_stPMICData.b1VBUSDischarge = !enumEn;

    // PCB Control
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_ON);
    }
    else
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_OFF);
    }

    // Disable Pmic VBUS Discharge
    if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CTRL_REG1) == _SUCCESS)
    {
        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }
    else
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);
        }
        else
        {
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_ON);
        }
    }
    else
    {
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_EXINT0(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection) using 1
{
    if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);
        }
        else
        {
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_ON);
        }
    }
    else
    {
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_WDINT(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection) using 3
{
    if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);
        }
        else
        {
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_ON);
        }
    }
    else
    {
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType)
{
    enumPowerDirection= enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_EXINT0(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType) using 1
{
    enumPowerDirection= enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_WDINT(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType) using 3
{
    enumPowerDirection= enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Read Output Status
// Input Value  : None
// Output Value : Output Mode (Fixed Voltage/PPS)
//--------------------------------------------------
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicReadPpsOperationModeStatus_EXINT0(void) using 1
{
    return _TYPE_C_PMIC_NONE_MODE_OPERATION;
}
#endif // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)

#if(_TYPE_C_PMIC_DEBUG == _ON)
//--------------------------------------------------
// Description  : PMIC Status
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicDebugCheckStatus(void)
{
    BYTE ucResult = 0;

    ucResult = ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_STATE_REG, _SY9329_SUBADDR_LENGTH, 5, (BYTE *)(&g_stPMICData) + _SY9329_STATE_REG);

    DebugMessageTypeC("0.Pmic:Power Good Status", g_stPMICData.b1PowerGoodState);
    DebugMessageTypeC("0.Pmic:Relation Status", g_stPMICData.b1BATVBUSRelation);
    DebugMessageTypeC("0.Pmic:Battery Status", g_stPMICData.b1BATStatus);
    DebugMessageTypeC("0.Pmic:VBUS OCP Flag", g_stPMICData.b1VOCPFlag);
    DebugMessageTypeC("0.Pmic:Inductor OCP Flag", g_stPMICData.b1LOCPFlag);
    DebugMessageTypeC("0.Pmic:VBUS UVP Flag", g_stPMICData.b1UVPFlag);
    DebugMessageTypeC("0.Pmic:OTP Flag", g_stPMICData.b1OTPFlag);
    DebugMessageTypeC("0.Pmic:Battery Voltage Value", g_stPMICData.ucBATValue);
    DebugMessageTypeC("0.Pmic:VBUS Voltage Value", g_stPMICData.ucVBUSValue);
    DebugMessageTypeC("0.Pmic:VBUS Current Value", g_stPMICData.ucVBUSCurrentValue);

    if (ucResult == _SUCCESS)
    {
        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }
    else
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }
}
#endif // End of #if(_TYPE_C_PMIC_DEBUG == _ON)

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
//--------------------------------------------------
// Description  : PMIC VBUS Current Reading
// Input Value  : None
// Output Value : usCurrent : 0 ~ 500 (Unit = 10mA)
//--------------------------------------------------
WORD ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue(void)
{
    WORD usCurrent;

    // Get Current value from PMIC's ADC
    ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9329_CURRENT_VALUE_REG, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9329_CURRENT_VALUE_REG);

    // Translate PMIC's Current Unit to 10mA/bit
    usCurrent = ((WORD)(((DWORD)g_stPMICData.ucVBUSCurrentValue * 100 * 6) / 256));

    // Show data
    DebugMessageTypeC("Pmic:Current Value(Bit)", g_stPMICData.ucVBUSCurrentValue);
    DebugMessageTypeC("Pmic:Current Value(10mA)", usCurrent);

    return usCurrent;
}
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_SY9329)


