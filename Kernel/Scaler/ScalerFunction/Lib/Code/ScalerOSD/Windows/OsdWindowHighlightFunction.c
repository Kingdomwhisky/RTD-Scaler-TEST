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
// ID Code      : OsdWindowHighlightFunction.c
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
void ScalerOsdWindowHighlightFunction(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucForegroundColor, BYTE ucBackgroundColor, BYTE ucCharactorBorderColor);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set window highlight function
// Input Value  : bEnable              -> _ENABLE or _DISABLE
//                enumOsdWindowsType   -> _OSD_WINDOW_4_1 ~ _OSD_WINDOW_4_8
//                ucForegroundColor    -> 0 ~ 63
//                BackgroundColor      -> 0 ~ 63
//                CharactorBorderColor -> 0 ~ 63
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowHighlightFunction(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucForegroundColor, BYTE ucBackgroundColor, BYTE ucCharactorBorderColor)
{
    ucCharactorBorderColor = ucCharactorBorderColor;

    switch(enumOsdWindowsType)
    {
        case _OSD_WINDOW_4_1:
            ScalerSetBit(P3A_2A_FRAME_CTRL_2A, ~_BIT6, ((BYTE)bEnable << 6));
            ScalerSetBit(P3A_2A_FRAME_CTRL_2A, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucForegroundColor);
            ScalerSetBit(P3A_2B_FRAME_CTRL_2B, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBackgroundColor);
            break;

        case _OSD_WINDOW_4_2:
            ScalerSetBit(P3A_2D_FRAME_CTRL_2D, ~_BIT6, ((BYTE)bEnable << 6));
            ScalerSetBit(P3A_2D_FRAME_CTRL_2D, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucForegroundColor);
            ScalerSetBit(P3A_2E_FRAME_CTRL_2E, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBackgroundColor);
            break;

        case _OSD_WINDOW_4_3:
            ScalerSetBit(P3A_30_FRAME_CTRL_30, ~_BIT6, ((BYTE)bEnable << 6));
            ScalerSetBit(P3A_30_FRAME_CTRL_30, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucForegroundColor);
            ScalerSetBit(P3A_31_FRAME_CTRL_31, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBackgroundColor);
            break;

        case _OSD_WINDOW_4_4:
            ScalerSetBit(P3A_4D_FRAME_CTRL_4D, ~_BIT6, ((BYTE)bEnable << 6));
            ScalerSetBit(P3A_4D_FRAME_CTRL_4D, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucForegroundColor);
            ScalerSetBit(P3A_4E_FRAME_CTRL_4E, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBackgroundColor);
            break;

        case _OSD_WINDOW_4_5:
            ScalerSetBit(P3A_4F_FRAME_CTRL_4F, ~_BIT6, ((BYTE)bEnable << 6));
            ScalerSetBit(P3A_4F_FRAME_CTRL_4F, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucForegroundColor);
            ScalerSetBit(P3A_50_FRAME_CTRL_50, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBackgroundColor);
            break;

        case _OSD_WINDOW_4_6:
            ScalerSetBit(P3A_51_FRAME_CTRL_51, ~_BIT6, ((BYTE)bEnable << 6));
            ScalerSetBit(P3A_51_FRAME_CTRL_51, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucForegroundColor);
            ScalerSetBit(P3A_52_FRAME_CTRL_52, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBackgroundColor);
            break;

        case _OSD_WINDOW_4_7:
            ScalerSetBit(P3A_53_FRAME_CTRL_53, ~_BIT6, ((BYTE)bEnable << 6));
            ScalerSetBit(P3A_53_FRAME_CTRL_53, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucForegroundColor);
            ScalerSetBit(P3A_54_FRAME_CTRL_54, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBackgroundColor);
            break;

        case _OSD_WINDOW_4_8:
            ScalerSetBit(P3A_55_FRAME_CTRL_55, ~_BIT6, ((BYTE)bEnable << 6));
            ScalerSetBit(P3A_55_FRAME_CTRL_55, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucForegroundColor);
            ScalerSetBit(P3A_56_FRAME_CTRL_56, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBackgroundColor);
            break;

        default:
            break;
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdWindowHighlightFunction(_ENABLE, _OSD_WINDOW_4_1, 1, 3, 5);
*/


