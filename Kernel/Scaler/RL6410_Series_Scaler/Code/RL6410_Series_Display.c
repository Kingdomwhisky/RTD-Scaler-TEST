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
// ID Code      : RL6410_Series_Display.c No.0000
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
void ScalerDisplayLvdsDrivingControl(BYTE ucDriv);
void ScalerDisplayLvdsPhaseConrol(void);
void ScalerDisplayLvdsSlewRateConrol(void);
void ScalerDisplayLvdsPadInitialPullDown(void);

void ScalerDisplayLvdsSetVcoBand(BYTE ucVcoBand);
void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand);
bit ScalerDisplayGetLvdsPowerStatus(void);
void ScalerDisplayLvdsPLL(bit bOn);
#endif

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

    // Set LVDS Driving Control
    ScalerDisplayLvdsDrivingControl(_LVDS_DRIV_CONTROL);

    // Set LVDS Phase Selection
    ScalerDisplayLvdsPhaseConrol();

    // Set LVDS data slew rate control
    ScalerDisplayLvdsSlewRateConrol();

    // Set LVDS TX output Data selection: Data / Termination
    ScalerDisplayLvdsTxDataSel();

    // LVDS Pad Strongly pull down
    ScalerDisplayLvdsPadInitialPullDown();

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
// Description  : LVDS Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPower(bit bOn)
{
    if(bOn == _ON)
    {
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)

        // Disable Port AB Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port A LVDS Block (Analog Port B)
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)

        // Disable Port AB Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port B LVDS Block (Analog Port A)
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_C)

        // Disable Port CD Weakly and Strongly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port C LVDS Block (Analog Port B)
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)

        // Disable Port CD Weakly and Strongly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port D LVDS Block (Analog Port A)
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Disable Port AB Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

        // Disable Port CD Weakly and Strongly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port CD LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Disable Port ABCD Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port ABCD LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

#endif // #if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
    }
    else
    {
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)

        // Enable Port A Weakly and Strongly Pull Down (Analog Port B)
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Power Down Port A LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT5), 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)

        // Enable Port B Weakly and Strongly Pull Down (Analog Port A)
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Power Down Port B LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6), 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_C)

        // Enable Port C Weakly and Strongly Pull Down (Analog Port B)
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Power Down Port C LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT5), 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)

        // Enable Port D Weakly and Strongly Pull Down (Analog Port A)
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Power Down Port D LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6), 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Enable Port AB Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Power Down Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

        // Enable Port CD Weakly and Strongly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Power Down Port CD LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Enable Port ABCD Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Power Down Port ABCD LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

#endif  // #if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
    }
}

//--------------------------------------------------
// Description  : Set LVDS driving control
// Input Value  : Driving current for Data and Clock pair
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsDrivingControl(BYTE ucDriv)
{
#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Output Termination 50ohm
    ScalerSetByte(P15_27_LVDS_PORTA_CTRL7, 0xFF);
    ScalerSetByte(P15_28_LVDS_PORTA_CTRL8, 0xFF);
    ScalerSetByte(P15_37_LVDS_PORTB_CTRL7, 0xFF);
    ScalerSetByte(P15_38_LVDS_PORTB_CTRL8, 0xFF);
    ScalerSetByte(P55_27_LVDS_PORTA_CTRL7, 0xFF);
    ScalerSetByte(P55_28_LVDS_PORTA_CTRL8, 0xFF);
    ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0xFF);
    ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0xFF);

#if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

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
            ScalerSetByte(P55_27_LVDS_PORTA_CTRL7, 0x55);
            ScalerSetByte(P55_28_LVDS_PORTA_CTRL8, 0x55);
            ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0x55);
            ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0x55);

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

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
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

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
    ScalerSetByte(P55_27_LVDS_PORTA_CTRL7, 0x00);
    ScalerSetByte(P55_28_LVDS_PORTA_CTRL8, 0x00);
    ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0x00);
    ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0x00);

#if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

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
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

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
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));

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
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

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

//--------------------------------------------------
// Description  : LVDS Pad Initial Pull Down
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPadInitialPullDown(void)
{
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)

    // Set LVDS Port A Strongly Pull Down Initially
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)

    // Set LVDS Port B Strongly Pull Down Initially
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_C)

    // Set LVDS Port C Strongly Pull Down Initially
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)

    // Set LVDS Port D Strongly Pull Down Initially
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

    // Set LVDS Port AB Strongly Pull Down Initially
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

    // Set LVDS Port CD Strongly Pull Down Initially
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

    // Set LVDS Port ABCD Strongly Pull Down Initially
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#endif // #if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
}

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

//--------------------------------------------------
// Description  : Get LVDS Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerDisplayGetLvdsPowerStatus(void)
{
    return (bit)((ScalerGetBit(P15_00_LVDS_COMMON_AB_CTRL0, _BIT3)) |
                 (ScalerGetBit(P55_00_LVDS_COMMON_AB_CTRL0, _BIT3)));
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
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

