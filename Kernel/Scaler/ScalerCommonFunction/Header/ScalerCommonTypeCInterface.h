/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonTypeCInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#define GET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT()      (g_bTypeC5400LenovoAltModeUrgentEvent)
#define SET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT()      (g_bTypeC5400LenovoAltModeUrgentEvent = _TRUE)
#define CLR_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT()      (g_bTypeC5400LenovoAltModeUrgentEvent = _FALSE)
#endif
#endif

//****************************************************************************
// INTERFACE STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
extern bit g_bTypeC5400LenovoAltModeUrgentEvent;
#endif
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
extern void ScalerTypeCHandler(BYTE ucInputPort, BYTE ucModeState);
extern EnumTypeCAttachStatus ScalerTypeCGetCcAttach(BYTE ucInputPort);
#if(_USB3_RETIMER_SUPPORT == _ON)
extern EnumTypeCAttachStatus ScalerTypeCSearchCcAttach(void);
#endif
extern EnumTypeCAltModeStatus ScalerTypeCGetAltModeReady(BYTE ucInputPort);
extern EnumTypeCOrientation ScalerTypeCGetOrientation(BYTE ucInputPort);
extern bit ScalerTypeCGetPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment);
extern EnumTypeCPowerRole ScalerTypeCGetPowerRole(BYTE ucInputPort);
extern bit ScalerTypeCReconnect(BYTE ucInputPort);
extern bit ScalerTypeCUpdateConfig(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap);
extern void ScalerTypeCIntHandler_EXINT0(void);
extern void ScalerTypeCPowerSwitch(EnumPowerAction enumPowerAction);
extern void ScalerTypeCSetPdoByKernel(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeCSetMaxPower(BYTE ucInputPort, WORD usMaxPower);
extern void ScalerTypeCSetPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
extern BYTE ScalerTypeCGetPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
#endif
extern BYTE ScalerTypeCGetPartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
extern EnumPdoCheck ScalerTypeCCheckPdoCountChange(BYTE ucInputPort, BYTE ucPdoCount);
extern EnumPdoCheck ScalerTypeCCheckPdoChange(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo);
extern void ScalerTypeCSetFixPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucVoltage, BYTE ucMaxCur);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
extern void ScalerTypeCSetPpsPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucMinVol, BYTE ucMaxVol, BYTE ucMaxCur);
#endif
extern void ScalerTypeCSetRdo(BYTE ucInputPort, StructTypeCUserRDO stTypeCUserRdo);
extern StructTypeCUserPDO ScalerTypeCGetPartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
extern void ScalerTypeCSetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo stTypeCUserProtectInfo);
#endif
extern bit ScalerTypeCGetPdoStatus(BYTE ucInputPort, BYTE *pucVoltage, BYTE *pucCurrent);
extern void ScalerTypeCSetPdSystemEvent(BYTE ucInputPort, EnumPDSysEvent enumPdSysEvent);
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern EnumTypeCLenovoAltModeStatus ScalerTypeCGetLenovoAltModeReady(BYTE ucInputPort);
extern EnumTypeCLenovoDeviceType ScalerTypeCGetLenovoDeviceType(BYTE ucInputPort);
extern StructTypeCLenovoSysEvent ScalerTypeCGetLenovoSystemEvent(BYTE ucInputPort);
extern void ScalerTypeCSetLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
extern bit ScalerTypeCCheckLenovoDockingEventBusy(BYTE ucInputPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern EnumTypeCAcerAltModeStatus ScalerTypeCGetAcerAltModeReady(BYTE ucInputPort);
extern StructTypeCAcerSysEvent ScalerTypeCGetAcerSystemEvent(BYTE ucInputPort);
extern void ScalerTypeCSetAcerUserEvent(BYTE ucInputPort, StructTypeCAcerUserEvent stAcerUserEvent);
extern EnumTypeCAcerBusyStatus ScalerTypeCCheckAcerUserEventBusy(BYTE ucInputPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern EnumTypeCHpAltModeStatus ScalerTypeCGetHpAltModeReady(BYTE ucInputPort);
extern StructTypeCHpSysEvent ScalerTypeCGetHpSystemEvent(BYTE ucInputPort);
extern void ScalerTypeCSetHpUserEvent(BYTE ucInputPort, StructTypeCHpUserEvent stHpUserEvent);
extern EnumTypeCHpBusyStatus ScalerTypeCCheckHpUserEventBusy(BYTE ucInputPort);
#endif
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

