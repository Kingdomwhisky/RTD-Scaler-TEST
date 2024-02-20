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
// ID Code      : OsdHorizontalDelayStep.c
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
void ScalerOsdHorizontalDelayStep(EnumOsdHorizontalDelayStepType enumOsdHorizontalDelayStepType);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set osd position
// Input Value  : enumOsdHorizontalDelayStepType -> _OSD_HORIZONTAL_DELAY_STEP_4_PIXEL or _OSD_HORIZONTAL_DELAY_STEP_1_PIXEL
// Output Value :
//--------------------------------------------------
void ScalerOsdHorizontalDelayStep(EnumOsdHorizontalDelayStepType enumOsdHorizontalDelayStepType)
{
    ScalerSetBit(P3A_06_FRAME_CTRL_06, ~_BIT4, (enumOsdHorizontalDelayStepType << 4));
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdHorizontalDelayStep(_OSD_HORIZONTAL_DELAY_STRP_1_PIXEL);
*/
