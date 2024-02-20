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
// ID Code      : ScalerTMDSRx4_SeptPhyInclude.h No.0000
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
#if(_D4_TMDS_SUPPORT == _ON)
extern void ScalerTMDSRx4DviVideoSetting(void);
extern void ScalerTMDSRx4FirstActiveProc(BYTE ucSourceType);
extern void ScalerTMDSRx4PowerOffProc(void);
extern void ScalerTMDSRx4SetPorchColor(EnumColorSpace enumColorFormat);
extern BYTE ScalerTMDSRx4TMDSVideoDetect(bit bWait);
extern void ScalerTMDSRx4TMDSVideoDetectEvent(void);

#if(_D4_HDMI_SUPPORT == _ON)
extern bit ScalerTMDSRx4HdmiAviPixelRepInfoChanged(void);
extern BYTE ScalerTMDSRx4HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern BYTE ScalerTMDSRx4HdmiGetColorDepth(void);
extern void ScalerTMDSRx4HdmiPacketDetect(bit bWait);
extern void ScalerTMDSRx4HdmiPacketDetectEvent(void);
extern void ScalerTMDSRx4HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
extern bit ScalerTMDSRx4HdmiDeepColorProc(WORD usTmdsClkCnt);
#endif

#endif

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
extern bit ScalerTMDSRx4TMDSNormalPreDetect(void);
extern bit ScalerTMDSRx4TMDSPSPreDetect(void);
#endif

#endif

extern void ScalerTMDSRx4HotPlugLowProc(void);
extern void ScalerTMDSRx4HotPlugHighProc(WORD usHpdTime);
#endif
