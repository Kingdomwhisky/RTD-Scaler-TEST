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
// ID Code      : RL6463_Series_Power.c No.0000
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
BYTE ScalerPowerIsolation(EnumPowerAction enumSwitch);
void ScalerPowerAllGroupPowerCutReset(BYTE ucOn);
void ScalerPowerGroupTopIsolation(BYTE ucOn);
void ScalerPowerGroupAudioIsolation(BYTE ucOn);
void ScalerPowerGroupGDIIsolation(BYTE ucOn);
void ScalerPowerGroupTopPowerCut(BYTE ucOn);
void ScalerPowerGroupAudioPowerCut(BYTE ucOn);
void ScalerPowerGroupGDIPowerCut(BYTE ucOn);
void ScalerPowerRecoverAGroupIsolationData(void);
void ScalerPowerRecoverBGroupIsolationData(void);
void ScalerPowerRecoverCGroupIsolationData(void);
void ScalerPowerRecoverDGroupIsolationData(void);
void ScalerPowerRecoverEGroupIsolationData(void);
void ScalerPowerRecoverTopGroupIsolationData(void);
void ScalerPowerRecoverAudioGroupIsolationData(void);
void ScalerPowerRecoverGDIGroupIsolationData(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Power cut block flow
// Input Value  : enumSwitch    --> Power action description.
// Output Value : return power group enter isolation area
//--------------------------------------------------
BYTE ScalerPowerIsolation(EnumPowerAction enumSwitch)
{
    BYTE ucPowerIsoFlg = 0x00;

    switch(enumSwitch)
    {
        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_AC_ON_INITIAL:

            // LVDS Pad Power Off
            ScalerDisplayLvdsPadPower(_OFF);

            // Group Top block isolation control
            ScalerPowerGroupTopIsolation(_ON);
            ucPowerIsoFlg |= _BIT0;

            // Group Audio block isolation control
            ScalerPowerGroupAudioIsolation(_ON);
            ucPowerIsoFlg |= _BIT1;

            // Group GDI & GDI PHY block isolation control
            ScalerPowerGroupGDIIsolation(_ON);
            ucPowerIsoFlg |= _BIT3;

            // Group Top block power control
            ScalerPowerGroupTopPowerCut(_ON);

            // Group Audio block power control
            ScalerPowerGroupAudioPowerCut(_ON);

            // Group GDI & GDI PHY block power control
            ScalerPowerGroupGDIPowerCut(_ON);

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // All power group Reset
            ScalerPowerAllGroupPowerCutReset(_ON);

            // Group Top block power control
            ScalerPowerGroupTopPowerCut(_OFF);

            // Group Audio block power control
            ScalerPowerGroupAudioPowerCut(_OFF);

            // Group GDI power block power control
            ScalerPowerGroupGDIPowerCut(_OFF);

            // Group Top block isolation control
            ScalerPowerGroupTopIsolation(_OFF);

            // Group Audio block isolationcontrol
            ScalerPowerGroupAudioIsolation(_OFF);

            // Group GDI & GDI PHY block isolation control
            ScalerPowerGroupGDIIsolation(_OFF);

            // All power group Relase
            ScalerPowerAllGroupPowerCutReset(_OFF);

            // LVDS Pad Power On
            ScalerDisplayLvdsPadPower(_ON);

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_PS:
        case _POWER_ACTION_PS_TO_OFF:

            break;

        default:
            break;
    }

    return ucPowerIsoFlg;
}

//--------------------------------------------------
// Description  : All Group Power reset
// Input Value  : ON --> Reset ; OFF --> Release
// Output Value : None
//--------------------------------------------------
void ScalerPowerAllGroupPowerCutReset(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Top Power Cut block Reset
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT0, _BIT0);

        // Audio Power Cut block Reset
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT0, _BIT0);

        // GDI & GDI PHY Power Cut block Reset
        ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT0, _BIT0);
    }
    else
    {
        // Top Power Cut block Reset
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT0, 0x00);

        // Audio Power Cut block Reset
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT0, 0x00);

        // GDI Power Cut block Reset
        ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group Top Isolation on/off
// Input Value  : ON --> Top Power (Low Power)
//                OFF --> Top Power (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupTopIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Top block Analog isolation on
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT0, 0x00);

        // Top block Digital isolation on
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Top block Digital isolation off
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT1, 0x00);

        // Top block Analog isolation off
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Group Audio Isolation on/off
// Input Value  : ON --> Audio Power (Low Power)
//                OFF --> Audio Power (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupAudioIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Audio block Digital isolation on
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Audio block Digital isolation off
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group GDI & GDI PHY Power Isolation on/off
// Input Value  : ON  --> Group GDI & GDI PHY (Low Power) ;
//                OFF --> Group GDI & GDI PHY (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupGDIIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // GDI block Analog isolation on
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT5, 0x00);

        // GDI PHY block Analog isolation on
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT4, 0x00);

#if(_DP_POWER_OFF_HDCP_SUPPORT == _ON)
        if(GET_DP_DC_OFF_HPD_HIGH() == _OFF)
#endif
        {
            // GDI & GDI PHY block Digital isolation on
            ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT1, _BIT1);
        }

        // Internal LV power switch off
        ScalerSetBit(PB_B5_BANDGAP_01, ~_BIT0, _BIT0);
    }
    else
    {
#if(_DP_POWER_OFF_HDCP_SUPPORT == _ON)
        if(GET_DP_DC_OFF_HPD_HIGH() == _OFF)
#endif
        {
            // GDI & GDI PHY block Digital isolation off
            ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT1, 0x00);
        }

        // GDI PHY block Analog isolation off
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT4, _BIT4);

        // GDI block Analog isolation off
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT5, _BIT5);

        // Internal LV power switch on
        ScalerSetBit(PB_B5_BANDGAP_01, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Group Top Power on/off
// Input Value  : ON --> Group Top (Low Power)
//                OFF --> Group Top (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupTopPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Top Power Strong power off
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT5, 0x00);

        // Top Power Weak power off
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Weak power on
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT4, _BIT4);

        // Wait for weak power on flag
        pData[0] = 50;

        while((ScalerGetBit(P0_09_TOP_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }

        // Strong power on
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT5, _BIT5);

        // Wait for strong power on flag
        pData[0] = 50;

        while((ScalerGetBit(P0_09_TOP_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }
    }
}

//--------------------------------------------------
// Description  : Group Audio Power on/off
// Input Value  : ON --> Group B(Low Power) ; OFF --> Group B (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupAudioPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Audio Power Strong power off
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT5, 0x00);

        // Audio Power Weak power off
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Weak power on
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT4, _BIT4);

        // Wait for weak power on flag
        pData[0] = 50;

        while((ScalerGetBit(PC0_0A_AUDIO_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }

        // Strong power on
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT5, _BIT5);

        // Wait for strong power on flag
        pData[0] = 50;

        while((ScalerGetBit(PC0_0A_AUDIO_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }
    }
}

//--------------------------------------------------
// Description  : Group GDI & GDI PHY Power on/off
// Input Value  : ON --> Group GDI & GDI PHY Power (Low Power)
//                OFF --> Group GDI & GDI PHY Power (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupGDIPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
#if(_DP_POWER_OFF_HDCP_SUPPORT == _ON)
        if(GET_DP_DC_OFF_HPD_HIGH() == _OFF)
#endif
        {
            // GDI & GDI PHY Power Strong power off
            ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT5, 0x00);

            // GDI & GDI PHY Power Weak power off
            ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT4, 0x00);
        }
    }
    else
    {
#if(_DP_POWER_OFF_HDCP_SUPPORT == _ON)
        if(GET_DP_DC_OFF_HPD_HIGH() == _OFF)
#endif
        {
            // DI & GDI PHY Weak power on
            ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT4, _BIT4);

            // DI & GDI PHY Wait for weak power on flag
            pData[0] = 50;

            while((ScalerGetBit(P0_0A_GDI_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
            {
                DELAY_5US();
            }

            // DI & GDI PHY Strong power on
            ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT5, _BIT5);

            // DI & GDI PHY Wait for strong power on flag
            pData[0] = 50;

            while((ScalerGetBit(P0_0A_GDI_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
            {
                DELAY_5US();
            }
        }
    }
}

//--------------------------------------------------
// Description  : Recover A Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverAGroupIsolationData(void)
{
    ScalerPowerRecoverTopGroupIsolationData();
}

//--------------------------------------------------
// Description  : Recover B Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverBGroupIsolationData(void)
{
    ScalerPowerRecoverAudioGroupIsolationData();
}

//--------------------------------------------------
// Description  : Recover C Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverCGroupIsolationData(void)
{
}

//--------------------------------------------------
// Description  : Recover D Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverDGroupIsolationData(void)
{
    // Recover GDI Group Power Cut Area
    ScalerPowerRecoverGDIGroupIsolationData();
}

//--------------------------------------------------
// Description  : Recover E Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverEGroupIsolationData(void)
{
}

//--------------------------------------------------
// Description  : Recover Top Power Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverTopGroupIsolationData(void)
{
    //////////////////////// Pin Share Start /////////////////////////////////////

    PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON();

    ScalerPinsharePowerOnReset();

    //////////////////////// Pin Share End /////////////////////////////////////

    //////////////////////// LVDS + LVDSPLL and VBO block start //////////////////

#if(_PANEL_STYLE == _PANEL_LVDS)
    // LVDS Port Power On recover
    ScalerDisplayLvdsInitialTable();
#endif

    //////////////////////// LVDS + LVDSPLL and VBO block End ////////////////////


    //////////////////////// DPLL/MPLL/DDR PLL block start ///////////////////////

    // DPLL power up
    ScalerPLLSetDPLLReset();

    //////////////////////// DPLL/MPLL/DDR PLL  block End ////////////////////////


    //////////////////////// DDR DLL + DDR Delaychain start //////////////////////

    //////////////////////// DDR DLL + DDR Delaychain End ////////////////////////
}
//--------------------------------------------------
// Description  : Recover Audio Power Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverAudioGroupIsolationData(void)
{
}

//--------------------------------------------------
// Description  : Recover GDI Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverGDIGroupIsolationData(void)
{
    // There is no action on RL6369 IC (For Tx Block) //C Group

    //////////////////////// GDI power cut block start ///////////////////////////////
#if(_DP_SUPPORT == _ON)

    // Set R0' Available HW Mode
    ScalerSetBit(PB_1A_HDCP_IRQ, ~(_BIT5 | _BIT4), _BIT5);

    // Enable DP Link Integrity Enable
    ScalerSetBit(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

    // DP Mac Clock Select to Xtal Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    if(ScalerGetBit(PB_20_HDCP_DEBUG, _BIT7) == _BIT7)
    {
        // HDCP R0 Calculate
        ScalerSetBit(PB_63_DUMMY2, ~_BIT7, _BIT7);
        ScalerSetBit(PB_63_DUMMY2, ~_BIT7, 0x00);
    }
#endif
    //////////////////////// GDI power cut block End /////////////////////////////////

    //////////////////////// GDI_2(CBUS/ECBUS) power cut block start ///////////////////////////////

    //////////////////////// GDI_2(CBUS/ECBUS) power cut block End /////////////////////////////////

    //////////////////////// HDCP 2.2 start //////////////////////

#if(_HDCP_2_2_SUPPORT == _ON)
    ScalerHdcp2Initial();
#endif

    //////////////////////// HDCP 2.2 End ////////////////////////

    // There is no action on RL6369 IC (For high speed port Block) //E Group
}

