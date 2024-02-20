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
// ID Code      : OsdRotationWindowSize.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerOSDLibInternalInclude.h"

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
void ScalerOsdRotationWindowSize(EnumOsdMapType enumOsdMapType, WORD usLength, WORD usWidth);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set window rotate reference size
// Input Value  : enumOsdMapType -> _OSD_A or _OSD_B
//                usLength       -> Horizontal max size
//                Width          -> Vertical max size
// Output Value :
//--------------------------------------------------
void ScalerOsdRotationWindowSize(EnumOsdMapType enumOsdMapType, WORD usLength, WORD usWidth)
{
    if(enumOsdMapType == _OSD_A)
    {
        // First OSD Width
        ScalerSetBit(P3A_38_FRAME_CTRL_38, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((usWidth & 0x0F00) >> 8));
        ScalerSetByte(P3A_3A_FRAME_CTRL_3A, (usWidth & 0xFF));

        // First OSD Length
        ScalerSetBit(P3A_38_FRAME_CTRL_38, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((usLength & 0x0F00) >> 4));
        ScalerSetByte(P3A_39_FRAME_CTRL_39, (usLength & 0xFF));
    }
    else
    {
        // Second OSD Width
        ScalerSetBit(P3A_3B_FRAME_CTRL_3B, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((usWidth & 0x0F00) >> 8));
        ScalerSetByte(P3A_3D_FRAME_CTRL_3D, (usWidth & 0xFF));

        // Second OSD Length
        ScalerSetBit(P3A_3B_FRAME_CTRL_3B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((usLength & 0x0F00) >> 4));
        ScalerSetByte(P3A_3C_FRAME_CTRL_3C, (usLength & 0xFF));
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdRotationWindowSize(_OSD_A, XEND(400), YEND(500));
*/



