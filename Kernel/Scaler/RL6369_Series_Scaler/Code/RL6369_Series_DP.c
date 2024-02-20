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
// ID Code      : RL6369_Series_DP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_DP_SUPPORT == _ON)

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
void ScalerDpSecDataReset(BYTE ucInputPort);
void ScalerDpTimerEventProc(EnumScalerTimerEventID enumEventID);
void ScalerDpPowerSwitch(EnumPowerAction enumPowerAction);

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
void ScalerDpEmbeddedSwitchSetting(BYTE ucInputPort);
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Sec Data Reset
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpSecDataReset(BYTE ucInputPort)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource() == _DIGITAL_AUDIO)
#endif
    {
        switch(ucInputPort)
        {
            case _D0_INPUT_PORT:
            case _D1_INPUT_PORT:
            case _D2_INPUT_PORT:

                ScalerDpRx0SecDataBlockReset();
                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Handle DP Related Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerDpTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED:
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED:
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX2_HOTPLUG_ASSERTED:
#endif
        ScalerDpRx0SetHotPlugEvent(_DP_HPD_ASSERTED);
        break;

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT:
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT:
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT:
#endif
        if(ScalerDpRx0HdcpReAuthStatusCheck() == _FALSE)
        {
            DebugMessageRx0("7. DP HDCP Long HPD", 0);
            ScalerDpRx0SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
        }

        break;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX0_LONG_HOTPLUG_EVENT:
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX1_LONG_HOTPLUG_EVENT:
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX2_LONG_HOTPLUG_EVENT:
#endif
        DebugMessageRx0("7. DP Long HPD", 0);
        ScalerDpRx0SetHotPlugEvent(_DP_LONG_HPD_EVENT);

        break;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ:
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ:
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ:
#endif
        ScalerDpRx0LinkStatusIRQ();
        break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check DP Into Power Saving
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPowerSwitch(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            SET_DP_DC_OFF_HPD_TOGGLE_FLAG();

#if((_DP_HDMI_COMPATIBLE_MODE == _OFF) && (_DP_POWER_OFF_HDCP_SUPPORT == _OFF))

            // Disable HDCP support
            ScalerDpRx0ChangeHdcpDpcdCapability(_DISABLE);

            // Power Down HDCP Reset
            ScalerDpRx0HDCPBlockReset();
#endif

            ScalerDpLowPowerProc();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

            ScalerDpLowPowerProc();

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // Disable Aux Power Saving Mode
            ScalerSetBit(PB7_62_AUX_2, ~_BIT1, 0x00);

            // Switch Aux PHY to GDI BandGap
            ScalerSetBit(PB7_63_AUX_3, ~_BIT7, 0x00);

            // Disable Aux INT
            ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~_BIT4, 0x00);

            IP = 0xA0;

            if(enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL)
            {
                // Enable HDCP support
                ScalerDpRx0ChangeHdcpDpcdCapability(_ENABLE);
            }

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

#if(_DP_SUPPORT == _ON)
            SET_DP_DC_OFF_HPD_TOGGLE_FLAG();
#endif
            break;

        default:

            break;
    }
}

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
//--------------------------------------------------
// Description  : Dp Embedded Switch Setting
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT or _D2_INPUT_PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpEmbeddedSwitchSetting(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);

            if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
            {
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                // Set DDC0 Pinshare to GPI
                ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_33_PIN_SHARE_CTRL83, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif
            }
            else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT)
            {
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                // Set DDC0 Pinshare to GPI
                ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_33_PIN_SHARE_CTRL83, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif
            }

#if(_D0_DDC_CHANNEL_SEL == _DDC0)
            // Set DDC0 Pinshare to Aux
            ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            // Enable Aux Channel 0, Disable Channel 1/2
            ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
            // Aux Mapping to DDC0
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), 0x00);
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
            // Set DDC1 Pinshare to Aux
            ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            // Enable Aux Channel 1, Disable Channel 0/2
            ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
            // Aux Mapping to DDC1
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), _BIT0);
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
            // Set DDC1 Pinshare to Aux
            ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P10_33_PIN_SHARE_CTRL83, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            // Enable Aux Channel 2, Disable Channel 0/1
            ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
            // Aux Mapping to DDC2
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), _BIT1);
#endif
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D1_DP_LINK_CLK_RATE);

            if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT)
            {
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                // Set DDC0 Pinshare to GPI
                ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_33_PIN_SHARE_CTRL83, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif
            }
            else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT)
            {
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                // Set DDC0 Pinshare to GPI
                ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_33_PIN_SHARE_CTRL83, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif
            }

#if(_D1_DDC_CHANNEL_SEL == _DDC0)
            // Set DDC0 Pinshare to Aux
            ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            // Enable Aux Channel 0, Disable Channel 1/2
            ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
            // Aux Mapping to DDC0
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), 0x00);
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
            // Set DDC1 Pinshare to Aux
            ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            // Enable Aux Channel 1, Disable Channel 0/2
            ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
            // Aux Mapping to DDC1
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), _BIT0);
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
            // Set DDC1 Pinshare to Aux
            ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P10_33_PIN_SHARE_CTRL83, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            // Enable Aux Channel 2, Disable Channel 0/1
            ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
            // Aux Mapping to DDC2
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), _BIT1);
#endif
            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

        case _D2_INPUT_PORT:

            ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D2_DP_LINK_CLK_RATE);

            if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT)
            {
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                // Set DDC0 Pinshare to GPI
                ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_33_PIN_SHARE_CTRL83, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif
            }
            else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
            {
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                // Set DDC0 Pinshare to GPI
                ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                // Set DDC1 Pinshare to GPI
                ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(P10_33_PIN_SHARE_CTRL83, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif
            }

#if(_D2_DDC_CHANNEL_SEL == _DDC0)
            // Set DDC0 Pinshare to Aux
            ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            // Enable Aux Channel 0, Disable Channel 1/2
            ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
            // Aux Mapping to DDC0
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), 0x00);
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
            // Set DDC1 Pinshare to Aux
            ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            // Enable Aux Channel 1, Disable Channel 0/2
            ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
            // Aux Mapping to DDC1
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), _BIT0);
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
            // Set DDC1 Pinshare to Aux
            ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P10_33_PIN_SHARE_CTRL83, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            // Enable Aux Channel 2, Disable Channel 0/1
            ScalerSetBit(PB7_60_DIG_TX_04, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
            // Aux Mapping to DDC2
            ScalerSetBit(P6F_09_AUX_MAP_DDC, ~(_BIT1 | _BIT0), _BIT1);
#endif
            break;
#endif
        default:
            break;
    }

    SET_DP_EMBEDDED_SWITCH_SELECT(ucInputPort);
    SET_DP_EMBEDDED_SWITCH_EVENT(_TRUE);
}
#endif

#endif // End of #if(_DP_SUPPORT == _ON)

