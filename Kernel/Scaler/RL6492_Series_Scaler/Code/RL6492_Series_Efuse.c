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
// ID Code      : RL6492_Series_Efuse.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _EFUSE_INITIAL_ADDRESS                 (0xA6)

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
    bit bEfuseAddrType = 0;
    BYTE ucEfuseAddress = 0;

    switch(enumEfuseDataState)
    {
        case _EFUSE_LVDS_DRIV:
            bEfuseAddrType = 1;
            ucEfuseAddress = 0xC0;
            break;

        case _EFUSE_TYPE_C_1M_OHM_RESISTOR:
            bEfuseAddrType = 1;
            ucEfuseAddress = 0xBF;
            break;

        case _EFUSE_CP_WAFER_INFO:
            bEfuseAddrType = 1;
            ucEfuseAddress = 0xC1;
            break;

        case _EFUSE_CC_RESISTANCE:
            bEfuseAddrType = 1;
            ucEfuseAddress = 0xA6;
            break;

        case _EFUSE_CC_ATTACH_VOLTAGE:
            bEfuseAddrType = 1;
            ucEfuseAddress = 0xAE;
            break;

        case _EFUSE_CC_BMC_TX_RX_VOLTAGE:
            bEfuseAddrType = 1;
            ucEfuseAddress = 0xB6;
            break;

        case _EFUSE_ADC_SLOP_OFFSET:
            bEfuseAddrType = 1;
            ucEfuseAddress = 0xBA;
            break;

        case _EFUSE_VBUS_COMPARATOR:
            bEfuseAddrType = 1;
            ucEfuseAddress = 0xBD;
            break;

        case _EFUSE_CHECK_BIT:
            bEfuseAddrType = 1;
            ucEfuseAddress = 0xA9;
            break;

        default:
            return;
    }

    // Enable eFuse Module Clk
    ScalerSetBit(P24_A3_EFUSE_CTRL_0, ~_BIT0, 0x00);

    // Set eFuse Address Type
    ScalerSetBit(P24_A2_EFUSE_BURN_IN_2, ~_BIT7, ((BYTE)bEfuseAddrType << 7));

    // Set eFuse Read Start Address
    ScalerSetByte(P24_A1_EFUSE_BURN_IN_1, (ucEfuseAddress - _EFUSE_INITIAL_ADDRESS));

    // Enable Read eFuse
    ScalerSetBit(P24_A3_EFUSE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // Delay Time us [10,x] for eFuse ready
    DELAY_10US();

    // Load eFuse data
    memcpy(pucEfuseData, (volatile BYTE xdata *)P24_A6_EFUSE_DATA0, ucEfuseLength);

    // Initial eFuse Address Type
    ScalerSetBit(P24_A2_EFUSE_BURN_IN_2, ~_BIT7, 0x00);

    // Disable eFuse Module Clk
    ScalerSetBit(P24_A3_EFUSE_CTRL_0, ~_BIT0, _BIT0);
}

