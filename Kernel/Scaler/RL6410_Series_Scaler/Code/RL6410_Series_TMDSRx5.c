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
// ID Code      : RL6410_Series_TMDSRx5.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6410_SERIES_TMDSRX5__

#include "ScalerFunctionInclude.h"

#if(_D5_TMDS_SUPPORT == _ON)

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
StructTMDSCtrlInfo g_stTMDSRx5CtrlInfo;
WORD g_usTMDSRx5ClkCount;

BYTE g_pucTMDSRx5LEMax[3];
BYTE g_pucTMDSRx5Tap1Max[3];
BYTE g_ucTMDSRx5ClkIRQ;
BYTE g_ucTMDSRx5Z0Status;
BYTE g_ucTMDSRx5SlaveAddr;


#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
BYTE g_pucTMDSRx5LEMin[3];
BYTE g_pucTMDSRx5Tap0Min[3];
BYTE g_pucTMDSRx5Tap0Max[3];
BYTE g_ucTMDSRx5Tap0Init;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
BYTE g_ucTMDSRx5ClkMode = _TMDS_24BIT_PHY_SETTING;
#endif

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)))
BYTE g_pucTmdsRx5Caps[3];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTMDSRx5Initial(void);
void ScalerTMDSRx5InterruptInitial(void);
void ScalerTMDSRx5SetDFEInitial_EXINT0(void);
void ScalerTMDSRx5FLDBandFineTune_EXINT0(void);
void ScalerTMDSRx5SetPhy_EXINT0(void);
void ScalerTMDSRx5IntHandler_EXINT0(void);
void ScalerTMDSRx5PSIntHandler_EXINT0(void);
bit ScalerTMDSRx5CheckCDRStable(WORD usClkCount);
BYTE ScalerTMDSRx5CheckCDRStable_EXINT0(WORD usClkCount);
WORD ScalerTMDSRx5MeasureClk(BYTE ucMeasureClk);
WORD ScalerTMDSRx5MeasureClk_EXINT0(BYTE ucMeasureClk);

#if(_D5_HDMI_SUPPORT == _ON)
bit ScalerTMDSRx5HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth);
void ScalerTMDSRx5HdmiAVMuteProc(void);

#if(_D5_HDMI_2_0_SUPPORT == _ON)
void ScalerTMDSRx5ReadRequestProc_EXINT0(BYTE ucRROutCome);
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
void ScalerTMDSRx5HDMI2HPDRRIRQEnable(bit bEnable);
#endif
void ScalerTMDSRx5ReadRequestTimerEventEnable_WDINT(bit bEnable);
void ScalerTMDSRx5Hdmi2FormatResetEvent(void);
#endif

#endif

void ScalerTMDSRx5PowerSavingProc(void);
void ScalerTMDSRx5FreqDetectDisable(void);

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
BYTE ScalerTMDSRx5TMDSScanInputPort(BYTE ucInputType);
#endif

BYTE ScalerTMDSRx5FormatDetect(void);
bit ScalerTMDSRx5HdcpEnabled(void);
bit ScalerTMDSRx5CheckDataDFE(void);

bit ScalerTMDSRx5TMDSStableDetect(BYTE ucSourceType);
void ScalerTMDSRx5HotPlugEvent(void);
void ScalerTMDSRx5SwitchSlaveAddr(void);
void ScalerTMDSRx5BeforeHotPlugEventProc(void);
void ScalerTMDSRx5AfterHotPlugEventProc(void);
void ScalerTMDSRx5Hdcp1p4AksvClear(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initialize TMDS setting for search
// Input Value  : Current Search Port
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5Initial(void)
{
    // Disable TMDS output
    ScalerSetBit(P74_A6_TMDS_OUTCTL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // Set HS Width(DE only) and HDCP Reference VS
    ScalerSetBit(P74_AB_TMDS_ACC2, ~(_BIT7 | _BIT6), 0x00);

    // Set TMDS Hsync/Vsync Polarity as Input Raw Polarity
    ScalerSetBit(P74_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);

    // Disable C9/CA Port Auto-Inc
    ScalerSetBit(P74_C8_HDMI_APC, ~_BIT0, 0x00);

#if(_D5_HDMI_SUPPORT == _ON)

    ScalerTMDSRx5HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

    // Deep Color Mode clock and detection auto
    ScalerSetBit(P74_B8_TMDS_DPC1, ~(_BIT3 | _BIT2), _BIT2);

    // Enable BCH Detection
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_02_PORT_PAGE74_HDMI_BCHCR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT3 | _BIT2 | _BIT1));

    // DVI mode don't disable Audio Clk
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

    // Set Video Watch Dog New Mode
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_32_PORT_PAGE74_HDMI_WDCR1, ~_BIT5, _BIT5);

    // Specify Packet Detect Type
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_43_PORT_PAGE74_HDMI_PTRSV0, _HDMI_AVI_INFO_TYPE);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_44_PORT_PAGE74_HDMI_PTRSV1, _HDMI_GENERAL_CONTROL_TYPE);

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_A4_PORT_PAGE74_HDMI_PTRSV_2, _SPD_INFO_TYPE);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_A5_PORT_PAGE74_HDMI_PTRSV_3, _HDR_INFO_TYPE);
#endif

    // Packet Variation Detect Disable
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_45_PORT_PAGE74_HDMI_PVGCR0, 0x00);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_46_PORT_PAGE74_HDMI_PVGCR1, 0x00);
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_47_PORT_PAGE74_HDMI_PVGCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_A9_PORT_PAGE74_HDMI_PVSR_4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_AA_PORT_PAGE74_HDMI_PVGCR3, 0x00);
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_AB_PORT_PAGE74_HDMI_PVGCR4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

#if(_D5_HDMI_2_0_SUPPORT == _ON)

    if(ScalerGetBit(P74_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
    {
        // Disable HDMI 2.0 SCDC Function
        ScalerSetBit(P74_19_HDMI_CTRL_19, ~_BIT7, 0x00);
    }

    // Disable SCDC Scrambling Status
    ScalerSetDataPortBit(P74_39_HDMI_CTRL_39, _P74_3A_PT_21_PORT_PAGE74_HDMI_SCDC_21, ~_BIT0, 0x00);

    // Set Scrambling detection SSCP Number = 8, Enable HW Auto Detect Scrambling Control Symbol
    ScalerSetBit(P74_01_HDMI_CTRL_01, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1 | _BIT0));

    // Set SCDC Port not auto increase
    ScalerSetBit(P74_38_HDMI_CTRL_38, ~(_BIT4 | _BIT0), _BIT4);

    // Disable Ignore Source Transimit Read Request Enable
    ScalerSetBit(P74_1C_HDMI_CTRL_1C, ~_BIT2, 0x00);

    // Set Read Request 1ms reference clock to XTAL
    ScalerSetBit(P74_1A_HDMI_CTRL_1A, ~_BIT3, 0x00);

    // Set time interval form bus free to Read Request(4.7us~500us)
    ScalerSetBit(P74_1B_HDMI_CTRL_1B, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

    // Enable HDMI 2.0 Function
    ScalerSetBit(P74_00_HDMI_CTRL_00, ~_BIT0, _BIT0);

    // Enable HDMI 2.0 SCDC Module
    ScalerSetBit(P74_19_HDMI_CTRL_19, ~_BIT7, _BIT7);

#else

    // Disable HDMI 2.0 Function
    ScalerSetBit(P74_00_HDMI_CTRL_00, ~_BIT0, 0x00);

    // Disable HDMI 2.0 SCDC Function
    ScalerSetBit(P74_19_HDMI_CTRL_19, ~_BIT7, 0x00);

#endif

#endif // End of #if(_D5_HDMI_SUPPORT == _ON)

    // Set HDCP DDC Channel
    ScalerSetBit(P74_C2_HDCP_PCR, ~(_BIT2 | _BIT1), 0x00);

    // Set HDCP DDC Debounce, TMDS Function
    ScalerSetBit(P74_AC_TMDS_Z0CC2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Set D5 Port HDCP Address is 0x74
    ScalerSetDataPortBit(P74_C3_HDCP_AP, _P74_C4_PT_C2_PORT_PAGE74_HDCP_SLAVE_ADD, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3A);

    // Set HDCP Feature
#if(_D5_HDMI_SUPPORT == _ON)

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_0)
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x81);
#elif(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_1)
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x83);
#else
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x81);
#endif

#else // Else of #if(_D5_HDMI_SUPPORT == _ON)

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_0)
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x01);
#elif(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_1)
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x03);
#else
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x01);
#endif

#endif // End of #if(_D5_HDMI_SUPPORT == _ON)

    // Enable New Advance Cipher Mode
    ScalerSetBit(P74_C0_HDCP_CR, ~_BIT7, _BIT7);

    // Disable HDMI MAC Global Power Down
    ScalerSetBit(P74_AD_TMDS_CPS, ~_BIT1, 0x00);

    // Enable MAC Input
    ScalerSetBit(P74_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set MAC Signal Swap
    ScalerSetBit(P74_A7_TMDS_PWDCTL, ~(_BIT6 | _BIT5), ((_D5_TMDS_BR_SWAP << 6) | (_D5_TMDS_PN_SWAP << 5)));

    // Auto switch to DVI when no signal
    ScalerSetBit(P74_AD_TMDS_CPS, ~_BIT2, _BIT2);

    // Detect TMDS Format by Data Island Packet Preamble & Guard Band
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), _BIT1);

    // Enable TMDS MAC Error Correction
    ScalerSetBit(P74_B7_TMDS_UDC2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Enable MHL Mac and Set MHL MAC Signal Swap
        ScalerSetBit(P79_A0_MHL_CTRL_00, ~(_BIT5 | _BIT0), ((_D5_TMDS_PN_SWAP << 5) | _BIT0));

        // Enable New Algorithm for Packed Pixel Mode
        ScalerSetBit(P79_A1_MHL_CTRL_01, ~_BIT7, _BIT7);

        // Guard Band reference enable for data remapping
        ScalerSetBit(P79_B2_MHL_CTRL_12, ~_BIT7, _BIT7);

        // Set 24Bit Mode Threshold
        ScalerSetByte(P79_AA_MHL_CTRL_0A, 0x00);
        ScalerSetByte(P79_AB_MHL_CTRL_0B, 0x09);

        // Set PP Mode Threshold
        ScalerSetByte(P79_AC_MHL_CTRL_0C, 0x00);
        ScalerSetByte(P79_AD_MHL_CTRL_0D, 0x09);

        // Set Detection Period
        ScalerSetByte(P79_A8_MHL_CTRL_08, 0x69);
        ScalerSetByte(P79_A9_MHL_CTRL_09, 0x78);

        // Set Detection by Video Leading and Detection Period by Xtal
        ScalerSetBit(P79_A7_MHL_CTRL_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT0), _BIT2);
    }
    else
#endif
    {
        // Disable MHL Mac and Revert CDR Data Polarity
        ScalerSetBit(P79_A0_MHL_CTRL_00, ~(_BIT5 | _BIT0), 0x00);

        // Guard Band reference disable for data remapping
        ScalerSetBit(P79_B2_MHL_CTRL_12, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Initialize TMDS Interrupt Required Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5InterruptInitial(void)
{
    // Enable INT Clock Check
    g_ucTMDSRx5ClkIRQ = _ENABLE;

    if(ScalerGetBit(P74_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
    {
        CLR_TMDS_RX5_PHY_SET();
    }

    // Enable Rx_En for Clk pair Z0
    ScalerSetBit(P7E_1A_CMU_00, ~_BIT7, _BIT7);

    // Choose Measure Clk to TMDS Clk
    ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

    // Set Freq. Reference Counter = 2000
    ScalerSetBit(P74_F6_HDMI_FREQDET_BOUND_H, ~(_BIT1 | _BIT0), _BIT0);

    // Set Online Measure Input Clock Divider = /2 (No Matter if Input Clock >300Mhz or <=300Mhz)
    ScalerSetBit(P74_E7_HDMI_FREQDET_OFFSET, ~_BIT6, _BIT6);

    // Settings for IRQ set PHY
    // Consider using table to fill all required initial settings
    // Set pre-set threshold (225MHz * 0.01 / 26.8KHz = 0x54)

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Set TMDS Offset = 1/32
        ScalerSetBit(P74_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // Set Upper Bound
        ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
        ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
    }
    else
#endif
    {
        // Set TMDS Offset = 1/32
        ScalerSetBit(P74_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
        // Set Upper Bound
        ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
        ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
        ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
        ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
    }

    // Set Lower Bound
    ScalerSetByte(P74_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
    ScalerSetByte(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

    // Set Stable Time (0x3F = about 5ms)
    ScalerSetByte(P74_EC_HDMI_FREQDET_STABLE, 0x3F);

    // Disable Freq. Unstable IRQ
    ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

    // Enable Freq. Stable IRQ
    ScalerSetBit(P74_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Clear IRQ Pending Flag
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_60_PORT_PAGE74_HDMI_INTCR, ~_BIT7, _BIT7);

    // Internal IRQ Enable (Global)
    ScalerGlobalIRQControl(_ENABLE);

    EX0 = 1;

    // Start Freq. Detection
    ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : TMDS DFE Initial Setting (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5SetDFEInitial_EXINT0(void) using 1
{
    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [3] Disable Running Length Detection
    // [2] bypass Blank out Case-3 Symbol
    ScalerSetBit_EXINT(P7E_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7E_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7E_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

    if(ScalerGetBit_EXINT(P7E_1B_CMU_01, _BIT0) == _BIT0) // DCDR
    {
        if(GET_INPUT_PIXEL_CLK() <= 1000)
        {
            // [7:6] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop
            ScalerSetBit_EXINT(P7E_E0_MODE_TIMER, ~(_BIT7 | _BIT6), _BIT7);
        }
        else
        {
            // [7:6] adapt_mode[1:0] = 2'b11 --> Amplitude-based Adaptation without Independent LE Loop
            ScalerSetBit_EXINT(P7E_E0_MODE_TIMER, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
    }
    else  // ACDR
    {
        // [7:6] adapt_mode[1:0] = 2'b11 --> Amplitude-based Adaptation without Independent LE Loop
        ScalerSetBit_EXINT(P7E_E0_MODE_TIMER, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }

    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetBit_EXINT(P7E_E0_MODE_TIMER, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1));

    // Set DFE Delay Time
    // Turn On LE/Tap1~6 Simultaneously
    ScalerSetByte_EXINT(P7E_E1_TIMER, 0x01);

    // Tap0_Gain = 1/256, Tap1_Gain = 1/512
    ScalerSetBit_EXINT(P7E_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT2));

    // Tap2_Gain = 1/512; Tap3_Gain = 1/512
    ScalerSetBit_EXINT(P7E_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4_Gain = 1/512; Servo_Gain = 1/256
    ScalerSetBit_EXINT(P7E_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // LE_Gain1 = 1/256, LE_Gain2 = 0
    ScalerSetBit_EXINT(P7E_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit_EXINT(P7E_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap0 = 0~21
    // Vth_Threshold = 1
    ScalerSetByte_EXINT(P7E_E6_LIMIT_1, 0x35);

    if(ScalerGetBit_EXINT(P7E_1B_CMU_01, _BIT0) == _BIT0) // DCDR
    {
        // LE = 0~24
        if(GET_INPUT_PIXEL_CLK() <= 1000)
        {
            // Tap1 = 0~31 in Mode2
            ScalerSetBit_EXINT(P7E_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else
        {
            // Tap1 = 0~55 in Mode3
            ScalerSetBit_EXINT(P7E_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
        }
    }
    else   // ACDR
    {
        // Tap1 = 0~55 in Mode3
        ScalerSetBit_EXINT(P7E_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
    }

    // Tap2 Max is 10, Min is -6
    ScalerSetBit_EXINT(P7E_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT4));
    ScalerSetBit_EXINT(P7E_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P7E_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 0, Min is -3
    ScalerSetBit_EXINT(P7E_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7E_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 0, Min is -3
    ScalerSetBit_EXINT(P7E_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7E_EB_LIMIT_6, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P7E_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Tap0_Threshold = 10
    ScalerSetBit_EXINT(P7E_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // Vth_max = 6
    // Vth_min = 0
    ScalerSetByte_EXINT(P7E_F9_LIMIT_10, 0x60);

    // Set Vth/Tap Divider
    // Servo_Divider = 40
    // Vth_Divider = 15
    // Tap_Divider = 10
    ScalerSetByte_EXINT(P7E_EC_LOOP_DIV_1, 0xA3);
    ScalerSetByte_EXINT(P7E_ED_LOOP_DIV_2, 0xCA);

    // [5] servo_notrans = 1'b1 --> Transition Bits are not Effective in Servo
    // [4] tap0_notrans = 1'b1 --> Transition Bits are not Effective in Tap0
    ScalerSetBit_EXINT(P7E_F8_GRAY_DEC_2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [0] tap0_trans = 1'b0 --> Nontransition Bits are Effective in Tap0
    ScalerSetBit_EXINT(P7E_E3_GAIN_2, ~_BIT0, 0x00);

#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
    // over 3.4Gbps, data has scramble, use Run length = 4
    if(GET_INPUT_PIXEL_CLK() >= 3400)
    {
        // [1:0] trans_rlength = 2'b10 --> Tap0 Run Length = 4
        ScalerSetBit_EXINT(P7E_E4_GAIN_3, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // [1:0] trans_rlength = 2'b00 --> Tap0 Run Length = 2
        ScalerSetBit_EXINT(P7E_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);
    }
#else
    // [1:0] trans_rlength = 2'b00 --> Tap0 Run Length = 2
    ScalerSetBit_EXINT(P7E_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);
#endif

    // [1] tap1_trans = 1'b1 --> Nontransition Bits are not Effective in LE/Tap1
    ScalerSetBit_EXINT(P7E_E3_GAIN_2, ~_BIT1, _BIT1);

    // [1] De_inverse = 1'b0 --> Adapation Only for Blanking Area (Transition Maximum)
    // [0] De_brank_en = 1'b0 --> Disable Blank Function of gdi_de
    ScalerSetBit_EXINT(P7E_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7E_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7E_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Code Initialize //
    /////////////////////////

    // Initial DFE Code
    if(ScalerGetBit_EXINT(P7E_1B_CMU_01, _BIT0) == _BIT0) // DCDR
    {
        if(GET_INPUT_PIXEL_CLK() <= 375)
        {
            // LE Max = 24, Initial = 4
            ScalerSetByte_EXINT(P7E_A2_L0_LIMIT_INIT, 0x84);
            ScalerSetByte_EXINT(P7E_B2_L1_LIMIT_INIT, 0x84);
            ScalerSetByte_EXINT(P7E_C2_L2_LIMIT_INIT, 0x84);

            // Tap1 Initial Value = 0 for Mode1 DFE
            ScalerSetByte_EXINT(P7E_A5_L0_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7E_B5_L1_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7E_C5_L2_INIT_3, 0x00);
        }
        else if(GET_INPUT_PIXEL_CLK() <= 700)
        {
            // LE Max = 24, Initial = 6
            ScalerSetByte_EXINT(P7E_A2_L0_LIMIT_INIT, 0x86);
            ScalerSetByte_EXINT(P7E_B2_L1_LIMIT_INIT, 0x86);
            ScalerSetByte_EXINT(P7E_C2_L2_LIMIT_INIT, 0x86);

            // Tap1 Initial Value = 0 for Mode1 DFE
            ScalerSetByte_EXINT(P7E_A5_L0_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7E_B5_L1_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7E_C5_L2_INIT_3, 0x00);
        }
        else if(GET_INPUT_PIXEL_CLK() <= 1000)
        {
            // LE Max = 24, Initial = 10
            ScalerSetByte_EXINT(P7E_A2_L0_LIMIT_INIT, 0x8A);
            ScalerSetByte_EXINT(P7E_B2_L1_LIMIT_INIT, 0x8A);
            ScalerSetByte_EXINT(P7E_C2_L2_LIMIT_INIT, 0x8A);

            // Tap1 Initial Value = 0 for Mode1 DFE
            ScalerSetByte_EXINT(P7E_A5_L0_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7E_B5_L1_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7E_C5_L2_INIT_3, 0x00);
        }
        else
        {
            // LE Max = 24, Initial = 12
            ScalerSetByte_EXINT(P7E_A2_L0_LIMIT_INIT, 0x8C);
            ScalerSetByte_EXINT(P7E_B2_L1_LIMIT_INIT, 0x8C);
            ScalerSetByte_EXINT(P7E_C2_L2_LIMIT_INIT, 0x8C);

            // Tap1 Initial Value = 12 for Mode3 DFE
            ScalerSetByte_EXINT(P7E_A5_L0_INIT_3, 0x0C);
            ScalerSetByte_EXINT(P7E_B5_L1_INIT_3, 0x0C);
            ScalerSetByte_EXINT(P7E_C5_L2_INIT_3, 0x0C);
        }
    }
    else    // ACDR
    {
        // LE Max = 21, Initial = 12
        ScalerSetByte_EXINT(P7E_A2_L0_LIMIT_INIT, 0x5C);
        ScalerSetByte_EXINT(P7E_B2_L1_LIMIT_INIT, 0x5C);
        ScalerSetByte_EXINT(P7E_C2_L2_LIMIT_INIT, 0x5C);

        // Tap1 Initial Value = 15 for Mode3 DFE
        ScalerSetByte_EXINT(P7E_A5_L0_INIT_3, 0x0F);
        ScalerSetByte_EXINT(P7E_B5_L1_INIT_3, 0x0F);
        ScalerSetByte_EXINT(P7E_C5_L2_INIT_3, 0x0F);
    }

    ScalerSetByte_EXINT(P7E_A3_L0_INIT_1, 0x90);
    ScalerSetByte_EXINT(P7E_B3_L1_INIT_1, 0x90);
    ScalerSetByte_EXINT(P7E_C3_L2_INIT_1, 0x90);

    ScalerSetByte_EXINT(P7E_A4_L0_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P7E_B4_L1_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P7E_C4_L2_INIT_2, 0x0F);

#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
    g_ucTMDSRx5Tap0Init = ScalerGetByte_EXINT(P7E_A4_L0_INIT_2);
#endif

    ScalerSetByte_EXINT(P7E_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7E_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7E_C6_L2_INIT_4, 0x00);

    ScalerSetByte_EXINT(P7E_A7_L0_INIT_5, 0x00);
    ScalerSetByte_EXINT(P7E_B7_L1_INIT_5, 0x00);
    ScalerSetByte_EXINT(P7E_C7_L2_INIT_5, 0x00);

    ScalerSetByte_EXINT(P7E_A8_L0_INIT_6, 0x00);
    ScalerSetByte_EXINT(P7E_B8_L1_INIT_6, 0x00);
    ScalerSetByte_EXINT(P7E_C8_L2_INIT_6, 0x00);

    ScalerSetByte_EXINT(P7E_A9_L0_INIT_7, 0x04);
    ScalerSetByte_EXINT(P7E_B9_L1_INIT_7, 0x04);
    ScalerSetByte_EXINT(P7E_C9_L2_INIT_7, 0x04);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P7E_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7E_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7E_CA_L2_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P7E_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7E_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7E_CA_L2_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P7E_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7E_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0x00);
}
//--------------------------------------------------
// Description  : TMDS FLD Band Fine Tune  (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5FLDBandFineTune_EXINT0(void) using 1
{
    WORD pusLaneFreq[3];
    BYTE ucCount = 0;
    BYTE ucLaneCount = 0;
    BYTE pucBestVCOBand[3];
    BYTE pucAutoVCOBand[3];
    BYTE ucBacksetting2 = 0;

    pusLaneFreq[0] = 0;
    pusLaneFreq[1] = 0;
    pusLaneFreq[2] = 0;

    // Get 3 Lane Auto Result
    pucAutoVCOBand[0] = (ScalerGetByte_EXINT(P7E_35_ANA_CDR_11) & 0x7F);
    pucAutoVCOBand[1] = (ScalerGetByte_EXINT(P7E_36_ANA_CDR_12) & 0x7F);
    pucAutoVCOBand[2] = (ScalerGetByte_EXINT(P7E_37_ANA_CDR_13) & 0x7F);

    // Scan Lane
    ScalerSetBit_EXINT(P7E_32_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pucAutoVCOBand[0]);
    ScalerSetBit_EXINT(P7E_33_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pucAutoVCOBand[1]);
    ScalerSetBit_EXINT(P7E_34_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pucAutoVCOBand[2]);

    ucBacksetting2 = ScalerGetByte_EXINT(P74_EC_HDMI_FREQDET_STABLE);

    // Set Open Loop
    ScalerSetBit_EXINT(P7E_2B_ANA_CDR_01, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // Change Measure Count  64=>3
    ScalerSetBit_EXINT(P74_EC_HDMI_FREQDET_STABLE, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

    for(ucLaneCount = 0; ucLaneCount < 3; ucLaneCount++)
    {
        // Read Lane0 Result
        ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT5 | _BIT4), ((ucLaneCount + 1) << 4));
        ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

        // Waiting For Measure Done -> 300us
        for(ucCount = 0; ucCount <= 60; ucCount++)
        {
            DELAY_5US_EXINT();

            if(ScalerGetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, _BIT6) == _BIT6)
            {
                // POP Result
                ScalerSetBit_EXINT(P74_EC_HDMI_FREQDET_STABLE, ~_BIT7, _BIT7);

                pusLaneFreq[ucLaneCount] = ((DWORD)((WORD)(ScalerGetByte_EXINT(P74_ED_HDMI_FREQDET_RESULT_M) << 8) | ScalerGetByte_EXINT(P74_EE_HDMI_FREQDET_RESULT_L))*27 / 100);
                break;
            }
        }
    }

    // For 3 Lane Cal Best Band
    for(ucLaneCount = 0; ucLaneCount < 3; ucLaneCount++)
    {
        if(pusLaneFreq[ucLaneCount] < GET_INPUT_PIXEL_CLK())
        {
            pucBestVCOBand[ucLaneCount] = pucAutoVCOBand[ucLaneCount] + 1;
        }
        else
        {
            pucBestVCOBand[ucLaneCount] = pucAutoVCOBand[ucLaneCount];
        }
    }

    // Reload Best Band
    ScalerSetBit_EXINT(P7E_32_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pucBestVCOBand[0]);
    ScalerSetBit_EXINT(P7E_33_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pucBestVCOBand[1]);
    ScalerSetBit_EXINT(P7E_34_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pucBestVCOBand[2]);

    // Reload Measure TMDS Clock & Clear Unsatble IRQ Flag & Dummy POP Out
    ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT7), 0x00);
    ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT7), _BIT7);
    for(ucCount = 0; ucCount <= 60; ucCount++)
    {
        DELAY_5US_EXINT();
        if(ScalerGetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, _BIT6) == _BIT6)
        {
            // POP result
            ScalerSetBit_EXINT(P74_EC_HDMI_FREQDET_STABLE, ~_BIT7, _BIT7);
            break;
        }
    }

    // Set Stable Count
    ScalerSetByte_EXINT(P74_EC_HDMI_FREQDET_STABLE, ucBacksetting2);

    // Clear Unstable IRQ Flag
    ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);
}
//--------------------------------------------------
// Description  : TMDS Set PHY Function (EXINT0 Only)
// Input Value  : Measured Clk Count for PHY Setting
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5SetPhy_EXINT0(void) using 1
{
    BYTE ucIcp = 0;


    //////////////
    // CDR Mode //
    //////////////

    if(GET_INPUT_PIXEL_CLK() <= 2000)  // DCDR
    {
        // [3:0] reg_en_ana_cdr = 4'b0000 --> Disable Analog CDR
        ScalerSetBit_EXINT(P7E_2A_ANA_CDR_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // [0] En_APLL_Lane2 = 1'b1 --> Enable Lane2 VCO as CMU
        ScalerSetBit_EXINT(P7E_1B_CMU_01, ~_BIT0, _BIT0);

        if((GET_INPUT_PIXEL_CLK() <= 1000) && (ScalerGetBit_EXINT(P7E_17_BANDGAP_03, _BIT1) == _BIT1))  // MHL mode
        {
            // [6:5] CMU_REFCK_SEL = 2'b10 --> Ref. TMDS Clock w/ Hysteresis OP
            ScalerSetBit_EXINT(P7E_1B_CMU_01, ~(_BIT6 | _BIT5), _BIT6);
        }
        else
        {
            // [6:5] CMU_REFCK_SEL = 2'b00 --> Ref. TMDS Clock w/o Hysteresis OP
            ScalerSetBit_EXINT(P7E_1B_CMU_01, ~(_BIT6 | _BIT5), 0x00);
        }
    }
    else  // ACDR
    {
        // [3:0] reg_en_ana_cdr = 4'b0111 --> Enable Lane0~2 Analog CDR
        ScalerSetBit_EXINT(P7E_2A_ANA_CDR_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // [0] En_APLL_Lane2 = 1'b0 --> Disable Lane2 VCO as CMU
        ScalerSetBit_EXINT(P7E_1B_CMU_01, ~_BIT0, 0x00);
    }

    ///////////////
    // RX CMU EN //
    ///////////////

    // [7] cmu_en = 0 --> Disable CMU PLL
    ScalerSetBit_EXINT(P7E_1B_CMU_01, ~_BIT7, 0x00);

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
    // [3:0] cdr_en = 4'b0000 --> Disable CDREN
    ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT3, 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT2, 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT1, 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT0, 0x00);

    if(ScalerGetBit_EXINT(P7E_17_BANDGAP_03, _BIT1) == _BIT1)  // MHL Mode
    {
        if(ScalerGetBit_EXINT(P7E_1B_CMU_01, _BIT0) == _BIT0) // DCDR
        {
            // [7:4] rx_en = 4'b1101 --> Enable RXEN for Lane0, 2, 3
            // [3:0] cdr_en = 4'b0101 --> Enable CDREX for Lane0, 2
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT7, _BIT7);
            DELAY_5US_EXINT();
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT6, _BIT6);
            DELAY_5US_EXINT();
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT5, 0x00);
            DELAY_5US_EXINT();
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT4, _BIT4);
            DELAY_5US_EXINT();
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT2, _BIT2);
            DELAY_5US_EXINT();
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT0, _BIT0);
        }
        else
        {
            // [7:4] rx_en = 4'b1001 --> Enable RXEN for Lane0, 3
            // [3:0] cdr_en = 4'b0001 --> Enable CDREX for Lane0
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT7, _BIT7);
            DELAY_5US_EXINT();
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT6, 0x00);
            DELAY_5US_EXINT();
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT5, 0x00);
            DELAY_5US_EXINT();
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT4, _BIT4);
            DELAY_5US_EXINT();
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT0, _BIT0);
        }
    }
    else
    {
        // [7:4] rx_en = 4'b1111 --> Enable RXEN
        // [3:0] cdr_en = 4'b0001 ~ 4'b0011 ~ 4'b0111
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT7, _BIT7);
        DELAY_5US_EXINT();
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT6, _BIT6);
        DELAY_5US_EXINT();
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT5, _BIT5);
        DELAY_5US_EXINT();
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT4, _BIT4);
        DELAY_5US_EXINT();
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT2, _BIT2);
        DELAY_5US_EXINT();
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT1, _BIT1);
        DELAY_5US_EXINT();
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT0, _BIT0);
    }
#else
    // [3:0] cdr_en = 4'b0000 --> Disable CDREN
    ScalerSetBit_EXINT(P7E_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    if(ScalerGetBit_EXINT(P7E_17_BANDGAP_03, _BIT1) == _BIT1)  // MHL Mode
    {
        if(ScalerGetBit_EXINT(P7E_1B_CMU_01, _BIT0) == _BIT0) // DCDR
        {
            // [7:4] rx_en = 4'b1101 --> Enable RXEN for Lane0, 2, 3
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT4));

            // [3:0] cdr_en = 4'b0101 --> Enable CDREX for Lane0, 2
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        }
        else
        {
            // [7:4] rx_en = 4'b1001 --> Enable RXEN for Lane0, 3
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));

            // [3:0] cdr_en = 4'b0001 --> Enable CDREX for Lane0
            ScalerSetBit_EXINT(P7E_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        }
    }
    else
    {
        // [7:4] rx_en = 4'b1111 --> Enable RXEN
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // [3:0] cdr_en = 4'b0001 ~ 4'b0011 ~ 4'b0111
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    }
#endif


    //////////////////////
    // A/DCDR  Setting  //
    //////////////////////

    // [1:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 700M/v
    ScalerSetBit_EXINT(P7E_2C_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);

    // [4] reg_sel_cont3 = 1'b1 --> BBPD UP/DN Pulse Div 3
    ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~_BIT4, _BIT4);

    // [7] en_fld_ref_ecbuss = 0 --> FLD Reference Lane3 Clock
    ScalerSetBit_EXINT(P7E_28_KOFFSET_04, ~_BIT7, 0x00);

    if(ScalerGetBit_EXINT(P7E_1B_CMU_01, _BIT0) == _BIT0) // DCDR
    {
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        if(ScalerGetBit_EXINT(P7E_17_BANDGAP_03, _BIT1) == _BIT1)  // MHL Mode
        {
            // [5:4] reg_cmu_sel_cp = 2'b10 --> Analog CDR Cp = 2pF
            // [3] reg_en_largers_forcmu = 1'b1 --> Analog CDR Rs Increase 8K
            // [2:0] reg_cmu_sel_Rs = 3'b011 --> Analog CDR Rs = 12K + 8K
            ScalerSetBit_EXINT(P7E_1E_CMU_04, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT1 | _BIT0));

            // [3:0] reg_cdr_cp_in = 4'b1010 --> Analog CDR Icp = 31.5uA
            ScalerSetBit_EXINT(P7E_31_ANA_CDR_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
        }
        else   // HDMI Mode
#endif
        {
            // [5:4] reg_cmu_sel_cp = 2'b10 --> Analog CDR Cp = 2pF
            // [3] reg_en_largers_forcmu = 1'b1 --> Analog CDR Rs Increase 8K
            // [2:0] reg_cmu_sel_Rs = 3'b110 --> Analog CDR Rs = 16K + 8K
            ScalerSetBit_EXINT(P7E_1E_CMU_04, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT2 | _BIT1));

            // [3:0] reg_cdr_cp_in = 4'b1100 --> Analog CDR Icp = 37.5uA
            ScalerSetBit_EXINT(P7E_31_ANA_CDR_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        }
    }
    else
    {
        // [5:4] reg_cmu_sel_cp = 2'b00 --> Analog CDR Cp = 0pF
        // [3] reg_en_largers_forcmu = 1'b0 --> Analog CDR Rs Increase 0K
        ScalerSetBit_EXINT(P7E_1E_CMU_04, ~(_BIT5 | _BIT4 | _BIT3), 0x00);

        if(GET_INPUT_PIXEL_CLK() <= 3000)
        {
            // [6:4] reg_sel_cdr_res = 3'b101 --> Analog CDR Rs = 6K
            // [3:0] reg_cdr_cp_in = 4'b0101 --> Analog CDR Icp = 16.5uA
            ScalerSetBit_EXINT(P7E_31_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
        }
        else
        {
            // [6:4] reg_sel_cdr_res = 3'b011 --> Analog CDR Rs = 2K
            // [3:0] reg_cdr_cp_in = 4'b0011 --> Analog CDR Icp = 10.5uA
            ScalerSetBit_EXINT(P7E_31_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
        }
    }

    ucIcp = (ScalerGetByte_EXINT(P7E_31_ANA_CDR_07) & 0x0F);

    // [7:5] KD = 3'b000 --> KD = 0
    ScalerSetBit_EXINT(P7E_4F_KD, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(ScalerGetBit_EXINT(P7E_17_BANDGAP_03, _BIT1) == _BIT1)  // MHL Mode
    {
        // KI = 3'b001 --> KI = 1/16
        ScalerSetBit_EXINT(P7E_50_KI_L0, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

        if(GET_INPUT_PIXEL_CLK() <= 1000)
        {
            // KP = 0x23 --> KP = 8.75
            ScalerSetByte_EXINT(P7E_53_KP_L0, 0x23);
        }
        else
        {
            // KP = 0x2F --> KP = 11.75
            ScalerSetByte_EXINT(P7E_53_KP_L0, 0x2F);
        }
    }
    else   // HDMI Mode
#endif
    {
        // KI = 3'b000 --> KI = 0
        ScalerSetBit_EXINT(P7E_50_KI_L0, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7E_51_KI_L1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7E_52_KI_L2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        if(GET_INPUT_PIXEL_CLK() < 1500)
        {
            // KP = 0x20 --> KP = 8
            ScalerSetByte_EXINT(P7E_53_KP_L0, 0x20);
            ScalerSetByte_EXINT(P7E_54_KP_L1, 0x20);
            ScalerSetByte_EXINT(P7E_55_KP_L2, 0x20);
        }
        else
        {
            // KP = 0x0F --> KP = 3.75
            ScalerSetByte_EXINT(P7E_53_KP_L0, 0x0F);
            ScalerSetByte_EXINT(P7E_54_KP_L1, 0x0F);
            ScalerSetByte_EXINT(P7E_55_KP_L2, 0x0F);
        }
    }

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(ScalerGetBit_EXINT(P7E_17_BANDGAP_03, _BIT1) == _BIT1)  // MHL Mode
    {
        // Check if Packed Pixel Mode
        if(GET_TMDS_RX5_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            if(GET_INPUT_PIXEL_CLK() <= 1500)
            {
                // Analog CDR Auto FLD Counter
                // ref_conuter = 30
                // cdr_counter = 480
                // 30/480 = 1/16 = 5*(1/80 clock rate)
                ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~(_BIT1 | _BIT0), _BIT0);
                ScalerSetByte_EXINT(P7E_2E_ANA_CDR_04, 0x1D);
                ScalerSetByte_EXINT(P7E_2F_ANA_CDR_05, 0xDF);

                // [5:4] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetBit_EXINT(P7E_1F_CMU_05, ~(_BIT5 | _BIT4), 0x00);

                // [7:0] N_CODE = 8'b0100 1100 --> 76 + 4 = 80
                ScalerSetByte_EXINT(P7E_20_CMU_06, 0x4C);

                // [2:0] SEL_DIV = 3'b010 --> 750MHz ~ 1500MHz
                ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                // [6:4] rate_sel = 3'b010 --> 750MHz ~ 1500MHz
                ScalerSetBit_EXINT(P7E_3E_EN_01, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
            }
            else
            {
                // Analog CDR Auto FLD Counter
                // ref_conuter = 50
                // cdr_counter = 400
                // 50/400 = 1/8 = 5*(1/40 clock rate)
                ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~(_BIT1 | _BIT0), _BIT0);
                ScalerSetByte_EXINT(P7E_2E_ANA_CDR_04, 0x31);
                ScalerSetByte_EXINT(P7E_2F_ANA_CDR_05, 0x8F);

                // [5:4] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetBit_EXINT(P7E_1F_CMU_05, ~(_BIT5 | _BIT4), 0x00);

                // [7:0] N_CODE = 8'b0010 0100 --> 36 + 4 = 40
                ScalerSetByte_EXINT(P7E_20_CMU_06, 0x24);

                // [2:0] rate_sel = 3'b001 --> 1500MHz ~ 3000MHz
                ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                // [6:4] SEL_DIV = 3'b001 --> 1500MHz ~ 3000MHz
                ScalerSetBit_EXINT(P7E_3E_EN_01, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
            }
        }
        else  // MHL 24bit Mode
        {
            if(GET_INPUT_PIXEL_CLK() <= 750)
            {
                // Analog CDR Auto FLD Counter
                // ref_conuter = 20
                // cdr_counter = 480
                // 20/480 = 1/24 = 5*(1/120 clock rate)
                ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~(_BIT1 | _BIT0), _BIT0);
                ScalerSetByte_EXINT(P7E_2E_ANA_CDR_04, 0x13);
                ScalerSetByte_EXINT(P7E_2F_ANA_CDR_05, 0xDF);

                // [5:4] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetBit_EXINT(P7E_1F_CMU_05, ~(_BIT5 | _BIT4), 0x00);

                // [7:0] N_CODE = 8'b0111 0100 --> 116 + 4 = 120
                ScalerSetByte_EXINT(P7E_20_CMU_06, 0x74);

                // [2:0] SEL_DIV = 3'b011 --> 375MHz ~ 750MHz
                ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                // [6:4] rate_sel = 3'b011 --> 375MHz ~ 750MHz
                ScalerSetBit_EXINT(P7E_3E_EN_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
            }
            else if(GET_INPUT_PIXEL_CLK() <= 1500)
            {
                // Analog CDR Auto FLD Counter
                // ref_conuter = 40
                // cdr_counter = 480
                // 40/480 = 1/12 = 5*(1/60 clock rate)
                ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~(_BIT1 | _BIT0), _BIT0);
                ScalerSetByte_EXINT(P7E_2E_ANA_CDR_04, 0x27);
                ScalerSetByte_EXINT(P7E_2F_ANA_CDR_05, 0xDF);

                // [5:4] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetBit_EXINT(P7E_1F_CMU_05, ~(_BIT5 | _BIT4), 0x00);

                // [7:0] N_CODE = 8'b0011 1000 --> 56 + 4 = 60
                ScalerSetByte_EXINT(P7E_20_CMU_06, 0x38);

                // [2:0] SEL_DIV = 3'b010 --> 750MHz ~ 1500MHz
                ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                // [6:4] rate_sel = 3'b010 --> 750MHz ~ 1500MHz
                ScalerSetBit_EXINT(P7E_3E_EN_01, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
            }
            else if(GET_INPUT_PIXEL_CLK() <= 3000)
            {
                // Analog CDR Auto FLD Counter
                // ref_conuter = 80
                // cdr_counter = 480
                // 80/480 = 1/6 = 5*(1/30 clock rate)
                ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~(_BIT1 | _BIT0), _BIT0);
                ScalerSetByte_EXINT(P7E_2E_ANA_CDR_04, 0x4F);
                ScalerSetByte_EXINT(P7E_2F_ANA_CDR_05, 0xDF);

                // [5:4] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetBit_EXINT(P7E_1F_CMU_05, ~(_BIT5 | _BIT4), 0x00);

                // [7:0] N_CODE = 8'b0001 1010 --> 26 + 4 = 30
                ScalerSetByte_EXINT(P7E_20_CMU_06, 0x1A);

                // [2:0] SEL_DIV = 3'b001 --> 1500MHz ~ 3000MHz
                ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                // [6:4] rate_sel = 3'b001 --> 1500MHz ~ 3000MHz
                ScalerSetBit_EXINT(P7E_3E_EN_01, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
            }
            else
            {
                // Analog CDR Auto FLD Counter
                // ref_conuter = 160
                // cdr_counter = 480
                // 160/480 = 1/3 = 5*(1/15 clock rate)
                ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~(_BIT1 | _BIT0), _BIT0);
                ScalerSetByte_EXINT(P7E_2E_ANA_CDR_04, 0x9F);
                ScalerSetByte_EXINT(P7E_2F_ANA_CDR_05, 0xDF);

                // [5:4] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetBit_EXINT(P7E_1F_CMU_05, ~(_BIT5 | _BIT4), 0x00);

                // [7:0] N_CODE = 8'b0000 1101 --> 11 + 4 = 30
                ScalerSetByte_EXINT(P7E_20_CMU_06, 0x0B);

                // [2:0] SEL_DIV = 3'b000 --> 3000MHz ~ 6000MHz
                ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                // [6:4] rate_sel = 3'b000 --> 3000MHz ~ 6000MHz
                ScalerSetBit_EXINT(P7E_3E_EN_01, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            }
        }
    }
    else     // HDMI Mode
#endif
    {
        if(GET_INPUT_PIXEL_CLK() <= 375)
        {
            // Analog CDR Auto FLD Counter
            // ref_conuter = 30
            // cdr_counter = 480
            // 30/480 = 1/16 = 5*(1/80 clock rate)
            ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(P7E_2E_ANA_CDR_04, 0x1D);
            ScalerSetByte_EXINT(P7E_2F_ANA_CDR_05, 0xDF);

            // [5:4] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetBit_EXINT(P7E_1F_CMU_05, ~(_BIT5 | _BIT4), 0x00);

            // [7:0] N_CODE = 8'b0100 1100 --> 76 + 4 = 80
            ScalerSetByte_EXINT(P7E_20_CMU_06, 0x4C);

            // [2:0] SEL_DIV = 3'b100 --> 187.5MHz ~ 375MHz
            ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

            // [6:4] rate_sel = 3'b100 --> 187.5MHz ~ 375MHz
            ScalerSetBit_EXINT(P7E_3E_EN_01, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
        }
        else if(GET_INPUT_PIXEL_CLK() <= 750)
        {
            // Analog CDR Auto FLD Counter
            // ref_conuter = 50
            // cdr_counter = 400
            // 50/400 = 1/8 = 5*(1/40 clock rate)
            ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(P7E_2E_ANA_CDR_04, 0x31);
            ScalerSetByte_EXINT(P7E_2F_ANA_CDR_05, 0x8F);

            // [5:4] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetBit_EXINT(P7E_1F_CMU_05, ~(_BIT5 | _BIT4), 0x00);

            // [7:0] N_CODE = 8'b0010 0100 --> 36 + 4 = 40
            ScalerSetByte_EXINT(P7E_20_CMU_06, 0x24);

            // [2:0] SEL_DIV = 3'b011 --> 375MHz ~ 750MHz
            ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // [6:4] rate_sel = 3'b011 --> 375MHz ~ 750MHz
            ScalerSetBit_EXINT(P7E_3E_EN_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
        }
        else if(GET_INPUT_PIXEL_CLK() <= 1500)
        {
            // Analog CDR Auto FLD Counter
            // ref_conuter = 125
            // cdr_counter = 500
            // 125/500 = 1/4 = 5*(1/20 clock rate)
            ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(P7E_2E_ANA_CDR_04, 0x7C);
            ScalerSetByte_EXINT(P7E_2F_ANA_CDR_05, 0xF3);

            // [5:4] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetBit_EXINT(P7E_1F_CMU_05, ~(_BIT5 | _BIT4), 0x00);

            // [7:0] N_CODE = 8'b0001 0000 --> 16 + 4 = 20
            ScalerSetByte_EXINT(P7E_20_CMU_06, 0x10);

            // [2:0] SEL_DIV = 3'b010 --> 750MHz ~ 1500MHz
            ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            // [6:4] rate_sel = 3'b010 --> 750MHz ~ 1500MHz
            ScalerSetBit_EXINT(P7E_3E_EN_01, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
        }
        else if(GET_INPUT_PIXEL_CLK() <= 3000)
        {
            // Analog CDR Auto FLD Counter
            // ref_conuter = 250
            // cdr_counter = 500
            // 250/500 = 1/2 = 5*(1/10 clock rate)
            ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(P7E_2E_ANA_CDR_04, 0xF9);
            ScalerSetByte_EXINT(P7E_2F_ANA_CDR_05, 0xF3);

            // [5:4] CMU_SELPREDIV = 2'b00 --> /2
            ScalerSetBit_EXINT(P7E_1F_CMU_05, ~(_BIT5 | _BIT4), _BIT4);

            // [7:0] N_CODE = 8'b0001 0000 --> 16 + 4 = 20
            ScalerSetByte_EXINT(P7E_20_CMU_06, 0x10);

            // [2:0] SEL_DIV = 3'b001 --> 1500MHz ~ 3000MHz
            ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            // [6:4] rate_sel = 3'b001 --> 1500MHz ~ 3000MHz
            ScalerSetBit_EXINT(P7E_3E_EN_01, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
        }
        else     // ACDR 1:10
        {
            // Analog CDR Auto FLD Counter
            // ref_conuter = 500
            // cdr_counter = 500
            // 500/500 = 1/1 = 5*(1/5 clock rate)
            ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte_EXINT(P7E_2E_ANA_CDR_04, 0xF3);
            ScalerSetByte_EXINT(P7E_2F_ANA_CDR_05, 0xF3);

            // [2:0] rate_sel = 3'b000 --> 3000MHz ~ 6000MHz
            ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // [6:4] SEL_DIV = 3'b000 --> 3000MHz ~ 6000MHz
            ScalerSetBit_EXINT(P7E_3E_EN_01, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        }
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [0] en_clkout_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(P7E_0E_SDM_03, ~_BIT0, 0x00);

    // [0] en_eqen_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(P7E_10_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 0 --> Disable Dataout
    ScalerSetBit_EXINT(P7E_11_DATA_TIMER, ~_BIT0, 0x00);

    // [4] reg_acdr_l0_en = 1'b0 --> Disable Lane0 ACDR_DFE
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit_EXINT(P7E_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // [6:4] RST_N = 3'b000 = 3'b111 -> Digital Circuit Reset Toggle
    // [2:0] Disable DCDR
    ScalerSetBit_EXINT(P7E_38_TMDS_RESET, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7E_38_TMDS_RESET, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4));


    /////////////////
    // DFE Setting //
    /////////////////

    // Load DFE Initial Code
    ScalerTMDSRx5SetDFEInitial_EXINT0();

    // Enable Tap0~4
    ScalerSetBit_EXINT(P7E_21_CMU_07, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

    if(GET_INPUT_PIXEL_CLK() <= 2500)
    {
        // [3:1] LE_lowgain_highboost = 111 --> LE HighBoost Mode
        ScalerSetBit_EXINT(P7E_22_CMU_08, ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2 | _BIT1));
    }
    else
    {
        // [3:1] LE_lowgain_highboost = 100 --> LE HighBoost Mode
        ScalerSetBit_EXINT(P7E_22_CMU_08, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
    }

    if(GET_INPUT_PIXEL_CLK() <= 2000)
    {
        // [7] SEL_DFE_DELAY = 1'b1 --> Increase DFE Delay
        ScalerSetBit_EXINT(P7E_22_CMU_08, ~_BIT7, _BIT7);
    }
    else
    {
        // [7] SEL_DFE_DELAY = 1'b0 --> Normal DFE Delay
        ScalerSetBit_EXINT(P7E_22_CMU_08, ~_BIT7, 0x00);
    }

    if(GET_INPUT_PIXEL_CLK() <= 2500)
    {
        // [7:5] LE_RLSEL = 3'b011
        // [4:2] LE_ISEL = 3'b000
        ScalerSetBit_EXINT(P7E_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    }
    else
    {
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
        if(GET_INPUT_PIXEL_CLK() <= 3400)
        {
            // [7:5] LE_RLSEL = 3'b001
            // [4:2] LE_ISEL = 3'b010
            ScalerSetBit_EXINT(P7E_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));
        }
        else
        {
            // [7:5] LE_RLSEL = 3'b000
            // [4:2] LE_ISEL = 3'b011
            ScalerSetBit_EXINT(P7E_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
        }
#else
        // [7:5] LE_RLSEL = 3'b001
        // [4:2] LE_ISEL = 3'b010
        ScalerSetBit_EXINT(P7E_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));
#endif
    }


    ////////////////////
    // First K Offset //
    ////////////////////

    // Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(P7E_1D_CMU_03, ~_BIT4, 0x00);

    // [5] Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT5, _BIT5);

    // [6] Toggle Foreground Calibration
    ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT6, 0x00);
    ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT6, _BIT6);

    // Waiting for K Offset
    DELAY_XUS_EXINT(50);


    ///////////////////////////////////
    // FLD Lock Band & DFE Adaptation//
    ///////////////////////////////////

    // [7] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
    // [6] reg_adp_en_manual = 1'b0 --> Disable adp_en_manual
    // [5] reg_cp_en_manual = 1'b0 -->  Disable cp_en_manual
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [3] xtal_en = 0 --> FLD Reference Input Clock
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(P7E_2B_ANA_CDR_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0), (_BIT7 | _BIT0));

    // [5] en_wide_temp = 1'b1 --> Enable Wide Temp VCO Band
    ScalerSetBit_EXINT(P7E_2D_ANA_CDR_03, ~_BIT5, _BIT5);

    // [3:2] en_vcm_tune = 2'b11 --> Vc = Vdd/2
    ScalerSetBit_EXINT(P7E_2C_ANA_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    if(ScalerGetBit_EXINT(P7E_1B_CMU_01, _BIT0) == _BIT0) // DCDR
    {
        // [7] reg_rstb_fsm --> Toggle for FLD reset
        ScalerSetBit_EXINT(P7E_2A_ANA_CDR_00, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(P7E_2A_ANA_CDR_00, ~_BIT7, _BIT7);

        // Waiting for FLD Lock Band
        DELAY_XUS_EXINT(360);

        // [7] cmu_en = 1'b1 --> Enable CMU PLL
        ScalerSetBit_EXINT(P7E_1B_CMU_01, ~_BIT7, _BIT7);

        // Enable Digital CDR
        ScalerSetByte_EXINT(P7E_38_TMDS_RESET, 0xFF);

        // Waiting for CMU Stable
        DELAY_XUS_EXINT(150);

        // [0] en_clkout_manual = 1 --> Enable Clkout
        ScalerSetBit_EXINT(P7E_0E_SDM_03, ~_BIT0, _BIT0);

        // [0] en_eqen_manual = 1 --> Enable Adaptation
        ScalerSetBit_EXINT(P7E_10_EQEN_TIMER, ~_BIT0, _BIT0);

        if(GET_INPUT_PIXEL_CLK() <= 375) // TMDS Clock < 375
        {
            // Disable Adaptation Loop  0x000
            ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0x00);
        }
        else if(GET_INPUT_PIXEL_CLK() <= 1000)// 375~1000
        {
            // Enable the Vth, Tap0~1 Adaptation Loop 0x043
            ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x43);
            ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0x43);
            ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0x43);
        }
        else
        {
            // Enable the LE, Vth, Tap0~1 Adaptation Loop 0x0C3
            ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0xC3);
            ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0xC3);
            ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0xC3);
        }

        // Waiting for the Adaptation
        DELAY_XUS_EXINT(290);
    }
    else
    {
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
        if(GET_INPUT_PIXEL_CLK() <= 3400) // 2000~3400 Analog CDR
        {
            // [7] cmu_en = 1'b1 --> Enable CMU PLL
            ScalerSetBit_EXINT(P7E_1B_CMU_01, ~_BIT7, _BIT7);

            // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
            // [1] reg_en_eqen_manual_l0 = 1'b1
            ScalerSetBit_EXINT(P7E_12_ANA_CDR, ~(_BIT4 | _BIT1), (_BIT4 | _BIT1));

            // [7] reg_rstb_fsm --> Toggle for FLD reset
            ScalerSetBit_EXINT(P7E_2A_ANA_CDR_00, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P7E_2A_ANA_CDR_00, ~_BIT7, _BIT7);

            // Enable LE, Vth, Tap0~4 Adaptation
            ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0xDF);
            ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0xDF);
            ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0xDF);

            // Waiting for VCO Stable & DFE Adaptation
            DELAY_XUS_EXINT(360);

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            if(ScalerGetBit_EXINT(P7E_17_BANDGAP_03, _BIT1) == _BIT1)  // MHL Mode
            {
                if(GET_INPUT_PIXEL_CLK() > 2500) // for 2500~3000 MHL PP Mode
                {
                    // Start to Record LE Max/Min
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, _BIT0);

                    // Waiting for DFE Adaptation
                    DELAY_XUS_EXINT(150);

                    // Stop to Record LE Max/Min
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, 0x00);

                    // Disable All Adaptation Loop
                    ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x00);

                    // Read Back LE Max
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

                    // Read Back Lane0
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
                    g_pucTMDSRx5LEMax[0] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                    // Set Max Value of LE
                    ScalerSetBit_EXINT(P7E_A5_L0_INIT_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), g_pucTMDSRx5LEMax[0]);

                    // Reload LE Max
                    ScalerSetBit_EXINT(P7E_AA_L0_INIT_8, ~_BIT1, _BIT1);
                    ScalerSetBit_EXINT(P7E_AA_L0_INIT_8, ~_BIT1, 0x00);
                }
            }
            else // HDMI Mode
#endif
            {
                if(GET_INPUT_PIXEL_CLK() > 2900) // for 2900~3400 10M Cable Case
                {
                    // Start to Record LE Max/Min
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, _BIT0);

                    // Waiting for DFE Adaptation
                    DELAY_XUS_EXINT(150);

                    // Stop to Record LE Max/Min
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, 0x00);

                    // Disable All Adaptation Loop
                    ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x00);
                    ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0x00);
                    ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0x00);

                    // Read Back LE Max
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

                    // Read Back Lane0
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
                    g_pucTMDSRx5LEMax[0] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                    // Read Back Lane1
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
                    g_pucTMDSRx5LEMax[1] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                    // Read Back Lane2
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
                    g_pucTMDSRx5LEMax[2] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                    // Read Back Tap1 Max
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

                    // Read Back Lane0
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
                    g_pucTMDSRx5Tap1Max[0] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                    // Read Back Lane1
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
                    g_pucTMDSRx5Tap1Max[1] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                    // Read Back Lane2
                    ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
                    g_pucTMDSRx5Tap1Max[2] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                    // Lane0 LEQ >= 20
                    if(g_pucTMDSRx5LEMax[0] >= 16)
                    {
                        // Set Tap2 = 6
                        ScalerSetByte_EXINT(P7E_A6_L0_INIT_4, 0x06);

                        // Set Max Value of LE + Tap1
                        ScalerSetBit_EXINT(P7E_A5_L0_INIT_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTMDSRx5LEMax[0] + g_pucTMDSRx5Tap1Max[0]));

                        // Reload LE/Tap1~2
                        ScalerSetBit_EXINT(P7E_AA_L0_INIT_8, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
                        ScalerSetBit_EXINT(P7E_AA_L0_INIT_8, ~(_BIT2 | _BIT1), 0x00);
                    }

                    // Lane1 LEQ >= 20
                    if(g_pucTMDSRx5LEMax[1] >= 16)
                    {
                        // Set Tap2 = 6
                        ScalerSetByte_EXINT(P7E_B6_L1_INIT_4, 0x06);

                        // Set Max Value of LE + Tap1
                        ScalerSetBit_EXINT(P7E_B5_L1_INIT_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTMDSRx5LEMax[1] + g_pucTMDSRx5Tap1Max[1]));

                        // Reload LE/Tap1~2
                        ScalerSetBit_EXINT(P7E_BA_L1_INIT_8, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
                        ScalerSetBit_EXINT(P7E_BA_L1_INIT_8, ~(_BIT2 | _BIT1), 0x00);
                    }

                    // Lane2 LEQ >= 20
                    if(g_pucTMDSRx5LEMax[2] >= 16)
                    {
                        // Set Tap2 = 6
                        ScalerSetByte_EXINT(P7E_C6_L2_INIT_4, 0x06);

                        // Set Max Value of LE + Tap1
                        ScalerSetBit_EXINT(P7E_C5_L2_INIT_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTMDSRx5LEMax[2] + g_pucTMDSRx5Tap1Max[2]));

                        // Reload LE/Tap1~2
                        ScalerSetBit_EXINT(P7E_CA_L2_INIT_8, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
                        ScalerSetBit_EXINT(P7E_CA_L2_INIT_8, ~(_BIT2 | _BIT1), 0x00);
                    }
                }
            }

            // Disable Adaptation
            ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0x00);
        }
        else  // 3400~6000 Analog CDR
        {
            // [7] cmu_en = 1'b1 --> Enable CMU PLL
            ScalerSetBit_EXINT(P7E_1B_CMU_01, ~_BIT7, _BIT7);

            // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
            // [1] reg_en_eqen_manual_l0 = 1'b1
            ScalerSetBit_EXINT(P7E_12_ANA_CDR, ~(_BIT4 | _BIT1), (_BIT4 | _BIT1));

            // [7] reg_rstb_fsm --> Toggle for FLD reset
            ScalerSetBit_EXINT(P7E_2A_ANA_CDR_00, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P7E_2A_ANA_CDR_00, ~_BIT7, _BIT7);

            // Enable LE, Vth, Tap0~4 Adaptation
            ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0xDF);
            ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0xDF);
            ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0xDF);

            // Waiting for VCO Stable & DFE Adaptation
            DELAY_XUS_EXINT(360);

#if(_INPUTCLOCK_RANG_DVI >= 3400)
            // Delay 2.9ms due to RLE0638 is unscrambled source.
            DELAY_XUS_EXINT(1000);
            DELAY_XUS_EXINT(1000);
            DELAY_XUS_EXINT(900);
#endif

            // Start to Record Tap0/Tap1 Max/Min
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, _BIT0);

            // Waiting for DFE Adaptation
            DELAY_XUS_EXINT(150);

            // Stop to Record Tap0 Max/Min
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, 0x00);

            // Disable Adaptation
            ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0x00);

            // Read Back Tap0 Max
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

            // Read Back Lane0
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            g_pucTMDSRx5Tap0Max[0] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Lane1
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            g_pucTMDSRx5Tap0Max[1] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Lane2
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            g_pucTMDSRx5Tap0Max[2] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Tap0 Min
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

            // Read Back Lane0
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            g_pucTMDSRx5Tap0Min[0] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Lane1
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            g_pucTMDSRx5Tap0Min[1] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Lane2
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            g_pucTMDSRx5Tap0Min[2] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Reload Max Value of Tap0
            ScalerSetByte_EXINT(P7E_A4_L0_INIT_2, g_pucTMDSRx5Tap0Min[0]);
            ScalerSetByte_EXINT(P7E_B4_L1_INIT_2, g_pucTMDSRx5Tap0Min[1]);
            ScalerSetByte_EXINT(P7E_C4_L2_INIT_2, g_pucTMDSRx5Tap0Min[2]);

            // Reload Tap0
            ScalerSetByte_EXINT(P7E_AA_L0_INIT_8, 0x01);
            ScalerSetByte_EXINT(P7E_BA_L1_INIT_8, 0x01);
            ScalerSetByte_EXINT(P7E_CA_L2_INIT_8, 0x01);
            ScalerSetByte_EXINT(P7E_AA_L0_INIT_8, 0x00);
            ScalerSetByte_EXINT(P7E_BA_L1_INIT_8, 0x00);
            ScalerSetByte_EXINT(P7E_CA_L2_INIT_8, 0x00);

            // Enable LE/Tap1 Adapt
            ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x82);
            ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0x82);
            ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0x82);

            // Waiting for DFE Adaptation
            DELAY_XUS_EXINT(290);

            // Start to Record LE Max/Min
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, _BIT0);

            // Waiting for DFE Adaptation
            DELAY_XUS_EXINT(150);

            // Stop to Record LE Max/Min
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, 0x00);

            // Disable Adaptation
            ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0x00);
            ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0x00);

            // Read Back LE Min
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));

            // Read Back Lane0
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            g_pucTMDSRx5LEMin[0] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Lane1
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            g_pucTMDSRx5LEMin[1] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Lane2
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            g_pucTMDSRx5LEMin[2] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back LE Max
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

            // Read Back Lane0
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            g_pucTMDSRx5LEMax[0] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Lane1
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            g_pucTMDSRx5LEMax[1] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Lane2
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            g_pucTMDSRx5LEMax[2] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Tap1 Max
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

            // Read Back Lane0
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            g_pucTMDSRx5Tap1Max[0] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Lane1
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            g_pucTMDSRx5Tap1Max[1] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Read Back Lane2
            ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            g_pucTMDSRx5Tap1Max[2] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

            // Reload LE/Tap1 to Max
            ScalerSetByte_EXINT(P7E_A5_L0_INIT_3, g_pucTMDSRx5LEMax[0] + g_pucTMDSRx5Tap1Max[0]);
            ScalerSetByte_EXINT(P7E_B5_L1_INIT_3, g_pucTMDSRx5LEMax[1] + g_pucTMDSRx5Tap1Max[1]);
            ScalerSetByte_EXINT(P7E_C5_L2_INIT_3, g_pucTMDSRx5LEMax[2] + g_pucTMDSRx5Tap1Max[2]);

            // Reload LE + Tap1
            ScalerSetByte_EXINT(P7E_AA_L0_INIT_8, 0x02);
            ScalerSetByte_EXINT(P7E_BA_L1_INIT_8, 0x02);
            ScalerSetByte_EXINT(P7E_CA_L2_INIT_8, 0x02);
            ScalerSetByte_EXINT(P7E_AA_L0_INIT_8, 0x00);
            ScalerSetByte_EXINT(P7E_BA_L1_INIT_8, 0x00);
            ScalerSetByte_EXINT(P7E_CA_L2_INIT_8, 0x00);
        }
#else
        // [7] cmu_en = 1'b1 --> Enable CMU PLL
        ScalerSetBit_EXINT(P7E_1B_CMU_01, ~_BIT7, _BIT7);

        // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
        // [1] reg_en_eqen_manual_l0 = 1'b1
        ScalerSetBit_EXINT(P7E_12_ANA_CDR, ~(_BIT4 | _BIT1), (_BIT4 | _BIT1));

        // [7] reg_rstb_fsm --> Toggle for FLD reset
        ScalerSetBit_EXINT(P7E_2A_ANA_CDR_00, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(P7E_2A_ANA_CDR_00, ~_BIT7, _BIT7);

        // Enable LE, Vth, Tap0~4 Adaptation
        ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0xDF);

        // Waiting for VCO Stable & DFE Adaptation
        DELAY_XUS_EXINT(360);

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        if(ScalerGetBit_EXINT(P7E_17_BANDGAP_03, _BIT1) == _BIT1)  // MHL Mode
        {
            if(GET_INPUT_PIXEL_CLK() > 2500) // for 2500~3000 MHL PP Mode
            {
                // Start to Record LE Max/Min
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, _BIT0);

                // Waiting for DFE Adaptation
                DELAY_XUS_EXINT(150);

                // Stop to Record LE Max/Min
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, 0x00);

                // Disable All Adaptation Loop
                ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x00);

                // Read Back LE Max
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

                // Read Back Lane0
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
                g_pucTMDSRx5LEMax[0] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                // Set Max Value of LE
                ScalerSetBit_EXINT(P7E_A5_L0_INIT_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), g_pucTMDSRx5LEMax[0]);

                // Reload LE Max
                ScalerSetBit_EXINT(P7E_AA_L0_INIT_8, ~_BIT1, _BIT1);
                ScalerSetBit_EXINT(P7E_AA_L0_INIT_8, ~_BIT1, 0x00);
            }
        }
        else // HDMI Mode
#endif
        {
            if(GET_INPUT_PIXEL_CLK() > 2900) // for 2900~3400 10M Cable Case
            {
                // Start to Record LE Max/Min
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, _BIT0);

                // Waiting for DFE Adaptation
                DELAY_XUS_EXINT(150);

                // Stop to Record LE Max/Min
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~_BIT0, 0x00);

                // Disable All Adaptation Loop
                ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x00);
                ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0x00);
                ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0x00);

                // Read Back LE Max
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

                // Read Back Lane0
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
                g_pucTMDSRx5LEMax[0] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                // Read Back Lane1
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
                g_pucTMDSRx5LEMax[1] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                // Read Back Lane2
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
                g_pucTMDSRx5LEMax[2] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                // Read Back Tap1 Max
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

                // Read Back Lane0
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
                g_pucTMDSRx5Tap1Max[0] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                // Read Back Lane1
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
                g_pucTMDSRx5Tap1Max[1] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                // Read Back Lane2
                ScalerSetBit_EXINT(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
                g_pucTMDSRx5Tap1Max[2] = ScalerGetByte_EXINT(P7E_F3_COEF_4);

                // Lane0 LEQ >= 20
                if(g_pucTMDSRx5LEMax[0] >= 16)
                {
                    // Set Tap2 = 6
                    ScalerSetByte_EXINT(P7E_A6_L0_INIT_4, 0x06);

                    // Set Max Value of LE + Tap1
                    ScalerSetBit_EXINT(P7E_A5_L0_INIT_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTMDSRx5LEMax[0] + g_pucTMDSRx5Tap1Max[0]));

                    // Reload LE/Tap1~2
                    ScalerSetBit_EXINT(P7E_AA_L0_INIT_8, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
                    ScalerSetBit_EXINT(P7E_AA_L0_INIT_8, ~(_BIT2 | _BIT1), 0x00);
                }

                // Lane1 LEQ >= 20
                if(g_pucTMDSRx5LEMax[1] >= 16)
                {
                    // Set Tap2 = 6
                    ScalerSetByte_EXINT(P7E_B6_L1_INIT_4, 0x06);

                    // Set Max Value of LE + Tap1
                    ScalerSetBit_EXINT(P7E_B5_L1_INIT_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTMDSRx5LEMax[1] + g_pucTMDSRx5Tap1Max[1]));

                    // Reload LE/Tap1~2
                    ScalerSetBit_EXINT(P7E_BA_L1_INIT_8, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
                    ScalerSetBit_EXINT(P7E_BA_L1_INIT_8, ~(_BIT2 | _BIT1), 0x00);
                }

                // Lane2 LEQ >= 20
                if(g_pucTMDSRx5LEMax[2] >= 16)
                {
                    // Set Tap2 = 6
                    ScalerSetByte_EXINT(P7E_C6_L2_INIT_4, 0x06);

                    // Set Max Value of LE + Tap1
                    ScalerSetBit_EXINT(P7E_C5_L2_INIT_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTMDSRx5LEMax[2] + g_pucTMDSRx5Tap1Max[2]));

                    // Reload LE/Tap1~2
                    ScalerSetBit_EXINT(P7E_CA_L2_INIT_8, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
                    ScalerSetBit_EXINT(P7E_CA_L2_INIT_8, ~(_BIT2 | _BIT1), 0x00);
                }
            }
        }

        // Disable Adaptation
        ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0x00);
#endif
    }

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(ScalerGetBit_EXINT(P7E_17_BANDGAP_03, _BIT1) == _BIT1)  // MHL Mode
    {
        // Disable Adaptation
        ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0x00);

        // [4] reg_adp_eq_off = 1'b1 --> Disable Adaptation for Analog CDR
        ScalerSetBit_EXINT(P7E_2B_ANA_CDR_01, ~_BIT4, _BIT4);

        // [1] reg_en_eqen_manual_l0 = 1'b0
        ScalerSetBit_EXINT(P7E_12_ANA_CDR, ~_BIT1, 0x00);

        // Reload Tap0 = 21
        ScalerSetByte_EXINT(P7E_A4_L0_INIT_2, 0x15);
        ScalerSetByte_EXINT(P7E_AA_L0_INIT_8, 0x01);
        ScalerSetByte_EXINT(P7E_AA_L0_INIT_8, 0x00);

        // Enable Sumamp High Gain Mode
        ScalerSetBit_EXINT(P7E_1D_CMU_03, ~_BIT4, _BIT4);

        /////////////////////
        // Second K Offset //
        /////////////////////

        // [5] Enable Foreground Calibration Auto Mode
        ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT5, _BIT5);

        // [6] Toggle Foreground Calibration
        ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT6, _BIT6);
        ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT6, 0x00);
        ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT6, _BIT6);

        // Waiting for K Offset
        DELAY_XUS_EXINT(150);

        // Set Manual FLD Fine Tune OK
        ScalerTMDSRx5FLDBandFineTune_EXINT0();

        // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
        if(ucIcp > 7)
        {
            ScalerSetBit_EXINT(P7E_31_ANA_CDR_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else
        {
            ScalerSetBit_EXINT(P7E_31_ANA_CDR_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
        }

        // Waiting for VCO Stable
        DELAY_25US_EXINT();

        // [6] reg_adj_en_manual = 1'b1 -->  Enable adj_en_manual
        // [5] reg_cp_en_manual = 1'b1 -->  Enable cp_en_manual
        ScalerSetBit_EXINT(P7E_2B_ANA_CDR_01, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

        // Waiting for VCO Stable
        DELAY_XUS_EXINT(80);

        // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
        ScalerSetBit_EXINT(P7E_31_ANA_CDR_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

        // Waiting for VCO Stable
        DELAY_XUS_EXINT(80);
    }
    else
#endif
    {
        if(ScalerGetBit_EXINT(P7E_1B_CMU_01, _BIT0) == _BIT0) // DCDR
        {
            // Disable the Vth Adaptation Loop
            ScalerSetBit_EXINT(P7E_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
            ScalerSetBit_EXINT(P7E_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
            ScalerSetBit_EXINT(P7E_C1_L2_DFE_EN_2, ~_BIT6, 0x00);
        }
        else // 2000~6000 ACDR
        {
            // [4] reg_adp_eq_off = 1'b1 --> Disable Adaptation for Analog CDR
            ScalerSetBit_EXINT(P7E_2B_ANA_CDR_01, ~_BIT4, _BIT4);

            // [1] reg_en_eqen_manual_l0 = 1'b0
            ScalerSetBit_EXINT(P7E_12_ANA_CDR, ~_BIT1, 0x00);

            // Enable Sumamp High Gain Mode
            ScalerSetBit_EXINT(P7E_1D_CMU_03, ~_BIT4, _BIT4);

            /////////////////////
            // Second K Offset //
            /////////////////////

            // Read Back K offset Lane0
            if((ScalerGetByte_EXINT(P7E_27_KOFFSET_03) & 0x1F) > 24)
            {
                // Set Servo = 24
                ScalerSetBit_EXINT(P7E_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
            }
            else if((ScalerGetByte_EXINT(P7E_27_KOFFSET_03) & 0x1F) < 8)
            {
                // Set Servo = 8
                ScalerSetBit_EXINT(P7E_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
            }

            // Read Back K offset Lane1
            if((ScalerGetByte_EXINT(P7E_28_KOFFSET_04) & 0x1F) > 24)
            {
                // Set Servo = 24
                ScalerSetBit_EXINT(P7E_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
            }
            else if((ScalerGetByte_EXINT(P7E_28_KOFFSET_04) & 0x1F) < 8)
            {
                // Set Servo = 8
                ScalerSetBit_EXINT(P7E_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
            }

            // Read Back K offset Lane2
            if((ScalerGetByte_EXINT(P7E_29_KOFFSET_05) & 0x1F) > 24)
            {
                // Set Servo = 24
                ScalerSetBit_EXINT(P7E_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
            }
            else if((ScalerGetByte_EXINT(P7E_29_KOFFSET_05) & 0x1F) < 8)
            {
                // Set Servo = 8
                ScalerSetBit_EXINT(P7E_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
            }

            // Reload Servo
            ScalerSetByte_EXINT(P7E_AA_L0_INIT_8, 0x20);
            ScalerSetByte_EXINT(P7E_BA_L1_INIT_8, 0x20);
            ScalerSetByte_EXINT(P7E_CA_L2_INIT_8, 0x20);
            ScalerSetByte_EXINT(P7E_AA_L0_INIT_8, 0x00);
            ScalerSetByte_EXINT(P7E_BA_L1_INIT_8, 0x00);
            ScalerSetByte_EXINT(P7E_CA_L2_INIT_8, 0x00);

            // [5] Enable Foreground Calibration Auto Mode
            ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT5, _BIT5);

            // [6] Toggle Foreground Calibration
            ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT6, _BIT6);
            ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT6, 0x00);
            ScalerSetBit_EXINT(P7E_24_KOFFSET_00, ~_BIT6, _BIT6);

            // Waiting for K Offset
            DELAY_XUS_EXINT(150);

            // Set Manual FLD Fine Tune OK
            ScalerTMDSRx5FLDBandFineTune_EXINT0();

            // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
            if(ucIcp > 7)
            {
                ScalerSetBit_EXINT(P7E_31_ANA_CDR_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            }
            else
            {
                ScalerSetBit_EXINT(P7E_31_ANA_CDR_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
            }

            // Waiting for VCO Stable
            DELAY_25US_EXINT();

            // [6] reg_adj_en_manual = 1'b1 -->  Enable adj_en_manual
            // [5] reg_cp_en_manual = 1'b1 -->  Enable cp_en_manual
            ScalerSetBit_EXINT(P7E_2B_ANA_CDR_01, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            // Waiting for VCO Stable
            DELAY_XUS_EXINT(80);

            // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
            ScalerSetBit_EXINT(P7E_31_ANA_CDR_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

            // Waiting for VCO Stable
            DELAY_XUS_EXINT(80);
        }
    }

#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
    // solve philip DVD issue
    if((ScalerGetBit_EXINT(P7E_E4_GAIN_3, _BIT1) == _BIT1) && (((g_pucTMDSRx5Tap0Max[0] == g_ucTMDSRx5Tap0Init) && (g_pucTMDSRx5Tap0Min[0] == g_ucTMDSRx5Tap0Init)) ||
                                                               ((g_pucTMDSRx5Tap0Max[1] == g_ucTMDSRx5Tap0Init) && (g_pucTMDSRx5Tap0Min[1] == g_ucTMDSRx5Tap0Init)) ||
                                                               ((g_pucTMDSRx5Tap0Max[2] == g_ucTMDSRx5Tap0Init) && (g_pucTMDSRx5Tap0Min[2] == g_ucTMDSRx5Tap0Init))))
    {
        // Disable Sumamp High Gain Mode
        ScalerSetBit_EXINT(P7E_1D_CMU_03, ~_BIT4, 0x00);

        // [1] reg_en_eqen_manual_l0 = 1'b1
        ScalerSetBit_EXINT(P7E_12_ANA_CDR, ~_BIT1, _BIT1);

        // Enable LE, Vth, Tap0~4 Adaptation
        ScalerSetByte_EXINT(P7E_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7E_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7E_C1_L2_DFE_EN_2, 0xDF);
    }
#endif

    // [3] reg_en_data_manual_l0 = 1'b1
    ScalerSetBit_EXINT(P7E_12_ANA_CDR, ~_BIT3, _BIT3);

    // [0] en_data_manual = 1'b1 --> Enable Dataout
    ScalerSetBit_EXINT(P7E_11_DATA_TIMER, ~_BIT0, _BIT0);

    // Reset PHY -> MAC Interface
    ScalerSetBit_EXINT(P74_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P74_A7_TMDS_PWDCTL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Reset HDMI 3 Channel FIFO
    ScalerSetBit_EXINT(P74_B0_TMDS_CHANNEL_FIFO, ~_BIT6, _BIT6);

    // HDMI 3 Channel FIFO Global Enable
    ScalerSetBit_EXINT(P74_B0_TMDS_CHANNEL_FIFO, ~(_BIT7 | _BIT6), _BIT7);

    // Clear RGB Data Detection Flags
    ScalerSetBit_EXINT(P74_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5));
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5IntHandler_EXINT0(void) using 1
{
#if(_D5_HDMI_2_0_SUPPORT == _ON)
    BYTE pucBackUp[4];
#else
    BYTE pucBackUp[2];
#endif

    WORD usCount = 0;

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    bit bMHLFail = _FALSE;
#endif

    pucBackUp[0] = ScalerGetByte_EXINT(P74_C9_HDMI_AP);
    pucBackUp[1] = ScalerGetByte_EXINT(P74_C8_HDMI_APC);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P74_C8_HDMI_APC, ~_BIT0, 0x00);

#if(_D5_HDMI_2_0_SUPPORT == _ON)
    pucBackUp[2] = ScalerGetByte_EXINT(P74_39_HDMI_CTRL_39);
    pucBackUp[3] = ScalerGetByte_EXINT(P74_38_HDMI_CTRL_38);
#endif

    // Freq. Stable Into IRQ
    if(((ScalerGetByte_EXINT(P74_EF_HDMI_ERROR_TH) & 0xC0) == 0xC0) && (g_ucTMDSRx5ClkIRQ == _ENABLE))
    {
        // Disable Freq Stable IRQ
        ScalerSetBit_EXINT(P74_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), _BIT6);

#if(_D5_HDMI_2_0_SUPPORT == _ON)
        // Set SCDC Port Clock Detected
        ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_40_PORT_PAGE74_HDMI_SCDC_40);
        ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

        // Disable Reset HDMI/DVI Format
        ScalerSetBit_EXINT(P74_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_10_PORT_PAGE74_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P74_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX5_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P74_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P74_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
#endif

        // Enable Freq unstable IRQ
        ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Pop up Counter Value
        ScalerSetBit_EXINT(P74_EC_HDMI_FREQDET_STABLE, ~_BIT7, _BIT7);

        usCount = (WORD)(((ScalerGetByte_EXINT(P74_ED_HDMI_FREQDET_RESULT_M) & 0x7F) << 8) | ScalerGetByte_EXINT(P74_EE_HDMI_FREQDET_RESULT_L));

        // TMDS_FREQ(MHz) = GDI_CLK(MHz) * CLK_COUNT * _TMDS_MEASURE_CLOCK_DIVIDER / _TMDS_MEASURE_CLOCK_COUNTER
        SET_INPUT_PIXEL_CLK((((DWORD)_GDI_CLK_KHZ * usCount + 50000) / 100000));

        if(GET_INPUT_PIXEL_CLK() > 3000)
        {
            // Set Input Clock Measure Divider = /2
            ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_28_PORT_PAGE74_HDMI_NTX1024TR0);
            ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~_BIT6, _BIT6);
        }
        else
        {
            // Set Input Clock Measure Divider = /1
            ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_28_PORT_PAGE74_HDMI_NTX1024TR0);
            ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~_BIT6, 0x00);
        }

        if((GET_TMDS_RX5_PHY_SET() == _FALSE) || ((bit)ScalerTMDSRx5CheckCDRStable_EXINT0(g_usTMDSRx5ClkCount) == _FALSE))
        {
            g_usTMDSRx5ClkCount = ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_TMDS);

            // If Measure Divider = /2 then CLK x 2
            ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_28_PORT_PAGE74_HDMI_NTX1024TR0);
            if(ScalerGetBit_EXINT(P74_CA_HDMI_DP, _BIT6) == _BIT6)
            {
                // TMDS_OFFLine Measure FREQ(MHz) = GDI_CLK(MHz) * 1024 * 2 / g_usTMDSRx5ClkCount
                SET_TMDS_OFFLINE_MEASURE_CLK(((DWORD)(_GDI_CLK_KHZ * 1024) * 2 / 100) / g_usTMDSRx5ClkCount);
            }
            else
            {
                // TMDS_OFFLine Measure FREQ(MHz) = GDI_CLK(MHz) * 1024 / g_usTMDSRx5ClkCount
                SET_TMDS_OFFLINE_MEASURE_CLK(((DWORD)(_GDI_CLK_KHZ * 1024) / 100) / g_usTMDSRx5ClkCount);
            }

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR);

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                // Set HDMI/DVI switch to Auto Mode
                ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
#else
                // Set HDMI/DVI switch to Manual Mode and Forced to HDMI
                ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
#endif

                if((GET_INPUT_PIXEL_CLK() >= 730) && (GET_INPUT_PIXEL_CLK() <= 770))
                {
                    SET_TMDS_RX5_CLK_MODE(_TMDS_MHL_PPMODE_PHY_SETTING);

                    SET_INPUT_PIXEL_CLK(GET_INPUT_PIXEL_CLK() * 4);
                    ScalerTMDSRx5SetPhy_EXINT0();
                    SET_INPUT_PIXEL_CLK(GET_INPUT_PIXEL_CLK() / 4);

                    // Enable Packed Pixel Mode
                    ScalerSetBit_EXINT(P79_A0_MHL_CTRL_00, ~_BIT1, _BIT1);

                    // Check CDR Stable
                    if((ScalerTMDSRx5CheckCDRStable_EXINT0(g_usTMDSRx5ClkCount) == _FALSE) || (ScalerMHLRx5DetectClkMode_EXINT0() == _FALSE))// MHL mode need modify
                    {
                        SET_TMDS_RX5_CLK_MODE(_TMDS_24BIT_PHY_SETTING);

                        // TMDS_FREQ(MHz) = GDI_CLK(MHz) * 1024 / CLK_COUNT = GDI_CLK(KHz) * 1024 / (CLK_COUNT * 1024)
                        SET_INPUT_PIXEL_CLK(GET_INPUT_PIXEL_CLK() * 3);
                        ScalerTMDSRx5SetPhy_EXINT0();
                        SET_INPUT_PIXEL_CLK(GET_INPUT_PIXEL_CLK() / 3);

                        // Disable Packed Pixel Mode
                        ScalerSetBit_EXINT(P79_A0_MHL_CTRL_00, ~_BIT1, 0x00);

                        if((ScalerTMDSRx5CheckCDRStable_EXINT0(g_usTMDSRx5ClkCount) == _FALSE) || (ScalerMHLRx5DetectClkMode_EXINT0() == _FALSE))// MHL Need modify
                        {
                            bMHLFail = _TRUE;
                        }
                    }
                }
                else
                {
                    SET_TMDS_RX5_CLK_MODE(_TMDS_24BIT_PHY_SETTING);

                    // TMDS_FREQ(MHz) = GDI_CLK(MHz) * 1024 / CLK_COUNT = GDI_CLK(KHz) * 1024 / (CLK_COUNT * 1024)
                    SET_INPUT_PIXEL_CLK(GET_INPUT_PIXEL_CLK() * 3);
                    ScalerTMDSRx5SetPhy_EXINT0();
                    SET_INPUT_PIXEL_CLK(GET_INPUT_PIXEL_CLK() / 3);

                    // Disable Packed Pixel Mode
                    ScalerSetBit_EXINT(P79_A0_MHL_CTRL_00, ~_BIT1, 0x00);

                    if((ScalerTMDSRx5CheckCDRStable_EXINT0(g_usTMDSRx5ClkCount) == _FALSE) || (ScalerMHLRx5DetectClkMode_EXINT0() == _FALSE))// MHL Need modify
                    {
                        bMHLFail = _TRUE;
                    }
                }
            }
            else
            {
                SET_TMDS_RX5_CLK_MODE(_TMDS_24BIT_PHY_SETTING);

                ScalerTMDSRx5SetPhy_EXINT0();

                // Disable Packed Pixel Mode
                ScalerSetBit_EXINT(P79_A0_MHL_CTRL_00, ~_BIT1, 0x00);

                // Set HDMI/DVI switch to Auto Mode
                ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR);
                ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
            }
#else
            ScalerTMDSRx5SetPhy_EXINT0();
#endif
        }

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        if(bMHLFail == _FALSE)
#endif
        {
            // Set Upper Bound (allow 1/64 freq shift)
            ScalerSetByte_EXINT(P74_E8_HDMI_FREQDET_UPPER_M, (HIBYTE(usCount + (usCount >> 6)) & 0x7F));
            ScalerSetByte_EXINT(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(usCount + (usCount >> 6)));

            // Set Lower bound
            ScalerSetByte_EXINT(P74_EA_HDMI_FREQDET_LOWER_M, (HIBYTE(usCount - (usCount >> 6)) & 0x7F));
            ScalerSetByte_EXINT(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(usCount - (usCount >> 6)));

            // Reset Color Depth to 8 Bits
            SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

            SET_TMDS_RX5_PHY_SET();
        }

#if(_D5_HDMI_2_0_SUPPORT == _ON)
        // Clear CED Lock Transition Flag
        ScalerSetBit_EXINT(P74_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Set HDMI 2.0 Character Error Detection Function Lock Transition Error Boundary
        ScalerSetBit_EXINT(P74_14_HDMI_CTRL_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_INPUT_PIXEL_CLK() / 10) >> 8);
        ScalerSetByte_EXINT(P74_15_HDMI_CTRL_15, (GET_INPUT_PIXEL_CLK() / 10));

        // Enable Character Error Detection Function & Valid Flag
        ScalerSetBit_EXINT(P74_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

        // Enable Character Error Detction Function Lock Transition IRQ
        ScalerSetBit_EXINT(P74_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
    }

    // Freq. Unstable Into IRQ
    if(((ScalerGetByte_EXINT(P74_E6_HDMI_FREQDET_CTRL) & 0x06) == 0x06) && (g_ucTMDSRx5ClkIRQ == _ENABLE))
    {
        // Clear Unstable IRQ Flag
        ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

        // Ensure Freq really unstable
        if((abs(g_usTMDSRx5ClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (g_usTMDSRx5ClkCount >> 6)) ||
           (abs(GET_INPUT_PIXEL_CLK() - ((GET_TMDS_OFFLINE_MEASURE_CLK() << 3) / ((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) ? _COLOR_DEPTH_8_BITS : GET_COLOR_DEPTH()))) > (GET_INPUT_PIXEL_CLK() >> 6)))
        {
            // Set Display M1 output force to background color and free run mode
            ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);

            // Disable RGB/clock Output to avoid garbage
            ScalerSetBit_EXINT(P74_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

#if(_D5_HDMI_2_0_SUPPORT == _ON)

            // Clear Scrambling Detection Flag
            ScalerSetBit_EXINT(P74_01_HDMI_CTRL_01, ~_BIT3, _BIT3);

            // Disable Scrambling Status
            ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_21_PORT_PAGE74_HDMI_SCDC_21);
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT0, 0x00);

            // Disable CED Function
            ScalerSetBit_EXINT(P74_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

            // Pop Up CED Error For Clear Error Counter
            ScalerSetBit_EXINT(P74_0C_HDMI_CTRL_0C, ~_BIT7, _BIT7);

            // Disable CED Lock Transition IRQ & Flag
            ScalerSetBit_EXINT(P74_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P74_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // Clear SCDC Port Status Update Flag & CED Update Flag
            ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_10_PORT_PAGE74_HDMI_SCDC_10);
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~(_BIT1 | _BIT0), 0x00);

            // Clear SCDC Port Status Lock Flag
            ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_40_PORT_PAGE74_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Reset HDMI/DVI Format
            ScalerSetBit_EXINT(P74_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
#endif

            // Disable Freq. Unstable IRQ
            ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

            // Set HDMI/DVI switch to Auto Mode
            ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR);
            ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                // Set Upper Bound
                ScalerSetByte_EXINT(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
                ScalerSetByte_EXINT(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));

                // Suspend Key Calculation before load key
                ScalerSetBit_EXINT(P74_AE_TMDS_RPS, ~_BIT1, 0x00);
            }
            else
#endif
            {
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte_EXINT(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte_EXINT(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte_EXINT(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte_EXINT(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
            }

            // Set Lower bound
            ScalerSetByte_EXINT(P74_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
            ScalerSetByte_EXINT(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

            // Reset Freq. Detect Counter(Toggle)
            ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

            // Enable Freq. Stable IRQ
            ScalerSetBit_EXINT(P74_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            CLR_TMDS_RX5_PHY_SET();

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)))
            // Reset Authenticated FSM
            ScalerSetByte_EXINT(P6E_28_HDCP_I2C_CTRL_2, 0x01);
            ScalerSetBit_EXINT(P6E_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);

            // Cancel HDCP 2.2 Re-Auth Timer Event
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX5_HDCP2_REAUTH);
#endif
        }
    }

#if(_D5_HDMI_2_0_SUPPORT == _ON)

    // Detect Source Write Read Request Enable Flag
    if((ScalerGetBit_EXINT(P74_25_HDMI_CTRL_25, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P74_26_HDMI_CTRL_26, _BIT3) == _BIT3))
    {
        // Clear Read Request Flag
        ScalerSetBit_EXINT(P74_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Set Read Request Enable
        SET_HDMI_2_0_RX5_RR_ENABLE();

        // Enable Test Read Request HW Auto Mode
        ScalerSetBit_EXINT(P74_1C_HDMI_CTRL_1C, ~_BIT1, _BIT1);

        // Enable CED Update Read Request Auto Mode
        ScalerSetBit_EXINT(P74_24_HDMI_CTRL_24, ~_BIT0, _BIT0);

        // Enable Read Request Done IRQ
        ScalerSetBit_EXINT(P74_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
    }

    // Detect CED Channel 2 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P74_17_HDMI_CTRL_17, _BIT2) == _BIT2) && (ScalerGetBit_EXINT(P74_18_HDMI_CTRL_18, _BIT2) == _BIT2))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P74_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P74_17_HDMI_CTRL_17, _BIT5) == _BIT5)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_40_PORT_PAGE74_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT3, _BIT3);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_40_PORT_PAGE74_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT3, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_10_PORT_PAGE74_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P74_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX5_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P74_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P74_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Detect CED Channel 1 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P74_17_HDMI_CTRL_17, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P74_18_HDMI_CTRL_18, _BIT1) == _BIT1))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P74_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P74_17_HDMI_CTRL_17, _BIT4) == _BIT4)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_40_PORT_PAGE74_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT2, _BIT2);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_40_PORT_PAGE74_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT2, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_10_PORT_PAGE74_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P74_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX5_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P74_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P74_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Detect CED Channel 0 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P74_17_HDMI_CTRL_17, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P74_18_HDMI_CTRL_18, _BIT0) == _BIT0))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P74_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P74_17_HDMI_CTRL_17, _BIT3) == _BIT3)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_40_PORT_PAGE74_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT1, _BIT1);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_40_PORT_PAGE74_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT1, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, _P74_3A_PT_10_PORT_PAGE74_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P74_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P74_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX5_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P74_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P74_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Read Request Done into IRQ
    if((ScalerGetBit_EXINT(P74_1F_HDMI_CTRL_1F, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P74_1C_HDMI_CTRL_1C, _BIT7) == _BIT7))
    {
        // Clear Read Request Done Flag
        ScalerSetBit_EXINT(P74_1C_HDMI_CTRL_1C, ~_BIT7, _BIT7);

        // Read Request Outcome Processing
        ScalerTMDSRx5ReadRequestProc_EXINT0(ScalerGetByte_EXINT(P74_1C_HDMI_CTRL_1C) & 0x70);
    }

    // Detect HDMI HPD Rising to Falling into IRQ
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(P74_23_HDMI_CTRL_23, (_BIT6 | _BIT1)) == (_BIT6 | _BIT1))
    {
        // Clear HPD IRQ Flag
        ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~_BIT1, _BIT1);

        if(ScalerGetBit_EXINT(P74_23_HDMI_CTRL_23, (_BIT2 | _BIT0)) == 0x00)
        {
            // Clear All Source Write SCDC Port Register
            ScalerSetBit_EXINT(P74_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Clear HDMI 2.0 Read Request Enable
            CLR_HDMI_2_0_RX5_RR_ENABLE();

            // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~_BIT6, _BIT6);

            /*
            // Disable Test Read Request HW Auto Mode
            ScalerSetBit_EXINT(P74_1C_HDMI_CTRL_1C, ~_BIT1, 0x00);

            // Disable CED Update Read Request Auto Mode
            ScalerSetBit_EXINT(P74_24_HDMI_CTRL_24, ~_BIT0, 0x00);

            // Disable Character Error Detection Function
            ScalerSetBit_EXINT(P74_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

            // Disable Lock Transition IRQ
            ScalerSetBit_EXINT(P74_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            ScalerSetBit_EXINT(P74_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Detect 3 Channel CDR Stable
            if((bit)ScalerTMDSRx5CheckCDRStable_EXINT(g_usTMDSRx5ClkCount) == _TRUE)
            {
                // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

                // Enable Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
            }
            */
        }
        else
        {
            /*
            // Enable CED Function
            ScalerSetBit_EXINT(P74_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

            // Enable CED Lock Transition IRQ
            ScalerSetBit_EXINT(P74_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            ScalerSetBit_EXINT(P74_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Enable SCDC Module
            ScalerSetBit_EXINT(P74_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
            */

            // Disable Falling to Rising IRQ, Set IRQ Status Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);

            // Enable Rising to edge IRQ
            ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
        }
    }
#endif // End of #if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)

#endif // End of #if(_D5_HDMI_2_0_SUPPORT == _ON)

    // HDCP 1.4 Write Aksv IRQ have been Received
    if((ScalerGetBit_EXINT(P74_A9_TMDS_ABC0, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P74_AA_TMDS_ABC1, _BIT4) == _BIT4))
    {
        // clear AKSV flag
        ScalerSetBit_EXINT(P74_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), _BIT7);

        // SET KEY ready bit 1
        ScalerSetBit_EXINT(P74_AE_TMDS_RPS, ~_BIT1, _BIT1);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Enable HDCP 1.4 Module
        ScalerSetBit_EXINT(P74_C0_HDCP_CR, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Disable HDCP 2 Function
        ScalerSetBit_EXINT(P6E_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);
#endif
    }

#if(_AUDIO_SUPPORT == _ON)
    // Detect if Auido Sampling is Changed
    ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_8A_PORT_PAGE74_AUDIO_FREQDET);
    if(ScalerGetBit_EXINT(P74_CA_HDMI_DP, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1))
    {
        // Clear Auido Sampling Change Flag
        ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_8A_PORT_PAGE74_AUDIO_FREQDET);
        ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~_BIT1, _BIT1);

        // Disable FIFO Boundary Tracking, Disable Trend Tracking
        ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_15_PORT_PAGE74_HDMI_PSCR);
        ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~(_BIT3 | _BIT2), 0x00);

        // Set Double Buffer bit
        ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_10_PORT_PAGE74_HDMI_CMCR);
        ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~_BIT4, _BIT4);

        // Reload D code
        ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0);
        ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~_BIT6, _BIT6);
        ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0);
        ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~_BIT6, 0x00);
    }
#endif

    // Clear IRQ Pending Flag
    ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_60_PORT_PAGE74_HDMI_INTCR);
    ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~_BIT7, _BIT7);

    ScalerSetByte_EXINT(P74_C8_HDMI_APC, pucBackUp[1]);
    ScalerSetByte_EXINT(P74_C9_HDMI_AP, pucBackUp[0]);

#if(_D5_HDMI_2_0_SUPPORT == _ON)
    ScalerSetByte_EXINT(P74_38_HDMI_CTRL_38, pucBackUp[3]);
    ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, pucBackUp[2]);
#endif
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process In PS/PD State(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5PSIntHandler_EXINT0(void) using 1
{
#if(_D5_HDMI_2_0_SUPPORT == _ON)
    BYTE pucBackUp[4];
#else
    BYTE pucBackUp[2];
#endif

    pucBackUp[0] = ScalerGetByte_EXINT(P74_C9_HDMI_AP);
    pucBackUp[1] = ScalerGetByte_EXINT(P74_C8_HDMI_APC);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P74_C8_HDMI_APC, ~_BIT0, 0x00);

#if(_D5_HDMI_2_0_SUPPORT == _ON)
    pucBackUp[2] = ScalerGetByte_EXINT(P74_39_HDMI_CTRL_39);
    pucBackUp[3] = ScalerGetByte_EXINT(P74_38_HDMI_CTRL_38);
#endif

    // HDCP 1.4 Write Aksv IRQ have been Received
    if((ScalerGetBit_EXINT(P74_A9_TMDS_ABC0, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P74_AA_TMDS_ABC1, _BIT4) == _BIT4))
    {
        // clear AKSV flag
        ScalerSetBit_EXINT(P74_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), _BIT7);

        // SET KEY ready bit 1
        ScalerSetBit_EXINT(P74_AE_TMDS_RPS, ~_BIT1, _BIT1);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Enable HDCP 1.4 Module
        ScalerSetBit_EXINT(P74_C0_HDCP_CR, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Disable HDCP 2 Function
        ScalerSetBit_EXINT(P6E_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);
#endif
    }

#if(_D5_HDMI_2_0_SUPPORT == _ON)
    // Detect Source Write Read Request Enable Flag
    if((ScalerGetBit_EXINT(P74_25_HDMI_CTRL_25, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P74_26_HDMI_CTRL_26, _BIT3) == _BIT3))
    {
        // Clear Read Request Flag
        ScalerSetBit_EXINT(P74_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Set Read Request Enable
        SET_HDMI_2_0_RX5_RR_ENABLE();

        // Enable Test Read Request HW Auto Mode
        ScalerSetBit_EXINT(P74_1C_HDMI_CTRL_1C, ~_BIT1, _BIT1);

        // Enable CED Update Read Request Auto Mode
        ScalerSetBit_EXINT(P74_24_HDMI_CTRL_24, ~_BIT0, _BIT0);

        // Enable Read Request Done IRQ
        ScalerSetBit_EXINT(P74_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
    }

    // Read Request Done into IRQ
    if((ScalerGetBit_EXINT(P74_1F_HDMI_CTRL_1F, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P74_1C_HDMI_CTRL_1C, _BIT7) == _BIT7))
    {
        // Clear Read Request Done Flag
        ScalerSetBit_EXINT(P74_1C_HDMI_CTRL_1C, ~_BIT7, _BIT7);

        // Read Request Outcome Processing
        ScalerTMDSRx5ReadRequestProc_EXINT0(ScalerGetByte_EXINT(P74_1C_HDMI_CTRL_1C) & 0x70);
    }

    // Detect HDMI HPD Rising to Falling into IRQ
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(P74_23_HDMI_CTRL_23, (_BIT6 | _BIT1)) == (_BIT6 | _BIT1))
    {
        // Clear HPD IRQ Flag
        ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~_BIT1, _BIT1);

        if(ScalerGetBit_EXINT(P74_23_HDMI_CTRL_23, (_BIT2 | _BIT0)) == 0x00)
        {
            // Clear All Source Write SCDC Port Register
            ScalerSetBit_EXINT(P74_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Clear HDMI 2.0 Read Request Enable
            CLR_HDMI_2_0_RX5_RR_ENABLE();

            // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~_BIT6, _BIT6);

            /*
            // Disable Test Read Request HW Auto Mode
            ScalerSetBit_EXINT(P74_1C_HDMI_CTRL_1C, ~_BIT1, 0x00);

            // Disable CED Update Read Request Auto Mode
            ScalerSetBit_EXINT(P74_24_HDMI_CTRL_24, ~_BIT0, 0x00);

            // Disable Character Error Detection Function
            ScalerSetBit_EXINT(P74_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

            // Disable Lock Transition IRQ
            ScalerSetBit_EXINT(P74_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            ScalerSetBit_EXINT(P74_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Detect 3 Channel CDR Stable
            if((bit)ScalerTMDSRx5CheckCDRStable_EXINT(g_usTMDSRx5ClkCount) == _TRUE)
            {
                // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

                // Enable Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
            }
            */
        }
        else
        {
            /*
            // Enable CED Function
            ScalerSetBit_EXINT(P74_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

            // Enable CED Lock Transition IRQ
            ScalerSetBit_EXINT(P74_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            ScalerSetBit_EXINT(P74_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Enable SCDC Module
            ScalerSetBit_EXINT(P74_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
            */

            // Disable Falling to Rising IRQ, Set IRQ Status Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);

            // Enable Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P74_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
        }
    }
#endif // End of #if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
#endif // End of #if(_D5_HDMI_2_0_SUPPORT == _ON)

    // Clear IRQ Pending Flag
    ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_60_PORT_PAGE74_HDMI_INTCR);
    ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~_BIT7, _BIT7);

    ScalerSetByte_EXINT(P74_C8_HDMI_APC, pucBackUp[1]);
    ScalerSetByte_EXINT(P74_C9_HDMI_AP, pucBackUp[0]);

#if(_D5_HDMI_2_0_SUPPORT == _ON)
    ScalerSetByte_EXINT(P74_38_HDMI_CTRL_38, pucBackUp[3]);
    ScalerSetByte_EXINT(P74_39_HDMI_CTRL_39, pucBackUp[2]);
#endif
}

//--------------------------------------------------
// Description  : Check CDR Locked
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
bit ScalerTMDSRx5CheckCDRStable(WORD usClkCount)
{
    // Disable INT Clock Check
    g_ucTMDSRx5ClkIRQ = _DISABLE;

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        switch(GET_TMDS_RX5_CLK_MODE())
        {
            // Check if Packed Pixel Mode
            case _TMDS_MHL_PPMODE_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
                {
                    DebugMessageRx5("R Channel CDR Unstable", ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED));

                    // Enable INT Clock Check
                    g_ucTMDSRx5ClkIRQ = _ENABLE;

                    return _FALSE;
                }

                break;

            // Check if 24 Bit Mode
            case _TMDS_24BIT_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED) * 3)) > (usClkCount >> 6))
                {
                    DebugMessageRx5("R Channel CDR Unstable", ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED));

                    // Enable INT Clock Check
                    g_ucTMDSRx5ClkIRQ = _ENABLE;

                    return _FALSE;
                }

                break;

            default:

                // Enable INT Clock Check
                g_ucTMDSRx5ClkIRQ = _ENABLE;

                return _FALSE;
                break;
        }
    }
    else
#endif // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    {
        // Check Current Measured Freq. is the same as previously locked
        if(abs(usClkCount - ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED)) > (usClkCount >> 6))
        {
            DebugMessageRx5("R Channel CDR Unstable", ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED));

            // Enable INT Clock Check
            g_ucTMDSRx5ClkIRQ = _ENABLE;

            return _FALSE;
        }

        if(abs(usClkCount - ScalerTMDSRx5MeasureClk(_CLK_SOURCE_BLUE)) > (usClkCount >> 6))
        {
            DebugMessageRx5("B Channel CDR Unstable", ScalerTMDSRx5MeasureClk(_CLK_SOURCE_BLUE));

            // Enable INT Clock Check
            g_ucTMDSRx5ClkIRQ = _ENABLE;

            return _FALSE;
        }

        if(abs(usClkCount - ScalerTMDSRx5MeasureClk(_CLK_SOURCE_GREEN)) > (usClkCount >> 6))
        {
            DebugMessageRx5("G Channel CDR Unstable", ScalerTMDSRx5MeasureClk(_CLK_SOURCE_GREEN));

            // Enable INT Clock Check
            g_ucTMDSRx5ClkIRQ = _ENABLE;

            return _FALSE;
        }
    }

    // Enable INT Clock Check
    g_ucTMDSRx5ClkIRQ = _ENABLE;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check CDR Locked (EXINT0 Only)
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
BYTE ScalerTMDSRx5CheckCDRStable_EXINT0(WORD usClkCount) using 1
{
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        switch(GET_TMDS_RX5_CLK_MODE())
        {
            // Check if Packed Pixel Mode
            case _TMDS_MHL_PPMODE_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                break;

            // Check if 24 Bit Mode
            case _TMDS_24BIT_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_RED) * 3)) > (usClkCount >> 6))
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
#endif // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

    {
        // Check Current Measured Freq. is the same as previously locked
        if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
        {
            return _FALSE;
        }

        if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_RED)) > (usClkCount >> 6))
        {
            return _FALSE;
        }

        if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_BLUE)) > (usClkCount >> 6))
        {
            return _FALSE;
        }

        if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_GREEN)) > (usClkCount >> 6))
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
WORD ScalerTMDSRx5MeasureClk(BYTE ucMeasureClk)
{
    BYTE ucDelayCount = 0;

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Enable Rx_EN (Lane0,3)
        ScalerSetBit(P7E_1A_CMU_00, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));
    }
    else
#endif
    {
        // Enable Rx_EN (Lane3)
        ScalerSetBit(P7E_1A_CMU_00, ~_BIT7, _BIT7);
    }

    // Disable Measure for Reset Measure Window
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_28_PORT_PAGE74_HDMI_NTX1024TR0, ~(_BIT5 | _BIT4 | _BIT3), 0x00);

    // Select reference clk to Xtal Clk and measure clk
    ScalerSetBit(P74_AD_TMDS_CPS, ~(_BIT6 | _BIT5 | _BIT4), ((ucMeasureClk << 5) | _BIT4));

    // Start Measure
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_28_PORT_PAGE74_HDMI_NTX1024TR0, ~(_BIT5 | _BIT4 | _BIT3), _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        DELAY_5US();

        if((ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_28_PORT_PAGE74_HDMI_NTX1024TR0, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerGetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_28_PORT_PAGE74_HDMI_NTX1024TR0, 2, &pData[0], _AUTOINC);

    return ((WORD)(pData[0] & 0x07) << 8) | pData[1];
}

//--------------------------------------------------
// Description  : Measure Clk (EXINT0 Only)
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerTMDSRx5MeasureClk_EXINT0(BYTE ucMeasureClk) using 1
{
    BYTE ucDelayCount = 0;
    WORD usClkCount = 0;
    BYTE ucBackUp = 0;

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Enable Rx_EN (Lane0,3)
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));
    }
    else
#endif
    {
        // Enable Rx_EN (Lane3)
        ScalerSetBit_EXINT(P7E_1A_CMU_00, ~_BIT7, _BIT7);
    }

    // Disable Measure for Reset Measure Window
    ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_28_PORT_PAGE74_HDMI_NTX1024TR0);
    ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~(_BIT5 | _BIT4 | _BIT3), 0x00);

    // Select reference clk to Xtal Clk and measure clk
    ScalerSetBit_EXINT(P74_AD_TMDS_CPS, ~(_BIT6 | _BIT5 | _BIT4), ((ucMeasureClk << 5) | _BIT4));

    ucBackUp = ScalerGetByte_EXINT(P74_C8_HDMI_APC);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P74_C8_HDMI_APC, ~_BIT0, 0x00);

    // Start Measure
    ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_28_PORT_PAGE74_HDMI_NTX1024TR0);
    ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~(_BIT5 | _BIT4 | _BIT3), _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        DELAY_5US_EXINT();

        if((ScalerGetBit_EXINT(P74_CA_HDMI_DP, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_28_PORT_PAGE74_HDMI_NTX1024TR0);
    usClkCount = ((WORD)(ScalerGetByte_EXINT(P74_CA_HDMI_DP) & 0x07) << 8);

    ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_29_PORT_PAGE74_HDMI_NTX1024TR1);
    usClkCount = usClkCount | ScalerGetByte_EXINT(P74_CA_HDMI_DP);

    ScalerSetByte_EXINT(P74_C8_HDMI_APC, ucBackUp);

    return usClkCount;
}

#if(_D5_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Deep Color PLL
// Input Value  : usTMDSClkCount, ucColorDepth
// Output Value : None
//--------------------------------------------------
bit ScalerTMDSRx5HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth)
{
    DWORD ulTMDSClkValue = 0;
    WORD usM = 0;
    BYTE ucN = 0;
    BYTE ucDivS = 0;
    BYTE ucFactor = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Fin = TMDS_clk
    // Fref = Fin / N
    // Fvco = Fin * M / N
    // Freq = Fvco / Divs
    //
    // Restriction
    // A. BW = Kvco * Icp * R / (M * 2pi) = 700k (Band10 Kvco = 1880), R = 13k)
    // B. 300MHz < Fvco < 600MHz
    // C. (Fin / N) >= 10 * BW --> (Fin / N) >= 7MHz
    // D. YCbCr 420, Ratio = 2, other case Ratio = 1
    //
    // note 1.   According A, Icp = 2.5 ~ 20 --> 14 <= M <= 111
    // note 2.   According B and note 1. --> 3 <= (Fin / N) <= 42
    // note 3.   According C and note 2. --> 7 <= (Fin / N) <= 42
    // note 4_a. 10bit : (M / N / Divs) = (4 / 5 * Ratio) --> M = N * Divs * (4 / 5 * Ratio), N or Divs: multiple of 5
    // note 4_b. 12bit : (M / N / Divs) = (2 / 3 * Ratio) --> M = N * Divs * (2 / 3 * Ratio), N or Divs: multiple of 3
    // note 4_b. 16bit : (M / N / Divs) = (1 / 2 * Ratio) --> M = N * Divs * (1 / 2 * Ratio), N or Divs: multiple of 2
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // If Measure Divider = /2 then TMDS_CLK x 2, unit:kHz
    if(ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_28_PORT_PAGE74_HDMI_NTX1024TR0, _BIT6) == _BIT6)
    {
        ulTMDSClkValue = (DWORD)_GDI_CLK_KHZ * 1024 * 2 / usTMDSClkCount;
    }
    else
    {
        ulTMDSClkValue = (DWORD)_GDI_CLK_KHZ * 1024 / usTMDSClkCount;
    }

    DebugMessageRx5("TMDS clk", ulTMDSClkValue);
    DebugMessageRx5("Color Depth", ucColorDepth);

    switch(ucColorDepth)
    {
        case _COLOR_DEPTH_10_BITS:

            ucFactor = 5;

            break;

        case _COLOR_DEPTH_12_BITS:

            ucFactor = 3;

            break;

        case _COLOR_DEPTH_16_BITS:

            ucFactor = 2;

            break;

        default:

            return _FALSE;
    }

    // N <= (Fin / 7)
    PDATA_WORD(0) = (ulTMDSClkValue / 7000);

    if(PDATA_WORD(0) < 2)
    {
        return _FALSE;
    }
    else if(PDATA_WORD(0) >= ucFactor)
    {
        // N: Multiple of factor
        PDATA_WORD(0) -= (PDATA_WORD(0) % ucFactor);
    }
    else if(PDATA_WORD(0) > 255)
    {
        // N: Multiple of factor
        PDATA_WORD(0) = 255 - (255 % ucFactor);
    }

    ucN = PDATA_WORD(0);

    // for differenct Divs, find suitable Divs and M
    for(pData[15] = 0; pData[15] <= 254; pData[15] += 2)
    {
        // N or Divs: Multiple of factor
        if(((ucN % ucFactor) == 0x00) || ((pData[15] % ucFactor) == 0x00))
        {
            usM = (WORD)ucN * ((pData[15] == 0) ? 1 : pData[15]) * (ucFactor - 1) / ucFactor;

            // Fvco = Fin * M / N
            PDATA_DWORD(0) = (ulTMDSClkValue * usM / ucN);

            if((PDATA_DWORD(0) >= 300000) && (PDATA_DWORD(0) <= 600000))
            {
                ucDivS = ((pData[15] == 0) ? 1 : pData[15]);
                break;
            }
        }

        if((pData[15] == 254) && (ucDivS == 0))
        {
            DebugMessageRx5("4. PLL Setting Error", 0);
            return _FALSE;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Precise formula of Chrage Pump Current depends on DPM, resistor, and band.                   //
    // If VCO band = 'b00, Icp = (700 * M * 2 * pi) / (778 * 0x01C1[7:5]).                          //
    // If VCO band = 'b01, Icp = (700 * M * 2 * pi) / (1340 * 0x01C1[7:5]).                         //
    // If VCO band = 'b10, Icp = (700 * M * 2 * pi) / (1880 * 0x01C1[7:5]).                         //
    // If VCO band = 'b11, Icp = (700 * M * 2 * pi) / (2340 * 0x01C1[7:5]).                         //
    // 700: DPLL max frequency design target is 700MHz; 778: Frequency curve in band00 is 778MHz.   //
    // Assume DPLL_M=0x13, DPM=0x13+2=21; DPN=2; reg_dpll_vcomd='b01; reg_dpll_rs[2:0]='b011;       //
    // Icp = (700 * 21 * 2 * 3.14) / (1340 * 13)                                                    //
    //////////////////////////////////////////////////////////////////////////////////////////////////

    // Set VCO resister = 3b'011(13K), Capacitor = 2b'11(66pF) (Analog DIC suggust)
    ScalerSetBit(P6E_BE_MN_SCLKG_PLL_CHP, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

    // BW = Kvco * Icp * R / (M * 2pi) = 700k --> Icp = M * BW * 2pi / Kvco / R
    PDATA_WORD(1) = ((DWORD)usM * 700UL * 2 * 314UL * 20) / _PLL_VCO_BAND_10 / ((7 + (ScalerGetBit(P6E_BE_MN_SCLKG_PLL_CHP, (_BIT7 | _BIT6 | _BIT5)) >> 5) * 2) * 100);
    pData[5] = (PDATA_WORD(1) + 25) / 50;
    pData[5] -= ((pData[5] == 0) ? 0 : 1);

    if(pData[5] > 0x07)
    {
        pData[5] = 0x07;
    }

    DebugMessageRx5("Deep Color Charge Pump icp =", pData[5]);

    // DPPLL Power Down
    ScalerSetByte(P6E_BD_MN_SCLKG_PLL_PWR, 0x80);

    // Disable M/N Tracking
    ScalerSetBit(P6E_A7_MN_SCLKG_TRK_CTRL, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set PLL Charge Pump Current
    ScalerSetBit(P6E_BE_MN_SCLKG_PLL_CHP, ~(_BIT2 | _BIT1 | _BIT0), (pData[5] & 0x07));

    // Set VCOMD, phase Swallow Circuit Clock Select, SCLKGSTOP
    ScalerSetBit(P6E_BF_MN_SCLKG_PLL_WD, ~(0x7F), 0x16);

    // Set DPPLL Div_2 & Div_s
    ScalerSetByte(P6E_A3_MN_SCLKG_DIVS, (ucDivS >> 1));

    // Set DPPLL Div_O.
    ScalerSetBit(P6E_BD_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0), (0 & (_BIT1 | _BIT0)));

    // Offset Value Setting
    ScalerSetByte(P6E_A6_MN_SCLKG_OFFS_L, 0);
    ScalerSetByte(P6E_A5_MN_SCLKG_OFFS_M, 0);
    ScalerSetBit(P6E_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P6E_A7_MN_SCLKG_TRK_CTRL, ~(_BIT1 | _BIT0), 0x00);

    // Enable phase swallow
    ScalerSetBit(P6E_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), _BIT4);

    // Set DPPLL M Code
    ScalerSetBit(P6E_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), (HIBYTE(usM - 2) & 0x03));
    ScalerSetByte(P6E_A1_MN_SCLKG_DIVM, LOBYTE(usM - 2));

    // Set DPPLL N Code
    ScalerSetByte(P6E_A2_MN_SCLKG_DIVN, (ucN - 2));

    // PLL Input Clock select to Link Clock, Output Clock Select to PLL Clock, Double Buffer.
    ScalerSetBit(P6E_A0_MN_SCLKG_CTRL, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

    // Load offset value
    ScalerSetBit(P6E_A4_MN_SCLKG_OFFS_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

    // Double Buffer for M/N Tracking
    ScalerSetBit(P6E_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(P6E_C0_MN_SCLKG_PLL_INSEL, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL Power On
    ScalerSetBit(P6E_BD_MN_SCLKG_PLL_PWR, ~_BIT7, 0x00);

    ScalerTimerDelayXms(2);

    ////////////////////////////////
    // DPPLL VCO Band Calibration //
    ////////////////////////////////

    // Reg DPLL_CMPEN
    ScalerSetBit(P6E_BD_MN_SCLKG_PLL_PWR, ~_BIT2, _BIT2);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALLCH
    ScalerSetBit(P6E_BD_MN_SCLKG_PLL_PWR, ~_BIT3, _BIT3);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALSW
    ScalerSetBit(P6E_BD_MN_SCLKG_PLL_PWR, ~_BIT4, _BIT4);

    // Check VCO Band is '10
    if(ScalerGetBit(P6E_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) != _BIT5)
    {
        switch(ScalerGetBit(P6E_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) >> 4)
        {
            case 00:

                PDATA_WORD(0) = _PLL_VCO_BAND_00;
                break;

            case 01:

                PDATA_WORD(0) = _PLL_VCO_BAND_01;
                break;

            case 10:

                PDATA_WORD(0) = _PLL_VCO_BAND_10;
                break;

            case 11:

                PDATA_WORD(0) = _PLL_VCO_BAND_11;
                break;

            default:
                PDATA_WORD(0) = _PLL_VCO_BAND_10;
                break;
        }

        PDATA_WORD(1) = ((DWORD)usM * 700UL * 2 * 314UL * 20) / PDATA_WORD(0) / ((7 + (ScalerGetBit(P6E_BE_MN_SCLKG_PLL_CHP, (_BIT7 | _BIT6 | _BIT5)) >> 5) * 2) * 100);

        DebugMessageRx5("4. reset Icp", PDATA_WORD(1));

        pData[5] = (PDATA_WORD(1) + 25) / 50;
        pData[5] -= ((pData[5] == 0) ? 0 : 1);

        if(pData[5] > 0x07)
        {
            pData[5] = 0x07;
        }

        // Set PLL Charge Pump Current
        ScalerSetBit(P6E_BE_MN_SCLKG_PLL_CHP, ~(_BIT2 | _BIT1 | _BIT0), (pData[5] & 0x07));

        DebugMessageRx5("4. VCO is not band10, reset Icp", pData[5]);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Hdmi Handle AVMute Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5HdmiAVMuteProc(void)
{
    // if AVMute Has been triggered
    if((ScalerGetBit(P74_CB_HDMI_SR, _BIT6) == 0x00) && (ScalerGetBit(P74_A6_TMDS_OUTCTL, (_BIT6 | _BIT5 | _BIT4)) == 0x00))
    {
        // Clear AVMute Flag
        ScalerSetBit(P74_CB_HDMI_SR, ~_BIT7, _BIT7);

        // Disable AVMute Watch Dog
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~_BIT7, 0x00);

        // Enable Video/Audio Output
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_30_PORT_PAGE74_HDMI_AVMCR, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));

        // Enable RGB Output
        ScalerSetBit(P74_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

        // Enable AVMute Watch Dog
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~_BIT7, _BIT7);
    }
}

#if(_D5_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Read Request Outcome Case Processing(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5ReadRequestProc_EXINT0(BYTE ucRROutCome) using 1
{
    // Get Read Request Outcome Case
    switch(ucRROutCome)
    {
        case _HDMI_2_0_READ_REQUEST_ACK_DONE:
        case _HDMI_2_0_READ_REQUEST_ACK_STOP:

            break;

        case _HDMI_2_0_READ_REQUEST_NACK1:

            if(GET_HDMI_2_0_RX5_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P74_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);
            }

            break;

        case _HDMI_2_0_READ_REQUEST_NACK2:

#if(_WD_TIMER_INT_SUPPORT == _ON)
            if(GET_HDMI_2_0_RX5_RR_ENABLE() == _TRUE)
            {
                // Enable Read Request Retry
                ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_RX5_HDMI_RR_RETRY);
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
void ScalerTMDSRx5HDMI2HPDRRIRQEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set HPD Debounce = 700 Clock Cycle
        // Set HPD IRQ Detect Rising to Falling Edge IRQ
        ScalerSetBit(P74_23_HDMI_CTRL_23, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT5 | _BIT4 | _BIT3 | _BIT1));

        // Enable HDMI HPD IRQ Enable
        ScalerSetBit(P74_23_HDMI_CTRL_23, ~_BIT6, _BIT6);

        // Write 1 Clear Read Request
        ScalerSetBit(P74_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Enable HDMI 2.0 SCDC IIC Module
        ScalerSetBit(P74_19_HDMI_CTRL_19, ~_BIT7, _BIT7);

        // Clear HDMI 2.0 Read Request Enable
        CLR_HDMI_2_0_RX5_RR_ENABLE();

        // Enable HDMI 2.0 Read Request Enable Detect IRQ
        ScalerSetBit(P74_26_HDMI_CTRL_26, ~_BIT3, _BIT3);
    }
    else
    {
        // Write 1 Clear Read Request
        ScalerSetBit(P74_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Clear HDMI 2.0 Read Request Enable
        CLR_HDMI_2_0_RX5_RR_ENABLE();

        // Disable HDMI 2.0 Read Request Enable Detect IRQ
        ScalerSetBit(P74_26_HDMI_CTRL_26, ~_BIT3, 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Read Request Timer Event Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5ReadRequestTimerEventEnable_WDINT(bit bEnable) using 3
{
    if(bEnable == _ENABLE)
    {
        if(GET_HDMI_2_0_RX5_RR_ENABLE() == _TRUE)
        {
            // FW Manual Enable Read Request
            ScalerSetBit_EXINT(P74_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);
        }
    }
    else
    {
        // Disable Read Request Enable
        ScalerSetBit_EXINT(P74_1B_HDMI_CTRL_1B, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : TMDS Format Reset Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5Hdmi2FormatResetEvent(void)
{
    CLR_TMDS_RX5_HDMI_2_0_FORMAT_RESET_WAITING();
}
#endif // End of #if(_D5_HDMI_2_0_SUPPORT == _ON)

#endif // End of #if(_D5_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS Power Saving Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5PowerSavingProc(void)
{
    // Set Power Saving DDC Debounce Counter
    g_usDDCDebounceCnt = _TMDS_DDC_DEBOUNCE_PS;

    ScalerTMDSRx5FreqDetectDisable();

    // Switch TMDS Input/Output to Auto
    ScalerSetBit(P74_A6_TMDS_OUTCTL, ~_BIT7, _BIT7);
    ScalerSetBit(P74_A7_TMDS_PWDCTL, ~_BIT4, _BIT4);

    // Set Freq. Stable Time: 5 times
    ScalerSetByte(P74_EC_HDMI_FREQDET_STABLE, 0x05);

    // Set Freq. Shift Offset to Max
    ScalerSetBit(P74_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Set Upper Bound
        ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_PS_UPPER_BOUND));
        ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_PS_UPPER_BOUND));
    }
    else
#endif
    {
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
        // Set Upper Bound
        ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));
        ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));
#else
        ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_PS_LOW_SPEED_UPPER_BOUND));
        ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_PS_LOW_SPEED_UPPER_BOUND));
#endif
    }

    // Set Lower Bound
    ScalerSetByte(P74_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_PS_LOWER_BOUND));
    ScalerSetByte(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_PS_LOWER_BOUND));
}

//--------------------------------------------------
// Description  : TMDS Freq. Detection IRQ Disable and Clear Clock Counter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5FreqDetectDisable(void)
{
    // Disable TMDS Freq. Detect IRQ
    ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);
    ScalerSetBit(P74_EF_HDMI_ERROR_TH, ~_BIT7, 0x00);

    // Clear TMDS Clk Count
    g_usTMDSRx5ClkCount = 0;

    // Clear PHY SET flag
    CLR_TMDS_RX5_PHY_SET();

    // Disable HDMI MAC Power
    ScalerSetBit(P74_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable CED Function
    ScalerSetBit(P74_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // Pop Up CED Error For Clear Error Counter
    ScalerSetBit(P74_0C_HDMI_CTRL_0C, ~_BIT7, _BIT7);

    // Disable CED Lock Transition IRQ & Flag
    ScalerSetBit(P74_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P74_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Set Read Request 1ms reference clock to internal OSC
    ScalerSetBit(P74_1A_HDMI_CTRL_1A, ~_BIT3, _BIT3);

    // Set time interval form bus free to Read Request(4.7us~500us)
    ScalerSetBit(P74_1B_HDMI_CTRL_1B, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));
}

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
//--------------------------------------------------
// Description  : TMDS Port Source/Sync Scanning and Setting
// Input Value  : Input Port
// Output Value : Source DVI --> DVI Format
//                Source HDMI --> HDMI Format
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerTMDSRx5TMDSScanInputPort(BYTE ucInputType)
{
    BYTE ucTMDSType = _SOURCE_NONE;

    BYTE ucTMDSVideoDataType = _TMDS_VIDEO_DATA_NONE;

#if(_D5_HDMI_SUPPORT == _ON)
    WORD usInputPixelClk = 0;
#endif

    ucInputType = ucInputType;

    if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        return _SOURCE_NONE;
    }

    if(GET_TMDS_RX5_PHY_SET() == _TRUE)
    {
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
        {
            // Set DIGITAL_PORT_SWITCH Flag for MHL
            SET_DIGITAL_PORT_SWITCH_TO_D5();
        }
#endif

        // Delay for PHY Stable
        ScalerTimerDelayXms(2);

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

#if(_D5_HDMI_2_0_SUPPORT == _ON)

        if((ScalerTMDSRx5CheckCDRStable(g_usTMDSRx5ClkCount) == _FALSE) || (ScalerTMDSRx5CheckDataDFE() == _FALSE) ||
           ((GET_D5_TMDS_MODE() == _TMDS_MHL_MODE) && (ScalerMHLRx5DetectClkMode() == _FALSE)) ||
           (ScalerTMDSRx5TMDSVideoDetect(_WAIT) == _TMDS_VIDEO_DATA_NONE))

#else

        // Detect MHL Mode
        if((ScalerTMDSRx5CheckCDRStable(g_usTMDSRx5ClkCount) == _FALSE) || (ScalerTMDSRx5CheckDataDFE() == _FALSE) ||
           ((GET_D5_TMDS_MODE() == _TMDS_MHL_MODE) && (ScalerMHLRx5DetectClkMode() == _FALSE)))

#endif

#else // Else of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

#if(_D5_HDMI_2_0_SUPPORT == _ON)

        if((ScalerTMDSRx5CheckCDRStable(g_usTMDSRx5ClkCount) == _FALSE) || (ScalerTMDSRx5CheckDataDFE() == _FALSE) || (ScalerTMDSRx5TMDSVideoDetect(_WAIT) == _TMDS_VIDEO_DATA_NONE))
#else
        if((ScalerTMDSRx5CheckCDRStable(g_usTMDSRx5ClkCount) == _FALSE) || (ScalerTMDSRx5CheckDataDFE() == _FALSE))
#endif

#endif // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        {

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

            if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                // Set Upper Bound
                ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
                ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
            }
            else
#endif
            {
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
            }

            // Set Lower Bound
            ScalerSetByte(P74_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
            ScalerSetByte(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

            // Set Stable Time (0x3F = about 5ms)
            ScalerSetByte(P74_EC_HDMI_FREQDET_STABLE, 0x3F);

            CLR_TMDS_RX5_PHY_SET();

            // Disable Freq. Unstable IRQ
            ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

            // Reset Freq. Detect Counter(Toggle)
            ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
            ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

            // Enable Freq. Stable IRQ
            ScalerSetBit(P74_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            return _SOURCE_NONE;
        }

        // Clear RGBHV Flag
        ScalerSetBit(P74_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear Info Packet SRAM
        ScalerSetBit(P74_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P74_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P74_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P74_CC_HDMI_GPVS, ~_BIT5, _BIT5);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
        // Clear DRR flag
        CLR_FREESYNC_ENABLED();
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
        // Clear SPD infoframe
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
        // Clear SPD infoframe
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);
#endif

        DebugMessageRx5("9. Freq Check Pass => Pixel Clock", GET_INPUT_PIXEL_CLK());

#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
        DebugMessageRx5("7. TMDS Lane0 LE Min", g_pucTMDSRx5LEMin[0]);
        DebugMessageRx5("7. TMDS Lane1 LE Min", g_pucTMDSRx5LEMin[1]);
        DebugMessageRx5("7. TMDS Lane2 LE Min", g_pucTMDSRx5LEMin[2]);
#endif

        DebugMessageRx5("7. TMDS Lane0 LE Max", g_pucTMDSRx5LEMax[0]);
        DebugMessageRx5("7. TMDS Lane1 LE Max", g_pucTMDSRx5LEMax[1]);
        DebugMessageRx5("7. TMDS Lane2 LE Max", g_pucTMDSRx5LEMax[2]);

#if(_D5_HDMI_2_0_SUPPORT == _ON)

        // Disable Reset HDMI/DVI Format
        ScalerSetBit(P74_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

        DebugMessageRx5("HDMI 2.0 Error Boundary set High Byte", ScalerGetByte(P74_14_HDMI_CTRL_14));
        DebugMessageRx5("HDMI 2.0 Error Boundary set Low Byte", ScalerGetByte(P74_15_HDMI_CTRL_15));
#endif

        if(ScalerTMDSRx5FormatDetect() == _SOURCE_HDMI)
        {
            DebugMessageRx5("Format Detect HDMI", 0x00);

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
            ScalerSetDataPortBit(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, ~_BIT1, _BIT1);
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
            ScalerSetDataPortBit(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, ~_BIT1, 0x00);
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            if(GET_TMDS_RX5_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
            {
                ucTMDSType = _SOURCE_HDMI;
            }
            else
#endif
            {
                ucTMDSType = _SOURCE_DVI;
            }
        }

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        // Mute ASUS Padfone until Source Read Ri Done (Incase of Color Format Error)
        if(((GET_MHL_RX5_ADOPTER_ID_HBYTE() == _ASUS_PADFONE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX5_ADOPTER_ID_LBYTE() == _ASUS_PADFONE2_ADOPTER_ID_LBYTE)) &&
           !(((ScalerGetBit(P74_A9_TMDS_ABC0, _BIT7) == _BIT7) || (ScalerGetBit(P74_AE_TMDS_RPS, (_BIT1)) == _BIT1)) && (ScalerGetBit(P74_A9_TMDS_ABC0, _BIT6) == _BIT6)))
        {
            return _SOURCE_NONE;
        }
#endif

        ucTMDSVideoDataType = ScalerTMDSRx5TMDSVideoDetect(_WAIT);

        if(ucTMDSVideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
        {
            DebugMessageRx5("DE Only Mode", 0x00);

#if(_DVI_DE_ONLY_SUPPORT == _ON)
            if(ucTMDSType == _SOURCE_DVI)
            {
                // Enable DE Only Mode
                ScalerSetBit(P74_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
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
            ScalerSetBit(P74_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
        }
        else
        {
            return _SOURCE_NONE;
        }

        // [1] De_inverse = 1'b1 --> Adapation Only for Data Area (Transition Minimum)
        // [0] De_brank_en = 1'b1 --> Enable Blank Function of gdi_de
        ScalerSetBit(P7E_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7E_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7E_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_D5_HDMI_SUPPORT == _ON)
        if(ucTMDSType == _SOURCE_HDMI)
        {
            // HDMI packet detect --> AVI infoframe & GCP packet
            ScalerTMDSRx5HdmiPacketDetect(_WAIT);

            ScalerSyncTMDSRx5HdmiVideoSetting();

            SET_COLOR_DEPTH(ScalerTMDSRx5HdmiGetColorDepth());

            if((GET_COLOR_DEPTH() != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422))
            {
                DebugMessageRx5("Deep Color Mode Detected", GET_COLOR_DEPTH());

                // Backup Input Pixel clk
                usInputPixelClk = GET_INPUT_PIXEL_CLK();

                SET_INPUT_PIXEL_CLK((GET_INPUT_PIXEL_CLK() << 3) / GET_COLOR_DEPTH());

                if(ScalerTMDSRx5HdmiDeepColorProc(g_usTMDSRx5ClkCount) == _FALSE)
                {
                    // Restore Input Pixel clk
                    SET_INPUT_PIXEL_CLK(usInputPixelClk);

                    return _SOURCE_NONE;
                }

                // Turn On Deep Color Block
                ScalerSetBit(P74_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            }
            else
            {
                // Turn off Deep Color Block
                ScalerSetBit(P74_B5_TMDS_UDC0, ~_BIT7, 0x00);
            }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
            if(GET_HDMIRX5_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE)
            {
                SET_HDMI_FREESYNC_ENABLED();

                // Get SPD Free Sync Vfreq Max
                g_usFREESYNCVFreq_max = (WORD)GET_HDMIRX5_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MAX_VFREQ) * 10;
                g_usFREESYNCVFreq_min = (WORD)GET_HDMIRX5_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MIN_VFREQ) * 10;

                // Disable DE Only Mode
                ScalerSetBit(P74_A7_TMDS_PWDCTL, ~_BIT7, 0x00);
            }
#endif
        }
        else
        {
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            // Guard Band reference disable for data remapping
            ScalerSetBit(P79_B2_MHL_CTRL_12, ~_BIT7, 0x00);
#endif

            CLR_HDMI_RX5_AVI_INFO_FRAME_RECEIVED();

            CLR_HDMI_RX5_GCP_RECEIVED();

            // Disable All WD when DVI
            ScalerTMDSRx5HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            ScalerTMDSRx5DviVideoSetting();

            SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

            // Turn off Deep Color Block
            ScalerSetBit(P74_B5_TMDS_UDC0, ~_BIT7, 0x00);
        }
#else

        ScalerTMDSRx5DviVideoSetting();

        SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

        // Turn off Deep Color Block
        ScalerSetBit(P74_B5_TMDS_UDC0, ~_BIT7, 0x00);
#endif

        // Enable Video Output
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_30_PORT_PAGE74_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_80_PORT_PAGE74_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P74_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
        // solve philip DVD issue
        if(ScalerGetBit(P7E_E4_GAIN_3, _BIT1) == _BIT1)
        {
            // Disable LE, Vth, Tap0~4 Adaptation
            ScalerSetByte(P7E_A1_L0_DFE_EN_2, 0x00);
            ScalerSetByte(P7E_B1_L1_DFE_EN_2, 0x00);
            ScalerSetByte(P7E_C1_L2_DFE_EN_2, 0x00);

            // [1] reg_en_eqen_manual_l0 = 1'b0
            ScalerSetBit(P7E_12_ANA_CDR, ~_BIT1, 0x00);

            // Enable Sumamp High Gain Mode
            ScalerSetBit(P7E_1D_CMU_03, ~_BIT4, _BIT4);
        }
#endif

        return ucTMDSType;
    }

    return _SOURCE_NONE;
}
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

//--------------------------------------------------
// Description  : Detect TMDS Format
// Input Value  : None
// Output Value : Return DVI or HDMI format
//--------------------------------------------------
BYTE ScalerTMDSRx5FormatDetect(void)
{
    // Polling at least 3 frame for HW auto detect TMDS format
    if(ScalerTimerPollingFlagProc(130, P74_CB_HDMI_SR, _BIT0, _TRUE) == _TRUE)
    {
        ScalerSetBit(P74_AF_TMDS_WDC, ~_BIT0, 0x00);

#if(_D5_HDMI_2_0_SUPPORT == _ON)
        if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
        {
            // Check if HDMI 2.0 ON
            if(ScalerGetBit(P74_00_HDMI_CTRL_00, _BIT0) == _BIT0)
            {
                // Set Manual Format to HDMI
                ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Toggle HW Format Detect Flag Reset
                ScalerSetBit(P74_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
                ScalerSetBit(P74_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

                SET_TMDS_RX5_HDMI_2_0_FORMAT_RESET_WAITING();

                ScalerTimerReactiveTimerEvent(130, _SCALER_TIMER_EVENT_RX5_HDMI2_FORMAT_RESET_WAIT);
            }

            // Detect Scrambling Control Symbol
            if(ScalerGetBit(P74_01_HDMI_CTRL_01, _BIT3) == _BIT3)
            {
                // Enable Scrambling Status in SCDC
                ScalerSetDataPortBit(P74_39_HDMI_CTRL_39, _P74_3A_PT_21_PORT_PAGE74_HDMI_SCDC_21, ~_BIT0, _BIT0);
            }
        }
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
        {
            // Set Manual Format to HDMI
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
        }
#endif
        return _SOURCE_HDMI;
    }
    else
    {
        ScalerSetBit(P74_AF_TMDS_WDC, ~_BIT0, _BIT0);

        if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
        {
#if(_D5_HDMI_2_0_SUPPORT == _ON)
            if(ScalerGetBit(P74_00_HDMI_CTRL_00, _BIT0) == _BIT0)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX5_HDMI2_FORMAT_RESET_WAIT);
            }
#endif
            // Set Format Detect HW Auto Mode
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);
        }
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        else
        {
            // Manual Set to DVI Mode
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT3);
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
bit ScalerTMDSRx5HdcpEnabled(void)
{
    BYTE pucHDCPFrameCount[2];
    memset(pucHDCPFrameCount, 0, sizeof(pucHDCPFrameCount));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    if((ScalerGetBit(P74_C0_HDCP_CR, _BIT0) == _BIT0) && (ScalerGetBit(P6E_26_HDCP_I2C_CTRL_0, _BIT7) == 0x00))
#endif
    {
        ScalerGetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_C0_PORT_PAGE74_HDCP_FCR, 1, &pucHDCPFrameCount[0], _NON_AUTOINC);

        // Wait 2Vsync to make sure frame counter changing, and timeout 45ms (margin + 1/24 frame+rate)
        ScalerSetBit(P74_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
        ScalerTimerPollingFlagProc(45, P74_A4_TMDS_CTRL, _BIT3, _TRUE);
        ScalerSetBit(P74_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
        ScalerTimerPollingFlagProc(45, P74_A4_TMDS_CTRL, _BIT3, _TRUE);

        ScalerGetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_C0_PORT_PAGE74_HDCP_FCR, 1, &pucHDCPFrameCount[1], _NON_AUTOINC);

        if(pucHDCPFrameCount[0] != pucHDCPFrameCount[1])
        {
            return _TRUE;
        }

        return _FALSE;
    }
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    else if((ScalerGetBit(P74_C0_HDCP_CR, _BIT0) == 0x00) && (ScalerGetBit(P6E_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7))
    {
        if(ScalerGetByte(P6E_2C_HDCP_I2C_CTRL_6) == 0x10)
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
bit ScalerTMDSRx5CheckDataDFE(void)
{
    BYTE ucTemp = 0;
    BYTE ucCnt = 0;

    // DFE Check only under HDMI Mode.
    // MHL has only 1 data Lane --> Skip DFE Check Process and Function return True!
    if(ScalerGetBit(P7E_17_BANDGAP_03, _BIT1) != _BIT1)
    {
        for(pData[0] = 0; pData[0] <= 2; pData[0]++)
        {
            // Sel lane
            ScalerSetBit(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), pData[0] << 6);

            // Read VTH
            ScalerSetBit(P7E_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            if((ScalerGetByte(P7E_F1_COEF_2) & 0x1F) == 0)
            {
                for(ucCnt = 0; ucCnt < 3; ucCnt++)
                {
                    // Read TAP0
                    ScalerSetBit(P7E_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ucTemp = (ScalerGetByte(P7E_F1_COEF_2) & 0x1F);

                    if(ucTemp < 21)
                    {
                        return _TRUE;
                    }
                    else if(ucCnt == 2)
                    {
                        DebugMessageRx5("DFE Abnormal ", 0);
                        return _FALSE;
                    }
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
bit ScalerTMDSRx5TMDSStableDetect(BYTE ucSourceType)
{
    // CLR SCL/SDA Toggle Flag
    CLR_TMDS_RX5_DDC_DETECTED();

    if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        DebugMessageRx5("Rx5 HPD Toggle!!", 0);
        return _FALSE;
    }

    if(ScalerTMDSRx5CheckCDRStable(g_usTMDSRx5ClkCount) == _FALSE)
    {
        DebugMessageRx5("CDR Unstable!!", ucSourceType);
        return _FALSE;
    }

    // Check TMDS Clock Output Disable
    if(ScalerGetBit(P74_A6_TMDS_OUTCTL, _BIT3) == 0x00)
    {
        DebugMessageRx5("TMDS Clock Output has been disable", ucSourceType);
        return _FALSE;
    }

#if(_D5_HDMI_2_0_SUPPORT == _ON)

    if((GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE) && (ScalerGetBit(P74_00_HDMI_CTRL_00, _BIT0) == _BIT0))
    {
        if(ucSourceType == _SOURCE_HDMI)
        {
            if(GET_TMDS_RX5_HDMI_2_0_FORMAT_RESET_WAITING() == _FALSE)
            {
                if(ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, _BIT3) != _BIT3)
                {
                    return _FALSE;
                }
                else
                {
                    if(ScalerGetBit(P74_CB_HDMI_SR, _BIT0) == 0x00)
                    {
                        DebugMessageRx5("TMDS Format Changed", ucSourceType);

                        return _FALSE;
                    }
                    else
                    {
                        // Toggle HW Format Detect Flag Reset
                        ScalerSetBit(P74_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
                        ScalerSetBit(P74_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

                        SET_TMDS_RX5_HDMI_2_0_FORMAT_RESET_WAITING();

                        ScalerTimerReactiveTimerEvent(130, _SCALER_TIMER_EVENT_RX5_HDMI2_FORMAT_RESET_WAIT);
                    }
                }
            }
        }
        else
        {
            if(ScalerGetBit(P74_CB_HDMI_SR, _BIT0) == _BIT0)
            {
                DebugMessageRx5("TMDS Format Changed", ucSourceType);
                return _FALSE;
            }
        }
    }
    else
#endif
    {
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        if((GET_TMDS_RX5_CLK_MODE() == _TMDS_24BIT_PHY_SETTING) ||
           ((GET_TMDS_RX5_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING) && (ucSourceType == _SOURCE_DVI)))
#endif
        {
            if(ucSourceType == _SOURCE_HDMI)
            {
                if(ScalerGetBit(P74_CB_HDMI_SR, _BIT0) == 0x00)
                {
                    DebugMessageRx5("TMDS Format Changed", ucSourceType);
                    return _FALSE;
                }
            }
            else
            {
                if(ScalerGetBit(P74_CB_HDMI_SR, _BIT0) == _BIT0)
                {
                    DebugMessageRx5("TMDS Format Changed", ucSourceType);
                    return _FALSE;
                }
            }
        }
    }

    if(GET_TMDS_RX5_Z0_ASSERTED() == _TRUE)
    {
        if((ScalerGetBit(P74_A9_TMDS_ABC0, _BIT6) == _BIT6) && (!((((ScalerGetBit(P74_A9_TMDS_ABC0, _BIT7)) == _BIT7) || ((ScalerGetBit(P74_AE_TMDS_RPS, _BIT1)) == _BIT1)) && ((ScalerGetBit(P74_A9_TMDS_ABC0, _BIT5)) == _BIT5))))
        {
            SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            CLR_TMDS_RX5_Z0_ASSERTED();

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)

            SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            CLR_TMDS_RX4_Z0_ASSERTED();
#endif

            DebugMessageRx5("7. HDCP Abnormal !!!!!", 0);

            // MHL mode of MHL PORT will not return FALSE
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
                return _FALSE;
            }
#else
            return _FALSE;
#endif
        }
        else if(((ScalerGetBit(P74_A9_TMDS_ABC0, _BIT7) == (_BIT7)) || (ScalerGetBit(P74_AE_TMDS_RPS, _BIT1) == (_BIT1))) && (ScalerGetBit(P74_A9_TMDS_ABC0, _BIT5) == (_BIT5)))
        {
            CLR_TMDS_RX5_Z0_ASSERTED();

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)

            CLR_TMDS_RX4_Z0_ASSERTED();
#endif

            DebugMessageRx5("7. HDCP Normal", 0);
        }
    }

    if(ucSourceType == _SOURCE_DVI)
    {
        if(GET_TMDS_RX5_RGBHV_DETECTING() == _FALSE)
        {
            // TMDS Video Detected
#if(_DVI_DE_ONLY_SUPPORT == _OFF)
            if(ScalerTMDSRx5TMDSVideoDetect(_NOT_WAIT) != _TMDS_VIDEO_DATA_RGBHV)
#else
            if(ScalerTMDSRx5TMDSVideoDetect(_NOT_WAIT) == _TMDS_VIDEO_DATA_NONE)
#endif
            {
                DebugMessageRx5("TMDS Video format changed", ucSourceType);

                return _FALSE;
            }
        }
    }

#if(_D5_HDMI_SUPPORT == _ON)

    if(ucSourceType == _SOURCE_HDMI)
    {
        if(GET_HDMI_RX5_PACKET_DETECTING() == _FALSE)
        {
            // HDMI Packet Detected
            ScalerTMDSRx5HdmiPacketDetect(_NOT_WAIT);

            if(GET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED() == _TRUE)
            {
                if(ScalerSyncTMDSRx5HdmiColorInfoChanged() == _TRUE)
                {
                    DebugMessageRx5("Color Info Changed", ucSourceType);
                    return _FALSE;
                }

                if(ScalerTMDSRx5HdmiAviPixelRepInfoChanged() == _TRUE)
                {
                    DebugMessageRx5("Pixel Repetition Info Changed", ucSourceType);
                    return _FALSE;
                }
            }
            else
            {
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                if(GET_TMDS_RX5_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
#endif
                {
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                    {
                        DebugMessageRx5("HDMI Info Frame Not Received and not RGB", ucSourceType);
                        return _FALSE;
                    }
                }

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
                if(GET_COLOR_RGB_QUANTIZATION_RANGE() != _RGB_QUANTIZATION_RESERVED)
                {
                    DebugMessageRx5("No Quantization Range Specified", ucSourceType);
                    return _FALSE;
                }
#endif

                if(GET_TMDS_RX5_AVI_PIXEL_REPETITION() != _AVI_PIXEL_REPETITION_0)
                {
                    DebugMessageRx5("Pixel Repetition Not Received and not Pixel repetition 0", ucSourceType);
                    return _FALSE;
                }
            }

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                if((ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_41_PORT_PAGE74_HDMI_VWDSR, _BIT0) == _BIT0) && (ScalerGetBit(P74_CC_HDMI_GPVS, _BIT0) == _BIT0))
                {
                    DebugMessageRx5("HDMI AVI info frame has changed", ucSourceType);
                    return _FALSE;
                }
            }

            if(GET_HDMI_RX5_GCP_RECEIVED() == _TRUE)
            {
                if((GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422) && (ScalerTMDSRx5HdmiGetColorDepth() != GET_COLOR_DEPTH()))
                {
                    DebugMessageRx5("Color Depth Has Changed", GET_COLOR_DEPTH());
                    return _FALSE;
                }
            }
            else
            {
                if((GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422) && (GET_COLOR_DEPTH() != _COLOR_DEPTH_8_BITS))
                {
                    DebugMessageRx5("HDMI GCP PACKET Not Received and not 8 bit", ucSourceType);
                    return _FALSE;
                }
            }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
            if(GET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED() == _TRUE)
            {
                if((bit)GET_HDMIRX5_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) != GET_HDMI_FREESYNC_ENABLED())
                {
                    DebugMessageRx5("HDMI Freesync Status Change", GET_HDMI_FREESYNC_ENABLED());
                    return _FALSE;
                }
            }
            else
            {
                if(GET_HDMI_FREESYNC_ENABLED() == _TRUE)
                {
                    DebugMessageRx5("HDMI Freesync Status Change", GET_HDMI_FREESYNC_ENABLED());
                    return _FALSE;
                }
            }
#endif
        }
    }

#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)

    if(GET_TMDS_RX5_TOGGLE_Z0() == _TRUE)
    {
        SET_TMDS_RX5_TOGGLE_Z0_EVENT();

        return _FALSE;
    }

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)

    if(GET_TMDS_RX4_TOGGLE_Z0() == _TRUE)
    {
        SET_TMDS_RX4_TOGGLE_Z0_EVENT();

        return _FALSE;
    }
#endif

#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : TMDS Hot Plug Event
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerTMDSRx5HotPlugEvent(void)
{
    ScalerTMDSRx5BeforeHotPlugEventProc();

    // ACER mode and DVI port will only toggle Z0 130ms
#if((_D5_INPUT_PORT_TYPE == _D5_DVI_PORT) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
    if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
    {
        // MHL mode of MHL PORT can not pull HPD
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D5_CABLE_STATUS() == _TRUE) && (GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D5_CABLE_STATUS() == _TRUE))
#endif
        {
            ScalerTimerDelayXms(_TMDS_ACER_HPD_TIME);
        }
    }
    else
#endif
    {
        // HPD Low
        ScalerTMDSRx5HotPlugLowProc();

        // wait
        if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
        {
            ScalerTMDSRx5HotPlugHighProc(GET_HDMI_HOTPLUG_TIME());
        }
        else if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
        {
            ScalerTMDSRx5HotPlugHighProc(_TMDS_HDCP_2_2_HPD_TIME);
        }
        else if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
        {
            ScalerTMDSRx5HotPlugHighProc(_TMDS_ACER_HPD_TIME);
        }
        else if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() == _TMDS_HPD_EDID_SWITCH)
        {
            ScalerTMDSRx5HotPlugHighProc(_TMDS_EDID_SWITCH_HPD_TIME);
        }
        else
        {
            ScalerTMDSRx5HotPlugHighProc(GET_HDMI_HOTPLUG_TIME());
        }
    }

    // Restore Slave Address and Z0 Status
    ScalerTMDSRx5AfterHotPlugEventProc();

    DebugMessageRx5("Rx5 HPD Toggle!!", 0);

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
    if(GET_TMDS_RX5_TOGGLE_Z0_EVENT() == _TRUE)
    {
        CLR_TMDS_RX5_TOGGLE_Z0();
        CLR_TMDS_RX5_TOGGLE_Z0_EVENT();
    }
#endif

    CLR_TMDS_RX5_HPD_TRIGGER_EVENT();
}

//--------------------------------------------------
// Description  : TMDS Switch Slave Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5SwitchSlaveAddr(void)
{
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_C2_PORT_PAGE74_HDCP_SLAVE_ADD, 0x7F);
}

//--------------------------------------------------
// Description  : TMDS Before Hot Plug Event Process
// Input Value  : None
// Output Value : Hot Plug time
//--------------------------------------------------
void ScalerTMDSRx5BeforeHotPlugEventProc(void)
{
    // MHL mode of MHL PORT can not pull HPD
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D5_CABLE_STATUS() == _TRUE) && (GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D5_CABLE_STATUS() == _TRUE))
#endif
    {
        // Save Z0 Status
        g_ucTMDSRx5Z0Status = ScalerGetBit(P7E_18_IMPEDANCE_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Backup Slave Address
        ScalerGetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_C2_PORT_PAGE74_HDCP_SLAVE_ADD, 1, &g_ucTMDSRx5SlaveAddr, _NON_AUTOINC);

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)))
        // Reset HDCP 2.2
        ScalerTMDSRx5Hdcp2ResetProc();
#endif

#if(_D5_HDMI_2_0_SUPPORT == _ON)
        // Disable HDMI 2.0 SCDC Function
        ScalerSetBit(P74_19_HDMI_CTRL_19, ~_BIT7, 0x00);
#endif

        // Disable Z0
        ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
    else if(GET_D5_CABLE_STATUS() == _FALSE)
    {
        // Reset DDC5
        MCU_FE80_DDC5_DDC_CONTROL_1 |= _BIT1;
    }
}

//--------------------------------------------------
// Description  : TMDS After Hot Plug Event Process
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerTMDSRx5AfterHotPlugEventProc(void)
{
    // MHL mode of MHL PORT can not pull HPD
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D5_CABLE_STATUS() == _TRUE) && (GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D5_CABLE_STATUS() == _TRUE))
#endif
    {
        // Restore Slave Address
        ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_C2_PORT_PAGE74_HDCP_SLAVE_ADD, g_ucTMDSRx5SlaveAddr);

#if(_D5_HDMI_2_0_SUPPORT == _ON)
        // Enable HDMI 2.0 SCDC Function
        ScalerSetBit(P74_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
#endif

        // Restore Z0 Status
        ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), g_ucTMDSRx5Z0Status);
    }
}

//--------------------------------------------------
// Description  : HDCP 1.4 R0 IIC 20k issue Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5Hdcp1p4AksvClear(void)
{
    // Disable R0 ready bit
    ScalerSetBit(P74_AE_TMDS_RPS, ~_BIT1, 0x00);
}

#endif // End of #if(_D5_TMDS_SUPPORT == _ON)
