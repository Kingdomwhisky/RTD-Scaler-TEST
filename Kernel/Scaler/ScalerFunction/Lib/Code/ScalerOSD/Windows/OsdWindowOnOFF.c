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
// ID Code      : OsdWindowOnOFF.c
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
void ScalerOsdWindowOnOFF(EnumOsdWindowsType enumOsdWindowsType, bit bWinOnOff);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable/Disable window
// Input Value  : enumOsdWindowsType -> _OSD_WINDOW_0,   _OSD_WINDOW_1,   _OSD_WINDOW_2,   _OSD_WINDOW_3,   _OSD_WINDOW_4,   _OSD_WINDOW_5,
//                                      _OSD_WINDOW_6,   _OSD_WINDOW_7,   _OSD_WINDOW_8,   _OSD_WINDOW_9,   _OSD_WINDOW_4_1, _OSD_WINDOW_4_2,
//                                      _OSD_WINDOW_4_3, _OSD_WINDOW_4_4, _OSD_WINDOW_4_5, _OSD_WINDOW_4_6, _OSD_WINDOW_4_7, _OSD_WINDOW_4_8
//                                      _OSD_WINDOW_5_1, _OSD_WINDOW_5_2, _OSD_WINDOW_5_3, _OSD_WINDOW_5_4, _OSD_WINDOW_5_5, _OSD_WINDOW_5_6,
//                                      _OSD_WINDOW_5_7, _OSD_WINDOW_5_8
//                                      _OSD_WINDOW_ALL,
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowOnOFF(EnumOsdWindowsType enumOsdWindowsType, bit bWinOnOff)
{
    if(enumOsdWindowsType <= _OSD_WINDOW_7)
    {
        // _OSD_WINDOW_0 ~ _OSD_WINDOW_7
        ScalerSetBit(P3A_57_FRAME_CTRL_57, ~(_BIT0 << enumOsdWindowsType), ((BYTE)bWinOnOff << enumOsdWindowsType));
    }
    else if((enumOsdWindowsType == _OSD_WINDOW_8) || (enumOsdWindowsType == _OSD_WINDOW_9))
    {
        // _OSD_WINDOW_8 ~ _OSD_WINDOW_9
        ScalerSetBit(P3A_58_FRAME_CTRL_58, ~(_BIT0 << (enumOsdWindowsType - _OSD_WINDOW_8)), ((BYTE)bWinOnOff << (enumOsdWindowsType - _OSD_WINDOW_8)));
    }
    else if((enumOsdWindowsType >= _OSD_WINDOW_4_1) && (enumOsdWindowsType <= _OSD_WINDOW_4_8))
    {
        // _OSD_WINDOW_4_1 ~ _OSD_WINDOW_4_8
        ScalerSetBit(P3A_59_FRAME_CTRL_59, ~(_BIT0 << (enumOsdWindowsType - _OSD_WINDOW_4_1)), ((BYTE)bWinOnOff << (enumOsdWindowsType - _OSD_WINDOW_4_1)));
    }
#if(_OSD_WINDOW_5_1_5_8_SUPPORT == _ON)
    else if((enumOsdWindowsType >= _OSD_WINDOW_5_1) && (enumOsdWindowsType <= _OSD_WINDOW_5_8))
    {
        // _OSD_WINDOW_5_1 ~ _OSD_WINDOW_5_8
        ScalerSetBit(P3A_5A_FRAME_CTRL_5A, ~(_BIT0 << (enumOsdWindowsType - _OSD_WINDOW_5_1)), ((BYTE)bWinOnOff << (enumOsdWindowsType - _OSD_WINDOW_5_1)));
    }
#endif
}
