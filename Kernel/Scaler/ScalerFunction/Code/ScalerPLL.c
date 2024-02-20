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
// ID Code      : ScalerPLL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_PLL__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of APLL VCO Reference Clock Select
//--------------------------------------------------
#if(_LC_TANK_SUPPORT == _ON)

#if(_XTALESS_SUPPORT == _ON)
#define _APLL_REF_CLK                               _LC_TANK_XTAL_FREQUENCY
#else
#define _APLL_REF_CLK                               _EXT_XTAL
#endif

#else

#define _APLL_REF_CLK                               _EXT_XTAL

#endif

//--------------------------------------------------
// Definitions of M2PLL N.F default code
//--------------------------------------------------
#if(_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
#if(_LC_TANK_SUPPORT == _ON)

#if(_XTALESS_SUPPORT == _ON)
#define _M2PLL_DEFAULT_N_F_CODE                     0x1B0315E2UL
#else
#define _M2PLL_DEFAULT_N_F_CODE                     0x32000000UL
#endif

#else

#define _M2PLL_DEFAULT_N_F_CODE                     0x32000000UL

#endif
#endif

//--------------------------------------------------
// Definitions of APLL VCO Divider Threshold
//--------------------------------------------------
#define _APLL_VCO_M_CODE_MIN                        7

//--------------------------------------------------
// Definitions of APLL VCO Divider Threshold
//--------------------------------------------------
#define _APLL_VCO_DEVIDER_4_2_THERSHOLD             100000

//--------------------------------------------------
// Definitions of difference between measurement edge phase and calculation by mode edge phase
//--------------------------------------------------
#define _PHASE_DELAY_EDGEPHASE_THRESHOLD            2

//----------------------------------------------------------------------------
// APLL Parameters
//----------------------------------------------------------------------------
#define _APLL_SUM_I_READ_COUNT                      3

//--------------------------------------------------
// Definations of APLL _G_VALUE_DIVIDER
//--------------------------------------------------
#define _G_VALUE_DIVIDER_0                          4
#define _G_VALUE_DIVIDER_1                          16
#define _G_VALUE_DIVIDER_2                          64
#define _G_VALUE_DIVIDER_3                          128
#define _G_VALUE_DIVIDER_4                          256
#define _G_VALUE_DIVIDER_5                          512

//--------------------------------------------------
// Definations of DPLL setting state
//--------------------------------------------------
#define _DPLL_SET_POWER_OFF                         0
#define _DPLL_SET_VCO_BAND                          1
#define _DPLL_SET_FREQ                              2
#define _DPLL_SET_POWER_ON                          3
#define _DPLL_SET_OFFSET                            4

//--------------------------------------------------
// Definations of DPLL Change
//--------------------------------------------------
#define _DPLL_FREQ_CHG_OVER_10PER                   0
#define _DPLL_FREQ_CHG_UNDER_10PER                  1

//--------------------------------------------------
// Definations of DPLL Range
//--------------------------------------------------
#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)
#define _DPLL_BOUNDRY                               350000
#else
#if((_DPLL_BAND11_SUPPORT == _ON) && (_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON))
#define _DPLL_BOUNDRY_0                             640000
#define _DPLL_BOUNDRY_1                             1280000
#define _DPLL_BOUNDRY_2                             2560000
#define _DPLL_BOUNDRY_3                             5120000
#else
#define _DPLL_BOUNDRY_0                             600000
#define _DPLL_BOUNDRY_1                             1200000
#define _DPLL_BOUNDRY_2                             2400000
#define _DPLL_BOUNDRY_3                             4800000
#endif
#endif

#if(_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON)
#define _FORCE_FREQ_DOWN_THRESHOLD                  700000
#endif

#define _VCO_BAND10                                 2
#define _VCO_BAND11                                 3

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
//--------------------------------------------------
// Definations of MPLL Range
//--------------------------------------------------
#define _MPLL_BOUNDRY_0                             56250
#define _MPLL_BOUNDRY_1                             81250
#define _MPLL_BOUNDRY_2                             112500
#define _MPLL_BOUNDRY_3                             162500
#define _MPLL_BOUNDRY_4                             225000
#define _MPLL_BOUNDRY_5                             325000
#define _MPLL_BOUNDRY_6                             450000
#endif // #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

//--------------------------------------------------
// Definations of DDR2
//--------------------------------------------------
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
#define OESYNC_OP_SEL(pi, usSelBit)                 ((((pi) & _BIT4) == _BIT4) ? (usSelBit) : 0x00)

#define GET_OESYNC_SETTING(stPI)                    (\
                                                        OESYNC_OP_SEL(((stPI).ucCLK), _BIT0) |\
                                                        OESYNC_OP_SEL(((stPI).ucCMD), _BIT1) |\
                                                        OESYNC_OP_SEL(((stPI).ucDQS0), _BIT2) |\
                                                        OESYNC_OP_SEL(((stPI).ucDQS1), _BIT3) |\
                                                        OESYNC_OP_SEL(((stPI).ucDQ0), _BIT6) |\
                                                        OESYNC_OP_SEL(((stPI).ucDQ1), _BIT7)\
                                                    )
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

#if(_VGA_SUPPORT == _ON)
typedef struct
{
    WORD usPEValue;
    WORD usPreHTotal;
    DWORD ulDivider;
} StructAdjustApllData;
#endif

#if(_VGA_SUPPORT == _ON)
typedef enum
{
    _ADCPLL_PHASE_METHOD_MANUAL,
    _ADCPLL_PHASE_METHOD_LOOKUPTABLE
} EnumADCPLLPhaseMethod;
#endif // End of #if(_VGA_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

#if(_VGA_SUPPORT == _ON)
StructAdjustApllData g_stApllData;
#endif

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
StructDDR3PhaseInfo g_stDdr3PhaseData;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerPLLM2PLLPower(BYTE ucOn);
void ScalerM2PLLDiv(BYTE ucDiv);

void ScalerPLLSetDPLLReset(void);

#if((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N) || ((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F) && (_PANEL_STYLE != _PANEL_VBO)))
void ScalerPLLSetDPLLOffset(WORD usOffset);
#endif

#if((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
void ScalerPLLSetDPLLNFcode(DWORD ulNFcode);
#endif

void ScalerPLLSetDPLLSSC(BYTE ucDclkSpreadSpeed, BYTE ucSpreadRange);
void ScalerPLLSetDPLLFreq(DWORD ulFreq);

#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N)
void ScalerPLLSetDPLLFreqMN(DWORD ulFreq);
#endif

#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F)
void ScalerPLLSetDPLLFreqNfCascade(DWORD ulFreq);
#endif

#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)
void ScalerPLLSetDPLLFreqNfCombo(DWORD ulFreq);
#endif

#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F)
void ScalerPLLSetDPLLFreqNf(DWORD ulFreq);
#endif

DWORD ScalerPLLGetNewCount(DWORD ulCountNew, DWORD ulCountOld, DWORD ulValueOld, bit bProportion);
void ScalerDPLLFineTuneFrameSyncLineBuffer(void);

#if(_FRC_SUPPORT == _ON)
void ScalerDPLLFineTuneFrameSyncFrameBuffer(void);
#endif

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
#if(_MPLL_STRUCT_TYPE != _MPLL_STRUCT_COMBO_M2PLL)
void ScalerPLLSetMPLLOffset(WORD usMclkOffset);
void ScalerPLLSetMPLLFreq(DWORD ulFreq);
#endif
#endif

#if(_VGA_SUPPORT == _ON)
bit ScalerAPLLAdjust(WORD usCurrHTotal, WORD usCurrHFreq);
void ScalerAPLLLockThdSet(WORD usHFreq);
BYTE ScalerAPLLGetAPLLGValue(WORD *pusDelta);
bit ScalerAPLLFastLockAdjust(WORD usCurrHTotal);
bit ScalerAPLLGetSumI(DWORD *pulDiv);
WORD ScalerAPLLGetIHTotal(void);
void ScalerPLLSetPhase(BYTE ucPhase, WORD usVfreq);
WORD ScalerPLLGetApllReferClkFreqKhz(void);
#endif

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
void ScalerPLLDDR2PLLCtrl(bit bEnable);
void ScalerPLLDDR2PLLOutputCtrl(bit bEnable);
void ScalerPLLSetDDR2PLLFreq(DWORD ulFreq);
void ScalerPLLSetDDR2PLLWritePhase(StructDDR2PLLPI code *pstDDR2PLLPhase, bit bDDRSel);
#endif

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
void ScalerPLLSetDDRPLLFreq(DWORD ulFreq);
void ScalerPLLSetDDRPLLWritePhase(DWORD ulDDRPLLInitPhase0, DWORD ulDDRPLLInitPhase1);

#if(_DDR3_MULTIPHASE_EXIST == _ON)
void ScalerPLLGetDDR3PhaseData(StructDDR3PhaseInfo *pstDdr3PhaseData);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : M2PLL Power COntrol.
// Input Value  : ucOn    --> ON/OFF.
// Output Value : None
//--------------------------------------------------
void ScalerPLLM2PLLPower(BYTE ucOn)
{
#if(_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_M_N)
    if(ucOn == _ON)
    {
        // Power Off M2PLL
        ScalerSetBit(P1_E5_M2PLL_WD, ~_BIT0, _BIT0);

        // In fact, we can move the m/n code setting to scaler initial
        // Set M2PLL M Code
        ScalerSetByte(P1_E0_M2PLL_M, (_M2PLL_PLL_M - 2));

        // Set M2PLL N Code
        ScalerSetByte(P1_E1_M2PLL_N, (((_M2PLL_PLL_O >> 1) << 4) | (_M2PLL_PLL_N - 2)));

        // Set Rs, Cs, Icp
        ScalerSetByte(P1_E4_M2PLL_CRNT, 0x73);

        // DPLL VCORSTB Set to Normal
        ScalerSetBit(P1_E5_M2PLL_WD, ~_BIT1, (_DPLL_VCORSTB_NORMAL_VALUE << 1));

        // Power On M2PLL
        ScalerSetBit(P1_E5_M2PLL_WD, ~_BIT0, 0x00);
        DELAY_XUS(150);

        // Reset PFD, LPF
        ScalerSetBit(P1_E5_M2PLL_WD, ~_BIT5, _BIT5);
        DELAY_5US();
        ScalerSetBit(P1_E5_M2PLL_WD, ~_BIT5, 0x00);

        // Wait for M2PLL Stable (1ms)
        DELAY_XUS(1000);
    }
    else
    {
        // Power Off M2PLL
        ScalerSetBit(P1_E5_M2PLL_WD, ~_BIT0, _BIT0);
    }

#elif(_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)

    DWORD ulNFcode = _M2PLL_DEFAULT_N_F_CODE;
    BYTE pucNFvalue[4];
    memset(pucNFvalue, 0, sizeof(pucNFvalue));

    if(ucOn == _ON)
    {
#if(_LC_TANK_SUPPORT == _ON)
        // M2PLL clock selection from LC tank or Xtal
        ScalerSetBit(P41_03_PLL_IN_CONTROL, ~(_BIT7 | _BIT6), ((_XTALESS_SUPPORT == _ON) ? 0x00 : _BIT6));

#if((_XTALESS_SUPPORT == _ON) && (_EFUSE_SUPPORT == _ON))
        // Read Out eFuse Data
        ScalerEfuseGetData(_EFUSE_M2PLL_N_F_CODE, 4, pucNFvalue);

        ulNFcode = (((DWORD)pucNFvalue[0] << 24) | ((DWORD)pucNFvalue[1] << 16) | ((DWORD)pucNFvalue[2] << 8) | pucNFvalue[3]);
        ulNFcode = (ulNFcode == 0) ? _M2PLL_DEFAULT_N_F_CODE : ulNFcode;
#endif
#endif

        // Dobule Buffer for Prediv, Outputdiv, Bpn
        ScalerSetBit(P41_03_PLL_IN_CONTROL, ~_BIT0, _BIT0);

        // Power On LDO
        ScalerSetBit(P41_09_M2PLL_LDO, ~_BIT7, _BIT7);

        // Set Icp = 5uA
        ScalerSetByte(P41_06_M2PLL_0, 0x79);

        // Set PI current 3.33uA
        ScalerSetByte(P41_07_M2PLL_1, 0x26);

        // Set NF code
        ScalerSetDWord(P41_0D_N_F_CODE_1, ulNFcode);

        // N.F double buffer
        ScalerSetBit(P41_0C_N_F_CODE_0, ~_BIT0, _BIT0);

        // DPLL VCORSTB Set to Normal
        ScalerSetBit(P41_08_M2PLL_CONTROL, ~_BIT1, (_DPLL_VCORSTB_NORMAL_VALUE << 1));

        // Disable PI Bypass
        ScalerSetBit(P41_07_M2PLL_1, ~_BIT2, 0x00);

        // Power On M2PLL
        ScalerSetBit(P41_08_M2PLL_CONTROL, ~_BIT0, 0x00);

        // Wait for M2PLL Stable (1ms)
        DELAY_XUS(1000);
    }
    else
    {
        // Power Off M2PLL
        ScalerSetBit(P41_08_M2PLL_CONTROL, ~_BIT0, _BIT0);
    }
#endif // End of #if(_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_M_N)
}

//--------------------------------------------------
// Description  : System Clock Select From M2PLL Divider Control.
// Input Value  : ucDiv    --> Divider.
// Output Value : None
//--------------------------------------------------
void ScalerM2PLLDiv(BYTE ucDiv)
{
    // Internal Xtal Freq. From M2PLL divider
    ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), ucDiv << 3);
}

//--------------------------------------------------
// Description  : Reset DPLL Setting, Enable DPLL Spread Spectrum Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLReset(void)
{
#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)

    // Power Down LVDS Port AB CK_LVDS Clk
    ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~_BIT4, 0x00);

    // Clk Not Ready
    ScalerSetBit(P1_C0_DPLL0, ~_BIT4, 0x00);

    // Disable LDO
    ScalerSetBit(P1_D2_LVDSPLL_2, ~_BIT2, 0x00);

    // Power Down PLL
    ScalerSetBit(P1_D1_LVDSPLL_1, ~_BIT0, _BIT0);

    // Disable SSCG
    ScalerSetBit(P1_CA_SSCG_0, ~_BIT7, 0x00);

    // Reset PLL N.F Code
    ScalerPLLSetDPLLNFcode(0);

#elif(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F)

#if(_PANEL_STYLE == _PANEL_LVDS)
    // Power Down LVDS
    ScalerDisplayLvdsPLL(_OFF);
#else
    // Power Down DPTx PLL
    ScalerPLLDPTxPLLReset();
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

    // Disable LDO
    ScalerSetBit(P1_D2_DPLL_ANALOG_SETTING_2, ~_BIT2, 0x00);

    // Power Down PLL
    ScalerSetBit(P1_D1_DPLL_ANALOG_SETTING_1, ~_BIT0, _BIT0);

    // Disable SSCG
    ScalerSetBit(P1_CA_DPLL_SSCG_0, ~_BIT7, 0x00);

    // Reset PLL N.F Code
    ScalerPLLSetDPLLNFcode(0);

#else

    // Power Down DPLL
    ScalerSetBit(P1_C2_DPLL_WD, ~_BIT0, _BIT0);

#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F)
#if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
    // Power Down DPTx PLL
    ScalerPLLDPTxPLLReset();
#endif
#endif

    // Enable dpll_m_n_set_mode
    ScalerSetBit(P1_D9_DPLL_M_N_MSB, ~_BIT7, _BIT7);

    // Reset DPLL M Code (LSB)
    ScalerSetByte(P1_BF_DPLL_M, 0x00);

    // Reset DPLL M, N Code(MSB)
    ScalerSetBit(P1_D9_DPLL_M_N_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Reset DPLL N Code(LSB)
    ScalerSetBit(P1_C0_DPLL_N, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set DPLL BPN
    ScalerSetBit(P1_C0_DPLL_N, ~_BIT6, 0x00);

    // Reset DPLL Output Divier
    ScalerSetBit(P1_C0_DPLL_N, ~(_BIT5 | _BIT4), 0x00);

    // DPLL Bypass Calibration
    ScalerSetBit(P1_C3_DPLL_CAL, ~_BIT5, _BIT5);

    // Disable DPLL Calibration Mode
    ScalerSetBit(P1_C3_DPLL_CAL, ~(_BIT4 | _BIT3 | _BIT2), 0x00);

    // Disable DPLL WD Reset, DPLL WD Set Normal, DPLL Freq Tuning Enable, DPLL Reset VCO Normal
    ScalerSetBit(P1_C2_DPLL_WD, ~(_BIT6 | _BIT5 | _BIT3 | _BIT1), (_BIT3 | (_DPLL_VCORSTB_NORMAL_VALUE << 1)));

    // Enable DDS Spread Spectrum Output, Disable fixed last line
    ScalerSetBit(P1_CA_FIXED_LAST_LINE_CTRL, ~(_BIT1 | _BIT0), _BIT0);

    // Enable DPLL Phase Swallow, Set LDO
    ScalerSetBit(P1_D7_DPLL_LDO, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
#endif // End of #if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)
}

#if((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N) || ((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F) && (_PANEL_STYLE != _PANEL_VBO)))
//--------------------------------------------------
// Description  : Adjust DPLL Offset
// Input Value  : Target Offset Value
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLOffset(WORD usOffset)
{
    ScalerSetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, ~0x0F, (HIBYTE(usOffset) & 0x0F));
    ScalerSetByte(P1_C5_DCLK_FINE_TUNE_OFFSET_LSB, LOBYTE(usOffset));

    ScalerSetBit(P1_C6_DCLK_SPREAD_SPECTRUM, ~_BIT2, _BIT2);
}
#endif

#if((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
//--------------------------------------------------
// Description  : Adjust DPLL N.F
// Input Value  : Target N.F Value
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLNFcode(DWORD ulNFcode)
{
    BYTE ucNCode = 0;
    DWORD ulFCode = 0;

    ucNCode = ((ulNFcode & 0xFF00000) >> 20);

    ulFCode = (ulNFcode & 0x00FFFFF);

    // Check if ucNCode < 5
    ucNCode = (ucNCode < 5) ? 5 : ucNCode;

    // Set N[3:0].F[19:16] Code and double buffer for N.f code, prediv, postdiv
    ScalerSetByte(_REG_DPLL_N_F_CODE_1, ((ucNCode & 0x0F) << 4) | ((ulFCode & 0xF0000) >> 16));

    // Set F[15:8] Code
    ScalerSetByte(_REG_DPLL_N_F_CODE_2, ((ulFCode & 0x0FF00) >> 8));

    // Set F[7:0] Code
    ScalerSetByte(_REG_DPLL_N_F_CODE_3, ((ulFCode & 0x000FF) >> 0));

    // Set Double Buffer for N.f code
    ScalerSetBit(_REG_DPLL_N_F_CODE_0, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((ucNCode & 0xF0) >> 4)));
}
#endif

//--------------------------------------------------
// Description  : Adjust DPLL Spread Spectrum
// Input Value  : Spread Spectrum Range
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLSSC(BYTE ucDclkSpreadSpeed, BYTE ucSpreadRange)
{
#if(_PANEL_STYLE == _PANEL_VBO)

    // _SPEED_30K
    ScalerDisplaySetVboPLLSSC(ucDclkSpreadSpeed, ucSpreadRange);
    ScalerSetBit(P1_C6_DCLK_SPREAD_SPECTRUM, ~_BIT2, _BIT2);

#else

#if((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))

    DWORD ulSSCGStep = 0;
    WORD usTBase = 0;
    BYTE ucStepWeighting = 0;

    // Disable SSCG, Disable SSCG_TBASE_CAL_EN
    ScalerSetBit(_REG_DPLL_SSCG_0, ~(_BIT7 | _BIT2), 0x00);

    // Wait SSCG disalbe, SSCG disable at triangle center
    ScalerTimerPollingFlagProc(2, _REG_DPLL_SSCG_0, _BIT7, 0x00);

    if((ucSpreadRange != _OFF) &&
       ((ucDclkSpreadSpeed == _SPEED_33K) || (ucDclkSpreadSpeed == _SPEED_66K)))
    {
        // Set SSCG speed
        BYTE ucSpreadSpeed = (ucDclkSpreadSpeed == _SPEED_33K) ? 33 : 66;

        // calculate TBase with constant Fref
        usTBase = (ScalerGetBit(_REG_DPLL_ANALOG_SETTING_0, _BIT4) == _BIT4) ? _EXT_XTAL : (_EXT_XTAL / GET_N_F_PLL_PREDIVIDER());

        usTBase = usTBase / ucSpreadSpeed;

        // TBase must be a multiple of 4
        usTBase = ((usTBase + 2) >> 2) << 2;

        // SSCG_TBASE_CAL_EN set manual mode
        ScalerSetBit(_REG_DPLL_SSCG_0, ~_BIT2, 0x00);

        ///////////////////////////////////////////////////////////////////////////
        //
        // Calculate SSCG range step
        //
        // N.F * range = step * (TBASE / 2)
        // Step = SSCG_step * SSCG_weight, SSCG_step unit: 2^8, SSCG_weight min:1/8
        // Setp calculate use min unit: 2^8 / 8 = 2^5
        // range: 5 * ucSpreadRange / 1000.   ucSpreadRange = 15 --> range = 7.5%
        //
        ///////////////////////////////////////////////////////////////////////////
        ulSSCGStep = ((((DWORD)(ScalerGetDWord(_REG_DPLL_N_F_CODE_0) & 0x0FFFFFFF) >> 5) * 5 * ucSpreadRange * 2) / 1000 + (usTBase / 2)) / usTBase;

        if((ulSSCGStep >> 8) < 1)
        {
            ucStepWeighting = 0;
        }
        else if((ulSSCGStep >> 8) < 2)
        {
            ucStepWeighting = 1;
        }
        else if((ulSSCGStep >> 8) < 4)
        {
            ucStepWeighting = 2;
        }
        else if((ulSSCGStep >> 8) < 8)
        {
            ucStepWeighting = 3;
        }
        else if((ulSSCGStep >> 8) < 16)
        {
            ucStepWeighting = 4;
        }
        else if((ulSSCGStep >> 8) < 32)
        {
            ucStepWeighting = 5;
        }
        else
        {
            ucStepWeighting = 6;
        }

        DebugMessageDigital("6. DPLL SSCG Step", ulSSCGStep);
        DebugMessageDigital("6. DPLL SSCG Step Weighting", ucStepWeighting);
        DebugMessageDigital("6. DPLL TBASE", usTBase);

        ScalerSetByte(_REG_DPLL_SSCG_1, (ulSSCGStep >> ucStepWeighting));
        ScalerSetByte(_REG_DPLL_SSCG_2, (((ucStepWeighting & 0x07) << 5) | ((usTBase >> 8) & 0x0F)));
        ScalerSetByte(_REG_DPLL_SSCG_3, (usTBase & 0xFF));

        // Enable SSCG
        ScalerSetBit(_REG_DPLL_SSCG_0, ~_BIT7, _BIT7);
    }

#else
    // _SPEED_33K, _SPEED_66K
    ScalerSetByte(P1_D6_DCLK_SSC_COUNT, 0x94);
    ScalerSetBit(P1_C6_DCLK_SPREAD_SPECTRUM, ~0xF0, ((ucSpreadRange << 4) & 0xF0));
    ScalerSetBit(P1_C6_DCLK_SPREAD_SPECTRUM, ~_BIT3, ((ucDclkSpreadSpeed == _SPEED_33K) ? 0x00 : _BIT3));
    ScalerSetBit(P1_C6_DCLK_SPREAD_SPECTRUM, ~_BIT2, _BIT2);
#endif // End of #if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)
#endif // End of #if(_PANEL_STYLE == _PANEL_VBO)
}

//--------------------------------------------------
// Description  : Set DPLL Freq
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLFreq(DWORD ulFreq)
{
#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N)
    ScalerPLLSetDPLLFreqMN(ulFreq);
#elif(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F)
    ScalerPLLSetDPLLFreqNfCascade(ulFreq);
#elif(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)
    ScalerPLLSetDPLLFreqNfCombo(ulFreq);
#elif(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F)
    ScalerPLLSetDPLLFreqNf(ulFreq);
#endif
}

#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N)
//--------------------------------------------------
// Description  : Set DPLL Freq
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLFreqMN(DWORD ulFreq)
{
    BYTE ucDPLLSettingState = _DPLL_SET_POWER_OFF;
    bit bDISPPower = 0;
    WORD usMcode = 0;
    DWORD ulRefClk = 0;
    BYTE ucOutputdivider = 0;

#if(_PANEL_STYLE == _PANEL_LVDS)

    ScalerPLLSetDisplayPLL(ulFreq);

#elif((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX)) // Elif of #if(_PANEL_STYLE == _PANEL_LVDS)

    ScalerPLLSetDisplayPLL(ulFreq);

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

    ulRefClk = ScalerPLLGetDPLLRefClk(ulFreq);

    ulFreq = (ulFreq >> _D_DOMAIN_PATH);

#if(_PANEL_STYLE == _PANEL_LVDS)

    bDISPPower = ScalerDisplayGetLvdsPowerStatus();

#elif(_PANEL_STYLE == _PANEL_DPTX)

    bDISPPower = ScalerPLLGetDptxPowerStatus();

#elif(_PANEL_STYLE == _PANEL_VBO)

    bDISPPower = ScalerDisplayGetVboPowerStatus();

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

    // usMcode = 16*real Mcode, for accuracy
    usMcode = ((ulFreq << 4) * 2 * 16 / (ulRefClk * 15));

    // DPLL_VCO_clk_now
    PDATA_DWORD(0) = ulFreq * 16 / 15;

    if(bDISPPower == _ON)
    {
        PDATA_DWORD(1) = (((DWORD)(ScalerGetByte(P1_D9_DPLL_M_N_MSB) & 0x30) << 4) + ScalerGetByte(P1_BF_DPLL_M) + 2) * ulRefClk / (((DWORD)(ScalerGetByte(P1_D9_DPLL_M_N_MSB) & 0x0F) << 4) + (ScalerGetByte(P1_C0_DPLL_N) & 0x0F) + 2) / (1 << (ScalerGetByte(P1_DA_DPLL_OUTPUT_CLK_DIV) & 0x03)) / 2;

        if(ABSDWORD(PDATA_DWORD(0), PDATA_DWORD(1)) <= (PDATA_DWORD(1) / 10))
        {
            pData[14] = _DPLL_FREQ_CHG_UNDER_10PER;
        }
        else
        {
            pData[14] = _DPLL_FREQ_CHG_OVER_10PER;
        }
    }
    else
    {
        pData[14] = _DPLL_FREQ_CHG_OVER_10PER;
    }

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if((GET_AIO_MODERN_STANDBY_MODE() == _TRUE) && (GET_DPLL_POWER_STATUS() == _TRUE))
    {
        // DPLL_VCO_clk_now
        PDATA_DWORD(0) = ulFreq * 16 / 15;
        PDATA_DWORD(1) = (((DWORD)(ScalerGetByte(P1_D9_DPLL_M_N_MSB) & 0x30) << 4) + ScalerGetByte(P1_BF_DPLL_M) + 2) * ulRefClk / (((DWORD)(ScalerGetByte(P1_D9_DPLL_M_N_MSB) & 0x0F) << 4) + (ScalerGetByte(P1_C0_DPLL_N) & 0x0F) + 2) / (1 << (ScalerGetByte(P1_DA_DPLL_OUTPUT_CLK_DIV) & 0x03)) / 2;

        if(ABSDWORD(PDATA_DWORD(0), PDATA_DWORD(1)) <= (PDATA_DWORD(1) / 10))
        {
            pData[14] = _DPLL_FREQ_CHG_UNDER_10PER;
        }
        else
        {
            pData[14] = _DPLL_FREQ_CHG_OVER_10PER;
        }
    }
#endif

    // DPLL freq change under 10%, VCO band and div_o keep as before
    if(pData[14] == _DPLL_FREQ_CHG_UNDER_10PER)
    {
        // ucOutputdivider = DPLL_pixelclk_div[1:0]
        ucOutputdivider = ScalerGetBit(P1_DA_DPLL_OUTPUT_CLK_DIV, (_BIT1 | _BIT0));

        switch(ucOutputdivider)
        {
            case 0:

                pData[14] = 8;
                break;

            case 1:

                pData[14] = 4;
                break;

            case 2:

                pData[14] = 2;
                break;

            case 3:

                pData[14] = 1;
                break;

            default:

                break;
        }

        usMcode = (usMcode + (pData[14] / 2)) / pData[14];

        if((usMcode - 2) == (((WORD)(ScalerGetByte(P1_D9_DPLL_M_N_MSB) & 0x30) << 4) + ScalerGetByte(P1_BF_DPLL_M)))
        {
            ucDPLLSettingState = _DPLL_SET_OFFSET;
        }
        else
        {
            ucDPLLSettingState = _DPLL_SET_FREQ;
        }
    }
    else
    {
        // ----------- Previous Select Band & Div Alg. -----------
        // ucOutputdivider = DPLL VCO band
        PDATA_DWORD(1) = PDATA_DWORD(0) * 16;
        if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_0)
        {
            ucOutputdivider = 3;
        }
        else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_1)
        {
            ucOutputdivider = 2;
        }
        else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_2)
        {
            ucOutputdivider = 1;
        }
        else
        {
            ucOutputdivider = 0;
        }

        // ------------- Div Alg. --------------
        // ucOutputdivider = DPLL_O[1:0]
        switch(ucOutputdivider)
        {
            case 0:

                pData[14] = 8;
                break;

            case 1:

                pData[14] = 4;
                break;

            case 2:

                pData[14] = 2;
                break;

            case 3:

                pData[14] = 1;
                break;

            default:

                break;
        }

        usMcode = (usMcode + (pData[14] / 2)) / pData[14];
    }

    switch(ucDPLLSettingState)
    {
        case _DPLL_SET_POWER_OFF:

            // Wait DEN STOP
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_PANEL_STYLE == _PANEL_LVDS)
            // Power Down LVDS
            ScalerDisplayLvdsPLL(_OFF);
#elif(_PANEL_STYLE == _PANEL_VBO)
            // Power Down Vby1
            ScalerDisplayVboPLL(_OFF);
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

            // Power Down DPLL
            ScalerSetBit(P1_C2_DPLL_WD, ~_BIT0, _BIT0);

        /*@fallthrough@*/
        case _DPLL_SET_VCO_BAND:

            // Manual set DPLL VCO band = b'10
            ScalerSetBit(P1_C3_DPLL_CAL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((0x02) << 6) | _BIT5);

        /*@fallthrough@*/
        case _DPLL_SET_FREQ:

            //////////////////////////////////////////////////////////////////////////////////////////////////
            // Old Formula : Icp * N_Code / M_Code = 0.5 * Fxtal / 27MHz (for xtal not 27MHz)               //
            // Icp set 2.5uA, 5uA, 7.5uA, 10uA......                                                        //
            // Precise formula of Chrage Pump Current depends on DPM, resistor, and band.                   //
            // If VCO band = 'b00, Icp = (700 * M * 2 * pi) / (778 * 0x01C1[7:5]).                          //
            // If VCO band = 'b01, Icp = (700 * M * 2 * pi) / (1340 * 0x01C1[7:5]).                         //
            // If VCO band = 'b10, Icp = (700 * M * 2 * pi) / (1880 * 0x01C1[7:5]).                         //
            // If VCO band = 'b11, Icp = (700 * M * 2 * pi) / (2340 * 0x01C1[7:5]).                         //
            // 700: DPLL max frequency design target is 700MHz; 778: Frequency curve in band00 is 778MHz.   //
            // Assume DPLL_M=0x13, DPM=0x13+2=21; DPN=2; reg_dpll_vcomd='b01; reg_dpll_rs[2:0]='b011;       //
            // Icp = (700 * 21 * 2 * 3.14) / (1340 * 13)                                                    //
            //////////////////////////////////////////////////////////////////////////////////////////////////
            PDATA_DWORD(0) = (DWORD)usMcode * 700UL * 628 * 20 / 1880 / ((7 + (ScalerGetBit(P1_C1_DPLL_CRNT, (_BIT7 | _BIT6 | _BIT5)) >> 5) * 2) * 100);
            pData[1] = (PDATA_DWORD(0) + 25) / 50;
            pData[1] -= (pData[1] == 0) ? 0 : 1;

            DebugMessageDigital("6. DisplayPLL Charge Pump icp =", pData[1]);

            // Set M Code
            ScalerSetByte(P1_BF_DPLL_M, ((usMcode - 2) & 0xFF));
            ScalerSetBit(P1_D9_DPLL_M_N_MSB, ~(_BIT5 | _BIT4), (((usMcode - 2) >> 4) & 0x30));

            // M/N code should be written in porch
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

            // Set N Code and Output divider
            ScalerSetByte(P1_C0_DPLL_N, 0x00);

            // Set pixel clk divider (DIV_B)
            ScalerSetBit(P1_DA_DPLL_OUTPUT_CLK_DIV, ~(_BIT1 | _BIT0), ucOutputdivider);

            // Set Icp
            ScalerSetByte(P1_C1_DPLL_CRNT, (0x78 | (pData[1] & 0x07)));

        /*@fallthrough@*/
        case _DPLL_SET_POWER_ON:

            // DPLL VCORSTB Set to Normal
            ScalerSetBit(P1_E5_M2PLL_WD, ~_BIT1, (_DPLL_VCORSTB_NORMAL_VALUE << 1));

#if(_DPLL_WD_SET_REF_POWER == _ON)
            // DPLL Power Down
            if(ScalerGetBit(P1_C2_DPLL_WD, _BIT0) == _BIT0)
#endif
            {
                // Power Up DPLL
                ScalerSetBit(P1_C2_DPLL_WD, ~_BIT0, 0x00);
                DELAY_XUS(150);

                // Reset PFD, LPF
                ScalerSetBit(P1_C2_DPLL_WD, ~_BIT5, _BIT5);
                DELAY_5US();
                ScalerSetBit(P1_C2_DPLL_WD, ~_BIT5, 0x00);
            }

        /*@fallthrough@*/
        case _DPLL_SET_OFFSET:

            // Calculate DPLL Output Freq. According to current Settings
            PDATA_DWORD(0) = ulRefClk * 1000 / ((1 << (ucOutputdivider)) * 2) * usMcode / 2;

            // Offset resolution (Dclk / 2^15) in Hz
            PDATA_DWORD(1) = PDATA_DWORD(0) >> 15;

            // Target frequency of Dclk in Hz
            PDATA_WORD(0) = (PDATA_DWORD(0) - (ulFreq * 1000)) / PDATA_DWORD(1);
            PDATA_WORD(0) = PDATA_WORD(0) & 0x0fff;

            // Set Dpll Offset
            ScalerPLLSetDPLLOffset(PDATA_WORD(0));

            break;

        default:

            break;
    }

#if(_PANEL_STYLE == _PANEL_LVDS)
    // Recover LVDS PLL
    if(bDISPPower == _ON)
    {
        // Power On LVDS
        ScalerDisplayLvdsPLL(_ON);
    }
#endif
}
#endif // End of #if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N)

#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F)
//--------------------------------------------------
// Description  : Set DPLL Freq
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLFreqNfCascade(DWORD ulFreq)
{
    BYTE ucDPLLSettingState = _DPLL_SET_POWER_OFF;
    bit bDISPPower = 0;
    bit bForceFreqDown = 0;
    WORD usMcode = 0;
    DWORD ulRefClk = 0;
    BYTE ucOutputdivider = 0;
#if((_DPLL_BAND11_SUPPORT == _ON) && (_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON))
    BYTE ucVcoBand = _VCO_BAND10;
#endif

    ucDPLLSettingState = ucDPLLSettingState;

#if(_PANEL_STYLE == _PANEL_LVDS)

    ScalerPLLSetDisplayPLL(ulFreq);

#elif((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX)) // Elif of #if(_PANEL_STYLE == _PANEL_LVDS)

    ScalerPLLSetDPLLRefPLL(ulFreq);

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

    ulRefClk = ScalerPLLGetDPLLRefClk(ulFreq);

    ulFreq = (ulFreq >> _D_DOMAIN_PATH);

    bForceFreqDown = _FALSE;

#if(_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON)
    if((ulFreq * 2) > _FORCE_FREQ_DOWN_THRESHOLD)
    {
        bForceFreqDown = _TRUE;
    }
#endif

#if(_MN_DPLL_PATH_TYPE == _MN_DPLL_PATH2)

    // Set MN DPLL Phase Swallow Path2
    ScalerSetBit(P1_C3_DPLL_CAL, ~_BIT0, 0x00);

    // Set DPLL Freq down
    ScalerSetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, ~_BIT4, _BIT4);

#else

    // Set MN DPLL Phase Swallow Path1
    ScalerSetBit(P1_C3_DPLL_CAL, ~_BIT0, _BIT0);

#if(_MN_DPLL_FREQ_UP == _ON)
    if(bForceFreqDown == _TRUE)
    {
        // Set DPLL Freq down
        ScalerSetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, ~_BIT4, _BIT4);
    }
    else
    {
        // Set DPLL Freq up
        ScalerSetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, ~_BIT4, 0x00);
    }

#if(_HW_PLL_EDGE_SELECT_TYPE == _PLL_EDGE_GEN_1_DEFAULT_POSITIVE)
    // Set DPLL Negative
    ScalerSetBit(P1_D7_DPLL_LDO, ~_BIT1, _BIT1);
#endif

#else
    // Set DPLL Freq down
    ScalerSetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, ~_BIT4, _BIT4);
#endif

#endif

#if(_PANEL_STYLE == _PANEL_LVDS)

    bDISPPower = ScalerDisplayGetLvdsPowerStatus();

#elif(_PANEL_STYLE == _PANEL_DPTX)

    bDISPPower = ScalerPLLGetDptxPowerStatus();

#elif(_PANEL_STYLE == _PANEL_VBO)

    bDISPPower = ScalerDisplayGetVboPowerStatus();

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

#if(_PANEL_STYLE == _PANEL_VBO)
    // ----------- Previous Select Band & Div Alg. -----------
    // ucOutputdivider = DPLL_O[1:0]
    PDATA_DWORD(1) = ulFreq * 16;
    if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_0)
    {
        ucOutputdivider = 3;
    }
    else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_1)
    {
        ucOutputdivider = 2;
    }
    else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_2)
    {
        ucOutputdivider = 1;
    }
    else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_3)
    {
        ucOutputdivider = 0;
    }
    else
    {
        ucOutputdivider = 0;
#if((_DPLL_BAND11_SUPPORT == _ON) && (_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON))
        ucVcoBand = _VCO_BAND11;
#endif
    }

    usMcode = (1 << ((ScalerGetBit(P1_D8_DPLL_RELOAD_CTRL, (_BIT3 | _BIT2)) >> 2) + 1)) * (_VBO_OUTPUT_PORT) * (1 << ucOutputdivider) / ((ScalerGetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, _BIT2) >> 2) + 1);

    // Wait DEN STOP
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    // Power Down DPLL
    ScalerSetBit(P1_C2_DPLL_WD, ~_BIT0, _BIT0);

#if((_DPLL_BAND11_SUPPORT == _ON) && (_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON))
    // set DPLL VCO band and bypass calibration
    ScalerSetBit(P1_C3_DPLL_CAL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((ucVcoBand) << 6) | _BIT5);
#else
    // Manual set DPLL VCO band = 10 and bypass calibration
    ScalerSetBit(P1_C3_DPLL_CAL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT5));
#endif

    // DPLL SET Icp:

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Old Formula : Icp * N_Code / M_Code = 0.5 * Fxtal / 27MHz (for xtal not 27MHz)               //
    // Icp set 2.5uA, 5uA, 7.5uA, 10uA......                                                        //
    // Precise formula of Chrage Pump Current depends on DPM, resistor, and band.                   //
    // If VCO band = 'b00, Icp = (700 * M * 2 * pi) / (778 * 0x01C1[7:5]).                          //
    // If VCO band = 'b01, Icp = (700 * M * 2 * pi) / (1340 * 0x01C1[7:5]).                         //
    // If VCO band = 'b10, Icp = (700 * M * 2 * pi) / (1880 * 0x01C1[7:5]).                         //
    // If VCO band = 'b11, Icp = (700 * M * 2 * pi) / (2340 * 0x01C1[7:5]).                         //
    // 700: DPLL max frequency design target is 700MHz; 778: Frequency curve in band00 is 778MHz.   //
    // Assume DPLL_M=0x13, DPM=0x13+2=21; DPN=2; reg_dpll_vcomd='b01; reg_dpll_rs[2:0]='b011;       //
    // Icp = (700 * 21 * 2 * 3.14) / (1340 * 13)                                                    //
    //////////////////////////////////////////////////////////////////////////////////////////////////

#if((_DPLL_BAND11_SUPPORT == _ON) && (_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON))
    PDATA_DWORD(0) = ((ucVcoBand == _VCO_BAND11) ? 2340 : 1880);
#else
    PDATA_DWORD(0) = 1880;
#endif
    PDATA_DWORD(0) = (DWORD)usMcode * 700UL * 628UL * 20UL / PDATA_DWORD(0) / ((7UL + (ScalerGetBit(P1_C1_DPLL_CRNT, (_BIT7 | _BIT6 | _BIT5)) >> 5UL) * 2UL) * 100UL);
    pData[1] = (PDATA_DWORD(0) + 25) / 50;
    pData[1] -= (pData[1] == 0) ? 0 : 1;

    DebugMessageDigital("6. DisplayPLL Charge Pump icp =", pData[1]);

    // Set M Code
    ScalerSetByte(P1_BF_DPLL_M, ((usMcode - 2) & 0xFF));
    ScalerSetBit(P1_D9_DPLL_M_N_MSB, ~(_BIT5 | _BIT4), (((usMcode - 2) >> 4) & 0x30));

    // M/N code should be written in porch
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    // Set N Code and Output divider
    ScalerSetByte(P1_C0_DPLL_N, (_VBO_BYTE_MODE - 2));

    // Set pixel clk divider (DIV_B)
    ScalerSetBit(P1_DA_DPLL_OUTPUT_CLK_DIV, ~(_BIT1 | _BIT0), ucOutputdivider);

    // Set Icp
    ScalerSetByte(P1_C1_DPLL_CRNT, (0x78 | (pData[1] & 0x07)));

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(P1_E5_M2PLL_WD, ~_BIT1, (_DPLL_VCORSTB_NORMAL_VALUE << 1));

    // Power Up DPLL
    ScalerSetBit(P1_C2_DPLL_WD, ~_BIT0, 0x00);
    DELAY_XUS(150);

    // Reset PFD, LPF
    ScalerSetBit(P1_C2_DPLL_WD, ~_BIT5, _BIT5);
    DELAY_5US();
    ScalerSetBit(P1_C2_DPLL_WD, ~_BIT5, 0x00);

#else

#if(_MN_DPLL_PATH_TYPE == _MN_DPLL_PATH2)

    // usMcode = 16*real Mcode, for accuracy
    usMcode = (ulFreq << 4) * 2 * 17 / (ulRefClk * 16);

    // DPLL_VCO_clk_now
    PDATA_DWORD(0) = ulFreq * 17 / 16;

#else

#if(_MN_DPLL_FREQ_UP == _ON)
    if(ScalerGetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, _BIT4) == 0x00)
    {
        // usMcode = 16*real Mcode, for accuracy
        usMcode = ((ulFreq << 4) * 2 * 16 / (ulRefClk * 17));

        // DPLL_VCO_clk_now
        PDATA_DWORD(0) = ulFreq * 16 / 17;
    }
    else
#endif
    {
        // usMcode = 16*real Mcode, for accuracy
        usMcode = ((ulFreq << 4) * 2 * 16 / (ulRefClk * 15));

        // DPLL_VCO_clk_now
        PDATA_DWORD(0) = ulFreq * 16 / 15;
    }

#endif

    if(bDISPPower == _ON)
    {
        PDATA_DWORD(1) = (((DWORD)(ScalerGetByte(P1_D9_DPLL_M_N_MSB) & 0x30) << 4) + ScalerGetByte(P1_BF_DPLL_M) + 2) * ulRefClk / (((DWORD)(ScalerGetByte(P1_D9_DPLL_M_N_MSB) & 0x0F) << 4) + (ScalerGetByte(P1_C0_DPLL_N) & 0x0F) + 2) / (1 << (ScalerGetByte(P1_DA_DPLL_OUTPUT_CLK_DIV) & 0x03)) / 2;

        if(ABSDWORD(PDATA_DWORD(0), PDATA_DWORD(1)) <= (PDATA_DWORD(1) / 10))
        {
            pData[14] = _DPLL_FREQ_CHG_UNDER_10PER;
        }
        else
        {
            pData[14] = _DPLL_FREQ_CHG_OVER_10PER;
        }
    }
    else
    {
        pData[14] = _DPLL_FREQ_CHG_OVER_10PER;
    }

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if((GET_AIO_MODERN_STANDBY_MODE() == _TRUE) && (GET_DPLL_POWER_STATUS() == _TRUE))
    {
        PDATA_DWORD(1) = (((DWORD)(ScalerGetByte(P1_D9_DPLL_M_N_MSB) & 0x30) << 4) + ScalerGetByte(P1_BF_DPLL_M) + 2) * ulRefClk / (((DWORD)(ScalerGetByte(P1_D9_DPLL_M_N_MSB) & 0x0F) << 4) + (ScalerGetByte(P1_C0_DPLL_N) & 0x0F) + 2) / (1 << (ScalerGetByte(P1_DA_DPLL_OUTPUT_CLK_DIV) & 0x03)) / 2;

        if(ABSDWORD(PDATA_DWORD(0), PDATA_DWORD(1)) <= (PDATA_DWORD(1) / 10))
        {
            pData[14] = _DPLL_FREQ_CHG_UNDER_10PER;
        }
        else
        {
            pData[14] = _DPLL_FREQ_CHG_OVER_10PER;
        }
    }
#endif

    // DPLL freq change under 10%, VCO band and div_o keep as before
    if(pData[14] == _DPLL_FREQ_CHG_UNDER_10PER)
    {
        // ucOutputdivider = DPLL_pixelclk_div[1:0]
        ucOutputdivider = ScalerGetBit(P1_DA_DPLL_OUTPUT_CLK_DIV, (_BIT1 | _BIT0));

        switch(ucOutputdivider)
        {
            case 0:

                pData[14] = 8;
                break;

            case 1:

                pData[14] = 4;
                break;

            case 2:

                pData[14] = 2;
                break;

            case 3:

                pData[14] = 1;
                break;

            default:

                break;
        }

        usMcode = (usMcode + (pData[14] / 2)) / pData[14];

        if((usMcode - 2) == (((WORD)(ScalerGetByte(P1_D9_DPLL_M_N_MSB) & 0x30) << 4) + ScalerGetByte(P1_BF_DPLL_M)))
        {
            ucDPLLSettingState = _DPLL_SET_OFFSET;
        }
        else
        {
            ucDPLLSettingState = _DPLL_SET_FREQ;
        }
    }
    else
    {
        // ----------- Previous Select Band & Div Alg. -----------
        // ucOutputdivider = DPLL VCO band
        PDATA_DWORD(1) = PDATA_DWORD(0) * 16;
        if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_0)
        {
            ucOutputdivider = 3;
        }
        else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_1)
        {
            ucOutputdivider = 2;
        }
        else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_2)
        {
            ucOutputdivider = 1;
        }
        else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_3)
        {
            ucOutputdivider = 0;
        }
        else
        {
            ucOutputdivider = 0;
#if((_DPLL_BAND11_SUPPORT == _ON) && (_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON))
            ucVcoBand = _VCO_BAND11;
#endif
        }

        // ------------- Div Alg. --------------
        // ucOutputdivider = DPLL_O[1:0]
        switch(ucOutputdivider)
        {
            case 0:

                pData[14] = 8;
                break;

            case 1:

                pData[14] = 4;
                break;

            case 2:

                pData[14] = 2;
                break;

            case 3:

                pData[14] = 1;
                break;

            default:

                break;
        }

        usMcode = (usMcode + (pData[14] / 2)) / pData[14];
    }

    switch(ucDPLLSettingState)
    {
        case _DPLL_SET_POWER_OFF:

            // Wait DEN STOP
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_PANEL_STYLE == _PANEL_LVDS)
            // Power Down LVDS
            ScalerDisplayLvdsPLL(_OFF);
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

            // Power Down DPLL
            ScalerSetBit(P1_C2_DPLL_WD, ~_BIT0, _BIT0);

        /*@fallthrough@*/
        case _DPLL_SET_VCO_BAND:

#if((_DPLL_BAND11_SUPPORT == _ON) && (_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON))
            // set DPLL VCO band and bypass calibration
            ScalerSetBit(P1_C3_DPLL_CAL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((ucVcoBand) << 6) | _BIT5);
#else
            // Manual set DPLL VCO band = 10 and bypass calibration
            ScalerSetBit(P1_C3_DPLL_CAL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT5));
#endif

        /*@fallthrough@*/
        case _DPLL_SET_FREQ:

            //////////////////////////////////////////////////////////////////////////////////////////////////
            // Old Formula : Icp * N_Code / M_Code = 0.5 * Fxtal / 27MHz (for xtal not 27MHz)               //
            // Icp set 2.5uA, 5uA, 7.5uA, 10uA......                                                        //
            // Precise formula of Chrage Pump Current depends on DPM, resistor, and band.                   //
            // If VCO band = 'b00, Icp = (700 * M * 2 * pi) / (778 * 0x01C1[7:5]).                          //
            // If VCO band = 'b01, Icp = (700 * M * 2 * pi) / (1340 * 0x01C1[7:5]).                         //
            // If VCO band = 'b10, Icp = (700 * M * 2 * pi) / (1880 * 0x01C1[7:5]).                         //
            // If VCO band = 'b11, Icp = (700 * M * 2 * pi) / (2340 * 0x01C1[7:5]).                         //
            // 700: DPLL max frequency design target is 700MHz; 778: Frequency curve in band00 is 778MHz.   //
            // Assume DPLL_M=0x13, DPM=0x13+2=21; DPN=2; reg_dpll_vcomd='b01; reg_dpll_rs[2:0]='b011;       //
            // Icp = (700 * 21 * 2 * 3.14) / (1340 * 13)                                                    //
            //////////////////////////////////////////////////////////////////////////////////////////////////
#if((_DPLL_BAND11_SUPPORT == _ON) && (_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON))
            PDATA_DWORD(0) = ((ucVcoBand == _VCO_BAND11) ? 2340 : 1880);
#else
            PDATA_DWORD(0) = 1880;
#endif
            PDATA_DWORD(0) = (DWORD)usMcode * 700UL * 628UL * 20UL / PDATA_DWORD(0) / ((7UL + (ScalerGetBit(P1_C1_DPLL_CRNT, (_BIT7 | _BIT6 | _BIT5)) >> 5UL) * 2UL) * 100UL);
            pData[1] = (PDATA_DWORD(0) + 25) / 50;
            pData[1] -= (pData[1] == 0) ? 0 : 1;

            DebugMessageDigital("6. DisplayPLL Charge Pump icp =", pData[1]);

            // Set M Code
            ScalerSetByte(P1_BF_DPLL_M, ((usMcode - 2) & 0xFF));
            ScalerSetBit(P1_D9_DPLL_M_N_MSB, ~(_BIT5 | _BIT4), (((usMcode - 2) >> 4) & 0x30));

            // M/N code should be written in porch
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

            // Set N Code and Output divider
            ScalerSetByte(P1_C0_DPLL_N, 0x00);

            // Set pixel clk divider (DIV_B)
            ScalerSetBit(P1_DA_DPLL_OUTPUT_CLK_DIV, ~(_BIT1 | _BIT0), ucOutputdivider);

            // Set Icp
            ScalerSetByte(P1_C1_DPLL_CRNT, (0x78 | (pData[1] & 0x07)));

        /*@fallthrough@*/
        case _DPLL_SET_POWER_ON:

            // DPLL VCORSTB Set to Normal
            ScalerSetBit(P1_E5_M2PLL_WD, ~_BIT1, (_DPLL_VCORSTB_NORMAL_VALUE << 1));

#if(_DPLL_WD_SET_REF_POWER == _ON)
            // DPLL Power Down
            if(ScalerGetBit(P1_C2_DPLL_WD, _BIT0) == _BIT0)
#endif
            {
                // Power Up DPLL
                ScalerSetBit(P1_C2_DPLL_WD, ~_BIT0, 0x00);
                DELAY_XUS(150);

                // Reset PFD, LPF
                ScalerSetBit(P1_C2_DPLL_WD, ~_BIT5, _BIT5);
                DELAY_5US();
                ScalerSetBit(P1_C2_DPLL_WD, ~_BIT5, 0x00);
            }

        /*@fallthrough@*/
        case _DPLL_SET_OFFSET:

            // Calculate DPLL Output Freq. According to current Settings
            PDATA_DWORD(0) = ulRefClk * 1000 / ((1 << (ucOutputdivider)) * 2) * usMcode / 2;

#if(_MN_DPLL_PATH_TYPE == _MN_DPLL_PATH2)

            // fvco = Xtal * M/N * 2^15 / (2^15 + offset), Freq Down.
            // (Dclk * 2^15)/ulFreq in Hz
            PDATA_DWORD(1) = GET_DWORD_MUL_DIV((PDATA_DWORD(0)), (1UL << 15), (ulFreq * 1000));

            // Target frequency of Dclk in Hz
            PDATA_WORD(0) = PDATA_DWORD(1) - (1 << 15);

#else

            // Offset resolution (Dclk / 2^15) in Hz
            PDATA_DWORD(1) = PDATA_DWORD(0) >> 15;

#if(_MN_DPLL_FREQ_UP == _ON)
            if(ScalerGetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, _BIT4) == 0x00)
            {
                // Target frequency of Dclk in Hz
                PDATA_WORD(0) = ((ulFreq * 1000) - PDATA_DWORD(0)) / PDATA_DWORD(1);
            }
            else
#endif
            {
                // Target frequency of Dclk in Hz
                PDATA_WORD(0) = (PDATA_DWORD(0) - (ulFreq * 1000)) / PDATA_DWORD(1);
            }

#endif

            PDATA_WORD(0) = PDATA_WORD(0) & 0x0fff;

            // Set Dpll Offset
            ScalerPLLSetDPLLOffset(PDATA_WORD(0));

            break;

        default:

            break;
    }
#endif

#if(_PANEL_STYLE == _PANEL_LVDS)
    // Recover LVDS PLL
    if(bDISPPower == _ON)
    {
        // Power On LVDS
        ScalerDisplayLvdsPLL(_ON);
    }
#endif
}
#endif // End of #if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F)

#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)
//--------------------------------------------------
// Description  : Set DPLL Freq
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLFreqNfCombo(DWORD ulFreq)
{
    BYTE ucDPLLSettingState = _DPLL_SET_POWER_OFF;
    bit bDISPPower = 0;
    BYTE ucNcode = 0;
    BYTE ucFcode_MSB4b = 0;
    WORD usFcode_LSB16b = 0;
    BYTE ucPostDiv = 0;
    BYTE ucPreDiv = 2;
    DWORD ultemp = 0;
    DWORD ulcurFreq = 0;

    bDISPPower = ScalerDisplayGetLvdsPowerStatus();

    // Lvds_data_clk = (Dclk * 7) / lvds_port, d domain is 1 path.
    // Pixel clk = D_domain_path_num * DCLK
    // = lvds_port_num * lvds_clk
    // Lvds_data_clk = 7 * lvds_clk

    PDATA_DWORD(1) = ((ulFreq * 7) >> _LVDS_OUTPUT_PORT);

    if(bDISPPower == _OFF)
    {
        if(PDATA_DWORD(1) >= _DPLL_BOUNDRY)
        {
            ucPostDiv = 0; // Div 1
        }
        else
        {
            ucPostDiv = 1; // Div 2
        }
    }
    else
    {
        // Calculate Current Freq =  (N.F + 2) * Xtal / Prediv / Postdiv
        ulcurFreq = (((((ScalerGetDWord(P1_C0_DPLL0) & 0x0FFFFFFF) + 0x200000) >> 14) * _EXT_XTAL) / ucPreDiv) >> (6 + ((ScalerGetByte(P1_D0_LVDSPLL_0) & (_BIT6 | _BIT5)) >> 5));

        // Check if Freq Modification Is Over 10 %
        if(ABSDWORD(PDATA_DWORD(1), ulcurFreq) > (ulcurFreq / 10))
        {
            if(PDATA_DWORD(1) >= _DPLL_BOUNDRY)
            {
                ucPostDiv = 0; // Div 1

                if(ulcurFreq >= _DPLL_BOUNDRY)
                {
                    ucDPLLSettingState = _DPLL_SET_FREQ;
                }
            }
            else
            {
                ucPostDiv = 1; // Div 2

                if(ulcurFreq < _DPLL_BOUNDRY)
                {
                    ucDPLLSettingState = _DPLL_SET_FREQ;
                }
            }
        }
        else
        {
            ucDPLLSettingState = _DPLL_SET_FREQ;
            ucPostDiv = (ScalerGetByte(P1_D0_LVDSPLL_0) & (_BIT6 | _BIT5)) >> 5;
        }
    }

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if((GET_AIO_MODERN_STANDBY_MODE() == _TRUE) && (GET_DPLL_POWER_STATUS() == _TRUE))
    {
        ucDPLLSettingState = _DPLL_SET_FREQ;
        ucPostDiv = (ScalerGetByte(P1_D0_LVDSPLL_0) & (_BIT6 | _BIT5)) >> 5;
    }
#endif

    switch(ucDPLLSettingState)
    {
        case _DPLL_SET_POWER_OFF:

            // Wait DEN STOP
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

            // Power Down LVDS Port AB CK_LVDS Clk
            ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~_BIT4, 0x00);

            // Clk Not Ready
            ScalerSetBit(P1_C0_DPLL0, ~_BIT4, 0x00);

            // Disable LDO
            ScalerSetBit(P1_D2_LVDSPLL_2, ~_BIT2, 0x00);

            // Power Down PLL
            ScalerSetBit(P1_D1_LVDSPLL_1, ~_BIT0, _BIT0);

        /*@fallthrough@*/
        case _DPLL_SET_VCO_BAND:
            // Set VCO Band
            ScalerSetBit(P1_D0_LVDSPLL_0, ~(_BIT3 | _BIT2), _BIT3);

        /*@fallthrough@*/
        case _DPLL_SET_FREQ:
        case _DPLL_SET_POWER_ON:

            // Set Postdiv and Prediv
            if(ucPreDiv == 1)
            {
                ScalerSetBit(P1_D0_LVDSPLL_0, ~(_BIT6 | _BIT5 | _BIT4), ((ucPostDiv << 5) | _BIT4));
            }
            else
            {
                ScalerSetBit(P1_D0_LVDSPLL_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), ((ucPostDiv << 5) | (ucPreDiv - 2)));
            }

            // Calculate N.F
            // PDATA_DWORD(1) = ((ulFreq * 7) >> _LVDS_OUTPUT_PORT)
            // NFcode = PDATA_DWORD(1) * 2 * Postdiv / Xtal
            ucNcode = (PDATA_DWORD(1) << ucPostDiv) * ucPreDiv / _EXT_XTAL;
            ucFcode_MSB4b = (((PDATA_DWORD(1) << ucPostDiv) * ucPreDiv - ((DWORD)_EXT_XTAL) * ucNcode) << 4) / _EXT_XTAL;
            usFcode_LSB16b = (((((PDATA_DWORD(1) << ucPostDiv) * ucPreDiv - ((DWORD)_EXT_XTAL) * ucNcode) << 4) - ucFcode_MSB4b * _EXT_XTAL) << 16) / _EXT_XTAL;

            //////////////////////////////////////////////////////////////////////////////////////////////////
            // Icp set 2.5uA, 5uA, 7.5uA, 10uA......                                                        //
            // Precise formula of Chrage Pump Current depends on DPM, resistor, and band.                   //
            // If VCO band = 'b00, Icp = (700 * N* 2 * pi) /  (1540 * 0x01D3[2:0]).                         //
            // If VCO band = 'b01, Icp = (700 * N * 2 * pi) / (1810 * 0x01D3[2:0]).                         //
            // If VCO band = 'b10, Icp = (700 * N * 2 * pi) / (2120 * 0x01D3[2:0]).                         //
            // If VCO band = 'b11, Icp = (700 * N * 2 * pi) / (2390 * 0x01D3[2:0]).                         //
            // 700: DPLL max frequency design target is 700MHz; 778: Frequency curve in band00 is 778MHz.   //
            // Assume DPLL_M=0x13, DPM=0x13+2=21; DPN=2; reg_dpll_vcomd='b01; reg_dpll_rs[2:0]='b011;       //
            // Icp = (700 * 21 * 2 * 3.14) / (1340 * 13)                                                    //
            //////////////////////////////////////////////////////////////////////////////////////////////////

            PDATA_DWORD(0) = 2120;

            PDATA_DWORD(0) = (ucNcode * 700UL * 628 * 20) / PDATA_DWORD(0) / ((7 + (ScalerGetBit(P1_D3_LVDSPLL_3, _BIT2 | _BIT1 | _BIT0) *2)) * 100);
            pData[1] = (PDATA_DWORD(0) + 25) / 50;
            pData[1] -= (pData[1] == 0) ? 0 : 1;

            // Set CMU Icp, Ipfrs
            ScalerSetByte(P1_D3_LVDSPLL_3, ((pData[1] & 0x07) << 5) | 0x1B);

            // Set LVDS Dual Mode Div
            ScalerSetBit(P1_D1_LVDSPLL_1, ~_BIT1, ((_LVDS_OUTPUT_PORT == _LVDS_1_PORT) ? _BIT1 : 0x00));

            // CMU PI, ipi = 10uA
            ScalerSetBit(P1_D2_LVDSPLL_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT1 | _BIT0), _BIT1);

            // Power Up PLL
            ScalerSetBit(P1_D1_LVDSPLL_1, ~_BIT0, 0x00);

            // Enable LDO
            ScalerSetBit(P1_D2_LVDSPLL_2, ~_BIT2, _BIT2);

            DELAY_XUS(150);

            // Set N.f and Double Buffer For N.f Code
            ultemp = (((DWORD)(ucNcode - 2) << 20) | ((DWORD)ucFcode_MSB4b << 16) | (DWORD)usFcode_LSB16b);
            ScalerPLLSetDPLLNFcode(ultemp);

            // Clk Ready
            ScalerSetBit(P1_C0_DPLL0, ~_BIT4, _BIT4);

            if(bDISPPower == _ON)
            {
                // Power On LVDS Port AB CK_LVDS Clk
                ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~_BIT4, _BIT4);
            }

            break;

        default:

            break;
    }
}
#endif // End of #if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)

#if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F)
//--------------------------------------------------
// Description  : Set DPLL Freq
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLFreqNf(DWORD ulFreq)
{
    BYTE ucDPLLSettingState = _DPLL_SET_POWER_OFF;
    bit bDISPPower = 0;
    DWORD ulRefClk = 0;
    BYTE ucPreDiv = 1;
    BYTE ucNcode = 0;
    BYTE ucFcode_MSB4b = 0;
    WORD usFcode_LSB16b = 0;
    BYTE ucPostDiv = 0;
    DWORD ultemp = 0;
    DWORD ulvcoFreq = 0;
    BYTE ucBypassDivide2 = 0;

#if(_PANEL_STYLE == _PANEL_LVDS)

    ScalerPLLSetDisplayPLL(ulFreq); // change name, as ScalerPLLSetOutputInterfacePLL, CYShih

#elif(_PANEL_STYLE == _PANEL_DPTX) // Elif of #if(_PANEL_STYLE == _PANEL_LVDS)

    ScalerPLLSetDPLLRefPLL(ulFreq);

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

    ulRefClk = ScalerPLLGetDPLLRefClk(ulFreq);

    ulFreq = (ulFreq >> _D_DOMAIN_PATH);

#if(_PANEL_STYLE == _PANEL_LVDS)

    bDISPPower = ScalerDisplayGetLvdsPowerStatus();

#elif(_PANEL_STYLE == _PANEL_DPTX)

    bDISPPower = ScalerPLLGetDptxPowerStatus();

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

    PDATA_DWORD(1) = ulFreq * 16;

    if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_0)
    {
        ucPostDiv = 3;
    }
    else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_1)
    {
        ucPostDiv = 2;
    }
    else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_2)
    {
        ucPostDiv = 1;
    }
    else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_3)
    {
        ucPostDiv = 0;
    }
    else
    {
        ucPostDiv = 0;
        ucBypassDivide2 = 1;
    }

    if(bDISPPower == _ON)
    {
        ucDPLLSettingState = _DPLL_SET_FREQ;
    }

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if((GET_AIO_MODERN_STANDBY_MODE() == _TRUE) && (GET_DPLL_POWER_STATUS() == _TRUE))
    {
        ucDPLLSettingState = _DPLL_SET_FREQ;
    }
#endif

    switch(ucDPLLSettingState)
    {
        case _DPLL_SET_POWER_OFF:

            // Wait DEN STOP
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_PANEL_STYLE == _PANEL_LVDS)
            // Power Down LVDS
            ScalerDisplayLvdsPLL(_OFF);
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

            // Disable LDO
            ScalerSetBit(P1_D2_DPLL_ANALOG_SETTING_2, ~_BIT2, 0x00);

            // Power Down PLL
            ScalerSetBit(P1_D1_DPLL_ANALOG_SETTING_1, ~_BIT0, _BIT0);

        /*@fallthrough@*/
        case _DPLL_SET_VCO_BAND:
            // Set VCO Band
            ScalerSetBit(P1_D0_DPLL_ANALOG_SETTING_0, ~(_BIT3 | _BIT2), _BIT3);

        /*@fallthrough@*/
        case _DPLL_SET_FREQ:
        case _DPLL_SET_POWER_ON:

            // Set Postdiv and Prediv
            if(ucPreDiv < 2)
            {
                ScalerSetBit(P1_D0_DPLL_ANALOG_SETTING_0, ~(_BIT6 | _BIT5 | _BIT4), (ucPostDiv << 5) | _BIT4);
            }
            else
            {
                ScalerSetBit(P1_D0_DPLL_ANALOG_SETTING_0, ~(_BIT6 | _BIT5 | _BIT4), (ucPostDiv << 5));
                ScalerSetByte(P1_C9_DPLL_CLK_CTRL_1, (ucPreDiv - 2));
            }

            // Set fixed divide 2
            if(ucBypassDivide2 == 1)
            {
                ScalerSetBit(P1_BF_DPLL_CLK_CTRL_0, ~_BIT7, _BIT7);
            }
            else
            {
                ScalerSetBit(P1_BF_DPLL_CLK_CTRL_0, ~_BIT7, 0x00);
            }

            // Calculate N.F
            // NFcode = ulFreq * 2 * Postdiv * ucPreDiv / Xtal, 2 is a fixed divider, 2 can be bypassed by 0x01BF[7]
            ulvcoFreq = ulFreq << ucPostDiv << (1 - ucBypassDivide2);
            ucNcode = ulvcoFreq * ucPreDiv / ulRefClk;
            ucFcode_MSB4b = ((ulvcoFreq * ucPreDiv - ((DWORD)ulRefClk) * ucNcode) << 4) / ulRefClk;
            usFcode_LSB16b = ((((ulvcoFreq * ucPreDiv - ((DWORD)ulRefClk) * ucNcode) << 4) - ucFcode_MSB4b * ulRefClk) << 16) / ulRefClk;

            //////////////////////////////////////////////////////////////////////////////////////////////////
            // Icp set 2.5uA, 5uA, 7.5uA, 10uA......                                                        //
            // Precise formula of Chrage Pump Current depends on DPM, resistor, and band.                   //
            // If VCO band = 'b00, Icp = (700 * N* 2 * pi) /  (1540 * 0x01D3[2:0]).                         //
            // If VCO band = 'b01, Icp = (700 * N * 2 * pi) / (1810 * 0x01D3[2:0]).                         //
            // If VCO band = 'b10, Icp = (700 * N * 2 * pi) / (2120 * 0x01D3[2:0]).                         //
            // If VCO band = 'b11, Icp = (700 * N * 2 * pi) / (2390 * 0x01D3[2:0]).                         //
            // 700: DPLL max frequency design target is 700MHz; 778: Frequency curve in band00 is 778MHz.   //
            // Assume DPLL_M=0x13, DPM=0x13+2=21; DPN=2; reg_dpll_vcomd='b01; reg_dpll_rs[2:0]='b011;       //
            // Icp = (700 * 21 * 2 * 3.14) / (1340 * 13)                                                    //
            //////////////////////////////////////////////////////////////////////////////////////////////////

            PDATA_DWORD(0) = 1804;

            PDATA_DWORD(0) = (ucNcode * 1400UL * 628 * 20) / PDATA_DWORD(0) / ((7 + (ScalerGetBit(P1_D3_DPLL_ANALOG_SETTING_3, _BIT2 | _BIT1 | _BIT0) *2)) * 100);
            pData[1] = (PDATA_DWORD(0) + 25) / 50;
            pData[1] -= (pData[1] == 0) ? 0 : 1;

            // Set CMU Icp, Ipfrs
            ScalerSetByte(P1_D3_DPLL_ANALOG_SETTING_3, ((pData[1] & 0x07) << 5) | 0x1B);

            // Get ipi from freq.
            if(ulvcoFreq < 320000)
            {
                pData[1] = 3;
            }
            else if(ulvcoFreq < 380000)
            {
                pData[1] = 2;
            }
            else if(ulvcoFreq < 525000)
            {
                pData[1] = 1;
            }
            else
            {
                pData[1] = 0;
            }

            // CMU PI, set ipi
            ScalerSetBit(P1_D2_DPLL_ANALOG_SETTING_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT1 | _BIT0), ((pData[1] & 0x03) << 5) | _BIT1);

            // Power Up PLL
            ScalerSetBit(P1_D1_DPLL_ANALOG_SETTING_1, ~_BIT0, 0x00);

            // Enable LDO
            ScalerSetBit(P1_D2_DPLL_ANALOG_SETTING_2, ~_BIT2, _BIT2);

            DELAY_XUS(150);

            // Set N.f and Double Buffer For N.f Code
            ultemp = (((DWORD)(ucNcode - 2) << 20) | ((DWORD)ucFcode_MSB4b << 16) | (DWORD)usFcode_LSB16b);
            ScalerPLLSetDPLLNFcode(ultemp);

#if(_PANEL_STYLE == _PANEL_LVDS)
            if(bDISPPower == _ON)
            {
                // Power On LVDS Clk
                ScalerDisplayLvdsPLL(_ON);
            }
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

            break;

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Calulate New PLL Parameter
// Input Value  : ulCountNew, ulCountOld, ulValueOld, bPropitional
// Output Value : New Parameter
//--------------------------------------------------
DWORD ScalerPLLGetNewCount(DWORD ulCountNew, DWORD ulCountOld, DWORD ulValueOld, bit bProportion)
{
    if(bProportion == _TRUE)
    {
        return GET_DWORD_MUL_DIV(ulCountNew, ulValueOld, ulCountOld);
    }
    else
    {
        return GET_DWORD_MUL_DIV(ulCountOld, ulValueOld, ulCountNew);
    }
}

//--------------------------------------------------
// Description  : Set FrameSync offset to match I/D active time & last-line target
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDPLLFineTuneFrameSyncLineBuffer(void)
{
    WORD usDVtotal = 0;
    WORD usLastLine = 0;
    DWORD ulDiffOffsetOld = 0;
    DWORD ulDiffOffsetNew = 0;
    DWORD ulInputActiveRegion = 0;
    DWORD ulDisplayActiveRegion = 0;
    bit bProportion = _TRUE;

    DWORD ulDclk = GET_D_CLK_FREQ();
    DWORD ulDtotal = 0;
    BYTE ucDebounceCnt = 5;
    DWORD ulPanelClockMaxSpread = MAXOF(_PANEL_PIXEL_CLOCK_MAX_SPREAD, _PANEL_PIXEL_CLOCK_KHZ);
    DWORD ulPanelClockMinSpread = MINOF(_PANEL_PIXEL_CLOCK_MIN_SPREAD, _PANEL_PIXEL_CLOCK_KHZ);
    StructDHtotalFTStatus stDHtotalFTStatus;

    // Temporary Enable Frame Sync Fine Tune for Interlace Mode in order to Get Equal Frame Period
    if(GET_INTERLACED_MODE() == _TRUE)
    {
        if(ScalerGetBit(P0_32_SCALE_CONTROL_REG, _BIT6) == _BIT6)
        {
            // Video Compensation on Even Field; Enable Last Line Measure on Odd Field
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT7 | _BIT6), _BIT7);
        }
        else
        {
            // Video Compensation on Odd Field; Enable Last Line Measure on Even Field
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
    }
    else
    {
        // Disable Last Line Measure by Field
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT7 | _BIT6), 0x00);
    }

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        ulDisplayActiveRegion = GET_MDOMAIN_D_ACTIVE_REGIOM_BACKUP();
        g_ulInputActiveRegionBackUp = ScalerMeasureGetInputRegionCountResult(_WAIT);
    }
    else
#endif
    {
        ScalerTimerWaitForEvent(_EVENT_IVS);

        ulDisplayActiveRegion = ScalerMDomainGetDisplayActiveRegion();

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
        SET_MDOMAIN_D_ACTIVE_REGIOM_BACKUP(ulDisplayActiveRegion);
#endif

        g_ulInputActiveRegionBackUp = ScalerMeasureGetInputRegionCountResult(_NOT_WAIT);

        DebugMessageFS("InputRegionCount", g_ulInputActiveRegionBackUp);
        DebugMessageFS("DisplayRegionCount", ulDisplayActiveRegion);
    }

    if(ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1, _BIT0) == _BIT0)
    {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
        {
            // I Den add line when VSD enable
            pData[0] = 2;
        }
        else
#endif
        {
            // I Den add line when VSD enable
            pData[0] = 1;
        }

        ulInputActiveRegion = g_ulInputActiveRegionBackUp - (((DWORD)g_stMDomainInputData.usHTotal * ((g_ulInputActiveRegionBackUp + 2) >> 2) * pData[0] / ((DWORD)g_stMDomainInputData.usHTotal * g_stMDomainInputData.usVHeight + g_stMDomainInputData.usHWidth)) << 2);
    }
    else
    {
        ulInputActiveRegion = g_ulInputActiveRegionBackUp;
    }

#if((_PANEL_STYLE == _PANEL_VBO) && (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F))
    // Get current (N code + 4) * 2^12 + F code
    PDATA_WORD(0) = (WORD)((ScalerGetBit(P38_DC_DPTX_CMU12, 0x0F) << 4) | (ScalerGetByte(P38_DD_DPTX_CMU13) >> 4));
    PDATA_WORD(1) = (WORD)((ScalerGetBit(P38_DD_DPTX_CMU13, 0x0F) << 8) | ScalerGetByte(P38_DE_DPTX_CMU14));
    ulDiffOffsetOld = ((DWORD)PDATA_WORD(0) + 4) * 4096 + PDATA_WORD(1);
#elif((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
    // Get current (N code + 2) * 2^20 + F code
    ulDiffOffsetOld = ((ScalerGetDWord(_REG_DPLL_N_F_CODE_0) & 0x0FFFFFFF) + 0x200000);
#else

    ulDiffOffsetOld = (((WORD)(ScalerGetByte(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB) & 0x0F) << 8) | ScalerGetByte(P1_C5_DCLK_FINE_TUNE_OFFSET_LSB));

    DebugMessageFS("Original offset", ulDiffOffsetOld);

#if(_MN_DPLL_PATH_TYPE == _MN_DPLL_PATH2)

    // DPLL path 2 frequency and offset is in inverse propition
    bProportion = _FALSE;

    // Get current (2^15 + offset)
    ulDiffOffsetOld = 32768 + ulDiffOffsetOld;

#else

#if(_MN_DPLL_FREQ_UP == _ON)
    if(ScalerGetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, _BIT4) == 0x00)
    {
        // Get current (2^15 + offset)
        ulDiffOffsetOld = 32768 + ulDiffOffsetOld;
    }
    else
#endif
    {
        // Get current (2^15 - offset)
        ulDiffOffsetOld = 32768 - ulDiffOffsetOld;
    }

#endif

#endif

    /////////////////////////////////////////////////////////////////////////
    ///
    /// Path 1: active_count and offset relation are in inverse proportion when frame sync fine tune
    ///
    /// (disp_act_region * offset_old) = (input_act_region * offset_new)
    /// offset_new = disp_act_region * offset_old / input_act_region
    /// offset_bias = offset_new - offset_old
    ///
    ///                   abs(disp_act_region - input_act_region) * offset_old
    /// Offset bias =  -----------------------------------------------------------
    ///                                     input_act_region
    ///
    /////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////
    ///
    /// Path 2: active_count and offset relation are in direct proportion when frame sync fine tune
    ///
    /// (disp_act_region / offset_old) = (input_act_region / offset_new)
    /// offset_new = input_act_region / disp_act_region * offset_old
    /// offset_bias = offset_new - offset_old
    ///
    ///                       abs(input_act_region - disp_act_region) * offset_old
    /// Offset_bias =  ----------------------------------------------------------------
    ///                                      disp_act_region
    ///
    /////////////////////////////////////////////////////////////////////////

    while(ucDebounceCnt > 0)
    {
        //=====================================
        // Measure input/ display active region
        //=====================================
        ulDisplayActiveRegion = ScalerMDomainGetDisplayActiveRegion();
        DebugMessageScaler("DisplayRegionCount", ulDisplayActiveRegion);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// N.F PLL: active_count and NF code relation are in inverse proportion when frame sync fine tune
        ///
        /// (disp_act_region * N.F_old) = (input_act_region * N.F_new)
        /// N.F_new = disp_act_region * N.F_old / input_act_region
        ///
        /////////////////////////////////////////////////////////////////////////

#if((_MEASURE_ADJUSTED_IHF_SUPPORT == _ON) || (_MEASURE_ADJUSTED_IVF_SUPPORT == _ON))
        // Calculate NF code
        ulDiffOffsetNew = ScalerPLLGetNewCount(ScalerMeasureGetAdjustedActiveRegionCount(GET_MDOMAIN_INPUT_HWIDTH(), GET_MDOMAIN_INPUT_VHEIGHT()), ulDisplayActiveRegion, ulDiffOffsetOld, !bProportion);
#else
        ulDiffOffsetNew = ScalerPLLGetNewCount(ulInputActiveRegion, ulDisplayActiveRegion, ulDiffOffsetOld, ~bProportion);
#endif
        // Calculate Dclk
        ulDclk = (ScalerPLLGetNewCount(ulDiffOffsetNew, ulDiffOffsetOld, GET_D_CLK_FREQ(), bProportion));

        stDHtotalFTStatus = ScalerMDomainDHtotalFinetune(ulDclk, ulPanelClockMaxSpread, ulPanelClockMinSpread);

        if(stDHtotalFTStatus.usDHtotal != GET_MDOMAIN_OUTPUT_HTOTAL())
        {
            SET_MDOMAIN_OUTPUT_HTOTAL(stDHtotalFTStatus.usDHtotal);
            SET_DIS_TIMING_GEN_H_TOTAL(GET_MDOMAIN_OUTPUT_HTOTAL());

            ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);

            if(stDHtotalFTStatus.b1DHtotalFineTuneStatus == _FALSE)
            {
                break;
            }
        }
        else
        {
            break;
        }

        ucDebounceCnt --;
    }

    // Measure DVtotal in frame sync mode
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
    GET_DVTOTAL_LASTLINE(usDVtotal);

    // Pop out Last line
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, 0x00);
    GET_DVTOTAL_LASTLINE(usLastLine);
    usLastLine = (usLastLine << _D_DOMAIN_PATH);

#if(_LAST_LINE_FINETUNE_ENABLE == _ENABLE)
#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _FALSE)
#endif
    {
        /////////////////////////////////////////////////////////////////////////
        ///
        /// Path 1: Dtotal pixel and offset relation are in direct proportion when last line fine tune
        ///
        /// Fine Tune Last Line to Panel Target
        /// Dtotal = DHtotal * DV count + Last-line
        ///
        /// Dtotal' = Dtotal * (2^15 - offset_new) / (2^15 - offset_old)
        ///
        /////////////////////////////////////////////////////////////////////////

        /////////////////////////////////////////////////////////////////////////
        ///
        /// Path 2: Dtotal pixel and offset relation are in inverse proportion when last line fine tune
        ///
        /// Fine Tune Last Line to Panel Target
        /// Dtotal = DHtotal * DV count + Last-line
        ///
        /// Dtotal' = Dtotal * (2^15 + offset_old) / (2^15 + offset_new)
        ///
        /////////////////////////////////////////////////////////////////////////

        DWORD ulDtotalNew = 0;
        DWORD ulDtotalTemp = 0;

        // Calculate Frame Sync finetune Dtotal
        ulDtotal = (DWORD)usDVtotal * g_stMDomainOutputData.usHTotal + usLastLine;

        ulDtotal = ScalerPLLGetNewCount(ulDiffOffsetNew, ulDiffOffsetOld, ulDtotal, bProportion);

        // Calculate new last-line
        usLastLine = ulDtotal % g_stMDomainOutputData.usHTotal;

        DebugMessageFS("Estimated last-line", usLastLine);

        // Calculate modified Dtotal
        ulDtotalNew = ulDtotal - usLastLine + _LAST_LINE_TARGET;

        if(abs(usLastLine - _LAST_LINE_TARGET) > (g_stMDomainOutputData.usHTotal >> 1))
        {
            if(usLastLine > _LAST_LINE_TARGET)
            {
                ulDtotalNew += (DWORD)g_stMDomainOutputData.usHTotal;  // +
            }
            else
            {
                ulDtotalNew -= (DWORD)g_stMDomainOutputData.usHTotal;  // -
            }
        }

        ulDiffOffsetNew = ScalerPLLGetNewCount(ulDtotalNew, ulDtotal, ulDiffOffsetNew, bProportion);
        ulDclk = (ScalerPLLGetNewCount(ulDiffOffsetNew, ulDiffOffsetOld, GET_D_CLK_FREQ(), bProportion));

        ulDtotalTemp = ScalerMDomainDtotalLastLineFinetune(ulDclk, ulPanelClockMaxSpread, ulPanelClockMinSpread, ulDtotalNew);

        if(ulDtotalTemp != ulDtotalNew)
        {
            ulDiffOffsetNew = ScalerPLLGetNewCount(ulDtotalTemp, ulDtotalNew, ulDiffOffsetNew, bProportion);
            ulDclk = (ScalerPLLGetNewCount(ulDiffOffsetNew, ulDiffOffsetOld, GET_D_CLK_FREQ(), bProportion));

            ulDtotalNew = ulDtotalTemp;
            DebugMessageFS("_Last_line_modify_Dclk", ulDclk);
        }

        // Modify Dt by new Dtotal & old Dtotal
        ScalerMemoryCompensateDtForLastLine(ulDtotalNew, ulDtotal);
    }
#endif

    SET_D_CLK_FREQ(ScalerPLLGetNewCount(ulDiffOffsetNew, ulDiffOffsetOld, GET_D_CLK_FREQ(), bProportion));

    DebugMessageScaler("Dclk fine tune", GET_D_CLK_FREQ());

#if((_PANEL_STYLE == _PANEL_VBO) && (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F))
    ScalerPLLSetDPLLRefPLL(GET_D_CLK_FREQ());
#elif((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
    // Apply N.F for last-line
    ScalerPLLSetDPLLNFcode(ulDiffOffsetNew - 0x200000);
#else

#if(_MN_DPLL_PATH_TYPE == _MN_DPLL_PATH2)

    // Apply Offset for last-line
    ScalerPLLSetDPLLOffset(ulDiffOffsetNew - 32768);
    DebugMessageFS("New offset", ulDiffOffsetNew - 32768);

#else

#if(_MN_DPLL_FREQ_UP == _ON)
    if(ScalerGetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, _BIT4) == 0x00)
    {
        // Apply Offset for last-line
        ScalerPLLSetDPLLOffset(ulDiffOffsetNew - 32768);
        DebugMessageFS("New offset", ulDiffOffsetNew - 32768);
    }
    else
#endif
    {
        // Apply Offset for last-line
        ScalerPLLSetDPLLOffset(32768 - ulDiffOffsetNew);
        DebugMessageFS("New offset", 32768 - ulDiffOffsetNew);
    }

#endif

#endif

    // Switch to "input active region"
    ScalerMeasureSetInputRegionCount(_ACTIVE_REGION_TYPE);

    // Disable Last Line Measure by Field
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT7 | _BIT6), 0x00);
}

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set FrameSync offset to match I/D active time & last-line target
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDPLLFineTuneFrameSyncFrameBuffer(void)
{
    WORD usDVtotal = 0;
    WORD usLastLine = 0;
    WORD usDVtotalNext = 0;
    WORD usLastLineNext = 0;
    DWORD ulDiffOffsetOld = 0;
    DWORD ulDiffOffsetNew = 0;
    DWORD ulPixel2offsetMax = 0;
    DWORD ulPixel2offsetMin = 0;
    DWORD ulPixelPerOffsetOld = 0;
    BYTE ucN = 2;
    bit bProportion = _TRUE;
    DWORD ulDclk = GET_D_CLK_FREQ();
    DWORD ulDtotal = 0;
    DWORD ulDtotalNew = 0;
    DWORD ulDtotalTemp = 0;
    DWORD ulPanelClockMaxSpread = MAXOF(_PANEL_PIXEL_CLOCK_MAX_SPREAD, _PANEL_PIXEL_CLOCK_KHZ);
    DWORD ulPanelClockMinSpread = MINOF(_PANEL_PIXEL_CLOCK_MIN_SPREAD, _PANEL_PIXEL_CLOCK_KHZ);


#if(_LAST_LINE_FINETUNE_ENABLE == _DISABLE)
    return;
#endif

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        return;
    }
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }

    if(GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY)
    {
        BYTE ucRawN = 1;

        ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_27_N_FOR_MN_FRAME_RATE, 1, &ucRawN, _AUTOINC);

        if(ucRawN != 0xFF)
        {
            ucN = ucRawN + 1;
        }

        for(pData[0] = 0; pData[0] < ucN; pData[0]++)
        {
            ScalerTimerWaitForEvent(_EVENT_DVS);
        }

        ScalerTimerWaitForEvent(_EVENT_DVS);
    }

    // Measure DVtotal in frame sync mode
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
    GET_DVTOTAL_LASTLINE(usDVtotal);

    // Pop out Last line
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, 0x00);
    GET_DVTOTAL_LASTLINE(usLastLine);
    usLastLine = (usLastLine << _D_DOMAIN_PATH);

    if(GET_INTERLACED_MODE() == _TRUE)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);

        // Pop out DVtotal
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
        GET_DVTOTAL_LASTLINE(usDVtotalNext);

        // Pop out Last line
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, 0x00);
        GET_DVTOTAL_LASTLINE(usLastLineNext);
        usLastLineNext = (usLastLineNext << _D_DOMAIN_PATH);
    }

#if((_PANEL_STYLE == _PANEL_VBO) && (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F))
    // Get current (N code + 4) * 2^12 + F code
    PDATA_WORD(0) = (WORD)((ScalerGetBit(P38_DC_DPTX_CMU12, 0x0F) << 4) | (ScalerGetByte(P38_DD_DPTX_CMU13) >> 4));
    PDATA_WORD(1) = (WORD)((ScalerGetBit(P38_DD_DPTX_CMU13, 0x0F) << 8) | ScalerGetByte(P38_DE_DPTX_CMU14));
    ulDiffOffsetOld = ((DWORD)PDATA_WORD(0) + 4) * 4096 + PDATA_WORD(1);
#elif((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
    // Get current (N code + 2) * 2^20 + F code
    ulDiffOffsetOld = ((ScalerGetDWord(_REG_DPLL_N_F_CODE_0) & 0xFFFFFFF) + 0x200000);
#else

    ulDiffOffsetOld = (((WORD)(ScalerGetByte(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB) & 0x0F) << 8) | ScalerGetByte(P1_C5_DCLK_FINE_TUNE_OFFSET_LSB));

    DebugMessageFS("Original offset", ulDiffOffsetOld);

#if(_MN_DPLL_PATH_TYPE == _MN_DPLL_PATH2)

    // DPLL path 2 frequency and offset is in inverse propition
    bProportion = _FALSE;

    // Get current (2^15 + offset)
    ulDiffOffsetOld = 32768 + ulDiffOffsetOld;
#else

#if(_MN_DPLL_FREQ_UP == _ON)
    if(ScalerGetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, _BIT4) == 0x00)
    {
        // Get current (2^15 + offset)
        ulDiffOffsetOld = 32768 + ulDiffOffsetOld;
    }
    else
#endif
    {
        // Get current (2^15 - offset)
        ulDiffOffsetOld = 32768 - ulDiffOffsetOld;
    }

#endif

#endif
    ulDiffOffsetNew = ulDiffOffsetOld;

    // Calculate Dtotal
    ulDtotal = (DWORD)usDVtotal * g_stMDomainOutputData.usHTotal + usLastLine;

    /////////////////////////////////////////////////////////////////////////
    ///
    /// Path 1: Dtotal pixel and offset relation are in direct proportion when last line fine tune
    ///
    /// Fine Tune Last Line to Panel Target
    /// Dtotal = DHtotal * DV count + Last-line
    ///
    /// Dtotal' = Dtotal * (2^15 - offset_new) / (2^15 - offset_old)
    ///
    /////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////
    ///
    /// Path 2: Dtotal pixel and offset relation are in inverse proportion when last line fine tune
    ///
    /// Fine Tune Last Line to Panel Target
    /// Dtotal = DHtotal * DV count + Last-line
    ///
    /// Dtotal' = Dtotal * (2^15 + offset_old) / (2^15 + offset_new)
    ///
    /////////////////////////////////////////////////////////////////////////

    if(GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY)
    {
        // Check minimum value of N
        if(ucN < 2)
        {
            ucN = 2;
        }

        PDATA_WORD(0) = GET_FREE_RUN_DVTOTAL();
        PDATA_WORD(1) = usDVtotal - ((PDATA_WORD(0) + 1) * (ucN - 1)); // usframesync_dvtotal

        // check if free run DVtotal less than frame sync DVtotal
        if(PDATA_WORD(0) < PDATA_WORD(1))
        {
            PDATA_WORD(0) = usDVtotal / ucN;
            SET_FREE_RUN_DVTOTAL(PDATA_WORD(0));
            PDATA_WORD(1) = usDVtotal - ((PDATA_WORD(0) + 1) * (ucN - 1));
        }

        ulPixelPerOffsetOld = ((ulDtotal % ulDiffOffsetOld) != 0x00) ? ((ulDtotal / ulDiffOffsetOld) + 1) : (ulDtotal / ulDiffOffsetOld);

        // Calcualte last line target maximum
        ulPixel2offsetMax = (DWORD)(g_stMDomainOutputData.usHTotal * (PDATA_WORD(0) - PDATA_WORD(1))) + _MN_LAST_LINE_MAX - usLastLine;
        ulPixel2offsetMax /= ulPixelPerOffsetOld;

        // Calcualte last line target minimum
        ulPixel2offsetMin = (DWORD)(g_stMDomainOutputData.usHTotal * (PDATA_WORD(0) - PDATA_WORD(1))) + _MN_LAST_LINE_MIN - usLastLine;
        ulPixel2offsetMin = (ulPixel2offsetMin / ulPixelPerOffsetOld) + 1;

        // Check new last line boundary
        if(ulPixel2offsetMax < ulPixel2offsetMin)
        {
            PDATA_WORD(1) = _LAST_LINE_TARGET - ((usLastLine + (ulPixel2offsetMax * ulPixelPerOffsetOld)) % g_stMDomainOutputData.usHTotal);
            PDATA_WORD(1) /= (ucN - 1);

            // Set Last line
            SET_FREE_RUN_LAST_LINE(GET_MDOMAIN_OUTPUT_HTOTAL() - PDATA_WORD(1));

            ulDtotalNew = ulDtotal + (ulPixel2offsetMax * ulPixelPerOffsetOld);
        }
        else
        {
            ulDtotalNew = ulDtotal + ((ulPixel2offsetMax + ulPixel2offsetMin) * ulPixelPerOffsetOld / 2);
        }
    }
    else
    {
        // Calculate modified Dtotal
        ulDtotalNew = ulDtotal - usLastLine + _LAST_LINE_TARGET;

        if(abs(usLastLine - _LAST_LINE_TARGET) > (g_stMDomainOutputData.usHTotal >> 1))
        {
            if(usLastLine > _LAST_LINE_TARGET)
            {
                ulDtotalNew += (DWORD)g_stMDomainOutputData.usHTotal;  // +
            }
            else
            {
                ulDtotalNew -= (DWORD)g_stMDomainOutputData.usHTotal;  // -
            }
        }
    }

    ulDiffOffsetNew = ScalerPLLGetNewCount(ulDtotalNew, ulDtotal, ulDiffOffsetNew, bProportion);

    ulDclk = (ScalerPLLGetNewCount(ulDiffOffsetNew, ulDiffOffsetOld, GET_D_CLK_FREQ(), bProportion));

    ulDtotalTemp = ScalerMDomainDtotalLastLineFinetune(ulDclk, ulPanelClockMaxSpread, ulPanelClockMinSpread, ulDtotalNew);

    if(ulDtotalTemp != ulDtotalNew)
    {
        ulDiffOffsetNew = ScalerPLLGetNewCount(ulDtotalTemp, ulDtotalNew, ulDiffOffsetNew, bProportion);
        ulDclk = (ScalerPLLGetNewCount(ulDiffOffsetNew, ulDiffOffsetOld, GET_D_CLK_FREQ(), bProportion));

        ulDtotalNew = ulDtotalTemp;
        DebugMessageFS("_Last_line_modify_Dclk", ulDclk);
    }

    if(GET_INTERLACED_MODE() == _TRUE)
    {
        // Calculate next frame Dtotal
        ulDtotal = ((DWORD)usDVtotalNext * g_stMDomainOutputData.usHTotal + usLastLineNext);

        // Using new Dclk offset, calculate next frame new last line
        PDATA_DWORD(1) = ScalerPLLGetNewCount(ulDiffOffsetNew, ulDiffOffsetOld, ulDtotal, bProportion);
        PDATA_DWORD(1) = PDATA_DWORD(1) % g_stMDomainOutputData.usHTotal;

        // (0 < (next frame new last line) <= 0.05 line) or (0.95 line <= (next frame new last line) <= 1 line), modify Dclk offset
        if((PDATA_DWORD(1) <= ((DWORD)g_stMDomainOutputData.usHTotal * 5 / 100)) || (PDATA_DWORD(1) >= ((DWORD)g_stMDomainOutputData.usHTotal * 95 / 100)))
        {
            // Calculate 0.2 line for Dclk offset
            pData[15] = (((DWORD)g_stMDomainOutputData.usHTotal * 20 / 100) * ulDiffOffsetNew / ulDtotal);

#if((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
            if(_LAST_LINE_TARGET <= (g_stMDomainOutputData.usHTotal / 2))
            {
                ulDiffOffsetNew += pData[15];
            }
            else
            {
                ulDiffOffsetNew -= pData[15];
            }
#else

#if(_MN_DPLL_PATH_TYPE == _MN_DPLL_PATH2)

            if(_LAST_LINE_TARGET <= (g_stMDomainOutputData.usHTotal / 2))
            {
                ulDiffOffsetNew -= pData[15];
            }
            else
            {
                ulDiffOffsetNew += pData[15];
            }

#else

#if(_MN_DPLL_FREQ_UP == _ON)
            if(ScalerGetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, _BIT4) == 0x00)
            {
                if(_LAST_LINE_TARGET <= (g_stMDomainOutputData.usHTotal / 2))
                {
                    ulDiffOffsetNew -= pData[15];
                }
                else
                {
                    ulDiffOffsetNew += pData[15];
                }
            }
            else
#endif
            {
                if(_LAST_LINE_TARGET <= (g_stMDomainOutputData.usHTotal / 2))
                {
                    ulDiffOffsetNew += pData[15];
                }
                else
                {
                    ulDiffOffsetNew -= pData[15];
                }
            }

#endif

#endif
        }
    }

    SET_D_CLK_FREQ(ScalerPLLGetNewCount(ulDiffOffsetNew, ulDiffOffsetOld, GET_D_CLK_FREQ(), bProportion));

#if((_PANEL_STYLE == _PANEL_VBO) && (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F))
    ScalerPLLSetDPLLRefPLL(GET_D_CLK_FREQ());
#elif((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
    // Apply N.F for last-line
    ScalerPLLSetDPLLNFcode(ulDiffOffsetNew - 0x200000);
#else

#if(_MN_DPLL_PATH_TYPE == _MN_DPLL_PATH2)

    // Apply Offset for last-line
    ScalerPLLSetDPLLOffset(ulDiffOffsetNew - 32768);
    DebugMessageScaler("New offset", ulDiffOffsetNew - 32768);

#else

#if(_MN_DPLL_FREQ_UP == _ON)
    if(ScalerGetBit(P1_C4_DCLK_FINE_TUNE_OFFSET_MSB, _BIT4) == 0x00)
    {
        // Apply Offset for last-line
        ScalerPLLSetDPLLOffset(ulDiffOffsetNew - 32768);
        DebugMessageScaler("New offset", ulDiffOffsetNew - 32768);
    }
    else
#endif
    {
        // Apply Offset for last-line
        ScalerPLLSetDPLLOffset(32768 - ulDiffOffsetNew);
        DebugMessageScaler("New offset", 32768 - ulDiffOffsetNew);
    }

#endif

#endif
}
#endif // End of #if(_FRC_SUPPORT == _ON)

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
#if(_MPLL_STRUCT_TYPE != _MPLL_STRUCT_COMBO_M2PLL)
//--------------------------------------------------
// Description  : Adjust Mclk offset
// Input Value  : Dclk offset
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetMPLLOffset(WORD usMclkOffset)
{
    ScalerSetBit(P0_FA_MCLK_FINE_TUNE_OFFSET_MSB, ~0x0F, HIBYTE(usMclkOffset) & 0x0f);
    ScalerSetByte(P0_FB_MCLK_FINE_TUNE_OFFSET_LSB, LOBYTE(usMclkOffset));
    ScalerSetBit(P0_FC_MCLK_SPREAD_SPECTRUM, ~(_BIT2 | _BIT0), _BIT2 | _BIT0);
}

//--------------------------------------------------
// Description  : Set display clock (Dclk)/memory clock(Mclk) frequency in kHz
// Input Value  : ulFreq    --> Target Dclk/Mclk frequency
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetMPLLFreq(DWORD ulFreq)
{
    WORD usMcode = 0;

    // Power down MPLL
    ScalerSetBit(P0_F8_MPLL_WD, ~_BIT0, _BIT0);

    // Enable DDS Spread Spectrum Output
    ScalerSetBit(P0_FC_MCLK_SPREAD_SPECTRUM, ~_BIT0, _BIT0);

#if(_MN_MPLL_PATH_TYPE == _MN_MPLL_PATH2)

    // Set MPLL Phase Swallow Path2
    ScalerSetBit(P0_F9_MPLL_CAL, ~_BIT0, 0x00);

    // Set MPLL Freq down
    ScalerSetBit(P0_F8_MPLL_WD, ~_BIT4, _BIT4);

    // There is fixed div2 by hardware in output path without control register expressed by _MPLL_FIXED_DIV
    // and for mathematical operation so initial output div we set div8 here.
    usMcode = ulFreq * 8 * 2 * _MPLL_FIXED_DIV * 17 / ((DWORD)_EXT_XTAL * 16);

#else

    // Set MPLL Phase Swallow Path1
    ScalerSetBit(P0_F9_MPLL_CAL, ~_BIT0, _BIT0);

#if(_MN_MPLL_FREQ_UP == _ON)
    // Set MPLL Freq up
    ScalerSetBit(P0_F8_MPLL_WD, ~_BIT4, 0x00);

#if(_HW_PLL_EDGE_SELECT_TYPE == _PLL_EDGE_GEN_1_DEFAULT_POSITIVE)
    // Set MPLL Negative
    ScalerSetBit(P0_FE_MPLL_RESER, ~_BIT1, _BIT1);
#endif

#if(_HW_PLL_AUTO_EDGE_SELECT_SUPPORT == _ON)
    // Disable MPLL Auto Edge
    ScalerSetBit(P0_FE_MPLL_RESER, ~_BIT2, _BIT2);
#endif

    // There is fixed div2 by hardware in output path without control register expressed by _MPLL_FIXED_DIV
    // and for mathematical operation so initial output div we set div8 here.
    usMcode = ulFreq * 8 * 2 * _MPLL_FIXED_DIV * 16 / ((DWORD)_EXT_XTAL * 17);
#else
    // Set MPLL Freq down
    ScalerSetBit(P0_F8_MPLL_WD, ~_BIT4, _BIT4);

    // There is fixed div2 by hardware in output path without control register expressed by _MPLL_FIXED_DIV
    // and for mathematical operation so initial output div we set div8 here.
    usMcode = ulFreq * 8 * 2 * _MPLL_FIXED_DIV * 16 / ((DWORD)_EXT_XTAL * 15);
#endif

#endif

    // MPLL_VCO_clk_now
    PDATA_DWORD(0) = ulFreq * _MPLL_FIXED_DIV;

    // pData[15]: [5:4]=DPLL_O[1:0],[1:0]=DPLL VCO band
    if(PDATA_DWORD(0) < _MPLL_BOUNDRY_0) // DPLL_VCO = 2^3 * f_target
    {
        pData[15] = ((3 << 4) | (1));
    }
    else if(PDATA_DWORD(0) < _MPLL_BOUNDRY_1) // DPLL_VCO = 2^3 * f_target
    {
        pData[15] = ((3 << 4) | (2));
    }
    else if(PDATA_DWORD(0) < _MPLL_BOUNDRY_2) // DPLL_VCO = 2^2 * f_target
    {
        pData[15] = ((2 << 4) | (1));
    }
    else if(PDATA_DWORD(0) < _MPLL_BOUNDRY_3) // DPLL_VCO = 2^2 * f_target
    {
        pData[15] = ((2 << 4) | (2));
    }
    else if(PDATA_DWORD(0) < _MPLL_BOUNDRY_4) // DPLL_VCO = 2^1 * f_target
    {
        pData[15] = ((1 << 4) | (1));
    }
    else if(PDATA_DWORD(0) < _MPLL_BOUNDRY_5) // DPLL_VCO = 2^1 * f_target
    {
        pData[15] = ((1 << 4) | (2));
    }
    else if(PDATA_DWORD(0) < _MPLL_BOUNDRY_6) // DPLL_VCO = 2^0 * f_target
    {
        pData[15] = ((0 << 4) | (1));
    }
    else // DPLL_VCO = 1 * f_target
    {
        pData[15] = ((0 << 4) | (2));
    }

    switch(((pData[15] & 0x30) >> 4))
    {
        case 0:

            pData[0] = 8;
            break;

        case 1:

            pData[0] = 4;
            break;

        case 2:

            pData[0] = 2;
            break;

        case 3:

            pData[0] = 1;
            break;

        default:

            break;
    }

    usMcode = (usMcode + (pData[0] / 2)) / pData[0];

    // Manual set MPLL VCO band
    ScalerSetBit(P0_F9_MPLL_CAL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((pData[15] & 0x03) << 6) | _BIT5);

    // Set M Code
    ScalerSetByte(P0_F5_MPLL_M, (usMcode - 2));

    // Set N Code & Output divider
    ScalerSetByte(P0_F6_MPLL_N, (pData[15] & 0x30));

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Old Formula : Icp * N_Code / M_Code = 0.5 * Fxtal / 27MHz (for xtal not 27MHz)               //
    // Icp set 2.5uA, 5uA, 7.5uA, 10uA......                                                        //
    // Precise formula of Chrage Pump Current depends on DPM, resistor, and band.                   //
    // If VCO band = 'b00, Icp = (700 * M * 2 * pi) / (778 * 0x01C1[7:5]).                          //
    // If VCO band = 'b01, Icp = (700 * M * 2 * pi) / (1340 * 0x01C1[7:5]).                         //
    // If VCO band = 'b10, Icp = (700 * M * 2 * pi) / (1880 * 0x01C1[7:5]).                         //
    // If VCO band = 'b11, Icp = (700 * M * 2 * pi) / (2340 * 0x01C1[7:5]).                         //
    // 700: DPLL max frequency design target is 700MHz; 778: Frequency curve in band00 is 778MHz.   //
    // Assume MPLL_M=0x13, DPM=0x13+2=21; DPN=2; reg_dpll_vcomd='b01; reg_dpll_rs[2:0]='b011;       //
    // Icp = (700 * 21 * 2 * 3.14) / (1340 * 13)                                                    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    switch((pData[15] & 0x03))
    {
        case 0:

            PDATA_DWORD(0) = 778;
            break;

        case 1:

            PDATA_DWORD(0) = 1340;
            break;

        case 2:

            PDATA_DWORD(0) = 1880;
            break;

        case 3:

            PDATA_DWORD(0) = 2340;
            break;

        default:

            break;
    }
    PDATA_DWORD(0) = (DWORD)usMcode * 700UL * 628UL * 20 / PDATA_DWORD(0) / ((7 + (ScalerGetBit(P0_F7_MPLL_CRNT, (_BIT7 | _BIT6 | _BIT5)) >> 5) * 2) * 100);

    pData[1] = (PDATA_DWORD(0) + 25) / 50;
    pData[1] -= (pData[1] == 0) ? 0 : 1;

    // Set Current Control
    ScalerSetByte(P0_F7_MPLL_CRNT, (0x78 | (pData[1] & 0x07)));

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(P0_F8_MPLL_WD, ~_BIT1, (_DPLL_VCORSTB_NORMAL_VALUE << 1));

    // Power up MPLL
    ScalerSetBit(P0_F8_MPLL_WD, ~(_BIT6 | _BIT5 | _BIT3 | _BIT0), _BIT3);
    DELAY_XUS(150);

    // Reset PFD, LPF
    ScalerSetBit(P0_F8_MPLL_WD, ~_BIT5, _BIT5);
    DELAY_5US();
    ScalerSetBit(P0_F8_MPLL_WD, ~_BIT5, 0x00);

    // Calculate MPLL Output Freq. According to current Settings
    PDATA_DWORD(0) = (DWORD)_EXT_XTAL * 1000 / (1 << ((pData[15] & 0x30) >> 4)) / _MPLL_FIXED_DIV * usMcode / 2;

#if(_MN_MPLL_PATH_TYPE == _MN_MPLL_PATH2)

    // fvco = Xtal * M/N * 2^15 / (2^15 + offset), Freq Down.
    // (Dclk * 2^15)/ulFreq in Hz
    PDATA_DWORD(1) = GET_DWORD_MUL_DIV((PDATA_DWORD(0)), (1UL << 15), (ulFreq * 1000));

    // Target frequency of Dclk in Hz
    usMcode = PDATA_DWORD(1) - (1 << 15);

#else

    // Offset resolution (Dclk / 2^15) in Hz
    PDATA_DWORD(1) = (PDATA_DWORD(0) >> 15);

#if(_MN_MPLL_FREQ_UP == _ON)
    // Target frequency of Dclk in Hz
    usMcode = ((ulFreq * 1000) - PDATA_DWORD(0)) / PDATA_DWORD(1);
#else
    // Target frequency of Dclk in Hz
    usMcode = (PDATA_DWORD(0) - (ulFreq * 1000)) / PDATA_DWORD(1);
#endif

#endif

    usMcode = usMcode & 0x0FFF;

    // Set Mpll Offset
    ScalerPLLSetMPLLOffset(usMcode);

    // Wait for Mpll stable (Must!)
    ScalerTimerDelayXms(2);
}
#endif // #if(_MPLL_STRUCT_TYPE != _MPLL_STRUCT_COMBO_M2PLL)
#endif // #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : ADC Clock adjust.
// Input Value  : usCurrHTotal    --> IHTotal.
// Output Value : Return _TRUE if adjust successful.
//--------------------------------------------------
bit ScalerAPLLAdjust(WORD usCurrHTotal, WORD usCurrHFreq)
{
    BYTE ucLoopCnt = 0;
    BYTE pucData[5] = {0};
    BYTE ucMcode = 0;
    BYTE ucNcode = 0;
    SBYTE chKcode = 0;
    WORD usIcode = 0;
    WORD usPcode = 0;
    WORD usApllRefClock = 0;
    DWORD ulOldPllDivider = 0;
    DWORD ulMKCodeBackUp = 0;

    DebugMessageAnalog("APLL Clock", usCurrHTotal);

    // Disable new mode
    ScalerSetByte(P1_BB_DDS_MIX_4, 0x1b);

    // Disable Fast PLL Mechanism
    ScalerSetByte(P1_AA_FAST_PLL_CTRL, 0x00);

    // Power down APLL
    ScalerSetBit(P1_AF_PLL_WD, ~_BIT0, _BIT0);

    // APLL Inital Setting
    ScalerSetByte(P1_A0_PLL_DIV_CTRL, 0x08);

    // Set DDS Mix
    ScalerSetByte(P1_B9_DDS_MIX_2, 0xFF);
    ScalerSetByte(P1_BA_DDS_MIX_3, 0xFF);

    // Set APLL lock threshold by H-Sync Freq
    ScalerAPLLLockThdSet(usCurrHFreq);

    // Set the divide number
    ScalerSetBit(P1_B1_PLLDIV_H, ~0x0F, (BYTE)(((usCurrHTotal - 1) >> 8) & 0x0f));
    ScalerSetByte(P1_B2_PLLDIV_L, (BYTE)((usCurrHTotal - 1) & 0x00ff));

    // Get Apll Ref clock
    usApllRefClock = ScalerPLLGetApllReferClkFreqKhz();

    // Get ADC Sampling clock freq.
    ulOldPllDivider = (DWORD)usCurrHFreq * usCurrHTotal / 10; // ADC sampling clock, UNIT in KHz

    // Record Current Pixel Clock
    SET_INPUT_PIXEL_CLK(ulOldPllDivider / 100); // Unit: 0.1M Hz

    pucData[0] = (ulOldPllDivider < _APLL_VCO_DEVIDER_4_2_THERSHOLD) ? 4 : 2; // Vco_divider

    if(_APLL_REF_CLK == _EXT_XTAL)
    {
        // Decide N Code value by Vco clock Freq
        if(ulOldPllDivider * pucData[0] >= 120000)
        {
            ucNcode = 1;
        }
        else
        {
            ucNcode = 2;
        }

        // VCO divider select
        ScalerSetBit(P1_B1_PLLDIV_H, ~(_BIT6 | _BIT5 | _BIT4), (pucData[0] == 2) ? (_BIT6 | _BIT5) : (_BIT6 | _BIT5 | _BIT4));

        // Calculate (M + K/16) = IHF * usCurrHTotal * N1 * vco_divider / Fxtal
        ulOldPllDivider = ((ulOldPllDivider * ucNcode * pucData[0]) << 10) / usApllRefClock;

        // Get M, K code, M + K/16 = pllclock / 1024
        ucMcode = ulOldPllDivider >> 10; // M code is the integer part.

        // K is the fraction part quantized by 16
        chKcode = ((DWORD)ulOldPllDivider - ((DWORD)ucMcode << 10)) >> 6;

        // Set K code within -8 to 7 due to 3 bits.
        if(chKcode > 7)
        {
            ucMcode += 1;
            chKcode -= 16;
        }
        else if(chKcode < -8)
        {
            ucMcode -= 1;
            chKcode += 16;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////
        // Precise formula of Chrage Pump Current depends on VCO Freq  or M Code                        //
        // M Code can't be less than 5                                                                  //
        // Fvco >= 360M, N =1                                                                           //
        // Loop filter resister = 3b'000 (R1 = 4K), 4.4K Consider 0.4K parasitic resistance             //
        //                                                                                              //
        //         1MHz * 2 * pi * M                                                                    //
        //  Icp = ---------------------- = (3140 * ucMcode) / 1100   (icp unit uA)                      //
        //         500MHz/V * 4.4K                                                                      //
        //                                                                                              //
        // Fvco >= 120M, N =1                                                                           //
        // Loop filter resister = 3b'001 (R1 = 8K), 8.4K Consider 0.4K parasitic resistance             //
        //                                                                                              //
        //         1MHz * 2 * pi * M                                                                    //
        //  Icp = ---------------------- = (3140 * ucMcode) / 2100   (icp unit uA)                      //
        //         500MHz/V * 8.4K                                                                      //
        //                                                                                              //
        // Fvco < 120M, N = 2                                                                           //
        // Loop filter resister = 3b'101 (R1 = 16K),16.4K Consider 0.4K parasitic resistance            //
        //                                                                                              //
        //         0.5MHz * 2 * pi * M                                                                  //
        //  Icp = ---------------------- = (3140 * ucMcode) / 8200    (icp unit uA)                     //
        //         500MHz/V * 16.4K                                                                     //
        // Let pi = 3.14                                                                                //
        //////////////////////////////////////////////////////////////////////////////////////////////////
        if(((DWORD)GET_INPUT_PIXEL_CLK() * pucData[0]) >= 3600)
        {
            PDATA_WORD(0) = (WORD)((DWORD)3140 * ucMcode * 10 / 1100); // x 10 in order to 0.1, Unit 0.1uA

            // Resiter = 3b'000 --> 4K
            pData[14] = 0x00;
        }
        else if(((DWORD)GET_INPUT_PIXEL_CLK() * pucData[0]) >= 1200)
        {
            PDATA_WORD(0) = (WORD)((DWORD)3140 * ucMcode * 10 / 2100); // x 10 in order to 0.1, Unit 0.1uA

            // Resiter = 3b'010 --> 8K
            pData[14] = _BIT6;
        }
        else
        {
            PDATA_WORD(0) = (WORD)((DWORD)3140 * ucMcode * 10 / 8200); // x 10 in order to 0.1, Unit 0.1uA

            // Resiter = 3b'110 --> 16K
            pData[14] = (_BIT7 | _BIT6);
        }
    }
    else // Else (_APLL_REF_CLK == _LC_TANK_XTAL_FREQUENCY)
    {
        // VCO divider select
        ScalerSetBit(P1_B1_PLLDIV_H, ~(_BIT6 | _BIT5 | _BIT4), (pucData[0] == 2) ? (_BIT6 | _BIT5) : (_BIT6 | _BIT5 | _BIT4));

        ulMKCodeBackUp = ulOldPllDivider;
        ucLoopCnt = 0;
        do
        {
            // Avoid M Code Too Small, N = 2 ^ ucLoopCnt, N value range = 1, 2, 4
            ucNcode = _BIT0 << ucLoopCnt;

            // Calculate (M + K/16) = IHF * usCurrHTotal * N1 * vco_divider / Fxtal
            ulOldPllDivider = ((ulMKCodeBackUp * ucNcode * pucData[0]) << 10) / usApllRefClock;

            if(ulOldPllDivider > ((WORD)_APLL_VCO_M_CODE_MIN << 10))
            {
                break;
            }
        }while(ucLoopCnt++ < 2);

        DebugMessageAnalog("ucNcode", ucNcode);

        // Get M, K code, M + K/16 = pllclock / 1024
        ucMcode = ulOldPllDivider >> 10; // M code is the integer part.

        DebugMessageAnalog("ucMcode", ucMcode);

        // K is the fraction part quantized by 16
        chKcode = ((DWORD)ulOldPllDivider - ((DWORD)ucMcode << 10)) >> 6;

        // Set K code within -8 to 7 due to 3 bits.
        if(chKcode > 7)
        {
            ucMcode += 1;
            chKcode -= 16;
        }
        else if(chKcode < -8)
        {
            ucMcode -= 1;
            chKcode += 16;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////
        // Precise formula of Chrage Pump Current depends on VCO Freq  or M Code                        //
        // Original Formula: BW = 2 * pi * ((Fref / 10) / N) / _APLL_BW_FACTOR(=1.2)=Kvco*Icp*R/(2*pi*M)//
        // Kvco = 2 * pi * 450e6 * _APLL_KVCO_FACTOR(=1.2)                                              //
        //        BW * 2 * pi * M              2*pi*Fref*2*pi*M          pi*Fref*M                      //
        // Icp = ---------------------- = --------------------------- = -------------                   //
        //          Kvco * R1              10*N*1.2*2*pi*450e6*1.2*R1    3240e6*N*R1                    //
        // M Code can't be less than 5, AICD Suggest threshold define 7                                 //
        // N = 1                                                                                        //
        // Loop filter resister = 3b'001 (R1 = 6K), 6.4K Consider 0.4K parasitic resistance             //
        //                                                                                              //
        //         pi * 27M * M                                                                         //
        //  Icp = ---------------------- = (84780 * ucMcode) / 20736   (icp unit uA)                    //
        //         3240 * 6.4K                                                                          //
        //                                                                                              //
        // N = 2                                                                                        //
        // Loop filter resister = 3b'010 (R1 = 8K), 8.4K Consider 0.4K parasitic resistance             //
        //                                                                                              //
        //         pi * 27M * M                                                                         //
        //  Icp = ---------------------- = (84780 * ucMcode) / 54432   (icp unit uA)                    //
        //         3240 * 2 * 8.4K                                                                      //
        //                                                                                              //
        // N = 4                                                                                        //
        // Loop filter resister = 3b'110 (R1 = 16K), 16.4K Consider 0.4K parasitic resistance           //
        //                                                                                              //
        //         pi * 27M * M                                                                         //
        //  Icp = ---------------------- = (84780 * ucMcode) / 212544   (icp unit uA)                   //
        //         3240 * 4 * 16.4K                                                                     //
        //                                                                                              //
        // Let pi = 3.14                                                                                //
        //////////////////////////////////////////////////////////////////////////////////////////////////
        if(ucNcode == 1)
        {
            PDATA_WORD(0) = (WORD)((DWORD)84780 * ucMcode * 10 / 20736); // x 10 in order to 0.1, Unit 0.1uA

            // Resiter = 3b'001 --> 6K
            pData[14] = _BIT5;
        }
        else if(ucNcode == 2)
        {
            PDATA_WORD(0) = (WORD)((DWORD)84780 * ucMcode * 10 / 54432); // x 10 in order to 0.1, Unit 0.1uA

            // Resiter = 3b'010 --> 8K
            pData[14] = _BIT6;
        }
        else // ucNcode == 4 or default value
        {
            PDATA_WORD(0) = (WORD)((DWORD)84780 * ucMcode * 10 / 212544); // x 10 in order to 0.1, Unit 0.1uA

            // Resiter = 3b'110 --> 16K
            pData[14] = (_BIT7 | _BIT6);
        }
    }

    // Get icp step, truncate lsb bit
    pData[15] = (PDATA_WORD(0)) / 25;
    pData[15] -= (pData[15] == 0) ? 0 : 1;

    // Icp only 5bit (bit4 = doubled), Min current = 2.5uA, Max current = 80mA
    pData[15] = (pData[15] > 0x0F) ? ((pData[15] / 2) | _BIT4) : pData[15];
    pData[15] = (pData[15] > 0x1F) ? 0x1F : pData[15];

    // Reg = Resistor & Icp, Resistor: MSB 3bit, Icp: LSB 5bit (When bit4 = 1, current * 2)
    ScalerSetByte(P1_AE_PLL_CRNT, (pData[14] | pData[15]));

    // Set N code
    if(ucNcode == 1)
    {
        ScalerSetBit(P1_AD_PLL_N, ~_BIT3, _BIT3);
    }
    else
    {
        ScalerSetBit(P1_AD_PLL_N, ~0x0F, (((ucNcode - 2) & 0x07)));
    }

    // Set M code
    ScalerSetByte(P1_AC_PLL_M, (ucMcode - 3));

    // Set K code
    ScalerSetBit(P1_AD_PLL_N, ~0xF0, ((chKcode & 0x0f) << 4));

    // Enable PFD Calibration
    ScalerSetBit(P1_A4_PFD_CALIBRATED_RESULTS_H, ~_BIT7, 0x00);
    ScalerSetBit(P1_A4_PFD_CALIBRATED_RESULTS_H, ~_BIT7, _BIT7);

    // Get PFD Calibration result
    if(ScalerTimerPollingFlagProc(100, P1_A4_PFD_CALIBRATED_RESULTS_H, _BIT7, 0) == _TRUE)
    {
        ScalerRead(P1_A4_PFD_CALIBRATED_RESULTS_H, 2, pucData, _AUTOINC);
        g_stApllData.usPEValue = ((WORD)(pucData[0] & 0x0F) << 8) | pucData[1];

        g_stApllData.usPEValue = (WORD)((DWORD)1000000 / ((DWORD)g_stApllData.usPEValue * _SYS_CLK_KHZ / 1000)); // Unit : ps

        DebugMessageAnalog("5. usPEValue", g_stApllData.usPEValue);
    }
    else
    {
        ScalerSetBit(P1_A4_PFD_CALIBRATED_RESULTS_H, ~_BIT7, 0x00);

        return _FALSE;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // Formula :                                                                 //
    //                                                                           //
    //  I_gain       Ths                    PE(UNIT)                   1         //
    // --------- x  ------- = ------------------------------------ x  -----      //
    //   2^22        Tbck        Txclk x 16N / (16M +- K) x 1/16       8         //
    //                                                                           //
    //  I_gain         Ths                      PE(UNIT)                   1     //
    // --------- x  ----------- = ------------------------------------ x  -----  //
    //   2^22       Tclk x N         Txclk x N / (M +- K/16) x 1/16        8     //
    //                                                                           //
    //                                                                           //
    //           2^22 x PE_U x (M +- K/16) x 2^4        1                        //
    // I_gain = ----------------------------------- x ------                     //
    //                        Ths                      2^3                       //
    //                                                                           //
    //           2^23 x PE_U x (M +- K/16)                                       //
    //       = -----------------------------                                     //
    //                      Ths                                                  //
    //                                                                           //
    //                                                                           //
    //       = IHF x 2^23 x PE_U x (M +- K/16)                                   //
    //                                                                           //
    //                                                                           //
    // I_gain = IHF x 2^23 x PE_U x (M +- K/16)                                  //
    // IHFreq/10 UNIT is KHz, so result has to multiply 10^2          //
    // (PE Value UNIT is ps, so result has to multiply 10^-12)                   //
    //                                                                           //
    // I_gain = 10^2 x 2^23 x 10^-12 x 2^-10 => 10^10 / 2^13 = 1220703           //
    //                                                                           //
    ///////////////////////////////////////////////////////////////////////////////

    // Calculate I code
    usIcode = (WORD)(((DWORD)usCurrHFreq * g_stApllData.usPEValue * (ulOldPllDivider >> 10)) / 1192);

    // Total gain = 3 / 8
    usIcode = (usIcode / 64) & 0x00007fff; // n = 64 x 8 = 512

    // The minimum value of I code is 1.
    if(usIcode < 1)
    {
        usIcode = 1;
    }

    // Set I code
    ScalerSetByte(P1_A1_I_CODE_M, (BYTE)(usIcode >> 8));
    ScalerSetByte(P1_A2_I_CODE_L, (BYTE)usIcode);

    // Calculate P code
    usPcode = (WORD)(((DWORD)191 * usIcode * usApllRefClock / ((ucNcode * usCurrHFreq + 5) / 10)) >> 7); // Total Gain = 192/512

    // Get G value (ucData[0])
    pucData[0] = ScalerAPLLGetAPLLGValue(&usPcode);

    // Set G value
    ScalerSetByte(P1_B6_P_CODE_MAPPING_METHOD, (pucData[0] << 2));

    // Set P code
    ScalerSetByte(P1_A3_P_CODE, (BYTE)usPcode);

    // Intial Phase
    ScalerSetByte(P1_B4_PLLPHASE_CTRL1, 0x00);

    // Apply phase write port for phase DB
    ScalerSetByte(P1_B3_PLLPHASE_CTRL0, ScalerGetByte(P1_B3_PLLPHASE_CTRL0));

    // Release top misc power down control
    ScalerSetBit(P1_F2_APLL_MISC, ~_BIT7, 0x00);

    // Power up APLL
    ScalerSetBit(P1_AF_PLL_WD, ~_BIT0, 0x00);

    // Check PLL lock already
    if(ScalerTimerPollingFlagProc(150, P1_B8_DDS_MIX_1, _BIT0, _TRUE) == _FALSE)
    {
        DebugMessageAnalog("5. APLL Unlock", 0);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : APLL Lock Threshold Setting
// Input Value  : usHFreq --> H-Sync Freq
// Output Value : None
//--------------------------------------------------
void ScalerAPLLLockThdSet(WORD usHFreq)
{
    if(usHFreq <= 250) // 25K
    {
        ScalerSetBit(P1_B8_DDS_MIX_1, ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));   // PE thd= 46
    }
    else if(usHFreq <= 500) // 50K
    {
        ScalerSetBit(P1_B8_DDS_MIX_1, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);   // PE thd= 23
    }
    else if(usHFreq <= 750) // 75K
    {
        ScalerSetBit(P1_B8_DDS_MIX_1, ~(_BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));   // PE thd= 11
    }
    else // Uper 75K
    {
        ScalerSetBit(P1_B8_DDS_MIX_1, ~(_BIT3 | _BIT2 | _BIT1), _BIT2);   // PE thd= 9
    }
}

//--------------------------------------------------
// Description  : Get APLL G value
// Input Value  : The P code of APLL
// Output Value : G value
//--------------------------------------------------
BYTE ScalerAPLLGetAPLLGValue(WORD *pusDelta)
{
    if(*pusDelta == 0)
    {
        *pusDelta = 0x01;
    }

    if(*pusDelta > 255)
    {
        for(pData[0] = 9; pData[0] < 15; pData[0]++)
        {
            if((*pusDelta >> pData[0]) == 0)
            {
                break;
            }
        }

        switch(pData[0] - 9)
        {
            case 0:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_0 / 2)) / _G_VALUE_DIVIDER_0;
                break;

            case 1:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_1 / 2)) / _G_VALUE_DIVIDER_1;
                break;

            case 2:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_2 / 2)) / _G_VALUE_DIVIDER_2;
                break;

            case 3:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_3 / 2)) / _G_VALUE_DIVIDER_3;
                break;

            case 4:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_4 / 2)) / _G_VALUE_DIVIDER_4;
                break;

            case 5:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_5 / 2)) / _G_VALUE_DIVIDER_5;
                break;

            default:
                break;
        }

        return (pData[0] - 7);
    }

    return 1;
}

//--------------------------------------------------
// Description  : ADC Clock Fast Lock adjust.
// Input Value  : usCurrHTotal    --> IHTotal.
// Output Value : Return _TRUE if adjust successful.
//--------------------------------------------------
bit ScalerAPLLFastLockAdjust(WORD usCurrHTotal)
{
    BYTE ucMcode = 0;
    BYTE ucNcode = 0;
    SBYTE chKcode = 0;
    WORD usIcode = 0;
    WORD usPcode = 0;
    DWORD ulClockRatio = 0;

    // Get New PLL Divider
    if(ScalerAPLLGetSumI(&g_stApllData.ulDivider) == _FALSE)
    {
        DebugMessageAnalog("5. Measure Sum I Fail", 0);

        // Set usCurrHTotal, M ocde, K code
        ScalerSetBit(P1_B1_PLLDIV_H, ~0x0F, (BYTE)(((usCurrHTotal - 1) >> 8) & 0x000f));
        ScalerSetByte(P1_B2_PLLDIV_L, (BYTE)((usCurrHTotal - 1) & 0x00ff));

        // Set the fast PLL setting by double buffer method
        ScalerSetBit(P1_AA_FAST_PLL_CTRL, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

        if(ScalerTimerPollingFlagProc(100, P1_AA_FAST_PLL_CTRL, _BIT6, 0) == _FALSE)
        {
            return _FALSE;
        }
        else
        {
            return _TRUE;
        }
    }

    // Enable Fast PLL Mechanism
    ScalerSetByte(P1_AA_FAST_PLL_CTRL, 0x20);

    // Calculate Clock Ratio = usCurrHTotal / Old IH-Total
    ulClockRatio = (((DWORD)0x01 << 30) / ScalerAPLLGetIHTotal()) * usCurrHTotal;

    // Calculate New PLL Divider = Old PLL Divider x (New Clock / Old IH-Total) = Old PLL Divider x Clock Ratio
    PDATA_DWORD(0) = ((g_stApllData.ulDivider & 0xffff0000) >> 16) * ((ulClockRatio & 0xffff0000) >> 16);
    PDATA_DWORD(1) = ((g_stApllData.ulDivider & 0xffff0000) >> 16) * ((ulClockRatio & 0x0000ffff) >> 0);
    PDATA_DWORD(1) += ((g_stApllData.ulDivider & 0x0000ffff) >> 0) * ((ulClockRatio & 0xffff0000) >> 16);
    PDATA_DWORD(2) = ((g_stApllData.ulDivider & 0x0000ffff) >> 0) * ((ulClockRatio & 0x0000ffff) >> 0);
    PDATA_DWORD(3) = (PDATA_DWORD(0) << (16 - 14)) + (PDATA_DWORD(1) >> 14) + (PDATA_DWORD(2) >> (16 + 14));

    // Get M code, K code
    ucMcode = pData[12];
    chKcode = ((pData[13] & 0xf0) >> 4) & 0x0f;

    if(chKcode > 7)
    {
        ucMcode += 1;
        chKcode -= 16;
    }

    // Set usCurrHTotal, M ocde, K code
    ScalerSetBit(P1_B1_PLLDIV_H, ~0x0F, (BYTE)(((usCurrHTotal - 1) >> 8) & 0x000f));
    ScalerSetByte(P1_B2_PLLDIV_L, (BYTE)((usCurrHTotal - 1) & 0x00ff));
    ScalerSetByte(P1_AC_PLL_M, (ucMcode - 3));
    ScalerSetBit(P1_AD_PLL_N, ~0xF0, ((chKcode & 0x0f) << 4));

    // Calculate Sum_I (22 bits)
    PDATA_DWORD(0) = (PDATA_DWORD(3) & 0x000FFFFF) << 2;

    // Set Sum_I (22 bits)
    ScalerSetBit(P1_F7_FAST_PLL_SUM_I_26_24, ~(_BIT2 | _BIT1 | _BIT0), (pData[0] & 0x07));
    ScalerWrite(P1_F8_FAST_PLL_SUM_I_23_16, 3, pData + 1, _AUTOINC);

    // Read PFD Calibrated result
    ScalerSetBit(P1_A4_PFD_CALIBRATED_RESULTS_H, ~_BIT7, _BIT7); // Enable PFD Calibration
    if(ScalerTimerPollingFlagProc(100, P1_A4_PFD_CALIBRATED_RESULTS_H, _BIT7, 0) == _TRUE)
    {
        ScalerRead(P1_A4_PFD_CALIBRATED_RESULTS_H, 2, pData, _AUTOINC);
        g_stApllData.usPEValue = ((WORD)(pData[0] & 0x0F) << 8) | pData[1];
        g_stApllData.usPEValue = (WORD)((DWORD)1000000 / ((DWORD)g_stApllData.usPEValue * _SYS_CLK_KHZ / 1000)); // Unit : ps
    }
    else
    {
        ScalerSetBit(P1_A4_PFD_CALIBRATED_RESULTS_H, ~_BIT7, 0x00);
        return _FALSE;
    }

    // Calculate I code
    usIcode = (WORD)(((((DWORD)GET_INPUT_TIMING_HFREQ() + 5) / 10) * g_stApllData.usPEValue * (PDATA_DWORD(3) / 100000)) / 20000);
    usIcode = (usIcode / 64) & 0x00007fff; // n = 64 x 8 = 512

    // The minimum value of I code is 1.
    if(usIcode < 1)
    {
        usIcode = 1;
    }

    // Set I code
    ScalerSetByte(P1_A1_I_CODE_M, (BYTE)(usIcode >> 8));
    ScalerSetByte(P1_A2_I_CODE_L, (BYTE)usIcode);

    // Get N Code
    ucNcode = ScalerGetByte(P1_AD_PLL_N);
    ucNcode = (ucNcode & _BIT3) ? 1 : ((ucNcode & 0x07) + 2);
    DebugMessageAnalog("Fast Pll N Code =", ucNcode);

    // Calculate P code
    usPcode = (WORD)(((DWORD)191 * usIcode * ScalerPLLGetApllReferClkFreqKhz() / ((ucNcode * GET_INPUT_TIMING_HFREQ() + 5) / 10)) >> 7); // Total Gain = 192/512

    // Get G value (ucData[15])
    pData[15] = ScalerAPLLGetAPLLGValue(&usPcode);

    // Set G value
    ScalerSetByte(P1_B6_P_CODE_MAPPING_METHOD, (pData[15] << 2));

    // Set P code
    ScalerSetByte(P1_A3_P_CODE, (BYTE)usPcode);

    // Set the P code Maximum
    ScalerSetByte(P1_B9_DDS_MIX_2, 0xFF);
    ScalerSetByte(P1_BA_DDS_MIX_3, 0xFF);

    // Coast Sent into APLL condition : Capture unlock && Coast Signal Enable
    if(((ScalerGetBit(P0_4E_HSYNC_TYPE_DETECTION_FLAG, _BIT0)) == _BIT0) && ((ScalerGetBit(P0_48_SYNC_INVERT, _BIT6)) == _BIT6))
    {
        // APLL Setting Apply at the End of Coast Window
        ScalerSetBit(P1_A0_PLL_DIV_CTRL, ~_BIT0, _BIT0);
    }
    else
    {
        // APLL Setting Apply at the End of DEN
        ScalerSetBit(P1_A0_PLL_DIV_CTRL, ~_BIT0, 0x00);
    }

    // Set the fast PLL setting by double buffer method
    ScalerSetBit(P1_AA_FAST_PLL_CTRL, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    if(ScalerTimerPollingFlagProc(100, P1_AA_FAST_PLL_CTRL, _BIT6, 0) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}


//--------------------------------------------------
// Description  : Get Sum I value
// Input Value  : pusDiv -- > Sum I change to divider par
// Output Value : Divider Pointor
//--------------------------------------------------
bit ScalerAPLLGetSumI(DWORD *pulDiv)
{
    BYTE pucData[5] = {0};
    BYTE ucMcode = 0;
    SBYTE chKcode = 0;
    SBYTE chKValue = 0;
    SDWORD lSumI = 0;
    SDWORD lTemp = 0;

    // Disable Sum_i Measure
    ScalerSetBit(P1_AA_FAST_PLL_CTRL, ~_BIT2, 0x00);

    // Get Sum_I (27 bits)
    for(pucData[4] = 0; pucData[4] < _APLL_SUM_I_READ_COUNT; pucData[4]++)
    {
        // Enable Sum_i Measure
        ScalerSetBit(P1_AA_FAST_PLL_CTRL, ~_BIT2, _BIT2);

        if(ScalerTimerPollingFlagProc(100, P1_AA_FAST_PLL_CTRL, _BIT2, 0) == _TRUE) // Check Measure Sum_I
        {
            // Disable Sum_i Measure
            ScalerSetBit(P1_AA_FAST_PLL_CTRL, ~_BIT2, 0x00);
            ScalerRead(P1_FB_FAST_PLL_SUM_I_MEASURE_26_24, 4, pucData, _AUTOINC);

            lTemp = ((((DWORD)pucData[0] & 0x07) << 24) | ((DWORD)pucData[1] << 16) | ((DWORD)pucData[2] << 8) | ((DWORD)pucData[3]));

            // To check the signed bit (Bit_26) of SUM_I
            if((pucData[0] & _BIT2) != 0x00)
            {
                lTemp |= 0xF8000000;
            }

            lSumI += lTemp;
            lTemp = 0;
        }
        else
        {
            ScalerSetByte(P1_AA_FAST_PLL_CTRL, 0x00);

            return _FALSE;
        }
    }

    lSumI = lSumI / _APLL_SUM_I_READ_COUNT;

    // Get K code
    chKcode = ScalerGetBit(P1_AD_PLL_N, 0xF0);

    if((chKcode & _BIT7) != 0x00) // Register chKcode is negative value
    {
        chKcode = 0xF8 | (chKcode >> 4);
    }
    else
    {
        chKcode = chKcode >> 4;
    }

    // Get K Value (4 bits for bit25 ~ bit22) and Set Sum I
    if(lSumI < 0)
    {
        lSumI = 0 - lSumI;
        chKValue = 0 - (BYTE)((lSumI >> 22) & 0x000000FF);
        lSumI = 0x400000 - (lSumI & 0x003fffff); // 0x400000 = 2^22
        chKcode -= 1;
    }
    else
    {
        chKValue = (BYTE)((lSumI >> 22) & 0x000000FF);
    }

    // Compensate K Value
    chKcode = chKcode + chKValue;

    // Get M code
    ucMcode = ScalerGetByte(P1_AC_PLL_M) + 3;

    // Set K code >= 0
    if(chKcode < 0)
    {
        ucMcode -= 1;
        chKcode += 16;
    }

    *pulDiv = ((DWORD)ucMcode << (26 - 2)) + (((DWORD)chKcode & 0x0000000f) << (22 - 2)) + (((DWORD)lSumI & 0x003fffff) >> 2);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Apll H-Total Divider.
// Input Value  : None
// Output Value : None.
//--------------------------------------------------
WORD ScalerAPLLGetIHTotal(void)
{
    return ((((WORD)(ScalerGetByte(P1_B1_PLLDIV_H)) & 0x000F) << 8) | ScalerGetByte(P1_B2_PLLDIV_L)) + 1;
}

//--------------------------------------------------
// Description  : Apply Phase setting.
// Input Value  : ucPhase    --> For Apply  Phase step.
// Output Value : None.
//--------------------------------------------------
void ScalerPLLSetPhase(BYTE ucPhase, WORD usVfreq)
{
    BYTE ucEdgePhase = 0;
    BYTE ucEdgePhaseTemp = 0;
    BYTE ucLeftBound = 0;
    BYTE ucRightBound = 0;
    DWORD ulDotClock = 0;
    ucPhase = ucPhase & 0x3f;

    ///////////////////////////////////////////////////////////////////////////////////////
    // Code below is to select stable HSYNC latch edge.                                  //
    // Calculating delay between input clock into ADC and output from ADC.               //
    // Original Formula :                                                                //
    // select = 64 * 6.95  * ulRate / 1000000;                                           //
    ///////////////////////////////////////////////////////////////////////////////////////

    // Get the current IHTotal of ADC
    ulDotClock = (DWORD)(ScalerAPLLGetIHTotal()) * ScalerSyncProcMeasureIHFreqByStableMeasure();
    PDATA_DWORD(0) = ((DWORD)ScalerAPLLGetIHTotal() * GET_INPUT_TIMING_VTOTAL() * usVfreq) / 1000;

    if(GET_THERMO_LONG_PATH_STATUS() == _TRUE)
    {
        DebugMessageAnalog("Current HS Delay", g_usPhaseDelayTimeLongPath);
        // Get phase delay count
        ucEdgePhase = (ulDotClock * g_usPhaseDelayTimeLongPath / 10000000) + _PHASE_DELAY_HALF_PERIOD_SHIFT;

        // Get phase delay count reference mode table
        ucEdgePhaseTemp = (PDATA_DWORD(0) * g_usPhaseDelayTimeLongPath / 10000000) + _PHASE_DELAY_HALF_PERIOD_SHIFT;

#if(_PHASE_DELAY_TIME_VALUE_LONG_PATH < 0)
        // Negate Hs delay meta-stable phase
        ucEdgePhase = (~ucEdgePhase & 0x3F);
        ucEdgePhaseTemp = (~ucEdgePhaseTemp & 0x3F);
#endif
    }
    else
    {
        DebugMessageAnalog("Current HS Delay", g_usPhaseDelayTimeShortPath);

        // Get phase delay count
        ucEdgePhase = (ulDotClock * g_usPhaseDelayTimeShortPath / 10000000) + _PHASE_DELAY_HALF_PERIOD_SHIFT;

        // Get phase delay count reference mode table
        ucEdgePhaseTemp = (PDATA_DWORD(0) * g_usPhaseDelayTimeShortPath / 10000000) + _PHASE_DELAY_HALF_PERIOD_SHIFT;

#if(_PHASE_DELAY_TIME_VALUE_SHORT_PATH < 0)
        // Negate Hs delay meta-stable phase
        ucEdgePhase = (~ucEdgePhase & 0x3F);
        ucEdgePhaseTemp = (~ucEdgePhaseTemp & 0x3F);
#endif
    }

    DebugMessageAnalog("Measure edge phase", ucEdgePhase);
    DebugMessageAnalog("Mode table edge phase", ucEdgePhaseTemp);

    // Eliminate measurement error if difference of edge phase is small
    if(ABSDWORD(ucEdgePhase, ucEdgePhaseTemp) <= _PHASE_DELAY_EDGEPHASE_THRESHOLD)
    {
        ucEdgePhase = ucEdgePhaseTemp;
    }

    ucLeftBound = ((ucEdgePhase + 64 - 12) % 64);
    ucRightBound = ((ucEdgePhase + 12) % 64);

    if(ucLeftBound < ucRightBound) // case1
    {
        if(ucPhase <= ucLeftBound)
        {
            g_stRegVgaCapture.b2_02_3_HSSYNCEDGE_HDLYONE = 0x00;
        }
        else if((ucPhase > ucLeftBound) && (ucPhase <= ucRightBound))
        {
            g_stRegVgaCapture.b2_02_3_HSSYNCEDGE_HDLYONE = (_BIT1 | _BIT0);
        }
        else if(ucPhase > ucRightBound)
        {
            g_stRegVgaCapture.b2_02_3_HSSYNCEDGE_HDLYONE = _BIT1;
        }
    }
    else // case 2
    {
        if(ucPhase < ucRightBound)
        {
            g_stRegVgaCapture.b2_02_3_HSSYNCEDGE_HDLYONE = _BIT0;
        }
        else if((ucPhase >= ucRightBound) && (ucPhase < ucLeftBound))
        {
            g_stRegVgaCapture.b2_02_3_HSSYNCEDGE_HDLYONE = 0;
        }
        else if(ucPhase >= ucLeftBound)
        {
            g_stRegVgaCapture.b2_02_3_HSSYNCEDGE_HDLYONE = (_BIT1 | _BIT0);
        }
    }

    // Phase Select Method for Look Up Table (default)
    ScalerSetBit(P1_B1_PLLDIV_H, ~_BIT6, (_ADCPLL_PHASE_METHOD_LOOKUPTABLE << 6) & _BIT6);

    // Set phase
    if(ScalerGetBit(P1_B1_PLLDIV_H, _BIT4) == _BIT4)
    {
        ScalerSetBit(P1_B4_PLLPHASE_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucPhase << 1) & (~_BIT7)));
    }
    else
    {
        ScalerSetBit(P1_B4_PLLPHASE_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ucPhase & (~_BIT7)));
    }

    // Apply the above setting by setting Double Buffer Ready in VGIP
    ScalerVgaTopDoubleBufferApply();

    // Apply phase write port
    ScalerSetByte(P1_B3_PLLPHASE_CTRL0, ScalerGetByte(P1_B3_PLLPHASE_CTRL0));
}

//--------------------------------------------------
// Description  : Get LC tank Freq from efuse.
// Input Value  : None.
// Output Value : Return LC tank freq Khz.
//--------------------------------------------------
WORD ScalerPLLGetApllReferClkFreqKhz(void)
{
    WORD usLCTankFreq = 0;

#if(_LC_TANK_SUPPORT == _ON)

#if(_XTALESS_SUPPORT == _ON)

#if(_EFUSE_SUPPORT == _ON)
    BYTE pucLCtankFreqKhz[2] = {0};

    // Read Out eFuse Data
    ScalerEfuseGetData(_EFUSE_LC_TANK_FREQ_FOR_APLL, 2, pucLCtankFreqKhz);

    usLCTankFreq = (WORD)(((DWORD)pucLCtankFreqKhz[0] * 1000) + ((WORD)pucLCtankFreqKhz[1] * 10));

    // Check LC Tank Efuse measure freq tolerance max ratio 20%
    if(ABSDWORD(usLCTankFreq, _LC_TANK_XTAL_FREQUENCY) > (_LC_TANK_XTAL_FREQUENCY * 2 / 10))
    {
        usLCTankFreq = _LC_TANK_XTAL_FREQUENCY;
    }

#else

    usLCTankFreq = _LC_TANK_XTAL_FREQUENCY;

#endif // End of #if(_EFUSE_SUPPORT == _ON)

#else

    usLCTankFreq = _EXT_XTAL;

#endif // End of #if(_XTALESS_SUPPORT == _ON)

#else

    usLCTankFreq = _EXT_XTAL;

#endif // End of #if(_LC_TANK_SUPPORT == _ON)

    return usLCTankFreq;
}

#endif // End of #if(_VGA_SUPPORT == _ON)


#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
//--------------------------------------------------
// Description  : DDR2PLL Function Control
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerPLLDDR2PLLCtrl(bit bEnable)
{
    BYTE ucDDRSel = 0;

    for(ucDDRSel = _DDR2_DEV_SEQ_BEGIN; ucDDRSel < _DDR2_DEV_SEQ_END; ucDDRSel++)
    {
        if(bEnable == _ENABLE)
        {
            // Enable DDR2PLL LDO
            ScalerSetDWord(DDR2_GET_REG(P88_34_CRT_RST_CTL_1, ucDDRSel), 0x00000001);

            DELAY_XUS(150);

            // De-assert both PLL reset and PLL ptr reset
            ScalerSetDWord(DDR2_GET_REG(P88_34_CRT_RST_CTL_1, ucDDRSel), 0x0000000D);

            DELAY_XUS(85);
        }
        else // Disable
        {
            // Assert both PLL reset and PLL ptr reset
            ScalerSetDWord(DDR2_GET_REG(P88_34_CRT_RST_CTL_1, ucDDRSel), 0x00000000);

            DELAY_XUS(85);

            // Disable DDR2PLL LDO
            ScalerSetDWord(DDR2_GET_REG(P88_34_CRT_RST_CTL_1, ucDDRSel), 0x00000000);

            DELAY_XUS(150);
        }
    }
}

//--------------------------------------------------
// Description  : DDR2PLL Output Control
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerPLLDDR2PLLOutputCtrl(bit bEnable)
{
    BYTE ucDDRSel = 0;

    for(ucDDRSel = _DDR2_DEV_SEQ_BEGIN; ucDDRSel < _DDR2_DEV_SEQ_END; ucDDRSel++)
    {
        if(bEnable == _ENABLE)
        {
            // Enable DDR2PLL CLK
            ScalerSetDWord(DDR2_GET_REG(P88_04_PLL_CTRL0_1, ucDDRSel), 0x00CF18CF);

            DELAY_XUS(85);

            // Enable DDR2PLL CLK output, and wait until PLL is stable
            ScalerSetDWord(DDR2_GET_REG(P88_08_PLL_CTRL1_1, ucDDRSel), (0x00CF0000 | ((~0xFFFFF800 & GET_OESYNC_SETTING(tDDR2_PLL_PHASE[ucDDRSel])))));
            ScalerTimerPollingFlagProc(40, DDR2_GET_REG(P90_13_INT_STATUS2_0, ucDDRSel), _BIT0, _TRUE);
        }
        else // Disable
        {
            // Disable DDR2PLL CLK
            ScalerSetDWord(DDR2_GET_REG(P88_04_PLL_CTRL0_1, ucDDRSel), 0x000018CF);

            DELAY_XUS(85);

            // Disable DDR2PLL A CLK output
            ScalerSetDWord(DDR2_GET_REG(P88_08_PLL_CTRL1_1, ucDDRSel), (0x00000000 | ((~0xFFFFF800 & GET_OESYNC_SETTING(tDDR2_PLL_PHASE[ucDDRSel])))));

            DELAY_XUS(85);
        }
    }
}

//--------------------------------------------------
// Description  : Set DDR2PLL Freq
// Input Value  : Target DDR Data Rate (KHz)
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDDR2PLLFreq(DWORD ulFreq)
{
    BYTE ucNCode = 0;
    BYTE ucDDRSel = 0;
    DWORD ulDpiNCode = 0;
    DWORD ulDpiFCode = 0;

    // Disable CLK output, Reset PLL, Disable PLL
    ScalerPLLDDR2PLLOutputCtrl(_DISABLE);
    ScalerPLLDDR2PLLCtrl(_DISABLE);

    for(ucDDRSel = _DDR2_DEV_SEQ_BEGIN; ucDDRSel < _DDR2_DEV_SEQ_END; ucDDRSel++)
    {
        // Enable DDR2PLL LDO
        ScalerSetDWord(DDR2_GET_REG(P88_34_CRT_RST_CTL_1, ucDDRSel), 0x00000001);

        DELAY_XUS(150);

        //=============================================
        // Set DDR2PLL phase
        //=============================================
        // Set DDR initial phase
        ScalerSetDWord(DDR2_GET_REG(P88_00_CRT_CTRL_1, ucDDRSel), 0x00000002);
        ScalerPLLSetDDR2PLLWritePhase(&(tDDR2_PLL_PHASE[ucDDRSel]), ucDDRSel);

        //=============================================
        // Set coefficient of DDR2PLL
        //=============================================
        if(ulFreq >= 1600000)
        {
            ScalerSetDWord(DDR2_GET_REG(P88_1C_PLL_CTRL3_1, ucDDRSel), 0x23905354);
        }
        else if(ulFreq >= 1333000)
        {
            ScalerSetDWord(DDR2_GET_REG(P88_1C_PLL_CTRL3_1, ucDDRSel), 0x22905354);
        }
        else if(ulFreq >= 1066000)
        {
            ScalerSetDWord(DDR2_GET_REG(P88_1C_PLL_CTRL3_1, ucDDRSel), 0x22505254);
        }
        else if(ulFreq >= 677000)
        {
            ScalerSetDWord(DDR2_GET_REG(P88_1C_PLL_CTRL3_1, ucDDRSel), 0x25105134);
        }
        else
        {
            ScalerSetDWord(DDR2_GET_REG(P88_1C_PLL_CTRL3_1, ucDDRSel), 0x25105034);
        }

        // pll_sel_cpmode
        ScalerSetDWord(DDR2_GET_REG(P88_04_PLL_CTRL0_1, ucDDRSel), 0x000018CF);
    }

    //=============================================
    // Calculate Freq. & Set N F code & Disable SSC
    //=============================================
    ucNCode = ulFreq / (DWORD)_EXT_XTAL;

    // Calculate DDRPLL Output Freq. According to current Settings
    PDATA_DWORD(0) = (DWORD)_EXT_XTAL * 1000 * ucNCode;

    // Offset resolution (Dclk / 2^13) in Hz
    PDATA_DWORD(1) = ((DWORD)_EXT_XTAL * 1000 + (1 << 12)) >> 13;

    // Target frequency of DDR clk in Hz
    PDATA_DWORD(1) = ((ulFreq * 1000) - PDATA_DWORD(0)) / PDATA_DWORD(1);
    ulDpiFCode = PDATA_DWORD(1) & 0x1fff;

    // Set DDR PLL N code / Offset / SSC Enable bit
    pData[0] = ucNCode - ((ucNCode >= 2) ? 2 : 0);
    ulDpiNCode = (0x00000000 | pData[0]);


    for(ucDDRSel = _DDR2_DEV_SEQ_BEGIN; ucDDRSel < _DDR2_DEV_SEQ_END; ucDDRSel++)
    {
        // Set N F code
        ScalerSetDWord(DDR2_GET_REG(P88_28_PLL_SSC2_1, ucDDRSel), ulDpiNCode);
        ScalerSetDWord(DDR2_GET_REG(P88_24_PLL_SSC1_1, ucDDRSel), ulDpiFCode);

        // Set WD disable
        ScalerSetDWord(DDR2_GET_REG(P88_2C_PLL_WDOG_1, ucDDRSel), 0x00000000);

        // Set SSC range & frequency = 0
        ScalerSetDWord(DDR2_GET_REG(P88_20_PLL_SSC0_1, ucDDRSel), 0x00000000);


        // De-assert PLL reset
        ScalerSetDWord(DDR2_GET_REG(P88_34_CRT_RST_CTL_1, ucDDRSel), 0x0000000D);
    }

    DELAY_XUS(150);

    // Enable PLL CLK output
    ScalerPLLDDR2PLLOutputCtrl(_ENABLE);
}

//--------------------------------------------------
// Description  : Set DDR2PLL Write Phase
// Input Value  : pstDDR2PLLPhase, bDDRSel
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDDR2PLLWritePhase(StructDDR2PLLPI code *pstDDR2PLLPhase, bit bDDRSel)
{
    StructDDR2PLLPI stPI;
    DWORD ulPITemp = 0;

    //-------------------------------
    // Fetch PLL phase info
    //-------------------------------
    stPI.ucCLK = pstDDR2PLLPhase->ucCLK % _TOT_DDR2_PLL_PI_NUM;
    stPI.ucCMD = pstDDR2PLLPhase->ucCMD % _TOT_DDR2_PLL_PI_NUM;
    stPI.ucDQS0 = pstDDR2PLLPhase->ucDQS0 % _TOT_DDR2_PLL_PI_NUM;
    stPI.ucDQS1 = pstDDR2PLLPhase->ucDQS1 % _TOT_DDR2_PLL_PI_NUM;
    stPI.ucDQ0 = pstDDR2PLLPhase->ucDQ0 % _TOT_DDR2_PLL_PI_NUM;
    stPI.ucDQ1 = pstDDR2PLLPhase->ucDQ1 % _TOT_DDR2_PLL_PI_NUM;

    // CLK/CMD/DQS0/DQS1
    ulPITemp = ((DWORD)stPI.ucDQS1 << 24) | ((DWORD)stPI.ucDQS0 << 16) | ((DWORD)stPI.ucCMD << 8) | ((DWORD)stPI.ucCLK);
    ScalerSetDWord(DDR2_GET_REG(P88_10_PLL_PI0_1, bDDRSel), ulPITemp);

    // DQ0
    ulPITemp = (DWORD)stPI.ucDQ0 << 16;
    ScalerSetDWord(DDR2_GET_REG(P88_14_PLL_PI1_1, bDDRSel), ulPITemp);

    // DQ1
    ulPITemp = stPI.ucDQ1;
    ScalerSetDWord(DDR2_GET_REG(P88_18_PLL_PI2_1, bDDRSel), ulPITemp);

    // Set dpi_oesync_op_sel
    ScalerSetDWord(DDR2_GET_REG(P88_08_PLL_CTRL1_1, bDDRSel), (~0xFFFFF800 & GET_OESYNC_SETTING(stPI)));
}
#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
//--------------------------------------------------
// Description  : Set DDRPLL Freq
// Input Value  : Target DDR Data Rate (KHz)
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDDRPLLFreq(DWORD ulFreq)
{
    BYTE ucNCode = 0;

    // Disable CLK output, Reset PLL, Disable PLL
    ScalerSetDWord(PA5_00_SYS_PLL_DDR1_1, 0x000000FC);

    //===========================
    // Set coefficient of DDR PLL
    //===========================
    // Set reg_cco_band
    if(ulFreq >= 850000)
    {
        pData[2] = 0x79;
    }
    else
    {
        pData[2] = 0x71;
    }

    // Set reg_post_pi_cl, reg_post_pi_bias, reg_post_pi_rl
    if(ulFreq >= 1500000)
    {
        pData[1] = 0x7B;
    }
    else if(ulFreq >= 1300000)
    {
        pData[1] = 0x7A;
    }
    else if(ulFreq >= 1100000)
    {
        pData[1] = 0x76;
    }
    else if(ulFreq >= 900000)
    {
        pData[1] = 0xF6;
    }
    else
    {
        pData[1] = 0xF1;
    }

    // Set reg_loop_pi_isel
    if(ulFreq >= 1400000)
    {
        pData[0] = 0x9B;
    }
    else if(ulFreq >= 1000000)
    {
        pData[0] = 0x9A;
    }
    else if(ulFreq > 600000)
    {
        pData[0] = 0x99;
    }
    else
    {
        pData[0] = 0x98;
    }

    PDATA_DWORD(0) = 0xFE000000 | ((DWORD)pData[2] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[0]);
    ScalerSetDWord(PA5_04_SYS_PLL_DDR2_1, PDATA_DWORD(0));

    //=============================================
    // Calculate Freq. & Set N F code & Disable SSC
    //=============================================
    ucNCode = ulFreq / (DWORD)_EXT_XTAL;

    // Calculate DDRPLL Output Freq. According to current Settings
    PDATA_DWORD(0) = (DWORD)_EXT_XTAL * 1000 * ucNCode;

    // Offset resolution (Dclk / 2^13) in Hz
    PDATA_DWORD(1) = ((DWORD)_EXT_XTAL * 1000 + (1 << 12)) >> 13;

    // Target frequency of DDR clk in Hz
    PDATA_DWORD(1) = ((ulFreq * 1000) - PDATA_DWORD(0)) / PDATA_DWORD(1);
    PDATA_DWORD(1) = PDATA_DWORD(1) & 0x1fff;

    // Set DDR PLL N code / Offset / SSC Enable bit
    pData[0] = ucNCode - ((ucNCode >= 2) ? 2 : 0);
    PDATA_DWORD(1) = (((DWORD)pData[0]) << 20) | ((PDATA_DWORD(1)) << 4);
    ScalerSetDWord(PA5_14_SYS_PLL_DDR_SSC2_1, PDATA_DWORD(1));

#if(_DDR3_MULTIPHASE_EXIST == _ON)
    // Set phase control
    ScalerPLLSetDDRPLLWritePhase(g_stDdr3PhaseData.ulDdrPllInitialPhase0, g_stDdr3PhaseData.ulDdrPllInitialPhase1);
#else
    // Set phase control
    ScalerPLLSetDDRPLLWritePhase(_DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1);
#endif

    // Set WD disable
    ScalerSetDWord(PA5_10_SYS_PLL_DDR_SSC1_1, 0x00000000);

    // Set SSC range & frequency = 0
    ScalerSetDWord(PA5_18_SYS_PLL_DDR_SSC3_1, 0x00000000);
    // ScalerTimerDelayXms(16);

    // Enable PLL
    ScalerSetDWord(PA5_00_SYS_PLL_DDR1_1, 0x000000FD);
    DELAY_XUS(85);

    // Disable Reset PLL
    ScalerSetDWord(PA5_00_SYS_PLL_DDR1_1, 0x000000FF);

    // Delay 2ms
    ScalerTimerDelayXms(2);

    // Enable CLK[0] (internal clk) for phy setting
    ScalerSetDWord(PA5_00_SYS_PLL_DDR1_1, 0x000000FB);

    //== Misc Setting ==//
    // DC1 Write DQS post amble and Read Delay Tap
#if(_DDRPLL_CLK_SOURCE == _DDRPLL_VCO_CLK_1X)
    ScalerSetDWord(PAC_30_DQS_PRE_PST_AMBLE_CTRL1, 0x00000011);  // dqs postamble
    ScalerSetDWord(PAC_30_DQS_PRE_PST_AMBLE_CTRL1, 0x00000000);

    // DDR 1X DC1 Read initial Phase Setting
    ScalerSetDWord(PA8_80_DQ0_1_DLYN_1, 0x1c1c1c1c); // set inital read DQS to DQ phase to tap: 31, 20~39@1.2V,24`29@1.0V

#elif(_DDRPLL_CLK_SOURCE == _DDRPLL_VCO_CLK_2X)
    ScalerSetDWord(PAC_30_DQS_PRE_PST_AMBLE_CTRL1, 0x00000011);
    ScalerSetDWord(PAC_30_DQS_PRE_PST_AMBLE_CTRL1, 0x00001000);

#if(_DDR3_MULTIPHASE_EXIST == _ON)
    // DDR 2X DC1 Read initial Phase Setting
    ScalerSetDWord(PA8_80_DQ0_1_DLYN_1, g_stDdr3PhaseData.ulDdrReadDqDelayTap); // set inital read DQS to DQ phase to tap: 31, 20~39@1.2V,24`29@1.0V
#else
    // DDR 2X DC1 Read initial Phase Setting
    ScalerSetDWord(PA8_80_DQ0_1_DLYN_1, _DDR3_READ_DQ_DLYN_TAP); // set inital read DQS to DQ phase to tap: 31, 20~39@1.2V,24`29@1.0V
#endif

#endif

    // Enable CLK switch
    ScalerSetDWord(PA5_00_SYS_PLL_DDR1_1, 0x00000003);

    // Delay 2ms
    ScalerTimerDelayXms(2);
}

//--------------------------------------------------
// Description  : Set DDRPLL Write Phase
// Input Value  : _DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDDRPLLWritePhase(DWORD ulDDRPLLInitPhase0, DWORD ulDDRPLLInitPhase1)
{
    BYTE pucPhaseOfClk[6];
    BYTE ucSyncSel = 0x00;
    DWORD ulDDRPLLClk2XSel = 0x00000000;

    PDATA_DWORD(0) = ulDDRPLLInitPhase0;
    pucPhaseOfClk[0] = pData[3] & 0x3F; // valid phase range: 0~63
    pucPhaseOfClk[1] = pData[2] & 0x3F;
    pucPhaseOfClk[2] = pData[1] & 0x3F;
    pucPhaseOfClk[3] = pData[0] & 0x3F;

    PDATA_DWORD(0) = ulDDRPLLInitPhase1;
    pucPhaseOfClk[4] = pData[3] & 0x3F;
    pucPhaseOfClk[5] = pData[2] & 0x3F;

#if(_DDRPLL_CLK_SOURCE == _DDRPLL_VCO_CLK_2X)
    // 2X CLK setting
    ulDDRPLLClk2XSel = 0x00000111;
    ulDDRPLLClk2XSel |= ((pucPhaseOfClk[4] >= 32) ? 0x00000200 : 0x00000000);
    ulDDRPLLClk2XSel |= ((pucPhaseOfClk[3] >= 32) ? 0x00000020 : 0x00000000);
    ulDDRPLLClk2XSel |= ((pucPhaseOfClk[2] >= 32) ? 0x00000002 : 0x00000000);

    // DDR PLL sync select setting
    // Fast version of "if((16 <= phase <= 31) OR (48 <= phase <= 63)), then corresponding SyncSel bit is set to 1"
    ucSyncSel |= (((pucPhaseOfClk[0] & _BIT4) == _BIT4) ? _BIT0 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[1] & _BIT4) == _BIT4) ? _BIT1 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[2] & _BIT4) == _BIT4) ? _BIT2 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[3] & _BIT4) == _BIT4) ? _BIT3 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[4] & _BIT4) == _BIT4) ? _BIT4 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[5] & _BIT4) == _BIT4) ? _BIT5 : 0x00);
#endif

    ScalerSetDWord(PA5_1C_SYS_PLL5_1, ulDDRPLLClk2XSel);

    pData[0] = ucSyncSel;
    pData[1] = 0x00;
    pData[2] = pucPhaseOfClk[5];
    pData[3] = pucPhaseOfClk[4];
    ScalerSetDWord(PA5_0C_SYS_PLL_DDR4_1, PDATA_DWORD(0));

    pData[0] = pucPhaseOfClk[3];
    pData[1] = pucPhaseOfClk[2];
    pData[2] = pucPhaseOfClk[1];
    pData[3] = pucPhaseOfClk[0];
    ScalerSetDWord(PA5_08_SYS_PLL_DDR3_1, PDATA_DWORD(0));
}

#if(_DDR3_MULTIPHASE_EXIST == _ON)
//--------------------------------------------------
// Description  : Get DDR3 Phase Data From User
// Input Value  : StructDDR3PhaseInfo
// Output Value : None
//--------------------------------------------------
void ScalerPLLGetDDR3PhaseData(StructDDR3PhaseInfo *pstDdr3PhaseData)
{
    g_stDdr3PhaseData = *pstDdr3PhaseData;
}
#endif

#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
