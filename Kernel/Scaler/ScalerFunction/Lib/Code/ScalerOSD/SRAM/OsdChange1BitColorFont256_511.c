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
// ID Code      : OsdChange1BitColorFont256_511.c
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
void ScalerOsdChange1BitColorFont256_511(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucForegroundColor, BYTE ucBackgroundColor);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : ucRow. ucCol. ucLength. ucHeight.     -> Just that !!
//                ucForegroundColor. ucBackgroundColor  -> Color number
// Output Value :
//--------------------------------------------------
void ScalerOsdChange1BitColorFont256_511(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucForegroundColor, BYTE ucBackgroundColor)
{
    BYTE ucTemp = 0;
    BYTE ucColorByte0 = (_BIT6 | _BIT5);
    bit bOSDOn = _OFF;

    // Get OSD Status for Write-Protection Function setting OSD circuit enable.
    bOSDOn = ScalerGetBit(P3A_02_FRAME_CTRL_02, _BIT0);

    for(ucTemp = 0; ucTemp < ucHeight; ucTemp++)
    {
        ScalerOsdSramDataValue(ucRow + ucTemp, ucCol, ucLength, ((ucForegroundColor << 4) | ucBackgroundColor), _OSD_BYTE2);
    }

    ScalerOsdWriteProtection(_ENABLE, _OSD_BYTE0, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    for(ucTemp = 0; ucTemp < ucHeight; ucTemp++)
    {
        ScalerOsdSramDataValue(ucRow + ucTemp, ucCol, ucLength, ucColorByte0, _OSD_BYTE0);
    }

    ScalerOsdWriteProtection(_DISABLE, _OSD_BYTE0, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Recovery OSD Status
    if(bOSDOn == _OFF)
    {
        ScalerOsdCircuitActivated(bOSDOn);
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdChange1BitColorFont256_511(ROW(0), COL(0), LENGTH(1), HEIGHT(1), FGCOLOR(3), BGCOLOR(4));
*/

