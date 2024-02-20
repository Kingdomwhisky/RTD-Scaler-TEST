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
// ID Code      : RL6432_Series_ColorUltraVividEnable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_ColorLibInternalInclude.h"

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


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerColorUltraVividEnable(EnumFunctionOnOFF enumFunctionOnOff, EnumDBApply enumDBApply);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable / Disable / Clock Gated UltraVivid Function
// Input Value  : enumFunctionOnOff -> _ENABLE or _DISABLE or _CLCOK_GATED
// Output Value : None
//--------------------------------------------------
void ScalerColorUltraVividEnable(EnumFunctionOnOFF enumFunctionOnOff, EnumDBApply enumDBApply)
{
    if(enumFunctionOnOff == _FUNCTION_ON)
    {
        // Disable UltraVivid Clock Gated
        ScalerSetBit(P0_1F_M1_ICLK_GATED_CTRL1, ~_BIT6, _BIT6);

        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT7, _BIT7);

        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT6, _BIT6);

        // Enable UltraVivid Function
        // ScalerSetBit(P11_A1_I_DLTI_CTRL_M1, ~_BIT0, _BIT0);

        ScalerSetBit(P14_C0_LSR_CTRL, ~_BIT7, _BIT7);

        // Bypass DSHP
        ScalerSetBit(P12_A0_SR_SHP_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);
        ScalerSetBit(P12_A1_SR_SHP_CTRL_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Wait for Double Buffer
        ScalerGlobalIDDomainDBApply(enumDBApply);
    }
    else if(enumFunctionOnOff == _FUNCTION_OFF)
    {
        // Disable UltraVivid Clock Gated
        ScalerSetBit(P0_1F_M1_ICLK_GATED_CTRL1, ~_BIT6, _BIT6);

        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT7, _BIT7);

        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT6, _BIT6);

        // Disable UltraVivid Function
        ScalerSetBit(P11_A1_I_DLTI_CTRL_M1, ~_BIT0, 0x00);

        ScalerSetBit(P14_C0_LSR_CTRL, ~_BIT7, 0x00);

        // Bypass DSHP
        ScalerSetBit(P12_A0_SR_SHP_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);
        ScalerSetBit(P12_A1_SR_SHP_CTRL_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Wait for Double Buffer
        ScalerGlobalIDDomainDBApply(enumDBApply);
    }
    else
    {
        // Disable UltraVivid Clock Gated
        ScalerSetBit(P0_1F_M1_ICLK_GATED_CTRL1, ~_BIT6, _BIT6);

        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT7, _BIT7);

        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT6, _BIT6);

        // Disable UltraVivid Function
        ScalerSetBit(P11_A1_I_DLTI_CTRL_M1, ~_BIT0, 0x00);

        ScalerSetBit(P14_C0_LSR_CTRL, ~_BIT7, 0x00);

        ScalerSetBit(P12_A0_SR_SHP_CTRL_0, ~_BIT7, 0x00);

        // Wait for Double Buffer
        ScalerGlobalIDDomainDBApply(_DB_APPLY_POLLING);

        // Enable IDLTI Clock Gated
        ScalerSetBit(P0_1F_M1_ICLK_GATED_CTRL1, ~_BIT6, 0x00);

        // Enable LSR & D-SHP Clock Gated
        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT7, 0x00);

        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT6, 0x00);
    }
}
