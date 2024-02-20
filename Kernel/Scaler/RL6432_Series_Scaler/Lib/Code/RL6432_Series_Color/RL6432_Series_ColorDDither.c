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
// ID Code      : RL6432_Series_ColorDDither.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DITHER_TABLE_LENGTH    (144)
#define _TEMPORAL_TABLE_LENGTH  (32)

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
void ScalerColorDDitherLoadDitherTable(BYTE code *pucDitherTable, BYTE ucBankAddress);
void ScalerColorDDitherLoadTempoTable(BYTE code *pucTempoTable, BYTE ucBankAddress);
void ScalerColorDDitherLoadSetting(DWORD ulSettingOption);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust D Dither Setting
// Input Value  :
//                pucDitherTable : Dither Table Pointer
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherLoadDitherTable(BYTE code *pucDitherTable, BYTE ucBankAddress)
{
    if(pucDitherTable != _NULL_POINTER)
    {
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0x80);
        ScalerBurstWrite(pucDitherTable, _DITHER_TABLE_LENGTH, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust D Dither Setting
// Input Value  :
//                pucTempoTable : Temporal Table Pointer
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherLoadTempoTable(BYTE code *pucTempoTable, BYTE ucBankAddress)
{
    if(pucTempoTable != _NULL_POINTER)
    {
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0xC0);
        ScalerBurstWrite(pucTempoTable, _TEMPORAL_TABLE_LENGTH, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust D Dither Common Setting
// Input Value  : D Dither Setting Option
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherLoadSetting(DWORD ulSettingOption)
{
    BYTE ucData = 0;
    ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1 | _BIT0), ulSettingOption & 0x0000003F);
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_00_D_DITHER_COMMON_SET0);
    ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, ((ulSettingOption & 0x00007F00) >> 8) | (ulSettingOption & 0x00000080));
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_02_D_DITHER_COMMON_SET2);
    ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, (ulSettingOption & 0x00FF0000) >> 16);
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_0D_D_DITHER_COMMON_CTRL2);
    ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, (ulSettingOption & 0xFF000000) >> 24);

    // reset frame counter
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_01_D_DITHER_COMMON_SET1);
    ucData = ScalerGetByte(P0_69_D_DITHER_DATA_ACCESS) | _BIT7;
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_01_D_DITHER_COMMON_SET1);
    ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, ucData);
}
