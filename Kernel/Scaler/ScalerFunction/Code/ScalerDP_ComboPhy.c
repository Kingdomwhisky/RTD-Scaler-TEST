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
// ID Code      : ScalerDP_ComboPhy.c No.0000
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
BYTE g_ucDpRx0MainLinkMarginal;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
void ScalerDpEdidSwitch(BYTE ucInputPort);
void ScalerDpFakeLinkTrainingSetting(BYTE ucInputPort);
void ScalerDpFirstActiveProc(BYTE ucInputPort);
EnumDpPowerState ScalerDpGetPowerStatus(BYTE ucInputPort);
EnumDpLaneCount ScalerDpGetLaneCount(BYTE ucInputPort);
EnumDpLinkRate ScalerDpGetLinkRate(BYTE ucInputPort);
EnumDpVoltageSwingLevel ScalerDpGetLaneVoltageSwingLv(BYTE ucInputPort, EnumDpLane enumDpLane);
EnumDpPreEmphasisLevel ScalerDpGetLanePreEmpLv(BYTE ucInputPort, EnumDpLane enumDpLane);
bit ScalerDpGetSrcMstEnable(BYTE ucInputPort);
bit ScalerDpHdcpCheckValid(BYTE ucInputPort);
void ScalerDpSetHotPlugEvent(BYTE ucInputPort, EnumDpHotPlugAssertType enumHpdType);
void ScalerDpHotPlugHandler(void);
void ScalerDpInitial(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
void ScalerDpJudgeHPDToggle(EnumPowerAction enumPowerAction);
void ScalerDpLaneCountSwitch(BYTE ucInputPort, EnumDpLaneCount enumDpLaneCount);
void ScalerDpLowPowerProc(void);
bit ScalerDpNormalPreDetect(BYTE ucInputPort);
bit ScalerDpPSPreDetect(BYTE ucInputPort);
void ScalerDpResetProc(void);
void ScalerDpScanInitial(BYTE ucInputPort);
BYTE ScalerDpScanInputPort(BYTE ucInputPort);
bit ScalerDpStableDetect(BYTE ucInputPort);
void ScalerDpVersionSwitch(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
void ScalerDpHDCPUnplugReset(BYTE ucInputPort);
void ScalerDpMainLinkQualityManagement(BYTE ucInputPort);
StructDpRxErrorCount ScalerDpRxGetErrorCount(BYTE ucInputPort);

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
void ScalerDpRestoreFakeLTLaneCount(EnumSourceSearchPort enumSourceSearchPort);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP EDID Switch
// Input Value  : Input DP Port
// Output Value : None
//--------------------------------------------------
void ScalerDpEdidSwitch(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    SET_DP_RX_D0_EDID_SWITCH();
    SET_DP_RX_CAPABILITY_SWITCHED();
}
//--------------------------------------------------
// Description  : DP Fake Link Training Setting
// Input Value  : ucInputPortType
// Output Value : None
//--------------------------------------------------
void ScalerDpFakeLinkTrainingSetting(BYTE ucInputPort)
{
    if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (ucInputPort == _D0_INPUT_PORT)) ||
       ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (ucInputPort == _D1_INPUT_PORT)) ||
       ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (ucInputPort == _D2_INPUT_PORT)))
    {
        return;
    }
    else
    {
        ScalerDpRx0FakeLTProtect();
    }
}
//--------------------------------------------------
// Description  : DP First Active Process
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpFirstActiveProc(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    ScalerDpRx0SetFifoWD(_ENABLE);
    ScalerDpRx0SetFifoIRQ(_ENABLE);
}

//--------------------------------------------------
// Description  : Get DP Power Status (DPCD 00600h)
// Input Value  : DP Input Port
// Output Value : DP Power Status
//--------------------------------------------------
EnumDpPowerState ScalerDpGetPowerStatus(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
    {
        return _DP_POWER_DOWN;
    }
    else if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))
    {
        return _DP_POWER_DOWN_WITH_AUX;
    }

    return _DP_POWER_NORMAL;
}

//--------------------------------------------------
// Description  : Get DP Lane Count (DPCD 00101h)
// Input Value  : DP Input Port
// Output Value : DP Lane Count
//--------------------------------------------------
EnumDpLaneCount ScalerDpGetLaneCount(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
}

//--------------------------------------------------
// Description  : Get DP Link Rate (DPCD 00100h)
// Input Value  : Input DP Port
// Output Value : DP Link Rate
//--------------------------------------------------
EnumDpLinkRate ScalerDpGetLinkRate(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00));
}

//--------------------------------------------------
// Description  : Get DP Voltage Swing Level (DPCD 00103h-00106h [1:0])
// Input Value  : DP Input Port, Lane #
// Output Value : DP Voltage Swing Level of the lane
//--------------------------------------------------
EnumDpVoltageSwingLevel ScalerDpGetLaneVoltageSwingLv(BYTE ucInputPort, EnumDpLane enumDpLane)
{
    ucInputPort = ucInputPort;

    return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT1 | _BIT0)));
}

//--------------------------------------------------
// Description  : Get DP Pre-emphasis Level (DPCD 00103h-00106h [4:3])
// Input Value  : DP Input Port, Lane #
// Output Value : DP Pre-emphasis Level of the lane
//--------------------------------------------------
EnumDpPreEmphasisLevel ScalerDpGetLanePreEmpLv(BYTE ucInputPort, EnumDpLane enumDpLane)
{
    ucInputPort = ucInputPort;

    return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT4 | _BIT3)) >> 3);
}

//--------------------------------------------------
// Description  : Get DP Source MST enable (DPCD 00111h[0])
// Input Value  : DP Input Port
// Output Value : _TRUE --> MST enable, _FALSE --> SST
//--------------------------------------------------
bit ScalerDpGetSrcMstEnable(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT0) == _BIT0)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : Input Port
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpHdcpCheckValid(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return ScalerDpRx0HdcpCheckValid();
}
//--------------------------------------------------
// Description  : Dp HotPlug Event for interface
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void ScalerDpSetHotPlugEvent(BYTE ucInputPort, EnumDpHotPlugAssertType enumHpdType)
{
    ucInputPort = ucInputPort;

    ScalerDpRx0SetHotPlugEvent(enumHpdType);
}

//--------------------------------------------------
// Description  : Dp Hot Plug Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHotPlugHandler(void)
{
    EnumDpHotPlugTime enumHpdTime = _DP_HPD_TIME_NONE;

    enumHpdTime = ScalerDpRx0BeforeHpdToggleProc(GET_DP_RX0_HOTPLUG_ASSERT_TYPE());

    CLR_DP_RX0_HOTPLUG_ASSERT_TYPE();

    if(enumHpdTime == _DP_HPD_TIME_NONE)
    {
        return;
    }

    if(enumHpdTime != _DP_HPD_ASSERTED_TIME)
    {
        // Low Process
        switch(GET_DP_EMBEDDED_SWITCH_SELECT())
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            case _D0_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
                {
                    DebugMessageRx0("_D0_HOT_PLUG_LOW", 0);
                    PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);

                    ScalerTimerDelayXms(enumHpdTime);
                    DebugMessageRx0("DelayXms", enumHpdTime);
                }

                break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            case _D1_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
                {
                    DebugMessageRx0("_D1_HOT_PLUG_LOW", 0);
                    PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

                    ScalerTimerDelayXms(enumHpdTime);
                    DebugMessageRx0("DelayXms", enumHpdTime);
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            case _D2_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D2_INPUT_PORT) == _TRUE)
                {
                    DebugMessageRx0("_D2_HOT_PLUG_LOW", 0);
                    PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);

                    ScalerTimerDelayXms(enumHpdTime);
                    DebugMessageRx0("DelayXms", enumHpdTime);
                }

                break;
#endif

            default:
                break;
        }
    }

    // High Process
    ScalerDpRx0AfterHpdToggleProc();

    switch(GET_DP_EMBEDDED_SWITCH_SELECT())
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
            {
                PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
                DebugMessageRx0("_D0_HOT_PLUG_HIGH", 0);
            }

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
            {
                DebugMessageRx0("_D1_HOT_PLUG_HIGH", 0);
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
            }

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            if(ScalerSyncDpCableStatus(_D2_INPUT_PORT) == _TRUE)
            {
                DebugMessageRx0("_D2_HOT_PLUG_HIGH", 0);
                PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Initial DP Settings
// Input Value  : DP port, DPCD version, Lane Count, MST Port
// Output Value : None
//--------------------------------------------------
void ScalerDpInitial(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport)
{
    ucInputPort = ucInputPort;
    ScalerDpRx0Initial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumFreeSyncSupport);
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

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) || (_DP_POWER_OFF_HDCP_SUPPORT == _ON))
            if(GET_DP_DC_OFF_HPD_HIGH() == _FALSE)
#else
            if((GET_DP_DC_OFF_HPD_HIGH() == _FALSE) || (GET_DP_RX0_HDCP_CHECK_ENABLE() == _TRUE))
#endif
            {
                ScalerDpRx0SetHotPlugEvent(_DP_HPD_LOW_RESET_AUX);
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            if(((GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT) && (PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)) ||
               ((GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT) && (PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)) ||
               ((GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT) && (PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH)))
            {
#if((_DP_HDMI_COMPATIBLE_MODE == _ON) || (_DP_POWER_OFF_HDCP_SUPPORT == _ON))
                return;
#endif

#if(_DP_DELL_D3_TEST_SUPPORT == _OFF)
                if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
#endif
                {
                    ScalerDpRx0SetHotPlugEvent(_DP_LONG_HPD_EVENT);
                }
            }
            else
            {
                // Use long HPD instead of assert to avoid causing HP EliteBook 840 fail to play bluray DVD due to the long HPD which width is less than ~250ms
                ScalerDpRx0SetHotPlugEvent(_DP_LONG_HPD_EVENT);
            }

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:
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
    if(ucInputPort == _D0_INPUT_PORT)
    {
        if(enumDpLaneCount > _D0_DP_MAIN_LINK_LANES)
        {
            enumDpLaneCount = _D0_DP_MAIN_LINK_LANES;
        }
    }
    else if(ucInputPort == _D1_INPUT_PORT)
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

    SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
    SET_DP_RX_CAPABILITY_SWITCHED();
}
//--------------------------------------------------
// Description  : DP Low Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpLowPowerProc(void)
{
    // Turn Off Output Clock
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, 0x00);

    // Turn Off SCLK PLL
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Set Data State to End State trigger Aux Int, Clear Aux INT Flag
    ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

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
}
//--------------------------------------------------
// Description  : Signal PreDetection for DP(Power Normal)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpNormalPreDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
    return ScalerDpRx0NormalPreDetect();
}
//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpPSPreDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
    return ScalerDpRx0PSPreDetect();
}
//--------------------------------------------------
// Description  : DP Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpResetProc(void)
{
    // Disable DP Fifo Under/OverFlow Watch Dog
    ScalerDpRx0SetFifoWD(_DISABLE);

    // Disable DP Fifo Under/OverFlow IRQ
    ScalerDpRx0SetFifoIRQ(_DISABLE);

    // Disable DP No Video Stream IRQ
    ScalerDpRx0SetNoVideoStreamIRQ(_DISABLE);
}
//--------------------------------------------------
// Description  : Initial Setting for DP Scanning Port(Power Normal)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpScanInitial(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    ScalerDpRx0MacInitial();

    ScalerDpRx0PhyInitial();

    CLR_DP_RX0_FAKE_LINK_TRAINING();
}
//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDpScanInputPort(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
    return ScalerDpRx0ScanInputPort();
}
//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpStableDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
    return ScalerDpRx0StableDetect();
}
//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : DP input port, _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpVersionSwitch(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort)
{
    ucInputPort = ucInputPort;

    SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);
    SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
    SET_DP_RX_CAPABILITY_SWITCHED();
}

//--------------------------------------------------
// Description  : HDCP Reset
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpHDCPUnplugReset(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    ScalerDpRx0HDCPUnplugReset();
}

//--------------------------------------------------
// Description  : Dp Main Link Quality Management
// Input Value  : Dx Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpMainLinkQualityManagement(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

#if(_DP_RX_ACTIVE_REDUCE_LANE_COUNT_SUPPORT == _ON)
    ScalerDpRx0MainLinkQualityManagement(ucInputPort);
#endif
}

//--------------------------------------------------
// Description  : Read DP Rx Error Count
// Input Value  : DP Input Port
// Output Value : DP 4 Lane Error Count & Valid Flag
//--------------------------------------------------
StructDpRxErrorCount ScalerDpRxGetErrorCount(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return ScalerDpRx0GetErrorCount();
}

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Restore DP Rx Fake LT Support Lane Count
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpRestoreFakeLTLaneCount(EnumSourceSearchPort enumSourceSearchPort)
{
    enumSourceSearchPort = enumSourceSearchPort;

    g_ucDpRx0FakeLTLaneCount = g_ucDpRx0FakeLTLaneCountBackUp;
}
#endif
#endif
