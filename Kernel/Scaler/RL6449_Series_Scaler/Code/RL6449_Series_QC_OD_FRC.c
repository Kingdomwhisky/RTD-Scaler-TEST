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
// ID Code      : RL6449_Series_QC_OD_FRC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6449_SERIES_QC__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _IMD_CRC_I_AFTER_VGIP = 0,
    _IMD_CRC_I_AFTER_IDITHER,
    _IMD_CRC_I_AFTER_SD,
    _IMD_CRC_M_AFTER_FIFO = 0,
    _IMD_CRC_D_AFTER_DDITHER = 0,
    _IMD_CRC_D_AFTER_OD,
}EnumCRCPosition;


//****************************************************************************
// CODE TABLES
//****************************************************************************

//--------------------------------------------------
// Code Tables of FRC CRC
//--------------------------------------------------
BYTE code tFRC_CRCTable[] = {
    0x65, 0xCC, 0xED, 0x00, 0x00, 0x00, // M1
    0x65, 0xCC, 0xED, 0x00, 0x00, 0x00, // M2
};

#if(_QC_4P_MODE_ == _ON)
// 1280x1024 --> 1920x1080
BYTE code tFRC_CRCTable_4P_1[] = {
    0x4B, 0xA1, 0xEB, 0x00, 0x00, 0x00, // M1
    0x4B, 0xA1, 0xEB, 0x00, 0x00, 0x00, // M2
    0x4B, 0xA1, 0xEB, 0x00, 0x00, 0x00, // S1
    0x4B, 0xA1, 0xEB, 0x00, 0x00, 0x00, // S2
};

// 2048x2160 --> 1920x1080
BYTE code tFRC_CRCTable_4P_2[] = {
    0x8B, 0xAD, 0x56, 0x00, 0x00, 0x00, // M1
    0x8B, 0xAD, 0x56, 0x00, 0x00, 0x00, // M2
    0x8B, 0x25, 0x3D, 0x00, 0x00, 0x00, // S1
    0x8B, 0x25, 0x3D, 0x00, 0x00, 0x00, // S2
};

BYTE code tFRC_CRCTable_PBP_LR[] = {
    0xF2, 0x26, 0xA6, 0x00, 0x00, 0x00, // M1
    0xEF, 0x94, 0xB2, 0x00, 0x00, 0x00, // M2
    0x87, 0x1A, 0x3C, 0x00, 0x00, 0x00, // S1
/*
    0x6C, 0x62, 0xBE, 0x00, 0x00, 0x00, // M1
    0xFB, 0xE7, 0x0C, 0x00, 0x00, 0x00, // M2
    0x7F, 0x51, 0x43, 0x00, 0x00, 0x00, // S1
*/
};
#endif

//--------------------------------------------------
// Code Tables of OD Setting and CRC
//--------------------------------------------------
BYTE code tQC_OD_8BIT_TABLE[] =
{
    0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x04, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x09, 0x05, 0x00, 0x01, 0x00, 0x02, 0x06, 0x03, 0x06, 0x06, 0x06, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x0B, 0x07, 0x04, 0x00, 0x01, 0x04, 0x04, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x10,
    0x11, 0x0F, 0x09, 0x04, 0x00, 0x03, 0x06, 0x05, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0F, 0x13, 0x19, 0x1C,
    0x1B, 0x14, 0x0D, 0x08, 0x03, 0x00, 0x03, 0x06, 0x0D, 0x0D, 0x0D, 0x10, 0x12, 0x17, 0x1C, 0x23, 0x26,
    0x15, 0x18, 0x12, 0x0D, 0x08, 0x04, 0x00, 0x03, 0x08, 0x0D, 0x0F, 0x12, 0x17, 0x1B, 0x1E, 0x2A, 0x2C,
    0x17, 0x1C, 0x1B, 0x14, 0x0F, 0x0A, 0x05, 0x00, 0x04, 0x08, 0x0D, 0x11, 0x17, 0x1D, 0x1F, 0x2A, 0x32,
    0x1B, 0x21, 0x20, 0x1E, 0x16, 0x12, 0x0D, 0x07, 0x00, 0x04, 0x09, 0x0F, 0x15, 0x1D, 0x21, 0x2B, 0x34,
    0x1F, 0x20, 0x20, 0x21, 0x1B, 0x1B, 0x14, 0x0E, 0x08, 0x00, 0x06, 0x0D, 0x14, 0x1E, 0x22, 0x2A, 0x35,
    0x24, 0x1F, 0x1F, 0x21, 0x1E, 0x1E, 0x1B, 0x15, 0x0F, 0x08, 0x00, 0x06, 0x10, 0x1B, 0x22, 0x2A, 0x34,
    0x22, 0x1A, 0x1B, 0x20, 0x21, 0x1F, 0x1B, 0x18, 0x12, 0x0F, 0x08, 0x00, 0x09, 0x17, 0x21, 0x29, 0x30,
    0x1A, 0x18, 0x19, 0x1E, 0x20, 0x20, 0x1E, 0x19, 0x15, 0x10, 0x0D, 0x08, 0x00, 0x0D, 0x1F, 0x24, 0x2C,
    0x16, 0x16, 0x15, 0x16, 0x16, 0x16, 0x17, 0x16, 0x16, 0x14, 0x12, 0x0D, 0x09, 0x00, 0x0D, 0x1C, 0x23,
    0x13, 0x10, 0x12, 0x11, 0x12, 0x12, 0x12, 0x12, 0x11, 0x11, 0x10, 0x0D, 0x0A, 0x09, 0x00, 0x10, 0x1A,
    0x11, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0B, 0x0B, 0x0B, 0x0A, 0x09, 0x08, 0x00, 0x0F,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00,
};

BYTE code tQC_OD_10BIT_TABLE[] =
{
    0x00, 0x00, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80, 0x02, 0x80,
    0x04, 0x80, 0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80,
    0x09, 0x80, 0x05, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x80, 0x02, 0x80, 0x06, 0x80, 0x03, 0x80, 0x06, 0x80, 0x06, 0x80, 0x06, 0x80, 0x03, 0x80, 0x06, 0x80, 0x06, 0x80, 0x06, 0x80, 0x06, 0x80, 0x06, 0x80,
    0x0B, 0x80, 0x07, 0x80, 0x04, 0x80, 0x00, 0x00, 0x01, 0x80, 0x04, 0x80, 0x04, 0x80, 0x09, 0x80, 0x09, 0x80, 0x09, 0x80, 0x09, 0x80, 0x09, 0x80, 0x09, 0x80, 0x09, 0x80, 0x09, 0x80, 0x09, 0x80, 0x10, 0x80,
    0x11, 0x80, 0x0F, 0x80, 0x09, 0x80, 0x04, 0x80, 0x00, 0x00, 0x03, 0x80, 0x06, 0x80, 0x05, 0x80, 0x0C, 0x80, 0x0C, 0x80, 0x0C, 0x80, 0x0C, 0x80, 0x0C, 0x80, 0x0F, 0x80, 0x13, 0x80, 0x19, 0x80, 0x1C, 0x80,
    0x1B, 0x80, 0x14, 0x80, 0x0D, 0x80, 0x08, 0x80, 0x03, 0x80, 0x00, 0x00, 0x03, 0x80, 0x06, 0x80, 0x0D, 0x80, 0x0D, 0x80, 0x0D, 0x80, 0x10, 0x80, 0x12, 0x80, 0x17, 0x80, 0x1C, 0x80, 0x23, 0x80, 0x26, 0x80,
    0x15, 0x80, 0x18, 0x80, 0x12, 0x80, 0x0D, 0x80, 0x08, 0x80, 0x04, 0x80, 0x00, 0x00, 0x03, 0x80, 0x08, 0x80, 0x0D, 0x80, 0x0F, 0x80, 0x12, 0x80, 0x17, 0x80, 0x1B, 0x80, 0x1E, 0x80, 0x2A, 0x80, 0x2C, 0x80,
    0x17, 0x80, 0x1C, 0x80, 0x1B, 0x80, 0x14, 0x80, 0x0F, 0x80, 0x0A, 0x80, 0x05, 0x80, 0x00, 0x00, 0x04, 0x80, 0x08, 0x80, 0x0D, 0x80, 0x11, 0x80, 0x17, 0x80, 0x1D, 0x80, 0x1F, 0x80, 0x2A, 0x80, 0x32, 0x80,
    0x1B, 0x80, 0x21, 0x80, 0x20, 0x80, 0x1E, 0x80, 0x16, 0x80, 0x12, 0x80, 0x0D, 0x80, 0x07, 0x80, 0x00, 0x00, 0x04, 0x80, 0x09, 0x80, 0x0F, 0x80, 0x15, 0x80, 0x1D, 0x80, 0x21, 0x80, 0x2B, 0x80, 0x34, 0x80,
    0x1F, 0x80, 0x20, 0x80, 0x20, 0x80, 0x21, 0x80, 0x1B, 0x80, 0x1B, 0x80, 0x14, 0x80, 0x0E, 0x80, 0x08, 0x80, 0x00, 0x00, 0x06, 0x80, 0x0D, 0x80, 0x14, 0x80, 0x1E, 0x80, 0x22, 0x80, 0x2A, 0x80, 0x35, 0x80,
    0x24, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x21, 0x80, 0x1E, 0x80, 0x1E, 0x80, 0x1B, 0x80, 0x15, 0x80, 0x0F, 0x80, 0x08, 0x80, 0x00, 0x00, 0x06, 0x80, 0x10, 0x80, 0x1B, 0x80, 0x22, 0x80, 0x2A, 0x80, 0x34, 0x80,
    0x22, 0x80, 0x1A, 0x80, 0x1B, 0x80, 0x20, 0x80, 0x21, 0x80, 0x1F, 0x80, 0x1B, 0x80, 0x18, 0x80, 0x12, 0x80, 0x0F, 0x80, 0x08, 0x80, 0x00, 0x00, 0x09, 0x80, 0x17, 0x80, 0x21, 0x80, 0x29, 0x80, 0x30, 0x80,
    0x1A, 0x80, 0x18, 0x80, 0x19, 0x80, 0x1E, 0x80, 0x20, 0x80, 0x20, 0x80, 0x1E, 0x80, 0x19, 0x80, 0x15, 0x80, 0x10, 0x80, 0x0D, 0x80, 0x08, 0x80, 0x00, 0x00, 0x0D, 0x80, 0x1F, 0x80, 0x24, 0x80, 0x2C, 0x80,
    0x16, 0x80, 0x16, 0x80, 0x15, 0x80, 0x16, 0x80, 0x16, 0x80, 0x16, 0x80, 0x17, 0x80, 0x16, 0x80, 0x16, 0x80, 0x14, 0x80, 0x12, 0x80, 0x0D, 0x80, 0x09, 0x80, 0x00, 0x00, 0x0D, 0x80, 0x1C, 0x80, 0x23, 0x80,
    0x13, 0x80, 0x10, 0x80, 0x12, 0x80, 0x11, 0x80, 0x12, 0x80, 0x12, 0x80, 0x12, 0x80, 0x12, 0x80, 0x11, 0x80, 0x11, 0x80, 0x10, 0x80, 0x0D, 0x80, 0x0A, 0x80, 0x09, 0x80, 0x00, 0x00, 0x10, 0x80, 0x1A, 0x80,
    0x11, 0x80, 0x0B, 0x80, 0x0B, 0x80, 0x0B, 0x80, 0x0B, 0x80, 0x0B, 0x80, 0x0B, 0x80, 0x0B, 0x80, 0x0A, 0x80, 0x0B, 0x80, 0x0B, 0x80, 0x0B, 0x80, 0x0A, 0x80, 0x09, 0x80, 0x08, 0x80, 0x00, 0x00, 0x0F, 0x80,
    0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x00, 0x00,
};


BYTE code tQC_OD_CRC_TABLE_0[] =
{
    0x91, 0xC5, 0xFA, 0xCB, 0x9D, 0xFF, // M1
    0xEF, 0x92, 0x59, 0x68, 0xE6, 0x12, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub

    0x70, 0xE1, 0x06, 0x4E, 0x12, 0x7F, // M1
    0x52, 0x34, 0x9F, 0xC3, 0x2C, 0x1F, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub
};

BYTE code tQC_OD_CRC_TABLE_1[] =
{
    0x0F, 0x08, 0xCF, 0x0F, 0x05, 0xEF, // M1
    0xAD, 0x47, 0x19, 0x82, 0x41, 0x13, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub

    0x62, 0x3D, 0xE3, 0x0F, 0x05, 0xEF, // M1
    0xE5, 0xDF, 0xE5, 0xF5, 0x93, 0xB5, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub
};

BYTE code tQC_OD_CRC_TABLE_2[] =
{
    0x1C, 0xC3, 0x4C, 0x2F, 0xDE, 0x7C, // M1
    0x27, 0xB7, 0x08, 0x03, 0xFC, 0x38, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub

    0x62, 0x3D, 0xE3, 0x0F, 0x05, 0xEF, // M1
    0xE5, 0xDF, 0xE5, 0xF5, 0x93, 0xB5, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub
};

BYTE code tQC_OD_CRC_TABLE_3[] =
{
    0x8B, 0x68, 0x4E, 0x0A, 0xC6, 0x7E, // M1
    0x94, 0x0B, 0x44, 0x47, 0x6E, 0xA5, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub

    0x08, 0xEC, 0x22, 0xD1, 0x29, 0x56, // M1
    0xCF, 0x7A, 0xAB, 0x3C, 0x7D, 0x19, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub
};

BYTE code tQC_OD_CRC_TABLE_4[] =
{
    0x90, 0xC7, 0x01, 0x1E, 0x72, 0xB4, // M1
    0x64, 0x7B, 0xEB, 0xA5, 0x7B, 0x58, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub

    0x62, 0x3D, 0xE3, 0x0F, 0x05, 0xEF, // M1
    0xE5, 0xDF, 0xE5, 0xF5, 0x93, 0xB5, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub
};

BYTE code tQC_OD_CRC_TABLE_5[] =
{
    0x2C, 0xE8, 0xFF, 0x89, 0xD0, 0x95, // M1
    0x99, 0x5E, 0xDE, 0x37, 0x5B, 0x2F, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub

    0x62, 0x3D, 0xE3, 0x0F, 0x05, 0xEF, // M1
    0xE5, 0xDF, 0xE5, 0xF5, 0x93, 0xB5, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub
};

BYTE code tQC_OD_CRC_TABLE_6[] =
{
    0x51, 0x71, 0x93, 0x0C, 0xFE, 0xEB, // M1
    0x3C, 0xEA, 0x9E, 0xE2, 0x3D, 0xA7, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub

    0xEF, 0x58, 0xC8, 0x6F, 0xCB, 0x67, // M1
    0x41, 0xF0, 0xF8, 0x29, 0x9A, 0x6B, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub
};

BYTE code tQC_OD_CRC_TABLE_7[] =
{
    0x40, 0xED, 0xD7, 0xFF, 0xFD, 0xF5, // M1
    0x65, 0xC9, 0x93, 0x79, 0x72, 0x16, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub

    0x3B, 0xA5, 0x2A, 0xDB, 0x86, 0x99, // M1
    0xC9, 0x80, 0xCD, 0x19, 0xB0, 0x3F, // M2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sub
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
typedef enum
{
    _DISPLAY_MODE_1P,
    _DISPLAY_MODE_PIP,
    _DISPLAY_MODE_PBP_LR,
    _DISPLAY_MODE_PBP_TB,
    _DISPLAY_MODE_4P,
} EnumDisplayMode;
/*
typedef enum
{
    _FRC_DISPLAY_ONOFF = _BIT0,
    _FRC_CAPTURE_ONOFF = _BIT2,
    _FRC_ALL_ONOFF = (_FRC_DISPLAY_ONOFF | _FRC_CAPTURE_ONOFF),
} EnumFRCOnOff;
*/

#define _REG_PAGE_OFFSET                (0x4000)

#if(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_2PCS)
//#define _FRC_CAP_M1_1ST_BLOCK_STA_ADDR                    ((DWORD)0x000000)
#define _FRC_CAP_M1_2ND_BLOCK_STA_ADDR                    ((DWORD)512 << 12)   // 0x20 0000
#define _FRC_CAP_M2_1ST_BLOCK_STA_ADDR                    ((DWORD)1024 << 12)  // 0x40 0000
#define _FRC_CAP_M2_2ND_BLOCK_STA_ADDR                    ((DWORD)1536 << 12)  // 0x60 0000
#define _FRC_CAP_S1_1ST_BLOCK_STA_ADDR                    ((DWORD)2048 << 12)  // 0x80 0000
#define _FRC_CAP_S1_2ND_BLOCK_STA_ADDR                    ((DWORD)2560 << 12)  // 0xA0 0000
#define _FRC_CAP_S2_1ST_BLOCK_STA_ADDR                    ((DWORD)2304 << 12)  // 0x90 0000
#define _FRC_CAP_S2_2ND_BLOCK_STA_ADDR                    ((DWORD)2816 << 12)  // 0xB0 0000
#elif(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_1PC)
//#define _FRC_CAP_M1_1ST_BLOCK_STA_ADDR                    ((DWORD)0x000000)
#define _FRC_CAP_M1_2ND_BLOCK_STA_ADDR                    ((DWORD)512 << 11)   // 0x10 0000
#define _FRC_CAP_M2_1ST_BLOCK_STA_ADDR                    ((DWORD)1024 << 11)  // 0x20 0000
#define _FRC_CAP_M2_2ND_BLOCK_STA_ADDR                    ((DWORD)1536 << 11)  // 0x30 0000
#define _FRC_CAP_S1_1ST_BLOCK_STA_ADDR                    ((DWORD)2048 << 11)  // 0x40 0000
#define _FRC_CAP_S1_2ND_BLOCK_STA_ADDR                    ((DWORD)2560 << 11)  // 0x50 0000
#define _FRC_CAP_S2_1ST_BLOCK_STA_ADDR                    ((DWORD)2304 << 11)  // 0x48 0000
#define _FRC_CAP_S2_2ND_BLOCK_STA_ADDR                    ((DWORD)2816 << 11)  // 0x58 0000
#endif

//--------------------------------------------------
// OD Definitions
//--------------------------------------------------
#if(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_2PCS)
#define _OD_M1_MEM_START_ADDR           ((DWORD)7168 << 12) // 0x1C0 0000
#define _OD_M2_MEM_START_ADDR           ((DWORD)7680 << 12) // 0x1E0 0000
#elif(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_1PC)
#define _OD_M1_MEM_START_ADDR           ((DWORD)6144 << 11) // 0x0C0 0000
#define _OD_M2_MEM_START_ADDR           ((DWORD)7168 << 11) // 0x0E0 0000
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_QC_4P_MODE_ == _ON)
void ScalerQCMemorySetFifoCapture(EnumInputDataPath enumInputDataPath, WORD usHWidth, WORD usVHeight, BYTE ucDispMode);
DWORD ScalerQCFRCRegPageSelection(EnumInputDataPath ucInputPath);
void ScalerQCFRCEn(EnumFRCOnOff enumCapDispOnOff, EnumInputDataPath ucInputPath, bit bEn);
void ScalerQCFRCInitial(EnumInputDataPath enumInputPath, EnumDisplayMode enumDispMode);
void ScalerQCFRCInputCtrl(WORD usHorSize, WORD usVerSize, EnumInputDataPath enumInputPath, EnumDisplayMode enumDispMode);
void ScalerQCFRCDisplayCtrl(WORD usHorSize, WORD usVerSize, EnumInputDataPath enumInputPath, EnumDisplayMode enumDispMode);
void ScalerQCFRCCompareIHFandDHF(void);
void ScalerQCFRCControl(EnumInputDataPath enumInputPath, BYTE ucDispMode);
void ScalerQCFRC(BYTE ucDispMode);
#endif

bit ScalerQCFRCTest(void);
void ScalerQCODDDomainPattern1(void);
void ScalerQCODDDomainPattern2(void);
bit ScalerQCODTest(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_QC_4P_MODE_ == _ON)
//--------------------------------------------------
// Description  : Set FIFO Capture
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerQCMemorySetFifoCapture(EnumInputDataPath enumInputDataPath, WORD usHWidth, WORD usVHeight, BYTE ucDispMode)
{
    WORD usPageSelect = 0x0000;
    BYTE ucRegSelect = 0x00;

    for(pData[0] = 0; pData[0] < 4; pData[0]++)
    {
        if((enumInputDataPath & ((BYTE)_INPUT_PATH_M1 << pData[0])) == ((BYTE)_INPUT_PATH_M1 << pData[0]))
        {
            ucRegSelect = (pData[0] % 2) * 4;

            if((enumInputDataPath & ((BYTE)_INPUT_PATH_M1 | _INPUT_PATH_M2)) != 0)
            {
                // (Display mode != PBP_TB) || ((Display mode == PBP_TB) && M1)
                if((ucDispMode != _DISPLAY_MODE_PBP_TB) ||
                    ((ucDispMode == _DISPLAY_MODE_PBP_TB) && (pData[0] == 0)))
                {
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_00_DISPLAY_READ_WID_BSU_H + ucRegSelect), (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_01_DISPLAY_READ_WID_BSU_L + ucRegSelect), LOBYTE(usHWidth));
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_02_DISPLAY_READ_LEN_BSU_L + ucRegSelect), LOBYTE(usVHeight));
                    ScalerSetDataPortBit(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H + ucRegSelect), ~(_BIT4 | _BIT0), (((usHWidth & 0x1000) >> 8) | ((usVHeight & 0x1000) >> 12)));
                }
            }

            if((enumInputDataPath & ((BYTE)_INPUT_PATH_S1 | _INPUT_PATH_S2)) != 0)
            {
                if(ucDispMode == _DISPLAY_MODE_PBP_TB)
                {
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_04_DISPLAY_READ_WID_BSU_H_M2), (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_05_DISPLAY_READ_WID_BSU_L_M2), LOBYTE(usHWidth));
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_06_DISPLAY_READ_LEN_BSU_L_M2), LOBYTE(usVHeight));
                    ScalerSetDataPortBit(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_07_DISPLAY_READ_WID_LEN_BSU_H_M2), ~(_BIT4 | _BIT0), (((usHWidth & 0x1000) >> 8) | ((usVHeight & 0x1000) >> 12)));
                }
                else
                {
                    ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_S, (_P80_31_PT_00_DISPLAY_READ_WID_BSU_H_S1 + ucRegSelect), (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));
                    ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_S, (_P80_31_PT_01_DISPLAY_READ_WID_BSU_L_S1 + ucRegSelect), LOBYTE(usHWidth));
                    ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_S, (_P80_31_PT_02_DISPLAY_READ_LEN_BSU_L_S1 + ucRegSelect), LOBYTE(usVHeight));
                }
            }

            usPageSelect = ((WORD)pData[0] * 0x4000);

            // Set Capture Line Pixel Number
            ScalerSetByte(P5_1F_CAP_M1_PIXEL_NUM_H + usPageSelect, HIBYTE(usHWidth));
            ScalerSetByte(P5_20_CAP_M1_PIXEL_NUM_L + usPageSelect, LOBYTE(usHWidth));
            ScalerSetByte(P5_A2_DISP_M1_PXL_NUM_H + usPageSelect, HIBYTE(usHWidth));
            ScalerSetByte(P5_A3_DISP_M1_PXL_NUM_L + usPageSelect, LOBYTE(usHWidth));

            // Set Display Line Number
            ScalerSetByte(P5_21_CAP_M1_LINE_NUM_H + usPageSelect, HIBYTE(usVHeight));
            ScalerSetByte(P5_22_CAP_M1_LINE_NUM_L + usPageSelect, LOBYTE(usVHeight));
            ScalerSetByte(P5_A4_DISP_M1_LINE_NUM_H + usPageSelect, HIBYTE(usVHeight));
            ScalerSetByte(P5_A5_DISP_M1_LINE_NUM_L + usPageSelect, LOBYTE(usVHeight));
        }
    }
}

//--------------------------------------------------
// Description  : Select FRC Setting Path Address
// Input Value  : None
// Output Value : Path Address
//--------------------------------------------------
DWORD ScalerQCFRCRegPageSelection(EnumInputDataPath ucInputPath)
{
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 1;
    BYTE ucIdx;

    switch(ucInputPath)
    {
        case _INPUT_PATH_M1:
        case _INPUT_PATH_M2:
        case _INPUT_PATH_S1:
        case _INPUT_PATH_S2:
            for(ucIdx = 0; ucIdx < 4;ucIdx++)
            {
                if((ucInputPath & ((BYTE)_BIT0 << ucIdx)) == ((BYTE)_BIT0 << ucIdx))
                {
                    break;
                }
            }
            ucPathCount = 1;
            usPageSelect = ((DWORD)0x4000 * ucIdx);
            break;

        case _INPUT_PATH_S1_S2:
            ucPathCount = 2;
            usPageSelect = _REG_SUB1_PAGE;
            break;

        case _INPUT_PATH_ALL:
            ucPathCount = 4;
            usPageSelect = _REG_MAIN1_PAGE;
            break;

        default:
        case _INPUT_PATH_M1_M2:
            ucPathCount = 2;
            usPageSelect = _REG_MAIN1_PAGE;
            break;
    }

    return (((DWORD)usPageSelect << 8) | ucPathCount);
}

//--------------------------------------------------
// Description  : FRC function enable/disable
// Input Value  : ucSettingPath: path
// Input Value  : bEn: enable/disable
// Output Value : None
//--------------------------------------------------
void ScalerQCFRCEn(EnumFRCOnOff enumCapDispOnOff, EnumInputDataPath ucInputPath, bit bEn)
{
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 1;
    BYTE ucBitSelect = (_BIT2 | _BIT0);
    BYTE ucRegOffset = 0;
    BYTE ucIdx;

    // Calculate Register Page Number
    PDATA_DWORD(0) = ScalerQCFRCRegPageSelection(ucInputPath);
    ucPathCount = (PDATA_DWORD(0) & 0xFF);
    usPageSelect = (PDATA_DWORD(0) >> 8);

    for(ucIdx = 0; ucIdx < ucPathCount; ucIdx++)
    {
        ucBitSelect = (enumCapDispOnOff & (_BIT2 | _BIT0));
        if((usPageSelect == _REG_MAIN1_PAGE) || (usPageSelect == _REG_MAIN2_PAGE))
        {
            // M1 & M2
            ucRegOffset = 0x00;
            ucBitSelect = (usPageSelect == _REG_MAIN1_PAGE) ? (ucBitSelect << 4) : (ucBitSelect);
        }
        else
        {
            // S1 & S2
            ucRegOffset = 0x01;
            ucBitSelect = (usPageSelect == _REG_SUB1_PAGE) ? (ucBitSelect << 4) : (ucBitSelect);
        }

        if(bEn == _DISABLE)
        {
            if((enumCapDispOnOff & _FRC_CAPTURE_ONOFF) == _FRC_CAPTURE_ONOFF)
            {
                // Disable Capture Block
                ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT7), 0x00);
            }

            if((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) == _FRC_DISPLAY_ONOFF)
            {
                // Disable Display Block
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT0), 0x00);
            }

            // Clock Gating Disable(iclk/dclk)
            ScalerSetBit(P37_91_M_DOMAIN_FRC_CLK_SET1 + ucRegOffset, ~(ucBitSelect), 0x00);
        }
        else
        {
            if((enumCapDispOnOff & _FRC_CAPTURE_ONOFF) == _FRC_CAPTURE_ONOFF)
            {
                if(ScalerGetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, _BIT7) == 0x00)
                {
                    // Clock Gating Enable(iclk)
                    ScalerSetBit(P37_91_M_DOMAIN_FRC_CLK_SET1 + ucRegOffset, ~(ucBitSelect), ucBitSelect);

                    // Enable Capture Block
                    ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT7), _BIT7);
                }
            }

            if((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) == _FRC_DISPLAY_ONOFF)
            {
                if(ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, _BIT0) == 0x00)
                {
                    // Clock Gating Enable (dclk)
                    ScalerSetBit(P37_91_M_DOMAIN_FRC_CLK_SET1 + ucRegOffset, ~(ucBitSelect), ucBitSelect);

                    // Enable Display block
                    ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT0), _BIT0);
                }
            }
        } // End of if(bEn == _DISABLE)

        // Enable Double buffer
        ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~(_BIT4), _BIT4);

        usPageSelect += _REG_PAGE_OFFSET;

    }// End of for(ucIdx = 0; ucIdx < ucPathCount; ucIdx++)

    if((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) != 0)
    {
        // Wait double buffer
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : FRC Initial
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerQCFRCInitial(EnumInputDataPath enumInputPath, EnumDisplayMode enumDispMode)
{
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 1;
    BYTE ucIdx;

    ScalerQCFRCEn(_FRC_ALL_ONOFF, _INPUT_PATH_ALL, _DISABLE);

    // Enable Display double buffer
    ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P85_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(PC5_AD_DISP_STATUS, ~_BIT4, _BIT4);

    // Wait double buffer
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    // (For Roation using) Merge m1 display frame sync fifo to m2 display frame sync fifo.
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_24_DISP_MAIN_FIFO_LEN_CTRL, ~_BIT1, 0x00);

    // Calculate Register Page Number
    PDATA_DWORD(0)= ScalerQCFRCRegPageSelection(enumInputPath);
    ucPathCount = pData[3];
    usPageSelect = (PDATA_DWORD(0) >> 8);

    for(ucIdx = 0; ucIdx < ucPathCount; ucIdx++)
    {
        // Cosider Read/Write Address
        if(usPageSelect == _REG_MAIN1_PAGE)
        {
            PDATA_DWORD(0) = _FRC_CAP_M1_1ST_BLOCK_STA_ADDR;
            PDATA_DWORD(1) = _FRC_CAP_M1_2ND_BLOCK_STA_ADDR;
        }
        else if(usPageSelect == _REG_MAIN2_PAGE)
        {
            PDATA_DWORD(0) = _FRC_CAP_M2_1ST_BLOCK_STA_ADDR;
            PDATA_DWORD(1) = _FRC_CAP_M2_2ND_BLOCK_STA_ADDR;
        }
        else if(usPageSelect == _REG_SUB1_PAGE)
        {
            PDATA_DWORD(0) = _FRC_CAP_S1_1ST_BLOCK_STA_ADDR;
            PDATA_DWORD(1) = _FRC_CAP_S1_2ND_BLOCK_STA_ADDR;
        }
        else if(usPageSelect == _REG_SUB2_PAGE)
        {
            PDATA_DWORD(0) = _FRC_CAP_S2_1ST_BLOCK_STA_ADDR;
            PDATA_DWORD(1) = _FRC_CAP_S2_2ND_BLOCK_STA_ADDR;
        }

        // Set Read/Write Address
        pData[15] = 0x00;
        for(pData[14] = 0; pData[14] < 2; pData[14]++)
        {
            // Set Write/Read Start Address
            ScalerSetBit((P5_00_CAP_M1_MEM_ADDR_MSB + usPageSelect + pData[15]), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte((P5_01_CAP_M1_MEM_ADDR_H + usPageSelect + pData[15]), pData[1]);
            ScalerSetByte((P5_02_CAP_M1_MEM_ADDR_M + usPageSelect + pData[15]), pData[2]);
            ScalerSetByte((P5_03_CAP_M1_MEM_ADDR_L + usPageSelect + pData[15]), pData[3]);
            // Set Write/Read 2nd Address
            ScalerSetBit((P5_04_CAP_M1_BL2_ADDR_MSB + usPageSelect + pData[15]), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[4] & 0x0F));
            ScalerSetByte((P5_05_CAP_M1_BL2_ADDR_H + usPageSelect + pData[15]), pData[5]);
            ScalerSetByte((P5_06_CAP_M1_BL2_ADDR_M + usPageSelect + pData[15]), pData[6]);
            ScalerSetByte((P5_07_CAP_M1_BL2_ADDR_L + usPageSelect + pData[15]), pData[7]);
            // Set Write/Read 3rd Address
            ScalerSetBit((P5_08_CAP_M1_BL3_ADDR_MSB + usPageSelect + pData[15]), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[8] & 0x0F));
            ScalerSetByte((P5_09_CAP_M1_BL3_ADDR_H + usPageSelect + pData[15]), pData[9]);
            ScalerSetByte((P5_0A_CAP_M1_BL3_ADDR_M + usPageSelect + pData[15]), pData[10]);
            ScalerSetByte((P5_0B_CAP_M1_BL3_ADDR_L + usPageSelect + pData[15]), pData[11]);

            pData[15] = 0x80;
        }

        if(GET_MEMORY_SELECT() != _FRAME_SYNC_LINE_BUFFER)
        {
            // Use Information From FRC Capture
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT2 | _BIT1), 0x00);
        }

        usPageSelect += _REG_PAGE_OFFSET;
    }

    if(enumDispMode == _DISPLAY_MODE_4P)
    {
        // Set Single Channel Mode
        ScalerSetBit(P5_29_CAP_M1_DDR_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(P45_29_CAP_M2_DDR_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(P85_29_CAP_S1_DDR_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(PC5_29_CAP_S2_DDR_CTRL3, ~_BIT1, _BIT1);

        ScalerSetBit(P5_AF_DISP_M1_DISP_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(P45_AF_DISP_M2_DISP_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(P85_AF_DISP_S1_DISP_CTRL3, ~_BIT1, _BIT1);
        ScalerSetBit(PC5_AF_DISP_S2_DISP_CTRL3, ~_BIT1, _BIT1);

        ScalerQCFRCEn(_FRC_ALL_ONOFF, _INPUT_PATH_ALL, _ENABLE);

        // Set Pre-read
        ScalerSetByte(P5_A6_DISP_M1_PRRD_VST_H, 0x00);
        ScalerSetByte(P5_A7_DISP_M1_PRRD_VST_L, 0x03);
        ScalerSetByte(P45_A6_DISP_M2_PRRD_VST_H, 0x04);
        ScalerSetByte(P45_A7_DISP_M2_PRRD_VST_L, 0x3B);
        ScalerSetByte(P85_A6_DISP_S1_PRRD_VST_H, 0x00);
        ScalerSetByte(P85_A7_DISP_S1_PRRD_VST_L, 0x03);
        ScalerSetByte(PC5_A6_DISP_S2_PRRD_VST_H, 0x04);
        ScalerSetByte(PC5_A7_DISP_S2_PRRD_VST_L, 0x3B);

    }
    else
    {
        // Set Cooperation mode
        ScalerSetBit(P5_29_CAP_M1_DDR_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(P45_29_CAP_M2_DDR_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(P85_29_CAP_S1_DDR_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(PC5_29_CAP_S2_DDR_CTRL3, ~_BIT1, 0x00);

        ScalerSetBit(P5_AF_DISP_M1_DISP_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(P45_AF_DISP_M2_DISP_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(P85_AF_DISP_S1_DISP_CTRL3, ~_BIT1, 0x00);
        ScalerSetBit(PC5_AF_DISP_S2_DISP_CTRL3, ~_BIT1, 0x00);

        ScalerSetByte(P5_A6_DISP_M1_PRRD_VST_H, 0x02);
        ScalerSetByte(P5_A7_DISP_M1_PRRD_VST_L, 0x1F);
        ScalerSetByte(P45_A6_DISP_M2_PRRD_VST_H, 0x02);
        ScalerSetByte(P45_A7_DISP_M2_PRRD_VST_L, 0x1F);
        ScalerSetByte(P85_A6_DISP_S1_PRRD_VST_H, 0x02);
        ScalerSetByte(P85_A7_DISP_S1_PRRD_VST_L, 0x1F);
        ScalerSetByte(PC5_A6_DISP_S2_PRRD_VST_H, 0x02);
        ScalerSetByte(PC5_A7_DISP_S2_PRRD_VST_L, 0x1F);

        // Enable Main
        ScalerTimerWaitForEvent(_EVENT_IEN_START);
        ScalerQCFRCEn(_FRC_CAPTURE_ONOFF, _INPUT_PATH_M1_M2, _ENABLE);
        ScalerTimerWaitForEvent(_EVENT_DEN_START);
        ScalerQCFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_M1_M2, _ENABLE);

        // Enable Sub
        ScalerTimerWaitForEvent(_EVENT_IEN_START);
        ScalerQCFRCEn(_FRC_CAPTURE_ONOFF, _INPUT_PATH_S1_S2, _ENABLE);
        ScalerTimerWaitForEvent(_EVENT_DEN_START);
        ScalerQCFRCEn(_FRC_DISPLAY_ONOFF, _INPUT_PATH_S1_S2, _ENABLE);  // ???
    }

    // Enable Display double buffer
    ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P85_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(PC5_AD_DISP_STATUS, ~_BIT4, _BIT4);

    // Disable M:N frame tracking
    ScalerMemorySetFrameTrackingEnable(_DISABLE);

    // Wait double buffer
    ScalerTimerWaitForEvent(_EVENT_DVS);
}

//--------------------------------------------------
// Description  : IN1 FIFO Setting for FRC Mode
// Input Value  : ucSettingPath --> Path
//                ucHorSize --> Horizontal size
//                ucVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerQCFRCInputCtrl(WORD usHorSize, WORD usVerSize, EnumInputDataPath enumInputPath, EnumDisplayMode enumDispMode)
{
    StructMemoryLineBlockStep stStep;
    DWORD ulTemp = 0;
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 1;
    BYTE ucIdx;

    // Calculate Register Page Number
    ulTemp = ScalerQCFRCRegPageSelection(enumInputPath);;
    ucPathCount = (ulTemp & 0xFF);
    usPageSelect = (ulTemp >> 8);

    // Calculate Line Mode Size
    ulTemp = ScalerMemoryCalculateFrameLineTotalPixel(_LINE_MODE, usHorSize, usVerSize);

    if((enumInputPath == _INPUT_PATH_M1_M2) ||
        (enumInputPath == _INPUT_PATH_S1_S2))
    {
        // E/O Mode
        usVerSize = usVerSize >> 1;
    }

    // Calculate Line Step and Block Step
    ScalerMemoryCalculateLineStepAndBlockStep(ulTemp, usVerSize, &stStep);

    // One Line total pixel for Memory (FRC unit : 64 bits)
    ulTemp = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT()  % 64) ?
             (((DWORD)usHorSize * GET_MEMORY_DATA_BIT()  / 64) + 1) :
             ((DWORD)usHorSize * GET_MEMORY_DATA_BIT()  / 64);

    // Calculate Number of One Line and Remain of One Line
    ulTemp = ScalerMemoryCalculateNumberAndRemain(ulTemp, _FRC_ACCESS_WRITE_LENGTH, 1);

    for(ucIdx = 0; ucIdx < ucPathCount; ucIdx++)
    {
        // Set Input Format 30 Bit
        if(GET_MEMORY_DATA_BIT() == (_COLOR_DEPTH_10_BITS * 3))
        {
            ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2 + usPageSelect, ~_BIT7, _BIT7);
        }
        else
        {
            ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2 + usPageSelect, ~_BIT7, 0x00);
        }

        // Set Line Mode
        ScalerSetBit(P5_28_CAP_M1_DDR_CTRL2 + usPageSelect, ~(_BIT4), 0x00);

        // Set Block Step
        ScalerSetBit(P5_15_CAP_M1_BLOCK_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((stStep.ulBlockStep >> 24) & 0x0F));
        ScalerSetByte(P5_16_CAP_M1_BLOCK_STEP_H + usPageSelect, ((stStep.ulBlockStep >> 16) & 0xFF));
        ScalerSetByte(P5_17_CAP_M1_BLOCK_STEP_M + usPageSelect, ((stStep.ulBlockStep >> 8) & 0xFF));
        ScalerSetByte(P5_18_CAP_M1_BLOCK_STEP_L + usPageSelect, (stStep.ulBlockStep & 0xFF));

        if((enumInputPath == _INPUT_PATH_S1_S2) &
            ((enumDispMode == _DISPLAY_MODE_PIP) || (enumDispMode == _DISPLAY_MODE_PBP_LR)))
        {
            if(usPageSelect == _REG_SUB2_PAGE)
            {
                PDATA_DWORD(0) = (_FRC_CAP_S1_1ST_BLOCK_STA_ADDR + stStep.ulLineStep);
                PDATA_DWORD(1) = (_FRC_CAP_S1_2ND_BLOCK_STA_ADDR + stStep.ulLineStep);

                // Set Write/Read Start Address
                ScalerSetBit((P5_00_CAP_M1_MEM_ADDR_MSB + usPageSelect), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
                ScalerSetByte((P5_01_CAP_M1_MEM_ADDR_H + usPageSelect), pData[1]);
                ScalerSetByte((P5_02_CAP_M1_MEM_ADDR_M + usPageSelect), pData[2]);
                ScalerSetByte((P5_03_CAP_M1_MEM_ADDR_L + usPageSelect), pData[3]);
                // Set Write/Read 2nd Address
                ScalerSetBit((P5_04_CAP_M1_BL2_ADDR_MSB + usPageSelect), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[4] & 0x0F));
                ScalerSetByte((P5_05_CAP_M1_BL2_ADDR_H + usPageSelect), pData[5]);
                ScalerSetByte((P5_06_CAP_M1_BL2_ADDR_M + usPageSelect), pData[6]);
                ScalerSetByte((P5_07_CAP_M1_BL2_ADDR_L + usPageSelect), pData[7]);
                // Set Write/Read 3rd Address
                ScalerSetBit((P5_08_CAP_M1_BL3_ADDR_MSB + usPageSelect), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[8] & 0x0F));
                ScalerSetByte((P5_09_CAP_M1_BL3_ADDR_H + usPageSelect), pData[9]);
                ScalerSetByte((P5_0A_CAP_M1_BL3_ADDR_M + usPageSelect), pData[10]);
                ScalerSetByte((P5_0B_CAP_M1_BL3_ADDR_L + usPageSelect), pData[11]);

                // Set S2 Use Information From FRC Capture
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT2 | _BIT1), 0x00);
                // Enable FRC Display
                ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~_BIT4, _BIT4);
            }

            // Set Line Step
            ScalerSetBit(P5_19_CAP_M1_LINE_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (((stStep.ulLineStep * 2) >> 24) & 0x0F));
            ScalerSetByte(P5_1A_CAP_M1_LINE_STEP_H + usPageSelect, (((stStep.ulLineStep * 2) >> 16) & 0xFF));
            ScalerSetByte(P5_1B_CAP_M1_LINE_STEP_M + usPageSelect, (((stStep.ulLineStep * 2) >> 8) & 0xFF));
            ScalerSetByte(P5_1C_CAP_M1_LINE_STEP_L + usPageSelect, ((stStep.ulLineStep * 2) & 0xFF));
        }
        else
        {
            // Set Line Step
            ScalerSetBit(P5_19_CAP_M1_LINE_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((stStep.ulLineStep >> 24) & 0x0F));
            ScalerSetByte(P5_1A_CAP_M1_LINE_STEP_H + usPageSelect, ((stStep.ulLineStep >> 16) & 0xFF));
            ScalerSetByte(P5_1B_CAP_M1_LINE_STEP_M + usPageSelect, ((stStep.ulLineStep >> 8) & 0xFF));
            ScalerSetByte(P5_1C_CAP_M1_LINE_STEP_L + usPageSelect, (stStep.ulLineStep & 0xFF));
        }

        // Set Water level
        ScalerSetBit(P5_1D_CAP_M1_WATER_LEVEL_H + usPageSelect, ~(_BIT0), ((((WORD)_FRC_ACCESS_WRITE_LENGTH / 2) >> 8) & 0x01));
        ScalerSetByte(P5_1E_CAP_M1_WATER_LEVEL_L + usPageSelect, (((WORD)_FRC_ACCESS_WRITE_LENGTH / 2) & 0xFF));

        // Set Pixel Nmber
        ScalerSetByte(P5_1F_CAP_M1_PIXEL_NUM_H + usPageSelect, HIBYTE(usHorSize));
        ScalerSetByte(P5_20_CAP_M1_PIXEL_NUM_L + usPageSelect, LOBYTE(usHorSize));

        // Set Line Number
        ScalerSetByte(P5_21_CAP_M1_LINE_NUM_H + usPageSelect, HIBYTE(usVerSize));
        ScalerSetByte(P5_22_CAP_M1_LINE_NUM_L + usPageSelect, LOBYTE(usVerSize));

        // Set Number
        ScalerSetByte(P5_23_CAP_M1_WR_NUM_H + usPageSelect, ((ulTemp >> 8) & 0xFF));
        ScalerSetByte(P5_24_CAP_M1_WR_NUM_L + usPageSelect, (ulTemp & 0xFF));

        // Set Length, Remain
        ScalerSetByte(P5_25_CAP_M1_WR_LEN + usPageSelect, _FRC_ACCESS_WRITE_LENGTH);
        ScalerSetByte(P5_26_CAP_M1_WR_REMAIN + usPageSelect, ((ulTemp >> 16) & 0xFF));

        #if 0
        // Set Down limit = default value 0x0000000
        ScalerSetBit(P5_0C_CAP_M1_BOUNDARY_ADDR1_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P5_0D_CAP_M1_BOUNDARY_ADDR1_H + usPageSelect, 0x00);
        ScalerSetByte(P5_0E_CAP_M1_BOUNDARY_ADDR1_M + usPageSelect, 0x00);
        ScalerSetByte(P5_0F_CAP_M1_BOUNDARY_ADDR1_L + usPageSelect, 0x00);

        // Set Up limit = default value = 0xFFFFFFF
        ScalerSetBit(P5_10_CAP_M1_BOUNDARY_ADDR2_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
        ScalerSetByte(P5_11_CAP_M1_BOUNDARY_ADDR2_H + usPageSelect, 0xFF);
        ScalerSetByte(P5_12_CAP_M1_BOUNDARY_ADDR2_M + usPageSelect, 0xFF);
        ScalerSetByte(P5_13_CAP_M1_BOUNDARY_ADDR2_L + usPageSelect, 0xFF);
        #endif

        // Use IVS as synchronous reset
        ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT1), _BIT1);

        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER)
        {
            // Set Double Buffer
            ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
        }
        else
        {
            // Set Single Buffer
            ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
        }

        usPageSelect += _REG_PAGE_OFFSET;
    }
}

//--------------------------------------------------
// Description  : MAIN FIFO Setting for FRC Mode
// Input Value  : usHorSize --> Horizontal size
//                usVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerQCFRCDisplayCtrl(WORD usHorSize, WORD usVerSize, EnumInputDataPath enumInputPath, EnumDisplayMode enumDispMode)
{
    StructMemoryLineBlockStep stStep;
    DWORD ulTemp;
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 0;
    BYTE ucIdx;

    // Calculate Register Page Number
    ulTemp = ScalerQCFRCRegPageSelection(enumInputPath);;
    ucPathCount = (ulTemp & 0xFF);
    usPageSelect = (ulTemp >> 8);

    // Calculate Line Mode Size
    ulTemp = ScalerMemoryCalculateFrameLineTotalPixel(_LINE_MODE, usHorSize, usVerSize);

    if(enumInputPath == _INPUT_PATH_M1_M2)
    {
        // E/O Mode
        usVerSize = usVerSize >> 1;
    }
    else if(enumInputPath == _INPUT_PATH_S1_S2)
    {
        switch(enumDispMode)
        {
            case _DISPLAY_MODE_PIP:
            case _DISPLAY_MODE_PBP_LR:
                ucPathCount = 1;
                break;

            case _DISPLAY_MODE_PBP_TB:
                usVerSize = usVerSize >> 1;
                break;

            default:
                break;
        }
    }

    // Calculate Line Step And Block Step
    ScalerMemoryCalculateLineStepAndBlockStep(ulTemp, usVerSize, &stStep);

    // One Line total pixel for Memory (FRC unit : 64 bits)
    ulTemp = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT()  % 64) ?
             (((DWORD)usHorSize * GET_MEMORY_DATA_BIT()  / 64) + 1) :
             ((DWORD)usHorSize * GET_MEMORY_DATA_BIT()  / 64);

    // Calculate Number of One Line and Remain of One Line
    ulTemp = ScalerMemoryCalculateNumberAndRemain(ulTemp, _FRC_ACCESS_READ_LENGTH, 0);

    for(ucIdx = 0; ucIdx < ucPathCount; ucIdx++)
    {
        // Set Block Step
        ScalerSetBit(P5_95_DISP_M1_BLOCK_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((stStep.ulBlockStep >> 24) & 0x0F));
        ScalerSetByte(P5_96_DISP_M1_BLOCK_STEP_H + usPageSelect, ((stStep.ulBlockStep >> 16) & 0xFF));
        ScalerSetByte(P5_97_DISP_M1_BLOCK_STEP_M + usPageSelect, ((stStep.ulBlockStep >> 8) & 0xFF));
        ScalerSetByte(P5_98_DISP_M1_BLOCK_STEP_L + usPageSelect, (stStep.ulBlockStep & 0xFF));

        // Set Line Step
        ScalerSetBit(P5_99_DISP_M1_LINE_STEP_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((stStep.ulLineStep >> 24) & 0x0F));
        ScalerSetByte(P5_9A_DISP_M1_LINE_STEP_H + usPageSelect, ((stStep.ulLineStep >> 16) & 0xFF));
        ScalerSetByte(P5_9B_DISP_M1_LINE_STEP_M + usPageSelect, ((stStep.ulLineStep >> 8) & 0xFF));
        ScalerSetByte(P5_9C_DISP_M1_LINE_STEP_L + usPageSelect, (stStep.ulLineStep & 0xFF));

        // Set Water Level
        // Display Water Level < FIFO Depth (512) - Length / 2
        ScalerSetBit(P5_A0_DISP_M1_WTLVL_H + usPageSelect, ~(_BIT0), ((510 - _FRC_ACCESS_READ_LENGTH / 2) >> 8) & 0x01);
        ScalerSetByte(P5_A1_DISP_M1_WTLVL_L + usPageSelect, ((510 - _FRC_ACCESS_READ_LENGTH / 2) & 0xFF));

        // Set Pixel Number
        ScalerSetByte(P5_A2_DISP_M1_PXL_NUM_H + usPageSelect, HIBYTE(usHorSize));
        ScalerSetByte(P5_A3_DISP_M1_PXL_NUM_L + usPageSelect, LOBYTE(usHorSize));

        // Set Line number
        ScalerSetByte(P5_A4_DISP_M1_LINE_NUM_H + usPageSelect, HIBYTE(usVerSize));
        ScalerSetByte(P5_A5_DISP_M1_LINE_NUM_L + usPageSelect, LOBYTE(usVerSize));

        // Set Number
        ScalerSetByte(P5_A8_DISP_M1_READ_NUM_H + usPageSelect, ((ulTemp >> 8) & 0xFF));
        ScalerSetByte(P5_A9_DISP_M1_READ_NUM_L + usPageSelect, (ulTemp & 0xFF));

        // Set Length, Remain
        ScalerSetByte(P5_AA_DISP_M1_READ_LEN + usPageSelect, _FRC_ACCESS_READ_LENGTH);
        ScalerSetByte(P5_AB_DISP_M1_READ_REMAIN + usPageSelect, ((ulTemp >> 16) & 0xFF));

        #if 0
        // Set Down limit = default value 0x0000000
        ScalerSetBit(P5_8C_DISP_M1_BOUNDARY_ADDR1_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P5_8D_DISP_M1_BOUNDARY_ADDR1_H + usPageSelect, 0x00);
        ScalerSetByte(P5_8E_DISP_M1_BOUNDARY_ADDR1_M + usPageSelect, 0x00);
        ScalerSetByte(P5_8F_DISP_M1_BOUNDARY_ADDR1_L + usPageSelect, 0x00);

        // Set Up limit = default value = 0xFFFFFFF
        ScalerSetBit(P5_90_DISP_M1_BOUNDARY_ADDR2_MSB + usPageSelect, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
        ScalerSetByte(P5_91_DISP_M1_BOUNDARY_ADDR2_H + usPageSelect, 0xFF);
        ScalerSetByte(P5_92_DISP_M1_BOUNDARY_ADDR2_M + usPageSelect, 0xFF);
        ScalerSetByte(P5_93_DISP_M1_BOUNDARY_ADDR2_L + usPageSelect, 0xFF);
        #endif

        // Set Line mode
        ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~_BIT7, 0x00);

        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER)
        {
            // Set Double Frame Buffer
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
        }
        else
        {
            // Set Single Frame Buffer
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        }

        usPageSelect += _REG_PAGE_OFFSET;
    }

    // Calculate Register Page Number
    ulTemp = ScalerQCFRCRegPageSelection(enumInputPath);;
    usPageSelect = (ulTemp >> 8);

    // Enable FRC Display double buffer
    for(ucIdx = 0; ucIdx < ucPathCount; ucIdx++)
    {
        ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~_BIT4, _BIT4);
        usPageSelect += _REG_PAGE_OFFSET;
    }

    // Wait double buffer apply
    ScalerTimerWaitForEvent(_EVENT_DVS);
}

//--------------------------------------------------
// Description  : Compare which one of IHF and DHF is bigger, and see if they are too similar
// Input Value  : ucSettingPath --> Path
//                stFIFOSize    --> FIFO size
// Output Value : output is true when they are too similar
//--------------------------------------------------
void ScalerQCFRCCompareIHFandDHF(void)
{
    WORD usPageSelect = 0x0000;
    BYTE ucIdx;

    // Set Input Slower Than Display
    for(ucIdx = 0; ucIdx < 4; ucIdx++)
    {
        ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~_BIT3, 0x00);
        usPageSelect += _REG_PAGE_OFFSET;
    }
}

//--------------------------------------------------
// Description  : FRC control
// Input Value  : stFIFOSize --> FIFO size
// Output Value : None
//--------------------------------------------------
void ScalerQCFRCControl(EnumInputDataPath enumInputPath, BYTE ucDispMode)
{
    EnumDisplayMode enumDispMode = _DISPLAY_MODE_1P;
    WORD usHWidth;
    WORD usVHeight;

    if(ucDispMode == _4P)
    {
        if(GET_MDOMAIN_INPUT_HWIDTH() == 1280)
        {
            usHWidth = 1280;
            usVHeight = 1024;
        }
        else
        {
            usHWidth = 1920;
            usVHeight = 1080;
        }
        enumDispMode = _DISPLAY_MODE_4P;
    }
    else if(ucDispMode == _PBP_LR)
    {
        usHWidth = 1920;
        usVHeight = 1080;

        enumDispMode = _DISPLAY_MODE_PBP_LR;
    }

    // Set FIFO Capture Size
    ScalerQCMemorySetFifoCapture(enumInputPath, usHWidth, usVHeight, enumDispMode);

    // Set FRC Initial
    ScalerQCFRCInitial(enumInputPath, enumDispMode);

    // Set FRC IVS2DVSDelay
    ScalerFRCAdjustIVS2DVSDelay(usVHeight);

    // Consider Input Faster Or Slower
    ScalerQCFRCCompareIHFandDHF();

    // Set Up FRC Capture
    ScalerQCFRCInputCtrl(usHWidth, usVHeight, enumInputPath, enumDispMode);

    // Set Up FRC Display
    ScalerQCFRCDisplayCtrl(usHWidth, usVHeight, enumInputPath, enumDispMode);

    // Set Frame tracking function for VFreq < 30Hz
    if((GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY) && (enumDispMode == _DISPLAY_MODE_1P))
    {
        ScalerMemoryFrameTracking();
        ScalerMemorySetFrameTrackingEnable(_ENABLE);
    }

    //DebugMessageQC("FRC-H", usHWidth);
    //DebugMessageQC("FRC-V", usVHeight);
}

//--------------------------------------------------
// Description  : FRC control
// Input Value  : stFIFOSize --> FIFO size
// Output Value : None
//--------------------------------------------------
void ScalerQCFRC(BYTE ucDispMode)
{
    ScalerQCFRCEn((_FRC_CAPTURE_ONOFF | _FRC_DISPLAY_ONOFF), _INPUT_PATH_ALL, _DISABLE);

    if(ucDispMode == _4P)
    {
        ScalerQCFRCControl(_INPUT_PATH_ALL, _4P);
    }
    else if(ucDispMode == _PBP_LR)
    {
        ScalerQCFRCControl(_INPUT_PATH_M1_M2, _PBP_LR);
        ScalerQCFRCControl(_INPUT_PATH_S1_S2, _PBP_LR);
    }
}

//--------------------------------------------------
// Description  : Scale Down Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCFRC4PTest(BYTE ucDispMode)
{
    BYTE ucData = 0;

    DebugMessageQC("5. *** FRC Start ***", ucDispMode);

    ScalerQCIDomainRandomGenOn(_GRAY);

    if(ucDispMode == _4P)
    {
        ScalerQCWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1);
        ScalerQCWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1);
        ScalerQCWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1);

        if(GET_MDOMAIN_INPUT_HWIDTH() == 1280)
        {
            ucData = (ucData | (BYTE)ScalerQCCRCCompare(_M_DOMAIN_CRC, _IMD_CRC_M_AFTER_FIFO, (_M1 | _M2 | _S1 | _S2), tFRC_CRCTable_4P_1, 1));
        }
        else
        {
            ucData = (ucData | (BYTE)ScalerQCCRCCompare(_M_DOMAIN_CRC, _IMD_CRC_M_AFTER_FIFO, (_M1 | _M2 | _S1 | _S2), tFRC_CRCTable_4P_2, 1));
        }
    }
    else if(ucDispMode == _PBP_LR)
    {
        ScalerQCWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1);
        ScalerQCWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1);
        ScalerQCWaitForIDDomainEvent(_EVENT_DVS, _INPUT_PATH_M1);

        ucData = (ucData | (BYTE)ScalerQCCRCCompare(_M_DOMAIN_CRC, _IMD_CRC_M_AFTER_FIFO, (_M1 | _M2 | _S1), tFRC_CRCTable_PBP_LR, 1));
    }

    ScalerQCIDomainRandomGenOff();

    DebugMessageQC("5. *** FRC End ***", ucDispMode);
    if(ucData == 0x00)
    {
        DebugMessageQC("6. ****** FRC PASS", ucDispMode);
        return 0;
    }
    else
    {
        DebugMessageQC("6. FRC Mode", ucDispMode);
        DebugMessageQC("6. ****** FRC FAIL", ucDispMode);
        return 1;
    }
}
#endif

//--------------------------------------------------
// Description  : Scale Down Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCFRCTest(void)
{
    BYTE ucData = 0;
#if(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_1PC)
    BYTE ucTepm[4];
#endif

    DebugMessageQC("5. FRC Start", 0x00);

    ScalerQCIDomainRandomGenOn(_GRAY);

#if(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_1PC)
    ucTepm[0] = ScalerGetBit(P0_23_SCALE_DOWN_CTRL_M1, (_BIT1 | _BIT0));
    ucTepm[1] = ScalerGetBit(P40_23_SCALE_DOWN_CTRL_M2, (_BIT1 | _BIT0));
    ucTepm[2] = ScalerGetBit(P0_32_SCALE_CONTROL_REG, (_BIT1 | _BIT0));
    ucTepm[3] = ScalerGetBit(P40_32_SCALE_CONTROL_REG_M2, (_BIT1 | _BIT0));

    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P40_23_SCALE_DOWN_CTRL_M2, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P40_32_SCALE_CONTROL_REG_M2, ~(_BIT1 | _BIT0), 0x00);
#endif

    //***********************************
    //  FRC Capture - 3840 x 2160, 24Bit
    //***********************************
    // Set Start Address
    ScalerSetBit(P5_00_CAP_M1_MEM_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_01_CAP_M1_MEM_ADDR_H, 0x00);
    ScalerSetByte(P5_02_CAP_M1_MEM_ADDR_M, 0x00);
    ScalerSetByte(P5_03_CAP_M1_MEM_ADDR_L, 0x00);
    ScalerSetBit(P45_00_CAP_M2_MEM_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_01_CAP_M2_MEM_ADDR_H, 0x17);
    ScalerSetByte(P45_02_CAP_M2_MEM_ADDR_M, 0xBB);
    ScalerSetByte(P45_03_CAP_M2_MEM_ADDR_L, 0x00);
    // Set 2nd Address
    ScalerSetBit(P5_04_CAP_M1_BL2_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_05_CAP_M1_BL2_ADDR_H, 0x2F);
    ScalerSetByte(P5_06_CAP_M1_BL2_ADDR_M, 0x76);
    ScalerSetByte(P5_07_CAP_M1_BL2_ADDR_L, 0x00);
    ScalerSetBit(P45_04_CAP_M2_BL2_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_05_CAP_M2_BL2_ADDR_H, 0x47);
    ScalerSetByte(P45_06_CAP_M2_BL2_ADDR_M, 0x31);
    ScalerSetByte(P45_07_CAP_M2_BL2_ADDR_L, 0x00);
    // Set 3rd Address
    ScalerSetBit(P5_08_CAP_M1_BL3_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_09_CAP_M1_BL3_ADDR_H, 0x00);
    ScalerSetByte(P5_0A_CAP_M1_BL3_ADDR_M, 0x00);
    ScalerSetByte(P5_0B_CAP_M1_BL3_ADDR_L, 0x00);
    ScalerSetBit(P45_08_CAP_M2_BL3_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_09_CAP_M2_BL3_ADDR_H, 0x00);
    ScalerSetByte(P45_0A_CAP_M2_BL3_ADDR_M, 0x00);
    ScalerSetByte(P45_0B_CAP_M2_BL3_ADDR_L, 0x00);
    // Set Block Step
    ScalerSetBit(P5_15_CAP_M1_BLOCK_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_16_CAP_M1_BLOCK_STEP_H, 0x17);
    ScalerSetByte(P5_17_CAP_M1_BLOCK_STEP_M, 0xBB);
    ScalerSetByte(P5_18_CAP_M1_BLOCK_STEP_L, 0x00);
    ScalerSetBit(P45_15_CAP_M2_BLOCK_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_16_CAP_M2_BLOCK_STEP_H, 0x17);
    ScalerSetByte(P45_17_CAP_M2_BLOCK_STEP_M, 0xBB);
    ScalerSetByte(P45_18_CAP_M2_BLOCK_STEP_L, 0x00);
    // Set Line Step
    ScalerSetBit(P5_19_CAP_M1_LINE_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_1A_CAP_M1_LINE_STEP_H, 0x00);
    ScalerSetByte(P5_1B_CAP_M1_LINE_STEP_M, 0x05);
    ScalerSetByte(P5_1C_CAP_M1_LINE_STEP_L, 0xA0);
    ScalerSetBit(P45_19_CAP_M2_LINE_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_1A_CAP_M2_LINE_STEP_H, 0x00);
    ScalerSetByte(P45_1B_CAP_M2_LINE_STEP_M, 0x05);
    ScalerSetByte(P45_1C_CAP_M2_LINE_STEP_L, 0xA0);
    // Set Water level
    ScalerSetBit(P5_1D_CAP_M1_WATER_LEVEL_H, ~(_BIT0), 0x00);
    ScalerSetByte(P5_1E_CAP_M1_WATER_LEVEL_L, 0x3E);
    ScalerSetBit(P45_1D_CAP_M2_WATER_LEVEL_H, ~(_BIT0), 0x00);
    ScalerSetByte(P45_1E_CAP_M2_WATER_LEVEL_L, 0x3E);
    // Set Pixel Nmber
    ScalerSetByte(P5_1F_CAP_M1_PIXEL_NUM_H, 0x0F);
    ScalerSetByte(P5_20_CAP_M1_PIXEL_NUM_L, 0x00);
    ScalerSetByte(P45_1F_CAP_M2_PIXEL_NUM_H, 0x0F);
    ScalerSetByte(P45_20_CAP_M2_PIXEL_NUM_L, 0x00);
    // Set Line Number
    ScalerSetByte(P5_21_CAP_M1_LINE_NUM_H, 0x04);
    ScalerSetByte(P5_22_CAP_M1_LINE_NUM_L, 0x38);
    ScalerSetByte(P45_21_CAP_M2_LINE_NUM_H, 0x04);
    ScalerSetByte(P45_22_CAP_M2_LINE_NUM_L, 0x38);
    // Set Number
    ScalerSetByte(P5_23_CAP_M1_WR_NUM_H, 0x00);
    ScalerSetByte(P5_24_CAP_M1_WR_NUM_L, 0x0B);
    ScalerSetByte(P45_23_CAP_M2_WR_NUM_H, 0x00);
    ScalerSetByte(P45_24_CAP_M2_WR_NUM_L, 0x0B);
    // Set Length, Remain
    ScalerSetByte(P5_25_CAP_M1_WR_LEN, 0x7C);
    ScalerSetByte(P5_26_CAP_M1_WR_REMAIN, 0x4C);
    ScalerSetByte(P45_25_CAP_M2_WR_LEN, 0x7C);
    ScalerSetByte(P45_26_CAP_M2_WR_REMAIN, 0x4C);
    // Use IVS as synchronous reset
    ScalerSetByte(P5_27_CAP_M1_DDR_CTRL1, 0xA2);
    ScalerSetByte(P45_27_CAP_M2_DDR_CTRL1, 0xA2);
    // Set Line mode
    ScalerSetBit(P5_28_CAP_M1_DDR_CTRL2, ~(_BIT4), 0x00);
    ScalerSetBit(P45_28_CAP_M2_DDR_CTRL2, ~(_BIT4), 0x00);

    //***********************************
    //  FRC Display - 3840 x 2160, 24Bit
    //***********************************
    // Set Read Start Address
    ScalerSetBit(P5_80_DISP_M1_READ_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_81_DISP_M1_READ_ADDR_H, 0x00);
    ScalerSetByte(P5_82_DISP_M1_READ_ADDR_M, 0x00);
    ScalerSetByte(P5_83_DISP_M1_READ_ADDR_L, 0x00);
    ScalerSetBit(P45_80_DISP_M2_READ_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_81_DISP_M2_READ_ADDR_H, 0x17);
    ScalerSetByte(P45_82_DISP_M2_READ_ADDR_M, 0xBB);
    ScalerSetByte(P45_83_DISP_M2_READ_ADDR_L, 0x00);
    // Set 2nd address
    ScalerSetBit(P5_84_DISP_M1_BL2_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_85_DISP_M1_BL2_ADDR_H, 0x2F);
    ScalerSetByte(P5_86_DISP_M1_BL2_ADDR_M, 0x76);
    ScalerSetByte(P5_87_DISP_M1_BL2_ADDR_L, 0x00);
    ScalerSetBit(P45_84_DISP_M2_BL2_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_85_DISP_M2_BL2_ADDR_H, 0x47);
    ScalerSetByte(P45_86_DISP_M2_BL2_ADDR_M, 0x31);
    ScalerSetByte(P45_87_DISP_M2_BL2_ADDR_L, 0x00);
    // Set 3rd address
    ScalerSetBit(P5_88_DISP_M1_BL3_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_89_DISP_M1_BL3_ADDR_H, 0x00);
    ScalerSetByte(P5_8A_DISP_M1_BL3_ADDR_M, 0x00);
    ScalerSetByte(P5_8B_DISP_M1_BL3_ADDR_L, 0x00);
    ScalerSetBit(P45_88_DISP_M2_BL3_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_89_DISP_M2_BL3_ADDR_H, 0x00);
    ScalerSetByte(P45_8A_DISP_M2_BL3_ADDR_M, 0x00);
    ScalerSetByte(P45_8B_DISP_M2_BL3_ADDR_L, 0x00);
    // Set Block Step
    ScalerSetBit(P5_95_DISP_M1_BLOCK_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_96_DISP_M1_BLOCK_STEP_H, 0x17);
    ScalerSetByte(P5_97_DISP_M1_BLOCK_STEP_M, 0xBB);
    ScalerSetByte(P5_98_DISP_M1_BLOCK_STEP_L, 0x00);
    ScalerSetBit(P45_95_DISP_M2_BLOCK_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_96_DISP_M2_BLOCK_STEP_H, 0x17);
    ScalerSetByte(P45_97_DISP_M2_BLOCK_STEP_M, 0xBB);
    ScalerSetByte(P45_98_DISP_M2_BLOCK_STEP_L, 0x00);
    // Set Line Step
    ScalerSetBit(P5_99_DISP_M1_LINE_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P5_9A_DISP_M1_LINE_STEP_H, 0x00);
    ScalerSetByte(P5_9B_DISP_M1_LINE_STEP_M, 0x05);
    ScalerSetByte(P5_9C_DISP_M1_LINE_STEP_L, 0xA0);
    ScalerSetBit(P45_99_DISP_M2_LINE_STEP_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P45_9A_DISP_M2_LINE_STEP_H, 0x00);
    ScalerSetByte(P45_9B_DISP_M2_LINE_STEP_M, 0x05);
    ScalerSetByte(P45_9C_DISP_M2_LINE_STEP_L, 0xA0);
    // Set Water Level
    // Display Water Level < FIFO Depth (512) - Length / 2
    ScalerSetBit(P5_A0_DISP_M1_WTLVL_H, ~(_BIT0), 0x01);
    ScalerSetByte(P5_A1_DISP_M1_WTLVL_L, 0xC0);
    ScalerSetBit(P45_A0_DISP_M2_WTLVL_H, ~(_BIT0), 0x01);
    ScalerSetByte(P45_A1_DISP_M2_WTLVL_L, 0xC0);
    // Set Pixel Number
    ScalerSetByte(P5_A2_DISP_M1_PXL_NUM_H, 0x0F);
    ScalerSetByte(P5_A3_DISP_M1_PXL_NUM_L, 0x00);
    ScalerSetByte(P45_A2_DISP_M2_PXL_NUM_H, 0x0F);
    ScalerSetByte(P45_A3_DISP_M2_PXL_NUM_L, 0x00);
    // Set Line number
    ScalerSetByte(P5_A4_DISP_M1_LINE_NUM_H, 0x04);
    ScalerSetByte(P5_A5_DISP_M1_LINE_NUM_L, 0x38);
    ScalerSetByte(P45_A4_DISP_M2_LINE_NUM_H, 0x04);
    ScalerSetByte(P45_A5_DISP_M2_LINE_NUM_L, 0x38);
    // Set Pre-read
    ScalerSetByte(P5_A6_DISP_M1_PRRD_VST_H, 0x00);
    ScalerSetByte(P5_A7_DISP_M1_PRRD_VST_L, 0x03);
    ScalerSetByte(P45_A6_DISP_M2_PRRD_VST_H, 0x00);
    ScalerSetByte(P45_A7_DISP_M2_PRRD_VST_L, 0x03);
    // Set Number
    ScalerSetByte(P5_A8_DISP_M1_READ_NUM_H, 0x00);
    ScalerSetByte(P5_A9_DISP_M1_READ_NUM_L, 0x0B);
    ScalerSetByte(P45_A8_DISP_M2_READ_NUM_H, 0x00);
    ScalerSetByte(P45_A9_DISP_M2_READ_NUM_L, 0x0B);
    // Set Length, Remain
    ScalerSetByte(P5_AA_DISP_M1_READ_LEN, 0x7C);
    ScalerSetByte(P5_AB_DISP_M1_READ_REMAIN, 0x4C);
    ScalerSetByte(P45_AA_DISP_M2_READ_LEN, 0x7C);
    ScalerSetByte(P45_AB_DISP_M2_READ_REMAIN, 0x4C);
    // Set Input Format 24 Bit
    ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2, ~_BIT7, 0x00);
    ScalerSetBit(P45_AE_DISP_M2_DISP_CTRL2, ~_BIT7, 0x00);
    // Set Line mode, Double Frame Buffer, Enable FRC M1/M2 Display
    ScalerSetByte(P5_AC_DISP_M1_DISP_CTRL1, 0x41);
    ScalerSetByte(P45_AC_DISP_M2_DISP_CTRL1, 0x41);
    // Enable FRC M1/M2 Display double buffer
    ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
    ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);
    // Wait CAPTURE double buffer apply
    ScalerTimerWaitForEvent(_EVENT_IVS);
    // Wait Double frame buffer update data
    ScalerTimerWaitForEvent(_EVENT_IVS);
    // Wait DISPLAY double buffer apply
    //ScalerTimerWaitForEvent(_EVENT_DVS);
    // Wait Double frame buffer update data
    //ScalerTimerWaitForEvent(_EVENT_DVS);

    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_M_DOMAIN_CRC, _IMD_CRC_M_AFTER_FIFO, _M1 | _M2, tFRC_CRCTable, 1));

#if(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_1PC)
    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~(_BIT1 | _BIT0), ucTepm[0]);
    ScalerSetBit(P40_23_SCALE_DOWN_CTRL_M2, ~(_BIT1 | _BIT0), ucTepm[1]);
    ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~(_BIT1 | _BIT0), ucTepm[2]);
    ScalerSetBit(P40_32_SCALE_CONTROL_REG_M2, ~(_BIT1 | _BIT0), ucTepm[3]);
#endif

    ScalerQCIDomainRandomGenOff();

    DebugMessageQC("5. FRC End", 0x00);
    if(ucData == 0x00)
    {
        DebugMessageQC("6. FRC PASS", 0x00);
        return 0;
    }
    else
    {
        DebugMessageQC("6. FRC Mode", 0x01);
        DebugMessageQC("6. FRC FAIL", 0x00);
        return 1;
    }
}

//--------------------------------------------------
// Description  : Enable D Domain Pattern1 for OD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCODDDomainPattern1(void)
{
    ScalerSetByte(P7_F0_DISP_PG_R_CTRL, 0xC1);
    ScalerSetByte(P7_F1_DISP_PG_G_CTRL, 0x01);
    ScalerSetByte(P7_F2_DISP_PG_B_CTRL, 0x01);
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, 0x00);
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, 0x00);
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, 0x00);
    ScalerSetByte(P7_F6_DISP_PG_PIXEL_DELTA_H, 0x01);
    ScalerSetByte(P7_F7_DISP_PG_LINE_DELTA_H, 0x01);

    ScalerSetByte(P7_FB_D_PG_CTRL_0, 0x40);
    ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L, 0x15);
    ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL, 0x00);
}


//--------------------------------------------------
// Description  : Enable D Domain Pattern2 for OD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCODDDomainPattern2(void)
{
    ScalerSetByte(P7_F0_DISP_PG_R_CTRL, 0xC1);
    ScalerSetByte(P7_F1_DISP_PG_G_CTRL, 0x01);
    ScalerSetByte(P7_F2_DISP_PG_B_CTRL, 0x01);
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, 0x01);
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, 0x01);
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, 0x01);
    ScalerSetByte(P7_F6_DISP_PG_PIXEL_DELTA_H, 0x01);
    ScalerSetByte(P7_F7_DISP_PG_LINE_DELTA_H, 0x01);

    ScalerSetByte(P7_FB_D_PG_CTRL_0, 0x40);
    ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L, 0x15);
    ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL, 0x00);
}


//--------------------------------------------------
// Description  : OD Test
// Input Value  : None
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCODTest(void)
{
    BYTE ucData = 0;
    BYTE ucODLUTWriteStatus = 0;

    DebugMessageQC("5. OD Start", 0x00);

    //==================================================
    // Load 8-bit OD LUT Table
    //==================================================
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7 | _BIT0), 0x00);
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7), _BIT7);
    ScalerBurstWrite(tQC_OD_8BIT_TABLE, sizeof(tQC_OD_8BIT_TABLE), GET_CURRENT_BANK_NUMBER(), P3_C0_LS_LUT_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    ScalerRead(P3_BF_LS_LUT_CTRL, 1, &ucODLUTWriteStatus, _NON_AUTOINC);

    if((ucODLUTWriteStatus & 0x02) != 0x00)
    {
        DebugMessageQC("5. 3.OD Write 8-bit LUT Fail", 0x00);
    }

    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7), 0x00);

    ucODLUTWriteStatus = 0x00;


    // Memory Start Address and R/W FIFO Setting
    // M1
    ScalerSetByte(P3_D0_LS_DDR_FIFO_WTLVL_W_H, 0x00);
    ScalerSetByte(P3_D1_LS_DDR_FIFO_WTLVL_W_L, 0x30);
    ScalerSetByte(P3_D2_LS_DDR_FIFO_WTLVL_R_H, 0x00);
    ScalerSetByte(P3_D3_LS_DDR_FIFO_WTLVL_R_L, 0x60);
    ScalerSetByte(P3_D6_LS_DDR_FIFO_RW_LEN_H, 0x00);
    ScalerSetByte(P3_D7_LS_DDR_FIFO_RW_LEN_L, 0x60);

    PDATA_DWORD(0) = _OD_M1_MEM_START_ADDR;
    ScalerSetBit(P3_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
    ScalerSetByte(P3_DB_LS_DDR_START_ADDR_H, pData[1]);
    ScalerSetByte(P3_DC_LS_DDR_START_ADDR_M, pData[2]);
    ScalerSetByte(P3_DD_LS_DDR_START_ADDR_L, pData[3]);

    // M2
    ScalerSetByte(P43_D0_LS_DDR_FIFO_WTLVL_W_H, 0x00);
    ScalerSetByte(P43_D1_LS_DDR_FIFO_WTLVL_W_L, 0x30);
    ScalerSetByte(P43_D2_LS_DDR_FIFO_WTLVL_R_H, 0x00);
    ScalerSetByte(P43_D3_LS_DDR_FIFO_WTLVL_R_L, 0x60);
    ScalerSetByte(P43_D6_LS_DDR_FIFO_RW_LEN_H, 0x00);
    ScalerSetByte(P43_D7_LS_DDR_FIFO_RW_LEN_L, 0x60);

    PDATA_DWORD(0) = _OD_M2_MEM_START_ADDR;
    ScalerSetBit(P43_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
    ScalerSetByte(P43_DB_LS_DDR_START_ADDR_H, pData[1]);
    ScalerSetByte(P43_DC_LS_DDR_START_ADDR_M, pData[2]);
    ScalerSetByte(P43_DD_LS_DDR_START_ADDR_L, pData[3]);

    // DPG On
    ScalerQCDDomainRandomGenOn(_MASS, _BIT_MODE_10);

    //==================================================
    // Pattern 0:
    // RGBtoYUV
    // YUV444
    // Src Res: prev->4bit+UV round, curr->6bit+UV round
    // YUVtoRGB
    // Lvl Est: est_gain=9, est_value=1, asymmetric
    // NR: RGB related mode, nr_thd=1
    // HLW: full mode
    // Delta Gain: 93/64
    //==================================================
    DebugMessageQC("5. Mode_0", 0x00);

    // M1
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x15);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x17);
    ScalerSetByte(P3_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // M2
    ScalerSetByte(P43_D4_LS_DDR_FIFO_RW_NUM_H, 0x15);
    ScalerSetByte(P43_D5_LS_DDR_FIFO_RW_NUM_L, 0x17);
    ScalerSetByte(P43_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P43_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, (_BIT4 | _BIT3));
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x5D);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT5));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT5 | _BIT1));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT6 | _BIT5 | _BIT4));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, 0x09);
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6 | 0x01));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), 0x00);

    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1 | _M2, tQC_OD_CRC_TABLE_0, 2) << 0);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 1:
    // RGBtoYUV (Simp.)
    // Comp: YUV444to422, drop Mode, uv type 0
    // Src Res: prev->5bit+UV round, curr->4bit
    // Decomp: interp. mode
    // YUVtoRGB (Simp.)
    // Lvl Est: est_gain=15, est_value=3, est_range=8_pixels
    // NR: RGB indep. mode, nr_thd=9
    // HLW: full mode
    // Delta Gain: 1/64
    //==================================================
    DebugMessageQC("5. Mode_1", 0x00);

    // M1
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x17);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0xBA);
    ScalerSetByte(P3_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // M2
    ScalerSetByte(P43_D4_LS_DDR_FIFO_RW_NUM_H, 0x17);
    ScalerSetByte(P43_D5_LS_DDR_FIFO_RW_NUM_L, 0xBA);
    ScalerSetByte(P43_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P43_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | _BIT3 | _BIT1));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, (_BIT5 | _BIT4));
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x01);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT6 | _BIT5 | _BIT4));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (_BIT4 | 0x0F));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (0x03));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), 0x00);

    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1 | _M2, tQC_OD_CRC_TABLE_1, 2) << 1);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 2:
    // RGBtoYUV
    // Comp: YUV444to411, drop Mode
    // Src Res: prev->6bit, curr->8bit
    // Decomp: dup. mode
    // Lvl Est: est_gain=6, est_value=2, est_range=32_pixels, asymmetric
    // NR: RGB indep. mode, nr_thd=2
    // HLW: full mode
    // Delta Gain: 64/64
    //==================================================
    DebugMessageQC("5. Mode_2", 0x00);

    // M1
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x18);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x63);
    ScalerSetByte(P3_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x48);
    // M2
    ScalerSetByte(P43_D4_LS_DDR_FIFO_RW_NUM_H, 0x18);
    ScalerSetByte(P43_D5_LS_DDR_FIFO_RW_NUM_L, 0x63);
    ScalerSetByte(P43_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P43_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x48);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | _BIT3 | _BIT0));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, (_BIT4 | 0x01));
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x40);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT6 | _BIT5 | _BIT4 | 0x02));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT6 | _BIT3 | _BIT2));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, 0x00);
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (_BIT5 | _BIT4 | 0x06));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6 | 0x02));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), 0x00);

    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1 | _M2, tQC_OD_CRC_TABLE_2, 2) << 2);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 3:
    // Comp: SP1x2, average Mode
    // Src Res: prev->6bit, curr->5bit
    // Decomp: dup. mode
    // Bypass current frame
    // Lvl Est: est_gain=1, est_value=1, est_range=16_pixels, asymmetric
    // NR: RGB related mode, nr_thd=2
    // HLW: full mode
    // Delta Gain: 255/64
    //==================================================
    DebugMessageQC("5. Mode_3", 0x00);

    // M1
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x19);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x0C);
    ScalerSetByte(P3_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x30);
    // M2
    ScalerSetByte(P43_D4_LS_DDR_FIFO_RW_NUM_H, 0x19);
    ScalerSetByte(P43_D5_LS_DDR_FIFO_RW_NUM_L, 0x0C);
    ScalerSetByte(P43_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P43_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x30);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | _BIT3 | _BIT0));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, (_BIT4 | _BIT3 | 0x01));
    ScalerSetByte(P3_A3_DELTA_GAIN, 0xFF);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT7 | _BIT4 | 0x04));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT6 | _BIT3 | _BIT2));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT7));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (_BIT5 | 0x01));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6 | 0x01));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), 0x00);

    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1 | _M2, tQC_OD_CRC_TABLE_3, 2) << 3);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Load 10-bit OD LUT Table
    //==================================================
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7 | _BIT0), _BIT0);
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7), _BIT7);
    ScalerBurstWrite(tQC_OD_10BIT_TABLE, sizeof(tQC_OD_10BIT_TABLE), GET_CURRENT_BANK_NUMBER(), P3_C0_LS_LUT_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    ScalerRead(P3_BF_LS_LUT_CTRL, 1, &ucODLUTWriteStatus, _NON_AUTOINC);

    if((ucODLUTWriteStatus & 0x02) != 0x00)
    {
        DebugMessageQC("5. 3.OD Write 10-bit LUT Fail", 0x00);
    }

    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7), 0x00);

    ucODLUTWriteStatus = 0x00;

    //==================================================
    // Pattern 4:
    // Comp: SP1x3, average Mode
    // Src Res: prev->6bit, curr->6bit
    // Decomp: interp. mode
    // YUVtoRGB
    // Lvl Est: est_gain=14, est_value=0, est_range=16_pixels, asymmetric
    // NR: RGB indep. mode, nr_thd=1
    // HLW: full mode
    // Delta Gain: 99/64
    //==================================================
    DebugMessageQC("5. Mode_4", 0x00);

    // M1
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x19);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x0C);
    ScalerSetByte(P3_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x30);
    // M2
    ScalerSetByte(P43_D4_LS_DDR_FIFO_RW_NUM_H, 0x19);
    ScalerSetByte(P43_D5_LS_DDR_FIFO_RW_NUM_L, 0x0C);
    ScalerSetByte(P43_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P43_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x30);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | _BIT3 | _BIT0));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, (_BIT4));
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x63);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT4 | 0x06));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT6));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (_BIT5 | 0x0E));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), _BIT0);

    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1 | _M2, tQC_OD_CRC_TABLE_4, 2) << 4);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 5:
    // RGBtoYUV
    // Comp: SP1x4, average Mode
    // Src Res: prev->8bit, curr->6bit
    // Decomp: interp. mode
    // YUVtoRGB
    // Lvl Est: est_gain=8, est_value=1, est_range=8_pixels
    // HLW: full mode
    //==================================================
    DebugMessageQC("5. Mode_5", 0x00);

    // M1
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x12);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x74);
    ScalerSetByte(P3_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // M2
    ScalerSetByte(P43_D4_LS_DDR_FIFO_RW_NUM_H, 0x12);
    ScalerSetByte(P43_D5_LS_DDR_FIFO_RW_NUM_L, 0x74);
    ScalerSetByte(P43_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P43_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, 0x00);
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x40);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT5 | _BIT4 | 0x08));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT6));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (_BIT4 | 0x08));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (0x01));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), _BIT0);

    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1 | _M2, tQC_OD_CRC_TABLE_5, 2) << 5);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 6:
    // RGBtoYUV
    // Comp: YUV444to422, average Mode, uv type 1
    // Src Res: prev->4bit+UV round, curr->8bit
    // Decomp: interp. mode
    // Lvl Est: est_gain=8, est_value=2, asymmetric
    // HLW: inside HLW
    //==================================================
    DebugMessageQC("5. Mode_6", 0x00);

    ScalerQCHighlightWindowOn();

    // M1
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x0F);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0xD1);
    ScalerSetByte(P3_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // M2
    ScalerSetByte(P43_D4_LS_DDR_FIFO_RW_NUM_H, 0x0F);
    ScalerSetByte(P43_D5_LS_DDR_FIFO_RW_NUM_L, 0xD1);
    ScalerSetByte(P43_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P43_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | 0x03));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, 0x00);
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x40);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT5 | _BIT4 | _BIT0));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT3));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT4));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (0x08));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6 | 0x02));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), _BIT0);

    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1 | _M2, tQC_OD_CRC_TABLE_6, 2) << 6);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 7:
    // RGBtoYUV
    // Comp: YUV444to422, average Mode, uv type 1
    // Src Res: prev->4bit+UV round, curr->8bit
    // Decomp: interp. mode
    // Lvl Est: est_gain=8, est_value=2, asymmetric
    // HLW: outside HLW
    //==================================================
    DebugMessageQC("5. Mode_7", 0x00);

    ScalerQCHighlightWindowOn();

    // M1
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x0F);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0xD1);
    ScalerSetByte(P3_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // M2
    ScalerSetByte(P43_D4_LS_DDR_FIFO_RW_NUM_H, 0x0F);
    ScalerSetByte(P43_D5_LS_DDR_FIFO_RW_NUM_L, 0xD1);
    ScalerSetByte(P43_D8_LS_DDR_FIFO_RW_REMAIN_H, 0x00);
    ScalerSetByte(P43_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | 0x03));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), _BIT5);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, 0x00);
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x40);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT5 | _BIT4 | _BIT0));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT3));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT4));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (0x08));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6 | 0x02));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), _BIT0);

    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1 | _M2, tQC_OD_CRC_TABLE_7, 2) << 7);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    ScalerQCHighlightWindowOff();
    ScalerQCDDomainPatternGenOff();

    DebugMessageQC("5. OD End", 0x00);
    if(ucData == 0x00)
    {
        DebugMessageQC("6. OD PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", ucData);
        DebugMessageQC("6. OD FAIL", 0x00);
        return _TEST_FAIL;
    }
}
#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)
