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
// ID Code      : TypeC_Pmic_SILERGY_SY9228.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"

#if(_TYPE_C_PMIC_TYPE == _PMIC_SY9228)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC SY9228
//--------------------------------------------------
#define _SY9228_SUBADDR_LENGTH              0x01
#define _SY9228_FUNCTION_SETTING1           0x00
#define _SY9228_FUNCTION_SETTING2           0x01
#define _SY9228_VOUT_SETTING                0x02
#define _SY9228_PROTECT_REG1                0x03
#define _SY9228_PROTECT_REG2                0x04
#define _SY9228_STATE_REG                   0x05
#define _SY9228_INT_REG                     0x06
#define _SY9228_VIN_VALUE_REG               0x07
#define _SY9228_VOUT_VALUE_REG              0x08
#define _SY9228_CURRENT_VALUE_REG           0x09
#define _SY9228_VENDER_ID                   0x0A

//--------------------------------------------------
// Initial Setting
//--------------------------------------------------
#define _ADDR_00_REGULATOR_ENABLE           0x00        // Disable
#define _ADDR_00_SWITCH_FREQ                0x00        // 250kHz
#define _ADDR_00_ADC_ACTIVE                 0x01        // Active
#define _ADDR_00_ADC_MODE                   0x01        // Auto Detect Mode
#define _ADDR_00_VBUS_DISCHARGE             0x01        // Inactive Discharge
#define _ADDR_00_GATE_ENABLE                0x00        // Disable
#define _ADDR_01_CABLE_COMPENSATION         0x02        // 100m Ohm
#define _ADDR_02_VOUT_SETTING               0x32        // 5V
#define _ADDR_03_VOUT_OCP_SETTING           0x06        // 50mV
#define _ADDR_03_VOUT_OVP_SETTING           0x00        // 115%
#define _ADDR_03_SLEW_RATE                  0x03        // 4mV/uS
#define _ADDR_04_LOCP_SETTING               0x00        // 6A
#define _ADDR_04_VOUT_UVP_SETTING           0x02        // 70%
#define _ADDR_04_LOCP_MODE                  0x00        // Latch off
#define _ADDR_04_VOUT_UVP_MODE              0x00        // Latch off
#define _ADDR_04_OTP_MODE                   0x01        // Auto recover
#define _ADDR_04_VOUT_OVP_MODE              0x01        // Auto recover

//--------------------------------------------------
// Definitions of Pmic SY9228 Control
//--------------------------------------------------
#define _PMIC_SOURCE                        1
#define _PMIC_SINK                          0


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1FS1Reserved : 1;
    BYTE b1GateEnable : 1;
    BYTE b1VOUTDischarge : 1;
    BYTE b1ADCMode : 1;
    BYTE b1ADCEnable : 1;
    BYTE b2SwitchFreq : 2;
    BYTE b1PMICEnable : 1;

    BYTE b5FS2Reserved : 5;
    BYTE b3CableCompensation : 3;

    BYTE ucOutputVoltageSetting;

    BYTE b1PS1Reserved : 1;
    BYTE b2SlewRate : 2;
    BYTE b2OVPSetting : 2;
    BYTE b3VOCPSetting : 3;

    BYTE b1OVPMode : 1;
    BYTE b1OTPMode : 1;
    BYTE b1UVPMode : 1;
    BYTE b1LOCPMode : 1;
    BYTE b2UVPSetting : 2;
    BYTE b2LOCPSetting : 2;

    BYTE b6SRReserved : 6;
    BYTE b1VinVoutRelation : 1;
    BYTE b1PowerGoodState : 1;

    BYTE b2IRReserved : 2;
    BYTE b1OVPFlag : 1;
    BYTE b1OTPFlag : 1;
    BYTE b1UVPFlag : 1;
    BYTE b1LOCPFlag : 1;
    BYTE b1VOCPFlag : 1;
    BYTE b1ADCReady : 1;

    BYTE ucInputVoltageValue;
    BYTE ucOutputVoltageValue;
    BYTE ucOutputCurrentValue;

    BYTE b4VenderID : 4;
    BYTE b4Product : 4;
} StructSY9228RegisterMap;

//****************************************************************************
// CODE TABLES
//****************************************************************************
StructSY9228RegisterMap code g_stPmicInitialData =
{
    0x00,                              // Reserved
    _ADDR_00_GATE_ENABLE,              // Gate Enable by define
    _ADDR_00_VBUS_DISCHARGE,           // Discharge Enable by define
    _ADDR_00_ADC_MODE,                 // ADC Mode select by define
    _ADDR_00_ADC_ACTIVE,               // ADC Active select by define
    _ADDR_00_SWITCH_FREQ,              // Switching Freq by define
    _ADDR_00_REGULATOR_ENABLE,         // Regulator Enable by define

    0x00,                              // Reserved
    _ADDR_01_CABLE_COMPENSATION,       // Cable Impedance Compensation by define

    _ADDR_02_VOUT_SETTING,             // Output Voltage by define

    0x00,                              // Reserved
    _ADDR_03_SLEW_RATE,                // OVP Threshold by define
    _ADDR_03_VOUT_OVP_SETTING,         // OVP Threshold by define
    _ADDR_03_VOUT_OCP_SETTING,         // OCP Threshold by define

    _ADDR_04_VOUT_OVP_MODE,            // OVP mode by define
    _ADDR_04_OTP_MODE,                 // OTP mode by define
    _ADDR_04_VOUT_UVP_MODE,            // UVP mode by define
    _ADDR_04_LOCP_MODE,                // LOCP mode by define
    _ADDR_04_VOUT_UVP_SETTING,         // UVP Threshold by define
    _ADDR_04_LOCP_SETTING,             // LOCP by define

    0x00,                              // Reserved
    0x00,                              // Input/Output Voltage relation (Read Only)
    0x00,                              // Power Good Status (Read Only)

    0x00,                              // Reserved
    0x00,                              // OVP Flag (Read Only)
    0x00,                              // OTP Flag (Read Only)
    0x00,                              // UVP Flag (Read Only)
    0x00,                              // LOCP Flag (Read Only)
    0x00,                              // OCP Flag (Read Only)
    0x00,                              // ADC Data Ready (Read Only)

    0x00,                              // Input Voltage Value (Read Only)
    0x00,                              // Output Voltage Value (Read Only)
    0x00,                              // Output Current Value (Read Only)

    0x00,                              // Product (Read Only)
    0x00,                              // Vender ID (Read Only)
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSY9228RegisterMap g_stPMICData;

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
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicACOnInitial(void)
{
    // Set PMIC Data initial value
    g_stPMICData = g_stPmicInitialData;

    PCB_PMIC_POWER(_POWER_ON);

    // Initial Pmic Value
    ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 5, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1);
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : None
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
    ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 5, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1);
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    enumPowerDirection = enumPowerDirection;

    // Set Pmic config
    g_stPMICData.b1PMICEnable = _ON;
    g_stPMICData.b1GateEnable = _ON;
    PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);

    if(enumPowerDirection == _PMIC_SOURCE)
     {
        if((usVoltage > 2100) || (usVoltage < 360))
        {
            return _FAIL;
        }

        // Set VOUT Voltage
        g_stPMICData.ucOutputVoltageSetting = (BYTE)(usVoltage / 10);

        // Set Switch Frequency
        if(usVoltage >= 1330)
        {
            g_stPMICData.b2SwitchFreq = 0x00;
        }
        else if(usVoltage >= 610)
        {
            g_stPMICData.b2SwitchFreq = 0x01;
        }
        else
        {
            g_stPMICData.b2SwitchFreq = 0x02;
        }

        // Set VBUS Current Limit
        if(usCurrent <= 50)
        {
            g_stPMICData.b3VOCPSetting = 0x00;
        }
        else if(usCurrent <= 100)
        {
            g_stPMICData.b3VOCPSetting = 0x01;
        }
        else if(usCurrent <= 150)
        {
            g_stPMICData.b3VOCPSetting = 0x02;
        }
        else if(usCurrent <= 200)
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
        else if(usCurrent <= 500)
        {
            g_stPMICData.b3VOCPSetting = 0x06;
        }
        else
        {
            g_stPMICData.b3VOCPSetting = 0x07;
        }

        if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _FAIL)
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
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent) using 1
{
    enumPowerDirection = enumPowerDirection;

    // Set Pmic config
    g_stPMICData.b1PMICEnable = _ON;
    g_stPMICData.b1GateEnable = _ON;
    PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);

    if(enumPowerDirection == _PMIC_SOURCE)
     {
        if((usVoltage > 2100) || (usVoltage < 360))
        {
            return _FAIL;
        }

        // Set VOUT Voltage
        g_stPMICData.ucOutputVoltageSetting = (BYTE)(usVoltage / 10);

        // Set Switch Frequency
        if(usVoltage >= 1330)
        {
            g_stPMICData.b2SwitchFreq = 0x00;
        }
        else if(usVoltage >= 610)
        {
            g_stPMICData.b2SwitchFreq = 0x01;
        }
        else
        {
            g_stPMICData.b2SwitchFreq = 0x02;
        }

        // Set VBUS Current Limit
        if(usCurrent <= 50)
        {
            g_stPMICData.b3VOCPSetting = 0x00;
        }
        else if(usCurrent <= 100)
        {
            g_stPMICData.b3VOCPSetting = 0x01;
        }
        else if(usCurrent <= 150)
        {
            g_stPMICData.b3VOCPSetting = 0x02;
        }
        else if(usCurrent <= 200)
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
        else if(usCurrent <= 500)
        {
            g_stPMICData.b3VOCPSetting = 0x06;
        }
        else
        {
            g_stPMICData.b3VOCPSetting = 0x07;
        }

        if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _FAIL)
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
    if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent) using 3
{
    enumPowerDirection = enumPowerDirection;

    // Set Pmic config
    g_stPMICData.b1PMICEnable = _ON;
    g_stPMICData.b1GateEnable = _ON;
    PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);

    if(enumPowerDirection == _PMIC_SOURCE)
     {
        if((usVoltage > 2100) || (usVoltage < 360))
        {
            return _FAIL;
        }

        // Set VOUT Voltage
        g_stPMICData.ucOutputVoltageSetting = (BYTE)(usVoltage / 10);

        // Set Switch Frequency
        if(usVoltage >= 1330)
        {
            g_stPMICData.b2SwitchFreq = 0x00;
        }
        else if(usVoltage >= 610)
        {
            g_stPMICData.b2SwitchFreq = 0x01;
        }
        else
        {
            g_stPMICData.b2SwitchFreq = 0x02;
        }

        // Set VBUS Current Limit
        if(usCurrent <= 50)
        {
            g_stPMICData.b3VOCPSetting = 0x00;
        }
        else if(usCurrent <= 100)
        {
            g_stPMICData.b3VOCPSetting = 0x01;
        }
        else if(usCurrent <= 150)
        {
            g_stPMICData.b3VOCPSetting = 0x02;
        }
        else if(usCurrent <= 200)
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
        else if(usCurrent <= 500)
        {
            g_stPMICData.b3VOCPSetting = 0x06;
        }
        else
        {
            g_stPMICData.b3VOCPSetting = 0x07;
        }

        if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 4, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT(void) using 3
{
    g_stPMICData.b1PMICEnable = _OFF;

    // Disable PMIC
    if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge(EnumTypeCPmicDischarge enumEn)
{
    // Set PMIC VBUS Discharge status
    g_stPMICData.b1VOUTDischarge = !enumEn;

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
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _SUCCESS)
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
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(EnumTypeCPmicDischarge enumEn) using 1
{
    // Set PMIC VBUS Discharge status
    g_stPMICData.b1VOUTDischarge = !enumEn;

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
    if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _SUCCESS)
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
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_WDINT(EnumTypeCPmicDischarge enumEn) using 3
{
    // Set PMIC VBUS Discharge status
    g_stPMICData.b1VOUTDischarge = !enumEn;

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
    if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _SUCCESS)
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
        g_stPMICData.b1GateEnable = _ON;

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
        g_stPMICData.b1GateEnable = _OFF;
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
    }

    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
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
        g_stPMICData.b1GateEnable = _ON;

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
        g_stPMICData.b1GateEnable = _OFF;
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
    }

    if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
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
        g_stPMICData.b1GateEnable = _ON;

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
        g_stPMICData.b1GateEnable = _OFF;
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
    }

    if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
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

    ucResult = ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_STATE_REG, _SY9228_SUBADDR_LENGTH, 6, (BYTE *)(&g_stPMICData) + _SY9228_STATE_REG);

    DebugMessageTypeC("5.Pmic:Power Good Status", g_stPMICData.b1PowerGoodState);
    DebugMessageTypeC("5.Pmic:Relation Status", g_stPMICData.b1VinVoutRelation);
    DebugMessageTypeC("6.Pmic:Output OCP Flag", g_stPMICData.b1VOCPFlag);
    DebugMessageTypeC("6.Pmic:Inductor OCP Flag", g_stPMICData.b1LOCPFlag);
    DebugMessageTypeC("6.Pmic:Output UVP Flag", g_stPMICData.b1UVPFlag);
    DebugMessageTypeC("6.Pmic:OTP Flag", g_stPMICData.b1OTPFlag);
    DebugMessageTypeC("6.Pmic:Output UVP Flag", g_stPMICData.b1OVPFlag);
    DebugMessageTypeC("7.Pmic:Input Voltage Value", g_stPMICData.ucInputVoltageValue);
    DebugMessageTypeC("8.Pmic:Output Voltage Value", g_stPMICData.ucOutputVoltageValue);
    DebugMessageTypeC("9.Pmic:Output Current Value", g_stPMICData.ucOutputCurrentValue);
    DebugMessageTypeC("A.Pmic:Product ID", g_stPMICData.b4Product);
    DebugMessageTypeC("A.Pmic:Vender ID", g_stPMICData.b4VenderID);

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
    ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY9228_CURRENT_VALUE_REG, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY9228_CURRENT_VALUE_REG);

    // Translate PMIC's Current Unit to 10mA/bit
    usCurrent = ((WORD)(((DWORD)g_stPMICData.ucOutputCurrentValue * 100 * 6) / 256));

    // Show data
    DebugMessageTypeC("Pmic:Current Value(Bit)", g_stPMICData.ucOutputCurrentValue);
    DebugMessageTypeC("Pmic:Current Value(10mA)", usCurrent);

    return usCurrent;
}
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_SY9228)

