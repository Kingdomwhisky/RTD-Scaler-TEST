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
//-------------------------------------------------------------------------------------//
// ID Code      : RL6410_Series_ColorGlobalHueSatEnable.c
// Update Note  :
//-------------------------------------------------------------------------------------//
#include "RL6410_Series_ColorLibInternalInclude.h"

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
void ScalerColorSRGBEnable(EnumFunctionOnOFF enumOn);



//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable/Disable SRGB function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorSRGBEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT1, _BIT1);
        ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT2, _BIT2);
    }
    else if(enumOn == _FUNCTION_OFF)
    {
        ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT2, 0x00);
    }
    else
    {
        ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT2, 0x00);
        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT1, 0x00);
    }
}

