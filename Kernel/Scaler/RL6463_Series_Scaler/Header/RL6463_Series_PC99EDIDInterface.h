/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6463_Series_PC99EDIDInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_PC99_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of PC99 EDID start address (at bank 0)
//--------------------------------------------------
#define _HW_PC99_WRITE_EDID_COMMAND_BANK_INDEX                  (0)
#define _HW_PC99_WRITE_EDID_COMMAND_ADDR_START                  (0xFD70)
#define _HW_PC99_A0_EDID_FLASH_ADDR_START                       (0xFD80)
#define _HW_PC99_D0_EDID_FLASH_ADDR_START                       (0xFE00)
#define _HW_PC99_D1_EDID_FLASH_ADDR_START                       (0xFF00)
#endif

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_HW_PC99_SUPPORT == _ON)
extern void ScalerPC99EDIDInitialControl(void);
#endif
