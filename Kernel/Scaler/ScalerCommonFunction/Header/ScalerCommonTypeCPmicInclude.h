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
// ID Code      : ScalerCommonTypeCPmicInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON) && (_TYPE_C_PMIC_TYPE != _PMIC_NONE))
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1PmicIICSetStart : 1;
    BYTE b1PmicIICMainLoop : 1;
    BYTE b1PmicIICExint0Loop : 1;
    BYTE b1PmicIICWdintLoop : 1;
    BYTE b1PmicIICExint0EverLoop : 1;
    BYTE b1PmicIICWdintEverLoop : 1;
} StructPmicControl;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
extern void ScalerTypeCPmicHwIICSetFreqDiv(EnumClkSel enumClock);
#endif
extern void ScalerTypeCPmicRx0Initial(void);
extern void ScalerTypeCPmicRx0Reset(void);
extern bit ScalerTypeCPmicRx0Setting(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
extern BYTE ScalerTypeCPmicRx0Setting_EXINT0(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
extern BYTE ScalerTypeCPmicRx0Setting_WDINT(bit bAction, bit bPowerDirection, EnumPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent);
extern bit ScalerTypeCPmicRx0VbusDischarge(bit bEn);
extern BYTE ScalerTypeCPmicRx0VbusDischarge_EXINT0(bit bEn);
extern BYTE ScalerTypeCPmicRx0VbusDischarge_WDINT(bit bEn);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicOperationMode ScalerTypeCPmicRx0ReadPpsOperationModeStatus_EXINT0(void);
#endif
#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
extern bit ScalerTypeCPmicRx0Check(void);
extern bit ScalerTypeCPmicRx0Tracking(void);
extern void ScalerTypeCPmicRx0OcpProtect(void);
#endif

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC)
extern void ScalerTypeCPmicRx0FwOcpIntHandler_EXINT0(void);
#if(_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0)
extern void ScalerTypeCPmicRx0WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID);
#endif
#endif

#if(_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON)
extern void ScalerTypeCPmicRx0OvpUvpIntHandler_EXINT0(void);
#endif
#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON) && (_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON))
