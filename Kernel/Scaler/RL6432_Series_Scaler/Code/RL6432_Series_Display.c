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
// ID Code      : RL6432_Series_Display.c No.0000
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
void ScalerDisplayLvdsPadPower(bit bOn);
void ScalerDisplayLvdsPower(bit bOn);
void ScalerDisplayLvdsClkInfoSelect(void);
void ScalerDisplayLvdsDrivingControl(BYTE ucDriv);
void ScalerDisplayLvdsPhaseConrol(void);
void ScalerDisplayLvdsSlewRateConrol(void);

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
void ScalerDisplayLvdsSetVcoBand(BYTE ucVcoBand);
void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand);
#endif

bit ScalerDisplayGetLvdsPowerStatus(void);
void ScalerDisplayLvdsPLL(bit bOn);

#elif(_PANEL_STYLE == _PANEL_DPTX)
void ScalerDisplayUseLvdsPadPower(bit bOn);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

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
    ScalerSetBit(P39_01_LVDS_DISPLAY_CONV_CTRL0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), ((_LVDS_OUTPUT_PORT << 6) | (_LVDS_PANEL_SECTION << 4) | (_LVDS_TABLE_TYPE << 0)));

    // Display Resolution Control Settings
    ScalerSetBit(P39_01_LVDS_DISPLAY_CONV_CTRL0, ~(_BIT2 | _BIT1), (_PANEL_DISP_BIT_MODE << 1));

    // Dispaly Panel Resoultion
    ScalerSetBit(P39_01_LVDS_DISPLAY_CONV_CTRL0, ~_BIT3, ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT) ? _BIT3 : 0x00));

    // Set LVDS Interface Type
    ScalerSetByte(P39_06_LVDS_DISPLAY_CONV_CTRL5, ((_LVDS_RB_SWAP << 7) | (_LVDS_ML_SWAP << 6) | (_LVDS_PN_SWAP << 4) | (_BIT3) | (_LVDS_CLK_CHANNEL_SEL << 1) | (_LVDS_PAIR_MIRROR << 0)));

    // Set LVDS Display Content
    ScalerSetBit(P39_07_LVDS_DISPLAY_CONV_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_DVS_INVERT << 3) | (_LVDS_DHS_INVERT << 2) | (_LVDS_DEN_INVERT << 1) | (_BIT0)));

    // Set OCLK: Non-inverted
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_20_DISPLAY_CLOCK_FINE_TUNE, ~_BIT0, 0x00);

    // Set LVDS BW Parameter
    ScalerSetByte(P15_0D_LVDS_COMMON_AB_CTRL13, 0xAB);
    ScalerSetByte(P55_0D_LVDS_COMMON_AB_CTRL13, 0xAB);

    // Set LVDS common mode Voltage
    ScalerDisplayVcmControl(_LVDS_VCM_CONTROL);

    // Set LVDS Driving Double Current Disable
    ScalerSetBit(P15_20_LVDS_PORTA_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_20_LVDS_PORTA_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

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
    ScalerSetBit(P15_23_LVDS_PORTA_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P15_33_LVDS_PORTB_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P55_23_LVDS_PORTA_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P55_33_LVDS_PORTB_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));

    // Set LVDS Pre-emphasis On
    ScalerSetBit(P15_23_LVDS_PORTA_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(P15_33_LVDS_PORTB_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
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

            ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));
            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));

            break;

        case _LVDS_VCM_NORMAL:

            ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT3 | _BIT1));
            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT3 | _BIT1));

            break;

        case _LVDS_VCM_HIGH:

            ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

        case _LVDS_VCM_USER:

            ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | (_LVDS_VCM_USER_LEVEL & 0x1F)));
            ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | (_LVDS_VCM_USER_LEVEL & 0x1F)));

            break;

        default:

            break;
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
    // Weakly/ Strongly Pull Down Controlled By User
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), ((_LVDS_PORTA_WEAKLY_PULL_DOWN_USER_CONTROL << 7) | (_LVDS_PORTA_STRONGLY_PULL_DOWN_USER_CONTROL << 6)));
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), ((_LVDS_PORTB_WEAKLY_PULL_DOWN_USER_CONTROL << 7) | (_LVDS_PORTB_STRONGLY_PULL_DOWN_USER_CONTROL << 6)));
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), ((_LVDS_PORTC_WEAKLY_PULL_DOWN_USER_CONTROL << 7) | (_LVDS_PORTC_STRONGLY_PULL_DOWN_USER_CONTROL << 6)));
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), ((_LVDS_PORTD_WEAKLY_PULL_DOWN_USER_CONTROL << 7) | (_LVDS_PORTD_STRONGLY_PULL_DOWN_USER_CONTROL << 6)));
#endif

    if(bOn == _ON)
    {
        // Set LVDS Configuration: Hiz
        ScalerDisplayLvdsPower(_OFF);

        // Power Up Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Power Up Port C LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT5), (_BIT5));
#endif

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Power Up Port D LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6), (_BIT6));
#endif
    }
    else
    {
        // Power Down Port ABCD LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), 0x00);
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), 0x00);
    }
}

//--------------------------------------------------
// Description  : LVDS Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPower(bit bOn)
{
    bit bTxaPulDw = _DISABLE;
    bit bTxbPulDw = _DISABLE;
    bit bTxcPulDw = _DISABLE;
    bit bTxdPulDw = _DISABLE;

    bTxaPulDw = (((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)) ? _ENABLE : _DISABLE);
    bTxbPulDw = (((_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)) ? _ENABLE : _DISABLE);
    bTxcPulDw = (((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)) ? _ENABLE : _DISABLE);
    bTxdPulDw = (((_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)) ? _ENABLE : _DISABLE);

    if(bOn == _ON)
    {
#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Enable LVDS Port AB IBGEN Power
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, _BIT7);
#endif

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Enable LVDS Port CD IBGEN Power
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, _BIT7);
#endif

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Set LVDS Port B Configuration: LVDS
        ScalerSetBit(P10_45_PIN_SHARE_CTRLA5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_46_PIN_SHARE_CTRLA6, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_47_PIN_SHARE_CTRLA7, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_48_PIN_SHARE_CTRLB0, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_49_PIN_SHARE_CTRLB1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_4A_PIN_SHARE_CTRLB2, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_4B_PIN_SHARE_CTRLB3, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_4C_PIN_SHARE_CTRLB4, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_4D_PIN_SHARE_CTRLB5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_4E_PIN_SHARE_CTRLB6, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
#endif

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Set LVDS Port A Configuration: LVDS
        ScalerSetBit(P10_4F_PIN_SHARE_CTRLB7, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_50_PIN_SHARE_CTRLC0, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_51_PIN_SHARE_CTRLC1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_52_PIN_SHARE_CTRLC2, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_53_PIN_SHARE_CTRLC3, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_54_PIN_SHARE_CTRLC4, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_55_PIN_SHARE_CTRLC5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_56_PIN_SHARE_CTRLC6, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_57_PIN_SHARE_CTRLC7, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_58_PIN_SHARE_CTRLD0, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_59_PIN_SHARE_CTRLD1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_5A_PIN_SHARE_CTRLD2, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
#endif

#if(_LVDS_SETTING_CONTROL_BY_USER == _DISABLE)
        // Weakly/ Strongly Pull Down Disabled
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
#endif
    }
    else
    {
#if(_LVDS_SETTING_CONTROL_BY_USER == _DISABLE)
        // Weakly/ Strongly Pull Down Controlled By LVDS Port Select
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (bTxaPulDw == _ENABLE ? (_BIT7 | _BIT6) : 0x00));
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (bTxbPulDw == _ENABLE ? (_BIT7 | _BIT6) : 0x00));
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (bTxcPulDw == _ENABLE ? (_BIT7 | _BIT6) : 0x00));
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (bTxdPulDw == _ENABLE ? (_BIT7 | _BIT6) : 0x00));
#endif

        // Disable LVDS Port ABCD IBGEN Power
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, 0x00);
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, 0x00);

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Set LVDS Port B Configuration: HiZ
        ScalerSetBit(P10_45_PIN_SHARE_CTRLA5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_46_PIN_SHARE_CTRLA6, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_47_PIN_SHARE_CTRLA7, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_48_PIN_SHARE_CTRLB0, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_49_PIN_SHARE_CTRLB1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_4A_PIN_SHARE_CTRLB2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_4B_PIN_SHARE_CTRLB3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_4C_PIN_SHARE_CTRLB4, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_4D_PIN_SHARE_CTRLB5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_4E_PIN_SHARE_CTRLB6, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
        // Set LVDS Port A Configuration: HiZ
        ScalerSetBit(P10_4F_PIN_SHARE_CTRLB7, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_50_PIN_SHARE_CTRLC0, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_51_PIN_SHARE_CTRLC1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_52_PIN_SHARE_CTRLC2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_53_PIN_SHARE_CTRLC3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_54_PIN_SHARE_CTRLC4, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_55_PIN_SHARE_CTRLC5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_56_PIN_SHARE_CTRLC6, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_57_PIN_SHARE_CTRLC7, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_58_PIN_SHARE_CTRLD0, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_59_PIN_SHARE_CTRLD1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_5A_PIN_SHARE_CTRLD2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
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
    ScalerSetByte(P15_27_LVDS_PORTA_CTRL7, 0xFF);
    ScalerSetByte(P15_28_LVDS_PORTA_CTRL8, 0xFF);
    ScalerSetByte(P15_37_LVDS_PORTB_CTRL7, 0xFF);
    ScalerSetByte(P15_38_LVDS_PORTB_CTRL8, 0xFF);
    ScalerSetByte(P55_28_LVDS_PORTA_CTRL8, 0xFF);
    ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0xFF);
    ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0xFF);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_C)
    ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetByte(P55_63_DPTX_Z0_TX_3, 0x88);
#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)
    ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetByte(P55_62_DPTX_Z0_TX_2, 0x88);
#elif((_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
    ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetByte(P55_62_DPTX_Z0_TX_2, 0x88);
    ScalerSetByte(P55_63_DPTX_Z0_TX_3, 0x88);
#endif // End of (_LVDS_PORT_SEL == _LVDS_1_PORT_C)
#endif // End of #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // LVDS CLK(1 push 2): CLK set 80ohm as Termination on, CLK set current 2x as Termination Off
#if((_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))

#if(_LVDS_PORT_SEL != _LVDS_2_PORT_CD)
#if(_LVDS_PAIR_MIRROR == _DISABLE)
#if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)

    // Set LVDS TXBC Output Termination 80ohm
    ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), 0x00);

    // Set LVDS TXBC Current 2x
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT3, _BIT3);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_1)

    // Set LVDS TXB1 Output Termination 80ohm
    ScalerSetBit(P15_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), 0x00);

    // Set LVDS TXB1 Current 2x
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT1, _BIT1);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_2)

    // Set LVDS TXB2 Output Termination 80ohm
    ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), 0x00);

    // Set LVDS TXB2 Current 2x
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT2, _BIT2);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_3)

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // Set LVDS TXB3 Output Termination 80ohm
        ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT3 | _BIT2), 0x00);

        // Set LVDS TXB3 Current 2x
        ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT4, _BIT4);
    }
    else
    {
        // Set LVDS TXBC Output Termination 80ohm
        ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), 0x00);

        // Set LVDS TXBC Current 2x
        ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT3, _BIT3);
    }

#endif // End of #if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)

#else // Else of #if(_LVDS_PAIR_MIRROR == _DISABLE)
#if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // Set LVDS TXB2 Output Termination 80ohm
        ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), 0x00);

        // Set LVDS TXB2 Current 2x
        ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT2, _BIT2);
    }
    else
    {
        // Set LVDS TXB1 Output Termination 80ohm
        ScalerSetBit(P15_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), 0x00);

        // Set LVDS TXB1 Current 2x
        ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT1, _BIT1);
    }

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_1)

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // Set LVDS TXB3 Output Termination 80ohm
        ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT3 | _BIT2), 0x00);

        // Set LVDS TXB3 Current 2x
        ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT4, _BIT4);
    }
    else
    {
        // Set LVDS TXBC Output Termination 80ohm
        ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), 0x00);

        // Set LVDS TXBC Current 2x
        ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT3, _BIT3);
    }

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_2)

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // Set LVDS TXBC Output Termination 80ohm
        ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), 0x00);

        // Set LVDS TXBC Current 2x
        ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT3, _BIT3);
    }
    else
    {
        // Set LVDS TXB2 Output Termination 80ohm
        ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), 0x00);

        // Set LVDS TXB2 Current 2x
        ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT2, _BIT2);
    }

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_3)

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // Set LVDS TXB1 Output Termination 80ohm
        ScalerSetBit(P15_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), 0x00);

        // Set LVDS TXB1 Current 2x
        ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT1, _BIT1);
    }
    else
    {
        // Set LVDS TXB1 Output Termination 80ohm
        ScalerSetBit(P15_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), 0x00);

        // Set LVDS TXB1 Current 2x
        ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT1, _BIT1);
    }

#endif // End of #if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)
#endif // End of #if(_LVDS_PAIR_MIRROR == _DISABLE)

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Disable LVDS TXB Current 2x
    ScalerSetByte(P15_30_LVDS_PORTB_CTRL0, 0x00);

#endif // End of #if(_LVDS_TERMINATION_CONTROL == _DISABLE)
#endif // End of #if(_LVDS_PORT_SEL != _LVDS_2_PORT_CD)

#if(_LVDS_PORT_SEL != _LVDS_2_PORT_AB)
#if(_LVDS_PAIR_MIRROR == _DISABLE)
#if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)

    // Set LVDS TXBC Output Termination 80ohm
    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), 0x00);

    // Set LVDS TXBC Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT3, _BIT3);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_1)

    // Set LVDS TXB1 Output Termination 80ohm
    ScalerSetBit(P55_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), 0x00);

    // Set LVDS TXB1 Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT1, _BIT1);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_2)

    // Set LVDS TXB2 Output Termination 80ohm
    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), 0x00);

    // Set LVDS TXB2 Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT2, _BIT2);

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_3)

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // Set LVDS TXB3 Output Termination 80ohm
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT1, 0x00);
        ScalerSetBit(P55_63_DPTX_Z0_TX_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

        // Set LVDS TXB3 Current 2x
        ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT4, _BIT4);
    }
    else
    {
        // Set LVDS TXBC Output Termination 80ohm
        ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), 0x00);

        // Set LVDS TXBC Current 2x
        ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT3, _BIT3);
    }

#endif // End of #if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)

#else // Else of #if(_LVDS_PAIR_MIRROR == _DISABLE)
#if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // Set LVDS TXB2 Output Termination 80ohm
        ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), 0x00);

        // Set LVDS TXB2 Current 2x
        ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT2, _BIT2);
    }
    else
    {
        // Set LVDS TXB1 Output Termination 80ohm
        ScalerSetBit(P55_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), 0x00);

        // Set LVDS TXB1 Current 2x
        ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT1, _BIT1);
    }

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_1)

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // Set LVDS TXB3 Output Termination 80ohm
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT1, 0x00);
        ScalerSetBit(P55_63_DPTX_Z0_TX_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

        // Set LVDS TXB3 Current 2x
        ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT4, _BIT4);
    }
    else
    {
        // Set LVDS TXBC Output Termination 80ohm
        ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), 0x00);

        // Set LVDS TXBC Current 2x
        ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT3, _BIT3);
    }

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_2)

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // Set LVDS TXBC Output Termination 80ohm
        ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), 0x00);

        // Set LVDS TXBC Current 2x
        ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT3, _BIT3);
    }
    else
    {
        // Set LVDS TXB2 Output Termination 80ohm
        ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), 0x00);

        // Set LVDS TXB2 Current 2x
        ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT2, _BIT2);
    }

#elif(_LVDS_CLK_CHANNEL_SEL == _MODE_3)

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // Set LVDS TXB1 Output Termination 80ohm
        ScalerSetBit(P55_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), 0x00);

        // Set LVDS TXB1 Current 2x
        ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT1, _BIT1);
    }
    else
    {
        // Set LVDS TXB1 Output Termination 80ohm
        ScalerSetBit(P55_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), 0x00);

        // Set LVDS TXB1 Current 2x
        ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT1, _BIT1);
    }

#endif // End of #if(_LVDS_CLK_CHANNEL_SEL == _NORMAL_MODE)
#endif // End of #if(_LVDS_PAIR_MIRROR == _DISABLE)

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Disable LVDS TXB Current 2x
    ScalerSetByte(P55_30_LVDS_PORTB_CTRL0, 0x00);

#endif // End of #if(_LVDS_TERMINATION_CONTROL == _DISABLE)
#endif // End of #if(_LVDS_PORT_SEL != _LVDS_2_PORT_AB)

#endif // End of #if((_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))

#if(_LVDS_SETTING_CONTROL_BY_USER == _ENABLE)

    // Set LVDS TXA Current 2x
    ScalerSetBit(P15_20_LVDS_PORTA_CTRL0, ~_BIT5, (_LVDS_PORTA_DATA4_DRIV_2X_USER_CTRL) << 5);
    ScalerSetBit(P15_20_LVDS_PORTA_CTRL0, ~_BIT4, (_LVDS_PORTA_DATA3_DRIV_2X_USER_CTRL) << 4);
    ScalerSetBit(P15_20_LVDS_PORTA_CTRL0, ~_BIT2, (_LVDS_PORTA_DATA2_DRIV_2X_USER_CTRL) << 2);
    ScalerSetBit(P15_20_LVDS_PORTA_CTRL0, ~_BIT1, (_LVDS_PORTA_DATA1_DRIV_2X_USER_CTRL) << 1);
    ScalerSetBit(P15_20_LVDS_PORTA_CTRL0, ~_BIT0, (_LVDS_PORTA_DATA0_DRIV_2X_USER_CTRL) << 0);

    // Set LVDS TXB Current 2x
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT5, (_LVDS_PORTB_DATA4_DRIV_2X_USER_CTRL) << 5);
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT4, (_LVDS_PORTB_DATA3_DRIV_2X_USER_CTRL) << 4);
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT3, (_LVDS_PORTB_CLK_DRIV_2X_USER_CTRL) << 3);
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT2, (_LVDS_PORTB_DATA2_DRIV_2X_USER_CTRL) << 2);
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT1, (_LVDS_PORTB_DATA1_DRIV_2X_USER_CTRL) << 1);
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~_BIT0, (_LVDS_PORTB_DATA0_DRIV_2X_USER_CTRL) << 0);

    // Set LVDS TXC Current 2x
    ScalerSetBit(P55_20_LVDS_PORTA_CTRL0, ~_BIT5, (_LVDS_PORTC_DATA4_DRIV_2X_USER_CTRL) << 5);
    ScalerSetBit(P55_20_LVDS_PORTA_CTRL0, ~_BIT4, (_LVDS_PORTC_DATA3_DRIV_2X_USER_CTRL) << 4);
    ScalerSetBit(P55_20_LVDS_PORTA_CTRL0, ~_BIT2, (_LVDS_PORTC_DATA2_DRIV_2X_USER_CTRL) << 2);
    ScalerSetBit(P55_20_LVDS_PORTA_CTRL0, ~_BIT1, (_LVDS_PORTC_DATA1_DRIV_2X_USER_CTRL) << 1);
    ScalerSetBit(P55_20_LVDS_PORTA_CTRL0, ~_BIT0, (_LVDS_PORTC_DATA0_DRIV_2X_USER_CTRL) << 0);

    // Set LVDS TXD Current 2x
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT5, (_LVDS_PORTD_DATA4_DRIV_2X_USER_CTRL) << 5);
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT4, (_LVDS_PORTD_DATA3_DRIV_2X_USER_CTRL) << 4);
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT3, (_LVDS_PORTD_CLK_DRIV_2X_USER_CTRL) << 3);
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT2, (_LVDS_PORTD_DATA2_DRIV_2X_USER_CTRL) << 2);
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT1, (_LVDS_PORTD_DATA1_DRIV_2X_USER_CTRL) << 1);
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~_BIT0, (_LVDS_PORTD_DATA0_DRIV_2X_USER_CTRL) << 0);

    // Set LVDS TXA Output Termination
    ScalerSetBit(P15_27_LVDS_PORTA_CTRL7, ~(_BIT3 | _BIT2), (_LVDS_PORTA_DATA0_TERMINATION_USER_ADJUST & 0x03) << 2);
    ScalerSetBit(P15_27_LVDS_PORTA_CTRL7, ~(_BIT1 | _BIT0), (_LVDS_PORTA_DATA1_TERMINATION_USER_ADJUST & 0x03) << 0);

    ScalerSetBit(P15_28_LVDS_PORTA_CTRL8, ~(_BIT7 | _BIT6), (_LVDS_PORTA_DATA2_TERMINATION_USER_ADJUST & 0x03) << 6);
    ScalerSetBit(P15_28_LVDS_PORTA_CTRL8, ~(_BIT3 | _BIT2), (_LVDS_PORTA_DATA3_TERMINATION_USER_ADJUST & 0x03) << 2);
    ScalerSetBit(P15_28_LVDS_PORTA_CTRL8, ~(_BIT1 | _BIT0), (_LVDS_PORTA_DATA4_TERMINATION_USER_ADJUST & 0x03) << 0);

    // Set LVDS TXB Output Termination
    ScalerSetBit(P15_37_LVDS_PORTB_CTRL7, ~(_BIT3 | _BIT2), (_LVDS_PORTB_DATA0_TERMINATION_USER_ADJUST & 0x03) << 2);
    ScalerSetBit(P15_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), (_LVDS_PORTB_DATA1_TERMINATION_USER_ADJUST & 0x03) << 0);
    ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), (_LVDS_PORTB_DATA2_TERMINATION_USER_ADJUST & 0x03) << 6);
    ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), (_LVDS_PORTB_CLK_TERMINATION_USER_ADJUST & 0x03) << 4);
    ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT3 | _BIT2), (_LVDS_PORTB_DATA3_TERMINATION_USER_ADJUST & 0x03) << 2);
    ScalerSetBit(P15_38_LVDS_PORTB_CTRL8, ~(_BIT1 | _BIT0), (_LVDS_PORTB_DATA4_TERMINATION_USER_ADJUST & 0x03) << 0);

    // Set LVDS TXC0 Output Termination
    if(_LVDS_PORTC_DATA0_TERMINATION_USER_ADJUST == 0x00)
    {// 80: 00110 (0)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT3, 0x00);
        ScalerSetBit(P55_62_DPTX_Z0_TX_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    }
    else if(_LVDS_PORTC_DATA0_TERMINATION_USER_ADJUST == 0x01)
    {// 70: 01010 (1)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT3, 0x00);
        ScalerSetBit(P55_62_DPTX_Z0_TX_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));
    }
    else if(_LVDS_PORTC_DATA0_TERMINATION_USER_ADJUST == 0x02)
    {// 60: 10000 (2)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT3, _BIT3);
        ScalerSetBit(P55_62_DPTX_Z0_TX_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
    else
    {// 50: 11000 (3)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT3, _BIT3);
        ScalerSetBit(P55_62_DPTX_Z0_TX_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7));
    }

    // Set LVDS TXC1 Output Termination
    if(_LVDS_PORTC_DATA1_TERMINATION_USER_ADJUST == 0x00)
    {// 80: 00110 (0)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT2, 0x00);
        ScalerSetBit(P55_62_DPTX_Z0_TX_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    }
    else if(_LVDS_PORTC_DATA1_TERMINATION_USER_ADJUST == 0x01)
    {// 70: 01010 (1)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT2, 0x00);
        ScalerSetBit(P55_62_DPTX_Z0_TX_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    }
    else if(_LVDS_PORTC_DATA1_TERMINATION_USER_ADJUST == 0x02)
    {// 60: 10000 (2)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT2, _BIT2);
        ScalerSetBit(P55_62_DPTX_Z0_TX_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {// 50: 11000 (3)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT2, _BIT2);
        ScalerSetBit(P55_62_DPTX_Z0_TX_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));
    }

    // Set LVDS TXC2~TXC4 Output Termination
    ScalerSetBit(P55_28_LVDS_PORTA_CTRL8, ~(_BIT7 | _BIT6), (_LVDS_PORTC_DATA2_TERMINATION_USER_ADJUST & 0x03) << 6);
    ScalerSetBit(P55_28_LVDS_PORTA_CTRL8, ~(_BIT3 | _BIT2), (_LVDS_PORTC_DATA3_TERMINATION_USER_ADJUST & 0x03) << 2);
    ScalerSetBit(P55_28_LVDS_PORTA_CTRL8, ~(_BIT1 | _BIT0), (_LVDS_PORTC_DATA4_TERMINATION_USER_ADJUST & 0x03) << 0);

    // Set LVDS TXD0~TXD2/TXDCLK Output Termination
    ScalerSetBit(P55_37_LVDS_PORTB_CTRL7, ~(_BIT3 | _BIT2), (_LVDS_PORTD_DATA0_TERMINATION_USER_ADJUST & 0x03) << 2);
    ScalerSetBit(P55_37_LVDS_PORTB_CTRL7, ~(_BIT1 | _BIT0), (_LVDS_PORTD_DATA1_TERMINATION_USER_ADJUST & 0x03) << 0);
    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT7 | _BIT6), (_LVDS_PORTD_DATA2_TERMINATION_USER_ADJUST & 0x03) << 6);
    ScalerSetBit(P55_38_LVDS_PORTB_CTRL8, ~(_BIT5 | _BIT4), (_LVDS_PORTD_CLK_TERMINATION_USER_ADJUST & 0x03) << 4);

    // Set LVDS TXD3 Output Termination
    if(_LVDS_PORTD_DATA3_TERMINATION_USER_ADJUST == 0x00)
    {// 80: 00110 (0)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT1, 0x00);
        ScalerSetBit(P55_63_DPTX_Z0_TX_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    }
    else if(_LVDS_PORTD_DATA3_TERMINATION_USER_ADJUST == 0x01)
    {// 70: 01010 (1)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT1, 0x00);
        ScalerSetBit(P55_63_DPTX_Z0_TX_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));
    }
    else if(_LVDS_PORTD_DATA3_TERMINATION_USER_ADJUST == 0x02)
    {// 60: 10000 (2)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT1, _BIT1);
        ScalerSetBit(P55_63_DPTX_Z0_TX_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
    else
    {// 50: 11000 (3)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT1, _BIT1);
        ScalerSetBit(P55_63_DPTX_Z0_TX_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7));
    }

    // Set LVDS TXD4 Output Termination
    if(_LVDS_PORTD_DATA4_TERMINATION_USER_ADJUST == 0x00)
    {// 80: 00110 (0)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT0, 0x00);
        ScalerSetBit(P55_63_DPTX_Z0_TX_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    }
    else if(_LVDS_PORTD_DATA4_TERMINATION_USER_ADJUST == 0x01)
    {// 70: 01010 (1)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT0, 0x00);
        ScalerSetBit(P55_63_DPTX_Z0_TX_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    }
    else if(_LVDS_PORTD_DATA4_TERMINATION_USER_ADJUST == 0x02)
    {// 60: 10000 (2)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT0, _BIT0);
        ScalerSetBit(P55_63_DPTX_Z0_TX_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {// 50: 11000 (3)
        ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~_BIT0, _BIT0);
        ScalerSetBit(P55_63_DPTX_Z0_TX_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));
    }
#endif
}

//--------------------------------------------------
// Description  : Set LVDS driving control
// Input Value  : Driving current for Data and Clock pair
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsDrivingControl(BYTE ucDriv)
{
#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

#if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            // Set LVDS Output Termination 70ohm
            ScalerSetByte(P15_27_LVDS_PORTA_CTRL7, 0x55);
            ScalerSetByte(P15_28_LVDS_PORTA_CTRL8, 0x55);
            ScalerSetByte(P15_37_LVDS_PORTB_CTRL7, 0x55);
            ScalerSetByte(P15_38_LVDS_PORTB_CTRL8, 0x55);

            ScalerSetByte(P55_28_LVDS_PORTA_CTRL8, 0x55);
            ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0x55);
            ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0x55);
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_C)
            ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte(P55_63_DPTX_Z0_TX_3, 0xAA);
#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)
            ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~(_BIT3 | _BIT2), 0x00);
            ScalerSetByte(P55_62_DPTX_Z0_TX_2, 0xAA);
#elif((_LVDS_PORT_SEL == _LVDS_2_PORT_CD) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
            ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
            ScalerSetByte(P55_62_DPTX_Z0_TX_2, 0xAA);
            ScalerSetByte(P55_63_DPTX_Z0_TX_3, 0xAA);
#endif // End of (_LVDS_PORT_SEL == _LVDS_1_PORT_C)

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

            break;

        case _LVDS_DRIV_CONTROL_USER_MODE_1:
            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            break;

        case _LVDS_DRIV_CONTROL_USER_MODE_2:
            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _LVDS_DRIV_CONTROL_USER_MODE_3:
            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            break;

        default:

            break;
    }

#else // #if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_USER_MODE_1:
        case _LVDS_DRIV_CONTROL_USER_MODE_2:
        case _LVDS_DRIV_CONTROL_USER_MODE_3:
        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            break;

        default:

            break;
    }
#endif // #if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

#elif(_LVDS_TERMINATION_CONTROL == _DISABLE)

    // Disable Output Termination
    ScalerSetByte(P15_27_LVDS_PORTA_CTRL7, 0x00);
    ScalerSetByte(P15_28_LVDS_PORTA_CTRL8, 0x00);
    ScalerSetByte(P15_37_LVDS_PORTB_CTRL7, 0x00);
    ScalerSetByte(P15_38_LVDS_PORTB_CTRL8, 0x00);

    ScalerSetByte(P55_28_LVDS_PORTA_CTRL8, 0x00);
    ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0x00);
    ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0x00);
    ScalerSetByte(P55_61_DPTX_Z0_TX_1, 0x00);
    ScalerSetByte(P55_62_DPTX_Z0_TX_2, 0x00);
    ScalerSetByte(P55_63_DPTX_Z0_TX_3, 0x00);

#if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));

            break;

        case _LVDS_DRIV_CONTROL_USER_MODE_1:
        case _LVDS_DRIV_CONTROL_USER_MODE_2:
        case _LVDS_DRIV_CONTROL_USER_MODE_3:
        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        default:

            break;
    }

#elif(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_1)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));

            break;

        case _LVDS_DRIV_CONTROL_USER_MODE_1:
        case _LVDS_DRIV_CONTROL_USER_MODE_2:
        case _LVDS_DRIV_CONTROL_USER_MODE_3:
        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        default:

            break;
    }

#elif(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_2)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1));
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1));
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1));
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1));

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_USER_MODE_1:
        case _LVDS_DRIV_CONTROL_USER_MODE_2:
        case _LVDS_DRIV_CONTROL_USER_MODE_3:
        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        default:

            break;
    }

#elif(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_3)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_USER_MODE_1:
        case _LVDS_DRIV_CONTROL_USER_MODE_2:
        case _LVDS_DRIV_CONTROL_USER_MODE_3:
        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        default:

            break;
    }
#endif // #if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

#endif // End of #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

#if(_LVDS_SETTING_CONTROL_BY_USER == _ENABLE)

    // Set LVDS TXA/ TXB Driving Current
    ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_LVDS_DRIV_CURRENT_USER_ADUST & 0x0F));

    // Set LVDS TXC/ TXD Driving Current
    ScalerSetByte(P55_57_DPTX_SWING_CURRENT_1, 0xAA);
    ScalerSetByte(P55_58_DPTX_SWING_CURRENT_2, 0xAA);
    ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_LVDS_DRIV_CURRENT_USER_ADUST & 0x0F));
#endif
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

    ScalerSetBit(P15_21_LVDS_PORTA_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(P15_31_LVDS_PORTB_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(P55_21_LVDS_PORTA_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(P55_31_LVDS_PORTB_CTRL1, ~_BIT7, _BIT7);

// PI_Phase_AB0 select
#if(_LVDS_PI_PHASE_AB0_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_AB0_SEL >> 2));  // ((_LVDS_PI_PHASE_AB0_SEL - (_LVDS_PI_PHASE_AB0_SEL % 4)) >> 2)
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_AB0_SEL % 8)) & 0xF0;

    ScalerSetBit(P15_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P15_05_LVDS_COMMON_AB_CTRL5, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P15_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P15_05_LVDS_COMMON_AB_CTRL5, 0x30);
#endif

// PI_Phase_AB1 select
#if(_LVDS_PI_PHASE_AB1_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_AB1_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_AB1_SEL % 8)) & 0xF0;

    ScalerSetBit(P15_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P15_07_LVDS_COMMON_AB_CTRL7, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P15_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P15_07_LVDS_COMMON_AB_CTRL7, 0x30);
#endif

// PI_Phase_AB2 select
#if(_LVDS_PI_PHASE_AB2_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_AB2_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_AB2_SEL % 8)) & 0xF0;

    ScalerSetBit(P15_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P15_09_LVDS_COMMON_AB_CTRL9, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P15_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P15_09_LVDS_COMMON_AB_CTRL9, 0x30);
#endif

// PI_Phase_AB3 select
#if(_LVDS_PI_PHASE_AB3_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_AB3_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_AB3_SEL % 8)) & 0xF0;

    ScalerSetBit(P15_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P15_0B_LVDS_COMMON_AB_CTRL11, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P15_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P15_0B_LVDS_COMMON_AB_CTRL11, 0x30);
#endif

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

    // Set Port A Phase selection (Analog Port B)
    ScalerSetBit(P15_34_LVDS_PORTB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_A0_PHASE << 2) | (_LVDS_A1_PHASE << 0)));
    ScalerSetByte(P15_35_LVDS_PORTB_CTRL5, ((_LVDS_A2_PHASE << 6) | (_LVDS_AC_PHASE << 4) | (_LVDS_A3_PHASE << 2) | (_LVDS_A4_PHASE << 0)));

    // Set Port B Phase selection (Analog Port A)
    ScalerSetBit(P15_24_LVDS_PORTA_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_B0_PHASE << 2) | (_LVDS_B1_PHASE << 0)));
    ScalerSetByte(P15_25_LVDS_PORTA_CTRL5, ((_LVDS_B2_PHASE << 6) | (_LVDS_BC_PHASE << 4) | (_LVDS_B3_PHASE << 2) | (_LVDS_B4_PHASE << 0)));

    // Set Port C Phase selection (Analog Port B)
    ScalerSetBit(P55_34_LVDS_PORTB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_C0_PHASE << 2) | (_LVDS_C1_PHASE << 0)));
    ScalerSetByte(P55_35_LVDS_PORTB_CTRL5, ((_LVDS_C2_PHASE << 6) | (_LVDS_CC_PHASE << 4) | (_LVDS_C3_PHASE << 2) | (_LVDS_C4_PHASE << 0)));

    // Set Port D Phase selection (Analog Port A)
    ScalerSetBit(P55_24_LVDS_PORTA_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_D0_PHASE << 2) | (_LVDS_D1_PHASE << 0)));
    ScalerSetByte(P55_25_LVDS_PORTA_CTRL5, ((_LVDS_D2_PHASE << 6) | (_LVDS_DC_PHASE << 4) | (_LVDS_D3_PHASE << 2) | (_LVDS_D4_PHASE << 0)));

    // Set LVDS PI Control Enable, and Set LVDS ckpixel_inv Falling Edge
    ScalerSetBit(P15_03_LVDS_COMMON_AB_CTRL3, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);
}

//--------------------------------------------------
// Description  : LVDS Slew rate Contorl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSlewRateConrol(void)
{
#if(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_0)

    ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#elif(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_1)

    ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));
    ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));

    ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));
    ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));

#elif(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_2)

    ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#elif(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_3)

    ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#endif // #if(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_0)
}

#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB) || (_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD))
//--------------------------------------------------
// Description  : Manual set LVDS VCO band
// Input Value  : ucVcoBand
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSetVcoBand(BYTE ucVcoBand)
{
    ScalerSetBit(P15_0E_LVDS_COMMON_AB_CTRL14, ~(_BIT1 | _BIT0), ucVcoBand);
    ScalerSetBit(P55_0E_LVDS_COMMON_AB_CTRL14, ~(_BIT1 | _BIT0), ucVcoBand);
}

//--------------------------------------------------
// Description  : Set LVDS PI Operation band
// Input Value  : ucPhaseBand
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand)
{
    ScalerSetBit(P15_03_LVDS_COMMON_AB_CTRL3, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P15_04_LVDS_COMMON_AB_CTRL4, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P15_06_LVDS_COMMON_AB_CTRL6, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P15_08_LVDS_COMMON_AB_CTRL8, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P15_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_04_LVDS_COMMON_AB_CTRL4, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_06_LVDS_COMMON_AB_CTRL6, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_08_LVDS_COMMON_AB_CTRL8, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT6 | _BIT5), ucPhaseBand);
}
#endif

//--------------------------------------------------
// Description  : Get LVDS Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerDisplayGetLvdsPowerStatus(void)
{
    return (bit)((ScalerGetBit(P15_00_LVDS_COMMON_AB_CTRL0, _BIT3)) | (ScalerGetBit(P55_00_LVDS_COMMON_AB_CTRL0, _BIT3)));
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
#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB))

        // Power Up LVDS Port AB PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))

        // Power Up LVDS Port CD PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Power Up LVDS Port ABCD PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#endif // #if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB))

        // Wait for LVDS PLL stable
        ScalerTimerDelayXms(2);

        // Set LVDS CLK Signal
        ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0xE3);
    }
    else
    {
#if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB))

        // Power Down LVDS Port AB PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

#elif((_LVDS_PORT_SEL == _LVDS_1_PORT_C) || (_LVDS_PORT_SEL == _LVDS_1_PORT_D) || (_LVDS_PORT_SEL == _LVDS_2_PORT_CD))

        // Power Down LVDS Port CD PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Power Down LVDS Port ABCD PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

#endif // #if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB))

        // Disable LVDS CLK Signal, and Set To DC Level
        ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0x00);
    }
}

#elif(_PANEL_STYLE == _PANEL_DPTX)
//--------------------------------------------------
// Description  : LVDS Pad Power Control --> eDP Panel
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayUseLvdsPadPower(bit bOn)
{
    // Disable Weakly / Strongly Pull Down
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

    if(bOn == _ON)
    {
        // Power Up Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
    }
    else
    {
        // Power Down Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), 0x00);
    }
}
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

