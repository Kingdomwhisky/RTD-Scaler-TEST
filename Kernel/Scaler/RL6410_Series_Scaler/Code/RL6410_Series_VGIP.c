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
// ID Code      : RL6410_Series_VGIP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6410_SERIES_VGIP__

#include "ScalerFunctionInclude.h"

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
void ScalerVgipInputInitial(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial for VGIP Input
// Input Value  : Input Source Type
// Output Value : None
//--------------------------------------------------
void ScalerVgipInputInitial(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
    enumSourceType = enumSourceType;

    // Initial format conversion
    ScalerFmtCnvInitialSetting(enumSourceSearchPort);

    // Set source from format conversion; Disable Double buffer, Analog Capture, and Stop generate DE
    ScalerSetBit(P0_10_M1_VGIP_CTRL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

    // HS Sync Edge select to Positive, Disable 1 clock Delay Mode
    ScalerSetBit(P0_12_M1_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3 | _BIT2), 0x00);

    // Set M2 VGIP state
    ScalerSetBit(P40_10_M2_VGIP_CTRL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
    ScalerSetBit(P40_12_M2_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3 | _BIT2), 0x00);

    // Reset field detect edge
    ScalerSetBit(P0_11_M1_VGIP_SIGINV, ~(_BIT5 | _BIT3), 0x00);
    ScalerSetBit(P40_11_M2_VGIP_SIGINV, ~(_BIT5 | _BIT3), 0x00);

#if(_FREESYNC_SUPPORT == _ON)
    if((GET_FREESYNC_ENABLED() == _TRUE) && (enumSourceType == _SOURCE_DP))
    {
        // Enable bypass Vsync
        ScalerVgipVsBypassEnable(_ENABLE);
    }
    else
    {
        // Disable bypass Vsync
        ScalerVgipVsBypassEnable(_DISABLE);
    }
#else
    // Disable bypass Vsync
    ScalerVgipVsBypassEnable(_DISABLE);
#endif

    // Set clock gating
    ScalerSetBit(P80_1F_S1_ICLK_GATED_CTRL1, ~_BIT3, 0x00);
    ScalerSetBit(PC0_1F_S2_ICLK_GATED_CTRL1, ~_BIT3, 0x00);

#if((_MEASURE_ADJUSTED_IHF_SUPPORT == _ON) || (_MEASURE_ADJUSTED_IVF_SUPPORT == _ON))
    // Set to analog measure
    ScalerVgipSetDigitalCaptureStatus(_DISABLE);
#endif

    // Initial IVS/IHS Delay for Capture and Auto
    ScalerVgipSetCaptureHDelay(0x00);
    ScalerVgipSetCaptureVDelay(0x00);

#if((_MEASURE_ADJUSTED_IHF_SUPPORT == _ON) || (_MEASURE_ADJUSTED_IVF_SUPPORT == _ON))
    ScalerVgipSetCaptureHStartPosition(0x00);
    ScalerVgipSetCaptureVStartPosition(0x00);

    // Set to digital measure
    ScalerVgipSetDigitalCaptureStatus(_ENABLE);
#endif
}
