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
// ID Code      : RL6492_Series_ColorContrastAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6492_Series_ColorLibInternalInclude.h"

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
void ScalerColorContrastAdjust(EnumBriConCoefType enumBriConCoefType, WORD *pusData);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust Contrast
// Input Value  : EnumBriConCoefType, Coefficient
//                12 bit input, old 8 bit contrast input value must left shift 4 bit
//                0 (00h) ~ 1(800h) ~  2(FFFh)
// Output Value : void
//--------------------------------------------------
void ScalerColorContrastAdjust(EnumBriConCoefType enumBriConCoefType, WORD *pusData)
{
    switch(enumBriConCoefType)
    {
        case _CONTRAST_COEF_A:
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_03_CTS_RED_COE_SETA_H, (pusData[0] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_04_CTS_GRN_COE_SETA_H, (pusData[1] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_05_CTS_BLU_COE_SETA_H, (pusData[2] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_21_CTS_COE_SETA_RG_L, ((pusData[0] & 0x000F) << 4) | ((pusData[1] & 0x000F)));
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_22_CTS_COE_SETA_B_L, (pusData[2] & 0x000F) << 4);
            break;

        case _CONTRAST_COEF_B:
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_09_CTS_RED_COE_SETB_H, (pusData[0] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_0A_CTS_GRN_COE_SETB_H, (pusData[1] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_0B_CTS_BLU_COE_SETB_H, (pusData[2] & 0x0FF0) >> 4);
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_24_CTS_COE_SETB_RG_L, ((pusData[0] & 0x000F) << 4) | ((pusData[1] & 0x000F)));
            ScalerSetDataPortByte(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_25_CTS_COE_SETB_B_L, (pusData[2] & 0x000F) << 4);
            break;

        default:
            break;
    }
}
