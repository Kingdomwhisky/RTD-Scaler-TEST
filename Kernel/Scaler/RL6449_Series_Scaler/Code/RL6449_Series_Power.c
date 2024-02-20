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
// ID Code      : RL6449_Series_Power.c No.0000
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
void ScalerPowerGroupADIIsolation(BYTE ucOn);
void ScalerPowerGroupD0Isolation(BYTE ucOn);
void ScalerPowerGroupD1Isolation(BYTE ucOn);
void ScalerPowerGroupD2Isolation(BYTE ucOn);
void ScalerPowerGroupD3Isolation(BYTE ucOn);
void ScalerPowerGroupAPowerCut(BYTE ucOn);
void ScalerPowerGroupADIPowerCut(BYTE ucOn);
void ScalerPowerGroupD0PowerCut(BYTE ucOn);
void ScalerPowerGroupD1PowerCut(BYTE ucOn);
void ScalerPowerGroupD2PowerCut(BYTE ucOn);
void ScalerPowerGroupD3PowerCut(BYTE ucOn);
void ScalerPowerRecoverAGroupIsolationData(void);
void ScalerPowerRecoverBGroupIsolationData(void);
void ScalerPowerRecoverCGroupIsolationData(void);
void ScalerPowerRecoverDGroupIsolationData(void);
void ScalerPowerRecoverEGroupIsolationData(void);
void ScalerPowerRecoverADIGroupIsolationData(void);
void ScalerPowerRecoverDPRxGroupIsolationData(void);
void ScalerPowerRecoverHDMIRxGroupIsolationData(void);


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

            // Group A block isolation control
            ScalerPowerGroupAIsolation(_ON);

            ucPowerIsoFlg |= _BIT0;

            // Group B block isolation control
            ScalerPowerGroupBIsolation(_ON);
            ucPowerIsoFlg |= _BIT1;

            // Group ADI block isolation control
            ScalerPowerGroupADIIsolation(_ON);
            ucPowerIsoFlg |= _BIT2;

            // Group D2 to D3 block isolation control
            ScalerPowerGroupD2Isolation(_ON);
            ScalerPowerGroupD3Isolation(_ON);
            ucPowerIsoFlg |= _BIT3;

            // Group D0 to D1 block isolation control
            ScalerPowerGroupD0Isolation(_ON);
            ScalerPowerGroupD1Isolation(_ON);
            ucPowerIsoFlg |= _BIT4;

            // Group ADI power control
            ScalerPowerGroupADIPowerCut(_ON);

            // Group D2 to D3 power control
            ScalerPowerGroupD2PowerCut(_ON);
            ScalerPowerGroupD3PowerCut(_ON);

            // Group D0 to D1 power control
            ScalerPowerGroupD0PowerCut(_ON);
            ScalerPowerGroupD1PowerCut(_ON);

            // Group A power control control by GPIO
            ScalerPowerGroupAPowerCut(_ON);

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // All power group Reset
            ScalerPowerAllGroupPowerCutReset(_ON);

            // Group A power supply control by GPIO
            ScalerPowerGroupAPowerCut(_OFF);

            // Group ADI power control
            ScalerPowerGroupADIPowerCut(_OFF);

            // Group D2 to D3 power control
            ScalerPowerGroupD2PowerCut(_OFF);
            ScalerPowerGroupD3PowerCut(_OFF);

            // Group D0 to D1 power control
            ScalerPowerGroupD0PowerCut(_OFF);
            ScalerPowerGroupD1PowerCut(_OFF);

            // Group A block isolation control
            ScalerPowerGroupAIsolation(_OFF);

            // Group B block isolation control
            ScalerPowerGroupBIsolation(_OFF);

            // Group ADI block isolation control
            ScalerPowerGroupADIIsolation(_OFF);

            // Group D2 to D3 block isolation control
            ScalerPowerGroupD2Isolation(_OFF);
            ScalerPowerGroupD3Isolation(_OFF);

            // Group D0 to D1 block isolation control
            ScalerPowerGroupD0Isolation(_OFF);
            ScalerPowerGroupD1Isolation(_OFF);

            // All power group Relase
            ScalerPowerAllGroupPowerCutReset(_OFF);

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
// Description  : All Group Power reset
// Input Value  : ON --> Reset ; OFF --> Release
// Output Value : None
//--------------------------------------------------
void ScalerPowerAllGroupPowerCutReset(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Group A Power Cut block Reset
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT0, _BIT0);

        // Group ADI Power Cut block Reset
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT0, _BIT0);

        if((ScalerGetBit(P6F_20_D0_POWER_CTRL, _BIT1) == _BIT1) || (ScalerGetBit(P0_F1_VCCKOFF_CONTROL1, _BIT0) == _BIT0))
        {
            // Group D0 Power Cut block Reset
            ScalerSetBit(P6F_20_D0_POWER_CTRL, ~_BIT0, _BIT0);
        }

        if((ScalerGetBit(P6F_21_D1_POWER_CTRL, _BIT1) == _BIT1) || (ScalerGetBit(P0_F1_VCCKOFF_CONTROL1, _BIT1) == _BIT1))
        {
            // Group D1 Power Cut block Reset
            ScalerSetBit(P6F_21_D1_POWER_CTRL, ~_BIT0, _BIT0);
        }

        if((ScalerGetBit(P6F_22_D2_POWER_CTRL, _BIT1) == _BIT1) || (ScalerGetBit(P0_F1_VCCKOFF_CONTROL1, _BIT2) == _BIT2))
        {
            // Group D2 Power Cut block Reset
            ScalerSetBit(P6F_22_D2_POWER_CTRL, ~_BIT0, _BIT0);
        }

        if((ScalerGetBit(P6F_23_D3_POWER_CTRL, _BIT1) == _BIT1) || (ScalerGetBit(P0_F1_VCCKOFF_CONTROL1, _BIT3) == _BIT3))
        {
            // Group D3 Power Cut block Reset
            ScalerSetBit(P6F_23_D3_POWER_CTRL, ~_BIT0, _BIT0);
        }
    }
    else
    {
        // Group A Power Cut block Relase
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT0, 0x00);

        // Group ADI Power Cut block Relase
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT0, 0x00);

        // Group D0 Power Cut block Relase
        ScalerSetBit(P6F_20_D0_POWER_CTRL, ~_BIT0, 0x00);

        // Group D1 Power Cut block Relase
        ScalerSetBit(P6F_21_D1_POWER_CTRL, ~_BIT0, 0x00);

        // Group D2 Power Cut block Relase
        ScalerSetBit(P6F_22_D2_POWER_CTRL, ~_BIT0, 0x00);

        // Group D3 Power Cut block Relase
        ScalerSetBit(P6F_23_D3_POWER_CTRL, ~_BIT0, 0x00);
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
        // Analog isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT4, _BIT4);

        // Digital isolation on
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT1, 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT4, 0x00);

        // Wait for VCCK_OFF Power On Stable
        POLLING_VCCK_OFF_STATUS(_VCCK_OFF_TIME_POLLING_POWER_ON);
    }
}

//--------------------------------------------------
// Description  : Group B Isolation on/off
// Input Value  : ON --> Group B(Low Power) ; OFF --> Group B (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupBIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Analog isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT3, _BIT3);
    }
    else
    {
        // Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT3, 0x00);
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
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT6, _BIT6);

        // Digital isolation on
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P6F_26_ADI_POWER_CTRL, ~_BIT1, 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT6, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group D0 Isolation on/off
// Input Value  : ON --> Group D0 (Low Power) ; OFF --> Group D0 (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupD0Isolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // D0 Analog isolation on
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT0, _BIT0);

        // D0 Digital isolation on
        ScalerSetBit(P6F_20_D0_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // D0 Digital isolation off
        ScalerSetBit(P6F_20_D0_POWER_CTRL, ~_BIT1, 0x00);

        // D0 Analog isolation off
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group D1 Isolation on/off
// Input Value  : ON --> Group D1 (Low Power) ; OFF --> Group D1 (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupD1Isolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // D1 Analog isolation on
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT1, _BIT1);

        // D1 Digital isolation on
        ScalerSetBit(P6F_21_D1_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // D1 Digital isolation off
        ScalerSetBit(P6F_21_D1_POWER_CTRL, ~_BIT1, 0x00);

        // D1 Analog isolation off
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group D2 Isolation on/off
// Input Value  : ON --> Group D2 (Low Power) ; OFF --> Group D2 (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupD2Isolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // D2 Analog isolation on
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT2, _BIT2);

        // D2 Digital isolation on
        ScalerSetBit(P6F_22_D2_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // D2 Digital isolation off
        ScalerSetBit(P6F_22_D2_POWER_CTRL, ~_BIT1, 0x00);

        // D2 Analog isolation off
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT2, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group D3 Isolation on/off
// Input Value  : ON --> Group D3 (Low Power) ; OFF --> Group D3 (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupD3Isolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // D3 Analog isolation on
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT3, _BIT3);

        // D3 Digital isolation on
        ScalerSetBit(P6F_23_D3_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // D3 Digital isolation off
        ScalerSetBit(P6F_23_D3_POWER_CTRL, ~_BIT1, 0x00);

        // D3 Analog isolation off
        ScalerSetBit(P0_F1_VCCKOFF_CONTROL1, ~_BIT3, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group A Power on/off
// Input Value  : ON --> Group A(Low Power) ; OFF --> Group A (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupAPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        PCB_VCCK_OFF_POWER(_VCCK_OFF_POWER_OFF);

        PCB_DDR_POWER(_DDR_POWER_OFF);

        PCB_DDR_POWER_RELEASE_TIME(_DDR_POWER_OFF_TIME);
    }
    else
    {
        // Group A power block power cut on
        if((ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT4) == _BIT4) || (ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT1) == _BIT1))
        {
            PCB_DDR_POWER(_DDR_POWER_ON);

            // Wait for DDR stable, can't delete
            ScalerTimerDelayXms(10);

            PCB_VCCK_OFF_POWER(_VCCK_OFF_POWER_ON);

            // Wait for 1.1V stable, can't delete
            ScalerTimerDelayXms(10);
        }
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
    }
    else
    {
        // Group C power block power cut on
        if((ScalerGetBit(P0_F1_VCCKOFF_CONTROL1, _BIT6) == _BIT6) || (ScalerGetBit(P6F_26_ADI_POWER_CTRL, _BIT1) == _BIT1))
        {
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
}

//--------------------------------------------------
// Description  : Group D0 Power on/off
// Input Value  : ON --> Group D0(Low Power) ; OFF --> Group D0 (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupD0PowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // D0 Strong power off
        ScalerSetBit(P6F_20_D0_POWER_CTRL, ~_BIT5, 0x00);

        // D0 Weak power off
        ScalerSetBit(P6F_20_D0_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Group D0 power block power cut on
        if((ScalerGetBit(P0_F1_VCCKOFF_CONTROL1, _BIT0) == _BIT0) || (ScalerGetBit(P6F_20_D0_POWER_CTRL, _BIT1) == _BIT1))
        {
            // Weak power on
            ScalerSetBit(P6F_20_D0_POWER_CTRL, ~_BIT4, _BIT4);

            // Wait for weak power on flag
            pData[0] = 50;

            while((ScalerGetBit(P6F_20_D0_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
            {
                DELAY_5US();
            }

            // Strong power on
            ScalerSetBit(P6F_20_D0_POWER_CTRL, ~_BIT5, _BIT5);

            // Wait for strong power on flag
            pData[0] = 50;

            while((ScalerGetBit(P6F_20_D0_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
            {
                DELAY_5US();
            }
        }
    }
}

//--------------------------------------------------
// Description  : Group D1 Power on/off
// Input Value  : ON --> Group D1(Low Power) ; OFF --> Group D1 (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupD1PowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // D1 Strong power off
        ScalerSetBit(P6F_21_D1_POWER_CTRL, ~_BIT5, 0x00);

        // D1 Weak power off
        ScalerSetBit(P6F_21_D1_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Group D1 power block power cut on
        if((ScalerGetBit(P0_F1_VCCKOFF_CONTROL1, _BIT1) == _BIT1) || (ScalerGetBit(P6F_21_D1_POWER_CTRL, _BIT1) == _BIT1))
        {
            // Weak power on
            ScalerSetBit(P6F_21_D1_POWER_CTRL, ~_BIT4, _BIT4);

            // Wait for weak power on flag
            pData[0] = 50;

            while((ScalerGetBit(P6F_21_D1_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
            {
                DELAY_5US();
            }

            // Strong power on
            ScalerSetBit(P6F_21_D1_POWER_CTRL, ~_BIT5, _BIT5);

            // Wait for strong power on flag
            pData[0] = 50;

            while((ScalerGetBit(P6F_21_D1_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
            {
                DELAY_5US();
            }
        }
    }
}

//--------------------------------------------------
// Description  : Group D2 Power on/off
// Input Value  : ON --> Group D2 (Low Power) ; OFF --> Group D2 (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupD2PowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // D2 Strong power off
        ScalerSetBit(P6F_22_D2_POWER_CTRL, ~_BIT5, 0x00);

        // D2 Weak power off
        ScalerSetBit(P6F_22_D2_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Group D2 power block power cut on
        if((ScalerGetBit(P0_F1_VCCKOFF_CONTROL1, _BIT2) == _BIT2) || (ScalerGetBit(P6F_22_D2_POWER_CTRL, _BIT1) == _BIT1))
        {
            // Weak power on
            ScalerSetBit(P6F_22_D2_POWER_CTRL, ~_BIT4, _BIT4);

            // Wait for weak power on flag
            pData[0] = 50;

            while((ScalerGetBit(P6F_22_D2_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
            {
                DELAY_5US();
            }

            // Strong power on
            ScalerSetBit(P6F_22_D2_POWER_CTRL, ~_BIT5, _BIT5);

            // Wait for strong power on flag
            pData[0] = 50;

            while((ScalerGetBit(P6F_22_D2_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
            {
                DELAY_5US();
            }
        }
    }
}

//--------------------------------------------------
// Description  : Group D3 Power on/off
// Input Value  : ON --> Group D3 (Low Power) ; OFF --> Group D3 (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupD3PowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // D3 Strong power off
        ScalerSetBit(P6F_23_D3_POWER_CTRL, ~_BIT5, 0x00);

        // D3 Weak power off
        ScalerSetBit(P6F_23_D3_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Group D3 power block power cut on
        if((ScalerGetBit(P0_F1_VCCKOFF_CONTROL1, _BIT3) == _BIT3) || (ScalerGetBit(P6F_23_D3_POWER_CTRL, _BIT1) == _BIT1))
        {
            // Weak power on
            ScalerSetBit(P6F_23_D3_POWER_CTRL, ~_BIT4, _BIT4);

            // Wait for weak power on flag
            pData[0] = 50;

            while((ScalerGetBit(P6F_23_D3_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
            {
                DELAY_5US();
            }

            // Strong power on
            ScalerSetBit(P6F_23_D3_POWER_CTRL, ~_BIT5, _BIT5);

            // Wait for strong power on flag
            pData[0] = 50;

            while((ScalerGetBit(P6F_23_D3_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
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
    //////////////////////// Pin Share Start /////////////////////////////////////

    PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON();

    ScalerPinsharePowerOnReset();

    //////////////////////// Pin Share End /////////////////////////////////////

    //////////////////////// VBO block start /////////////////////////////////////

#if(_PANEL_STYLE == _PANEL_VBO)
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
// Description  : Recover B Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverBGroupIsolationData(void)
{
    //////////////////////// Audio DAC block start ///////////////////////////////

    //////////////////////// Audio DAC block End /////////////////////////////////

}

//--------------------------------------------------
// Description  : Recover C Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverCGroupIsolationData(void)
{
    ScalerPowerRecoverADIGroupIsolationData();
}

//--------------------------------------------------
// Description  : Recover D Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverDGroupIsolationData(void)
{
    ScalerPowerRecoverHDMIRxGroupIsolationData();
}

//--------------------------------------------------
// Description  : Recover E Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverEGroupIsolationData(void)
{
    // Recover DPRx Group Power Cut Area
    ScalerPowerRecoverDPRxGroupIsolationData();
}

//--------------------------------------------------
// Description  : Recover ADI Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverADIGroupIsolationData(void)
{
    //////////////////////// GDI Tx (eDP)block start /////////////////////////////

#if(_DP_TX_SUPPORT == _ON)
    // AC_ON_TO_NORMAL or OFF_TO_NORMAL or PS_TO_NORMAL
    ScalerSyncDpTxPowerProc(_POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_PANEL_STYLE == _PANEL_DPTX)
    // Initial DPTx1
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    // Initial DPTx1
    ScalerDisplayDPTx1Initial();
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    // Initial DPTx2
    ScalerDisplayDPTx2Initial();
#endif

#endif // #if(_PANEL_STYLE == _PANEL_DPTX)

    //////////////////////// GDI Tx (eDP) block End //////////////////////////////

} // END of void ScalerPowerRecoverADIGroupIsolationData(void)
//--------------------------------------------------
// Description  : Recover DPRx Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverDPRxGroupIsolationData(void)
{
    //////////////////////// DPLL video GDI0~1 block start ///////////////////////

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    // Set R0' Available HW Mode
    ScalerSetBit(PB_1A_HDCP_IRQ, ~(_BIT5 | _BIT4), _BIT5);

    // Enable DP Link Integrity Enable
    ScalerSetBit(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

    // Restore HDCP Mode
    SET_DP_RX0_HDCP_MODE(GET_DP_RX0_HDCP_MODE_BACKUP());

    // DP Mac Clock Select to Xtal Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    if(ScalerGetBit(PB_20_HDCP_DEBUG, _BIT7) == _BIT7)
    {
        // HDCP R0 Calculate
        ScalerSetBit(PB_63_HDCP_OTHER, ~_BIT7, _BIT7);
        ScalerSetBit(PB_63_HDCP_OTHER, ~_BIT7, 0x00);
    }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Set Type Value = 1 for AES 1
    ScalerSetByte(PB_94_HDCP_TYPE_AES_1, 0x01);
#endif
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    // Set R0' Available HW Mode
    ScalerSetBit(PB0_1A_HDCP_IRQ, ~(_BIT5 | _BIT4), _BIT5);

    // Enable DP Link Integrity Enable
    ScalerSetBit(PB0_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

    // Restore HDCP Mode
    SET_DP_RX1_HDCP_MODE(GET_DP_RX1_HDCP_MODE_BACKUP());

    // DP Mac Clock Select to Xtal Clock
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    if(ScalerGetBit(PB0_20_HDCP_DEBUG, _BIT7) == _BIT7)
    {
        // HDCP R0 Calculate
        ScalerSetBit(PB0_63_HDCP_OTHER, ~_BIT7, _BIT7);
        ScalerSetBit(PB0_63_HDCP_OTHER, ~_BIT7, 0x00);
    }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Set Type Value = 1 for AES 1
    ScalerSetByte(PB0_94_HDCP_TYPE_AES_1, 0x01);
#endif
#endif

    //////////////////////// DPLL video GDI0~1 block End /////////////////////////


    //////////////////////// DPLL audio GDI0~1 block start ///////////////////////

    //////////////////////// DPLL audio GDI0~1 block End /////////////////////////


    //////////////////////// DPLL MST to SST0/1 block start //////////////////////

    //////////////////////// DPLL MST to SST0/1 block End /////////////////////////


    //////////////////////// HDMI2.0/DP1.2 Phy GDI0~1 block start /////////////////

    //////////////////////// HDMI2.0/DP1.2 Phy GDI0~1 block End ///////////////////


    //////////////////////// HDMI2.0/DP1.2 Phy DFE GDI2~5 block start /////////////

    //////////////////////// HDMI2.0/DP1.2 Phy DFE GDI2~5 block End ///////////////


    //////////////////////// Format Conversion block start ////////////////////////

    //////////////////////// Format Conversion block End //////////////////////////
} // END of void ScalerPowerRecoverDPRxGroupIsolationData(void)

//--------------------------------------------------
// Description  : Recover HDMIRx Group Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverHDMIRxGroupIsolationData(void)
{
    //////////////////////// DPLL video GDI2~5 block start ///////////////////////

    //////////////////////// DPLL video GDI2~5 block End /////////////////////////


    //////////////////////// DPLL audio GDI2~5 block start ///////////////////////

    //////////////////////// DPLL audio GDI2~5 block End /////////////////////////


    //////////////////////// HDMI1.4 Phy GDI2~5 block start //////////////////////

    //////////////////////// HDMI1.4 Phy GDI2~5 block End ////////////////////////


    //////////////////////// HDMI1.4 Phy DFE GDI2~5 block start //////////////////

    //////////////////////// HDMI1.4 Phy DFE GDI2~5 block End ////////////////////

}