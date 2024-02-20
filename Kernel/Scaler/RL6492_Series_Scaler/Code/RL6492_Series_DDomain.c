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
// ID Code      : RL6492_Series_DDomain.c No.0000
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

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
void ScalerDDomainBackgroundSetColor10bit(WORD usRed, WORD usGreen, WORD usBlue);
#endif

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

    // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT, ucRed);
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT, ucGreen);
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT, ucBlue);
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT, 0x00);

    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, 0x00);
}

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Display Background Color (10bit)
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainBackgroundSetColor10bit(WORD usRed, WORD usGreen, WORD usBlue) // 10bit
{
    // M1 Reset Port index
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, 0x00);
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, _BIT5);

    // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT, (usRed >> 2));
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT, (usGreen >> 2));
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT, (usBlue >> 2));
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT, ((usRed & 0x03) << 6) | ((usGreen & 0x03) << 4) | ((usBlue & 0x03) << 2));

    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, 0x00);
}
#endif // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
