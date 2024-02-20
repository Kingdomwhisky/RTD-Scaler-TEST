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
// ID Code      : Osd1BitFontShrink.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerOSDLibInternalInclude.h"

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
void ScalerOsd1BitFontShrink(EnumOsd1BitShrinkType enumOsd1BitShrinkType);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : enumOsd1BitShrinkType -> _OSD_1BIT_SHRINK_BY_MIDDLE or _OSD_1BIT_SHRINK_BY_LEFT or _OSD_1BIT_SHRINK_BY_RIGHT
// Output Value :
//--------------------------------------------------
void ScalerOsd1BitFontShrink(EnumOsd1BitShrinkType enumOsd1BitShrinkType)
{
    ScalerSetBit(P3A_02_FRAME_CTRL_02, ~(_BIT2 | _BIT1), (enumOsd1BitShrinkType << 1));
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsd1BitFontShrink(_OSD_1BIT_SHRINK_BY_LEFT);
*/

