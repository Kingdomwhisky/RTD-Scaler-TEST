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
// ID Code      : RL6410_Series_ColorPanelUniformityEnable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
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
void ScalerColorPanelUniformityEnable(EnumFunctionOnOFF enumOn);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable/Disable Panel Uniformity
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityEnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT0, _BIT0);
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT7, _BIT7);
    }
    else if(enumOn == _FUNCTION_OFF)
    {
        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT0, _BIT0);
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT7, 0x00);
    }
    else
    {
        ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT7, 0x00);
        ScalerTimerWaitForEvent(_EVENT_DVS);
        ScalerTimerDelayXms(2);
        ScalerSetBit(P1_DB_DCLK_GATED_CTRL1, ~_BIT0, 0x00);
    }
}
