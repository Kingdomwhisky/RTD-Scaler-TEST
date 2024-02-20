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
// ID Code      : RL6432_Series_ColorSixColorInitialDell.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
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
SWORD code tSIX_COLOR_DEFAULT_ANGLE_DELL[][5] =
{
    {   0,    0,  722,  722,  722},
    { 722,    0,  604,  604,  604},
    {1326,    0,  722,  722,  722},
    {2048,    0,  722,  722,  722},
    {2770,    0,  604,  604,  604},
    {3374,    0,  722,  722,  722},
};

SWORD code tSIX_COLOR_U_MAX_DELL[][5] =
{
    {2047, 2047, 1024, 1024, 1024},
    {1024, 1024, 3072, 3072, 3072},
    {3072, 3072, 2048, 2048, 2048},
    {2048, 2048, 3072, 3072, 3072},
    {3072, 3072, 1024, 1024, 1024},
    {1024, 1024, 2047, 2047, 2047},
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerColorSixColorSetAngleRBDell(BYTE ucCMSel);
void ScalerColorSixColorInitialDell(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set range for one CM
// Input Value  : ucCMSel --> Color selected
//                shRBuffer --> Right buffer hue
//                shRWidth --> Right range
//                shAngle --> Master Range
//                shLWidth --> Left Range
//                shLBuffer --> Left Buffer Range
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorSetAngleRBDell(BYTE ucCMSel)
{
    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_53_PORT_CMN_MST_UMAX_H);

    // Master Umax
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX_DELL[ucCMSel][_SIX_COLOR_CENTER_DELL]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX_DELL[ucCMSel][_SIX_COLOR_CENTER_DELL]) & 0xFF));

    // Rightwidth Umax
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX_DELL[ucCMSel][_SIX_COLOR_RIGHTWIDTH_DELL]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX_DELL[ucCMSel][_SIX_COLOR_RIGHTWIDTH_DELL]) & 0xFF));

    // Leftwidth Umax
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX_DELL[ucCMSel][_SIX_COLOR_LEFTWIDTH_DELL]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX_DELL[ucCMSel][_SIX_COLOR_LEFTWIDTH_DELL]) & 0xFF));

    // Rightbuffer Umax
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX_DELL[ucCMSel][_SIX_COLOR_RIGHTBUFFER_DELL]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX_DELL[ucCMSel][_SIX_COLOR_RIGHTBUFFER_DELL]) & 0xFF));

    // Leftbuffer Umax
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX_DELL[ucCMSel][_SIX_COLOR_LEFTBUFFER_DELL]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX_DELL[ucCMSel][_SIX_COLOR_LEFTBUFFER_DELL]) & 0xFF));

    // Right Buffer Hue
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE_DELL[ucCMSel][_SIX_COLOR_RIGHTBUFFER_DELL] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE_DELL[ucCMSel][_SIX_COLOR_RIGHTBUFFER_DELL] & 0xFF);

    // Right Width Range
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE_DELL[ucCMSel][_SIX_COLOR_RIGHTWIDTH_DELL] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE_DELL[ucCMSel][_SIX_COLOR_RIGHTWIDTH_DELL] & 0xFF);

    // Master Range
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE_DELL[ucCMSel][_SIX_COLOR_CENTER_DELL] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE_DELL[ucCMSel][_SIX_COLOR_CENTER_DELL] & 0xFF);

    // Left Width Range
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE_DELL[ucCMSel][_SIX_COLOR_LEFTWIDTH_DELL] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE_DELL[ucCMSel][_SIX_COLOR_LEFTWIDTH_DELL] & 0xFF);

    // Left Buffer Range
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE_DELL[ucCMSel][_SIX_COLOR_LEFTBUFFER_DELL] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE_DELL[ucCMSel][_SIX_COLOR_LEFTBUFFER_DELL] & 0xFF);

    // Set Master/Rightwidth/Leftwidth/Rightbuffer/Leftbuffer LSB to 0
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_83_PORT_CMN_MST_WID_UMAX_L);
    ScalerSetByte(P7_D3_ICM_DATA, 0x00);
    ScalerSetByte(P7_D3_ICM_DATA, 0x00);

    // Set Right Buffer Hue/Right Width Range/Master Range/Left Width Range/Left Buffer Range LSB to 0
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_85_PORT_CMN_HUE_SET1_L);
    ScalerSetByte(P7_D3_ICM_DATA, 0x00);
    ScalerSetByte(P7_D3_ICM_DATA, 0x00);
}

//--------------------------------------------------
// Description  : Enable ICM function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorInitialDell(void)
{
    BYTE ucCmIndex = 0;

    // Enable ICM
    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT4 | _BIT3), _BIT4 | _BIT3);

    // Enable New ICM mode
    ScalerSetBit(P7_D4_ICM_SEL2, ~(_BIT2 | _BIT1), _BIT2 | _BIT1);

    // Enable ICM function
    ScalerSetByte(P7_D0_ICM_CONTROL, (_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Close SCM
    ScalerSetByte(P7_CC_SCM_BLOCK_ENABLE, 0x00);
    ScalerSetBit(P7_CD_SCM_BLOCK_SELECT, ~_BIT4, 0x00);

    // Close ICM Brightness
    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0xBF);
    ScalerSetByte(P7_D3_ICM_DATA, 0x0E);

    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x01);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0xBF);
    ScalerSetByte(P7_D3_ICM_DATA, 0x0E);

    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x02);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0xBF);
    ScalerSetByte(P7_D3_ICM_DATA, 0x0E);

    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x03);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0xBF);
    ScalerSetByte(P7_D3_ICM_DATA, 0x0E);

    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x04);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0xBF);
    ScalerSetByte(P7_D3_ICM_DATA, 0x0E);

    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x05);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0xBF);
    ScalerSetByte(P7_D3_ICM_DATA, 0x0E);

    for(ucCmIndex = 0; ucCmIndex < 6; ucCmIndex++)
    {
        ScalerColorSixColorSetAngleRBDell(ucCmIndex);
    }
}
