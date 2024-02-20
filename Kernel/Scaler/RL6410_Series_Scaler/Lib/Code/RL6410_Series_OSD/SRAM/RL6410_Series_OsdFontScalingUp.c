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
// ID Code      : RL6410_Series_OsdFontScalingUp.c
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
void ScalerOsdFontScalingUpRatio(EnumOsdFontScalingRatioType enumRatio);
void ScalerOsdFontScalingUpBoundaryCodition(EnumOsdFontScalingBoundaryType enumBoundary);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : OSD Font Scale Up Ratio
// Input Value  : enumRatio
// Output Value :
// Note         : Scale_Ratio is recommended to set BEFORE Font_Scale_En.
//               If users want to change scale ratio, the recommended flow is Disable OSD -> Set new Scale_Ratio -> Enable OSD.
//               Font Scale up, Double Width/Height, and Auto Rotation&Remap. These three features cannot be open at the same time.
//--------------------------------------------------
void ScalerOsdFontScalingUpRatio(EnumOsdFontScalingRatioType enumRatio)
{
    ScalerSetBit(P3A_43_FRAME_CTRL_43, ~(_BIT4 | _BIT3 | _BIT2), (enumRatio << 2));
}

//--------------------------------------------------
// Description  : OSD Font Scale Up Boundary Condition
// Input Value  : enumRatio
// Output Value :
//--------------------------------------------------
void ScalerOsdFontScalingUpBoundaryCodition(EnumOsdFontScalingBoundaryType enumBoundary)
{
    ScalerSetBit(P3A_43_FRAME_CTRL_43, ~(_BIT1 | _BIT0), enumBoundary);
}
