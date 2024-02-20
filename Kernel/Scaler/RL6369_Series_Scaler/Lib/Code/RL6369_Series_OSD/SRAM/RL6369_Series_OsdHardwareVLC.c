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
// ID Code      : RL6369_Series_OsdHardwareVLC.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6369_Series_OSDLibInternalInclude.h"

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
void ScalerOsdHardwareVLC(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Osd Load Hardware VLC
// Input Value  : *pArray          -> VLC table
//                usVLCTableSize   -> Use VLC_TABLE_SIZE(VLC table)
//                ucBankNum        -> Bank number (GET_CURRENT_BANK_NUMBER())
//                usOffset         -> Font address
//                usFontTableStart -> Font base address
//                ucOsdRotateType  -> _OSD_ROTATE_DEGREE_0 or _OSD_ROTATE_DEGREE_90 or _OSD_ROTATE_DEGREE_270
// Output Value :
//--------------------------------------------------
void ScalerOsdHardwareVLC(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType)
{
    BYTE ucVlcType = 0;

    if(enumOsdRotateType == _OSD_ROTATE_DEGREE_90)
    {
        ucVlcType = _OSD_ROTATE_CW | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE | _OSD_ROTATE_ROTATION;
    }
    else if(enumOsdRotateType == _OSD_ROTATE_DEGREE_270)
    {
        ucVlcType = _OSD_ROTATE_CCW | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE | _OSD_ROTATE_ROTATION;
    }
    else
    {
        ucVlcType = _OSD_ROTATE_NO_SWAP;
    }

    // rotation
    ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT2 | _BIT0), ucVlcType);

    ScalerBurstWrite(pucArray, 8, ucBankNum, P3A_0F_FRAME_CTRL_0F, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);

    usOffset = usOffset * 9;
    usOffset += usFontTableStart;

    // osd compression enable
    ScalerSetBit(P3A_17_FRAME_CTRL_17, ~(_BIT1 | _BIT0), (_OSD_DECODE_COMPRESSED | _OSD_COMPRESSION_ENABLE));

    pucArray += 10;

    ScalerOsdSramAddressSet(usOffset, _OSD_BYTEALL);
    ScalerOsdBurstWriteDataPort(pucArray, usVLCTableSize, ucBankNum, _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_FLASH);

    // OSD HW needs time to process it and then write decompressed data into SRAM.
    // The value 1ms is enough at all.
    ScalerTimerDelayXms(2);

    // osd compression disable
    ScalerSetBit(P3A_17_FRAME_CTRL_17, ~(_BIT1 | _BIT0), (_OSD_DECODE_COMPRESSED | _OSD_COMPRESSION_DISABLE));

    if(enumOsdRotateType != _OSD_ROTATE_DEGREE_0)
    {
        ucVlcType = _OSD_ROTATE_ROTATION;
    }
    else
    {
        ucVlcType = _OSD_ROTATE_NORMAL;
    }

    ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT2 | _BIT0), ucVlcType);
}

