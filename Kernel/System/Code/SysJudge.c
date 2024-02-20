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
// ID Code      : SysJudge.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_JUDGE__

#include "SysInclude.h"

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
BYTE xdata g_ucSignalUnstable = 0;
BYTE xdata g_ucIssueState = 0;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysJudgeHandler(void);
bit SysJudgeCheckStatus(void);
bit SysJudgeStateChangeEvent(EnumModeStatus enumModeState);
void SysJudgeModeResetProc(void);
WORD SysJudgeGetActiveWaitTime(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Judge Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysJudgeHandler(void)
{
    CLR_MODE_STATE_CHANGE_OTHERS();

    switch(SysPowerGetPowerStatus())
    {
        case _POWER_STATUS_OFF:

            if(GET_MODE_STATE() != _MODE_STATUS_POWER_OFF)
            {
                if(SysJudgeStateChangeEvent(_MODE_STATUS_POWER_OFF) == _FALSE)
                {
                    break;
                }
            }

            break;

        case _POWER_STATUS_SAVING:

            if(GET_MODE_STATE() != _MODE_STATUS_POWER_SAVING)
            {
                if(SysJudgeStateChangeEvent(_MODE_STATUS_POWER_SAVING) == _FALSE)
                {
                    break;
                }
            }

            break;

        case _POWER_STATUS_NORMAL:

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if(ScalerSyncGetUrgentEventFlg() == _TRUE)
            {
                ScalerSyncClrUrgentEventFlg();

                if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSIGNAL_STATE) == _TRUE)
                {
                    ScalerTimerReactiveTimerEvent(SEC(1), _SYSTEM_TIMER_EVENT_JUDGE_NOSIGNAL_STATE);
                }

                if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE) == _TRUE)
                {
                    if(GET_MODE_STATE() == _MODE_STATUS_DISPLAY_SETTING)
                    {
                        ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                    }
                }
            }
#endif

            switch(GET_MODE_STATE())
            {
                case _MODE_STATUS_POWER_OFF:

                    if(SysJudgeStateChangeEvent(_MODE_STATUS_INITIAL) == _FALSE)
                    {
                        break;
                    }

                    break;

                case _MODE_STATUS_INITIAL:

                    if(SysJudgeStateChangeEvent(_MODE_STATUS_SEARCH) == _FALSE)
                    {
                        return;
                    }

                    return;

                    break;

                case _MODE_STATUS_SEARCH:

                    if(UserInterfaceGetLogoStatus() == _TRUE)
                    {
                        return;
                    }

                    if(GET_SOURCE_JUDGE(g_ucSearchIndex) == _TRUE)
                    {
                        // If Timing can't be confirmed for 1 sec, switch to No Support State
                        ScalerTimerActiveTimerEvent(SEC(1), _SYSTEM_TIMER_EVENT_JUDGE_NOSIGNAL_STATE);

                        if(SysModeGetTimingConfirm() == _TRUE)
                        {
                            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSIGNAL_STATE);

                            if(UserCommonInterfaceCheckNoSupport() == _FALSE)
                            {
                                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

                                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_SETTING) == _FALSE)
                                {
                                    break;
                                }
                            }
                            else
                            {
                                ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                            }
                        }
                    }
                    else if(GET_SOURCE_SWITCH_FINISH() == _TRUE)  // If Search Finish, Switch to no signal
                    {
                        if(SysJudgeStateChangeEvent(_MODE_STATUS_NOSIGNAL) == _FALSE)
                        {
                            break;
                        }
                        else
                        {
                            CLR_SOURCE_SWITCH_FINISH();
                        }
                    }

                    break;

                case _MODE_STATUS_DISPLAY_SETTING:

                    if(((SysModeGetActiveReady() == _TRUE)) && (UserCommonInterfaceReadyForActive() == _TRUE))
                    {
                        if(SysJudgeStateChangeEvent(_MODE_STATUS_ACTIVE) == _FALSE)
                        {
                            break;
                        }
                        else
                        {
                            CLR_MODE_ACTIVE_READY();
                        }
                    }
                    else
                    {
                        if(SysModeGetDisplaySettingReady() == _TRUE)
                        {
                            // Check Whether to Support Current D Clk
                            if(UserInterfaceGetDclkNoSupportStatus() == _TRUE)
                            {
                                ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                            }
                            else
                            {
                                ScalerTimerActiveTimerEvent(SysJudgeGetActiveWaitTime(), _SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);
                            }
                        }
                        else
                        {
                            // If Display Setting can't be Ready for 2 sec, switch to No Support State
                            ScalerTimerActiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                        }
                    }

                    break;

                case _MODE_STATUS_ACTIVE:

                    break;

                case _MODE_STATUS_NOSUPPORT:

                    break;

                case _MODE_STATUS_NOSIGNAL:
                case _MODE_STATUS_POWER_SAVING:

                    if(SysModeGetTimingConfirm() == _TRUE)
                    {
                        UserCommonInterfaceOsdResetProc();

                        if(UserCommonInterfaceCheckNoSupport() == _FALSE)
                        {
                            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                            if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_SETTING) == _FALSE)
                            {
                                break;
                            }
                        }
                        else
                        {
                            ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                        }
                    }

                    break;

                case _MODE_STATUS_FACTORY:

                    break;

                default:

                    break;
            }

            break;

        default:
            break;
    }

    // Handle Status Check and Manual Reset Requests
    SysJudgeModeResetProc();

    if(SysJudgeCheckStatus() == _FALSE)
    {
        g_ucSignalUnstable ++;
        // Force Reset
        CLR_MODE_STATE_CHANGE_SOURCE();
        CLR_MODE_STATE_CHANGE_MODE();
        CLR_MODE_STATE_CHANGE_MHL();
        CLR_MODE_STATE_CHANGE_OSD();
        CLR_MODE_STATE_CHANGE_OTHERS();
        SET_MODE_RESET_TARGET(_MODE_ACTION_NO_RESET_MODE);

        SysModeResetState(_MODE_ACTION_RESET_TO_SEARCH);

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
        if(UserCommonNVRamGetSystemData(_COLORIMETRY_SEAMLESS_CHANGE) == _TRUE)
        {
            CLR_DIGITAL_COLOR_INFO_CHANGE_RESET();
        }
        else
        {
            SET_DIGITAL_COLOR_INFO_CHANGE_RESET();
        }
#endif

        if((GET_MODE_STATE() != _MODE_STATUS_NOSIGNAL) && (GET_MODE_STATE() != _MODE_STATUS_POWER_SAVING))
        {
            SysJudgeStateChangeEvent(_MODE_STATUS_SEARCH);
        }
    }
}

//--------------------------------------------------
// Description  : Check Status
// Input Value  : None.
// Output Value : _FALSE => Status Changed
//--------------------------------------------------
bit SysJudgeCheckStatus(void)
{
    if(GET_MODE_STATE() != _MODE_STATUS_FACTORY)
    {
        if(GET_SOURCE_JUDGE(g_ucSearchIndex) == _TRUE)
        {
            if(SysSourceStableCheck() == _FALSE)
            {
                DebugMessageSystem("Source Unstable!!", GET_SOURCE_TYPE(g_ucSearchIndex));
                return _FALSE;
            }
        }

        if(SysModeGetTimingConfirm() == _TRUE)
        {
            // Check whether Input Timing changed
            if(ScalerMeasureTimingChange(GET_SOURCE_TYPE(g_ucSearchIndex), SysSourceGetInputPort()) == _TRUE)
            {
                DebugMessageSystem("Measured Input HV Changed", GET_SOURCE_TYPE(g_ucSearchIndex));
                return _FALSE;
            }

            // double check input timing
            if((GET_INPUT_TIMING_DOUBLE_CHECK() == _TRUE) &&
               ((SysModeGetDisplaySettingReady() == _TRUE) || (GET_MODE_STATE() == _MODE_STATUS_NOSUPPORT)))
            {
                if(GET_SOURCE_TYPE(g_ucSearchIndex) != _SOURCE_VGA)
                {
                    if(ScalerMeasureInterlaceCheck(GET_SOURCE_TYPE(g_ucSearchIndex), SysSourceGetInputPort()) != GET_INPUT_TIMING_INTERLACE_FLG())
                    {
                        DebugMessageSystem("Input Timing Double Check : Interlace Flag Change", GET_SOURCE_TYPE(g_ucSearchIndex));
                        return _FALSE;
                    }
                }

                CLR_INPUT_TIMING_DOUBLE_CHECK();
            }
        }

        if(SysModeGetDisplaySettingReady() == _TRUE)
        {
            if((ScalerMDomainMemoryCheck() == _FALSE) ||
               (ScalerMDomainDisplayTimingGenCheck() == _FALSE))
            {
                DebugMessageSystem("Memory Check Failed", GET_SOURCE_TYPE(g_ucSearchIndex));
                return _FALSE;
            }

#if(_ULTRA_HDR_SUPPORT == _ON)
            ScalerSyncGetColorInfoFrame(SysSourceGetInputPort(), _DP_GET_RSV0_INFO_ACTIVE);
#endif
        }

#if(_PANEL_STYLE == _PANEL_DPTX)
#if(_PANEL_DPTX_HPD_DETECT == _ON)
        if(GET_MODE_STATE() == _MODE_STATUS_ACTIVE)
        {
            if(ScalerDisplayDPTxStableDetect() == _FALSE)
            {
                DebugMessageSystem("eDP unstable", 0x00);
                return _FALSE;
            }
        }
#endif
#endif
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Switch to Active State
// Input Value  : None
// Output Value : _TRUE => Successfully Changed
//--------------------------------------------------
bit SysJudgeStateChangeEvent(EnumModeStatus enumModeState)
{
    // Check mode reset target
    if(GET_MODE_RESET_TARGET() != _MODE_ACTION_NO_RESET_MODE)
    {
        return _FALSE;
    }

    if((GET_MODE_STATE_CHANGE_SOURCE() == _FALSE) &&
       (GET_MODE_STATE_CHANGE_MODE() == _FALSE) &&
       (GET_MODE_STATE_CHANGE_MHL() == _FALSE) &&
       (GET_MODE_STATE_CHANGE_OSD() == _FALSE) &&
       (GET_MODE_STATE_CHANGE_OTHERS() == _FALSE))
    {
        SET_MODE_STATE(enumModeState);

        SET_MODE_STATE_CHANGE_SOURCE();
        SET_MODE_STATE_CHANGE_MODE();
        SET_MODE_STATE_CHANGE_MHL();
        SET_MODE_STATE_CHANGE_OSD();
        SET_MODE_STATE_CHANGE_OTHERS();

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Mode Reset Process according to reset target
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysJudgeModeResetProc(void)
{
    BYTE ucModeResetTarget = GET_MODE_RESET_TARGET();

    SET_MODE_RESET_TARGET(_MODE_ACTION_NO_RESET_MODE);

    switch(ucModeResetTarget)
    {
        case _MODE_ACTION_RESET_TO_SEARCH:

            if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_SEARCH);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_SEARCH) == _FALSE)
                {
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_SEARCH);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG:

            if(GET_MODE_STATE() == _MODE_STATUS_ACTIVE)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_SETTING) == _FALSE)
                {
                    // Resume mode reset target
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING:

            if(GET_MODE_STATE() == _MODE_STATUS_ACTIVE)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_SETTING) == _FALSE)
                {
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_NOSIGNAL:

            if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
            {
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSIGNAL_STATE);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_NOSIGNAL) == _FALSE)
                {
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_NOSIGNAL);
                    return;
                }
                else
                {
                    CLR_SOURCE_SWITCH_FINISH();
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_NOSUPPORT:

            if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_NOSUPPORT);

                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_NOSUPPORT) == _FALSE)
                {
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_NOSUPPORT);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_FACTORY_MODE:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSIGNAL_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);

            if(SysJudgeStateChangeEvent(_MODE_STATUS_FACTORY) == _FALSE)
            {
                SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_FACTORY_MODE);
                return;
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Required Wait Time before Active
// Input Value  : None
// Output Value : Required Wait Time
//--------------------------------------------------
WORD SysJudgeGetActiveWaitTime(void)
{
    if(GET_MODE_NO_WAIT_FOR_ACTIVE() == _FALSE)
    {
        switch(GET_SOURCE_TYPE(g_ucSearchIndex))
        {
#if(_VGA_SUPPORT == _ON)
            case _SOURCE_VGA:
                return _WAIT_TIME_TO_ACTIVE_VGA;
                break;
#endif

#if(_DVI_SUPPORT == _ON)
            case _SOURCE_DVI:
                return _WAIT_TIME_TO_ACTIVE_DVI;
                break;
#endif

#if(_HDMI_SUPPORT == _ON)
            case _SOURCE_HDMI:
                return _WAIT_TIME_TO_ACTIVE_HDMI;
                break;
#endif

#if(_DP_SUPPORT == _ON)
            case _SOURCE_DP:
                return _WAIT_TIME_TO_ACTIVE_DP;
                break;
#endif

            default:
                break;
        }
    }

    return 0;
}
