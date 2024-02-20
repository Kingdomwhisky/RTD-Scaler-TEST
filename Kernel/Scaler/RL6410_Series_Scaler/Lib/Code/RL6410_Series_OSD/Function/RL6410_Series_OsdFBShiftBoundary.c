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
// ID Code      : RL6410_Series_OsdFBShiftBoundary.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_OSDLibInternalInclude.h"

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
void ScalerOsdFBShiftBoundarySize(WORD usUpperBoundary, WORD usLowerBoundary);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set Shift Vertical Boundary Size in Front/Back Mode
// Input Value  : usUpperBoundary -> 0 ~ 4095
//                usLowerBoundary -> 0 ~ 4095
// Output Value :
//--------------------------------------------------
void ScalerOsdFBShiftBoundarySize(WORD usUpperBoundary, WORD usLowerBoundary)
{
    BYTE ucBoundary_L = 0x00;

    ScalerSetByte(P3A_8C_FRAME_CTRL_8C, (usUpperBoundary >> 4));         // OSD Vertical Upper Boundary [11:4]
    ScalerSetByte(P3A_8D_FRAME_CTRL_8D, (usLowerBoundary >> 4));         // OSD Vertical Lower Boundary [11:4]

    // OSD Vertical Upper Boundary [0:3]
    // OSD Vertical Lower Boundary [0:3]
    ucBoundary_L = (((usUpperBoundary & 0x0F) << 4) | (usLowerBoundary & 0x0F));
    ScalerSetByte(P3A_8E_FRAME_CTRL_8E, ucBoundary_L);
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdFBShiftBoundarySize(YSTART(100), YEND(1000));
*/

