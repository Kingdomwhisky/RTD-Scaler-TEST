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
// ID Code      : RL6449_Series_ColorSixColorAdjustDell.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6449_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Table Length
//--------------------------------------------------
#define _SIXCOLOR_TABLE_SIZE_MSB_DELL                  16
#define _SIXCOLOR_TABLE_SIZE_LSB_DELL                  4
#define _SIXCOLOR_TABLE_SIZE_AXIS_DELL                 16
#define _SIXCOLOR_TO_GRAY_TABLE_SIZE_LSB_DELL          20

//--------------------------------------------------
// Definitions of Six Color
//--------------------------------------------------
#define _SIX_COLOR_RIGHTBUFFER_DELL                    0
#define _SIX_COLOR_RIGHTWIDTH_DELL                     1
#define _SIX_COLOR_CENTER_DELL                         2
#define _SIX_COLOR_LEFTWIDTH_DELL                      3
#define _SIX_COLOR_LEFTBUFFER_DELL                     4


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// Code Tables of SixColor
//--------------------------------------------------
SWORD code tSIX_COLOR_U_MAX_8_DELL[] =
{
    256, -256, -512, -256, 256, 512,
};

SWORD code tSIX_COLOR_V_MAX_8_DELL[] =
{
    512, 512, 0, -512, -512, 0,
};

SWORD code tSIX_COLOR_CTOC_DELTA_UV_DOWN_DELL[][2] =
{
    {-512,    0},
    {-256, -512},
    { 256, -512},
    { 512,    0},
    { 256,  512},
    {-256,  512},
};

SWORD code tSIX_COLOR_CTOC_DELTA_UV_UP_DELL[][2] =
{
    { 256, -512},
    { 512,    0},
    { 256,  512},
    {-256,  512},
    {-512,    0},
    {-256, -512},
};

SWORD code tSIX_COLOR_CTOC_DELTA_Y_DOWN_DELL[] =
{
    143, -81, 49, -130, 80, -51,
};

SWORD code tSIX_COLOR_CTOC_DELTA_Y_UP_DELL[] =
{
    79, -131, 81, -46, 131, -80,
};

code BYTE tICM_TABLE_GRAY_LSB_DELL[] =
{
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerColorSixColorAdjustDell(BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);
void ScalerColorSixColorICMLoadDell(SWORD shDeltaY, BYTE *pucICMData, BYTE ucCMSel, BYTE ucLoadSelect);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : 6 Color ICM adjust
// Input Value  : ucColorIndex --> Color Adjusted Now
//                ucHuePosition --> Hue position after mapping
//                ucSatPosition --> Sat position after mapping
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorAdjustDell(BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition)
{
    BYTE pucCentDeltaUV[16];
    BYTE ucLastIndex = 0;
    BYTE ucNextIndex = 0;
    BYTE ucPointIndex = 0;
    SWORD shDeltaSat = 0;
    SWORD shDeltaUmax1 = 0;
    SWORD shDeltaVmax1 = 0;
    SWORD shDeltaUmax = 0;
    SWORD shDeltaVmax = 0;
    SWORD shDeltaY = 0;
    SWORD shDeltaU = 0;
    SWORD shDeltaV = 0;
    memset(pucCentDeltaUV, 0, sizeof(pucCentDeltaUV));

    ucLastIndex = (ucColorIndex == 0) ? 5 : (ucColorIndex - 1);
    ucNextIndex = (ucColorIndex == 5) ? 0 : (ucColorIndex + 1);

    // Not Use SCM
    ScalerSetBit(P7_CD_SCM_BLOCK_SELECT, ~_BIT4, 0x00);

    // Delta Saturation = (-512 * 200 + ((512 - (-512)) * ucSatPosition)) / 200
    shDeltaSat = ((SDWORD)-102400 + ((SDWORD)ucSatPosition << 10)) / 200;

    if(ucHuePosition > 50)
    {
        shDeltaUmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_DOWN_DELL[ucColorIndex][0] * (ucHuePosition - 50) / 50;
        shDeltaVmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_DOWN_DELL[ucColorIndex][1] * (ucHuePosition - 50) / 50;
        shDeltaY = (SDWORD)tSIX_COLOR_CTOC_DELTA_Y_DOWN_DELL[ucColorIndex] * (ucHuePosition - 50) / 50;
    }
    else if(ucHuePosition < 50)
    {
        shDeltaUmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_UP_DELL[ucColorIndex][0] * (50 - ucHuePosition) / 50;
        shDeltaVmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_UP_DELL[ucColorIndex][1] * (50 - ucHuePosition) / 50;
        shDeltaY = (SDWORD)tSIX_COLOR_CTOC_DELTA_Y_UP_DELL[ucColorIndex] * (50 - ucHuePosition) / 50;
    }
    else
    {
        shDeltaUmax = 0;
        shDeltaVmax = 0;
        shDeltaY = 0;
    }

    shDeltaUmax1 = tSIX_COLOR_U_MAX_8_DELL[ucColorIndex] + shDeltaUmax;
    shDeltaVmax1 = tSIX_COLOR_V_MAX_8_DELL[ucColorIndex] + shDeltaVmax;

    shDeltaUmax1 = (SDWORD)shDeltaSat * shDeltaUmax1 >> 9;
    shDeltaVmax1 = (SDWORD)shDeltaSat * shDeltaVmax1 >> 9;

    shDeltaUmax = (shDeltaUmax1 + shDeltaUmax) >> 3;
    shDeltaVmax = (shDeltaVmax1 + shDeltaVmax) >> 3;

    for(ucPointIndex = 0; ucPointIndex < 8; ucPointIndex++)
    {
        shDeltaU = (shDeltaUmax * (ucPointIndex + 1)) >> 3;
        shDeltaV = (shDeltaVmax * (ucPointIndex + 1)) >> 3;

        shDeltaU = MAXOF(-128, MINOF(127, shDeltaU));
        shDeltaV = MAXOF(-128, MINOF(127, shDeltaV));

        pucCentDeltaUV[ucPointIndex << 1] = shDeltaU & 0xFF;
        pucCentDeltaUV[(ucPointIndex << 1) + 1] = shDeltaV & 0xFF;
    }

    ScalerColorSixColorICMLoadDell(shDeltaY, pucCentDeltaUV, ucColorIndex, _SIX_COLOR_CENTER_DELL);
    ScalerColorSixColorICMLoadDell(shDeltaY, pucCentDeltaUV, ucColorIndex, _SIX_COLOR_LEFTWIDTH_DELL);
    ScalerColorSixColorICMLoadDell(shDeltaY, pucCentDeltaUV, ucColorIndex, _SIX_COLOR_LEFTBUFFER_DELL);
    ScalerColorSixColorICMLoadDell(shDeltaY, pucCentDeltaUV, ucNextIndex, _SIX_COLOR_RIGHTWIDTH_DELL);
    ScalerColorSixColorICMLoadDell(shDeltaY, pucCentDeltaUV, ucNextIndex, _SIX_COLOR_RIGHTBUFFER_DELL);

    // Set LSB to 0
    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), ucColorIndex);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_6F_PORT_CMN_MST_00_01_UV_OFFSET_L);
    ScalerBurstWrite(tICM_TABLE_GRAY_LSB_DELL, _SIXCOLOR_TO_GRAY_TABLE_SIZE_LSB_DELL, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Set dy LSB to 0
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_87_PORT_CMN_AXIS_DELY_L);
    ScalerSetByte(P7_D3_ICM_DATA, 0x00);
}

//--------------------------------------------------
// Description   : Fill 6 Color ICM Data
// Input Value   : pucICMData --> Point to ICM uvoffset
//                 ucCMSel --> Color selected
//                   ucLoadSelect --> Axis selected
// Output Value  : None
//--------------------------------------------------
void ScalerColorSixColorICMLoadDell(SWORD shDeltaY, BYTE *pucICMData, BYTE ucCMSel, BYTE ucLoadSelect)
{
    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);

    switch(ucLoadSelect)
    {
        case _SIX_COLOR_RIGHTBUFFER_DELL:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_33_PORT_CMN_RBUF_00_DU_H);
            break;

        case _SIX_COLOR_RIGHTWIDTH_DELL:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_13_PORT_CMN_RWID_00_DU_H);
            break;

        case _SIX_COLOR_CENTER_DELL:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_03_PORT_CMN_MST_00_DU_H);
            break;

        case _SIX_COLOR_LEFTWIDTH_DELL:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_23_PORT_CMN_LWID_00_DU_H);
            break;

        case _SIX_COLOR_LEFTBUFFER_DELL:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_43_PORT_CMN_LBUF_00_DU_H);
            break;

        default:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_23_PORT_CMN_LWID_00_DU_H);
            break;
    }

    ScalerBurstWrite(pucICMData, _SIXCOLOR_TABLE_SIZE_AXIS_DELL, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);

    switch(ucLoadSelect)
    {
        case _SIX_COLOR_RIGHTBUFFER_DELL:
            return;

        case _SIX_COLOR_RIGHTWIDTH_DELL:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_6B_PORT_CMN_R_AXIS_DELY_H);
            break;

        case _SIX_COLOR_CENTER_DELL:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_69_PORT_CMN_M_AXIS_DELY_H);
            break;

        case _SIX_COLOR_LEFTWIDTH_DELL:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_6D_PORT_CMN_L_AXIS_DELY_H);
            break;

        case _SIX_COLOR_LEFTBUFFER_DELL:
            return;

        default:
            return;
    }

    ScalerSetByte(P7_D3_ICM_DATA, (BYTE)((shDeltaY >> 8) & 0xFF));
    ScalerSetByte(P7_D3_ICM_DATA, (BYTE)(shDeltaY & 0xFF));
}
