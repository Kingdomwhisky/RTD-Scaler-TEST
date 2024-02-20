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
// ID Code      : ScalerTMDSRx1_SeptPhyInclude.h No.0000
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
#if(_D1_TMDS_SUPPORT == _ON)
extern void ScalerTMDSRx1FirstActiveProc(BYTE ucSourceType);
extern void ScalerTMDSRx1PowerOffProc(void);
extern void ScalerTMDSRx1TMDSVideoDetectEvent(void);

#if(_D1_HDMI_SUPPORT == _ON)
extern bit ScalerTMDSRx1HdmiAviPixelRepInfoChanged(void);
extern bit ScalerTMDSRx1HdmiDeepColorProc(WORD usTmdsClkCnt);
extern void ScalerTMDSRx1HdmiPacketDetectEvent(void);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
extern void ScalerTMDSRx1Hdmi2FormatResetEvent(void);
#endif

#endif

extern void ScalerTMDSRx1HotPlugLowProc(void);
extern void ScalerTMDSRx1HotPlugHighProc(WORD usHpdTime);
#endif
