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
// ID Code      : OsdChange2BitColor.c
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
void ScalerOsdChange2BitColor(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : ucRow. ucCol. ucLength. ucHeight.       -> Just that !!
//                ucColor0. ucColor1. ucColor2. ucColor3  -> Color number
// Output Value :
//--------------------------------------------------
void ScalerOsdChange2BitColor(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3)
{
    BYTE ucTemp = 0;
    BYTE ucByte0 = _BIT7;
    BYTE ucByte2 = 0;

    if((ucColor0 > 7) && (ucColor3 > 7))
    {
        ucByte0 |= _BIT5;
        ucColor0 -= 8;
        ucColor3 -= 8;
    }

    if((ucColor1 > 7) && (ucColor2 > 7))
    {
        ucByte0 |= _BIT4;
        ucColor1 -= 8;
        ucColor2 -= 8;
    }

    ucByte0 = ucByte0 | ((ucColor3 & 0x07) << 1) | ((ucColor0 & _BIT2) >> 2);
    ucByte2 = ((ucColor0 & 0x03) << 6) | ((ucColor2 & 0x07) << 3) | (ucColor1 & 0x07);

    for(ucTemp = 0; ucTemp < ucHeight; ucTemp++)
    {
        ScalerOsdSramDataValue2Byte(ucRow + ucTemp, ucCol, ucLength, ucByte0, ucByte2, _OSD_BYTE0_BYTE2);
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdChange2BitColor(ROW(0), COL(0), LENGTH(1), HEIGHT(1), COLOR00(0), COLOR01(1), COLOR10(2), COLOR11(3));
*/

