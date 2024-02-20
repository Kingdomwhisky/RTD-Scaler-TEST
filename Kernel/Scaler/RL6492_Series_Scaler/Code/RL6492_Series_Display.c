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
// ID Code      : RL6492_Series_Display.c No.0000
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
#if(_PANEL_STYLE == _PANEL_LVDS)

void ScalerDisplayLvdsInitialTable(void);
void ScalerDisplayVcmControl(BYTE ucType);
void ScalerDisplayLvdsPower(bit bOn);
void ScalerDisplayLvdsClkInfoSelect(void);
void ScalerDisplayLvdsDrivingControl(BYTE ucDriv);
void ScalerDisplayLvdsPhaseConrol(void);
void ScalerDisplayLvdsSlewRateConrol(void);

void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand);

bit ScalerDisplayGetLvdsPowerStatus(void);
void ScalerDisplayLvdsPLL(bit bOn);
void ScalerDisplayLvdsPadPower(bit bOn);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

#if(_PANEL_STYLE == _PANEL_DPTX)
void ScalerDisplayUseLvdsPadPower(bit bOn);
#endif // #if(_PANEL_STYLE == _PANEL_DPTX)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Description  : Initial Settings for Display Interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsInitialTable(void)
{
    // Set DISP mode is LVDS
    ScalerSetBit(P39_00_LVDS_DISP_TYPE, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // Set Panel Display Type
    ScalerSetBit(P39_01_LVDS_DISPLAY_CONV_CTRL0, ~(_BIT7 | _BIT6 | _BIT0), ((_LVDS_OUTPUT_PORT << 6) | (_LVDS_TABLE_TYPE << 0)));

    // Display Resolution Control Settings
    ScalerSetBit(P39_01_LVDS_DISPLAY_CONV_CTRL0, ~_BIT1, ((_PANEL_DISP_BIT_MODE & 0x1) << 1));

    // Set LVDS Interface Type
    ScalerSetByte(P39_06_LVDS_DISPLAY_CONV_CTRL5, ((_LVDS_RB_SWAP << 7) | (_LVDS_ML_SWAP << 6) | (_LVDS_PN_SWAP << 4) | (_BIT3) | (_LVDS_CLK_CHANNEL_SEL << 1) | (_LVDS_PAIR_MIRROR << 0)));

    // Set LVDS Display Content
    ScalerSetBit(P39_07_LVDS_DISPLAY_CONV_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_DVS_INVERT << 3) | (_LVDS_DHS_INVERT << 2) | (_LVDS_DEN_INVERT << 1) | (_BIT0)));

    // Set LVDS BW Parameter
    ScalerSetByte(P55_0D_LVDS_COMMON_AB_CTRL13, 0xAB);

    // Set LVDS common mode Voltage
    ScalerDisplayVcmControl(_LVDS_VCM_CONTROL);

    // Set LVDS Driving Double Current Disable
    ScalerSetBit(P55_20_LVDS_PORTA_CTRL0, ~(_BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set LVDS Output Termination Seletcion
    ScalerDisplayLvdsClkInfoSelect();

    // Set LVDS Driving Control
    ScalerDisplayLvdsDrivingControl(_LVDS_DRIV_CONTROL);

    // Set LVDS Phase Selection
    ScalerDisplayLvdsPhaseConrol();

    // Set LVDS data slew rate control
    ScalerDisplayLvdsSlewRateConrol();

    // Set LVDS TX output Data selection: Data / Termination
    ScalerDisplayLvdsTxDataSel();

    // Set LVDS TX Output Data Swap Selection
    ScalerDisplayLvdsTxPortSwap();

    // Disable LVDS CLK Signal, and Set To DC Level
    ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0x00);

    // Set LVDS Shape-adjustment
    ScalerSetBit(P55_23_LVDS_PORTA_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P55_33_LVDS_PORTB_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));

    // Set LVDS Pre-emphasis On
    ScalerSetBit(P55_23_LVDS_PORTA_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(P55_33_LVDS_PORTB_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
}

//--------------------------------------------------
// Description  : Set LVDS driving control
// Input Value  : VCM for Data and Clock pair
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVcmControl(BYTE ucType)
{
    // Set LVDS common mode Voltage
    switch(ucType)
    {
        case _LVDS_VCM_LOW:

            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));

            break;

        case _LVDS_VCM_NORMAL:

            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT3 | _BIT1));

            break;

        case _LVDS_VCM_HIGH:

            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

        case _LVDS_VCM_USER:

            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | (_LVDS_VCM_USER_LEVEL & 0x1F)));

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : LVDS Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPower(bit bOn)
{
    if(bOn == _ON)
    {
        // Enable LVDS Port CD IBGEN Power
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, _BIT7);

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))
        // Set LVDS Port C Configuration: LVDS
        ScalerSetBit(P10_20_PIN_SHARE_CTRL20__OFF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_21_PIN_SHARE_CTRL21__OFF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_22_PIN_SHARE_CTRL22__OFF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_23_PIN_SHARE_CTRL23__OFF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_24_PIN_SHARE_CTRL24__OFF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_25_PIN_SHARE_CTRL25__OFF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_26_PIN_SHARE_CTRL26__OFF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_27_PIN_SHARE_CTRL27__OFF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_28_PIN_SHARE_CTRL28__OFF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_29_PIN_SHARE_CTRL29__OFF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
#endif
    }
    else
    {
        // Disable LVDS Port CD IBGEN Power
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, 0x00);

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))
        // Set LVDS Port C Configuration: HiZ
        ScalerSetBit(P10_20_PIN_SHARE_CTRL20__OFF1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_21_PIN_SHARE_CTRL21__OFF1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_22_PIN_SHARE_CTRL22__OFF1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_23_PIN_SHARE_CTRL23__OFF1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_24_PIN_SHARE_CTRL24__OFF1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_25_PIN_SHARE_CTRL25__OFF1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_26_PIN_SHARE_CTRL26__OFF1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_27_PIN_SHARE_CTRL27__OFF1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_28_PIN_SHARE_CTRL28__OFF1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_29_PIN_SHARE_CTRL29__OFF1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : Set Dual Port LVDS Clk Infomation: CLK set 80ohm as Termination On / CLK set current 2x as Termination Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsClkInfoSelect(void)
{
    // Set LVDS Output Termination 50ohm Initially
    ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0xFF);
    ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0xFF);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)
#if((_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))
    ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetByte(P55_62_DPTX_Z0_TX_2, 0x88);
    ScalerSetByte(P55_63_DPTX_Z0_TX_3, 0x88);
#endif // End of #if((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))
#endif // End of #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // LVDS CLK(1 push 2): CLK set 80ohm as Termination on, CLK set current 2x as Termination Off
#if(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)
#if(_LVDS_PAIR_MIRROR == _DISABLE)
#if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)

    // Set LVDS TXDC Output Termination 80ohm
    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), 0x00);

    // Set LVDS TXDC Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT3, _BIT3);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_1)

    // Set LVDS TXD1 Output Termination 80ohm
    ScalerSetBit(P55_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), 0x00);

    // Set LVDS TXD1 Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT1, _BIT1);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_2)

    // Set LVDS TXD2 Output Termination 80ohm
    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), 0x00);

    // Set LVDS TXD2 Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT2, _BIT2);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_3)

    // Set LVDS TXDC Output Termination 80ohm
    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), 0x00);

    // Set LVDS TXDC Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT3, _BIT3);

#endif // End of #if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)

#else // Else of #if(_LVDS_PAIR_MIRROR == _DISABLE)
#if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)

    // Set LVDS TXD1 Output Termination 80ohm
    ScalerSetBit(P55_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), 0x00);

    // Set LVDS TXD1 Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT1, _BIT1);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_1)

    // Set LVDS TXDC Output Termination 80ohm
    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), 0x00);

    // Set LVDS TXDC Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT3, _BIT3);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_2)

    // Set LVDS TXD2 Output Termination 80ohm
    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), 0x00);

    // Set LVDS TXD2 Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT2, _BIT2);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_3)

    // Set LVDS TXD1 Output Termination 80ohm
    ScalerSetBit(P55_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), 0x00);

    // Set LVDS TXD1 Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT1, _BIT1);

#endif // End of #if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)
#endif // End of #if(_LVDS_PAIR_MIRROR == _DISABLE)

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Disable LVDS TXD Current 2x
    ScalerSetByte(P55_30_LVDS_PORTB_CTRL0, 0x00);

#endif // End of #if(_LVDS_TERMINATION_CONTROL == _DISABLE)
#endif // End of #if(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)
}

//--------------------------------------------------
// Description  : Set LVDS driving control
// Input Value  : Driving current for Data and Clock pair
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsDrivingControl(BYTE ucDriv)
{
    BYTE ucEfuseDriv = 0;
    WORD usTempDriv = 0;

    // load LVDS driving from efuse
    ScalerEfuseGetData(_EFUSE_LVDS_DRIV, 1, &ucEfuseDriv);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

#if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 375 / 350) : 0x78;

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 425 / 350) : 0x88;

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 500 / 350) : 0xA0;

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 575 / 350) : 0xB8;

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            // Set LVDS Output Termination 70ohm
            ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0x55);
            ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0x55);
#if((_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))
            ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
            ScalerSetByte(P55_62_DPTX_Z0_TX_2, 0xAA);
            ScalerSetByte(P55_63_DPTX_Z0_TX_3, 0xAA);
#endif // End of ((_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 275 / 350) : 0x58;

            break;

        default:

            break;
    }

#else // #if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 425 / 350) : 0x88;

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 450 / 350) : 0x90;

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 475 / 350) : 0x98;

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 500 / 350) : 0xA0;

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            // Set LVDS Output Termination 70ohm
            ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0x55);
            ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0x55);
#if((_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))
            ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
            ScalerSetByte(P55_62_DPTX_Z0_TX_2, 0xAA);
            ScalerSetByte(P55_63_DPTX_Z0_TX_3, 0xAA);
#endif // End of ((_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))

            usTempDriv = (ucEfuseDriv != 0) ? ucEfuseDriv : 0x70;

            break;

        default:

            break;
    }
#endif // #if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

#elif(_LVDS_TERMINATION_CONTROL == _DISABLE)

    // Disable Output Termination
    ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0x00);
    ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0x00);
    ScalerSetByte(P55_61_DPTX_Z0_TX_1, 0x00);
    ScalerSetByte(P55_62_DPTX_Z0_TX_2, 0x00);
    ScalerSetByte(P55_63_DPTX_Z0_TX_3, 0x00);

#if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 225 / 350) : 0x48;

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 250 / 350) : 0x50;

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 275 / 350) : 0x58;

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 300 / 350) : 0x60;

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 150 / 350) : 0x30;

            break;

        default:

            break;
    }

#elif(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_1)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 225 / 350) : 0x48;

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 275 / 350) : 0x58;

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 325 / 350) : 0x68;

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            usTempDriv = (ucEfuseDriv != 0) ? ucEfuseDriv : 0x70;

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 200 / 350) : 0x40;

            break;

        default:

            break;
    }

#elif(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_2)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT1 | _BIT0), _BIT1);
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1));
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1));
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1));
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1));

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 250 / 350) : 0x50;

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 300 / 350) : 0x60;

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            usTempDriv = (ucEfuseDriv != 0) ? ucEfuseDriv : 0x70;

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 400 / 350) : 0x80;

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 200 / 350) : 0x48;

            break;

        default:

            break;
    }

#elif(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_3)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 300 / 350) : 0x60;

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            usTempDriv = (ucEfuseDriv != 0) ? ucEfuseDriv : 0x70;

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 375 / 350) : 0x78;

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 400 / 350) : 0x80;

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * 325 / 350) : 0x68;

            break;

        default:

            break;
    }
#endif // #if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

#endif // End of #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    ScalerSetByte(P55_0C_LVDS_COMMON_AB_CTRL12, ((usTempDriv < 0xFF) ? usTempDriv : 0xFF));
}

//--------------------------------------------------
// Description  : LVDS Phase Selection Contorl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPhaseConrol(void)
{
    BYTE ucLvdsPhaseSeedH = 0x03;
    BYTE ucLvdsPhaseSeedL = 0x0F;
    BYTE ucLvdsPhaseH = 0x00;
    BYTE ucLvdsPhaseL = 0x00;

    ScalerSetBit(P55_21_LVDS_PORTA_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(P55_31_LVDS_PORTB_CTRL1, ~_BIT7, _BIT7);

// PI_Phase_CD0 select
#if(_LVDS_PI_PHASE_CD0_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_CD0_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_CD0_SEL % 8)) & 0xF0;

    ScalerSetBit(P55_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P55_05_LVDS_COMMON_AB_CTRL5, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P55_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_05_LVDS_COMMON_AB_CTRL5, 0x30);
#endif

// PI_Phase_CD1 select
#if(_LVDS_PI_PHASE_CD1_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_CD1_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_CD1_SEL % 8)) & 0xF0;

    ScalerSetBit(P55_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P55_07_LVDS_COMMON_AB_CTRL7, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P55_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_07_LVDS_COMMON_AB_CTRL7, 0x30);
#endif

// PI_Phase_CD2 select
#if(_LVDS_PI_PHASE_CD2_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_CD2_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_CD2_SEL % 8)) & 0xF0;

    ScalerSetBit(P55_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P55_09_LVDS_COMMON_AB_CTRL9, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P55_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_09_LVDS_COMMON_AB_CTRL9, 0x30);
#endif

// PI_Phase_CD3 select
#if(_LVDS_PI_PHASE_CD3_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_CD3_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_CD3_SEL % 8)) & 0xF0;

    ScalerSetBit(P55_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P55_0B_LVDS_COMMON_AB_CTRL11, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P55_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_0B_LVDS_COMMON_AB_CTRL11, 0x30);
#endif

    // Set Port C Phase selection (Analog Port B)
    ScalerSetBit(P55_34_LVDS_PORTB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_C0_PHASE << 2) | (_LVDS_C1_PHASE << 0)));
    ScalerSetByte(P55_35_LVDS_PORTB_CTRL5, ((_LVDS_C2_PHASE << 6) | (_LVDS_CC_PHASE << 4) | (_LVDS_C3_PHASE << 2) | (_LVDS_C4_PHASE << 0)));

    // Set Port D Phase selection (Analog Port A)
    ScalerSetBit(P55_24_LVDS_PORTA_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_D0_PHASE << 2) | (_LVDS_D1_PHASE << 0)));
    ScalerSetByte(P55_25_LVDS_PORTA_CTRL5, ((_LVDS_D2_PHASE << 6) | (_LVDS_DC_PHASE << 4) | (_LVDS_D3_PHASE << 2) | (_LVDS_D4_PHASE << 0)));

    // Set LVDS PI Control Enable
    ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~(_BIT1 | _BIT0), _BIT0);
}

//--------------------------------------------------
// Description  : LVDS Slew rate Contorl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSlewRateConrol(void)
{
    ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6), (_LVDS_SR_CONTROL << 6));
    ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6), (_LVDS_SR_CONTROL << 6));
}

//--------------------------------------------------
// Description  : Set LVDS PI Operation band
// Input Value  : ucPhaseBand
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand)
{
    ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_04_LVDS_COMMON_AB_CTRL4, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_06_LVDS_COMMON_AB_CTRL6, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_08_LVDS_COMMON_AB_CTRL8, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT6 | _BIT5), ucPhaseBand);
}

//--------------------------------------------------
// Description  : Get LVDS Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerDisplayGetLvdsPowerStatus(void)
{
    return (bit)(ScalerGetBit(P55_00_LVDS_COMMON_AB_CTRL0, _BIT3));
}

//--------------------------------------------------
// Description  : LVDS PLL(Data) Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPLL(bit bOn)
{
    if(bOn == _ON)
    {
        // Power Up LVDS Port CD PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

        // Wait for LVDS PLL stable
        ScalerTimerDelayXms(2);

        // Set LVDS CLK Signal
        ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0xE3);
    }
    else
    {
        // Power Down LVDS Port CD PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

        // Disable LVDS CLK Signal, and Set To DC Level
        ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0x00);
    }
}

//--------------------------------------------------
// Description  : LVDS Pad Power Control --> LVDS, TTL, GPIO
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPadPower(bit bOn)
{
#if(_LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
    // Weakly/Strongly Pull Down Controlled By User
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), ((_LVDS_PORTA_WEAKLY_PULL_DOWN_USER_CONTROL << 7) | (_LVDS_PORTA_STRONGLY_PULL_DOWN_USER_CONTROL << 6)));
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), ((_LVDS_PORTB_WEAKLY_PULL_DOWN_USER_CONTROL << 7) | (_LVDS_PORTB_STRONGLY_PULL_DOWN_USER_CONTROL << 6)));

#else
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_C)
    // Enable Weakly Pull Down, Disable Strongly Pull Down
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), _BIT7);
#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)
    // Enable Weakly Pull Down, Disable Strongly Pull Down
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);
#else
    // Enable Weakly Pull Down, Disable Strongly Pull Down
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), _BIT7);
#endif
#endif

    if(bOn == _ON)
    {
        // Set LVDS Configuration: Hiz
        ScalerDisplayLvdsPower(_OFF);

        // Power Up Port CD LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
    }
    else
    {
        // Power Down Port CD LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), 0x00);
    }
}
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

#if(_PANEL_STYLE == _PANEL_DPTX)
//--------------------------------------------------
// Description  : LVDS Pad Power Control --> eDP Panel
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayUseLvdsPadPower(bit bOn)
{
    // Disable Weakly / Strongly Pull Down
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

    if(bOn == _ON)
    {
        // Power Up Port CD LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
    }
    else
    {
        // Power Down Port CD LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), 0x00);
    }
}
#endif

