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
// ID Code      : RL6432_Series_SDRAM.c No.0000
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
#if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
void ScalerSdramPowerEnable(bit bOn);
void ScalerSdramPinshareInitial(void);
void ScalerSdramMpllPowerDown(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
//--------------------------------------------------
// Description  : Sdram ScalerSdramPowerMode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramPowerEnable(bit bOn)
{
    if(bOn == _ON)
    {
        // Config for SDRAM mode
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT0, 0x00);

        // Enable OP power
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT1, 0x00);

        // DDR Vref select internal
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT4, 0x00);

        // Enable DQ low different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT2, 0x00);

        // Enable DQ high different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT3, 0x00);

        // Enable Pad power on
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT5, _BIT5);

        // Disable Second OP power
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT1, _BIT1);

        // Disable Sdram CKE force low into Power down mode
        ScalerSetBit(P4_A6_SDR_SLEW_RATE, ~_BIT1, 0x00);

        // Precharge power down mode select
        ScalerSetBit(P4_B7_SDR_POWER_CTRL0, ~(_BIT5 | _BIT4), 0x00);

        // Delay Time us [5,x] Waiting for DDR setting
        DELAY_5US();

        // Inactive power down
        ScalerSetBit(P4_B7_SDR_POWER_CTRL0, ~_BIT7, 0x00);
    }
    else
    {
        // Enable OP power
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT1, 0x00);

        // DDR Vref select internal
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT4, 0x00);

        // Enable DQ low different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT2, 0x00);

        // Enable DQ high different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT3, 0x00);

        // Enable Pad power on
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT5, _BIT5);

        // Enable Second OP power
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT1, 0x00);

        // DDR Second Vref select internal
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT4, 0x00);

        // Enable Second DQ low different amplifier
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT2, 0x00);

        // Enable Second DQ high different amplifier
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT3, 0x00);

        // Enable Second Pad power on
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT5, _BIT5);

        // Enable Deep power down
        ScalerSetBit(P4_B7_SDR_POWER_CTRL0, ~(_BIT5 | _BIT4), _BIT5);

        // Delay Time us [5,x] Waiting for DDR setting
        DELAY_5US();

        // Active power down
        ScalerSetBit(P4_B7_SDR_POWER_CTRL0, ~_BIT7, _BIT7);

        // Enable Sdram CKE force low into Power down mode
        ScalerSetBit(P4_A6_SDR_SLEW_RATE, ~_BIT1, _BIT1);

        // Disable DQ low different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT2, _BIT2);

        // Disable DQ high different amplifier
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT3, _BIT3);

        // DDR Vref select external
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT4, _BIT4);

        // Disable Pad power off
        ScalerSetBit(P4_00_SDDR_CTRL, ~_BIT5, 0x00);

        // Disable Second DQ low different amplifier
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT2, _BIT2);

        // Disable Second DQ high different amplifier
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT3, _BIT3);

        // DDR Second Vref select external
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT4, _BIT4);

        // Disable Second Pad power off
        ScalerSetBit(P4_10_SDDR_CTRL, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  : Sdram Pinshare Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramPinshareInitial(void)
{
    ScalerSetByte(P4_01_SDDR_CLK_CTRL0, 0x80);
    ScalerSetByte(P4_02_SDDR_CLK_CTRL1, 0xAA);
    ScalerSetByte(P4_03_SDDR_CDAR_CTRL, 0x50);
    ScalerSetByte(P4_04_SDDR_DQSX0_CTRL0, 0x01);
    ScalerSetByte(P4_05_SDDR_DQSX0_CTRL1, 0xAA);
    ScalerSetByte(P4_06_SDDR_DQX0_CTRL0, 0x01);
    ScalerSetByte(P4_07_SDDR_DQX0_CTRL1, 0xAA);
    ScalerSetByte(P4_08_SDDR_DQSX1_CTRL0, 0x01);
    ScalerSetByte(P4_09_SDDR_DQSX1_CTRL1, 0xAA);
    ScalerSetByte(P4_0A_SDDR_DQX1_CTRL0, 0x01);
    ScalerSetByte(P4_0B_SDDR_DQX1_CTRL1, 0xAA);
}

//--------------------------------------------------
// Description  : SDRAM MPLL Power Down
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramMpllPowerDown(void)
{
    // Power off MPLL
    ScalerSetBit(P0_F8_MPLL_WD, ~_BIT0, _BIT0);
}
#endif
