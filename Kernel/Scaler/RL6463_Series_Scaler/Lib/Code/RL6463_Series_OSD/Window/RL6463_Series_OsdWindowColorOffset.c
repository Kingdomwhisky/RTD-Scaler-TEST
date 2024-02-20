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
// ID Code      : RL6463_Series_OsdWindowColorOffset.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6463_Series_OSDLibInternalInclude.h"

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
void ScalerOsdWinodwColorOffset(EnumOsdWinColorOffsetType enumOffset);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set OSD Window Color Index offset
// Input Value  : enumOffset -> _OSD_WIN_COLOR_PALETTE_0_15 or _OSD_WIN_COLOR_PALETTE_16_31 ro _OSD_WIN_COLOR_PALETTE_32_41 or _OSD_WIN_COLOR_PALETTE_42_63
// Output Value :
//--------------------------------------------------
void ScalerOsdWinodwColorOffset(EnumOsdWinColorOffsetType enumOffset)
{
    ScalerSetBit(P3A_8F_FRAME_CTRL_8F_DUMMY, ~(_BIT1 | _BIT0), enumOffset);
}

