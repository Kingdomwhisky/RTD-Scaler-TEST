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
// ID Code      : ScalerCommonNVRamCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Flash Support List
//--------------------------------------------------
#define _FLASH_W25X20A                              0
#define _FLASH_W25X21CL                             1
#define _FLASH_PM25LV020                            2
// This is MX25L2026D, it is not same with MX25L2026E
#define _FLASH_MX25L2026                            3
#define _FLASH_EN25F20                              4
#define _FLASH_PM25LD020                            5
// It is the same with MX25L2026E and KH25L2026E
#define _FLASH_MX25L2025                            6
// It is the same with MX25L4026E and KH25L4026E and KH25L4006E
#define _FLASH_MX25L4006E                           7
#define _FLASH_SST25LF020A                          8
#define _FLASH_W25X41CL                             9
#define _FLASH_FM25F04                              10
#define _FLASH_N25S40                               11
#define _FLASH_A25L040                              12
//W25Q80DV use the same _FLASH_W25Q80BV
#define _FLASH_W25Q80BV                             13
#define _FLASH_PM25LQ020A                           14
#define _FLASH_MX25L4026D                           15
#define _FLASH_W25X40CL                             16
#define _FLASH_EN25F20A                             17
#define _FLASH_EN25F40A                             18
#define _FLASH_EN25Q40A                             19
//EN25Q80A and EN25Q80B use the same _FLASH_EN25Q80
#define _FLASH_EN25Q80                              20
// GD25Q080C use the same _FLASH_GD25Q080B
#define _FLASH_GD25Q80B                             21
#define _FLASH_GD25M21B                             22
#define _FLASH_GD25M41B                             23
// KH25L8006E use the same _FLASH_MX25L8006E
#define _FLASH_MX25L8006E                           24
#define _FLASH_PM25LQ080                            25
//GD25Q40C use the same _FLASH_GD25Q40B
#define _FLASH_GD25Q40B                             26
#define _FLASH_MX25L1606E                           27
#define _FLASH_MX25L3206E                           28
#define _FLASH_A25L016                              29
#define _FLASH_W25Q16DV                             30
#define _FLASH_A25L032                              31
#define _FLASH_W25Q32F                              32
#define _FLASH_GD25Q16                              33
#define _FLASH_MX25L1633E                           34
#define _FLASH_GD25Q16C                             35
#define _FLASH_MX25L3233F                           36
#define _FLASH_PM25LQ040                            37
#define _FLASH_GD25Q41B                             38
#define _FLASH_EN25QH32A                            39
#define _FLASH_MX25V1635F                           40
#define _FLASH_AT25SF041                            41
#define _FLASH_MX25L6433F                           42
#define _FLASH_PM25LQ016                            43
#define _FLASH_GD25Q32C                             44
#define _FLASH_MX25V8035F                           45
#define _FLASH_AT25SF321                            46
#define _FLASH_FM25Q08A                             47
#define _FLASH_FM25Q04                              48
#define _FLASH_W25Q16JVSIM                          49
#define _FLASH_W25Q32JVSIM                          50
#define _FLASH_IS25LQ040B                           51
// MX25L3236FM2I-08G use the same _FLASH_KH25L3236F
#define _FLASH_KH25L3236F                           52
#define _FLASH_W25Q16JVSIQ                          53
#define _FLASH_MX25V4035F                           54
#define _FLASH_P25Q40H                              55
// This is different with FM25Q08A
#define _FLASH_FM25Q08                              56
#define _FLASH_P25Q80H                              57
#define _FLASH_P25Q16H                              58
#define _FLASH_BY25D40C                             59
#define _FLASH_GD25VQ16C                            60
#define _FLASH_MD25D80DT                            61
#define _FLASH_MD25D40DT                            62
#define _FLASH_EN25QH16B                            63
#define _FLASH_IS25LP080D                           64
#define _FLASH_BY25D40ASTIG                         65
#define _FLASH_BY25D16ASTIG                         66
#define _FLASH_BY25D80ASTIG                         67
#define _FLASH_XM25QH80B                            68
#define _FLASH_XM25QH40B                            69
#define _FLASH_XT25F08B                             70
#define _FLASH_W25Q32JVSSIQ                         71
#define _FLASH_P25Q32H                              72
#define _FLASH_W25Q128JVSQ                          73
#define _FLASH_XM25QH16C                            74
#define _FLASH_BY25Q80BSTIG                         75
#define _FLASH_XM25QH32CHIGT                        76
#define _FLASH_TYPE_END                             77
#define _FLASH_TOTAL_COUNT                          _FLASH_TYPE_END
#define _FLASH_DEFAULT_TYPE                         _FLASH_W25X20A
#define _FLASH_UNDETECT                             0xFE

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of Version Code related Infor.
//--------------------------------------------------
typedef struct
{
    BYTE ucIDCheck1OpCode; // ID check 1 OP code(0x9F/0x90/0xAB)
    BYTE ucIDCheck1_ID0; // ID check 1 ID
    BYTE ucIDCheck1_ID1;
    BYTE ucIDCheck1_ID2;
    BYTE ucIDCheck2OpCode; // ID check 1 OP code(0x90/0xAB)
    BYTE ucIDCheck2_ID0; // ID check 1 ID
    BYTE ucIDCheck2_ID1;
    BYTE ucIDCheck2_ID2;
    BYTE ucWRENOpCode; // WREN OP code
    BYTE ucWRDisOpCode; // WRDis OP code
    BYTE ucPageEraseOpCode; // Page erase OP code
    BYTE ucUnprotectWRSR; // Unprotect status register value
    BYTE ucProtectWRSR; // Protect status register value
} StructFlashInformation;

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucFlashType;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerFlashDetectFlashType(void);
extern void ScalerFlashWREN(BYTE ucBank, BYTE ucPage);
extern void ScalerFlashWRDis(void);

extern bit ScalerFlashErasePage(BYTE ucBank, BYTE ucPage);


