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
// ID Code      : OsdWriteByte.c
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
void ScalerOsdWriteByte(BYTE ucIndicateAndWriteByte, EnumOsdDBufType enumDBuf, WORD usAddr, BYTE ucData);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set OSD Write Byte
// Input Value  : ucIndicateAndWriteByte -> (_OSD_WIN_CONTROL or _OSD_SRAM)  |
//                                          (_OSD_BYTE0       or _OSD_BYTE1       or _OSD_BYTE2       or
//                                           _OSD_BYTE0_BYTE1 or _OSD_BYTE0_BYTE2 or _OSD_BYTE1_BYTE2 or _OSD_BYTEALL)
//                usAddr                 -> SRAM address
//                ucData                 -> ucIndicate's Data
// Output Value :
//--------------------------------------------------
void ScalerOsdWriteByte(BYTE ucIndicateAndWriteByte, EnumOsdDBufType enumDBuf, WORD usAddr, BYTE ucData)
{
    enumDBuf = enumDBuf;

    // Set Address Indicator: 00: Window control registers, 10: Font Select and font map SRAM
    ScalerSetBit(P0_94_OSD_WRITE_OPTION, ~(_BIT3 | _BIT2), (ucIndicateAndWriteByte & (_BIT3 | _BIT2)));

    // Select Which Byte to Write:  001: Byte0, 010: Byte1, 100: Byte2, 011: Byte0 & Byte1, 101: Byte0 & Byte2, 110: Byte1 & Byte2,111: All
    ScalerSetBit(P0_94_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5), (ucIndicateAndWriteByte & (_BIT7 | _BIT6 | _BIT5)));

    // Set Address
    ScalerSetBit(P0_90_OSD_ADR_PORT_MSB, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usAddr) & 0x7F));
    ScalerSetByte(P0_91_OSD_ADR_PORT_LSB, LOBYTE(usAddr));

    // Set Data
    ScalerSetByte(P0_92_OSD_DATA_PORT, ucData);
}
