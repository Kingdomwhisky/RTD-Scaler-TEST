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
// ID Code      : RL6410_Series_TMDSRx5Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_D5_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_RX5_PHY_SET()                          (g_stTMDSRx5CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_RX5_PHY_SET()                          (g_stTMDSRx5CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_RX5_PHY_SET()                          (g_stTMDSRx5CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_RX5_RGBHV_DETECTING()                  (g_stTMDSRx5CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_RX5_RGBHV_DETECTING()                  (g_stTMDSRx5CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_RX5_RGBHV_DETECTING()                  (g_stTMDSRx5CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_RX5_PACKET_DETECTING()                 (g_stTMDSRx5CtrlInfo.b1PacketDetecting)
#define SET_HDMI_RX5_PACKET_DETECTING()                 (g_stTMDSRx5CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_RX5_PACKET_DETECTING()                 (g_stTMDSRx5CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx5CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx5CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX5_AVI_INFO_FRAME_RECEIVED()          (g_stTMDSRx5CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_RX5_GCP_RECEIVED()                     (g_stTMDSRx5CtrlInfo.b1GCPReceived)
#define SET_HDMI_RX5_GCP_RECEIVED()                     (g_stTMDSRx5CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_RX5_GCP_RECEIVED()                     (g_stTMDSRx5CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of HDR Received Flag
//--------------------------------------------------
#if(_HDMI_HDR10_SUPPORT == _ON)
#define GET_HDMI_RX5_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx5CtrlInfo.b1HDRInfoFrameReceived)
#define SET_HDMI_RX5_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx5CtrlInfo.b1HDRInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX5_HDR10_INFO_FRAME_RECEIVED()        (g_stTMDSRx5CtrlInfo.b1HDRInfoFrameReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_RX5_Z0_ASSERTED()                      (g_stTMDSRx5CtrlInfo.b1Z0Asserted)
#define SET_TMDS_RX5_Z0_ASSERTED()                      (g_stTMDSRx5CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_RX5_Z0_ASSERTED()                      (g_stTMDSRx5CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_RX5_HPD_TRIGGER_EVENT()                (g_stTMDSRx5CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX5_HPD_TRIGGER_EVENT(x)               (g_stTMDSRx5CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX5_HPD_TRIGGER_EVENT()                (g_stTMDSRx5CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#if(_D5_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI 2.0 Format Reset Check Wait
//--------------------------------------------------
#define GET_TMDS_RX5_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx5CtrlInfo.b1HDMI2FormatResetWaiting)
#define SET_TMDS_RX5_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx5CtrlInfo.b1HDMI2FormatResetWaiting = _TRUE)
#define CLR_TMDS_RX5_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx5CtrlInfo.b1HDMI2FormatResetWaiting = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 Read Request Enable Flag
//--------------------------------------------------
#define GET_HDMI_2_0_RX5_RR_ENABLE()                    (g_stTMDSRx5CtrlInfo.b1HDMI2RREnable)
#define SET_HDMI_2_0_RX5_RR_ENABLE()                    (g_stTMDSRx5CtrlInfo.b1HDMI2RREnable = _TRUE)
#define CLR_HDMI_2_0_RX5_RR_ENABLE()                    (g_stTMDSRx5CtrlInfo.b1HDMI2RREnable = _FALSE)
#endif

#define GET_TMDS_RX5_DDC_DETECTED()                     (g_stTMDSRx5CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX5_DDC_DETECTED()                     (g_stTMDSRx5CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX5_DDC_DETECTED()                     (g_stTMDSRx5CtrlInfo.b1TMDSDdcDetected = _FALSE)

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
#define GET_TMDS_RX5_CLK_MODE()                         (g_ucTMDSRx5ClkMode)
#define SET_TMDS_RX5_CLK_MODE(x)                        (g_ucTMDSRx5ClkMode = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTMDSCtrlInfo g_stTMDSRx5CtrlInfo;
extern WORD g_usTMDSRx5ClkCount;
extern BYTE g_ucTMDSRx5Z0Status;

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
extern BYTE g_ucTMDSRx5ClkMode;
#endif

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)))
extern BYTE g_pucTmdsRx5Caps[3];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern void ScalerTMDSRx5Initial(void);
extern void ScalerTMDSRx5InterruptInitial(void);
extern void ScalerTMDSRx5IntHandler_EXINT0(void);
extern void ScalerTMDSRx5PSIntHandler_EXINT0(void);
extern bit ScalerTMDSRx5CheckCDRStable(WORD usClkCount);
extern BYTE ScalerTMDSRx5CheckCDRStable_EXINT0(WORD usClkCount);

#if(_D5_HDMI_SUPPORT == _ON)
extern bit ScalerTMDSRx5HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth);
extern void ScalerTMDSRx5HdmiAVMuteProc(void);

#if(_D5_HDMI_2_0_SUPPORT == _ON)
extern void ScalerTMDSRx5ReadRequestProc_EXINT0(BYTE ucRROutCome);
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
extern void ScalerTMDSRx5HDMI2HPDRRIRQEnable(bit bEnable);
#endif
extern void ScalerTMDSRx5ReadRequestTimerEventEnable_WDINT(bit bEnable);
extern void ScalerTMDSRx5Hdmi2FormatResetEvent(void);
#endif

#endif

extern void ScalerTMDSRx5PowerSavingProc(void);
extern void ScalerTMDSRx5FreqDetectDisable(void);

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
extern BYTE ScalerTMDSRx5TMDSScanInputPort(BYTE ucInputType);
#endif

extern BYTE ScalerTMDSRx5FormatDetect(void);
extern bit ScalerTMDSRx5HdcpEnabled(void);
extern bit ScalerTMDSRx5CheckDataDFE(void);

extern bit ScalerTMDSRx5TMDSStableDetect(BYTE ucSourceType);
extern void ScalerTMDSRx5HotPlugEvent(void);
extern void ScalerTMDSRx5SwitchSlaveAddr(void);
extern void ScalerTMDSRx5BeforeHotPlugEventProc(void);
extern void ScalerTMDSRx5AfterHotPlugEventProc(void);
extern void ScalerTMDSRx5Hdcp1p4AksvClear(void);

#endif // End of #if(_D5_TMDS_SUPPORT == _ON)

