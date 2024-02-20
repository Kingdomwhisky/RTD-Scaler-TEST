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
// ID Code      : ScalerDisplay.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY__

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
#if(_PANEL_STYLE == _PANEL_VBO)
BYTE code tDISPLAY_VBO_DRV_TABLE[48] =
{
    // Pre-emphasis->               0(0mV)               1(50mV)              2(100mV)             3(150mV)
    // VoltageSwing
    /*    0 (200mV)   */      0x00, 0x08, 0x22,    0x24, 0x08, 0x44,    0x25, 0x08, 0x66,    0x27, 0x08, 0xAA,
    /*    1 (250mV)   */      0x00, 0x08, 0x44,    0x05, 0x08, 0x66,    0x64, 0x08, 0xAA,    0x65, 0x0A, 0xAA,
    /*    2 (300mV)   */      0x00, 0x08, 0x66,    0x01, 0x08, 0xAA,    0x03, 0x0A, 0xAA,    0x61, 0x0C, 0xAA,
    /*    3 (350mV)   */      0x00, 0x08, 0xAA,    0x01, 0x0A, 0xAA,    0x60, 0x0C, 0xAA,    0x61, 0x0E, 0xAA,
};
#endif


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_VBO)
StructVboInfo g_stVboInfo =
{
    _FAIL,
    _FALSE,
    _DISABLE,
};
#endif // #if(_PANEL_STYLE == _PANEL_VBO)

#if(_FRC_SUPPORT == _ON)
StructDVCustomizedFreq g_stDVCustomizedFreq;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)
void ScalerDisplayLvdsTxDataSel(void);
void ScalerDisplayLvdsTxPortSwap(void);
#endif

#if(_PANEL_STYLE == _PANEL_VBO)
void ScalerDisplayVboMac(bit bOn);
void ScalerDisplayVboPhy(bit bOn);
void ScalerDisplayVboAnalogPhyConrol(bit bEnable);
void ScalerDisplayVboCdr2AlnLatency(void);

void ScalerDisplayVboHtpdnSetFwControl(bit bEnable);
void ScalerDisplayVboForceVideoOutput(bit bEnable);
void ScalerDisplayVboSetLocknInterrupt(bit bEnable);
void ScalerDisplayVboSetUnLocknInterrupt(bit bEnable);
void ScalerDisplayVboPollingHotPlug(WORD usNum);
void ScalerDisplayVboHtpdnHandler(void);
void ScalerDisplayVboLocknHandler(void);
void ScalerDisplayVboCtsFifoHandler(void);
bit ScalerDisplayVboLocknStatus(void);
void ScalerDisplayVboPanelSetFastOff(bit bEnable);
bit ScalerDisplayVboPanelFastOffCheck(void);
void ScalerDisplayVboPanelBacklightReTurnOn(void);
void ScalerDisplayVboIntHandler_EXINT0(void);
bit ScalerDisplayGetVboPowerStatus(void);
void ScalerDisplaySetVboPLLSSC(bit bDclkSpreadSpeed, BYTE ucSpreadRange);
void ScalerDisplayVboDrivingControl(BYTE ucDrvLane, BYTE ucEmpLane);
void ScalerDisplayVboInitialTable(void);
void ScalerDisplayVboPLL(bit bOn);
void ScalerDisplayVboPower(bit bOn);
void ScalerDisplayVboSetZ0(void);
#endif

BYTE ScalerDisplaySelectDVFMode(void);
void ScalerDisplaySetDVFreq(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Description  : LVDS TX Port output Data Selection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsTxDataSel(void)
{
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, 0x00);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port A Output Termination Enable (Analog Port B)
    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port A Output Termination Disable (Analog Port B)
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_B)

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, 0x00);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port B Output Termination Enable (Analog Port A)
    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port B Output Termination Disable (Analog Port A)
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_C)

    ScalerSetByte(_LVDS_TXCD_OUTPUT_DATA_PORT_ADDR, 0x00);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port C Output Termination Enable (Analog Port B)
    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port C Output Termination Disable (Analog Port B)
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_D)

    ScalerSetByte(_LVDS_TXCD_OUTPUT_DATA_PORT_ADDR, 0x00);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port D Output Termination Enable (Analog Port A)
    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port D Output Termination Disable (Analog Port A)
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x10));

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port AB Output Termination Enable
    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port AB Output Termination Disable
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

    ScalerSetByte(_LVDS_TXCD_OUTPUT_DATA_PORT_ADDR, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x10));

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port CD Output Termination Enable
    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port CD Output Termination Disable
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x32));
    ScalerSetByte(P39_03_LVDS_DISPLAY_CONV_CTRL2, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x23 : 0x10));

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port ABCD Output Termination Enable
    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port ABCD Output Termination Disable
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

#endif // #if(_LVDS_PORT_SEL == _LVDS_1_PORT_A)
}

//--------------------------------------------------
// Description  : LVDS TX Port output Data Swap Selection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsTxPortSwap(void)
{
    BYTE ucLvdsPortSwapIndex = 0;

    // Port AB Swap
    ucLvdsPortSwapIndex = ((_LVDS_PORT_AB_SWAP == _DISABLE) ? 0 : 4);

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, (((ScalerGetBit(P39_02_LVDS_DISPLAY_CONV_CTRL1, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> ucLvdsPortSwapIndex) | ((ScalerGetBit(P39_02_LVDS_DISPLAY_CONV_CTRL1, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << ucLvdsPortSwapIndex)));

    // Port CD Swap
    ucLvdsPortSwapIndex = ((_LVDS_PORT_CD_SWAP == _DISABLE) ? 0 : 4);

    ScalerSetByte(P39_03_LVDS_DISPLAY_CONV_CTRL2, (((ScalerGetBit(P39_03_LVDS_DISPLAY_CONV_CTRL2, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> ucLvdsPortSwapIndex) | ((ScalerGetBit(P39_03_LVDS_DISPLAY_CONV_CTRL2, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << ucLvdsPortSwapIndex)));

    // Port EF Swap
    ucLvdsPortSwapIndex = ((_LVDS_PORT_EF_SWAP == _DISABLE) ? 0 : 4);

    ScalerSetByte(P39_04_LVDS_DISPLAY_CONV_CTRL3, (((ScalerGetBit(P39_04_LVDS_DISPLAY_CONV_CTRL3, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> ucLvdsPortSwapIndex) | ((ScalerGetBit(P39_04_LVDS_DISPLAY_CONV_CTRL3, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << ucLvdsPortSwapIndex)));

    // Port GH Swap
    ucLvdsPortSwapIndex = ((_LVDS_PORT_GH_SWAP == _DISABLE) ? 0 : 4);

    ScalerSetByte(P39_05_LVDS_DISPLAY_CONV_CTRL4, (((ScalerGetBit(P39_05_LVDS_DISPLAY_CONV_CTRL4, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> ucLvdsPortSwapIndex) | ((ScalerGetBit(P39_05_LVDS_DISPLAY_CONV_CTRL4, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << ucLvdsPortSwapIndex)));
}
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

#if(_PANEL_STYLE == _PANEL_VBO)
//--------------------------------------------------
// Description  : Settings for Vbyone MAC
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboMac(bit bOn)
{
    BYTE ucCount = 0;

    if(bOn == _ON)
    {
        // Set Vby1 MAC
        ScalerSetBit(P38_0A_TRANSMIT_CONTROL_H1, ~_BIT7, _BIT7);

        // Check Vby1 Cts Fifo Status Twice
        for(ucCount = 0; ucCount < 2; ucCount++)
        {
            ScalerTimerDelayXms(2);

            // Check Vbyone Cts Fifo Condiction
            if(ScalerGetBit(P38_17_CTS_FIFO_L, (_BIT1 | _BIT0)) != 0x00)
            {
                // Cts Fifo Handler
                ScalerDisplayVboCtsFifoHandler();
            }
        }
    }
    else
    {
        // Reset Vby1 MAC
        ScalerSetBit(P38_0A_TRANSMIT_CONTROL_H1, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Settings for Vbyone Digital Phy
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPhy(bit bOn)
{
    if(bOn == _ON)
    {
        // Set Vby1 Digital Phy
        ScalerSetBit(P38_00_VIDEO_FORMAT_H, ~_BIT4, _BIT4);

        // Enable Digital Phy output
        ScalerSetByte(P38_8E_PHY0_TXBIST_02_H1, 0xFF);
    }
    else
    {
        // Disable Digital Phy output
        ScalerSetByte(P38_8E_PHY0_TXBIST_02_H1, 0x00);

        // Reset Vby1 Digital Phy
        ScalerSetBit(P38_00_VIDEO_FORMAT_H, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Control Vby1 Phy
// Input Value  : bit bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboAnalogPhyConrol(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Vby1 Power on
        ScalerDisplayVboPower(_ON);

        // Vby1 PLL on
        ScalerDisplayVboPLL(_ON);

        // Set Vby1 MAC
        ScalerDisplayVboMac(_ON);

        // Set Vby1 Digital Phy, Enable Output
        ScalerDisplayVboPhy(_ON);
    }
    else
    {
        // Reset Vby1 Digital Phy, disable Output
        ScalerDisplayVboPhy(_OFF);

        // Reset Vby1 MAC
        ScalerDisplayVboMac(_OFF);

        // Vby1 PLL off
        ScalerDisplayVboPLL(_OFF);

        // Vby1 Power off
        ScalerDisplayVboPower(_OFF);
    }
}

//--------------------------------------------------
// Description  : Vbyone Latency between CDR and ALN pattern
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboCdr2AlnLatency(void)
{
    ScalerSetBit(P38_0A_TRANSMIT_CONTROL_H1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (((_CDR_TRANSFER_ALN_LATENCY * 27) >> 16) & 0x3F));
    ScalerSetByte(P38_0B_TRANSMIT_CONTROL_L2, (((_CDR_TRANSFER_ALN_LATENCY * 27) >> 8) & 0xFF));
    ScalerSetByte(P38_0C_TRANSMIT_CONTROL_L1, ((_CDR_TRANSFER_ALN_LATENCY * 27) & 0xFF));
}

//--------------------------------------------------
// Description  : Vbyone HTPDN Interrupt Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboHtpdnSetFwControl(bit bEnable)
{
    // Write Clear the HTDPN and LOCKN Flag
    ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    if(bEnable == _ENABLE)
    {
        // Set HTPDN Interrupt Disable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

        // Set HTPDN Pull High
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT1, _BIT1);

        // Set Vby1 HTPDN controlled by F/W
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT7, _BIT7);
    }
    else
    {
        // Set HTPDN Interrupt Enable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT6);

        // Set Vby1 HTPDN controlled by H/W
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Vbyone Video Output Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboForceVideoOutput(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set Vby1 LOCKN controlled by F/W
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT6, _BIT6);

        // Set LOCKN Pull Low
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT0, 0x00);
    }
    else
    {
        // Disable Detect Lock Status
        ScalerDisplayVboSetLocknInterrupt(_DISABLE);

        // Disable Detect UnLock Stauts
        ScalerDisplayVboSetUnLocknInterrupt(_DISABLE);

        // Set LOCKN Pull High
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT0, _BIT0);

        // Set Vby1 LOCKN controlled by H/W
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT6, 0x00);

        // Clear all flag
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));

        // LOCKN status initial: Fail
        g_stVboInfo.b1VboLocknStatus = _FAIL;

        // LOCKN Ripped off status initial: False
        g_stVboInfo.b1VboLocknRippedOff = _FALSE;

        // Set Panel Fast Off Disable
        g_stVboInfo.b1PanelFastOffStatus = _DISABLE;
    }
}

//--------------------------------------------------
// Description  : Vbyone LOCKN Interrupt Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboSetLocknInterrupt(bit bEnable)
{
    // Write Clear the Lock Flag
    ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT5);

    if(bEnable == _ENABLE)
    {
        // Set LOCKN Interrupt Enable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT7);
    }
    else
    {
        // Set LOCKN Interrupt Disable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : Vbyone LOCKN_FAIL Interrupt Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboSetUnLocknInterrupt(bit bEnable)
{
    // Write Clear the UnLock Flag
    ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT1);

    if(bEnable == _ENABLE)
    {
        // Set LOCKN_FAIL Interrupt Enable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), _BIT3);
    }

    else
    {
        // Set LOCKN_FAIL Interrupt Disable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : Wait for Vbyone Htpdn
// Input Value  : WORD usNum
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPollingHotPlug(WORD usNum)
{
    ScalerTimerPollingFlagProc(usNum, P38_28_VBY1_IRQ_CTRL, _BIT4, _TRUE);
}

//--------------------------------------------------
// Description  : Vbyone Htpdn Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboHtpdnHandler(void)
{
    if(ScalerGetBit(P38_28_VBY1_IRQ_CTRL, _BIT4) != _BIT4)
    {
        // Set HTPDN Interrupt Disable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

        // Set UnLOCKN Status: None
        g_stVboInfo.b1VboLocknRippedOff = _FALSE;

        // Set Vby1 HTPDN controlled by F/W
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT7, _BIT7);

        // Set HTPDN Pull Low
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT1, 0x00);

        // Set LOCKN Interrupt Enable
        ScalerDisplayVboSetLocknInterrupt(_ENABLE);
    }

    // Set Detect UnLock Interrupt Enable
    ScalerDisplayVboSetUnLocknInterrupt(_ENABLE);
}

//--------------------------------------------------
// Description  : Vbyone Lockn Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboLocknHandler(void)
{
    // Check Vbyone Lockn status success
    if(ScalerDisplayVboLocknStatus() != _SUCCESS)
    {
        // Force transfer to ALN pattern, and enable video output
        ScalerDisplayVboForceVideoOutput(_ENABLE);

        // Wait Delay time for ALN patern
        ScalerTimerDelayXms(80);
    }
}

//--------------------------------------------------
// Description  : Vbyone CTS-FIFO Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboCtsFifoHandler(void)
{
    BYTE ucCount = 0;

    // Set CTS FIFO Initial Address For Reading
    ScalerSetBit(P38_15_CTS_FIFO_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Set CTS FIFO PLL Tracking Boundary
    ScalerSetByte(P38_16_CTS_FIFO_M, 0x00);

    // Toggle Vby1 MAC
    ScalerSetBit(P38_0A_TRANSMIT_CONTROL_H1, ~_BIT7, 0x00);
    ScalerTimerDelayXms(2);
    ScalerSetBit(P38_0A_TRANSMIT_CONTROL_H1, ~_BIT7, _BIT7);

    // Toggle Vby1 Cts Fifo 4 Times
    for(ucCount = 0; ucCount < 4; ucCount++)
    {
        ScalerSetBit(P38_17_CTS_FIFO_L, ~_BIT3, 0x00);
        ScalerTimerDelayXms(2);

        ScalerSetBit(P38_17_CTS_FIFO_L, ~_BIT3, _BIT3);
        ScalerTimerDelayXms(2);
    }

    // Reset CTS FIFO PLL Tracking Boundary
    ScalerSetByte(P38_16_CTS_FIFO_M, 0x11);
}

//--------------------------------------------------
// Description  : Vbyone LOCKN Check
// Input Value  : None
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
bit ScalerDisplayVboLocknStatus(void)
{
    return g_stVboInfo.b1VboLocknStatus;
}

//--------------------------------------------------
// Description  : Vbyone Panel Fast Off Setting
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPanelSetFastOff(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        g_stVboInfo.b1PanelFastOffStatus = _ENABLE;
    }
    else
    {
        g_stVboInfo.b1PanelFastOffStatus = _DISABLE;
    }
}

//--------------------------------------------------
// Description  : Vbyone Panel Fast Off Check
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerDisplayVboPanelFastOffCheck(void)
{
    return g_stVboInfo.b1PanelFastOffStatus;
}

//--------------------------------------------------
// Description  : Vbyone LOCKN Re Lock, Re-Turn on Backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPanelBacklightReTurnOn(void)
{
    // When CDR Re-Lock: Backlight Re-Turn on
    if(g_stVboInfo.b1VboLocknRippedOff == _TRUE)
    {
        if((ScalerDisplayVboLocknStatus() == _SUCCESS) || (ScalerGetBit(P38_0D_TRANSMIT_STATUS, _BIT1) == _BIT1))
        {
            ScalerTimerDelayXms(_PANEL_POWER_ON_T3);

            // Check Vby1 ALN_En flag, when Vby1 CDR locked, this flag will be triggered
            if(ScalerGetBit(P38_0D_TRANSMIT_STATUS, _BIT1) == _BIT1)
            {
                // Backlight Turn On
                PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_ON);

                // Set CDR re-lock Status: None
                g_stVboInfo.b1VboLocknRippedOff = _FALSE;

                // Set LOCKN Status: Success
                g_stVboInfo.b1VboLocknStatus = _SUCCESS;
            }
            else
            {
#if(_PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING == _ON)
                // Backlight Turn Off
                PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);
#endif
                // Set LOCKN Status: Fail
                g_stVboInfo.b1VboLocknStatus = _FAIL;
            }
        }
#if(_PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING == _ON)
        else
        {
            // Backlight Turn Off
            PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);

            // Set LOCKN Status: Fail
            g_stVboInfo.b1VboLocknStatus = _FAIL;
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Vbyone Interrupt Handler: HTPDN, LOCKN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboIntHandler_EXINT0(void) using 1
{
    // HTPDN: Plug-In Flag
    if(ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT6 | _BIT4)) == (_BIT6 | _BIT4))
    {
        // Set LOCKN Interrupt Enable
        ScalerSetBit_EXINT(P38_28_VBY1_IRQ_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT7);

        // Disable HPTDN Interrupt
        ScalerSetBit_EXINT(P38_28_VBY1_IRQ_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

        // Set UnLOCKN Status: None
        g_stVboInfo.b1VboLocknRippedOff = _FALSE;
    }

    // LOCKN: Glitch / Unlock / Lock
    if((ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1)) &&
       (ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5)))
    {
        // Write Clear the Lock / UnLock Flag
        ScalerSetBit_EXINT(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

        // Set LOCKN Status: Fail
        g_stVboInfo.b1VboLocknStatus = _SUCCESS;
    }
    else if(ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1))
    {
        // Write Clear the UnLock Flag
        ScalerSetBit_EXINT(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT1);

#if(_PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING == _OFF)
        // Backlight Turn Off when CDR unlock
        PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);
#endif

        // Set UnLOCKN Status: Ripped off
        g_stVboInfo.b1VboLocknRippedOff = _TRUE;

        // Set LOCKN Status: Fail
        g_stVboInfo.b1VboLocknStatus = _FAIL;
    }
    else if(ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5))
    {
        // Write Clear the Lock Flag
        ScalerSetBit_EXINT(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT5);

        // Set LOCKN Status: Success
        g_stVboInfo.b1VboLocknStatus = _SUCCESS;
    }

    // LOCKN: Un-LOCK Flag
    // HTPDN: Un-Plug Flag
    // if((ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1)) || (ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0)))
}

//--------------------------------------------------
// Description  : Get Vby1 Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerDisplayGetVboPowerStatus(void)
{
    return (bit)(ScalerGetBit(P38_A0_DPTX_PHY_CTRL0, _BIT4));
}

//--------------------------------------------------
// Description  : Adjust Vbo Ref DPLL Spread Spectrum
// Input Value  : Spread Spectrum Range
// Output Value : None
//--------------------------------------------------
void ScalerDisplaySetVboPLLSSC(bit bDclkSpreadSpeed, BYTE ucSpreadRange)
{
    bDclkSpreadSpeed = bDclkSpreadSpeed;

    // Disable Dpll Dclk Spread Range
    ScalerSetBit(P1_C6_DCLK_SPREAD_SPECTRUM, ~0xF0, 0x00);

    // Set Dpll Dclk Double Buffer
    ScalerSetBit(P1_C6_DCLK_SPREAD_SPECTRUM, ~_BIT2, _BIT2);

    if(ucSpreadRange != 0x00)
    {
        PDATA_WORD(0) = (WORD)((ScalerGetBit(P38_DC_DPTX_CMU12, 0x1F) << 4) | (ScalerGetByte(P38_DD_DPTX_CMU13) >> 4));
        PDATA_WORD(1) = (WORD)((ScalerGetBit(P38_DD_DPTX_CMU13, 0x0F) << 8) | ScalerGetByte(P38_DE_DPTX_CMU14));

        // Calculate Spread Spectrum FMDIV: 30kHz
        PDATA_WORD(3) = (((_EXT_XTAL / 31) + 2) & 0xFFFC);

        // Calculate SSC
        PDATA_WORD(2) = ((((DWORD)PDATA_WORD(0) + 4) * 4096 + PDATA_WORD(1))) * 16 / 100 / PDATA_WORD(3) / 15 * ucSpreadRange;

        // Set Spread Spectrum FMDIV: 30kHz
        ScalerSetByte(P38_E0_DPTX_CMU16, (BYTE)(PDATA_WORD(3) >> 8));
        ScalerSetByte(P38_E1_DPTX_CMU17, (BYTE)PDATA_WORD(3));

        // Set Spread Spectrum Range
        ScalerSetByte(P38_E2_DPTX_CMU18, (BYTE)(PDATA_WORD(2) >> 8));
        ScalerSetByte(P38_E3_DPTX_CMU19, (BYTE)PDATA_WORD(2));

        // [5] 1: Enable SSC, 0: disable
        // [4] 0: 1st Order SDM, 1:2nd Order SDM
        // [3] 0: Triangular wave, 1: Square wave
        ScalerSetBit(P38_D5_DPTX_CMU5, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
    }
    else
    {
        // Disable SSC
        ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  : Setting for Vbyone driving control
// Input Value  : Driving current and Pre-emphasis for Vby1 Data Lane
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboDrivingControl(BYTE ucDrvLane, BYTE ucEmpLane)
{
    BYTE ucIndex = 0x00;
    BYTE *pucTable = 0x00;

    ucIndex = (ucDrvLane * 4 + ucEmpLane) * 3;

    pucTable = tDISPLAY_VBO_DRV_TABLE;

    // De-emphasis [9:8]
    ScalerSetBit(P38_A8_DPTX_DEEMP_EN_LANE7_4H, ~(_BIT7 | _BIT6), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 6));
    ScalerSetBit(P38_A8_DPTX_DEEMP_EN_LANE7_4H, ~(_BIT5 | _BIT4), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 4));
    ScalerSetBit(P38_A8_DPTX_DEEMP_EN_LANE7_4H, ~(_BIT3 | _BIT2), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 2));
    ScalerSetBit(P38_A8_DPTX_DEEMP_EN_LANE7_4H, ~(_BIT1 | _BIT0), (((pucTable[ucIndex + 1] & 0xF0) >> 4)));

    ScalerSetBit(P38_AD_DPTX_DEEMP_EN_LANE3_0H, ~(_BIT7 | _BIT6), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 6));
    ScalerSetBit(P38_AD_DPTX_DEEMP_EN_LANE3_0H, ~(_BIT5 | _BIT4), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 4));
    ScalerSetBit(P38_AD_DPTX_DEEMP_EN_LANE3_0H, ~(_BIT3 | _BIT2), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 2));
    ScalerSetBit(P38_AD_DPTX_DEEMP_EN_LANE3_0H, ~(_BIT1 | _BIT0), (((pucTable[ucIndex + 1] & 0xF0) >> 4)));

    // De-emphasis [7:0]
    ScalerSetByte(P38_A9_DPTX_DEEMP_EN_LANE7L, pucTable[ucIndex + 0]);
    ScalerSetByte(P38_AA_DPTX_DEEMP_EN_LANE6L, pucTable[ucIndex + 0]);
    ScalerSetByte(P38_AB_DPTX_DEEMP_EN_LANE5L, pucTable[ucIndex + 0]);
    ScalerSetByte(P38_AC_DPTX_DEEMP_EN_LANE4L, pucTable[ucIndex + 0]);

    ScalerSetByte(P38_AE_DPTX_DEEMP_EN_LANE3L, pucTable[ucIndex + 0]);
    ScalerSetByte(P38_AF_DPTX_DEEMP_EN_LANE2L, pucTable[ucIndex + 0]);
    ScalerSetByte(P38_B0_DPTX_DEEMP_EN_LANE1L, pucTable[ucIndex + 0]);
    ScalerSetByte(P38_B1_DPTX_DEEMP_EN_LANE0L, pucTable[ucIndex + 0]);

    // Data [3:0]
    ScalerSetBit(P38_B4_DPTX_DRV_DAC_DAT_LANE7_6, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));
    ScalerSetBit(P38_B4_DPTX_DRV_DAC_DAT_LANE7_6, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));
    ScalerSetBit(P38_B5_DPTX_DRV_DAC_DAT_LANE5_4, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));
    ScalerSetBit(P38_B5_DPTX_DRV_DAC_DAT_LANE5_4, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));

    ScalerSetBit(P38_B6_DPTX_DRV_DAC_DAT_LANE3_2, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));
    ScalerSetBit(P38_B6_DPTX_DRV_DAC_DAT_LANE3_2, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));
    ScalerSetBit(P38_B7_DPTX_DRV_DAC_DAT_LANE1_0, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));
    ScalerSetBit(P38_B7_DPTX_DRV_DAC_DAT_LANE1_0, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));

    // Post1 [3:0]
    ScalerSetBit(P38_BC_DPTX_DRV_DAC_POST1_LANE7_6, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));
    ScalerSetBit(P38_BC_DPTX_DRV_DAC_POST1_LANE7_6, ~0x0F, ((pucTable[ucIndex + 2] & 0xF0) >> 4));
    ScalerSetBit(P38_BD_DPTX_DRV_DAC_POST1_LANE5_4, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));
    ScalerSetBit(P38_BD_DPTX_DRV_DAC_POST1_LANE5_4, ~0x0F, ((pucTable[ucIndex + 2] & 0xF0) >> 4));

    ScalerSetBit(P38_BE_DPTX_DRV_DAC_POST1_LANE3_2, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));
    ScalerSetBit(P38_BE_DPTX_DRV_DAC_POST1_LANE3_2, ~0x0F, ((pucTable[ucIndex + 2] & 0xF0) >> 4));
    ScalerSetBit(P38_BF_DPTX_DRV_DAC_POST1_LANE1_0, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));
    ScalerSetBit(P38_BF_DPTX_DRV_DAC_POST1_LANE1_0, ~0x0F, ((pucTable[ucIndex + 2] & 0xF0) >> 4));

    // Post0 [3:0]
    ScalerSetBit(P38_B8_DPTX_DRV_DAC_POST0_LANE7_6, ~0xF0, ((pucTable[ucIndex + 2] & 0x0F) << 4));
    ScalerSetBit(P38_B8_DPTX_DRV_DAC_POST0_LANE7_6, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));
    ScalerSetBit(P38_B9_DPTX_DRV_DAC_POST0_LANE5_4, ~0xF0, ((pucTable[ucIndex + 2] & 0x0F) << 4));
    ScalerSetBit(P38_B9_DPTX_DRV_DAC_POST0_LANE5_4, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));

    ScalerSetBit(P38_BA_DPTX_DRV_DAC_POST0_LANE3_2, ~0xF0, ((pucTable[ucIndex + 2] & 0x0F) << 4));
    ScalerSetBit(P38_BA_DPTX_DRV_DAC_POST0_LANE3_2, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));
    ScalerSetBit(P38_BB_DPTX_DRV_DAC_POST0_LANE1_0, ~0xF0, ((pucTable[ucIndex + 2] & 0x0F) << 4));
    ScalerSetBit(P38_BB_DPTX_DRV_DAC_POST0_LANE1_0, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));
}

//--------------------------------------------------
// Description  : Initial Settings for Vbyone Interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboInitialTable(void)
{
    // Set DISP mode is Vby1
    ScalerSetBit(P39_00_LVDS_DISP_TYPE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Set Link Clk Source
    ScalerSetBit(P38_2A_VBY1_LCLK_SOURCE_CTRL, ~_BIT0, _BIT0);

    // Set Vby1 HS Control
    ScalerSetBit(P38_17_CTS_FIFO_L, ~(_BIT7 | _BIT1 | _BIT0), ((_VBO_HS_CONTROL & _BIT0) << 7));

    // Set Vby1 Display Data Bit Resolution
    ScalerSetBit(P38_00_VIDEO_FORMAT_H, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _VBO_BIT_MODE);

    // Set Vby1 Display Data Lane
    ScalerSetByte(P38_03_LANE_STATUS_H, (_BIT6 | _VBO_OUTPUT_PORT));

    // Set Vby1 Display Type
    ScalerSetByte(P38_04_LANE_STATUS_L, ((_VBO_PANEL_SECTION << 3) | _VBO_BYTE_MODE));

    // Set Vby1 MLSwap and LaneSwap Control
    ScalerSetBit(P38_27_VBY1_FW_CTRL, ~(_BIT5 | _BIT4), ((_VBO_ML_SWAP << 5) | (_VBO_LANE_SWAP << 4)));

    // Set Vby1 Transmit Control
    ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~(_BIT5 | _BIT4), (_BIT5 | (_VBO_VIDEO_TRANSFER_TYPE << 4)));
    ScalerSetBit(P38_0A_TRANSMIT_CONTROL_H1, ~_BIT6, 0x00);
    ScalerSetBit(P38_0D_TRANSMIT_STATUS, ~_BIT7, _BIT7);
    ScalerSetBit(P38_0E_THREE_FLAG, ~(_BIT2 | _BIT1 | _BIT0), ((_VBO_VS_CONTROL << 1) | ((_VBO_HS_CONTROL & _BIT1) >> 1)));

    // Set ASY FIFO PLL Tracking Boundary
    ScalerSetBit(P38_08_PLL_TRACKING, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Set CTS FIFO Initial Address For Reading
    ScalerSetBit(P38_15_CTS_FIFO_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // Set CTS FIFO PLL Tracking Boundary
    ScalerSetByte(P38_16_CTS_FIFO_M, 0x11);

    // Set Vby1 Digital Phy Initial
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set Vby1 PN Swap Control
#if(_VBO_PN_SWAP == _ENABLE)
    ScalerSetByte(P38_80_DPTX_PN_SWAP1, 0xFF);
#else
    ScalerSetByte(P38_80_DPTX_PN_SWAP1, 0x00);
#endif // End of #if(_VBO_PN_SWAP == _ENABLE)

    // Disable Vby1 Digital Output, Force Vby1 Output DC Level Signal
    ScalerSetByte(P38_8E_PHY0_TXBIST_02_H1, 0x00);

    // Set HTPDN control by F/W, pull high
    ScalerDisplayVboHtpdnSetFwControl(_ENABLE);

    // Reset Vby1 Digital Phy, disable Output
    ScalerDisplayVboPhy(_OFF);

    // Reset Vby1 MAC
    ScalerDisplayVboMac(_OFF);

    // Set Vby1 Z0
    ScalerDisplayVboSetZ0();

    // Set Vby1 Driving Control
    ScalerDisplayVboDrivingControl(_VBO_LANE_DRIV_CONTROL, _VBO_PRE_EMPHASIS_CONTROL);

    // Set Vby1 CDR to ALN Latency Control
    ScalerDisplayVboCdr2AlnLatency();

    // LOCKN status initial: Fail
    g_stVboInfo.b1VboLocknStatus = _FAIL;

    // LOCKN Ripped off status initial: False
    g_stVboInfo.b1VboLocknRippedOff = _FALSE;

    // Set Panel Fast Off Disable
    g_stVboInfo.b1PanelFastOffStatus = _DISABLE;
}

//--------------------------------------------------
// Description  : Vbyone PLL Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPLL(bit bOn)
{
    if(bOn == _ON)
    {
        // Power Up DPLL CLK to Vby1
        ScalerSetBit(P1_DC_DCLK_GATED_CTRL2, ~_BIT1, _BIT1);

        // Power Up Vby1 PLL for LCLK
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT6, _BIT6);
    }
    else
    {
        // Power Down Vby1 PLL for LCLK
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT6, 0x00);

        // Disable DPLL CLK to Vby1
        ScalerSetBit(P1_DC_DCLK_GATED_CTRL2, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Vbyone Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPower(bit bOn)
{
    if(bOn == _ON)
    {
        // Disable Weakly Pull Down
        ScalerSetByte(P38_C1_DPTX_RCVDET_BIAS_PULLDN1, 0x00);

        // Power Up Vby1 Digital Block: reg_en
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT7, _BIT7);

        // Power Up Vby1 Analog Block
#if(_VBO_OUTPUT_PORT == _VBO_1_DATA_LANE)

        // Lane:0 power on
        ScalerSetByte(P38_A1_DPTX_PHY_CTRL1, _BIT0);

#elif(_VBO_OUTPUT_PORT == _VBO_2_DATA_LANE)

        // Lane:0-1 power on
        ScalerSetByte(P38_A1_DPTX_PHY_CTRL1, (_BIT1 | _BIT0));

#elif(_VBO_OUTPUT_PORT == _VBO_4_DATA_LANE)

        // Lane:0-3 power on
        ScalerSetByte(P38_A1_DPTX_PHY_CTRL1, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

#else   // #elif(_VBO_OUTPUT_PORT == _VBO_8_DATA_LANE)

        // Lane:0-7 power on
        ScalerSetByte(P38_A1_DPTX_PHY_CTRL1, 0xFF);

#endif  // End of #if(_VBO_OUTPUT_PORT == _VBO_1_DATA_LANE)
    }
    else
    {
        // Power Down Vby1 Analog Block
        ScalerSetByte(P38_A1_DPTX_PHY_CTRL1, 0x00);

        // Power Down Vby1 Digital Block
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT7, 0x00);

        // Enable Weakly Pull Down
        ScalerSetByte(P38_C1_DPTX_RCVDET_BIAS_PULLDN1, 0xFF);
    }
}

//--------------------------------------------------
// Description  : Settings for Vbyone Z0 Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboSetZ0(void)
{
    // Set Vby1 Z0 Value
    ScalerSetByte(P38_CC_DPTX_Z0_LANE7_6, 0x88);
    ScalerSetByte(P38_CD_DPTX_Z0_LANE5_4, 0x88);
    ScalerSetByte(P38_CE_DPTX_Z0_LANE3_2, 0x88);
    ScalerSetByte(P38_CF_DPTX_Z0_LANE1_0, 0x88);
}

#endif // End of #if(_PANEL_STYLE == _PANEL_VBO)

//--------------------------------------------------
// Description  : Set display DVF mode by V freq.
// Input Value  : stDVCustomizedFreq --> custim V freq. range
// Output Value : None
//--------------------------------------------------
BYTE ScalerDisplaySelectDVFMode(void)
{
#if(_FRC_SUPPORT == _ON)
#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        return _1_IVF;
    }
    else
#endif
    {
        if(g_stDVCustomizedFreq.b1FORCETOFREERUN == _ENABLE)
        {
            return _PANEL_TYP_FRAME_RATE_FREE_RUN;
        }
        else
        {
            WORD usMaxFreqMargin = g_stDVCustomizedFreq.usMaxFreq + _FRAME_SYNC_MARGIN;
            WORD usMinFreqMargin = g_stDVCustomizedFreq.usMinFreq - _FRAME_SYNC_MARGIN;

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
            StructRtkAdvMbrPanelInfo stPanelInfo;
            memset(&stPanelInfo, 0, sizeof(StructRtkAdvMbrPanelInfo));

            stPanelInfo.usMaxFreq = g_stDVCustomizedFreq.usMaxFreq;
            stPanelInfo.usMinFreq = g_stDVCustomizedFreq.usMinFreq;
            stPanelInfo.ucFrameSyncMargin = _FRAME_SYNC_MARGIN;
            stPanelInfo.ulPixelClock = _PANEL_PIXEL_CLOCK_KHZ;
            stPanelInfo.ulPixelClockMax = _PANEL_PIXEL_CLOCK_MAX_SPREAD;
            stPanelInfo.ulPixelClockMin = _PANEL_PIXEL_CLOCK_MIN_SPREAD;

            ScalerMbrUpdateRtkAdvMbrStatus(GET_MDOMAIN_INPUT_VFREQ(), &stPanelInfo);
            DebugMessageScaler("MBR: GET_MDOMAIN_INPUT_VFREQ", ScalerMbrGetAdvMbrStatus());
#endif

            if((g_stMDomainInputData.usVFreq <= usMaxFreqMargin) &&
               (g_stMDomainInputData.usVFreq >= usMinFreqMargin))
            {
                return _1_IVF;
            }
            else
            {
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if((_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_II) && (_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
                if(ScalerRotationCheckStatus() == _TRUE)
                {
#if(_MN_FRAMESYNC_FORCE_TO_FREERUN == _OFF)
                    if((g_stMDomainInputData.usVFreq <= (usMaxFreqMargin * 5 / 4)) &&
                       (g_stMDomainInputData.usVFreq >= (usMinFreqMargin * 5 / 4))) // DVF = 5 * IVF / 4
                    {
                        return _5_4_IVF;
                    }
                    else if((g_stMDomainInputData.usVFreq <= (usMaxFreqMargin * 6 / 5)) &&
                            (g_stMDomainInputData.usVFreq >= (usMinFreqMargin * 6 / 5))) // DVF = 6 * IVF / 5
                    {
                        return _6_5_IVF;
                    }
                    else
#endif
                    {
                        return _PANEL_TYP_FRAME_RATE_FREE_RUN;
                    }
                }
                else
#endif
#endif
                {
#if(_MN_FRAMESYNC_FORCE_TO_FREERUN == _OFF)
                    if((g_stMDomainInputData.usVFreq <= (usMaxFreqMargin / 2)) &&
                       (g_stMDomainInputData.usVFreq >= (usMinFreqMargin / 2))) // DVF = 2 * IVF
                    {
                        // For 1080p_30
                        return _2_IVF;
                    }
                    else if((g_stMDomainInputData.usVFreq <= (usMaxFreqMargin * 2 / 5)) &&
                            (g_stMDomainInputData.usVFreq >= (usMinFreqMargin * 2 / 5))) // DVF = 2.5 * IVF
                    {
                        // For 1080p_25, 1080p_24
                        return _2_5_IVF;
                    }
                    else if((g_stMDomainInputData.usVFreq <= (usMaxFreqMargin / 3)) &&
                            (g_stMDomainInputData.usVFreq >= (usMinFreqMargin / 3))) // DVF = 3 * IVF
                    {
                        return _3_IVF;
                    }
                    else
#endif
                    {
                        return _PANEL_TYP_FRAME_RATE_FREE_RUN;
                    }
                }
            }
        }
    }
#else // else of #if(_FRC_SUPPORT == _ON)

    return _1_IVF;

#endif // End of #if(_FRC_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Set DVfreq.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplaySetDVFreq(void)
{
    switch(GET_MEMORY_DVF_SELECT())
    {
        case _1_IVF:
            g_usDVFreq = g_stMDomainInputData.usVFreq;
            break;

#if(_FRC_SUPPORT == _ON)
        case _2_IVF:
            g_usDVFreq = 2 * g_stMDomainInputData.usVFreq;
            break;

        case _3_IVF:
            g_usDVFreq = 3 * g_stMDomainInputData.usVFreq;
            break;

        case _5_4_IVF:
            g_usDVFreq = 4 * g_stMDomainInputData.usVFreq / 5;
            break;

        case _6_5_IVF:
            g_usDVFreq = 5 * g_stMDomainInputData.usVFreq / 6;
            break;

        case _2_5_IVF:
            g_usDVFreq = 5 * g_stMDomainInputData.usVFreq / 2;
            break;

        case _PANEL_TYP_FRAME_RATE_FREE_RUN:
            g_usDVFreq = g_stDVCustomizedFreq.usTypFreq;
            break;
#endif
        default:
            g_usDVFreq = g_stMDomainInputData.usVFreq;
            break;
    }
}

