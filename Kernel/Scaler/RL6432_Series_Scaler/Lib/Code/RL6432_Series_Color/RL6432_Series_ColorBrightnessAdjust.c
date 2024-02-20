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
// ID Code      : RL6432_Series_ColorBrightnessAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_ColorLibInternalInclude.h"

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
void ScalerColorBrightnessAdjust(EnumBriConCoefType enumBriConCoefType, WORD *pusData);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust Brightness
// Input Value  : EnumBriConCoefTypem, Coefficient
//                10 bit input, old 8 bit brightness input value must left shift 2 bit
//                -2048(00h) ~ 0(200h) ~  +2044(3FFh)
// Output Value : void
//--------------------------------------------------
void ScalerColorBrightnessAdjust(EnumBriConCoefType enumBriConCoefType, WORD *pusData)
{
    switch(enumBriConCoefType)
    {
        case _BRIGHTNESS_COEF_A:
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_00_BRI_RED_COE_SETA_H, (pusData[0] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_01_BRI_GRN_COE_SETA_H, (pusData[1] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_02_BRI_BLU_COE_SETA_H, (pusData[2] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_20_BRI_COE_SETA_L, ((pusData[0] & 0x0003) << 6) | ((pusData[1] & 0x0003) << 4) | ((pusData[2] & 0x0003) << 2));
            break;

        case _BRIGHTNESS_COEF_B:
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_06_BRI_RED_COE_SETB_H, (pusData[0] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_07_BRI_GRN_COE_SETB_H, (pusData[1] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_08_BRI_BLU_COE_SETB_H, (pusData[2] & 0x03FC) >> 2);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_23_BRI_COE_SETB_L, ((pusData[0] & 0x0003) << 6) | ((pusData[1] & 0x0003) << 4) | ((pusData[2] & 0x0003) << 2));
            break;

        default:
            break;
    }
}

