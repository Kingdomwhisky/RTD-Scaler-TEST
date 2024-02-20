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
// ID Code      : RL6410_Series_DPRx0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6410_SERIES_DPRX0__

#include "ScalerFunctionInclude.h"

#if(_D0_DP_EXIST == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


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
BYTE g_ucDpRx0AuxAddressBackup;

BYTE g_pucDpRx0LEBound[4];
BYTE g_pucDpRx0Tap1MinTemp[4];
BYTE g_pucDpRx0Tap1Max[4];
BYTE g_pucDpRx0LEMinTemp[4];
BYTE g_pucDpRx0LEMax[4];
BYTE g_ucDpRx0EQCRC;
WORD g_pusDpRx0ClockCount[4];
WORD g_pusDpRx0ClockCount1[4];
BYTE g_ucRx0AuxTemp;
BYTE g_ucRx0AuxTemp_EXINT;
WORD g_usDpRx0Vfrontporch;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
BYTE g_ucDpRx0FakeLTLaneCount;
BYTE g_ucDpRx0FakeLTLaneCountBackUp;
#endif

#if(_DP_TX_SUPPORT == _ON)
bit g_bDpRx0HdcpAksvWritten = 0;
WORD g_usDpRx0HdcpKsvFifoOffset;
StructDPRxHDCPAuthInfo g_stDpRx0HDCPAuthInfo;
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
BYTE g_pucDPRx0Caps[3];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpRx0AuxPowerOnInitial(void);
void ScalerDpRx0AuxIntInitial(void);
void ScalerDpRx0DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
void ScalerDpRx0ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
void ScalerDpRx0RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
void ScalerDpRx0SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue);

bit ScalerDpRx0StreamClkRegenerate(void);
bit ScalerDpRx0HdcpCheck(void);
void ScalerDpRx0PhyCtsTp1SetPhy(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx0PhyCtsTp2SetPhy(void);
void ScalerDpRx0PhyCTS(void);
WORD ScalerDpRx0PhyCtsAction(void);

#if(_DP_LINK_RATE_CHANGE_WO_LT_SUPPORT == _ON)
void ScalerDpRx0LinkRateChangeRebuildPhy(void);
bit ScalerDpRx0LinkRateChange(void);
#endif

bit ScalerDpRx0NormalPreDetect(void);

#if(_DP_MST_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
bit ScalerDpRx0MstToSstStreamClkRegenerate(void);
#endif
#endif

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

    // Aux ps clk from IOSC
    ScalerSetBit(P0_0B_POWER_CTRL, ~(_BIT5 | _BIT4), 0x00);
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

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
    // Clear HDCP AKSV IRQ
    ScalerSetBit(PB7_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // Enable HDCP AKSV IRQ
    ScalerSetBit(PB7_A5_AUX_RESERVE5, ~(_BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT6);
#endif

    // Source Read 022xxh INT
    ScalerSetByte(PB7_B4_AUX_IRQ_ADDR0_MSB, 0x30);
    ScalerSetByte(PB7_B5_AUX_IRQ_ADDR0_MSB1, 0x22);
    ScalerSetByte(PB7_B6_AUX_IRQ_ADDR0_LSB, 0x00);

    // Clear Read DPCD 022xxh INT Flag
    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);

    // Enable Read DPCD 022xxh INT
    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT6);

    // Disable Wildcard IRQ for Error Counter
    ScalerSetBit(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), 0x00);

    // Use Wildcard 3 to DPCD 0x0021xh, LSB 4 Bits Discarded
    ScalerSetByte(PB7_BD_AUX_IRQ_ADDR3_MSB, 0x10);
    ScalerSetByte(PB7_BE_AUX_IRQ_ADDR3_MSB1, 0x02);
    ScalerSetByte(PB7_BF_AUX_IRQ_ADDR3_LSB, 0x10);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
    {
        // Rx0 Clear DPCD 111 IRQ Flag
        ScalerSetBit(PB7_B3_AUX_SPECIAL_IRQ_FLAG, ~_BIT7, _BIT7);

        // Rx0 Enable DPCD 111 IRQ
        ScalerSetBit(PB7_B2_AUX_SPECIAL_IRQ_EN, ~_BIT7, _BIT7);
    }
#endif

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

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _OFF)
#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
    // _BIT1: Repeater,  _BIT0: HDCP Capable
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x03);
#else
    // _BIT1: Repeater,  _BIT0: HDCP Capable
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x01);
#endif
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
    {
        SET_DP_RX0_FREESYNC_SUPPORT(enumFreeSyncSupport);

        if(GET_DP_RX0_FREESYNC_SUPPORT() == _FREESYNC_SUPPORT_ON)
        {
            ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);
        }
        else
        {
            ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);
        }
    }
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
    {
        SET_DP_RX6_FREESYNC_SUPPORT(enumFreeSyncSupport);

        if(GET_DP_RX6_FREESYNC_SUPPORT() == _FREESYNC_SUPPORT_ON)
        {
            ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);
        }
        else
        {
            ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);
        }
    }
#endif
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

    // Set HDCP_Capable and Repeater Bit
    g_pucDPRx0Caps[0] = 0x02;
    g_pucDPRx0Caps[1] = 0x00;
    g_pucDPRx0Caps[2] = (_BIT1 | _DP_RX0_HDCP_2_2_REPEATER_SUPPORT);

    // Load RxCaps to DPCD Table
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), g_pucDPRx0Caps[pData[0]]);
    }
#endif

    if(ScalerGlobalGetIDCode() == _RL6410_VER_B_ID_CODE)
    {
        // Diable DP HDCP Capable
        ScalerDpRx0SetDpcdBitValue(0x06, 0x80, 0x28, ~_BIT0, 0x00);
    }

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
#if((_DP_DPCD_DFP_PRESENT_REF_TO == _DP_TX_EXISTENCE) && (_DP_TX_SUPPORT == _ON))
    // Down Sream Port Present
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x01);
#else
    // Down Sream Port isn't Present
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x00);
#endif

    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x21, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort)
{
    enumDpRxMstPort = enumDpRxMstPort;

    if(enumDpVersion >= _DP_VERSION_1_4)
    {
        // DPCD Capability Field Initial
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

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
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
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D0_DP_LINK_CLK_RATE);
#else
            g_ucDpRx0DPCD02201hValue = _D0_DP_LINK_CLK_RATE;
#endif
        }
        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
        {
            if(_D6_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D6_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D6_DP_LINK_CLK_RATE);
#else
            g_ucDpRx0DPCD02201hValue = _D6_DP_LINK_CLK_RATE;
#endif
        }
#else // Else of #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

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

#endif // End of #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

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

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
        // Branch IEEE OUI
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x00, _DP_1_2_BRANCH_RTK_IEEE_OUI_L);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x01, _DP_1_2_BRANCH_RTK_IEEE_OUI_M);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x02, _DP_1_2_BRANCH_RTK_IEEE_OUI_H);

        // Branch IEEE OUI LSB For DP1.2
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x03, _DP_BRANCH_RTK_ID_STRING_0);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x04, _DP_BRANCH_RTK_ID_STRING_1);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x05, _DP_BRANCH_RTK_ID_STRING_2);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x06, _DP_BRANCH_RTK_ID_STRING_3);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x07, _DP_BRANCH_RTK_ID_STRING_4);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x08, _DP_BRANCH_RTK_ID_STRING_5);

        // Branch HW/FW Version
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x09, _DP_BRANCH_RTK_HW_VERSION);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x0A, _DP_BRANCH_RTK_FW_VERSION_H);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x0B, _DP_BRANCH_RTK_FW_VERSION_L);
#endif

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON)
        // _BIT3:0, Down Stream Port Counter
        pData[0] = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _DP_1_2_DOWN_STREAM_PORT_COUNT));

        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x09, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x80, 0x08);
        ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x03);
#endif

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if((enumDpRxMstPort == _DP_MST_RX0_PORT) || (enumDpRxMstPort == _DP_MST_RX6_PORT))
#else
        if(enumDpRxMstPort == _DP_MST_RX0_PORT)
#endif
        {
            // Down Sream Port Present
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x01);

            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x21, 0x01);
        }
        else
        {
#if((_DP_DPCD_DFP_PRESENT_REF_TO == _DP_TX_EXISTENCE) && (_DP_TX_SUPPORT == _ON))
            // Down Sream Port Present
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x01);
#else
            // Down Sream Port isn't Present
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x00);
#endif

            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x21, 0x00);
        }
#endif
    }
    else if(enumDpVersion == _DP_VERSION_1_2)
    {
        // DPCD Capability Field Initial
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_2);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x00, _DP_VERSION_1_4);
#else
        g_ucDpRx0DPCD02200hValue = _DP_VERSION_1_4;
#endif

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x0E, ~_BIT7, 0x00);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
        {
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
        }
        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
        {
            if(_D6_DP_LINK_CLK_RATE > _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D6_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D6_DP_LINK_CLK_RATE);
#else
            g_ucDpRx0DPCD02201hValue = _D6_DP_LINK_CLK_RATE;
#endif
        }
#else // Else of #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

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

#endif // End of #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

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

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
        // Branch IEEE OUI
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x00, _DP_1_2_BRANCH_RTK_IEEE_OUI_L);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x01, _DP_1_2_BRANCH_RTK_IEEE_OUI_M);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x02, _DP_1_2_BRANCH_RTK_IEEE_OUI_H);

        // Branch IEEE OUI LSB For DP1.2
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x03, _DP_BRANCH_RTK_ID_STRING_0);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x04, _DP_BRANCH_RTK_ID_STRING_1);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x05, _DP_BRANCH_RTK_ID_STRING_2);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x06, _DP_BRANCH_RTK_ID_STRING_3);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x07, _DP_BRANCH_RTK_ID_STRING_4);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x08, _DP_BRANCH_RTK_ID_STRING_5);

        // Branch HW/FW Version
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x09, _DP_BRANCH_RTK_HW_VERSION);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x0A, _DP_BRANCH_RTK_FW_VERSION_H);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x0B, _DP_BRANCH_RTK_FW_VERSION_L);
#endif

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON)
        // _BIT3:0, Down Stream Port Counter
        pData[0] = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _DP_1_2_DOWN_STREAM_PORT_COUNT));

        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x09, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x80, 0x08);
        ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x03);
#endif

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if((enumDpRxMstPort == _DP_MST_RX0_PORT) || (enumDpRxMstPort == _DP_MST_RX6_PORT))
#else
        if(enumDpRxMstPort == _DP_MST_RX0_PORT)
#endif
        {
            // Down Sream Port Present
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x01);

            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x21, 0x01);
        }
        else
        {
#if((_DP_DPCD_DFP_PRESENT_REF_TO == _DP_TX_EXISTENCE) && (_DP_TX_SUPPORT == _ON))
            // Down Sream Port Present
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x01);
#else
            // Down Sream Port isn't Present
            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x00);
#endif

            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x21, 0x00);
        }
#endif
    }
    else
    {
        // DPCD Capability Field Initial
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_1);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x00, _DP_VERSION_1_4);
#else
        g_ucDpRx0DPCD02200hValue = _DP_VERSION_1_4;
#endif

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x0E, ~_BIT7, 0x00);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
        {
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
        }
        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
        {
            if(_D6_DP_LINK_CLK_RATE > _DP_HIGH_SPEED_270MHZ)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D6_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D6_DP_LINK_CLK_RATE);
#else
            g_ucDpRx0DPCD02201hValue = _D6_DP_LINK_CLK_RATE;
#endif
        }
#else // Else of #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

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

#endif // End of #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

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

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
#if(_DP_SINK_VER11_OUI_SUPPORT == _ON)
        // Branch IEEE OUI
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x00, _DP_1_1_BRANCH_RTK_IEEE_OUI_L);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x01, _DP_1_1_BRANCH_RTK_IEEE_OUI_M);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x02, _DP_1_1_BRANCH_RTK_IEEE_OUI_H);
#else
        // Branch IEEE OUI
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x00, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x01, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x02, 0x00);
#endif

        // Branch IEEE OUI LSB For DP1.1
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x03, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x04, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x05, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x06, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x07, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x08, 0x00);

        // Branch HW/FW Version For DP1.1
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x09, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x0A, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x05, 0x0B, 0x00);
#endif

#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON)
        // _BIT3:0, Down Stream Port Counter
        pData[0] = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _DP_1_1_DOWN_STREAM_PORT_COUNT));

        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x09, 0x02);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x80, 0x00);
        ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x01);
#endif

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
#if((_DP_DPCD_DFP_PRESENT_REF_TO == _DP_TX_EXISTENCE) && (_DP_TX_SUPPORT == _ON))
        // Down Sream Port Present
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x01);
#else
        // Down Sream Port isn't Present
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x00);
#endif

        // MST Capability Disable
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x21, 0x00);
#endif
    }

    if((ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) >= _DP_LINK_HBR2) ||
       ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (_D0_DP_LINK_CLK_RATE >= _DP_LINK_HBR2)))
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
}

//--------------------------------------------------
// Description  : Rebuilding DP PHY
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
    WORD usVCOBandDiff = 0;
    WORD usVCOBandScan = 0;
    BYTE pucTap0[4];
    BYTE ucIcp = 0;


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

    // DP Lane Swap Setting
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_LANE3 << 6);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_LANE2 << 4);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_LANE1 << 2);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // [1:0] DP Mac Clock Selection
    ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // DP Lane PN Swap Setting
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, GET_DP_RX0_PCB_LANE3_PN_SWAP() << 7);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, GET_DP_RX0_PCB_LANE2_PN_SWAP() << 6);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, GET_DP_RX0_PCB_LANE1_PN_SWAP() << 5);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, GET_DP_RX0_PCB_LANE0_PN_SWAP() << 4);


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF)

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit(P1D_1B_CMU_01, ~_BIT7, 0x00);

    // [7:4] RX_EN = 4'b0000 --> Disable RX_EN
    // [3:0] CDR_EN = 4'b0000 --> Disable CDR_EN
    ScalerSetByte(P1D_1A_CMU_00, 0x00);

    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT0, _BIT0);

                // [7:6] reg_en_ana_cdr = 4'b0001 --> Enable Lane0 Analog CDR
                ScalerSetBit(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), 0x00);
                ScalerSetBit(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), _BIT6);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT1, _BIT1);

                // [7:6] reg_en_ana_cdr = 4'b0010 --> Enable Lane0 Analog CDR
                ScalerSetBit(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), 0x00);
                ScalerSetBit(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), _BIT7);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT2, _BIT2);

                // [7:6] reg_en_ana_cdr = 4'b0100 --> Enable Lane0 Analog CDR
                ScalerSetBit(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), _BIT6);
                ScalerSetBit(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), 0x00);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT3, _BIT3);

                // [7:6] reg_en_ana_cdr = 4'b1000 --> Enable Lane0 Analog CDR
                ScalerSetBit(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), _BIT7);
                ScalerSetBit(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), 0x00);
            }

            // [4:3] DP MAC Select One Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT0, _BIT0);

                // [6] reg_en_ana_cdr[0] = 1 --> Enable Lane0 Analog CDR
                ScalerSetBit(P1D_2B_KOFFSET_07, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT1, _BIT1);

                // [7] reg_en_ana_cdr[1] = 1 --> Enable Lane1 Analog CDR
                ScalerSetBit(P1D_2B_KOFFSET_07, ~_BIT7, _BIT7);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT2, _BIT2);

                // [6] reg_en_ana_cdr[2] = 1 --> Enable Lane2 Analog CDR
                ScalerSetBit(P1D_2A_KOFFSET_06, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT3, _BIT3);

                // [7] reg_en_ana_cdr[3] = 1 --> Enable Lane3 Analog CDR
                ScalerSetBit(P1D_2A_KOFFSET_06, ~_BIT7, _BIT7);
            }

            if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT0, _BIT0);

                // [6] reg_en_ana_cdr[0] = 1 --> Enable Lane0 Analog CDR
                ScalerSetBit(P1D_2B_KOFFSET_07, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT1, _BIT1);

                // [7] reg_en_ana_cdr[1] = 1 --> Enable Lane1 Analog CDR
                ScalerSetBit(P1D_2B_KOFFSET_07, ~_BIT7, _BIT7);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT2, _BIT2);

                // [6] reg_en_ana_cdr[2] = 1 --> Enable Lane2 Analog CDR
                ScalerSetBit(P1D_2A_KOFFSET_06, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit(P1D_1A_CMU_00, ~_BIT3, _BIT3);

                // [7] reg_en_ana_cdr[3] = 1 --> Enable Lane3 Analog CDR
                ScalerSetBit(P1D_2A_KOFFSET_06, ~_BIT7, _BIT7);
            }

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            // [7:4] Enable Lane0~3 Rx_en
            ScalerSetBit(P1D_1A_CMU_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // [3:0] Enable Lane0~3 CDR_en
            ScalerSetBit(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // [7:6] reg_en_ana_cdr = 4'b1111 --> Enable Lane0~3 Analog CDR
            ScalerSetBit(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerSetBit(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // [4:3] DP MAC Select Four Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }
#else
    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            // [4:3] DP MAC Select One Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            // [4:3] DP MAC Select Four Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }
#endif

    ///////////////////////
    // Frequency Setting //
    ///////////////////////

    // [6] reg_xtal_en = 1'b1 --> Using 27M Xtal
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~_BIT3, _BIT3);

    if(ucDpLinkRate == _DP_LINK_HBR2)
    {
        // [7:5] rate_sel = 3'b000 --> 3~6GHz
        ScalerSetBit(P1D_44_ST_01, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [2:0] SEL_DIV = 3'b000 --> 3~6GHz
        ScalerSetBit(P1D_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // [7:5] rate_sel = 3'b001 --> 1.5~3GHz
        ScalerSetBit(P1D_44_ST_01, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // [2:0] SEL_DIV = 3'b001 --> 1.5~3GHz
        ScalerSetBit(P1D_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    if(ucDpLinkRate == _DP_LINK_RBR)   // RBR
    {
        // Analog CDR Auto FLD Counter
        // 0x2D[1] 0x2E --> ref_conuter = 25
        // 0x2D[0] 0x2F --> cdr_counter = 300
        // 25/300 = 1/12 = 5*(27M/1.62G)
        ScalerSetBit(P1D_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);
        ScalerSetByte(P1D_2E_ANA_CDR_03, 0x18);
        ScalerSetByte(P1D_2F_ANA_CDR_04, 0x2B);
    }
    else
    {
        // Analog CDR Auto FLD Counter
        // 0x2D[1] 0x2E --> ref_conuter = 25
        // 0x2D[0] 0x2F --> cdr_counter = 500
        // 25/500 = 1/20 = 5*(27M/2.7G)
        ScalerSetBit(P1D_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);
        ScalerSetByte(P1D_2E_ANA_CDR_03, 0x18);
        ScalerSetByte(P1D_2F_ANA_CDR_04, 0xF3);
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [4] Enable Comma Detection
    ScalerSetBit(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);

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

    // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit(P1D_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

    // [7:4] RST_N = 4'b0000 = 4'b1111 --> Digital Circuit Reset Toggle
    // [3:0] CDR_RST_N = 4'b0000 --> Disable DCDR
    ScalerSetByte(P1D_3A_TMDS_RESET, 0x00);
    ScalerSetByte(P1D_3A_TMDS_RESET, 0xF0);


    //////////////////
    // ACDR Setting //
    //////////////////

    if(ucDpLinkRate == _DP_LINK_HBR2)
    {
        // [7] reg_sel_CDR_cp = 0 --> Disable CDR Loop's CP (1nF)
        // [6:4] reg_sel_cdr_res = 3'b010 --> Analog CDR Rs = 1.5K
        // [3:0] reg_cdr_cp_in = 4'b0010 --> Analog CDR Icp = 7.5uA
        ScalerSetByte(P1D_31_ANA_CDR_06, 0x22);
    }
    else
    {
        // [7] reg_sel_CDR_cp = 0 --> Disable CDR Loop's CP (1nF)
        // [6:4] reg_sel_cdr_res = 3'b100 --> Analog CDR Rs = 4K
        // [3:0] reg_cdr_cp_in = 4'b0101 --> Analog CDR Icp = 16.5uA
        ScalerSetByte(P1D_31_ANA_CDR_06, 0x45);
    }

    ucIcp = (ScalerGetByte(P1D_31_ANA_CDR_06) & 0x0F);


    /////////////////
    // DFE Setting //
    /////////////////

    // [7:3] Tap_EN = 5'b11111 --> Enable Tap0~4
    ScalerSetBit(P1D_21_CMU_07, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

    // Set DFE Initial
    ScalerDpRx0SetDFEInitial(ucDpLinkRate);

    // [4] en_sumamp_highgain = 0 --> Disable Sumamp High Gain Mode
    ScalerSetBit(P1D_1D_CMU_03, ~_BIT4, 0x00);

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            // LE Peaking = 3GHz
            // [7:5] LE_RLSEL = 3'b000
            // [4:2] LE_ISEL = 3'b011
            ScalerSetBit(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

            break;

        case _DP_LINK_HBR:

            // LE Peaking = 1.7GHz
            // [7:5] LE_RLSEL = 3'b001
            // [4:2] LE_ISEL = 3'b010
            ScalerSetBit(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            break;

        case _DP_LINK_RBR:
        default:

            // LE Peaking = 900MHz
            // [7:5] LE_RLSEL = 3'b011
            // [4:2] LE_ISEL = 3'b000
            ScalerSetBit(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            break;
    }


    //////////////
    // K Offset //
    //////////////

    // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
    ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT5, _BIT5);

    // [6] en_fore_offset --> Toggle Foreground Calibration
    ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);
    ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, 0x00);
    ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);

    // Delay Time us [85,x] Waiting for K Offset
    DELAY_XUS(85);


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit(P1D_1B_CMU_01, ~_BIT7, _BIT7);

    // [7] reg_auto_mode = 1'b1 --> FLD Auto Mode
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

    if(ucDpLinkRate == _DP_LINK_HBR2)
    {
        // [2] reg_rstb_fsm --> FLD Reset
        ScalerSetBit(P1D_2D_ANA_CDR_02, ~_BIT2, 0x00);

        // [1] reg_eqen_manual = 1'b1 --> Enable Adaptation
        ScalerSetBit(P1D_12_ANA_CDR, ~_BIT1, _BIT1);

        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0xDF);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit(P1D_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [85,x] Waiting for DFE Adaptation
        DELAY_XUS(85);

        // Start to Record Max/Min
        ScalerSetBit(P1D_F2_COEF_3, ~_BIT0, _BIT0);

        // Delay Time us [85,x] Waiting for DFE Adaptation
        DELAY_XUS(85);

        // Stop To Record Max/Min
        ScalerSetBit(P1D_F2_COEF_3, ~_BIT0, 0x00);

        // Select to Lane0
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

        // Read Back LE Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[0] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[0] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Select to Lane1
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

        // Read Back LE Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[1] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[1] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Select to Lane2
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

        // Read Back LE Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[2] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[2] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Select to Lane3
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Read Back LE Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[3] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[3] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        g_pucDpRx0LEBound[0] = 20;
        g_pucDpRx0LEBound[1] = 20;
        g_pucDpRx0LEBound[2] = 20;
        g_pucDpRx0LEBound[3] = 20;

        while(((g_pucDpRx0LEMax[0] > 15) && (g_pucDpRx0Tap1Max[0] < 4) && (g_pucDpRx0LEBound[0] > 15)) ||
              ((g_pucDpRx0LEMax[1] > 15) && (g_pucDpRx0Tap1Max[1] < 4) && (g_pucDpRx0LEBound[1] > 15)) ||
              ((g_pucDpRx0LEMax[2] > 15) && (g_pucDpRx0Tap1Max[2] < 4) && (g_pucDpRx0LEBound[2] > 15)) ||
              ((g_pucDpRx0LEMax[3] > 15) && (g_pucDpRx0Tap1Max[3] < 4) && (g_pucDpRx0LEBound[3] > 15)))
        {
            if(g_pucDpRx0Tap1Max[0] < 4)
            {
                g_pucDpRx0LEBound[0]--;
                ScalerSetBit(P1D_A2_L0_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit(P1D_A3_L0_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[0] & _BIT4) << 3));
            }

            if(g_pucDpRx0Tap1Max[1] < 4)
            {
                g_pucDpRx0LEBound[1]--;
                ScalerSetBit(P1D_B2_L1_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[1] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit(P1D_B3_L1_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[1] & _BIT4) << 3));
            }

            if(g_pucDpRx0Tap1Max[2] < 4)
            {
                g_pucDpRx0LEBound[2]--;
                ScalerSetBit(P1D_C2_L2_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[2] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit(P1D_C3_L2_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[2] & _BIT4) << 3));
            }

            if(g_pucDpRx0Tap1Max[3] < 4)
            {
                g_pucDpRx0LEBound[3]--;
                ScalerSetBit(P1D_D2_L3_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[3] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit(P1D_D3_L3_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[3] & _BIT4) << 3));
            }

            // Start to Record Tap0 Max/Min
            ScalerSetBit(P1D_F2_COEF_3, ~_BIT0, _BIT0);

            // Delay Time us [85,x] Waiting for DFE Adaptation
            DELAY_XUS(85);

            // Stop To Record Tap0 Max/Min
            ScalerSetBit(P1D_F2_COEF_3, ~_BIT0, 0x00);

            // Select to Lane0
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

            // Read Back LE Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[0] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[0] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Select to Lane1
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

            // Read Back LE Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[1] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[1] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Select to Lane2
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

            // Read Back LE Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[2] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[2] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Select to Lane3
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Read Back LE Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[3] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[3] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);
        }

        // Disable DFE Adapt
        ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0x00);

        // [1] reg_eqen_manual = 1'b0 --> Disable Adaptation
        ScalerSetBit(P1D_12_ANA_CDR, ~_BIT1, 0x00);

        // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
        ScalerSetBit(P1D_2C_ANA_CDR_01, ~_BIT4, _BIT4);

        // Read Back Tap0
        ScalerSetByte(P1D_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte(P1D_A4_L0_INIT_2, 0x15);
            ScalerSetBit(P1D_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P1D_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(P1D_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte(P1D_B4_L1_INIT_2, 0x15);
            ScalerSetBit(P1D_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P1D_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(P1D_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte(P1D_C4_L2_INIT_2, 0x15);
            ScalerSetBit(P1D_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P1D_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit(P1D_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte(P1D_D4_L3_INIT_2, 0x15);
            ScalerSetBit(P1D_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P1D_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit(P1D_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_DA_L3_INIT_8, ~_BIT0, 0x00);
        }


        //////////////
        // K Offset //
        //////////////

        // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
        ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT5, _BIT5);

        // [6] en_fore_offset --> Toggle Foreground Calibration
        ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);
        ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, 0x00);
        ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);

        // Delay Time us [85,x] Waiting for K Offset
        DELAY_XUS(85);
    }
    else
    {
        // [2] reg_rstb_fsm = 1'b0 --> FLD Reset
        ScalerSetBit(P1D_2D_ANA_CDR_02, ~_BIT2, 0x00);

        // [1] reg_eqen_manual = 1'b1 --> Enable Adaptation
        ScalerSetBit(P1D_12_ANA_CDR, ~_BIT1, _BIT1);

        // Enable LE/Vth/Tap0/Tap1/Tap2
        ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0xC7);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit(P1D_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [300,x] Waiting for DFE Adaptation
        DELAY_XUS(300);

        // Disable Adaptation
        ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0x00);
    }


    /////////////////////
    // FLD Manual Mode //
    /////////////////////

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            g_pusDpRx0ClockCount[0] = 0x2710; // ideal 5.4G
            g_pusDpRx0ClockCount[1] = 0x2710; // ideal 5.4G
            g_pusDpRx0ClockCount[2] = 0x2710; // ideal 5.4G
            g_pusDpRx0ClockCount[3] = 0x2710; // ideal 5.4G

            break;

        case _DP_LINK_HBR:

            g_pusDpRx0ClockCount[0] = 0x1388; // ideal 2.7G
            g_pusDpRx0ClockCount[1] = 0x1388; // ideal 2.7G
            g_pusDpRx0ClockCount[2] = 0x1388; // ideal 2.7G
            g_pusDpRx0ClockCount[3] = 0x1388; // ideal 2.7G

            break;

        default:
        case _DP_LINK_RBR:

            g_pusDpRx0ClockCount[0] = 0xBB8; // ideal 1.62G
            g_pusDpRx0ClockCount[1] = 0xBB8; // ideal 1.62G
            g_pusDpRx0ClockCount[2] = 0xBB8; // ideal 1.62G
            g_pusDpRx0ClockCount[3] = 0xBB8; // ideal 1.62G

            break;
    }

    // [6] reg_adp_en_manual = 1'b0 --> CDR Open Loop
    // [5] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT6 | _BIT5), 0x00);

    // Scan Lane0 Auto FLD + 4
    ScalerSetBit(P1D_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_36_ANA_CDR_11) & 0x7F) + 4));
    ScalerSetBit(P1D_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_37_ANA_CDR_12) & 0x7F) + 4));
    ScalerSetBit(P1D_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_38_ANA_CDR_13) & 0x7F) + 4));
    ScalerSetBit(P1D_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_39_ANA_CDR_14) & 0x7F) + 4));

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    // [6] reg_adp_en_manual = 1'b1 --> Enable VCO Clock Out
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT7 | _BIT6), _BIT6);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();


    //////////////////////////
    //  Scan Auto Band + 4  //
    //////////////////////////

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

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
            usVCOBandScan = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }


    /////////////////////////
    // VCO Band Difference //
    /////////////////////////

    // Scan Lane0~3 Auto FLD
    ScalerSetBit(P1D_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_36_ANA_CDR_11) & 0x7F));
    ScalerSetBit(P1D_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_37_ANA_CDR_12) & 0x7F));
    ScalerSetBit(P1D_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_38_ANA_CDR_13) & 0x7F));
    ScalerSetBit(P1D_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_39_ANA_CDR_14) & 0x7F));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
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
        g_pusDpRx0ClockCount1[_D0_DP_LANE0] = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        usVCOBandDiff = (abs(usVCOBandScan - g_pusDpRx0ClockCount1[_D0_DP_LANE0]) >> 2);
    }
    else
    {
        usVCOBandDiff = 0;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    if(usVCOBandDiff != 0)
    {
        switch(ucDpcdLane & 0x1F)
        {
            case _DP_FOUR_LANE:

                // Lane3 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE3, usVCOBandDiff);

                // Lane2 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE2, usVCOBandDiff);

                // Lane1 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE1, usVCOBandDiff);

                // Lane0 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE0, usVCOBandDiff);

                break;

            case _DP_TWO_LANE:

                // Lane1 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE1, usVCOBandDiff);

                // Lane0 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE0, usVCOBandDiff);

                break;

            default:
            case _DP_ONE_LANE:

                // Lane0 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand(_D0_DP_LANE0, usVCOBandDiff);

                break;
        }
    }

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [5] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~_BIT5, _BIT5);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US();

    if(ucDpLinkRate <= _DP_LINK_HBR)
    {
        // Set Vth Min = 0
        ScalerSetBit(P1D_F9_LIMIT_10, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Vth/Tap0 Adaptation
        ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0x41);
        ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0x41);
        ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0x41);
        ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0x41);
    }

    // [3] reg_en_data_manual_l0 = 1'b1 --> Data from PHY to MAC
    ScalerSetBit(P1D_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    g_pusDpRx0ClockCount[0] = 0;
    g_pusDpRx0ClockCount[1] = 0;
    g_pusDpRx0ClockCount[2] = 0;
    g_pusDpRx0ClockCount[3] = 0;

    // [5] ln_ck_sel = 1'b1 -> DP CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
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
            break;
        }
    }

    if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        g_pusDpRx0ClockCount[0] = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));
    }
    else
    {
        switch(ucDpLinkRate)
        {
            case _DP_LINK_HBR2:

                g_pusDpRx0ClockCount[0] = 0x2710;

                break;

            case _DP_LINK_HBR:

                g_pusDpRx0ClockCount[0] = 0x1388;

                break;

            default:
            case _DP_LINK_RBR:

                g_pusDpRx0ClockCount[0] = 0xBB8;

                break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
}

//--------------------------------------------------
// Description : Initial Signal check
// Input Value  : DP Link Rate
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue)
{
    ucDpLEQScanValue = ucDpLEQScanValue;


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF)

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit(P1D_1B_CMU_01, ~_BIT7, 0x00);

    // [7:4] RX_EN = 4'b0000 --> Disable RX_EN
    // [3:0] CDR_EN = 4'b0000 --> Disable CDR_EN
    ScalerSetByte(P1D_1A_CMU_00, 0x00);

    // [7:4] Enable Lane0~3 Rx_en
    ScalerSetBit(P1D_1A_CMU_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [3:0] Enable Lane0~3 CDR_en
    ScalerSetBit(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:6] reg_en_ana_cdr = 4'b1111 --> Enable Lane0~3 Analog CDR
    ScalerSetBit(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif
    // [4:3] DP MAC Select Four Lane
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));


    ////////////////
    // LE Setting //
    ////////////////

    // [7:6] adapt_mode[1:0] = 2'b11 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 3)
    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetByte(P1D_E0_MODE_TIMER, 0xF2);

    // Tap1 Min is 49
    ScalerSetBit(P1D_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    // LE Max = 18, Initial = 18, Servo Initial = 16
    ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x22);
    ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x22);
    ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x22);
    ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x22);
    ScalerSetByte(P1D_A3_L0_INIT_1, 0xD0);
    ScalerSetByte(P1D_B3_L1_INIT_1, 0xD0);
    ScalerSetByte(P1D_C3_L2_INIT_1, 0xD0);
    ScalerSetByte(P1D_D3_L3_INIT_1, 0xD0);

    // Tap1 Initial Value = 18
    ScalerSetByte(P1D_A5_L0_INIT_3, 0x12);
    ScalerSetByte(P1D_B5_L1_INIT_3, 0x12);
    ScalerSetByte(P1D_C5_L2_INIT_3, 0x12);
    ScalerSetByte(P1D_D5_L3_INIT_3, 0x12);

    // Load Intial DFE Code
    ScalerSetByte(P1D_AA_L0_INIT_8, 0x82);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x82);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x82);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x82);

    ScalerSetByte(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(P1D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0x00);

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            // LE Peaking = 3GHz
            // [7:5] LE_RLSEL = 3'b000
            // [4:2] LE_ISEL = 3'b011
            ScalerSetBit(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

            break;

        case _DP_LINK_HBR:

            // LE Peaking = 1.7GHz
            // [7:5] LE_RLSEL = 3'b001
            // [4:2] LE_ISEL = 3'b010
            ScalerSetBit(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            break;

        case _DP_LINK_RBR:
        default:

            // LE Peaking = 900MHz
            // [7:5] LE_RLSEL = 3'b011
            // [4:2] LE_ISEL = 3'b000
            ScalerSetBit(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            break;
    }
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

    if(ScalerGlobalGetIDCode() >= _RL6410_VER_C_ID_CODE)
    {
        // PLL Input Clock select to Link Clock, Output Clock Select to PLL Clock, Double Buffer.
        ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
    }
    else
    {
        // PLL Input Clock select to XTAL, Output Clock Select to PLL Clock, Double Buffer.
        ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
    }

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

#if(_HW_PLL_EDGE_SELECT_TYPE == _PLL_EDGE_GEN_1_DEFAULT_POSITIVE)
    // Set PLL Edge = Negative
    ScalerSetBit(PB5_C1_MN_SCLKG_PLL_RESERVE, ~_BIT1, _BIT1);
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
        // DE only mode Disable HSync Tracking
        ScalerSetBit(PB5_A7_MN_SCLKG_TRK_CTRL, ~_BIT6, 0x00);
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
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyCtsTp1SetPhy(EnumDpNFCodeRef enumDpNFCodeRef)
{
    BYTE ucIcp = 0;


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

    // DP Lane Swap Setting
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_LANE3 << 6);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_LANE2 << 4);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_LANE1 << 2);
    ScalerSetBit(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // [1:0] DP Mac Clock Selection
    ScalerSetBit(PB_96_DUMMY3, ~(_BIT1 | _BIT0), (g_ucDpRx0PhyCtsCtrl & 0x30) >> 4);

    // DP Lane PN Swap Setting
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT7, GET_DP_RX0_PCB_LANE3_PN_SWAP() << 7);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT6, GET_DP_RX0_PCB_LANE2_PN_SWAP() << 6);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT5, GET_DP_RX0_PCB_LANE1_PN_SWAP() << 5);
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~_BIT4, GET_DP_RX0_PCB_LANE0_PN_SWAP() << 4);


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit(P1D_1B_CMU_01, ~_BIT7, 0x00);

    // [7:4] Rx_en = 4'b0000 -> Disable RX_EN
    // [3:0] CDR_en = 4'b0000 -> Disable CDR_EN
    ScalerSetByte(P1D_1A_CMU_00, 0x00);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
    {
        case 0x10:

            // Lane1 Test, Enable RX_EN/CDR_EN for Lane1
            ScalerSetByte(P1D_1A_CMU_00, 0x22);

            // [7:6] reg_en_ana_cdr = 4'b0010 --> Enable Lane1 Analog CDR
            ScalerSetBit(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), 0x00);
            ScalerSetBit(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), _BIT7);

            break;

        case 0x20:

            // Lane2 Test, Enable RX_EN/CDR_EN for Lane2
            ScalerSetByte(P1D_1A_CMU_00, 0x44);

            // [7:6] reg_en_ana_cdr = 4'b0100 --> Enable Lane2 Analog CDR
            ScalerSetBit(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), _BIT6);
            ScalerSetBit(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), 0x00);

            break;

        case 0x30:

            // Lane3 Test, Enable RX_EN/CDR_EN for Lane3
            ScalerSetByte(P1D_1A_CMU_00, 0x88);

            // [7:6] reg_en_ana_cdr = 4'b1000 --> Enable Lane3 Analog CDR
            ScalerSetBit(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), _BIT7);
            ScalerSetBit(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), 0x00);

            break;

        default:
        case 0x00:

            // Lane0 Test, Enable RX_EN/CDR_EN for Lane0
            ScalerSetByte(P1D_1A_CMU_00, 0x11);

            // [7:6] reg_en_ana_cdr = 4'b0001 --> Enable Lane0 Analog CDR
            ScalerSetBit(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), 0x00);
            ScalerSetBit(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), _BIT6);

            break;
    }

    // [4:3] One Lane Test
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);


    ///////////////////////
    // Frequency Setting //
    ///////////////////////

    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)
    {
        // [7:5] rate_sel = 3'b000 --> 3~6GHz
        ScalerSetBit(P1D_44_ST_01, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [2:0] SEL_DIV = 3'b000 --> 3~6GHz
        ScalerSetBit(P1D_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // [7:5] rate_sel = 3'b001 --> 1.5~3GHz
        ScalerSetBit(P1D_44_ST_01, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // [2:0] SEL_DIV = 3'b001 --> 1.5~3GHz
        ScalerSetBit(P1D_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
    {
        // [3] reg_xtal_en = 1'b1 --> Using 27M Xtal
        ScalerSetBit(P1D_2C_ANA_CDR_01, ~_BIT3, _BIT3);

        if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x00)   // RBR
        {
            // Analog CDR Auto FLD Counter
            // 0x2D[1] 0x2E --> ref_conuter = 25
            // 0x2D[0] 0x2F --> cdr_counter = 300
            // 25/300 = 1/12 = 5*(27M/1.62G)
            ScalerSetBit(P1D_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte(P1D_2E_ANA_CDR_03, 0x18);
            ScalerSetByte(P1D_2F_ANA_CDR_04, 0x2B);
        }
        else
        {
            // Analog CDR Auto FLD Counter
            // 0x2D[1] 0x2E --> ref_conuter = 25
            // 0x2D[0] 0x2F --> cdr_counter = 500
            // 25/500 = 1/20 = 5*(27M/2.7G)
            ScalerSetBit(P1D_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte(P1D_2E_ANA_CDR_03, 0x18);
            ScalerSetByte(P1D_2F_ANA_CDR_04, 0xF3);
        }
    }
    else
    {
        // [3] reg_xtal_en = 1'b0 --> Using D10.2 Clock
        ScalerSetBit(P1D_2C_ANA_CDR_01, ~_BIT3, 0x00);

        // Analog CDR Auto FLD Counter
        // ref_conuter = 125
        // cdr_counter = 250
        // 250/500 = 1/2 = 5*(D10.2_clock / data_rate)
        ScalerSetBit(P1D_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte(P1D_2E_ANA_CDR_03, 0x7C);
        ScalerSetByte(P1D_2F_ANA_CDR_04, 0xF9);
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

    // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit(P1D_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

    // [7:4] RST_N = 4'b0000 = 4'b1111 --> Digital Circuit Reset Toggle
    // [3:0] CDR_RST_N = 4'b0000 --> Disable DCDR
    ScalerSetByte(P1D_3A_TMDS_RESET, 0x00);
    ScalerSetByte(P1D_3A_TMDS_RESET, 0xF0);


    //////////////////
    // ACDR Setting //
    //////////////////

    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)   // HBR2
    {
        // [7] reg_sel_CDR_cp = 0 --> Disable CDR Loop's CP (1nF)
        // [6:4] reg_sel_cdr_res = 3'b010 --> Analog CDR Rs = 1.5K
        // [3:0] reg_cdr_cp_in = 4'b0010 --> Analog CDR Icp = 7.5uA
        ScalerSetByte(P1D_31_ANA_CDR_06, 0x22);
    }
    else
    {
        // [7] reg_sel_CDR_cp = 0 --> Disable CDR Loop's CP (1nF)
        // [6:4] reg_sel_cdr_res = 3'b100 --> Analog CDR Rs = 4K
        // [3:0] reg_cdr_cp_in = 4'b0101 --> Analog CDR Icp = 16.5uA
        ScalerSetByte(P1D_31_ANA_CDR_06, 0x45);
    }

    ucIcp = (ScalerGetByte(P1D_31_ANA_CDR_06) & 0x0F);


    /////////////////
    // DFE Setting //
    /////////////////

    // [7:3] Tap_EN = 5'b11111 --> Enable Tap0~4
    ScalerSetBit(P1D_21_CMU_07, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

    // [4] en_sumamp_highgain = 0 --> Disable Sumamp High Gain Mode
    ScalerSetBit(P1D_1D_CMU_03, ~_BIT4, 0x00);

    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)
    {
        // Set DFE Initial
        ScalerDpRx0SetDFEInitial(_DP_LINK_HBR2);

        // LE Peaking = 3GHz
        // [7:5] LE_RLSEL = 3'b000
        // [4:2] LE_ISEL = 3'b011
        ScalerSetBit(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
    }
    else if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x40)
    {
        // Set DFE Initial
        ScalerDpRx0SetDFEInitial(_DP_LINK_HBR);

        // LE Peaking = 1.7GHz
        // [7:5] LE_RLSEL = 3'b001
        // [4:2] LE_ISEL = 3'b010
        ScalerSetBit(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));
    }
    else
    {
        // Set DFE Initial
        ScalerDpRx0SetDFEInitial(_DP_LINK_RBR);

        // LE Peaking = 900MHz
        // [7:5] LE_RLSEL = 3'b011
        // [4:2] LE_ISEL = 3'b000
        ScalerSetBit(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    }


    //////////////
    // K Offset //
    //////////////

    // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
    ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT5, _BIT5);

    // [6] en_fore_offset --> Toggle Foreground Calibration
    ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);
    ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, 0x00);
    ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);

    // Delay Time us [85,x] Waiting for K Offset
    DELAY_XUS(85);


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit(P1D_1B_CMU_01, ~_BIT7, _BIT7);

    // [7] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

    // [2] reg_rstb_fsm --> FLD Reset
    ScalerSetBit(P1D_2D_ANA_CDR_02, ~_BIT2, 0x00);

    // [1] reg_en_eqen_manual_l0 = 1'b1 --> DFE Adaptation Ready
    ScalerSetBit(P1D_12_ANA_CDR, ~_BIT1, _BIT1);

    // Enable LE/Vth/Tap0-4 Adaptation
    ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0xDF);
    ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0xDF);
    ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0xDF);
    ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0xDF);

    // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
    ScalerSetBit(P1D_2D_ANA_CDR_02, ~_BIT2, _BIT2);

    // Delay Time us [85,x] Waiting for FLD Lock Band
    DELAY_XUS(85);

    // Start to Record Tap0 Max/Min
    ScalerSetBit(P1D_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [85,x] Waiting for DFE Adaptation
    DELAY_XUS(85);

    // Stop To Record Tap0 Max/Min
    ScalerSetBit(P1D_F2_COEF_3, ~_BIT0, 0x00);

    // [1] reg_en_eqen_manual_l0 = 1'b0 --> DFE Adaptation Off
    ScalerSetBit(P1D_12_ANA_CDR, ~_BIT1, 0x00);

    // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~_BIT4, _BIT4);

    // Disable All Adapation Loop
    ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0x00);

    // Read Back Tap0 Max
    ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    // Reload Max Value of Tap0 (Lane0)
    ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetByte(P1D_A4_L0_INIT_2, (ScalerGetByte(P1D_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane1)
    ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetByte(P1D_B4_L1_INIT_2, (ScalerGetByte(P1D_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane2)
    ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetByte(P1D_C4_L2_INIT_2, (ScalerGetByte(P1D_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane3)
    ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetByte(P1D_D4_L3_INIT_2, (ScalerGetByte(P1D_F3_COEF_4) & 0x1F));

    // Reload Tap0
    ScalerSetBit(P1D_AA_L0_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit(P1D_BA_L1_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit(P1D_CA_L2_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit(P1D_DA_L3_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit(P1D_AA_L0_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit(P1D_BA_L1_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit(P1D_CA_L2_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit(P1D_DA_L3_INIT_8, ~_BIT0, 0x00);


    /////////////////////
    // FLD Manual Mode //
    /////////////////////

    // Manually Reload FLD Band
    ScalerSetBit(P1D_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_36_ANA_CDR_11) & 0x7F));
    ScalerSetBit(P1D_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_37_ANA_CDR_12) & 0x7F));
    ScalerSetBit(P1D_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_38_ANA_CDR_13) & 0x7F));
    ScalerSetBit(P1D_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_39_ANA_CDR_14) & 0x7F));

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    // [6] reg_adp_en_manual = 1'b1 --> Use eqen_manual_l0 as DFE Flag
    // [5] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [5] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~_BIT5, _BIT5);

    // Delay Time us [45,x] Waiting for CDR Stable
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x] Waiting for CDR Stable
    DELAY_45US();

    // [3] reg_en_data_manual_l0 = 1'b1 --> Data from PHY to MAC
    ScalerSetBit(P1D_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyCtsTp2SetPhy(void)
{
    BYTE ucBestVCOBand = 0;
    WORD usVCOBandDiff = 0;
    WORD usVCOAutoBandAdd4 = 0;
    BYTE pucTap0[4];
    BYTE ucIcp = (ScalerGetByte(P1D_31_ANA_CDR_06) & 0x0F);


    /////////////
    // Rx Misc //
    /////////////

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit(P1D_1B_CMU_01, ~_BIT7, 0x00);

    // [4] Enable Comma Detection
    ScalerSetBit(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    // [5] Disable De-Scrambling
    ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    // [2] Enable Enhancement Control Mode
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);

    // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit(P1D_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

    // [7:4] RST_N = 4'b0000 = 4'b1111 --> Digital Circuit Reset Toggle
    // [3:0] CDR_RST_N = 4'b0000 --> Disable DCDR
    ScalerSetByte(P1D_3A_TMDS_RESET, 0x00);
    ScalerSetByte(P1D_3A_TMDS_RESET, 0xF0);

    // [4] en_sumamp_highgain = 0 --> Disable Sumamp High Gain Mode
    ScalerSetBit(P1D_1D_CMU_03, ~_BIT4, 0x00);

    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)
    {
        // Set DFE Initial
        ScalerDpRx0SetDFEInitial(_DP_LINK_HBR2);

        // [1] tap1_trans = 1'b0 --> Tap1 is Effective Only on Transition Bits
        ScalerSetBit(P1D_E3_GAIN_2, ~_BIT1, _BIT1);
    }
    else if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x40)
    {
        // Set DFE Initial
        ScalerDpRx0SetDFEInitial(_DP_LINK_HBR);
    }
    else
    {
        // Set DFE Initial
        ScalerDpRx0SetDFEInitial(_DP_LINK_RBR);
    }


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit(P1D_1B_CMU_01, ~_BIT7, _BIT7);

    // [7] reg_auto_mode = 1'b1 --> FLD Auto Mode
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

    // [2] reg_rstb_fsm --> FLD Reset
    ScalerSetBit(P1D_2D_ANA_CDR_02, ~_BIT2, 0x00);

    // [1] reg_en_eqen_manual_l0 = 1'b1 --> DFE Adaptation Enable
    ScalerSetBit(P1D_12_ANA_CDR, ~_BIT1, _BIT1);

    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)
    {
        // Enable LE/Vth/Tap0~4
        ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0xDF);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit(P1D_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [85,x] Waiting for FLD Lock Band
        DELAY_XUS(85);

        // Start to Record Max/Min
        ScalerSetBit(P1D_F2_COEF_3, ~_BIT0, _BIT0);

        // Delay Time us [85,x] Waiting for DFE Adaptation
        DELAY_XUS(85);

        // Stop To Record Max/Min
        ScalerSetBit(P1D_F2_COEF_3, ~_BIT0, 0x00);

        // Select to Lane0
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

        // Read Back LE Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[0] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[0] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Select to Lane1
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

        // Read Back LE Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[1] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[1] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Select to Lane2
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

        // Read Back LE Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[2] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[2] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Select to Lane3
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Read Back LE Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[3] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[3] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

        g_pucDpRx0LEBound[0] = 18;
        g_pucDpRx0LEBound[1] = 18;
        g_pucDpRx0LEBound[2] = 18;
        g_pucDpRx0LEBound[3] = 18;

        while(((g_pucDpRx0LEMax[0] > 15) && (g_pucDpRx0Tap1Max[0] < 4) && (g_pucDpRx0LEBound[0] > 15)) ||
              ((g_pucDpRx0LEMax[1] > 15) && (g_pucDpRx0Tap1Max[1] < 4) && (g_pucDpRx0LEBound[1] > 15)) ||
              ((g_pucDpRx0LEMax[2] > 15) && (g_pucDpRx0Tap1Max[2] < 4) && (g_pucDpRx0LEBound[2] > 15)) ||
              ((g_pucDpRx0LEMax[3] > 15) && (g_pucDpRx0Tap1Max[3] < 4) && (g_pucDpRx0LEBound[3] > 15)))
        {
            if(g_pucDpRx0Tap1Max[0] < 4)
            {
                g_pucDpRx0LEBound[0]--;
                ScalerSetBit(P1D_A2_L0_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit(P1D_A3_L0_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[0] & _BIT4) << 3));
            }

            if(g_pucDpRx0Tap1Max[1] < 4)
            {
                g_pucDpRx0LEBound[1]--;
                ScalerSetBit(P1D_B2_L1_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[1] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit(P1D_B3_L1_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[1] & _BIT4) << 3));
            }

            if(g_pucDpRx0Tap1Max[2] < 4)
            {
                g_pucDpRx0LEBound[2]--;
                ScalerSetBit(P1D_C2_L2_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[2] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit(P1D_C3_L2_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[2] & _BIT4) << 3));
            }

            if(g_pucDpRx0Tap1Max[3] < 4)
            {
                g_pucDpRx0LEBound[3]--;
                ScalerSetBit(P1D_D2_L3_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[3] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit(P1D_D3_L3_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[3] & _BIT4) << 3));
            }

            // Start to Record Tap0 Max/Min
            ScalerSetBit(P1D_F2_COEF_3, ~_BIT0, _BIT0);

            // Delay Time us [85,x] Waiting for DFE Adaptation
            DELAY_XUS(85);

            // Stop To Record Tap0 Max/Min
            ScalerSetBit(P1D_F2_COEF_3, ~_BIT0, 0x00);

            // Select to Lane0
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

            // Read Back LE Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[0] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[0] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Select to Lane1
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

            // Read Back LE Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[1] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[1] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Select to Lane2
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

            // Read Back LE Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[2] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[2] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Select to Lane3
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Read Back LE Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[3] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[3] = (ScalerGetByte(P1D_F3_COEF_4) & 0x1F);
        }

        // [1] reg_en_eqen_manual_l0 = 1'b0 --> DFE Adaptation Off
        ScalerSetBit(P1D_12_ANA_CDR, ~_BIT1, 0x00);

        // Disable DFE Adaptation
        ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0x00);

        // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
        ScalerSetBit(P1D_2C_ANA_CDR_01, ~_BIT4, _BIT4);

        // Read Back Tap0
        ScalerSetByte(P1D_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte(P1D_A4_L0_INIT_2, 0x15);
            ScalerSetBit(P1D_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P1D_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(P1D_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte(P1D_B4_L1_INIT_2, 0x15);
            ScalerSetBit(P1D_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P1D_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(P1D_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte(P1D_C4_L2_INIT_2, 0x15);
            ScalerSetBit(P1D_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P1D_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit(P1D_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte(P1D_D4_L3_INIT_2, 0x15);
            ScalerSetBit(P1D_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(P1D_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit(P1D_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(P1D_DA_L3_INIT_8, ~_BIT0, 0x00);
        }


        /////////////////////
        // Second K Offset //
        /////////////////////

        // [4] en_sumamp_highgain = 1 --> enable Sumamp High Gain Mode
        ScalerSetBit(P1D_1D_CMU_03, ~_BIT4, _BIT4);

        // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
        ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT5, _BIT5);

        // [6] en_fore_offset --> Toggle Foreground Calibration
        ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);
        ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, 0x00);
        ScalerSetBit(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);

        // Delay Time us [85,x] Waiting for DFE Adaptation
        DELAY_XUS(85);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0xC7);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit(P1D_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [300,x] Waiting for FLD Lock Band
        DELAY_XUS(300);

        // [1] reg_en_eqen_manual_l0 = 1'b0 --> DFE Off
        ScalerSetBit(P1D_12_ANA_CDR, ~_BIT1, 0x00);

        // Disable Adaptation
        ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0x00);

        // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
        ScalerSetBit(P1D_2C_ANA_CDR_01, ~_BIT4, _BIT4);
    }


    /////////////////////
    // FLD Manual Mode //
    /////////////////////

    // [6] reg_adp_en_manual = 1'b0 --> CDR Open Loop
    // [5] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT6 | _BIT5), 0x00);

    // Scan Auto FLD + 4
    ScalerSetBit(P1D_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_36_ANA_CDR_11) & 0x7F) + 4));
    ScalerSetBit(P1D_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_37_ANA_CDR_12) & 0x7F) + 4));
    ScalerSetBit(P1D_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_38_ANA_CDR_13) & 0x7F) + 4));
    ScalerSetBit(P1D_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(P1D_39_ANA_CDR_14) & 0x7F) + 4));

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    // [6] reg_adp_en_manual = 1'b1 --> Enable VCO Clock Out
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT7 | _BIT6), _BIT6);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();


    /////////////////////////
    // Scan Auto Band + 4  //
    /////////////////////////

    // Target Freq.
    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x80)
    {
        g_pusDpRx0ClockCount[0] = 0x2710; // 5.4G
    }
    else if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x40)
    {
        g_pusDpRx0ClockCount[0] = 0x1388; // 2.7G
    }
    else
    {
        g_pusDpRx0ClockCount[0] = 0xBB8; // 1.62G
    }

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
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

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
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
    ScalerSetBit(P1D_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_36_ANA_CDR_11) & 0x7F));
    ScalerSetBit(P1D_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_37_ANA_CDR_12) & 0x7F));
    ScalerSetBit(P1D_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_38_ANA_CDR_13) & 0x7F));
    ScalerSetBit(P1D_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P1D_39_ANA_CDR_14) & 0x7F));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
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
        g_pusDpRx0ClockCount1[0] = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        usVCOBandDiff = (abs(usVCOAutoBandAdd4 - g_pusDpRx0ClockCount1[0]) >> 2);

        if(g_pusDpRx0ClockCount1[0] < g_pusDpRx0ClockCount[0])
        {
            switch(g_ucDpRx0PhyCtsCtrl & 0x30)
            {
                default:
                case 0x00: // Lane0 VCO Adjust

                    ucBestVCOBand = (ScalerGetByte(P1D_36_ANA_CDR_11) & 0x7F) + (((g_pusDpRx0ClockCount[0] - g_pusDpRx0ClockCount1[0]) / usVCOBandDiff) + 1);

                    break;

                case 0x10: // Lane1 VCO Adjust

                    ucBestVCOBand = (ScalerGetByte(P1D_37_ANA_CDR_12) & 0x7F) + (((g_pusDpRx0ClockCount[0] - g_pusDpRx0ClockCount1[0]) / usVCOBandDiff) + 1);

                    break;

                case 0x20: // Lane2 VCO Adjust

                    ucBestVCOBand = (ScalerGetByte(P1D_38_ANA_CDR_13) & 0x7F) + (((g_pusDpRx0ClockCount[0] - g_pusDpRx0ClockCount1[0]) / usVCOBandDiff) + 1);

                    break;

                case 0x30: // Lane3 VCO Adjust

                    ucBestVCOBand = (ScalerGetByte(P1D_39_ANA_CDR_14) & 0x7F) + (((g_pusDpRx0ClockCount[0] - g_pusDpRx0ClockCount1[0]) / usVCOBandDiff) + 1);

                    break;
            }
        }
        else
        {
            switch(g_ucDpRx0PhyCtsCtrl & 0x30)
            {
                default:
                case 0x00: // Lane0 VCO Adjust

                    ucBestVCOBand = (ScalerGetByte(P1D_36_ANA_CDR_11) & 0x7F) - ((g_pusDpRx0ClockCount1[0] - g_pusDpRx0ClockCount[0]) / usVCOBandDiff);

                    break;

                case 0x10: // Lane1 VCO Adjust

                    ucBestVCOBand = (ScalerGetByte(P1D_37_ANA_CDR_12) & 0x7F) - ((g_pusDpRx0ClockCount1[0] - g_pusDpRx0ClockCount[0]) / usVCOBandDiff);

                    break;

                case 0x20: // Lane2 VCO Adjust

                    ucBestVCOBand = (ScalerGetByte(P1D_38_ANA_CDR_13) & 0x7F) - ((g_pusDpRx0ClockCount1[0] - g_pusDpRx0ClockCount[0]) / usVCOBandDiff);

                    break;

                case 0x30: // Lane3 VCO Adjust

                    ucBestVCOBand = (ScalerGetByte(P1D_39_ANA_CDR_14) & 0x7F) - ((g_pusDpRx0ClockCount1[0] - g_pusDpRx0ClockCount[0]) / usVCOBandDiff);

                    break;
            }
        }
    }
    else // Measure Fail -> Use Auto FLD Band
    {
        switch(g_ucDpRx0PhyCtsCtrl & 0x30)
        {
            default:
            case 0x00: // Lane0 VCO Adjust

                ucBestVCOBand = (ScalerGetByte(P1D_36_ANA_CDR_11) & 0x7F);

                break;

            case 0x10: // Lane1 VCO Adjust

                ucBestVCOBand = (ScalerGetByte(P1D_37_ANA_CDR_12) & 0x7F);

                break;

            case 0x20: // Lane2 VCO Adjust

                ucBestVCOBand = (ScalerGetByte(P1D_38_ANA_CDR_13) & 0x7F);

                break;

            case 0x30: // Lane3 VCO Adjust

                ucBestVCOBand = (ScalerGetByte(P1D_39_ANA_CDR_14) & 0x7F);

                break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // Manually Reload FLD Band
    ScalerSetBit(P1D_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);
    ScalerSetBit(P1D_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);
    ScalerSetBit(P1D_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);
    ScalerSetBit(P1D_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [5] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(P1D_2C_ANA_CDR_01, ~_BIT5, _BIT5);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US();

    // [3] reg_en_data_manual_l0 = 1'b1 --> Data from PHY to MAC
    ScalerSetBit(P1D_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : DP PHY CTS Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyCTS(void)
{
    // _ERROR_PRONE_CODE
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 25[5] = 0 --> PHY CTS Enable Start
    // RL6410 Version AB
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[2:0]) = 0x01 --> CDR
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[2:0]) = 0x02 --> EQ CRC
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[2:0]) = 0x03 --> PRBS7 Error Counter Reset and Counter Start
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[2:0]) = 0x04 --> PRBS7 Error Counter Read
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[2:0]) = 0x05 --> PHY CTS Disable
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[5:4]) = 00 --> lane0
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[5:4]) = 01 --> lane1
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[5:4]) = 10 --> lane2
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[5:4]) = 11 --> lane3
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[7:6]) = 00 --> RBR
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[7:6]) = 01 --> HBR
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 13[7:6]) = 10 --> HBR2

    // RL6410 Version C
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[2:0]) = 0x01 --> CDR
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[2:0]) = 0x02 --> EQ CRC
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[2:0]) = 0x03 --> PRBS7 Error Counter Reset and Counter Start
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[2:0]) = 0x04 --> PRBS7 Error Counter Read
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[2:0]) = 0x05 --> PHY CTS Disable
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[5:4]) = 00 --> lane0
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[5:4]) = 01 --> lane1
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[5:4]) = 10 --> lane2
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[5:4]) = 11 --> lane3
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[7:6]) = 00 --> RBR
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[7:6]) = 01 --> HBR
    // g_ucDpRx0PhyCtsCtrl(Page0x1D 50[7:6]) = 10 --> HBR2

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

            switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x02) & (_BIT1 | _BIT0))
            {
                case 0x01: // CDR Lock Check

                    if(ucPhyCtsAutoMode != 0x11)
                    {
                        // Link Rate
                        switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00))
                        {
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
                    }

                    break;

                case 0x00:

                    if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, (0x0B + ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4))) >> 4))) != 0x00)
                    {
                        if(ucPhyCtsAutoMode != 0x05) // Error Count Enable
                        {
                            // Error Count Enable
                            ucPhyCtsAutoMode = 0x03;

                            ScalerDpRx0PhyCtsTp2SetPhy();

                            ScalerTimerDelayXms(2);

                            switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, (0x0B + ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, (_BIT5 | _BIT4))) >> 4))))
                            {
                                case 0x03: // PRBS7 Pattern

                                    // PRBS7 Pattern for RBR/HBR
                                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                                    ScalerTimerDelayXms(2);

                                    // Error Count Lock
                                    ucPhyCtsAutoMode = 0x05;

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

                                        for(usTemp = 0; usTemp <= 1000; usTemp++)
                                        {
                                            // [6] reg_adp_en_manual = 1'b0 --> CDR Open Loop
                                            // [5] reg_cp_en_manual = 1'b0 --> CDR Open Loop
                                            ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT6 | _BIT5), 0x00);

                                            // Delay Time us [25,x] Waiting for VCO Stable
                                            DELAY_25US();

                                            // [6] reg_adp_en_manual = 1'b1 --> CDR Close Loop
                                            // [5] reg_cp_en_manual = 1'b1 --> CDR Close Loop
                                            ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

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

            DebugMessageRx0("7. PHY CTS Loop", ScalerGetByte(ScalerDpRx0PhyCtsAction()));

            switch(ScalerGetByte(ScalerDpRx0PhyCtsAction()) & 0x30)
            {
                default:
                case 0x00: // Source Lane0

                    ScalerSetBit(ScalerDpRx0PhyCtsAction(), ~(_BIT5 | _BIT4), _D0_DP_LANE0 << 4);

                    break;

                case 0x10: // Source Lane1

                    ScalerSetBit(ScalerDpRx0PhyCtsAction(), ~(_BIT5 | _BIT4), _D0_DP_LANE1 << 4);

                    break;

                case 0x20: // Source Lane2

                    ScalerSetBit(ScalerDpRx0PhyCtsAction(), ~(_BIT5 | _BIT4), _D0_DP_LANE2 << 4);

                    break;

                case 0x30: // Source Lane3

                    ScalerSetBit(ScalerDpRx0PhyCtsAction(), ~(_BIT5 | _BIT4), _D0_DP_LANE3 << 4);

                    break;
            }

            ScalerRead(ScalerDpRx0PhyCtsAction(), 1, &g_ucDpRx0PhyCtsCtrl, _NON_AUTOINC);

            DebugMessageRx0("7. PHY CTS Loop", g_ucDpRx0PhyCtsCtrl);

            switch(g_ucDpRx0PhyCtsCtrl & 0x07)
            {
                case 0x01: // CDR Lock Check

                    ScalerSetByte(ScalerDpRx0PhyCtsAction(), (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0))); // Clear DP PHY CTS Phase Info

                    ScalerDpRx0PhyCtsTp1SetPhy(_DP_NF_REF_XTAL);

                    if(ScalerDpRx0PhyCtsTp1Check() == _TRUE)
                    {
                        ScalerSetByte(P1D_0D_SDM_02, 0x01);
                    }
                    else
                    {
                        ScalerSetByte(P1D_0D_SDM_02, 0xFF);
                    }

                    break;

                case 0x02: // Symbol Lock Check

                    ScalerSetByte(ScalerDpRx0PhyCtsAction(), (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                    ScalerDpRx0PhyCtsTp2SetPhy();

                    if(ScalerDpRx0PhyCtsTp2Check() == _TRUE)
                    {
                        ScalerSetByte(P1D_0D_SDM_02, 0x01);
                    }
                    else
                    {
                        ScalerSetByte(P1D_0D_SDM_02, 0xFF);
                    }

                    break;

                case 0x03:

                    ScalerSetByte(ScalerDpRx0PhyCtsAction(), (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

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

                            ucIcp = (ScalerGetByte(P1D_31_ANA_CDR_06) & 0x0F);

                            for(usTemp = 0; usTemp <= 1000; usTemp++)
                            {
                                // [6] reg_adp_en_manual = 1'b0 --> CDR Open Loop
                                // [5] reg_cp_en_manual = 1'b0 --> CDR Open Loop
                                ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT6 | _BIT5), 0x00);

                                // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
                                if(ucIcp > 7)
                                {
                                    ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                                }
                                else
                                {
                                    ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
                                }

                                // Delay Time us [25,x] Waiting for VCO Stable
                                DELAY_25US();

                                // [6] reg_adp_en_manual = 1'b1 --> CDR Close Loop
                                // [5] reg_cp_en_manual = 1'b1 --> CDR Close Loop
                                ScalerSetBit(P1D_2C_ANA_CDR_01, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

                                // Delay Time us [45,x] Waiting for VCO Stable
                                DELAY_45US();

                                // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
                                ScalerSetBit(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

                                // Delay Time us [45,x] Waiting for VCO Stable
                                DELAY_45US();

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

                    ScalerSetByte(P1D_0C_SDM_01, 0x00);
                    ScalerSetByte(P1D_0D_SDM_02, 0x00);

                    break;

                case 0x04:

                    ScalerSetByte(ScalerDpRx0PhyCtsAction(), (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                    ScalerTimerDelayXms(10);

                    ScalerSetByte(P1D_0C_SDM_01, ScalerGetByte(PB_0B_BIST_PATTERN3));
                    ScalerSetByte(P1D_0D_SDM_02, ScalerGetByte(PB_0C_BIST_PATTERN4));

                    break;

                case 0x05:

                    // Clear DP PHY CTS Result
                    ScalerSetByte(P1D_0C_SDM_01, 0x00);
                    ScalerSetByte(P1D_0D_SDM_02, 0x00);

                    // Disable PRBS7 Error Detection
                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // Clear DP PHY CTS Control Register
                    ScalerSetByte(ScalerDpRx0PhyCtsAction(), 0x00);

                    CLR_DP_RX0_PHY_CTS_FLG();

                    break;

                default:

                    // Clear DP PHY CTS Control Register
                    ScalerSetBit(ScalerDpRx0PhyCtsAction(), ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                    break;
            }

            if((g_ucDpRx0PhyCtsCtrl & 0x07) != 0x05)
            {
                if(((ScalerGetByte(ScalerDpRx0PhyCtsAction()) & 0x30) >> 4) == _D0_DP_LANE0) // Source Lane0
                {
                    ScalerSetBit(ScalerDpRx0PhyCtsAction(), ~(_BIT5 | _BIT4), _DP_SCALER_LANE0 << 4);
                }
                else if(((ScalerGetByte(ScalerDpRx0PhyCtsAction()) & 0x30) >> 4) == _D0_DP_LANE1) // Source Lane1
                {
                    ScalerSetBit(ScalerDpRx0PhyCtsAction(), ~(_BIT5 | _BIT4), _DP_SCALER_LANE1 << 4);
                }
                else if(((ScalerGetByte(ScalerDpRx0PhyCtsAction()) & 0x30) >> 4) == _D0_DP_LANE2) // Source Lane2
                {
                    ScalerSetBit(ScalerDpRx0PhyCtsAction(), ~(_BIT5 | _BIT4), _DP_SCALER_LANE2 << 4);
                }
                else if(((ScalerGetByte(ScalerDpRx0PhyCtsAction()) & 0x30) >> 4) == _D0_DP_LANE3) // Source Lane3
                {
                    ScalerSetBit(ScalerDpRx0PhyCtsAction(), ~(_BIT5 | _BIT4), _DP_SCALER_LANE3 << 4);
                }

                DebugMessageRx0("7. PHY CTS Loop (Swap Back)", ScalerGetByte(ScalerDpRx0PhyCtsAction()));
            }
            else
            {
                g_ucDpRx0PhyCtsCtrl = 0x00;
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP PHY CTS Action Register
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD ScalerDpRx0PhyCtsAction(void)
{
    if(ScalerGlobalGetIDCode() >= _RL6410_VER_C_ID_CODE)
    {
        return P1D_50_CDR_00;
    }
    else
    {
        return P1D_13_PHY_RESERVED;
    }
}

#if(_DP_LINK_RATE_CHANGE_WO_LT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Rebuild PHY when DPCD Link Rate != PHY Link Rate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0LinkRateChangeRebuildPhy(void)
{
    SET_DP_RX0_AUX_MANUAL_MODE();

    if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) && (ScalerDpRx0LinkRateChange() == _TRUE))
    {
        ScalerDpRx0RebuildPhy(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01));

        SET_DP_RX0_AUX_AUTO_MODE();

        // De-Skew Circuit Reset
        ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

        // Mac Reset After Link Clock Stable
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

        // Delay for Lane Alignment after Mac Reset
        ScalerTimerDelayXms(2);
    }

    SET_DP_RX0_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Check DPCD Link Rate = PHY Link Rate?
// Input Value  : None
// Output Value : True : Link Rate Change
//              : False :
//--------------------------------------------------
bit ScalerDpRx0LinkRateChange(void)
{
    EnumDpLinkRate enumPhyRate = _DP_LINK_NONE;

    if(ScalerGetBit(P1D_23_CMU_09, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        enumPhyRate = _DP_LINK_HBR2;
    }
    else if(ScalerGetBit(P1D_23_CMU_09, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) == (_BIT5 | _BIT3))
    {
        enumPhyRate = _DP_LINK_HBR;
    }
    else if(ScalerGetBit(P1D_23_CMU_09, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) == (_BIT6 | _BIT5))
    {
        enumPhyRate = _DP_LINK_RBR;
    }

    if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == enumPhyRate)
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}
#endif

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

#if(_DP_MST_SUPPORT == _ON)

    if(GET_DP_RX0_AUX_CH_POWER_ON_WAKE_UP() == _TRUE)
    {
        CLR_DP_RX0_AUX_CH_POWER_ON_WAKE_UP();
    }

#endif

#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)

    // ASSR Mode Setting
    ScalerDpRx0ASSRModeSetting();

#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    CLR_DP_RX0_SOURCE_TYPE_JUDGE();
#endif

    switch(GET_DP_RX0_LINK_TRAINING_STATUS())
    {
        case _DP_NORMAL_LINK_TRAINING_PASS:
        case _DP_LINK_STATUS_FAIL:

            CLR_DP_RX0_VALID_VIDEO_CHECK();

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpRx0MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            ScalerDpRx6MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
#endif
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
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                {
                    CLR_DP_RX_D0_MARGIN_LINK_HBR2();
                }
                else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                {
                    CLR_DP_RX_D6_MARGIN_LINK_HBR2();
                }
#else
                CLR_DP_RX_D0_MARGIN_LINK_HBR2();
#endif
#endif
                return _TRUE;
            }
            else
            {
                DebugMessageRx0("7. Link Status Fail IRQ", 0);

#if(_DP_LINK_RATE_CHANGE_WO_LT_SUPPORT == _ON)
                ScalerDpRx0LinkRateChangeRebuildPhy();
#endif
                SET_DP_RX0_AUX_MANUAL_MODE();

                if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
                {
                    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_STATUS_FAIL);

                    ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
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

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpRx0MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            ScalerDpRx6MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
#endif

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
                DebugMessageRx0("9. Lane0 Tap1 Max", ScalerGetByte(P1D_A5_L0_INIT_3));
                DebugMessageRx0("9. Lane1 Tap1 Max", ScalerGetByte(P1D_B5_L1_INIT_3));
                DebugMessageRx0("9. Lane2 Tap1 Max", ScalerGetByte(P1D_C5_L2_INIT_3));
                DebugMessageRx0("9. Lane3 Tap1 Max", ScalerGetByte(P1D_D5_L3_INIT_3));
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
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                {
                    CLR_DP_RX_D0_MARGIN_LINK_HBR2();
                }
                else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                {
                    CLR_DP_RX_D6_MARGIN_LINK_HBR2();
                }
#else
                CLR_DP_RX_D0_MARGIN_LINK_HBR2();
#endif
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
                if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
                {
                    // Reset Daisy Chain Async-fifo
                    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, _BIT6);
                    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, 0x00);
                }
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
#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
                    ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX0_LONG_HOTPLUG_EVENT);
#endif
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

#if(_DP_MST_SUPPORT == _ON)
        ScalerDpRx0MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        ScalerDpRx6MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
#endif
    }

    return _FALSE;
}

#if(_DP_MST_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP MST2SST Stream Clk PLL Setting
// Input Value  : None
// Output Value : True --> Stream CLK Regen. ok
//--------------------------------------------------
bit ScalerDpRx0MstToSstStreamClkRegenerate(void)
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

    if(ScalerGlobalGetIDCode() >= _RL6410_VER_C_ID_CODE)
    {
        // PLL Input Clock select to Link Clock, Output Clock Select to PLL Clock, Double Buffer.
        ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6), _BIT6);
    }
    else
    {
        // PLL Input Clock select to Crystal Clock, Output Clock Select to PLL Clock, Double Buffer.
        ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6), 0x00);
    }

    ulDpNvidValue = ((((DWORD)ScalerGetByte(PA_23_MSA_NVID_00)) << 16) | (((DWORD)ScalerGetByte(PA_24_MSA_NVID_01)) << 8) | ((DWORD)ScalerGetByte(PA_25_MSA_NVID_02)));

    usDpHtotal = ((((WORD)ScalerGetByte(PA_40_MN_DPF_HTT_M)) << 8) | ((WORD)ScalerGetByte(PA_41_MN_DPF_HTT_L)));

    usDpVtotal = ((((WORD)ScalerGetByte(PA_48_MN_DPF_VTT_M)) << 8) | ((WORD)ScalerGetByte(PA_49_MN_DPF_VTT_L)));

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

    PDATA_DWORD(0) = ((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ;

    if(ScalerGetBit(PA_A0_MN_SCLKG_CTRL, (_BIT7 | _BIT6)) == 0x00)
    {
        // PLL Reference Clock is GDI Clock (For 6410-A)
        ulXtal_clk = _GDI_CLK_KHZ;

        // Set N code to Fin = 13.5MHz
        ucplln = 2;
    }
    else
    {
        // PLL Reference Clock is Lin_Clk/2 (For 6410-B ECO)
        ulXtal_clk = (PDATA_DWORD(0) / 1000 / 2);

        // Set N code to Fin = 13.5MHz
        ucplln = ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00);
    }

    // Measurement Enable
    ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PA_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The result
    ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);

    ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PA_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PA_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PA_5A_MN_MEAS_VLN_L)));

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MST_FREESYNC_ENABLED() == _TRUE)
    {
        ulDpMvidValue = ((((DWORD)ScalerGetByte(PA_20_MSA_MVID_00)) << 16) | (((DWORD)ScalerGetByte(PA_21_MSA_MVID_01)) << 8) | ((DWORD)ScalerGetByte(PA_22_MSA_MVID_02)));

        // Calculate streamclk
        ulStreamClkValue = ((DWORD)ulDpMvidValue * (PDATA_DWORD(0) / ulDpNvidValue) + (PDATA_DWORD(0) % ulDpNvidValue * 100 / ulDpNvidValue * (DWORD)ulDpMvidValue / 100));
    }
    else
#endif
    {
        // Calculate streamclk (Unit is Hz)
        ulStreamClkValue = (((((DWORD)usDpHtotal) * ((DWORD)usDpVtotal) * 100) / ulVBs2BsCount) * _GDI_CLK_KHZ * 10);
    }

    SET_DP_TX_INPUT_PIXEL_CLK(ulStreamClkValue / 100000);

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

#if(_DP_MN_PLL_FREQUENCY_TREND == _PLL_FREQ_DOWN)
    lOffsetValue = 0x7FFFF - lOffsetValue + 1;
#endif

    // DPPLL Power Down
    ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    /*
    // Disable M/N Tracking
    ScalerSetBit(PA_A7_MN_SCLKG_TRK_CTRL, ~_BIT7, 0x00);
    */

    // Disable HSync Tracking
    ScalerSetBit(PA_A7_MN_SCLKG_TRK_CTRL, ~_BIT6, 0x00);

    // Set VCOMD, Path Type of Phase Swallow , SCLKGSTOP
    ScalerSetBit(PA_BF_MN_SCLKG_PLL_WD, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | (_BIT2 & (_DP_MN_PLL_PATH_TYPE << 2)) | _BIT1));

#if(_HW_PLL_EDGE_SELECT_TYPE == _PLL_EDGE_GEN_1_DEFAULT_POSITIVE)
    // Set PLL Edge = Negative
    ScalerSetBit(PA_C1_MN_SCLKG_PLL_RESERVE, ~_BIT1, _BIT1);
#endif

    // Set DPPLL Div_2 & Div_s
    ScalerSetByte(PA_A3_MN_SCLKG_DIVS, (((ucdiv2) << 7) | ((ucdivs) << 0)));

    // Set DPPLL Div_O.
    ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0), ucpllo);

    // Offset Value Setting
    ScalerSetByte(PA_A6_MN_SCLKG_OFFS_L, (BYTE)lOffsetValue);
    ScalerSetByte(PA_A5_MN_SCLKG_OFFS_M, (BYTE)(lOffsetValue >> 8));
    ScalerSetBit(PA_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 | _BIT0), ((BYTE)(lOffsetValue >> 16)) & (_BIT2 | _BIT1 | _BIT0));

    // Enable phase swallow
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), _BIT4);

    // Set DPPLL M Code
    ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), (((ulpllm - 2) >> 8) & 0x03));
    ScalerSetByte(PA_A1_MN_SCLKG_DIVM, ((ulpllm - 2) & 0xFF));

    // Set DPPLL N Code
    ScalerSetByte(PA_A2_MN_SCLKG_DIVN, (ucplln - 2));

    // Load offset value
    ScalerSetBit(PA_A4_MN_SCLKG_OFFS_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

    // Double Buffer for M/N Tracking
    ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(PA_C0_MN_SCLKG_PLL_INSEL, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL Power On
    ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~_BIT7, 0x00);

    ScalerTimerDelayXms(2);


    ////////////////////////////////
    // DPPLL VCO Band Calibration //
    ////////////////////////////////

    // Reg DPLL_CMPEN
    ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~_BIT2, _BIT2);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALLCH
    ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~_BIT3, _BIT3);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALSW
    ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~_BIT4, _BIT4);

    // VCO Band : 01 ---> KVCO = 1340
    // VCO Band : 10 ---> KVCO = 1880
    // VCO Band : 11 ---> KVCO = 2340
    // R : 13
    // Icp = 6.28 * 700 * M / KVCO / R
    // Icp   = 2.5u + bit[0] * 2.5u + bit[1] * 5u + bit[2] * 10u (A)
    // Icp = 2.5uA, 5uA, 7.5uA, 10uA......
    if(ScalerGetBit(PA_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) == _BIT5)
    {
        pData[5] = 4396 * ulpllm / 1880 / 13;
    }
    else if(ScalerGetBit(PA_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
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
    ScalerSetByte(PA_BE_MN_SCLKG_PLL_CHP, (0x78 | (pData[5] & 0x07)));

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

    ScalerSetBit(PA_A8_MN_SCLKG_TRK_MN_I_H, ~(_BIT2 | _BIT1 | _BIT0), ((BYTE)(ulIcodeValue >> 16) & 0x03));
    ScalerSetByte(PA_A9_MN_SCLKG_TRK_MN_I_M, (BYTE)(ulIcodeValue >> 8));
    ScalerSetByte(PA_AA_MN_SCLKG_TRK_MN_I_L, (BYTE)ulIcodeValue);

    // Set P Code
    ScalerSetBit(PA_AB_MN_SCLKG_TRK_MN_P_H, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetByte(PA_AC_MN_SCLKG_TRK_MN_P_M, 0xFF);
    ScalerSetByte(PA_AD_MN_SCLKG_TRK_MN_P_L, 0xFF);
    */

    ////////////////////////////////////////
    // DPPLL HS Tracking Tracking Setting //
    ////////////////////////////////////////

    // Disable Tracking New Mode
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~(_BIT2 | _BIT1), _BIT1);

    // Set Initial I/P Code
    ScalerSetByte(PA_B1_MN_SCLKG_TRK_VS_I_M, 0x00);
    ScalerSetByte(PA_B2_MN_SCLKG_TRK_VS_I_L, 0x04);
    ScalerSetByte(PA_B3_MN_SCLKG_TRK_VS_P_H, 0x00);
    ScalerSetByte(PA_B4_MN_SCLKG_TRK_VS_P_M, 0x7F);
    ScalerSetByte(PA_B5_MN_SCLKG_TRK_VS_P_L, 0xFF);

    // Get How Many Lines per SSC Period
    pData[0] = ulStreamClkValue / usDpHtotal / 33000;

    if(pData[0] > 15)
    {
        pData[0] = 15;
    }

    // Set Tracking Freq
    ScalerSetBit(PA_A8_MN_SCLKG_TRK_MN_I_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (pData[0] << 4));

    if(ulStreamClkValue >= 50000000)
    {
        // Set Threshold of Phase Error = 63 for Timing that Stream Clock is more than 50MHz
        ScalerSetByte(PA_B7_MN_SCLKG_TRK_VS_NLOCK, 0x3F);
    }
    else
    {
        // Set Threshold of Phase Error = 127
        ScalerSetByte(PA_B7_MN_SCLKG_TRK_VS_NLOCK, 0x7F);
    }

    // Enable H Sync Tracking
    ScalerSetByte(PA_A7_MN_SCLKG_TRK_CTRL, 0x58);

    // Double Buffer for H Sync Tracking
    ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // Get Frame Period
    ucFrameTime = 1000 / (ulStreamClkValue / usDpHtotal / usDpVtotal) + 1;

    pData[0] = 0;

    // Waiting for Stream Clk Stable
    do
    {
        // Clear PE Max Record
        ScalerSetByte(PA_B6_MN_SCLKG_TRK_VS_PE, 0x01);

        // Clear PE Flag
        ScalerSetBit(PA_B7_MN_SCLKG_TRK_VS_NLOCK, ~_BIT7, _BIT7);

        // Delay 1 Frame
        ScalerTimerDelayXms(ucFrameTime);

        pData[0]++;
    }
    while((ScalerGetBit(PA_B7_MN_SCLKG_TRK_VS_NLOCK, _BIT7) == _BIT7) && (pData[0] < 10));

    // Set Final I Code
    ScalerSetByte(PA_B1_MN_SCLKG_TRK_VS_I_M, HIBYTE(LOWORD(ul2ndICode)));
    ScalerSetByte(PA_B2_MN_SCLKG_TRK_VS_I_L, LOBYTE(LOWORD(ul2ndICode)));

    // Set Final P Code
    ScalerSetByte(PA_B3_MN_SCLKG_TRK_VS_P_H, LOBYTE(HIWORD(ul2ndPCode)));
    ScalerSetByte(PA_B4_MN_SCLKG_TRK_VS_P_M, HIBYTE(LOWORD(ul2ndPCode)));
    ScalerSetByte(PA_B5_MN_SCLKG_TRK_VS_P_L, LOBYTE(LOWORD(ul2ndPCode)));

    // Don't Enable HS Tracking New Mode for DE Only Mode
    if(ScalerGetBit(PA_35_DPF_CTRL_0, (_BIT5 | _BIT4)) != _BIT4)
    {
        // Only Enable Tracking at Active Region when PE is Small
        PDATA_WORD(0) = ulVBs2BsCount / usDpVtotal / 2;

        ScalerSetBit(PA_C2_HS_TRACKING_NEW_MODE1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
        ScalerSetByte(PA_C3_HS_TRACKING_NEW_MODE2, pData[1]);

        // Enable Tracking New Mode
        ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~(_BIT2 | _BIT1), _BIT2);
    }

    // Set Threshold of Phase Error
    ScalerSetByte(PA_B7_MN_SCLKG_TRK_VS_NLOCK, (_DP_HS_TRACKING_STABLE_PE_THRESHOLD & ~_BIT7));

    pData[0] = 0;

    // Waiting for Stream Clk Stable
    do
    {
        // Clear PE Max Record
        ScalerSetByte(PA_B6_MN_SCLKG_TRK_VS_PE, 0x01);

        // Clear PE Flag
        ScalerSetBit(PA_B7_MN_SCLKG_TRK_VS_NLOCK, ~_BIT7, _BIT7);

        // Delay 1 Frame
        ScalerTimerDelayXms(ucFrameTime);

        pData[0]++;
    }
    while((ScalerGetBit(PA_B7_MN_SCLKG_TRK_VS_NLOCK, _BIT7) == _BIT7) && (pData[0] < 10));

    // Check if DPF Mode is DE Mode
    if(ScalerGetBit(PA_35_DPF_CTRL_0, (_BIT5 | _BIT4)) == _BIT4)
    {
        // DE only mode Disable HSync Tracking
        ScalerSetBit(PA_A7_MN_SCLKG_TRK_CTRL, ~_BIT6, 0x00);
    }

    // Start Generate Display Format
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT7, _BIT7);

    // Polling Vertical BS
    ScalerTimerPollingFlagProc(50, PA_29_MST2SST_VBID, _BIT0, _TRUE);

    // Delay for PG Stable
    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

    return _TRUE;
}


#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_DP_MST_SUPPORT == _ON)
#endif // End of #if(_D0_DP_EXIST == _ON)
