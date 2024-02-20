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
// ID Code      : RL6432_Series_Efuse.c No.0000
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
void ScalerEfuseGetData(EnumEfuseDataState enumEfuseDataState, BYTE ucEfuseLength, BYTE *pucEfuseData);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : M2PLL Power COntrol.
// Input Value  : enumEfuseDataState, pucEfuseData
// Output Value : None
//--------------------------------------------------
void ScalerEfuseGetData(EnumEfuseDataState enumEfuseDataState, BYTE ucEfuseLength, BYTE *pucEfuseData)
{
    WORD usEfuseAddress = 0;

    switch(enumEfuseDataState)
    {
        default:
            return;
    }

    // Enable eFuse Module Clk
    ScalerSetBit(P24_A3_EFUSE_CTRL_0, ~_BIT0, 0x00);

    // Set eFuse Read Start Address
    ScalerSetByte(P24_A1_EFUSE_BURN_IN_1, (usEfuseAddress >> 1));

    // Enable Read eFuse
    ScalerSetBit(P24_A3_EFUSE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // Delay Time us [10,x] for eFuse ready
    DELAY_10US();

    // Load eFuse data
    if((usEfuseAddress % 2) == 0)
    {
        memcpy(pucEfuseData, (volatile BYTE xdata *)P24_A6_EFUSE_DATA0, ucEfuseLength);
    }
    else
    {
        memcpy(pucEfuseData, (volatile BYTE xdata *)P24_A7_EFUSE_DATA1, ucEfuseLength);
    }

    // Disable eFuse Module Clk
    ScalerSetBit(P24_A3_EFUSE_CTRL_0, ~_BIT0, _BIT0);
}

