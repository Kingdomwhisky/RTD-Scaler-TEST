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
// ID Code      : OsdWindowGradientLevel.c
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
void ScalerOsdWindowGradientLevel(EnumOsdWindowsType enumOsdWindowsType, BYTE ucLevelR, BYTE ucLevelG, BYTE ucLevelB);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set window extension gradient level for R/G/B channel
// Input Value  : enumOsdWindowsType -> _OSD_WINDOW_0, _OSD_WINDOW_5, _OSD_WINDOW_6, _OSD_WINDOW_7, _OSD_WINDOW_8, _OSD_WINDOW_9
//                ucLevelR           -> window RED extension gradient level (0 ~ 255)
//                ucLevelG           -> window GRN extension gradient level (0 ~ 255)
//                ucLevelB           -> window BLU extension gradient level (0 ~ 255)
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowGradientLevel(EnumOsdWindowsType enumOsdWindowsType, BYTE ucLevelR, BYTE ucLevelG, BYTE ucLevelB)
{
    WORD usTempWindowNumber = 0;

    usTempWindowNumber = 0x174 + (enumOsdWindowsType * 7);
    ScalerOsdWriteAllByte((_OSD_WIN_CONTROL), usTempWindowNumber, ucLevelR, ucLevelG, ucLevelB);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    SET_OSD_WINDOW_GRADIENT_ENABLE_R(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_ENABLE(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_LEVEL_EXTENSION(_OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_256);
    SET_OSD_WINDOW_NUMBER(5);
    SET_OSD_WINDOW_COLOR(4);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    ScalerOsdDrawWindow(XSTART(100), YSTART(200), XEND(300), YEND(400));
    ScalerOsdWindowGradientLevel(_OSD_WINDOW_0, 100, 100, 100);
*/

