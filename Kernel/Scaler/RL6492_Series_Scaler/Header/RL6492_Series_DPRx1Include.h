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
// ID Code      : RL6492_Series_DPRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D1_DP_EXIST == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX1_FAKE_LINK_TRAINING()                 ((g_ucDpRx1Info & _BIT7) >> 7)
#define SET_DP_RX1_FAKE_LINK_TRAINING()                 (g_ucDpRx1Info |= _BIT7)
#define CLR_DP_RX1_FAKE_LINK_TRAINING()                 (g_ucDpRx1Info &= ~_BIT7)

#define GET_DP_RX1_VALID_VIDEO_CHECK()                  ((g_ucDpRx1Info & _BIT6) >> 6)
#define SET_DP_RX1_VALID_VIDEO_CHECK()                  (g_ucDpRx1Info |= _BIT6)
#define CLR_DP_RX1_VALID_VIDEO_CHECK()                  {\
                                                            ScalerDpRx1CancelValidSignalDetectTimerEvent();\
                                                            (g_ucDpRx1Info &= ~_BIT6);\
                                                        }

#define GET_DP_RX1_CRC_CALCULATE()                      ((g_ucDpRx1Info & _BIT5) >> 5)
#define SET_DP_RX1_CRC_CALCULATE()                      (g_ucDpRx1Info |= _BIT5)
#define CLR_DP_RX1_CRC_CALCULATE()                      (g_ucDpRx1Info &= ~_BIT5)

#define GET_DP_RX1_PS_AUX_TOGGLE()                      (g_bDpRx1PSAuxToggle)
#define SET_DP_RX1_PS_AUX_TOGGLE()                      (g_bDpRx1PSAuxToggle = _TRUE)
#define CLR_DP_RX1_PS_AUX_TOGGLE()                      (g_bDpRx1PSAuxToggle = _FALSE)

#define GET_DP_RX1_AUX_COMMAND_NO_REPLY()               (g_bDpRx1AuxCommandNoReply)
#define SET_DP_RX1_AUX_COMMAND_NO_REPLY()               (g_bDpRx1AuxCommandNoReply = _TRUE)
#define CLR_DP_RX1_AUX_COMMAND_NO_REPLY()               (g_bDpRx1AuxCommandNoReply = _FALSE)

#define GET_DP_RX1_PHY_CTS_FLG()                        (((bit)ScalerGetBit(P1D_50_CDR_01, _BIT0)) && (ScalerGetBit(P1D_50_CDR_01, (_BIT2 | _BIT1)) == _BIT1))
#define SET_DP_RX1_PHY_CTS_FLG()                        (ScalerSetBit(P1D_50_CDR_01, ~_BIT0, _BIT0))
#define CLR_DP_RX1_PHY_CTS_FLG()                        (ScalerSetBit(P1D_50_CDR_01, ~_BIT0, 0x00))

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
#define GET_DP_RX1_SIGNALDETECT_INT_HAPPENED()          (g_bDpRx1SignaldetectINTHappened)
#define SET_DP_RX1_SIGNALDETECT_INT_HAPPENED()          (g_bDpRx1SignaldetectINTHappened = _TRUE)
#define CLR_DP_RX1_SIGNALDETECT_INT_HAPPENED()          (g_bDpRx1SignaldetectINTHappened = _FALSE)
#endif

#define SET_DP_RX1_AUX_MANUAL_MODE_EXINT()              (ScalerSetBit_EXINT(PBA_D0_AUX_MODE_SET, ~_BIT1, 0x00))

#define SET_DP_RX1_AUX_MANUAL_MODE()                    {\
                                                            EX0 = 0;\
                                                            ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, 0x00);\
                                                            EX0 = 1;\
                                                        }

#define SET_DP_RX1_AUX_MANUAL_MODE_PHY_CTS()            (ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, 0x00))

#define SET_DP_RX1_AUX_AUTO_MODE_EXINT()                (ScalerSetBit_EXINT(PBA_D0_AUX_MODE_SET, ~_BIT1, _BIT1))

#define SET_DP_RX1_AUX_AUTO_MODE()                      {\
                                                            EX0 = 0;\
                                                            ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, _BIT1);\
                                                            EX0 = 1;\
                                                        }

#define SET_DP_RX1_AUX_AUTO_MODE_PHY_CTS()              (ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, _BIT1))

#define GET_DP_RX1_VFRONT_PORCH()                       (g_usDpRx1Vfrontporch)
#define SET_DP_RX1_VFRONT_PORCH(x)                      (g_usDpRx1Vfrontporch = (x))

#define SET_DP_RX1_PORCH_COLOR_RGB()                    {\
                                                            ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x00);\
                                                            ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                            ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x00);\
                                                            ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                            ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x00);\
                                                            ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                        }

#define SET_DP_RX1_PORCH_COLOR_YCC_LIMIT()              {\
                                                            if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x01);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x01);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x08);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x08);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x01);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x08);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                        }

#define SET_DP_RX1_PORCH_COLOR_YCC_FULL()               {\
                                                            if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x01);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x01);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x08);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x08);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x00);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x08);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                        }

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
#define SET_DP_RX1_INTERLACE_VTT_FW_MODE(x)             {\
                                                            (((x) == _EVEN) ? (ScalerSetBit(PB5_F1_DP_RSV1, ~_BIT4, _BIT4)) : (ScalerSetBit(PB5_F1_DP_RSV1, ~_BIT4, 0x00)));\
                                                        }
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//----------------------------------------------------------------------------
// Macro of Dp Lane Valid Check
//----------------------------------------------------------------------------
#define GET_DP_RX1_SOURCE_TYPE_JUDGE()                  (g_bDpRx1SourceTypeJudge)
#define SET_DP_RX1_SOURCE_TYPE_JUDGE()                  (g_bDpRx1SourceTypeJudge = _TRUE)
#define CLR_DP_RX1_SOURCE_TYPE_JUDGE()                  (g_bDpRx1SourceTypeJudge = _FALSE)
#endif

//--------------------------------------------------
// Macro of DP Lane Mapping
//--------------------------------------------------
#define GET_DP_RX1_PCB_LANE0_MAPPING()                  (g_stDpRx1LanesMapping.b2Lane0Mapping)
#define SET_DP_RX1_PCB_LANE0_MAPPING(x)                 (g_stDpRx1LanesMapping.b2Lane0Mapping = (x))

#define GET_DP_RX1_PCB_LANE1_MAPPING()                  (g_stDpRx1LanesMapping.b2Lane1Mapping)
#define SET_DP_RX1_PCB_LANE1_MAPPING(x)                 (g_stDpRx1LanesMapping.b2Lane1Mapping = (x))

#define GET_DP_RX1_PCB_LANE2_MAPPING()                  (g_stDpRx1LanesMapping.b2Lane2Mapping)
#define SET_DP_RX1_PCB_LANE2_MAPPING(x)                 (g_stDpRx1LanesMapping.b2Lane2Mapping = (x))

#define GET_DP_RX1_PCB_LANE3_MAPPING()                  (g_stDpRx1LanesMapping.b2Lane3Mapping)
#define SET_DP_RX1_PCB_LANE3_MAPPING(x)                 (g_stDpRx1LanesMapping.b2Lane3Mapping = (x))

#define GET_DP_RX1_PCB_LANE0_PN_SWAP()                  (g_stDpRx1LanesMapping.b1Lane0PNSwap)
#define SET_DP_RX1_PCB_LANE0_PN_SWAP(x)                 (g_stDpRx1LanesMapping.b1Lane0PNSwap = (x))

#define GET_DP_RX1_PCB_LANE1_PN_SWAP()                  (g_stDpRx1LanesMapping.b1Lane1PNSwap)
#define SET_DP_RX1_PCB_LANE1_PN_SWAP(x)                 (g_stDpRx1LanesMapping.b1Lane1PNSwap = (x))

#define GET_DP_RX1_PCB_LANE2_PN_SWAP()                  (g_stDpRx1LanesMapping.b1Lane2PNSwap)
#define SET_DP_RX1_PCB_LANE2_PN_SWAP(x)                 (g_stDpRx1LanesMapping.b1Lane2PNSwap = (x))

#define GET_DP_RX1_PCB_LANE3_PN_SWAP()                  (g_stDpRx1LanesMapping.b1Lane3PNSwap)
#define SET_DP_RX1_PCB_LANE3_PN_SWAP(x)                 (g_stDpRx1LanesMapping.b1Lane3PNSwap = (x))

//----------------------------------------------------------------------------
// Macro of HDCP Information
//----------------------------------------------------------------------------
#define GET_DP_RX1_HDCP_MODE_BACKUP()                   (g_enumDpRx1HdcpMode)
#define SET_DP_RX1_HDCP_MODE_BACKUP(x)                  (g_enumDpRx1HdcpMode = (x))

#define GET_DP_RX1_HDCP_MODE()                          ((ScalerGetBit(PB_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

// HDCP mode register at power off region, set register and backup variable must at the same time.
#define SET_DP_RX1_HDCP_MODE(x)                         {\
                                                            if((x) == _HDCP_22)\
                                                            {\
                                                                ScalerSetBit(PB_1A_HDCP_IRQ, ~_BIT1, _BIT1);\
                                                                SET_DP_RX1_HDCP_MODE_BACKUP(_HDCP_22);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetBit(PB_1A_HDCP_IRQ, ~_BIT1, 0x00);\
                                                                SET_DP_RX1_HDCP_MODE_BACKUP(_HDCP_14);\
                                                            }\
                                                        }

#define GET_DP_RX1_HDCP_MODE_EXINT()                    ((ScalerGetBit_EXINT(PB_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

// HDCP mode register at power off region, set register and backup variable must at the same time.
#define SET_DP_RX1_HDCP_MODE_EXINT(x)                   {\
                                                            if((x) == _HDCP_22)\
                                                            {\
                                                                ScalerSetBit_EXINT(PB_1A_HDCP_IRQ, ~_BIT1, _BIT1);\
                                                                SET_DP_RX1_HDCP_MODE_BACKUP(_HDCP_22);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetBit_EXINT(PB_1A_HDCP_IRQ, ~_BIT1, 0x00);\
                                                                SET_DP_RX1_HDCP_MODE_BACKUP(_HDCP_14);\
                                                            }\
                                                        }

//--------------------------------------------------
// Definitions of DP Lane Setting Ralation to Actual Lane Mapping
//--------------------------------------------------
#define _D1_DP_LANE0                                    (GET_DP_RX1_PCB_LANE0_MAPPING())
#define _D1_DP_LANE1                                    (GET_DP_RX1_PCB_LANE1_MAPPING())
#define _D1_DP_LANE2                                    (GET_DP_RX1_PCB_LANE2_MAPPING())
#define _D1_DP_LANE3                                    (GET_DP_RX1_PCB_LANE3_MAPPING())

//--------------------------------------------------
// Macro of DP Lane Mapping
//--------------------------------------------------
#define GET_DP_RX1_LANE_MAPPING_MODE()                  (g_stDpRx1LanesMapping.b1LaneMappingMode)
#define SET_DP_RX1_LANE_MAPPING_MODE(x)                 (g_stDpRx1LanesMapping.b1LaneMappingMode = (x))

#define GET_DP_RX1_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx1MSAFailMacRsetCount)
#define ADD_DP_RX1_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx1MSAFailMacRsetCount++)
#define CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx1MSAFailMacRsetCount = 0)

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

#endif
#endif

//--------------------------------------------------
// Macro of Dp Measure Pop Up Action
//--------------------------------------------------
// Delay 5us for Wait Hw Update Period to Prevent MCU Get wrong value, Update Period is 3T, T = 1/14.318M or 1/27M
#define SET_DP_RX1_MEASURE_POP_UP()                     {\
                                                            ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                            DELAY_5US();\
                                                        }

//--------------------------------------------------
// Macro of Dp Rx Mac Assigned
//--------------------------------------------------
#define GET_REG_DP_RX1_MAC_ASSIGNED()                   ((ScalerGetBit(PB_00_HD_DP_SEL, (_BIT1 | _BIT0)) == _BIT1) ? _TRUE : _FALSE)
#define GET_REG_DP_RX1_MAC_ASSIGNED_EXINT()             ((ScalerGetBit_EXINT(PB_00_HD_DP_SEL, (_BIT1 | _BIT0)) == _BIT1) ? _TRUE : _FALSE)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bDpRx1PSAuxToggle;
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
extern bit g_bDpRx1SignaldetectINTHappened;
#endif

extern bit g_bDpRx1AuxCommandNoReply;

extern BYTE g_ucDpRx1LinkStatus01;
extern BYTE g_ucDpRx1LinkStatus23;
extern BYTE g_ucDpRx1LinkRequest01;
extern BYTE g_ucDpRx1LinkRequest23;
extern BYTE g_ucDpRx1Temp;
extern BYTE g_pucDpRx1Backup[3];
extern BYTE g_ucDpRx1Info;
extern BYTE g_ucDpRx1LinkRate;
extern BYTE g_ucDpRx1LaneCount;
extern BYTE g_ucDpRx1TrainingPatternSet;

extern BYTE g_ucDpRx1EQCRC;
extern WORD g_usDpRx1ClockTargetCount;
extern WORD g_usDpRx1ClockMeasureCount;
extern BYTE g_ucRx1AuxTemp;
extern BYTE g_ucRx1AuxTemp_EXINT;
extern WORD g_usDpRx1Vfrontporch;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
extern BYTE g_ucDpRx1FakeLTLaneCount;
extern BYTE g_ucDpRx1FakeLTLaneCountBackUp;
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern BYTE g_pucDPRx1Caps[3];
#endif

extern WORD g_pusDpRx1ClockCount[4];
extern WORD g_pusDpRx1ClockCount1[4];

extern BYTE g_ucDpRx1PhyCtsCtrl;
extern EnumHDCPType g_enumDpRx1HdcpMode;

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit g_bDpRx1SourceTypeJudge;
#endif

extern StructDpLanesMapping g_stDpRx1LanesMapping;

extern WORD g_pusDpRx1ClockCount[4];
extern WORD g_pusDpRx1ClockCount1[4];

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit g_bDpRx1VscSdpColorMode;

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern bit g_bDpRx1RSV1PacketDetecting;
#endif
#endif

extern BYTE g_ucDpRx1MSAFailMacRsetCount;
extern bit g_bDpRx1SourceRDErrorCount;
extern bit g_bDpRx1Tp1Initial;
extern BYTE g_ucDpRx1LTPatternSet;

#if(_DP_HDR10_SUPPORT == _ON)
extern BYTE g_pucDPRx1HDR10Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
extern BYTE g_pucDPRx1RSV0Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
extern StructDPInfoFrameRSV0Ctrl g_stDPRx1InfoFrameRSV0Ctrl;
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
extern StructDpLinkInfo g_stDpRx1LinkInfo;
#endif

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
extern BYTE g_ucDpRx1AuxModeBackup_EXINT;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx1AuxPowerOnInitial(void);
extern void ScalerDpRx1AuxIntInitial(void);
extern void ScalerDpRx1DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
extern void ScalerDpRx1ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
extern void ScalerDpRx1ChangeHdcpDpcdCapability(bit bEn);
extern void ScalerDpRx1MacInitial(void);
extern void ScalerDpRx1PhyInitial(void);
extern void ScalerDpRx1RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpRx1SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue);
extern bit ScalerDpRx1DecodeCheck(void);
extern bit ScalerDpRx1DisplayFormatSetting(void);
extern bit ScalerDpRx1StreamClkRegenerate(void);
extern bit ScalerDpRx1FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpRx1HDCPBlockReset(void);
extern void ScalerDpRx1HDCPUnplugReset(void);
extern bit ScalerDpRx1HdcpCheck(void);
extern bit ScalerDpRx1HdcpReAuthStatusCheck(void);
extern void ScalerDpRx1CpIRQ(EnumDpRxBStatusType enumBStatusType);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpRx1CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType);
#endif
extern bit ScalerDpRx1HdcpCheckValid(void);
extern bit ScalerDpRx1HdcpCheckEnabled(void);
extern void ScalerDpRx1PhyCTS(void);
extern void ScalerDpRx1SetFifoWD(bit bEn);
extern void ScalerDpRx1SetFifoIRQ(bit bEn);
extern bit ScalerDpRx1NormalPreDetect(void);
extern BYTE ScalerDpRx1ScanInputPort(void);
extern bit ScalerDpRx1StableDetect(void);

extern void ScalerDpRx1AdjustVsyncDelay(void);
extern bit ScalerDpRx1AlignCheck(void);
extern void ScalerDpRx1ScrambleSetting(void);

#if((_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON) && (_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON))
extern bit ScalerDpRx1LaneValidCheck(void);
#endif

extern void ScalerDpRx1CheckHdcpCpirqStatus(void);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
extern bit ScalerDpRx1CheckVgipVsBypass(void);
#endif

extern void ScalerDpRx1CrcCalculate(void);
#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
extern void ScalerDpRx1HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
#endif
extern void ScalerDpRx1SetNoVideoStreamIRQ(bit bEn);
extern void ScalerDpRx1DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);
extern DWORD ScalerDpRx1GetBStoVSDelay(void);
extern BYTE ScalerDpRx1GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern BYTE ScalerDpRx1GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern bit ScalerDpRx1GetVideoStream(void);
extern EnumDpHotPlugTime ScalerDpRx1BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType);
extern void ScalerDpRx1AfterHpdToggleProc(void);
extern void ScalerDpRx1CancelValidSignalDetectTimerEvent(void);

extern void ScalerDpRx1Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
extern bit ScalerDpRx1MarginLinkCheck(void);
extern void ScalerDpRx1LinkStatusIRQ(void);
extern void ScalerDpRx1AuxSet(void);
extern void ScalerDpRx1ErrorCounterUpdate_EXINT0(void);
extern void ScalerDpRx1ErrorCounterDisable_EXINT0(void);
extern void ScalerDpRx1ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType);

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerDpRx1DecodeErrorCountReset_WDINT(void);
#endif

extern bit ScalerDpRx1MSAActiveChange(void);
extern bit ScalerDpRx1PSPreDetect(void);
extern void ScalerDpRx1SecDataBlockReset(void);
extern void ScalerDpRx1SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpRx1SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpRx1SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);

#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
extern void ScalerDpRx1ASSRModeSetting(void);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDpRx1GetFREESYNCStatusChange(void);
extern void ScalerDpRx1SetFREESYNCMsaForLut(WORD usDpHtotal);
#endif

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

extern bit ScalerDpRx1MSACheck(void);
#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
extern bit ScalerDpRx1VbiosAssrCheck(bit bMSACheckResult);
#endif
extern void ScalerDpRx1FakeLTProtect(void);
extern void ScalerDpRx1SetInitialRSV0InfoType(void);
extern void ScalerDpRx1SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType);
extern void ScalerDpRx1HpdIrqAssert(void);

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_ULTRA_HDR_SUPPORT == _ON))
extern void ScalerDpRx1GetInfoFrameRSV0(BYTE *pucDPRx1RSV0Data);
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
extern void ScalerDpRx1InfoFrameRSV0Check(void);
extern void ScalerDpRx1RSV0PacketDetectEvent(void);
extern void ScalerDpRx1InfoFrameRSV0Initial(void);
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
extern bit ScalerDpRx1CheckHdcpCapability(void);
extern void ScalerDpRx1HdcpHandshakeMonitorEnable(void);
extern void ScalerDpRx1HdcpHandshakeMonitorDisable(void);
extern void ScalerDpRx1HdcpHandshakeMonitorDisable_EXINT0(void);
#endif
extern StructDpRxErrorCount ScalerDpRx1GetErrorCount(void);

#endif // End of #if(_D1_DP_EXIST == _ON)
