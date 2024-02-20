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
// ID Code      : RTD2014OsdFontVLC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDFONTVLC__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//        0x0f,0x81,0x7e,0x3c,0x9d,0xba,0x24,0x56,0x01,0x61,0x00,0x90,
//        0x84,0x24,0x21,0x49,0x48,0x12,0x92,0xeb,0x21,0xa9,0x22,0xa9,
//        0x22,0x00,0x90,0x24,0x49,0x92,0x24,0xe4,0x24,0xc8,0x72,0x48,
//        0x2a,0x4c,0x56,0x4e,0xf5,0x0e,0x00,0x24,0x49,0x92,0x24,0x09,
//        0x91,0x00,0x00,0x00,0x00,0x40,0x92,0x24,0x49,0x92,0x10,0x09,
//        0x00,0x00,0x00,0x00,0x24,0x49,0x92,0x24,0x89,0x8e,0xc4,0x6c,
//        0x74,0x82,0x49,0xd8,0x39,0xab,0x05,0x00,0x42,0x92,0x90,0x24,
//        0x24,0x09,0x49,0xc2,0x9d,0x84,0xbe,0x12,0xba,0x93,0x2a,0x92,
//        0x2a,0x92,0x2a,0x92,0x2a,0x92,0x2a,0x92,0x2a,0x92,0x2a,0x92,
//        0x2a,0x92,0x2a,0x32,0x59,0xa4,0x13,0xb6,0x09,0xf4,0x06,0x00,
//        0x00,0x00,0x00,0xe0,0x14,0x64,0x39,0x24,0x15,0x26,0x2b,0xa7,
//        0x7a,0x67,0xb2,0x48,0x27,0x6c,0x13,0x00,0x1a,0xcc,0x46,0x27,
//        0x98,0x84,0x9d,0xb3,0x5a,0xa2,0x66,0xe7,0x90,0x2c,0x24,0x15,
//        0x35,0x3b,0x87,0x64,0x21,0x29,0x9c,0x05,0x0a,0x00,0x00,0x40,
//        0xe8,0x4e,0xe8,0x4e,0xe8,0x4e,0xe8,0x4e,0xe8,0x4e,0xe8,0x4e,
//        0xe8,0x4e,0xe8,0x4e,0xe8,0x4e,0xaa,0x48,0xaa,0x48,0xaa,0x48,
//        0xaa,0x48,0xaa,0x48,0xaa,0x48,0xaa,0x48,0xaa,0x48,0xaa,0x08,
//        0x00,0x00,0x80,0x06,0xb3,0xd1,0x09,0x26,0x61,0xe7,0xac,0x96,
//        0x4e,0x30,0x09,0x3b,0x67,0xb5,0x44,0xcd,0xce,0x21,0x59,0x48,
//        0x0a,0x67,0x81,0x02,0x14,0x49,0x2d,0x92,0x93,0xb2,0x27,0x59,
//        0x47,0x67,0x27,0x8c,0x84,0xb6,0x07,0x34,0x00,0x00,0x00,0x00,
//        0x14,0x58,0x47,0x91,0x58,0x24,0x27,0x65,0x4f,0x42,0x77,0x42,
//        0x77,0x42,0x77,0x42,0x77,0x42,0x77,0x42,0x77,0x42,0x77,0x42,
//        0x77,0x42,0x77,0x52,0x45,0x72,0x15,0x49,0x1e,0x92,0x84,0x24,
//        0x21,0x49,0x48,0x12,0x02,0x00,0x51,0xb3,0x73,0x48,0x16,0x92,
//        0xc2,0x59,0x12,0x29,0x49,0x92,0x24,0x49,0x02,0x00,0x00,0x00,
//        0x00,0x89,0x90,0x24,0x49,0x92,0x24,0x00,0x00,0x00,0x00,0x90,
//        0x08,0x49,0x92,0x24,0x49,0x02,0x00,0x59,0x47,0x67,0x27,0x8c,
//        0x84,0xb6,0x07,0x49,0x87,0x24,0x49,0x92,0x24,0x01,0x80,0xd0,
//        0x9d,0x70,0x75,0x42,0xee,0x84,0x24,0x21,0x49,0x48,0x12,0x92,
//        0x00,0xc0,0xff,


BYTE code tICON_REALTEK_1BIT_LOGO0[]=
{
    0x0f,0x3c,0xe1,0x87,0x4d,0x25,0x69,0xab,0x04,0xe0,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x93,
    0x74,0x93,0x74,0x93,0x74,0x93,0x74,0x93,0x74,0x93,0x74,0x93,
    0x74,0x92,0x24,0x49,0x92,0x54,0x42,0x55,0x42,0x55,0x42,0x55,
    0x42,0x55,0x42,0x55,0x42,0x01,0x49,0x92,0x24,0x49,0x92,0x24,
    0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,
    0x4d,0xd2,0x49,0x92,0x24,0x49,0x02,0x00,0x00,0x00,0x00,0x40,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x25,0x54,0x92,0x24,0x49,0x92,
    0x34,0x49,0x37,0x49,0x37,0x49,0x37,0x49,0x37,0x49,0x37,0x49,
    0x03,0x49,0x92,0x24,0x49,0x52,0x09,0x55,0x09,0x55,0x09,0x55,
    0x09,0x55,0x09,0x55,0x09,0x55,0x09,0xd5,0x24,0xdd,0x24,0xdd,
    0x24,0xdd,0x24,0xdd,0x24,0xdd,0x24,0xdd,0x24,0xdd,0x24,0x9d,
    0x24,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x34,0x49,0x37,
    0x49,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x90,0x64,0xad,0x00,0x00,0x00,0x00,0x00,0x00,0xa4,0x3b,0x49,
    0x25,0x54,0x25,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xaa,0x50,0x09,0x55,0x09,0x55,0x09,0x55,0x09,
    0x55,0x09,0x55,0x09,0x55,0x09,0x55,0x09,0x95,0x24,0x09,0x66,
    0x60,0x06,0x66,0x60,0x06,0x66,0x60,0x06,0x66,0x60,0x06,0x66,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x49,0xd6,0x4a,0x92,0xb5,
    0x92,0x64,0xad,0x24,0x59,0x2b,0x49,0xd6,0x4a,0x92,0xb5,0x92,
    0x64,0xad,0x24,0x59,0x2b,0x49,0xd6,0x4a,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0xac,0x64,0xd0,0x03,0x7b,
    0x83,0x2d,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x95,0x24,0xb1,0x72,0x12,0x4e,0x25,0x9c,0x74,0x27,
    0x49,0x77,0x92,0x74,0x27,0x49,0x77,0x92,0x74,0x27,0x49,0x77,
    0x92,0x74,0x27,0x49,0x77,0x92,0x74,0x27,0x51,0x05,0x55,0x50,
    0x05,0x55,0x50,0x05,0x55,0x50,0x05,0x55,0x50,0x05,0xcc,0xc0,
    0x0c,0xcc,0xc0,0x0c,0xcc,0xc0,0x0c,0x64,0x34,0xc9,0x0e,0xc9,
    0x24,0x59,0x2b,0x27,0x21,0x2b,0xa1,0x9c,0xc0,0x2a,0x00,0x00,
    0x00,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0xe4,0x24,0x49,0x56,0xe5,0x24,0x64,0x25,0x14,0x80,0x0d,
    0xf6,0x86,0x69,0x4d,0xa2,0x49,0xba,0x49,0xba,0x49,0xba,0x49,
    0xba,0x12,0xea,0x24,0xd4,0x49,0x38,0x49,0x96,0x24,0x49,0x25,
    0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,
    0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,
    0x49,0x92,0x24,0x93,0x24,0xe9,0x4e,0x92,0xee,0x24,0xe9,0x4e,
    0x92,0xdd,0x49,0x86,0x24,0x9b,0xa4,0x31,0x81,0xdd,0x00,0x55,
    0x50,0x05,0x55,0x50,0x05,0x55,0x50,0x05,0x39,0xa8,0x84,0x95,
    0x84,0x93,0xde,0x49,0x92,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x00,0x00,
    0x7a,0x43,0x46,0x93,0xec,0x90,0x4c,0x7a,0x27,0x49,0x26,0x49,
    0x92,0x24,0x4e,0x60,0x15,0x00,0x00,0x00,0x00,0x00,0x48,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x04,0x00,0x80,
    0x24,0x49,0x9a,0xa4,0x9b,0xa4,0x9b,0xa4,0x9b,0xa4,0x9b,0xa4,
    0x01,0x00,0x48,0x92,0x24,0xbb,0x93,0x0c,0x49,0x36,0x49,0x63,
    0x02,0xbb,0x01,0x00,0x00,0x00,0x80,0x5a,0x90,0x83,0x4a,0x58,
    0x49,0x38,0x49,0x6a,0x25,0x49,0x4e,0x92,0x24,0x49,0x52,0x2b,
    0x49,0x72,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0xb2,0x49,0x1a,0x13,0xd8,0x4d,0x2d,
    0x00,0x00,0x00,0x00,0x4d,0xd2,0x4d,0xd2,0x4d,0xd2,0x4d,0xd2,
    0x49,0x92,0x24,0x49,0xb2,0x12,0xca,0x09,0xac,0x02,0x00,0x00,
    0x40,0x92,0x24,0x49,0x92,0x64,0x92,0x24,0xbb,0x93,0x0c,0x49,
    0x36,0x49,0x63,0x02,0xbb,0x01,0x00,0x00,0x00,0x40,0x25,0x54,
    0x25,0x54,0x25,0x54,0x25,0x54,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x2b,0xa1,0x9c,0xc0,0x2a,0xa0,0xb7,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x27,0xc9,0xee,0x24,0x43,
    0x92,0x4d,0xd2,0x98,0xc0,0x6e,0x6a,0x41,0x0e,0x2a,0x61,0x55,
    0x42,0xc9,0x41,0x25,0xac,0x24,0x9c,0x24,0xb5,0x92,0x24,0x27,
    0x99,0x24,0xc9,0xee,0x24,0x43,0x92,0x4d,0xd2,0x49,0x92,0x24,
    0x49,0xb2,0x49,0x1a,0x13,0xd8,0x0d,0x00,0x80,0x24,0x9c,0x24,
    0x49,0x92,0x24,0x01,0x00,0x00,0x00,0x80,0x24,0x49,0x9a,0xa4,
    0x9b,0xa4,0x9b,0xa4,0x9b,0xa4,0x9b,0xa4,0x9b,0xa4,0x9b,0xa4,
    0x9b,0xa4,0x9b,0xa4,0x01,0xa0,0x12,0xaa,0x12,0xaa,0x12,0x0a,
    0x00,0x00,0x00,0x00,0x9a,0xa4,0x9b,0xa4,0x9b,0xa4,0x01,0x00,
    0x00,0xb2,0x3b,0xc9,0x90,0x64,0x73,0xd2,0x50,0x00,0x00,0x00,
    0x00,0x00,0xa8,0x84,0xaa,0x84,0xaa,0x84,0xaa,0x84,0xaa,0x84,
    0xaa,0x84,0xaa,0x84,0x02,0x80,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0xa4,0x12,0xaa,
    0x12,0x2a,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x95,0x50,
    0x4e,0x60,0x15,0x00,0x00,0x08,0xc9,0x20,0xa3,0x49,0x76,0x48,
    0x26,0xbd,0x93,0x24,0x93,0x24,0xc9,0x49,0x92,0xac,0xca,0x49,
    0xc8,0x4a,0xa8,0x24,0xab,0x72,0x12,0xb2,0x12,0xca,0x09,0xac,
    0x02,0x7a,0x43,0x46,0x93,0xec,0x26,0xe9,0x4a,0xa8,0x4a,0xa8,
    0x4a,0xa8,0x4a,0xa8,0x4a,0xa8,0x4a,0xa8,0x4a,0xa8,0x4a,0xa8,
    0x4a,0x28,0x4c,0x60,0x37,0xb5,0x20,0x07,0x95,0xb0,0x2a,0xa1,
    0x2a,0xa1,0x2a,0xa1,0x2a,0xa1,0x92,0xd4,0x4a,0x92,0x9c,0x6c,
    0x92,0xc6,0x04,0x76,0x53,0x0b,0x72,0x50,0x09,0xab,0x12,0x2a,
    0x49,0x92,0x24,0x49,0x00,0x00,0x48,0x92,0x24,0x49,0x92,0x24,
    0x49,0xd0,0x03,0x00,0x00,0x00,0x00,0x00,0xa0,0x49,0x1a,0x00,
    0xb0,0xc1,0xb4,0x4d,0x62,0x48,0x3a,0x5b,0x92,0x4c,0x27,0x49,
    0x92,0x04,0x00,0x00,0x00,0xb0,0xc0,0x29,0xac,0x04,0x27,0xd9,
    0x0a,0x00,0x2e,0xd0,0x2c,0xdd,0x9c,0xea,0x26,0xe9,0x26,0xe9,
    0x26,0xe9,0x26,0xe9,0x24,0x49,0x92,0x24,0x01,0x00,0x20,0x49,
    0x92,0x24,0x49,0x92,0x24,0x51,0x07,0xe9,0x9d,0x24,0x99,0x24,
    0x2b,0xa1,0x9c,0xc0,0x2a,0xa0,0x37,0x64,0x34,0xc9,0x6e,0x92,
    0x76,0x02,0xab,0x80,0xde,0x90,0xd1,0x24,0xbb,0x49,0xba,0x49,
    0xba,0x49,0xba,0x49,0xba,0x12,0xaa,0x12,0xaa,0x12,0xaa,0x12,
    0xaa,0x12,0x2a,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x04,
    0x36,0xa0,0x12,0xaa,0x12,0xaa,0x12,0xaa,0x12,0xaa,0x12,0xaa,
    0x12,0xaa,0x12,0xaa,0x49,0xba,0x49,0xba,0x49,0xba,0x49,0xba,
    0x49,0x3a,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x04,0x00,
    0x00,0x00,0x00,0x00,0x20,0x49,0x92,0x24,0xe9,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x54,0x42,0x55,0x42,0x01,0x00,0x00,0x00,0x40,
    0x92,0x24,0x49,0x92,0x24,0x49,0x52,0x09,0x55,0x09,0x55,0x09,
    0x55,0x09,0x55,0x09,0x55,0x09,0x95,0x24,0x09,0x0b,0x40,0x93,
    0x74,0x93,0x74,0x93,0x74,0x93,0x74,0x93,0x74,0x93,0x74,0x93,
    0x74,0x93,0x74,0x93,0x74,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0xf2,0xff,
};

BYTE code tICON_REALTEK_1BIT_LOGO1[]=
{
    0x0f,0x3c,0x17,0x8e,0x2d,0x45,0x69,0xab,0x04,0x5c,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x90,0x24,0x49,0x92,0x24,0x49,0x92,
    0x48,0x08,0x03,0x00,0x00,0x00,0xa4,0x35,0xc9,0x3e,0x24,0x27,
    0x49,0x92,0x24,0x2b,0x59,0x89,0xc9,0x24,0x94,0x5a,0x30,0x03,
    0x00,0x00,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0xc9,0x4a,0x92,0x54,0x25,0xc9,0x4c,0x42,
    0x92,0x6c,0x49,0xb2,0x77,0x92,0xf4,0x4e,0x92,0xee,0x24,0xe9,
    0x4e,0x92,0xee,0x24,0xe9,0x4e,0x92,0xdd,0x49,0x56,0x42,0x56,
    0xc2,0xaa,0x84,0x55,0x09,0x35,0x09,0x35,0x09,0x33,0x09,0x33,
    0x09,0x33,0x09,0xd3,0x24,0xdd,0x24,0xdd,0x24,0xdd,0x24,0xdd,
    0x24,0xdd,0x24,0xdd,0x24,0xdd,0x24,0xdd,0x24,0x0d,0x00,0x00,
    0x00,0x00,0x95,0x50,0x95,0x50,0x95,0x50,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x39,0x49,0xd2,0x24,0xbd,0x49,0x36,0x12,0x38,0x81,
    0x3e,0xd0,0x0d,0x7b,0x03,0x80,0x4a,0xa8,0x49,0x18,0x09,0xac,
    0x05,0x55,0x30,0x03,0x00,0x00,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x6b,
    0x25,0x49,0x55,0x2a,0xa1,0x2a,0xa1,0x2a,0xa1,0x2a,0xa1,0x2a,
    0xa1,0x2a,0xa1,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x9f,0x24,0xb1,0x93,0x34,0xc9,0x49,0x9f,0x24,0xb1,0x93,0x34,
    0xc9,0x41,0xb2,0xd1,0x07,0x6c,0x00,0x00,0x00,0x00,0xa0,0x06,
    0xb2,0x50,0x09,0x93,0x84,0x95,0xa4,0x26,0x49,0xb2,0x92,0x84,
    0x95,0xa4,0x26,0x49,0xb2,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x02,0x00,0x40,0xf6,
    0x4e,0x12,0x3b,0x49,0x48,0x72,0x48,0xce,0x26,0x69,0x74,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,0x35,0xa8,0x84,0xaa,
    0x84,0x5a,0x09,0x6b,0x25,0xac,0x24,0x23,0x49,0x6a,0x92,0x64,
    0x55,0x92,0x24,0x49,0x92,0xa4,0x12,0xaa,0x12,0xaa,0x12,0xaa,
    0x12,0xaa,0x12,0xaa,0x12,0xaa,0x12,0xaa,0x12,0xaa,0x12,0x2a,
    0x7d,0x92,0xa4,0x3b,0x49,0xf6,0x4e,0x12,0x92,0x1c,0x92,0xd3,
    0x24,0x67,0x93,0xf4,0x26,0xd9,0x48,0x00,0xea,0x82,0xb5,0x20,
    0xc1,0x24,0x4c,0x25,0xcc,0x4a,0xa8,0x95,0xb0,0x92,0x10,0x00,
    0xc0,0x06,0xbd,0xe1,0x34,0xe4,0x40,0x62,0x93,0xec,0x26,0xe9,
    0x24,0x53,0x49,0x62,0xb2,0x12,0x52,0x09,0x6b,0x12,0x4a,0xc2,
    0x58,0x81,0x5a,0x30,0x85,0x24,0x49,0x92,0x24,0x49,0x92,0x24,
    0x7d,0x92,0xc4,0x4e,0xd2,0x24,0x07,0xc9,0x46,0x1f,0xb0,0x21,
    0xd9,0xe8,0x03,0x36,0x00,0x00,0xd4,0x40,0x16,0x2a,0x61,0xd4,
    0x40,0x16,0x2a,0x61,0x92,0xb0,0x92,0xd4,0x24,0x49,0x56,0x92,
    0x24,0x49,0x92,0x24,0x49,0x12,0x00,0x00,0x64,0x90,0x64,0x64,
    0x25,0x64,0x12,0xca,0x0a,0x4c,0x61,0xb2,0xb0,0x12,0x2a,0xc9,
    0x9a,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x39,0x27,0x49,0xfa,0x24,0xc9,0xee,0x24,0xd9,0x3b,
    0x09,0xce,0x81,0x3e,0xb0,0x1b,0xf6,0x66,0xc0,0x0c,0x54,0xc1,
    0x5a,0x90,0x85,0x24,0x33,0x49,0x52,0x95,0x24,0xab,0x92,0x24,
    0x2b,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x1c,0x92,0x0e,0xc9,0xc9,0x96,0x24,0x7b,0x27,0x49,0x77,0x92,
    0x9c,0x93,0x24,0x39,0x49,0x92,0x24,0x49,0x92,0xc4,0x0c,0x00,
    0x00,0x00,0x00,0x00,0x1b,0xf4,0x96,0x24,0x49,0x92,0x24,0x49,
    0xd6,0x4a,0x92,0xaa,0x24,0x99,0x49,0x12,0xb2,0x12,0x56,0x25,
    0xd4,0x24,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x7a,0x5b,0x09,
    0x6b,0x12,0x4a,0xc2,0xa8,0x05,0x33,0x00,0x00,0x00,0x48,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0xc9,0x4a,
    0x92,0x4c,0x25,0x89,0x49,0x25,0x2c,0xf4,0x86,0x1c,0x4d,0xb2,
    0x43,0x72,0xd2,0x3b,0x49,0x72,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x00,0x00,0x00,0x00,0x80,0xde,0x90,0xa3,0x49,0x76,
    0x92,0x95,0x24,0x99,0xca,0x4a,0xc8,0x24,0x94,0x15,0x98,0x02,
    0x00,0x00,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x64,0x25,0x49,0xa6,0xb2,0x12,0x12,0x92,
    0x1c,0x92,0xd3,0x24,0x67,0x93,0xf4,0x26,0xd9,0x48,0xe0,0x1c,
    0xe8,0x86,0xdd,0x00,0x00,0x00,0x00,0x20,0x49,0x4d,0x92,0xac,
    0x4a,0x92,0xb5,0x02,0x00,0x00,0x00,0x00,0x87,0xe4,0x84,0x24,
    0xd9,0x3b,0x89,0x84,0xb1,0x02,0xb5,0x60,0x0a,0x0c,0x00,0x00,
    0x00,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,
    0x49,0xb2,0x92,0x24,0xb5,0x92,0x64,0x2a,0x49,0x4c,0x70,0xda,
    0x26,0xd1,0x24,0x3b,0x24,0x27,0x5b,0x92,0x9c,0x4e,0x92,0x9c,
    0x24,0x49,0x92,0x24,0x49,0x02,0x00,0x00,0x00,0x00,0x00,0x7a,
    0xc3,0x69,0x12,0xc6,0x0a,0x4c,0x01,0x00,0x00,0x00,0x00,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0xd4,0x4a,0x12,
    0x93,0x95,0x90,0x49,0x28,0x09,0x42,0x72,0xd2,0x3b,0x49,0x72,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x09,0x00,0x00,0xe8,0x0d,0x39,0x9a,0x64,0x87,0xe4,
    0xa4,0x77,0x92,0xe4,0x24,0x99,0x84,0xb2,0x02,0x53,0x00,0x00,
    0x00,0x00,0x80,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0xc9,0x4a,
    0x92,0x4c,0x65,0x25,0x64,0x12,0xca,0x0a,0x4c,0xa1,0x12,0xaa,
    0x12,0xaa,0x12,0x0a,0x00,0x00,0x00,0x00,0x92,0x24,0x49,0x92,
    0x24,0x49,0x12,0x00,0x00,0x00,0x00,0x48,0x92,0x24,0x49,0x92,
    0x9c,0x93,0x24,0xdd,0x49,0xb2,0x3b,0x49,0xec,0x24,0x21,0xc9,
    0x21,0x39,0x4d,0xd2,0xb0,0x99,0x81,0x2a,0x58,0x05,0x59,0x90,
    0x60,0x12,0xa6,0x12,0x6a,0x25,0xac,0xf4,0x4e,0x92,0xd3,0x49,
    0x92,0x93,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,
    0x49,0x92,0x24,0x49,0x00,0x00,0x00,0xb0,0x37,0x74,0xc3,0x69,
    0xc8,0xb1,0x49,0x24,0x21,0x2b,0x61,0x55,0x42,0x4d,0xc2,0x48,
    0x60,0x2d,0xa8,0x82,0x19,0x00,0x49,0x92,0x24,0x49,0x92,0x24,
    0x49,0x25,0x54,0x25,0x54,0x25,0x54,0x25,0x54,0x25,0x54,0x25,
    0xd4,0x26,0xd1,0x24,0x1d,0x92,0x93,0xbd,0x93,0xe4,0x74,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x12,0x00,0x00,0x00,
    0x00,0x40,0x6f,0x38,0xc7,0x26,0xa1,0x16,0x18,0x00,0x00,0x00,
    0x00,0x00,0x90,0x24,0x49,0x92,0x24,0x49,0x56,0x92,0x64,0x2a,
    0x2b,0x21,0x95,0xb0,0x24,0x8c,0xb5,0x60,0x0a,0xff,
};





BYTE code tFONT1_GLOBAL[]=
{
    0x0f,0x7e,0x83,0xc1,0x64,0x29,0xba,0x5d,0x02,0xce,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xec,0x7d,0xce,0x64,
    0xef,0x73,0xfe,0x32,0xdb,0x49,0xcd,0x50,0xb5,0x87,0x02,0x00,
    0x00,0x00,0x00,0xc0,0xed,0x30,0xdd,0x6b,0x0d,0x00,0x00,0xc0,
    0x99,0x59,0xeb,0x64,0x66,0xad,0x4f,0xcc,0x59,0x69,0xce,0xe9,
    0xe6,0x9c,0x06,0x00,0x00,0x00,0x00,0x05,0xaa,0xa0,0x0a,0x00,
    0x00,0x00,0x00,0x10,0x42,0xed,0x99,0x64,0xed,0x3d,0xb3,0x00,
    0x00,0x00,0x00,0x00,0x00,0xd2,0xbd,0x56,0x00,0x00,0x00,0x00,
    0x00,0x00,0xd6,0x60,0x01,0x00,0x00,0x00,0x00,0x00,0xd4,0x0c,
    0x05,0x00,0x00,0x00,0x00,0x00,0x90,0xe4,0x9c,0x00,0x00,0x00,
    0x00,0x00,0x00,0x54,0xd2,0x5d,0x00,0x00,0x00,0x00,0x00,0x00,
    0x35,0xb3,0x77,0x01,0x00,0x00,0x00,0x00,0x00,0xa0,0xd6,0x9c,
    0x34,0x4b,0x02,0x09,0x54,0xad,0x93,0xd4,0xb5,0xaf,0xaa,0xab,
    0x3e,0xef,0x7c,0xae,0xeb,0xfb,0xdd,0x5f,0x97,0xe7,0xfb,0xc0,
    0xe3,0xbe,0xcf,0x91,0x7d,0x9f,0xc3,0xd2,0x4c,0x2a,0x91,0xee,
    0x54,0xea,0xea,0x24,0xae,0xab,0xf2,0xa8,0xaa,0x02,0x6c,0x6a,
    0x35,0x92,0x41,0x87,0x3d,0xdd,0xc9,0xba,0xe8,0xfe,0x7b,0x39,
    0x7f,0xbf,0x1f,0xeb,0xe7,0xee,0xfe,0xdd,0x70,0xab,0x82,0x2a,
    0xa8,0x82,0x2a,0xa8,0x82,0x2a,0x50,0x00,0x80,0xda,0x7b,0x66,
    0xc5,0x64,0xaa,0x49,0x76,0x78,0xdf,0xce,0x9e,0x99,0xac,0xee,
    0x99,0xa2,0xcd,0x01,0x80,0xcd,0x5a,0x7b,0xb3,0xd6,0x4e,0xf7,
    0x5a,0xd9,0xac,0xb5,0x37,0x6b,0xed,0xb4,0xb5,0x36,0x6d,0x05,
    0x00,0x6a,0x0f,0xb5,0x7b,0x93,0xa9,0x3e,0x67,0x27,0xb5,0xd6,
    0x58,0xa9,0x8a,0xb3,0xfa,0xc2,0xd1,0x00,0xa0,0x66,0xa8,0x9a,
    0xa1,0x6a,0x86,0xaa,0x99,0x51,0x35,0xb3,0xa7,0x2a,0xd3,0xbb,
    0x88,0x2e,0x00,0x38,0xdd,0x9c,0xd3,0xcd,0x39,0xdd,0x9c,0xd3,
    0xcd,0x39,0xdd,0x9c,0xd3,0xdd,0x0e,0xad,0x0f,0x00,0xd4,0x0c,
    0x55,0x33,0x54,0x25,0x54,0xcd,0x50,0x35,0x43,0x55,0x86,0x22,
    0x14,0x00,0xd4,0x3b,0x54,0xe5,0x43,0x55,0xf7,0xde,0x55,0x09,
    0x55,0x9f,0x50,0x35,0xef,0x56,0x8c,0x5d,0x00,0x80,0xdd,0x60,
    0x00,0x18,0xd0,0xdb,0x90,0x80,0xda,0x00,0xe0,0x01,0xd7,0x03,
    0x7d,0xe1,0x74,0x63,0x75,0x73,0xaa,0x9b,0x95,0x6e,0x2a,0xdd,
    0x47,0xd2,0xbd,0x4e,0xd2,0x7d,0x56,0xd2,0xed,0xa4,0xba,0xc9,
    0xea,0xa6,0x4e,0x37,0x4b,0x37,0xc7,0xd5,0xf0,0x5c,0xe0,0x01,
    0x6e,0x70,0xdd,0x50,0x97,0xa1,0xca,0xa6,0x6a,0x9a,0xaa,0x1d,
    0xaa,0x3a,0xa3,0x2a,0xd9,0x53,0x95,0xcc,0xae,0x4a,0x4c,0x55,
    0x9a,0xaa,0x6c,0xaa,0x7a,0xa8,0xda,0xa8,0x1a,0x5c,0x05,0xf7,
    0x05,0x6e,0x00,0x00,0x9c,0xd4,0x4d,0x92,0xba,0x56,0x3a,0x55,
    0xc9,0x4c,0x55,0xb2,0xa7,0x2a,0xb4,0x0a,0x00,0x00,0x9b,0xb4,
    0x90,0x74,0xf6,0xac,0xa4,0x7a,0x93,0x95,0x66,0x9d,0x84,0x03,
    0x5c,0x20,0x63,0x9d,0x24,0xed,0x64,0x25,0x94,0x15,0x0e,0x00,
    0x00,0x27,0xe1,0xac,0x0e,0x2b,0xbb,0x8f,0xca,0xec,0xac,0x34,
    0x49,0xd0,0x19,0x00,0x00,0x00,0x00,0x00,0x00,0xeb,0x40,0x0a,
    0x2b,0xe1,0x64,0x37,0x05,0x3c,0xa0,0xe1,0x6a,0xd6,0xe9,0x4d,
    0xaa,0x91,0x0c,0x76,0x83,0x01,0x54,0x6f,0x72,0x12,0x96,0x0a,
    0x9c,0x05,0x00,0x00,0x00,0x00,0xc0,0x80,0xde,0x86,0x44,0x53,
    0xd9,0xcd,0x59,0x7d,0x41,0x83,0x07,0x00,0x6e,0x50,0x70,0xd5,
    0x1e,0x6a,0xa5,0x29,0x09,0xc7,0x2a,0x70,0x00,0x00,0x00,0x00,
    0x00,0xd8,0x03,0x69,0x9b,0x64,0xc2,0xaa,0x06,0x1c,0x50,0x0b,
    0x27,0x41,0x75,0x58,0x35,0x9b,0xba,0xa0,0xc0,0x0d,0x34,0xb5,
    0x32,0x24,0x1b,0x1d,0x98,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xe0,0x80,0x82,0x05,0x00,0x00,0x00,0xac,0x6e,0xd6,
    0xea,0x66,0xad,0x6e,0xd6,0xea,0x66,0x25,0x8e,0x24,0xa9,0x95,
    0x24,0xab,0x12,0x71,0xb2,0xa0,0xc0,0x01,0x00,0x20,0xdd,0xb1,
    0xd2,0x9d,0x24,0xdd,0x49,0x68,0x09,0x00,0x00,0x00,0x00,0x00,
    0xc0,0x0a,0xac,0x84,0xb5,0x76,0x58,0x63,0xb3,0x86,0x75,0x26,
    0x49,0x2a,0x00,0x00,0x24,0x42,0x92,0x24,0x12,0x89,0x04,0x12,
    0x48,0x90,0xa4,0x92,0xe1,0xac,0x59,0x1b,0xb3,0xb2,0x59,0x2b,
    0x61,0x11,0x16,0x00,0x00,0x12,0x48,0x20,0x41,0x92,0x90,0x24,
    0x09,0x91,0x00,0x00,0x00,0x6c,0xc2,0x26,0xd9,0x9b,0x64,0x6f,
    0x92,0xbd,0x49,0x36,0x64,0x03,0xc0,0xff,
};

/*
BYTE code tFONT1_ICON_D0_PORT[] =
{
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
    0xf0,0x18,0x42,0x3c,0xe7,0x6d,0x59,0xab,0x01,0x82,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x74,0x42,0x77,0x42,0x5f,0x09,
    0xc7,0xc9,0xbe,0x21,0xa5,0x48,0x76,0x72,0x27,0x49,0x92,0x24,
    0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x12,0x57,
    0x9c,0x00,0xd9,0x42,0x52,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0xc9,0xd5,0xe9,0x84,
    0x9c,0x84,0x3e,0x09,0x27,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x52,0x95,0x24,0x49,0x92,0x24,0x49,0x72,0x27,
    0xc9,0x26,0x29,0x24,0x37,0x2a,0x70,0x6f,0x70,0x03,0xb2,0x2b,
    0x09,0x2a,0x1b,0x00,0x00,0x00,0x00,0x00,0x1d,0x00,0x00,0x00,
    0x00,0x00,0x00,0x24,0x49,0x22,0xe1,0xb8,0x1a,0x00,0x00,0x00,
    0x00,0x90,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0xb9,0x3a,0x27,
    0x21,0x12,0x2e,0x09,0x24,0x90,0x20,0x7b,0x27,0xc9,0x7d,0x27,
    0x09,0x49,0x8a,0xa4,0x36,0xc9,0x7e,0x22,0xb9,0x5b,0x92,0xb3,
    0x49,0x95,0x48,0x6e,0x00,0x00,0x00,0x20,0x11,0x88,0x04,0x98,
    0xa5,0x01,0x00,0x00,0x00,0x12,0x81,0x48,0x80,0xb4,0x02,0x00,
    0x00,0x00,0x48,0x04,0x22,0x01,0x56,0x19,0x00,0x00,0x00,0x80,
    0x44,0x20,0x12,0x20,0x07,0x24,0x90,0x40,0x02,0x09,0x24,0x90,
    0x14,0x77,0x72,0xa2,0x12,0xd7,0x3e,0xc9,0xd6,0x92,0x2a,0xa2,
    0x8a,0xa4,0x0a,0xa9,0x22,0xa9,0x22,0x49,0x41,0x62,0x93,0xdc,
    0x49,0x92,0xcc,0x5a,0xdd,0x33,0x4b,0x33,0x6b,0x75,0x0f,0x4b,
    0xcf,0xac,0xd5,0x3d,0xb3,0x56,0xf7,0x00,0x40,0x92,0x24,0xe9,
    0xae,0x4a,0x5a,0x91,0xee,0xaa,0xd0,0x2a,0xe9,0xae,0x4a,0xba,
    0xab,0x02,0x00,0x49,0x92,0xac,0xaa,0x99,0xb5,0xca,0xb0,0xaa,
    0x66,0x16,0x65,0xd6,0xaa,0x9a,0x59,0xab,0x6a,0x66,0x01,0x40,
    0x92,0x24,0x39,0x87,0x00,0x49,0xae,0x2b,0x40,0xce,0x21,0x1c,
    0x02,0x00,0x49,0x92,0x48,0xf6,0x26,0x81,0xa4,0x8a,0x04,0x92,
    0xbd,0x5d,0x89,0x7d,0x9d,0x84,0x2b,0x09,0x9d,0x24,0xc9,0xff,

#elif((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
    0x0f,0x18,0x3e,0xc7,0x9b,0x26,0x4d,0x5a,0x01,0x58,0x00,0x00,
    0x00,0x00,0x00,0x00,0x80,0x84,0x72,0x02,0x35,0xa0,0x00,0x00,
    0x00,0x00,0xa0,0xc1,0xda,0x90,0x08,0xc9,0x4e,0xba,0x26,0x93,
    0x70,0x08,0x00,0x00,0x00,0x00,0x00,0x48,0x92,0x24,0x49,0x12,
    0x00,0x00,0x00,0x00,0x00,0x9a,0x2c,0x8b,0x64,0x2f,0x6a,0x56,
    0x98,0x5a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x83,0x93,0x50,0x49,
    0xa6,0x92,0x24,0x27,0x00,0x00,0x9c,0x84,0x4a,0x92,0x49,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x89,0x29,0x54,0x82,0x24,
    0x51,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x96,0x24,0x6b,0x25,0x49,0x56,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x7b,0x25,0x49,0x75,0x92,0x7d,0x26,
    0x59,0x00,0xb0,0x09,0xd5,0x9d,0xf4,0xe9,0xde,0x6b,0xd2,0x5d,
    0x9d,0x74,0x9f,0x49,0xba,0x93,0xa4,0x3b,0x89,0x29,0xc8,0x01,
    0x83,0x49,0x33,0x93,0x30,0xb3,0xc2,0x3c,0xc1,0x33,0x09,0x95,
    0x84,0x93,0x24,0x49,0x92,0x24,0x2a,0x92,0x6c,0x21,0x49,0x92,
    0xc4,0x6c,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x02,0x24,0x49,0x12,0x09,0x49,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0xe2,0xb3,0x90,
    0x92,0xac,0xdc,0xf7,0x24,0xd7,0x7d,0xa7,0xe7,0xba,0xef,0xe4,
    0xaa,0xfb,0x5e,0xa9,0x4a,0x92,0x3e,0xc9,0x5e,0x93,0xa4,0x3a,
    0x49,0xce,0x24,0x49,0x92,0xac,0x24,0x49,0xef,0x24,0x8b,0x24,
    0x4d,0xb2,0xd3,0x9d,0x64,0x91,0xa4,0x49,0x36,0x56,0xa0,0x37,
    0x00,0x00,0x80,0x44,0xd1,0x54,0xf5,0x95,0xab,0xea,0x5a,0x36,
    0x7b,0x82,0x43,0x28,0x00,0x00,0x12,0x01,0x48,0xae,0x5c,0x17,
    0xe5,0x9d,0x44,0x20,0x12,0x00,0x00,0x12,0x41,0x15,0x72,0x5d,
    0xb9,0x2e,0x67,0xf4,0xca,0x5e,0x51,0xb4,0x04,0x00,0x80,0xba,
    0xef,0xad,0xcc,0xbd,0x77,0x79,0x66,0x6f,0xb0,0x01,0x00,0x00,
    0x00,0x58,0x81,0xde,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0xfe,0xff,

#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    0x0f,0x13,0x8e,0xc7,0xb9,0x26,0x4d,0x5a,0x01,0x5f,0x00,0x00,
    0x00,0x00,0x00,0x00,0x80,0x84,0x72,0x02,0xd5,0xa0,0x00,0x00,
    0x00,0x00,0x60,0xc0,0xda,0x90,0x08,0xc9,0x4e,0xa6,0x3a,0x9d,
    0x70,0x08,0x00,0x00,0x00,0x00,0x00,0x48,0x92,0x24,0x49,0x12,
    0x00,0x00,0x00,0x00,0x00,0x86,0x2c,0x8b,0x64,0x2f,0xaa,0x57,
    0xe8,0x5a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x8d,0x93,0x50,0x49,
    0xba,0x92,0x24,0x27,0x00,0x00,0x9c,0x84,0x4a,0x92,0x4e,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x89,0x2e,0x54,0x82,0x24,
    0x51,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x91,0x24,0x6b,0x25,0x49,0x56,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x7b,0x25,0x49,0x4d,0x92,0x7d,0x3a,
    0x59,0x00,0xb0,0x09,0x35,0x93,0xcc,0x99,0xd9,0xab,0x33,0x53,
    0x93,0xcc,0x9c,0x4e,0x66,0x92,0x64,0x26,0x89,0x2e,0xc8,0x01,
    0x8d,0xce,0xd0,0x9d,0xd0,0xbd,0x42,0x3f,0xc1,0xd3,0x09,0x95,
    0x84,0x93,0x24,0x49,0x92,0x24,0x2a,0x92,0x6c,0x21,0x49,0x92,
    0x44,0x6f,0x72,0x92,0xe9,0x64,0xaf,0x4a,0x56,0xe6,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x40,0x92,0x24,0x91,0xd0,0xc9,0x5e,
    0x95,0xc4,0x9c,0x24,0xa9,0x24,0x49,0x92,0x24,0x49,0x92,0x24,
    0x3e,0x0b,0x29,0xc9,0xca,0x75,0x75,0x72,0x5f,0x57,0xa6,0xef,
    0xeb,0x4a,0xee,0xba,0xae,0x95,0xaa,0x24,0x99,0x93,0xec,0xd5,
    0x49,0x6a,0x92,0xe4,0x74,0x92,0x24,0xc9,0x4a,0x92,0xcc,0x4e,
    0xb2,0x48,0x32,0x24,0x3b,0x33,0x49,0x16,0x49,0x86,0x64,0x63,
    0x05,0x66,0x03,0x00,0x00,0x48,0x14,0x57,0xab,0x9a,0x2b,0x5d,
    0x75,0xdd,0x33,0x55,0x77,0xa2,0x6a,0x88,0x0a,0x00,0x00,0x89,
    0xd0,0xad,0x49,0x3a,0xdd,0x6f,0xf7,0xde,0x6f,0x22,0x10,0x09,
    0x00,0x00,0x89,0xd0,0x55,0x4d,0xaa,0xd2,0x3d,0xa7,0xab,0x26,
    0x7b,0x45,0x31,0x12,0x00,0x00,0xea,0xba,0xb6,0xd2,0xd7,0xde,
    0xe5,0xe9,0xbd,0xc1,0x06,0x00,0x00,0x00,0x60,0x05,0x66,0x03,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf8,
    0xff,
#endif
};

/*
BYTE code tFONT1_ICON_DP[] =
{


    0x0f,0x13,0x8e,0xc7,0xb9,0x26,0x4d,0x5a,0x01,0x5f,0x00,0x00,
    0x00,0x00,0x00,0x00,0x80,0x84,0x72,0x02,0xd5,0xa0,0x00,0x00,
    0x00,0x00,0x60,0xc0,0xda,0x90,0x08,0xc9,0x4e,0xa6,0x3a,0x9d,
    0x70,0x08,0x00,0x00,0x00,0x00,0x00,0x48,0x92,0x24,0x49,0x12,
    0x00,0x00,0x00,0x00,0x00,0x86,0x2c,0x8b,0x64,0x2f,0xaa,0x57,
    0xe8,0x5a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x8d,0x93,0x50,0x49,
    0xba,0x92,0x24,0x27,0x00,0x00,0x9c,0x84,0x4a,0x92,0x4e,0x92,
    0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x89,0x2e,0x54,0x82,0x24,
    0x51,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
    0x24,0x49,0x92,0x91,0x24,0x6b,0x25,0x49,0x56,0x92,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x7b,0x25,0x49,0x4d,0x92,0x7d,0x3a,
    0x59,0x00,0xb0,0x09,0x35,0x93,0xcc,0x99,0xd9,0xab,0x33,0x53,
    0x93,0xcc,0x9c,0x4e,0x66,0x92,0x64,0x26,0x89,0x2e,0xc8,0x01,
    0x8d,0xce,0xd0,0x9d,0xd0,0xbd,0x42,0x3f,0xc1,0xd3,0x09,0x95,
    0x84,0x93,0x24,0x49,0x92,0x24,0x2a,0x92,0x6c,0x21,0x49,0x92,
    0x44,0x6f,0x72,0x92,0xe9,0x64,0xaf,0x4a,0x56,0xe6,0x24,0x49,
    0x92,0x24,0x49,0x92,0x24,0x40,0x92,0x24,0x91,0xd0,0xc9,0x5e,
    0x95,0xc4,0x9c,0x24,0xa9,0x24,0x49,0x92,0x24,0x49,0x92,0x24,
    0x3e,0x0b,0x29,0xc9,0xca,0x75,0x75,0x72,0x5f,0x57,0xa6,0xef,
    0xeb,0x4a,0xee,0xba,0xae,0x95,0xaa,0x24,0x99,0x93,0xec,0xd5,
    0x49,0x6a,0x92,0xe4,0x74,0x92,0x24,0xc9,0x4a,0x92,0xcc,0x4e,
    0xb2,0x48,0x32,0x24,0x3b,0x33,0x49,0x16,0x49,0x86,0x64,0x63,
    0x05,0x66,0x03,0x00,0x00,0x48,0x14,0x57,0xab,0x9a,0x2b,0x5d,
    0x75,0xdd,0x33,0x55,0x77,0xa2,0x6a,0x88,0x0a,0x00,0x00,0x89,
    0xd0,0xad,0x49,0x3a,0xdd,0x6f,0xf7,0xde,0x6f,0x22,0x10,0x09,
    0x00,0x00,0x89,0xd0,0x55,0x4d,0xaa,0xd2,0x3d,0xa7,0xab,0x26,
    0x7b,0x45,0x31,0x12,0x00,0x00,0xea,0xba,0xb6,0xd2,0xd7,0xde,
    0xe5,0xe9,0xbd,0xc1,0x06,0x00,0x00,0x00,0x60,0x05,0x66,0x03,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf8,
    0xff,




};
*/

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdFontVLCLoadFont(BYTE ucState);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Osd Load Hardware VLC Font
// Input Value  :
// Output Value :
//--------------------------------------------------
/*
void OsdLoadHardwareVLCFont(BYTE *pucArray, WORD usOffset, WORD usFontTableStart, bit bOsdRotate)
{
    WORD usNum = 0;

    if(bOsdRotate == _TRUE)
    {
        usNum = 0x85;
    }

    // rotation
    ScalerOsdFrameControlByte(0x003, _OSD_BYTE2, usNum);

    // osd compression
    ScalerOsdAddrMsb(0xC0);
    ScalerOsdAddrLsb(0x05);
    ScalerOsdBurstWriteDataPort(pucArray, 8, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_FLASH);

    usNum = ((WORD) * (pucArray + 8) << 8) | *(pucArray + 9);

    usOffset = usOffset * 9;
    usOffset += usFontTableStart;

    // osd compression enable
    ScalerOsdFrameControlByte(0x007, _OSD_BYTE2, 0x01);

    // Osd load font > 12K
    if(usOffset > 4095)
    {
        ScalerOsdScrambleLoadFontAddrHsbSet();
    }
    else
    {
        ScalerOsdScrambleLoadFontAddrHsbClr();
    }

    pucArray += 10;

    ScalerOsdAddrMsb((HIBYTE(usOffset) & 0x000f) | 0xd0);
    ScalerOsdAddrLsb(LOBYTE(usOffset));
    ScalerOsdBurstWriteDataPort(pucArray, usNum, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_FLASH);

    // For osd load font > 12K !!
    ScalerOsdScrambleLoadFontAddrHsbClr();
    ScalerOsdFrameControlByte(0x007, _OSD_BYTE2, 0x00);
    ScalerOsdFrameControlByte(0x003, _OSD_BYTE2, (BYTE)bOsdRotate);
}
*/
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdFontVLCLoadFont(BYTE ucState)
{
    switch(ucState)
    {
        case _FONT1_GLOBAL:
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
            ScalerOsdHardwareVLC(tFONT1_GLOBAL, VLC_TABLE_SIZE(tFONT1_GLOBAL), GET_CURRENT_BANK_NUMBER(), _1GLOBAL_START, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
#else
            ScalerOsdHardwareVLC(tFONT1_GLOBAL, VLC_TABLE_SIZE(tFONT1_GLOBAL), GET_CURRENT_BANK_NUMBER(), _1GLOBAL_START, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);
#endif
            break;

        case _REALTEK_1BIT_LOGO0:
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
            ScalerOsdHardwareVLC(tICON_REALTEK_1BIT_LOGO0, VLC_TABLE_SIZE(tICON_REALTEK_1BIT_LOGO0), GET_CURRENT_BANK_NUMBER(), _LOGO_START_ADDRESS, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
#else
            ScalerOsdHardwareVLC(tICON_REALTEK_1BIT_LOGO0, VLC_TABLE_SIZE(tICON_REALTEK_1BIT_LOGO0), GET_CURRENT_BANK_NUMBER(), _LOGO_START_ADDRESS, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);
#endif
            break;

        case _REALTEK_1BIT_LOGO1:
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
            ScalerOsdHardwareVLC(tICON_REALTEK_1BIT_LOGO1, VLC_TABLE_SIZE(tICON_REALTEK_1BIT_LOGO1), GET_CURRENT_BANK_NUMBER(), _Logo1_0x00, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
#else
            ScalerOsdHardwareVLC(tICON_REALTEK_1BIT_LOGO1, VLC_TABLE_SIZE(tICON_REALTEK_1BIT_LOGO1), GET_CURRENT_BANK_NUMBER(), _Logo1_0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);
#endif
            break;

        default:
            break;
    }
}

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
