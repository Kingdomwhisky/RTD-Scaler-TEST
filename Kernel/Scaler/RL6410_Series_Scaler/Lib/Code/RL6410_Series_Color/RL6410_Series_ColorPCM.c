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
// ID Code      : RL6410_Series_ColorPCM.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_ColorLibInternalInclude.h"

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
void ScalerColorPCMLoadTable(EnumPCMType enumPCMMode, BYTE *pucIGammaTableArray, BYTE *pucOGammaTableArray, BYTE *pucColorMatrixArray, BYTE ucBankNum, WORD usLength, BYTE ucGammaBankNum);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set PCM(Input Gamma, Output Gamma, Color Matrix)
// Input Value  : PCM Type --> sRGB / AdobeRGB
//                Input Gamma Table  & its bank number
//                Output Gamma Table & its bank number
//                Color Matrix       & its bank number
// Output Value : None
//--------------------------------------------------
void ScalerColorPCMLoadTable(EnumPCMType enumPCMMode, BYTE *pucIGammaTableArray, BYTE *pucOGammaTableArray, BYTE *pucColorMatrixArray, BYTE ucBankNum, WORD usLength, BYTE ucGammaBankNum)
{
    ScalerColorSRGBSwap(_SRGB_BEFORE_OG);

    // Set InputGamma LUT
    if((enumPCMMode == _PCM_USER_MODE) || (enumPCMMode == _PCM_HDR_2084) || (enumPCMMode == _PCM_BYPASS))
    {
        ScalerColorPCMInputGammaAdjust(pucIGammaTableArray, ucBankNum);
    }
    else
    {
        ScalerColorPCMInputGammaAdjust((BYTE *)ScalerColorPCMGetTableAddress(enumPCMMode), ScalerColorPCMGetTableBank());
    }

    // Load Gamma table
    ScalerColorPCMOutputGammaAdjust(pucOGammaTableArray, ucGammaBankNum);

    // Set color Matrix
    if((enumPCMMode == _PCM_SOFT_PROFT) || (enumPCMMode == _PCM_HDR_2084))
    {
        ScalerColorPCMSRGBAdjust(_SRGB_1_BIT_SHIFT_LEFT, pucColorMatrixArray, ucBankNum, usLength);
    }
    else if(enumPCMMode == _PCM_BYPASS)
    {
        // do nothing
    }
    else
    {
        ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, pucColorMatrixArray, ucBankNum, usLength);
    }
}

