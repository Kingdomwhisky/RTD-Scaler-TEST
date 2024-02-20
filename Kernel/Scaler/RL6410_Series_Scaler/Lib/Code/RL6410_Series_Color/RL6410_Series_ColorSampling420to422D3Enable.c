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
// ID Code      : RL6410_Series_ColorSampling420to422D3Enable.c
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
void ScalerColor420To422D3Enable(EnumFunctionOnOFF enumFunctionOnOFF);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable / Disable 420To422 for D3 source
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerColor420To422D3Enable(EnumFunctionOnOFF enumFunctionOnOFF)
{
    if(enumFunctionOnOFF == _FUNCTION_ON)
    {
        ScalerSetBit(P31_31_YUV420_TO_422_CTL_D2D3, ~_BIT4, _BIT4);
        ScalerSetBit(P31_33_YUV420_TO_YUV422_D3, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
        ScalerSetBit(P31_33_YUV420_TO_YUV422_D3, ~_BIT3, _BIT3);
    }
    else
    {
        ScalerSetBit(P31_33_YUV420_TO_YUV422_D3, ~(_BIT7 | _BIT3), 0x00);
        ScalerSetBit(P31_34_YUV420_TO_YUV422_HSTM0_D2D3, ~_BIT6, 0x00); // reset duplicate mode
    }
}

