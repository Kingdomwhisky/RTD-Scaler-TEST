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
// ID Code      : RL6492_Series_TMDS.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_TMDS__

#include "ScalerFunctionInclude.h"

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Measure Clk Source
//--------------------------------------------------
#define _CLK_SOURCE_RED                         0
#define _CLK_SOURCE_BLUE                        1
#define _CLK_SOURCE_GREEN                       2
#define _CLK_SOURCE_TMDS                        3

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructTMDSCtrlInfo g_stTMDSRx0CtrlInfo;
StructTMDSCtrlInfo g_stTMDSRx1CtrlInfo;
StructTMDSCtrlInfo g_stTMDSRx2CtrlInfo;
WORD g_usTMDSClkCount;

#if(_D1_TMDS_SUPPORT == _ON)
BYTE g_ucTMDSRx1Z0Status;
#endif
#if(_D2_TMDS_SUPPORT == _ON)
BYTE g_ucTMDSRx2Z0Status;
#endif
BYTE g_ucTMDSSlaveAddr;

BYTE g_ucTMDSRx1HdcpType;
BYTE g_ucTMDSRx2HdcpType;

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
BYTE g_pucTmdsRx1Caps[3];
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
BYTE g_pucTmdsRx2Caps[3];
#endif
#endif
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTMDSInitial(BYTE ucInputPort);
void ScalerTMDSInterruptInitial(BYTE ucInputPort);
void ScalerTMDSSetDFEInitial_EXINT0(void);
void ScalerTMDSFLDBandFineTune_EXINT0(void);
void ScalerTMDSSetPhy_EXINT0(void);
void ScalerTMDSIntHandler_EXINT0(void);
void ScalerTMDSPSIntHandler_EXINT0(void);
bit ScalerTMDSCheckCDRStable(BYTE ucInputPort, WORD usClkCount);
BYTE ScalerTMDSCheckCDRStable_EXINT0(WORD usClkCount);
WORD ScalerTMDSMeasureClk(BYTE ucInputPort, BYTE ucMeasureClk);
WORD ScalerTMDSMeasureClk_EXINT0(BYTE ucMeasureClk);
void ScalerTMDSRx0SetPorchColor(EnumColorSpace enumColorFormat);

#if(_HDMI_SUPPORT == _ON)

void ScalerTMDSHdmiAVMuteProc(void);
bit ScalerTMDSYUV420SupportCheck(BYTE ucInputPort);

#if(_HDMI_2_0_SUPPORT == _ON)
void ScalerTMDSReadRequestProc_EXINT0(BYTE ucRROutCome);
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
void ScalerTMDSRx0HDMI2HPDRRIRQEnable(bit bEnable);
#endif
void ScalerTMDSHdmiReadRequestTimerEnable_WDINT(bit bEnable);
void ScalerTMDSHdmi2FormatResetEvent(EnumScalerTimerEventID enumEventID);
#endif

#endif

void ScalerTMDSPowerSavingProc(BYTE ucPortSelect);
void ScalerTMDSPowerOffProc(void);
void ScalerTMDSFirstActiveProc(BYTE ucInputPort, BYTE ucSourceType);

bit ScalerTMDSPSPreDetect(BYTE ucInputPort);
bit ScalerTMDSNormalPreDetect(BYTE ucInputPort);
BYTE ScalerTMDSScanInputPort(BYTE ucInputPort, BYTE ucInputType);
BYTE ScalerTMDSFormatDetect(void);
bit ScalerTMDSHdcpEnabled(BYTE ucInputPort);
bit ScalerTMDSStableDetect(BYTE ucInputPort, BYTE ucSourceType);
void ScalerTMDSHotPlugEvent(BYTE ucPortSelect);
void ScalerTMDSSwitchSlaveAddr(BYTE ucPortSelect);
void ScalerTMDSBeforeHotPlugEventProc(BYTE ucPortSelect);
void ScalerTMDSAfterHotPlugEventProc(BYTE ucPortSelect);
void ScalerTMDSBackupHdcpType(BYTE ucInputPort);
void ScalerTMDSHdcp1p4AksvClear(BYTE ucInputPort);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initialize TMDS setting for search
// Input Value  : Current Search Port
// Output Value : None
//--------------------------------------------------
void ScalerTMDSInitial(BYTE ucInputPort)
{
    // Disable TMDS output
    ScalerSetBit(P2_A6_TMDS_OUTCTL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // Set HS Width(DE only) and HDCP Reference VS
    ScalerSetBit(P2_AB_TMDS_ACC2, ~(_BIT7 | _BIT6), 0x00);

    // Disable C9/CA Port Auto-Inc
    ScalerSetBit(P2_C8_HDMI_APC, ~_BIT0, 0x00);

#if(_HDMI_SUPPORT == _ON)

    ScalerTMDSHdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

    // Deep Color Mode clock and detection auto
    ScalerSetBit(P2_B8_TMDS_DPC1, ~(_BIT3 | _BIT2), _BIT2);

    // Enable BCH Detection
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_02_PORT_PAGE2_HDMI_BCHCR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT3 | _BIT2 | _BIT1));

    // DVI mode don't disable Audio Clk
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

    // Set Video Watch Dog New Mode
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_32_PORT_PAGE2_HDMI_WDCR1, ~_BIT5, _BIT5);

    // Specify Packet Detect Type
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_43_PORT_PAGE2_HDMI_PTRSV0, _HDMI_AVI_INFO_TYPE);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_44_PORT_PAGE2_HDMI_PTRSV1, _HDMI_GENERAL_CONTROL_TYPE);

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_A4_PORT_PAGE2_HDMI_PTRSV_2, _SPD_INFO_TYPE);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_A5_PORT_PAGE2_HDMI_PTRSV_3, _HDR_INFO_TYPE);
#endif

    // Packet Variation Detect Disable
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_45_PORT_PAGE2_HDMI_PVGCR0, 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_46_PORT_PAGE2_HDMI_PVGCR1, 0x00);
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_47_PORT_PAGE2_HDMI_PVGCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_A9_PORT_PAGE2_HDMI_PVSR_4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_AA_PORT_PAGE2_HDMI_PVGCR3, 0x00);
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_AB_PORT_PAGE2_HDMI_PVGCR4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

#if(_HDMI_2_0_SUPPORT == _ON)

    if(ScalerGetBit(P2_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
    {
        // Disable HDMI 2.0 SCDC Function
        ScalerSetBit(P2_19_HDMI_CTRL_19, ~_BIT7, 0x00);
    }

    // Disable SCDC Scrambling Status
    ScalerSetDataPortBit(P2_39_HDMI_CTRL_39, _P2_3A_PT_21_PORT_PAGE02_HDMI_SCDC_21, ~_BIT0, 0x00);

    // Set Scrambling detection SSCP Number = 8, Enable HW Auto Detect Scrambling Control Symbol
    ScalerSetBit(P2_01_HDMI_CTRL_01, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1 | _BIT0));

    // Set SCDC Port not auto increase
    ScalerSetBit(P2_38_HDMI_CTRL_38, ~(_BIT4 | _BIT0), _BIT4);

    // Disable Ignore Source Transimit Read Request Enable
    ScalerSetBit(P2_1C_HDMI_CTRL_1C, ~_BIT2, 0x00);

    // Set Read Request 1ms reference clock to XTAL
    ScalerSetBit(P2_1A_HDMI_CTRL_1A, ~_BIT3, 0x00);

    // Set time interval form bus free to Read Request(4.7us~500us)
    ScalerSetBit(P2_1B_HDMI_CTRL_1B, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

    // Enable HDMI 2.0 Function
    ScalerSetBit(P2_00_HDMI_CTRL_00, ~_BIT0, _BIT0);

    // Enable HDMI 2.0 SCDC Module
    ScalerSetBit(P2_19_HDMI_CTRL_19, ~_BIT7, _BIT7);

#else

    // Disable HDMI 2.0 Function
    ScalerSetBit(P2_00_HDMI_CTRL_00, ~_BIT0, 0x00);

    // Disable HDMI 2.0 SCDC Function
    ScalerSetBit(P2_19_HDMI_CTRL_19, ~_BIT7, 0x00);

#endif

#endif

    switch(ucInputPort)
    {
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_DDC_CHANNEL_SEL == _DDC1)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), 0x00);
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), _BIT1);
#endif
            // Set HPD INT from D1 HPD pin
            ScalerSetBit(P10_45_HDMI_HPD_INT_SEL__ON1, ~_BIT0, 0x00);

            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
#if(_D2_DDC_CHANNEL_SEL == _DDC1)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), 0x00);
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), _BIT1);
#endif

            // Set HPD INT from D2 HPD pin
            ScalerSetBit(P10_45_HDMI_HPD_INT_SEL__ON1, ~_BIT0, _BIT0);

            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

        default:
            break;
    }

    // Set HDCP DDC Debounce, TMDS Function
    ScalerSetBit(P2_AC_TMDS_Z0CC2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Set HDCP Address is 0x74
    ScalerSetDataPortBit(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3A);

    // Set HDCP Feature
#if(_HDMI_SUPPORT == _ON)

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_0)
    ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_40_PORT_PAGE2_BCAPS, 0x81);
#elif(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_1)
    ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_40_PORT_PAGE2_BCAPS, 0x83);
#else
    ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_40_PORT_PAGE2_BCAPS, 0x81);
#endif

#else // Else of #if(_HDMI_SUPPORT == _ON)

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_0)
    ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_40_PORT_PAGE2_BCAPS, 0x01);
#elif(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_1)
    ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_40_PORT_PAGE2_BCAPS, 0x03);
#else
    ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_40_PORT_PAGE2_BCAPS, 0x01);
#endif

#endif // End of #if(_HDMI_SUPPORT == _ON)

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
    // Set HDMI frequency detection function clk from HDMI source
    ScalerSetBit(P2_E1_AUX_PS_REPLY, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
#else
    // MAC Select to HDMI
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT0, _BIT0);
#endif

    // PHY Select to HDMI
    ScalerSetBit(P1D_05_DIG_05, ~_BIT7, _BIT7);

    // Analog Select to HDMI
    ScalerSetBit(P1D_16_BANDGAP_02, ~_BIT5, 0x00);

    // Disable HDMI MAC Global Power Down
    ScalerSetBit(P2_AD_TMDS_CPS, ~_BIT1, 0x00);

    // Enable MAC Input
    ScalerSetBit(P2_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set MAC Signal Swap
    ScalerSetBit(P2_A7_TMDS_PWDCTL, ~(_BIT6 | _BIT5), ((ucInputPort == _D1_INPUT_PORT) ? ((_D1_TMDS_BR_SWAP << 6) | (_D1_TMDS_PN_SWAP << 5)) : ((_D2_TMDS_BR_SWAP << 6) | (_D2_TMDS_PN_SWAP << 5))));

    // Auto switch to DVI when no signal
    ScalerSetBit(P2_AD_TMDS_CPS, ~_BIT2, _BIT2);

    // Detect TMDS Format by Data Island Packet Preamble & Guard Band
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), _BIT1);

    // Enable TMDS MAC Error Correction
    ScalerSetBit(P2_B7_TMDS_UDC2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Set HDMI/DVI switch to Auto Mode
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
}

//--------------------------------------------------
// Description  : Initialize TMDS Interrupt Required Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSInterruptInitial(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    if(ScalerGetBit(P2_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
    {
        CLR_TMDS_PHY_SET();
    }

    // Enable Rx_En for Clk pair Z0
    ScalerSetBit(P1D_20_CMU_03, ~_BIT7, _BIT7);

    // Set Reg_bypass_ok=1 for solve P/N short(480p issue)
    ScalerSetBit(P1D_21_CMU_04, ~_BIT0, _BIT0);

    // Choose Measure Clk to TMDS Clk
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

    // Settings for IRQ set PHY
    // Consider using table to fill all required initial settings
    // Set pre-set threshold (225MHz * 0.01 / 26.8KHz = 0x54)

    // Set TMDS Offset = 1/32
    ScalerSetBit(P2_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
    // Set Upper Bound
    ScalerSetByte(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
    ScalerSetByte(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
    ScalerSetByte(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
    ScalerSetByte(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif

    // Set Lower Bound
    ScalerSetByte(P2_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
    ScalerSetByte(P2_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

    // Disable Freq. Unstable IRQ
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

    // Enable Freq. Stable IRQ
    ScalerSetBit(P2_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Set Stable Time (0x3F = about 5ms)
    ScalerSetByte(P2_EC_HDMI_FREQDET_STABLE, 0x3F);

    // Clear IRQ Pending Flag
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_60_PORT_PAGE2_HDMI_INTCR, ~_BIT7, _BIT7);

    // Internal IRQ Enable (Global)
    ScalerGlobalIRQControl(_ENABLE);

    EX0 = 1;

    // Start Freq. Detection
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : TMDS DFE Initial Setting (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSSetDFEInitial_EXINT0(void) using 1
{
    /////////////////////////
    // DFE Code Initialize //
    /////////////////////////

    // Initial DFE Code
    if(GET_INPUT_PIXEL_CLK() < 435)
    {
        // LE  Initial = 4
        ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x04);
        ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x04);
        ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x04);
    }
    else if(GET_INPUT_PIXEL_CLK() < 875)
    {
        // LE  Initial = 6
        ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x06);
        ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x06);
        ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x06);
    }
    else if(GET_INPUT_PIXEL_CLK() < 2250)
    {
        // LE Initial = 9
        ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x09);
        ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x09);
        ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x09);
    }
    else
    {
        // LE Initial = 12
        ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x0C);
        ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x0C);
        ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x0C);
    }

    // Tap0 Initial Value = 15
    ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P1D_B4_L1_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P1D_C4_L2_INIT_2, 0x0F);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P1D_A5_L0_INIT_3, 0x00);
    ScalerSetByte_EXINT(P1D_B5_L1_INIT_3, 0x00);
    ScalerSetByte_EXINT(P1D_C5_L2_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(P1D_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P1D_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P1D_C6_L2_INIT_4, 0x00);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x17);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x17);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x17);

    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x00);
}
//--------------------------------------------------
// Description  : TMDS FLD Band Fine Tune  (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSFLDBandFineTune_EXINT0(void) using 1
{
    WORD usLaneFreq = 0;
    BYTE ucCount = 0;
    BYTE ucBestVCOBand = 0;
    BYTE ucAutoVCOBand = 0;
    BYTE ucBacksetting2 = 0;

    // Get 3 Lane Auto Result
    ucAutoVCOBand = (ScalerGetByte_EXINT(P1D_34_ANA_CDR_06) & 0x7F);

    // Scan Lane
    ScalerSetBit_EXINT(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucAutoVCOBand);

    ucBacksetting2 = ScalerGetByte_EXINT(P2_EC_HDMI_FREQDET_STABLE);

    // Set Open Loop
    ScalerSetBit_EXINT(P1D_2E_ANA_CDR_00, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~(_BIT2 | _BIT1), _BIT1);

    // Change Measure Count  64=>3
    ScalerSetBit_EXINT(P2_EC_HDMI_FREQDET_STABLE, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

    // Read Lane0 Result
    ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT7), 0x00);
    ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT7), _BIT7);

    // Waiting For Measure Done -> 300us
    for(ucCount = 0; ucCount <= 60; ucCount++)
    {
        DELAY_5US_EXINT();
        if(ScalerGetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, _BIT6) == _BIT6)
        {
            // POP Result
            ScalerSetBit_EXINT(P2_EC_HDMI_FREQDET_STABLE, ~_BIT7, _BIT7);

            usLaneFreq = ((DWORD)((WORD)(ScalerGetByte_EXINT(P2_ED_HDMI_FREQDET_RESULT_M) << 8) | ScalerGetByte_EXINT(P2_EE_HDMI_FREQDET_RESULT_L))*27 / 100);

            break;
        }
    }

    if(usLaneFreq < GET_INPUT_PIXEL_CLK())
    {
        ucBestVCOBand = ucAutoVCOBand + 1;
    }
    else
    {
        ucBestVCOBand = ucAutoVCOBand;
    }

    // Reload Best Band
    ScalerSetBit_EXINT(P1D_33_ANA_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

    // Reload Measure TMDS Clock & Clear Unsatble IRQ Flag & Dummy POP Out
    ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT7), 0x00);
    ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT7), _BIT7);
    for(ucCount = 0; ucCount <= 60; ucCount++)
    {
        DELAY_5US_EXINT();
        if(ScalerGetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, _BIT6) == _BIT6)
        {
            // POP result
            ScalerSetBit_EXINT(P2_EC_HDMI_FREQDET_STABLE, ~_BIT7, _BIT7);
            break;
        }
    }
    // Set Stable Count
    ScalerSetByte_EXINT(P2_EC_HDMI_FREQDET_STABLE, ucBacksetting2);

    // Reload Measure TMDS Clock & Clear Unsatble IRQ Flag
    ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);
}

//-------------------------------------------------------------------
// Description  : TMDS Set PHY Function for HDMI+MHL2.0 (EXINT0 Only)
// Input Value  : None
// Output Value : None
//-------------------------------------------------------------------
void ScalerTMDSSetPhy_EXINT0(void) using 1
{
    BYTE ucIcp = 0;

    ///////////////
    // RX CMU EN //
    ///////////////

    // [7] cmu_en = 0 --> Disable CMU PLL
    ScalerSetBit_EXINT(P1D_21_CMU_04, ~_BIT7, 0x00);

    // [3:0] cdr_en = 4'b0000 --> Disable CDREN
    ScalerSetBit_EXINT(P1D_20_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [7:4] rx_en = 4'b1111 --> Enable RXEN
    ScalerSetBit_EXINT(P1D_20_CMU_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // dp_bbpd_sel = 2'b00 --> ACDR from Lane0
    ScalerSetBit_EXINT(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), 0x00);

    // [3] sel_iblpf = 1 --> Enable Local Bias LPF
    ScalerSetBit_EXINT(P1D_15_BANDGAP_01, ~_BIT3, _BIT3);

    DELAY_45US_EXINT();


    // [3:0] cdr_en = 4'b0001 ~ 4'b0011 ~ 4'b0111 ~ 4'b1111
    ScalerSetBit_EXINT(P1D_20_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P1D_20_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1D_20_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1D_20_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Recover Reg_bypass_ok=0 before koffset and after cdr_en=1
    // for solve P/N short(480p issue)
    ScalerSetBit_EXINT(P1D_21_CMU_04, ~_BIT0, 0x00);

    // DCDR
    if(GET_INPUT_PIXEL_CLK() < 2000)
    {
        // [4] ACDR_l3_en = 0
        ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT4, 0x00);
    }
    // HCDR
    else
    {
        // [4] ACDR_l3_en = 1
        ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT4, _BIT4);
    }


    /////////////////
    // CMU Setting //
    /////////////////

    // [0] PLL_WD_EN = 1'b0 --> Disable WD
    ScalerSetBit_EXINT(P1D_0F_WD, ~_BIT0, 0x00);

    // [7] sel_in_div4 = 0 --> Input Ref. Clock/1
    // [3] CMU_SEL_D4 = 0 --> CMU Feedback Loop/1
    ScalerSetBit_EXINT(P1D_24_CMU_07, ~(_BIT7 | _BIT3), 0x00);

    // DCDR
    if(ScalerGetBit_EXINT(P1D_12_ANA_CDR, _BIT4) == 0x00)
    {
        // [7:6] CMU_SEL_CP = 2'b10 --> CMU LPF Cp = 2pF for DCDR
        ScalerSetBit_EXINT(P1D_23_CMU_06, ~(_BIT7 | _BIT6), _BIT7);

        // [3:0] cdr_cp_in = 4'b1100 --> Icp = 37.5uA
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
    }
    // HCDR
    else
    {
        // [7:6] CMU_SEL_CP = 2'b00 --> CMU LPF Cp = 0pF for ACDR
        ScalerSetBit_EXINT(P1D_23_CMU_06, ~(_BIT7 | _BIT6), 0x00);

        // [3:0] cdr_cp_in = 4'b0110 --> Icp = 19.5uA
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    }

    ucIcp = ScalerGetByte_EXINT(P1D_31_ANA_CDR_03) & 0x0F;

    // [3] en_largers_forcmu = 1 --> CMU Rs increase 8K
    ScalerSetBit_EXINT(P1D_21_CMU_04, ~_BIT3, _BIT3);

    // [6:4] CMU_SEL_R1 = 3'b110 --> CMU LPF Rs = 16K + 8K
    ScalerSetBit_EXINT(P1D_24_CMU_07, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    // [6:4] SEL_CDR_RES = 3'b100 --> Analog CDR LPF Rs = 4K
    ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    if((GET_INPUT_PIXEL_CLK() >= 220) && (GET_INPUT_PIXEL_CLK() < 435))
    {
        // Analog CDR Auto FLD Counter
        // ref_conuter = 30
        // cdr_counter = 480
        // 30/480 = 1/16 = 5*(1/80 clock rate)
        ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetByte_EXINT(P1D_36_ANA_CDR_08, 0x1D);
        ScalerSetByte_EXINT(P1D_37_ANA_CDR_09, 0xDF);

        // [2:0] rate_sel = 3'b100 --> 218.75MHz ~ 437.5MHz
        ScalerSetBit_EXINT(P1D_3C_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

        // [1:0] SEL_DIV = 2'b11 --> 218.75MHz ~ 437.5MHz
        ScalerSetBit_EXINT(P1D_24_CMU_07, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // [5:4] CMU_SELPREDIV = 2'b00 --> /1
        ScalerSetBit_EXINT(P1D_25_CMU_08, ~(_BIT5 | _BIT4), 0x00);

        // [7:0] N_CODE = 0x4C --> 76 + 4 = 80
        ScalerSetByte_EXINT(P1D_1E_CMU_01, 0x4C);
    }
    else if((GET_INPUT_PIXEL_CLK() >= 435) && (GET_INPUT_PIXEL_CLK() < 875))
    {
        // Analog CDR Auto FLD Counter
        // ref_conuter = 50
        // cdr_counter = 400
        // 50/400 = 1/8 = 5*(1/40 clock rate)
        ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetByte_EXINT(P1D_36_ANA_CDR_08, 0x31);
        ScalerSetByte_EXINT(P1D_37_ANA_CDR_09, 0x8F);

        // [2:0] rate_sel = 3'b011 --> 437.5MHz ~ 875MHz
        ScalerSetBit_EXINT(P1D_3C_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

        // [1:0] SEL_DIV = 2'b10 --> 437.5MHz ~ 875MHz
        ScalerSetBit_EXINT(P1D_24_CMU_07, ~(_BIT1 | _BIT0), _BIT1);

        // [5:4] CMU_SELPREDIV = 2'b01 --> /1
        ScalerSetBit_EXINT(P1D_25_CMU_08, ~(_BIT5 | _BIT4), 0x00);

        // [7:0] N_CODE = 0x4C --> 36 + 4 = 40
        ScalerSetByte_EXINT(P1D_1E_CMU_01, 0x24);
    }
    else if((GET_INPUT_PIXEL_CLK() >= 875) && (GET_INPUT_PIXEL_CLK() < 1750))
    {
        // Analog CDR Auto FLD Counter
        // ref_conuter = 125
        // cdr_counter = 500
        // 125/500 = 1/4 = 5*(1/20 clock rate)
        ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetByte_EXINT(P1D_36_ANA_CDR_08, 0x7C);
        ScalerSetByte_EXINT(P1D_37_ANA_CDR_09, 0xF3);

        // [2:0] rate_sel = 3'b010 --> 875MHz ~ 1750MHz
        ScalerSetBit_EXINT(P1D_3C_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // [1:0] SEL_DIV = 2'b01 --> 875MHz ~ 1750MHz
        ScalerSetBit_EXINT(P1D_24_CMU_07, ~(_BIT1 | _BIT0), _BIT0);

        // [5:4] CMU_SELPREDIV = 2'b01 --> /1
        ScalerSetBit_EXINT(P1D_25_CMU_08, ~(_BIT5 | _BIT4), 0x00);

        // [7:0] N_CODE = 0x4C --> 16 + 4 = 20
        ScalerSetByte_EXINT(P1D_1E_CMU_01, 0x10);
    }
    else if(GET_INPUT_PIXEL_CLK() >= 1750)
    {
        // Analog CDR Auto FLD Counter
        // ref_conuter = 250
        // cdr_counter = 500
        // 250/500 = 1/2 = 5*(1/10 clock rate)
        ScalerSetBit_EXINT(P1D_35_ANA_CDR_07, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetByte_EXINT(P1D_36_ANA_CDR_08, 0xF9);
        ScalerSetByte_EXINT(P1D_37_ANA_CDR_09, 0xF3);

        // [2:0] rate_sel = 3'b001 --> 1750MHz ~ 3500MHz
        ScalerSetBit_EXINT(P1D_3C_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

        // [1:0] SEL_DIV = 2'b00 --> 1750MHz ~ 3500MHz
        ScalerSetBit_EXINT(P1D_24_CMU_07, ~(_BIT1 | _BIT0), 0x00);

        // [5:4] CMU_SELPREDIV = 2'b01 --> /2
        ScalerSetBit_EXINT(P1D_25_CMU_08, ~(_BIT5 | _BIT4), _BIT4);

        // [7:0] N_CODE = 0x4C --> 16 + 4 = 20
        ScalerSetByte_EXINT(P1D_1E_CMU_01, 0x10);
    }


    /////////////////
    // FLD Setting //
    /////////////////

    // [1:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 700M/v
    ScalerSetBit_EXINT(P1D_30_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);

    // [4] reg_sel_cont3 = 1'b1 --> BBPD UP/DN Pulse Div 3
    ScalerSetBit_EXINT(P1D_34_ANA_CDR_06, ~_BIT7, _BIT7);

    if(GET_INPUT_PIXEL_CLK() < 1500)
    {
        // KP_L0 = 8
        // KP_L1 = 8
        // KP_L2 = 8
        ScalerSetByte_EXINT(P1D_56_CDR_07, 0x20);
        ScalerSetByte_EXINT(P1D_57_CDR_08, 0x20);
        ScalerSetByte_EXINT(P1D_58_CDR_09, 0x20);
    }
    else
    {
        // KP_L0 = 5
        // KP_L1 = 5
        // KP_L2 = 5
        ScalerSetByte_EXINT(P1D_56_CDR_07, 0x14);
        ScalerSetByte_EXINT(P1D_57_CDR_08, 0x14);
        ScalerSetByte_EXINT(P1D_58_CDR_09, 0x14);
    }

    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [1] bypass_clk_rdy = 1 --> manual mode
    // [0] en_clkout_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(P1D_0E_SDM_04, ~(_BIT1 | _BIT0), _BIT1);

    // [1] bypass_eqen_rdy = 1 --> manual mode
    // [0] en_eqen_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(P1D_10_EQEN_TIMER, ~(_BIT1 | _BIT0), _BIT1);

    // [1] bypass_data_rdy = 1 --> manual mode
    // [0] en_data_manual = 0 --> Disable Dataout
    ScalerSetBit_EXINT(P1D_11_DATA_TIMER, ~(_BIT1 | _BIT0), _BIT1);

    // [7] Disable FLD Auto Mode
    ScalerSetBit_EXINT(P1D_2E_ANA_CDR_00, ~_BIT7, 0x00);

    // DCDR
    if(ScalerGetBit_EXINT(P1D_12_ANA_CDR, _BIT4) == 0x00)
    {
        // [3] EN_DATA_manual_l3 = 0
        // [2] Bypass_data_rdy_l3 = 0
        // [1] EN_eqen_manual_l3 = 0
        // [0] Bypass_eqen_rdy_l3 = 0
        ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    // HCDR
    else
    {
        // [3] EN_DATA_manual_l3 = 0
        // [2] Bypass_data_rdy_l3 = 1
        // [1] EN_eqen_manual_l3 = 0
        // [0] Bypass_eqen_rdy_l3 = 1
        ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));
    }

    // [7:4] RST_N = 4'b0000 --> Digital Circuit Reset
    ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [7:4] RST_N = 4'b1111 --> Digital Circuit Normal
    ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));


    /////////////////
    // DFE Setting //
    /////////////////

    // Load DFE Initial Code
    ScalerTMDSSetDFEInitial_EXINT0();

    // [7:5] LE_lowgain_highboost = 1 --> LE LowGain HighBoost Mode
    ScalerSetBit_EXINT(P1D_2B_KOFFSET_05, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    if(GET_INPUT_PIXEL_CLK() < 2000)
    {
        // [4] SEL_DFE_DELAY = 1'b1 --> Increase DFE Delay
        ScalerSetBit_EXINT(P1D_28_KOFFSET_02, ~_BIT6, _BIT6);
    }
    else
    {
        // [4] SEL_DFE_DELAY = 1'b0 --> Normal DFE Delay
        ScalerSetBit_EXINT(P1D_28_KOFFSET_02, ~_BIT6, 0x00);
    }

    if(GET_INPUT_PIXEL_CLK() < 2000)
    {
        // [7:5] LE_ISEL = 3'b000
        ScalerSetBit_EXINT(P1D_2C_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [7:5] LE_RLSEL = 3'b011
        ScalerSetBit_EXINT(P1D_2D_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));
    }
    else
    {
        // [7:5] LE_ISEL = 3'b010
        ScalerSetBit_EXINT(P1D_2C_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

        // [7:5] LE_RLSEL = 3'b001
        ScalerSetBit_EXINT(P1D_2D_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
    }

    //////////////
    // K Offset //
    //////////////

    // Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(P1D_29_KOFFSET_03, ~_BIT6, 0x00);

    // [6] Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~_BIT6, _BIT6);

    // [7] Toggle Foreground Calibration
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(P1D_2A_KOFFSET_04, ~_BIT7, _BIT7);

    // Waiting for K Offset
    DELAY_XUS_EXINT(150);

    // [2:0] Enable Tap0~2
    ScalerSetBit_EXINT(P1D_2E_ANA_CDR_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Reset Digital CDR
    ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    if(ScalerGetBit_EXINT(P1D_12_ANA_CDR, _BIT4) == 0x00)
    {
        ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit_EXINT(P1D_38_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    }

    ///////////////////
    // FLD Lock Band //
    ///////////////////

    // [7] reg_en_vco_lpf = 1 --> enable vco lpf
    // [2] reg_cp_en_manual = 1'b0 -->  Disable cp_en_manual
    // [1] reg_ac_en_manual = 0 --> Disable adp_en_manual
    // [3] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1), _BIT7);

    // [5] lane_en = 1 --> Enable FLD
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT5, _BIT5);

    // [7] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
    ScalerSetBit_EXINT(P1D_2E_ANA_CDR_00, ~_BIT7, _BIT7);

    // [6] xtal_en = 0 --> FLD Reference Input Clock
    ScalerSetBit_EXINT(P1D_30_ANA_CDR_02, ~_BIT6, 0x00);

    // [7] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~_BIT7, _BIT7);

    // [7] en_wide_temp = 1'b1 --> Enable Wide Temp VCO Band
    ScalerSetBit_EXINT(P1D_33_ANA_CDR_05, ~_BIT7, _BIT7);

    // [3:2] en_vcm_tune = 2'b11 --> Vc = Vdd/2
    ScalerSetBit_EXINT(P1D_32_ANA_CDR_04, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [7] reg_rstb_fsm --> Toggle for FLD reset
    // [6] reg_rstb_fld --> Toggle for FLD reset
    ScalerSetBit_EXINT(P1D_32_ANA_CDR_04, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P1D_32_ANA_CDR_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Waiting for VCO Stable
    DELAY_XUS_EXINT(360);

    // DCDR
    if(ScalerGetBit_EXINT(P1D_12_ANA_CDR, _BIT4) == 0x00)
    {
        // [7] cmu_en = 1'b1 --> Enable CMU PLL
        ScalerSetBit_EXINT(P1D_21_CMU_04, ~_BIT7, _BIT7);

        // Waiting for CMU PLL Stable
        DELAY_XUS_EXINT(150);

        // [0] en_clkout_manual = 1 --> Enable Clkout
        ScalerSetBit_EXINT(P1D_0E_SDM_04, ~_BIT0, _BIT0);
    }
    // HCDR
    else
    {
        // [0] en_clkout_manual = 1 --> Enable Clkout
        ScalerSetBit_EXINT(P1D_0E_SDM_04, ~_BIT0, _BIT0);

        // Set Manual FLD Fine Tune OK
        ScalerTMDSFLDBandFineTune_EXINT0();

        // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
        if(ucIcp > 7)
        {
            ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else
        {
            ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
        }

        // Waiting for VCO Stable
        DELAY_25US_EXINT();

        // Set Close Loop
        ScalerSetBit_EXINT(P1D_2F_ANA_CDR_01, ~_BIT2, _BIT2);

        // Waiting for VCO Stable
        DELAY_XUS_EXINT(80);

        // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

        // Waiting for VCO Stable
        DELAY_XUS_EXINT(80);

        // [3] en_data_manual_l3 = 1'b1 --> Enable Dataout for Lane3
        ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT3, _BIT3);

        // [3] en_eqen_manual_l3 = 1'b1 --> Enable Eqen for Lane3
        ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT1, _BIT1);
    }

    // [0] en_eqen_manual = 1 --> Enable Adaptation
    ScalerSetBit_EXINT(P1D_10_EQEN_TIMER, ~_BIT0, _BIT0);

    // Waiting for the Adaptation
    DELAY_XUS_EXINT(290);

    // [0] en_eqen_manual = 0 --> Disable Adaptation
    ScalerSetBit_EXINT(P1D_10_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 1 --> Enable Dataout
    ScalerSetBit_EXINT(P1D_11_DATA_TIMER, ~_BIT0, _BIT0);

    // Reset PHY -> MAC Interface
    ScalerSetBit_EXINT(P2_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P2_A7_TMDS_PWDCTL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Reset HDMI 3 Channel FIFO
    ScalerSetBit_EXINT(P2_B0_TMDS_CHANNEL_FIFO, ~_BIT6, _BIT6);

    // HDMI 3 Channel FIFO Global Enable
    ScalerSetBit_EXINT(P2_B0_TMDS_CHANNEL_FIFO, ~(_BIT7 | _BIT6), _BIT7);

    // Clear RGB Data Detection Flags
    ScalerSetBit_EXINT(P2_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5));
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSIntHandler_EXINT0(void) using 1
{
#if(_HDMI_2_0_SUPPORT == _ON)
    BYTE pucBackUp[4];
#else
    BYTE pucBackUp[2];
#endif

    WORD usCount = 0;

    pucBackUp[0] = ScalerGetByte_EXINT(P2_C9_HDMI_AP);
    pucBackUp[1] = ScalerGetByte_EXINT(P2_C8_HDMI_APC);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P2_C8_HDMI_APC, ~_BIT0, 0x00);

#if(_HDMI_2_0_SUPPORT == _ON)
    pucBackUp[2] = ScalerGetByte_EXINT(P2_39_HDMI_CTRL_39);
    pucBackUp[3] = ScalerGetByte_EXINT(P2_38_HDMI_CTRL_38);
#endif

    // Freq. Stable Into IRQ
    if((ScalerGetByte_EXINT(P2_EF_HDMI_ERROR_TH) & 0xC0) == 0xC0)
    {
        // Disable Freq Stable IRQ
        ScalerSetBit_EXINT(P2_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), _BIT6);

#if(_HDMI_2_0_SUPPORT == _ON)
        // Set SCDC Port Clock Detected
        ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_40_PORT_PAGE02_HDMI_SCDC_40);
        ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

        // Disable Reset HDMI/DVI Format
        ScalerSetBit_EXINT(P2_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_10_PORT_PAGE02_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P2_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX0_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P2_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P2_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
#endif

        // Enable Freq unstable IRQ
        ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Pop up Counter Value
        ScalerSetBit_EXINT(P2_EC_HDMI_FREQDET_STABLE, ~_BIT7, _BIT7);

        usCount = (WORD)(((ScalerGetByte_EXINT(P2_ED_HDMI_FREQDET_RESULT_M) & 0x7F) << 8) | ScalerGetByte_EXINT(P2_EE_HDMI_FREQDET_RESULT_L));

        // TMDS_FREQ(MHz) = GDI_CLK(MHz) * CLK_COUNT * _TMDS_MEASURE_CLOCK_DIVIDER / _TMDS_MEASURE_CLOCK_COUNTER
        SET_INPUT_PIXEL_CLK((((DWORD)_GDI_CLK_KHZ * usCount + 50000) / 100000));

        if(GET_INPUT_PIXEL_CLK() > 3000)
        {
            // Set Input Clock Measure Divider = /2
            ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0);
            ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~_BIT6, _BIT6);
        }
        else
        {
            // Set Input Clock Measure Divider = /1
            ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0);
            ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~_BIT6, 0x00);
        }

        if((GET_TMDS_PHY_SET() == _FALSE) || ((bit)ScalerTMDSCheckCDRStable_EXINT0(g_usTMDSClkCount) == _FALSE))
        {
            g_usTMDSClkCount = ScalerTMDSMeasureClk_EXINT0(_CLK_SOURCE_TMDS);

            // If Measure Divider = /2 then CLK x 2
            ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0);
            if(ScalerGetBit_EXINT(P2_CA_HDMI_DP, _BIT6) == _BIT6)
            {
                // TMDS_OFFLine Measure FREQ(MHz) = GDI_CLK(MHz) * 1024 * 2 / g_usTMDSClkCount
                SET_TMDS_OFFLINE_MEASURE_CLK(((DWORD)(_GDI_CLK_KHZ * 1024) * 2 / 100) / g_usTMDSClkCount);
            }
            else
            {
                // TMDS_OFFLine Measure FREQ(MHz) = GDI_CLK(MHz) * 1024 / g_usTMDSClkCount
                SET_TMDS_OFFLINE_MEASURE_CLK(((DWORD)(_GDI_CLK_KHZ * 1024) / 100) / g_usTMDSClkCount);
            }

            ScalerTMDSSetPhy_EXINT0();
        }

        // Set Upper Bound (allow 1/64 freq shift)
        ScalerSetByte_EXINT(P2_E8_HDMI_FREQDET_UPPER_M, (HIBYTE(usCount + (usCount >> 6)) & 0x7F));
        ScalerSetByte_EXINT(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(usCount + (usCount >> 6)));

        // Set Lower bound
        ScalerSetByte_EXINT(P2_EA_HDMI_FREQDET_LOWER_M, (HIBYTE(usCount - (usCount >> 6)) & 0x7F));
        ScalerSetByte_EXINT(P2_EB_HDMI_FREQDET_LOWER_L, LOBYTE(usCount - (usCount >> 6)));

        // Reset Color Depth to 8 Bits
        SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);
        SET_TMDS_PHY_SET();

#if(_HDMI_2_0_SUPPORT == _ON)
        // Clear CED Lock Transition Flag
        ScalerSetBit_EXINT(P2_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Set HDMI 2.0 Character Error Detection Function Lock Transition Error Boundary
        ScalerSetBit_EXINT(P2_14_HDMI_CTRL_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_INPUT_PIXEL_CLK() / 10) >> 8);
        ScalerSetByte_EXINT(P2_15_HDMI_CTRL_15, (GET_INPUT_PIXEL_CLK() / 10));

        // Enable Character Error Detection Function & Valid Flag
        ScalerSetBit_EXINT(P2_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

        // Enable Character Error Detction Function Lock Transition IRQ
        ScalerSetBit_EXINT(P2_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
    }

    // Freq. Unstable Into IRQ
    if((ScalerGetByte_EXINT(P2_E6_HDMI_FREQDET_CTRL) & 0x06) == 0x06)
    {
        // Clear Unstable IRQ Flag
        ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

        // Ensure Freq really unstable
        if((abs(g_usTMDSClkCount - ScalerTMDSMeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (g_usTMDSClkCount >> 6)) ||
           (abs(GET_INPUT_PIXEL_CLK() - ((GET_TMDS_OFFLINE_MEASURE_CLK() << 3) / ((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) ? _COLOR_DEPTH_8_BITS : GET_COLOR_DEPTH()))) > (GET_INPUT_PIXEL_CLK() >> 6)))
        {
            if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
            {
                // Set Display M1 output force to background color and free run mode
                ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);
            }

            // Disable RGB/clock Output to avoid garbage
            ScalerSetBit_EXINT(P2_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

#if(_HDMI_2_0_SUPPORT == _ON)

            // Clear Scrambling Detection Flag
            ScalerSetBit_EXINT(P2_01_HDMI_CTRL_01, ~_BIT3, _BIT3);

            // Disable Scrambling Status
            ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_21_PORT_PAGE02_HDMI_SCDC_21);
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT0, 0x00);

            // Disable CED Function
            ScalerSetBit_EXINT(P2_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

            // Pop Up CED Error For Clear Error Counter
            ScalerSetBit_EXINT(P2_0C_HDMI_CTRL_0C, ~_BIT7, _BIT7);

            // Disable CED Lock Transition IRQ & Flag
            ScalerSetBit_EXINT(P2_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P2_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // Clear SCDC Port Status Update Flag & CED Update Flag
            ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_10_PORT_PAGE02_HDMI_SCDC_10);
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~(_BIT1 | _BIT0), 0x00);

            // Clear SCDC Port Status Lock Flag
            ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_40_PORT_PAGE02_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Reset HDMI/DVI Format
            ScalerSetBit_EXINT(P2_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
#endif

            // Disable Freq. Unstable IRQ
            ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
            // Set Upper Bound
            ScalerSetByte_EXINT(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
            ScalerSetByte_EXINT(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
            ScalerSetByte_EXINT(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
            ScalerSetByte_EXINT(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
            // Set Lower bound
            ScalerSetByte_EXINT(P2_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
            ScalerSetByte_EXINT(P2_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

            // Reset Freq. Detect Counter(Toggle)
            ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

            // Enable Freq. Stable IRQ
            ScalerSetBit_EXINT(P2_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            CLR_TMDS_PHY_SET();

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            // Reset Authenticated FSM
            ScalerSetByte_EXINT(P2D_28_HDCP_I2C_CTRL_2, 0x01);
            ScalerSetBit_EXINT(P2D_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);

            if(CHECK_TMDS_DPHY_SWITCH(_D1_INPUT_PORT) == _TRUE)
            {
#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
                // Cancel HDCP 2.2 Re-Auth Timer Event
                ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX1_HDCP2_REAUTH);
#endif
            }
            else
            {
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
                // Cancel HDCP 2.2 Re-Auth Timer Event
                ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH);
#endif
            }

#endif
        }
    }

#if(_HDMI_2_0_SUPPORT == _ON)

    // Detect Source Write Read Request Enable Flag
    if((ScalerGetBit_EXINT(P2_25_HDMI_CTRL_25, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P2_26_HDMI_CTRL_26, _BIT3) == _BIT3))
    {
        // Clear Read Request Flag
        ScalerSetBit_EXINT(P2_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Set Read Request Enable
        SET_HDMI_2_0_RX0_RR_ENABLE();

        // Enable Test Read Request HW Auto Mode
        ScalerSetBit_EXINT(P2_1C_HDMI_CTRL_1C, ~_BIT1, _BIT1);

        // Enable CED Update Read Request Auto Mode
        ScalerSetBit_EXINT(P2_24_HDMI_CTRL_24, ~_BIT0, _BIT0);

        // Enable Read Request Done IRQ
        ScalerSetBit_EXINT(P2_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
    }

    // Detect CED Channel 2 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P2_17_HDMI_CTRL_17, _BIT2) == _BIT2) && (ScalerGetBit_EXINT(P2_18_HDMI_CTRL_18, _BIT2) == _BIT2))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P2_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P2_17_HDMI_CTRL_17, _BIT5) == _BIT5)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_40_PORT_PAGE02_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT3, _BIT3);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_40_PORT_PAGE02_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT3, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_10_PORT_PAGE02_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P2_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX0_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P2_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P2_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Detect CED Channel 1 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P2_17_HDMI_CTRL_17, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P2_18_HDMI_CTRL_18, _BIT1) == _BIT1))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P2_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P2_17_HDMI_CTRL_17, _BIT4) == _BIT4)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_40_PORT_PAGE02_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT2, _BIT2);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_40_PORT_PAGE02_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT2, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_10_PORT_PAGE02_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P2_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX0_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P2_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P2_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Detect CED Channel 0 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P2_17_HDMI_CTRL_17, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P2_18_HDMI_CTRL_18, _BIT0) == _BIT0))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P2_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P2_17_HDMI_CTRL_17, _BIT3) == _BIT3)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_40_PORT_PAGE02_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT1, _BIT1);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_40_PORT_PAGE02_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT1, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, _P2_3A_PT_10_PORT_PAGE02_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P2_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P2_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX0_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P2_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P2_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Read Request Done into IRQ
    if((ScalerGetBit_EXINT(P2_1F_HDMI_CTRL_1F, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P2_1C_HDMI_CTRL_1C, _BIT7) == _BIT7))
    {
        // Clear Read Request Done Flag
        ScalerSetBit_EXINT(P2_1C_HDMI_CTRL_1C, ~_BIT7, _BIT7);

        // Read Request Outcome Processing
        ScalerTMDSReadRequestProc_EXINT0(ScalerGetByte_EXINT(P2_1C_HDMI_CTRL_1C) & 0x70);
    }

    // Detect HDMI HPD Rising to Falling into IRQ
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(P2_23_HDMI_CTRL_23, (_BIT6 | _BIT1)) == (_BIT6 | _BIT1))
    {
        // Clear HPD IRQ Flag
        ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~_BIT1, _BIT1);

        if(ScalerGetBit_EXINT(P2_23_HDMI_CTRL_23, (_BIT2 | _BIT0)) == 0x00)
        {
            // Clear All Source Write SCDC Port Register
            ScalerSetBit_EXINT(P2_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Clear HDMI 2.0 Read Request Enable
            CLR_HDMI_2_0_RX0_RR_ENABLE();

            // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~_BIT6, _BIT6);

            /*
            // Disable Test Read Request HW Auto Mode
            ScalerSetBit_EXINT(P2_1C_HDMI_CTRL_1C, ~_BIT1, 0x00);

            // Disable CED Update Read Request Auto Mode
            ScalerSetBit_EXINT(P2_24_HDMI_CTRL_24, ~_BIT0, 0x00);

            // Disable Character Error Detection Function
            ScalerSetBit_EXINT(P2_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

            // Disable Lock Transition IRQ
            ScalerSetBit_EXINT(P2_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            ScalerSetBit_EXINT(P2_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Detect 3 Channel CDR Stable
            if((bit)ScalerTMDSCheckCDRStable_EXINT(g_usTMDSRx1ClkCount) == _TRUE)
            {
                // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

                // Enable Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
            }
            */
        }
        else
        {
            /*
            // Enable CED Function
            ScalerSetBit_EXINT(P2_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

            // Enable CED Lock Transition IRQ
            ScalerSetBit_EXINT(P2_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            ScalerSetBit_EXINT(P2_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Enable SCDC Module
            ScalerSetBit_EXINT(P2_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
            */

            // Disable Falling to Rising IRQ, Set IRQ Status Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);

            // Enable Rising to edge IRQ
            ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
        }
    }
#endif // End of #if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)

#endif // End of #if(_HDMI_2_0_SUPPORT == _ON)

    // HDCP 1.4 Write Aksv IRQ have been Received
    if((ScalerGetBit_EXINT(P2_A9_TMDS_ABC0, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P2_AA_TMDS_ABC1, _BIT4) == _BIT4))
    {
        // clear AKSV flag
        ScalerSetBit_EXINT(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), _BIT7);

        // set ready bit
        ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, _BIT1);

#if(_HDCP_2_2_SUPPORT == _ON)
        // Enable HDCP 1.4 Module
        ScalerSetBit_EXINT(P2_C0_HDCP_CR, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Disable HDCP 2 Function
        ScalerSetBit_EXINT(P2D_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);
#endif
    }

#if(_AUDIO_SUPPORT == _ON)
    // Detect if Auido Sampling is Changed
    ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET);
    if(ScalerGetBit_EXINT(P2_CA_HDMI_DP, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1))
    {
        // Clear Auido Sampling Change Flag
        ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET);
        ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~_BIT1, _BIT1);

#if(_LINE_IN_SUPPORT == _ON)
        if(ScalerAudioGetInputSource_EXINT0() == _DIGITAL_AUDIO)
#endif
        {
            // Disable FIFO Boundary Tracking, Disable Trend Tracking
            ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR);
            ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~(_BIT3 | _BIT2), 0x00);

            // Set Double Buffer bit
            ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR);
            ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~_BIT4, _BIT4);

            // Reload D code
            ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0);
            ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~_BIT6, _BIT6);
            ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0);
            ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~_BIT6, 0x00);
        }
    }
#endif

    // Clear IRQ Pending Flag
    ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_60_PORT_PAGE2_HDMI_INTCR);
    ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~_BIT7, _BIT7);

    ScalerSetByte_EXINT(P2_C8_HDMI_APC, pucBackUp[1]);
    ScalerSetByte_EXINT(P2_C9_HDMI_AP, pucBackUp[0]);

#if(_HDMI_2_0_SUPPORT == _ON)
    ScalerSetByte_EXINT(P2_38_HDMI_CTRL_38, pucBackUp[3]);
    ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, pucBackUp[2]);
#endif
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process In PS/PD State(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSPSIntHandler_EXINT0(void) using 1
{
#if(_HDMI_2_0_SUPPORT == _ON)
    BYTE pucBackUp[4];
#else
    BYTE pucBackUp[2];
#endif

    pucBackUp[0] = ScalerGetByte_EXINT(P2_C9_HDMI_AP);
    pucBackUp[1] = ScalerGetByte_EXINT(P2_C8_HDMI_APC);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P2_C8_HDMI_APC, ~_BIT0, 0x00);

#if(_HDMI_2_0_SUPPORT == _ON)
    pucBackUp[2] = ScalerGetByte_EXINT(P2_39_HDMI_CTRL_39);
    pucBackUp[3] = ScalerGetByte_EXINT(P2_38_HDMI_CTRL_38);
#endif

    // HDCP 1.4 Write Aksv IRQ have been Received
    if((ScalerGetBit_EXINT(P2_A9_TMDS_ABC0, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P2_AA_TMDS_ABC1, _BIT4) == _BIT4))
    {
        // clear AKSV flag
        ScalerSetBit_EXINT(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), _BIT7);

        // set ready bit
        ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, _BIT1);

#if(_HDCP_2_2_SUPPORT == _ON)
        // Enable HDCP 1.4 Module
        ScalerSetBit_EXINT(P2_C0_HDCP_CR, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Disable HDCP 2 Function
        ScalerSetBit_EXINT(P2D_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);
#endif
    }

#if(_HDMI_2_0_SUPPORT == _ON)
    // Detect Source Write Read Request Enable Flag
    if((ScalerGetBit_EXINT(P2_25_HDMI_CTRL_25, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P2_26_HDMI_CTRL_26, _BIT3) == _BIT3))
    {
        // Clear Read Request Flag
        ScalerSetBit_EXINT(P2_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Set Read Request Enable
        SET_HDMI_2_0_RX0_RR_ENABLE();

        // Enable Test Read Request HW Auto Mode
        ScalerSetBit_EXINT(P2_1C_HDMI_CTRL_1C, ~_BIT1, _BIT1);

        // Enable CED Update Read Request Auto Mode
        ScalerSetBit_EXINT(P2_24_HDMI_CTRL_24, ~_BIT0, _BIT0);

        // Enable Read Request Done IRQ
        ScalerSetBit_EXINT(P2_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
    }

    // Read Request Done into IRQ
    if((ScalerGetBit_EXINT(P2_1F_HDMI_CTRL_1F, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P2_1C_HDMI_CTRL_1C, _BIT7) == _BIT7))
    {
        // Clear Read Request Done Flag
        ScalerSetBit_EXINT(P2_1C_HDMI_CTRL_1C, ~_BIT7, _BIT7);

        // Read Request Outcome Processing
        ScalerTMDSReadRequestProc_EXINT0(ScalerGetByte_EXINT(P2_1C_HDMI_CTRL_1C) & 0x70);
    }

    // Detect HDMI HPD Rising to Falling into IRQ
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(P2_23_HDMI_CTRL_23, (_BIT6 | _BIT1)) == (_BIT6 | _BIT1))
    {
        // Clear HPD IRQ Flag
        ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~_BIT1, _BIT1);

        if(ScalerGetBit_EXINT(P2_23_HDMI_CTRL_23, (_BIT2 | _BIT0)) == 0x00)
        {
            // Clear All Source Write SCDC Port Register
            ScalerSetBit_EXINT(P2_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Clear HDMI 2.0 Read Request Enable
            CLR_HDMI_2_0_RX0_RR_ENABLE();

            // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~_BIT6, _BIT6);

            /*
            // Disable Test Read Request HW Auto Mode
            ScalerSetBit_EXINT(P2_1C_HDMI_CTRL_1C, ~_BIT1, 0x00);

            // Disable CED Update Read Request Auto Mode
            ScalerSetBit_EXINT(P2_24_HDMI_CTRL_24, ~_BIT0, 0x00);

            // Disable Character Error Detection Function
            ScalerSetBit_EXINT(P2_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

            // Disable Lock Transition IRQ
            ScalerSetBit_EXINT(P2_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            ScalerSetBit_EXINT(P2_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Detect 3 Channel CDR Stable
            if((bit)ScalerTMDSCheckCDRStable_EXINT(g_usTMDSRx1ClkCount) == _TRUE)
            {
                // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

                // Enable Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
            }
            */
        }
        else
        {
            /*
            // Enable CED Function
            ScalerSetBit_EXINT(P2_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

            // Enable CED Lock Transition IRQ
            ScalerSetBit_EXINT(P2_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            ScalerSetBit_EXINT(P2_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Enable SCDC Module
            ScalerSetBit_EXINT(P2_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
            */

            // Disable Falling to Rising IRQ, Set IRQ Status Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);

            // Enable Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P2_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
        }
    }
#endif // End of #if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
#endif // End of #if(_HDMI_2_0_SUPPORT == _ON)

    // Clear IRQ Pending Flag
    ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_60_PORT_PAGE2_HDMI_INTCR);
    ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~_BIT7, _BIT7);

    ScalerSetByte_EXINT(P2_C8_HDMI_APC, pucBackUp[1]);
    ScalerSetByte_EXINT(P2_C9_HDMI_AP, pucBackUp[0]);

#if(_HDMI_2_0_SUPPORT == _ON)
    ScalerSetByte_EXINT(P2_38_HDMI_CTRL_38, pucBackUp[3]);
    ScalerSetByte_EXINT(P2_39_HDMI_CTRL_39, pucBackUp[2]);
#endif
}

//--------------------------------------------------
// Description  : Check CDR Locked
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
bit ScalerTMDSCheckCDRStable(BYTE ucInputPort, WORD usClkCount)
{
    // Check Current Measured Freq. is the same as previously locked
    if(abs(usClkCount - ScalerTMDSMeasureClk(ucInputPort, _CLK_SOURCE_RED)) > (usClkCount >> 6))
    {
        return _FALSE;
    }

    if(abs(usClkCount - ScalerTMDSMeasureClk(ucInputPort, _CLK_SOURCE_BLUE)) > (usClkCount >> 6))
    {
        return _FALSE;
    }

    if(abs(usClkCount - ScalerTMDSMeasureClk(ucInputPort, _CLK_SOURCE_GREEN)) > (usClkCount >> 6))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check CDR Locked (EXINT0 Only)
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
BYTE ScalerTMDSCheckCDRStable_EXINT0(WORD usClkCount) using 1
{
    // Check Current Measured Freq. is the same as previously locked
    if(abs(usClkCount - ScalerTMDSMeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
    {
        return _FALSE;
    }

    if(abs(usClkCount - ScalerTMDSMeasureClk_EXINT0(_CLK_SOURCE_RED)) > (usClkCount >> 6))
    {
        return _FALSE;
    }

    if(abs(usClkCount - ScalerTMDSMeasureClk_EXINT0(_CLK_SOURCE_BLUE)) > (usClkCount >> 6))
    {
        return _FALSE;
    }

    if(abs(usClkCount - ScalerTMDSMeasureClk_EXINT0(_CLK_SOURCE_GREEN)) > (usClkCount >> 6))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Measure Clk
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerTMDSMeasureClk(BYTE ucInputPort, BYTE ucMeasureClk)
{
    BYTE ucDelayCount = 0;

    ucInputPort = ucInputPort;

    // Enable CMU_EN(Lane0,1,2) and Rx_EN(Lane0,1,2,3)
    ScalerSetByte(P1D_20_CMU_03, 0xFF);

    // Disable Measure for Reset Measure Window
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0, ~(_BIT5 | _BIT4 | _BIT3), 0x00);

    // Select reference clk to Xtal Clk and measure clk
    ScalerSetBit(P2_AD_TMDS_CPS, ~(_BIT6 | _BIT5 | _BIT4), ((ucMeasureClk << 5) | _BIT4));

    // Start Measure
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0, ~(_BIT5 | _BIT4 | _BIT3), _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        DELAY_5US();

        if((ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerGetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0, 2, &pData[0], _AUTOINC);

    return ((WORD)(pData[0] & 0x07) << 8) | pData[1];
}

//--------------------------------------------------
// Description  : Measure Clk (EXINT0 Only)
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerTMDSMeasureClk_EXINT0(BYTE ucMeasureClk) using 1
{
    BYTE ucDelayCount = 0;
    WORD usClkCount = 0;
    BYTE ucBackUp = 0;

    // Enable CMU_EN(Lane0,1,2) and Rx_EN(Lane0,1,2,3)
    ScalerSetByte_EXINT(P1D_20_CMU_03, 0xFF);

    // Disable Measure for Reset Measure Window
    ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0);
    ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~(_BIT5 | _BIT4 | _BIT3), 0x00);

    // Select reference clk to Xtal Clk and measure clk
    ScalerSetBit_EXINT(P2_AD_TMDS_CPS, ~(_BIT6 | _BIT5 | _BIT4), ((ucMeasureClk << 5) | _BIT4));

    ucBackUp = ScalerGetByte_EXINT(P2_C8_HDMI_APC);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P2_C8_HDMI_APC, ~_BIT0, 0x00);

    // Start Measure
    ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0);
    ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~(_BIT5 | _BIT4 | _BIT3), _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        DELAY_5US_EXINT();

        if((ScalerGetBit_EXINT(P2_CA_HDMI_DP, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0);
    usClkCount = ((WORD)(ScalerGetByte_EXINT(P2_CA_HDMI_DP) & 0x07) << 8);

    ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_29_PORT_PAGE2_HDMI_NTX1024TR1);
    usClkCount = usClkCount | ScalerGetByte_EXINT(P2_CA_HDMI_DP);

    ScalerSetByte_EXINT(P2_C8_HDMI_APC, ucBackUp);

    return usClkCount;
}

//--------------------------------------------------
// Description  : Set Back Ground Color
// Input Value  : InputPort and Current Color Space
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx0SetPorchColor(EnumColorSpace enumColorFormat)
{
    // Manual Set Background Color Enable
    ScalerSetBit(P2_B9_TMDS_OUT_CTRL, ~_BIT7, 0x00);

    if((enumColorFormat == _COLOR_SPACE_YCBCR444) || (enumColorFormat == _COLOR_SPACE_YCBCR422))
    {
        ScalerSetByte(P2_BA_TMDS_ROUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P2_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P2_BC_TMDS_GOUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P2_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P2_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P2_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YCBCR420)
    {
        ScalerSetByte(P2_BA_TMDS_ROUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P2_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P2_BC_TMDS_GOUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P2_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P2_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P2_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }

#endif
    else
    {
        ScalerSetByte(P2_BA_TMDS_ROUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P2_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P2_BC_TMDS_GOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P2_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P2_BE_TMDS_BOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P2_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
}

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hdmi Handle AVMute Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHdmiAVMuteProc(void)
{
    // if AVMute Has been triggered
    if((ScalerGetBit(P2_CB_HDMI_SR, _BIT6) == 0x00) && (ScalerGetBit(P2_A6_TMDS_OUTCTL, (_BIT6 | _BIT5 | _BIT4)) == 0x00))
    {
        // Clear AVMute Flag
        ScalerSetBit(P2_CB_HDMI_SR, ~_BIT7, _BIT7);

        // Disable AVMute Watch Dog
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT7, 0x00);

        // Enable Video/Audio Output
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_30_PORT_PAGE2_HDMI_AVMCR, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));

        // Enable RGB Output
        ScalerSetBit(P2_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

        // Enable AVMute Watch Dog
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : TMDS 420 Color Space Support Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerTMDSYUV420SupportCheck(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            // Check YCbCr 420 format; only support 8 bit
            if(ScalerColorGetColorSpace() == _COLOR_SPACE_YCBCR420)
            {
                return _FALSE;
            }

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(ScalerColorGetColorSpace() == _COLOR_SPACE_YCBCR420)
            {
                return _FALSE;
            }

            break;
#endif
        default:
            break;
    }

    return _TRUE;
}

#if(_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Read Request Outcome Case Processing(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSReadRequestProc_EXINT0(BYTE ucRROutCome) using 1
{
    // Get Read Request Outcome Case
    switch(ucRROutCome)
    {
        case _HDMI_2_0_READ_REQUEST_ACK_DONE:
        case _HDMI_2_0_READ_REQUEST_ACK_STOP:

            break;

        case _HDMI_2_0_READ_REQUEST_NACK1:

            if(GET_HDMI_2_0_RX0_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P2_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);
            }

            break;

        case _HDMI_2_0_READ_REQUEST_NACK2:

#if(_WD_TIMER_INT_SUPPORT == _ON)
            if(GET_HDMI_2_0_RX0_RR_ENABLE() == _TRUE)
            {
                // Enable Read Request Retry
                ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_RX1_HDMI_RR_RETRY);
            }
#endif

            break;

        default:

            break;
    }
}

#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS HPD IRQ Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx0HDMI2HPDRRIRQEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set HPD Debounce = 700 Clock Cycle
        // Set HPD IRQ Detect Rising to Falling Edge IRQ
        ScalerSetBit(P2_23_HDMI_CTRL_23, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT5 | _BIT4 | _BIT3 | _BIT1));

        // Enable HDMI HPD IRQ Enable
        ScalerSetBit(P2_23_HDMI_CTRL_23, ~_BIT6, _BIT6);

        // Write 1 Clear Read Request
        ScalerSetBit(P2_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Enable HDMI 2.0 SCDC IIC Module
        ScalerSetBit(P2_19_HDMI_CTRL_19, ~_BIT7, _BIT7);

        // Clear HDMI 2.0 Read Request Enable
        CLR_HDMI_2_0_RX0_RR_ENABLE();

        // Enable HDMI 2.0 Read Request Enable Detect IRQ
        ScalerSetBit(P2_26_HDMI_CTRL_26, ~_BIT3, _BIT3);
    }
    else
    {
        // Write 1 Clear Read Request
        ScalerSetBit(P2_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Clear HDMI 2.0 Read Request Enable
        CLR_HDMI_2_0_RX0_RR_ENABLE();

        // Disable HDMI 2.0 Read Request Enable Detect IRQ
        ScalerSetBit(P2_26_HDMI_CTRL_26, ~_BIT3, 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Hdmi Enable RR Timer
// Input Value  : bEnable => Enable RR Timer flag
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHdmiReadRequestTimerEnable_WDINT(bit bEnable) using 3
{
    if(bEnable == _ENABLE)
    {
        if(GET_HDMI_2_0_RX0_RR_ENABLE() == _TRUE)
        {
            // FW Manual Enable Read Request
            ScalerSetBit_EXINT(P2_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);
        }
    }
    else
    {
        // Disable Read Request Enable
        ScalerSetBit_EXINT(P2_1B_HDMI_CTRL_1B, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : TMDS Format Reset Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHdmi2FormatResetEvent(EnumScalerTimerEventID enumEventID)
{
    enumEventID = enumEventID;

    CLR_TMDS_RX0_HDMI_2_0_FORMAT_RESET_WAITING();
}
#endif // End of #if(_HDMI_2_0_SUPPORT == _ON)

#endif // End of #if(_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS Power Saving Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSPowerSavingProc(BYTE ucPortSelect)
{
    ucPortSelect = ucPortSelect;

    // Set Power Saving DDC Debounce Counter
    g_usDDCDebounceCnt = _TMDS_DDC_DEBOUNCE_PS;

    ScalerTMDSFreqDetectDisable();

    // Switch TMDS Input/Output to Auto
    ScalerSetBit(P2_A6_TMDS_OUTCTL, ~_BIT7, _BIT7);
    ScalerSetBit(P2_A7_TMDS_PWDCTL, ~_BIT4, _BIT4);

    // Set Freq. Stable Time: 5 times
    ScalerSetByte(P2_EC_HDMI_FREQDET_STABLE, 0x05);

    // Set Freq. Shift Offset to Max
    ScalerSetBit(P2_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
    // Set Upper Bound
    ScalerSetByte(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));
    ScalerSetByte(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));
#else
    ScalerSetByte(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_PS_LOW_SPEED_UPPER_BOUND));
    ScalerSetByte(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_PS_LOW_SPEED_UPPER_BOUND));
#endif


    // Set Counter Lower Bound
    ScalerSetByte(P2_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_PS_LOWER_BOUND));
    ScalerSetByte(P2_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_PS_LOWER_BOUND));
}

//--------------------------------------------------
// Description  : TMDS Power Off Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSPowerOffProc(void)
{
    // Disable EDID read/ SCL toggle IRQ
    MCU_FFE5_DDC1_EDID_IRQ = ((MCU_FFE5_DDC1_EDID_IRQ & ~(_BIT3 | _BIT1)) | (_BIT2 | _BIT0));
    MCU_FE69_DDC2_EDID_IRQ = ((MCU_FE69_DDC2_EDID_IRQ & ~(_BIT3 | _BIT1)) | (_BIT2 | _BIT0));

    ScalerTMDSFreqDetectDisable();
}

//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerTMDSFirstActiveProc(BYTE ucInputPort, BYTE ucSourceType)
{
    ucInputPort = ucInputPort;
    ucSourceType = ucSourceType;
}

//--------------------------------------------------
// Description  : Signal Detection for TMDS(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSPSPreDetect(BYTE ucInputPort)
{
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

    if((ucInputPort == _D1_INPUT_PORT) && (GET_TMDS_RX1_DDC_DETECTED() == _TRUE))
    {
        DebugMessageDigital("7. wuzanne test : Normal D1 DDC", 0);

        CLR_TMDS_RX1_DDC_DETECTED();

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX1_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_DDC_CHANNEL_SEL == _DDC1)
        if(((MCU_FFE5_DDC1_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX1_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX1_DDC_DETECTED();
        }
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
        if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX1_DDC_DETECTED() != _TRUE))
        {
            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
            MCU_FE69_DDC2_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX1_DDC_DETECTED();
        }
#endif // End of #if(_D1_DDC_CHANNEL_SEL == _DDC0)
    }
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

    if((ucInputPort == _D2_INPUT_PORT) && (GET_TMDS_RX2_DDC_DETECTED() == _TRUE))
    {
        DebugMessageDigital("7. wuzanne test : Normal D2 DDC", 0);

        CLR_TMDS_RX2_DDC_DETECTED();

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX2_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    if(ucInputPort == _D2_INPUT_PORT)
    {
#if(_D2_DDC_CHANNEL_SEL == _DDC1)
        if(((MCU_FFE5_DDC1_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX2_DDC_DETECTED();
        }
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
        if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
        {
            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
            MCU_FE69_DDC2_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX2_DDC_DETECTED();
        }
#endif // End of #if(_D2_DDC_CHANNEL_SEL == _DDC0)
    }
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

    // Reset Freq. Detect Counter(Toggle) & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear Freq. Stable Flag
    ScalerSetBit(P2_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear Unstable Flag
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 5 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P2_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P2_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        if(ucInputPort == _D1_INPUT_PORT)
        {
            SET_TMDS_RX1_TOGGLE_Z0();
        }
        else if(ucInputPort == _D2_INPUT_PORT)
        {
            SET_TMDS_RX2_TOGGLE_Z0();
        }
#endif
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal PreDetection for TMDS(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSNormalPreDetect(BYTE ucInputPort)
{
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
    if((ucInputPort == _D1_INPUT_PORT) && (GET_TMDS_RX1_DDC_DETECTED() == _TRUE))
    {
        DebugMessageDigital("7. wuzanne test : Normal D1 DDC", 0);

        CLR_TMDS_RX1_DDC_DETECTED();

        return _TRUE;
    }

    if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_DDC_CHANNEL_SEL == _DDC1)
        if(((MCU_FFE5_DDC1_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX1_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX1_DDC_DETECTED();
        }
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
        if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX1_DDC_DETECTED() != _TRUE))
        {
            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
            MCU_FE69_DDC2_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX1_DDC_DETECTED();
        }
#endif
    }
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
    if((ucInputPort == _D2_INPUT_PORT) && (GET_TMDS_RX2_DDC_DETECTED() == _TRUE))
    {
        DebugMessageDigital("7. wuzanne test : Normal D2 DDC", 0);

        CLR_TMDS_RX2_DDC_DETECTED();

        return _TRUE;
    }

    if(ucInputPort == _D2_INPUT_PORT)
    {
#if(_D2_DDC_CHANNEL_SEL == _DDC1)
        if(((MCU_FFE5_DDC1_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX2_DDC_DETECTED();
        }
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
        if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
        {
            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
            MCU_FE69_DDC2_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX2_DDC_DETECTED();
        }
#endif // End of #if(_D2_DDC_CHANNEL_SEL == _DDC0)
    }
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

    ScalerTimerDelayXms(6);

    if(GET_TMDS_PHY_SET() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Port Source/Sync Scanning and Setting
// Input Value  : Input Port
// Output Value : Source DVI --> DVI Format
//                Source HDMI --> HDMI Format
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerTMDSScanInputPort(BYTE ucInputPort, BYTE ucInputType)
{
    BYTE ucTMDSType = _SOURCE_NONE;
    BYTE ucTMDSVideoDataType = _TMDS_VIDEO_DATA_NONE;

#if(_HDMI_SUPPORT == _ON)
    WORD usInputPixelClk = 0;
#endif

    ucInputType = ucInputType;

    switch(ucInputPort)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
            {
                return _SOURCE_NONE;
            }

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            if((ScalerGetBit(P2D_40_HDCP_2PX_ENCRYP_STS, (_BIT7 | _BIT6)) == _BIT7) && (GET_TMDS_RX1_HDCP2_AUTHENTICATION_DONE() != _TRUE) && (GET_TMDS_RX1_BACKUP_HDCP_TYPE() == _HDCP_22))
            {
                SET_TMDS_RX1_BACKUP_HDCP_TYPE(_HDCP_NONE);

                // Set RxStatus REAUTH_REQ
                ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
                ScalerSetDataPortBit(P2_C3_HDCP_AP, _P2_C4_PT_71_PORT_PAGE2_HDCP2_STATUS2, ~_BIT3, _BIT3);
                ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

                // Active HDCP 2.2 Re-Auth Timer Event for HPD Trigger Event Usage
                ScalerTimerActiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_RX1_HDCP2_REAUTH);

                return _SOURCE_NONE;
            }
#endif
            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
            {
                return _SOURCE_NONE;
            }

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            if((ScalerGetBit(P2D_40_HDCP_2PX_ENCRYP_STS, (_BIT7 | _BIT6)) == _BIT7) && (GET_TMDS_RX2_HDCP2_AUTHENTICATION_DONE() != _TRUE) && (GET_TMDS_RX2_BACKUP_HDCP_TYPE() == _HDCP_22))
            {
                SET_TMDS_RX2_BACKUP_HDCP_TYPE(_HDCP_NONE);

                // Set RxStatus REAUTH_REQ
                ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
                ScalerSetDataPortBit(P2_C3_HDCP_AP, _P2_C4_PT_71_PORT_PAGE2_HDCP2_STATUS2, ~_BIT3, _BIT3);
                ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

                // Active HDCP 2.2 Re-Auth Timer Event for HPD Trigger Event Usage
                ScalerTimerActiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH);

                return _SOURCE_NONE;
            }
#endif
            break;
#endif

        default:

            break;
    }

    if(GET_TMDS_PHY_SET() == _TRUE)
    {
        // Delay for PHY Stable
        ScalerTimerDelayXms(2);

#if(_HDMI_2_0_SUPPORT == _ON)
        if((ScalerTMDSCheckCDRStable(ucInputPort, g_usTMDSClkCount) == _FALSE) || (ScalerTMDSVideoDetect(_WAIT) == _TMDS_VIDEO_DATA_NONE))
#else
        if(ScalerTMDSCheckCDRStable(ucInputPort, g_usTMDSClkCount) == _FALSE)
#endif
        {
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
            // Set Upper Bound
            ScalerSetByte(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
            ScalerSetByte(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
            ScalerSetByte(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
            ScalerSetByte(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
            // Set Lower bound
            ScalerSetByte(P2_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
            ScalerSetByte(P2_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));


            // Set Stable Time (0x3F = about 5ms)
            ScalerSetByte(P2_EC_HDMI_FREQDET_STABLE, 0x3F);

            CLR_TMDS_PHY_SET();

            // Disable Freq. Unstable IRQ
            ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

            // Reset Freq. Detect Counter(Toggle)
            ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
            ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

            // Enable Freq. Stable IRQ
            ScalerSetBit(P2_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            DebugMessageDigital("Scan Input Port Clk UnStable", 0x00);

            return _SOURCE_NONE;
        }

        // Clear RGBHV Flag
        ScalerSetBit(P2_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear Info Packet SRAM
        ScalerSetBit(P2_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P2_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P2_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P2_CC_HDMI_GPVS, ~_BIT5, _BIT5);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
        // Clear DRR flag
        CLR_FREESYNC_ENABLED();
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
        // Clear SPD infoframe
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);
#endif

        DebugMessageRx1("9. Freq Check Pass => Pixel Clock", GET_INPUT_PIXEL_CLK());

#if(_HDMI_2_0_SUPPORT == _ON)

        // Disable Reset HDMI/DVI Format
        ScalerSetBit(P2_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

        DebugMessageRx1("HDMI 2.0 Error Boundary set High Byte", ScalerGetByte(P2_14_HDMI_CTRL_14));
        DebugMessageRx1("HDMI 2.0 Error Boundary set Low Byte", ScalerGetByte(P2_15_HDMI_CTRL_15));
#endif

        if(ScalerTMDSFormatDetect() == _SOURCE_HDMI)
        {
            DebugMessageDigital("Format Detect HDMI", 0x00);

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
            ScalerSetDataPortBit(P2_C3_HDCP_AP, _P2_C4_PT_40_PORT_PAGE2_BCAPS, ~_BIT1, _BIT1);
#endif

#if(_HDMI_FROM_DVI_CONNECT == _OFF)
            if(GET_PORT_TYPE(ucInputType) == _PORT_DVI)
            {
                return _SOURCE_NONE;
            }
#endif
            ucTMDSType = _SOURCE_HDMI;
        }
        else
        {
#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
            ScalerSetDataPortBit(P2_C3_HDCP_AP, _P2_C4_PT_40_PORT_PAGE2_BCAPS, ~_BIT1, 0x00);
#endif

            ucTMDSType = _SOURCE_DVI;
        }

        ucTMDSVideoDataType = ScalerTMDSVideoDetect(_WAIT);

        if(ucTMDSVideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
        {
            DebugMessageDigital("DE Only Mode", 0x00);

#if(_DVI_DE_ONLY_SUPPORT == _ON)
            if(ucTMDSType == _SOURCE_DVI)
            {
                // Enable DE Only Mode
                ScalerSetBit(P2_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
            }
            else
            {
                return _SOURCE_NONE;
            }
#else
            return _SOURCE_NONE;
#endif
        }
        else if(ucTMDSVideoDataType == _TMDS_VIDEO_DATA_RGBHV)
        {
            // Enable DE Only Mode
            ScalerSetBit(P2_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
        }
        else
        {
            return _SOURCE_NONE;
        }

#if(_HDMI_SUPPORT == _ON)
        if(ucTMDSType == _SOURCE_HDMI)
        {
            // HDMI packet detect --> AVI infoframe & GCP packet
            ScalerTMDSHdmiPacketDetect(_WAIT);

            ScalerSyncTMDSRx0HdmiVideoSetting();

            SET_COLOR_DEPTH(ScalerTMDSHdmiGetColorDepth());

            if((GET_COLOR_DEPTH() != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422))
            {
                DebugMessageDigital("Deep Color Mode Detected", GET_COLOR_DEPTH());

                // Backup Input Pixel clk
                usInputPixelClk = GET_INPUT_PIXEL_CLK();

                SET_INPUT_PIXEL_CLK((GET_INPUT_PIXEL_CLK() << 3) / GET_COLOR_DEPTH());

                if(ScalerTMDSHdmiDeepColorProc(g_usTMDSClkCount) == _FALSE)
                {
                    // Restore Input Pixel clk
                    SET_INPUT_PIXEL_CLK(usInputPixelClk);

                    return _SOURCE_NONE;
                }

                // Turn On Deep Color Block
                ScalerSetBit(P2_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            }
            else
            {
                // Turn off Deep Color Block
                ScalerSetBit(P2_B5_TMDS_UDC0, ~_BIT7, 0x00);
            }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
            if(GET_HDMIRX1_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE)
            {
                SET_HDMI_FREESYNC_ENABLED();

                // Get SPD Free Sync Vfreq Max
                g_usFREESYNCVFreq_max = (WORD)GET_HDMIRX1_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MAX_VFREQ) * 10;
                g_usFREESYNCVFreq_min = (WORD)GET_HDMIRX1_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MIN_VFREQ) * 10;

                // Disable DE Only Mode
                ScalerSetBit(P2_A7_TMDS_PWDCTL, ~_BIT7, 0x00);
            }
#endif
        }
        else
        {
            CLR_HDMI_RX0_AVI_INFO_FRAME_RECEIVED();

            CLR_HDMI_GCP_RECEIVED();

            // Disable All WD when DVI
            ScalerTMDSHdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            ScalerTMDSDviVideoSetting(ucInputPort);

            SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

            // Turn off Deep Color Block
            ScalerSetBit(P2_B5_TMDS_UDC0, ~_BIT7, 0x00);
        }
#else

        ScalerTMDSDviVideoSetting(ucInputPort);

        SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

        // Turn off Deep Color Block
        ScalerSetBit(P2_B5_TMDS_UDC0, ~_BIT7, 0x00);
#endif

        // Enable Video Output
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_30_PORT_PAGE2_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_80_PORT_PAGE2_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P2_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

        return ucTMDSType;
    }
    return _SOURCE_NONE;
}

//--------------------------------------------------
// Description  : Detect TMDS Format
// Input Value  : None
// Output Value : Return DVI or HDMI format
//--------------------------------------------------
BYTE ScalerTMDSFormatDetect(void)
{
    // Polling at least 3 frame for HW auto detect TMDS format
    if(ScalerTimerPollingFlagProc(130, P2_CB_HDMI_SR, _BIT0, _TRUE) == _TRUE)
    {
        ScalerSetBit(P2_AF_TMDS_WDC, ~_BIT0, 0x00);

#if(_HDMI_2_0_SUPPORT == _ON)
        if((GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE) || (GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE))
        {
            // Check if HDMI 2.0 ON
            if(ScalerGetBit(P2_00_HDMI_CTRL_00, _BIT0) == _BIT0)
            {
                // Set Manual Format to HDMI
                ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Toggle HW Format Detect Flag Reset
                ScalerSetBit(P2_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
                ScalerSetBit(P2_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

                SET_TMDS_RX0_HDMI_2_0_FORMAT_RESET_WAITING();

                ScalerTimerReactiveTimerEvent(130, _SCALER_TIMER_EVENT_RX0_HDMI2_FORMAT_RESET_WAIT);
            }

            // Detect Scrambling Control Symbol
            if(ScalerGetBit(P2_01_HDMI_CTRL_01, _BIT3) == _BIT3)
            {
                // Enable Scrambling Status in SCDC
                ScalerSetDataPortBit(P2_39_HDMI_CTRL_39, _P2_3A_PT_21_PORT_PAGE02_HDMI_SCDC_21, ~_BIT0, _BIT0);
            }
        }
#endif

        return _SOURCE_HDMI;
    }
    else
    {
        ScalerSetBit(P2_AF_TMDS_WDC, ~_BIT0, _BIT0);

        if((GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE) || (GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE))
        {
#if(_HDMI_2_0_SUPPORT == _ON)
            if(ScalerGetBit(P2_00_HDMI_CTRL_00, _BIT0) == _BIT0)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX0_HDMI2_FORMAT_RESET_WAIT);
            }
#endif
            // Set Format Detect HW Auto Mode
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);
        }

        return _SOURCE_DVI;
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerTMDSHdcpEnabled(BYTE ucInputPort)
{
    BYTE pucHDCPFrameCount[2];
    memset(pucHDCPFrameCount, 0, sizeof(pucHDCPFrameCount));

    ucInputPort = ucInputPort;

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    if((ScalerGetBit(P2_C0_HDCP_CR, _BIT0) == _BIT0) && (ScalerGetBit(P2D_26_HDCP_I2C_CTRL_0, _BIT7) == 0x00))
#endif
    {
        ScalerGetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C0_PORT_PAGE2_HDCP_FCR, 1, &pucHDCPFrameCount[0], _NON_AUTOINC);

        // Wait 2Vsync to make sure frame counter changing, and timeout 45ms (margin + 1/24 frame+rate)
        ScalerSetBit(P2_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
        ScalerTimerPollingFlagProc(45, P2_A4_TMDS_CTRL, _BIT3, _TRUE);
        ScalerSetBit(P2_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
        ScalerTimerPollingFlagProc(45, P2_A4_TMDS_CTRL, _BIT3, _TRUE);


        ScalerGetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C0_PORT_PAGE2_HDCP_FCR, 1, &pucHDCPFrameCount[1], _NON_AUTOINC);

        if(pucHDCPFrameCount[0] != pucHDCPFrameCount[1])
        {
            return _TRUE;
        }

        return _FALSE;
    }
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    else if((ScalerGetBit(P2_C0_HDCP_CR, _BIT0) == 0x00) && (ScalerGetBit(P2D_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7))
    {
        if(ScalerGetByte(P2D_2C_HDCP_I2C_CTRL_6) == 0x10)
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
        return _FALSE;
    }
#endif
}

//--------------------------------------------------
// Description  : On Line Check TMDS stability
// Input Value  : ucSourceType --> Source Type
// Output Value : True --> TMDS Stable
//                False --> TMDS Unstable
//--------------------------------------------------
bit ScalerTMDSStableDetect(BYTE ucInputPort, BYTE ucSourceType)
{
    ucInputPort = ucInputPort;

    // CLR SCL/SDA Toggle Flag
    CLR_TMDS_RX1_DDC_DETECTED();
    CLR_TMDS_RX2_DDC_DETECTED();

    switch(ucInputPort)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
            {
                return _FALSE;
            }

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)

            if(GET_TMDS_RX1_TOGGLE_Z0() == _TRUE)
            {
                SET_TMDS_RX1_TOGGLE_Z0_EVENT();

                return _FALSE;
            }

#endif
            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
            {
                return _FALSE;
            }

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)

            if(GET_TMDS_RX2_TOGGLE_Z0() == _TRUE)
            {
                SET_TMDS_RX2_TOGGLE_Z0_EVENT();

                return _FALSE;
            }

#endif
            break;
#endif

        default:

            break;
    }

    if(ScalerTMDSCheckCDRStable(ucInputPort, g_usTMDSClkCount) == _FALSE)
    {
        DebugMessageRx1("CDR Unstable!!", ucSourceType);
        return _FALSE;
    }

    // Check TMDS Clock Output Disable
    if(ScalerGetBit(P2_A6_TMDS_OUTCTL, _BIT3) == 0x00)
    {
        DebugMessageRx1("TMDS Clock Output has been disable", ucSourceType);
        return _FALSE;
    }

#if(_HDMI_2_0_SUPPORT == _ON)

    if(((GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE) || (GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)) && (ScalerGetBit(P2_00_HDMI_CTRL_00, _BIT0) == _BIT0))
    {
        if(ucSourceType == _SOURCE_HDMI)
        {
            if(GET_TMDS_RX0_HDMI_2_0_FORMAT_RESET_WAITING() == _FALSE)
            {
                if(ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR, _BIT3) != _BIT3)
                {
                    return _FALSE;
                }
                else
                {
                    if(ScalerGetBit(P2_CB_HDMI_SR, _BIT0) == 0x00)
                    {
                        DebugMessageRx1("TMDS Format Changed", ucSourceType);

                        return _FALSE;
                    }
                    else
                    {
                        // Toggle HW Format Detect Flag Reset
                        ScalerSetBit(P2_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
                        ScalerSetBit(P2_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

                        SET_TMDS_RX0_HDMI_2_0_FORMAT_RESET_WAITING();

                        ScalerTimerReactiveTimerEvent(130, _SCALER_TIMER_EVENT_RX0_HDMI2_FORMAT_RESET_WAIT);
                    }
                }
            }
        }
        else
        {
            if(ScalerGetBit(P2_CB_HDMI_SR, _BIT0) == _BIT0)
            {
                DebugMessageRx1("TMDS Format Changed", ucSourceType);
                return _FALSE;
            }
        }
    }
    else

#endif
    {
        // Check TMDS Format Changed

        if(ucSourceType == _SOURCE_HDMI)
        {
            if(ScalerGetBit(P2_CB_HDMI_SR, _BIT0) == 0x00)
            {
                DebugMessageRx1("TMDS Format Changed", ucSourceType);
                return _FALSE;
            }
        }
        else
        {
            if(ScalerGetBit(P2_CB_HDMI_SR, _BIT0) == _BIT0)
            {
                DebugMessageRx1("TMDS Format Changed", ucSourceType);
                return _FALSE;
            }
        }
    }

    switch(ucInputPort)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_TMDS_Z0_ASSERTED() == _TRUE)
            {
                if((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT6) == _BIT6) && (!((((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT7)) == _BIT7) || ((ScalerGetBit(P2_AE_TMDS_RPS, _BIT1)) == _BIT1)) && ((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT5)) == _BIT5))))
                {
                    SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

                    CLR_TMDS_Z0_ASSERTED();

                    DebugMessageRx1("7. HDCP Abnormal !!!!!", 0);

                    return _FALSE;
                }
                else if(((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT7) == (_BIT7)) || (ScalerGetBit(P2_AE_TMDS_RPS, _BIT1) == (_BIT1))) && (ScalerGetBit(P2_A9_TMDS_ABC0, _BIT5) == (_BIT5)))
                {
                    CLR_TMDS_Z0_ASSERTED();

                    DebugMessageRx1("7. HDCP Normal", 0);
                }
            }

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_TMDS_Z0_ASSERTED() == _TRUE)
            {
                if((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT6) == _BIT6) && (!((((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT7)) == _BIT7) || ((ScalerGetBit(P2_AE_TMDS_RPS, _BIT1)) == _BIT1)) && ((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT5)) == _BIT5))))
                {
                    SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

                    CLR_TMDS_Z0_ASSERTED();

                    DebugMessageRx1("7. HDCP Abnormal !!!!!", 0);

                    // MHL mode of MHL PORT will not return FALSE
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
                    {
                        return _FALSE;
                    }
#else
                    return _FALSE;
#endif
                }
                else if(((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT7) == (_BIT7)) || (ScalerGetBit(P2_AE_TMDS_RPS, _BIT1) == (_BIT1))) && (ScalerGetBit(P2_A9_TMDS_ABC0, _BIT5) == (_BIT5)))
                {
                    CLR_TMDS_Z0_ASSERTED();

                    DebugMessageRx1("7. HDCP Normal", 0);
                }
            }

            break;
#endif

        default:

            break;
    }

    if(ucSourceType == _SOURCE_DVI)
    {
        if(GET_TMDS_RGBHV_DETECTING() == _FALSE)
        {
            // TMDS Video Detected
#if(_DVI_DE_ONLY_SUPPORT == _OFF)
            if(ScalerTMDSVideoDetect(_NOT_WAIT) != _TMDS_VIDEO_DATA_RGBHV)
#else
            if(ScalerTMDSVideoDetect(_NOT_WAIT) == _TMDS_VIDEO_DATA_NONE)
#endif
            {
                DebugMessageRx1("TMDS Video format changed", ucSourceType);

                return _FALSE;
            }
        }
    }

#if(_HDMI_SUPPORT == _ON)

    if(ucSourceType == _SOURCE_HDMI)
    {
        if(GET_HDMI_PACKET_DETECTING() == _FALSE)
        {
            // HDMI Packet Detected
            ScalerTMDSHdmiPacketDetect(_NOT_WAIT);

            if(GET_HDMI_RX0_AVI_INFO_FRAME_RECEIVED() == _TRUE)
            {
                if(ScalerSyncTMDSRx0HdmiColorInfoChanged() == _TRUE)
                {
                    DebugMessageRx1("Color Info Changed", ucSourceType);
                    return _FALSE;
                }

                if(ScalerTMDSHdmiAviPixelRepInfoChanged() == _TRUE)
                {
                    DebugMessageRx1("Pixel Repetition Info Changed", ucSourceType);
                    return _FALSE;
                }
            }
            else
            {
                if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    DebugMessageRx1("HDMI Info Frame Not Received and not RGB", ucSourceType);
                    return _FALSE;
                }

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
                if(GET_COLOR_RGB_QUANTIZATION_RANGE() != _RGB_QUANTIZATION_RESERVED)
                {
                    DebugMessageRx1("No Quantization Range Specified", ucSourceType);
                    return _FALSE;
                }
#endif

                if(GET_TMDS_RX0_AVI_PIXEL_REPETITION() != _AVI_PIXEL_REPETITION_0)
                {
                    DebugMessageRx1("Pixel Repetition Not Received and not Pixel repetition 0", ucSourceType);
                    return _FALSE;
                }
            }

            if((ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_41_PORT_PAGE2_HDMI_VWDSR, _BIT0) == _BIT0) && (ScalerGetBit(P2_CC_HDMI_GPVS, _BIT0) == _BIT0))
            {
                DebugMessageRx1("HDMI AVI info frame has changed", ucSourceType);
                return _FALSE;
            }

            if(GET_HDMI_GCP_RECEIVED() == _TRUE)
            {
                if((GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422) && (ScalerTMDSHdmiGetColorDepth() != GET_COLOR_DEPTH()))
                {
                    DebugMessageRx1("Color Depth Has Changed", GET_COLOR_DEPTH());
                    return _FALSE;
                }
            }
            else
            {
                if((GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422) && (GET_COLOR_DEPTH() != _COLOR_DEPTH_8_BITS))
                {
                    DebugMessageRx1("HDMI GCP PACKET Not Received and not 8 bit", ucSourceType);
                    return _FALSE;
                }
            }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
            if(GET_TMDS_RX0_SPD_INFO_FRAME_RECEIVED() == _TRUE)
            {
                if((bit)GET_HDMIRX1_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) != GET_HDMI_FREESYNC_ENABLED())
                {
                    DebugMessageRx1("HDMI Freesync Status Change", GET_HDMI_FREESYNC_ENABLED());
                    return _FALSE;
                }
            }
            else
            {
                if(GET_HDMI_FREESYNC_ENABLED() == _TRUE)
                {
                    DebugMessageRx1("HDMI Freesync Status Change", GET_HDMI_FREESYNC_ENABLED());
                    return _FALSE;
                }
            }
#endif
        }
    }

#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : TMDS Hot Plug Event
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerTMDSHotPlugEvent(BYTE ucPortSelect)
{
    switch(ucPortSelect)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            ScalerTMDSBeforeHotPlugEventProc(_D1_INPUT_PORT);

            // ACER mode and DVI port will only toggle Z0 130ms
#if((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
            if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
            {
                if(GET_D1_CABLE_STATUS() == _TRUE)
                {
                    ScalerTimerDelayXms(_TMDS_ACER_HPD_TIME);
                }
            }
            else
#endif
            {
                // HPD Low
                ScalerTMDSHotPlugLowProc(_D1_INPUT_PORT);

                // wait
                if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
                {
                    ScalerTMDSHotPlugHighProc(_D1_INPUT_PORT, GET_HDMI_HOTPLUG_TIME());
                }
                else if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
                {
                    ScalerTMDSHotPlugHighProc(_D1_INPUT_PORT, _TMDS_HDCP_2_2_HPD_TIME);
                }
                else if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
                {
                    ScalerTMDSHotPlugHighProc(_D1_INPUT_PORT, _TMDS_ACER_HPD_TIME);
                }
                else if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_EDID_SWITCH)
                {
                    ScalerTMDSHotPlugHighProc(_D1_INPUT_PORT, _TMDS_EDID_SWITCH_HPD_TIME);
                }
                else
                {
                    ScalerTMDSHotPlugHighProc(_D1_INPUT_PORT, GET_HDMI_HOTPLUG_TIME());
                }
            }

            // Restore Slave Address and Z0 Status
            ScalerTMDSAfterHotPlugEventProc(_D1_INPUT_PORT);

            DebugMessageRx1("Rx1 HPD Toggle!!", 0);

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
            if(GET_TMDS_RX1_TOGGLE_Z0_EVENT() == _TRUE)
            {
                CLR_TMDS_RX1_TOGGLE_Z0();
                CLR_TMDS_RX1_TOGGLE_Z0_EVENT();
            }
#endif

            CLR_TMDS_RX1_HPD_TRIGGER_EVENT();

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            ScalerTMDSBeforeHotPlugEventProc(_D2_INPUT_PORT);

            // ACER mode and DVI port will only toggle Z0 130ms
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
            if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
            {
                if(GET_D2_CABLE_STATUS() == _TRUE)
                {
                    ScalerTimerDelayXms(_TMDS_ACER_HPD_TIME);
                }
            }
            else
#endif
            {
                // HPD Low
                ScalerTMDSHotPlugLowProc(_D2_INPUT_PORT);

                // wait
                if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
                {
                    ScalerTMDSHotPlugHighProc(_D2_INPUT_PORT, GET_HDMI_HOTPLUG_TIME());
                }
                else if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
                {
                    ScalerTMDSHotPlugHighProc(_D2_INPUT_PORT, _TMDS_HDCP_2_2_HPD_TIME);
                }
                else if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
                {
                    ScalerTMDSHotPlugHighProc(_D2_INPUT_PORT, _TMDS_ACER_HPD_TIME);
                }
                else if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() == _TMDS_HPD_EDID_SWITCH)
                {
                    ScalerTMDSHotPlugHighProc(_D2_INPUT_PORT, _TMDS_EDID_SWITCH_HPD_TIME);
                }
                else
                {
                    ScalerTMDSHotPlugHighProc(_D2_INPUT_PORT, GET_HDMI_HOTPLUG_TIME());
                }
            }

            // Restore Slave Address and Z0 Status
            ScalerTMDSAfterHotPlugEventProc(_D2_INPUT_PORT);

            DebugMessageRx2("Rx2 HPD Toggle!!", 0);

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
            if(GET_TMDS_RX2_TOGGLE_Z0_EVENT() == _TRUE)
            {
                CLR_TMDS_RX2_TOGGLE_Z0();
                CLR_TMDS_RX2_TOGGLE_Z0_EVENT();
            }
#endif

            CLR_TMDS_RX2_HPD_TRIGGER_EVENT();

            break;
#endif


        default:

            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Switch Slave Address
// Input Value  : ucPortSelect
// Output Value :
//--------------------------------------------------
void ScalerTMDSSwitchSlaveAddr(BYTE ucPortSelect)
{
    ucPortSelect = ucPortSelect;

    // Switch Slave Address to unknow State (Prohibit any handshake on DDC Channel During HPD Low)
    ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, 0x7F);
}

//--------------------------------------------------
// Description  : TMDS Before Hot Plug Event Process
// Input Value  : ucPortSelect
// Output Value : Hot Plug time
//--------------------------------------------------
void ScalerTMDSBeforeHotPlugEventProc(BYTE ucPortSelect)
{
    switch(ucPortSelect)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_D1_CABLE_STATUS() == _TRUE)
            {
                // Save Z0 Status
                g_ucTMDSRx1Z0Status = ScalerGetBit(P1D_17_IMPEDANCE_00, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Backup Slave Address
                ScalerGetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, 1, &g_ucTMDSSlaveAddr, _NON_AUTOINC);

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT))
                // Reset HDCP 2.2
                ScalerHdcp2ResetTMDSProc(_D1_INPUT_PORT);
#endif

#if(_HDMI_2_0_SUPPORT == _ON)
                // Disable HDMI 2.0 SCDC Function
                ScalerSetBit(P2_19_HDMI_CTRL_19, ~_BIT7, 0x00);
#endif

                // Disable Z0
                ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }
            else if(GET_D1_CABLE_STATUS() == _FALSE)
            {
                // DDC reset
#if(_D1_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT1;
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE65_DDC2_DDC_CONTROL_1 |= _BIT1;
#endif
            }

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_D2_CABLE_STATUS() == _TRUE)
            {
                // Save Z0 Status
                g_ucTMDSRx2Z0Status = ScalerGetBit(P1D_19_IMPEDANCE_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Backup Slave Address
                ScalerGetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, 1, &g_ucTMDSSlaveAddr, _NON_AUTOINC);

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON) && (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT))
                // Reset HDCP 2.2
                ScalerHdcp2ResetTMDSProc(_D2_INPUT_PORT);
#endif

#if(_HDMI_2_0_SUPPORT == _ON)
                // Disable HDMI 2.0 SCDC Function
                ScalerSetBit(P2_19_HDMI_CTRL_19, ~_BIT7, 0x00);
#endif

                // Disable Z0
                ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }
            else if(GET_D2_CABLE_STATUS() == _FALSE)
            {
                // DDC reset
#if(_D2_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT1;
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE65_DDC2_DDC_CONTROL_1 |= _BIT1;
#endif
            }

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : TMDS After Hot Plug Event Process
// Input Value  : ucPortSelect
// Output Value :
//--------------------------------------------------
void ScalerTMDSAfterHotPlugEventProc(BYTE ucPortSelect)
{
    switch(ucPortSelect)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_D1_CABLE_STATUS() == _TRUE)
            {
                // Restore Slave Address
                ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, g_ucTMDSSlaveAddr);

#if(_HDMI_2_0_SUPPORT == _ON)
                // Enable HDMI 2.0 SCDC Function
                ScalerSetBit(P2_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
#endif

                // Restore Z0 Status
                ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), g_ucTMDSRx1Z0Status);
            }
            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_D2_CABLE_STATUS() == _TRUE)
            {
                // Restore Slave Address
                ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, g_ucTMDSSlaveAddr);

#if(_HDMI_2_0_SUPPORT == _ON)
                // Enable HDMI 2.0 SCDC Function
                ScalerSetBit(P2_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
#endif

                // Restore Z0 Status
                ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), g_ucTMDSRx2Z0Status);
            }
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Backup HDCP Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSBackupHdcpType(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D1_INPUT_PORT:
            if((ScalerGetBit(P2_C0_HDCP_CR, _BIT0) == _BIT0) && (ScalerGetBit(P2_A9_TMDS_ABC0, _BIT6) == _BIT6))
            {
                SET_TMDS_RX1_BACKUP_HDCP_TYPE(_HDCP_14);
            }
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)

            else if((ScalerGetBit(P2D_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7) && (ScalerGetByte(P2D_2C_HDCP_I2C_CTRL_6) == 0x10))
            {
                SET_TMDS_RX1_BACKUP_HDCP_TYPE(_HDCP_22);
            }
#endif
            else
            {
                SET_TMDS_RX1_BACKUP_HDCP_TYPE(_HDCP_NONE);
            }
            break;


        case _D2_INPUT_PORT:
            if((ScalerGetBit(P2_C0_HDCP_CR, _BIT0) == _BIT0) && (ScalerGetBit(P2_A9_TMDS_ABC0, _BIT6) == _BIT6))
            {
                SET_TMDS_RX2_BACKUP_HDCP_TYPE(_HDCP_14);
            }
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            else if((ScalerGetBit(P2D_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7) && (ScalerGetByte(P2D_2C_HDCP_I2C_CTRL_6) == 0x10))
            {
                SET_TMDS_RX2_BACKUP_HDCP_TYPE(_HDCP_22);
            }
#endif
            else
            {
                SET_TMDS_RX2_BACKUP_HDCP_TYPE(_HDCP_NONE);
            }
            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : ScalerTMDSHdcp1p4AksvClear
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerTMDSHdcp1p4AksvClear(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_TMDS_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            if(CHECK_TMDS_DPHY_SWITCH(_D0_INPUT_PORT) == _TRUE)
            {
                ScalerSetBit(P2_AE_TMDS_RPS, ~(_BIT1), 0x00);
            }

            break;
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            if(CHECK_TMDS_DPHY_SWITCH(_D1_INPUT_PORT) == _TRUE)
            {
                // SET KEY ready bit 0
                ScalerSetBit(P2_AE_TMDS_RPS, ~(_BIT1), 0x00);
            }
            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            if(CHECK_TMDS_DPHY_SWITCH(_D2_INPUT_PORT) == _TRUE)
            {
                // SET KEY ready bit 0
                ScalerSetBit(P2_AE_TMDS_RPS, ~(_BIT1), 0x00);
            }
            break;
#endif


        default:

            break;
    }
}

#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
