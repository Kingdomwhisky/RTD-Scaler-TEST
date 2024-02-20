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
// ID Code      : OsdBlankFont.c
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
void ScalerOsdBlankFont(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucPixelLength, BYTE ucBackgroundColor, EnumOsdBlankType enumOsdBlankingType);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : ucRow. ucCol. ucLength. ucHeight. -> Just that !!
//                ucPixelLength                     -> BLANK_FONT : 4 ~ 255 other 0 ~ 255
//                ucBackgroundColor                 -> Color number
//                enumOsdBlinkingType               -> _OSD_BLANK_FONT or _OSD_BLANK_ALIGN
// Output Value :
//--------------------------------------------------
void ScalerOsdBlankFont(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucPixelLength, BYTE ucBackgroundColor, EnumOsdBlankType enumOsdBlankingType)
{
    BYTE ucTemp = 0;

    enumOsdBlankingType = (enumOsdBlankingType & 0x03);

    for(ucTemp = 0; ucTemp < ucHeight; ucTemp++)
    {
        ScalerOsdSramDataValue(ucRow + ucTemp, ucCol, ucLength, enumOsdBlankingType, _OSD_BYTE0);
        ScalerOsdSramDataValue(ucRow + ucTemp, ucCol, ucLength, (ucPixelLength & 0xFF), _OSD_BYTE1);
        ScalerOsdSramDataValue(ucRow + ucTemp, ucCol, ucLength, (ucBackgroundColor & 0x3F), _OSD_BYTE2);
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdBlankFont(ROW(0), COL(1), LENGTH(1), HEIGHT(1), VALUES(4), BGCOLOR(0), _OSD_BLINKING_EFFECT_DISABLE);
*/

