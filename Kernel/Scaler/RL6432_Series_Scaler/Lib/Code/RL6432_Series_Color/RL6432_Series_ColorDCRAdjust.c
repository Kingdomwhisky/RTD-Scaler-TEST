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
// ID Code      : RL6432_Series_ColorDCRAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_ColorLibInternalInclude.h"

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
void ScalerColorDCRAdjust(WORD usThreshold1, WORD usThreshold2, EnumDCRMeasureSel enumDCRMeasureSel);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set DCR TH1 & TH2
// Input Value  : TH1 & TH2, EnumDCRMeasureSel, bDCRSource
// Output Value : None
//--------------------------------------------------
void ScalerColorDCRAdjust(WORD usThreshold1, WORD usThreshold2, EnumDCRMeasureSel enumDCRMeasureSel)
{
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_00_DCR_THESHOLD1_1 << 2) | _BIT0);
    ScalerSetByte(P7_D9_DCR_DATA_PORT, usThreshold1 >> 2);
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_01_DCR_THESHOLD2_1 << 2) | _BIT0);
    ScalerSetByte(P7_D9_DCR_DATA_PORT, usThreshold2 >> 2);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_38_DCR_THESHOLD1_0 << 2) | _BIT0);
    ScalerSetByte(P7_D9_DCR_DATA_PORT, (usThreshold1 & (_BIT1 | _BIT0)) << 6);
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_39_DCR_THESHOLD2_0 << 2) | _BIT0);
    ScalerSetByte(P7_D9_DCR_DATA_PORT, (usThreshold2 & (_BIT1 | _BIT0)) << 6);

    ScalerSetBit(P7_DA_DCR_CTRL, ~(_BIT3 | _BIT2 | _BIT1), (enumDCRMeasureSel << 1));
}

