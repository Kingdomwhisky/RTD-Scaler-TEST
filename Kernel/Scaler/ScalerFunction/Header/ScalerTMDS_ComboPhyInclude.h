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
// ID Code      : ScalerTMDS_ComboPhyInclude.h No.0000
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


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_TMDS_PAGE2_COMBO_EXIST == _ON) && (_DVI_SUPPORT == _ON))
extern void ScalerTMDSDviVideoSetting(BYTE ucInputPort);
extern void ScalerTMDSFreqDetectDisable(void);
extern void ScalerTMDSResetProc(void);
extern BYTE ScalerTMDSVideoDetect(bit bWait);
extern void ScalerTMDSVideoDetectEvent(EnumScalerTimerEventID enumEventID);

#if(_HDMI_SUPPORT == _ON)
extern bit ScalerTMDSHdmiAviPixelRepInfoChanged(void);
extern bit ScalerTMDSHdmiDeepColorProc(WORD usTmdsClkCnt);
extern BYTE ScalerTMDSHdmiGetColorDepth(void);
extern void ScalerTMDSHdmiPacketDetect(bit bWait);
extern void ScalerTMDSHdmiPacketDetectEvent(EnumScalerTimerEventID enumEventID);
extern void ScalerTMDSHdmiWatchDog(BYTE ucWDType, bit bEnable);
extern BYTE ScalerTMDSRx0HdmiGetAVIInfo(EnumAviInfoContent enumContent);
#endif

#if(_UNDERSCAN_SUPPORT == _ON)
extern void ScalerTMDSSetPorchColor(BYTE ucInputPort, EnumColorSpace enumColorFormat);
#endif

extern void ScalerTMDSHotPlugLowProc(BYTE ucPortSelect);
extern void ScalerTMDSHotPlugHighProc(BYTE ucPortSelect, WORD usHpdTime);
#endif

