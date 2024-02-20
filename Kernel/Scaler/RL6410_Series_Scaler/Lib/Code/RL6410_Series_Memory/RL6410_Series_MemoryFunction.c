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
// ID Code      : RL6410_Series_MemoryFunction.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_MemoryLibInternalInclude.h"

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
DWORD ScalerMemoryCalculateNumberAndRemain(DWORD ulTotalSize, WORD usLength, bit bDummy);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Calculate the number and remain
// Input Value  : ulTotalSize --> Image total size
//                ucLength --> Length of SDRAM access
// Output Value : Number and Remain
//--------------------------------------------------
DWORD ScalerMemoryCalculateNumberAndRemain(DWORD ulTotalSize, WORD usLength, bit bDummy)
{
    if(bDummy == _TRUE)
    {
        /// In 6193, System Bridge data bus is 128 bits,
        ///   but its burst length and address unit is still 64 bits.
        ///   So NUM, LEN, and REM must be a multiple of 2.
        ulTotalSize += (ulTotalSize % 2);
    }

    if((ulTotalSize % usLength) != 0)
    {
        PDATA_WORD(0) = ulTotalSize / usLength; // Number
        PDATA_WORD(1) = ulTotalSize % usLength; // Remain
    }
    else
    {
        ulTotalSize = ulTotalSize - usLength;
        PDATA_WORD(0) = ulTotalSize / usLength; // Number
        PDATA_WORD(1) = usLength;               // Remain
    }

    return (((DWORD)PDATA_WORD(1) << 16) | PDATA_WORD(0));
}

