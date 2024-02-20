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
// ID Code      : OsdRoundedWindowPattern8x8.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerOSDLibInternalInclude.h"

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
void ScalerOsdRoundedWindowPattern8x8(BYTE ucIdx, BYTE ucType);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set Window Rounded Pattern 8x8
// Input Value  : ucIdx -> Pattern Index 0~7
// Input Value  : ucType -> Pattern Type
// Output Value :
//--------------------------------------------------
void ScalerOsdRoundedWindowPattern8x8(BYTE ucIdx, BYTE ucType)
{
    WORD usAddr = P3A_60_FRAME_CTRL_60;

    usAddr += (ucIdx / 2);

    if((ucIdx % 2) == 0)
    {
        ScalerSetBit(usAddr, ~(_BIT2 | _BIT1 | _BIT0), (ucType & 0x07));
    }
    else
    {
        ScalerSetBit(usAddr, ~(_BIT6 | _BIT5 | _BIT4), ((ucType & 0x07) << 4));
    }
}
