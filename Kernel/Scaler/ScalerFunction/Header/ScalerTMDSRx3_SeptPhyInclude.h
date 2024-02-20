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
// ID Code      : ScalerTMDSRx3_SeptPhyInclude.h No.0000
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
#if(_D3_TMDS_SUPPORT == _ON)
extern void ScalerTMDSRx3DviVideoSetting(void);
extern void ScalerTMDSRx3FirstActiveProc(BYTE ucSourceType);
extern void ScalerTMDSRx3PowerOffProc(void);
extern BYTE ScalerTMDSRx3TMDSVideoDetect(bit bWait);
extern void ScalerTMDSRx3TMDSVideoDetectEvent(void);
extern void ScalerTMDSRx3PSIntHandler_EXINT0(void);

#if(_D3_HDMI_SUPPORT == _ON)
extern bit ScalerTMDSRx3HdmiAviPixelRepInfoChanged(void);
extern BYTE ScalerTMDSRx3HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern BYTE ScalerTMDSRx3HdmiGetColorDepth(void);
extern void ScalerTMDSRx3HdmiPacketDetectEvent(void);

#if(_D3_HDMI_2_0_SUPPORT == _ON)
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
extern void ScalerTMDSRx3HDMI2HPDRRIRQEnable(bit bEnable);
#endif
extern void ScalerTMDSRx3Hdmi2FormatResetEvent(void);
extern void ScalerTMDSRx3ReadRequestProc_EXINT0(BYTE ucRROutCome);
extern void ScalerTMDSRx3ReadRequestTimerEventEnable_WDINT(bit bEnable);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
extern bit ScalerTMDSRx3HdmiDeepColorProc(WORD usTmdsClkCnt);
#endif

#endif

#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
extern bit ScalerTMDSRx3TMDSNormalPreDetect(void);
extern bit ScalerTMDSRx3TMDSPSPreDetect(void);
#endif

#endif

extern void ScalerTMDSRx3HotPlugLowProc(void);
extern void ScalerTMDSRx3HotPlugHighProc(WORD usHpdTime);
#endif
