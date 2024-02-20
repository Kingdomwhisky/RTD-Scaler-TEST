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
// ID Code      : OsdRowHeight.c
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
void ScalerOsdRowHeight(BYTE ucRow, BYTE ucHeight, BYTE ucLength);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : ucRow -> ROW_MAPA(x), ROW_MAPB(x)
//                ucHeight -> 1 ~ 64
//                ucLength -> number of row to be changed
// Output Value :
//--------------------------------------------------
void ScalerOsdRowHeight(BYTE ucRow, BYTE ucHeight, BYTE ucLength)
{
    BYTE ucIdx = 0;

    if(ucHeight > 64)
    {
        ucHeight = 64;
    }

    ucHeight--;

    if(ScalerGetBit(P3A_18_FRAME_CTRL_18, _BIT3) == _BIT3) // OSD 2 font function
    {
        if(ucRow >= _OSD_MAP_B_ROW_OFFSET)
        {
            ScalerOsdSramAddressSet((ScalerGetByte(P3A_1A_FRAME_CTRL_1A) + (ucRow - _OSD_MAP_B_ROW_OFFSET)), _OSD_BYTE1);
        }
        else
        {
            ScalerOsdSramAddressSet((ScalerGetByte(P3A_19_FRAME_CTRL_19) + ucRow), _OSD_BYTE1);
        }
    }
    else
    {
        ScalerOsdSramAddressSet((0 + ucRow), _OSD_BYTE1);
    }

    for(ucIdx = 0; ucIdx < ucLength; ucIdx++)
    {
        ScalerOsdDataPort(ucHeight);
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdRowHeight(ROW_MAPA(0), HEIGHT(31), LENGTH(3));
*/

