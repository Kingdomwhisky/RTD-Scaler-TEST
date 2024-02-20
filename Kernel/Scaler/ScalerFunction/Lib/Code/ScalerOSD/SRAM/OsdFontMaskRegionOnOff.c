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
// ID Code      : OsdFontMaskRegionOnOff.c
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
void ScalerOsdFontMaskRegionOnOff(EnumOsdMapType enumOsdMapType, bit bOnOff);
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : MASK Specific Region of Font A/B Enable/Disable
// Input Value  : bOnOff
// Output Value :
//--------------------------------------------------
void ScalerOsdFontMaskRegionOnOff(EnumOsdMapType enumOsdMapType, bit bOnOff)
{
    if(enumOsdMapType == _OSD_A)
    {
        ScalerSetBit(P3A_45_FRAME_CTRL_45, ~_BIT7, ((BYTE)bOnOff << 7));
    }
    else
    {
        ScalerSetBit(P3A_47_FRAME_CTRL_47, ~_BIT7, ((BYTE)bOnOff << 7));
    }
}

