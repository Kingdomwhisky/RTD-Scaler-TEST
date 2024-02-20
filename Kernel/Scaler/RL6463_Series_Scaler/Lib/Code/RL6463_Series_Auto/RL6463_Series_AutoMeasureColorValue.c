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
// ID Code      : RL6463_Series_AutoMeasureColorValue.c
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


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
EnumAutoResult ScalerAutoMeasureColorValue(BYTE ucColor, bit bSelectMax, BYTE *pucResult);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Measure color min/max from specific channel
// Input Value  : ucColor --> R/G/B
//                pucResult --> memory to store measure result
// Output Value : _AUTO_FAIL or _AUTO_SUCCESS
//--------------------------------------------------
EnumAutoResult ScalerAutoMeasureColorValue(BYTE ucColor, bit bSelectMax, BYTE *pucResult)
{
    // Disable 121-LPF; Set to R channel for auto-balance new mode
    ScalerSetBit(P0_7A_AUTO_ADJ_CTRL0, ~(_BIT5 | _BIT1 | _BIT0), _BIT1);

    // Enable image auto-balance new mode
    ScalerSetBit(P0_76_RED_NOISE_MARGIN, ~_BIT0, _BIT0);

    // Start Measure
    if(ScalerAutoCompareMeasure((bSelectMax == _TRUE) ? _MEASURE_MAX : _MEASURE_RGB_MIN) == _AUTO_FAIL)
    {
        return _AUTO_FAIL;
    }

    switch(ucColor)
    {
        case _AUTO_RED_CHANNEL:
            *pucResult = ScalerGetByte(P0_84_AUTO_PHASE_3);
            break;

        case _AUTO_GREEN_CHANNEL:
            *pucResult = ScalerGetByte(P0_85_AUTO_PHASE_2);
            break;

        case _AUTO_BLUE_CHANNEL:
            *pucResult = ScalerGetByte(P0_86_AUTO_PHASE_1);
            break;

        default:
            return _AUTO_FAIL;
    }

    return _AUTO_SUCCESS;
}

