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
// ID Code      : BeaconUserAdjust.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST__
#define __USER_PANEL__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
#define _HLWIN_TYPE5_MOVE_TIME                      SEC(0.01)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// IR TABLE
//----------------------------------------------------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
BYTE code tIR_INITIAL_TABLE[] =
{
#if(_IR_PROTOCAL == _IR_NEC_DTV328)
    #include "IRRemote/NEC_DTV328.h"

#elif(_IR_PROTOCAL == _IR_SONY_B102P)
    #include "IRRemote/SONY_B102P.h"

#elif(_IR_PROTOCAL == _IR_PHILIPS_RC6)
    #include "IRRemote/PHILIPS_RC6.h"

#endif // End of #if(_IR_PROTOCAL == _IR_NEC_DTV328)
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
bit g_bHLWinRLMove = _RIGHT;
WORD g_usHLWinHPos;
WORD g_usHLWinHWidth;
WORD g_usHLWinVPos;
WORD g_usHLWinVHeight;
#endif

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
bit g_bTypeCPortControllerPowerOffFlag = _FALSE;
#endif
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
//-------------------------------------------------------
// Adjust Backlight
//-------------------------------------------------------
void UserAdjustBacklight(WORD usBacklight);

//-------------------------------------------------------
// Dp Load Edid Related
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
EnumEdidSelection UserAdjustGetDpEdidIndex(BYTE ucInputPort);
#endif

//-------------------------------------------------------
// Audio Related
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
void UserAdjustAudioMuteSwitch(void);
void UserAdjustAudioVolume(BYTE ucVolume);
WORD UserAdjustAudioVolumeMapping(BYTE ucVolume);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//-------------------------------------------------------
// DCC
//-------------------------------------------------------
#if(_DCC_FUNCTION == _ON)
void UserAdjustDCC(BYTE ucColorEffect);
#endif // End of #if(_DCC_FUNCTION == _ON)

//-------------------------------------------------------
// ICM
//-------------------------------------------------------
#if(_ICM_SUPPORT == _ON)
void UserAdjustICM(BYTE ucColorEffect);
#endif

#if(_SCM_SUPPORT == _ON)
void UserAdjustSCM(BYTE ucColorEffect);
#endif

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
void UserAdjustColorEffectMode(void);
#endif

//-------------------------------------------------------
// CTS / BRI
//-------------------------------------------------------
#if(_CONTRAST_SUPPORT == _ON)
void UserAdjustContrast(WORD usContrast);
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
void UserAdjustBrightness(WORD usBrightness);
#endif

//-------------------------------------------------------
// 3D Gamma
//-------------------------------------------------------

//-------------------------------------------------------
// sRGB
//-------------------------------------------------------
#if(_GLOBAL_HUE_SATURATION == _ON)
void UserAdjustGlobalHueSat(SWORD shHue, WORD usSat);
#endif

//-------------------------------------------------------
// Unifomity
//-------------------------------------------------------

//-------------------------------------------------------
// Output Gamma
//-------------------------------------------------------

//-------------------------------------------------------
// OD
//-------------------------------------------------------
#if(_OD_SUPPORT == _ON)
void UserAdjustOD(void);
#endif

//-------------------------------------------------------
// Highlight window
//-------------------------------------------------------
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
void UserAdjustHLWinType(BYTE ucHLWinType);
void UserAdjustHLWinType5Move(void);
void UserAdjustHighLightWindowEffectSpace(void);
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
void UserAdjustFREESYNCODMeasure(void);
#endif


//-------------------------------------------------------
// HW IR Mode
//-------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
void UserAdjusIR(void);
#endif

//-------------------------------------------------------
// DP
//-------------------------------------------------------
#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
void UserAdjustEmbeddedDpSwitch(void);
#endif

//-------------------------------------------------------
// Pixel Shift
//-------------------------------------------------------
#if(_PIXEL_SHIFT_SUPPORT == _ON)
void UserAdjustPixelShifting(void);
#endif

//-------------------------------------------------------
// SDRToHDR
//-------------------------------------------------------
#if(_SDR_TO_HDR_SUPPORT == _ON)
void UserAdjustSDRToHDR(bit bOn);
#endif

//-------------------------------------------------------
// DCR
//-------------------------------------------------------
#if(_DCR_SUPPORT == _ON)
#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
void UserAdjustDCRTHD(void);
#endif
#endif

//-------------------------------------------------------
// Type-C Port Controller
//-------------------------------------------------------
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
void UserAjustTypeCPowerControl(EnumPowerAction enumSwitch);
#endif
#endif
#endif

//-------------------------------------------------------
// HDR
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
void UserAdjustHdrCheckDpVersion(WORD usHdrMode);
#endif

//-------------------------------------------------------
// 
//-------------------------------------------------------
#if(_BACKLIGHT_SENSOR == _ON)
void UserAdjustSetSensorbacklightvalue(BYTE SenserBrightnessFlag);
#endif

//-------------------------------------------------------
// HDMI_SPLITTER_1X2
//-------------------------------------------------------
#if(_HDMI_SPLITTER_1X2_EN == _ON)
void UserAdjust_HdmiSplitter_Init(void);
void UserAdjust_HdmiSplitter_SetData(BYTE Data1st,BYTE Data2nd);
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustBacklight(WORD usBacklight)
{
    float ucTemp;
    BYTE ucFacBacklightLRegMax;
    BYTE ucFacBacklightLRegMid;
    BYTE ucFacBacklightLRegMin;
#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
    BYTE ucBackLight;
#endif

#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    ucFacBacklightLRegMax = GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE());
    ucFacBacklightLRegMid = GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE());
    ucFacBacklightLRegMin = GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE());
#else
    ucFacBacklightLRegMax = GET_FACTORY_BACKLIGHT_REG_MAX();
    ucFacBacklightLRegMid = GET_FACTORY_BACKLIGHT_REG_MID();
    ucFacBacklightLRegMin = GET_FACTORY_BACKLIGHT_REG_MIN();
#endif

#if((_USER_BEACON_FACTORY_OSD == _ON)&&(_OSD_BriCon_RANGE == 100))
    if(ucFacBacklightLRegMax < ucFacBacklightLRegMid)
    {
        ucFacBacklightLRegMid = ucFacBacklightLRegMax;
    }

    if(ucFacBacklightLRegMid < ucFacBacklightLRegMin)
    {
        ucFacBacklightLRegMin = ucFacBacklightLRegMid;
    }


    if(usBacklight >= _DEFAULT_BACKLIGHT)
    {
        usBacklight = ucTemp = (float)(usBacklight-_DEFAULT_BACKLIGHT)*(ucFacBacklightLRegMax-ucFacBacklightLRegMid)/(100-_DEFAULT_BACKLIGHT)+ucFacBacklightLRegMid;
    }
    else
    {
        usBacklight = ucTemp =(float)(usBacklight)*(ucFacBacklightLRegMid-ucFacBacklightLRegMin)/_DEFAULT_BACKLIGHT+ucFacBacklightLRegMin;
    }
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
    ucBackLight = (BYTE)usBacklight;
#endif

    usBacklight = CAL_8BIT_PWM_TO_REAL_PWM((BYTE)usBacklight);

#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
#if(_PWM_DUT_RESOLUTION == _PWM_12BIT)
    if(usBacklight + GetDifferencePwmValue() < 0)
        usBacklight = 0;
    else if(usBacklight + GetDifferencePwmValue() > 4095)
        usBacklight = 4095;
    else
        usBacklight += GetDifferencePwmValue();
#endif
#endif

#if(_BACKLIGHT_PWM_INVERSE == _ON)
    usBacklight = ((_PWM_DUT_RESOLUTION == _PWM_12BIT)? 4095:255) - usBacklight;
#endif

#if(_PANEL_PWM_BEFORE_BL_CONTROL == _ON)
    if(PCB_PANEL_POWER_DETECT() == _PANEL_CONTROL_OFF)
    {
        return;
    }
#else
    if(GET_PANELPOWERSTATUS() != _BACKLIGHT_ON_ALREADY)
    {
        //if backlight on/off is not on,do not need to set Backlight pwm
        return;
    }
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
    UserCommonInterfaceOledAdjustBackLight(ucBackLight);
#endif

    // Adjust backlight by changing PWM duty
    PCB_BACKLIGHT_PWM(usBacklight);

#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
    if(GET_OSD_BACKLIGHT() != GET_SENSOR_BACKLIGHT())
    {
        // user adjust backlight, set stop sensor detect flag
        SET_IIC_SENSOR_BACKLIGHT_STOP_STATE();
        ScalerTimerReactiveTimerEvent(800, _USER_TIMER_EVENT_BACKLIGHTSENSOR_STOP);
        SET_UPDATE_TARGET_FLAG(_TRUE);
    }
    
#endif

}

//----------------------------------------------------------------------------
// Not Kernel Related Function
//----------------------------------------------------------------------------

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get the Mapping of Edid index of Function Application
// Input Value  : ucInputPort
// Output Value : Edid Index
//--------------------------------------------------
EnumEdidSelection UserAdjustGetDpEdidIndex(BYTE ucInputPort)
{
    BYTE ucIndex = 0;
    BYTE ucDpResolution = 0;

#if(_DP_FREESYNC_SUPPORT == _ON)
    if((GET_OSD_FREE_SYNC_STATUS() == _ON))
    {
        ucIndex += ((_DP_HDR10_SUPPORT == _ON) ? 0x06 : 0x03);
    }
#endif

#if(_DP_HDR10_SUPPORT == _ON)
    if((UserInterfaceHDRGetHDR10ModeStatus(ucInputPort) != _HDR10_MODE_OFF))
    {
        ucIndex += 0x03;
    }
#endif

    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D0_SELECT);
            break;
        case _D1_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D1_SELECT);
            break;
        case _D2_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D2_SELECT);
            break;
        case _D6_INPUT_PORT:
            ucDpResolution = UserCommonNVRamGetSystemData(_EDID_D6_SELECT);
            break;
        default:
            break;
    }

    switch(ucDpResolution)
    {
        case _DP_EDID_1080P:
            break;

        case _DP_EDID_2560_1440:
            ucIndex += 0x01;
            break;

        case _DP_EDID_4K2K_60HZ:
            ucIndex += 0x02;
            break;

        default:
            break;
    }

    return ucIndex;
}
#endif

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mute/Unmute Aduio Volume
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void UserAdjustAudioMuteSwitch(void)
{
    SysAudioMuteProc(UserInterfaceGetAudioMuteStatus());
}

//--------------------------------------------------
// Description  : Adjust Aduio Volume
// Input Value  : ucVolume
// Output Value : Node
//--------------------------------------------------
void UserAdjustAudioVolume(BYTE ucVolume)
{
    ScalerAudioDigitalAdjustVolume(UserAdjustAudioVolumeMapping(ucVolume));
}

//--------------------------------------------------
// Description  : OSD Volume Mapping to Real Value
// Input Value  : usVolume
// Output Value : usVolume
//--------------------------------------------------
WORD UserAdjustAudioVolumeMapping(BYTE ucVolume)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(UserInterfaceGetAudioSource() == _LINE_IN_AUDIO)
    {
        return (UserCommonAdjustPercentToRealValue(ucVolume, _LINE_IN_VOLUME_MAX, _LINE_IN_VOLUME_MIN, _LINE_IN_VOLUME_CENTER));
    }
    else
#endif // End of #if(_LINE_IN_SUPPORT == _ON)
    {
        return (UserCommonAdjustPercentToRealValue(ucVolume, _DIGITAL_VOLUME_MAX, _DIGITAL_VOLUME_MIN, _DIGITAL_VOLUME_CENTER));
    }
}
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DCC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set DCC Table
// Input Value  : Request DCC Table
// Output Value : None
//--------------------------------------------------
void UserAdjustDCC(BYTE ucColorEffect)
{
    if((ucColorEffect >= _COLOREFFECT_GAME) && (ucColorEffect < _COLOREFFECT_USER))
    {
        ScalerColorDCCAdjust(tDCC_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_DCC_FUNCTION == _ON)


#if(_ICM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set ICM parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustICM(BYTE ucColorEffect)
{
    if((ucColorEffect >= _COLOREFFECT_GAME) && (ucColorEffect < _COLOREFFECT_USER))
    {
        ScalerColorICMLoadTable(tICM_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_ICM_SUPPORT == _ON)

#if(_SCM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set SCM parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustSCM(BYTE ucColorEffect)
{
    if((ucColorEffect >= _COLOREFFECT_GAME) && (ucColorEffect < _COLOREFFECT_USER))
    {
        ScalerColorSCMLoadTable(tSCM_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_SCM_SUPPORT == _ON)

#if 0//((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustColorEffectMode(void)
{
    BYTE ucIndex = 0;
    BYTE ucBackupSixColor = 0;
    BYTE ucBackupHue = 0;
    BYTE ucBackupSaturation = 0;

    ucBackupSixColor = GET_OSD_SIX_COLOR();
    ucBackupHue = GET_OSD_SIX_COLOR_HUE();
    ucBackupSaturation = GET_OSD_SIX_COLOR_SATURATION();

    switch(GET_OSD_COLOR_EFFECT())
    {
        case _COLOREFFECT_STANDARD:
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif
            break;

        case _COLOREFFECT_USER:
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if 0//(_SIX_COLOR_SUPPORT == _ON)
            for(ucIndex = 0; ucIndex < 6; ucIndex++)
            {
                SET_OSD_SIX_COLOR(ucIndex);
                OsdDisplaySixColorGetOneColor(ucIndex);
                ScalerColorSixColorAdjust(ucIndex, GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
            }

            ScalerColorSixColorInitial();
#endif
            break;

        case _COLOREFFECT_MOVIE:
        case _COLOREFFECT_GAME:
        case _COLOREFFECT_PHOTO:
        case _COLOREFFECT_VIVID:
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_DCC_FUNCTION == _ON)
            UserAdjustDCC(GET_OSD_COLOR_EFFECT());
#endif

// Adjust SCM Table, Should before ICM Adjust
#if(_SCM_SUPPORT == _ON)
            UserAdjustSCM(GET_OSD_COLOR_EFFECT());
#endif

#if(_ICM_SUPPORT == _ON)
            UserAdjustICM(GET_OSD_COLOR_EFFECT());
#endif


#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_ON);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_ON);
#endif
            break;

        default:
            break;
    }

    SET_OSD_SIX_COLOR(ucBackupSixColor);
    SET_OSD_SIX_COLOR_HUE(ucBackupHue);
    SET_OSD_SIX_COLOR_SATURATION(ucBackupSaturation);
}
#endif // End of #if(_SIX_COLOR_SUPPORT == _ON)

#if(_CONTRAST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust Contrast
// Input Value  : 12 bit input, old 8 bit contrast input value must left shift 4 bit
//                0 (00h) ~ 1(800h) ~  2(FFFh)
// Output Value : void
//--------------------------------------------------
void UserAdjustContrast(WORD usContrast)
{
#if(_OSD_BriCon_RANGE == 100)
    BYTE g_ucDefaultContrast;
    WORD g_usContrast;
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    WORD pusData[6] = {0};

#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
    pusData[3] = 0x800;
    pusData[4] = 0x800;
    pusData[5] = 0x800;
#else
    pusData[3] = 0x80;
    pusData[4] = 0x80;
    pusData[5] = 0x80;
#endif

#else
    WORD pusData[3] = {0};
#endif

#if(_OSD_BriCon_RANGE == 100)
    g_usContrast = usContrast;
    g_ucDefaultContrast = _DEFAULT_CONTRAST;
    
    if(g_ucDefaultContrast > 100)
        g_ucDefaultContrast = 100;

    if(g_usContrast > 100)
        g_usContrast = 100;
    
    if((g_ucDefaultContrast == 100) || (g_ucDefaultContrast == 0))  // not has three point, only two point
    {
        usContrast = (DWORD)g_usContrast*(_CONTRAST_REG_VALUE_MAX-_CONTRAST_REG_VALUE_MIN) / 100 + _CONTRAST_REG_VALUE_MIN;
    }
    else
    {
        if(g_usContrast >= g_ucDefaultContrast)
        {
            usContrast = (DWORD)(g_usContrast-g_ucDefaultContrast)*(_CONTRAST_REG_VALUE_MAX-_CONTRAST_REG_VALUE_DEF)/(100-g_ucDefaultContrast)+_CONTRAST_REG_VALUE_DEF;
        }
        else
        {
            usContrast = (DWORD)(g_usContrast)*(_CONTRAST_REG_VALUE_DEF-_CONTRAST_REG_VALUE_MIN)/g_ucDefaultContrast+_CONTRAST_REG_VALUE_MIN;
        }
    }
    
#if(_CUSTOMER == _CUS_TOSHIBA)
#if(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND)
    if(GET_COLOR_TEMP_TYPE() == _BEACON_ULTRASOUND)
    {
        usContrast = (DWORD)g_usContrast*(_CONTRAST_REG_VALUE_MAX-_CONTRAST_REG_VALUE_DEF) / 100 + _CONTRAST_REG_VALUE_DEF;
    }
#endif
#endif

#endif

#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
    pusData[0] = (WORD)(((DWORD)g_stColorProcData.usColorTempR * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempR * usContrast / 2048);
    pusData[1] = (WORD)(((DWORD)g_stColorProcData.usColorTempG * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempG * usContrast / 2048);
    pusData[2] = (WORD)(((DWORD)g_stColorProcData.usColorTempB * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempB * usContrast / 2048);

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // 10-bit Panel
        pusData[0] = UserCommonAdjust10bitPanelCompensate(pusData[0]);
        pusData[1] = UserCommonAdjust10bitPanelCompensate(pusData[1]);
        pusData[2] = UserCommonAdjust10bitPanelCompensate(pusData[2]);
    }
#if(_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)
    else if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
    {
        pusData[0] = UserCommonAdjust6bitPanelCompensate(pusData[0]);
        pusData[1] = UserCommonAdjust6bitPanelCompensate(pusData[1]);
        pusData[2] = UserCommonAdjust6bitPanelCompensate(pusData[2]);
    }
#endif

#else
    pusData[0] = (WORD)(((DWORD)g_stColorProcData.usColorTempR * usContrast / 128) > 255) ? 255 : (WORD)((DWORD)g_stColorProcData.usColorTempR * usContrast / 128);
    pusData[1] = (WORD)(((DWORD)g_stColorProcData.usColorTempG * usContrast / 128) > 255) ? 255 : (WORD)((DWORD)g_stColorProcData.usColorTempG * usContrast / 128);
    pusData[2] = (WORD)(((DWORD)g_stColorProcData.usColorTempB * usContrast / 128) > 255) ? 255 : (WORD)((DWORD)g_stColorProcData.usColorTempB * usContrast / 128);

#if(_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)
    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
    {
        pusData[0] = UserCommonAdjust6bitPanelCompensate(pusData[0]);
        pusData[1] = UserCommonAdjust6bitPanelCompensate(pusData[1]);
        pusData[2] = UserCommonAdjust6bitPanelCompensate(pusData[2]);
    }
#endif
#endif

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
    {
        ScalerColorContrastAdjust(_CONTRAST_COEF_A, pusData);
        ScalerColorContrastAdjust(_CONTRAST_COEF_B, &pusData[3]);
    }
    else
    {
        ScalerColorContrastAdjust(_CONTRAST_COEF_B, pusData);
        ScalerColorContrastAdjust(_CONTRAST_COEF_A, &pusData[3]);
    }
#else
    ScalerColorContrastAdjust(_CONTRAST_COEF_A, pusData);
#endif

    ScalerColorContrastEnable(_FUNCTION_ON);
}
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust Brightness
// Input Value  : 10 bit input, old 8 bit brightness input value must left shift 2 bit
//                -2048(00h) ~ 0(200h) ~  +2044(3FFh)
// Output Value : void
//--------------------------------------------------
void UserAdjustBrightness(WORD usBrightness)
{
#if(_OSD_BriCon_RANGE == 100)
    BYTE g_ucDefaultBrightness;
    WORD g_usBrightness;
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    WORD pusData[6] = {0};

#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
    pusData[3] = 0x200;
    pusData[4] = 0x200;
    pusData[5] = 0x200;
#else
    pusData[3] = 0x80;
    pusData[4] = 0x80;
    pusData[5] = 0x80;
#endif

#else
    WORD pusData[3] = {0};
#endif

#if(_OSD_BriCon_RANGE == 100)
    g_usBrightness = usBrightness;
    g_ucDefaultBrightness = _DEFAULT_BRIGHTNESS;
    
    if(g_ucDefaultBrightness > 100)
        g_ucDefaultBrightness = 100;

    if(g_usBrightness > 100)
        g_usBrightness = 100;
    
    if((g_ucDefaultBrightness == 100) || (g_ucDefaultBrightness == 0))  // not has three point, only two point
    {
        usBrightness = (DWORD)g_usBrightness*(_BRIGHTNESS_REG_VALUE_MAX-_BRIGHTNESS_REG_VALUE_MIN)/100+_BRIGHTNESS_REG_VALUE_MIN;
    }
    else
    {
        if(g_usBrightness >= g_ucDefaultBrightness)
        {
            usBrightness = (DWORD)(g_usBrightness-g_ucDefaultBrightness)*(_BRIGHTNESS_REG_VALUE_MAX-_BRIGHTNESS_REG_VALUE_DEF)/(100-g_ucDefaultBrightness)+_BRIGHTNESS_REG_VALUE_DEF;
        }
        else
        {
            usBrightness = (DWORD)(g_usBrightness)*(_BRIGHTNESS_REG_VALUE_DEF-_BRIGHTNESS_REG_VALUE_MIN)/g_ucDefaultBrightness+_BRIGHTNESS_REG_VALUE_MIN;
        }
    }
#endif

    pusData[0] = usBrightness;
    pusData[1] = usBrightness;
    pusData[2] = usBrightness;

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
    {
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusData);
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_B, &pusData[3]);
    }
    else
    {
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_B, pusData);
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, &pusData[3]);
    }
#else
    ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusData);
#endif

    ScalerColorBrightnessEnable(_FUNCTION_ON);
}
#endif


#if(_GLOBAL_HUE_SATURATION == _ON)
//--------------------------------------------------
// Description  : Adjust Global Hue Saturation
// Input Value  : Hue and Saturation
// Output Value : None
//--------------------------------------------------
void UserAdjustGlobalHueSat(SWORD shHue, WORD usSat)  // for OSD Adjust & Dianliang:  Display Off & ON
{
    UserCommonAdjustGlobalHueSat(_DEFAULT_HUE - shHue, usSat);
}
#endif  // Enf of #if(_GLOBAL_HUE_SATURATION == _ON)

#if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load OD LUT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustOD(void)
{
#if(_FREESYNC_SUPPORT == _ON)
    if(ScalerSyncGetFREESYNCEnable() == _TRUE)
    {
        ScalerODLoadLUT(tOD_FREESYNC_TABLE[0], GET_CURRENT_BANK_NUMBER(), _OD_LUT_MODE);
    }
    else
#endif
    {
        ScalerODLoadLUT(tOD_TABLE[0], GET_CURRENT_BANK_NUMBER(), _OD_LUT_MODE);
    }
}
#endif // End of #if(_OD_SUPPORT == _ON)

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust High Light Window
// Input Value  : HLWinType
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinType(BYTE ucHLWinType)
{
    ucHLWinType = ucHLWinType;
/*
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);

    if(ucHLWinType == _HL_WIN_OFF)
    {
        return;
    }

    if(GET_MDOMAIN_OUTPUT_HWIDTH() == _PANEL_DH_WIDTH)
    {
        g_usHLWinHPos = 0;
    }
    else
    {
        g_usHLWinHPos = (_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2;
    }

    if(GET_MDOMAIN_OUTPUT_VHEIGHT() == _PANEL_DV_HEIGHT)
    {
        g_usHLWinVPos = 0;
    }
    else
    {
        g_usHLWinVPos = (_PANEL_DV_HEIGHT - GET_MDOMAIN_OUTPUT_VHEIGHT()) / 2;
    }

    switch(ucHLWinType)
    {
        case _HL_WIN_1:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() - _HL_WIN_BORDER_SIZE;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;

            break;

        case _HL_WIN_2:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 2;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;

            break;

        case _HL_WIN_3:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() - _HL_WIN_BORDER_SIZE;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() / 2;

            break;

        case _HL_WIN_4:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 2;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() / 2;
            g_usHLWinHPos = ((GET_MDOMAIN_OUTPUT_HWIDTH() - g_usHLWinHWidth) / 2) + ((_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2) - 1;
            g_usHLWinVPos = (GET_MDOMAIN_OUTPUT_VHEIGHT() - g_usHLWinVHeight) / 2 - 1;

            break;

        case _HL_WIN_5:

            g_usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 6;
            g_usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;
            g_usHLWinHPos = (GET_MDOMAIN_OUTPUT_HWIDTH() - g_usHLWinHWidth) / 2;

            ScalerTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);

            break;

        default:

            break;
    }

    ScalerColorHLWAdjust(g_usHLWinHPos, g_usHLWinHWidth, g_usHLWinVPos, g_usHLWinVHeight, _DB_APPLY_NONE);
*/
}

//--------------------------------------------------
// Description  : High Light Window Type5 Move
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinType5Move(void)
{
/*
    WORD usNonFullScreenOffset = 0;

    if(GET_MDOMAIN_OUTPUT_HWIDTH() == _PANEL_DH_WIDTH)
    {
        // Full screen
        usNonFullScreenOffset = 0;
    }
    else
    {
        // Non full screen
        usNonFullScreenOffset = (_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2;
    }

    if(g_bHLWinRLMove == _RIGHT)
    {
        g_usHLWinHPos++;

        if((GET_MDOMAIN_OUTPUT_HWIDTH() + usNonFullScreenOffset) <= (g_usHLWinHPos + g_usHLWinHWidth + _HL_WIN_BORDER_SIZE))
        {
            g_bHLWinRLMove = _LEFT;
            g_usHLWinHPos = (GET_MDOMAIN_OUTPUT_HWIDTH() + usNonFullScreenOffset) - (g_usHLWinHWidth + _HL_WIN_BORDER_SIZE);
        }
    }
    else // _LEFT
    {
        g_usHLWinHPos--;

        if(g_usHLWinHPos <= usNonFullScreenOffset)
        {
            g_bHLWinRLMove = _RIGHT;
            g_usHLWinHPos = usNonFullScreenOffset;
        }
    }

    ScalerColorHLWAdjust(g_usHLWinHPos, g_usHLWinHWidth, g_usHLWinVPos, g_usHLWinVHeight, _DB_APPLY_NO_POLLING);

    ScalerTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
*/
}

//--------------------------------------------------
// Description  : Adjust All High Light Window Effect Space
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHighLightWindowEffectSpace(void)
{
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
    ScalerColorHLWBRICTSAdjust(_BRI_CON_B_ON_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_DCC_FUNCTION == _ON)
    ScalerColorHLWDCCAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_GAMMA_FUNCTION == _ON)
    ScalerColorHLWOutputGammaAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
    ScalerColorHLWSRGBAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_IAPS_SUPPORT == _ON)
    ScalerColorHLWIAPSGainAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_ICM_SUPPORT == _ON)
    ScalerColorHLWICMAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if((_DCR_SUPPORT == _ON) || (_IAPS_SUPPORT == _ON))
    ScalerColorHLWDCRAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
    ScalerColorHLWUltraVividAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_YPEAKING_SUPPORT == _ON)
    ScalerColorHLWYpeakingAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    ScalerColorHLWPanelUniformityAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_PCM_FUNCTION == _ON)
    ScalerColorHLWPCMAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if(_RGB_3D_GAMMA == _ON)
    ScalerColorHLWRGB3DGammaAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
#endif
}
#endif // End of #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)

#if(_FREESYNC_OD_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set FREESYNC OD Measure
// Input Value  : Current DHtotal(pixel)/ Current Dclk(kHz)/ Target Measure VFreq(0.1Hz)
// Output Value : None
//--------------------------------------------------
void UserAdjustFREESYNCODMeasure(void)
{
    // Set Backlight
    UserAdjustBacklight(100);

    // Enable Backlight
    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

    // Disable OSD
    ScalerOsdDisableOsd();

    // Disable D-domain Pattern Gen.
    ScalerDDomainPatternGenEnable(_DISABLE);

    // According FREESYNC setting to set accurate Htotal/ Dclk
    ScalerMDomainFREESYNCODSetDisplayFormat(((WORD)_PANEL_DH_TOTAL), ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ), ((WORD)_PANEL_FREESYNC_MIN_FRAME_RATE));

    while(_TRUE)
    {
        ScalerDebug();
        ScalerDDomainFREESYNCODSetBackgroundGrayLevel();
    }
}
#endif


#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//--------------------------------------------------
// Description  : Set IR Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjusIR(void)
{
    ScalerIRHWModeDecoder(tIR_INITIAL_TABLE, GET_CURRENT_BANK_NUMBER());
}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
//--------------------------------------------------
// Description  : Set embedded DP switch status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustEmbeddedDpSwitch(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
    {
        if(GET_DP_EMBEDDED_SWITCH_SELECT() != _D0_INPUT_PORT)
        {
            SysSourceEmbeddedDpSwitch(_D0_INPUT_PORT);
        }
        return;
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
    {
        if(GET_DP_EMBEDDED_SWITCH_SELECT() != _D1_INPUT_PORT)
        {
            SysSourceEmbeddedDpSwitch(_D1_INPUT_PORT);
        }
        return;
    }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    if(ScalerSyncDpCableStatus(_D2_INPUT_PORT) == _TRUE)
    {
        if(GET_DP_EMBEDDED_SWITCH_SELECT() != _D2_INPUT_PORT)
        {
            SysSourceEmbeddedDpSwitch(_D2_INPUT_PORT);
        }
        return;
    }
#endif
}
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Pixel orbiting step as following
//  -2->
// ^    |
// |    3
// 1    |
// |    v
// < -0- <-7-
//      |     |
//      4     6
//      |     |
//      v -5->
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustPixelShifting(void)
{
#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
    BYTE ucPixelShift = 0;

    WORD usVdelay = 0;
    WORD usHdelay = 0;
    BYTE ucVstep = 2;
    BYTE ucHstep = 2;

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        ucVstep = (ucVstep + 1) & 0xFE;
    }
#endif

    ScalerGlobalWatchDog(_DISABLE);

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        usHdelay = ScalerVgaTopGetCaptureHDelay();
        usVdelay = ScalerVgaTopGetCaptureVDelay();
    }
    else
#endif
    {
        usHdelay = ScalerVgipGetCaptureHDelay();
        usVdelay = ScalerVgipGetCaptureVDelay();
    }

    for(ucPixelShift = 0; ucPixelShift < 8; ucPixelShift++)
    {
        ScalerTimerDelayXms(200);

        switch(ucPixelShift)
        {
            case 0: // _PIXEL0_TURN_LEFT:
            case 7: // _PIXEL1_TURN_LEFT:
                usHdelay += ucHstep;
                break;

            case 2: // _PIXEL0_TURN_RIGHT:
            case 5: // _PIXEL1_TURN_RIGHT:
                if(usHdelay >= ucHstep)
                {
                    usHdelay -= ucHstep;
                }
                else
                {
                    usHdelay = 0;
                }
                break;

            case 1: // _PIXEL0_TURN_UP:
            case 6: // _PIXEL1_TURN_UP:
                usVdelay += ucVstep;
                break;

            case 3: // _PIXEL0_TURN_DOWN:
            case 4: // _PIXEL1_TURN_DOWN:
                if(usVdelay >= ucVstep)
                {
                    usVdelay -= ucVstep;
                }
                else
                {
                    usVdelay = 0;
                }
                break;

            default:
                break;
        }

#if(_VGA_SUPPORT == _ON)
        if(SysSourceGetSourceType() == _SOURCE_VGA)
        {
            ScalerVgaTopSetCaptureHDelay(usHdelay);
            ScalerVgaTopSetCaptureVDelay(usVdelay);
            ScalerVgaTopDoubleBufferApply();
        }
        else
#endif
        {
            ScalerVgipSetCaptureHDelay(usHdelay);
            ScalerVgipSetCaptureVDelay(usVdelay);
            ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);
        }
    }

    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerGlobalWatchDog(_ENABLE);

#endif

#if(_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_MDOMAIN)
    BYTE ucPixelShift = 0;
    WORD usDHstart = ScalerMDomainGetDisplayTimingGenActiveRegionHStart();
    WORD usDHend = ScalerMDomainGetDisplayTimingGenActiveRegionHEnd();
    WORD usDVstart = ScalerMDomainGetDisplayTimingGenActiveRegionVStart();
    WORD usDVend = ScalerMDomainGetDisplayTimingGenActiveRegionVEnd();
    WORD usDVBGstart = GET_MDOMAIN_OUTPUT_VBSTART();
    WORD usDVBGend = GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT();
    WORD usDisplayHstart = usDHstart;
    WORD usDisplayVstart = usDVstart;

    // usDVBGstart/usDVBGend
    ScalerMDomainSetDisplayTimingGenBackgroundVStart(HIBYTE(usDVBGstart), LOBYTE(usDVBGstart), _DB_APPLY_NONE);
    ScalerMDomainSetDisplayTimingGenBackgroundVEnd(HIBYTE(usDVBGend), LOBYTE(usDVBGend), _DB_APPLY_NO_POLLING);

    // capture H start/end
    ScalerMDomainSetCaptureWindowHStart(HIBYTE(usDHstart), LOBYTE(usDHstart));
    ScalerMDomainSetCaptureWindowHEnd(HIBYTE(usDHend), LOBYTE(usDHend));
    // capture V start/end
    ScalerMDomainSetCaptureWindowVStart(HIBYTE(usDVstart), LOBYTE(usDVstart));
    ScalerMDomainSetCaptureWindowVEnd(HIBYTE(usDVend), LOBYTE(usDVend));

    ScalerMDomainSetCaptureWindowEnable(_ENABLE);

    for(ucPixelShift = 0; ucPixelShift < 8; ucPixelShift++)
    {
        ScalerTimerDelayXms(200);
        switch(ucPixelShift)
        {
            // H <-
            case 0: // _PIXEL0_TURN_LEFT:
                usDHend -= 1;
                usDisplayHstart -= 1;
                break;

            // V ^
            case 1: // _PIXEL0_TURN_UP:
                usDVstart += 1;
                usDVBGstart += 1;
                usDVBGend += 1;
                break;

            // H ->
            case 2: // _PIXEL0_TURN_RIGHT:
                usDHend += 1;
                usDisplayHstart += 1;
                break;

            // V v
            case 3: // _PIXEL0_TURN_DOWN:
                usDVstart -= 1;
                usDVBGstart -= 1;
                usDVBGend -= 1;
                break;

            // V v
            case 4: // _PIXEL1_TURN_DOWN:
                usDisplayVstart += 1;
                usDVstart += 1;
                break;

            // H ->
            case 5: // _PIXEL1_TURN_RIGHT:
                usDisplayHstart += 1;
                usDHstart += 1;
                break;

            // V ^
            case 6: // _PIXEL1_TURN_UP:
                usDisplayVstart -= 1;
                usDVstart -= 1;
                break;

            // H <-
            case 7: // _PIXEL1_TURN_LEFT:
                usDisplayHstart -= 1;
                usDHstart -= 1;
                break;

            default:
                break;
        }

        switch(ucPixelShift)
        {
            case 0: // _PIXEL0_TURN_LEFT:
            case 2: // _PIXEL0_TURN_RIGHT:
            case 5: // _PIXEL1_TURN_RIGHT:
            case 7: // _PIXEL1_TURN_LEFT:
                // Display H active start setting
                ScalerMDomainSetDisplayTimingGenActiveRegionHStart(HIBYTE(usDisplayHstart), LOBYTE(usDisplayHstart), _DB_APPLY_POLLING);
                // Capture window H start setting
                ScalerMDomainSetCaptureWindowHStart(HIBYTE(usDHstart), LOBYTE(usDHstart));
                // Capture window H end setting
                ScalerMDomainSetCaptureWindowHEnd(HIBYTE(usDHend), LOBYTE(usDHend));

                break;

            case 1: // _PIXEL0_TURN_UP:
            case 3: // _PIXEL0_TURN_DOWN:
            case 4: // _PIXEL1_TURN_DOWN:
            case 6: // _PIXEL1_TURN_UP:
                // Display V active start setting
                ScalerMDomainSetDisplayTimingGenActiveRegionVStart(HIBYTE(usDisplayVstart), LOBYTE(usDisplayVstart), _DB_APPLY_POLLING);
                // Capture window V start setting
                ScalerMDomainSetCaptureWindowVStart(HIBYTE(usDVstart), LOBYTE(usDVstart));
                // Display V background start setting
                ScalerMDomainSetDisplayTimingGenBackgroundVStart(HIBYTE(usDVBGstart), LOBYTE(usDVBGstart), _DB_APPLY_POLLING);
                // Display V background end setting
                ScalerMDomainSetDisplayTimingGenBackgroundVEnd(HIBYTE(usDVBGend), LOBYTE(usDVBGend), _DB_APPLY_POLLING);
                break;

            default:
                break;
        }
    }

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerMDomainSetCaptureWindowEnable(_DISABLE);
#endif
}
#endif

#if(_SDR_TO_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set SDRToHDR parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustSDRToHDR(bit bOn)
{
    if(bOn == _ON)
    {
#if(_CONTRAST_SUPPORT == _ON)
        ScalerColorContrastEnable(_FUNCTION_OFF);
#endif
        UserCommonAdjustSDRToHDR(tSDRTOHDR_INPUTGAMMA, tSDRTOHDR_ICM, tSDRTOHDR_DCC, GET_CURRENT_BANK_NUMBER());
    }
    else
    {
        UserAdjustColorEffectMode();
        OsdFuncColorPcmAdjust();
    }
}
#endif // End of #if(_SDR_TO_HDR_SUPPORT == _ON)

#if(_DCR_SUPPORT == _ON)
#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust DCR initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustDCRTHD(void)
{
    // Adjust DCR Threshold & Source
#if(_DCR_BIT_MODE == _DCR_GEN_1_0_10BIT)
    ScalerColorDCRAdjust(_DCR_THESHOLD1, _DCR_THESHOLD2, _MEASURE_AVERAGE);
#elif((_DCR_BIT_MODE == _DCR_GEN_0_0_8BIT) || (_DCR_BIT_MODE == _DCR_GEN_0_1_8BIT))
    ScalerColorDCRAdjust((_DCR_THESHOLD1 >> 2), (_DCR_THESHOLD2 >> 2), _MEASURE_AVERAGE);
#endif
}
#endif // End of #if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
#endif // End of #if(_DCR_SUPPORT == _ON)

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
//--------------------------------------------------
// Description  : User Control Type-C Port Controller Power
// Input Value  : ucSwitch --> Power Action
// Output Value : None
//--------------------------------------------------
void UserAjustTypeCPowerControl(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            //Switch On Port Controller Power By PCB Control
            PCB_PORT_CTRL_POW_RTD_USER(_PORT_CTRL_POWER_ON);
            CLR_TYPE_C_PORT_CTRL_POWER_OFF_FLG();

            break;

        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:

            if(GET_PCB_PORT_CTRL_POW_STATUS_RTD_USER() == _PORT_CTRL_POWER_OFF)
            {
                // Switch On Port Conroller Power By PCB Control
                PCB_PORT_CTRL_POW_RTD_USER(_PORT_CTRL_POWER_ON);
            }

            break;

        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_PS:

#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && ((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER )))
            if(SysSourceGetCableDetect(_D0_INPUT_PORT) == _FALSE)
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && ((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER )))
            if(SysSourceGetCableDetect(_D1_INPUT_PORT) == _FALSE)
#elif((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && ((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER )))
            if(SysSourceGetCableDetect(_D6_INPUT_PORT) == _FALSE)
#endif
            {
                // Switch Off Repeater Power By PCB Control
                PCB_PORT_CTRL_POW_RTD_USER(_PORT_CTRL_POWER_OFF);
                SET_TYPE_C_PORT_CTRL_POWER_OFF_FLG();
            }
            else
            {
                CLR_TYPE_C_PORT_CTRL_POWER_OFF_FLG();
            }

            break;

        default:

            break;
    }
}
#endif // End of #if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
#endif // End of #if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Switch Dp Version to 1.4, if HDR On
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHdrCheckDpVersion(WORD usHdrMode)
{
    // Switch Dp Version to 1.3, if HDR Function Support
    if(usHdrMode != _HDR10_MODE_OFF)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        if(GET_OSD_DP_D0_VERSION() <= _DP_VER_1_DOT_2)
        {
            SET_OSD_DP_D0_VERSION(_DP_VER_1_DOT_3);

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            UserCommonInterfaceDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
        }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        if(GET_OSD_DP_D1_VERSION() <= _DP_VER_1_DOT_2)
        {
            SET_OSD_DP_D1_VERSION(_DP_VER_1_DOT_3);

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            UserCommonInterfaceDpVersionSwitch(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
        }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        if(GET_OSD_DP_D2_VERSION() <= _DP_VER_1_DOT_2)
        {
            SET_OSD_DP_D2_VERSION(_DP_VER_1_DOT_3);

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            UserCommonInterfaceDpVersionSwitch(_D2_INPUT_PORT, UserInterfaceGetDPVersion(_D2_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
        }
#endif
    }
}
#endif // End of #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))

#if(_BACKLIGHT_SENSOR == _ON)
void UserAdjustSetSensorbacklightvalue(BYTE SenserBrightnessFlag)
{
    BYTE ucBacklightData;
    
    ucBacklightData = GET_OSD_BACKLIGHT();

#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    if(ucBacklightData >= _DEFAULT_BACKLIGHT)
    {
        ucBacklightData  = (float)(ucBacklightData-_DEFAULT_BACKLIGHT)*(GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE())-GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE()))/(100-_DEFAULT_BACKLIGHT)+GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE());
    }
    else
    {
        ucBacklightData  =(float)(ucBacklightData)*(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())-GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE()))/_DEFAULT_BACKLIGHT+GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE());
    }
#else
    if(ucBacklightData >= _DEFAULT_BACKLIGHT)
    {
        ucBacklightData  = (float)(ucBacklightData-_DEFAULT_BACKLIGHT)*(GET_FACTORY_BACKLIGHT_REG_MAX()-GET_FACTORY_BACKLIGHT_REG_MID())/(100-_DEFAULT_BACKLIGHT)+GET_FACTORY_BACKLIGHT_REG_MID();
    }
    else
    {
        ucBacklightData  =(float)(ucBacklightData)*(GET_FACTORY_BACKLIGHT_REG_MID()-GET_FACTORY_BACKLIGHT_REG_MIN())/_DEFAULT_BACKLIGHT+GET_FACTORY_BACKLIGHT_REG_MIN();
    }
#endif

    sensor_brightness_flag = SenserBrightnessFlag;
    g_stOtherUserData.Sensor_backlight_value = ucBacklightData*4;
    DebugMessageSystem("(g_stOtherUserData.Sensor_backlight_value ", g_stOtherUserData.Sensor_backlight_value);
    ScalerTimerReactiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_SAVE_OTHER_USER_DATA);    
}
#endif

#if(_HDMI_SPLITTER_1X2_EN == _ON)
void UserAdjust_HdmiSplitter_Init(void)
{
    BYTE SplitterData[2];
    SplitterData[0] = GET_1ST_DATA();
    SplitterData[1] = GET_2ND_DATA();
    if(_FAIL == UserCommonEepromIICWrite(HDMI_SPLITTER_1X2_ID, 0, 0, 2, SplitterData, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
    {
         DebugMessageSystem("HdmiSplitter Init Fail.",0);
    }
    
}

void UserAdjust_HdmiSplitter_SetData(BYTE Data1st,BYTE Data2nd)
{
    BYTE SplitterData[2];
    SplitterData[0] = Data1st;
    SplitterData[1] = Data2nd;
    if(_FAIL == UserCommonEepromIICWrite(HDMI_SPLITTER_1X2_ID, 0, 0, 2, SplitterData, _IIC_USER_SENSOR, _SW_IIC_PIN_GPIO, _WRITE_SIZE_8))
    {
         DebugMessageSystem("HdmiSplitter SetData Fail.",0);
    }
    
}
#endif

#endif//#if(_OSD_TYPE == _BEACON_OSD)
