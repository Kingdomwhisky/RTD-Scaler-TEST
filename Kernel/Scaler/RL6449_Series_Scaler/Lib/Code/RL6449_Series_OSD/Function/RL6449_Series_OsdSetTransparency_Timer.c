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
// ID Code      : RL6449_Series_OsdSetTransparency_Timer.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6449_Series_OSDLibInternalInclude.h"

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
void ScalerOsdSetTransparency_EXINT(BYTE ucTransparency);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set OSD Transparency for Timer Interrupt
// Input Value  : ucTransparency -> 0 ~ 255
// Output Value :
//--------------------------------------------------
void ScalerOsdSetTransparency_EXINT(BYTE ucTransparency)
{
    // alpha_blending_level[7:5]
    ScalerSetBit_EXINT(P0_6C_OVERLAY_CTRL, ~(_BIT4 | _BIT3 | _BIT2), ((ucTransparency & 0xE0) >> 3));

    // alpha_blending_level[4:0]
    ScalerSetBit_EXINT(P0_8F_OVERLAY_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), ((ucTransparency & 0x1F) << 3));
}

