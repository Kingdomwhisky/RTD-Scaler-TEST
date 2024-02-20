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
// ID Code      : OsdCharCommandAllByteSeries.c
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
void ScalerOsdCharCommandAllByteSeries(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2, WORD usLength);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set OSD Char Command All Byte Series
// Input Value  : usCharAddr -> SRAM address
//                ucByte0      -> Byte0 data
//                ucByte1      -> Byte1 data
//                ucByte2      -> Byte2 data
//                usLength     -> Length
// Output Value :
//--------------------------------------------------
void ScalerOsdCharCommandAllByteSeries(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2, WORD usLength)
{
    ScalerOsdSramAddressSet(usCharAddr, _OSD_BYTEALL);

    do
    {
        ScalerSetByte(P0_92_OSD_DATA_PORT, ucByte0);
        ScalerSetByte(P0_92_OSD_DATA_PORT, ucByte1);
        ScalerSetByte(P0_92_OSD_DATA_PORT, ucByte2);
    }
    while(--usLength);
}
