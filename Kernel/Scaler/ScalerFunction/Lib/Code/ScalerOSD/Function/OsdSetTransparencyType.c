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
// ID Code      : OsdSetTransparencyType.c
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
void ScalerOsdSetTransparencyType(EnumOsdTransparencyType enumOsdTransparencyType);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set Osd transparency type
// Input Value  : enumOsdTransparencyType -> _OSD_TRANSPARENCY_DISABLE or _OSD_TRANSPARENCY_ONLY_WINDOW                      or
//                                           _OSD_TRANSPARENCY_ALL     or _OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND
// Output Value :
//--------------------------------------------------
void ScalerOsdSetTransparencyType(EnumOsdTransparencyType enumOsdTransparencyType)
{
    ScalerSetBit(P3A_0A_FRAME_CTRL_0A, ~(_BIT3 | _BIT2), enumOsdTransparencyType);
}


