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
// ID Code      : RL6463_Series_DPRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX0_PHY_CTS_FLG()                        ((bit)ScalerGetBit(PB_BD_CMU_00, _BIT0))
#define SET_DP_RX0_PHY_CTS_FLG()                        (ScalerSetBit(PB_BD_CMU_00, ~_BIT0, _BIT0))
#define CLR_DP_RX0_PHY_CTS_FLG()                        (ScalerSetBit(PB_BD_CMU_00, ~_BIT0, 0x00))

#define SET_DP_RX0_AUX_MANUAL_MODE_EXINT()              (ScalerSetBit_EXINT(PB7_D0_AUX_MODE_SET, ~_BIT1, 0x00))

#define SET_DP_RX0_AUX_MANUAL_MODE()                    {\
                                                            EX0 = 0;\
                                                            ScalerSetBit(PB7_D0_AUX_MODE_SET, ~_BIT1, 0x00);\
                                                            EX0 = 1;\
                                                        }

#define SET_DP_RX0_AUX_MANUAL_MODE_PHY_CTS()            (ScalerSetBit(PB7_D0_AUX_MODE_SET, ~_BIT1, 0x00))

#define SET_DP_RX0_AUX_AUTO_MODE_EXINT()                (ScalerSetBit_EXINT(PB7_D0_AUX_MODE_SET, ~_BIT1, _BIT1))

#define SET_DP_RX0_AUX_AUTO_MODE()                      {\
                                                            EX0 = 0;\
                                                            ScalerSetBit(PB7_D0_AUX_MODE_SET, ~_BIT1, _BIT1);\
                                                            EX0 = 1;\
                                                        }

#define SET_DP_RX0_AUX_AUTO_MODE_PHY_CTS()              (ScalerSetBit(PB7_D0_AUX_MODE_SET, ~_BIT1, _BIT1))

#define GET_DP_RX0_VFRONT_PORCH()                       (g_usDpRx0Vfrontporch)
#define SET_DP_RX0_VFRONT_PORCH(x)                      (g_usDpRx0Vfrontporch = (x))

#define SET_DP_RX0_PORCH_COLOR_RGB()                    {\
                                                            ScalerSetBit(PB5_51_MN_DPF_BG_MODE_SEL, ~_BIT0, 0x00);\
                                                        }

#define SET_DP_RX0_PORCH_COLOR_YCC_LIMIT()              {\
                                                            ScalerSetBit(PB5_51_MN_DPF_BG_MODE_SEL, ~_BIT0, _BIT0);\
                                                        }

#define SET_DP_RX0_PORCH_COLOR_YCC_FULL()               {\
                                                            ScalerSetBit(PB5_51_MN_DPF_BG_MODE_SEL, ~_BIT0, _BIT0);\
                                                        }

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
#define SET_DP_RX0_INTERLACE_VTT_FW_MODE(x)             {\
                                                            (((x) == _EVEN) ? (ScalerSetBit(PB5_F1_DP_RSV1, ~_BIT4, _BIT4)) : (ScalerSetBit(PB5_F1_DP_RSV1, ~_BIT4, 0x00)));\
                                                        }
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bDpRx0PSAuxToggle;

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
extern WORD g_usDpRx0ClockTargetCount;
extern WORD g_usDpRx0ClockMeasureCount;
extern BYTE g_ucRx0AuxTemp;
extern BYTE g_ucRx0AuxTemp_EXINT;
extern WORD g_usDpRx0Vfrontporch;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
extern BYTE g_ucDpRx0FakeLTLaneCount;
extern BYTE g_ucDpRx0FakeLTLaneCountBackUp;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx0AuxPowerOnInitial(void);
extern void ScalerDpRx0AuxIntInitial(void);
extern void ScalerDpRx0DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
extern void ScalerDpRx0MacInitial(void);
extern void ScalerDpRx0PhyInitial(void);
extern void ScalerDpRx0RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpRx0PassiveDFEFineTune(void);
extern bit ScalerDpRx0CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpRx0SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue);
extern bit ScalerDpRx0DisplayFormatSetting(void);

extern bit ScalerDpRx0StreamClkRegenerate(void);
extern void ScalerDpRx0AdjustVsyncDelay(void);
extern bit ScalerDpRx0HdcpMeasureCheck(void);
extern void ScalerDpRx0PhyCTS(void);
extern bit ScalerDpRx0NormalPreDetect(void);
extern BYTE ScalerDpRx0ScanInputPort(void);
extern bit ScalerDpRx0StableDetect(void);
extern void ScalerDpRx0SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType);

#if(_DP_RX_ACTIVE_REDUCE_LANE_COUNT_SUPPORT == _ON)
extern void ScalerDpRx0MainLinkQualityManagement(BYTE ucInputPort);
#endif

extern StructDpRxErrorCount ScalerDpRx0GetErrorCount(void);

