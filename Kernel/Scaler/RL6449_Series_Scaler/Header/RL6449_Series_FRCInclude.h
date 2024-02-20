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
// ID Code      : RL6449_Series_FRCInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of FRC address
//--------------------------------------------------
#if((_MEMORY_SIZE_CONFIG & _MEMORY_TYPE_CONFIG_MASK) == _MEMORY_DDR3)
//_1G_16BIT_DDR3_2PCS or _2G_16BIT_GDDR3_2PCS --> bank_remap_wide_enable = 1, Address: Row[27:12],Bnak[11:9],Column[8:0]
//_1G_16BIT_DDR3_1PC or _2G_16BIT_GDDR3_1PC --> bank_remap_wide_enable = 1, Address: Row[26:11],Bnak[10:8],Column[7:0]
//    |================|
//    |  M1 - Block 0  |
//    |----------------|
//    |  M2 - Block 0  |
//    |================|
//    |  M1 - Block 1  |
//    |----------------|
//    |  M2 - Block 1  |
//    |================|
//    |  M1 - Block 2  |
//    |----------------|
//    |  M2 - Block 2  |
//    |================|
//    |       OD       |
//    |================|
#define _FRC_CAP_M1_1ST_BLOCK_STA_ADDR                    (0x000000)     // ROW = 0
/*
#define _FRC_CAP_M1_2ND_BLOCK_STA_ADDR                    (512 << 12)     // ROW = 512
#define _FRC_CAP_M1_3RD_BLOCK_STA_ADDR                    (4096 << 12)    // ROW = 4096

#define _FRC_CAP_M2_1ST_BLOCK_STA_ADDR                    (1024 << 12)    // ROW = 1024
#define _FRC_CAP_M2_2ND_BLOCK_STA_ADDR                    (1536 << 12)    // ROW = 1536
#define _FRC_CAP_M2_3RD_BLOCK_STA_ADDR                    (4608 << 12)    // ROW = 4608
*/

#else

#define _FRC_CAP_M1_1ST_BLOCK_STA_ADDR                    (0x000000)     // ROW = 0
#define _FRC_CAP_M1_2ND_BLOCK_STA_ADDR                    (1365 << 11)    // ROW = 1365
#define _FRC_CAP_M1_3RD_BLOCK_STA_ADDR                    (682 << 11)     // ROW = 682

#define _FRC_CAP_M2_1ST_BLOCK_STA_ADDR                    (341 << 11)     // ROW = 341
#define _FRC_CAP_M2_2ND_BLOCK_STA_ADDR                    (1706 << 11)    // ROW = 1706
#define _FRC_CAP_M2_3RD_BLOCK_STA_ADDR                    (1023 << 11)    // ROW = 1023

#endif

#define _FRC_DISP_M1_1ST_BLOCK_STA_ADDR                   1
#define _FRC_DISP_M1_2ND_BLOCK_STA_ADDR                   2
#define _FRC_DISP_M1_3RD_BLOCK_STA_ADDR                   3
#define _FRC_DISP_M1_4TH_BLOCK_STA_ADDR                   4
#define _FRC_DISP_M2_1ST_BLOCK_STA_ADDR                   5
#define _FRC_DISP_M2_2ND_BLOCK_STA_ADDR                   6
#define _FRC_DISP_M2_3RD_BLOCK_STA_ADDR                   7
#define _FRC_DISP_M2_4TH_BLOCK_STA_ADDR                   8

//--------------------------------------------------
// Define FRC Access Length
//--------------------------------------------------
#define _FRC_ACCESS_WRITE_LENGTH                          (0x7C)
#define _FRC_ACCESS_READ_LENGTH                           (0x7C)
#endif // End of #if(_FRC_SUPPORT == _ON)

//--------------------------------------------------
// Deinfe FRC setting path
//--------------------------------------------------
#define _FRC_CAP_MAIN_1                                   (_BIT0)
#define _FRC_CAP_MAIN_2                                   (_BIT1)

#define _FRC_DISP_MAIN_1                                  (_BIT4)
#define _FRC_DISP_MAIN_2                                  (_BIT5)

#define _FRC_CAP_DISP_ALL                                 (_FRC_CAP_MAIN_1 | _FRC_CAP_MAIN_2 | _FRC_DISP_MAIN_1 | _FRC_DISP_MAIN_2)

#define _FRC_START_ADDRESS_M1                             (_FRC_CAP_M1_1ST_BLOCK_STA_ADDR)

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
extern void ScalerFRCControl(const StructSDRAMDataInfo *pstFIFOSize);
extern void ScalerFRCCompareIHFandDHF(WORD usVerSize);
extern WORD ScalerFRCSetOneFrameDVTotal(void);
#endif

extern void ScalerFRCSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect);

