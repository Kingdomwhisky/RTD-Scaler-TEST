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
// ID Code      : BeaconUserBoot.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_BOOT__

#include "UserCommonInclude.h"

#if((_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _FLASH_PARTITION_BOOTTABLE_BANK                          (0x10)
#define _FLASH_PARTITION_BOOTTABLE_ADDRESS                       (0xF8FE)
#define _FLASH_PARTITION_BOOTTABLE_DATA                          0xAA, 0x55


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tFLASH_PARTITION_BOOTTABLE[] =
{
    _FLASH_PARTITION_BOOTTABLE_DATA
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT)
BYTE UserInterfaceGetUserCodeLocation(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT)
//--------------------------------------------------
// Description  : Check boot/user code status
// Input Value  : None
// Output Value : Bank number of user code
//--------------------------------------------------
BYTE UserInterfaceGetUserCodeLocation(void)
{
    BYTE pucBootTable[sizeof(tFLASH_PARTITION_BOOTTABLE)];
    memset(pucBootTable, 0, sizeof(tFLASH_PARTITION_BOOTTABLE));

    // Select XDATA BANK start
    MCU_FFFD_XDATA_BANK_START = 0x00;

    // Read BootTable data from Flash
    UserCommonFlashRead(_FLASH_PARTITION_BOOTTABLE_BANK, _FLASH_PARTITION_BOOTTABLE_ADDRESS, sizeof(tFLASH_PARTITION_BOOTTABLE), pucBootTable);

    // Check user-defined user/boot code id
    if(memcmp(pucBootTable, tFLASH_PARTITION_BOOTTABLE, sizeof(tFLASH_PARTITION_BOOTTABLE)) == 0)
    {
        // Check success; return user bank address
        return _FLASH_PARTITION_BOOTTABLE_BANK;
    }

    // Check fail; return init bank
    return _FLASH_PARTITION_INIT_BANK;
}
#endif

#endif // End of #if((_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))

