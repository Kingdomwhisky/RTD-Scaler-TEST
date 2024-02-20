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
// ID Code      : Gain_14_1200nit_Table.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// HDR10 BRIGHTNESS ADJUST GAIN 1.4 1200 NIT
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
0x1C, 0x39, 0x55, 0x6F, 0x88, 0x9D, 0xAE, 0xBA, 0xC6, 0xD2, 0xE4, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// usercurve  0x011B ~ 0x0150
0x0E, 0x00, 0x80, 0x2A, 0xC0, 0x00,
0x47, 0x40, 0x00, 0x62, 0x80, 0xC0,
0x7C, 0x40, 0x40, 0x93, 0x80, 0xC0,
0xA7, 0x40, 0xC0, 0xB5, 0x40, 0xC0,
0xC0, 0x80, 0x40, 0xCB, 0x80, 0xC0,
0xDB, 0x40, 0xC0, 0xEE, 0x40, 0x40,
0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0,
0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

#endif