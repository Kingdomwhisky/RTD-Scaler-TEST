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
// ID Code      : ScalerDP_SeptPhy.c No.0000
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
#if(_DP_SUPPORT == _ON)
void ScalerDpEdidSwitch(BYTE ucInputPort);
void ScalerDpFakeLinkTrainingSetting(BYTE ucInputPort);
EnumDpPowerState ScalerDpGetPowerStatus(BYTE ucInputPort);
EnumDpLaneCount ScalerDpGetLaneCount(BYTE ucInputPort);
EnumDpLinkRate ScalerDpGetLinkRate(BYTE ucInputPort);
EnumDpVoltageSwingLevel ScalerDpGetLaneVoltageSwingLv(BYTE ucInputPort, EnumDpLane enumDpLane);
EnumDpPreEmphasisLevel ScalerDpGetLanePreEmpLv(BYTE ucInputPort, EnumDpLane enumDpLane);
bit ScalerDpGetSrcMstEnable(BYTE ucInputPort);
void ScalerDpSetHotPlugEvent(BYTE ucInputPort, EnumDpHotPlugAssertType enumHpdType);
void ScalerDpHotPlugHandler(void);
void ScalerDpJudgeHPDToggle(EnumPowerAction enumPowerAction);
void ScalerDpInitial(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
void ScalerDpLaneCountSwitch(BYTE ucInputPort, EnumDpLaneCount enumDpLaneCount);
void ScalerDpLowPowerProc(void);
void ScalerDpResetProc(void);
void ScalerDpTimerEventProc(EnumScalerTimerEventID enumEventID);
void ScalerDpVersionSwitch(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
bit ScalerDpCheckDCOffHpdToggle(EnumPowerAction enumPowerAction);
void ScalerDpHDCPUnplugReset(BYTE ucInputPort);
void ScalerDpMainLinkQualityManagement(BYTE ucInputPort);
StructDpRxErrorCount ScalerDpRxGetErrorCount(BYTE ucInputPort);

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
void ScalerDpRestoreFakeLTLaneCount(EnumSourceSearchPort enumSourceSearchPort);
#endif

#if(_DP_MST_SUPPORT == _ON)
void ScalerDpMstFakeOffDoneProc(void);
void ScalerDpMstReset(EnumDPMSTPort enumRxMstPort);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
void ScalerDpMstReset_EXINT0(EnumDPMSTPort enumRxMstPort);
#endif

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpHDCPHandler(void);
void ScalerDpHdcpResetUpstreamEventProc(void);
#endif
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
            SET_DP_RX_D1_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
            SET_DP_RX_D6_EDID_SWITCH();
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

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if((ucInputPort != _D0_INPUT_PORT) && (ucInputPort != _D6_INPUT_PORT))
#else
    if(ucInputPort != _D0_INPUT_PORT)
#endif
    {
        ScalerDpRx0FakeLTProtect();
    }

#endif

#if(_D1_DP_EXIST == _ON)

    if(ucInputPort != _D1_INPUT_PORT)
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

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
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

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:

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

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            return (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00));
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:

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

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT1 | _BIT0)));
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:

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

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT4 | _BIT3)) >> 3);
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:

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

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
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
#if(_D0_DP_EXIST == _ON)
    if(ucInputPort == _D0_INPUT_PORT)
    {
        ScalerDpRx0SetHotPlugEvent(enumHpdType);
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(ucInputPort == _D1_INPUT_PORT)
    {
        ScalerDpRx1SetHotPlugEvent(enumHpdType);
    }
#endif
}

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
        pstHpdSeq[1 + ucPortNum].enumPort = _D1_INPUT_PORT;
        ucPortNum ++;
    }

    CLR_DP_RX1_HOTPLUG_ASSERT_TYPE();
#endif

    if(ucPortNum == 0)
    {
        return;
    }

#if(_DP_LONG_HPD_MODE == _DP_LONG_HPD_DELAY_MODE)
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
#endif

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
#if(_D0_DP_EXIST == _ON)

            case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if(((GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT) && (ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)) ||
                   ((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (ScalerSyncDpCableStatus(_D6_INPUT_PORT) == _TRUE)))
#else
                if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
#endif
                {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                    if(GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_ON)
#endif
                    {
                        DebugMessageRx0("_D0_HOT_PLUG_LOW", 0);
                        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
                    }
                }

                break;
#endif

#if(_D1_DP_EXIST == _ON)

            case _D1_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
                {
                    DebugMessageRx1("_D1_HOT_PLUG_LOW", 0);
                    PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
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
#if(_D0_DP_EXIST == _ON)

            case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if(((GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT) && (ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)) ||
                   ((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (ScalerSyncDpCableStatus(_D6_INPUT_PORT) == _TRUE)))
#else
                if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
#endif
                {
#if(_DP_LONG_HPD_MODE == _DP_LONG_HPD_DELAY_MODE)
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
#endif

#if(_DP_LONG_HPD_MODE == _DP_LONG_HPD_TIMEREVENT_MODE)
                    if(pstHpdSeq[ucI].enumHpdTime > 0)
                    {
                        ScalerTimerReactiveTimerEvent(pstHpdSeq[ucI].enumHpdTime, _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                    }
                    else
#endif
                    {
                        ScalerDpRx0AfterHpdToggleProc();

                        PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
                    }
                }

                break;
#endif

#if(_D1_DP_EXIST == _ON)

            case _D1_INPUT_PORT:

                if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
                {
#if(_DP_LONG_HPD_MODE == _DP_LONG_HPD_DELAY_MODE)
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
#endif

#if(_DP_LONG_HPD_MODE == _DP_LONG_HPD_TIMEREVENT_MODE)
                    if(pstHpdSeq[ucI].enumHpdTime > 0)
                    {
                        ScalerTimerReactiveTimerEvent(pstHpdSeq[ucI].enumHpdTime, _SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);
                    }
                    else
#endif
                    {
                        ScalerDpRx1AfterHpdToggleProc();

                        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
                    }
                }

                break;
#endif
            default:
                break;
        }
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

#if(_DP_MST_SUPPORT == _ON)
                if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
                {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                    if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
                    {
                        ScalerDpRx0SetHotPlugEvent(_DP_HPD_LOW_RESET_AUX);
                    }
                }
                else
#endif
                {
#if((_DP_HDMI_COMPATIBLE_MODE == _ON) || (_DP_POWER_OFF_HDCP_SUPPORT == _ON))
                    if(GET_DP_DC_OFF_HPD_HIGH() == _FALSE)
#else
                    if((GET_DP_DC_OFF_HPD_HIGH() == _FALSE) || (GET_DP_RX0_HDCP_CHECK_ENABLE() == _TRUE))
#endif
                    {
                        ScalerDpRx0SetHotPlugEvent(_DP_HPD_LOW_RESET_AUX);
                    }
                }
#endif // End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)

#if(_DP_MST_SUPPORT == _ON)
                if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
                {
                    ScalerDpRx1SetHotPlugEvent(_DP_HPD_LOW_RESET_AUX);
                }
                else
#endif
                {
#if((_DP_HDMI_COMPATIBLE_MODE == _ON) || (_DP_POWER_OFF_HDCP_SUPPORT == _ON))
                    if(GET_DP_DC_OFF_HPD_HIGH() == _FALSE)
#else
                    if((GET_DP_DC_OFF_HPD_HIGH() == _FALSE) || (GET_DP_RX1_HDCP_CHECK_ENABLE() == _TRUE))
#endif
                    {
                        ScalerDpRx1SetHotPlugEvent(_DP_HPD_LOW_RESET_AUX);
                    }
                }
#endif // End of #if(_D1_DP_EXIST == _ON)
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

#if(_D0_DP_EXIST == _ON)

            // 2002h Has Been Read and Cancel Rx Mst Msg Finish during PS/ PD
            if(GET_DP_RX0_AUX_COMMAND_NO_REPLY() == _TRUE)
            {
                CLR_DP_RX0_AUX_COMMAND_NO_REPLY();

                ScalerDpRx0SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);
            }
            else if(enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL)
            {
#if(_DP_MST_SUPPORT == _ON)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) || (g_enumDpMSTCapablePort == _DP_MST_RX6_PORT))
#else
                if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
#endif
                {
                    if(enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL)
                    {
                        // Instead of _DP_HPD_ASSERTED, do the _DP_MST_LONG_HPD_EVENT to prevent the DC off/on toggled quickly.
                        ScalerDpRx0SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);
                    }
                }
                else
#endif
                {
                    if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
                    {
                        // Case of (GET_DP_DC_OFF_HPD_HIGH() == _TRUE), HPD remains high

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
                        // Case of ((GET_DP_DC_OFF_HPD_HIGH() == _FALSE) || (ScalerDpRx0HdcpCheckEnabled() == _TRUE)), DC off HPD low

                        // Use long HPD instead of assert to avoid causing HP EliteBook 840 fail to play bluray DVD due to the long HPD which width is less than ~250ms
                        ScalerDpRx0SetHotPlugEvent(_DP_LONG_HPD_EVENT);
                    }
                }
            }

#endif // End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)

            // 2002h Has Been Read and Cancel Rx Mst Msg Finish during PS/ PD
            if(GET_DP_RX1_AUX_COMMAND_NO_REPLY() == _TRUE)
            {
                CLR_DP_RX1_AUX_COMMAND_NO_REPLY();

                ScalerDpRx1SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);
            }
            else if(enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL)
            {
#if(_DP_MST_SUPPORT == _ON)
                if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
                {
                    if(enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL)
                    {
                        // Instead of _DP_HPD_ASSERTED, do the _DP_MST_LONG_HPD_EVENT to prevent the DC off/on toggled quickly.
                        ScalerDpRx1SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);
                    }
                }
                else
#endif
                {
                    if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
                    {
                        // Case of (GET_DP_DC_OFF_HPD_HIGH() == _TRUE), HPD remains high

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) || (_DP_POWER_OFF_HDCP_SUPPORT == _ON))
                        return;
#endif

#if(_DP_DELL_D3_TEST_SUPPORT == _OFF)
                        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
#endif
                        {
                            ScalerDpRx1SetHotPlugEvent(_DP_LONG_HPD_EVENT);
                        }
                    }
                    else
                    {
                        // Case of ((GET_DP_DC_OFF_HPD_HIGH() == _FALSE) || (ScalerDpRx1HdcpCheckEnabled() == _TRUE)), DC off HPD low

                        // Use long HPD instead of assert to avoid causing HP EliteBook 840 fail to play bluray DVD due to the long HPD which width is less than ~250ms
                        ScalerDpRx1SetHotPlugEvent(_DP_LONG_HPD_EVENT);
                    }
                }
            }

#endif // End of #if(_D1_DP_EXIST == _ON)

            break;

        case _POWER_ACTION_OFF_TO_FAKE_OFF:
        default:

            break;
    }
}

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
            ScalerDpRx1Initial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumFreeSyncSupport);
            break;
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
            ScalerDpRx6Initial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumFreeSyncSupport);
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

            if(enumDpLaneCount > _D1_DP_MAIN_LINK_LANES)
            {
                enumDpLaneCount = _D1_DP_MAIN_LINK_LANES;
            }

            SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:

            if(enumDpLaneCount > _D6_DP_MAIN_LINK_LANES)
            {
                enumDpLaneCount = _D6_DP_MAIN_LINK_LANES;
            }

            SET_DP_RX_D6_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
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

    // Turn Off Output Clock
    ScalerSetBit(PB8_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, 0x00);

    // Turn Off SCLK PLL
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

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

#if(_HDMI_CEC_SUPPORT == _OFF)
        // Disable GDI Bandgap
        ScalerGDIPhyBandgap(_OFF);
#endif
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

#if(_HDMI_CEC_SUPPORT == _OFF)
        // Disable GDI Bandgap
        ScalerGDIPhyBandgap(_OFF);
#endif

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
    ScalerSetBit(PB8_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, 0x00);

    // Turn Off SCLK PLL
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

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

#if(_HDMI_CEC_SUPPORT == _OFF)
        // Disable GDI Bandgap
        ScalerGDIPhyBandgap(_OFF);
#endif

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

#if(_DP_TX_SUPPORT == _ON)
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        ScalerDpTxForceIdlePatternSetting();
        ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE) // for Clone OOR Case
    {
        // Clear Exceed BW Flag for Clone Mode
        CLR_DP_TX_EXCEED_LINK_BANDWIDTH();
    }
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
#if(_D0_DP_EXIST == _ON)
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
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(((GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT) && (ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)) ||
               ((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (ScalerSyncDpCableStatus(_D6_INPUT_PORT) == _TRUE)))
#else
            if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
#endif
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

#if(_D1_DP_EXIST == _ON)
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

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
            if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
            {
                if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2) &&
                   (GET_DP_RX_D1_MARGIN_LINK_HBR2() == _TRUE))
                {
                    DebugMessageRx1("7. DP Margin Link Long HPD", 0);

                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    // When Define Extended Rx Cap Should Set DPCD 0x02201
                    ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, _DP_LINK_HBR);
#else
                    // When Define Extended Rx Cap Should Set DPCD 0x02201
                    g_ucDpRx1DPCD02201hValue = _DP_LINK_HBR;
#endif

                    ScalerDpRx1SetHotPlugEvent(_DP_HBR2_MARGIN_LINK_HPD_EVENT);
                }
                else
                {
                    ScalerDpRx1LinkStatusIRQ();
                }
            }
#else
            ScalerDpRx1LinkStatusIRQ();
#endif
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
    enumDpRxMstPort = enumDpRxMstPort;

    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)
        case _D0_INPUT_PORT:
            SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
#endif
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D1_DP_EXIST == _ON)
        case _D1_INPUT_PORT:
            SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
#endif
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
            SET_DP_RX_D6_PORT_TARGET_VERSION(enumDpVersion);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
#endif
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
// Description  : HDCP Reset
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpHDCPUnplugReset(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif

            ScalerDpRx0HDCPUnplugReset();

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:

            ScalerDpRx1HDCPUnplugReset();

            break;
#endif

        default:

            break;
    }
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
        case _D0_INPUT_PORT:

            g_ucDpRx0FakeLTLaneCount = g_ucDpRx0FakeLTLaneCountBackUp;
            break;

        case _D1_INPUT_PORT:
            g_ucDpRx1FakeLTLaneCount = g_ucDpRx1FakeLTLaneCountBackUp;
            break;

        default:
            break;
    }
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Proc DP HPD Toggle Behavior when MST Fake Off Timer Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstFakeOffDoneProc(void)
{
    CLR_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD();

#if(_D0_DP_EXIST == _ON)
    if(ScalerDpRx0HdcpCheckEnabled() == _TRUE)
    {
        SET_DP_RX0_HDCP_CHECK_ENABLE();
    }
    else
    {
        CLR_DP_RX0_HDCP_CHECK_ENABLE();
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(ScalerDpRx1HdcpCheckEnabled() == _TRUE)
    {
        SET_DP_RX1_HDCP_CHECK_ENABLE();
    }
    else
    {
        CLR_DP_RX1_HDCP_CHECK_ENABLE();
    }
#endif

    ScalerDpJudgeHPDToggle(_POWER_ACTION_NORMAL_TO_FAKE_OFF);
}

//--------------------------------------------------
// Description  : DP Mst Reset
// Input Value  : _DP_MST_RX0_PORT or _DP_MST_RX1_PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpMstReset(EnumDPMSTPort enumRxMstPort)
{
    if(enumRxMstPort == _DP_MST_NO_PORT)
    {
        return;
    }

// HW Reset-----------------------------------
#if(_D0_DP_EXIST == _ON)

    if(enumRxMstPort == _DP_MST_RX0_PORT)
    {
        DebugMessageRx0("DP Rx0 MST reset", 0);

        ScalerDpRx0MstReset();
    }
#endif

#if(_D1_DP_EXIST == _ON)

    if(enumRxMstPort == _DP_MST_RX1_PORT)
    {
        DebugMessageRx1("DP Rx1 MST reset", 0);

        ScalerDpRx1MstReset();
    }
#endif

    // Reset ST1_Source ~ ST5_Source
    ScalerDpRxMstClrStreamMuxBackup();

// FW Reset-----------------------------------

    // MSG Status Reset
    SET_DP_RX_MST_MODE_STATE(_DP_RX_MST_MODE_STATUS_NONE_MSG);
    SET_DP_RX_EVENT(_DP_RX_NONE_EVENT);

    // Free Request Pool Array
    SET_DP_REQUEST_POOL_FREE();

    // Free Reply Pool Array
    SET_DP_REPLY_POOL_FREE();

    // Free Reply Buffer
    SET_DP_RX_REPLY_BUF_FREE();

    // Clear Allocated Flag Manual Mode
    CLR_DP_RX_MANUAL_FORCE_SET_ACT();

    CLR_DP_RX_CANCEL_MSG_TIMEOUT_EVENT();

    ScalerDpRxMstClrStreamMuxBackup();

    // Reset Stream ID Mapping Table
    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        g_pucDpStreamToIdMapping[pData[0]] = 0;
    }

    // Clear Down Request MSG Proc Flags
    CLR_DP_RX_DOWN_REQUEST_ANAL();
    CLR_DP_RX_DOWN_REQ_BUF_RELEASE();
    SET_DP_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_DOWN_REQUEST_BUF0);
    CLR_DP_GEN_DOWN_REQUEST_MSG();
    CLR_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
    CLR_DP_RX_SELF_GEN_DOWN_REQUEST_MSG();

    // Clear Down Reply MSG Proc Flags
    CLR_DP_RX_DOWN_REPLY_READY();
    CLR_DP_RX_DOWN_REPLY_SET_HPD();
    CLR_DP_RX_DOWN_REPLY_BYPASS();
    CLR_DP_RX_DOWN_REPLY_DIRECTLY();
    CLR_REG_DP_RX_DOWN_REPLY_MSG_IS_READ();

#if(_DOWN_REPLY_MANUAL_MODE_SUPPORT == _ON)
    // Clear the Rx Down Reply MSG Segment Count No.
    g_ucDpDownReplyManualMsgCount = 0;
#endif

    // Clear Up Request MSG Proc Flags
    CLR_DP_RX_UP_REQUEST_READY();
    CLR_DP_RX_UP_REQUEST_ANAL();
    CLR_DP_RX_UP_REQUEST_BYPASS_DONE();
    CLR_DP_RX_UP_REQUEST_RETRY_NUM();
    CLR_DP_RX_UP_REQUEST_CRC_FAIL_RETRY_NUM();
    CLR_DP_RX_ILLEGAL_UP_REQUEST_MSG();
    CLR_DP_RX_SELF_GEN_UP_REQUEST_RETRY();
    CLR_DP_GEN_UP_REQUEST_MSG();

    // Clear Up Reply MSG Proc Flags
    CLR_DP_RX_UP_REPLY_BUF_RELEASE();
    SET_DP_RX_UP_REPLY_BUF_PRIORITY(_DP_UP_REPLY_BUF0);
    CLR_DP_RX_UP_REPLY_ANAL();
    CLR_DP_RX_UP_REPLY_DIRECTLY();

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
    g_enumDpMSTCapablePort = _DP_MST_NO_PORT;

    // Sync MST Target Port
    SET_DP_RX_TARGET_MST_PORT(g_enumDpMSTCapablePort);
#endif

// Tx Reset-----------------------------------

    // Disable MST to SST
    SET_DP_RX_MST2SST_ENABLE(_DISABLE);

#if(_DP_TX_SUPPORT == _ON)

    ScalerDpTxMstReset();

#endif
}

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Mst Reset
// Input Value  : _DP_MST_RX0_PORT or _DP_MST_RX1_PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpMstReset_EXINT0(EnumDPMSTPort enumRxMstPort) using 1
{
    if(enumRxMstPort == _DP_MST_NO_PORT)
    {
        return;
    }

// HW Reset-----------------------------------
#if(_D0_DP_EXIST == _ON)

    if(enumRxMstPort == _DP_MST_RX0_PORT)
    {
        ScalerDpRx0MstReset_EXINT0();
    }
#endif

#if(_D1_DP_EXIST == _ON)

    if(enumRxMstPort == _DP_MST_RX1_PORT)
    {
        ScalerDpRx1MstReset_EXINT0();
    }
#endif

    // Reset ST1_Source ~ ST5_Source
    ScalerDpRxMstClrStreamMuxBackup_EXINT0();

// FW Reset-----------------------------------

    // MSG Status Reset
    SET_DP_RX_MST_MODE_STATE(_DP_RX_MST_MODE_STATUS_NONE_MSG);
    SET_DP_RX_EVENT(_DP_RX_NONE_EVENT);

    // Free Request Pool Array
    SET_DP_REQUEST_POOL_FREE();

    // Free Reply Pool Array
    SET_DP_REPLY_POOL_FREE();

    // Free Reply Buffer
    SET_DP_RX_REPLY_BUF_FREE();

    // Clear Allocated Flag Manual Mode
    CLR_DP_RX_MANUAL_FORCE_SET_ACT();

    CLR_DP_RX_CANCEL_MSG_TIMEOUT_EVENT();

    ScalerDpRxMstClrStreamMuxBackup_EXINT0();

    // Reset Stream ID Mapping Table
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 5; pData_EXINT[0]++)
    {
        g_pucDpStreamToIdMapping[pData_EXINT[0]] = 0;
    }

    // Clear Down Request MSG Proc Flags
    CLR_DP_RX_DOWN_REQUEST_ANAL();
    CLR_DP_RX_DOWN_REQ_BUF_RELEASE();
    SET_DP_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_DOWN_REQUEST_BUF0);
    CLR_DP_GEN_DOWN_REQUEST_MSG();
    CLR_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
    CLR_DP_RX_SELF_GEN_DOWN_REQUEST_MSG();

    // Clear Down Reply MSG Proc Flags
    CLR_DP_RX_DOWN_REPLY_READY();
    CLR_DP_RX_DOWN_REPLY_SET_HPD();
    CLR_DP_RX_DOWN_REPLY_BYPASS();
    CLR_DP_RX_DOWN_REPLY_DIRECTLY();
    CLR_REG_DP_RX_DOWN_REPLY_MSG_IS_READ();

#if(_DOWN_REPLY_MANUAL_MODE_SUPPORT == _ON)
    // Clear the Rx Down Reply MSG Segment Count No.
    g_ucDpDownReplyManualMsgCount = 0;
#endif

    // Clear Up Request MSG Proc Flags
    CLR_DP_RX_UP_REQUEST_READY();
    CLR_DP_RX_UP_REQUEST_ANAL();
    CLR_DP_RX_UP_REQUEST_BYPASS_DONE();
    CLR_DP_RX_UP_REQUEST_RETRY_NUM();
    CLR_DP_RX_UP_REQUEST_CRC_FAIL_RETRY_NUM();
    CLR_DP_RX_ILLEGAL_UP_REQUEST_MSG();
    CLR_DP_RX_SELF_GEN_UP_REQUEST_RETRY();
    CLR_DP_GEN_UP_REQUEST_MSG();

    // Clear Up Reply MSG Proc Flags
    CLR_DP_RX_UP_REPLY_BUF_RELEASE();
    SET_DP_RX_UP_REPLY_BUF_PRIORITY(_DP_UP_REPLY_BUF0);
    CLR_DP_RX_UP_REPLY_ANAL();
    CLR_DP_RX_UP_REPLY_DIRECTLY();

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
    g_enumDpMSTCapablePort = _DP_MST_NO_PORT;

    // Sync MST Target Port
    SET_DP_RX_TARGET_MST_PORT(g_enumDpMSTCapablePort);
#endif

// Tx Reset-----------------------------------

#if(_DP_TX_SUPPORT == _ON)

    ScalerDpTxMstReset_EXINT0();

#endif
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx HDCP Auth Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpHDCPHandler(void)
{
    ScalerDpHdcpResetUpstreamEventProc();

#if(_D0_DP_EXIST == _ON)
    ScalerDpRx0HDCPHandler();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpRx0Hdcp2RepeaterHandler();
#endif
#endif

#if(_D1_DP_EXIST == _ON)
    ScalerDpRx1HDCPHandler();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpRx1Hdcp2RepeaterHandler();
#endif
#endif

    ScalerDpTxHDCPHandler();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpTxHdcp2Handler();
#endif
}

//--------------------------------------------------
// Description  : Dp Rx HDCP Auth Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpHdcpResetUpstreamEventProc(void)
{
#if(_D0_DP_EXIST == _ON)
    CLR_DP_RX0_HDCP_UPSTREAM_EVENT();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    CLR_DP_RX0_HDCP2_UPSTREAM_EVENT();
#endif
#endif

#if(_D1_DP_EXIST == _ON)
    CLR_DP_RX1_HDCP_UPSTREAM_EVENT();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    CLR_DP_RX1_HDCP2_UPSTREAM_EVENT();
#endif
#endif
}
#endif // #if(_DP_TX_SUPPORT == _ON)
#endif // #if(_DP_MST_SUPPORT == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)
