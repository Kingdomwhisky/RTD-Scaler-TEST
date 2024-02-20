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
// ID Code      : RL6369_Series_FRCInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _FRC_ACCESS_WRITE_LENGTH                        (0xA0)

#if(_MEMORY_SIZE_CONFIG == _1M_16BIT_SDRAM)
#define _FRC_ACCESS_READ_LENGTH                         (0x7C)
#else
#define _FRC_ACCESS_READ_LENGTH                         (0xFC)
#endif

//--------------------------------------------------
// Deinfe FRC setting path
//--------------------------------------------------
#define _FRC_CAP_MAIN_1                                 (_BIT0)
#define _FRC_DISP_MAIN_1                                (_BIT4)

#define _FRC_CAP_DISP_ALL                               (_FRC_CAP_MAIN_1 | _FRC_DISP_MAIN_1)

//--------------------------------------------------
// Deinfe for FRC auto 3 block toggle
//--------------------------------------------------
#define _FRC_R_1ST_BLOCK_STA_ADDR_H                     (0x00) // 0 row
#define _FRC_R_1ST_BLOCK_STA_ADDR_M                     (0x00)

#define _FRC_R_2ND_BLOCK_STA_ADDR_H                     (0x55) // 2730 row
#define _FRC_R_2ND_BLOCK_STA_ADDR_M                     (0x50)

#define _FRC_R_3RD_BLOCK_STA_ADDR_H                     (0x2A) // 1365 row
#define _FRC_R_3RD_BLOCK_STA_ADDR_M                     (0xA8)

#define _M_N_AUTO_BLK_TOGGLE_STABLE_TIME                (50)

#define _FRC_START_ADDRESS_M1                           (_FRC_R_1ST_BLOCK_STA_ADDR_H)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
extern void ScalerFRCInitial(void);
extern void ScalerFRCEn(BYTE ucSettingPath, bit bEn);
#endif

#if(_FRC_SUPPORT == _ON)
extern WORD ScalerFRCSetOneFrameDVTotal(void);
extern void ScalerFRCControl(const StructSDRAMDataInfo *pstFIFOSize);
#endif

extern void ScalerFRCSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect);

