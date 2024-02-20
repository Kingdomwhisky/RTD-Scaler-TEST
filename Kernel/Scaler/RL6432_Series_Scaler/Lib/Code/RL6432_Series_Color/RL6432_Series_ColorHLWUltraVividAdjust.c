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
// ID Code      : RL6432_Series_ColorHLWUltraVividAdjust.c
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
void ScalerColorHLWUltraVividAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set ultravivid Highlight Window
// Input Value  : Highlight Window Active Region
//                EnumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorHLWUltraVividAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply)
{
    switch(enumHLWActive)
    {
        case _HLW_FULL_WINDOW:
            ScalerSetBit(P11_B9_SCALER_LSR_HLW, ~(_BIT7 | _BIT6), 0x00);
            ScalerSetBit(P11_DC_I_DLTI_HLW_CTRL_M1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0D_HLW_CONTROL1, ~(_BIT1 | _BIT0), (enumHLWActive & 0x03));
            break;

        case _HLW_INSIDE_WINDOW:
            ScalerSetBit(P11_B9_SCALER_LSR_HLW, ~(_BIT7 | _BIT6), _BIT7);
            ScalerSetBit(P11_DC_I_DLTI_HLW_CTRL_M1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0D_HLW_CONTROL1, ~(_BIT1 | _BIT0), (enumHLWActive & 0x03));
            break;

        case _HLW_OUTSIDE_WINDOW:
            ScalerSetBit(P11_B9_SCALER_LSR_HLW, ~(_BIT7 | _BIT6), _BIT7 | _BIT6);
            ScalerSetBit(P11_DC_I_DLTI_HLW_CTRL_M1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0D_HLW_CONTROL1, ~(_BIT1 | _BIT0), (enumHLWActive & 0x03));
            break;

        default:
            break;
    }

    if(GET_INTERLACED_MODE() == _TRUE)
    {
        ScalerGlobalIDomainDBApply(enumDBApply);
        ScalerGlobalDDomainDBApply(enumDBApply);
    }
    else
    {
        ScalerGlobalIDDomainDBApply(enumDBApply);
    }
}

