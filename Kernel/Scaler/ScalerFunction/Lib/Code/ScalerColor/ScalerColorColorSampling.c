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
// ID Code      : ScalerColorColorSampling.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerColorLibInternalInclude.h"

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
void ScalerColor422To444(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : 420To422 parameter setting for D1 source
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColor422To444(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420))
    {
        // Enable YUV 422 to 444 function
        ScalerSetBit(P31_40_YUV422_TO_444_PATH0, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
    }
    else
    {
        // Disable YUV 422 to 444 function
        ScalerSetBit(P31_40_YUV422_TO_444_PATH0, ~_BIT3, 0x00);
    }
}
