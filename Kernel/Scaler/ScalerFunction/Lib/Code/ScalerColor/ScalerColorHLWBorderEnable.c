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
// ID Code      : ScalerColorHLWBorderEnable.c
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
void ScalerColorHLWBorderEnable(bit bTopBorderEn, bit bBottomBorderEn, bit bLeftBorderEn, bit bRightBorderEn);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust HLW Border Enable
// Input Value  : bTopBorderEn, bBottomBorderEn, bLeftBorderEn, bRightBorderEn, enumDBApply
// Output Value : none
//--------------------------------------------------
void ScalerColorHLWBorderEnable(bit bTopBorderEn, bit bBottomBorderEn, bit bLeftBorderEn, bit bRightBorderEn)
{
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((BYTE)(~bLeftBorderEn) << 7) | ((BYTE)(~bRightBorderEn) << 6) | ((BYTE)(~bTopBorderEn) << 5) | ((BYTE)(~bBottomBorderEn) << 4));

    ScalerGlobalDDomainDBApply(_DB_APPLY_NO_POLLING);
}

