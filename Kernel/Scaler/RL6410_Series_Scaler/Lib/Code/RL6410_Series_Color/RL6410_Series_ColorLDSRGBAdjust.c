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
//-------------------------------------------------------------------------------------//
// ID Code      : RL6410_Series_ColorLDSRGBAdjust.c
// Update Note  :
//-------------------------------------------------------------------------------------//
#include "RL6410_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Table Length
//--------------------------------------------------
#define _SRGB_TABLE_SIZE                        24


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
bit ScalerColorLDSRGBAdjust(BYTE *pucSRGBArray, EnumSrgbPrecision enumPrecision);



//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************


//--------------------------------------------------
// Description  : Adjust SRGB function for LD
// Input Value  : SRGB Matrix
//                SRGB Precision
// Output Value : _TRUE/_FALSE
//--------------------------------------------------

bit ScalerColorLDSRGBAdjust(BYTE *pucSRGBArray, EnumSrgbPrecision enumPrecision)
{
    // Clear Waiting flag
    ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT6, _BIT6); // Reset Port

    if(ScalerTimerPollingFlagProc(2, P0_62_SRGB_CTRL, _BIT6, 0) == _FALSE) // pollling till Reset port address finished
    {
        return _FALSE;
    }

    ScalerSetBit(P0_62_SRGB_CTRL, ~(_BIT5 | _BIT4 | _BIT3), 0x00); // Write sequence

    ScalerBurstWrite(pucSRGBArray, _SRGB_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_63_SRGB_ACCESS_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

    ScalerSetBit(P0_68_GAMMA_BIST_DITHER_SETA, ~(_BIT6 | _BIT5), (enumPrecision << 5)); // Precision

    ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT7, _BIT7);   // no apply none, always effective on dvs

    return _TRUE;
}



