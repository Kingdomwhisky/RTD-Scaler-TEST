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
// ID Code      : OsdFrameControlByteGet.c
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
BYTE ScalerOsdFrameControlByteGet(WORD usAddr, EnumOsdWriteType enumOsdWriteType);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get OSD Frame Control Byte
// Input Value  : usAddr           -> WindowControl address
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
// Output Value : FrameControl Value
//--------------------------------------------------
BYTE ScalerOsdFrameControlByteGet(WORD usAddr, EnumOsdWriteType enumOsdWriteType)
{
    ScalerSetBit(P0_94_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5), enumOsdWriteType);
    ScalerSetBit(P0_94_OSD_WRITE_OPTION, ~(_BIT3 | _BIT2), _OSD_WIN_CONTROL);

    ScalerSetByte(P0_90_OSD_ADR_PORT_MSB, (HIBYTE(usAddr) & 0x7F));
    ScalerSetByte(P0_91_OSD_ADR_PORT_LSB, LOBYTE(usAddr));

    return ScalerGetByte(P0_92_OSD_DATA_PORT);
}
