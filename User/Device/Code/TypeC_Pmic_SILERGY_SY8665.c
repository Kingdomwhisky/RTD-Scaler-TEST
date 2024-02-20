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
// ID Code      : TypeC_Pmic_SILERGY_SY8665.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"

#if(_TYPE_C_PMIC_TYPE == _PMIC_SY8665)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC SY8665
//--------------------------------------------------
#define _SY8665_SUBADDR_LENGTH              0x01

#define _SY8665_FUNCTION_SETTING1           0x00
#define _SY8665_FUNCTION_SETTING2           0x01
#define _SY8665_FUNCTION_SETTING3           0x02
#define _SY8665_PROTECT_SETTING1            0x03
#define _SY8665_PROTECT_SETTING2            0x04

#define _SY8665_STATE_REG                   0x05

//--------------------------------------------------
// Macros of PMIC STATUS
//--------------------------------------------------


//--------------------------------------------------
// Initial Setting
//--------------------------------------------------
#define _DISCHARGE_REG_1_80_K               0x00
#define _DISCHARGE_REG_1_44_K               0x01
#define _DISCHARGE_REG_1_08_K               0x10
#define _DISCHARGE_REG_1_72_K               0x11

#define _TURN_OFF_DISCHANGE_AT_ALL          0x00
#define _TURN_ON_DISCHANGE_AT_ALL           0x01

#define _MODE_ALL_OFF1                      0x00
#define _MODE_SOURCE_MODE1                  0x01 // Buck switching, NFET turn on,  PFET turn off.
#define _MODE_SOURCE_MODE2                  0x02 // Buck standby,   NFET turn on,  PFET turn on.
#define _MODE_SOURCE_MODE3                  0x03 // Buck standby,   NFET turn off, PFET turn on
#define _MODE_ALL_OFF2                      0x04
#define _MODE_SINK_MODE1                    0x05 // Buck is disabled, NFET turn on,  PFET turn on.
#define _MODE_SINK_MODE2                    0x06 // Buck standby,     NFET turn off, PFET turn on.
#define _MODE_SINK_MODE3                    0x07 // Buck is disabled, NFET turn off, PFET turn on.

#define _OUTPUT_VOLTAGE_0V                  0x00
#define _OUTPUT_VOLTAGE_3V                  0x01
#define _OUTPUT_VOLTAGE_5V                  (_OUTPUT_VOLTAGE_3V + 10)
#define _OUTPUT_VOLTAGE_7V                  (_OUTPUT_VOLTAGE_3V + 20)
#define _OUTPUT_VOLTAGE_9V                  (_OUTPUT_VOLTAGE_3V + 30)
#define _OUTPUT_VOLTAGE_12V                 (_OUTPUT_VOLTAGE_3V + 45)
#define _OUTPUT_VOLTAGE_15V                 (_OUTPUT_VOLTAGE_3V + 60)
#define _OUTPUT_VOLTAGE_20V                 (_OUTPUT_VOLTAGE_3V + 85)

#define _LIGHT_LOAD_PULSE_SKIP              0x00
#define _LIGHT_LOAD_BURST_MODE              0x01

#define _CABLE_IMPEDANCE_RCMP_0             0x01
#define _CABLE_IMPEDANCE_RCMP_20            0x01
#define _CABLE_IMPEDANCE_RCMP_40            0x02
#define _CABLE_IMPEDANCE_RCMP_60            0x03
#define _CABLE_IMPEDANCE_RCMP_70            0x04
#define _CABLE_IMPEDANCE_RCMP_100           0x05
#define _CABLE_IMPEDANCE_RCMP_120           0x06
#define _CABLE_IMPEDANCE_RCMP_140           0x07

#define _SY8665_INT_ENABLE                  0x00
#define _SY8665_INT_DISABLE                 0x01

#define _GO_BIT_INTERNAL_MODE               0x00
#define _GO_BIT_EXTERNAL_MODE               0x01

#define _BUCK_SWITCHING_250KHZ              0x00
#define _BUCK_SWITCHING_500KHZ              0x01
#define _BUCK_SWITCHING_750KHZ              0x02
#define _BUCK_SWITCHING_1MHZ                0x03

#define _LATCH_OFF_MODE                     0x00
#define _AUTO_RECOVER_MODE                  0x01

#define _OUTPUT_CURRENT_LIMIT_10MV          0x00
#define _OUTPUT_CURRENT_LIMIT_15MV          0x01
#define _OUTPUT_CURRENT_LIMIT_20MV          0x02
#define _OUTPUT_CURRENT_LIMIT_25MV          0x03
#define _OUTPUT_CURRENT_LIMIT_30MV          0x04
#define _OUTPUT_CURRENT_LIMIT_40MV          0x05
#define _OUTPUT_CURRENT_LIMIT_50MV          0x06
#define _OUTPUT_CURRENT_LIMIT_60MV          0x07

#define _V_VBUS_OVP_THRESHOLD_125P          0x00
#define _V_VBUS_OVP_THRESHOLD_120P          0x01
#define _V_VBUS_OVP_THRESHOLD_115P          0x02
#define _V_VBUS_OVP_THRESHOLD_110P          0x03

#define _V_SWO_UVP_THRESHOLD_50P            0x00
#define _V_SWO_UVP_THRESHOLD_60P            0x01
#define _V_SWO_UVP_THRESHOLD_70P            0x02
#define _V_SWO_UVP_THRESHOLD_80P            0x03

#define INDUCTOR_PEAK_CURRENT_LIMIT_5A      0x00
#define INDUCTOR_PEAK_CURRENT_LIMIT_7A      0x01



//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b3Mode : 3;
    BYTE b1DischargeEnableAllOff : 1;
    BYTE b1Fs1Reserved : 1;
    BYTE b2DischargeResistorSetting : 2;
    BYTE b1I2cReset : 1;

    BYTE b7OutputVoltageSetting : 7;
    BYTE b1Fs2Reserved : 1;

    BYTE b2Fs3Reserved : 2;
    BYTE b1InterruptEnable : 1;
    BYTE b1GoBit : 1;
    BYTE b3CableImpedanceCompensation : 3;
    BYTE b1LightLoadOperation : 1;

    BYTE b2Ps1Reserved : 2;
    BYTE b2BuckSwitchingFrequence : 2;
    BYTE b1Uvp : 1;
    BYTE b1Ovp : 1;
    BYTE b1Otp : 1;
    BYTE b1ReverseCurrentProtectionMode : 1;

    BYTE b1InductorPeakCurrentLimit : 1;
    BYTE b2VswoUvpThreshold : 2;
    BYTE b2VvbusOvpThreshod : 2;
    BYTE b3OutputCurrentLimit : 3;

    BYTE b1IntFlagUvp : 1;
    BYTE b1IntFlagOcp : 1;
    BYTE b1IntFlagOvp : 1;
    BYTE b1IntFlagOverTemperatureProtection : 1;
    BYTE b1IntFlagVoltageReversed : 1;
    BYTE b1IntFlagVbusAbsoluteMaximumOvp : 1;
    BYTE b1IntFlagReserved : 1;
    BYTE b1PowerGood : 1;

} StructSY8665RegisterMap;

//****************************************************************************
// CODE TABLES
//****************************************************************************
StructSY8665RegisterMap code g_stPmicInitialData =
{
    _MODE_ALL_OFF1,                     // Mode
    _TURN_ON_DISCHANGE_AT_ALL,          // Discharge Enable at All off
    0x00,                               // Reserved
    _DISCHARGE_REG_1_80_K,              // Discharge Resistor Setting
    _OFF,                               // Reset all registers to default value. Automatically clear to "0" after reset is done.

    _OUTPUT_VOLTAGE_5V,                 // Output Voltage Setting
    0x00,                               // Reserved

    0x00,                               // Reserved
    _SY8665_INT_DISABLE,                // Interrupt Disable
    _GO_BIT_INTERNAL_MODE,              // Go_bit
    _CABLE_IMPEDANCE_RCMP_100,          // Cable Impedance Compensation
    _LIGHT_LOAD_PULSE_SKIP,             // Light Load Operation

    0x00,                               // Reserved
    _BUCK_SWITCHING_250KHZ,             // Buck Switching Frequency Setting
    _AUTO_RECOVER_MODE,                 // UVP((Source Mode 1)
    _AUTO_RECOVER_MODE,                 // OVP((Source Mode 1)
    _AUTO_RECOVER_MODE,                 // OTP
    _AUTO_RECOVER_MODE,                 // Reverse Current Protection mode

    INDUCTOR_PEAK_CURRENT_LIMIT_5A,     // Inductor Peak Current Limit
    _V_SWO_UVP_THRESHOLD_60P,           // VSWO UVP Threshold (Buck mode)
    _V_VBUS_OVP_THRESHOLD_125P,         // VVBUS OVP Threshold (Buck mode)
    _OUTPUT_CURRENT_LIMIT_60MV,         // Output Current Limit

    0x00,                              // UVP Flag (Read Only)
    0x00,                              // OCP Flag (Read Only)
    0x00,                              // OVP Flag (Read Only)
    0x00,                              // Over temperature protection Flag (Read Only)
    0x00,                              // VBUS absolute maximum OVP Flag (Read Only)
    0x00,                              // Reserved
    0x00,                              // Power Good
};



//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSY8665RegisterMap g_stPMICData;


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
    ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 5, (BYTE *)(&g_stPMICData) + _SY8665_FUNCTION_SETTING1);
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
    ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 5, (BYTE *)(&g_stPMICData) + _SY8665_FUNCTION_SETTING1);
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 400 (Unit = 50mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    if(usVoltage > 2000) // maximum 20V
    {
        usVoltage = 2000;
    }

    // Set operation mode
    if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SNK)
    {
        // Sink mode1: 5V~20V@5A
        g_stPMICData.b3Mode = _MODE_SINK_MODE1;
    }
    else // _TYPE_C_PMIC_DIRECTION_SRC
    {
        if(usVoltage >= (2000))//20V (unit: 10mV)
        {
            // Source mode2: 20V@5A
            g_stPMICData.b3Mode = _MODE_SOURCE_MODE2;
        }
        else
        {
            // Source mode1: 3V~12V@5A, 15V@3A
            g_stPMICData.b3Mode = _MODE_SOURCE_MODE1;
        }
    }

    // Set VBUS Voltage
    if(usVoltage <= (300)) // 3V
    {
        g_stPMICData.b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V;
    }
    else
    {
        g_stPMICData.b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V + (((usVoltage) - 300)/ 20);
    }

    g_stPMICData.b2BuckSwitchingFrequence = _BUCK_SWITCHING_500KHZ;

    // Set VBUS Current Limit
    if(usCurrent <= 100) // < 1A (unit: 10mA)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_15MV;
    }
    else if(usCurrent <= 150)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_20MV;
    }
    else if(usCurrent <= 200)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_25MV;
    }
    else if(usCurrent <= 250)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_30MV;
    }
    else if(usCurrent <= 300)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_40MV;
    }
    else if(usCurrent <= 400)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_50MV;
    }
    else
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_60MV;
    }



    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 5, (BYTE *)(&g_stPMICData) + _SY8665_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
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
    // Set operation mode
    g_stPMICData.b3Mode = _MODE_ALL_OFF1;

    // Disable PMIC
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY8665_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 400 (Unit = 50mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent) using 1
{

    if(usVoltage > 2000) // maximum 20V
    {
        usVoltage = 2000;
    }

    // Set operation mode
    if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SNK)
    {
        // Sink mode1: 5V~20V@5A
        g_stPMICData.b3Mode = _MODE_SINK_MODE1;
    }
    else // _TYPE_C_PMIC_DIRECTION_SRC
    {
        if(usVoltage >= (2000))//20V (unit: 10mV)
        {
            // Source mode2: 20V@5A
            g_stPMICData.b3Mode = _MODE_SOURCE_MODE2;
        }
        else
        {
            // Source mode1: 3V~12V@5A, 15V@3A
            g_stPMICData.b3Mode = _MODE_SOURCE_MODE1;
        }
    }

    // Set VBUS Voltage
    if(usVoltage <= (300)) // 3V
    {
        g_stPMICData.b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V;
    }
    else
    {
        g_stPMICData.b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V + (((usVoltage) - 300)/ 20);
    }

    g_stPMICData.b2BuckSwitchingFrequence = _BUCK_SWITCHING_500KHZ;

    // Set VBUS Current Limit
    if(usCurrent <= 100) // < 1A (unit: 10mA)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_15MV;
    }
    else if(usCurrent <= 150)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_20MV;
    }
    else if(usCurrent <= 200)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_25MV;
    }
    else if(usCurrent <= 250)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_30MV;
    }
    else if(usCurrent <= 300)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_40MV;
    }
    else if(usCurrent <= 400)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_50MV;
    }
    else
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_60MV;
    }

    if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 5, (BYTE *)(&g_stPMICData) + _SY8665_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0(void)
{
    // Set operation mode
    g_stPMICData.b3Mode = _MODE_ALL_OFF1;

    // Disable PMIC
    if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY8665_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 400 (Unit = 50mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent) using 3
{

    if(usVoltage > 2000) // maximum 20V
    {
        usVoltage = 2000;
    }

    // Set operation mode
    if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SNK)
    {
        // Sink mode1: 5V~20V@5A
        g_stPMICData.b3Mode = _MODE_SINK_MODE1;
    }
    else // _TYPE_C_PMIC_DIRECTION_SRC
    {
        if(usVoltage >= (2000))//20V (unit: 10mV)
        {
            // Source mode2: 20V@5A
            g_stPMICData.b3Mode = _MODE_SOURCE_MODE2;
        }
        else
        {
            // Source mode1: 3V~12V@5A, 15V@3A
            g_stPMICData.b3Mode = _MODE_SOURCE_MODE1;
        }
    }

    // Set VBUS Voltage
    if(usVoltage <= (300)) // 3V
    {
        g_stPMICData.b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V;
    }
    else
    {
        g_stPMICData.b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V + (((usVoltage) - 300)/ 20);
    }

    g_stPMICData.b2BuckSwitchingFrequence = _BUCK_SWITCHING_500KHZ;

    // Set VBUS Current Limit
    if(usCurrent <= 100) // < 1A (unit: 10mA)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_15MV;
    }
    else if(usCurrent <= 150)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_20MV;
    }
    else if(usCurrent <= 200)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_25MV;
    }
    else if(usCurrent <= 250)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_30MV;
    }
    else if(usCurrent <= 300)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_40MV;
    }
    else if(usCurrent <= 400)
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_50MV;
    }
    else
    {
        g_stPMICData.b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_60MV;
    }

    if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 5, (BYTE *)(&g_stPMICData) + _SY8665_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT(void)
{
    // Set operation mode
    g_stPMICData.b3Mode = _MODE_ALL_OFF1;

    // Disable PMIC
    if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY8665_FUNCTION_SETTING1) == _FAIL)
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
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_DISABLE)
    {
        g_stPMICData.b1DischargeEnableAllOff = _TURN_OFF_DISCHANGE_AT_ALL;
    }
    else
    {
        g_stPMICData.b1DischargeEnableAllOff = _TURN_ON_DISCHANGE_AT_ALL;
    }

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
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY8665_FUNCTION_SETTING1) == _SUCCESS)
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
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_DISABLE)
    {
        g_stPMICData.b1DischargeEnableAllOff = _TURN_OFF_DISCHANGE_AT_ALL;
    }
    else
    {
        g_stPMICData.b1DischargeEnableAllOff = _TURN_ON_DISCHANGE_AT_ALL;
    }

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
    if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY8665_FUNCTION_SETTING1) == _SUCCESS)
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
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_DISABLE)
    {
        g_stPMICData.b1DischargeEnableAllOff = _TURN_OFF_DISCHANGE_AT_ALL;
    }
    else
    {
        g_stPMICData.b1DischargeEnableAllOff = _TURN_ON_DISCHANGE_AT_ALL;
    }

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
    if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY8665_FUNCTION_SETTING1) == _SUCCESS)
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
    if(ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _SY8665_STATE_REG, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _SY8665_STATE_REG) == _SUCCESS)
    {
        DebugMessageTypeC("0.Pmic:Power Good Status", g_stPMICData.b1PowerGood);
        DebugMessageTypeC("0.Pmic:Vbus Absolute Maximum Ovp", g_stPMICData.b1IntFlagVbusAbsoluteMaximumOvp);
        DebugMessageTypeC("0.Pmic:Voltage Reversed", g_stPMICData.b1IntFlagVoltageReversed);
        DebugMessageTypeC("0.Pmic:Over Temperature Protection", g_stPMICData.b1IntFlagOverTemperatureProtection);
        DebugMessageTypeC("0.Pmic:OVP Flag", g_stPMICData.b1IntFlagOvp);
        DebugMessageTypeC("0.Pmic:OCP Flag", g_stPMICData.b1IntFlagOcp);
        DebugMessageTypeC("0.Pmic:UVO Flag", g_stPMICData.b1IntFlagUvp);

        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }
    else
    {
        DebugMessageTypeC("0.Read Pmic State Fail", 0x99);
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
    return 0;
}
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_SY8665)


