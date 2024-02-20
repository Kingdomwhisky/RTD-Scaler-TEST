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
// ID Code      : ScalerColorSpaceLoadYuv2RgbTable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _COLOR_CONV_YUV2RGB_TABLE_SIZE                          26


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// Code Tables of Color Conversion
//--------------------------------------------------
// YCC to RGB Table
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
BYTE code tCOLOR_CONV_YUV2RGB_ITU601[] =
{
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0xE4, 0xAB, 0x26, 0x67, 0x41, 0x92,
    0xE3, 0x42, 0xC8, 0x17, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
};

BYTE code tCOLOR_CONV_YUV2RGB_ITU709[] =
{
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0xE4, 0xAB, 0x27, 0x31, 0x00, 0xDB,
    0x42, 0x23, 0x88, 0x79, 0x00, 0x10,
    0x00, 0x10, 0x00, 0x10, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
};

BYTE code tCOLOR_CONV_YUV2RGB_ITU709_RGBLIMIT[] =
{
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0xE4, 0xAB, 0x27, 0x31, 0x00, 0xDB,
    0x42, 0x23, 0x88, 0x79, 0xF0, 0x00,
    0xF0, 0x00, 0xF0, 0x00, 0x02, 0x56,
    0x02, 0x56, 0x02, 0x56,
    _END
#elif(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1)
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0xE4, 0xAB, 0x27, 0x31, 0x00, 0xDB,
    0x42, 0x23, 0x88, 0x79, 0x3C, 0x00,
    0x3C, 0x00, 0x3C, 0x00, 0x02, 0x56,
    0x02, 0x56, 0x02, 0x56,
    _END
#endif
};
#endif // End of #if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))

BYTE code tCOLOR_CONV_YUV2RGB_ITU601_YUVFULL[] =
{
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0x04, 0x00, 0xA5, 0x9B, 0x61, 0x60,
    0x42, 0xDB, 0x87, 0x16, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
#elif(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_3)
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0x04, 0x00, 0x05, 0x9C, 0x01, 0x60,
    0x02, 0xDB, 0x07, 0x17, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
#endif
};

BYTE code tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL[] =
{
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0x04, 0x00, 0xA6, 0x4C, 0xC0, 0xBF,
    0x61, 0xDF, 0x27, 0x6C, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
#elif(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_3)
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0x04, 0x00, 0x06, 0x4D, 0x00, 0xC0,
    0x01, 0xDF, 0x07, 0x6C, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
#endif
};

// YCC to RGB Table - 8bit
BYTE code tCOLOR_CONV_YUV2RGB_ITU601_8BIT[] =
{
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0x64, 0xA8, 0x66, 0x62, 0x21, 0x91,
    0x63, 0x40, 0xA8, 0x11, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
#elif(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_3)
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0x04, 0xA8, 0x06, 0x62, 0x01, 0x91,
    0x03, 0x40, 0x08, 0x12, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
#endif
};

BYTE code tCOLOR_CONV_YUV2RGB_ITU709_8BIT[] =
{
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0x64, 0xA8, 0xC7, 0x2B, 0x60, 0xDA,
    0xA2, 0x21, 0x28, 0x73, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
#elif(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_3)
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0x04, 0xAD, 0x07, 0x34, 0x00, 0xDA,
    0x02, 0x23, 0x08, 0x7C, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
#endif
};

BYTE code tCOLOR_CONV_YUV2RGB_ITU709_RGBLIMIT_8BIT[] =
{
#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0xE4, 0xAB, 0x27, 0x31, 0x00, 0xDB,
    0x42, 0x23, 0x88, 0x79, 0xF0, 0x00,
    0xF0, 0x00, 0xF0, 0x00, 0x02, 0x54,
    0x02, 0x54, 0x02, 0x54,
    _END
#elif(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1)
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0xE4, 0xAB, 0x27, 0x31, 0x00, 0xDB,
    0x42, 0x23, 0x88, 0x79, 0x3C, 0x00,
    0x3C, 0x00, 0x3C, 0x00, 0x02, 0x54,
    0x02, 0x54, 0x02, 0x54,
    _END
#elif(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_3)
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0x04, 0xAD, 0x07, 0x34, 0x00, 0xDA,
    0x02, 0x23, 0x08, 0x7C, 0x3C, 0x00,
    0x3C, 0x00, 0x3C, 0x00, 0x02, 0x54,
    0x02, 0x54, 0x02, 0x54,
    _END
#endif
};

#if(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2)
// BT2020 Constant Table
/*
BYTE code tCOLOR_CONV_YUV2RGB_ITU_BT2020_CL[] =
{
    52, _AUTOINC, (BYTE)P14_40_SR_BT2020_COEF_H11_HSB,
    0x01, 0x2A, 0xF8, 0x01, 0x2A, 0xF8, 0x01, 0x2A, 0xF8,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x37, 0x28,
    0x01, 0xF6, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xCE, 0x48,
    0x01, 0x22, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x80, 0x00,

    15, _AUTOINC, (BYTE)P14_AC_SR_YCC2RGB_R_OFFSET_MSB,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x02, 0x00, 0x02, 0x00,
    _END
};*/

// BT2020 NonConstant Table
BYTE code tCOLOR_CONV_YUV2RGB_ITU_BT2020_NCL[] =
{
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0xE4, 0xAB, 0x06, 0xBC, 0x60, 0xC0,
    0x02, 0x9C, 0xA8, 0x97, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
};

BYTE code tCOLOR_CONV_YUV2RGB_ITU_BT2020_NCL_YUVFULL[] =
{
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB,
    0x04, 0x00, 0x05, 0xE6, 0x80, 0xA8,
    0x22, 0x49, 0x87, 0x86, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
};
#endif // End of #if(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2)

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerColorSpaceLoadYuv2RgbTable(EnumColorSpace enumColorSpace, bit bUltraVividSupport);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Color Space Load YUV2RGB table
// Input Value  : enumColorSpace --> Color Space RGB or not
//                bUltraVividSupport --> UltraVivid Support
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceLoadYuv2RgbTable(EnumColorSpace enumColorSpace, bit bUltraVividSupport)
{
    BYTE *pucYUV2RGBTable = 0x00;

#if((_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_1) || (_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2))
    BYTE code *pucYUV2RGB601Table = tCOLOR_CONV_YUV2RGB_ITU601;
    BYTE code *pucYUV2RGB709Table = tCOLOR_CONV_YUV2RGB_ITU709;
    BYTE code *pucYUV2RGB709RGBLimitTable = tCOLOR_CONV_YUV2RGB_ITU709_RGBLIMIT;
    BYTE code *pucYUV2RGB601Table8bit = tCOLOR_CONV_YUV2RGB_ITU601_8BIT;
    BYTE code *pucYUV2RGB709Table8bit = tCOLOR_CONV_YUV2RGB_ITU709_8BIT;
    BYTE code *pucYUV2RGB709RGBLimitTable8bit = tCOLOR_CONV_YUV2RGB_ITU709_RGBLIMIT_8BIT;
#elif(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_3)
    BYTE code *pucYUV2RGB601Table = tCOLOR_CONV_YUV2RGB_ITU601_8BIT;
    BYTE code *pucYUV2RGB709Table = tCOLOR_CONV_YUV2RGB_ITU709_8BIT;
    BYTE code *pucYUV2RGB709RGBLimitTable = tCOLOR_CONV_YUV2RGB_ITU709_RGBLIMIT_8BIT;
    BYTE code *pucYUV2RGB601Table8bit = tCOLOR_CONV_YUV2RGB_ITU601_8BIT;
    BYTE code *pucYUV2RGB709Table8bit = tCOLOR_CONV_YUV2RGB_ITU709_8BIT;
    BYTE code *pucYUV2RGB709RGBLimitTable8bit = tCOLOR_CONV_YUV2RGB_ITU709_RGBLIMIT_8BIT;
#endif

    bUltraVividSupport = bUltraVividSupport;

    if((GET_COLOR_SPACE_RGB(enumColorSpace) == _TRUE) &&
       (GET_COLOR_RGB_LIMIT_RANGE_USER() == _TRUE))
    {
        // Load D-Domain YUV2RGB Table according for RGB Limit Range
        if(GET_COLOR_DEPTH() > _COLOR_DEPTH_8_BITS)
        {
            pucYUV2RGBTable = pucYUV2RGB709RGBLimitTable;
        }
        else
        {
            pucYUV2RGBTable = pucYUV2RGB709RGBLimitTable8bit;
        }

#if(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_0)
        if(bUltraVividSupport == _ON)
        {
            // Set D-Domain YUV2RGB YCbCr Clamp
            ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
        }
        else
#endif
        {
            if(ScalerGetBit(P0_9C_RGB2YCC_CTRL, _BIT0) == 0x00)
            {
                // Disable D-Domain YUV2RGB YCbCr Clamp for Identity_Matrix
                ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL, ~(_BIT2 | _BIT1), 0x00);
            }
            else
            {
                // Enable D-Domain YUV2RGB YCbCr Clamp
                ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
            }
        }
    }
    else if((GET_COLOR_SPACE_RGB(enumColorSpace) == _FALSE) && (GET_COLOR_YCC_FULL_RANGE_USER() == _TRUE))
    {
        // Load D-Domain YUV2RGB Table according to Colorimetry
        switch(GET_COLORIMETRY())
        {
            case _COLORIMETRY_YCC_SMPTE_170M:
            case _COLORIMETRY_YCC_ITUR_BT601:
            case _COLORIMETRY_YCC_XVYCC601:
                pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU601_YUVFULL;
                break;

            case _COLORIMETRY_YCC_ITUR_BT709:
            case _COLORIMETRY_YCC_XVYCC709:
                pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL;
                break;

            case _COLORIMETRY_EXT:
                switch(GET_EXT_COLORIMETRY())
                {
                    case _COLORIMETRY_EXT_YCC_ITUR_BT601:
                    case _COLORIMETRY_EXT_YCC_XVYCC601:
                    case _COLORIMETRY_EXT_YCC_SYCC601:
                    case _COLORIMETRY_EXT_YCC_ADOBEYCC601:
                        pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU601_YUVFULL;
                        break;

#if(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2)
                    case _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL:
                    case _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL:
                        pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU_BT2020_NCL_YUVFULL;
                        break;
#endif

                    case _COLORIMETRY_EXT_YCC_ITUR_BT709:
                    case _COLORIMETRY_EXT_YCC_XVYCC709:
                    default:
                        pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL;
                        break;
                }
                break;

            default:
                pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL;
                break;
        }

        // Set D-Domain YUV2RGB YCbCr Clamp
        ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL, ~(_BIT2 | _BIT1), _BIT2);
    }
    else
    {
        // Load D-Domain YUV2RGB Table according to Colorimetry
        switch(GET_COLORIMETRY())
        {
            case _COLORIMETRY_YCC_SMPTE_170M:
            case _COLORIMETRY_YCC_ITUR_BT601:
            case _COLORIMETRY_YCC_XVYCC601:
                if(GET_COLOR_DEPTH() > _COLOR_DEPTH_8_BITS)
                {
                    pucYUV2RGBTable = pucYUV2RGB601Table;
                }
                else
                {
                    pucYUV2RGBTable = pucYUV2RGB601Table8bit;
                }
                break;

            case _COLORIMETRY_YCC_ITUR_BT709:
            case _COLORIMETRY_YCC_XVYCC709:
                if(GET_COLOR_DEPTH() > _COLOR_DEPTH_8_BITS)
                {
                    pucYUV2RGBTable = pucYUV2RGB709Table;
                }
                else
                {
                    pucYUV2RGBTable = pucYUV2RGB709Table8bit;
                }
                break;

            case _COLORIMETRY_EXT:
                switch(GET_EXT_COLORIMETRY())
                {
                    case _COLORIMETRY_EXT_YCC_ITUR_BT601:
                    case _COLORIMETRY_EXT_YCC_XVYCC601:
                    case _COLORIMETRY_EXT_YCC_SYCC601:
                    case _COLORIMETRY_EXT_YCC_ADOBEYCC601:
                        if(GET_COLOR_DEPTH() > _COLOR_DEPTH_8_BITS)
                        {
                            pucYUV2RGBTable = pucYUV2RGB601Table;
                        }
                        else
                        {
                            pucYUV2RGBTable = pucYUV2RGB601Table8bit;
                        }
                        break;

#if(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2)
                    case _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL:
                    case _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL:
                        pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU_BT2020_NCL;
                        break;
#endif

                    case _COLORIMETRY_EXT_YCC_ITUR_BT709:
                    case _COLORIMETRY_EXT_YCC_XVYCC709:
                    default:
                        if(GET_COLOR_DEPTH() > _COLOR_DEPTH_8_BITS)
                        {
                            pucYUV2RGBTable = pucYUV2RGB709Table;
                        }
                        else
                        {
                            pucYUV2RGBTable = pucYUV2RGB709Table8bit;
                        }
                        break;
                }
                break;

            default:
                if(GET_COLOR_DEPTH() > _COLOR_DEPTH_8_BITS)
                {
                    pucYUV2RGBTable = pucYUV2RGB709Table;
                }
                else
                {
                    pucYUV2RGBTable = pucYUV2RGB709Table8bit;
                }
                break;
        }

        // Set D-Domain YUV2RGB YCbCr Clamp
        ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
    }

    ScalerBurstWrite(pucYUV2RGBTable, _COLOR_CONV_YUV2RGB_TABLE_SIZE,
                     GET_CURRENT_BANK_NUMBER(), P14_A2_SR_YCC2RGB_COEF_K11_MSB,
                     _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
}
