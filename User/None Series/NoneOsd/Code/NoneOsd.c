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
// ID Code      : NoneOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __NONE_OSD__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _NONE_OSD)

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
StructOsdUserDataType g_stOSDUserData;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserOsdHandler(void);
void NoneOsdSystemFlowProc(void);
void NoneOsdEventMsgProc(void);

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
    NoneOsdSystemFlowProc();
    NoneOsdEventMsgProc();
}

//--------------------------------------------------
// Description  : OSD system flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void NoneOsdSystemFlowProc(void)
{
    switch(SysPowerGetPowerStatus())
    {
        case _POWER_STATUS_OFF:

            break;

        case _POWER_STATUS_SAVING:

            break;

        case _POWER_STATUS_NORMAL:

            break;

        default:

            break;
    }

    switch(SysModeGetModeState())
    {
        case _MODE_STATUS_POWER_OFF:

            break;

        case _MODE_STATUS_INITIAL:

            break;

        case _MODE_STATUS_SEARCH:
            if(SysModeGetModeStateChange() == _TRUE)
            {
                UserInterfaceKeyPadLedControl(_LED_POWER_SEARCH);
            }
            break;

        case _MODE_STATUS_DISPLAY_SETTING:

            break;

        case _MODE_STATUS_ACTIVE:
            if(SysModeGetModeStateChange() == _TRUE)
            {
                UserInterfaceKeyPadLedControl(_LED_POWER_ACTIVE);
            }

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_FACTORY_MODE);
#endif

            break;

        case _MODE_STATUS_NOSUPPORT:
        case _MODE_STATUS_NOSIGNAL:

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
            SysModeSetFreeRun();
            ScalerDDomainBackgroundSetColor(0x00, 0x00, 0x00);
            ScalerDDomainBackgroundEnable(_ENABLE);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            ScalerDDomainBackgroundSetColor(0xFF, 0x00, 0x00);
            ScalerTimerDelayXms(500);
            ScalerDDomainBackgroundSetColor(0x00, 0xFF, 0x00);
            ScalerTimerDelayXms(500);
            ScalerDDomainBackgroundSetColor(0x00, 0x00, 0xFF);
            ScalerTimerDelayXms(500);
            ScalerDDomainBackgroundEnable(_DISABLE);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_FACTORY_MODE);

#else
            if(SysModeGetModeStateChange() == _TRUE)
            {
                SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
            }

#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)

            break;

        case _MODE_STATUS_POWER_SAVING:

            break;

        case _MODE_STATUS_FACTORY:

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
            NoneFactoryQCFlow(SysSourceGetInputPort());
#endif

            break;

        default:

            break;
    }

    if(GET_KEYMESSAGE() < _KEY_AMOUNT)
    {
        // (*OperationTable[GET_OSD_STATE()])();
        (*OperationTable[0])();
    }
}

//--------------------------------------------------
// Description  : OSD event message processing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void NoneOsdEventMsgProc(void)
{
//        switch(GET_OSD_EVENT_MESSAGE())
//        {
//
//    #if(_VGA_SUPPORT == _ON)
//            case _OSDEVENT_DO_AUTO_CONFIG_MSG:
//
//                UserCommonAutoConfig();
//
//                break;
//    #endif
//
//        }
//
//        SET_OSD_EVENT_MESSAGE(_OSDEVENT_NONE_MSG);
}

//--------------------------------------------------
// Description  : Menu None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void MenuNone(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_ULTRA_VIVID_SUPPORT == _ON)
            UserCommonAdjustUltraVivid(_FUNCTION_OFF, _COLOR_SPACE_RGB, _DB_APPLY_POLLING);
#endif

#if(_GAMMA_FUNCTION == _ON)
            UserAdjustGamma(_GAMMA_OFF);
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            ScalerColorHLWAdjust(0, 0, 0, 0, _DB_APPLY_NONE);
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
            ScalerMDomainAspectOriginMode(_FALSE);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
            UserCommonAdjustAspectRatio();
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
#if(_AUDIO_SUPPORT == _ON)
            UserAdjustAudioMuteSwitch();
            UserAdjustAudioVolume(0);
#endif
#endif

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
            UserAdjustColorEffectMode();
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            UserAdjustHLWinType(0);
            UserAdjustHLWinType5Move();
            UserAdjustHighLightWindowEffectSpace();
#endif

#if(_INSTANT_TIMER_EVENT_0 == _ON)
            ScalerTimer0SetTimerCount(16);
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            ScalerColorHLWBorderEnable(_OFF, _OFF, _OFF, _OFF);
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            UserCommonAutoConfig();
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                // Perform auto-color for RGB
                if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_RGB) == _AUTO_SUCCESS)
                {
                    ScalerAutoGetAutoColorResult(&g_stAdcData);
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
                    // Calculate YPbPr gain/offset using formula
                    g_stAdcData = ScalerAutoBalanceYPbPrFromFormula(&g_stAdcData);
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);

                    // Restore RGB gain/offset
                    ScalerAutoGetAutoColorResult(&g_stAdcData);
#endif
                }
                else
                {
                    UserCommonNVRamRestoreADCSetting();
                }
            }
#endif // End of #if(_VGA_SUPPORT == _ON)
            break;

        case _EXIT_KEY_MESSAGE:
            // auto adjust
#if(_VGA_SUPPORT == _ON)
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_FAIL_SAFE_MODE() == _FALSE) && (SysSourceGetSourceType() == _SOURCE_VGA))
            {
//                SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
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
};

#endif//#if(_OSD_TYPE == _NONE_OSD)
