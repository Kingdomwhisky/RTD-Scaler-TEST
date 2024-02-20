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
// ID Code      : RL6492_Series_Power.c No.0000
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
void ScalerPowerTypeCPowerACOnSetting(void);
void ScalerPowerAllGroupPowerCutReset(BYTE ucOn);

void ScalerPowerGroupTopIsolation(BYTE ucOn);
void ScalerPowerGroupADIIsolation(BYTE ucOn);
void ScalerPowerGroupDPHYIsolation(BYTE ucOn);
void ScalerPowerGroupU3RetimerIsolation(BYTE ucOn);
void ScalerPowerGroupTPCUFPIsolation(BYTE ucOn);
void ScalerPowerGroupHDCP22Isolation(BYTE ucOn);

void ScalerPowerGroupTopPowerCut(BYTE ucOn);
void ScalerPowerGroupADIPowerCut(BYTE ucOn);
void ScalerPowerGroupDPHYPowerCut(BYTE ucOn);
void ScalerPowerGroupU3RetimerPowerCut(BYTE ucOn);
void ScalerPowerGroupTPCUFPPowerCut(BYTE ucOn);
void ScalerPowerGroupHDCP22PowerCut(BYTE ucOn);

void ScalerPowerRecoverAGroupIsolationData(void);
void ScalerPowerRecoverBGroupIsolationData(void);
void ScalerPowerRecoverCGroupIsolationData(void);
void ScalerPowerRecoverDGroupIsolationData(void);
void ScalerPowerRecoverEGroupIsolationData(void);

void ScalerPowerRecoverTopGroupIsolationData(void);
void ScalerPowerRecoverGDITXGroupIsolationData(void);

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
        case _POWER_ACTION_AC_ON_INITIAL:

            ScalerPowerTypeCPowerACOnSetting();

            ucPowerIsoFlg = (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:

#if(_PANEL_STYLE == _PANEL_LVDS)
            // LVDS Pad Power Off
            ScalerDisplayLvdsPadPower(_OFF);
#elif(_PANEL_STYLE == _PANEL_DPTX)
            // LVDS Pad Power Off for eDP
            ScalerDisplayUseLvdsPadPower(_OFF);
#endif
            // Group Top block isolation control
            ScalerPowerGroupTopIsolation(_ON);

            ucPowerIsoFlg |= _BIT0;
            ucPowerIsoFlg |= _BIT1;

            // Group ADI block isolation control
            ScalerPowerGroupADIIsolation(_ON);
            ucPowerIsoFlg |= _BIT2;

            // Group DPHY block isolation control
            ScalerPowerGroupDPHYIsolation(_ON);

            // Group D block isolation control
            ucPowerIsoFlg |= _BIT3;

            // Group U3 block isolation control
            ScalerPowerGroupU3RetimerIsolation(_ON);

            // Group E block isolation control
            ucPowerIsoFlg |= _BIT4;

            // Group HDCP2_2 isolation control
            ScalerPowerGroupHDCP22Isolation(_ON);

            // Group ADI power control
            ScalerPowerGroupADIPowerCut(_ON);

            // Grounp DPHY power control
            ScalerPowerGroupDPHYPowerCut(_ON);

            // Group U3 Retimer power control
            ScalerPowerGroupU3RetimerPowerCut(_ON);

            // Group HDCP2_2 PowerCut control
            ScalerPowerGroupHDCP22PowerCut(_ON);

            // Group A power control control by GPIO
            ScalerPowerGroupTopPowerCut(_ON);

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            // All power group Reset
            ScalerPowerAllGroupPowerCutReset(_ON);

            // Group A power supply control by GPIO
            ScalerPowerGroupTopPowerCut(_OFF);

            // Grounp DPHY power control
            ScalerPowerGroupDPHYPowerCut(_OFF);

            // Group ADI power control
            ScalerPowerGroupADIPowerCut(_OFF);

#if(_USB3_RETIMER_SUPPORT == _ON)
            // Group U3 Retimer power control
            ScalerPowerGroupU3RetimerPowerCut(_OFF);
#endif

            // Group HDCP2_2 PowerCut control
            ScalerPowerGroupHDCP22PowerCut(_OFF);

            // Group A block isolation control
            ScalerPowerGroupTopIsolation(_OFF);

            // Group DPHY block isolation control
            ScalerPowerGroupDPHYIsolation(_OFF);

            // Group ADI block isolation control
            ScalerPowerGroupADIIsolation(_OFF);

#if(_USB3_RETIMER_SUPPORT == _ON)
            // Group U3 Retimer isolation control
            ScalerPowerGroupU3RetimerIsolation(_OFF);
#endif

            // Group HDCP2_2 isolation control
            ScalerPowerGroupHDCP22Isolation(_OFF);

            // All power group Relase
            ScalerPowerAllGroupPowerCutReset(_OFF);

#if(_PANEL_STYLE == _PANEL_LVDS)
            // LVDS Pad Power On
            ScalerDisplayLvdsPadPower(_ON);
#elif(_PANEL_STYLE == _PANEL_DPTX)
            // LVDS Pad Power On for eDP
            ScalerDisplayUseLvdsPadPower(_ON);
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_PS:

            break;

        case _POWER_ACTION_PS_TO_OFF:

            break;

        default:
            break;
    }

    return ucPowerIsoFlg;
}

//--------------------------------------------------
// Description  : Group Type C Power on/off
// Input Value  : ON  --> Group Type C (Low Power)
// Input Value  : OFF --> Group Type C (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerTypeCPowerACOnSetting(void)
{
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    // Group TPCUFP Power Cut block Reset
    ScalerSetBit(P6F_27_USB_TYPEC_POWER_CTRL, ~_BIT0, _BIT0);

    // Group Type-C power control
    ScalerPowerGroupTPCUFPPowerCut(_OFF);

    // Group Type-C isolation control
    ScalerPowerGroupTPCUFPIsolation(_OFF);

    // Group TPCUFP Power Cut Release
    ScalerSetBit(P6F_27_USB_TYPEC_POWER_CTRL, ~_BIT0, 0x00);
#else
    // Group Type-C isolation control
    ScalerPowerGroupTPCUFPIsolation(_ON);

    // Group Type-C power control
    ScalerPowerGroupTPCUFPPowerCut(_ON);

    // 10-bit SARADC power off
    ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~_BIT0, 0x00);
#endif
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
        // Group Top Power Cut block Reset
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT0, _BIT0);

        // Group DPHY Power Cut block Reset
        ScalerSetBit(P6F_29_DP_U3_DPHY_POWER_CTRL, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        // Group ADI Power Cut block Reset
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT0, _BIT0);

        // Group U3 Power Cut block Reset
        ScalerSetBit(P6F_28_USB3_RETIMER_POWER_CTRL, ~_BIT0, _BIT0);

        // Group HDCP22 Power Cut block Reset
        ScalerSetBit(P80_0B_HDCP_POWER_CTRL, ~_BIT0, _BIT0);
    }
    else
    {
        // Group Top Power Cut block Reset
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT0, 0x00);

        // Group DPHY Power Cut block Reset
        ScalerSetBit(P6F_29_DP_U3_DPHY_POWER_CTRL, ~(_BIT2 | _BIT0), 0x00);

        // Group ADI Power Cut block Reset
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT0, 0x00);

        // Group U3 Power Cut block Reset
        ScalerSetBit(P6F_28_USB3_RETIMER_POWER_CTRL, ~_BIT0, 0x00);

        // Group HDCP22 Power Cut block Reset
        ScalerSetBit(P80_0B_HDCP_POWER_CTRL, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group TOP Isolation on/off
// Input Value  : ON --> Group A(Low Power) ; OFF --> Group A (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupTopIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Analog isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~(_BIT5 | _BIT4), 0x00);

        // Digital isolation on
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT1, 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

        // Wait for VCCK_OFF Power On Stable
        POLLING_VCCK_OFF_STATUS(_VCCK_OFF_TIME_POLLING_POWER_ON);
    }
}

//--------------------------------------------------
// Description  : Group ADI Isolation on/off
// Input Value  : ON --> Group ADI(Low Power) ; OFF --> Group ADI (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupADIIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Analog isolation on
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT6, 0x00);

        // Digital isolation on
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT1, 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT6, _BIT6);
    }
}

//--------------------------------------------------
// Description  : Group DPHY Isolation on/off
// Input Value  : ON  --> Group DPHY (Low Power)
// Input Value  : OFF --> Group DPHY (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupDPHYIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Analog isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT0, 0x00);

        // Digital isolation on
        ScalerSetBit(P6F_29_DP_U3_DPHY_POWER_CTRL, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P6F_29_DP_U3_DPHY_POWER_CTRL, ~(_BIT3 | _BIT1), 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Group U3Retimer Isolation on/off
// Input Value  : ON  --> Group U3Retimer (Low Power)
// Input Value  : OFF --> Group U3Retimer (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupU3RetimerIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Digital isolation on
        ScalerSetBit(P6F_28_USB3_RETIMER_POWER_CTRL, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P6F_28_USB3_RETIMER_POWER_CTRL, ~(_BIT3 | _BIT1), 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT1, _BIT1);
    }
}

//--------------------------------------------------
// Description  : Group TPCUFP Isolation on/off
// Input Value  : ON  --> Group TPCUFP (Low Power)
// Input Value  : OFF --> Group TPCUFP (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupTPCUFPIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Analog isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT2, 0x00);

        // Digital isolation on
        ScalerSetBit(P6F_27_USB_TYPEC_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P6F_27_USB_TYPEC_POWER_CTRL, ~_BIT1, 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT2, _BIT2);
    }
}

//--------------------------------------------------
// Description  : Group HDCP22 Isolation on/off
// Input Value  : ON  --> Group HDCP22 (Low Power)
// Input Value  : OFF --> Group HDCP22 (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupHDCP22Isolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Digital isolation on
        ScalerSetBit(P80_0B_HDCP_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P80_0B_HDCP_POWER_CTRL, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group TOP Power on/off
// Input Value  : ON --> Group A(Low Power) ; OFF --> Group A (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupTopPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Strong power off
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT5, 0x00);

        // Weak power off
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Weak power on
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT4, _BIT4);

        // Wait for weak power on flag
        pData[0] = 50;

        while((ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }

        // Strong power on
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT5, _BIT5);

        // Wait for strong power on flag
        pData[0] = 50;

        while((ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }
        PCB_VCCK_OFF_POWER(_VCCK_OFF_POWER_ON);
    }
}

//--------------------------------------------------
// Description  : Group ADI Power on/off
// Input Value  : ON --> Group ADI(Low Power) ; OFF --> Group ADI (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupADIPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Strong power off
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT5, 0x00);

        // Weak power off
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT4, 0x00);

        // Intermal LV Power switch off
        ScalerSetBit(P1D_15_BANDGAP_01, ~_BIT0, 0x00);
    }
    else
    {
        // Intermal LV Power switch on
        ScalerSetBit(P1D_15_BANDGAP_01, ~_BIT0, _BIT0);

        // Weak power on
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT4, _BIT4);

        // Wait for weak power on flag
        pData[0] = 50;

        while((ScalerGetBit(P6F_26_ADI_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }

        // Strong power on
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT5, _BIT5);

        // Wait for strong power on flag
        pData[0] = 50;

        while((ScalerGetBit(P6F_26_ADI_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }
    }
}

//--------------------------------------------------
// Description  : Group DPHY Power on/off
// Input Value  : ON  --> Group DPHY (Low Power)
// Input Value  : OFF --> Group DPHY (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupDPHYPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // U3 APHY / OOBS power off
        ScalerSetBit(P6F_2A_ANALOG_APHY_POWER_CTRL, ~(_BIT5 | _BIT4), 0x00);

        // Strong power off
        ScalerSetBit(P6F_29_DP_U3_DPHY_POWER_CTRL, ~_BIT5, 0x00);

        // Weak power off
        ScalerSetBit(P6F_29_DP_U3_DPHY_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Weak power on
        ScalerSetBit(P6F_29_DP_U3_DPHY_POWER_CTRL, ~_BIT4, _BIT4);

        // Wait for weak power on flag
        pData[0] = 50;

        while((ScalerGetBit(P6F_29_DP_U3_DPHY_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }

        // Strong power on
        ScalerSetBit(P6F_29_DP_U3_DPHY_POWER_CTRL, ~_BIT5, _BIT5);

        // Wait for strong power on flag
        pData[0] = 50;

        while((ScalerGetBit(P6F_29_DP_U3_DPHY_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }

        // U3 APHY / OOBS power on
        ScalerSetBit(P6F_2A_ANALOG_APHY_POWER_CTRL, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
    }
}

//--------------------------------------------------
// Description  : Group U3Retimer Power on/off
// Input Value  : ON  --> Group U3Retimer (Low Power)
// Input Value  : OFF --> Group U3Retimer (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupU3RetimerPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // USB3 APHY / OOBS power off
        ScalerSetBit(P6F_2A_ANALOG_APHY_POWER_CTRL, ~(_BIT1 | _BIT0), 0x00);

        // Strong power off
        ScalerSetBit(P6F_28_USB3_RETIMER_POWER_CTRL, ~_BIT5, 0x00);

        // Weak power off
        ScalerSetBit(P6F_28_USB3_RETIMER_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // USB3 APHY / OOBS power on
        ScalerSetBit(P6F_2A_ANALOG_APHY_POWER_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Weak power on
        ScalerSetBit(P6F_28_USB3_RETIMER_POWER_CTRL, ~_BIT4, _BIT4);

        // Wait for weak power on flag
        pData[0] = 50;

        while((ScalerGetBit(P6F_28_USB3_RETIMER_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }

        // Strong power on
        ScalerSetBit(P6F_28_USB3_RETIMER_POWER_CTRL, ~_BIT5, _BIT5);

        // Wait for strong power on flag
        pData[0] = 50;

        while((ScalerGetBit(P6F_28_USB3_RETIMER_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }
    }
}

//--------------------------------------------------
// Description  : Group TPCUFP Power on/off
// Input Value  : ON  --> Group TPCUFP (Low Power)
// Input Value  : OFF --> Group TPCUFP (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupTPCUFPPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Strong power off
        ScalerSetBit(P6F_27_USB_TYPEC_POWER_CTRL, ~_BIT5, 0x00);

        // Weak power off
        ScalerSetBit(P6F_27_USB_TYPEC_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Weak power on
        ScalerSetBit(P6F_27_USB_TYPEC_POWER_CTRL, ~_BIT4, _BIT4);

        // Wait for weak power on flag
        pData[0] = 50;

        while((ScalerGetBit(P6F_27_USB_TYPEC_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }

        // Strong power on
        ScalerSetBit(P6F_27_USB_TYPEC_POWER_CTRL, ~_BIT5, _BIT5);

        // Wait for strong power on flag
        pData[0] = 50;

        while((ScalerGetBit(P6F_27_USB_TYPEC_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }
    }
}

//--------------------------------------------------
// Description  : Group HDCP22 Power on/off
// Input Value  : ON  --> Group HDCP22 (Low Power)
// Input Value  : OFF --> Group HDCP22 (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupHDCP22PowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Strong power off
        ScalerSetBit(P80_0B_HDCP_POWER_CTRL, ~_BIT5, 0x00);

        // Weak power off
        ScalerSetBit(P80_0B_HDCP_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Weak power on
        ScalerSetBit(P80_0B_HDCP_POWER_CTRL, ~_BIT4, _BIT4);

        // Wait for weak power on flag
        pData[0] = 50;

        while((ScalerGetBit(P80_0B_HDCP_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
        {
            DELAY_5US();
        }

        // Strong power on
        ScalerSetBit(P80_0B_HDCP_POWER_CTRL, ~_BIT5, _BIT5);

        // Wait for strong power on flag
        pData[0] = 50;

        while((ScalerGetBit(P80_0B_HDCP_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
        {
            DELAY_5US();
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
    ScalerPowerRecoverGDITXGroupIsolationData();
}

//--------------------------------------------------
// Description  : Recover B Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverBGroupIsolationData(void)
{
}

//--------------------------------------------------
// Description  : Recover The setting of Group C Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverCGroupIsolationData(void)
{
    //////////////////////// GDI power cut block start ///////////////////////////////
#if(_DP_SUPPORT == _ON)
    // Set R0' Available HW Mode
    ScalerSetBit(PB_1A_HDCP_IRQ, ~(_BIT5 | _BIT4), _BIT5);

    // Enable DP Link Integrity Enable
    ScalerSetBit(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

#if(_D0_DP_EXIST == _ON)
    // Restore HDCP Mode
    SET_DP_RX0_HDCP_MODE(GET_DP_RX0_HDCP_MODE_BACKUP());
#endif

#if(_D1_DP_EXIST == _ON)
    // Restore HDCP Mode
    SET_DP_RX1_HDCP_MODE(GET_DP_RX1_HDCP_MODE_BACKUP());
#endif

    // DP Mac Clock Select to Xtal Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    if(ScalerGetBit(PB_20_HDCP_DEBUG, _BIT7) == _BIT7)
    {
        // HDCP R0 Calculate
        ScalerSetBit(PB_63_HDCP_OTHER, ~_BIT7, _BIT7);
        ScalerSetBit(PB_63_HDCP_OTHER, ~_BIT7, 0x00);
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
// Description  : Recover D Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverDGroupIsolationData(void)
{
}

//--------------------------------------------------
// Description  : Recover The setting of Group E Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverEGroupIsolationData(void)
{
}

//--------------------------------------------------
// Description  : Recover The setting of Group A Power Cut Area.
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
#elif(_PANEL_STYLE == _PANEL_VBO)
    // VBO Power On recover
    ScalerDisplayVboInitialTable();
#endif

    //////////////////////// LVDS + LVDSPLL and VBO block End ////////////////////


    //////////////////////// DPLL/MPLL/DDR PLL block start ///////////////////////

    // DPLL power up
    ScalerPLLSetDPLLReset();

    //////////////////////// DPLL/MPLL/DDR PLL  block End ////////////////////////


    //////////////////////// DDR DLL + DDR Delaychain start //////////////////////

    //////////////////////// DDR DLL + DDR Delaychain End ////////////////////////

    //////////////////////// HDCP 2.2 start //////////////////////

#if(_HDCP_2_2_SUPPORT == _ON)
    ScalerHdcp2Initial();
#endif

    //////////////////////// HDCP 2.2 End ////////////////////////
}

//--------------------------------------------------
// Description  : Recover The setting of Group GDI TX Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverGDITXGroupIsolationData(void)
{
#if(_PANEL_STYLE == _PANEL_DPTX)
    // Initial DPTx1
    ScalerDisplayDPTx1Initial();
#endif // #if(_PANEL_STYLE == _PANEL_DPTX)
}

