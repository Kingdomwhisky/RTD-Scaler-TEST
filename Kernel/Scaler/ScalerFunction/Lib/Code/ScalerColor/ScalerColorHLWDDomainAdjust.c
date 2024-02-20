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
// ID Code      : ScalerColorHLWDDomainAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerColorLibInternalInclude.h"

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
void ScalerColorHLWDDomainAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust highlight window region
// Input Value  : usHPos, usHWidth, usVPos, usVHeight
// Output Value : None
//--------------------------------------------------
void ScalerColorHLWDDomainAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight)
{
    if((usHWidth == 0) || (usVHeight == 0))
    {
        return;
    }

    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_00_HLW_HOR_START_H, (BYTE)((usHPos >> 8) & 0x1F));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_01_HLW_HOR_START_L, (BYTE)(usHPos & 0xFF));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_02_HLW_HOR_END_H, (BYTE)(((usHPos + usHWidth) >> 8) & 0x1F));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_03_HLW_HOR_END_L, (BYTE)((usHPos + usHWidth) & 0xFF));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_04_HLW_VER_START_H, (BYTE)((usVPos >> 8) & 0x1F));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_05_HLW_VER_START_L, (BYTE)(usVPos & 0xFF));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_06_HLW_VER_END_H, (BYTE)(((usVPos + usVHeight) >> 8) & 0x1F));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_07_HLW_VER_END_L, (BYTE)((usVPos + usVHeight) & 0xFF));
}
