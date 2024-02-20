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
// ID Code      : RL6492_Series_ColorPCMTable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6492_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// PCM TABLE For OCC
//----------------------------------------------------------------------------------------------------
BYTE code tPCM_INPUTGAMMA_SRGB[] =
{
    0x00, 0x00, 0x28,
    0x04, 0xF0, 0x77,
    0x09, 0xF0, 0xC6,
    0x0F, 0x01, 0x1F,
    0x15, 0x21, 0x8A,
    0x1C, 0x82, 0x0B,
    0x25, 0x32, 0xA1,
    0x2F, 0x53, 0x4E,
    0x3A, 0xD4, 0x12,
    0x47, 0xD4, 0xEE,
    0x56, 0x65, 0xE4,
    0x66, 0x86, 0xF3,
    0x78, 0x58, 0x1D,
    0x8B, 0xC9, 0x62,
    0xA0, 0xFA, 0xC3,
    0xB7, 0xEC, 0x40,
    0xD0, 0x9D, 0xDA,
    0xEB, 0x3F, 0x92,
    0x41, 0xE4, 0x5A,
    0x49, 0x84, 0xD8,
    0x51, 0x95, 0x5D,
    0x5A, 0x25, 0xEA,
    0x63, 0x46, 0x7F,
    0x6C, 0xD7, 0x1D,
    0x76, 0xF7, 0xC3,
    0x81, 0x98, 0x71,
    0x8C, 0xC9, 0x28,
    0x98, 0x79, 0xE8,
    0xA4, 0xCA, 0xB1,
    0xB1, 0x9B, 0x83,
    0xBE, 0xFC, 0x5E,
    0xCC, 0xED, 0x42,
    0xDB, 0x7E, 0x2F,
    0xEA, 0x9F, 0x25,
    0xFA, 0x44, 0x09,
    0x42, 0xA4, 0x4C,
    0x46, 0xE4, 0x91,
    0x4B, 0x44, 0xD8,
    0x4F, 0xD5, 0x22,
    0x54, 0x85, 0x6E,
    0x59, 0x55, 0xBD,
    0x5E, 0x56, 0x0E,
    0x63, 0x86, 0x62,
    0x68, 0xD6, 0xB9,
    0x6E, 0x57, 0x12,
    0x73, 0xF7, 0x6E,
    0x79, 0xD7, 0xCC,
    0x7F, 0xC8, 0x2D,
    0x85, 0xF8, 0x91,
    0x8C, 0x48, 0xF8,
    0x92, 0xC9, 0x61,
    0x99, 0x79, 0xCD,
    0xA0, 0x4A, 0x3C,
    0xA7, 0x4A, 0xAE,
    0xAE, 0x7B, 0x22,
    0xB5, 0xDB, 0x99,
    0xBD, 0x6C, 0x14,
    0xC5, 0x2C, 0x91,
    0xCD, 0x0D, 0x10,
    0xD5, 0x2D, 0x93,
    0xDD, 0x6E, 0x19,
    0xE5, 0xDE, 0xA2,
    0xEE, 0x8F, 0x2E,
    0xF7, 0x5F, 0xBD,
    0xFF, 0xC0, 0x00,
    0x23, 0x44,
};

BYTE code tPCM_INPUTGAMMA_ADOBERGB[] =
{
    0x00, 0x00, 0x02,
    0x00, 0x70, 0x11,
    0x02, 0x00, 0x34,
    0x04, 0xE0, 0x6E,
    0x09, 0x40, 0xBF,
    0x0F, 0x11, 0x29,
    0x16, 0x81, 0xAD,
    0x1F, 0x92, 0x4C,
    0x2A, 0x53, 0x06,
    0x36, 0xE3, 0xDD,
    0x45, 0x34, 0xD0,
    0x55, 0x55, 0xE1,
    0x67, 0x57, 0x10,
    0x7B, 0x38, 0x5D,
    0x90, 0xF9, 0xCA,
    0xA8, 0xCB, 0x55,
    0xC2, 0x7D, 0x01,
    0xDE, 0x3E, 0xCD,
    0xFB, 0xF4, 0x2E,
    0x46, 0xF4, 0xB2,
    0x4F, 0x65, 0x3E,
    0x58, 0x65, 0xD2,
    0x61, 0xF6, 0x6E,
    0x6C, 0x07, 0x14,
    0x76, 0x97, 0xC1,
    0x81, 0xC8, 0x78,
    0x8D, 0x69, 0x37,
    0x99, 0xAA, 0x00,
    0xA6, 0x7A, 0xD1,
    0xB3, 0xCB, 0xAB,
    0xC1, 0xBC, 0x8E,
    0xD0, 0x3D, 0x7A,
    0xDF, 0x4E, 0x70,
    0xEE, 0xEF, 0x6E,
    0xFF, 0x14, 0x1E,
    0x44, 0x04, 0x62,
    0x48, 0x54, 0xA9,
    0x4C, 0xD4, 0xF2,
    0x51, 0x75, 0x3D,
    0x56, 0x45, 0x8B,
    0x5B, 0x35, 0xDB,
    0x60, 0x46, 0x2E,
    0x65, 0x86, 0x83,
    0x6A, 0xE6, 0xDA,
    0x70, 0x77, 0x34,
    0x76, 0x27, 0x90,
    0x7C, 0x07, 0xEF,
    0x82, 0x08, 0x51,
    0x88, 0x28, 0xB4,
    0x8E, 0x79, 0x1B,
    0x94, 0xF9, 0x84,
    0x9B, 0x99, 0xEF,
    0xA2, 0x6A, 0x5D,
    0xA9, 0x5A, 0xCD,
    0xB0, 0x6B, 0x40,
    0xB7, 0xAB, 0xB6,
    0xBF, 0x1C, 0x2E,
    0xC6, 0xBC, 0xA8,
    0xCE, 0x7D, 0x26,
    0xD6, 0x5D, 0xA5,
    0xDE, 0x6E, 0x28,
    0xE6, 0xAE, 0xAD,
    0xEF, 0x0F, 0x34,
    0xF7, 0x9F, 0xBF,
    0xFF, 0xC0, 0x00,
    0x24, 0x44,
};

BYTE code tPCM_INPUTGAMMA_EBU[] =
{
    0x00, 0x00, 0x01,
    0x00, 0x40, 0x0A,
    0x01, 0x30, 0x20,
    0x03, 0x10, 0x47,
    0x06, 0x10, 0x80,
    0x0A, 0x40, 0xCD,
    0x0F, 0xC1, 0x30,
    0x16, 0xA1, 0xAA,
    0x1E, 0xF2, 0x3B,
    0x28, 0xD2, 0xE6,
    0x34, 0x53, 0xAA,
    0x41, 0x74, 0x8A,
    0x50, 0x45, 0x85,
    0x60, 0xE6, 0x9E,
    0x73, 0x57, 0xD3,
    0x87, 0x99, 0x27,
    0x9D, 0xDA, 0x9A,
    0xB5, 0xFC, 0x2D,
    0xD0, 0x2D, 0xDF,
    0xEC, 0x5F, 0xB3,
    0x42, 0xA4, 0x6A,
    0x4A, 0xB4, 0xEF,
    0x53, 0x65, 0x7E,
    0x5C, 0x96, 0x15,
    0x66, 0x46, 0xB6,
    0x70, 0x97, 0x5F,
    0x7B, 0x78, 0x11,
    0x86, 0xE8, 0xCD,
    0x92, 0xF9, 0x93,
    0x9F, 0x9A, 0x62,
    0xAC, 0xDB, 0x3A,
    0xBA, 0xAC, 0x1D,
    0xC9, 0x2D, 0x09,
    0xD8, 0x3D, 0xFF,
    0xE7, 0xEF, 0x00,
    0xF8, 0x44, 0x02,
    0x42, 0x54, 0x47,
    0x46, 0xB4, 0x8F,
    0x4B, 0x44, 0xDA,
    0x50, 0x05, 0x27,
    0x54, 0xF5, 0x77,
    0x5A, 0x05, 0xC9,
    0x5F, 0x46, 0x1F,
    0x64, 0xA6, 0x77,
    0x6A, 0x46, 0xD2,
    0x70, 0x07, 0x2F,
    0x75, 0xF7, 0x90,
    0x7C, 0x17, 0xF3,
    0x82, 0x68, 0x59,
    0x88, 0xD8, 0xC2,
    0x8F, 0x89, 0x2E,
    0x96, 0x59, 0x9D,
    0x9D, 0x5A, 0x0F,
    0xA4, 0x9A, 0x83,
    0xAB, 0xFA, 0xFB,
    0xB3, 0x8B, 0x76,
    0xBB, 0x4B, 0xF4,
    0xC3, 0x4C, 0x74,
    0xCB, 0x6C, 0xF8,
    0xD3, 0xBD, 0x7F,
    0xDC, 0x4E, 0x09,
    0xE4, 0xFE, 0x96,
    0xED, 0xEF, 0x27,
    0xF7, 0x0F, 0xBA,
    0xFF, 0xC0, 0x00,
    0x27, 0x46,
};

BYTE code tPCM_INPUTGAMMA_SOFTPROFT[] =
{
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x01,
    0x00, 0x20, 0x04,
    0x00, 0x70, 0x0B,
    0x01, 0x00, 0x17,
    0x01, 0xF0, 0x2A,
    0x03, 0x60, 0x45,
    0x05, 0x60, 0x6A,
    0x08, 0x00, 0x9A,
    0x0B, 0x70, 0xD7,
    0x0F, 0xA1, 0x22,
    0x14, 0xD1, 0x7D,
    0x1B, 0x11, 0xE9,
    0x22, 0x62, 0x68,
    0x2A, 0xF2, 0xFC,
    0x34, 0xD3, 0xA5,
    0x40, 0x24, 0x65,
    0x4C, 0xF5, 0x3E,
    0x5B, 0x56, 0x32,
    0x6B, 0x67, 0x41,
    0x7D, 0x48, 0x6E,
    0x91, 0x09, 0xB9,
    0xA6, 0xBB, 0x25,
    0xBE, 0x8C, 0xB3,
    0xD8, 0x7E, 0x64,
    0xF4, 0xA4, 0x0E,
    0x44, 0xD4, 0x8D,
    0x4D, 0x15, 0x16,
    0x55, 0xF5, 0xAA,
    0x5F, 0x76, 0x48,
    0x69, 0xB6, 0xF1,
    0x74, 0xA7, 0xA5,
    0x80, 0x48, 0x66,
    0x8C, 0xA9, 0x32,
    0x99, 0xDA, 0x0B,
    0xA7, 0xDA, 0xF2,
    0xB6, 0xAB, 0xE5,
    0xC6, 0x4C, 0xE6,
    0xD6, 0xCD, 0xF6,
    0xE8, 0x3F, 0x13,
    0xFA, 0x84, 0x10,
    0x43, 0x74, 0x5F,
    0x48, 0x84, 0xB2,
    0x4D, 0xD5, 0x09,
    0x53, 0x65, 0x64,
    0x59, 0x35, 0xC3,
    0x5F, 0x46, 0x26,
    0x65, 0x96, 0x8E,
    0x6C, 0x36, 0xFA,
    0x73, 0x27, 0x6B,
    0x7A, 0x57, 0xE0,
    0x81, 0xD8, 0x5A,
    0x89, 0x98, 0xD9,
    0x91, 0xB9, 0x5D,
    0x9A, 0x19, 0xE6,
    0xA2, 0xDA, 0x74,
    0xAB, 0xDB, 0x08,
    0xB5, 0x3B, 0xA0,
    0xBE, 0xFC, 0x3E,
    0xC8, 0xFC, 0xE2,
    0xD3, 0x6D, 0x8B,
    0xDE, 0x2E, 0x3A,
    0xE9, 0x3E, 0xEE,
    0xF4, 0xBF, 0xA9,
    0xFF, 0xC0, 0x00,
    0x32, 0x50,
};

BYTE code tPCM_INPUT_GAMMA_REC709GAMMA24[] =
{
    0x00, 0x00, 0x01,
    0x00, 0x30, 0x08,
    0x01, 0x00, 0x1B,
    0x02, 0xA0, 0x3D,
    0x05, 0x50, 0x70,
    0x09, 0x00, 0xB6,
    0x0E, 0x01, 0x0F,
    0x14, 0x41, 0x7E,
    0x1B, 0xE2, 0x04,
    0x25, 0x02, 0xA2,
    0x2F, 0xB3, 0x59,
    0x3B, 0xE4, 0x2A,
    0x49, 0xD5, 0x17,
    0x59, 0x76, 0x1F,
    0x6A, 0xE7, 0x44,
    0x7E, 0x28, 0x87,
    0x93, 0x49, 0xE8,
    0xAA, 0x5B, 0x69,
    0xC3, 0x5D, 0x0A,
    0xDE, 0x6E, 0xCB,
    0xFB, 0x94, 0x2C,
    0x46, 0xB4, 0xAD,
    0x4F, 0x15, 0x37,
    0x57, 0xF5, 0xCA,
    0x61, 0x76, 0x66,
    0x6B, 0x77, 0x0B,
    0x76, 0x17, 0xB9,
    0x81, 0x48, 0x71,
    0x8D, 0x09, 0x32,
    0x99, 0x69, 0xFD,
    0xA6, 0x7A, 0xD2,
    0xB4, 0x1B, 0xB1,
    0xC2, 0x5C, 0x9A,
    0xD1, 0x3D, 0x8E,
    0xE0, 0xBE, 0x8C,
    0xF0, 0xEF, 0x94,
    0x40, 0x74, 0x2A,
    0x44, 0xD4, 0x71,
    0x49, 0x64, 0xBB,
    0x4E, 0x15, 0x08,
    0x53, 0x05, 0x58,
    0x58, 0x15, 0xAA,
    0x5D, 0x56, 0x00,
    0x62, 0xB6, 0x58,
    0x68, 0x56, 0xB3,
    0x6E, 0x17, 0x11,
    0x74, 0x17, 0x72,
    0x7A, 0x37, 0xD5,
    0x80, 0x88, 0x3C,
    0x87, 0x18, 0xA6,
    0x8D, 0xC9, 0x13,
    0x94, 0xA9, 0x83,
    0x9B, 0xC9, 0xF6,
    0xA3, 0x0A, 0x6C,
    0xAA, 0x8A, 0xE5,
    0xB2, 0x3B, 0x62,
    0xBA, 0x1B, 0xE1,
    0xC2, 0x2C, 0x64,
    0xCA, 0x7C, 0xEA,
    0xD2, 0xED, 0x73,
    0xDB, 0x9E, 0x00,
    0xE4, 0x7E, 0x90,
    0xED, 0x9F, 0x23,
    0xF6, 0xEF, 0xB9,
    0xFF, 0xC0, 0x00,
    0x28, 0x47,
};

BYTE code tPCM_INPUT_GAMMA_DCIP3[] =
{
    0x00, 0x00, 0x00,
    0x00, 0x10, 0x04,
    0x00, 0x80, 0x0E,
    0x01, 0x70, 0x22,
    0x03, 0x10, 0x42,
    0x05, 0x70, 0x6F,
    0x08, 0xB0, 0xAC,
    0x0D, 0x00, 0xF9,
    0x12, 0x71, 0x59,
    0x19, 0x01, 0xCC,
    0x20, 0xE2, 0x55,
    0x2A, 0x22, 0xF5,
    0x34, 0xD3, 0xAC,
    0x41, 0x14, 0x7C,
    0x4E, 0xE5, 0x66,
    0x5E, 0x66, 0x6C,
    0x6F, 0xA7, 0x8E,
    0x82, 0xB8, 0xCE,
    0x97, 0x9A, 0x2D,
    0xAE, 0x8B, 0xAB,
    0xC7, 0x6D, 0x49,
    0xE2, 0x5F, 0x0A,
    0xFF, 0x74, 0x3B,
    0x47, 0xB4, 0xBD,
    0x50, 0x15, 0x48,
    0x59, 0x15, 0xDC,
    0x62, 0xA6, 0x7A,
    0x6C, 0xC7, 0x21,
    0x77, 0x97, 0xD3,
    0x83, 0x08, 0x8F,
    0x8F, 0x19, 0x55,
    0x9B, 0xCA, 0x26,
    0xA9, 0x3B, 0x02,
    0xB7, 0x4B, 0xE9,
    0xC6, 0x1C, 0xDB,
    0xD5, 0x9D, 0xD9,
    0xE5, 0xCE, 0xE3,
    0xF6, 0xCF, 0xF8,
    0x42, 0x24, 0x46,
    0x46, 0xC4, 0x92,
    0x4B, 0x94, 0xE0,
    0x50, 0x95, 0x32,
    0x55, 0xC5, 0x87,
    0x5B, 0x35, 0xDF,
    0x60, 0xD6, 0x3B,
    0x66, 0xA6, 0x9A,
    0x6C, 0xA6, 0xFC,
    0x72, 0xE7, 0x62,
    0x79, 0x67, 0xCB,
    0x80, 0x18, 0x38,
    0x86, 0xF8, 0xA8,
    0x8E, 0x19, 0x1C,
    0x95, 0x79, 0x93,
    0x9D, 0x0A, 0x0F,
    0xA4, 0xEA, 0x8E,
    0xAC, 0xEB, 0x10,
    0xB5, 0x3B, 0x97,
    0xBD, 0xCC, 0x21,
    0xC6, 0x8C, 0xB0,
    0xCF, 0x8D, 0x42,
    0xD8, 0xDD, 0xD8,
    0xE2, 0x5E, 0x73,
    0xEC, 0x1F, 0x11,
    0xF6, 0x2F, 0xB4,
    0xFF, 0xC0, 0x00,
    0x2C, 0x4B,
};

BYTE code tPCM_INPUTGAMMA_SMPTEC[] =
{
    0x00, 0x00, 0x02,
    0x00, 0x70, 0x11,
    0x02, 0x00, 0x34,
    0x04, 0xE0, 0x6E,
    0x09, 0x40, 0xBF,
    0x0F, 0x11, 0x29,
    0x16, 0x81, 0xAD,
    0x1F, 0x92, 0x4C,
    0x2A, 0x53, 0x06,
    0x36, 0xE3, 0xDD,
    0x45, 0x34, 0xD0,
    0x55, 0x55, 0xE1,
    0x67, 0x57, 0x10,
    0x7B, 0x38, 0x5D,
    0x90, 0xF9, 0xCA,
    0xA8, 0xCB, 0x55,
    0xC2, 0x7D, 0x01,
    0xDE, 0x3E, 0xCD,
    0xFB, 0xF4, 0x2E,
    0x46, 0xF4, 0xB2,
    0x4F, 0x65, 0x3E,
    0x58, 0x65, 0xD2,
    0x61, 0xF6, 0x6E,
    0x6C, 0x07, 0x14,
    0x76, 0x97, 0xC1,
    0x81, 0xC8, 0x78,
    0x8D, 0x69, 0x37,
    0x99, 0xAA, 0x00,
    0xA6, 0x7A, 0xD1,
    0xB3, 0xCB, 0xAB,
    0xC1, 0xBC, 0x8E,
    0xD0, 0x3D, 0x7A,
    0xDF, 0x4E, 0x70,
    0xEE, 0xEF, 0x6E,
    0xFF, 0x14, 0x1E,
    0x44, 0x04, 0x62,
    0x48, 0x54, 0xA9,
    0x4C, 0xD4, 0xF2,
    0x51, 0x75, 0x3D,
    0x56, 0x45, 0x8B,
    0x5B, 0x35, 0xDB,
    0x60, 0x46, 0x2E,
    0x65, 0x86, 0x83,
    0x6A, 0xE6, 0xDA,
    0x70, 0x77, 0x34,
    0x76, 0x27, 0x90,
    0x7C, 0x07, 0xEF,
    0x82, 0x08, 0x51,
    0x88, 0x28, 0xB4,
    0x8E, 0x79, 0x1B,
    0x94, 0xF9, 0x84,
    0x9B, 0x99, 0xEF,
    0xA2, 0x6A, 0x5D,
    0xA9, 0x5A, 0xCD,
    0xB0, 0x6B, 0x40,
    0xB7, 0xAB, 0xB6,
    0xBF, 0x1C, 0x2E,
    0xC6, 0xBC, 0xA8,
    0xCE, 0x7D, 0x26,
    0xD6, 0x5D, 0xA5,
    0xDE, 0x6E, 0x28,
    0xE6, 0xAE, 0xAD,
    0xEF, 0x0F, 0x34,
    0xF7, 0x9F, 0xBF,
    0xFF, 0xC0, 0x00,
    0x24, 0x44,
};

BYTE code tPCM_INPUTGAMMA_DISPLAYP3[] =
{
    0x00, 0x00, 0x28,
    0x04, 0xF0, 0x77,
    0x09, 0xF0, 0xC6,
    0x0F, 0x01, 0x1F,
    0x15, 0x21, 0x8A,
    0x1C, 0x82, 0x0B,
    0x25, 0x32, 0xA1,
    0x2F, 0x53, 0x4E,
    0x3A, 0xD4, 0x12,
    0x47, 0xD4, 0xEE,
    0x56, 0x65, 0xE4,
    0x66, 0x86, 0xF3,
    0x78, 0x58, 0x1D,
    0x8B, 0xC9, 0x62,
    0xA0, 0xFA, 0xC3,
    0xB7, 0xEC, 0x40,
    0xD0, 0x9D, 0xDA,
    0xEB, 0x3F, 0x92,
    0x41, 0xE4, 0x5A,
    0x49, 0x84, 0xD8,
    0x51, 0x95, 0x5D,
    0x5A, 0x25, 0xEA,
    0x63, 0x46, 0x7F,
    0x6C, 0xD7, 0x1D,
    0x76, 0xF7, 0xC3,
    0x81, 0x98, 0x71,
    0x8C, 0xC9, 0x28,
    0x98, 0x79, 0xE8,
    0xA4, 0xCA, 0xB1,
    0xB1, 0x9B, 0x83,
    0xBE, 0xFC, 0x5E,
    0xCC, 0xED, 0x42,
    0xDB, 0x7E, 0x2F,
    0xEA, 0x9F, 0x25,
    0xFA, 0x44, 0x09,
    0x42, 0xA4, 0x4C,
    0x46, 0xE4, 0x91,
    0x4B, 0x44, 0xD8,
    0x4F, 0xD5, 0x22,
    0x54, 0x85, 0x6E,
    0x59, 0x55, 0xBD,
    0x5E, 0x56, 0x0E,
    0x63, 0x86, 0x62,
    0x68, 0xD6, 0xB9,
    0x6E, 0x57, 0x12,
    0x73, 0xF7, 0x6E,
    0x79, 0xD7, 0xCC,
    0x7F, 0xC8, 0x2D,
    0x85, 0xF8, 0x91,
    0x8C, 0x48, 0xF8,
    0x92, 0xC9, 0x61,
    0x99, 0x79, 0xCD,
    0xA0, 0x4A, 0x3C,
    0xA7, 0x4A, 0xAE,
    0xAE, 0x7B, 0x22,
    0xB5, 0xDB, 0x99,
    0xBD, 0x6C, 0x14,
    0xC5, 0x2C, 0x91,
    0xCD, 0x0D, 0x10,
    0xD5, 0x2D, 0x93,
    0xDD, 0x6E, 0x19,
    0xE5, 0xDE, 0xA2,
    0xEE, 0x8F, 0x2E,
    0xF7, 0x5F, 0xBD,
    0xFF, 0xC0, 0x00,
    0x23, 0x44,
};

BYTE code tPCM_INPUT_GAMMA_BYPASS[] =
{
    0x00, 0x02, 0x00,
    0x40, 0x06, 0x00,
    0x80, 0x0A, 0x00,
    0xC0, 0x0E, 0x00,
    0x40, 0x04, 0x80,
    0x50, 0x05, 0x80,
    0x60, 0x06, 0x80,
    0x70, 0x07, 0x80,
    0x80, 0x08, 0x80,
    0x90, 0x09, 0x80,
    0xA0, 0x0A, 0x80,
    0xB0, 0x0B, 0x80,
    0xC0, 0x0C, 0x80,
    0xD0, 0x0D, 0x80,
    0xE0, 0x0E, 0x80,
    0xF0, 0x0F, 0x80,
    0x40, 0x04, 0x20,
    0x44, 0x04, 0x60,
    0x48, 0x04, 0xA0,
    0x4C, 0x04, 0xE0,
    0x50, 0x05, 0x20,
    0x54, 0x05, 0x60,
    0x58, 0x05, 0xA0,
    0x5C, 0x05, 0xE0,
    0x60, 0x06, 0x20,
    0x64, 0x06, 0x60,
    0x68, 0x06, 0xA0,
    0x6C, 0x06, 0xE0,
    0x70, 0x07, 0x20,
    0x74, 0x07, 0x60,
    0x78, 0x07, 0xA0,
    0x7C, 0x07, 0xE0,
    0x80, 0x08, 0x20,
    0x84, 0x08, 0x60,
    0x88, 0x08, 0xA0,
    0x8C, 0x08, 0xE0,
    0x90, 0x09, 0x20,
    0x94, 0x09, 0x60,
    0x98, 0x09, 0xA0,
    0x9C, 0x09, 0xE0,
    0xA0, 0x0A, 0x20,
    0xA4, 0x0A, 0x60,
    0xA8, 0x0A, 0xA0,
    0xAC, 0x0A, 0xE0,
    0xB0, 0x0B, 0x20,
    0xB4, 0x0B, 0x60,
    0xB8, 0x0B, 0xA0,
    0xBC, 0x0B, 0xE0,
    0xC0, 0x0C, 0x20,
    0xC4, 0x0C, 0x60,
    0xC8, 0x0C, 0xA0,
    0xCC, 0x0C, 0xE0,
    0xD0, 0x0D, 0x20,
    0xD4, 0x0D, 0x60,
    0xD8, 0x0D, 0xA0,
    0xDC, 0x0D, 0xE0,
    0xE0, 0x0E, 0x20,
    0xE4, 0x0E, 0x60,
    0xE8, 0x0E, 0xA0,
    0xEC, 0x0E, 0xE0,
    0xF0, 0x0F, 0x20,
    0xF4, 0x0F, 0x60,
    0xF8, 0x0F, 0xA0,
    0xFC, 0x0F, 0xE0,
    0xFF, 0xC0, 0x00,
    0x07, 0x1F,
};

code BYTE *tPCM_INPUTGAMMA[] =
{
    tPCM_INPUTGAMMA_SRGB,
    tPCM_INPUTGAMMA_ADOBERGB,
    tPCM_INPUTGAMMA_SRGB, // UserDefine
    tPCM_INPUTGAMMA_EBU,
    tPCM_INPUTGAMMA_SOFTPROFT,
    tPCM_INPUT_GAMMA_REC709GAMMA24,
    tPCM_INPUT_GAMMA_DCIP3,
    tPCM_INPUTGAMMA_SMPTEC,
    tPCM_INPUT_GAMMA_DCIP3, // UserDefine2
    tPCM_INPUTGAMMA_SMPTEC, // UserDefine3
    tPCM_INPUT_GAMMA_DCIP3, // UserDefine4
    tPCM_INPUTGAMMA_EBU, // UserDefine5
    tPCM_INPUT_GAMMA_REC709GAMMA24, // UserDefine6
    tPCM_INPUTGAMMA_DISPLAYP3,
    tPCM_INPUT_GAMMA_BYPASS,
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
WORD ScalerColorPCMGetTableAddress(EnumPCMType enumPCMMode);
BYTE ScalerColorPCMGetTableBank(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set PCM(Input Gamma, Output Gamma, Color Matrix)
// Input Value  : PCM Type --> sRGB / AdobeRGB
// Output Value : PCM table address
//--------------------------------------------------
WORD ScalerColorPCMGetTableAddress(EnumPCMType enumPCMMode)
{
    return (WORD)tPCM_INPUTGAMMA[enumPCMMode];
}

//--------------------------------------------------
// Description  : Set PCM(Input Gamma, Output Gamma, Color Matrix)
// Input Value  : None
// Output Value : PCM table bank
//--------------------------------------------------
BYTE ScalerColorPCMGetTableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}
