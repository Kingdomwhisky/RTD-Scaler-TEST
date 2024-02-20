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
// ID Code      : RL6463_Series_OSDLibInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __RL6463_SERIES_OSD_LIB_INTERFACE__
#define __RL6463_SERIES_OSD_LIB_INTERFACE__

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define _OSD_POSITION_OFFSET_H                                  0x28
#define _OSD_POSITION_OFFSET_V                                  0x04

#define _OSD_DOUBLE_POSITION_OFFSET_H                           0x0C
#define _OSD_DOUBLE_POSITION_OFFSET_V                           0x01

#define _OSD_ROTATE_NO_SWAP                                     0x00
#define _OSD_ROTATE_CCW                                         (_BIT7)
#define _OSD_ROTATE_CW                                          (_BIT7 | _BIT6)

#define GET_OSD_POSITION_V_OFFSET_CORRECT_COMPENSATION()        (g_ucOSDPositionVOffsetCorrectCompensation)

//****************************************************************************
// INTERFACE STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

typedef enum
{
    _OSD_WIN_COLOR_PALETTE_0_15,
    _OSD_WIN_COLOR_PALETTE_16_31,
    _OSD_WIN_COLOR_PALETTE_32_41,
    _OSD_WIN_COLOR_PALETTE_42_63,
} EnumOsdWinColorOffsetType;

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern BYTE g_ucOSDPositionVOffsetCorrectCompensation;


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
//--------------------------------------------------
// SRAM
//--------------------------------------------------
extern void ScalerOsdFontRotateCtrl(EnumOsdRotateType enumRotType, BYTE ucFontDownloadRotEn, BYTE ucDispRotEn);
extern void ScalerOsdHardwareCompression(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType, bit bTableLocation);
extern void ScalerOsdHardwareVLC(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType);
extern void ScalerOsdSramBaseAddressSet(EnumOsdMapType enumOsdMapType, BYTE ucRowCommandStart, WORD usCharactorCommandStart, WORD usFontStart);

//--------------------------------------------------
// Function
//--------------------------------------------------
extern void ScalerOsdSetTransparency(BYTE ucTransparency);
extern void ScalerOsdSetTransparency_EXINT(BYTE ucTransparency);
extern void ScalerOsdPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
extern void ScalerOsdPositionOffsetCorrection(void);

//--------------------------------------------------
// Window
//--------------------------------------------------
extern void ScalerOsdWinodwColorOffset(EnumOsdWinColorOffsetType enumOffset);
#endif
