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
// ID Code      : UserCommonGlobalDimming.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_GLOBAL_DIMMING__

#include "UserCommonInclude.h"

#if(_GLOBAL_DIMMING_SUPPORT == _ON)

#pragma OT(8)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GD_TRIGGER_VALUE                       1

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
WORD code tGDHDRToneMappingLv540[256] =
{
#include _GD_HDR_TONE_MAPPING_LV540
};

WORD code tGDHDR2084Lv[256] =
{
#include _GD_HDR_2084_LV
};

WORD code tGDSDRGamma22Lv[256] =
{
#include _GD_SDR_GAMMA_22_LV
};

WORD code tGDSDRGamma24Lv[256] =
{
#include _GD_SDR_GAMMA_24_LV
};

WORD code tGDSDRGamma26Lv[256] =
{
#include _GD_SDR_GAMMA_26_LV
};

WORD code tGDSDROGCCase1Lv[256] =
{
#include _GD_SDR_OGC_CASE_1_LV
};

WORD code tGDSDROGCCase2Lv[256] =
{
#include _GD_SDR_OGC_CASE_2_LV
};

WORD code tGDSDROGCCase3Lv[256] =
{
#include _GD_SDR_OGC_CASE_3_LV
};

WORD code tGDSDROGCCase4Lv[256] =
{
#include _GD_SDR_OGC_CASE_4_LV
};

WORD code tGDSDROGCCase5Lv[256] =
{
#include _GD_SDR_OGC_CASE_5_LV
};

WORD code tStepRTable[256] =
{
#include _GD_STEP_R_TABLE
};

#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
WORD code tGDPWMLUT[_GD_PANEL_PWM_MAX + 1] =
{
#include _GD_PWM_LUT_TABLE
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usGDLastDCRMaxY = 255;
WORD g_usGDDCRToLV;
WORD g_usGDApplyLV;
WORD g_usGDLastApplyLV = _GD_PANEL_LV_MAX;
WORD g_usGDApplyPWM;
WORD g_usLastApplyPWM = _GD_PANEL_PWM_MAX;
WORD g_usGDLastDeltaPWM = _GD_PANEL_PWM_MAX;
WORD g_usGDR;
WORD g_usLastGainValue = 0x200;
BYTE g_pucSRGBMatrixHalf[24];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonGlobalDimmingHandler(void);
EnumGDStatus UserCommonGlobalDimmingGetEnableStatus(void);
void UserCommonGlobalDimmingAdjust(void);
void UserCommonGlobalDimmingDCRToLv(WORD usDCRMaxY, WORD *pusDCRToLV);
void UserCommonGlobalDimmingStepToTarget(WORD *pusApplyLv, WORD *pusTargetLv, WORD *pusLastApplyLv, WORD usDCRResult, WORD *pusLastDCRResult);
void UserCommonGlobalDimmingCalPWMValue(WORD usApplyLv);
void UserCommonGlobalDimmingInitialSetting(bit bEn);
void UserCommonGlobalDimmingSetGainValue(void);
void UserCommonGlobalDimmingEnable(bit bEn);
void UserCommonGlobalDimmingSetPWMValue(WORD usPWM);
#if(_GLOBAL_DIMMING_LOW_SENSITIVITY_SUPPORT == _ON)
WORD UserCommonGlobalDimmingLowSensitivityTatget(WORD usDCRMaxY, WORD usLastDCRMaxY);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonGlobalDimmingHandler(void)
{
    if(UserCommonGlobalDimmingGetEnableStatus() == _GD_ENABLE)
    {
        UserCommonGlobalDimmingAdjust();
    }
}

//--------------------------------------------------
// Description  : Judge Global Dimming ON or OFF
// Input Value  : None
// Output Value : GD_ENABLE OR GD_DISABLE
//--------------------------------------------------
EnumGDStatus UserCommonGlobalDimmingGetEnableStatus(void)
{
#if(_LOCAL_DIMMING_SUPPORT == _ON)
    if(UserInterfaceGetLocalDimmingStatus() == _LD_ENABLE)
    {
        return _GD_DISABLE;
    }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(GET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING() == _ON)
    {
        return _GD_DISABLE;
    }
#endif

    if((GET_ON_LINE_CALIBRATION_STATUS() == _CALIBRATION_OFF) &&
       (UserInterfaceGetGlobalDimmingStatus() == _GD_ENABLE))
    {
#if(_HDR10_SUPPORT == _ON)
        if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
        {
            return _GD_ENABLE;
        }
        else
#endif
        {
            if(UserInterfaceSDROCCOGCMode() == _SDR_CALIBRATION_BY_OGC_TOOL)
            {
                return _GD_ENABLE;
            }
            else
            {
                return _GD_DISABLE;
            }
        }
    }

    return _GD_DISABLE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonGlobalDimmingAdjust(void)
{
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_0)
    WORD usDCRMaxY = ScalerColorDCRReadResult(_DCR_Y_MAX_VAL);
#elif(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
    WORD usDCRMaxY = 0;
    WORD usMaxR = ScalerColorDCRReadResult(_DCR_HIGH_LV_VAL_R);
    WORD usMaxG = ScalerColorDCRReadResult(_DCR_HIGH_LV_VAL_G);
    WORD usMaxB = ScalerColorDCRReadResult(_DCR_HIGH_LV_VAL_B);
    usDCRMaxY = MAXOF(usMaxR, usMaxG);
    usDCRMaxY = MAXOF(usDCRMaxY, usMaxB);
#endif


    usDCRMaxY = (usDCRMaxY >> 2);
#if(_GLOBAL_DIMMING_LOW_SENSITIVITY_SUPPORT == _ON)
    usDCRMaxY = UserCommonGlobalDimmingLowSensitivityTatget(usDCRMaxY, g_usGDLastDCRMaxY);
#endif
    UserCommonGlobalDimmingDCRToLv(usDCRMaxY, &g_usGDDCRToLV);

    UserCommonGlobalDimmingStepToTarget(&g_usGDApplyLV, &g_usGDDCRToLV, &g_usGDLastApplyLV, usDCRMaxY, &g_usGDLastDCRMaxY);
    UserCommonGlobalDimmingSetGainValue();
    UserCommonGlobalDimmingCalPWMValue(g_usGDApplyLV);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonGlobalDimmingDCRToLv(WORD usDCRMaxY, WORD *pusDCRToLV)
{
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
    {
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
        WORD usLightEnhanceCode = 0;
        BYTE ucGainValue = UserInterfaceHDRGetHDR10LightEnhanceGain();

        if(ucGainValue > 160)
        {
            ucGainValue = 160;
        }
        else if(ucGainValue < 100)
        {
            ucGainValue = 100;
        }

        usLightEnhanceCode = (usDCRMaxY * ucGainValue / 100);
        if(usLightEnhanceCode > 255)
        {
            usLightEnhanceCode = 255;
        }
        usDCRMaxY = usLightEnhanceCode;
#endif

        if(UserCommonHDRGetHDR10LvType() == _HDR10_MAX_MASTERING_LV_TYPE_NOTM)
        {
            *pusDCRToLV = tGDHDR2084Lv[usDCRMaxY];
        }
        else
        {
            *pusDCRToLV = tGDHDRToneMappingLv540[usDCRMaxY];
        }
    }
    else
#endif
    {
        if(UserInterfaceGetSDRPCMMode() != _SDR_NONE_OCC)
        {
            switch(UserInterfaceGetSDRPCMMode())
            {
                case _SDR_SRGB:
                case _SDR_ADOBE_RGB:

                    *pusDCRToLV = tGDSDRGamma22Lv[usDCRMaxY];
                    break;

                case _SDR_EBU_MODE:
                case _SDR_REC_709:

                    *pusDCRToLV = tGDSDRGamma24Lv[usDCRMaxY];
                    break;

                case _SDR_DCI_P3:

                    *pusDCRToLV = tGDSDRGamma26Lv[usDCRMaxY];
                    break;

                default:
                    break;
            }
        }
        else if(UserInterfaceGetSDROGCMode() != _SDR_NONE_OGC)
        {
            switch(UserInterfaceGetSDROGCMode())
            {
                case _SDR_OGC_CASE_1:
                    *pusDCRToLV = tGDSDROGCCase1Lv[usDCRMaxY];
                    break;

                case _SDR_OGC_CASE_2:

                    *pusDCRToLV = tGDSDROGCCase2Lv[usDCRMaxY];
                    break;

                case _SDR_OGC_CASE_3:

                    *pusDCRToLV = tGDSDROGCCase3Lv[usDCRMaxY];
                    break;

                case _SDR_OGC_CASE_4:

                    *pusDCRToLV = tGDSDROGCCase4Lv[usDCRMaxY];
                    break;

                case _SDR_OGC_CASE_5:

                    *pusDCRToLV = tGDSDROGCCase5Lv[usDCRMaxY];
                    break;

                default:
                    break;
            }
        }
        else
        {
            *pusDCRToLV = tGDSDRGamma22Lv[usDCRMaxY];
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonGlobalDimmingStepToTarget(WORD *pusApplyLv, WORD *pusTargetLv, WORD *pusLastApplyLv, WORD usDCRResult, WORD *pusLastDCRResult)
{
    if(usDCRResult >= *pusLastDCRResult)
    {
        if((*pusTargetLv - *pusLastApplyLv) == (tGDHDRToneMappingLv540[255] - tGDHDRToneMappingLv540[0]))
        {
            g_usGDR = 1024;
        }
        else
        {
            g_usGDR = tStepRTable[usDCRResult - *pusLastDCRResult];
        }
    }
    else
    {
        g_usGDR = tStepRTable[(*pusLastDCRResult) - usDCRResult];
    }

    *pusApplyLv = ((((DWORD)g_usGDR * *pusTargetLv) + ((DWORD)(1024 - g_usGDR) * *pusLastApplyLv)) + 512) / 1024;

    if(*pusApplyLv == *pusLastApplyLv)
    {
        if((*pusApplyLv > *pusTargetLv) && (*pusApplyLv != 0))
        {
            *pusApplyLv = *pusApplyLv - 1;
        }
        else if(*pusApplyLv < *pusTargetLv)
        {
            *pusApplyLv = *pusApplyLv + 1;
        }
    }

    *pusLastApplyLv = *pusApplyLv;
    *pusLastDCRResult = usDCRResult;
}

//--------------------------------------------------
// Description  : Set driver PWM
// Input Value  : Panel Apply PWM
// Output Value : void
//--------------------------------------------------
void UserCommonGlobalDimmingCalPWMValue(WORD usApplyLv)
{
    WORD usPWM = _GD_PANEL_PWM_MAX;
    WORD usMaxDelPWM = _GD_PANEL_PWM_MAX;

    usPWM = ((DWORD)(usApplyLv) * _GD_PANEL_PWM_MAX) / _GD_PANEL_LV_MAX;

    if(usPWM > _GD_PANEL_PWM_MAX)
    {
        usPWM = _GD_PANEL_PWM_MAX;
    }
    else if(usPWM < _GD_PANEL_PWM_MIN)
    {
        usPWM = _GD_PANEL_PWM_MIN;
    }

    usMaxDelPWM = ((((DWORD)g_usGDR * usPWM) + ((DWORD)(1024 - g_usGDR) * g_usLastApplyPWM))) / 1024;

    if(usMaxDelPWM == g_usLastApplyPWM)
    {
        if((usMaxDelPWM > usPWM) && (usMaxDelPWM > _GD_PANEL_PWM_MIN))
        {
            usMaxDelPWM = usMaxDelPWM - 1;
        }
        else if(usMaxDelPWM < usPWM)
        {
            usMaxDelPWM = usMaxDelPWM + 1;
        }
    }

    if(usPWM > g_usLastApplyPWM)
    {
        if(usPWM > usMaxDelPWM)
        {
            usPWM = usMaxDelPWM;
        }
    }
    else
    {
        if(usPWM < usMaxDelPWM)
        {
            usPWM = usMaxDelPWM;
        }
    }

    g_usLastApplyPWM = usPWM;

#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
    UserCommonGlobalDimmingSetPWMValue(tGDPWMLUT[usPWM]);
#else
    UserCommonGlobalDimmingSetPWMValue(usPWM);
#endif

    DebugMessageHDR("usPWM", usPWM);
}

//--------------------------------------------------
// Description  : Global dimming initial setting
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonGlobalDimmingInitialSetting(bit bEn)
{
    BYTE pucSRGBMatrixOriginal[18] = {0};
    SWORD shSRGBValueOriginal = 0;
    SWORD shDiagoanlValueHalf = 0;
    BYTE ucI = 0;
    BYTE ucDecimalNum = 0;
    BYTE ucShiftNum = 0;

    // SRGB
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
    {
        WORD usHDRColorMatrixFlashAddress = UserCommonHDRGetHDR10ColorMatrix();
        UserCommonFlashRead(_OGC_FLASH_BANK, usHDRColorMatrixFlashAddress, 18, pucSRGBMatrixOriginal);
        ucDecimalNum = 11;
    }
    else
#endif
    {
        if(UserInterfaceGetSDRPCMMode() != _SDR_NONE_OCC)
        {
            switch(UserInterfaceGetSDRPCMMode())
            {
                case _SDR_SRGB:
                    UserCommonFlashRead(_OGC_FLASH_BANK, _OCC_SRGBMATRIX_ADDRESS, 18, pucSRGBMatrixOriginal);
                    ucDecimalNum = 12;
                    break;

                case _SDR_ADOBE_RGB:
                    UserCommonFlashRead(_OGC_FLASH_BANK, _OCC_ADOBEMATRIX_ADDRESS, 18, pucSRGBMatrixOriginal);
                    ucDecimalNum = 12;
                    break;

                case _SDR_EBU_MODE:
                    UserCommonFlashRead(_OGC_FLASH_BANK, _OCC_EBU_ADDRESS, 18, pucSRGBMatrixOriginal);
                    ucDecimalNum = 12;
                    break;

                case _SDR_REC_709:
                    UserCommonFlashRead(_OGC_FLASH_BANK, _OCC_REC709_ADDRESS, 18, pucSRGBMatrixOriginal);
                    ucDecimalNum = 12;
                    break;

                case _SDR_DCI_P3:
                    UserCommonFlashRead(_OGC_FLASH_BANK, _OCC_DCIP3_ADDRESS, 18, pucSRGBMatrixOriginal);
                    ucDecimalNum = 12;
                    break;

                default:
                    break;
            }
        }
        else if(UserInterfaceGetSDROGCMode() != _SDR_NONE_OGC)
        {
            ucDecimalNum = 9;
        }
    }

    ucShiftNum = (ucDecimalNum - 9);

    if(bEn == _ENABLE)
    {
        for(ucI = 0; ucI < 9; ucI++)
        {
            SWORD shValue = (((WORD)(pucSRGBMatrixOriginal[2 * ucI] & 0x01) << 15) |
                             ((WORD)pucSRGBMatrixOriginal[(2 * ucI) + 1] << 7) |
                             ((pucSRGBMatrixOriginal[2 * ucI] & 0xE0) >> 1));
            shValue >>= 4;

            shSRGBValueOriginal = (shValue + (ucShiftNum >> 1)) >> ucShiftNum;

            if((ucI % 4) == 0)
            {
                shDiagoanlValueHalf = ((shSRGBValueOriginal + 0x201) >> 1) - 0x200;
            }
            else
            {
                shDiagoanlValueHalf = (shSRGBValueOriginal + 1) >> 1;
            }
            g_pucSRGBMatrixHalf[2 * ucI] = ((shDiagoanlValueHalf & 0x07) << 5) | ((shDiagoanlValueHalf >> 11) & 0x01);
            g_pucSRGBMatrixHalf[2 * ucI + 1] = (shDiagoanlValueHalf >> 3) & 0xFF;
        }
        ScalerColorSRGBAdjust(g_pucSRGBMatrixHalf, _SRGB_3_BIT_SHIFT_LEFT);
    }
    else
    {
        if(ucDecimalNum == 11)
        {
            ScalerColorSRGBAdjust(pucSRGBMatrixOriginal, _SRGB_1_BIT_SHIFT_LEFT);
        }
        else if(ucDecimalNum == 12)
        {
            ScalerColorSRGBAdjust(pucSRGBMatrixOriginal, _SRGB_0_BIT_SHIFT_LEFT);
        }
        else if(ucDecimalNum == 9)
        {
            ScalerColorSRGBAdjust(pucSRGBMatrixOriginal, _SRGB_3_BIT_SHIFT_LEFT);
        }
    }
}


//--------------------------------------------------
// Description  :Apply Gain Value
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonGlobalDimmingSetGainValue(void)
{
    WORD usGainValue = 0;
    WORD usApplyGainValue = 0;
    BYTE pucSRGBMatrix[24] = {0};
    BYTE ucI = 0;

    usGainValue = (((DWORD)_GD_PANEL_LV_MAX << 9) / g_usGDApplyLV);

    usApplyGainValue = ((((DWORD)g_usGDR * usGainValue) + ((DWORD)g_usLastGainValue * (1024 - g_usGDR))) + 512) / 1024;

    if(usApplyGainValue == g_usLastGainValue)
    {
        if(usApplyGainValue < usGainValue)
        {
            usApplyGainValue = usApplyGainValue + 1;
        }
        else if((usApplyGainValue > usGainValue) && (usApplyGainValue > 512))
        {
            usApplyGainValue = usApplyGainValue - 1;
        }
    }

    usApplyGainValue = (usApplyGainValue > _GLOBAL_DIMMING_MAX_GAIN) ? _GLOBAL_DIMMING_MAX_GAIN : usApplyGainValue;
    usApplyGainValue = (usApplyGainValue < _GLOBAL_DIMMING_MIN_GAIN) ? _GLOBAL_DIMMING_MIN_GAIN : usApplyGainValue;

    DebugMessageHDR("usApplyGainValue", usApplyGainValue);

    g_usLastGainValue = usApplyGainValue;

    for(ucI = 0; ucI < 9; ucI++)
    {
        SDWORD lSRGBApplylValue = 0;
        SWORD shValue = (((WORD)(g_pucSRGBMatrixHalf[2 * ucI] & 0x01) << 15) |
                         ((WORD)g_pucSRGBMatrixHalf[(2 * ucI) + 1] << 7) |
                         ((g_pucSRGBMatrixHalf[2 * ucI] & 0xE0) >> 1));
        shValue >>= 4;

        if((ucI % 4) == 0)
        {
            lSRGBApplylValue = (((SDWORD)shValue * (SDWORD)usApplyGainValue + 0x100) >> 9) +
                               ((((SDWORD)usApplyGainValue * 0x200) + 0x100) >> 9) - 0x200;
        }
        else
        {
            lSRGBApplylValue = ((SDWORD)shValue * (SDWORD)usApplyGainValue + 0x100) >> 9;
        }

        if(lSRGBApplylValue > _GLOBAL_DIMMING_SRGB_MAX)
        {
            DebugMessageHDR("lSRGBApplylValue", lSRGBApplylValue);
            lSRGBApplylValue = _GLOBAL_DIMMING_SRGB_MAX;
        }

        pucSRGBMatrix[2 * ucI] = ((lSRGBApplylValue & 0x07) << 5) | ((lSRGBApplylValue >> 11) & 0x01);
        pucSRGBMatrix[2 * ucI + 1] = (lSRGBApplylValue >> 3) & 0xFF;
    }

    ScalerColorSRGBAdjust(pucSRGBMatrix, _SRGB_3_BIT_SHIFT_LEFT);
}

//--------------------------------------------------
// Description  : Enable Global Dimming Function in OSD
// Input Value  : _Enable or _Disable
// Output Value : void
//--------------------------------------------------
void UserCommonGlobalDimmingEnable(bit bEn)
{
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
    ScalerColorSRGBEnable(_FUNCTION_OFF);
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);

    UserCommonGlobalDimmingInitialSetting(bEn);

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
    {
        WORD usOCCGammaTableArray = ((bEn == _ON) ? _DIMMING_OCC_GAMMA10_ADDRESS : _OCC_GAMMA10_ADDRESS);

        ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + usOCCGammaTableArray, _OGC_FLASH_BANK);

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorOutputGammaEnable(_FUNCTION_ON);
        ScalerColorSRGBEnable(_FUNCTION_ON);
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
    }
    else
#endif
    {
        UserInterfaceGlobalDimmingAdjustPCM();
    }
}

//--------------------------------------------------
// Description  : Set PWM value
// Input Value  : PWM value, 0~2048
// Output Value : void
//--------------------------------------------------
void UserCommonGlobalDimmingSetPWMValue(WORD usPWM)
{
    UserInterfaceGlobalDimmingAdjustPWM(usPWM);
}

#if(_GLOBAL_DIMMING_LOW_SENSITIVITY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set PWM value
// Input Value  : PWM value, 0~2048
// Output Value : void
//--------------------------------------------------
WORD UserCommonGlobalDimmingLowSensitivityTatget(WORD usDCRMaxY, WORD usLastDCRMaxY)
{
    if(abs(usDCRMaxY - usLastDCRMaxY) > _GD_TRIGGER_VALUE)
    {
        return usDCRMaxY;
    }

    return usLastDCRMaxY;
}
#endif

#endif // End of #if(_Global_DIMMING_SUPPORT == _ON)

