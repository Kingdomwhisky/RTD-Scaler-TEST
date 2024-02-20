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
// ID Code      : OsdWindowSpecialColorMask.c
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
void ScalerOsdWindowSpecialColorMask(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, EnumOsdSpecialColorMaskOperation enumOsdSpecialColorMaskOperation);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set window special color mask
// Input Value  : bEnable            -> _ENABLE or _DISABLE
//                enumOsdWindowsType -> _OSD_WINDOW_0, _OSD_WINDOW_5, _OSD_WINDOW_6, _OSD_WINDOW_7, _OSD_WINDOW_8, _OSD_WINDOW_9
//                EnumOsdSpecialColorMaskOperation  -> _OSD_SPECIAL_COLOR_MASK_AND_OPERATION or _OSD_SPECIAL_COLOR_MASK_OR_OPERATION
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowSpecialColorMask(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, EnumOsdSpecialColorMaskOperation enumOsdSpecialColorMaskOperation)
{
    BYTE ucTemp = 0;
    WORD usTempWindowNumber = 0;

    usTempWindowNumber = 0x177 + (enumOsdWindowsType * 7);
    ucTemp = ScalerOsdFrameControlByteGet(usTempWindowNumber, _OSD_BYTE0);
    ucTemp = ((ucTemp & ~(_BIT3 | _BIT2)) | (((BYTE)enumOsdSpecialColorMaskOperation << 3) | ((BYTE)bEnable << 2)));

    ScalerOsdFrameControlByte(usTempWindowNumber, _OSD_BYTE0, ucTemp);
}



/*
//--------------------------------------------------
// example
//--------------------------------------------------
    SET_OSD_WINDOW_NUMBER(0);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    SET_OSD_WINDOW_COLOR(4);
    ScalerOsdDrawWindow(XSTART(100), YSTART(200), XEND(300), YEND(400));
    ScalerOsdWindowSpecialColorMask(_ENABLE, _OSD_WINDOW_0, _OSD_SPECIAL_COLOR_MASK_AND_OPERATION);
*/
