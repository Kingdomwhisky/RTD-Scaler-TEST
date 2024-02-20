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
// ID Code      : NoneUserAdjust.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST__
#define __USER_PANEL__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _NONE_OSD)

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


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


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

//-------------------------------------------------------
// SDRtoHDR
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

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//----------------------------------------------------------------------------
// Kernel Related Function
//----------------------------------------------------------------------------
//--------------------------------------------------
// Description  : Adjust backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustBacklight(WORD usBacklight)
{
    usBacklight = usBacklight;

#if(_BACKLIGHT_PWM_INVERSE == _ON)
    usBacklight = _BACKLIGHT_MAX - usBacklight;
#endif

    // Adjust backlight by changing PWM duty
    PCB_BACKLIGHT_PWM(usBacklight);
}

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get the Mapping of Edid index of Function Application
// Input Value  : ucInputPort
// Output Value : Edid Index
//--------------------------------------------------
EnumEdidSelection UserAdjustGetDpEdidIndex(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return _EDID_INDEX_0;
}
#endif

//----------------------------------------------------------------------------
// Not Kernel Related Function
//----------------------------------------------------------------------------
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
    ucVolume = ucVolume;

#if(_TRANSLATOR_SUPPORT == _OFF)
    ScalerAudioDigitalAdjustVolume(UserAdjustAudioVolumeMapping(ucVolume));
#endif
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
    if((ucColorEffect != _COLOREFFECT_STANDARD) && (ucColorEffect != _COLOREFFECT_USER))
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
    if((ucColorEffect != _COLOREFFECT_STANDARD) && (ucColorEffect != _COLOREFFECT_USER))
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
    if((ucColorEffect != _COLOREFFECT_STANDARD) && (ucColorEffect != _COLOREFFECT_USER))
    {
        ScalerColorSCMLoadTable(tSCM_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_SCM_SUPPORT == _ON)


#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
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

#if(_SIX_COLOR_SUPPORT == _ON)
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
    WORD pusData[3] = {0};

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // 10-bit Panel
        pusData[0] = UserCommonAdjust10bitPanelCompensate(usContrast);
        pusData[1] = UserCommonAdjust10bitPanelCompensate(usContrast);
        pusData[2] = UserCommonAdjust10bitPanelCompensate(usContrast);
    }
#if(_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)
    else if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
    {
        pusData[0] = UserCommonAdjust6bitPanelCompensate(usContrast);
        pusData[1] = UserCommonAdjust6bitPanelCompensate(usContrast);
        pusData[2] = UserCommonAdjust6bitPanelCompensate(usContrast);
    }
#endif
    else
    {
        pusData[0] = usContrast;
        pusData[1] = usContrast;
        pusData[2] = usContrast;
    }

    ScalerColorContrastAdjust(_CONTRAST_COEF_A, pusData);
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
    WORD pusData[3] = {0};
    pusData[0] = usBrightness;
    pusData[1] = usBrightness;
    pusData[2] = usBrightness;

    ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusData);
    ScalerColorBrightnessEnable(_FUNCTION_ON);
}
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
//--------------------------------------------------
// Description  : Adjust Global Hue Saturation
// Input Value  : Hue and Saturation
// Output Value : None
//--------------------------------------------------
void UserAdjustGlobalHueSat(SWORD shHue, WORD usSat)
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
    ScalerODLoadLUT(tOD_TABLE[0], GET_CURRENT_BANK_NUMBER(), _OD_LUT_MODE);
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
//        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
//
//        if(ucHLWinType == _HL_WIN_OFF)
//        {
//            return;
//        }
//
//        if(GET_MDOMAIN_OUTPUT_HWIDTH() == _PANEL_DH_WIDTH)
//        {
//            usHLWinHPos = 0;
//        }
//        else
//        {
//            usHLWinHPos = (_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2;
//        }
//
//        if(GET_MDOMAIN_OUTPUT_VHEIGHT() == _PANEL_DV_HEIGHT)
//        {
//            usHLWinVPos = 0;
//        }
//        else
//        {
//            usHLWinVPos = (_PANEL_DV_HEIGHT - GET_MDOMAIN_OUTPUT_VHEIGHT()) / 2;
//        }
//
//        switch(ucHLWinType)
//        {
//            case _HL_WIN_1:
//
//                usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() - _HL_WIN_BORDER_SIZE;
//                usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;
//
//                break;
//
//            case _HL_WIN_2:
//
//                usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 2;
//                usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;
//
//                break;
//
//            case _HL_WIN_3:
//
//                usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() - _HL_WIN_BORDER_SIZE;
//                usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() / 2;
//
//                break;
//
//            case _HL_WIN_4:
//
//                usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 2;
//                usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() / 2;
//                usHLWinHPos = ((GET_MDOMAIN_OUTPUT_HWIDTH() - usHLWinHWidth) / 2) + ((_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2) - 1 ;
//                usHLWinVPos = (GET_MDOMAIN_OUTPUT_VHEIGHT() - usHLWinVHeight) / 2 - 1;
//
//                break;
//
//            case _HL_WIN_5:
//
//                usHLWinHWidth = GET_MDOMAIN_OUTPUT_HWIDTH() / 6;
//                usHLWinVHeight = GET_MDOMAIN_OUTPUT_VHEIGHT() - _HL_WIN_BORDER_SIZE;
//                usHLWinHPos = (GET_MDOMAIN_OUTPUT_HWIDTH() - usHLWinHWidth) / 2;
//
//                ScalerTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
//
//                break;
//
//            default:
//
//                break;
//        }
//
//        ScalerColorHLWAdjust(usHLWinHPos, usHLWinHWidth, usHLWinVPos, usHLWinVHeight, _DB_APPLY_NONE);
}

//--------------------------------------------------
// Description  : High Light Window Type5 Move
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinType5Move(void)
{
//        WORD uiNonFullScreenOffset;
//
//        if(GET_MDOMAIN_OUTPUT_HWIDTH() == _PANEL_DH_WIDTH)//Full screen
//        {
//            uiNonFullScreenOffset = 0;
//        }
//        else//Non full screen
//        {
//            uiNonFullScreenOffset = (_PANEL_DH_WIDTH - GET_MDOMAIN_OUTPUT_HWIDTH()) / 2;
//        }
//
//        if(bHLWinRLMove == _RIGHT)
//        {
//            usHLWinHPos++;
//
//            if((GET_MDOMAIN_OUTPUT_HWIDTH() + uiNonFullScreenOffset) <= (usHLWinHPos + usHLWinHWidth + _HL_WIN_BORDER_SIZE))
//            {
//                bHLWinRLMove = _LEFT;
//                usHLWinHPos = (GET_MDOMAIN_OUTPUT_HWIDTH() + uiNonFullScreenOffset) - (usHLWinHWidth + _HL_WIN_BORDER_SIZE);
//            }
//        }
//        else // _LEFT
//        {
//            usHLWinHPos--;
//
//            if(usHLWinHPos <= uiNonFullScreenOffset)
//            {
//                bHLWinRLMove = _RIGHT;
//                usHLWinHPos = uiNonFullScreenOffset;
//            }
//        }
//
//        ScalerColorHLWAdjust(usHLWinHPos, usHLWinHWidth, usHLWinVPos, usHLWinVHeight, _DB_APPLY_NONE);
//
//        ScalerTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
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

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
        ScalerColorSRGBEnable(_FUNCTION_OFF);
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
        UserAdjustPCM(_PCM_OSD_SRGB);

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
        ScalerColorSRGBEnable(_FUNCTION_ON);
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
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

#endif//#if(_OSD_TYPE == _NONE_OSD)
