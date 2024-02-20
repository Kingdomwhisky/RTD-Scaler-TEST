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
// ID Code      : RL6463_Series_ColorPCMTable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6463_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// PCM TABLE For OCC
//----------------------------------------------------------------------------------------------------
BYTE code tPCM_INPUTGAMMA_SRGB[] =
{
    0x00, 0x00, 0x14,
    0x02, 0x80, 0x3C,
    0x05, 0x50, 0x72,
    0x09, 0x50, 0xBE,
    0x0E, 0xC1, 0x20,
    0x15, 0xA1, 0x9B,
    0x1E, 0x22, 0x30,
    0x28, 0x52, 0xE1,
    0x34, 0x53, 0xAF,
    0x10, 0x91, 0x27,
    0x14, 0x71, 0x6A,
    0x18, 0xE1, 0xB5,
    0x1D, 0xD2, 0x08,
    0x23, 0x52, 0x64,
    0x29, 0x52, 0xC9,
    0x2F, 0xE3, 0x36,
    0x37, 0x13, 0xAE,
    0x3E, 0xD1, 0x0C,
    0x11, 0xD1, 0x2E,
    0x14, 0x01, 0x53,
    0x16, 0x71, 0x7B,
    0x18, 0xF1, 0xA5,
    0x1B, 0xB1, 0xD2,
    0x1E, 0x92, 0x01,
    0x21, 0xA2, 0x33,
    0x24, 0xD2, 0x68,
    0x28, 0x32, 0xA0,
    0x2B, 0xC2, 0xDA,
    0x2F, 0x83, 0x17,
    0x33, 0x73, 0x58,
    0x37, 0x93, 0x9B,
    0x3B, 0xD3, 0xE1,
    0x3F, 0xC0, 0x00,
    0x11, 0x22,
};

BYTE code tPCM_INPUTGAMMA_ADOBERGB[] =
{
    0x00, 0x00, 0x06,
    0x00, 0xE0, 0x18,
    0x02, 0x40, 0x3C,
    0x05, 0xA0, 0x7F,
    0x0A, 0xA0, 0xDC,
    0x11, 0x61, 0x56,
    0x19, 0xF1, 0xEE,
    0x24, 0x62, 0xA5,
    0x30, 0xD3, 0x7C,
    0x3F, 0x31, 0x1D,
    0x13, 0xF1, 0x63,
    0x18, 0x91, 0xB2,
    0x1D, 0xC2, 0x09,
    0x23, 0x82, 0x69,
    0x29, 0xC2, 0xD2,
    0x30, 0xA3, 0x44,
    0x38, 0x03, 0xBF,
    0x10, 0x01, 0x11,
    0x12, 0x21, 0x34,
    0x14, 0x71, 0x5A,
    0x16, 0xE1, 0x82,
    0x19, 0x71, 0xAD,
    0x1C, 0x31, 0xDA,
    0x1F, 0x22, 0x0A,
    0x22, 0x32, 0x3C,
    0x25, 0x62, 0x70,
    0x28, 0xC2, 0xA8,
    0x2C, 0x42, 0xE1,
    0x2F, 0xF3, 0x1D,
    0x33, 0xD3, 0x5C,
    0x37, 0xD3, 0x9E,
    0x3B, 0xF3, 0xE2,
    0x3F, 0xC0, 0x00,
    0x12, 0x21,
};

code BYTE *tPCM_INPUTGAMMA[] =
{
    tPCM_INPUTGAMMA_SRGB,
    tPCM_INPUTGAMMA_ADOBERGB,
    tPCM_INPUTGAMMA_SRGB, // UserDefine
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
WORD ScalerColorPCMGetTableAddress(EnumPCMType enumPCMMode);
BYTE ScalerColorPCMGetTableBank(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set PCM(Input Gamma, Output Gamma, Color Matrix)
// Input Value  : PCM Type --> sRGB / AdobeRGB
// Output Value : PCM table address
//--------------------------------------------------
WORD ScalerColorPCMGetTableAddress(EnumPCMType enumPCMMode)
{
    return (WORD)tPCM_INPUTGAMMA[enumPCMMode];
}

//--------------------------------------------------
// Description  : Set PCM(Input Gamma, Output Gamma, Color Matrix)
// Input Value  : None
// Output Value : PCM table bank
//--------------------------------------------------
BYTE ScalerColorPCMGetTableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}

