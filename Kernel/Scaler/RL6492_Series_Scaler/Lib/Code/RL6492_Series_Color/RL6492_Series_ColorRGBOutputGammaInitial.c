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
// ID Code      : RL6492_Series_ColorRGBOutputGammaInitial.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6492_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _RGB_GAMMA_START_POINT        8
#define _RGB_GAMMA_BLEND_LAYER        0 // 0:63 1:127 2:255
#define _RGB_GAMMA_CEN_TH             0 // 0:4 1:8

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
void ScalerColorRGBOutputGammaInitial(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust output gamma
// Input Value  : SelRegion ans Gamma Table and Gamma Table Banks and Table Length
// Output Value : None
//--------------------------------------------------
void ScalerColorRGBOutputGammaInitial(void)
{
    ScalerSetByte(P9_D1_RGB_GAMMA_START_POINT_M1, _RGB_GAMMA_START_POINT);

    ScalerSetBit(P9_D2_RGB_GAMMA_ADJUST_M1, ~(_BIT5 | _BIT4), (_RGB_GAMMA_BLEND_LAYER << 4));

    ScalerSetBit(P9_D2_RGB_GAMMA_ADJUST_M1, ~_BIT0, _RGB_GAMMA_CEN_TH);
}
