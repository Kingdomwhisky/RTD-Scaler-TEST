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
// ID Code      : DccModeHDRLike2084.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DCC MODE HDR Like 2084
//****************************************************************************
#if(_DCC_TABLE_TYPE == _DCC_GEN_1)

_DCC_CONTROL,
0x10,
_DCC_TABLE,
//control
0x04, 0x00, 0x00,
0xB0, 0xFF, 0x00,
0x10, 0x00, 0xFF,
// control LSB 0x0017 ~ 0x001B
0x00, 0x00, 0x00, 0x00, 0x00,
//usercurve
0x18, 0x2A, 0x3F, 0x52,
0x62, 0x72, 0x82, 0x92,
0xA3, 0xB4, 0xC5, 0xD5,
0xE2, 0xF0, 0xFA, 0x00,
0x00, 0x00, 0x02,
0x50, 0x14, 0x34, 0x22,
// usercurve Add 0x011B ~ 0x0150
0x0A, 0x80, 0x00, 0x1F, 0x80, 0x00,
0x34, 0x80, 0x00, 0x48, 0x80, 0x00,
0x5A, 0x00, 0x00, 0x6A, 0x00, 0x00,
0x7A, 0x00, 0x00, 0x8A, 0x00, 0x00,
0x9A, 0x80, 0x00, 0xAB, 0x80, 0x00,
0xBC, 0x80, 0x00, 0xCD, 0x00, 0x00,
0xDB, 0x80, 0x00, 0xE9, 0x00, 0x00,
0xF5, 0x00, 0x00, 0xFD, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
_DCC_END,

#endif
