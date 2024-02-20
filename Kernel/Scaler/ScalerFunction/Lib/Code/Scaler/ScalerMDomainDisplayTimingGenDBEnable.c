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
// ID Code      : ScalerMDomainDisplayTimingGenDBEnable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerLibInternalInclude.h"

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
void ScalerMDomainDisplayTimingGenDBEnable(bit bEnable);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set Display Timing Gen Double Buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMDomainDisplayTimingGenDBEnable(bit bEnable)
{
    // Set Display Timing Gen Double Buffer
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~(_BIT7 | _BIT6), _BIT7);
    }
    else
    {
        ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~(_BIT7 | _BIT6), 0x00);
    }
}

