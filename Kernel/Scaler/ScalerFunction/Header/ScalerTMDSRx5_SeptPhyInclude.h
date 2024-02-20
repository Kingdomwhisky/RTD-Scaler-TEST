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
// ID Code      : ScalerTMDSRx5_SeptPhyInclude.h No.0000
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
#if(_D5_TMDS_SUPPORT == _ON)
extern void ScalerTMDSRx5DviVideoSetting(void);
extern void ScalerTMDSRx5FirstActiveProc(BYTE ucSourceType);
extern void ScalerTMDSRx5PowerOffProc(void);
extern void ScalerTMDSRx5SetPorchColor(EnumColorSpace enumColorFormat);
extern BYTE ScalerTMDSRx5TMDSVideoDetect(bit bWait);
extern void ScalerTMDSRx5TMDSVideoDetectEvent(void);

#if(_D5_HDMI_SUPPORT == _ON)
extern bit ScalerTMDSRx5HdmiAviPixelRepInfoChanged(void);
extern bit ScalerTMDSRx5HdmiDeepColorProc(WORD usTmdsClkCnt);
extern BYTE ScalerTMDSRx5HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern BYTE ScalerTMDSRx5HdmiGetColorDepth(void);
extern void ScalerTMDSRx5HdmiPacketDetect(bit bWait);
extern void ScalerTMDSRx5HdmiPacketDetectEvent(void);
extern void ScalerTMDSRx5HdmiWatchDog(BYTE ucWDType, bit bEnable);
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
extern bit ScalerTMDSRx5TMDSNormalPreDetect(void);
extern bit ScalerTMDSRx5TMDSPSPreDetect(void);
#endif

extern void ScalerTMDSRx5HotPlugLowProc(void);
extern void ScalerTMDSRx5HotPlugHighProc(WORD usHpdTime);
#endif
