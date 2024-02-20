/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonTypeCPowerInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))

// Temporary Definittions
#define _TYPE_C_EMB_DFP_PORT_SUPPORT    _OFF

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_TYPE_C_LOC_PW_ON_THR()      ((WORD)(g_stTpcRx0PowerInfo.b10Rx0LocPowOn))
#define SET_TYPE_C_LOC_PW_ON_THR(x)     (g_stTpcRx0PowerInfo.b10Rx0LocPowOn = ScalerTypeCPowerRx0CorrectionToRawData(x))
#define GET_TYPE_C_LOC_PW_OFF_THR()     ((WORD)(g_stTpcRx0PowerInfo.b10Rx0LocPowOff))
#define SET_TYPE_C_LOC_PW_OFF_THR(x)    (g_stTpcRx0PowerInfo.b10Rx0LocPowOff = ScalerTypeCPowerRx0CorrectionToRawData(x))

#define GET_TYPE_C_5V_UP_BND()          ((WORD)(g_stTpcRx0PowerInfo.b10Rx05VUpBound))
#define SET_TYPE_C_5V_UP_BND(x)         (g_stTpcRx0PowerInfo.b10Rx05VUpBound = ScalerTypeCPowerRx0CorrectionToRawData(x))
#define GET_TYPE_C_5V_LOW_BND()         ((WORD)(g_stTpcRx0PowerInfo.b10Rx05VLowBound))
#define SET_TYPE_C_5V_LOW_BND(x)        (g_stTpcRx0PowerInfo.b10Rx05VLowBound = ScalerTypeCPowerRx0CorrectionToRawData(x))

#define GET_TYPE_C_0V_UP_BND()          ((WORD)(g_stTpcRx0PowerInfo.b10Rx00VUpBound))
#define SET_TYPE_C_0V_UP_BND(x)         (g_stTpcRx0PowerInfo.b10Rx00VUpBound = ScalerTypeCPowerRx0CorrectionToRawData(x))

#define GET_TYPE_C_AVALIABLE_PWR()      ((WORD)(g_stTpcRx0PowerInfo.b10AvaliablePower))
#define SET_TYPE_C_AVALIABLE_PWR(x)     (g_stTpcRx0PowerInfo.b10AvaliablePower = (x))

#if(_USB3_RETIMER_SUPPORT == _ON)
#define GET_USB3_VBUS_ON_THR()          ((WORD)(g_stU3VbusOnOffThr.b10Rx0Usb3VbusOnThr))
#define SET_USB3_VBUS_ON_THR(x)         (g_stU3VbusOnOffThr.b10Rx0Usb3VbusOnThr = ScalerTypeCPowerRx0CorrectionToRawData(x))

#define GET_USB3_VBUS_OFF_THR()         ((WORD)(g_stU3VbusOnOffThr.b10Rx0Usb3VbusOffThr))
#define SET_USB3_VBUS_OFF_THR(x)        (g_stU3VbusOnOffThr.b10Rx0Usb3VbusOffThr = ScalerTypeCPowerRx0CorrectionToRawData(x))
#endif

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
#define GET_RX0_MAX_POWER()             ((WORD)(g_stTpcRx0PowerInfo.b10Rx0MaxPower))
#define SET_RX0_MAX_POWER(x)            (g_stTpcRx0PowerInfo.b10Rx0MaxPower = (x))

#define GET_RX0_VBUS_STATUS()           ((bit)(g_stTpcRx0PowerInfo.b1VbusStatus))
#define SET_RX0_VBUS_STATUS(x)          (g_stTpcRx0PowerInfo.b1VbusStatus = (x))

#define GET_RX0_REQ_PWR()               ((WORD)(g_stTpcRx0PowerInfo.b10Rx0ReqPower))
#define SET_RX0_REQ_PWR(x)              (g_stTpcRx0PowerInfo.b10Rx0ReqPower = (x))

#define GET_RX0_OUTPUT_VOL()            ((WORD)(g_stTpcRx0PowerInfo.b12Rx0OutputVol))
#define SET_RX0_OUTPUT_VOL(x)           (g_stTpcRx0PowerInfo.b12Rx0OutputVol = (x))

#define GET_RX0_OUTPUT_CUR()            ((WORD)(g_stTpcRx0PowerInfo.b10Rx0OutputCur))
#define SET_RX0_OUTPUT_CUR(x)           (g_stTpcRx0PowerInfo.b10Rx0OutputCur = (x))

#endif // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
// Type-C ADC Digital Comparator Channels
typedef enum
{
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    _TYPE_C_A0_UFP_VBUS = 0x00,
#endif // End Of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    _TYPE_C_A2_LOC_PW = 0x01,
#if(_TYPE_C_EMB_DFP_PORT_SUPPORT == _ON)
    _TYPE_C_A4_DFP_VBUS = 0x02,
#endif // End of #if(_TYPE_C_EMB_DFP_PORT_SUPPORT == _ON)
}EnumAdcVbusCompChannel;

#if(_USB3_RETIMER_SUPPORT == _ON)
typedef struct
{
    WORD b10Rx0Usb3VbusOnThr : 10;
    WORD b10Rx0Usb3VbusOffThr : 10;
}StructUsb3VbusOnOffThr;
#endif
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTypeCPowerInfo g_stTpcRx0PowerInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern void ScalerTypeCPowerInitial(void);
extern bit ScalerTypeCPowerCheckLocPowExist(bit bCondition);
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
extern WORD ScalerTypeCPowerRx0CorrectionToIdealData(WORD usRawData);
#endif
#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) && (_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0))
extern WORD ScalerTypeCPowerRx0CorrectionToIdealData_EXINT0(WORD usRawData);
#endif
extern void ScalerTypeCPowerRx0UnattachReset(void);
extern void ScalerTypeCPowerRx0UnattachVthAdjust(void);
extern void ScalerTypeCPowerRx0UnattachVthAdjust_EXINT0(WORD usVoltage);
extern bit ScalerTypeCPowerRx0CheckVbusSafe0V(void);
extern bit ScalerTypeCPowerRx0CheckVbusSafe5V(void);
#if(_USB3_RETIMER_SUPPORT == _ON)
extern bit ScalerTypeCPowerRx0CheckVbus(bit bAction);
#endif
// extern bit ScalerTypeCPowerRx0CheckVbusReady(WORD usVoltage);
extern void ScalerTypeCPowerRx0VbusControl(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
extern void ScalerTypeCPowerRx0VbusControl_EXINT0(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
extern void ScalerTypeCPowerRx0VbusControl_WDINT(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
extern void ScalerTypeCPowerIntHandler_EXINT0(void);
extern bit ScalerTypeCPowerCheckVbusCapability(EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
extern BYTE ScalerTypeCPowerCheckVbusCapability_EXINT0(EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
extern BYTE ScalerTypeCPowerCheckVbusCapability_WDINT(EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
#endif // End Of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
extern WORD ScalerTypeCPowerGetAdcOutput(EnumTypeCAdcChannel enumChannel);
extern void ScalerTypeCPowerRangeIntControl(EnumTypeCAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCPowerRangeIntSetting(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
#if((_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC))
extern void ScalerTypeCPowerRangeIntControl_EXINT0(EnumTypeCAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCPowerRangeIntControl_WDINT(EnumTypeCAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCPowerRangeIntSetting_EXINT0(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
extern void ScalerTypeCPowerRangeIntSetting_WDINT(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
#endif // End of #if((_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC))
#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
extern void ScalerTypeCPowerClearAdcIntFlag_EXINT0(EnumTypeCAdcChannel enumChannel);
extern BYTE ScalerTypeCPowerAdcIntCheck_EXINT0(EnumTypeCAdcChannel enumChannel);
#if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
extern WORD ScalerTypeCPowerGetAdcOutput_EXINT0(EnumTypeCAdcChannel enumChannel);
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
