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
// ID Code      : ScalerDP_SeptPhyInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
extern void ScalerDpEdidSwitch(BYTE ucInputPort);

extern EnumDpPowerState ScalerDpGetPowerStatus(BYTE ucInputPort);
extern EnumDpLaneCount ScalerDpGetLaneCount(BYTE ucInputPort);
extern EnumDpLinkRate ScalerDpGetLinkRate(BYTE ucInputPort);
extern EnumDpVoltageSwingLevel ScalerDpGetLaneVoltageSwingLv(BYTE ucInputPort, EnumDpLane enumDpLane);
extern EnumDpPreEmphasisLevel ScalerDpGetLanePreEmpLv(BYTE ucInputPort, EnumDpLane enumDpLane);
extern bit ScalerDpGetSrcMstEnable(BYTE ucInputPort);
extern void ScalerDpSetHotPlugEvent(BYTE ucInputPort, EnumDpHotPlugAssertType enumHpdType);
extern void ScalerDpHotPlugHandler(void);
extern void ScalerDpJudgeHPDToggle(EnumPowerAction enumPowerAction);
extern void ScalerDpInitial(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
extern void ScalerDpLaneCountSwitch(BYTE ucInputPort, EnumDpLaneCount enumDpLaneCount);
extern void ScalerDpVersionSwitch(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
extern void ScalerDpHDCPUnplugReset(BYTE ucInputPort);
extern void ScalerDpMainLinkQualityManagement(BYTE ucInputPort);
extern StructDpRxErrorCount ScalerDpRxGetErrorCount(BYTE ucInputPort);

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
extern void ScalerDpRestoreFakeLTLaneCount(EnumSourceSearchPort enumSourceSearchPort);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMstFakeOffDoneProc(void);
extern void ScalerDpMstReset(EnumDPMSTPort enumRxMstPort);
#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpHDCPHandler(void);
#endif
#endif
#endif

