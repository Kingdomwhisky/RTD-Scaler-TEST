/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6492_Series_DPRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_DPRX1__

#include "ScalerFunctionInclude.h"

#if(_D1_DP_EXIST == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DP_DE_ONLY_MODE_WITH_FULL_LAST_LINE_SUPPORT            _OFF


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
bit g_bDpRx1PSAuxToggle = _FALSE;
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
bit g_bDpRx1SignaldetectINTHappened;
#endif

bit g_bDpRx1AuxCommandNoReply = _FALSE;

BYTE g_ucDpRx1LinkStatus01;
BYTE g_ucDpRx1LinkStatus23;
BYTE g_ucDpRx1LinkRequest01;
BYTE g_ucDpRx1LinkRequest23;
BYTE g_ucDpRx1Temp;
BYTE g_pucDpRx1Backup[3];
BYTE g_ucDpRx1Info;
BYTE g_ucDpRx1LinkRate;
BYTE g_ucDpRx1LaneCount;
BYTE g_ucDpRx1TrainingPatternSet;

BYTE g_pucDpRx1Tap1MinTemp[4];
BYTE g_pucDpRx1LEMinTemp[4];
BYTE g_ucDpRx1EQCRC;
WORD g_usDpRx1ClockTargetCount;
WORD g_usDpRx1ClockMeasureCount;
BYTE g_ucRx1AuxTemp;
BYTE g_ucRx1AuxTemp_EXINT;
WORD g_usDpRx1Vfrontporch;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
BYTE g_ucDpRx1FakeLTLaneCount;
BYTE g_ucDpRx1FakeLTLaneCountBackUp;
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
BYTE g_pucDPRx1Caps[3];
#endif

WORD g_pusDpRx1ClockCount[4];
WORD g_pusDpRx1ClockCount1[4];

BYTE g_ucDpRx1PhyCtsCtrl;
EnumHDCPType g_enumDpRx1HdcpMode;

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
bit g_bDpRx1SourceTypeJudge = _FALSE;
#endif

StructDpLanesMapping g_stDpRx1LanesMapping;

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit g_bDpRx1VscSdpColorMode;

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
bit g_bDpRx1RSV1PacketDetecting;

#endif
#endif

BYTE g_ucDpRx1MSAFailMacRsetCount;
bit g_bDpRx1SourceRDErrorCount = _FALSE;

#if(_DP_HDR10_SUPPORT == _ON)
BYTE g_ucDPRx1InfoTypeCompare;
BYTE g_pucDPRx1HDR10Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
BYTE g_pucDPRx1InfoTemp[_HW_DP_INFOFRAME_RSV0_LENGTH];
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
BYTE g_pucDPRx1RSV0Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
StructDPInfoFrameRSV0Ctrl g_stDPRx1InfoFrameRSV0Ctrl;
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
StructDpLinkInfo g_stDpRx1LinkInfo;
#endif

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
BYTE g_ucDpRx1AuxModeBackup_EXINT;
#endif

bit g_bDpRx1Tp1Initial = _FALSE;
BYTE g_ucDpRx1LTPatternSet;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpRx1AuxPowerOnInitial(void);
void ScalerDpRx1AuxIntInitial(void);
void ScalerDpRx1DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
void ScalerDpRx1ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
void ScalerDpRx1ChangeHdcpDpcdCapability(bit bEn);
void ScalerDpRx1MacInitial(void);
void ScalerDpRx1PhyInitial(void);
void ScalerDpRx1RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
void ScalerDpRx1PassiveDFEFineTune(void);
void ScalerDpRx1AdjustLaneFLDBand(WORD usVCOBandDiff);
void ScalerDpRx1SetDFEInitial(EnumDpLinkRate enumDpLinkRate);
bit ScalerDpRx1CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
bit ScalerDpRx1MeasureLaneCDRClk(BYTE ucDpLinkRate, BYTE ucDpRx1LaneNumber);
void ScalerDpRx1ValidSignalDetection(void);
BYTE ScalerDpRx1LinkRateDetect(void);
bit ScalerDpRx1LinkRateCheck(BYTE ucDpLinkRate);
WORD ScalerDpRx1SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);
bit ScalerDpRx1SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
bit ScalerDpRx1VBIOSMSACheck(bit bDeskewEnhanced);
#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
bit ScalerDpRx1VbiosAssrCheck(bit bMSACheckResult);
#endif
bit ScalerDpRx1ChangeSrambleSeed(void);
void ScalerDpRx1SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue);
bit ScalerDpRx1DecodeCheck(void);
bit ScalerDpRx1DFECheck(void);
bit ScalerDpRx1DisplayFormatSetting(void);
bit ScalerDpRx1InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);
bit ScalerDpRx1StreamClkRegenerate(void);
bit ScalerDpRx1FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
void ScalerDpRx1HDCPBlockReset(void);
void ScalerDpRx1HDCPUnplugReset(void);
bit ScalerDpRx1HdcpCheck(void);
bit ScalerDpRx1HdcpReAuthStatusCheck(void);
bit ScalerDpRx1HdcpMeasureCheck(void);
void ScalerDpRx1CpIRQ(EnumDpRxBStatusType enumBStatusType);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
void ScalerDpRx1CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType);
#endif
bit ScalerDpRx1HdcpCheckValid(void);
bit ScalerDpRx1HdcpCheckEnabled(void);
void ScalerDpRx1PhyCtsTp1SetPhy(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx1PhyCtsTp2SetPhy(void);
bit ScalerDpRx1PhyCtsTp1Check(void);
bit ScalerDpRx1PhyCtsTp2Check(void);
void ScalerDpRx1PhyCTS(void);

void ScalerDpRx1SetFifoWD(bit bEn);
void ScalerDpRx1SetFifoIRQ(bit bEn);
bit ScalerDpRx1NormalPreDetect(void);
BYTE ScalerDpRx1ScanInputPort(void);
bit ScalerDpRx1StableDetect(void);

void ScalerDpRx1AVMute(void);
void ScalerDpRx1AdjustVsyncDelay(void);
bit ScalerDpRx1AlignCheck(void);
void ScalerDpRx1ScrambleSetting(void);

#if((_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON) && (_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON))
bit ScalerDpRx1LaneValidCheck(void);
#endif

void ScalerDpRx1CheckHdcpCpirqStatus(void);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
bit ScalerDpRx1CheckVgipVsBypass(void);
#endif

void ScalerDpRx1CrcCalculate(void);
#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
void ScalerDpRx1HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
#endif
void ScalerDpRx1SetNoVideoStreamIRQ(bit bEn);
void ScalerDpRx1DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);
DWORD ScalerDpRx1GetBStoVSDelay(void);
BYTE ScalerDpRx1GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
BYTE ScalerDpRx1GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
bit ScalerDpRx1GetVideoStream(void);
EnumDpHotPlugTime ScalerDpRx1BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType);
void ScalerDpRx1AfterHpdToggleProc(void);
void ScalerDpRx1CancelValidSignalDetectTimerEvent(void);

void ScalerDpRx1Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
bit ScalerDpRx1MarginLinkCheck(void);
void ScalerDpRx1LinkStatusIRQ(void);
void ScalerDpRx1AuxSet(void);
void ScalerDpRx1ErrorCounterUpdate_EXINT0(void);
void ScalerDpRx1ErrorCounterDisable_EXINT0(void);
void ScalerDpRx1ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType);

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx1DecodeErrorCountReset_WDINT(void);
#endif

void ScalerDpRx1DecodeErrorCountReset(void);

bit ScalerDpRx1MSAActiveChange(void);
bit ScalerDpRx1PSPreDetect(void);
void ScalerDpRx1SetDpLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation);
void ScalerDpRx1SecDataBlockReset(void);
void ScalerDpRx1SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
void ScalerDpRx1SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
void ScalerDpRx1SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);

#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
void ScalerDpRx1ASSRModeSetting(void);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
bit ScalerDpRx1GetFREESYNCStatusChange(void);
void ScalerDpRx1SetFREESYNCMsaForLut(WORD usDpHtotal);
#endif

bit ScalerDpRx1GetVideoInfo(void);
void ScalerDpRx1SetColorInfo(void);
void ScalerDpRx1VideoSetting(void);
void ScalerDpRx1ColorimetrySetting(void);
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
void ScalerDpRx1ColorimetryExtSetting(void);
#endif
void ScalerDpRx1QuantizationSetting(void);

bit ScalerDpRx1MiscCheck(void);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit ScalerDpRx1VscCheck(void);

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
void ScalerDpRx1RSV1PacketDetectEvent(void);
void ScalerDpRx1SetInitialRSV1InfoType(void);
#endif

#endif

bit ScalerDpRx1MSACheck(void);
void ScalerDpRx1FakeLTProtect(void);
void ScalerDpRx1SetInitialRSV0InfoType(void);
void ScalerDpRx1SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType);
void ScalerDpRx1HpdIrqAssert(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
void ScalerDpRx1HpdIrqAssert_EXINT0(void);
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_ULTRA_HDR_SUPPORT == _ON))
void ScalerDpRx1GetInfoFrameRSV0(BYTE *pucDPRx1RSV0Data);
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
void ScalerDpRx1InfoFrameRSV0Check(void);
void ScalerDpRx1RSV0PacketDetectEvent(void);
void ScalerDpRx1InfoFrameRSV0Initial(void);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
BYTE ScalerDpRx1SelectInfoFrameType(BYTE ucInfoFrameTypeCurrent);

#if(_AUDIO_SUPPORT == _ON)
void ScalerDpRx1SwitchHDR10CmpAudioInfo(void);
#endif
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
bit ScalerDpRx1CheckHdcpCapability(void);
void ScalerDpRx1HdcpHandshakeMonitorEnable(void);
void ScalerDpRx1HdcpHandshakeMonitorDisable(void);
void ScalerDpRx1HdcpHandshakeMonitorDisable_EXINT0(void);
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
void ScalerDpRx1TimingInfoBackup(void);
#endif

StructDpRxErrorCount ScalerDpRx1GetErrorCount(void);
WORD ScalerDpRx1GetDecodeErrorCount(BYTE ucDpRx1LaneNumber);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial Setting for DP Digital Aux, Analog Aux
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AuxPowerOnInitial(void)
{
    // Digital Aux Power On, DPCD REG Power On, MSG Power On.
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT1 | _BIT0), 0x00);

    // Average 8 cycles as Start Postion, Aux Clk Select to 27MHz, no Swap
    ScalerSetByte(PBA_72_AUX_DIG_PHY2, 0xC0);

#if(_DP_AUX_REPLY_CLK_SEL_FROM == _DP_AUX_REPLY_SEL_IOSC)
    // Aux Clk Select Manual Mode, Aux New Mode
    ScalerSetBit(PBA_73_AUX_DIG_PHY3, ~(_BIT7 | _BIT6), _BIT6);
#else
    // Aux Clk Select Source, Aux New Mode
    ScalerSetBit(PBA_73_AUX_DIG_PHY3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif

    // HW Fake Link Training Disable.
    ScalerSetBit(PBA_C6_AUX_PHY_DIG2, ~_BIT4, 0x00);

    // Set Aux Precharge Number.
    ScalerSetBit(PBA_74_AUX_DIG_PHY4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

    // Aux Auto Mode, Using Default Average Number.
    ScalerSetByte(PBA_75_AUX_DIG_PHY5, 0x0D);

#if(_DP_AUX_REPLY_TIMEOUT_BY_USER == _ON)
    // Aux Reply Timeout Setting
    ScalerSetByte(PBA_A2_AUX_RESERVE2, _DP_AUX_REPLY_TIMEOUT_USER_SETTING);
#endif

    // Enble Aux Channel.
    ScalerSetBit(PBA_D0_AUX_MODE_SET, ~(_BIT3 | _BIT2 | _BIT0), _BIT0);

    // Fast IIC Clock.
    ScalerSetByte(PBA_D1_DP_IIC_SET, 0x02);

    // Set aux mac clk use xclk
    ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), _BIT3);

    // Not Reply when Aux Error.
    ScalerSetBit(PBA_DB_AUX_STATUS, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetBit(PBA_76_AUX_DIG_PHY6, ~(_BIT7 | _BIT6), _BIT6);

    // Aux Ack Timer.
    ScalerSetBit(PBA_F0_AUX_TX_TIMER, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));

    // Set Timeout Target
    ScalerSetBit(PBA_F1_AUX_TX_TIMER_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));

    // Disable Reply IIC Defer Before Data Ready.
    ScalerSetBit(PBA_F4_MCUIIC, ~(_BIT6 | _BIT5), 0x00);

    // Enable Aux Error Handler.
    ScalerSetBit(PBA_78_AUX_DIG_PHY8, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // Toggle Aux Auto K
    ScalerSetBit(PBA_65_AUX_5, ~_BIT7, 0x00);
    ScalerSetBit(PBA_65_AUX_5, ~_BIT7, _BIT7);

    // Aux Mode Set (Diff Mode or Single-ended mode) && Aux RX1 Resistance Setting
    ScalerDpRx1AuxSet();

    // Set Aux Talk Mode ADJR
    ScalerSetByte(PBA_67_DIG_TX_03, 0xFF);

    ScalerSetBit(PBA_60_DIG_TX_04, ~(_BIT1 | _BIT0), _BIT0);

    switch(GET_DP_EMBEDDED_SWITCH_SELECT())
    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

#if(_D1_AUX_DDC_CHANNEL == _D1_AUX_MAP_DDC1_PIN)
            // Enable Aux Channel 1, Disable Channel 2
            ScalerSetBit(PBA_60_DIG_TX_04, ~(_BIT7 | _BIT6), _BIT7);
            // Aux Mapping to DDC1
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT3 | _BIT2), _BIT2);

#elif(_D1_AUX_DDC_CHANNEL == _D1_AUX_MAP_DDC2_PIN)
            // Enable Aux Channel 1, Disable Channel 2
            ScalerSetBit(PBA_60_DIG_TX_04, ~(_BIT7 | _BIT6), _BIT6);
            // Aux Mapping to DDC1
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT3 | _BIT2), _BIT3);
#endif
            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

#if(_D2_AUX_DDC_CHANNEL == _D2_AUX_MAP_DDC1_PIN)
            // Enable Aux Channel 1, Disable Channel 2
            ScalerSetBit(PBA_60_DIG_TX_04, ~(_BIT7 | _BIT6), _BIT7);
            // Aux Mapping to DDC1
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT3 | _BIT2), _BIT2);

#elif(_D2_AUX_DDC_CHANNEL == _D2_AUX_MAP_DDC2_PIN)
            // Enable Aux Channel 1, Disable Channel 2
            ScalerSetBit(PBA_60_DIG_TX_04, ~(_BIT7 | _BIT6), _BIT6);
            // Aux Mapping to DDC1
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT3 | _BIT2), _BIT3);
#endif
            break;
#endif
        default:
            break;
    }

    // Delay 100ms for Aux Common Mode Voltage Stable, To Avoid Swing Couple to Aux Cabledetect
    ScalerTimerDelayXms(100);

    // Aux comm current select max
    ScalerSetBit(PBA_64_AUX_4, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Set Aux D_2 = ~D_1 for Aux Single Ended Mode
    ScalerSetBit(PBA_79_AUX_DIG_PHY9, ~_BIT7, _BIT7);

    // Clear the Clock Divider for AUX MAC and PHY
    ScalerSetBit(PBA_73_AUX_DIG_PHY3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PBA_B0_AUX_PAYLOAD_CLEAR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Aux ps clk from IOSC
    ScalerSetBit(P0_0B_POWER_CTRL, ~(_BIT5 | _BIT4), 0x00);

    // Set the Clock Divider = 1 for AUX MAC and PHY
    ScalerSetBit(PBA_73_AUX_DIG_PHY3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PBA_B0_AUX_PAYLOAD_CLEAR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
}

//--------------------------------------------------
// Description  : Initial Setting for DP Aux INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AuxIntInitial(void)
{
    // Enable 068xxx INT
    ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~(_BIT4 | _BIT1 | _BIT0), _BIT1);
    ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT2);

    // Disable other DPCD, Aux Timeout, Receiving Aux INT.
    ScalerSetBit(PBA_DC_AUX_IRQ_STATUS, ~(_BIT5 | _BIT3 | _BIT2), 0x00);

    // Disable Aux Phy Int
    ScalerSetBit(PBA_77_AUX_DIG_PHY7, ~_BIT7, 0x00);

    // Enable DPCD INT
    ScalerSetByte(PBA_DE_AUX_DPCD_IRQ_EN, 0xE5);

    // Internal IRQ Enable (Global)
    ScalerGlobalIRQControl(_ENABLE);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Clear HDCP2.2 Handshaked Related IRQ
    ScalerSetBit(PBA_A4_AUX_RESERVE4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));
    ScalerSetBit(PBA_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable HDCP2.2 Handshaked Related IRQ
    ScalerSetBit(PBA_A3_AUX_RESERVE3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));
    ScalerSetBit(PBA_A5_AUX_RESERVE5, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // Source Read 692DFh(HPrime) INT
    ScalerSetByte(PBA_B7_AUX_IRQ_ADDR1_MSB, 0x06);
    ScalerSetByte(PBA_B8_AUX_IRQ_ADDR1_MSB1, 0x92);
    ScalerSetByte(PBA_B9_AUX_IRQ_ADDR1_LSB, 0xDF);
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    // INT Wildcard 0 set for Source Read 68028h
    ScalerSetByte(PBA_B4_AUX_IRQ_ADDR0_MSB, 0x06);
    ScalerSetByte(PBA_B5_AUX_IRQ_ADDR0_MSB1, 0x80);
    ScalerSetByte(PBA_B6_AUX_IRQ_ADDR0_LSB, 0x28);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // INT Wildcard 2 set for Source Read 6921Xh
    ScalerSetByte(PBA_BA_AUX_IRQ_ADDR2_MSB, 0x16);
    ScalerSetByte(PBA_BB_AUX_IRQ_ADDR2_MSB1, 0x92);
    ScalerSetByte(PBA_BC_AUX_IRQ_ADDR2_LSB, 0x10);
#endif

    ScalerDpRx1HdcpHandshakeMonitorEnable();

#else
    // Enable Rx1 DPCD table controlled by DP HDCP circuit
    SET_REG_DP_RX1_DPCD_CTRL_BY_HDCP();
#endif

    // Disable Wildcard IRQ for Error Counter
    ScalerSetBit(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), 0x00);

    // Use Wildcard 3 to DPCD 0x0021xh, LSB 4 Bits Discarded
    ScalerSetByte(PBA_BD_AUX_IRQ_ADDR3_MSB, 0x10);
    ScalerSetByte(PBA_BE_AUX_IRQ_ADDR3_MSB1, 0x02);
    ScalerSetByte(PBA_BF_AUX_IRQ_ADDR3_LSB, 0x10);

    // Enable INT0
    EX0 = 1;
}

//--------------------------------------------------
// Description  : DPCD Table Initial
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport)
{
    enumFreeSyncSupport = enumFreeSyncSupport;

    ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);
    ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);

    ScalerDpRx1ChangeDpcdVersion(enumDpVersion, enumDpRxMstPort);

    // Enhanced Framing Support(Bit7) and DP Lane Count(Bit[4:0])
    pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x02);
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x02, ((pData[0] & ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) | _BIT7 | enumDpLaneCount));

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
    g_ucDpRx1FakeLTLaneCount = (enumDpLaneCount & 0x1F);
    g_ucDpRx1FakeLTLaneCountBackUp = (enumDpLaneCount & 0x1F);
#endif

    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x03, 0x01);

#if(_AUDIO_SUPPORT == _ON)
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x04, 0x01);
#else
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x04, 0x00);
#endif

    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x05, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x06, 0x01);
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x08, 0x02);

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _OFF)
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x09, 0x00);
#endif

#if(_AUDIO_SUPPORT == _ON)
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0A, 0x06);
#else
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0A, 0x00);
#endif

    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0B, 0x00);

    switch(GET_DP_EMBEDDED_SWITCH_SELECT())
    {
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_ASSR_MODE_SUPPORT == _ON))
        case _D1_INPUT_PORT:

            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0D, 0x01);

            SET_DP_RX1_AUX_MANUAL_MODE();
            ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
            SET_DP_RX1_AUX_AUTO_MODE();

            break;
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_ASSR_MODE_SUPPORT == _ON))
        case _D2_INPUT_PORT:

            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0D, 0x01);

            SET_DP_RX1_AUX_MANUAL_MODE();
            ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
            SET_DP_RX1_AUX_AUTO_MODE();

            break;
#endif

        default:
            break;
    }

    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x21, 0x00);

    // DPCD Link Status Field Setting
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x00, 0x41);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x08, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x09, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x0A, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x0B, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x46, 0x20);

    // Initialize Reserved to 0
    ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x10, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x12, 0x00);

#if(_DP_FREESYNC_SUPPORT == _ON)
    switch(GET_DP_EMBEDDED_SWITCH_SELECT())
    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            SET_DP_RX1_FREESYNC_SUPPORT(enumFreeSyncSupport);

            if(GET_DP_RX1_FREESYNC_SUPPORT() == _FREESYNC_SUPPORT_ON)
            {
                ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);
            }
            else
            {
                ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);
            }

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            SET_DP_RX2_FREESYNC_SUPPORT(enumFreeSyncSupport);

            if(GET_DP_RX2_FREESYNC_SUPPORT() == _FREESYNC_SUPPORT_ON)
            {
                ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);
            }
            else
            {
                ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);
            }

            break;
#endif

        default:
            break;
    }
#endif
    // Initialize HDCP2.2 DPCD (69XXXh) to 0s for avoiding SRAM initial state values remained
    SET_DP_RX1_AUX_MANUAL_MODE();

    for(PDATA_WORD(0) = 0x9000; PDATA_WORD(0) <= 0x94BF; PDATA_WORD(0)++)
    {
        ScalerDpRx1SetDpcdValue(0x06, pData[0], pData[1], 0x00);
    }

    SET_DP_RX1_AUX_AUTO_MODE();

#if(_DP_HDCP_2_2_SUPPORT == _ON)

    // Load Certrx to DPCD Table
    ScalerDpRx1Hdcp2LoadCertRrxKey();
#endif

    // Down Stream Port isn't HPD Aware
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x80, 0x00);

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    // Disable HDCP at first
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x00);
#else
    // _BIT1: Repeater,  _BIT0: HDCP Capable
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x01);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)

    // Set HDCP_Capable and Repeater Bit
    g_pucDPRx1Caps[0] = 0x02;
    g_pucDPRx1Caps[1] = 0x00;
    g_pucDPRx1Caps[2] = 0x02;

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    // Disable HDCP at first
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), 0x00);
    }
#else
    // Load RxCaps to DPCD Table
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), g_pucDPRx1Caps[pData[0]]);
    }
#endif
#endif

    // Align 0220Xh & 0000Xh
    for(pData[0] = 0x02; pData[0] <= 0x0F; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x00, 0x22, pData[0], ScalerDpRx1GetDpcdInfo(0x00, 0x00, pData[0]));
    }
}

//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort)
{
    enumDpRxMstPort = _DP_MST_NO_PORT;

    if(enumDpVersion >= _DP_VERSION_1_4)
    {
        // DPCD Version
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_2);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x00, enumDpVersion);
#else
        g_ucDpRx1DPCD02200hValue = enumDpVersion;
#endif

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x0E, ~_BIT7, _BIT7);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x10, 0x08);
#else
        g_ucDpRx1DPCD02210hValue = 0x08;
#endif

#else

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x10, 0x00);
#else
        g_ucDpRx1DPCD02210hValue = 0x00;
#endif

#endif

        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            case _D1_INPUT_PORT:

                if(_D1_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
                }
                else
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _D1_DP_LINK_CLK_RATE);
                }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, _D1_DP_LINK_CLK_RATE);
#else
                g_ucDpRx1DPCD02201hValue = _D1_DP_LINK_CLK_RATE;
#endif

                break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            case _D2_INPUT_PORT:

                if(_D2_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
                }
                else
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _D2_DP_LINK_CLK_RATE);
                }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, _D2_DP_LINK_CLK_RATE);
#else
                g_ucDpRx1DPCD02201hValue = _D2_DP_LINK_CLK_RATE;
#endif

                break;
#endif
            default:
                break;
        }

        // _BIT3:0, Down Stream Port Counter
        pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _DP_1_2_DOWN_STREAM_PORT_COUNT));

        // _BIT7 = 1: Always IEEE OUI Support Under DP1.2
        ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

        // Sink IEEE OUI
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x00, _DP_1_2_SINK_RTK_IEEE_OUI_L);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x01, _DP_1_2_SINK_RTK_IEEE_OUI_M);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x02, _DP_1_2_SINK_RTK_IEEE_OUI_H);

        // Sink IEEE OUI LSB For DP1.2
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x03, _DP_1_2_SINK_RTK_ID_STRING_0);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x04, _DP_1_2_SINK_RTK_ID_STRING_1);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x05, _DP_1_2_SINK_RTK_ID_STRING_2);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x06, _DP_1_2_SINK_RTK_ID_STRING_3);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x07, _DP_1_2_SINK_RTK_ID_STRING_4);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x08, _DP_1_2_SINK_RTK_ID_STRING_5);

        // Sink HW/FW Version For DP1.2
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x09, _DP_1_2_SINK_RTK_HW_VERSION);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x0A, _DP_1_2_SINK_RTK_FW_VERSION_H);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x0B, _DP_1_2_SINK_RTK_FW_VERSION_L);

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON)
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x09, 0x00);
#endif
    }
    else if(enumDpVersion == _DP_VERSION_1_2)
    {
        // DPCD Version
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_2);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x00, _DP_VERSION_1_4);
#else
        g_ucDpRx1DPCD02200hValue = _DP_VERSION_1_4;
#endif

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x0E, ~_BIT7, 0x00);

        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            case _D1_INPUT_PORT:

                if(_D1_DP_LINK_CLK_RATE > _DP_HIGH_SPEED2_540MHZ)
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
                }
                else
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _D1_DP_LINK_CLK_RATE);
                }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, _D1_DP_LINK_CLK_RATE);
#else
                g_ucDpRx1DPCD02201hValue = _D1_DP_LINK_CLK_RATE;
#endif

                break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            case _D2_INPUT_PORT:

                if(_D2_DP_LINK_CLK_RATE > _DP_HIGH_SPEED2_540MHZ)
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
                }
                else
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _D2_DP_LINK_CLK_RATE);
                }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, _D2_DP_LINK_CLK_RATE);
#else
                g_ucDpRx1DPCD02201hValue = _D2_DP_LINK_CLK_RATE;
#endif

                break;
#endif
            default:
                break;
        }

        // _BIT3:0, Down Stream Port Counter
        pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _DP_1_2_DOWN_STREAM_PORT_COUNT));

        // _BIT7 = 1: Always IEEE OUI Support Under DP1.2
        ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

        // Sink IEEE OUI
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x00, _DP_1_2_SINK_RTK_IEEE_OUI_L);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x01, _DP_1_2_SINK_RTK_IEEE_OUI_M);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x02, _DP_1_2_SINK_RTK_IEEE_OUI_H);

        // Sink IEEE OUI LSB For DP1.2
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x03, _DP_1_2_SINK_RTK_ID_STRING_0);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x04, _DP_1_2_SINK_RTK_ID_STRING_1);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x05, _DP_1_2_SINK_RTK_ID_STRING_2);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x06, _DP_1_2_SINK_RTK_ID_STRING_3);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x07, _DP_1_2_SINK_RTK_ID_STRING_4);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x08, _DP_1_2_SINK_RTK_ID_STRING_5);

        // Sink HW/FW Version For DP1.2
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x09, _DP_1_2_SINK_RTK_HW_VERSION);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x0A, _DP_1_2_SINK_RTK_FW_VERSION_H);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x0B, _DP_1_2_SINK_RTK_FW_VERSION_L);

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON)
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x09, 0x00);
#endif
    }
    else
    {
        // DPCD Version
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_1);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x00, _DP_VERSION_1_4);
#else
        g_ucDpRx1DPCD02200hValue = _DP_VERSION_1_4;
#endif

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x0E, ~_BIT7, 0x00);

        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            case _D1_INPUT_PORT:

                if(_D1_DP_LINK_CLK_RATE > _DP_HIGH_SPEED_270MHZ)
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR);
                }
                else
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _D1_DP_LINK_CLK_RATE);
                }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, _D1_DP_LINK_CLK_RATE);
#else
                g_ucDpRx1DPCD02201hValue = _D1_DP_LINK_CLK_RATE;
#endif

                break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            case _D2_INPUT_PORT:

                if(_D2_DP_LINK_CLK_RATE > _DP_HIGH_SPEED_270MHZ)
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR);
                }
                else
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _D2_DP_LINK_CLK_RATE);
                }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, _D2_DP_LINK_CLK_RATE);
#else
                g_ucDpRx1DPCD02201hValue = _D2_DP_LINK_CLK_RATE;
#endif

                break;
#endif
            default:
                break;
        }

        // _BIT3:0, Down Stream Port Counter
        pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _DP_1_1_DOWN_STREAM_PORT_COUNT));

#if(_DP_SINK_VER11_OUI_SUPPORT == _ON)
        // _BIT7 = 1: IEEE OUI Support
        ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

        // Sink IEEE OUI
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x00, _DP_1_1_SINK_RTK_IEEE_OUI_L);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x01, _DP_1_1_SINK_RTK_IEEE_OUI_M);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x02, _DP_1_1_SINK_RTK_IEEE_OUI_H);
#else
        // _BIT7 = 0: IEEE OUI Not Support
        ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT7, 0x00);

        // Sink IEEE OUI
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x00, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x01, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x02, 0x00);
#endif

        // Sink IEEE OUI LSB For DP1.1
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x03, _DP_1_1_SINK_RTK_ID_STRING_0);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x04, _DP_1_1_SINK_RTK_ID_STRING_1);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x05, _DP_1_1_SINK_RTK_ID_STRING_2);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x06, _DP_1_1_SINK_RTK_ID_STRING_3);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x07, _DP_1_1_SINK_RTK_ID_STRING_4);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x08, _DP_1_1_SINK_RTK_ID_STRING_5);

        // Sink HW/FW Version For DP1.1
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x09, _DP_1_1_SINK_RTK_HW_VERSION);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x0A, _DP_1_1_SINK_RTK_FW_VERSION_H);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x0B, _DP_1_1_SINK_RTK_FW_VERSION_L);

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON)
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x09, 0x02);
#endif
    }

    if((ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x01) >= _DP_LINK_HBR2) ||
       ((ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpRx1GetDpcdInfo(0x00, 0x22, 0x01) >= _DP_LINK_HBR2)))
    {
        // TPS3 Support
        ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x02, ~_BIT6, _BIT6);
    }
    else
    {
        // TPS3 NonSupport
        ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x02, ~_BIT6, 0x00);
    }

    // Set TRAINING_AUX_RD_INTERVAL = 400us for EQ phase
    ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x0E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_LT_AUX_RD_INTVL_EQ_400US);

    // Align 0220Xh & 0000Xh
    for(pData[0] = 0x02; pData[0] <= 0x0F; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x00, 0x22, pData[0], ScalerDpRx1GetDpcdInfo(0x00, 0x00, pData[0]));
    }
}

//--------------------------------------------------
// Description  : Dp HDCP DPCD capability Switch
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ChangeHdcpDpcdCapability(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Clear flag for write 68xxx int
        ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~_BIT1, _BIT1);

        // Enable Write 68xxx int
        ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~_BIT2, _BIT2);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        // Clear flag for Write AKSV int
        ScalerSetBit(PBA_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

        // Enable Write AKSV int
        ScalerSetBit(PBA_A5_AUX_RESERVE5, ~_BIT6, _BIT6);

        // Enable HDCP and repeater support
        ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x03);
#else
        // Enable HDCP support
        ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x01);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        // Enable the HDCP2.2 capability
        for(pData[0] = 0; pData[0] < 3; pData[0]++)
        {
            ScalerDpRx1SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), g_pucDPRx1Caps[pData[0]]);
        }
#endif
    }
    else
    {
        // Disable Write 68xxx int
        ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~_BIT2, 0x00);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        // Disable Write AKSV int
        ScalerSetBit(PBA_A5_AUX_RESERVE5, ~_BIT6, 0x00);
#endif
        // Disable HDCP support
        ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x00);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        // Disable the HDCP2.2 capability
        for(pData[0] = 0; pData[0] < 3; pData[0]++)
        {
            ScalerDpRx1SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), 0x00);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Dp Mac Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MacInitial(void)
{
    // Set Digital Phy to Normal
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // err_8b10b_ctrl_gate = 1'b1 --> Avoid 8b10b Error Decode to FS
    ScalerSetBit(PB_10_PHY_CH_FIFO_SYNC0, ~_BIT3, _BIT3);

    // DP RGB Output Enable
    ScalerSetBit(PB5_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // DP CLK Output Enable
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, _BIT6);

    // 0x00:disable error correction, 0xF4:enable all error correction
    ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~_BIT1, _BIT1);

    // Disable DP Fifo Under/OverFlow Watch Dog
    ScalerDpRx1SetFifoWD(_DISABLE);

    // Disable DP Fifo Under/OverFlow IRQ
    ScalerDpRx1SetFifoIRQ(_DISABLE);

    // Disable DP No Video Stream IRQ
    ScalerDpRx1SetNoVideoStreamIRQ(_DISABLE);

    ScalerDpRx1SetInitialRSV0InfoType();

    // Enable HW to store data to RSV0 memory (Only for RL6492)
    ScalerSetBit(PB6_3E_DP_INFO_FM_RSV_STATUS, ~_BIT4, _BIT4);

#if((_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON) && (_HW_DP_VSC_SDP_REG_SUPPORT != _ON))

    ScalerDpRx1SetInitialRSV1InfoType();

    // Enable HW to store data to RSV1 memory (Only for RL6492)
    ScalerSetBit(PB6_3E_DP_INFO_FM_RSV_STATUS, ~_BIT5, _BIT5);
#endif

    CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();
}

//--------------------------------------------------
// Description  : DP Phy Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1PhyInitial(void)
{
    // [7:6] rxvcom_sel = 2'b01 --> VDD-0.3V
    // [5] en_enhance_bias = 1'b1 --> enhance clock lane buffer current
    // [0] powersw_on = 1'b1 --> power switch on
    ScalerSetBit(P1D_15_BANDGAP_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), (_BIT6 | _BIT5 | _BIT0));

    // [7:6] offcal_range = 2'b11 --> 75uA
    ScalerSetBit(P1D_26_KOFFSET_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [7] sel_d2s_highrate = 1'b1 --> Increase d2s Gain
    ScalerSetBit(P1D_28_KOFFSET_02, ~_BIT7, _BIT7);

    // [7:6] CMU_SEL_CP = 2'b00 --> CMU LPF Cp = 0pF
    ScalerSetBit(P1D_23_CMU_06, ~(_BIT7 | _BIT6), 0x00);

    // [1:0] cdr_kvco = 2'b01 --> KVCO = 700M/v
    ScalerSetBit(P1D_30_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);

    // [7] en_wide_temp = 1'b1 --> Vcp-Vcn=-0.1V
    ScalerSetBit(P1D_33_ANA_CDR_05, ~_BIT7, _BIT7);

    // [7] sel_cont3 = 1'b1 --> BBPD UP/DN Div3
    ScalerSetBit(P1D_34_ANA_CDR_06, ~_BIT7, _BIT7);

    // [3:0] Enable Data Stream Signal Detection
    ScalerSetBit(P1D_22_CMU_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [4] en_sumamp_highgain = 0 --> Disable Sumamp High Gain Mode
    ScalerSetBit(P1D_29_KOFFSET_03, ~_BIT6, 0x00);

    // [0] reg_bypass_ok = 0 --> Disable bypass ok
    ScalerSetBit(P1D_21_CMU_04, ~_BIT0, 0x00);

    // DP Global Parameter MeasureCount Initial
    ScalerSyncDpMeasureCountInitial();
}

//--------------------------------------------------
// Description  : Rebuilding DP PHY
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
    BYTE ucD1Z0Status = 0;
    BYTE ucD2Z0Status = 0;
    WORD usVCOBandDiff = 0;
    WORD usVCOBandScan = 0;
    BYTE ucIcp = 0;


    ////////////////////
    // Mode Select DP //
    ////////////////////

    // Backup Z0 Status
    ucD1Z0Status = ScalerGetBit(P1D_17_IMPEDANCE_00, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ucD2Z0Status = ScalerGetBit(P1D_19_IMPEDANCE_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable Z0
    ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [5] dp_mode = 1'b1 --> Select DP Mode
    ScalerSetBit(P1D_16_BANDGAP_02, ~_BIT5, _BIT5);

    // [7] si_hd_dp_sel = 1'b0 --> Select DP
    ScalerSetBit(P1D_05_DIG_05, ~_BIT7, 0x00);

    // [4] PSM = 1'b0 --> Disable Clock Switch
    ScalerSetBit(P1D_15_BANDGAP_01, ~_BIT4, 0x00);

    // Restore Z0 Status
    ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucD1Z0Status);
    ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucD2Z0Status);


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

    // DP Lane Swap Setting
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D1_DP_LANE3 << 6);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D1_DP_LANE2 << 4);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D1_DP_LANE1 << 2);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

    // DP Lane PN Swap Setting
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, GET_DP_RX1_PCB_LANE3_PN_SWAP() << 7);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, GET_DP_RX1_PCB_LANE2_PN_SWAP() << 6);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, GET_DP_RX1_PCB_LANE1_PN_SWAP() << 5);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, GET_DP_RX1_PCB_LANE0_PN_SWAP() << 4);


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

    // [7] cmu_en = 1'b0 --> Lane3 CMU Disable
    ScalerSetBit(P1D_21_CMU_04, ~_BIT7, 0x00);

    // Disable RX_EN, CDR_EN
    ScalerSetByte(P1D_20_CMU_03, 0x00);

    // Enable RX_EN
    ScalerSetBit(P1D_20_CMU_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            // dp_bbpd_sel[3:2] --> ACDR BBPD UP/DN from MAC Lane0
            ScalerSetBit(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), GET_DP_RX1_PCB_LANE0_MAPPING() << 2);

            if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable Lane0 CDR_EN for DCDR
                ScalerSetBit(P1D_20_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable Lane1 CDR_EN for DCDR
                ScalerSetBit(P1D_20_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable Lane2 CDR_EN for DCDR
                ScalerSetBit(P1D_20_CMU_03, ~_BIT2, _BIT2);
            }

            // [4:3] DP MAC Select One Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            if((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) || (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3))
            {
                // dp_bbpd_sel[3:2] = 2'b11 --> ACDR BBPD UP/DN from Lane3
                ScalerSetBit(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
            }
            else
            {
                // dp_bbpd_sel[3:2] --> ACDR BBPD UP/DN from MAC Lane0
                ScalerSetBit(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), GET_DP_RX1_PCB_LANE0_MAPPING() << 2);
            }

            if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable Lane0 CDR_EN for DCDR
                ScalerSetBit(P1D_20_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable Lane1 CDR_EN for DCDR
                ScalerSetBit(P1D_20_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable Lane2 CDR_EN for DCDR
                ScalerSetBit(P1D_20_CMU_03, ~_BIT2, _BIT2);
            }

            if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable Lane0 CDR_EN for DCDR
                ScalerSetBit(P1D_20_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable Lane1 CDR_EN for DCDR
                ScalerSetBit(P1D_20_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable Lane2 CDR_EN for DCDR
                ScalerSetBit(P1D_20_CMU_03, ~_BIT2, _BIT2);
            }

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            // dp_bbpd_sel[3:2] = 2'b11 --> ACDR BBPD UP/DN from Lane3
            ScalerSetBit(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // Enable Lane0/1/2 CDR_EN for DCDR
            ScalerSetBit(P1D_20_CMU_03, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P1D_20_CMU_03, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P1D_20_CMU_03, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [4:3] DP MAC Select Four Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }

    // Enable Lane3 CDR_EN for BBPD
    ScalerSetBit(P1D_20_CMU_03, ~_BIT3, _BIT3);

    // ln_clk_func_sel[1:0] --> MAC Clock from Analog CDR Lane
    ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), (ScalerGetBit(P1D_30_ANA_CDR_02, (_BIT3 | _BIT2)) >> 2));

    // Delay Time us [25,x]
    DELAY_25US();

    // Enable Analog CDR and FLD
    ScalerSetBit(P1D_12_ANA_CDR, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));


    ///////////////////////
    // Frequency Setting //
    ///////////////////////

    // [6] xtal_en = 1'b1 --> FLD using xtal as reference clock
    ScalerSetBit(P1D_30_ANA_CDR_02, ~_BIT6, _BIT6);

    switch(ucDpLinkRate)
    {
        // 25/500 = 1/20 = 5*(27M/2.7G)
        case _DP_LINK_HBR:

            g_usDpRx1ClockTargetCount = 0x1388; // ideal 2.7G

            // [2:0] rate_sel = 3'b001 --> 1.75~3.5Gbps
            ScalerSetBit(P1D_3C_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            // [1:0] SEL_DIV = 2'b00 --> 1.75~3.5Gbps
            ScalerSetBit(P1D_24_CMU_07, ~(_BIT1 | _BIT0), 0x00);

            // ref_conuter = 24
            ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT7, 0x00);
            ScalerSetByte(P1D_36_ANA_CDR_08, 0x18);

            // cdr_counter = 499
            ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT6, _BIT6);
            ScalerSetByte(P1D_37_ANA_CDR_09, 0xF3);

            break;

        // 20/480 = 1/24 = 5*(27M/3.24G)
        case _DP_LINK_RBR:
        default:

            g_usDpRx1ClockTargetCount = 0xBB8; // ideal 1.62G

            // [2:0] rate_sel = 3'b001 --> 875M~1.75Gbps
            ScalerSetBit(P1D_3C_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            // [1:0] SEL_DIV = 2'b00 --> 875M~1.75Gbps
            ScalerSetBit(P1D_24_CMU_07, ~(_BIT1 | _BIT0), _BIT0);

            // ref_conuter = 19
            ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT7, 0x00);
            ScalerSetByte(P1D_36_ANA_CDR_08, 0x13);

            // cdr_counter = 479
            ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT6, _BIT6);
            ScalerSetByte(P1D_37_ANA_CDR_09, 0xDF);

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // Enable Comma Detection
    ScalerSetBit(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    if((ucDpcdLane & _BIT7) == _BIT7)
    {
        // Enable Enhancement Control Mode --> MAC
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable Enhancement Control Mode --> MAC
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
    {
        // Disable Scrambling
        ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // Enable Scrambling
        ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
    }

    // [1] bypass_clk_rdy = 1'b1 --> Clk Rdy Signal in Manual Mode
    // [0] en_clkout_manual = 1'b1 --> Enable Clkout
    ScalerSetBit(P1D_0E_SDM_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1] bypass_eqen_rdy = 1'b1 --> EQEN Rdy Signal in Manual Mode
    // [0] en_eqen_manual = 1'b1 --> Enable EQ
    ScalerSetBit(P1D_10_EQEN_TIMER, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1] bypass_data_rdy = 1'b1 --> Data Rdy Signal in Manual Mode
    // [0] en_data_manual = 1'b0 --> Disable Dataout
    ScalerSetBit(P1D_11_DATA_TIMER, ~(_BIT1 | _BIT0), _BIT1);

    // [3] reg_en_data_manual_l3 = 1'b0 --> Disable Data Ready
    // [2] reg_bypass_data_rdy_l3 = 1'b1 --> Data Ready Signal in Manual Mode
    // [1] reg_en_eqen_manual_l3 = 1'b1 --> Enable EQ
    // [0] reg_bypass_eqen_rdy_l3 = 1'b1 --> EQ Ready Signal in Manual Mode
    ScalerSetBit(P1D_12_ANA_CDR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Digital Circuit Reset Toggle
    ScalerSetByte(P1D_38_TMDS_RESET, 0x00);
    ScalerSetByte(P1D_38_TMDS_RESET, 0xF0);

    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            break;

        case _DP_TWO_LANE:

            // [3] cdr_rst_n_lane0 = CDR_EN[0]
            ScalerSetBit(P1D_38_TMDS_RESET, ~_BIT3, (ScalerGetBit(P1D_20_CMU_03, _BIT0) << 3));

            // [2] cdr_rst_n_lane1 = CDR_EN[1]
            ScalerSetBit(P1D_38_TMDS_RESET, ~_BIT2, (ScalerGetBit(P1D_20_CMU_03, _BIT1) << 1));

            // [1] cdr_rst_n_lane2 = CDR_EN[2]
            ScalerSetBit(P1D_38_TMDS_RESET, ~_BIT1, (ScalerGetBit(P1D_20_CMU_03, _BIT2) >> 1));

            if((GET_DP_RX1_PCB_LANE0_MAPPING() != _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() != _DP_SCALER_LANE3))
            {
                if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
                {
                    // [3] cdr_rst_n_lane0 = 0 --> Disable DCDR Lane0
                    ScalerSetBit(P1D_38_TMDS_RESET, ~_BIT3, 0x00);
                }
                else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
                {
                    // [2] cdr_rst_n_lane1 = 0 --> Disable DCDR Lane1
                    ScalerSetBit(P1D_38_TMDS_RESET, ~_BIT2, 0x00);
                }
                else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
                {
                    // [1] cdr_rst_n_lane2 = 0 --> Disable DCDR Lane2
                    ScalerSetBit(P1D_38_TMDS_RESET, ~_BIT1, 0x00);
                }
            }

            break;

        case _DP_FOUR_LANE:
        default:

            // [3:0] cdr_rst_n_lane0~3 = 4'b1110
            ScalerSetBit(P1D_38_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

            break;
    }


    /////////////////
    // CDR Setting //
    /////////////////

    // [6:4] sel_cdr_res = 3'b110 --> 8K Ohm
    ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR:

            // [3:0] cdr_cp_in = 4'b0101 --> (1nF)16.5uA
            ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Lane0~2 KP = 4
            ScalerSetByte(P1D_56_CDR_07, 0x10);
            ScalerSetByte(P1D_57_CDR_08, 0x10);
            ScalerSetByte(P1D_58_CDR_09, 0x10);

            break;

        case _DP_LINK_RBR:
        default:

            // [3:0] cdr_cp_in = 4'b0110 --> (1nF)19.5uA
            ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Lane0~2 KP = 8
            ScalerSetByte(P1D_56_CDR_07, 0x20);
            ScalerSetByte(P1D_57_CDR_08, 0x20);
            ScalerSetByte(P1D_58_CDR_09, 0x20);

            break;
    }

    ucIcp = (ScalerGetByte(P1D_31_ANA_CDR_03) & 0x0F);


    ////////////////
    // EQ Setting //
    ////////////////

    // [4:0] reg_fore_off_adjr_Lane0~3 = 5'b10000
    ScalerSetBit(P1D_2A_KOFFSET_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P1D_2B_KOFFSET_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P1D_2C_KOFFSET_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P1D_2D_KOFFSET_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR:

            // [7] le_lowgain_highboost = 1'b0 --> Disable LE High-boost Mode
            ScalerSetBit(P1D_2B_KOFFSET_05, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // [7:5] le_isel = 3'b010 --> LE Peaking = 1.7Gbps
            ScalerSetBit(P1D_2C_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

            // [7:5] le_rlsel = 3'b001 --> LE Peaking = 1.7Gbps
            ScalerSetBit(P1D_2D_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            break;

        case _DP_LINK_RBR:
        default:

            // [7] le_lowgain_highboost = 1'b0 --> Enable LE High-boost Mode
            ScalerSetBit(P1D_2B_KOFFSET_05, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // [7:5] le_isel = 3'b000 --> LE Peaking = 900Mbps
            ScalerSetBit(P1D_2C_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // [7:5] le_rlsel = 3'b011 --> LE Peaking = 900Mbps
            ScalerSetBit(P1D_2D_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

            break;
    }

    // Set DFE Initial
    ScalerDpRx1SetDFEInitial(ucDpLinkRate);

    // [2:0] tap_en = 3'b001 --> Eable Tap0 Passive EQ
    ScalerSetBit(P1D_2E_ANA_CDR_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [7] en_fore_offset = 1'b0 --> Disable EQ foreground Offset Calibration
    // [6] fore_off_autok = 1'b1 --> Enable EQ foreground Offset Calibration Auto Mode
    ScalerSetBit(P1D_2A_KOFFSET_04, ~(_BIT7 | _BIT6), _BIT6);

    // Toggle en_fore_offset
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x]
    DELAY_XUS(85);


    ///////////////////
    // FLD Auto Mode //
    ///////////////////

    // Set FLD Auto Mode
    ScalerSetBit(P1D_2E_ANA_CDR_00, ~_BIT7, _BIT7);

    // [2] cp_en_manual = 1'b0 --> CDR Open Loop
    // [1] adp_en_manual = 1'b0 --> Disable CDR Clock
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~(_BIT2 | _BIT1), 0x00);

    // [7] rstb_fld --> Reset Timer of Analog CDR
    // [6] rstb_fsm --> FLD Reset
    ScalerSetBit(P1D_32_ANA_CDR_04, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P1D_32_ANA_CDR_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Delay Time us [150,x]
    DELAY_XUS(150);


    /////////////////////
    // FLD Manual Mode //
    /////////////////////

    // Scan Auto FLD + 4
    ScalerSetBit(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_34_ANA_CDR_06) & 0x7F) + 4));

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    ScalerSetBit(P1D_2E_ANA_CDR_00, ~_BIT7, 0x00);

    // [1] adp_en_manual = 1'b1 --> Enable CDR Clock Out
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT1, _BIT1);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();


    //////////////////////////
    //  Scan FLD Band + 4   //
    //////////////////////////

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [1:0] freqdet_lane_sel = ACDR Lane
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ScalerGetBit(P1D_30_ANA_CDR_02, (_BIT3 | _BIT2)) >> 2));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT Value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            usVCOBandScan = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }


    /////////////////////////
    // VCO Band Difference //
    /////////////////////////

    // Scan Auto FLD Band
    ScalerSetBit(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_34_ANA_CDR_06) & 0x7F));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT Value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        if((usVCOBandScan == 0) || (ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6))
        {
            break;
        }
    }

    if((usVCOBandScan != 0) && (ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6))
    {
        g_usDpRx1ClockMeasureCount = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        usVCOBandDiff = (abs(usVCOBandScan - g_usDpRx1ClockMeasureCount) >> 2);
    }
    else
    {
        usVCOBandDiff = 0;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    if(usVCOBandDiff != 0)
    {
        // VCO Adjust
        ScalerDpRx1AdjustLaneFLDBand(usVCOBandDiff);
    }

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();


    ////////////////////
    // CDR Close Loop //
    ////////////////////

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS(150);

    // [0] en_data_manual = 1'b1 --> Enable Dataout
    ScalerSetBit(P1D_11_DATA_TIMER, ~_BIT0, _BIT0);

    // [3] en_data_manual_l3 = 1'b1 --> Enable Dataout for Lane3
    ScalerSetBit(P1D_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] xclk_sel = 1'b0 --> Keep Link Clock from Analog
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : DP DFE Finetune
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1PassiveDFEFineTune(void)
{
    WORD pusLevel0LEErrorCount[4];
    WORD pusLevel1LEErrorCount[4];
    WORD pusLevel2LEErrorCount[4];
    WORD pusLevel3LEErrorCount[4];
    BYTE ucLELevel0 = 0;
    BYTE ucLELevel1 = 0;
    BYTE ucLELevel2 = 0;
    BYTE ucLELevel3 = 0;
    BYTE ucIcp = 0;
    BYTE ucLaneSelect = 0;
    BYTE ucTemp = 0;

    ucIcp = (ScalerGetByte(P1D_31_ANA_CDR_03) & 0x0F);
    ucLELevel2 = ScalerGetBit(P1D_A2_L0_LIMIT_INIT, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)); // 10/12
    ucLELevel0 = ucLELevel2 - 9; // 1/3
    ucLELevel1 = ucLELevel2 - 5; // 5/7
    ucLELevel3 = ucLELevel2 + 5; // 15/17


    ////////////////////////////
    // LE = Default = Level 2 //
    ////////////////////////////

    // [2:0] rxbist_method = 3'b000 --> Clear 8b10b Error Count
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [2:0] rxbist_method = 3'b010 --> Detect 8b10b + Disparity Correctness
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay for Checking 8b10b Error Count
    ScalerTimerDelayXms(5);

    // [4:3] rxbist_lane_sel = 2'b00 --> Lane0
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE0 << 3);
    pusLevel2LEErrorCount[_D1_DP_LANE0] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#if(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE1 << 3);
    pusLevel2LEErrorCount[_D1_DP_LANE1] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE2 << 3);
    pusLevel2LEErrorCount[_D1_DP_LANE2] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE3 << 3);
    pusLevel2LEErrorCount[_D1_DP_LANE3] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#endif

    //////////////////
    // LE = Level 3 //
    //////////////////

    // LE Initial = 15/17
    ScalerSetByte(P1D_A2_L0_LIMIT_INIT, ucLELevel3);
    ScalerSetByte(P1D_B2_L1_LIMIT_INIT, ucLELevel3);
    ScalerSetByte(P1D_C2_L2_LIMIT_INIT, ucLELevel3);
    ScalerSetByte(P1D_D2_L3_LIMIT_INIT, ucLELevel3);

    // Load Intial DFE Code
    ScalerSetByte(P1D_AA_L0_INIT_8, 0x80);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x80);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x80);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x80);

    ScalerSetByte(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x00);

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS(150);

    // [2:0] rxbist_method = 3'b000 --> Clear 8b10b Error Count
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [2:0] rxbist_method = 3'b010 --> Detect 8b10b + Disparity Correctness
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay for Checking 8b10b Error Count
    ScalerTimerDelayXms(5);

    // [4:3] rxbist_lane_sel = 2'b00 --> Lane0
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE0 << 3);
    pusLevel3LEErrorCount[_D1_DP_LANE0] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#if(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE1 << 3);
    pusLevel3LEErrorCount[_D1_DP_LANE1] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE2 << 3);
    pusLevel3LEErrorCount[_D1_DP_LANE2] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE3 << 3);
    pusLevel3LEErrorCount[_D1_DP_LANE3] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#endif

    //////////////////
    // LE = Level 1 //
    //////////////////

    // LE Initial = 5/7
    ScalerSetByte(P1D_A2_L0_LIMIT_INIT, ucLELevel1);
    ScalerSetByte(P1D_B2_L1_LIMIT_INIT, ucLELevel1);
    ScalerSetByte(P1D_C2_L2_LIMIT_INIT, ucLELevel1);
    ScalerSetByte(P1D_D2_L3_LIMIT_INIT, ucLELevel1);

    // Load Intial DFE Code
    ScalerSetByte(P1D_AA_L0_INIT_8, 0x80);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x80);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x80);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x80);

    ScalerSetByte(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x00);

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS(150);

    // [2:0] rxbist_method = 3'b000 --> Clear 8b10b Error Count
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [2:0] rxbist_method = 3'b010 --> Detect 8b10b + Disparity Correctness
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay for Checking 8b10b Error Count
    ScalerTimerDelayXms(5);

    // [4:3] rxbist_lane_sel = 2'b00 --> Lane0
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE0 << 3);
    pusLevel1LEErrorCount[_D1_DP_LANE0] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#if(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE1 << 3);
    pusLevel1LEErrorCount[_D1_DP_LANE1] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE2 << 3);
    pusLevel1LEErrorCount[_D1_DP_LANE2] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE3 << 3);
    pusLevel1LEErrorCount[_D1_DP_LANE3] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#endif


    //////////////////
    // LE = Level 0 //
    //////////////////

    // LE Initial = 1/3
    ScalerSetByte(P1D_A2_L0_LIMIT_INIT, ucLELevel0);
    ScalerSetByte(P1D_B2_L1_LIMIT_INIT, ucLELevel0);
    ScalerSetByte(P1D_C2_L2_LIMIT_INIT, ucLELevel0);
    ScalerSetByte(P1D_D2_L3_LIMIT_INIT, ucLELevel0);

    // Load Intial DFE Code
    ScalerSetByte(P1D_AA_L0_INIT_8, 0x80);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x80);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x80);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x80);

    ScalerSetByte(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x00);

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS(150);

    // [2:0] rxbist_method = 3'b000 --> Clear 8b10b Error Count
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [2:0] rxbist_method = 3'b010 --> Detect 8b10b + Disparity Correctness
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay for Checking 8b10b Error Count
    ScalerTimerDelayXms(5);

    // [4:3] rxbist_lane_sel = 2'b00 --> Lane0
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE0 << 3);
    pusLevel0LEErrorCount[_D1_DP_LANE0] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#if(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE1 << 3);
    pusLevel0LEErrorCount[_D1_DP_LANE1] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE2 << 3);
    pusLevel0LEErrorCount[_D1_DP_LANE2] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D1_DP_LANE3 << 3);
    pusLevel0LEErrorCount[_D1_DP_LANE3] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#endif

    DebugMessageRx1("Level 3 LE ErrorCount[_D1_DP_LANE0]", pusLevel3LEErrorCount[_D1_DP_LANE0]);
    DebugMessageRx1("Level 2 LE ErrorCount[_D1_DP_LANE0]", pusLevel2LEErrorCount[_D1_DP_LANE0]);
    DebugMessageRx1("Level 1 LE ErrorCount[_D1_DP_LANE0]", pusLevel1LEErrorCount[_D1_DP_LANE0]);
    DebugMessageRx1("Level 0 LE ErrorCount[_D1_DP_LANE0]", pusLevel0LEErrorCount[_D1_DP_LANE0]);

#if(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    DebugMessageRx1("Level 3 LE ErrorCount[_D1_DP_LANE1]", pusLevel3LEErrorCount[_D1_DP_LANE1]);
    DebugMessageRx1("Level 2 LE ErrorCount[_D1_DP_LANE1]", pusLevel2LEErrorCount[_D1_DP_LANE1]);
    DebugMessageRx1("Level 1 LE ErrorCount[_D1_DP_LANE1]", pusLevel1LEErrorCount[_D1_DP_LANE1]);
    DebugMessageRx1("Level 0 LE ErrorCount[_D1_DP_LANE1]", pusLevel0LEErrorCount[_D1_DP_LANE1]);

    DebugMessageRx1("Level 3 LE ErrorCount[_D1_DP_LANE2]", pusLevel3LEErrorCount[_D1_DP_LANE2]);
    DebugMessageRx1("Level 2 LE ErrorCount[_D1_DP_LANE2]", pusLevel2LEErrorCount[_D1_DP_LANE2]);
    DebugMessageRx1("Level 1 LE ErrorCount[_D1_DP_LANE2]", pusLevel1LEErrorCount[_D1_DP_LANE2]);
    DebugMessageRx1("Level 0 LE ErrorCount[_D1_DP_LANE2]", pusLevel0LEErrorCount[_D1_DP_LANE2]);

    DebugMessageRx1("Level 3 LE ErrorCount[_D1_DP_LANE3]", pusLevel3LEErrorCount[_D1_DP_LANE3]);
    DebugMessageRx1("Level 2 LE ErrorCount[_D1_DP_LANE3]", pusLevel2LEErrorCount[_D1_DP_LANE3]);
    DebugMessageRx1("Level 1 LE ErrorCount[_D1_DP_LANE3]", pusLevel1LEErrorCount[_D1_DP_LANE3]);
    DebugMessageRx1("Level 0 LE ErrorCount[_D1_DP_LANE3]", pusLevel0LEErrorCount[_D1_DP_LANE3]);
#endif


    ///////////////////////////////////
    // Choose The Best DFE Parameter //
    ///////////////////////////////////

    for(ucLaneSelect = 0; ucLaneSelect < 4; ucLaneSelect++)
    {
#if(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_1_LANE)

        ucTemp = _D1_DP_LANE0;

#elif(_DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

        ucTemp = ucLaneSelect;
#endif
        if(pusLevel3LEErrorCount[ucTemp] >= pusLevel0LEErrorCount[ucTemp])
        {
            if((pusLevel2LEErrorCount[ucTemp] > pusLevel0LEErrorCount[ucTemp]) && (pusLevel1LEErrorCount[ucTemp] >= pusLevel0LEErrorCount[ucTemp]))
            {
                if(pusLevel1LEErrorCount[ucTemp] == pusLevel0LEErrorCount[ucTemp])
                {
                    // LE Initial = 3/5
                    ScalerSetByte((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), (ucLELevel0 + ucLELevel1) >> 1);
                }
                else
                {
                    // LE Initial = 1/3
                    ScalerSetByte((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel0);
                }
            }
            else if((pusLevel0LEErrorCount[ucTemp] > pusLevel2LEErrorCount[ucTemp]) && (pusLevel1LEErrorCount[ucTemp] >= pusLevel2LEErrorCount[ucTemp]))
            {
                if(pusLevel1LEErrorCount[ucTemp] == pusLevel2LEErrorCount[ucTemp])
                {
                    // LE Initial = 7/9
                    ScalerSetByte((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), (ucLELevel1 + ucLELevel2) >> 1);
                }
                else
                {
                    // LE Initial = 10/12
                    ScalerSetByte((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel2);
                }
            }
            else
            {
                // LE Initial = 5/7
                ScalerSetByte((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel1);
            }
        }
        else
        {
            if((pusLevel1LEErrorCount[ucTemp] > pusLevel3LEErrorCount[ucTemp]) && (pusLevel2LEErrorCount[ucTemp] >= pusLevel3LEErrorCount[ucTemp]))
            {
                if(pusLevel2LEErrorCount[ucTemp] == pusLevel3LEErrorCount[ucTemp])
                {
                    // LE Initial = 12/14
                    ScalerSetByte((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), (ucLELevel2 + ucLELevel3) >> 1);
                }
                else
                {
                    // LE Initial = 15/17
                    ScalerSetByte((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel3);
                }
            }
            else if((pusLevel3LEErrorCount[ucTemp] > pusLevel1LEErrorCount[ucTemp]) && (pusLevel2LEErrorCount[ucTemp] >= pusLevel1LEErrorCount[ucTemp]))
            {
                if(pusLevel2LEErrorCount[ucTemp] == pusLevel1LEErrorCount[ucTemp])
                {
                    // LE Initial = 7/9
                    ScalerSetByte((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), (ucLELevel1 + ucLELevel2) >> 1);
                }
                else
                {
                    // LE Initial = 5/7
                    ScalerSetByte((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel1);
                }
            }
            else
            {
                // LE Initial = 10/12
                ScalerSetByte((P1D_A2_L0_LIMIT_INIT + (ucLaneSelect * 0x0010)), ucLELevel2);
            }
        }
    }

    // HBR Reload Tap0 = 21
    if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
    {
        ScalerSetByte(P1D_A4_L0_INIT_2, 0x15);
        ScalerSetByte(P1D_B4_L1_INIT_2, 0x15);
        ScalerSetByte(P1D_C4_L2_INIT_2, 0x15);
        ScalerSetByte(P1D_D4_L3_INIT_2, 0x15);
    }

    // Load Intial DFE Code
    ScalerSetByte(P1D_AA_L0_INIT_8, 0x81);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x81);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x81);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x81);

    ScalerSetByte(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x00);

    // Toggle en_fore_offset
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x]
    DELAY_XUS(85);

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS(150);
}

//--------------------------------------------------
// Description  : DP FLD Band Finetune
// Input Value  : LaneNumber
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AdjustLaneFLDBand(WORD usVCOBandDiff)
{
    BYTE ucBestVCOBand = 0;
    BYTE ucAutoVCOBand = 0;

    ucAutoVCOBand = (ScalerGetByte(P1D_34_ANA_CDR_06) & 0x7F);

    // [1:0] freqdet_lane_sel = ACDR Lane
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ScalerGetBit(P1D_30_ANA_CDR_02, (_BIT3 | _BIT2)) >> 2));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            break;
        }
    }

    if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        g_usDpRx1ClockMeasureCount = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        if(g_usDpRx1ClockMeasureCount < g_usDpRx1ClockTargetCount)
        {
            ucBestVCOBand = ucAutoVCOBand + (((g_usDpRx1ClockTargetCount - g_usDpRx1ClockMeasureCount) / usVCOBandDiff) + 1);
        }
        else
        {
            ucBestVCOBand = ucAutoVCOBand - ((g_usDpRx1ClockMeasureCount - g_usDpRx1ClockTargetCount) / usVCOBandDiff);
        }
    }
    else
    {
        ucBestVCOBand = ucAutoVCOBand;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // Manually Reload FLD Band
    ScalerSetBit(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDFEInitial(EnumDpLinkRate enumDpLinkRate)
{
    enumDpLinkRate = enumDpLinkRate;


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // LE Initial = 10
    ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x0A);
    ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x0A);
    ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x0A);
    ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x0A);

    // Tap0 Initial Value = 15
    ScalerSetByte(P1D_A4_L0_INIT_2, 0x0F);
    ScalerSetByte(P1D_B4_L1_INIT_2, 0x0F);
    ScalerSetByte(P1D_C4_L2_INIT_2, 0x0F);
    ScalerSetByte(P1D_D4_L3_INIT_2, 0x0F);

    // Tap1 Initial Value = 0
    ScalerSetByte(P1D_A5_L0_INIT_3, 0x00);
    ScalerSetByte(P1D_B5_L1_INIT_3, 0x00);
    ScalerSetByte(P1D_C5_L2_INIT_3, 0x00);
    ScalerSetByte(P1D_D5_L3_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte(P1D_A6_L0_INIT_4, 0x00);
    ScalerSetByte(P1D_B6_L1_INIT_4, 0x00);
    ScalerSetByte(P1D_C6_L2_INIT_4, 0x00);
    ScalerSetByte(P1D_D6_L3_INIT_4, 0x00);

    // Load Intial DFE Code
    ScalerSetByte(P1D_AA_L0_INIT_8, 0xFF);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0xFF);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0xFF);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0xFF);

    ScalerSetByte(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x00);
}

//--------------------------------------------------
// Description  : Check Valid Lane CDR
// Input Value  : None
// Output Value : True --> CDR Lock
//--------------------------------------------------
bit ScalerDpRx1CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
    CLR_DP_RX1_SIGNALDETECT_INT_HAPPENED();
#endif

    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            if(ScalerDpRx1MeasureLaneCDRClk(ucDpLinkRate, _D1_DP_LANE0) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_TWO_LANE:

            if(ScalerDpRx1MeasureLaneCDRClk(ucDpLinkRate, _D1_DP_LANE0) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_FOUR_LANE:
        default:

            if(ScalerDpRx1MeasureLaneCDRClk(ucDpLinkRate, _D1_DP_LANE3) == _TRUE)
            {
                return _TRUE;
            }

            break;
    }

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
    if(GET_DP_RX1_SIGNALDETECT_INT_HAPPENED() == _TRUE)
    {
        return _TRUE;
    }
    else
#endif
    {
        DebugMessageRx1("7. wuzanne test : DP CDR Unlock", 0);

        return _FALSE;
    }
}

//--------------------------------------------------
// Description : check DP CDR locked or unlocked
// Input Value  : DP Lane
// Output Value : True --> locked; False --> unlocked
//--------------------------------------------------
bit ScalerDpRx1MeasureLaneCDRClk(BYTE ucDpLinkRate, BYTE ucDpRx1LaneNumber)
{
    WORD usCDRClockCount = 0;

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR:

            if((abs(g_pusDpRx1ClockCount[ucDpRx1LaneNumber] - 0x1388)) > (0x1388 >> 4))
            {
                return _TRUE;
            }

            break;

        default:
        case _DP_LINK_RBR:

            if((abs(g_pusDpRx1ClockCount[ucDpRx1LaneNumber] - 0xBB8)) > (0xBB8 >> 4))
            {
                return _TRUE;
            }

            break;
    }

    // Select Measure CDR Clock & XTAL 27M Count 1000 Times
    ScalerSetByte(PB_50_DP_SIG_DET_0, 0x23);

    // Select CDR Lane
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), ucDpRx1LaneNumber);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // Toggle Start Measure
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [85,x] Waiting for Measure Done
    DELAY_XUS(85);

    if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == 0x00)
    {
        return _FALSE;
    }

    usCDRClockCount = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

    if(abs(g_pusDpRx1ClockCount[ucDpRx1LaneNumber] - usCDRClockCount) > (g_pusDpRx1ClockCount[ucDpRx1LaneNumber] >> 7))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Valid Video Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ValidSignalDetection(void)
{
    BYTE ucDpLinkRate = 0;
    BYTE ucDpLaneCount = _DP_FOUR_LANE;

    SET_DP_RX1_AUX_MANUAL_MODE();

    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
       (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
    {
        ucDpLinkRate = ScalerDpRx1LinkRateDetect();

        SET_DP_RX1_AUX_AUTO_MODE();

        if(ucDpLinkRate == _DP_LINK_NONE)
        {
            return;
        }

        do
        {
            SET_DP_RX1_AUX_MANUAL_MODE();

            if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
               (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
            {
                ScalerDpRx1RebuildPhy(ucDpLinkRate, (ucDpLaneCount | _BIT7));

                SET_DP_RX1_AUX_AUTO_MODE();

                if(ScalerDpRx1VBIOSMSACheck(_FALSE) == _TRUE)
                {
                    break;
                }
                else
                {
                    if(ScalerDpRx1VBIOSMSACheck(_TRUE) == _TRUE)
                    {
                        break;
                    }
                }

                if(ucDpLaneCount == _DP_FOUR_LANE)
                {
                    ucDpLaneCount = _DP_TWO_LANE;
                }
                else if(ucDpLaneCount == _DP_TWO_LANE)
                {
                    ucDpLaneCount = _DP_ONE_LANE;
                }
                else if(ucDpLaneCount == _DP_ONE_LANE)
                {
                    ucDpLaneCount = 0x00;
                }
            }
            else
            {
                SET_DP_RX1_AUX_AUTO_MODE();

                return;
            }
        }
        while((ucDpLaneCount == _DP_TWO_LANE) || (ucDpLaneCount == _DP_ONE_LANE));

        SET_DP_RX1_AUX_MANUAL_MODE();

        if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
           (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
        {
            ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x00, ucDpLinkRate);
            ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x01, ((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x60) | (ucDpLaneCount | _BIT7)));

            if(ucDpLaneCount == _DP_FOUR_LANE)
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x77);
            }
            else if(ucDpLaneCount == _DP_TWO_LANE)
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x00);
            }
            else
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x07);
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x00);
            }

            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x04, 0x01);

            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS_VBIOS);
        }

        SET_DP_RX1_AUX_AUTO_MODE();
    }

    SET_DP_RX1_AUX_AUTO_MODE();

    DebugMessageRx1("VBIOS_Link_Rate", ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00));
    DebugMessageRx1("VBIOS_Lane_Count", ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01));
}

//--------------------------------------------------
// Description : DP Link Rate Detect
// Input Value  : None
// Output Value : Link Rate
//--------------------------------------------------
BYTE ScalerDpRx1LinkRateDetect(void)
{
    BYTE ucDpLinkRate = 0;
    BYTE ucDpLinkRateDecide = _DP_LINK_NONE;

    do
    {
        if(ucDpLinkRate == 0)
        {
            if(((GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT) ? _HW_DP_D1_MAX_LINK_RATE_SUPPORT : _HW_DP_D2_MAX_LINK_RATE_SUPPORT) > ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x01))
            {
                ucDpLinkRate = ((GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT) ? _HW_DP_D1_MAX_LINK_RATE_SUPPORT : _HW_DP_D2_MAX_LINK_RATE_SUPPORT);
            }
            else
            {
                ucDpLinkRate = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x01);
            }
        }
        else if(ucDpLinkRate == _DP_LINK_HBR3)
        {
            ucDpLinkRate = _DP_LINK_HBR2;
        }
        else if(ucDpLinkRate == _DP_LINK_HBR2)
        {
            ucDpLinkRate = _DP_LINK_HBR;
        }
        else if(ucDpLinkRate == _DP_LINK_HBR)
        {
            ucDpLinkRate = _DP_LINK_RBR;
        }

        if(ScalerDpRx1LinkRateCheck(ucDpLinkRate) == _TRUE)
        {
            ucDpLinkRateDecide = ucDpLinkRate;

            break;
        }
    }
    while(ucDpLinkRate != _DP_LINK_RBR);

    return ucDpLinkRateDecide;
}

//--------------------------------------------------
// Description : Check Valid Lane
// Input Value  : ucDpLinkRate -> DP Link Rate
// Output Value : _TRUE -> Valid Signal
//--------------------------------------------------
bit ScalerDpRx1LinkRateCheck(BYTE ucDpLinkRate)
{
    WORD usDataStreamL0 = 0;
    BYTE ucDpLEQScanValue = _DP_RELOAD_LEQ_INITIAL;
    WORD usMeasureUpperBound = 0;
    WORD usMeasureLowerBound = 0;

    do
    {
        if(ucDpLEQScanValue == _DP_RELOAD_LEQ_INITIAL)
        {
            ucDpLEQScanValue = _DP_RELOAD_LEQ_LARGE;
        }
        else if(ucDpLEQScanValue == _DP_RELOAD_LEQ_LARGE)
        {
            ucDpLEQScanValue = _DP_RELOAD_LEQ_DEFAULT;
        }

        ScalerDpRx1SignalDetectInitial(ucDpLinkRate, ucDpLEQScanValue);

        usDataStreamL0 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

        switch(ucDpLinkRate)
        {
            case _DP_LINK_HBR2:

                usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_HBR2_SAVED;
                usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_HBR2_SAVED;

                break;

            case _DP_LINK_HBR:

                usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_HBR_SAVED;
                usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_HBR_SAVED;

                break;

            case _DP_LINK_RBR:

                usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_RBR_SAVED;
                usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_RBR_SAVED;

                break;

            default:

                break;
        }

        if((usDataStreamL0 < usMeasureUpperBound) && (usDataStreamL0 > usMeasureLowerBound))
        {
            return _TRUE;
        }
    }
    while(ucDpLEQScanValue != _DP_RELOAD_LEQ_DEFAULT);

    return _FALSE;
}

//--------------------------------------------------
// Description : DP Signal Detection Measure
// Input Value  : DP Lane Select, Measure target, Measure Period
// Output Value : Measure Counter
//--------------------------------------------------
WORD ScalerDpRx1SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod)
{
    WORD usDpMeasureCount = 0;

    // [1:0] freqdet_lane_sel
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ucDpLaneSel & (_BIT1 | _BIT0)));

    // [5] ln_ck_sel
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT5, enumDpMeasureTarget);

    switch(enumDpMeasurePeriod)
    {
        case _DP_MEASURE_PERIOD_1000_CYCLE:

#if(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_1)
            // [4:0] DP_XTAL_CYCLE = 5'b00011
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
#elif(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_2)
            // [0] DP_XTAL_CYCLE = 1'b0
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT0, 0x00);
#endif
            break;

        case _DP_MEASURE_PERIOD_2000_CYCLE:
        default:

#if(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_1)
            // [4:0] DP_XTAL_CYCLE = 5'b00100
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
#elif(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_2)
            // [0] DP_XTAL_CYCLE = 1'b1
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT0, _BIT0);
#endif
            break;
    }

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            usDpMeasureCount = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

            break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    return usDpMeasureCount;
}

//--------------------------------------------------
// Description : Check Valid Signal
// Input Value  : DP Link Rate and Lane Count
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx1SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
    WORD usDataStreamL0 = 0;
    WORD usDataStreamL1 = 0;
    WORD usDataStreamL2 = 0;
    WORD usDataStreamL3 = 0;
    WORD usMeasureUpperBound = 0;
    WORD usMeasureLowerBound = 0;

    // Scrambling Disable Check
    if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x02, _BIT5) == _BIT5)
    {
        return _TRUE;
    }

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
    CLR_DP_RX1_SIGNALDETECT_INT_HAPPENED();
#endif

    // Scrambling Disable Check
    if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x02, _BIT5) == _BIT5)
    {
        return _TRUE;
    }

    // Measure Data Stream Count
    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            usDataStreamL0 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;

        case _DP_TWO_LANE:

            usDataStreamL0 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL1 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;

        default:
        case _DP_FOUR_LANE:

            usDataStreamL0 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL1 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL2 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE2, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL3 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE3, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;
    }

    // Data Stream Count Upper Bound = (VCO target count) x 2 x 0.65
    // Data Stream Count Lower Bound = (VCO target count) x 2 x 0.55
    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_HBR2_SAVED;
            usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_HBR2_SAVED;

            break;

        case _DP_LINK_HBR:

            usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_HBR_SAVED;
            usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_HBR_SAVED;

            break;

        case _DP_LINK_RBR:

            usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_RBR_SAVED;
            usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_RBR_SAVED;

            break;

        default:

            break;
    }

    // Link Rate is a Unreasonable Value
    if((usMeasureUpperBound == 0) || (usMeasureLowerBound == 0))
    {
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
        if(GET_DP_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
        {
            return _FALSE;
        }
    }

    // Check Data Stream Count
    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            if((usDataStreamL0 > usMeasureUpperBound) || (usDataStreamL0 < usMeasureLowerBound))
            {
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
                {
                    return _FALSE;
                }
            }

            break;

        case _DP_TWO_LANE:

            if(((usDataStreamL0 > usMeasureUpperBound) || (usDataStreamL0 < usMeasureLowerBound)) ||
               ((usDataStreamL1 > usMeasureUpperBound) || (usDataStreamL1 < usMeasureLowerBound)))
            {
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
                {
                    return _FALSE;
                }
            }

            break;

        default:
        case _DP_FOUR_LANE:

            if(((usDataStreamL0 > usMeasureUpperBound) || (usDataStreamL0 < usMeasureLowerBound)) ||
               ((usDataStreamL1 > usMeasureUpperBound) || (usDataStreamL1 < usMeasureLowerBound)) ||
               ((usDataStreamL2 > usMeasureUpperBound) || (usDataStreamL2 < usMeasureLowerBound)) ||
               ((usDataStreamL3 > usMeasureUpperBound) || (usDataStreamL3 < usMeasureLowerBound)))
            {
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
                {
                    return _FALSE;
                }
            }

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : VBIOS Lane Adjust
// Input Value  : DP Lane Count
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpRx1VBIOSMSACheck(bit bDeskewEnhanced)
{
    bit bMSACheckResult = _FALSE;

    do
    {
        // De-Skew Circuit Reset
        ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), (((bDeskewEnhanced == _TRUE) ? _BIT7 : 0x00) | _BIT6));

        // Mac Reset After Link Clock Stable
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

        // SEC Reset
        ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT4, _BIT4);
        ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT4, 0x00);

        // Wait Two Frame Time to Get MSA
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        // Pop up Main Stream Attributes
        ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

        // Get Nvid
        ScalerRead(PB6_1D_MSA_NVID_0, 3, pData, _AUTOINC);

        // Get Hactive
        ScalerRead(PB6_0C_MSA_HWD_0, 2, &pData[4], _AUTOINC);

        // Get Vactive
        ScalerRead(PB6_16_MSA_VHT_0, 2, &pData[6], _AUTOINC);

        // Get Hstart
        ScalerRead(PB6_0A_MSA_HST_0, 2, &pData[8], _AUTOINC);

        // Get Vstart
        ScalerRead(PB6_14_MSA_VST_0, 2, &pData[10], _AUTOINC);

        if(((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) != 0x00) &&
           (PDATA_WORD(2) != 0x00) && (PDATA_WORD(3) != 0x00) && (PDATA_WORD(4) != 0x00) && (PDATA_WORD(5) != 0x00) &&
           (PDATA_WORD(2) > PDATA_WORD(4)) && (PDATA_WORD(3) > PDATA_WORD(5)))
        {
            bMSACheckResult = _TRUE;

            break;
        }
    }while(ScalerDpRx1ChangeSrambleSeed() == _TRUE);

#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
    bMSACheckResult = ScalerDpRx1VbiosAssrCheck(bMSACheckResult);
#endif

    return bMSACheckResult;
}

#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : VBIOS ASSR Detect
// Input Value  : bMSACheckResult
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpRx1VbiosAssrCheck(bit bMSACheckResult)
{
    switch(GET_DP_EMBEDDED_SWITCH_SELECT())
    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

#if(_D1_DP_ASSR_MODE_SUPPORT == _ON)

            SET_DP_RX1_AUX_MANUAL_MODE();

            if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
               (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
            {
                if(bMSACheckResult == _TRUE)
                {
                    if(ScalerGetBit(PB_07_SCRAMBLE_CTRL, _BIT4) == _BIT4)
                    {
                        ScalerDpRx1SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, _BIT0);
                    }
                    else
                    {
                        ScalerDpRx1SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, 0x00);
                    }
                }
                else
                {
                    // Set Scramble Seed = Default 0xFFFF
                    ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);

                    ScalerDpRx1SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, 0x00);
                }
            }
            else
            {
                bMSACheckResult = _FALSE;
            }

            SET_DP_RX1_AUX_AUTO_MODE();

#endif

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

        case _D2_INPUT_PORT:

#if(_D2_DP_ASSR_MODE_SUPPORT == _ON)

            SET_DP_RX1_AUX_MANUAL_MODE();

            if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
               (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
            {
                if(bMSACheckResult == _TRUE)
                {
                    if(ScalerGetBit(PB_07_SCRAMBLE_CTRL, _BIT4) == _BIT4)
                    {
                        ScalerDpRx1SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, _BIT0);
                    }
                    else
                    {
                        ScalerDpRx1SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, 0x00);
                    }
                }
                else
                {
                    // Set Scramble Seed = Default 0xFFFF
                    ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);

                    ScalerDpRx1SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, 0x00);
                }
            }
            else
            {
                bMSACheckResult = _FALSE;
            }

            SET_DP_RX1_AUX_AUTO_MODE();

#endif

            break;
#endif

        default:
            break;
    }

    return bMSACheckResult;
}
#endif

//--------------------------------------------------
// Description  : Change Dp Scramble Seed
// Input Value  : None
// Output Value : False --> Change Scrmable Seed Finish
//--------------------------------------------------
bit ScalerDpRx1ChangeSrambleSeed(void)
{
    switch(GET_DP_EMBEDDED_SWITCH_SELECT())
    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

#if(_D1_DP_ASSR_MODE_SUPPORT == _ON)

            if(ScalerGetBit(PB_07_SCRAMBLE_CTRL, _BIT4) == 0x00)
            {
                // Try Scramble Seed = 0xFFFE
                ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);

                return _TRUE;
            }
            else
#endif
            {
                return _FALSE;
            }

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

        case _D2_INPUT_PORT:

#if(_D2_DP_ASSR_MODE_SUPPORT == _ON)

            if(ScalerGetBit(PB_07_SCRAMBLE_CTRL, _BIT4) == 0x00)
            {
                // Try Scramble Seed = 0xFFFE
                ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);

                return _TRUE;
            }
            else
#endif
            {
                return _FALSE;
            }

            break;
#endif

        default:

            return _FALSE;

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description : Initial Signal check
// Input Value  : DP Link Rate and DP Reload LEQ Scan Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue)
{
    // [3:2] reg_dp_bbpd_sel --> Default set ACDR to PCB Lane0
    ScalerSetBit(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), (GET_DP_RX1_PCB_LANE0_MAPPING() << 2));

    ///////////////
    // RX CMU EN //
    ///////////////

    // Disable RX_EN, CDR_EN
    ScalerSetByte(P1D_20_CMU_03, 0x00);

    // Enable RX_EN, CDR_EN
    ScalerSetByte(P1D_20_CMU_03, 0xFF);


    ////////////////
    // EQ Setting //
    ////////////////

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR:

            // [7] le_lowgain_highboost = 1'b0 --> Disable LE High-boost Mode
            ScalerSetBit(P1D_2B_KOFFSET_05, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // [7:5] le_isel = 3'b010 --> LE Peaking = 1.7Gbps
            ScalerSetBit(P1D_2C_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

            // [7:5] le_rlsel = 3'b001 --> LE Peaking = 1.7Gbps
            ScalerSetBit(P1D_2D_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            switch(ucDpLEQScanValue)
            {
                case _DP_RELOAD_LEQ_DEFAULT:

                    // LE Initial = 10
                    ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x0A);
                    ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x0A);
                    ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x0A);
                    ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x0A);

                    break;

                case _DP_RELOAD_LEQ_LARGE:
                default:

                    // LE Initial = 15
                    ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x0F);
                    ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x0F);
                    ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x0F);
                    ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x0F);

                    break;
            }

            break;

        case _DP_LINK_RBR:
        default:

            // [7] le_lowgain_highboost = 1'b0 --> Enable LE High-boost Mode
            ScalerSetBit(P1D_2B_KOFFSET_05, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // [7:5] le_isel = 3'b000 --> LE Peaking = 900Mbps
            ScalerSetBit(P1D_2C_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // [7:5] le_rlsel = 3'b011 --> LE Peaking = 900Mbps
            ScalerSetBit(P1D_2D_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

            // LE Initial = 10
            ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x0A);
            ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x0A);
            ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x0A);
            ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x0A);

            break;
    }

    // Tap0 Initial Value = 15
    ScalerSetByte(P1D_A4_L0_INIT_2, 0x0F);
    ScalerSetByte(P1D_B4_L1_INIT_2, 0x0F);
    ScalerSetByte(P1D_C4_L2_INIT_2, 0x0F);
    ScalerSetByte(P1D_D4_L3_INIT_2, 0x0F);

    // [2:0] tap_en = 3'b001 --> Eable Tap0 Passive EQ
    ScalerSetBit(P1D_2E_ANA_CDR_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // Delay Time us [85,x]
    DELAY_XUS(85);

    // [7] en_fore_offset = 1'b0 --> Disable EQ foreground Offset Calibration
    // [6] fore_off_autok = 1'b1 --> Enable EQ foreground Offset Calibration Auto Mode
    ScalerSetBit(P1D_2A_KOFFSET_04, ~(_BIT7 | _BIT6), _BIT6);

    // Toggle en_fore_offset
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x]
    DELAY_XUS(85);

    // [4:0] reg_fore_off_adjr_Lane0~3
    // if Auto K = 0 ~ 15 Reload Auto K + 8, Auto K = 16 ~ 31 Reload Auto K - 8
    if((ScalerGetByte(P1D_26_KOFFSET_00) & 0x1F) > 15)
    {
        ScalerSetBit(P1D_2A_KOFFSET_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_26_KOFFSET_00) & 0x1F) - 8));
    }
    else
    {
        ScalerSetBit(P1D_2A_KOFFSET_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_26_KOFFSET_00) & 0x1F) + 8));
    }

    if((ScalerGetByte(P1D_27_KOFFSET_01) & 0x1F) > 15)
    {
        ScalerSetBit(P1D_2B_KOFFSET_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_27_KOFFSET_01) & 0x1F) - 8));
    }
    else
    {
        ScalerSetBit(P1D_2B_KOFFSET_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_27_KOFFSET_01) & 0x1F) + 8));
    }

    if((ScalerGetByte(P1D_28_KOFFSET_02) & 0x1F) > 15)
    {
        ScalerSetBit(P1D_2C_KOFFSET_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_28_KOFFSET_02) & 0x1F) - 8));
    }
    else
    {
        ScalerSetBit(P1D_2C_KOFFSET_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_28_KOFFSET_02) & 0x1F) + 8));
    }

    if((ScalerGetByte(P1D_29_KOFFSET_03) & 0x1F) > 15)
    {
        ScalerSetBit(P1D_2D_KOFFSET_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_29_KOFFSET_03) & 0x1F) - 8));
    }
    else
    {
        ScalerSetBit(P1D_2D_KOFFSET_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_29_KOFFSET_03) & 0x1F) + 8));
    }

    // [6] fore_off_autok = 1'b0 --> Enable EQ foreground Offset Calibration Manual Mode
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description : check DP 8b/10b Decode Error
// Input Value  : None
// Output Value : True --> ok, False --> 8b/10b Decode Error
//--------------------------------------------------
bit ScalerDpRx1DecodeCheck(void)
{
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)

    if(GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE)
    {
        if(GET_DP_RX1_SOURCE_TYPE_JUDGE() == _FALSE)
        {
#if(_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON)
            if(ScalerDpRx1LaneValidCheck() == _FALSE)
            {
                return _TRUE;
            }
#else
            return _TRUE;
#endif
        }
    }

#endif

    pData[1] = 3;

    while(pData[1] > 0)
    {
        // Clear 8b/10b Decode Error Flag
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [150,x]
        DELAY_XUS(150);

        switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                {
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if(((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT1 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2)) == 0x00)))
                {
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:

                if(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
                {
                    return _TRUE;
                }

                break;

            default:

                return _FALSE;

                break;
        }

        pData[1]--;
    }

    DebugMessageRx1("7. DP 8b/10b Decode Error", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description : check DFE Coef
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx1DFECheck(void)
{
    // DFECheck is not adopted for RL6492 Rx1
    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Display Format Generator Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1DisplayFormatSetting(void)
{
    BYTE ucOddFlg = 0;
    WORD usDpVtotal = 0;
    WORD usDpHactive = 0;
    DWORD ulStreamClkValue = 0;
    DWORD ulVBs2BsCount = 0;

#if(_DP_FREESYNC_SUPPORT == _ON)
    WORD usHBs2BsCount = 0;
    DWORD ulDpMvidValue = 0;
    DWORD ulDpNvidValue = 0;
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        // Restore VBs2Bs Count
        ulVBs2BsCount = g_stDpRx1LinkInfo.ulVBsToBsCountN;
    }
    else
#endif
    {
        // Measurement Enable
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB5_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
        {
            return _FALSE;
        }

        // Pop up The result
        SET_DP_RX1_MEASURE_POP_UP();

        // Measurement Disable
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);

        // VBs2BS count in GDI clk
        ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB5_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB5_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB5_5A_MN_MEAS_VLN_L)));
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // Get IVfreq
        PDATA_DWORD(0) = ((DWORD)_GDI_CLK_KHZ * 1000 / (ulVBs2BsCount / 10));

        if((PDATA_DWORD(0) < (_PANEL_FREESYNC_MIN_FRAME_RATE - _FRAME_SYNC_MARGIN)) || (PDATA_DWORD(0) > (_PANEL_FREESYNC_MAX_FRAME_RATE + _FRAME_SYNC_MARGIN)))
        {
            return _FALSE;
        }

        // HBs2Bs count in Link Clk / 2
        usHBs2BsCount = (((DWORD)ScalerGetByte(PB5_5B_MN_MEAS_HLN_M)) << 8) | ((DWORD)ScalerGetByte(PB5_5C_MN_MEAS_HLN_L));

        // VTotal in line, Link Clk / 2 : (Link Rate * 27 / 2)
        usDpVtotal = ulVBs2BsCount * (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2) / usHBs2BsCount * 1000 / _GDI_CLK_KHZ;

        ulDpMvidValue = ((((DWORD)ScalerGetByte(PB6_1A_MSA_MVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1B_MSA_MVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1C_MSA_MVID_2)));

        ulDpNvidValue = ((((DWORD)ScalerGetByte(PB6_1D_MSA_NVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1E_MSA_NVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1F_MSA_NVID_2)));

        // [5] ln_ck_sel = 1'b1 -> CDR Clock
        // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

        // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
        ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

        // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
        ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

        // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

        // Waiting for Measure Done
        ScalerTimerDelayXms(2);

        PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

        PDATA_DWORD(0) = ((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ;

        // Calculate streamclk
        ulStreamClkValue = ((DWORD)ulDpMvidValue * (PDATA_DWORD(0) / ulDpNvidValue) + (PDATA_DWORD(0) % ulDpNvidValue * 100 / ulDpNvidValue * (DWORD)ulDpMvidValue / 100));
    }
    else
#endif
    {
        usDpVtotal = ((((WORD)ScalerGetByte(PB6_10_MSA_VTTE_0)) << 8) | ((WORD)ScalerGetByte(PB6_11_MSA_VTTE_1)));

        // Calculate streamclk (Unit is Hz)
        ulStreamClkValue = (((((((DWORD)ScalerGetByte(PB6_08_MSA_HTT_0)) << 8) | ((WORD)ScalerGetByte(PB6_09_MSA_HTT_1))) * ((DWORD)usDpVtotal) * 100) / ulVBs2BsCount) * _GDI_CLK_KHZ * 10);
    }

    // Input Pixel CLK Unit is 0.1 M
    SET_INPUT_PIXEL_CLK(ulStreamClkValue / 100000);

    // Disable Generate Display Format
    ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT7, 0x00);

    // DP Display Format Generator Reset
    ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT7, 0x00);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
    {
        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);
    }

    // Set Vactive
    ScalerRead(PB6_16_MSA_VHT_0, 2, &pData[4], _AUTOINC);

    if(PDATA_WORD(2) > _12_BIT)
    {
        return _FALSE;
    }
    else
    {
        ScalerSetBit(PB5_4D_MN_DPF_VHT_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(2)));
        ScalerSetByte(PB5_4E_MN_DPF_VHT_L, LOBYTE(PDATA_WORD(2)));
    }

    // Set Hactive
    ScalerRead(PB6_0C_MSA_HWD_0, 2, pData, _AUTOINC);

    if(PDATA_WORD(0) > _12_BIT)
    {
        return _FALSE;
    }
    else
    {
        ScalerSetBit(PB5_45_MN_DPF_HWD_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
        ScalerSetByte(PB5_46_MN_DPF_HWD_L, LOBYTE(PDATA_WORD(0)));
    }

    usDpHactive = PDATA_WORD(0);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // HTotal in Pixel Clk, Link Clk / 2 : (Link Rate * 27 / 2)
        WORD usDpHtotal = (DWORD)usHBs2BsCount * (GET_INPUT_PIXEL_CLK() / 10) / (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2);

        // Set Htotal
        if(usDpHtotal > _12_BIT)
        {
            return _FALSE;
        }
        else
        {
            ScalerSetBit(PB5_41_MN_DPF_HTT_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usDpHtotal));
            ScalerSetByte(PB5_42_MN_DPF_HTT_L, LOBYTE(usDpHtotal));
        }

        // Set Hstart
        if(_DP_DE_ONLY_MODE_HSTART > _12_BIT)
        {
            return _FALSE;
        }
        else
        {
            ScalerSetBit(PB5_43_MN_DPF_HST_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_DP_DE_ONLY_MODE_HSTART));
            ScalerSetByte(PB5_44_MN_DPF_HST_L, LOBYTE(_DP_DE_ONLY_MODE_HSTART));
        }

        // Set HSP => Positive
        ScalerSetBit(PB5_47_MN_DPF_HSW_M, ~_BIT7, 0x00);

        // Set HSW
        ScalerSetByte(PB5_48_MN_DPF_HSW_L, (_DP_DE_ONLY_MODE_HSW > _8_BIT) ? 0xFF : LOBYTE(_DP_DE_ONLY_MODE_HSW));

        // Set Vstart
        if(_DP_DE_ONLY_MODE_VSTART > _10_BIT)
        {
            return _FALSE;
        }
        else
        {
            ScalerSetBit(PB5_4B_MN_DPF_VST_M, ~(_BIT1 | _BIT0), HIBYTE(_DP_DE_ONLY_MODE_VSTART));
            ScalerSetByte(PB5_4C_MN_DPF_VST_L, LOBYTE(_DP_DE_ONLY_MODE_VSTART));
        }

        // Set VSP => Positive
        ScalerSetBit(PB5_4F_MN_DPF_VSW_M, ~_BIT7, 0x00);

        // Set VSW
        ScalerSetByte(PB5_50_MN_DPF_VSW_L, (_DP_DE_ONLY_MODE_VSW > _8_BIT) ? 0xFF : LOBYTE(_DP_DE_ONLY_MODE_VSW));

        PDATA_WORD(0) = GET_DPRX1_BS_TO_HS_DELAY(usDpHtotal);

        // Set HBs2Bs
        ScalerSetByte(PB5_38_BS2HS_0, pData[0]);
        ScalerSetByte(PB5_39_BS2HS_1, pData[1]);

        ScalerDpRx1InterlaceCheck(&usDpVtotal, &ucOddFlg);

        // Set DE Only Mode Vsync Front Porch
        ScalerSetByte(PB5_40_VS_FRONT_PORCH, GET_DP_RX1_VFRONT_PORCH());

        // Set DE Only Mode
        ScalerSetBit(PB5_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), _BIT4);

        // Choose Frame start BE to Reset FIFO
        ScalerSetBit(PB5_20_PG_CTRL_0, ~_BIT5, 0x00);

        // Set DP FREESYNC Mode Enable
        ScalerSetBit(PB5_F0_DP_RSV0, ~_BIT0, _BIT0);

        ScalerDpRx1SetFREESYNCMsaForLut(usDpHtotal);

        DebugMessageRx1("FREESYNC Mode Enabled!!", ScalerGetByte(PB5_30_DPF_CTRL_0));
    }
    else
#endif
    {
        DWORD ulBs2VsDelay = 0;

        // Set Htotal
        ScalerRead(PB6_08_MSA_HTT_0, 2, &pData[2], _AUTOINC);

        if(PDATA_WORD(1) > _12_BIT)
        {
            return _FALSE;
        }
        else
        {
            ScalerSetBit(PB5_41_MN_DPF_HTT_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(1)));
            ScalerSetByte(PB5_42_MN_DPF_HTT_L, LOBYTE(PDATA_WORD(1)));
        }

        // Get HSW
        pData[4] = ScalerGetBit(PB6_0E_MSA_HSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        pData[5] = ScalerGetByte(PB6_0F_MSA_HSW_1);

        // Get HSW min by Measure clock
        PDATA_WORD(3) = ((DWORD) _DP_HSYNC_WIDTH_MEASURE_COUNTER * GET_INPUT_PIXEL_CLK() * 100) / _MEASURE_CLK + 1;

        // Check HSW <= HSW min
        if(PDATA_WORD(2) <= PDATA_WORD(3))
        {
            // Check if H porch is more than HSW min
            if((PDATA_WORD(1) - usDpHactive) >= PDATA_WORD(3))
            {
                // HSW = HSW min
                PDATA_WORD(2) = PDATA_WORD(3);
            }
            else
            {
                // HSW = Max H Porch
                PDATA_WORD(2) = (PDATA_WORD(1) - usDpHactive);
            }
        }

        // DPF H Front Porch must not be less than 8 (HW constraint)
        // Check if H porch is more than 8
        if((PDATA_WORD(1) - usDpHactive - PDATA_WORD(2)) <= _DP_HSYNC_FRONT_PORCH)
        {
            // HSW < HSW min
            if(PDATA_WORD(2) < PDATA_WORD(3))
            {
                // Hstart = HSW
                PDATA_WORD(4) = PDATA_WORD(2);
            }
            else if((PDATA_WORD(1) - usDpHactive - PDATA_WORD(3) >= _DP_HSYNC_FRONT_PORCH))
            {
                // HSW = H porch - _DP_HSYNC_FRONT_PORCH
                PDATA_WORD(2) = PDATA_WORD(1) - usDpHactive - _DP_HSYNC_FRONT_PORCH;

                // Hstart = HSW
                PDATA_WORD(4) = PDATA_WORD(2);
            }
            else
            {
                // HSW = HSW min
                PDATA_WORD(2) = PDATA_WORD(3);

                // Hstart = HSW min
                PDATA_WORD(4) = PDATA_WORD(3);
            }
        }
        else
        {
            // Hstart = Htotal - Hactive - _DP_HSYNC_FRONT_PORCH
            PDATA_WORD(4) = PDATA_WORD(1) - usDpHactive - _DP_HSYNC_FRONT_PORCH;
        }

        // Set HSP => positive
        ScalerSetBit(PB5_47_MN_DPF_HSW_M, ~_BIT7, 0x00);

        // Set HSW
        ScalerSetByte(PB5_48_MN_DPF_HSW_L, (PDATA_WORD(2) > _8_BIT) ? 0xFF : LOBYTE(PDATA_WORD(2)));

        // Set Hstart
        if(PDATA_WORD(4) > _12_BIT)
        {
            return _FALSE;
        }
        else
        {
            ScalerSetBit(PB5_43_MN_DPF_HST_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(4)));
            ScalerSetByte(PB5_44_MN_DPF_HST_L, LOBYTE(PDATA_WORD(4)));
        }

        DebugMessageRx1("###Origin usVTotal###", usDpVtotal);

        if(ScalerDpRx1InterlaceCheck(&usDpVtotal, &ucOddFlg) == _TRUE) // Interlace
        {
            DebugMessageRx1("7. IIIIIInterLace Vtotal", usDpVtotal);
        }
        else // Progressive
        {
            DebugMessageRx1("7. PPPPProgressive", 0);
        }

        // Set Vtotal
        if(usDpVtotal > _12_BIT)
        {
            return _FALSE;
        }
        else
        {
            ScalerSetBit(PB5_49_MN_DPF_VTT_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usDpVtotal));
            ScalerSetByte(PB5_4A_MN_DPF_VTT_L, LOBYTE(usDpVtotal));
        }

        // Get Vactive
        ScalerRead(PB6_16_MSA_VHT_0, 2, &pData[4], _AUTOINC);

        // V Front porch must not be less than 2 because of V scaling down.
        // Set Vstart -> (Vtotal - Vactive - Frontporch)
        PDATA_WORD(0) = usDpVtotal - PDATA_WORD(2) - GET_DP_RX1_VFRONT_PORCH();

        if(PDATA_WORD(0) > _10_BIT)
        {
            return _FALSE;
        }
        else
        {
            ScalerSetBit(PB5_4B_MN_DPF_VST_M, ~(_BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
            ScalerSetByte(PB5_4C_MN_DPF_VST_L, LOBYTE(PDATA_WORD(0)));
        }

        // Set VSP => Positive
        ScalerSetBit(PB5_4F_MN_DPF_VSW_M, ~_BIT7, 0x00);

        // Set VSW
        ScalerSetByte(PB5_50_MN_DPF_VSW_L, (_DP_VSYNC_WIDTH > _8_BIT) ? 0xFF : LOBYTE(_DP_VSYNC_WIDTH));

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
        if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
        {
            // Set Odd Field BS to VS Delay
            ScalerSetBit(PB5_35_OVBLK2VS_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayOdd >> 16));
            ScalerSetByte(PB5_36_OVBLK2VS_M, (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayOdd >> 8));
            ScalerSetByte(PB5_37_OVBLK2VS_L, (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayOdd >> 0));

            // Set Even Field BS to VS Delay
            ScalerSetBit(PB5_32_EVBLK2VS_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayEven >> 16));
            ScalerSetByte(PB5_33_EVBLK2VS_M, (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayEven >> 8));
            ScalerSetByte(PB5_34_EVBLK2VS_L, (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayEven >> 0));
        }
        else
#endif
        {
            ulBs2VsDelay = ScalerDpRx1GetBStoVSDelay();

            // Set Odd Field BS to VS Delay
            if(ulBs2VsDelay > _20_BIT)
            {
                return _FALSE;
            }
            else
            {
                ScalerSetBit(PB5_35_OVBLK2VS_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(ulBs2VsDelay >> 16));
                ScalerSetByte(PB5_36_OVBLK2VS_M, (BYTE)(ulBs2VsDelay >> 8));
                ScalerSetByte(PB5_37_OVBLK2VS_L, (BYTE)(ulBs2VsDelay >> 0));
            }

            if((bit)ucOddFlg == _TRUE)
            {
                // Get Htotal
                ScalerRead(PB6_08_MSA_HTT_0, 2, &pData[10], _AUTOINC);

                // BStoVSDelay = BStoVSDelay + (Link Clk * 256 / Stream Clk) * ((DWORD)Htotal) / 256;
                ulBs2VsDelay += ((((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270UL) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(5)) / 256 / 2;
            }

            // Set Even Field BS to VS Delay
            if(ulBs2VsDelay > _20_BIT)
            {
                return _FALSE;
            }
            else
            {
                ScalerSetBit(PB5_32_EVBLK2VS_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(ulBs2VsDelay >> 16));
                ScalerSetByte(PB5_33_EVBLK2VS_M, (BYTE)(ulBs2VsDelay >> 8));
                ScalerSetByte(PB5_34_EVBLK2VS_L, (BYTE)(ulBs2VsDelay >> 0));
            }
        }

        // Choose VS Rising to Reset FIFO
        ScalerSetBit(PB5_20_PG_CTRL_0, ~_BIT5, 0x00);

        // Set DP FREESYNC Mode Disable
        ScalerSetBit(PB5_F0_DP_RSV0, ~_BIT0, 0x00);

        // Set full last line Mode
        ScalerSetBit(PB5_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

        DebugMessageRx1("FREESYNC Mode Disabled", ScalerGetByte(PB5_30_DPF_CTRL_0));
    }

    // Double Buffer to Apply Display Format Setting (RL6492 has no double buffer for display format setting)
    // ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT6, _BIT6);

    ScalerDpRx1VideoSetting();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDpRx1InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg)
{
    DWORD ulLinkClk = 0;
    WORD usTempVTotal = *pusVTotal;
    WORD usHTotalCount = 0;

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _OFF)
    WORD usVsyncWidth = 0;
    WORD usVstart = 0;
    WORD usVactive = 0;
#endif

    // Set Vfront Porch
    SET_DP_RX1_VFRONT_PORCH(_DP_VSYNC_FRONT_PORCH);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        return _FALSE;
    }
#endif

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Field inverse disable and Clr Fake Interlace Flag
    ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));
#else
    ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), _BIT0);
#endif

    // =========== Link Clock Measure Start ===========
    PDATA_WORD(0) = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE0, _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_2000_CYCLE);

    if(PDATA_WORD(0) == 0)
    {
        if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR3)
        {
            PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR3;
        }
        else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR2;
        }
        else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
        {
            PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR;
        }
        else // Both Default && _DP_LINK_RBR Case
        {
            PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_RBR;
        }
    }

    PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

    // Link Clk in KHz
    ulLinkClk = (PDATA_DWORD(0) / 1000);

    DebugMessageRx1("Current Link Clk", ulLinkClk);
    // =========== Link Clock Measure End ===========

    // =========== Continue Measure Two Frame Start ===========
    // Start to Measure Vertical BS to BS Counter by GDI Clock
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB5_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The result
    SET_DP_RX1_MEASURE_POP_UP();

    // Get Measure Result
    ScalerRead(PB5_58_MN_MEAS_CTRL, 3, &pData[5], _AUTOINC);

    // Delay 2ms To Get VBID
    ScalerTimerDelayXms(2);

    // Get VBID
    ScalerRead(PB6_01_DP_VBID, 1, &pData[1], _NON_AUTOINC);

    // Delay 1 frame
    ScalerTimerDelayXms((((PDATA_DWORD(1) & 0x001FFFFF) / (_GDI_CLK_KHZ)) + 2));

    // Pop up Measure Result
    SET_DP_RX1_MEASURE_POP_UP();

    // Get Measure Result
    ScalerRead(PB5_58_MN_MEAS_CTRL, 3, &pData[9], _AUTOINC);

    // Get Measure Htotal Counts
    ScalerRead(PB5_5B_MN_MEAS_HLN_M, 2, &pData[12], _AUTOINC);

    // Get VBID
    ScalerRead(PB6_01_DP_VBID, 1, &pData[2], _NON_AUTOINC);

    PDATA_DWORD(1) = (PDATA_DWORD(1) & 0x001FFFFF);
    PDATA_DWORD(2) = (PDATA_DWORD(2) & 0x001FFFFF);

    // Disable Measure Block
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    // =========== Continue Measure Two Frame End ===========

    // Convert HTotal Count from 1/2 Link Clk to GDI Clk
    usHTotalCount = ((DWORD)PDATA_WORD(6) * _GDI_CLK_KHZ * 2 + (ulLinkClk >> 1)) / ulLinkClk;

    DebugMessageRx1("HTotal Count", usHTotalCount);

    // if VTotal Difference > 1/2 HTotal
    if((ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))) > (usHTotalCount / 2))
    {
        if(PDATA_DWORD(1) < PDATA_DWORD(2))
        {
            usTempVTotal = ((PDATA_DWORD(1) + (usHTotalCount >> 1)) / usHTotalCount);
        }
        else
        {
            usTempVTotal = ((PDATA_DWORD(2) + (usHTotalCount >> 1)) / usHTotalCount);
        }

        *pucOddFlg = _TRUE;
    }
    else
    {
        *pucOddFlg = _FALSE;
    }

    DebugMessageRx1("####Calculated usVTotal####", usTempVTotal);

    DebugMessageRx1("7. DelayTime", (((PDATA_DWORD(1) & 0x000FFFFF) / (_GDI_CLK_KHZ)) + 2));
    DebugMessageRx1("7. Frame[N] VBS2BS Counter", PDATA_DWORD(1));
    DebugMessageRx1("7. Frame[N + 1] VBS2BS Counter", PDATA_DWORD(2));
    DebugMessageRx1("7. Frame diff", (ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))));

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Check N and N+1 Frame Vs2Vs Count
    if((*pucOddFlg) == _TRUE)
    {
        // Enable DP Interlace
        ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

        // Enable Field Sync by BE
        ScalerSetBit(PB5_F1_DP_RSV1, ~_BIT0, _BIT0);

        // HW Check Interlace
        if(ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, _BIT5) == _BIT5)
        {
            // Field reference HW
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);
        }
        else
        {
            // Field reference VBID
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);
        }

        // Set Vtt odd fw mode
        SET_DP_RX1_INTERLACE_VTT_FW_MODE(_ODD);

        *pusVTotal = usTempVTotal;

        return _TRUE;
    }
    else
    {
        // Check VBID Field Toggle and VBID Interlace Info
        if(((pData[1] & _BIT1) != (pData[2] & _BIT1)) && (ScalerGetBit(PB6_01_DP_VBID, _BIT2) == _BIT2))
        {
            // Enable DP Interlace
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

            // Field reference VBID
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

            // Enable Field Sync by BE
            ScalerSetBit(PB5_F1_DP_RSV1, ~_BIT0, _BIT0);

            // Set Vtt Even fw mode
            SET_DP_RX1_INTERLACE_VTT_FW_MODE(_EVEN);

            *pusVTotal = usTempVTotal;

            return _TRUE;
        }

        // Enable DP Progressive Mode
        ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), 0x00);

        // Field reference VBID
        ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

        // Enable Field Sync by VBID
        ScalerSetBit(PB5_F1_DP_RSV1, ~_BIT0, 0x00);

        // Set Vtt Even fw mode
        SET_DP_RX1_INTERLACE_VTT_FW_MODE(_EVEN);

        return _FALSE;
    }
#else
    if(ScalerGetBit(PB6_01_DP_VBID, _BIT2) == _BIT2) // Interlace
    {
        // Enable DP Interlace
        ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

        if((*pucOddFlg) == _FALSE)
        {
            // Disable DP Interlace
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), 0x00);
        }

        // Get VSW
        usVsyncWidth = ((WORD)ScalerGetByte(PB6_18_MSA_VSW_0) << 8) | ScalerGetByte(PB6_19_MSA_VSW_1);
        usVsyncWidth &= 0x7FFF;

        // Get VStart
        usVstart = ((WORD)ScalerGetByte(PB6_14_MSA_VST_0) << 8) | ScalerGetByte(PB6_15_MSA_VST_1);

        // usVbackporch = usVstart - Fixed V-Sync Pulse Width, usVbackporch > usVsyncWidth + 2 lines, here 2 lines is for V-Sync Falling edge to DEN Rising Edge distance margion
        if(((pData[1] & _BIT1) != (pData[2] & _BIT1)) && (usVstart > (usVsyncWidth + _DP_VSYNC_WIDTH + 2)))
        {
            // Field Information reference to VBID
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

            // Get Vactive
            usVactive = ((WORD)ScalerGetByte(PB6_16_MSA_VHT_0) << 8) | ScalerGetByte(PB6_17_MSA_VHT_1);

            // Set Front Porch = VTotal - Active height - MSA V Start + V Sync Pulse Width
            SET_DP_RX1_VFRONT_PORCH(usTempVTotal - usVactive - usVstart + usVsyncWidth);

            if((ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, _BIT0) == 0x00) &&
               ((((pData[1] & _BIT1) == _BIT1) && ((pData[2] & _BIT1) == 0x00) && (PDATA_DWORD(1) < PDATA_DWORD(2))) ||
                (((pData[1] & _BIT1) == 0x00) && ((pData[2] & _BIT1) == _BIT1) && (PDATA_DWORD(1) > PDATA_DWORD(2)))))
            {
                // Field inverse enable
                ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), _BIT4);
            }
        }
        else
        {
            // Field reference HW
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);
        }

        *pusVTotal = usTempVTotal;

        return _TRUE;
    }
    else if((ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))) > (usHTotalCount / 2))
    {
        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        if(ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, _BIT0) == _BIT0)
        {
            DebugMessageRx1("Fake Interlace", 0);
            *pucOddFlg = _FALSE;
        }
        else
        {
            // Enable interlace mode, field reference HW
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), (_BIT7 | _BIT6));

            *pusVTotal = usTempVTotal;

            return _TRUE;
        }
    }

    // Disable DP Interlace
    ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), 0x00);

    return _FALSE;
#endif
}

//--------------------------------------------------
// Description  : DP Stream Clk PLL Setting
// Input Value  : None
// Output Value : True --> Stream CLK Regen. ok
//--------------------------------------------------
bit ScalerDpRx1StreamClkRegenerate(void)
{
    DWORD ulStreamClkValue = 0;
    SDWORD lOffsetValue = 0;
    DWORD ulpllm = 0;
    DWORD ulXtal_clk = 0;
    WORD usDpHtotal = 0;
    WORD usDpVtotal = 0;
    DWORD ulVBs2BsCount = 0;
    DWORD ulDpNvidValue = 0;
    BYTE ucpllo = 0;
    BYTE ucdivs = 0;
    BYTE ucdiv2 = 0;
    BYTE ucplln = 0;
    BYTE ucBuf = 0;
    BYTE ucdiv_pllo = 0;
    BYTE ucdiv_divs = 0;
    BYTE ucFrameTime = 0;
    DWORD ul2ndICode = 0x02;
    DWORD ul2ndPCode = 0;
    DWORD ulpllmDelta = 0;

#if(_DP_FREESYNC_SUPPORT == _ON)
    DWORD ulDpMvidValue = 0;
#endif

    // PLL Input Clock select to Link Clock, Output Clock Select to PLL Clock, Double Buffer.
    ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

    ulDpNvidValue = ((((DWORD)ScalerGetByte(PB6_1D_MSA_NVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1E_MSA_NVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1F_MSA_NVID_2)));

    usDpHtotal = ((((WORD)ScalerGetByte(PB5_41_MN_DPF_HTT_M)) << 8) | ((WORD)ScalerGetByte(PB5_42_MN_DPF_HTT_L)));

    usDpVtotal = ((((WORD)ScalerGetByte(PB5_49_MN_DPF_VTT_M)) << 8) | ((WORD)ScalerGetByte(PB5_4A_MN_DPF_VTT_L)));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Waiting for Measure Done
    ScalerTimerDelayXms(2);

    if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));
    }
    else
    {
        if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = 0x4E20;
        }
        else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
        {
            PDATA_WORD(0) = 0x2710;
        }
        else // Both Default && _DP_LINK_RBR Case
        {
            PDATA_WORD(0) = 0x1770;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

    if(ScalerGetBit(PB5_A0_MN_SCLKG_CTRL, (_BIT7 | _BIT6)) == 0x00)
    {
        ulXtal_clk = _GDI_CLK_KHZ;

        // Set N code to Fin = 13.5MHz
        ucplln = 2;
    }
    else if(ScalerGetBit(PB5_A0_MN_SCLKG_CTRL, (_BIT7 | _BIT6)) == _BIT6)
    {
        // PLL Reference Clock is Link_Clk/2
        ulXtal_clk = (PDATA_DWORD(0) / 1000 / 2);

        // Set N code to Fin = 13.5MHz
        ucplln = ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00);
    }

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        ulVBs2BsCount = g_stDpRx1LinkInfo.ulVBsToBsCountN;
    }
    else
#endif
    {
        // Measurement Enable
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB5_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
        {
            return _FALSE;
        }

        // Pop up The result
        SET_DP_RX1_MEASURE_POP_UP();

        ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB5_58_MN_MEAS_CTRL) & 0x1F)) << 16) | ((DWORD)ScalerGetByte(PB5_59_MN_MEAS_VLN_M) << 8) | ((DWORD)ScalerGetByte(PB5_5A_MN_MEAS_VLN_L)));

        // Measurement Disable
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        ulDpMvidValue = ((((DWORD)ScalerGetByte(PB6_1A_MSA_MVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1B_MSA_MVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1C_MSA_MVID_2)));

        // Calculate streamclk
        ulStreamClkValue = ((DWORD)ulDpMvidValue * (PDATA_DWORD(0) / ulDpNvidValue) + (PDATA_DWORD(0) % ulDpNvidValue * 100 / ulDpNvidValue * (DWORD)ulDpMvidValue / 100));
    }
    else
#endif
    {
        // Calculate streamclk (Unit is Hz)
        ulStreamClkValue = (((((DWORD)usDpHtotal) * ((DWORD)usDpVtotal) * 100) / ulVBs2BsCount) * _GDI_CLK_KHZ * 10);
    }

    // Input Pixel CLK Unit is 0.1 M
    SET_INPUT_PIXEL_CLK(ulStreamClkValue / 100000);

    DebugMessageRx1("Stream Clk", ulStreamClkValue);

    // Get DPLL parameter
    // If "HW Input Clock Max > ulStreamClkValue > 270Mhz"
    if((_HW_DP_MAC1_INPUT_CLOCK_MAX > ulStreamClkValue) && (ulStreamClkValue >= 270000000))
    {
        ucpllo = 0;
        ucdivs = 0;

        ucdiv_divs = 1;
        ucdiv_pllo = 1;

        ulpllm = ((((ulStreamClkValue / 4) * ucdiv_divs * ucdiv_pllo) * ucplln / 250) / (ulXtal_clk));

        if(ulpllm > 257)
        {
            return _FALSE;
        }
    }
    // If "270MHz > ulStreamClkValue > 4.21875Mhz"
    else if((ulStreamClkValue < 270000000) && (ulStreamClkValue >= 4218750))
    {
        ucpllo = 1;

        if((ulStreamClkValue < 270000000) && (ulStreamClkValue >= 135000000))
        {
            ucdivs = 0;
        }
        else if((ulStreamClkValue < 135000000) && (ulStreamClkValue >= 67500000))
        {
            ucdivs = 1;
        }
        else if((ulStreamClkValue < 67500000) && (ulStreamClkValue >= 33750000))
        {
            ucdivs = 2;
        }
        else if((ulStreamClkValue < 33750000) && (ulStreamClkValue >= 16875000))
        {
            ucdivs = 4;
        }
        else if((ulStreamClkValue < 16875000) && (ulStreamClkValue >= 8437500))
        {
            ucdivs = 8;
        }
        else
        {
            ucdivs = 16;
        }

        // Because set 17 get minimum error for recovery stream clk , close to fact clk.
        if(ucdivs == 0)
        {
            ucdiv_divs = 1;
        }
        else
        {
            ucdiv_divs = 2 * ucdivs;
        }

        ucdiv_pllo = 1;

        if(ucpllo != 0)
        {
            ucdiv_pllo = 1;

            for(ucBuf = 0; ucBuf < ucpllo; ucBuf++)
            {
                ucdiv_pllo = 2 * ucdiv_pllo;
            }
        }

        ulpllm = ((((ulStreamClkValue / 4) * ucdiv_divs * ucdiv_pllo) * ucplln / 250) / (ulXtal_clk));

        if(ulpllm > 257)
        {
            return _FALSE;
        }
    }
    else
    {
        return _FALSE;
    }

#if(_DP_MN_PLL_FREQUENCY_TREND == _PLL_FREQ_DOWN)
    // For Trend of Phase Swallow is Up(Frequency Down).
    ulpllm++;
#endif

    // Determine M code Step Within VCO Frequency Range
    // UP Case: (M+M_delta)/N*Fin < The Available Highest M/N*Fin Frequency
    // DN Case: (M-M_delta)/N*Fin > The Available Lowest M/N*Fin Frequency
    ulpllmDelta = ulpllm / _DP_MN_PLL_VCO_FREQ_RANGE;

    do
    {
#if(_DP_MN_PLL_FREQUENCY_TREND == _PLL_FREQ_DOWN)
        // Path1: M'/N*Fin*(1-1/8*Ratio/100) =< VCO Target
        // Path2: M'/N*Fin*(1-1/9*Ratio/100) =< VCO Target
        if(ScalerComputeDwordMulDiv((ulpllm + ulpllmDelta) * (_DP_MN_PLL_VCO_FREQ_RANGE * 100 - _DP_MN_PLL_DECIDE_M_CODE_FACTOR), (ulXtal_clk * 1000), ucplln * _DP_MN_PLL_VCO_FREQ_RANGE * 100) <= (ulStreamClkValue * ucdiv_divs * ucdiv_pllo))
        {
            ulpllm += ulpllmDelta;
            break;
        }
#else
        // Path1: M'/N*Fin*(1+1/8*Ratio/100) >= VCO Target
        // Path2: M'/N*Fin*(1+1/7*Ratio/100) >= VCO Target
        if(ScalerComputeDwordMulDiv((ulpllm - ulpllmDelta) * (_DP_MN_PLL_VCO_FREQ_RANGE * 100 + _DP_MN_PLL_DECIDE_M_CODE_FACTOR), (ulXtal_clk * 1000), ucplln * _DP_MN_PLL_VCO_FREQ_RANGE * 100) >= (ulStreamClkValue * ucdiv_divs * ucdiv_pllo))
        {
            ulpllm -= ulpllmDelta;
            break;
        }
#endif

        ulpllmDelta--;
    }
    while(ulpllmDelta > 0);

    DebugMessageRx1("modified M code", ulpllm);

#if(_DP_MN_PLL_PATH_TYPE == _PATH2)
#if(_DP_MN_PLL_FREQUENCY_TREND == _PLL_FREQ_DOWN)
    // offset = (m*2^21)*(f_ref)/f/n) - 2^21
    lOffsetValue = (ScalerComputeDwordMulDiv((ulpllm << 21), (ulXtal_clk * 1000), (ulStreamClkValue * ucdiv_pllo * ucdiv_divs)) / ucplln) - 2097152;
#else
    // offset = 2^21 - (m*2^21)*(f_ref)/f/n)
    lOffsetValue = 2097152 - (ScalerComputeDwordMulDiv((ulpllm << 21), (ulXtal_clk * 1000), (ulStreamClkValue * ucdiv_pllo * ucdiv_divs)) / ucplln);
#endif
#else
#if(_DP_MN_PLL_FREQUENCY_TREND == _PLL_FREQ_DOWN)
    // offset = (m/n*f_ref - f)/(m/n*f_ref)*2^21
    // seperate *2^21 to *32*16384*4
    lOffsetValue = ((SDWORD)((ulXtal_clk * 1000 / ucplln) * ulpllm) - (SDWORD)(ulStreamClkValue * ucdiv_pllo * ucdiv_divs)) * 32 / ulpllm * ucplln / ulXtal_clk * 16384 / 1000 * 4;
#else
    // offset = (f - m/n*f_ref)/(m/n*f_ref)*2^21
    // seperate *2^21 to *32*16384*4
    lOffsetValue = ((SDWORD)(ulStreamClkValue * ucdiv_pllo * ucdiv_divs) - (SDWORD)((ulXtal_clk * 1000 / ucplln) * ulpllm)) * 32 / ulpllm * ucplln / ulXtal_clk * 16384 / 1000 * 4;
#endif
#endif

    // Calculate P code to Avoid Reversing Trend of PLL Phase Swallow
    ul2ndPCode = ((lOffsetValue << 1) / _DP_HS_TRACKING_STABLE_PE_THRESHOLD  - ul2ndICode);

    if(ul2ndPCode < 0xFFF)
    {
        // The Minimum P code is 00FFFh.
        ul2ndPCode = 0xFFF;
    }

    DebugMessageRx1("P Code", ul2ndPCode);

#if(_DP_MN_PLL_FREQUENCY_TREND == _PLL_FREQ_DOWN)
    lOffsetValue = 0x7FFFF - lOffsetValue + 1;
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        lOffsetValue = g_stDpRx1LinkInfo.lStreamClockOffset;
    }
#endif

    // DPPLL Power Down
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    /*
    // Disable M/N Tracking
    ScalerSetBit(PB5_A7_MN_SCLKG_TRK_CTRL, ~_BIT7, 0x00);
    */

    // Disable HSync Tracking
    ScalerSetBit(PB5_A7_MN_SCLKG_TRK_CTRL, ~_BIT6, 0x00);

    // Set VCOMD, Path Type of Phase Swallow , SCLKGSTOP
    ScalerSetBit(PB5_BF_MN_SCLKG_PLL_WD, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | (_BIT2 & (_DP_MN_PLL_PATH_TYPE << 2)) | _BIT1));

#if(_HW_PLL_AUTO_EDGE_SELECT_SUPPORT == _ON)
    // Disable PLL Auto Edge
    ScalerSetBit(PB5_C1_MN_SCLKG_PLL_RESERVE, ~_BIT1, 0x00);
#endif

    // Set DPPLL Div_2 & Div_s
    ScalerSetByte(PB5_A3_MN_SCLKG_DIVS, (((ucdiv2) << 7) | ((ucdivs) << 0)));

    // Set DPPLL Div_O.
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0), ucpllo);

    // Offset Value Setting
    ScalerSetByte(PB5_A6_MN_SCLKG_OFFS_L, (BYTE)lOffsetValue);
    ScalerSetByte(PB5_A5_MN_SCLKG_OFFS_M, (BYTE)(lOffsetValue >> 8));
    ScalerSetBit(PB5_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 | _BIT0), ((BYTE)(lOffsetValue >> 16)) & (_BIT2 | _BIT1 | _BIT0));

    // Enable phase swallow
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), _BIT4);

    // Set DPPLL M Code
    ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), (((ulpllm - 2) >> 8) & 0x03));
    ScalerSetByte(PB5_A1_MN_SCLKG_DIVM, ((ulpllm - 2) & 0xFF));

    // Set DPPLL N Code
    ScalerSetByte(PB5_A2_MN_SCLKG_DIVN, (ucplln - 2));

    // Load offset value
    ScalerSetBit(PB5_A4_MN_SCLKG_OFFS_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

    // Double Buffer for M/N Tracking
    ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(PB5_C0_MN_SCLKG_PLL_INSEL, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL Power On
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT7, 0x00);

    ScalerTimerDelayXms(2);


    ////////////////////////////////
    // DPPLL VCO Band Calibration //
    ////////////////////////////////

    // Reg DPLL_CMPEN
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT2, _BIT2);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALLCH
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT3, _BIT3);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALSW
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT4, _BIT4);

    // VCO Band : 01 ---> KVCO = 1340
    // VCO Band : 10 ---> KVCO = 1880
    // VCO Band : 11 ---> KVCO = 2340
    // R : 13
    // Icp = 6.28 * 700 * M / KVCO / R
    // Icp   = 2.5u + bit[0] * 2.5u + bit[1] * 5u + bit[2] * 10u (A)
    // Icp = 2.5uA, 5uA, 7.5uA, 10uA......
    if(ScalerGetBit(PB5_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) == _BIT5)
    {
        pData[5] = 4396 * ulpllm / 1880 / 13;
    }
    else if(ScalerGetBit(PB5_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        pData[5] = 4396 * ulpllm / 2340 / 13;
    }
    else
    {
        // For ICP default Setting
        pData[5] = 4396 * ulpllm / 1340 / 13;
    }

    pData[5] = ((20 * pData[5]) + 25) / 50;
    pData[5] -= (pData[5] == 0) ? 0 : 1;

    // Set PLL Charge Pump Current
    ScalerSetByte(PB5_BE_MN_SCLKG_PLL_CHP, (0x78 | (pData[5] & 0x07)));

    /*
    ////////////////////////////////
    // DPPLL M/N Tracking Setting //
    ////////////////////////////////

    // Don't Use M/N Tracking for Nvid > 0x40000 or Nvid < 0xFF

    //////////////////// Enable M/N auto tracking /////////////////////////
    // I = (2^22)*( (Tdds / Tmn) * (1 / n), n = 8
    // 1. Fdds = 1/4 * Fvco = (ulLinkClkValue / 8) * (ulpllm / ucplln) / 4 --> Tdds = (32 / ulLinkClkValue) * (plln / ulpllm)
    // 2. Tmn = Nvid * (1 / ulLinkClkValue)
    // from1,2 we can get : I = (2^27) * (ucplln / ulpllm) / Nvid / n = (2^24) * (ucplln / ulpllm) / Nvid

    ulIcodeValue = (16777216 / ulDpNvidValue) * ucplln / ulpllm;  //I = (2^24) * (ucplln / ulpllm) / Nvid

    ScalerSetBit(PB5_A8_MN_SCLKG_TRK_MN_I_H, ~(_BIT2 | _BIT1 | _BIT0), ((BYTE)(ulIcodeValue >> 16) & 0x03));
    ScalerSetByte(PB5_A9_MN_SCLKG_TRK_MN_I_M, (BYTE)(ulIcodeValue >> 8));
    ScalerSetByte(PB5_AA_MN_SCLKG_TRK_MN_I_L, (BYTE)ulIcodeValue);

    // Set P Code
    ScalerSetBit(PB5_AB_MN_SCLKG_TRK_MN_P_H, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetByte(PB5_AC_MN_SCLKG_TRK_MN_P_M, 0xFF);
    ScalerSetByte(PB5_AD_MN_SCLKG_TRK_MN_P_L, 0xFF);
    */

    ////////////////////////////////////////
    // DPPLL HS Tracking Tracking Setting //
    ////////////////////////////////////////

    // Disable Tracking New Mode
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~(_BIT2 | _BIT1), _BIT1);

    // Set Initial I/P Code
    ScalerSetByte(PB5_B1_MN_SCLKG_TRK_VS_I_M, 0x00);
    ScalerSetByte(PB5_B2_MN_SCLKG_TRK_VS_I_L, 0x04);
    ScalerSetByte(PB5_B3_MN_SCLKG_TRK_VS_P_H, 0x00);
    ScalerSetByte(PB5_B4_MN_SCLKG_TRK_VS_P_M, 0x7F);
    ScalerSetByte(PB5_B5_MN_SCLKG_TRK_VS_P_L, 0xFF);

    // Get How Many Lines per SSC Period
    pData[0] = ulStreamClkValue / usDpHtotal / 33000;

    if(pData[0] > 15)
    {
        pData[0] = 15;
    }

    // Set Tracking Freq 8 Line for 33K SSC at 4K2K60Hz
    ScalerSetBit(PB5_A8_MN_SCLKG_TRK_MN_I_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (pData[0] << 4));

    if(ulStreamClkValue >= 50000000)
    {
        // Set Threshold of Phase Error = 63 for Timing that Stream Clock is more than 50MHz
        ScalerSetByte(PB5_B7_MN_SCLKG_TRK_VS_NLOCK, 0x3F);
    }
    else
    {
        // Set Threshold of Phase Error = 127
        ScalerSetByte(PB5_B7_MN_SCLKG_TRK_VS_NLOCK, 0x7F);
    }

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
    {
        // Enable H Sync Tracking
        ScalerSetByte(PB5_A7_MN_SCLKG_TRK_CTRL, 0x58);
    }

    // Double Buffer for H Sync Tracking
    ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // Get Frame Period
    ucFrameTime = 1000 / (ulStreamClkValue / usDpHtotal / usDpVtotal) + 1;

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
    {
        pData[0] = 0;

        // Waiting for Stream Clk Stable
        do
        {
            // Clear PE Max Record
            ScalerSetByte(PB5_B6_MN_SCLKG_TRK_VS_PE, 0x01);

            // Clear PE Flag
            ScalerSetBit(PB5_B7_MN_SCLKG_TRK_VS_NLOCK, ~_BIT7, _BIT7);

            // Delay 1 Frame
            ScalerTimerDelayXms(ucFrameTime);

            pData[0]++;
        }
        while((ScalerGetBit(PB5_B7_MN_SCLKG_TRK_VS_NLOCK, _BIT7) == _BIT7) && (pData[0] < 10));

        DebugMessageRx1("1st PE Loop", pData[0]);
        DebugMessageRx1("1st PE Max Record", ScalerGetByte(PB5_B6_MN_SCLKG_TRK_VS_PE));
    }

    // Set Final I Code
    ScalerSetByte(PB5_B1_MN_SCLKG_TRK_VS_I_M, HIBYTE(LOWORD(ul2ndICode)));
    ScalerSetByte(PB5_B2_MN_SCLKG_TRK_VS_I_L, LOBYTE(LOWORD(ul2ndICode)));

    // Set Final P Code
    ScalerSetByte(PB5_B3_MN_SCLKG_TRK_VS_P_H, LOBYTE(HIWORD(ul2ndPCode)));
    ScalerSetByte(PB5_B4_MN_SCLKG_TRK_VS_P_M, HIBYTE(LOWORD(ul2ndPCode)));
    ScalerSetByte(PB5_B5_MN_SCLKG_TRK_VS_P_L, LOBYTE(LOWORD(ul2ndPCode)));

    // Don't Enable HS Tracking New Mode for DE Only Mode
    if(ScalerGetBit(PB5_30_DPF_CTRL_0, (_BIT5 | _BIT4)) != _BIT4)
    {
        // Need to be Moved to FIFO Ready
        // Only Enable Tracking at Active Region when PE is Small
        PDATA_WORD(0) = ulVBs2BsCount / usDpVtotal / 2;

        ScalerSetBit(PB5_C2_HS_TRACKING_NEW_MODE1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
        ScalerSetByte(PB5_C3_HS_TRACKING_NEW_MODE2, pData[1]);

        ScalerDpRx1HSActiveTrackingMode(_DP_HS_TRACKING_FW_MODE);

        // Enable Tracking New Mode
        ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~(_BIT2 | _BIT1), _BIT2);
    }

    // Set Threshold of Phase Error
    ScalerSetByte(PB5_B7_MN_SCLKG_TRK_VS_NLOCK, (_DP_HS_TRACKING_STABLE_PE_THRESHOLD & ~_BIT7));

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        // Enable H Sync Tracking
        ScalerSetByte(PB5_A7_MN_SCLKG_TRK_CTRL, 0x58);
    }
#endif

    pData[0] = 0;

    // Waiting for Stream Clk Stable
    do
    {
        // Clear PE Max Record
        ScalerSetByte(PB5_B6_MN_SCLKG_TRK_VS_PE, 0x01);

        // Clear PE Flag
        ScalerSetBit(PB5_B7_MN_SCLKG_TRK_VS_NLOCK, ~_BIT7, _BIT7);

        // Delay 1 Frame
        ScalerTimerDelayXms(ucFrameTime);

        pData[0]++;
    }
    while((ScalerGetBit(PB5_B7_MN_SCLKG_TRK_VS_NLOCK, _BIT7) == _BIT7) && (pData[0] < 10));

    DebugMessageRx1("2nd PE Loop", pData[0]);
    DebugMessageRx1("2nd PE Max Record", ScalerGetByte(PB5_B6_MN_SCLKG_TRK_VS_PE));

    // Check if DPF Mode is DE Mode
    if(ScalerGetBit(PB5_30_DPF_CTRL_0, (_BIT5 | _BIT4)) == _BIT4)
    {
#if(_DP_DE_ONLY_MODE_WITH_FULL_LAST_LINE_SUPPORT == _ON)
        if(ScalerGlobalGetIDCode() >= _RL6492_VER_C_ID_CODE)
        {
            WORD usHBs2BsCount = ((((WORD)ScalerGetByte(PB5_5B_MN_MEAS_HLN_M)) << 8) | (ScalerGetByte(PB5_5C_MN_MEAS_HLN_L)));

            // Half BS delay counted by GDI_CLK = HBs2BsCount / (1/2 * Link_clk) * GDI_clk / 2
            PDATA_WORD(0) = usHBs2BsCount * (_GDI_CLK_KHZ / 1000) / (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 27);

            ScalerSetBit(PB5_C2_HS_TRACKING_NEW_MODE1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte(PB5_C3_HS_TRACKING_NEW_MODE2, pData[1]);

            ScalerDpRx1HSActiveTrackingMode(_DP_HS_TRACKING_FW_MODE);

            // Enable Tracking New Mode
            ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~(_BIT2 | _BIT1), _BIT2);

            // Enable full last line mode for DE only mode & generate de_mod_de_window by cr_be (avoid BS lost case)
            ScalerSetBit(PB5_F1_DP_RSV1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
        else
#endif
        {
            // DE only mode Disable HSync Tracking
            ScalerSetBit(PB5_A7_MN_SCLKG_TRK_CTRL, ~_BIT6, 0x00);
        }
    }

    // Start Generate Display Format
    ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT7, _BIT7);

    // Polling Vertical BS
    ScalerTimerPollingFlagProc(50, PB6_01_DP_VBID, _BIT0, _TRUE);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        // Delay for PG Stable
        ScalerTimerDelayXms(ucFrameTime);
    }
    else
#endif
    {
        // Delay for PG Stable
        ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);
    }

    return _TRUE;
}


//--------------------------------------------------
// Description  : DP Video Fifo Check
// Input Value  : Fifo Check Condition
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerDpRx1FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition)
{
    if(enumFifoCheckCondition == _DP_FIFO_DELAY_CHECK)
    {
        ScalerSetBit(PB5_21_PG_CTRL_1, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
        if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
        {
            ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

            pData[0] = 0;

            while(pData[0] < 6)
            {
                ScalerTimerDelayXms(10);

                if((ScalerGetBit(PB5_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PB5_21_PG_CTRL_1, _BIT2) == _BIT2))
                {
                    return _FALSE;
                }

                pData[0]++;
            }
        }
    }
    else
    {
        if((ScalerGetBit(PB5_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PB5_21_PG_CTRL_1, _BIT2) == _BIT2))
        {
            return _FALSE;
        }
    }

    if(ScalerGetBit(PB6_3B_DP_IRQ_CTRL1, _BIT4) == 0x00)
    {
        // Enable DP No Video Stream IRQ
        ScalerDpRx1SetNoVideoStreamIRQ(_ENABLE);
    }

    if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x05, _BIT0) == 0x00)
    {
        // Set DP Receive Port0 In Sync
        ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : HDCP Reset For Dp Rx1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPBlockReset(void)
{
#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    if(GET_REG_DP_RX1_MAC_ASSIGNED() == _TRUE)
#endif
    {
        // Reset HDCP Block
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
    }

    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x29, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2A, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2B, 0x00);

    for(pData[0] = 0; pData[0] < 20; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x14 + pData[0]), 0x00);
    }

    for(pData[0] = 0; pData[0] < 15; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), 0x00);
    }

    SET_DP_RX1_AUX_MANUAL_MODE();

    // Clear Aksv
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x07, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x08, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x09, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x0A, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x0B, 0x00);

    SET_DP_RX1_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : HDCP Unplug Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPUnplugReset(void)
{
    ScalerDpRx1HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpRx1Hdcp2ResetProc();
#endif

    // Clear CPIRQ flag while unplug
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) & ~_BIT2));
}

//--------------------------------------------------
// Description  : Check DP Link Integrity
// Input Value  : None
// Output Value : FALSE => DP Link Integrity Fail
//--------------------------------------------------
bit ScalerDpRx1HdcpCheck(void)
{
    // Check for HDCP Block work in 1.4
    if(GET_DP_RX1_HDCP_MODE() == _HDCP_14)
    {
        if((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x07) == 0x00) &&
           (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x08) == 0x00) &&
           (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x09) == 0x00) &&
           (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0A) == 0x00) &&
           (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0B) == 0x00))
        {
            return _TRUE;
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(GET_DP_RX1_HDCP2_AUTHENTICATION_DONE() == _FALSE)
        {
            return _TRUE;
        }
    }
#endif

    if(((ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
    {
        return _TRUE;
    }

    // Check for HDCP Block work in 1.4
    if((GET_DP_RX1_HDCP_MODE() == _HDCP_14) && ((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & _BIT2) == 0x00))
    {
        return _FALSE;
    }

    if((GET_DP_RX1_HDCP_MODE() == _HDCP_14) && (ScalerDpRx1HdcpMeasureCheck() == _TRUE))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check DP Hdcp ReAuth Process
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerDpRx1HdcpReAuthStatusCheck(void)
{
    if(GET_DP_RX1_HDCP_MODE() == _HDCP_14)
    {
        if((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) || (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
           (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) || (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
           (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : DP HDCP Measure Check
// Input Value  : None
// Output Value : FALSE => Measure Check Fail
//--------------------------------------------------
bit ScalerDpRx1HdcpMeasureCheck(void)
{
    DWORD ulLinkClk = 0;
    WORD usHTotalCount = 0;

    // Pop up Main Stream Attributes
    ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Vtotal
    ScalerRead(PB6_10_MSA_VTTE_0, 2, &pData[10], _AUTOINC);

    if(PDATA_WORD(5) == 0)
    {
        return _FALSE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Waiting for Measure Done
    ScalerTimerDelayXms(2);

    if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));
    }
    else
    {
        if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = 0x4E20;
        }
        else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
        {
            PDATA_WORD(0) = 0x2710;
        }
        else // Both Default && _DP_LINK_RBR Case
        {
            PDATA_WORD(0) = 0x1770;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

    // Link Clk in KHz
    ulLinkClk = (PDATA_DWORD(0) / 1000);

    DebugMessageRx1("Current Link Clk", ulLinkClk);

    // Start to Measure Vertical BS to BS Counter by GDI Clock
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB5_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The result
    SET_DP_RX1_MEASURE_POP_UP();

    // Get Measure Result
    ScalerRead(PB5_58_MN_MEAS_CTRL, 3, &pData[1], _AUTOINC);

    // Get Measure Htotal Counts
    ScalerRead(PB5_5B_MN_MEAS_HLN_M, 2, &pData[6], _AUTOINC);

    // Disable Measure Block
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);

    // Convert HTotal Count from 1/2 Link Clk to GDI Clk
    usHTotalCount = ((DWORD)PDATA_WORD(3) * _GDI_CLK_KHZ * 2 + (ulLinkClk >> 1)) / ulLinkClk;

    PDATA_DWORD(0) = (PDATA_DWORD(0) & 0x001FFFFF);
    PDATA_DWORD(1) = ((DWORD)usHTotalCount & 0x0000FFFF);

    PDATA_WORD(2) = PDATA_DWORD(0) / PDATA_DWORD(1);

    // 2% Tolerance
    if((ABSDWORD(PDATA_WORD(2), PDATA_WORD(5))) > (PDATA_WORD(5) * 2 / 100))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CpIRQ(EnumDpRxBStatusType enumBStatusType)
{
    switch(enumBStatusType)
    {
        case _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL:

            if(GET_DP_RX1_HDCP_MODE() == _HDCP_14)
            {
                // Reset HDCP Block
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

                SET_DP_RX1_AUX_MANUAL_MODE();

                // Clear Aksv
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x07, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x08, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x09, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x0A, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x0B, 0x00);

                SET_DP_RX1_AUX_AUTO_MODE();

                // Set B Status
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) | enumBStatusType));
            }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            else
            {
                // Disable HDCP 2.2 Module
                SET_DP_RX1_HDCP_MODE(_HDCP_14);

                // Disable HDCP2.2 Auth. Done
                ScalerSetBit(PB_20_HDCP_DEBUG, ~_BIT4, 0x00);

                // Reset HDCP Block
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

                ScalerDpRx1SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) | _BIT4));

                // Clear Authentication Done Flag
                CLR_DP_RX1_HDCP2_AUTHENTICATION_DONE();
            }
#endif
            break;

        case _DP_HDCP_BSTATUS_REAUTH_REQ:

            ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) | _BIT3));

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_RXSTATUS_REAUTH_REQ:

            ScalerDpRx1SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) | _BIT3));

            break;
#endif

        case _DP_HDCP_BSTATUS_V_READY:
        case _DP_HDCP_BSTATUS_R0_AVAILABLE:

            // Set B Status
            ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) | enumBStatusType));

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpRx1SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;
#endif

        default:

            break;
    }

    // Link Status CPIRQ Flag
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) | _BIT2));

    ScalerDpRx1HpdIrqAssert();
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType) using 1
{
    BYTE ucBackUp = 0;

    ucBackUp = ScalerGetByte_EXINT(PBA_D0_AUX_MODE_SET);

    switch(enumBStatusType)
    {
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;

        default:

            break;
    }

    // Link Status CPIRQ Flag
    pData_EXINT[0] = (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x01) | _BIT2);

    // SET AUX AUTO MODE
    SET_DP_RX1_AUX_AUTO_MODE_EXINT();

    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x01, pData_EXINT[0]);

    if((ucBackUp & _BIT1) == 0x00)
    {
        // SET AUX MANUAL MODE
        SET_DP_RX1_AUX_MANUAL_MODE_EXINT();
    }

    ScalerDpRx1HpdIrqAssert_EXINT0();
}
#endif

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : None
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpRx1HdcpCheckValid(void)
{
    if(GET_DP_RX1_HDCP_MODE() == _HDCP_14)
    {
        if(ScalerGetBit(PB_20_HDCP_DEBUG, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
        {
            return _TRUE;
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(ScalerGetBit(PB_20_HDCP_DEBUG, _BIT4) == _BIT4)
        {
            if((ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerDpRx1HdcpCheckEnabled(void)
{
    if(GET_DP_RX1_HDCP_MODE() == _HDCP_14)
    {
        if(ScalerGetBit(PB_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5))
        {
            if((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) ||
               (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
               (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) ||
               (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
               (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00))
            {
                return _TRUE;
            }
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(ScalerGetBit(PB_20_HDCP_DEBUG, _BIT4) == _BIT4)
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1PhyCtsTp1SetPhy(EnumDpNFCodeRef enumDpNFCodeRef)
{
    BYTE ucIcp = 0;


    ////////////////////
    // Mode Select DP //
    ////////////////////

    // [5] dp_mode = 1'b1 --> Select DP Mode
    ScalerSetBit(P1D_16_BANDGAP_02, ~_BIT5, _BIT5);

    // [7] si_hd_dp_sel = 1'b0 --> Select DP
    ScalerSetBit(P1D_05_DIG_05, ~_BIT7, 0x00);

    // [4] PSM = 1'b0 --> Disable Clock Switch
    ScalerSetBit(P1D_15_BANDGAP_01, ~_BIT4, 0x00);


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

    // DP Lane Swap Setting
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D1_DP_LANE3 << 6);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D1_DP_LANE2 << 4);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D1_DP_LANE1 << 2);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

    // DP Lane PN Swap Setting
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, GET_DP_RX1_PCB_LANE3_PN_SWAP() << 7);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, GET_DP_RX1_PCB_LANE2_PN_SWAP() << 6);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, GET_DP_RX1_PCB_LANE1_PN_SWAP() << 5);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, GET_DP_RX1_PCB_LANE0_PN_SWAP() << 4);


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

    // [5] dp_mode = 1'b1 --> Select DP Mode
    ScalerSetBit(P1D_16_BANDGAP_02, ~_BIT5, _BIT5);

    // [7] si_hd_dp_sel = 1'b0 --> Select DP
    ScalerSetBit(P1D_05_DIG_05, ~_BIT7, 0x00);

    // [4] PSM = 1'b0 --> Disable Clock Switch
    ScalerSetBit(P1D_15_BANDGAP_01, ~_BIT4, 0x00);

    // [7] cmu_en = 1'b0 --> Lane3 CMU Disable
    ScalerSetBit(P1D_21_CMU_04, ~_BIT7, 0x00);

    // Disable RX_EN, CDR_EN
    ScalerSetByte(P1D_20_CMU_03, 0x00);

    switch(g_ucDpRx1PhyCtsCtrl & 0x30)
    {
        case 0x10:

            // dp_bbpd_sel[3:2] = 2'b01 --> ACDR BBPD UP/DN from Lane1
            ScalerSetBit(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), _BIT2);

            // ln_clk_func_sel[1:0] = 2'b01 --> MAC Clock from Analog Lane1
            ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _BIT0);

            // Lane1 Test, Enable RX_EN/CDR_EN for Lane1/3
            ScalerSetByte(P1D_20_CMU_03, 0xAA);

            break;

        case 0x20:

            // dp_bbpd_sel[3:2] = 2'b10 --> ACDR BBPD UP/DN from Lane2
            ScalerSetBit(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), _BIT3);

            // ln_clk_func_sel[1:0] = 2'b10 --> MAC Clock from Analog Lane2
            ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _BIT1);

            // Lane2 Test, Enable RX_EN/CDR_EN for Lane2/3
            ScalerSetByte(P1D_20_CMU_03, 0xCC);

            break;

        case 0x30:

            // dp_bbpd_sel[3:2] = 2'b11 --> ACDR BBPD UP/DN from Lane3
            ScalerSetBit(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // ln_clk_func_sel[1:0] = 2'b11 --> MAC Clock from Analog Lane3
            ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Lane3 Test, Enable RX_EN/CDR_EN for Lane3
            ScalerSetByte(P1D_20_CMU_03, 0x88);

            break;

        default:
        case 0x00:

            // dp_bbpd_sel[3:2] = 2'b00 --> ACDR BBPD UP/DN from Lane0
            ScalerSetBit(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), 0x00);

            // ln_clk_func_sel[1:0] = 2'b00 --> MAC Clock from Analog Lane0
            ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), 0x00);

            // Lane0 Test, Enable RX_EN/CDR_EN for Lane0/3
            ScalerSetByte(P1D_20_CMU_03, 0x99);

            break;
    }

    // Delay Time us [25,x]
    DELAY_25US();

    // Enable Analog CDR and FLD
    ScalerSetBit(P1D_12_ANA_CDR, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [4:3] One Lane Test
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);


    ///////////////////////
    // Frequency Setting //
    ///////////////////////

    switch((g_ucDpRx1PhyCtsCtrl & 0xC0))
    {
        // HBR
        case 0x40:

            // [2:0] rate_sel = 3'b001 --> 1.75~3.5Gbps
            ScalerSetBit(P1D_3C_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            // [1:0] SEL_DIV = 2'b00 --> 1.75~3.5Gbps
            ScalerSetBit(P1D_24_CMU_07, ~(_BIT1 | _BIT0), 0x00);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [6] reg_xtal_en = 1'b1 --> Using 27M Xtal
                ScalerSetBit(P1D_30_ANA_CDR_02, ~_BIT6, _BIT6);

                // 25/500 = 1/20 = 5*(27M/2.7G)
                // ref_conuter = 24
                ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT7, 0x00);
                ScalerSetByte(P1D_36_ANA_CDR_08, 0x18);

                // cdr_counter = 499
                ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT6, _BIT6);
                ScalerSetByte(P1D_37_ANA_CDR_09, 0xF3);
            }
            else
            {
                // [6] xtal_en = 1'b1 --> D10.2 clock
                ScalerSetBit(P1D_30_ANA_CDR_02, ~_BIT6, 0x00);

                // 125/500 = 1/4 = 5*(135M/2.7G)
                // ref_conuter = 124
                ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT7, 0x00);
                ScalerSetByte(P1D_36_ANA_CDR_08, 0x7C);

                // cdr_counter = 499
                ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT6, _BIT6);
                ScalerSetByte(P1D_37_ANA_CDR_09, 0xF3);
            }

            break;

        // RBR
        case 0x00:
        default:

            // [2:0] rate_sel = 3'b001 --> 875M~1.75Gbps
            ScalerSetBit(P1D_3C_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            // [1:0] SEL_DIV = 2'b00 --> 875M~1.75Gbps
            ScalerSetBit(P1D_24_CMU_07, ~(_BIT1 | _BIT0), _BIT0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [6] reg_xtal_en = 1'b1 --> Using 27M Xtal
                ScalerSetBit(P1D_30_ANA_CDR_02, ~_BIT6, _BIT6);

                // 20/480 = 1/24 = 5*(27M/3.24G)
                // ref_conuter = 19
                ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT7, 0x00);
                ScalerSetByte(P1D_36_ANA_CDR_08, 0x13);

                // cdr_counter = 479
                ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT6, _BIT6);
                ScalerSetByte(P1D_37_ANA_CDR_09, 0xDF);
            }
            else
            {
                // [6] xtal_en = 1'b1 --> D10.2 clock
                ScalerSetBit(P1D_30_ANA_CDR_02, ~_BIT6, 0x00);

                // 60/480 = 1/8 = 5*(81M/3.24G)
                // ref_conuter = 59
                ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT7, 0x00);
                ScalerSetByte(P1D_36_ANA_CDR_08, 0x3B);

                // cdr_counter = 479
                ScalerSetBit(P1D_35_ANA_CDR_07, ~_BIT6, _BIT6);
                ScalerSetByte(P1D_37_ANA_CDR_09, 0xDF);
            }

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [4] Disable Comma Detection
    ScalerSetBit(PB_05_SAMPLE_EDGE, ~_BIT4, _BIT4);

    // [5] Disable De-Scrambling
    ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    // [2] Enable Enhancement Control Mode
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);

    // [1] bypass_clk_rdy = 1'b1 --> Clk Rdy Signal in Manual Mode
    // [0] en_clkout_manual = 1'b1 --> Enable Clkout
    ScalerSetBit(P1D_0E_SDM_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1] bypass_eqen_rdy = 1'b1 --> EQEN Rdy Signal in Manual Mode
    // [0] en_eqen_manual = 1'b1 --> Enable EQ
    ScalerSetBit(P1D_10_EQEN_TIMER, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1] bypass_data_rdy = 1'b1 --> Data Rdy Signal in Manual Mode
    // [0] en_data_manual = 1'b0 --> Disable Dataout
    ScalerSetBit(P1D_11_DATA_TIMER, ~(_BIT1 | _BIT0), _BIT1);

    // [3] reg_en_data_manual_l3 = 1'b0 --> Disable Data Ready
    // [2] reg_bypass_data_rdy_l3 = 1'b1 --> Data Ready Signal in Manual Mode
    // [1] reg_en_eqen_manual_l3 = 1'b1 --> Enable EQ
    // [0] reg_bypass_eqen_rdy_l3 = 1'b1 --> EQ Ready Signal in Manual Mode
    ScalerSetBit(P1D_12_ANA_CDR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Digital Circuit Reset Toggle
    ScalerSetByte(P1D_38_TMDS_RESET, 0x00);
    ScalerSetBit(P1D_38_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));


    /////////////////
    // CDR Setting //
    /////////////////

    // [6:4] sel_cdr_res = 3'b110 --> 8K Ohm
    ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    if((g_ucDpRx1PhyCtsCtrl & 0xC0) == 0x00)   // RBR
    {
        // [3:0] cdr_cp_in = 4'b0110 --> (1nF)19.5uA
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    }
    else
    {
        // [3:0] cdr_cp_in = 4'b0101 --> (1nF)16.5uA
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    }

    ucIcp = (ScalerGetByte(P1D_31_ANA_CDR_03) & 0x0F);


    ////////////////
    // EQ Setting //
    ////////////////

    // [4:0] reg_fore_off_adjr_Lane0~3 = 5'b10000
    ScalerSetBit(P1D_2A_KOFFSET_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P1D_2B_KOFFSET_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P1D_2C_KOFFSET_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P1D_2D_KOFFSET_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

    if((g_ucDpRx1PhyCtsCtrl & 0xC0) == 0x00)   // RBR
    {
        // [7] le_lowgain_highboost = 1'b1 --> Enable LE High-boost Mode
        ScalerSetBit(P1D_2B_KOFFSET_05, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

        // [7:5] le_isel = 3'b000 --> LE Peaking = 900Mbps
        ScalerSetBit(P1D_2C_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [7:5] le_rlsel = 3'b011 --> LE Peaking = 900Mbps
        ScalerSetBit(P1D_2D_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

        // Set DFE Initial
        ScalerDpRx1SetDFEInitial(_DP_LINK_RBR);
    }
    else
    {
        // [7] le_lowgain_highboost = 1'b0 --> Disable LE High-boost Mode
        ScalerSetBit(P1D_2B_KOFFSET_05, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [7:5] le_isel = 3'b010 --> LE Peaking = 1.7Gbps
        ScalerSetBit(P1D_2C_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

        // [7:5] le_rlsel = 3'b001 --> LE Peaking = 1.7Gbps
        ScalerSetBit(P1D_2D_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // Set DFE Initial
        ScalerDpRx1SetDFEInitial(_DP_LINK_HBR);
    }

    // [2:0] tap_en = 3'b001 --> Eable Tap0 Passive EQ
    ScalerSetBit(P1D_2E_ANA_CDR_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [7] en_fore_offset = 1'b0 --> Disable EQ foreground offset calibration
    // [6] fore_off_autok = 1'b1 --> Enable EQ foreground offset calibration using auto mode
    ScalerSetBit(P1D_2A_KOFFSET_04, ~(_BIT7 | _BIT6), _BIT6);

    // Toggle en_fore_offset
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x]
    DELAY_XUS(85);


    ///////////////////
    // FLD Auto Mode //
    ///////////////////

    // Set FLD Auto Mode
    ScalerSetBit(P1D_2E_ANA_CDR_00, ~_BIT7, _BIT7);

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    // [1] adp_en_manual = 1'b0 --> Disable CDR Clock
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~(_BIT2 | _BIT1), 0x00);

    // [7] rstb_fld --> Reset Timer of Analog CDR
    // [6] rstb_fsm --> FLD Reset Signal
    ScalerSetBit(P1D_32_ANA_CDR_04, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P1D_32_ANA_CDR_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Delay Time us [150,x]
    DELAY_XUS(150);


    /////////////////////
    // FLD Manual Mode //
    /////////////////////

    // Scan Lane3 Auto FLD
    ScalerSetBit(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_34_ANA_CDR_06) & 0x7F));

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    ScalerSetBit(P1D_2E_ANA_CDR_00, ~_BIT7, 0x00);

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    // [1] adp_en_manual = 1'b1 --> Enable CDR Clock
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

    // Delay Time us [45,x] Waiting for VCO Stable
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x] Waiting for VCO Stable
    DELAY_45US();

    // [0] en_data_manual = 1'b1 --> Enable Dataout
    ScalerSetBit(P1D_11_DATA_TIMER, ~_BIT0, _BIT0);

    // [3] en_data_manual_l3 = 1'b1 --> Enable Dataout for Lane3
    ScalerSetBit(P1D_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] xclk_sel = 1'b0 --> Keep Link Clock from Analog
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);

    // [1] dig_reset Toggle
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1PhyCtsTp2SetPhy(void)
{
    BYTE ucBestVCOBand = 0;
    WORD usVCOBandDiff = 0;
    WORD usVCOAutoBandAdd4 = 0;
    BYTE ucIcp = (ScalerGetByte(P1D_31_ANA_CDR_03) & 0x0F);


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // Enable Comma Detection
    ScalerSetBit(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    // Enable Scrambling
    ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    // Enable Enhancement Control Mode --> MAC
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);

    // [0] en_data_manual = 1'b0 --> Disable Dataout
    ScalerSetBit(P1D_11_DATA_TIMER, ~_BIT0, 0x00);

    // [3] en_data_manual_l3 = 1'b0 --> Disable Dataout for Lane3
    ScalerSetBit(P1D_12_ANA_CDR, ~_BIT3, 0x00);

    // Digital Circuit Reset Toggle
    ScalerSetByte(P1D_38_TMDS_RESET, 0x00);
    ScalerSetBit(P1D_38_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));


    ////////////////////////
    //  FLD Band Finetune //
    ////////////////////////

    // Target Freq.
    if((g_ucDpRx1PhyCtsCtrl & 0xC0) == 0x00)
    {
        g_usDpRx1ClockTargetCount = 0xBB8; // ideal 1.62G
    }
    else
    {
        g_usDpRx1ClockTargetCount = 0x1388; // ideal 2.7G
    }

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT2, 0x00);

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    switch(g_ucDpRx1PhyCtsCtrl & 0x30)
    {
        default:
        case 0x00: // Lane0 VCO Adjust

            // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
            ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), 0x00);

            break;

        case 0x10: // Lane1 VCO Adjust

            // [1:0] freqdet_lane_sel = 2'b01 -> Lane1
            ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _BIT0);

            break;

        case 0x20: // Lane2 VCO Adjust

            // [1:0] freqdet_lane_sel = 2'b10 -> Lane2
            ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _BIT1);

            break;

        case 0x30: // Lane3 VCO Adjust

            // [1:0] freqdet_lane_sel = 2'b11 -> Lane3
            ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;
    }

    // Scan Auto FLD + 4
    ScalerSetBit(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_34_ANA_CDR_06) & 0x7F) + 4));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT Value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        // FLD + 4 Measure Done
        if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            usVCOAutoBandAdd4 = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }


    /////////////////////////
    // VCO Band Difference //
    /////////////////////////

    // Scan Auto FLD
    ScalerSetBit(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_34_ANA_CDR_06) & 0x7F));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT Value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        // FLD + 4 Measure Fail or Measure Done
        if((usVCOAutoBandAdd4 == 0) || (ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6))
        {
            break;
        }
    }

    // Measure Done
    if((ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6) && (usVCOAutoBandAdd4 != 0))
    {
        g_usDpRx1ClockMeasureCount = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        usVCOBandDiff = (abs(usVCOAutoBandAdd4 - g_usDpRx1ClockMeasureCount) >> 2);

        if(g_usDpRx1ClockMeasureCount < g_usDpRx1ClockTargetCount)
        {
            // VCO Adjust
            ucBestVCOBand = (ScalerGetByte(P1D_34_ANA_CDR_06) & 0x7F) + (((g_usDpRx1ClockTargetCount - g_usDpRx1ClockMeasureCount) / usVCOBandDiff) + 1);
        }
        else
        {
            // VCO Adjust
            ucBestVCOBand = (ScalerGetByte(P1D_34_ANA_CDR_06) & 0x7F) - ((g_usDpRx1ClockMeasureCount - g_usDpRx1ClockTargetCount) / usVCOBandDiff);
        }
    }
    else
    {
        // Measure Fail -> Use Auto FLD Band
        ucBestVCOBand = (ScalerGetByte(P1D_34_ANA_CDR_06) & 0x7F);
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // Manually Reload FLD Band
    ScalerSetBit(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x] Waiting for VCO Stable
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x] Waiting for VCO Stable
    DELAY_45US();

    // [0] en_data_manual = 1'b1 --> Enable Dataout
    ScalerSetBit(P1D_11_DATA_TIMER, ~_BIT0, _BIT0);

    // [3] en_data_manual_l3 = 1'b1 --> Enable Dataout for Lane3
    ScalerSetBit(P1D_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] xclk_sel = 1'b0 --> Keep Link Clock from Analog
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);

    // [1] dig_reset Toggle
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
bit ScalerDpRx1PhyCtsTp1Check(void)
{
    // Wait for 10ms
    ScalerTimerDelayXms(10);

    // Clear 8B/10B Decode Error Flags
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Wait for 2ms
    ScalerTimerDelayXms(2);

    switch(g_ucDpRx1PhyCtsCtrl & 0x30)
    {
        case 0x00: // Lane0 Test

            // EQ auto K,Check lane0 CRC
            pData[0] = 0x10;
            pData[1] = 0x01;

            break;

        case 0x10: // Lane1 Test

            // EQ auto K,Check lane1 CRC
            pData[0] = 0x20;
            pData[1] = 0x02;

            break;

        case 0x20: // Lane2 Test

            // EQ auto K,Check lane2 CRC
            pData[0] = 0x40;
            pData[1] = 0x04;

            break;

        case 0x30: // Lane3 Test

            // EQ auto K,Check lane3 CRC
            pData[0] = 0x80;
            pData[1] = 0x08;

            break;

        default:

            pData[0] = 0x00;
            pData[1] = 0x00;

            break;
    }

    if(((ScalerGetByte(PB_06_DECODE_10B8B_ERROR) & pData[1]) == 0x00) &&
       ((ScalerGetByte(PB_14_EQ_CRC_3) & pData[0]) != 0x00))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
bit ScalerDpRx1PhyCtsTp2Check(void)
{
    ScalerTimerDelayXms(10);

    switch(g_ucDpRx1PhyCtsCtrl & 0x30)
    {
        case 0x00: // Lane0 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), 0x00);

            pData[0] = 0x01;

            break;

        case 0x10: // Lane1 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT3);

            pData[0] = 0x02;

            break;

        case 0x20: // Lane2 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT4);

            pData[0] = 0x04;

            break;

        case 0x30: // Lane3 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            pData[0] = 0x08;

            break;

        default:

            pData[0] = 0x00;

            break;
    }

    // Mac Use Xtal Clk
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    // Clear EQ-CRC
    ScalerSetBit(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

    // Start Calculate EQ-CRC
    ScalerSetBit(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    ScalerTimerDelayXms(2);

    if((ScalerGetByte(PB_12_EQ_CRC_1) & pData[0]) != 0x00)
    {
        // Stop Calculate EQ-CRC
        ScalerSetBit(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

        return _TRUE;
    }

    // Stop Calculate EQ-CRC
    ScalerSetBit(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP PHY CTS Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1PhyCTS(void)
{
    // _ERROR_PRONE_CODE
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 50[0] = 0 --> PHY CTS Enable Start
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 51[2:0]) = 0x01 --> CDR
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 51[2:0]) = 0x02 --> EQ CRC
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 51[2:0]) = 0x03 --> PRBS7 Error Counter Reset and Counter Start
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 51[2:0]) = 0x04 --> PRBS7 Error Counter Read
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 51[2:0]) = 0x05 --> PHY CTS Disable
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 51[5:4]) = 00 --> lane0
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 51[5:4]) = 01 --> lane1
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 51[5:4]) = 10 --> lane2
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 51[5:4]) = 11 --> lane3
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 51[7:6]) = 00 --> RBR
    // g_ucDpRx1PhyCtsCtrl(Page0x1D 51[7:6]) = 01 --> HBR

    // ucPhyCtsAutoMode = 0x00 --> PHY CTS Manual Mode
    // ucPhyCtsAutoMode = 0xFF --> PHY CTS Auto Mode Enable
    // ucPhyCtsAutoMode = 0x01 --> PHY CTS TP1 Setphy
    // ucPhyCtsAutoMode = 0x11 --> PHY CTS TP1 Pass
    // ucPhyCtsAutoMode = 0xF1 --> PHY CTS TP1 Fail
    // ucPhyCtsAutoMode = 0x02 --> PHY CTS TP2 Setphy
    // ucPhyCtsAutoMode = 0x12 --> PHY CTS TP2 Pass
    // ucPhyCtsAutoMode = 0xF2 --> PHY CTS TP2 Fail
    // ucPhyCtsAutoMode = 0x03 --> PHY CTS Error Count Enable
    // ucPhyCtsAutoMode = 0x04 --> PHY CTS Error Count Lock
    // ucPhyCtsAutoMode = 0x05 --> PHY CTS Error Count Report

    WORD usErrorCount = 0;
    BYTE ucPhyCtsAutoMode = 0;

    g_ucDpRx1PhyCtsCtrl = 0x00;

    EX0 = 0;

    ScalerSetBit(P1D_50_CDR_01, ~(_BIT4 | _BIT3), ScalerGetBit(P1D_50_CDR_01, (_BIT2 | _BIT1)) << 2);

    if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x70, _BIT7) == _BIT7)
    {
        ucPhyCtsAutoMode = 0xFF;

        while(ucPhyCtsAutoMode != 0x00)
        {
            ScalerDebug();

            if(ucPhyCtsAutoMode == 0x11)
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x11);
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x11);
            }
            else if(ucPhyCtsAutoMode == 0x12)
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x77);
            }

            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x06, 0x22);
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x07, 0x22);

            switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x02) & (_BIT1 | _BIT0))
            {
                case 0x01: // CDR Lock Check

                    if(ucPhyCtsAutoMode != 0x11)
                    {
                        // Link Rate
                        switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00))
                        {
                            case 0x0A:

                                g_ucDpRx1PhyCtsCtrl = ((g_ucDpRx1PhyCtsCtrl & 0x3F) | (_BIT6));

                                break;

                            default:
                            case 0x06:

                                g_ucDpRx1PhyCtsCtrl = (g_ucDpRx1PhyCtsCtrl & 0x3F);

                                break;
                        }

                        // Lane Select
                        switch(ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
                        {
                            default:
                            case 0x00: // Source Lane0

                                g_ucDpRx1PhyCtsCtrl = ((g_ucDpRx1PhyCtsCtrl & 0xCF) | (_D1_DP_LANE0 << 4));

                                break;

                            case 0x10: // Source Lane1

                                g_ucDpRx1PhyCtsCtrl = ((g_ucDpRx1PhyCtsCtrl & 0xCF) | (_D1_DP_LANE1 << 4));

                                break;

                            case 0x20: // Source Lane2

                                g_ucDpRx1PhyCtsCtrl = ((g_ucDpRx1PhyCtsCtrl & 0xCF) | (_D1_DP_LANE2 << 4));

                                break;

                            case 0x30: // Source Lane3

                                g_ucDpRx1PhyCtsCtrl = ((g_ucDpRx1PhyCtsCtrl & 0xCF) | (_D1_DP_LANE3 << 4));

                                break;
                        }

                        SET_DP_RX1_AUX_MANUAL_MODE_PHY_CTS();

                        ScalerDpRx1PhyCtsTp1SetPhy(_DP_NF_REF_XTAL);

                        ucPhyCtsAutoMode = 0x01;
                    }

                    if(ucPhyCtsAutoMode == 0x01)
                    {
                        if(ScalerDpRx1PhyCtsTp1Check() == _TRUE)
                        {
                            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x11);
                            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x11);

                            ucPhyCtsAutoMode = 0x11;
                        }
                        else
                        {
                            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x00);
                            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x00);

                            ucPhyCtsAutoMode = 0xF1;
                        }

                        SET_DP_RX1_AUX_AUTO_MODE_PHY_CTS();
                    }

                    break;

                case 0x02: // Symbol Lock Check by TPS2
                case 0x03: // Symbol Lock Check by TPS3
                case 0x07: // Symbol Lock Check by TPS4

                    if((ucPhyCtsAutoMode == 0x11) || (ucPhyCtsAutoMode == 0xF2))
                    {
                        SET_DP_RX1_AUX_MANUAL_MODE_PHY_CTS();

                        ScalerDpRx1PhyCtsTp2SetPhy();

                        ucPhyCtsAutoMode = 0x02;
                    }

                    if(ucPhyCtsAutoMode == 0x02)
                    {
                        if(ScalerDpRx1PhyCtsTp2Check() == _TRUE)
                        {
                            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x77);

                            ucPhyCtsAutoMode = 0x12;
                        }
                        else
                        {
                            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x11);
                            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x11);

                            ucPhyCtsAutoMode = 0xF2;
                        }
                    }

                    SET_DP_RX1_AUX_AUTO_MODE_PHY_CTS();

                    if(ucPhyCtsAutoMode == 0x12)
                    {
                        // Mac Use Xtal Clk
                        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

                        // Error Count Lane Select
                        ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (g_ucDpRx1PhyCtsCtrl & (_BIT5 | _BIT4)) >> 1);

                        // Disable Error Detection
                        ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                        // Reverse PRBS7 Pattern Gen
                        ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~_BIT6, _BIT6);

                        // Disable Scramble
                        ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

                        // Reset DPCD Error Count
                        ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x10, 0x00);
                        ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x11, 0x00);
                        ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x12, 0x00);
                        ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x13, 0x00);
                        ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x14, 0x00);
                        ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x15, 0x00);
                        ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x16, 0x00);
                        ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x17, 0x00);

                        switch(ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
                        {
                            case (_BIT5 | _BIT4):

                                ScalerDpRx1SetDpcdBitValue(0x00, 0x02, 0x17, ~_BIT7, _BIT7);

                                break;

                            case (_BIT5):

                                ScalerDpRx1SetDpcdBitValue(0x00, 0x02, 0x15, ~_BIT7, _BIT7);

                                break;

                            case (_BIT4):

                                ScalerDpRx1SetDpcdBitValue(0x00, 0x02, 0x13, ~_BIT7, _BIT7);

                                break;

                            default:
                            case 0x00:

                                ScalerDpRx1SetDpcdBitValue(0x00, 0x02, 0x11, ~_BIT7, _BIT7);

                                break;
                        }
                    }

                    break;

                case 0x00:

                    if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, (0x0B + ((ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4))) >> 4))) != 0x00)
                    {
                        if(ucPhyCtsAutoMode != 0x05) // Error Count Enable
                        {
                            // Error Count Enable
                            ucPhyCtsAutoMode = 0x03;

                            switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, (0x0B + ((ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4))) >> 4))))
                            {
                                case 0x03: // PRBS7 Pattern

                                    // PRBS7 Pattern for RBR/HBR
                                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                                    ScalerTimerDelayXms(2);

                                    // Error Count Lock
                                    ucPhyCtsAutoMode = 0x05;

                                    // Disable Wildcard IRQ for Error Counter
                                    ScalerSetBit(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), 0x00);

                                    // Enable Read Error Counter IRQ, Clear IRQ Flag
                                    ScalerSetBit(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                                    break;

                                default:

                                    break;
                            }
                        }

                        while(ucPhyCtsAutoMode == 0x05) // Error Count Report
                        {
                            ScalerDebug();

                            usErrorCount = (((WORD)ScalerGetByte(PB_0B_BIST_PATTERN3)) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4);

                            ScalerTimerDelayXms(2);

                            switch(ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
                            {
                                case (_BIT5 | _BIT4):

                                    // Store Lane3 Error
                                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x16, LOBYTE(usErrorCount));
                                    ScalerDpRx1SetDpcdBitValue(0x00, 0x02, 0x17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                                    break;

                                case (_BIT5):

                                    // Store Lane2 Error
                                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x14, LOBYTE(usErrorCount));
                                    ScalerDpRx1SetDpcdBitValue(0x00, 0x02, 0x15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                                    break;

                                case (_BIT4):

                                    // Store Lane1 Error
                                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x12, LOBYTE(usErrorCount));
                                    ScalerDpRx1SetDpcdBitValue(0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                                    break;

                                default:
                                case 0x00:

                                    // Store Lane0 Error
                                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x10, LOBYTE(usErrorCount));
                                    ScalerDpRx1SetDpcdBitValue(0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                                    break;
                            }

                            // If DPCD 0x0021xh Hit
                            if(ScalerGetBit(PBA_FB_DUMMY_1, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
                            {
                                // Clear IRQ Flag
                                ScalerSetBit(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT1);

                                // Reset 8B/10B Error Counter
                                ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                                ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                            }
                            else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, (0x0B + ((ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4))) >> 4))) == 0x00)
                            {
                                ucPhyCtsAutoMode = 0xFF;
                            }
                        }
                    }
                    else if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x70, _BIT7) == 0x00)
                    {
                        ucPhyCtsAutoMode = 0x00;
                    }

                    break;

                default:

                    break;
            }
        }
    }
    else
    {
        while(GET_DP_RX1_PHY_CTS_FLG() == _TRUE)
        {
            ScalerDebug();

            DebugMessageRx1("7. PHY CTS Loop", ScalerGetByte(P1D_51_CDR_02));

            switch(ScalerGetByte(P1D_51_CDR_02) & 0x30)
            {
                default:
                case 0x00: // Source Lane0

                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _D1_DP_LANE0 << 4);

                    break;

                case 0x10: // Source Lane1

                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _D1_DP_LANE1 << 4);

                    break;

                case 0x20: // Source Lane2

                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _D1_DP_LANE2 << 4);

                    break;

                case 0x30: // Source Lane3

                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _D1_DP_LANE3 << 4);

                    break;
            }

            ScalerRead(P1D_51_CDR_02, 1, &g_ucDpRx1PhyCtsCtrl, _NON_AUTOINC);

            DebugMessageRx1("7. PHY CTS Loop", g_ucDpRx1PhyCtsCtrl);

            switch(g_ucDpRx1PhyCtsCtrl & 0x07)
            {
                case 0x01: // CDR Lock Check

                    ScalerSetByte(P1D_51_CDR_02, (g_ucDpRx1PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0))); // Clear DP PHY CTS Phase Info

                    ScalerDpRx1PhyCtsTp1SetPhy(_DP_NF_REF_XTAL);

                    if(ScalerDpRx1PhyCtsTp1Check() == _TRUE)
                    {
                        ScalerSetBit(P1D_50_CDR_01, ~_BIT5, _BIT5);
                    }
                    else
                    {
                        ScalerSetBit(P1D_50_CDR_01, ~_BIT5, 0x00);
                    }

                    break;

                case 0x02: // Symbol Lock Check

                    ScalerSetByte(P1D_51_CDR_02, (g_ucDpRx1PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                    ScalerDpRx1PhyCtsTp2SetPhy();

                    if(ScalerDpRx1PhyCtsTp2Check() == _TRUE)
                    {
                        ScalerSetBit(P1D_50_CDR_01, ~_BIT6, _BIT6);
                    }
                    else
                    {
                        ScalerSetBit(P1D_50_CDR_01, ~_BIT6, 0x00);
                    }

                    break;

                case 0x03:

                    ScalerSetByte(P1D_51_CDR_02, (g_ucDpRx1PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                    switch(g_ucDpRx1PhyCtsCtrl & 0x30)
                    {
                        case 0x00: // Lane0 Test

                            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), 0x00);

                            break;

                        case 0x10: // Lane1 Test

                            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT3);

                            break;

                        case 0x20: // Lane2 Test

                            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT4);

                            break;

                        case 0x30: // Lane3 Test

                            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

                            break;

                        default:
                            break;
                    }

                    // Disable Scramble
                    ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

                    // Reverse PRBS7 Pattern Gen
                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~_BIT6, _BIT6);

                    // Disable PRBS7 Error Detection
                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // Waiting for PHY Stable
                    ScalerTimerDelayXms(10);

                    // PRBS7 Pattern for RBR/HBR
                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    break;

                case 0x04:

                    ScalerSetByte(P1D_51_CDR_02, (g_ucDpRx1PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                    break;

                case 0x05:

                    ScalerSetByte(P1D_51_CDR_02, (g_ucDpRx1PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                    // Disable PRBS7 Error Detection
                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    CLR_DP_RX1_PHY_CTS_FLG();

                    break;

                default:

                    // Clear DP PHY CTS Control Register
                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                    break;
            }

            if((g_ucDpRx1PhyCtsCtrl & 0x07) != 0x05)
            {
                if(((ScalerGetByte(P1D_51_CDR_02) & 0x30) >> 4) == _D1_DP_LANE0) // Source Lane0
                {
                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _DP_SCALER_LANE0 << 4);
                }
                else if(((ScalerGetByte(P1D_51_CDR_02) & 0x30) >> 4) == _D1_DP_LANE1) // Source Lane1
                {
                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _DP_SCALER_LANE1 << 4);
                }
                else if(((ScalerGetByte(P1D_51_CDR_02) & 0x30) >> 4) == _D1_DP_LANE2) // Source Lane2
                {
                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _DP_SCALER_LANE2 << 4);
                }
                else if(((ScalerGetByte(P1D_51_CDR_02) & 0x30) >> 4) == _D1_DP_LANE3) // Source Lane3
                {
                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _DP_SCALER_LANE3 << 4);
                }

                DebugMessageRx1("7. PHY CTS Loop (Swap Back)", ScalerGetByte(P1D_51_CDR_02));
            }
            else
            {
                g_ucDpRx1PhyCtsCtrl = 0x00;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow Watch Dog
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetFifoWD(bit bEn)
{
    ScalerSetBit(PB6_38_DP_VWD_CTRL, ~(_BIT5 | _BIT4), ((bEn == _ENABLE) ? (_BIT5 | _BIT4) : 0x00));
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetFifoIRQ(bit bEn)
{
    ScalerSetBit(PB6_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), ((bEn == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
}

//--------------------------------------------------
// Description  : Signal PreDetection for DP(Power Normal)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpRx1NormalPreDetect(void)
{
    // For Dp PHY CTS Test
    if((GET_DP_RX1_PHY_CTS_FLG() == _TRUE) || (ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x70, _BIT7) == _BIT7))
    {
        ScalerDpRx1PhyCTS();

        return _FALSE;
    }

    switch(GET_DP_EMBEDDED_SWITCH_SELECT())
    {
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_ASSR_MODE_SUPPORT == _ON))
        case _D1_INPUT_PORT:

            // ASSR Mode Setting
            ScalerDpRx1ASSRModeSetting();

            break;
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_ASSR_MODE_SUPPORT == _ON))
        case _D2_INPUT_PORT:

            // ASSR Mode Setting
            ScalerDpRx1ASSRModeSetting();

            break;
#endif

        default:
            break;
    }

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    // Check if source doing HDCP handshake while HDCP capability disable
    if(GET_DP_RX1_HDCP_HANDSHAKE_WO_CAP() == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    CLR_DP_RX1_SOURCE_TYPE_JUDGE();
#endif

    switch(GET_DP_RX1_LINK_TRAINING_STATUS())
    {
        case _DP_NORMAL_LINK_TRAINING_PASS:
        case _DP_LINK_STATUS_FAIL:

            CLR_DP_RX1_VALID_VIDEO_CHECK();

            if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpRx1DFECheck() == _TRUE) || (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpRx1MarginLinkCheck() == _TRUE) &&
               (ScalerDpRx1AlignCheck() == _TRUE) &&
               (ScalerDpRx1DecodeCheck() == _TRUE))
            {
                /*
                DebugMessageRx1("9. Lane0 LE Diff", (g_pucDpRx1LEMaxTemp[0] - g_pucDpRx1LEMinTemp[0]));
                DebugMessageRx1("9. Lane1 LE Diff", (g_pucDpRx1LEMaxTemp[1] - g_pucDpRx1LEMinTemp[1]));
                DebugMessageRx1("9. Lane2 LE Diff", (g_pucDpRx1LEMaxTemp[2] - g_pucDpRx1LEMinTemp[2]));
                DebugMessageRx1("9. Lane3 LE Diff", (g_pucDpRx1LEMaxTemp[3] - g_pucDpRx1LEMinTemp[3]));
                DebugMessageRx1("9. Lane0 LE Min", g_pucDpRx1LEMinTemp[0]);
                DebugMessageRx1("9. Lane1 LE Min", g_pucDpRx1LEMinTemp[1]);
                DebugMessageRx1("9. Lane2 LE Min", g_pucDpRx1LEMinTemp[2]);
                DebugMessageRx1("9. Lane3 LE Min", g_pucDpRx1LEMinTemp[3]);
                DebugMessageRx1("9. Lane0 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[0] - g_pucDpRx1Tap0MinTemp[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[1] - g_pucDpRx1Tap0MinTemp[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[2] - g_pucDpRx1Tap0MinTemp[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[3] - g_pucDpRx1Tap0MinTemp[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max", g_pucDpRx1Tap0MaxTemp[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max", g_pucDpRx1Tap0MaxTemp[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max", g_pucDpRx1Tap0MaxTemp[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max", g_pucDpRx1Tap0MaxTemp[3]);
                DebugMessageRx1("9. FLD Band", ScalerGetByte(PB_BF_LANE0_A_CDR_02));
                DebugMessageRx1("9. Best FLD Band", ScalerGetByte(PB_BE_LANE0_A_CDR_01));
                DebugMessageRx1("9. Lane0 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[0] - g_pucDpRx1Tap0MinTemp2[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[1] - g_pucDpRx1Tap0MinTemp2[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[2] - g_pucDpRx1Tap0MinTemp2[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[3] - g_pucDpRx1Tap0MinTemp2[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[3]);
                DebugMessageRx1("9. TP2 Check Result", g_ucDpRx1EQCRC);
                */

                switch(GET_DP_EMBEDDED_SWITCH_SELECT())
                {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                    case _D1_INPUT_PORT:
                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LONG_HOTPLUG_EVENT);
                        g_ucDpRx1FakeLTLaneCount = g_ucDpRx1LaneCount;
#endif
#if(_DP_ULTRA_HDR_SUPPORT == _ON)
                        ScalerSyncDpSecDataResetProc(_D1_INPUT_PORT);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                        if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                        {
                            // Need to delay 3 Frames totally after Secondary Data Block Reset
                            ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);
                        }
#endif
                        break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                    case _D2_INPUT_PORT:
                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ);
#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_LONG_HOTPLUG_EVENT);
                        g_ucDpRx1FakeLTLaneCount = g_ucDpRx1LaneCount;
#endif
#if(_DP_ULTRA_HDR_SUPPORT == _ON)
                        ScalerSyncDpSecDataResetProc(_D2_INPUT_PORT);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                        if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                        {
                            // Need to delay 3 Frames totally after Secondary Data Block Reset
                            ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);
                        }
#endif
                        break;
#endif
                    default:
                        break;
                }

                if(GET_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH() == _TRUE)
                {
#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                    if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                    {
                        ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);
                    }

                    CLR_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH();
                }

                SET_DP_RX1_AUX_MANUAL_MODE();

                if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL)
                {
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);

                    ScalerDpRx1ScrambleSetting();
                }

                SET_DP_RX1_AUX_AUTO_MODE();

                if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
                   (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
                {
                    return _FALSE;
                }

                return _TRUE;
            }
            else
            {
                DebugMessageRx1("7. Link Status Fail IRQ", 0);

                SET_DP_RX1_AUX_MANUAL_MODE();

                if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
                {
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_STATUS_FAIL);

                    switch(GET_DP_EMBEDDED_SWITCH_SELECT())
                    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                        case _D1_INPUT_PORT:
                            ScalerTimerActiveTimerEvent(100, _SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
                            break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                        case _D2_INPUT_PORT:
                            ScalerTimerActiveTimerEvent(100, _SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ);
                            break;
#endif
                        default:
                            break;
                    }
                }

                SET_DP_RX1_AUX_AUTO_MODE();
            }

            break;

        case _DP_LINK_TRAINING_FAIL:

            switch(GET_DP_EMBEDDED_SWITCH_SELECT())
            {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                case _D1_INPUT_PORT:
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
                    break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                case _D2_INPUT_PORT:
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ);
                    break;
#endif
                default:
                    break;
            }

            ScalerDpRx1LinkStatusIRQ();

            break;

        case _DP_FAKE_LINK_TRAINING_PASS:
        case _DP_FAKE_LINK_TRAINING_PASS_VBIOS:

            CLR_DP_RX1_VALID_VIDEO_CHECK();

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
            if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
            {
                ScalerTimerDelayXms(30);
            }

            DebugMessageRx1("7. DP Rebuild PHY", GET_DP_RX1_LINK_TRAINING_STATUS());

            switch(GET_DP_EMBEDDED_SWITCH_SELECT())
            {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                case _D1_INPUT_PORT:
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
                    break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                case _D2_INPUT_PORT:
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ);
                    break;
#endif
                default:
                    break;
            }

            SET_DP_RX1_AUX_MANUAL_MODE();

            if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
            {
                ScalerDpRx1RebuildPhy(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01));

                SET_DP_RX1_AUX_AUTO_MODE();

                ScalerDpRx1PassiveDFEFineTune();
            }

            SET_DP_RX1_AUX_AUTO_MODE();

            // De-Skew Circuit Reset
            ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
            ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

            // Mac Reset After Link Clock Stable
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

            // Delay for Lane Alignment after Mac Reset
            ScalerTimerDelayXms(2);

            if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS)
            {
                ScalerDpRx1DecodeErrorCountReset();
            }

            if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpRx1DFECheck() == _TRUE) || (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpRx1MarginLinkCheck() == _TRUE) &&
               (ScalerDpRx1AlignCheck() == _TRUE) &&
               (ScalerDpRx1DecodeCheck() == _TRUE))
            {
                DebugMessageRx1("7. Rebuild Phy Pass", 0);

                /*
                DebugMessageRx1("9. Lane0 LE Diff", (g_pucDpRx1LEMaxTemp[0] - g_pucDpRx1LEMinTemp[0]));
                DebugMessageRx1("9. Lane1 LE Diff", (g_pucDpRx1LEMaxTemp[1] - g_pucDpRx1LEMinTemp[1]));
                DebugMessageRx1("9. Lane2 LE Diff", (g_pucDpRx1LEMaxTemp[2] - g_pucDpRx1LEMinTemp[2]));
                DebugMessageRx1("9. Lane3 LE Diff", (g_pucDpRx1LEMaxTemp[3] - g_pucDpRx1LEMinTemp[3]));
                DebugMessageRx1("9. Lane0 LE Min", g_pucDpRx1LEMinTemp[0]);
                DebugMessageRx1("9. Lane1 LE Min", g_pucDpRx1LEMinTemp[1]);
                DebugMessageRx1("9. Lane2 LE Min", g_pucDpRx1LEMinTemp[2]);
                DebugMessageRx1("9. Lane3 LE Min", g_pucDpRx1LEMinTemp[3]);
                DebugMessageRx1("9. Lane0 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[0] - g_pucDpRx1Tap0MinTemp[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[1] - g_pucDpRx1Tap0MinTemp[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[2] - g_pucDpRx1Tap0MinTemp[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[3] - g_pucDpRx1Tap0MinTemp[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max", g_pucDpRx1Tap0MaxTemp[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max", g_pucDpRx1Tap0MaxTemp[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max", g_pucDpRx1Tap0MaxTemp[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max", g_pucDpRx1Tap0MaxTemp[3]);
                DebugMessageRx1("9. FLD Band", ScalerGetByte(PB_BF_LANE0_A_CDR_02));
                DebugMessageRx1("9. Best FLD Band", ScalerGetByte(PB_BE_LANE0_A_CDR_01));
                DebugMessageRx1("9. D10.2 Counter", g_usDpRx1ClockCount);
                DebugMessageRx1("9. D10.2 Counter1", g_usDpRx1ClockCount1);
                DebugMessageRx1("9. Lane0 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[0] - g_pucDpRx1Tap0MinTemp2[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[1] - g_pucDpRx1Tap0MinTemp2[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[2] - g_pucDpRx1Tap0MinTemp2[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[3] - g_pucDpRx1Tap0MinTemp2[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[3]);
                DebugMessageRx1("9. Best FLD Band", ScalerGetByte(PB_BE_LANE0_A_CDR_01));
                DebugMessageRx1("9. TP2 Check Result", g_ucDpRx1EQCRC);
                DebugMessageRx1("9. DP Requeset", ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x06));
                DebugMessageRx1("9. DP Requeset", ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x07));
                DebugMessageRx1("9. Lane0 Tap1 Max", ScalerGetByte(P1D_A5_L0_INIT_3));
                DebugMessageRx1("9. Lane1 Tap1 Max", ScalerGetByte(P1D_B5_L1_INIT_3));
                DebugMessageRx1("9. Lane2 Tap1 Max", ScalerGetByte(P1D_C5_L2_INIT_3));
                DebugMessageRx1("9. Lane3 Tap1 Max", ScalerGetByte(P1D_D5_L3_INIT_3));
                */

                SET_DP_RX1_AUX_MANUAL_MODE();

                if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
                {
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);
                    CLR_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH();

                    ScalerDpRx1ScrambleSetting();
                }

                SET_DP_RX1_AUX_AUTO_MODE();

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
                switch(GET_DP_EMBEDDED_SWITCH_SELECT())
                {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                    case _D1_INPUT_PORT:
                        ScalerSyncDpSecDataResetProc(_D1_INPUT_PORT);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                        if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                        {
                            // Need to delay 3 Frames totally after Secondary Data Block Reset
                            ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);
                        }

                        break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                    case _D2_INPUT_PORT:
                        ScalerSyncDpSecDataResetProc(_D2_INPUT_PORT);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                        if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                        {
                            // Need to delay 3 Frames totally after Secondary Data Block Reset
                            ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);
                        }

                        break;
#endif
                    default:
                        break;
                }
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                {
                    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);
                }

                if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
                   (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
                {
                    return _FALSE;
                }

                return _TRUE;
            }
            else
            {
                DebugMessageRx1("7. DP Rebuild PHY Fail", 0);

                SET_DP_RX1_AUX_MANUAL_MODE();

                if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS)
                {
                    ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);

                    ScalerDpRx1HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    ScalerDpRx1Hdcp2ResetProc();
#endif
                }
                else if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS)
                {
#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
                    ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX1_LONG_HOTPLUG_EVENT);
#endif
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_STATUS_FAIL);

                    SET_DP_RX1_AUX_AUTO_MODE();

                    return _TRUE;
                }

                SET_DP_RX1_AUX_AUTO_MODE();
            }

            break;

        case _DP_LINK_TRAINING_NONE:

            if(GET_DP_RX1_VALID_VIDEO_CHECK() == _TRUE)
            {
                ScalerDpRx1ValidSignalDetection();

                DebugMessageRx1("7. VBIOS Check !!!!!!!", GET_DP_RX1_FAKE_LINK_TRAINING());
            }

            break;

        default:

            break;
    }

    if(GET_DP_RX1_VALID_VIDEO_CHECK() == _TRUE)
    {
        CLR_DP_RX1_VALID_VIDEO_CHECK();
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : None
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDpRx1ScanInputPort(void)
{
    if(GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _SOURCE_NONE;
    }

    // 2nd Scramble Setting Sync
    ScalerDpRx1ScrambleSetting();

    if(ScalerDpRx1HdcpCheck() == _FALSE)
    {
        DebugMessageRx1("7. DP HDCP Check Fail", 0);

        ScalerDpRx1CpIRQ(_DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

#if(_DP_LONG_HPD_AFTER_CPIRQ_SUPPORT == _ON)
        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            case _D1_INPUT_PORT:
                ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
                break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            case _D2_INPUT_PORT:
                ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT);
                break;
#endif
            default:
                break;
        }
#endif

        return _SOURCE_NONE;
    }

    if(ScalerDpRx1GetVideoStream() == _FALSE)
    {
        DebugMessageRx1("7. DP Video Stream Fail", 0);

        return _SOURCE_NONE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x07) & _BIT7) == _BIT7)
    {
        SET_DP_FREESYNC_ENABLED();
    }
    else
    {
        CLR_FREESYNC_ENABLED();
    }
#endif

    if(ScalerDpRx1MSACheck() == _FALSE)
    {
        DebugMessageRx1("7. DP MSA Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx1GetVideoInfo() == _FALSE)
    {
        DebugMessageRx1("7. DP Get Video Info Fail", 0);

        return _SOURCE_NONE;
    }
    else
    {
        ScalerDpRx1SetColorInfo();
    }

    if(ScalerDpRx1DisplayFormatSetting() == _FALSE)
    {
        DebugMessageRx1("7. DP Display Format Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx1StreamClkRegenerate() == _FALSE)
    {
        DebugMessageRx1("7. DP SteamClk Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx1FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() == _TRUE)
        {
            return _SOURCE_NONE;
        }
        else
#endif
        {
#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if((ScalerSyncCheckUrgentEvent() == _TRUE))
            {
                return _SOURCE_NONE;
            }
#endif

            ScalerDpRx1AdjustVsyncDelay();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if((ScalerSyncCheckUrgentEvent() == _TRUE))
            {
                return _SOURCE_NONE;
            }
#endif

            if(ScalerDpRx1FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
            {
#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if((ScalerSyncCheckUrgentEvent() == _TRUE))
                {
                    return _SOURCE_NONE;
                }
#endif

                ScalerDpRx1AdjustVsyncDelay();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if((ScalerSyncCheckUrgentEvent() == _TRUE))
                {
                    return _SOURCE_NONE;
                }
#endif

                if(ScalerDpRx1FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
                {
                    DebugMessageRx1("7. DP Fifo Fail", 0);

                    return _SOURCE_NONE;
                }
            }
        }
    }

    switch(GET_DP_EMBEDDED_SWITCH_SELECT())
    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
            break;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT);
            break;
#endif
        default:
            break;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    // Measurement Enable for On-Line VFreq check
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);
#endif

    ScalerSetBit(PB5_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

#if(_AUDIO_SUPPORT == _ON)
    // Enable Audio Channel
    ScalerAudioDpAudioEnable(_ENABLE, _D1_INPUT_PORT);
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    ScalerDpRx1InfoFrameRSV0Initial();
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    ScalerFreeSyncDpRx1GetSPDVfreqMaxMin();
#endif

#if((_DP_HDR10_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
    ScalerDpRx1SwitchHDR10CmpAudioInfo();
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    ScalerDpRx1TimingInfoBackup();
#endif

    DebugMessageRx1("Source DP Rx1 Found", 0);

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    SET_DP_RX1_SOURCE_TYPE_JUDGE();
#endif

    return _SOURCE_DP;
}

//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : None
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpRx1StableDetect(void)
{
#if(_DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER == _ON)
    if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
#else
    if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
       (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
#endif
    {
        DebugMessageRx1("7. DP Power Down", 0);

        return _FALSE;
    }

    if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE) ||
       (ScalerDpRx1AlignCheck() == _FALSE) ||
       (ScalerDpRx1DecodeCheck() == _FALSE) ||
       ((ScalerDpRx1DFECheck() == _FALSE) && (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE)))
    {
        DebugMessageRx1("7. DP Link Fail", 0);

        return _FALSE;
    }

    if(ScalerDpRx1GetVideoStream() == _FALSE)
    {
        DebugMessageRx1("7. DP Video Stream Fail", 0);

        return _FALSE;
    }

    if(ScalerDpRx1MiscCheck() == _FALSE)
    {
        DebugMessageRx1("7. DP Misc Change", 0);

        return _FALSE;
    }

    if(ScalerDpRx1FifoCheck(_DP_FIFO_POLLING_CHECK) == _FALSE)
    {
        DebugMessageRx1("7. Fifo Under/Overflow", 0);

        return _FALSE;
    }

    if(ScalerDpRx1MSAActiveChange() == _TRUE)
    {
        DebugMessageRx1("7. MSA Timing Change", 0);

        return _FALSE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(ScalerDpRx1GetFREESYNCStatusChange() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Clear CPIRQ Flag
    ScalerDpRx1CheckHdcpCpirqStatus();

    ScalerDpRx1CrcCalculate();

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP RGB Output Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AVMute(void)
{
    if(ScalerGetBit(PB6_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Set free run & force to BG
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT5 | _BIT3), _BIT5);
    }

    // Disable fifo overflwo/ underflwo IRQ
    ScalerSetBit(PB6_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

    // Disable RGB Output
    ScalerSetBit(PB5_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#if(_AUDIO_SUPPORT == _ON)
    // Disable Audio Channel
    ScalerAudioDpAudioEnable(_DISABLE, _D1_INPUT_PORT);
#endif
}
//--------------------------------------------------
// Description  : DP Adjust Vsync Delay
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AdjustVsyncDelay(void)
{
    DWORD ulBStoVSDelayDeltaOverflow = 0;
    DWORD ulBStoVSDelayDeltaUnderflow = 0;

    if(ScalerGetBit(PB5_21_PG_CTRL_1, (_BIT1 | _BIT0)) == 0x00)// Fifo Ok
    {
        return;
    }
    else if(ScalerGetBit(PB5_21_PG_CTRL_1, _BIT0) == _BIT0) // Fifo Overflow
    {
        // Get Htotal
        ScalerRead(PB6_08_MSA_HTT_0, 2, &pData[0], _AUTOINC);

        // ((Link Clk * 256)/ Stream CLK) * Htotal / 256 --> 1 Line
        ulBStoVSDelayDeltaOverflow = (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 270UL) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(0)) / 256;

        DebugMessageRx1("7. Fifo Overflow --> nVidia Case", ulBStoVSDelayDeltaOverflow);
    }
    else if(ScalerGetBit(PB5_21_PG_CTRL_1, _BIT1) == _BIT1) // Fifo Underflow
    {
        // Get Hactive
        ScalerRead(PB6_0C_MSA_HWD_0, 2, &pData[0], _AUTOINC);

        if(PDATA_WORD(0) != 1366)
        {
            return;
        }

        PDATA_WORD(0) = PDATA_WORD(0) - 2;

        // Set Hactive
        ScalerSetBit(PB5_45_MN_DPF_HWD_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
        ScalerSetByte(PB5_46_MN_DPF_HWD_L, LOBYTE(PDATA_WORD(0)));

        // ((Link Clk * 2)/ Stream CLK) --> 2 pixels
        ulBStoVSDelayDeltaUnderflow = (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 270) * 2) / ((DWORD)GET_INPUT_PIXEL_CLK());

        DebugMessageRx1("7. Fifo Underflow --> QD882 Case", ulBStoVSDelayDeltaUnderflow);
    }

    // For Initial Value Before Use PDATA_DWORD(0)
    pData[0] = 0;

    // Get BStoVSDelay Even
    ScalerRead(PB5_32_EVBLK2VS_H, 3, &pData[1], _AUTOINC);

    // For Initial Value Before Use PDATA_DWORD(1)
    pData[4] = 0;

    // Get BStoVSDelay Odd
    ScalerRead(PB5_35_OVBLK2VS_H, 3, &pData[5], _AUTOINC);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    PDATA_DWORD(0) = PDATA_DWORD(0) - ((ulBStoVSDelayDeltaOverflow + ulBStoVSDelayDeltaUnderflow) / 2);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    PDATA_DWORD(1) = PDATA_DWORD(1) - ((ulBStoVSDelayDeltaOverflow + ulBStoVSDelayDeltaUnderflow) / 2);

    // Set Even Field BS to VS Delay
    ScalerSetByte(PB5_32_EVBLK2VS_H, pData[1]);
    ScalerSetByte(PB5_33_EVBLK2VS_M, pData[2]);
    ScalerSetByte(PB5_34_EVBLK2VS_L, pData[3]);

    // Set Odd Field BS to VS Delay
    ScalerSetByte(PB5_35_OVBLK2VS_H, pData[5]);
    ScalerSetByte(PB5_36_OVBLK2VS_M, pData[6]);
    ScalerSetByte(PB5_37_OVBLK2VS_L, pData[7]);

    // Double Buffer to Apply Display Format Setting (RL6492 has no double buffer for display format setting)
    // ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT6, _BIT6);

    // Reset Display Format Gen
    ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT7, _BIT7);

    // Polling Vertical BS
    ScalerTimerPollingFlagProc(50, PB6_01_DP_VBID, _BIT0, _TRUE);

    // Delay for PG Stable
    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);
}
//--------------------------------------------------
// Description  : Check Valid Lane Alignment
// Input Value  : None
// Output Value : True --> Align
//--------------------------------------------------
bit ScalerDpRx1AlignCheck(void)
{
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)

    if(GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE)
    {
        if(GET_DP_RX1_SOURCE_TYPE_JUDGE() == _FALSE)
        {
#if(_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON)
            if(ScalerDpRx1LaneValidCheck() == _FALSE)
            {
                return _TRUE;
            }
#else
            return _TRUE;
#endif
        }
    }

#endif

    if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F) == _DP_ONE_LANE)
    {
        return _TRUE;
    }
    else
    {
        if(ScalerGetBit(PB_0E_DESKEW_PHY, _BIT4) == 0x00)
        {
            if(ScalerGetBit(PB_0E_DESKEW_PHY, (_BIT7 | _BIT6)) != (_BIT7 | _BIT6))
            {
                ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                ScalerTimerDelayXms(3);
            }
            else
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Scramble Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ScrambleSetting(void)
{
    BYTE ucBackUp = ScalerGetByte(PBA_D0_AUX_MODE_SET);
    bit bEnhanceChange = _FALSE;
    bit bScrambleChange = _FALSE;

    SET_DP_RX1_AUX_MANUAL_MODE();

    if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x01, _BIT7) == _BIT7) != (ScalerGetBit(PB_01_PHY_DIG_RESET_CTRL, _BIT2) == _BIT2))
    {
        bEnhanceChange = _TRUE;

        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x01, _BIT7) == _BIT7)
        {
            // Enable Enhancement Control Mode --> MAC
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
        }
        else
        {
            // Disable Enhancement Control Mode --> MAC
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
        }
    }

    if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x02, _BIT5) == _BIT5) != (ScalerGetBit(PB_07_SCRAMBLE_CTRL, _BIT5) == _BIT5))
    {
        bScrambleChange = _TRUE;

        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x02, _BIT5) == _BIT5)
        {
            // Disable Scrambling
            ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
        }
        else
        {
            // Enable Scrambling
            ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
        }
    }

    if((bEnhanceChange == _TRUE) || (bScrambleChange == _TRUE))
    {
        SET_DP_RX1_AUX_AUTO_MODE();

        // Delay 2ms for Scramble
        ScalerTimerDelayXms(2);

        SET_DP_RX1_AUX_MANUAL_MODE();
    }

    if((ucBackUp & _BIT1) == _BIT1)
    {
        SET_DP_RX1_AUX_AUTO_MODE();
    }
}

#if((_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON) && (_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Check Lane Valid
// Input Value  : None
// Output Value : True --> ok, False --> Lane Valid Error
//--------------------------------------------------
bit ScalerDpRx1LaneValidCheck(void)
{
    // Enable Lane Valid Detect
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT3, 0x00);
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT3, _BIT3);

    // Delay Time us [150,x]
    DELAY_XUS(150);

    switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_ONE_LANE:

            if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit(PB_00_HD_DP_SEL, _BIT7) == 0x00)) ||
               ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit(PB_00_HD_DP_SEL, _BIT6) == 0x00)) ||
               ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit(PB_00_HD_DP_SEL, _BIT5) == 0x00)) ||
               ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit(PB_00_HD_DP_SEL, _BIT4) == 0x00)))
            {
                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            if(((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT7 | _BIT6)) == 0x00)) ||
               ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT7 | _BIT5)) == 0x00)) ||
               ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT7 | _BIT4)) == 0x00)) ||
               ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT6 | _BIT5)) == 0x00)) ||
               ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT6 | _BIT4)) == 0x00)) ||
               ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2))) &&
                (ScalerGetBit(PB_00_HD_DP_SEL, (_BIT5 | _BIT4)) == 0x00)))
            {
                return _FALSE;
            }

            break;

        case _DP_FOUR_LANE:

            if(ScalerGetBit(PB_00_HD_DP_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
            {
                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Clear CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CheckHdcpCpirqStatus(void)
{
    if((ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
    {
        if((ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) & _BIT2) == _BIT2)
        {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Check HDCP22 decode
            if(GET_DP_RX1_HDCP_MODE() == _HDCP_22)
            {
                if(ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) == 0x00)
                {
                    // Clear Link Status CPIRQ Flag
                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) & ~_BIT2));
                }
            }
            else
#endif
            {
                if(ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) == 0x00)
                {
                    // Clear Link Status CPIRQ Flag
                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) & ~_BIT2));
                }
            }
        }
    }
}

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check VGIP VS bypass for DP
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpRx1CheckVgipVsBypass(void)
{
    // Get Hstart
    ScalerRead(PB5_43_MN_DPF_HST_M, 2, &pData[0], _AUTOINC);

    // Get Vstart
    ScalerRead(PB5_4B_MN_DPF_VST_M, 2, &pData[2], _AUTOINC);

    // Check for nVedia 2560x1440@144Hz timing (reduced blanking)
    if((PDATA_WORD(0) < _VGIP_IH_CAPTURE_MIN_VALUE) ||
       (PDATA_WORD(1) <= _VGIP_IV_CAPTURE_MIN_VALUE))
    {
        DebugMessageRx1("DP RX1 VGIP VS Bypass Mode", PDATA_WORD(0));

        return _TRUE;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DP CRC Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CrcCalculate(void)
{
    if(GET_DP_RX1_CRC_CALCULATE() == _TRUE)
    {
        DebugMessageRx1("7. DP CRC Test Start", 0);

        if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
        {
            ScalerSetBit(PB5_70_DP_CRC_CTRL, ~_BIT4, _BIT4);
        }
        else
        {
            ScalerSetBit(PB5_70_DP_CRC_CTRL, ~_BIT4, 0x00);
        }

        // Start CRC Calculation
        ScalerSetBit(PB5_70_DP_CRC_CTRL, ~_BIT7, _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB5_70_DP_CRC_CTRL, _BIT6, _TRUE) == _TRUE)
        {
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x40, ScalerGetByte(PB5_72_DP_CRC_R_L));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x41, ScalerGetByte(PB5_71_DP_CRC_R_M));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x42, ScalerGetByte(PB5_74_DP_CRC_G_L));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x43, ScalerGetByte(PB5_73_DP_CRC_G_M));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x44, ScalerGetByte(PB5_76_DP_CRC_B_L));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x45, ScalerGetByte(PB5_75_DP_CRC_B_M));

            CLR_DP_RX1_CRC_CALCULATE();

            // Update _TEST_CRC_COUNT
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x46, 0x21);
        }

        // Stop CRC Calculation
        ScalerSetBit(PB5_70_DP_CRC_CTRL, ~_BIT7, 0x00);
    }
}
#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
//--------------------------------------------------
// Description  : DP Hs Tracking Active Region Setting
// Input Value  : Hs Tracking Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType)
{
    if(enumHSTrackingType == _DP_HS_TRACKING_FW_MODE)
    {
        // HS Tracking Region By FW Setting
        ScalerSetBit(PB5_B9_MN_SCLKG_SDM_TEST, ~_BIT7, _BIT7);

        // BE Start Num = 2 line
        ScalerSetBit(PB5_C7_VBID_MAN_MADE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

        // BE End Num = 2 line
        ScalerSetBit(PB5_C7_VBID_MAN_MADE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // HS Tracking Region By FW Setting
        ScalerSetBit(PB5_B9_MN_SCLKG_SDM_TEST, ~_BIT7, 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetNoVideoStreamIRQ(bit bEn)
{
    // VB-ID[3] Change Flag
    ScalerSetBit(PB6_36_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

    // VB-ID[3] Change IRQ
    ScalerSetBit(PB6_3B_DP_IRQ_CTRL1, ~_BIT4, ((bEn == _ENABLE) ? _BIT4 : 0x00));
}

//--------------------------------------------------
// Description  : DPCD Link Status Field Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus)
{
    pData[0] = ScalerGetByte(PBA_D0_AUX_MODE_SET);

    SET_DP_RX1_AUX_MANUAL_MODE();

    if(enumDpResetStatus == _DP_DPCD_LINK_STATUS_INITIAL)
    {
        // Set DPCD 00600h to 0x01
        ScalerDpRx1SetDpcdBitValue(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x04, 0x80);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x06, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x07, 0x00);

    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    CLR_DP_RX1_BACKUP_PD_LINK_STATUS_FLG();

    if((pData[0] & _BIT1) == _BIT1)
    {
        SET_DP_RX1_AUX_AUTO_MODE();
    }
}
//--------------------------------------------------
// Description  : DP BS to VS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
DWORD ScalerDpRx1GetBStoVSDelay(void)
{
    DWORD ulVFrontPorch = 0;
    DWORD ulHFrontPorch = 0;
    WORD usFifoOffset = 0;

    // Get Htotal
    ScalerRead(PB6_08_MSA_HTT_0, 2, &pData[2], _AUTOINC);

    // VFrontPorch = 3 * Htotal * (Link Clk / Stream CLK)
    ulVFrontPorch = ((DWORD)GET_DP_RX1_VFRONT_PORCH()) * ((DWORD)PDATA_WORD(1) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) *
                    ((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 270) / 256;

    // Get Hactive
    ScalerRead(PB6_0C_MSA_HWD_0, 2, pData, _AUTOINC);

    // Get HSW
    pData[4] = ScalerGetBit(PB6_0E_MSA_HSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    pData[5] = ScalerGetByte(PB6_0F_MSA_HSW_1);

    // Get HSW min by Measure clock
    PDATA_WORD(3) = ((DWORD) _DP_HSYNC_WIDTH_MEASURE_COUNTER * GET_INPUT_PIXEL_CLK() * 100) / _MEASURE_CLK + 1;

    // Check HSW <= HSW min
    if(PDATA_WORD(2) <= PDATA_WORD(3))
    {
        // Check if H porch is more than HSW min
        if((PDATA_WORD(1) - PDATA_WORD(0)) >= PDATA_WORD(3))
        {
            // HSW = HSW min
            PDATA_WORD(2) = PDATA_WORD(3);
        }
        else
        {
            // HSW = Max H Porch
            PDATA_WORD(2) = (PDATA_WORD(1) - PDATA_WORD(0));
        }
    }

    // DPF H Front Porch must not be less than 8 (HW constraint)
    // Check if H porch is more than 8
    if((PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(2)) <= _DP_HSYNC_FRONT_PORCH)
    {
        // HSW < HSW min
        if(PDATA_WORD(2) < PDATA_WORD(3))
        {
            // Hstart = HSW
            PDATA_WORD(4) = PDATA_WORD(2);
        }
        else if((PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(3) >= _DP_HSYNC_FRONT_PORCH))
        {
            // HSW = H porch - _DP_HSYNC_FRONT_PORCH
            PDATA_WORD(2) = PDATA_WORD(1) - PDATA_WORD(0) - _DP_HSYNC_FRONT_PORCH;

            // Hstart = HSW
            PDATA_WORD(4) = PDATA_WORD(2);
        }
        else
        {
            // HSW = HSW min
            PDATA_WORD(2) = PDATA_WORD(3);

            // Hstart = HSW min
            PDATA_WORD(4) = PDATA_WORD(3);
        }
    }
    else
    {
        // Hstart = Htotal - Hactive - _DP_HSYNC_FRONT_PORCH
        PDATA_WORD(4) = PDATA_WORD(1) - PDATA_WORD(0) - _DP_HSYNC_FRONT_PORCH;
    }

    // HFrontPorch = (Htotal - Hactive - Hstart) * (Link Clk / Stream CLK)
    ulHFrontPorch = (((DWORD)(PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(4))) * (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_INPUT_PIXEL_CLK()));

    pData[15] = GET_COLOR_DEPTH();

    // DP fifo size = 256 x 96bit
    if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
    {
        // FifoOffset = (1/2 * (256 * 96) / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (4 * (WORD)pData[15]);
    }
    else
    {
        // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (6 * (WORD)pData[15]);
    }

    // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)) * (Link Clk / Stream CLK))
    usFifoOffset = (WORD)(((DWORD)usFifoOffset) * (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_INPUT_PIXEL_CLK()));

    return ((ulVFrontPorch + ulHFrontPorch + (DWORD)usFifoOffset) / 2);
}
//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetBit(PBA_C4_DPCD_DATA_PORT, ucDpcdBit);
}
//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte(PBA_C4_DPCD_DATA_PORT);
}
//--------------------------------------------------
// Description  : Check Dp Video Straam VBID
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpRx1GetVideoStream(void)
{
    if(ScalerGetBit(PB6_01_DP_VBID, _BIT3) == 0x00)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Before Hpd Toggle Process
// Input Value  : EnumDpHotPlugAssertType
// Output Value : None
//--------------------------------------------------
EnumDpHotPlugTime ScalerDpRx1BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType)
{
    if(enumHpdType == _DP_HPD_NONE)
    {
        return _DP_HPD_TIME_NONE;
    }

    if(enumHpdType == _DP_HPD_ASSERTED)
    {
        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            case _D1_INPUT_PORT:

                if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
                {
                    return _DP_HPD_TIME_NONE;
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            case _D2_INPUT_PORT:

                if(PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH)
                {
                    return _DP_HPD_TIME_NONE;
                }

                break;
#endif

            default:

                return _DP_HPD_TIME_NONE;
        }
    }

    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX1_DP_LINK_TRAINING_REBUILD_PHY);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_HOTPLUG_ASSERTED);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ);
#endif

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_WD_TIMER_INT_SUPPORT == _ON))
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE);
#endif

    if(enumHpdType != _DP_HPD_ASSERTED)
    {
        if(GET_REG_DP_RX1_MAC_ASSIGNED() == _TRUE)
        {
            ScalerDpRx1AVMute();
        }

        ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);

#if(_DP_HPD_LOW_AUX_NOT_REPLY_SUPPORT == _ON)
        // Reset Aux Phy
        ScalerSetBit(PBA_65_AUX_5, ~_BIT7, 0x00);
#endif
    }

    if(enumHpdType == _DP_HPD_LOW)
    {
        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            case _D1_INPUT_PORT:

                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

                DebugMessageRx1("_D1_HOT_PLUG_LOW", 0);


                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            case _D2_INPUT_PORT:

                PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);

                DebugMessageRx1("_D2_HOT_PLUG_LOW", 0);

                break;
#endif

            default:
                break;
        }

        return _DP_HPD_TIME_NONE;
    }
    else if(enumHpdType == _DP_HPD_LOW_RESET_AUX)
    {
        // Reset Aux Phy
        ScalerSetBit(PBA_65_AUX_5, ~_BIT7, 0x00);

        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            case _D1_INPUT_PORT:

                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

                DebugMessageRx1("_D1_HOT_PLUG_LOW", 0);

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            case _D2_INPUT_PORT:

                PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);

                DebugMessageRx1("_D2_HOT_PLUG_LOW", 0);

                break;
#endif

            default:
                break;
        }

        return _DP_HPD_TIME_NONE;
    }

    // Reset DDC1
    MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT1;

#if(_DP_FREESYNC_SUPPORT == _ON)
    SET_DP_RX1_AUX_MANUAL_MODE();
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x07, 0x00);
    SET_DP_RX1_AUX_AUTO_MODE();
#endif

    ScalerDpRx1HDCPUnplugReset();

    switch(GET_DP_EMBEDDED_SWITCH_SELECT())
    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

#if(_D1_DP_ASSR_MODE_SUPPORT == _ON)
            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0D, 0x01);

            SET_DP_RX1_AUX_MANUAL_MODE();
            ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
            SET_DP_RX1_AUX_AUTO_MODE();
#else
            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0D, 0x00);
#endif

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

        case _D2_INPUT_PORT:

#if(_D2_DP_ASSR_MODE_SUPPORT == _ON)
            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0D, 0x01);

            SET_DP_RX1_AUX_MANUAL_MODE();
            ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
            SET_DP_RX1_AUX_AUTO_MODE();
#else
            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0D, 0x00);
#endif

            break;
#endif

        default:
            break;
    }

    if(enumHpdType == _DP_LONG_HPD_EVENT)
    {
        return _DP_LONG_HPD_TIME;
    }
    else if(enumHpdType == _DP_HDCP_LONG_HPD_EVENT)
    {
        return _DP_HDCP_LONG_HPD_TIME;
    }
    else if(enumHpdType == _DP_MST_LONG_HPD_EVENT)
    {
        // Reset Aux Phy
        ScalerSetBit(PBA_65_AUX_5, ~_BIT7, 0x00);

        return _DP_MST_LONG_HPD_TIME;
    }
    else if(enumHpdType == _DP_HPD_ASSERTED)
    {
        return _DP_HPD_ASSERTED_TIME;
    }

    return _DP_HPD_TIME_NONE;
}

//--------------------------------------------------
// Description  : Dp After Hpd Toggle Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AfterHpdToggleProc(void)
{
    // Release Aux Phy
    ScalerSetBit(PBA_65_AUX_5, ~_BIT7, _BIT7);

    SET_DP_RX1_AUX_MANUAL_MODE();

    if((GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS) && (GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_LINK_TRAINING_PASS))
    {
        ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x00, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0xE0));
    }

    SET_DP_RX1_AUX_AUTO_MODE();

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    CLR_DP_RX1_HDCP_HANDSHAKE_WO_CAP();
#endif

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
    if(GET_DP_AUTO_SEARCH_SWITCH() == _FALSE)
#endif
    {
        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            case _D1_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
                {
                    ScalerTimerActiveTimerEvent(1200, _SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            case _D2_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D2_INPUT_PORT) == _TRUE)
                {
                    ScalerTimerActiveTimerEvent(1200, _SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);
                }

                break;
#endif

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Dp Rx1 Cancel ValidSignalDetect TimerEvent
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CancelValidSignalDetectTimerEvent(void)
{
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);
}

//--------------------------------------------------
// Description  : Initial Setting for DP
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport)
{
    ScalerDpRx1AuxPowerOnInitial();

    ScalerDpRx1DpcdInitial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumFreeSyncSupport);

    // Must be initialized "AFTER DPCD setting" to avoid entering interruption unexpectively
    ScalerDpRx1AuxIntInitial();

    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    SET_DP_RX1_FAKE_LINK_TRAINING();

    SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
    SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
    SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

    SET_DP_RX1_HDCP_MODE_BACKUP(_HDCP_14);

    ScalerDpRx1SetDpLaneMapping(_TYPE_C_PIN_ASSIGNMENT_C, _TYPE_C_ORIENTATION_UNFLIP);
}

//--------------------------------------------------
// Description  : DP Margin Link Check
// Input Value  : None
// Output Value : _TRUE : Link ok ; _FALSE : Margin Link
//--------------------------------------------------
bit ScalerDpRx1MarginLinkCheck(void)
{
    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1LinkStatusIRQ(void)
{
    SET_DP_RX1_AUX_MANUAL_MODE();

    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_FAIL) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
    {
        ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_RESET);

        SET_DP_RX1_AUX_AUTO_MODE();

        ScalerDpRx1HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        ScalerDpRx1Hdcp2ResetProc();
#endif

        if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
           (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))
        {
            if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
            {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
#endif
            }
            else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT)
            {
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT);
#endif
            }

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_WD_TIMER_INT_SUPPORT == _ON))
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE);
#endif

            ScalerDpRx1HpdIrqAssert();
        }
    }

    SET_DP_RX1_AUX_AUTO_MODE();
}

//-------------------------------------------------------
// Description  : Set Aux Diff mode or Single-eneded mode
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpRx1AuxSet(void)
{
    if(GET_DP_AUX_DIFF_MODE() == _FALSE)
    {
        // Set TX VLDO = 1.1V
        ScalerSetBit(PBA_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_AUX_SWING_1100_MV << 4));

        // Open AUX ADJR_P
        ScalerSetBit(PBA_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Rx Common Mode from 3.3V
        ScalerSetBit(PBA_60_DIG_TX_04, ~_BIT5, _BIT5);

        // [5]Enable Single-Ended Mode, [4:3]Aux Vth-->50mV, [0]Aux 50ohm auto K(Enable Big_Z0_P)
        ScalerSetByte(PBA_62_AUX_2, 0x29);

        // [4]Enable Big_Z0_N, [3:0]Open ADJR_N
        ScalerSetBit(PBA_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    }
    else
    {
        // Set TX VLDO = 1.1V
        ScalerSetBit(PBA_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_AUX_SWING_1100_MV << 4));

        // Rx Common Mode from 3.3V
        ScalerSetBit(PBA_60_DIG_TX_04, ~_BIT5, _BIT5);

        // [5]Disable Single-Ended Mode, [4:3]Aux Vth-->50mV, [0]Aux 50ohm auto K(Enable Big_Z0_P)
        ScalerSetByte(PBA_62_AUX_2, 0x09);

        // [4]Enable Big_Z0_N
        ScalerSetBit(PBA_66_AUX_6, ~_BIT4, _BIT4);

        // AUX RX1 P Channel Resistance Setting
        ScalerSetBit(PBA_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());

        // AUX RX1 N Channel Resistance Setting
        ScalerSetBit(PBA_66_AUX_6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());
    }
}

//--------------------------------------------------
// Description  : DP Error Counter Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ErrorCounterUpdate_EXINT0(void) using 1
{
    WORD usErrorTemp = 0;

    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            // Store Lane0 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE0 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x10, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            break;

        case _DP_TWO_LANE:

            // Store Lane0 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE0 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x10, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane1 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE1 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x12, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            break;

        default:
        case _DP_FOUR_LANE:

            // Store Lane0 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE0 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x10, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane1 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE1 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x12, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane2 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE2 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x14, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane3 Error
            ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE3 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x16, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            break;
    }

    // Reset 8B/10B Error Counter
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
}

//--------------------------------------------------
// Description  : DP Error Counter Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ErrorCounterDisable_EXINT0(void) using 1
{
    // Disable Wildcard IRQ for Error Counter
    ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), 0x00);

    // Disable 8B/10B Error Counter
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Enable DPCD Auto Increment
    ScalerSetBit_EXINT(PBA_C0_DPCD_CTRL, ~_BIT0, _BIT0);

    // Set DPCD 0x21xh
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, 0x00);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, 0x02);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, 0x10);

    // Set DPCD 0x210-0x217 = 0x00
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);

    // Disable DPCD Auto Increment
    ScalerSetBit_EXINT(PBA_C0_DPCD_CTRL, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : DP Error Counter Enable
// Input Value  : DP Link Training Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    // Enable DPCD Error Count Valid Flag
    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);

            break;

        case _DP_TWO_LANE:

            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~_BIT7, _BIT7);

            break;

        default:
        case _DP_FOUR_LANE:

            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~_BIT7, _BIT7);
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x15, ~_BIT7, _BIT7);
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x17, ~_BIT7, _BIT7);

            break;
    }

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        // Enable 8B/10B Error Counter
        ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
    }

    // Enable Read Error Counter IRQ, Clear IRQ Flag
    ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DecodeErrorCountReset_WDINT(void) using 3
{
    // Reset 8b10b Error Count Value
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Start Record 8b10b Error Count Value
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
}
#endif

//--------------------------------------------------
// Description  : Reset 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DecodeErrorCountReset(void)
{
    // Reset 8b10b Error Count Value
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Start Record 8b10b Error Count Value
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
}

//--------------------------------------------------
// Description  : Check DP Vactive / Hactive Information
// Input Value  : None
// Output Value : True --> DP Vactive / Hactive Information Check Ok
//--------------------------------------------------
bit ScalerDpRx1MSAActiveChange(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Display Format Hactive
    ScalerRead(PB5_45_MN_DPF_HWD_M, 2, &pData[0], _AUTOINC);

    // Get MSA Hactive
    ScalerRead(PB6_0C_MSA_HWD_0, 2, &pData[2], _AUTOINC);

    // Get Display Format Vactive
    ScalerRead(PB5_4D_MN_DPF_VHT_M, 2, &pData[4], _AUTOINC);

    // Get MSA Vactive
    ScalerRead(PB6_16_MSA_VHT_0, 2, &pData[6], _AUTOINC);

    if((PDATA_WORD(0) != PDATA_WORD(1)) || (PDATA_WORD(2) != PDATA_WORD(3)))
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpRx1PSPreDetect(void)
{
    // Back to noraml for DP PHY CTS
    if(GET_DP_RX1_PHY_CTS_FLG() == _TRUE)
    {
        return _TRUE;
    }

    if(GET_DP_RX1_VALID_VIDEO_CHECK() == _TRUE)
    {
        DebugMessageRx1("7. Valid Video Check", 0);

        return _TRUE;
    }

    if(GET_DP_RX1_PS_AUX_TOGGLE() == _TRUE)
    {
        DebugMessageRx1("7. Power Saving Aux Handshake", 0);

        return _TRUE;
    }

    if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        DebugMessageRx1("7. Normal Link Training under Fake Power Saving Case", 0);

        return _TRUE;
    }

    if(((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) &&
        ((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
         (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))) ||
       (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
    {
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))

        if(ScalerAudioGetDigitalAudioSource(_D1_INPUT_PORT) == _DIGITAL_AUDIO_SOURCE_DP)
        {
            DebugMessageAudio("00. DP Power Saving Audio : Idle Pattern Case", ScalerAudioGetDigitalAudioSource(_D1_INPUT_PORT));
            return _TRUE;
        }
#endif
        DebugMessageRx1("7. Idle Pattern Case", 0);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set DP Lane Mapping Type
// Input Value  : ucLanetype --> Lane Mapping Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation)
{
    if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
    {
        if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Lane 0 <--> Lane 2
            // Lane 1 <--> Lane 3
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_DP_RX1_PCB_LANE0_MAPPING(_D1_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D1_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D1_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D1_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(!_D1_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(!_D1_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(!_D1_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(!_D1_DP_PCB_LANE3_PN_SWAP);
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            SET_DP_RX1_PCB_LANE0_MAPPING(_D2_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D2_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D2_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D2_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(!_D2_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(!_D2_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(!_D2_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(!_D2_DP_PCB_LANE3_PN_SWAP);
#endif

#if(_D1_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
            // Enable Aux Digital Phy PN Swap
            ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
#else
            // Disable Aux Digital Phy PN Swap
            ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
#endif
        }
        else // Normal Cable Mode
        {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_DP_RX1_PCB_LANE0_MAPPING(_D1_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D1_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D1_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D1_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(_D1_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(_D1_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(_D1_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(_D1_DP_PCB_LANE3_PN_SWAP);
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            SET_DP_RX1_PCB_LANE0_MAPPING(_D2_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D2_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D2_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D2_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(_D2_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(_D2_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(_D2_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(_D2_DP_PCB_LANE3_PN_SWAP);
#endif

            // Disable Aux Digital Phy PN Swap
            ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
        }
    }
    else
    {
        if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Lane 0 <--> Lane 2
            // Lane 1 <--> Lane 3
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_DP_RX1_PCB_LANE0_MAPPING(_D1_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D1_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D1_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D1_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(!_D1_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(!_D1_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(!_D1_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(!_D1_DP_PCB_LANE3_PN_SWAP);
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            SET_DP_RX1_PCB_LANE0_MAPPING(_D2_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D2_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D2_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D2_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(!_D2_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(!_D2_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(!_D2_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(!_D2_DP_PCB_LANE3_PN_SWAP);
#endif

            // Disable Aux Digital Phy PN Swap
            ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
        }
        else // Normal Cable Mode
        {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_DP_RX1_PCB_LANE0_MAPPING(_D1_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D1_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D1_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D1_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(_D1_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(_D1_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(_D1_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(_D1_DP_PCB_LANE3_PN_SWAP);
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            SET_DP_RX1_PCB_LANE0_MAPPING(_D2_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D2_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D2_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D2_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(_D2_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(_D2_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(_D2_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(_D2_DP_PCB_LANE3_PN_SWAP);
#endif

            // Enable Aux Digital Phy PN Swap
            ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
        }
    }
}

//--------------------------------------------------
// Description  : Dp Secondary Data Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SecDataBlockReset(void)
{
    // Set S code by FW manual
    ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, _BIT7);

    // Sec Data Block Reset
    ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT4, _BIT4);
    ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT4, 0x00);

    // Set S code by HW auto
    ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, 0x00);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetBit(PBA_C4_DPCD_DATA_PORT, ~(~ucNotDpcdBit), ucDpcdBit);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetByte(PBA_C4_DPCD_DATA_PORT, ucDpcdValue);
}
//--------------------------------------------------
// Description  : DP Sink Status Setting
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync)
{
    if(enumInSync == _DP_SINK_IN_SYNC)
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 in Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) | _BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 in Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) | _BIT1));
        }
    }
    else
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 Out of Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) & ~_BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 Out of Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) & ~_BIT1));
        }
    }
}

#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP ASSR Mode On/ Off
// Input Value  : _ON/ _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ASSRModeSetting(void)
{
    if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x0A) & _BIT0) == _BIT0)
    {
        // Scramble seed equal to 0xFFFE
        ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);
    }
    else
    {
        // Scramble seed equal to 0xFFFF
        ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);
    }
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check FREESYNC Enable
// Input Value  : None
// Output Value : _TRUE: FREESYNC change
//--------------------------------------------------
bit ScalerDpRx1GetFREESYNCStatusChange(void)
{
    if((GET_FREESYNC_ENABLED() == _TRUE) && ((g_stInputTimingData.usVFreq < (_PANEL_FREESYNC_MIN_FRAME_RATE - _FRAME_SYNC_MARGIN)) || (g_stInputTimingData.usVFreq > (_PANEL_FREESYNC_MAX_FRAME_RATE + _FRAME_SYNC_MARGIN))))
    {
        DebugMessageRx1("7.FREESYNC IVF out of panel range", g_stInputTimingData.usVFreq);
        return _TRUE;
    }

    if((bit)(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x07) & _BIT7) != GET_FREESYNC_ENABLED())
    {
        DebugMessageRx1("7.FREESYNC ignore MSA 0 -> 1", 0);
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set DP Freesync Htotal info
// Input Value  : Dp Timing Info
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetFREESYNCMsaForLut(WORD usDpHtotal)
{
    WORD usTempMeasureHtotal = usDpHtotal;
    WORD usTempMsaHtotal = ((((WORD)ScalerGetByte(PB6_08_MSA_HTT_0)) << 8) | ((WORD)ScalerGetByte(PB6_09_MSA_HTT_1)));
    WORD usTempMsaHtotalMargin = ((DWORD)usTempMeasureHtotal * _DP_FREESYNC_HTOTAL_MARGIN / 100);

    if((usTempMsaHtotal > (usTempMeasureHtotal + usTempMsaHtotalMargin)) || (usTempMsaHtotal < (usTempMeasureHtotal - usTempMsaHtotalMargin)))
    {
        SET_DP_RX1_HTOTAL(usTempMeasureHtotal);

        SET_DP_RX1_HTOTAL_MARGIN(usTempMsaHtotalMargin);

        DebugMessageRx1("7. DP Freesync Get MSA Htotal Fail", usTempMsaHtotal);
    }
    else
    {
        SET_DP_RX1_HTOTAL(usTempMsaHtotal);

        SET_DP_RX1_HTOTAL_MARGIN(1);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Get Video Info
// Input Value  : None
// Output Value : TRUE --> Get successfully
//--------------------------------------------------
bit ScalerDpRx1GetVideoInfo(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    CLR_DP_RX1_VSC_SDP_COLOR_MODE();

    // Check MISC1[6]
    if((ScalerGetBit(PB6_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        SET_DP_RX1_VSC_SDP_COLOR_MODE();

#if(_HW_DP_VSC_SDP_REG_SUPPORT == _ON)

        // Read DB16~18 --> pData[0:2]
        ScalerRead(PB6_46_VSC15, 3, pData, _AUTOINC);
#else
        // Delay 2 frames for SRAM ready (worst case)
        ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX * 2);

        SET_DP_RX1_RSV1_DETECTING();

        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_RSV1_PACKET_DETECT);

        // Read DB16~18 --> pData[0:2]
        ScalerGetDataPortByte(PB6_30_DP_INFO_FM_ADR, _DP_INFO_RSV1_DB16, 3, pData, _AUTOINC);
#endif
        // Set ColorimetryExtPreValue & QuantizationPreValue & ColorDepthPreValue
        SET_DP_RX1_COLORIMETRY_EXT_PREVALUE(pData[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        SET_DP_RX1_QUANTIZATION_PREVALUE((pData[1] & _BIT7) >> 7);
        SET_DP_RX1_COLOR_DEPTH_PREVALUE(pData[1] & (_BIT2 | _BIT1 | _BIT0));
        SET_DP_RX1_COLOR_SPACE_PREVALUE(pData[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        DebugMessageRx1("VSC DB16", pData[0]);
        DebugMessageRx1("VSC DB17", pData[1]);
    }
    else
#endif
    {
        // Get MISC Info
        pData[0] = ScalerGetByte(PB6_02_MN_STRM_ATTR_MISC);

        // Set ColorimetryPreValue & QuantizationPreValue
        SET_DP_RX1_COLORIMETRY_PREVALUE((pData[0] & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
        SET_DP_RX1_QUANTIZATION_PREVALUE((pData[0] & _BIT3) >> 3);
        SET_DP_RX1_COLOR_DEPTH_PREVALUE((pData[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
        SET_DP_RX1_COLOR_SPACE_PREVALUE((ScalerGetBit(PB6_03_MN_STRM_ATTR_MISC1, _BIT7)) | (pData[0] & (_BIT2 | _BIT1)));
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetColorInfo(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    if(GET_DP_RX1_VSC_SDP_COLOR_MODE() == _TRUE)
    {
        // Use VSC SDP
        // Set Color Space Macro
        switch(GET_DP_RX1_COLOR_SPACE_PREVALUE())
        {
            case _VSC_COLOR_SPACE_0:
                SET_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;

            case _VSC_COLOR_SPACE_1:
                SET_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _VSC_COLOR_SPACE_2:
                SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _VSC_COLOR_SPACE_3:
                SET_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
                break;

            case _VSC_COLOR_SPACE_4:
                SET_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case _VSC_COLOR_SPACE_5:
                SET_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }

        // Set Colorimetry Ext
        ScalerDpRx1ColorimetryExtSetting();
    }
    else
#endif
    {
        switch(GET_DP_RX1_COLOR_SPACE_PREVALUE())
        {
            case _BIT1:
                SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _BIT2:
                SET_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _BIT7:
                SET_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case (_BIT7 | _BIT1):
                SET_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }

        // Set Colorimetry
        ScalerDpRx1ColorimetrySetting();
    }

    // Get Color Depth
    if(GET_COLOR_SPACE() != _COLOR_SPACE_RAW)
    {
        switch(GET_DP_RX1_COLOR_DEPTH_PREVALUE())
        {
            case 0:
                SET_COLOR_DEPTH(_COLOR_DEPTH_6_BITS);
                break;

            case 1:
                SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);
                break;

            case 2:
                SET_COLOR_DEPTH(_COLOR_DEPTH_10_BITS);
                break;

            case 3:
                SET_COLOR_DEPTH(_COLOR_DEPTH_12_BITS);
                break;

            case 4:
                SET_COLOR_DEPTH(_COLOR_DEPTH_16_BITS);
                break;

            default:
                SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);
                break;
        }
    }
    else
    {
        switch(GET_DP_RX1_COLOR_DEPTH_PREVALUE())
        {
            case 1:
                SET_COLOR_DEPTH(_COLOR_DEPTH_6_BITS);
                break;

            case 2:
                SET_COLOR_DEPTH(_COLOR_DEPTH_7_BITS);
                break;

            case 3:
                SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);
                break;

            case 4:
                SET_COLOR_DEPTH(_COLOR_DEPTH_10_BITS);
                break;

            case 5:
                SET_COLOR_DEPTH(_COLOR_DEPTH_12_BITS);
                break;

            case 6:
                SET_COLOR_DEPTH(_COLOR_DEPTH_14_BITS);
                break;

            case 7:
                SET_COLOR_DEPTH(_COLOR_DEPTH_16_BITS);
                break;

            default:
                SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);
                break;
        }
    }

    // Set Porch Color
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420))
    {
        if(GET_DP_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_LIMIT)
        {
            SET_DP_RX1_PORCH_COLOR_YCC_LIMIT();
        }
        else if(GET_DP_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_DP_RX1_PORCH_COLOR_YCC_FULL();
        }
    }
    else
    {
        SET_DP_RX1_PORCH_COLOR_RGB();
    }

    // Set Quantization Range
    ScalerDpRx1QuantizationSetting();
}

//--------------------------------------------------
// Description  : DP Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1VideoSetting(void)
{
    // Set Color Space for Display Format Gen.
    switch(GET_COLOR_SPACE())
    {
        case _COLOR_SPACE_RGB:
            DebugMessageRx1("_COLOR_SPACE_RGB", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_YCBCR444:
            DebugMessageRx1("_COLOR_SPACE_YCBCR444", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), _BIT4);
            break;

        case _COLOR_SPACE_YCBCR422:
            DebugMessageRx1("_COLOR_SPACE_YCBCR422", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), _BIT3);
            break;

        case _COLOR_SPACE_YCBCR420:
            DebugMessageRx1("_COLOR_SPACE_YCBCR420", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_Y_ONLY:
            DebugMessageRx1("_COLOR_SPACE_Y_ONLY", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            break;

        case _COLOR_SPACE_RAW:
            DebugMessageRx1("_COLOR_SPACE_RAW", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        default:
            // RGB
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;
    }

    // Set Color Depth for Display Format Gen.
    ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), GET_DP_RX1_COLOR_DEPTH_PREVALUE());
    DebugMessageRx1("_COLOR_DEPTH", GET_COLOR_DEPTH());
}


//--------------------------------------------------
// Description  : DP Rx1 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ColorimetrySetting(void)
{
    BYTE ucColorimetryValue = (GET_DP_RX1_COLORIMETRY_PREVALUE() << 1);

    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ucColorimetryValue & (_BIT4 | _BIT3))
        {
            case 0:
                SET_COLORIMETRY(_COLORIMETRY_YCC_XVYCC601);
                DebugMessageRx1("_COLORIMETRY_YCC_XVYCC601", 0);
                break;

            case _BIT3:
                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT601);
                DebugMessageRx1("_COLORIMETRY_YCC_ITUR_BT601", 0);
                break;

            case _BIT4:
                SET_COLORIMETRY(_COLORIMETRY_YCC_XVYCC709);
                DebugMessageRx1("_COLORIMETRY_YCC_XVYCC709", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT709);
                DebugMessageRx1("_COLORIMETRY_YCC_ITUR_BT709", 0);
                break;

            default:
                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(ucColorimetryValue & (_BIT4 | _BIT3 | _BIT2 | _BIT1))
        {
            case 0:
                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SRGB_VESA", 0);
                break;

            case _BIT3:
                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SRGB_CEA", 0);
                break;

            case (_BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_XRRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_XRRGB", 0);
                break;

            case (_BIT4 | _BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_SCRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SCRGB", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_COLORIMETRY(_COLORIMETRY_RGB_ADOBERGB);
                DebugMessageRx1("_COLORIMETRY_RGB_ADOBERGB", 0);
                break;

            case (_BIT3 | _BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_DCI_P3);
                DebugMessageRx1("_COLORIMETRY_RGB_DCI_P3", 0);
                break;

            case (_BIT4 | _BIT3 | _BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_COLOR_PROFILE);
                DebugMessageRx1("_COLORIMETRY_RGB_COLOR_PROFILE", 0);
                break;

            default:
                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SRGB", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
    {
        SET_COLORIMETRY(_COLORIMETRY_Y_ONLY);
        DebugMessageRx1("_COLORIMETRY_Y_ONLY", 0);
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        SET_COLORIMETRY(_COLORIMETRY_RAW);
        DebugMessageRx1("_COLORIMETRY_RAW", 0);
    }
}

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx1 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ColorimetryExtSetting(void)
{
    SET_COLORIMETRY(_COLORIMETRY_EXT);

    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(GET_DP_RX1_COLORIMETRY_EXT_PREVALUE())
        {
            case _VSC_COLORIMETRY_0:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT601", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT709);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT709", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_XVYCC601", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC709);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_XVYCC709", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_SYCC601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_SYCC601", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ADOBEYCC601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ADOBEYCC601", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL", 0);
                break;

            case _VSC_COLORIMETRY_7:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL", 0);
                break;

            default:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);
                DebugMessageRx1("_COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(GET_DP_RX1_COLORIMETRY_EXT_PREVALUE())
        {
            case _VSC_COLORIMETRY_0:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_SRGB", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_XRRGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_XRRGB", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SCRGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_SCRGB", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ADOBERGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_ADOBERGB", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_DCI_P3);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_DCI_P3", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ITUR_BT2020);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_ITUR_BT2020", 0);
                break;

            default:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);
                DebugMessageRx1("_COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
    {
        SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_Y_ONLY_DICOM_PART14);
        DebugMessageRx1("_COLORIMETRY_EXT_Y_ONLY_DICOM_PART14", 0);
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE);
        DebugMessageRx1("_COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE", 0);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Rx1 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1QuantizationSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        if(GET_DP_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);
            DebugMessageRx1("_YCC_QUANTIZATION_FULL_RANGE", 0);
        }
        else
        {
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);
            DebugMessageRx1("_YCC_QUANTIZATION_LIMIT_RANGE", 0);
        }

        SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);
    }
    else if(GET_COLORIMETRY() == _COLORIMETRY_RGB_ADOBERGB) // Special case for AdobeRGB
    {
        SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);
        SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);
    }
    else
    {
        if(GET_DP_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);
            DebugMessageRx1("_RGB_QUANTIZATION_FULL_RANGE", 0);
        }
        else
        {
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_LIMIT_RANGE);
            DebugMessageRx1("_RGB_QUANTIZATION_LIMIT_RANGE", 0);
        }

        SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);
    }
}

//--------------------------------------------------
// Description  : Check DP Misc Information
// Input Value  : None
// Output Value : True --> DP Misc Check Ok
//--------------------------------------------------
bit ScalerDpRx1MiscCheck(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    // Check MISC1[6]
    if((ScalerGetBit(PB6_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        return ScalerDpRx1VscCheck();
    }
    else
#endif
    {
        // Get MISC Info
        BYTE ucMisc0 = ScalerGetByte(PB6_02_MN_STRM_ATTR_MISC);
        BYTE ucColorSpaceValue = (ScalerGetBit(PB6_03_MN_STRM_ATTR_MISC1, _BIT7)) | (ucMisc0 & (_BIT2 | _BIT1));

        // Color Space Check
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)

        // Color format info source change from VSC --> MISC
        if(GET_DP_RX1_VSC_SDP_COLOR_MODE() == _TRUE)
        {
            switch(ucColorSpaceValue)
            {
                case _BIT1:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_YCBCR422", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT2:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR444)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_YCBCR444", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT7:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_Y_ONLY)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_Y_ONLY", 0);
                        return _FALSE;
                    }
                    break;

                case (_BIT7 | _BIT1):
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_RAW)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_RAW", 0);
                        return _FALSE;
                    }
                    break;

                default:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_RGB", 0);
                        return _FALSE;
                    }
                    break;
            }
        }
        else
#endif
        {
            if(ucColorSpaceValue != GET_DP_RX1_COLOR_SPACE_PREVALUE())
            {
                DebugMessageRx1("Misc change: Color Space", 0);
                return _FALSE;
            }
        }

        // Color Depth Check
        if((((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5) != GET_DP_RX1_COLOR_DEPTH_PREVALUE())
        {
            DebugMessageRx1("Misc change: Color Depth", (((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5));
            return _FALSE;
        }

        // Colorimetry Check
        if(GET_COLORIMETRY() != _COLORIMETRY_EXT)
        {
            if(((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1) != GET_DP_RX1_COLORIMETRY_PREVALUE())
            {
                DebugMessageRx1("Misc change: Colorimetry", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_RX1_COLORIMETRY_PREVALUE((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
                    ScalerDpRx1ColorimetrySetting();
                    SET_DP_RX1_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            DebugMessageRx1("Misc change: Ext Colorimetry", 0);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX1_COLORIMETRY_PREVALUE((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
                ScalerDpRx1ColorimetrySetting();
                SET_DP_RX1_COLORIMETRY_CHANGED();
            }
        }

        // Dynamic Range Check
#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
        if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422))
        {
            if(((ucMisc0 & _BIT3) >> 3) != GET_DP_RX1_QUANTIZATION_PREVALUE())
            {
                DebugMessageRx1("Misc change: Dynamic Range", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_RX1_QUANTIZATION_PREVALUE((ucMisc0 & _BIT3) >> 3);
                    ScalerDpRx1QuantizationSetting();
                    SET_DP_RX1_QUANTIZATION_CHANGED();
                }
            }
        }
        else
#endif
        {
#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
            if(((ucMisc0 & _BIT3) >> 3) != GET_DP_RX1_QUANTIZATION_PREVALUE())
            {
                DebugMessageRx1("Misc change: Dynamic Range", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_RX1_QUANTIZATION_PREVALUE((ucMisc0 & _BIT3) >> 3);
                    ScalerDpRx1QuantizationSetting();
                    SET_DP_RX1_QUANTIZATION_CHANGED();
                }
            }
#endif
        }

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() == _FALSE)
#endif
        {
            // Get HSW
            ScalerRead(PB6_0E_MSA_HSW_0, 2, &pData[0], _AUTOINC);

            // Get VSW
            ScalerRead(PB6_18_MSA_VSW_0, 2, &pData[2], _AUTOINC);

            if(((PDATA_WORD(0) & 0x7FFF) == 0x00) || ((PDATA_WORD(1) & 0x7FFF) == 0x00))
            {
                return _FALSE;
            }
        }

        return _TRUE;
    }
}

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DP VSC SDP Information
// Input Value  : None
// Output Value : True --> DP VSC SDP Check Ok
//--------------------------------------------------
bit ScalerDpRx1VscCheck(void)
{
    BYTE pucVscColorFormat[3];

    memset(pucVscColorFormat, 0, sizeof(pucVscColorFormat));

#if(_HW_DP_VSC_SDP_REG_SUPPORT == _ON)

    // Read DB16~18 --> pucVscColorFormat[0:2]
    ScalerRead(PB6_46_VSC15, 3, pucVscColorFormat, _AUTOINC);
#else
    if(GET_DP_RX1_RSV1_DETECTING() == _FALSE)
    {
        // Read DB16~18 --> pucVscColorFormat[0:2]
        ScalerGetDataPortByte(PB6_30_DP_INFO_FM_ADR, _DP_INFO_RSV1_DB16, 3, pucVscColorFormat, _AUTOINC);

        SET_DP_RX1_RSV1_DETECTING();

        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_RSV1_PACKET_DETECT);
    }
    else
    {
        return _TRUE;
    }
#endif

    // Color Space Check
    if(GET_DP_RX1_VSC_SDP_COLOR_MODE() == _FALSE)
    {
        // Color format info source change from MISC --> VSC
        switch(pucVscColorFormat[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4))
        {
            case _VSC_COLOR_SPACE_0:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_RGB", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_1:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR444)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_YCBCR444", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_2:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_YCBCR422", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_3:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR420)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_YCBCR420", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_4:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_Y_ONLY)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_Y_ONLY", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_5:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_RAW)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_RAW", 0);
                    return _FALSE;
                }

                break;

            default:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_RGB", 0);
                    return _FALSE;
                }

                break;
        }
    }
    else
    {
        if((pucVscColorFormat[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) != GET_DP_RX1_COLOR_SPACE_PREVALUE())
        {
            DebugMessageRx1("VSC change: Color Space", 0);
            return _FALSE;
        }
    }

    // Color Depth Check
    if((pucVscColorFormat[1] & (_BIT2 | _BIT1 | _BIT0)) != GET_DP_RX1_COLOR_DEPTH_PREVALUE())
    {
        DebugMessageRx1("VSC change: Color Depth", 0);
        return _FALSE;
    }

    // Colorimetry Ext Check
    if(GET_COLORIMETRY() == _COLORIMETRY_EXT)
    {
        if((pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX1_COLORIMETRY_EXT_PREVALUE())
        {
            DebugMessageRx1("VSC change: Color Depth", 0);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX1_COLORIMETRY_EXT_PREVALUE(pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerDpRx1ColorimetryExtSetting();
                SET_DP_RX1_COLORIMETRY_EXT_CHANGED();
            }
        }
    }
    else
    {
        DebugMessageRx1("VSC change: Colorimetry Ext", 0);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
        {
            return _FALSE;
        }
        else
        {
            SET_DP_RX1_COLORIMETRY_EXT_PREVALUE(pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerDpRx1ColorimetryExtSetting();
            SET_DP_RX1_COLORIMETRY_EXT_CHANGED();
        }
    }

    // Dynamic Range Check
#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420))
    {
        if(((pucVscColorFormat[1] & _BIT7) >> 7) != GET_DP_RX1_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx1("VSC change: Dynamic Range", ((pucVscColorFormat[1] & _BIT7) >> 7));

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX1_QUANTIZATION_PREVALUE((pucVscColorFormat[1] & _BIT7) >> 7);
                ScalerDpRx1QuantizationSetting();
                SET_DP_RX1_QUANTIZATION_CHANGED();
            }
        }
    }
    else
#endif
    {
#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
        if(((pucVscColorFormat[1] & _BIT7) >> 7) != GET_DP_RX1_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx1("VSC change: Dynamic Range", ((pucVscColorFormat[1] & _BIT7) >> 7));

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX1_QUANTIZATION_PREVALUE((pucVscColorFormat[1] & _BIT7) >> 7);
                ScalerDpRx1QuantizationSetting();
                SET_DP_RX1_QUANTIZATION_CHANGED();
            }
        }
#endif
    }

    return _TRUE;
}

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
//--------------------------------------------------
// Description  : DP Rx1 VSC Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1RSV1PacketDetectEvent(void)
{
    CLR_DP_RX1_RSV1_DETECTING();
}

//--------------------------------------------------
// Description  : Set DP Rx1 RSV1 infoframe type to VSC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetInitialRSV1InfoType(void)
{
    // Set Packet Type of RSV1 to VSC
    ScalerSetByte(PB6_2D_DP_INFO_FM_RSV1, _DP_SDP_TYPE_VSC);

    CLR_DP_RX1_RSV1_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_RSV1_PACKET_DETECT);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
    ScalerSetByte(PBC_54_DP_INFO_FM_RSV1, _DP_SDP_TYPE_VSC);

    CLR_DP_RX1_MST2SST_RSV1_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_MST2SST_RSV1_PACKET_DETECT);
#endif
}
#endif
#endif

//--------------------------------------------------
// Description  : Check Dp Video Straam VBID
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpRx1MSACheck(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Hactive
    ScalerRead(PB6_0C_MSA_HWD_0, 2, &pData[4], _AUTOINC);

    // Get Vactive
    ScalerRead(PB6_16_MSA_VHT_0, 2, &pData[12], _AUTOINC);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        if((PDATA_WORD(2) == 0x00) || (PDATA_WORD(6) == 0x00))
        {
            return _FALSE;
        }
    }
    else
#endif
    {
        // Get Htotal
        ScalerRead(PB6_08_MSA_HTT_0, 2, &pData[0], _AUTOINC);

        // Get Hstart
        ScalerRead(PB6_0A_MSA_HST_0, 2, &pData[2], _AUTOINC);

        // Get HSW
        ScalerRead(PB6_0E_MSA_HSW_0, 2, &pData[6], _AUTOINC);

        // Get Vtotal
        ScalerRead(PB6_10_MSA_VTTE_0, 2, &pData[8], _AUTOINC);

        // Get Vstart
        ScalerRead(PB6_14_MSA_VST_0, 2, &pData[10], _AUTOINC);

        // Get VSW
        ScalerRead(PB6_18_MSA_VSW_0, 2, &pData[14], _AUTOINC);

        if((PDATA_WORD(0) == 0x00) || (PDATA_WORD(1) == 0x00) || (PDATA_WORD(2) == 0x00) || ((PDATA_WORD(3) & 0x7FFF) == 0x00) ||
           (PDATA_WORD(4) == 0x00) || (PDATA_WORD(5) == 0x00) || (PDATA_WORD(6) == 0x00) || ((PDATA_WORD(7) & 0x7FFF) == 0x00))
        {
            if((PDATA_WORD(0) == 0x00) && (PDATA_WORD(1) == 0x00) && (PDATA_WORD(2) == 0x00) && ((PDATA_WORD(3) & 0x7FFF) == 0x00) &&
               (PDATA_WORD(4) == 0x00) && (PDATA_WORD(5) == 0x00) && (PDATA_WORD(6) == 0x00) && ((PDATA_WORD(7) & 0x7FFF) == 0x00))
            {
#if(_DP_MST_SUPPORT == _ON)
                if(GET_REG_DP_RX_MST_ENABLE() == _FALSE)
#endif
                {
                    if(ScalerDpRx1HdcpCheckValid() == _TRUE)
                    {
                        if(GET_DP_RX1_MSA_FAIL_MAC_RESET_COUNT() < 10)
                        {
                            ADD_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();
                        }
                        else
                        {
                            CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();

                            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
                            ScalerTimerDelayXms(30);
                            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

                            // Delay a Complete Frame
                            ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

                            ScalerDpRx1DecodeErrorCountReset();
                        }
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            return _FALSE;
        }

        CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();
    }

    // Get Mvid
    ScalerRead(PB6_1A_MSA_MVID_0, 3, pData, _AUTOINC);

    if((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) == 0x00)
    {
        return _FALSE;
    }

    // Get Nvid
    ScalerRead(PB6_1D_MSA_NVID_0, 3, pData, _AUTOINC);

    if((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) == 0x00)
    {
        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : PS Mode Set Fake LT Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1FakeLTProtect(void)
{
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX1_DP_LINK_TRAINING_REBUILD_PHY);

    SET_DP_RX1_FAKE_LINK_TRAINING();

    SET_DP_RX1_AUX_MANUAL_MODE();

    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY))
    {
        SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
    }

    SET_DP_RX1_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Set DP RSV0 infoframe type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetInitialRSV0InfoType(void)
{
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
    // Set Freesync Info Type to RSV0
    ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, _SPD_INFO_TYPE);
#else
#if((_DP_HDR10_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
    // Set Audio Info Type to RSV0
    ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, _DP_AUDIO_TIMESTAMP);
#endif
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    CLR_DP_RX1_RSV0_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_RSV0_PACKET_DETECT);
#endif
}

//--------------------------------------------------
// Description  : Set Dp HotPlug Event
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType)
{
    if((enumHpdType > _DP_HPD_LOW) && (ScalerSyncDpCableStatus(GET_DP_EMBEDDED_SWITCH_SELECT()) == _FALSE))
    {
        return;
    }

    // If the priority of enumHpdType is higher
    if(enumHpdType < GET_DP_RX1_HOTPLUG_ASSERT_TYPE())
    {
        SET_DP_RX1_HOTPLUG_ASSERT_TYPE(enumHpdType);
    }
}

//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HpdIrqAssert(void)
{
    if((GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT) && (PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH))
    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
        SET_DP_D1_HPD_IRQ_ASSERT_T2_EVENT();
#else

        BYTE ucBackUp2 = ScalerGetByte(PBA_D0_AUX_MODE_SET);

        SET_DP_RX1_AUX_MANUAL_MODE();

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

        // Default = 750us
        switch(GET_DP_IRQ_TIME_10US())
        {
            case 55:
                DELAY_XUS(500);
                break;

            case 60:
                DELAY_XUS(546);
                break;

            case 65:
                DELAY_XUS(588);
                break;

            case 70:
                DELAY_XUS(634);
                break;

            case 75:
                DELAY_XUS(682);
                break;

            case 80:
                DELAY_XUS(728);
                break;

            case 85:
                DELAY_XUS(768);
                break;

            case 90:
                DELAY_XUS(816);
                break;

            case 95:
                DELAY_XUS(862);
                break;

            default:
                DELAY_XUS(682);
                break;
        }

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);

        if((ucBackUp2 & _BIT1) == _BIT1)
        {
            SET_DP_RX1_AUX_AUTO_MODE();
        }
#endif

        // For Meeting Spec of HPD_IRQ Minimum Spacing >= 2 ms
        ScalerTimerDelayXms(3);
#endif
    }
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    else if((GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT) && (PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH))
    {
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
        SET_DP_D2_HPD_IRQ_ASSERT_T2_EVENT();
#else

        BYTE ucBackUp2 = ScalerGetByte(PBA_D0_AUX_MODE_SET);

        SET_DP_RX1_AUX_MANUAL_MODE();

        PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);

        // Default = 750us
        switch(GET_DP_IRQ_TIME_10US())
        {
            case 55:
                DELAY_XUS(500);
                break;

            case 60:
                DELAY_XUS(546);
                break;

            case 65:
                DELAY_XUS(588);
                break;

            case 70:
                DELAY_XUS(634);
                break;

            case 75:
                DELAY_XUS(682);
                break;

            case 80:
                DELAY_XUS(728);
                break;

            case 85:
                DELAY_XUS(768);
                break;

            case 90:
                DELAY_XUS(816);
                break;

            case 95:
                DELAY_XUS(862);
                break;

            default:
                DELAY_XUS(682);
                break;
        }

        PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);

        if((ucBackUp2 & _BIT1) == _BIT1)
        {
            SET_DP_RX1_AUX_AUTO_MODE();
        }
#endif

        // For Meeting Spec of HPD_IRQ Minimum Spacing >= 2 ms
        ScalerTimerDelayXms(3);
    }
#endif
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HpdIrqAssert_EXINT0(void) using 1
{
    if((GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT) && (PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH))
    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
        SET_DP_D1_HPD_IRQ_ASSERT_T2_EVENT();
#else

        BYTE ucBackUp2 = ScalerGetByte_EXINT(PBA_D0_AUX_MODE_SET);

        SET_DP_RX1_AUX_MANUAL_MODE_EXINT();

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

        // Default = 750us
        switch(GET_DP_IRQ_TIME_10US())
        {
            case 55:
                DELAY_XUS_EXINT(500);
                break;

            case 60:
                DELAY_XUS_EXINT(546);
                break;

            case 65:
                DELAY_XUS_EXINT(588);
                break;

            case 70:
                DELAY_XUS_EXINT(634);
                break;

            case 75:
                DELAY_XUS_EXINT(682);
                break;

            case 80:
                DELAY_XUS_EXINT(728);
                break;

            case 85:
                DELAY_XUS_EXINT(768);
                break;

            case 90:
                DELAY_XUS_EXINT(816);
                break;

            case 95:
                DELAY_XUS_EXINT(862);
                break;

            default:
                DELAY_XUS_EXINT(682);
                break;
        }

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);

        if((ucBackUp2 & _BIT1) == _BIT1)
        {
            SET_DP_RX1_AUX_AUTO_MODE_EXINT();
        }
#endif
#endif
    }
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    else if((GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT) && (PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH))
    {
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
        SET_DP_D2_HPD_IRQ_ASSERT_T2_EVENT();
#else

        BYTE ucBackUp2 = ScalerGetByte_EXINT(PBA_D0_AUX_MODE_SET);

        SET_DP_RX1_AUX_MANUAL_MODE_EXINT();

        PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);

        // Default = 750us
        switch(GET_DP_IRQ_TIME_10US())
        {
            case 55:
                DELAY_XUS_EXINT(500);
                break;

            case 60:
                DELAY_XUS_EXINT(546);
                break;

            case 65:
                DELAY_XUS_EXINT(588);
                break;

            case 70:
                DELAY_XUS_EXINT(634);
                break;

            case 75:
                DELAY_XUS_EXINT(682);
                break;

            case 80:
                DELAY_XUS_EXINT(728);
                break;

            case 85:
                DELAY_XUS_EXINT(768);
                break;

            case 90:
                DELAY_XUS_EXINT(816);
                break;

            case 95:
                DELAY_XUS_EXINT(862);
                break;

            default:
                DELAY_XUS_EXINT(682);
                break;
        }

        PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);

        if((ucBackUp2 & _BIT1) == _BIT1)
        {
            SET_DP_RX1_AUX_AUTO_MODE_EXINT();
        }
#endif
    }
#endif
}
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_ULTRA_HDR_SUPPORT == _ON))
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpRx1GetInfoFrameRSV0(BYTE *pucDPRx1RSV0Data)
{
    BYTE ucTemp = 0;
    BYTE ucDebounceCnt = 5;

    BYTE pucTmepData1[_HW_DP_INFOFRAME_RSV0_LENGTH];
    BYTE pucTmepData2[_HW_DP_INFOFRAME_RSV0_LENGTH];

    do
    {
        ScalerSetByte(PB6_30_DP_INFO_FM_ADR, (_DP_INFO_RSV0_DB0 + ucTemp));
        pucTmepData1[ucTemp] = ScalerGetByte(PB6_31_DP_INFO_FM_DAT);

        ucTemp ++;
    }
    while(ucTemp < _HW_DP_INFOFRAME_RSV0_LENGTH);

    do
    {
        ucTemp = 0;

        do
        {
            ScalerSetByte(PB6_30_DP_INFO_FM_ADR, (_DP_INFO_RSV0_DB0 + ucTemp));
            pucTmepData2[ucTemp] = ScalerGetByte(PB6_31_DP_INFO_FM_DAT);

            ucTemp ++;
        }
        while(ucTemp < _HW_DP_INFOFRAME_RSV0_LENGTH);

        if(memcmp(pucTmepData1, pucTmepData2, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
        {
            break;
        }
        else
        {
            memcpy(pucTmepData1, pucTmepData2, _HW_DP_INFOFRAME_RSV0_LENGTH);
        }

        ucDebounceCnt --;
    }
    while(ucDebounceCnt > 0);

    memcpy(pucDPRx1RSV0Data, pucTmepData2, _HW_DP_INFOFRAME_RSV0_LENGTH);
}
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP InfoFrame RSV0 Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1InfoFrameRSV0Check(void)
{
    BYTE pucDPRx1RSV0Data[_HW_DP_INFOFRAME_RSV0_LENGTH];
    BYTE ucInfoFrameType = 0;

    memset(pucDPRx1RSV0Data, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
    ScalerDpRx1GetInfoFrameRSV0(pucDPRx1RSV0Data);

#if(_DP_HDR10_SUPPORT == _ON)
    ucInfoFrameType = ScalerGetByte(PB6_2C_DP_INFO_FM_RSV0);

    if(ucInfoFrameType == _HDR_INFO_TYPE)
    {
        switch(g_ucDPRx1InfoTypeCompare)
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
            case _SPD_INFO_TYPE:

                if(GET_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED() == _TRUE)
                {
                    if(memcmp(pucDPRx1RSV0Data, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                    {
                        if(memcmp(g_pucDPRx1RSV0Backup, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                        {
                            CLR_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                            memset(g_pucDPRx1HDR10Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                        }
                        else
                        {
                            // Do nothing: confuse case, keep last time status
                        }
                    }
                    else
                    {
                        SET_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                        memcpy(g_pucDPRx1HDR10Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                }
                else
                {
                    SET_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx1HDR10Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;
#endif

            case _DP_AUDIO_TIMESTAMP:

                if(GET_DP_RX1_AUDIO_INFO_FRAME_RECEIVED() == _TRUE)
                {
                    // Maud:[0:15], Naud:[16:31] is constant, Check Naud (arrary[16:27])
                    if(memcmp(&pucDPRx1RSV0Data[16], &g_pucDPRx1InfoTemp[16], 12) == 0)
                    {
                        if(memcmp(g_pucDPRx1RSV0Backup, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                        {
                            CLR_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                            memset(g_pucDPRx1HDR10Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                        }
                        else
                        {
                            // Do nothing: confuse case, keep last time status
                        }
                    }
                    else
                    {
                        SET_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                        memcpy(g_pucDPRx1HDR10Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                }
                else
                {
                    SET_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx1HDR10Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;

            default:
                break;
        }
    }
    else
    {
        switch(g_ucDPRx1InfoTypeCompare)
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
            case _SPD_INFO_TYPE:

                if(memcmp(pucDPRx1RSV0Data, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                {
                    if(memcmp(g_pucDPRx1HDR10Backup, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                    {
                        CLR_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED();
                        memset(g_pucDPRx1RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                    else
                    {
                        // Do nothing: confuse case, keep last time status
                    }
                }
                else
                {
                    SET_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx1RSV0Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;
#endif

            case _DP_AUDIO_TIMESTAMP:

                if(memcmp(pucDPRx1RSV0Data, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                {
                    if(memcmp(g_pucDPRx1HDR10Backup, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                    {
                        CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
                        memset(g_pucDPRx1RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                    else
                    {
                        // Do nothing: confuse case, keep last time status
                    }
                }
                else
                {
                    SET_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx1RSV0Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;

            default:
                break;
        }
    }

    ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, ScalerDpRx1SelectInfoFrameType(ucInfoFrameType));

    // Get infoframe after switch infoframe header for check
    ScalerDpRx1GetInfoFrameRSV0(g_pucDPRx1InfoTemp);
#else
    ucInfoFrameType = ucInfoFrameType;
#endif
}

//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1RSV0PacketDetectEvent(void)
{
    CLR_DP_RX1_RSV0_DETECTING();
}

//--------------------------------------------------
// Description  : DP InfoFrame RSV0 initial setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1InfoFrameRSV0Initial(void)
{
#if(_DP_HDR10_SUPPORT == _ON)
    CLR_DP_RX1_HDR_INFO_FRAME_RECEIVED();

    // Get RSV0 Infoframe
    ScalerDpRx1GetInfoFrameRSV0(g_pucDPRx1RSV0Backup);

    // Get Compare with HDR infoframe type
    g_ucDPRx1InfoTypeCompare = ScalerGetByte(PB6_2C_DP_INFO_FM_RSV0);

    // Set DP RSV0 info type: HDR
    ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, _HDR_INFO_TYPE);

    // Get infoframe after switch infoframe header for check
    ScalerDpRx1GetInfoFrameRSV0(g_pucDPRx1InfoTemp);
#endif
}
#endif // End of #if(_DP_ULTRA_HDR_SUPPORT == _ON)

#if(_DP_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Select InfoFrame Type
// Input Value  : None
// Output Value : InfoFrame Type
//--------------------------------------------------
BYTE ScalerDpRx1SelectInfoFrameType(BYTE ucInfoFrameTypeCurrent)
{
    BYTE ucInfoFrameTypeNext = 0;

    if(ucInfoFrameTypeCurrent == _HDR_INFO_TYPE)
    {
        ucInfoFrameTypeNext = g_ucDPRx1InfoTypeCompare;
    }
    else
    {
        ucInfoFrameTypeNext = _HDR_INFO_TYPE;
    }

    return ucInfoFrameTypeNext;
}

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch DP HDR10 comapre info type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SwitchHDR10CmpAudioInfo(void)
{
    BYTE pucRSV0Data1[_HW_DP_INFOFRAME_RSV0_LENGTH];
    BYTE pucRSV0Data2[_HW_DP_INFOFRAME_RSV0_LENGTH];

    memset(pucRSV0Data1, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
    memset(pucRSV0Data2, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED() == _TRUE)
    {
        CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
    }
    else
#endif
    {
        // Set Audio Info Type to RSV0
        ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, _DP_AUDIO_TIMESTAMP);

        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        ScalerDpRx1GetInfoFrameRSV0(pucRSV0Data1);

        // check pucRSV0Data1 not all 0
        if(memcmp(pucRSV0Data1, pucRSV0Data2, _HW_DP_INFOFRAME_RSV0_LENGTH) != 0)
        {
            // Get MSA Naud
            pucRSV0Data2[16] = ScalerGetByte(PB6_23_MSA_NAUD_0);
            pucRSV0Data2[17] = ScalerGetByte(PB6_24_MSA_NAUD_1);
            pucRSV0Data2[18] = ScalerGetByte(PB6_25_MSA_NAUD_2);
            pucRSV0Data2[19] = 0x00;

            // Check Audio time stamp info
            if((memcmp(&pucRSV0Data1[16], &pucRSV0Data2[16], 4) == 0) &&
               (memcmp(&pucRSV0Data1[16], &pucRSV0Data1[20], 4) == 0) &&
               (memcmp(&pucRSV0Data1[16], &pucRSV0Data1[24], 4) == 0))
            {
                SET_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
                memcpy(g_pucDPRx1RSV0Backup, pucRSV0Data1, _HW_DP_INFOFRAME_RSV0_LENGTH);
            }
            else
            {
                CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
                memset(g_pucDPRx1RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
            }
        }
        else
        {
            CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
            memset(g_pucDPRx1RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
        }

        // Get Compare with HDR infoframe type
        g_ucDPRx1InfoTypeCompare = ScalerGetByte(PB6_2C_DP_INFO_FM_RSV0);

        // Set DP RSV0 info type: HDR
        ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, _HDR_INFO_TYPE);

        // Get infoframe after switch infoframe header for check
        ScalerDpRx1GetInfoFrameRSV0(g_pucDPRx1InfoTemp);
    }
}
#endif

#endif // End of #if(_DP_HDR10_SUPPORT == _ON)

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DPCD HDCP capability
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpRx1CheckHdcpCapability(void)
{
    if(ScalerDpRx1GetDpcdBitInfo(0x06, 0x80, 0x28, _BIT0) == _BIT0)
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        if(ScalerDpRx1GetDpcdBitInfo(0x06, 0x92, 0x1F, _BIT1) == _BIT1)
#endif
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Enable HDCP Hanshake Monitoring Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HdcpHandshakeMonitorEnable(void)
{
    // Clear Read DPCD 68028h INT Flag
    ScalerSetBit(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);

    // Enable Read DPCD 68028h INT
    ScalerSetBit(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT6);

    // Clear HDCP AKSV IRQ
    ScalerSetBit(PBA_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // Enable HDCP AKSV IRQ
    ScalerSetBit(PBA_A5_AUX_RESERVE5, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT6);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Clear Read DPCD 6921Xh INT Flag
    ScalerSetBit(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT3);

    // Enable Read DPCD 6921Xh INT
    ScalerSetBit(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT2);
#endif
}

//--------------------------------------------------
// Description  : Disable HDCP Hanshake Monitoring Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HdcpHandshakeMonitorDisable(void)
{
    // Disable Read DPCD 68028h INT
    ScalerSetBit(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), 0x00);

    // Disable HDCP AKSV IRQ
    ScalerSetBit(PBA_A5_AUX_RESERVE5, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Disable Read DPCD 6921Xh INT
    ScalerSetBit(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), 0x00);
#endif
}

//--------------------------------------------------
// Description  : Disable HDCP Hanshake Monitoring Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HdcpHandshakeMonitorDisable_EXINT0(void) using 1
{
    // Disable Read DPCD 68028h INT
    ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), 0x00);

    // Disable HDCP AKSV IRQ
    ScalerSetBit_EXINT(PBA_A5_AUX_RESERVE5, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Disable Read DPCD 6921Xh INT
    ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), 0x00);
#endif
}
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Backup Timing Info for Modern Standby
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1TimingInfoBackup(void)
{
    // Backup Offset Value of Stream Clock
    g_stDpRx1LinkInfo.lStreamClockOffset = ((((SDWORD)ScalerGetBit(PB5_BA_MN_SCLKG_SDM_SUMC_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << 16) |
                                            (((WORD)ScalerGetByte(PB5_BB_MN_SCLKG_SDM_SUMC_M)) << 8) |
                                            (ScalerGetByte(PB5_BC_MN_SCLKG_SDM_SUMC_L))) >> 1;

    // Backup VBs2Bs Delay of Even Field
    g_stDpRx1LinkInfo.ulVBsToBsDelayEven = (((DWORD)ScalerGetBit(PB5_32_EVBLK2VS_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << 16) |
                                           (((WORD)ScalerGetByte(PB5_33_EVBLK2VS_M)) << 8) |
                                           (ScalerGetByte(PB5_34_EVBLK2VS_L));

    // Backup VBs2Bs Delay of Odd Field
    g_stDpRx1LinkInfo.ulVBsToBsDelayOdd = (((DWORD)ScalerGetBit(PB5_35_OVBLK2VS_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << 16) |
                                          (((WORD)ScalerGetByte(PB5_36_OVBLK2VS_M)) << 8) |
                                          (ScalerGetByte(PB5_37_OVBLK2VS_L));
}
#endif

//--------------------------------------------------
// Description  : Read DP Rx Error Count
// Input Value  : DP Input Port
// Output Value : DP 4 Lane Error Count & Valid Flag
//--------------------------------------------------
StructDpRxErrorCount ScalerDpRx1GetErrorCount(void)
{
    StructDpRxErrorCount stDpRxErrorCount;

    if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE) ||
       (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE))
    {
        DebugMessageSystem("Rx Fail to Report Valid Error Counter", 0x00);

        switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            case _DP_TWO_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            default:
            case _DP_FOUR_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0x7FFF;

                break;
        }
    }
    else
    {
        switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            case _DP_TWO_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE1);
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            default:
            case _DP_FOUR_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE1);
                stDpRxErrorCount.usDpRxLane2ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE2);
                stDpRxErrorCount.usDpRxLane3ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE3);

                break;
        }
    }

    // Reset Error Counter
    ScalerDpRx1DecodeErrorCountReset();

    return stDpRxErrorCount;
}

//--------------------------------------------------
// Description  : Get 8b10b Error Count value
// Input Value  : Lane
// Output Value : Error Count
//--------------------------------------------------
WORD ScalerDpRx1GetDecodeErrorCount(BYTE ucDpRx1LaneNumber)
{
    // Select Lane
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (ucDpRx1LaneNumber << 3));

    return ((((WORD)ScalerGetByte(PB_0B_BIST_PATTERN3)) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));
}
#endif // End of #if(_D1_DP_EXIST == _ON)
