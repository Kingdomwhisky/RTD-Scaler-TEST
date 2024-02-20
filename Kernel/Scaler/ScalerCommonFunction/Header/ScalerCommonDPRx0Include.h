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
// ID Code      : ScalerCommonDPRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D0_DP_EXIST == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_RX0_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx0MSAFailMacRsetCount)
#define ADD_DP_RX0_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx0MSAFailMacRsetCount++)
#define CLR_DP_RX0_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx0MSAFailMacRsetCount = 0)

#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
#define GET_DP_RX0_SIGNALDETECT_INT_HAPPENED()          (g_bDpRx0SignaldetectINTHappened)
#define SET_DP_RX0_SIGNALDETECT_INT_HAPPENED()          (g_bDpRx0SignaldetectINTHappened = _TRUE)
#define CLR_DP_RX0_SIGNALDETECT_INT_HAPPENED()          (g_bDpRx0SignaldetectINTHappened = _FALSE)
#endif

//--------------------------------------------------
// Macro of Dp Error Count Read Record
//--------------------------------------------------
#define GET_DP_RX0_SOURCE_READ_ERROR_COUNT()            (g_bDpRx0SourceRDErrorCount)
#define SET_DP_RX0_SOURCE_READ_ERROR_COUNT()            (g_bDpRx0SourceRDErrorCount = _TRUE)
#define CLR_DP_RX0_SOURCE_READ_ERROR_COUNT()            (g_bDpRx0SourceRDErrorCount = _FALSE)

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
#define GET_DP_RX0_RSV0_DETECTING()                     (g_stDPRx0InfoFrameRSV0Ctrl.b1RSV0PacketDetecting)
#define SET_DP_RX0_RSV0_DETECTING()                     (g_stDPRx0InfoFrameRSV0Ctrl.b1RSV0PacketDetecting = _TRUE)
#define CLR_DP_RX0_RSV0_DETECTING()                     (g_stDPRx0InfoFrameRSV0Ctrl.b1RSV0PacketDetecting = _FALSE)

#define GET_DP_RX0_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx0InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive)
#define SET_DP_RX0_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx0InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive = _TRUE)
#define CLR_DP_RX0_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx0InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive = _FALSE)

#define GET_DP_RX0_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx0InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive)
#define SET_DP_RX0_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx0InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive = _TRUE)
#define CLR_DP_RX0_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx0InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive = _FALSE)

#define GET_DP_RX0_AMD_SPD_INFO_FRAME_RECEIVED()        (g_stDPRx0InfoFrameRSV0Ctrl.b1AMDSPDInfoFrameReceive)
#define SET_DP_RX0_AMD_SPD_INFO_FRAME_RECEIVED()        (g_stDPRx0InfoFrameRSV0Ctrl.b1AMDSPDInfoFrameReceive = _TRUE)
#define CLR_DP_RX0_AMD_SPD_INFO_FRAME_RECEIVED()        (g_stDPRx0InfoFrameRSV0Ctrl.b1AMDSPDInfoFrameReceive = _FALSE)
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#define GET_DP_RX0_VSC_SDP_COLOR_MODE()                 (g_bDpRx0VscSdpColorMode)
#define SET_DP_RX0_VSC_SDP_COLOR_MODE()                 (g_bDpRx0VscSdpColorMode = _TRUE)
#define CLR_DP_RX0_VSC_SDP_COLOR_MODE()                 (g_bDpRx0VscSdpColorMode = _FALSE)

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
#define GET_DP_RX0_RSV1_DETECTING()                     (g_bDpRx0RSV1PacketDetecting)
#define SET_DP_RX0_RSV1_DETECTING()                     (g_bDpRx0RSV1PacketDetecting = _TRUE)
#define CLR_DP_RX0_RSV1_DETECTING()                     (g_bDpRx0RSV1PacketDetecting = _FALSE)

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#define GET_DP_RX0_MST2SST_RSV1_DETECTING()             (g_bDpRx0MstToSstRSV1PacketDetecting)
#define SET_DP_RX0_MST2SST_RSV1_DETECTING()             (g_bDpRx0MstToSstRSV1PacketDetecting = _TRUE)
#define CLR_DP_RX0_MST2SST_RSV1_DETECTING()             (g_bDpRx0MstToSstRSV1PacketDetecting = _FALSE)
#endif
#endif
#endif // End of #if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)



//--------------------------------------------------
// Macro of Dp Measure Pop Up Action
//--------------------------------------------------
// Delay 5us for Wait Hw Update Period to Prevent MCU Get wrong value, Update Period is 3T, T = 1/14.318M or 1/27M
#define SET_DP_RX0_MEASURE_POP_UP()                     {\
                                                            ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                            DELAY_5US();\
                                                        }


// Delay 5us for Wait Hw Update Period to Prevent MCU Get wrong value, Update Period is 3T, T = 1/14.318M or 1/27M
#define SET_DP_RX0_MEASURE_POP_UP_MST2SST()             {\
                                                            ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                            DELAY_5US();\
                                                        }

//--------------------------------------------------
// Macro of DP Rx Interlace info
//--------------------------------------------------
#define GET_DP_RX0_INTERLACE_VTOTAL_NUMBER()            (g_bDpRx0InterlaceVtotalNum)
#define SET_DP_RX0_INTERLACE_VTOTAL_NUMBER(x)           (g_bDpRx0InterlaceVtotalNum = (x))

//--------------------------------------------------
// Macro of DP Mst to sst V-Front Porch Setting
//--------------------------------------------------
#if(_DP_TX_SUPPORT == _ON)
#define GET_DP_RX0_MST_TO_SST_VFRONT_PORCH()            (g_usDpRx0MstToSstVfrontporch)
#define SET_DP_RX0_MST_TO_SST_VFRONT_PORCH(x)           (g_usDpRx0MstToSstVfrontporch = (x))

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
#define SET_DP_RX0_INTERLACE_VTT_FW_MODE_MST2SST(x)     {\
                                                        }
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
extern bit g_bDpRx0SignaldetectINTHappened;
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit g_bDpRx0VscSdpColorMode;

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern bit g_bDpRx0RSV1PacketDetecting;

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern bit g_bDpRx0MstToSstRSV1PacketDetecting;
#endif
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
extern WORD g_usDpRx0MstToSstVfrontporch;
#endif

extern BYTE g_ucDpRx0MSAFailMacRsetCount;
extern bit g_bDpRx0SourceRDErrorCount;
extern bit g_bDpRx0InterlaceVtotalNum;
extern bit g_bDpRx0Tp1Initial;
extern BYTE g_ucDpRx0LTPatternSet;

#if(_DP_HDR10_SUPPORT == _ON)
extern BYTE g_pucDPRx0HDR10Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
extern BYTE g_pucDPRx0RSV0Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
extern StructDPInfoFrameRSV0Ctrl g_stDPRx0InfoFrameRSV0Ctrl;
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
extern StructDpLinkInfo g_stDpRx0LinkInfo;
#endif

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
extern BYTE g_ucDpRx0AuxModeBackup_EXINT;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx0DecodeErrorCountReset(void);
extern WORD ScalerDpRx0GetDecodeErrorCount(BYTE ucDpRx0LaneNumber);
extern void ScalerDpRx0ValidSignalDetection(void);
extern WORD ScalerDpRx0SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);
extern bit ScalerDpRx0SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern bit ScalerDpRx0InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);
extern bit ScalerDpRx0GetVideoInfo(void);
extern void ScalerDpRx0SetColorInfo(void);
extern void ScalerDpRx0VideoSetting(void);
extern void ScalerDpRx0ColorimetrySetting(void);
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern void ScalerDpRx0ColorimetryExtSetting(void);
#endif
extern void ScalerDpRx0QuantizationSetting(void);

extern bit ScalerDpRx0MiscCheck(void);
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit ScalerDpRx0VscCheck(void);

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern void ScalerDpRx0RSV1PacketDetectEvent(void);
extern void ScalerDpRx0SetInitialRSV1InfoType(void);
#endif

#endif

extern void ScalerDpRx0HDCPUnplugReset(void);

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpRx0MstReset(void);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
extern void ScalerDpRx0MstReset_EXINT0(void);
#endif

extern bit ScalerDpRx0AuxChSourcePowerCheck(void);
extern void ScalerDpRx0AuxChPowerStatusCheck(bit bCableStatus);

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpRx0MstToSstGetVideoInfo(void);
extern void ScalerDpRx0MstToSstSetColorInfo(void);
extern void ScalerDpRx0MstToSstVideoSetting(void);
extern bit ScalerDpRx0MstToSstMiscCheck(void);
extern bit ScalerDpRx0MstToSstInterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit ScalerDpRx0MstToSstVscCheck(void);

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern void ScalerDpRx0MstToSstRSV1PacketDetectEvent(void);
#endif
#endif

#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx0UpdateSinkCount(BYTE ucSinkCount);
#endif

extern bit ScalerDpRx0MSACheck(void);
extern void ScalerDpRx0FakeLTProtect(void);
extern void ScalerDpRx0SetInitialRSV0InfoType(void);

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_ULTRA_HDR_SUPPORT == _ON))
extern void ScalerDpRx0GetInfoFrameRSV0(BYTE *pucDPRx0RSV0Data);
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
extern void ScalerDpRx0InfoFrameRSV0Check(void);
extern void ScalerDpRx0RSV0PacketDetectEvent(void);
extern void ScalerDpRx0InfoFrameRSV0Initial(void);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_AUDIO_SUPPORT == _ON)
extern void ScalerDpRx0SwitchHDR10CmpAudioInfo(void);
#endif
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerDpRx0DecodeErrorCountReset_WDINT(void);
#endif

#endif // End of #if(_D0_DP_EXIST == _ON)
