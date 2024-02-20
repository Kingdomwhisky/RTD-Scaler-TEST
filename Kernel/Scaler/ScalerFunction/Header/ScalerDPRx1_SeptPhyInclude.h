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
// ID Code      : ScalerDPRx1_SeptPhyInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_D1_DP_EXIST == _ON)
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

#define GET_DP_RX1_HDCP_MODE()                          ((ScalerGetBit(PB0_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

// HDCP mode register at power off region, set register and backup variable must at the same time.
#define SET_DP_RX1_HDCP_MODE(x)                         {\
                                                            if((x) == _HDCP_22)\
                                                            {\
                                                                ScalerSetBit(PB0_1A_HDCP_IRQ, ~_BIT1, _BIT1);\
                                                                SET_DP_RX1_HDCP_MODE_BACKUP(_HDCP_22);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetBit(PB0_1A_HDCP_IRQ, ~_BIT1, 0x00);\
                                                                SET_DP_RX1_HDCP_MODE_BACKUP(_HDCP_14);\
                                                            }\
                                                        }

#define GET_DP_RX1_HDCP_MODE_EXINT()                    ((ScalerGetBit_EXINT(PB0_1A_HDCP_IRQ, _BIT1) == _BIT1) ? _HDCP_22 : _HDCP_14)

// HDCP mode register at power off region, set register and backup variable must at the same time.
#define SET_DP_RX1_HDCP_MODE_EXINT(x)                   {\
                                                            if((x) == _HDCP_22)\
                                                            {\
                                                                ScalerSetBit_EXINT(PB0_1A_HDCP_IRQ, ~_BIT1, _BIT1);\
                                                                SET_DP_RX1_HDCP_MODE_BACKUP(_HDCP_22);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetBit_EXINT(PB0_1A_HDCP_IRQ, ~_BIT1, 0x00);\
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

#if(_DP_MST_SUPPORT == _ON)
#define GET_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx1MiscInfo.b1DpCheckAuxChNoPowerDebounce)
#define SET_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx1MiscInfo.b1DpCheckAuxChNoPowerDebounce = _TRUE)
#define CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx1MiscInfo.b1DpCheckAuxChNoPowerDebounce = _FALSE)

#define GET_DP_RX1_CHECK_AUX_CH_POWER_STATUS()          (g_stDpRx1MiscInfo.b2DpCheckAuxChPowerStatus)
#define SET_DP_RX1_CHECK_AUX_CH_POWER_STATUS(x)         (g_stDpRx1MiscInfo.b2DpCheckAuxChPowerStatus = (x))
#define CLR_DP_RX1_CHECK_AUX_CH_POWER_STATUS()          (g_stDpRx1MiscInfo.b2DpCheckAuxChPowerStatus = _DP_RX_AUX_POWER_STATUS_NONE)

#define GET_DP_RX1_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx1MiscInfo.b1DpAuxChPowerOnWakeUp)
#define SET_DP_RX1_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx1MiscInfo.b1DpAuxChPowerOnWakeUp = _TRUE)
#define CLR_DP_RX1_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx1MiscInfo.b1DpAuxChPowerOnWakeUp = _FALSE)

#define GET_DP_RX1_SOURCE_FIRST_POWER_ON()              (g_stDpRx1MiscInfo.b1DpSourceFirstPowerOn)
#define SET_DP_RX1_SOURCE_FIRST_POWER_ON()              (g_stDpRx1MiscInfo.b1DpSourceFirstPowerOn = _TRUE)
#define CLR_DP_RX1_SOURCE_FIRST_POWER_ON()              (g_stDpRx1MiscInfo.b1DpSourceFirstPowerOn = _FALSE)

#define GET_DP_RX1_SOURCE_WRITE_POWER_UP()              (g_stDpRx1MiscInfo.enumDpSourceWritePowerUp)
#define SET_DP_RX1_SOURCE_WRITE_POWER_UP(x)             (g_stDpRx1MiscInfo.enumDpSourceWritePowerUp = (x))
#define CLR_DP_RX1_SOURCE_WRITE_POWER_UP()              (g_stDpRx1MiscInfo.enumDpSourceWritePowerUp = _DP_SOURCE_WRITE_POWER_UP_NONE)
#endif // #if(_DP_MST_SUPPORT == _ON)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucDpRx1PhyCtsCtrl;
extern EnumHDCPType g_enumDpRx1HdcpMode;
extern StructDpLanesMapping g_stDpRx1LanesMapping;

#if(_DP_MST_SUPPORT == _ON)
extern StructDPRxMiscInfo g_stDpRx1MiscInfo;
extern BYTE g_pucDpRx1MstTimeSlotBackup[13];
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
extern StructDpLinkInfo g_stDpRx1LinkInfo;
#endif

extern WORD g_pusDpRx1ClockCount[4];
extern WORD g_pusDpRx1ClockCount1[4];
extern BYTE g_ucDpRx1Tp1PermitSwingLevel0;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
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

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
extern void ScalerDpRx1CalculateLinkRate(EnumDpLaneCount enumDpLaneCount);
#endif

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
extern void ScalerDpRx1Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
extern bit ScalerDpRx1MarginLinkCheck(void);
extern void ScalerDpRx1LinkStatusIRQ(void);
extern void ScalerDpRx1AuxSet(void);
extern void ScalerDpRx1ErrorCounterUpdate_EXINT0(void);
extern void ScalerDpRx1ErrorCounterDisable_EXINT0(void);
extern void ScalerDpRx1ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern bit ScalerDpRx1MSAActiveChange(void);
extern bit ScalerDpRx1PSPreDetect(void);
extern void ScalerDpRx1SecDataBlockReset(void);
extern void ScalerDpRx1SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpRx1SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpRx1SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpRx1ChangeHdcpDpcdCapability(bit bEn);

#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
extern void ScalerDpRx1ASSRModeSetting(void);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDpRx1GetFREESYNCStatusChange(void);
extern void ScalerDpRx1SetFREESYNCMsaForLut(WORD usDpHtotal);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpRx1MstInfoBackup(EnumDpMstBackup enumDpMstBackup);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx1HDCPAuthShaRun(bit bIsFirst);
extern void ScalerDpRx1HDCPChangeAuthState(EnumDPRxHDCPAuthState enumHDCPAuthState);
extern bit ScalerDpRx1HDCPCheckLvp(void);
extern void ScalerDpRx1HDCPHandler(void);
extern void ScalerDpRx1HDCPSetReadIrqTimeout(void);
extern void ScalerDpRx1HDCPSetRepeaterProcTimeout(void);
extern void ScalerDpRx1MstToSstProc(void);
extern void ScalerDpRx1MstToSstSetColorInfo(void);
#endif

#endif // End of #if(_DP_MST_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx1UpdateSinkCount(BYTE ucSinkCount);
#endif

extern void ScalerDpRx1AdjustLaneFLDBand(BYTE ucDpRx1LaneNumber, WORD usVCOBandDiff);
extern void ScalerDpRx1CpIRQ(EnumDpRxBStatusType enumBStatusType);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpRx1CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType);
#endif
extern bit ScalerDpRx1DFECheck(void);
extern bit ScalerDpRx1DecodeCheck(void);
extern bit ScalerDpRx1DisplayFormatSetting(void);
extern bit ScalerDpRx1FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpRx1HDCPBlockReset(void);
extern bit ScalerDpRx1HdcpCheckValid(void);
extern bit ScalerDpRx1HdcpCheckEnabled(void);
extern bit ScalerDpRx1HdcpMeasureCheck(void);
extern bit ScalerDpRx1HdcpReAuthStatusCheck(void);
extern void ScalerDpRx1MacInitial(void);
extern bit ScalerDpRx1NormalPreDetect(void);
extern bit ScalerDpRx1PhyCtsTp1Check(void);
extern bit ScalerDpRx1PhyCtsTp2Check(void);
extern void ScalerDpRx1PhyInitial(void);
extern BYTE ScalerDpRx1ScanInputPort(void);
extern void ScalerDpRx1SetDFEInitial(EnumDpLinkRate enumDpLinkRate);
extern void ScalerDpRx1SetFifoIRQ(bit bEn);
extern void ScalerDpRx1SetFifoWD(bit bEn);
extern bit ScalerDpRx1StableDetect(void);
extern void ScalerDpRx1ValidSignalDetectionActiveEvent(void);

#if(_DP_MST_SUPPORT == _ON)
extern bit ScalerDpRx1LTStatusCheck(void);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx1HDCPEnableReadIrq(bit bEnable);
extern bit ScalerDpRx1MstToSstFifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern bit ScalerDpRx1MstToSstMSAActiveChange(void);
extern bit ScalerDpRx1MstToSstMeasureInput(void);
extern bit ScalerDpRx1MstToSstMiscCheck(void);
extern BYTE ScalerDpRx1MstToSstScanInputPort(void);
extern void ScalerDpRx1DfpDeviceDetailConfigReset(void);
extern void ScalerDpRx1DfpDeviceDetailConfig(void);
#endif

#endif
extern StructDpRxErrorCount ScalerDpRx1GetErrorCount(void);

#endif // End of #if(_D1_DP_EXIST == _ON)

