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
// ID Code      : ScalerDPRx0_SeptPhyInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_D0_DP_EXIST == _ON)

//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX0_FAKE_LINK_TRAINING()                 ((g_ucDpRx0Info & _BIT7) >> 7)
#define SET_DP_RX0_FAKE_LINK_TRAINING()                 (g_ucDpRx0Info |= _BIT7)
#define CLR_DP_RX0_FAKE_LINK_TRAINING()                 (g_ucDpRx0Info &= ~_BIT7)

#define GET_DP_RX0_VALID_VIDEO_CHECK()                  ((g_ucDpRx0Info & _BIT6) >> 6)
#define SET_DP_RX0_VALID_VIDEO_CHECK()                  (g_ucDpRx0Info |= _BIT6)
#define CLR_DP_RX0_VALID_VIDEO_CHECK()                  {\
                                                            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);\
                                                            (g_ucDpRx0Info &= ~_BIT6);\
                                                        }

#define GET_DP_RX0_CRC_CALCULATE()                      ((g_ucDpRx0Info & _BIT5) >> 5)
#define SET_DP_RX0_CRC_CALCULATE()                      (g_ucDpRx0Info |= _BIT5)
#define CLR_DP_RX0_CRC_CALCULATE()                      (g_ucDpRx0Info &= ~_BIT5)

#define GET_DP_RX0_PS_AUX_TOGGLE()                      (g_bDpRx0PSAuxToggle)
#define SET_DP_RX0_PS_AUX_TOGGLE()                      (g_bDpRx0PSAuxToggle = _TRUE)
#define CLR_DP_RX0_PS_AUX_TOGGLE()                      (g_bDpRx0PSAuxToggle = _FALSE)

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//----------------------------------------------------------------------------
// Macro of Dp Lane Valid Check
//----------------------------------------------------------------------------
#define GET_DP_RX0_SOURCE_TYPE_JUDGE()                  (g_bDpRx0SourceTypeJudge)
#define SET_DP_RX0_SOURCE_TYPE_JUDGE()                  (g_bDpRx0SourceTypeJudge = _TRUE)
#define CLR_DP_RX0_SOURCE_TYPE_JUDGE()                  (g_bDpRx0SourceTypeJudge = _FALSE)
#endif

//--------------------------------------------------
// Macro of DP Lane Mapping
//--------------------------------------------------
#define GET_DP_RX0_PCB_LANE0_MAPPING()                  (g_stDpRx0LanesMapping.b2Lane0Mapping)
#define SET_DP_RX0_PCB_LANE0_MAPPING(x)                 (g_stDpRx0LanesMapping.b2Lane0Mapping = (x))

#define GET_DP_RX0_PCB_LANE1_MAPPING()                  (g_stDpRx0LanesMapping.b2Lane1Mapping)
#define SET_DP_RX0_PCB_LANE1_MAPPING(x)                 (g_stDpRx0LanesMapping.b2Lane1Mapping = (x))

#define GET_DP_RX0_PCB_LANE2_MAPPING()                  (g_stDpRx0LanesMapping.b2Lane2Mapping)
#define SET_DP_RX0_PCB_LANE2_MAPPING(x)                 (g_stDpRx0LanesMapping.b2Lane2Mapping = (x))

#define GET_DP_RX0_PCB_LANE3_MAPPING()                  (g_stDpRx0LanesMapping.b2Lane3Mapping)
#define SET_DP_RX0_PCB_LANE3_MAPPING(x)                 (g_stDpRx0LanesMapping.b2Lane3Mapping = (x))

#define GET_DP_RX0_PCB_LANE0_PN_SWAP()                  (g_stDpRx0LanesMapping.b1Lane0PNSwap)
#define SET_DP_RX0_PCB_LANE0_PN_SWAP(x)                 (g_stDpRx0LanesMapping.b1Lane0PNSwap = (x))

#define GET_DP_RX0_PCB_LANE1_PN_SWAP()                  (g_stDpRx0LanesMapping.b1Lane1PNSwap)
#define SET_DP_RX0_PCB_LANE1_PN_SWAP(x)                 (g_stDpRx0LanesMapping.b1Lane1PNSwap = (x))

#define GET_DP_RX0_PCB_LANE2_PN_SWAP()                  (g_stDpRx0LanesMapping.b1Lane2PNSwap)
#define SET_DP_RX0_PCB_LANE2_PN_SWAP(x)                 (g_stDpRx0LanesMapping.b1Lane2PNSwap = (x))

#define GET_DP_RX0_PCB_LANE3_PN_SWAP()                  (g_stDpRx0LanesMapping.b1Lane3PNSwap)
#define SET_DP_RX0_PCB_LANE3_PN_SWAP(x)                 (g_stDpRx0LanesMapping.b1Lane3PNSwap = (x))

//----------------------------------------------------------------------------
// Macro of HDCP Information
//----------------------------------------------------------------------------
#define GET_DP_RX0_HDCP_MODE_BACKUP()                   (g_enumDpRx0HdcpMode)
#define SET_DP_RX0_HDCP_MODE_BACKUP(x)                  (g_enumDpRx0HdcpMode = (x))

#define GET_DP_RX0_HDCP_MODE()                          ((ScalerGetBit(PB_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

// HDCP mode register at power off region, set register and backup variable must at the same time.
#define SET_DP_RX0_HDCP_MODE(x)                         {\
                                                            if((x) == _HDCP_22)\
                                                            {\
                                                                ScalerSetBit(PB_1A_HDCP_IRQ, ~_BIT1, _BIT1);\
                                                                SET_DP_RX0_HDCP_MODE_BACKUP(_HDCP_22);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetBit(PB_1A_HDCP_IRQ, ~_BIT1, 0x00);\
                                                                SET_DP_RX0_HDCP_MODE_BACKUP(_HDCP_14);\
                                                            }\
                                                        }

#define GET_DP_RX0_HDCP_MODE_EXINT()                    ((ScalerGetBit_EXINT(PB_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

// HDCP mode register at power off region, set register and backup variable must at the same time.
#define SET_DP_RX0_HDCP_MODE_EXINT(x)                   {\
                                                            if((x) == _HDCP_22)\
                                                            {\
                                                                ScalerSetBit_EXINT(PB_1A_HDCP_IRQ, ~_BIT1, _BIT1);\
                                                                SET_DP_RX0_HDCP_MODE_BACKUP(_HDCP_22);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetBit_EXINT(PB_1A_HDCP_IRQ, ~_BIT1, 0x00);\
                                                                SET_DP_RX0_HDCP_MODE_BACKUP(_HDCP_14);\
                                                            }\
                                                        }

//--------------------------------------------------
// Definitions of DP Lane Setting Ralation to Actual Lane Mapping
//--------------------------------------------------
#define _D0_DP_LANE0                                    (GET_DP_RX0_PCB_LANE0_MAPPING())
#define _D0_DP_LANE1                                    (GET_DP_RX0_PCB_LANE1_MAPPING())
#define _D0_DP_LANE2                                    (GET_DP_RX0_PCB_LANE2_MAPPING())
#define _D0_DP_LANE3                                    (GET_DP_RX0_PCB_LANE3_MAPPING())

#if(_DP_MST_SUPPORT == _ON)
#define GET_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx0MiscInfo.b1DpCheckAuxChNoPowerDebounce)
#define SET_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx0MiscInfo.b1DpCheckAuxChNoPowerDebounce = _TRUE)
#define CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx0MiscInfo.b1DpCheckAuxChNoPowerDebounce = _FALSE)

#define GET_DP_RX0_CHECK_AUX_CH_POWER_STATUS()          (g_stDpRx0MiscInfo.b2DpCheckAuxChPowerStatus)
#define SET_DP_RX0_CHECK_AUX_CH_POWER_STATUS(x)         (g_stDpRx0MiscInfo.b2DpCheckAuxChPowerStatus = (x))
#define CLR_DP_RX0_CHECK_AUX_CH_POWER_STATUS()          (g_stDpRx0MiscInfo.b2DpCheckAuxChPowerStatus = _DP_RX_AUX_POWER_STATUS_NONE)

#define GET_DP_RX0_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx0MiscInfo.b1DpAuxChPowerOnWakeUp)
#define SET_DP_RX0_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx0MiscInfo.b1DpAuxChPowerOnWakeUp = _TRUE)
#define CLR_DP_RX0_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx0MiscInfo.b1DpAuxChPowerOnWakeUp = _FALSE)

#define GET_DP_RX0_SOURCE_FIRST_POWER_ON()              (g_stDpRx0MiscInfo.b1DpSourceFirstPowerOn)
#define SET_DP_RX0_SOURCE_FIRST_POWER_ON()              (g_stDpRx0MiscInfo.b1DpSourceFirstPowerOn = _TRUE)
#define CLR_DP_RX0_SOURCE_FIRST_POWER_ON()              (g_stDpRx0MiscInfo.b1DpSourceFirstPowerOn = _FALSE)

#define GET_DP_RX0_SOURCE_WRITE_POWER_UP()              (g_stDpRx0MiscInfo.enumDpSourceWritePowerUp)
#define SET_DP_RX0_SOURCE_WRITE_POWER_UP(x)             (g_stDpRx0MiscInfo.enumDpSourceWritePowerUp = (x))
#define CLR_DP_RX0_SOURCE_WRITE_POWER_UP()              (g_stDpRx0MiscInfo.enumDpSourceWritePowerUp = _DP_SOURCE_WRITE_POWER_UP_NONE)
#endif // #if(_DP_MST_SUPPORT == _ON)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_D0_DP_EXIST == _ON)
extern BYTE g_ucDpRx0PhyCtsCtrl;
extern EnumHDCPType g_enumDpRx0HdcpMode;
extern StructDpLanesMapping g_stDpRx0LanesMapping;

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit g_bDpRx0SourceTypeJudge;
#endif

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT != _ON)
extern BYTE g_ucDpRx0DPCD02200hValue;
extern BYTE g_ucDpRx0DPCD02201hValue;
extern BYTE g_ucDpRx0DPCD02210hValue;
#endif

#if(_DP_MST_SUPPORT == _ON)
extern StructDPRxMiscInfo g_stDpRx0MiscInfo;
extern BYTE g_pucDpRx0MstTimeSlotBackup[13];
#endif

#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_D0_DP_EXIST == _ON)
extern void ScalerDpRx0AdjustVsyncDelay(void);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
extern bit ScalerDpRx0CheckVgipVsBypass(void);
#endif

extern void ScalerDpRx0SetNoVideoStreamIRQ(bit bEn);
extern void ScalerDpRx0DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);
extern DWORD ScalerDpRx0GetBStoVSDelay(void);
extern void ScalerDpRx0Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
extern bit ScalerDpRx0MarginLinkCheck(void);
extern void ScalerDpRx0LinkStatusIRQ(void);
extern void ScalerDpRx0AuxSet(void);
extern void ScalerDpRx0HpdIrqAssert(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpRx0CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType);
#endif
extern EnumDpHotPlugTime ScalerDpRx0BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType);
extern void ScalerDpRx0AfterHpdToggleProc(void);
extern bit ScalerDpRx0ChangeSrambleSeed(void);

#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)
extern bit ScalerDpRx0VbiosAssrCheck(bit bMSACheckResult);
#endif
extern bit ScalerDpRx0PSPreDetect(void);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
extern void ScalerDpRx6Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpRx0MstInfoBackup(EnumDpMstBackup enumDpMstBackup);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
extern bit ScalerDpRx6AuxChSourcePowerCheck(void);
extern void ScalerDpRx6AuxChPowerStatusCheck(bit bCableStatus);
extern void ScalerDpRx6MstInfoBackup(EnumDpMstBackup enumDpMstBackup);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx0HDCPAuthShaRun(bit bIsFirst);

extern void ScalerDpRx0HDCPChangeAuthState(EnumDPRxHDCPAuthState enumHDCPAuthState);
extern bit ScalerDpRx0HDCPCheckLvp(void);
extern void ScalerDpRx0HDCPHandler(void);
extern void ScalerDpRx0HDCPSetReadIrqTimeout(void);
extern void ScalerDpRx0HDCPSetRepeaterProcTimeout(void);
extern DWORD ScalerDpRx0MstToSstGetBStoVSDelay(void);
extern void ScalerDpRx0MstToSstProc(void);

#if(_DP_FREESYNC_SUPPORT == _ON)
extern WORD ScalerDpRx0MstToSstGetBStoHSDelay(WORD usDpHtotal);
#endif

extern void ScalerDpRx0DfpDeviceDetailConfigReset(void);
extern void ScalerDpRx0DfpDeviceDetailConfig(void);
#endif

#endif

extern void ScalerDpRx0AdjustLaneFLDBand(BYTE ucDpRx0LaneNumber, WORD usVCOBandDiff);
extern bit ScalerDpRx0CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpRx0CpIRQ(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpRx0DFECheck(void);
extern bit ScalerDpRx0AlignCheck(void);
extern bit ScalerDpRx0DecodeCheck(void);
extern bit ScalerDpRx0DisplayFormatSetting(void);
extern bit ScalerDpRx0FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpRx0HDCPBlockReset(void);
extern bit ScalerDpRx0HdcpCheckValid(void);
extern bit ScalerDpRx0HdcpCheckEnabled(void);
extern bit ScalerDpRx0HdcpMeasureCheck(void);
extern bit ScalerDpRx0HdcpReAuthStatusCheck(void);
extern void ScalerDpRx0MacInitial(void);
extern bit ScalerDpRx0PhyCtsTp1Check(void);
extern bit ScalerDpRx0PhyCtsTp2Check(void);
extern void ScalerDpRx0PhyInitial(void);
extern BYTE ScalerDpRx0ScanInputPort(void);
extern void ScalerDpRx0SetDFEInitial(EnumDpLinkRate enumDpLinkRate);
extern void ScalerDpRx0SetFifoIRQ(bit bEn);
extern void ScalerDpRx0SetFifoWD(bit bEn);
extern bit ScalerDpRx0StableDetect(void);
extern void ScalerDpRx0SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType);

#if(_DP_MST_SUPPORT == _ON)
extern bit ScalerDpRx0LTStatusCheck(void);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx0HDCPEnableReadIrq(bit bEnable);
extern bit ScalerDpRx0MstToSstDisplayFormatSetting(void);
extern bit ScalerDpRx0MstToSstFifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern bit ScalerDpRx0MstToSstMeasureInput(void);
#endif

#endif
extern StructDpRxErrorCount ScalerDpRx0GetErrorCount(void);

#endif
