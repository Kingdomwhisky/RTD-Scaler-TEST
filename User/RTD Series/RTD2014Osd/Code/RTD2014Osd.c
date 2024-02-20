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
// ID Code      : RTD2014Osd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSD__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

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
StructOsdInfo g_stOsdInfo;

WORD g_usAdjustValue;
WORD g_usBackupValue;
BYTE g_ucLogoTimerCounter;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserOsdHandler(void);
void RTDOsdSystemFlowProc(void);
void RTDOsdEventMsgProc(void);

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : OSD Handler, executed in the main loop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserOsdHandler(void)
{
    RTDOsdSystemFlowProc();
    RTDOsdEventMsgProc();
}

//--------------------------------------------------
// Description  : OSD system flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDOsdSystemFlowProc(void)
{
    switch(SysModeGetModeState())
    {
        case _MODE_STATUS_POWER_OFF:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
            }

            break;

        case _MODE_STATUS_INITIAL:

            if(SysModeGetModeStateChange() == _TRUE)
            {
#if(_FREESYNC_OD_MEASURE == _ON)
                UserAdjustFREESYNCODMeasure();
#endif

                OsdDispShowLogo();
                UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
                ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
            }

            break;

        case _MODE_STATUS_SEARCH:

            if(SysModeGetModeStateChange() == _TRUE)
            {
#if(_FREEZE_SUPPORT == _ON)
                if(GET_OSD_FREEZE_STATUS() == _ON)
                {
                    SET_OSD_FREEZE_STATUS(_OFF);
                }
#endif
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    UserInterfaceKeyPadLedControl(_LED_POWER_SEARCH);
                }
            }

            break;

        case _MODE_STATUS_DISPLAY_SETTING:

            break;

        case _MODE_STATUS_ACTIVE:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    UserInterfaceKeyPadLedControl(_LED_POWER_ACTIVE);
                }
            }

            break;

        case _MODE_STATUS_NOSUPPORT:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOSUPPORT_MSG);
                    UserInterfaceKeyPadLedControl(_LED_POWER_NOSUPPORT);
                }
            }

            break;

        case _MODE_STATUS_NOSIGNAL:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                if(SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT)) == _TRUE)
                {
                    ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                }
                else
                {
                    ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
                }
            }

            break;

        case _MODE_STATUS_POWER_SAVING:

            if(SysSourceGetCableDetect(SysSourceGetInputPort()) == _FALSE)
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
            }

            if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
            {
                if(GET_OSD_POWER_SAVING_SHOW_SOURCE() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_SOURCE(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG);
                }
                else if(GET_OSD_WAKE_UP_SWITCH_DDCCI_PORT() == _TRUE)
                {
                    SET_OSD_WAKE_UP_SWITCH_DDCCI_PORT(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG);
                }
#if(_DP_SUPPORT == _ON)
                else if(GET_OSD_POWER_SAVING_SHOW_DP_OPTION() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_DP_OPTION(_FALSE);
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_DP_VERSIOM_MSG);
                }
#endif
#if(_DP_DEBUG_MSG == _ON)
                else if(GET_OSD_POWER_SAVING_SHOW_DP_INFO() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_DP_INFO(_FALSE);

                    OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
                    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
                }
#endif
            }

            break;

        case _MODE_STATUS_FACTORY:

            break;

        default:

            break;
    }

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
    // Check embedded DP switch status
    UserCommonAdjustEmbeddedDpSwitch();
#endif

    if(GET_KEYMESSAGE() < _KEY_AMOUNT)
    {
        // hot key
        if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) ||
           (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT) ||
           (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
           (SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
        {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
            if((GET_OSD_STATE() != _MENU_NONE) &&
               ((GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE) || (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) &&
               (GET_OSD_STATE() != _MENU_HOTKEY_SOURCE))
#else
            if((GET_OSD_STATE() != _MENU_NONE) && ((GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE) || (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)))
#endif
            {
                SET_KEYREPEATENABLE();
            }
        }

        if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
        {
            RTDFactoryMenuOperation();
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
        }
        else
        {
#if(_FREEZE_SUPPORT == _ON)
#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG) == _TRUE)
            {
                return;
            }
#else
            if(GET_FREEZE_DISABLE_MSG_STATE() == _ON)
            {
                return;
            }
#endif
#endif
            // back up previous OSD State
            SET_OSD_STATE_PREVIOUS(GET_OSD_STATE());

#if(_FREEZE_SUPPORT == _ON)
            if(GET_OSD_FREEZE_STATUS() == _ON) // Confirm whether disable the freeze status
            {
                if(OsdFuncCheckFreezeDisable() == _TRUE)
                {
                    return;
                }
            }
#endif

            if((GET_OSD_STATE() >= _MENU_PICTURE) && (GET_OSD_STATE() <= _MENU_COLOR_PCM_SOFT_PROFT_ADJUST))
            {
                OsdDispMainMenuKeyInfo(GET_KEYMESSAGE(), _OSD_HIGHLIGHT);
            }

            (*OperationTable[GET_OSD_STATE()])();

            if(GET_OSD_IN_FACTORY_MENU_STATUS() == _FALSE)
            {
                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
                {
                    if(GET_OSD_TIME_OUT() <= 10)
                    {
                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
                    }
                }
            }


/*
            if((GET_OSD_STATE() >= _MENU_NONE) &&
                (GET_OSD_STATE() < _MENU_END) &&
                ((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)))
            {
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }
            else//(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
            }

            if(GET_OSD_IN_FACTORY_MENU_STATUS())
            {
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
            }
*/
        }
    }
}

//--------------------------------------------------
// Description  : OSD event message processing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDOsdEventMsgProc(void)
{
    switch(GET_OSD_EVENT_MESSAGE())
    {
        case _OSDEVENT_SHOW_NOSIGNAL_MSG:
            OsdDispOsdMessage(_OSD_DISP_NOSIGNAL_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOCABLE_MSG:
            OsdDispOsdMessage(_OSD_DISP_NOCABLE_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOSUPPORT_MSG:

            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

            OsdDispOsdMessage(_OSD_DISP_NOSUPPORT_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG:
            OsdDispOsdMessage(_OSD_DISP_FAIL_SAFE_MODE_MSG);
            break;

        case _OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG:
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            SET_OSD_STATE(_MENU_HOTKEY_SOURCE);
            OsdFuncSetOsdItemFlag();
            g_usBackupValue = GET_OSD_INPUT_PORT_OSD_ITEM();
            OsdDispHotKeySourceMenu();

            ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            break;

        case _OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG:

            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            SET_OSD_STATE(_MENU_HOTKEY_DDCCI);
            OsdDispHotKeyOptionMenu(_HOTKEY_DDCCI);
            ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

            break;

        case _OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG:
            OsdDispDisableOsd();
            OsdDispOsdMessage(_OSD_DISP_POWER_SAVING_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            break;

        case _OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG:

            OsdDispDisableOsd();
            SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_DO_AUTO_CONFIG_MSG:
#if(_FREEZE_SUPPORT == _ON)
            ScalerTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
#endif
            OsdDispAutoConfigProc();
            break;
#endif

        case _OSDEVENT_ACTIVE_DO_ONE_TIME_MSG:

#if(_FREEZE_SUPPORT == _ON)
            ScalerTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
#endif

#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                if(UserInterfaceGetFirstAutoConfigStatus() == _TRUE)
                {
                    OsdDispAutoConfigProc();
                }
            }
#endif

            if(GET_OSD_STATE() == _MENU_NONE)
            {
                OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
                ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            break;

        case _OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG:
            UserCommonNVRamSaveSystemData();
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG:
            UserCommonNVRamSaveModeUserData();
            break;
#endif
        case _OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG:
            RTDNVRamSaveOSDData();
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_SAVE_NVRAM_ADCDATA_MSG:
            if(ScalerColorGetColorSpaceRGB(UserCommonInterfaceGetColorFormat()) == _TRUE)
            {
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
            }
            else
            {
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
            }
            break;
#endif

        case _OSDEVENT_SAVE_NVRAM_COLORPROC_MSG:
            RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
            break;

        case _OSDEVENT_SAVE_NVRAM_BRICON_MSG:
            RTDNVRamSaveBriCon(SysSourceGetSourceType());
            break;

        case _OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG:
            RTDNVRamSaveSixColorData();
            break;

#if(_DP_SUPPORT == _ON)
        case _OSDEVENT_DP_VERSIOM_MSG:
            SET_OSD_STATE(_MENU_HOTKEY_DP_OPTION);

            if(SysSourceGetSourceType() == _SOURCE_DP)
            {
                if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                {
                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D0_OPTION);
                }
                else if(SysSourceGetInputPort() == _D1_INPUT_PORT)
                {
                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D1_OPTION);
                }
                else if(SysSourceGetInputPort() == _D2_INPUT_PORT)
                {
                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D2_OPTION);
                }
                else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                {
                    OsdDispHotKeyOptionMenu(_HOTKEY_DP_D6_OPTION);
                }
            }
            else
            {
#if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D0_OPTION);
#elif (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D1_OPTION);
#elif (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D2_OPTION);
#elif (_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D6_OPTION);
#else
                SET_OSD_STATE(_MENU_NONE);
#endif
            }

            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            break;
#endif

        default:
            break;
    }

    SET_OSD_EVENT_MESSAGE(_OSDEVENT_NONE_MSG);
}


void MenuNone(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                SET_OSD_STATE(_MENU_PICTURE);
                OsdFuncSetOsdItemFlag();
                OsdDispMainMenu();
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            // input source
            CLR_KEYREPEATENABLE();

            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
                SET_OSD_POWER_SAVING_SHOW_SOURCE(_TRUE);

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            else if((SysModeGetModeState() == _MODE_STATUS_NOSUPPORT) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG);
            }
            else if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                SET_OSD_STATE(_MENU_HOTKEY_SOURCE);
                OsdFuncSetOsdItemFlag();
                g_usBackupValue = GET_OSD_INPUT_PORT_OSD_ITEM();
                OsdDispHotKeySourceMenu();
            }
            break;

        case _LEFT_KEY_MESSAGE:

            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                // active show input information
                OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
                ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_DISABLE);
            }
#if(_DP_DEBUG_MSG == _ON)
            else if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
                SET_OSD_POWER_SAVING_SHOW_DP_INFO(_TRUE);

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            else
            {
                OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            }

#endif

            break;

        case _EXIT_KEY_MESSAGE:
            // auto adjust
#if(_VGA_SUPPORT == _ON)
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_FAIL_SAFE_MODE() == _FALSE) && (SysSourceGetSourceType() == _SOURCE_VGA))
            {
#if(_FREEZE_SUPPORT == _ON)
                if(GET_OSD_FREEZE_STATUS() == _ON)
                {
                    SET_OSD_FREEZE_STATUS(_OFF);
                    UserCommonAdjustDisplayFreeze(GET_OSD_FREEZE_STATUS());
                    OsdDispOsdMessage(_OSD_DISP_DISABLE_FREEZE_MSG);
                    ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
                }
#endif

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
            }
#endif
            // ddcci
            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
                SET_OSD_WAKE_UP_SWITCH_DDCCI_PORT(_TRUE);

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            else if((SysModeGetModeState() == _MODE_STATUS_NOSUPPORT) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG);
            }

            break;

        default:
            break;
    }
}

void MenuPicture(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
#if (_SHARPNESS_SUPPORT == _ON)
                SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_PICTURE_0);
                OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_SHARPNESS());
#endif
                return;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
#if (_SHARPNESS_SUPPORT == _ON)
                SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_PICTURE_0);
                OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_SHARPNESS());
#endif
                return;
            }
#endif
            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_PICTURE_0);

            // OsdDispMainMenuKeyInfo(_KEY_INFO_BACK, _OSD_UNSELECT);
            OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAY);

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_FACTORY);

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
            if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
               (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
            {
                OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdHeight, 5);
            }
            else
#endif
            {
                OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdWidth, 5);
            }
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FACTORY_0);

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuDisplay(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                SET_OSD_STATE(_MENU_DISPLAY_AUTO);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_0);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            }
            else
#endif
            {
                SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
                if((GET_OSD_DISP_ROTATE() >= _DISP_ROTATE_0 + 4))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
                }
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuColor(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
                if(GET_OSD_HDR_LIGHT_ENHANCE() != 0)
                    break;
#endif
#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
                if(GET_OSD_HDR_COLOR_ENHANCE() != 0)
                    break;
#endif
                SET_OSD_STATE(_MENU_COLOR_EFFECT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());

                if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
                }
                break;
            }
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
            if(GET_OSD_LOCAL_DIMMING() == _ON)
            {
                SET_OSD_STATE(_MENU_COLOR_GAMMA);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
                OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());
                if(GET_OSD_GAMMA() == _GAMMA_24)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
                }
                break;
            }
#endif
#if(_SDR_TO_HDR_SUPPORT == _ON)
            if(GET_OSD_SDR_TO_HDR() == _ON)
            {
                break;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                SET_OSD_STATE(_MENU_COLOR_EFFECT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());

                if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
                }
                break;
            }
#endif

            SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuAdvance(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_ITEM_INDEX(0);
            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            if((SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP) || (SysSourceGetInputPort() <= _D1_INPUT_PORT))
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
            }
            else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
            }

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuInput(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = SysSourceGetInputPort();
            if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                SET_OSD_STATE(_MENU_INPUT_AUTO);
            }
            else
            {
                switch(SysSourceGetInputPort())
                {
                    case _A0_INPUT_PORT:
                        SET_OSD_STATE(_MENU_INPUT_A0_PORT);
                        break;

                    case _D0_INPUT_PORT:
                        SET_OSD_STATE(_MENU_INPUT_D0_PORT);
                        break;

                    case _D1_INPUT_PORT:
                        SET_OSD_STATE(_MENU_INPUT_D1_PORT);
                        break;

                    case _D2_INPUT_PORT:
                        SET_OSD_STATE(_MENU_INPUT_D2_PORT);
                        break;

                    case _D3_INPUT_PORT:
                        SET_OSD_STATE(_MENU_INPUT_D3_PORT);
                        break;

                    case _D4_INPUT_PORT:
                        SET_OSD_STATE(_MENU_INPUT_D4_PORT);
                        break;

                    case _D5_INPUT_PORT:
                        SET_OSD_STATE(_MENU_INPUT_D5_PORT);
                        break;

                    case _D6_INPUT_PORT:
                        SET_OSD_STATE(_MENU_INPUT_D6_PORT);
                        break;

                    default:
                        break;
                }
            }

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _SELECT, SysSourceGetScanType());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuAudio(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_VOLUME);

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_AUDIO_0);
            OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            if((SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP) || (SysSourceGetInputPort() <= _D1_INPUT_PORT))
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
            }
            else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuOther(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_RESET);

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_0);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INFORMATION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INFORMATION_0);
            OsdDispShowInformation();
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuInformation(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_FACTORY);

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
            if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
               (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
            {
                OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdHeight, 5);
            }
            else
#endif
            {
                OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdWidth, 5);
            }
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FACTORY_0);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
            if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
               (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
            {
                OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdHeight, 5);
            }
            else
#endif
            {
                OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdWidth, 5);
            }
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuFactory(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDispDisableOsd();
            ScalerOsdMapRotation(0, _ENABLE, HEIGHT(_FACTORY_OSD_ROW), _DISABLE, 0, _DISABLE);
            RTDFactoryMainMenu();
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INFORMATION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INFORMATION_0);
            OsdDispShowInformation();
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuPictureBacklight(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_BACKLIGHT();

            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
#if (_BRIGHTNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_BRIGHTNESS());
#elif (_CONTRAST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST());
#elif (_SHARPNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS());
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            OsdDispMainMenuKeyInfo(_KEY_INFO_EXIT, _OSD_UNSELECT);
            break;

        default:
            break;
    }
}

void MenuPictureBrightness(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_BRIGHTNESS();

            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
#if (_CONTRAST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST());
#elif (_SHARPNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS());
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            break;

        default:
            break;
    }
}

void MenuPictureContrast(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_CONTRAST();

            SET_OSD_STATE(_MENU_PICTURE_CONTRAST_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_SHARPNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS());
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if (_BRIGHTNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_BRIGHTNESS());
#else
            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            break;

        default:
            break;
    }
}

void MenuPictureSharpness(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_SHARPNESS();

            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
                break;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                break;
            }
#endif

#if (_CONTRAST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST());
#elif (_BRIGHTNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_BRIGHTNESS());
#else
            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            break;

        default:
            break;
    }
}

void MenuDisplayAuto(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainSubString(_AUTO_CONFIG_DO);
                OsdDispSliderAndNumber(_MENU_DISPLAY_AUTO, 0);
                OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
                OsdDispMainSubString(_AUTO_CONFIG_RESULT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispClearSelectColor(_DOWN);
            OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
            SET_OSD_STATE(_MENU_DISPLAY_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS, GET_VGA_MODE_ADJUST_H_POSITION());
            }
            else
#endif
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS, GET_DIGITAL_H_POSITION());
            }

            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
            OsdDispClearSelectColor(_DOWN);
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
            break;

        default:
            break;
    }
}




void MenuDisplayHPos(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                g_usBackupValue = GET_VGA_MODE_ADJUST_H_POSITION();
            }
            else
#endif
            {
                g_usBackupValue = GET_DIGITAL_H_POSITION();
            }

            SET_OSD_STATE(_MENU_DISPLAY_HPOS_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAY_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_VPOS, GET_VGA_MODE_ADJUST_V_POSITION());
            }
            else
#endif
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_VPOS, GET_DIGITAL_V_POSITION());
            }
            break;

        case _LEFT_KEY_MESSAGE:

#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                SET_OSD_STATE(_MENU_DISPLAY_AUTO);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSliderAndNumber();
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
            break;

        default:
            break;
    }
}

void MenuDisplayVPos(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                g_usBackupValue = GET_VGA_MODE_ADJUST_V_POSITION();
            }
            else
#endif
            {
                g_usBackupValue = GET_DIGITAL_V_POSITION();
            }

            SET_OSD_STATE(_MENU_DISPLAY_VPOS_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                SET_OSD_STATE(_MENU_DISPLAY_CLOCK);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispSliderAndNumber(_MENU_DISPLAY_CLOCK, GET_VGA_MODE_ADJUST_CLOCK());
            }
            else
#endif
            {
                SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
                OsdDispClearSliderAndNumber();
                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
                if((GET_OSD_DISP_ROTATE() >= _DISP_ROTATE_0 + 4))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
                }
            }
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAY_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS, GET_VGA_MODE_ADJUST_H_POSITION());
            }
            else
#endif
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS, GET_DIGITAL_H_POSITION());
            }

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
            break;

        default:
            break;
    }
}

void MenuDisplayClock(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            g_usBackupValue = GET_VGA_MODE_ADJUST_CLOCK();
            SET_OSD_STATE(_MENU_DISPLAY_CLOCK_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usBackupValue, _SLIDER_0, _SELECT);
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                WORD usUserIHTotal = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                usUserIHTotal = UserCommonAdjustRealValueToPercent(g_usBackupValue, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _SELECT);
            }
#endif

#endif
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                SET_OSD_STATE(_MENU_DISPLAY_PHASE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
                OsdDispSliderAndNumber(_MENU_DISPLAY_PHASE, GET_VGA_MODE_ADJUST_PHASE());
            }
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAY_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_VPOS, GET_VGA_MODE_ADJUST_V_POSITION());
            }
#endif


            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
            break;

        default:
            break;
    }
}

void MenuDisplayPhase(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            g_usBackupValue = GET_VGA_MODE_ADJUST_PHASE();

            SET_OSD_STATE(_MENU_DISPLAY_PHASE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            // OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());

            if((GET_OSD_DISP_ROTATE() >= _DISP_ROTATE_0 + 4))
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
            }
            break;

        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                SET_OSD_STATE(_MENU_DISPLAY_CLOCK);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_0);
                OsdDispSliderAndNumber(_MENU_DISPLAY_CLOCK, GET_VGA_MODE_ADJUST_CLOCK());
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);
            break;

        default:
            break;
    }
}

void MenuDisplayDispRotate(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            g_usBackupValue = GET_OSD_DISP_ROTATE();
            SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _SELECT, GET_OSD_DISP_ROTATE());
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
            if(GET_OSD_DISP_ROTATE() == _DISP_ROTATE_0)
            {
                SET_OSD_STATE(_MENU_DISPLAY_LATENCY);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_LATENCY);
            }
#elif(_FREEZE_SUPPORT == _ON)

            SET_OSD_STATE(_MENU_DISPLAY_FREEZE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);

#endif
            break;

        case _LEFT_KEY_MESSAGE:

#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_DISPLAY_PHASE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispSliderAndNumber(_MENU_DISPLAY_PHASE, GET_VGA_MODE_ADJUST_PHASE());
            }
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);

            break;

        default:
            break;
    }
}

void MenuDisplayLatency(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
            g_usBackupValue = GET_OSD_LATENCY();
            SET_OSD_STATE(_MENU_DISPLAY_LATENCY_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _SELECT, GET_OSD_LATENCY());
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_FREEZE_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAY_FREEZE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
#endif
            break;

        case _LEFT_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            // OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
            OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
            if((GET_OSD_DISP_ROTATE() >= (_DISP_ROTATE_0 + 4)))
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);

            break;

        default:
            break;
    }
}

void MenuDislayFreeze(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_FREEZE_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAY_FREEZE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, GET_OSD_FREEZE_STATUS());
            g_usBackupValue = GET_OSD_FREEZE_STATUS();
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
            if(GET_OSD_DISP_ROTATE() == _DISP_ROTATE_0)
            {
                SET_OSD_STATE(_MENU_DISPLAY_LATENCY);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_LATENCY);
            }
#else
            SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
            if((GET_OSD_DISP_ROTATE() >= _DISP_ROTATE_0 + 4))
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAY_0);

            break;

        default:
            break;
    }
}

void MenuColorPanelUniformity(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_PANEL_UNIFORMITY();
            SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _SELECT, GET_OSD_PANEL_UNIFORMITY());

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_GAMMA);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());

            if(GET_OSD_GAMMA() == _GAMMA_24)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
            }

            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);

            break;

        default:
            break;
    }
}



void MenuColorGamma(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(GET_OSD_PANEL_UNIFORMITY() == _ON)
            {
                g_usBackupValue = _FROM_STATE_GAMMA;
                g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY();
                OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
                SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
            }
            else
            {
                g_usBackupValue = GET_OSD_GAMMA();

                SET_OSD_STATE(_MENU_COLOR_GAMMA_ADJUST);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _SELECT, GET_OSD_GAMMA());
            }
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_CONTRAST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE());
            if(GET_COLOR_TEMP_TYPE() >= _CT_SRGB)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
            }
#else
            SET_OSD_STATE(_MENU_COLOR_EFFECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());

            if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
            }
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
            if(GET_OSD_LOCAL_DIMMING() == _ON)
            {
                break;
            }
#endif
            SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorTemperature(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_COLOR_TEMP_TYPE();

            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFFECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());

            if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
            }
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_GAMMA);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());

            if(GET_OSD_GAMMA() == _GAMMA_24)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorEffect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT();

            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
                break;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                break;
            }
#endif

            SET_OSD_STATE(_MENU_COLOR_DEMO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
            if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
            }

            break;

        case _LEFT_KEY_MESSAGE:
#if(_HDR10_SUPPORT == _ON)
            if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
            {
                break;
            }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                break;
            }
#endif

#if(_CONTRAST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE());


            if(GET_COLOR_TEMP_TYPE() >= _CT_SRGB)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
            }
#else
            SET_OSD_STATE(_MENU_COLOR_GAMMA);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());

            if(GET_OSD_GAMMA() == _GAMMA_24)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorDemo(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_HLWIN_TYPE();

            SET_OSD_STATE(_MENU_COLOR_DEMO_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _SELECT, GET_OSD_HLWIN_TYPE());
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_COLOR_FORMAT_CONVERT == _ON)
            if((SysSourceGetSourceType() == _SOURCE_VGA) || (SysSourceGetSourceType() == _SOURCE_DVI))
            {
                SET_OSD_STATE(_MENU_COLOR_FORMAT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_FORMAT);
            }
            else
#endif
            {
                SET_OSD_STATE(_MENU_COLOR_PCM);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                if(GET_OSD_PCM_STATUS() >= _PCM_OSD_SOFT_PROFT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
                }
                else
#endif
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }
            }
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFFECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());

            if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorFormat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_FORMAT();

            SET_OSD_STATE(_MENU_COLOR_FORMAT_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _SELECT, GET_OSD_COLOR_FORMAT());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_PCM);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
            if(GET_OSD_PCM_STATUS() >= _PCM_OSD_SOFT_PROFT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
            }
            else
#endif
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
            }
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_DEMO);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorPCM(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(GET_OSD_PANEL_UNIFORMITY() == _ON)
            {
                g_usBackupValue = _FROM_STATE_PCM;
                g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY();
                OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
                SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
            }
            else
            {
                g_usBackupValue = GET_OSD_PCM_STATUS();
                SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_HUE, GET_OSD_HUE());

            break;

        case _LEFT_KEY_MESSAGE:
#if(_COLOR_FORMAT_CONVERT == _ON)
            if((SysSourceGetSourceType() == _SOURCE_VGA) || (SysSourceGetSourceType() == _SOURCE_DVI))
            {
                SET_OSD_STATE(_MENU_COLOR_FORMAT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_FORMAT);
            }
            else
#endif
            {
                SET_OSD_STATE(_MENU_COLOR_DEMO);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());

                if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}


void MenuColorHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_HUE();

            SET_OSD_STATE(_MENU_COLOR_HUE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_SATURATION);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_SATURATION, GET_OSD_SATURATION());
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_COLOR_PCM);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
            if(GET_OSD_PCM_STATUS() >= _PCM_OSD_SOFT_PROFT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
            }
            else
#endif
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorSaturation(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_SATURATION();

            SET_OSD_STATE(_MENU_COLOR_SATURATION_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_HUE);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_HUE, GET_OSD_HUE());
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}
void MenuAdvanceItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDispAdvanceItemSelect(GET_OSD_ITEM_INDEX());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDispAdvanceItemCountbyKeyMessage() == _FALSE)
                break;

            OsdDispMainMenuItemSelection((GET_OSD_ITEM_INDEX() % 4), _OSD_SELECT);
            OsdDispMainMenuItemIndication2(GET_OSD_ITEM_INDEX(), GET_OSD_STATE(), _OSD_SELECT);
            OsdDispClearSliderAndNumber();
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispAdvanceItemSwitch(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            SET_OSD_ITEM_INDEX(0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE);
            break;

        default:
            break;
    }
}


void MenuInputAuto(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(SysSourceGetScanType() != _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
                {
                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                }

#if(_DP_MST_SUPPORT == _ON)
                UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                RTDNVRamSaveOSDData();
#endif
            }
            else
            {
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_INPUT_A0_PORT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysSourceGetScanType() != _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                }
                else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}


void MenuInputA0Port(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _A0_INPUT_PORT))
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
                SysSourceSwitchInputPort(_A0_INPUT_PORT);
                SET_OSD_STATE(_MENU_INPUT);
                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                }

#if(_DP_MST_SUPPORT == _ON)
                UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                RTDNVRamSaveOSDData();
#endif
            }
            else
            {
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D0_PORT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_AUTO);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            else if(SysSourceGetInputPort() != _A0_INPUT_PORT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                }
                else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuInputD0Port(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D0_INPUT_PORT))
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
                SysSourceSwitchInputPort(_D0_INPUT_PORT);
                SET_OSD_STATE(_MENU_INPUT);
                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                }

#if(_DP_MST_SUPPORT == _ON)
                UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                RTDNVRamSaveOSDData();
#endif
            }
            else
            {
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D1_PORT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_A0_PORT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            else if(SysSourceGetInputPort() != _D0_INPUT_PORT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                }
                else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuInputD1Port(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D1_INPUT_PORT))
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
                SysSourceSwitchInputPort(_D1_INPUT_PORT);
                SET_OSD_STATE(_MENU_INPUT);
                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                }

#if(_DP_MST_SUPPORT == _ON)
                UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                RTDNVRamSaveOSDData();
#endif
            }
            else
            {
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D2_PORT);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D0_PORT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            else if(SysSourceGetInputPort() != _D1_INPUT_PORT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                }
                else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}


void MenuInputD2Port(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D2_INPUT_PORT))
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
                SysSourceSwitchInputPort(_D2_INPUT_PORT);
                SET_OSD_STATE(_MENU_INPUT);
                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                }

#if(_DP_MST_SUPPORT == _ON)
                UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                RTDNVRamSaveOSDData();
#endif
            }
            else
            {
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D3_PORT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D1_PORT);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
            }
            else if(SysSourceGetInputPort() != _D2_INPUT_PORT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                }
                else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuInputD3Port(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D3_INPUT_PORT))
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
                SysSourceSwitchInputPort(_D3_INPUT_PORT);
                SET_OSD_STATE(_MENU_INPUT);
                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                }

#if(_DP_MST_SUPPORT == _ON)
                UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                RTDNVRamSaveOSDData();
#endif
            }
            else
            {
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D4_PORT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D2_PORT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
            }
            else if(SysSourceGetInputPort() != _D3_INPUT_PORT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                }
                else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuInputD4Port(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D4_INPUT_PORT))
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
                SysSourceSwitchInputPort(_D4_INPUT_PORT);
                SET_OSD_STATE(_MENU_INPUT);
                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                }

#if(_DP_MST_SUPPORT == _ON)
                UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                RTDNVRamSaveOSDData();
#endif
            }
            else
            {
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D5_PORT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D3_PORT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
            }
            else if(SysSourceGetInputPort() != _D4_INPUT_PORT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                }
                else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}


void MenuInputD5Port(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D5_INPUT_PORT))
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
                SysSourceSwitchInputPort(_D5_INPUT_PORT);
                SET_OSD_STATE(_MENU_INPUT);
                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                }

#if(_DP_MST_SUPPORT == _ON)
                UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                RTDNVRamSaveOSDData();
#endif
            }
            else
            {
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D6_PORT);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D4_PORT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());


            break;

        case _EXIT_KEY_MESSAGE:
            if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
            }
            else if(SysSourceGetInputPort() != _D5_INPUT_PORT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                }
                else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}


void MenuInputD6Port(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
            if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetInputPort() != _D6_INPUT_PORT))
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
                SysSourceSwitchInputPort(_D6_INPUT_PORT);
                SET_OSD_STATE(_MENU_INPUT);
                SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                   (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                }

#if(_DP_MST_SUPPORT == _ON)
                UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                RTDNVRamSaveOSDData();
#endif
            }
            else
            {
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_D5_PORT);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_INPUT, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
            }
            else if(SysSourceGetInputPort() != _D6_INPUT_PORT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
                if(SysSourceGetInputPort() <= _D1_INPUT_PORT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                }
                else if((SysSourceGetInputPort() >= _D2_INPUT_PORT) || (SysSourceGetInputPort() <= _D5_INPUT_PORT))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());
            }
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuAudioVolume(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_VOLUME();

            SET_OSD_STATE(_MENU_AUDIO_VOLUME_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME_ADJUST, GET_OSD_VOLUME());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_AUDIO_MUTE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        default:
            break;
    }
}

void MenuAudioMute(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_VOLUME_MUTE();

            SET_OSD_STATE(_MENU_AUDIO_MUTE_ON_OFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _SELECT, GET_OSD_VOLUME_MUTE());

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);

            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            SET_OSD_STATE(_MENU_AUDIO_VOLUME);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        default:
            break;
    }
}

void MenuAudioStandAlong(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_AUDIO_STAND_ALONE();

            SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG_SELECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _SELECT, GET_OSD_AUDIO_STAND_ALONE());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);

            if((SysSourceGetSourceType() == _SOURCE_VGA) ||
               (SysSourceGetSourceType() == _SOURCE_DVI))
            {
                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, _LINE_IN_AUDIO);
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
            }

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_SOURCE);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_MUTE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        default:
            break;
    }
}

void MenuAudioAudioSource(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if((SysSourceGetSourceType() != _SOURCE_VGA) &&
               (SysSourceGetSourceType() != _SOURCE_DVI))
            {
                g_usBackupValue = GET_OSD_AUDIO_SOURCE();

                SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE_SELECT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _SELECT, GET_OSD_AUDIO_SOURCE());
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_AUDIO_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        default:
            break;
    }
}

void MenuAudioSoundMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE_SELECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_AUDIO_AUDIO_SELF_TEST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, _OFF);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_AUDIO_0);

            if((SysSourceGetSourceType() == _SOURCE_VGA) ||
               (SysSourceGetSourceType() == _SOURCE_DVI))
            {
                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, _LINE_IN_AUDIO);
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
            }

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_SOURCE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        default:
            break;
    }
}
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
void MenuAudioAudioSelfTest(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_AUDIO_SELF_TEST_SELECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _OFF);
            g_usBackupValue = _OFF;
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        default:
            break;
    }
}
#endif

void MenuOtherReset(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDispOsdReset();
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME, GET_OSD_TIME_OUT());
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherMenuTime(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_TIME_OUT();

            SET_OSD_STATE(_MENU_OTHER_MENU_TIME_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME_ADJUST, GET_OSD_TIME_OUT());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS, GET_OSD_HPOS());
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER_RESET);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherOsdHPos(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_HPOS();

            SET_OSD_STATE(_MENU_OTHER_OSD_HPOS_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS_ADJUST, GET_OSD_HPOS());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS, GET_OSD_VPOS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME, GET_OSD_TIME_OUT());
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherOsdVPos(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_VPOS();

            SET_OSD_STATE(_MENU_OTHER_OSD_VPOS_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS_ADJUST, GET_OSD_VPOS());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_1);
            OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _UNSELECT, GET_OSD_LANGUAGE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OSD_LANGUAGE);

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS, GET_OSD_HPOS());
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherLanguage(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_LANGUAGE();

            SET_OSD_STATE(_MENU_OTHER_LANGUAGE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _SELECT, GET_OSD_LANGUAGE());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY, GET_OSD_TRANSPARENCY_STATUS());
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_0);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS, GET_OSD_VPOS());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherTransparency(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_TRANSPARENCY_STATUS();

            SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY_ADJUST, GET_OSD_TRANSPARENCY_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _UNSELECT, GET_OSD_ROTATE_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OSD_ROTATE);
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _UNSELECT, GET_OSD_LANGUAGE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OSD_LANGUAGE);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherRotate(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_ROTATE_STATUS();

            SET_OSD_STATE(_MENU_OTHER_ROTATE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _SELECT, GET_OSD_ROTATE_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY, GET_OSD_TRANSPARENCY_STATUS());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuPictureBacklightAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_BACKLIGHT())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT_ADJUST, GET_OSD_BACKLIGHT());
            UserAdjustBacklight(GET_OSD_BACKLIGHT());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_BACKLIGHT())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_BACKLIGHT(g_usAdjustValue);
                UserAdjustBacklight(GET_OSD_BACKLIGHT());
            }
            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        default:
            break;
    }
}

void MenuPictureBrightnessAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_BRIGHTNESS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
            }

            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS_ADJUST, GET_OSD_BRIGHTNESS());

#if(_BRIGHTNESS_SUPPORT == _ON)
            UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_BRIGHTNESS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_BRIGHTNESS(g_usAdjustValue);

#if(_BRIGHTNESS_SUPPORT == _ON)
                UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
            }
            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        default:
            break;
    }
}

void MenuPictureContrastAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CONTRAST())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_BRICON_MSG);
            }

            SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST_ADJUST, GET_OSD_CONTRAST());

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CONTRAST())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_CONTRAST(g_usAdjustValue);

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            }
            SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        default:
            break;
    }
}

void MenuPictureSharpnessAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS_ADJUST, GET_OSD_SHARPNESS());
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_SHARPNESS_SUPPORT == _ON)
            UserCommonAdjustSharpness(SysSourceGetInputPort());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SHARPNESS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_SHARPNESS(g_usAdjustValue);
#if(_SHARPNESS_SUPPORT == _ON)
                UserCommonAdjustSharpness(SysSourceGetInputPort());
#endif
            }
            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_SHARPNESS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}
void MenuDisplayHPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                if(g_usBackupValue != GET_VGA_MODE_ADJUST_H_POSITION())
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
            }
            else
#endif
            {
                if(g_usBackupValue != GET_DIGITAL_H_POSITION())
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
            }

            SET_OSD_STATE(_MENU_DISPLAY_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS_ADJUST, GET_VGA_MODE_ADJUST_H_POSITION());
                UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION());
            }
            else
#endif
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_HPOS_ADJUST, GET_DIGITAL_H_POSITION());
                UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
            }
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAY_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                if(g_usBackupValue != GET_VGA_MODE_ADJUST_H_POSITION())
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_VGA_MODE_ADJUST_H_POSITION(g_usAdjustValue);
                    UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION());
                }
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_H_POSITION(), _SLIDER_0, _UNSELECT);
                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            }
            else
#endif
            {
                if(g_usBackupValue != GET_DIGITAL_H_POSITION())
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_DIGITAL_H_POSITION(g_usAdjustValue);
                    UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
                }
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_DIGITAL_H_POSITION(), _SLIDER_0, _UNSELECT);
                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_DIGITAL_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            }

            break;

        default:
            break;
    }
}

void MenuDisplayVPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                if(g_usBackupValue != GET_VGA_MODE_ADJUST_V_POSITION())
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
            }
            else
#endif
            {
                if(g_usBackupValue != GET_DIGITAL_V_POSITION())
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
            }

            SET_OSD_STATE(_MENU_DISPLAY_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_VPOS_ADJUST, GET_VGA_MODE_ADJUST_V_POSITION());
                UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION());
            }
            else
#endif
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_VPOS_ADJUST, GET_DIGITAL_V_POSITION());
                UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
            }
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAY_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                if(g_usBackupValue != GET_VGA_MODE_ADJUST_V_POSITION())
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_VGA_MODE_ADJUST_V_POSITION(g_usAdjustValue);
                    UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION());
                }
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_V_POSITION(), _SLIDER_0, _UNSELECT);
                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            }
            else
#endif
            {
                if(g_usBackupValue != GET_DIGITAL_V_POSITION())
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_DIGITAL_V_POSITION(g_usAdjustValue);
                    UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
                }
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_DIGITAL_V_POSITION(), _SLIDER_0, _UNSELECT);
                OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_DIGITAL_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            }

            break;

        default:
            break;
    }
}

void MenuDisplayClockAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_CLOCK())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
            }
#endif
            SET_OSD_STATE(_MENU_DISPLAY_CLOCK);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                WORD usUserIHTotal = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                usUserIHTotal = UserCommonAdjustRealValueToPercent(g_usAdjustValue, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _UNSELECT);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            OsdDispSliderAndNumber(_MENU_DISPLAY_CLOCK_ADJUST, GET_VGA_MODE_ADJUST_CLOCK());
            UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_CLOCK())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
                UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
            }
            SET_OSD_STATE(_MENU_DISPLAY_CLOCK);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_CLOCK(), _SLIDER_0, _UNSELECT);
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                WORD usUserIHTotal = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                usUserIHTotal = UserCommonAdjustRealValueToPercent(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _UNSELECT);
            }
#endif
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_CLOCK(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
#endif

            break;

        default:
            break;
    }
}

void MenuDisplayPhaseAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_PHASE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
            }
#endif
            SET_OSD_STATE(_MENU_DISPLAY_PHASE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            OsdDispSliderAndNumber(_MENU_DISPLAY_PHASE_ADJUST, GET_VGA_MODE_ADJUST_PHASE());
            UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_PHASE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_VGA_MODE_ADJUST_PHASE(g_usAdjustValue);
                UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
            }
            SET_OSD_STATE(_MENU_DISPLAY_PHASE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_PHASE(), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_PHASE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
#endif
            break;

        default:
            break;
    }
}

void MenuDisplayDispRotateAdjust(void)
{
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DISP_ROTATE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            // OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
            OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
            break;

        case _RIGHT_KEY_MESSAGE:
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_OSD_DISP_ROTATE() != (_DISP_ROTATE_AMOUNT - 1)))
            {
                if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0 + 3))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
                }
                OsdDispSliderAndNumber(_MENU_DISPLAY_DISP_ROTATE_ADJUST, GET_OSD_DISP_ROTATE());

#if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
                if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0 + 1))
                {
                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
                }
#endif
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_OSD_DISP_ROTATE() != _DISP_ROTATE_0))
            {
                if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0 + 4))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
                }
                OsdDispSliderAndNumber(_MENU_DISPLAY_DISP_ROTATE_ADJUST, GET_OSD_DISP_ROTATE());

#if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
                if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0))
                {
                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
                }
#endif
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if(g_usBackupValue != GET_OSD_DISP_ROTATE())
                {
                    SET_OSD_DISP_ROTATE(g_usBackupValue);

                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);

                    if(GET_OSD_DISP_ROTATE() >= (_DISP_ROTATE_0 + 4))
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
                    }
                    else
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
                    }
                }
                SET_OSD_STATE(_MENU_DISPLAY_DISP_ROTATE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
#if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAY_1);
#endif
            }
            break;

        default:
            break;
    }
#endif
}

void MenuDisplayLatencyAdjust(void)
{
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_LATENCY())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_DISPLAY_LATENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());

            break;

        case _RIGHT_KEY_MESSAGE:
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_OSD_LATENCY() != _LATENCY_H))
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_LATENCY_ADJUST, GET_OSD_LATENCY());

                // Set Backlight OFF to prevent garbage
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }

            break;

        case _LEFT_KEY_MESSAGE:

            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_OSD_LATENCY() != _LATENCY_L))
            {
                OsdDispSliderAndNumber(_MENU_DISPLAY_LATENCY_ADJUST, GET_OSD_LATENCY());

                // Set Backlight OFF to prevent garbage
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }

            break;

        case _EXIT_KEY_MESSAGE:

            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if(g_usBackupValue != GET_OSD_LATENCY())
                {
                    SET_OSD_LATENCY(g_usBackupValue);

                    // Set Backlight OFF to prevent garbage
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
                }
                SET_OSD_STATE(_MENU_DISPLAY_LATENCY);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
            }

            break;

        default:
            break;
    }
#endif
}

void MenuDisplayFreezeAdjust(void)
{
#if(_FREEZE_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAY_FREEZE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:

            if(GET_OSD_FREEZE_STATUS() != _OFF)
            {
                SET_OSD_FREEZE_STATUS(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, _OFF);
                UserCommonAdjustDisplayFreeze(_OFF);
            }

            break;

        case _LEFT_KEY_MESSAGE:

            if(GET_OSD_FREEZE_STATUS() != _ON)
            {
                SET_OSD_FREEZE_STATUS(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, _ON);
                UserCommonAdjustDisplayFreeze(_ON);
            }

            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_FREEZE_STATUS())
            {
                SET_OSD_FREEZE_STATUS(g_usBackupValue);
                UserCommonAdjustDisplayFreeze(GET_OSD_FREEZE_STATUS());
            }

            SET_OSD_STATE(_MENU_DISPLAY_FREEZE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
            break;

        default:
            break;
    }
#endif
}

void MenuColorPanelUniformityAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PANEL_UNIFORMITY())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_PANEL_UNIFORMITY(_OFF);

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
            if(GET_OSD_PANEL_UNIFORMITY() == _ON)
            {
                ScalerTimerWaitForEvent(_EVENT_DVS);
                ScalerTimerDelayXms(2);

                UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
                ScalerColorPanelUniformityEnable(_FUNCTION_ON);
            }
#endif

            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _SELECT, GET_OSD_PANEL_UNIFORMITY());

            break;
        case _LEFT_KEY_MESSAGE:

            if(GET_OSD_PANEL_UNIFORMITY() != _ON)
            {
                SET_OSD_PANEL_UNIFORMITY(_ON);

#if(_UNIFORMITY_SUPPORT == _ON)
                ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
                {
                    ScalerTimerWaitForEvent(_EVENT_DVS);
                    ScalerTimerDelayXms(2);

                    UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
                    ScalerColorPanelUniformityEnable(_FUNCTION_ON);
                }
#endif
            }

            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _SELECT, GET_OSD_PANEL_UNIFORMITY());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PANEL_UNIFORMITY())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_PANEL_UNIFORMITY(g_usAdjustValue);

#if(_UNIFORMITY_SUPPORT == _ON)
                ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
                {
                    ScalerTimerWaitForEvent(_EVENT_DVS);
                    ScalerTimerDelayXms(2);

                    UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
                    ScalerColorPanelUniformityEnable(_FUNCTION_ON);
                }
#endif
            }
            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY());

            break;

        default:
            break;
    }
}


void MenuColorGammaAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_GAMMA())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_GAMMA);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_GAMMA() != _GAMMA_24)
            {
                if(GET_OSD_GAMMA() == _GAMMA_22)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
                }

                OsdDispSliderAndNumber(_MENU_COLOR_GAMMA_ADJUST, GET_OSD_GAMMA());

#if(_GAMMA_FUNCTION == _ON)
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                if(GET_OSD_GAMMA() != _GAMMA_OFF)
                {
                    UserAdjustGamma(GET_OSD_GAMMA());
                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                    UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                }
#endif
            }

            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_GAMMA() != _GAMMA_OFF)
            {
                if(GET_OSD_GAMMA() == _GAMMA_24)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
                }

                OsdDispSliderAndNumber(_MENU_COLOR_GAMMA_ADJUST, GET_OSD_GAMMA());

#if(_GAMMA_FUNCTION == _ON)
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

                if(GET_OSD_GAMMA() != _GAMMA_OFF)
                {
                    UserAdjustGamma(GET_OSD_GAMMA());
                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                    UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                }
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_GAMMA())
            {
                SET_OSD_GAMMA(g_usBackupValue);

#if(_GAMMA_FUNCTION == _ON)
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
                if(GET_OSD_GAMMA() != _GAMMA_OFF)
                {
                    UserAdjustGamma(GET_OSD_GAMMA());
                    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                    UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
                }
#endif
            }

            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_GAMMA);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());
            if(GET_OSD_GAMMA() >= _GAMMA_24)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
            }


            break;

        default:
            break;
    }
}

void MenuColorColorTempAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            if(GET_COLOR_TEMP_TYPE() == _CT_USER)
            {
                g_usBackupValue = GET_COLOR_TEMP_TYPE();
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
                OsdDispClearSelectColor(_UP);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearArrow(_DOWN);
                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_R, GET_COLOR_TEMP_TYPE_USER_R());
            }
            else
            {
                OsdDispClearArrow(_DOWN);
                SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE());
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_COLOR_TEMP_TYPE() != _CT_USER)
            {
                if(GET_COLOR_TEMP_TYPE() == _CT_5800)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
                }
                OsdDispSliderAndNumber(_MENU_COLOR_TEMPERATURE_ADJUST, GET_COLOR_TEMP_TYPE());
                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            }
            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_COLOR_TEMP_TYPE() != _CT_9300)
            {
                if(GET_COLOR_TEMP_TYPE() == _CT_SRGB)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
                }
                OsdDispSliderAndNumber(_MENU_COLOR_TEMPERATURE_ADJUST, GET_COLOR_TEMP_TYPE());
                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_COLOR_TEMP_TYPE())
            {
                SET_COLOR_TEMP_TYPE(g_usBackupValue);

                // Adjust Color
                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            }

            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE());

            if(GET_COLOR_TEMP_TYPE() >= _CT_SRGB)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
            }


            break;

        default:
            break;
    }
}

void MenuColorColorEffectAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_COLOR_EFFECT())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_USER)
            {
                g_usBackupValue = GET_OSD_COLOR_EFFECT();
                OsdDispClearSelectColor(_UP);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
                OsdDispClearArrow(_DOWN);
            }
            else
            {
                OsdDispClearArrow(_DOWN);
                SET_OSD_STATE(_MENU_COLOR_EFFECT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());
                if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
                }
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_COLOR_EFFECT() != _COLOREFFECT_AMOUNT)
            {
                if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_PHOTO)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
                }
                OsdDispSliderAndNumber(_MENU_COLOR_EFFECT_ADJUST, GET_OSD_COLOR_EFFECT());

#if(_HDR10_SUPPORT == _ON)
                if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
                {
                    UserCommonHDRAdjustHDR10ColorEffect();
                }
                else
#endif
                {
#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
                    UserAdjustColorEffectMode();
#endif
                }
            }

            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_COLOR_EFFECT() != _COLOREFFECT_STANDARD)
            {
                if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_VIVID)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
                }

                OsdDispSliderAndNumber(_MENU_COLOR_EFFECT_ADJUST, GET_OSD_COLOR_EFFECT());

#if(_HDR10_SUPPORT == _ON)
                if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
                {
                    UserCommonHDRAdjustHDR10ColorEffect();
                }
                else
#endif
                {
#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
                    UserAdjustColorEffectMode();
#endif
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_COLOR_EFFECT())
            {
                SET_OSD_COLOR_EFFECT(g_usBackupValue);

#if(_HDR10_SUPPORT == _ON)
                if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
                {
                    UserCommonHDRAdjustHDR10ColorEffect();
                }
                else
#endif
                {
#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
                    UserAdjustColorEffectMode();
#endif
                }
            }

            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_EFFECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT());
            if(GET_OSD_COLOR_EFFECT() >= _COLOREFFECT_VIVID)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
            }

            break;

        default:
            break;
    }
}

void MenuColorColorDemoAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HLWIN_TYPE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_DEMO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_HLWIN_TYPE() != _HL_WIN_5)
            {
                if(GET_OSD_HLWIN_TYPE() == _HL_WIN_3)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
                }
                OsdDispSliderAndNumber(_MENU_COLOR_DEMO_ADJUST, GET_OSD_HLWIN_TYPE());

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
                if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
                {
                    ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_POLLING);
                }
                else
                {
                    UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());
                    ScalerColorHLWEnable(_FUNCTION_ON, _DB_APPLY_POLLING);
                }

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
                UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
#endif

#if(_DCC_FUNCTION == _ON)
                ScalerColorDCCNormalizeFactorAdjust();
#endif
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
            {
                if(GET_OSD_HLWIN_TYPE() == _HL_WIN_4)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
                }
                OsdDispSliderAndNumber(_MENU_COLOR_DEMO_ADJUST, GET_OSD_HLWIN_TYPE());

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
                if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
                {
                    ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_POLLING);
                }
                else
                {
                    UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());
                    ScalerColorHLWEnable(_FUNCTION_ON, _DB_APPLY_POLLING);
                }

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
                UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
#endif

#if(_DCC_FUNCTION == _ON)
                ScalerColorDCCNormalizeFactorAdjust();
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HLWIN_TYPE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_HLWIN_TYPE(g_usAdjustValue);
                // Adjust HLWIN
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
                if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
                {
                    UserAdjustHLWinType(_HL_WIN_OFF);
                    ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_POLLING);
                }
                else
                {
                    UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());
                    ScalerColorHLWEnable(_FUNCTION_ON, _DB_APPLY_POLLING);
                }

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
#endif

#if(_DCC_FUNCTION == _ON)
                ScalerColorDCCNormalizeFactorAdjust();
#endif
            }
            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_DEMO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
            if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
            }

            break;

        default:
            break;
    }
}

void MenuColorColorFormatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_COLOR_FORMAT())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_FORMAT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT());
            break;

        case _RIGHT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if(GET_OSD_COLOR_FORMAT() != _COLOR_SPACE_YPBPR)
                {
                    SET_OSD_COLOR_FORMAT(_COLOR_SPACE_YPBPR);
                    OsdFuncColorFormatAdjust();
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _SELECT, GET_OSD_COLOR_FORMAT());
                }
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if(GET_OSD_COLOR_FORMAT() != _COLOR_SPACE_RGB)
                {
                    SET_OSD_COLOR_FORMAT(_COLOR_SPACE_RGB);
                    OsdFuncColorFormatAdjust();
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _SELECT, GET_OSD_COLOR_FORMAT());
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if(g_usBackupValue != GET_OSD_COLOR_FORMAT())
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_OSD_COLOR_FORMAT(g_usAdjustValue);
                    OsdFuncColorFormatAdjust();
                }
                SET_OSD_STATE(_MENU_COLOR_FORMAT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT());
            }

            break;

        default:
            break;
    }
}

void MenuColorColorPCMAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
            if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
            {
                g_usBackupValue = GET_OSD_PCM_STATUS();
                OsdDispClearArrow(_UP);
                OsdDispClearArrow(_DOWN);
                SET_OSD_STATE(_MENU_COLOR_PCM_SOFT_PROFT_ADJUST);
                // SET_OSD_PCM_SOFT_PROFT_MODE(_PCM_SOFT_MODE_1);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_PCM_1);

                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_SOFT_PROFT_TYPE, _SELECT, GET_OSD_PCM_SOFT_PROFT_MODE());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PCM_SOFT_PROFT);
            }
            else
#endif
            {
                if(g_usBackupValue != GET_OSD_PCM_STATUS())
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                }

                SET_OSD_STATE(_MENU_COLOR_PCM);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
            }
            break;

        case _RIGHT_KEY_MESSAGE:

#if(_OCC_SUPPORT == _ON)
#if(_RGB_3D_GAMMA == _ON)
            if(GET_OSD_PCM_STATUS() != _PCM_OSD_SOFT_PROFT)
#else
            if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
#endif
            {
                OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS());

#if(_RGB_3D_GAMMA == _ON)
                if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
                }
                else
                {
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
                }
#else
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
#endif
                OsdFuncColorPcmAdjust();
            }
#else    // #if(_OCC_SUPPORT == _ON)
            if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
            {
                OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS());
            }
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
            OsdFuncColorPcmAdjust();
#endif

            break;

        case _LEFT_KEY_MESSAGE:

#if(_OCC_SUPPORT == _ON)
            if(GET_OSD_PCM_STATUS() != _PCM_OSD_SRGB)
            {
                OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS());

                if(GET_OSD_PCM_STATUS() == _PCM_OSD_NATIVE)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }
                else
                {
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
                }
                OsdFuncColorPcmAdjust();
            }
#else   //#if(_OCC_SUPPORT == _ON)
            if(GET_OSD_PCM_STATUS() != _PCM_OSD_USER)
            {
                OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS());
                if(GET_OSD_PCM_STATUS() == _PCM_OSD_NATIVE)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }
                else
                {
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
                }
                OsdFuncColorPcmAdjust();
            }
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PCM_STATUS())
            {
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                if(g_usBackupValue == _PCM_OSD_SOFT_PROFT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                }
#endif

                SET_OSD_PCM_STATUS(g_usBackupValue);

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
                {
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
                }
                else if((g_usAdjustValue == _PCM_OSD_SOFT_PROFT) && (GET_OSD_PCM_STATUS() != _PCM_OSD_SOFT_PROFT))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }
                else
                {
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }
#else
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
#endif
                OsdFuncColorPcmAdjust();
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
            }

            SET_OSD_STATE(_MENU_COLOR_PCM);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            break;

        default:
            break;
    }
}

void MenuColorColorHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_HUE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_HUE_ADJUST, GET_OSD_HUE());
#if(_GLOBAL_HUE_SATURATION == _ON)
            UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HUE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_HUE(g_usAdjustValue);
#if(_GLOBAL_HUE_SATURATION == _ON)
                UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_HUE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_HUE(), _HUE_MAX, _HUE_MIN, _HUE_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);


            break;

        default:
            break;
    }
}

void MenuColorColorSaturationAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_SATURATION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_SATURATION_ADJUST, GET_OSD_SATURATION());
#if(_GLOBAL_HUE_SATURATION == _ON)
            UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SATURATION())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_SATURATION(g_usAdjustValue);
#if(_GLOBAL_HUE_SATURATION == _ON)
                UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_SATURATION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SATURATION(), _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        default:
            break;
    }
}

void MenuAdvanceAspectAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ASPECT_RATIO_TYPE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDispClearArrow(_DOWN);
            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if((GET_OSD_ASPECT_RATIO_TYPE()%4) == 3)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_1);
                }
                OsdDispSliderAndNumber(_MENU_ADVANCE_ASPECT_ADJUST, GET_OSD_ASPECT_RATIO_TYPE());

                if(g_usAdjustValue != GET_OSD_ASPECT_RATIO_TYPE())
                {
                    SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
                    OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _SELECT, GET_OSD_ASPECT_RATIO_TYPE());
#if(_ASPECT_RATIO_SUPPORT == _ON)
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
#else
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
#endif
                }
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if(((GET_OSD_ASPECT_RATIO_TYPE()%4) == 0)&&(GET_OSD_ASPECT_RATIO_TYPE() != 0))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_0);
                }
                OsdDispSliderAndNumber(_MENU_ADVANCE_ASPECT_ADJUST, GET_OSD_ASPECT_RATIO_TYPE());

                if(g_usAdjustValue != GET_OSD_ASPECT_RATIO_TYPE())
                {
                    SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
                    OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _SELECT, GET_OSD_ASPECT_RATIO_TYPE());
#if(_ASPECT_RATIO_SUPPORT == _ON)
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
#else
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
#endif
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if(g_usBackupValue != GET_OSD_ASPECT_RATIO_TYPE())
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_OSD_ASPECT_RATIO_TYPE(g_usAdjustValue);
                    // Adjust HLW
#if(_ASPECT_RATIO_SUPPORT == _ON)
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
#else
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
#endif
                }

                OsdDispClearArrow(_DOWN);
                OsdDispAdvanceMenuReDraw(_LOW);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceOverScanAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_OVERSCAN_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_OVER_SCAN_ADJUST, GET_OSD_OVERSCAN_STATUS());

#if(_OVERSCAN_SUPPORT == _ON)
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
            {
                if(g_usBackupValue != GET_OSD_OVERSCAN_STATUS())
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_OSD_OVERSCAN_STATUS(g_usAdjustValue);
#if(_OVERSCAN_SUPPORT == _ON)
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
                }

                OsdDispAdvanceMenuReDraw(_LOW);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceOverDriveOnOff(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_OD_STATUS();
            SET_OSD_STATE(_MENU_ADVANCE_OD_ONOFF_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_OD_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_GAIN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_OD_GAIN(), _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}


void MenuAdvanceOverDriveGain(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_OD_GAIN();
            SET_OSD_STATE(_MENU_ADVANCE_OD_GAIN_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}

void MenuAdvanceDCRAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DCR_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_DCR_STATUS() != _OFF)
            {
                SET_OSD_DCR_STATUS(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _SELECT, GET_OSD_DCR_STATUS());
            }

            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_DCR_STATUS() != _ON)
            {
                SET_OSD_DCR_STATUS(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _SELECT, GET_OSD_DCR_STATUS());
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DCR_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_DCR_STATUS(g_usAdjustValue);
            }

            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        default:
            break;
    }
}

void MenuAdvanceDdcciAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DDCCI_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_DDCCI_STATUS() != _OFF)
            {
                SET_OSD_DDCCI_STATUS(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _SELECT, GET_OSD_DDCCI_STATUS());
                UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_DDCCI_STATUS() != _ON)
            {
                SET_OSD_DDCCI_STATUS(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _SELECT, GET_OSD_DDCCI_STATUS());
                UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DDCCI_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_DDCCI_STATUS(g_usAdjustValue);
                UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
            }

            OsdDispAdvanceMenuReDraw(_LOW);


            break;

        default:
            break;
    }
}

void MenuAdvanceUltraVividAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ULTRA_VIVID_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(((GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_H) && (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) ||
               ((GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_OFF) && (GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)))
            {
            }
            else
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_ULTRA_VIVID_ADJUST, GET_OSD_ULTRA_VIVID_STATUS());
#if(_ULTRA_VIVID_SUPPORT == _ON)
                UserInterfaceAdjustUltraVividProc(_DB_APPLY_POLLING);
#endif // End of #if(_ULTRA_VIVID_SUPPORT == _ON)
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ULTRA_VIVID_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_ULTRA_VIVID_STATUS(g_usAdjustValue);

#if(_ULTRA_VIVID_SUPPORT == _ON)
                UserInterfaceAdjustUltraVividProc(_DB_APPLY_POLLING);
#endif // End of #if(_ULTRA_VIVID_SUPPORT == _ON)
            }

            OsdDispAdvanceMenuReDraw(_LOW);


            break;

        default:
            break;
    }
}

void MenuAdvanceDpOptionD0(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            g_usBackupValue = GET_OSD_DP_D0_VERSION();
            SET_OSD_STATE(_MENU_ADVANCE_DP_D0_VERSION_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D1_1_DOT_X);
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D2_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D2_1_DOT_X);
#elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D6_1_DOT_X);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D0_1_DOT_X);
#endif
            break;

        case _LEFT_KEY_MESSAGE:

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}

void MenuAdvanceDpOptionD1(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            g_usBackupValue = GET_OSD_DP_D1_VERSION();
            SET_OSD_STATE(_MENU_ADVANCE_DP_D1_VERSION_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D2_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D2_1_DOT_X);
#elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D6_1_DOT_X);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D1_1_DOT_X);
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D0_1_DOT_X);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D1_1_DOT_X);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}

void MenuAdvanceDpOptionD2(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            g_usBackupValue = GET_OSD_DP_D2_VERSION();
            SET_OSD_STATE(_MENU_ADVANCE_DP_D2_VERSION_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D2_VERSION());
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D6_1_DOT_X);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D2_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D2_1_DOT_X);
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D1_1_DOT_X);
#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D0_1_DOT_X);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D2_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D2_1_DOT_X);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}

void MenuAdvanceDpOptionD6(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            g_usBackupValue = GET_OSD_DP_D6_VERSION();
            SET_OSD_STATE(_MENU_ADVANCE_DP_D6_VERSION_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
#endif

            break;

        case _RIGHT_KEY_MESSAGE:

            break;

        case _LEFT_KEY_MESSAGE:
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D2_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D2_1_DOT_X);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D1_1_DOT_X);
#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D0_1_DOT_X);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_D6_1_DOT_X);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}

void MenuAdvanceDPMstAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_MST())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_MST_SUPPORT == _ON)
                UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());

                if(GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP)
                {
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
#endif
            }
            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_DP_MST() < _MST_AMOUNT)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_DP_MST_ADJUST, GET_OSD_DP_MST());
                if(GET_OSD_DP_MST() > 3)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_MST_1);
                }
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_DP_MST() > _MST_OFF)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_DP_MST_ADJUST, GET_OSD_DP_MST());
                if(GET_OSD_DP_MST() == 3)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_MST);
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_MST())
            {
                // g_usAdjustValue = g_usBackupValue;
                SET_OSD_DP_MST(g_usBackupValue);
            }
            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        default:
            break;
    }
}

void MenuAdvanceDPEdidAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != UserCommonNVRamGetSystemData(_DP_EDID_SELECT))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                UserCommonInterfaceDPSwitchEdid(_D0_INPUT_PORT);
                UserCommonInterfaceDPSwitchEdid(_D1_INPUT_PORT);
                UserCommonInterfaceDPSwitchEdid(_D2_INPUT_PORT);
                UserCommonInterfaceDPSwitchEdid(_D6_INPUT_PORT);
#endif
            }

            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
            if(UserCommonNVRamGetSystemData(_DP_EDID_SELECT) != _DP_EDID_4K2K_60HZ)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_DP_EDID_ADJUST, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(UserCommonNVRamGetSystemData(_DP_EDID_SELECT) != _DP_EDID_1080P)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_DP_EDID_ADJUST, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != UserCommonNVRamGetSystemData(_DP_EDID_SELECT))
            {
                UserCommonNVRamSetSystemData(_DP_EDID_SELECT, g_usBackupValue);
            }
            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        default:
            break;
    }
}

void MenuAdvanceCloneAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CLONE_MODE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
                UserCommonInterfaceCloneModeSwitch(GET_OSD_CLONE_MODE());
#endif
            }
            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_CLONE_ADJUST, GET_OSD_CLONE_MODE());

            OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE());
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_CLONE_ADJUST, GET_OSD_CLONE_MODE());
            OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE());
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        default:
            break;
    }
}

void MenuAdvanceFreeSyncAdjust(void)
{
#if((_FREESYNC_SUPPORT == _ON)||(_FREESYNC_II_SUPPORT == _ON))
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_FREE_SYNC_STATUS())
            {
                SET_OSD_FREE_SYNC_STATUS(g_usBackupValue);

#if(_FREESYNC_SUPPORT == _ON)
                UserCommonInterfaceFreeSyncSupportSwitch();
#endif

#if((_HDMI_MULTI_EDID_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
                // Switch Edid for All HDMI Port
                UserCommonInterfaceHDMISwitchAllPortEdid();
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                // Switch All DP Port Edid
                UserCommonInterfaceDPSwitchAllPortEdid();
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
                UserCommonHDRAdjust(_HDR_FLOW_OSD_MODE_CHANGE);
#endif
            }
            SET_OSD_STATE(_MENU_ADVANCE_FREESYNC_ADJUST);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            OsdDispAdvanceMenuReDraw(_LOW);
            break;

        case _RIGHT_KEY_MESSAGE:

            if(g_usBackupValue != _OFF)
            {
                g_usBackupValue = _OFF;
                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, g_usBackupValue);
            }

            break;

        case _LEFT_KEY_MESSAGE:

            if(g_usBackupValue != _ON)
            {
                g_usBackupValue = _ON;
                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, g_usBackupValue);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_FREE_SYNC_STATUS())
            {
                SET_OSD_FREE_SYNC_STATUS(g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_FREESYNC_ADJUST);
            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        default:
            break;
    }
#endif
}

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
void MenuAdvanceTypeCModeD0(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            g_usBackupValue = GET_OSD_D0_TYPE_C_U3_MODE();
            SET_OSD_STATE(_MENU_ADVANCE_D0_TYPE_C_MODE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _SELECT, g_usBackupValue);
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D1_TYPE_C_U3_MODE());
#elif(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D6_TYPE_C_U3_MODE());
#endif
            break;

        case _LEFT_KEY_MESSAGE:

            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}

void MenuAdvanceTypeCModeD1(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            g_usBackupValue = GET_OSD_D1_TYPE_C_U3_MODE();

            SET_OSD_STATE(_MENU_ADVANCE_D1_TYPE_C_MODE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _SELECT, g_usBackupValue);
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D6_TYPE_C_U3_MODE());
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D0_TYPE_C_U3_MODE());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}

void MenuAdvanceTypeCModeD2(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            break;

        case _RIGHT_KEY_MESSAGE:
#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D6_TYPE_C_U3_MODE());
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D1_TYPE_C_U3_MODE());
#elif(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D0_TYPE_C_U3_MODE());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}

void MenuAdvanceTypeCModeD6(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            g_usBackupValue = GET_OSD_D6_TYPE_C_U3_MODE();
            SET_OSD_STATE(_MENU_ADVANCE_D6_TYPE_C_MODE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _SELECT, g_usBackupValue);
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D1_TYPE_C_U3_MODE());
#elif(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D0_TYPE_C_U3_MODE());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}
#endif

#if(_HDR10_SUPPORT == _ON)
void MenuAdvanceHdrMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_HDR_MODE();

            SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _SELECT, GET_OSD_HDR_MODE());
            break;

        case _RIGHT_KEY_MESSAGE:

            if(UserCommonHDRGetHDR10Status() == _HDR10_OFF)
                return;

            SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_DARK_ENHANCE_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}

void MenuAdvanceHdrDarkEnhanceOnOff(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_DARK_ENHANCE_STATUS();
            SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_DARK_ENHANCE_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR_SHARPNESS_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_HDR_SHARPNESS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_HDR_MODE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_MODE);
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}
void MenuAdvanceHdrSharpnessOnOff(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_HDR_SHARPNESS();
            SET_OSD_STATE(_MENU_ADVANCE_HDR_SHARPNESS_ONOFF_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_HDR_SHARPNESS());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_CONTRAST, GET_OSD_HDR_CONTRAST());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_DARK_ENHANCE_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}
void MenuAdvanceHdrContrast(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_HDR_CONTRAST();
            SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_OSD_HDR_CONTRAST(), _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
#if((_HDR10_COLOR_ENHANCE_SUPPORT == _ON)||(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON))
#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_HDR_COLOR_ENHANCE);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST_1);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_COLOR_ENHANCE, GET_OSD_HDR_COLOR_ENHANCE());
#elif(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_HDR_LIGHT_ENHANCE);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST_1);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_LIGHT_ENHANCE, GET_OSD_HDR_LIGHT_ENHANCE());
#endif
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR_SHARPNESS_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_HDR_SHARPNESS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}
void MenuAdvanceHdrColorEnhance(void)
{
#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_HDR_COLOR_ENHANCE();

            SET_OSD_STATE(_MENU_ADVANCE_HDR_COLOR_ENHANCE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_COLOR_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _SELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_HDR_LIGHT_ENHANCE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_LIGHT_ENHANCE, GET_OSD_HDR_LIGHT_ENHANCE());
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_CONTRAST, GET_OSD_HDR_CONTRAST());
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
#endif
}
void MenuAdvanceHdrLightEnhance(void)
{
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_HDR_LIGHT_ENHANCE();

            SET_OSD_STATE(_MENU_ADVANCE_HDR_LIGHT_ENHANCE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_LIGHT_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_HDR_COLOR_ENHANCE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_COLOR_ENHANCE, GET_OSD_HDR_COLOR_ENHANCE());
#else
            SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_CONTRAST, GET_OSD_HDR_CONTRAST());
#endif
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
#endif
}



#endif

void MenuAdvanceEdidAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_DP:
                    SET_OSD_STATE(_MENU_ADVANCE_EDID_DX_ADJUST);
                    OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_PRE_SELECT);
                    g_usBackupValue = UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue);
                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                default:
                    break;
            }

            break;

        case _RIGHT_KEY_MESSAGE:
            if(g_usAdjustValue == 3)
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_1);
            }

            if(g_usAdjustValue < 5) // D0-D6
            {
                g_usAdjustValue++;
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
                {
                    case _PORT_DP:
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_RESOLUTION);
                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
                        break;

                    case _PORT_HDMI20:
                    case _PORT_HDMI:
                    case _PORT_MHL:
                    default:
                        break;
                }
            }

            break;

        case _LEFT_KEY_MESSAGE:
            if(g_usAdjustValue == 4)
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_0);
            }
            if(g_usAdjustValue > 0) // D0-D6
            {
                g_usAdjustValue--;
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
                {
                    case _PORT_DP:
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_RESOLUTION);
                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
                        break;

                    case _PORT_HDMI20:
                    case _PORT_HDMI:
                    case _PORT_MHL:
                    default:
                        break;
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}

void MenuAdvanceEdidDXAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_EDID_ADJUST);
            OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_SELECT);
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_DP:
                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, g_usBackupValue);
                    if(g_usBackupValue != UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue))
                    {
                        UserCommonNVRamSetSystemData(_EDID_D0_SELECT + g_usAdjustValue, g_usBackupValue);
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                        UserCommonInterfaceDPSwitchEdid(_D0_INPUT_PORT + g_usAdjustValue);
#endif
                    }
                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                default:
                    break;
            }

            break;

        case _RIGHT_KEY_MESSAGE:
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_DP:
                    if(g_usBackupValue < _DP_EDID_4K2K_60HZ)
                    {
                        g_usBackupValue++;
                    }

                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, g_usBackupValue);
                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                default:
                    break;
            }


            break;

        case _LEFT_KEY_MESSAGE:
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_DP:
                    if(g_usBackupValue > _DP_EDID_1080P)
                    {
                        g_usBackupValue--;
                    }

                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, g_usBackupValue);
                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                default:
                    break;
            }

            break;

        case _EXIT_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_EDID_ADJUST);
            OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_SELECT);
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_DP:
                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                default:
                    break;
            }
            break;

        default:
            break;
    }
}
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
void MenuAdvanceHDMIVersionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:

#if(_D0_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 0)
                    {
                        break;
                    }
#endif
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 1)
                    {
                        break;
                    }
#endif
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 2)
                    {
                        break;
                    }
#endif
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 3)
                    {
                        break;
                    }
#endif
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 4)
                    {
                        break;
                    }
#endif
#if(_D5_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 5)
                    {
                        break;
                    }
#endif

                    SET_OSD_STATE(_MENU_ADVANCE_DX_HDMI_VERSION_ADJUST);
                    OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_PRE_SELECT);
                    g_usBackupValue = OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue);// UserCommonNVRamGetSystemData(_EDID_D0_SELECT + );
                    OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _SELECT, g_usBackupValue);
                    break;

                default:
                    break;
            }

            break;

        case _RIGHT_KEY_MESSAGE:
            if(g_usAdjustValue == 3)
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_1);
            }

            if(g_usAdjustValue < 5) // D0-D5
            {
                g_usAdjustValue++;
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
                {
                    case _PORT_HDMI20:
                    case _PORT_HDMI:
                    case _PORT_MHL:
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 0)
                        {
                            break;
                        }
#endif
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 1)
                        {
                            break;
                        }
#endif
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 2)
                        {
                            break;
                        }
#endif
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 3)
                        {
                            break;
                        }
#endif
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 4)
                        {
                            break;
                        }
#endif
#if(_D5_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 5)
                        {
                            break;
                        }
#endif
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDMI_VERSIONS );
                        OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _UNSELECT, OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue));
                        break;
                    default:
                        break;
                }
            }

            break;

        case _LEFT_KEY_MESSAGE:
            if(g_usAdjustValue == 4)
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_0);
            }
            if(g_usAdjustValue > 0) // D0-D6
            {
                g_usAdjustValue--;
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
                {
                    case _PORT_HDMI20:
                    case _PORT_HDMI:
                    case _PORT_MHL:
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 0)
                        {
                            break;
                        }
#endif
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 1)
                        {
                            break;
                        }
#endif
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 2)
                        {
                            break;
                        }
#endif
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 3)
                        {
                            break;
                        }
#endif
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 4)
                        {
                            break;
                        }
#endif
#if(_D5_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 5)
                        {
                            break;
                        }
#endif
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDMI_VERSIONS );
                        OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _UNSELECT, OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue));
                        break;
                    default:
                        break;
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispAdvanceMenuReDraw(_HIGH);
            break;

        default:
            break;
    }
}

void MenuAdvanceDxHDMIVersionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDMI_VERSION_ADJUST);
            OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_SELECT);
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                    OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _UNSELECT, g_usBackupValue);
                    if(g_usBackupValue != OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue))
                    {
                        //UserCommonNVRamSetSystemData(_EDID_D0_SELECT + g_usAdjustValue, g_usBackupValue);
                        OsdFuncSetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue, g_usBackupValue);
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                        // Add EDID DDCRAM Switch & HPD event
                        UserCommonInterfaceHDMISwitchEdid(_D0_INPUT_PORT + g_usAdjustValue, UserInterfaceGetMultiHdmiEdidIndex(_D0_INPUT_PORT + g_usAdjustValue));
                    }
                    break;
                default:
                    break;
            }

            break;

        case _RIGHT_KEY_MESSAGE:
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                    if(g_usBackupValue < _EDID_INDEX_2)
                    {
                        g_usBackupValue++;
                    }
                    OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _SELECT, g_usBackupValue);
                    break;
                default:
                    break;
            }


            break;

        case _LEFT_KEY_MESSAGE:
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                    if(g_usBackupValue > _EDID_INDEX_0)
                    {
                        g_usBackupValue--;
                    }
                    OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _SELECT, g_usBackupValue);
                    break;
                default:
                    break;
            }

            break;

        case _EXIT_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_HDMI_VERSION_ADJUST);
            OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_SELECT);
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                    OsdDispMainMenuOptionSetting(_OPTION_HDMI_VERSIONS_TYPE, _UNSELECT, OsdFuncGetHdmiPortVersion(_D0_INPUT_PORT + g_usAdjustValue));
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}
#endif
#if(_PIXEL_SHIFT_SUPPORT == _ON)
void MenuAdvancePixelShifAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDispAdvanceMenuReDraw(_LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _ON);
            UserAdjustPixelShifting();
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _OFF);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispAdvanceMenuReDraw(_LOW);
            break;

        default:
            break;
    }
}

#endif
#if (_SDR_TO_HDR_SUPPORT == _ON)
void MenuAdvanceSdrToHdrAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SDR_TO_HDR())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_SDR_TO_HDR() != _OFF)
            {
                SET_OSD_SDR_TO_HDR(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_SDR_TO_HDR());
                UserAdjustSDRToHDR(_OFF);
            }

            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_SDR_TO_HDR() != _ON)
            {
                SET_OSD_SDR_TO_HDR(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_SDR_TO_HDR());
                UserAdjustSDRToHDR(_ON);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SDR_TO_HDR())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_SDR_TO_HDR(g_usAdjustValue);
            }

            OsdDispAdvanceMenuReDraw(_LOW);

            break;

        default:
            break;
    }
}
#endif

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
void MenuAdvanceMBRMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_MBR_STATUS();
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            SET_OSD_STATE(_MENU_ADVANCE_MBR_MODE_ADJUST);
            OsdDispMainMenuOptionSetting(_OPTION_MBR_MODE, _SELECT, GET_OSD_MBR_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_MBR_DUTY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_MBR_DUTY(), 100, 0, 50);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}


void MenuAdvanceMBRDuty(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_MBR_DUTY();
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            SET_OSD_STATE(_MENU_ADVANCE_MBR_DUTY_ADJUST);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_MBR_POSITION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_MBR_POSITION(), 100, 0, 50);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_MBR_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuOptionSetting(_OPTION_MBR_MODE, _UNSELECT, GET_OSD_MBR_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_MBR_MODE);
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}
void MenuAdvanceMBRPosition(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_MBR_POSITION();
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            SET_OSD_STATE(_MENU_ADVANCE_MBR_POSITION_ADJUST);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_MBR_DUTY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_MBR_DUTY(), 100, 0, 50);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispAdvanceMenuReDraw(_HIGH);
            break;

        default:
            break;
    }
}
void MenuAdvanceMBRModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_MBR_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_MBR_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MBR_MODE, _UNSELECT, GET_OSD_MBR_STATUS());

            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_MBR_STATUS() == _OSD_MBR_USER_DISABLE)
            {
                SET_OSD_MBR_STATUS(_OSD_MBR_USER_ENABLE);
                OsdDispMainMenuOptionSetting(_OPTION_MBR_MODE, _SELECT, GET_OSD_MBR_STATUS());
                //switch
            }
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) ||(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
            else if(GET_OSD_MBR_STATUS() == _OSD_MBR_USER_ENABLE)
            {
                SET_OSD_MBR_STATUS(_OSD_RTK_ADV_MBR_USER_ENABLE);
                OsdDispMainMenuOptionSetting(_OPTION_MBR_MODE, _SELECT, GET_OSD_MBR_STATUS());
                //switch
            }
#endif
            else
            {
                SET_OSD_MBR_STATUS(_OSD_MBR_USER_DISABLE);
                OsdDispMainMenuOptionSetting(_OPTION_MBR_MODE, _SELECT, GET_OSD_MBR_STATUS());
                //switch

            }
            // Reset to display setting to re-set backlight parameters
            // Caustion!! RTK_Adv_MBR requires "reset to display setting to be effective
#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _ON)
            UserCommonInterfaceMbrStrobeBacklightCtrl(_LIGHT_CONTROL_ON);
#else
            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_MBR_STATUS() == _OSD_MBR_USER_ENABLE)
            {
                SET_OSD_MBR_STATUS(_OSD_MBR_USER_DISABLE);
                OsdDispMainMenuOptionSetting(_OPTION_MBR_MODE, _SELECT, GET_OSD_MBR_STATUS());
                //switch
            }
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
            else if(GET_OSD_MBR_STATUS() == _OSD_MBR_USER_DISABLE)
            {
                SET_OSD_MBR_STATUS(_OSD_RTK_ADV_MBR_USER_ENABLE);
                OsdDispMainMenuOptionSetting(_OPTION_MBR_MODE, _SELECT, GET_OSD_MBR_STATUS());
                //switch
            }
#endif
            else
            {
                SET_OSD_MBR_STATUS(_OSD_MBR_USER_ENABLE);
                OsdDispMainMenuOptionSetting(_OPTION_MBR_MODE, _SELECT, GET_OSD_MBR_STATUS());
                //switch

            }

            // Reset to display setting to re-set backlight parameters
            // Caustion!! RTK_Adv_MBR requires "reset to display setting to be effective
#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _ON)
            UserCommonInterfaceMbrStrobeBacklightCtrl(_LIGHT_CONTROL_ON);
#else
            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_MBR_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_MBR_STATUS(g_usAdjustValue);
                //switch

                // Reset to display setting to re-set backlight parameters
                // Caustion!! RTK_Adv_MBR requires "reset to display setting to be effective
#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _ON)
                UserCommonInterfaceMbrStrobeBacklightCtrl(_LIGHT_CONTROL_ON);
#else
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
            }
            SET_OSD_STATE(_MENU_ADVANCE_MBR_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MBR_MODE, _UNSELECT, GET_OSD_MBR_STATUS());

            break;

        default:
            break;
    }
}
void MenuAdvanceMBRDutyAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_MBR_DUTY())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_MBR_DUTY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_MBR_DUTY(), _OSD_MBR_DUTY_MAX, _OSD_MBR_DUTY_MIN, _OSD_MBR_DUTY_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_MBR_DUTY_ADJUST, GET_OSD_MBR_DUTY());
            //insert Function call
            if(GET_OSD_MBR_STATUS() == _OSD_MBR_USER_ENABLE)
            {
                UserInterfaceMbrBacklightAdjust(_BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR, _LIGHT_CONTROL_ON, GET_MBR_DVTOTAL());
            }
            else if(GET_OSD_MBR_STATUS() == _OSD_RTK_ADV_MBR_USER_ENABLE)
            {
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
                UserCommonInterfaceMbrAdvAdjust(GET_OSD_MBR_DUTY(), GET_OSD_MBR_POSITION(), _LIGHT_CONTROL_ON);
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_MBR_DUTY())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_MBR_DUTY(g_usAdjustValue);
                //insert Function call
                if(GET_OSD_MBR_STATUS() == _OSD_MBR_USER_ENABLE)
                {
                    UserInterfaceMbrBacklightAdjust(_BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR, _LIGHT_CONTROL_ON, GET_MBR_DVTOTAL());
                }
                else if(GET_OSD_MBR_STATUS() == _OSD_RTK_ADV_MBR_USER_ENABLE)
                {
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
                    UserCommonInterfaceMbrAdvAdjust(GET_OSD_MBR_DUTY(), GET_OSD_MBR_POSITION(), _LIGHT_CONTROL_ON);
#endif
                }
            }
            SET_OSD_STATE(_MENU_ADVANCE_MBR_DUTY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_MBR_DUTY(), _OSD_MBR_DUTY_MAX, _OSD_MBR_DUTY_MIN, _OSD_MBR_DUTY_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        default:
            break;
    }
}
void MenuAdvanceMBRPositionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_MBR_POSITION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_MBR_POSITION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_MBR_POSITION(), _OSD_MBR_POS_MAX, _OSD_MBR_POS_MIN, _OSD_MBR_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_MBR_POSITION_ADJUST, GET_OSD_MBR_POSITION());
            //insert Function call
            if(GET_OSD_MBR_STATUS() == _OSD_MBR_USER_ENABLE)
            {
                UserInterfaceMbrBacklightAdjust(_BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR, _LIGHT_CONTROL_ON, GET_MBR_DVTOTAL());
            }
            else if(GET_OSD_MBR_STATUS() == _OSD_RTK_ADV_MBR_USER_ENABLE)
            {
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
                UserCommonInterfaceMbrAdvAdjust(GET_OSD_MBR_DUTY(), GET_OSD_MBR_POSITION(), _LIGHT_CONTROL_ON);
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_MBR_POSITION())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_MBR_POSITION(g_usAdjustValue);
                //insert Function call
                if(GET_OSD_MBR_STATUS() == _OSD_MBR_USER_ENABLE)
                {
                    UserInterfaceMbrBacklightAdjust(_BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR, _LIGHT_CONTROL_ON, GET_MBR_DVTOTAL());
                }
                else if(GET_OSD_MBR_STATUS() == _OSD_RTK_ADV_MBR_USER_ENABLE)
                {
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
                    UserCommonInterfaceMbrAdvAdjust(GET_OSD_MBR_DUTY(), GET_OSD_MBR_POSITION(), _LIGHT_CONTROL_ON);
#endif
                }
            }
            SET_OSD_STATE(_MENU_ADVANCE_MBR_POSITION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_MBR_POSITION(), _OSD_MBR_POS_MAX, _OSD_MBR_POS_MIN, _OSD_MBR_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        default:
            break;
    }
}

#endif
void MenuAudioVolumeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_AUDIO_VOLUME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME_ADJUST, GET_OSD_VOLUME());

            if((GET_OSD_VOLUME_MUTE() == _ON) && (g_usBackupValue == GET_OSD_VOLUME()))
            {
                // RTDOsdDispOsdFunctionAdjust(_MENU_AUDIO_MUTE_ON_OFF);
                SET_OSD_VOLUME_MUTE(_OFF);
            }
#if(_AUDIO_SUPPORT == _ON)
            UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_VOLUME(g_usAdjustValue);
#if(_AUDIO_SUPPORT == _ON)
                UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
            }
            SET_OSD_STATE(_MENU_AUDIO_VOLUME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_OSD_VOLUME(), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        default:
            break;
    }
}

void MenuAudioMuteOnOff(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME_MUTE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_AUDIO_MUTE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_MUTE_ON_OFF, GET_OSD_VOLUME_MUTE());
#if(_AUDIO_SUPPORT == _ON)
            UserAdjustAudioMuteSwitch();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME_MUTE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_VOLUME_MUTE(g_usAdjustValue);
#if(_AUDIO_SUPPORT == _ON)
                UserAdjustAudioMuteSwitch();
#endif
            }
            SET_OSD_STATE(_MENU_AUDIO_MUTE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());
            break;

        default:
            break;
    }
}

void MenuAudioStandAlongSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_STAND_ALONE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_AUDIO_STAND_ALONE() == _ON)
            {
                SET_OSD_AUDIO_STAND_ALONE(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _SELECT, GET_OSD_AUDIO_STAND_ALONE());
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_AUDIO_STAND_ALONE() == _OFF)
            {
                SET_OSD_AUDIO_STAND_ALONE(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _SELECT, GET_OSD_AUDIO_STAND_ALONE());
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_STAND_ALONE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_AUDIO_STAND_ALONE(g_usAdjustValue);
            }
            SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
            break;

        default:
            break;
    }
}

void MenuAudioAudioSourceSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_SOURCE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_AUDIO_SOURCE_SELECT, GET_OSD_AUDIO_SOURCE());

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_SOURCE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_AUDIO_SOURCE(g_usAdjustValue);
            }
            SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
            break;

        default:
            break;
    }
}

void MenuAudioSoundModeSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
void MenuAudioAudioSelfTestSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
        case _EXIT_KEY_MESSAGE:
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
            if(ScalerAudioGetInternalAudioGenEnable(SysSourceGetInputPort()) == _ENABLE)
                SysAudioInternalGenTestProc(_OFF);
#endif
            SET_OSD_STATE(_MENU_AUDIO_AUDIO_SELF_TEST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, _OFF);
            break;

        case _RIGHT_KEY_MESSAGE:
            if(g_usBackupValue == _ON)
            {
                g_usBackupValue = _OFF;
                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _OFF);
                SysAudioInternalGenTestProc(_OFF);
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(g_usBackupValue == _OFF)
            {
                g_usBackupValue = _ON;
                OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, _ON);

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
                SysAudioInternalGenTestProc(_ON);
                SysAudioMuteProc(_OFF);
#endif
            }
            break;

        default:
            break;
    }
}
#endif
void MenuOtherMenuTimeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_TIME_OUT())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME, GET_OSD_TIME_OUT());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME_ADJUST, GET_OSD_TIME_OUT());
            ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_TIME_OUT())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_TIME_OUT(g_usAdjustValue);
                ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        default:
            break;
    }
}

void MenuOtherOsdHPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HPOS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS, GET_OSD_HPOS());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS_ADJUST, GET_OSD_HPOS());
            OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HPOS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_HPOS(g_usAdjustValue);
                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
            }
            SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuOtherOsdVPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VPOS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS, GET_OSD_VPOS());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS_ADJUST, GET_OSD_VPOS());
            OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VPOS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_VPOS(g_usAdjustValue);
                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
            }
            SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuOtherLanguageAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LANGUAGE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _UNSELECT, GET_OSD_LANGUAGE());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_LANGUAGE_ADJUST, g_usAdjustValue);
            if(g_usAdjustValue != GET_OSD_LANGUAGE())
            {
                SET_OSD_LANGUAGE(g_usAdjustValue);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_1);
                OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _SELECT, GET_OSD_LANGUAGE());
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LANGUAGE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_LANGUAGE(g_usAdjustValue);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_1);
            }

            SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_LANGUAGE_ADJUST, _UNSELECT, GET_OSD_LANGUAGE());
            break;

        default:
            break;
    }
}

void MenuOtherTransparencyAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_TRANSPARENCY_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY, GET_OSD_TRANSPARENCY_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY_ADJUST, GET_OSD_TRANSPARENCY_STATUS());
            OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_TRANSPARENCY_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_TRANSPARENCY_STATUS(g_usAdjustValue);
                OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
            }
            SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TRANSPARENCY_STATUS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuOtherRotateAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ROTATE_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _UNSELECT, GET_OSD_ROTATE_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_ROTATE_ADJUST, GET_OSD_ROTATE_STATUS());
            if(g_usAdjustValue != GET_OSD_ROTATE_STATUS())
            {
                SET_OSD_ROTATE_STATUS(g_usAdjustValue);
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
                OsdDispOsdRotateSwitch();
#endif
                OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _SELECT, GET_OSD_ROTATE_STATUS());
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ROTATE_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_ROTATE_STATUS(g_usAdjustValue);

#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
                OsdDispOsdRotateSwitch();
#endif
            }
            SET_OSD_STATE(_MENU_OTHER_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _UNSELECT, GET_OSD_ROTATE_STATUS());

            break;

        default:
            break;
    }
}

void MenuColorColortempUserR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_R();

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_R, GET_COLOR_TEMP_TYPE_USER_R());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_G, GET_COLOR_TEMP_TYPE_USER_G());
            break;
        case _LEFT_KEY_MESSAGE:

            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = _CT_USER;
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
            OsdDispClearSliderAndNumber();
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            OsdDispMainMenuItemIndication(_ITEM_2, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColortempUserG(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_G();

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_G, GET_COLOR_TEMP_TYPE_USER_G());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_B, GET_COLOR_TEMP_TYPE_USER_B());
            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_R, GET_COLOR_TEMP_TYPE_USER_R());

            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = _CT_USER;
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
            OsdDispClearSliderAndNumber();
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            OsdDispMainMenuItemIndication(_ITEM_2, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}


void MenuColorColortempUserB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_B();

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_B, GET_COLOR_TEMP_TYPE_USER_B());
            break;

        case _RIGHT_KEY_MESSAGE:

            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_G, GET_COLOR_TEMP_TYPE_USER_G());
            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = _CT_USER;
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
            OsdDispClearSliderAndNumber();
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            OsdDispMainMenuItemIndication(_ITEM_2, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColortempUserAdjustR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_R())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_R, GET_COLOR_TEMP_TYPE_USER_R());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_R, GET_COLOR_TEMP_TYPE_USER_R());

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_R())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_COLOR_TEMP_TYPE_USER_R(g_usAdjustValue);

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_COLOR_TEMP_TYPE_USER_R(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuColorColortempUserAdjustG(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_G())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_G, GET_COLOR_TEMP_TYPE_USER_G());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_G, GET_COLOR_TEMP_TYPE_USER_G());

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_G())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_COLOR_TEMP_TYPE_USER_G(g_usAdjustValue);

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_COLOR_TEMP_TYPE_USER_G(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuColorColortempUserAdjustB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_B())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_B, GET_COLOR_TEMP_TYPE_USER_B());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_B, GET_COLOR_TEMP_TYPE_USER_B());

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_B())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_COLOR_TEMP_TYPE_USER_B(g_usAdjustValue);

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_COLOR_TEMP_TYPE_USER_B(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_R);
            OsdDisplaySixColorGetOneColor(_SIXCOLOR_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _LEFT_KEY_MESSAGE:

            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT();
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserY(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_Y);
            OsdDisplaySixColorGetOneColor(_SIXCOLOR_Y);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT();
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserG(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_G);
            OsdDisplaySixColorGetOneColor(_SIXCOLOR_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT();
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserC(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_C);
            OsdDisplaySixColorGetOneColor(_SIXCOLOR_C);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT();
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_B);
            OsdDisplaySixColorGetOneColor(_SIXCOLOR_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT();
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserM(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_M);
            OsdDisplaySixColorGetOneColor(_SIXCOLOR_M);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT();
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserRHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserRSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserGHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserGSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserCHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserCSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserRHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);


            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());

#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());

#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserRSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserGHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserGSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserCHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserCSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorPCMSoftProftAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PCM_SOFT_PROFT_MODE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);

            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_PCM_SOFT_PROFT_MODE() == _PCM_SOFT_MODE_1)
            {
                SET_OSD_PCM_SOFT_PROFT_MODE(_PCM_SOFT_MODE_2);
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
                UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
#endif
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_SOFT_PROFT_TYPE, _SELECT, GET_OSD_PCM_SOFT_PROFT_MODE());
            }
            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_PCM_SOFT_PROFT_MODE() == _PCM_SOFT_MODE_2)
            {
                SET_OSD_PCM_SOFT_PROFT_MODE(_PCM_SOFT_MODE_1);

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
                UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
#endif
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_SOFT_PROFT_TYPE, _SELECT, GET_OSD_PCM_SOFT_PROFT_MODE());
            }
            break;


            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PCM_SOFT_PROFT_MODE())
            {
                SET_OSD_PCM_SOFT_PROFT_MODE(g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
            break;

        default:
            break;
    }
}


void MenuAdvanceODOnOffAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_OD_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());

            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_OD_STATUS() != _OFF)
            {
                SET_OSD_OD_STATUS(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_OD_STATUS());
#if(_OD_SUPPORT == _ON)
                ScalerODEnable(GET_OSD_OD_STATUS());
#endif
            }

            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_OD_STATUS() != _ON)
            {
                SET_OSD_OD_STATUS(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_OD_STATUS());
#if(_OD_SUPPORT == _ON)
                ScalerODEnable(GET_OSD_OD_STATUS());
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_OD_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_OD_STATUS(g_usAdjustValue);
#if(_OD_SUPPORT == _ON)
                ScalerODEnable(GET_OSD_OD_STATUS());
#endif
            }
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());

            break;

        default:
            break;
    }
}


void MenuAdvanceODGainAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_OD_GAIN())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_GAIN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_OD_GAIN(), _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_OD_GAIN_ADJUST, GET_OSD_OD_GAIN());
#if(_OD_SUPPORT == _ON)
            ScalerODAdjustDeltaGain(GET_OSD_OD_GAIN());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_OD_GAIN())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_OD_GAIN(g_usAdjustValue);
#if(_OD_SUPPORT == _ON)
                ScalerODAdjustDeltaGain(GET_OSD_OD_GAIN());
#endif // End of #if(_OD_SUPPORT == _ON)
            }
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_GAIN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_OD_GAIN(), _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);




            break;

        default:
            break;
    }
}

void MenuAdvanceDpD0VersionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D0_VERSION())
            {
                if((GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D0))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
                // Disable HDR Function, if DP Version Switch to 1.1/1.2
                if((GET_OSD_DP_D0_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF))
                {
                    SET_OSD_HDR_MODE(_HDR10_MODE_OFF);

                    // Switch DP D0 Port Edid
                    UserCommonInterfaceDPSwitchEdid(_D0_INPUT_PORT);
                }
#endif
#endif

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_SUPPORT == _ON)
                UserCommonInterfaceDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());

                if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                {
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
#endif
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());

            break;

        case _RIGHT_KEY_MESSAGE:
#if((_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ) || (_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ))
            if((GET_OSD_DP_D0_VERSION() + 1) > _DP_VER_AMOUNT)
            {
                SET_OSD_DP_D0_VERSION(_DP_VER_1_DOT_1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
            }
            else
            {
                SET_OSD_DP_D0_VERSION(GET_OSD_DP_D0_VERSION() + 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
            }
#endif
            break;
        case _LEFT_KEY_MESSAGE:
#if((_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ) || (_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ))
            if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_D0_VERSION(_DP_VER_AMOUNT);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
            }
            else
            {
                SET_OSD_DP_D0_VERSION(GET_OSD_DP_D0_VERSION() - 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D0_VERSION())
            {
                SET_OSD_DP_D0_VERSION(g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());

            break;

        default:
            break;
    }
}



void MenuAdvanceDpD1VersionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D1_VERSION())
            {
                if((GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D1))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
                // Disable HDR Function, if DP Version Switch to 1.1/1.2
                if((GET_OSD_DP_D1_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF))
                {
                    SET_OSD_HDR_MODE(_HDR10_MODE_OFF);

                    // Switch DP D1 Port Edid
                    UserCommonInterfaceDPSwitchEdid(_D1_INPUT_PORT);
                }
#endif
#endif

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_SUPPORT == _ON)
                UserCommonInterfaceDpVersionSwitch(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());

                if(SysSourceGetInputPort() == _D1_INPUT_PORT)
                {
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
#endif
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());

            break;

        case _RIGHT_KEY_MESSAGE:
#if((_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ) || (_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ))
            if((GET_OSD_DP_D1_VERSION() + 1) > _DP_VER_AMOUNT)
            {
                SET_OSD_DP_D1_VERSION(_DP_VER_1_DOT_1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
            }
            else
            {
                SET_OSD_DP_D1_VERSION(GET_OSD_DP_D1_VERSION() + 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
            }
#endif
            break;
        case _LEFT_KEY_MESSAGE:
#if((_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ) || (_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ))
            if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_D1_VERSION(_DP_VER_AMOUNT);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
            }
            else
            {
                SET_OSD_DP_D1_VERSION(GET_OSD_DP_D1_VERSION() - 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D1_VERSION())
            {
                SET_OSD_DP_D1_VERSION(g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());

            break;

        default:
            break;
    }
}

void MenuAdvanceDpD2VersionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D2_VERSION())
            {
                if((GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D1))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
                // Disable HDR Function, if DP Version Switch to 1.1/1.2
                if((GET_OSD_DP_D2_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF))
                {
                    SET_OSD_HDR_MODE(_HDR10_MODE_OFF);

                    // Switch DP D2 Port Edid
                    UserCommonInterfaceDPSwitchEdid(_D2_INPUT_PORT);
                }
#endif
#endif

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_SUPPORT == _ON)
                UserCommonInterfaceDpVersionSwitch(_D2_INPUT_PORT, UserInterfaceGetDPVersion(_D2_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());

                if(SysSourceGetInputPort() == _D2_INPUT_PORT)
                {
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
#endif
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D2_VERSION());

            break;

        case _RIGHT_KEY_MESSAGE:
#if((_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ) || (_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ))
            if((GET_OSD_DP_D2_VERSION() + 1) > _DP_VER_AMOUNT)
            {
                SET_OSD_DP_D2_VERSION(_DP_VER_1_DOT_1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D2_VERSION());
            }
            else
            {
                SET_OSD_DP_D2_VERSION(GET_OSD_DP_D2_VERSION() + 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D2_VERSION());
            }
#endif
            break;
        case _LEFT_KEY_MESSAGE:
#if((_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ) || (_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ))
            if(GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_D2_VERSION(_DP_VER_AMOUNT);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D2_VERSION());
            }
            else

            {
                SET_OSD_DP_D2_VERSION(GET_OSD_DP_D2_VERSION() - 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D2_VERSION());
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D2_VERSION())
            {
                SET_OSD_DP_D2_VERSION(g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D2_VERSION());

            break;

        default:
            break;
    }
}

void MenuAdvanceDpD6VersionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D6_VERSION())
            {
                if((GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D6))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_SUPPORT == _ON)
                UserCommonInterfaceDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());

                if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                {
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
#endif
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());

            break;

        case _RIGHT_KEY_MESSAGE:
            if((GET_OSD_DP_D6_VERSION() + 1) > _DP_VER_AMOUNT)
            {
                SET_OSD_DP_D6_VERSION(_DP_VER_1_DOT_1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
            }
            else
            {
                SET_OSD_DP_D6_VERSION(GET_OSD_DP_D6_VERSION() + 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_D6_VERSION(_DP_VER_AMOUNT);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
            }
            else

            {
                SET_OSD_DP_D6_VERSION(GET_OSD_DP_D6_VERSION() - 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D6_VERSION())
            {
                SET_OSD_DP_D6_VERSION(g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
            break;

        default:
            break;
    }
}

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
void MenuAdvanceD0TypeCModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            if(g_usBackupValue != GET_OSD_D0_TYPE_C_U3_MODE())
            {
                if(g_usBackupValue == _TYPE_C_U3_ON)
                {
                    SET_OSD_D0_TYPE_C_U3_MODE(_TYPE_C_U3_ON);
                }
                else if(g_usBackupValue == _TYPE_C_U3_OFF)
                {
                    SET_OSD_D0_TYPE_C_U3_MODE(_TYPE_C_U3_OFF);
                }

                UserCommonInterfaceTypeCU3ModeSwitch(_D0_INPUT_PORT);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, g_usBackupValue);
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            if(g_usBackupValue == _TYPE_C_U3_ON)
            {
                g_usBackupValue = _TYPE_C_U3_OFF;
            }
            else
            {
                g_usBackupValue = _TYPE_C_U3_ON;
            }

            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _SELECT, g_usBackupValue);
            break;

        case _EXIT_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D0_TYPE_C_U3_MODE());
#endif
            break;

        default:
            break;
    }
}

void MenuAdvanceD1TypeCModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            if(g_usBackupValue != GET_OSD_D1_TYPE_C_U3_MODE())
            {
                if(g_usBackupValue == _TYPE_C_U3_ON)
                {
                    SET_OSD_D1_TYPE_C_U3_MODE(_TYPE_C_U3_ON);
                }
                else
                {
                    SET_OSD_D1_TYPE_C_U3_MODE(_TYPE_C_U3_OFF);
                }


                UserCommonInterfaceTypeCU3ModeSwitch(_D1_INPUT_PORT);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, g_usBackupValue);
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(g_usBackupValue == _TYPE_C_U3_ON)
            {
                g_usBackupValue = _TYPE_C_U3_OFF;
            }
            else
            {
                g_usBackupValue = _TYPE_C_U3_ON;
            }

            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _SELECT, g_usBackupValue);
            break;

        case _EXIT_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D1_TYPE_C_U3_MODE());
#endif

            break;

        default:
            break;
    }
}

void MenuAdvanceD2TypeCModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            break;


        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(g_usBackupValue == _TYPE_C_U3_ON)
            {
                g_usBackupValue = _TYPE_C_U3_OFF;
            }
            else
            {
                g_usBackupValue = _TYPE_C_U3_ON;
            }
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _SELECT, g_usBackupValue);
            break;

        case _EXIT_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            break;

        default:
            break;
    }
}

void MenuAdvanceD6TypeCModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            if(g_usBackupValue != GET_OSD_D6_TYPE_C_U3_MODE())
            {
                if(g_usBackupValue == _TYPE_C_U3_ON)
                {
                    SET_OSD_D6_TYPE_C_U3_MODE(_TYPE_C_U3_ON);
                }
                else
                {
                    SET_OSD_D6_TYPE_C_U3_MODE(_TYPE_C_U3_OFF);
                }

                UserCommonInterfaceTypeCU3ModeSwitch(_D6_INPUT_PORT);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, g_usBackupValue);
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(g_usBackupValue == _TYPE_C_U3_ON)
            {
                g_usBackupValue = _TYPE_C_U3_OFF;
            }
            else
            {
                g_usBackupValue = _TYPE_C_U3_ON;
            }
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _SELECT, g_usBackupValue);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_TYPE_C_MODE_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
            OsdDispMainMenuOptionSetting(_OPTION_TYPE_C_MODE_SELECT, _UNSELECT, GET_OSD_D6_TYPE_C_U3_MODE());
#endif
            break;

        default:
            break;
    }
}
#endif // End of #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

#if(_HDR10_SUPPORT == _ON)
void MenuAdvanceHdrModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_MODE())
            {
                if(((g_usBackupValue == _HDR10_MODE_OFF) && (GET_OSD_HDR_MODE() != _HDR10_MODE_OFF)) ||
                   ((g_usBackupValue != _HDR10_MODE_OFF) && (GET_OSD_HDR_MODE() == _HDR10_MODE_OFF)))
                {
#if(_EDID_HDR10_AUTO_SWITCH == _ON)

#if((_HDMI_MULTI_EDID_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
                    // Switch All HDMI Port Edid
                    UserCommonInterfaceHDMISwitchAllPortEdid();
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                    // Switch Dp Version to 1.3, if HDR On
                    UserAdjustHdrCheckDpVersion(GET_OSD_HDR_MODE());

                    // Switch All DP Port Edid
                    UserCommonInterfaceDPSwitchAllPortEdid();
#endif

#if(_HDR10_SUPPORT == _ON)
                    UserCommonHDR10SupportSwitch();
#endif

#endif
                }
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_HDR_MODE());
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(((GET_OSD_HDR_MODE() == _HDR10_MODE_FORCE_2084) && (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) ||
               ((GET_OSD_HDR_MODE() == _HDR10_MODE_OFF) && (GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)))
            {
            }
            else
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_MODE_ADJUST, GET_OSD_HDR_MODE());

                UserCommonHDRAdjust(_HDR_FLOW_OSD_MODE_CHANGE);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_MODE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_HDR_MODE(g_usAdjustValue);

                UserCommonHDRAdjust(_HDR_FLOW_OSD_MODE_CHANGE);
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_HDR_MODE());

            break;

        default:
            break;
    }
}


void MenuAdvanceHdrDarkEnhanceOnOffAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DARK_ENHANCE_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_DARK_ENHANCE_STATUS());

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
            {
                if(GET_OSD_DARK_ENHANCE_STATUS() != _OFF)
                {
                    SET_OSD_DARK_ENHANCE_STATUS(_OFF);
                    OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_DARK_ENHANCE_STATUS());
                }
            }
            else
            {
                if(GET_OSD_DARK_ENHANCE_STATUS() != _ON)
                {
                    SET_OSD_DARK_ENHANCE_STATUS(_ON);
                    OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_DARK_ENHANCE_STATUS());
                }
            }

            UserCommonHDRAdjust(_HDR_FLOW_OSD_DARK_ENHANCE);

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DARK_ENHANCE_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_DARK_ENHANCE_STATUS(g_usAdjustValue);

                UserCommonHDRAdjust(_HDR_FLOW_OSD_DARK_ENHANCE);
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_DARK_ENHANCE_STATUS());

            break;

        default:
            break;
    }
}
void MenuAdvanceHdrSharpnessOnOffAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_SHARPNESS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_SHARPNESS_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_HDR_SHARPNESS());

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
            {
                if(GET_OSD_HDR_SHARPNESS() != _OFF)
                {
                    SET_OSD_HDR_SHARPNESS(_OFF);
                    OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_HDR_SHARPNESS());
                }
            }
            else
            {
                if(GET_OSD_HDR_SHARPNESS() != _ON)
                {
                    SET_OSD_HDR_SHARPNESS(_ON);
                    OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _SELECT, GET_OSD_HDR_SHARPNESS());
                }
            }

#if(_ULTRA_VIVID_SUPPORT == _ON)
            UserCommonAdjustUltraVivid(_FUNCTION_ON, UserCommonInterfaceGetColorFormat(), _DB_APPLY_NO_POLLING);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_SHARPNESS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_HDR_SHARPNESS(g_usAdjustValue);

#if(_ULTRA_VIVID_SUPPORT == _ON)
                UserCommonAdjustUltraVivid(_FUNCTION_ON, UserCommonInterfaceGetColorFormat(), _DB_APPLY_NO_POLLING);
#endif
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_SHARPNESS_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_HDR_SHARPNESS());

            break;

        default:
            break;
    }
}

void MenuAdvanceHdrContrastAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_CONTRAST())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_CONTRAST_ADJUST, GET_OSD_HDR_CONTRAST());

#if((_CONTRAST_SUPPORT == _ON) && (_HDR10_SUPPORT == _ON))
            UserCommonHDRAdjustHDR10Contrast(GET_OSD_HDR_CONTRAST());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_CONTRAST())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_HDR_CONTRAST(g_usAdjustValue);

#if((_CONTRAST_SUPPORT == _ON) && (_HDR10_SUPPORT == _ON))
                UserCommonHDRAdjustHDR10Contrast(GET_OSD_HDR_CONTRAST());
#endif
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        default:
            break;
    }
}
void MenuAdvanceHdrColorEnhanceAdjust(void)
{
#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_COLOR_ENHANCE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_ADVANCE_HDR_COLOR_ENHANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_COLOR_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_COLOR_ENHANCE_ADJUST, GET_OSD_HDR_COLOR_ENHANCE());

#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
            UserCommonHDRAdjustHDR10ColorEffect();
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_COLOR_ENHANCE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_HDR_COLOR_ENHANCE(g_usAdjustValue);
            }

#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
            UserCommonHDRAdjustHDR10ColorEffect();
#endif
            SET_OSD_STATE(_MENU_ADVANCE_HDR_COLOR_ENHANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_COLOR_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_COLOR_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        default:
            break;
    }
#endif
}
void MenuAdvanceHdrLightEnhanceAdjust(void)
{
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_LIGHT_ENHANCE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_ADVANCE_HDR_LIGHT_ENHANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_LIGHT_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_LIGHT_ENHANCE_ADJUST, GET_OSD_HDR_LIGHT_ENHANCE());

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
            UserCommonHDRAdjustHDR10ColorEffect();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_LIGHT_ENHANCE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_HDR_LIGHT_ENHANCE(g_usAdjustValue);
            }

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
            UserCommonHDRAdjustHDR10ColorEffect();
#endif
            SET_OSD_STATE(_MENU_ADVANCE_HDR_LIGHT_ENHANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), ((WORD)GET_OSD_HDR_LIGHT_ENHANCE()*100/_LEVEL_H), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HDR_LIGHT_ENHANCE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        default:
            break;
    }
#endif
}


#endif

#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
void MenuAdvanceHdrLDOnOff(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_LOCAL_DIMMING();
            SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_LOCAL_DIMMING());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_LD_ADJ(), 100, 0, 50);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}


void MenuAdvanceHdrLDSmoothAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_OD_GAIN();
            SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_LOCAL_DIMMING());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispAdvanceMenuReDraw(_HIGH);

            break;

        default:
            break;
    }
}

void MenuAdvanceHdrLDOnOffAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LOCAL_DIMMING())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_LOCAL_DIMMING());
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_LOCAL_DIMMING() != _OFF)
            {
                SET_OSD_LOCAL_DIMMING(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_LOCAL_DIMMING());
#if(_LOCAL_DIMMING_SUPPORT == _ON)
                UserCommonLocalDimmingEnable(_DISABLE);
                UserAdjustBacklight(GET_OSD_BACKLIGHT());
#endif
            }

            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_LOCAL_DIMMING() != _ON)
            {
                SET_OSD_LOCAL_DIMMING(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_LOCAL_DIMMING());
#if(_LOCAL_DIMMING_SUPPORT == _ON)
                UserCommonLocalDimmingEnable(_ENABLE);
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LOCAL_DIMMING())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_LOCAL_DIMMING(g_usAdjustValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_LOCAL_DIMMING());

            break;

        default:
            break;
    }
}


void MenuAdvanceHdrLDSmoothAdjAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LD_ADJ())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_LD_ADJ(), 100, 0, 50);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ_ADJUST, GET_OSD_LD_ADJ());

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LD_ADJ())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_LD_ADJ(g_usAdjustValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_LD_ADJ(), 100, 0, 50);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        default:
            break;
    }
}
#endif

void MenuHotKeyDdcci(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
               (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
               (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
            {
                ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }
            else
            {
                OsdDispDisableOsd();
            }
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DDCCI);

            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
               (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
            {
                ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
               (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
               (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
            {
                ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }
            else
            {
                OsdDispDisableOsd();
            }
            break;

        default:
            break;
    }
}

void MenuHotKeySource(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(GET_OSD_DP_VERSION_HOTKEY_DISP() == _OFF)
            {
                if(g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
                {
                    switch(GET_OSD_INPUT_PORT_OSD_ITEM())
                    {
                        case _OSD_INPUT_AUTO: // auto
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_AUTO_SEARCH_SUPPORT == _OFF))
                            if(GET_OSD_DP_MST() != _MST_OFF)
                            {
                                SET_OSD_DP_MST(_MST_OFF);
                            }
#endif
                            SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);
                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType())
                            {
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;

                        case _OSD_INPUT_A0: // A0
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_A0_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }
                            break;
#else
                            return;
#endif


                        case _OSD_INPUT_D0: // D0
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D0_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D1:    // D1
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D1_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D2:    // D2
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D2_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D3:    // D3
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D3_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D4:    // D4
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D4_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D5:    // D5
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D5_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }

                            break;
#else
                            return;
#endif

                        case _OSD_INPUT_D6:    // D6
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
                            SET_FORCE_POW_SAV_STATUS(_FALSE);
                            SysSourceSwitchInputPort(_D6_INPUT_PORT);
                            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

                            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                            {
                                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            }
                            break;
#else
                            return;
#endif

                        default:
                            break;
                    }

#if(_DP_MST_SUPPORT == _ON)
                    UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
                    RTDNVRamSaveOSDData();
#endif
                }
                else
                {
                    if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
                       (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
                       (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
                    {
                        ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                    }
                    else
                    {
                        OsdDispDisableOsd();
                    }
                }
                SET_OSD_STATE(_MENU_NONE);
            }

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_INPUT_PORT_OSD_ITEM(OsdDisplayDetOverRange(GET_OSD_INPUT_PORT_OSD_ITEM(), 8, 0, _ON));
            OsdDispHotKeySourceMenuSwitch();
            if((GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D2) ||
               (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D6) ||
               (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_AUTO))
            {
                OsdDispHotKeySourceMenuIcon();
            }

            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
               (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
            {
                ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            break;

        case _LEFT_KEY_MESSAGE:

            SET_OSD_INPUT_PORT_OSD_ITEM(OsdDisplayDetOverRange(GET_OSD_INPUT_PORT_OSD_ITEM(), 8, 0, _ON));
            OsdDispHotKeySourceMenuSwitch();
            if((GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D5) ||
               (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D1) ||
               (GET_OSD_INPUT_PORT_OSD_ITEM() == _OSD_INPUT_D6))
            {
                OsdDispHotKeySourceMenuIcon();
            }
            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
               (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
            {
                ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_INPUT_PORT_OSD_ITEM())
            {
                SET_OSD_INPUT_PORT_OSD_ITEM(g_usBackupValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
               (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL) ||
               (SysModeGetModeState() == _MODE_STATUS_NOSUPPORT))
            {
                ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }
            else
            {
                OsdDispDisableOsd();
            }

            break;

        default:
            break;
    }
}


void MenuHotKeyDpOption(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usAdjustValue == _HOTKEY_DP_D0_OPTION)
            {
#if(_DP_SUPPORT == _ON)
                if((GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D0))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                UserCommonInterfaceDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                SysSourceSwitchInputPort(_D0_INPUT_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
#endif
            }
            else if(g_usAdjustValue == _HOTKEY_DP_D1_OPTION)
            {
#if(_DP_SUPPORT == _ON)
                if((GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D1))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                UserCommonInterfaceDpVersionSwitch(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                SysSourceSwitchInputPort(_D1_INPUT_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
#endif
            }
            else if(g_usAdjustValue == _HOTKEY_DP_D6_OPTION)
            {
#if(_DP_SUPPORT == _ON)
                if((GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D6))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                UserCommonInterfaceDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                SysSourceSwitchInputPort(_D6_INPUT_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
#endif
            }
            else if(g_usAdjustValue == _HOTKEY_DP_D2_OPTION)
            {
#if(_DP_SUPPORT == _ON)
                if((GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D6))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                UserCommonInterfaceDpVersionSwitch(_D2_INPUT_PORT, UserInterfaceGetDPVersion(_D2_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                SysSourceSwitchInputPort(_D2_INPUT_PORT);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
#endif
            }

            SET_FORCE_POW_SAV_STATUS(_FALSE);
            SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);
            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);

            if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
               (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
            {
                UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
            }

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) || (SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
            {
                ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            }

            if(g_usAdjustValue == _HOTKEY_DP_D0_OPTION)
            {
                OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DP_D0_OPTION);
            }
            else if(g_usAdjustValue == _HOTKEY_DP_D1_OPTION)
            {
                OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DP_D1_OPTION);
            }
            else if(g_usAdjustValue == _HOTKEY_DP_D2_OPTION)
            {
                OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DP_D2_OPTION);
            }
            else if(g_usAdjustValue == _HOTKEY_DP_D6_OPTION)
            {
                OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DP_D6_OPTION);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usAdjustValue == _HOTKEY_DP_D0_OPTION)
            {
#if (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D1_OPTION);
#elif (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D2_OPTION);
#elif (_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D6_OPTION);
#endif
            }
            else if(g_usAdjustValue == _HOTKEY_DP_D1_OPTION)
            {
#if (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D2_OPTION);
#elif (_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D6_OPTION);
#elif (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D0_OPTION);
#endif
            }
            else if(g_usAdjustValue == _HOTKEY_DP_D2_OPTION)
            {
#if (_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D6_OPTION);
#elif (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D0_OPTION);
#elif (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D1_OPTION);
#endif
            }
            else if(g_usAdjustValue == _HOTKEY_DP_D6_OPTION)
            {
#if (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D0_OPTION);
#elif (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D1_OPTION);
#elif (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                OsdDispHotKeyOptionMenu(_HOTKEY_DP_D2_OPTION);
#endif
            }
            // SET_OSD_POWER_SAVING_SHOW_DP_OPTION(_FALSE);
            // OsdDispDisableOsd();
            // SET_OSD_STATE(_MENU_HOTKEY_SOURCE);
            // OsdDispHotKeySourceMenu();

            break;

        default:
            break;
    }
}


void MenuPanelUniformityMsgAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _EXIT_KEY_MESSAGE:
            if(g_usAdjustValue != GET_OSD_PANEL_UNIFORMITY())
            {
                SET_OSD_PANEL_UNIFORMITY(g_usAdjustValue);

#if(_UNIFORMITY_SUPPORT == _ON)
                ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
                {
                    ScalerTimerWaitForEvent(_EVENT_DVS);
                    ScalerTimerDelayXms(2);
                    UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);

                    ScalerColorPanelUniformityEnable(_FUNCTION_ON);
                }
#endif
            }
            break;

        case _MENU_KEY_MESSAGE:
            RTDNVRamSaveOSDData();
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            OsdFuncDisableOsd();
            OsdFuncCloseWindow(_OSD_WINDOW_ALL);
            OsdDispMainMenu();

            if(g_usBackupValue == _FROM_STATE_GAMMA)
            {
                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
                OsdDispMainMenuItemIndication(_ITEM_1, 9, _OSD_SELECT);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);

                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
                {
                    SET_OSD_STATE(_MENU_COLOR_GAMMA);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA());
                }
                else
                {
                    SET_OSD_STATE(_MENU_COLOR_GAMMA_ADJUST);
                    g_usBackupValue = GET_OSD_GAMMA();
                    OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _SELECT, GET_OSD_GAMMA());
                }

                if(GET_OSD_GAMMA() == _GAMMA_24)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
                }
            }
            else if(g_usBackupValue == _FROM_STATE_PCM)
            {
                OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
                OsdDispMainMenuItemIndication(_ITEM_7, 9, _OSD_SELECT);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);

                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
                {
                    SET_OSD_STATE(_MENU_COLOR_PCM);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS());
                }
                else
                {
                    SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
                    g_usBackupValue = GET_OSD_PCM_STATUS();
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS());
                }

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                if(GET_OSD_PCM_STATUS() >= _PCM_OSD_SOFT_PROFT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
                }
                else
#endif
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }
            }
#if(_HDR10_SUPPORT == _ON)
            else if(g_usBackupValue == _FROM_STATE_HDR)
            {
                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
                {
                    OsdDispAdvanceMenuReDraw(_HIGH);
                }
                else
                {
                    OsdDispAdvanceMenuReDraw(_HIGH);
                }
            }
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
            else if(g_usBackupValue == _FROM_STATE_LD)
            {
                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
                {
                    OsdDispAdvanceMenuReDraw(_HIGH);
                }
                else
                {
                    //OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
                    //OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
                    SET_OSD_STATE(_MENU_ADVANCE_HDR_LD_ONOFF);
                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_LOCAL_DIMMING);
                    OsdDispMainMenuOptionSetting(_OPTION_ON_OFF, _UNSELECT, GET_OSD_LOCAL_DIMMING());
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                }
            }
#endif
#if(_SDR_TO_HDR_SUPPORT == _ON)
            else if(g_usBackupValue == _FROM_STATE_SDRTOHDR)
            {
                if(GET_OSD_PANEL_UNIFORMITY() == _ON)
                {
                    OsdDispAdvanceMenuReDraw(_HIGH);
                }
                else
                {
                    OsdDispAdvanceMenuReDraw(_HIGH);
                }
            }
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispPanelUniformityMsgSwitch();

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
            if(GET_OSD_PANEL_UNIFORMITY() == _ON)
            {
                ScalerTimerWaitForEvent(_EVENT_DVS);
                ScalerTimerDelayXms(2);
                UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);

                ScalerColorPanelUniformityEnable(_FUNCTION_ON);
            }
#endif
            break;

        default:
            break;
    }
}

code void (*OperationTable[])(void) =
{
    MenuNone,

    // main
    MenuPicture,
    MenuDisplay,
    MenuColor,
    MenuAdvance,
    MenuInput,
    MenuAudio,
    MenuOther,
    MenuInformation,
    MenuFactory,

    // picture
    MenuPictureBacklight,
    MenuPictureBrightness,
    MenuPictureContrast,
    MenuPictureSharpness,

    // display
    MenuDisplayAuto,
    MenuDisplayHPos,
    MenuDisplayVPos,
    MenuDisplayClock,
    MenuDisplayPhase,
    MenuDisplayDispRotate,
    MenuDisplayLatency,
    MenuDislayFreeze,

    // color
    MenuColorPanelUniformity,
    MenuColorGamma,
    MenuColorTemperature,
    MenuColorEffect,
    MenuColorDemo,
    MenuColorFormat,
    MenuColorPCM,
    MenuColorHue,
    MenuColorSaturation,

    // advance
    MenuAdvanceItem,

    // input
    MenuInputAuto,
    MenuInputA0Port,
    MenuInputD0Port,
    MenuInputD1Port,
    MenuInputD2Port,
    MenuInputD3Port,
    MenuInputD4Port,
    MenuInputD5Port,
    MenuInputD6Port,

    // audio
    MenuAudioVolume,
    MenuAudioMute,
    MenuAudioStandAlong,
    MenuAudioAudioSource,
    MenuAudioSoundMode,
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    MenuAudioAudioSelfTest,
#endif
    // other
    MenuOtherReset,
    MenuOtherMenuTime,
    MenuOtherOsdHPos,
    MenuOtherOsdVPos,
    MenuOtherLanguage,
    MenuOtherTransparency,
    MenuOtherRotate,

    // picture adjust
    MenuPictureBacklightAdjust,
    MenuPictureBrightnessAdjust,
    MenuPictureContrastAdjust,
    MenuPictureSharpnessAdjust,

    // display adjust
    MenuDisplayHPosAdjust,
    MenuDisplayVPosAdjust,
    MenuDisplayClockAdjust,
    MenuDisplayPhaseAdjust,
    MenuDisplayDispRotateAdjust,
    MenuDisplayLatencyAdjust,
    MenuDisplayFreezeAdjust,

    // color adjust
    MenuColorPanelUniformityAdjust,
    MenuColorGammaAdjust,
    MenuColorColorTempAdjust,
    MenuColorColorEffectAdjust,
    MenuColorColorDemoAdjust,
    MenuColorColorFormatAdjust,
    MenuColorColorPCMAdjust,
    MenuColorColorHueAdjust,
    MenuColorColorSaturationAdjust,

    // advance adjust
    MenuAdvanceAspectAdjust,
    MenuAdvanceOverScanAdjust,
    MenuAdvanceOverDriveOnOff,
    MenuAdvanceOverDriveGain,
    MenuAdvanceDCRAdjust,
    MenuAdvanceDdcciAdjust,
    MenuAdvanceUltraVividAdjust,
    MenuAdvanceDpOptionD0,
    MenuAdvanceDpOptionD1,
    MenuAdvanceDpOptionD2,
    MenuAdvanceDpOptionD6,
    MenuAdvanceDPMstAdjust,
    MenuAdvanceDPEdidAdjust,
    MenuAdvanceCloneAdjust,
    MenuAdvanceFreeSyncAdjust,
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    MenuAdvanceTypeCModeD0,
    MenuAdvanceTypeCModeD1,
    MenuAdvanceTypeCModeD2,
    MenuAdvanceTypeCModeD6,
#endif

#if(_HDR10_SUPPORT == _ON)
    MenuAdvanceHdrMode,
    MenuAdvanceHdrDarkEnhanceOnOff,
    MenuAdvanceHdrSharpnessOnOff,
    MenuAdvanceHdrContrast,
    MenuAdvanceHdrColorEnhance,
    MenuAdvanceHdrLightEnhance,
#endif
    MenuAdvanceEdidAdjust,
    MenuAdvanceEdidDXAdjust,
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    MenuAdvanceHDMIVersionAdjust,
    MenuAdvanceDxHDMIVersionAdjust,
#endif
#if(_PIXEL_SHIFT_SUPPORT == _ON)
    MenuAdvancePixelShifAdjust,
#endif
#if (_SDR_TO_HDR_SUPPORT == _ON)
    MenuAdvanceSdrToHdrAdjust,
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    MenuAdvanceMBRMode,
    MenuAdvanceMBRDuty,
    MenuAdvanceMBRPosition,
    MenuAdvanceMBRModeAdjust,
    MenuAdvanceMBRDutyAdjust,
    MenuAdvanceMBRPositionAdjust,
#endif

    // Audio adjust
    MenuAudioVolumeAdjust,
    MenuAudioMuteOnOff,
    MenuAudioStandAlongSelect,
    MenuAudioAudioSourceSelect,
    MenuAudioSoundModeSelect,
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    MenuAudioAudioSelfTestSelect,
#endif

    // other adjust
    MenuOtherMenuTimeAdjust,
    MenuOtherOsdHPosAdjust,
    MenuOtherOsdVPosAdjust,
    MenuOtherLanguageAdjust,
    MenuOtherTransparencyAdjust,
    MenuOtherRotateAdjust,

    // color temp user RGB
    MenuColorColortempUserR,
    MenuColorColortempUserG,
    MenuColorColortempUserB,

    // color temp user adjust RGB
    MenuColorColortempUserAdjustR,
    MenuColorColortempUserAdjustG,
    MenuColorColortempUserAdjustB,

    // color effect user adjust
    MenuColorColorEffcUserR,
    MenuColorColorEffcUserY,
    MenuColorColorEffcUserG,
    MenuColorColorEffcUserC,
    MenuColorColorEffcUserB,
    MenuColorColorEffcUserM,

    MenuColorColorEffcUserRHue,
    MenuColorColorEffcUserRSat,

    MenuColorColorEffcUserYHue,
    MenuColorColorEffcUserYSat,

    MenuColorColorEffcUserGHue,
    MenuColorColorEffcUserGSat,

    MenuColorColorEffcUserCHue,
    MenuColorColorEffcUserCSat,

    MenuColorColorEffcUserBHue,
    MenuColorColorEffcUserBSat,

    MenuColorColorEffcUserMHue,
    MenuColorColorEffcUserMSat,

    // color effect user adjust Hue & Sat
    MenuColorColorEffcUserRHueAdjust,
    MenuColorColorEffcUserRSatAdjust,

    MenuColorColorEffcUserYHueAdjust,
    MenuColorColorEffcUserYSatAdjust,

    MenuColorColorEffcUserGHueAdjust,
    MenuColorColorEffcUserGSatAdjust,

    MenuColorColorEffcUserCHueAdjust,
    MenuColorColorEffcUserCSatAdjust,

    MenuColorColorEffcUserBHueAdjust,
    MenuColorColorEffcUserBSatAdjust,

    MenuColorColorEffcUserMHueAdjust,
    MenuColorColorEffcUserMSatAdjust,

    MenuColorColorPCMSoftProftAdjust,

    MenuAdvanceODOnOffAdjust,
    MenuAdvanceODGainAdjust,

    MenuAdvanceDpD0VersionAdjust,
    MenuAdvanceDpD1VersionAdjust,
    MenuAdvanceDpD2VersionAdjust,
    MenuAdvanceDpD6VersionAdjust,

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    MenuAdvanceD0TypeCModeAdjust,
    MenuAdvanceD1TypeCModeAdjust,
    MenuAdvanceD2TypeCModeAdjust,
    MenuAdvanceD6TypeCModeAdjust,
#endif

#if(_HDR10_SUPPORT == _ON)
    MenuAdvanceHdrModeAdjust,
    MenuAdvanceHdrDarkEnhanceOnOffAdjust,
    MenuAdvanceHdrSharpnessOnOffAdjust,
    MenuAdvanceHdrContrastAdjust,
    MenuAdvanceHdrColorEnhanceAdjust,
    MenuAdvanceHdrLightEnhanceAdjust,
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
    MenuAdvanceHdrLDOnOff,
    MenuAdvanceHdrLDSmoothAdj,
    MenuAdvanceHdrLDOnOffAdjust,
    MenuAdvanceHdrLDSmoothAdjAdjust,
#endif

    // ddcci
    MenuHotKeyDdcci,

    // hotkey source
    MenuHotKeySource,

    // hotkey dp version
    MenuHotKeyDpOption,

    // ask turn off/on panel uniformity msg
    MenuPanelUniformityMsgAdjust,
};

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
