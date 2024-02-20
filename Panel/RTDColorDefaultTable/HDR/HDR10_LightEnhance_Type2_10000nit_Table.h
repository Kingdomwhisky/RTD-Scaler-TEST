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
// ID Code      : Gain_14_10000nit_Table.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// HDR10 BRIGHTNESS ADJUST GAIN 1.4 10000 NIT
//****************************************************************************

#if(_DCC_TABLE_TYPE == _DCC_GEN_1)

_DCC_CONTROL,
0x30,
_DCC_TABLE,
//control
0x00, 0x00, 0x00,
0x01, 0x00, 0x00,
0x00, 0x00, 0x00,
// control LSB 0x0017 ~ 0x001B
0x00, 0x00, 0x00, 0x00, 0x00,
// usercurve 0x0100 ~ 0x010F
0x16, 0x2C, 0x42, 0x58, 0x6D, 0x81, 0x93, 0xA4, 0xB3, 0xBF, 0xC7, 0xCE, 0xD6, 0xE2, 0xF0, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// usercurve  0x011B ~ 0x0150
0x0A, 0xC0, 0x00, 0x21, 0x40, 0x40,
0x37, 0x80, 0x80, 0x4D, 0x40, 0x00,
0x62, 0x80, 0x00, 0x77, 0x00, 0x00,
0x8A, 0x40, 0x80, 0x9C, 0x00, 0x40,
0xAC, 0x00, 0x00, 0xB9, 0x80, 0x00,
0xC3, 0x80, 0x80, 0xCA, 0xC0, 0x80,
0xD2, 0x40, 0x00, 0xDB, 0x80, 0x40,
0xE9, 0x40, 0xC0, 0xF8, 0x80, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

#endif