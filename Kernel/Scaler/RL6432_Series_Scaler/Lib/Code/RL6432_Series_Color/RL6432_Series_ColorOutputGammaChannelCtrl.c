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
// ID Code      : RL6432_Series_ColorOutputGammaChannelCtrl.c
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
void ScalerColorOutputGammaChannelCtrl(BYTE ucColorChannel, WORD usOffset, bit bLocation);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Switch Gamma Channel
// Input Value  : ucColorChannel: 0- Red, 1- Green, 2- Blue;
//                ucOffset: Offset
//                bLocation: 0-Write to SDRAM, 1- Write to LATCH
// Output Value : None
//--------------------------------------------------
void ScalerColorOutputGammaChannelCtrl(BYTE ucColorChannel, WORD usOffset, bit bLocation)
{
    // Select Channel
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~(_BIT7 | _BIT5 | _BIT4 | _BIT2), ((ucColorChannel << 4) | ((BYTE)bLocation << 2)));

    // Specify address
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT3, _BIT3);
    ScalerSetByte(P0_66_GAMMA_PORT_SETA, HIBYTE(usOffset));
    ScalerSetByte(P0_66_GAMMA_PORT_SETA, LOBYTE(usOffset));
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~(_BIT7 | _BIT3), _BIT7);
}

