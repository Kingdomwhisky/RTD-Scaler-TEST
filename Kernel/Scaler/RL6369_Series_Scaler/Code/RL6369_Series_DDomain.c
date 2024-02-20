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
// ID Code      : RL6369_Series_DDomain.c No.0000
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

void ScalerDDomainBackgroundEnable(bit bEnable);
void ScalerDDomainBackgroundSetColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Display Force to Background Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // M1 Enable Force to Back Ground
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);
    }
    else
    {
        // M1 Disable Force to Back Ground
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set Display Background Color
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundSetColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{
    // M1 Reset Port index
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, 0x00);
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, _BIT5);

    // 8bits RGB color
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, ucRed);
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, ucGreen);
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, ucBlue);

    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, 0x00);
}

