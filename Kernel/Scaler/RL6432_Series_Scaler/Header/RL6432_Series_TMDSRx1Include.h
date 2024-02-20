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
// ID Code      : RL6432_Series_TMDSRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_D1_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_RX1_PHY_SET()                          (g_stTMDSRx1CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_RX1_PHY_SET()                          (g_stTMDSRx1CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_RX1_PHY_SET()                          (g_stTMDSRx1CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_RX1_RGBHV_DETECTING()                  (g_stTMDSRx1CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_RX1_RGBHV_DETECTING()                  (g_stTMDSRx1CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_RX1_RGBHV_DETECTING()                  (g_stTMDSRx1CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_RX1_PACKET_DETECTING()                 (g_stTMDSRx1CtrlInfo.b1PacketDetecting)
#define SET_HDMI_RX1_PACKET_DETECTING()                 (g_stTMDSRx1CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_RX1_PACKET_DETECTING()                 (g_stTMDSRx1CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx1CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx1CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX1_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx1CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_RX1_GCP_RECEIVED()                     (g_stTMDSRx1CtrlInfo.b1GCPReceived)
#define SET_HDMI_RX1_GCP_RECEIVED()                     (g_stTMDSRx1CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_RX1_GCP_RECEIVED()                     (g_stTMDSRx1CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of HDR Received Flag
//--------------------------------------------------
#if(_HDMI_HDR10_SUPPORT == _ON)
#define GET_HDMI_RX1_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx1CtrlInfo.b1HDRInfoFrameReceived)
#define SET_HDMI_RX1_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx1CtrlInfo.b1HDRInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX1_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx1CtrlInfo.b1HDRInfoFrameReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_RX1_Z0_ASSERTED()                      (g_stTMDSRx1CtrlInfo.b1Z0Asserted)
#define SET_TMDS_RX1_Z0_ASSERTED()                      (g_stTMDSRx1CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_RX1_Z0_ASSERTED()                      (g_stTMDSRx1CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_RX1_HPD_TRIGGER_EVENT()                (g_stTMDSRx1CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX1_HPD_TRIGGER_EVENT(x)               (g_stTMDSRx1CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX1_HPD_TRIGGER_EVENT()                (g_stTMDSRx1CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#if(_D1_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI 2.0 Format Reset Check Wait
//--------------------------------------------------
#define GET_TMDS_RX1_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx1CtrlInfo.b1HDMI2FormatResetWaiting)
#define SET_TMDS_RX1_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx1CtrlInfo.b1HDMI2FormatResetWaiting = _TRUE)
#define CLR_TMDS_RX1_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx1CtrlInfo.b1HDMI2FormatResetWaiting = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 Read Request Enable Flag
//--------------------------------------------------
#define GET_HDMI_2_0_RX1_RR_ENABLE()                    (g_stTMDSRx1CtrlInfo.b1HDMI2RREnable)
#define SET_HDMI_2_0_RX1_RR_ENABLE()                    (g_stTMDSRx1CtrlInfo.b1HDMI2RREnable = _TRUE)
#define CLR_HDMI_2_0_RX1_RR_ENABLE()                    (g_stTMDSRx1CtrlInfo.b1HDMI2RREnable = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 High Speed Mode
//--------------------------------------------------
#define GET_TMDS_RX1_HIGH_SPEED_MODE()                  (g_stTMDSRx1CtrlInfo.b1HDMI2HighSpeedMode)
#define SET_TMDS_RX1_HIGH_SPEED_MODE()                  (g_stTMDSRx1CtrlInfo.b1HDMI2HighSpeedMode = _TRUE)
#define CLR_TMDS_RX1_HIGH_SPEED_MODE()                  (g_stTMDSRx1CtrlInfo.b1HDMI2HighSpeedMode = _FALSE)
#endif

#define GET_TMDS_RX1_DDC_DETECTED()                     (g_stTMDSRx1CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX1_DDC_DETECTED()                     (g_stTMDSRx1CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX1_DDC_DETECTED()                     (g_stTMDSRx1CtrlInfo.b1TMDSDdcDetected = _FALSE)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#define GET_TMDS_RX1_CLK_MODE()                         (g_ucTMDSRx1ClkMode)
#define SET_TMDS_RX1_CLK_MODE(x)                        (g_ucTMDSRx1ClkMode = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTMDSCtrlInfo g_stTMDSRx1CtrlInfo;
extern WORD g_usTMDSRx1ClkCount;

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
extern BYTE g_ucTMDSRx1ClkMode;
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
extern BYTE g_pucTmdsRx1Caps[3];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTMDSRx1Initial(void);
extern void ScalerTMDSRx1InterruptInitial(void);
extern void ScalerTMDSRx1IntHandler_EXINT0(void);
extern void ScalerTMDSRx1PSIntHandler_EXINT0(void);
extern void ScalerTMDSRx1SetPorchColor(EnumColorSpace enumColorFormat);

#if(_D1_HDMI_SUPPORT == _ON)
extern bit ScalerTMDSRx1HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth);
extern bit ScalerTMDSRx1HdmiWaitDeepColorPllLock(void);
extern void ScalerTMDSRx1HdmiPacketDetect(bit bWait);
extern BYTE ScalerTMDSRx1HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern void ScalerTMDSRx1HdmiAVMuteProc(void);
extern void ScalerTMDSRx1HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
extern void ScalerTMDSRx1ReadRequestProc_EXINT0(BYTE ucRROutCome);
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
extern void ScalerTMDSRx1HDMI2HPDRRIRQEnable(bit bEnable);
#endif
extern void ScalerTMDSRx1ReadRequestTimerEventEnable_WDINT(bit bEnable);
#endif

#endif

extern void ScalerTMDSRx1PowerSavingProc(void);
extern void ScalerTMDSRx1FreqDetectDisable(void);
extern bit ScalerTMDSRx1TMDSPSPreDetect(void);
extern bit ScalerTMDSRx1TMDSNormalPreDetect(void);
extern BYTE ScalerTMDSRx1TMDSScanInputPort(BYTE ucInputType);
extern bit ScalerTMDSRx1HdcpEnabled(void);
extern BYTE ScalerTMDSRx1TMDSVideoDetect(bit bWait);
extern bit ScalerTMDSRx1CheckDataDFE(void);

extern bit ScalerTMDSRx1TMDSStableDetect(BYTE ucSourceType);
extern void ScalerTMDSRx1HotPlugEvent(void);
extern void ScalerTMDSRx1SwitchSlaveAddr(void);
extern void ScalerTMDSRx1BeforeHotPlugEventProc(void);
extern void ScalerTMDSRx1AfterHotPlugEventProc(void);
extern void ScalerTMDSRx1Hdcp1p4AksvClear(void);

#endif // End of #if(_D1_TMDS_SUPPORT == _ON)
