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
// ID Code      : RL6492_Series_DP.c No.0000
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
void ScalerDpScanInitial(BYTE ucInputPort);
void ScalerDpSecDataReset(BYTE ucInputPort);
bit ScalerDpNormalPreDetect(BYTE ucInputPort);
BYTE ScalerDpScanInputPort(BYTE ucInputPort);
bit ScalerDpPSPreDetect(BYTE ucInputPort);
bit ScalerDpStableDetect(BYTE ucInputPort);
void ScalerDpHDCPUnplugReset(BYTE ucInputPort);
bit ScalerDpHdcpCheckValid(BYTE ucInputPort);
void ScalerDpFirstActiveProc(BYTE ucInputPort);
void ScalerDpPowerSwitch(EnumPowerAction enumPowerAction);
void ScalerDpJudgeHPDToggle(EnumPowerAction enumPowerAction);

void ScalerDpEdidSwitch(BYTE ucInputPort);
void ScalerDpFakeLinkTrainingSetting(BYTE ucInputPort);
EnumDpPowerState ScalerDpGetPowerStatus(BYTE ucInputPort);
EnumDpLaneCount ScalerDpGetLaneCount(BYTE ucInputPort);
EnumDpLinkRate ScalerDpGetLinkRate(BYTE ucInputPort);
EnumDpVoltageSwingLevel ScalerDpGetLaneVoltageSwingLv(BYTE ucInputPort, EnumDpLane enumDpLane);
EnumDpPreEmphasisLevel ScalerDpGetLanePreEmpLv(BYTE ucInputPort, EnumDpLane enumDpLane);
bit ScalerDpGetSrcMstEnable(BYTE ucInputPort);
void ScalerDpSetHotPlugEvent(BYTE ucInputPort, EnumDpHotPlugAssertType enumHpdType);

#if(_DP_LONG_HPD_MODE == _DP_LONG_HPD_DELAY_MODE)
void ScalerDpHotPlugHandler(void);

#elif(_DP_LONG_HPD_MODE == _DP_LONG_HPD_TIMEREVENT_MODE)
void ScalerDpHotPlugHandler(void);
#endif

void ScalerDpInitial(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
void ScalerDpLaneCountSwitch(BYTE ucInputPort, EnumDpLaneCount enumDpLaneCount);
void ScalerDpLowPowerProc(void);
void ScalerDpResetProc(void);
void ScalerDpTimerEventProc(EnumScalerTimerEventID enumEventID);
void ScalerDpVersionSwitch(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
bit ScalerDpCheckDCOffHpdToggle(EnumPowerAction enumPowerAction);
void ScalerDpMainLinkQualityManagement(BYTE ucInputPort);
StructDpRxErrorCount ScalerDpRxGetErrorCount(BYTE ucInputPort);

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
void ScalerDpRestoreFakeLTLaneCount(EnumSourceSearchPort enumSourceSearchPort);
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
void ScalerDpHdcpCapSwitch(BYTE ucInputPort);
void ScalerDpHdcpCtrlDpcdSwitch(BYTE ucInputPort);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial Setting for DP Scanning Port(Power Normal)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpScanInitial(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            ScalerDpRx0MacInitial();

            ScalerDpRx0PhyInitial();

            CLR_DP_RX0_FAKE_LINK_TRAINING();

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            ScalerDpRx1MacInitial();

            ScalerDpRx1PhyInitial();

            CLR_DP_RX1_FAKE_LINK_TRAINING();

            break;
#endif

        default:

            break;
    }
}

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
#if(_D0_DP_EXIST == _ON)

            case _D0_INPUT_PORT:

                if(GET_REG_DP_RX0_MAC_ASSIGNED() == _TRUE)
                {
                    ScalerDpRx0SecDataBlockReset();
                }

                break;
#endif

#if(_D1_DP_EXIST == _ON)

            case _D1_INPUT_PORT:
            case _D2_INPUT_PORT:

                if(GET_REG_DP_RX1_MAC_ASSIGNED() == _TRUE)
                {
                    ScalerDpRx1SecDataBlockReset();
                }

                break;
#endif

            default:
                break;
        }
    }
}


//--------------------------------------------------
// Description  : Signal PreDetection for DP(Power Normal)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpNormalPreDetect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            return ScalerDpRx0NormalPreDetect();
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return ScalerDpRx1NormalPreDetect();
#endif
        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDpScanInputPort(BYTE ucInputPort)
{
    switch((ucInputPort))
    {
#if(_D0_DP_EXIST == _ON)
        case _D0_INPUT_PORT:

            return ScalerDpRx0ScanInputPort();
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return ScalerDpRx1ScanInputPort();
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpPSPreDetect(BYTE ucInputPort)
{
    switch((ucInputPort))
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            return ScalerDpRx0PSPreDetect();
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return ScalerDpRx1PSPreDetect();
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpStableDetect(BYTE ucInputPort)
{
    switch((ucInputPort))
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            return ScalerDpRx0StableDetect();
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return ScalerDpRx1StableDetect();
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP Unplug Reset
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpHDCPUnplugReset(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            ScalerDpRx0HDCPUnplugReset();

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            ScalerDpRx1HDCPUnplugReset();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : Input Port
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpHdcpCheckValid(BYTE ucInputPort)
{
    switch((ucInputPort))
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            return ScalerDpRx0HdcpCheckValid();
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return ScalerDpRx1HdcpCheckValid();
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP First Active Process
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpFirstActiveProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            // Enable DP Fifo Under/OverFlow Watch Dog
            ScalerDpRx0SetFifoWD(_ENABLE);

            // Enable DP Fifo Under/OverFlow IRQ
            ScalerDpRx0SetFifoIRQ(_ENABLE);

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            // Enable DP Fifo Under/OverFlow Watch Dog
            ScalerDpRx1SetFifoWD(_ENABLE);

            // Enable DP Fifo Under/OverFlow IRQ
            ScalerDpRx1SetFifoIRQ(_ENABLE);

            break;
#endif

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

#if(_D0_DP_EXIST == _ON)
            CLR_DP_RX0_AUX_COMMAND_NO_REPLY();

            // Disable HDCP support
            ScalerDpRx0ChangeHdcpDpcdCapability(_DISABLE);

            // Power Down HDCP Reset
            ScalerDpRx0HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            ScalerDpRx0Hdcp2ResetProc();
#endif

#endif // End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)
            CLR_DP_RX1_AUX_COMMAND_NO_REPLY();

            // Disable HDCP support
            ScalerDpRx1ChangeHdcpDpcdCapability(_DISABLE);

            // Power Down HDCP Reset
            ScalerDpRx1HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            ScalerDpRx1Hdcp2ResetProc();
#endif

#endif // End of #if(_D1_DP_EXIST == _ON)

            ScalerDpLowPowerProc();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

#if(_D0_DP_EXIST == _ON)

            CLR_DP_RX0_AUX_COMMAND_NO_REPLY();

#endif // End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)

            CLR_DP_RX1_AUX_COMMAND_NO_REPLY();

#endif // End of #if(_D1_DP_EXIST == _ON)

            ScalerDpLowPowerProc();

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

#if(_D0_DP_EXIST == _ON)

            // Disable Aux Power Saving Mode
            ScalerSetBit(PB7_62_AUX_2, ~_BIT1, 0x00);

            // Switch Aux PHY to GDI BandGap
            ScalerSetBit(PB7_63_AUX_3, ~_BIT7, 0x00);

            // Disable Aux INT
            ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~_BIT4, 0x00);

#if(_DP_HDCP_ARBITER_SUPPORT == _OFF)
            if((enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL) || (enumPowerAction == _POWER_ACTION_OFF_TO_FAKE_OFF))
            {
                // Enable HDCP support
                ScalerDpRx0ChangeHdcpDpcdCapability(_ENABLE);
            }
#endif
#endif // End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)

            // Disable Aux Power Saving Mode
            ScalerSetBit(PBA_62_AUX_2, ~_BIT1, 0x00);

            // Switch Aux PHY to GDI BandGap
            ScalerSetBit(PBA_63_AUX_3, ~_BIT7, 0x00);

            // Disable Aux INT
            ScalerSetBit(PBA_7A_AUX_DIG_PHYA, ~_BIT4, 0x00);

#if(_DP_HDCP_ARBITER_SUPPORT == _OFF)
            if((enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL) || (enumPowerAction == _POWER_ACTION_OFF_TO_FAKE_OFF))
            {
                // Enable HDCP support
                ScalerDpRx1ChangeHdcpDpcdCapability(_ENABLE);
            }
#endif
#endif // End of #if(_D1_DP_EXIST == _ON)

            IP = 0xA0;

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

//--------------------------------------------------
// Description  : Decision DP HPD Toggle Behavior
// Input Value  : Power Action State
// Output Value : None
//--------------------------------------------------
void ScalerDpJudgeHPDToggle(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

            if(ScalerDpCheckDCOffHpdToggle(enumPowerAction) == _TRUE)
            {
#if(_D0_DP_EXIST == _ON)

                if((GET_DP_DC_OFF_HPD_HIGH() == _FALSE) || (GET_DP_RX0_HDCP_CHECK_ENABLE() == _TRUE))
                {
                    ScalerDpRx0SetHotPlugEvent(_DP_HPD_LOW_RESET_AUX);
                }

#endif // End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)

                CLR_DP_RX1_AUX_COMMAND_NO_REPLY();

                if((GET_DP_DC_OFF_HPD_HIGH() == _FALSE) || (GET_DP_RX1_HDCP_CHECK_ENABLE() == _TRUE))
                {
                    ScalerDpRx1SetHotPlugEvent(_DP_HPD_LOW_RESET_AUX);
                }

#endif // End of #if(_D1_DP_EXIST == _ON)
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

#if(_D0_DP_EXIST == _ON)

#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
            if(GET_DP_RX0_ALT_MODE_HPD_STAUTS() == _HIGH)
#else
            if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
#endif
            {
                // Case of (GET_DP_DC_OFF_HPD_HIGH() == _TRUE), HPD remains high

#if(_DP_DELL_D3_TEST_SUPPORT == _OFF)
                if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
#endif
                {
                    ScalerDpRx0SetHotPlugEvent(_DP_LONG_HPD_EVENT);
                }
            }
            else
            {
                // Case of ((GET_DP_DC_OFF_HPD_HIGH() == _FALSE) || (ScalerDpRx0HdcpCheckEnabled() == _TRUE)), DC off HPD low

                // Use long HPD instead of assert to avoid causing HP EliteBook 840 fail to play bluray DVD due to the long HPD which width is less than ~250ms
                ScalerDpRx0SetHotPlugEvent(_DP_LONG_HPD_EVENT);
            }

#endif // End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)

            switch(GET_DP_EMBEDDED_SWITCH_SELECT())
            {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

                case _D1_INPUT_PORT:

                    if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
                    {
#if(_DP_DELL_D3_TEST_SUPPORT == _OFF)
                        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
#endif
                        {
                            ScalerDpRx1SetHotPlugEvent(_DP_LONG_HPD_EVENT);
                        }
                    }
                    else
                    {
                        // Use long HPD instead of assert to avoid causing HP EliteBook 840 fail to play bluray DVD due to the long HPD which width is less than ~250ms
                        ScalerDpRx1SetHotPlugEvent(_DP_LONG_HPD_EVENT);
                    }

                    break;
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

                case _D2_INPUT_PORT:

                    if(PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH)
                    {
#if(_DP_DELL_D3_TEST_SUPPORT == _OFF)
                        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
#endif
                        {
                            ScalerDpRx1SetHotPlugEvent(_DP_LONG_HPD_EVENT);
                        }
                    }
                    else
                    {
                        // Use long HPD instead of assert to avoid causing HP EliteBook 840 fail to play bluray DVD due to the long HPD which width is less than ~250ms
                        ScalerDpRx1SetHotPlugEvent(_DP_LONG_HPD_EVENT);
                    }

                    break;
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

                default:

                    break;
            }
#endif // End of #if(_D1_DP_EXIST == _ON)

            break;

        case _POWER_ACTION_OFF_TO_FAKE_OFF:
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP EDID Switch
// Input Value  : Input DP Port
// Output Value : None
//--------------------------------------------------
void ScalerDpEdidSwitch(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            SET_DP_RX_D0_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            SET_DP_RX_D1_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Fake Link Training Setting
// Input Value  : ucInputPortType
// Output Value : None
//--------------------------------------------------
void ScalerDpFakeLinkTrainingSetting(BYTE ucInputPort)
{
#if(_D0_DP_EXIST == _ON)
    if(ucInputPort != _D0_INPUT_PORT)
    {
        ScalerDpRx0FakeLTProtect();
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (ucInputPort == _D1_INPUT_PORT)) ||
       ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (ucInputPort == _D2_INPUT_PORT)))
    {
        return;
    }
    else
    {
        ScalerDpRx1FakeLTProtect();
    }
#endif
}

//--------------------------------------------------
// Description  : Get DP Power Status (DPCD 00600h)
// Input Value  : DP Input Port
// Output Value : DP Power Status
//--------------------------------------------------
EnumDpPowerState ScalerDpGetPowerStatus(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
            {
                return _DP_POWER_DOWN;
            }
            else if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))
            {
                return _DP_POWER_DOWN_WITH_AUX;
            }

            return _DP_POWER_NORMAL;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
            {
                return _DP_POWER_DOWN;
            }
            else if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))
            {
                return _DP_POWER_DOWN_WITH_AUX;
            }

            return _DP_POWER_NORMAL;
#endif

        default:

            return _DP_POWER_NORMAL;
    }
}

//--------------------------------------------------
// Description  : Get DP Lane Count (DPCD 00101h)
// Input Value  : DP Input Port
// Output Value : DP Lane Count
//--------------------------------------------------
EnumDpLaneCount ScalerDpGetLaneCount(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
#endif
        default:

            return _DP_LINK_4_LANE;
    }
}

//--------------------------------------------------
// Description  : Get DP Link Rate (DPCD 00100h)
// Input Value  : DP Input Port
// Output Value : DP Link Rate
//--------------------------------------------------
EnumDpLinkRate ScalerDpGetLinkRate(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            return (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00));
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00));
#endif
        default:

            return _DP_LINK_RBR;
    }
}

//--------------------------------------------------
// Description  : Get DP Voltage Swing Level(DPCD 00103h-00106h [1:0])
// Input Value  : DP Input Port, Lane #
// Output Value : DP Voltage Swing Level of the lane
//--------------------------------------------------
EnumDpVoltageSwingLevel ScalerDpGetLaneVoltageSwingLv(BYTE ucInputPort, EnumDpLane enumDpLane)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT1 | _BIT0)));
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT1 | _BIT0)));
#endif
        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : Get DP Pre-emphasis Level(DPCD 00103h-00106h [4:3])
// Input Value  : DP Input Port, Lane #
// Output Value : DP Pre-emphasis Level of the lane
//--------------------------------------------------
EnumDpPreEmphasisLevel ScalerDpGetLanePreEmpLv(BYTE ucInputPort, EnumDpLane enumDpLane)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT4 | _BIT3)) >> 3);
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT4 | _BIT3)) >> 3);
#endif
        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : Get DP Source MST enable (DPCD 00111h[0])
// Input Value  : DP Input Port
// Output Value : _TRUE --> MST enable, _FALSE --> SST
//--------------------------------------------------
bit ScalerDpGetSrcMstEnable(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT0) == _BIT0)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT0) == _BIT0)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Dp HotPlug Event for interface
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void ScalerDpSetHotPlugEvent(BYTE ucInputPort, EnumDpHotPlugAssertType enumHpdType)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            ScalerDpRx0SetHotPlugEvent(enumHpdType);

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            ScalerDpRx1SetHotPlugEvent(enumHpdType);

            break;
#endif
        default:

            break;
    }
}

#if(_DP_LONG_HPD_MODE == _DP_LONG_HPD_DELAY_MODE)
//--------------------------------------------------
// Description  : Dp Hot Plug Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHotPlugHandler(void)
{
    BYTE ucI = 0;
    BYTE ucPortNum = 0;

    StructHpdSequence pstHpdSeq[] =
    {
        // dummy
        {_NO_INPUT_PORT, _DP_HPD_TIME_NONE},

#if(_D0_DP_EXIST == _ON)
        {_NO_INPUT_PORT, _DP_HPD_TIME_NONE},
#endif
#if(_D1_DP_EXIST == _ON)
        {_NO_INPUT_PORT, _DP_HPD_TIME_NONE},
#endif
    };

#if(_D0_DP_EXIST == _ON)
    if((pstHpdSeq[1 + ucPortNum].enumHpdTime = ScalerDpRx0BeforeHpdToggleProc(GET_DP_RX0_HOTPLUG_ASSERT_TYPE())) != _DP_HPD_TIME_NONE)
    {
        pstHpdSeq[1 + ucPortNum].enumPort = _D0_INPUT_PORT;
        ucPortNum ++;
    }

    CLR_DP_RX0_HOTPLUG_ASSERT_TYPE();
#endif

#if(_D1_DP_EXIST == _ON)
    if((pstHpdSeq[1 + ucPortNum].enumHpdTime = ScalerDpRx1BeforeHpdToggleProc(GET_DP_RX1_HOTPLUG_ASSERT_TYPE())) != _DP_HPD_TIME_NONE)
    {
        pstHpdSeq[1 + ucPortNum].enumPort = GET_DP_EMBEDDED_SWITCH_SELECT();
        ucPortNum ++;
    }

    CLR_DP_RX1_HOTPLUG_ASSERT_TYPE();
#endif

    if(ucPortNum == 0)
    {
        return;
    }

    // Bubble sort for reorder squence (HPD time short -> long)
    for(pData[0] = 1; pData[0] < ucPortNum; pData[0] ++)
    {
        for(pData[1] = 1; pData[1] <= (ucPortNum - pData[0]); pData[1] ++)
        {
            if(pstHpdSeq[pData[1]].enumHpdTime > pstHpdSeq[pData[1] + 1].enumHpdTime)
            {
                pstHpdSeq[0] = pstHpdSeq[pData[1]];
                pstHpdSeq[pData[1]] = pstHpdSeq[pData[1] + 1];
                pstHpdSeq[pData[1] + 1] = pstHpdSeq[0];
            }
        }
    }

    // Reset the dummy seq time for first HPD delay calculation
    pstHpdSeq[0].enumPort = _NO_INPUT_PORT;
    pstHpdSeq[0].enumHpdTime = 0;

    // Low Process
    for(ucI = 1; ucI <= ucPortNum; ucI ++)
    {
        if(pstHpdSeq[ucI].enumHpdTime == _DP_HPD_ASSERTED_TIME)
        {
            // Skip low process of this turn
            continue;
        }

        switch(pstHpdSeq[ucI].enumPort)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            case _D0_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
                {
                    DebugMessageRx0("_D0_HOT_PLUG_LOW", 0);

#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
                    SET_DP_RX0_ALT_MODE_HPD_LOW();
#else
                    PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
#endif
                }

                break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            case _D1_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
                {
                    DebugMessageRx1("_D1_HOT_PLUG_LOW", 0);
                    PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            case _D2_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D2_INPUT_PORT) == _TRUE)
                {
                    DebugMessageRx1("_D2_HOT_PLUG_LOW", 0);
                    PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
                }

                break;
#endif
            default:
                break;
        }
    }

    // High Process
    for(ucI = 1; ucI <= ucPortNum; ucI ++)
    {
        switch(pstHpdSeq[ucI].enumPort)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            case _D0_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
                {
                    if((pstHpdSeq[ucI].enumHpdTime != pstHpdSeq[ucI - 1].enumHpdTime))
                    {
                        ScalerTimerDelayXms(pstHpdSeq[ucI].enumHpdTime - pstHpdSeq[ucI - 1].enumHpdTime);
                        DebugMessageRx0("_D0_HOT_PLUG_HIGH after Xms", (pstHpdSeq[ucI].enumHpdTime - pstHpdSeq[ucI - 1].enumHpdTime));
                    }
                    else
                    {
                        // Avoid pulling high concurrently (solution of NVIDIA probably ignoring the sencond HPD high while 2 ports conneted)
                        if(ucI >= 2)
                        {
                            ScalerTimerDelayXms(2);
                            DebugMessageRx0("_D0_HOT_PLUG_HIGH after Xms", 2);
                        }
                    }

                    ScalerDpRx0AfterHpdToggleProc();

#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
                    SET_DP_RX0_ALT_MODE_HPD_HIGH();
#else
                    PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
#endif
                }

                break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            case _D1_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
                {
                    if((pstHpdSeq[ucI].enumHpdTime != pstHpdSeq[ucI - 1].enumHpdTime))
                    {
                        ScalerTimerDelayXms(pstHpdSeq[ucI].enumHpdTime - pstHpdSeq[ucI - 1].enumHpdTime);
                        DebugMessageRx1("_D1_HOT_PLUG_HIGH after Xms", (pstHpdSeq[ucI].enumHpdTime - pstHpdSeq[ucI - 1].enumHpdTime));
                    }
                    else
                    {
                        // Avoid pulling high concurrently (solution of NVIDIA probably ignoring the sencond HPD high while 2 ports conneted)
                        if(ucI >= 2)
                        {
                            ScalerTimerDelayXms(2);
                            DebugMessageRx1("_D1_HOT_PLUG_HIGH after Xms", 2);
                        }
                    }

                    ScalerDpRx1AfterHpdToggleProc();

                    PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            case _D2_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D2_INPUT_PORT) == _TRUE)
                {
                    if((pstHpdSeq[ucI].enumHpdTime != pstHpdSeq[ucI - 1].enumHpdTime))
                    {
                        ScalerTimerDelayXms(pstHpdSeq[ucI].enumHpdTime - pstHpdSeq[ucI - 1].enumHpdTime);
                        DebugMessageRx1("_D2_HOT_PLUG_HIGH after Xms", (pstHpdSeq[ucI].enumHpdTime - pstHpdSeq[ucI - 1].enumHpdTime));
                    }
                    else
                    {
                        // Avoid pulling high concurrently (solution of NVIDIA probably ignoring the sencond HPD high while 2 ports conneted)
                        if(ucI >= 2)
                        {
                            ScalerTimerDelayXms(2);
                            DebugMessageRx1("_D2_HOT_PLUG_HIGH after Xms", 2);
                        }
                    }

                    ScalerDpRx1AfterHpdToggleProc();

                    PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
                }

                break;
#endif
            default:
                break;
        }
    }
}

#elif(_DP_LONG_HPD_MODE == _DP_LONG_HPD_TIMEREVENT_MODE)
//--------------------------------------------------
// Description  : Dp Hot Plug Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHotPlugHandler(void)
{
    BYTE ucI = 0;
    BYTE ucPortNum = 0;

    StructHpdSequence pstHpdSeq[] =
    {
#if(_D0_DP_EXIST == _ON)
        {_NO_INPUT_PORT, _DP_HPD_TIME_NONE},
#endif
#if(_D1_DP_EXIST == _ON)
        {_NO_INPUT_PORT, _DP_HPD_TIME_NONE},
#endif
    };

#if(_D0_DP_EXIST == _ON)
    if((pstHpdSeq[ucPortNum].enumHpdTime = ScalerDpRx0BeforeHpdToggleProc(GET_DP_RX0_HOTPLUG_ASSERT_TYPE())) != _DP_HPD_TIME_NONE)
    {
        pstHpdSeq[ucPortNum].enumPort = _D0_INPUT_PORT;
        ucPortNum ++;
    }

    CLR_DP_RX0_HOTPLUG_ASSERT_TYPE();
#endif

#if(_D1_DP_EXIST == _ON)
    if((pstHpdSeq[ucPortNum].enumHpdTime = ScalerDpRx1BeforeHpdToggleProc(GET_DP_RX1_HOTPLUG_ASSERT_TYPE())) != _DP_HPD_TIME_NONE)
    {
        pstHpdSeq[ucPortNum].enumPort = GET_DP_EMBEDDED_SWITCH_SELECT();
        ucPortNum ++;
    }

    CLR_DP_RX1_HOTPLUG_ASSERT_TYPE();
#endif

    if(ucPortNum == 0)
    {
        return;
    }

    // Low Process
    for(ucI = 0; ucI < ucPortNum; ucI ++)
    {
        if(pstHpdSeq[ucI].enumHpdTime == _DP_HPD_ASSERTED_TIME)
        {
            // Skip low process of this turn
            continue;
        }

        switch(pstHpdSeq[ucI].enumPort)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            case _D0_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
                {
                    DebugMessageRx0("_D0_HOT_PLUG_LOW", 0);

#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
                    SET_DP_RX0_ALT_MODE_HPD_LOW();
#else
                    PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
#endif
                }

                break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            case _D1_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
                {
                    DebugMessageRx1("_D1_HOT_PLUG_LOW", 0);
                    PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            case _D2_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D2_INPUT_PORT) == _TRUE)
                {
                    DebugMessageRx1("_D2_HOT_PLUG_LOW", 0);
                    PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
                }

                break;
#endif
            default:
                break;
        }
    }

    // High Process
    for(ucI = 0; ucI < ucPortNum; ucI ++)
    {
        switch(pstHpdSeq[ucI].enumPort)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            case _D0_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
                {
                    if(pstHpdSeq[ucI].enumHpdTime == _DP_HPD_ASSERTED_TIME)
                    {
                        DebugMessageRx0("_D0_HOT_PLUG_HIGH", 0);

                        ScalerDpRx0AfterHpdToggleProc();

#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
                        SET_DP_RX0_ALT_MODE_HPD_HIGH();
#else
                        PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
#endif
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(pstHpdSeq[ucI].enumHpdTime, _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                    }
                }

                break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            case _D1_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
                {
                    if(pstHpdSeq[ucI].enumHpdTime == _DP_HPD_ASSERTED_TIME)
                    {
                        DebugMessageRx1("_D1_HOT_PLUG_HIGH", 0);

                        ScalerDpRx1AfterHpdToggleProc();

                        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(pstHpdSeq[ucI].enumHpdTime, _SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);
                    }
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            case _D2_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D2_INPUT_PORT) == _TRUE)
                {
                    if(pstHpdSeq[ucI].enumHpdTime == _DP_HPD_ASSERTED_TIME)
                    {
                        DebugMessageRx1("_D2_HOT_PLUG_HIGH", 0);

                        ScalerDpRx1AfterHpdToggleProc();

                        PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(pstHpdSeq[ucI].enumHpdTime, _SCALER_TIMER_EVENT_DP_RX2_HOTPLUG_ASSERTED);
                    }
                }

                break;
#endif
            default:
                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Initial DP Settings
// Input Value  : _D0_DP_PORT or _D1_DP_PORT or _D2_DP_PORT, DPCD version, Lane Count, MST Port
// Output Value : None
//--------------------------------------------------
void ScalerDpInitial(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            ScalerDpRx0Initial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumFreeSyncSupport);

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            ScalerDpRx1Initial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumFreeSyncSupport);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Lane Switch
// Input Value  : DP input port, DP Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpLaneCountSwitch(BYTE ucInputPort, EnumDpLaneCount enumDpLaneCount)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            if(enumDpLaneCount > _D0_DP_MAIN_LINK_LANES)
            {
                enumDpLaneCount = _D0_DP_MAIN_LINK_LANES;
            }

            SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
            SET_DP_RX_CAPABILITY_SWITCHED();

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            if(ucInputPort == _D1_INPUT_PORT)
            {
                if(enumDpLaneCount > _D1_DP_MAIN_LINK_LANES)
                {
                    enumDpLaneCount = _D1_DP_MAIN_LINK_LANES;
                }
            }
            else if(ucInputPort == _D2_INPUT_PORT)
            {
                if(enumDpLaneCount > _D2_DP_MAIN_LINK_LANES)
                {
                    enumDpLaneCount = _D2_DP_MAIN_LINK_LANES;
                }
            }

            SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
            SET_DP_RX_CAPABILITY_SWITCHED();

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Low Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpLowPowerProc(void)
{
#if((_D0_DP_EXIST == _ON) && (_D1_DP_EXIST == _ON))

    // Turn Off Output Clock
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, 0x00);

    // Turn Off SCLK PLL
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Set end to idle trigger Aux Int, Clear Aux INT Flag
    ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Clear Manchester/Stop pattern/Sync_end pattern/Byte boundary check Error
    ScalerSetBit(PB7_79_AUX_DIG_PHY9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set end to idle trigger Aux Int, Clear Aux INT Flag
    ScalerSetBit(PBA_7A_AUX_DIG_PHYA, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Clear Manchester/Stop pattern/Sync_end pattern/Byte boundary check Error
    ScalerSetBit(PBA_79_AUX_DIG_PHY9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerTimerDelayXms(2);

    if((ScalerGetBit(PB7_7A_AUX_DIG_PHYA, _BIT0) == 0x00) && (ScalerGetBit(PBA_7A_AUX_DIG_PHYA, _BIT0) == 0x00))
    {
        // Aux PHY Power Saving Mode
        ScalerSetBit(PB7_62_AUX_2, ~_BIT1, _BIT1);

        // Aux Bias Current From POR
        ScalerSetBit(PB7_63_AUX_3, ~_BIT7, _BIT7);

        // Aux PHY Power Saving Mode
        ScalerSetBit(PBA_62_AUX_2, ~_BIT1, _BIT1);

        // Aux Bias Current From POR
        ScalerSetBit(PBA_63_AUX_3, ~_BIT7, _BIT7);

        // Disable GDI Bandgap
        ScalerGDIPhyBandgap(_OFF);

        IP = 0x81;

        CLR_DP_RX0_PS_AUX_TOGGLE();

        CLR_DP_RX1_PS_AUX_TOGGLE();

        // Enable Aux INT
        ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~(_BIT4 | _BIT0), (_BIT4));

        // Enable Aux INT
        ScalerSetBit(PBA_7A_AUX_DIG_PHYA, ~(_BIT4 | _BIT0), (_BIT4));

        DebugMessageDigital("7. Low Power Event", 0);
    }
    else
    {
        SET_DP_RX0_PS_AUX_TOGGLE();

        SET_DP_RX1_PS_AUX_TOGGLE();
    }

#elif(_D0_DP_EXIST == _ON)

    // Turn Off Output Clock
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, 0x00);

    // Turn Off SCLK PLL
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Set end to idle trigger Aux Int, Clear Aux INT Flag
    ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Clear Manchester/Stop pattern/Sync_end pattern/Byte boundary check Error
    ScalerSetBit(PB7_79_AUX_DIG_PHY9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerTimerDelayXms(2);

    if(ScalerGetBit(PB7_7A_AUX_DIG_PHYA, _BIT0) == 0x00)
    {
        // Aux PHY Power Saving Mode
        ScalerSetBit(PB7_62_AUX_2, ~_BIT1, _BIT1);

        // Aux Bias Current From POR
        ScalerSetBit(PB7_63_AUX_3, ~_BIT7, _BIT7);

        // Disable GDI Bandgap
        ScalerGDIPhyBandgap(_OFF);

        IP = 0x81;

        CLR_DP_RX0_PS_AUX_TOGGLE();

        // Enable Aux INT
        ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~(_BIT4 | _BIT0), (_BIT4));

        DebugMessageDigital("7. Low Power Event", 0);
    }
    else
    {
        SET_DP_RX0_PS_AUX_TOGGLE();
    }

#elif(_D1_DP_EXIST == _ON)

    // Turn Off Output Clock
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, 0x00);

    // Turn Off SCLK PLL
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Set end to idle trigger Aux Int, Clear Aux INT Flag
    ScalerSetBit(PBA_7A_AUX_DIG_PHYA, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Clear Manchester/Stop pattern/Sync_end pattern/Byte boundary check Error
    ScalerSetBit(PBA_79_AUX_DIG_PHY9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerTimerDelayXms(2);

    if(ScalerGetBit(PBA_7A_AUX_DIG_PHYA, _BIT0) == 0x00)
    {
        // Aux PHY Power Saving Mode
        ScalerSetBit(PBA_62_AUX_2, ~_BIT1, _BIT1);

        // Aux Bias Current From POR
        ScalerSetBit(PBA_63_AUX_3, ~_BIT7, _BIT7);

        // Disable GDI Bandgap
        ScalerGDIPhyBandgap(_OFF);

        IP = 0x81;

        CLR_DP_RX1_PS_AUX_TOGGLE();

        // Enable Aux INT
        ScalerSetBit(PBA_7A_AUX_DIG_PHYA, ~(_BIT4 | _BIT0), (_BIT4));

        DebugMessageDigital("7. Low Power Event", 0);
    }
    else
    {
        SET_DP_RX1_PS_AUX_TOGGLE();
    }
#endif
}
//--------------------------------------------------
// Description  : DP Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpResetProc(void)
{
#if(_D0_DP_EXIST == _ON)

    // Disable DP Fifo Under/OverFlow Watch Dog
    ScalerDpRx0SetFifoWD(_DISABLE);

    // Disable DP Fifo Under/OverFlow IRQ
    ScalerDpRx0SetFifoIRQ(_DISABLE);

    // Disable DP No Video Stream IRQ
    ScalerDpRx0SetNoVideoStreamIRQ(_DISABLE);
#endif

#if(_D1_DP_EXIST == _ON)

    // Disable DP Fifo Under/OverFlow Watch Dog
    ScalerDpRx1SetFifoWD(_DISABLE);

    // Disable DP Fifo Under/OverFlow IRQ
    ScalerDpRx1SetFifoIRQ(_DISABLE);

    // Disable DP No Video Stream IRQ
    ScalerDpRx1SetNoVideoStreamIRQ(_DISABLE);
#endif
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
            ScalerDpRx0SetHotPlugEvent(_DP_HPD_ASSERTED);
            break;

        case _SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT:

            if(ScalerDpRx0HdcpReAuthStatusCheck() == _FALSE)
            {
                DebugMessageRx0("7. DP HDCP Long HPD", 0);
                ScalerDpRx0SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
            }

            break;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX0_LONG_HOTPLUG_EVENT:

            DebugMessageRx0("7. DP Long HPD", 0);
            ScalerDpRx0SetHotPlugEvent(_DP_LONG_HPD_EVENT);

            break;
#endif
        case _SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ:

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
            if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
            {
                if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2) &&
                   ((GET_DP_RX_D0_MARGIN_LINK_HBR2() == _TRUE) || (GET_DP_RX_D6_MARGIN_LINK_HBR2() == _TRUE)))
                {
                    DebugMessageRx0("7. DP Margin Link Long HPD", 0);

                    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    // When Define Extended Rx Cap Should Set DPCD 0x02201
                    ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _DP_LINK_HBR);
#else
                    // When Define Extended Rx Cap Should Set DPCD 0x02201
                    g_ucDpRx0DPCD02201hValue = _DP_LINK_HBR;
#endif

                    ScalerDpRx0SetHotPlugEvent(_DP_HBR2_MARGIN_LINK_HPD_EVENT);
                }
                else
                {
                    ScalerDpRx0LinkStatusIRQ();
                }
            }
#else
            ScalerDpRx0LinkStatusIRQ();
#endif
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED:

            ScalerDpRx1SetHotPlugEvent(_DP_HPD_ASSERTED);

            break;

        case _SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT:

            if(ScalerDpRx1HdcpReAuthStatusCheck() == _FALSE)
            {
                DebugMessageRx1("7. DP HDCP Long HPD", 0);
                ScalerDpRx1SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
            }

            break;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX1_LONG_HOTPLUG_EVENT:

            DebugMessageRx1("7. DP Long HPD", 0);
            ScalerDpRx1SetHotPlugEvent(_DP_LONG_HPD_EVENT);

            break;
#endif
        case _SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ:

            ScalerDpRx1LinkStatusIRQ();

            break;
#endif


#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

        case _SCALER_TIMER_EVENT_DP_RX2_HOTPLUG_ASSERTED:

            ScalerDpRx1SetHotPlugEvent(_DP_HPD_ASSERTED);

            break;

        case _SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT:

            if(ScalerDpRx1HdcpReAuthStatusCheck() == _FALSE)
            {
                DebugMessageRx1("7. DP HDCP Long HPD", 0);
                ScalerDpRx1SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
            }

            break;

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX2_LONG_HOTPLUG_EVENT:

            DebugMessageRx1("7. DP Long HPD", 0);
            ScalerDpRx1SetHotPlugEvent(_DP_LONG_HPD_EVENT);

            break;
#endif
        case _SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ:

            ScalerDpRx1LinkStatusIRQ();

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : DP input port, _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpVersionSwitch(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

            SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
            SET_DP_RX_CAPABILITY_SWITCHED();

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
            SET_DP_RX_CAPABILITY_SWITCHED();

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check DP DC OFF HPD Toggle
// Input Value  : enumPowerAction
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpCheckDCOffHpdToggle(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

#if(_DP_MST_SUPPORT == _ON)
            if(GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD() == _TRUE)
            {
                return _FALSE;
            }
#endif

            break;

        default:

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Main Link Quality Management
// Input Value  : Dx Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpMainLinkQualityManagement(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
}

//--------------------------------------------------
// Description  : Read DP Rx Error Count
// Input Value  : DP Input Port
// Output Value : DP 4 Lane Error Count & Valid Flag
//--------------------------------------------------
StructDpRxErrorCount ScalerDpRxGetErrorCount(BYTE ucInputPort)
{
    StructDpRxErrorCount stDpRxErrorCount;
    stDpRxErrorCount.usDpRxLane0ErrorCount = 0;
    stDpRxErrorCount.usDpRxLane1ErrorCount = 0;
    stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
    stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)
        case _D0_INPUT_PORT:

            return ScalerDpRx0GetErrorCount();
#endif

#if(_D1_DP_EXIST == _ON)
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return ScalerDpRx1GetErrorCount();
#endif

        default:

            return stDpRxErrorCount;
    }
}

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Restore DP Rx Fake LT Support Lane Count
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpRestoreFakeLTLaneCount(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
#if(_D0_DP_EXIST == _ON)
        case _D0_INPUT_PORT:

            g_ucDpRx0FakeLTLaneCount = g_ucDpRx0FakeLTLaneCountBackUp;
            break;
#endif

#if(_D1_DP_EXIST == _ON)
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            g_ucDpRx1FakeLTLaneCount = g_ucDpRx1FakeLTLaneCountBackUp;
            break;
#endif

        default:
            break;
    }
}
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Hdcp Capility Switch
// Input Value  : Input DP Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcpCapSwitch(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

#if(_D0_DP_EXIST == _ON)
            DebugMessageRx0("Set Rx0 HDCP capability!!", 0);

            SET_DP_RX0_TARGET_HDCP_CAPABILITY(_ENABLE);
#endif

#if(_D1_DP_EXIST == _ON)
            SET_DP_RX1_TARGET_HDCP_CAPABILITY(_DISABLE);
#endif

            break;

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

#if(_D0_DP_EXIST == _ON)

            SET_DP_RX0_TARGET_HDCP_CAPABILITY(_DISABLE);
#endif

#if(_D1_DP_EXIST == _ON)
            DebugMessageRx1("Set Rx1 HDCP capability!!", 0);

            SET_DP_RX1_TARGET_HDCP_CAPABILITY(_ENABLE);
#endif

            break;

        default:

#if(_D0_DP_EXIST == _ON)
            DebugMessageRx0("Set Rx0 HDCP capability!!", 0);

            SET_DP_RX0_TARGET_HDCP_CAPABILITY(_ENABLE);
#endif

#if(_D1_DP_EXIST == _ON)
            SET_DP_RX1_TARGET_HDCP_CAPABILITY(_DISABLE);
#endif

            break;
    }

    SET_DP_RX_CAPABILITY_SWITCHED();
}

//--------------------------------------------------
// Description  : Enable DPCD table control by DP HDCP circuit
// Input Value  : EnumSourceSearchPort
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcpCtrlDpcdSwitch(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

#if(_D0_DP_EXIST == _ON)
            // Enable HDCP support
            ScalerDpRx0ChangeHdcpDpcdCapability(_ENABLE);

            // Disable HDCP handshake monitoring
            ScalerDpRx0HdcpHandshakeMonitorDisable();

            // Align capability switch target
            SET_DP_RX0_TARGET_HDCP_CAPABILITY(_ENABLE);
#endif

#if(_D1_DP_EXIST == _ON)
            // Disable HDCP support
            ScalerDpRx1ChangeHdcpDpcdCapability(_DISABLE);

            // Enable HDCP handshake monitoring while HDCP capabilit disable
            ScalerDpRx1HdcpHandshakeMonitorEnable();

            // Align capability switch target
            SET_DP_RX1_TARGET_HDCP_CAPABILITY(_DISABLE);
#endif

            // Switch Rx0 DPCD table controlled by DP HDCP circuit
            SET_REG_DP_RX0_DPCD_CTRL_BY_HDCP();

            break;

        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

#if(_D0_DP_EXIST == _ON)
            // Disable HDCP support
            ScalerDpRx0ChangeHdcpDpcdCapability(_DISABLE);

            // Enable HDCP handshake monitoring while HDCP capabilit disable
            ScalerDpRx0HdcpHandshakeMonitorEnable();

            // Align capability switch target
            SET_DP_RX0_TARGET_HDCP_CAPABILITY(_DISABLE);
#endif

#if(_D1_DP_EXIST == _ON)
            // Enable HDCP support
            ScalerDpRx1ChangeHdcpDpcdCapability(_ENABLE);

            // Disable HDCP handshake monitoring
            ScalerDpRx1HdcpHandshakeMonitorDisable();

            // Align capability switch target
            SET_DP_RX1_TARGET_HDCP_CAPABILITY(_ENABLE);
#endif

            // Switch Rx1 DPCD table controlled by DP HDCP circuit
            SET_REG_DP_RX1_DPCD_CTRL_BY_HDCP();

            break;

        default:
            break;
    }
}
#endif

#endif // #if(_DP_SUPPORT == _ON)

