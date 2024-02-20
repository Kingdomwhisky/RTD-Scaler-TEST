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
// ID Code      : ScalerCommonFlashRead.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCLAER_COMMON_FLASH_READ__

#include "ScalerCommonNVRamLibInternalInclude.h"

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
bit ScalerFlashRead(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Load data from flash
// Input Value  : ucBank: bank index
//                usAddr: address in ucBank
//                ucLength: the data length to load
//                pucData: data buffer to save the load data
// Output Value : _TRUE for load success and _FALSE for load fail
//--------------------------------------------------
bit ScalerFlashRead(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData)
{
    WORD usIndex = 0;

    // The access bank is smaller than than the start bank
    if(ucBank < MCU_FFFD_XDATA_BANK_START)
    {
        return _FALSE;
    }

    // Enable flash access and address auto increase
    MCU_FF7C_ACCESS_FLASH_DATA_CTRL |= (_BIT1 | _BIT0);

    MCU_FF78_ACCESS_FLASH_ADDR_0 = ucBank;
    MCU_FF79_ACCESS_FLASH_ADDR_1 = (BYTE)(usAddr >> 8);
    MCU_FF7A_ACCESS_FLASH_ADDR_2 = (BYTE)(usAddr);

    for(usIndex = 0; usIndex < usLength; usIndex++)
    {
        pucData[usIndex] = MCU_FF7B_ACCESS_FLASH_DATA_PORT;
    }

    // Disable flash access
    MCU_FF7C_ACCESS_FLASH_DATA_CTRL &= ~_BIT0;

    return _TRUE;
}

