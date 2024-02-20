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
// ID Code      : RL6369_Series_TMDS.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6369_SERIES_TMDS__

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
BYTE g_ucTMDSClkIRQ;

#if(_D0_TMDS_SUPPORT == _ON)
BYTE g_ucTMDSRx0Z0Status;
#endif
#if(_D1_TMDS_SUPPORT == _ON)
BYTE g_ucTMDSRx1Z0Status;
#endif
#if(_D2_TMDS_SUPPORT == _ON)
BYTE g_ucTMDSRx2Z0Status;
#endif
BYTE g_ucTMDSSlaveAddr;


#if(_MHL_SUPPORT == _ON)
BYTE g_ucTMDSClkMode = _TMDS_24BIT_PHY_SETTING;
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
BYTE g_pucRxCaps[3];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTMDSInitial(BYTE ucInputPort);
void ScalerTMDSInterruptInitial(BYTE ucInputPort);
void ScalerTMDSSetDFEInitial_EXINT0(void);
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
#endif

void ScalerTMDSPowerSavingProc(BYTE ucPortSelect);
void ScalerTMDSPowerOffProc(void);
void ScalerTMDSFirstActiveProc(BYTE ucInputPort, BYTE ucSourceType);
bit ScalerTMDSPSPreDetect(BYTE ucInputPort);
bit ScalerTMDSNormalPreDetect(BYTE ucInputPort);
BYTE ScalerTMDSScanInputPort(BYTE ucInputPort, BYTE ucInputType);
BYTE ScalerTMDSFormatDetect(void);
bit ScalerTMDSHdcpEnabled(BYTE ucInputPort);
bit ScalerTMDSCheckDataDFE(BYTE ucInputPort);

bit ScalerTMDSStableDetect(BYTE ucInputPort, BYTE ucSourceType);
void ScalerTMDSHotPlugEvent(BYTE ucPortSelect);
void ScalerTMDSSwitchSlaveAddr(BYTE ucPortSelect);
void ScalerTMDSBeforeHotPlugEventProc(BYTE ucPortSelect);
void ScalerTMDSAfterHotPlugEventProc(BYTE ucPortSelect);
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

    // Set TMDS Hsync/Vsync Polarity as Input Raw Polarity
    ScalerSetBit(P2_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);

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

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_A4_PORT_PAGE2_HDMI_PTRSV_2, _SPD_INFO_TYPE);
#endif

    // Packet Variation Detect Disable
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_45_PORT_PAGE2_HDMI_PVGCR0, 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_46_PORT_PAGE2_HDMI_PVGCR1, 0x00);
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_47_PORT_PAGE2_HDMI_PVGCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_A9_PORT_PAGE2_HDMI_PVSR_4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    ScalerSetDataPortByte(P2_C9_HDMI_AP, _P2_CA_PT_AA_PORT_PAGE2_HDMI_PVGCR3, 0x00);
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_AB_PORT_PAGE2_HDMI_PVGCR4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
#endif

    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), 0x00);
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), _BIT1);
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), _BIT2);
#endif
            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), 0x00);
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), _BIT1);
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), _BIT2);
#endif
            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), 0x00);
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), _BIT1);
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), _BIT2);
#endif
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

    // Disable HDMI 2.0 Function
    ScalerSetBit(P2_00_HDMI_CTRL_00, ~_BIT0, 0x00);

    // MAC Select to HDMI
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT0, _BIT0);

    // Disable HDMI MAC Global Power Down
    ScalerSetBit(P2_AD_TMDS_CPS, ~_BIT1, 0x00);

    // Enable MAC Input
    ScalerSetBit(P2_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set MAC Signal Swap
    ScalerSetBit(P2_A7_TMDS_PWDCTL, ~(_BIT6 | _BIT5), ((ucInputPort == _D0_INPUT_PORT) ? ((_D0_TMDS_BR_SWAP << 6) | (_D0_TMDS_PN_SWAP << 5)) : ((ucInputPort == _D1_INPUT_PORT) ? ((_D1_TMDS_BR_SWAP << 6) | (_D1_TMDS_PN_SWAP << 5)) : ((_D2_TMDS_BR_SWAP << 6) | (_D2_TMDS_PN_SWAP << 5)))));

    // Auto switch to DVI when no signal
    ScalerSetBit(P2_AD_TMDS_CPS, ~_BIT2, _BIT2);

    // Detect TMDS Format by Data Island Packet Preamble & Guard Band
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), _BIT1);

    // Enable TMDS MAC Error Correction
    ScalerSetBit(P2_B7_TMDS_UDC2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

#if(_MHL_SUPPORT == _ON)
    if(((ucInputPort == _D0_INPUT_PORT) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ucInputPort == _D1_INPUT_PORT) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ucInputPort == _D2_INPUT_PORT) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
    {
        // Enable MHL Mac and Set MHL MAC Signal Swap
        ScalerSetBit(P26_A0_MHL_CTRL_00, ~(_BIT5 | _BIT0), (ucInputPort == _D0_INPUT_PORT) ? ((_D0_TMDS_PN_SWAP << 5) | _BIT0) : ((ucInputPort == _D1_INPUT_PORT) ? ((_D1_TMDS_PN_SWAP << 5) | _BIT0) : ((_D2_TMDS_PN_SWAP << 5) | _BIT0)));

        // Enable New Algorithm for Packed Pixel Mode
        ScalerSetBit(P26_A1_MHL_CTRL_01, ~_BIT7, _BIT7);

        // Guard Band reference enable for data remapping
        ScalerSetBit(P26_B2_MHL_CTRL_12, ~_BIT7, _BIT7);

        // Set 24Bit Mode Threshold
        ScalerSetByte(P26_AA_MHL_CTRL_0A, 0x00);
        ScalerSetByte(P26_AB_MHL_CTRL_0B, 0x09);

        // Set PP Mode Threshold
        ScalerSetByte(P26_AC_MHL_CTRL_0C, 0x00);
        ScalerSetByte(P26_AD_MHL_CTRL_0D, 0x09);

        // Set Detection Period
        ScalerSetByte(P26_A8_MHL_CTRL_08, 0x69);
        ScalerSetByte(P26_A9_MHL_CTRL_09, 0x78);

        // Set Detection by Video Leading and Detection Period by Xtal
        ScalerSetBit(P26_A7_MHL_CTRL_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT0), _BIT2);
    }
    else
#endif
    {
        // Disable MHL Mac and Revert CDR Data Polarity
        ScalerSetBit(P26_A0_MHL_CTRL_00, ~(_BIT5 | _BIT0), 0x00);

        // Guard Band reference disable for data remapping
        ScalerSetBit(P26_B2_MHL_CTRL_12, ~_BIT7, 0x00);

        // Set HDMI/DVI switch to Auto Mode
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
    }
}

//--------------------------------------------------
// Description  : Initialize TMDS Interrupt Required Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSInterruptInitial(BYTE ucInputPort)
{
    // Enable INT Clock Check
    g_ucTMDSClkIRQ = _ENABLE;

    ucInputPort = ucInputPort;

    if(ScalerGetBit(P2_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
    {
        CLR_TMDS_PHY_SET();
    }

    // Enable Rx_En for Clk pair Z0
    ScalerSetBit(PB_C0_CMU_03, ~_BIT7, _BIT7);

    // Choose Measure Clk to TMDS Clk
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

    // Set Freq. Reference Counter = 2000
    ScalerSetBit(P2_F6_HDMI_FREQDET_BOUND_H, ~(_BIT1 | _BIT0), _BIT0);

    // Set Online Measure Input Clock Divider = /2 (No Matter if Input Clock >300Mhz or <=300Mhz)
    ScalerSetBit(P2_E7_HDMI_FREQDET_OFFSET, ~_BIT6, _BIT6);

    // Settings for IRQ set PHY
    // Consider using table to fill all required initial settings
    // Set pre-set threshold (225MHz * 0.01 / 26.8KHz = 0x54)

#if(_MHL_SUPPORT == _ON)
    if(((ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == 0x00) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT6) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT7) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
    {
        // Set TMDS Offset = 1/32
        ScalerSetBit(P2_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // Set Upper Bound
        ScalerSetByte(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
        ScalerSetByte(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
    }
    else
#endif
    {
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
    }

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
    // [7] Positive Symbol-Rate Clock
    // [6] Enable Timer Control DFE Loop
    // [5:4] No Reduce Gain
    // [3] Disable Running Length Detection
    // [2] bypass Blank out Case-3 Symbol
    ScalerSetBit_EXINT(P1D_A0_L0_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6));
    ScalerSetBit_EXINT(P1D_B0_L1_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6));
    ScalerSetBit_EXINT(P1D_C0_L2_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6));

    if(GET_INPUT_PIXEL_CLK() < 1000)
    {
        // [7:6] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop
        ScalerSetBit_EXINT(P1D_E0_MODE_TIMER, ~(_BIT7 | _BIT6), _BIT7);
    }
    else
    {
        // [7:6] adapt_mode[1:0] = 2'b11 --> Amplitude-based Adaptation without Independent LE Loop
        ScalerSetBit_EXINT(P1D_E0_MODE_TIMER, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }

    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetBit_EXINT(P1D_E0_MODE_TIMER, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1));

    // Set DFE Delay Time
    // Turn On LE/Tap1~6 Simultaneously
    ScalerSetByte_EXINT(P1D_E1_TIMER, 0x01);

    // Tap0,Tap1 Loop Gain 1/512
    ScalerSetBit_EXINT(P1D_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap2,Tap3 Loop Gain 1/512
    ScalerSetBit_EXINT(P1D_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4,Servo Loop Gain 1/512
    ScalerSetBit_EXINT(P1D_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // LE Gain1 Loop Gain 1/256, LE Gain2 Loop Gain 0, LE Pre-Courser Gain 0
    ScalerSetBit_EXINT(P1D_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit_EXINT(P1D_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap0 Max is 21
    ScalerSetByte_EXINT(P1D_E6_LIMIT_1, 0x35);

    if(GET_INPUT_PIXEL_CLK() < 1000)
    {
        // Tap1 Min is -31
        ScalerSetBit_EXINT(P1D_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        // Tap1 Min is LE(-24) + Tap1(-31) = -55
        ScalerSetBit_EXINT(P1D_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
    }

    // Tap2 Max is 6, Min is -6
    ScalerSetBit_EXINT(P1D_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(P1D_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P1D_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 1, Min is -6
    ScalerSetBit_EXINT(P1D_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P1D_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));

    // Tap4 Max is 1, Min is -6
    ScalerSetBit_EXINT(P1D_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_EB_LIMIT_6, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit_EXINT(P1D_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap0 Threshold
    ScalerSetBit_EXINT(P1D_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // Set Vth Max = 8, Min = 0
    ScalerSetByte_EXINT(P1D_F9_LIMIT_10, 0x80);

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetByte_EXINT(P1D_EC_LOOP_DIV_1, 0xA3);

    // Tap Divider = 10
    ScalerSetByte_EXINT(P1D_ED_LOOP_DIV_2, 0xCA);

    // [7] servo_trans = 1'b0 --> Servo is Effective on Each Bit
    // [6] tap0_trans = 1'b0 --> Tap0 is Effective on Each Bit
    // [5] servo_notrans = 1'b1 --> Servo is Effective when Non-Tran
    // [4] tap0_notrans = 1'b1 --> Tap0 is Effective when Non-Tran
    ScalerSetBit_EXINT(P1D_F8_GRAY_DEC_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [1] De_inverse = 1'b0 --> Adapation Only for Blanking Area (Transition Maximum)
    // [0] De_brank_en = 1'b0 --> Disable Blank Function of gdi_de
    ScalerSetBit_EXINT(P1D_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Code Initialize //
    /////////////////////////

    // Initial DFE Code
    if(GET_INPUT_PIXEL_CLK() < 375)
    {
        // LE Max = 24, Initial = 4
        ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x84);
    }
    else if(GET_INPUT_PIXEL_CLK() < 700)
    {
        // LE Max = 24, Initial = 6
        ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x86);
        ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x86);
        ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x86);
    }
    else if(GET_INPUT_PIXEL_CLK() < 1000)
    {
        // LE Max = 24, Initial = 10
        ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x8A);
        ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x8A);
        ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x8A);
    }
    else
    {
        // LE Max = 24, Initial = 12
        ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x8C);
        ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x8C);
        ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x8C);
    }

    // Servo Initial = 16
    ScalerSetByte_EXINT(P1D_A3_L0_INIT_1, 0x90);
    ScalerSetByte_EXINT(P1D_B3_L1_INIT_1, 0x90);
    ScalerSetByte_EXINT(P1D_C3_L2_INIT_1, 0x90);

    // Tap0 Initial Value = 15
    ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P1D_B4_L1_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P1D_C4_L2_INIT_2, 0x0F);

    if(GET_INPUT_PIXEL_CLK() < 1000)
    {
        // Tap1 Initial Value = 0 for Mode2 DFE
        ScalerSetByte_EXINT(P1D_A5_L0_INIT_3, 0x00);
        ScalerSetByte_EXINT(P1D_B5_L1_INIT_3, 0x00);
        ScalerSetByte_EXINT(P1D_C5_L2_INIT_3, 0x00);
    }
    else
    {
        // Tap1 Initial Value = 15 for Mode3 DFE
        ScalerSetByte_EXINT(P1D_A5_L0_INIT_3, 0x0F);
        ScalerSetByte_EXINT(P1D_B5_L1_INIT_3, 0x0F);
        ScalerSetByte_EXINT(P1D_C5_L2_INIT_3, 0x0F);
    }

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(P1D_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P1D_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P1D_C6_L2_INIT_4, 0x00);

    // Tap3 Initial Value = 0
    ScalerSetByte_EXINT(P1D_A7_L0_INIT_5, 0x00);
    ScalerSetByte_EXINT(P1D_B7_L1_INIT_5, 0x00);
    ScalerSetByte_EXINT(P1D_C7_L2_INIT_5, 0x00);

    // Tap4 Initial Value = 0
    ScalerSetByte_EXINT(P1D_A8_L0_INIT_6, 0x00);
    ScalerSetByte_EXINT(P1D_B8_L1_INIT_6, 0x00);
    ScalerSetByte_EXINT(P1D_C8_L2_INIT_6, 0x00);

    // Vth Initial Value = 6
    ScalerSetByte_EXINT(P1D_A9_L0_INIT_7, 0x06);
    ScalerSetByte_EXINT(P1D_B9_L1_INIT_7, 0x06);
    ScalerSetByte_EXINT(P1D_C9_L2_INIT_7, 0x06);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P1D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);
}

//-------------------------------------------------------------------
// Description  : TMDS Set PHY Function for HDMI+MHL2.0 (EXINT0 Only)
// Input Value  : None
// Output Value : None
//-------------------------------------------------------------------
void ScalerTMDSSetPhy_EXINT0(void) using 1
{
    ///////////////
    // RX CMU EN //
    ///////////////

    // [7] cmu_en = 0 --> Disable CMU PLL
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT7, 0x00);

    // [3:0] cdr_en = 4'b0000 --> Disable CDREN
    ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    if(ScalerGetBit_EXINT(PB_B6_BANDGAP_02, _BIT4) == _BIT4)  // MHL Mode
    {
        // [7:4] rx_en = 4'b1001 --> Enable RXEN for Lane0, 3
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));

        // [3] sel_iblpf = 1 --> Enable Local Bias LPF
        ScalerSetBit_EXINT(PB_B5_BANDGAP_01, ~_BIT3, _BIT3);

        // wait 45us
        DELAY_45US_EXINT();

        // [3:0] cdr_en = 4'b0001 --> Enable CDREX for Lane0
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // [7:4] rx_en = 4'b1111 --> Enable RXEN
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // [3] sel_iblpf = 1 --> Enable Local Bias LPF
        ScalerSetBit_EXINT(PB_B5_BANDGAP_01, ~_BIT3, _BIT3);

        // wait 45us
        DELAY_45US_EXINT();

        // [3:0] cdr_en = 4'b0001 ~ 4'b0011 ~ 4'b0111
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    }


    /////////////////
    // CMU Setting //
    /////////////////

    // [7] BYPASS_PI = 1'b1 --> Use Integer N_CODE
    ScalerSetBit_EXINT(PB_AE_SDM_04, ~_BIT7, _BIT7);

    // [0] PLL_WD_EN = 1'b0 --> Disable WD
    ScalerSetBit_EXINT(PB_AF_WD, ~_BIT0, 0x00);

    // [2] CMU_BYPASS_PI = 1'b1 --> Integer N PLL
    // [1] cmu_en_awdog = 1'b0 --> Disable CMU WatchDog
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~(_BIT2 | _BIT1), _BIT2);

    // [6:4] CMU_PI_I_SEL = 3'b101 --> CMU PI Current = 18.75uA
    ScalerSetBit_EXINT(PB_C3_CMU_06, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

    // [7] sel_in_div4 = 0 --> Input Ref. Clock/1
    // [3] CMU_SEL_D4 = 0 --> CMU Feedback Loop/1
    ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT7 | _BIT3), 0x00);

    // [0] N_CODE[8] = 0
    ScalerSetBit_EXINT(PB_AB_SDM_01, ~_BIT0, 0x00);

#if(_MHL_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(PB_B6_BANDGAP_02, _BIT4) == _BIT4)   // MHL 2.0
    {
        // [7] CMU_SEL_CP = 1 --> CMU LPF Cp = 2pF
        // [6:4] CMU_PI_I_SEL = 3'b101 --> CMU PI Current = 18.75uA
        ScalerSetBit_EXINT(PB_C3_CMU_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT4));

        // [6:4] CMU_SEL_R1 = 3'b011 --> CMU LPF Rs = 12KOhm
        ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

        // Check if Packed Pixel Mode
        if(GET_TMDS_RX0_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            // [3:0] CMU_SEL_PUMP_I = 4'b0110 --> CMU Charge Pump Current = 17.5uA
            ScalerSetBit_EXINT(PB_C3_CMU_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            if((GET_INPUT_PIXEL_CLK() >= 750) && (GET_INPUT_PIXEL_CLK() < 1500))
            {
                // [2:0] rate_sel = 3'b010 --> 750MHz ~ 1500MHz
                ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                // [2:0] SEL_DIV = 3'b010 --> 750MHz ~ 1500MHz
                ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                // [5:4] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), 0x00);

                // [7:0] N_CODE = 0x4C --> 76 + 4 = 80
                ScalerSetByte_EXINT(PB_AC_SDM_02, 0x4C);
            }
            else if((GET_INPUT_PIXEL_CLK() >= 1500) && (GET_INPUT_PIXEL_CLK() < 2000))
            {
                // [2:0] rate_sel = 3'b001 --> 1500MHz ~ 2250MHz
                ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                // [2:0] SEL_DIV = 3'b001 --> 1500MHz ~ 2250MHz
                ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                // [5:4] CMU_SELPREDIV = 2'b01 --> /2
                ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), _BIT4);

                // [7:0] N_CODE = 0x4C --> 76 + 4 = 80
                ScalerSetByte_EXINT(PB_AC_SDM_02, 0x4C);
            }
            else if((GET_INPUT_PIXEL_CLK() >= 2000) && (GET_INPUT_PIXEL_CLK() < 3000)) // 2~3G PP Mode, ACDR
            {
                // [2:0] rate_sel = 3'b001 --> 3000Mbps
                ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                // [2:0] SEL_DIV = 3'b001 --> 3000Mbps
                ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                // [7] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
                // [6:4] reg_sel_cdr_res = 3'b101 --> Analog CDR Rs = 6K
                // [3:0] reg_cdr_cp_in = 4'b0101 --> Analog CDR Icp = 16.5uA
                ScalerSetByte_EXINT(PB_D1_ANA_CDR_03, 0xD5);

                // Analog CDR Auto FLD Counter
                ScalerSetByte_EXINT(PB_D5_ANA_CDR_07, 0x45);
                ScalerSetByte_EXINT(PB_D6_ANA_CDR_08, 0x3B);
                ScalerSetByte_EXINT(PB_D7_ANA_CDR_09, 0xDF);

                // [5] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
                ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT5, _BIT5);

                // [3] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
                ScalerSetBit_EXINT(PB_CF_ANA_CDR_01, ~_BIT3, 0x00);

                // [6] xtal_en = 0 --> FLD Reference Input Clock
                // [1:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 700M/v
                ScalerSetBit_EXINT(PB_D0_ANA_CDR_02, ~(_BIT6 | _BIT1 | _BIT0), _BIT0);

                // [0] en_mhl_fld_ecbuss = 0 --> MHL Mode FLD Reference Common Mode Clock
                ScalerSetBit_EXINT(PB_BF_CMU_02, ~_BIT0, 0x00);

                // [7] reg_en_vco_lpf = 1'b0 --> Disable Analog CDR Multi Band VCO's LPF
                // [6] reg_sel_cdr_cp = 1'b0 --> Disable Analog CDR Loop's CP (1pF)
                // [5] reg_enhance_bias_boost = 1'b0 --> Disable Enhance LEQ Boost Bias
                // [4] reg_enhance_bias_gain = 1'b0 --> Disable Enhance LEQ Gain Bias
                ScalerSetBit_EXINT(PB_D2_ANA_CDR_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

                // [7] en_wide_temp = 1'b1
                ScalerSetBit_EXINT(PB_D3_ANA_CDR_05, ~_BIT7, _BIT7);
            }
            else if(GET_INPUT_PIXEL_CLK() >= 3000) // 3G PP Mode, ACDR
            {
                // [2:0] rate_sel = 3'b001 --> 6000Mbps
                ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                // [2:0] SEL_DIV = 3'b001 --> 6000Mbps
                ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                // [7] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
                // [6:4] reg_sel_cdr_res = 3'b101 --> Analog CDR Rs = 2K
                // [3:0] reg_cdr_cp_in = 4'b0101 --> Analog CDR Icp = 10.5uA
                ScalerSetByte_EXINT(PB_D1_ANA_CDR_03, 0xA3);

                // Analog CDR Auto FLD Counter
                ScalerSetByte_EXINT(PB_D5_ANA_CDR_07, 0x45);
                ScalerSetByte_EXINT(PB_D6_ANA_CDR_08, 0x77);
                ScalerSetByte_EXINT(PB_D7_ANA_CDR_09, 0xDF);

                // [5] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
                ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT5, _BIT5);

                // [3] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
                ScalerSetBit_EXINT(PB_CF_ANA_CDR_01, ~_BIT3, 0x00);

                // [6] xtal_en = 0 --> FLD Reference Input Clock
                // [1:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 700M/v
                ScalerSetBit_EXINT(PB_D0_ANA_CDR_02, ~(_BIT6 | _BIT1 | _BIT0), _BIT0);

                // [0] en_mhl_fld_ecbuss = 0 --> MHL Mode FLD Reference Common Mode Clock
                ScalerSetBit_EXINT(PB_BF_CMU_02, ~_BIT0, 0x00);

                // [7] reg_en_vco_lpf = 1'b0 --> Disable Analog CDR Multi Band VCO's LPF
                // [6] reg_sel_cdr_cp = 1'b0 --> Disable Analog CDR Loop's CP (1pF)
                // [5] reg_enhance_bias_boost = 1'b0 --> Disable Enhance LEQ Boost Bias
                // [4] reg_enhance_bias_gain = 1'b0 --> Disable Enhance LEQ Gain Bias
                ScalerSetBit_EXINT(PB_D2_ANA_CDR_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

                // [7] en_wide_temp = 1'b1
                ScalerSetBit_EXINT(PB_D3_ANA_CDR_05, ~_BIT7, _BIT7);
            }
        }
        else  // MHL 24bit Mode
        {
            // [3:0] CMU_SEL_PUMP_I = 4'b1010 --> CMU Charge Pump Current = 17.5uA
            ScalerSetBit_EXINT(PB_C3_CMU_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            if((GET_INPUT_PIXEL_CLK() >= 375) && (GET_INPUT_PIXEL_CLK() < 750))
            {
                // [2:0] rate_sel = 3'b010 --> 375MHz ~ 750MHz
                ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                // [2:0] SEL_DIV = 3'b010 --> 375MHz ~ 750MHz
                ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                // [5:4] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), 0x00);

                // [7:0] N_CODE = 0x74 --> 116 + 4 = 120
                ScalerSetByte_EXINT(PB_AC_SDM_02, 0x74);
            }
            else if((GET_INPUT_PIXEL_CLK() >= 750) && (GET_INPUT_PIXEL_CLK() < 1125))
            {
                // [2:0] rate_sel = 3'b010 --> 750MHz ~ 1500MHz
                ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                // [2:0] SEL_DIV = 3'b010 --> 750MHz ~ 1500MHz
                ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                // [5:4] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), 0x00);

                // [7:0] N_CODE = 0x38 --> 56 + 4 = 60
                ScalerSetByte_EXINT(PB_AC_SDM_02, 0x38);
            }
            else if((GET_INPUT_PIXEL_CLK() >= 1125) && (GET_INPUT_PIXEL_CLK() < 1500))
            {
                // [2:0] rate_sel = 3'b010 --> 750MHz ~ 1500MHz
                ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                // [2:0] SEL_DIV = 3'b010 --> 750MHz ~ 1500MHz
                ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                // [5:4] CMU_SELPREDIV = 2'b01 --> /2
                ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), _BIT4);

                // [7:0] N_CODE = 0x74 --> 116 + 4 = 120
                ScalerSetByte_EXINT(PB_AC_SDM_02, 0x74);
            }
            else if((GET_INPUT_PIXEL_CLK() >= 1500) && (GET_INPUT_PIXEL_CLK() < 2000))
            {
                // [2:0] rate_sel = 3'b001 --> 1500MHz ~ 2250MHz
                ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                // [2:0] SEL_DIV = 3'b001 --> 1500MHz ~ 2250MHz
                ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                // [5:4] CMU_SELPREDIV = 2'b10 --> /4
                ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), _BIT5);

                // [7:0] N_CODE = 0x74 --> 116 + 4 = 120
                ScalerSetByte_EXINT(PB_AC_SDM_02, 0x74);
            }
            else if(GET_INPUT_PIXEL_CLK() < 3000) // 2000~3000 2.25G 24bit Mode, ACDR
            {
                // [2:0] rate_sel = 3'b001 --> 300MGbps
                ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                // [2:0] SEL_DIV = 3'b001 --> 3000Mbps
                ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                // [7] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
                // [6:4] reg_sel_cdr_res = 3'b101 --> Analog CDR Rs = 6K
                // [3:0] reg_cdr_cp_in = 4'b0101 --> Analog CDR Icp = 16.5uA
                ScalerSetByte_EXINT(PB_D1_ANA_CDR_03, 0xD5);

                // Analog CDR Auto FLD Counter
                ScalerSetByte_EXINT(PB_D5_ANA_CDR_07, 0x45);
                ScalerSetByte_EXINT(PB_D6_ANA_CDR_08, 0x4F);
                ScalerSetByte_EXINT(PB_D7_ANA_CDR_09, 0xDF);

                // [5] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
                ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT5, _BIT5);

                // [3] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
                ScalerSetBit_EXINT(PB_CF_ANA_CDR_01, ~_BIT3, 0x00);

                // [6] xtal_en = 0 --> FLD Reference Input Clock
                // [1:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 700M/v
                ScalerSetBit_EXINT(PB_D0_ANA_CDR_02, ~(_BIT6 | _BIT1 | _BIT0), _BIT0);

                // [0] en_mhl_fld_ecbuss = 0 --> MHL Mode FLD Reference Common Mode Clock
                ScalerSetBit_EXINT(PB_BF_CMU_02, ~_BIT0, 0x00);

                // [7] reg_en_vco_lpf = 1'b0 --> Disable Analog CDR Multi Band VCO's LPF
                // [6] reg_sel_cdr_cp = 1'b0 --> Disable Analog CDR Loop's CP (1pF)
                // [5] reg_enhance_bias_boost = 1'b0 --> Disable Enhance LEQ Boost Bias
                // [4] reg_enhance_bias_gain = 1'b0 --> Disable Enhance LEQ Gain Bias
                ScalerSetBit_EXINT(PB_D2_ANA_CDR_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

                // [7] en_wide_temp = 1'b1
                ScalerSetBit_EXINT(PB_D3_ANA_CDR_05, ~_BIT7, _BIT7);
            }
            else
            {
                // [2:0] rate_sel = 3'b000 --> 6000Mbps
                ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                // [2:0] SEL_DIV = 3'b000 --> 6000Mbps
                ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                // [7] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
                // [6:4] reg_sel_cdr_res = 3'b101 --> Analog CDR Rs = 2K
                // [3:0] reg_cdr_cp_in = 4'b0101 --> Analog CDR Icp = 10.5uA
                ScalerSetByte_EXINT(PB_D1_ANA_CDR_03, 0xA3);

                // Analog CDR Auto FLD Counter
                ScalerSetByte_EXINT(PB_D5_ANA_CDR_07, 0x45);
                ScalerSetByte_EXINT(PB_D6_ANA_CDR_08, 0x9F);
                ScalerSetByte_EXINT(PB_D7_ANA_CDR_09, 0xDF);

                // [5] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
                ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT5, _BIT5);

                // [3] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
                ScalerSetBit_EXINT(PB_CF_ANA_CDR_01, ~_BIT3, 0x00);

                // [6] xtal_en = 0 --> FLD Reference Input Clock
                // [1:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 700M/v
                ScalerSetBit_EXINT(PB_D0_ANA_CDR_02, ~(_BIT6 | _BIT1 | _BIT0), _BIT0);

                // [0] en_mhl_fld_ecbuss = 0 --> MHL Mode FLD Reference Common Mode Clock
                ScalerSetBit_EXINT(PB_BF_CMU_02, ~_BIT0, 0x00);

                // [7] reg_en_vco_lpf = 1'b0 --> Disable Analog CDR Multi Band VCO's LPF
                // [6] reg_sel_cdr_cp = 1'b0 --> Disable Analog CDR Loop's CP (1pF)
                // [5] reg_enhance_bias_boost = 1'b0 --> Disable Enhance LEQ Boost Bias
                // [4] reg_enhance_bias_gain = 1'b0 --> Disable Enhance LEQ Gain Bias
                ScalerSetBit_EXINT(PB_D2_ANA_CDR_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

                // [7] en_wide_temp = 1'b1
                ScalerSetBit_EXINT(PB_D3_ANA_CDR_05, ~_BIT7, _BIT7);
            }
        }
    }
    else     // HDMI Mode
#endif
    {
        // [7] CMU_SEL_CP = 0 --> CMU LPF Cp = 1pF
        // [3:0] CMU_SEL_PUMP_I = 4'b1010 --> CMU Charge Pump Current = 27.5uA
        ScalerSetBit_EXINT(PB_C3_CMU_06, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

        // [6:4] CMU_SEL_R1 = 3'b011 --> CMU LPF Rs = 12KOhm
        ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

        if((GET_INPUT_PIXEL_CLK() >= 187) && (GET_INPUT_PIXEL_CLK() < 375))
        {
            // [2:0] rate_sel = 3'b100 --> 187.5MHz ~ 375MHz
            ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

            // [2:0] SEL_DIV = 3'b100 --> 187.5MHz ~ 375MHz
            ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

            // [5:4] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), 0x00);

            // [7:0] N_CODE = 0x4C --> 76 + 4 = 80
            ScalerSetByte_EXINT(PB_AC_SDM_02, 0x4C);
        }
        else if((GET_INPUT_PIXEL_CLK() >= 375) && (GET_INPUT_PIXEL_CLK() < 750))
        {
            // [2:0] rate_sel = 3'b011 --> 375MHz ~ 750MHz
            ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // [2:0] SEL_DIV = 3'b011 --> 375MHz ~ 750MHz
            ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // [5:4] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), 0x00);

            // [7:0] N_CODE = 0x24 --> 36 + 4 = 40
            ScalerSetByte_EXINT(PB_AC_SDM_02, 0x24);
        }
        else if((GET_INPUT_PIXEL_CLK() >= 750) && (GET_INPUT_PIXEL_CLK() < 1500))
        {
            // [2:0] rate_sel = 3'b010 --> 750MHz ~ 1500MHz
            ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            // [2:0] SEL_DIV = 3'b010 --> 750MHz ~ 1500MHz
            ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            // [5:4] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), 0x00);

            // [7:0] N_CODE = 0x10 --> 16 + 4 = 20
            ScalerSetByte_EXINT(PB_AC_SDM_02, 0x10);
        }
        else if((GET_INPUT_PIXEL_CLK() >= 1500) && (GET_INPUT_PIXEL_CLK() < 3000))
        {
            // [2:0] rate_sel = 3'b001 --> 1500MHz ~ 3000MHz
            ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            // [2:0] SEL_DIV = 3'b001 --> 1500MHz ~ 3000MHz
            ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            // [5:4] CMU_SELPREDIV = 2'b10 --> /4
            ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), _BIT5);

            // [7:0] N_CODE = 0x24 --> 36 + 4 = 40
            ScalerSetByte_EXINT(PB_AC_SDM_02, 0x24);
        }
        else if(GET_INPUT_PIXEL_CLK() >= 3000)
        {
            // [2:0] rate_sel = 3'b000 --> 3000MHz ~ 6000MHz
            ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // [2:0] SEL_DIV = 3'b000 --> 3000MHz ~ 6000MHz
            ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // [5:4] CMU_SELPREDIV = 2'b11 --> Ditermined By CMU_PREDIVN
            // [3:0] CMU_PREDIVN = 4'b0110 --> Predivder N = 6 + 2 = 8
            ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT1));

            // [7:0] N_CODE = 0x24 --> 36 + 4 = 40
            ScalerSetByte_EXINT(PB_AC_SDM_02, 0x24);
        }
    }


    /////////////////
    // CDR Setting //
    /////////////////

    // KD_L0 = 0
    // KD_L1 = 0
    // KD_L2 = 0
    ScalerSetBit_EXINT(PB_F4_CDR_05, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_F4_CDR_05, ~_BIT3, 0x00);
    ScalerSetBit_EXINT(PB_F5_CDR_06, ~_BIT7, 0x00);

#if(_MHL_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(PB_B6_BANDGAP_02, _BIT4) == _BIT4) // MHL2.0 Mode, DCDR
    {
        // Check if Packed Pixel Mode
        if(GET_TMDS_RX0_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            // KI_L0 = 3'b011 --> KI = 1/4
            ScalerSetBit_EXINT(PB_F4_CDR_05, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

            // KP_L0 = 0x13 --> KP = 12.75
            ScalerSetByte_EXINT(PB_F6_CDR_07, 0x33);
        }
        else
        {
            // KI_L0 = 3'b001 --> KI = 1/16
            ScalerSetBit_EXINT(PB_F4_CDR_05, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

            // KP_L0 = 0x13 --> KP = 11.75
            ScalerSetByte_EXINT(PB_F6_CDR_07, 0x2F);
        }
    }
    else   // HDMI Mode
#endif
    {
        // KI_L0 = 0
        // KI_L1 = 0
        // KI_L2 = 0
        ScalerSetBit_EXINT(PB_F4_CDR_05, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit_EXINT(PB_F4_CDR_05, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(PB_F5_CDR_06, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

        if(GET_INPUT_PIXEL_CLK() < 1500)
        {
            // KP_L0 = 8
            // KP_L1 = 8
            // KP_L2 = 8
            ScalerSetByte_EXINT(PB_F6_CDR_07, 0x20);
            ScalerSetByte_EXINT(PB_F7_CDR_08, 0x20);
            ScalerSetByte_EXINT(PB_F8_CDR_09, 0x20);
        }
        else
        {
            // KP_L0 = 4
            // KP_L1 = 4
            // KP_L2 = 4
            ScalerSetByte_EXINT(PB_F6_CDR_07, 0x10);
            ScalerSetByte_EXINT(PB_F7_CDR_08, 0x10);
            ScalerSetByte_EXINT(PB_F8_CDR_09, 0x10);
        }
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [0] en_clkout_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB_AE_SDM_04, ~_BIT0, 0x00);

    // [0] en_eqen_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 0 --> Disable Dataout
    ScalerSetBit_EXINT(PB_B1_DATA_TIMER, ~_BIT0, 0x00);

    // [7] Disable Hybrid Mode
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT7, 0x00);

#if(_MHL_SUPPORT == _ON)   // MHL 2.0 ACDR
    if((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, _BIT4) == _BIT4) &&
       (GET_INPUT_PIXEL_CLK() >= 2000))
    {
        // [6] Enable Lane0 ACDR
        ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT6, _BIT6);

        // [4] Enable Lane0 ACDR_DFE
        ScalerSetBit_EXINT(PB_B2_ANA_CDR, ~_BIT4, _BIT4);

        // [3] reg_en_data_manual_l0 = 1'b0
        // [2] reg_bypass_data_rdy_l0 = 1'b1
        // [1] reg_en_eqen_manual_l0 = 1'b0
        // [0] reg_bypass_eqen_rdy_l0 = 1'b1
        ScalerSetBit_EXINT(PB_B2_ANA_CDR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    }
    else
#endif
    {
        // [6] Disable Lane0 ACDR
        ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT6, 0x00);

        // [4] Disable Lane0 ACDR
        ScalerSetBit_EXINT(PB_B2_ANA_CDR, ~_BIT4, 0x00);
    }

    // [7:4] RST_N = 4'b0000 --> Digital Circuit Reset
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [7:4] RST_N = 4'b1111 --> Digital Circuit Normal
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));


    /////////////////
    // DFE Setting //
    /////////////////

    // Load DFE Initial Code
    ScalerTMDSSetDFEInitial_EXINT0();

    // [7:5] LE_lowgain_highboost = 1 --> LE LowGain HighBoost Mode
    ScalerSetBit_EXINT(PB_CB_KOFFSET_05, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    if(GET_INPUT_PIXEL_CLK() < 2000)
    {
        // [4] SEL_DFE_DELAY = 1'b1 --> Increase DFE Delay
        ScalerSetBit_EXINT(PB_C8_KOFFSET_02, ~_BIT6, _BIT6);
    }
    else
    {
        // [4] SEL_DFE_DELAY = 1'b0 --> Normal DFE Delay
        ScalerSetBit_EXINT(PB_C8_KOFFSET_02, ~_BIT6, 0x00);
    }

    if(GET_INPUT_PIXEL_CLK() < 2500)
    {
        // [7:5] LE_ISEL = 3'b000
        ScalerSetBit_EXINT(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [4:2] LE_RLSEL = 3'b011
        ScalerSetBit_EXINT(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));
    }
    else
    {
        // [7:5] LE_ISEL = 3'b010
        ScalerSetBit_EXINT(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

        // [4:2] LE_RLSEL = 3'b001
        ScalerSetBit_EXINT(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
    }


    //////////////
    // K Offset //
    //////////////

#if(_MHL_SUPPORT == _ON)   // MHL 2.0
    if(ScalerGetBit_EXINT(PB_B6_BANDGAP_02, _BIT4) == _BIT4)
    {
        // Enable Sumamp High Gain Mode
        ScalerSetBit_EXINT(PB_C9_KOFFSET_03, ~_BIT6, _BIT6);

        // Tap0 = 21
        ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, 0x15);
        ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x01);
        ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);
    }
    else
#endif
    {
        // Disable Sumamp High Gain Mode
        ScalerSetBit_EXINT(PB_C9_KOFFSET_03, ~_BIT6, 0x00);
    }

    // [6] Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT6, _BIT6);

    // [7] Toggle Foreground Calibration
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);

    // Waiting for K Offset
    DELAY_XUS_EXINT(150);

    // Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(PB_C9_KOFFSET_03, ~_BIT6, 0x00);

    // Tap0 = 15
    ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x01);
    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [4:0] Enable Tap0~2
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Enable Adaptation
    if(GET_INPUT_PIXEL_CLK() < 375)  // 187.5~375
    {
        // Disable Adaptation Loop  0x000
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);
    }
    else if(GET_INPUT_PIXEL_CLK() < 1000)   // 375~1000
    {
        // Enable the Vth, Tap0~1 Adaptation Loop 0x43
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x43);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x43);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x43);
    }
    else if(GET_INPUT_PIXEL_CLK() < 3000)   // 1000~3000
    {
        // Enable the LE, Vth, Tap0~1 Adaptation Loop 0xC3
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0xC3);
    }
    else   // 3000~3400
    {
        // Enable the Vth, Tap0 Adaptation Loop 0x041
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x41);
    }

#if(_MHL_SUPPORT == _ON)   // MHL 2.0 ACDR
    if((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, _BIT4) == _BIT4) &&
       (GET_INPUT_PIXEL_CLK() >= 2000))
    {
        // [1] reg_en_eqen_manual_l0 = 1'b1
        ScalerSetBit_EXINT(PB_B2_ANA_CDR, ~_BIT1, _BIT1);

        // [0] reg_rstb_fsm --> Toggle for FLD reset
        ScalerSetBit_EXINT(PB_CF_ANA_CDR_01, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(PB_CF_ANA_CDR_01, ~_BIT7, _BIT7);

        // Waiting for FLD Lock Band
        DELAY_XUS_EXINT(580);
    }
    else
#endif
    {
        // Reset Digital CDR
        ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // [7] cmu_en = 1'b1 --> Enable CMU PLL
        ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT7, _BIT7);

        // Waiting for CMU PLL Stable
        DELAY_XUS_EXINT(150);

        // [0] en_clkout_manual = 1 --> Enable Clkout
        ScalerSetBit_EXINT(PB_AE_SDM_04, ~_BIT0, _BIT0);

        // [0] en_eqen_manual = 1 --> Enable Adaptation
        ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, _BIT0);
    }

    // Waiting for the Adaptation
    DELAY_XUS_EXINT(290);

    // Reduce Loop Gain to 1/4
    ScalerSetBit_EXINT(P1D_A0_L0_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);
    ScalerSetBit_EXINT(P1D_B0_L1_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);
    ScalerSetBit_EXINT(P1D_C0_L2_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);

    // Waiting for the Adaptation
    DELAY_XUS_EXINT(290);

#if(_MHL_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(PB_B6_BANDGAP_02, _BIT4) == _BIT4) // MHL Mode
    {
        // Disable Adaptation Loop
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);

        // [0] en_eqen_manual = 0 --> Disable Adaptation
        ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, 0x00);

        // [3] reg_adp_eq_off = 1'b0 -->  Disable Analog CDR DFE Adaptation
        ScalerSetBit_EXINT(PB_CF_ANA_CDR_01, ~_BIT3, _BIT3);

        // [1] reg_en_eqen_manual_l0 = 1'b0
        ScalerSetBit_EXINT(PB_B2_ANA_CDR, ~_BIT1, 0x00);

        // Enable Sumamp High Gain Mode
        ScalerSetBit_EXINT(PB_C9_KOFFSET_03, ~_BIT6, _BIT6);

        // Tap0 = 21
        ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, 0x15);
        ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x01);
        ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);
    }
    else
#endif
    {
        if(GET_INPUT_PIXEL_CLK() < 3000) // 375~3000
        {
            // Disable the Vth Adaptation Loop
            ScalerSetBit_EXINT(P1D_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
            ScalerSetBit_EXINT(P1D_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
            ScalerSetBit_EXINT(P1D_C1_L2_DFE_EN_2, ~_BIT6, 0x00);
        }
        else  // 3000~3400
        {
            // Disable All Adapation Loop
            ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);

            // Restore Loop Gain to 1
            ScalerSetBit_EXINT(P1D_A0_L0_DFE_EN_1, ~(_BIT5 | _BIT4), 0x00);
            ScalerSetBit_EXINT(P1D_B0_L1_DFE_EN_1, ~(_BIT5 | _BIT4), 0x00);
            ScalerSetBit_EXINT(P1D_C0_L2_DFE_EN_1, ~(_BIT5 | _BIT4), 0x00);

            // Enable the LE, Tap1~2 Adaptation Loop 0x86
            ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x86);
            ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x86);
            ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x86);

            // Waiting for the Adaptation
            DELAY_XUS_EXINT(290);


            // Reduce Loop Gain to 1/4
            ScalerSetBit_EXINT(P1D_A0_L0_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);
            ScalerSetBit_EXINT(P1D_B0_L1_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);
            ScalerSetBit_EXINT(P1D_C0_L2_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);

            // Waiting for the Adaptation
            DELAY_XUS_EXINT(290);

            // Disable All Adaptation Loop
            ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);

            // [0] en_eqen_manual = 0 --> Disable Adaptation
            ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, 0x00);
        }
    }

#if(_MHL_SUPPORT == _ON)   // MHL 2.0 ACDR
    if((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, _BIT4) == _BIT4) &&
       (GET_INPUT_PIXEL_CLK() >= 2000))
    {
        // [3] en_data_manual_l0 = 1 --> Enable Dataout for Lane0
        ScalerSetBit_EXINT(PB_B2_ANA_CDR, ~_BIT3, _BIT3);
    }
    else
#endif
    {
        // [0] en_data_manual = 1 --> Enable Dataout
        ScalerSetBit_EXINT(PB_B1_DATA_TIMER, ~_BIT0, _BIT0);
    }

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
    BYTE pucBackUp[2];
    WORD usCount = 0;

#if(_MHL_SUPPORT == _ON)
    bit bMHLFail = _FALSE;
#endif

    pucBackUp[0] = ScalerGetByte_EXINT(P2_C9_HDMI_AP);
    pucBackUp[1] = ScalerGetByte_EXINT(P2_C8_HDMI_APC);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P2_C8_HDMI_APC, ~_BIT0, 0x00);

    // Freq. Stable Into IRQ
    if(((ScalerGetByte_EXINT(P2_EF_HDMI_ERROR_TH) & 0xC0) == 0xC0) && (g_ucTMDSClkIRQ == _ENABLE))
    {
        // Disable Freq Stable IRQ
        ScalerSetBit_EXINT(P2_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), _BIT6);

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
                // TMDS_OFFLine Measure FREQ(MHz) = GDI_CLK(MHz) * 1024 / g_usTMDSRx2ClkCount
                SET_TMDS_OFFLINE_MEASURE_CLK(((DWORD)(_GDI_CLK_KHZ * 1024) / 100) / g_usTMDSClkCount);
            }

#if(_MHL_SUPPORT == _ON)
            if(((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == 0x00) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT6) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT7) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
            {
                ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR);

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                // Set HDMI/DVI switch to Auto Mode
                ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
#else
                // Set HDMI/DVI switch to Manual Mode and Forced to HDMI
                ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
#endif

                SET_TMDS_RX0_CLK_MODE(_TMDS_MHL_PPMODE_PHY_SETTING);

                SET_INPUT_PIXEL_CLK(GET_INPUT_PIXEL_CLK() * 4);
                ScalerTMDSSetPhy_EXINT0();
                SET_INPUT_PIXEL_CLK(GET_INPUT_PIXEL_CLK() / 4);

                // Enable Packed Pixel Mode
                ScalerSetBit_EXINT(P26_A0_MHL_CTRL_00, ~_BIT1, _BIT1);

                // Check CDR Stable
                if((ScalerTMDSCheckCDRStable_EXINT0(g_usTMDSClkCount) == _FALSE) || (ScalerMHLDetectClkMode_EXINT0() == _FALSE))// MHL mode need modify
                {
                    SET_TMDS_RX0_CLK_MODE(_TMDS_24BIT_PHY_SETTING);

                    // TMDS_FREQ(MHz) = GDI_CLK(MHz) * 1024 / CLK_COUNT = GDI_CLK(KHz) * 1024 / (CLK_COUNT * 1024)
                    SET_INPUT_PIXEL_CLK(GET_INPUT_PIXEL_CLK() * 3);
                    ScalerTMDSSetPhy_EXINT0();
                    SET_INPUT_PIXEL_CLK(GET_INPUT_PIXEL_CLK() / 3);

                    // Disable Packed Pixel Mode
                    ScalerSetBit_EXINT(P26_A0_MHL_CTRL_00, ~_BIT1, 0x00);

                    if((ScalerTMDSCheckCDRStable_EXINT0(g_usTMDSClkCount) == _FALSE) || (ScalerMHLDetectClkMode_EXINT0() == _FALSE))// MHL Need modify
                    {
                        bMHLFail = _TRUE;
                    }
                }
            }
            else
            {
                SET_TMDS_RX0_CLK_MODE(_TMDS_24BIT_PHY_SETTING);

                ScalerTMDSSetPhy_EXINT0();

                // Disable Packed Pixel Mode
                ScalerSetBit_EXINT(P26_A0_MHL_CTRL_00, ~_BIT1, 0x00);

                // Set HDMI/DVI switch to Auto Mode
                ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR);
                ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
            }
#else
            ScalerTMDSSetPhy_EXINT0();
#endif  // end of #if(_MHL_SUPPORT == _ON)
        }

#if(_MHL_SUPPORT == _ON)
        if(bMHLFail == _FALSE)
#endif
        {
            // Set Upper Bound (allow 1/64 freq shift)
            ScalerSetByte_EXINT(P2_E8_HDMI_FREQDET_UPPER_M, (HIBYTE(usCount + (usCount >> 6)) & 0x7F));
            ScalerSetByte_EXINT(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(usCount + (usCount >> 6)));

            // Set Lower bound
            ScalerSetByte_EXINT(P2_EA_HDMI_FREQDET_LOWER_M, (HIBYTE(usCount - (usCount >> 6)) & 0x7F));
            ScalerSetByte_EXINT(P2_EB_HDMI_FREQDET_LOWER_L, LOBYTE(usCount - (usCount >> 6)));

            // Reset Color Depth to 8 Bits
            SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

            SET_TMDS_PHY_SET();
        }
    }

    // Freq. Unstable Into IRQ
    if(((ScalerGetByte_EXINT(P2_E6_HDMI_FREQDET_CTRL) & 0x06) == 0x06) && (g_ucTMDSClkIRQ == _ENABLE))
    {
        // Clear Unstable IRQ Flag
        ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

        // Ensure Freq really unstable
        if((abs(g_usTMDSClkCount - ScalerTMDSMeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (g_usTMDSClkCount >> 6)) ||
           (abs(GET_INPUT_PIXEL_CLK() - ((GET_TMDS_OFFLINE_MEASURE_CLK() << 3) / ((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) ? _COLOR_DEPTH_8_BITS : GET_COLOR_DEPTH()))) > (GET_INPUT_PIXEL_CLK() >> 6)))
        {
            // Set Display M1 output force to background color and free run mode
            ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);

            // Disable RGB/clock Output to avoid garbage
            ScalerSetBit_EXINT(P2_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // Disable Freq. Unstable IRQ
            ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

#if(_MHL_SUPPORT == _ON)
            // Set HDMI/DVI switch to Auto Mode
            ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR);
            ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);

            if(((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == 0x00) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT6) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT7) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
            {
                // Set Upper Bound
                ScalerSetByte_EXINT(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
                ScalerSetByte_EXINT(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));

                // Set Lower bound
                ScalerSetByte_EXINT(P2_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte_EXINT(P2_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Suspend Key Calculation before load key
                ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, 0x00);
            }
            else
#endif // End of #if(_MHL_SUPPORT == _ON)
            {
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
            }

            // Reset Freq. Detect Counter(Toggle)
            ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P2_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

            // Enable Freq. Stable IRQ
            ScalerSetBit_EXINT(P2_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            CLR_TMDS_PHY_SET();

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            // Reset Authenticated FSM
            ScalerSetByte_EXINT(P63_A2_HDCP_I2C_CTRL_A2, 0x01);
            ScalerSetBit_EXINT(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT6, _BIT6);

            // Cancel HDCP 2.2 Re-Auth Timer Event
            if(CHECK_TMDS_DPHY_SWITCH(_D0_INPUT_PORT) == _TRUE)
            {
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
                ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX0_HDCP2_REAUTH);
#endif
            }
            else if(CHECK_TMDS_DPHY_SWITCH(_D1_INPUT_PORT) == _TRUE)
            {
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
                ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX1_HDCP2_REAUTH);
#endif
            }
            else if(CHECK_TMDS_DPHY_SWITCH(_D2_INPUT_PORT) == _TRUE)
            {
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
                ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH);
#endif
            }

#endif
        }
    }

    // HDCP 1.4 Write Aksv IRQ have been Received
    if((ScalerGetBit_EXINT(P2_A9_TMDS_ABC0, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P2_AA_TMDS_ABC1, _BIT4) == _BIT4))
    {
        // clear AKSV flag
        ScalerSetBit_EXINT(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), _BIT7);

        // SET KEY ready bit 1
        ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, _BIT1);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Enable HDCP 1.4 Module
        ScalerSetBit_EXINT(P2_C0_HDCP_CR, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Disable HDCP 2 Function
        ScalerSetBit_EXINT(P63_A0_HDCP_I2C_CTRL_A0, ~_BIT7, 0x00);
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
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process In PS/PD State(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSPSIntHandler_EXINT0(void) using 1
{
    BYTE pucBackUp[2];

    pucBackUp[0] = ScalerGetByte_EXINT(P2_C9_HDMI_AP);
    pucBackUp[1] = ScalerGetByte_EXINT(P2_C8_HDMI_APC);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P2_C8_HDMI_APC, ~_BIT0, 0x00);

    // HDCP 1.4 Write Aksv IRQ have been Received
    if((ScalerGetBit_EXINT(P2_A9_TMDS_ABC0, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P2_AA_TMDS_ABC1, _BIT4) == _BIT4))
    {
        // clear AKSV flag
        ScalerSetBit_EXINT(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), _BIT7);

        // SET KEY ready bit 1
        ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, _BIT1);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Enable HDCP 1.4 Module
        ScalerSetBit_EXINT(P2_C0_HDCP_CR, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Disable HDCP 2 Function
        ScalerSetBit_EXINT(P63_A0_HDCP_I2C_CTRL_A0, ~_BIT7, 0x00);
#endif
    }

    // Clear IRQ Pending Flag
    ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_60_PORT_PAGE2_HDMI_INTCR);
    ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~_BIT7, _BIT7);

    ScalerSetByte_EXINT(P2_C8_HDMI_APC, pucBackUp[1]);
    ScalerSetByte_EXINT(P2_C9_HDMI_AP, pucBackUp[0]);
}

//--------------------------------------------------
// Description  : Check CDR Locked
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
bit ScalerTMDSCheckCDRStable(BYTE ucInputPort, WORD usClkCount)
{
    // Disable INT Clock Check
    g_ucTMDSClkIRQ = _DISABLE;

#if(_MHL_SUPPORT == _ON)

    if(((ucInputPort == _D0_INPUT_PORT) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ucInputPort == _D1_INPUT_PORT) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ucInputPort == _D2_INPUT_PORT) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
    {
        switch(GET_TMDS_RX0_CLK_MODE())
        {
            // Check if Packed Pixel Mode
            case _TMDS_MHL_PPMODE_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSMeasureClk(ucInputPort, _CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
                {
                    DebugMessageDigital("R Channel CDR Unstable", ScalerTMDSMeasureClk(ucInputPort, _CLK_SOURCE_RED));

                    // Enable INT Clock Check
                    g_ucTMDSClkIRQ = _ENABLE;

                    return _FALSE;
                }

                break;

            // Check if 24 Bit Mode
            case _TMDS_24BIT_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSMeasureClk(ucInputPort, _CLK_SOURCE_RED) * 3)) > (usClkCount >> 6))
                {
                    DebugMessageDigital("R Channel CDR Unstable", ScalerTMDSMeasureClk(ucInputPort, _CLK_SOURCE_RED));

                    // Enable INT Clock Check
                    g_ucTMDSClkIRQ = _ENABLE;

                    return _FALSE;
                }

                break;

            default:

                // Enable INT Clock Check
                g_ucTMDSClkIRQ = _ENABLE;

                return _FALSE;
                break;
        }
    }
    else

#endif // End of #if(_MHL_SUPPORT == _ON)
    {
        // Check Current Measured Freq. is the same as previously locked
        if(abs(usClkCount - ScalerTMDSMeasureClk(ucInputPort, _CLK_SOURCE_RED)) > (usClkCount >> 6))
        {
            // Enable INT Clock Check
            g_ucTMDSClkIRQ = _ENABLE;

            return _FALSE;
        }

        if(abs(usClkCount - ScalerTMDSMeasureClk(ucInputPort, _CLK_SOURCE_BLUE)) > (usClkCount >> 6))
        {
            // Enable INT Clock Check
            g_ucTMDSClkIRQ = _ENABLE;

            return _FALSE;
        }

        if(abs(usClkCount - ScalerTMDSMeasureClk(ucInputPort, _CLK_SOURCE_GREEN)) > (usClkCount >> 6))
        {
            // Enable INT Clock Check
            g_ucTMDSClkIRQ = _ENABLE;

            return _FALSE;
        }
    }

    // Enable INT Clock Check
    g_ucTMDSClkIRQ = _ENABLE;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check CDR Locked (EXINT0 Only)
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
BYTE ScalerTMDSCheckCDRStable_EXINT0(WORD usClkCount) using 1
{
#if(_MHL_SUPPORT == _ON)

    if(((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == 0x00) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT6) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT7) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
    {
        switch(GET_TMDS_RX0_CLK_MODE())
        {
            // Check if Packed Pixel Mode
            case _TMDS_MHL_PPMODE_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSMeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSMeasureClk_EXINT0(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                break;

            // Check if 24 Bit Mode
            case _TMDS_24BIT_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSMeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSMeasureClk_EXINT0(_CLK_SOURCE_RED) * 3)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                break;

            default:

                return _FALSE;
                break;
        }
    }
    else

#endif // End of #if(_MHL_SUPPORT == _ON)
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

#if(_MHL_SUPPORT == _ON)
    if(((ucInputPort == _D0_INPUT_PORT) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ucInputPort == _D1_INPUT_PORT) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ucInputPort == _D2_INPUT_PORT) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
    {
        // Enable CMU_EN(Lane0) and Rx_EN(Lane0,3)
        ScalerSetByte(PB_C0_CMU_03, 0x91);
    }
    else
#endif
    {
        // Enable CMU_EN(Lane0,1,2) and Rx_EN(Lane0,1,2,3)
        ScalerSetByte(PB_C0_CMU_03, 0xF7);
    }

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

#if(_MHL_SUPPORT == _ON)
    if(((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == 0x00) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT6) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ScalerGetBit_EXINT(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT7) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
    {
        // Enable CMU_EN(Lane0) and Rx_EN(Lane0,3)
        ScalerSetByte_EXINT(PB_C0_CMU_03, 0x91);
    }
    else
#endif
    {
        // Enable CMU_EN(Lane0,1,2) and Rx_EN(Lane0,1,2,3)
        ScalerSetByte_EXINT(PB_C0_CMU_03, 0xF7);
    }

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

    if((enumColorFormat == _COLOR_SPACE_YPBPR) ||
       (enumColorFormat == _COLOR_SPACE_YCBCR444) ||
       (enumColorFormat == _COLOR_SPACE_YCBCR422) ||
       (enumColorFormat == _COLOR_SPACE_YCBCR420))
    {
        ScalerSetByte(P2_BA_TMDS_ROUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P2_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P2_BC_TMDS_GOUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P2_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P2_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P2_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
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
#if(_D0_TMDS_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            // Check YCbCr 420 format; only support 8 bit
            if(ScalerColorGetColorSpace() == _COLOR_SPACE_YCBCR420)
            {
                return _FALSE;
            }

            break;
#endif

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

#if(_MHL_SUPPORT == _ON)
    if(((ucPortSelect == _D0_INPUT_PORT) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ucPortSelect == _D1_INPUT_PORT) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
       ((ucPortSelect == _D2_INPUT_PORT) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
    {
        // Set Upper Bound
        ScalerSetByte(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_PS_UPPER_BOUND));
        ScalerSetByte(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_PS_UPPER_BOUND));
    }
    else
#endif
    {
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
        // Set Upper Bound
        ScalerSetByte(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));
        ScalerSetByte(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));
#else
        ScalerSetByte(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_PS_LOW_SPEED_UPPER_BOUND));
        ScalerSetByte(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_PS_LOW_SPEED_UPPER_BOUND));
#endif
    }

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
    MCU_FFE4_DDC0_EDID_IRQ = ((MCU_FFE4_DDC0_EDID_IRQ & ~(_BIT3 | _BIT1)) | (_BIT2 | _BIT0));
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
    ucSourceType = ucSourceType;
    ucInputPort = ucInputPort;
}

//--------------------------------------------------
// Description  : Signal Detection for TMDS(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSPSPreDetect(BYTE ucInputPort)
{
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

    if((ucInputPort == _D0_INPUT_PORT) && (GET_TMDS_RX0_DDC_DETECTED() == _TRUE))
    {
        // DDC handshake Detected
        DebugMessageDigital("7. wuzanne test : Normal D0 DDC", 0);

        CLR_TMDS_RX0_DDC_DETECTED();

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        SET_D0_HDMI_PS_WAKEUP();
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX0_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    if(ucInputPort == _D0_INPUT_PORT)
    {
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
        if(((MCU_FFE4_DDC0_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX0_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX0_DDC_DETECTED();
        }
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
        if(((MCU_FFE5_DDC1_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX0_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX0_DDC_DETECTED();
        }
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
        if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX0_DDC_DETECTED() != _TRUE))
        {
            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
            MCU_FE69_DDC2_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX0_DDC_DETECTED();
        }
#endif // End of #if(_D0_DDC_CHANNEL_SEL == _DDC0)
    }
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

    if((ucInputPort == _D1_INPUT_PORT) && (GET_TMDS_RX1_DDC_DETECTED() == _TRUE))
    {
        DebugMessageDigital("7. wuzanne test : Normal D1 DDC", 0);

        CLR_TMDS_RX1_DDC_DETECTED();

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        SET_D1_HDMI_PS_WAKEUP();
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX1_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
        if(((MCU_FFE4_DDC0_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX1_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX1_DDC_DETECTED();
        }
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
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

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        SET_D2_HDMI_PS_WAKEUP();
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX2_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    if(ucInputPort == _D2_INPUT_PORT)
    {
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
        if(((MCU_FFE4_DDC0_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX2_DDC_DETECTED();
        }
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
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
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
        if(ucInputPort == _D0_INPUT_PORT)
        {
            SET_D0_HDMI_PS_WAKEUP();
        }
        else if(ucInputPort == _D1_INPUT_PORT)
        {
            SET_D1_HDMI_PS_WAKEUP();
        }
        else if(ucInputPort == _D2_INPUT_PORT)
        {
            SET_D2_HDMI_PS_WAKEUP();
        }
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        if(ucInputPort == _D0_INPUT_PORT)
        {
            SET_TMDS_RX0_TOGGLE_Z0();
        }
        else if(ucInputPort == _D1_INPUT_PORT)
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
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
    // DDC handshake Detected
    if((ucInputPort == _D0_INPUT_PORT) && (GET_TMDS_RX0_DDC_DETECTED() == _TRUE))
    {
        DebugMessageDigital("7. wuzanne test : Normal D0 DDC", 0);

        CLR_TMDS_RX0_DDC_DETECTED();

        return _TRUE;
    }

    if(ucInputPort == _D0_INPUT_PORT)
    {
        // Enable DDC Toggle IRQ
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
        if(((MCU_FFE4_DDC0_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX0_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX0_DDC_DETECTED();
        }
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
        if(((MCU_FFE5_DDC1_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX0_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX0_DDC_DETECTED();
        }
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
        if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX0_DDC_DETECTED() != _TRUE))
        {
            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
            MCU_FE69_DDC2_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX0_DDC_DETECTED();
        }
#endif // End of #if(_D0_DDC_CHANNEL_SEL == _DDC0)
    }
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
    if((ucInputPort == _D1_INPUT_PORT) && (GET_TMDS_RX1_DDC_DETECTED() == _TRUE))
    {
        DebugMessageDigital("7. wuzanne test : Normal D1 DDC", 0);

        CLR_TMDS_RX1_DDC_DETECTED();

        return _TRUE;
    }

    if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
        if(((MCU_FFE4_DDC0_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX1_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX1_DDC_DETECTED();
        }
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
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
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
        if(((MCU_FFE4_DDC0_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
        {
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT3;

            CLR_TMDS_RX2_DDC_DETECTED();
        }
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
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
#if(_D0_TMDS_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
            {
                return _SOURCE_NONE;
            }

            break;
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
            {
                return _SOURCE_NONE;
            }

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
            {
                return _SOURCE_NONE;
            }

            break;
#endif

        default:

            break;
    }

    if(GET_TMDS_PHY_SET() == _TRUE)
    {
#if(_MHL_SUPPORT == _ON)

        // Set DIGITAL_PORT_SWITCH Flag for MHL
        switch(ucInputPort)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
            case _D0_INPUT_PORT:
                if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
                {
                    SET_DIGITAL_PORT_SWITCH_TO_D0();
                }

                break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            case _D1_INPUT_PORT:
                if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
                {
                    SET_DIGITAL_PORT_SWITCH_TO_D1();
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            case _D2_INPUT_PORT:
                if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
                {
                    SET_DIGITAL_PORT_SWITCH_TO_D2();
                }

                break;
#endif
            default:
                break;
        }
#endif

        // Delay for PHY Stable
        ScalerTimerDelayXms(2);

#if(_MHL_SUPPORT == _ON)
        // Detect MHL Mode
        if((ScalerTMDSCheckCDRStable(ucInputPort, g_usTMDSClkCount) == _FALSE) || (ScalerTMDSCheckDataDFE(ucInputPort) == _FALSE) ||
           ((((ucInputPort == _D0_INPUT_PORT) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
             ((ucInputPort == _D1_INPUT_PORT) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
             ((ucInputPort == _D2_INPUT_PORT) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE))) &&
            (ScalerMHLDetectClkMode() == _FALSE)))
#else // Else of #if(_MHL_SUPPORT == _ON)
        if((ScalerTMDSCheckCDRStable(ucInputPort, g_usTMDSClkCount) == _FALSE) || (ScalerTMDSCheckDataDFE(ucInputPort) == _FALSE))
#endif // End of #if(_MHL_SUPPORT == _ON)
        {
#if(_MHL_SUPPORT == _ON)
            // Detect MHL Mode
            if(((ucInputPort == _D0_INPUT_PORT) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((ucInputPort == _D1_INPUT_PORT) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((ucInputPort == _D2_INPUT_PORT) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
            {
                // Set Upper Bound
                ScalerSetByte(P2_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
                ScalerSetByte(P2_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));

                // Set Lower bound
                ScalerSetByte(P2_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P2_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
            }
            else
#endif // End of #if(_MHL_SUPPORT == _ON)
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
            }

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

        DebugMessageRx0("9. Freq Check Pass => Pixel Clock", GET_INPUT_PIXEL_CLK());

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

#if(_MHL_SUPPORT == _ON)
            if(GET_TMDS_RX0_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
            {
                ucTMDSType = _SOURCE_HDMI;
            }
            else
#endif
            {
                ucTMDSType = _SOURCE_DVI;
            }
        }

        switch(ucInputPort)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
            case _D0_INPUT_PORT:

                // Mute ASUS Padfone until Source Read Ri Done (Incase of Color Format Error)
                if(((GET_MHL_RX0_ADOPTER_ID_HBYTE() == _ASUS_PADFONE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX0_ADOPTER_ID_LBYTE() == _ASUS_PADFONE2_ADOPTER_ID_LBYTE)) &&
                   !(((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT7) == _BIT7) || (ScalerGetBit(P2_AE_TMDS_RPS, (_BIT1)) == _BIT1)) && (ScalerGetBit(P2_A9_TMDS_ABC0, _BIT6) == _BIT6)))
                {
                    return _SOURCE_NONE;
                }

                break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            case _D1_INPUT_PORT:

                // Mute ASUS Padfone until Source Read Ri Done (Incase of Color Format Error)
                if(((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _ASUS_PADFONE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _ASUS_PADFONE2_ADOPTER_ID_LBYTE)) &&
                   !(((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT7) == _BIT7) || (ScalerGetBit(P2_AE_TMDS_RPS, (_BIT1)) == _BIT1)) && (ScalerGetBit(P2_A9_TMDS_ABC0, _BIT6) == _BIT6)))
                {
                    return _SOURCE_NONE;
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            case _D2_INPUT_PORT:

                // Mute ASUS Padfone until Source Read Ri Done (Incase of Color Format Error)
                if(((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _ASUS_PADFONE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _ASUS_PADFONE2_ADOPTER_ID_LBYTE)) &&
                   !(((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT7) == _BIT7) || (ScalerGetBit(P2_AE_TMDS_RPS, (_BIT1)) == _BIT1)) && (ScalerGetBit(P2_A9_TMDS_ABC0, _BIT6) == _BIT6)))
                {
                    return _SOURCE_NONE;
                }

                break;
#endif

            default:

                break;
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

        // [1] De_inverse = 1'b1 --> Adapation Only for Data Area (Transition Minimum)
        // [0] De_brank_en = 1'b1 --> Enable Blank Function of gdi_de
        ScalerSetBit(P1D_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P1D_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P1D_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

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
            if(GET_HDMIRX0_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE)
            {
                SET_HDMI_FREESYNC_ENABLED();

                // Get SPD Free Sync Vfreq Max
                g_usFREESYNCVFreq_max = (WORD)GET_HDMIRX0_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MAX_VFREQ) * 10;
                g_usFREESYNCVFreq_min = (WORD)GET_HDMIRX0_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MIN_VFREQ) * 10;

                // Disable DE Only Mode
                ScalerSetBit(P2_A7_TMDS_PWDCTL, ~_BIT7, 0x00);
            }
#endif
        }
        else
        {
#if(_MHL_SUPPORT == _ON)
            // Guard Band reference disable for data remapping
            ScalerSetBit(P26_B2_MHL_CTRL_12, ~_BIT7, 0x00);
#endif

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

#if(_MHL_SUPPORT == _ON)

        if(((ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == 0x00) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
           ((ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT6) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
           ((ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT7) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
        {
            // Set Manual Format to HDMI
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
        }
#endif
        return _SOURCE_HDMI;
    }
    else
    {
        ScalerSetBit(P2_AF_TMDS_WDC, ~_BIT0, _BIT0);

#if(_MHL_SUPPORT == _ON)

        if(((ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == 0x00) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
           ((ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT6) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
           ((ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) == _BIT7) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)))
        {
            // Set Manual Format to DVI
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT3);
        }
#endif
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
    if((ScalerGetBit(P2_C0_HDCP_CR, _BIT0) == _BIT0) && (ScalerGetBit(P63_A0_HDCP_I2C_CTRL_A0, _BIT7) == 0x00))
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
    else if((ScalerGetBit(P2_C0_HDCP_CR, _BIT0) == 0x00) && (ScalerGetBit(P63_A0_HDCP_I2C_CTRL_A0, _BIT7) == _BIT7))
    {
        if(ScalerGetByte(P63_A6_HDCP_I2C_CTRL_A6) == 0x10)
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
// Description  : DFE Adaptation in Normal Signal
// Input Value  : None
// Output Value : True --> DFE Normal
//                False --> DFE Abnormal
//--------------------------------------------------
bit ScalerTMDSCheckDataDFE(BYTE ucInputPort)
{
    BYTE ucTemp = 0;
    BYTE ucCnt = 0;
    ucInputPort = ucInputPort;

    for(pData[0] = 0; pData[0] <= 2; pData[0]++)
    {
        // Sel lane
        ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), pData[0] << 6);

        // Read VTH
        ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        if((ScalerGetByte(P1D_F1_COEF_2) & 0x1F) == 0)
        {
            for(ucCnt = 0; ucCnt < 3; ucCnt++)
            {
                // Read TAP0
                ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                ucTemp = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

                if(ucTemp < 21)
                {
                    return _TRUE;
                }
                else if(ucCnt == 2)
                {
                    DebugMessageRx0("DFE Abnormal ", 0);
                    return _FALSE;
                }
            }
        }
    }
    return _TRUE;
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
    CLR_TMDS_RX0_DDC_DETECTED();
    CLR_TMDS_RX1_DDC_DETECTED();
    CLR_TMDS_RX2_DDC_DETECTED();

    switch(ucInputPort)
    {
#if(_D0_TMDS_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
            {
                DebugMessageRx0("Rx HPD Toggle!!", 0);
                return _FALSE;
            }

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)

            if(GET_TMDS_RX0_TOGGLE_Z0() == _TRUE)
            {
                SET_TMDS_RX0_TOGGLE_Z0_EVENT();

                return _FALSE;
            }

#endif
            break;
#endif

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
        DebugMessageRx0("CDR Unstable!!", ucSourceType);
        return _FALSE;
    }

    // Check TMDS Clock Output Disable
    if(ScalerGetBit(P2_A6_TMDS_OUTCTL, _BIT3) == 0x00)
    {
        DebugMessageRx0("TMDS Clock Output has been disable", ucSourceType);
        return _FALSE;
    }


    // Check TMDS Format Changed
#if(_MHL_SUPPORT == _ON)
    if((GET_TMDS_RX0_CLK_MODE() == _TMDS_24BIT_PHY_SETTING) ||
       ((GET_TMDS_RX0_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING) && (ucSourceType == _SOURCE_DVI)))
#endif
    {
        if(ucSourceType == _SOURCE_HDMI)
        {
            if(ScalerGetBit(P2_CB_HDMI_SR, _BIT0) == 0x00)
            {
                DebugMessageRx0("TMDS Format Changed", ucSourceType);
                return _FALSE;
            }
        }
        else
        {
            if(ScalerGetBit(P2_CB_HDMI_SR, _BIT0) == _BIT0)
            {
                DebugMessageRx0("TMDS Format Changed", ucSourceType);
                return _FALSE;
            }
        }
    }

    switch(ucInputPort)
    {
#if(_D0_TMDS_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_TMDS_Z0_ASSERTED() == _TRUE)
            {
                if((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT6) == _BIT6) && (!((((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT7)) == _BIT7) || ((ScalerGetBit(P2_AE_TMDS_RPS, _BIT1)) == _BIT1)) && ((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT5)) == _BIT5))))
                {
                    SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

                    CLR_TMDS_Z0_ASSERTED();

                    DebugMessageRx0("7. HDCP Abnormal !!!!!", 0);

                    // MHL mode of MHL PORT will not return FALSE
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
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

                    DebugMessageRx0("7. HDCP Normal", 0);
                }
            }

            break;
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_TMDS_Z0_ASSERTED() == _TRUE)
            {
                if((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT6) == _BIT6) && (!((((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT7)) == _BIT7) || ((ScalerGetBit(P2_AE_TMDS_RPS, _BIT1)) == _BIT1)) && ((ScalerGetBit(P2_A9_TMDS_ABC0, _BIT5)) == _BIT5))))
                {
                    SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

                    CLR_TMDS_Z0_ASSERTED();

                    DebugMessageRx0("7. HDCP Abnormal !!!!!", 0);

                    // MHL mode of MHL PORT will not return FALSE
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
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

                    DebugMessageRx0("7. HDCP Normal", 0);
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

                    DebugMessageRx0("7. HDCP Abnormal !!!!!", 0);

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

                    DebugMessageRx0("7. HDCP Normal", 0);
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
                DebugMessageRx0("TMDS Video format changed", ucSourceType);

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
                    DebugMessageRx0("Color Info Changed", ucSourceType);
                    return _FALSE;
                }

                if(ScalerTMDSHdmiAviPixelRepInfoChanged() == _TRUE)
                {
                    DebugMessageRx0("Pixel Repetition Info Changed", ucSourceType);
                    return _FALSE;
                }
            }
            else
            {
#if(_MHL_SUPPORT == _ON)
                if(GET_TMDS_RX0_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
#endif
                {
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                    {
                        DebugMessageRx0("HDMI Info Frame Not Received and not RGB", ucSourceType);
                        return _FALSE;
                    }
                }

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
                if(GET_COLOR_RGB_QUANTIZATION_RANGE() != _RGB_QUANTIZATION_RESERVED)
                {
                    DebugMessageRx0("No Quantization Range Specified", ucSourceType);
                    return _FALSE;
                }
#endif

                if(GET_TMDS_RX0_AVI_PIXEL_REPETITION() != _AVI_PIXEL_REPETITION_0)
                {
                    DebugMessageRx0("Pixel Repetition Not Received and not Pixel repetition 0", ucSourceType);
                    return _FALSE;
                }
            }

            if((ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_41_PORT_PAGE2_HDMI_VWDSR, _BIT0) == _BIT0) && (ScalerGetBit(P2_CC_HDMI_GPVS, _BIT0) == _BIT0))
            {
                DebugMessageRx0("HDMI AVI info frame has changed", ucSourceType);
                return _FALSE;
            }

            if(GET_HDMI_GCP_RECEIVED() == _TRUE)
            {
                if((GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422) && (ScalerTMDSHdmiGetColorDepth() != GET_COLOR_DEPTH()))
                {
                    DebugMessageRx0("Color Depth Has Changed", GET_COLOR_DEPTH());
                    return _FALSE;
                }
            }
            else
            {
                if((GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422) && (GET_COLOR_DEPTH() != _COLOR_DEPTH_8_BITS))
                {
                    DebugMessageRx0("HDMI GCP PACKET Not Received and not 8 bit", ucSourceType);
                    return _FALSE;
                }
            }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
            if(GET_TMDS_RX0_SPD_INFO_FRAME_RECEIVED() == _TRUE)
            {
                if((bit)GET_HDMIRX0_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) != GET_HDMI_FREESYNC_ENABLED())
                {
                    DebugMessageRx0("HDMI Freesync Status Change", GET_HDMI_FREESYNC_ENABLED());
                    return _FALSE;
                }
            }
            else
            {
                if(GET_HDMI_FREESYNC_ENABLED() == _TRUE)
                {
                    DebugMessageRx0("HDMI Freesync Status Change", GET_HDMI_FREESYNC_ENABLED());
                    return _FALSE;
                }
            }
#endif
        }
    }

#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
    if(GET_HDMI_HOTPLUG_TOGGLE() == _TRUE)
    {
        if(ucInputPort == _D0_INPUT_PORT)
        {
            if(GET_D0_HDMI_PS_WAKEUP() == _TRUE)
            {
                CLR_D0_HDMI_PS_WAKEUP();

                SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_EIZO_PS_WAKEUP);

                // MHL mode of MHL PORT will not return FALSE
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
                {
                    return _FALSE;
                }
#else
                return _FALSE;
#endif
            }
        }
        else if(ucInputPort == _D1_INPUT_PORT)
        {
            if(GET_D1_HDMI_PS_WAKEUP() == _TRUE)
            {
                CLR_D1_HDMI_PS_WAKEUP();

                SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_EIZO_PS_WAKEUP);

                // MHL mode of MHL PORT will not return FALSE
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
                {
                    return _FALSE;
                }
#else
                return _FALSE;
#endif
            }
        }
        else if(ucInputPort == _D2_INPUT_PORT)
        {
            if(GET_D2_HDMI_PS_WAKEUP() == _TRUE)
            {
                CLR_D2_HDMI_PS_WAKEUP();

                SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_EIZO_PS_WAKEUP);

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
        }
    }
    else
    {
        CLR_D0_HDMI_PS_WAKEUP();
        CLR_D1_HDMI_PS_WAKEUP();
        CLR_D2_HDMI_PS_WAKEUP();
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
#if(_D0_TMDS_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            ScalerTMDSBeforeHotPlugEventProc(_D0_INPUT_PORT);

            // ACER mode and DVI port will only toggle Z0 130ms
#if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
            if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
            {
                // MHL mode of MHL_PORT can not pull HPD
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D0_CABLE_STATUS() == _TRUE) && (GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
                if((GET_D0_CABLE_STATUS() == _TRUE) && (GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE))
#endif
#else
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D0_CABLE_STATUS() == _TRUE))
#else
                if(GET_D0_CABLE_STATUS() == _TRUE)
#endif
#endif
                {
                    ScalerTimerDelayXms(_TMDS_ACER_HPD_TIME);
                }
            }
            else
#endif
            {
                // HPD Low
                ScalerTMDSHotPlugLowProc(_D0_INPUT_PORT);

                // wait
                if((GET_TMDS_RX0_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL) || (GET_TMDS_RX0_HPD_TRIGGER_EVENT() == _TMDS_HPD_EIZO_PS_WAKEUP))
                {
                    ScalerTMDSHotPlugHighProc(_D0_INPUT_PORT, GET_HDMI_HOTPLUG_TIME());
                }
                else if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
                {
                    ScalerTMDSHotPlugHighProc(_D0_INPUT_PORT, _TMDS_HDCP_2_2_HPD_TIME);
                }
                else if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
                {
                    ScalerTMDSHotPlugHighProc(_D0_INPUT_PORT, _TMDS_ACER_HPD_TIME);
                }
                else if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() == _TMDS_HPD_EDID_SWITCH)
                {
                    ScalerTMDSHotPlugHighProc(_D0_INPUT_PORT, _TMDS_EDID_SWITCH_HPD_TIME);
                }
                else
                {
                    ScalerTMDSHotPlugHighProc(_D0_INPUT_PORT, GET_HDMI_HOTPLUG_TIME());
                }
            }

            // Restore Slave Address and Z0 Status
            ScalerTMDSAfterHotPlugEventProc(_D0_INPUT_PORT);

            DebugMessageRx0("Rx0 HPD Toggle!!", 0);

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
            if(GET_TMDS_RX0_TOGGLE_Z0_EVENT() == _TRUE)
            {
                CLR_TMDS_RX0_TOGGLE_Z0();
                CLR_TMDS_RX0_TOGGLE_Z0_EVENT();
            }
#endif

            CLR_TMDS_RX0_HPD_TRIGGER_EVENT();

            break;
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            ScalerTMDSBeforeHotPlugEventProc(_D1_INPUT_PORT);

            // ACER mode and DVI port will only toggle Z0 130ms
#if((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
            if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
            {
                // MHL mode of MHL_PORT can not pull HPD
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE) && (GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
                if((GET_D1_CABLE_STATUS() == _TRUE) && (GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE))
#endif
#else
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE))
#else
                if(GET_D1_CABLE_STATUS() == _TRUE)
#endif
#endif
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
                if((GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL) || (GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_EIZO_PS_WAKEUP))
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

            DebugMessageRx0("Rx1 HPD Toggle!!", 0);

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
                // MHL mode of MHL_PORT can not pull HPD
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D2_CABLE_STATUS() == _TRUE) && (GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
                if((GET_D2_CABLE_STATUS() == _TRUE) && (GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE))
#endif
#else
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D2_CABLE_STATUS() == _TRUE))
#else
                if(GET_D2_CABLE_STATUS() == _TRUE)
#endif
#endif
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
                if((GET_TMDS_RX2_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL) || (GET_TMDS_RX2_HPD_TRIGGER_EVENT() == _TMDS_HPD_EIZO_PS_WAKEUP))
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

            DebugMessageRx0("Rx2 HPD Toggle!!", 0);

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
#if(_D0_TMDS_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            // MHL mode of MHL_PORT can not pull HPD
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D0_CABLE_STATUS() == _TRUE) && (GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
            if((GET_D0_CABLE_STATUS() == _TRUE) && (GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE))
#endif
#else
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D0_CABLE_STATUS() == _TRUE))
#else
            if(GET_D0_CABLE_STATUS() == _TRUE)
#endif
#endif
            {
                // Save Z0 Status
                g_ucTMDSRx0Z0Status = ScalerGetBit(PB_B7_IMPEDANCE_00, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Backup Slave Address
                ScalerGetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, 1, &g_ucTMDSSlaveAddr, _NON_AUTOINC);

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() != _TMDS_HPD_EIZO_PS_WAKEUP)
#endif
                {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)))
                    // Reset HDCP 2.2
                    ScalerHdcp2ResetTMDSProc(_D0_INPUT_PORT);
#endif
                    // Disable Z0
                    ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                }
            }
            else if(GET_D0_CABLE_STATUS() == _FALSE)
            {
                // DDC reset
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT1;
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT1;
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE65_DDC2_DDC_CONTROL_1 |= _BIT1;
#endif
            }

            break;
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            // MHL mode of MHL_PORT can not pull HPD
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE) && (GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
            if((GET_D1_CABLE_STATUS() == _TRUE) && (GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE))
#endif
#else
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE))
#else
            if(GET_D1_CABLE_STATUS() == _TRUE)
#endif
#endif
            {
                // Save Z0 Status
                g_ucTMDSRx1Z0Status = ScalerGetBit(PB_B9_IMPEDANCE_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Backup Slave Address
                ScalerGetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, 1, &g_ucTMDSSlaveAddr, _NON_AUTOINC);

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() != _TMDS_HPD_EIZO_PS_WAKEUP)
#endif
                {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)))
                    // Reset HDCP 2.2
                    ScalerHdcp2ResetTMDSProc(_D1_INPUT_PORT);
#endif
                    // Disable Z0
                    ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                }
            }
            else if(GET_D1_CABLE_STATUS() == _FALSE)
            {
                // DDC reset
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT1;
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT1;
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE65_DDC2_DDC_CONTROL_1 |= _BIT1;
#endif
            }

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            // MHL mode of MHL_PORT can not pull HPD
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D2_CABLE_STATUS() == _TRUE) && (GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
            if((GET_D2_CABLE_STATUS() == _TRUE) && (GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE))
#endif
#else
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D2_CABLE_STATUS() == _TRUE))
#else
            if(GET_D2_CABLE_STATUS() == _TRUE)
#endif
#endif
            {
                // Save Z0 Status
                g_ucTMDSRx2Z0Status = ScalerGetBit(PB_BB_IMPEDANCE_04, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Backup Slave Address
                ScalerGetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, 1, &g_ucTMDSSlaveAddr, _NON_AUTOINC);

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() != _TMDS_HPD_EIZO_PS_WAKEUP)
#endif
                {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)))
                    // Reset HDCP 2.2
                    ScalerHdcp2ResetTMDSProc(_D2_INPUT_PORT);
#endif
                    // Disable Z0
                    ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                }
            }
            else if(GET_D2_CABLE_STATUS() == _FALSE)
            {
                // DDC reset
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT1;
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
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
#if(_D0_TMDS_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            // MHL mode of MHL_PORT can not pull HPD
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D0_CABLE_STATUS() == _TRUE) && (GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
            if((GET_D0_CABLE_STATUS() == _TRUE) && (GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE))
#endif
#else
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D0_CABLE_STATUS() == _TRUE))
#else
            if(GET_D0_CABLE_STATUS() == _TRUE)
#endif
#endif
            {
                // Restore Slave Address
                ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, g_ucTMDSSlaveAddr);

                // Restore Z0 Status
                ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), g_ucTMDSRx0Z0Status);
            }
            break;
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            // MHL mode of MHL_PORT can not pull HPD
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE) && (GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
            if((GET_D1_CABLE_STATUS() == _TRUE) && (GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE))
#endif
#else
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE))
#else
            if(GET_D1_CABLE_STATUS() == _TRUE)
#endif
#endif
            {
                // Restore Slave Address
                ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, g_ucTMDSSlaveAddr);

                // Restore Z0 Status
                ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), g_ucTMDSRx1Z0Status);
            }
            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            // MHL mode of MHL_PORT can not pull HPD
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D2_CABLE_STATUS() == _TRUE) && (GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
            if((GET_D2_CABLE_STATUS() == _TRUE) && (GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE))
#endif
#else
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D2_CABLE_STATUS() == _TRUE))
#else
            if(GET_D2_CABLE_STATUS() == _TRUE)
#endif
#endif
            {
                // Restore Slave Address
                ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, g_ucTMDSSlaveAddr);

                // Restore Z0 Status
                ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), g_ucTMDSRx2Z0Status);
            }
            break;
#endif

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
