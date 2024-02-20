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
// ID Code      : RL6432_Series_FormatConversion.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
void ScalerFmtCnvInitialSetting(EnumSourceSearchPort enumSourceSearchPort);
EnumFormatConversionSourceType ScalerFmtCnvGetSourceType(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initialize for format conversion
// Input Value  : enumSourceSearchPort --> input port
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvInitialSetting(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
        case _A0_INPUT_PORT:

            // Set source index to A0
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_ADC << 4));
            break;

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            // Set source index to D0
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D0 << 4));
            break;

        case _D1_INPUT_PORT:

#if(_D1_DP_EXIST == _ON)
            // Set source index to D1
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D1 << 4));
#else
            // Set source index to D2
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D2 << 4));
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            if(ScalerDualLinkDVIRx2GetDualDVIMode() == _TRUE)
            {
                // Set source index to DUAL DVI
                ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_DUAL_DVI << 4));
            }
            else
#endif
            {
                // Set source index to D2
                ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D2 << 4));
            }

            break;

        case _D3_INPUT_PORT:

            // Set source index to D3
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D3 << 4));
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Show format conversion input source
// Input Value  : NONE
// Output Value : Current format conversino source
//--------------------------------------------------
EnumFormatConversionSourceType ScalerFmtCnvGetSourceType(void)
{
    return (EnumFormatConversionSourceType)(ScalerGetBit(P31_00_FC_INPUT_SEL_P01, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
}

