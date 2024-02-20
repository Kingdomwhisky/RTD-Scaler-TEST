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
// ID Code      : ScalerDPRx0_ComboPhyInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_D0_DP_EXIST == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX0_FAKE_LINK_TRAINING()                 ((g_ucDpRx0Info & _BIT7) >> 7)
#define SET_DP_RX0_FAKE_LINK_TRAINING()                 (g_ucDpRx0Info |= _BIT7)
#define CLR_DP_RX0_FAKE_LINK_TRAINING()                 (g_ucDpRx0Info &= ~_BIT7)

#define GET_DP_RX0_VALID_VIDEO_CHECK()                  ((g_ucDpRx0Info & _BIT6) >> 6)
#define SET_DP_RX0_VALID_VIDEO_CHECK()                  (g_ucDpRx0Info |= _BIT6)
#define CLR_DP_RX0_VALID_VIDEO_CHECK()                  {\
                                                            ScalerDpRx0CancelValidSignalDetectTimerEvent();\
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

#if(_HW_DP_LANE_VALID_CHECK_SUPPORT == _OFF)
#define GET_DP_RX0_SOURCE_LT_FIRST_ROUND()              (g_bDpRx0SourceLTFirstRound)
#define SET_DP_RX0_SOURCE_LT_FIRST_ROUND()              (g_bDpRx0SourceLTFirstRound = _TRUE)
#define CLR_DP_RX0_SOURCE_LT_FIRST_ROUND()              (g_bDpRx0SourceLTFirstRound = _FALSE)
#endif
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

//--------------------------------------------------
// Definitions of DP Lane Setting Ralation to Actual Lane Mapping
//--------------------------------------------------
#define _D0_DP_LANE0                                    (GET_DP_RX0_PCB_LANE0_MAPPING())
#define _D0_DP_LANE1                                    (GET_DP_RX0_PCB_LANE1_MAPPING())
#define _D0_DP_LANE2                                    (GET_DP_RX0_PCB_LANE2_MAPPING())
#define _D0_DP_LANE3                                    (GET_DP_RX0_PCB_LANE3_MAPPING())


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucDpRx0PhyCtsCtrl;

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit g_bDpRx0SourceTypeJudge;

#if(_HW_DP_LANE_VALID_CHECK_SUPPORT == _OFF)
extern bit g_bDpRx0SourceLTFirstRound;
#endif
#endif

extern StructDpLanesMapping g_stDpRx0LanesMapping;
extern BYTE g_ucDpRx0EQCRC;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx0ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
extern void ScalerDpRx0CpIRQ(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpRx0AlignCheck(void);
extern bit ScalerDpRx0DecodeCheck(void);
extern void ScalerDpRx0SetNoVideoStreamIRQ(bit bEn);
extern void ScalerDpRx0DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);
extern bit ScalerDpRx0FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpRx0HDCPBlockReset(void);
extern bit ScalerDpRx0HdcpCheck(void);
extern bit ScalerDpRx0HdcpCheckValid(void);
extern bit ScalerDpRx0HdcpCheckEnabled(void);
extern bit ScalerDpRx0HdcpReAuthStatusCheck(void);
extern void ScalerDpRx0Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
extern bit ScalerDpRx0MarginLinkCheck(void);
extern void ScalerDpRx0LinkStatusIRQ(void);
extern void ScalerDpRx0AuxSet(void);
extern bit ScalerDpRx0ChangeSrambleSeed(void);

#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)
extern bit ScalerDpRx0VbiosAssrCheck(bit bMSACheckResult);
#endif

extern bit ScalerDpRx0PSPreDetect(void);
extern bit ScalerDpRx0PhyCtsTp2Check(void);
extern void ScalerDpRx0SetFifoIRQ(bit bEn);
extern void ScalerDpRx0SetFifoWD(bit bEn);
extern void ScalerDpRx0HpdIrqAssert(void);
extern EnumDpHotPlugTime ScalerDpRx0BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType);
extern void ScalerDpRx0AfterHpdToggleProc(void);
extern void ScalerDpRx0CancelValidSignalDetectTimerEvent(void);

#endif
