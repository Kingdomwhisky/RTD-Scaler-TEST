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
// ID Code      : RL6369_Series_ColorSixColorInitial.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6369_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
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
SWORD code tSIX_COLOR_DEFAULT_ANGLE[][5] =
{
    {587,  0, 135, 482,  604},
    {1191, 0, 135, 260,  420},
    {1611, 0, 437, 884,  1024},
    {2635, 0, 135, 280,  370},
    {3005, 0, 369, 504,  746},
    {3751, 0, 345, 670,  932}
};

SWORD code tSIX_COLOR_U_MAX[][5] =
{
    {1256, 1256, 1024, 3955, 3560},
    {3560, 3560, 3072, 2856, 2630},
    {2630, 2630, 2048, 2643, 2841},
    {2841, 2841, 3072, 3594, 3885},
    {3885, 3885, 1024, 1256, 1584},
    {1584, 1584, 2047, 1609, 1256},
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerColorSixColorSetAngleRB(BYTE ucCMSel);
void ScalerColorSixColorInitialNormal(void);


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
void ScalerColorSixColorSetAngleRB(BYTE ucCMSel)
{
    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_53_PORT_CMN_MST_UMAX_H);

    // Master Umax
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_CENTER]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_CENTER]) & 0xFF));

    // Rightwidth Umax
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_RIGHTWIDTH]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_RIGHTWIDTH]) & 0xFF));

    // Leftwidth Umax
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_LEFTWIDTH]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_LEFTWIDTH]) & 0xFF));

    // Rightbuffer Umax
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_RIGHTBUFFER]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_RIGHTBUFFER]) & 0xFF));

    // Leftbuffer Umax
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_LEFTBUFFER]) >> 8));
    ScalerSetByte(P7_D3_ICM_DATA, ((tSIX_COLOR_U_MAX[ucCMSel][_SIX_COLOR_LEFTBUFFER]) & 0xFF));

    // Right Buffer Hue
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_RIGHTBUFFER] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_RIGHTBUFFER] & 0xFF);

    // Right Width Range
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_RIGHTWIDTH] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_RIGHTWIDTH] & 0xFF);

    // Master Range
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_CENTER] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_CENTER] & 0xFF);

    // Left Width Range
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_LEFTWIDTH] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_LEFTWIDTH] & 0xFF);

    // Left Buffer Range
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_LEFTBUFFER] >> 8);
    ScalerSetByte(P7_D3_ICM_DATA, tSIX_COLOR_DEFAULT_ANGLE[ucCMSel][_SIX_COLOR_LEFTBUFFER] & 0xFF);
}

//--------------------------------------------------
// Description  : Enable ICM function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorInitialNormal(void)
{
    BYTE ucCmIndex = 0;

    // Enable ICM
    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT4 | _BIT3), _BIT4 | _BIT3);

    // Enable New ICM mode
    ScalerSetBit(P7_D4_ICM_SEL2, ~(_BIT2 | _BIT1), _BIT2 | _BIT1);

    // Enable ICM function
    ScalerSetByte(P7_D0_ICM_CONTROL, (_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Close ICM Brightness
    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0x00);

    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x01);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0x00);

    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x02);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0x00);

    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x03);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0x00);

    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x04);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0x00);

    ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x05);
    ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
    ScalerSetByte(P7_D3_ICM_DATA, 0x00);

    for(ucCmIndex = 0; ucCmIndex < 6; ucCmIndex++)
    {
        ScalerColorSixColorSetAngleRB(ucCmIndex);
    }
}
