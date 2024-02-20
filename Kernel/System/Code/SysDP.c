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
// ID Code      : SysDP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_DP__

#include "SysInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//--------------------------------------------------
// Definitions of mode search status
//--------------------------------------------------


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
void SysDpRxHandler(void);
void SysDpCableDetection(void);
bit SysDpCableStatus(EnumSourceSearchPort enumInputPort);
void SysDpJudgeHPDToggle(void);
void SysDpDcOffHPDToggleProc(EnumPowerAction enumSwitch);
bit SysDpSourceKeepDetectingCheck(void);
bit SysDpCheckTwoChipDataExchangePort(BYTE ucInputPort);
#endif

#if(_DP_TX_SUPPORT == _ON)
void SysDpTxHandler(void);
bit SysDpTxCloneOutputStatus(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
void SysDpTxHdcp2Handler(void);
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
void SysDpMstHandler(void);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
void SysDpMstAutoSwitch(void);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpRxHandler(void)
{
    SysDpCableDetection();

#if(_DP_TX_SUPPORT == _ON)
    ScalerSyncDpTxHdcpUpstreamSwitchProc(SysSourceGetInputPort());
    ScalerSyncDpRxSinkCountUpdateProc(SysSourceGetInputPort());
#endif

    if((GET_MODE_STATE() == _MODE_STATUS_SEARCH) || (GET_MODE_STATE() == _MODE_STATUS_NOSIGNAL) || (GET_MODE_STATE() == _MODE_STATUS_FACTORY))
    {
        ScalerDpMainLinkQualityManagement(SysSourceGetInputPort());
    }

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
    if((GET_MODE_STATE() == _MODE_STATUS_SEARCH) || (GET_MODE_STATE() == _MODE_STATUS_NOSIGNAL) || (GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING))
    {
        SysDpMstAutoSwitch();
    }
#endif

    ScalerSyncDpCapabilitySwitchProc();

    // DP Judge HPD Toggle
    SysDpJudgeHPDToggle();

#if((_DP_TX_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
    {
        ScalerSyncDpHdcpRepeaterCapableProc(SysSourceGetInputPort(), GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())));
    }
#endif

    ScalerDpHotPlugHandler();

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)

    // Set Embedded switch select to the target after HPD low of current port toggled by HotPlugHandler
    if(GET_DP_EMBEDDED_SWITCH_SELECT() != GET_DP_EMBEDDED_SWITCH_TARGET())
    {
        ScalerDpEmbeddedSwitchSetting(GET_DP_EMBEDDED_SWITCH_TARGET());
    }
#endif

#if(_DP_TX_SUPPORT == _ON)
    if(GET_MODE_STATE() == _MODE_STATUS_ACTIVE)
    {
        ScalerDpTxCloneOutputProc(SysSourceGetInputPort(), GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())), SysDpTxCloneOutputStatus());
    }
#endif
}

//--------------------------------------------------
// Description  : DP Cable Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpCableDetection(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP))
    if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
    {
        if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) != SysDpCableStatus(_D0_INPUT_PORT))
        {
            if(SysDpCableStatus(_D0_INPUT_PORT) == _TRUE)
            {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
                {
                    if((GET_DP_DC_OFF_HPD_HIGH() == _ON) || (SysPowerGetPowerStatus() != _POWER_STATUS_OFF))
                    {
#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                        if(!((SysPowerGetPowerStatus() == _POWER_STATUS_OFF) && (ScalerDpRxMstGetMstCapability(_D0_INPUT_PORT) == _TRUE)))
#else
                        if(!((SysPowerGetPowerStatus() == _POWER_STATUS_OFF) && (UserCommonInterfaceGetDpMstCapablePort() == _DP_MST_RX0_PORT)))
#endif
                        {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                            DebugMessageSystem("HPD - High Event", SysTypeCGetAltModeReady(_D0_INPUT_PORT));
#endif
                            ScalerTimerReactiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                        }
                    }
                }
            }
            else
            {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
                {
#if(_DP_MST_SUPPORT == _ON)
                    // Fake Off to Off while MST port unplug
                    if((SysPowerGetPowerStatus() == _POWER_STATUS_OFF) && (GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD() == _TRUE))
                    {
                        if(ScalerDpRxMstGetCapablePort() == _DP_MST_RX0_PORT)
                        {
                            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);

                            ScalerDpMstFakeOffDoneProc();

                            SET_TARGET_POWER_STATUS(_POWER_STATUS_OFF);
                        }
                    }

                    // Cable Unplug Reset
                    ScalerDpRxMstCableUnplugReset(_D0_INPUT_PORT);

                    // Reset MST Backup
                    ScalerDpRxMstInfoBackup(_D0_INPUT_PORT, _DP_MST_BACKUP_INFO_RESET);
#endif

#if(_AUDIO_SUPPORT == _ON)
                    SysAudioDpAudioSecDataResetProc(_D0_INPUT_PORT);
#else
                    ScalerDpSecDataReset(_D0_INPUT_PORT);
#endif
                    ScalerDpSetHotPlugEvent(_D0_INPUT_PORT, _DP_HPD_LOW);

#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                    DebugMessageSystem("HPD - Low", SysTypeCGetAltModeReady(_D0_INPUT_PORT));
#endif

                    ScalerDpHDCPUnplugReset(_D0_INPUT_PORT);
                }
            }

            ScalerSyncDpSetCableStatus(_D0_INPUT_PORT, SysDpCableStatus(_D0_INPUT_PORT));
        }

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if((GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_DOWN) && (GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT))
        {
            ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
        }
#elif((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE != _DP_EMBEDDED_SWITCH_NONE))
        if((GET_DP_EMBEDDED_SWITCH_EVENT() == _TRUE) && (GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT))
        {
            ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
            SET_DP_EMBEDDED_SWITCH_EVENT(_FALSE);
        }
#endif

#if(_DP_MST_SUPPORT == _ON)
        ScalerDpAuxChPowerStatusCheck(_D0_INPUT_PORT, ScalerSyncDpCableStatus(_D0_INPUT_PORT));
#endif
    }
#endif // End of #if(_D0_DP_SUPPORT == _ON)

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP))
    if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
#endif
    {
        if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) != SysDpCableStatus(_D1_INPUT_PORT))
        {
            if(SysDpCableStatus(_D1_INPUT_PORT) == _TRUE)
            {
                if((GET_DP_DC_OFF_HPD_HIGH() == _ON) || (SysPowerGetPowerStatus() != _POWER_STATUS_OFF))
                {
#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                    if(!((SysPowerGetPowerStatus() == _POWER_STATUS_OFF) && (ScalerDpRxMstGetMstCapability(_D1_INPUT_PORT) == _TRUE)))
#else
                    if(!((SysPowerGetPowerStatus() == _POWER_STATUS_OFF) && (UserCommonInterfaceGetDpMstCapablePort() == _DP_MST_RX1_PORT)))
#endif
                    {
#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                        DebugMessageSystem("HPD - High Event", SysTypeCGetAltModeReady(_D1_INPUT_PORT));
#endif
                        ScalerTimerReactiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);
                    }
                }
            }
            else
            {
#if(_DP_MST_SUPPORT == _ON)
                // Fake Off to Off while MST port unplug
                if((SysPowerGetPowerStatus() == _POWER_STATUS_OFF) && (GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD() == _TRUE))
                {
                    if(ScalerDpRxMstGetCapablePort() == _DP_MST_RX1_PORT)
                    {
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);

                        ScalerDpMstFakeOffDoneProc();

                        SET_TARGET_POWER_STATUS(_POWER_STATUS_OFF);
                    }
                }

                // Cable Unplug Reset
                ScalerDpRxMstCableUnplugReset(_D1_INPUT_PORT);

                // Reset MST Backup
                ScalerDpRxMstInfoBackup(_D1_INPUT_PORT, _DP_MST_BACKUP_INFO_RESET);
#endif

#if(_AUDIO_SUPPORT == _ON)
                SysAudioDpAudioSecDataResetProc(_D1_INPUT_PORT);
#else
                ScalerDpSecDataReset(_D1_INPUT_PORT);
#endif
                ScalerDpSetHotPlugEvent(_D1_INPUT_PORT, _DP_HPD_LOW);

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                DebugMessageSystem("HPD - Low", SysTypeCGetAltModeReady(_D1_INPUT_PORT));
#endif

                ScalerDpHDCPUnplugReset(_D1_INPUT_PORT);
            }

            ScalerSyncDpSetCableStatus(_D1_INPUT_PORT, SysDpCableStatus(_D1_INPUT_PORT));
        }

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE != _DP_EMBEDDED_SWITCH_NONE))
        if((GET_DP_EMBEDDED_SWITCH_EVENT() == _TRUE) && (GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT))
        {
            ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);
            SET_DP_EMBEDDED_SWITCH_EVENT(_FALSE);
        }
#endif

#if(_DP_MST_SUPPORT == _ON)
        ScalerDpAuxChPowerStatusCheck(_D1_INPUT_PORT, ScalerSyncDpCableStatus(_D1_INPUT_PORT));
#endif
    }
#endif // End of #if(_D1_DP_SUPPORT == _ON)

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP))
    if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT)
#endif
    {
        if(ScalerSyncDpCableStatus(_D2_INPUT_PORT) != SysDpCableStatus(_D2_INPUT_PORT))
        {
            if(SysDpCableStatus(_D2_INPUT_PORT) == _TRUE)
            {
                if((GET_DP_DC_OFF_HPD_HIGH() == _ON) || (SysPowerGetPowerStatus() != _POWER_STATUS_OFF))
                {
                    ScalerTimerReactiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX2_HOTPLUG_ASSERTED);
                }
            }
            else
            {
#if(_DP_MST_SUPPORT == _ON)
                // Cable Unplug Reset
                ScalerDpRxMstCableUnplugReset(_D2_INPUT_PORT);

                // Reset MST Backup
                ScalerDpRxMstInfoBackup(_D2_INPUT_PORT, _DP_MST_BACKUP_INFO_RESET);
#endif

#if(_AUDIO_SUPPORT == _ON)
                SysAudioDpAudioSecDataResetProc(_D2_INPUT_PORT);
#else
                ScalerDpSecDataReset(_D2_INPUT_PORT);
#endif
                ScalerDpSetHotPlugEvent(_D2_INPUT_PORT, _DP_HPD_LOW);

                ScalerDpHDCPUnplugReset(_D2_INPUT_PORT);
            }

            ScalerSyncDpSetCableStatus(_D2_INPUT_PORT, SysDpCableStatus(_D2_INPUT_PORT));
        }

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE != _DP_EMBEDDED_SWITCH_NONE))
        if((GET_DP_EMBEDDED_SWITCH_EVENT() == _TRUE) && (GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT))
        {
            ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX2_HOTPLUG_ASSERTED);
            SET_DP_EMBEDDED_SWITCH_EVENT(_FALSE);
        }
#endif
    }
#endif // End of #if(_D2_DP_SUPPORT == _ON)

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
    if(ScalerSyncDpCableStatus(_D6_INPUT_PORT) != SysDpCableStatus(_D6_INPUT_PORT))
    {
        if(SysDpCableStatus(_D6_INPUT_PORT) == _TRUE)
        {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
#endif
            {
                if((GET_DP_DC_OFF_HPD_HIGH() == _ON) || (SysPowerGetPowerStatus() != _POWER_STATUS_OFF))
                {
#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                    if(!((SysPowerGetPowerStatus() == _POWER_STATUS_OFF) && (ScalerDpRxMstGetMstCapability(_D6_INPUT_PORT) == _TRUE)))
#else
                    if(!((SysPowerGetPowerStatus() == _POWER_STATUS_OFF) && (UserCommonInterfaceGetDpMstCapablePort() == _DP_MST_RX0_PORT)))
#endif
                    {
#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                        DebugMessageSystem("HPD - High Event", SysTypeCGetAltModeReady(_D6_INPUT_PORT));
#endif
                        ScalerTimerReactiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                    }
                }
            }
        }
        else
        {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
#endif
            {
#if((_DP_MST_SUPPORT == _ON) && ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
                // Fake Off to Off while MST port unplug
                if((SysPowerGetPowerStatus() == _POWER_STATUS_OFF) && (GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD() == _TRUE))
                {
                    if(ScalerDpRxMstGetCapablePort() == _DP_MST_RX0_PORT)
                    {
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);

                        ScalerDpMstFakeOffDoneProc();

                        SET_TARGET_POWER_STATUS(_POWER_STATUS_OFF);
                    }
                }

                // Cable Unplug Reset
                ScalerDpRxMstCableUnplugReset(_D0_INPUT_PORT);

                // Reset MST Backup
                ScalerDpRxMstInfoBackup(_D6_INPUT_PORT, _DP_MST_BACKUP_INFO_RESET);
#endif

#if(_AUDIO_SUPPORT == _ON)
                SysAudioDpAudioSecDataResetProc(_D0_INPUT_PORT);
#else
                ScalerDpSecDataReset(_D0_INPUT_PORT);
#endif
                ScalerDpSetHotPlugEvent(_D0_INPUT_PORT, _DP_HPD_LOW);

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                DebugMessageSystem("HPD - Low", SysTypeCGetAltModeReady(_D6_INPUT_PORT));
#endif

                ScalerDpHDCPUnplugReset(_D0_INPUT_PORT);
            }
        }

        ScalerSyncDpSetCableStatus(_D6_INPUT_PORT, SysDpCableStatus(_D6_INPUT_PORT));
    }

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_DOWN))
    {
        ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
    }
#endif

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpAuxChPowerStatusCheck(_D6_INPUT_PORT, ScalerSyncDpCableStatus(_D6_INPUT_PORT));
#endif
#endif // End of #if(_D6_DP_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : DP Port Cable Status
// Input Value  : enumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit SysDpCableStatus(EnumSourceSearchPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

#if(_D0_DP_REPEATER_TYPE == _REPEATER_RTS_TRANSLATOR)
            return _TRUE;
#endif

#if(_DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW == _ON)
            if((UserInterfaceGetDpMstTargetPort() != _DP_MST_NO_PORT) && (SysSourceGetInputPort() != _D0_INPUT_PORT))
            {
                return _FALSE;
            }
#endif

#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            return SysTypeCGetAltModeReady(_D0_INPUT_PORT);
#else
            return GET_D0_CABLE_STATUS();
#endif
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

#if(_D1_DP_REPEATER_TYPE == _REPEATER_RTS_TRANSLATOR)
            return _TRUE;
#endif

#if(_DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW == _ON)
            if((UserInterfaceGetDpMstTargetPort() != _DP_MST_NO_PORT) && (SysSourceGetInputPort() != _D1_INPUT_PORT))
            {
                return _FALSE;
            }
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            return SysTypeCGetAltModeReady(_D1_INPUT_PORT);
#else
            return GET_D1_CABLE_STATUS();
#endif
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

#if(_DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW == _ON)
            if((UserInterfaceGetDpMstTargetPort() != _DP_MST_NO_PORT) && (SysSourceGetInputPort() != _D2_INPUT_PORT))
            {
                return _FALSE;
            }
#endif
            return GET_D2_CABLE_STATUS();
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:

#if(_DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW == _ON)
            if((UserInterfaceGetDpMstTargetPort() != _DP_MST_NO_PORT) && (SysSourceGetInputPort() != _D6_INPUT_PORT))
            {
                return _FALSE;
            }
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            return SysTypeCGetAltModeReady(_D6_INPUT_PORT);
#else
            return GET_D6_CABLE_STATUS();
#endif
#endif
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Decide DP Rx Judge HPD Toggle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpJudgeHPDToggle(void)
{
    if(GET_DP_DC_OFF_HPD_TOGGLE_FLAG() == _TRUE)
    {
        CLR_DP_DC_OFF_HPD_TOGGLE_FLAG();

        switch(GET_POWER_STATUS())
        {
            case _POWER_STATUS_OFF:

                ScalerDpJudgeHPDToggle(_POWER_ACTION_NORMAL_TO_OFF);
                break;

            case _POWER_STATUS_NORMAL:

                if(GET_POWER_SWITCH_TO_FAKE_OFF() == _TRUE)
                {
                    ScalerDpJudgeHPDToggle(_POWER_ACTION_NORMAL_TO_FAKE_OFF);
                }
                else
                {
#if(_DP_MST_SUPPORT == _ON)
                    if(GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD() == _FALSE)
#endif
                    {
                        ScalerDpJudgeHPDToggle(_POWER_ACTION_OFF_TO_NORMAL);
                    }
                }

                break;

            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Decide DP Rx Dc Off Set HPD Toggle Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpDcOffHPDToggleProc(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:

#if(_DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT == _ON)
            if(UserInterfaceGetDpDcOnHpdMode() == _DP_HPD_TOGGLE_NORMAL)
#endif
            {
                SET_DP_DC_OFF_HPD_TOGGLE_FLAG();
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check DP Source Keep Detecting or Not
// Input Value  : None
// Output Value : _TRUE: keep detecting, _FALSE: stop detecting
//--------------------------------------------------
bit SysDpSourceKeepDetectingCheck(void)
{
#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
    if((GET_AUDIO_PLAYING_ALONE() == _TRUE) && (UserInterfaceGetAudioSource() == _DIGITAL_AUDIO))
    {
        return _TRUE;
    }
#endif

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
    if((GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_FIXED_PORT) &&
       (GET_SOURCE_JUDGE(g_ucSearchIndex) == _FALSE) &&
       (SysSourceGetInputPort() == ScalerDpRxMstGetInputPort(ScalerDpRxMstGetCapablePort())))
    {
        if((ScalerDpRxMstGetSrcMsgEnable(SysSourceGetInputPort()) == _TRUE) &&
           (ScalerDpGetPowerStatus(SysSourceGetInputPort()) == _DP_POWER_NORMAL))
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
//--------------------------------------------------
// Description  : Check if Specific ucInputPort is TwoChip Data Exchange Port or Not
// Input Value  : ucInputPort
// Output Value : TwoChip Data Exchange Port _TRUE / _FALSE
//--------------------------------------------------
bit SysDpCheckTwoChipDataExchangePort(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE))
            return _TRUE;
#else
            return _FALSE;
#endif
            break;

        case _D1_INPUT_PORT:
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE))
            return _TRUE;
#else
            return _FALSE;
#endif
            break;

        default:

            return _FALSE;

            break;
    }
    return _FALSE;
}
#endif // End of #if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)

#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTxHandler(void)
{
    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
    {
        // HPD Detection Function
        ScalerDpTxHPDProc();

        ScalerDpTxJudgeHandler();

        ScalerDpTxModeHandler();

#if(_DP_MST_SUPPORT == _ON)
        ScalerDpHDCPHandler();
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        SysDpTxHdcp2Handler();
#endif
    }
}

//--------------------------------------------------
// Description  : Decide whether to Clone output to DP Tx
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysDpTxCloneOutputStatus(void)
{
    if(UserInterfaceGetDpCloneOutputStatus() == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerSyncDpTxCloneOutputPortCheck(SysSourceGetInputPort()) == _FALSE)
    {
        return _FALSE;
    }

    if(GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP)
    {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _OFF))
        if(SysSourceGetInputPort() == _D0_INPUT_PORT)
        {
            return _FALSE;
        }
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _OFF))
        if(SysSourceGetInputPort() == _D1_INPUT_PORT)
        {
            return _FALSE;
        }
#endif
    }

    return _TRUE;
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx MST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTxHdcp2Handler(void)
{
    BYTE pucDpTxHdcp2Key[384];

    if(GET_DP_TX_HDCP2_LOAD_KEY_EN() == _TRUE)
    {
        CLR_DP_TX_HDCP2_LOAD_KEY_EN();

        ScalerDpTxHdcp2DcpLlcRsaInit();

        UserCommonInterfaceGetDpTxHdcp2RRMODN(0, 0x180, pucDpTxHdcp2Key);
        ScalerDpTxHdcp2LoadKeyProc(_DP_TX_HDCP2_KEY_RRMODN, pucDpTxHdcp2Key);

        UserCommonInterfaceGetDpTxHdcp2DcpLlcN(0, 0x180, pucDpTxHdcp2Key);
        ScalerDpTxHdcp2LoadKeyProc(_DP_TX_HDCP2_KEY_DCP_LLC_N, pucDpTxHdcp2Key);

        ScalerDpTxHdcp2LoadKeyProc(_DP_TX_HDCP2_KEY_EKEY1, pucDpTxHdcp2Key);

        UserCommonInterfaceGetDpTxHdcp2EKey(0, 0x80, pucDpTxHdcp2Key);
        ScalerDpTxHdcp2LoadKeyProc(_DP_TX_HDCP2_KEY_EKEY2, pucDpTxHdcp2Key);

        UserCommonInterfaceGetDpTxHdcp2NPinv(0, 0x04, pucDpTxHdcp2Key);
        ScalerDpTxHdcp2LoadKeyProc(_DP_TX_HDCP2_KEY_NPINV, pucDpTxHdcp2Key);

        SET_DP_TX_HDCP2_LOAD_KEY_FINISH();
    }
}
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx MST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpMstHandler(void)
{
    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
    {
        ScalerDpRxMstHandler();

#if(_DP_TX_SUPPORT == _ON)
        ScalerDpTxMstHandler();
#endif

        ScalerDpRxMstStreamsHandler();

        ScalerSyncDpSourceWritePowerUpProc();

        if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
        {
            ScalerDpRxMstStreamMuxChangeHandler();
        }
    }
}

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP MST Auto Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpMstAutoSwitch(void)
{
    bit bMstForceSwitchEn = _FALSE;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    // For some of HP scan type, the first loop of source search for checking monitor status
    if(SysSourceHpGetMonitorStatusCheckProcessing() == _TRUE)
    {
        if(GET_SOURCE_HP_PORT_SWITCH_TARGET() == g_ucSearchIndex)
        {
            bMstForceSwitchEn = _TRUE;
        }
        else
        {
            return;
        }
    }
#endif

    if((GET_SOURCE_JUDGE(g_ucSearchIndex) == _TRUE) || (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT) || (bMstForceSwitchEn == _TRUE))
    {
        // Disable other ports
#if(_D0_DP_EXIST == _ON)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if((SysSourceGetInputPort() != _D0_INPUT_PORT) && (SysSourceGetInputPort() != _D6_INPUT_PORT))
#else
        if(SysSourceGetInputPort() != _D0_INPUT_PORT)
#endif
        {
            ScalerDpRxMstCapabilitySwitch(_D0_INPUT_PORT, _DISABLE);
        }
#endif

#if(_D1_DP_EXIST == _ON)
        if(SysSourceGetInputPort() != _D1_INPUT_PORT)
        {
            ScalerDpRxMstCapabilitySwitch(_D1_INPUT_PORT, _DISABLE);
        }
#endif

        if(ScalerDpRxMstGetInputPort(ScalerDpRxMstGetCapablePort()) != SysSourceGetInputPort())
        {
            ScalerDpMstReset(ScalerDpRxMstGetCapablePort());
        }
    }

    // Input port has the right to become a MST capable port
    if(SysSourceGetInputPort() == ScalerDpRxMstGetInputPort(UserCommonInterfaceGetDpMstCapablePort()))
    {
        ScalerDpRxMstCapabilitySwitch(SysSourceGetInputPort(), _ENABLE);
    }
    else
    {
        ScalerDpRxMstCapabilitySwitch(SysSourceGetInputPort(), _DISABLE);
    }
}
#endif
#endif
