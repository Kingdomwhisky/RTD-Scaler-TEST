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
// ID Code      : RL6410_Series_OsdPosition.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_OSDLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerOsdPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set osd position
// Input Value  : enumOsdPositionType -> _OSD_POSITION_GLOBAL_A or _OSD_POSITION_GLOBAL_B or _OSD_POSITION_FONT_A or _OSD_POSITION_FONT_B
//                usX                 -> Horizontal delay value (min:2)
//                usY                 -> Vertical  delay value (min:1)
// Output Value :
//--------------------------------------------------
void ScalerOsdPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY)
{
    // Check Osd Double Buffer
    if(ScalerGetBit(P0_93_OSD_MISC_PORT, _BIT7) == 0x00)
    {
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    }

    if(enumOsdPositionType == _OSD_POSITION_GLOBAL_A)
    {
        // First Horizontal Delay Bit[11:10]
        ScalerSetBit(P3A_06_FRAME_CTRL_06, ~(_BIT3 | _BIT2), ((usX & 0xC00) >> 8));

        // First Horizontal Delay [9:2]
        ScalerSetByte(P3A_01_FRAME_CTRL_01, (BYTE)(usX >> 2));

        // First Vertical Delay [11]
        ScalerSetBit(P3A_06_FRAME_CTRL_06, ~_BIT6, ((usY & 0x800) >> 5));

        // First Vertical Delay [10:3]
        ScalerSetByte(P3A_00_FRAME_CTRL_00, (BYTE)(usY >> 3));

        // (_BIT7 | _BIT6) : First Horizontal Delay Bit [1:0], (_BIT5 | _BIT4 | _BIT3) : First Vertical Delay [2:0].
        ScalerSetBit(P3A_02_FRAME_CTRL_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (((usX & 0x0003) << 6) | ((usY & 0x07) << 3)));
    }
    else if(enumOsdPositionType == _OSD_POSITION_GLOBAL_B)
    {
        // Second Horizontal Delay Bit[11:10]
        ScalerSetBit(P3A_06_FRAME_CTRL_06, ~(_BIT1 | _BIT0), ((usX & 0xC00) >> 10));

        // Second Horizontal Delay [9:2]
        ScalerSetByte(P3A_04_FRAME_CTRL_04, (BYTE)(usX >> 2));

        // Second Vertical Delay [11]
        ScalerSetBit(P3A_06_FRAME_CTRL_06, ~_BIT5, ((usY & 0x800) >> 6));

        // Second Vertical Delay [10:3]
        ScalerSetByte(P3A_03_FRAME_CTRL_03, (BYTE)(usY >> 3));

        // (_BIT7 | _BIT6) : Second Horizontal Delay Bit [1:0],  (_BIT5 | _BIT4 | _BIT3) : Second Vertical Delay [2:0]
        ScalerSetBit(P3A_05_FRAME_CTRL_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (((usX & 0x0003) << 6) | ((usY & 0x07) << 3)));
    }
    else if(enumOsdPositionType == _OSD_POSITION_FONT_A)
    {
        // (_BIT7 | _BIT6 | _BIT5 | _BIT4) : FONT A Horizontal Delay [11:8]
        // (_BIT3 | _BIT2 | _BIT1 | _BIT0) : FONT A Vertical Delay [11:8]
        ScalerSetByte(P3A_24_FRAME_CTRL_24, (((usX & 0xF00) >> 4) | ((usY & 0xF00) >> 8)));

        // FONT A Horizontal Delay [7:0]
        ScalerSetByte(P3A_25_FRAME_CTRL_25, (usX & 0x0FF));

        // FONT A Vertical Delay [7:0]
        ScalerSetByte(P3A_26_FRAME_CTRL_26, (usY & 0x0FF));
    }
    else if(enumOsdPositionType == _OSD_POSITION_FONT_B)
    {
        // (_BIT7 | _BIT6 | _BIT5 | _BIT4) : FONT B Horizontal Delay [11:8]
        // (_BIT3 | _BIT2 | _BIT1 | _BIT0) : FONT B Vertical Delay [11:8]
        ScalerSetByte(P3A_27_FRAME_CTRL_27, (((usX & 0xF00) >> 4) | ((usY & 0xF00) >> 8)));

        // FONT B Horizontal Delay [7:0]
        ScalerSetByte(P3A_28_FRAME_CTRL_28, (usX & 0x0FF));

        // FONT B Vertical Delay [7:0]
        ScalerSetByte(P3A_29_FRAME_CTRL_29, (usY & 0x0FF));
    }
}



/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdPosition(_OSD_POSITION_GLOBAL_A, XPOS(100), YPOS(100));
*/
