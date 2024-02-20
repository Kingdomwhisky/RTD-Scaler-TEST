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
// ID Code      : RL6432_Series_OsdVerticalBoundaryFunction.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_OSDLibInternalInclude.h"

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
void ScalerOsdVerticalBoundary(bit bEnable);
void ScalerOsdVerticalBoundarySize(WORD usUpperBoundary, WORD usLowerBoundary);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set vertical boundary function
// Input Value  : bEnable   -> _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerOsdVerticalBoundary(bit bEnable)
{
    ScalerSetBit(P3A_18_FRAME_CTRL_18, ~_BIT5, ((BYTE)bEnable << 5));
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdVerticalBoundary(_ENABLE);
*/


//--------------------------------------------------
// Description  : Set vertical boundary size
// Input Value  : usUpperBoundary -> 0 ~ 2047
//                usLowerBoundary -> 0 ~ 2047
// Output Value :
//--------------------------------------------------
void ScalerOsdVerticalBoundarySize(WORD usUpperBoundary, WORD usLowerBoundary)
{
    ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT6 | _BIT5 | _BIT4), ((HIBYTE(usUpperBoundary) & 0x07) << 4));   // OSD Vertical Upper Boundary [10:8]
    ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT2 | _BIT1 | _BIT0), (HIBYTE(usLowerBoundary) & 0x07));          // OSD Vertical Lower Boundary [10:8]

    ScalerSetByte(P3A_1F_FRAME_CTRL_1F, LOBYTE(usUpperBoundary)); // OSD Vertical Upper Boundary [7:0]
    ScalerSetByte(P3A_20_FRAME_CTRL_20, LOBYTE(usLowerBoundary)); // OSD Vertical Lower Boundary [7:0]
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdVerticalBoundarySize(YSTART(100), YEND(1000));
*/

