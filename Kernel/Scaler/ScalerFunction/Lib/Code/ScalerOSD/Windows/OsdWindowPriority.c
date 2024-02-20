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
// ID Code      : OsdWindowPriority.c
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
void ScalerOsdWindowPriority(EnumOsdWindowsType enumOsdWindowsType, EnumOsdWindowPriorityType enumOsdWindowPriorityType);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set window Priority
// Input Value  : enumOsdWindowsType        -> _OSD_WINDOW_2 or _OSD_WINDOW_3 or _OSD_WINDOW_4 or _OSD_WINDOW_8 or _OSD_WINDOW_9
//                enumOsdWindowPriorityType -> _OSD_WINDOW_PRIORITY_LOWER_THAN_FONT or _OSD_WINDOW_PRIORITY_HIGHTER_THAN_FONT
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowPriority(EnumOsdWindowsType enumOsdWindowsType, EnumOsdWindowPriorityType enumOsdWindowPriorityType)
{
    if(enumOsdWindowsType == _OSD_WINDOW_2)
    {
        ScalerSetBit(P3A_08_FRAME_CTRL_08, ~_BIT7, (enumOsdWindowPriorityType << 7));
    }
    else if(enumOsdWindowsType == _OSD_WINDOW_3)
    {
        ScalerSetBit(P3A_07_FRAME_CTRL_07, ~_BIT0, enumOsdWindowPriorityType);
    }
    else if(enumOsdWindowsType == _OSD_WINDOW_4)
    {
        ScalerSetBit(P3A_07_FRAME_CTRL_07, ~_BIT1, (enumOsdWindowPriorityType << 1));
    }
    else if(enumOsdWindowsType == _OSD_WINDOW_8)
    {
        ScalerSetBit(P3A_08_FRAME_CTRL_08, ~_BIT5, (enumOsdWindowPriorityType << 5));
    }
    else if(enumOsdWindowsType == _OSD_WINDOW_9)
    {
        ScalerSetBit(P3A_08_FRAME_CTRL_08, ~_BIT6, (enumOsdWindowPriorityType << 6));
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdWindowPriority(_OSD_WINDOW_8, _OSD_WINDOW_PRIORITY_HIGHTER_THAN_FONT);
*/
