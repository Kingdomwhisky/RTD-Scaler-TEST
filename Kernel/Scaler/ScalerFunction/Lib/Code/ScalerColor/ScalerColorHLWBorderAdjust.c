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
// ID Code      : ScalerColorHLWBorderAdjust.c
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
void ScalerColorHLWBorderAdjust(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust HLW Border Width and Color
// Input Value  : ucBorderWidth, ucRed, ucGreen, ucBlue, enumDBApply
// Output Value : none
//--------------------------------------------------
void ScalerColorHLWBorderAdjust(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{
    // set HLW's Border
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_08_HLW_BORDER_WIDTH, (ucBorderWidth & 0x1F));

    // border color is 10bits,  here still use 8bits
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_09_HLW_BORDER_RED, (ucRed & 0xFF));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_0A_HLW_BORDER_GRN, (ucGreen & 0xFF));
    ScalerSetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_0B_HLW_BORDER_BLU, (ucBlue & 0xFF));

    ScalerGlobalDDomainDBApply(_DB_APPLY_NO_POLLING);
}
