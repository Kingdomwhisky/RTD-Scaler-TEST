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
// ID Code      : NoneUserBoot.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_BOOT__

#include "UserCommonInclude.h"

#if((_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
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
    return _FLASH_PARTITION_INIT_BANK;
}
#endif

#endif // End of #if((_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))

