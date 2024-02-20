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
// ID Code      : ScalerCommonDataPortAccessGetDword.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerCommonRegLibInternalInclude.h"

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
DWORD ScalerGetDataPortDword(WORD usAddr, BYTE ucValue, bit bAutoInc);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get bytes from selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Address we want to Get
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
DWORD ScalerGetDataPortDword(WORD usAddr, BYTE ucValue, bit bAutoInc)
{
    BYTE pucArray[4];
    memset(pucArray, 0x00, sizeof(pucArray));

    ScalerGetDataPortByte(usAddr, ucValue, 4, pucArray, bAutoInc);

    return ((DWORD)pucArray[0] << 24) +
           ((DWORD)pucArray[1] << 16) +
           ((DWORD)pucArray[2] << 8) +
           ((DWORD)pucArray[3] << 0);
}

