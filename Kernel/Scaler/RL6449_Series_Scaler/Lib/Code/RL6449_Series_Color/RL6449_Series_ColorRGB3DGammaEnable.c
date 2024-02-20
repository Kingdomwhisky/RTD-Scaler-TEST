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
// ID Code      : RL6449_Series_ColorRGB3DGammaEnable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6449_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Table Length
//--------------------------------------------------



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
void ScalerColorRGB3DGammaEnable(EnumFunctionOnOFF enumOn);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable/Disable 3D Gamma
// Input Value  : _FUNCTION_ON / _FUNCTION_OFF/_FUNCTION_CLOCK_GATED
// Output Value : None
//--------------------------------------------------
void ScalerColorRGB3DGammaEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT3, _BIT3);
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT7, _BIT7);
    }
    else if(enumOn == _FUNCTION_OFF)
    {
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT7, 0x00);
    }
    else // _FUNCTION_CLOCK_GATED
    {
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT3, 0x00);
    }
}

