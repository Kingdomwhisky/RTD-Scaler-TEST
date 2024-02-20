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
// ID Code      : RL6463_Series_DPRx0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6463_SERIES_DPRX0__

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

WORD g_usDpRx0ClockTargetCount;
WORD g_usDpRx0ClockMeasureCount;
BYTE g_ucRx0AuxTemp;
BYTE g_ucRx0AuxTemp_EXINT;
WORD g_usDpRx0Vfrontporch;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
BYTE g_ucDpRx0FakeLTLaneCount;
BYTE g_ucDpRx0FakeLTLaneCountBackUp;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpRx0AuxPowerOnInitial(void);
void ScalerDpRx0AuxIntInitial(void);
void ScalerDpRx0DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
void ScalerDpRx0MacInitial(void);
void ScalerDpRx0PhyInitial(void);
void ScalerDpRx0RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
void ScalerDpRx0PassiveDFEFineTune(void);
void ScalerDpRx0AdjustLaneFLDBand(WORD usVCOBandDiff);
void ScalerDpRx0SetDFEInitial(EnumDpLinkRate enumDpLinkRate);
bit ScalerDpRx0CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
bit ScalerDpRx0MeasureLaneCDRClk(BYTE ucDpLinkRate, BYTE ucDpRx0LaneNumber);
void ScalerDpRx0SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue);
bit ScalerDpRx0DisplayFormatSetting(void);

DWORD ScalerDpRx0GetBStoVSDelay(void);
bit ScalerDpRx0StreamClkRegenerate(void);
void ScalerDpRx0AdjustVsyncDelay(void);
bit ScalerDpRx0HdcpMeasureCheck(void);
void ScalerDpRx0PhyCtsTp1SetPhy(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx0PhyCtsTp2SetPhy(void);
bit ScalerDpRx0PhyCtsTp1Check(void);
void ScalerDpRx0PhyCTS(void);

bit ScalerDpRx0NormalPreDetect(void);
BYTE ScalerDpRx0ScanInputPort(void);
bit ScalerDpRx0StableDetect(void);
void ScalerDpRx0SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType);

#if(_DP_RX_ACTIVE_REDUCE_LANE_COUNT_SUPPORT == _ON)
void ScalerDpRx0MainLinkQualityManagement(BYTE ucInputPort);
bit ScalerDpRx0MainLinkPerformanceCheck(void);
#endif

StructDpRxErrorCount ScalerDpRx0GetErrorCount(void);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
void ScalerDpRx0TimingInfoBackup(void);
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

    // RL6463 remove single ended mode
    // ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT1 | _BIT0), _BIT0);

    if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT)
    {
#if(_D0_AUX_DDC_CHANNEL == _D0_AUX_MAP_DDC0_PIN)
        // Enable Aux Channel 0, Disable Channel 1/2
        ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6), _BIT7);
        // Aux Mapping to DDC0
        ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), 0x00);
#elif(_D0_AUX_DDC_CHANNEL == _D0_AUX_MAP_DDC1_PIN)
        // Enable Aux Channel 1, Disable Channel 0/2
        ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6), _BIT6);
        // Aux Mapping to DDC1
        ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), _BIT0);
#endif
    }
    else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
    {
#if(_D1_AUX_DDC_CHANNEL == _D1_AUX_MAP_DDC0_PIN)
        // Enable Aux Channel 0, Disable Channel 1/2
        ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6), _BIT7);
        // Aux Mapping to DDC0
        ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), 0x00);
#elif(_D1_AUX_DDC_CHANNEL == _D1_AUX_MAP_DDC1_PIN)
        // Enable Aux Channel 1, Disable Channel 0/2
        ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6), _BIT6);
        // Aux Mapping to DDC1
        ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), _BIT0);
#endif
    }

    // Delay 100ms for Aux Common Mode Voltage Stable, To Avoid Swing Couple to Aux Cabledetect
    ScalerTimerDelayXms(100);

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

    if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
#endif
    }
    else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D1_DP_LINK_CLK_RATE);
#endif
    }

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

    if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT)
    {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_ASSR_MODE_SUPPORT == _ON))
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x0D, 0x01);

        SET_DP_RX0_AUX_MANUAL_MODE();
        ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
        SET_DP_RX0_AUX_AUTO_MODE();
#endif
    }
    else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
    {
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_ASSR_MODE_SUPPORT == _ON))
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x0D, 0x01);

        SET_DP_RX0_AUX_MANUAL_MODE();
        ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
        SET_DP_RX0_AUX_AUTO_MODE();
#endif
    }

    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x21, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x80, 0x00);

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

    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x01);

#if(_DP_FREESYNC_SUPPORT == _ON)
    switch(GET_DP_EMBEDDED_SWITCH_SELECT())
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            SET_DP_RX0_FREESYNC_SUPPORT(enumFreeSyncSupport);

            if(GET_DP_RX0_FREESYNC_SUPPORT() == _FREESYNC_SUPPORT_ON)
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);
            }
            else
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);
            }

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            SET_DP_RX1_FREESYNC_SUPPORT(enumFreeSyncSupport);

            if(GET_DP_RX1_FREESYNC_SUPPORT() == _FREESYNC_SUPPORT_ON)
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);
            }
            else
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);
            }

            break;
#endif

        default:
            break;
    }
#endif
}

//--------------------------------------------------
// Description  : Dp Mac Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0MacInitial(void)
{
    // Set Digital Phy to Normal
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // Set Digital PHY Sampling Edge
    ScalerSetBit(PB_05_SAMPLE_EDGE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

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

#if((_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON) && (_HW_DP_VSC_SDP_REG_SUPPORT != _ON))
    ScalerDpRx0SetInitialRSV1InfoType();
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
    // [7:6] rxvcom_sel = 2'b01 --> VDD-0.3V
    // [5] en_enhance_bias = 1'b1 --> enhance clock lane buffer current
    // [0] powersw_on = 1'b1 --> power switch on
    ScalerSetBit(PB_B5_BANDGAP_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), (_BIT6 | _BIT5 | _BIT0));

    // [7:6] offcal_range = 2'b11 --> 75uA
    ScalerSetBit(PB_C6_KOFFSET_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [7] sel_d2s_highrate = 1'b1 --> Increase d2s Gain
    ScalerSetBit(PB_C8_KOFFSET_02, ~_BIT7, _BIT7);

    // [7:6] CMU_SEL_CP = 2'b00 --> CMU LPF Cp = 0pF
    ScalerSetBit(PB_C3_CMU_06, ~(_BIT7 | _BIT6), 0x00);

    // [1:0] cdr_kvco = 2'b01 --> KVCO = 700M/v
    ScalerSetBit(PB_D0_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);

    // [7] en_wide_temp = 1'b1 --> Vcp-Vcn=-0.1V
    ScalerSetBit(PB_D3_ANA_CDR_05, ~_BIT7, _BIT7);

    // [7] sel_cont3 = 1'b1 --> BBPD UP/DN Div3
    ScalerSetBit(PB_D4_ANA_CDR_06, ~_BIT7, _BIT7);

    // [3:0] Enable Data Stream Signal Detection
    ScalerSetBit(PB_C2_CMU_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [4] en_sumamp_highgain = 0 --> Disable Sumamp High Gain Mode
    ScalerSetBit(PB_C9_KOFFSET_03, ~_BIT6, 0x00);

    // [0] reg_bypass_ok = 1'b0 --> Disable bypass ok
    ScalerSetBit(PB_C1_CMU_04, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : Rebuilding DP PHY
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
    BYTE ucD0Z0Status = 0;
    BYTE ucD1Z0Status = 0;
    WORD usVCOBandDiff = 0;
    WORD usVCOBandScan = 0;
    BYTE ucIcp = 0;


    ////////////////////
    // Mode Select DP //
    ////////////////////

    // Backup Z0 Status
    ucD0Z0Status = ScalerGetBit(PB_B7_IMPEDANCE_00, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ucD1Z0Status = ScalerGetBit(PB_B9_IMPEDANCE_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable Z0
    ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Termination to GND
    ScalerSetBit(PB_BF_CMU_02, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [5] dp_mode = 1'b1 --> Select DP Mode
    ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT5, _BIT5);

    // [0] hd_dp_sel = 1'b0 --> Select DP
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT0, 0x00);

    // [4] PSM = 1'b0 --> Disable Clock Switch
    ScalerSetBit(PB_B5_BANDGAP_01, ~_BIT4, 0x00);

    // Restore Z0 Status
    ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucD0Z0Status);
    ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucD1Z0Status);


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

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


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

    // [7] cmu_en = 1'b0 --> Lane3 CMU Disable
    ScalerSetBit(PB_C1_CMU_04, ~_BIT7, 0x00);

    // Disable RX_EN, CDR_EN
    ScalerSetByte(PB_C0_CMU_03, 0x00);

    // Enable RX_EN
    ScalerSetBit(PB_C0_CMU_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            // dp_bbpd_sel[3:2] --> ACDR BBPD UP/DN from MAC Lane0
            ScalerSetBit(PB_D0_ANA_CDR_02, ~(_BIT3 | _BIT2), GET_DP_RX0_PCB_LANE0_MAPPING() << 2);

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable Lane0 CDR_EN for DCDR
                ScalerSetBit(PB_C0_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable Lane1 CDR_EN for DCDR
                ScalerSetBit(PB_C0_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable Lane2 CDR_EN for DCDR
                ScalerSetBit(PB_C0_CMU_03, ~_BIT2, _BIT2);
            }

            // [4:3] DP MAC Select One Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            if((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) || (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3))
            {
                // dp_bbpd_sel[3:2] = 2'b11 --> ACDR BBPD UP/DN from Lane3
                ScalerSetBit(PB_D0_ANA_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
            }
            else
            {
                // dp_bbpd_sel[3:2] --> ACDR BBPD UP/DN from MAC Lane0
                ScalerSetBit(PB_D0_ANA_CDR_02, ~(_BIT3 | _BIT2), GET_DP_RX0_PCB_LANE0_MAPPING() << 2);
            }

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable Lane0 CDR_EN for DCDR
                ScalerSetBit(PB_C0_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable Lane1 CDR_EN for DCDR
                ScalerSetBit(PB_C0_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable Lane2 CDR_EN for DCDR
                ScalerSetBit(PB_C0_CMU_03, ~_BIT2, _BIT2);
            }

            if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable Lane0 CDR_EN for DCDR
                ScalerSetBit(PB_C0_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable Lane1 CDR_EN for DCDR
                ScalerSetBit(PB_C0_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable Lane2 CDR_EN for DCDR
                ScalerSetBit(PB_C0_CMU_03, ~_BIT2, _BIT2);
            }

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            // dp_bbpd_sel[3:2] = 2'b11 --> ACDR BBPD UP/DN from Lane3
            ScalerSetBit(PB_D0_ANA_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // Enable Lane0/1/2 CDR_EN for DCDR
            ScalerSetBit(PB_C0_CMU_03, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PB_C0_CMU_03, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(PB_C0_CMU_03, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [4:3] DP MAC Select Four Lane
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }

    // Enable Lane3 CDR_EN for BBPD
    ScalerSetBit(PB_C0_CMU_03, ~_BIT3, _BIT3);

    // ln_clk_func_sel[1:0] --> MAC Clock from Analog CDR Lane
    ScalerSetBit(PB_96_LINK_CLOCK_SELECT, ~(_BIT1 | _BIT0), (ScalerGetBit(PB_D0_ANA_CDR_02, (_BIT3 | _BIT2)) >> 2));

    // Delay Time us [25,x]
    DELAY_25US();

    // Enable Analog CDR and FLD
    ScalerSetBit(PB_B2_ANA_CDR, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));


    ///////////////////////
    // Frequency Setting //
    ///////////////////////

    // [2:0] rate_sel = 3'b001 --> 1.5~3Gbps
    ScalerSetBit(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [1:0] SEL_DIV = 2'b00 --> 1.5~3Gbps
    ScalerSetBit(PB_C4_CMU_07, ~(_BIT1 | _BIT0), 0x00);

    // [6] xtal_en = 1'b1 --> FLD using xtal as reference clock
    ScalerSetBit(PB_D0_ANA_CDR_02, ~_BIT6, _BIT6);

    switch(ucDpLinkRate)
    {
        // 26/492 = 5*(28.6M/2.7G)
        case _DP_LINK_HBR:

            g_usDpRx0ClockTargetCount = 0x1270; // ideal 2.7G

            // ref_conuter = 26
            ScalerSetBit(PB_D5_ANA_CDR_07, ~_BIT7, 0x00);
            ScalerSetByte(PB_D6_ANA_CDR_08, 0x19);

            // cdr_counter = 491
            ScalerSetBit(PB_D5_ANA_CDR_07, ~_BIT6, _BIT6);
            ScalerSetByte(PB_D7_ANA_CDR_09, 0xEA);

            break;

        // 43/487 = 5*(28.6M/1.62G)
        case _DP_LINK_RBR:
        default:

            g_usDpRx0ClockTargetCount = 0xB10; // ideal 1.62G

            // ref_conuter = 43
            ScalerSetBit(PB_D5_ANA_CDR_07, ~_BIT7, 0x00);
            ScalerSetByte(PB_D6_ANA_CDR_08, 0x2A);

            // cdr_counter = 499
            ScalerSetBit(PB_D5_ANA_CDR_07, ~_BIT6, _BIT6);
            ScalerSetByte(PB_D7_ANA_CDR_09, 0xE6);

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

    if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
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
    ScalerSetBit(PB_AE_SDM_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1] bypass_eqen_rdy = 1'b1 --> EQEN Rdy Signal in Manual Mode
    // [0] en_eqen_manual = 1'b1 --> Enable EQ
    ScalerSetBit(PB_B0_EQEN_TIMER, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1] bypass_data_rdy = 1'b1 --> Data Rdy Signal in Manual Mode
    // [0] en_data_manual = 1'b0 --> Disable Dataout
    ScalerSetBit(PB_B1_DATA_TIMER, ~(_BIT1 | _BIT0), _BIT1);

    // [3] reg_en_data_manual_l3 = 1'b0 --> Disable Data Ready
    // [2] reg_bypass_data_rdy_l3 = 1'b1 --> Data Ready Signal in Manual Mode
    // [1] reg_en_eqen_manual_l3 = 1'b1 --> Enable EQ
    // [0] reg_bypass_eqen_rdy_l3 = 1'b1 --> EQ Ready Signal in Manual Mode
    ScalerSetBit(PB_B2_ANA_CDR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Digital Circuit Reset Toggle
    ScalerSetByte(PB_D8_TMDS_RESET, 0x00);
    ScalerSetByte(PB_D8_TMDS_RESET, 0xF0);

    switch(ucDpcdLane & 0x1F)
    {
        case _DP_ONE_LANE:

            break;

        case _DP_TWO_LANE:

            // [3] cdr_rst_n_lane0 = CDR_EN[0]
            ScalerSetBit(PB_D8_TMDS_RESET, ~_BIT3, (ScalerGetBit(PB_C0_CMU_03, _BIT0) << 3));

            // [2] cdr_rst_n_lane1 = CDR_EN[1]
            ScalerSetBit(PB_D8_TMDS_RESET, ~_BIT2, (ScalerGetBit(PB_C0_CMU_03, _BIT1) << 1));

            // [1] cdr_rst_n_lane2 = CDR_EN[2]
            ScalerSetBit(PB_D8_TMDS_RESET, ~_BIT1, (ScalerGetBit(PB_C0_CMU_03, _BIT2) >> 1));

            if((GET_DP_RX0_PCB_LANE0_MAPPING() != _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() != _DP_SCALER_LANE3))
            {
                if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
                {
                    // [3] cdr_rst_n_lane0 = 0 --> Disable DCDR Lane0
                    ScalerSetBit(PB_D8_TMDS_RESET, ~_BIT3, 0x00);
                }
                else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
                {
                    // [2] cdr_rst_n_lane1 = 0 --> Disable DCDR Lane1
                    ScalerSetBit(PB_D8_TMDS_RESET, ~_BIT2, 0x00);
                }
                else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
                {
                    // [1] cdr_rst_n_lane2 = 0 --> Disable DCDR Lane2
                    ScalerSetBit(PB_D8_TMDS_RESET, ~_BIT1, 0x00);
                }
            }

            break;

        case _DP_FOUR_LANE:
        default:

            // [3:0] cdr_rst_n_lane0~3 = 4'b1110
            ScalerSetBit(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

            break;
    }


    /////////////////
    // CDR Setting //
    /////////////////

    // [6:4] sel_cdr_res = 3'b011 --> 4K Ohm
    ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR:

            // [3:0] cdr_cp_in = 4'b0100 --> (1nF)13.5uA
            ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

            // Lane0~2 KP = 4
            ScalerSetByte(PB_F6_CDR_07, 0x10);
            ScalerSetByte(PB_F7_CDR_08, 0x10);
            ScalerSetByte(PB_F8_CDR_09, 0x10);

            break;

        case _DP_LINK_RBR:
        default:

            // [3:0] cdr_cp_in = 4'b0010 --> (1nF)7.5uA
            ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

            // Lane0~2 KP = 8
            ScalerSetByte(PB_F6_CDR_07, 0x20);
            ScalerSetByte(PB_F7_CDR_08, 0x20);
            ScalerSetByte(PB_F8_CDR_09, 0x20);

            break;
    }

    ucIcp = (ScalerGetByte(PB_D1_ANA_CDR_03) & 0x0F);


    ////////////////
    // EQ Setting //
    ////////////////

    // [4:0] reg_fore_off_adjr_Lane0~3 = 5'b10000
    ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(PB_CB_KOFFSET_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(PB_CC_KOFFSET_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(PB_CD_KOFFSET_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR:

            // [7] le_lowgain_highboost = 1'b1 --> Enable LE High-boost Mode
            ScalerSetBit(PB_CB_KOFFSET_05, ~_BIT7, _BIT7);

            // [7:5] le_isel = 3'b010 --> LE Peaking = 1.7Gbps
            ScalerSetBit(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

            // [7:5] le_rlsel = 3'b001 --> LE Peaking = 1.7Gbps
            ScalerSetBit(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            break;

        case _DP_LINK_RBR:
        default:

            // [7] le_lowgain_highboost = 1'b0 --> Disable LE High-boost Mode
            ScalerSetBit(PB_CB_KOFFSET_05, ~_BIT7, 0x00);

            // [7:5] le_isel = 3'b000 --> LE Peaking = 900Mbps
            ScalerSetBit(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // [7:5] le_rlsel = 3'b011 --> LE Peaking = 900Mbps
            ScalerSetBit(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

            break;
    }

    // Set DFE Initial
    ScalerDpRx0SetDFEInitial(ucDpLinkRate);

    // [2:0] tap_en = 3'b001 --> Eable Tap0 Passive EQ
    ScalerSetBit(PB_CE_ANA_CDR_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [7] en_fore_offset = 1'b0 --> Disable EQ foreground Offset Calibration
    // [6] fore_off_autok = 1'b1 --> Enable EQ foreground Offset Calibration Auto Mode
    ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT7 | _BIT6), _BIT6);

    // Toggle en_fore_offset
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x]
    DELAY_XUS(85);

    ///////////////////
    // FLD Auto Mode //
    ///////////////////

    // Set FLD Auto Mode
    ScalerSetBit(PB_CE_ANA_CDR_00, ~_BIT7, _BIT7);

    // [2] cp_en_manual = 1'b0 --> CDR Open Loop
    // [1] adp_en_manual = 1'b0 --> Disable CDR Clock
    ScalerSetBit(PB_CF_ANA_CDR_01, ~(_BIT2 | _BIT1), 0x00);

    // [7] rstb_fld --> Reset Timer of Analog CDR
    // [6] rstb_fsm --> FLD Reset
    ScalerSetBit(PB_D2_ANA_CDR_04, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(PB_D2_ANA_CDR_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Delay Time us [150,x]
    DELAY_XUS(150);


    /////////////////////
    // FLD Manual Mode //
    /////////////////////

    // Scan Auto FLD + 4
    ScalerSetBit(PB_D3_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(PB_D4_ANA_CDR_06) & 0x7F) + 4));

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    ScalerSetBit(PB_CE_ANA_CDR_00, ~_BIT7, 0x00);

    // [1] adp_en_manual = 1'b1 --> Enable CDR Clock Out
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT1, _BIT1);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();


    //////////////////////////
    //  Scan FLD Band + 4   //
    //////////////////////////

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [0] DP_XTAL_CYCLE = 1'b0 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT0), _BIT5);

    // [1:0] freqdet_lane_sel = ACDR Lane
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ScalerGetBit(PB_D0_ANA_CDR_02, (_BIT3 | _BIT2)) >> 2));

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
    ScalerSetBit(PB_D3_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(PB_D4_ANA_CDR_06) & 0x7F));

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
        g_usDpRx0ClockMeasureCount = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        usVCOBandDiff = (abs(usVCOBandScan - g_usDpRx0ClockMeasureCount) >> 2);
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
        ScalerDpRx0AdjustLaneFLDBand(usVCOBandDiff);
    }

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();


    ////////////////////
    // CDR Close Loop //
    ////////////////////

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS(150);

    // [0] en_data_manual = 1'b1 --> Enable Dataout
    ScalerSetBit(PB_B1_DATA_TIMER, ~_BIT0, _BIT0);

    // [3] en_data_manual_l3 = 1'b1 --> Enable Dataout for Lane3
    ScalerSetBit(PB_B2_ANA_CDR, ~_BIT3, _BIT3);

    // [6] xclk_sel = 1'b0 --> Keep Link Clock from Analog
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}
//--------------------------------------------------
// Description  : DP DFE Finetune
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PassiveDFEFineTune(void)
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

    ucIcp = (ScalerGetByte(PB_D1_ANA_CDR_03) & 0x0F);
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
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE0 << 3);
    pusLevel2LEErrorCount[_D0_DP_LANE0] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#if(_DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE1 << 3);
    pusLevel2LEErrorCount[_D0_DP_LANE1] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE2 << 3);
    pusLevel2LEErrorCount[_D0_DP_LANE2] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE3 << 3);
    pusLevel2LEErrorCount[_D0_DP_LANE3] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

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
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS(150);

    // [2:0] rxbist_method = 3'b000 --> Clear 8b10b Error Count
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [2:0] rxbist_method = 3'b010 --> Detect 8b10b + Disparity Correctness
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay for Checking 8b10b Error Count
    ScalerTimerDelayXms(5);

    // [4:3] rxbist_lane_sel = 2'b00 --> Lane0
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE0 << 3);
    pusLevel3LEErrorCount[_D0_DP_LANE0] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#if(_DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE1 << 3);
    pusLevel3LEErrorCount[_D0_DP_LANE1] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE2 << 3);
    pusLevel3LEErrorCount[_D0_DP_LANE2] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE3 << 3);
    pusLevel3LEErrorCount[_D0_DP_LANE3] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

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
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS(150);

    // [2:0] rxbist_method = 3'b000 --> Clear 8b10b Error Count
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [2:0] rxbist_method = 3'b010 --> Detect 8b10b + Disparity Correctness
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay for Checking 8b10b Error Count
    ScalerTimerDelayXms(5);

    // [4:3] rxbist_lane_sel = 2'b00 --> Lane0
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE0 << 3);
    pusLevel1LEErrorCount[_D0_DP_LANE0] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#if(_DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE1 << 3);
    pusLevel1LEErrorCount[_D0_DP_LANE1] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE2 << 3);
    pusLevel1LEErrorCount[_D0_DP_LANE2] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE3 << 3);
    pusLevel1LEErrorCount[_D0_DP_LANE3] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

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
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS(150);

    // [2:0] rxbist_method = 3'b000 --> Clear 8b10b Error Count
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [2:0] rxbist_method = 3'b010 --> Detect 8b10b + Disparity Correctness
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay for Checking 8b10b Error Count
    ScalerTimerDelayXms(5);

    // [4:3] rxbist_lane_sel = 2'b00 --> Lane0
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE0 << 3);
    pusLevel0LEErrorCount[_D0_DP_LANE0] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#if(_DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    // [4:3] rxbist_lane_sel = 2'b01 --> Lane1
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE1 << 3);
    pusLevel0LEErrorCount[_D0_DP_LANE1] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b10 --> Lane2
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE2 << 3);
    pusLevel0LEErrorCount[_D0_DP_LANE2] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // [4:3] rxbist_lane_sel = 2'b11 --> Lane3
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _D0_DP_LANE3 << 3);
    pusLevel0LEErrorCount[_D0_DP_LANE3] = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

#endif

    DebugMessageRx0("Level 3 LE ErrorCount[_D0_DP_LANE0]", pusLevel3LEErrorCount[_D0_DP_LANE0]);
    DebugMessageRx0("Level 2 LE ErrorCount[_D0_DP_LANE0]", pusLevel2LEErrorCount[_D0_DP_LANE0]);
    DebugMessageRx0("Level 1 LE ErrorCount[_D0_DP_LANE0]", pusLevel1LEErrorCount[_D0_DP_LANE0]);
    DebugMessageRx0("Level 0 LE ErrorCount[_D0_DP_LANE0]", pusLevel0LEErrorCount[_D0_DP_LANE0]);

#if(_DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

    DebugMessageRx0("Level 3 LE ErrorCount[_D0_DP_LANE1]", pusLevel3LEErrorCount[_D0_DP_LANE1]);
    DebugMessageRx0("Level 2 LE ErrorCount[_D0_DP_LANE1]", pusLevel2LEErrorCount[_D0_DP_LANE1]);
    DebugMessageRx0("Level 1 LE ErrorCount[_D0_DP_LANE1]", pusLevel1LEErrorCount[_D0_DP_LANE1]);
    DebugMessageRx0("Level 0 LE ErrorCount[_D0_DP_LANE1]", pusLevel0LEErrorCount[_D0_DP_LANE1]);

    DebugMessageRx0("Level 3 LE ErrorCount[_D0_DP_LANE2]", pusLevel3LEErrorCount[_D0_DP_LANE2]);
    DebugMessageRx0("Level 2 LE ErrorCount[_D0_DP_LANE2]", pusLevel2LEErrorCount[_D0_DP_LANE2]);
    DebugMessageRx0("Level 1 LE ErrorCount[_D0_DP_LANE2]", pusLevel1LEErrorCount[_D0_DP_LANE2]);
    DebugMessageRx0("Level 0 LE ErrorCount[_D0_DP_LANE2]", pusLevel0LEErrorCount[_D0_DP_LANE2]);

    DebugMessageRx0("Level 3 LE ErrorCount[_D0_DP_LANE3]", pusLevel3LEErrorCount[_D0_DP_LANE3]);
    DebugMessageRx0("Level 2 LE ErrorCount[_D0_DP_LANE3]", pusLevel2LEErrorCount[_D0_DP_LANE3]);
    DebugMessageRx0("Level 1 LE ErrorCount[_D0_DP_LANE3]", pusLevel1LEErrorCount[_D0_DP_LANE3]);
    DebugMessageRx0("Level 0 LE ErrorCount[_D0_DP_LANE3]", pusLevel0LEErrorCount[_D0_DP_LANE3]);
#endif


    ///////////////////////////////////
    // Choose The Best DFE Parameter //
    ///////////////////////////////////

    for(ucLaneSelect = 0; ucLaneSelect < 4; ucLaneSelect++)
    {
#if(_DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_1_LANE)

        ucTemp = _D0_DP_LANE0;

#elif(_DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE == _FINE_TUNE_DFE_BY_4_LANE)

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
    if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
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
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x]
    DELAY_XUS(85);

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x]
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [150,x] Wait MAC align comma --> idle pattern worse case every 8192 symbol insert bs (8192 x 1/162M x 2bs = 102us)
    DELAY_XUS(150);
}
//--------------------------------------------------
// Description  : DP FLD Band Finetune
// Input Value  : LaneNumber
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AdjustLaneFLDBand(WORD usVCOBandDiff)
{
    BYTE ucBestVCOBand = 0;
    BYTE ucAutoVCOBand = 0;

    ucAutoVCOBand = (ScalerGetByte(PB_D4_ANA_CDR_06) & 0x7F);

    // [1:0] freqdet_lane_sel = ACDR Lane
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ScalerGetBit(PB_D0_ANA_CDR_02, (_BIT3 | _BIT2)) >> 2));

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
        g_usDpRx0ClockMeasureCount = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        if(g_usDpRx0ClockMeasureCount < g_usDpRx0ClockTargetCount)
        {
            ucBestVCOBand = ucAutoVCOBand + (((g_usDpRx0ClockTargetCount - g_usDpRx0ClockMeasureCount) / usVCOBandDiff) + 1);
        }
        else
        {
            ucBestVCOBand = ucAutoVCOBand - ((g_usDpRx0ClockMeasureCount - g_usDpRx0ClockTargetCount) / usVCOBandDiff);
        }
    }
    else
    {
        ucBestVCOBand = ucAutoVCOBand;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // Manually Reload FLD Band
    ScalerSetBit(PB_D3_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDFEInitial(EnumDpLinkRate enumDpLinkRate)
{
    enumDpLinkRate = enumDpLinkRate;

    // Change to T-switch to solve interference but input BW loss more 2dB
    if(ScalerGlobalGetIDCode() >= _RL6463_VER_C_ID_CODE)
    {
        // LE Initial = 12
        ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x0C);
        ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x0C);
        ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x0C);
        ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x0C);
    }
    else
    {
        // LE Initial = 10
        ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x0A);
        ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x0A);
        ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x0A);
        ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x0A);
    }

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

            if(ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE0) == _TRUE)
            {
                return _TRUE;
            }
            break;

        case _DP_FOUR_LANE:
        default:

            if(ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE3) == _TRUE)
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

#if(_XTALESS_SUPPORT == _ON)
    return _TRUE;
#endif

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR:

            if((abs(g_usDpRx0ClockTargetCount - 0x1270)) > (0x1270 >> 4))
            {
                return _TRUE;
            }

            break;

        default:
        case _DP_LINK_RBR:

            if((abs(g_usDpRx0ClockTargetCount - 0xB10)) > (0xB10 >> 4))
            {
                return _TRUE;
            }

            break;
    }

    // Select Measure CDR Clock & XTAL 27M Count 1000 Times
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT0), _BIT5);

    // Select CDR Lane
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), ucDpRx0LaneNumber);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // Toggle Start Measure
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

    if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == 0x00)
    {
        return _FALSE;
    }

    usCDRClockCount = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

    if(abs(g_usDpRx0ClockTargetCount - usCDRClockCount) > (g_usDpRx0ClockTargetCount >> 7))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : Initial Signal check
// Input Value  : DP Link Rate and DP Reload LEQ Scan Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue)
{
    // [3:2] reg_dp_bbpd_sel --> Default set ACDR to PCB Lane0
    ScalerSetBit(PB_D0_ANA_CDR_02, ~(_BIT3 | _BIT2), (GET_DP_RX0_PCB_LANE0_MAPPING() << 2));

    ///////////////
    // RX CMU EN //
    ///////////////

    // Disable RX_EN, CDR_EN
    ScalerSetByte(PB_C0_CMU_03, 0x00);

    // Enable RX_EN, CDR_EN
    ScalerSetByte(PB_C0_CMU_03, 0xFF);


    ////////////////
    // EQ Setting //
    ////////////////

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR:

            // [7] le_lowgain_highboost = 1'b1 --> Enable LE High-boost Mode
            ScalerSetBit(PB_CB_KOFFSET_05, ~_BIT7, _BIT7);

            // [7:5] le_isel = 3'b010 --> LE Peaking = 1.7Gbps
            ScalerSetBit(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

            // [7:5] le_rlsel = 3'b001 --> LE Peaking = 1.7Gbps
            ScalerSetBit(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            // Change to T-switch to solve interference but input BW loss more 2dB
            if(ScalerGlobalGetIDCode() >= _RL6463_VER_C_ID_CODE)
            {
                switch(ucDpLEQScanValue)
                {
                    case _DP_RELOAD_LEQ_DEFAULT:

                        // LE Initial = 12
                        ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x0C);
                        ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x0C);
                        ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x0C);
                        ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x0C);

                        break;

                    case _DP_RELOAD_LEQ_LARGE:
                    default:

                        // LE Initial = 17
                        ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x11);
                        ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x11);
                        ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x11);
                        ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x11);

                        break;
                }
            }
            else
            {
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
            }

            break;

        case _DP_LINK_RBR:
        default:

            // [7] le_lowgain_highboost = 1'b0 --> Disable LE High-boost Mode
            ScalerSetBit(PB_CB_KOFFSET_05, ~_BIT7, 0x00);

            // [7:5] le_isel = 3'b000 --> LE Peaking = 900Mbps
            ScalerSetBit(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // [7:5] le_rlsel = 3'b011 --> LE Peaking = 900Mbps
            ScalerSetBit(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

            // Change to T-switch to solve interference but input BW loss more 2dB
            if(ScalerGlobalGetIDCode() >= _RL6463_VER_C_ID_CODE)
            {
                // LE Initial = 12
                ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x0C);
                ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x0C);
                ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x0C);
                ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x0C);
            }
            else
            {
                // LE Initial = 10
                ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x0A);
                ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x0A);
                ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x0A);
                ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x0A);
            }

            break;
    }

    // Tap0 Initial Value = 15
    ScalerSetByte(P1D_A4_L0_INIT_2, 0x0F);
    ScalerSetByte(P1D_B4_L1_INIT_2, 0x0F);
    ScalerSetByte(P1D_C4_L2_INIT_2, 0x0F);
    ScalerSetByte(P1D_D4_L3_INIT_2, 0x0F);

    // [2:0] tap_en = 3'b001 --> Eable Tap0 Passive EQ
    ScalerSetBit(PB_CE_ANA_CDR_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // Delay Time us [85,x]
    DELAY_XUS(85);

    // [7] en_fore_offset = 1'b0 --> Disable EQ foreground Offset Calibration
    // [6] fore_off_autok = 1'b1 --> Enable EQ foreground Offset Calibration Auto Mode
    ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT7 | _BIT6), _BIT6);

    // Toggle en_fore_offset
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x]
    DELAY_XUS(85);

    // [4:0] reg_fore_off_adjr_Lane0~3
    // if Auto K = 0 ~ 15 Reload Auto K + 8, Auto K = 16 ~ 31 Reload Auto K - 8
    if((ScalerGetByte(PB_C6_KOFFSET_00) & 0x1F) > 15)
    {
        ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(PB_C6_KOFFSET_00) & 0x1F) - 8));
    }
    else
    {
        ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(PB_C6_KOFFSET_00) & 0x1F) + 8));
    }

    if((ScalerGetByte(PB_C7_KOFFSET_01) & 0x1F) > 15)
    {
        ScalerSetBit(PB_CB_KOFFSET_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(PB_C7_KOFFSET_01) & 0x1F) - 8));
    }
    else
    {
        ScalerSetBit(PB_CB_KOFFSET_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(PB_C7_KOFFSET_01) & 0x1F) + 8));
    }

    if((ScalerGetByte(PB_C8_KOFFSET_02) & 0x1F) > 15)
    {
        ScalerSetBit(PB_CC_KOFFSET_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(PB_C8_KOFFSET_02) & 0x1F) - 8));
    }
    else
    {
        ScalerSetBit(PB_CC_KOFFSET_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(PB_C8_KOFFSET_02) & 0x1F) + 8));
    }

    if((ScalerGetByte(PB_C9_KOFFSET_03) & 0x1F) > 15)
    {
        ScalerSetBit(PB_CD_KOFFSET_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(PB_C9_KOFFSET_03) & 0x1F) - 8));
    }
    else
    {
        ScalerSetBit(PB_CD_KOFFSET_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(PB_C9_KOFFSET_03) & 0x1F) + 8));
    }

    // [6] fore_off_autok = 1'b0 --> Enable EQ foreground Offset Calibration Manual Mode
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT6, 0x00);
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
        // [0] DP_XTAL_CYCLE = 1'b0 -> XTAL Counter Cycles = 2000
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

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

    // Double Buffer to Apply Display Format Setting (RL6463 has no double buffer for display format setting)
    // ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT6, _BIT6);

    ScalerDpRx0VideoSetting();

    return _TRUE;
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

    // DP fifo size = 128 x 96bit
    if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
    {
        // FifoOffset = (1/2 * (128 * 96) / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (4 * (WORD)pData[15]);
    }
    else
    {
        // FifoOffset = (1/2 * (128 * 96) / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (6 * (WORD)pData[15]);
    }

    // FifoOffset = (usFifoOffset) * (Link Clk / Stream CLK))
    usFifoOffset = (WORD)(((DWORD)usFifoOffset) * (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_INPUT_PIXEL_CLK()));

    return ((ulVFrontPorch + ulHFrontPorch + (DWORD)usFifoOffset) / 2);
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

    // Reset DP Stream Clock Block
    ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT2, 0x00);

    // PLL Input Clock select to Link Clock, Output Clock Select to PLL Clock, Double Buffer.
    ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);

    ulDpNvidValue = ((((DWORD)ScalerGetByte(PB6_1D_MSA_NVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1E_MSA_NVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1F_MSA_NVID_2)));

    usDpHtotal = ((((WORD)ScalerGetByte(PB5_41_MN_DPF_HTT_M)) << 8) | ((WORD)ScalerGetByte(PB5_42_MN_DPF_HTT_L)));

    usDpVtotal = ((((WORD)ScalerGetByte(PB5_49_MN_DPF_VTT_M)) << 8) | ((WORD)ScalerGetByte(PB5_4A_MN_DPF_VTT_L)));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [0] DP_XTAL_CYCLE = 1'b0 -> XTAL Counter Cycles = 2000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

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
        // For RL6463,GDI_CLK is 28.6MHz
        if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = 0x49C1;
        }
        else if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
        {
            PDATA_WORD(0) = 0x24E1;
        }
        else // Both Default && _DP_LINK_RBR Case
        {
            PDATA_WORD(0) = 0x1620;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

    // PLL Reference Clock is Link_Clk/2
    ulXtal_clk = (PDATA_DWORD(0) / 1000 / 2);

    // Set N code to Fin = 13.5MHz
    ucplln = ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00);

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

    // DP CLK Output Enable
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, _BIT6);

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

    ulIcodeValue = (16777216 / g_ulDpNvidValue) * ucplln / ulpllm;  //I = (2^24) * (ucplln / ulpllm) / Nvid

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

    // Double Buffer to Apply Display Format Setting(RL6463 have no double buffer for Display FOrmat setting)
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
        // For RL6463,GDI_CLK is 28.6MHz
        if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = 0x49C1;
        }
        else if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
        {
            PDATA_WORD(0) = 0x24E1;
        }
        else // Both Default && _DP_LINK_RBR Case
        {
            PDATA_WORD(0) = 0x1620;
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
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0PhyCtsTp1SetPhy(EnumDpNFCodeRef enumDpNFCodeRef)
{
    BYTE ucIcp = 0;


    ////////////////////
    // Mode Select DP //
    ////////////////////

    // Termination to GND
    ScalerSetBit(PB_BF_CMU_02, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [5] dp_mode = 1'b1 --> Select DP Mode
    ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT5, _BIT5);

    // [0] hd_dp_sel = 1'b0 --> Select DP
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT0, 0x00);

    // [4] PSM = 1'b0 --> Disable Clock Switch
    ScalerSetBit(PB_B5_BANDGAP_01, ~_BIT4, 0x00);


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

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


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

    // [7] cmu_en = 1'b0 --> Lane3 CMU Disable
    ScalerSetBit(PB_C1_CMU_04, ~_BIT7, 0x00);

    // Disable RX_EN, CDR_EN
    ScalerSetByte(PB_C0_CMU_03, 0x00);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
    {
        case 0x10:

            // dp_bbpd_sel[3:2] = 2'b01 --> ACDR BBPD UP/DN from Lane1
            ScalerSetBit(PB_D0_ANA_CDR_02, ~(_BIT3 | _BIT2), _BIT2);

            // ln_clk_func_sel[1:0] = 2'b01 --> MAC Clock from Analog Lane1
            ScalerSetBit(PB_96_LINK_CLOCK_SELECT, ~(_BIT1 | _BIT0), _BIT0);

            // Lane1 Test, Enable RX_EN/CDR_EN for Lane1/3
            ScalerSetByte(PB_C0_CMU_03, 0xAA);

            break;

        case 0x20:

            // dp_bbpd_sel[3:2] = 2'b10 --> ACDR BBPD UP/DN from Lane2
            ScalerSetBit(PB_D0_ANA_CDR_02, ~(_BIT3 | _BIT2), _BIT3);

            // ln_clk_func_sel[1:0] = 2'b10 --> MAC Clock from Analog Lane2
            ScalerSetBit(PB_96_LINK_CLOCK_SELECT, ~(_BIT1 | _BIT0), _BIT1);

            // Lane2 Test, Enable RX_EN/CDR_EN for Lane2/3
            ScalerSetByte(PB_C0_CMU_03, 0xCC);

            break;

        case 0x30:

            // dp_bbpd_sel[3:2] = 2'b11 --> ACDR BBPD UP/DN from Lane3
            ScalerSetBit(PB_D0_ANA_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // ln_clk_func_sel[1:0] = 2'b11 --> MAC Clock from Analog Lane3
            ScalerSetBit(PB_96_LINK_CLOCK_SELECT, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Lane3 Test, Enable RX_EN/CDR_EN for Lane3
            ScalerSetByte(PB_C0_CMU_03, 0x88);

            break;

        default:
        case 0x00:

            // dp_bbpd_sel[3:2] = 2'b00 --> ACDR BBPD UP/DN from Lane0
            ScalerSetBit(PB_D0_ANA_CDR_02, ~(_BIT3 | _BIT2), 0x00);

            // ln_clk_func_sel[1:0] = 2'b00 --> MAC Clock from Analog Lane0
            ScalerSetBit(PB_96_LINK_CLOCK_SELECT, ~(_BIT1 | _BIT0), 0x00);

            // Lane0 Test, Enable RX_EN/CDR_EN for Lane0/3
            ScalerSetByte(PB_C0_CMU_03, 0x99);

            break;
    }

    // Delay Time us [25,x]
    DELAY_25US();

    // Enable Analog CDR and FLD
    ScalerSetBit(PB_B2_ANA_CDR, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [4:3] One Lane Test
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);


    ///////////////////////
    // Frequency Setting //
    ///////////////////////

    // [2:0] rate_sel = 3'b001 --> 1.5~3Gbps
    ScalerSetBit(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [1:0] SEL_DIV = 2'b00 --> 1.5~3Gbps
    ScalerSetBit(PB_C4_CMU_07, ~(_BIT1 | _BIT0), 0x00);

    if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
    {
        // [6] reg_xtal_en = 1'b1 --> Using 28.6M Xtal
        ScalerSetBit(PB_D0_ANA_CDR_02, ~_BIT6, _BIT6);

        if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x00)   // RBR = 44/499 = 5*(28.6M/1.62G)
        {
            // ref_conuter = 44
            ScalerSetBit(PB_D5_ANA_CDR_07, ~_BIT7, 0x00);
            ScalerSetByte(PB_D6_ANA_CDR_08, 0x2B);

            // cdr_counter = 499
            ScalerSetBit(PB_D5_ANA_CDR_07, ~_BIT6, _BIT6);
            ScalerSetByte(PB_D7_ANA_CDR_09, 0xF2);
        }
        else  // HBR = 26/492 = 5*(28.6M/2.7G)
        {
            // ref_conuter = 26
            ScalerSetBit(PB_D5_ANA_CDR_07, ~_BIT7, 0x00);
            ScalerSetByte(PB_D6_ANA_CDR_08, 0x19);

            // cdr_counter = 492
            ScalerSetBit(PB_D5_ANA_CDR_07, ~_BIT6, _BIT6);
            ScalerSetByte(PB_D7_ANA_CDR_09, 0xEB);
        }
    }
    else
    {
        // [6] xtal_en = 1'b1 --> D10.2 clock
        ScalerSetBit(PB_D0_ANA_CDR_02, ~_BIT6, 0x00);

        // ref_conuter = 250
        ScalerSetBit(PB_D5_ANA_CDR_07, ~_BIT7, 0x00);
        ScalerSetByte(PB_D6_ANA_CDR_08, 0xFA);

        // cdr_counter = 500
        ScalerSetBit(PB_D5_ANA_CDR_07, ~_BIT6, _BIT6);
        ScalerSetByte(PB_D7_ANA_CDR_09, 0xEB);
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
    ScalerSetBit(PB_AE_SDM_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1] bypass_eqen_rdy = 1'b1 --> EQEN Rdy Signal in Manual Mode
    // [0] en_eqen_manual = 1'b1 --> Enable EQ
    ScalerSetBit(PB_B0_EQEN_TIMER, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1] bypass_data_rdy = 1'b1 --> Data Rdy Signal in Manual Mode
    // [0] en_data_manual = 1'b0 --> Disable Dataout
    ScalerSetBit(PB_B1_DATA_TIMER, ~(_BIT1 | _BIT0), _BIT1);

    // [3] reg_en_data_manual_l3 = 1'b0 --> Disable Data Ready
    // [2] reg_bypass_data_rdy_l3 = 1'b1 --> Data Ready Signal in Manual Mode
    // [1] reg_en_eqen_manual_l3 = 1'b1 --> Enable EQ
    // [0] reg_bypass_eqen_rdy_l3 = 1'b1 --> EQ Ready Signal in Manual Mode
    ScalerSetBit(PB_B2_ANA_CDR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Digital Circuit Reset Toggle
    ScalerSetByte(PB_D8_TMDS_RESET, 0x00);
    ScalerSetBit(PB_D8_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));


    /////////////////
    // CDR Setting //
    /////////////////

    // [6:4] sel_cdr_res = 3'b011 --> 4K Ohm
    ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x00)   // RBR
    {
        // [3:0] cdr_cp_in = 4'b0010 --> (1nF)7.5uA
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // [3:0] cdr_cp_in = 4'b0100 --> (1nF)13.5uA
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
    }

    ucIcp = (ScalerGetByte(PB_D1_ANA_CDR_03) & 0x0F);


    ////////////////
    // EQ Setting //
    ////////////////

    // [4:0] reg_fore_off_adjr_Lane0~3 = 5'b10000
    ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(PB_CB_KOFFSET_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(PB_CC_KOFFSET_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(PB_CD_KOFFSET_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x00)   // RBR
    {
        // [7] le_lowgain_highboost = 1'b0 --> Disable LE High-boost Mode
        ScalerSetBit(PB_CB_KOFFSET_05, ~_BIT7, 0x00);

        // [7:5] le_isel = 3'b000 --> LE Peaking = 900Mbps
        ScalerSetBit(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [7:5] le_rlsel = 3'b011 --> LE Peaking = 900Mbps
        ScalerSetBit(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

        // Set DFE Initial
        ScalerDpRx0SetDFEInitial(_DP_LINK_RBR);
    }
    else
    {
        // [7] le_lowgain_highboost = 1'b1 --> Enable LE High-boost Mode
        ScalerSetBit(PB_CB_KOFFSET_05, ~_BIT7, _BIT7);

        // [7:5] le_isel = 3'b010 --> LE Peaking = 1.7Gbps
        ScalerSetBit(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

        // [7:5] le_rlsel = 3'b001 --> LE Peaking = 1.7Gbps
        ScalerSetBit(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // Set DFE Initial
        ScalerDpRx0SetDFEInitial(_DP_LINK_HBR);
    }

    // [2:0] tap_en = 3'b001 --> Eable Tap0 Passive EQ
    ScalerSetBit(PB_CE_ANA_CDR_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [7] en_fore_offset = 1'b0 --> Disable EQ foreground offset calibration
    // [6] fore_off_autok = 1'b1 --> Enable EQ foreground offset calibration using auto mode
    ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT7 | _BIT6), _BIT6);

    // Toggle en_fore_offset
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x]
    DELAY_XUS(85);


    ///////////////////
    // FLD Auto Mode //
    ///////////////////

    // Set FLD Auto Mode
    ScalerSetBit(PB_CE_ANA_CDR_00, ~_BIT7, _BIT7);

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    // [1] adp_en_manual = 1'b0 --> Disable CDR Clock
    ScalerSetBit(PB_CF_ANA_CDR_01, ~(_BIT2 | _BIT1), 0x00);

    // [7] rstb_fld --> Reset Timer of Analog CDR
    // [6] rstb_fsm --> FLD Reset Signal
    ScalerSetBit(PB_D2_ANA_CDR_04, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(PB_D2_ANA_CDR_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Delay Time us [150,x]
    DELAY_XUS(150);


    /////////////////////
    // FLD Manual Mode //
    /////////////////////

    // Scan Lane3 Auto FLD
    ScalerSetBit(PB_D3_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(PB_D4_ANA_CDR_06) & 0x7F));

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    ScalerSetBit(PB_CE_ANA_CDR_00, ~_BIT7, 0x00);

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    // [1] adp_en_manual = 1'b1 --> Enable CDR Clock
    ScalerSetBit(PB_CF_ANA_CDR_01, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

    // Delay Time us [45,x] Waiting for VCO Stable
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x] Waiting for VCO Stable
    DELAY_45US();

    // [0] en_data_manual = 1'b1 --> Enable Dataout
    ScalerSetBit(PB_B1_DATA_TIMER, ~_BIT0, _BIT0);

    // [3] en_data_manual_l3 = 1'b1 --> Enable Dataout for Lane3
    ScalerSetBit(PB_B2_ANA_CDR, ~_BIT3, _BIT3);

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
void ScalerDpRx0PhyCtsTp2SetPhy(void)
{
    BYTE ucBestVCOBand = 0;
    WORD usVCOBandDiff = 0;
    WORD usVCOAutoBandAdd4 = 0;
    BYTE ucIcp = (ScalerGetByte(PB_D1_ANA_CDR_03) & 0x0F);


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
    ScalerSetBit(PB_B1_DATA_TIMER, ~_BIT0, 0x00);

    // [3] en_data_manual_l3 = 1'b0 --> Disable Dataout for Lane3
    ScalerSetBit(PB_B2_ANA_CDR, ~_BIT3, 0x00);

    // Digital Circuit Reset Toggle
    ScalerSetByte(PB_D8_TMDS_RESET, 0x00);
    ScalerSetBit(PB_D8_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));


    ////////////////////////
    //  FLD Band Finetune //
    ////////////////////////

    // Target Freq.
    if((g_ucDpRx0PhyCtsCtrl & 0xC0) == 0x00)
    {
        g_usDpRx0ClockTargetCount = 0xB10; // ideal 1.62G
    }
    else
    {
        g_usDpRx0ClockTargetCount = 0x1270; // ideal 2.7G
    }

    // [2] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT2, 0x00);

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [0] DP_XTAL_CYCLE = 1'b0 -> XTAL Counter Cycles = 1000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT0), _BIT5);

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

    // Scan Auto FLD + 4
    ScalerSetBit(PB_D3_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte(PB_D4_ANA_CDR_06) & 0x7F) + 4));

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
    ScalerSetBit(PB_D3_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(PB_D4_ANA_CDR_06) & 0x7F));

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
        g_usDpRx0ClockMeasureCount = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        usVCOBandDiff = (abs(usVCOAutoBandAdd4 - g_usDpRx0ClockMeasureCount) >> 2);

        if(g_usDpRx0ClockMeasureCount < g_usDpRx0ClockTargetCount)
        {
            // VCO Adjust
            ucBestVCOBand = (ScalerGetByte(PB_D4_ANA_CDR_06) & 0x7F) + (((g_usDpRx0ClockTargetCount - g_usDpRx0ClockMeasureCount) / usVCOBandDiff) + 1);
        }
        else
        {
            // VCO Adjust
            ucBestVCOBand = (ScalerGetByte(PB_D4_ANA_CDR_06) & 0x7F) - ((g_usDpRx0ClockMeasureCount - g_usDpRx0ClockTargetCount) / usVCOBandDiff);
        }
    }
    else
    {
        // Measure Fail -> Use Auto FLD Band
        ucBestVCOBand = (ScalerGetByte(PB_D4_ANA_CDR_06) & 0x7F);
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // Manually Reload FLD Band
    ScalerSetBit(PB_D3_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [2] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit(PB_CF_ANA_CDR_01, ~_BIT2, _BIT2);

    // Delay Time us [45,x] Waiting for VCO Stable
    DELAY_45US();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x] Waiting for VCO Stable
    DELAY_45US();

    // [0] en_data_manual = 1'b1 --> Enable Dataout
    ScalerSetBit(PB_B1_DATA_TIMER, ~_BIT0, _BIT0);

    // [3] en_data_manual_l3 = 1'b1 --> Enable Dataout for Lane3
    ScalerSetBit(PB_B2_ANA_CDR, ~_BIT3, _BIT3);

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
bit ScalerDpRx0PhyCtsTp1Check(void)
{
    // Wait for 10ms
    ScalerTimerDelayXms(10);

    // Clear 8B/10B Decode Error Flags
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Wait for 2ms
    ScalerTimerDelayXms(2);

    ScalerSetByte(PB7_A1_AUX_RESERVE1, ScalerGetByte(PB_06_DECODE_10B8B_ERROR));
    ScalerSetByte(PB7_A2_AUX_RESERVE2, ScalerGetByte(PB_14_EQ_CRC_3));
    ScalerSetByte(PB7_A3_AUX_RESERVE3, g_ucDpRx0PhyCtsCtrl & 0x30);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
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

    if(((ScalerGetByte(PB7_A1_AUX_RESERVE1) & pData[1]) == 0x00) &&
       ((ScalerGetByte(PB7_A2_AUX_RESERVE2) & pData[0]) != 0x00))
    {
        return _TRUE;
    }

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
    // g_ucDpRx0PhyCtsCtrl(Page0x0B BD[0] = 0 --> PHY CTS Enable Start
    // g_ucDpRx0PhyCtsCtrl(Page0x0B F0[2:0]) = 0x01 --> CDR
    // g_ucDpRx0PhyCtsCtrl(Page0x0B F0[2:0]) = 0x02 --> EQ CRC
    // g_ucDpRx0PhyCtsCtrl(Page0x0B F0[2:0]) = 0x03 --> PRBS7 Error Counter Reset and Counter Start
    // g_ucDpRx0PhyCtsCtrl(Page0x0B F0[2:0]) = 0x04 --> PRBS7 Error Counter Read
    // g_ucDpRx0PhyCtsCtrl(Page0x0B F0[2:0]) = 0x05 --> PHY CTS Disable
    // g_ucDpRx0PhyCtsCtrl(Page0x0B F0[5:4]) = 00 --> lane0
    // g_ucDpRx0PhyCtsCtrl(Page0x0B F0[5:4]) = 01 --> lane1
    // g_ucDpRx0PhyCtsCtrl(Page0x0B F0[5:4]) = 10 --> lane2
    // g_ucDpRx0PhyCtsCtrl(Page0x0B F0[5:4]) = 11 --> lane3
    // g_ucDpRx0PhyCtsCtrl(Page0x0B F0[7:6]) = 00 --> RBR
    // g_ucDpRx0PhyCtsCtrl(Page0x0B F0[7:6]) = 01 --> HBR

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

                                // Reset 8B/10B Error Counter
                                ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                                ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
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

            DebugMessageRx0("7. PHY CTS Loop", ScalerGetByte(PB_F0_CDR_01));

            switch(ScalerGetByte(PB_F0_CDR_01) & 0x30)
            {
                default:
                case 0x00: // Source Lane0

                    ScalerSetBit(PB_F0_CDR_01, ~(_BIT5 | _BIT4), _D0_DP_LANE0 << 4);

                    break;

                case 0x10: // Source Lane1

                    ScalerSetBit(PB_F0_CDR_01, ~(_BIT5 | _BIT4), _D0_DP_LANE1 << 4);

                    break;

                case 0x20: // Source Lane2

                    ScalerSetBit(PB_F0_CDR_01, ~(_BIT5 | _BIT4), _D0_DP_LANE2 << 4);

                    break;

                case 0x30: // Source Lane3

                    ScalerSetBit(PB_F0_CDR_01, ~(_BIT5 | _BIT4), _D0_DP_LANE3 << 4);

                    break;
            }

            ScalerRead(PB_F0_CDR_01, 1, &g_ucDpRx0PhyCtsCtrl, _NON_AUTOINC);

            DebugMessageRx0("7. PHY CTS Loop", g_ucDpRx0PhyCtsCtrl);

            switch(g_ucDpRx0PhyCtsCtrl & 0x07)
            {
                case 0x01: // CDR Lock Check

                    ScalerSetByte(PB_F0_CDR_01, (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0))); // Clear DP PHY CTS Phase Info

                    ScalerDpRx0PhyCtsTp1SetPhy(_DP_NF_REF_XTAL);

                    if(ScalerDpRx0PhyCtsTp1Check() == _TRUE)
                    {
                        ScalerSetByte(PB_F1_CDR_02, 0x01);
                    }
                    else
                    {
                        ScalerSetByte(PB_F1_CDR_02, 0xFF);
                    }

                    break;

                case 0x02: // Symbol Lock Check

                    ScalerSetByte(PB_F0_CDR_01, (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                    ScalerDpRx0PhyCtsTp2SetPhy();

                    if(ScalerDpRx0PhyCtsTp2Check() == _TRUE)
                    {
                        ScalerSetByte(PB_F1_CDR_02, 0x01);
                    }
                    else
                    {
                        ScalerSetByte(PB_F1_CDR_02, 0xFF);
                    }

                    break;

                case 0x03:

                    ScalerSetByte(PB_F0_CDR_01, (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

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

                    // Disable PRBS7 Error Detection
                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // Waiting for PHY Stable
                    ScalerTimerDelayXms(10);

                    // PRBS7 Pattern for RBR/HBR
                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB_F1_CDR_02, 0x00);
                    ScalerSetByte(PB_F2_CDR_03, 0x00);

                    break;

                case 0x04:

                    ScalerSetByte(PB_F0_CDR_01, (g_ucDpRx0PhyCtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                    ScalerTimerDelayXms(10);

                    if((ScalerGetByte(PB_09_BIST_PATTERN1) | ScalerGetByte(PB_0A_BIST_PATTERN2)) != 0x00)
                    {
                        ScalerSetByte(PB_F1_CDR_02, ScalerGetByte(PB_0B_BIST_PATTERN3));
                        ScalerSetByte(PB_F2_CDR_03, ScalerGetByte(PB_0C_BIST_PATTERN4));
                    }
                    else
                    {
                        ScalerSetByte(PB_F1_CDR_02, 0x0F);
                        ScalerSetByte(PB_F2_CDR_03, 0x0F);
                    }

                    break;

                case 0x05:

                    // Disable PRBS7 Error Detection
                    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // Clear DP PHY CTS Result
                    ScalerSetByte(PB_F1_CDR_02, 0x00);
                    ScalerSetByte(PB_F2_CDR_03, 0x00);

                    // Clear DP PHY CTS Control Register
                    ScalerSetByte(PB_F0_CDR_01, 0x00);

                    CLR_DP_RX0_PHY_CTS_FLG();

                    break;

                default:

                    break;
            }

            if((g_ucDpRx0PhyCtsCtrl & 0x07) != 0x05)
            {
                if(((ScalerGetByte(PB_F0_CDR_01) & 0x30) >> 4) == _D0_DP_LANE0) // Source Lane0
                {
                    ScalerSetBit(PB_F0_CDR_01, ~(_BIT5 | _BIT4), _DP_SCALER_LANE0 << 4);
                }
                else if(((ScalerGetByte(PB_F0_CDR_01) & 0x30) >> 4) == _D0_DP_LANE1) // Source Lane1
                {
                    ScalerSetBit(PB_F0_CDR_01, ~(_BIT5 | _BIT4), _DP_SCALER_LANE1 << 4);
                }
                else if(((ScalerGetByte(PB_F0_CDR_01) & 0x30) >> 4) == _D0_DP_LANE2) // Source Lane2
                {
                    ScalerSetBit(PB_F0_CDR_01, ~(_BIT5 | _BIT4), _DP_SCALER_LANE2 << 4);
                }
                else if(((ScalerGetByte(PB_F0_CDR_01) & 0x30) >> 4) == _D0_DP_LANE3) // Source Lane3
                {
                    ScalerSetBit(PB_F0_CDR_01, ~(_BIT5 | _BIT4), _DP_SCALER_LANE3 << 4);
                }

                DebugMessageRx0("7. PHY CTS Loop (Swap Back)", ScalerGetByte(PB_F0_CDR_01));
            }
            else
            {
                g_ucDpRx0PhyCtsCtrl = 0x00;
            }
        }
    }
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

    if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT)
    {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_ASSR_MODE_SUPPORT == _ON))
        // ASSR Mode Setting
        ScalerDpRx0ASSRModeSetting();
#endif
    }
    else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
    {
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_ASSR_MODE_SUPPORT == _ON))
        // ASSR Mode Setting
        ScalerDpRx0ASSRModeSetting();
#endif
    }

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    CLR_DP_RX0_SOURCE_TYPE_JUDGE();
#endif

    switch(GET_DP_RX0_LINK_TRAINING_STATUS())
    {
        case _DP_NORMAL_LINK_TRAINING_PASS:
        case _DP_LINK_STATUS_FAIL:

            CLR_DP_RX0_VALID_VIDEO_CHECK();

            if((ScalerDpRx0CDRCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
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

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
#endif

                if(GET_DP_RX0_NORMAL_LINK_TRAINING_SETPHY_FINISH() == _TRUE)
                {
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

                return _TRUE;
            }
            else
            {
                DebugMessageRx0("7. Link Status Fail IRQ", 0);

                SET_DP_RX0_AUX_MANUAL_MODE();

                if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
                {
                    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_STATUS_FAIL);

                    if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT)
                    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                        ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
#endif
                    }
                    else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
                    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                        ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
#endif
                    }
                }

                SET_DP_RX0_AUX_AUTO_MODE();
            }

            break;

        case _DP_LINK_TRAINING_FAIL:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
#endif

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

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
#endif

            SET_DP_RX0_AUX_MANUAL_MODE();

            if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
            {
                ScalerDpRx0RebuildPhy(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01));

                SET_DP_RX0_AUX_AUTO_MODE();

                ScalerDpRx0PassiveDFEFineTune();
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
               (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
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
        if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
#endif
        }
        else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
        {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
#endif
        }
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

    if(ScalerDpRx0StreamClkRegenerate() == _FALSE)
    {
        DebugMessageRx0("7. DP SteamClk Fail", 0);

        return _SOURCE_NONE;
    }

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
            ScalerDpRx0AdjustVsyncDelay();

            if(ScalerDpRx0FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
            {
                ScalerDpRx0AdjustVsyncDelay();

                if(ScalerDpRx0FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
                {
                    DebugMessageRx0("7. DP Fifo Fail", 0);

                    return _SOURCE_NONE;
                }
            }
        }
    }

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    // Measurement Enable for On-Line VFreq check
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);
#endif

    ScalerSetBit(PB5_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

#if(_AUDIO_SUPPORT == _ON)
    // Enable Audio Channel
    ScalerAudioDpAudioEnable(_ENABLE, _D0_INPUT_PORT);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    ScalerFreeSyncDpRx0GetSPDVfreqMaxMin();
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    ScalerDpRx0TimingInfoBackup();
#endif

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
       (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE))
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
    if((enumHpdType > _DP_HPD_LOW) && (ScalerSyncDpCableStatus(GET_DP_EMBEDDED_SWITCH_SELECT()) == _FALSE))
    {
        return;
    }

    // If the priority of enumHpdType is higher
    if(enumHpdType < GET_DP_RX0_HOTPLUG_ASSERT_TYPE())
    {
        SET_DP_RX0_HOTPLUG_ASSERT_TYPE(enumHpdType);
    }
}

#if(_DP_RX_ACTIVE_REDUCE_LANE_COUNT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Main Link Quality Management
// Input Value  : Dx Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0MainLinkQualityManagement(BYTE ucInputPort)
{
    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == _DP_LINK_4_LANE)
    {
        if((GET_DP_RX0_MAIN_LINK_MARGINAL() == _TRUE) || (ScalerDpRx0MainLinkPerformanceCheck() == _FALSE))
        {
            ScalerDpLaneCountSwitch(ucInputPort, _DP_LINK_2_LANE);
            DebugMessageRx0("7. wuzanne test : DP Lane3 Marginal ", GET_DP_RX0_MAIN_LINK_MARGINAL());
            DebugMessageRx0("7. wuzanne test : Adjust DP Lane to 2", 0);
        }
    }
}

//--------------------------------------------------
// Description  : Main Link Performance Check
// Input Value  : None
// Output Value : True --> Main Link Good
//                False --> Main Link NG
//--------------------------------------------------
bit ScalerDpRx0MainLinkPerformanceCheck(void)
{
    WORD usLane0ErrorCount = 0x00;
    WORD usLane3ErrorCount = 0x00;
    BYTE ucTemp = 100;

    SET_DP_RX0_AUX_MANUAL_MODE();

    if((GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS) ||
       (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != _DP_LINK_4_LANE))
    {
        SET_DP_RX0_AUX_AUTO_MODE();

        return _TRUE;
    }

    SET_DP_RX0_AUX_AUTO_MODE();

    // Clear Error Count
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Start Error Count
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    while(ucTemp > 0)
    {
        ucTemp--;

        ScalerTimerDelayXms(1);

        if(GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
        {
            return _TRUE;
        }
    }

    // Read Lane0 Error Count
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), 0x00);
    usLane0ErrorCount = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    // Read Lane3 Error Count
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
    usLane3ErrorCount = (((WORD)(ScalerGetByte(PB_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    DebugMessageRx0("7. wuzanne test : Lane0 Error Count", usLane0ErrorCount);
    DebugMessageRx0("7. wuzanne test : Lane3 Error Count", usLane3ErrorCount);

    if(((usLane3ErrorCount > usLane0ErrorCount) && (usLane3ErrorCount >= 3)) || (usLane3ErrorCount >= 0x7FFE))
    {
        SET_DP_RX0_AUX_MANUAL_MODE();

        if(GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
        {
            SET_DP_RX0_AUX_AUTO_MODE();

            return _TRUE;
        }

        SET_DP_RX0_AUX_AUTO_MODE();

        return _FALSE;
    }

    return _TRUE;
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

    if(ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE)
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
#endif // End of #if(_D0_DP_EXIST == _ON)
