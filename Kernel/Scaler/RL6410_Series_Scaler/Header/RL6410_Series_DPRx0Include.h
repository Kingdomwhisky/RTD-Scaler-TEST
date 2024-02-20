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
// ID Code      : RL6410_Series_DPRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D0_DP_EXIST == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX0_AUX_COMMAND_NO_REPLY()               (g_bDpRx0AuxCommandNoReply)
#define SET_DP_RX0_AUX_COMMAND_NO_REPLY()               (g_bDpRx0AuxCommandNoReply = _TRUE)
#define CLR_DP_RX0_AUX_COMMAND_NO_REPLY()               (g_bDpRx0AuxCommandNoReply = _FALSE)

#define GET_DP_RX0_PHY_CTS_FLG()                        (!((bit)ScalerGetBit(P1D_25_KOFFSET_01, _BIT5)))
#define SET_DP_RX0_PHY_CTS_FLG()                        (ScalerSetBit(P1D_25_KOFFSET_01, ~_BIT5, 0x00))
#define CLR_DP_RX0_PHY_CTS_FLG()                        (ScalerSetBit(P1D_25_KOFFSET_01, ~_BIT5, _BIT5))

#define SET_DP_RX0_AUX_MANUAL_MODE_EXINT()              (ScalerSetBit_EXINT(PB7_D0_AUX_MODE_SET, ~_BIT1, 0x00))

#define SET_DP_RX0_AUX_MANUAL_MODE()                    {\
                                                            EX0 = 0;\
                                                            ScalerSetBit(PB7_D0_AUX_MODE_SET, ~_BIT1, 0x00);\
                                                            EX0 = 1;\
                                                        }

#define SET_DP_RX0_AUX_MANUAL_MODE_PHY_CTS()            (ScalerSetBit(PB7_D0_AUX_MODE_SET, ~_BIT1, 0x00))

#define SET_DP_RX0_AUX_AUTO_MODE_EXINT()                {\
                                                            ScalerSetBit_EXINT(PB7_D0_AUX_MODE_SET, ~_BIT4, 0x00);\
                                                            ScalerSetBit_EXINT(PB7_D0_AUX_MODE_SET, ~_BIT1, _BIT1);\
                                                        }

#define SET_DP_RX0_AUX_AUTO_MODE()                      {\
                                                            EX0 = 0;\
                                                            ScalerSetBit(PB7_D0_AUX_MODE_SET, ~_BIT1, _BIT1);\
                                                            EX0 = 1;\
                                                        }

#define SET_DP_RX0_AUX_AUTO_MODE_PHY_CTS()              (ScalerSetBit(PB7_D0_AUX_MODE_SET, ~_BIT1, _BIT1))

#define GET_DP_RX0_VFRONT_PORCH()                       (g_usDpRx0Vfrontporch)
#define SET_DP_RX0_VFRONT_PORCH(x)                      (g_usDpRx0Vfrontporch = (x))

#define SET_DP_RX0_PORCH_COLOR_RGB()                    {\
                                                            ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x00);\
                                                            ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                            ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x00);\
                                                            ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                            ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x00);\
                                                            ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                        }

#define SET_DP_RX0_PORCH_COLOR_YCC_LIMIT()              {\
                                                            if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x10);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x10);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x80);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x10);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                        }

#define SET_DP_RX0_PORCH_COLOR_YCC_FULL()               {\
                                                            if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x10);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x10);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x80);\
                                                                ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x00);\
                                                                ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                        }

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
#define SET_DP_RX0_INTERLACE_VTT_FW_MODE(x)             {\
                                                        }
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Macro of RX HDCP Authentication
//--------------------------------------------------
#define GET_DP_RX0_HDCP_AUTH_STATE()                    (g_stDpRx0HDCPAuthInfo.b4AuthState)
#define SET_DP_RX0_HDCP_AUTH_STATE(x)                   (g_stDpRx0HDCPAuthInfo.b4AuthState = (x))

#define GET_DP_RX0_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx0HDCPAuthInfo.b1AuthStateChange)
#define SET_DP_RX0_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx0HDCPAuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_RX0_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx0HDCPAuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_RX0_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx0HDCPAuthInfo.b1AuthRepeaterProcTimeout)
#define SET_DP_RX0_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx0HDCPAuthInfo.b1AuthRepeaterProcTimeout = _TRUE)
#define CLR_DP_RX0_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx0HDCPAuthInfo.b1AuthRepeaterProcTimeout = _FALSE)

#define GET_DP_RX0_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx0HDCPAuthInfo.b1AuthReadIrqTimeout)
#define SET_DP_RX0_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx0HDCPAuthInfo.b1AuthReadIrqTimeout = _TRUE)
#define CLR_DP_RX0_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx0HDCPAuthInfo.b1AuthReadIrqTimeout = _FALSE)

#define GET_DP_RX0_HDCP_UPSTREAM_EVENT()                (g_stDpRx0HDCPAuthInfo.ucAuthUpstreamEvent)
#define SET_DP_RX0_HDCP_UPSTREAM_EVENT(x)               (g_stDpRx0HDCPAuthInfo.ucAuthUpstreamEvent = (x))
#define CLR_DP_RX0_HDCP_UPSTREAM_EVENT()                (g_stDpRx0HDCPAuthInfo.ucAuthUpstreamEvent = _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE)

#define GET_DP_RX0_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx0HDCPAuthInfo.b1AuthCpIrqTimer)
#define SET_DP_RX0_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx0HDCPAuthInfo.b1AuthCpIrqTimer = _TRUE)
#define CLR_DP_RX0_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx0HDCPAuthInfo.b1AuthCpIrqTimer = _FALSE)

#define GET_DP_RX0_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx0HdcpAksvWritten)
#define SET_DP_RX0_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx0HdcpAksvWritten = _TRUE)
#define CLR_DP_RX0_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx0HdcpAksvWritten = _FALSE)

#define GET_DP_RX0_HDCP_REPEATER_SUPPORT()              ((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x28) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))

#define GET_DP_RX0_HDCP_M0_0()                          (ScalerGetByte(PB_2F_M0_BYTE_0))
#define GET_DP_RX0_HDCP_M0_1()                          (ScalerGetByte(PB_2E_M0_BYTE_1))
#define GET_DP_RX0_HDCP_M0_2()                          (ScalerGetByte(PB_2D_M0_BYTE_2))
#define GET_DP_RX0_HDCP_M0_3()                          (ScalerGetByte(PB_2C_M0_BYTE_3))
#define GET_DP_RX0_HDCP_M0_4()                          (ScalerGetByte(PB_2B_M0_BYTE_4))
#define GET_DP_RX0_HDCP_M0_5()                          (ScalerGetByte(PB_2A_M0_BYTE_5))
#define GET_DP_RX0_HDCP_M0_6()                          (ScalerGetByte(PB_29_M0_BYTE_6))
#define GET_DP_RX0_HDCP_M0_7()                          (ScalerGetByte(PB_28_M0_BYTE_7))
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bDpRx0PSAuxToggle;

extern bit g_bDpRx0AuxCommandNoReply;

extern BYTE g_ucDpRx0LinkStatus01;
extern BYTE g_ucDpRx0LinkStatus23;
extern BYTE g_ucDpRx0LinkRequest01;
extern BYTE g_ucDpRx0LinkRequest23;
extern BYTE g_ucDpRx0Temp;
extern BYTE g_pucDpRx0Backup[3];
extern BYTE g_ucDpRx0Info;
extern BYTE g_ucDpRx0LinkRate;
extern BYTE g_ucDpRx0LaneCount;
extern BYTE g_ucDpRx0TrainingPatternSet;
extern BYTE g_ucDpRx0AuxAddressBackup;

extern BYTE g_pucDpRx0LEBound[4];
extern BYTE g_pucDpRx0Tap1MinTemp[4];
extern BYTE g_pucDpRx0Tap1Max[4];
extern BYTE g_pucDpRx0LEMinTemp[4];
extern BYTE g_pucDpRx0LEMax[4];
extern BYTE g_ucDpRx0EQCRC;
extern WORD g_pusDpRx0ClockCount[4];
extern WORD g_pusDpRx0ClockCount1[4];
extern BYTE g_ucRx0AuxTemp;
extern BYTE g_ucRx0AuxTemp_EXINT;
extern WORD g_usDpRx0Vfrontporch;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
extern BYTE g_ucDpRx0FakeLTLaneCount;
extern BYTE g_ucDpRx0FakeLTLaneCountBackUp;
#endif

#if(_DP_MST_SUPPORT == _ON)
extern StructDPRxMiscInfo g_stDpRx0MiscInfo;
#endif

#if(_DP_TX_SUPPORT == _ON)
extern bit g_bDpRx0HdcpAksvWritten;
extern WORD g_usDpRx0HdcpKsvFifoOffset;
extern StructDPRxHDCPAuthInfo g_stDpRx0HDCPAuthInfo;
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern BYTE g_pucDPRx0Caps[3];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx0AuxPowerOnInitial(void);
extern void ScalerDpRx0AuxIntInitial(void);
extern void ScalerDpRx0DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
extern void ScalerDpRx0ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
extern void ScalerDpRx0RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpRx0SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue);
extern bit ScalerDpRx0StreamClkRegenerate(void);
extern bit ScalerDpRx0HdcpCheck(void);
extern void ScalerDpRx0PhyCTS(void);
extern bit ScalerDpRx0NormalPreDetect(void);

#if(_DP_MST_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpRx0MstToSstStreamClkRegenerate(void);
#endif
#endif

#endif // End of #if(_D0_DP_EXIST == _ON)
