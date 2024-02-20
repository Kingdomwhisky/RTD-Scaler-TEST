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
// ID Code      : OsdWindowGrayLevel.c
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
void ScalerOsdWindowGrayLevel(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucPixelStep, BYTE ucDecimalPart);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set precise gradient level
// Input Value  : bEnable            -> _ENABLE or _DISABLE
//                enumOsdWindowsType -> _OSD_WINDOW_0, _OSD_WINDOW_5, _OSD_WINDOW_6, _OSD_WINDOW_7, _OSD_WINDOW_8, _OSD_WINDOW_9
//                ucPixelStep        -> Pixel Step for toggle/incremental, can not be 0 (1 ~ 255)
//                ucDecimalPart      -> Decimal part for Pixel-step (0~7)
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowGrayLevel(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucPixelStep, BYTE ucDecimalPart)
{
    WORD usTempWindowNumber = 0;
    BYTE ucTemp = 0;

    usTempWindowNumber = 0x177 + (enumOsdWindowsType * 7);

    ucTemp = ScalerOsdFrameControlByteGet(usTempWindowNumber, _OSD_BYTE0);
    ucTemp = ((ucTemp & ~_BIT1) | ((BYTE)bEnable << 1));

    ScalerOsdFrameControlAllByte(usTempWindowNumber, _OSD_WITHOUT_DB, ucTemp, ucPixelStep, ucDecimalPart);
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    SET_OSD_WINDOW_GRADIENT_ENABLE_R(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_ENABLE(_ENABLE);
    SET_OSD_WINDOW_NUMBER(0);
    SET_OSD_WINDOW_COLOR(4);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    ScalerOsdDrawWindow(XSTART(50), YSTART(450), XEND(1450), YEND(650));
    ScalerOsdWindowGrayLevel(_ENABLE, _OSD_WINDOW_0, 5, 4);
*/
