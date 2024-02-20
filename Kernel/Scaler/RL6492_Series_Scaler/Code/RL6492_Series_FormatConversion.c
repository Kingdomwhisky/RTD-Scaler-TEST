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
// ID Code      : RL6492_Series_FormatConversion.c No.0000
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
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            // Set source index to D0
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D0 << 4));
            break;

        default:
            break;
    }

    // Reset Read Index
    ScalerSetBit(P31_0C_CTS_FIFO_CTRL, ~(_BIT1), 0x00);
}

//--------------------------------------------------
// Description  : Show format conversion input source
// Input Value  : NONE
// Output Value : Current format conversino source
//--------------------------------------------------
EnumFormatConversionSourceType ScalerFmtCnvGetSourceType(void)
{
    switch(ScalerGetBit(P31_00_FC_INPUT_SEL_P01, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4)
    {
        case 0x02:
            return _FC_SOURCE_ADC;

        case 0x03:
            if(ScalerGetBit(PB_00_HD_DP_SEL, (_BIT1 | _BIT0)) == 0x00)
            {
                return _FC_SOURCE_D0;
            }
            else
            {
                if(ScalerGetBit(P1D_16_BANDGAP_02, _BIT7) == 0)
                {
                    return _FC_SOURCE_D1;
                }
                else
                {
                    return _FC_SOURCE_D2;
                }
            }

        default:
            return _FC_SOURCE_NONE;
    }
}

