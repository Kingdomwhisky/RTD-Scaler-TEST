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
// ID Code      : RL6369_Series_Power.c No.0000
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
void ScalerPowerGroupAIsolation(BYTE ucOn);
void ScalerPowerGroupBIsolation(BYTE ucOn);
void ScalerPowerGroupDIsolation(BYTE ucOn);
void ScalerPowerGroupAPowerCut(BYTE ucOn);
void ScalerPowerGroupBPowerCut(BYTE ucOn);
void ScalerPowerGroupDPowerCut(BYTE ucOn);
void ScalerPowerRecoverAGroupIsolationData(void);
void ScalerPowerRecoverBGroupIsolationData(void);
void ScalerPowerRecoverCGroupIsolationData(void);
void ScalerPowerRecoverDGroupIsolationData(void);
void ScalerPowerRecoverEGroupIsolationData(void);

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

#if(_PANEL_STYLE == _PANEL_LVDS)
            // LVDS Pad Power Off
            ScalerDisplayLvdsPadPower(_OFF);
#elif(_PANEL_STYLE == _PANEL_TTL)
            // TTL Pad Power Off
            ScalerDisplayTtlPadPower(_OFF);
#endif

            // Group A (another name is top power) block isolation control
            ScalerPowerGroupAIsolation(_ON);
            ucPowerIsoFlg |= _BIT0;

            // Group B (audio) block isolation control
            ScalerPowerGroupBIsolation(_ON);
            ucPowerIsoFlg |= _BIT1;

            // Group D (another name is GDI power) block isolation control
            ScalerPowerGroupDIsolation(_ON);
            ucPowerIsoFlg |= _BIT3;

            // Group A (another name is top power) power control control by GPIO
            ScalerPowerGroupAPowerCut(_ON);

            // Group B (audio)power control
            ScalerPowerGroupBPowerCut(_ON);

            // Group D (another name is GDI power)power control
            ScalerPowerGroupDPowerCut(_ON);

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // All power group Reset
            ScalerPowerAllGroupPowerCutReset(_ON);

            // Group A (another name is top power) power supply control by GPIO
            ScalerPowerGroupAPowerCut(_OFF);

            // Group B (Audio) power control
            ScalerPowerGroupBPowerCut(_OFF);

            // Group D (another name is GDI power) power control
            ScalerPowerGroupDPowerCut(_OFF);

            // Group A (another name is top power) block isolation control
            ScalerPowerGroupAIsolation(_OFF);

            // Group B (audio) block isolation control
            ScalerPowerGroupBIsolation(_OFF);

            // Group D (another name is GDIpower) block isolation control
            ScalerPowerGroupDIsolation(_OFF);

            // All power group Relase
            ScalerPowerAllGroupPowerCutReset(_OFF);

#if(_PANEL_STYLE == _PANEL_LVDS)
            // LVDS Pad Power On
            ScalerDisplayLvdsPadPower(_ON);
#elif(_PANEL_STYLE == _PANEL_TTL)
            // TTL Pad Power On
            ScalerDisplayTtlPadPower(_ON);
#endif
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
        // Group A (another name is top power) Power Cut block Reset
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT0, _BIT0);

        // Audio Power Cut block Relase
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT0, _BIT0);

        // Group D (another name is GDI power) Power Cut block Reset
        ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT0, _BIT0);

        // GDI_2 Power Cut block Reset
        ScalerSetBit(P40_0A_GDI_2_POWER_CTRL, ~_BIT0, _BIT0);
    }
    else
    {
        // Group A (another name is top power) Power Cut block Relase
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT0, 0x00);

        // Audio Power Cut block Relase
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT0, 0x00);

        // Group D (another name is GDI power) Power Cut block Relase
        ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT0, 0x00);

        // GDI_2 Power Cut block Relase
        ScalerSetBit(P40_0A_GDI_2_POWER_CTRL, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group A Isolation on/off
// Input Value  : ON --> Group A(Low Power) ; OFF --> Group A (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupAIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Top Power M2PLL isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT5, _BIT5);

        // Top Power MPLL/DPLL/LVDSPLL region isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT4, _BIT4);

        // Top Power Digital region isolation on & USB analog Phy Isolation on
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Top Power M2PLL isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT5, 0x00);

        // Top Power Digital region isolation off & USB analog Phy Isolation off
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT1, 0x00);

        // Top Power analog region isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT4, 0x00);

#if(_USB_LV_SUPPORT == _ON)
        // Usb digital phy Power region isolation off
        ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT3, 0x00);
#else
        // Usb digital phy Power region isolation on
        ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT3, _BIT3);
#endif
    }
}

//--------------------------------------------------
// Description  : Group B (Audio) Isolation on/off
// Input Value  : ON --> Group B(Low Power) ; OFF --> Group B (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupBIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Audio Power Analog isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT3, _BIT3);

        // Audio Power Digital isolation on
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Audio Power Digital isolation off
        ScalerSetBit(PC0_0A_AUDIO_POWER_CTRL, ~_BIT1, 0x00);

        // Audio Power Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT3, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group B (another name is GDI power) Isolation on/off
// Input Value  : ON --> Group B(Low Power) ; OFF --> Group B (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupDIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
#if((_DP_HDMI_COMPATIBLE_MODE == _ON) || (_DP_POWER_OFF_HDCP_SUPPORT == _ON))
        if(GET_DP_DC_OFF_HPD_HIGH() == _OFF)
#endif
        {
            if(ScalerGlobalGetIDCode() > _RL6369_VER_B_ID_CODE)
            {
                // GDI_Phy analog isolation on
                ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT0, _BIT0);
            }
            else
            {
                // GDI_Phy analog isolation OFF
                ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT0, 0x00);
            }

            // DP-PLL, HDMI-Audio-PLL isolation on
            ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT2, _BIT2);

            // GDI Power Digital isolation on
            ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT1, _BIT1);
        }

        if((ScalerGlobalGetIDCode() > _RL6369_VER_B_ID_CODE) && ((bit)PCB_EMBEDDED_LDO_DETECT() == _EMBEDDED_LDO_OFF))
        {
            // GDI Power Switch off for external GDI1.1 In
            ScalerSetBit(P80_0A_GDI_PHY_POWER_CTRL, ~_BIT4, 0x00);
        }
        else
        {
            // GDI Power Switch on for external GDI1.1 In
            ScalerSetBit(P80_0A_GDI_PHY_POWER_CTRL, ~_BIT4, _BIT4);
        }

        // GDI_2(CBUS/ECBUS) Power Analog isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT1, _BIT1);

        // GDI_2 Power Digital isolation on
        ScalerSetBit(P40_0A_GDI_2_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
#if((_DP_HDMI_COMPATIBLE_MODE == _ON) || (_DP_POWER_OFF_HDCP_SUPPORT == _ON))
        if(GET_DP_DC_OFF_HPD_HIGH() == _OFF)
#endif
        {
            // GDI_Phy analog isolation off
            ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT0, 0x00);

            // GDI Power Digital isolation off
            ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT1, 0x00);

            // GDI Power Analog isolation off
            ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT2, 0x00);
        }

        // GDI Power Switch on for external GDI1.1 In
        ScalerSetBit(P80_0A_GDI_PHY_POWER_CTRL, ~_BIT4, _BIT4);

        // GDI_2 Power Digital isolation off
        ScalerSetBit(P40_0A_GDI_2_POWER_CTRL, ~_BIT1, 0x00);

        // GDI_2 Power Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group A (another name is Top power) Power on/off
// Input Value  : ON --> Group A(Low Power) ; OFF --> Group A (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupAPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Top Power Weak power off
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT4, 0x00);

        // Top Power Strong power off
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT5, 0x00);
    }
    else
    {
        // Top Power Block Power Cut
        if(ScalerGetBit(P0_09_TOP_POWER_CTRL, _BIT1) == _BIT1)
        {
            // Weak power on
            ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT4, _BIT4);

            // Wait for weak power on flag
            pData[0] = 200;

            while((ScalerGetBit(P0_09_TOP_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0)) {};

            // Strong power on
            ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT5, _BIT5);

            // Wait for strong power on flag
            pData[0] = 200;

            while((ScalerGetBit(P0_09_TOP_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0)) {};
        }
    }
}

//--------------------------------------------------
// Description  : Group B (Audio) Power on/off
// Input Value  : ON --> Group B(Low Power) ; OFF --> Group B (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupBPowerCut(BYTE ucOn)
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
        // Audio power block power cut on
        if((ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT3) == _BIT3) || (ScalerGetBit(PC0_0A_AUDIO_POWER_CTRL, _BIT1) == _BIT1))
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
}

//--------------------------------------------------
// Description  : Group D (another name is GDI power) Power on/off
// Input Value  : ON --> Group B(Low Power) ; OFF --> Group B (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupDPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
#if((_DP_HDMI_COMPATIBLE_MODE == _ON) || (_DP_POWER_OFF_HDCP_SUPPORT == _ON))
        if(GET_DP_DC_OFF_HPD_HIGH() == _OFF)
#endif
        {
            // GDI Power Strong power off
            ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT5, 0x00);

            // GDI Power Weak power off
            ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT4, 0x00);
        }

        // GDI_2 Power Strong power off
        ScalerSetBit(P40_0A_GDI_2_POWER_CTRL, ~_BIT5, 0x00);

        // GDI_2 Power Weak power off
        ScalerSetBit(P40_0A_GDI_2_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
#if((_DP_HDMI_COMPATIBLE_MODE == _ON) || (_DP_POWER_OFF_HDCP_SUPPORT == _ON))
        if(GET_DP_DC_OFF_HPD_HIGH() == _OFF)
#endif
        {
            // Group B power block power cut on
            if((ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT2) == _BIT2) || (ScalerGetBit(P0_0A_GDI_POWER_CTRL, _BIT1) == _BIT1))
            {
                // Weak power on
                ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT4, _BIT4);

                // Wait for weak power on flag
                pData[0] = 50;

                while((ScalerGetBit(P0_0A_GDI_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
                {
                    DELAY_5US();
                }

                // Strong power on
                ScalerSetBit(P0_0A_GDI_POWER_CTRL, ~_BIT5, _BIT5);

                // Wait for strong power on flag
                pData[0] = 50;

                while((ScalerGetBit(P0_0A_GDI_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
                {
                    DELAY_5US();
                }
            }
        }

        // GDI_2 power block power cut on
        if((ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT1) == _BIT1) || (ScalerGetBit(P40_0A_GDI_2_POWER_CTRL, _BIT1) == _BIT1))
        {
            // Weak power on
            ScalerSetBit(P40_0A_GDI_2_POWER_CTRL, ~_BIT4, _BIT4);

            // Wait for weak power on flag
            pData[0] = 50;

            while((ScalerGetBit(P40_0A_GDI_2_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
            {
                DELAY_5US();
            }

            // Strong power on
            ScalerSetBit(P40_0A_GDI_2_POWER_CTRL, ~_BIT5, _BIT5);

            // Wait for strong power on flag
            pData[0] = 50;

            while((ScalerGetBit(P40_0A_GDI_2_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
            {
                DELAY_5US();
            }
        }
    }
}

//--------------------------------------------------
// Description  : Recover The setting of Group A Power Cut Area (another name is top power).
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverAGroupIsolationData(void)
{
    //////////////////////// Pin Share Start /////////////////////////////////////

    PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON();

    ScalerPinsharePowerOnReset();

    //////////////////////// Pin Share End /////////////////////////////////////

    //////////////////////// LVDS + LVDSPLL and VBO block start //////////////////

#if(_PANEL_STYLE == _PANEL_LVDS)
    // LVDS Port Power On recover
    ScalerDisplayLvdsInitialTable();
#elif(_PANEL_STYLE == _PANEL_TTL)
    // TTL Power On recover
    ScalerDisplayTtlInitialTable();
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
// Description  : Recover The setting of Group B Power Cut Area .
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverBGroupIsolationData(void)
{
    //////////////////////// Audio power cut block start ///////////////////////////////

    //////////////////////// Audio power cut block End /////////////////////////////////
}

//--------------------------------------------------
// Description  : Recover The setting of Group C Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverCGroupIsolationData(void)
{
    // There is no action on RL6369 IC (For Tx Block)
}

//--------------------------------------------------
// Description  : Recover The setting of Group D Power Cut Area (another name is GDI power).
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverDGroupIsolationData(void)
{
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
}

//--------------------------------------------------
// Description  : Recover The setting of Group E Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverEGroupIsolationData(void)
{
    // There is no action on RL6369 IC (For high speed port Block)
}

