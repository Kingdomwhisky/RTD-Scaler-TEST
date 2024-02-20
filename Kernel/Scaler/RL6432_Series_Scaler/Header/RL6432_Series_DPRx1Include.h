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
// ID Code      : RL6432_Series_DPRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D1_DP_EXIST == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX1_AUX_COMMAND_NO_REPLY()               (g_bDpRx1AuxCommandNoReply)
#define SET_DP_RX1_AUX_COMMAND_NO_REPLY()               (g_bDpRx1AuxCommandNoReply = _TRUE)
#define CLR_DP_RX1_AUX_COMMAND_NO_REPLY()               (g_bDpRx1AuxCommandNoReply = _FALSE)

#define GET_DP_RX1_PHY_CTS_FLG()                        (!((bit)ScalerGetBit(P7A_25_KOFFSET_01, _BIT5)))
#define SET_DP_RX1_PHY_CTS_FLG()                        (ScalerSetBit(P7A_25_KOFFSET_01, ~_BIT5, 0x00))
#define CLR_DP_RX1_PHY_CTS_FLG()                        (ScalerSetBit(P7A_25_KOFFSET_01, ~_BIT5, _BIT5))

#define SET_DP_RX1_AUX_MANUAL_MODE_EXINT()              (ScalerSetBit_EXINT(PBA_D0_AUX_MODE_SET, ~_BIT1, 0x00))

#define SET_DP_RX1_AUX_MANUAL_MODE()                    {\
                                                            EX0 = 0;\
                                                            ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, 0x00);\
                                                            EX0 = 1;\
                                                        }


#define SET_DP_RX1_AUX_MANUAL_MODE_PHY_CTS()            (ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, 0x00))

#define SET_DP_RX1_AUX_AUTO_MODE_EXINT()                {\
                                                            ScalerSetBit_EXINT(PBA_D0_AUX_MODE_SET, ~_BIT4, 0x00);\
                                                            ScalerSetBit_EXINT(PBA_D0_AUX_MODE_SET, ~_BIT1, _BIT1);\
                                                        }

#define SET_DP_RX1_AUX_AUTO_MODE()                      {\
                                                            EX0 = 0;\
                                                            ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, _BIT1);\
                                                            EX0 = 1;\
                                                        }

#define SET_DP_RX1_AUX_AUTO_MODE_PHY_CTS()              (ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, _BIT1))

#define GET_DP_RX1_VFRONT_PORCH()                       (g_usDpRx1Vfrontporch)
#define SET_DP_RX1_VFRONT_PORCH(x)                      (g_usDpRx1Vfrontporch = (x))

#define SET_DP_RX1_PORCH_COLOR_RGB()                    {\
                                                            ScalerSetByte(PB8_51_MN_DPF_BG_RED_M, 0x00);\
                                                            ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                            ScalerSetByte(PB8_53_MN_DPF_BG_GRN_M, 0x00);\
                                                            ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                            ScalerSetByte(PB8_55_MN_DPF_BG_BLU_M, 0x00);\
                                                            ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                        }

#define SET_DP_RX1_PORCH_COLOR_YCC_LIMIT()              {\
                                                            if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                            {\
                                                                ScalerSetByte(PB8_51_MN_DPF_BG_RED_M, 0x10);\
                                                                ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB8_53_MN_DPF_BG_GRN_M, 0x10);\
                                                                ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB8_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetByte(PB8_51_MN_DPF_BG_RED_M, 0x80);\
                                                                ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB8_53_MN_DPF_BG_GRN_M, 0x10);\
                                                                ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB8_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                        }

#define SET_DP_RX1_PORCH_COLOR_YCC_FULL()               {\
                                                            if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                            {\
                                                                ScalerSetByte(PB8_51_MN_DPF_BG_RED_M, 0x10);\
                                                                ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB8_53_MN_DPF_BG_GRN_M, 0x10);\
                                                                ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB8_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetByte(PB8_51_MN_DPF_BG_RED_M, 0x80);\
                                                                ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB8_53_MN_DPF_BG_GRN_M, 0x00);\
                                                                ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB8_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                        }

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
#define SET_DP_RX1_INTERLACE_VTT_FW_MODE(x)             {\
                                                        }
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Macro of RX HDCP Authentication
//--------------------------------------------------
#define GET_DP_RX1_HDCP_AUTH_STATE()                    (g_stDpRx1HDCPAuthInfo.b4AuthState)
#define SET_DP_RX1_HDCP_AUTH_STATE(x)                   (g_stDpRx1HDCPAuthInfo.b4AuthState = (x))

#define GET_DP_RX1_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx1HDCPAuthInfo.b1AuthStateChange)
#define SET_DP_RX1_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx1HDCPAuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx1HDCPAuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx1HDCPAuthInfo.b1AuthRepeaterProcTimeout)
#define SET_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx1HDCPAuthInfo.b1AuthRepeaterProcTimeout = _TRUE)
#define CLR_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx1HDCPAuthInfo.b1AuthRepeaterProcTimeout = _FALSE)

#define GET_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx1HDCPAuthInfo.b1AuthReadIrqTimeout)
#define SET_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx1HDCPAuthInfo.b1AuthReadIrqTimeout = _TRUE)
#define CLR_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx1HDCPAuthInfo.b1AuthReadIrqTimeout = _FALSE)

#define GET_DP_RX1_HDCP_UPSTREAM_EVENT()                (g_stDpRx1HDCPAuthInfo.ucAuthUpstreamEvent)
#define SET_DP_RX1_HDCP_UPSTREAM_EVENT(x)               (g_stDpRx1HDCPAuthInfo.ucAuthUpstreamEvent = (x))
#define CLR_DP_RX1_HDCP_UPSTREAM_EVENT()                (g_stDpRx1HDCPAuthInfo.ucAuthUpstreamEvent = _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE)

#define GET_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx1HDCPAuthInfo.b1AuthCpIrqTimer)
#define SET_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx1HDCPAuthInfo.b1AuthCpIrqTimer = _TRUE)
#define CLR_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx1HDCPAuthInfo.b1AuthCpIrqTimer = _FALSE)

#define GET_DP_RX1_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx1HdcpAksvWritten)
#define SET_DP_RX1_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx1HdcpAksvWritten = _TRUE)
#define CLR_DP_RX1_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx1HdcpAksvWritten = _FALSE)

#define GET_DP_RX1_HDCP_REPEATER_SUPPORT()              ((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x28) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))

#define GET_DP_RX1_HDCP_M0_0()                          (ScalerGetByte(PB0_2F_M0_BYTE_0))
#define GET_DP_RX1_HDCP_M0_1()                          (ScalerGetByte(PB0_2E_M0_BYTE_1))
#define GET_DP_RX1_HDCP_M0_2()                          (ScalerGetByte(PB0_2D_M0_BYTE_2))
#define GET_DP_RX1_HDCP_M0_3()                          (ScalerGetByte(PB0_2C_M0_BYTE_3))
#define GET_DP_RX1_HDCP_M0_4()                          (ScalerGetByte(PB0_2B_M0_BYTE_4))
#define GET_DP_RX1_HDCP_M0_5()                          (ScalerGetByte(PB0_2A_M0_BYTE_5))
#define GET_DP_RX1_HDCP_M0_6()                          (ScalerGetByte(PB0_29_M0_BYTE_6))
#define GET_DP_RX1_HDCP_M0_7()                          (ScalerGetByte(PB0_28_M0_BYTE_7))
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bDpRx1PSAuxToggle;

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
extern BYTE g_ucDpRx1AuxAddressBackup;

extern BYTE g_pucDpRx1LEBound[4];
extern BYTE g_pucDpRx1Tap1MinTemp[4];
extern BYTE g_pucDpRx1Tap1Max[4];
extern BYTE g_pucDpRx1LEMinTemp[4];
extern BYTE g_pucDpRx1LEMax[4];
extern BYTE g_ucDpRx1EQCRC;
extern BYTE g_ucRx1AuxTemp;
extern BYTE g_ucRx1AuxTemp_EXINT;
extern WORD g_usDpRx1Vfrontporch;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
extern BYTE g_ucDpRx1FakeLTLaneCount;
extern BYTE g_ucDpRx1FakeLTLaneCountBackUp;
#endif

#if(_DP_TX_SUPPORT == _ON)
extern bit g_bDpRx1HdcpAksvWritten;
extern WORD g_usDpRx1HdcpKsvFifoOffset;
extern StructDPRxHDCPAuthInfo g_stDpRx1HDCPAuthInfo;
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern BYTE g_pucDPRx1Caps[3];
#endif

extern WORD g_pusDpRx1ClockCount[4];
extern WORD g_pusDpRx1ClockCount1[4];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx1AuxPowerOnInitial(void);
extern void ScalerDpRx1AuxIntInitial(void);
extern void ScalerDpRx1DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
extern void ScalerDpRx1ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
extern void ScalerDpRx1RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpRx1SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue);
extern bit ScalerDpRx1StreamClkRegenerate(void);
extern bit ScalerDpRx1HdcpCheck(void);
extern void ScalerDpRx1PhyCTS(void);

#if(_DP_MST_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpRx1MstToSstStreamClkRegenerate(void);
#endif
#endif

#endif // End of #if(_D1_DP_EXIST == _ON)


