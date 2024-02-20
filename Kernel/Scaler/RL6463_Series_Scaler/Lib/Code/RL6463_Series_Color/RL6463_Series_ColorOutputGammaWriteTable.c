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
// ID Code      : RL6463_Series_ColorOutputGammaWriteTable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6463_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GAMMA_WRITE_TO_SRAM                    0
#define _GAMMA_WRITE_TO_LATCH                   1

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
void ScalerColorOutputGammaWriteTable(BYTE *pucGammaTableArray, EnumGammaChannel enumGammaChannel, BYTE ucOffset, WORD usDataLength);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust output gamma by selecting Channel/Offset/Length
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerColorOutputGammaWriteTable(BYTE *pucGammaTableArray, EnumGammaChannel enumGammaChannel, BYTE ucOffset, WORD usDataLength)
{
    // Enable Gamma access
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, _BIT7);

    // Set Gamma Channel
    ScalerColorOutputGammaChannelCtrl(enumGammaChannel, ucOffset, _GAMMA_WRITE_TO_SRAM);

    // Write Gamma LUT
    ScalerWrite(P0_66_GAMMA_PORT_SETA, usDataLength, pucGammaTableArray, _NON_AUTOINC);

    // Disable Port Access
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);
}
