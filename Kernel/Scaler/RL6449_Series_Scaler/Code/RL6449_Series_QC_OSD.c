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
// ID Code      : RL6449_Series_QC_OSD.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6449_SERIES_QC_OSD__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

#include _OSD_INCLUDE

//--------------------------------------------------
// Definitions of Map Row & Col Size
//--------------------------------------------------
#define _OSD_2_FONT_FUNCTION_MAP                        _ON
#define _OSD_TABLE_CODE_WRITE                           _OFF

#define _OSD_MAP_FONT_BASE_ADDRESS                      856

#define _OSD_MAPA_SIZE_ROW                              14
#define _OSD_MAPA_SIZE_COL                              32
#define _OSD_MAPA_ADDRESS_ROWCOMMAND                    0
#define _OSD_MAPA_ADDRESS_CHARCOMMAND                   23

#define _OSD_MAPB_SIZE_ROW                              7
#define _OSD_MAPB_SIZE_COL                              55
#define _OSD_MAPB_ADDRESS_ROWCOMMAND                    15
#define _OSD_MAPB_ADDRESS_CHARCOMMAND                   471

//----------------------------------------------------------------------------
// OSD QC SRAM Definition
//----------------------------------------------------------------------------
#define ROW(x)                                          (x)
#define COL(x)                                          (x)
#define ROW_B(x)                                        ((x) + 100)

#define LANGUAGE(x)                                     (x)
#define WIDTH(x)                                        (x)
#define HEIGHT(x)                                       (x)
#define LENGTH(x)                                       (x)
#define VALUES(x)                                       (x)
#define TYPE(x)                                         (x)

#define ICON_2BIT(x)                                    ((_2BIT_FONT_ICON_START / 2) - _2BIT_OFFSET + (x))
#define ICON_4BIT(x)                                    ((_4BIT_FONT_ICON_START / 4) + (x))

#define _CHAR_WIDTH_3                                   (0x03)
#define _CHAR_WIDTH_4                                   (0x04)
#define _CHAR_WIDTH_5                                   (0x05)
#define _CHAR_WIDTH_6                                   (0x06)
#define _CHAR_WIDTH_7                                   (0x07)
#define _CHAR_WIDTH_8                                   (0x08)
#define _CHAR_WIDTH_9                                   (0x09)
#define _CHAR_WIDTH_10                                  (0x0A)
#define _CHAR_WIDTH_11                                  (0x0B)
#define _CHAR_WIDTH_12                                  (0x0C)

#define _1BIT_FONT_ICON_SIZE                            32
#define _1BIT_FONT_ICON_START                           0

#define _2BIT_OFFSET                                    (_1BIT_FONT_ICON_SIZE / 2)
#define _2BIT_FONT_ICON_SIZE                            120 // (255 * 2)
#define _2BIT_FONT_ICON_START                           (_1BIT_FONT_ICON_SIZE)

#define _4BIT_FONT_ICON_SIZE                            308
#define _4BIT_FONT_ICON_START                           (_1BIT_FONT_ICON_SIZE + _2BIT_FONT_ICON_SIZE)

#define _OSD_FONT_SIZE                                  (_1BIT_FONT_ICON_SIZE + _2BIT_FONT_ICON_SIZE + _4BIT_FONT_ICON_SIZE)

#define _ROW_COMMAND_DOUBLE_DISABLE                     (0x00)
#define _ROW_COMMAND_DOUBLE_ENABLE                      (_BIT1 | _BIT0)
#define _ROW_COMMAND_BORDER                             (_BIT2)
#define _ROW_COMMAND_SHADOW_LEFT_TOP                    (_BIT4)
#define _ROW_COMMAND_SHADOW_LEFT_BOTTOM                 (_BIT4 | _BIT2)
#define _ROW_COMMAND_SHADOW_RIGHT_TOP                   (_BIT4 | _BIT3)
#define _ROW_COMMAND_SHADOW_RIGHT_BOTTOM                (_BIT4 | _BIT3 | _BIT2)

#define _CLEAR_DATA                                     0x4C, 0x06, 0x17

//----------------------------------------------------------------------------
// OSD QC Window Definition
//----------------------------------------------------------------------------
#define _OSD_OFFSET_X                                   40
#define _OSD_OFFSET_Y                                   40

#define _OSD_WINDOW_WIDTH                               200
#define _OSD_WINDOW_HEIGHT                              200

#define _OSD_WINDOW_OFFSET_X                            230
#define _OSD_WINDOW_OFFSET_Y                            230

#define _OSD_WINDOW_0_X_START                           510
#define _OSD_WINDOW_0_Y_START                           10

#define _OSD_WINDOW_1_X_START                           (_OSD_WINDOW_0_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_1_Y_START                           (_OSD_WINDOW_0_Y_START)

#define _OSD_WINDOW_2_X_START                           (_OSD_WINDOW_1_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_2_Y_START                           (_OSD_WINDOW_0_Y_START)

#define _OSD_WINDOW_3_X_START                           (_OSD_WINDOW_2_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_3_Y_START                           (_OSD_WINDOW_0_Y_START)

#define _OSD_WINDOW_4_X_START                           (_OSD_WINDOW_3_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_4_Y_START                           (_OSD_WINDOW_0_Y_START)

#define _OSD_WINDOW_5_X_START                           (_OSD_WINDOW_0_X_START)
#define _OSD_WINDOW_5_Y_START                           (_OSD_WINDOW_0_Y_START + _OSD_WINDOW_OFFSET_Y)

#define _OSD_WINDOW_6_X_START                           (_OSD_WINDOW_0_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_6_Y_START                           (_OSD_WINDOW_5_Y_START)

#define _OSD_WINDOW_7_X_START                           (_OSD_WINDOW_1_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_7_Y_START                           (_OSD_WINDOW_5_Y_START)

#define _OSD_WINDOW_8_X_START                           (_OSD_WINDOW_2_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_8_Y_START                           (_OSD_WINDOW_5_Y_START)

#define _OSD_WINDOW_9_X_START                           (_OSD_WINDOW_3_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_9_Y_START                           (_OSD_WINDOW_5_Y_START)

#define _OSD_WINDOW_4_1_X_START                         (_OSD_WINDOW_0_X_START)
#define _OSD_WINDOW_4_1_Y_START                         (_OSD_WINDOW_5_Y_START + _OSD_WINDOW_OFFSET_Y)

#define _OSD_WINDOW_4_2_X_START                         (_OSD_WINDOW_0_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_4_2_Y_START                         (_OSD_WINDOW_4_1_Y_START)

#define _OSD_WINDOW_4_3_X_START                         (_OSD_WINDOW_1_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_4_3_Y_START                         (_OSD_WINDOW_4_1_Y_START)

#define _OSD_WINDOW_4_4_X_START                         (_OSD_WINDOW_2_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_4_4_Y_START                         (_OSD_WINDOW_4_1_Y_START)

#define _OSD_WINDOW_4_5_X_START                         (_OSD_WINDOW_0_X_START)
#define _OSD_WINDOW_4_5_Y_START                         (_OSD_WINDOW_4_1_Y_START + _OSD_WINDOW_OFFSET_Y)

#define _OSD_WINDOW_4_6_X_START                         (_OSD_WINDOW_0_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_4_6_Y_START                         (_OSD_WINDOW_4_5_Y_START)

#define _OSD_WINDOW_4_7_X_START                         (_OSD_WINDOW_1_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_4_7_Y_START                         (_OSD_WINDOW_4_5_Y_START)

#define _OSD_WINDOW_4_8_X_START                         (_OSD_WINDOW_2_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_4_8_Y_START                         (_OSD_WINDOW_4_5_Y_START)

#define _OSD_WINDOW_5_1_X_START                         (10) // _OSD_WINDOW_0_X_START
#define _OSD_WINDOW_5_1_Y_START                         (_OSD_WINDOW_4_1_Y_START)

#define _OSD_WINDOW_5_2_X_START                         (_OSD_WINDOW_5_1_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_5_2_Y_START                         (_OSD_WINDOW_5_1_Y_START)

#define _OSD_WINDOW_5_3_X_START                         (_OSD_WINDOW_5_1_X_START)
#define _OSD_WINDOW_5_3_Y_START                         (_OSD_WINDOW_5_1_Y_START + _OSD_WINDOW_OFFSET_Y)

#define _OSD_WINDOW_5_4_X_START                         (_OSD_WINDOW_5_3_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_5_4_Y_START                         (_OSD_WINDOW_5_3_Y_START)

#define _OSD_WINDOW_5_5_X_START                         (_OSD_WINDOW_5_3_X_START)
#define _OSD_WINDOW_5_5_Y_START                         (_OSD_WINDOW_5_3_Y_START + _OSD_WINDOW_OFFSET_Y)

#define _OSD_WINDOW_5_6_X_START                         (_OSD_WINDOW_5_5_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_5_6_Y_START                         (_OSD_WINDOW_5_5_Y_START)

#define _OSD_WINDOW_5_7_X_START                         (_OSD_WINDOW_5_5_X_START)
#define _OSD_WINDOW_5_7_Y_START                         (_OSD_WINDOW_5_5_Y_START + _OSD_WINDOW_OFFSET_Y)

#define _OSD_WINDOW_5_8_X_START                         (_OSD_WINDOW_5_7_X_START + _OSD_WINDOW_OFFSET_X)
#define _OSD_WINDOW_5_8_Y_START                         (_OSD_WINDOW_5_7_Y_START)


#define _ONE_1BIT_ADDRESS_SIZE                          9     // 1 font = 9 address
#define _SRAM_SIZE_2BIT_SIZE                            4     // 4 2-bit fonts
#define _SRAM_SIZE_4BIT_SIZE                            4     // 4 4-bit fonts

#define _SRAM_SIZE_2BIT_OFFSET                          508   // should be divisible by 2
#define _SRAM_SIZE_4BIT_OFFSET                          508     // should be divisible by 4
#define _SRAM_SIZE_FONT_BASE_ADDRESS                    (_OSD_SRAM_SIZE - (_SRAM_SIZE_4BIT_OFFSET * 4 * _ONE_1BIT_ADDRESS_SIZE) - (_SRAM_SIZE_4BIT_SIZE * 4 * _ONE_1BIT_ADDRESS_SIZE))  // max SRAM size

#define _QC_OSD_POSITION_OFFSET_H                       0x3B
#define _QC_OSD_POSITION_OFFSET_V                       0x04

#define _QC_OSD_DOUBLE_POSITION_OFFSET_H                0x2A
#define _QC_OSD_DOUBLE_POSITION_OFFSET_V                0x01

#define _QC_OSD_OFFSET_DRAW_WINDOW_H                    10
#define _QC_OSD_OFFSET_DRAW_WINDOW_V                    0

#define _ROUND_WINDOW_1                                 _OSD_WINDOW_5_1
#define _ROUND_WINDOW_2                                 _OSD_WINDOW_5_4
#define _ROUND_WINDOW_3                                 _OSD_WINDOW_5_8

#define _OSD_SCALING_RATIO_150							((WORD)64 * 100 / 150)
#define _OSD_SCALING_RATIO_200							((WORD)64 * 100 / 200)
#define _OSD_SCALING_RATIO_250							((WORD)64 * 100 / 250)
#define _OSD_SCALING_RATIO_300							((WORD)64 * 100 / 300)

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
enum OSDQCHardwareVLCDef
{
    _OSD_VLC_QCMAP,
    _OSD_VLC_QCFONT_GLOBAL,
    _OSD_VLC_QCFONT_2BITBROOK,
    _OSD_VLC_QCFONT_4BITLUFFY,

    _OSD_VLC_24_36_1BIT,
    _OSD_VLC_24_36_2BIT,
    _OSD_VLC_24_36_4BIT,
};
enum OSDQCIconDef
{
    _OSD_QCICON_1BIT,     _OSD_QCICON_1BIT_BOARD_SHADOW,
    _OSD_QCICON_2BIT,     _OSD_QCICON_4BIT,
};
enum OSDQCFrameDef
{
    _OSD_FRAME_1,
    _OSD_FRAME_2, _OSD_FRAME_2_1, _OSD_FRAME_2_2, _OSD_FRAME_2_3,
    _OSD_FRAME_3,       _OSD_FRAME_4,
    _OSD_FRAME_5,       _OSD_FRAME_6,
    _OSD_FRAME_7,       _OSD_FRAME_8,
    _OSD_FRAME_9,       _OSD_FRAME_10,
    _OSD_FRAME_11,      _OSD_FRAME_12,
    _OSD_FRAME_13,      _OSD_FRAME_14,
    _OSD_FRAME_15,      _OSD_FRAME_16,
    _OSD_FRAME_17,      _OSD_FRAME_18,
    _OSD_FRAME_19,      _OSD_FRAME_20,
    _OSD_FRAME_END,
};

//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// Load OSD FONTDATA_TABLE
//--------------------------------------------------
BYTE code tQCDRAW_MAP[] =
{
0x01,0x4c,0x82,0x37,0x56,0x9a,0xbd,0xef,0x05,0xe5,0x23,0x59,0x46,0xb2,0x8c,0x64,0x19,0xc9,0x32,0x92,0x65,0x24,0xcb,0x48,0x96,0x91,0x2c,0x23,0x59,0x46,0xb2,0x8c,0x64,0x19,0xc9,0x32,0x92,0x65,0x24,0x0b,0x30,0x92,0x7d,0x46,0xb2,0xcf,0x48,0xf6,0x19,0xc9,0x3e,0x23,0xd9,0x67,0x24,0xfb,0x8c,0x64,0x1f,0xa0,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,
0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,
0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,
0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,
0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,
0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,
0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xa8,0x26,0xaa,0x89,0x6a,0xa2,0x9a,0xf8,0xff,
};

BYTE code tQCFONT_GLOBAL[] =
{
0x01,0x8f,0x9b,0xe3,0x65,0x27,0xda,0x4c,0x00,0xeb,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0x74,0x75,0x4b,0xaa,0xec,0xa4,0x4a,
0x26,0x6b,0x56,0x66,0xd6,0xca,0xca,0xcc,0x8a,0xa4,0x6a,0x4b,
0xaa,0x74,0xa7,0x8b,0xb4,0x6e,0x09,0x9e,0x04,0x57,0x22,0xfb,
0x4a,0xb8,0xae,0x84,0x4b,0x22,0x2d,0x41,0x77,0x1a,0xe9,0xea,
0x96,0x54,0xe9,0xa4,0x4a,0x66,0xd6,0xcc,0x37,0x59,0xeb,0xee,
0x99,0xa9,0x9f,0xa4,0x56,0x4b,0xaa,0x74,0xa7,0x8b,0x74,0x75,
0x4b,0xaa,0x74,0x52,0x65,0x32,0x33,0xc9,0xa4,0xea,0x3d,0x99,
0xb5,0x22,0xa9,0xd9,0x92,0x2a,0xdd,0xe9,0x22,0x5d,0xdd,0x92,
0x2a,0x27,0xa9,0xb2,0xee,0x54,0xbd,0xfd,0xb9,0xd7,0x9c,0x73,
0xdf,0x55,0x47,0xa6,0xea,0x95,0x54,0xe9,0x4e,0x17,0xe9,0xea,
0x96,0x54,0xe9,0x4c,0x15,0xc9,0xd4,0xce,0x64,0xa6,0x4f,0x66,
0x55,0x24,0xb5,0xb6,0xa4,0x4a,0x77,0xba,0x48,0x57,0xb7,0xa4,
0x4a,0x4f,0xaa,0xc8,0xac,0x99,0x4c,0xd6,0xea,0xcc,0xcc,0x8a,
0xa4,0xaa,0x25,0x55,0xba,0xd3,0x45,0xba,0xba,0x25,0x55,0x7a,
0x32,0x23,0xc9,0x77,0xf5,0x93,0x54,0x3d,0x57,0x52,0xf5,0x48,
0xaa,0x2e,0x49,0x95,0xee,0x74,0x91,0xae,0x6e,0x49,0x95,0x4e,
0xaa,0x7c,0x32,0x33,0xd6,0x4c,0x4d,0x9b,0x99,0x21,0xa9,0x6a,
0x49,0x95,0xee,0x74,0x91,0xae,0x6e,0x49,0x95,0x4e,0xa6,0x64,
0xb2,0x56,0x7a,0x66,0x56,0x4e,0x66,0x55,0x24,0xb5,0xb6,0xa4,
0x4a,0x77,0xba,0xfc,0xff,
};

BYTE code tQCFONT_2BITBROOK[] =
{
0x0f,0x18,0x3c,0x7e,0x62,0x4b,0x9d,0x5a,0x04,0xb6,0x00,0x00,
0x00,0x80,0x81,0xd2,0xb8,0xa1,0xc0,0x0d,0x00,0x00,0x00,0x18,
0xa8,0x04,0x93,0x50,0x93,0x30,0x00,0x00,0x00,0xc0,0xc2,0xa1,
0x51,0xee,0x07,0xad,0x16,0x00,0x00,0x00,0xc0,0x22,0x47,0x5a,
0x92,0x9c,0x95,0x24,0xc9,0x4a,0x00,0x00,0x00,0x00,0x00,0x00,
0xd0,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x01,0x00,0x00,0x00,
0x00,0x40,0x15,0x00,0x00,0x00,0x00,0x00,0x00,0x54,0x01,0x00,
0x00,0x00,0x00,0x00,0x3c,0xec,0xa3,0x93,0xae,0xec,0x03,0x00,
0x00,0x00,0x00,0xf0,0xb0,0x8f,0x4e,0xba,0xb2,0x0f,0x6b,0xa3,
0xba,0x31,0x50,0x17,0xcc,0x82,0xab,0x29,0x0b,0x53,0x70,0x0d,
0xac,0xc3,0xda,0xa8,0x6e,0x0c,0xd4,0x05,0xb3,0xe0,0x6a,0xca,
0xc2,0x14,0x5c,0x03,0xeb,0x58,0x4c,0xd4,0x6a,0xb6,0xd9,0x00,
0x00,0x00,0x00,0x14,0x2c,0x26,0x6a,0x35,0xdb,0x6c,0x00,0x00,
0x00,0x00,0x0a,0x00,0x00,0x8b,0x66,0x8e,0x46,0x75,0x53,0xd5,
0xb8,0x06,0xd6,0x05,0xbd,0x00,0x00,0x16,0xcd,0x1c,0x8d,0xea,
0xa6,0xaa,0x71,0x0d,0xac,0x0b,0x7a,0x51,0x70,0x2b,0x6e,0x70,
0x6b,0x94,0xa7,0xc1,0x0d,0x00,0x00,0x26,0x61,0x26,0x61,0x2a,
0x61,0x24,0x94,0x1d,0x30,0x00,0x00,0xa0,0xd0,0x97,0x6e,0xb8,
0x9f,0xa7,0x51,0xf7,0xa3,0x51,0x70,0x6b,0x58,0x64,0x30,0xbd,
0xa8,0x4a,0xf4,0x96,0xc0,0xec,0xd5,0xa8,0xb3,0x34,0x09,0x9c,
0x34,0x2c,0x32,0x98,0x5e,0x14,0x3c,0x50,0x37,0x67,0xd3,0xb7,
0x66,0xe3,0xe9,0x1b,0x75,0x37,0x66,0x20,0x01,0x60,0x2d,0xc8,
0xd1,0x67,0x27,0x7d,0x74,0x92,0x66,0xe7,0xa0,0xa6,0x31,0x03,
0x09,0x40,0x41,0xad,0xbd,0x08,0x95,0x17,0x5c,0x00,0x00,0x00,
0x80,0x82,0x5a,0x7b,0x11,0x2a,0x2f,0xb8,0x00,0x00,0x00,0x80,
0xdd,0x52,0x6b,0xef,0x23,0xa9,0x13,0x86,0x05,0x00,0x00,0x80,
0xc3,0xb0,0x5b,0x6a,0xed,0x7d,0x24,0x75,0xc2,0xb0,0x00,0x00,
0x00,0x70,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xc0,0x14,0x5c,0x37,0xac,0x85,0xea,0xa6,
0x9c,0x45,0xa9,0xc1,0x34,0xdc,0x13,0x66,0x2f,0x5c,0xa6,0xe0,
0xba,0x61,0x2d,0x54,0x37,0xe5,0x2c,0x4a,0x0d,0xa6,0xe1,0x9e,
0x30,0x7b,0xe1,0x82,0x06,0x00,0x00,0x80,0xd5,0x9a,0xd9,0x0e,
0xc7,0x82,0xbd,0xa0,0x01,0x00,0x00,0x60,0xb5,0x66,0xb6,0xc3,
0xb1,0x60,0x2f,0x00,0x00,0x00,0x00,0x50,0x05,0x33,0x30,0x03,
0x00,0x00,0x00,0x00,0x50,0x05,0x33,0x30,0x83,0x0b,0xae,0x05,
0xab,0xa1,0x17,0xac,0xc5,0x58,0x58,0x1b,0xba,0x01,0xc0,0x05,
0xd7,0x82,0xd5,0xd0,0x0b,0xd6,0x62,0x2c,0xac,0x0d,0xdd,0x00,
0x00,0x00,0x00,0x53,0x90,0x8d,0x4a,0x30,0x09,0x35,0x09,0x33,
0x09,0x03,0x00,0x80,0x29,0x58,0x17,0xaa,0x1b,0x03,0x75,0xc3,
0x7d,0x57,0x71,0x57,0x06,0x49,0x4a,0x92,0x64,0x27,0x49,0x92,
0x24,0x49,0x92,0x24,0xe9,0x24,0x89,0x99,0x75,0x40,0xab,0x35,
0x68,0x4a,0xb0,0x36,0x68,0x00,0xd0,0x67,0x8d,0x98,0x59,0x17,
0x68,0xc9,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
0x92,0x24,0x49,0x92,0x24,0xe9,0x95,0x24,0xec,0x44,0x1d,0x09,
0x00,0x00,0x00,0x60,0x17,0xaa,0x57,0x33,0x3c,0xab,0x70,0x58,
0x24,0x9d,0x96,0x24,0x67,0x25,0x49,0x4e,0x92,0x24,0x49,0x92,
0x48,0x2a,0x61,0x24,0xc0,0x61,0x61,0xba,0x1a,0xdb,0xb5,0x60,
0x6e,0xa8,0xc2,0x41,0xba,0x1a,0xa3,0x1b,0x66,0x83,0x02,0x00,
0x98,0x02,0xd5,0x60,0x35,0xac,0x05,0x6b,0x31,0x1b,0x14,0x00,
0xc0,0x14,0xa8,0x06,0xab,0xe1,0x59,0xf0,0x3c,0x00,0x74,0xc3,
0x5a,0xd0,0x0b,0xba,0xe1,0x5a,0x30,0xa3,0xa9,0xea,0xa6,0xaa,
0x01,0x74,0xc3,0x5a,0xd0,0x0b,0xba,0xe1,0x5a,0x30,0xa3,0xa9,
0xea,0xa6,0xaa,0xcd,0x40,0x15,0x00,0x00,0x00,0x00,0x00,0x30,
0x03,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x02,0x7b,0x69,
0x66,0x1a,0xd7,0xc0,0x7a,0x60,0x2d,0x78,0x16,0xdc,0x17,0x00,
0x0b,0xec,0xa5,0x99,0x69,0x5c,0x03,0xeb,0x81,0xb5,0xe0,0x59,
0x70,0x5f,0x26,0x61,0x26,0x61,0x2a,0x61,0x24,0x94,0x1d,0xa8,
0x01,0x00,0x00,0x77,0x15,0xf7,0x5d,0xc5,0x5d,0x8a,0xd1,0x4d,
0xb9,0x16,0xd4,0x00,0x00,0x00,0x00,0x40,0x37,0x53,0x67,0x49,
0x92,0x24,0x49,0x92,0x24,0xb5,0x33,0x09,0xd9,0x09,0x1b,0x00,
0xd0,0xcd,0xd4,0xb5,0x6c,0x4b,0x05,0x8b,0xa6,0x2e,0x03,0xe7,
0x81,0x2b,0xec,0x9d,0xb0,0x77,0xd2,0xb2,0x93,0xb3,0x92,0xec,
0xe4,0x24,0x3b,0x39,0x67,0x92,0x24,0x49,0x92,0x24,0x49,0x92,
0xe1,0x7a,0x66,0x78,0xae,0xa9,0xd6,0x4f,0xb9,0x96,0x76,0x99,
0x7b,0xd6,0xc5,0x7d,0xdd,0x30,0x0b,0x00,0xec,0x0d,0xd9,0xa8,
0x04,0x3b,0x61,0x72,0x92,0x24,0xbd,0x92,0x2c,0x92,0xe0,0x04,
0x72,0x78,0x1e,0x58,0x0f,0xaa,0x1b,0x57,0x61,0x5c,0x93,0xac,
0xea,0x85,0x45,0x19,0x5c,0x1b,0xe6,0x86,0xb5,0x60,0x2d,0xe8,
0x05,0xdd,0x00,0x00,0x00,0x0c,0xe0,0x79,0xe0,0x79,0xa0,0x17,
0x74,0x03,0x00,0x00,0x30,0xd0,0x54,0x35,0xae,0x81,0x7d,0x69,
0xaa,0x7a,0xc1,0x5a,0xb0,0x9a,0xb2,0x9a,0xa9,0xc6,0x8a,0xa6,
0xaa,0x71,0x0d,0xec,0x4b,0x53,0xd5,0x0b,0xd6,0x82,0xd5,0x94,
0xd5,0x4c,0x35,0x56,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xc0,0xa2,0xa6,0x6b,0x2d,0x76,0x75,
0x53,0x05,0x55,0x8d,0xb2,0x9a,0xb2,0x0f,0x18,0x00,0x8b,0x9a,
0xae,0xb5,0xd8,0xd5,0x4d,0x15,0x54,0x35,0xca,0x6a,0xca,0x3e,
0x60,0x00,0x00,0x00,0x00,0x00,0xc0,0x0d,0x5e,0x76,0x52,0x8d,
0x01,0x00,0x00,0x00,0x80,0x1b,0xbc,0xec,0xa4,0x1a,0x93,0x84,
0xec,0x84,0xcd,0x61,0x00,0x00,0x00,0x00,0x60,0xc1,0xda,0xbb,
0x78,0x38,0x0c,0x00,0x00,0x00,0x00,0x24,0x49,0x92,0x9d,0x9d,
0x50,0x26,0x00,0x00,0x00,0x00,0x50,0xab,0xd7,0x52,0x7b,0x5d,
0xab,0x28,0x13,0x00,0x00,0x00,0x00,0x40,0x02,0x27,0x60,0x01,
0x00,0x00,0x00,0xf0,0x80,0x19,0xb8,0x06,0x2c,0x00,0x00,0x00,
0x00,0x1e,0xd4,0x40,0x15,0x54,0xc1,0x14,0x5c,0x83,0xf4,0x1a,
0x85,0x99,0x05,0x77,0xdf,0xf4,0xf3,0xa8,0x81,0x2a,0xa8,0x82,
0x29,0xb8,0x06,0xe9,0x35,0x0a,0x33,0xab,0x99,0xe9,0x43,0xf6,
0x02,0xd0,0x0d,0xdd,0x00,0x00,0x00,0x00,0x00,0x40,0x37,0x74,
0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x67,0x41,0x0d,0x00,
0x00,0x00,0x00,0x00,0x70,0x16,0xd4,0x00,0x00,0x00,0x00,0x00,
0x80,0x39,0x07,0x6b,0x26,0x09,0x05,0x00,0x00,0x00,0x00,0x98,
0x73,0xb0,0x66,0x92,0x50,0x00,0x00,0x00,0x00,0x00,0xc0,0x54,
0x93,0x75,0xf6,0x01,0x15,0x00,0x00,0x00,0x00,0x30,0xd5,0x64,
0x9d,0x7d,0x40,0x05,0x00,0x00,0x00,0xe8,0x5d,0x39,0x38,0x3e,
0x01,0x00,0x00,0x00,0x00,0xa0,0x77,0xe5,0xe0,0xf8,0x04,0x00,
0x00,0x00,0x00,0x80,0xe2,0xe9,0xf2,0xf4,0x7d,0xeb,0xfb,0x56,
0x1e,0x85,0x82,0x5b,0x37,0xdc,0x0f,0x54,0x01,0x08,0x3b,0xc9,
0xea,0x99,0xe4,0x1c,0x95,0x9d,0xb0,0x2b,0x61,0x24,0x30,0x1b,
0xaa,0x00,0x00,0x00,0x80,0x06,0x1e,0xa8,0x5b,0x43,0x37,0x3c,
0xb8,0x3e,0x00,0x00,0x40,0x83,0xb5,0x20,0x47,0x93,0x74,0x93,
0x2c,0x5c,0xf1,0xff,
};

BYTE code tQCFONT_4BITLUFFY[] =
{
0x0f,0x81,0x24,0xc3,0x7e,0x95,0x6a,0xdb,0x0e,0x98,0x00,0x00,
0x68,0x70,0x1a,0xce,0x81,0x73,0x90,0x5c,0x48,0x72,0x3a,0x00,
0x00,0x68,0x30,0x03,0x6b,0xc1,0x5a,0x28,0xbb,0x5d,0x98,0x01,
0x00,0x80,0x06,0x33,0xb0,0x16,0xac,0x85,0xb2,0xdb,0x85,0x19,
0x00,0x00,0x68,0x30,0x03,0x6b,0xc1,0x5a,0x28,0xbb,0x5d,0x98,
0x01,0x00,0x9b,0x26,0x25,0x57,0xb2,0x77,0x92,0xdc,0x77,0x92,
0xdc,0x77,0x92,0xec,0x3b,0x49,0xaa,0x92,0x00,0xc0,0xcd,0x85,
0x55,0xaa,0xcd,0x00,0x30,0xc0,0x40,0x2d,0x00,0xc0,0xcd,0x85,
0x55,0xaa,0xcd,0x00,0x30,0xc0,0x40,0x2d,0x00,0xc0,0xcd,0x85,
0x55,0xaa,0xcd,0x00,0x30,0xc0,0x40,0x2d,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x58,0x0d,0x00,0x00,0x00,0x00,0x00,
0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x1a,0x00,0x00,
0x00,0x00,0x00,0x00,0x3e,0x0d,0x00,0x00,0x00,0x00,0xf8,0xd8,
0xc0,0x3e,0x00,0x00,0x00,0x00,0x00,0xe8,0x1c,0x24,0x39,0x92,
0x24,0x09,0x00,0x00,0x00,0x00,0x7c,0xdc,0xc0,0x6a,0x00,0x00,
0x00,0x00,0x00,0x7c,0xdc,0xc0,0x3e,0x00,0x00,0x00,0x00,0x20,
0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x24,0x49,0x92,0x24,
0x49,0x92,0x04,0x00,0x00,0x00,0xc8,0xed,0x02,0x00,0x00,0x00,
0x00,0x00,0x20,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x0b,
0xa7,0xf4,0x06,0x00,0x00,0x00,0x00,0x00,0x45,0xb6,0xdc,0x92,
0x24,0x49,0x02,0x00,0x00,0x00,0x00,0x1f,0x5c,0x9c,0x0d,0x00,
0x00,0x00,0x00,0x00,0x2e,0x5c,0xe5,0x6c,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x98,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x1b,
0x00,0x00,0x00,0x00,0x00,0x00,0x4c,0x01,0x00,0x00,0x00,0x00,
0x00,0xc0,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x77,0xbb,0x92,
0x9c,0x93,0x24,0xd7,0x95,0x24,0xd7,0x95,0x24,0xe7,0x4a,0x92,
0xee,0x00,0xc0,0xd9,0xc0,0x69,0x85,0x35,0x60,0xc1,0x02,0x6b,
0x41,0x0f,0x00,0x38,0x1b,0x38,0xad,0xb0,0x06,0x2c,0x58,0x60,
0x2d,0xe8,0x01,0x00,0x67,0x03,0xa7,0x15,0xd6,0x80,0x05,0x0b,
0xac,0x05,0x3d,0x00,0x00,0x00,0xb0,0x0b,0xf6,0x86,0xbd,0xdd,
0x64,0xcb,0xae,0x24,0x00,0x00,0xa0,0xc0,0x5a,0x30,0x03,0x33,
0x0e,0x86,0x55,0x00,0x00,0x00,0x05,0xd6,0x82,0x19,0x98,0x71,
0x30,0xac,0x02,0x00,0x00,0x28,0xb0,0x16,0xcc,0xc0,0x8c,0x83,
0x61,0x15,0x92,0x5c,0x27,0x49,0xae,0x2b,0x49,0xae,0x2b,0x49,
0xfa,0xe4,0xec,0x10,0x00,0x00,0x00,0xac,0x05,0xc0,0x02,0xb3,
0xdc,0x9f,0xd6,0x00,0x00,0x00,0xb0,0x16,0x00,0x0b,0xcc,0x72,
0x7f,0x5a,0x03,0x00,0x00,0xc0,0x5a,0x00,0x2c,0x30,0xcb,0xfd,
0x69,0x0d,0x00,0x00,0x20,0xbb,0x92,0x24,0x49,0x92,0x24,0x49,
0x92,0xbf,0x24,0x89,0xce,0x49,0xb8,0x24,0xb4,0x73,0x81,0x86,
0x59,0xa0,0x01,0x60,0x83,0x1e,0x0b,0x76,0x17,0xda,0x2c,0xd0,
0x30,0x0b,0x34,0x00,0x6c,0xd0,0x63,0xc1,0xee,0x42,0x9b,0x05,
0x1a,0x66,0x81,0x06,0x80,0x0d,0x7a,0x2c,0xd8,0x5d,0x68,0xb3,
0x40,0x03,0x40,0x81,0x7b,0x2b,0x12,0x21,0xb9,0x53,0x9d,0xe4,
0xee,0x4e,0xee,0x1d,0xc9,0xfd,0xd4,0x4e,0x36,0x80,0x02,0xb3,
0x14,0xda,0x81,0x8f,0xa7,0x68,0x73,0xe8,0x81,0x59,0xd7,0x29,
0x0b,0x40,0x81,0x59,0x0a,0x6d,0x60,0xe9,0x87,0x76,0x0e,0x3d,
0x30,0xeb,0x3a,0x65,0x01,0x28,0x30,0x4b,0xa1,0x0d,0x2c,0xcf,
0x43,0x3b,0x87,0x9e,0x60,0xde,0xda,0x65,0xb5,0x0d,0x07,0x4b,
0x2f,0xaa,0x3f,0x7f,0x6b,0xac,0x62,0xcf,0x34,0xde,0xa4,0x43,
0x22,0x00,0x72,0xe1,0xda,0xe1,0xa4,0xaa,0x5d,0xf7,0xe9,0xd3,
0xa9,0xeb,0xca,0xb5,0x7f,0x77,0x92,0x22,0x12,0x20,0x49,0x92,
0xb6,0xb1,0x06,0xe3,0x59,0xad,0x7a,0xce,0x1a,0xab,0x56,0xad,
0x99,0xc6,0x9b,0x74,0x00,0x92,0x24,0x69,0x1b,0xeb,0xe0,0xe3,
0x59,0xad,0xfa,0xf3,0xb7,0xc6,0xaa,0x55,0x7b,0xa6,0xf1,0x26,
0x1d,0x12,0x01,0x00,0x50,0x14,0xa7,0x3c,0x65,0x4d,0x4d,0xad,
0xbf,0x9f,0xc3,0x9a,0x49,0x9c,0x92,0x08,0x40,0x92,0x24,0x49,
0xae,0xe4,0x4a,0xee,0x2b,0x9f,0x2b,0xb5,0xaf,0x7d,0x9d,0xae,
0x7b,0x27,0xa7,0x37,0xd9,0x57,0x80,0x24,0x49,0x00,0x14,0xc5,
0x29,0x4f,0x59,0x43,0xad,0xe7,0x99,0x83,0x91,0xc8,0x06,0x24,
0x49,0x02,0xa0,0x28,0x4e,0x79,0xca,0x9a,0x9a,0x5a,0x7f,0xbf,
0x39,0xac,0x99,0x44,0xb6,0x44,0x00,0x00,0x00,0x00,0x00,0x20,
0x11,0x12,0x01,0x48,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,
0x49,0x92,0x24,0x49,0x12,0x22,0x01,0x92,0x24,0x01,0x00,0x00,
0x00,0x80,0x44,0x00,0x92,0x24,0x01,0x00,0x00,0x00,0x80,0x44,
0x48,0x04,0x00,0x00,0x80,0x5e,0x05,0xdf,0xa1,0x19,0x24,0x7f,
0x21,0x11,0x80,0x24,0x49,0x92,0x24,0x49,0x92,0xe4,0x3e,0x57,
0x92,0x74,0x27,0x77,0x9e,0x27,0x09,0x3f,0x09,0x90,0x24,0x09,
0x00,0x00,0xbd,0x0a,0xbe,0x43,0x53,0x48,0x12,0x80,0x24,0x49,
0x00,0x00,0xe8,0x55,0xf0,0x1d,0x9a,0x2f,0x92,0x84,0x44,0x00,
0x16,0x5a,0xc3,0xc7,0xaa,0xf7,0xb2,0x86,0xcf,0xfe,0x6a,0xed,
0x81,0xe7,0x17,0x91,0x44,0x00,0x8a,0xdc,0x6e,0x92,0x9d,0x52,
0x95,0xb3,0xf7,0xbd,0xaf,0xce,0x9d,0xfb,0x54,0x92,0xf4,0x88,
0x3c,0x40,0x92,0x24,0x85,0x06,0x3e,0x55,0xb5,0x2e,0x6b,0xd6,
0xac,0x3d,0x5a,0xcf,0x03,0x4f,0x22,0x02,0x24,0x49,0xb2,0xd1,
0x1a,0x3e,0xb5,0xeb,0xbd,0xac,0x59,0xf3,0xd9,0x5f,0xad,0xe7,
0x81,0x27,0x11,0x49,0x04,0x00,0x00,0x9c,0x46,0xe7,0xc2,0x95,
0x70,0x92,0xac,0xca,0x95,0x54,0xe5,0x24,0x71,0x9e,0x44,0x3f,
0x80,0x06,0x6b,0xd0,0x0a,0x0b,0xa6,0x28,0xb5,0x58,0xdb,0xc0,
0xd2,0x72,0x0f,0xa0,0xc1,0x1a,0xb4,0xc2,0x82,0x29,0x56,0xd5,
0x62,0xef,0x1a,0x58,0x5a,0xee,0x01,0x34,0x58,0x83,0x56,0x58,
0x30,0xc5,0xaa,0x5a,0xec,0x5d,0x43,0xac,0x6a,0xfa,0x9b,0xe4,
0x74,0x92,0xe4,0x4a,0x92,0x24,0x49,0x92,0xc4,0x4e,0xb2,0x49,
0x6e,0x24,0x85,0x7d,0x83,0x82,0x35,0xa0,0x00,0x06,0xd4,0x8b,
0x81,0x2e,0x58,0xf8,0x34,0xd8,0xb0,0x06,0x14,0xc0,0x80,0x7a,
0x31,0xd0,0x05,0x0b,0x9f,0x06,0x1b,0xd6,0x80,0x02,0x18,0x50,
0x2f,0x06,0xba,0x60,0xe1,0xd3,0x60,0xcb,0xbd,0x93,0xe4,0xbe,
0x93,0xe4,0xbe,0x93,0x64,0xef,0x24,0xb7,0xba,0x12,0x00,0x00,
0x00,0x33,0x00,0x0c,0x58,0x83,0xa3,0x36,0xd0,0x1b,0x00,0x00,
0x33,0x00,0x0c,0x58,0x83,0xa3,0x36,0xd0,0x1b,0x00,0x00,0x33,
0x00,0x0c,0x58,0x83,0xa3,0x36,0xd0,0x1b,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xb2,0xaf,0x00,0xc4,0x5f,0x00,0x00,0x00,
0x00,0x20,0x71,0x91,0x24,0x09,0x2c,0x00,0x00,0x00,0x00,0x40,
0xf6,0x09,0xaa,0x10,0x57,0x00,0x00,0x00,0x00,0x80,0xec,0x2b,
0xa8,0x42,0x24,0x00,0xf0,0x70,0xce,0xf3,0x07,0x7f,0x07,0x0e,
0xe1,0x10,0x09,0x40,0x24,0x1d,0x74,0x27,0x74,0x25,0xb3,0x96,
0x44,0x97,0x04,0x40,0x22,0x24,0x49,0x02,0x00,0x0d,0x2a,0x99,
0xb5,0x24,0xba,0x24,0x00,0x88,0x04,0x20,0x12,0xa0,0xc1,0xc3,
0xac,0xf7,0x0f,0xfd,0x77,0xe0,0x10,0x0e,0x91,0x00,0x44,0x02,
0xba,0x01,0x00,0x00,0x44,0x42,0x24,0x00,0x91,0x24,0x42,0x92,
0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x09,0x90,0x08,0x49,0x92,
0x00,0x80,0x86,0x24,0x49,0x92,0x24,0x49,0x92,0x04,0x20,0x12,
0x80,0x48,0x00,0x0d,0x00,0x00,0x10,0x09,0x91,0x00,0x44,0x02,
0x68,0x00,0x00,0x80,0x48,0x88,0x04,0x20,0x92,0xa4,0xb3,0x48,
0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x09,0x90,0x08,0x49,0x92,
0x00,0xc0,0xa1,0x4e,0x25,0x49,0x92,0x24,0x49,0x92,0x24,0x00,
0x91,0x00,0x44,0x02,0x1c,0xea,0x14,0x00,0x00,0x44,0x42,0x24,
0x00,0x91,0xd0,0x96,0x43,0x9d,0x02,0x00,0x80,0x48,0x88,0x04,
0x20,0x92,0x44,0x48,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,
0x01,0x12,0x21,0x49,0x12,0x00,0x00,0x92,0x24,0x49,0x92,0x24,
0x49,0x12,0x80,0x48,0x00,0x22,0x01,0x00,0x00,0x00,0x88,0x84,
0x48,0x00,0x22,0x01,0x00,0x00,0x00,0x88,0x84,0x48,0x00,0x22,
0x49,0x56,0x28,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x00,
0x89,0x90,0x24,0x09,0x00,0xec,0x86,0x24,0x49,0x92,0x24,0x49,
0x92,0x04,0x20,0x12,0x80,0x48,0x80,0xdd,0x00,0x00,0x00,0x91,
0x10,0x09,0x40,0x24,0x2c,0xec,0x06,0x00,0x00,0x88,0x84,0x48,
0x00,0x22,0x49,0x84,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,
0x12,0x20,0x11,0x92,0x24,0x01,0x00,0x14,0x49,0x92,0x24,0x49,
0x92,0x24,0x09,0x40,0x24,0x00,0x91,0x00,0x28,0x00,0x00,0x20,
0x12,0x22,0x01,0x88,0x04,0x40,0xb1,0xf7,0xcd,0xb3,0x14,0x6b,
0xc3,0x82,0x6c,0x22,0x01,0x88,0x64,0x13,0x8a,0x64,0xf7,0x9a,
0xa4,0x4b,0x25,0x0f,0x92,0x02,0x12,0x21,0x49,0x12,0x60,0x81,
0x05,0xab,0xd7,0x24,0x5d,0x2a,0x79,0x90,0x14,0x40,0x24,0x00,
0x91,0x2c,0xb0,0x60,0xfd,0xd6,0xf0,0x2c,0xc5,0xbb,0x61,0x41,
0x36,0x91,0x00,0x44,0xb2,0xc0,0x82,0x05,0x00,0x00,0xa0,0x23,
0x01,0xd8,0x12,0x00,0x00,0x00,0x00,0x48,0x84,0x24,0x49,0x38,
0x00,0x00,0x00,0x00,0x00,0x1d,0x09,0xc0,0x4f,0x02,0x00,0x00,
0x00,0x00,0x3a,0x12,0x80,0x9f,0x04,0x00,0x00,0x00,0x00,0x00,
0xd4,0x06,0x05,0x00,0x00,0x00,0x00,0x50,0xa0,0x0a,0x00,0x00,
0x00,0x00,0x00,0x28,0x50,0x05,0x0a,0x00,0x00,0x00,0x00,0xa0,
0x40,0x6d,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x42,
0x4b,0xe0,0xba,0xe0,0x1c,0xe8,0x03,0x00,0x00,0x80,0x86,0x56,
0x05,0xab,0xc0,0x02,0x03,0x1a,0x00,0x00,0x34,0xb4,0x2a,0x58,
0x05,0x16,0x18,0xd0,0x00,0x00,0xa0,0xa1,0x55,0xc1,0x2a,0xb0,
0xc0,0x80,0x06,0x00,0x00,0xa9,0x9d,0xe4,0x26,0xc9,0x4d,0x72,
0x6f,0x92,0xbd,0x49,0xf6,0x4d,0xb2,0xc3,0x75,0xdd,0x29,0x7d,
0x72,0x65,0x13,0x7b,0xd0,0x0a,0x03,0x06,0x66,0x60,0x06,0xa6,
0x59,0xd5,0x56,0xcd,0xa8,0x1e,0xcd,0x1e,0xb4,0xc2,0x80,0x81,
0x19,0x98,0x81,0x69,0x56,0xb5,0x55,0x33,0xaa,0x47,0xb3,0x07,
0xad,0x30,0x60,0x60,0x06,0x66,0x60,0x9a,0x55,0x6d,0xd5,0x8c,
0xea,0xd1,0xf4,0x05,0x00,0x00,0x00,0x00,0xd0,0x20,0x07,0x66,
0x83,0x06,0x00,0x00,0x00,0xa0,0x1b,0x6a,0x15,0x66,0x83,0x06,
0x00,0x00,0x00,0xa0,0x1b,0x6a,0x15,0x66,0x83,0x06,0x00,0x00,
0x00,0xa0,0x1b,0x6a,0x15,0x49,0x92,0x24,0x49,0x92,0x3b,0xd7,
0x95,0xdc,0xf7,0x39,0xc9,0x7d,0x9f,0x93,0xdc,0xf7,0x39,0x49,
0xee,0xeb,0x4a,0x92,0x24,0x49,0x92,0x00,0x28,0x74,0x2f,0xb0,
0x16,0x66,0xa1,0xad,0x45,0x77,0x01,0x00,0x00,0x0a,0xdd,0x0b,
0xac,0x85,0x59,0x68,0x6b,0xd1,0x5d,0x00,0x00,0x80,0x42,0xf7,
0x02,0x6b,0x61,0x16,0xda,0x5a,0x74,0x17,0x00,0x80,0x7d,0x83,
0x02,0x00,0x00,0x00,0xa0,0x0a,0x72,0xc3,0x3a,0x50,0x05,0x00,
0x00,0x00,0xc0,0x2a,0x45,0x0f,0xac,0x03,0x55,0x00,0x00,0x00,
0x00,0xac,0x52,0xf4,0xc0,0x3a,0x50,0x05,0x00,0x00,0x00,0xc0,
0x2a,0x45,0x8f,0x24,0x7d,0x72,0x25,0xe4,0x24,0x9c,0x93,0x70,
0x4e,0xc2,0x39,0x09,0xe7,0xba,0xc3,0x49,0x6d,0x72,0x73,0x75,
0xd0,0x1f,0xa0,0x16,0xac,0x81,0x19,0x98,0x05,0x63,0x9a,0x65,
0x4d,0xab,0x56,0x7b,0xa0,0x3f,0x40,0x2d,0x58,0x03,0x33,0x30,
0x0b,0xc6,0x34,0xcb,0x9a,0x56,0xad,0xf6,0x40,0x7f,0x80,0x5a,
0xb0,0x06,0x66,0x60,0x16,0x8c,0x69,0x96,0x35,0xad,0x5a,0xed,
0x51,0x24,0x85,0x04,0xee,0xc0,0xbe,0xa1,0x36,0x28,0x00,0x00,
0x14,0x28,0x28,0x74,0xc3,0x0c,0x2c,0x50,0x05,0x00,0x80,0x02,
0x05,0x85,0x6e,0x98,0x81,0x05,0xaa,0x00,0x00,0x50,0xa0,0xa0,
0xd0,0x0d,0x33,0xb0,0x40,0x15,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x34,0x00,0x00,0x00,0x00,0x00,0x00,0x98,0x06,0x00,
0x00,0x00,0x00,0x00,0x80,0x69,0x00,0x00,0x00,0x00,0x00,0x00,
0x98,0x46,0x27,0x1c,0x27,0xa0,0x01,0x74,0x37,0x3e,0xe7,0x30,
0x77,0x9f,0x76,0xef,0xe5,0x3a,0x7b,0xe7,0x93,0xec,0x81,0x65,
0x15,0xcd,0x81,0x86,0x9e,0xc1,0x6f,0xe1,0xcc,0xac,0xe9,0x9a,
0xdd,0xb5,0x46,0x3d,0xcc,0xc0,0xb2,0x8a,0xe6,0x40,0x43,0xcf,
0xe0,0xb7,0x70,0x66,0xd6,0x74,0xcd,0xee,0x5a,0xa3,0x1e,0x66,
0x60,0x59,0x45,0x73,0xa0,0xa1,0x67,0xf0,0x5b,0x38,0x33,0x6b,
0xba,0x66,0x77,0xad,0x51,0x0f,0x93,0x24,0xfb,0x4a,0x92,0x24,
0xc9,0x95,0x9c,0x44,0x87,0x2b,0x65,0x5f,0x92,0xbd,0x93,0x64,
0xef,0xe4,0x64,0x4b,0x0a,0xb8,0x6e,0x00,0x9b,0x8d,0xa3,0xa4,
0x3f,0xe6,0x0f,0xa3,0x8a,0x59,0x7c,0x6a,0x75,0x59,0x7e,0x70,
0xdd,0x00,0x36,0x1b,0x47,0x49,0x7f,0xcc,0x1f,0x46,0x15,0xb3,
0xf8,0xd4,0xea,0xb2,0xfc,0xe0,0xba,0x01,0x6c,0x36,0x8e,0x92,
0xfe,0x98,0x3f,0x8c,0x2a,0x66,0xf1,0xa9,0xd5,0x65,0xf9,0x39,
0xd7,0x1d,0xce,0xb9,0x6f,0x72,0x72,0x4b,0x92,0x84,0x48,0x80,
0x27,0x49,0x9e,0x27,0x49,0x9e,0x27,0x49,0x1e,0xab,0xa6,0x1f,
0x33,0x33,0x52,0x4b,0x03,0x72,0xbb,0xa8,0x08,0x2f,0xbc,0x2f,
0xbc,0x2f,0xbc,0x56,0x4d,0x3f,0x66,0x66,0xa4,0x96,0x06,0xe4,
0x76,0x51,0x11,0x5e,0x78,0x5f,0x78,0x5f,0x78,0xad,0x9a,0x7e,
0xcc,0xcc,0x48,0x2d,0x0d,0xc8,0xed,0xa2,0x22,0xbc,0xf0,0xbe,
0xf0,0xbe,0xf0,0x26,0x49,0x92,0x24,0x49,0xee,0x24,0xd9,0x2a,
0x89,0xb4,0xed,0x4a,0x6e,0xd7,0x95,0xdc,0xf7,0x75,0xee,0xdc,
0xf7,0xa5,0xe5,0x3e,0x84,0x03,0x68,0x38,0x36,0xba,0x8e,0x28,
0x6e,0x7b,0x61,0xac,0xa3,0x7b,0xcd,0xa9,0xee,0x97,0x70,0x00,
0x0d,0xc7,0x46,0xd7,0x11,0xc5,0x6d,0x2f,0x8c,0x75,0x74,0xaf,
0x39,0xd5,0xfd,0x12,0x0e,0xa0,0xe1,0xd8,0xe8,0x3a,0xa2,0xb8,
0xed,0x85,0xb1,0x8e,0xee,0x35,0xa7,0xba,0xdf,0x22,0xd9,0xb8,
0x03,0x0a,0x80,0x2a,0x37,0xbb,0xea,0x2a,0x7b,0x5f,0xd7,0xbd,
0xd5,0x75,0x92,0x7b,0xce,0x82,0xc1,0x28,0xd8,0x80,0xa2,0x1f,
0x5f,0xd6,0x5a,0x55,0xc6,0xb3,0x66,0xd9,0x96,0xee,0x6b,0x2d,
0x18,0x8c,0x82,0x0d,0x28,0xfa,0xf1,0x65,0xad,0x55,0x65,0x3c,
0x6b,0x96,0x6d,0xe9,0xbe,0xd6,0x82,0xc1,0x28,0xd8,0x80,0xa2,
0x1f,0x5f,0xd6,0x5a,0x55,0xc6,0xb3,0x66,0xd9,0x96,0xee,0x6b,
0x01,0x00,0x00,0x00,0x00,0x00,0xa0,0x00,0x00,0x00,0x00,0x00,
0x00,0xc0,0x2e,0x00,0x00,0x00,0x00,0x00,0x00,0xd8,0x05,0x00,
0x00,0x00,0x00,0x00,0x00,0xbb,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xc0,0x29,0x48,0xee,0x23,0x49,0xae,0x93,
0x24,0xd7,0x95,0x24,0xd7,0x95,0x24,0xd7,0x95,0x24,0x7d,0x02,
0x00,0xd9,0xc0,0x99,0x06,0x0b,0xaa,0xa0,0x0a,0x16,0xe8,0x01,
0x00,0xd9,0xc0,0x99,0x06,0x0b,0xaa,0xa0,0x0a,0x16,0xe8,0x01,
0x00,0xd9,0xc0,0x99,0x06,0x0b,0xaa,0xa0,0x0a,0x16,0xe8,0x21,
0x17,0x4e,0x42,0x27,0xe1,0x4a,0x72,0x3a,0x49,0x92,0x24,0x49,
0x92,0x3b,0x49,0x52,0x3b,0x49,0x4a,0x12,0xb5,0x30,0xd0,0x05,
0x0b,0xf7,0x01,0x00,0xa6,0xa1,0x16,0xac,0x82,0x5a,0x18,0xe8,
0x82,0x85,0xfb,0x00,0x00,0xd3,0x50,0x0b,0x56,0x41,0x2d,0x0c,
0x74,0xc1,0xc2,0x7d,0x00,0x80,0x69,0xa8,0x05,0xab,0xb0,0x93,
0x64,0xef,0x93,0x64,0x97,0x4e,0x76,0x65,0x27,0x25,0xb9,0x43,
0x52,0x9b,0xeb,0x82,0x73,0x41,0x1f,0x2c,0xc5,0x5a,0xab,0x58,
0x6f,0x1d,0xd6,0xdb,0x1f,0x5e,0x9c,0x7e,0x54,0xd5,0xa2,0x0a,
0xd6,0x82,0x81,0xa5,0x58,0x6b,0x15,0xeb,0xad,0xc3,0x7a,0xfb,
0xc3,0x8b,0xd3,0x8f,0xaa,0x5a,0x54,0xc1,0x5a,0x30,0xb0,0x14,
0x6b,0xad,0x62,0xbd,0x75,0x58,0x6f,0x7f,0x78,0x71,0xfa,0x51,
0x55,0x8b,0x2a,0x58,0x0b,0x06,0x8a,0xc4,0x93,0x3b,0x79,0x3a,
0xb9,0xf2,0x74,0xa2,0x9b,0x64,0xcb,0x2d,0xb9,0x93,0x24,0x49,
0x92,0x24,0x49,0x92,0x76,0x74,0x95,0x8b,0xfe,0xb2,0x7d,0x87,
0x3a,0xdf,0x3a,0xbb,0x3f,0xed,0x2a,0x0e,0x00,0x00,0xed,0xe8,
0x2a,0x17,0xfd,0x65,0xfb,0x0e,0x75,0xbe,0x75,0x76,0x7f,0xda,
0x55,0x1c,0x00,0x00,0xda,0xd1,0x55,0x2e,0xfa,0xcb,0xf6,0x1d,
0xea,0x7c,0xeb,0xec,0xfe,0xb4,0xab,0x38,0x00,0x00,0x10,0x79,
0x9e,0x08,0x4f,0x92,0x3c,0x4f,0x92,0x3c,0x4f,0x72,0xe5,0x01,
0x92,0x24,0x49,0x92,0x24,0x49,0x12,0x22,0xbf,0x9f,0xcb,0xed,
0x85,0xf7,0x85,0xf7,0xbd,0xdc,0x5e,0xc7,0x06,0x00,0x00,0x22,
0xbf,0x9f,0xcb,0xed,0x85,0xf7,0x85,0xf7,0xbd,0xdc,0x5e,0xc7,
0x06,0x00,0x00,0x22,0xbf,0x9f,0xcb,0xed,0x85,0xf7,0x85,0xf7,
0xbd,0xdc,0x5e,0xc7,0x06,0x00,0x80,0x93,0x0b,0x27,0xc9,0x75,
0x3a,0x49,0xba,0xec,0xe4,0x71,0xb5,0x48,0x72,0x39,0x49,0x92,
0x24,0x49,0x92,0x24,0xc9,0xd8,0x76,0x7f,0x71,0xcf,0xb7,0xf1,
0x7d,0xea,0xc3,0xd7,0x3e,0xbb,0x0b,0x71,0x03,0x00,0x30,0xb6,
0xdd,0x5f,0xdc,0xf3,0x6d,0x7c,0x9f,0xfa,0xf0,0xb5,0xcf,0xee,
0x42,0xdc,0x00,0x00,0x8c,0x6d,0xf7,0x17,0xf7,0x7c,0x1b,0xdf,
0xa7,0x3e,0x7c,0xed,0xb3,0xbb,0x10,0x37,0x00,0x00,0x27,0x49,
0xce,0x49,0xee,0x9c,0x93,0xd8,0xa7,0x93,0xab,0x8f,0x2b,0x09,
0x7d,0x12,0xb8,0x6f,0xd8,0x37,0xec,0x0d,0xdd,0x6b,0xe8,0x9e,
0xa1,0x3e,0xf3,0x65,0x9f,0xaf,0x42,0x9b,0xd5,0x8d,0xee,0x86,
0x19,0x58,0xa0,0x7b,0x0d,0xdd,0x33,0xd4,0x67,0xbe,0xec,0xf3,
0x55,0x68,0xb3,0xba,0xd1,0xdd,0x30,0x03,0x0b,0x74,0xaf,0xa1,
0x7b,0x86,0xfa,0xcc,0x97,0x7d,0xbe,0x0a,0x6d,0x56,0x37,0xba,
0x1b,0x66,0x60,0x81,0x7b,0x2b,0x12,0x37,0xc9,0xce,0x96,0x24,
0x49,0x92,0x24,0x49,0x92,0x5c,0x49,0x92,0x3e,0x49,0x72,0x3a,
0xe8,0xb1,0xa0,0x1a,0xc6,0x5b,0x60,0x00,0xa0,0xc0,0x2c,0x98,
0x86,0x1e,0x0b,0xaa,0x61,0xbc,0x05,0x06,0x00,0x0a,0xcc,0x82,
0x69,0xe8,0xb1,0xa0,0x1a,0xc6,0x5b,0x60,0x00,0xa0,0xc0,0x2c,
0x98,0x06,0x00,0x40,0x4a,0xae,0x64,0xef,0x24,0xb9,0xef,0x24,
0xb9,0xef,0x24,0xd9,0x77,0x92,0xd4,0x4e,0x02,0x00,0x37,0x07,
0xab,0xec,0x36,0x00,0xd0,0x30,0x03,0xb5,0x00,0x00,0x37,0x07,
0xab,0xec,0x36,0x00,0xd0,0x30,0x03,0xb5,0x00,0x00,0x37,0x07,
0xab,0xec,0x36,0x00,0xd0,0x30,0x03,0xb5,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xe0,0x0a,0x97,0xeb,0x82,0xeb,0x82,0x3e,0xa0,0x01,
0x00,0x00,0x60,0x15,0x01,0x2c,0x30,0x0b,0x34,0x00,0x00,0x00,
0xac,0x22,0x80,0x05,0x66,0x81,0x06,0x00,0x00,0x80,0x55,0x04,
0xb0,0xc0,0x2c,0xd0,0x00,0x00,0x00,0xc8,0xde,0x49,0xb2,0x77,
0x92,0xec,0x9d,0x24,0xb5,0x93,0x6c,0xae,0x04,0x00,0x00,0xc0,
0x2c,0x98,0x01,0x03,0xb5,0xf0,0x51,0x5b,0x03,0x00,0x00,0x98,
0x05,0x33,0x60,0xa0,0x16,0x3e,0x6a,0x6b,0x00,0x00,0x00,0xb3,
0x60,0x06,0x0c,0xd4,0xc2,0x47,0x6d,0x0d,0x00,0x00,0x40,0x03,
0x00,0x00,0x00,0x00,0x00,0x40,0x37,0x00,0x00,0x00,0x00,0x00,
0x00,0x74,0x03,0x00,0x00,0x00,0x00,0x00,0x40,0x37,0x00,0x00,
0x00,0x00,0x00,0x00,0x92,0x24,0x49,0x72,0xae,0x24,0xd1,0x91,
0x70,0x68,0x00,0x00,0x00,0x00,0x58,0xa5,0xe8,0xd1,0x85,0xc5,
0x05,0x00,0x00,0x00,0x00,0xab,0x14,0x3d,0xba,0xb0,0xb8,0x00,
0x00,0x00,0x00,0x60,0x95,0xa2,0x47,0x17,0x16,0x17,0x00,0x00,
0x00,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x88,0x04,
0x00,0x00,0x00,0x00,0x00,0x20,0xdb,0x29,0x00,0x00,0x00,0x00,
0x00,0x00,0xd9,0x4e,0x01,0x00,0x00,0x00,0x00,0x00,0xc8,0x76,
0x0a,0x00,0x00,0x40,0x92,0x24,0xb9,0xef,0x24,0x51,0x49,0x90,
0xdc,0x50,0x00,0x00,0x00,0x00,0xd3,0xe8,0x5a,0x28,0xda,0xc0,
0x0d,0x00,0x00,0x00,0x30,0x8d,0xae,0x85,0xa2,0x0d,0xdc,0x00,
0x00,0x00,0x00,0xd3,0xe8,0x5a,0x28,0xda,0xc0,0x0d,0x00,0x00,
0x00,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0xaa,0x00,0x00,0x00,
0x00,0x00,0x00,0xa0,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0xaa,
0x00,0x00,0x00,0x00,0x00,0x00,0x24,0xb9,0x4e,0x92,0x5c,0x57,
0x92,0x5c,0x57,0x92,0xf4,0xc9,0x75,0x47,0x07,0x00,0x00,0x00,
0x6b,0xc1,0x5a,0xb0,0x16,0xcc,0xb2,0x0f,0x8d,0xa2,0x01,0x00,
0xc0,0x5a,0xb0,0x16,0xac,0x05,0xb3,0xec,0x43,0xa3,0x68,0x00,
0x00,0xb0,0x16,0xac,0x05,0x6b,0xc1,0x2c,0xfb,0xd0,0x28,0x1a,
0x00,0x00,0xec,0xdc,0xd8,0x1b,0xf6,0x86,0xda,0x00,0x00,0x00,
0x00,0xcc,0x09,0x66,0x60,0x06,0xd6,0x02,0x05,0x00,0x00,0x00,
0x73,0x82,0x19,0x98,0x81,0xb5,0x40,0x01,0x00,0x00,0xc0,0x9c,
0x60,0x06,0x66,0x60,0x2d,0x50,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xfe,0xff,
};

BYTE code tQCFONT_24_36_1BIT[] =
{
0x03,0xc1,0x8f,0x96,0xb7,0xed,0x24,0x5a,0x00,0x9b,0xc0,0x02,
0x7b,0xa6,0x7b,0xab,0x4a,0xa8,0x4a,0xa8,0x4a,0xec,0x99,0xee,
0x0d,0x16,0x00,0x1c,0x70,0xd0,0xcf,0x81,0x73,0xe0,0x1c,0x38,
0x07,0x0e,0xa3,0x17,0x00,0x2c,0xa0,0x26,0xbd,0x7b,0x4a,0x1c,
0xc8,0x94,0x56,0x3d,0x95,0x60,0x64,0x01,0xc0,0x02,0x6a,0xd2,
0xbb,0xa7,0xd0,0x83,0xa5,0x2a,0xec,0xa9,0x0e,0xb0,0x00,0xe0,
0x06,0x0b,0xd6,0x45,0xf7,0x15,0x92,0xac,0x72,0x9f,0x04,0x42,
0xb1,0x00,0x60,0x95,0x66,0xe8,0x9e,0x45,0xf7,0xa8,0xd1,0x5b,
0x15,0xf6,0x54,0x07,0x58,0x00,0xb0,0x80,0x9a,0xf4,0x5e,0x24,
0xd4,0x24,0x5b,0x55,0x62,0x4f,0x75,0x80,0x05,0x00,0xab,0x34,
0xaa,0xd2,0xd3,0x33,0xd2,0x81,0x1c,0xc8,0x81,0x03,0x0e,0x00,
0x2c,0xa0,0x26,0xbd,0xf7,0x54,0xc7,0x1e,0x6d,0xa9,0x4a,0xec,
0xa9,0x0e,0xb0,0x00,0x60,0x01,0x35,0xe9,0xad,0x2a,0xb1,0xab,
0x3a,0x54,0xb1,0xf6,0x54,0x07,0x58,0xc0,0xff,
};

BYTE code tQCFONT_24_36_2BIT[] =
{
0x0f,0x36,0xc8,0x1e,0xd2,0x45,0x79,0xab,0x00,0x7c,0x40,0x46,
0x50,0x5d,0x65,0xaf,0x55,0xb5,0xf7,0x5a,0x55,0x61,0x55,0x6d,
0x5d,0x55,0x92,0x49,0x92,0x24,0x49,0x92,0x24,0x44,0x02,0x00,
0x00,0x00,0x24,0x42,0x92,0x24,0x40,0x96,0xa0,0xa7,0x8a,0xea,
0x2a,0xaa,0xaa,0xe8,0xaa,0x62,0xba,0x4a,0xb2,0x92,0x24,0x49,
0x92,0x24,0x09,0x91,0x00,0x00,0x00,0x00,0x89,0x90,0x24,0x09,
0x90,0x11,0x54,0x57,0xd9,0x6b,0x55,0xed,0xbd,0x56,0x55,0x58,
0x55,0x1b,0x55,0x12,0xc9,0x24,0x49,0x92,0x24,0x09,0x91,0x00,
0x00,0x00,0x00,0x89,0x90,0x24,0x09,0x90,0xb1,0xd1,0xd3,0x05,
0xd3,0x2a,0x66,0xe8,0xee,0xe1,0x74,0xb5,0xe4,0x64,0x27,0x49,
0x92,0x24,0x49,0x88,0x04,0x00,0x00,0x00,0x48,0x84,0x24,0x49,
0xfe,0xff,
};

BYTE code tQCFONT_24_36_4BIT[] =
{
0x0f,0x3e,0x7c,0x6d,0x18,0xba,0x24,0x59,0x00,0xe1,0x66,0xba,
0x25,0x93,0xb6,0x67,0xba,0xf7,0x9e,0xe9,0xde,0x7b,0xa6,0x7b,
0xef,0x99,0xee,0xbd,0x67,0xba,0xb7,0x49,0x27,0x66,0xba,0xa1,
0x1b,0xba,0xa1,0x1b,0xba,0xa1,0x1b,0xba,0xa1,0x1b,0xba,0xa1,
0x9b,0x19,0x98,0x81,0x19,0x98,0x81,0x19,0x98,0x81,0x19,0x98,
0x81,0x19,0x98,0xe9,0x66,0xa6,0x9b,0x99,0x6e,0x66,0xba,0x99,
0xe9,0x66,0xa6,0x9b,0x99,0x6e,0x66,0xba,0x99,0xe9,0x86,0xb5,
0x64,0x59,0x4b,0xb1,0x56,0x15,0x6b,0x55,0xb1,0x56,0x15,0x6b,
0x55,0x91,0x14,0xd6,0x69,0xac,0x45,0x15,0x54,0x41,0x15,0x54,
0x41,0x15,0x54,0x41,0x15,0x54,0x41,0x15,0xb0,0x16,0xac,0x05,
0x6b,0xc1,0x5a,0xb0,0x16,0xac,0x05,0x6b,0xc1,0x5a,0xb0,0x16,
0x55,0x50,0x05,0x55,0x50,0x05,0x55,0x50,0x05,0x55,0x50,0x05,
0x55,0x00,0x12,0xe1,0xba,0x57,0x95,0x4d,0x55,0x3d,0x54,0xc5,
0xba,0xab,0x2e,0x7b,0x55,0x21,0x72,0x80,0x24,0x49,0x88,0x04,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x21,
0x49,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x49,0x92,0x25,
0x49,0x50,0x05,0x55,0x50,0xc5,0x56,0xc5,0xda,0x55,0x58,0x12,
0x20,0x49,0x12,0x22,0x01,0x00,0x00,0x00,0x00,0x20,0x49,0x12,
0x22,0x01,0x00,0x00,0x00,0x12,0x21,0x49,0x12,0x00,0x00,0x00,
0x00,0x00,0x12,0x21,0x49,0x92,0xff,
};

code BYTE *tQCOSD_VLC_TABLE[] =
{
    tQCDRAW_MAP,                      tQCFONT_GLOBAL,
    tQCFONT_2BITBROOK,                tQCFONT_4BITLUFFY,
    tQCFONT_24_36_1BIT,               tQCFONT_24_36_2BIT,
    tQCFONT_24_36_4BIT,
};

BYTE code tQCICON_1BIT[] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, _END_,
};

BYTE code tQCICON_1BIT_BOARD_SHADOW[] =
{
    0x00, 0x01, _NEXT_,
    0x00, 0x01, 0x02, _NEXT_,
    0x00, 0x01, 0x02, 0x03, _NEXT_,
    0x00, 0x01, 0x02, 0x03, 0x04, _NEXT_,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, _END_,
};

BYTE code tQCICON_2BIT[] =
{
    ICON_2BIT(0x00), ICON_2BIT(0x01), ICON_2BIT(0x02), ICON_2BIT(0x03), ICON_2BIT(0x04), ICON_2BIT(0x05), ICON_2BIT(0x06), ICON_2BIT(0x07), _NEXT_,
    ICON_2BIT(0x08), ICON_2BIT(0x09), ICON_2BIT(0x0A), ICON_2BIT(0x0B), ICON_2BIT(0x0C), ICON_2BIT(0x0D), ICON_2BIT(0x0E), ICON_2BIT(0x0F), _NEXT_,
    ICON_2BIT(0x10), ICON_2BIT(0x11), ICON_2BIT(0x12), ICON_2BIT(0x13), ICON_2BIT(0x14), ICON_2BIT(0x15), ICON_2BIT(0x16), ICON_2BIT(0x17), _NEXT_,
    ICON_2BIT(0x18), ICON_2BIT(0x19), ICON_2BIT(0x1A), ICON_2BIT(0x1B), ICON_2BIT(0x1C), ICON_2BIT(0x1D), ICON_2BIT(0x1E), ICON_2BIT(0x1F), _NEXT_,
    ICON_2BIT(0x20), ICON_2BIT(0x21), ICON_2BIT(0x22), ICON_2BIT(0x23), ICON_2BIT(0x24), ICON_2BIT(0x25), ICON_2BIT(0x26), ICON_2BIT(0x27), _NEXT_,
    ICON_2BIT(0x28), ICON_2BIT(0x29), ICON_2BIT(0x2A), ICON_2BIT(0x2B), ICON_2BIT(0x2C), ICON_2BIT(0x2D), ICON_2BIT(0x2E), ICON_2BIT(0x2F), _END_,
};

BYTE code tQCICON_4BIT[] =
{
    ICON_4BIT(0x00), ICON_4BIT(0x01), ICON_4BIT(0x02), ICON_4BIT(0x03), ICON_4BIT(0x04), ICON_4BIT(0x05), ICON_4BIT(0x06), ICON_4BIT(0x07), ICON_4BIT(0x08), ICON_4BIT(0x09), ICON_4BIT(0x0A), _NEXT_,
    ICON_4BIT(0x0B), ICON_4BIT(0x0C), ICON_4BIT(0x0D), ICON_4BIT(0x0E), ICON_4BIT(0x0F), ICON_4BIT(0x10), ICON_4BIT(0x11), ICON_4BIT(0x12), ICON_4BIT(0x13), ICON_4BIT(0x14), ICON_4BIT(0x15), _NEXT_,
    ICON_4BIT(0x16), ICON_4BIT(0x17), ICON_4BIT(0x18), ICON_4BIT(0x19), ICON_4BIT(0x1A), ICON_4BIT(0x1B), ICON_4BIT(0x1C), ICON_4BIT(0x1D), ICON_4BIT(0x1E), ICON_4BIT(0x1F), ICON_4BIT(0x20), _NEXT_,
    ICON_4BIT(0x21), ICON_4BIT(0x22), ICON_4BIT(0x23), ICON_4BIT(0x24), ICON_4BIT(0x25), ICON_4BIT(0x26), ICON_4BIT(0x27), ICON_4BIT(0x28), ICON_4BIT(0x29), ICON_4BIT(0x2A), ICON_4BIT(0x2B), _NEXT_,
    ICON_4BIT(0x2C), ICON_4BIT(0x2D), ICON_4BIT(0x2E), ICON_4BIT(0x2F), ICON_4BIT(0x30), ICON_4BIT(0x31), ICON_4BIT(0x32), ICON_4BIT(0x33), ICON_4BIT(0x34), ICON_4BIT(0x35), ICON_4BIT(0x36), _NEXT_,
    ICON_4BIT(0x37), ICON_4BIT(0x38), ICON_4BIT(0x39), ICON_4BIT(0x3A), ICON_4BIT(0x3B), ICON_4BIT(0x3C), ICON_4BIT(0x3D), ICON_4BIT(0x3E), ICON_4BIT(0x3F), ICON_4BIT(0x40), ICON_4BIT(0x41), _NEXT_,
    ICON_4BIT(0x42), ICON_4BIT(0x43), ICON_4BIT(0x44), ICON_4BIT(0x45), ICON_4BIT(0x46), ICON_4BIT(0x47), ICON_4BIT(0x48), ICON_4BIT(0x49), ICON_4BIT(0x4A), ICON_4BIT(0x4B), ICON_4BIT(0x4C), _END_,
};

code BYTE *tQCICON_TABLE[] =
{
    tQCICON_1BIT,             tQCICON_1BIT_BOARD_SHADOW,
    tQCICON_2BIT,             tQCICON_4BIT,
};

BYTE code tQCClearTableData[] =
{
    _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
    _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
    _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
    _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
    _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
    _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
};

//--------------------------------------------------
// Description  : Load OSD 64 Palette table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE code tPALETTE_QC[] =
{
    0xFF, 0x80, 0x80,
    0xFF, 0xFF, 0x80,
    0x80, 0xFF, 0x80,
    0x00, 0xFF, 0x80,
    0x80, 0xFF, 0xFF,
    0x00, 0x80, 0xFF,
    0xFF, 0x80, 0xC0,
    0xFF, 0x80, 0xFF,

    0xFF, 0x00, 0xFF,
    0x80, 0x80, 0xC0,
    0x00, 0x80, 0xC0,
    0x00, 0xFF, 0xFF,
    0x00, 0xFF, 0x40,
    0x80, 0xFF, 0x00,
    0xFF, 0xFF, 0x00,
    0xFF, 0x00, 0x00,

    0x80, 0x40, 0x40,
    0xFF, 0x80, 0x40,
    0x00, 0xFF, 0x00,
    0x00, 0x80, 0x80,
    0x00, 0x40, 0x80,
    0x80, 0x80, 0xFF,
    0x80, 0x00, 0x40,
    0xFF, 0x00, 0x80,

    0x80, 0x00, 0xFF,
    0x80, 0x00, 0x80,
    0x00, 0x00, 0xA0,
    0x00, 0x00, 0xFF,
    0x00, 0x80, 0x40,
    0x00, 0x80, 0x00,
    0xFF, 0x80, 0x00,
    0x80, 0x00, 0x00,

    0x40, 0x00, 0x00,
    0x80, 0x40, 0x00,
    0x00, 0x40, 0x00,
    0x00, 0x40, 0x40,
    0x00, 0x00, 0x80,
    0x00, 0x00, 0x40,
    0x40, 0x00, 0x40,
    0x40, 0x00, 0x80,

    0xFF, 0xFF, 0xFF,
    0x40, 0x00, 0x40,
    0xC0, 0xC0, 0xC0,
    0x40, 0x80, 0x80,
    0x80, 0x80, 0x80,
    0x80, 0x80, 0x40,
    0x80, 0x80, 0x00,
    0x00, 0x00, 0x00,

    0xC0, 0x00, 0x40,
    0xC0, 0xFF, 0xFF,
    0xFF, 0xC0, 0xFF,
    0xFF, 0xFF, 0xC0,
    0xC0, 0xFF, 0xC0,
    0xFF, 0xC0, 0xC0,
    0x00, 0xC0, 0xC0,
    0xC0, 0xC0, 0x00,

    0xC0, 0x00, 0xC0,
    0xC0, 0xC0, 0xFF,
    0xC0, 0x80, 0xC0,
    0xC0, 0xC0, 0x80,
    0x80, 0xC0, 0xC0,
    0x40, 0x80, 0xC0,
    0x40, 0x40, 0xC0,
    0x40, 0x40, 0x40,
};

BYTE code tQCWINDOW_PRIORITY[] =
{
    _OSD_WINDOW_0,      _OSD_WINDOW_1,      _OSD_WINDOW_2,      _OSD_WINDOW_3,      _OSD_WINDOW_4,
    _OSD_WINDOW_4_1,    _OSD_WINDOW_4_2,    _OSD_WINDOW_4_3,    _OSD_WINDOW_4_4,
    _OSD_WINDOW_4_5,    _OSD_WINDOW_4_6,    _OSD_WINDOW_4_7,    _OSD_WINDOW_4_8,
    _OSD_WINDOW_5,      _OSD_WINDOW_6,      _OSD_WINDOW_7,      _OSD_WINDOW_8,      _OSD_WINDOW_9,

    // 6193
    _OSD_WINDOW_5_1,    _OSD_WINDOW_5_2,    _OSD_WINDOW_5_3,    _OSD_WINDOW_5_4,
    _OSD_WINDOW_5_5,    _OSD_WINDOW_5_6,    _OSD_WINDOW_5_7,    _OSD_WINDOW_5_8,
};

BYTE code tQCGRADIENT_POLITY[] =
{
//  R/G/B Color Gradient           R/G/B Gradient Polarity
//  R,       G,          B,        R                                      G,                                     B,
   _DISABLE, _DISABLE,  _DISABLE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,  /* Win 0 */
   _DISABLE, _DISABLE,  _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,  /* Win 5 */
   _DISABLE, _DISABLE,  _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,  /* Win 6 */
   _DISABLE, _ENABLE,   _DISABLE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,  /* Win 7 */
   _DISABLE, _ENABLE,   _DISABLE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,  /* Win 8 */
   _DISABLE, _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,  /* Win 9 */

   _DISABLE, _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
   _DISABLE, _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
   _DISABLE, _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
   _ENABLE,  _DISABLE,  _DISABLE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
   _ENABLE,  _DISABLE,  _DISABLE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
   _ENABLE,  _DISABLE,  _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,

   _ENABLE,  _DISABLE,  _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
   _ENABLE,  _DISABLE,  _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
   _ENABLE,  _DISABLE,  _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
   _ENABLE,  _ENABLE,   _DISABLE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
   _ENABLE,  _ENABLE,   _DISABLE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
   _ENABLE,  _ENABLE,   _DISABLE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,

   _ENABLE,  _ENABLE,   _DISABLE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
   _ENABLE,  _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
   _ENABLE,  _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
   _ENABLE,  _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
   _ENABLE,  _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
   _ENABLE,  _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,

   _ENABLE,  _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
   _ENABLE,  _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
   _ENABLE,  _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
   _ENABLE,  _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
   _ENABLE,  _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
   _ENABLE,  _ENABLE,   _ENABLE,  _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
};

BYTE code tQCFONT_WINDOW_PRIORITY[] =
{
    _OSD_WINDOW_2,  _OSD_WINDOW_3,  _OSD_WINDOW_4,  _OSD_WINDOW_8,  _OSD_WINDOW_9,
};

enum OSDQCFontCBody0Def
{
    _GLOBAL_FONT_END,
}; // FontCBody0

enum OSDQCFontCBody1Def
{
    U0043 = _GLOBAL_FONT_END,
    U0044,
    U004F,
    U0051,
    U0053,
}; // FontCBody1

enum OSDQCStringTextDef
{
    _OSD_TEXT_TEST,
}; // StringText

BYTE code tsOsdQCTest[] =
{
    U004F,U0053,U0044,U0051,U0043,_END_,
};

BYTE code tsFontCWidth0[] =
{
    12,
};

BYTE code tsFontCWidth1[] =
{
    9,
    8,
    9,
    10,
    8,
};

BYTE code tsFontCWidth2[] =
{
    12,
};

BYTE code tsFontCBody0[] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
}; // tsFontCBody0

BYTE code tsFontCBody1[] =
{
    0x00,0x00,0x00,0x01,0x0e,0x00,0x76,0xf3,0x08,0xcc,0x10,0x00,0xcc,0x00,0x00,0xcc,0x11,0x08,0x67,0x3f,0x80,0x10,0xe0,0x00,0x00,0x00,0x00, // U0043, 1, 1
    0x00,0x00,0x00,0x0f,0x0c,0x00,0xfc,0xe6,0x00,0xcc,0x33,0x00,0xcc,0x33,0x00,0xcc,0x33,0x00,0xcf,0x6e,0x00,0xf0,0xc0,0x00,0x00,0x00,0x00, // U0044, 1, 1
    0x00,0x00,0x00,0x03,0x0e,0x00,0x76,0xf3,0x00,0xcc,0x11,0x88,0xcc,0x11,0x88,0xcc,0x11,0x88,0x67,0x3f,0x00,0x30,0xe0,0x00,0x00,0x00,0x00, // U004F, 1, 1
    0x00,0x00,0x00,0x03,0x0e,0x00,0x76,0xf3,0x00,0xcc,0x11,0x88,0xcc,0x11,0x88,0xcc,0x1d,0x88,0x67,0x7f,0x00,0x30,0xf0,0xc8,0x00,0x00,0x00, // U0051, 1, 1
    0x00,0x00,0x00,0x03,0x0c,0x00,0x7c,0xe7,0x00,0xce,0x30,0x00,0x73,0xce,0x00,0x0c,0x73,0x00,0xe7,0x3e,0x00,0x30,0xc0,0x00,0x00,0x00,0x00, // U0053, 1, 1
}; // tsFontCBody1

BYTE code tsFontCBody2[] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
}; // tsFontCBody2

BYTE code tQC_OSD_CRC_TABLE_1[] =
{
    0x70, 0xFB, 0x8F, 0xC2, 0xBB, 0x7D, // M1
    0x82, 0xC3, 0x9E, 0x15, 0x2A, 0x74, // M2
};

BYTE code tQC_OSD_CRC_TABLE_1_1[] =
{
    0x54, 0xA0, 0x39, 0xC9, 0xEC, 0xF5, // M1
    0x6F, 0x84, 0x27, 0x2A, 0x71, 0x42, // M2
};

BYTE code tQC_OSD_CRC_TABLE_2[] =
{
    0xBC, 0x84, 0x63, 0xC9, 0x4D, 0xCE, // M1
    0x40, 0xA4, 0x5E, 0xD2, 0x2A, 0x66, // M2
};

BYTE code tQC_OSD_CRC_TABLE_2_1[] =
{
    0x1A, 0x0D, 0x13, 0x3E, 0xDB, 0x89, // M1
    0xFF, 0xE8, 0x7B, 0x44, 0xFE, 0x79, // M2
};

BYTE code tQC_OSD_CRC_TABLE_2_2[] =
{
    0xDF, 0x75, 0x09, 0x08, 0x0C, 0x7F, // M1
    0x6E, 0x1C, 0xCC, 0xEE, 0xC8, 0x04, // M2
};

BYTE code tQC_OSD_CRC_TABLE_2_3[] =
{
    0xBB, 0x7C, 0x59, 0xA3, 0x31, 0xB9, // M1
    0x24, 0x8C, 0xE9, 0xC0, 0x20, 0xC8, // M2
};

BYTE code tQC_OSD_CRC_TABLE_3[] =
{
    0x17, 0xA7, 0x1E, 0x38, 0x83, 0x3F, // M1
    0x4E, 0x62, 0xB6, 0xB7, 0x92, 0x8D, // M2
};

BYTE code tQC_OSD_CRC_TABLE_4[] =
{
    0x62, 0xAE, 0xC1, 0x9B, 0x55, 0x04, // M1
    0xCF, 0xE6, 0xB5, 0xBE, 0xE5, 0xC0, // M2
};

BYTE code tQC_OSD_CRC_TABLE_5[] =
{
    0x18, 0x89, 0xB4, 0x43, 0xE4, 0x4B, // M1
    0x83, 0x98, 0x8A, 0x47, 0xB8, 0x35, // M2
};

BYTE code tQC_OSD_CRC_TABLE_6[] =
{
    0x93, 0x59, 0xCA, 0xC9, 0xE4, 0xFC, // M1
    0x33, 0x40, 0x61, 0xDA, 0xC8, 0x86, // M2
};

BYTE code tQC_OSD_CRC_TABLE_7[] =
{
    0xB7, 0x58, 0x5D, 0x44, 0xC4, 0x82, // M1
    0xA7, 0xC5, 0xF8, 0x44, 0xC4, 0x82, // M2
};

BYTE code tQC_OSD_CRC_TABLE_8[] =
{
    0x29, 0x12, 0xF6, 0x90, 0x2C, 0xD9, // M1
    0x36, 0x58, 0xE4, 0xAC, 0x29, 0x1F, // M2
};

BYTE code tQC_OSD_CRC_TABLE_9[] =
{
    0xAE, 0x0C, 0xB8, 0xB0, 0x8D, 0x4B, // M1
    0xAA, 0x74, 0x5E, 0xFA, 0x5A, 0x43, // M2
};

BYTE code tQC_OSD_CRC_TABLE_10[] =
{
    0x02, 0x73, 0x11, 0x01, 0x8A, 0x67, // M1
    0x02, 0x73, 0x11, 0x01, 0x8A, 0x67, // M2
};

BYTE code tQC_OSD_CRC_TABLE_11[] =
{
    0xDF, 0xBB, 0x14, 0x9C, 0x41, 0x53, // M1
    0xDF, 0xBB, 0x14, 0x9C, 0x41, 0x53, // M2
};

BYTE code tQC_OSD_CRC_TABLE_12[] =
{
    0x13, 0xC6, 0x75, 0x86, 0x5F, 0x5A, // M1
    0xFF, 0x65, 0xF0, 0x3C, 0x97, 0x96, // M2
};

BYTE code tQC_OSD_CRC_TABLE_13[] =
{
    0xCB, 0x7B, 0x3E, 0x38, 0xCA, 0xDF, // M1
    0xC8, 0xDF, 0xE4, 0x38, 0xCA, 0xDF, // M2
};

BYTE code tQC_OSD_CRC_TABLE_14[] =
{
    0xEB, 0x6E, 0x1F, 0x83, 0x07, 0xF2, // M1
    0xCF, 0x5B, 0x6A, 0x83, 0x07, 0xF2, // M2
};

BYTE code tQC_OSD_CRC_TABLE_15[] =
{
    0x72, 0x30, 0x7A, 0x6F, 0x03, 0x0A, // M1
    0xF7, 0xF2, 0x09, 0x8B, 0x86, 0xCB, // M2
};

BYTE code tQC_OSD_CRC_TABLE_16[] =
{
    0x14, 0x30, 0xF2, 0xB5, 0x55, 0x24, // M1
    0x6C, 0xB9, 0xEA, 0xB5, 0x55, 0x24, // M2
};

BYTE code tQC_OSD_CRC_TABLE_17[] =
{
    0xE6, 0x57, 0x75, 0xCB, 0xDF, 0x01, // M1
    0xB2, 0x09, 0x93, 0x74, 0x31, 0x2A, // M2
};

BYTE code tQC_OSD_CRC_TABLE_18[] =
{
    0x28, 0x28, 0x82, 0xE5, 0x80, 0x9D, // M1
    0xD5, 0xBD, 0x12, 0x71, 0xAF, 0x90, // M2
};

BYTE code tQC_OSD_CRC_TABLE_19[] =
{
    0x5B, 0xA3, 0x50, 0x27, 0x50, 0x1E, // M1
    0x8F, 0xC1, 0x80, 0x52, 0x51, 0x20, // M2
};

BYTE code tQC_OSD_CRC_TABLE_20[] =
{
    0x95, 0x19, 0xCA, 0x37, 0x72, 0x75, // M1
    0x1E, 0x1E, 0x9A, 0x15, 0xE6, 0x2A, // M2
};

code BYTE *tOSD_QCTABLE_LANGUAGE_TEXT[] =
{
    tsOsdQCTest,
};    // *tOSD_TABLE_LANGUAGE_TEXT

code BYTE *tOSD_TABLE_LANGUAGE_FONT_BODY[] =
{
    tsFontCBody0,
    tsFontCBody1,
    tsFontCBody2,
};    // *tOSD_TABLE_LANGUAGE_FONT_BODY

code int tOSD_TABLE_LANGUAGE_FONT_COUNT[] =
{
    sizeof(tsFontCBody0) / 27,
    sizeof(tsFontCBody1) / 27,
    sizeof(tsFontCBody2) / 27,
};    // OSD_TABLE_LANGUAGE_FONT_COUNT

code BYTE *tOSD_TABLE_LANGUAGE_FONT_WIDTH[] =
{
    tsFontCWidth0,
    tsFontCWidth1,
    tsFontCWidth2,
};    // OSD_TABLE_LANGUAGE_FONT_WIDTH

#define _PFONT_TYPE_0                                   0
#define _PFONT_0_MIN_POS                                20 // 20 // 20
#define _PFONT_0_MAX_POS                                30 // 30 // 100

BYTE g_ucQCOSDFontPointer0 = _PFONT_0_MIN_POS;
BYTE g_ucQCOSDFontPointer0Max = _PFONT_0_MAX_POS;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerQC_OSDPrintCRC(BYTE ucFrame, BYTE ucPath, BYTE *pucCRC, BYTE ucNum);
bit ScalerQC_OSDCRCCompare(BYTE ucDomain, BYTE ucPosition, BYTE ucSourceSel, BYTE *pucCRC, BYTE ucFrameNum);

void ScalerQC_OSDWindowRoundedWin(bit bEnable);
void ScalerQC_OSDSRAMSize(bit bEnable);
void ScalerQC_OSDFont24_36(bit bEnable);
void ScalerQC_OSDScaleUp(bit bEnable, BYTE ucFactor, BYTE ucType);

void ScalerQC_OSDTablePaletteAdjust(void);
void ScalerQC_OSDRegInitial(void);
void ScalerQC_OSDFontLoadVLC(EnumOsdRotateType enumOsdRotateType);
void ScalerQC_OSDFuncApplyMap(EnumOsdRotateType enumOsdRotateType);
void ScalerQC_OSDRotateFont(BYTE *pucArray, WORD usTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType);
void ScalerQC_OSDLoadIcon(BYTE ucRow, BYTE ucCol, BYTE ucLanguage, BYTE ucIconSelect);
void ScalerQC_OSDFxLoadText(BYTE ucRow, BYTE ucCol, BYTE ucSelect, BYTE *pucArray);
void ScalerQC_OSDSRAMTestPattern(void);

void ScalerQC_OSDBlankFont(BYTE ucStatus, BYTE ucBlankLength);
void ScalerQC_OSDBlankFontCw270(BYTE ucStatus, BYTE ucBlankLength);
void ScalerQC_OSD1BitFontShrink(BYTE ucStatus, ucCharWidth);
void ScalerQC_OSD1BitColor(BYTE ucDoubleEnable);
void ScalerQC_OSD2BitFontByte1Bit7Swap(BYTE ucStatus);
void ScalerQC_OSDReference4BitBackground(BYTE ucStatus);
void ScalerQC_OSDDrawWindow(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucWindowColor, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd);
void ScalerQC_OSDWindowPriority(bit bEnable);
void ScalerQC_OSDWindowGridLine(bit bENABLE, BYTE ucStatus);
void ScalerQC_OSDSetGridLine(EnumOsdWindowsType enumOsdWindowsType, BYTE ucGridLineWidth, BYTE ucGridLineColor, bit bHorizontalEnable, bit bVerticalEnable, BYTE ucGridLineOffset, WORD usGridLinePitch, bit bGridFunctionEnable);
void ScalerQC_OSDWindowGradient(bit bEnable, BYTE ucStatus);
void ScalerQC_OSDWindowSaturatedColor(bit bEnable);
void ScalerQC_OSDWindowGradientLevelExtension(bit bEnable);
void ScalerQC_OSDSetGradient(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucWindowColor, BYTE ucGradStep, BYTE ucGradLevel, bit bPolarity_R, bit bPolarity_G, bit bPolarity_B, bit bEnable_R, bit bEnable_G, bit bEnable_B, bit bEnableSaturated, bit bEnableReversed, bit bLevelExtension, bit bGradientDirection, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd);
void ScalerQC_OSDAlphaBlendingType(bit bEnable, EnumOsdTransparencyType enumOsdTransparencyType);
void ScalerQC_OSDFuncClear(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight);
void ScalerQC_OSDWindowChessboard(bit bEnable);
void ScalerQC_OSDWindowHighlight(bit bEnable);
void ScalerQC_OSDWindowShadowBorder(bit bEnable);
void ScalerQC_OSDSetShadowBorder(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucWindowColor, BYTE ucShadowColor, BYTE ucBorderColor, BYTE ucWidth, BYTE ucHeight, BYTE ucButtonType, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd);
void ScalerQC_OSDWindow6SpecialFunction(bit bEnable, EnumOsdWindow6FunctionType enumOsdWindow6FunctionType);
void ScalerQC_OSDWindow7SpecialFunction(bit bEnable, EnumOsdWindow7FunctionType enumOsdWindow7FunctionType);
void ScalerQC_OSDWindowBorderPriority(bit bEnable, bit bBorderEnable);
void ScalerQC_OSDWindowFontPriority(bit bEnable, EnumOsdWindowPriorityType enumOsdWindowPriorityType);
void ScalerQC_OSDWindowGrayLevel(bit bEnable);
void ScalerQC_OSDWindowGradientStepExtension(bit bEnable);
void ScalerQC_OSDWindowSpecialColorMask(bit bEnable);
void ScalerQC_OSDLoadFontAddress(WORD usOffset);
void ScalerQC_OSDPutStringProp(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucLanguage, BYTE *pucArray);
void ScalerQC_OSDTableLoadText(BYTE ucRow, BYTE ucCol, BYTE ucPFontType, BYTE ucLanguage, BYTE ucStringType);
void ScalerQC_OSDReorder(void);
void ScalerQC_OSDSetHStart(WORD usHStart);
void ScalerQC_OSDFuncFrame(BYTE ucFrameStatus);
void ScalerQC_OSDCloseFuncFrame(BYTE ucFrameStatus);

bit ScalerQC_OSDTestProc(void);
bit ScalerQCOSDTest(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Print CRC when not match
// Input Value  : pucCRC: IC CRC, ucNum: CRC Number
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDPrintCRC(BYTE ucFrame, BYTE ucPath, BYTE *pucCRC, BYTE ucNum)
{
    BYTE ucIdx = 0;
    char pucMessage[12] = "5.M1_CRC[0]";

    switch(ucPath)
    {
        case 0:
        default:
            pucMessage[2] = 'M';
            pucMessage[3] = '1';
            break;

        case 1:
            pucMessage[2] = 'M';
            pucMessage[3] = '2';
            break;

        case 2:
            pucMessage[2] = 'S';
            pucMessage[3] = '1';
            break;

        case 3:
            pucMessage[2] = 'S';
            pucMessage[3] = '2';
            break;

        case 4:
            pucMessage[2] = 'R';
            pucMessage[3] = '1';
            break;

        case 5:
            pucMessage[2] = 'R';
            pucMessage[3] = '2';
            break;
    }

    if(ucFrame > 0)
    {
        DebugMessageQC("5.======Frame=====", ucFrame);
    }

    for(ucIdx = 0; ucIdx < ucNum; ucIdx++)
    {
        pucMessage[9] = (ucIdx + 0x30);
        DebugMessageQC(pucMessage, pucCRC[ucIdx]);
    }

    pucCRC = pucCRC;
}

//--------------------------------------------------
// Description  : Compare CRC with IC Read out
// Input Value  : enumDomain: CRC domain, e.g. _I_DOMAIN
//                ucPosition: CRC Position, e.g._I_CRC_AFTER_VGIP
//                ucSourceSel: Path Sel,e.g. _M1|_M2|S1
//                pucCRC: CRC Table pointer
//                ucFrameNum: Frame number to be compared, if not by frame, set 1
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQC_OSDCRCCompare(BYTE ucDomain, BYTE ucPosition, BYTE ucSourceSel, BYTE *pucCRC, BYTE ucFrameNum)
{
    BYTE uci = 0;
    BYTE ucj = 0;
    BYTE uck = 0;
    BYTE xdata pucReadCRC[36] = {0};
    bit bFlag = _TEST_PASS;
    BYTE pucOrder[6] = {_M1, _M2, _S1, _S2, _ROT_M1, _ROT_M2};
    WORD usAddr = P36_01_I_MAIN1_CRC_1;
    BYTE ucPathNum = 4;
    BYTE ucWaitType = _EVENT_DVS;
    BYTE pucMessage[8] = "Frame 0";

    ScalerSetByte(P36_00_I_CRC_CTRL, 0x00);
    ScalerSetByte(P36_40_M_CRC_CTRL, 0x00);
    ScalerSetByte(P36_2C_D_CRC_CTRL, 0x00);

    if(ucDomain == _I_DOMAIN_CRC)
    {
        ucWaitType = _EVENT_IVS;
        usAddr = P36_01_I_MAIN1_CRC_1;
        ucPathNum = 4;
        ScalerSetByte(P36_00_I_CRC_CTRL, ((ucPosition & 0x03) << 6) | ucSourceSel);
    }
    else if(ucDomain == _M_DOMAIN_CRC)
    {
        ucWaitType = _EVENT_DVS;
        usAddr = P36_41_M_M1_CRC_1;
        ucPathNum = 6;
        ScalerSetByte(P36_40_M_CRC_CTRL, ucSourceSel);
    }
    else // D-domain
    {
        ucWaitType = _EVENT_DVS;
        usAddr = P36_2D_D_MAIN1_CRC_1;
        ucPathNum = 3;
        ScalerSetByte(P36_2C_D_CRC_CTRL, ((ucPosition & 0x01) << 7) | ucSourceSel);
    }

    ScalerTimerWaitForEvent(ucWaitType);

    for(uck = 0; uck < ucFrameNum; uck++)
    {
        ScalerTimerWaitForEvent(ucWaitType);
        ScalerTimerDelayXms(2);

        for(ucj = 0; ucj < ucPathNum; ucj++)
        {
            if((ucSourceSel & pucOrder[ucj]) != 0)
            {
                for(uci = 6 * ucj; uci < 6 * (ucj + 1); uci++)
                {
                    pucReadCRC[uci] = ScalerGetByte(usAddr + uci);
                }
            }
        }

        for(ucj = 0; ucj < ucPathNum; ucj++)
        {
            if((ucSourceSel & pucOrder[ucj]) != 0)
            {
                for(uci = 6 * ucj; uci < 6 * (ucj + 1); uci++)
                {
                    if(pucReadCRC[uci] != pucCRC[uck * ucPathNum * 6 + uci])
                    {
                        ScalerQC_OSDPrintCRC(uck, ucj, pucReadCRC + 6 * ucj, 6);
                        bFlag = _TEST_FAIL;
                        break;
                    }
                }
             }
        }

        if(bFlag == _TEST_FAIL)
        {
            return _TEST_FAIL;
        }
    }

    if(bFlag == _TEST_PASS)
    {
        DebugMessageQC("5.===Pass===", 0);
    }

    return bFlag;
}


//--------------------------------------------------
// Description  : Rounded Window
// Input Value  :None
// Output Value :None
//--------------------------------------------------
void ScalerQC_OSDWindowRoundedWin(bit bEnable)
{
    BYTE ucIdx = 0;

    SET_OSD_WINDOW_NUMBER(_ROUND_WINDOW_1);
    SET_OSD_WINDOW_ENABLE(bEnable);
    SET_OSD_WINDOW_COLOR(4);
    SET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE(_ENABLE);
    ScalerOsdDrawWindow(XSTART(_OSD_WINDOW_4_3_X_START), YSTART(_OSD_WINDOW_4_3_Y_START), XEND(_OSD_WINDOW_4_3_X_START + _OSD_WINDOW_WIDTH), YEND(_OSD_WINDOW_4_3_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdRoundedWindowSize(_ROUND_WINDOW_1, _OSD_ROUNDED_WIN_SIZE_8X8);
    ScalerOsdRoundedWindowOnOff(_ROUND_WINDOW_1, bEnable, _ENABLE, _ENABLE, _ENABLE, _ENABLE);

    for(ucIdx = 0; ucIdx < 8; ucIdx++)
    {
        ScalerOsdRoundedWindowPattern8x8(ucIdx, ucIdx);
    }

    SET_OSD_WINDOW_NUMBER(_ROUND_WINDOW_2);
    SET_OSD_WINDOW_ENABLE(bEnable);
    SET_OSD_WINDOW_COLOR(6);
    SET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE(_ENABLE);
    ScalerOsdDrawWindow(XSTART(_OSD_WINDOW_4_4_X_START), YSTART(_OSD_WINDOW_4_4_Y_START), XEND(_OSD_WINDOW_4_4_X_START + _OSD_WINDOW_WIDTH), YEND(_OSD_WINDOW_4_4_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdRoundedWindowSize(_ROUND_WINDOW_2, _OSD_ROUNDED_WIN_SIZE_16X16);
    ScalerOsdRoundedWindowOnOff(_ROUND_WINDOW_2, bEnable, _DISABLE, _ENABLE, _ENABLE, _DISABLE);

    for(ucIdx = 0; ucIdx < 16; ucIdx++)
    {
        ScalerOsdRoundedWindowPattern16x16(ucIdx, ucIdx);
    }

    SET_OSD_WINDOW_NUMBER(_ROUND_WINDOW_3);
    SET_OSD_WINDOW_ENABLE(bEnable);
    SET_OSD_WINDOW_COLOR(9);
    SET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE(_ENABLE);
    ScalerOsdDrawWindow(XSTART(_OSD_WINDOW_4_8_X_START), YSTART(_OSD_WINDOW_4_8_Y_START), XEND(_OSD_WINDOW_4_8_X_START + _OSD_WINDOW_WIDTH), YEND(_OSD_WINDOW_4_8_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdRoundedWindowSize(_ROUND_WINDOW_3, _OSD_ROUNDED_WIN_SIZE_32X32);
    ScalerOsdRoundedWindowOnOff(_ROUND_WINDOW_3, bEnable, _ENABLE, _DISABLE, _DISABLE, _ENABLE);

    for(ucIdx = 0; ucIdx < 32; ucIdx++)
    {
        ScalerOsdRoundedWindowPattern32x32(ucIdx, ucIdx);
    }

    // close window
    if(bEnable != _ENABLE)
    {
        ScalerOsdWindowDisable(_ROUND_WINDOW_1);
        ScalerOsdWindowDisable(_ROUND_WINDOW_2);
        ScalerOsdWindowDisable(_ROUND_WINDOW_3);
    }
}

//--------------------------------------------------
// Description  : Font Scale Up
// Input Value  :None
// Output Value :None
//--------------------------------------------------
void ScalerQC_OSDSRAMSize(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        ScalerOsdSramBaseAddressSet(_OSD_A, _OSD_MAPA_ADDRESS_ROWCOMMAND, _OSD_MAPA_ADDRESS_CHARCOMMAND, _SRAM_SIZE_FONT_BASE_ADDRESS);

        ScalerOsdHardwareVLC(tQCOSD_VLC_TABLE[_OSD_VLC_24_36_1BIT], VLC_TABLE_SIZE(tQCOSD_VLC_TABLE[_OSD_VLC_24_36_1BIT]), GET_CURRENT_BANK_NUMBER(), 0x00, _SRAM_SIZE_FONT_BASE_ADDRESS, _OSD_ROTATE_DEGREE_0);

        ScalerOsd2BitFontOffset(_SRAM_SIZE_2BIT_OFFSET);
        ScalerOsdHardwareVLC(tQCOSD_VLC_TABLE[_OSD_VLC_24_36_2BIT], VLC_TABLE_SIZE(tQCOSD_VLC_TABLE[_OSD_VLC_24_36_2BIT]), GET_CURRENT_BANK_NUMBER(), (_SRAM_SIZE_2BIT_OFFSET * 2), _SRAM_SIZE_FONT_BASE_ADDRESS, _OSD_ROTATE_DEGREE_0);
        ScalerOsdSramDataValue(ROW(1), COL(0), LENGTH(1), 0x00 + 3, _OSD_BYTE1);
        ScalerOsdChange2BitColor(ROW(1), COL(0), LENGTH(1), HEIGHT(1), COLOR00(0), COLOR01(1), COLOR10(3), COLOR11(9));

        ScalerOsd4BitFontOffset(_SRAM_SIZE_4BIT_OFFSET);
        ScalerOsdHardwareVLC(tQCOSD_VLC_TABLE[_OSD_VLC_24_36_4BIT], VLC_TABLE_SIZE(tQCOSD_VLC_TABLE[_OSD_VLC_24_36_4BIT]), GET_CURRENT_BANK_NUMBER(), (_SRAM_SIZE_4BIT_OFFSET * 4), _SRAM_SIZE_FONT_BASE_ADDRESS, _OSD_ROTATE_DEGREE_0);
        ScalerOsdSramDataValue(ROW(2), COL(0), LENGTH(1), 0x00 + 3, _OSD_BYTE1);
        ScalerOsdChange4BitColor(ROW(2), COL(0), LENGTH(1), HEIGHT(1), BGCOLOR(0), (_OSD_4BIT_PALETTE_00_01_02_03 | _OSD_4BIT_PALETTE_04_05_06_07 | _OSD_4BIT_PALETTE_08_09_10_11 | _OSD_4BIT_PALETTE_12_13_14_15));
    }
    else
    {
        ScalerQC_OSDFuncApplyMap(_OSD_ROTATE_DEGREE_0);
        ScalerQC_OSDFuncClear(ROW(0), COL(0), LENGTH(_OSD_MAPA_SIZE_COL), HEIGHT(_OSD_MAPA_SIZE_ROW));
        // ScalerQC_OSDFuncClear(ROW_MAPB(0), COL(0), LENGTH(_OSD_MAPB_SIZE_COL), HEIGHT(_OSD_MAPB_SIZE_ROW));
    }
}

//--------------------------------------------------
// Description  : Font Scale Up
// Input Value  :None
// Output Value :None
//--------------------------------------------------
void ScalerQC_OSDFont24_36(bit bEnable)
{
    BYTE ucIdx = 0;

    if(bEnable == _ENABLE)
    {
        ScalerOsd2BitFontOffset(_SRAM_SIZE_2BIT_OFFSET / 4);
        ScalerOsd4BitFontOffset(_SRAM_SIZE_4BIT_OFFSET / 4);

        ScalerOsdRowHeight(ROW(0), HEIGHT(36), LENGTH(_OSD_MAPA_SIZE_ROW));

        for(ucIdx = 0; ucIdx < 14; ucIdx++)
        {
            ScalerOsdSramDataValue(ROW(ucIdx), COL(0), LENGTH(_OSD_MAPA_SIZE_COL), 0x58, _OSD_BYTE0);
            ScalerOsdSramDataValue(ROW(ucIdx), COL(0), LENGTH(_OSD_MAPA_SIZE_COL), 0x00, _OSD_BYTE1);
        }

        ScalerOsdSramDataValue(ROW(1), COL(0), LENGTH(1), 0x00, _OSD_BYTE1);
        ScalerOsdChange2BitColor(ROW(1), COL(0), LENGTH(1), HEIGHT(1), COLOR00(0), COLOR01(1), COLOR10(3), COLOR11(9));

        ScalerOsdSramDataValue(ROW(2), COL(0), LENGTH(1), 0x00, _OSD_BYTE1);
        ScalerOsdChange4BitColor(ROW(2), COL(0), LENGTH(1), HEIGHT(1), BGCOLOR(0), (_OSD_4BIT_PALETTE_00_01_02_03 | _OSD_4BIT_PALETTE_04_05_06_07 | _OSD_4BIT_PALETTE_08_09_10_11 | _OSD_4BIT_PALETTE_12_13_14_15));
    }

    ScalerOsdFont24x36OnOff(bEnable);
}

//--------------------------------------------------
// Description  : Font Scale Up
// Input Value  :None
// Output Value :None
//--------------------------------------------------
void ScalerQC_OSDScaleUp(bit bEnable, BYTE ucFactor, BYTE ucType)
{
    if(bEnable == _ENABLE)
    {
        ScalerOsdChange1BitColor(ROW(0), COL(0), LENGTH(10), HEIGHT(1), FG_COLOR(1), BG_COLOR(0));
        ScalerOsdChange1BitColor(ROW(1), COL(0), LENGTH(10), HEIGHT(1), FG_COLOR(1), BG_COLOR(9));
    }
    else
    {
        ScalerOsdChange1BitColor(ROW(0), COL(0), LENGTH(10), HEIGHT(2), FG_COLOR(1), BG_COLOR(7));
    }

    ScalerOsdScaleUpVerFactor(ucFactor);
    ScalerOsdScaleUpHorFactor(ucFactor);
    ScalerOsdScaleUpBoundaryCodition(ucType);
    ScalerOsdScaleUpOnOff(bEnable);
}

//--------------------------------------------------
// Description  : QC test palette
// Input Value  :None
// Output Value :None
//--------------------------------------------------
void ScalerQC_OSDTablePaletteAdjust(void)
{
    BYTE xdata ucIdx = 0;
    BYTE xdata ucPaletteSize = 0;

    ucPaletteSize = sizeof(tPALETTE_QC) / 3;

    for(ucIdx = 0; ucIdx < ucPaletteSize; ucIdx++)
    {
        ScalerOsdSetColorPalette(ucIdx, tPALETTE_QC[(ucIdx * 3) + 0], tPALETTE_QC[(ucIdx * 3) + 1], tPALETTE_QC[(ucIdx * 3) + 2]);
    }
}

//--------------------------------------------------
// Description  : Initial osd registers
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDRegInitial(void)
{
    WORD usWinTemp = 0;

    // frame control registers without initial value
    ScalerSetByte(P3A_09_FRAME_CTRL_09, 0x00);
    ScalerSetByte(P3A_0A_FRAME_CTRL_0A, 0x00);
    ScalerSetByte(P3A_0B_FRAME_CTRL_0B, 0x00);

    ScalerSetByte(P3A_0C_FRAME_CTRL_0C, 0x00);
    ScalerSetByte(P3A_0D_FRAME_CTRL_0D, 0x00);
    ScalerSetByte(P3A_0E_FRAME_CTRL_0E, 0x00);

    ScalerSetByte(P3A_0F_FRAME_CTRL_0F, 0x00);
    ScalerSetByte(P3A_10_FRAME_CTRL_10, 0x00);
    ScalerSetByte(P3A_11_FRAME_CTRL_11, 0x00);

    ScalerSetByte(P3A_12_FRAME_CTRL_12, 0x00);
    ScalerSetByte(P3A_13_FRAME_CTRL_13, 0x00);
    ScalerSetByte(P3A_14_FRAME_CTRL_14, 0x00);

    ScalerSetByte(P3A_15_FRAME_CTRL_15, 0x00);
    ScalerSetByte(P3A_16_FRAME_CTRL_16, 0x00);
    ScalerSetByte(P3A_17_FRAME_CTRL_17, 0x00);

    ScalerOsdDrawGridLinePanelPitch(0, 0);

    // window control registers without initial value
    for(usWinTemp = 0; usWinTemp < 10; usWinTemp++)
    {
        ScalerOsdFrameControlAllByte((0x103 + usWinTemp * 4), _OSD_WITHOUT_DB, 0x00, 0x00, 0x00);
        if(usWinTemp < 8)
        {
            ScalerOsdFrameControlAllByte((0x203 + usWinTemp * 4), _OSD_WITHOUT_DB, 0x00, 0x00, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Load font map
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDFontLoadVLC(EnumOsdRotateType enumOsdRotateType)
{
    ScalerOsdHardwareVLC(tQCOSD_VLC_TABLE[_OSD_VLC_QCMAP], VLC_TABLE_SIZE(tQCOSD_VLC_TABLE[_OSD_VLC_QCMAP]), GET_CURRENT_BANK_NUMBER(), 0x00, 0x00, _OSD_ROTATE_DEGREE_0);
    ScalerQC_OSDRotateFont(tQCOSD_VLC_TABLE[_OSD_VLC_QCFONT_GLOBAL], VLC_TABLE_SIZE(tQCOSD_VLC_TABLE[_OSD_VLC_QCFONT_GLOBAL]), GET_CURRENT_BANK_NUMBER(), 0x00, _OSD_MAP_FONT_BASE_ADDRESS, enumOsdRotateType);
    ScalerOsdHardwareVLC(tQCOSD_VLC_TABLE[_OSD_VLC_QCFONT_2BITBROOK], VLC_TABLE_SIZE(tQCOSD_VLC_TABLE[_OSD_VLC_QCFONT_2BITBROOK]), GET_CURRENT_BANK_NUMBER(), _2BIT_FONT_ICON_START, _OSD_MAP_FONT_BASE_ADDRESS, enumOsdRotateType);
    ScalerOsdHardwareVLC(tQCOSD_VLC_TABLE[_OSD_VLC_QCFONT_4BITLUFFY], VLC_TABLE_SIZE(tQCOSD_VLC_TABLE[_OSD_VLC_QCFONT_4BITLUFFY]), GET_CURRENT_BANK_NUMBER(), _4BIT_FONT_ICON_START, _OSD_MAP_FONT_BASE_ADDRESS, enumOsdRotateType);
}

//--------------------------------------------------
// Description  : Set font map information
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDFuncApplyMap(EnumOsdRotateType enumOsdRotateType)
{
    ScalerQC_OSDFontLoadVLC(enumOsdRotateType);
    SET_OSD_MAPA_COL_MAX(_OSD_MAPA_SIZE_COL);
    ScalerOsdSramBaseAddressSet(_OSD_A, _OSD_MAPA_ADDRESS_ROWCOMMAND, _OSD_MAPA_ADDRESS_CHARCOMMAND, _OSD_MAP_FONT_BASE_ADDRESS);

    SET_OSD_MAPB_COL_MAX(_OSD_MAPB_SIZE_COL);
    ScalerOsdSramBaseAddressSet(_OSD_B, _OSD_MAPB_ADDRESS_ROWCOMMAND, _OSD_MAPB_ADDRESS_CHARCOMMAND, _OSD_MAP_FONT_BASE_ADDRESS);
}

//--------------------------------------------------
// Description  : Set font map rotation with accleration
// Input Value  : *pucArray          -> table
//                usTableSize   -> Use TABLE_SIZE
//                ucBankNum        -> Bank number (GET_CURRENT_BANK_NUMBER())
//                usOffset         -> Font address
//                usFontTableStart -> Font base address
//                ucOsdRotateType  -> _OSD_ROTATE_DEGREE_0 or _OSD_ROTATE_DEGREE_90 or _OSD_ROTATE_DEGREE_270
// Output Value :
//--------------------------------------------------
void ScalerQC_OSDRotateFont(BYTE *pucArray, WORD usTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType)
{
    BYTE ucType = 0;

    if(enumOsdRotateType == _OSD_ROTATE_DEGREE_90)
    {
        ucType = ucType | _OSD_ROTATE_CW | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE | _OSD_ROTATE_ROTATION;
    }
    else if(enumOsdRotateType == _OSD_ROTATE_DEGREE_270)
    {
        ucType = ucType | _OSD_ROTATE_CCW | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE | _OSD_ROTATE_ROTATION;
    }
    else if(enumOsdRotateType == _OSD_ROTATE_DEGREE_180)
    {
        ucType = ucType | _OSD_ROTATE_CW180 | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE | _OSD_ROTATE_ROTATION;
    }
    else
    {
        ucType = ucType | _OSD_ROTATE_NO_SWAP;
    }
    // rotation
    ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT2 | _BIT0), ucType);
    ScalerSetByte(P3A_0F_FRAME_CTRL_0F, *(pucArray + 0));
    ScalerSetByte(P3A_10_FRAME_CTRL_10, *(pucArray + 1));
    ScalerSetByte(P3A_11_FRAME_CTRL_11, *(pucArray + 2));
    ScalerSetByte(P3A_12_FRAME_CTRL_12, *(pucArray + 3));
    ScalerSetByte(P3A_13_FRAME_CTRL_13, *(pucArray + 4));
    ScalerSetByte(P3A_14_FRAME_CTRL_14, *(pucArray + 5));
    ScalerSetByte(P3A_15_FRAME_CTRL_15, *(pucArray + 6));
    ScalerSetByte(P3A_16_FRAME_CTRL_16, *(pucArray + 7));

    usOffset = usOffset * 9; // ---
    usOffset += usFontTableStart;

    // osd compression enable
    if(enumOsdRotateType == _OSD_ROTATE_DEGREE_0)
    {
        ScalerSetBit(P3A_17_FRAME_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        ScalerSetBit(P3A_17_FRAME_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    }

    pucArray += 10; // ---

    ScalerOsdSramAddressSet(usOffset, _OSD_BYTEALL);
    ScalerOsdBurstWriteDataPort(pucArray, usTableSize, ucBankNum, _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_FLASH);

    // OSD HW needs time to process it and then write decompressed data into SRAM.
    // The value 1ms is enough at all.
    ScalerTimerDelayXms(2);

    // osd compression disable
    ScalerSetBit(P3A_17_FRAME_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    if(enumOsdRotateType != _OSD_ROTATE_DEGREE_0)
    {
        ucType = 0x01;
    }
    else
    {
        ucType = 0x00;
    }

    ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT2 | _BIT0), ucType);
}

//--------------------------------------------------
// Description  : Load icon table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDLoadIcon(BYTE ucRow, BYTE ucCol, BYTE ucLanguage, BYTE ucIconSelect)
{
    ScalerQC_OSDFxLoadText(ucRow, ucCol, ucLanguage, tQCICON_TABLE[ucIconSelect]);
}

//--------------------------------------------------
// Description  : load text
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDFxLoadText(BYTE ucRow, BYTE ucCol, BYTE ucSelect, BYTE *pucArray)
{
    BYTE xdata ucRepeat = 0;
    BYTE xdata ucNext = 0;
    BYTE xdata ucTemp = 0;
    WORD xdata usText = 0;
    WORD xdata usCnt = 0;

    while(_TRUE)
    {
        if(*(pucArray + usCnt) == _END_)
        {
            if(ucTemp == ucSelect)
            {
                break;
            }
            else
            {
                pucArray += (usCnt + 1);
                usCnt = 0;
            }
            ucTemp++;
        }
        usCnt++;
    }

    usCnt = 0;

    while(*(pucArray + usText) != _END_)
    {
        ScalerOsdSramAddressCount(ucRow + ucNext, ucCol + usCnt + ucRepeat, _OSD_BYTE1);

        switch(*(pucArray + usText))
        {
            case _REPEAT_:
                if(ucRepeat < (*(pucArray + usText + 1) - 1))
                {
                    ucRepeat++;
                }
                else
                {
                    usText += 2;
                    ucRepeat = 0;
                    continue;
                }
                break;

            case _NEXT_:
                ucNext++;
                usText++;
                usCnt = 0;
                continue;

            default:
                ucTemp = *(pucArray + usText);
                usText++;
                usCnt++;
                break;
        }

        ScalerOsdDataPort(ucTemp);
    }
}

//--------------------------------------------------
// Description  : Draw SRAM test pattern
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDSRAMTestPattern(void)
{
    BYTE ucIdx = 0;

    // 1Bit Icon
    ScalerQC_OSDLoadIcon(ROW(1), COL(0), LANGUAGE(0), _OSD_QCICON_1BIT);
    ScalerQC_OSDLoadIcon(ROW(2), COL(0), LANGUAGE(0), _OSD_QCICON_1BIT);
    ScalerQC_OSDLoadIcon(ROW(2), COL(16), LANGUAGE(0), _OSD_QCICON_1BIT);
    ScalerQC_OSDLoadIcon(ROW(3), COL(0), LANGUAGE(0), _OSD_QCICON_1BIT_BOARD_SHADOW);

    // 2Bit Icon
    ScalerOsd2BitFontOffset(_2BIT_OFFSET);
    for(ucIdx = 0; ucIdx < 4; ucIdx++)
    {
        ScalerQC_OSDLoadIcon(ROW(8), COL(0 + (ucIdx * 8)), LANGUAGE(0), _OSD_QCICON_2BIT);
        ScalerOsdChange2BitColor(ROW(8), COL(0 + (ucIdx * 8)), LENGTH(8), HEIGHT(6), COLOR_00(0), COLOR_01(1), COLOR_10(2), COLOR_11(3));
    }
    // 4Bit Icon
    for(ucIdx = 0; ucIdx < 5; ucIdx++)
    {
        ScalerQC_OSDLoadIcon(ROW_MAPB(0), COL(0 + (ucIdx * 11)), LANGUAGE(0), _OSD_QCICON_4BIT);
        ScalerOsdChange4BitColor(ROW_MAPB(0), COL(0 + (ucIdx * 11)), LENGTH(11), HEIGHT(7), 0x01, _OSD_4BIT_PALETTE_00_01_02_03 | _OSD_4BIT_PALETTE_04_05_06_07 | _OSD_4BIT_PALETTE_08_09_10_11 | _OSD_4BIT_PALETTE_12_13_14_15);
    }
}

//--------------------------------------------------
// Description  : Draw blank font
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDBlankFont(BYTE ucStatus, BYTE ucBlankLength)
{
    BYTE ucIdx = 0;

    ScalerOsdBlankCommandColorExtension(ucStatus);

    // Blank Font Color
    ScalerOsdBlankFont(ROW(0), COL(0), LENGTH(1), HEIGHT(1), VALUES(ucBlankLength), BG_COLOR(17), _OSD_BLANK_FONT);

    // align
    for(ucIdx = 0; ucIdx < 5; ucIdx++)
    {
        ScalerOsdBlankFont(ROW(3 + ucIdx), COL(2 + ucIdx), LENGTH(1), HEIGHT(1), VALUES(15), BG_COLOR(22), _OSD_BLANK_ALIGN);
    }
}

//--------------------------------------------------
// Description  : Draw blank font
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDBlankFontCw270(BYTE ucStatus, BYTE ucBlankLength)
{
    BYTE ucIdx = 0;

    ScalerOsdBlankCommandColorExtension(ucStatus);

    // Blank Font Color
    ScalerOsdBlankFont(ROW(0), COL(0), LENGTH(1), HEIGHT(1), VALUES(ucBlankLength), BG_COLOR(17), _OSD_BLANK_FONT);

    // align
    for(ucIdx = 0; ucIdx < _OSD_MAPA_SIZE_ROW; ucIdx++)
    {
        ScalerOsdBlankFont(ROW(ucIdx), COL(_OSD_MAPA_SIZE_COL - 1), LENGTH(1), HEIGHT(1), VALUES(_OSD_MAPA_SIZE_COL + 1), BG_COLOR(22), _OSD_BLANK_ALIGN);
    }
}

//--------------------------------------------------
// Description  : Test 1-bit font shrink
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSD1BitFontShrink(BYTE ucStatus, ucCharWidth)
{
    ScalerOsd1BitFontShrink(ucStatus);
    ScalerOsdSramDataValue(ROW(2), COL(16), LENGTH(11), (0x40 | ucCharWidth), _OSD_BYTE0);
}

//--------------------------------------------------
// Description  : Test 1-bit font color
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSD1BitColor(BYTE ucDoubleEnable)
{
    // test 1-bit font color palette 16~32
    ScalerOsdChange1BitColor(ROW(1), COL(0), LENGTH(6), HEIGHT(1), FG_COLOR(2), BG_COLOR(3));

    // test 1-bit font color palette 0~15
    ScalerOsdChange1BitColor(ROW(2), COL(0), LENGTH(11), HEIGHT(1), FG_COLOR(5), BG_COLOR(6));

    // For Row Command For Font Border & Shadow
    ScalerOsdChange1BitColor(ROW(3), COL(0), LENGTH(2), HEIGHT(1), FG_COLOR(9), BG_COLOR(0));
    ScalerOsdChange1BitColor(ROW(4), COL(0), LENGTH(3), HEIGHT(1), FG_COLOR(9), BG_COLOR(0));
    ScalerOsdChange1BitColor(ROW(5), COL(0), LENGTH(4), HEIGHT(1), FG_COLOR(9), BG_COLOR(0));
    ScalerOsdChange1BitColor(ROW(6), COL(0), LENGTH(5), HEIGHT(1), FG_COLOR(9), BG_COLOR(0));
    ScalerOsdChange1BitColor(ROW(7), COL(0), LENGTH(6), HEIGHT(1), FG_COLOR(9), BG_COLOR(0));

    ScalerOsdCommandByte(ROW(3), _OSD_BYTE0, (0x80 | _ROW_COMMAND_DOUBLE_DISABLE));
    ScalerOsdCommandByte(ROW(4), _OSD_BYTE0, (0x80 | _ROW_COMMAND_DOUBLE_DISABLE));

    if(ucDoubleEnable == _ENABLE)
    {
        ScalerOsdCommandByte(ROW(5), _OSD_BYTE0, (0x80 | _ROW_COMMAND_DOUBLE_ENABLE));
        ScalerOsdCommandByte(ROW(6), _OSD_BYTE0, (0x80 | _ROW_COMMAND_DOUBLE_ENABLE));
        ScalerOsdCommandByte(ROW(7), _OSD_BYTE0, (0x80 | _ROW_COMMAND_DOUBLE_ENABLE));
    }
    else
    {
        ScalerOsdCommandByte(ROW(5), _OSD_BYTE0, (0x80 | _ROW_COMMAND_DOUBLE_DISABLE));
        ScalerOsdCommandByte(ROW(6), _OSD_BYTE0, (0x80 | _ROW_COMMAND_DOUBLE_DISABLE));
        ScalerOsdCommandByte(ROW(7), _OSD_BYTE0, (0x80 | _ROW_COMMAND_DOUBLE_DISABLE));
    }
}

//--------------------------------------------------
// Description  : Test 2-bit font bit swap (or font select extension)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSD2BitFontByte1Bit7Swap(BYTE ucStatus)
{
    ScalerOsd2BitFontByte1Bit7Swap(ucStatus);

    if(ucStatus == _OSD_2BIT_CHAR_BIT7_BY_CHANGE_PALETTE)
    {
        // background color transparent when color00 = 0
        ScalerOsdChange2BitColor16_31(ROW(8), COL(0), LENGTH(8), HEIGHT(6), COLOR_00(0 + 16), COLOR_01(1 + 16), COLOR_10(2 + 16), COLOR_11(3 + 16));
        // MSB for color00 and color11
        ScalerOsdChange2BitColor16_31(ROW(8), COL(8), LENGTH(8), HEIGHT(6), COLOR_00(14 + 16), COLOR_01(5 + 16), COLOR_10(7 + 16), COLOR_11(12 + 16));
        // change palette to 16~32
        ScalerOsdChange2BitColor16_31(ROW(8), COL(16), LENGTH(8), HEIGHT(6), COLOR_00(2 + 16), COLOR_01(11 + 16), COLOR_10(14 + 16), COLOR_11(7 + 16));
        // change palette to 16~32 and MSB for color00 and color11
        ScalerOsdChange2BitColor16_31(ROW(8), COL(24), LENGTH(8), HEIGHT(6), COLOR_00(8 + 16), COLOR_01(9 + 16), COLOR_10(10 + 16), COLOR_11(14 + 16));
    }
    else if(ucStatus == _OSD_2BIT_CHAR_BIT7_BY_SELECT_FONT)
    {
        // MSB for color01 and color10
        ScalerOsdChange2BitColor(ROW(8), COL(0), LENGTH(8), HEIGHT(6), COLOR_00(7), COLOR_01(8), COLOR_10(15), COLOR_11(4));

        // MSB for color00 and color11
        ScalerOsdChange2BitColor(ROW(8), COL(8), LENGTH(8), HEIGHT(6), COLOR_00(14), COLOR_01(0), COLOR_10(4), COLOR_11(9));

        // MSB for color01 and color10
        ScalerOsdChange2BitColor(ROW(8), COL(16), LENGTH(8), HEIGHT(6), COLOR_00(0), COLOR_01(1), COLOR_10(2), COLOR_11(3));

        // MSB for color00 and color11
        ScalerOsdChange2BitColor(ROW(8), COL(24), LENGTH(8), HEIGHT(6), COLOR_00(11), COLOR_01(12), COLOR_10(13), COLOR_11(14));
    }
}

//--------------------------------------------------
// Description  : Test 4-bit font reference background
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDReference4BitBackground(BYTE ucStatus)
{
    ScalerReference4BitBackground(ucStatus);

    if(ucStatus == _OSD_4BIT_BACKGROUND_TO_BYTE2)
    {
        // change palette and background color follow palette color 0, 16, 32, 48
        ScalerOsdChange4BitColor(ROW_MAPB(0), COL(0), LENGTH(11), HEIGHT(7), 0x01, _OSD_4BIT_PALETTE_00_01_02_03 | _OSD_4BIT_PALETTE_04_05_06_07 | _OSD_4BIT_PALETTE_08_09_10_11 | _OSD_4BIT_PALETTE_12_13_14_15);
        ScalerOsdChange4BitColor(ROW_MAPB(0), COL(11), LENGTH(11), HEIGHT(7), 0x01, _OSD_4BIT_PALETTE_16_17_18_19 | _OSD_4BIT_PALETTE_20_21_22_23 | _OSD_4BIT_PALETTE_24_25_26_27 | _OSD_4BIT_PALETTE_28_29_30_31);
        ScalerOsdChange4BitColor(ROW_MAPB(0), COL(22), LENGTH(11), HEIGHT(7), 0x01, _OSD_4BIT_PALETTE_32_33_34_35 | _OSD_4BIT_PALETTE_36_37_38_39 | _OSD_4BIT_PALETTE_40_41_42_43 | _OSD_4BIT_PALETTE_44_45_46_47);
        ScalerOsdChange4BitColor(ROW_MAPB(0), COL(33), LENGTH(11), HEIGHT(7), 0x01, _OSD_4BIT_PALETTE_48_49_50_51 | _OSD_4BIT_PALETTE_52_53_54_55 | _OSD_4BIT_PALETTE_56_57_58_59 | _OSD_4BIT_PALETTE_50_61_62_63);
        // background color transparent when BGColor set 0x00
        ScalerOsdChange4BitColor(ROW_MAPB(0), COL(44), LENGTH(11), HEIGHT(7), 0x00, _OSD_4BIT_PALETTE_48_49_50_51 | _OSD_4BIT_PALETTE_52_53_54_55 | _OSD_4BIT_PALETTE_56_57_58_59 | _OSD_4BIT_PALETTE_50_61_62_63);
    }
    else if(ucStatus == _OSD_4BIT_BACKGROUND_TO_BYTE0)
    {
        // background color follow byte0 select palette 0~15 index color no matter how palette change
        ScalerOsdChange4BitColor(ROW_MAPB(0), COL(0), LENGTH(11), HEIGHT(7), 0x07, _OSD_4BIT_PALETTE_16_17_18_19 | _OSD_4BIT_PALETTE_20_21_22_23 | _OSD_4BIT_PALETTE_24_25_26_27 | _OSD_4BIT_PALETTE_28_29_30_31);
        ScalerOsdChange4BitColor(ROW_MAPB(0), COL(11), LENGTH(11), HEIGHT(7), 0x05, _OSD_4BIT_PALETTE_00_01_02_03 | _OSD_4BIT_PALETTE_04_05_06_07 | _OSD_4BIT_PALETTE_08_09_10_11 | _OSD_4BIT_PALETTE_12_13_14_15);
        ScalerOsdChange4BitColor(ROW_MAPB(0), COL(22), LENGTH(11), HEIGHT(7), 0x08, _OSD_4BIT_PALETTE_16_17_18_19 | _OSD_4BIT_PALETTE_20_21_22_23 | _OSD_4BIT_PALETTE_24_25_26_27 | _OSD_4BIT_PALETTE_28_29_30_31);
        ScalerOsdChange4BitColor(ROW_MAPB(0), COL(33), LENGTH(11), HEIGHT(7), 0x0f, _OSD_4BIT_PALETTE_00_01_02_03 | _OSD_4BIT_PALETTE_04_05_06_07 | _OSD_4BIT_PALETTE_08_09_10_11 | _OSD_4BIT_PALETTE_12_13_14_15);

        // background color transparent when BGColor set 0x00
        ScalerOsdChange4BitColor(ROW_MAPB(0), COL(44), LENGTH(11), HEIGHT(7), 0x00, _OSD_4BIT_PALETTE_00_01_02_03 | _OSD_4BIT_PALETTE_04_05_06_07 | _OSD_4BIT_PALETTE_08_09_10_11 | _OSD_4BIT_PALETTE_12_13_14_15);
    }
}

//--------------------------------------------------
// Description  : Draw window
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDDrawWindow(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucWindowColor, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
{
    SET_OSD_WINDOW_NUMBER(enumOsdWindowsType);
    SET_OSD_WINDOW_ENABLE(bEnable);
    SET_OSD_WINDOW_COLOR(ucWindowColor);
    SET_OSD_WINDOW_REFERENCE_DELAY(_OSD_FIRST_DELAY);
    ScalerOsdDrawWindow(usXStart, usYStart, usXEnd, usYEnd);

    // close window
    if(bEnable != _ENABLE)
    {
        ScalerOsdWindowDisable(enumOsdWindowsType);
    }
}

//--------------------------------------------------
// Description  : Test window priority
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowPriority(bit bEnable)
{
    BYTE ucIdx = 0;

    for(ucIdx = 0; ucIdx < 18; ucIdx++)
    {
        SET_OSD_WINDOW_NUMBER(tQCWINDOW_PRIORITY[ucIdx]);
        SET_OSD_WINDOW_COLOR(ucIdx);
        SET_OSD_WINDOW_ENABLE(bEnable);
        ScalerOsdDrawWindow(X_START(_OSD_WINDOW_0_X_START + (_OSD_OFFSET_X * ucIdx)), Y_START(_OSD_WINDOW_0_Y_START + (_OSD_OFFSET_Y * ucIdx)), X_END(_OSD_WINDOW_0_X_START + _OSD_WINDOW_WIDTH + (_OSD_OFFSET_X * ucIdx)), Y_END(_OSD_WINDOW_0_Y_START + _OSD_WINDOW_HEIGHT + (_OSD_OFFSET_Y * ucIdx)));

        // close window
        if(bEnable != _ENABLE)
        {
            ScalerOsdWindowDisable(tQCWINDOW_PRIORITY[ucIdx]);
        }
    }

    for(ucIdx = 0; ucIdx < 8; ucIdx++)
    {
        SET_OSD_WINDOW_NUMBER(tQCWINDOW_PRIORITY[18 + ucIdx]);
        SET_OSD_WINDOW_COLOR(18 + ucIdx);
        SET_OSD_WINDOW_ENABLE(bEnable);
        ScalerOsdDrawWindow(X_START(500 + _OSD_WINDOW_0_X_START + (_OSD_OFFSET_X * ucIdx)), Y_START(_OSD_WINDOW_0_Y_START + (_OSD_OFFSET_Y * ucIdx)), X_END(500 + _OSD_WINDOW_0_X_START + _OSD_WINDOW_WIDTH + (_OSD_OFFSET_X * ucIdx)), Y_END(_OSD_WINDOW_0_Y_START + _OSD_WINDOW_HEIGHT + (_OSD_OFFSET_Y * ucIdx)));

        // close window
        if(bEnable != _ENABLE)
        {
            ScalerOsdWindowDisable(tQCWINDOW_PRIORITY[18 + ucIdx]);
        }
    }
}

//--------------------------------------------------
// Description  : Test window 4 grid line function
//                Delete window 2, 3 grid line function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowGridLine(bit bENABLE, BYTE ucStatus)
{
    ScalerOsdDrawGridLinePanelPitch(993, 993);
    // Win 2
    ScalerQC_OSDSetGridLine(_OSD_WINDOW_2, (0 + (ucStatus * 3)), 61, _ENABLE, _ENABLE, 0x03, 0x2710, bENABLE);
    ScalerQC_OSDDrawWindow(bENABLE, _OSD_WINDOW_2, 10, X_START(_OSD_WINDOW_2_X_START), Y_START(_OSD_WINDOW_2_Y_START), X_END(_OSD_WINDOW_2_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_2_Y_START + _OSD_WINDOW_HEIGHT));

    // Win 3
    ScalerQC_OSDSetGridLine(_OSD_WINDOW_3, 1, 62, _DISABLE, _ENABLE, 0x03, 0x2710, bENABLE);
    ScalerQC_OSDDrawWindow(bENABLE, _OSD_WINDOW_3, 11, X_START(_OSD_WINDOW_3_X_START), Y_START(_OSD_WINDOW_3_Y_START), X_END(_OSD_WINDOW_3_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_3_Y_START + _OSD_WINDOW_HEIGHT));

    // Win 4
    ScalerQC_OSDSetGridLine(_OSD_WINDOW_4, 2, 63, _ENABLE, _DISABLE, 0x03, 0x2710, bENABLE);
    ScalerQC_OSDDrawWindow(bENABLE, _OSD_WINDOW_4, 10, X_START(_OSD_WINDOW_4_X_START), Y_START(_OSD_WINDOW_4_Y_START), X_END(_OSD_WINDOW_4_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_Y_START + _OSD_WINDOW_HEIGHT));
}

//--------------------------------------------------
// Description  : Set grid line
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDSetGridLine(EnumOsdWindowsType enumOsdWindowsType, BYTE ucGridLineWidth, BYTE ucGridLineColor, bit bHorizontalEnable, bit bVerticalEnable, BYTE ucGridLineOffset,
    WORD usGridLinePitch, bit bGridFunctionEnable)
{
    SET_OSD_GRID_WINDOW_NUMBER(enumOsdWindowsType);
    SET_OSD_GRID_LINE_WIDTH(ucGridLineWidth);
    SET_OSD_GRID_LINE_COLOR(ucGridLineColor);
    SET_OSD_GRID_LINE_HORIZONTAL_ENABLE(bHorizontalEnable);
    SET_OSD_GRID_LINE_VERTICAL_ENABLE(bVerticalEnable);
    SET_OSD_GRID_LINE_OFFSET(ucGridLineOffset);
    SET_OSD_GRID_LINE_PITCH(usGridLinePitch);
    SET_OSD_GRID_LINE_FUNCTION_ENABLE(bGridFunctionEnable);

    ScalerOsdDrawGridLine();
}

//--------------------------------------------------
// Description  : Test window 0, 5, 6, 7, 8, 9 gradient function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowGradient(bit bEnable, BYTE ucStatus)
{
    /*
    void ScalerQC_OSDSetGradient(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucWindowColor, BYTE ucGradStep, BYTE ucGradLevel,
                                bit bPolarity_R, bit bPolarity_G,
                                bit bPolarity_B, bit bEnable_R,
                                bit bEnable_G, bit bEnable_B,
                                bit bEnableSaturated, bit bEnableReversed,
                                bit bLevelExtension, bit bGradientDirection,
                                WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
    */
    // Gradient Horizontal Direction
    // Window 0
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_0, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_1, _OSD_WINDOW_GRADIENT_LEVEL_PER_1,
    tQCGRADIENT_POLITY[(ucStatus * 36) + 3], tQCGRADIENT_POLITY[(ucStatus * 36) + 4],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 5], tQCGRADIENT_POLITY[(ucStatus * 36) + 0],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 1], tQCGRADIENT_POLITY[(ucStatus * 36) + 2], _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_0_X_START), Y_START(_OSD_WINDOW_0_Y_START), X_END(_OSD_WINDOW_0_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_0_Y_START + _OSD_WINDOW_HEIGHT));

    // Window 5
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_5, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_2, _OSD_WINDOW_GRADIENT_LEVEL_PER_2,
    tQCGRADIENT_POLITY[(ucStatus * 36) + 6 + 3], tQCGRADIENT_POLITY[(ucStatus * 36) + 6 + 4],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 6 + 5], tQCGRADIENT_POLITY[(ucStatus * 36) + 6 + 0],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 6 + 1], tQCGRADIENT_POLITY[(ucStatus * 36) + 6 + 2], _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_5_X_START), Y_START(_OSD_WINDOW_5_Y_START), X_END(_OSD_WINDOW_5_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_Y_START + _OSD_WINDOW_HEIGHT));

    // Window 6
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_6, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_3, _OSD_WINDOW_GRADIENT_LEVEL_PER_3,
    tQCGRADIENT_POLITY[(ucStatus * 36) + 12 + 3], tQCGRADIENT_POLITY[(ucStatus * 36) + 12 + 4],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 12 + 5], tQCGRADIENT_POLITY[(ucStatus * 36) + 12 + 0],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 12 + 1], tQCGRADIENT_POLITY[(ucStatus * 36) + 12 + 2], _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_6_X_START), Y_START(_OSD_WINDOW_6_Y_START), X_END(_OSD_WINDOW_6_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_6_Y_START + _OSD_WINDOW_HEIGHT));

    // Gradient Vertical Direction  // 6193
    // Window 7
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_7, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    tQCGRADIENT_POLITY[(ucStatus * 36) + 18 + 3], tQCGRADIENT_POLITY[(ucStatus * 36) + 18 + 4],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 18 + 5], tQCGRADIENT_POLITY[(ucStatus * 36) + 18 + 0],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 18 + 1], tQCGRADIENT_POLITY[(ucStatus * 36) + 18 + 2], _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_VERTICAL,
    X_START(_OSD_WINDOW_7_X_START), Y_START(_OSD_WINDOW_7_Y_START), X_END(_OSD_WINDOW_7_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_7_Y_START + _OSD_WINDOW_HEIGHT));

    // Window 8
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_8, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_5,
    tQCGRADIENT_POLITY[(ucStatus * 36) + 24 + 3], tQCGRADIENT_POLITY[(ucStatus * 36) + 24 + 4],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 24 + 5], tQCGRADIENT_POLITY[(ucStatus * 36) + 24 + 0],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 24 + 1], tQCGRADIENT_POLITY[(ucStatus * 36) + 24 + 2], _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_VERTICAL,
    X_START(_OSD_WINDOW_8_X_START), Y_START(_OSD_WINDOW_8_Y_START), X_END(_OSD_WINDOW_8_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_8_Y_START + _OSD_WINDOW_HEIGHT));

    // Window9
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_9, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_6,
    tQCGRADIENT_POLITY[(ucStatus * 36) + 30 + 3], tQCGRADIENT_POLITY[(ucStatus * 36) + 30 + 4],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 30 + 5], tQCGRADIENT_POLITY[(ucStatus * 36) + 30 + 0],
    tQCGRADIENT_POLITY[(ucStatus * 36) + 30 + 1], tQCGRADIENT_POLITY[(ucStatus * 36) + 30 + 2], _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_VERTICAL,
    X_START(_OSD_WINDOW_9_X_START), Y_START(_OSD_WINDOW_9_Y_START), X_END(_OSD_WINDOW_9_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_9_Y_START + _OSD_WINDOW_HEIGHT));
}

//--------------------------------------------------
// Description  : Test window 0, 5, 6, 7, 8, 9 gradient saturated color and reversed mode
//                Delete win 7 gradient function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowSaturatedColor(bit bEnable)
{
    /*
    void ScalerQC_OSDSetGradient(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucWindowColor, BYTE ucGradStep, BYTE ucGradLevel,
                                bit bPolarity_R, bit bPolarity_G,
                                bit bPolarity_B, bit bEnable_R,
                                bit bEnable_G, bit bEnable_B,
                                bit bEnableSaturated, bit bEnableReversed,
                                bit bLevelExtension, bit bGradientDirection,
                                WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
    */

    // saturated color
    // Window 0
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_0, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_1, _OSD_WINDOW_GRADIENT_LEVEL_PER_8,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _ENABLE, _ENABLE, _DISABLE,
    _ENABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_0_X_START), Y_START(_OSD_WINDOW_0_Y_START), X_END(_OSD_WINDOW_0_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_0_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowSaturatedColorSelect(_OSD_WINDOW_0, 192, 30, 128);

    // Window 5
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_5, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_2, _OSD_WINDOW_GRADIENT_LEVEL_PER_7,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _DISABLE, _ENABLE, _ENABLE,
    _ENABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_5_X_START), Y_START(_OSD_WINDOW_5_Y_START), X_END(_OSD_WINDOW_5_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowSaturatedColorSelect(_OSD_WINDOW_5, 128, 192, 30);

    // Window 6
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_6, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_3, _OSD_WINDOW_GRADIENT_LEVEL_PER_6,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _ENABLE, _DISABLE, _ENABLE,
    _ENABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_6_X_START), Y_START(_OSD_WINDOW_6_Y_START), X_END(_OSD_WINDOW_6_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_6_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowSaturatedColorSelect(_OSD_WINDOW_6, 30, 128, 192);

    // Window 7
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_7, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_1, _OSD_WINDOW_GRADIENT_LEVEL_PER_5,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _ENABLE, _ENABLE, _DISABLE,
    _ENABLE, _ENABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_7_X_START), Y_START(_OSD_WINDOW_7_Y_START), X_END(_OSD_WINDOW_7_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_7_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowSaturatedColorSelect(_OSD_WINDOW_7, 192, 64, 128);

    // Window 8
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_8, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_2, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _DISABLE, _ENABLE, _ENABLE,
    _ENABLE, _ENABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_8_X_START), Y_START(_OSD_WINDOW_8_Y_START), X_END(_OSD_WINDOW_8_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_8_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowSaturatedColorSelect(_OSD_WINDOW_8, 128, 192, 64);

    // Window 9
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_9, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_3, _OSD_WINDOW_GRADIENT_LEVEL_PER_3,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _ENABLE, _DISABLE, _ENABLE,
    _ENABLE, _ENABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_9_X_START), Y_START(_OSD_WINDOW_9_Y_START), X_END(_OSD_WINDOW_9_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_9_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowSaturatedColorSelect(_OSD_WINDOW_9, 64, 128, 192);
}

//--------------------------------------------------
// Description  : Test window 0, 5, 6, 7, 8, 9 gradient level extension function
//                Delete win 7 gradient function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowGradientLevelExtension(bit bEnable)
{
    /*
    void ScalerQC_OSDSetGradient(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucWindowColor, BYTE ucGradStep, BYTE ucGradLevel,
                                bit bPolarity_R, bit bPolarity_G,
                                bit bPolarity_B, bit bEnable_R,
                                bit bEnable_G, bit bEnable_B,
                                bit bEnableSaturated, bit bEnableReversed,
                                bit bLevelExtension, bit bGradientDirection,
                                WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
    */

    // Window 0
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_0, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _ENABLE, _ENABLE, _DISABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_256, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_0_X_START), Y_START(_OSD_WINDOW_0_Y_START), X_END(_OSD_WINDOW_0_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_0_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientLevel(_OSD_WINDOW_0, 10, 10, 10);

    // Window 5
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_5, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _DISABLE, _ENABLE, _ENABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_256, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_5_X_START), Y_START(_OSD_WINDOW_5_Y_START), X_END(_OSD_WINDOW_5_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientLevel(_OSD_WINDOW_5, 20, 20, 20);

    // Window 6
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_6, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _ENABLE, _DISABLE, _ENABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_256, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_6_X_START), Y_START(_OSD_WINDOW_6_Y_START), X_END(_OSD_WINDOW_6_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_6_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientLevel(_OSD_WINDOW_6, 30, 30, 30);

    // Window 7
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_7, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _ENABLE, _ENABLE, _DISABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_256, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_7_X_START), Y_START(_OSD_WINDOW_7_Y_START), X_END(_OSD_WINDOW_7_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_7_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientLevel(_OSD_WINDOW_7, 40, 40, 40);

    // Window 8
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_8, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _DISABLE, _ENABLE, _ENABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_256, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_8_X_START), Y_START(_OSD_WINDOW_8_Y_START), X_END(_OSD_WINDOW_8_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_8_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientLevel(_OSD_WINDOW_8, 50, 50, 50);

    // Window 9
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_9, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _ENABLE, _DISABLE, _ENABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_256, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_9_X_START), Y_START(_OSD_WINDOW_9_Y_START), X_END(_OSD_WINDOW_9_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_9_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientLevel(_OSD_WINDOW_9, 60, 60, 60);
}

//--------------------------------------------------
// Description  : Set window gradient
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDSetGradient(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucWindowColor,
    BYTE ucGradStep, BYTE ucGradLevel, bit bPolarity_R, bit bPolarity_G, bit bPolarity_B, bit bEnable_R,
    bit bEnable_G, bit bEnable_B, bit bEnableSaturated, bit bEnableReversed, bit bLevelExtension,
    bit bGradientDirection, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
{
    SET_OSD_WINDOW_NUMBER(enumOsdWindowsType);
    SET_OSD_WINDOW_ENABLE(bEnable);
    SET_OSD_WINDOW_COLOR(ucWindowColor);
    SET_OSD_WINDOW_GRADIENT_LEVEL_SETP(ucGradStep);
    SET_OSD_WINDOW_GRADIENT_LEVEL_PER(ucGradLevel);
    SET_OSD_WINDOW_GRADIENT_POLARITY_R(bPolarity_R);
    SET_OSD_WINDOW_GRADIENT_POLARITY_G(bPolarity_G);
    SET_OSD_WINDOW_GRADIENT_POLARITY_B(bPolarity_B);
    SET_OSD_WINDOW_GRADIENT_ENABLE_R(bEnable_R);
    SET_OSD_WINDOW_GRADIENT_ENABLE_G(bEnable_G);
    SET_OSD_WINDOW_GRADIENT_ENABLE_B(bEnable_B);
    SET_OSD_WINDOW_REFERENCE_DELAY(_OSD_FIRST_DELAY);
    SET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_MODE(bEnableSaturated);
    SET_OSD_WINDOW_GRADIENT_REVERSED_COLOR_MODE(bEnableReversed);
    SET_OSD_WINDOW_GRADIENT_LEVEL_EXTENSION(bLevelExtension);
    SET_OSD_WINDOW_GRADIENT_ENABLE(bEnable);
    SET_OSD_WINDOW_GRADIENT_DIRECTION(bGradientDirection);
    ScalerOsdDrawWindow(usXStart, usYStart, usXEnd, usYEnd);

    // close window
    if(bEnable != _ENABLE)
    {
        ScalerOsdWindowDisable(enumOsdWindowsType);
    }
}

//--------------------------------------------------
// Description  : Test alpha blending type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDAlphaBlendingType(bit bEnable, EnumOsdTransparencyType enumOsdTransparencyType)
{
    SET_OSD_WINDOW_BLEND_ENABLE(bEnable);
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_2, 2, X_START(_OSD_WINDOW_2_X_START), Y_START(_OSD_WINDOW_2_Y_START), X_END(_OSD_WINDOW_2_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_2_Y_START + _OSD_WINDOW_HEIGHT));
    SET_OSD_WINDOW_BLEND_ENABLE(bEnable);
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_3, 3, X_START(_OSD_WINDOW_3_X_START), Y_START(_OSD_WINDOW_3_Y_START), X_END(_OSD_WINDOW_3_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_3_Y_START + _OSD_WINDOW_HEIGHT));
    SET_OSD_WINDOW_BLEND_ENABLE(bEnable);
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4, 4, X_START(_OSD_WINDOW_4_X_START), Y_START(_OSD_WINDOW_4_Y_START), X_END(_OSD_WINDOW_4_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_Y_START + _OSD_WINDOW_HEIGHT));

    ScalerOsdSetTransparencyType(enumOsdTransparencyType);
}

//--------------------------------------------------
// Description  : Clear font map with 1-bit font
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDFuncClear(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight)
{
    BYTE xdata ucIdx = 0;

    for(ucIdx = 0; ucIdx < ucHeight; ucIdx++)
    {
        ScalerOsdSramAddressCount(ucRow + ucIdx, ucCol, _OSD_BYTEALL);
        ScalerOsdBurstWriteDataPort(tQCClearTableData, (ucLength * 3), GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_FLASH);
    }
}

//--------------------------------------------------
// Description  : Test window 8, 9, 4-1 ~ 4-8 chessboard function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowChessboard(bit bEnable)
{
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_8, 8, X_START(_OSD_WINDOW_8_X_START), Y_START(_OSD_WINDOW_8_Y_START), X_END(_OSD_WINDOW_8_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_8_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_9, 9, X_START(_OSD_WINDOW_9_X_START), Y_START(_OSD_WINDOW_9_Y_START), X_END(_OSD_WINDOW_9_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_9_Y_START + _OSD_WINDOW_HEIGHT));
    // Window 4-1 ~ 4-8
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4_1, 10, X_START(_OSD_WINDOW_4_1_X_START), Y_START(_OSD_WINDOW_4_1_Y_START), X_END(_OSD_WINDOW_4_1_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_1_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4_2, 11, X_START(_OSD_WINDOW_4_2_X_START), Y_START(_OSD_WINDOW_4_2_Y_START), X_END(_OSD_WINDOW_4_2_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_2_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4_3, 12, X_START(_OSD_WINDOW_4_3_X_START), Y_START(_OSD_WINDOW_4_3_Y_START), X_END(_OSD_WINDOW_4_3_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_3_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4_4, 13, X_START(_OSD_WINDOW_4_4_X_START), Y_START(_OSD_WINDOW_4_4_Y_START), X_END(_OSD_WINDOW_4_4_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_4_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4_5, 14, X_START(_OSD_WINDOW_4_5_X_START), Y_START(_OSD_WINDOW_4_5_Y_START), X_END(_OSD_WINDOW_4_5_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_5_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4_6, 15, X_START(_OSD_WINDOW_4_6_X_START), Y_START(_OSD_WINDOW_4_6_Y_START), X_END(_OSD_WINDOW_4_6_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_6_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4_7, 16, X_START(_OSD_WINDOW_4_7_X_START), Y_START(_OSD_WINDOW_4_7_Y_START), X_END(_OSD_WINDOW_4_7_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_7_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4_8, 17, X_START(_OSD_WINDOW_4_8_X_START), Y_START(_OSD_WINDOW_4_8_Y_START), X_END(_OSD_WINDOW_4_8_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_8_Y_START + _OSD_WINDOW_HEIGHT));

    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_8, 1, 16);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_9, 3, 22);
    // Window 4-1 ~ 4-8
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_4_1, 5, 6);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_4_2, 23, 24);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_4_3, 28, 32);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_4_4, 34, 42);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_4_5, 43, 41);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_4_6, 48, 62);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_4_7, 55, 56);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_4_8, 57, 63);

    // Window 5-1 ~ 5-8
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_5_1, 10, X_START(_OSD_WINDOW_5_1_X_START), Y_START(_OSD_WINDOW_5_1_Y_START), X_END(_OSD_WINDOW_5_1_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_1_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_5_2, 11, X_START(_OSD_WINDOW_5_2_X_START), Y_START(_OSD_WINDOW_5_2_Y_START), X_END(_OSD_WINDOW_5_2_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_2_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_5_3, 12, X_START(_OSD_WINDOW_5_3_X_START), Y_START(_OSD_WINDOW_5_3_Y_START), X_END(_OSD_WINDOW_5_3_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_3_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_5_4, 13, X_START(_OSD_WINDOW_5_4_X_START), Y_START(_OSD_WINDOW_5_4_Y_START), X_END(_OSD_WINDOW_5_4_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_4_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_5_5, 14, X_START(_OSD_WINDOW_5_5_X_START), Y_START(_OSD_WINDOW_5_5_Y_START), X_END(_OSD_WINDOW_5_5_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_5_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_5_6, 15, X_START(_OSD_WINDOW_5_6_X_START), Y_START(_OSD_WINDOW_5_6_Y_START), X_END(_OSD_WINDOW_5_6_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_6_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_5_7, 16, X_START(_OSD_WINDOW_5_7_X_START), Y_START(_OSD_WINDOW_5_7_Y_START), X_END(_OSD_WINDOW_5_7_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_7_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_5_8, 17, X_START(_OSD_WINDOW_5_8_X_START), Y_START(_OSD_WINDOW_5_8_Y_START), X_END(_OSD_WINDOW_5_8_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_8_Y_START + _OSD_WINDOW_HEIGHT));

    // Window 5-1 ~ 5-8
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_5_1, 5, 6);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_5_2, 23, 24);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_5_3, 28, 32);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_5_4, 34, 42);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_5_5, 43, 41);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_5_6, 48, 62);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_5_7, 55, 56);
    ScalerOsdWindowChessboard(bEnable, _OSD_WINDOW_5_8, 57, 63);
}

//--------------------------------------------------
// Description  : Test window 4-1 ~ 4-3 highlight function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowHighlight(bit bEnable)
{
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4_1, 10, X_START(_OSD_WINDOW_4_1_X_START), Y_START(_OSD_WINDOW_4_1_Y_START), X_END(_OSD_WINDOW_4_1_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_1_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4_2, 11, X_START(_OSD_WINDOW_4_2_X_START), Y_START(_OSD_WINDOW_4_2_Y_START), X_END(_OSD_WINDOW_4_2_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_2_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_4_3, 12, X_START(_OSD_WINDOW_4_3_X_START), Y_START(_OSD_WINDOW_4_3_Y_START), X_END(_OSD_WINDOW_4_3_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_3_Y_START + _OSD_WINDOW_HEIGHT));

    ScalerOsdWindowHighlightFunction(bEnable, _OSD_WINDOW_4_1, 16, 3, 9);
    ScalerOsdWindowHighlightFunction(bEnable, _OSD_WINDOW_4_2, 23, 24, 5);
    ScalerOsdWindowHighlightFunction(bEnable, _OSD_WINDOW_4_3, 48, 49, 8);
}

//--------------------------------------------------
// Description  : Test window shadow border
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowShadowBorder(bit bEnable)
{
    // button type shadow 1
    ScalerQC_OSDSetShadowBorder(bEnable, _OSD_WINDOW_4_1, 0, 48, 49, WIDTH(7), HEIGHT(7), _OSD_WINDOW_BUTTON_TYPE_SHADOW_1,
    X_START(_OSD_WINDOW_4_1_X_START), Y_START(_OSD_WINDOW_4_1_Y_START), X_END(_OSD_WINDOW_4_1_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_1_Y_START + _OSD_WINDOW_HEIGHT));
    // button type shadow 2
    ScalerQC_OSDSetShadowBorder(bEnable, _OSD_WINDOW_4_2, 1, 50, 51, WIDTH(6), HEIGHT(6), _OSD_WINDOW_BUTTON_TYPE_SHADOW_2,
    X_START(_OSD_WINDOW_4_2_X_START), Y_START(_OSD_WINDOW_4_2_Y_START), X_END(_OSD_WINDOW_4_2_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_2_Y_START + _OSD_WINDOW_HEIGHT));
    // button type shadow 3
    ScalerQC_OSDSetShadowBorder(bEnable, _OSD_WINDOW_4_3, 2, 52, 53, WIDTH(5), HEIGHT(5), _OSD_WINDOW_BUTTON_TYPE_SHADOW_3,
    X_START(_OSD_WINDOW_4_3_X_START), Y_START(_OSD_WINDOW_4_3_Y_START), X_END(_OSD_WINDOW_4_3_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_3_Y_START + _OSD_WINDOW_HEIGHT));
    // button type shadow 4
    ScalerQC_OSDSetShadowBorder(bEnable, _OSD_WINDOW_4_4, 3, 54, 55, WIDTH(4), HEIGHT(4), _OSD_WINDOW_BUTTON_TYPE_SHADOW_4,
    X_START(_OSD_WINDOW_4_4_X_START), Y_START(_OSD_WINDOW_4_4_Y_START), X_END(_OSD_WINDOW_4_4_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_4_Y_START + _OSD_WINDOW_HEIGHT));
    // button type 3D 1
    ScalerQC_OSDSetShadowBorder(bEnable, _OSD_WINDOW_4_5, 4, 56, 57, WIDTH(3), HEIGHT(3), _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_1,
    X_START(_OSD_WINDOW_4_5_X_START), Y_START(_OSD_WINDOW_4_5_Y_START), X_END(_OSD_WINDOW_4_5_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_5_Y_START + _OSD_WINDOW_HEIGHT));
    // button type 3D 2
    ScalerQC_OSDSetShadowBorder(bEnable, _OSD_WINDOW_4_6, 5, 58, 59, WIDTH(2), HEIGHT(2), _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_2,
    X_START(_OSD_WINDOW_4_6_X_START), Y_START(_OSD_WINDOW_4_6_Y_START), X_END(_OSD_WINDOW_4_6_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_6_Y_START + _OSD_WINDOW_HEIGHT));
    // button type border
    ScalerQC_OSDSetShadowBorder(bEnable, _OSD_WINDOW_4_7, 6, 60, 61, WIDTH(1), HEIGHT(1), _OSD_WINDOW_BUTTON_TYPE_BORDER,
    X_START(_OSD_WINDOW_4_7_X_START), Y_START(_OSD_WINDOW_4_7_Y_START), X_END(_OSD_WINDOW_4_7_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_7_Y_START + _OSD_WINDOW_HEIGHT));
    // button type reserved
    ScalerQC_OSDSetShadowBorder(bEnable, _OSD_WINDOW_4_8, 7, 62, 63, WIDTH(0), HEIGHT(0), _OSD_WINDOW_BUTTON_TYPE_RESERVED,
    X_START(_OSD_WINDOW_4_8_X_START), Y_START(_OSD_WINDOW_4_8_Y_START), X_END(_OSD_WINDOW_4_8_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_4_8_Y_START + _OSD_WINDOW_HEIGHT));
}

//--------------------------------------------------
// Description  : Set window shadow border button
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDSetShadowBorder(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucWindowColor,
    BYTE ucShadowColor, BYTE ucBorderColor, BYTE ucWidth, BYTE ucHeight, BYTE ucButtonType,
    WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
{
    SET_OSD_WINDOW_NUMBER(enumOsdWindowsType);
    SET_OSD_WINDOW_ENABLE(bEnable);
    SET_OSD_WINDOW_COLOR(ucWindowColor);
    SET_OSD_WINDOW_COLOR_SHADOW(ucShadowColor);
    SET_OSD_WINDOW_COLOR_BORDER(ucBorderColor);
    SET_OSD_WINDOW_SHADOW_BORDER_PIXEL_WIDTH(ucWidth);
    SET_OSD_WINDOW_SHADOW_BORDER_PIXEL_HEIGHT(ucHeight);
    SET_OSD_WINDOW_REFERENCE_DELAY(_OSD_FIRST_DELAY);
    SET_OSD_WINDOW_BUTTON_ENABLE(bEnable);
    SET_OSD_WINDOW_BUTTON_TYPE(ucButtonType);
    ScalerOsdDrawWindow(usXStart, usYStart, usXEnd, usYEnd);

    // close window
    if(bEnable != _ENABLE)
    {
        ScalerOsdWindowDisable(enumOsdWindowsType);
    }
}

//--------------------------------------------------
// Description  : Test window 6 special function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindow6SpecialFunction(bit bEnable, EnumOsdWindow6FunctionType enumOsdWindow6FunctionType)
{
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_6, 6, X_START(10), Y_START(0), X_END(10 + _OSD_WINDOW_WIDTH), Y_END(0 + _OSD_WINDOW_HEIGHT));

    ScalerOsdWindow6SpecialFunction(enumOsdWindow6FunctionType);
}
//--------------------------------------------------
// Description  : Test window 7 special function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindow7SpecialFunction(bit bEnable, EnumOsdWindow7FunctionType enumOsdWindow7FunctionType)
{
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_7, 7, X_START(30 + _OSD_WINDOW_WIDTH), Y_START(0), X_END(30 + _OSD_WINDOW_WIDTH + _OSD_WINDOW_WIDTH), Y_END(0 + _OSD_WINDOW_HEIGHT));

    ScalerOsdWindow7SpecialFunction(enumOsdWindow7FunctionType);
}

//--------------------------------------------------
// Description  : Test window 4-1 ~ 4-8 border priority
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowBorderPriority(bit bEnable, bit bBorderEnable)
{
    BYTE ucIdx = 0;

    ScalerOsdPosition(_OSD_POSITION_FONT_B, X_POS(0), Y_POS(_OSD_WINDOW_OFFSET_X + 50));

    for(ucIdx = 0; ucIdx < 8; ucIdx++)
    {
        SET_OSD_WINDOW_BORDER_PRIORITY(bBorderEnable);

        /*
            void ScalerQC_OSDSetShadowBorder(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucWindowColor,
            BYTE ucShadowColor, BYTE ucBorderColor, BYTE ucWidth, BYTE ucHeight, BYTE ucButtonType,
            WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
        */

        // Window 4-1 ~ 4-8
        ScalerQC_OSDSetShadowBorder(bEnable, (_OSD_WINDOW_4_1 + ucIdx), 0,
                                    (8 + (ucIdx * 5)), (8 + (ucIdx * 5)), WIDTH(0), HEIGHT(0), _OSD_WINDOW_BUTTON_TYPE_BORDER,
                                    X_START(10 + (ucIdx * 84)), Y_START(50 + _OSD_WINDOW_OFFSET_X), X_END(0 + 93 + (ucIdx * 84)), Y_END(50 + _OSD_WINDOW_OFFSET_X + 62));


        SET_OSD_WINDOW_BORDER_PRIORITY(bBorderEnable);

        // Window 5-1 ~ 5-8
        ScalerQC_OSDSetShadowBorder(bEnable, (_OSD_WINDOW_5_1 + ucIdx), 0,
                                    (8 + (ucIdx * 5)), (8 + (ucIdx * 5)), WIDTH(0), HEIGHT(0), _OSD_WINDOW_BUTTON_TYPE_BORDER,
                                    X_START(10 + (ucIdx * 84)), Y_START(50 + _OSD_WINDOW_OFFSET_X + 65), X_END(0 + 93 + (ucIdx * 84)), Y_END(50 + _OSD_WINDOW_OFFSET_X + 65 * 2));
    }
}

//--------------------------------------------------
// Description  : Test window 2, 3, 4, 8, 9 priority higher than font
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowFontPriority(bit bEnable, EnumOsdWindowPriorityType enumOsdWindowPriorityType)
{
    BYTE ucIdx = 0;

    for(ucIdx = 0; ucIdx < 5; ucIdx++)
    {
        ScalerQC_OSDDrawWindow(bEnable, (tQCFONT_WINDOW_PRIORITY[ucIdx]), (2 + ucIdx * 9), X_START(10 + (ucIdx * 84)), Y_START(50 + _OSD_WINDOW_OFFSET_Y), X_END(0 + 93 + (ucIdx * 84)), Y_END(50 + _OSD_WINDOW_OFFSET_X + 150));
    }
    ScalerOsdWindowPriority(_OSD_WINDOW_2, enumOsdWindowPriorityType);
    ScalerOsdWindowPriority(_OSD_WINDOW_3, enumOsdWindowPriorityType);
    ScalerOsdWindowPriority(_OSD_WINDOW_4, enumOsdWindowPriorityType);
    ScalerOsdWindowPriority(_OSD_WINDOW_8, enumOsdWindowPriorityType);
    ScalerOsdWindowPriority(_OSD_WINDOW_9, enumOsdWindowPriorityType);
}

//--------------------------------------------------
// Description  : Test window gray level function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowGrayLevel(bit bEnable)
{
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_0, 15, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_1,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _ENABLE, _ENABLE, _ENABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(50), Y_START(450), X_END(50 + 1400), Y_END(450 + 200));
    ScalerOsdWindowGrayLevel(bEnable, _OSD_WINDOW_0, 5, 4);
}

//--------------------------------------------------
// Description  : Test window 0, 5, 6, 8, 9 gradient step extension function
//                Delete window 7 gradient function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowGradientStepExtension(bit bEnable)
{
    // Window 0
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_0, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _ENABLE, _ENABLE, _DISABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_0_X_START), Y_START(_OSD_WINDOW_0_Y_START), X_END(_OSD_WINDOW_0_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_0_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientStep(bEnable, _OSD_WINDOW_0, 10);

    // Window 5
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_5, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _DISABLE, _ENABLE, _ENABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_5_X_START), Y_START(_OSD_WINDOW_5_Y_START), X_END(_OSD_WINDOW_5_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_5_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientStep(bEnable, _OSD_WINDOW_5, 20);

    // Window 6
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_6, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _ENABLE, _DISABLE, _ENABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_6_X_START), Y_START(_OSD_WINDOW_6_Y_START), X_END(_OSD_WINDOW_6_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_6_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientStep(bEnable, _OSD_WINDOW_6, 40);

    // Window 7
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_7, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _ENABLE, _ENABLE, _DISABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_7_X_START), Y_START(_OSD_WINDOW_7_Y_START), X_END(_OSD_WINDOW_7_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_7_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientStep(bEnable, _OSD_WINDOW_7, 80);

    // Window 8
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_8, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _DISABLE, _ENABLE, _ENABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_8_X_START), Y_START(_OSD_WINDOW_8_Y_START), X_END(_OSD_WINDOW_8_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_8_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientStep(bEnable, _OSD_WINDOW_8, 160);

    // Window 9
    ScalerQC_OSDSetGradient(bEnable, _OSD_WINDOW_9, 44, _OSD_WINDOW_GRADIENT_LEVEL_STEP_4, _OSD_WINDOW_GRADIENT_LEVEL_PER_4,
    _OSD_WINDOW_GRADIENT_POLARITY_DECREASE, _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,
    _OSD_WINDOW_GRADIENT_POLARITY_INCREASE, _ENABLE, _DISABLE, _ENABLE,
    _DISABLE, _DISABLE,
    _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8, _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,
    X_START(_OSD_WINDOW_9_X_START), Y_START(_OSD_WINDOW_9_Y_START), X_END(_OSD_WINDOW_9_X_START + _OSD_WINDOW_WIDTH), Y_END(_OSD_WINDOW_9_Y_START + _OSD_WINDOW_HEIGHT));
    ScalerOsdWindowGradientStep(bEnable, _OSD_WINDOW_9, 255);
}

//--------------------------------------------------
// Description  : Test window 0, 5, 6, 7, 8, 9 special color mask with gradient pattern gen
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDWindowSpecialColorMask(bit bEnable)
{
    // set gradient pattern gen
    ScalerSetByte(P7_F0_DISP_PG_R_CTRL, 0x81); // 0x07F0
    ScalerSetByte(P7_F1_DISP_PG_G_CTRL, 0x01);
    ScalerSetByte(P7_F2_DISP_PG_B_CTRL, 0x01);
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, 0x00);
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, 0x00);
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, 0x00);
    ScalerSetByte(P7_F6_DISP_PG_PIXEL_DELTA_H, 0x01);
    ScalerSetByte(P7_F7_DISP_PG_LINE_DELTA_H, 0x00);
    ScalerSetByte(P7_F8_DISP_PG_PIXEL_STEP_H, 0x02);

    ScalerSetByte(P7_F9_DISP_PG_LINE_STEP_H, 0x00);
    ScalerSetByte(P7_FA_DISP_PG_DELTA_H_STEP_M, 0x00);

    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_0, 15, X_START(0), Y_START(0), X_END(3840), Y_END(165));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_5, 27, X_START(0), Y_START(165), X_END(3840), Y_END(2 * 165));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_6, 18, X_START(0), Y_START(2 * 165), X_END(3840), Y_END(3 * 165));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_7, 15, X_START(0), Y_START(3 * 165), X_END(3840), Y_END(4 * 165));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_8, 27, X_START(0), Y_START(4 * 165), X_END(3840), Y_END(5 * 165));
    ScalerQC_OSDDrawWindow(bEnable, _OSD_WINDOW_9, 18, X_START(0), Y_START(5 * 165), X_END(3840), Y_END(6 * 165));

    ScalerOsdWindowSpecialColorMask(bEnable, _OSD_WINDOW_0, _OSD_SPECIAL_COLOR_MASK_AND_OPERATION);
    ScalerOsdWindowSpecialColorMask(bEnable, _OSD_WINDOW_5, _OSD_SPECIAL_COLOR_MASK_AND_OPERATION);
    ScalerOsdWindowSpecialColorMask(bEnable, _OSD_WINDOW_6, _OSD_SPECIAL_COLOR_MASK_AND_OPERATION);
    ScalerOsdWindowSpecialColorMask(bEnable, _OSD_WINDOW_7, _OSD_SPECIAL_COLOR_MASK_OR_OPERATION);
    ScalerOsdWindowSpecialColorMask(bEnable, _OSD_WINDOW_8, _OSD_SPECIAL_COLOR_MASK_OR_OPERATION);
    ScalerOsdWindowSpecialColorMask(bEnable, _OSD_WINDOW_9, _OSD_SPECIAL_COLOR_MASK_OR_OPERATION);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerQC_OSDLoadFontAddress(WORD usOffset)
{
    WORD xdata usAddr = 0;
    BYTE xdata ucSwapType = 0x00;

    usAddr = usOffset * 9;
    usAddr += _OSD_MAP_FONT_BASE_ADDRESS;

    ScalerOsdSramAddressSet(usAddr, _OSD_BYTEALL);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerQC_OSDPutStringProp(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucLanguage, BYTE *pucArray)
{
    bit bEndFlag = 0;
    BYTE xdata pucpTemp[27] = {0};
    BYTE *pucFontTable = 0;
    WORD usDataAddress = 0;

    pData[2] = 0;
    pData[3] = 0;
    pData[4] = 0;
    pData[5] = 0;
    pData[6] = 0;
    pData[7] = 0;
    pData[8] = 0;
    pData[9] = 0;
    PDATA_WORD(6) = 0;
    PDATA_WORD(7) = 0;

    pData[0] = ucLanguage;

    while(pData[0] != 0)
    {
        if(*pucArray == _END_)
        {
            pData[0]--;
        }
        pucArray++;
    }

    usDataAddress = g_ucQCOSDFontPointer0;

    // reorder
    SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT6);
    SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~(_BIT7 | _BIT5)));

    while(*(pucArray + pData[2]) != _END_)
    {
        switch(*(pucArray + pData[2]))
        {
            case _END_:
                bEndFlag = 1;
                break;

            default:

                pData[3] = *(pucArray + pData[2]);
                if(pData[3] >= _GLOBAL_FONT_END)
                {
                    pucFontTable = tOSD_TABLE_LANGUAGE_FONT_BODY[ucLanguage + 1];
                    pData[4] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[3] - _GLOBAL_FONT_END];
                }
                else
                {
                    pucFontTable = tOSD_TABLE_LANGUAGE_FONT_BODY[0];
                    pData[4] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[3]];
                }
                pData[2]++;
                break;
        }

        if(pData[5] == 0)
        {
            pData[5] = pData[4];
        }
        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT3);    // first bits shift direction: left shift
        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~_BIT2)); // left bits shift direction: rigth shift
        SCALEROSD_FONT_ROTATE_1_2_BITS_SHIFT_SET(((pData[4] - pData[5]) << 4) | pData[5]); // first bits shift and second bits shift

        pData[6] = pData[2];
        pData[7] = pData[5];

        for(pData[0] = 0; pData[0] < 9; pData[0]++)
        {
            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT0); // restart from last three bytes

            if(pData[3] >= _GLOBAL_FONT_END)
            {
                pucFontTable = tOSD_TABLE_LANGUAGE_FONT_BODY[ucLanguage + 1];
            }
            else
            {
                pucFontTable = tOSD_TABLE_LANGUAGE_FONT_BODY[0];
            }

            if(pucFontTable == tOSD_TABLE_LANGUAGE_FONT_BODY[0])
            {
                PDATA_WORD(6) = pData[3] * 27 + pData[0] * 3;
            }
            else
            {
                PDATA_WORD(6) = (pData[3] - _GLOBAL_FONT_END) * 27 + pData[0] * 3;
            }

            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6)));
            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 1));
            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 2));

            pData[2] = pData[6];
            pData[5] = pData[7];

            if((pData[5] == 12) || (*(pucArray + pData[2]) == _END_))
            {
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
            }
            else
            {
                pData[8] = *(pucArray + pData[2]);
                if(pData[8] >= _GLOBAL_FONT_END)
                {
                    pucFontTable = tOSD_TABLE_LANGUAGE_FONT_BODY[ucLanguage + 1];
                    pData[4] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[8] - _GLOBAL_FONT_END];
                }
                else
                {
                    pucFontTable = tOSD_TABLE_LANGUAGE_FONT_BODY[0];
                    pData[4] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[8]];
                }

                pData[2] ++;

                if(pucFontTable == tOSD_TABLE_LANGUAGE_FONT_BODY[0])
                {
                    PDATA_WORD(6) = pData[8] * 27 + pData[0] * 3;
                }
                else
                {
                    PDATA_WORD(6) = (pData[8] - _GLOBAL_FONT_END) * 27 + pData[0] * 3;
                }

                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6)));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 1));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 2));

                pData[5] += pData[4];
            }

            while((pData[5] < 12) && *(pucArray + pData[2]) != _END_)
            {
                SCALEROSD_FONT_ROTATE_3_L_BITS_SHIFT_SET((pData[5] << 4) | pData[5]); // third bits shift and left bits shift

                switch(*(pucArray + pData[2]))
                {
                    case _END_:
                        bEndFlag = 1;
                        break;

                    default:

                        pData[8] = *(pucArray + pData[2]);

                        if(pData[8] >= _GLOBAL_FONT_END)
                        {
                            pucFontTable = tOSD_TABLE_LANGUAGE_FONT_BODY[ucLanguage + 1];
                            pData[4] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[8] - _GLOBAL_FONT_END];
                        }
                        else
                        {
                            pucFontTable = tOSD_TABLE_LANGUAGE_FONT_BODY[0];
                            pData[4] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[8]];
                        }
                        pData[2] ++;
                        break;
                }

                pData[5] += pData[4];

                if(pucFontTable == tOSD_TABLE_LANGUAGE_FONT_BODY[0])
                {
                    PDATA_WORD(6) = pData[8] * 27 + pData[0] * 3;
                }
                else
                {
                    PDATA_WORD(6) = (pData[8] - _GLOBAL_FONT_END) * 27 + pData[0] * 3;
                }

                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6)));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 1));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 2));
            }

            pucpTemp[pData[0] * 3 + 2] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            pucpTemp[pData[0] * 3 + 1] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            pucpTemp[pData[0] * 3] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
        }

        if(pData[5] <= 12)
        {
            pData[5] = 0;
        }
        else
        {
            pData[5] = pData[5] - 12;
            pData[2]--;
        }

        // Write the pro font data to sram
        if(ucFptsSelect == 0)
        {
            ScalerQC_OSDLoadFontAddress(g_ucQCOSDFontPointer0);

            if(g_ucQCOSDFontPointer0 >= g_ucQCOSDFontPointer0Max)
            {
                g_ucQCOSDFontPointer0 = _PFONT_0_MIN_POS;
            }
            else
            {
                g_ucQCOSDFontPointer0++;
            }
        }
        ScalerOsdBurstWriteDataPort(pucpTemp, 27, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);

        ScalerOsdFrameControlByte(0x007, _OSD_BYTE2, 0x00);

        ScalerOsdScrambleLoadFontAddrHsbClr();

        pData[9]++; // Record the length of prop string

    } // End of while(*(pucArray + stringcnt) != _END_)

    // Increase the sram address pointer
    ScalerOsdSramAddressCount(ucRow, ucCol, _OSD_BYTE1);

    for(pData[10] = 0; pData[10] < pData[9]; pData[10]++)
    {
        ScalerOsdDataPort(usDataAddress);

        if(usDataAddress >= g_ucQCOSDFontPointer0Max)
        {
            usDataAddress = _PFONT_0_MIN_POS;
        }
        else
        {
            usDataAddress++;
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerQC_OSDTableLoadText(BYTE ucRow, BYTE ucCol, BYTE ucPFontType, BYTE ucLanguage, BYTE ucStringType)
{
    switch(ucStringType)
    {
        case 0:
            ScalerQC_OSDPutStringProp(ucRow, ucCol, ucPFontType, ucLanguage, tOSD_QCTABLE_LANGUAGE_TEXT[0]);
            break;
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Test OSD decode non-compressed data, osd reorder
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDReorder(void)
{
    ScalerQC_OSDTableLoadText(ROW(0), COL(8), _PFONT_TYPE_0, LANGUAGE(0), TYPE(_OSD_TEXT_TEST));
    ScalerOsdChange1BitColor(ROW(0), COL(7), LENGTH(6), HEIGHT(1), FG_COLOR(0), BG_COLOR(5));
}

//--------------------------------------------------
// Description  : Set Display HStart
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDSetHStart(WORD usHStart)
{
    ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~_BIT7, _BIT7);
    // Set Main H background st/ ed (Panel size)
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usHStart) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usHStart));
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usHStart + _PANEL_DH_WIDTH) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usHStart + _PANEL_DH_WIDTH));

    // Main1 Active
    // Set Main1 H Active Start / End
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usHStart) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usHStart));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usHStart + _PANEL_DH_WIDTH) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usHStart + _PANEL_DH_WIDTH));

    ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~_BIT6, _BIT6);
    ScalerTimerPollingFlagProc(60, P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, _BIT6, 0x00);
    ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : QC OSD test frame
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDFuncFrame(BYTE ucFrameStatus)
{
    BYTE ucIdx = 0;

    ScalerOsdDisableOsd();

    switch(ucFrameStatus)
    {
        //----------------------------
        // _OSD_FRAME_1
        //----------------------------
        case _OSD_FRAME_1:
            ScalerOsd2FontFunction(_ENABLE);
            ScalerOsdSetTransparency(6);

            // SRAM
            ScalerQC_OSDReorder();

            ScalerQC_OSDBlankFont(_ENABLE, 72);
            ScalerQC_OSD1BitFontShrink(_OSD_1BIT_SHRINK_BY_MIDDLE, _CHAR_WIDTH_7);
            ScalerQC_OSD1BitColor(_ENABLE);
            ScalerQC_OSD2BitFontByte1Bit7Swap(_OSD_2BIT_CHAR_BIT7_BY_CHANGE_PALETTE);
            ScalerQC_OSDReference4BitBackground(_OSD_4BIT_BACKGROUND_TO_BYTE2);

            // Function
            ScalerOsdSpecificColorBlending(_ENABLE, 1);

            // Window
            ScalerQC_OSDWindowPriority(_ENABLE);
            break;

        //----------------------------
        // _OSD_FRAME_2
        //----------------------------
        case _OSD_FRAME_2:
            ScalerOsd2FontFunction(_ENABLE);

            // SRAM
            ScalerQC_OSDBlankFont(_DISABLE, 72);
            ScalerQC_OSD1BitFontShrink(_OSD_1BIT_SHRINK_BY_LEFT, _CHAR_WIDTH_7);
            ScalerQC_OSD2BitFontByte1Bit7Swap(_OSD_2BIT_CHAR_BIT7_BY_SELECT_FONT);
            ScalerQC_OSDReference4BitBackground(_OSD_4BIT_BACKGROUND_TO_BYTE0);
            // Window
            ScalerQC_OSDWindowGradient(_ENABLE, 0);
            ScalerQC_OSDWindowGridLine(_ENABLE, 0);
            break;

        //----------------------------
        // _OSD_FRAME_2_1 - cw270
        //----------------------------
        case _OSD_FRAME_2_1:

            // SRAM
            // clear align
            for(ucIdx = 0; ucIdx < 5; ucIdx++)
            {
                ScalerOsdSramDataValue(ROW(3 + ucIdx), COL(2 + ucIdx), LENGTH(1), 0x4C, _OSD_BYTE0);
                ScalerOsdSramDataValue(ROW(3 + ucIdx), COL(2 + ucIdx), LENGTH(1), 0x00, _OSD_BYTE1);
                ScalerOsdSramDataValue(ROW(3 + ucIdx), COL(2 + ucIdx), LENGTH(1), 0x10, _OSD_BYTE2);
            }

            ScalerQC_OSD1BitFontShrink(_OSD_1BIT_SHRINK_BY_LEFT, _CHAR_WIDTH_9);
            ScalerOsdBlankFont(ROW(2), COL(29), LENGTH(1), HEIGHT(1), VALUES(28), BG_COLOR(17), _OSD_BLANK_FONT);
            ScalerOsdBlankFont(ROW(2), COL(30), LENGTH(1), HEIGHT(1), VALUES(29), BG_COLOR(17), _OSD_BLANK_FONT);
            ScalerQC_OSD1BitColor(_DISABLE);
            ScalerQC_OSDBlankFontCw270(_ENABLE, 12);
            ScalerOsdMapRotation(_OSD_ROTATE_DEGREE_270, _OSD_MAP_A_REMAPPING_ENABLE, _OSD_MAPA_SIZE_ROW, _OSD_MAP_B_REMAPPING_ENABLE, _OSD_MAPB_SIZE_ROW, _OSD_FONT_LIB_ROTATION_ENABLE);
            ScalerOsdPosition(_OSD_POSITION_GLOBAL_B, X_POS(0 + 1 + 200), Y_POS(0 + 100));

            /* //Window align boundary for debug check
            SET_OSD_WINDOW_NUMBER(_OSD_WINDOW_0);
            SET_OSD_WINDOW_COLOR(5);
            SET_OSD_WINDOW_ENABLE(_ENABLE);
            ScalerOsdDrawWindow(X_START(0), Y_START(374), X_END(400), Y_END(383));
            */
            break;

        //----------------------------
        // _OSD_FRAME_2_2 - cw90
        //----------------------------
        case _OSD_FRAME_2_2:
            // SRAM
            ScalerQC_OSDBlankFont(_DISABLE, 30);
            ScalerQC_OSD1BitColor(_DISABLE);

            ScalerOsdMapRotation(_OSD_ROTATE_DEGREE_90, _OSD_MAP_A_REMAPPING_ENABLE, _OSD_MAPA_SIZE_ROW, _OSD_MAP_B_REMAPPING_ENABLE, _OSD_MAPB_SIZE_ROW, _OSD_FONT_LIB_ROTATION_ENABLE);
            ScalerOsdPosition(_OSD_POSITION_GLOBAL_B, X_POS(0 + 1 + 200), Y_POS(0 + 100));
            break;

        //----------------------------
        // _OSD_FRAME_2_3 - cw180
        //----------------------------
        case _OSD_FRAME_2_3:
            // SRAM
            ScalerQC_OSDBlankFont(_DISABLE, 30);
            ScalerQC_OSD1BitColor(_DISABLE);

            ScalerOsdMapRotation(_OSD_ROTATE_DEGREE_180, _OSD_MAP_A_REMAPPING_ENABLE, _OSD_MAPA_SIZE_ROW, _OSD_MAP_B_REMAPPING_ENABLE, _OSD_MAPB_SIZE_ROW, _OSD_FONT_LIB_ROTATION_ENABLE);
            break;

        //----------------------------
        // _OSD_FRAME_3
        //----------------------------
        case _OSD_FRAME_3:
            ScalerOsd2FontFunction(_DISABLE);

            // SRAM
            ScalerQC_OSD1BitFontShrink(_OSD_1BIT_SHRINK_BY_RIGHT, _CHAR_WIDTH_10);
            // function
            ScalerOsdPopOn(_ENABLE, _OSD_A);
            // window
            ScalerQC_OSDWindowGradient(_ENABLE, 1);
            ScalerQC_OSDWindowGridLine(_ENABLE, 1);
           break;

        //----------------------------
        // _OSD_FRAME_4
        //----------------------------
        case _OSD_FRAME_4:
            ScalerOsd2FontFunction(_DISABLE);
            ScalerOsdSetTransparency(5);

            // function
            ScalerOsdPopOn(_ENABLE, _OSD_B);
            ScalerOsdVerticalBoundary(_ENABLE);
            ScalerOsdVerticalBoundarySize(50, 420);
            // window
            ScalerQC_OSDWindowGradient(_ENABLE, 2);
            ScalerQC_OSDAlphaBlendingType(_ENABLE, _OSD_TRANSPARENCY_ONLY_WINDOW);
            break;

        //----------------------------
        // _OSD_FRAME_5
        //----------------------------
        case _OSD_FRAME_5:
            ScalerOsd2FontFunction(_DISABLE);
            ScalerOsdSetTransparency(4);

            // function
            ScalerOsdRollUp(_ENABLE, 8, 13);
            ScalerQC_OSDAlphaBlendingType(_ENABLE, _OSD_TRANSPARENCY_ALL);

            // window
            ScalerQC_OSDWindowGradient(_ENABLE, 3);
            break;

        //----------------------------
        // _OSD_FRAME_6
        //----------------------------
        case _OSD_FRAME_6:
            ScalerOsd2FontFunction(_ENABLE);
            ScalerOsdSetTransparency(3);
            ScalerQC_OSDFuncApplyMap(_OSD_ROTATE_DEGREE_90);
            ScalerQC_OSDFuncClear(ROW(0), COL(0), LENGTH(_OSD_MAPA_SIZE_COL), HEIGHT(_OSD_MAPA_SIZE_ROW));
            ScalerQC_OSDFuncClear(ROW_MAPB(0), COL(0), LENGTH(_OSD_MAPB_SIZE_COL), HEIGHT(_OSD_MAPB_SIZE_ROW));

            // function
            ScalerQC_OSDAlphaBlendingType(_ENABLE, _OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);

            // window
            ScalerQC_OSDWindowGradient(_ENABLE, 4);
            ScalerQC_OSDWindowChessboard(_ENABLE);
            break;

        //----------------------------
        // _OSD_FRAME_7
        //----------------------------
        case _OSD_FRAME_7:
            ScalerOsd2FontFunction(_ENABLE);
            ScalerOsdReferenceDelay(_OSD_B, _OSD_FIRST_DELAY);
            ScalerOsdPosition(_OSD_POSITION_FONT_B, X_POS(_OSD_WINDOW_4_1_X_START), Y_POS(_OSD_WINDOW_4_1_Y_START));

            // window
            ScalerQC_OSDWindowSaturatedColor(_ENABLE);
            ScalerQC_OSDWindowHighlight(_ENABLE);
            break;

        //----------------------------
        // _OSD_FRAME_8
        //----------------------------
        case _OSD_FRAME_8:
            ScalerOsd2FontFunction(_DISABLE);
			ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_QC_OSD_POSITION_OFFSET_H - 2), Y_POS(_QC_OSD_POSITION_OFFSET_V - 1));

			ScalerOsdScaleUpHorSize(0, 12 *_OSD_MAPA_SIZE_COL);
			ScalerOsdScaleUpVerSize(0, 18 *_OSD_MAPA_SIZE_ROW);
			ScalerQC_OSDScaleUp(_ENABLE, _OSD_SCALING_RATIO_150, _OSD_SCALING_BOUNDARY_NEIGHTBOOR);

            // window
            ScalerQC_OSDWindowGradientLevelExtension(_ENABLE);
            ScalerQC_OSDWindowShadowBorder(_ENABLE);
            break;

        //----------------------------
        // _OSD_FRAME_9
        //----------------------------
        case _OSD_FRAME_9:
            ScalerOsd2FontFunction(_DISABLE);
            ScalerOsdSetTransparency(2);

            // window
            ScalerQC_OSDWindow6SpecialFunction(_ENABLE, _OSD_WINDOW_6_FUNCTION_NO_BLENDING_BOTH);
            ScalerQC_OSDWindow7SpecialFunction(_ENABLE, _OSD_WINDOW_7_FUNCTION_NO_BLENDING_BOTH);
            break;

        //----------------------------
        // _OSD_FRAME_10
        //----------------------------
        case _OSD_FRAME_10:
            ScalerOsd2FontFunction(_ENABLE);
            ScalerOsdSetTransparency(1);

            // function
            ScalerQC_OSDSetHStart(128);
            ScalerOsdDoubleFunction(_OSD_DOUBLE_WIDTH_ENABLE, _OSD_DOUBLE_HEIGHT_ENABLE);
            ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_QC_OSD_DOUBLE_POSITION_OFFSET_H), Y_POS(_QC_OSD_DOUBLE_POSITION_OFFSET_V));

            // window
            ScalerQC_OSDWindow6SpecialFunction(_ENABLE, _OSD_WINDOW_6_FUNCTION_NO_BLENDING_FOREGROUND);
            ScalerQC_OSDWindow7SpecialFunction(_ENABLE, _OSD_WINDOW_7_FUNCTION_NO_BLENDING_FOREGROUND);
            ScalerQC_OSDWindowBorderPriority(_ENABLE, _ENABLE);
            break;

        //----------------------------
        // _OSD_FRAME_11
        //----------------------------
        case _OSD_FRAME_11:
            ScalerOsd2FontFunction(_ENABLE);
            ScalerOsdSetTransparency(2);

            // function
            ScalerQC_OSDSetHStart(128);
            ScalerOsdDoubleFunction(_OSD_DOUBLE_WIDTH_ENABLE, _OSD_DOUBLE_HEIGHT_ENABLE);
            ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_QC_OSD_DOUBLE_POSITION_OFFSET_H), Y_POS(_QC_OSD_DOUBLE_POSITION_OFFSET_V));

            // window
            ScalerQC_OSDWindow6SpecialFunction(_ENABLE, _OSD_WINDOW_6_FUNCTION_NO_BLENDING_BACKGROUND);
            ScalerQC_OSDWindow7SpecialFunction(_ENABLE, _OSD_WINDOW_7_FUNCTION_NO_BLENDING_BACKGROUND);
            ScalerQC_OSDWindowBorderPriority(_ENABLE, _DISABLE);
            break;

        //----------------------------
        // _OSD_FRAME_12
        //----------------------------
        case _OSD_FRAME_12:
            ScalerOsd2FontFunction(_ENABLE);
            ScalerOsdSetTransparency(3);

            // window
            ScalerQC_OSDWindow6SpecialFunction(_ENABLE, _OSD_WINDOW_6_FUNCTION_BLENDING_BOTH);
            ScalerQC_OSDWindow7SpecialFunction(_ENABLE, _OSD_WINDOW_7_FUNCTION_BLENDING_BOTH);
            ScalerQC_OSDWindowFontPriority(_ENABLE, _OSD_WINDOW_PRIORITY_HIGHTER_THAN_FONT);
            break;

        //----------------------------
        // _OSD_FRAME_13
        //----------------------------
        case _OSD_FRAME_13:
            ScalerOsd2FontFunction(_ENABLE);
            ScalerOsdSetTransparency(4);

            // window
            ScalerQC_OSDWindow7SpecialFunction(_ENABLE, _OSD_WINDOW_7_FUNCTION_MASK_REGION_TRANSPARENT_ALL);
            ScalerQC_OSDWindowFontPriority(_ENABLE, _OSD_WINDOW_PRIORITY_LOWER_THAN_FONT);
            break;

        //----------------------------
        // _OSD_FRAME_14
        //----------------------------
        case _OSD_FRAME_14:
            ScalerOsd2FontFunction(_DISABLE);
            ScalerOsdSetTransparency(5);
            ScalerOsdChange1BitColor(ROW(0), COL(0), LENGTH(32), HEIGHT(5), FG_COLOR(1), BG_COLOR(0));
            ScalerQC_OSDDrawWindow(_ENABLE, _OSD_WINDOW_5, 5, X_START(10), Y_START(0), X_END(30 + _OSD_WINDOW_WIDTH + _OSD_WINDOW_WIDTH), Y_END(0 + _OSD_WINDOW_HEIGHT));

            // function
            ScalerOsdHorizontalDelayStep(_OSD_HORIZONTAL_DELAY_STEP_1_PIXEL);

            // window
            ScalerQC_OSDWindow7SpecialFunction(_ENABLE, _OSD_WINDOW_7_FUNCTION_MASK_REGION_APPEAR);
            break;

        //----------------------------
        // _OSD_FRAME_15
        //----------------------------
        case _OSD_FRAME_15:
            ScalerOsd2FontFunction(_DISABLE);
            ScalerOsdSetTransparency(6);
            ScalerOsdChange1BitColor(ROW(0), COL(0), LENGTH(32), HEIGHT(5), FG_COLOR(1), BG_COLOR(0));
            ScalerQC_OSDDrawWindow(_ENABLE, _OSD_WINDOW_5, 5, X_START(10), Y_START(0), X_END(30 + _OSD_WINDOW_WIDTH + _OSD_WINDOW_WIDTH), Y_END(0 + _OSD_WINDOW_HEIGHT));

            // window
            ScalerQC_OSDWindow7SpecialFunction(_ENABLE, _OSD_WINDOW_7_FUNCTION_MASK_REGION_TRANSPARENT_FONT);
            break;

        //----------------------------
        // _OSD_FRAME_16
        //----------------------------
         case _OSD_FRAME_16:
            ScalerOsd2FontFunction(_DISABLE);
            // window
            ScalerOsdWindowDisable(_OSD_WINDOW_7);
            ScalerQC_OSDWindowGrayLevel(_ENABLE);
            break;

        //----------------------------
        // _OSD_FRAME_17
        //----------------------------
        case _OSD_FRAME_17:
            ScalerOsd2FontFunction(_DISABLE);
			ScalerOsdPosition(_OSD_POSITION_FONT_A, X_POS(0), Y_POS(500));
			ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_QC_OSD_POSITION_OFFSET_H - 2), Y_POS(_QC_OSD_POSITION_OFFSET_V - 1));

			ScalerOsdScaleUpHorSize(0, 12 *_OSD_MAPA_SIZE_COL);
			ScalerOsdScaleUpVerSize(500, 18 *_OSD_MAPA_SIZE_ROW);
            ScalerQC_OSDScaleUp(_ENABLE, _OSD_SCALING_RATIO_200, _OSD_SCALING_BOUNDARY_THIN);

            // window
            ScalerQC_OSDWindowGradientStepExtension(_ENABLE);
            break;

        //----------------------------
        // _OSD_FRAME_18
        //----------------------------
        case _OSD_FRAME_18:
            ScalerOsd2FontFunction(_DISABLE);
            ScalerQC_OSDScaleUp(_ENABLE, _OSD_SCALING_RATIO_250, _OSD_SCALING_BOUNDARY_FAT);

            // window
            ScalerQC_OSDWindowSpecialColorMask(_ENABLE);
            break;

        //----------------------------
        // _OSD_FRAME_19
        //----------------------------
        case _OSD_FRAME_19:
            ScalerQC_OSDWindowRoundedWin(_ENABLE);
            ScalerQC_OSDSRAMSize(_ENABLE);
            ScalerQC_OSDFont24_36(_ENABLE);
            break;

        //----------------------------
        // _OSD_FRAME_20
        //----------------------------
        case _OSD_FRAME_20:
			ScalerOsdPosition(_OSD_POSITION_FONT_A, X_POS(0), Y_POS(0));
			ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_QC_OSD_POSITION_OFFSET_H - 2), Y_POS(_QC_OSD_POSITION_OFFSET_V - 1));
			ScalerOsdScaleUpHorSize(0, 12 *_OSD_MAPA_SIZE_COL);
			ScalerOsdScaleUpVerSize(0, 18 *_OSD_MAPA_SIZE_ROW);
            ScalerQC_OSDScaleUp(_ENABLE, _OSD_SCALING_RATIO_300, _OSD_SCALING_BOUNDARY_NEIGHTBOOR);
           break;

        default:
            break;
    }

    ScalerOsdEnableOsd();
}

//--------------------------------------------------
// Description  : Close QC OSD test frame
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQC_OSDCloseFuncFrame(BYTE ucFrameStatus)
{
    BYTE ucIdx = 0;

    switch(ucFrameStatus)
    {
        case _OSD_FRAME_1:
            // Function
            ScalerOsdSpecificColorBlending(_DISABLE, 1);
            // Window
            ScalerQC_OSDWindowPriority(_DISABLE);
            break;

        case _OSD_FRAME_2:
            // Window
            ScalerQC_OSDWindowGradient(_DISABLE, 0);
            ScalerQC_OSDWindowGridLine(_DISABLE, 0);
            break;

        case _OSD_FRAME_2_1:
            // Function
            // clear align
            for(ucIdx = 0; ucIdx < _OSD_MAPA_SIZE_ROW; ucIdx++)
            {
                ScalerOsdSramDataValue(ROW(ucIdx), COL(_OSD_MAPA_SIZE_COL - 1), LENGTH(1), 0x4C, _OSD_BYTE0);
                ScalerOsdSramDataValue(ROW(ucIdx), COL(_OSD_MAPA_SIZE_COL - 1), LENGTH(1), 0x00, _OSD_BYTE1);
                ScalerOsdSramDataValue(ROW(ucIdx), COL(_OSD_MAPA_SIZE_COL - 1), LENGTH(1), 0x10, _OSD_BYTE2);
            }

            // clear blank
            ScalerOsdSramDataValue(ROW(2), COL(29), LENGTH(2), 0x4C, _OSD_BYTE0);
            ScalerOsdSramDataValue(ROW(2), COL(29), LENGTH(2), 0x00, _OSD_BYTE1);
            ScalerOsdSramDataValue(ROW(2), COL(29), LENGTH(2), 0x10, _OSD_BYTE2);

            // 2 bit ICON
            ScalerQC_OSDLoadIcon(ROW(8), COL(0 + (3 * 8)), LANGUAGE(0), _OSD_QCICON_2BIT);
            ScalerOsdChange2BitColor(ROW(8), COL(0 + (3 * 8)), LENGTH(8), HEIGHT(6), COLOR_00(0), COLOR_01(1), COLOR_10(2), COLOR_11(3));
            ScalerQC_OSD2BitFontByte1Bit7Swap(_OSD_2BIT_CHAR_BIT7_BY_SELECT_FONT);

            ScalerOsdMapRotation(_OSD_ROTATE_DEGREE_0, _OSD_MAP_A_REMAPPING_ENABLE, _OSD_MAPA_SIZE_ROW, _OSD_MAP_B_REMAPPING_ENABLE, _OSD_MAPB_SIZE_ROW, _OSD_FONT_LIB_ROTATION_ENABLE);
            break;

        case _OSD_FRAME_2_2:
            // Function
            ScalerQC_OSD1BitFontShrink(_OSD_1BIT_SHRINK_BY_LEFT, _CHAR_WIDTH_7);
            ScalerOsdMapRotation(_OSD_ROTATE_DEGREE_0, _OSD_MAP_A_REMAPPING_ENABLE, _OSD_MAPA_SIZE_ROW, _OSD_MAP_B_REMAPPING_ENABLE, _OSD_MAPB_SIZE_ROW, _OSD_FONT_LIB_ROTATION_ENABLE);
            ScalerOsdPosition(_OSD_POSITION_GLOBAL_B, X_POS(0 + 6), Y_POS(0 + 505));
            break;

        case _OSD_FRAME_2_3:
            // Function
            ScalerQC_OSD1BitFontShrink(_OSD_1BIT_SHRINK_BY_LEFT, _CHAR_WIDTH_7);
            ScalerQC_OSDBlankFont(_DISABLE, 72);
            ScalerQC_OSD1BitColor(_ENABLE);
            ScalerOsdMapRotation(_OSD_ROTATE_DEGREE_0, _OSD_MAP_A_REMAPPING_ENABLE, _OSD_MAPA_SIZE_ROW, _OSD_MAP_B_REMAPPING_ENABLE, _OSD_MAPB_SIZE_ROW, _OSD_FONT_LIB_ROTATION_ENABLE);
            break;

        case _OSD_FRAME_3:
            // function
            ScalerOsdPopOn(_DISABLE, _OSD_A);
            // window
            ScalerQC_OSDWindowGradient(_DISABLE, 1);
            ScalerQC_OSDWindowGridLine(_DISABLE, 1);
           break;

        case _OSD_FRAME_4:
            // function
            ScalerOsdPopOn(_DISABLE, _OSD_B);
            ScalerOsdVerticalBoundary(_DISABLE);

            // window
            ScalerQC_OSDWindowGradient(_DISABLE, 2);
            ScalerQC_OSDAlphaBlendingType(_DISABLE, _OSD_TRANSPARENCY_DISABLE);
            break;

        case _OSD_FRAME_5:
            // function
            ScalerOsdRollUp(_DISABLE, 8, 13);
            ScalerQC_OSDAlphaBlendingType(_DISABLE, _OSD_TRANSPARENCY_DISABLE);

            // window
            ScalerQC_OSDWindowGradient(_DISABLE, 3);
            break;

        case _OSD_FRAME_6:
            // function
            ScalerQC_OSDAlphaBlendingType(_DISABLE, _OSD_TRANSPARENCY_DISABLE);
            // window
            ScalerQC_OSDWindowGradient(_DISABLE, 4);
            ScalerQC_OSDWindowChessboard(_DISABLE);

            ScalerQC_OSDFuncApplyMap(_OSD_ROTATE_DEGREE_0);
            ScalerQC_OSDFuncClear(ROW(0), COL(0), LENGTH(_OSD_MAPA_SIZE_COL), HEIGHT(_OSD_MAPA_SIZE_ROW));
            ScalerQC_OSDFuncClear(ROW_MAPB(0), COL(0), LENGTH(_OSD_MAPB_SIZE_COL), HEIGHT(_OSD_MAPB_SIZE_ROW));
            break;

        case _OSD_FRAME_7:
            // window
            /* //re-use in Frame_8
            ScalerQC_OSDWindowSaturatedColor(_DISABLE);
            ScalerQC_OSDWindowHighlight(_DISABLE);
            */
            break;

        case _OSD_FRAME_8:
			ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_QC_OSD_POSITION_OFFSET_H), Y_POS(_QC_OSD_POSITION_OFFSET_V));
            ScalerQC_OSDScaleUp(_DISABLE, 0, _OSD_SCALING_BOUNDARY_NEIGHTBOOR);

            // window
            /* //re-use in Frame_9
            ScalerQC_OSDWindowGradientLevelExtension(_DISABLE);
            ScalerQC_OSDWindowShadowBorder(_DISABLE);
            */
            break;

        case _OSD_FRAME_9:
            // window
            ScalerQC_OSDWindow6SpecialFunction(_DISABLE, _OSD_WINDOW_6_FUNCTION_DISABLE);
            ScalerQC_OSDWindow7SpecialFunction(_DISABLE, _OSD_WINDOW_7_FUNCTION_DISABLE);
            break;

        case _OSD_FRAME_10:
            // function
            ScalerQC_OSDSetHStart(_PANEL_DH_START);
            ScalerOsdDoubleFunction(_OSD_DOUBLE_WIDTH_DISABLE, _OSD_DOUBLE_HEIGHT_DISABLE);
            // window
            ScalerQC_OSDWindow6SpecialFunction(_DISABLE, _OSD_WINDOW_6_FUNCTION_DISABLE);
            ScalerQC_OSDWindow7SpecialFunction(_DISABLE, _OSD_WINDOW_7_FUNCTION_DISABLE);
            ScalerQC_OSDWindowBorderPriority(_DISABLE, _DISABLE);
            break;

        case _OSD_FRAME_11:
            // function
            ScalerOsd2FontFunction(_DISABLE);
            ScalerQC_OSDSetHStart(_PANEL_DH_START);
            ScalerOsdDoubleFunction(_OSD_DOUBLE_WIDTH_DISABLE, _OSD_DOUBLE_HEIGHT_DISABLE);
            // window
            ScalerQC_OSDWindow6SpecialFunction(_DISABLE, _OSD_WINDOW_6_FUNCTION_DISABLE);
            ScalerQC_OSDWindow7SpecialFunction(_DISABLE, _OSD_WINDOW_7_FUNCTION_DISABLE);
            ScalerQC_OSDWindowBorderPriority(_DISABLE, _DISABLE);
            break;

        case _OSD_FRAME_12:
            // window
            ScalerQC_OSDWindow6SpecialFunction(_DISABLE, _OSD_WINDOW_6_FUNCTION_DISABLE);
            ScalerQC_OSDWindow7SpecialFunction(_DISABLE, _OSD_WINDOW_7_FUNCTION_DISABLE);
            ScalerQC_OSDWindowFontPriority(_DISABLE, _OSD_WINDOW_PRIORITY_LOWER_THAN_FONT);
            break;

        case _OSD_FRAME_13:
            // window
            /* //re-use in Frame_14
            ScalerQC_OSDWindow7SpecialFunction(_DISABLE, _OSD_WINDOW_7_FUNCTION_DISABLE);
            ScalerQC_OSDWindowFontPriority(_DISABLE, _OSD_WINDOW_PRIORITY_LOWER_THAN_FONT);
            */
            break;

        case _OSD_FRAME_14:
            /* //re-use in Frame_15
            ScalerQC_OSDFuncClear(ROW(0), COL(0), LENGTH(_OSD_MAPA_SIZE_COL), HEIGHT(_OSD_MAPA_SIZE_ROW));
            ScalerQC_OSDDrawWindow(_DISABLE, _OSD_WINDOW_5, 5, X_START(10), Y_START(0), X_END(30 + _OSD_WINDOW_WIDTH + _OSD_WINDOW_WIDTH), Y_END(0 + _OSD_WINDOW_HEIGHT));
            // function
            ScalerOsdHorizontalDelayStep(_OSD_HORIZONTAL_DELAY_STEP_4_PIXEL);
            // window
            ScalerQC_OSDWindow7SpecialFunction(_DISABLE, _OSD_WINDOW_7_FUNCTION_DISABLE);
            */
            break;

        case _OSD_FRAME_15:
            ScalerQC_OSDFuncClear(ROW(0), COL(0), LENGTH(_OSD_MAPA_SIZE_COL), HEIGHT(_OSD_MAPA_SIZE_ROW));
            ScalerQC_OSDDrawWindow(_DISABLE, _OSD_WINDOW_5, 5, X_START(10), Y_START(0), X_END(30 + _OSD_WINDOW_WIDTH + _OSD_WINDOW_WIDTH), Y_END(0 + _OSD_WINDOW_HEIGHT));
            // window
            ScalerQC_OSDWindow7SpecialFunction(_DISABLE, _OSD_WINDOW_7_FUNCTION_DISABLE);
            break;

         case _OSD_FRAME_16:
            // window
            ScalerQC_OSDWindowGrayLevel(_DISABLE);
            break;

        case _OSD_FRAME_17:
            // window
            ScalerQC_OSDWindowGradientStepExtension(_DISABLE);
            break;

        case _OSD_FRAME_18:
			ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_QC_OSD_POSITION_OFFSET_H), Y_POS(_QC_OSD_POSITION_OFFSET_V));
            ScalerQC_OSDScaleUp(_DISABLE, 0, _OSD_SCALING_BOUNDARY_NEIGHTBOOR);

            // window
            ScalerQC_OSDWindowSpecialColorMask(_DISABLE);

            ScalerSetByte(P7_F0_DISP_PG_R_CTRL, 0x80);
            ScalerSetByte(P7_F1_DISP_PG_G_CTRL, 0x00);
            ScalerSetByte(P7_F2_DISP_PG_B_CTRL, 0x00);
            ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, 0x00);
            ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, 0x00);
            ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, 0x00);
            ScalerSetByte(P7_F6_DISP_PG_PIXEL_DELTA_H, 0x00);
            ScalerSetByte(P7_F7_DISP_PG_LINE_DELTA_H, 0x00);
            ScalerSetByte(P7_F8_DISP_PG_PIXEL_STEP_H, 0x00);

            ScalerSetByte(P7_F9_DISP_PG_LINE_STEP_H, 0x00);
            ScalerSetByte(P7_FA_DISP_PG_DELTA_H_STEP_M, 0x00);

            ScalerQC_OSDWindowFontPriority(_DISABLE, _OSD_WINDOW_PRIORITY_HIGHTER_THAN_FONT);
            break;

        case _OSD_FRAME_19:
            ScalerQC_OSDWindowRoundedWin(_DISABLE);
            ScalerQC_OSDSRAMSize(_DISABLE);
            ScalerQC_OSDFont24_36(_DISABLE);
            break;

        case _OSD_FRAME_20:
			ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_QC_OSD_POSITION_OFFSET_H), Y_POS(_QC_OSD_POSITION_OFFSET_V));
            ScalerQC_OSDScaleUp(_DISABLE, 0, _OSD_SCALING_BOUNDARY_NEIGHTBOOR);
            break;

        default:
            break;
    }
}

//-----------------------------------------
// Description  : OSD test function
// Input Value  : None
// Output Value : None
//-----------------------------------------
bit ScalerQC_OSDTestProc(void)
{
    WORD usData = 0;

    ScalerOsdGlobalDoubleBuffer(_DISABLE);

    // close dither
    ScalerSetByte(P0_60_HLW_ADDR_PORT, 0x00);
    ScalerSetByte(P0_62_SRGB_CTRL, 0x00);
    ScalerSetByte(P0_67_GAMMA_CTRL_SETA, 0x00);
    ScalerSetByte(P0_6A_D_DITHER_COMMON_CTRL1, 0x00);
    // activate OSD
    ScalerOsdCircuitActivated(_ENABLE);
    // set pattern gen color
    ScalerSetByte(P7_F0_DISP_PG_R_CTRL, 0x80);
    ScalerSetByte(P7_F1_DISP_PG_G_CTRL, 0x00);
    ScalerSetByte(P7_F2_DISP_PG_B_CTRL, 0x00);

    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, 0x00);
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, 0x00);
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, 0x00);
    ScalerSetBit(P7_F0_DISP_PG_R_CTRL, ~_BIT7, _BIT7);

    // set ENA
    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
    // set palette
    ScalerQC_OSDTablePaletteAdjust();
    // Set initial value to registers without inital value
    ScalerQC_OSDRegInitial();
    // enable 2 OSD map
    ScalerOsd2FontFunction(_ENABLE);
    // set map command
    ScalerQC_OSDFuncApplyMap(_OSD_ROTATE_DEGREE_0);
    // Set Position
    ScalerOsdFontWindowVericalAlignemnt(_ENABLE);
    ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_QC_OSD_POSITION_OFFSET_H), Y_POS(_QC_OSD_POSITION_OFFSET_V));
    ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_WINDOW, X_POS(_QC_OSD_OFFSET_DRAW_WINDOW_H), Y_POS(_QC_OSD_OFFSET_DRAW_WINDOW_V));
    ScalerOsdPosition(_OSD_POSITION_GLOBAL_A, X_POS(0), Y_POS(0));
    ScalerOsdPosition(_OSD_POSITION_GLOBAL_B, X_POS(0), Y_POS(0 + 505));

    ScalerOsdReferenceDelay(_OSD_A, _OSD_FIRST_DELAY);
    ScalerOsdReferenceDelay(_OSD_B, _OSD_SECOND_DELAY);
    ScalerOsdPosition(_OSD_POSITION_FONT_A, X_POS(0), Y_POS(0));
    ScalerOsdPosition(_OSD_POSITION_FONT_B, X_POS(0), Y_POS(0));

    // draw 1-bit, 2-bit, 4-bit test pattern
    ScalerQC_OSDSRAMTestPattern();

    //---------------------------------------
    // frame 1
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame1 Start", 0x01);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_1);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_1, 1) << 0));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_1);
    DebugMessageQC("5.OsdTestFrame1 END", 0x01);

    //---------------------------------------
    // frame 2
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame2 Start", 0x02);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_2);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_2, 1) << 1));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_2);
    DebugMessageQC("5.OsdTestFrame2 END", 0x02);

    //---------------------------------------
    // frame 2-1
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame2_1 Start", 0x02);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_2_1);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_2_1, 1) << 1));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_2_1);
    DebugMessageQC("5.OsdTestFrame2_1 END", 0x02);

    //---------------------------------------
    // frame 2-2
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame2_2 Start", 0x02);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_2_2);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_2_2, 1) << 1));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_2_2);
    DebugMessageQC("5.OsdTestFrame2_2 END", 0x02);

    //---------------------------------------
    // frame 2-3
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame2_3 Start", 0x02);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_2_3);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_2_3, 1) << 1));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_2_3);
    DebugMessageQC("5.OsdTestFrame2_2 END", 0x02);

    //---------------------------------------
    // frame 3
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame3 Start", 0x03);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_3);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_3, 1) << 2));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_3);
    DebugMessageQC("5.OsdTestFrame3 END", 0x03);

    //---------------------------------------
    // frame 4
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame4 Start", 0x04);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_4);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_4, 1) << 3));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_4);
    DebugMessageQC("5.OsdTestFrame4 END", 0x04);

    //---------------------------------------
    // frame 5
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame5 Start", 0x05);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_5);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_5, 1) << 4));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_5);
    DebugMessageQC("5.OsdTestFrame5 END", 0x05);

    //---------------------------------------
    // frame 6
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame6 Start", 0x06);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_6);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_6, 1) << 5));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_6);
    DebugMessageQC("5.OsdTestFrame6 END", 0x06);

    //---------------------------------------
    // frame 7
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame7 Start", 0x07);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_7);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_7, 1) << 6));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_7);
    DebugMessageQC("5.OsdTestFrame7 END", 0x07);

    //---------------------------------------
    // frame 8
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame8 Start", 0x08);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_8);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_8, 1) << 7));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_8);
    DebugMessageQC("5.OsdTestFrame8 END", 0x08);

    //---------------------------------------
    // frame 9
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame9 Start", 0x09);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_9);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_9, 1) << 8));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_9);
    DebugMessageQC("5.OsdTestFrame9 END", 0x09);

    //---------------------------------------
    // frame 10
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame10 Start", 0x0a);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_10);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_10, 1) << 9));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_10);
    DebugMessageQC("5.OsdTestFrame10 END", 0x0a);

    //---------------------------------------
    // frame 11
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame11 Start", 0x0b);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_11);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_11, 1) << 10));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_11);
    DebugMessageQC("5.OsdTestFrame11 END", 0x0b);

    //---------------------------------------
    // frame 12
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame12 Start", 0x0c);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_12);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_12, 1) << 11));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_12);
    DebugMessageQC("5.OsdTestFrame12 END", 0x0c);

    //---------------------------------------
    // frame 13
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame13 Start", 0x0d);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_13);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_13, 1) << 12));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_13);
    DebugMessageQC("5.OsdTestFrame13 END", 0x0d);

    //---------------------------------------
    // frame 14
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame14 Start", 0x0e);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_14);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_14, 1) << 13));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_14);
    DebugMessageQC("5.OsdTestFrame14 END", 0x0e);

    //---------------------------------------
    // frame 15
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame15 Start", 0x0f);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_15);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_15, 1) << 14));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_15);
    DebugMessageQC("5.OsdTestFrame15 END", 0x0f);

    //---------------------------------------
    // frame 16
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame16 Start", 0x10);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_16);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_16, 1) << 15));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_16);
    DebugMessageQC("5.OsdTestFrame16 END", 0x10);

    //---------------------------------------
    // frame 17
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame17 Start", 0x11);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_17);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_17, 1) << 0));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_17);
    DebugMessageQC("5.OsdTestFrame17 END", 0x11);

    //---------------------------------------
    // frame 18
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame18 Start", 0x12);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_18);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_18, 1) << 1));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_18);
    DebugMessageQC("5.OsdTestFrame18 END", 0x12);

    //---------------------------------------
    // frame 19
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame19 Start", 0x13);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_19);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_19, 1) << 2));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_19);
    DebugMessageQC("5.OsdTestFrame19 END", 0x13);

    //---------------------------------------
    // frame 20
    //---------------------------------------
    DebugMessageQC("5.OsdTestFrame20 Start", 0x13);
    ScalerQC_OSDFuncFrame(_OSD_FRAME_20);

    usData = (usData | ((WORD)ScalerQC_OSDCRCCompare(_D_DOMAIN_CRC, _D_CRC_AFTER_OD, _M1 | _M2, tQC_OSD_CRC_TABLE_20, 1) << 3));

    ScalerQC_OSDCloseFuncFrame(_OSD_FRAME_20);
    DebugMessageQC("5.OsdTestFrame20 END", 0x13);


    ScalerDDomainBackgroundEnable(_DISABLE);
    // disable pattern gen
    ScalerSetByte(P7_F0_DISP_PG_R_CTRL, 0x00);
    // disable OSD overlap
    ScalerOsdDisableOsd();
    // disable OSD
    ScalerOsdCircuitActivated(_DISABLE);

    if(usData == 0)
    {
        DebugMessageQC("5.Osd Test Pass", 0);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("5.Fail Mode", usData);
        DebugMessageQC("5.Osd Test Fail", 0);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// QC Process
//--------------------------------------------------
bit ScalerQCOSDTest(void)
{
    bit bResult = 0;

    DebugMessageQC("5. OSD Start", 0x00);

    bResult = ScalerQC_OSDTestProc();

    DebugMessageQC("5. OSD End", 0x00);
    return bResult;
}

#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)

