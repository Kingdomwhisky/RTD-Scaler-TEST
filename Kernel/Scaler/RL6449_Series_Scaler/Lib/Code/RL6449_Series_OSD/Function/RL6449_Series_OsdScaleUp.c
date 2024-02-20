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
// ID Code      : RL6449_Series_OsdScaleUp.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6449_Series_OSDLibInternalInclude.h"

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
void ScalerOsdScaleUpBoundaryCodition(EnumOsdScaleUpBoundaryType enumBoundary);
void ScalerOsdScaleUpVerInitialValue(BYTE ucVerInitialValue);
void ScalerOsdScaleUpHorInitialValue(BYTE ucHorInitialValue);
void ScalerOsdScaleUpVerFactor(BYTE ucVerFactor);
void ScalerOsdScaleUpHorFactor(BYTE ucHorFactor);
void ScalerOsdScaleUpVerSize(WORD usVStart, WORD usVHeight);
void ScalerOsdScaleUpHorSize(WORD usHStart, WORD usHWidth);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : OSD Scale Up Boundary Condition
// Input Value  : enumRatio
// Output Value :
//--------------------------------------------------
void ScalerOsdScaleUpBoundaryCodition(EnumOsdScaleUpBoundaryType enumBoundary)
{
    ScalerSetBit(P3A_C0_OSD_SU_CRTL, ~(_BIT1 | _BIT0), enumBoundary);
}

//--------------------------------------------------
// Description  : OSD Scale Up V Initial Value
// Input Value  : ucVerInitialValue
// Output Value :
//--------------------------------------------------
void ScalerOsdScaleUpVerInitialValue(BYTE ucVerInitialValue)
{
    ScalerSetBit(P3A_C1_OSD_SU_INITIAL_PHASE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucVerInitialValue);
}
//--------------------------------------------------
// Description  : OSD Scale Up H Initial Value
// Input Value  : ucHorInitialValue
// Output Value :
//--------------------------------------------------
void ScalerOsdScaleUpHorInitialValue(BYTE ucHorInitialValue)
{
    ScalerSetBit(P3A_C1_OSD_SU_INITIAL_PHASE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucHorInitialValue);
}

//--------------------------------------------------
// Description  : OSD Scale Up V Ratio
// Input Value  : ucVerFactor : input/output * 2^6
// Output Value :
//--------------------------------------------------
void ScalerOsdScaleUpVerFactor(BYTE ucVerFactor)
{
    ScalerSetBit(P3A_C2_OSD_VER_FACTOR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucVerFactor);
}

//--------------------------------------------------
// Description  : OSD Scale Up H Ratio
// Input Value  : ucHorFactor : input/output * 2^6
// Output Value :
//--------------------------------------------------
void ScalerOsdScaleUpHorFactor(BYTE ucHorFactor)
{
    ScalerSetBit(P3A_C3_OSD_HOR_FACTOR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucHorFactor);
}

//--------------------------------------------------
// Description  : OSD Scale Up V Start/Height
// Input Value  : usVStart
// Input Value  : usVHeight
// Output Value :
//--------------------------------------------------
void ScalerOsdScaleUpVerSize(WORD usVStart, WORD usVHeight)
{
    WORD usBGVStart = 0;

    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H, 2, &pData[0], _AUTOINC);
    usBGVStart = ((pData[0] & 0x1F) << 8) | (pData[1]);

    usVStart = usVStart + (((usBGVStart % 2) == 0) ? (usBGVStart - 1) : (usBGVStart - 2));
    ScalerSetBit(P3A_C4_OSD_SU_VER_ST_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usVStart) & 0x0F);
    ScalerSetByte(P3A_C5_OSD_SU_VER_ST_L, LOBYTE(usVStart));

    ScalerSetBit(P3A_C8_OSD_SU_VER_SIZE_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usVHeight) & 0x0F);
    ScalerSetByte(P3A_C9_OSD_SU_VER_SIZE_L, LOBYTE(usVHeight));
}

//--------------------------------------------------
// Description  : OSD Scale Up H Start/Height
// Input Value  : usHStart
// Input Value  : usHWidth
// Output Value :
//--------------------------------------------------
void ScalerOsdScaleUpHorSize(WORD usHStart, WORD usHWidth)
{
    WORD usBGHStart = 0;

    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H, 2, &pData[0], _AUTOINC);
    usBGHStart = ((pData[0] & 0x1F) << 8) | (pData[1]);

    ScalerSetByte(0x06, usBGHStart);
    usHStart = usHStart + (usBGHStart / 2 - 7);
    ScalerSetBit(P3A_C6_OSD_SU_HOR_ST_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usHStart) & 0x0F);
    ScalerSetByte(P3A_C7_OSD_SU_HOR_ST_L, LOBYTE(usHStart));

    ScalerSetBit(P3A_CA_OSD_SU_HOR_SIZE_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usHWidth) & 0x0F);
    ScalerSetByte(P3A_CB_OSD_SU_HOR_SIZE_L, LOBYTE(usHWidth));
}



