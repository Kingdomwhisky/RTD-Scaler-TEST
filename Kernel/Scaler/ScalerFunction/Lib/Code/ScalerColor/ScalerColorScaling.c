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
// ID Code      : ScalerColorScaling.c
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
bit ScalerColorScalingByPassTableSel(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Scaling By pass
// Input Value  : none
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerColorScalingByPassTableSel(void)
{
    ScalerGetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_03_VER_SCALE_FACTOR_H, 3, &pData[0], _AUTOINC);
    ScalerGetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_00_HOR_SCALE_FACTOR_H, 3, &pData[3], _AUTOINC);

    if(((pData[0] & 0x0F) == 0x0F) && (pData[1] == 0xFF) && (pData[2] == 0xFF) &&
       ((pData[3] & 0x0F) == 0x0F) && (pData[4] == 0xFF) && (pData[5] == 0xFF))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

