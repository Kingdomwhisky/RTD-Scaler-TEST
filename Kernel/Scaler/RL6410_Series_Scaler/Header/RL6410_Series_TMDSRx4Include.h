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
// ID Code      : RL6410_Series_TMDSRx4Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_D4_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_RX4_PHY_SET()                          (g_stTMDSRx4CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_RX4_PHY_SET()                          (g_stTMDSRx4CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_RX4_PHY_SET()                          (g_stTMDSRx4CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_RX4_RGBHV_DETECTING()                  (g_stTMDSRx4CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_RX4_RGBHV_DETECTING()                  (g_stTMDSRx4CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_RX4_RGBHV_DETECTING()                  (g_stTMDSRx4CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_RX4_PACKET_DETECTING()                 (g_stTMDSRx4CtrlInfo.b1PacketDetecting)
#define SET_HDMI_RX4_PACKET_DETECTING()                 (g_stTMDSRx4CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_RX4_PACKET_DETECTING()                 (g_stTMDSRx4CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx4CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx4CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX4_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx4CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_RX4_GCP_RECEIVED()                     (g_stTMDSRx4CtrlInfo.b1GCPReceived)
#define SET_HDMI_RX4_GCP_RECEIVED()                     (g_stTMDSRx4CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_RX4_GCP_RECEIVED()                     (g_stTMDSRx4CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of HDR Received Flag
//--------------------------------------------------
#if(_HDMI_HDR10_SUPPORT == _ON)
#define GET_HDMI_RX4_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx4CtrlInfo.b1HDRInfoFrameReceived)
#define SET_HDMI_RX4_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx4CtrlInfo.b1HDRInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX4_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx4CtrlInfo.b1HDRInfoFrameReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_RX4_Z0_ASSERTED()                      (g_stTMDSRx4CtrlInfo.b1Z0Asserted)
#define SET_TMDS_RX4_Z0_ASSERTED()                      (g_stTMDSRx4CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_RX4_Z0_ASSERTED()                      (g_stTMDSRx4CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_RX4_HPD_TRIGGER_EVENT()                (g_stTMDSRx4CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX4_HPD_TRIGGER_EVENT(x)               (g_stTMDSRx4CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX4_HPD_TRIGGER_EVENT()                (g_stTMDSRx4CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#if(_D4_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI 2.0 Format Reset Check Wait
//--------------------------------------------------
#define GET_TMDS_RX4_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx4CtrlInfo.b1HDMI2FormatResetWaiting)
#define SET_TMDS_RX4_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx4CtrlInfo.b1HDMI2FormatResetWaiting = _TRUE)
#define CLR_TMDS_RX4_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx4CtrlInfo.b1HDMI2FormatResetWaiting = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 Read Request Enable Flag
//--------------------------------------------------
#define GET_HDMI_2_0_RX4_RR_ENABLE()                    (g_stTMDSRx4CtrlInfo.b1HDMI2RREnable)
#define SET_HDMI_2_0_RX4_RR_ENABLE()                    (g_stTMDSRx4CtrlInfo.b1HDMI2RREnable = _TRUE)
#define CLR_HDMI_2_0_RX4_RR_ENABLE()                    (g_stTMDSRx4CtrlInfo.b1HDMI2RREnable = _FALSE)
#endif

#define GET_TMDS_RX4_DDC_DETECTED()                     (g_stTMDSRx4CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX4_DDC_DETECTED()                     (g_stTMDSRx4CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX4_DDC_DETECTED()                     (g_stTMDSRx4CtrlInfo.b1TMDSDdcDetected = _FALSE)

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
#define GET_TMDS_RX4_CLK_MODE()                         (g_ucTMDSRx4ClkMode)
#define SET_TMDS_RX4_CLK_MODE(x)                        (g_ucTMDSRx4ClkMode = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTMDSCtrlInfo g_stTMDSRx4CtrlInfo;
extern WORD g_usTMDSRx4ClkCount;

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
extern BYTE g_ucTMDSRx4ClkMode;
#endif

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)))
extern BYTE g_pucTmdsRx4Caps[3];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTMDSRx4Initial(void);
extern void ScalerTMDSRx4InterruptInitial(void);
extern void ScalerTMDSRx4IntHandler_EXINT0(void);
extern void ScalerTMDSRx4PSIntHandler_EXINT0(void);
extern bit ScalerTMDSRx4CheckCDRStable(WORD usClkCount);
extern BYTE ScalerTMDSRx4CheckCDRStable_EXINT0(WORD usClkCount);

#if(_D4_HDMI_SUPPORT == _ON)

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
extern bit ScalerTMDSRx4HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth);
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)

extern void ScalerTMDSRx4HdmiAVMuteProc(void);

#if(_D4_HDMI_2_0_SUPPORT == _ON)
extern void ScalerTMDSRx4ReadRequestProc_EXINT0(BYTE ucRROutCome);
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
extern void ScalerTMDSRx4HDMI2HPDRRIRQEnable(bit bEnable);
#endif
extern void ScalerTMDSRx4ReadRequestTimerEventEnable_WDINT(bit bEnable);
extern void ScalerTMDSRx4Hdmi2FormatResetEvent(void);
#endif

#endif

extern void ScalerTMDSRx4PowerSavingProc(void);
extern void ScalerTMDSRx4FreqDetectDisable(void);

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
extern BYTE ScalerTMDSRx4TMDSScanInputPort(BYTE ucInputType);
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

extern BYTE ScalerTMDSRx4FormatDetect(void);
extern bit ScalerTMDSRx4HdcpEnabled(void);
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
extern bit ScalerTMDSRx4CheckDataDFE(void);

extern bit ScalerTMDSRx4TMDSStableDetect(BYTE ucSourceType);
extern void ScalerTMDSRx4HotPlugEvent(void);
extern void ScalerTMDSRx4SwitchSlaveAddr(void);
extern void ScalerTMDSRx4BeforeHotPlugEventProc(void);
extern void ScalerTMDSRx4AfterHotPlugEventProc(void);
extern void ScalerTMDSRx4Hdcp1p4AksvClear(void);

#endif // End of #if(_D4_TMDS_SUPPORT == _ON)

