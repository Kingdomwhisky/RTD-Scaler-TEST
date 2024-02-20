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
// ID Code      : RL6410_Series_OsdFontRotateCtrl.c
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
void ScalerOsdFontRotateCtrl(EnumOsdRotateType enumRotType, BYTE ucFontDownloadRotEn, BYTE ucDispRotEn);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set Osd Font Rotation
// Input Value  : enumRotType
// Input Value  : ucFontDownloadRotEn
// Input Value  : ucDispRotEn
// Output Value :
//--------------------------------------------------
void ScalerOsdFontRotateCtrl(EnumOsdRotateType enumRotType, BYTE ucFontDownloadRotEn, BYTE ucDispRotEn)
{
    switch(enumRotType)
    {
        default:
        case _OSD_ROTATE_DEGREE_0:
            ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~(_BIT7 | _BIT6), 0x00);
            break;

        case _OSD_ROTATE_DEGREE_90:
            ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            break;

        case _OSD_ROTATE_DEGREE_270:
            ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~(_BIT7 | _BIT6), _BIT7);
            break;

        case _OSD_ROTATE_DEGREE_180:
            ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~(_BIT7 | _BIT6), _BIT6);
            break;
    }

    if(((bit)ucFontDownloadRotEn) == _ENABLE)
    {
        ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~_BIT2, _BIT2);
    }
    else
    {
        ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~_BIT2, 0x00);
    }

    if((enumRotType == _OSD_ROTATE_DEGREE_0) || (enumRotType == _OSD_ROTATE_DEGREE_180))
    {
        ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~_BIT0, 0x00);
    }
    else
    {
        ScalerSetBit(P3A_0B_FRAME_CTRL_0B, ~_BIT0, (bit)ucDispRotEn);
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdFontRotateCtrl(_OSD_ROTATE_DEGREE_90, _ENABLE, _OSD_ROTATE_ROTATION);
*/


