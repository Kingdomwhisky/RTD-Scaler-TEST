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
// ID Code      : RL6369_Series_Display.c No.0000
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

void ScalerDisplayLvdsSetVcoBand(BYTE ucVcoBand);
void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand);
bit ScalerDisplayGetLvdsPowerStatus(void);
void ScalerDisplayLvdsPLL(bit bOn);
#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

#if(_PANEL_STYLE == _PANEL_TTL)
void ScalerDisplayTtlInitialTable(void);
void ScalerDisplayTtlPadPower(bit bOn);
void ScalerDisplayTtlPower(bit bOn);
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
    ScalerSetBit(P39_06_LVDS_DISPLAY_CONV_CTRL5, ~0xFF, ((_LVDS_RB_SWAP << 7) | (_LVDS_ML_SWAP << 6) | (_LVDS_PN_SWAP << 4) | (_BIT3) | (_LVDS_CLK_CHANNEL_SEL << 1) | (_LVDS_PAIR_MIRROR << 0)));

    // Set LVDS Display Content
    ScalerSetBit(P39_07_LVDS_DISPLAY_CONV_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_DVS_INVERT << 3) | (_LVDS_DHS_INVERT << 2) | (_LVDS_DEN_INVERT << 1) | (_BIT0)));

    // Set OCLK: Non-inverted
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_20_DISPLAY_CLOCK_FINE_TUNE, ~_BIT0, 0x00);

    // Set LVDS BW Parameter
    ScalerSetByte(P15_0D_LVDS_COMMON_AB_CTRL13, 0xAB);

    // Set LVDS common mode Voltage
    ScalerDisplayVcmControl(_LVDS_VCM_CONTROL);

    // Set LVDS Driving Double Current Disable
    ScalerSetBit(P15_20_LVDS_PORTA_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set LVDS Output Termination Seletcion
    ScalerDisplayLvdsClkInfoSelect();

    // Set LVDS Driving Control
    ScalerDisplayLvdsDrivingControl(_LVDS_DRIV_CONTROL);

    // Set LVDS Phase Selection
    ScalerDisplayLvdsPhaseConrol();

    // Set LVDS data slew rate control
    ScalerDisplayLvdsSlewRateConrol();

    // Set LVDS TX output Data selection: Data / Strongly pull down / Termination
    ScalerDisplayLvdsTxDataSel();

    // Set LVDS TX Output Data Swap Selection
    ScalerDisplayLvdsTxPortSwap();

    // Disable LVDS CLK Signal, and Set To DC Level
    ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0x00);

    // Set LVDS Shape-adjustment
    ScalerSetBit(P15_23_LVDS_PORTA_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P15_33_LVDS_PORTB_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));

    // Set LVDS Pre-emphasis On
    ScalerSetBit(P15_23_LVDS_PORTA_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(P15_33_LVDS_PORTB_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
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

            break;

        case _LVDS_VCM_NORMAL:

            ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT0));

            break;

        case _LVDS_VCM_HIGH:

            ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

        case _LVDS_VCM_USER:

            ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | (_LVDS_VCM_USER_LEVEL & 0x1F)));

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
    // Weakly/Strongly Pull Down Controlled By User
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), ((_LVDS_PORTA_WEAKLY_PULL_DOWN_USER_CONTROL << 7) | (_LVDS_PORTA_STRONGLY_PULL_DOWN_USER_CONTROL << 6)));
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), ((_LVDS_PORTB_WEAKLY_PULL_DOWN_USER_CONTROL << 7) | (_LVDS_PORTB_STRONGLY_PULL_DOWN_USER_CONTROL << 6)));
#else
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
    // Enable Weakly Pull Down, Disable Strong Pull Down
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), _BIT7);
#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)
    // Enable Weakly Pull Down, Disable Strong Pull Down
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);
#else
    // Enable Weakly Pull Down, Disable Strong Pull Down
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), _BIT7);
#endif
#endif

    if(bOn == _ON)
    {
        // Set LVDS Configuration: Hiz
        ScalerDisplayLvdsPower(_OFF);

        // Power Up Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
    }
    else
    {
        // Power Down Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), 0x00);
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
        // Enable LVDS Port AB IBGEN Power
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, _BIT7);

#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)

        // Set LVDS Port A Configuration: LVDS
        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit(P10_27_PIN_SHARE_CTRL67, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        }

        ScalerSetBit(P10_3B_LVDS_TTL_SELECT0, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_3C_LVDS_TTL_SELECT1, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_3D_LVDS_TTL_SELECT2, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_3E_LVDS_TTL_SELECT3, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_3F_LVDS_TTL_SELECT4, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_40_LVDS_TTL_SELECT5, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_41_LVDS_TTL_SELECT6, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_42_LVDS_TTL_SELECT7, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_43_LVDS_TTL_SELECT8, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_44_LVDS_TTL_SELECT9, ~(_BIT1 | _BIT0), _BIT1);

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)

        // Set LVDS Port B Configuration: LVDS
        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            ScalerSetBit(P10_1C_PIN_SHARE_CTRL54, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit(P10_1D_PIN_SHARE_CTRL55, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        }

        ScalerSetBit(P10_1E_PIN_SHARE_CTRL56, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_1F_PIN_SHARE_CTRL57, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_20_PIN_SHARE_CTRL60, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_21_PIN_SHARE_CTRL61, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_22_PIN_SHARE_CTRL62, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_23_PIN_SHARE_CTRL63, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_24_PIN_SHARE_CTRL64, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_25_PIN_SHARE_CTRL65, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Set LVDS Port A Configuration: LVDS
        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit(P10_27_PIN_SHARE_CTRL67, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        }

        ScalerSetBit(P10_3B_LVDS_TTL_SELECT0, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_3C_LVDS_TTL_SELECT1, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_3D_LVDS_TTL_SELECT2, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_3E_LVDS_TTL_SELECT3, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_3F_LVDS_TTL_SELECT4, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_40_LVDS_TTL_SELECT5, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_41_LVDS_TTL_SELECT6, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_42_LVDS_TTL_SELECT7, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_43_LVDS_TTL_SELECT8, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit(P10_44_LVDS_TTL_SELECT9, ~(_BIT1 | _BIT0), _BIT1);

        // Set LVDS Port B Configuration: LVDS
        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            ScalerSetBit(P10_1C_PIN_SHARE_CTRL54, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit(P10_1D_PIN_SHARE_CTRL55, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        }

        ScalerSetBit(P10_1E_PIN_SHARE_CTRL56, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_1F_PIN_SHARE_CTRL57, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_20_PIN_SHARE_CTRL60, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_21_PIN_SHARE_CTRL61, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_22_PIN_SHARE_CTRL62, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_23_PIN_SHARE_CTRL63, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_24_PIN_SHARE_CTRL64, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetBit(P10_25_PIN_SHARE_CTRL65, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

#endif // #if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
    }
    else
    {
        // Disable LVDS Port AB IBGEN Power
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~_BIT7, 0x00);

#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)

        // Set LVDS Port A Configuration: HiZ
        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P10_27_PIN_SHARE_CTRL67, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }

        ScalerSetBit(P10_3B_LVDS_TTL_SELECT0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_3C_LVDS_TTL_SELECT1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_3D_LVDS_TTL_SELECT2, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_3E_LVDS_TTL_SELECT3, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_3F_LVDS_TTL_SELECT4, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_40_LVDS_TTL_SELECT5, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_41_LVDS_TTL_SELECT6, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_42_LVDS_TTL_SELECT7, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_43_LVDS_TTL_SELECT8, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_44_LVDS_TTL_SELECT9, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)

        // Set LVDS Port B Configuration: HiZ
        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            ScalerSetBit(P10_1C_PIN_SHARE_CTRL54, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P10_1D_PIN_SHARE_CTRL55, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }

        ScalerSetBit(P10_1E_PIN_SHARE_CTRL56, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_1F_PIN_SHARE_CTRL57, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_20_PIN_SHARE_CTRL60, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_21_PIN_SHARE_CTRL61, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_22_PIN_SHARE_CTRL62, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_23_PIN_SHARE_CTRL63, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_24_PIN_SHARE_CTRL64, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_25_PIN_SHARE_CTRL65, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Set LVDS Port A Configuration: HiZ
        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P10_27_PIN_SHARE_CTRL67, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }

        ScalerSetBit(P10_3B_LVDS_TTL_SELECT0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_3C_LVDS_TTL_SELECT1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_3D_LVDS_TTL_SELECT2, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_3E_LVDS_TTL_SELECT3, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_3F_LVDS_TTL_SELECT4, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_40_LVDS_TTL_SELECT5, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_41_LVDS_TTL_SELECT6, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_42_LVDS_TTL_SELECT7, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_43_LVDS_TTL_SELECT8, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P10_44_LVDS_TTL_SELECT9, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Set LVDS Port B Configuration: HiZ
        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
        {
            ScalerSetBit(P10_1C_PIN_SHARE_CTRL54, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P10_1D_PIN_SHARE_CTRL55, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }

        ScalerSetBit(P10_1E_PIN_SHARE_CTRL56, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_1F_PIN_SHARE_CTRL57, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_20_PIN_SHARE_CTRL60, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_21_PIN_SHARE_CTRL61, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_22_PIN_SHARE_CTRL62, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_23_PIN_SHARE_CTRL63, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_24_PIN_SHARE_CTRL64, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P10_25_PIN_SHARE_CTRL65, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif  // #if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
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

    // Dual Port LVDS: CLK set 80ohm as Termination on, CLK set current 2x as Termination Off
#if(_LVDS_OUTPUT_PORT == _LVDS_2_PORT)
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
#endif // End of #if(_LVDS_OUTPUT_PORT == _LVDS_2_PORT)

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

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

            break;

        default:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            break;
    }

#elif(_LVDS_TERMINATION_CONTROL == _DISABLE)

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;

        default:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;
    }
#endif // End of #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

#if(_LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
    ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_LVDS_DRIV_CURRENT_USER_ADUST & 0x0F));
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

    // Set Port A Phase selection (Analog Port B)
    ScalerSetBit(P15_34_LVDS_PORTB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_A0_PHASE << 2) | (_LVDS_A1_PHASE << 0)));
    ScalerSetBit(P15_35_LVDS_PORTB_CTRL5, ~0xFF, ((_LVDS_A2_PHASE << 6) | (_LVDS_AC_PHASE << 4) | (_LVDS_A3_PHASE << 2) | (_LVDS_A4_PHASE << 0)));

    // Set Port B Phase selection (Analog Port A)
    ScalerSetBit(P15_24_LVDS_PORTA_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_B0_PHASE << 2) | (_LVDS_B1_PHASE << 0)));
    ScalerSetBit(P15_25_LVDS_PORTA_CTRL5, ~0xFF, ((_LVDS_B2_PHASE << 6) | (_LVDS_BC_PHASE << 4) | (_LVDS_B3_PHASE << 2) | (_LVDS_B4_PHASE << 0)));

    // Set LVDS PI Control Enable, and Set LVDS ckpixel_inv Falling Edge
    ScalerSetBit(P15_03_LVDS_COMMON_AB_CTRL3, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);
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

#elif(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_1)

    ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));
    ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));

#elif(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_2)

    ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#elif(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_3)

    ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#endif // #if(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_0)
}

//--------------------------------------------------
// Description  : Manual set LVDS VCO band
// Input Value  : ucVcoBand
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSetVcoBand(BYTE ucVcoBand)
{
    ScalerSetBit(P15_0E_LVDS_COMMON_AB_CTRL14, ~(_BIT1 | _BIT0), ucVcoBand);
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
}

//--------------------------------------------------
// Description  : Get LVDS Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerDisplayGetLvdsPowerStatus(void)
{
    return (bit)(ScalerGetBit(P15_00_LVDS_COMMON_AB_CTRL0, _BIT3));
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

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_EF)

        // Power Up LVDS Port EF PLL
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_GH)

        // Power Up LVDS Port GH PLL
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Power Up LVDS Port ABCD PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_CDEF)

        // Power Up LVDS Port CDEF PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_EFGH)

        // Power Up LVDS Port EFGH PLL
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_8_PORT_ABCDEFGH)

        // Power Up LVDS Port ABCDEFGH PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

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

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_EF)

        // Power Down LVDS Port EF PLL
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_GH)

        // Power Down LVDS Port GH PLL
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Power Down LVDS Port ABCD PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_CDEF)

        // Power Down LVDS Port CDEF PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_EFGH)

        // Power Down LVDS Port EFGH PLL
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

#elif(_LVDS_PORT_SEL == _LVDS_8_PORT_ABCDEFGH)

        // Power Down LVDS Port ABCDEFGH PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

#endif // #if((_LVDS_PORT_SEL == _LVDS_1_PORT_A) || (_LVDS_PORT_SEL == _LVDS_1_PORT_B) || (_LVDS_PORT_SEL == _LVDS_2_PORT_AB))

        // Disable LVDS CLK Signal, and Set To DC Level
        ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0x00);
    }
}
#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

#if(_PANEL_STYLE == _PANEL_TTL)
//--------------------------------------------------
// Description  : Initial Settings for Display Interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayTtlInitialTable(void)
{
    // Display Type Control Settings
    ScalerSetBit(P39_01_LVDS_DISPLAY_CONV_CTRL0, ~(_BIT2 | _BIT1), (_PANEL_DISP_BIT_MODE << 1));

    // Set TTL Interface Type
    ScalerSetBit(P39_06_LVDS_DISPLAY_CONV_CTRL5, ~0xFF, ((_LVDS_RB_SWAP << 7) | (_LVDS_ML_SWAP << 6) | (_LVDS_PN_SWAP << 4) | (_BIT3) | (_LVDS_CLK_CHANNEL_SEL << 1) | (_LVDS_PAIR_MIRROR << 0)));

    // Set TTL Display Content
    ScalerSetBit(P39_07_LVDS_DISPLAY_CONV_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_DVS_INVERT << 3) | (_LVDS_DHS_INVERT << 2) | (_LVDS_DEN_INVERT << 1) | (_BIT0)));

    // Set OCLK: Non-inverted
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_20_DISPLAY_CLOCK_FINE_TUNE, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : TTL Pad Power Control --> LVDS, TTL, GPIO
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayTtlPadPower(bit bOn)
{
    // Enable Weakly Pull Down, Disable Strong Pull Down
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), _BIT7);

    if(bOn == _ON)
    {
        // Set TTL Configuration: Hiz
        ScalerDisplayTtlPower(_OFF);

        // Power Up Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
    }
    else
    {
        // Power Down Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT6 | _BIT5), 0x00);
    }
}

//--------------------------------------------------
// Description  : LVDS Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayTtlPower(bit bOn)
{
    if(bOn == _ON)
    {
        // Disable Port AB Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Set DEN
        ScalerSetBit(P10_2A_PIN_SHARE_CTRL72, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

        // Set DHS
        ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

        // Set DCLK
        ScalerSetBit(P10_2C_PIN_SHARE_CTRL74, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

        // Set DVS
        ScalerSetBit(P10_2D_PIN_SHARE_CTRL75, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

        // Enable DCLK
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_20_DISPLAY_CLOCK_FINE_TUNE, ~_BIT1, _BIT1);

        // Set DISP mode is TTL
        ScalerSetBit(P39_00_LVDS_DISP_TYPE, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_24_BIT)
        // TTL_R1
        ScalerSetBit(P10_28_PIN_SHARE_CTRL70, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        // TTL_R0
        ScalerSetBit(P10_29_PIN_SHARE_CTRL71, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // TTL_G1
        ScalerSetBit(P10_3D_LVDS_TTL_SELECT2, ~(_BIT1 | _BIT0), 0x00);
        // TTL_G0
        ScalerSetBit(P10_3E_LVDS_TTL_SELECT3, ~(_BIT1 | _BIT0), 0x00);

        // TTL_B1
        ScalerSetBit(P10_22_PIN_SHARE_CTRL62, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        // TTL_B0
        ScalerSetBit(P10_23_PIN_SHARE_CTRL63, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
#endif

        // TTL_R7
        ScalerSetBit(P10_3F_LVDS_TTL_SELECT4, ~(_BIT1 | _BIT0), 0x00);
        // TTL_R6
        ScalerSetBit(P10_40_LVDS_TTL_SELECT5, ~(_BIT1 | _BIT0), 0x00);
        // TTL_R5
        ScalerSetBit(P10_41_LVDS_TTL_SELECT6, ~(_BIT1 | _BIT0), 0x00);
        // TTL_R4
        ScalerSetBit(P10_42_LVDS_TTL_SELECT7, ~(_BIT1 | _BIT0), 0x00);
        // TTL_R3
        ScalerSetBit(P10_43_LVDS_TTL_SELECT8, ~(_BIT1 | _BIT0), 0x00);
        // TTL_R2
        ScalerSetBit(P10_44_LVDS_TTL_SELECT9, ~(_BIT1 | _BIT0), 0x00);

        // TTL_G7
        ScalerSetBit(P10_24_PIN_SHARE_CTRL64, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        // TTL_G6
        ScalerSetBit(P10_25_PIN_SHARE_CTRL65, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        // TTL_G5
        ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        // TTL_G4
        ScalerSetBit(P10_27_PIN_SHARE_CTRL67, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        // TTL_G3
        ScalerSetBit(P10_3B_LVDS_TTL_SELECT0, ~(_BIT1 | _BIT0), 0x00);
        // TTL_G2
        ScalerSetBit(P10_3C_LVDS_TTL_SELECT1, ~(_BIT1 | _BIT0), 0x00);

        // TTL_B7
        ScalerSetBit(P10_1C_PIN_SHARE_CTRL54, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        // TTL_B6
        ScalerSetBit(P10_1D_PIN_SHARE_CTRL55, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        // TTL_B5
        ScalerSetBit(P10_1E_PIN_SHARE_CTRL56, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        // TTL_B4
        ScalerSetBit(P10_1F_PIN_SHARE_CTRL57, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        // TTL_B3
        ScalerSetBit(P10_20_PIN_SHARE_CTRL60, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        // TTL_B2
        ScalerSetBit(P10_21_PIN_SHARE_CTRL61, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    }
    else
    {
#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_24_BIT)
        // TTL_R1: Hiz
        ScalerSetBit(P10_28_PIN_SHARE_CTRL70, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // TTL_R0: Hiz
        ScalerSetBit(P10_29_PIN_SHARE_CTRL71, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // TTL_G1: Hiz
        ScalerSetBit(P10_3D_LVDS_TTL_SELECT2, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        // TTL_G0: Hiz
        ScalerSetBit(P10_3E_LVDS_TTL_SELECT3, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // TTL_B1: Hiz
        ScalerSetBit(P10_22_PIN_SHARE_CTRL62, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // TTL_B0: Hiz
        ScalerSetBit(P10_23_PIN_SHARE_CTRL63, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

        // TTL_R7: Hiz
        ScalerSetBit(P10_3F_LVDS_TTL_SELECT4, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        // TTL_R6: Hiz
        ScalerSetBit(P10_40_LVDS_TTL_SELECT5, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        // TTL_R5: Hiz
        ScalerSetBit(P10_41_LVDS_TTL_SELECT6, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        // TTL_R4: Hiz
        ScalerSetBit(P10_42_LVDS_TTL_SELECT7, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        // TTL_R3: Hiz
        ScalerSetBit(P10_43_LVDS_TTL_SELECT8, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        // TTL_R2: Hiz
        ScalerSetBit(P10_44_LVDS_TTL_SELECT9, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // TTL_G7: Hiz
        ScalerSetBit(P10_24_PIN_SHARE_CTRL64, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // TTL_G6: Hiz
        ScalerSetBit(P10_25_PIN_SHARE_CTRL65, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // TTL_G5: Hiz
        ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // TTL_G4: Hiz
        ScalerSetBit(P10_27_PIN_SHARE_CTRL67, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // TTL_G3: Hiz
        ScalerSetBit(P10_3B_LVDS_TTL_SELECT0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        // TTL_G2: Hiz
        ScalerSetBit(P10_3C_LVDS_TTL_SELECT1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // TTL_B7: Hiz
        ScalerSetBit(P10_1C_PIN_SHARE_CTRL54, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // TTL_B6: Hiz
        ScalerSetBit(P10_1D_PIN_SHARE_CTRL55, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // TTL_B5: Hiz
        ScalerSetBit(P10_1E_PIN_SHARE_CTRL56, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // TTL_B4: Hiz
        ScalerSetBit(P10_1F_PIN_SHARE_CTRL57, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // TTL_B3: Hiz
        ScalerSetBit(P10_20_PIN_SHARE_CTRL60, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // TTL_B2: Hiz
        ScalerSetBit(P10_21_PIN_SHARE_CTRL61, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Set DISP mode is Hiz
        ScalerSetBit(P39_00_LVDS_DISP_TYPE, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // Disable DCLK
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_20_DISPLAY_CLOCK_FINE_TUNE, ~_BIT1, 0x00);

        // Set DEN: GPI
        ScalerSetBit(P10_2A_PIN_SHARE_CTRL72, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Set DHS: GPI
        ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Set DCLK: GPI
        ScalerSetBit(P10_2C_PIN_SHARE_CTRL74, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Set DVS: GPI
        ScalerSetBit(P10_2D_PIN_SHARE_CTRL75, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Port AB Weakly Pull Down, Disable Port AB Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), _BIT7);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), _BIT7);
    }
}
#endif // End of #if(_PANEL_STYLE == _PANEL_TTL)
