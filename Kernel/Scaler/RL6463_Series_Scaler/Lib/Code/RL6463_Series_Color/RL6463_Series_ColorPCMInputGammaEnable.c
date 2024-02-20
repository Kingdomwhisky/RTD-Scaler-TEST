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
// ID Code      : RL6463_Series_ColorPCMInputGammaEnable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6463_Series_ColorLibInternalInclude.h"

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
void ScalerColorPCMInputGammaEnable(EnumFunctionOnOFF enumOn);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable/Disable Input gamma
// Input Value  : _FUNCTION_ON / _FUNCTION_OFF /_FUNCTION_CLOCK_GATED
// Output Value : None
//--------------------------------------------------
void ScalerColorPCMInputGammaEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        // Disable Clock Gated
        ScalerSetBit(P9_A1_INPUT_GAMMA_CTRL, ~_BIT6, _BIT6);
    }
    else // _FUNCTION_CLOCK_GATED
    {
        ScalerSetBit(P9_A1_INPUT_GAMMA_CTRL, ~_BIT6, 0x00);
    }
}
