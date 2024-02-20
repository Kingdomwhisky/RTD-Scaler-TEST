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
// ID Code      : SysInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "Global.h"
#include "Project.h"
#include "ScalerCommonFunctionInterface.h"

#if(_TRANSLATOR_SUPPORT == _OFF)
#include "ScalerFunctionInterface.h"
#else
#include "TranslatorFunctionInterface.h"
#endif

#include "UserCommonInterface.h"

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Power.c Related MACRO
//--------------------------------------------------
//--------------------------------------------------
// Power action
//--------------------------------------------------
#define GET_TARGET_POWER_STATUS()               (g_stPowerInfo.b4PowerAction)
#define SET_TARGET_POWER_STATUS(x)              (g_stPowerInfo.b4PowerAction = (x))

//--------------------------------------------------
// Power status
//--------------------------------------------------
#define GET_POWER_STATUS()                      (g_stPowerInfo.b4PowerStatus)
#define SET_POWER_STATUS(x)                     (g_stPowerInfo.b4PowerStatus = (x))

//--------------------------------------------------
// Power Isolation flag
//--------------------------------------------------
#define GET_POWER_ISO_A_FLG()                   ((bit)(g_stPowerInfo.b1IsolationAFlag))
#define SET_POWER_ISO_A_FLG()                   (g_stPowerInfo.b1IsolationAFlag = 1)
#define CLR_POWER_ISO_A_FLG()                   (g_stPowerInfo.b1IsolationAFlag = 0)

#define GET_POWER_ISO_B_FLG()                   ((bit)(g_stPowerInfo.b1IsolationBFlag))
#define SET_POWER_ISO_B_FLG()                   (g_stPowerInfo.b1IsolationBFlag = 1)
#define CLR_POWER_ISO_B_FLG()                   (g_stPowerInfo.b1IsolationBFlag = 0)

#define GET_POWER_ISO_C_FLG()                   ((bit)(g_stPowerInfo.b1IsolationCFlag))
#define SET_POWER_ISO_C_FLG()                   (g_stPowerInfo.b1IsolationCFlag = 1)
#define CLR_POWER_ISO_C_FLG()                   (g_stPowerInfo.b1IsolationCFlag = 0)

#define GET_POWER_ISO_D_FLG()                   ((bit)(g_stPowerInfo.b1IsolationDFlag))
#define SET_POWER_ISO_D_FLG()                   (g_stPowerInfo.b1IsolationDFlag = 1)
#define CLR_POWER_ISO_D_FLG()                   (g_stPowerInfo.b1IsolationDFlag = 0)

#define GET_POWER_ISO_E_FLG()                   ((bit)(g_stPowerInfo.b1IsolationEFlag))
#define SET_POWER_ISO_E_FLG()                   (g_stPowerInfo.b1IsolationEFlag = 1)
#define CLR_POWER_ISO_E_FLG()                   (g_stPowerInfo.b1IsolationEFlag = 0)

//--------------------------------------------------
// Power status Switch to Fake Saving
//--------------------------------------------------
#define GET_POWER_SWITCH_TO_FAKE_SAVING()       ((bit)(g_stPowerInfo.b1PowerSwitchtoFakeSaving))
#define SET_POWER_SWITCH_TO_FAKE_SAVING()       (g_stPowerInfo.b1PowerSwitchtoFakeSaving = 1)
#define CLR_POWER_SWITCH_TO_FAKE_SAVING()       (g_stPowerInfo.b1PowerSwitchtoFakeSaving = 0)

//--------------------------------------------------
// Power status Switch to Off
//--------------------------------------------------
#define GET_POWER_SWITCH_TO_FAKE_OFF()          ((bit)(g_stPowerInfo.b1PowerSwitchtoFakeOff))
#define SET_POWER_SWITCH_TO_FAKE_OFF()          (g_stPowerInfo.b1PowerSwitchtoFakeOff = 1)
#define CLR_POWER_SWITCH_TO_FAKE_OFF()          (g_stPowerInfo.b1PowerSwitchtoFakeOff = 0)

//--------------------------------------------------
// Source.c Related MACRO
//--------------------------------------------------
#define GET_SOURCE_SEARCH_TIME_INITIAL()        ((bit)(g_stInputInfo.b1SearchTimeInitial))
#define SET_SOURCE_SEARCH_TIME_INITIAL()        (g_stInputInfo.b1SearchTimeInitial = 1)
#define CLR_SOURCE_SEARCH_TIME_INITIAL()        (g_stInputInfo.b1SearchTimeInitial = 0)

#define GET_SOURCE_SEARCH_PORT_INITIAL()        ((bit)(g_stInputInfo.b1SearchPortInitial))
#define SET_SOURCE_SEARCH_PORT_INITIAL()        (g_stInputInfo.b1SearchPortInitial = 1)
#define CLR_SOURCE_SEARCH_PORT_INITIAL()        (g_stInputInfo.b1SearchPortInitial = 0)

#define GET_SOURCE_DETECTING()                  ((bit)(g_stInputInfo.b1Detecting))
#define SET_SOURCE_DETECTING()                  (g_stInputInfo.b1Detecting = 1)
#define CLR_SOURCE_DETECTING()                  (g_stInputInfo.b1Detecting = 0)

#define GET_SOURCE_SCAN_TYPE()                  (g_stInputInfo.b4SourceSwitchType)
#define SET_SOURCE_SCAN_TYPE(x)                 (g_stInputInfo.b4SourceSwitchType = (x))

#define GET_SOURCE_SWITCH_FINISH()              (g_stInputInfo.b1SourceSwitchCount)
#define SET_SOURCE_SWITCH_FINISH()              (g_stInputInfo.b1SourceSwitchCount = 1)
#define CLR_SOURCE_SWITCH_FINISH()              (g_stInputInfo.b1SourceSwitchCount = 0)

#define GET_SOURCE_SEARCH_TIME_REACTIVE()       (g_stInputInfo.b1SourceSearchTimeReactivate)
#define SET_SOURCE_SEARCH_TIME_REACTIVE()       (g_stInputInfo.b1SourceSearchTimeReactivate = 1)
#define CLR_SOURCE_SEARCH_TIME_REACTIVE()       (g_stInputInfo.b1SourceSearchTimeReactivate = 0)

#define GET_SOURCE_SEARCH_CHECK_NVRAM_PORT()    (g_stInputInfo.b1SourceSearchCheckNVRamPort)
#define SET_SOURCE_SEARCH_CHECK_NVRAM_PORT()    (g_stInputInfo.b1SourceSearchCheckNVRamPort = 1)
#define CLR_SOURCE_SEARCH_CHECK_NVRAM_PORT()    (g_stInputInfo.b1SourceSearchCheckNVRamPort = 0)

#define GET_SOURCE_SEARCH_DELAY_MODE()          (g_stInputInfo.b2SourceSearchDelayMode)
#define SET_SOURCE_SEARCH_DELAY_MODE(x)         (g_stInputInfo.b2SourceSearchDelayMode = (x))

#define GET_SOURCE_EIZO_PS_SUPPORT()            (g_stInputInfo.b1SourceEizoPSSupport)
#define SET_SOURCE_EIZO_PS_SUPPORT()            (g_stInputInfo.b1SourceEizoPSSupport = 1)
#define CLR_SOURCE_EIZO_PS_SUPPORT()            (g_stInputInfo.b1SourceEizoPSSupport = 0)

#define GET_SOURCE_EIZO_INFO_RESET()            (g_stInputInfo.b1SourceEizoInfoReset)
#define SET_SOURCE_EIZO_INFO_RESET()            (g_stInputInfo.b1SourceEizoInfoReset = 1)
#define CLR_SOURCE_EIZO_INFO_RESET()            (g_stInputInfo.b1SourceEizoInfoReset = 0)

#define GET_SOURCE_EIZO_EVENT_TIME()            (g_stInputInfo.usSourceEizoEventTime)
#define SET_SOURCE_EIZO_EVENT_TIME(x)           (g_stInputInfo.usSourceEizoEventTime = (x))

#define GET_SOURCE_HP_SOURCE_JUDGE()            (g_stInputInfo.b1SourceHpSourceJudge)
#define SET_SOURCE_HP_SOURCE_JUDGE()            (g_stInputInfo.b1SourceHpSourceJudge = 1)
#define CLR_SOURCE_HP_SOURCE_JUDGE()            (g_stInputInfo.b1SourceHpSourceJudge = 0)

#define GET_SOURCE_HP_SWITCH_NO_CABLE()         (g_stInputInfo.b1SourceHpSwitchNoCable)
#define SET_SOURCE_HP_SWITCH_NO_CABLE()         (g_stInputInfo.b1SourceHpSwitchNoCable = 1)
#define CLR_SOURCE_HP_SWITCH_NO_CABLE()         (g_stInputInfo.b1SourceHpSwitchNoCable = 0)

#define GET_SOURCE_HP_TIMING_CHANGE()           (g_stInputInfo.b1SourceHpTimingChange)
#define SET_SOURCE_HP_TIMING_CHANGE()           (g_stInputInfo.b1SourceHpTimingChange = 1)
#define CLR_SOURCE_HP_TIMING_CHANGE()           (g_stInputInfo.b1SourceHpTimingChange = 0)

#define GET_SOURCE_HP_TARGET_SEARCH_TIMES()     (g_stInputInfo.b2SourceHpTargetSearchTimes)
#define SET_SOURCE_HP_TARGET_SEARCH_TIMES(x)    (g_stInputInfo.b2SourceHpTargetSearchTimes = (x))

#define GET_SOURCE_HP_PORT_SWITCH_TARGET()      (g_stInputInfo.b3SourceHpPortSwitchTarget)
#define SET_SOURCE_HP_PORT_SWITCH_TARGET(x)     (g_stInputInfo.b3SourceHpPortSwitchTarget = (x))

#define GET_SOURCE_HP_FROM_TIMING_CHANGE()      (g_stInputInfo.b1SourceHpFromTimingChange)
#define SET_SOURCE_HP_FROM_TIMING_CHANGE()      (g_stInputInfo.b1SourceHpFromTimingChange = 1)
#define CLR_SOURCE_HP_FROM_TIMING_CHANGE()      (g_stInputInfo.b1SourceHpFromTimingChange = 0)

#define GET_SOURCE_TYPE(x)                      (g_pstSourceInfo[x].b3SourceType)
#define SET_SOURCE_TYPE(x, y)                   (g_pstSourceInfo[x].b3SourceType = (y))

#define GET_SOURCE_SEARCH_TIMES(x)              ((g_pstSourceInfo[x].b2SearchTimes))
#define INCREASE_SOURCE_SEARCH_TIMES(x)         (g_pstSourceInfo[x].b2SearchTimes++)
#define SET_SOURCE_SEARCH_TIMES(x, y)           (g_pstSourceInfo[x].b2SearchTimes = (y))
#define CLR_SOURCE_SEARCH_TIMES(x)              (g_pstSourceInfo[x].b2SearchTimes = 0)

#define GET_CABLE_DETECT(x)                     (g_pstSourceInfo[x].b1CableDetect)
#define SET_CABLE_DETECT(x, y)                  (g_pstSourceInfo[x].b1CableDetect = (y))

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#define GET_TYPE_C_ALT_MODE_DETECT(x)           (g_pstSourceInfo[x].b1TypeCAltModeDetect)
#define SET_TYPE_C_ALT_MODE_DETECT(x, y)        (g_pstSourceInfo[x].b1TypeCAltModeDetect = (y))
#endif

#define GET_CABLE_STATUS_CHANGE(x)              (g_pstSourceInfo[x].b1CableStatusChange)
#define SET_CABLE_STATUS_CHANGE(x, y)           (g_pstSourceInfo[x].b1CableStatusChange = (y))

#define GET_SOURCE_JUDGE(x)                     ((bit)(g_pstSourceInfo[x].b1SourceChosen))
#define SET_SOURCE_JUDGE(x, y)                  (g_pstSourceInfo[x].b1SourceChosen = (y))
#define CLR_SOURCE_JUDGE(x)                     (g_pstSourceInfo[x].b1SourceChosen = 0)

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
#define GET_SOURCE_BG_JUDGE(x)                  ((bit)(g_pstBgSourceInfo[x].b1SourceChosen))
#define SET_SOURCE_BG_JUDGE(x, y)               (g_pstBgSourceInfo[x].b1SourceChosen = (y))
#define CLR_SOURCE_BG_JUDGE(x)                  (g_pstBgSourceInfo[x].b1SourceChosen = 0)
#endif

#define GET_SOURCE_PREDETECT(x)                 ((bit)(g_pstSourceInfo[x].b1SourcePreDetect))
#define SET_SOURCE_PREDETECT(x, y)              (g_pstSourceInfo[x].b1SourcePreDetect = (y))
#define CLR_SOURCE_PREDETECT(x)                 (g_pstSourceInfo[x].b1SourcePreDetect = 0)

#define GET_SOURCE_TYPE_BACKUP()                (g_stSourceInfoBackup.b3SourceType)
#define SET_SOURCE_TYPE_BACKUP(x)               (g_stSourceInfoBackup.b3SourceType = (x))

#define GET_SOURCE_SEARCH_TIMES_BACKUP()        ((g_stSourceInfoBackup.b2SearchTimes))
#define SET_SOURCE_SEARCH_TIMES_BACKUP(x)       (g_stSourceInfoBackup.b2SearchTimes = (x))

#define GET_CABLE_DETECT_BACKUP()               (g_stSourceInfoBackup.b1CableDetect)
#define SET_CABLE_DETECT_BACKUP(x)              (g_stSourceInfoBackup.b1CableDetect = (x))

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#define GET_TYPE_C_ALT_MODE_DETECT_BACKUP()     (g_stSourceInfoBackup.b1TypeCAltModeDetect)
#define SET_TYPE_C_ALT_MODE_DETECT_BACKUP(x)    (g_stSourceInfoBackup.b1TypeCAltModeDetect = (x))
#endif

#define GET_CABLE_STATUS_CHANGE_BACKUP()        (g_stSourceInfoBackup.b1CableStatusChange)
#define SET_CABLE_STATUS_CHANGE_BACKUP(x)       (g_stSourceInfoBackup.b1CableStatusChange = (x))

#define GET_SOURCE_JUDGE_BACKUP()               ((bit)(g_stSourceInfoBackup.b1SourceChosen))
#define SET_SOURCE_JUDGE_BACKUP(x)              (g_stSourceInfoBackup.b1SourceChosen = (x))

#define GET_SOURCE_PREDETECT_BACKUP()           ((bit)(g_stSourceInfoBackup.b1SourcePreDetect))
#define SET_SOURCE_PREDETECT_BACKUP(x)          (g_stSourceInfoBackup.b1SourcePreDetect = (x))

#define GET_SOURCE_HP_TARGET_NO_SIGNAL()        (g_stInputInfo.b1SourceHpTargetNoSignal)
#define SET_SOURCE_HP_TARGET_NO_SIGNAL()        (g_stInputInfo.b1SourceHpTargetNoSignal = 1)
#define CLR_SOURCE_HP_TARGET_NO_SIGNAL()        (g_stInputInfo.b1SourceHpTargetNoSignal = 0)

#define GET_SOURCE_ASUS_START_AUTO()            (g_stInputInfo.b1SourceAsusStartAuto)
#define SET_SOURCE_ASUS_START_AUTO()            (g_stInputInfo.b1SourceAsusStartAuto = 1)
#define CLR_SOURCE_ASUS_START_AUTO()            (g_stInputInfo.b1SourceAsusStartAuto = 0)

#define GET_SOURCE_ASUS_FIRST_START_AUTO()      (g_stInputInfo.b1SourceAsusFirstStartAuto)
#define SET_SOURCE_ASUS_FIRST_START_AUTO()      (g_stInputInfo.b1SourceAsusFirstStartAuto = 1)
#define CLR_SOURCE_ASUS_FIRST_START_AUTO()      (g_stInputInfo.b1SourceAsusFirstStartAuto = 0)

#define GET_SOURCE_ASUS_START_POLLING()         (g_stInputInfo.b1SourceAsusStartPolling)
#define SET_SOURCE_ASUS_START_POLLING()         (g_stInputInfo.b1SourceAsusStartPolling = 1)
#define CLR_SOURCE_ASUS_START_POLLING()         (g_stInputInfo.b1SourceAsusStartPolling = 0)

#define GET_SOURCE_FUJITSU_SWITCH_PORT()        (g_stInputInfo.b1SourceFujitsuSwitchPort)
#define SET_SOURCE_FUJITSU_SWITCH_PORT()        (g_stInputInfo.b1SourceFujitsuSwitchPort = 1)
#define CLR_SOURCE_FUJITSU_SWITCH_PORT()        (g_stInputInfo.b1SourceFujitsuSwitchPort = 0)

#define GET_SOURCE_DP_SWITCH_TIMEOUT()          (g_stInputInfo.b1SourceDpSwitchTimeout)
#define SET_SOURCE_DP_SWITCH_TIMEOUT()          (g_stInputInfo.b1SourceDpSwitchTimeout = 1)
#define CLR_SOURCE_DP_SWITCH_TIMEOUT()          (g_stInputInfo.b1SourceDpSwitchTimeout = 0)

#if((_HP_SOURCE_SCAN_SUPPORT == _ON) && (_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE))
#define GET_SOURCE_HP_DETECTING()               (g_stInputInfo.b1SourceHpDetecting)
#define SET_SOURCE_HP_DETECTING()               (g_stInputInfo.b1SourceHpDetecting = 1)
#define CLR_SOURCE_HP_DETECTING()               (g_stInputInfo.b1SourceHpDetecting = 0)
#endif

//--------------------------------------------------
// Mode.c Related MACRO
//--------------------------------------------------
#define GET_MODE_STATE()                        (g_stModeInfo.b5ModeState)
#define SET_MODE_STATE(x)                       (g_stModeInfo.b5ModeState = (x))

#define GET_MODE_DISPLAY_SETTING_READY()        (bit)(g_stModeInfo.b1DisplaySettingReady)
#define SET_MODE_DISPLAY_SETTING_READY()        (g_stModeInfo.b1DisplaySettingReady = _TRUE)
#define CLR_MODE_DISPLAY_SETTING_READY()        (g_stModeInfo.b1DisplaySettingReady = _FALSE)

#define GET_MODE_TIMING_CONFIRM()               (bit)(g_stModeInfo.b1TimingConfirm)
#define SET_MODE_TIMING_CONFIRM()               (g_stModeInfo.b1TimingConfirm = _TRUE)
#define CLR_MODE_TIMING_CONFIRM()               (g_stModeInfo.b1TimingConfirm = _FALSE)

#define GET_MODE_STATE_CHANGE_OTHERS()          (bit)(g_stModeInfo.b1ModeStateChangedForOthers)
#define SET_MODE_STATE_CHANGE_OTHERS()          (g_stModeInfo.b1ModeStateChangedForOthers = _TRUE)
#define CLR_MODE_STATE_CHANGE_OTHERS()          (g_stModeInfo.b1ModeStateChangedForOthers = _FALSE)

#define GET_MODE_STATE_CHANGE_SOURCE()          (bit)(g_stModeInfo.b1ModeStateChangedForSource)
#define SET_MODE_STATE_CHANGE_SOURCE()          (g_stModeInfo.b1ModeStateChangedForSource = _TRUE)
#define CLR_MODE_STATE_CHANGE_SOURCE()          (g_stModeInfo.b1ModeStateChangedForSource = _FALSE)

#define GET_MODE_STATE_CHANGE_MODE()            (bit)(g_stModeInfo.b1ModeStateChangedForMode)
#define SET_MODE_STATE_CHANGE_MODE()            (g_stModeInfo.b1ModeStateChangedForMode = _TRUE)
#define CLR_MODE_STATE_CHANGE_MODE()            (g_stModeInfo.b1ModeStateChangedForMode = _FALSE)

#if(_MHL_SUPPORT == _ON)
#define GET_MODE_STATE_CHANGE_MHL()             (bit)(g_stModeInfo.b1ModeStateChangedForMHL)
#define SET_MODE_STATE_CHANGE_MHL()             (g_stModeInfo.b1ModeStateChangedForMHL = _TRUE)
#define CLR_MODE_STATE_CHANGE_MHL()             (g_stModeInfo.b1ModeStateChangedForMHL = _FALSE)
#else
#define GET_MODE_STATE_CHANGE_MHL()             (bit)(_FALSE)
#define SET_MODE_STATE_CHANGE_MHL()             {}
#define CLR_MODE_STATE_CHANGE_MHL()             {}
#endif

#define GET_MODE_STATE_CHANGE_OSD()             (bit)(g_stModeInfo.b1ModeStateChangedForOsd)
#define SET_MODE_STATE_CHANGE_OSD()             (g_stModeInfo.b1ModeStateChangedForOsd = _TRUE)
#define CLR_MODE_STATE_CHANGE_OSD()             (g_stModeInfo.b1ModeStateChangedForOsd = _FALSE)

#define GET_MODE_RESET_TARGET()                 (g_stModeInfo.b4ModeResetFlag)
#define SET_MODE_RESET_TARGET(x)                (g_stModeInfo.b4ModeResetFlag = (x))

#define GET_MODE_NO_WAIT_FOR_ACTIVE()           (bit)(g_stModeInfo.b1NoWaitForActive)
#define SET_MODE_NO_WAIT_FOR_ACTIVE()           (g_stModeInfo.b1NoWaitForActive = _TRUE)
#define CLR_MODE_NO_WAIT_FOR_ACTIVE()           (g_stModeInfo.b1NoWaitForActive = _FALSE)

#define GET_MODE_ACTIVE_READY()                 (bit)(g_stModeInfo.b1ActiveReady)
#define SET_MODE_ACTIVE_READY()                 (g_stModeInfo.b1ActiveReady = _TRUE)
#define CLR_MODE_ACTIVE_READY()                 (g_stModeInfo.b1ActiveReady = _FALSE)

#define GET_FIRST_AUTOK_STATUS()                (bit)(g_stModeInfo.b1AutokReady)
#define SET_FIRST_AUTOK_STATUS()                (g_stModeInfo.b1AutokReady = _TRUE)
#define CLR_FIRST_AUTOK_STATUS()                (g_stModeInfo.b1AutokReady = _FALSE)

//--------------------------------------------------
// Audio.c Related MACRO
//--------------------------------------------------
#define GET_AUDIO_PLAYBACK_SEARCH_INDEX()       (g_stAudioInfo.b4AudioPlaybackSearchIndex)
#define SET_AUDIO_PLAYBACK_SEARCH_INDEX(x)      (g_stAudioInfo.b4AudioPlaybackSearchIndex = (x))

#define GET_AUDIO_STATE()                       (g_stAudioInfo.b2AudioState)
#define SET_AUDIO_STATE(x)                      (g_stAudioInfo.b2AudioState = (x))

#define GET_AUDIO_STATE_CHANGE()                (bit)(g_stAudioInfo.b1AudioStateChange)
#define SET_AUDIO_STATE_CHANGE()                (g_stAudioInfo.b1AudioStateChange = _TRUE)
#define CLR_AUDIO_STATE_CHANGE()                (g_stAudioInfo.b1AudioStateChange = _FALSE)

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#define GET_AUDIO_PLAYING_ALONE()               (bit)(g_stAudioInfo.b1AudioPlayingAlone)
#define SET_AUDIO_PLAYING_ALONE()               (g_stAudioInfo.b1AudioPlayingAlone = _TRUE)
#define CLR_AUDIO_PLAYING_ALONE()               (g_stAudioInfo.b1AudioPlayingAlone = _FALSE)
#endif

//--------------------------------------------------
// Test.c Related MACRO
//--------------------------------------------------
#ifndef _DISPLAY_SETTING_TEST
#define _DISPLAY_SETTING_TEST                   _OFF
#endif

#if(_DISPLAY_SETTING_TEST == _ON)
#define DISPLAY_SETTING_TEST_INIT()             {\
                                                    SysTestingInit();\
                                                }
#define DISPLAY_SETTING_TEST_UPDATE()           {\
                                                    if(SysTestUpateSetting() == _FALSE)\
                                                    {\
                                                        return _FALSE;\
                                                    }\
                                                }
#else
#define DISPLAY_SETTING_TEST_INIT()             {}
#define DISPLAY_SETTING_TEST_UPDATE()           {}
#endif

//--------------------------------------------------
// SysTypeC.c Related MACRO
//--------------------------------------------------
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
#define GET_D0_USB_HUB_MODE_STATE()             (g_stD0UsbHubInfo.b7USBHubModeState)
#define SET_D0_USB_HUB_MODE_STATE(x)            (g_stD0UsbHubInfo.b7USBHubModeState = (x))

#define GET_D0_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD0UsbHubInfo.b1SSDeviceDetecting)
#define SET_D0_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD0UsbHubInfo.b1SSDeviceDetecting = _TRUE)
#define CLR_D0_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD0UsbHubInfo.b1SSDeviceDetecting = _FALSE)

#define GET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD0UsbHubInfo.enumHubDspChange)
#define SET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD0UsbHubInfo.enumHubDspChange = _HUB_DSP_DEVICE_CHANGE)
#define CLR_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD0UsbHubInfo.enumHubDspChange = _HUB_DSP_DEVICE_NO_CHANGE)
#endif
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
#define GET_D1_USB_HUB_MODE_STATE()             (g_stD1UsbHubInfo.b7USBHubModeState)
#define SET_D1_USB_HUB_MODE_STATE(x)            (g_stD1UsbHubInfo.b7USBHubModeState = (x))

#define GET_D1_USB_HUB_SS_DEVICE_DETECT_FLG()   (bit)(g_stD1UsbHubInfo.b1SSDeviceDetecting)
#define SET_D1_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD1UsbHubInfo.b1SSDeviceDetecting = _TRUE)
#define CLR_D1_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD1UsbHubInfo.b1SSDeviceDetecting = _FALSE)

#define GET_D1_TYPE_C_USB_HUB_INFO()            (g_stD1UsbHubInfo.b4UsbHubStatus)
#define SET_D1_TYPE_C_USB_HUB_INFO(x)           (g_stD1UsbHubInfo.b4UsbHubStatus = (x))

#define GET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD1UsbHubInfo.enumHubDspChange)
#define SET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD1UsbHubInfo.enumHubDspChange = _HUB_DSP_DEVICE_CHANGE)
#define CLR_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD1UsbHubInfo.enumHubDspChange = _HUB_DSP_DEVICE_NO_CHANGE)
#endif
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
#define GET_D6_USB_HUB_MODE_STATE()             (g_stD6UsbHubInfo.b7USBHubModeState)
#define SET_D6_USB_HUB_MODE_STATE(x)            (g_stD6UsbHubInfo.b7USBHubModeState = (x))

#define GET_D6_USB_HUB_SS_DEVICE_DETECT_FLG()   (bit)(g_stD6UsbHubInfo.b1SSDeviceDetecting)
#define SET_D6_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD6UsbHubInfo.b1SSDeviceDetecting = _TRUE)
#define CLR_D6_USB_HUB_SS_DEVICE_DETECT_FLG()   (g_stD6UsbHubInfo.b1SSDeviceDetecting = _FALSE)

#define GET_D6_TYPE_C_USB_HUB_INFO()            (g_stD6UsbHubInfo.b4UsbHubStatus)
#define SET_D6_TYPE_C_USB_HUB_INFO(x)           (g_stD6UsbHubInfo.b4UsbHubStatus = (x))

#define GET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD6UsbHubInfo.enumHubDspChange)
#define SET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD6UsbHubInfo.enumHubDspChange = _HUB_DSP_DEVICE_CHANGE)
#define CLR_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG() (g_stD6UsbHubInfo.enumHubDspChange = _HUB_DSP_DEVICE_NO_CHANGE)
#endif
#endif

#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1SearchTimeInitial : 1;
    BYTE b1SearchPortInitial : 1;
    BYTE b1Detecting : 1;
    BYTE b1SourceSwitchCount : 1;
    BYTE b1SourceSearchTimeReactivate : 1;
    BYTE b1SourceSearchCheckNVRamPort : 1;
    BYTE b2SourceSearchDelayMode : 2; // 00 : Polling
                                      // 01 : Defualt Search Time
                                      // 10 : Reactivate Search Time
    WORD usSourceEizoEventTime;
    BYTE b1SourceEizoPSSupport : 1;
    BYTE b1SourceEizoInfoReset : 1;
    BYTE b1SourceHpSourceJudge : 1;
    BYTE b1SourceHpSwitchNoCable : 1;
    BYTE b1SourceHpTimingChange : 1;
    BYTE b1SourceHpFromTimingChange : 1;

    BYTE b2SourceHpTargetSearchTimes : 2;
    BYTE b3SourceHpPortSwitchTarget : 3;
    BYTE b1SourceHpTargetNoSignal : 1;
    BYTE b1SourceAsusStartAuto : 1;
    BYTE b1SourceAsusFirstStartAuto : 1;
    BYTE b1SourceAsusStartPolling : 1;
    BYTE b1SourceFujitsuSwitchPort : 1;
    BYTE b1SourceDpSwitchTimeout : 1;
    BYTE b4SourceSwitchType : 4; // 0000 : fixed;
                                 // 0001 : auto in group;
                                 // 0010 : auto without group;
                                 // 0011 : HP style 1 --> Scan Mode;
                                 // 0100 : HP style 2 --> Timing Change;
                                 // 0101 : HP style 3 --> Switch Port
                                 // 0110 : HP style 4
                                 // 0111 : Asus style
                                 // 1000 : Dell hotkey auto
                                 // 1001 : Dell hotkey fixed

#if((_HP_SOURCE_SCAN_SUPPORT == _ON) && (_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE))
    BYTE b1SourceHpDetecting : 1;
#endif
} StructInputInfoType;

typedef struct
{
    BYTE b5ModeState : 5;
    BYTE b1DisplaySettingReady : 1;
    BYTE b1TimingConfirm : 1;
    BYTE b1ModeStateChangedForOthers : 1;
    BYTE b1ModeStateChangedForOsd : 1;
    BYTE b1ModeStateChangedForSource : 1;
    BYTE b1ModeStateChangedForMode : 1;
    BYTE b1ModeStateChangedForMHL : 1;
    BYTE b4ModeResetFlag : 4;
    BYTE b1NoWaitForActive : 1;
    BYTE b1ActiveReady : 1;
    BYTE b1AutokReady : 1;
} StructModeInfoType;

typedef struct
{
    BYTE b4PowerAction : 4;
    BYTE b4PowerStatus : 4;
    BYTE b1IsolationAFlag : 1;
    BYTE b1IsolationBFlag : 1;
    BYTE b1IsolationCFlag : 1;
    BYTE b1IsolationDFlag : 1;
    BYTE b1IsolationEFlag : 1;
    BYTE b1PowerSwitchtoFakeSaving : 1;
    BYTE b1PowerSwitchtoFakeOff : 1;
} StructPowerInfoType;

typedef struct
{
    BYTE b3SourceType : 3;
    BYTE b2SearchTimes : 2;
    BYTE b1CableDetect : 1;
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    BYTE b1TypeCAltModeDetect : 1;
#endif
    BYTE b1CableStatusChange : 1;
    BYTE b1SourceChosen : 1;
    BYTE b1SourcePreDetect : 1;
} StructSourceInfoType;

typedef struct
{
    BYTE b4AudioPlaybackSearchIndex : 4;
    BYTE b2AudioState : 2;
    BYTE b1AudioStateChange : 1;

#if(_SLEEP_AUDIO_SUPPORT == _ON)
    BYTE b1AudioPlayingAlone : 1;
#endif
} StructAudioInfoType;

typedef struct
{
    BYTE b7USBHubModeState : 7;
    BYTE b1SSDeviceDetecting : 1;
    BYTE b4UsbHubStatus : 4;
    EnumHubDspDetectStatus enumHubDspChange;
} StructUsbHubInfo;

//--------------------------------------------------
// Enumerations of USB SS Device Mode State
//--------------------------------------------------
typedef enum
{
    _USB_MODE_STATUS_INITIAL = 0x00,
    _USB_MODE_STATUS_DETECT_SS_STATE = 0x01,
    _USB_MODE_STATUS_SS_STATE = 0x02,
    _USB_MODE_STATUS_PS_STATE = 0x03,
    _USB_MODE_STATUS_PD_STATE = 0x04,
    _USB_MODE_STATUS_NONE = 0xFF,
} EnumUsbModeStatus;

//--------------------------------------------------
// Enumerations of TypeC Cable Status Change
//--------------------------------------------------
typedef enum
{
    _TYPE_C_CABLE_UNPLUG = 0x00,
    _TYPE_C_CABLE_PLUG = 0x01,
    _TYPE_C_CABLE_UNCHANGE = 0xFF,
} EnumTypeCCableStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
// __SYSTEM_MODE__
extern StructModeInfoType g_stModeInfo;


// __SYSTEM_POWER__
extern StructPowerInfoType g_stPowerInfo;


// __SYSTEM_SOURCE__
extern StructSourceInfoType g_pstSourceInfo[_INPUT_PORT_VALID];
extern StructSourceInfoType g_stSourceInfoBackup;
extern BYTE g_ucSearchIndex;
extern StructInputInfoType g_stInputInfo;

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
extern StructSourceInfoType g_pstBgSourceInfo[_INPUT_PORT_VALID];
extern BYTE g_ucBgDetectIndex;
#endif


// __SYSTEM_JUDGE__
extern bit g_bEventEdgeFlg;


// __SYSTEM_AUDIO__
extern StructAudioInfoType g_stAudioInfo;


// __SYSTEM_VGA__


#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
extern StructUsbHubInfo g_stD0UsbHubInfo;
#endif
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
extern StructUsbHubInfo g_stD1UsbHubInfo;
#endif
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
extern StructUsbHubInfo g_stD6UsbHubInfo;
#endif
#endif

#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// __SYSTEM_JUDGE__
extern void SysJudgeHandler(void);
extern bit SysJudgeStateChangeEvent(EnumModeStatus enumModeState);


// __SYSTEM_MODE__
extern void SysModeHandler(void);
extern bit SysModeGetDisplaySettingReady(void);
extern bit SysModeGetTimingConfirm(void);
extern bit SysModeGetActiveReady(void);
extern void SysModeResetState(BYTE ucResetTarget);
extern void SysModeSetFreeRun(void);
extern void SysModeSetResetTarget(EnumModeAction enumResetTarget);

// __SYSTEM_TEST__
#if(_DISPLAY_SETTING_TEST == _ON)
extern void SysTestingInit(void);
extern bit SysTestUpateSetting(void);
#endif

// __SYSTEM_MHL__
extern void SysMHLMscHandler(void);


// __SYSTEM_POWER__
extern void SysPowerInitial(void);
extern void SysPowerHandler(void);
extern BYTE SysPowerGetPowerStatus(void);

// __SYSTEM_SOURCE__
extern void SysSourceHandler(void);
extern void SysSourceInitial(void);
extern bit SysSourceStableCheck(void);
extern void SysSourceClearDetectingEvent(void);
extern void SysSourceSwitchInputPort(BYTE ucInputPort);
extern void SysSourceInfoReset(void);
extern BYTE SysSourceGetInputPort(void);
extern BYTE SysSourceGetInputPortType(BYTE ucInputPort);
extern BYTE SysSourceGetSourceType(void);
extern BYTE SysSourceConvertSearchPort(BYTE ucInputPort);
extern void SysSourceCableResetProc(void);
extern void SysSourceFirstActiveProc(void);
extern void SysSourcePowerOffProc(void);

#if(_USB3_RETIMER_SUPPORT == _ON)
extern EnumTypeCCableStatus SysSourceGetTypeCCableStatusChange(void);
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
extern BYTE SysSourceBgGetInputPort(void);
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
extern bit SysSourceHpGetMonitorStatusCheckProcessing(void);
#endif

// __SYSTEM_TIMER__
extern void SysTimerHandler(void);


#if(_VGA_SUPPORT == _ON)
extern BYTE SysVgaScanInputPort(BYTE ucInputPort);
#endif

// __SYSTEM_AUDIO__

#if(_AUDIO_SUPPORT == _ON)
extern void SysAudioHandler(void);
extern void SysAudioPowerProc(EnumPowerAction enumSwitch);

#if(_DP_SUPPORT == _ON)
void SysAudioDpAudioSecDataResetProc(BYTE ucInputPort);
#endif
#endif


// __SYSTEM_DP__
#if(_DP_SUPPORT == _ON)
extern void SysDpRxHandler(void);
extern void SysDpDcOffHPDToggleProc(EnumPowerAction enumSwitch);
extern bit SysDpSourceKeepDetectingCheck(void);
extern bit SysDpCheckTwoChipDataExchangePort(BYTE ucInputPort);
#endif

// __SYSTEM_TMDS__
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
extern void SysTMDSRxHandler(void);
#if(_HDMI_SUPPORT == _ON)
extern void SysTMDSRxSetPsWakeupHpdToggle(void);
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void SysDpTxHandler(void);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern void SysDpMstHandler(void);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
extern void SysDpMstAutoSwitch(void);
#endif
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
extern void SysTypeCInitial(void);
extern void SysTypeCHandler(void);
extern void SysTypeCPowerSwitch(EnumPowerAction enumSwitch);
extern EnumTypeCOrientation SysTypeCGetPortControllerOrientation(BYTE ucInputPort);
extern bit SysTypeCGetPortControllerPinAssignment(BYTE ucInputPort);
extern bit SysTypeCGetCcAttach(BYTE ucInputPort);
extern bit SysTypeCGetAltModeReady(BYTE ucInputPort);
#if(_DP_PORT_EXIST == _ON)
extern bit SysTypeCCheckTypeCPortControllerExist(BYTE ucInputPort);
#endif

#if(((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)))
extern void SysTypeCSwitchToUnattachState(BYTE ucInputPort);
#endif

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
extern void SysTypeCSetLenovoRcvDeviceTypeTimeout(BYTE ucInputPort);
#endif

#if(_BILLBOARD_SUPPORT == _ON)
extern void SysTypeCBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion);
#endif

#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

// __SYSTEM_USB__

#if(_HDMI_TX_SUPPORT == _ON)
extern void SysHdmiTxHandler(void);
#endif

#if(_EMBEDDED_DP_TX_SUPPORT == _ON)
extern void SysDpEmbeddedTxHandler(void);
#endif

// __SYSTEM_CEC__
#if(_HDMI_CEC_SUPPORT == _ON)
extern void SysCecHandler(void);
#endif

// __SYSTEM_COLOR__
extern void SysColorHandler(void);

#if(_AUTO_TEST_SUPPORT == _ON)
extern void SysAutotestHandler(void);
extern void SysAutotestOSDSwitchCtrl(void);
extern void SysAutotestIntProc_EXINT1(void);
#endif
