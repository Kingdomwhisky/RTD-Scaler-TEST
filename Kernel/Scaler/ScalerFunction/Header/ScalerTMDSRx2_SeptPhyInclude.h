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
// ID Code      : ScalerTMDSRx2_SeptPhyInclude.h No.0000
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
#if(_D2_TMDS_SUPPORT == _ON)
extern void ScalerTMDSRx2DviVideoSetting(void);
extern void ScalerTMDSRx2FirstActiveProc(BYTE ucSourceType);
extern void ScalerTMDSRx2PowerOffProc(void);
extern BYTE ScalerTMDSRx2TMDSVideoDetect(bit bWait);
extern void ScalerTMDSRx2TMDSVideoDetectEvent(void);
extern void ScalerTMDSRx2PSIntHandler_EXINT0(void);

#if(_D2_HDMI_SUPPORT == _ON)
extern bit ScalerTMDSRx2HdmiAviPixelRepInfoChanged(void);
extern BYTE ScalerTMDSRx2HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern BYTE ScalerTMDSRx2HdmiGetColorDepth(void);
extern void ScalerTMDSRx2HdmiPacketDetectEvent(void);

#if(_D2_HDMI_2_0_SUPPORT == _ON)
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
extern void ScalerTMDSRx2HDMI2HPDRRIRQEnable(bit bEnable);
#endif
extern void ScalerTMDSRx2Hdmi2FormatResetEvent(void);
extern void ScalerTMDSRx2ReadRequestProc_EXINT0(BYTE ucRROutCome);
extern void ScalerTMDSRx2ReadRequestTimerEventEnable_WDINT(bit bEnable);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
extern bit ScalerTMDSRx2HdmiDeepColorProc(WORD usTmdsClkCnt);
#endif

#endif

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
extern bit ScalerTMDSRx2TMDSNormalPreDetect(void);
extern bit ScalerTMDSRx2TMDSPSPreDetect(void);
#endif

#endif

extern void ScalerTMDSRx2HotPlugLowProc(void);
extern void ScalerTMDSRx2HotPlugHighProc(WORD usHpdTime);
#endif
