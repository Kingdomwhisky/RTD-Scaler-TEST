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
// ID Code      : ScalerColorSpaceConvertLoadTable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// Code Tables of Color Conversion
//--------------------------------------------------
// RGB to YCC Table
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
BYTE code tCOLOR_CONV_RGB2YUV_ITU709[] = // enable RGB2YUV
{
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0x00, 0xBA, 0x02, 0x73, 0x00, 0x3F, // h00~h02 MSB
    0xFF, 0x99, 0xFE, 0xA6, 0x01, 0xC0, // h10~h12 MSB
    0x01, 0xC0, 0xFE, 0x68, 0xFF, 0xD6, // h20~h22 MSB
    0x31, 0x22, 0x34, 0x45, 0x70,       // h00~h22 LSB
    _END
#elif(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1)
    21, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0x00, 0xBA, 0x02, 0x73, 0x00, 0x3F, // h00~h02 MSB
    0xFF, 0x99, 0xFE, 0xA6, 0x01, 0xC0, // h10~h12 MSB
    0x01, 0xC0, 0xFE, 0x68, 0xFF, 0xD6, // h20~h22 MSB
    _END
#endif
};
#endif


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
void ScalerColorSpaceConvertLoadTable(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
//--------------------------------------------------
// Description  : Load Table for Color Space Conversion
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvertLoadTable(void)
{
    // Enable I-Domain RGB2YUV coefficient Access, Set Y_Out/CbCr_Out Shift
    ScalerSetBit(P0_9C_RGB2YCC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), (_BIT7 | _BIT6 | _BIT3));

    // Load I-Domain RGB2YUV Table for UltraVivid or RGB Quantization Limit Range Case
    ScalerBurstWrite(tCOLOR_CONV_RGB2YUV_ITU709, sizeof(tCOLOR_CONV_RGB2YUV_ITU709), GET_CURRENT_BANK_NUMBER(), P0_9D_RGB2YCC_COEF_DATA, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    // Disable I-Domain RGB2YUV coefficient Access
    ScalerSetBit(P0_9C_RGB2YCC_CTRL, ~_BIT3, 0x00);
}
#endif
