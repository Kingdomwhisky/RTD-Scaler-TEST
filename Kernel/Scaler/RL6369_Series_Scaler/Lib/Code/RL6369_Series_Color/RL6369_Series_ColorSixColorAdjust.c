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
// ID Code      : RL6369_Series_ColorSixColorAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6369_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Table Length
//--------------------------------------------------
#define _SIXCOLOR_TABLE_SIZE_MSB                  64
#define _SIXCOLOR_TABLE_SIZE_AXIS                 16

//--------------------------------------------------
// Definitions of Six Color
//--------------------------------------------------
#define _SIX_COLOR_RIGHTBUFFER                    0
#define _SIX_COLOR_RIGHTWIDTH                     1
#define _SIX_COLOR_CENTER                         2
#define _SIX_COLOR_LEFTWIDTH                      3
#define _SIX_COLOR_LEFTBUFFER                     4


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// Code Tables of SixColor
//--------------------------------------------------
SWORD code tSIX_COLOR_U_MAX_8[][3] =
{
    { 313,  255,  -35},
    {-134, -255, -310},
    {-366, -512, -363},
    {-313, -255, -125},
    { -52,  255,  313},
    { 396,  512,  402},
};

SWORD code tSIX_COLOR_V_MAX_8[][3] =
{
    { 396,  512,  512},
    { 512,  512,  403},
    { 290,    0, -297},
    {-396, -512, -512},
    {-512, -512, -396},
    {-231,    0,  219},
};

SWORD code tSIX_COLOR_CTOC_DELTA_UV_DOWN[][2] =
{
    {-447,    0}, // R-->Y
    {-179, -361}, // Y-->G
    { 226, -449}, // G-->C
    { 348,    0}, // C-->B
    { 193,  390}, // B-->M
    {-226,  449}, // M-->R
};

SWORD code tSIX_COLOR_RTOR_DELTA_UV_DOWN[][4] =
{
    { -58,  116, -390,    0},
    {-122,    0, -111, -221},
    {-145, -291,  198, -396},
    {  58, -116,  203,    0},
    { 309,    0,  140,  280},
    { 116,  232, -198,  396},
};

SWORD code tSIX_COLOR_LTOL_DELTA_UV_DOWN[][2] =
{
    {-221,    0},
    {-202, -404},
    { 107, -215},
    { 382,    0},
    { 198,  396},
    {-146,  293},
};

SWORD code tSIX_COLOR_CTOC_DELTA_UV_UP[][2] =
{
    { 197, -397}, // R-->M
    { 358,    0}, // Y-->R
    { 229,  454}, // G-->Y
    {-177,  358}, // C-->G
    {-444,    0}, // B-->C
    {-227, -450}, // M-->B
};

SWORD code tSIX_COLOR_RTOR_DELTA_UV_UP[][2] =
{
    { 198, -396},
    { 390,    0},
    { 111,  221},
    {-198,  396},
    {-203,    0},
    {-140, -280},
};

SWORD code tSIX_COLOR_LTOL_DELTA_UV_UP[][4] =
{
    { 291,    0,  146, -293},
    {  54,  108,  221,    0},
    {-149,  297,  202,  404},
    {-130,    0, -107,  215},
    { -58, -116, -382,    0},
    { 110, -219, -198, -396},
};

code BYTE tICM_TABLE_GRAY_R[] =
{
    0xFC, 0xF8, 0xF8, 0xF0, 0xF4, 0xE8, 0xF0, 0xE0, 0xEC, 0xD8, 0xE8, 0xD0, 0xE4, 0xC8, 0xE0, 0xC0,
    0xFB, 0xFA, 0xF6, 0xF4, 0xF1, 0xED, 0xEC, 0xE7, 0xE7, 0xE1, 0xE3, 0xDB, 0xDE, 0xD5, 0xD9, 0xCE,
    0x01, 0xF8, 0x01, 0xF0, 0x02, 0xE8, 0x02, 0xE0, 0x03, 0xD8, 0x03, 0xD0, 0x04, 0xC8, 0x04, 0xC0,
    0xFB, 0xFA, 0xF6, 0xF4, 0xF1, 0xED, 0xEC, 0xE7, 0xE7, 0xE1, 0xE3, 0xDB, 0xDE, 0xD5, 0xD9, 0xCE,
};

code BYTE tICM_TABLE_GRAY_Y[] =
{
    0x04, 0xF8, 0x08, 0xF0, 0x0C, 0xE8, 0x10, 0xE0, 0x14, 0xD8, 0x18, 0xD0, 0x1C, 0xC8, 0x20, 0xC0,
    0x02, 0xF8, 0x04, 0xF0, 0x06, 0xE8, 0x08, 0xE0, 0x0A, 0xD8, 0x0D, 0xD0, 0x0F, 0xC8, 0x11, 0xC0,
    0x05, 0xFA, 0x0A, 0xF3, 0x0F, 0xED, 0x13, 0xE7, 0x18, 0xE0, 0x1D, 0xDA, 0x22, 0xD4, 0x27, 0xCE,
    0x02, 0xF8, 0x04, 0xF0, 0x06, 0xE8, 0x08, 0xE0, 0x0A, 0xD8, 0x0D, 0xD0, 0x0F, 0xC8, 0x11, 0xC0,
};

code BYTE tICM_TABLE_GRAY_G[] =
{
    0x08, 0x00, 0x10, 0x00, 0x18, 0x00, 0x20, 0x00, 0x28, 0x00, 0x30, 0x00, 0x38, 0x00, 0x40, 0x00,
    0x06, 0xFB, 0x0B, 0xF7, 0x11, 0xF2, 0x17, 0xEE, 0x1D, 0xE9, 0x22, 0xE5, 0x28, 0xE0, 0x2E, 0xDC,
    0x06, 0x05, 0x0B, 0x09, 0x11, 0x0E, 0x17, 0x13, 0x1C, 0x17, 0x22, 0x1C, 0x28, 0x21, 0x2D, 0x25,
    0x06, 0xFB, 0x0B, 0xF7, 0x11, 0xF2, 0x17, 0xEE, 0x1D, 0xE9, 0x22, 0xE5, 0x28, 0xE0, 0x2E, 0xDC,
};

code BYTE tICM_TABLE_GRAY_C[] =
{
    0x04, 0x08, 0x08, 0x10, 0x0C, 0x18, 0x10, 0x20, 0x14, 0x28, 0x18, 0x30, 0x1C, 0x38, 0x20, 0x40,
    0x05, 0x06, 0x0A, 0x0C, 0x0F, 0x13, 0x14, 0x19, 0x19, 0x1F, 0x1D, 0x25, 0x22, 0x2B, 0x27, 0x32,
    0x02, 0x08, 0x04, 0x10, 0x06, 0x18, 0x08, 0x20, 0x0A, 0x28, 0x0C, 0x30, 0x0E, 0x38, 0x10, 0x40,
    0x05, 0x06, 0x0A, 0x0C, 0x0F, 0x13, 0x14, 0x19, 0x19, 0x1F, 0x1D, 0x25, 0x22, 0x2B, 0x27, 0x32,
};

code BYTE tICM_TABLE_GRAY_B[] =
{
    0xFC, 0x08, 0xF8, 0x10, 0xF4, 0x18, 0xF0, 0x20, 0xEC, 0x28, 0xE8, 0x30, 0xE4, 0x38, 0xE0, 0x40,
    0x01, 0x08, 0x02, 0x10, 0x02, 0x18, 0x03, 0x20, 0x04, 0x28, 0x05, 0x30, 0x06, 0x38, 0x07, 0x40,
    0xFB, 0x06, 0xF6, 0x0C, 0xF1, 0x13, 0xEC, 0x19, 0xE7, 0x1F, 0xE3, 0x25, 0xDE, 0x2B, 0xD9, 0x32,
    0x01, 0x08, 0x02, 0x10, 0x02, 0x18, 0x03, 0x20, 0x04, 0x28, 0x05, 0x30, 0x06, 0x38, 0x07, 0x40,
};

code BYTE tICM_TABLE_GRAY_M[] =
{
    0xF8, 0x00, 0xF0, 0x00, 0xE8, 0x00, 0xE0, 0x00, 0xD8, 0x00, 0xD0, 0x00, 0xC8, 0x00, 0xC0, 0x00,
    0xFA, 0x04, 0xF4, 0x07, 0xED, 0x0B, 0xE7, 0x0E, 0xE1, 0x12, 0xDB, 0x16, 0xD5, 0x19, 0xCE, 0x1D,
    0xFA, 0xFD, 0xF3, 0xF9, 0xED, 0xF6, 0xE7, 0xF2, 0xE1, 0xEF, 0xDA, 0xEB, 0xD4, 0xE8, 0xCE, 0xE5,
    0xFA, 0x04, 0xF4, 0x07, 0xED, 0x0B, 0xE7, 0x0E, 0xE1, 0x12, 0xDB, 0x16, 0xD5, 0x19, 0xCE, 0x1D,
};

code BYTE *tICM_TABLE_GRAY[] =
{
    tICM_TABLE_GRAY_R,
    tICM_TABLE_GRAY_Y,
    tICM_TABLE_GRAY_G,
    tICM_TABLE_GRAY_C,
    tICM_TABLE_GRAY_B,
    tICM_TABLE_GRAY_M,
};

//Osd Turning position to next CM
BYTE code tR_TURNING_POSITION_DOWN[] = {61, 66, 71, 68, 75, 69};
BYTE code tL_TURNING_POSITION_UP[] = {27, 34, 29, 33, 39, 32};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerColorSixColorAdjustNormal(BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);
void ScalerColorSixColorICMLoad(BYTE *pucICMData, BYTE ucCMSel, BYTE ucLoadSelect);


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
void ScalerColorSixColorAdjustNormal(BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition)
{
    BYTE pucCentDeltaUV[16];
    BYTE ucLastIndex = 0;
    BYTE ucAxis = 0;
    BYTE ucPointIndex = 0;
    SWORD shDeltaSat = 0;
    SWORD shDeltaUmax1 = 0;
    SWORD shDeltaVmax1 = 0;
    SWORD shDeltaUmax = 0;
    SWORD shDeltaVmax = 0;
    SWORD shDeltaU = 0;
    SWORD shDeltaV = 0;
    BYTE ucTurningPositiongUp = 0;
    BYTE ucTurningPositiongDown = 0;
    memset(pucCentDeltaUV, 0, sizeof(pucCentDeltaUV));

    ucLastIndex = (ucColorIndex == 0) ? 5 : (ucColorIndex - 1);

    if(ucSatPosition != 0)
    {
        ucTurningPositiongUp = tL_TURNING_POSITION_UP[ucColorIndex];
        ucTurningPositiongDown = tR_TURNING_POSITION_DOWN[ucColorIndex];

        // Delta Saturation = (-512 * 200 + ((512 - (-512)) * ucSatPosition)) / 200
        shDeltaSat = ((SDWORD)-102400 + ((SDWORD)ucSatPosition << 10)) / 200;

        for(ucAxis = 1; ucAxis < 4; ucAxis++)
        {
            // Calculate Delta Hue of one Axis

            if(ucAxis == _SIX_COLOR_RIGHTWIDTH)
            {
                if((ucHuePosition > 50) && (ucHuePosition <= ucTurningPositiongDown))
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][0] * (ucHuePosition - 50) / (ucTurningPositiongDown - 50);
                    shDeltaVmax = (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][1] * (ucHuePosition - 50) / (ucTurningPositiongDown - 50);
                }
                else if(ucHuePosition > ucTurningPositiongDown)
                {
                    shDeltaUmax = tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][0] + (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][2] * (ucHuePosition - ucTurningPositiongDown) / (100 - ucTurningPositiongDown);
                    shDeltaVmax = tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][1] + (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_DOWN[ucColorIndex][3] * (ucHuePosition - ucTurningPositiongDown) / (100 - ucTurningPositiongDown);
                }
                else if(ucHuePosition < 50)
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_UP[ucColorIndex][0] * (50 - ucHuePosition) / 50;
                    shDeltaVmax = (SDWORD)tSIX_COLOR_RTOR_DELTA_UV_UP[ucColorIndex][1] * (50 - ucHuePosition) / 50;
                }
                else
                {
                    shDeltaUmax = 0;
                    shDeltaVmax = 0;
                }
            }
            else if(ucAxis == _SIX_COLOR_CENTER)
            {
                if(ucHuePosition > 50)
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_DOWN[ucColorIndex][0] * (ucHuePosition - 50) / 50;
                    shDeltaVmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_DOWN[ucColorIndex][1] * (ucHuePosition - 50) / 50;
                }
                else if(ucHuePosition < 50)
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_UP[ucColorIndex][0] * (50 - ucHuePosition) / 50;
                    shDeltaVmax = (SDWORD)tSIX_COLOR_CTOC_DELTA_UV_UP[ucColorIndex][1] * (50 - ucHuePosition) / 50;
                }
                else
                {
                    shDeltaUmax = 0;
                    shDeltaVmax = 0;
                }
            }
            else
            {
                if(ucHuePosition > 50)
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_DOWN[ucColorIndex][0] * (ucHuePosition - 50) / 50;
                    shDeltaVmax = (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_DOWN[ucColorIndex][1] * (ucHuePosition - 50) / 50;
                }
                else if((ucHuePosition < 50) && (ucHuePosition >= ucTurningPositiongUp))
                {
                    shDeltaUmax = (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][0] * (50 - ucHuePosition) / (50 - ucTurningPositiongUp);
                    shDeltaVmax = (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][1] * (50 - ucHuePosition) / (50 - ucTurningPositiongUp);
                }
                else if(ucHuePosition < ucTurningPositiongUp)
                {
                    shDeltaUmax = tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][0] + (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][2] * (ucTurningPositiongUp - ucHuePosition) / ucTurningPositiongUp;
                    shDeltaVmax = tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][1] + (SDWORD)tSIX_COLOR_LTOL_DELTA_UV_UP[ucColorIndex][3] * (ucTurningPositiongUp - ucHuePosition) / ucTurningPositiongUp;
                }
                else
                {
                    shDeltaUmax = 0;
                    shDeltaVmax = 0;
                }
            }

            shDeltaUmax1 = tSIX_COLOR_U_MAX_8[ucColorIndex][ucAxis - 1] + shDeltaUmax;
            shDeltaVmax1 = tSIX_COLOR_V_MAX_8[ucColorIndex][ucAxis - 1] + shDeltaVmax;

            shDeltaUmax1 = ((SDWORD)shDeltaSat * shDeltaUmax1) >> 9;
            shDeltaVmax1 = ((SDWORD)shDeltaSat * shDeltaVmax1) >> 9;

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

            ScalerColorSixColorICMLoad(pucCentDeltaUV, ucColorIndex, ucAxis);

            if(ucAxis == _SIX_COLOR_RIGHTWIDTH)
            {
                ScalerColorSixColorICMLoad(pucCentDeltaUV, ucColorIndex, _SIX_COLOR_RIGHTBUFFER);
                ScalerColorSixColorICMLoad(pucCentDeltaUV, ucLastIndex, _SIX_COLOR_LEFTBUFFER);
            }
        }
    }
    else
    {
        // Load Code Table
        ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), ucColorIndex);
        ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_03_PORT_CMN_MST_00_DU_H);
        ScalerBurstWrite(tICM_TABLE_GRAY[ucColorIndex], _SIXCOLOR_TABLE_SIZE_MSB, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), ucLastIndex);
        ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_43_PORT_CMN_LBUF_00_DU_H);
        ScalerBurstWrite(&tICM_TABLE_GRAY[ucColorIndex][16], 16, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }
}

//--------------------------------------------------
// Description   : Fill 6 Color ICM Data
// Input Value   : pucICMData --> Point to ICM uvoffset
//                 ucCMSel --> Color selected
//                   ucLoadSelect --> Axis selected
// Output Value  : None
//--------------------------------------------------
void ScalerColorSixColorICMLoad(BYTE *pucICMData, BYTE ucCMSel, BYTE ucLoadSelect)
{
    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);

    switch(ucLoadSelect)
    {
        // Rightbuffer
        case 0:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_33_PORT_CMN_RBUF_00_DU_H);
            break;

        // Rightwidth
        case 1:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_13_PORT_CMN_RWID_00_DU_H);
            break;

        // Center
        case 2:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_03_PORT_CMN_MST_00_DU_H);
            break;

        // Leftwidth
        case 3:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_23_PORT_CMN_LWID_00_DU_H);
            break;

        // Leftbuffer
        case 4:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_43_PORT_CMN_LBUF_00_DU_H);
            break;

        default:
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_23_PORT_CMN_LWID_00_DU_H);
            break;
    }

    ScalerBurstWrite(pucICMData, _SIXCOLOR_TABLE_SIZE_AXIS, GET_CURRENT_BANK_NUMBER(), P7_D3_ICM_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
}
