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
// ID Code      : ScalerCommonTypeCPower.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _TYPE_C_POWER_DEBUG         _OFF

#define _ADC_OUTPUT_MAX_TIME        2

// Unit = 0.1V (Use Unsigned Long to prevent int overflow during calculation)
#define _TYPE_C_ADC_MAX_VOLTAGE     240
#define _TYPE_C_ADAPTOR_VOLTAGE     120

#define _TYPE_C_VSAFE5V_UP_BND      57
#define _TYPE_C_VSAFE5V_LOW_BND     44

#define _TYPE_C_VSAFE0V_UP_BND      5

// Just for Retimer On/Off
#if(_USB3_RETIMER_SUPPORT == _ON)
#define _USB3_VBUS_ON_THR           44
#define _USB3_VBUS_OFF_THR          37
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
StructTypeCPowerInfo g_stTpcRx0PowerInfo;
#endif // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

#if(_USB3_RETIMER_SUPPORT == _ON)
StructUsb3VbusOnOffThr g_stU3VbusOnOffThr;
#endif
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTypeCPowerClkSel(BYTE ucClockSel);
void ScalerTypeCPowerInitial(void);
void ScalerTypeCPowerLocPowReset(void);
bit ScalerTypeCPowerCheckLocPowExist(bit bCondition);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
WORD ScalerTypeCPowerRx0CorrectionToRawData(WORD usIdealVoltage);
WORD ScalerTypeCPowerRx0CorrectionToRawData_EXINT0(WORD usIdealVoltage);
#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
WORD ScalerTypeCPowerRx0CorrectionToIdealData(WORD usRawData);
#endif
#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) && (_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0))
WORD ScalerTypeCPowerRx0CorrectionToIdealData_EXINT0(WORD usRawData);
#endif
void ScalerTypeCPowerRx0UnattachReset(void);
void ScalerTypeCPowerRx0UnattachVthAdjust(void);
void ScalerTypeCPowerRx0UnattachVthAdjust_EXINT0(WORD usVoltage);
bit ScalerTypeCPowerRx0CheckVbusSafe0V(void);
bit ScalerTypeCPowerRx0CheckVbusSafe5V(void);
#if(_USB3_RETIMER_SUPPORT == _ON)
bit ScalerTypeCPowerRx0CheckVbus(bit bAction);
#endif
// bit ScalerTypeCPowerRx0CheckVbusReady(WORD usVoltage);
void ScalerTypeCPowerRx0VbusControl(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
void ScalerTypeCPowerRx0VbusControl_EXINT0(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
void ScalerTypeCPowerRx0VbusControl_WDINT(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
void ScalerTypeCPowerIntHandler_EXINT0(void);
bit ScalerTypeCPowerCheckVbusCapability(EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
BYTE ScalerTypeCPowerCheckVbusCapability_EXINT0(EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
BYTE ScalerTypeCPowerCheckVbusCapability_WDINT(EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
#endif // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

WORD ScalerTypeCPowerGetAdcOutput(EnumTypeCAdcChannel enumChannel);
void ScalerTypeCPowerRangeIntControl(EnumTypeCAdcChannel enumChannel, bit bAction);
void ScalerTypeCPowerRangeIntSetting(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
void ScalerTypeCPowerVbusCompIntControl(EnumAdcVbusCompChannel enumChannel, bit bType, bit bAction);
// void ScalerTypeCPowerVbusCompIntControl_EXINT0(EnumAdcVbusCompChannel enumChannel, bit bType, bit bAction);
void ScalerTypeCPowerVbusCompDebounce(EnumAdcVbusCompChannel enumChannel, bit bType, BYTE ucDebCycle);
void ScalerTypeCPowerVbusCompThrSetting(EnumAdcVbusCompChannel enumChannel, bit bType, WORD usThreshold);
void ScalerTypeCPowerVbusCompThrSetting_EXINT0(EnumAdcVbusCompChannel enumChannel, bit bType, WORD usThreshold);
#if((_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC))
void ScalerTypeCPowerRangeIntControl_EXINT0(EnumTypeCAdcChannel enumChannel, bit bAction);
void ScalerTypeCPowerRangeIntControl_WDINT(EnumTypeCAdcChannel enumChannel, bit bAction);
void ScalerTypeCPowerRangeIntSetting_EXINT0(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
void ScalerTypeCPowerRangeIntSetting_WDINT(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
#endif // End of #if((_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC))
#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
void ScalerTypeCPowerClearAdcIntFlag_EXINT0(EnumTypeCAdcChannel enumChannel);
BYTE ScalerTypeCPowerAdcIntCheck_EXINT0(EnumTypeCAdcChannel enumChannel);
#if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
WORD ScalerTypeCPowerGetAdcOutput_EXINT0(EnumTypeCAdcChannel enumChannel);
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Type C ADC Clk Setting (Always Use IOSC = 28MHz)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerClkSel(BYTE ucClockSel)
{
    if(ucClockSel == _IOSC_CLK)
    {
        // [0x7F03] [7:6] Clk Sel = IOSC (b'00) / [5:0] adc_clk_div = b'0004
        ScalerSetByte(P7F_03_10B_ADC_CLK_CLRT, 0x05);

#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
        ScalerTypeCPmicHwIICSetFreqDiv(_IOSC_CLK);
#endif

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        ScalerTypeCRx0CcClkSel(_IOSC_CLK);
        ScalerTypeCRx0PdClkSel(_IOSC_CLK);
#endif
    }
}

//--------------------------------------------------
// Description  : TypeC Power Initail Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerInitial(void)
{
    // -------------------- ADC AIF Setting ---------------------

    // [0x7F55] LDO Setting : [5] reg_sar_ckout_sel = Reserve ckout / [4] reg_ldo_trim = LDO Normal Mode / [0] reg_pow_ldo = _ENABLE
    ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~(_BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));

    // [0x7F59] Low Pass Filter Setting
    ScalerSetBit(P7F_59_ADC_LPF, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

#if(_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON)
    // [0x7F56] Fast Role Swap Comparator Setting ([5:0] Vth = 250 ~ 565 mV, Delta = 5mV)
    ScalerSetBit(P7F_56_FRS_VBUS_COMP0, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5));
#endif

    // -------------------- ADC Output Setting ---------------------

    // [0x7F01] ADC Output Channel Enable

    // [7:6] Channel4/3 (DFP_VOMN/IMON)
#if(_TYPE_C_EMB_DFP_PORT_SUPPORT == _ON)
    ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#else
    ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT7 | _BIT6), 0x00);
#endif

    // [5] Channel2 (LOC_PW)
    ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~_BIT5, _BIT5);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) || (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON))
    // [4:3] Channel1/0 (UFP_VOMN/IMON)
    ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
#else
    // [4:3] Channel1/0 (UFP_VOMN/IMON)
    ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~_BIT3, _BIT3);
#endif
#else
    ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT4 | _BIT3), 0x00);
#endif

    // [0x7F05] [2:0]ADC Number of Outputs Averaged (1/2/4/8/16/32) = 4
    ScalerSetBit(P7F_05_10B_ADC_AVE_CTRL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // [0x7F07-08] ADC Switch Time (#ADC_CLK Cycles) = 8 * 12 clk cycles
    ScalerSetBit(P7F_07_10B_ADC_SW_TM0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P7F_08_10B_ADC_SW_TM1, 0x60);

    // [0x7F09-0A] ADC Idle Time (#ADC_CLK Cycles) = 0 clk cycle
    ScalerSetBit(P7F_09_10B_ADC_IDLE_TM0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P7F_0A_10B_ADC_IDLE_TM1, 0x00);

    // [0x7F0B-0F] Number Of Averaged Outputs to be Debounced For Channel0-4
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    ScalerSetByte(P7F_0B_10B_ADC_A0_DEB_CLRT, 0x02);
    ScalerSetByte(P7F_0C_10B_ADC_A1_DEB_CLRT, 0x02);
#endif

    ScalerSetByte(P7F_0D_10B_ADC_A2_DEB_CLRT, 0x02);

#if(_TYPE_C_EMB_DFP_PORT_SUPPORT == _ON)
    ScalerSetByte(P7F_0E_10B_ADC_A3_DEB_CLRT, 0x02);
    ScalerSetByte(P7F_0F_10B_ADC_A4_DEB_CLRT, 0x02);
#endif

    // [0x7F00] ADC Mode Setting : [7] Normal Mode / [6] Auto Mode = Enable / [5] ADC En = Enable
    ScalerSetBit(P7F_00_10B_ADC_CTL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    // Set Debounce For UFP Vbus On/Off Comparator Detection
    ScalerTypeCPowerVbusCompDebounce(_TYPE_C_A0_UFP_VBUS, _ON, 0x02);
    ScalerTypeCPowerVbusCompDebounce(_TYPE_C_A0_UFP_VBUS, _OFF, 0x02);
#endif

    // Set Debounce For Local Power On/Off Comparator Detection
    ScalerTypeCPowerVbusCompDebounce(_TYPE_C_A2_LOC_PW, _ON, 0x02);
    ScalerTypeCPowerVbusCompDebounce(_TYPE_C_A2_LOC_PW, _OFF, 0x02);

#if(_TYPE_C_EMB_DFP_PORT_SUPPORT == _ON)
    // Set Debounce For DFP Vbus On/Off Comparator Detection
    ScalerTypeCPowerVbusCompDebounce(_TYPE_C_A4_DFP_VBUS, _ON, 0x02);
    ScalerTypeCPowerVbusCompDebounce(_TYPE_C_A4_DFP_VBUS, _OFF, 0x02);
#endif

    // [0x7F75] ADC Switch Setting : [5:4] FR_SWAP Comp = UFP Vbus / [3:2] CC HW Det = UFP Vbus
    ScalerSetBit(P7F_75_FRS_SIG_CTRL_UPF, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // Reset ADC Related Flags
    SET_RX0_VBUS_STATUS(_OFF);

    // Initiate Avaliable Power = PMIC Max Power
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    SET_RX0_REQ_PWR(0);
#endif

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_POWER_DEBUG == _ON))
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    DebugMessageTypeC("    [PWR INIT] Rx0 Output Power : ", GET_RX0_REQ_PWR());
#endif
#endif  // End of #if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_POWER_DEBUG == _ON))

#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
    ScalerTypeCPmicRx0Initial();
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
    SET_USB3_VBUS_ON_THR(_USB3_VBUS_ON_THR);
    SET_USB3_VBUS_OFF_THR(_USB3_VBUS_OFF_THR);
#endif
    SET_TYPE_C_5V_UP_BND(_TYPE_C_VSAFE5V_UP_BND);
    SET_TYPE_C_5V_LOW_BND(_TYPE_C_VSAFE5V_LOW_BND);
    SET_TYPE_C_0V_UP_BND(_TYPE_C_VSAFE0V_UP_BND);
    SET_TYPE_C_LOC_PW_ON_THR(_TYPE_C_ADAPTOR_VOLTAGE * 9 / 10);
    SET_TYPE_C_LOC_PW_OFF_THR(_TYPE_C_ADAPTOR_VOLTAGE * 8 / 10);

    // Reset Local Power Channel (Channel 2)
    ScalerTypeCPowerLocPowReset();
}

//--------------------------------------------------
// Description  : Reset ADC Local Power Channel Threshold to Default Value and Disable IRQs
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerLocPowReset(void)
{
    // 1. Disable Local Power Range Detection IRQ
    ScalerTypeCPowerRangeIntControl(_TYPE_C_LOC_PW, _DISABLE);

    // 2. Disable Local Power Digital Comparator On/Off Detection IRQs
    ScalerTypeCPowerVbusCompIntControl(_TYPE_C_A2_LOC_PW, _ON, _DISABLE);
    ScalerTypeCPowerVbusCompIntControl(_TYPE_C_A2_LOC_PW, _OFF, _DISABLE);

    // 3. Reset Local Power Didital Comparator On/Off Detection Threshold
    ScalerTypeCPowerVbusCompThrSetting(_TYPE_C_A2_LOC_PW, _ON, GET_TYPE_C_LOC_PW_ON_THR());
    ScalerTypeCPowerVbusCompThrSetting(_TYPE_C_A2_LOC_PW, _OFF, GET_TYPE_C_LOC_PW_OFF_THR());
}

//--------------------------------------------------
// Description  : Check if Local Power (AC Adaptor) Exists
// Input Value  : None
// Output Value : 0 : No Local Power / 1 : Local Power Exist
//--------------------------------------------------
bit ScalerTypeCPowerCheckLocPowExist(bit bCondition)
{
    bit bDetResult = _FALSE;
    if(bCondition == _ON)
    {   // Check Local Power On IRQ Flag
        if(ScalerGetBit(P7F_3A_10B_ADC_VBUS_INT, _BIT1) == _BIT1)
        {
            bDetResult = _TRUE;
        }
        else
        {
            bDetResult = _FALSE;
        }
    }
    else
    {   // Check Local Power Off IRQ Flag
        if(ScalerGetBit(P7F_3A_10B_ADC_VBUS_INT, _BIT5) == _BIT5)
        {
            bDetResult = _TRUE;
        }
        else
        {
            bDetResult = _FALSE;
        }
    }
    // Clear Local Power On/Off IRQ Flag For Update Next Time
    ScalerSetBit(P7F_3A_10B_ADC_VBUS_INT, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));

    return bDetResult;
}

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

//--------------------------------------------------
// Description  : Correction Ideal Voltage to Raw Data
// Input Value  : Voltage (Unit:0.1V)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCPowerRx0CorrectionToRawData(WORD usIdealVoltage)
{
    DWORD ulCorrectionCompThr = (DWORD)(usIdealVoltage);

    // Transition V to mV (*100)
    // Transition Voltage to ADC input domain (/12)
    ulCorrectionCompThr = ulCorrectionCompThr * 100 / 12;

    // Ident offset is positive or negative
    if(g_bsign == 0x01)
    {
        ulCorrectionCompThr = (ulCorrectionCompThr + g_ucoffset) * 1000 / g_usSlop;
    }
    else
    {
        if(ulCorrectionCompThr > g_ucoffset)
        {
            ulCorrectionCompThr = (ulCorrectionCompThr - g_ucoffset) * 1000 / g_usSlop;
        }
        else
        {
            ulCorrectionCompThr = (ulCorrectionCompThr - 0) * 1000 / 1953;
        }
    }

    return (WORD)ulCorrectionCompThr;
}

//--------------------------------------------------
// Description  : Correction Ideal Voltage to Raw Data
// Input Value  : Voltage (Unit:0.1V)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCPowerRx0CorrectionToRawData_EXINT0(WORD usIdealVoltage) using 1
{
    DWORD ulCorrectionCompThr = (DWORD)usIdealVoltage;

    // Transition V to mV (*100)
    // Transition Voltage to ADC input domain (/12)
    ulCorrectionCompThr = ulCorrectionCompThr * 100 / 12;

    // Ident offset is positive or negative
    if(g_bsign == 0x01)
    {
        ulCorrectionCompThr = (ulCorrectionCompThr + g_ucoffset) * 1000 / g_usSlop;
    }
    else
    {
        if(ulCorrectionCompThr > g_ucoffset)
        {
            ulCorrectionCompThr = (ulCorrectionCompThr - g_ucoffset) * 1000 / g_usSlop;
        }
        else
        {
            ulCorrectionCompThr = (ulCorrectionCompThr - 0) * 1000 / 1953;
        }
    }

    return (WORD)ulCorrectionCompThr;
}

#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
//--------------------------------------------------
// Description  : Correction Raw Data to Ideal Data
// Input Value  : ADC_Code (0 ~ 1024)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCPowerRx0CorrectionToIdealData(WORD usRawData)
{
    DWORD ulResult = (DWORD)(usRawData);
    DWORD ulAx = 0;
    DWORD ulB = 0;

    ulAx = (DWORD)(g_usSlop) * ulResult / 1000;
    ulB = g_ucoffset;

    // check offset is positive or negative
    if(g_bsign == 0x01)
    {
        if(ulAx > ulB)
        {
            ulResult = ((ulAx - ulB) * 512 / 1000);
        }
        else
        {
            ulResult = 0;
        }
    }
    else
    {
        ulResult = ((ulAx + ulB) * 512 / 1000);
    }

    return (WORD)ulResult;
}
#endif

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) && (_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0))
//--------------------------------------------------
// Description  : Correction Raw Data to Ideal Data
// Input Value  : ADC_Code (0 ~ 1024)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCPowerRx0CorrectionToIdealData_EXINT0(WORD usRawData) using 1
{
    DWORD ulResult = (DWORD)(usRawData);
    DWORD ulAx = 0;
    DWORD ulB = 0;

    ulAx = (DWORD)(g_usSlop) * ulResult / 1000;
    ulB = g_ucoffset;

    // check offset is positive or negative
    if(g_bsign == 0x01)
    {
        if(ulAx > ulB)
        {
            ulResult = ((ulAx - ulB) * 512 / 1000);
        }
        else
        {
            ulResult = 0;
        }
    }
    else
    {
        ulResult = ((ulAx + ulB) * 512 / 1000);
    }

    return (WORD)ulResult;
}
#endif

//--------------------------------------------------
// Description  : Reset ADC UFP Vbus Channel (ch1/2) Threshold to Default Value and Disable IRQs
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRx0UnattachReset(void)
{
    // 1. Disable Vbus Range Detection IRQ
    ScalerTypeCPowerRangeIntControl(_TYPE_C_UFP_VMON, _DISABLE);

    // 2. Reset Vbus Range Detection Threshold to vSafe5V 3.67 ~ 5.5V
    ScalerTypeCPowerRangeIntSetting(_TYPE_C_UFP_VMON, GET_TYPE_C_5V_UP_BND(), GET_TYPE_C_5V_LOW_BND(), _TYPE_C_ADC_WITHIN_RANGE);

    // 3. Disable Local Power Digital Comparator On/Off Detection IRQs
    ScalerTypeCPowerVbusCompIntControl(_TYPE_C_A0_UFP_VBUS, _ON, _DISABLE);
    ScalerTypeCPowerVbusCompIntControl(_TYPE_C_A0_UFP_VBUS, _OFF, _DISABLE);

    // 4. Reset Local Power Digital Comparator On/Off Detection Threshold to 4.6V
    ScalerTypeCPowerVbusCompThrSetting(_TYPE_C_A0_UFP_VBUS, _ON, GET_TYPE_C_5V_LOW_BND());
    ScalerTypeCPowerVbusCompThrSetting(_TYPE_C_A0_UFP_VBUS, _OFF, GET_TYPE_C_5V_LOW_BND());

#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
    // 5. Reset Pmic
    ScalerTypeCPmicRx0Reset();
#endif
}

//--------------------------------------------------
// Description  : Set Vbus Thr When Attached
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRx0UnattachVthAdjust(void)
{
    // Set Threshold to 3.67V --> 3.7V (Unit:0.1V)
    WORD usVoltage = ScalerTypeCPowerRx0CorrectionToRawData(37);

    // Set Unattach Vth to Digital On/Off Comparator
    ScalerTypeCPowerVbusCompThrSetting(_TYPE_C_A0_UFP_VBUS, _ON, usVoltage);
    ScalerTypeCPowerVbusCompThrSetting(_TYPE_C_A0_UFP_VBUS, _OFF, usVoltage);
}

//--------------------------------------------------
// Description  : Set Vbus Thr When Attached
// Input Value  : ucVoltage : Negotiated Voltage in 10mV
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRx0UnattachVthAdjust_EXINT0(WORD usVoltage) using 1
{
    // Sink Unattach Voltage "Refer to CC Spec Table 4-3" (Unit:10mV)
    if(usVoltage == 500)
    {
        // When PD Contract = 5V or No PD : Use 3.67V (367 * 10mV)
        // Adjust Sink Unattach Vth (usVoltage * 10 / 100 = usVoltage / 10)
        usVoltage = ScalerTypeCPowerRx0CorrectionToRawData_EXINT0(367 / 10);
    }
    else
    {
        // When PD Contract Above 5V : [(Vnew * 0.95) - 1250mV] * 0.9
        // Adjust Sink Unattach Vth (usVoltage * 10 / 100 = usVoltage / 10)
        usVoltage = ScalerTypeCPowerRx0CorrectionToRawData_EXINT0((((usVoltage * 19 / 20) - 125) * 9 / 10) / 10);
    }

    // Adjust Sink Unattach Vth
    ScalerTypeCPowerVbusCompThrSetting_EXINT0(_TYPE_C_A0_UFP_VBUS, _ON, usVoltage);
    ScalerTypeCPowerVbusCompThrSetting_EXINT0(_TYPE_C_A0_UFP_VBUS, _OFF, usVoltage);
}

//--------------------------------------------------
// Description  : Check if UFP Vbus Voltage is vSafe0V
// Input Value  : None
// Output Value : 0 : Not vSafe0V / 1 : Vbus is vSafe0V
//--------------------------------------------------
bit ScalerTypeCPowerRx0CheckVbusSafe0V(void)
{
#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_POWER_DEBUG == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
    DebugMessageTypeC("    [PWR CHK] Vbus Vol : ", ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON));
    DebugMessageTypeC("    [PWR CHK] vSafe0v Vol Max: ", GET_TYPE_C_0V_UP_BND());
#endif

    if(ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON) <= GET_TYPE_C_0V_UP_BND())
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check if UFP Vbus Voltage is vSafe5V
// Input Value  : None
// Output Value : 0 : Not vSafe5V / 1 : Vbus is vSafe5V
//--------------------------------------------------
bit ScalerTypeCPowerRx0CheckVbusSafe5V(void)
{
#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_POWER_DEBUG == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
    DebugMessageTypeC("    [PWR CHK] Vbus Vol : ", ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON));
    DebugMessageTypeC("    [PWR CHK] vSafe5v Vol Min : ", GET_TYPE_C_5V_LOW_BND());
#endif

    if((ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON) >= GET_TYPE_C_5V_LOW_BND()) && (ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON) <= GET_TYPE_C_5V_UP_BND()))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check if UFP Vbus Voltage is Above vSafe5V
// Input Value  : None
// Output Value : 0 : Vbus < Not vSafe5V / 1 : Vbus > vSafe5V
//--------------------------------------------------
bit ScalerTypeCPowerRx0CheckVbus(bit bAction)
{
    if(bAction == _ENABLE)
    {
        if(ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON) >= GET_USB3_VBUS_ON_THR())
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        if(ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON) <= GET_USB3_VBUS_OFF_THR())
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
}
#endif

/*
//--------------------------------------------------
// Description  : Check if UFP Vbus Voltage is in the Requested Range
// Input Value  : usVoltage : Unit = 50mV
// Output Value : _TRUE / _FLASE
//--------------------------------------------------
bit ScalerTypeCPowerRx0CheckVbusReady(WORD usVoltage)
{
    if(usVoltage == 100)
    {   // Check Vbus = vSafe5V (4.5 ~ 5.5 V)
        if((ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON) >= (WORD)((DWORD)usVoltage * 213 / 100 * 9 / 10)) &&
           (ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON) <= (WORD)((DWORD)usVoltage * 213 / 100 * 11 / 10)))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else if(usVoltage == 0)
    {   // Check Vbus = vSafe0V
        if(ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON) <= GET_TYPE_C_0V_UP_BND())
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {   // Check Other Voltage Reange (0.95 ~ 1.05 vSrcNew) : 2.13 = [usVoltage * 50mV * 1024(10-bit)] / [24(Max Vol) * 1000]
        if((ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON) >= (WORD)((DWORD)usVoltage * 213 / 100 * 95 / 100)) &&
           (ScalerTypeCPowerGetAdcOutput(_TYPE_C_UFP_VMON) <= (WORD)((DWORD)usVoltage * 213 / 100 * 105 / 100)))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
}
*/

//--------------------------------------------------
// Description  : Control Rx0 Vbus to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                usVoltage : 0 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRx0VbusControl(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent)
{
    // Calculate Requested Power to Unit = 0.1 W
    WORD usRegPower = ((DWORD)usVoltage * usCurrent / 1000);
#if(_TYPE_C_PMIC_TYPE == _PMIC_NONE)
    bPowerDirection = bPowerDirection;
    enumPdoType = enumPdoType;
#endif

    if(bAction == _ON)
    {
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
        // Control PMIC to Turn On Vbus Power
        ScalerTypeCPmicRx0Setting(bAction, bPowerDirection, enumPdoType, usVoltage, usCurrent);
#endif

        // Distribute New-Requested Power, and Update Avaliable Power
        SET_RX0_REQ_PWR(usRegPower);
        SET_RX0_OUTPUT_VOL(usVoltage);
        SET_RX0_OUTPUT_CUR(usCurrent);
        SET_RX0_VBUS_STATUS(_ON);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_POWER_DEBUG == _ON))
        DebugMessageTypeC("    [PWR/PMIC] Vbus Power On : ", bAction);
#endif
    }
    else
    {
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
        // Control PMIC to Turn Off Vbus Power
        ScalerTypeCPmicRx0Setting(bAction, bPowerDirection, enumPdoType, usVoltage, usCurrent);
#endif

        // Return Rx0 Requested Power Back
        SET_RX0_REQ_PWR(0);
        SET_RX0_OUTPUT_VOL(0);
        SET_RX0_OUTPUT_CUR(0);
        SET_RX0_VBUS_STATUS(_OFF);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_POWER_DEBUG == _ON))
        DebugMessageTypeC("    [PWR] Vbus Power Off : ", bAction);
#endif
    }

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_POWER_DEBUG == _ON))
    DebugMessageTypeC("    ----> Request Power : ", usRegPower);
    DebugMessageTypeC("    ----> Output Power : ", GET_RX0_REQ_PWR());
    DebugMessageTypeC("    ----> Remain Power : ", (GET_RX0_MAX_POWER() - GET_RX0_REQ_PWR()));
#endif
}

//--------------------------------------------------
// Description  : Control Rx0 Vbus to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                usVoltage : 0 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRx0VbusControl_EXINT0(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent) using 1
{
    // Calculate Requested Power to Unit = 0.1 W
    WORD usRegPower_EXINT = ((DWORD)usVoltage * usCurrent / 1000);
#if(_TYPE_C_PMIC_TYPE == _PMIC_NONE)
    bPowerDirection = bPowerDirection;
    enumPdoType = enumPdoType;
#endif

    if(bAction == _ON)
    {
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
        // Control PMIC to Turn On Vbus Power
        ScalerTypeCPmicRx0Setting_EXINT0(bAction, bPowerDirection, enumPdoType, usVoltage, usCurrent);
#endif

        // Distribute New-Requested Power, and Update Avaliable Power
        SET_RX0_REQ_PWR(usRegPower_EXINT);
        SET_RX0_OUTPUT_VOL(usVoltage);
        SET_RX0_OUTPUT_CUR(usCurrent);
        SET_RX0_VBUS_STATUS(_ON);
    }
    else
    {
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
        // Control PMIC to Turn Off Vbus Power
        ScalerTypeCPmicRx0Setting_EXINT0(bAction, bPowerDirection, enumPdoType, usVoltage, usCurrent);
#endif

        SET_RX0_REQ_PWR(0);
        SET_RX0_OUTPUT_VOL(0);
        SET_RX0_OUTPUT_CUR(0);
        SET_RX0_VBUS_STATUS(_OFF);
    }
}

//--------------------------------------------------
// Description  : Control Rx0 Vbus to Directed Voltage
// Input Value  : bAction : _ON / _OFF
//                usVoltage : 0 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRx0VbusControl_WDINT(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent) using 3
{
    // Calculate Requested Power to Unit = 0.1 W
    WORD usRegPower_WDINT = ((DWORD)usVoltage * usCurrent / 1000);
#if(_TYPE_C_PMIC_TYPE == _PMIC_NONE)
    bPowerDirection = bPowerDirection;
    enumPdoType = enumPdoType;
#endif

    if(bAction == _ON)
    {
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
        // Control PMIC to Turn On Vbus Power
        ScalerTypeCPmicRx0Setting_WDINT(bAction, bPowerDirection, enumPdoType, usVoltage, usCurrent);
#endif

        // Distribute New-Requested Power, and Update Avaliable Power
        SET_RX0_REQ_PWR(usRegPower_WDINT);
        SET_RX0_OUTPUT_VOL(usVoltage);
        SET_RX0_OUTPUT_CUR(usCurrent);
        SET_RX0_VBUS_STATUS(_ON);
    }
    else
    {
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
        // Control PMIC to Turn Off Vbus Power
        ScalerTypeCPmicRx0Setting_WDINT(bAction, bPowerDirection, enumPdoType, usVoltage, usCurrent);
#endif

        SET_RX0_REQ_PWR(0);
        SET_RX0_OUTPUT_VOL(0);
        SET_RX0_OUTPUT_CUR(0);
        SET_RX0_VBUS_STATUS(_OFF);
    }
}

//--------------------------------------------------
// Description  : Interrupt Handler For TypeC Power
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerIntHandler_EXINT0(void) using 1
{
    if((ScalerGetBit_EXINT(P7F_3A_10B_ADC_VBUS_INT, _BIT5) == _BIT5) && (ScalerGetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, _BIT5) == _BIT5))
    {   // Local Power Off Interrupt
    }

    if((ScalerGetBit_EXINT(P7F_3A_10B_ADC_VBUS_INT, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, _BIT1) == _BIT1))
    {   // Local Power On Interrupt
    }

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    ScalerTypeCPmicRx0OvpUvpIntHandler_EXINT0();
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
    ScalerTypeCPmicRx0FwOcpIntHandler_EXINT0();
#endif
}

//--------------------------------------------------
// Description  : Check Vbus Capability is legal
// Input Value  : None
// Output Value : PD SRC Cap Sent Status
//--------------------------------------------------
bit ScalerTypeCPowerCheckVbusCapability(EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent)
{
    // Calculate Requested Power to Unit = 0.1 W
    WORD usRegPower = ((DWORD)usVoltage * usCurrent / 1000);
    bit bVbusCheck = _FALSE;

    switch(enumPdoType)
    {
        case _PD_FIX_SUPPLY_PDO:

            if((usVoltage <= 2100) && (usCurrent <= ScalerTypeCRx0PdGetCableMaxCurrent()) && (usRegPower <= GET_RX0_MAX_POWER()))
            {
                bVbusCheck = _TRUE;
            }

            break;

        case _PD_3_PROGRAMMABLE_PDO:

            if((usVoltage <= 2100) && (usCurrent <= ScalerTypeCRx0PdGetCableMaxCurrent()))
            {
                bVbusCheck = _TRUE;
            }

            break;

        default:

            break;
    }

    return bVbusCheck;
}

//--------------------------------------------------
// Description  : Check Vbus Capability is legal
// Input Value  : None
// Output Value : PD SRC Cap Sent Status
//--------------------------------------------------
BYTE ScalerTypeCPowerCheckVbusCapability_EXINT0(EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent) using 1
{
    // Calculate Requested Power to Unit = 0.1 W
    WORD usRegPower_EXINT = ((DWORD)usVoltage * usCurrent / 1000);
    BYTE ucVbusCheck_EXINT = _FALSE;

    switch(enumPdoType)
    {
        case _PD_FIX_SUPPLY_PDO:

            if((usVoltage <= 2100) && (usCurrent <= ScalerTypeCRx0PdGetCableMaxCurrent_EXINT0()) && (usRegPower_EXINT <= GET_RX0_MAX_POWER()))
            {
                ucVbusCheck_EXINT = _TRUE;
            }

            break;

        case _PD_3_PROGRAMMABLE_PDO:

            if((usVoltage <= 2100) && (usCurrent <= ScalerTypeCRx0PdGetCableMaxCurrent_EXINT0()))
            {
                ucVbusCheck_EXINT = _TRUE;
            }

            break;

        default:

            break;
    }

    return ucVbusCheck_EXINT;
}

//--------------------------------------------------
// Description  : Check Vbus Capability is legal
// Input Value  : None
// Output Value : PD SRC Cap Sent Status
//--------------------------------------------------
BYTE ScalerTypeCPowerCheckVbusCapability_WDINT(EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent) using 3
{
    // Calculate Requested Power to Unit = 0.1 W
    WORD usRegPower_WDINT = ((DWORD)usVoltage * usCurrent / 1000);
    BYTE ucVbusCheck_WDINT = _FALSE;

    switch(enumPdoType)
    {
        case _PD_FIX_SUPPLY_PDO:

            if((usVoltage <= 2100) && (usCurrent <= ScalerTypeCRx0PdGetCableMaxCurrent_WDINT()) && (usRegPower_WDINT <= GET_RX0_MAX_POWER()))
            {
                ucVbusCheck_WDINT = _TRUE;
            }

            break;

        case _PD_3_PROGRAMMABLE_PDO:

            if((usVoltage <= 2100) && (usCurrent <= ScalerTypeCRx0PdGetCableMaxCurrent_WDINT()))
            {
                ucVbusCheck_WDINT = _TRUE;
            }

            break;

        default:

            break;
    }

    return ucVbusCheck_WDINT;
}

#endif // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

//--------------------------------------------------
// Description  : Get ADC Channel Output Value (Not IRQ)
// Input Value  : enumChannel : 0/1 (_TYPE_C_UFP_VMON/IMON) / 2 (_TYPE_C_LOC_PW) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : None
//--------------------------------------------------
WORD ScalerTypeCPowerGetAdcOutput(EnumTypeCAdcChannel enumChannel)
{
    DWORD ulResult = 0;

    // [0x7F02] [4:0] Write Valid Output Bit to Get New Value From ADC
    ScalerSetBit(P7F_02_10B_ADC_OUTPUT, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));

    // Polling Valid Output Bit (will be 1 when the New Output is Put into Register [0x7F10-19])
    if(ScalerTimerPollingFlagProc(_ADC_OUTPUT_MAX_TIME, P7F_02_10B_ADC_OUTPUT, (_BIT0 << enumChannel), (_BIT0 << enumChannel)) == _TRUE)
    {
        pData[0] = (ScalerGetByte(P7F_10_10B_ADC_A0_RSLT_H + (enumChannel * 2)));
        pData[1] = (ScalerGetByte(P7F_11_10B_ADC_A0_RSLT_L + (enumChannel * 2))) & (_BIT1 | _BIT0);

        // usResult [9:0] = {RSLT_H[7:0] | RSLT[1:0]}
        ulResult = ((pData[0] << 2) | (pData[1]));
    }
    return (WORD)ulResult;
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Control
// Input Value  : enumChannel : 0/1 (_TYPE_C_UFP_VMON/IMON) / 2 (_TYPE_C_LOC_PW) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRangeIntControl(EnumTypeCAdcChannel enumChannel, bit bAction)
{
    if(bAction == _ENABLE)
    {
        // [0x7F1B] Clear Channel Range Detection IRQ
        ScalerSetBit(P7F_1A_10B_ADC_COMP_INT, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0 << enumChannel));

        // [0x7F1B] Disable Channel INT
        ScalerSetBit(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }
    else
    {
        // [0x7F1B] Disable Channel INT
        ScalerSetBit(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), 0x00);
    }
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : enumChannel : 0/1 (_TYPE_C_UFP_VMON/IMON) / 2 (_TYPE_C_LOC_PW) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                usHigh / usLow : High/Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRangeIntSetting(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange)
{
    // [0x7F1C] Set INT Triggered Condition (INT Triggered when IN/OUT of Range)
    if(bRange == _TYPE_C_ADC_WITHIN_RANGE)
    {
        ScalerSetBit(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), 0x00);
    }
    else
    {
        ScalerSetBit(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }

    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh & (0x03FF);
    usLow = usLow & (0x03FF);

    // [0x7F20-29] Set High Threshold
    // [0x7F20] adc_a0_hi_thr[9:2] = ucHigh[9:2]
    // [0x7F21] adc_a0_hi_thr[1:0] = ucHigh[1:0]
    ScalerSetByte((P7F_20_10B_ADC_A0_HIGH_THR1 + (enumChannel * 2)), (BYTE)(usHigh >> 2));
    ScalerSetBit((P7F_21_10B_ADC_A0_HIGH_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usHigh & (_BIT1 | _BIT0)));

    // [0x7F30-39] Set Low Threshold
    // [0x7F30] adc_a0_low_thr[9:2] = ucLow[9:2]
    // [0x7F31] adc_a0_low_thr[1:0] = ucLow[1:0]
    ScalerSetByte((P7F_30_10B_ADC_A0_LOW_THR1 + (enumChannel * 2)), (BYTE)(usLow >> 2));
    ScalerSetBit((P7F_31_10B_ADC_A0_LOW_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usLow & (_BIT1 | _BIT0)));
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator On/Off IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_A0_UFP_VBUS) / 1 (_TYPE_C_A2_LOC_PW) / 2 (_TYPE_C_A4_DFP_VBUS)
//                bType : _ON (Vbus On Detection) / _OFF (Vbus Off Detection)
//                bAction : IRQ _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerVbusCompIntControl(EnumAdcVbusCompChannel enumChannel, bit bType, bit bAction)
{
    if(bAction == _ENABLE)
    {
        if(bType == _ON)
        {
            ScalerSetBit(P7F_3A_10B_ADC_VBUS_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT0 << enumChannel));
            ScalerSetBit(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
        }
        else
        {
            ScalerSetBit(P7F_3A_10B_ADC_VBUS_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 << enumChannel));
            ScalerSetBit(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));
        }
    }
    else
    {
        if(bType == _ON)
        {
            ScalerSetBit(P7F_3A_10B_ADC_VBUS_INT, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
            ScalerSetBit(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), 0x00);
        }
        else
        {
            ScalerSetBit(P7F_3A_10B_ADC_VBUS_INT, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
            ScalerSetBit(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator On/Off IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_A0_UFP_VBUS) / 1 (_TYPE_C_A2_LOC_PW) / 2 (_TYPE_C_A4_DFP_VBUS)
//                bType : _ON (Vbus On Detection) / _OFF (Vbus Off Detection)
//                bAction : IRQ _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
/*
void ScalerTypeCPowerVbusCompIntControl_EXINT0(EnumAdcVbusCompChannel enumChannel, bit bType, bit bAction) using 1
{
    if(bAction == _ENABLE)
    {
        if(bType == _ON)
        {
            ScalerSetBit_EXINT(P7F_3A_10B_ADC_VBUS_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT0 << enumChannel));
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
        }
        else
        {
            ScalerSetBit_EXINT(P7F_3A_10B_ADC_VBUS_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 << enumChannel));
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));
        }
    }
    else
    {
        if(bType == _ON)
        {
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), 0x00);
        }
        else
        {
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), 0x00);
        }
    }
}
*/

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Debounce Setting
// Input Value  : enumChannel : 0 (_TYPE_C_A0_UFP_VBUS) / 1 (_TYPE_C_A2_LOC_PW) / 2 (_TYPE_C_A4_DFP_VBUS)
//                bType : _ON (Vbus_On_Debounce) / _OFF (Vbus_Off_Debounce)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerVbusCompDebounce(EnumAdcVbusCompChannel enumChannel, bit bType, BYTE ucDebCycle)
{
    if(bType == _ON)
    {
        // [0x7F3C + ucChannel] adc_a0/a2/a4_vbus_on_deb = ucDbCycle
        ScalerSetByte((P7F_3C_10B_ADC_A0_VBUS_ON_DEB + enumChannel), ucDebCycle);
    }
    else
    {
        // [0x7F3C + ucChannel] adc_a0/a2/a4_vbus_on_deb = ucDbCycle
        ScalerSetByte((P7F_3F_10B_ADC_A0_VBUS_OFF_DEB + enumChannel), ucDebCycle);
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Thresholed Setting
// Input Value  : enumChannel : 0 (_TYPE_C_A0_UFP_VBUS) / 1 (_TYPE_C_A2_LOC_PW) / 2 (_TYPE_C_A4_DFP_VBUS)
//                bType : _ON (Vbus On Comparator) / _OFF (Vbus Off Comparator)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerVbusCompThrSetting(EnumAdcVbusCompChannel enumChannel, bit bType, WORD usThreshold)
{
    // Clip Threshole to Valid Value (Not More than 10-bit)
    usThreshold = usThreshold & (0x03FF);

    if(bType == _ON)
    {
        // [0x7F42-43 + ucChannel*2] A0/A2/A4 Vbus On Comparator Threshold
        // [0x7F42] = adc_a0_vbus_on_thr[9:2] = usThreshold[9:2]
        // [0x7F43] = adc_a0_vbus_on_thr[1:0] = usThreshold[1:0]
        ScalerSetByte(P7F_42_10B_ADC_A0_VBUS_ON_THR1 + (enumChannel * 2), (BYTE)(usThreshold >> 2));
        ScalerSetBit(P7F_43_10B_ADC_A0_VBUS_ON_THR2 + (enumChannel * 2), ~(_BIT1 | _BIT0), (BYTE)(usThreshold & (_BIT1 | _BIT0)));
    }
    else
    {
        // [0x7F48-49 + ucChannel*2] A0/A2/A4 Vbus Off Comparator Threshold
        // [0x7F48] = adc_a0_vbus_off_thr[9:2] = ucValue[9:2]
        // [0x7F49] = adc_a0_vbus_off_thr[1:0] = ucValue[1:0]
        ScalerSetByte(P7F_48_10B_ADC_A0_VBUS_OFF_THR1 + (enumChannel * 2), (BYTE)(usThreshold >> 2));
        ScalerSetBit(P7F_49_10B_ADC_A0_VBUS_OFF_THR2 + (enumChannel * 2), ~(_BIT1 | _BIT0), (BYTE)(usThreshold & (_BIT1 | _BIT0)));
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Thresholed Setting
// Input Value  : enumChannel : 0 (_TYPE_C_A0_UFP_VBUS) / 1 (_TYPE_C_A2_LOC_PW) / 2 (_TYPE_C_A4_DFP_VBUS)
//                bType : _ON (Vbus On Comparator) / _OFF (Vbus Off Comparator)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerVbusCompThrSetting_EXINT0(EnumAdcVbusCompChannel enumChannel, bit bType, WORD usThreshold) using 1
{
    // Clip Threshole to Valid Value (Not More than 10-bit)
    usThreshold = usThreshold & (0x03FF);

    if(bType == _ON)
    {
        // [0x7F42-43 + ucChannel*2] A0/A2/A4 Vbus On Comparator Threshold
        // [0x7F42] = adc_a0_vbus_on_thr[9:2] = usThreshold[9:2]
        // [0x7F43] = adc_a0_vbus_on_thr[1:0] = usThreshold[1:0]
        ScalerSetByte_EXINT(P7F_42_10B_ADC_A0_VBUS_ON_THR1 + (enumChannel * 2), (BYTE)(usThreshold >> 2));
        ScalerSetBit_EXINT(P7F_43_10B_ADC_A0_VBUS_ON_THR2 + (enumChannel * 2), ~(_BIT1 | _BIT0), (BYTE)(usThreshold & (_BIT1 | _BIT0)));
    }
    else
    {
        // [0x7F48-49 + ucChannel*2] A0/A2/A4 Vbus Off Comparator Threshold
        // [0x7F48] = adc_a0_vbus_off_thr[9:2] = ucValue[9:2]
        // [0x7F49] = adc_a0_vbus_off_thr[1:0] = ucValue[1:0]
        ScalerSetByte_EXINT(P7F_48_10B_ADC_A0_VBUS_OFF_THR1 + (enumChannel * 2), (BYTE)(usThreshold >> 2));
        ScalerSetBit_EXINT(P7F_49_10B_ADC_A0_VBUS_OFF_THR2 + (enumChannel * 2), ~(_BIT1 | _BIT0), (BYTE)(usThreshold & (_BIT1 | _BIT0)));
    }
}

#if((_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC))
//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Control
// Input Value  : enumChannel : 0/1 (_TYPE_C_UFP_VMON/IMON) / 2 (_TYPE_C_LOC_PW) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRangeIntControl_EXINT0(EnumTypeCAdcChannel enumChannel, bit bAction) using 1
{
    if(bAction == _ENABLE)
    {
        // [0x7F1B] Clear Channel Range Detection IRQ
        ScalerSetBit_EXINT(P7F_1A_10B_ADC_COMP_INT, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0 << enumChannel));

        // [0x7F1B] Disable Channel INT
        ScalerSetBit_EXINT(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }
    else
    {
        // [0x7F1B] Disable Channel INT
        ScalerSetBit_EXINT(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), 0x00);
    }
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Control
// Input Value  : enumChannel : 0/1 (_TYPE_C_UFP_VMON/IMON) / 2 (_TYPE_C_LOC_PW) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRangeIntControl_WDINT(EnumTypeCAdcChannel enumChannel, bit bAction) using 3
{
    if(bAction == _ENABLE)
    {
        // [0x7F1B] Clear Channel Range Detection IRQ
        ScalerSetBit_EXINT(P7F_1A_10B_ADC_COMP_INT, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0 << enumChannel));

        // [0x7F1B] Disable Channel INT
        ScalerSetBit_EXINT(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }
    else
    {
        // [0x7F1B] Disable Channel INT
        ScalerSetBit_EXINT(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), 0x00);
    }
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : enumChannel : 0/1 (_TYPE_C_UFP_VMON/IMON) / 2 (_TYPE_C_LOC_PW) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                usHigh / usLow : High/Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRangeIntSetting_EXINT0(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange) using 1
{
    // [0x7F1C] Set INT Triggered Condition (INT Triggered when IN/OUT of Range)
    if(bRange == _TYPE_C_ADC_WITHIN_RANGE)
    {
        ScalerSetBit_EXINT(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), 0x00);
    }
    else
    {
        ScalerSetBit_EXINT(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }

    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh & (0x03FF);
    usLow = usLow & (0x03FF);

    // [0x7F20-29] Set High Threshold
    // [0x7F20] adc_a0_hi_thr[9:2] = ucHigh[9:2]
    // [0x7F21] adc_a0_hi_thr[1:0] = ucHigh[1:0]
    ScalerSetByte_EXINT((P7F_20_10B_ADC_A0_HIGH_THR1 + (enumChannel * 2)), (BYTE)(usHigh >> 2));
    ScalerSetBit_EXINT((P7F_21_10B_ADC_A0_HIGH_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usHigh & (_BIT1 | _BIT0)));

    // [0x7F30-39] Set Low Threshold
    // [0x7F30] adc_a0_low_thr[9:2] = ucLow[9:2]
    // [0x7F31] adc_a0_low_thr[1:0] = ucLow[1:0]
    ScalerSetByte_EXINT((P7F_30_10B_ADC_A0_LOW_THR1 + (enumChannel * 2)), (BYTE)(usLow >> 2));
    ScalerSetBit_EXINT((P7F_31_10B_ADC_A0_LOW_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usLow & (_BIT1 | _BIT0)));
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : enumChannel : 0/1 (_TYPE_C_UFP_VMON/IMON) / 2 (_TYPE_C_LOC_PW) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                usHigh / usLow : High/Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerRangeIntSetting_WDINT(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange) using 3
{
    // [0x7F1C] Set INT Triggered Condition (INT Triggered when IN/OUT of Range)
    if(bRange == _TYPE_C_ADC_WITHIN_RANGE)
    {
        ScalerSetBit_EXINT(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), 0x00);
    }
    else
    {
        ScalerSetBit_EXINT(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }

    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh & (0x03FF);
    usLow = usLow & (0x03FF);

    // [0x7F20-29] Set High Threshold
    // [0x7F20] adc_a0_hi_thr[9:2] = ucHigh[9:2]
    // [0x7F21] adc_a0_hi_thr[1:0] = ucHigh[1:0]
    ScalerSetByte_EXINT((P7F_20_10B_ADC_A0_HIGH_THR1 + (enumChannel * 2)), (BYTE)(usHigh >> 2));
    ScalerSetBit_EXINT((P7F_21_10B_ADC_A0_HIGH_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usHigh & (_BIT1 | _BIT0)));

    // [0x7F30-39] Set Low Threshold
    // [0x7F30] adc_a0_low_thr[9:2] = ucLow[9:2]
    // [0x7F31] adc_a0_low_thr[1:0] = ucLow[1:0]
    ScalerSetByte_EXINT((P7F_30_10B_ADC_A0_LOW_THR1 + (enumChannel * 2)), (BYTE)(usLow >> 2));
    ScalerSetBit_EXINT((P7F_31_10B_ADC_A0_LOW_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usLow & (_BIT1 | _BIT0)));
}
#endif // End of #if((_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC))

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
//--------------------------------------------------
// Description  : Clear ADC INT Flag
// Input Value  : enumChannel : 0/1 (_TYPE_C_UFP_VMON/IMON) / 2 (_TYPE_C_LOC_PW) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerClearAdcIntFlag_EXINT0(EnumTypeCAdcChannel enumChannel) using 1
{
    ScalerSetBit_EXINT(P7F_1A_10B_ADC_COMP_INT, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0 << enumChannel));
}

//--------------------------------------------------
// Description  : ADC INT Check
// Input Value  : enumChannel : 0/1 (_TYPE_C_UFP_VMON/IMON) / 2 (_TYPE_C_LOC_PW) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCPowerAdcIntCheck_EXINT0(EnumTypeCAdcChannel enumChannel) using 1
{
    return ((ScalerGetBit_EXINT(P7F_1A_10B_ADC_COMP_INT, (_BIT0 << enumChannel)) == (_BIT0 << enumChannel)) && (ScalerGetBit_EXINT(P7F_1B_10B_ADC_COMP_INT_EN, (_BIT0 << enumChannel)) == (_BIT0 << enumChannel)));
}

#if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
//--------------------------------------------------
// Description  : Get ADC Channel Output Value (Not IRQ)
// Input Value  : enumChannel : 0/1 (_TYPE_C_UFP_VMON/IMON) / 2 (_TYPE_C_LOC_PW) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : None
//--------------------------------------------------
WORD ScalerTypeCPowerGetAdcOutput_EXINT0(EnumTypeCAdcChannel enumChannel) using 1
{
    DWORD ulResult = 0;

    // [0x7F02] [4:0] Write Valid Output Bit to Get New Value From ADC
    ScalerSetBit_EXINT(P7F_02_10B_ADC_OUTPUT, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));

    // Polling Valid Output Bit (will be 1 when the New Output is Put into Register [0x7F10-19])
    if(ScalerTimerPollingFlagProc_EXINT0(_ADC_OUTPUT_MAX_TIME, P7F_02_10B_ADC_OUTPUT, (_BIT0 << enumChannel), (_BIT0 << enumChannel)) == _TRUE)
    {
        pData_EXINT[0] = (ScalerGetByte_EXINT(P7F_10_10B_ADC_A0_RSLT_H + (enumChannel * 2)));
        pData_EXINT[1] = (ScalerGetByte_EXINT(P7F_11_10B_ADC_A0_RSLT_L + (enumChannel * 2))) & (_BIT1 | _BIT0);

        // usResult [9:0] = {RSLT_H[7:0] | RSLT[1:0]}
        ulResult = ((pData_EXINT[0] << 2) | (pData_EXINT[1]));
    }
    return (WORD)ulResult;
}
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))

