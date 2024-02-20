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
// ID Code      : OsdAddress90_91_92.c
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
void ScalerOsdAddrMsb(BYTE ucValue);
void ScalerOsdAddrLsb(BYTE ucValue);
void ScalerOsdDataPort(BYTE ucValue);
void ScalerOsdAddrSet(EnumOsdAddrIndicateType enumAddrIndicator, EnumOsdWriteType enumByteSel, WORD usAddress, EnumOsdDBufType enumDbufEnable);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : OSD Addr Msb 0x90
// Input Value  : ucValue -> 0x90 data
// Output Value :
//--------------------------------------------------
void ScalerOsdAddrMsb(BYTE ucValue)
{
    ScalerSetBit(P0_90_OSD_ADR_PORT_MSB, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ucValue & 0x7F));
}

//--------------------------------------------------
// Description  : OSD Addr Lsb 0x91
// Input Value  : ucValue -> 0x91 data
// Output Value :
//--------------------------------------------------
void ScalerOsdAddrLsb(BYTE ucValue)
{
    ScalerSetByte(P0_91_OSD_ADR_PORT_LSB, ucValue);
}

//--------------------------------------------------
// Description  : OSD Data Port 0x92
// Input Value  : ucValue -> 0x92 data
// Output Value :
//--------------------------------------------------
void ScalerOsdDataPort(BYTE ucValue)
{
    ScalerSetByte(P0_92_OSD_DATA_PORT, ucValue);
}

//--------------------------------------------------
// Description  : OSD Addr: 0x90[6:0], 0x91[7:0]
// Input Value  : ucAddrIndicator -> _OSD_WIN_CONTROL or _OSD_SRAM
//                ucByteSel       -> _OSD_BYTE0       or _OSD_BYTE1       or _OSD_BYTE2       or
//                                   _OSD_BYTE0_BYTE1 or _OSD_BYTE0_BYTE2 or _OSD_BYTE1_BYTE2 or _OSD_BYTEALL
//                usAddress       -> SRAM address
//                ucDbufEnable    -> _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerOsdAddrSet(EnumOsdAddrIndicateType enumAddrIndicator, EnumOsdWriteType enumByteSel, WORD usAddress, EnumOsdDBufType enumDbufEnable)
{
    enumDbufEnable = enumDbufEnable;

    // Set Address Indicator: 00: Window control registers, 10: Font Select and font map SRAM
    ScalerSetBit(P0_94_OSD_WRITE_OPTION, ~(_BIT3 | _BIT2), enumAddrIndicator);

    // Select Which Byte to Write:  001: Byte0, 010: Byte1, 100: Byte2, 011: Byte0 & Byte1, 101: Byte0 & Byte2, 110: Byte1 & Byte2,111: All
    ScalerSetBit(P0_94_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5), enumByteSel);

    // Set Address
    ScalerOsdAddrMsb(HIBYTE(usAddress));
    ScalerOsdAddrLsb(LOBYTE(usAddress));
}

