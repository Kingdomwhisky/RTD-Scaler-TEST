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
// ID Code      : RL6410_Series_OsdGetFBShift.c
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
WORD ScalerOsdGetFBShiftValue(EnumOsdFrontBackShiftType enumOsdFrontBackShiftType);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Shift Vertical Boundary Size in Front/Back Mode
// Input Value  : enumOsdFrontBackShiftType   -> _OSD_FRONT_BACK_SHIFT_INSIDE or _OSD_FRONT_BACK_SHIFT_OUTSIDE
// Output Value : 0 ~ 4095
//--------------------------------------------------
WORD ScalerOsdGetFBShiftValue(EnumOsdFrontBackShiftType enumOsdFrontBackShiftType)
{
    switch(enumOsdFrontBackShiftType)
    {
        case _OSD_FRONT_BACK_SHIFT_INSIDE:
            return ((ScalerGetByte(P3A_5B_FRAME_CTRL_5B) << 4) | ((ScalerGetByte(P3A_5D_FRAME_CTRL_5D) & 0xF0) >> 4));

        case _OSD_FRONT_BACK_SHIFT_OUTSIDE:
            return ((ScalerGetByte(P3A_5C_FRAME_CTRL_5C) << 4) | (ScalerGetByte(P3A_5D_FRAME_CTRL_5D) & 0x0F));

        default:
            break;
    }

    return 0x0000;
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdGetFBShiftValue(_OSD_FRONT_BACK_SHIFT_INSIDE);
*/

