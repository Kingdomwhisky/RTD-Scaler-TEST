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
// ID Code      : RL6463_Series_TMDS.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6463_SERIES_TMDS__

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
WORD g_usTMDSClkCount;
BYTE g_ucTMDSClkIRQ;

#if(_D0_TMDS_SUPPORT == _ON)
BYTE g_ucTMDSRx0Z0Status;
#endif
#if(_D1_TMDS_SUPPORT == _ON)
BYTE g_ucTMDSRx1Z0Status;
#endif
BYTE g_ucTMDSSlaveAddr;

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
bit ScalerTMDSStableDetect(BYTE ucInputPort, BYTE ucSourceType);
void ScalerTMDSHotPlugEvent(BYTE ucPortSelect);
void ScalerTMDSSwitchSlaveAddr(BYTE ucPortSelect);
void ScalerTMDSBeforeHotPlugEventProc(BYTE ucPortSelect);
void ScalerTMDSAfterHotPlugEventProc(BYTE ucPortSelect);
void ScalerTMDSBEDCheck(void);
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

    // BED enable for Data Rate >= 700
    if(GET_INPUT_PIXEL_CLK() >= 700)
    {
        // BED counter period set 1 frame
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_B5_PORT_PAGE2_HDMI_BED_FUNC_6, ~(_BIT7 | _BIT6), 0x00);

        // Enable BED Double buffer and Valid Period Type by Frame(by Vsync)
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_AF_PORT_PAGE2_HDMI_BED_FUNC_0, ~(_BIT3 | _BIT1 | _BIT0), _BIT3);
    }

    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), 0x00);
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), _BIT1);
#endif
            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), 0x00);
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
            ScalerSetBit(P2_C2_HDCP_PCR, ~(_BIT2 | _BIT1), _BIT1);
#endif
            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

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

    // MAC Select to HDMI
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT0, _BIT0);

    // PHY Select to HDMI
    ScalerSetBit(PB_A5_DIG_05, ~_BIT7, _BIT7);

    // Analog Select to HDMI
    ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT5, 0x00);

    // Termination to VDD
    ScalerSetBit(PB_BF_CMU_02, ~(_BIT5 | _BIT4), 0x00);

    // Disable HDMI MAC Global Power Down
    ScalerSetBit(P2_AD_TMDS_CPS, ~_BIT1, 0x00);

    // Enable MAC Input
    ScalerSetBit(P2_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set MAC Signal Swap
    ScalerSetBit(P2_A7_TMDS_PWDCTL, ~(_BIT6 | _BIT5), ((ucInputPort == _D0_INPUT_PORT) ? ((_D0_TMDS_BR_SWAP << 6) | (_D0_TMDS_PN_SWAP << 5)) : ((_D1_TMDS_BR_SWAP << 6) | (_D1_TMDS_PN_SWAP << 5))));

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
    // Enable INT Clock Check
    g_ucTMDSClkIRQ = _ENABLE;

    ucInputPort = ucInputPort;

    if(ScalerGetBit(P2_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
    {
        CLR_TMDS_PHY_SET();
    }

    // Enable Rx_En for Clk pair Z0
    ScalerSetBit(PB_C0_CMU_03, ~_BIT7, _BIT7);

    // Set Reg_bypass_ok=1 for solve P/N short(480p issue)
    ScalerSetBit(PB_C1_CMU_04, ~_BIT0, _BIT0);

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
    if(GET_INPUT_PIXEL_CLK() < 375)
    {
        // LE  Initial = 4
        ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x04);
        ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x04);
        ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x04);
    }
    else if(GET_INPUT_PIXEL_CLK() < 700)
    {
        // LE  Initial = 6
        ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x06);
        ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x06);
        ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x06);
    }
    else
    {
        // Change to T-switch to solve interference but input BW loss more 2dB
        if(ScalerGlobalGetIDCode_EXINT0() >= _RL6463_VER_C_ID_CODE)
        {
            // LE Initial = 11
            ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x0B);
            ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x0B);
            ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x0B);
        }
        else
        {
            // LE Initial = 9
            ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x09);
            ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x09);
            ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x09);
        }
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

    // [7:4] rx_en = 4'b1111 --> Enable RXEN
    ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [3] sel_iblpf = 1 --> Enable Local Bias LPF
    ScalerSetBit_EXINT(PB_B5_BANDGAP_01, ~_BIT3, _BIT3);

    DELAY_45US_EXINT();

    // [3:0] cdr_en = 4'b0001 ~ 4'b0011 ~ 4'b0111 ~ 4'b1111
    ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Recover Reg_bypass_ok=0 before koffset and after cdr_en=1
    // for solve P/N short(480p issue)
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT0, 0x00);

    /////////////////
    // CMU Setting //
    /////////////////

    // [0] PLL_WD_EN = 1'b0 --> Disable WD
    ScalerSetBit_EXINT(PB_AF_WD, ~_BIT0, 0x00);

    // [7] sel_in_div4 = 0 --> Input Ref. Clock/1
    // [3] CMU_SEL_D4 = 0 --> CMU Feedback Loop/1
    ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT7 | _BIT3), 0x00);

    // [7:6] CMU_SEL_CP = 2'b10 --> CMU LPF Cp = 2pF
    ScalerSetBit_EXINT(PB_C3_CMU_06, ~(_BIT7 | _BIT6), _BIT7);

    // [3:0] cdr_cp_in = 4'b1100 --> Icp = 37.5uA
    ScalerSetBit_EXINT(PB_D1_ANA_CDR_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

    // [3] en_largers_forcmu = 1 --> CMU Rs increase 8K
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT3, _BIT3);

    // [6:4] CMU_SEL_R1 = 3'b110 --> CMU LPF Rs = 16K + 8K
    ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    if((GET_INPUT_PIXEL_CLK() >= 187) && (GET_INPUT_PIXEL_CLK() < 375))
    {
        // Analog CDR Auto FLD Counter
        // ref_conuter = 30
        // cdr_counter = 480
        // 30/480 = 1/16 = 5*(1/80 clock rate)
        ScalerSetBit_EXINT(PB_D5_ANA_CDR_07, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetByte_EXINT(PB_D6_ANA_CDR_08, 0x1D);
        ScalerSetByte_EXINT(PB_D7_ANA_CDR_09, 0xDF);

        // [2:0] rate_sel = 3'b100 --> 187.5MHz ~ 375MHz
        ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

        // [1:0] SEL_DIV = 2'b11 --> 187.5MHz ~ 375MHz
        ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // [5:4] CMU_SELPREDIV = 2'b00 --> /1
        ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), 0x00);

        // [7:0] N_CODE = 0x4C --> 76 + 4 = 80
        ScalerSetByte_EXINT(PB_BE_CMU_01, 0x4C);
    }
    else if((GET_INPUT_PIXEL_CLK() >= 375) && (GET_INPUT_PIXEL_CLK() < 750))
    {
        // Analog CDR Auto FLD Counter
        // ref_conuter = 50
        // cdr_counter = 400
        // 50/400 = 1/8 = 5*(1/40 clock rate)
        ScalerSetBit_EXINT(PB_D5_ANA_CDR_07, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetByte_EXINT(PB_D6_ANA_CDR_08, 0x31);
        ScalerSetByte_EXINT(PB_D7_ANA_CDR_09, 0x8F);

        // [2:0] rate_sel = 3'b011 --> 375MHz ~ 750MHz
        ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

        // [1:0] SEL_DIV = 2'b10 --> 375MHz ~ 750MHz
        ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT1 | _BIT0), _BIT1);

        // [5:4] CMU_SELPREDIV = 2'b01 --> /1
        ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), 0x00);

        // [7:0] N_CODE = 0x4C --> 36 + 4 = 40
        ScalerSetByte_EXINT(PB_BE_CMU_01, 0x24);
    }
    else if((GET_INPUT_PIXEL_CLK() >= 750) && (GET_INPUT_PIXEL_CLK() < 1500))
    {
        // Analog CDR Auto FLD Counter
        // ref_conuter = 125
        // cdr_counter = 500
        // 125/500 = 1/4 = 5*(1/20 clock rate)
        ScalerSetBit_EXINT(PB_D5_ANA_CDR_07, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetByte_EXINT(PB_D6_ANA_CDR_08, 0x7C);
        ScalerSetByte_EXINT(PB_D7_ANA_CDR_09, 0xF3);

        // [2:0] rate_sel = 3'b010 --> 750MHz ~ 1500MHz
        ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // [1:0] SEL_DIV = 2'b01 --> 750MHz ~ 1500MHz
        ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT1 | _BIT0), _BIT0);

        // [5:4] CMU_SELPREDIV = 2'b01 --> /1
        ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), 0x00);

        // [7:0] N_CODE = 0x4C --> 16 + 4 = 20
        ScalerSetByte_EXINT(PB_BE_CMU_01, 0x10);
    }
    else if((GET_INPUT_PIXEL_CLK() >= 1500) && (GET_INPUT_PIXEL_CLK() < 3000))
    {
        // Analog CDR Auto FLD Counter
        // ref_conuter = 250
        // cdr_counter = 500
        // 250/500 = 1/2 = 5*(1/10 clock rate)
        ScalerSetBit_EXINT(PB_D5_ANA_CDR_07, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetByte_EXINT(PB_D6_ANA_CDR_08, 0xF9);
        ScalerSetByte_EXINT(PB_D7_ANA_CDR_09, 0xF3);

        // [2:0] rate_sel = 3'b001 --> 1500MHz ~ 3000MHz
        ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

        // [1:0] SEL_DIV = 2'b00 --> 1500MHz ~ 3000MHz
        ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT1 | _BIT0), 0x00);

        // [5:4] CMU_SELPREDIV = 2'b01 --> /2
        ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), _BIT4);

        // [7:0] N_CODE = 0x4C --> 16 + 4 = 20
        ScalerSetByte_EXINT(PB_BE_CMU_01, 0x10);
    }

    /////////////////
    // FLD Setting //
    /////////////////

    // [1:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 700M/v
    ScalerSetBit_EXINT(PB_D0_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);

    // [4] reg_sel_cont3 = 1'b1 --> BBPD UP/DN Pulse Div 3
    ScalerSetBit_EXINT(PB_D4_ANA_CDR_06, ~_BIT7, _BIT7);


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
        // KP_L0 = 5
        // KP_L1 = 5
        // KP_L2 = 5
        ScalerSetByte_EXINT(PB_F6_CDR_07, 0x14);
        ScalerSetByte_EXINT(PB_F7_CDR_08, 0x14);
        ScalerSetByte_EXINT(PB_F8_CDR_09, 0x14);
    }

    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [1] bypass_clk_rdy = 1 --> manual mode
    // [0] en_clkout_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB_AE_SDM_04, ~(_BIT1 | _BIT0), _BIT1);

    // [1] bypass_eqen_rdy = 1 --> manual mode
    // [0] en_eqen_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~(_BIT1 | _BIT0), _BIT1);

    // [1] bypass_data_rdy = 1 --> manual mode
    // [0] en_data_manual = 0 --> Disable Dataout
    ScalerSetBit_EXINT(PB_B1_DATA_TIMER, ~(_BIT1 | _BIT0), _BIT1);

    // [7] Disable Hybrid Mode
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT7, 0x00);

    // [4] Disable Lane0 ACDR
    ScalerSetBit_EXINT(PB_B2_ANA_CDR, ~_BIT4, 0x00);

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

    if(GET_INPUT_PIXEL_CLK() < 2000)
    {
        // [7:5] LE_ISEL = 3'b000
        ScalerSetBit_EXINT(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [7:5] LE_RLSEL = 3'b011
        ScalerSetBit_EXINT(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));
    }
    else
    {
        // [7:5] LE_ISEL = 3'b010
        ScalerSetBit_EXINT(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

        // [7:5] LE_RLSEL = 3'b001
        ScalerSetBit_EXINT(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
    }

    //////////////
    // K Offset //
    //////////////

    // Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(PB_C9_KOFFSET_03, ~_BIT6, 0x00);

    // [6] Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT6, _BIT6);

    // [7] Toggle Foreground Calibration
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);

    // Waiting for K Offset
    DELAY_XUS_EXINT(150);

    // [2:0] Enable Tap0~2
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Reset Digital CDR
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    ///////////////////
    // FLD Lock Band //
    ///////////////////

    // [2] reg_cp_en_manual = 1'b0 -->  Disable cp_en_manual
    // [1] reg_ac_en_manual = 0 --> Disable adp_en_manual
    // [3] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    ScalerSetBit_EXINT(PB_CF_ANA_CDR_01, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

    // [5] lane_en = 1 --> Enable FLD
    ScalerSetBit_EXINT(PB_B2_ANA_CDR, ~_BIT5, _BIT5);

    // [7] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT7, _BIT7);

    // [6] xtal_en = 0 --> FLD Reference Input Clock
    ScalerSetBit_EXINT(PB_D0_ANA_CDR_02, ~_BIT6, 0x00);

    // [7] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(PB_D1_ANA_CDR_03, ~_BIT7, _BIT7);

    // [7] en_wide_temp = 1'b1 --> Enable Wide Temp VCO Band
    ScalerSetBit_EXINT(PB_D3_ANA_CDR_05, ~_BIT7, _BIT7);

    // [3:2] en_vcm_tune = 2'b11 --> Vc = Vdd/2
    ScalerSetBit_EXINT(PB_D2_ANA_CDR_04, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [7] reg_rstb_fsm --> Toggle for FLD reset
    // [6] reg_rstb_fld --> Toggle for FLD reset
    ScalerSetBit_EXINT(PB_D2_ANA_CDR_04, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(PB_D2_ANA_CDR_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Waiting for VCO Stable
    DELAY_XUS_EXINT(360);

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT7, _BIT7);

    // Waiting for CMU PLL Stable
    DELAY_XUS_EXINT(150);

    // [0] en_clkout_manual = 1 --> Enable Clkout
    ScalerSetBit_EXINT(PB_AE_SDM_04, ~_BIT0, _BIT0);

    // [0] en_eqen_manual = 1 --> Enable Adaptation
    ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, _BIT0);

    // Waiting for the Adaptation
    DELAY_XUS_EXINT(290);

    // [0] en_eqen_manual = 0 --> Disable Adaptation
    ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 1 --> Enable Dataout
    ScalerSetBit_EXINT(PB_B1_DATA_TIMER, ~_BIT0, _BIT0);

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
        }
    }

    // HDCP 1.4 Write Aksv IRQ have been Received
    if((ScalerGetBit_EXINT(P2_A9_TMDS_ABC0, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P2_AA_TMDS_ABC1, _BIT4) == _BIT4))
    {
        // clear AKSV flag
        ScalerSetBit_EXINT(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), _BIT7);

        // SET KEY ready bit 1
        ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, _BIT1);
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
    ScalerSetByte(PB_C0_CMU_03, 0xFF);

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
    ScalerSetByte_EXINT(PB_C0_CMU_03, 0xFF);

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
        ScalerSetBit(P2_B9_TMDS_OUT_CTRL, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerSetBit(P2_B9_TMDS_OUT_CTRL, ~_BIT6, 0x00);
    }
    //////////////////////////////////////////////////////////////////
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
    MCU_FFE4_DDC0_EDID_IRQ = ((MCU_FFE4_DDC0_EDID_IRQ & ~(_BIT3 | _BIT1)) | (_BIT2 | _BIT0));
    MCU_FFE5_DDC1_EDID_IRQ = ((MCU_FFE5_DDC1_EDID_IRQ & ~(_BIT3 | _BIT1)) | (_BIT2 | _BIT0));

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
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

    if((ucInputPort == _D0_INPUT_PORT) && (GET_TMDS_RX0_DDC_DETECTED() == _TRUE))
    {
        // DDC handshake Detected
        DebugMessageDigital("7. wuzanne test : Normal D0 DDC", 0);

        CLR_TMDS_RX0_DDC_DETECTED();

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
#endif // End of #if(_D0_DDC_CHANNEL_SEL == _DDC0)
    }
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

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
#endif // End of #if(_D1_DDC_CHANNEL_SEL == _DDC0)
    }
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)


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
        if(ucInputPort == _D0_INPUT_PORT)
        {
            SET_TMDS_RX0_TOGGLE_Z0();
        }
        else if(ucInputPort == _D1_INPUT_PORT)
        {
            SET_TMDS_RX1_TOGGLE_Z0();
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
#endif
    }
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

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

        default:

            break;
    }

    if(GET_TMDS_PHY_SET() == _TRUE)
    {
        // Delay for PHY Stable
        ScalerTimerDelayXms(2);


        if(ScalerTMDSCheckCDRStable(ucInputPort, g_usTMDSClkCount) == _FALSE)
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

        DebugMessageRx0("9. Freq Check Pass => Pixel Clock", GET_INPUT_PIXEL_CLK());

        if(GET_INPUT_PIXEL_CLK() >= 700)
        {
            // BED Check to fine tune DFE
            ScalerTMDSBEDCheck();
        }

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

        return _SOURCE_HDMI;
    }
    else
    {
        ScalerSetBit(P2_AF_TMDS_WDC, ~_BIT0, _BIT0);
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

                    return _FALSE;
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

                    return _FALSE;
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
                if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    DebugMessageRx0("HDMI Info Frame Not Received and not RGB", ucSourceType);
                    return _FALSE;
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
                if(GET_D0_CABLE_STATUS() == _TRUE)
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
                if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
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

            if(GET_D0_CABLE_STATUS() == _TRUE)
            {
                // Save Z0 Status
                g_ucTMDSRx0Z0Status = ScalerGetBit(PB_B7_IMPEDANCE_00, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Backup Slave Address
                ScalerGetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, 1, &g_ucTMDSSlaveAddr, _NON_AUTOINC);

                // Disable Z0
                ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }
            else if(GET_D0_CABLE_STATUS() == _FALSE)
            {
                // DDC reset
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT1;
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT1;
#endif
            }

            break;
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(GET_D1_CABLE_STATUS() == _TRUE)
            {
                // Save Z0 Status
                g_ucTMDSRx1Z0Status = ScalerGetBit(PB_B9_IMPEDANCE_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Backup Slave Address
                ScalerGetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, 1, &g_ucTMDSSlaveAddr, _NON_AUTOINC);

                // Disable Z0
                ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }
            else if(GET_D1_CABLE_STATUS() == _FALSE)
            {
                // DDC reset
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT1;
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT1;
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

            if(GET_D0_CABLE_STATUS() == _TRUE)
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

            if(GET_D1_CABLE_STATUS() == _TRUE)
            {
                // Restore Slave Address
                ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD, g_ucTMDSSlaveAddr);

                // Restore Z0 Status
                ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), g_ucTMDSRx1Z0Status);
            }
            break;
#endif

        default:

            break;
    }
}

//-------------------------------------------------
// Description  : TMDS Bit Error Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSBEDCheck(void)
{
    BYTE ucBEDErrorCount = 0;
    BYTE ucTMDSBEDCycle = 0;

    // Disable Freq. Unstable IRQ to prevent DFE return to Default value
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT6 | _BIT2 | _BIT1), 0x00);

    // check 12 frames, XBOX worst case is 10 frames.
    for(ucTMDSBEDCycle = 0; ucTMDSBEDCycle < 12; ucTMDSBEDCycle++)
    {
        // Clear Vsync
        ScalerSetBit(P2_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);

        // Wait Vsync
        if(ScalerTimerPollingFlagProc(50, P2_A4_TMDS_CTRL, _BIT3, _TRUE) == _TRUE)
        {
            // Read Bit Error enable
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_AF_PORT_PAGE2_HDMI_BED_FUNC_0, ~_BIT5, _BIT5);

            // pop up Bit Error Counter
            ScalerSetByte(P2_C9_HDMI_AP, _P2_CA_PT_B6_PORT_PAGE2_HDMI_BED_FUNC_7);
            ucBEDErrorCount = ScalerGetByte(P2_CA_HDMI_DP);

            if(ucBEDErrorCount > 0)
            {
                if(ScalerGlobalGetIDCode() >= _RL6463_VER_C_ID_CODE)
                {
                    // change to LEQ = 6
                    ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x06);
                    ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x06);
                    ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x06);
                }
                else
                {
                    // change to LEQ = 5
                    ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x05);
                    ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x05);
                    ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x05);
                }

                break;
            }
        }
        // no Vsync, DE only mode keep LEQ default
        else
        {
            break;
        }
    }

    // Enable Freq. Unstable IRQ
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);
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
                // SET KEY ready bit 1
                ScalerSetBit(P2_AE_TMDS_RPS, ~(_BIT1), 0x00);
            }
            break;
#endif

        default:

            break;
    }
}
#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
