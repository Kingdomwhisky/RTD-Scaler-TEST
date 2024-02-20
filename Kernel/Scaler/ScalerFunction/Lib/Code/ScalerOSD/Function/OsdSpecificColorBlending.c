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
// ID Code      : OsdSpecificColorBlending.c
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
void ScalerOsdSpecificColorBlending(bit bEnable, BYTE ucIndex);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set specific color blending
// Input Value  :     bEnable -> _ENABLE or _DISABLE
//                    ucIndex -> BlendingColor LUT index (0~63)
// Output Value :
//--------------------------------------------------
void ScalerOsdSpecificColorBlending(bit bEnable, BYTE ucIndex)
{
    // Set Match blending type 2 color bit[5:0]
    ScalerSetBit(P3A_08_FRAME_CTRL_08, ~(_BIT4), (_BIT4));

    // Set Specific Color Blending (blending Type 2) Enable/Disable
    ScalerSetBit(P3A_09_FRAME_CTRL_09, ~_BIT7, ((BYTE)bEnable << 7));

    // Set Blending Color from 64-color LUT [5:0] (blending Type 2)
    ScalerSetBit(P3A_08_FRAME_CTRL_08, ~(_BIT3 | _BIT2), ((ucIndex & (_BIT5 | _BIT4)) >> 2));
    ScalerSetBit(P3A_09_FRAME_CTRL_09, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIndex & 0x0F));
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdSpecificColorBlending(_ENABLE,15);
*/
