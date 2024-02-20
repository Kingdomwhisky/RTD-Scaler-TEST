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
// ID Code      : TypeC_Pmic_Sys_Solution.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"

#if(_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


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
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : ucSlaveAddr : I2C Slave Address
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicUnattachReset(void)
{
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    enumPowerDirection = enumPowerDirection;
    usVoltage = usVoltage;
    usCurrent = usCurrent;

#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
    ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, 0, 0, 0, 0);
#endif

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff(void)
{
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
    enumPowerDirection = enumPowerDirection;
    usVoltage = usVoltage;
    usCurrent = usCurrent;

#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
    ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, 0, 0, 0, 0);
#endif

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0(void) using 1
{
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
    enumPowerDirection = enumPowerDirection;
    usVoltage = usVoltage;
    usCurrent = usCurrent;

#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
    ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, 0, 0, 0, 0);
#endif

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT(void) using 3
{
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
    enumEn = enumEn;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : ucSlaveAddr : I2C Slave Address
//                bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(EnumTypeCPmicDischarge enumEn) using 1
{
    enumEn = enumEn;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : ucSlaveAddr : I2C Slave Address
//                bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_WDINT(EnumTypeCPmicDischarge enumEn) using 3
{
    enumEn = enumEn;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    enumSwitchControl = enumSwitchControl;
    enumPowerDirection = enumPowerDirection;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_EXINT0(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection) using 1
{
    enumSwitchControl = enumSwitchControl;
    enumPowerDirection = enumPowerDirection;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_WDINT(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection) using 3
{
    enumSwitchControl = enumSwitchControl;
    enumPowerDirection = enumPowerDirection;

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
    return _TYPE_C_PMIC_CONTROL_SUCCESS;
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
#endif // End of #if(_TYPE_C_PMIC_OCP_PROTECT_METHOD == _TYPE_C_PMIC_OCP_BY_POLLING_PMIC)
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)


