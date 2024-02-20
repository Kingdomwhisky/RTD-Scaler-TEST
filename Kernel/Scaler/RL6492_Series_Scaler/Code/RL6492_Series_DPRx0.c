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
// ID Code      : RL6492_Series_DPRx0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_DPRX0__

#include "ScalerFunctionInclude.h"

#if(_D0_DP_EXIST == _ON)

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
bit g_bDpRx0PSAuxToggle = _FALSE;

bit g_bDpRx0AuxCommandNoReply = _FALSE;

BYTE g_ucDpRx0LinkStatus01;
BYTE g_ucDpRx0LinkStatus23;
BYTE g_ucDpRx0LinkRequest01;
BYTE g_ucDpRx0LinkRequest23;
BYTE g_ucDpRx0Temp;
BYTE g_pucDpRx0Backup[3];
BYTE g_ucDpRx0Info;
BYTE g_ucDpRx0LinkRate;
BYTE g_ucDpRx0LaneCount;
BYTE g_ucDpRx0TrainingPatternSet;

BYTE g_pucDpRx0Tap1MinTemp[4];
BYTE g_pucDpRx0LEMinTemp[4];
BYTE g_ucDpRx0EQCRC;
WORD g_pusDpRx0ClockCount[4];
WORD g_pusDpRx0ClockCount1[4];

WORD g_usDpRx0D10p2CountCriteriaUpperBoundRBR;
WORD g_usDpRx0D10p2CountCriteriaUpperBoundHBR;
WORD g_usDpRx0D10p2CountCriteriaUpperBoundHBR2;
WORD g_usDpRx0D10p2CountCriteriaLowerBoundRBR;
WORD g_usDpRx0D10p2CountCriteriaLowerBoundHBR;
WORD g_usDpRx0D10p2CountCriteriaLowerBoundHBR2;

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
bit g_bDpRx0SourceTypeJudge = _FALSE;
#endif

BYTE g_ucRx0AuxTemp;
BYTE g_ucRx0AuxTemp_EXINT;
WORD g_usDpRx0Vfrontporch;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
BYTE g_ucDpRx0FakeLTLaneCount;
BYTE g_ucDpRx0FakeLTLaneCountBackUp;
#endif

BYTE g_ucDpRx0PhyCtsCtrl;
EnumHDCPType g_enumDpRx0HdcpMode;
StructDpLanesMapping g_stDpRx0LanesMapping;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
BYTE g_pucDPRx0Caps[3];
#endif

#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
bit g_bDpRx0AltModeHpd = _LOW;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpRx0AuxPowerOnInitial(void);
void ScalerDpRx0AuxIntInitial(void);
void ScalerDpRx0DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
void ScalerDpRx0ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
EnumDpHotPlugTime ScalerDpRx0BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType);
void ScalerDpRx0AfterHpdToggleProc(void);
void ScalerDpRx0HpdIrqAssert(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
void ScalerDpRx0HpdIrqAssert_EXINT0(void);
void ScalerDpRx0CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType);
#endif
void ScalerDpRx0MacInitial(void);
void ScalerDpRx0PhyInitial(void);
void ScalerDpRx0RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
void ScalerDpRx0Rebuild4LanePhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
void ScalerDpRx0RebuildUnFlip2LanePhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
void ScalerDpRx0RebuildFlip2LanePhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
#endif

void ScalerDpRx0AdjustLaneFLDBand(BYTE ucDpRx0LaneNumber);
void ScalerDpRx0SetDFEInitial(EnumDpLinkRate enumDpLinkRate);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
void ScalerDpRx0SetDFEInitialUnFlip2Lane(EnumDpLinkRate enumDpLinkRate);
void ScalerDpRx0SetDFEInitialFlip2Lane(EnumDpLinkRate enumDpLinkRate);
#endif

bit ScalerDpRx0CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
bit ScalerDpRx0MeasureLaneCDRClk(BYTE ucDpLinkRate, BYTE ucDpRx0LaneNumber);
bit ScalerDpRx0AlignCheck(void);
bit ScalerDpRx0DecodeCheck(void);
bit ScalerDpRx0DFECheck(void);
void ScalerDpRx0SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue);
bit ScalerDpRx0DisplayFormatSetting(void);
bit ScalerDpRx0StreamClkRegenerate(void);
bit ScalerDpRx0FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
void ScalerDpRx0HDCPBlockReset(void);
bit ScalerDpRx0HdcpCheck(void);
bit ScalerDpRx0HdcpReAuthStatusCheck(void);
bit ScalerDpRx0HdcpMeasureCheck(void);
void ScalerDpRx0CpIRQ(EnumDpRxBStatusType enumBStatusType);
bit ScalerDpRx0HdcpCheckValid(void);
bit ScalerDpRx0HdcpCheckEnabled(void);
void ScalerDpRx0PhyCtsTp1SetPhy(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx0PhyCtsTp1SetPhy4Lane(EnumDpNFCodeRef enumDpNFCodeRef);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
void ScalerDpRx0PhyCtsTp1SetPhyUnFlip2Lane(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx0PhyCtsTp1SetPhyFlip2Lane(EnumDpNFCodeRef enumDpNFCodeRef);
#endif

void ScalerDpRx0PhyCtsTp2SetPhy(void);
void ScalerDpRx0PhyCtsTp2SetPhy4Lane(void);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
void ScalerDpRx0PhyCtsTp2SetPhyUnFlip2Lane(void);
void ScalerDpRx0PhyCtsTp2SetPhyFlip2Lane(void);
#endif

bit ScalerDpRx0PhyCtsTp1Check(void);
bit ScalerDpRx0PhyCtsTp2Check(void);
void ScalerDpRx0PhyCTS(void);
void ScalerDpRx0SetFifoWD(bit bEn);
void ScalerDpRx0SetFifoIRQ(bit bEn);
bit ScalerDpRx0NormalPreDetect(void);
bit ScalerDpRx0ChangeSrambleSeed(void);
#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)
bit ScalerDpRx0VbiosAssrCheck(bit bMSACheckResult);
#endif
BYTE ScalerDpRx0ScanInputPort(void);
bit ScalerDpRx0StableDetect(void);
void ScalerDpRx0SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType);

void ScalerDpRx0AdjustVsyncDelay(void);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
bit ScalerDpRx0CheckVgipVsBypass(void);
#endif

void ScalerDpRx0SetNoVideoStreamIRQ(bit bEn);
void ScalerDpRx0DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);
DWORD ScalerDpRx0GetBStoVSDelay(void);
void ScalerDpRx0Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
bit ScalerDpRx0MarginLinkCheck(void);
void ScalerDpRx0LinkStatusIRQ(void);
void ScalerDpRx0AuxSet(void);
#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
bit ScalerDpRx0DecodeErrorCountCheck(WORD usTimeCriteria, BYTE ucErrorCriteria);
bit ScalerDpRx0DecodeErrorCountLaneMeasure(BYTE ucErrorCriteria, BYTE ucDpRx0LaneNumber);
bit ScalerDpRx0LaneBsCheck(void);
#endif

bit ScalerDpRx0PSPreDetect(void);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
void ScalerDpRx0SetDpAltModeLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation);
#else
void ScalerDpRx0SetDpLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation);
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
bit ScalerDpRx0CheckHdcpCapability(void);
void ScalerDpRx0HdcpHandshakeMonitorEnable(void);
void ScalerDpRx0HdcpHandshakeMonitorDisable(void);
void ScalerDpRx0HdcpHandshakeMonitorDisable_EXINT0(void);
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
void ScalerDpRx0TimingInfoBackup(void);
#endif
StructDpRxErrorCount ScalerDpRx0GetErrorCount(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial Setting for DP Digital Aux, Analog Aux
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AuxPowerOnInitial(void)
{
    // Digital Aux Power On, DPCD REG Power On, MSG Power On.
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT1 | _BIT0), 0x00);

    // Average 8 cycles as Start Postion, Aux Clk Select to 27MHz, no Swap
    ScalerSetByte(PB7_72_AUX_DIG_PHY2, 0xC0);

#if(_ERROR_PRONE_CODE == _TRUE)
    // Disable Aux APHY Swap
    ScalerSetBit(PB7_66_AUX_6, ~_BIT7, 0x00);
#endif

#if(_DP_AUX_REPLY_CLK_SEL_FROM == _DP_AUX_REPLY_SEL_IOSC)
    // Aux Clk Select Manual Mode, Aux New Mode
    ScalerSetBit(PB7_73_AUX_DIG_PHY3, ~(_BIT7 | _BIT6), _BIT6);
#else
    // Aux Clk Select Source, Aux New Mode
    ScalerSetBit(PB7_73_AUX_DIG_PHY3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif

    // HW Fake Link Training Disable.
    ScalerSetBit(PB7_C6_AUX_PHY_DIG2, ~_BIT4, 0x00);

    // Set Aux Precharge Number.
    ScalerSetBit(PB7_74_AUX_DIG_PHY4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

    // Aux Auto Mode, Using Default Average Number.
    ScalerSetByte(PB7_75_AUX_DIG_PHY5, 0x0D);

#if(_DP_AUX_REPLY_TIMEOUT_BY_USER == _ON)
    // Aux Reply Timeout Setting
    ScalerSetByte(PB7_A2_AUX_RESERVE2, _DP_AUX_REPLY_TIMEOUT_USER_SETTING);
#endif

    // Enble Aux Channel.
    ScalerSetBit(PB7_D0_AUX_MODE_SET, ~(_BIT3 | _BIT2 | _BIT0), _BIT0);

    // Fast IIC Clock.
    ScalerSetByte(PB7_D1_DP_IIC_SET, 0x02);

    // Set aux mac clk use xclk
    ScalerSetBit(PB7_DA_AUX_FIFO_RST, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), _BIT3);

    // Not Reply when Aux Error.
    ScalerSetBit(PB7_DB_AUX_STATUS, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetBit(PB7_76_AUX_DIG_PHY6, ~(_BIT7 | _BIT6), _BIT6);

    // Aux Ack Timer.
    ScalerSetBit(PB7_F0_AUX_TX_TIMER, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));

    // Set Timeout Target
    ScalerSetBit(PB7_F1_AUX_TX_TIMER_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));

    // Disable Reply IIC Defer Before Data Ready.
    ScalerSetBit(PB7_F4_MCUIIC, ~(_BIT6 | _BIT5), 0x00);

    // Enable Aux Error Handler.
    ScalerSetBit(PB7_78_AUX_DIG_PHY8, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // Toggle Aux Auto K
    ScalerSetBit(PB7_65_AUX_5, ~_BIT7, 0x00);
    ScalerSetBit(PB7_65_AUX_5, ~_BIT7, _BIT7);

    // Aux Mode Set (Diff Mode or Single-ended mode) && Aux RX0 Resistance Setting
    ScalerDpRx0AuxSet();

    // Set Aux Talk Mode ADJR
    ScalerSetByte(PB7_67_DIG_TX_03, 0xFF);

    ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT1 | _BIT0), _BIT0);

    // Aux comm current select max
    ScalerSetBit(PB7_64_AUX_4, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Set Aux D_2 = ~D_1 for Aux Single Ended Mode
    ScalerSetBit(PB7_79_AUX_DIG_PHY9, ~_BIT7, _BIT7);

    // Clear the Clock Divider for AUX MAC and PHY
    ScalerSetBit(PB7_73_AUX_DIG_PHY3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB7_B0_AUX_PAYLOAD_CLEAR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Aux ps clk from IOSC
    ScalerSetBit(P0_0B_POWER_CTRL, ~(_BIT5 | _BIT4), 0x00);

    // Set the Clock Divider = 1 for AUX MAC and PHY
    ScalerSetBit(PB7_73_AUX_DIG_PHY3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB7_B0_AUX_PAYLOAD_CLEAR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
}

//--------------------------------------------------
// Description  : Initial Setting for DP Aux INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AuxIntInitial(void)
{
    // Enable 068xxx INT
    ScalerSetBit(PB7_DA_AUX_FIFO_RST, ~(_BIT4 | _BIT1 | _BIT0), _BIT1);
    ScalerSetBit(PB7_DA_AUX_FIFO_RST, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT2);

    // Disable other DPCD, Aux Timeout, Receiving Aux INT.
    ScalerSetBit(PB7_DC_AUX_IRQ_STATUS, ~(_BIT5 | _BIT3 | _BIT2), 0x00);

    // Disable Aux Phy Int
    ScalerSetBit(PB7_77_AUX_DIG_PHY7, ~_BIT7, 0x00);

    // Enable DPCD INT
    ScalerSetByte(PB7_DE_AUX_DPCD_IRQ_EN, 0xE5);

    // Internal IRQ Enable (Global)
    ScalerGlobalIRQControl(_ENABLE);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Clear HDCP2.2 Handshaked Related IRQ
    ScalerSetBit(PB7_A4_AUX_RESERVE4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));
    ScalerSetBit(PB7_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable HDCP2.2 Handshaked Related IRQ
    ScalerSetBit(PB7_A3_AUX_RESERVE3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));
    ScalerSetBit(PB7_A5_AUX_RESERVE5, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // Source Read 692DFh(HPrime) INT
    ScalerSetByte(PB7_B7_AUX_IRQ_ADDR1_MSB, 0x06);
    ScalerSetByte(PB7_B8_AUX_IRQ_ADDR1_MSB1, 0x92);
    ScalerSetByte(PB7_B9_AUX_IRQ_ADDR1_LSB, 0xDF);
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    // INT Wildcard 0 set for Source Read 68028h
    ScalerSetByte(PB7_B4_AUX_IRQ_ADDR0_MSB, 0x06);
    ScalerSetByte(PB7_B5_AUX_IRQ_ADDR0_MSB1, 0x80);
    ScalerSetByte(PB7_B6_AUX_IRQ_ADDR0_LSB, 0x28);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // INT Wildcard 2 set for Source Read 6921Xh
    ScalerSetByte(PB7_BA_AUX_IRQ_ADDR2_MSB, 0x16);
    ScalerSetByte(PB7_BB_AUX_IRQ_ADDR2_MSB1, 0x92);
    ScalerSetByte(PB7_BC_AUX_IRQ_ADDR2_LSB, 0x10);
#endif

    ScalerDpRx0HdcpHandshakeMonitorEnable();

#else
    // Enable Rx0 DPCD table controlled by DP HDCP circuit
    SET_REG_DP_RX0_DPCD_CTRL_BY_HDCP();
#endif

    // Disable Wildcard IRQ for Error Counter
    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), 0x00);

    // Use Wildcard 3 to DPCD 0x0021xh, LSB 4 Bits Discarded
    ScalerSetByte(PB7_BD_AUX_IRQ_ADDR3_MSB, 0x10);
    ScalerSetByte(PB7_BE_AUX_IRQ_ADDR3_MSB1, 0x02);
    ScalerSetByte(PB7_BF_AUX_IRQ_ADDR3_LSB, 0x10);

    // Enable INT0
    EX0 = 1;
}

//--------------------------------------------------
// Description  : DPCD Table Initial
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport)
{
    enumFreeSyncSupport = enumFreeSyncSupport;

    ScalerDpRx0SinkStatusSet(_DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);
    ScalerDpRx0SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);

    ScalerDpRx0ChangeDpcdVersion(enumDpVersion, enumDpRxMstPort);

    // Enhanced Framing Support(Bit7) and DP Lane Count(Bit[4:0])
    pData[0] = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x02);
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x02, ((pData[0] & ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) | _BIT7 | enumDpLaneCount));

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
    g_ucDpRx0FakeLTLaneCount = (enumDpLaneCount & 0x1F);
    g_ucDpRx0FakeLTLaneCountBackUp = (enumDpLaneCount & 0x1F);
#endif

    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x03, 0x01);

#if(_AUDIO_SUPPORT == _ON)
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x04, 0x01);
#else
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x04, 0x00);
#endif

    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x06, 0x01);
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x08, 0x02);

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _OFF)
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x09, 0x00);
#endif

#if(_AUDIO_SUPPORT == _ON)
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x0A, 0x06);
#else
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x0A, 0x00);
#endif

    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x0B, 0x00);

#if(_D0_DP_ASSR_MODE_SUPPORT == _ON)
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x0D, 0x01);

    SET_DP_RX0_AUX_MANUAL_MODE();
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
    SET_DP_RX0_AUX_AUTO_MODE();
#endif

    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x21, 0x00);

    // DPCD Link Status Field Setting
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x00, 0x41);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x01, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x05, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x08, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x09, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x0A, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x0B, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x46, 0x20);

    // Initialize Reserved to 0
    ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x10, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x12, 0x00);

#if(_DP_FREESYNC_SUPPORT == _ON)

    SET_DP_RX0_FREESYNC_SUPPORT(enumFreeSyncSupport);

    if(GET_DP_RX0_FREESYNC_SUPPORT() == _FREESYNC_SUPPORT_ON)
    {
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);
    }
#endif

    // Initialize HDCP2.2 DPCD (69XXXh) to 0s for avoiding SRAM initial state values remained
    SET_DP_RX0_AUX_MANUAL_MODE();

    for(PDATA_WORD(0) = 0x9000; PDATA_WORD(0) <= 0x94BF; PDATA_WORD(0)++)
    {
        ScalerDpRx0SetDpcdValue(0x06, pData[0], pData[1], 0x00);
    }

    SET_DP_RX0_AUX_AUTO_MODE();

#if(_DP_HDCP_2_2_SUPPORT == _ON)

    // Load Certrx to DPCD Table
    ScalerDpRx0Hdcp2LoadCertRrxKey();
#endif

    // Down Stream Port isn't HPD Aware
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x80, 0x00);

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    // Disable HDCP at first
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x00);
#else
    // _BIT1: Repeater,  _BIT0: HDCP Capable
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x01);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)

    // Set HDCP_Capable and Repeater Bit
    g_pucDPRx0Caps[0] = 0x02;
    g_pucDPRx0Caps[1] = 0x00;
    g_pucDPRx0Caps[2] = 0x02;

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    // Disable HDCP at first
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), 0x00);
    }
#else
    // Load RxCaps to DPCD Table
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), g_pucDPRx0Caps[pData[0]]);
    }
#endif
#endif

    // Align 0220Xh & 0000Xh
    for(pData[0] = 0x02; pData[0] <= 0x0F; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x00, 0x22, pData[0], ScalerDpRx0GetDpcdInfo(0x00, 0x00, pData[0]));
    }
}

//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort)
{
    enumDpRxMstPort = _DP_MST_NO_PORT;

    if(enumDpVersion >= _DP_VERSION_1_4)
    {
        // DPCD Version
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_2);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x00, enumDpVersion);
#else
        g_ucDpRx0DPCD02200hValue = enumDpVersion;
#endif

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x0E, ~_BIT7, _BIT7);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x10, 0x08);
#else
        g_ucDpRx0DPCD02210hValue = 0x08;
#endif

#else

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x10, 0x00);
#else
        g_ucDpRx0DPCD02210hValue = 0x00;
#endif

#endif

        if(_D0_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
        }
        else
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
        }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D0_DP_LINK_CLK_RATE);
#else
        g_ucDpRx0DPCD02201hValue = _D0_DP_LINK_CLK_RATE;
#endif

        // _BIT3:0, Down Stream Port Counter
        pData[0] = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _DP_1_2_DOWN_STREAM_PORT_COUNT));

        // _BIT7 = 1: Always IEEE OUI Support Under DP1.2
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

        // Sink IEEE OUI
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x00, _DP_1_2_SINK_RTK_IEEE_OUI_L);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x01, _DP_1_2_SINK_RTK_IEEE_OUI_M);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x02, _DP_1_2_SINK_RTK_IEEE_OUI_H);

        // Sink IEEE OUI LSB For DP1.2
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x03, _DP_1_2_SINK_RTK_ID_STRING_0);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x04, _DP_1_2_SINK_RTK_ID_STRING_1);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x05, _DP_1_2_SINK_RTK_ID_STRING_2);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x06, _DP_1_2_SINK_RTK_ID_STRING_3);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x07, _DP_1_2_SINK_RTK_ID_STRING_4);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x08, _DP_1_2_SINK_RTK_ID_STRING_5);

        // Sink HW/FW Version For DP1.2
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x09, _DP_1_2_SINK_RTK_HW_VERSION);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x0A, _DP_1_2_SINK_RTK_FW_VERSION_H);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x0B, _DP_1_2_SINK_RTK_FW_VERSION_L);

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x09, 0x00);
#endif
    }
    else if(enumDpVersion == _DP_VERSION_1_2)
    {
        // DPCD Version
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_2);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x00, _DP_VERSION_1_4);
#else
        g_ucDpRx0DPCD02200hValue = _DP_VERSION_1_4;
#endif

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x0E, ~_BIT7, 0x00);

        if(_D0_DP_LINK_CLK_RATE > _DP_HIGH_SPEED2_540MHZ)
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
        }
        else
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
        }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D0_DP_LINK_CLK_RATE);
#else
        g_ucDpRx0DPCD02201hValue = _D0_DP_LINK_CLK_RATE;
#endif

        // _BIT3:0, Down Stream Port Counter
        pData[0] = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _DP_1_2_DOWN_STREAM_PORT_COUNT));

        // _BIT7 = 1: Always IEEE OUI Support Under DP1.2
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

        // Sink IEEE OUI
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x00, _DP_1_2_SINK_RTK_IEEE_OUI_L);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x01, _DP_1_2_SINK_RTK_IEEE_OUI_M);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x02, _DP_1_2_SINK_RTK_IEEE_OUI_H);

        // Sink IEEE OUI LSB For DP1.2
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x03, _DP_1_2_SINK_RTK_ID_STRING_0);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x04, _DP_1_2_SINK_RTK_ID_STRING_1);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x05, _DP_1_2_SINK_RTK_ID_STRING_2);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x06, _DP_1_2_SINK_RTK_ID_STRING_3);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x07, _DP_1_2_SINK_RTK_ID_STRING_4);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x08, _DP_1_2_SINK_RTK_ID_STRING_5);

        // Sink HW/FW Version For DP1.2
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x09, _DP_1_2_SINK_RTK_HW_VERSION);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x0A, _DP_1_2_SINK_RTK_FW_VERSION_H);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x0B, _DP_1_2_SINK_RTK_FW_VERSION_L);

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x09, 0x00);
#endif
    }
    else
    {
        // DPCD Version
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_1);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x00, _DP_VERSION_1_4);
#else
        g_ucDpRx0DPCD02200hValue = _DP_VERSION_1_4;
#endif

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x0E, ~_BIT7, 0x00);

        if(_D0_DP_LINK_CLK_RATE > _DP_HIGH_SPEED_270MHZ)
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR);
        }
        else
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
        }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D0_DP_LINK_CLK_RATE);
#else
        g_ucDpRx0DPCD02201hValue = _D0_DP_LINK_CLK_RATE;
#endif

        // _BIT3:0, Down Stream Port Counter
        pData[0] = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _DP_1_1_DOWN_STREAM_PORT_COUNT));

#if(_DP_SINK_VER11_OUI_SUPPORT == _ON)
        // _BIT7 = 1: IEEE OUI Support
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

        // Sink IEEE OUI
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x00, _DP_1_1_SINK_RTK_IEEE_OUI_L);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x01, _DP_1_1_SINK_RTK_IEEE_OUI_M);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x02, _DP_1_1_SINK_RTK_IEEE_OUI_H);
#else
        // _BIT7 = 0: IEEE OUI Not Support
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT7, 0x00);

        // Sink IEEE OUI
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x00, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x01, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x02, 0x00);
#endif

        // Sink IEEE OUI LSB For DP1.1
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x03, _DP_1_1_SINK_RTK_ID_STRING_0);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x04, _DP_1_1_SINK_RTK_ID_STRING_1);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x05, _DP_1_1_SINK_RTK_ID_STRING_2);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x06, _DP_1_1_SINK_RTK_ID_STRING_3);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x07, _DP_1_1_SINK_RTK_ID_STRING_4);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x08, _DP_1_1_SINK_RTK_ID_STRING_5);

        // Sink HW/FW Version For DP1.1
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x09, _DP_1_1_SINK_RTK_HW_VERSION);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x0A, _DP_1_1_SINK_RTK_FW_VERSION_H);
        ScalerDpRx0SetDpcdValue(0x00, 0x04, 0x0B, _DP_1_1_SINK_RTK_FW_VERSION_L);

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x09, 0x02);
#endif
    }

    if((ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) >= _DP_LINK_HBR2) ||
       ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpRx0GetDpcdInfo(0x00, 0x22, 0x01) >= _DP_LINK_HBR2)))
    {
        // TPS3 Support
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x02, ~_BIT6, _BIT6);
    }
    else
    {
        // TPS3 NonSupport
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x02, ~_BIT6, 0x00);
    }

    // Set TRAINING_AUX_RD_INTERVAL = 400us for EQ phase
    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x0E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_LT_AUX_RD_INTVL_EQ_400US);

    // Align 0220Xh & 0000Xh
    for(pData[0] = 0x02; pData[0] <= 0x0F; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x00, 0x22, pData[0], ScalerDpRx0GetDpcdInfo(0x00, 0x00, pData[0]));
    }
}

//--------------------------------------------------
// Description  : Dp Before Hpd Toggle Process
// Input Value  : EnumDpHotPlugAssertType
// Output Value : None
//--------------------------------------------------
EnumDpHotPlugTime ScalerDpRx0BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType)
{
    if(enumHpdType == _DP_HPD_NONE)
    {
        return _DP_HPD_TIME_NONE;
    }

    if(enumHpdType == _DP_HPD_ASSERTED)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
        if(GET_DP_RX0_ALT_MODE_HPD_STAUTS() == _HIGH)
#else
        if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
#endif
        {
            return _DP_HPD_TIME_NONE;
        }
    }

    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_WD_TIMER_INT_SUPPORT == _ON))
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_RX0_HDCP2_SKE);
#endif

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
    if((enumHpdType != _DP_HDCP_LONG_HPD_EVENT) && (enumHpdType != _DP_HBR2_MARGIN_LINK_HPD_EVENT) && ((ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x00) >= _DP_VERSION_1_2) || (ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)))
    {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D0_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpRx0GetDpcdInfo(0x00, 0x22, 0x01) < _D0_DP_LINK_CLK_RATE)))
#else
        if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D0_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (g_ucDpRx0DPCD02201hValue < _D0_DP_LINK_CLK_RATE)))
#endif
        {
            if(_D0_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D0_DP_LINK_CLK_RATE);
#else
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            g_ucDpRx0DPCD02201hValue = _D0_DP_LINK_CLK_RATE;
#endif
            DebugMessageRx0("Flag Clear_Hotplug Event_D0", _D0_DP_LINK_CLK_RATE);
        }
    }
#endif

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
    if(enumHpdType != _DP_HBR2_MARGIN_LINK_HPD_EVENT)
    {
        ScalerDpRx0CalculateLinkRate(GET_DP_RX_D0_PORT_TARGET_LANE_COUNT());
    }
#endif

    if(enumHpdType != _DP_HPD_ASSERTED)
    {
        if(GET_REG_DP_RX0_MAC_ASSIGNED() == _TRUE)
        {
            ScalerDpRx0AVMute();
        }

        ScalerDpRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);

#if(_DP_HPD_LOW_AUX_NOT_REPLY_SUPPORT == _ON)
        // Reset Aux Phy
        ScalerSetBit(PB7_65_AUX_5, ~_BIT7, 0x00);
#endif
    }

    if(enumHpdType == _DP_HPD_LOW)
    {
        DebugMessageRx0("_D0_HOT_PLUG_LOW", 0);

#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
        SET_DP_RX0_ALT_MODE_HPD_LOW();
#else
        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
#endif

        return _DP_HPD_TIME_NONE;
    }
    else if(enumHpdType == _DP_HPD_LOW_RESET_AUX)
    {
        // Reset Aux Phy
        ScalerSetBit(PB7_65_AUX_5, ~_BIT7, 0x00);

        DebugMessageRx0("_D0_HOT_PLUG_LOW", 0);

#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
        SET_DP_RX0_ALT_MODE_HPD_LOW();
#else
        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
#endif

        return _DP_HPD_TIME_NONE;
    }

    // Reset DDC0
    MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT1;

#if(_DP_FREESYNC_SUPPORT == _ON)
    SET_DP_RX0_AUX_MANUAL_MODE();
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x07, 0x00);
    SET_DP_RX0_AUX_AUTO_MODE();
#endif

    ScalerDpRx0HDCPUnplugReset();

#if(_D0_DP_ASSR_MODE_SUPPORT == _ON)
    SET_DP_RX0_AUX_MANUAL_MODE();
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
    SET_DP_RX0_AUX_AUTO_MODE();
#endif

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
        ScalerSetBit(PB7_65_AUX_5, ~_BIT7, 0x00);

        return _DP_MST_LONG_HPD_TIME;
    }
#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
    else if(enumHpdType == _DP_HBR2_MARGIN_LINK_HPD_EVENT)
    {
        return _DP_HBR2_MARGIN_LINK_HPD_TIME;
    }
#endif
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
void ScalerDpRx0AfterHpdToggleProc(void)
{
    // Release Aux Phy
    ScalerSetBit(PB7_65_AUX_5, ~_BIT7, _BIT7);

    SET_DP_RX0_AUX_MANUAL_MODE();

    if((GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS) && (GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_FAKE_LINK_TRAINING_PASS))
    {
        ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x00, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x01, (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0xE0));
    }

    SET_DP_RX0_AUX_AUTO_MODE();

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    CLR_DP_RX0_HDCP_HANDSHAKE_WO_CAP();
#endif

    if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
    {
        ScalerTimerActiveTimerEvent(1200, _SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);
    }
}

//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HpdIrqAssert(void)
{
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
    if(GET_DP_RX0_ALT_MODE_HPD_STAUTS() == _HIGH)
    {
        ScalerTypeCRx0PdPushHpd(_PD_HPD_IRQ);
    }

#else
    if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
    {
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
        SET_DP_D0_HPD_IRQ_ASSERT_T2_EVENT();
#else

        BYTE ucBackUp2 = ScalerGetByte(PB7_D0_AUX_MODE_SET);

        SET_DP_RX0_AUX_MANUAL_MODE();

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);

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

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);

        if((ucBackUp2 & _BIT1) == _BIT1)
        {
            SET_DP_RX0_AUX_AUTO_MODE();
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
void ScalerDpRx0HpdIrqAssert_EXINT0(void) using 1
{
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
    if(GET_DP_RX0_ALT_MODE_HPD_STAUTS() == _HIGH)
    {
        ScalerTypeCRx0PdPushHpd_EXINT0(_PD_HPD_IRQ);
    }

#else
    if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
    {
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
        SET_DP_D0_HPD_IRQ_ASSERT_T2_EVENT();
#else

        BYTE ucBackUp2 = ScalerGetByte_EXINT(PB7_D0_AUX_MODE_SET);

        SET_DP_RX0_AUX_MANUAL_MODE_EXINT();

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);

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

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);

        if((ucBackUp2 & _BIT1) == _BIT1)
        {
            SET_DP_RX0_AUX_AUTO_MODE_EXINT();
        }
#endif
    }
#endif
}

//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType) using 1
{
    BYTE ucBackUp = 0;

    ucBackUp = ScalerGetByte_EXINT(PB7_D0_AUX_MODE_SET);

    switch(enumBStatusType)
    {
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpRx0SetDpcdValue_EXINT0(0x06, 0x94, 0x93, (ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;

        default:

            break;
    }

    // Link Status CPIRQ Flag
    pData_EXINT[0] = (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x01) | _BIT2);

    // SET AUX AUTO MODE
    SET_DP_RX0_AUX_AUTO_MODE_EXINT();

    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x01, pData_EXINT[0]);

    if((ucBackUp & _BIT1) == 0x00)
    {
        // SET AUX MANUAL MODE
        SET_DP_RX0_AUX_MANUAL_MODE_EXINT();
    }

    ScalerDpRx0HpdIrqAssert_EXINT0();
}
#endif

//--------------------------------------------------
// Description  : Dp Mac Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0MacInitial(void)
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
    ScalerDpRx0SetFifoWD(_DISABLE);

    // Disable DP Fifo Under/OverFlow IRQ
    ScalerDpRx0SetFifoIRQ(_DISABLE);

    // Disable DP No Video Stream IRQ
    ScalerDpRx0SetNoVideoStreamIRQ(_DISABLE);

    ScalerDpRx0SetInitialRSV0InfoType();

    // Enable HW to store data to RSV0 memory (Only for RL6492)
    ScalerSetBit(PB6_3E_DP_INFO_FM_RSV_STATUS, ~_BIT4, _BIT4);

#if((_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON) && (_HW_DP_VSC_SDP_REG_SUPPORT != _ON))

    ScalerDpRx0SetInitialRSV1InfoType();

    // Enable HW to store data to RSV1 memory (Only for RL6492)
    ScalerSetBit(PB6_3E_DP_INFO_FM_RSV_STATUS, ~_BIT5, _BIT5);

#endif

    CLR_DP_RX0_MSA_FAIL_MAC_RESET_COUNT();
}

//--------------------------------------------------
// Description  : DP Phy Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyInitial(void)
{
    //////////////////
    // Misc Setting //
    //////////////////

    // [7:4] pn_channel_en = 4'b1111 --> Switch PN Channel On
    // [3:0] Enable Signal Detection
    ScalerSetByte(P1A_20_DP_RX_00, 0xFF);

#if((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) || (_D0_DP_Z0_IMPEDANCE_OPTION == _U3_90_OHM))

    // Lane0/2 Z0 Differential Impedance = 0x5
    // Lane1/3 Z0 Differential Impedance = 0x7
    ScalerSetByte(P1A_01_COMBO_01, 0x75);
    ScalerSetByte(P1A_02_COMBO_02, 0x75);
#else
    // Lane0/2 Z0 Differential Impedance = 0x4
    // Lane1/3 Z0 Differential Impedance = 0x6
    ScalerSetByte(P1A_01_COMBO_01, 0x64);
    ScalerSetByte(P1A_02_COMBO_02, 0x64);
#endif

    // [3:0] sel_pi_phase = 1 --> PR Normal Mode
    ScalerSetBit(P1A_28_DP_RX_08, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));


    /////////////////
    // DFE Initial //
    /////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    ScalerSetBit(P17_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    ScalerSetBit(P17_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    ScalerSetBit(P17_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    ScalerSetBit(P17_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    // [7:6] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetByte(P17_E0_MODE_TIMER, 0xB2);

    // Set DFE Delay Time
    ScalerSetByte(P17_E1_TIMER, 0x01);

    // Tap0,Tap1 Loop Gain 1/512
    ScalerSetBit(P17_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap2,Tap3 Loop Gain 1/512
    ScalerSetBit(P17_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4,Servo Loop Gain 1/512
    ScalerSetBit(P17_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // LE Gain1 Loop Gain 1/256, LE Gain2 Loop Gain 0, LE Pre-Courser Gain 0
    ScalerSetBit(P17_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit(P17_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap0 Max is 27
    ScalerSetByte(P17_E6_LIMIT_1, 0x3B);

    // Tap1 Min is -10
    ScalerSetByte(P17_E7_LIMIT_2, 0x0A);

    // Tap2 Max is 6, Min is -6
    ScalerSetBit(P17_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit(P17_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P17_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 3, Min is -3
    ScalerSetBit(P17_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(P17_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 3, Min is -3
    ScalerSetBit(P17_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P17_EB_LIMIT_6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P17_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Tap0 Threshold = 10
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetByte(P17_EC_LOOP_DIV_1, 0xA3);

    // [1] tap1_trans = 1'b1 --> Tap1 is Effective on Transition bit
    // [0] tap0_trans = 1'b0 --> Tap0 is Effective every Bits
    ScalerSetBit(P17_E3_GAIN_2, ~(_BIT1 | _BIT0), _BIT1);

    // [5] servo_notrans = 1'b0 --> Servo is Effective on Every Bits
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT5, 0x00);

    // [1:0] trans_rlength = 2'b00 --> Tap0 Run Length = 2
    ScalerSetBit(P17_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);

    // Set Vth Max = 63, Min = 12
    ScalerSetByte(P17_F9_LIMIT_10, 0xF3);


    ////////////////
    // EQ Setting //
    ////////////////

    // reg_tap_en : DFE TAP Enable
    ScalerSetBit(P1A_16_COMBO_RX_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1A_17_COMBO_RX_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [6:4] reg_fld_adp_time = 0.64*(6+1) us
    ScalerSetBit(P1C_57_DP_FLD_9, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));


    /////////////////
    // CDR Setting //
    /////////////////

    // [7] en_wide_temp = 1 --> Vcp-Vcn = -0.1V
    ScalerSetBit(P1A_04_COMBO_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] reg_en_vco_lpf = 4'b0000 --> Analog CDR Multi Band VCO's LPF Always Off
    ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [1:0] reg_vcm_ctrl_rx_l0_l2 = 2'b00  --> vdd - 0.2V
    ScalerSetBit(P1A_2C_DP_RX_12, ~(_BIT1 | _BIT0), 0x00);

    // reg_timer_en = 1 for CDR_RDY
    ScalerSetBit(P1C_4B_READY_TIMER_0, ~_BIT0, _BIT0);

    // reg_fld_cp_adj_en = 4'b1111 Enable Adjust Icp When Tracking
    ScalerSetBit(P1C_55_DP_FLD_7, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // reg_cdr_div_delta for FLD Lock Band Setting
    ScalerSetByte(P1C_6D_DP_FLD_31, 0x01);
    ScalerSetByte(P1C_6E_DP_FLD_32, 0x01);
    ScalerSetByte(P1C_6F_DP_FLD_33, 0x01);
    ScalerSetByte(P1C_70_DP_FLD_34, 0x01);

    // reg_dp_fld_rstb = 1'b1 --> Enable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~_BIT4, _BIT4);


    ////////////////////
    // Offset Setting //
    ////////////////////

    // reg_offk_dellay = 4*Clock Period for Accuracy
    ScalerSetBit(P1C_27_FORE_OFFSET_K_1, ~(_BIT6 | _BIT5), _BIT5);
    ScalerSetBit(P1C_2F_FORE_OFFSET_K_9, ~(_BIT6 | _BIT5), _BIT5);
    ScalerSetBit(P1C_37_FORE_OFFSET_K_17, ~(_BIT6 | _BIT5), _BIT5);
    ScalerSetBit(P1C_3F_FORE_OFFSET_K_25, ~(_BIT6 | _BIT5), _BIT5);

    // reg_sel_forek = LEQ for Detecting Calibration Done
    ScalerSetBit(P1C_28_FORE_OFFSET_K_2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit(P1C_30_FORE_OFFSET_K_10, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit(P1C_38_FORE_OFFSET_K_18, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit(P1C_40_FORE_OFFSET_K_26, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // reg_rstb_fore_offset = 1'b1 --> Enable foreground K
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~_BIT4, _BIT4);

    // DP Global Parameter MeasureCount Initial
    ScalerSyncDpMeasureCountInitial();

    g_usDpRx0D10p2CountCriteriaUpperBoundRBR = _DP_COUNT_D10P2_UPPER_BOUND_1000_RBR_SAVED;
    g_usDpRx0D10p2CountCriteriaUpperBoundHBR = _DP_COUNT_D10P2_UPPER_BOUND_1000_HBR_SAVED;
    g_usDpRx0D10p2CountCriteriaUpperBoundHBR2 = _DP_COUNT_D10P2_UPPER_BOUND_1000_HBR2_SAVED;

    g_usDpRx0D10p2CountCriteriaLowerBoundRBR = _DP_COUNT_D10P2_LOWER_BOUND_1000_RBR_SAVED;
    g_usDpRx0D10p2CountCriteriaLowerBoundHBR = _DP_COUNT_D10P2_LOWER_BOUND_1000_HBR_SAVED;
    g_usDpRx0D10p2CountCriteriaLowerBoundHBR2 = _DP_COUNT_D10P2_LOWER_BOUND_1000_HBR2_SAVED;
}

//--------------------------------------------------
// Description  : Rebuilding DP PHY
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [4] Enable Comma Detection
    ScalerSetBit(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
    {
        // [5] Disable De-Scrambling
        ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // [5] Enable De-Scrambling
        ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
    }

    if((ucDpcdLane & _BIT7) == _BIT7)
    {
        // [2] Enable Enhancement Control Mode
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // [2] Disable Enhancement Control Mode
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

    // Main-Link Lane Setting Start
    if(ScalerTypeCRx0PdGetPinAssignment() != _TYPE_C_PIN_ASSIGNMENT_E)
    {
        // Pin Assignment C/D PN Swap
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, _D0_DP_PCB_LANE3_PN_SWAP << 7);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, _D0_DP_PCB_LANE2_PN_SWAP << 6);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, _D0_DP_PCB_LANE1_PN_SWAP << 5);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, _D0_DP_PCB_LANE0_PN_SWAP << 4);
    }
    else
    {
        // Pin Assignment E PN Swap
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, (!_D0_DP_PCB_LANE3_PN_SWAP) << 7);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, (!_D0_DP_PCB_LANE2_PN_SWAP) << 6);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, (!_D0_DP_PCB_LANE1_PN_SWAP) << 5);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, (!_D0_DP_PCB_LANE0_PN_SWAP) << 4);
    }

    SET_DP_RX0_PCB_LANE0_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT7) >> 7);
    SET_DP_RX0_PCB_LANE1_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT6) >> 6);
    SET_DP_RX0_PCB_LANE2_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT5) >> 5);
    SET_DP_RX0_PCB_LANE3_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT4) >> 4);

    switch(ScalerTypeCRx0PdGetPinAssignment())
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE1_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE0_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE2_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);

                // [1:0] DP Mac Clock Selection
                ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE0_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);

                // [1:0] DP Mac Clock Selection
                ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);
            }

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            ScalerDpRx0Rebuild4LanePhy(ucDpLinkRate, ucDpcdLane);

            break;

        case _TYPE_C_PIN_ASSIGNMENT_D:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE1_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE0_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE2_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);

                SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
                SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
                SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
                SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

                // [1:0] DP Mac Clock Selection
                ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);

                ScalerDpRx0RebuildUnFlip2LanePhy(ucDpLinkRate, ucDpcdLane);
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE0_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);

                SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
                SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
                SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
                SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

                // [1:0] DP Mac Clock Selection
                ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);

                ScalerDpRx0RebuildFlip2LanePhy(ucDpLinkRate, ucDpcdLane);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_E:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE2_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE3_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE1_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);

                // [1:0] DP Mac Clock Selection
                ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE0_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE1_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE3_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE2_MAPPING);

                // [1:0] DP Mac Clock Selection
                ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE2_MAPPING);
            }

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            ScalerDpRx0Rebuild4LanePhy(ucDpLinkRate, ucDpcdLane);

            break;

        default:
        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            // DP Lane Swap Setting
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE1_MAPPING << 2);
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            // [1:0] DP Mac Clock Selection
            ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);

            ScalerDpRx0Rebuild4LanePhy(ucDpLinkRate, ucDpcdLane);

            break;
    }

#else

    // DP Lane Swap Setting
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_LANE3 << 6);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_LANE2 << 4);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_LANE1 << 2);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // DP Lane PN Swap Setting
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, GET_DP_RX0_PCB_LANE3_PN_SWAP() << 7);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, GET_DP_RX0_PCB_LANE2_PN_SWAP() << 6);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, GET_DP_RX0_PCB_LANE1_PN_SWAP() << 5);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, GET_DP_RX0_PCB_LANE0_PN_SWAP() << 4);

    // [1:0] DP Mac Clock Selection
    ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);

    ScalerDpRx0Rebuild4LanePhy(ucDpLinkRate, ucDpcdLane);

#endif
}

//--------------------------------------------------
// Description  : Rebuilding DP 4Lane
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Rebuild4LanePhy(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
    BYTE ucIcp = 0;
    BYTE pucTap0[4];

    // LDO_en for Lane1,3
    ScalerSetBit(P1A_30_COMBO_USB_00, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));

    // Enable Lane1,3 1.1V LDO Tracking
    ScalerSetBit(P1A_30_COMBO_USB_00, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

    // [7:4] LANE_EN = 4'b0000 --> Disable LANE_EN
    // [3:0] CDR_EN = 4'b0000 --> Disable CDR_EN
    ScalerSetByte(P1A_22_DP_RX_02, 0x00);

    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT2, _BIT2);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT3, _BIT3);
            }

            // [4:3] DP MAC Select One Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT2, _BIT2);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT3, _BIT3);
            }

            if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT2, _BIT2);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT3, _BIT3);
            }

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        default:
        case _DP_FOUR_LANE:

            // [7:4] Enable LANE_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // [3:0] Enable Lane0~3 CDR_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // [4:3] DP MAC Select Four Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetByte(P1C_4C_READY_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte(P1C_4D_READY_TIMER_2, 0x0F);

    // [4:2] reg_vcm_ctrl_op_l1 = 3'b101 --> 600mV
    ScalerSetBit(P1A_2C_DP_RX_12, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [4:2] reg_vcm_ctrl_op_l3 = 3'b101 --> 600mV
    ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [3:0] reg_fld_xtal_en = 4'b1111 --> Using 27M Xtal
    ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] Disable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpRx0SetDFEInitial(ucDpLinkRate);


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            // [7:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 900M/v in Each Lane
            ScalerSetByte(P1A_03_COMBO_03, 0x55);

            // [7:4] en_half_pf = 1 --> Half Rate PD for High Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // [6:4][2:0] sel_cont3 = 3'b010 --> BBPD UP/DN Sync
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // [4][0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~(_BIT4 | _BIT0), 0x00);

            // [7:5][3:1] LE_lowgain_highboost = 3'b110
            // [4][0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetByte(P1A_14_COMBO_RX_04, 0xCC);

            // [7:6] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), 0x00);

            // [1:0] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_sel_cdr_res = 2K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x50);
            ScalerSetByte(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 13.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xCC);
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xCC);

            // Analog CDR Auto FLD Counter (50/500 = 2*(27M/540M))
            ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(P1C_63_DP_FLD_21, 0x31);
            ScalerSetByte(P1C_64_DP_FLD_22, 0x31);
            ScalerSetByte(P1C_65_DP_FLD_23, 0x31);
            ScalerSetByte(P1C_66_DP_FLD_24, 0x31);

            ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
            ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
            ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
            ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);

            g_pusDpRx0ClockCount[0] = 0x2710; // ideal 5.4G

            break;

        case _DP_LINK_HBR:

            // [7:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetByte(P1A_03_COMBO_03, 0x00);

            // [7:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [6:4][2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // [4][0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~(_BIT4 | _BIT0), 0x00);

            // [7:5][3:1] LE_lowgain_highboost = 3'b100
            // [4][0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetByte(P1A_14_COMBO_RX_04, 0x88);

            // [7:6] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT6);

            // [1:0] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 8K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x50);
            ScalerSetByte(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 16.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xDD);
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xDD);

            // Analog CDR Auto FLD Counter (100/500 = 2*(27M/270M))
            ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(P1C_63_DP_FLD_21, 0x63);
            ScalerSetByte(P1C_64_DP_FLD_22, 0x63);
            ScalerSetByte(P1C_65_DP_FLD_23, 0x63);
            ScalerSetByte(P1C_66_DP_FLD_24, 0x63);

            ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
            ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
            ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
            ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);

            g_pusDpRx0ClockCount[0] = 0x1388; // ideal 2.7G

            break;

        default:
        case _DP_LINK_RBR:

            // [7:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetByte(P1A_03_COMBO_03, 0x00);

            // [7:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [6:4][2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // [4][0] highboost_for_rbr = 1 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

            // [7:5][3:1] LE_lowgain_highboost = 3'b000
            // [4][0] sel_dyn_std = 1 --> Std DFF
            ScalerSetByte(P1A_14_COMBO_RX_04, 0x11);

            // [7:6] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT7);

            // [1:0] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT1);

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 6K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x70);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x70);
            ScalerSetByte(P1C_53_DP_FLD_5, 0x70);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x70);

            // reg_fld_cdr_cp Icp = 19.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xEE);
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xEE);

            // Analog CDR Auto FLD Counter (50/150 = 2*(27M/162M))
            ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(P1C_63_DP_FLD_21, 0x31);
            ScalerSetByte(P1C_64_DP_FLD_22, 0x31);
            ScalerSetByte(P1C_65_DP_FLD_23, 0x31);
            ScalerSetByte(P1C_66_DP_FLD_24, 0x31);

            ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(P1C_68_DP_FLD_26, 0x96);
            ScalerSetByte(P1C_69_DP_FLD_27, 0x96);
            ScalerSetByte(P1C_6A_DP_FLD_28, 0x96);
            ScalerSetByte(P1C_6B_DP_FLD_29, 0x96);

            g_pusDpRx0ClockCount[0] = 0xBB8; // ideal 1.62G

            break;
    }

    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];

    // Backup Icp for CDR lock
    ucIcp = ScalerGetByte(P1C_5D_DP_FLD_15);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P1C_2E_FORE_OFFSET_K_8, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_36_FORE_OFFSET_K_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_3E_FORE_OFFSET_K_24, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_46_FORE_OFFSET_K_32, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable Foreground Calibration
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    //////////////
    // FLD Band //
    //////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetByte(P1C_50_DP_FLD_2, 0xFF);
    ScalerSetByte(P1C_50_DP_FLD_2, 0x0F);

    // [3:0] reg_fld_en = 4'b0000 --> Disable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(P17_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte(P17_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte(P17_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte(P17_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(P17_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte(P17_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte(P17_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte(P17_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // [3:0] reg_fld_en = 4'b1111 --> Enable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // Disable DFE Adaptation
    ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte(P17_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte(P17_A4_L0_INIT_2, 0x1B);
            ScalerSetBit(P17_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P17_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(P17_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte(P17_B4_L1_INIT_2, 0x1B);
            ScalerSetBit(P17_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P17_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(P17_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte(P17_C4_L2_INIT_2, 0x1B);
            ScalerSetBit(P17_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P17_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit(P17_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte(P17_D4_L3_INIT_2, 0x1B);
            ScalerSetBit(P17_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P17_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit(P17_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }

    // Enable Foreground Offset Calibration lane
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    ///////////////////////
    // FLD Band Finetune //
    ///////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetByte(P1C_59_DP_FLD_11, ScalerGetByte(P1C_75_DP_FLD_39));
    ScalerSetByte(P1C_5A_DP_FLD_12, ScalerGetByte(P1C_76_DP_FLD_40));
    ScalerSetByte(P1C_5B_DP_FLD_13, ScalerGetByte(P1C_77_DP_FLD_41));
    ScalerSetByte(P1C_5C_DP_FLD_14, ScalerGetByte(P1C_78_DP_FLD_42));

    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock for Signal Detection
    ScalerSetBit(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_fld_cp_en_manual = 4'b0000 --> CDR Open Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetByte(P1C_50_DP_FLD_2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] Enable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE0);

            break;

        case _DP_TWO_LANE:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE0);

            // Lane1 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE1);

            break;

        default:
        case _DP_FOUR_LANE:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE0);

            // Lane1 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE1);

            // Lane2 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE2);

            // Lane3 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE3);

            break;
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte(P1C_5D_DP_FLD_15, 0xFF);
    ScalerSetByte(P1C_5E_DP_FLD_16, 0xFF);

    // [3:0] reg_fld_cp_en_manual = 4'b1111 --> CDR Close Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte(P1C_5D_DP_FLD_15, ucIcp);
    ScalerSetByte(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    // [1:0] freqdet_lane_sel = Lane0
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

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
            g_pusDpRx0ClockCount[0] = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }

    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];
}

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
//--------------------------------------------------
// Description  : Rebuilding DP 2Lane PHY at Unflip Alt Mode
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RebuildUnFlip2LanePhy(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
    BYTE ucIcp = 0;
    BYTE pucTap0[2];

    // LDO_en for Lane3
    ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT5, _BIT5);

    // Enable Lane3 1.1V LDO Tracking
    ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT4, _BIT4);

    // [7:6] LANE_EN = 2'000 --> Disable LANE_EN
    // [3:2] CDR_EN = 2'b00 --> Disable CDR_EN
    ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT2, _BIT2);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT3, _BIT3);
            }

            // [4:3] DP MAC Select One Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        default:
        case _DP_TWO_LANE:

            // [7:6] Enable Lane2/3 LANE_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // [3:2] Enable Lane2~3 CDR_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2), _BIT2);
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:6] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:2] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit(P1C_4C_READY_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7:6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [4:2] reg_vcm_ctrl_op_l3 = 3'b101 --> 600mV
    ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [3:2] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
    ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:0] Disable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpRx0SetDFEInitialUnFlip2Lane(ucDpLinkRate);


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            // [7:4] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 900M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

            // [7:6] en_half_pf = 1 --> Half Rate PD for High Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // [6:4] sel_cont3 = 3'b010 --> BBPD UP/DN Sync
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

            // [4] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT4, 0x00);

            // [7:5] LE_lowgain_highboost = 3'b110
            // [4] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

            // [1:0] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_sel_cdr_res = 2K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 13.5uA in Each Lane
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xCC);

            // Analog CDR Auto FLD Counter (50/500 = 2*(27M/540M))
            ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetByte(P1C_65_DP_FLD_23, 0x31);
            ScalerSetByte(P1C_66_DP_FLD_24, 0x31);

            ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
            ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
            ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);

            g_pusDpRx0ClockCount[0] = 0x2710; // ideal 5.4G

            break;

        case _DP_LINK_HBR:

            // [7:4] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [7:6] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6), 0x00);

            // [6:4] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

            // [4] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT4, 0x00);

            // [7:5] LE_lowgain_highboost = 3'b100
            // [4] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

            // [1:0] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 8K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Initial Band
            ScalerSetByte(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 16.5uA in Each Lane
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xDD);

            // Analog CDR Auto FLD Counter (100/500 = 2*(27M/270M))
            ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetByte(P1C_65_DP_FLD_23, 0x63);
            ScalerSetByte(P1C_66_DP_FLD_24, 0x63);

            ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
            ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
            ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);

            g_pusDpRx0ClockCount[0] = 0x1388; // ideal 2.7G

            break;

        default:
        case _DP_LINK_RBR:

            // [7:4] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [7:6] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6), 0x00);

            // [6:4] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

            // [4] highboost_for_rbr = 1 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT4, _BIT4);

            // [7:5] LE_lowgain_highboost = 3'b000
            // [4] sel_dyn_std = 1 --> Std DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

            // [1:0] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT1);

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 6K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_53_DP_FLD_5, 0x70);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x70);

            // reg_fld_cdr_cp Icp = 19.5uA in Each Lane
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xEE);

            // Analog CDR Auto FLD Counter (50/150 = 2*(27M/162M))
            ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetByte(P1C_65_DP_FLD_23, 0x31);
            ScalerSetByte(P1C_66_DP_FLD_24, 0x31);

            ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetByte(P1C_6A_DP_FLD_28, 0x96);
            ScalerSetByte(P1C_6B_DP_FLD_29, 0x96);

            g_pusDpRx0ClockCount[0] = 0xBB8; // ideal 1.62G

            break;
    }

    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];

    // Backup Icp for CDR lock
    ucIcp = ScalerGetByte(P1C_5E_DP_FLD_16);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P1C_3E_FORE_OFFSET_K_24, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_46_FORE_OFFSET_K_32, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable Foreground Calibration lane2, 3
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    //////////////
    // FLD Band //
    //////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:2] reg_fld_en = 2'b00 --> Disable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(P17_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte(P17_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(P17_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte(P17_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // [3:2] reg_fld_en = 2'b11 --> Enable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // Disable DFE Adaptation
    ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte(P17_F0_COEF_1, 0x01);

        // Select to Lane2
        ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[0] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[1] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte(P17_C4_L2_INIT_2, 0x1B);
            ScalerSetBit(P17_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P17_C4_L2_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(P17_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte(P17_D4_L3_INIT_2, 0x1B);
            ScalerSetBit(P17_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P17_D4_L3_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(P17_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }
    // Enable Foreground Offset Calibration lane2, 3
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    ///////////////////////
    // FLD Band Finetune //
    ///////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetByte(P1C_5B_DP_FLD_13, ScalerGetByte(P1C_77_DP_FLD_41));
    ScalerSetByte(P1C_5C_DP_FLD_14, ScalerGetByte(P1C_78_DP_FLD_42));

    // [3:2] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock for Signal Detection
    ScalerSetBit(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:2] reg_fld_cp_en_manual = 4'b0000 --> CDR Open Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT3 | _BIT2), 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] Enable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE0);

            break;

        default:
        case _DP_TWO_LANE:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE0);

            // Lane1 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE1);

            break;
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte(P1C_5E_DP_FLD_16, 0xFF);

    // [3:2] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7:6] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    // [1:0] freqdet_lane_sel = Lane0
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

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
            g_pusDpRx0ClockCount[0] = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }

    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];
}


//--------------------------------------------------
// Description  : Rebuilding DP 2Lane PHY at Flip Alt Mode
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RebuildFlip2LanePhy(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
    BYTE ucIcp = 0;
    BYTE pucTap0[2];

    // LDO_en for Lane1
    ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT1, _BIT1);

    // Enable Lane1 1.1V LDO Tracking
    ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT0, _BIT0);

    // [5:4] LANE_EN = 2'000 --> Disable LANE_EN
    // [1:0] CDR_EN = 2'b00 --> Disable CDR_EN
    ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 LANE_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_EN
                ScalerSetBit(P1A_22_DP_RX_02, ~_BIT1, _BIT1);
            }

            // [4:3] DP MAC Select One Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        default:
        case _DP_TWO_LANE:

            // [7:6] Enable Lane0/1 LANE_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

            // [3:2] Enable Lane0~1 CDR_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [1:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit(P1C_4C_READY_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [4:2] reg_vcm_ctrl_op_l1 = 3'b101 --> 600mV
    ScalerSetBit(P1A_2C_DP_RX_12, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [1:0] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
    ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [3:0] Disable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpRx0SetDFEInitialFlip2Lane(ucDpLinkRate);


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            // [3:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 900M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // [5:4] en_half_pf = 1 --> Half Rate PD for High Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

            // [2:0] sel_cont3 = 3'b010 --> BBPD UP/DN Sync
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            // [0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT0, 0x00);

            // [3:1] LE_lowgain_highboost = 3'b110
            // [0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

            // [7:6] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), 0x00);

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_sel_cdr_res = 2K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x50);

            // reg_fld_cdr_cp Icp = 13.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xCC);

            // Analog CDR Auto FLD Counter (50/500 = 2*(27M/540M))
            ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte(P1C_63_DP_FLD_21, 0x31);
            ScalerSetByte(P1C_64_DP_FLD_22, 0x31);

            ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
            ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);

            g_pusDpRx0ClockCount[0] = 0x2710; // ideal 5.4G

            break;

        case _DP_LINK_HBR:

            // [3:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // [5:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT5 | _BIT4), 0x00);

            // [2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // [0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT0, 0x00);

            // [3:1] LE_lowgain_highboost = 3'b100
            // [0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

            // [7:6] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT6);

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 8K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x50);

            // reg_fld_cdr_cp Icp = 16.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xDD);

            // Analog CDR Auto FLD Counter (100/500 = (27M/270M))
            ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetByte(P1C_63_DP_FLD_21, 0x63);
            ScalerSetByte(P1C_64_DP_FLD_22, 0x63);

            ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
            ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
            ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);

            g_pusDpRx0ClockCount[0] = 0x1388; // ideal 2.7G

            break;

        default:
        case _DP_LINK_RBR:

            // [3:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // [5:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT5 | _BIT4), 0x00);

            // [2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // [0] highboost_for_rbr = 1 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT0, _BIT0);

            // [3:1] LE_lowgain_highboost = 3'b000
            // [0] sel_dyn_std = 1 --> Std DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            // [7:6] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT7);

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 6K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x70);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x70);

            // reg_fld_cdr_cp Icp = 19.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xEE);

            // Analog CDR Auto FLD Counter (50/150 = 2*(27M/162M))
            ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte(P1C_63_DP_FLD_21, 0x31);
            ScalerSetByte(P1C_64_DP_FLD_22, 0x31);

            ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte(P1C_68_DP_FLD_26, 0x96);
            ScalerSetByte(P1C_69_DP_FLD_27, 0x96);

            g_pusDpRx0ClockCount[0] = 0xBB8; // ideal 1.62G

            break;
    }

    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];

    // Backup Icp for CDR lock
    ucIcp = ScalerGetByte(P1C_5D_DP_FLD_15);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P1C_2E_FORE_OFFSET_K_8, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_36_FORE_OFFSET_K_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable Foreground Calibration lane0, 1
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    //////////////
    // FLD Band //
    //////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] reg_fld_en = 2'b00 --> Disable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(P17_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte(P17_B1_L1_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(P17_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte(P17_B1_L1_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // [1:0] reg_fld_en = 2'b11 --> Enable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // Disable DFE Adaptation
    ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte(P17_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte(P17_A4_L0_INIT_2, 0x1B);
            ScalerSetBit(P17_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P17_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(P17_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte(P17_B4_L1_INIT_2, 0x1B);
            ScalerSetBit(P17_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P17_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(P17_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P17_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
    }

    // Enable Foreground Offset Calibration lane0, 1
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    ///////////////////////
    // FLD Band Finetune //
    ///////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetByte(P1C_59_DP_FLD_11, ScalerGetByte(P1C_75_DP_FLD_39));
    ScalerSetByte(P1C_5A_DP_FLD_12, ScalerGetByte(P1C_76_DP_FLD_40));

    // [1:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock for Signal Detection
    ScalerSetBit(P1C_57_DP_FLD_9, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] reg_fld_cp_en_manual = 4'b0000 --> CDR Open Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT1 | _BIT0), 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] Enable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE0);

            break;

        default:
        case _DP_TWO_LANE:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE0);

            // Lane1 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE1);

            break;
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte(P1C_5D_DP_FLD_15, 0xFF);

    // [1:0] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte(P1C_5D_DP_FLD_15, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [5:4] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    // [1:0] freqdet_lane_sel = Lane0
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

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
            g_pusDpRx0ClockCount[0] = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }

    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];
}
#endif

//--------------------------------------------------
// Description  : DP FLD Band Finetune
// Input Value  : LaneNumber
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AdjustLaneFLDBand(BYTE ucDpRx0LaneNumber)
{
    WORD usVCOAutoBandAdd4 = 0;
    BYTE ucBestVCOBand = 0;
    BYTE ucFLDBand = 0;
    BYTE ucVCOBandDiff = 0;

    g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] = 0;

    // [1:0] freqdet_lane_sel
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), ucDpRx0LaneNumber);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        // FLD Auto Band Measure Done
        if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            // Clock Count of Each Lane in FLD Auto Band
            g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }


    ////////////////////////
    // Fine Tune VCO Band //
    ////////////////////////

    // Scan Lane0~3 Auto FLD
    switch(ucDpRx0LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ucFLDBand = ScalerGetByte(P1C_59_DP_FLD_11);
            ScalerSetByte(P1C_59_DP_FLD_11, (ucFLDBand + 4));

            break;

        case _DP_SCALER_LANE1:

            ucFLDBand = ScalerGetByte(P1C_5A_DP_FLD_12);
            ScalerSetByte(P1C_5A_DP_FLD_12, (ucFLDBand + 4));

            break;

        case _DP_SCALER_LANE2:

            ucFLDBand = ScalerGetByte(P1C_5B_DP_FLD_13);
            ScalerSetByte(P1C_5B_DP_FLD_13, (ucFLDBand + 4));

            break;

        case _DP_SCALER_LANE3:

            ucFLDBand = ScalerGetByte(P1C_5C_DP_FLD_14);
            ScalerSetByte(P1C_5C_DP_FLD_14, (ucFLDBand + 4));

            break;
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        if((g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] == 0) || (ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6))
        {
            break;
        }
    }

    // Measure Done
    if((g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] != 0) && (ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6))
    {
        usVCOAutoBandAdd4 = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        ucVCOBandDiff = (abs(g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] - usVCOAutoBandAdd4) >> 2);
    }
    else
    {
        ucVCOBandDiff = 0;
    }


    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    if(ucVCOBandDiff != 0)
    {
        if(g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] < g_pusDpRx0ClockCount[ucDpRx0LaneNumber])
        {
            ucBestVCOBand = ucFLDBand + (((g_pusDpRx0ClockCount[ucDpRx0LaneNumber] - g_pusDpRx0ClockCount1[ucDpRx0LaneNumber]) / ucVCOBandDiff) + 1);
        }
        else
        {
            ucBestVCOBand = ucFLDBand - ((g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] - g_pusDpRx0ClockCount[ucDpRx0LaneNumber]) / ucVCOBandDiff);
        }
    }
    else
    {
        ucBestVCOBand = ucFLDBand;
    }

    // Manually Reload FLD Band
    switch(ucDpRx0LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ScalerSetByte(P1C_59_DP_FLD_11, ucBestVCOBand);

            break;

        case _DP_SCALER_LANE1:

            ScalerSetByte(P1C_5A_DP_FLD_12, ucBestVCOBand);

            break;

        case _DP_SCALER_LANE2:

            ScalerSetByte(P1C_5B_DP_FLD_13, ucBestVCOBand);

            break;

        case _DP_SCALER_LANE3:

            ScalerSetByte(P1C_5C_DP_FLD_14, ucBestVCOBand);

            break;
    }
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDFEInitial(EnumDpLinkRate enumDpLinkRate)
{
    if(((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x02) & (_BIT2 | _BIT1 | _BIT0)) == 0x03) ||
       ((enumDpLinkRate == _DP_LINK_HBR2) && (GET_DP_RX0_PHY_CTS_FLG() == _TRUE) && ((g_ucDpRx0PhyCtsCtrl & 0x0F) == 0x02)))
    {
        // Tap Divider = 34 for TPS3
        ScalerSetByte(P17_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte(P17_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);

    // LE Max = 24, LE Initial = 16, Servo Initial = 16
    ScalerSetByte(P17_A2_L0_LIMIT_INIT, 0x80);
    ScalerSetByte(P17_B2_L1_LIMIT_INIT, 0x80);
    ScalerSetByte(P17_C2_L2_LIMIT_INIT, 0x80);
    ScalerSetByte(P17_D2_L3_LIMIT_INIT, 0x80);

    ScalerSetByte(P17_A3_L0_INIT_1, 0xD0);
    ScalerSetByte(P17_B3_L1_INIT_1, 0xD0);
    ScalerSetByte(P17_C3_L2_INIT_1, 0xD0);
    ScalerSetByte(P17_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 21
    ScalerSetByte(P17_A4_L0_INIT_2, 0x15);
    ScalerSetByte(P17_B4_L1_INIT_2, 0x15);
    ScalerSetByte(P17_C4_L2_INIT_2, 0x15);
    ScalerSetByte(P17_D4_L3_INIT_2, 0x15);

    // Tap1 Initial Value = 0
    ScalerSetByte(P17_A5_L0_INIT_3, 0x00);
    ScalerSetByte(P17_B5_L1_INIT_3, 0x00);
    ScalerSetByte(P17_C5_L2_INIT_3, 0x00);
    ScalerSetByte(P17_D5_L3_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte(P17_A6_L0_INIT_4, 0x00);
    ScalerSetByte(P17_B6_L1_INIT_4, 0x00);
    ScalerSetByte(P17_C6_L2_INIT_4, 0x00);
    ScalerSetByte(P17_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 28
    ScalerSetByte(P17_A9_L0_INIT_7, 0x1C);
    ScalerSetByte(P17_B9_L1_INIT_7, 0x1C);
    ScalerSetByte(P17_C9_L2_INIT_7, 0x1C);
    ScalerSetByte(P17_D9_L3_INIT_7, 0x1C);

    // Load Intial DFE Code
    ScalerSetByte(P17_AA_L0_INIT_8, 0xFF);
    ScalerSetByte(P17_BA_L1_INIT_8, 0xFF);
    ScalerSetByte(P17_CA_L2_INIT_8, 0xFF);
    ScalerSetByte(P17_DA_L3_INIT_8, 0xFF);

    ScalerSetByte(P17_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P17_BA_L1_INIT_8, 0x00);
    ScalerSetByte(P17_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P17_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
}

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDFEInitialUnFlip2Lane(EnumDpLinkRate enumDpLinkRate)
{
    if((enumDpLinkRate == _DP_LINK_HBR2) &&
       ((GET_DP_RX0_PHY_CTS_FLG() == _TRUE) ||
        ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, _BIT7) == _BIT7) &&
         ((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x02) & (_BIT2 | _BIT1 | _BIT0)) == 0x03))))
    {
        // Tap Divider = 34 for TPS3
        ScalerSetByte(P17_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte(P17_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);

    // LE Max = 24, LE Initial = 16, Servo Initial = 16
    ScalerSetByte(P17_C2_L2_LIMIT_INIT, 0x80);
    ScalerSetByte(P17_D2_L3_LIMIT_INIT, 0x80);

    ScalerSetByte(P17_C3_L2_INIT_1, 0xD0);
    ScalerSetByte(P17_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 21
    ScalerSetByte(P17_C4_L2_INIT_2, 0x15);
    ScalerSetByte(P17_D4_L3_INIT_2, 0x15);

    // Tap1 Initial Value = 0
    ScalerSetByte(P17_C5_L2_INIT_3, 0x00);
    ScalerSetByte(P17_D5_L3_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte(P17_C6_L2_INIT_4, 0x00);
    ScalerSetByte(P17_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 28
    ScalerSetByte(P17_C9_L2_INIT_7, 0x1C);
    ScalerSetByte(P17_D9_L3_INIT_7, 0x1C);

    // Load Intial DFE Code
    ScalerSetByte(P17_CA_L2_INIT_8, 0xFF);
    ScalerSetByte(P17_DA_L3_INIT_8, 0xFF);

    ScalerSetByte(P17_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P17_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
}


//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDFEInitialFlip2Lane(EnumDpLinkRate enumDpLinkRate)
{
    if((enumDpLinkRate == _DP_LINK_HBR2) &&
       ((GET_DP_RX0_PHY_CTS_FLG() == _TRUE) ||
        ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, _BIT7) == _BIT7) &&
         ((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x02) & (_BIT2 | _BIT1 | _BIT0)) == 0x03))))
    {
        // Tap Divider = 34 for TPS3
        ScalerSetByte(P17_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte(P17_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);

    // LE Max = 24, LE Initial = 16, Servo Initial = 16
    ScalerSetByte(P17_A2_L0_LIMIT_INIT, 0x80);
    ScalerSetByte(P17_B2_L1_LIMIT_INIT, 0x80);

    ScalerSetByte(P17_A3_L0_INIT_1, 0xD0);
    ScalerSetByte(P17_B3_L1_INIT_1, 0xD0);

    // Tap0 Initial Value = 21
    ScalerSetByte(P17_A4_L0_INIT_2, 0x15);
    ScalerSetByte(P17_B4_L1_INIT_2, 0x15);

    // Tap1 Initial Value = 0
    ScalerSetByte(P17_A5_L0_INIT_3, 0x00);
    ScalerSetByte(P17_B5_L1_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte(P17_A6_L0_INIT_4, 0x00);
    ScalerSetByte(P17_B6_L1_INIT_4, 0x00);

    // Vth Initial Value = 28
    ScalerSetByte(P17_A9_L0_INIT_7, 0x1C);
    ScalerSetByte(P17_B9_L1_INIT_7, 0x1C);

    // Load Intial DFE Code
    ScalerSetByte(P17_AA_L0_INIT_8, 0xFF);
    ScalerSetByte(P17_BA_L1_INIT_8, 0xFF);

    ScalerSetByte(P17_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P17_BA_L1_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}
#endif

//--------------------------------------------------
// Description  : Check Valid Lane CDR
// Input Value  : None
// Output Value : True --> CDR Lock
//--------------------------------------------------
bit ScalerDpRx0CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
    CLR_DP_RX0_SIGNALDETECT_INT_HAPPENED();
#endif

    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            if(ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE0) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_TWO_LANE:

            if((ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE0) == _TRUE) &&
               (ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE1) == _TRUE))
            {
                return _TRUE;
            }

            break;

        case _DP_FOUR_LANE:
        default:

            if((ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE0) == _TRUE) &&
               (ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE1) == _TRUE) &&
               (ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE2) == _TRUE) &&
               (ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE3) == _TRUE))
            {
                return _TRUE;
            }

            break;
    }

#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
    if(GET_DP_RX0_SIGNALDETECT_INT_HAPPENED() == _TRUE)
    {
        return _TRUE;
    }
    else
#endif
    {
        DebugMessageRx0("7. wuzanne test : DP CDR Unlock", 0);

        return _FALSE;
    }
}

//--------------------------------------------------
// Description : check DP CDR locked or unlocked
// Input Value  : DP Lane
// Output Value : True --> locked; False --> unlocked
//--------------------------------------------------
bit ScalerDpRx0MeasureLaneCDRClk(BYTE ucDpLinkRate, BYTE ucDpRx0LaneNumber)
{
    WORD usCDRClockCount = 0;

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            if((abs(g_pusDpRx0ClockCount[ucDpRx0LaneNumber] - 0x2710)) > (0x2710 >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_HBR:

            if((abs(g_pusDpRx0ClockCount[ucDpRx0LaneNumber] - 0x1388)) > (0x1388 >> 4))
            {
                return _TRUE;
            }

            break;

        default:
        case _DP_LINK_RBR:

            if((abs(g_pusDpRx0ClockCount[ucDpRx0LaneNumber] - 0xBB8)) > (0xBB8 >> 4))
            {
                return _TRUE;
            }

            break;
    }

    // Select Measure CDR Clock & XTAL 27M Count 1000 Times
    ScalerSetByte(PB_50_DP_SIG_DET_0, 0x23);

    // Select CDR Lane
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), ucDpRx0LaneNumber);

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

    if(abs(g_pusDpRx0ClockCount[ucDpRx0LaneNumber] - usCDRClockCount) > (g_pusDpRx0ClockCount[ucDpRx0LaneNumber] >> 7))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Valid Lane Alignment
// Input Value  : None
// Output Value : True --> Align
//--------------------------------------------------
bit ScalerDpRx0AlignCheck(void)
{
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)

    if(GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE)
    {
        if(GET_DP_RX0_SOURCE_TYPE_JUDGE() == _FALSE)
        {
#if(_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON)
            if(ScalerDpRx0LaneValidCheck() == _FALSE)
            {
                return _TRUE;
            }
#else
            return _TRUE;
#endif
        }
    }

#endif

    if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F) == _DP_ONE_LANE)
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
// Description : check DP 8b/10b Decode Error
// Input Value  : None
// Output Value : True --> ok, False --> 8b/10b Decode Error
//--------------------------------------------------
bit ScalerDpRx0DecodeCheck(void)
{
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)

    if(GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE)
    {
        if(GET_DP_RX0_SOURCE_TYPE_JUDGE() == _FALSE)
        {
#if(_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON)
            if(ScalerDpRx0LaneValidCheck() == _FALSE)
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

        switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                if(((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                {
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if(((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT1 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2))) &&
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

    DebugMessageRx0("7. DP 8b/10b Decode Error", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description : check DFE Coef
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx0DFECheck(void)
{
    if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_FOUR_LANE:

            // Read Lane2 DFE
            ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0C1B)
            {
                DebugMessageRx0("7. Lane2 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane3 DFE
            ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0C1B)
            {
                DebugMessageRx0("7. Lane3 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0C1B)
            {
                DebugMessageRx0("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0C1B)
            {
                DebugMessageRx0("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0C1B)
            {
                DebugMessageRx0("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0C1B)
            {
                DebugMessageRx0("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0C1B)
            {
                DebugMessageRx0("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : Initial Signal check
// Input Value  : DP Link Rate
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue)
{
    ucDpLEQScanValue = ucDpLEQScanValue;

    // [5] ldo_en_u3_a1 = 1'b1 --> CMU 1.1V LDO Enable
    // [1] ldo_en_u3_a0 = 1'b1 --> CMU 1.1V LDO Enable
    ScalerSetBit(P1A_30_COMBO_USB_00, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));

    // Delay 50us for LDO Power Stable
    DELAY_XUS(50);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

    DebugMessageRx0("Signal Detection Initial_Pinassignment", ScalerTypeCRx0PdGetPinAssignment());
    DebugMessageRx0("Signal Detection Initial_Orientation", GET_CC_RX0_ORIENTATION());

    // Main-Link Lane Setting Start
    if(ScalerTypeCRx0PdGetPinAssignment() != _TYPE_C_PIN_ASSIGNMENT_E)
    {
        // Pin Assignment C/D PN Swap
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, _D0_DP_PCB_LANE3_PN_SWAP << 7);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, _D0_DP_PCB_LANE2_PN_SWAP << 6);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, _D0_DP_PCB_LANE1_PN_SWAP << 5);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, _D0_DP_PCB_LANE0_PN_SWAP << 4);
    }
    else
    {
        // Pin Assignment E PN Swap
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, (!_D0_DP_PCB_LANE3_PN_SWAP) << 7);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, (!_D0_DP_PCB_LANE2_PN_SWAP) << 6);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, (!_D0_DP_PCB_LANE1_PN_SWAP) << 5);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, (!_D0_DP_PCB_LANE0_PN_SWAP) << 4);
    }

    SET_DP_RX0_PCB_LANE0_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT7) >> 7);
    SET_DP_RX0_PCB_LANE1_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT6) >> 6);
    SET_DP_RX0_PCB_LANE2_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT5) >> 5);
    SET_DP_RX0_PCB_LANE3_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT4) >> 4);

    switch(ScalerTypeCRx0PdGetPinAssignment())
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE1_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE0_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE2_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE0_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);
            }

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            break;

        case _TYPE_C_PIN_ASSIGNMENT_D:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE1_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE0_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE2_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);

                SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
                SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
                SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
                SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE0_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);

                SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
                SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
                SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
                SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_E:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE2_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE3_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE1_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE0_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE1_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE3_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE2_MAPPING);
            }

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            break;

        default:
        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            // DP Lane Swap Setting
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE1_MAPPING << 2);
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            break;
    }

    if(ScalerTypeCRx0PdGetPinAssignment() == _TYPE_C_PIN_ASSIGNMENT_D)
    {
        if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_FLIP)
        {
            ///////////////////////////
            // RX CMU EN & Mac Power //
            ///////////////////////////

            // [7:6] SEL_Rate Initial
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), 0x00);

            // [5:4] LANE_EN = 2'b00 --> Disable LANE_EN
            // [1:0] CDR_EN = 2'b00 --> Disable CDR_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

            // [5:4] Enable LANE_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

            // [3:0] Enable Lane0~3 CDR_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            // [3:0] Enable Foreground Offset Calibration
            ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));


            ////////////////
            // LE Setting //
            ////////////////

            // [7:6] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
            // [5] edge_det_mode = 1 --> Edge Lag Data
            // [4] transition_only = 1 --> Only Transition Bit is Effective
            // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
            // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
            ScalerSetByte(P17_E0_MODE_TIMER, 0xB2);

            // LE Max = 24, LE Initial = 18, Servo Initial = 16
            ScalerSetByte(P17_A2_L0_LIMIT_INIT, 0x82);
            ScalerSetByte(P17_B2_L1_LIMIT_INIT, 0x82);
            ScalerSetByte(P17_A3_L0_INIT_1, 0xD0);
            ScalerSetByte(P17_B3_L1_INIT_1, 0xD0);

            // Load Intial DFE Code
            ScalerSetByte(P17_AA_L0_INIT_8, 0x80);
            ScalerSetByte(P17_BA_L1_INIT_8, 0x80);

            ScalerSetByte(P17_AA_L0_INIT_8, 0x00);
            ScalerSetByte(P17_BA_L1_INIT_8, 0x00);

            // DFE Loop Normal
            ScalerSetBit(P17_EF_RESET_1, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P17_EF_RESET_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Disable All Adaptation Loop
            ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
            ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);


            /////////////////////////////////
            // Frequency Parameter Setting //
            /////////////////////////////////

            switch(ucDpLinkRate)
            {
                case _DP_LINK_HBR2:

                    // [3:1] LE_lowgain_highboost = 3'b110
                    // [0] sel_dyn_std = 0 --> Dyn DFF
                    ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

                    // reg_le_rlsel / reg_le_isel = 5.4GHz
                    ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

                    break;

                case _DP_LINK_HBR:

                    // [3:1] LE_lowgain_highboost = 3'b100
                    // [0] sel_dyn_std = 0 --> Dyn DFF
                    ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

                    // reg_le_rlsel / reg_le_isel = 2.7GHz
                    ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

                    break;

                case _DP_LINK_RBR:
                default:

                    // [3:1] LE_lowgain_highboost = 3'b000
                    // [0] sel_dyn_std = 1 --> Std DFF
                    ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    // reg_le_rlsel / reg_le_isel = 1.62GHz
                    ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

                    break;
            }
        }
        else
        {
            ///////////////////////////
            // RX CMU EN & Mac Power //
            ///////////////////////////

            // [1:0] SEL_Rate Initial
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), 0x00);

            // [7:6] LANE_EN = 2'b00 --> Disable LANE_EN
            // [3:2] CDR_EN = 2'b00 --> Disable CDR_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

            // [5:4] Enable LANE_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6));

            // [3:0] Enable Lane0~3 CDR_EN
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2), _BIT2);
            ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            // [3:0] Enable Foreground Offset Calibration
            ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));


            ////////////////
            // LE Setting //
            ////////////////

            // [7:6] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
            // [5] edge_det_mode = 1 --> Edge Lag Data
            // [4] transition_only = 1 --> Only Transition Bit is Effective
            // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
            // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
            ScalerSetByte(P17_E0_MODE_TIMER, 0xB2);

            // LE Max = 24, LE Initial = 18, Servo Initial = 16
            ScalerSetByte(P17_C2_L2_LIMIT_INIT, 0x82);
            ScalerSetByte(P17_D2_L3_LIMIT_INIT, 0x82);
            ScalerSetByte(P17_C3_L2_INIT_1, 0xD0);
            ScalerSetByte(P17_D3_L3_INIT_1, 0xD0);

            // Load Intial DFE Code
            ScalerSetByte(P17_CA_L2_INIT_8, 0x80);
            ScalerSetByte(P17_DA_L3_INIT_8, 0x80);

            ScalerSetByte(P17_CA_L2_INIT_8, 0x00);
            ScalerSetByte(P17_DA_L3_INIT_8, 0x00);

            // DFE Loop Normal
            ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // Disable All Adaptation Loop
            ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
            ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);


            /////////////////////////////////
            // Frequency Parameter Setting //
            /////////////////////////////////

            switch(ucDpLinkRate)
            {
                case _DP_LINK_HBR2:

                    // [7:5] LE_lowgain_highboost = 3'b110
                    // [4] sel_dyn_std = 0 --> Dyn DFF
                    ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

                    // reg_le_rlsel / reg_le_isel = 5.4GHz
                    ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

                    break;

                case _DP_LINK_HBR:

                    // [7:5] LE_lowgain_highboost = 3'b100
                    // [4] sel_dyn_std = 0 --> Dyn DFF
                    ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

                    // reg_le_rlsel / reg_le_isel = 2.7GHz
                    ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

                    break;

                case _DP_LINK_RBR:
                default:

                    // [7:5] LE_lowgain_highboost = 3'b000
                    // [4] sel_dyn_std = 1 --> Std DFF
                    ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

                    // reg_le_rlsel / reg_le_isel = 1.62GHz
                    ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

                    break;
            }
        }
    }
    else
#endif
    {
        ///////////////////////////
        // RX CMU EN & Mac Power //
        ///////////////////////////

        // [7:6] SEL_Rate Initial
        ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), 0x00);

        // [1:0] SEL_Rate Initial
        ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), 0x00);

        // [7:4] LANE_EN = 4'b0000 --> Disable LANE_EN
        // [3:0] CDR_EN = 4'b0000 --> Disable CDR_EN
        ScalerSetByte(P1A_22_DP_RX_02, 0x00);

        // [7:4] Enable LANE_EN
        ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // [3:0] Enable Lane0~3 CDR_EN
        ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // [4:3] DP MAC Select Four Lane
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

        // [3:0] Enable Foreground Offset Calibration
        ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));


        ////////////////
        // LE Setting //
        ////////////////

        // [7:6] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
        // [5] edge_det_mode = 1 --> Edge Lag Data
        // [4] transition_only = 1 --> Only Transition Bit is Effective
        // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
        // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
        ScalerSetByte(P17_E0_MODE_TIMER, 0xB2);

        // LE Max = 24, LE Initial = 18, Servo Initial = 16
        ScalerSetByte(P17_A2_L0_LIMIT_INIT, 0x82);
        ScalerSetByte(P17_B2_L1_LIMIT_INIT, 0x82);
        ScalerSetByte(P17_C2_L2_LIMIT_INIT, 0x82);
        ScalerSetByte(P17_D2_L3_LIMIT_INIT, 0x82);
        ScalerSetByte(P17_A3_L0_INIT_1, 0xD0);
        ScalerSetByte(P17_B3_L1_INIT_1, 0xD0);
        ScalerSetByte(P17_C3_L2_INIT_1, 0xD0);
        ScalerSetByte(P17_D3_L3_INIT_1, 0xD0);

        // Load Intial DFE Code
        ScalerSetByte(P17_AA_L0_INIT_8, 0x80);
        ScalerSetByte(P17_BA_L1_INIT_8, 0x80);
        ScalerSetByte(P17_CA_L2_INIT_8, 0x80);
        ScalerSetByte(P17_DA_L3_INIT_8, 0x80);

        ScalerSetByte(P17_AA_L0_INIT_8, 0x00);
        ScalerSetByte(P17_BA_L1_INIT_8, 0x00);
        ScalerSetByte(P17_CA_L2_INIT_8, 0x00);
        ScalerSetByte(P17_DA_L3_INIT_8, 0x00);

        // DFE Loop Normal
        ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Disable All Adaptation Loop
        ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);


        /////////////////////////////////
        // Frequency Parameter Setting //
        /////////////////////////////////

        switch(ucDpLinkRate)
        {
            case _DP_LINK_HBR2:

                // [7:5][3:1] LE_lowgain_highboost = 3'b110
                // [4][0] sel_dyn_std = 0 --> Dyn DFF
                ScalerSetByte(P1A_14_COMBO_RX_04, 0xCC);

                // reg_le_rlsel / reg_le_isel = 5.4GHz
                ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));
                ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

                break;

            case _DP_LINK_HBR:

                // [7:5][3:1] LE_lowgain_highboost = 3'b100
                // [4][0] sel_dyn_std = 0 --> Dyn DFF
                ScalerSetByte(P1A_14_COMBO_RX_04, 0x88);

                // reg_le_rlsel / reg_le_isel = 2.7GHz
                ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
                ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

                break;

            case _DP_LINK_RBR:
            default:

                // [7:5][3:1] LE_lowgain_highboost = 3'b000
                // [4][0] sel_dyn_std = 1 --> Std DFF
                ScalerSetByte(P1A_14_COMBO_RX_04, 0x11);

                // reg_le_rlsel / reg_le_isel = 1.62GHz
                ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
                ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

                break;
        }
    }
}
//--------------------------------------------------
// Description  : DP Display Format Generator Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx0DisplayFormatSetting(void)
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
        ulVBs2BsCount = g_stDpRx0LinkInfo.ulVBsToBsCountN;
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
        SET_DP_RX0_MEASURE_POP_UP();

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
        usDpVtotal = ulVBs2BsCount * (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2) / usHBs2BsCount * 1000 / _GDI_CLK_KHZ;

        ulDpMvidValue = ((((DWORD)ScalerGetByte(PB6_1A_MSA_MVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1B_MSA_MVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1C_MSA_MVID_2)));

        ulDpNvidValue = ((((DWORD)ScalerGetByte(PB6_1D_MSA_NVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1E_MSA_NVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1F_MSA_NVID_2)));

        // [5] ln_ck_sel = 1'b1 -> CDR Clock
        // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

        // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
        ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

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
        WORD usDpHtotal = (DWORD)usHBs2BsCount * (GET_INPUT_PIXEL_CLK() / 10) / (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2);

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

        PDATA_WORD(0) = GET_DPRX0_BS_TO_HS_DELAY(usDpHtotal);

        // Set HBs2Bs
        ScalerSetByte(PB5_38_BS2HS_0, pData[0]);
        ScalerSetByte(PB5_39_BS2HS_1, pData[1]);

        ScalerDpRx0InterlaceCheck(&usDpVtotal, &ucOddFlg);

        // Set DE Only Mode Vsync Front Porch
        ScalerSetByte(PB5_40_VS_FRONT_PORCH, GET_DP_RX0_VFRONT_PORCH());

        // Set DE Only Mode
        ScalerSetBit(PB5_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), _BIT4);

        // Choose Frame start BE to Reset FIFO
        ScalerSetBit(PB5_20_PG_CTRL_0, ~_BIT5, 0x00);

        // Set DP FREESYNC Mode Enable
        ScalerSetBit(PB5_F0_DP_RSV0, ~_BIT0, _BIT0);

        ScalerDpRx0SetFREESYNCMsaForLut(usDpHtotal);

        DebugMessageRx0("FREESYNC Mode Enabled!!", ScalerGetByte(PB5_30_DPF_CTRL_0));
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

        DebugMessageRx0("###Origin usVTotal###", usDpVtotal);

        if(ScalerDpRx0InterlaceCheck(&usDpVtotal, &ucOddFlg) == _TRUE) // Interlace
        {
            DebugMessageRx0("7. IIIIIInterLace Vtotal", usDpVtotal);
        }
        else // Progressive
        {
            DebugMessageRx0("7. PPPPProgressive", 0);
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
        PDATA_WORD(0) = usDpVtotal - PDATA_WORD(2) - GET_DP_RX0_VFRONT_PORCH();

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
            ScalerSetBit(PB5_35_OVBLK2VS_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayOdd >> 16));
            ScalerSetByte(PB5_36_OVBLK2VS_M, (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayOdd >> 8));
            ScalerSetByte(PB5_37_OVBLK2VS_L, (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayOdd >> 0));

            // Set Even Field BS to VS Delay
            ScalerSetBit(PB5_32_EVBLK2VS_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayEven >> 16));
            ScalerSetByte(PB5_33_EVBLK2VS_M, (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayEven >> 8));
            ScalerSetByte(PB5_34_EVBLK2VS_L, (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayEven >> 0));
        }
        else
#endif
        {
            ulBs2VsDelay = ScalerDpRx0GetBStoVSDelay();

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
                ulBs2VsDelay += ((((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00)) * 270UL) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(5)) / 256 / 2;
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

        DebugMessageRx0("FREESYNC Mode Disabled", ScalerGetByte(PB5_30_DPF_CTRL_0));
    }

    // Double Buffer to Apply Display Format Setting (RL6492 has no double buffer for display format setting)
    // ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT6, _BIT6);

    ScalerDpRx0VideoSetting();

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Stream Clk PLL Setting
// Input Value  : None
// Output Value : True --> Stream CLK Regen. ok
//--------------------------------------------------
bit ScalerDpRx0StreamClkRegenerate(void)
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
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

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
        if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = 0x4E20;
        }
        else if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
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
        ucplln = ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00);
    }

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        ulVBs2BsCount = g_stDpRx0LinkInfo.ulVBsToBsCountN;
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
        SET_DP_RX0_MEASURE_POP_UP();

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

    DebugMessageRx0("Stream Clk", ulStreamClkValue);

    // Get DPLL parameter
    // If "HW Input Clock Max > ulStreamClkValue > 270Mhz"
    if((_HW_DP_MAC0_INPUT_CLOCK_MAX > ulStreamClkValue) && (ulStreamClkValue >= 270000000))
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

    DebugMessageRx0("modified M code", ulpllm);

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

    DebugMessageRx0("P Code", ul2ndPCode);

#if(_DP_MN_PLL_FREQUENCY_TREND == _PLL_FREQ_DOWN)
    lOffsetValue = 0x7FFFF - lOffsetValue + 1;
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        lOffsetValue = g_stDpRx0LinkInfo.lStreamClockOffset;
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

        DebugMessageRx0("1st PE Loop", pData[0]);
        DebugMessageRx0("1st PE Max Record", ScalerGetByte(PB5_B6_MN_SCLKG_TRK_VS_PE));
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

        ScalerDpRx0HSActiveTrackingMode(_DP_HS_TRACKING_FW_MODE);

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

    DebugMessageRx0("2nd PE Loop", pData[0]);
    DebugMessageRx0("2nd PE Max Record", ScalerGetByte(PB5_B6_MN_SCLKG_TRK_VS_PE));

    // Check if DPF Mode is DE Mode
    if(ScalerGetBit(PB5_30_DPF_CTRL_0, (_BIT5 | _BIT4)) == _BIT4)
    {
#if(_DP_DE_ONLY_MODE_WITH_FULL_LAST_LINE_SUPPORT == _ON)
        if(ScalerGlobalGetIDCode() >= _RL6492_VER_C_ID_CODE)
        {
            WORD usHBs2BsCount = ((((WORD)ScalerGetByte(PB5_5B_MN_MEAS_HLN_M)) << 8) | (ScalerGetByte(PB5_5C_MN_MEAS_HLN_L)));

            // Half BS delay counted by GDI_CLK = HBs2BsCount / (1/2 * Link_clk) * GDI_clk / 2
            PDATA_WORD(0) = usHBs2BsCount * (_GDI_CLK_KHZ / 1000) / (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 27);

            ScalerSetBit(PB5_C2_HS_TRACKING_NEW_MODE1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte(PB5_C3_HS_TRACKING_NEW_MODE2, pData[1]);

            ScalerDpRx0HSActiveTrackingMode(_DP_HS_TRACKING_FW_MODE);

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
bit ScalerDpRx0FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition)
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
        ScalerDpRx0SetNoVideoStreamIRQ(_ENABLE);
    }

    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x05, _BIT0) == 0x00)
    {
        // Set DP Receive Port0 In Sync
        ScalerDpRx0SinkStatusSet(_DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : HDCP Reset For Dp Rx0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPBlockReset(void)
{
#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    if(GET_REG_DP_RX0_MAC_ASSIGNED() == _TRUE)
#endif
    {
        // Reset HDCP Block
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
    }

    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x29, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x2A, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x2B, 0x00);

    for(pData[0] = 0; pData[0] < 20; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x14 + pData[0]), 0x00);
    }

    for(pData[0] = 0; pData[0] < 15; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), 0x00);
    }

    SET_DP_RX0_AUX_MANUAL_MODE();

    // Clear Aksv
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x07, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x08, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x09, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0A, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0B, 0x00);

    SET_DP_RX0_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Check DP Link Integrity
// Input Value  : None
// Output Value : FALSE => DP Link Integrity Fail
//--------------------------------------------------
bit ScalerDpRx0HdcpCheck(void)
{
    // Check for HDCP Block work in 1.4
    if(GET_DP_RX0_HDCP_MODE() == _HDCP_14)
    {
        if((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x07) == 0x00) &&
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x08) == 0x00) &&
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x09) == 0x00) &&
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0A) == 0x00) &&
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0B) == 0x00))
        {
            return _TRUE;
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(GET_DP_RX0_HDCP2_AUTHENTICATION_DONE() == _FALSE)
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
    if((GET_DP_RX0_HDCP_MODE() == _HDCP_14) && ((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x11) & _BIT2) == 0x00))
    {
        return _FALSE;
    }

    if((GET_DP_RX0_HDCP_MODE() == _HDCP_14) && (ScalerDpRx0HdcpMeasureCheck() == _TRUE))
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
bit ScalerDpRx0HdcpReAuthStatusCheck(void)
{
    if(GET_DP_RX0_HDCP_MODE() == _HDCP_14)
    {
        if((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) || (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) || (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00))
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
bit ScalerDpRx0HdcpMeasureCheck(void)
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
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

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
        if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = 0x4E20;
        }
        else if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
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

    DebugMessageRx0("Current Link Clk", ulLinkClk);

    // Start to Measure Vertical BS to BS Counter by GDI Clock
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB5_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The result
    SET_DP_RX0_MEASURE_POP_UP();

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
void ScalerDpRx0CpIRQ(EnumDpRxBStatusType enumBStatusType)
{
    switch(enumBStatusType)
    {
        case _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL:

            if(GET_DP_RX0_HDCP_MODE() == _HDCP_14)
            {
                // Reset HDCP Block
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

                SET_DP_RX0_AUX_MANUAL_MODE();

                // Clear Aksv
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x07, 0x00);
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x08, 0x00);
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x09, 0x00);
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0A, 0x00);
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0B, 0x00);

                SET_DP_RX0_AUX_AUTO_MODE();

                // Set B Status
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x29) | enumBStatusType));
            }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            else
            {
                // Disable HDCP 2.2 Module
                SET_DP_RX0_HDCP_MODE(_HDCP_14);

                // Disable HDCP2.2 Auth. Done
                ScalerSetBit(PB_20_HDCP_DEBUG, ~_BIT4, 0x00);

                // Reset HDCP Block
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

                ScalerDpRx0SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx0GetDpcdInfo(0x06, 0x94, 0x93) | _BIT4));

                // Clear Authentication Done Flag
                CLR_DP_RX0_HDCP2_AUTHENTICATION_DONE();
            }
#endif
            break;

        case _DP_HDCP_BSTATUS_REAUTH_REQ:

            ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x29) | _BIT3));

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_RXSTATUS_REAUTH_REQ:

            ScalerDpRx0SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx0GetDpcdInfo(0x06, 0x94, 0x93) | _BIT3));

            break;
#endif

        case _DP_HDCP_BSTATUS_V_READY:
        case _DP_HDCP_BSTATUS_R0_AVAILABLE:

            // Set B Status
            ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x29) | enumBStatusType));

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpRx0SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx0GetDpcdInfo(0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;
#endif

        default:

            break;
    }

    // Link Status CPIRQ Flag
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x01) | _BIT2));

    ScalerDpRx0HpdIrqAssert();
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : None
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpRx0HdcpCheckValid(void)
{
    if(GET_DP_RX0_HDCP_MODE() == _HDCP_14)
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
bit ScalerDpRx0HdcpCheckEnabled(void)
{
    if(GET_DP_RX0_HDCP_MODE() == _HDCP_14)
    {
        if(ScalerGetBit(PB_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5))
        {
            if((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) ||
               (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
               (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) ||
               (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
               (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00))
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
void ScalerDpRx0PhyCtsTp1SetPhy(EnumDpNFCodeRef enumDpNFCodeRef)
{
    // [0] hd_dp_sel = 1'b0 --> Select DP
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT0, 0x00);

    // [4] Disable Comma Detection
    ScalerSetBit(PB_05_SAMPLE_EDGE, ~_BIT4, _BIT4);

    // [5] Disable De-Scrambling
    ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    // [2] Disable Enhancement Control Mode
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);

    // [1:0] DP Mac Clock Selection
    ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), (g_ucDpRx0PhyCtsCtrl & 0x30) >> 4);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

    // Main-Link Lane Setting Start
    if(ScalerTypeCRx0PdGetPinAssignment() != _TYPE_C_PIN_ASSIGNMENT_E)
    {
        // Pin Assignment C/D PN Swap
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, _D0_DP_PCB_LANE3_PN_SWAP << 7);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, _D0_DP_PCB_LANE2_PN_SWAP << 6);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, _D0_DP_PCB_LANE1_PN_SWAP << 5);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, _D0_DP_PCB_LANE0_PN_SWAP << 4);
    }
    else
    {
        // Pin Assignment E PN Swap
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, (!_D0_DP_PCB_LANE3_PN_SWAP) << 7);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, (!_D0_DP_PCB_LANE2_PN_SWAP) << 6);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, (!_D0_DP_PCB_LANE1_PN_SWAP) << 5);
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, (!_D0_DP_PCB_LANE0_PN_SWAP) << 4);
    }

    SET_DP_RX0_PCB_LANE0_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT7) >> 7);
    SET_DP_RX0_PCB_LANE1_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT6) >> 6);
    SET_DP_RX0_PCB_LANE2_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT5) >> 5);
    SET_DP_RX0_PCB_LANE3_PN_SWAP(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT4) >> 4);

    switch(ScalerTypeCRx0PdGetPinAssignment())
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE1_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE0_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE2_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE0_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);
            }

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            ScalerDpRx0PhyCtsTp1SetPhy4Lane(enumDpNFCodeRef);

            break;

        case _TYPE_C_PIN_ASSIGNMENT_D:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE1_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE0_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE2_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);

                SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
                SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
                SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
                SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

                ScalerDpRx0PhyCtsTp1SetPhyUnFlip2Lane(enumDpNFCodeRef);
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE0_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);

                SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
                SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
                SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
                SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

                ScalerDpRx0PhyCtsTp1SetPhyFlip2Lane(enumDpNFCodeRef);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_E:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE2_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE3_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE1_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE0_MAPPING << 6);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE1_MAPPING << 4);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE3_MAPPING << 2);
                ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE2_MAPPING);
            }

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            ScalerDpRx0PhyCtsTp1SetPhy4Lane(enumDpNFCodeRef);

            break;

        default:
        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            // DP Lane Swap Setting
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE1_MAPPING << 2);
            ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            ScalerDpRx0PhyCtsTp1SetPhy4Lane(enumDpNFCodeRef);

            break;
    }

#else

    // DP Lane Swap Setting
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_LANE3 << 6);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_LANE2 << 4);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_LANE1 << 2);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // DP Lane PN Swap Setting
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, GET_DP_RX0_PCB_LANE3_PN_SWAP() << 7);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, GET_DP_RX0_PCB_LANE2_PN_SWAP() << 6);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, GET_DP_RX0_PCB_LANE1_PN_SWAP() << 5);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, GET_DP_RX0_PCB_LANE0_PN_SWAP() << 4);

    ScalerDpRx0PhyCtsTp1SetPhy4Lane(enumDpNFCodeRef);

#endif
}


//--------------------------------------------------
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyCtsTp1SetPhy4Lane(EnumDpNFCodeRef enumDpNFCodeRef)
{
    BYTE ucIcp = 0;

    // LDO_en for Lane1,3
    ScalerSetBit(P1A_30_COMBO_USB_00, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));

    // Enable Lane1,3 1.1V LDO Tracking
    ScalerSetBit(P1A_30_COMBO_USB_00, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

    // [7:4] LANE_EN = 4'b0000 --> Disable LANE_EN
    // [3:0] CDR_EN = 4'b0000 --> Disable CDR_EN
    ScalerSetByte(P1A_22_DP_RX_02, 0x00);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
    {
        case 0x30:

            // [7] Enable Lane3 Rx_en
            ScalerSetBit(P1A_22_DP_RX_02, ~_BIT7, _BIT7);

            // [3] Enable Lane3 CDR_en
            ScalerSetBit(P1A_22_DP_RX_02, ~_BIT3, _BIT3);

            break;

        case 0x20:

            // [6] Enable Lane2 Rx_en
            ScalerSetBit(P1A_22_DP_RX_02, ~_BIT6, _BIT6);

            // [2] Enable Lane2 CDR_en
            ScalerSetBit(P1A_22_DP_RX_02, ~_BIT2, _BIT2);

            break;

        case 0x10:

            // [5] Enable Lane1 Rx_en
            ScalerSetBit(P1A_22_DP_RX_02, ~_BIT5, _BIT5);

            // [1] Enable Lane1 CDR_en
            ScalerSetBit(P1A_22_DP_RX_02, ~_BIT1, _BIT1);

            break;

        default:
        case 0x00:

            // [4] Enable Lane0 Rx_en
            ScalerSetBit(P1A_22_DP_RX_02, ~_BIT4, _BIT4);

            // [0] Enable Lane0 CDR_en
            ScalerSetBit(P1A_22_DP_RX_02, ~_BIT0, _BIT0);

            break;
    }

    // [4:3] DP Mac Select One Lane
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetByte(P1C_4C_READY_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte(P1C_4D_READY_TIMER_2, 0x0F);

    // [4:2] reg_vcm_ctrl_op_l1 = 3'b101 --> 600mV
    ScalerSetBit(P1A_2C_DP_RX_12, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [4:2] reg_vcm_ctrl_op_l3 = 3'b101 --> 600mV
    ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [3:0] Disable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // Disable DFE Adaptation
    ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);

    // LE Max = 24, LE Initial = 24
    ScalerSetByte(P17_A2_L0_LIMIT_INIT, 0x88);
    ScalerSetByte(P17_B2_L1_LIMIT_INIT, 0x88);
    ScalerSetByte(P17_C2_L2_LIMIT_INIT, 0x88);
    ScalerSetByte(P17_D2_L3_LIMIT_INIT, 0x88);
    ScalerSetByte(P17_A3_L0_INIT_1, 0xD0);
    ScalerSetByte(P17_B3_L1_INIT_1, 0xD0);
    ScalerSetByte(P17_C3_L2_INIT_1, 0xD0);
    ScalerSetByte(P17_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 26
    ScalerSetByte(P17_A4_L0_INIT_2, 0x1A);
    ScalerSetByte(P17_B4_L1_INIT_2, 0x1A);
    ScalerSetByte(P17_C4_L2_INIT_2, 0x1A);
    ScalerSetByte(P17_D4_L3_INIT_2, 0x1A);

    // Tap1 Initial Value = 0
    ScalerSetByte(P17_A5_L0_INIT_3, 0x00);
    ScalerSetByte(P17_B5_L1_INIT_3, 0x00);
    ScalerSetByte(P17_C5_L2_INIT_3, 0x00);
    ScalerSetByte(P17_D5_L3_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte(P17_A6_L0_INIT_4, 0x00);
    ScalerSetByte(P17_B6_L1_INIT_4, 0x00);
    ScalerSetByte(P17_C6_L2_INIT_4, 0x00);
    ScalerSetByte(P17_D6_L3_INIT_4, 0x00);

    // Load Intial DFE Code
    ScalerSetByte(P17_AA_L0_INIT_8, 0xFF);
    ScalerSetByte(P17_BA_L1_INIT_8, 0xFF);
    ScalerSetByte(P17_CA_L2_INIT_8, 0xFF);
    ScalerSetByte(P17_DA_L3_INIT_8, 0xFF);
    ScalerSetByte(P17_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P17_BA_L1_INIT_8, 0x00);
    ScalerSetByte(P17_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P17_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(g_ucDpRx0PhyCtsCtrl & 0xC0)
    {
        case 0x80:

            // [7:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 900M/v in Each Lane
            ScalerSetByte(P1A_03_COMBO_03, 0x55);

            // [7:4] en_half_pf = 1 --> Half Rate PD for High Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // [6:4][2:0] sel_cont3 = 3'b010 --> BBPD UP/DN Sync
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // [4][0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~(_BIT4 | _BIT0), 0x00);

            // [7:5][3:1] LE_lowgain_highboost = 3'b110
            // [4][0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetByte(P1A_14_COMBO_RX_04, 0xCC);

            // [7:6] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), 0x00);

            // [1:0] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_sel_cdr_res = 2K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x50);
            ScalerSetByte(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 13.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xCC);
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xCC);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:0] reg_fld_xtal_en = 4'b1111 --> Using 27M Xtal
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (50/500 = 2*(27M/540M))
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetByte(P1C_63_DP_FLD_21, 0x31);
                ScalerSetByte(P1C_64_DP_FLD_22, 0x31);
                ScalerSetByte(P1C_65_DP_FLD_23, 0x31);
                ScalerSetByte(P1C_66_DP_FLD_24, 0x31);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
                ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);
            }
            else
            {
                // [3:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte(P1C_64_DP_FLD_22, 0xF3);
                ScalerSetByte(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
                ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;

        case 0x40:

            // [7:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetByte(P1A_03_COMBO_03, 0x00);

            // [7:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [6:4][2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // [4][0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~(_BIT4 | _BIT0), 0x00);

            // [7:5][3:1] LE_lowgain_highboost = 3'b100
            // [4][0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetByte(P1A_14_COMBO_RX_04, 0x88);

            // [7:6] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT6);

            // [1:0] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 8K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x50);
            ScalerSetByte(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 16.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xDD);
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xDD);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:0] reg_fld_xtal_en = 4'b1111 --> Using 27M Xtal
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (100/500 = 2*(27M/270M))
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetByte(P1C_63_DP_FLD_21, 0x63);
                ScalerSetByte(P1C_64_DP_FLD_22, 0x63);
                ScalerSetByte(P1C_65_DP_FLD_23, 0x63);
                ScalerSetByte(P1C_66_DP_FLD_24, 0x63);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
                ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);
            }
            else
            {
                // [3:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)); // ref_div_cnt set MSB=1
                ScalerSetByte(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte(P1C_64_DP_FLD_22, 0xF3);
                ScalerSetByte(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)); // cdr_div_cnt set MSB=1
                ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
                ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;

        default:
        case 0x00:

            // [7:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetByte(P1A_03_COMBO_03, 0x00);

            // [7:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [6:4][2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // [4][0] highboost_for_rbr = 1 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

            // [7:5][3:1] LE_lowgain_highboost = 3'b000
            // [4][0] sel_dyn_std = 1 --> Std DFF
            ScalerSetByte(P1A_14_COMBO_RX_04, 0x11);

            // [7:6] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT7);

            // [1:0] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT1);

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 6K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x70);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x70);
            ScalerSetByte(P1C_53_DP_FLD_5, 0x70);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x70);

            // reg_fld_cdr_cp Icp = 19.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xEE);
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xEE);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:0] reg_fld_xtal_en = 4'b1111 --> Using 27M Xtal
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (50/150 = 2*(27M/162M))
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetByte(P1C_63_DP_FLD_21, 0x31);
                ScalerSetByte(P1C_64_DP_FLD_22, 0x31);
                ScalerSetByte(P1C_65_DP_FLD_23, 0x31);
                ScalerSetByte(P1C_66_DP_FLD_24, 0x31);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetByte(P1C_68_DP_FLD_26, 0x96);
                ScalerSetByte(P1C_69_DP_FLD_27, 0x96);
                ScalerSetByte(P1C_6A_DP_FLD_28, 0x96);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0x96);
            }
            else
            {
                // [3:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte(P1C_64_DP_FLD_22, 0xF3);
                ScalerSetByte(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
                ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;
    }

    // Backup Icp for CDR lock
    ucIcp = ScalerGetByte(P1C_5D_DP_FLD_15);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P1C_2E_FORE_OFFSET_K_8, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_36_FORE_OFFSET_K_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_3E_FORE_OFFSET_K_24, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_46_FORE_OFFSET_K_32, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable Foreground Offset Calibration
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    //////////////
    // FLD Band //
    //////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetByte(P1C_50_DP_FLD_2, 0xFF);
    ScalerSetByte(P1C_50_DP_FLD_2, 0x0F);

    // [3:0] reg_fld_en = 4'b0000 --> Disable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable DFE Adaptation
    ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);

    // [3:0] reg_fld_en = 4'b1111 --> Enable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [40,x] Waiting for FLD
    DELAY_40US();

    // Scan Auto FLD
    ScalerSetByte(P1C_59_DP_FLD_11, ScalerGetByte(P1C_75_DP_FLD_39));
    ScalerSetByte(P1C_5A_DP_FLD_12, ScalerGetByte(P1C_76_DP_FLD_40));
    ScalerSetByte(P1C_5B_DP_FLD_13, ScalerGetByte(P1C_77_DP_FLD_41));
    ScalerSetByte(P1C_5C_DP_FLD_14, ScalerGetByte(P1C_78_DP_FLD_42));

    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock for Signal Detection
    ScalerSetBit(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_fld_cp_en_manual = 4'b0000 --> CDR Open Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetByte(P1C_50_DP_FLD_2, 0x00);

    // [3:0] Enable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte(P1C_5D_DP_FLD_15, 0xFF);
    ScalerSetByte(P1C_5E_DP_FLD_16, 0xFF);

    // [3:0] reg_fld_cp_en_manual = 4'b1111 --> CDR Close Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte(P1C_5D_DP_FLD_15, ucIcp);
    ScalerSetByte(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
//--------------------------------------------------
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyCtsTp1SetPhyUnFlip2Lane(EnumDpNFCodeRef enumDpNFCodeRef)
{
    BYTE ucIcp = 0;

    // LDO_en for Lane3
    ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT5, _BIT5);

    // Enable Lane3 1.1V LDO Tracking
    ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT4, _BIT4);

    // [7:6] LANE_EN = 2'b00 --> Disable LANE_EN
    // [3:2] CDR_EN = 2'b00 --> Disable CDR_EN
    ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    if((g_ucDpRx0PhyCtsCtrl & 0x30) == 0x20)
    {
        // [6] Enable Lane2 Rx_en
        ScalerSetBit(P1A_22_DP_RX_02, ~_BIT6, _BIT6);

        // [2] Enable Lane2 CDR_en
        ScalerSetBit(P1A_22_DP_RX_02, ~_BIT2, _BIT2);
    }
    else if((g_ucDpRx0PhyCtsCtrl & 0x30) == 0x30)
    {
        // [7] Enable Lane3 Rx_en
        ScalerSetBit(P1A_22_DP_RX_02, ~_BIT7, _BIT7);

        // [3] Enable Lane3 CDR_en
        ScalerSetBit(P1A_22_DP_RX_02, ~_BIT3, _BIT3);
    }

    // [4:3] DP Mac Select One Lane
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:6] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:2] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit(P1C_4C_READY_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7:6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [4:2] reg_vcm_ctrl_op_l3 = 3'b101 --> 600mV
    ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [3:0] Disable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // Disable DFE Adaptation
    ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);

    // LE Max = 24, LE Initial = 24
    ScalerSetByte(P17_C2_L2_LIMIT_INIT, 0x88);
    ScalerSetByte(P17_D2_L3_LIMIT_INIT, 0x88);
    ScalerSetByte(P17_C3_L2_INIT_1, 0xD0);
    ScalerSetByte(P17_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 26
    ScalerSetByte(P17_C4_L2_INIT_2, 0x1A);
    ScalerSetByte(P17_D4_L3_INIT_2, 0x1A);

    // Tap1 Initial Value = 0
    ScalerSetByte(P17_C5_L2_INIT_3, 0x00);
    ScalerSetByte(P17_D5_L3_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte(P17_C6_L2_INIT_4, 0x00);
    ScalerSetByte(P17_D6_L3_INIT_4, 0x00);

    // Load Intial DFE Code
    ScalerSetByte(P17_CA_L2_INIT_8, 0xFF);
    ScalerSetByte(P17_DA_L3_INIT_8, 0xFF);
    ScalerSetByte(P17_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P17_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(g_ucDpRx0PhyCtsCtrl & 0xC0)
    {
        case 0x80:

            // [7:4] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 900M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

            // [7:6] en_half_pf = 1 --> Half Rate PD for High Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // [6:4] sel_cont3 = 3'b010 --> BBPD UP/DN Sync
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

            // [4] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT4, 0x00);

            // [7:5] LE_lowgain_highboost = 3'b110
            // [4] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

            // [1:0] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_sel_cdr_res = 2K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 13.5uA in Each Lane
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xCC);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:2] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Analog CDR Auto FLD Counter (50/500 = 2*(27M/540M))
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), 0x00);
                ScalerSetByte(P1C_65_DP_FLD_23, 0x31);
                ScalerSetByte(P1C_66_DP_FLD_24, 0x31);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);
            }
            else
            {
                // [3:2] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;

        case 0x40:

            // [7:4] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [7:6] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6), 0x00);

            // [6:4] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

            // [4] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT4, 0x00);

            // [7:5] LE_lowgain_highboost = 3'b100
            // [4] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

            // [1:0] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 8K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Initial Band
            ScalerSetByte(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 16.5uA in Each Lane
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xDD);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:2] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Analog CDR Auto FLD Counter (100/500 = 2*(27M/270M))
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), 0x00);
                ScalerSetByte(P1C_65_DP_FLD_23, 0x63);
                ScalerSetByte(P1C_66_DP_FLD_24, 0x63);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);
            }
            else
            {
                // [3:2] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;

        default:
        case 0x00:

            // [7:4] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [7:6] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT7 | _BIT6), 0x00);

            // [6:4] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

            // [4] highboost_for_rbr = 1 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT4, _BIT4);

            // [7:5] LE_lowgain_highboost = 3'b000
            // [4] sel_dyn_std = 1 --> Std DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

            // [1:0] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT1);

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 6K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_53_DP_FLD_5, 0x70);
            ScalerSetByte(P1C_54_DP_FLD_6, 0x70);

            // reg_fld_cdr_cp Icp = 19.5uA in Each Lane
            ScalerSetByte(P1C_5E_DP_FLD_16, 0xEE);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:2] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Analog CDR Auto FLD Counter (50/150 = 2*(27M/162M))
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), 0x00);
                ScalerSetByte(P1C_65_DP_FLD_23, 0x31);
                ScalerSetByte(P1C_66_DP_FLD_24, 0x31);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), 0x00);
                ScalerSetByte(P1C_6A_DP_FLD_28, 0x96);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0x96);
            }
            else
            {
                // [3:2] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;
    }

    // Backup Icp for CDR lock
    ucIcp = ScalerGetByte(P1C_5E_DP_FLD_16);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P1C_3E_FORE_OFFSET_K_24, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_46_FORE_OFFSET_K_32, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable Foreground Offset Calibration lane2, 3
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    //////////////
    // FLD Band //
    //////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:2] reg_fld_en = 2'b00 --> Disable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), 0x00);

    // Disable DFE Adaptation
    ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);

    // [3:2] reg_fld_en = 2b11 --> Enable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [40,x] Waiting for FLD
    DELAY_40US();

    // Scan Auto FLD
    ScalerSetByte(P1C_5B_DP_FLD_13, ScalerGetByte(P1C_77_DP_FLD_41));
    ScalerSetByte(P1C_5C_DP_FLD_14, ScalerGetByte(P1C_78_DP_FLD_42));

    // [3:2 reg_fld_adp_en_manual = 2'b11 --> Enable CDR Clock for Signal Detection
    ScalerSetBit(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:2] reg_fld_cp_en_manual = 2'b00 --> CDR Open Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT3 | _BIT2), 0x00);

    // [3:0] Enable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte(P1C_5E_DP_FLD_16, 0xFF);

    // [3:2] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7:6] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyCtsTp1SetPhyFlip2Lane(EnumDpNFCodeRef enumDpNFCodeRef)
{
    BYTE ucIcp = 0;

    // LDO_en for Lane1
    ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT1, _BIT1);

    // Enable Lane1 1.1V LDO Tracking
    ScalerSetBit(P1A_30_COMBO_USB_00, ~_BIT0, _BIT0);

    // [5:4] LANE_EN = 2'b00 --> Disable LANE_EN
    // [1:0] CDR_EN = 2'b00 --> Disable CDR_EN
    ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    if((g_ucDpRx0PhyCtsCtrl & 0x30) == 0x00)
    {
        // [4] Enable Lane0 Rx_en
        ScalerSetBit(P1A_22_DP_RX_02, ~_BIT4, _BIT4);

        // [0] Enable Lane0 CDR_en
        ScalerSetBit(P1A_22_DP_RX_02, ~_BIT0, _BIT0);
    }
    else if((g_ucDpRx0PhyCtsCtrl & 0x30) == 0x10)
    {
        // [5] Enable Lane1 Rx_en
        ScalerSetBit(P1A_22_DP_RX_02, ~_BIT5, _BIT5);

        // [1] Enable Lane1 CDR_en
        ScalerSetBit(P1A_22_DP_RX_02, ~_BIT1, _BIT1);
    }

    // [4:3] DP Mac Select One Lane
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [1:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit(P1C_4C_READY_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [4:2] reg_vcm_ctrl_op_l1 = 3'b101 --> 600mV
    ScalerSetBit(P1A_2C_DP_RX_12, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [3:0] Disable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // Disable DFE Adaptation
    ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);

    // LE Max = 24, LE Initial = 24
    ScalerSetByte(P17_A2_L0_LIMIT_INIT, 0x88);
    ScalerSetByte(P17_B2_L1_LIMIT_INIT, 0x88);
    ScalerSetByte(P17_A3_L0_INIT_1, 0xD0);
    ScalerSetByte(P17_B3_L1_INIT_1, 0xD0);

    // Tap0 Initial Value = 26
    ScalerSetByte(P17_A4_L0_INIT_2, 0x1A);
    ScalerSetByte(P17_B4_L1_INIT_2, 0x1A);

    // Tap1 Initial Value = 0
    ScalerSetByte(P17_A5_L0_INIT_3, 0x00);
    ScalerSetByte(P17_B5_L1_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte(P17_A6_L0_INIT_4, 0x00);
    ScalerSetByte(P17_B6_L1_INIT_4, 0x00);

    // Load Intial DFE Code
    ScalerSetByte(P17_AA_L0_INIT_8, 0xFF);
    ScalerSetByte(P17_BA_L1_INIT_8, 0xFF);
    ScalerSetByte(P17_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P17_BA_L1_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P17_EF_RESET_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(g_ucDpRx0PhyCtsCtrl & 0xC0)
    {
        case 0x80:

            // [3:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 900M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // [5:4] en_half_pf = 1 --> Half Rate PD for High Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

            // [2:0] sel_cont3 = 3'b010 --> BBPD UP/DN Sync
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            // [0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT0, 0x00);

            // [3:1] LE_lowgain_highboost = 3'b110
            // [0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

            // [7:6] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), 0x00);

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_sel_cdr_res = 2K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x50);

            // reg_fld_cdr_cp Icp = 13.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xCC);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [1:0] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (50/500 = 2*(27M/540M))
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), 0x00);
                ScalerSetByte(P1C_63_DP_FLD_21, 0x31);
                ScalerSetByte(P1C_64_DP_FLD_22, 0x31);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
            }
            else
            {
                // [1:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte(P1C_64_DP_FLD_22, 0xF3);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
            }

            break;

        case 0x40:

            // [3:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // [5:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT5 | _BIT4), 0x00);

            // [2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // [0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT0, 0x00);

            // [3:1] LE_lowgain_highboost = 3'b100
            // [0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

            // [7:6] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT6);

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 8K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x50);

            // reg_fld_cdr_cp Icp = 16.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xDD);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [1:0] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (100/500 = 2*(27M/270M))
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), 0x00);
                ScalerSetByte(P1C_63_DP_FLD_21, 0x63);
                ScalerSetByte(P1C_64_DP_FLD_22, 0x63);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
            }
            else
            {
                // [1:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte(P1C_64_DP_FLD_22, 0xF3);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
            }

            break;

        default:
        case 0x00:

            // [3:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit(P1A_03_COMBO_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // [5:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit(P1A_04_COMBO_04, ~(_BIT5 | _BIT4), 0x00);

            // [2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit(P1A_10_COMBO_RX_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // [0] highboost_for_rbr = 1 --> only in rbr
            ScalerSetBit(P1A_12_COMBO_RX_02, ~_BIT0, _BIT0);

            // [3:1] LE_lowgain_highboost = 3'b000
            // [0] sel_dyn_std = 1 --> Std DFF
            ScalerSetBit(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            // [7:6] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT7);

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 6K
            ScalerSetBit(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Initial Band
            ScalerSetByte(P1C_51_DP_FLD_3, 0x70);
            ScalerSetByte(P1C_52_DP_FLD_4, 0x70);

            // reg_fld_cdr_cp Icp = 19.5uA in Each Lane
            ScalerSetByte(P1C_5D_DP_FLD_15, 0xEE);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [1:0] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (50/150 = 2*(27M/162M))
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), 0x00);
                ScalerSetByte(P1C_63_DP_FLD_21, 0x31);
                ScalerSetByte(P1C_64_DP_FLD_22, 0x31);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), 0x00);
                ScalerSetByte(P1C_68_DP_FLD_26, 0x96);
                ScalerSetByte(P1C_69_DP_FLD_27, 0x96);
            }
            else
            {
                // [1:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte(P1C_64_DP_FLD_22, 0xF3);

                ScalerSetBit(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte(P1C_69_DP_FLD_27, 0xF4);
            }

            break;
    }

    // Backup Icp for CDR lock
    ucIcp = ScalerGetByte(P1C_5D_DP_FLD_15);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P1C_2E_FORE_OFFSET_K_8, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_36_FORE_OFFSET_K_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable Foreground Offset Calibration lane0, 1
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    //////////////
    // FLD Band //
    //////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] reg_fld_en = 2'b00 --> Disable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), 0x00);

    // Disable DFE Adaptation
    ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);

    // [1:0] reg_fld_en = 2b11 --> Enable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [40,x] Waiting for FLD
    DELAY_40US();

    // Scan Auto FLD
    ScalerSetByte(P1C_59_DP_FLD_11, ScalerGetByte(P1C_75_DP_FLD_39));
    ScalerSetByte(P1C_5A_DP_FLD_12, ScalerGetByte(P1C_76_DP_FLD_40));

    // [1:0 reg_fld_adp_en_manual = 2'b11 --> Enable CDR Clock for Signal Detection
    ScalerSetBit(P1C_57_DP_FLD_9, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] reg_fld_cp_en_manual = 2'b00 --> CDR Open Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT1 | _BIT0), 0x00);

    // [3:0] Enable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte(P1C_5D_DP_FLD_15, 0xFF);

    // [1:0] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte(P1C_5D_DP_FLD_15, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [5:4] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}
#endif


//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyCtsTp2SetPhy(void)
{
    // [4] Enable Comma Detection
    ScalerSetBit(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    // [5] Disable De-Scrambling
    ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    // [2] Disable Enhancement Control Mode
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

    if(ScalerGetBit(P1A_00_COMBO_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6))
    {
        ScalerDpRx0PhyCtsTp2SetPhyUnFlip2Lane();
    }
    else if(ScalerGetBit(P1A_00_COMBO_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        ScalerDpRx0PhyCtsTp2SetPhyFlip2Lane();
    }
    else
#endif
    {
        ScalerDpRx0PhyCtsTp2SetPhy4Lane();
    }
}


//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyCtsTp2SetPhy4Lane(void)
{
    BYTE ucIcp = 0;


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetByte(P1C_4C_READY_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte(P1C_4D_READY_TIMER_2, 0x0F);

    // [3:0] Disable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////////
    // DFE CDR Initial Setting //
    /////////////////////////////

    // DFE Parameter -> Set DFE Initial
    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)
    {
        g_pusDpRx0ClockCount[0] = 0x2710; // 5.4G

        ScalerDpRx0SetDFEInitial(_DP_LINK_HBR2);
    }
    else if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x40)
    {
        g_pusDpRx0ClockCount[0] = 0x1388; // 2.7G

        ScalerDpRx0SetDFEInitial(_DP_LINK_HBR);
    }
    else
    {
        g_pusDpRx0ClockCount[0] = 0xBB8; // 1.62G

        ScalerDpRx0SetDFEInitial(_DP_LINK_RBR);
    }

    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];

    ucIcp = ScalerGetByte(P1C_5D_DP_FLD_15);

    // Enable Foreground Offset Calibration
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Initial Band
    ScalerSetByte(P1C_51_DP_FLD_3, ScalerGetByte(P1C_75_DP_FLD_39));
    ScalerSetByte(P1C_52_DP_FLD_4, ScalerGetByte(P1C_76_DP_FLD_40));
    ScalerSetByte(P1C_53_DP_FLD_5, ScalerGetByte(P1C_77_DP_FLD_41));
    ScalerSetByte(P1C_54_DP_FLD_6, ScalerGetByte(P1C_78_DP_FLD_42));

    // Reset FLD Band and Enable Auto FLD
    ScalerSetByte(P1C_50_DP_FLD_2, 0xFF);
    ScalerSetByte(P1C_50_DP_FLD_2, 0x0F);

    // [3:0] reg_fld_en = 4'b0000 --> Disable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(P17_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte(P17_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte(P17_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte(P17_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(P17_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte(P17_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte(P17_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte(P17_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // [3:0] reg_fld_en = 4'b1111 --> Enable FLD
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // Disable DFE Adaptation
    ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);

    // Enable Foreground Offset Calibration
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    ///////////////////////
    // FLD Band Finetune //
    ///////////////////////

    // Scan Auto FLD
    ScalerSetByte(P1C_59_DP_FLD_11, ScalerGetByte(P1C_75_DP_FLD_39));
    ScalerSetByte(P1C_5A_DP_FLD_12, ScalerGetByte(P1C_76_DP_FLD_40));
    ScalerSetByte(P1C_5B_DP_FLD_13, ScalerGetByte(P1C_77_DP_FLD_41));
    ScalerSetByte(P1C_5C_DP_FLD_14, ScalerGetByte(P1C_78_DP_FLD_42));

    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetBit(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_fld_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetByte(P1C_50_DP_FLD_2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] Enable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
    {
        case 0x30:

            // Lane3 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_DP_SCALER_LANE3);

            break;

        case 0x20:

            // Lane2 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_DP_SCALER_LANE2);

            break;

        case 0x10:

            // Lane1 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_DP_SCALER_LANE1);

            break;

        default:
        case 0x00:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_DP_SCALER_LANE0);

            break;
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte(P1C_5D_DP_FLD_15, 0xFF);
    ScalerSetByte(P1C_5E_DP_FLD_16, 0xFF);

    // [3:0] reg_fld_cp_en_manual = 4'b1111 --> CDR Close Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte(P1C_5D_DP_FLD_15, ucIcp);
    ScalerSetByte(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}


#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyCtsTp2SetPhyUnFlip2Lane(void)
{
    BYTE ucIcp = 0;


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:6] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:2] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit(P1C_4C_READY_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7:6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:0] Disable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////////
    // DFE CDR Initial Setting //
    /////////////////////////////

    // DFE Parameter -> Set DFE Initial
    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)
    {
        g_pusDpRx0ClockCount[2] = 0x2710; // 5.4G

        ScalerDpRx0SetDFEInitialUnFlip2Lane(_DP_LINK_HBR2);
    }
    else if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x40)
    {
        g_pusDpRx0ClockCount[2] = 0x1388; // 2.7G

        ScalerDpRx0SetDFEInitialUnFlip2Lane(_DP_LINK_HBR);
    }
    else
    {
        g_pusDpRx0ClockCount[2] = 0xBB8; // 1.62G

        ScalerDpRx0SetDFEInitialUnFlip2Lane(_DP_LINK_RBR);
    }

    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[2];

    ucIcp = ScalerGetByte(P1C_5E_DP_FLD_16);

    // Enable Foreground Offset Calibration lane2, 3
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Initial Band
    ScalerSetByte(P1C_53_DP_FLD_5, ScalerGetByte(P1C_77_DP_FLD_41));
    ScalerSetByte(P1C_54_DP_FLD_6, ScalerGetByte(P1C_78_DP_FLD_42));

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Reset FLD -> Low Active Reset
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), 0x00);

    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(P17_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte(P17_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(P17_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte(P17_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Enable FLD and DFE Adaptation
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // Disable DFE Adaptation
    ScalerSetByte(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P17_D1_L3_DFE_EN_2, 0x00);

    // Enable Foreground Offset Calibration lane2, 3
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    ///////////////////////
    // FLD Band Finetune //
    ///////////////////////

    // Scan Auto FLD
    ScalerSetByte(P1C_5B_DP_FLD_13, ScalerGetByte(P1C_77_DP_FLD_41));
    ScalerSetByte(P1C_5C_DP_FLD_14, ScalerGetByte(P1C_78_DP_FLD_42));

    // [3:2] reg_fld_adp_en_manual = 2'b11 --> Enable CDR Clock
    ScalerSetBit(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:2] reg_fld_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT3 | _BIT2), 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] Enable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
    {
        case 0x30:

            // Lane3 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_DP_SCALER_LANE3);

            break;

        default:
        case 0x20:

            // Lane2 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_DP_SCALER_LANE2);

            break;
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = max for locking range
    ScalerSetByte(P1C_5E_DP_FLD_16, 0xFF);

    // [3:2] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7:6] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}


//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyCtsTp2SetPhyFlip2Lane(void)
{
    BYTE ucIcp = 0;


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [1:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit(P1C_4C_READY_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [3:0] Disable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////////
    // DFE CDR Initial Setting //
    /////////////////////////////

    // DFE Parameter -> Set DFE Initial
    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)
    {
        g_pusDpRx0ClockCount[0] = 0x2710; // 5.4G

        ScalerDpRx0SetDFEInitialFlip2Lane(_DP_LINK_HBR2);
    }
    else if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x40)
    {
        g_pusDpRx0ClockCount[0] = 0x1388; // 2.7G

        ScalerDpRx0SetDFEInitialFlip2Lane(_DP_LINK_HBR);
    }
    else
    {
        g_pusDpRx0ClockCount[0] = 0xBB8; // 1.62G

        ScalerDpRx0SetDFEInitialFlip2Lane(_DP_LINK_RBR);
    }

    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];

    ucIcp = ScalerGetByte(P1C_5D_DP_FLD_15);

    // Enable Foreground Offset Calibration lane0, 1
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Initial Band
    ScalerSetByte(P1C_51_DP_FLD_3, ScalerGetByte(P1C_75_DP_FLD_39));
    ScalerSetByte(P1C_52_DP_FLD_4, ScalerGetByte(P1C_76_DP_FLD_40));

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Reset FLD -> Low Active Reset
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), 0x00);

    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(P17_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte(P17_B1_L1_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(P17_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte(P17_B1_L1_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Enable FLD and DFE Adaptation
    ScalerSetBit(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS(85);

    // Disable DFE Adaptation
    ScalerSetByte(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P17_B1_L1_DFE_EN_2, 0x00);

    // Enable Foreground Offset Calibration lane0, 1
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 10; pData[0]++)
    {
        if(((ScalerGetBit(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US();
    }


    ///////////////////////
    // FLD Band Finetune //
    ///////////////////////

    // Scan Auto FLD
    ScalerSetByte(P1C_59_DP_FLD_11, ScalerGetByte(P1C_75_DP_FLD_39));
    ScalerSetByte(P1C_5A_DP_FLD_12, ScalerGetByte(P1C_76_DP_FLD_40));

    // [1:0] reg_fld_adp_en_manual = 2'b11 --> Enable CDR Clock
    ScalerSetBit(P1C_57_DP_FLD_9, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] reg_fld_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(P1C_50_DP_FLD_2, ~(_BIT1 | _BIT0), 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] Enable Signal Detection
    ScalerSetBit(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
    {
        case 0x10:

            // Lane1 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_DP_SCALER_LANE1);

            break;

        default:
        case 0x00:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand(_DP_SCALER_LANE0);

            break;
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = max for locking range
    ScalerSetByte(P1C_5D_DP_FLD_15, 0xFF);

    // [1:0] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte(P1C_5D_DP_FLD_15, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [5:4] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}
#endif

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
bit ScalerDpRx0PhyCtsTp1Check(void)
{
    // Wait for 10ms
    ScalerTimerDelayXms(10);

    // Clear 8B/10B Decode Error Flags
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Wait for 2ms
    ScalerTimerDelayXms(2);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
    {
        case 0x00: // Lane0 Test

            // EQ auto K,Check lane0 CRC
            pData[0] = 0x10;

            break;

        case 0x10: // Lane1 Test

            // EQ auto K,Check lane1 CRC
            pData[0] = 0x20;

            break;

        case 0x20: // Lane2 Test

            // EQ auto K,Check lane2 CRC
            pData[0] = 0x40;

            break;

        case 0x30: // Lane3 Test

            // EQ auto K,Check lane3 CRC
            pData[0] = 0x80;

            break;

        default:

            pData[0] = 0x00;

            break;
    }

    if(((ScalerGetByte(PB_06_DECODE_10B8B_ERROR) & (pData[0] >> 4)) == 0x00) &&
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
bit ScalerDpRx0PhyCtsTp2Check(void)
{
    ScalerTimerDelayXms(10);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
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
void ScalerDpRx0PhyCTS(void)
{
    // _ERROR_PRONE_CODE
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[0] = 1 --> PHY CTS Enable Start
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[2:1] = 00 --> D0 Port
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[2:0]) = 0x01 --> Clock Recovery
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[2:0]) = 0x02 --> EQ CRC
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[2:0]) = 0x03 --> Error Counter Reset
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[2:0]) = 0x04 --> Error Counter Read
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[2:0]) = 0x05 --> PHY CTS Disable
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[5:4]) = 00 --> lane0
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[5:4]) = 01 --> lane1
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[5:4]) = 10 --> lane2
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[5:4]) = 11 --> lane3
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[7:6]) = 00 --> RBR
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[7:6]) = 01 --> HBR
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[7:6]) = 10 --> HBR2
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 51[7:6]) = 11 --> HBR3

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

    WORD usTemp = 0;
    WORD usErrorCount = 0;
    BYTE ucIcp = 0;
    BYTE ucPhyCtsAutoMode = 0;

    g_ucDpRx0PhyCtsCtrl = 0x00;

    EX0 = 0;

    ScalerSetBit(P1D_50_CDR_01, ~(_BIT4 | _BIT3), ScalerGetBit(P1D_50_CDR_01, (_BIT2 | _BIT1)) << 2);

    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, _BIT7) == _BIT7)
    {
        ucPhyCtsAutoMode = 0xFF;

        while(ucPhyCtsAutoMode != 0x00)
        {
            ScalerDebug();

            if(ucPhyCtsAutoMode == 0x11)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x11);
                ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x11);
            }
            else if(ucPhyCtsAutoMode == 0x12)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x77);
            }

            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x06, 0x22);
            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x07, 0x22);

            switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x02) & (_BIT2 | _BIT1 | _BIT0))
            {
                case 0x01: // CDR Lock Check

                    if(ucPhyCtsAutoMode != 0x11)
                    {
                        // Link Rate
                        switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00))
                        {
                            case 0x1E:

                                g_ucDpRx0PhyCtsCtrl = ((g_ucDpRx0PhyCtsCtrl & 0x3F) | (_BIT7 | _BIT6));

                                break;

                            case 0x14:

                                g_ucDpRx0PhyCtsCtrl = ((g_ucDpRx0PhyCtsCtrl & 0x3F) | (_BIT7));

                                break;

                            case 0x0A:

                                g_ucDpRx0PhyCtsCtrl = ((g_ucDpRx0PhyCtsCtrl & 0x3F) | (_BIT6));

                                break;

                            default:
                            case 0x06:

                                g_ucDpRx0PhyCtsCtrl = (g_ucDpRx0PhyCtsCtrl & 0x3F);

                                break;
                        }

                        // Lane Select
                        switch(ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
                        {
                            default:
                            case 0x00: // Source Lane0

                                g_ucDpRx0PhyCtsCtrl = ((g_ucDpRx0PhyCtsCtrl & 0xCF) | (_D0_DP_LANE0 << 4));

                                break;

                            case 0x10: // Source Lane1

                                g_ucDpRx0PhyCtsCtrl = ((g_ucDpRx0PhyCtsCtrl & 0xCF) | (_D0_DP_LANE1 << 4));

                                break;

                            case 0x20: // Source Lane2

                                g_ucDpRx0PhyCtsCtrl = ((g_ucDpRx0PhyCtsCtrl & 0xCF) | (_D0_DP_LANE2 << 4));

                                break;

                            case 0x30: // Source Lane3

                                g_ucDpRx0PhyCtsCtrl = ((g_ucDpRx0PhyCtsCtrl & 0xCF) | (_D0_DP_LANE3 << 4));

                                break;
                        }

                        SET_DP_RX0_AUX_MANUAL_MODE_PHY_CTS();

                        ScalerDpRx0PhyCtsTp1SetPhy(_DP_NF_REF_XTAL);

                        ucPhyCtsAutoMode = 0x01;
                    }

                    if(ucPhyCtsAutoMode == 0x01)
                    {
                        if(ScalerDpRx0PhyCtsTp1Check() == _TRUE)
                        {
                            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x11);
                            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x11);

                            ucPhyCtsAutoMode = 0x11;
                        }
                        else
                        {
                            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x00);
                            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x00);

                            ucPhyCtsAutoMode = 0xF1;
                        }

                        SET_DP_RX0_AUX_AUTO_MODE_PHY_CTS();
                    }

                    break;

                case 0x02: // Symbol Lock Check by TPS2
                case 0x03: // Symbol Lock Check by TPS3
                case 0x07: // Symbol Lock Check by TPS4

                    if((ucPhyCtsAutoMode == 0x11) || (ucPhyCtsAutoMode == 0xF2))
                    {
                        SET_DP_RX0_AUX_MANUAL_MODE_PHY_CTS();

                        ScalerDpRx0PhyCtsTp2SetPhy();

                        ucPhyCtsAutoMode = 0x02;
                    }

                    if(ucPhyCtsAutoMode == 0x02)
                    {
                        if(ScalerDpRx0PhyCtsTp2Check() == _TRUE)
                        {
                            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x77);

                            ucPhyCtsAutoMode = 0x12;
                        }
                        else
                        {
                            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x11);
                            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x11);

                            ucPhyCtsAutoMode = 0xF2;
                        }
                    }

                    SET_DP_RX0_AUX_AUTO_MODE_PHY_CTS();

                    if(ucPhyCtsAutoMode == 0x12)
                    {
                        // Mac Use Xtal Clk
                        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

                        // Error Count Lane Select
                        ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (g_ucDpRx0PhyCtsCtrl & (_BIT5 | _BIT4)) >> 1);

                        // Disable Error Detection
                        ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                        // Reverse PRBS7 Pattern Gen
                        ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~_BIT6, _BIT6);

                        // Disable Scramble
                        ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

                        // Reset DPCD Error Count
                        ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x10, 0x00);
                        ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x11, 0x00);
                        ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x12, 0x00);
                        ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x13, 0x00);
                        ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x14, 0x00);
                        ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x15, 0x00);
                        ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x16, 0x00);
                        ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x17, 0x00);
                    }

                    break;

                case 0x00:

                    if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, (0x0B + ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4))) >> 4))) != 0x00)
                    {
                        if(ucPhyCtsAutoMode != 0x05) // Error Count Enable
                        {
                            // Error Count Enable
                            ucPhyCtsAutoMode = 0x03;

                            // Rebuild phy for pattern switch
                            ScalerDpRx0PhyCtsTp2SetPhy();

                            // Disable Error Detection
                            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                            ScalerTimerDelayXms(2);

                            switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, (0x0B + ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4))) >> 4))))
                            {
                                case 0x03: // PRBS7 Pattern

                                    // PRBS7 Pattern for RBR/HBR
                                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                                    ScalerTimerDelayXms(2);

                                    // Error Count Lock
                                    ucPhyCtsAutoMode = 0x05;

                                    switch(ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
                                    {
                                        case (_BIT5 | _BIT4):

                                            ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x17, ~_BIT7, _BIT7);

                                            break;

                                        case (_BIT5):

                                            ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x15, ~_BIT7, _BIT7);

                                            break;

                                        case (_BIT4):

                                            ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x13, ~_BIT7, _BIT7);

                                            break;

                                        default:
                                        case 0x00:

                                            ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x11, ~_BIT7, _BIT7);

                                            break;
                                    }

                                    // Disable Wildcard IRQ for Error Counter
                                    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), 0x00);

                                    // Enable Read Error Counter IRQ, Clear IRQ Flag
                                    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                                    break;

                                case 0x05: // CP2520 Pattern 1 (HBR2 compliance Pattern)
                                case 0x06: // CP2520 Pattern 2
                                case 0x07: // CP2520 Pattern 3 (TPS4 For HBR3 Compliance Pattern)

                                    // HBR2 Compliance Eye Pattern
                                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                                    ScalerTimerDelayXms(2);

                                    if(((((WORD)ScalerGetByte(PB_0B_BIST_PATTERN3)) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4)) < 1000)
                                    {
                                        // Error Count Lock
                                        ucPhyCtsAutoMode = 0x04;
                                    }
                                    else // Reset CDR to Re-allocate 10bit Raw Data
                                    {
                                        // [4] Disable Comma Detection
                                        ScalerSetBit(PB_05_SAMPLE_EDGE, ~_BIT4, _BIT4);

                                        if((g_ucDpRx0PhyCtsCtrl & 0x30) >= 0x20)
                                        {
                                            ucIcp = ScalerGetByte(P1C_5E_DP_FLD_16);
                                        }
                                        else
                                        {
                                            ucIcp = ScalerGetByte(P1C_5D_DP_FLD_15);
                                        }

                                        for(usTemp = 0; usTemp <= 1000; usTemp++)
                                        {
                                            // [3:0] reg_fld_cp_en_manual = 0 --> CDR Open Loop
                                            ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                                            // [7:0] reg_cdr_cp_in --> Max Icp to Enlarge Locking Range
                                            if((g_ucDpRx0PhyCtsCtrl & 0x30) >= 0x20)
                                            {
                                                ScalerSetByte(P1C_5E_DP_FLD_16, 0xFF);
                                            }
                                            else
                                            {
                                                ScalerSetByte(P1C_5D_DP_FLD_15, 0xFF);
                                            }

                                            // Delay Time us [25,x] Waiting for VCO Stable
                                            DELAY_25US();

                                            // [3:0] reg_fld_cp_en_manual = 1 --> CDR Close Loop
                                            ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                                            // Delay Time us [25,x] Waiting for VCO Stable
                                            DELAY_25US();

                                            // [7:0] reg_cdr_cp_in --> Restore Icp
                                            if((g_ucDpRx0PhyCtsCtrl & 0x30) >= 0x20)
                                            {
                                                ScalerSetByte(P1C_5E_DP_FLD_16, ucIcp);
                                            }
                                            else
                                            {
                                                ScalerSetByte(P1C_5D_DP_FLD_15, ucIcp);
                                            }

                                            // Delay Time us [25,x] Waiting for VCO Stable
                                            DELAY_25US();

                                            // Disable Error Detection
                                            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                                            // HBR2 Compliance Eye Pattern
                                            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                                            ScalerTimerDelayXms(2);

                                            if(((((WORD)ScalerGetByte(PB_0B_BIST_PATTERN3)) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4)) < 1000)
                                            {
                                                // Error Count Lock
                                                ucPhyCtsAutoMode = 0x04;

                                                break;
                                            }
                                        }
                                    }

                                    if(ucPhyCtsAutoMode == 0x04)
                                    {
                                        ucPhyCtsAutoMode = 0x05;

                                        switch(ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
                                        {
                                            case (_BIT5 | _BIT4):

                                                ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x17, ~_BIT7, _BIT7);

                                                break;

                                            case (_BIT5):

                                                ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x15, ~_BIT7, _BIT7);

                                                break;

                                            case (_BIT4):

                                                ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x13, ~_BIT7, _BIT7);

                                                break;

                                            default:
                                            case 0x00:

                                                ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x11, ~_BIT7, _BIT7);

                                                break;
                                        }

                                        // Disable Wildcard IRQ for Error Counter
                                        ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), 0x00);

                                        // Enable Read Error Counter IRQ, Clear IRQ Flag
                                        ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                                    }

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

                            switch(ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
                            {
                                case (_BIT5 | _BIT4):

                                    // Store Lane3 Error
                                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x16, LOBYTE(usErrorCount));
                                    ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                                    break;

                                case (_BIT5):

                                    // Store Lane2 Error
                                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x14, LOBYTE(usErrorCount));
                                    ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                                    break;

                                case (_BIT4):

                                    // Store Lane1 Error
                                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x12, LOBYTE(usErrorCount));
                                    ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                                    break;

                                default:
                                case 0x00:

                                    // Store Lane0 Error
                                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x10, LOBYTE(usErrorCount));
                                    ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                                    break;
                            }

                            // If DPCD 0x0021xh Hit
                            if(ScalerGetBit(PB7_FB_DUMMY_1, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
                            {
                                // Clear IRQ Flag
                                ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT1);

                                if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, (0x0B + ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4))) >> 4)))) == 0x03)
                                {
                                    // Reset 8B/10B Error Counter
                                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                                }
                                else
                                {
                                    // Reset 8B/10B Error Counter
                                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                                }
                            }
                            else if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, (0x0B + ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4))) >> 4))) == 0x00)
                            {
                                ucPhyCtsAutoMode = 0xFF;
                            }
                        }
                    }
                    else if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, _BIT7) == 0x00)
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
        while(GET_DP_RX0_PHY_CTS_FLG() == _TRUE)
        {
            ScalerDebug();

            DebugMessageRx0("7. PHY CTS Loop", ScalerGetByte(P1D_51_CDR_02));

            switch(ScalerGetByte(P1D_51_CDR_02) & 0x30)
            {
                default:
                case 0x00: // Source Lane0

                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _D0_DP_LANE0 << 4);

                    break;

                case 0x10: // Source Lane1

                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _D0_DP_LANE1 << 4);

                    break;

                case 0x20: // Source Lane2

                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _D0_DP_LANE2 << 4);

                    break;

                case 0x30: // Source Lane3

                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _D0_DP_LANE3 << 4);

                    break;
            }

            ScalerRead(P1D_51_CDR_02, 1, &g_ucDpRx0PhyCtsCtrl, _NON_AUTOINC);

            DebugMessageRx0("7. PHY CTS Loop", g_ucDpRx0PhyCtsCtrl);

            switch(g_ucDpRx0PhyCtsCtrl & 0x07)
            {
                case 0x01: // CDR Lock Check

                    ScalerSetByte(P1D_51_CDR_02, (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0))); // Clear DP PHY CTS Phase Info

                    ScalerDpRx0PhyCtsTp1SetPhy(_DP_NF_REF_XTAL);

                    if(ScalerDpRx0PhyCtsTp1Check() == _TRUE)
                    {
                        ScalerSetBit(P1D_50_CDR_01, ~_BIT5, _BIT5);
                    }
                    else
                    {
                        ScalerSetBit(P1D_50_CDR_01, ~_BIT5, 0x00);
                    }

                    break;

                case 0x02: // Symbol Lock Check

                    ScalerSetByte(P1D_51_CDR_02, (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                    ScalerDpRx0PhyCtsTp2SetPhy();

                    if(ScalerDpRx0PhyCtsTp2Check() == _TRUE)
                    {
                        ScalerSetBit(P1D_50_CDR_01, ~_BIT6, _BIT6);
                    }
                    else
                    {
                        ScalerSetBit(P1D_50_CDR_01, ~_BIT6, 0x00);
                    }

                    break;

                case 0x03:

                    ScalerSetByte(P1D_51_CDR_02, (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                    ScalerDpRx0PhyCtsTp2SetPhy();

                    // Mac Use Xtal Clk
                    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

                    ScalerTimerDelayXms(1000);

                    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
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

                    // Disable Error Detection
                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    if((g_ucDpRx0PhyCtsCtrl & 0x80) == 0x80)
                    {
                        // HBR2 Compliance Eye Pattern
                        ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    }
                    else
                    {
                        // PRBS7 Pattern for RBR/HBR
                        ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    }

                    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)  // HBR2 Case
                    {
                        ScalerTimerDelayXms(10);

                        if(((((WORD)ScalerGetByte(PB_0B_BIST_PATTERN3)) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4)) < 1000)
                        {
                            DebugMessageRx0("CDR No Reset", 0x00);
                        }
                        else // Reset CDR to Re-allocate 10bit Raw Data
                        {
                            // [4] Disable Comma Detection
                            ScalerSetBit(PB_05_SAMPLE_EDGE, ~_BIT4, _BIT4);

                            // [7:0] reg_cdr_cp_in --> Max Icp to Enlarge Locking Range
                            if((g_ucDpRx0PhyCtsCtrl & 0x30) >= 0x20)
                            {
                                ucIcp = ScalerGetByte(P1C_5E_DP_FLD_16);
                            }
                            else
                            {
                                ucIcp = ScalerGetByte(P1C_5D_DP_FLD_15);
                            }

                            for(usTemp = 0; usTemp <= 1000; usTemp++)
                            {
                                // [3:0] reg_fld_cp_en_manual = 0 --> CDR Open Loop
                                ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                                // [7:0] reg_cdr_cp_in --> Max Icp to Enlarge Locking Range
                                if((g_ucDpRx0PhyCtsCtrl & 0x30) >= 0x20)
                                {
                                    // [7:0] reg_cdr_cp_in --> Max Icp to Enlarge Locking Range
                                    ScalerSetByte(P1C_5E_DP_FLD_16, 0xFF);
                                }
                                else
                                {
                                    // [7:0] reg_cdr_cp_in --> Max Icp to Enlarge Locking Range
                                    ScalerSetByte(P1C_5D_DP_FLD_15, 0xFF);
                                }

                                // Delay Time us [25,x] Waiting for VCO Stable
                                DELAY_25US();

                                // [3:0] reg_fld_cp_en_manual = 1 --> CDR Close Loop
                                ScalerSetBit(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                                // Delay Time us [25,x] Waiting for VCO Stable
                                DELAY_25US();

                                // [7:0] reg_cdr_cp_in --> Restore Icp
                                if((g_ucDpRx0PhyCtsCtrl & 0x30) >= 0x20)
                                {
                                    ScalerSetByte(P1C_5E_DP_FLD_16, ucIcp);
                                }
                                else
                                {
                                    ScalerSetByte(P1C_5D_DP_FLD_15, ucIcp);
                                }

                                // Delay Time us [25,x] Waiting for VCO Stable
                                DELAY_25US();

                                // Disable Error Detection
                                ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                                // HBR2 Compliance Eye Pattern
                                ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                                ScalerTimerDelayXms(2);

                                DebugMessageRx0("CDR Reset", usTemp);

                                if(((((WORD)ScalerGetByte(PB_0B_BIST_PATTERN3)) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4)) < 1000)
                                {
                                    break;
                                }
                            }

                            DebugMessageRx0("CDR Reset Done", 0xFF);
                        }
                    }

                    break;

                case 0x04:

                    ScalerSetByte(P1D_51_CDR_02, (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                    break;

                case 0x05:

                    // Clear DP PHY CTS Control Register
                    ScalerSetByte(P1D_51_CDR_02, 0x00);

                    // Disable PRBS7 Error Detection
                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    CLR_DP_RX0_PHY_CTS_FLG();

                    break;

                default:

                    // Clear DP PHY CTS Control Register
                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                    break;
            }

            if((g_ucDpRx0PhyCtsCtrl & 0x07) != 0x05)
            {
                if(((ScalerGetByte(P1D_51_CDR_02) & 0x30) >> 4) == _D0_DP_LANE0) // Source Lane0
                {
                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _DP_SCALER_LANE0 << 4);
                }
                else if(((ScalerGetByte(P1D_51_CDR_02) & 0x30) >> 4) == _D0_DP_LANE1) // Source Lane1
                {
                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _DP_SCALER_LANE1 << 4);
                }
                else if(((ScalerGetByte(P1D_51_CDR_02) & 0x30) >> 4) == _D0_DP_LANE2) // Source Lane2
                {
                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _DP_SCALER_LANE2 << 4);
                }
                else if(((ScalerGetByte(P1D_51_CDR_02) & 0x30) >> 4) == _D0_DP_LANE3) // Source Lane3
                {
                    ScalerSetBit(P1D_51_CDR_02, ~(_BIT5 | _BIT4), _DP_SCALER_LANE3 << 4);
                }

                DebugMessageRx0("7. PHY CTS Loop (Swap Back)", ScalerGetByte(P1D_51_CDR_02));
            }
            else
            {
                g_ucDpRx0PhyCtsCtrl = 0x00;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow Watch Dog
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetFifoWD(bit bEn)
{
    ScalerSetBit(PB6_38_DP_VWD_CTRL, ~(_BIT5 | _BIT4), ((bEn == _ENABLE) ? (_BIT5 | _BIT4) : 0x00));
}

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetFifoIRQ(bit bEn)
{
    ScalerSetBit(PB6_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), ((bEn == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
}

//--------------------------------------------------
// Description  : Signal PreDetection for DP(Power Normal)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpRx0NormalPreDetect(void)
{
    // For Dp PHY CTS Test
    if((GET_DP_RX0_PHY_CTS_FLG() == _TRUE) || (ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, _BIT7) == _BIT7))
    {
        ScalerDpRx0PhyCTS();

        return _FALSE;
    }

#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)

    // ASSR Mode Setting
    ScalerDpRx0ASSRModeSetting();

#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    // Check if source doing HDCP handshake while HDCP capability disable
    if(GET_DP_RX0_HDCP_HANDSHAKE_WO_CAP() == _TRUE)
    {
        return _TRUE;
    }
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    CLR_DP_RX0_SOURCE_TYPE_JUDGE();
#endif

    switch(GET_DP_RX0_LINK_TRAINING_STATUS())
    {
        case _DP_NORMAL_LINK_TRAINING_PASS:
        case _DP_LINK_STATUS_FAIL:

            CLR_DP_RX0_VALID_VIDEO_CHECK();

            if((ScalerDpRx0CDRCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpRx0DFECheck() == _TRUE) || (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpRx0MarginLinkCheck() == _TRUE) &&
               (ScalerDpRx0AlignCheck() == _TRUE) &&
               (ScalerDpRx0DecodeCheck() == _TRUE))
            {
                /*
                DebugMessageRx0("9. Lane0 LE Diff", (g_pucDpRx0LEMaxTemp[0] - g_pucDpRx0LEMinTemp[0]));
                DebugMessageRx0("9. Lane1 LE Diff", (g_pucDpRx0LEMaxTemp[1] - g_pucDpRx0LEMinTemp[1]));
                DebugMessageRx0("9. Lane2 LE Diff", (g_pucDpRx0LEMaxTemp[2] - g_pucDpRx0LEMinTemp[2]));
                DebugMessageRx0("9. Lane3 LE Diff", (g_pucDpRx0LEMaxTemp[3] - g_pucDpRx0LEMinTemp[3]));
                DebugMessageRx0("9. Lane0 LE Min", g_pucDpRx0LEMinTemp[0]);
                DebugMessageRx0("9. Lane1 LE Min", g_pucDpRx0LEMinTemp[1]);
                DebugMessageRx0("9. Lane2 LE Min", g_pucDpRx0LEMinTemp[2]);
                DebugMessageRx0("9. Lane3 LE Min", g_pucDpRx0LEMinTemp[3]);
                DebugMessageRx0("9. Lane0 Tap0 Diff", (g_pucDpRx0Tap0MaxTemp[0] - g_pucDpRx0Tap0MinTemp[0]));
                DebugMessageRx0("9. Lane1 Tap0 Diff", (g_pucDpRx0Tap0MaxTemp[1] - g_pucDpRx0Tap0MinTemp[1]));
                DebugMessageRx0("9. Lane2 Tap0 Diff", (g_pucDpRx0Tap0MaxTemp[2] - g_pucDpRx0Tap0MinTemp[2]));
                DebugMessageRx0("9. Lane3 Tap0 Diff", (g_pucDpRx0Tap0MaxTemp[3] - g_pucDpRx0Tap0MinTemp[3]));
                DebugMessageRx0("9. Lane0 Tap0 Max", g_pucDpRx0Tap0MaxTemp[0]);
                DebugMessageRx0("9. Lane1 Tap0 Max", g_pucDpRx0Tap0MaxTemp[1]);
                DebugMessageRx0("9. Lane2 Tap0 Max", g_pucDpRx0Tap0MaxTemp[2]);
                DebugMessageRx0("9. Lane3 Tap0 Max", g_pucDpRx0Tap0MaxTemp[3]);
                DebugMessageRx0("9. FLD Band", ScalerGetByte(PB_BF_LANE0_A_CDR_02));
                DebugMessageRx0("9. Best FLD Band", ScalerGetByte(PB_BE_LANE0_A_CDR_01));
                DebugMessageRx0("9. Lane0 Tap0 Diff 2", (g_pucDpRx0Tap0MaxTemp2[0] - g_pucDpRx0Tap0MinTemp2[0]));
                DebugMessageRx0("9. Lane1 Tap0 Diff 2", (g_pucDpRx0Tap0MaxTemp2[1] - g_pucDpRx0Tap0MinTemp2[1]));
                DebugMessageRx0("9. Lane2 Tap0 Diff 2", (g_pucDpRx0Tap0MaxTemp2[2] - g_pucDpRx0Tap0MinTemp2[2]));
                DebugMessageRx0("9. Lane3 Tap0 Diff 2", (g_pucDpRx0Tap0MaxTemp2[3] - g_pucDpRx0Tap0MinTemp2[3]));
                DebugMessageRx0("9. Lane0 Tap0 Max 2", g_pucDpRx0Tap0MaxTemp2[0]);
                DebugMessageRx0("9. Lane1 Tap0 Max 2", g_pucDpRx0Tap0MaxTemp2[1]);
                DebugMessageRx0("9. Lane2 Tap0 Max 2", g_pucDpRx0Tap0MaxTemp2[2]);
                DebugMessageRx0("9. Lane3 Tap0 Max 2", g_pucDpRx0Tap0MaxTemp2[3]);
                DebugMessageRx0("9. TP2 Check Result", g_ucDpRx0EQCRC);
                */

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LONG_HOTPLUG_EVENT);

                g_ucDpRx0FakeLTLaneCount = g_ucDpRx0LaneCount;
#endif
                if(GET_DP_RX0_NORMAL_LINK_TRAINING_SETPHY_FINISH() == _TRUE)
                {
#if(_DP_ULTRA_HDR_SUPPORT == _ON)
                    ScalerSyncDpSecDataResetProc(_D0_INPUT_PORT);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                    if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                    {
                        // Need to delay 3 Frames totally after Secondary Data Block Reset
                        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);
                    }
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                    if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                    {
                        ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);
                    }

                    CLR_DP_RX0_NORMAL_LINK_TRAINING_SETPHY_FINISH();
                }

                SET_DP_RX0_AUX_MANUAL_MODE();

                if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL)
                {
                    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);

                    ScalerDpRx0ScrambleSetting();
                }

                SET_DP_RX0_AUX_AUTO_MODE();

                if((ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
                   (ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
                {
                    return _FALSE;
                }

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
                CLR_DP_RX_D0_MARGIN_LINK_HBR2();
#endif
                return _TRUE;
            }
            else
            {
                DebugMessageRx0("7. Link Status Fail IRQ", 0);

                SET_DP_RX0_AUX_MANUAL_MODE();

                if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
                {
                    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_STATUS_FAIL);

                    ScalerTimerActiveTimerEvent(100, _SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
                }

                SET_DP_RX0_AUX_AUTO_MODE();
            }

            break;

        case _DP_LINK_TRAINING_FAIL:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);

            ScalerDpRx0LinkStatusIRQ();

            break;

        case _DP_FAKE_LINK_TRAINING_PASS:
        case _DP_FAKE_LINK_TRAINING_PASS_VBIOS:

            CLR_DP_RX0_VALID_VIDEO_CHECK();

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
            if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
            {
                ScalerTimerDelayXms(30);
            }

            DebugMessageRx0("7. DP Rebuild PHY", GET_DP_RX0_LINK_TRAINING_STATUS());

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);

            SET_DP_RX0_AUX_MANUAL_MODE();

            if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
            {
                ScalerDpRx0RebuildPhy(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01));
            }

            SET_DP_RX0_AUX_AUTO_MODE();

            // De-Skew Circuit Reset
            ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
            ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

            // Mac Reset After Link Clock Stable
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

            // Delay for Lane Alignment after Mac Reset
            ScalerTimerDelayXms(2);

            if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS)
            {
                ScalerDpRx0DecodeErrorCountReset();
            }

            if((ScalerDpRx0CDRCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpRx0DFECheck() == _TRUE) || (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpRx0MarginLinkCheck() == _TRUE) &&
               (ScalerDpRx0AlignCheck() == _TRUE) &&
               (ScalerDpRx0DecodeCheck() == _TRUE))
            {
                DebugMessageRx0("7. Rebuild Phy Pass", 0);

                /*
                DebugMessageRx0("9. Lane0 LE Diff", (g_pucDpRx0LEMaxTemp[0] - g_pucDpRx0LEMinTemp[0]));
                DebugMessageRx0("9. Lane1 LE Diff", (g_pucDpRx0LEMaxTemp[1] - g_pucDpRx0LEMinTemp[1]));
                DebugMessageRx0("9. Lane2 LE Diff", (g_pucDpRx0LEMaxTemp[2] - g_pucDpRx0LEMinTemp[2]));
                DebugMessageRx0("9. Lane3 LE Diff", (g_pucDpRx0LEMaxTemp[3] - g_pucDpRx0LEMinTemp[3]));
                DebugMessageRx0("9. Lane0 LE Min", g_pucDpRx0LEMinTemp[0]);
                DebugMessageRx0("9. Lane1 LE Min", g_pucDpRx0LEMinTemp[1]);
                DebugMessageRx0("9. Lane2 LE Min", g_pucDpRx0LEMinTemp[2]);
                DebugMessageRx0("9. Lane3 LE Min", g_pucDpRx0LEMinTemp[3]);
                DebugMessageRx0("9. Lane0 Tap0 Diff", (g_pucDpRx0Tap0MaxTemp[0] - g_pucDpRx0Tap0MinTemp[0]));
                DebugMessageRx0("9. Lane1 Tap0 Diff", (g_pucDpRx0Tap0MaxTemp[1] - g_pucDpRx0Tap0MinTemp[1]));
                DebugMessageRx0("9. Lane2 Tap0 Diff", (g_pucDpRx0Tap0MaxTemp[2] - g_pucDpRx0Tap0MinTemp[2]));
                DebugMessageRx0("9. Lane3 Tap0 Diff", (g_pucDpRx0Tap0MaxTemp[3] - g_pucDpRx0Tap0MinTemp[3]));
                DebugMessageRx0("9. Lane0 Tap0 Max", g_pucDpRx0Tap0MaxTemp[0]);
                DebugMessageRx0("9. Lane1 Tap0 Max", g_pucDpRx0Tap0MaxTemp[1]);
                DebugMessageRx0("9. Lane2 Tap0 Max", g_pucDpRx0Tap0MaxTemp[2]);
                DebugMessageRx0("9. Lane3 Tap0 Max", g_pucDpRx0Tap0MaxTemp[3]);
                DebugMessageRx0("9. FLD Band", ScalerGetByte(PB_BF_LANE0_A_CDR_02));
                DebugMessageRx0("9. Best FLD Band", ScalerGetByte(PB_BE_LANE0_A_CDR_01));
                DebugMessageRx0("9. D10.2 Counter", g_usDpRx0ClockCount);
                DebugMessageRx0("9. D10.2 Counter1", g_usDpRx0ClockCount1);
                DebugMessageRx0("9. Lane0 Tap0 Diff 2", (g_pucDpRx0Tap0MaxTemp2[0] - g_pucDpRx0Tap0MinTemp2[0]));
                DebugMessageRx0("9. Lane1 Tap0 Diff 2", (g_pucDpRx0Tap0MaxTemp2[1] - g_pucDpRx0Tap0MinTemp2[1]));
                DebugMessageRx0("9. Lane2 Tap0 Diff 2", (g_pucDpRx0Tap0MaxTemp2[2] - g_pucDpRx0Tap0MinTemp2[2]));
                DebugMessageRx0("9. Lane3 Tap0 Diff 2", (g_pucDpRx0Tap0MaxTemp2[3] - g_pucDpRx0Tap0MinTemp2[3]));
                DebugMessageRx0("9. Lane0 Tap0 Max 2", g_pucDpRx0Tap0MaxTemp2[0]);
                DebugMessageRx0("9. Lane1 Tap0 Max 2", g_pucDpRx0Tap0MaxTemp2[1]);
                DebugMessageRx0("9. Lane2 Tap0 Max 2", g_pucDpRx0Tap0MaxTemp2[2]);
                DebugMessageRx0("9. Lane3 Tap0 Max 2", g_pucDpRx0Tap0MaxTemp2[3]);
                DebugMessageRx0("9. Best FLD Band", ScalerGetByte(PB_BE_LANE0_A_CDR_01));
                DebugMessageRx0("9. TP2 Check Result", g_ucDpRx0EQCRC);
                DebugMessageRx0("9. DP Requeset", ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x06));
                DebugMessageRx0("9. DP Requeset", ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x07));
                DebugMessageRx0("9. Lane0 Tap1 Max", ScalerGetByte(P17_A5_L0_INIT_3));
                DebugMessageRx0("9. Lane1 Tap1 Max", ScalerGetByte(P17_B5_L1_INIT_3));
                DebugMessageRx0("9. Lane2 Tap1 Max", ScalerGetByte(P17_C5_L2_INIT_3));
                DebugMessageRx0("9. Lane3 Tap1 Max", ScalerGetByte(P17_D5_L3_INIT_3));
                */

                SET_DP_RX0_AUX_MANUAL_MODE();

                if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
                {
                    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);
                    CLR_DP_RX0_NORMAL_LINK_TRAINING_SETPHY_FINISH();

                    ScalerDpRx0ScrambleSetting();
                }

                SET_DP_RX0_AUX_AUTO_MODE();

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
                ScalerSyncDpSecDataResetProc(_D0_INPUT_PORT);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                {
                    // Need to delay 3 Frames totally after Secondary Data Block Reset
                    ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);
                }
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                {
                    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);
                }

                if((ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
                   (ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
                {
                    return _FALSE;
                }

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
                CLR_DP_RX_D0_MARGIN_LINK_HBR2();
#endif
                return _TRUE;
            }
            else
            {
                DebugMessageRx0("7. DP Rebuild PHY Fail", 0);

                SET_DP_RX0_AUX_MANUAL_MODE();

                if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS)
                {
                    ScalerDpRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);

                    ScalerDpRx0HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    ScalerDpRx0Hdcp2ResetProc();
#endif
                }
                else if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS)
                {
                    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_STATUS_FAIL);

                    SET_DP_RX0_AUX_AUTO_MODE();

                    return _TRUE;
                }

                SET_DP_RX0_AUX_AUTO_MODE();
            }

            break;

        case _DP_LINK_TRAINING_NONE:

            if(GET_DP_RX0_VALID_VIDEO_CHECK() == _TRUE)
            {
                ScalerDpRx0ValidSignalDetection();

                DebugMessageRx0("7. VBIOS Check !!!!!!!", GET_DP_RX0_FAKE_LINK_TRAINING());
            }

            break;

        default:

            break;
    }

    if(GET_DP_RX0_VALID_VIDEO_CHECK() == _TRUE)
    {
        CLR_DP_RX0_VALID_VIDEO_CHECK();
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Change Dp Scramble Seed
// Input Value  : None
// Output Value : False --> Change Scrmable Seed Finish
//--------------------------------------------------
bit ScalerDpRx0ChangeSrambleSeed(void)
{
#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)

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
}

#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : VBIOS ASSR Detect
// Input Value  : bMSACheckResult
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpRx0VbiosAssrCheck(bit bMSACheckResult)
{
    SET_DP_RX0_AUX_MANUAL_MODE();

    if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
       (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
    {
        if(bMSACheckResult == _TRUE)
        {
            if(ScalerGetBit(PB_07_SCRAMBLE_CTRL, _BIT4) == _BIT4)
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, _BIT0);
            }
            else
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, 0x00);
            }
        }
        else
        {
            // Set Scramble Seed = Default 0xFFFF
            ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);

            ScalerDpRx0SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, 0x00);
        }
    }
    else
    {
        bMSACheckResult = _FALSE;
    }

    SET_DP_RX0_AUX_AUTO_MODE();

    return bMSACheckResult;
}
#endif

//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : None
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDpRx0ScanInputPort(void)
{
    if(GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _SOURCE_NONE;
    }

    // 2nd Scramble Setting Sync
    ScalerDpRx0ScrambleSetting();

    if(ScalerDpRx0HdcpCheck() == _FALSE)
    {
        DebugMessageRx0("7. DP HDCP Check Fail", 0);

        ScalerDpRx0CpIRQ(_DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

#if(_DP_LONG_HPD_AFTER_CPIRQ_SUPPORT == _ON)
        ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
#endif

        return _SOURCE_NONE;
    }

    if(ScalerDpRx0GetVideoStream() == _FALSE)
    {
        DebugMessageRx0("7. DP Video Stream Fail", 0);

        return _SOURCE_NONE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x07) & _BIT7) == _BIT7)
    {
        SET_DP_FREESYNC_ENABLED();
    }
    else
    {
        CLR_FREESYNC_ENABLED();
    }
#endif

    if(ScalerDpRx0MSACheck() == _FALSE)
    {
        DebugMessageRx0("7. DP MSA Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx0GetVideoInfo() == _FALSE)
    {
        DebugMessageRx0("7. DP Get Video Info Fail", 0);

        return _SOURCE_NONE;
    }
    else
    {
        ScalerDpRx0SetColorInfo();
    }

    if(ScalerDpRx0DisplayFormatSetting() == _FALSE)
    {
        DebugMessageRx0("7. DP Display Format Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx0StreamClkRegenerate() == _FALSE)
    {
        DebugMessageRx0("7. DP SteamClk Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx0FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
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

            ScalerDpRx0AdjustVsyncDelay();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if((ScalerSyncCheckUrgentEvent() == _TRUE))
            {
                return _SOURCE_NONE;
            }
#endif

            if(ScalerDpRx0FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
            {
#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if((ScalerSyncCheckUrgentEvent() == _TRUE))
                {
                    return _SOURCE_NONE;
                }
#endif

                ScalerDpRx0AdjustVsyncDelay();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if((ScalerSyncCheckUrgentEvent() == _TRUE))
                {
                    return _SOURCE_NONE;
                }
#endif

                if(ScalerDpRx0FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
                {
                    DebugMessageRx0("7. DP Fifo Fail", 0);

                    return _SOURCE_NONE;
                }
            }
        }
    }

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);

#if(_DP_FREESYNC_SUPPORT == _ON)
    // Measurement Enable for On-Line VFreq check
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);
#endif

    ScalerSetBit(PB5_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

#if(_AUDIO_SUPPORT == _ON)
    // Enable Audio Channel
    ScalerAudioDpAudioEnable(_ENABLE, _D0_INPUT_PORT);
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    ScalerDpRx0InfoFrameRSV0Initial();
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    ScalerFreeSyncDpRx0GetSPDVfreqMaxMin();
#endif

#if((_DP_HDR10_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
    ScalerDpRx0SwitchHDR10CmpAudioInfo();
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    ScalerDpRx0TimingInfoBackup();
#endif

    DebugMessageRx0("Source DP Rx0 Found", 0);

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    SET_DP_RX0_SOURCE_TYPE_JUDGE();
#endif

    return _SOURCE_DP;
}

//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : None
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpRx0StableDetect(void)
{
#if(_DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER == _ON)
    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
#else
    if((ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
       (ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
#endif
    {
        DebugMessageRx0("7. DP Power Down", 0);

        return _FALSE;
    }

    if((ScalerDpRx0CDRCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE) ||
       (ScalerDpRx0AlignCheck() == _FALSE) ||
       (ScalerDpRx0DecodeCheck() == _FALSE) ||
       ((ScalerDpRx0DFECheck() == _FALSE) && (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE)))
    {
        DebugMessageRx0("7. DP Link Fail", 0);

        return _FALSE;
    }

    if(ScalerDpRx0GetVideoStream() == _FALSE)
    {
        DebugMessageRx0("7. DP Video Stream Fail", 0);

        return _FALSE;
    }

    if(ScalerDpRx0MiscCheck() == _FALSE)
    {
        DebugMessageRx0("7. DP Misc Change", 0);

        return _FALSE;
    }

    if(ScalerDpRx0FifoCheck(_DP_FIFO_POLLING_CHECK) == _FALSE)
    {
        DebugMessageRx0("7. Fifo Under/Overflow", 0);

        return _FALSE;
    }

    if(ScalerDpRx0MSAActiveChange() == _TRUE)
    {
        DebugMessageRx0("7. MSA Timing Change", 0);

        return _FALSE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(ScalerDpRx0GetFREESYNCStatusChange() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Clear CPIRQ Flag
    ScalerDpRx0CheckHdcpCpirqStatus();

    ScalerDpRx0CrcCalculate();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Dp HotPlug Event
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType)
{
    if((enumHpdType > _DP_HPD_LOW) && (ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _FALSE))
    {
        return;
    }

    // If the priority of enumHpdType is higher
    if(enumHpdType < GET_DP_RX0_HOTPLUG_ASSERT_TYPE())
    {
        SET_DP_RX0_HOTPLUG_ASSERT_TYPE(enumHpdType);
    }
}

//--------------------------------------------------
// Description  : DP Adjust Vsync Delay
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AdjustVsyncDelay(void)
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
        ulBStoVSDelayDeltaOverflow = (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 270UL) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(0)) / 256;

        DebugMessageRx0("7. Fifo Overflow --> nVidia Case", ulBStoVSDelayDeltaOverflow);
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
        ulBStoVSDelayDeltaUnderflow = (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 270) * 2) / ((DWORD)GET_INPUT_PIXEL_CLK());

        DebugMessageRx0("7. Fifo Underflow --> QD882 Case", ulBStoVSDelayDeltaUnderflow);
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

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check VGIP VS bypass for DP
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpRx0CheckVgipVsBypass(void)
{
    // Get Hstart
    ScalerRead(PB5_43_MN_DPF_HST_M, 2, &pData[0], _AUTOINC);

    // Get Vstart
    ScalerRead(PB5_4B_MN_DPF_VST_M, 2, &pData[2], _AUTOINC);

    // Check for nVedia 2560x1440@144Hz timing (reduced blanking)
    if((PDATA_WORD(0) < _VGIP_IH_CAPTURE_MIN_VALUE) ||
       (PDATA_WORD(1) <= _VGIP_IV_CAPTURE_MIN_VALUE))
    {
        DebugMessageRx0("DP RX0 VGIP VS Bypass Mode", PDATA_WORD(0));

        return _TRUE;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetNoVideoStreamIRQ(bit bEn)
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
void ScalerDpRx0DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus)
{
    pData[0] = ScalerGetByte(PB7_D0_AUX_MODE_SET);

    SET_DP_RX0_AUX_MANUAL_MODE();

    if(enumDpResetStatus == _DP_DPCD_LINK_STATUS_INITIAL)
    {
        // Set DPCD 00600h to 0x01
        ScalerDpRx0SetDpcdBitValue(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x04, 0x80);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x05, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x06, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x07, 0x00);

    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    CLR_DP_RX0_BACKUP_PD_LINK_STATUS_FLG();

    if((pData[0] & _BIT1) == _BIT1)
    {
        SET_DP_RX0_AUX_AUTO_MODE();
    }
}
//--------------------------------------------------
// Description  : DP BS to VS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
DWORD ScalerDpRx0GetBStoVSDelay(void)
{
    DWORD ulVFrontPorch = 0;
    DWORD ulHFrontPorch = 0;
    WORD usFifoOffset = 0;

    // Get Htotal
    ScalerRead(PB6_08_MSA_HTT_0, 2, &pData[2], _AUTOINC);

    // VFrontPorch = 3 * Htotal * (Link Clk / Stream CLK)
    ulVFrontPorch = ((DWORD)GET_DP_RX0_VFRONT_PORCH()) * ((DWORD)PDATA_WORD(1) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) *
                    ((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 270) / 256;

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
    ulHFrontPorch = (((DWORD)(PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(4))) * (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_INPUT_PIXEL_CLK()));

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
    usFifoOffset = (WORD)(((DWORD)usFifoOffset) * (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_INPUT_PIXEL_CLK()));

    return ((ulVFrontPorch + ulHFrontPorch + (DWORD)usFifoOffset) / 2);
}
//--------------------------------------------------
// Description  : Initial Setting for DP
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport)
{
    ScalerDpRx0AuxPowerOnInitial();

    ScalerDpRx0DpcdInitial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumFreeSyncSupport);

    // Must be initialized "AFTER DPCD setting" to avoid entering interruption unexpectively
    ScalerDpRx0AuxIntInitial();

    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    SET_DP_RX0_FAKE_LINK_TRAINING();

    SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
    SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);
    SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

    SET_DP_RX0_HDCP_MODE_BACKUP(_HDCP_14);

    // _ERROR_PRONE_CODE
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_EMBEDDED)
    ScalerDpRx0SetDpLaneMapping(_TYPE_C_PIN_ASSIGNMENT_C, _TYPE_C_ORIENTATION_UNFLIP);
#endif
}

//--------------------------------------------------
// Description  : DP Margin Link Check
// Input Value  : None
// Output Value : _TRUE : Link ok ; _FALSE : Margin Link
//--------------------------------------------------
bit ScalerDpRx0MarginLinkCheck(void)
{
    switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00))
    {
        case _DP_LINK_HBR2:

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
            if((ScalerDpRx0DFECheck() == _TRUE) &&
               (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               (ScalerDpRx0LaneBsCheck() == _TRUE) &&
               (ScalerDpRx0DecodeErrorCountCheck(_DP_HBR2_MARGIN_LINK_TIME_CRITERIA, _DP_HBR2_MARGIN_LINK_ERROR_CRITERIA) == _FALSE))
            {
                if((ScalerDpRx0DFECheck() == _TRUE) &&
                   (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
                   (ScalerDpRx0LaneBsCheck() == _TRUE))
                {
                    if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
                    {
                        SET_DP_RX_D0_MARGIN_LINK_HBR2();
                        return _FALSE;
                    }
                }
            }
#else
            return _TRUE;
#endif
            break;

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0LinkStatusIRQ(void)
{
    SET_DP_RX0_AUX_MANUAL_MODE();

    if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_FAIL) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
    {
        ScalerDpRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_RESET);

        SET_DP_RX0_AUX_AUTO_MODE();

        ScalerDpRx0HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        ScalerDpRx0Hdcp2ResetProc();
#endif

        if((ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
           (ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_WD_TIMER_INT_SUPPORT == _ON))
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_RX0_HDCP2_SKE);
#endif

            ScalerDpRx0HpdIrqAssert();
        }
    }

    SET_DP_RX0_AUX_AUTO_MODE();
}

//-------------------------------------------------------
// Description  : Set Aux Diff mode or Single-eneded mode
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpRx0AuxSet(void)
{
    if(GET_DP_AUX_DIFF_MODE() == _FALSE)
    {
        // Set TX VLDO = 1.1V
        ScalerSetBit(PB7_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_AUX_SWING_1100_MV << 4));

        // Open AUX ADJR_P
        ScalerSetBit(PB7_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Rx Common Mode from 3.3V
        ScalerSetBit(PB7_60_DIG_TX_04, ~_BIT5, _BIT5);

        // [5]Enable Single-Ended Mode, [4:3]Aux Vth-->50mV, [0]Aux 50ohm auto K(Enable Big_Z0_P)
        ScalerSetByte(PB7_62_AUX_2, 0x29);

        // [4]Enable Big_Z0_N, [3:0]Open ADJR_N
        ScalerSetBit(PB7_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    }
    else
    {
        // Set TX VLDO = 1.1V
        ScalerSetBit(PB7_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_AUX_SWING_1100_MV << 4));

        // Rx Common Mode from 3.3V
        ScalerSetBit(PB7_60_DIG_TX_04, ~_BIT5, _BIT5);

        // [5]Disable Single-Ended Mode, [4:3]Aux Vth-->50mV, [0]Aux 50ohm auto K(Enable Big_Z0_P)
        ScalerSetByte(PB7_62_AUX_2, 0x09);

        // [4]Enable Big_Z0_N
        ScalerSetBit(PB7_66_AUX_6, ~_BIT4, _BIT4);

        // AUX RX0 P Channel Resistance Setting
        ScalerSetBit(PB7_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());

        // AUX RX0 N Channel Resistance Setting
        ScalerSetBit(PB7_66_AUX_6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());
    }
}

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check 8b10b Error Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx0DecodeErrorCountCheck(WORD usTimeCriteria, BYTE ucErrorCriteria)
{
    ScalerDpRx0DecodeErrorCountReset();

    ScalerTimerDelayXms(usTimeCriteria);

    switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_ONE_LANE:

            if(ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE0) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_TWO_LANE:

            if((ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE0) == _TRUE) &&
               (ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE1) == _TRUE))
            {
                return _TRUE;
            }

            break;

        case _DP_FOUR_LANE:
        default:

            if((ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE0) == _TRUE) &&
               (ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE1) == _TRUE) &&
               (ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE2) == _TRUE) &&
               (ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE3) == _TRUE))
            {
                return _TRUE;
            }

            break;
    }

    DebugMessageRx0("7. DP Error Count Fail", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description : Measure 8b10b Error Count Per Lane
// Input Value  : DP Lane
// Output Value : True --> locked; False --> unlocked
//--------------------------------------------------
bit ScalerDpRx0DecodeErrorCountLaneMeasure(BYTE ucErrorCriteria, BYTE ucDpRx0LaneNumber)
{
    WORD usErrorCountLaneMeasure = 0;

    // Select Lane
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (ucDpRx0LaneNumber << 3));

    usErrorCountLaneMeasure = ((((WORD)ScalerGetByte(PB_0B_BIST_PATTERN3)) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    if(usErrorCountLaneMeasure > ucErrorCriteria)
    {
        DebugMessageRx0("DP Lane", ucDpRx0LaneNumber);
        DebugMessageRx0("DP Lane Burst Error", usErrorCountLaneMeasure);

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : Check Lane BS
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx0LaneBsCheck(void)
{
    // Detect Enable
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT3, 0x00);
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT3, _BIT3);

    // Delay for 8192 x 10 x 8 x 2 / 1.62G = 809us
    DELAY_XUS(850);

    // Check Lane Bs
    if(ScalerGetBit(PB_00_HD_DP_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpRx0PSPreDetect(void)
{
    // Back to noraml for DP PHY CTS
    if(GET_DP_RX0_PHY_CTS_FLG() == _TRUE)
    {
        return _TRUE;
    }

    if(GET_DP_RX0_VALID_VIDEO_CHECK() == _TRUE)
    {
        DebugMessageRx0("7. Valid Video Check", 0);

        return _TRUE;
    }

    if(GET_DP_RX0_PS_AUX_TOGGLE() == _TRUE)
    {
        DebugMessageRx0("7. Power Saving Aux Handshake", 0);

        return _TRUE;
    }

    if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        DebugMessageRx0("7. Normal Link Training under Fake Power Saving Case", 0);

        return _TRUE;
    }

    if(((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) &&
        ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
         (ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))) ||
       (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
    {
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))

        if(ScalerAudioGetDigitalAudioSource(_D0_INPUT_PORT) == _DIGITAL_AUDIO_SOURCE_DP)
        {
            DebugMessageAudio("00. DP Power Saving Audio : Idle Pattern Case", ScalerAudioGetDigitalAudioSource(_D0_INPUT_PORT));
            return _TRUE;
        }
#endif
        DebugMessageRx0("7. Idle Pattern Case", 0);

        return _TRUE;
    }

    return _FALSE;
}

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
//--------------------------------------------------
// Description  : Lane Swap
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDpAltModeLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation)
{
    // AUX Setting
    switch(enumPinAssignment)
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:

            // Configure to DP 4 Lane
            ScalerSetBit(P1A_00_COMBO_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // reg_usb3_sel = 0 -> DP Mode Selection for DPHY
            ScalerSetBit(P1C_24_DPHY_2, ~_BIT4, 0x00);

            if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // Pin 17 AUX-P Pull High / Pin 15 AUX-N Pull Low
                ScalerPinshareRx0TypeCPinAssert(_TYPE_C_ORIENTATION_UNFLIP);

                // Disable Aux APHY Swap
                ScalerSetBit(PB7_66_AUX_6, ~_BIT7, 0x00);
            }
            else
            {
                // Pin 17 AUX-P Pull Low / Pin 15 AUX-N Pull High
                ScalerPinshareRx0TypeCPinAssert(_TYPE_C_ORIENTATION_FLIP);

                // Enable Aux APHY Swap
                ScalerSetBit(PB7_66_AUX_6, ~_BIT7, _BIT7);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_D:

            // reg_usb3_sel = 1 -> USB3 Mode Selection for DPHY
            ScalerSetBit(P1C_24_DPHY_2, ~_BIT4, _BIT4);

            if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // Pin 17 AUX-P Pull High / Pin 15 AUX-N Pull Low
                ScalerPinshareRx0TypeCPinAssert(_TYPE_C_ORIENTATION_UNFLIP);

                // Disable Aux APHY Swap
                ScalerSetBit(PB7_66_AUX_6, ~_BIT7, 0x00);

                // Configure to 2 Lane DP (Lane2/3) + 2 Lane U3 (Lane0/1)
                ScalerSetBit(P1A_00_COMBO_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

                // reg_usb3_lane_sel = 0 -> Select Lane0 as U3
                ScalerSetBit(P1C_24_DPHY_2, ~_BIT5, 0x00);
            }
            else
            {
                // Pin 17 AUX-P Pull Low / Pin 15 AUX-N Pull High
                ScalerPinshareRx0TypeCPinAssert(_TYPE_C_ORIENTATION_FLIP);

                // Enable Aux APHY Swap
                ScalerSetBit(PB7_66_AUX_6, ~_BIT7, _BIT7);

                // Configure to 2 Lane DP (Lane0/1) + 2 Lane U3 (Lane2/3)
                ScalerSetBit(P1A_00_COMBO_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

                // reg_usb3_lane_sel = 1 -> Select Lane1 as U3
                ScalerSetBit(P1C_24_DPHY_2, ~_BIT5, _BIT5);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_E:

            // Configure to DP 4 Lane
            ScalerSetBit(P1A_00_COMBO_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // reg_usb3_sel = 0 -> DP Mode Selection for DPHY
            ScalerSetBit(P1C_24_DPHY_2, ~_BIT4, 0x00);

            if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // Pin 17 AUX-P Pull Low / Pin 15 AUX-N Pull High
                ScalerPinshareRx0TypeCPinAssert(_TYPE_C_ORIENTATION_FLIP);

                // Enable Aux APHY Swap
                ScalerSetBit(PB7_66_AUX_6, ~_BIT7, _BIT7);
            }
            else
            {
                // Pin 17 AUX-P Pull High / Pin 15 AUX-N Pull Low
                ScalerPinshareRx0TypeCPinAssert(_TYPE_C_ORIENTATION_UNFLIP);

                // Disable Aux APHY Swap
                ScalerSetBit(PB7_66_AUX_6, ~_BIT7, 0x00);
            }

            break;

        default:
        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            // Configure to USB 4 Lane
            ScalerSetBit(P1A_00_COMBO_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // reg_usb3_sel = 1 -> USB3 Mode Selection for DPHY
            ScalerSetBit(P1C_24_DPHY_2, ~_BIT4, _BIT4);

            // Pin 15/17 AUX-P Pull/Down Disable
            ScalerPinshareRx0TypeCPinAssert(_TYPE_C_ORIENTATION_NONE);

            // Disable Aux APHY Swap
            ScalerSetBit(PB7_66_AUX_6, ~_BIT7, 0x00);

            if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // reg_usb3_lane_sel = 0 -> Select Lane0 as U3
                ScalerSetBit(P1C_24_DPHY_2, ~_BIT5, 0x00);
            }
            else
            {
                // reg_usb3_lane_sel = 1 -> Select Lane2 as U3
                ScalerSetBit(P1C_24_DPHY_2, ~_BIT5, _BIT5);
            }

            break;
    }
}
#else
//--------------------------------------------------
// Description  : Set DP Lane Mapping Type
// Input Value  : ucLanetype --> Lane Mapping Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDpLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation)
{
    if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
    {
        if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Lane 0 <--> Lane 2
            // Lane 1 <--> Lane 3
            SET_DP_RX0_PCB_LANE0_MAPPING(_D0_DP_PCB_LANE2_MAPPING);
            SET_DP_RX0_PCB_LANE1_MAPPING(_D0_DP_PCB_LANE3_MAPPING);
            SET_DP_RX0_PCB_LANE2_MAPPING(_D0_DP_PCB_LANE0_MAPPING);
            SET_DP_RX0_PCB_LANE3_MAPPING(_D0_DP_PCB_LANE1_MAPPING);
            SET_DP_RX0_PCB_LANE0_PN_SWAP(!_D0_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX0_PCB_LANE1_PN_SWAP(!_D0_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX0_PCB_LANE2_PN_SWAP(!_D0_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX0_PCB_LANE3_PN_SWAP(!_D0_DP_PCB_LANE3_PN_SWAP);

#if(_D0_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
            // Enable Aux Digital Phy PN Swap
            ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
#else
            // Disable Aux Digital Phy PN Swap
            ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
#endif
        }
        else // Normal Cable Mode
        {
            SET_DP_RX0_PCB_LANE0_MAPPING(_D0_DP_PCB_LANE0_MAPPING);
            SET_DP_RX0_PCB_LANE1_MAPPING(_D0_DP_PCB_LANE1_MAPPING);
            SET_DP_RX0_PCB_LANE2_MAPPING(_D0_DP_PCB_LANE2_MAPPING);
            SET_DP_RX0_PCB_LANE3_MAPPING(_D0_DP_PCB_LANE3_MAPPING);
            SET_DP_RX0_PCB_LANE0_PN_SWAP(_D0_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX0_PCB_LANE1_PN_SWAP(_D0_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX0_PCB_LANE2_PN_SWAP(_D0_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX0_PCB_LANE3_PN_SWAP(_D0_DP_PCB_LANE3_PN_SWAP);

            // Disable Aux Digital Phy PN Swap
            ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
        }
    }
    else
    {
        if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Lane 0 <--> Lane 2
            // Lane 1 <--> Lane 3
            SET_DP_RX0_PCB_LANE0_MAPPING(_D0_DP_PCB_LANE1_MAPPING);
            SET_DP_RX0_PCB_LANE1_MAPPING(_D0_DP_PCB_LANE0_MAPPING);
            SET_DP_RX0_PCB_LANE2_MAPPING(_D0_DP_PCB_LANE3_MAPPING);
            SET_DP_RX0_PCB_LANE3_MAPPING(_D0_DP_PCB_LANE2_MAPPING);
            SET_DP_RX0_PCB_LANE0_PN_SWAP(!_D0_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX0_PCB_LANE1_PN_SWAP(!_D0_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX0_PCB_LANE2_PN_SWAP(!_D0_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX0_PCB_LANE3_PN_SWAP(!_D0_DP_PCB_LANE3_PN_SWAP);

            // Disable Aux Digital Phy PN Swap
            ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
        }
        else // Normal Cable Mode
        {
            SET_DP_RX0_PCB_LANE0_MAPPING(_D0_DP_PCB_LANE3_MAPPING);
            SET_DP_RX0_PCB_LANE1_MAPPING(_D0_DP_PCB_LANE2_MAPPING);
            SET_DP_RX0_PCB_LANE2_MAPPING(_D0_DP_PCB_LANE1_MAPPING);
            SET_DP_RX0_PCB_LANE3_MAPPING(_D0_DP_PCB_LANE0_MAPPING);
            SET_DP_RX0_PCB_LANE0_PN_SWAP(_D0_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX0_PCB_LANE1_PN_SWAP(_D0_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX0_PCB_LANE2_PN_SWAP(_D0_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX0_PCB_LANE3_PN_SWAP(_D0_DP_PCB_LANE3_PN_SWAP);

            // Enable Aux Digital Phy PN Swap
            ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
        }
    }
}
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DPCD HDCP capability
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpRx0CheckHdcpCapability(void)
{
    if(ScalerDpRx0GetDpcdBitInfo(0x06, 0x80, 0x28, _BIT0) == _BIT0)
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        if(ScalerDpRx0GetDpcdBitInfo(0x06, 0x92, 0x1F, _BIT1) == _BIT1)
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
void ScalerDpRx0HdcpHandshakeMonitorEnable(void)
{
    // Clear Read DPCD 68028h INT Flag
    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);

    // Enable Read DPCD 68028h INT
    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT6);

    // Clear HDCP AKSV IRQ
    ScalerSetBit(PB7_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // Enable HDCP AKSV IRQ
    ScalerSetBit(PB7_A5_AUX_RESERVE5, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT6);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Clear Read DPCD 6921Xh INT Flag
    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT3);

    // Enable Read DPCD 6921Xh INT
    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT2);
#endif
}

//--------------------------------------------------
// Description  : Disable HDCP Hanshake Monitoring Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HdcpHandshakeMonitorDisable(void)
{
    // Disable Read DPCD 68028h INT
    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), 0x00);

    // Disable HDCP AKSV IRQ
    ScalerSetBit(PB7_A5_AUX_RESERVE5, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Disable Read DPCD 6921Xh INT
    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), 0x00);
#endif
}

//--------------------------------------------------
// Description  : Disable HDCP Hanshake Monitoring Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HdcpHandshakeMonitorDisable_EXINT0(void) using 1
{
    // Disable Read DPCD 68028h INT
    ScalerSetBit_EXINT(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), 0x00);

    // Disable HDCP AKSV IRQ
    ScalerSetBit_EXINT(PB7_A5_AUX_RESERVE5, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Disable Read DPCD 6921Xh INT
    ScalerSetBit_EXINT(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), 0x00);
#endif
}
#endif // End of #if(_DP_HDCP_ARBITER_SUPPORT == _ON)

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Backup Timing Info for Modern Standby
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0TimingInfoBackup(void)
{
    // Backup Offset Value of Stream Clock
    g_stDpRx0LinkInfo.lStreamClockOffset = ((((SDWORD)ScalerGetBit(PB5_BA_MN_SCLKG_SDM_SUMC_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << 16) |
                                            (((WORD)ScalerGetByte(PB5_BB_MN_SCLKG_SDM_SUMC_M)) << 8) |
                                            (ScalerGetByte(PB5_BC_MN_SCLKG_SDM_SUMC_L))) >> 1;

    // Backup VBs2Bs Delay of Even Field
    g_stDpRx0LinkInfo.ulVBsToBsDelayEven = (((DWORD)ScalerGetBit(PB5_32_EVBLK2VS_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << 16) |
                                           (((WORD)ScalerGetByte(PB5_33_EVBLK2VS_M)) << 8) |
                                           (ScalerGetByte(PB5_34_EVBLK2VS_L));

    // Backup VBs2Bs Delay of Odd Field
    g_stDpRx0LinkInfo.ulVBsToBsDelayOdd = (((DWORD)ScalerGetBit(PB5_35_OVBLK2VS_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << 16) |
                                          (((WORD)ScalerGetByte(PB5_36_OVBLK2VS_M)) << 8) |
                                          (ScalerGetByte(PB5_37_OVBLK2VS_L));
}
#endif

//--------------------------------------------------
// Description  : Read DP Rx Error Count
// Input Value  : DP Input Port
// Output Value : DP 4 Lane Error Count & Valid Flag
//--------------------------------------------------
StructDpRxErrorCount ScalerDpRx0GetErrorCount(void)
{
    StructDpRxErrorCount stDpRxErrorCount;

    if((ScalerDpRx0CDRCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE) ||
       (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE))
    {
        DebugMessageSystem("Rx Fail to Report Valid Error Counter", 0x00);

        switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
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
        switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            case _DP_TWO_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE1);
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            default:
            case _DP_FOUR_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE1);
                stDpRxErrorCount.usDpRxLane2ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE2);
                stDpRxErrorCount.usDpRxLane3ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE3);

                break;
        }
    }

    // Reset Error Counter
    ScalerDpRx0DecodeErrorCountReset();

    return stDpRxErrorCount;
}
#endif // End of #if(_D0_DP_EXIST == _ON)
