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
// ID Code      : RL6369_Series_PLL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Definations of LVDS VCO Range, convert into Dclk frequency
//--------------------------------------------------
#define _LVDS_PLL_BOUNDRY_0                         (250000  * (1 << _LVDS_OUTPUT_PORT) / (7 << _D_DOMAIN_PATH))
#define _LVDS_PLL_BOUNDRY_1                         (500000  * (1 << _LVDS_OUTPUT_PORT) / (7 << _D_DOMAIN_PATH))
#define _LVDS_PLL_BOUNDRY_2                         (1000000 * (1 << _LVDS_OUTPUT_PORT) / (7 << _D_DOMAIN_PATH))
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

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
#if(_PANEL_STYLE == _PANEL_LVDS)
void ScalerPLLSetDisplayPLL(DWORD ulFreq);
#endif
DWORD ScalerPLLGetDPLLRefClk(DWORD ulFreq);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Description  : Set Display Interface PLL: Frequency, VCO Band
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDisplayPLL(DWORD ulFreq)
{
    BYTE ucDispPllParam = 0x00;

    PDATA_DWORD(0) = (ulFreq >> _D_DOMAIN_PATH) * 16 / 15;

    // ----------- Previous Select Band & Div Alg. -----------
    // ucDispPllParam: [7:6] = LVDS_PLL_VCO
    if(PDATA_DWORD(0) < _LVDS_PLL_BOUNDRY_0)
    {
        ucDispPllParam |= (3 << 6);
    }
    else if(PDATA_DWORD(0) < _LVDS_PLL_BOUNDRY_1)
    {
        ucDispPllParam |= (2 << 6);
    }
    else if(PDATA_DWORD(0) < _LVDS_PLL_BOUNDRY_2)
    {
        ucDispPllParam |= (1 << 6);
    }
    else
    {
        ucDispPllParam |= (0 << 6);
    }

    // LVDS data rate = ((Pixel Clk) / (LVDS Outport)) * 7
    PDATA_DWORD(1) = ((PDATA_DWORD(0) << _D_DOMAIN_PATH) / (1 << _LVDS_OUTPUT_PORT)) * 7;

    // ucDispPllParam: [3:2] = LVDS PI Operation Frequency Seletcion
    if(PDATA_DWORD(1) < 250000)
    {
        ucDispPllParam |= (0 << 2);
    }
    else if(PDATA_DWORD(1) < 400000)
    {
        ucDispPllParam |= (1 << 2);
    }
    else if(PDATA_DWORD(1) < 600000)
    {
        ucDispPllParam |= (2 << 2);
    }
    else
    {
        ucDispPllParam |= (3 << 2);
    }

    // Manual set LVDS VCO band
    ScalerDisplayLvdsSetVcoBand((ucDispPllParam & 0xC0) >> 6);

    // Set LVDS PI Operation band
    ScalerDisplayLvdsSetPhaseBand(((ucDispPllParam & 0x0C) >> 2) << 5);
}
#endif

//--------------------------------------------------
// Description  : Get DPLL Ref Clk from DPTx PLL or Xtal
// Input Value  : Dclk
// Output Value : DPTx PLL clk or Xtal Clk
//--------------------------------------------------
DWORD ScalerPLLGetDPLLRefClk(DWORD ulFreq)
{
    ulFreq = ulFreq;

    return _EXT_XTAL;
}
