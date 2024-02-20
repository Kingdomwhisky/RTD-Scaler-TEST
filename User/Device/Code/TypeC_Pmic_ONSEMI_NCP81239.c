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
// ID Code      : TypeC_Pmic_ONSEMI_NCP81239.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"

#if(_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC NCP81239
//--------------------------------------------------
#define _NCP81239_SUBADDR_LENGTH            0x01
#define _NCP81239_CTRL_REG00                0x00
#define _NCP81239_CTRL_REG01                0x01
#define _NCP81239_CTRL_REG02                0x02
#define _NCP81239_CTRL_REG03                0x03
#define _NCP81239_CTRL_REG04                0x04
#define _NCP81239_CTRL_REG05                0x05
#define _NCP81239_CTRL_REG06                0x06
#define _NCP81239_CTRL_REG07                0x07
#define _NCP81239_CTRL_REG08                0x08
#define _NCP81239_CTRL_REG09                0x09
#define _NCP81239_CTRL_REG0A                0x0A
#define _NCP81239_CTRL_REG10                0x10
#define _NCP81239_CTRL_REG11                0x11
#define _NCP81239_CTRL_REG12                0x12
#define _NCP81239_CTRL_REG13                0x13
#define _NCP81239_CTRL_REG14                0x14
#define _NCP81239_CTRL_REG15                0x15

//--------------------------------------------------
// Definitions of Pmic NCP81239 Control
//--------------------------------------------------
#define _TUNE_RISE                          0
#define _TUNE_FALL                          1
#define _PMIC_SOURCE                        1
#define _PMIC_SINK                          0

//--------------------------------------------------
// NCP81239 Initial Setting
//--------------------------------------------------
#define _ADDR_01_VBUS                       0x32    // 5V
#define _ADDR_02_SLEW_RATE                  0x00
#define _ADDR_03_PWM_FREQ                   0x00
#define _ADDR_05_OCP_CLIM_POS               0x00
#define _ADDR_05_OCP_CLIM_NEG               0x00
#define _ADDR_06_CS1_CLIND                  0x03    // 5A
#define _ADDR_06_CS2_CLIND                  0x03    // 5A
#define _ADDR_09_INT_MASK_CS_CLIND          0x00
#define _ADDR_09_INT_MASK_OVP               0x00
#define _ADDR_09_INT_MASK_OCP_P             0x00
#define _ADDR_09_INT_MASK_PG_INT            0x00
#define _ADDR_09_INT_MASK_TSD               0x00
#define _ADDR_09_INT_MASK_UVP               0x00
#define _ADDR_09_INT_MASK_VCHN              0x00
#define _ADDR_09_INT_MASK_IIC_ACK           0x00
#define _ADDR_09_INT_MASK_SHUT_DOWN         0x00

//--------------------------------------------------
// Definitions of PMIC FUNCTION
//--------------------------------------------------
#define _TYPE_C_PMIC_VOLTAGE_OFFSET         1      // unit: 0.1V

//--------------------------------------------------
// Macros of PMIC STATUS
//--------------------------------------------------


//--------------------------------------------------
// Macros of PMIC CHECK START
//--------------------------------------------------

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b2CR00Reserved : 2;
    BYTE b1CR00EnMask : 1;
    BYTE b1CR00EnInternal : 1;
    BYTE b4CR00Reserved : 4;

    BYTE ucCR01DacTarget;

    BYTE b2CR02SlewRate : 2;
    BYTE b6CR02Reserved : 6;

    BYTE b3CR03PwmFreq : 3;
    BYTE b1CR03Reserved : 1;
    BYTE b1CR03DacLsb : 1;
    BYTE b3CR03Reserved : 3;

    BYTE b1CR04Pfet : 1;
    BYTE b1CR04Cfet : 1;
    BYTE b3CR04Reserved : 3;
    BYTE b1CR04Cs2DisCharge : 1;
    BYTE b2CR04Reserved : 2;

    BYTE b2CR05OcpClimPos : 2;
    BYTE b2CR05Reserved1 : 2;
    BYTE b2CR05OcpClimNeg : 2;
    BYTE b2CR05Reserved2 : 2;

    BYTE b2CR06Cs1Clind : 2;
    BYTE b2CR06Cs2Clind : 2;
    BYTE b4CR06Reserved : 4;

    BYTE b3CR07LoGmAmpSetting : 3;
    BYTE b1CR07GmManual : 1;
    BYTE b3CR07HiGmAmpSetting : 3;
    BYTE b1CR07GmAmpConfig : 1;

    BYTE b2CR08AmuxTrigger : 2;
    BYTE b3CR08AmuxSel : 3;
    BYTE b1CR08DisAdc : 1;
    BYTE b2CR08Reserved : 2;

    BYTE b1CR09IntMaskCsClind : 1;
    BYTE b1CR09IntMaskOvp : 1;
    BYTE b1CR09IntMaskOcpP : 1;
    BYTE b1CR09IntMaskPgInt : 1;
    BYTE b1CR09IntMaskTsd : 1;
    BYTE b1CR09IntMaskUvp : 1;
    BYTE b1CR09IntMaskVchn : 1;
    BYTE b1CR09IntMaskI2cAck : 1;

    BYTE b1CR0AIntMaskShutDown : 1;
    BYTE b7CR0AReserved : 7;

    BYTE b1CR0BPmicDirection : 1;
    BYTE b7CR0BReserved : 7;
    BYTE ucCR0CReserved;
    BYTE ucCR0DReserved;
    BYTE ucCR0EReserved;
    BYTE ucCR0FReserved;

    BYTE ucCR10VfbValue;
    BYTE ucCR11VinValue;
    BYTE ucCR12Cs2Value;
    BYTE ucCR13Cs1Value;

    BYTE b1CR14IntCsClindFlag : 1;
    BYTE b1CR14IntOvpFlag : 1;
    BYTE b1CR14IntOcpPFlag : 1;
    BYTE b1CR14IntPgIntFlag : 1;
    BYTE b1CR14IntTsdFlag : 1;
    BYTE b1CR14IntUvpFlag : 1;
    BYTE b1CR14IntVchnFlag : 1;
    BYTE b1CR14IntI2cAckFlag : 1;

    BYTE b1CR15IntShutDownFlag : 1;
    BYTE b7CR15Reserved : 7;
} StructNCP81239RegisterMap;

//****************************************************************************
// CODE TABLES
//****************************************************************************
StructNCP81239RegisterMap code g_stPmicInitialData =
{
    0x00,                              // Reserved
    0x00,                              // Hardware enable selected
    0x00,                              // Software control disable
    0x00,                              // Reserved

    _ADDR_01_VBUS,                     // VBUS setting is 5V

    _ADDR_02_SLEW_RATE,                // Slwe rate by define
    0x00,                              // Reserved

    _ADDR_03_PWM_FREQ,                 // by define
    0x00,                              // PWM freq Reserved
    0x00,                              // DAC resolution is 10mV
    0x00,                              // Reserved

    0x00,                              // PFET is disable
    0x00,                              // CFET is disable
    0x00,                              // Reserved
    0x00,                              // CS2 discharge is disable
    0x00,                              // Reserved

    _ADDR_05_OCP_CLIM_POS,             // internal positive current limit by define
    0x00,                              // Reserved
    _ADDR_05_OCP_CLIM_NEG,             // internal negative current limit by define
    0x00,                              // Reserved

    _ADDR_06_CS1_CLIND,                // CS1 positive current limit
    _ADDR_06_CS2_CLIND,                // CS2 positive current limit
    0x00,                              // Reserved

    0x01,                              // Low Amp GM value
    0x01,                              // register of amp gm settings
    0x05,                              // High Amp GM value
    0x00,                              // register of amp gm config

    0x00,                              // ADC Trigger
    0x00,                              // ADC MUX select
    0x00,                              // ADC is enable
    0x00,                              // Reserved

    _ADDR_09_INT_MASK_CS_CLIND,        // cs_clind int flag enable by define
    _ADDR_09_INT_MASK_OVP,             // OVP int flag enable by define
    _ADDR_09_INT_MASK_OCP_P,           // OCP_P int flag enable by define
    _ADDR_09_INT_MASK_PG_INT,          // PG int flag enable by define
    _ADDR_09_INT_MASK_TSD,             // TSD int flag enable by define
    _ADDR_09_INT_MASK_UVP,             // UVP int flag enable by define
    _ADDR_09_INT_MASK_VCHN,            // VCHN int flag enable by define
    _ADDR_09_INT_MASK_IIC_ACK,         // IIC_ACK int flag enable by define

    _ADDR_09_INT_MASK_SHUT_DOWN,       // SHUT_DOWN int flag enable by define
    0x00,                              // Reserved

    _PMIC_SINK,                        // Source/Sink status
    0x00,                              // Reserved
    0x00,                              // Reserved
    0x00,                              // Reserved
    0x00,                              // Reserved
    0x00,                              // Reserved

    0x00,                              // Vfb value(Read Only)
    0x00,                              // Vin value(Read Only)
    0x00,                              // CS2 value(Read Only)
    0x00,                              // CS1 value(Read Only)

    0x00,                              // CsClind flag(Read Only)
    0x00,                              // OVP flag(Read Only)
    0x00,                              // OCP_P flag(Read Only)
    0x00,                              // PG flag(Read Only)
    0x00,                              // TSD flag(Read Only)
    0x00,                              // UVP flag(Read Only)
    0x00,                              // VCHN flag(Read Only)
    0x00,                              // IIC_ACK flag(Read Only)

    0x00,                              // SHUT_DOWN flag(Read Only)
    0x00,                              // Reserved
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructNCP81239RegisterMap g_stPMICData;


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
    g_stPMICData = g_stPmicInitialData;
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : ucSlaveAddr : I2C Slave Address
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicUnattachReset(void)
{
    PCB_PMIC_POWER(_POWER_OFF);
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE ucPowerOnCount = 0;

    usCurrent = usCurrent;

    if(usVoltage > 2100)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(enumPowerDirection == _PMIC_SOURCE)
    {
        g_stPMICData.b1CR0BPmicDirection = _PMIC_SOURCE;
    }
    else
    {
        g_stPMICData.b1CR0BPmicDirection = _PMIC_SINK;
        PCB_PMIC_POWER(_POWER_OFF);
        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }

    // Set VBUS Voltage
    g_stPMICData.ucCR01DacTarget = (BYTE)((usVoltage / 10) + _TYPE_C_PMIC_VOLTAGE_OFFSET);

    if(PCB_PMIC_POWER_DETECT() == _POWER_OFF)
    {
        // Enable PMIC from power saving mode
        PCB_PMIC_POWER(_POWER_ON);

        // Wait for PMIC power ON
        ucPowerOnCount = 200;
        while(--ucPowerOnCount)
        {
            // Delay 5us
        }

        if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG00) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }
    else
    {
        if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG01) == _FAIL)
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
    PCB_PMIC_POWER(_POWER_OFF);

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
    BYTE ucPowerOnCount = 0;

    usCurrent = usCurrent;

    if(usVoltage > 2100)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(enumPowerDirection == _PMIC_SOURCE)
    {
        g_stPMICData.b1CR0BPmicDirection = _PMIC_SOURCE;
    }
    else
    {
        g_stPMICData.b1CR0BPmicDirection = _PMIC_SINK;
        PCB_PMIC_POWER(_POWER_OFF);
        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }

    // Set VBUS Voltage
    g_stPMICData.ucCR01DacTarget = (BYTE)((usVoltage / 10) + _TYPE_C_PMIC_VOLTAGE_OFFSET);

    if(PCB_PMIC_POWER_DETECT() == _POWER_OFF)
    {
        // Enable PMIC from power saving mode
        PCB_PMIC_POWER(_POWER_ON);

        // Wait for PMIC power ON
        ucPowerOnCount = 200;
        while(--ucPowerOnCount)
        {
            // Delay 5us
        }

        if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG00) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }
    else
    {
        if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG01) == _FAIL)
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
    PCB_PMIC_POWER(_POWER_OFF);

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent) using 3
{
    BYTE ucPowerOnCount = 0;

    usCurrent = usCurrent;

    if(usVoltage > 2100)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(enumPowerDirection == _PMIC_SOURCE)
    {
        g_stPMICData.b1CR0BPmicDirection = _PMIC_SOURCE;
    }
    else
    {
        g_stPMICData.b1CR0BPmicDirection = _PMIC_SINK;
        PCB_PMIC_POWER(_POWER_OFF);
        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }

    // Set VBUS Voltage
    g_stPMICData.ucCR01DacTarget = (BYTE)((usVoltage / 10) + _TYPE_C_PMIC_VOLTAGE_OFFSET);

    if(PCB_PMIC_POWER_DETECT() == _POWER_OFF)
    {
        // Enable PMIC from power saving mode
        PCB_PMIC_POWER(_POWER_ON);

        // Wait for PMIC power ON
        ucPowerOnCount = 200;
        while(--ucPowerOnCount)
        {
            // Delay 5us
        }

        if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG00) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }
    else
    {
        if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG01) == _FAIL)
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
    PCB_PMIC_POWER(_POWER_OFF);

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
    g_stPMICData.b1CR04Pfet = enumEn;

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
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _NCP81239_CTRL_REG04, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG04) == _SUCCESS)
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
    g_stPMICData.b1CR04Pfet = enumEn;

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
    if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _NCP81239_CTRL_REG04, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG04) == _SUCCESS)
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
    g_stPMICData.b1CR04Pfet = enumEn;

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
    if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _NCP81239_CTRL_REG04, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG04) == _SUCCESS)
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
        PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
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
        PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
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
        PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
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

    ucResult = ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _NCP81239_CTRL_REG10, _NCP81239_SUBADDR_LENGTH, 6, (BYTE *)(&g_stPMICData) + _NCP81239_CTRL_REG10);

    DebugMessageTypeC("0.Pmic:VFB Value", g_stPMICData.ucCR10VfbValue);
    DebugMessageTypeC("0.Pmic:Vin Value", g_stPMICData.ucCR11VinValue);
    DebugMessageTypeC("0.Pmic:CS2 Value", g_stPMICData.ucCR12Cs2Value);
    DebugMessageTypeC("0.Pmic:CS1 Value", g_stPMICData.ucCR13Cs1Value);
    DebugMessageTypeC("0.Pmic:Cs Clind Flag", g_stPMICData.b1CR14IntCsClindFlag);
    DebugMessageTypeC("0.Pmic:VBUS OVP Flag", g_stPMICData.b1CR14IntOvpFlag);
    DebugMessageTypeC("0.Pmic:OCP_P Flag", g_stPMICData.b1CR14IntOcpPFlag);
    DebugMessageTypeC("0.Pmic:Power Good Flag", g_stPMICData.b1CR14IntPgIntFlag);
    DebugMessageTypeC("0.Pmic:Thermal Sensor Flag", g_stPMICData.b1CR14IntTsdFlag);
    DebugMessageTypeC("0.Pmic:VBUS UVP Flag", g_stPMICData.b1CR14IntUvpFlag);
    DebugMessageTypeC("0.Pmic:Vchn Flag", g_stPMICData.b1CR14IntVchnFlag);
    DebugMessageTypeC("0.Pmic:IIC ACK Flag", g_stPMICData.b1CR14IntI2cAckFlag);
    DebugMessageTypeC("0.Pmic:Shut Down Flag", g_stPMICData.b1CR15IntShutDownFlag);

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
    return 0;
}
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)

