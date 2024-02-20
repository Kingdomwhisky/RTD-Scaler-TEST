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
// ID Code      : ScalerCommonDPRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D1_DP_EXIST == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_RX1_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx1MSAFailMacRsetCount)
#define ADD_DP_RX1_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx1MSAFailMacRsetCount++)
#define CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx1MSAFailMacRsetCount = 0)

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
#define GET_DP_RX1_SIGNALDETECT_INT_HAPPENED()          (g_bDpRx1SignaldetectINTHappened)
#define SET_DP_RX1_SIGNALDETECT_INT_HAPPENED()          (g_bDpRx1SignaldetectINTHappened = _TRUE)
#define CLR_DP_RX1_SIGNALDETECT_INT_HAPPENED()          (g_bDpRx1SignaldetectINTHappened = _FALSE)
#endif

//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX1_FAKE_LINK_TRAINING()                 ((g_ucDpRx1Info & _BIT7) >> 7)
#define SET_DP_RX1_FAKE_LINK_TRAINING()                 (g_ucDpRx1Info |= _BIT7)
#define CLR_DP_RX1_FAKE_LINK_TRAINING()                 (g_ucDpRx1Info &= ~_BIT7)

#define GET_DP_RX1_VALID_VIDEO_CHECK()                  ((g_ucDpRx1Info & _BIT6) >> 6)
#define SET_DP_RX1_VALID_VIDEO_CHECK()                  (g_ucDpRx1Info |= _BIT6)
#define CLR_DP_RX1_VALID_VIDEO_CHECK()                  {\
                                                            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);\
                                                            (g_ucDpRx1Info &= ~_BIT6);\
                                                        }

#define GET_DP_RX1_CRC_CALCULATE()                      ((g_ucDpRx1Info & _BIT5) >> 5)
#define SET_DP_RX1_CRC_CALCULATE()                      (g_ucDpRx1Info |= _BIT5)
#define CLR_DP_RX1_CRC_CALCULATE()                      (g_ucDpRx1Info &= ~_BIT5)

#define GET_DP_RX1_PS_AUX_TOGGLE()                      (g_bDpRx1PSAuxToggle)
#define SET_DP_RX1_PS_AUX_TOGGLE()                      (g_bDpRx1PSAuxToggle = _TRUE)
#define CLR_DP_RX1_PS_AUX_TOGGLE()                      (g_bDpRx1PSAuxToggle = _FALSE)

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//----------------------------------------------------------------------------
// Macro of Dp Lane Valid Check
//----------------------------------------------------------------------------
#define GET_DP_RX1_SOURCE_TYPE_JUDGE()                  (g_bDpRx1SourceTypeJudge)
#define SET_DP_RX1_SOURCE_TYPE_JUDGE()                  (g_bDpRx1SourceTypeJudge = _TRUE)
#define CLR_DP_RX1_SOURCE_TYPE_JUDGE()                  (g_bDpRx1SourceTypeJudge = _FALSE)
#endif

//--------------------------------------------------
// Macro of Dp Error Count Read Record
//--------------------------------------------------
#define GET_DP_RX1_SOURCE_READ_ERROR_COUNT()            (g_bDpRx1SourceRDErrorCount)
#define SET_DP_RX1_SOURCE_READ_ERROR_COUNT()            (g_bDpRx1SourceRDErrorCount = _TRUE)
#define CLR_DP_RX1_SOURCE_READ_ERROR_COUNT()            (g_bDpRx1SourceRDErrorCount = _FALSE)

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
#define GET_DP_RX1_RSV0_DETECTING()                     (g_stDPRx1InfoFrameRSV0Ctrl.b1RSV0PacketDetecting)
#define SET_DP_RX1_RSV0_DETECTING()                     (g_stDPRx1InfoFrameRSV0Ctrl.b1RSV0PacketDetecting = _TRUE)
#define CLR_DP_RX1_RSV0_DETECTING()                     (g_stDPRx1InfoFrameRSV0Ctrl.b1RSV0PacketDetecting = _FALSE)

#define GET_DP_RX1_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx1InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive)
#define SET_DP_RX1_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx1InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive = _TRUE)
#define CLR_DP_RX1_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx1InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive = _FALSE)

#define GET_DP_RX1_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx1InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive)
#define SET_DP_RX1_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx1InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive = _TRUE)
#define CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx1InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive = _FALSE)

#define GET_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED()        (g_stDPRx1InfoFrameRSV0Ctrl.b1AMDSPDInfoFrameReceive)
#define SET_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED()        (g_stDPRx1InfoFrameRSV0Ctrl.b1AMDSPDInfoFrameReceive = _TRUE)
#define CLR_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED()        (g_stDPRx1InfoFrameRSV0Ctrl.b1AMDSPDInfoFrameReceive = _FALSE)
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#define GET_DP_RX1_VSC_SDP_COLOR_MODE()                 (g_bDpRx1VscSdpColorMode)
#define SET_DP_RX1_VSC_SDP_COLOR_MODE()                 (g_bDpRx1VscSdpColorMode = _TRUE)
#define CLR_DP_RX1_VSC_SDP_COLOR_MODE()                 (g_bDpRx1VscSdpColorMode = _FALSE)

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
#define GET_DP_RX1_RSV1_DETECTING()                     (g_bDpRx1RSV1PacketDetecting)
#define SET_DP_RX1_RSV1_DETECTING()                     (g_bDpRx1RSV1PacketDetecting = _TRUE)
#define CLR_DP_RX1_RSV1_DETECTING()                     (g_bDpRx1RSV1PacketDetecting = _FALSE)

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#define GET_DP_RX1_MST2SST_RSV1_DETECTING()             (g_bDpRx1MstToSstRSV1PacketDetecting)
#define SET_DP_RX1_MST2SST_RSV1_DETECTING()             (g_bDpRx1MstToSstRSV1PacketDetecting = _TRUE)
#define CLR_DP_RX1_MST2SST_RSV1_DETECTING()             (g_bDpRx1MstToSstRSV1PacketDetecting = _FALSE)
#endif
#endif
#endif

//--------------------------------------------------
// Macro of Dp Measure Pop Up Action
//--------------------------------------------------
// Delay 5us for Wait Hw Update Period to Prevent MCU Get wrong value, Update Period is 3T, T = 1/14.318M or 1/27M
#define SET_DP_RX1_MEASURE_POP_UP()                     {\
                                                            ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                            DELAY_5US();\
                                                        }

// Delay 5us for Wait Hw Update Period to Prevent MCU Get wrong value, Update Period is 3T, T = 1/14.318M or 1/27M
#define SET_DP_RX1_MEASURE_POP_UP_MST2SST()             {\
                                                            ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                            DELAY_5US();\
                                                        }

//--------------------------------------------------
// Macro of DP Rx Interlace info
//--------------------------------------------------
#define GET_DP_RX1_INTERLACE_VTOTAL_NUMBER()            (g_bDpRx1InterlaceVtotalNum)
#define SET_DP_RX1_INTERLACE_VTOTAL_NUMBER(x)           (g_bDpRx1InterlaceVtotalNum = (x))

//--------------------------------------------------
// Macro of DP Mst to sst V-Front Porch Setting
//--------------------------------------------------
#if(_DP_TX_SUPPORT == _ON)
#define GET_DP_RX1_MST_TO_SST_VFRONT_PORCH()            (g_usDpRx1MstToSstVfrontporch)
#define SET_DP_RX1_MST_TO_SST_VFRONT_PORCH(x)           (g_usDpRx1MstToSstVfrontporch = (x))

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
#define SET_DP_RX1_INTERLACE_VTT_FW_MODE_MST2SST(x)     {\
                                                        }
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
extern bit g_bDpRx1SignaldetectINTHappened;
#endif

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT != _ON)
extern BYTE g_ucDpRx1DPCD02200hValue;
extern BYTE g_ucDpRx1DPCD02201hValue;
extern BYTE g_ucDpRx1DPCD02210hValue;
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit g_bDpRx1VscSdpColorMode;

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern bit g_bDpRx1RSV1PacketDetecting;

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern bit g_bDpRx1MstToSstRSV1PacketDetecting;
#endif
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
extern WORD g_usDpRx1MstToSstVfrontporch;
#endif

extern BYTE g_ucDpRx1MSAFailMacRsetCount;
extern bit g_bDpRx1SourceRDErrorCount;
extern bit g_bDpRx1InterlaceVtotalNum;
extern bit g_bDpRx1Tp1Initial;
extern BYTE g_ucDpRx1LTPatternSet;

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit g_bDpRx1SourceTypeJudge;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
extern BYTE g_pucDPRx1HDR10Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
extern BYTE g_pucDPRx1RSV0Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
extern StructDPInfoFrameRSV0Ctrl g_stDPRx1InfoFrameRSV0Ctrl;
#endif

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
extern BYTE g_ucDpRx1AuxModeBackup_EXINT;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerDpRx1DecodeErrorCountReset_WDINT(void);
#endif

void ScalerDpRx1DecodeErrorCountReset(void);
extern WORD ScalerDpRx1GetDecodeErrorCount(BYTE ucDpRx1LaneNumber);
extern void ScalerDpRx1ValidSignalDetection(void);
extern WORD ScalerDpRx1SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);
extern bit ScalerDpRx1SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern bit ScalerDpRx1InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);
extern bit ScalerDpRx1GetVideoInfo(void);
extern void ScalerDpRx1SetColorInfo(void);
extern void ScalerDpRx1VideoSetting(void);
extern void ScalerDpRx1ColorimetrySetting(void);
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern void ScalerDpRx1ColorimetryExtSetting(void);
#endif
extern void ScalerDpRx1QuantizationSetting(void);

extern bit ScalerDpRx1MiscCheck(void);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit ScalerDpRx1VscCheck(void);

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern void ScalerDpRx1RSV1PacketDetectEvent(void);
extern void ScalerDpRx1SetInitialRSV1InfoType(void);
#endif
#endif

extern void ScalerDpRx1HDCPUnplugReset(void);

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpRx1MstReset(void);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
extern void ScalerDpRx1MstReset_EXINT0(void);
#endif

extern bit ScalerDpRx1AuxChSourcePowerCheck(void);
extern void ScalerDpRx1AuxChPowerStatusCheck(bit bCableStatus);

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpRx1MstToSstInterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern void ScalerDpRx1MstToSstRSV1PacketDetectEvent(void);
#endif
#endif
#endif
#endif

extern bit ScalerDpRx1MSACheck(void);
#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
extern bit ScalerDpRx1VbiosAssrCheck(bit bMSACheckResult);
#endif
extern void ScalerDpRx1FakeLTProtect(void);
extern void ScalerDpRx1SetInitialRSV0InfoType(void);
extern void ScalerDpRx1SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType);
extern void ScalerDpRx1HpdIrqAssert(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpRx1HpdIrqAssert_EXINT0(void);
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_ULTRA_HDR_SUPPORT == _ON))
extern void ScalerDpRx1GetInfoFrameRSV0(BYTE *pucDPRx1RSV0Data);
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
extern void ScalerDpRx1InfoFrameRSV0Check(void);
extern void ScalerDpRx1RSV0PacketDetectEvent(void);
extern void ScalerDpRx1InfoFrameRSV0Initial(void);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_AUDIO_SUPPORT == _ON)
extern void ScalerDpRx1SwitchHDR10CmpAudioInfo(void);
#endif
#endif

#endif // End of #if(_D1_DP_EXIST == _ON)
