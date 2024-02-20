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
// ID Code      : RL6369_Series_TMDSInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
#define CHECK_TMDS_DPHY_SWITCH(port)                (\
                                                        (((port) == _D0_INPUT_PORT) && (ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == 0x00)) ||\
                                                        (((port) == _D1_INPUT_PORT) && (ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT6)) ||\
                                                        (((port) == _D2_INPUT_PORT) && (ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT7))\
                                                    )
//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_PHY_SET()                          (g_stTMDSRx0CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_PHY_SET()                          (g_stTMDSRx0CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_PHY_SET()                          (g_stTMDSRx0CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_RGBHV_DETECTING()                  (g_stTMDSRx0CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_RGBHV_DETECTING()                  (g_stTMDSRx0CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_RGBHV_DETECTING()                  (g_stTMDSRx0CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_PACKET_DETECTING()                 (g_stTMDSRx0CtrlInfo.b1PacketDetecting)
#define SET_HDMI_PACKET_DETECTING()                 (g_stTMDSRx0CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_PACKET_DETECTING()                 (g_stTMDSRx0CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_RX0_AVI_INFO_FRAME_RECEIVED()      (g_stTMDSRx0CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_RX0_AVI_INFO_FRAME_RECEIVED()      (g_stTMDSRx0CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_RX0_AVI_INFO_FRAME_RECEIVED()      (g_stTMDSRx0CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_GCP_RECEIVED()                     (g_stTMDSRx0CtrlInfo.b1GCPReceived)
#define SET_HDMI_GCP_RECEIVED()                     (g_stTMDSRx0CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_GCP_RECEIVED()                     (g_stTMDSRx0CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_Z0_ASSERTED()                      (g_stTMDSRx0CtrlInfo.b1Z0Asserted)
#define SET_TMDS_Z0_ASSERTED()                      (g_stTMDSRx0CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_Z0_ASSERTED()                      (g_stTMDSRx0CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_RX0_HPD_TRIGGER_EVENT()            (g_stTMDSRx0CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX0_HPD_TRIGGER_EVENT(x)           (g_stTMDSRx0CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX0_HPD_TRIGGER_EVENT()            (g_stTMDSRx0CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#define GET_TMDS_RX1_HPD_TRIGGER_EVENT()            (g_stTMDSRx1CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX1_HPD_TRIGGER_EVENT(x)           (g_stTMDSRx1CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX1_HPD_TRIGGER_EVENT()            (g_stTMDSRx1CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#define GET_TMDS_RX2_HPD_TRIGGER_EVENT()            (g_stTMDSRx2CtrlInfo.b3HPDTriggerEvent)
#define SET_TMDS_RX2_HPD_TRIGGER_EVENT(x)           (g_stTMDSRx2CtrlInfo.b3HPDTriggerEvent = (x))
#define CLR_TMDS_RX2_HPD_TRIGGER_EVENT()            (g_stTMDSRx2CtrlInfo.b3HPDTriggerEvent = _TMDS_HPD_NONE)

#define GET_TMDS_RX0_DDC_DETECTED()                 (g_stTMDSRx0CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX0_DDC_DETECTED()                 (g_stTMDSRx0CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX0_DDC_DETECTED()                 (g_stTMDSRx0CtrlInfo.b1TMDSDdcDetected = _FALSE)

#define GET_TMDS_RX1_DDC_DETECTED()                 (g_stTMDSRx1CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX1_DDC_DETECTED()                 (g_stTMDSRx1CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX1_DDC_DETECTED()                 (g_stTMDSRx1CtrlInfo.b1TMDSDdcDetected = _FALSE)

#define GET_TMDS_RX2_DDC_DETECTED()                 (g_stTMDSRx2CtrlInfo.b1TMDSDdcDetected)
#define SET_TMDS_RX2_DDC_DETECTED()                 (g_stTMDSRx2CtrlInfo.b1TMDSDdcDetected = _TRUE)
#define CLR_TMDS_RX2_DDC_DETECTED()                 (g_stTMDSRx2CtrlInfo.b1TMDSDdcDetected = _FALSE)

#if(_MHL_SUPPORT == _ON)
#define GET_TMDS_RX0_CLK_MODE()                     (g_ucTMDSClkMode)
#define SET_TMDS_RX0_CLK_MODE(x)                    (g_ucTMDSClkMode = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTMDSCtrlInfo g_stTMDSRx0CtrlInfo;
extern StructTMDSCtrlInfo g_stTMDSRx1CtrlInfo;
extern StructTMDSCtrlInfo g_stTMDSRx2CtrlInfo;
extern WORD g_usTMDSClkCount;

#if(_MHL_SUPPORT == _ON)
extern BYTE g_ucTMDSClkMode;
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
extern BYTE g_pucRxCaps[3];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTMDSInitial(BYTE ucInputPort);
extern void ScalerTMDSInterruptInitial(BYTE ucInputPort);
extern void ScalerTMDSRx0SetPorchColor(EnumColorSpace enumColorFormat);

#if(_HDMI_SUPPORT == _ON)
extern void ScalerTMDSHdmiAVMuteProc(void);
#endif

extern void ScalerTMDSPowerSavingProc(BYTE ucPortSelect);
extern void ScalerTMDSPowerOffProc(void);
extern void ScalerTMDSFirstActiveProc(BYTE ucInputPort, BYTE ucSourceType);
extern bit ScalerTMDSHdcpEnabled(BYTE ucInputPort);
extern bit ScalerTMDSCheckDataDFE(BYTE ucInputPort);
extern void ScalerTMDSHotPlugEvent(BYTE ucPortSelect);
extern void ScalerTMDSSwitchSlaveAddr(BYTE ucPortSelect);
extern void ScalerTMDSBeforeHotPlugEventProc(BYTE ucPortSelect);
extern void ScalerTMDSAfterHotPlugEventProc(BYTE ucPortSelect);

#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
