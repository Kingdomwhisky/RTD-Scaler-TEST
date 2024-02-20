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
// ID Code      : ScalerDPRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucDpRx0Tp1PermitSwingLevel0;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_D0_DP_EXIST == _ON)
extern void ScalerDpRx0ErrorCounterUpdate_EXINT0(void);
extern void ScalerDpRx0ErrorCounterDisable_EXINT0(void);
extern void ScalerDpRx0ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern void ScalerDpRx0AVMute(void);
extern void ScalerDpRx0ScrambleSetting(void);

#if((_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON) && (_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON))
extern bit ScalerDpRx0LaneValidCheck(void);
#endif

extern void ScalerDpRx0CheckHdcpCpirqStatus(void);
extern void ScalerDpRx0CrcCalculate(void);

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
extern void ScalerDpRx0CalculateLinkRate(EnumDpLaneCount enumDpLaneCount);
#endif

#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
extern void ScalerDpRx0HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
#endif
extern BYTE ScalerDpRx0GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern BYTE ScalerDpRx0GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern bit ScalerDpRx0GetVideoStream(void);
extern bit ScalerDpRx0MSAActiveChange(void);
extern void ScalerDpRx0SecDataBlockReset(void);
extern void ScalerDpRx0SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpRx0SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpRx0SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpRx0ChangeHdcpDpcdCapability(bit bEn);

#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)
extern void ScalerDpRx0ASSRModeSetting(void);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDpRx0GetFREESYNCStatusChange(void);
extern void ScalerDpRx0SetFREESYNCMsaForLut(WORD usDpHtotal);
#endif

#endif
