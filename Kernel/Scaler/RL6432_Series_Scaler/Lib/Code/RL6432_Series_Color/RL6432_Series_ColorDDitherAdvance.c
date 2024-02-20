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
// ID Code      : RL6432_Series_ColorDDitherAdvance.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DDITHER_REALIGN_TABLE_LENGTH           (48)
#define _DDITHER_REALIGN_TEMPO_TABLE_LENGTH     (8)
#define _DDITHER_LSB_TABLE_LENGTH               (16)
#define _DDITHER_ADVANCESETTING_TABLE_LENGTH    (45)


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
void ScalerColorDDitherAdvanceSettingAdjust(BYTE code *pucReAlignTable, BYTE code *pucReAlignTempoTable, BYTE code *pucLsbTable, BYTE code *pucAdvanceSettingTable, BYTE ucBankAddress);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust Advance Setting
// Input Value  :
//                pucReAlignTable : ReAlign Table Pointer
//                pucReAlignTempoTable : ReAlign Temporal Table Pointer
//                pucLsbTable : LSB Judge Table Pointer
//                pucAdvanceSettingTable : Advance Setting Table Pointer
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherAdvanceSettingAdjust(BYTE code *pucReAlignTable, BYTE code *pucReAlignTempoTable, BYTE code *pucLsbTable, BYTE code *pucAdvanceSettingTable, BYTE ucBankAddress)
{
    BYTE ucData = 0;

    ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6), 0x00);

    if(pucReAlignTable != _NULL_POINTER)
    {
        ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_80_D_DITHER_REALIGN_SET_R0);
        ScalerBurstWrite(pucReAlignTable, _DDITHER_REALIGN_TABLE_LENGTH, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }

    if(pucReAlignTempoTable != _NULL_POINTER)
    {
        ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_B0_D_DITHER_REALIGN_OFFSET0);
        ScalerBurstWrite(pucReAlignTempoTable, _DDITHER_REALIGN_TEMPO_TABLE_LENGTH, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }

    if(pucLsbTable != _NULL_POINTER)
    {
        ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_C0_D_DITHER_LSB_TABLE0);
        ScalerBurstWrite(pucLsbTable, _DDITHER_LSB_TABLE_LENGTH, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }

    if(pucAdvanceSettingTable != _NULL_POINTER)
    {
        ucData = ScalerGetByte(P0_6A_D_DITHER_COMMON_CTRL1) & _BIT5;
        ScalerBurstWrite(pucAdvanceSettingTable, 1, ucBankAddress, P0_6A_D_DITHER_COMMON_CTRL1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~(_BIT7 | _BIT6 | _BIT5), ucData);

        ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_00_D_DITHER_COMMON_SET0);
        ScalerBurstWrite(pucAdvanceSettingTable + 1, _DDITHER_ADVANCESETTING_TABLE_LENGTH - 1, ucBankAddress, P0_69_D_DITHER_DATA_ACCESS, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }

    // reset frame counter
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_01_D_DITHER_COMMON_SET1);
    ucData = ScalerGetByte(P0_69_D_DITHER_DATA_ACCESS) | _BIT7;
    ScalerSetByte(P0_6B_D_DITHER_REGISTER_ADDR, _P0_69_PT_01_D_DITHER_COMMON_SET1);
    ScalerSetByte(P0_69_D_DITHER_DATA_ACCESS, ucData);
}
