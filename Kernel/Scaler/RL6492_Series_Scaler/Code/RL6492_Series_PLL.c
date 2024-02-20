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
// ID Code      : RL6492_Series_PLL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Definations of DPTX CMU CCO Range
//--------------------------------------------------
#define _DPTX_PLL_BOUNDRY_0                         187500
#define _DPTX_PLL_BOUNDRY_1                         375000
#define _DPTX_PLL_BOUNDRY_2                         750000
#define _DPTX_PLL_BOUNDRY_3                         1500000

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

#if(_PANEL_STYLE == _PANEL_DPTX)
//--------------------------------------------------
// Definations of DPTX CLK Into DPLL Range
//--------------------------------------------------
#define _DPTX_CLK_IN_BOUNDRY_0                      56000
#define _DPTX_CLK_IN_BOUNDRY_1                      112000
#define _DPTX_CLK_IN_BOUNDRY_2                      224000

//--------------------------------------------------
// Definations of DPTX Phy Rate
//--------------------------------------------------
#define _DPTX_PHY_RATE_RBR                          1620000
#define _DPTX_PHY_RATE_HBR                          2700000
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_DPTX)
bit ScalerPLLGetDptxPowerStatus(void);
#endif
DWORD ScalerPLLGetDPLLRefClk(DWORD ulFreq);

#if(_PANEL_STYLE == _PANEL_LVDS)
void ScalerPLLSetDisplayPLL(DWORD ulFreq);
#elif(_PANEL_STYLE == _PANEL_DPTX)
void ScalerPLLSetDPLLRefPLL(DWORD ulFreq);
void ScalerPLLDPTxPLLReset(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_DPTX)
//--------------------------------------------------
// Description  : Get Dptx Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerPLLGetDptxPowerStatus(void)
{
    return (bit)(ScalerGetBit(P55_00_LVDS_COMMON_AB_CTRL0, _BIT3));
}
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

//--------------------------------------------------
// Description  : Get DPLL Ref Clk from DPTx PLL or Xtal
// Input Value  : Dclk
// Output Value : DPTx PLL clk or Xtal Clk
//--------------------------------------------------
DWORD ScalerPLLGetDPLLRefClk(DWORD ulFreq)
{
    ulFreq = ulFreq;

    // Dpll Referenced Clk: Xtal Clk
    ScalerSetBit(P1_BF_DPLL_CLK_CTRL_0, ~(_BIT1), 0x00);

    return (_EXT_XTAL);
}

#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Description  : Set Display Interface PLL: Frequency, VCO Band
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDisplayPLL(DWORD ulFreq)
{
    BYTE ucDispPllParam = 0x00;
    WORD usNCode = 0;
    DWORD ulCMUFreq = 0;

    PDATA_DWORD(0) = (ulFreq >> _D_DOMAIN_PATH) * 16 / 15;

    // LVDS data rate = ((Pixel Clk) / (LVDS Outport)) * 7
    ulCMUFreq = ((PDATA_DWORD(0) << _D_DOMAIN_PATH) / (1 << _LVDS_OUTPUT_PORT)) * 7;

    // ucDispPllParam: [3:2] = LVDS PI Operation Frequency Seletcion
    if(ulCMUFreq < 250000)
    {
        ucDispPllParam |= 0;
    }
    else if(ulCMUFreq < 400000)
    {
        ucDispPllParam |= 1;
    }
    else if(ulCMUFreq < 600000)
    {
        ucDispPllParam |= 2;
    }
    else
    {
        ucDispPllParam |= 3;
    }

    // Set LVDS PI Operation band
    ScalerDisplayLvdsSetPhaseBand(ucDispPllParam << 5);

    // Set CMU: LVDS Mode
    ScalerSetBit(P55_73_DPTX_CMU3, ~_BIT0, 0x00);

    // Set CMU Referenced Clk: From Dpll Clk
    ScalerSetBit(P55_73_DPTX_CMU3, ~_BIT7, _BIT7);

    // Enable N.F Set By FW
    ScalerSetBit(P38_D6_DPTX_CMU6, ~_BIT5, _BIT5);

    // Divider for Postdivider of CMU and Pre-divder of CMU
    ScalerSetBit(P55_72_DPTX_CMU2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // LDO voltage Setting
    ScalerSetBit(P55_0E_LVDS_COMMON_AB_CTRL14, ~0xFC, 0xFC);

    // Setting 16 Phase when N.PI Manual
    ScalerSetBit(P38_D7_DPTX_CMU7, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // CLKRD duty set to 4'b1111 @0638 as AMlee suggests.
    // Good Phase setting H/L = 4/6
    ScalerSetBit(P55_5D_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

    // [2] 0:Small Kvco, 1:Big Kvco
    // [1] 0:CCO Mode, 1:VCO Mode
    ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~(_BIT2 | _BIT1), _BIT2);

    // [4] 0:3pF, 1:4pF (CMU'S LPF Cp)
    ScalerSetBit(P55_0D_LVDS_COMMON_AB_CTRL13, ~_BIT4, _BIT4);

    // [0] 0:3rd LPF, 1:2nd LPF
    ScalerSetBit(P55_0F_LVDS_COMMON_AB_CTRL15, ~_BIT0, _BIT0);

    // [3] 0:Bypass PI, 1:Use PI
    // [2:0] PI Current setting
    ScalerSetBit(P55_70_DPTX_CMU0, ~0x0F, (_BIT1 | _BIT0));

    if(ulCMUFreq > _DPTX_PLL_BOUNDRY_3)
    {
        // VCO = 1.5~3 GHz, Phy range = 1.5~3 GHz, Freq_band = div1
        ScalerSetBit(P55_0F_LVDS_COMMON_AB_CTRL15, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

        // [7:5] PLL LPF serial resistor
        // [3:0] CMU'S CP Current
        ScalerSetBit(P55_0D_LVDS_COMMON_AB_CTRL13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1));
    }
    else if(ulCMUFreq > _DPTX_PLL_BOUNDRY_2)
    {
        // VCO = 1.5~3 GHz, Phy range = 0.75~1.5 GHz, Freq_band = div2
        ScalerSetBit(P55_0F_LVDS_COMMON_AB_CTRL15, ~(_BIT3 | _BIT2 | _BIT1), _BIT1);

        // [7:5] PLL LPF serial resistor
        // [3:0] CMU'S CP Current
        ScalerSetBit(P55_0D_LVDS_COMMON_AB_CTRL13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1));
    }
    else if(ulCMUFreq > _DPTX_PLL_BOUNDRY_1)
    {
        // VCO = 1.5~3 GHz, Phy range = 375~750 MHz, Freq_band = div4
        ScalerSetBit(P55_0F_LVDS_COMMON_AB_CTRL15, ~(_BIT3 | _BIT2 | _BIT1), _BIT2);

        // [7:5] PLL LPF serial resistor
        // [3:0] CMU'S CP Current
        ScalerSetBit(P55_0D_LVDS_COMMON_AB_CTRL13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1));
    }
    else if(ulCMUFreq > _DPTX_PLL_BOUNDRY_0)
    {
        // VCO = 1.5~3 GHz, Phy range = 187.5~375 MHz, Freq_band = div4
        ScalerSetBit(P55_0F_LVDS_COMMON_AB_CTRL15, ~(_BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

        // [7:5] PLL LPF serial resistor
        // [3:0] CMU'S CP Current
        ScalerSetBit(P55_0D_LVDS_COMMON_AB_CTRL13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1));
    }
    else
    {
        // VCO = 1.5~3 GHz, Phy range = 93.75~187.5 MHz, Freq_band = div8
        ScalerSetBit(P55_0F_LVDS_COMMON_AB_CTRL15, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);

        // [7:5] PLL LPF serial resistor
        // [3:0] CMU'S CP Current
        ScalerSetBit(P55_0D_LVDS_COMMON_AB_CTRL13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1));
    }

    // Count N.F Code
    usNCode = (7 - 2);

    // N Code = 9 bit
    usNCode &= 0x1FF;

    ScalerSetBit(P38_D6_DPTX_CMU6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)(usNCode >> 4));
    ScalerSetBit(P38_D7_DPTX_CMU7, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (BYTE)(usNCode << 4));
}

#elif(_PANEL_STYLE == _PANEL_DPTX)
//--------------------------------------------------
// Description  : Set DPLL Referenced DPTX PLL: Frequency, VCO Band
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLRefPLL(DWORD ulFreq)
{
    WORD usNCode = 0;
    WORD usFCode = 0;
    DWORD ulCMUFreq = 0;

    if(ScalerGetBit(P55_00_LVDS_COMMON_AB_CTRL0, _BIT3) == _BIT3)
    {
        return;
    }

    ulFreq = ulFreq;

    // HBR = 2.7GHz, RBR = 1.62GHz
    if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_RBR)
    {
        ulCMUFreq = _DPTX_PHY_RATE_RBR;
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR)
    {
        ulCMUFreq = _DPTX_PHY_RATE_HBR;
    }

    // Set CMU: DPTX Mode
    ScalerSetBit(P55_73_DPTX_CMU3, ~_BIT0, _BIT0);

    // Set CMU Referenced Clk: Xtal Clk
    ScalerSetBit(P55_73_DPTX_CMU3, ~_BIT7, 0x00);

    // Disable N.F Set By FW
    ScalerSetBit(P38_D6_DPTX_CMU6, ~_BIT5, 0x00);

    // Set Down SSC, Disable SSC
    ScalerSetBit(P38_D5_DPTX_CMU5, ~(_BIT6 | _BIT5), 0x00);

    // Divider for Postdivider of CMU and Pre-divder of CMU
    ScalerSetBit(P55_72_DPTX_CMU2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // LDO voltage Setting
    ScalerSetBit(P55_0E_LVDS_COMMON_AB_CTRL14, ~0xFC, 0xFC);

    // CLKRD duty set to 4'b1111 @0638 as AMlee suggests.
    // Good Phase setting H/L = 4/6
    ScalerSetBit(P55_5D_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

    // [7] 0:CCO Mode, 1:VCO Mode
    // [6] 0:Small Kvco, 1:Big Kvco
    // [5] 0:3rd LPF, 1:2nd LPF
    // [4] 0:1pF, 1:2pF (CMU'S LPF Cp)
    // [3] 0:Use PI, 1:Bypass PI
    // [2:0] PI Current setting
    // ScalerSetBit(P38_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

    // [2] 0:Small Kvco, 1:Big Kvco
    // [1] 0:CCO Mode, 1:VCO Mode
    ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~(_BIT2 | _BIT1), _BIT2);

    // [4] 0:3pF, 1:4pF (CMU'S LPF Cp)
    ScalerSetBit(P55_0D_LVDS_COMMON_AB_CTRL13, ~_BIT4, _BIT4);

    // [0] 0:3rd LPF, 1:2nd LPF
    ScalerSetBit(P55_0F_LVDS_COMMON_AB_CTRL15, ~_BIT0, _BIT0);

    // [3] 0:Use PI, 1:Bypass PI
    // [2:0] PI Current setting
    ScalerSetBit(P55_70_DPTX_CMU0, ~0x0F, (_BIT1 | _BIT0));

    // Phy range = 1.5~3 GHz, VCO = 1.5~3 GHz, spdsel = div1
    ScalerSetBit(P55_5D_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT1 | _BIT0), 0x00);

    // [7:5] PLL LPF serial resistor
    // [3:0] CMU'S CP Current
    ScalerSetBit(P55_0D_LVDS_COMMON_AB_CTRL13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1));

    // Count N.F Code
    usNCode = ulCMUFreq / (_EXT_XTAL * 2) - 4;
    usFCode = ulCMUFreq % (_EXT_XTAL * 2);

    if(usFCode != 0)
    {
        ulCMUFreq = ((DWORD)usFCode << 12);
        usFCode = ulCMUFreq / (_EXT_XTAL * 2);
    }

    // N Code = 9 bit
    // F Code = 12 bit
    usNCode &= 0x1FF;
    usFCode &= 0xFFF;

    ScalerSetByte(P38_DF_DPTX_CMU14, (BYTE)usFCode);
    ScalerSetByte(P38_DE_DPTX_CMU13, ((BYTE)(usNCode << 4) | (BYTE)(usFCode >> 8)));
    ScalerSetByte(P38_DD_DPTX_CMU12, (BYTE)(_BIT7 | (usNCode >> 4)));

    // Enable CMU power
    ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~_BIT3, _BIT3);

    // Wait for CMU Stable
    ScalerTimerDelayXms(2);

    // Enable Watch Dog
    ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT7, _BIT7);

    // Wait Watch Dog to check PLL is stable or not
    ScalerTimerPollingFlagProc(2, P38_D4_DPTX_CMU4, _BIT7, _TRUE);

    // Disable WD
    ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Reset DPTX PLL Setting, Disable DPTX PLL Spread Spectrum Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPLLDPTxPLLReset(void)
{
    // Check SSC is enable or not
    if(ScalerGetBit(P38_D5_DPTX_CMU5, _BIT5) != 0x00)
    {
        // Disable SSC
        ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT5, 0x00);

        // SSC Off stable
        ScalerTimerDelayXms(2);
    }

    // Disable CMU Power
    ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~_BIT3, 0x00);
}
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

