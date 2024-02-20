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
// ID Code      : RL6492_Series_ColorRingingFilterAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6492_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _RINGING_FILTER_THRESHOLD           30
#define _RINGING_FILTER_THD_RANGE           4
#define _RINGING_JUMP_JUDGEMENT_EN          _DISABLE
#define _RINGING_JUMP_DIFF_THD_UB           1  // reg value
#define _RINGING_JUMP_DIFF_THD_LB           1  // reg value
#define _RINGING_FILTER_DELTA               5

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
void ScalerColorRingingFilterAdjust(BYTE *pucOffsetCoef);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust Ringing Filter
// Input Value  : Offset Coef
// Output Value : None
//--------------------------------------------------
void ScalerColorRingingFilterAdjust(BYTE *pucOffsetCoef)
{
    BYTE ucTHD = 0;
    BYTE ucRFEn = 0;

    if(*pucOffsetCoef > 0)
    {
        ucTHD = (WORD)_RINGING_FILTER_DELTA * 128 / (*pucOffsetCoef);
    }
    else
    {
        ucTHD = 255;
    }

    if(ucTHD < _RINGING_FILTER_THRESHOLD)
    {
        ucTHD = _RINGING_FILTER_THRESHOLD;
    }
    else if(ucTHD > 255 - (1 << _RINGING_FILTER_THD_RANGE))
    {
        ucTHD = 255 - (1 << _RINGING_FILTER_THD_RANGE);
    }

    ucRFEn = 1;

    ScalerSetByte(P25_A1_RFILTER_THD, ucTHD);
    ScalerSetByte(P25_A2_RFILTER_THD_RNG_EXP, _RINGING_FILTER_THD_RANGE);
    ScalerSetByte(P25_A3_RFILTER_OFS_COEF, (*pucOffsetCoef));
    ScalerSetByte(P25_A5_RFILTER_DIFF_THD_UB, _RINGING_JUMP_DIFF_THD_UB);
    ScalerSetByte(P25_A6_RFILTER_DIFF_THD_LB, _RINGING_JUMP_DIFF_THD_LB);
    ScalerSetBit(P25_A0_RFILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5), ((ucRFEn << 7) | _BIT6 | (_RINGING_JUMP_JUDGEMENT_EN << 5)));
}
