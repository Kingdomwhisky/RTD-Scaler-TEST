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
// ID Code      : ScalerColorIDither.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerColorLibInternalInclude.h"


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DITHER_TABLE_LENGTH    (24)
#define _TEMPORAL_TABLE_LENGTH  (4)

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
void ScalerColorIDitherLoadDitherTable(BYTE code *pucDitherTable, BYTE ucBankAddress);
void ScalerColorIDitherLoadSeqTable(BYTE code *pucSeqTable, BYTE ucSeqLength, BYTE ucBankAddress);
void ScalerColorIDitherLoadTemporalTable(BYTE code *pucTempoTable, BYTE ucBankAddress);
void ScalerColorIDitherLoadSetting(WORD usAdjustOption);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Adjust IDither Setting
// Input Value  :
//                pucDitherTable : Dither Table Pointer
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherLoadDitherTable(BYTE code *pucDitherTable, BYTE ucBankAddress)
{
    if(pucDitherTable != _NULL_POINTER)
    {
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~(_BIT7 | _BIT6), 0x80);
        ScalerBurstWrite(pucDitherTable, _DITHER_TABLE_LENGTH, ucBankAddress, P0_88_I_DITHER_DATA_ACCESS_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust IDither Setting
// Input Value  :
//                pucDitherTable : Seq Table Pointer.
//                ucSeqLength : table len
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherLoadSeqTable(BYTE code *pucSeqTable, BYTE ucSeqLength, BYTE ucBankAddress)
{
    if(pucSeqTable != _NULL_POINTER)
    {
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~(_BIT7 | _BIT6), 0x40);
        ScalerBurstWrite(pucSeqTable, ucSeqLength, ucBankAddress, P0_88_I_DITHER_DATA_ACCESS_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust IDither Setting
// Input Value  :
//                pucDitherTable : Temporal Table Pointer
//              ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherLoadTemporalTable(BYTE code *pucTempoTable, BYTE ucBankAddress)
{
    if(pucTempoTable != _NULL_POINTER)
    {
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~(_BIT7 | _BIT6), 0xC0);
        ScalerBurstWrite(pucTempoTable, _TEMPORAL_TABLE_LENGTH, ucBankAddress, P0_88_I_DITHER_DATA_ACCESS_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust IDither Setting
// Input Value  : usAdjustOption->Adjust setting
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherLoadSetting(WORD usAdjustOption)
{
    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), usAdjustOption & 0x001F);
    ScalerSetBit(P0_8A_I_DITHER_COMMON_CTRL2_SETA, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (usAdjustOption & 0x7E00) >> 8);

#if(_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT)
    ScalerSetBit(P0_20_M1_DUMMY2, ~(_BIT7), (usAdjustOption & 0x0080));
#endif
}

