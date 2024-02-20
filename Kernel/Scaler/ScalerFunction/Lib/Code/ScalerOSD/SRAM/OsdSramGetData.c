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
// ID Code      : OsdSramGetData.c
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
void ScalerOsdSramGetData(EnumOsdWriteType enumOsdWriteType, WORD usSramAddress, BYTE ucLength, BYTE *pucData);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get SRAM address value
// Input Value  : enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
//                ucLength -> Length
// Output Value : pucData -> Data
//--------------------------------------------------
void ScalerOsdSramGetData(EnumOsdWriteType enumOsdWriteType, WORD usSramAddress, BYTE ucLength, BYTE *pucData)
{
    BYTE ucLenIdx = 0;
    BYTE ucRdIdx = 0;
    BYTE ucByteSel = 0;
    bit bOSDEnableBackup = 0;

    bOSDEnableBackup = ScalerGetBit(P3A_02_FRAME_CTRL_02, _BIT0);

    ScalerOsdCircuitActivated(_DISABLE);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    ScalerSetBit(P3A_33_FRAME_CTRL_33, ~_BIT4, _BIT4);

    ucByteSel = ((enumOsdWriteType == _OSD_BYTEALL) ? (3) : ((enumOsdWriteType == _OSD_BYTE0_BYTE1) ? 2 : ((enumOsdWriteType == _OSD_BYTE0_BYTE2) ? 2 : ((enumOsdWriteType == _OSD_BYTE1_BYTE2) ? 2 : 1))));

    for(ucLenIdx = 0; ucLenIdx < ucLength; ucLenIdx++)
    {
        ScalerOsdSramAddressSet(usSramAddress + ucLenIdx, enumOsdWriteType);

        for(ucRdIdx = 0; ucRdIdx < ucByteSel; ucRdIdx++)
        {
            pucData[(ucLenIdx * ucByteSel) + ucRdIdx] = ScalerGetByte(P0_92_OSD_DATA_PORT);
        }

        for(ucRdIdx = 0; ucRdIdx < ucByteSel; ucRdIdx++)
        {
            pucData[(ucLenIdx * ucByteSel) + ucRdIdx] = ScalerGetByte(P0_92_OSD_DATA_PORT);
        }
    }

    ScalerSetBit(P3A_33_FRAME_CTRL_33, ~_BIT4, 0x00);
    ScalerOsdCircuitActivated(bOSDEnableBackup);
}


