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
// ID Code      : BeaconFactoryFunction.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
#define __BEACON_FACTORY_FUNC_

#include "UserCommonInclude.h"

#if(_USER_BEACON_FACTORY_OSD == _ON)

#include "ScalerMDomainInclude.h"
extern void ScalerSetDataPortByte(WORD usAddr, BYTE ucValue1, BYTE ucValue2);
extern void ScalerGetDataPortByte(WORD usAddr, BYTE ucValue, WORD usLength, BYTE *pucArray, bit bAutoInc);
extern void ScalerSetDataPortBit(WORD usAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr);
extern BYTE ScalerGetDataPortBit(WORD usAddr, BYTE ucValue, BYTE ucAnd);
//--------------------------------------------------
// Control For LVDS
//--------------------------------------------------
#define _CM_8C_PT_A1_TCON_LVDS_CTRL1              0xA1 // LVDS Control Register1
#define _CM_8C_PT_A3_TCON_LVDS_CTRL3              0xA3 // LVDS Control Register3

//--------------------------------------------------
// Embedded Timing Controller(Port)
//--------------------------------------------------
#define CM_8B_TCON_ADDR_PORT                0x008B // TCON Address Port for Embedded TCON Access
#define CM_8C_TCON_DATA_PORT                0x008C // TCON Data Port for Embedded TCON Access

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE xdata g_ucBeaconFacOsdState = 0;
bit g_ucBeaconFacOsdShowFlag = _OFF;

#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
WORD prePwmValue = 0xFFFF;
#endif
//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
code void (*OperationFacOsdTable[][4])(void);
void BeaconFactoryOsdMenuOperation(void);

void BeaconFactoryMenuItemPage1(void);
void BeaconFactorySelectNextItemPage1(void);
void BeaconFactoryExitItemPage1(void);
void BeaconFactoryMenuExitPage1(void);


void BeaconFactoryMenuItemPage2(void);
void BeaconFactorySelectNextItemPage2(void);
void BeaconFactoryExitItemPage2(void);
void BeaconFactoryMenuExitPage2(void);
void BeaconFactoryMenuItemSel(BYTE item,BYTE color);

//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tFONT_FACTORY[] =
{
    0x04,0x28,0xf1,0xec,0x7a,0x35,0x96,0xbd,0x0a,0x57,0xc0,0x06,
    0x5a,0xad,0xa5,0xbb,0x8a,0xee,0x2a,0xba,0xab,0x2c,0xbd,0x0a,
    0xd8,0x00,0xb0,0xc0,0x0b,0xcf,0x82,0xcf,0x82,0xb5,0x60,0x2d,
    0x58,0x60,0x01,0xc0,0x00,0xad,0xd6,0xd2,0x8d,0x05,0x2b,0x50,
    0x58,0x9a,0xf6,0x0c,0x00,0x6c,0xb0,0xa8,0xb5,0x1e,0x58,0x0b,
    0xb6,0x6e,0x2c,0xfd,0x14,0xb0,0x01,0x40,0x43,0x75,0xb3,0xd2,
    0x4d,0x74,0x2f,0x3d,0xa7,0x9f,0xa2,0x1b,0x34,0x00,0x60,0xda,
    0x02,0x6b,0xd9,0x3c,0x45,0x53,0x4b,0x37,0x96,0x5e,0x05,0x6c,
    0x00,0xd8,0x40,0xab,0xb5,0x36,0x55,0xb4,0x7a,0x96,0xee,0x2a,
    0x4b,0xaf,0x02,0x36,0x00,0x4c,0x7b,0x58,0xb0,0x0a,0x2a,0x90,
    0x40,0x1a,0x1a,0x34,0x00,0x6c,0xa0,0xd5,0x5a,0x4b,0xaf,0xb2,
    0x58,0xb6,0xee,0x2a,0x4b,0xaf,0x02,0x36,0x00,0x6c,0xa0,0xd5,
    0x5a,0xba,0xab,0xac,0xee,0x55,0x74,0xb3,0x97,0x5e,0x05,0x6c,
    0x00,0x00,0xf0,0x00,0x0f,0x00,0xc0,0x03,0x3c,0x00,0x00,0x00,
    0x80,0x69,0x0b,0xda,0x1a,0x00,0x00,0x00,0xc0,0x82,0x35,0x17,
    0x66,0x86,0x6b,0xcd,0x70,0x59,0x17,0x00,0x00,0x00,0x00,0x00,
    0x00,0x80,0xd9,0xfb,0xba,0x06,0x00,0x9a,0xa5,0xf1,0x2c,0x78,
    0x1e,0x78,0x1e,0x78,0x1e,0x58,0x8f,0xc6,0x6a,0x00,0x58,0x8d,
    0xe5,0x34,0x9c,0x03,0xe7,0xc0,0x39,0xd0,0x07,0x4b,0xb3,0x00,
    0x00,0x58,0xdd,0x78,0x60,0x7d,0xa1,0x0e,0xa4,0x59,0x1a,0x16,
    0x00,0x00,0x00,0x00,0x00,0x9a,0x05,0xac,0x06,0x80,0x80,0x1b,
    0xee,0xc5,0x72,0x2f,0xd6,0x5a,0xba,0xeb,0x19,0xe9,0x14,0x22,
    0x00,0x60,0xda,0x85,0x74,0x42,0x27,0xa1,0xe5,0x1a,0x49,0x42,
    0x27,0x01,0xd7,0x00,0xc0,0x34,0xa8,0xd4,0x82,0x04,0x12,0x48,
    0x48,0xad,0x42,0x33,0x00,0x30,0x5c,0x48,0x27,0x54,0x25,0x54,
    0x25,0x54,0x25,0x74,0x12,0x70,0x0d,0x00,0xcc,0x71,0x81,0x04,
    0x12,0x74,0xae,0x41,0x02,0x09,0x8e,0x6b,0x00,0x60,0x8e,0x07,
    0x54,0x41,0x95,0x69,0x4f,0x41,0x15,0x54,0x81,0x02,0x00,0x03,
    0xa4,0x6b,0x41,0xe2,0xd9,0x12,0xaa,0x12,0x3a,0xab,0x80,0x01,
    0x00,0x11,0x24,0x09,0x49,0x42,0x4e,0xae,0x91,0x24,0x24,0x09,
    0x22,0x00,0x20,0x20,0x90,0x40,0x02,0x09,0x24,0x10,0x10,0x00,
    0xd0,0xa0,0x1b,0xba,0xa1,0x1b,0xba,0x17,0xba,0xd7,0x02,0x06,
    0x00,0x44,0x58,0x3a,0x11,0x92,0x0a,0x6f,0xce,0x22,0xdf,0xd2,
    0x92,0x45,0x04,0x00,0xa0,0x40,0x15,0x54,0x41,0x15,0x54,0x41,
    0x15,0xda,0x33,0x00,0xa0,0x34,0xbe,0xdf,0x73,0xb8,0xef,0xfb,
    0xb6,0xaa,0x3e,0x9f,0x75,0x57,0x75,0xdf,0xa9,0xea,0xbe,0x29,
    0x1d,0x00,0x10,0x41,0xf2,0x7e,0x75,0x92,0x57,0x92,0x24,0x2b,
    0x49,0xca,0x49,0xb2,0x88,0x00,0x80,0x01,0xd2,0xb5,0xa8,0x4a,
    0xa8,0x4a,0xa8,0x4a,0xe8,0xac,0x02,0x06,0x00,0x86,0x0b,0xe9,
    0x84,0x24,0x31,0xfa,0x0a,0x24,0x90,0x80,0x00,0x80,0x01,0xd2,
    0xb5,0xa8,0x4a,0xa8,0x4a,0xa8,0x4a,0x38,0xdf,0x55,0x0f,0x5f,
    0x06,0x00,0x86,0x0b,0xe9,0x84,0x24,0x31,0xfa,0x8a,0x45,0x52,
    0x5a,0xb2,0x88,0x00,0x80,0x61,0x21,0x9d,0x82,0x8a,0xa7,0x59,
    0x47,0x02,0x9d,0x0a,0x58,0x03,0x00,0x73,0x5c,0x04,0x12,0x48,
    0x20,0x81,0x04,0x02,0x02,0x00,0x22,0x48,0x12,0x92,0x84,0x24,
    0x21,0x49,0xe8,0x54,0xc0,0x1a,0x00,0x10,0x41,0xa7,0x42,0x77,
    0x95,0xc5,0x5a,0xeb,0xc6,0x5a,0x81,0x1b,0x04,0x00,0x2c,0xa1,
    0xd6,0x4a,0xaa,0xd6,0x4a,0xea,0xad,0xaa,0x7a,0xfb,0xbe,0xab,
    0x5a,0xee,0x55,0x4d,0x2c,0x00,0x20,0xc2,0xd2,0xab,0xdc,0x58,
    0xeb,0x86,0x2c,0xd6,0x5a,0xd2,0x29,0x94,0x06,0x00,0x22,0xe8,
    0xae,0x72,0x63,0xad,0xc0,0x1d,0x48,0x20,0x20,0x00,0x30,0xc7,
    0xc3,0xd2,0x28,0x58,0x81,0x60,0x69,0xd4,0xc2,0x71,0x0d,0x00,
    0x00,0x80,0xb6,0xcc,0xd3,0xad,0xe8,0xae,0x75,0x56,0x77,0x15,
    0xda,0xda,0x00,0x80,0x02,0x55,0x16,0x4f,0x6d,0xdd,0x55,0x74,
    0x57,0x59,0xfa,0x29,0x50,0x1b,0x00,0x00,0xa0,0x1b,0x17,0xd6,
    0x82,0xb5,0x74,0xb3,0x80,0x0b,0x00,0x34,0xe8,0xc6,0xea,0x5e,
    0xb6,0xee,0x2a,0xba,0xab,0xac,0xee,0x55,0x68,0x36,0x00,0x00,
    0xc0,0x62,0xd9,0xba,0xab,0xd0,0xf5,0xcc,0xd2,0xab,0x80,0x0d,
    0x00,0x0f,0x08,0x24,0x30,0x81,0x04,0x12,0x08,0x08,0x00,0x00,
    0xc0,0xea,0x5e,0xb6,0xee,0x2a,0xba,0xab,0xac,0xee,0x55,0x74,
    0xb3,0x37,0xab,0x16,0x80,0x05,0xd6,0xd2,0x6d,0xad,0x4b,0xf7,
    0x5a,0x74,0xaf,0x45,0xf7,0x5a,0x68,0x0b,0x00,0x04,0x00,0x81,
    0x04,0x12,0x48,0x20,0x20,0x00,0x50,0x00,0x28,0xa8,0x82,0x2a,
    0xa8,0x82,0x2a,0xa8,0x03,0x05,0xa0,0x40,0x95,0xa5,0xab,0x84,
    0xaa,0x2a,0x9e,0x3a,0x8b,0xaa,0xa2,0x15,0x00,0x08,0x08,0x24,
    0x90,0x40,0x02,0x09,0x04,0x04,0x00,0x00,0xe0,0x5b,0xe7,0xfc,
    0x3e,0xa9,0xea,0x4e,0xaa,0xba,0x93,0xaa,0xee,0x50,0x3a,0x00,
    0x00,0x00,0x8b,0xa7,0xf6,0xa2,0x6a,0x2d,0xaa,0xd6,0xa2,0x6a,
    0x41,0x2d,0x00,0x00,0x80,0xc5,0xb2,0x75,0x57,0xd1,0x5d,0x65,
    0xe9,0x55,0xc0,0x06,0x00,0x00,0x58,0x3c,0xb5,0x75,0x57,0xd1,
    0x5d,0x65,0xe9,0xa7,0xa0,0x6a,0xa3,0x0a,0x00,0x00,0xab,0x7b,
    0xd9,0xba,0xab,0xe8,0xae,0xb2,0xba,0x57,0xd1,0xcd,0xd6,0x0d,
    0x00,0x00,0x0e,0xfc,0x1a,0xba,0xa1,0x1b,0x1a,0x34,0x00,0x00,
    0xc0,0xa2,0xd6,0x46,0x95,0x85,0xb5,0x17,0x65,0xc1,0xda,0x00,
    0x00,0x04,0x12,0x98,0x40,0x02,0x09,0x04,0x5c,0x00,0x00,0x00,
    0xba,0xd7,0xa2,0x7b,0x2d,0xba,0xd7,0xb2,0xba,0xd7,0x42,0xb3,
    0x01,0x00,0x00,0x74,0x57,0x59,0xac,0xb5,0x6e,0xb8,0x03,0x37,
    0x08,0x00,0x00,0x40,0xaa,0xba,0x73,0x27,0xc9,0xbd,0x92,0xf7,
    0x5d,0x3a,0xf5,0x2e,0x5a,0x01,0x00,0x00,0x58,0x7a,0x95,0x1b,
    0xee,0x1b,0xb2,0x58,0x6e,0x5a,0x01,0x00,0x00,0xd0,0x5d,0x65,
    0xb1,0x6a,0xdd,0x58,0xeb,0x86,0x3b,0x90,0x66,0x09,0x00,0x00,
    0x4b,0x7b,0xa6,0xa0,0x1a,0x82,0xa5,0x69,0xcf,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x95,0x5a,0x55,0xaf,0xe6,
    0x7e,0x6d,0xcf,0x5d,0xe9,0xe5,0xa6,0x54,0x01,0x33,0x33,0x33,
    0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,
    0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,
    0xc0,0xb3,0x2d,0x3e,0xba,0xae,0xb3,0x6b,0x5f,0xeb,0xa9,0xfb,
    0xbe,0x72,0xd7,0x7d,0x5f,0xb9,0x3f,0xe9,0x24,0x94,0x5f,0x01,
    0x00,0x16,0xba,0xf3,0xcc,0x1c,0x57,0xaf,0x24,0x49,0x38,0xb9,
    0x46,0x55,0x82,0xed,0x19,0x00,0x28,0x8a,0xd9,0xaa,0x56,0xb5,
    0x1a,0xf7,0x9d,0xef,0x95,0xea,0xae,0xbb,0xaa,0x55,0x2d,0xbe,
    0xea,0x00,0xc0,0x0b,0x66,0x77,0xcb,0x87,0x95,0xcf,0xc7,0x51,
    0x33,0x47,0xf9,0x7c,0xe8,0x7c,0xd8,0x0c,0x00,0x34,0x45,0x6f,
    0xa9,0xbe,0xef,0xfb,0xbc,0xfb,0xbe,0xef,0xe4,0xbe,0xef,0x3b,
    0xb9,0x6b,0xdf,0x6f,0x6e,0x6e,0xdf,0x2f,0x00,0xcc,0x81,0x24,
    0x35,0x92,0x54,0x45,0xed,0x9a,0x6b,0xee,0xaa,0xa2,0xea,0x3c,
    0x38,0x00,0x00,0x2c,0x74,0xe7,0x99,0x39,0xae,0x5e,0x49,0x92,
    0x70,0x72,0x8d,0xaa,0x04,0xdb,0x33,0x00,0x30,0x0d,0xd3,0x9d,
    0xee,0xe9,0xa6,0xe7,0x78,0xdb,0x9b,0x3c,0xeb,0x7d,0x93,0xcf,
    0xfb,0xb2,0x3d,0x03,0x00,0x28,0x96,0x93,0xba,0x16,0xfb,0xb3,
    0x16,0xa9,0xb5,0x30,0x6b,0x71,0x9e,0xc5,0x66,0x00,0xe0,0x3a,
    0x8a,0xeb,0x24,0x65,0x76,0xf6,0xc7,0xa7,0xa4,0xd6,0xd3,0xb1,
    0xdf,0x4f,0xe5,0xd4,0x0b,0x1e,0x00,0xd0,0x0a,0xbd,0x6b,0xe6,
    0xd9,0xde,0x55,0xd2,0xef,0x9b,0x39,0x2e,0xee,0x24,0xb9,0xd9,
    0x66,0x00,0x60,0xb1,0x58,0xac,0xf7,0xad,0xec,0x67,0xfe,0xde,
    0xe4,0xf3,0x7e,0x3e,0xc9,0xd4,0x5a,0xe9,0x27,0x4d,0x39,0x37,
    0x00,0x34,0x98,0x6d,0x84,0xd2,0x96,0xf6,0xcc,0x6c,0xa3,0x02,
    0x81,0x75,0x00,0x20,0x80,0x6d,0x46,0x77,0x3d,0x43,0x7b,0x46,
    0xed,0x9e,0x59,0xa5,0x9e,0x61,0x3b,0x00,0xa0,0x40,0xf7,0xce,
    0x35,0xdd,0x3b,0xd7,0xd0,0xc9,0x74,0x4e,0xde,0x79,0x74,0x12,
    0xb6,0xcf,0x01,0x00,0x81,0x4e,0x86,0xce,0xe6,0x57,0xc9,0xdb,
    0xbd,0x92,0x7a,0x57,0x27,0x79,0x71,0xf4,0x07,0x00,0x8a,0x50,
    0x25,0xa9,0xbb,0x73,0xa5,0x8a,0xe4,0xb9,0x49,0xaa,0xaa,0xbe,
    0x6f,0xb1,0x65,0x01,0x40,0x81,0xee,0x9d,0x6b,0xba,0x77,0xae,
    0xa1,0x93,0xe9,0x9c,0xbc,0xf3,0xe8,0x24,0x6c,0x9f,0x03,0x00,
    0xd3,0x1e,0xa6,0xfb,0x29,0xb3,0x7b,0xca,0xef,0xb8,0xd2,0x9f,
    0xe4,0xca,0xe7,0x93,0x9e,0x1c,0x8a,0x1b,0x00,0x02,0x02,0x99,
    0x6d,0xe4,0x86,0x2c,0x96,0x5b,0xab,0xb5,0xf8,0x3a,0x00,0x20,
    0x20,0x90,0xb4,0x92,0x24,0xa9,0xa4,0xaa,0x93,0x40,0x60,0x1d,
    0x00,0x08,0x08,0x24,0x39,0xb9,0x26,0x49,0x92,0xe4,0xe4,0x9a,
    0x40,0x40,0x00,0x60,0xb6,0xa0,0x4a,0x71,0xdf,0xef,0x3b,0x73,
    0xdf,0xef,0xcb,0x7d,0xbf,0x2f,0x75,0xe7,0x1d,0xb6,0x00,0x80,
    0x80,0xe9,0x5c,0xf2,0x85,0xb7,0x6d,0x33,0x9f,0x4e,0xad,0xee,
    0xaa,0xce,0x66,0x73,0x01,0x40,0xb1,0xa8,0x52,0xab,0xaa,0xf3,
    0xad,0x2a,0xea,0x7e,0x6e,0xaa,0xbe,0x55,0x55,0x55,0x6c,0xb5,
    0x00,0x60,0x51,0x74,0xed,0xd4,0xbc,0xdb,0xfe,0xd4,0xbb,0x3b,
    0x75,0xde,0x5d,0xe6,0x7d,0x77,0x9d,0xe7,0xa5,0x78,0x01,0x60,
    0x11,0x16,0x6a,0x55,0x76,0xe6,0xf3,0x49,0xae,0xbc,0x9f,0x24,
    0xf9,0x7c,0xd2,0x49,0x53,0x3e,0x37,0x00,0x04,0xa4,0x90,0x6f,
    0x67,0x5d,0xdf,0x97,0xb5,0xde,0x74,0x57,0x25,0x95,0x4e,0x60,
    0x1d,0x00,0x00,0xe2,0xb8,0x26,0x49,0x25,0xd1,0x2a,0xb1,0xcd,
    0x04,0x02,0x02,0x00,0x45,0x81,0xd4,0x62,0x9f,0x77,0x3a,0x49,
    0x3a,0x9d,0x24,0x4b,0x27,0x61,0x7b,0x07,0x00,0xe6,0xb8,0x98,
    0x93,0x2b,0xf7,0x6c,0x23,0xd3,0x1e,0xd1,0x5d,0x25,0xdd,0x55,
    0x61,0x9b,0x01,0x80,0xe7,0x40,0x70,0x9d,0xf4,0xa9,0x6b,0x66,
    0xf7,0x54,0xd2,0x5d,0x95,0x38,0xae,0xa1,0x3d,0x03,0x00,0x01,
    0xb1,0x5d,0x23,0xa7,0x9e,0x91,0x53,0xcf,0xc8,0xa9,0x67,0xe4,
    0xd4,0x33,0x6c,0xd7,0x00,0xc0,0x6c,0x17,0xb3,0xeb,0x8a,0x39,
    0xfd,0xa6,0x67,0xf7,0x95,0xae,0xf2,0xbe,0x95,0xce,0xfb,0x2e,
    0xbe,0x3e,0x0d,0x00,0xcf,0xb6,0x58,0xfa,0x7d,0xcf,0xae,0x3d,
    0xef,0x53,0xf7,0xfd,0xae,0xba,0xef,0xbb,0xdf,0xef,0x4a,0xd7,
    0x42,0x39,0x05,0x00,0x73,0x5c,0x04,0x12,0x48,0x20,0x81,0xcc,
    0x36,0x02,0x00,0xc0,0x6c,0x17,0x48,0x20,0x81,0x04,0x12,0xe8,
    0x00,0x00,0x60,0xb6,0x87,0x39,0x7e,0x31,0x27,0x4f,0x99,0x93,
    0xa7,0xcc,0xf1,0x2c,0xa3,0xbd,0xd8,0x2e,0x00,0x50,0x14,0x48,
    0x2d,0xf6,0x79,0xa7,0x93,0xa4,0xd3,0x49,0xb2,0x74,0x12,0xb6,
    0x77,0x00,0xe0,0xb4,0xe1,0xdc,0xe7,0xef,0x93,0xbf,0xdd,0xf3,
    0xc9,0xe9,0x9e,0xe5,0x2f,0xbd,0x96,0x37,0x79,0xf7,0xa2,0xdc,
    0x37,0x00,0x2c,0xc2,0x42,0xad,0xc5,0xb6,0xaa,0x55,0xad,0xbb,
    0xbb,0xaa,0x92,0xd4,0x13,0x8a,0x06,0x80,0xc5,0x62,0xd9,0x6b,
    0x66,0x3b,0x63,0xbd,0xba,0xd2,0xb3,0x8d,0xa4,0xd5,0x7a,0xf9,
    0x3a,0x01,0x00,0xad,0x98,0xe3,0x5a,0x6b,0x4e,0xae,0x64,0x4e,
    0xae,0x64,0xb6,0x91,0x40,0x40,0x00,0x20,0x20,0x39,0xb9,0x66,
    0x4e,0xae,0x64,0xb6,0x91,0x54,0x75,0x27,0xb5,0x7b,0x06,0x04,
    0x00,0x00,0x39,0xb9,0x46,0x92,0x90,0x24,0x24,0x09,0x39,0xb9,
    0x06,0x00,0x80,0x02,0x37,0xa3,0xaa,0x76,0xd5,0x55,0x55,0x55,
    0x75,0xaa,0x9e,0xaa,0xae,0x72,0xc2,0xb1,0x00,0x40,0x45,0xf1,
    0xd3,0x93,0xfb,0xb3,0xeb,0x52,0x37,0x57,0xfa,0xee,0x5c,0xb9,
    0xef,0xaa,0xe4,0xc7,0xf6,0x7e,0x00,0xc0,0xd7,0x22,0xfa,0x7d,
    0xaf,0xd9,0xae,0x37,0x6f,0x55,0xf2,0xbe,0xc9,0x7b,0xbd,0x9f,
    0xf4,0xfb,0x86,0xf2,0x29,0x00,0x08,0x98,0x6d,0x64,0x43,0x5e,
    0xd6,0x7a,0x93,0x4e,0x25,0x6e,0xbf,0x01,0x01,0x80,0x39,0xc2,
    0x9c,0xa8,0x9e,0x93,0xad,0x3f,0xa9,0xaa,0xfb,0xa4,0xab,0x6e,
    0xf2,0x56,0xb3,0xf5,0x00,0x40,0x40,0x92,0x24,0x73,0x72,0x25,
    0x81,0xa4,0xaa,0x3b,0xb3,0x6b,0x3a,0x14,0x00,0x60,0xb6,0x81,
    0xaa,0x1b,0xa7,0x9e,0x99,0xe3,0x0a,0x09,0x24,0x66,0x68,0x1e,
    0x00,0xc0,0x22,0x39,0xb5,0xae,0xeb,0xe4,0x5b,0x99,0xad,0xee,
    0xf5,0xb4,0xaa,0xf5,0xa9,0x54,0xbd,0x50,0x0b,0x00,0x16,0xc5,
    0xb5,0xbb,0x4a,0xaa,0x6a,0x72,0xed,0x7a,0x2a,0x51,0xb5,0x13,
    0xaa,0x02,0xdf,0x06,0x80,0xd9,0x86,0x86,0xfe,0xc0,0xdd,0x69,
    0xba,0x85,0x6e,0x68,0x00,0x00,0x00,0x00,0x60,0x9b,0x01,0x00,
    0x00,0x00,0x66,0x1b,0x1a,0x22,0x27,0xd7,0x24,0x49,0x24,0x49,
    0xe2,0x78,0xfc,0x28,0x07,0x00,0x24,0x02,0x7d,0xa5,0x92,0x33,
    0x7d,0x5d,0x27,0x49,0xaa,0x3b,0x53,0xb9,0xfb,0xfb,0x16,0x5f,
    0x69,0x00,0x38,0x05,0xab,0x6a,0x5d,0xa6,0x6a,0xd6,0xfa,0x54,
    0x3d,0x6b,0xad,0xaa,0xcf,0xfb,0xaa,0x5a,0x0b,0xdb,0x02,0x00,
    0x05,0xba,0x77,0xae,0xe9,0xde,0xb9,0x86,0x4e,0xa6,0x73,0xf2,
    0xce,0xa3,0x93,0xb0,0x7d,0x0e,0x00,0x34,0x68,0xe8,0x39,0xe8,
    0x86,0x6e,0xe8,0x86,0x66,0x9b,0x01,0x00,0x2c,0x74,0xe7,0x99,
    0x39,0xae,0x5e,0x49,0x92,0x70,0x72,0x8d,0xaa,0x04,0xdb,0x33,
    0x00,0x70,0x62,0x91,0x4e,0x6d,0x5d,0x95,0xcf,0x7b,0x3a,0xb3,
    0x74,0x79,0xd6,0xd2,0xf9,0xbc,0x81,0xf5,0x00,0x40,0x11,0xae,
    0xed,0x4a,0xcd,0x5d,0xf5,0x49,0xee,0x3b,0x6f,0xf2,0xbd,0x93,
    0x2b,0xe5,0xfb,0x86,0x2d,0x0f,0x00,0x34,0x78,0xb6,0x75,0xd9,
    0x55,0xb3,0xea,0xae,0x7a,0x56,0x55,0xd5,0xe7,0xfd,0x56,0xed,
    0xb5,0x1e,0x58,0x00,0xa0,0x40,0xf7,0xce,0x35,0xdd,0x3b,0xd7,
    0xd0,0xc9,0x74,0x4e,0xde,0x79,0x74,0x12,0xb6,0xcf,0x01,0x80,
    0x69,0x1f,0x1e,0x2d,0xa9,0x9c,0xbf,0x35,0x95,0xf3,0xbe,0x53,
    0x39,0xef,0x3b,0x9c,0xbc,0xc5,0xf6,0x1b,0x00,0x48,0x84,0xb2,
    0xd5,0x74,0xed,0x6d,0xba,0x76,0xd5,0x74,0xed,0xaa,0x61,0xbf,
    0x35,0x6c,0x3d,0x00,0x10,0x30,0xc7,0xa5,0x25,0x09,0x39,0xb9,
    0x66,0x4e,0xae,0x90,0x24,0x38,0xae,0x01,0x80,0x05,0x16,0xae,
    0xf5,0xa9,0x3d,0x9e,0x55,0x95,0x5a,0x9f,0xaa,0x7e,0x57,0x55,
    0x99,0x9b,0x43,0x00,0x00,0x85,0xda,0x55,0x97,0xaa,0x9a,0xee,
    0xda,0x4f,0x3d,0xaa,0x6a,0xbb,0x76,0x55,0xa1,0x7c,0x01,0x40,
    0xa2,0x48,0x76,0xd5,0xcc,0x56,0xe3,0x53,0xf5,0xd4,0xe7,0x53,
    0xbb,0xf6,0xcc,0xae,0xaa,0x0f,0xe5,0xdb,0x00,0x50,0x14,0xb3,
    0xbd,0xb5,0xe6,0x38,0x31,0x47,0x62,0x8e,0xc4,0x9c,0x24,0x4d,
    0xa4,0x01,0x60,0xda,0x83,0xee,0x2a,0xb4,0x67,0xd8,0x6b,0x66,
    0x8e,0xa7,0x48,0x40,0xb3,0x00,0x60,0xb6,0x8b,0xd9,0x75,0x45,
    0x3a,0x49,0xa7,0x77,0xde,0x99,0xdd,0x57,0xd2,0xdd,0x49,0x68,
    0x1f,0x00,0x80,0x22,0xdd,0x55,0x57,0xba,0x6b,0x72,0xba,0xbf,
    0x57,0xd2,0x5d,0x77,0xfa,0xbe,0xab,0xc2,0xd7,0x03,0x00,0x14,
    0xe4,0xbe,0xeb,0xda,0xfb,0xbe,0xa7,0x92,0xba,0x53,0x89,0xaf,
    0x16,0xc7,0x35,0x6c,0x33,0x00,0x30,0xed,0x41,0x77,0x15,0xda,
    0x33,0xec,0x35,0x33,0xc7,0x53,0x24,0xa0,0x59,0x00,0xb0,0x58,
    0xcc,0x36,0x6b,0xc1,0x5a,0xc5,0x12,0x95,0xf7,0x2d,0xf7,0xfd,
    0x79,0xd1,0x0c,0x00,0x2c,0xb0,0xa8,0x5a,0xb3,0x3d,0xb5,0x50,
    0x45,0x77,0x3d,0xa3,0x3b,0x41,0x6b,0x00,0x00,0xc8,0xc9,0x35,
    0x92,0x84,0x9c,0x5c,0x23,0x49,0xcc,0xc9,0x15,0x44,0x00,0x40,
    0x13,0xfe,0x6a,0x4f,0x3e,0x9f,0x5d,0x57,0x3e,0x9f,0xaa,0x2b,
    0x9f,0xbf,0xda,0x93,0xcf,0xa7,0x2a,0x16,0x5f,0xfd,0x05,0x80,
    0x69,0x0f,0xd3,0xfd,0x94,0xe9,0x7e,0xca,0x6c,0xc3,0x75,0x94,
    0x84,0xb7,0xc2,0xd6,0x03,0x00,0xb3,0x0d,0x7f,0x8d,0xa4,0x72,
    0x9e,0x80,0xc8,0xc9,0x35,0x73,0x72,0x05,0x11,0x00,0x30,0x5b,
    0xf3,0xa9,0x92,0xfe,0xd4,0x7d,0xfc,0xba,0x76,0x32,0xf7,0x7d,
    0x27,0xbf,0xae,0x3b,0xdf,0x1f,0xdb,0x02,0x00,0x6e,0xcd,0xec,
    0x16,0xba,0x0f,0xe9,0x4e,0x76,0xba,0x93,0x9c,0xef,0xfd,0xcd,
    0x97,0x12,0x00,0x30,0xc7,0xc5,0x9c,0x5c,0xc9,0x9c,0x5c,0xc9,
    0x8f,0x25,0xcb,0x5e,0xdb,0xa2,0xd6,0x82,0x2c,0x00,0x98,0x6d,
    0x68,0xc8,0xa7,0x76,0xae,0xf9,0x54,0x25,0xf3,0xa9,0x4a,0x46,
    0xed,0x5c,0x03,0x00,0xff,

};

BYTE code tPALETTE_FAC0[] =
{
    0,0,0,// 0 
    255,0,0,// 1 select
    57,  57,  57,//     8,72,8,//Green 2
    255,255,255,// 3
    148,148,148,// 4
    16, 112, 247,// 5
    222,222,55,// 6
    100,180,180,
    100,180,180,
    100,180,180,
    100,180,180,
    100,180,180,
    100,180,180,
    100,180,180,
    100,180,180,
    100,180,180,
};

//--------------------------------------------------
// Windows  Table
//--------------------------------------------------
#define _WINDOW_ENABLE                              0x01
#define _BORDER1_1_PIXEL                            0x00
#define _BORDER0_1_PIXEL                            0
#define _1_LEVEL_RER_GRADIENT                       0x20

BYTE code tOSD_WINDOW_0_FACTORY_MEMU[] =
{
    WINNO(0),
    0x00,// Byte 0 of 104h
    0x00,// Byte 1 of 104h
    0x00,// Byte 2 of 104h
    0x00,// Byte 0 of 107h    
    _1_LEVEL_RER_GRADIENT | (5 &0x1F),// Byte 1 of 107h
    0x8D//(_WINDOW_ENABLE)//0x8D                         // Byte 2 of 107h
};
BYTE code tOSD_WINDOW_0_FACTORY_MEMU_1[] =
{
    WINNO(1),
    0x00,// Byte 0 of 104h
    0x00,// Byte 1 of 104h
    0x00,// Byte 2 of 104h
    0x00,// Byte 0 of 107h    
    _1_LEVEL_RER_GRADIENT | (2 &0x1F),// Byte 1 of 107h
    0x8D//(_WINDOW_ENABLE)//0x8D                         // Byte 2 of 107h
};

BYTE code tOSD_WINDOW_0_FACTORY_MEMU_2[] =
{
    WINNO(2),
    0x00,// Byte 0 of 104h
    0x00,// Byte 1 of 104h
    0x00,// Byte 2 of 104h
    0x00,// Byte 0 of 107h    
    _1_LEVEL_RER_GRADIENT | (6 &0x1F),// Byte 1 of 107h
    0x8D//(_WINDOW_ENABLE)//0x8D                         // Byte 2 of 107h
};

#if(_KAILI_FAC_LANGUAGE == _ON)
BYTE code tOSD_FACTORY_TEXT_STR[] =
{
//PAGE 1
    _A,_u,_t,_o,_SPACE,_C,_o,_l,_o,_r,_NEXT_,//_BEACON_FAC_OSD_AUTO_COLOR
    _G,_a,_m,_m,_a,_NEXT_,//_BEACON_FAC_OSD_GAMMA

#if(_CUSTOMER == _CUS_BAISHENG)
    _B,_r,_i,_g,_h,_t,_n,_e,_s,_s,_NEXT_,//_BEACON_FAC_OSD_DBRIGHTNESS
#else
    _D,_B,_r,_i,_g,_h,_t,_n,_e,_s,_s,_NEXT_,//_BEACON_FAC_OSD_DBRIGHTNESS
#endif
    _C,_o,_n,_t,_r,_a,_s,_t,_NEXT_,//_BEACON_FAC_OSD_CONTRAST
#if(_CUSTOMER == _CUS_BAISHENG)
    _B,_a,_c,_k,_l,_i,_g,_h,_t,_NEXT_,//_BEACON_FAC_OSD_BACKLIGHT
#else
    _B,_r,_i,_g,_h,_t,_n,_e,_s,_s,_NEXT_,//_BEACON_FAC_OSD_BACKLIGHT
#endif
    _C,_o,_l,_o,_r,_SPACE,_T,_e,_m,_p,_NEXT_,//_BEACON_FAC_OSD_CT_TYPE
    _R,_NEXT_,//_BEACON_FAC_OSD_CT_R
    _G,_NEXT_,//_BEACON_FAC_OSD_CT_G
    _B,_NEXT_,//_BEACON_FAC_OSD_CT_B
    _B,_a,_c,_k,_l,_i,_g,_h,_t,_SPACE,_H,_NEXT_,//_BEACON_FAC_OSD_BL_MAX
    _B,_a,_c,_k,_l,_i,_g,_h,_t,_SPACE,_M,_NEXT_,//_BEACON_FAC_OSD_BL_MID
    _B,_a,_c,_k,_l,_i,_g,_h,_t,_SPACE,_L,_NEXT_,//_BEACON_FAC_OSD_BL_MIN
    _A,_g,_i,_n,_g,_NEXT_,//_BEACON_FAC_OSD_BURN
    _A,_u,_t,_o,_S,_c,_a,_n,_NEXT_,//_BEACON_FAC_OSD_SOURCE_DET_TYPE //FAC_ADD_SOURCE_DET_ON_OFF_20151223 add
    _F,_a,_c,_t,_o,_r,_y,_R,_e,_s,_e,_t,_NEXT_,//_BEACON_FAC_OSD_RESET 
    _N,_e,_x,_t,_P,_a,_g,_e,_NEXT_,//NEXT PAGE
    _E,_x,_i,_t,_NEXT_,//_BEACON_FAC_OSD_EXIT
    _NEXT_,
    _NEXT_,
    _S,_N,_COLON,_END_,// Monitor SN

//PAGE 2 Only for test
    _S,_h,_a,_r,_p,_n,_e,_s,_s,_NEXT_,//_BEACON_FAC_OSD_SHARPNESS

    _S,_a,_t,_u,_r,_a,_t,_i,_o,_n,_NEXT_,//_BEACON_FAC_OSD_SATURATION
#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
    0x74,0x75,0x76,0x77,_NEXT_,//_BEACON_FAC_OSD_UART_ENABLE
#endif
    _H,_P,_o,_s,_NEXT_,//_BEACON_FAC_OSD_TEST1
    _V,_P,_o,_s,_NEXT_,//_BEACON_FAC_OSD_TEST2

    _D,_C,_l,_o,_c,_k,_R,_a,_n,_g,_e,_NEXT_,//_BEACON_FAC_OSD_TEST5
    _F,_M,_D,_I,_V,_NEXT_,//_BEACON_FAC_OSD_FMDVI
    _E,_E,_P,_R,_O,_M,_NEXT_,//_BEACON_FAC_OSD_TEST6
    _D,_d,_c,_c,_i,_C,_h,_a,_n,_e,_l,_NEXT_,//_BEACON_FAC_OSD_TEST7


#if(_SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)
    _L,_o,_a,_d,_SPACE,_G,_A,_M,_M,_A,_NEXT_,// _BEACON_FAC_OSD_SAVE_GAMMA_TO_EEPROM
    _S,_a,_v,_e,_SPACE,_G,_A,_M,_M,_A,_NEXT_,// _BEACON_FAC_OSD_SAVE_GAMMA_TO_EEPROM

#endif

#if(_ALS_TYPE != _SENSER_NONE)
    _A,_L,_S,_SPACE,_S,_W,_I,_T,_C,_H,_NEXT_,
#endif

    _L,_a,_s,_t,_P,_a,_g,_e,_NEXT_,// _BEACON_FAC_OSD_PAGE1
    _N,_e,_x,_t,_P,_a,_g,_e,_NEXT_,// _BEACON_FAC_OSD_PAGE3
    _E,_x,_i,_t,_NEXT_,//_BEACON_FAC_OSD_EXIT2
#if(_SAVE_GAMMA_TO_EEPROM_ON_LINE != _ON)
    _NEXT_,//
#endif
    _V,_e,_r,_s,_i,_o,_n,_COLON,_NEXT_,//¡ã?¡À?o?
    _M,_o,_d,_e,_l,_COLON,_NEXT_,//?¨²D¨ª
    _P,_a,_n,_e,_l,_COLON,_NEXT_,//?¨¢D¨ªo?
    _S,_c,_a,_l,_e,_r,_COLON,_NEXT_,//D???
    _D,_a,_t,_e,_COLON,_NEXT_,//¨¨??¨²
    _S,_V,_N,_COLON,_END_,//

//PAGE 3 Only for test no save
#if(_SIX_COLOR_SUPPORT == _ON)
    _R,_SPACE,_S,_A,_T,_NEXT_,
    _Y,_SPACE,_S,_A,_T,_NEXT_,
    _G,_SPACE,_S,_A,_T,_NEXT_,
    _C,_SPACE,_S,_A,_T,_NEXT_,
    _B,_SPACE,_S,_A,_T,_NEXT_,
    _M,_SPACE,_S,_A,_T,_NEXT_,

    _R,_SPACE,_H,_U,_E,_NEXT_,
    _Y,_SPACE,_H,_U,_E,_NEXT_,
    _G,_SPACE,_H,_U,_E,_NEXT_,
    _C,_SPACE,_H,_U,_E,_NEXT_,
    _B,_SPACE,_H,_U,_E,_NEXT_,
    _M,_SPACE,_H,_U,_E,_NEXT_,
#else
    _G,_A,_M,_M,_A,_SPACE,_B,_Y,_P,_A,_S,_S,_NEXT_,
    _D,_C,_L,_K,_NEXT_,
    _P,_W,_M,_SPACE,_F,_R,_E,_Q,_NEXT_,
    _F,_L,_A,_S,_H,_SPACE,_W,_P,_NEXT_,
    _G,_R,_A,_Y,_SPACE,_L,_E,_V,_E,_L,_NEXT_,
#endif
    _E,_x,_i,_t,_END_,


};
#else
BYTE code tOSD_FACTORY_TEXT_STR[] =
{
//PAGE 1
    0x49,0x4a,0x4b,0x4c,_NEXT_,//_BEACON_FAC_OSD_AUTO_COLOR
    0x4d,0x4e,0x0e,0x70,0x71,0x0f,_NEXT_,//_BEACON_FAC_OSD_GAMMA

    0x54,0x55,0x56,0x57,0x0e,0x70,0x71,0x0f,_NEXT_,//_BEACON_FAC_OSD_DBRIGHTNESS
    0x58,0x59,0x5a,0x0e,0x70,0x71,0x0f,_NEXT_,//_BEACON_FAC_OSD_CONTRAST
    0x56,0x57,0x0e,0x70,0x71,0x0f,_NEXT_,//_BEACON_FAC_OSD_BACKLIGHT
    0x4f,0x50,0x0e,0x70,0x71,0x0f,_NEXT_,//_BEACON_FAC_OSD_CT_TYPE
    0x51,_NEXT_,//_BEACON_FAC_OSD_CT_R
    0x52,_NEXT_,//_BEACON_FAC_OSD_CT_G
    0x53,_NEXT_,//_BEACON_FAC_OSD_CT_B
    0x5b,0x5c,0x56,0x57,_NEXT_,//_BEACON_FAC_OSD_BL_MAX
    0x70,0x71,0x56,0x57,_NEXT_,//_BEACON_FAC_OSD_BL_MID
    0x5b,0x5d,0x56,0x57,_NEXT_,//_BEACON_FAC_OSD_BL_MIN
    0x60,0x61,_NEXT_,//_BEACON_FAC_OSD_BURN
    0x8d,0x8e,0x8f,0x90,0x91,0x92,_NEXT_,//_BEACON_FAC_OSD_SOURCE_DET_TYPE //FAC_ADD_SOURCE_DET_ON_OFF_20151223 add
    0x6c,0x6d,0x6e,0x6f,_NEXT_,//_BEACON_FAC_OSD_RESET 
    0x7f,0x80,0x81,_NEXT_,//NEXT PAGE
    0x7a,0x7b,_NEXT_,//_BEACON_FAC_OSD_EXIT
    _NEXT_,
    _NEXT_,
    _S,_N,_COLON,_END_,// Monitor SN

//PAGE 2 Only for test
    0x82,0x83,0x84,_NEXT_,//_BEACON_FAC_OSD_SHARPNESS
    0x86,0x87,0x88,0x89,0x8a,_NEXT_,//_BEACON_FAC_OSD_SATURATION
#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
    0x74,0x75,0x76,0x77,_NEXT_,//_BEACON_FAC_OSD_UART_ENABLE
#endif
    0x62,0x63,0x64,0x65,0x66,0x67,_NEXT_,//_BEACON_FAC_OSD_TEST1
    0x62,0x63,0x68,0x69,0x66,0x67,_NEXT_,//_BEACON_FAC_OSD_TEST2
    0x6a,0x6b,_NEXT_,//_BEACON_FAC_OSD_TEST5
    _F,_M,_D,_I,_V,_NEXT_,//_BEACON_FAC_OSD_FMDVI
    _E,_E,_P,_R,_O,_M,0x7c,0x7d,0x7e,_NEXT_,//_BEACON_FAC_OSD_TEST6
    _D,_D,_C,_C,_I,0x8b,0x8c,_NEXT_,//_BEACON_FAC_OSD_TEST7

#if(_SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)
    _L,_o,_a,_d,_SPACE,_G,_A,_M,_M,_A,_NEXT_,// _BEACON_FAC_OSD_SAVE_GAMMA_TO_EEPROM
    _S,_a,_v,_e,_SPACE,_G,_A,_M,_M,_A,_NEXT_,// _BEACON_FAC_OSD_SAVE_GAMMA_TO_EEPROM
#endif

#if(_ALS_TYPE != _SENSER_NONE)
    _A,_L,_S,_SPACE,_S,_W,_I,_T,_C,_H,_NEXT_,
#endif

    0x85,0x80,0x81,_NEXT_,// _BEACON_FAC_OSD_PAGE1
    0x9d,0x9e,0x9f,0xa0,_NEXT_,// _BEACON_FAC_OSD_PAGE3
    0x7a,0x7b,_NEXT_,//_BEACON_FAC_OSD_EXIT2
#if(_SAVE_GAMMA_TO_EEPROM_ON_LINE != _ON)
    _NEXT_,
#endif
    0x78,0x79,0x96,_COLON,_NEXT_,//¡ã?¡À?o?
    0x94,0x95,_COLON,_NEXT_,//?¨²D¨ª
    0x93,0x95,0x96,_COLON,_NEXT_,//?¨¢D¨ªo?
    0x97,0x98,_COLON,_NEXT_,//D???
    0x99,0x9a,_COLON,_NEXT_,//¨¨??¨²
    _S,_V,_N,_COLON,_END_,//

//PAGE 3 Only for test no save
#if(_SIX_COLOR_SUPPORT == _ON)
    _R,_SPACE,_S,_A,_T,_NEXT_,
    _Y,_SPACE,_S,_A,_T,_NEXT_,
    _G,_SPACE,_S,_A,_T,_NEXT_,
    _C,_SPACE,_S,_A,_T,_NEXT_,
    _B,_SPACE,_S,_A,_T,_NEXT_,
    _M,_SPACE,_S,_A,_T,_NEXT_,

    _R,_SPACE,_H,_U,_E,_NEXT_,
    _Y,_SPACE,_H,_U,_E,_NEXT_,
    _G,_SPACE,_H,_U,_E,_NEXT_,
    _C,_SPACE,_H,_U,_E,_NEXT_,
    _B,_SPACE,_H,_U,_E,_NEXT_,
    _M,_SPACE,_H,_U,_E,_NEXT_,
#else
    _G,_A,_M,_M,_A,_SPACE,_B,_Y,_P,_A,_S,_S,_NEXT_,
    _D,_C,_L,_K,_NEXT_,
    _P,_W,_M,_SPACE,_F,_R,_E,_Q,_NEXT_,
    _F,_L,_A,_S,_H,_SPACE,_W,_P,_NEXT_,
    _G,_R,_A,_Y,_SPACE,_L,_E,_V,_E,_L,_NEXT_,
#endif

    _E,_x,_i,_t,_END_,

};
#endif
BYTE code tVersion_Str[] = _VERSION_STR;
BYTE code tPanel_Str[] =  _PANEL_STR;
BYTE code tModel_Str[] = _MODEL_STR;
BYTE code tScaler_Str[] = _SCALER_STR;


BYTE code tOSD_BEACON_FAC_COLORTEMP0[] =
{
#if(_COLOR_TEMP_SELECT_TYPE == _6500K_9300K)
    _SPACE,_6,_5,_0,_0,_K,_END_,//English
    _SPACE,_6,_5,_0,_0,_K,_END_,//Chinese
#elif(_COLOR_TEMP_SELECT_TYPE == _6700K_9300K)
    _SPACE,_6,_7,_0,_0,_K,_END_,//English
    _SPACE,_6,_7,_0,_0,_K,_END_,//Chinese
#elif(_COLOR_TEMP_SELECT_TYPE == _13000K_9300K)
    _1,_3,_0,_0,_0,_K,_END_,//English
    _1,_3,_0,_0,_0,_K,_END_,//Chinese
#elif(_COLOR_TEMP_SELECT_TYPE == _11000K_9300K)
    _1,_1,_0,_0,_0,_K,_END_,//English
    _1,_1,_0,_0,_0,_K,_END_,//Chinese
#elif((_COLOR_TEMP_SELECT_TYPE == _9300K_13000K)||(_COLOR_TEMP_SELECT_TYPE == _9300K_6500K))
    _SPACE,_9,_3,_0,_0,_K,_END_,//English
    _SPACE,_9,_3,_0,_0,_K,_END_,//Chinese
#elif(_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K)
    _1,_4,_0,_0,_0,_K,_END_,//English
    _1,_4,_0,_0,_0,_K,_END_,//Chinese
#elif(_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal)
    _SPACE,_SPACE,_S,_t,_d,_DOT,_END_,
    _SPACE,_SPACE,_SPACE,_SPACE,0x9F,0xA0,_END_,//Chinese
#elif((_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND)||(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K))
    _SPACE,_SPACE,_SPACE,_SPACE,_SPACE,_7,_5,_0,_0,_K,_END_,//English
    _SPACE,_SPACE,_SPACE,_SPACE,_SPACE,_7,_5,_0,_0,_K,_END_,//Chinese
#endif
};
BYTE code tOSD_BEACON_FAC_COLORTEMP1[] =
{
#if((_COLOR_TEMP_SELECT_TYPE == _6500K_9300K)||(_COLOR_TEMP_SELECT_TYPE == _6700K_9300K)||\
        (_COLOR_TEMP_SELECT_TYPE == _13000K_9300K)||(_COLOR_TEMP_SELECT_TYPE == _11000K_9300K))
    _SPACE,_9,_3,_0,_0,_K,_END_,//English
    _SPACE,_9,_3,_0,_0,_K,_END_,//Chinese
#elif(_COLOR_TEMP_SELECT_TYPE == _9300K_13000K)
    _1,_3,_0,_0,_0,_K,_END_,//English
    _1,_3,_0,_0,_0,_K,_END_,//Chinese
#elif(_COLOR_TEMP_SELECT_TYPE == _9300K_6500K)
    _SPACE,_6,_5,_0,_0,_K,_END_,//English
    _SPACE,_6,_5,_0,_0,_K,_END_,//Chinese
#elif(_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K)
    _1,_1,_0,_0,_0,_K,_END_,//English
    _1,_1,_0,_0,_0,_K,_END_,//Chinese
#elif(_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal)
    _SPACE,_SPACE,_C,_o,_o,_l,_END_,//English         
    _SPACE,_SPACE,_SPACE,_SPACE,0x9E,0x5A,_END_,//Chinese
#elif((_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND)||(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K))
    _SPACE,_SPACE,_SPACE,_SPACE,_1,_3,_0,_0,_0,_K,_END_,//English
    _SPACE,_SPACE,_SPACE,_SPACE,_1,_3,_0,_0,_0,_K,_END_,//Chinese
#endif

};

BYTE code tOSD_BEACON_FAC_COLORTEMP2[] =
{
#if(_CUSTOMER == _CUS_TOSHIBA)
    _SPACE,_SPACE,_SPACE,_SPACE,_SPACE,_SPACE,_U,_s,_e,_r,_END_,//English 
    _SPACE,_SPACE,_SPACE,_SPACE,_SPACE,_SPACE,_SPACE,_SPACE,0x77,0x78,_END_,//Chinese    
#else
    _SPACE,_SPACE,_U,_s,_e,_r,_END_,//English 
    _SPACE,_SPACE,_SPACE,_SPACE,0x77,0x78,_END_,//Chinese
#endif
};

#if((_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K) || \
    (_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal) || \
    (_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND))
BYTE code tOSD_BEACON_FAC_COLORTEMP3[] =
{
#if(_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K)
    _SPACE,_9,_3,_0,_0,_K,_END_,//English
    _SPACE,_9,_3,_0,_0,_K,_END_,//Chinese
#elif(_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal)
    _SPACE,_SPACE,_W,_a,_r,_m,_END_,//English                   
    _SPACE,_SPACE,_SPACE,_SPACE,0x9D,0x5A,_END_,//Chinese
#elif(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND)
    _U,_l,_t,_r,_a,_s,_o,_u,_n,_d,_END_,//English
    _U,_l,_t,_r,_a,_s,_o,_u,_n,_d,_END_,//Chinese
#endif
};
#endif

code BYTE *tOSD_BEACON_FAC_COLORTEMP[4] =
{
    tOSD_BEACON_FAC_COLORTEMP0,
    tOSD_BEACON_FAC_COLORTEMP1,
#if((_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K) || \
    (_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal) || \
    (_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND))
    tOSD_BEACON_FAC_COLORTEMP3,
#endif
#if(_COLOR_TEMP_SELECT_TYPE != _14000K_11000K_9300K)
    tOSD_BEACON_FAC_COLORTEMP2,
#endif   
};

BYTE code tOSD_BEACON_FAC_DDCCI_CHANNEL0[] =  // Auto
{
#if(_KAILI_FAC_LANGUAGE == _ON)
    _A,_u,_t,_o,_END_,
#else
    _SPACE,_SPACE,0x8d,0x8e,_END_,
#endif
};
BYTE code tOSD_BEACON_FAC_DDCCI_CHANNEL1[] =  // A0 Port
{
    _SPACE,_SPACE,_A,_0,_END_,
};
BYTE code tOSD_BEACON_FAC_DDCCI_CHANNEL2[] =  // D0 Port
{
    _SPACE,_SPACE,_D,_0,_END_,
};
BYTE code tOSD_BEACON_FAC_DDCCI_CHANNEL3[] =  // D1 Port
{
    _SPACE,_SPACE,_D,_1,_END_,
};
BYTE code tOSD_BEACON_FAC_DDCCI_CHANNEL4[] =  // D3 Port
{
    _SPACE,_SPACE,_D,_3,_END_,
};

BYTE code tOSD_BEACON_FAC_YES[] =
{
#if(_KAILI_FAC_LANGUAGE == _ON)
    _Y,_e,_s,_END_,
#else
    _SPACE,_SPACE,0x9b,_END_,
#endif
};

BYTE code tOSD_BEACON_FAC_NO[] =
{
#if(_KAILI_FAC_LANGUAGE == _ON)
    _SPACE,_N,_o,_END_,
#else
    _SPACE,_SPACE,0x9c,_END_,
#endif
};

code BYTE *tOSD_BEACON_FAC_YES_OR_NO[2] =
{
    tOSD_BEACON_FAC_NO,tOSD_BEACON_FAC_YES,
};

code BYTE *tOSD_BEACON_FAC_DDCCI_CHANNEL[] =
{
    tOSD_BEACON_FAC_DDCCI_CHANNEL0,
    tOSD_BEACON_FAC_DDCCI_CHANNEL1,
    tOSD_BEACON_FAC_DDCCI_CHANNEL2,
    tOSD_BEACON_FAC_DDCCI_CHANNEL3,
    tOSD_BEACON_FAC_DDCCI_CHANNEL4,
};

code StructBeaconFacType g_stBeaconFacDataDefault= 
{
     _DEFAULT_COLOR_TEMP,           // ucBeaconFacCTType
     _DEFAULT_BRIGHTNESS,           // ucBeaconFacDBrightness
     _DEFAULT_CONTRAST,             // ucBeaconFacContrast
     _DEFAULT_BACKLIGHT,            // ucBeaconFacBacklight
     _BACKLIGHT_REG_VALUE_MAX,      // ucBeaconFacBLMAX
     _BACKLIGHT_REG_VALUE_DEF,      // ucBeaconFacBLMID
     _BACKLIGHT_REG_VALUE_MIN,      //ucBeaconFacBLMIN	
 #if(_SECOND_COLORTEMP_THREE_POINT == _ON)
     _BACKLIGHT_SECOND_REG_VALUE_MAX,   // ucBeaconFacBLMAX
     _BACKLIGHT_SECOND_REG_VALUE_DEF,   // ucBeaconFacBLMID
     _BACKLIGHT_SECOND_REG_VALUE_MIN,   //ucBeaconFacBLMIN	
 #endif     
     _DEFAULT_GAMMA,                // ucBeaconFacGamma
     _ON,                           // ucBeaconFacBurn
#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
     _FACTORY_UART_ENABLE,          // ucBeaconFacPin62Pin63Func
#endif

    _DEFAULT_DDCCI_CHANNEL,        // DDCCI    == auto

    _DCLK_SPREAD_SPEED,             // BYTE ucBeaconFMDIV : 1   
#if(_SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)
     _LOAD_GAMMA_FROM_EEPROM,
     _SAVE_GAMMA_TO_EEPROM,
#endif
#if(_ALS_TYPE != _SENSER_NONE)
    _ALS_DEFAULT_SWITCH,
#endif
    _EEPROM_WP_ENABLE,                  // BYTE reserve;
    _OFF,
#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
    _ON,                             // BYTE bBackLightSensor_ONOFF
#endif    
//< (_DATA_ITEM_LENGTH - 2)
};

StructBeaconFacType g_stBeaconFacData;

#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
BYTE xdata ucIICControl1=0;
BYTE xdata ucIICControl2=0;
BYTE xdata ucIICControl3=0;
BYTE xdata ucIICControl4=0;
BYTE xdata ucIICControl5=0;




#if( _SAVE_GAMMA_TO_EEPROM_ON_LINE	 == _ON)
WORD xdata usArray;
#endif

bit  idata g_bGammaByPass = 0;
StructGammaRGBType stGammaRGBdata;
#endif

BYTE xdata ucMonitorSn[_MONITOR_SN_LENGTH]={0};

#if(_SAVE_GAMMA_TO_FLASH_ON_LINE == _ON)
BYTE xdata g_ucGammaIndex = 0;
WORD xdata g_usDataIndex = 0;
BYTE xdata g_ucDataCount= 0;
#endif 


WORD xdata g_ucFactoryAdjustHstart;
WORD xdata g_ucFactoryAdjustVstart;
WORD xdata g_ucFactoryHstartMid;
WORD xdata g_ucFactoryVstartMid;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void BeaconFactorySaveData(void);
void BeaconFactoryLoadData(void);
void BeaconFactoryRestoreData(void);

#if(_VGA_SUPPORT == _ON)
void BeaconFactoryAutoColor(void);

void BeaconFactoryAutoColor(void)
{

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        // Perform auto-color for RGB
        if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_RGB) == _AUTO_SUCCESS)
        {
            ScalerAutoGetAutoColorResult(&g_stAdcData);
            UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
            // Calculate YPbPr gain/offset using formula
            g_stAdcData = ScalerAutoBalanceYPbPrFromFormula(&g_stAdcData);
            UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);

            // Restore RGB gain/offset
            ScalerAutoGetAutoColorResult(&g_stAdcData);
#endif
        }
        else
        {
            UserCommonNVRamRestoreADCSetting();
        }
    }
#endif // End of #if(_VGA_SUPPORT == _ON)
}
#endif
//----------------------------------------------------------------------------------------------------
// Beacon Factory OSD Data Function
//----------------------------------------------------------------------------------------------------
DWORD BeaconFactoryFuncValueChange(DWORD Value,DWORD MaxValue,DWORD MinValue,bit loop)
{
    BYTE ucStep = 1;

    if(GET_KEYREPEATSTART())
    {
        if(MaxValue>1000)
        {
            ucStep = 255;
            if(Value<1000)
                ucStep = 10;
            else if(MaxValue<100)
                ucStep = 2;
        }
        else if(MaxValue>254)
        {
            ucStep = 3;
        }
        else if(MaxValue>99)
        {
            ucStep = 2;
        }
    }

#if 1

    if(((_BEACON_FAC_OSD_NONE<g_ucBeaconFacOsdState)&&(g_ucBeaconFacOsdState<_BEACON_FAC_OSD_SELECT_END)) || ((_BEACON_FAC_PAGE2_START<g_ucBeaconFacOsdState)&&(g_ucBeaconFacOsdState<_BEACON_FAC_PAGE2_SELECT_END)))
    {
        if(_RIGHT_KEY_MESSAGE == GET_KEYMESSAGE())//
        {
            Value+=ucStep;
            if((Value > MaxValue)&&(loop == _ON))
            {
                return MinValue;
            }
            else if((Value > MaxValue)&&(loop == _OFF))
            {
                return MaxValue;
            }
        }
        else if(_LEFT_KEY_MESSAGE == GET_KEYMESSAGE())
        {
            Value-=ucStep;

            if(((Value < MinValue)||(Value >= 65500000))&&(loop == _ON))//65500000 is for check overflow
            {
                return MaxValue;
            }
            else if(((Value < MinValue)||(Value >= 65500000))&&(loop == _OFF))
            {
                return MinValue;
            }
        }
    }
    else //if(((_BEACON_FAC_OSD_SELECT_END<g_ucBeaconFacOsdState)&&(g_ucBeaconFacOsdState<_BEACON_FAC_OSD_ADJUST_END)) || ((_BEACON_FAC_PAGE2_SELECT_END<g_ucBeaconFacOsdState)&&(g_ucBeaconFacOsdState<_BEACON_FAC_PAGE2_ADJUST_END)))
    {
        if(_LEFT_KEY_MESSAGE == GET_KEYMESSAGE())//_LEFT_KEY_MESSAGE
        {
            Value+=ucStep;
            if((Value > MaxValue)&&(loop == _ON))
            {
                return MinValue;
            }
            else if((Value > MaxValue)&&(loop == _OFF))
            {
                return MaxValue;
            }
        }
        else if(_RIGHT_KEY_MESSAGE == GET_KEYMESSAGE())
        {
            Value-=ucStep;

            if(((Value < MinValue)||(Value >= 65500000))&&(loop == _ON))//65500000 is for check overflow
            {
                return MaxValue;
            }
            else if(((Value < MinValue)||(Value >= 65500000))&&(loop == _OFF))
            {
                return MinValue;
            }
        }
    }


#else
    if(_RIGHT_KEY_MESSAGE == GET_KEYMESSAGE())//
    {
        Value+=ucStep;
        if((Value > MaxValue)&&(loop == _ON))
        {
            return MinValue;
        }
        else if((Value > MaxValue)&&(loop == _OFF))
        {
            return MaxValue;
        }
    }
    else if(_LEFT_KEY_MESSAGE == GET_KEYMESSAGE())
    {
        Value-=ucStep;

        if(((Value < MinValue)||(Value >= 65500000))&&(loop == _ON))//65500000 is for check overflow
        {
            return MaxValue;
        }
        else if(((Value < MinValue)||(Value >= 65500000))&&(loop == _OFF))
        {
            return MinValue;
        }
    }
#endif

    return Value;

}



void BeaconFactoryFuncHLine(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue, BYTE ucIndicate)
{
    WORD xdata usOsdAddr;
    BYTE xdata i;
    i = ucLength;
    do
    {
        usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + ucLength-i;

        if(ucIndicate == _WRITE_BYTE0)
        {
            ScalerOsdCommandByte(usOsdAddr + g_usFontSelectStart, _OSD_BYTE0, ucValue);
        }
        else if(ucIndicate == _WRITE_BYTE1)
        {
            ScalerOsdCommandByte(usOsdAddr + g_usFontSelectStart, _OSD_BYTE1, ucValue);
        }
        else if(ucIndicate == _WRITE_BYTE2)
        {
            ScalerOsdCommandByte(usOsdAddr + g_usFontSelectStart, _OSD_BYTE2, ucValue);
        }
    }
    while(--i);
}

void BeaconFactoryFuncShowNumber(BYTE ucRow, BYTE ucCol, DWORD usValue, BYTE ucPar)
{
    BeaconFuncShowNumber(ucRow, ucCol,usValue, ucPar);
}

void BeaconFactoryFuncPrintASCII(BYTE ucRow,BYTE ucCol,BYTE ucLen, BYTE *pArray)
{
    BYTE i=0;
    for(i=0;i<ucLen;i++)
    {
        if((*pArray >= 'A')&&(*pArray <= 'Z'))
        {
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, 0x4c, _WRITE_BYTE0);
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, *pArray-0x41+_A, _WRITE_BYTE1);
        }
        if((*pArray >= 'a')&&(*pArray <= 'z'))
        {
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, 0x4b, _WRITE_BYTE0);
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, *pArray-0x61+_a, _WRITE_BYTE1);
        }
        if((*pArray >= '0')&&(*pArray <= '9'))
        {
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, 0x49, _WRITE_BYTE0);//set 10 pixel width
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, *pArray-0x30+_0, _WRITE_BYTE1);
        }
        if((*pArray == '-')||(*pArray == '_'))
        {
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, 0x4A, _WRITE_BYTE0);
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, 0x0b, _WRITE_BYTE1);
        }
        if(*pArray == '.')
        {
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, 0x48, _WRITE_BYTE0);
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, 0x11, _WRITE_BYTE1);
        }
        if(*pArray == '*')
        {
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, 0x4A, _WRITE_BYTE0);
            BeaconFactoryFuncHLine(ucRow, ucCol+i, 1, 0x47, _WRITE_BYTE1);
        }
        pArray++;
    }
}

void BeaconFactoryFuncLoadText(BYTE ucRow, BYTE ucCol, BYTE ucSelect,BYTE *pucArray)
{
    BYTE ucOsdWidth = 0;
    BYTE ucCount = 0;
    BYTE ucHTemp = ucCol;
    BYTE ucSearchCount = 0;
    //ucColor =  COLOR(_CP_WHITE, _LOGO_CP_BG);

    while(_TRUE)
    {
        if(*(pucArray + ucCount) == _END_)
        {
            if(ucSearchCount == ucSelect)
            {
                break;
            }
            else
            {
                pucArray += (ucCount + 1);//Select next row by GET_OSD_LANGUAGE().
                ucCount = 0;
            }
            ucSearchCount++;
        }
        ucCount++;
    }


    ucSearchCount = ucCount = 0;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
        (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucOsdWidth = g_ucOsdHeight;
    }
    else
#endif
    {
        ucOsdWidth = g_ucOsdWidth;
    }

    while(*pucArray != _END_)
    {
        if(*pucArray == _NEXT_)
        {
            ucRow++;
            ucHTemp =ucCol;
            pucArray++;
        }
        else if(*pucArray == _SPACE_)
        {
            ucHTemp++;
            pucArray++;
        }
        else if(*pucArray == _REPEAT_)
        {
            ucCount = *(pucArray + 1) - 1;

            while(ucCount > 0)
            {
                if(*(pucArray - 1) != _SPACE_)
                {
                    // OsdFontPut1Bit(ucRow, ucHTemp, *(pucArray - 1), ucColor);
                    BeaconFuncHLine(ucRow,ucHTemp,1,*(pucArray - 1), _WRITE_BYTE1);
                }

                ucHTemp++;

                if((ucHTemp == ucOsdWidth) && (*(pucArray + 1) != _NEXT_))
                {
                    ucRow++;
                    ucHTemp =ucCol;
                }
                ucCount--;
            }
            pucArray += 2;
        }
        else
        {
            //OsdFontPut1Bit(ucRow, ucHTemp, *pucArray, ucColor);
            BeaconFuncHLine(ucRow,ucHTemp,1,*pucArray, _WRITE_BYTE1);
            ucHTemp++;

            if((ucHTemp == ucOsdWidth) && (*(pucArray + 1) != _NEXT_))
            {
                ucRow++;
                ucHTemp =ucCol;
            }
            pucArray++;
        }
    }
}


void BeaconFactoryFuncApplyMapSetting(BYTE ucHeight,BYTE ucWidth,BYTE ucByte1,BYTE ucColor)
{

    /*ScalerOsdDisableOsd();

    BeaconFuncCloseWindow(_WIN_ALL);

    g_ucOsdWidth = ucByte2;
    g_ucOsdHeight = ucRow;

    // Row Command
    ScalerOsdCharCommandAllByteSeries(0x000, ucByte0, ucByte1, g_ucOsdWidth, g_ucOsdHeight);
    ScalerOsdCharCommandByteSeries((0x000+g_ucOsdHeight), _OSD_BYTE0, 0x00, 1);

    //Set Font and Font Base address
    g_usFontSelectStart = g_ucOsdHeight + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(g_ucOsdWidth * g_ucOsdHeight);
    ScalerOsdFrameControlAllByte(0x004, _OSD_WITHOUT_DB, (BYTE)g_usFontSelectStart, ((g_usFontSelectStart >> 4) & 0xf0) | (g_usFontTableStart & 0x0f), g_usFontTableStart >> 4);

    //Disable win7 blending
    ScalerOsdFrameControlByte(0x003, _OSD_BYTE0, 0x10);
    ScalerOsdFrameControlByte(0x003, _OSD_BYTE1, (_BIT2));*/

    //OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
    BYTE ucI = 0;
    BYTE ucTmp = ucByte1-1; // Row Height = 18

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
        (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucI = ucWidth;
        ucWidth = ucHeight;
        ucHeight = ucI;
        ucTmp = 11;  // Row Height = 12
    }
#endif
    ScalerOsdDisableOsd();
    BeaconFuncCloseWindow(_OSD_WINDOW_ALL);

    // Row Command
    for(ucI = 0; ucI < ucHeight; ucI++)
    {
        ScalerOsdCommandAllByte(ucI, 0x80, ucTmp, ucWidth);
    }

    // Row Command end
    ScalerOsdCommandByte(ucHeight, _OSD_BYTE0, 0x00);

    // Frame Control (set font start address)
    g_usFontSelectStart = ucHeight + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(ucWidth * ucHeight);
    ScalerOsdSramBaseAddressSet(_OSD_A, 0, g_usFontSelectStart, g_usFontTableStart);

    // Character Command initial
    {
        ucTmp = 0x4C;  // 12 Pixel
    }

    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, ucTmp, 0, ucColor, (WORD)ucWidth * ucHeight);

    g_ucOsdWidth = ucWidth; // for calculation (unit: word count)
    g_ucOsdHeight = ucHeight;

    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
   // ScalerOsdDoubleFunction(GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());

}

void BeaconFactoryFuncDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd,BYTE *pStyle)
{
    BYTE cnt0 = 0;
    BYTE cnt1 = 0;

    SET_OSD_WINDOW_NUMBER(*pStyle);
    SET_OSD_WINDOW_COLOR(*(pStyle+5));
    SET_OSD_WINDOW_COLOR(GET_OSD_WINDOW_COLOR()&0x1F);

    SET_OSD_WINDOW_BLEND_ENABLE(_ENABLE);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerOsdDrawWindow((usXStart<10)?usXStart :(usXStart-10), usYStart, usXEnd-10, usYEnd);
}

//--------------------------------------------------
// Description	: 
// Input Value	: None
// Output Value : None
//--------------------------------------------------
void BeaconFactoryFuncSetColorPalette(BYTE *pAddress)
{
    BYTE ucAddr = 0;
    BYTE ucI = 0;

    for(ucI = 0; ucI < 16; ucI++)
    {
        ScalerOsdSetColorPalette(ucAddr + ucI, *(pAddress + (ucI * 3)), *(pAddress + (ucI * 3) + 1), *(pAddress + (ucI * 3) + 2));
    }

}

void BeaconFactoryFuncBurnInPattern(void)
{
    BYTE code tPatternBurnIn[3][5] = 
    {
        {255, 0, 255, 0, 0},
        {255, 0, 0, 255, 0},
        {255, 0, 0, 0, 255},
    };
    static BYTE g_ucColorTempBurnin = 0;

    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

    UserInterfaceKeyPadLedControl(_LED_POWER_SEARCH); // for led control in burn in

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    ScalerDDomainBackgroundSetColor(tPatternBurnIn[0][g_ucColorTempBurnin%0x05], tPatternBurnIn[1][g_ucColorTempBurnin%0x05], tPatternBurnIn[2][g_ucColorTempBurnin%0x05]);
    g_ucColorTempBurnin++;
    ScalerTimerActiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_BURN_IN);

}

void BeaconFactoryOsdPage1(void)
{

    ScalerOsdDisableOsd();
    
    g_ucBeaconFacOsdShowFlag = _ON;

    g_ucBeaconFacOsdState = _BEACON_FAC_OSD_NONE + 1;

    BeaconFactoryFuncApplyMapSetting(_OSD_FACTORY_ROW_SIZE,_OSD_FACTORY_COL_SIZE+6,18,0x80);

    //Adjust Color Palette
    BeaconFactoryFuncSetColorPalette(tPALETTE_FAC0);//_PALETTE_INDEX0

    //Load font
    ScalerOsdHardwareVLC(tFONT_FACTORY, VLC_TABLE_SIZE(tFONT_FACTORY), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);

    // Character Command initial
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4C, _SPACE, ((3 << 4) | _CP_BLACK), (WORD)((_OSD_FACTORY_COL_SIZE+6) * _OSD_FACTORY_ROW_SIZE));

    //Draw Window
    BeaconFactoryFuncDrawWindow(XSTART(8), YSTART(0), XEND(_OSD_FACTORY_COL_SIZE * 12-3), YEND(_OSD_FACTORY_ROW_SIZE *18), tOSD_WINDOW_0_FACTORY_MEMU);
    BeaconFactoryFuncDrawWindow(XSTART(8), YSTART(18), XEND(_OSD_FACTORY_COL_SIZE * 12-3), YEND((_OSD_FACTORY_ROW_SIZE-1) *18), tOSD_WINDOW_0_FACTORY_MEMU_1);

    //draw Menu content
    BeaconFactoryFuncLoadText(ROW(1), COL(1), 0 , tOSD_FACTORY_TEXT_STR);
  
    //draw color
    //FAC_DVI_AUTOCOLOR_GRAY_COLOR_20151223 start
    if((g_ucBeaconFacOsdState == _BEACON_FAC_OSD_AUTO_COLOR)&&(SysSourceGetSourceType() != _SOURCE_VGA))
    {
        g_ucBeaconFacOsdState = _BEACON_FAC_OSD_GAMMA;
        BeaconFactoryFuncHLine(_BEACON_FAC_OSD_AUTO_COLOR, 1, 13, (4 << 4 )|(_CP_BLACK), _WRITE_BYTE2);//180,180,180
    }
    //FAC_DVI_AUTOCOLOR_GRAY_COLOR_20151223 end

    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);

    //draw parameter number
#if 1//(_GAMMA_SELECT_TYPE == 0)
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_GAMMA), COL(_OSD_PARAMETER_COL),GET_FACTORY_GAMMA(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#else
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_GAMMA), COL(_OSD_PARAMETER_COL),GET_FACTORY_GAMMA()+8, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    if(GET_FACTORY_GAMMA() == _GAMMA_1)
    {
        BeaconFactoryFuncHLine(ROW(_BEACON_FAC_OSD_GAMMA), COL(_OSD_PARAMETER_COL-2),1,_1, _WRITE_BYTE1);
    }
    else
    {
        BeaconFuncHLine(ROW(_BEACON_FAC_OSD_GAMMA), COL(_OSD_PARAMETER_COL-2),1,_2, _WRITE_BYTE1);
    }
    BeaconFuncHLine(ROW(_BEACON_FAC_OSD_GAMMA), COL(_OSD_PARAMETER_COL-1),1,_DOT, _WRITE_BYTE1);

#endif

#if(_CUSTOMER == _CUS_TOSHIBA)
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_CT_TYPE), COL(_OSD_PARAMETER_COL-9) ,0, tOSD_BEACON_FAC_COLORTEMP[GET_FACTORY_COLORTEMP()]);
#else
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_CT_TYPE), COL(_OSD_PARAMETER_COL-5) ,0, tOSD_BEACON_FAC_COLORTEMP[GET_FACTORY_COLORTEMP()]);
#endif
    RTDNVRamLoadColorSetting(GET_FACTORY_COLORTEMP());
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_CT_R), COL(_OSD_PARAMETER_COL),(g_stColorProcData.usColorTempR >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_CT_G), COL(_OSD_PARAMETER_COL),(g_stColorProcData.usColorTempG >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_CT_B), COL(_OSD_PARAMETER_COL),(g_stColorProcData.usColorTempB >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_DBRIGHTNESS), COL(_OSD_PARAMETER_COL),GET_FACTORY_DBRIGHTNESS(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_CONTRAST), COL(_OSD_PARAMETER_COL),GET_FACTORY_CONTRAST(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BACKLIGHT), COL(_OSD_PARAMETER_COL),GET_FACTORY_BACKLIGHT(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MAX), COL(_OSD_PARAMETER_COL),GET_FACTORY_BACKLIGHT_REG_MAX(GET_FACTORY_COLORTEMP()), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MID), COL(_OSD_PARAMETER_COL),GET_FACTORY_BACKLIGHT_REG_MID(GET_FACTORY_COLORTEMP()), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MIN), COL(_OSD_PARAMETER_COL),GET_FACTORY_BACKLIGHT_REG_MIN(GET_FACTORY_COLORTEMP()), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#else
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MAX), COL(_OSD_PARAMETER_COL),GET_FACTORY_BACKLIGHT_REG_MAX(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MID), COL(_OSD_PARAMETER_COL),GET_FACTORY_BACKLIGHT_REG_MID(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MIN), COL(_OSD_PARAMETER_COL),GET_FACTORY_BACKLIGHT_REG_MIN(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#endif
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_BURN), COL(_OSD_PARAMETER_COL-2) ,0, tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_BURN()]);
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_SOURCE_DET_TYPE), COL(_OSD_PARAMETER_COL-2) ,0, tOSD_BEACON_FAC_YES_OR_NO[UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE)]);


    BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_OSD_EXIT+3), COL(4),_MONITOR_SN_LENGTH,ucMonitorSn);

    BeaconFactoryFuncPrintASCII(ROW(0), COL(5),7,"Factory");
    BeaconFactoryFuncPrintASCII(ROW(0), COL(15),sizeof(tVersion_Str),tVersion_Str); //V1.01.00
    BeaconFactoryFuncHLine(ROW(0), COL(15+sizeof(tVersion_Str)-4), 3, _SPACE, _WRITE_BYTE1); //clear .00

#if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))
    BeaconFactoryFuncHLine(_BEACON_FAC_OSD_BACKLIGHT, 1, 24, (4 << 4 )|(_CP_BLACK), _WRITE_BYTE2);//180,180,180
#endif

    //Set OSD Position Right down
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    //OSD enable
    ScalerOsdEnableOsd();
    SET_COLOR_TEMP_TYPE(GET_FACTORY_COLORTEMP());
    SET_OSD_BRIGHTNESS(GET_FACTORY_DBRIGHTNESS());
    SET_OSD_CONTRAST(GET_FACTORY_CONTRAST());
    SET_OSD_BACKLIGHT(GET_FACTORY_BACKLIGHT());
    SET_OSD_GAMMA(GET_FACTORY_GAMMA());

    // Adjust Backlight
    UserAdjustBacklight(GET_FACTORY_BACKLIGHT());
    // Adjust Brightness & Contrast
    //RTDNVRamLoadBriCon(_SOURCE_VGA);
#if(_BACKLIGHT_SENSOR == _ON)
    UserAdjustSetSensorbacklightvalue(1); 
#endif

    UserAdjustBrightness(GET_FACTORY_DBRIGHTNESS());
    RTDNVRamLoadColorSetting(GET_FACTORY_COLORTEMP());//load CT rgb
    UserAdjustContrast(GET_FACTORY_CONTRAST());
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
    CAdjustGammaTmp(GET_FACTORY_GAMMA(),GET_FACTORY_COLORTEMP());
#endif

}

void BeaconFactoryOsdPage2(void)
{
    g_ucBeaconFacOsdState = _BEACON_FAC_PAGE2_START + 1;

    BeaconFactoryFuncApplyMapSetting(_OSD_FACTORY_ROW_SIZE,_OSD_FACTORY_COL_SIZE+6,18,0x80);

    //Adjust Color Palette
    BeaconFactoryFuncSetColorPalette(tPALETTE_FAC0);//_PALETTE_INDEX0

    //Load font
    ScalerOsdHardwareVLC(tFONT_FACTORY, VLC_TABLE_SIZE(tFONT_FACTORY), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);

    // Character Command initial
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4C, _SPACE, ((3 << 4) | _CP_BLACK), (WORD)((_OSD_FACTORY_COL_SIZE+6) * _OSD_FACTORY_ROW_SIZE));

    //Draw Window
    BeaconFactoryFuncDrawWindow(XSTART(8), YSTART(0), XEND(_OSD_FACTORY_COL_SIZE * 12-3), YEND(_OSD_FACTORY_ROW_SIZE *18), tOSD_WINDOW_0_FACTORY_MEMU);
    BeaconFactoryFuncDrawWindow(XSTART(8), YSTART(18), XEND(_OSD_FACTORY_COL_SIZE * 12-3), YEND((_OSD_FACTORY_ROW_SIZE-1) *18), tOSD_WINDOW_0_FACTORY_MEMU_1);

    //draw Menu content
    BeaconFactoryFuncLoadText(ROW(1), COL(1), 1 , tOSD_FACTORY_TEXT_STR);
  
    //draw parameter number
    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_SHARPNESS-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),GET_OSD_SHARPNESS(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_SATURATION-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),GET_OSD_SATURATION(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_UART_ENABLE-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2) ,0, tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_TEST_PIN_FUNC()]);
#endif
    SET_FAC_ADJUST_HSTART(GET_MDOMAIN_OUTPUT_HSTART());
    SET_FAC_ADJUST_VSTART(GET_MDOMAIN_OUTPUT_VSTART());
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_TEST1-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),GET_FAC_ADJUST_HSTART(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_TEST2-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),GET_FAC_ADJUST_VSTART(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_TEST5-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),UserCommonNVRamGetSystemData(_SSC), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_FMDVI-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),GET_FACTORY_FMDIV(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_TEST6-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2) ,0, tOSD_BEACON_FAC_YES_OR_NO[(GET_FACTORY_EDID_PROTECT()== _EEPROM_WP_ENABLE)? 1:0 ]);
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_TEST7-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-3), 0 , tOSD_BEACON_FAC_DDCCI_CHANNEL[GET_FACTORY_DDCCI_CHANNEL()]);

#if(_SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_LOAD_GAMMA_FROM_EEPROM-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2), 0 , tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_LOAD_GAMMA_FROM_EEPROM()]);
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_SAVE_GAMMA_TO_EEPROM-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2), 0 , tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_SAVE_GAMMA_TO_EEPROM()]);

#endif
#if(_ALS_TYPE != _SENSER_NONE)
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_ALS-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2), 0 , tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_ALS()]);
#endif


    /*Panel: G170EG01_V1
    Version: V1.00T00V1.01
    Model: CL1717D
    Scaler: RTD2674S
    Dec 12	2015  08:12:24
    Used Time: xxxHour	xxMinute*/

#if(_KAILI_FAC_LANGUAGE == _ON)
    BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_PAGE2_SELECT_END+1-_BEACON_FAC_PAGE2_START), COL(9),sizeof(tVersion_Str),tVersion_Str);
    BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_PAGE2_SELECT_END+2-_BEACON_FAC_PAGE2_START), COL(7),sizeof(tModel_Str),tModel_Str);
    BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_PAGE2_SELECT_END+3-_BEACON_FAC_PAGE2_START), COL(7),sizeof(tPanel_Str),tPanel_Str);
    BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_PAGE2_SELECT_END+4-_BEACON_FAC_PAGE2_START), COL(8),sizeof(tScaler_Str),tScaler_Str);
    BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_PAGE2_SELECT_END+5-_BEACON_FAC_PAGE2_START), COL(6),sizeof(__DATE__),__DATE__);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE2_SELECT_END+6-_BEACON_FAC_PAGE2_START), COL(5),_SVN_VERSION, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_ON | _SHOW_6));    
#else
    BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_PAGE2_SELECT_END+1-_BEACON_FAC_PAGE2_START), COL(5),sizeof(tVersion_Str),tVersion_Str);
    BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_PAGE2_SELECT_END+2-_BEACON_FAC_PAGE2_START), COL(5),sizeof(tModel_Str),tModel_Str);
    BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_PAGE2_SELECT_END+3-_BEACON_FAC_PAGE2_START), COL(5),sizeof(tPanel_Str),tPanel_Str);
    BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_PAGE2_SELECT_END+4-_BEACON_FAC_PAGE2_START), COL(5),sizeof(tScaler_Str),tScaler_Str);
    BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_PAGE2_SELECT_END+5-_BEACON_FAC_PAGE2_START), COL(5),sizeof(__DATE__),__DATE__);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE2_SELECT_END+6-_BEACON_FAC_PAGE2_START), COL(5),_SVN_VERSION, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_ON | _SHOW_6));    
#endif

    //Set OSD Position Right down
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    //OSD enable
    ScalerOsdEnableOsd();

}

void BeaconFactoryOsdPage3(void)
{
    g_ucBeaconFacOsdState = _BEACON_FAC_PAGE3_START + 1;

    BeaconFactoryFuncApplyMapSetting(_OSD_FACTORY_ROW_SIZE,_OSD_FACTORY_COL_SIZE+6,18,0x80);

    //Adjust Color Palette
    BeaconFactoryFuncSetColorPalette(tPALETTE_FAC0);//_PALETTE_INDEX0

    //Load font
    ScalerOsdHardwareVLC(tFONT_FACTORY, VLC_TABLE_SIZE(tFONT_FACTORY), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);

    // Character Command initial
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4C, _SPACE, ((3 << 4) | _CP_BLACK), (WORD)((_OSD_FACTORY_COL_SIZE+6) * _OSD_FACTORY_ROW_SIZE));

    //Draw Window
    BeaconFactoryFuncDrawWindow(XSTART(8), YSTART(0), XEND(_OSD_FACTORY_COL_SIZE * 12-3), YEND(_OSD_FACTORY_ROW_SIZE *18), tOSD_WINDOW_0_FACTORY_MEMU);
    BeaconFactoryFuncDrawWindow(XSTART(8), YSTART(18), XEND(_OSD_FACTORY_COL_SIZE * 12-3), YEND((_OSD_FACTORY_ROW_SIZE-1) *18), tOSD_WINDOW_0_FACTORY_MEMU_1);

    //draw Menu content
    BeaconFactoryFuncLoadText(ROW(1), COL(1), 2 , tOSD_FACTORY_TEXT_STR);
  
    //draw parameter number
    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);
#if (_SIX_COLOR_SUPPORT == _ON)
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM1-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationR, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM2-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationY, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM3-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationG, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM4-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationC, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM5-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationB, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM6-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationM, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM7-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),50, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM8-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),50, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM9-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorHueG, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM10-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorHueC, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM11-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorHueB, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM12-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorHueM, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#else
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM1-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),(ScalerGetBit(0x0067, _BIT6) == _BIT6) ? 0 : 1, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM2-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),GET_D_CLK_FREQ(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM3-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),_PWM_FREQ, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM4-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),(ScalerGetByte(0xFE19) == 0x00) ? 0 : 1, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM5-_BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),0, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6));
#endif

    //Set OSD Position Right down
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    //OSD enable
    ScalerOsdEnableOsd();

}

void BeaconFactorySaveData(void)
{
//	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
    UserCommonFlashSaveItem(_FLASH_ITEMID_FACTORY_DATA, (BYTE *)(&g_stBeaconFacData), sizeof(StructBeaconFacType));

}
void BeaconFactoryLoadData(void)
{
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_FACTORY_DATA, pData, sizeof(StructBeaconFacType)) == _TRUE)
    {
        memcpy(&g_stBeaconFacData, pData, sizeof(StructBeaconFacType));
    }
    else
    {
        g_stBeaconFacData = g_stBeaconFacDataDefault;
    }
}
void BeaconFactoryRestoreData(void)
{
    g_stBeaconFacData = g_stBeaconFacDataDefault;
    
    if(UserCommonFlashLoadItem(_FLASH_ITEMID_FACTORY_DATA, pData, 1) == _TRUE)
    {
        BeaconFactorySaveData();
    }
}

void BeaconFactorySaveMonitorSN(BYTE* pucData)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = _MONITOR_SN_LENGTH;//sizeof(StructOsdUserDataType);

    for(ucItemOffset = 0; ucItemOffset < ((_MONITOR_SN_LENGTH + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++)
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_FACTORY_SN1 - _FLASH_ITEMID_FACTORY_SN0 + 1))
        {
            break;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_FACTORY_SN0 + ucItemOffset), (pucData + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), _DATA_ITEM_LENGTH - 2);    
            ucStructLen -= (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            UserCommonFlashSaveItem((_FLASH_ITEMID_FACTORY_SN0 + ucItemOffset), (pucData + ucItemOffset * (_DATA_ITEM_LENGTH - 2)), ucStructLen);
            break;
        }
    }
}

void BeaconFactoryLoadMonitorSN(BYTE* pucData)
{
    BYTE ucItemOffset = 0;
    BYTE ucStructLen = _MONITOR_SN_LENGTH;//sizeof(StructOsdUserDataType);
        
    for(ucItemOffset = 0; ucItemOffset < ((_MONITOR_SN_LENGTH + (_DATA_ITEM_LENGTH - 2) - 1) / (_DATA_ITEM_LENGTH - 2)); ucItemOffset++) 
    {
        // Here we check the total item number, it could not be smaller than the osd structure
        if(ucItemOffset > (_FLASH_ITEMID_FACTORY_SN1 - _FLASH_ITEMID_FACTORY_SN0 + 1))
        {
            break;
        }

        if(UserCommonFlashLoadItem((_FLASH_ITEMID_FACTORY_SN0 + ucItemOffset), pData, _DATA_ITEM_LENGTH - 2) == _FALSE)
        {
            memset(pucData,0,_MONITOR_SN_LENGTH);// = g_stOSDDefaultData;
            return;
        }

        if(ucStructLen > (_DATA_ITEM_LENGTH - 2))
        {
            memcpy((pucData + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, (_DATA_ITEM_LENGTH - 2));
            ucStructLen = ucStructLen - (_DATA_ITEM_LENGTH - 2);
        }
        else
        {
            memcpy((pucData + (ucItemOffset * (_DATA_ITEM_LENGTH - 2))), pData, ucStructLen);
            break;
        }
    }

}

#if(_USER_SHOW_DEBUG_OSD == _ON)
#warning "_USER_SHOW_DEBUG_OSD is _ON!!"
BYTE xdata g_ucDebugValue[40]= {0};
BYTE *BeaconDebugShowHex(BYTE ucDataArray)//ucDataArray :00 ~255
{
    BYTE xdata tsOSD_HEX[] = {_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_A,_B,_C,_D,_E,_F};

    //BYTE xdata pData[3] = {0};????????

    pData[0] = tsOSD_HEX[ucDataArray / 16];
    pData[1] = tsOSD_HEX[ucDataArray % 16];

    pData[2] = _END_;

    return pData;
}

void BeaconDebugOsdInitial(void)
{
    BeaconFactoryFuncApplyMapSetting(15,_OSD_FACTORY_COL_SIZE,18,0x80);

    //Adjust Color Palette
    BeaconFactoryFuncSetColorPalette(tPALETTE_FAC0);//_PALETTE_INDEX0

    //Load font
    ScalerOsdHardwareVLC(tFONT_FACTORY, VLC_TABLE_SIZE(tFONT_FACTORY), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);

    // Character Command initial
    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4C, _SPACE, ((3 << 4) | _CP_BLACK), (WORD)(_OSD_FACTORY_COL_SIZE * 15));//DFM rev02 patch note 4

    //Draw Window
    BeaconFactoryFuncDrawWindow(XSTART(0), YSTART(0), XEND(_OSD_FACTORY_COL_SIZE * 12), YEND(15 *18), tOSD_WINDOW_0_FACTORY_MEMU);//DFM rev02 patch note 4

    //Set OSD Position Right down
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 0, 0);

    //OSD enable
    ScalerOsdEnableOsd();

}

#endif

#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
//--------------------------------------------------
// Description  : Send DDC Data
// Input Value  : pWriteArray --> Data to be sent
//                usTimeOutCnt --> Timeout
// Output Value : None
//--------------------------------------------------
void BeaconFactoryDdcciSendData(BYTE *pucWriteArray, BYTE Length)
{
    WORD usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
    BYTE ucDdcciCount = 0;

    // Enable mcu write
    MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucDdcciCount < Length)
    {
        MCU_FF26_IIC_DATA_OUT = pucWriteArray[ucDdcciCount++];
    }

    // Disable mcu write
    MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
}

void BeaconFactoryDdcciCommand(void)
{
    if(GET_BACKLIGHT_COM())
    {
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
        // CEepromSaveSystemData();
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
#if(_BACKLIGHT_SENSOR == _ON)
        UserAdjustSetSensorbacklightvalue(1);
#endif
        CLR_BACKLIGHT_COM();
        SET_COMMAND_STATE();

    }
    // modify yh_wang 13.12.27 start{
    if(GET_SCREENSAVE_COM())
    {
        if(GET_OSD_BACKLIGHT()!=0)
        {
            //stOsdUserData.Powersaving_Bright=GET_OSD_BACKLIGHT();
            GET_OSD_BACKLIGHT()=0;
            //SET_ScreenPowerSaving();
            CLR_SCREENSAVERS_FLAG();
        }

        UserAdjustBacklight(GET_OSD_BACKLIGHT());
        //CEepromSaveSystemData();
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
        CLR_SCREENSAVE_COM();
        SET_COMMAND_STATE(); 

    }

    if(GET_SCREENSAVE_OFF_COM())
    {
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
        //CEepromSaveSystemData();
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
        CLR_SCREENSAVE_OFF_COM();
        SET_COMMAND_STATE(); 
    }


    if(GET_CONTRAST_COM())
    {
        UserAdjustContrast(GET_OSD_CONTRAST());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
        CLR_CONTRAST_COM();
        SET_COMMAND_STATE();
    }

    if(GET_BRIGHTNESS_COM())
    {
        UserAdjustBrightness(GET_OSD_BRIGHTNESS());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
        CLR_BRIGHTNESS_COM();
        SET_COMMAND_STATE();
    }

    if(GET_DEFAULT_COM())
    {
        UserAdjustBrightness(GET_OSD_BRIGHTNESS());
        UserAdjustContrast(GET_OSD_CONTRAST());
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
#if(_BACKLIGHT_SENSOR == _ON)
        UserAdjustSetSensorbacklightvalue(1);
#endif
        CLR_BRIGHTNESS_COM();
        SET_COMMAND_STATE();
    }

    if(GET_GAMMA_COM())
    {
        CLR_GAMMA_COM();
        CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
        //CEepromSaveOsdUserData();
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
        SET_COMMAND_STATE();
    }

    if(GET_GAMMA_COM_FORGAMMA_ADJ())
    {

        CLR_GAMMA_COM_FORGAMMA_ADJ();
        CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
        //CEepromSaveOsdUserData();
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
        SET_COMMAND_STATE();
    }

    if(GET_COLORTEMP_COM())
    {
        CLR_COLORTEMP_COM();
        //COsdDispColorTempSelect();	
        RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
        UserAdjustContrast(GET_OSD_CONTRAST());
        CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());      
        //CEepromSaveOsdUserData();
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
        SET_COMMAND_STATE();
    }

    if(GET_BRIGHTPION())
    {
#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
        if(GET_OLED_BACKLIGHT_MIN_STATE())
        {
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE()));
#else
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MIN());
#endif
            CLR_OLED_BACKLIGHT_MIN_STATE();
            SET_CHECK_STATE();
        }

        if(GET_OLED_BACKLIGHT_MID_STATE())
        {
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE()));
#else
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MID());
#endif
            CLR_OLED_BACKLIGHT_MID_STATE();
            SET_CHECK_STATE();
        }

        if(GET_OLED_BACKLIGHT_MAX_STATE())
        {
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE()));
#else
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MAX());
#endif
            CLR_OLED_BACKLIGHT_MAX_STATE();
            SET_CHECK_STATE();
        }        
#endif
  
#if(_BACKLIGHT_SENSOR == _ON)
        SET_IIC_SENSOR_BACKLIGHT_STOP_STATE();
        ScalerTimerReactiveTimerEvent(3000, _USER_TIMER_EVENT_BACKLIGHTSENSOR_STOP);
        if(GET_IIC_SENSOR_BACKLIGHT_MID_STATE())
        {
             ScalerTimerDelayXms(800);
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            if(GET_FACTORY_BACKLIGHT()   == _DEFAULT_BACKLIGHT)
            {            
#if(_CUSTOMER == _CUS_TOSHIBA)
                g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)] = read2561();
                g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)];
#else
                g_stOtherUserData.Sensor_brightness_default = read2561();
                g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default;
#endif
                g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())*4;
            //  BeaconFactorySaveData();
            }
            else
            {
                g_stOtherUserData.Sensor_brightness_value = read2561();
                g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())*4;
            }
#else
            if(GET_FACTORY_BACKLIGHT()   == _DEFAULT_BACKLIGHT)
            {
#if(_CUSTOMER == _CUS_TOSHIBA)
                g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)] = read2561();
                g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)];
#else
                g_stOtherUserData.Sensor_brightness_default = read2561();
                g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default;
#endif
                g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID()*4;
                BeaconFactorySaveData();
            }
            else
            {
                g_stOtherUserData.Sensor_brightness_value = read2561();
                g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID()*4;
            }
#endif
            CLR_IIC_SENSOR_BACKLIGHT_MID_STATE();
            ScalerTimerReactiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_SAVE_OTHER_USER_DATA);
        }
        
#elif(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
        SET_IIC_SENSOR_BACKLIGHT_STOP_STATE();
        ScalerTimerReactiveTimerEvent(3000, _USER_TIMER_EVENT_BACKLIGHTSENSOR_STOP);
        if(GET_IIC_SENSOR_BACKLIGHT_MID_STATE())
        {
            ScalerTimerReactiveTimerEvent(600, _USER_TIMER_EVENT_UPDATE_TARGET_SENSOR);
            ClearDiffValueBySetMidPwm();
        }
#endif

#if((_KL_SPECIAL_FUNTION == _ON) && (BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank))
        ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_KL_SPECIAL_FUNTION_SETTING);
#endif
        //CEepromSaveOsdUserData();
        //SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
        BeaconFactorySaveData();
        CLR_BRIGHTPION();
        SET_COMMAND_STATE();
    }
    if(GET_AutoAdjust())
    {
        CLR_AutoAdjust();
        CLR_AUTO_COMPLETE();
        BeaconMenuAutoAdjust();
        SET_AUTO_COMPLETE() ;
    }

    if(GET_AutoColor())
    {
        CLR_AutoColor() ;    
        CLR_AUTO_COMPLETE();
#if(_VGA_SUPPORT == _ON)
        if(SysSourceGetSourceType() == _SOURCE_VGA)
        {
            // Perform auto-color for RGB
            if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_RGB) == _AUTO_SUCCESS)
            {
                ScalerAutoGetAutoColorResult(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
                // Calculate YPbPr gain/offset using formula
                g_stAdcData = ScalerAutoBalanceYPbPrFromFormula(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);

                // Restore RGB gain/offset
                ScalerAutoGetAutoColorResult(&g_stAdcData);
#endif
            }
            else
            {
                UserCommonNVRamRestoreADCSetting();
            }
        }
        BeaconMenuItemSelColor(GET_OSD_STATE());
#endif // End of #if(_VGA_SUPPORT == _ON)

        SET_AUTO_COMPLETE();

    }

    if(GET_GAMMA_ZERO())
    {
        if(GET_CALIBRATION_STRAT())
        {
            BYTE t[3];
            t[0]=(BYTE)(stGammaRGBdata.tR>>2);
            t[1]=(BYTE)(stGammaRGBdata.tG>>2);
            t[2]=(BYTE)(stGammaRGBdata.tB>>2);
            //CAdjustBackgroundColor(t[0], t[1], t[2]);
            //CScalerSetBit(_VDISP_CTRL_28,0xdf,0x20);
            ScalerDDomainBackgroundSetColor(t[0], t[1], t[2]);
            ScalerDDomainBackgroundEnable(_ENABLE);
        }
        else
        {
            CAdjustGammaZero();
        }
        CLR_GAMMA_ZERO();
        SET_COMMAND_STATE();
    }

    if(GET_SEND_SENSOR_DATA())
    {
#if(_BACKLIGHT_SENSOR == _ENABLE) 
        g_pucDdcciTxBuf[0] = 0x00;          //Temperature
        g_pucDdcciTxBuf[1] = (BYTE)(Value2561>>8);           //backlightsensor high byte
        g_pucDdcciTxBuf[2] = (BYTE)(Value2561&0xFF);          //backlightsensor low byte
        g_pucDdcciTxBuf[3] = (BYTE)(GET_TARGET_SENSOR()>>8);          //Target value high byte
        g_pucDdcciTxBuf[4] = (BYTE)(GET_TARGET_SENSOR()&0xFF);          //Target value low byte   
#elif(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON) 
        g_pucDdcciTxBuf[0] = 0x00;          //Temperature      
        if(GET_BACKLIGHTSENSOR_ONOFF() == _OFF)
        {
            g_pucDdcciTxBuf[1] = 0xFF;          //backlightsensor high byte
            g_pucDdcciTxBuf[2] = 0xFF;         //backlightsensor low byte
        }
        else
        {
            g_pucDdcciTxBuf[1] = (BYTE)(GET_CURRENT_SENSOR()>>8);          //backlightsensor high byte
            g_pucDdcciTxBuf[2] = (BYTE)(GET_CURRENT_SENSOR()&0xFF);          //backlightsensor low byte
        }
        g_pucDdcciTxBuf[3] = (BYTE)(GET_TARGET_SENSOR()>>8);          //Target value high byte
        g_pucDdcciTxBuf[4] = (BYTE)(GET_TARGET_SENSOR()&0xFF);          //Target value low byte   
#else
        g_pucDdcciTxBuf[0] = 0x00;          //Temperature
        g_pucDdcciTxBuf[1] = 0x00;          //backlightsensor high byte
        g_pucDdcciTxBuf[2] = 0x00;          //backlightsensor low byte
        g_pucDdcciTxBuf[3] = 0x00;          //Target value high byte
        g_pucDdcciTxBuf[4] = 0x00;          //Target value low byte   
#endif

#if(_BACKLIGHT_PWM_INVERSE == _ON)
        g_pucDdcciTxBuf[5] = (4095 - MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM))>>8;      //PWM high byte
        g_pucDdcciTxBuf[6] = (4095 - MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM))&0xff;    //PWM low byte
#else
        g_pucDdcciTxBuf[5] = MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM)>>8;      //PWM high byte
        g_pucDdcciTxBuf[6] = MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM)&0xff;    //PWM low byte
#endif
        g_pucDdcciTxBuf[7] = IIC_COM_ADDRESS^g_pucDdcciTxBuf[0]^g_pucDdcciTxBuf[1]^g_pucDdcciTxBuf[2]^g_pucDdcciTxBuf[3]^g_pucDdcciTxBuf[4]^g_pucDdcciTxBuf[5]^g_pucDdcciTxBuf[6];
        
        BeaconFactoryDdcciSendData(g_pucDdcciTxBuf, 8);

        CLR_SEND_SENSOR_DATA();
        SET_COMMAND_STATE();
    }


    #if( _SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)

        if(GET_GAMMA_RGB_OF_EEPROM())
        {

            UserInterfaceSaveGammaToEepromOnline(usArray, stGammaRGBdata.tR, stGammaRGBdata.tG, stGammaRGBdata.tB);


            CLoadGammaFromEE(_GAMMA_START_ADDRESS_OF_EEPROM);
            CLR_GAMMA_RGB_OF_EEPROM();
            SET_COMMAND_STATE();
        }

    #endif	

    if(GET_MONITOR_SN_SAVE_COM())
    {
        BeaconFactorySaveMonitorSN(ucMonitorSn);
        CLR_MONITOR_SN_SAVE_COM();
        BeaconFactoryFuncPrintASCII(ROW(_BEACON_FAC_OSD_EXIT+3), COL(4),_MONITOR_SN_LENGTH,ucMonitorSn);
        
#if((_KL_SPECIAL_FUNTION == _ON) && (BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank))
        ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_KL_SPECIAL_FUNTION_SETTING);
#endif
    }

#if(BEACON_GAMMA_TYPE != Gamma_default)

#else
#if(_SAVE_GAMMA_TO_FLASH_ON_LINE == _ON)
    if(GET_SaveGammaOneTime_OK_OF_FLASH())
    {
        UserCommonFlashSaveGamma(g_ucGammaIndex, g_usDataIndex, g_ucDataCount,  g_ucDdcciRxBuf + 4);
        CLR_SaveGammaOneTime_OK_OF_FLASH();
        memset(g_ucDdcciRxBuf, 0, _DDCCI_RXBUF_LENGTH);
    }
#endif 
#endif
    if(GET_IIC_POWER_SWITCH_COM())
    {
        CLR_IIC_POWER_SWITCH_COM();

        if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
        {
            if(GET_IIC_POWER_FLAG()==_ON)
            {
                UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            }
            else
            {
                UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
            }
        }
        else
        {
            SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
        }
    }
}

#endif






//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void BeaconFactoryOsdMenuOperation(void)
{      
    BYTE ucOsdFunctionPoint;

    if((g_ucBeaconFacOsdState >_BEACON_FAC_OSD_NONE) && (g_ucBeaconFacOsdState < _BEACON_FAC_PAGE3_ADJUST_END) && (GET_KEYMESSAGE() < _KEY_AMOUNT))
    {
        if(g_ucBeaconFacOsdState < _BEACON_FAC_OSD_SELECT_END)
        {
            ucOsdFunctionPoint = _BEACON_FAC_OSD_NONE + 1;
        }
        else if(g_ucBeaconFacOsdState < _BEACON_FAC_OSD_ADJUST_END)
        {
            ucOsdFunctionPoint = g_ucBeaconFacOsdState - _FAC_PAGE1_AMOUNT;
        }
        else if(g_ucBeaconFacOsdState < _BEACON_FAC_PAGE2_SELECT_END)
        {
            ucOsdFunctionPoint = _BEACON_FAC_PAGE2_START + 1 - _FAC_PAGE1_AMOUNT;
        }
        else if(g_ucBeaconFacOsdState < _BEACON_FAC_PAGE2_ADJUST_END)
        {
            ucOsdFunctionPoint = g_ucBeaconFacOsdState - _FAC_PAGE1_AMOUNT - _FAC_PAGE2_AMOUNT;
        }
        else if(g_ucBeaconFacOsdState < _BEACON_FAC_PAGE3_SELECT_END)
        {
            ucOsdFunctionPoint = _BEACON_FAC_PAGE3_START + 1  - _FAC_PAGE1_AMOUNT - _FAC_PAGE2_AMOUNT;
        }
        else if(g_ucBeaconFacOsdState < _BEACON_FAC_PAGE3_ADJUST_END)
        {
            ucOsdFunctionPoint = g_ucBeaconFacOsdState - _FAC_PAGE1_AMOUNT - _FAC_PAGE2_AMOUNT - _FAC_PAGE3_AMOUNT;
        }
        DebugMessageOsd("ucOsdFunctionPoint",ucOsdFunctionPoint);

        DebugMessageOsd("_BEACON_FAC_PAGE3_START",_BEACON_FAC_PAGE3_START);
        (*OperationFacOsdTable[ucOsdFunctionPoint][GET_KEYMESSAGE()])();

    }
}

//--------------------------------------------------
// Description  : 
// Input Value  : 
// Output Value : 
//--------------------------------------------------
void BeaconFactoryMenuItemSel(BYTE item,BYTE color)
{
    if((_BEACON_FAC_OSD_NONE<item)&&(item<_BEACON_FAC_OSD_SELECT_END))
    {
        BeaconFactoryFuncHLine(item, 1, 13, (color<< 4 )|(_CP_BLACK), _WRITE_BYTE2);
        BeaconFactoryFuncDrawWindow(XSTART(8), YSTART(18*item), XEND(_OSD_FACTORY_COL_SIZE * 12-3), YEND((item+1) *18+2), tOSD_WINDOW_0_FACTORY_MEMU_2);
    }
    else if((_BEACON_FAC_OSD_SELECT_END<item)&&(item<_BEACON_FAC_OSD_ADJUST_END))
    {
        BeaconFactoryFuncHLine(item - (_FAC_PAGE1_AMOUNT + 1), 1, _OSD_PARAMETER_COL, (color<< 4 )|(_CP_BLACK), _WRITE_BYTE2);
    }
    else if((_BEACON_FAC_PAGE2_START<item)&&(item<_BEACON_FAC_PAGE2_SELECT_END))
    {
        BeaconFactoryFuncHLine(item - _BEACON_FAC_PAGE2_START, 1, 13, (color<< 4 )|(_CP_BLACK), _WRITE_BYTE2);
        BeaconFactoryFuncDrawWindow(XSTART(8), YSTART(18*(item - _BEACON_FAC_PAGE2_START)), XEND(_OSD_FACTORY_COL_SIZE * 12-3), YEND(((item - _BEACON_FAC_PAGE2_START)+1) *18+2), tOSD_WINDOW_0_FACTORY_MEMU_2);
    }
    else if((_BEACON_FAC_PAGE2_SELECT_END<item)&&(item<_BEACON_FAC_PAGE2_ADJUST_END))
    {
        BeaconFactoryFuncHLine(item - _BEACON_FAC_PAGE2_START-(_FAC_PAGE2_AMOUNT + 1), 1, _OSD_PARAMETER_COL, (color<< 4 )|(_CP_BLACK), _WRITE_BYTE2);
    }
    else if((_BEACON_FAC_PAGE3_START<item)&&(item<_BEACON_FAC_PAGE3_SELECT_END))
    {
        BeaconFactoryFuncHLine(item - _BEACON_FAC_PAGE3_START, 1, 13, (color<< 4 )|(_CP_BLACK), _WRITE_BYTE2);
        BeaconFactoryFuncDrawWindow(XSTART(8), YSTART(18*(item - _BEACON_FAC_PAGE3_START)), XEND(_OSD_FACTORY_COL_SIZE * 12-3), YEND(((item - _BEACON_FAC_PAGE3_START)+1) *18+2), tOSD_WINDOW_0_FACTORY_MEMU_2);
    }
    else if((_BEACON_FAC_PAGE3_SELECT_END<item)&&(item<_BEACON_FAC_PAGE3_ADJUST_END))
    {
        BeaconFactoryFuncHLine(item - _BEACON_FAC_PAGE3_START-(_FAC_PAGE3_AMOUNT + 1), 1, _OSD_PARAMETER_COL, (color<< 4 )|(_CP_BLACK), _WRITE_BYTE2);
    }
}

void BeaconFactoryMenuItemPage1(void)
{
    switch(g_ucBeaconFacOsdState)
    {
        case _BEACON_FAC_OSD_BL_MAX:
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE())));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE())));
    #endif
#else
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MAX()));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MAX()));
    #endif
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE()));
#else
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MAX());
#endif
#endif

            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);
            g_ucBeaconFacOsdState = g_ucBeaconFacOsdState + _FAC_PAGE1_AMOUNT + 1;
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);
            break;
        case _BEACON_FAC_OSD_BL_MID:
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
    #endif
#else
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MID()));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID()));
    #endif
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE()));
#else
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MID());
#endif
#endif

            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);//White
            g_ucBeaconFacOsdState = g_ucBeaconFacOsdState + _FAC_PAGE1_AMOUNT + 1;
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);//Red
            break;
        case _BEACON_FAC_OSD_BL_MIN:
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())));
    #endif
#else
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MIN()));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MIN());
    #endif
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE()));
#else
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MIN());
#endif
#endif

            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);
            g_ucBeaconFacOsdState = g_ucBeaconFacOsdState + _FAC_PAGE1_AMOUNT + 1;
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);
            break;
        case _BEACON_FAC_OSD_BACKLIGHT:
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);
            g_ucBeaconFacOsdState = g_ucBeaconFacOsdState + _FAC_PAGE1_AMOUNT + 1;
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);
            break;

        case _BEACON_FAC_OSD_AUTO_COLOR:
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                // Perform auto-color for RGB
                if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_RGB) == _AUTO_SUCCESS)
                {
                    ScalerAutoGetAutoColorResult(&g_stAdcData);
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
                    // Calculate YPbPr gain/offset using formula
                    g_stAdcData = ScalerAutoBalanceYPbPrFromFormula(&g_stAdcData);
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);

                    // Restore RGB gain/offset
                    ScalerAutoGetAutoColorResult(&g_stAdcData);
#endif
                }
                else
                {
                    UserCommonNVRamRestoreADCSetting();
                }
            }
#endif // End of #if(_VGA_SUPPORT == _ON)
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);
            break;

        case _BEACON_FAC_OSD_RESET:
            //RTDNVRamWholeRestore();
            RTDFlashRestoreColorSetting();
            SET_FACTORY_COLORTEMP(_DEFAULT_COLOR_TEMP);
            RTDNVRamLoadColorSetting(GET_FACTORY_COLORTEMP());//load CT rgb
            SET_FACTORY_DBRIGHTNESS(_DEFAULT_BRIGHTNESS);
            SET_FACTORY_CONTRAST(_DEFAULT_CONTRAST);
            SET_FACTORY_BACKLIGHT(_DEFAULT_BACKLIGHT);
            SET_FACTORY_GAMMA(_DEFAULT_GAMMA);

            //UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, _SOURCE_SWITCH_AUTO_IN_GROUP);
            UserCommonFlashRestoreSystemData();
            //g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));
            SysSourceSetScanType(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE)); 

            //UserCommonNVRamSetSystemData(_SSC,_DCLK_SPREAD_RANGE);
            UserCommonNVRamSaveSystemData();
            //SET_FACTORY_FMDIV(_SPEED_33K);
            BeaconFactorySaveData();
            SET_DCLK_SPREAD_RANGE_VALUE(UserCommonNVRamGetSystemData(_SSC));
            SET_DCLK_SPREAD_SPEED_VALUE(GET_FACTORY_FMDIV());
            //Save to user data
            SET_COLOR_TEMP_TYPE(GET_FACTORY_COLORTEMP());
            SET_OSD_BRIGHTNESS(GET_FACTORY_DBRIGHTNESS());
            SET_OSD_CONTRAST(GET_FACTORY_CONTRAST());
            SET_OSD_BACKLIGHT(GET_FACTORY_BACKLIGHT());
            SET_OSD_GAMMA(GET_FACTORY_GAMMA());

            RTDNVRamSaveOSDData();
            RTDNVRamSaveBriCon(_SOURCE_VGA);
            // Adjust Backlight
            UserAdjustBacklight(GET_FACTORY_BACKLIGHT());
            // Adjust Brightness & Contrast
            RTDNVRamLoadBriCon(_SOURCE_VGA);

            UserAdjustBrightness(GET_FACTORY_DBRIGHTNESS());
            UserAdjustContrast(GET_FACTORY_CONTRAST());
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
            CAdjustGammaTmp(GET_FACTORY_GAMMA(),GET_COLOR_TEMP_TYPE());
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
            RTDFlashRestoreSixColorData();
            ScalerColorSixColorAdjust(_SIXCOLOR_R, g_stSixColorData.ucSixColorHueR, g_stSixColorData.ucSixColorSaturationR); 
            ScalerColorSixColorAdjust(_SIXCOLOR_Y, g_stSixColorData.ucSixColorHueY, g_stSixColorData.ucSixColorSaturationY); 
            ScalerColorSixColorAdjust(_SIXCOLOR_G, g_stSixColorData.ucSixColorHueG, g_stSixColorData.ucSixColorSaturationG); 
            ScalerColorSixColorAdjust(_SIXCOLOR_C, g_stSixColorData.ucSixColorHueC, g_stSixColorData.ucSixColorSaturationC); 
            ScalerColorSixColorAdjust(_SIXCOLOR_B, g_stSixColorData.ucSixColorHueB, g_stSixColorData.ucSixColorSaturationB); 
            ScalerColorSixColorAdjust(_SIXCOLOR_M, g_stSixColorData.ucSixColorHueM, g_stSixColorData.ucSixColorSaturationM); 
            ScalerColorSixColorInitial();            
#endif

            g_ucBeaconFacOsdState = _BEACON_FAC_OSD_NONE;
            ScalerOsdDisableOsd();
            g_ucBeaconFacOsdShowFlag = _OFF;

            BeaconFactoryOsdPage1();

            break;

        case _BEACON_FAC_OSD_PAGE2:

            BeaconFactoryOsdPage2();
            break;

        case _BEACON_FAC_OSD_EXIT:

            BeaconFactoryExitItemPage1();
            break;

        default:

            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);//white
            g_ucBeaconFacOsdState = g_ucBeaconFacOsdState + _FAC_PAGE1_AMOUNT + 1;
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);//red
            break;
    }

}

void BeaconFactorySelectNextItemPage1(void)
{    
    BYTE preBeaconFacOsdState;
    preBeaconFacOsdState = g_ucBeaconFacOsdState;
    
    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);//white
    g_ucBeaconFacOsdState = BeaconFactoryFuncValueChange(g_ucBeaconFacOsdState,_BEACON_FAC_OSD_SELECT_END-1,_BEACON_FAC_OSD_NONE+1,_ON);
//FAC_DVI_AUTOCOLOR_GRAY_COLOR_20151223 start
    if((g_ucBeaconFacOsdState == _BEACON_FAC_OSD_AUTO_COLOR)&&(SysSourceGetSourceType() != _SOURCE_VGA))
    {
        g_ucBeaconFacOsdState = BeaconFactoryFuncValueChange(g_ucBeaconFacOsdState,_BEACON_FAC_OSD_SELECT_END-1,_BEACON_FAC_OSD_NONE+1,_ON);
    }
//FAC_DVI_AUTOCOLOR_GRAY_COLOR_20151223 end

#if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))
    if(g_ucBeaconFacOsdState == _BEACON_FAC_OSD_BACKLIGHT)
    {
        g_ucBeaconFacOsdState = BeaconFactoryFuncValueChange(g_ucBeaconFacOsdState,_BEACON_FAC_OSD_SELECT_END-1,_BEACON_FAC_OSD_NONE+1,_ON);
    }
#endif

    switch(g_ucBeaconFacOsdState)
    {
        case _BEACON_FAC_OSD_BL_MAX:
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE())));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE())));
    #endif
#else
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MAX()));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MAX()));
    #endif
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE()));
#else
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MAX());
#endif
#endif

            break;
        case _BEACON_FAC_OSD_BL_MID:
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
    #endif
#else
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MID()));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID()));
    #endif
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE()));
#else
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MID());
#endif
#endif

            break;
        case _BEACON_FAC_OSD_BL_MIN:
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())));
    #endif
#else
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MIN()));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MIN()));
    #endif
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE()));
#else
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MIN());
#endif
#endif

            break;
        default:
            if((preBeaconFacOsdState == _BEACON_FAC_OSD_BL_MAX) || (preBeaconFacOsdState == _BEACON_FAC_OSD_BL_MID) ||\
                (preBeaconFacOsdState == _BEACON_FAC_OSD_BL_MIN))
            {
                UserAdjustBacklight(GET_FACTORY_BACKLIGHT()); 
            }
            break;
    }

    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);//red
}

void BeaconFactoryExitItemPage1(void)
{
    if((g_ucBeaconFacOsdState == _BEACON_FAC_OSD_BL_MAX)||(g_ucBeaconFacOsdState == _BEACON_FAC_OSD_BL_MID) ||(g_ucBeaconFacOsdState == _BEACON_FAC_OSD_BL_MIN))
    {
        UserAdjustBacklight(GET_FACTORY_BACKLIGHT());        
    }

    g_ucBeaconFacOsdState = _BEACON_FAC_OSD_NONE;
    ScalerOsdDisableOsd();
    
#if(_BACKLIGHT_SENSOR == _ON)     
    ScalerTimerDelayXms(500);  
#endif

    g_ucBeaconFacOsdShowFlag = _OFF;

    //Osd_wakeup_20151223 start (for show no signal)
    if((GET_FACTORY_BURN()==_OFF)&&((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)))
    {
#if 0

		ScalerTimerActiveTimerEvent(SEC(0.1), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
#endif
    }
    //Osd_wakeup_20151223 end
}

void BeaconFactoryMenuExitPage1(void) //SAVE
{
    switch(g_ucBeaconFacOsdState - (_FAC_PAGE1_AMOUNT + 1))
    {
        case _BEACON_FAC_OSD_BACKLIGHT:
            //SET_FACTORY_BACKLIGHT_REG_MID(ucBacklightMidTemp);
            SET_FACTORY_BACKLIGHT(GET_OSD_BACKLIGHT());
            // Adjust Backlight
            UserAdjustBacklight(GET_FACTORY_BACKLIGHT());
#if(_BACKLIGHT_SENSOR == _ON)     
            ScalerTimerDelayXms(500);   
#if(_CUSTOMER == _CUS_TOSHIBA)       
            g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)]  = read2561();
            g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)] ;
            DebugMessageSystem("g_stOtherUserData.Sensor_brightness_default ",g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)] );        
#else
            g_stOtherUserData.Sensor_brightness_default = read2561();
            g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default;
            DebugMessageSystem("g_stOtherUserData.Sensor_brightness_default ",g_stOtherUserData.Sensor_brightness_default);        
#endif
            UserAdjustSetSensorbacklightvalue(0); 
#endif            
            break;
        case _BEACON_FAC_OSD_SOURCE_DET_TYPE://FAC_ADD_SOURCE_DET_ON_OFF_20151223 add
            UserCommonNVRamSaveSystemData();
            break;

        case _BEACON_FAC_OSD_BURN:
            //BeaconFactorySaveData();
            if((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
            {
                if(GET_FACTORY_BURN()==_OFF)
                {
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_BURN_IN);
                    //Adjust Color Background
                    ScalerDDomainBackgroundSetColor(0x00, 0x00, 0x00);
                    ScalerDDomainBackgroundEnable(_ENABLE);
                }
                else
                {
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);

                    UserAdjustBacklight(GET_OSD_BACKLIGHT());

                    ScalerTimerActiveTimerEvent(SEC(0.1), _USER_TIMER_EVENT_BURN_IN);
                }
            }
            break;

#if(_BACKLIGHT_SENSOR == _ON)           
        case _BEACON_FAC_OSD_BL_MID:
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
    #endif
#else
    #if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MID()));
    #else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID()));
    #endif
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE()));
#else
            UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MID());
#endif
#endif

            ScalerTimerDelayXms(1000);   
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            if(GET_FACTORY_BACKLIGHT()  == _DEFAULT_BACKLIGHT)
            {
#if(_CUSTOMER == _CUS_TOSHIBA)
                g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)]  = read2561();
                g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)];
#else
                g_stOtherUserData.Sensor_brightness_default = read2561();
                g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default;
#endif
                g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())*4;
            }
            else
            {
                g_stOtherUserData.Sensor_brightness_value = read2561();
                g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())*4;
            }
#else
            if(GET_FACTORY_BACKLIGHT()  == _DEFAULT_BACKLIGHT)
            {
#if(_CUSTOMER == _CUS_TOSHIBA)
                g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)]  = read2561();
                g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)];
#else
                g_stOtherUserData.Sensor_brightness_default = read2561();
                g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default;
#endif
                g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID()*4;
            }
            else
            {
                g_stOtherUserData.Sensor_brightness_value = read2561();
                g_stOtherUserData.Sensor_backlight_value = GET_FACTORY_BACKLIGHT_REG_MID()*4;
            }
            RTDNVRamRestoreOtherUserData();
#endif
            break; 

#elif(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
        case _BEACON_FAC_OSD_BL_MID:
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
#if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
#else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
#endif
#else
#if(_BACKLIGHT_PWM_INVERSE == _ON)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-GET_FACTORY_BACKLIGHT_REG_MID()));
#else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID()));
#endif
#endif

            SET_IIC_SENSOR_BACKLIGHT_MID_STATE();
            ScalerTimerDelayXms(600); 
            updateTargetSenorValue();
            ClearDiffValueBySetMidPwm();
            break;
#endif

        default:
            break;
    }

#if((_KL_SPECIAL_FUNTION == _ON) && (BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank))
    if(((g_ucBeaconFacOsdState - (_FAC_PAGE1_AMOUNT + 1)) == _BEACON_FAC_OSD_BL_MAX) || \
        ((g_ucBeaconFacOsdState - (_FAC_PAGE1_AMOUNT + 1)) == _BEACON_FAC_OSD_BL_MID) || \
        ((g_ucBeaconFacOsdState - (_FAC_PAGE1_AMOUNT + 1)) == _BEACON_FAC_OSD_BL_MIN))
    {
        ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_KL_SPECIAL_FUNTION_SETTING);
    }
#endif
    
    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);
    g_ucBeaconFacOsdState = g_ucBeaconFacOsdState - (_FAC_PAGE1_AMOUNT + 1); 
    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);

    BeaconFactorySaveData();
    //Save to user data
    SET_COLOR_TEMP_TYPE(GET_FACTORY_COLORTEMP());
    SET_OSD_BRIGHTNESS(GET_FACTORY_DBRIGHTNESS());
    SET_OSD_CONTRAST(GET_FACTORY_CONTRAST());
    SET_OSD_BACKLIGHT(GET_FACTORY_BACKLIGHT());
    SET_OSD_GAMMA(GET_FACTORY_GAMMA());

    RTDNVRamSaveOSDData();

    RTDNVRamSaveColorSetting(GET_FACTORY_COLORTEMP());

    RTDNVRamSaveBriCon(_SOURCE_VGA);


    // Adjust Brightness & Contrast
    RTDNVRamLoadBriCon(_SOURCE_VGA);

    UserAdjustBrightness(GET_FACTORY_DBRIGHTNESS());
    UserAdjustContrast(GET_FACTORY_CONTRAST());

}

//----------------------------------------------------------------------------------------------------
// OSD Function Adjust
//----------------------------------------------------------------------------------------------------

void BeaconFactoryGammaAdjust()
{
    SET_FACTORY_GAMMA(BeaconFactoryFuncValueChange(GET_FACTORY_GAMMA(),_GAMMA_AMOUNT,_GAMMA_1,_ON));

#if 1//(_GAMMA_SELECT_TYPE == 0)
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_GAMMA), COL(_OSD_PARAMETER_COL),GET_FACTORY_GAMMA(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#else
		BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_GAMMA), COL(_OSD_PARAMETER_COL),GET_FACTORY_GAMMA()+8, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
	
		if(GET_FACTORY_GAMMA() == _GAMMA_1)
		{
			BeaconFactoryFuncHLine(ROW(_BEACON_FAC_OSD_GAMMA), COL(_OSD_PARAMETER_COL-2),1,_1, _WRITE_BYTE1);
		}
		else
		{
			BeaconFuncHLine(ROW(_BEACON_FAC_OSD_GAMMA), COL(_OSD_PARAMETER_COL-2),1,_2, _WRITE_BYTE1);
		}
		BeaconFuncHLine(ROW(_BEACON_FAC_OSD_GAMMA), COL(_OSD_PARAMETER_COL-1),1,_DOT, _WRITE_BYTE1);
	
#endif

#if(_GAMMA_FUNCTION == _ON)
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
    RTDNVRamLoadColorSetting(GET_FACTORY_COLORTEMP());//load CT rgb
    UserAdjustContrast(GET_FACTORY_CONTRAST());
    CAdjustGammaTmp(GET_FACTORY_GAMMA(),GET_FACTORY_COLORTEMP());
#else
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    ScalerColorOutputGamma(_OFF);
    
    if(GET_FACTORY_GAMMA() != _GAMMA_OFF)
    {
        UserAdjustGamma(GET_FACTORY_GAMMA());

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorOutputGamma(_ON);
    }
#endif
#endif // End of #if(_GAMMA_FUNCTION == _ON)
}

void BeaconFactoryColorTempAdjust()
{
    SET_FACTORY_COLORTEMP(BeaconFactoryFuncValueChange(GET_FACTORY_COLORTEMP(),_CT_COLORTEMP_AMOUNT,0,_ON));

    //BeaconFactoryFuncShowNumber(ROW(g_ucBeaconFacOsdState - (_BEACON_FAC_OSD_SELECT_END-_BEACON_FAC_OSD_NONE)+2), COL(_OSD_PARAMETER_COL),GET_FACTORY_COLORTEMP(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_CUSTOMER == _CUS_TOSHIBA)
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_CT_TYPE), COL(_OSD_PARAMETER_COL-9),0 , tOSD_BEACON_FAC_COLORTEMP[GET_FACTORY_COLORTEMP()]);
#else
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_CT_TYPE), COL(_OSD_PARAMETER_COL-5),0 , tOSD_BEACON_FAC_COLORTEMP[GET_FACTORY_COLORTEMP()]);
#endif
    RTDNVRamLoadColorSetting(GET_FACTORY_COLORTEMP());
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_CT_R), COL(_OSD_PARAMETER_COL),(g_stColorProcData.usColorTempR >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_CT_G), COL(_OSD_PARAMETER_COL),(g_stColorProcData.usColorTempG >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_CT_B), COL(_OSD_PARAMETER_COL),(g_stColorProcData.usColorTempB >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    UserAdjustContrast(GET_FACTORY_CONTRAST());

#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    SET_COLOR_TEMP_TYPE(GET_FACTORY_COLORTEMP());
    RTDNVRamSaveOSDData();

    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MAX), COL(_OSD_PARAMETER_COL),GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE()), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MID), COL(_OSD_PARAMETER_COL),GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE()), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MIN), COL(_OSD_PARAMETER_COL),GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE()), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    UserAdjustBacklight(GET_OSD_BACKLIGHT());
    ScalerTimerDelayXms(1000);  
#if(_BACKLIGHT_SENSOR == _ON)
    g_stOtherUserData.Sensor_brightness_value = read2561();
    RTDNVRamSaveOtherUserData();
#endif
#endif

#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
    CAdjustGammaTmp(GET_FACTORY_GAMMA(),GET_FACTORY_COLORTEMP());
#endif

}
void BeaconFactoryColorTempAdjustR()
{
    BYTE ucColorTemp_R = (BYTE)(g_stColorProcData.usColorTempR >> 4);
    ucColorTemp_R = BeaconFactoryFuncValueChange(ucColorTemp_R,255,0,_OFF);
    g_stColorProcData.usColorTempR = (WORD)ucColorTemp_R << 4;
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_CT_R), COL(_OSD_PARAMETER_COL),ucColorTemp_R, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
    UserAdjustContrast(GET_FACTORY_CONTRAST());
}
void BeaconFactoryColorTempAdjustG()
{
    BYTE ucColorTemp_G = (BYTE)(g_stColorProcData.usColorTempG >> 4);
    ucColorTemp_G = BeaconFactoryFuncValueChange(ucColorTemp_G,255,0,_OFF);
    g_stColorProcData.usColorTempG = (WORD)ucColorTemp_G << 4;
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_CT_G), COL(_OSD_PARAMETER_COL),ucColorTemp_G, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
    UserAdjustContrast(GET_FACTORY_CONTRAST());
}
void BeaconFactoryColorTempAdjustB()
{
    BYTE ucColorTemp_B = (BYTE)(g_stColorProcData.usColorTempB >> 4);
    ucColorTemp_B = BeaconFactoryFuncValueChange(ucColorTemp_B,255,0,_OFF);
    g_stColorProcData.usColorTempB = (WORD)ucColorTemp_B << 4;
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_CT_B), COL(_OSD_PARAMETER_COL),ucColorTemp_B, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
    UserAdjustContrast(GET_FACTORY_CONTRAST());
}

void BeaconFactoryDBrightnessAdjust()
{
    SET_FACTORY_DBRIGHTNESS(BeaconFactoryFuncValueChange(GET_FACTORY_DBRIGHTNESS(),_OSD_BriCon_RANGE,0,_OFF));

    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_DBRIGHTNESS), COL(_OSD_PARAMETER_COL),GET_FACTORY_DBRIGHTNESS(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    UserAdjustBrightness(GET_FACTORY_DBRIGHTNESS());
}

void BeaconFactoryContrastAdjust()
{
    SET_FACTORY_CONTRAST(BeaconFactoryFuncValueChange(GET_FACTORY_CONTRAST(),_OSD_BriCon_RANGE,0,_OFF));

    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_CONTRAST), COL(_OSD_PARAMETER_COL),GET_FACTORY_CONTRAST(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    UserAdjustContrast(GET_FACTORY_CONTRAST());

}


void BeaconFactoryBacklightAdjust()
{
    SET_OSD_BACKLIGHT(BeaconFactoryFuncValueChange(GET_OSD_BACKLIGHT(),_OSD_BriCon_RANGE,0,_OFF));//99,1 UserAdjustBacklight ?D????µ?·???2??ü?a0

    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BACKLIGHT), COL(_OSD_PARAMETER_COL),GET_OSD_BACKLIGHT(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    UserAdjustBacklight(GET_OSD_BACKLIGHT());
/*
//DWORD_issue_20151203 start

    if(GET_FACTORY_BACKLIGHT()>ucBacklightDefaultTemp)
        ucBacklightMidTemp = ((DWORD)(GET_FACTORY_BACKLIGHT()-ucBacklightDefaultTemp)*(GET_FACTORY_BACKLIGHT_REG_MAX()-GET_FACTORY_BACKLIGHT_REG_MID())/(100-ucBacklightDefaultTemp))+GET_FACTORY_BACKLIGHT_REG_MID();
    else
        ucBacklightMidTemp = GET_FACTORY_BACKLIGHT_REG_MID()-((DWORD)(ucBacklightDefaultTemp - GET_FACTORY_BACKLIGHT())*(GET_FACTORY_BACKLIGHT_REG_MID()-GET_FACTORY_BACKLIGHT_REG_MIN())/ucBacklightDefaultTemp);

//DWORD_issue_20151203 end
    BeaconFactoryFuncShowNumber(ROW(6+_BEACON_FAC_OSD_BACKLIGHT), COL(_OSD_PARAMETER_COL),ucBacklightMidTemp, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_BACKLIGHT_PWM_INVERSE == _ON)
    PCB_BACKLIGHT_PWM(255-ucBacklightMidTemp);
#else
    PCB_BACKLIGHT_PWM(ucBacklightMidTemp);
#endif
*/
}

void BeaconFactoryBacklightRegMaxAdjust()
{
    BYTE mBacklightRegValue;
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    SET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE(), BeaconFactoryFuncValueChange(GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE()),255,GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE()),_OFF));
    mBacklightRegValue = GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE());
#else
    SET_FACTORY_BACKLIGHT_REG_MAX(BeaconFactoryFuncValueChange(GET_FACTORY_BACKLIGHT_REG_MAX(),255,GET_FACTORY_BACKLIGHT_REG_MID(),_OFF));
    mBacklightRegValue = GET_FACTORY_BACKLIGHT_REG_MAX();
#endif

    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MAX), COL(_OSD_PARAMETER_COL),mBacklightRegValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_BACKLIGHT_PWM_INVERSE == _ON)
    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-mBacklightRegValue));
#else
    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(mBacklightRegValue));
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
    UserCommonInterfaceOledAdjustBackLight(mBacklightRegValue);
#endif

}

void BeaconFactoryBacklightRegMidAdjust()
{
    BYTE mBacklightRegValue;
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    SET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE(),BeaconFactoryFuncValueChange(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE()),GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE()),GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE()),_OFF));
    mBacklightRegValue = GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE());
#else
    SET_FACTORY_BACKLIGHT_REG_MID(BeaconFactoryFuncValueChange(GET_FACTORY_BACKLIGHT_REG_MID(),GET_FACTORY_BACKLIGHT_REG_MAX(),GET_FACTORY_BACKLIGHT_REG_MIN(),_OFF));
    mBacklightRegValue = GET_FACTORY_BACKLIGHT_REG_MID();
#endif

    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MID), COL(_OSD_PARAMETER_COL),mBacklightRegValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_BACKLIGHT_PWM_INVERSE == _ON)
    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-mBacklightRegValue));
#else
    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(mBacklightRegValue));
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
    UserCommonInterfaceOledAdjustBackLight(mBacklightRegValue);
#endif

}


void BeaconFactoryBacklightRegMinAdjust()
{
    BYTE mBacklightRegValue;
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    SET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE(), BeaconFactoryFuncValueChange(GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE()),GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE()),0,_OFF));
    mBacklightRegValue = GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE());
#else
    SET_FACTORY_BACKLIGHT_REG_MIN(BeaconFactoryFuncValueChange(GET_FACTORY_BACKLIGHT_REG_MIN(),GET_FACTORY_BACKLIGHT_REG_MID(),0,_OFF));
    mBacklightRegValue = GET_FACTORY_BACKLIGHT_REG_MIN();
#endif

    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_BL_MIN), COL(_OSD_PARAMETER_COL),mBacklightRegValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_BACKLIGHT_PWM_INVERSE == _ON)
    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255-mBacklightRegValue));
#else
    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(mBacklightRegValue));
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
    UserCommonInterfaceOledAdjustBackLight(mBacklightRegValue);
#endif

}

void BeaconFactoryBurnAdjust()
{
    SET_FACTORY_BURN(BeaconFactoryFuncValueChange(GET_FACTORY_BURN(),1,0,_ON));
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_BURN), COL(_OSD_PARAMETER_COL-2) ,0, tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_BURN()]);

}
//FAC_ADD_SOURCE_DET_ON_OFF_20151223 start
void BeaconFactorySouceDetTypeAdjust()
{
    if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) == _SOURCE_SWITCH_FIXED_PORT)
    {
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, _SOURCE_SWITCH_AUTO_IN_GROUP);
        //UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
        SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
        UserCommonNVRamSaveSystemData();
    }
    else
    {
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, _SOURCE_SWITCH_FIXED_PORT);
        //UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
        SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
        UserCommonNVRamSaveSystemData();
    }
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_SOURCE_DET_TYPE), COL(_OSD_PARAMETER_COL-2) ,0, tOSD_BEACON_FAC_YES_OR_NO[UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE)]);

}
//FAC_ADD_SOURCE_DET_ON_OFF_20151223 end


//PAGE2
void BeaconFactoryMenuItemPage2(void)
{
    switch(g_ucBeaconFacOsdState)
    {
        case _BEACON_FAC_OSD_PAGE1:
            BeaconFactoryOsdPage1();
            break;
        case _BEACON_FAC_OSD_EXIT2:
            BeaconFactoryExitItemPage2();
            break;
        case _BEACON_FAC_OSD_PAGE3:
            BeaconFactoryOsdPage3();
            break;
        default:
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);
            g_ucBeaconFacOsdState = g_ucBeaconFacOsdState + _FAC_PAGE2_AMOUNT + 1;
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);
            break;
    }
}

void BeaconFactorySelectNextItemPage2(void)
{    
    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);
    g_ucBeaconFacOsdState = BeaconFactoryFuncValueChange(g_ucBeaconFacOsdState,_BEACON_FAC_PAGE2_SELECT_END-1,_BEACON_FAC_PAGE2_START+1,_ON);
    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);
}

void BeaconFactoryExitItemPage2(void)
{
    BeaconFactoryExitItemPage1();
}

void BeaconFactoryMenuExitPage2(void)
{
    switch(g_ucBeaconFacOsdState - (_FAC_PAGE2_AMOUNT + 1))
    {
        case _BEACON_FAC_OSD_TEST1:
        case _BEACON_FAC_OSD_TEST2:
        case _BEACON_FAC_OSD_TEST5:
            UserCommonNVRamSaveSystemData();
            break;
    #if(_SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)
        case _BEACON_FAC_OSD_LOAD_GAMMA_FROM_EEPROM:
            if(GET_FACTORY_LOAD_GAMMA_FROM_EEPROM() == 1)
            {

                if(CLoadGammaFromEE(_GAMMA_START_ADDRESS_OF_EEPROM) == _FAIL)
                {

                    SET_FACTORY_LOAD_GAMMA_FROM_EEPROM(0);
                    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_LOAD_GAMMA_FROM_EEPROM-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2), 0 , tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_LOAD_GAMMA_FROM_EEPROM()]);
                }
            }
            break;

        case _BEACON_FAC_OSD_SAVE_GAMMA_TO_EEPROM:
            if(GET_FACTORY_SAVE_GAMMA_TO_EEPROM() == 1)
            {

                if(CSaveGammaToEE(_GAMMA_START_ADDRESS_OF_EEPROM, GET_OSD_GAMMA()) == _FAIL)
                {

                    SET_FACTORY_SAVE_GAMMA_TO_EEPROM(0);
                    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_SAVE_GAMMA_TO_EEPROM-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2), 0 , tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_SAVE_GAMMA_TO_EEPROM()]);

                }
            }
            break;

    #endif
        default:
            RTDNVRamSaveOSDData();//Sharpness_save_20151125 add
            BeaconFactorySaveData();
            break;
    }

    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);
    g_ucBeaconFacOsdState = g_ucBeaconFacOsdState - (_FAC_PAGE2_AMOUNT + 1); 
    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);

}


void BeaconFactorySharpnessAdjust()
{
    SET_OSD_SHARPNESS(BeaconFactoryFuncValueChange(GET_OSD_SHARPNESS(),_SHARPNESS_MAX,_SHARPNESS_MIN,_OFF));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_SHARPNESS-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),GET_OSD_SHARPNESS(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_SHARPNESS_SUPPORT == _ON)
    UserCommonAdjustSharpness(SysSourceGetInputPort());
#endif

}

void BeaconFactorySaturationAdjust()
{
    SET_OSD_SATURATION(BeaconFactoryFuncValueChange(GET_OSD_SATURATION(),_SATURATION_MAX,_SATURATION_MIN,_OFF));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_SATURATION-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),GET_OSD_SATURATION(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_GLOBAL_HUE_SATURATION == _ON)
    UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
#endif
}

#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
void BeaconFactoryUartEnableAdjust()
{
    SET_FACTORY_TEST_PIN_FUNC(BeaconFactoryFuncValueChange(GET_FACTORY_TEST_PIN_FUNC(),1,0,_ON));
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_UART_ENABLE-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2) ,0, tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_TEST_PIN_FUNC()]);

}
#endif

void BeaconFactoryOutputHstartAdjust()
{
#if 0
#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    ScalerMDomainAspectOriginMode(_TRUE);	
#endif
    SET_FAC_ADJUST_HSTART(BeaconFactoryFuncValueChange(GET_FAC_ADJUST_HSTART(),2*g_ucFactoryHstartMid-_PANEL_DH_START,_PANEL_DH_START,_OFF));				  
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_TEST1- _BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),GET_FAC_ADJUST_HSTART(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#endif    
}

void BeaconFactoryOutputVstartAdjust()
{
#if 0
#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    ScalerMDomainAspectOriginMode(_TRUE);	
#endif
    SET_FAC_ADJUST_VSTART(BeaconFactoryFuncValueChange(GET_FAC_ADJUST_VSTART(),2*g_ucFactoryVstartMid-_PANEL_DV_START,_PANEL_DV_START,_OFF));				  
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_TEST2- _BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),GET_FAC_ADJUST_VSTART(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#endif    
}

void BeaconFactorySSCAdjust()
{
    UserCommonNVRamSetSystemData(_SSC,BeaconFactoryFuncValueChange(UserCommonNVRamGetSystemData(_SSC),15,0,_OFF));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_TEST5- _BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),UserCommonNVRamGetSystemData(_SSC), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    SET_DCLK_SPREAD_RANGE_VALUE(UserCommonNVRamGetSystemData(_SSC));
    //ScalerPLLSetDPLLSSC(GET_FACTORY_FMDIV(), UserCommonNVRamGetSystemData(_SSC));
    ScalerPLLSetDPLLSSC(GET_DCLK_SPREAD_SPEED_VALUE(), GET_DCLK_SPREAD_RANGE_VALUE());
}

void BeaconFactoryFMDIVAdjust()
{
    SET_FACTORY_FMDIV(BeaconFactoryFuncValueChange(GET_FACTORY_FMDIV(),_SPEED_66K,_SPEED_33K,_ON));
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_OSD_FMDVI- _BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL),GET_FACTORY_FMDIV(), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
//0 :_SPEED_33K 1 : _SPEED_66K
    SET_DCLK_SPREAD_SPEED_VALUE(GET_FACTORY_FMDIV());
    //ScalerPLLSetDPLLSSC(GET_FACTORY_FMDIV(), UserCommonNVRamGetSystemData(_SSC));
    ScalerPLLSetDPLLSSC(GET_DCLK_SPREAD_SPEED_VALUE(), GET_DCLK_SPREAD_RANGE_VALUE());
}


void BeaconFactoryEdidWriteAdjust()
{
    if(GET_FACTORY_EDID_PROTECT() == _EEPROM_WP_ENABLE)
    {
        SET_FACTORY_EDID_PROTECT(_EEPROM_WP_DISABLE);
        PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
        PCB_A0_EDID_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);
        BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_TEST6-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2) ,0, tOSD_BEACON_FAC_YES_OR_NO[0]);

    }
    else
    {
        SET_FACTORY_EDID_PROTECT(_EEPROM_WP_ENABLE);
        PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
        PCB_A0_EDID_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
        BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_TEST6-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL -2) ,0, tOSD_BEACON_FAC_YES_OR_NO[1]);

    }
}

void BeaconFactoryDdcciChannelAdjust()
{
    SET_FACTORY_DDCCI_CHANNEL(BeaconFactoryFuncValueChange(GET_FACTORY_DDCCI_CHANNEL(),4,0,_ON));
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_TEST7-_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-3), 0 , tOSD_BEACON_FAC_DDCCI_CHANNEL[GET_FACTORY_DDCCI_CHANNEL()]);

    switch(GET_FACTORY_DDCCI_CHANNEL())
    {
        case 0:
            ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
            break;
    #if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case 1:
            ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), _A0_INPUT_PORT);  
            break;
    #endif

    #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case 2:         
            ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), _D0_INPUT_PORT);
            break;
    #endif

    #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case 3:         
            ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), _D1_INPUT_PORT);
            break;
    #endif

    #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)    
        case 4:
            ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), _D3_INPUT_PORT);
            break;
    #endif

        default:
            ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
            break;
    }

}

#if(_SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)

void BeaconFactoryLoadGammaFromEepromAdjust(void)
{
    SET_FACTORY_LOAD_GAMMA_FROM_EEPROM(BeaconFactoryFuncValueChange(GET_FACTORY_LOAD_GAMMA_FROM_EEPROM(),1,0,_ON));
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_LOAD_GAMMA_FROM_EEPROM -_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2) ,0, tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_LOAD_GAMMA_FROM_EEPROM()]);
}

void BeaconFactorySaveGammaToEepromAdjust(void)
{
    SET_FACTORY_SAVE_GAMMA_TO_EEPROM(BeaconFactoryFuncValueChange(GET_FACTORY_SAVE_GAMMA_TO_EEPROM(),1,0,_ON));
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_SAVE_GAMMA_TO_EEPROM -_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2) ,0, tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_SAVE_GAMMA_TO_EEPROM()]);
}

#endif

#if(_ALS_TYPE != _SENSER_NONE)
bit BeaconFactoryAlsStatus()
{
    return GET_FACTORY_ALS();
}

void BeaconFactoryALSAdjust(void)
{
    SET_FACTORY_ALS(BeaconFactoryFuncValueChange(GET_FACTORY_ALS(),1,0,_ON));
    BeaconFactoryFuncLoadText(ROW(_BEACON_FAC_OSD_ALS -_BEACON_FAC_PAGE2_START), COL(_OSD_PARAMETER_COL-2) ,0, tOSD_BEACON_FAC_YES_OR_NO[GET_FACTORY_ALS()]);
}
#endif

//PAGE3
void BeaconFactoryMenuItemPage3(void)
{
    switch(g_ucBeaconFacOsdState)
    {
        case _BEACON_FAC_PAGE3_EXIT:
            ScalerDDomainBackgroundEnable(_DISABLE); 
            BeaconFactoryOsdPage2();
            break;
        default:
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);
            g_ucBeaconFacOsdState = g_ucBeaconFacOsdState + _FAC_PAGE3_AMOUNT + 1;
            BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);
            break;
    }
}

void BeaconFactorySelectNextItemPage3(void)
{    
    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);
    g_ucBeaconFacOsdState = BeaconFactoryFuncValueChange(g_ucBeaconFacOsdState,_BEACON_FAC_PAGE3_SELECT_END-1,_BEACON_FAC_PAGE3_START+1,_ON);
    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);
}

void BeaconFactoryExitItemPage3(void)
{
    BeaconFactoryExitItemPage1();
}

void BeaconFactoryMenuExitPage3(void)
{
    switch(g_ucBeaconFacOsdState - (_FAC_PAGE3_AMOUNT + 1))
    {
        default:
#if(_SIX_COLOR_SUPPORT == _ON)
            RTDNVRamSaveSixColorData();
#endif
            break;
    }

    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,3);
    g_ucBeaconFacOsdState = g_ucBeaconFacOsdState - (_FAC_PAGE3_AMOUNT + 1); 
    BeaconFactoryMenuItemSel(g_ucBeaconFacOsdState,1);
}


#if(_SIX_COLOR_SUPPORT == _ON)
void BeaconFactoryRSatAdjust()
{            
//R Y G C B M
  //for(i=0;i<10;i++)
    g_stSixColorData.ucSixColorSaturationR = BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorSaturationR,200,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM1- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationR, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_R, g_stSixColorData.ucSixColorHueR, g_stSixColorData.ucSixColorSaturationR); 
    ScalerColorSixColorInitial();
}
void BeaconFactoryYSatAdjust()
{
//Yellow=R+G
//R Y G C B M
  //for(i=0;i<10;i++)
    g_stSixColorData.ucSixColorSaturationY= BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorSaturationY,200,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM2- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationY, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_Y, g_stSixColorData.ucSixColorHueY, g_stSixColorData.ucSixColorSaturationY); 
    ScalerColorSixColorInitial();
}

void BeaconFactoryGSatAdjust()
{
//R Y G C B M
  //for(i=0;i<10;i++)
    g_stSixColorData.ucSixColorSaturationG = BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorSaturationG,200,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM3- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationG, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_G, g_stSixColorData.ucSixColorHueG, g_stSixColorData.ucSixColorSaturationG); 
    ScalerColorSixColorInitial();
}
void BeaconFactoryCSatAdjust()
{
//?¨¤
    g_stSixColorData.ucSixColorSaturationC= BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorSaturationC,200,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM4- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationC, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_C, g_stSixColorData.ucSixColorHueC, g_stSixColorData.ucSixColorSaturationC); 
    ScalerColorSixColorInitial();
}

void BeaconFactoryBSatAdjust()
{
//R Y G C B M
  //for(i=0;i<10;i++)
    g_stSixColorData.ucSixColorSaturationB = BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorSaturationB,200,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM5- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationB, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_B, g_stSixColorData.ucSixColorHueB, g_stSixColorData.ucSixColorSaturationB); 
    ScalerColorSixColorInitial();
}
void BeaconFactoryMSatAdjust()
{
    g_stSixColorData.ucSixColorSaturationM = BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorSaturationM,200,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM6- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorSaturationM, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_M, g_stSixColorData.ucSixColorHueM, g_stSixColorData.ucSixColorSaturationM); 
    ScalerColorSixColorInitial();
}



void BeaconFactoryRHueAdjust()
{            
//R Y G C B M
  //for(i=0;i<10;i++)
    g_stSixColorData.ucSixColorHueR = BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorHueR,100,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM7- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorHueR, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_R, g_stSixColorData.ucSixColorHueR, g_stSixColorData.ucSixColorSaturationR); 
    ScalerColorSixColorInitial();
}
void BeaconFactoryYHueAdjust()
{
//Yellow=R+G
//R Y G C B M
  //for(i=0;i<10;i++)
    g_stSixColorData.ucSixColorHueY= BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorHueY,100,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM8- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorHueY, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_Y, g_stSixColorData.ucSixColorHueY, g_stSixColorData.ucSixColorSaturationY); 
    ScalerColorSixColorInitial();
}

void BeaconFactoryGHueAdjust()
{
//R Y G C B M
  //for(i=0;i<10;i++)
    g_stSixColorData.ucSixColorHueG = BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorHueG,100,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM9- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorHueG, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_G, g_stSixColorData.ucSixColorHueG, g_stSixColorData.ucSixColorSaturationG); 
    ScalerColorSixColorInitial();
}
void BeaconFactoryCHueAdjust()
{
//?¨¤
//R Y G C B M
 // for(i=0;i<10;i++)
    g_stSixColorData.ucSixColorHueC= BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorHueC,100,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM10- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorHueC, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_C, g_stSixColorData.ucSixColorHueC, g_stSixColorData.ucSixColorSaturationC); 
    ScalerColorSixColorInitial();
}

void BeaconFactoryBHueAdjust()
{
//R Y G C B M
 // for(i=0;i<10;i++)
    g_stSixColorData.ucSixColorHueB = BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorHueB,100,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM11- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorHueB, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_B, g_stSixColorData.ucSixColorHueB, g_stSixColorData.ucSixColorSaturationB); 
    ScalerColorSixColorInitial();
}
void BeaconFactoryMHueAdjust()
{
//R Y G C B M
 // for(i=0;i<10;i++)
    g_stSixColorData.ucSixColorHueM = BeaconFactoryFuncValueChange(g_stSixColorData.ucSixColorHueM,100,0,_OFF);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM12- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_stSixColorData.ucSixColorHueM, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    ScalerColorSixColorAdjust(_SIXCOLOR_M, g_stSixColorData.ucSixColorHueM, g_stSixColorData.ucSixColorSaturationM); 
    ScalerColorSixColorInitial();
}
#else

void BeaconFactoryGammaBypassAdjust()
{
    if(ScalerGetBit(0x0067, _BIT6) == _BIT6)
    {
        BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM1- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),1, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6));
        ScalerSetBit(0x0067, ~(_BIT6), 0x00); 
    }
    else
    {
        BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM1- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),0, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6));
        ScalerSetBit(0x0067, ~(_BIT6), _BIT6); 
    }
}

void BeaconFactoryDclkAdjust()
{

}


void BeaconFactoryPwmFreqAdjust()
{
    static WORD g_ucTestPwmFrequency = _PWM_FREQ;
    g_ucTestPwmFrequency = BeaconFactoryFuncValueChange(g_ucTestPwmFrequency,65535,0,_ON);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM3- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),g_ucTestPwmFrequency, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6));
    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, g_ucTestPwmFrequency); 
}

void BeaconFactoryFlashWPPinAdjust()
{
    if(ScalerGetByte(0xFE19) == 0x00)
    {
        BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM4- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),1, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6));
        ScalerSetByte(0xFE19,0x01); 
    }
    else
    {
        BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM4- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),0, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6));
        ScalerSetByte(0xFE19,0x00); 
    }    
}

void BeaconFactoryGrayLevelAdjust()
{
    static BYTE ucPra = 0;
    ucPra = BeaconFactoryFuncValueChange(ucPra,255,0,_ON);
    BeaconFactoryFuncShowNumber(ROW(_BEACON_FAC_PAGE3_ITEM5- _BEACON_FAC_PAGE3_START), COL(_OSD_PARAMETER_COL),ucPra, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_6));
    // Set Background Color to RGB
    ScalerDDomainBackgroundSetColor(ucPra, ucPra, ucPra);
    ScalerDDomainBackgroundEnable(_ENABLE); 
}

#endif

//----------------------------------------------------------------------------------------------------
//BeaconFactory OSD Operation Table
//----------------------------------------------------------------------------------------------------
code void (*OperationFacOsdTable[][4])(void) =
{
//No use.Just for _BEACON_FAC_OSD_NONE
{ BeaconFactoryExitItemPage1,       BeaconFactoryExitItemPage1,             BeaconFactoryExitItemPage1,         BeaconFactoryExitItemPage1},
/////////////////////////////////////////////////////////////////////////////////////////////////
//Page 1 Select
/////////////////////////////////////////////////////////////////////////////////////////////////
{ BeaconFactoryMenuItemPage1,       BeaconFactorySelectNextItemPage1,       BeaconFactorySelectNextItemPage1,   BeaconFactoryExitItemPage1},
//...Amount: - _FAC_PAGE1_AMOUNT

/////////////////////////////////////////////////////////////////////////////////////////////////
//Page 1 Adjust  parameter
/////////////////////////////////////////////////////////////////////////////////////////////////
{ BeaconFactoryMenuExitPage1,       BeaconFactoryExitItemPage1,             BeaconFactoryExitItemPage1,         BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryGammaAdjust,               BeaconFactoryGammaAdjust,           BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryDBrightnessAdjust,         BeaconFactoryDBrightnessAdjust,     BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryContrastAdjust,            BeaconFactoryContrastAdjust,        BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryBacklightAdjust,           BeaconFactoryBacklightAdjust,       BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryColorTempAdjust,           BeaconFactoryColorTempAdjust,       BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryColorTempAdjustR,          BeaconFactoryColorTempAdjustR,      BeaconFactoryMenuExitPage1},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryColorTempAdjustG,          BeaconFactoryColorTempAdjustG,      BeaconFactoryMenuExitPage1},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryColorTempAdjustB,          BeaconFactoryColorTempAdjustB,      BeaconFactoryMenuExitPage1},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryBacklightRegMaxAdjust,     BeaconFactoryBacklightRegMaxAdjust, BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryBacklightRegMidAdjust,     BeaconFactoryBacklightRegMidAdjust, BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryBacklightRegMinAdjust,     BeaconFactoryBacklightRegMinAdjust, BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryBurnAdjust,                BeaconFactoryBurnAdjust,            BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactorySouceDetTypeAdjust,        BeaconFactorySouceDetTypeAdjust,    BeaconFactoryMenuExitPage1,},//FAC_ADD_SOURCE_DET_ON_OFF_20151223 add
{ BeaconFactoryMenuExitPage1,       BeaconFactoryExitItemPage1,             BeaconFactoryExitItemPage1,         BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryExitItemPage1,             BeaconFactoryExitItemPage1,         BeaconFactoryMenuExitPage1,},
{ BeaconFactoryMenuExitPage1,       BeaconFactoryExitItemPage1,             BeaconFactoryExitItemPage1,         BeaconFactoryMenuExitPage1,},
//No use.Just for _BEACON_FAC_OSD_ADJUST_END
{ BeaconFactoryExitItemPage1,       BeaconFactoryExitItemPage1,             BeaconFactoryExitItemPage1,         BeaconFactoryExitItemPage1},

/////////////////////////////////////////////////////////////////////////////////////////////////
//Page 2 Select
/////////////////////////////////////////////////////////////////////////////////////////////////
{ BeaconFactoryMenuItemPage2,       BeaconFactorySelectNextItemPage2,       BeaconFactorySelectNextItemPage2,   BeaconFactoryExitItemPage2},
//...Amount:- _FAC_PAGE2_AMOUNT

/////////////////////////////////////////////////////////////////////////////////////////////////
//Page 2 Adjust  parameter
/////////////////////////////////////////////////////////////////////////////////////////////////
{ BeaconFactoryMenuExitPage2,       BeaconFactorySharpnessAdjust,           BeaconFactorySharpnessAdjust,       BeaconFactoryMenuExitPage2,},
{ BeaconFactoryMenuExitPage2,       BeaconFactorySaturationAdjust,          BeaconFactorySaturationAdjust,      BeaconFactoryMenuExitPage2,},
#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
{ BeaconFactoryMenuExitPage2,       BeaconFactoryUartEnableAdjust,          BeaconFactoryUartEnableAdjust,      BeaconFactoryMenuExitPage2,},
#endif
{ BeaconFactoryMenuExitPage2,       BeaconFactoryOutputHstartAdjust,        BeaconFactoryOutputHstartAdjust,    BeaconFactoryMenuExitPage2,},
{ BeaconFactoryMenuExitPage2,       BeaconFactoryOutputVstartAdjust,        BeaconFactoryOutputVstartAdjust,    BeaconFactoryMenuExitPage2,},
{ BeaconFactoryMenuExitPage2,       BeaconFactorySSCAdjust,                 BeaconFactorySSCAdjust,             BeaconFactoryMenuExitPage2,},
{ BeaconFactoryMenuExitPage2,       BeaconFactoryFMDIVAdjust,               BeaconFactoryFMDIVAdjust,           BeaconFactoryMenuExitPage2,},
{ BeaconFactoryMenuExitPage2,       BeaconFactoryEdidWriteAdjust,           BeaconFactoryEdidWriteAdjust,       BeaconFactoryMenuExitPage2,},
{ BeaconFactoryMenuExitPage2,       BeaconFactoryDdcciChannelAdjust,        BeaconFactoryDdcciChannelAdjust,    BeaconFactoryMenuExitPage2,},
#if(_SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)
{ BeaconFactoryMenuExitPage2,       BeaconFactoryLoadGammaFromEepromAdjust, BeaconFactoryLoadGammaFromEepromAdjust, BeaconFactoryMenuExitPage2,},
{ BeaconFactoryMenuExitPage2,       BeaconFactorySaveGammaToEepromAdjust,   BeaconFactorySaveGammaToEepromAdjust,   BeaconFactoryMenuExitPage2,},
#endif
#if(_ALS_TYPE != _SENSER_NONE)
{ BeaconFactoryMenuExitPage2,       BeaconFactoryALSAdjust,                 BeaconFactoryALSAdjust,             BeaconFactoryMenuExitPage2,},
#endif
{ BeaconFactoryMenuExitPage2,       BeaconFactoryMenuExitPage2,             BeaconFactoryMenuExitPage2,         BeaconFactoryMenuExitPage2,},
{ BeaconFactoryMenuExitPage2,       BeaconFactoryMenuExitPage2,             BeaconFactoryMenuExitPage2,         BeaconFactoryMenuExitPage2,},
{ BeaconFactoryMenuExitPage2,       BeaconFactoryMenuExitPage2,             BeaconFactoryMenuExitPage2,         BeaconFactoryMenuExitPage2,},
//No use.Just for _BEACON_FAC_PAGE2_ADJUST_END
{ BeaconFactoryExitItemPage1,       BeaconFactoryExitItemPage1,             BeaconFactoryExitItemPage1,         BeaconFactoryExitItemPage1},


/////////////////////////////////////////////////////////////////////////////////////////////////
//Page 3 Select
/////////////////////////////////////////////////////////////////////////////////////////////////
{ BeaconFactoryMenuItemPage3,       BeaconFactorySelectNextItemPage3,       BeaconFactorySelectNextItemPage3,   BeaconFactoryExitItemPage3},
//...Amount:- _FAC_PAGE3_AMOUNT

/////////////////////////////////////////////////////////////////////////////////////////////////
//Page 3 Adjust  parameter
/////////////////////////////////////////////////////////////////////////////////////////////////

#if(_SIX_COLOR_SUPPORT == _ON)
{ BeaconFactoryMenuExitPage3,       BeaconFactoryRSatAdjust,                BeaconFactoryRSatAdjust,            BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryYSatAdjust,                BeaconFactoryYSatAdjust,            BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryGSatAdjust,                BeaconFactoryGSatAdjust,            BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryCSatAdjust,                BeaconFactoryCSatAdjust,            BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryBSatAdjust,                BeaconFactoryBSatAdjust,            BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryMSatAdjust,                BeaconFactoryMSatAdjust,            BeaconFactoryMenuExitPage3,},

{ BeaconFactoryMenuExitPage3,       BeaconFactoryRHueAdjust,                BeaconFactoryRHueAdjust,            BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryYHueAdjust,                BeaconFactoryYHueAdjust,            BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryGHueAdjust,                BeaconFactoryGHueAdjust,            BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryCHueAdjust,                BeaconFactoryCHueAdjust,            BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryBHueAdjust,                BeaconFactoryBHueAdjust,            BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryMHueAdjust,                BeaconFactoryMHueAdjust,            BeaconFactoryMenuExitPage3,},
#else
{ BeaconFactoryMenuExitPage3,       BeaconFactoryGammaBypassAdjust,         BeaconFactoryGammaBypassAdjust,     BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryDclkAdjust,                BeaconFactoryDclkAdjust,            BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryPwmFreqAdjust,             BeaconFactoryPwmFreqAdjust,         BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryFlashWPPinAdjust,          BeaconFactoryFlashWPPinAdjust,      BeaconFactoryMenuExitPage3,},
{ BeaconFactoryMenuExitPage3,       BeaconFactoryGrayLevelAdjust,           BeaconFactoryGrayLevelAdjust,       BeaconFactoryMenuExitPage3,},
#endif
{ BeaconFactoryMenuExitPage3,       BeaconFactoryMenuExitPage3,             BeaconFactoryMenuExitPage3,         BeaconFactoryMenuExitPage3,},

//No use.Just for _BEACON_FAC_PAGE3_ADJUST_END
{ BeaconFactoryExitItemPage1,       BeaconFactoryExitItemPage1,             BeaconFactoryExitItemPage1,         BeaconFactoryExitItemPage1},

};


#endif
