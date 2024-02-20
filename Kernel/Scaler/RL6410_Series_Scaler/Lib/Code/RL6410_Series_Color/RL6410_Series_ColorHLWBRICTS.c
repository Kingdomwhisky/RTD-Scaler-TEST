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
// ID Code      : RL6410_Series_ColorHLWBRICTS.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_ColorLibInternalInclude.h"

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
void ScalerColorHLWBRICTSAdjust(EnumBriConHLWType enumHLWActive, EnumDBApply enumDBApply);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable/Disable Contrast function
// Input Value  : enumHLWActive: HLW type
//                EnumDBApply
// Output Value : None
//--------------------------------------------------

void ScalerColorHLWBRICTSAdjust(EnumBriConHLWType enumHLWActive, EnumDBApply enumDBApply)
{
    if(enumHLWActive == _BRI_CON_B_ON_INSIDE_WINDOW)
    {
        ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0E_HLW_CONTROL0, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_11_HLW_SETSEL0, ~(_BIT3 | _BIT2), _BIT3);
    }
    else if(enumHLWActive == _BRI_CON_A_ON_HLW_OUTSIDE_WINDOW)
    {
        ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0E_HLW_CONTROL0, ~(_BIT7 | _BIT6), _BIT7);
        ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_11_HLW_SETSEL0, ~(_BIT3 | _BIT2), _BIT3);
    }
    else if(enumHLWActive == _BRI_CON_B_ON_INSIDE_A_ON_HLW_OUTSIDE_WINDOW)
    {
        ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0E_HLW_CONTROL0, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_11_HLW_SETSEL0, ~(_BIT3 | _BIT2), _BIT3);
    }
    else
    {
        ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0E_HLW_CONTROL0, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_11_HLW_SETSEL0, ~(_BIT3 | _BIT2), 0x00);
    }

    ScalerGlobalDDomainDBApply(enumDBApply);
}

