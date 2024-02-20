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
// ID Code      : RL6463_Series_ColorUltraVividEnable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6463_Series_ColorLibInternalInclude.h"

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
void ScalerColorUltraVividEnable(EnumFunctionOnOFF enumFunctionOnOff, EnumDBApply enumDBApply);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable / Disable / Clock Gated UltraVivid Function
// Input Value  : enumFunctionOnOff -> _ENABLE or _DISABLE or _CLCOK_GATED
// Output Value : None
//--------------------------------------------------
void ScalerColorUltraVividEnable(EnumFunctionOnOFF enumFunctionOnOff, EnumDBApply enumDBApply)
{
    if(enumFunctionOnOff == _FUNCTION_ON)
    {
        // Enable UltraVivid Function
        ScalerSetBit(P14_C0_LSR_CTRL, ~_BIT7, _BIT7);
        // Wait for Double Buffer
        ScalerGlobalIDDomainDBApply(enumDBApply);
    }
    else
    {
        // Disable UltraVivid Function
        ScalerSetBit(P14_C0_LSR_CTRL, ~_BIT7, 0x00);
        // Wait for Double Buffer
        ScalerGlobalIDDomainDBApply(enumDBApply);
    }
}
