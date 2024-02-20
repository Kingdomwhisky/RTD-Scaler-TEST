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
// ID Code      : ScalerCommonTypeCPmic.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_TYPE_C_PMIC__

#include "ScalerFunctionInclude.h"

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON) && (_TYPE_C_PMIC_TYPE != _PMIC_NONE))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of TYPE C Hardware IIC
//--------------------------------------------------
#define _TYPE_C_HW_IIC_BUFFER_SIZE          24
#define _TYPE_C_HW_IIC_READ_SIZE            24
#define _TYPE_C_HW_IIC_WRITE_SIZE           24

#if(_TYPE_C_PMIC_HW_IIC_SPEED == _HW_IIC_LOW_SPEED_100K)
#define _TYPE_C_HW_IIC_SLPC_14318K          0x26 // 38
#define _TYPE_C_HW_IIC_SHPC_14318K          0x22 // 34
#define _TYPE_C_HW_IIC_SLPC_28000K          0x2F // 47
#define _TYPE_C_HW_IIC_SHPC_28000K          0x2F // 47
#define _TYPE_C_HW_IIC_STA_SUGPIO_C         0x36 // 54
#define _TYPE_C_HW_IIC_TOR                  0x47 // 71
#else
#define _TYPE_C_HW_IIC_SLPC_14318K          0x0C // 12
#define _TYPE_C_HW_IIC_SHPC_14318K          0x04 // 4
#define _TYPE_C_HW_IIC_SLPC_28000K          0x0E // 14
#define _TYPE_C_HW_IIC_SHPC_28000K          0x06 // 6
#define _TYPE_C_HW_IIC_STA_SUGPIO_C         0x09 // 9
#define _TYPE_C_HW_IIC_TOR                  0x23 // 35
#endif

#define _TYPE_C_HW_IIC_FTPC                 0x03 // 3
#define _TYPE_C_HW_IIC_FD10_14318K          0x01 // 1
#define _TYPE_C_HW_IIC_FD10_28000K          0x02 // 2

//--------------------------------------------------
// Definitions of PMIC FUNCTION
//--------------------------------------------------
#define _TYPE_C_PMIC_FW_OVP_THRESHOLD       130    // unit: %
#define _TYPE_C_PMIC_FW_UVP_THRESHOLD       66     // unit: %
#define _TYPE_C_PMIC_FW_UVP_PPS_THRESHOLD   295    // unit: 0.01V
#define _TYPE_C_ADC_MAX_CURRENT             8      // unit: A
#define _TYPE_C_ADC_MAX_VOLTAGE             240UL  // unit: 0.1V
#define _TYPE_C_PMIC_SHORT_VOLTAGE          30UL   // unit: 0.1V
#define _TYPE_C_ADC_SHORT_THRESHOLD         (WORD)(_TYPE_C_PMIC_SHORT_VOLTAGE * 1024 / _TYPE_C_ADC_MAX_VOLTAGE)

//--------------------------------------------------
// Definitions of PMIC Protection Process Method
//--------------------------------------------------
#define _TYPE_C_PMIC_ERROR_RECOVERY         0
#define _TYPE_C_PMIC_HARD_RESET             1
#define _TYPE_C_PMIC_PROTECTION_METHOD      _TYPE_C_PMIC_HARD_RESET

//--------------------------------------------------
// Definitions of PMIC Minimum Current
//--------------------------------------------------
#define _TYPE_C_PMIC_MIN_CURRENT            85     // unit: 10mA
#define _TYPE_C_PMIC_MIN_PPS_CURRENT        60     // unit: 10mA

//--------------------------------------------------
// Definitions of PMIC Voltage Compesation
//--------------------------------------------------
#define _VOLTAGE_COMPESATION_CURRENT_UNIT   50     // unit: 10mA, R_comp = 0.1V / _VOLTAGE_COMPESATION_CURRENT_UNIT

//--------------------------------------------------
// Definitions of PMIC FW OCP Polling Function
//--------------------------------------------------
#define _TYPE_C_PMIC_HW_OCP_MAX             (_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE + 66)    // unit: %, should multiply with PMIC setting current to get the real OCP value

//--------------------------------------------------
// Definitions of PMIC Test FUNCTION
//--------------------------------------------------
#define _TYPE_C_PMIC_FORCE_OUTPUT           _OFF
#define _TYPE_C_PMIC_FORCE_VOLTAGE          1200   // unit: 10mV
#define _TYPE_C_PMIC_FORCE_CURRENT          100    // unit: 10mA

#if(_TYPE_C_PMIC_FORCE_OUTPUT == _ON)
#warning "Pmic would force output, typec port don't connect anything."
#endif

//--------------------------------------------------
// Macros of PMIC IIC Set Srart
//--------------------------------------------------
#define GET_PMIC_IIC_SET_START()            (g_stPMICControl.b1PmicIICSetStart)
#define SET_PMIC_IIC_SET_START()            (g_stPMICControl.b1PmicIICSetStart = _TRUE)
#define CLR_PMIC_IIC_SET_START()            (g_stPMICControl.b1PmicIICSetStart = _FALSE)

//--------------------------------------------------
// Macros of PMIC IIC Status
//--------------------------------------------------
#define GET_PMIC_IIC_IN_MAIN_LOOP()         (g_stPMICControl.b1PmicIICMainLoop)
#define SET_PMIC_IIC_IN_MAIN_LOOP()         (g_stPMICControl.b1PmicIICMainLoop = _TRUE)
#define CLR_PMIC_IIC_IN_MAIN_LOOP()         (g_stPMICControl.b1PmicIICMainLoop = _FALSE)
#define GET_PMIC_IIC_IN_EXINT0_LOOP()       (g_stPMICControl.b1PmicIICExint0Loop)
#define SET_PMIC_IIC_IN_EXINT0_LOOP()       (g_stPMICControl.b1PmicIICExint0Loop = _TRUE)
#define CLR_PMIC_IIC_IN_EXINT0_LOOP()       (g_stPMICControl.b1PmicIICExint0Loop = _FALSE)
#define GET_PMIC_IIC_IN_WDINT_LOOP()        (g_stPMICControl.b1PmicIICWdintLoop)
#define SET_PMIC_IIC_IN_WDINT_LOOP()        (g_stPMICControl.b1PmicIICWdintLoop = _TRUE)
#define CLR_PMIC_IIC_IN_WDINT_LOOP()        (g_stPMICControl.b1PmicIICWdintLoop = _FALSE)
#define GET_PMIC_IIC_EVER_IN_EXINT0_LOOP()  (g_stPMICControl.b1PmicIICExint0EverLoop)
#define SET_PMIC_IIC_EVER_IN_EXINT0_LOOP()  (g_stPMICControl.b1PmicIICExint0EverLoop = _TRUE)
#define CLR_PMIC_IIC_EVER_IN_EXINT0_LOOP()  (g_stPMICControl.b1PmicIICExint0EverLoop = _FALSE)
#define GET_PMIC_IIC_EVER_IN_WDINT_LOOP()   (g_stPMICControl.b1PmicIICWdintEverLoop)
#define SET_PMIC_IIC_EVER_IN_WDINT_LOOP()   (g_stPMICControl.b1PmicIICWdintEverLoop = _TRUE)
#define CLR_PMIC_IIC_EVER_IN_WDINT_LOOP()   (g_stPMICControl.b1PmicIICWdintEverLoop = _FALSE)

//--------------------------------------------------
// Macros of PMIC Output Enable Flag
//--------------------------------------------------
#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
#define GET_PMIC_OUTPUT_ENABLE()            (g_bPMICOutputEnable)
#define SET_PMIC_OUTPUT_ENABLE()            (g_bPMICOutputEnable = _ON)
#define CLR_PMIC_OUTPUT_ENABLE()            (g_bPMICOutputEnable = _OFF)

//--------------------------------------------------
// Macros of PMIC Bi-direction Flag
//--------------------------------------------------
#define GET_PMIC_BIDIR_MODE()               (g_bPMICBiDirMode)
#define SET_PMIC_BIDIR_SRC()                (g_bPMICBiDirMode = _PD_POWER_SRC)
#define SET_PMIC_BIDIR_SNK()                (g_bPMICBiDirMode = _PD_POWER_SNK)
#endif

//--------------------------------------------------
// Macros of PMIC OCP Check Flag
//--------------------------------------------------
#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
#define GET_PMIC_FW_OCP_CHECK_START()       (g_bPmicFwOcpCheckFlag)
#define SET_PMIC_FW_OCP_CHECK_START()       (g_bPmicFwOcpCheckFlag = _TRUE)
#define CLR_PMIC_FW_OCP_CHECK_START()       (g_bPmicFwOcpCheckFlag = _FALSE)

#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#define GET_PMIC_CURRENT_CHECK_START()      (g_bPmicFwOcpCheckFlag)
#define SET_PMIC_CURRENT_CHECK_START()      (g_bPmicFwOcpCheckFlag = _TRUE)
#define CLR_PMIC_CURRENT_CHECK_START()      (g_bPmicFwOcpCheckFlag = _FALSE)

#define GET_PMIC_OCP_PROTECT_START()        (g_bPmicFwOcpProtectFlag)
#define SET_PMIC_OCP_PROTECT_START()        (g_bPmicFwOcpProtectFlag = _ON)
#define CLR_PMIC_OCP_PROTECT_START()        (g_bPmicFwOcpProtectFlag = _OFF)
#endif

//--------------------------------------------------
// Macros of PMIC FW VBUS Check Flag
//--------------------------------------------------
#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
#define GET_PMIC_FW_VBUS_CHECK_START()      (g_bPmicFwVbusCheckFlag)
#define SET_PMIC_FW_VBUS_CHECK_START()      (g_bPmicFwVbusCheckFlag = _TRUE)
#define CLR_PMIC_FW_VBUS_CHECK_START()      (g_bPmicFwVbusCheckFlag = _FALSE)
#endif

//--------------------------------------------------
// Macros of PMIC Vbus Compensation Check Flag
//--------------------------------------------------
#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#define GET_PMIC_VBUS_COMP_CHECK_START()    (g_bPmicVbusCompCheckFlag)
#define SET_PMIC_VBUS_COMP_CHECK_START()    (g_bPmicVbusCompCheckFlag = _TRUE)
#define CLR_PMIC_VBUS_COMP_CHECK_START()    (g_bPmicVbusCompCheckFlag = _FALSE)
#endif

//--------------------------------------------------
// Macros of PMIC OCP Check Flag
//--------------------------------------------------
#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
#define GET_PMIC_GPIO_INT_CHECK_START()     (g_bPmicGpioIntFlag)
#define SET_PMIC_GPIO_INT_CHECK_START()     (g_bPmicGpioIntFlag = _TRUE)
#define CLR_PMIC_GPIO_INT_CHECK_START()     (g_bPmicGpioIntFlag = _FALSE)
#endif

//--------------------------------------------------
// Macros of PMIC Check Operating Status
//--------------------------------------------------
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#define GET_PMIC_GET_OMF_INFO_START()       (g_bPmicGetOmfInfoFlag)
#define SET_PMIC_GET_OMF_INFO_START()       (g_bPmicGetOmfInfoFlag = _TRUE)
#define CLR_PMIC_GET_OMF_INFO_START()       (g_bPmicGetOmfInfoFlag = _FALSE)

#define GET_PMIC_OMF_INFO()                 (g_enumPmicOMFInfo)
#define SET_PMIC_OMF_INFO(x)                (g_enumPmicOMFInfo = (x))
#endif

//--------------------------------------------------
// Macros of PMIC Check Flag
//--------------------------------------------------
#if(_TYPE_C_PMIC_DEBUG == _ON)
#define GET_PMIC_DEBUG_CHECK_START()        (g_bPmicDebugFlag)
#define SET_PMIC_DEBUG_CHECK_START()        (g_bPmicDebugFlag = _TRUE)
#define CLR_PMIC_DEBUG_CHECK_START()        (g_bPmicDebugFlag = _FALSE)
#endif

//--------------------------------------------------
// Macros of PMIC Output Mode Flag
//--------------------------------------------------
#define GET_PMIC_OUTPUT_MODE_STATUS()       (g_enumPmicOutputPdoType)
#define SET_PMIC_OUTPUT_MODE_STATUS(x)      (g_enumPmicOutputPdoType = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructPmicControl g_stPMICControl;

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
bit g_bPMICOutputEnable = _OFF;
bit g_bPMICBiDirMode = _PD_POWER_SNK;
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE)
bit g_bPmicFwOcpCheckFlag = _FALSE;

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
bit g_bPmicFwOcpProtectFlag = _OFF;
#endif
#endif

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
bit g_bPmicFwVbusCheckFlag = _FALSE;
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
bit g_bPmicVbusCompCheckFlag = _FALSE;
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
bit g_bPmicGpioIntFlag = _FALSE;
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
bit g_bPmicGetOmfInfoFlag = _FALSE;
EnumTypeCPmicOperationMode g_enumPmicOMFInfo = _TYPE_C_PMIC_CV_MODE_OPERATION;
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
bit g_bPmicDebugFlag = _FALSE;
#endif

EnumPDPdoType g_enumPmicOutputPdoType = _PD_NONE_SETTING_PDO;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
void ScalerTypeCPmicHwIICInitial(void);
void ScalerTypeCPmicHwIICSetFreqDiv(EnumClkSel enumClock);
bit ScalerTypeCPmicHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
BYTE ScalerTypeCPmicHwIICRead_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray);
#endif
bit ScalerTypeCPmicHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
BYTE ScalerTypeCPmicHwIICWrite_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
BYTE ScalerTypeCPmicHwIICWrite_WDINT(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
bit ScalerTypeCPmicHwIICSetStartCheck(void);
BYTE ScalerTypeCPmicHwIICSetStartCheck_EXINT0(void);
BYTE ScalerTypeCPmicHwIICSetStartCheck_WDINT(void);

bit ScalerTypeCPmicIICRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
BYTE ScalerTypeCPmicIICRead_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
#endif
bit ScalerTypeCPmicIICWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
BYTE ScalerTypeCPmicIICWrite_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
BYTE ScalerTypeCPmicIICWrite_WDINT(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
void ScalerTypeCPmicIICReset(void);
#endif

void ScalerTypeCPmicRx0Initial(void);
void ScalerTypeCPmicRx0Reset(void);
bit ScalerTypeCPmicRx0Setting(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
BYTE ScalerTypeCPmicRx0Setting_EXINT0(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
BYTE ScalerTypeCPmicRx0Setting_WDINT(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
bit ScalerTypeCPmicRx0VbusDischarge(bit bEn);
BYTE ScalerTypeCPmicRx0VbusDischarge_EXINT0(bit bEn);
BYTE ScalerTypeCPmicRx0VbusDischarge_WDINT(bit bEn);
bit ScalerTypeCPmicRx0SwitchControl(bit bEn, bit bPowerDirection);
BYTE ScalerTypeCPmicRx0SwitchControl_EXINT0(bit bEn, bit bPowerDirection);
BYTE ScalerTypeCPmicRx0SwitchControl_WDINT(bit bEn, bit bPowerDirection);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
EnumTypeCPmicOperationMode ScalerTypeCPmicRx0ReadPpsOperationModeStatus_EXINT0(void);
#endif
#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
bit ScalerTypeCPmicRx0Check(void);
bit ScalerTypeCPmicRx0Tracking(void);
#endif
#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
void ScalerTypeCPmicRx0FwOcpIntHandler_EXINT0(void);
#if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
void ScalerTypeCPmicRx0WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID);
#endif
#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
void ScalerTypeCPmicRx0OcpProtect(void);
#endif
#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
void ScalerTypeCPmicRx0OvpUvpIntHandler_EXINT0(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TypeC Hardware IIC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicHwIICInitial(void)
{
    // Reset IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module and disable TOR
    ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT7 | _BIT0), _BIT7);

    // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
    ScalerSetByte(P7F_61_I2CM_CR1, _TYPE_C_HW_IIC_TOR);

    // Disable burst mode
    ScalerSetByte(P7F_62_I2CM_CR2, 0x00);

    // Clear interrupts
    ScalerSetByte(P7F_63_I2CM_CR3, 0x00);

    // Set fall time period count
    ScalerSetByte(P7F_64_I2CM_STR0, _TYPE_C_HW_IIC_FTPC);

    // Set STA setup time period count
    ScalerSetByte(P7F_65_I2CM_STR1, _TYPE_C_HW_IIC_STA_SUGPIO_C);

    // Set SCL high period count
    ScalerSetByte(P7F_66_I2CM_STR2, _TYPE_C_HW_IIC_SHPC_28000K);

    // Set SCL low period count
    ScalerSetByte(P7F_67_I2CM_STR3, _TYPE_C_HW_IIC_SLPC_28000K);

    // Set frequency divisor: ref = xtal/(FD10+1)
    ScalerSetByte(P7F_6A_I2CM_CCR, _TYPE_C_HW_IIC_FD10_28000K);

    // Clear Pmic related control flag
    CLR_PMIC_IIC_SET_START();

    CLR_PMIC_IIC_IN_MAIN_LOOP();

    CLR_PMIC_IIC_IN_EXINT0_LOOP();

    CLR_PMIC_IIC_IN_WDINT_LOOP();

    CLR_PMIC_IIC_EVER_IN_EXINT0_LOOP();

    CLR_PMIC_IIC_EVER_IN_WDINT_LOOP();
}

//--------------------------------------------------
// Description  : TypeC Hardware IIC Clock Select
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicHwIICSetFreqDiv(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // Set freq. divisor: ref = XTAL/(FD10+1) = 7.16M(ref should be approx 10MHz)
        ScalerSetByte(P7F_6A_I2CM_CCR, _TYPE_C_HW_IIC_FD10_14318K);

        // Set STA setup time period count
        ScalerSetByte(P7F_65_I2CM_STR1, _TYPE_C_HW_IIC_STA_SUGPIO_C);

        // Set SCL high period count
        ScalerSetByte(P7F_66_I2CM_STR2, _TYPE_C_HW_IIC_SHPC_14318K);

        // Set SCL low period count
        ScalerSetByte(P7F_67_I2CM_STR3, _TYPE_C_HW_IIC_SLPC_14318K);
    }
    else
    {
        // Set freq. divisor: ref = IOSC/(FD10+1) = 9.3M(ref should be approx 10MHz)
        ScalerSetByte(P7F_6A_I2CM_CCR, _TYPE_C_HW_IIC_FD10_28000K);

        // Set STA setup time period count
        ScalerSetByte(P7F_65_I2CM_STR1, _TYPE_C_HW_IIC_STA_SUGPIO_C);

        // Set SCL high period count
        ScalerSetByte(P7F_66_I2CM_STR2, _TYPE_C_HW_IIC_SHPC_28000K);

        // Set SCL low period count
        ScalerSetByte(P7F_67_I2CM_STR3, _TYPE_C_HW_IIC_SLPC_28000K);
    }
}

//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray)
{
    BYTE ucI = 0;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _TYPE_C_HW_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeCPmicHwIICSetStartCheck() == _FAIL)
    {
        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

            // Set no repeat start
            ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucDataLength - 1) << 1));

    // If int happened while this I2C setting, then return.
    if((GET_PMIC_IIC_EVER_IN_EXINT0_LOOP() == _TRUE) || (GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE))
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // IIC command Start
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT6, _BIT6);

    // Set Pmic I2C set start flag
    SET_PMIC_IIC_SET_START();

    // Wait until Master Receive Complete
    if(ScalerTimerPollingFlagProc(4, P7F_68_I2CM_SR, _BIT1, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = ScalerGetByte(P7F_69_I2CM_TD);
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetBit(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Clear Pmic I2C set start flag
    CLR_PMIC_IIC_SET_START();

    // If int happened while this I2C setting, then return.
    if((GET_PMIC_IIC_EVER_IN_EXINT0_LOOP() == _TRUE) || (GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE))
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    CLR_PMIC_IIC_IN_MAIN_LOOP();

    return _SUCCESS;
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicHwIICRead_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray) using 1
{
    BYTE ucI = 0;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _TYPE_C_HW_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeCPmicHwIICSetStartCheck_EXINT0() == _FAIL)
    {
        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            ScalerSetBit_EXINT(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

            // Set no repeat start
            ScalerSetBit_EXINT(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit_EXINT(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit_EXINT(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit_EXINT(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit_EXINT(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucDataLength - 1) << 1));

    // If int happened while this I2C setting, then return.
    if(GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // IIC command Start
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT6, _BIT6);

    // Set Pmic I2C set start flag
    SET_PMIC_IIC_SET_START();

    // Wait until Master Receive Complete
    if(ScalerTimerPollingFlagProc_EXINT0(4, P7F_68_I2CM_SR, _BIT1, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = ScalerGetByte_EXINT(P7F_69_I2CM_TD);
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetBit_EXINT(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Clear Pmic I2C set start flag
    CLR_PMIC_IIC_SET_START();

    // If int happened while this I2C setting, then return.
    if(GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    CLR_PMIC_IIC_IN_EXINT0_LOOP();

    return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray)
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    if(ucDataLength > 16)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeCPmicHwIICSetStartCheck() == _FAIL)
    {
        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

    ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    pData[0] = ucDataLength;

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (pData[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((pData[0] + 1) << 1);

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < pData[0]; ucI++)
    {
        ScalerSetByte(P7F_69_I2CM_TD, pucWriteArray[ucI]);
    }

    // If int happened while this I2C setting, then return.
    if((GET_PMIC_IIC_EVER_IN_EXINT0_LOOP() == _TRUE) || (GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE))
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_MAIN_LOOP();

        return _FAIL;
    }

    // Send IIC command Start
    ScalerSetByte(P7F_60_I2CM_CR0, (0xC0 + ucTempLength));

    // Set Pmic I2C set start flag
    SET_PMIC_IIC_SET_START();

    CLR_PMIC_IIC_IN_MAIN_LOOP();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicHwIICWrite_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray) using 1
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    if(ucDataLength > 16)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeCPmicHwIICSetStartCheck_EXINT0() == _FAIL)
    {
        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit_EXINT(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit_EXINT(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    pData_EXINT[0] = ucDataLength;

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData_EXINT[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (pData_EXINT[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((pData_EXINT[0] + 1) << 1);

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < pData_EXINT[0]; ucI++)
    {
        ScalerSetByte_EXINT(P7F_69_I2CM_TD, pucWriteArray[ucI]);
    }

    // If int happened while this I2C setting, then return.
    if(GET_PMIC_IIC_EVER_IN_WDINT_LOOP() == _TRUE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _FAIL;
    }

    // Send IIC command Start
    ScalerSetByte_EXINT(P7F_60_I2CM_CR0, (0xC0 + ucTempLength));

    // Set Pmic I2C set start flag
    SET_PMIC_IIC_SET_START();

    // If interrupt form other process, then wait until transmit finished.
    if((GET_PMIC_IIC_IN_MAIN_LOOP() == _TRUE) || (GET_PMIC_IIC_IN_WDINT_LOOP() == _TRUE))
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc_EXINT0(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            CLR_PMIC_IIC_IN_EXINT0_LOOP();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetBit_EXINT(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();

        CLR_PMIC_IIC_IN_EXINT0_LOOP();

        return _SUCCESS;
    }

    CLR_PMIC_IIC_IN_EXINT0_LOOP();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                ucDataLength     --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicHwIICWrite_WDINT(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray) using 3
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    if(ucDataLength > 16)
    {
        return _FAIL;
    }

    // Check if set start before
    if(ScalerTypeCPmicHwIICSetStartCheck_WDINT() == _FAIL)
    {
        CLR_PMIC_IIC_IN_WDINT_LOOP();

        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit_EXINT(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit_EXINT(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_WDINT(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_WDINT_LOOP();

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte_EXINT(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

    ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    pData_EXINT[0] = ucDataLength;

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData_EXINT[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (pData_EXINT[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((pData_EXINT[0] + 1) << 1);

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < pData_EXINT[0]; ucI++)
    {
        ScalerSetByte_EXINT(P7F_69_I2CM_TD, pucWriteArray[ucI]);
    }

    // If int happened while this I2C setting, then return.
    if(GET_PMIC_IIC_EVER_IN_EXINT0_LOOP() == _TRUE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        CLR_PMIC_IIC_IN_WDINT_LOOP();

        return _FAIL;
    }

    // Send IIC command Start
    ScalerSetByte_EXINT(P7F_60_I2CM_CR0, (0xC0 + ucTempLength));

    // Set Pmic I2C set start flag
    SET_PMIC_IIC_SET_START();

    // If interrupt form other process, then wait until transmit finished.
    if((GET_PMIC_IIC_IN_MAIN_LOOP() == _TRUE) || (GET_PMIC_IIC_IN_EXINT0_LOOP() == _TRUE))
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc_WDINT(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            CLR_PMIC_IIC_IN_WDINT_LOOP();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetBit_EXINT(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();

        CLR_PMIC_IIC_IN_WDINT_LOOP();

        return _SUCCESS;
    }

    CLR_PMIC_IIC_IN_WDINT_LOOP();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : TypeC Hardware IIC Check if Set Start
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicHwIICSetStartCheck(void)
{
    SET_PMIC_IIC_IN_MAIN_LOOP();

    CLR_PMIC_IIC_EVER_IN_EXINT0_LOOP();

    CLR_PMIC_IIC_EVER_IN_WDINT_LOOP();

    if(GET_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetBit(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : TypeC Hardware IIC Check if Set Start
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicHwIICSetStartCheck_EXINT0(void) using 1
{
    SET_PMIC_IIC_IN_EXINT0_LOOP();

    SET_PMIC_IIC_EVER_IN_EXINT0_LOOP();

    CLR_PMIC_IIC_EVER_IN_WDINT_LOOP();

    if(GET_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc_EXINT0(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetBit_EXINT(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : TypeC Hardware IIC Check if Set Start
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicHwIICSetStartCheck_WDINT(void) using 3
{
    SET_PMIC_IIC_IN_WDINT_LOOP();

    SET_PMIC_IIC_EVER_IN_WDINT_LOOP();

    CLR_PMIC_IIC_EVER_IN_EXINT0_LOOP();

    if(GET_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc_WDINT(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit_EXINT(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            return _FAIL;
        }

        // Clear all flags
        ScalerSetBit_EXINT(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicIICRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;

    if(usLength == 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Receive 24 bytes each time
        ucDataCnt = _TYPE_C_HW_IIC_READ_SIZE;

        // Check if more than 24 bytes are needed to be received
        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Execute Hardware IIC Read Command
        if(ScalerTypeCPmicHwIICRead(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray) == _FAIL)
        {
            return _FAIL;
        }

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to read
//                pucReadArray     --> Result array
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicIICRead_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray) using 1
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;

    if(usLength == 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Receive 24 bytes each time
        ucDataCnt = _TYPE_C_HW_IIC_READ_SIZE;

        // Check if more than 24 bytes are needed to be received
        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Execute Hardware IIC Read Command
        if(ScalerTypeCPmicHwIICRead_EXINT0(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray) == _FAIL)
        {
            return _FAIL;
        }

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicIICWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE pucTempData[_TYPE_C_HW_IIC_WRITE_SIZE + 2];

    if(usLength <= 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Transmit max 30 bytes each time
        ucDataCnt = _TYPE_C_HW_IIC_WRITE_SIZE;

        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Execute Hardware IIC Write Command
        if(ScalerTypeCPmicHwIICWrite(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
        {
            return _FAIL;
        }

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicIICWrite_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray) using 1
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE pucTempData[_TYPE_C_HW_IIC_WRITE_SIZE + 2];

    if(usLength <= 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Transmit max 30 bytes each time
        ucDataCnt = _TYPE_C_HW_IIC_WRITE_SIZE;

        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Execute Hardware IIC Write Command
        if(ScalerTypeCPmicHwIICWrite_EXINT0(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
        {
            return _FAIL;
        }

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucSlaveAddr      --> Slave address
//                ucSubAddrLength  --> Start address length of selected device
//                usSubAddr        --> Start address of selected device
//                usLength         --> Numbers of data we want to write
//                pucWriteArray    --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicIICWrite_WDINT(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray) using 3
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE pucTempData[_TYPE_C_HW_IIC_WRITE_SIZE + 2];

    if(usLength <= 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Transmit max 30 bytes each time
        ucDataCnt = _TYPE_C_HW_IIC_WRITE_SIZE;

        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Execute Hardware IIC Write Command
        if(ScalerTypeCPmicHwIICWrite_WDINT(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
        {
            return _FAIL;
        }

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Reset Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicIICReset(void)
{
    CLR_PMIC_IIC_IN_MAIN_LOOP();
    CLR_PMIC_IIC_IN_EXINT0_LOOP();
    CLR_PMIC_IIC_IN_WDINT_LOOP();
    CLR_PMIC_IIC_EVER_IN_EXINT0_LOOP();
    CLR_PMIC_IIC_EVER_IN_WDINT_LOOP();

    if(GET_PMIC_IIC_SET_START() == _TRUE)
    {
        // Wait until Master Transmit Complete
        if(ScalerTimerPollingFlagProc(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
        {
            // Reset(Block) IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Clear Pmic I2C set start flag
            CLR_PMIC_IIC_SET_START();

            return;
        }

        // Clear all flags
        ScalerSetBit(P7F_68_I2CM_SR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Clear Pmic I2C set start flag
        CLR_PMIC_IIC_SET_START();
    }
}
#endif // End of #if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Rx0 PMIC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0Initial(void)
{
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
    ScalerTypeCPmicHwIICInitial();

    ScalerTypeCPmicIICReset();
#endif

    ExternalDeviceInterfaceTypeCPmicACOnInitial();

    // Reset PMIC Output Type
    SET_PMIC_OUTPUT_MODE_STATUS(_PD_NONE_SETTING_PDO);

#if(_TYPE_C_PMIC_FORCE_OUTPUT == _ON)
    ScalerTypeCPmicRx0Setting(_ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, _TYPE_C_PMIC_FORCE_VOLTAGE, _TYPE_C_PMIC_FORCE_CURRENT);
    ScalerTimerDelayXms(3000);

#if(_TYPE_C_PMIC_DEBUG == _ON)
    if(ExternalDeviceInterfaceTypeCPmicDebugCheckStatus() == _TYPE_C_PMIC_CONTROL_FAIL)
    {
        DebugMessageTypeC("PMIC Check Fail!", 0x00);
    }
#endif

    ScalerTypeCPmicRx0Setting(_OFF, _PD_POWER_SRC, _PD_NONE_SETTING_PDO, 0, 0);
#endif
}

//--------------------------------------------------
// Description  : Rx0 PMIC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0Reset(void)
{
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
    ScalerTypeCPmicHwIICInitial();

    ScalerTypeCPmicIICReset();
#endif

    ExternalDeviceInterfaceTypeCPmicUnattachReset();

    // Reset PMIC Output Type
    SET_PMIC_OUTPUT_MODE_STATUS(_PD_NONE_SETTING_PDO);

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    CLR_PMIC_FW_VBUS_CHECK_START();

    // Disable INT
    ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_VMON, _DISABLE);
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    CLR_PMIC_FW_OCP_CHECK_START();

    // Disable INT
    ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_IMON, _DISABLE);
#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    CLR_PMIC_CURRENT_CHECK_START();
    CLR_PMIC_OCP_PROTECT_START();
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
    CLR_PMIC_VBUS_COMP_CHECK_START();
#endif

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
    CLR_PMIC_OUTPUT_ENABLE();
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
    CLR_PMIC_GPIO_INT_CHECK_START();
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
    CLR_PMIC_GET_OMF_INFO_START();
    SET_PMIC_OMF_INFO(_TYPE_C_PMIC_CV_MODE_OPERATION);
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
    CLR_PMIC_DEBUG_CHECK_START();
#endif
}

//--------------------------------------------------
// Description  : Control Rx0 PMIC to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicRx0Setting(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent)
{
    EnumTypeCPmicControlResult enumResult = _TYPE_C_PMIC_CONTROL_FAIL;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
#if((_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC))
    WORD usThreshold1 = 0x0000;
#endif

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    WORD usThreshold2 = 0x0000;

    // Caculate OVP & UVP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set FW VBUS Check Start Flag
        SET_PMIC_FW_VBUS_CHECK_START();

        // Translate Voltage to SARADC Value
        usThreshold2 = ((WORD)(((DWORD)(usVoltage)) * 1024 / 2400));

        // Set Threshold for OVP
        usThreshold1 = ((WORD)((((DWORD)(usThreshold2)) * _TYPE_C_PMIC_FW_OVP_THRESHOLD) / 100));

        if(usThreshold1 >= 0x3FF)
        {
            usThreshold1 = 0x3FE;
        }

        // Set Threshold for UVP
        if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
        {
            usThreshold2 = ((WORD)(((DWORD)(_TYPE_C_PMIC_FW_UVP_PPS_THRESHOLD)) * 1024 / 2400));
        }
        else
        {
            usThreshold2 = ((WORD)((((DWORD)(usThreshold2)) * _TYPE_C_PMIC_FW_UVP_THRESHOLD) / 100));
        }

        // Disable INT
        ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_VMON, _DISABLE);

        // Set OVP/UVP range
        ScalerTypeCPowerRangeIntSetting(_TYPE_C_UFP_VMON, usThreshold1, usThreshold2, _TYPE_C_ADC_WITHOUT_RANGE);
    }
    else
    {
        // Clear FW VBUS Check Start Flag
        CLR_PMIC_FW_VBUS_CHECK_START();

        // Disable INT
        ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_VMON, _DISABLE);
    }
#endif

    // Minimum Current Setting for different PDO type
    if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
    {
        usCurrent = (usCurrent < _TYPE_C_PMIC_MIN_PPS_CURRENT ? _TYPE_C_PMIC_MIN_PPS_CURRENT : usCurrent);
    }
    else
    {
        usCurrent = (usCurrent < _TYPE_C_PMIC_MIN_CURRENT ? _TYPE_C_PMIC_MIN_CURRENT : usCurrent);
    }

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    // Caculate OCP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set FW OCP Check Start Flag
        SET_PMIC_FW_OCP_CHECK_START();

        // Calculate Max current value
        usThreshold1 = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_FW_OCP_CURRENT_VALUE) / 100));

        // Calculate current to SARADC
        usThreshold1 = ((WORD)((((DWORD)usThreshold1) * 1024 * 10) / _TYPE_C_ADC_MAX_CURRENT / 1000));

        // Disable INT
        ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_IMON, _DISABLE);

        // Set Range to check if current will be triggered OCP Current. Not enable int immediately because avoid inrush current.
        ScalerTypeCPowerRangeIntSetting(_TYPE_C_UFP_IMON, 0xFFFF, usThreshold1, _TYPE_C_ADC_WITHIN_RANGE);

        // Set PMIC OVP threshold to Max
        usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
    }
    else
    {
        // Clear FW OCP Check Start Flag
        CLR_PMIC_FW_OCP_CHECK_START();

        // Disable INT
        ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_IMON, _DISABLE);
    }
#endif

    // Setting PMIC
    if(bAction == _ON)
    {
        ScalerTypeCPmicRx0SwitchControl(_ON, bPowerDirection);

        if(bPowerDirection == _PD_POWER_SRC)
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
            SET_PMIC_OUTPUT_ENABLE();
            SET_PMIC_BIDIR_SRC();
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
            SET_PMIC_VBUS_COMP_CHECK_START();
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            SET_PMIC_GET_OMF_INFO_START();
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
            SET_PMIC_DEBUG_CHECK_START();
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
            SET_PMIC_CURRENT_CHECK_START();

            // Set PMIC OVP threshold to Max
            usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
            SET_PMIC_GPIO_INT_CHECK_START();
#endif
        }
        else
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
            CLR_PMIC_OUTPUT_ENABLE();
            SET_PMIC_BIDIR_SNK();
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
            CLR_PMIC_VBUS_COMP_CHECK_START();
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            CLR_PMIC_GET_OMF_INFO_START();
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
            CLR_PMIC_DEBUG_CHECK_START();
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
            CLR_PMIC_CURRENT_CHECK_START();
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
            CLR_PMIC_GPIO_INT_CHECK_START();
#endif
        }

        if(GET_PMIC_OUTPUT_MODE_STATUS() != enumPdoType)
        {
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            if(ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting(enumDirection, enumPdoType) == _TYPE_C_PMIC_CONTROL_FAIL)
            {
                return _FAIL;
            }
#endif
            SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);
        }

        enumResult = ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(enumDirection, usVoltage, usCurrent);
    }
    else
    {
        enumResult = ExternalDeviceInterfaceTypeCPmicTurnOff();

        // Reset PMIC Output Type
        SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
        CLR_PMIC_OUTPUT_ENABLE();
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
        CLR_PMIC_VBUS_COMP_CHECK_START();
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
        CLR_PMIC_GET_OMF_INFO_START();
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
        CLR_PMIC_DEBUG_CHECK_START();
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        CLR_PMIC_CURRENT_CHECK_START();
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
        CLR_PMIC_GPIO_INT_CHECK_START();
#endif
    }

    if(enumResult == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Control Rx0 PMIC to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0Setting_EXINT0(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent) using 1
{
    EnumTypeCPmicControlResult enumResult = _TYPE_C_PMIC_CONTROL_FAIL;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
#if((_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC))
    WORD usThreshold1 = 0x0000;
#endif

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    WORD usThreshold2 = 0x0000;

    // Caculate OVP & UVP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set FW VBUS Check Start Flag
        SET_PMIC_FW_VBUS_CHECK_START();

        // Translate Voltage to SARADC Value
        usThreshold2 = ((WORD)(((DWORD)(usVoltage)) * 1024 / 2400));

        // Set Threshold for OVP
        usThreshold1 = ((WORD)((((DWORD)(usThreshold2)) * _TYPE_C_PMIC_FW_OVP_THRESHOLD) / 100));

        if(usThreshold1 >= 0x3FF)
        {
            usThreshold1 = 0x3FE;
        }

        // Set Threshold for UVP
        if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
        {
            usThreshold2 = ((WORD)(((DWORD)(_TYPE_C_PMIC_FW_UVP_PPS_THRESHOLD)) * 1024 / 2400));
        }
        else
        {
            usThreshold2 = ((WORD)((((DWORD)(usThreshold2)) * _TYPE_C_PMIC_FW_UVP_THRESHOLD) / 100));
        }

        // Disable INT
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_VMON, _DISABLE);

        // Set OVP/UVP range
        ScalerTypeCPowerRangeIntSetting_EXINT0(_TYPE_C_UFP_VMON, usThreshold1, usThreshold2, _TYPE_C_ADC_WITHOUT_RANGE);
    }
    else
    {
        // Clear FW VBUS Check Start Flag
        CLR_PMIC_FW_VBUS_CHECK_START();

        // Disable INT
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_VMON, _DISABLE);
    }
#endif

    // Minimum Current Setting for different PDO type
    if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
    {
        usCurrent = (usCurrent < _TYPE_C_PMIC_MIN_PPS_CURRENT ? _TYPE_C_PMIC_MIN_PPS_CURRENT : usCurrent);
    }
    else
    {
        usCurrent = (usCurrent < _TYPE_C_PMIC_MIN_CURRENT ? _TYPE_C_PMIC_MIN_CURRENT : usCurrent);
    }

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    // Caculate OCP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set FW OCP Check Start Flag
        SET_PMIC_FW_OCP_CHECK_START();

        // Calculate Max current value
        usThreshold1 = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_FW_OCP_CURRENT_VALUE) / 100));

        // Calculate current to SARADC
        usThreshold1 = ((WORD)((((DWORD)usThreshold1) * 1024 * 10) / _TYPE_C_ADC_MAX_CURRENT / 1000));

        // Disable INT
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_IMON, _DISABLE);

        // Set Range to check if current will be triggered OCP Current. Not enable int immediately because avoid inrush current.
        ScalerTypeCPowerRangeIntSetting_EXINT0(_TYPE_C_UFP_IMON, 0xFFFF, usThreshold1, _TYPE_C_ADC_WITHIN_RANGE);

        // Set PMIC OVP threshold to Max
        usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
    }
    else
    {
        // Clear FW OCP Check Start Flag
        CLR_PMIC_FW_OCP_CHECK_START();

        // Disable INT
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_IMON, _DISABLE);
    }
#endif

    // Setting PMIC
    if(bAction == _ON)
    {
        ScalerTypeCPmicRx0SwitchControl_EXINT0(_ON, bPowerDirection);

        if(bPowerDirection == _PD_POWER_SRC)
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
            SET_PMIC_OUTPUT_ENABLE();
            SET_PMIC_BIDIR_SRC();
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
            SET_PMIC_VBUS_COMP_CHECK_START();
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            SET_PMIC_GET_OMF_INFO_START();
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
            SET_PMIC_DEBUG_CHECK_START();
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
            SET_PMIC_CURRENT_CHECK_START();

            // Set PMIC OVP threshold to Max
            usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
            SET_PMIC_GPIO_INT_CHECK_START();
#endif
        }
        else
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
            CLR_PMIC_OUTPUT_ENABLE();
            SET_PMIC_BIDIR_SNK();
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
            CLR_PMIC_VBUS_COMP_CHECK_START();
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            CLR_PMIC_GET_OMF_INFO_START();
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
            CLR_PMIC_DEBUG_CHECK_START();
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
            CLR_PMIC_CURRENT_CHECK_START();
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
            CLR_PMIC_GPIO_INT_CHECK_START();
#endif
        }

        if(GET_PMIC_OUTPUT_MODE_STATUS() != enumPdoType)
        {
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            if(ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_EXINT0(enumDirection, enumPdoType) == _TYPE_C_PMIC_CONTROL_FAIL)
            {
                return _FAIL;
            }
#endif
            SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);
        }

        enumResult = ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(enumDirection, usVoltage, usCurrent);
    }
    else
    {
        enumResult = ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0();

        // Reset PMIC Output Type
        SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
        CLR_PMIC_OUTPUT_ENABLE();
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
        CLR_PMIC_VBUS_COMP_CHECK_START();
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
        CLR_PMIC_GET_OMF_INFO_START();
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
        CLR_PMIC_DEBUG_CHECK_START();
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        CLR_PMIC_CURRENT_CHECK_START();
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
        CLR_PMIC_GPIO_INT_CHECK_START();
#endif
    }

    if(enumResult == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Control Rx0 PMIC to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 0 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0Setting_WDINT(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent) using 3
{
    EnumTypeCPmicControlResult enumResult = _TYPE_C_PMIC_CONTROL_FAIL;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
#if((_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC))
    WORD usThreshold1 = 0x0000;
#endif

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    WORD usThreshold2 = 0x0000;

    // Caculate OVP & UVP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set FW VBUS Check Start Flag
        SET_PMIC_FW_VBUS_CHECK_START();

        // Translate Voltage to SARADC Value
        usThreshold2 = ((WORD)(((DWORD)(usVoltage)) * 1024 / 2400));

        // Set Threshold for OVP
        usThreshold1 = ((WORD)((((DWORD)(usThreshold2)) * _TYPE_C_PMIC_FW_OVP_THRESHOLD) / 100));

        if(usThreshold1 >= 0x3FF)
        {
            usThreshold1 = 0x3FE;
        }

        // Set Threshold for UVP
        if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
        {
            usThreshold2 = ((WORD)(((DWORD)(_TYPE_C_PMIC_FW_UVP_PPS_THRESHOLD)) * 1024 / 2400));
        }
        else
        {
            usThreshold2 = ((WORD)((((DWORD)(usThreshold2)) * _TYPE_C_PMIC_FW_UVP_THRESHOLD) / 100));
        }

        // Disable INT
        ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_VMON, _DISABLE);

        // Set OVP/UVP range
        ScalerTypeCPowerRangeIntSetting_WDINT(_TYPE_C_UFP_VMON, usThreshold1, usThreshold2, _TYPE_C_ADC_WITHOUT_RANGE);
    }
    else
    {
        // Clear FW VBUS Check Start Flag
        CLR_PMIC_FW_VBUS_CHECK_START();

        // Disable INT
        ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_VMON, _DISABLE);
    }
#endif

    // Minimum Current Setting for different PDO type
    if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
    {
        usCurrent = (usCurrent < _TYPE_C_PMIC_MIN_PPS_CURRENT ? _TYPE_C_PMIC_MIN_PPS_CURRENT : usCurrent);
    }
    else
    {
        usCurrent = (usCurrent < _TYPE_C_PMIC_MIN_CURRENT ? _TYPE_C_PMIC_MIN_CURRENT : usCurrent);
    }

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    // Caculate OCP threshold
    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
    {
        // Set FW OCP Check Start Flag
        SET_PMIC_FW_OCP_CHECK_START();

        // Calculate Max current value
        usThreshold1 = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_FW_OCP_CURRENT_VALUE) / 100));

        // Calculate current to SARADC
        usThreshold1 = ((WORD)((((DWORD)usThreshold1) * 1024 * 10) / _TYPE_C_ADC_MAX_CURRENT / 1000));

        // Disable INT
        ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_IMON, _DISABLE);

        // Set Range to check if current will be triggered OCP Current. Not enable int immediately because avoid inrush current.
        ScalerTypeCPowerRangeIntSetting_WDINT(_TYPE_C_UFP_IMON, 0xFFFF, usThreshold1, _TYPE_C_ADC_WITHIN_RANGE);

        // Set PMIC OVP threshold to Max
        usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
    }
    else
    {
        // Clear FW OCP Check Start Flag
        CLR_PMIC_FW_OCP_CHECK_START();

        // Disable INT
        ScalerTypeCPowerRangeIntControl_WDINT(_TYPE_C_UFP_IMON, _DISABLE);
    }
#endif

    // Setting PMIC
    if(bAction == _ON)
    {
        ScalerTypeCPmicRx0SwitchControl_WDINT(_ON, bPowerDirection);

        if(bPowerDirection == _PD_POWER_SRC)
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
            SET_PMIC_OUTPUT_ENABLE();
            SET_PMIC_BIDIR_SRC();
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
            SET_PMIC_VBUS_COMP_CHECK_START();
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            SET_PMIC_GET_OMF_INFO_START();
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
            SET_PMIC_DEBUG_CHECK_START();
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
            SET_PMIC_CURRENT_CHECK_START();

            // Set PMIC OVP threshold to Max
            usCurrent = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_HW_OCP_MAX) / 100));
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
            SET_PMIC_GPIO_INT_CHECK_START();
#endif
        }
        else
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
            CLR_PMIC_OUTPUT_ENABLE();
            SET_PMIC_BIDIR_SNK();
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
            CLR_PMIC_VBUS_COMP_CHECK_START();
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            CLR_PMIC_GET_OMF_INFO_START();
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
            CLR_PMIC_DEBUG_CHECK_START();
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
            CLR_PMIC_CURRENT_CHECK_START();
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
            CLR_PMIC_GPIO_INT_CHECK_START();
#endif
        }

        if(GET_PMIC_OUTPUT_MODE_STATUS() != enumPdoType)
        {
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            if(ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_WDINT(enumDirection, enumPdoType) == _TYPE_C_PMIC_CONTROL_FAIL)
            {
                return _FAIL;
            }
#endif
            SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);
        }

        enumResult = ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(enumDirection, usVoltage, usCurrent);
    }
    else
    {
        enumResult = ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT();

        // Reset PMIC Output Type
        SET_PMIC_OUTPUT_MODE_STATUS(enumPdoType);

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
        CLR_PMIC_OUTPUT_ENABLE();
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
        CLR_PMIC_VBUS_COMP_CHECK_START();
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
        CLR_PMIC_GET_OMF_INFO_START();
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
        CLR_PMIC_DEBUG_CHECK_START();
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        CLR_PMIC_CURRENT_CHECK_START();
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
        CLR_PMIC_GPIO_INT_CHECK_START();
#endif
    }

    if(enumResult == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC VBUS Discharge Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicRx0VbusDischarge(bit bEn)
{
    EnumTypeCPmicDischarge enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;

    if(bEn == _ON)
    {
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_ENABLE;
    }
    else
    {
        ScalerTypeCPmicRx0SwitchControl(_OFF, _PD_POWER_SNK);
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;
    }

    if(ExternalDeviceInterfaceTypeCPmicVbusDischarge(enumDischarge) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC VBUS Discharge Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0VbusDischarge_EXINT0(bit bEn) using 1
{
    EnumTypeCPmicDischarge enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;

    if(bEn == _ON)
    {
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_ENABLE;
    }
    else
    {
        ScalerTypeCPmicRx0SwitchControl_EXINT0(_OFF, _PD_POWER_SNK);
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;
    }

    if(ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(enumDischarge) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC VBUS Discharge Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0VbusDischarge_WDINT(bit bEn) using 3
{
    EnumTypeCPmicDischarge enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;

    if(bEn == _ON)
    {
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_ENABLE;
    }
    else
    {
        ScalerTypeCPmicRx0SwitchControl_WDINT(_OFF, _PD_POWER_SNK);
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;
    }

    if(ExternalDeviceInterfaceTypeCPmicVbusDischarge_WDINT(enumDischarge) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC Switch Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicRx0SwitchControl(bit bEn, bit bPowerDirection)
{
    EnumTypeCPmicSwitchControl enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    if(bEn == _ON)
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE;
    }
    else
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    }

    if(bPowerDirection == _PD_POWER_SRC)
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
    }
    else
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
    }


    if(ExternalDeviceInterfaceTypeCPmicSwitchControl(enumSwitchControl, enumDirection) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC Switch Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0SwitchControl_EXINT0(bit bEn, bit bPowerDirection) using 1
{
    EnumTypeCPmicSwitchControl enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    if(bEn == _ON)
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE;
    }
    else
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    }

    if(bPowerDirection == _PD_POWER_SRC)
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
    }
    else
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
    }


    if(ExternalDeviceInterfaceTypeCPmicSwitchControl_EXINT0(enumSwitchControl, enumDirection) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : RX0 PMIC Switch Control
// Input Value  : bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
BYTE ScalerTypeCPmicRx0SwitchControl_WDINT(bit bEn, bit bPowerDirection) using 3
{
    EnumTypeCPmicSwitchControl enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    if(bEn == _ON)
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE;
    }
    else
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    }

    if(bPowerDirection == _PD_POWER_SRC)
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
    }
    else
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
    }


    if(ExternalDeviceInterfaceTypeCPmicSwitchControl_WDINT(enumSwitchControl, enumDirection) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Read Output Status
// Input Value  : None
// Output Value : Output Mode (Fixed Voltage/PPS)
//--------------------------------------------------
EnumTypeCPmicOperationMode ScalerTypeCPmicRx0ReadPpsOperationModeStatus_EXINT0(void) using 1
{
    if(PCB_PMIC_ALERT_DETECT() == _PMIC_ALERT_ON)
    {
        if(ExternalDeviceInterfaceTypeCPmicReadPpsOperationModeStatus_EXINT0() == _TYPE_C_PMIC_CC_MODE_OPERATION)
        {
            SET_PMIC_OMF_INFO(_TYPE_C_PMIC_CC_MODE_OPERATION);
        }
        else
        {
            SET_PMIC_OMF_INFO(_TYPE_C_PMIC_CV_MODE_OPERATION);
        }
    }

    return GET_PMIC_OMF_INFO();
}
#endif

#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : RX0 PMIC VBUS Check
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicRx0Check(void)
{
#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    if(GET_PMIC_FW_VBUS_CHECK_START() == _TRUE)
    {
        CLR_PMIC_FW_VBUS_CHECK_START();

        ScalerTimerDelayXms(20);

        // Clear flag and enable INT
        ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_VMON, _ENABLE);
    }
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    if(GET_PMIC_FW_OCP_CHECK_START() == _TRUE)
    {
        CLR_PMIC_FW_OCP_CHECK_START();

        ScalerTimerDelayXms(20);

        // Clear flag and enable INT
        ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_IMON, _ENABLE);
    }
#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    if(GET_PMIC_CURRENT_CHECK_START() == _TRUE)
    {
        CLR_PMIC_CURRENT_CHECK_START();
        CLR_PMIC_OCP_PROTECT_START();
        ScalerTimerReactiveTimerEvent(20, _SCALER_TIMER_EVENT_PMIC_TRACKING);
        DebugMessageTypeC("Pmic CHECK", 0x00);
    }
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
    if(GET_PMIC_VBUS_COMP_CHECK_START() == _TRUE)
    {
        CLR_PMIC_VBUS_COMP_CHECK_START();

        ScalerTimerReactiveTimerEvent(20, _SCALER_TIMER_EVENT_PMIC_TRACKING);
    }
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
    if(GET_PMIC_GPIO_INT_CHECK_START() == _ON)
    {
        CLR_PMIC_GPIO_INT_CHECK_START();
        ScalerTimerReactiveTimerEvent(20, _SCALER_TIMER_EVENT_PMIC_TRACKING);
        DebugMessageTypeC("Pmic GPIO tracking", 0xFF);
    }
#endif

#if(_TYPE_C_PMIC_DEBUG == _ON)
    if(GET_PMIC_DEBUG_CHECK_START() == _TRUE)
    {
        CLR_PMIC_DEBUG_CHECK_START();

        ScalerTimerDelayXms(20);

        if(ExternalDeviceInterfaceTypeCPmicDebugCheckStatus() == _TYPE_C_PMIC_CONTROL_FAIL)
        {
            DebugMessageTypeC("PMIC Check Fail!", 0x00);

            return _FAIL;
        }

        ScalerTimerReactiveTimerEvent(20, _SCALER_TIMER_EVENT_PMIC_TRACKING);
    }
#endif // End of #if(_TYPE_C_PMIC_DEBUG == _ON)

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : RX0 PMIC VBUS Check
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCPmicRx0Tracking(void)
{
    BYTE ucResult = _SUCCESS;
    BYTE ucTimerEvent = 0x00;
#if((_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) || (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC))
    WORD usCurrent = 0x0000;
    WORD usCurrentValue = 0x0000;
#endif
#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
    WORD usSchmittVIL = 0x0000;
    WORD usSchmittVIH = 0x0000;
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    WORD usOcpThreshold = 0x0000;
    WORD usOcpDelay = 0x0000;

    // PMIC OCP Detection
    if((GET_PMIC_BIDIR_MODE() == _PD_POWER_SRC) && (GET_PMIC_OUTPUT_ENABLE() == _ON))
    {
        if(GET_PMIC_OCP_PROTECT_START() == _OFF)
        {
            // Set 10ms Timer Event for FW Polling OCP
            ucTimerEvent |= 0x01;
            DebugMessageTypeC("Pmic Tracking", 0x00);

            // Read current value from PMIC's ADC
            usCurrentValue = ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue();

            // Minimum Current Setting for different PDO type
            usCurrent = GET_RX0_OUTPUT_CUR();
            usCurrent = (usCurrent < _TYPE_C_PMIC_MIN_CURRENT ? _TYPE_C_PMIC_MIN_CURRENT : usCurrent);

            // Calculate OCP threshold
            usOcpThreshold = ((WORD)((((DWORD)usCurrent) * _TYPE_C_PMIC_FW_OCP_CURRENT_VALUE) / 100));

            // Debounce when current > OCP threshold
            if(usCurrentValue >= usOcpThreshold)
            {
                ScalerTimerDelayXms(2);
                usCurrentValue = ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue();
            }

            // OCP judgment
            if(usCurrentValue >= usOcpThreshold)
            {
                usOcpDelay = MAXOF(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN, 10);
                ScalerTimerReactiveTimerEvent(usOcpDelay, _SCALER_TIMER_EVENT_PMIC_POLLING_OCP);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PMIC_TRACKING);
                DebugMessageTypeC("Pmic:Output Current OCP", 0x00);
                SET_PMIC_OCP_PROTECT_START();
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PMIC_POLLING_OCP);
                CLR_PMIC_OCP_PROTECT_START();
            }
        }
    }
    else
    {
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PMIC_TRACKING);
    }
#endif

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
    // If VBUS is source output, then keep tracking
    if((GET_PMIC_BIDIR_MODE() == _PD_POWER_SRC) && (GET_PMIC_OUTPUT_ENABLE() == _ON))
    {
        // Set 200ms Timer Event for Voltage Compensation
        ucTimerEvent |= 0x02;

        // Translate Current of 10bSARADC to 10mA/bit
        usCurrentValue = ((WORD)((((DWORD)ScalerTypeCPowerRx0CorrectionToIdealData(ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_IMON))) * 8 * 1000) / 1024 / 10));

        // Calculate VIL of compesation voltage (10mV)
        usSchmittVIL = GET_RX0_OUTPUT_VOL() + ((usCurrentValue * 10) / _VOLTAGE_COMPESATION_CURRENT_UNIT);

        // Calculate VIH of compesation voltage (10mV)
        usSchmittVIH = GET_RX0_OUTPUT_VOL() + (((usCurrentValue + 5) * 10) / _VOLTAGE_COMPESATION_CURRENT_UNIT);

        // Minimum Current Setting for different PDO type
        usCurrent = GET_RX0_OUTPUT_CUR();
        usCurrent = (usCurrent < _TYPE_C_PMIC_MIN_CURRENT ? _TYPE_C_PMIC_MIN_CURRENT : usCurrent);

        // Voltage compensation detect
        if(GET_RX0_OUTPUT_VOL() < usSchmittVIL)
        {
            DebugMessageTypeC("0.Pmic:Currnet Value", usCurrentValue);
            DebugMessageTypeC("0.Pmic:Voltage Change", usSchmittVIL);

            if(ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(_TYPE_C_PMIC_DIRECTION_SRC, usSchmittVIL, usCurrent) == _TYPE_C_PMIC_CONTROL_FAIL)
            {
                ucResult = _FAIL;
            }
        }
        else if(GET_RX0_OUTPUT_VOL() > usSchmittVIH)
        {
            DebugMessageTypeC("0.Pmic:Currnet Value", usCurrentValue);
            DebugMessageTypeC("0.Pmic:Voltage Change", usSchmittVIH);

            if(ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(_TYPE_C_PMIC_DIRECTION_SRC, usSchmittVIH, usCurrent) == _TYPE_C_PMIC_CONTROL_FAIL)
            {
                ucResult = _FAIL;
            }
        }
    }
    else
    {
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PMIC_TRACKING);
    }
#endif // End of #if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
    // PMIC GPIO detection
    if((GET_PMIC_BIDIR_MODE() == _PD_POWER_SRC) && (GET_PMIC_OUTPUT_ENABLE() == _ON))
    {
        // Set 200ms Timer Event for INT Pin Check
        ucTimerEvent |= 0x04;

        // Check GPIO status
        if(PCB_PMIC_INTERRUPT_DETECT() == _PMIC_INTERRUPT_ON)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PMIC_TRACKING);

            ScalerTypeCPmicRx0Setting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0);

            DebugMessageTypeC("Pmic GPIO interrupt!", PCB_PMIC_INTERRUPT_DETECT());

#if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)
            // Set Recovery
            SET_TYPE_C_ERROR_RECOVERY();
#else
            // Reset PMIC
            ExternalDeviceInterfaceTypeCPmicUnattachReset();

            // Send Hard reset
            ScalerTypeCRx0PdSendHardRst();
#endif
        }
    }
    else
    {
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PMIC_TRACKING);
    }
#endif // End of #if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)

#if(_TYPE_C_PMIC_DEBUG == _ON)
    ucTimerEvent |= 0x10;

    ExternalDeviceInterfaceTypeCPmicDebugCheckStatus();
#endif // End of #if(_TYPE_C_PMIC_DEBUG == _ON)

    // Active Timer Event
    if(ucTimerEvent != 0x00)
    {
        if((ucTimerEvent & 0x01) != 0x00)
        {
            ScalerTimerReactiveTimerEvent(10, _SCALER_TIMER_EVENT_PMIC_TRACKING);
        }
        else
        {
            ScalerTimerReactiveTimerEvent(200, _SCALER_TIMER_EVENT_PMIC_TRACKING);
        }
    }

    return ucResult;
}

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
//--------------------------------------------------
// Description  : RX0 PMIC FW Ocp interrupt handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0FwOcpIntHandler_EXINT0(void) using 1
{
#if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
    BYTE ucI = 0x00;
#endif

    CLR_PMIC_FW_OCP_CHECK_START();

    if(ScalerTypeCPowerAdcIntCheck_EXINT0(_TYPE_C_UFP_IMON) == _TRUE)
    {
        // Clear and Disable Int
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_IMON, _DISABLE);
        ScalerTypeCPowerClearAdcIntFlag_EXINT0(_TYPE_C_UFP_IMON);

#if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
        for(ucI = 0; ucI < 2; ucI++)
        {
            if(ScalerTypeCPowerRx0CorrectionToIdealData_EXINT0(ScalerTypeCPowerGetAdcOutput_EXINT0(_TYPE_C_UFP_VMON)) < _TYPE_C_ADC_SHORT_THRESHOLD)
            {
                // Disable Pmic
                ScalerTypeCPmicRx0Setting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0);

#if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)
                // Set Error Recovery
                ScalerTypeCRx0PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_ERROR_RECOVERY);
#elif(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_HARD_RESET)
                // Set OCP Event (PD3.0 : Alert + Hard Reset / PD2.0 : Hard Reset)
                ScalerTypeCRx0PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_POWER_OCP);
#endif // End of #if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)

                return;
            }
        }

        // Set WD Timer to Delay Shutdown Pmic
        ScalerTimerWDActivateTimerEvent_EXINT0(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN, _SCALER_WD_TIMER_EVENT_PMIC_RX0_FW_OCP_DELAY);
#else
        // Disable Pmic
        ScalerTypeCPmicRx0Setting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0);

#if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)
        // Set Error Recovery
        ScalerTypeCRx0PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_ERROR_RECOVERY);
#elif(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_HARD_RESET)
        // Set OCP Event (PD3.0 : Alert + Hard Reset / PD2.0 : Hard Reset)
        ScalerTypeCRx0PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_POWER_OCP);
#endif // End of #if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
    }
}

#if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
//--------------------------------------------------
// Description  : PMIC FW Ocp Delay interrupt handler
// Input Value  : ucSlaveAddr : I2C Slave Address
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID) using 3
{
    switch(enumEventID)
    {
        case _SCALER_WD_TIMER_EVENT_PMIC_RX0_FW_OCP_DELAY:

            CLR_PMIC_FW_OCP_CHECK_START();

            // Disable Pmic
            ScalerTypeCPmicRx0Setting_WDINT(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0);

#if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)
            // Set Error Recovery
            ScalerTypeCRx0PdSetSystemEvent_WDINT(_PD_SYS_EVENT_ERROR_RECOVERY);
#elif(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_HARD_RESET)
            // Set OCP Event (PD3.0 : Alert + Hard Reset / PD2.0 : Hard Reset)
            ScalerTypeCRx0PdSetSystemEvent_WDINT(_PD_SYS_EVENT_POWER_OCP);
#endif // End of #if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)

            break;

        default:

            break;
    }
}
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
#elif(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
//--------------------------------------------------
// Description  : RX0 PMIC FW Ocp Protect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0OcpProtect(void)
{
    DebugMessageTypeC("Pmic turn-off", 0x00);

    CLR_PMIC_OCP_PROTECT_START();

    ScalerTypeCPmicRx0Setting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0);

#if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)
    // Set Error Recovery
    ScalerTypeCRx0PdSetSystemEvent(_PD_SYS_EVENT_ERROR_RECOVERY);
#elif(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_HARD_RESET)
    // Set OCP Event (PD3.0 : Alert + Hard Reset / PD2.0 : Hard Reset)
    ScalerTypeCRx0PdSetSystemEvent(_PD_SYS_EVENT_POWER_OCP);
#endif // End of #if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)
}
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#endif // End of #if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : RX0 PMIC OVP interrupt handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPmicRx0OvpUvpIntHandler_EXINT0(void) using 1
{
    if((ScalerGetBit_EXINT(P7F_1A_10B_ADC_COMP_INT, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P7F_1B_10B_ADC_COMP_INT_EN, _BIT0) == _BIT0))
    {
        // Clear FW VBUS Check Start Flag
        CLR_PMIC_FW_VBUS_CHECK_START();

        // Disable INT
        ScalerTypeCPowerRangeIntControl_EXINT0(_TYPE_C_UFP_VMON, _DISABLE);

        // Disable PMIC
        ScalerTypeCPmicRx0Setting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0);

#if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)
        // Set Error Recovery
        ScalerTypeCRx0PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_ERROR_RECOVERY);
#elif(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_HARD_RESET)
        // Set OVP Event (PD3.0 : Alert + Hard Reset / PD2.0 : Hard Reset)
        ScalerTypeCRx0PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_POWER_OVP);
#endif // End of #if(_TYPE_C_PMIC_PROTECTION_METHOD == _TYPE_C_PMIC_ERROR_RECOVERY)
    }
}
#endif // End of #if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON) && (_TYPE_C_PMIC_TYPE != _PMIC_NONE))
