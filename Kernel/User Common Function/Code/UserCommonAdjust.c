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
// ID Code      : UserCommonAdjust.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_ADJUST__

#include "UserCommonInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

#if(_VGA_SUPPORT == _ON)

#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
//----------------------------------------------------------------------------------------------------
// TABLE DIGITAL FILTER ENHANCE PHASE MODE
//----------------------------------------------------------------------------------------------------
#include _DIGITAL_FILTER_ENHANCE_PHASE_TABLE
#endif

#if(_RINGING_FILTER_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// TABLE RINGING FILTER OFFSET COEFFICIENT
//----------------------------------------------------------------------------------------------------
#include _RINGING_FILTER_TABLE
#endif

#endif  // End of #if(_VGA_SUPPORT == _ON)


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

#if(_UNIFORMITY_SUPPORT == _ON)

BYTE code tUniformityType[] =
{
    _UNIFORMITY_1ST_TABLE_LEVEL,
    _UNIFORMITY_2ND_TABLE_LEVEL,
    _UNIFORMITY_3RD_TABLE_LEVEL,
    _UNIFORMITY_4TH_TABLE_LEVEL,
    _UNIFORMITY_5TH_TABLE_LEVEL,
    _UNIFORMITY_6TH_TABLE_LEVEL,
};

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// TABLE Uniformity Offset and Decay Address
//----------------------------------------------------------------------------------------------------

BYTE code tUNIFORMITY_OSD_TYPE_OFFSET_ENABLE_INDEX[] =
{
    _UNIFORMITY_OFFSET_TYPE0,
    _UNIFORMITY_OFFSET_TYPE1,
    _UNIFORMITY_OFFSET_TYPE2,
    _UNIFORMITY_OFFSET_TYPE3,
    _UNIFORMITY_OFFSET_TYPE4,
    _UNIFORMITY_OFFSET_TYPE5,
};
#endif // End of #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#endif // End of #if(_UNIFORMITY_SUPPORT == _ON)

#if(_CUSTOMER == _CUS_TOSHIBA)
BYTE g_ucPictureChange = 0;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************

#if(_VGA_SUPPORT == _ON)
WORD UserCommonAdjustGetAdcClockRange(BYTE ucPar);
void UserCommonAdjustClock(WORD usUserIHTotal);
void UserCommonAdjustPhase(BYTE ucPhase);

#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
void UserCommonAdjustDigitalFilterEnhancePhase(void);
#endif

#if(_RINGING_FILTER_SUPPORT == _ON)
void UserCommonAdjustRingingFilter(void);
#endif
#endif

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
void UserCommonAdjustEmbeddedDpSwitch(void);
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
WORD UserCommonAdjustGetHPositionRange(BYTE ucPar);
WORD UserCommonAdjustGetHPositionHBiasValue(void);
WORD UserCommonAdjustGetVPositionRange(BYTE ucPar);
WORD UserCommonAdjustGetVPositionVBiasValue(void);
void UserCommonAdjustHPosition(BYTE ucUserHPosition);
void UserCommonAdjustVPosition(BYTE ucUserVPosition);
#endif

BYTE UserCommonAdjustRealValueToPercent(WORD usRealValue, WORD usMax, WORD usMin, WORD usCenter);
WORD UserCommonAdjustPercentToRealValue(BYTE ucPercentValue, WORD usMax, WORD usMin, WORD usCenter);

#if(_CUSTOMER == _CUS_TOSHIBA)
void Set_1600_1024_State(bit state);
#endif

#if(_OVERSCAN_SUPPORT == _ON)
void UserCommonAdjustOverScan(void);
#endif

#if(_UNDERSCAN_SUPPORT == _ON)
void UserCommonAdjustUnderScan(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
void UserCommonAdjustAspectRatio(void);
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
void UserCommonAdjustRotationInputSize(void);
void UserCommonAdjustRotationDisplaySize(void);
#endif

#if(_I_DITHER_SUPPORT == _ON)
void UserCommonAdjustIDither(void);
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
void UserCommonAdjustRGBQuantizationRange(void);
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
void UserCommonAdjustUltraVivid(EnumFunctionOnOFF enumFunctionOnOFF, EnumColorSpace enumColorFormat, EnumDBApply enumDBApply);
#endif

#if(_D_DITHER_SUPPORT == _ON)
void UserCommonAdjustDDither(void);
#endif

#if(_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)
WORD UserCommonAdjust6bitPanelCompensate(WORD usData);
#endif

// 10  bit Panel
WORD UserCommonAdjust10bitPanelCompensate(WORD usData);

#if(_SHARPNESS_SUPPORT == _ON)
void UserCommonAdjustSharpness(EnumSourceSearchPort enumSourceSearchPort);
#endif

#if(_FREEZE_SUPPORT == _ON)
void UserCommonAdjustDisplayFreeze(bit bEn);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
BYTE UserCommonAdjustGetUniformityType(BYTE ucIndex);
void UserCommonAdjustPanelUniformity(EnumUniformityTypeSelect enumUniformityType, EnumUniformityModeSelect enumUniformityMode);
BYTE UserCommonAdjustPanelUniformityGainBank(EnumUniformityTypeSelect enumUniformityType);
WORD UserCommonAdjustPanelUniformityGainAddr(EnumUniformityTypeSelect enumUniformityType);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
BYTE UserCommonAdjustPanelUniformityOffsetBank(EnumUniformityTypeSelect enumUniformityType);
WORD UserCommonAdjustPanelUniformityOffsetAddr(EnumUniformityTypeSelect enumUniformityType);
WORD UserCommonAdjustPanelUniformityDecayAddr(EnumUniformityTypeSelect enumUniformityType);
#endif
#endif

#if(_OGC_SUPPORT == _ON)
void UserCommonAdjustOGCColorTempGain(BYTE ucColorTemp, BYTE ucGammaMode, BYTE *pucData, EnumOGCModeSelect enumOGCModeSelect);
#endif

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
BYTE UserCommonAdjustOGCBank(EnumOGCTypeSelect enumOGCTypeSelect, EnumOGCModeSelect enumOGCModeSelect);
BYTE *UserCommonAdjustOGCAddr(EnumOGCTypeSelect enumOGCTypeSelect, EnumOGCModeSelect enumOGCModeSelect);
#endif

#if(_PCM_FUNCTION == _ON)
void UserCommonAdjustPCM(EnumPCMType enumPCMMode, BYTE *pucIGammaTableArray, BYTE *pucOGammaTableArray, BYTE *pucColorMatrixArray, BYTE ucPCMBankNum, WORD usLength);
#endif

#if(_GAMMA_FUNCTION == _ON)
void UserCommonAdjustGamma(BYTE *pucOGammaTableArray, BYTE ucGammaBankNum);
void UserCommonAdjustGammaRegionEnable(EnumFunctionOnOFF enumOn);
#endif

#if(_SDR_TO_HDR_SUPPORT == _ON)
void UserCommonAdjustSDRToHDR(BYTE *pucIGammaTableArray, BYTE *pucICMTableArray, BYTE *pucDCCTableArray, BYTE ucSDRtoHDRBank);
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
void UserCommonAdjustGlobalHueSat(SWORD shHue, WORD usSat);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check if the ADC clock (IHTotal) is out of range. Range = (BackPorch + FrontPorch) * 2 / 5 .
// Input Value  : usClock   --> ADC Clock (IHTotal)
// Output Value : Return _TRUE if not out of range
//--------------------------------------------------
WORD UserCommonAdjustGetAdcClockRange(BYTE ucPar)
{
    WORD usDelta1 = 0;
    WORD usDelta2 = 0;
    WORD usDelta = 0;

    usDelta1 = GET_ADC_LIMIT_CLOCK() - g_stVGAModeUserData.usCenterClock;

    usDelta2 = g_stVGAModeUserData.usCenterClock - ScalerVgaTopGetCaptureHStartPosition() - ScalerVgaTopGetCaptureHWidth();

    usDelta = (usDelta1 < usDelta2) ? usDelta1 : usDelta2;

    if(ucPar == _GET_CLOCKRANGE_MAX)
    {
        if(usDelta < _CLOCK_BIAS)
        {
            return (g_stVGAModeUserData.usCenterClock + usDelta);
        }
        else
        {
            return (g_stVGAModeUserData.usCenterClock + _CLOCK_BIAS);
        }
    }
    else if(ucPar == _GET_CLOCKRANGE_MIN)
    {
        if(usDelta < _CLOCK_BIAS)
        {
            return (g_stVGAModeUserData.usCenterClock - usDelta);
        }
        else
        {
            return (g_stVGAModeUserData.usCenterClock - _CLOCK_BIAS);
        }
    }

    return (g_stVGAModeUserData.usCenterClock);
}

//--------------------------------------------------
// Description  : Adjust clock.
// Input Value  : usUserIHTotal --> OSD Value(0~100) or Real Value
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustClock(WORD usUserIHTotal)
{
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)

    WORD usClockRangeMax = 0;
    WORD usClockRangeMin = 0;

    usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
    usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
    usUserIHTotal = UserCommonAdjustPercentToRealValue((BYTE)usUserIHTotal, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

#endif

    ScalerGlobalWatchDog(_DISABLE);

    ScalerAPLLFastLockAdjust(usUserIHTotal);

    ScalerGlobalWatchDog(_ENABLE);
}

//--------------------------------------------------
// Description  : Adjust phase
// Input Value  : ucPhase --> phase value
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustPhase(BYTE ucPhase)
{
    ucPhase = UserCommonAdjustPercentToRealValue(ucPhase, _ADJUST_PHASE_MAX, _ADJUST_PHASE_MIN, _ADJUST_PHASE_CENTER);

    ScalerGlobalWatchDog(_DISABLE);

    ScalerPLLSetPhase(ucPhase, UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVFREQ));

    ScalerGlobalWatchDog(_ENABLE);
}

#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
//--------------------------------------------------
// Description  : Adjust Digital Filter Enhanced Phase Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustDigitalFilterEnhancePhase(void)
{
    BYTE ucI = 0;
    BYTE ucTemp = 0;
    BYTE ucSpan = 0;
    SWORD shTemp = 0;
    WORD usPixelRate = (ScalerSyncGetInputPixelClk() + 5) / 10;

    if(usPixelRate <= tDF_ENHANCE_PHASE_SETTING[0])
    {
        pData[0] = tDF_ENHANCE_PHASE_SETTING[1];
        pData[1] = tDF_ENHANCE_PHASE_SETTING[2];
        pData[2] = tDF_ENHANCE_PHASE_SETTING[3];
    }
    else if(usPixelRate >= tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 4])
    {
        pData[0] = tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 3];
        pData[1] = tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 2];
        pData[2] = tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 1];
    }
    else
    {
        for(ucI = 0; tDF_ENHANCE_PHASE_SETTING[ucI * 4] < usPixelRate; ucI++) {}

        ucI--;

        ucTemp = usPixelRate - tDF_ENHANCE_PHASE_SETTING[ucI * 4];
        ucSpan = tDF_ENHANCE_PHASE_SETTING[(ucI + 1) * 4] - tDF_ENHANCE_PHASE_SETTING[ucI * 4];

        shTemp = tDF_ENHANCE_PHASE_SETTING[((ucI + 1) * 4) + 1] - tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 1];
        pData[0] = tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 1] + (SWORD)ucTemp * shTemp / ucSpan;

        shTemp = tDF_ENHANCE_PHASE_SETTING[((ucI + 1) * 4) + 2] - tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 2];
        pData[1] = tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 2] + (SWORD)ucTemp * shTemp / ucSpan;

        shTemp = tDF_ENHANCE_PHASE_SETTING[((ucI + 1) * 4) + 3] - tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 3];
        pData[2] = tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 3] + (SWORD)ucTemp * shTemp / ucSpan;
    }

    ScalerColorDigitalFilterEnhancePhaseAdjust(pData);
}
#endif // End of #if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)


#if(_RINGING_FILTER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust Ringing Filter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustRingingFilter(void)
{
    BYTE ucI = 0;
    BYTE ucTemp = 0;
    BYTE ucSpan = 0;
    SWORD shTemp = 0;
    WORD usPixelRate = (ScalerSyncGetInputPixelClk() + 5) / 10;

    if(usPixelRate <= tRF_OFFSET_COEF_SETTING[0])
    {
        pData[0] = tRF_OFFSET_COEF_SETTING[1];
    }
    else if(usPixelRate >= tRF_OFFSET_COEF_SETTING[sizeof(tRF_OFFSET_COEF_SETTING) - 2])
    {
        pData[0] = tRF_OFFSET_COEF_SETTING[sizeof(tRF_OFFSET_COEF_SETTING) - 1];
    }
    else
    {
        for(ucI = 0; tRF_OFFSET_COEF_SETTING[ucI * 2] < usPixelRate; ucI++) {}

        ucI--;

        ucTemp = usPixelRate - tRF_OFFSET_COEF_SETTING[ucI * 2];
        ucSpan = tRF_OFFSET_COEF_SETTING[(ucI + 1) * 2] - tRF_OFFSET_COEF_SETTING[ucI * 2];

        shTemp = tRF_OFFSET_COEF_SETTING[((ucI + 1) * 2) + 1] - tRF_OFFSET_COEF_SETTING[(ucI * 2) + 1];
        pData[0] = tRF_OFFSET_COEF_SETTING[(ucI * 2) + 1] + (SWORD)ucTemp * shTemp / ucSpan;
    }

    ScalerColorRingingFilterAdjust(pData);
}
#endif // End of #if(_RINGING_FILTER_SUPPORT == _ON)
#endif // End of #if(_VGA_SUPPORT == _ON)

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
//--------------------------------------------------
// Description  : Check embedded DP switch status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustEmbeddedDpSwitch(void)
{
    // Proceed if not DP
    if(SysSourceGetSourceType() == _SOURCE_DP)
    {
        return;
    }
    else
    {
        // Proceed when in steady states
        switch(SysModeGetModeState())
        {
            case _MODE_STATUS_ACTIVE:
            case _MODE_STATUS_NOSUPPORT:
                break;

            default:
                return;
        }
    }

    UserInterfaceEmbeddedDpSwitch();
}
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Get Max or Min H-Position
// Input Value  : ucPar--> Max or Min paramater
// Output Value : Max or Min H-Position
//--------------------------------------------------
WORD UserCommonAdjustGetHPositionRange(BYTE ucPar)
{
    WORD usDeltaIHWidthOverScan = 0;
    WORD usIHWidth = 0;

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        usIHWidth = UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IHWIDTH);

#if((_OVERSCAN_SUPPORT == _ON) && (_VGA_CAPTURE_SUPPORT == _OFF))
        if(UserInterfaceGetOverScanStatus() == _TRUE)
        {
            if(usIHWidth >= ScalerVgaTopGetCaptureHWidth())
            {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
                if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
                {
                    usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgaTopGetCaptureHWidth()));
                }
                else
#endif
                {
                    usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgaTopGetCaptureHWidth()) / 2);
                }
            }
        }
#endif
    }
    else
#endif
    {
        usIHWidth = GET_INPUT_TIMING_HWIDTH();

#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus() == _TRUE)
        {
            if(usIHWidth >= ScalerVgipGetCaptureHWidth())
            {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
                if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
                {
                    usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgipGetCaptureHWidth()));
                }
                else
#endif
                {
                    usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgipGetCaptureHWidth()) / 2);
                }
            }
        }
#endif
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_OVERSCAN_SUPPORT == _ON)
    if(UserInterfaceGetOverScanStatus() == _FALSE)
#endif
    {
        if((ScalerRotationCheckStatus() == _TRUE) && (GET_ROT_DISP_SIZE() == _ROT_PIXEL_BY_PIXEL))
        {
            if((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270))
            {
                if(_PANEL_DV_HEIGHT < usIHWidth)
                {
                    usDeltaIHWidthOverScan = (usIHWidth - _PANEL_DV_HEIGHT);
                }
            }
            else if(GET_ROT_TYPE() == _ROT_CW180)
            {
                // Calculate / Set H
                if(_PANEL_DH_WIDTH < usIHWidth)
                {
                    usDeltaIHWidthOverScan = (usIHWidth - _PANEL_DH_WIDTH);
                }
            }
        }
    }
#endif

#if(_CUSTOMER == _CUS_TOSHIBA)
#if(TOSHIBA_DC_POWER == _OFF)
    if(GET_OSD_ASPECT_RATIO_TYPE() == _ASPECT_RATIO_VMAXIMAGE)
    {
        if((GET_INPUT_TIMING_HWIDTH() == 1600) && (GET_INPUT_TIMING_VHEIGHT() == 900) )
        {
            usDeltaIHWidthOverScan = 350;//ScalerVgipGetCaptureVHeight();  // TEST
        }
    }
#endif
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        if(ucPar == _GET_HPOSITIONRANGE_MAX)
        {
            return (g_stVGAModeUserData.usCenterHPosition + usDeltaIHWidthOverScan + _HPOSITION_BIAS);
        }
        else if(ucPar == _GET_HPOSITIONRANGE_MIN)
        {
            return (g_stVGAModeUserData.usCenterHPosition + usDeltaIHWidthOverScan - _HPOSITION_BIAS);
        }
        else
        {
            return (g_stVGAModeUserData.usCenterHPosition);
        }
    }
    else
#endif
    {
        if(ucPar == _GET_HPOSITIONRANGE_MAX)
        {
            return (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan + _HPOSITION_BIAS);
        }
        else if(ucPar == _GET_HPOSITIONRANGE_MIN)
        {
            return (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan - _HPOSITION_BIAS);
        }
        else
        {
            return (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan);
        }
    }
}

//--------------------------------------------------
// Description  : Get HPosition H Bias Value
// Input Value  : None
// Output Value : H Bias Value
//--------------------------------------------------
WORD UserCommonAdjustGetHPositionHBiasValue(void)
{
    WORD usHBias = 0;
    WORD usDeltaIHWidthOverScan = 0;
    WORD usIHWidth = 0;

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        usIHWidth = UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IHWIDTH);

#if((_OVERSCAN_SUPPORT == _ON) && (_VGA_CAPTURE_SUPPORT == _OFF))
        if(UserInterfaceGetOverScanStatus() == _TRUE)
        {
            if(usIHWidth >= ScalerVgaTopGetCaptureHWidth())
            {
                usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgaTopGetCaptureHWidth()) / 2);
            }
        }
#endif

        usHBias = ((g_stVGAModeUserData.usCenterHPosition - ScalerVgaTopGetCaptureHStartPosition()) <= (_MAX_H_POSITION_RANGE / 2)) ?
                  (g_stVGAModeUserData.usCenterHPosition - ScalerVgaTopGetCaptureHStartPosition() - 1) : (_MAX_H_POSITION_RANGE / 2);
    }
    else
#endif
    {
        usIHWidth = GET_INPUT_TIMING_HWIDTH();

#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus() == _TRUE)
        {
            if(usIHWidth >= ScalerVgipGetCaptureHWidth())
            {
                usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgipGetCaptureHWidth()) / 2);
            }
        }
#endif

        usHBias = ((GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan - ScalerVgipGetCaptureHStartPosition()) <= (_MAX_H_POSITION_RANGE / 2)) ?
                  (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan - ScalerVgipGetCaptureHStartPosition() - 1) : (_MAX_H_POSITION_RANGE / 2);
    }

    return usHBias;
}

//--------------------------------------------------
// Description  : Get Max or Min V-Position
// Input Value  : ucPar--> Max or Min paramater
// Output Value : Max or Min V-Position
//--------------------------------------------------
WORD UserCommonAdjustGetVPositionRange(BYTE ucPar)
{
    WORD usDeltaIVHeightOverScan = 0;
    WORD usDeltaIVHeightUnderScan = 0;
    WORD usIVHeight = 0;

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        usIVHeight = UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVHEIGHT);

#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus() == _TRUE)
        {
            if(usIVHeight >= ScalerVgaTopGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgaTopGetCaptureVHeight()) / 2);
            }
        }
#endif
    }
    else
#endif
    {
        usIVHeight = GET_INPUT_TIMING_VHEIGHT();

#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus() == _TRUE)
        {
            if(usIVHeight >= ScalerVgipGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgipGetCaptureVHeight()) / 2);
            }
        }
#endif
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_OVERSCAN_SUPPORT == _ON)
    if(UserInterfaceGetOverScanStatus() == _FALSE)
#endif
    {
        if((ScalerRotationCheckStatus() == _TRUE) && (GET_ROT_DISP_SIZE() == _ROT_PIXEL_BY_PIXEL))
        {
            if((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270))
            {
                // Calculate / Set V
                if(_PANEL_DH_WIDTH < usIVHeight)
                {
                    usDeltaIVHeightOverScan = ((usIVHeight - _PANEL_DH_WIDTH) / 2);
                }
            }
            else if(GET_ROT_TYPE() == _ROT_CW180)
            {
                if(_PANEL_DV_HEIGHT < usIVHeight)
                {
                    usDeltaIVHeightOverScan = ((usIVHeight - _PANEL_DV_HEIGHT) / 2);
                }
            }
        }
    }
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        if(usIVHeight <= ScalerVgaTopGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgaTopGetCaptureVHeight() - usIVHeight) / 2);
        }

        if(ucPar == _GET_VPOSITIONRANGE_MAX)
        {
            return (g_stVGAModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan + _VPOSITION_BIAS);
        }
        else if(ucPar == _GET_VPOSITIONRANGE_MIN)
        {
            return (g_stVGAModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - _VPOSITION_BIAS);
        }
        else
        {
            return (g_stVGAModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan);
        }
    }
    else
#endif
    {
        if(usIVHeight <= ScalerVgipGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgipGetCaptureVHeight() - usIVHeight) / 2);
        }

#if(_CUSTOMER == _CUS_TOSHIBA)
#if(TOSHIBA_DC_POWER == _OFF)       
        if((GET_OSD_ASPECT_RATIO_TYPE() == _ASPECT_RATIO_1280x1024) ||(GET_OSD_ASPECT_RATIO_TYPE() == _ASPECT_RATIO_FULL))  
        {
             if((GET_INPUT_TIMING_HWIDTH() == 1600) && (GET_INPUT_TIMING_VHEIGHT() == 1024) )
             {
                 if((GET_1600_1024_COM() == _ON) || (GET_OSD_ASPECT_RATIO_TYPE() == _ASPECT_RATIO_FULL))
                 {
                       usDeltaIVHeightOverScan = 0;//ScalerVgipGetCaptureVHeight();  // TEST
                 }
             }
        }
    
        if(GET_OSD_ASPECT_RATIO_TYPE() == _ASPECT_RATIO_VMAXIMAGE)
        {
             if((GET_INPUT_TIMING_HWIDTH() == 1600) && (GET_INPUT_TIMING_VHEIGHT() == 900) )
             {
                       usDeltaIVHeightOverScan = 144;//ScalerVgipGetCaptureVHeight();  // TEST
             }        
        }
#endif
#endif

        if(ucPar == _GET_VPOSITIONRANGE_MAX)
        {
            return (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan + _VPOSITION_BIAS);
        }
        else if(ucPar == _GET_VPOSITIONRANGE_MIN)
        {
            return (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - _VPOSITION_BIAS);
        }
        else
        {
            return (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan);
        }
    }
}

//--------------------------------------------------
// Description  : Get VPosition V Bias Value
// Input Value  : None
// Output Value : V Bias Value
//--------------------------------------------------
WORD UserCommonAdjustGetVPositionVBiasValue(void)
{
    WORD usVBias = 0;
    WORD usDeltaIVHeightOverScan = 0;
    WORD usDeltaIVHeightUnderScan = 0;
    WORD usIVHeight = 0;

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        usIVHeight = UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVHEIGHT);

#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus() == _TRUE)
        {
            if(usIVHeight >= ScalerVgaTopGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgaTopGetCaptureVHeight()) / 2);
            }
        }
#endif

        if(usIVHeight <= ScalerVgaTopGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgaTopGetCaptureVHeight() - usIVHeight) / 2);
        }

        usVBias = ((g_stVGAModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgaTopGetCaptureVStartPosition()) < (_MAX_V_POSITION_RANGE / 2)) ?
                  (g_stVGAModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgaTopGetCaptureVStartPosition()) : (_MAX_V_POSITION_RANGE / 2);

        return usVBias;
    }
    else
#endif
    {
        usIVHeight = GET_INPUT_TIMING_VHEIGHT();

#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus() == _TRUE)
        {
            if(usIVHeight >= ScalerVgipGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgipGetCaptureVHeight()) / 2);
            }
        }
#endif

        if(usIVHeight <= ScalerVgipGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgipGetCaptureVHeight() - usIVHeight) / 2);
        }

        usVBias = ((GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgipGetCaptureVStartPosition()) < (_MAX_V_POSITION_RANGE / 2)) ?
                  (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgipGetCaptureVStartPosition()) : (_MAX_V_POSITION_RANGE / 2);

        return usVBias;
    }
}

//--------------------------------------------------
// Description  : Adjust picture position.
// Input Value  : ucUserHPosition --> Current percentage of H position associate to OSD bar
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustHPosition(BYTE ucUserHPosition)
{
    WORD usTargetIHStart = 0;
    WORD usHPositionRangeMax = 0;
    WORD usHPositionRangeMin = 0;
    SWORD shHDelay = 0;

    usHPositionRangeMax = UserCommonAdjustGetHPositionRange(_GET_HPOSITIONRANGE_MAX);
    usHPositionRangeMin = UserCommonAdjustGetHPositionRange(_GET_HPOSITIONRANGE_MIN);

    usTargetIHStart = UserCommonAdjustPercentToRealValue((100 - ucUserHPosition), usHPositionRangeMax, usHPositionRangeMin, (((usHPositionRangeMax - usHPositionRangeMin) / 2) + usHPositionRangeMin));

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        // Disable Wach dog
        ScalerGlobalWatchDog(_DISABLE);

        shHDelay = (SWORD)usTargetIHStart - (SWORD)ScalerVgaTopGetCaptureHStartPosition();

        if((ScalerColorGetColorSpace() == _COLOR_SPACE_YCBCR422) || (ScalerColorGetColorSpace() == _COLOR_SPACE_YCBCR420))
        {
            shHDelay += ((shHDelay - ScalerVgaTopGetCaptureHDelay()) % 2);
        }

        // Can't set IH delay to 0 by HW limit
        shHDelay = (shHDelay < 1) ? 1 : shHDelay;

        // Compensate IHS delay
        ScalerVgaTopSetCaptureHDelay(shHDelay);

        // Apply the above setting by setting Double Buffer Ready in VGIP
        ScalerVgaTopDoubleBufferApply();

        // Enable Wach dog
        ScalerGlobalWatchDog(_ENABLE);
    }
    else
#endif
    {
        if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
        {
            // Disable Wach dog
            ScalerGlobalWatchDog(_DISABLE);

            shHDelay = (SWORD)usTargetIHStart - (SWORD)ScalerVgipGetCaptureHStartPosition();

            if((ScalerColorGetColorSpace() == _COLOR_SPACE_YCBCR422) || (ScalerColorGetColorSpace() == _COLOR_SPACE_YCBCR420))
            {
                shHDelay += ((shHDelay - ScalerVgipGetCaptureHDelay()) % 2);
            }

            // Can't set IH delay to 0 by HW limit
            shHDelay = (shHDelay < 1) ? 1 : shHDelay;

            // Compensate IHS delay
            ScalerVgipSetCaptureHDelay(shHDelay);

            // Apply the above setting by setting Double Buffer Ready in VGIP
            ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);

            // Enable Wach dog
            ScalerGlobalWatchDog(_ENABLE);
        }
    }
}

//--------------------------------------------------
// Description  : Adjust picture position.
// Input Value  : ucUserVPosition --> Current percentage of V position associate to OSD bar
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustVPosition(BYTE ucUserVPosition)
{
    WORD usTargetIVStart = 0;
    WORD usVDelayAdjustDeltaLimit = 0;
    WORD usVPositionRangeMax = 0;
    WORD usVPositionRangeMin = 0;
    SWORD shVDelay = 0;
    BYTE ucTimeoutCounter = 0;

    usVPositionRangeMax = UserCommonAdjustGetVPositionRange(_GET_VPOSITIONRANGE_MAX);
    usVPositionRangeMin = UserCommonAdjustGetVPositionRange(_GET_VPOSITIONRANGE_MIN);

    usTargetIVStart = UserCommonAdjustPercentToRealValue(ucUserVPosition, usVPositionRangeMax, usVPositionRangeMin, (((usVPositionRangeMax - usVPositionRangeMin) / 2) + usVPositionRangeMin));

#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        // Disable Wach dog
        ScalerGlobalWatchDog(_DISABLE);

        shVDelay = (SWORD)usTargetIVStart - (SWORD)ScalerVgaTopGetCaptureVStartPosition();

        shVDelay = (shVDelay < 0) ? 0 : shVDelay;

        // Get current V adjust limit
        usVDelayAdjustDeltaLimit = ScalerMDomainGetVerticalAdjustLimit(_SOURCE_VGA);

        ucTimeoutCounter = (abs(shVDelay - ScalerVgaTopGetCaptureVDelay()) / usVDelayAdjustDeltaLimit) + 1;

        do
        {
            if(shVDelay > ScalerVgaTopGetCaptureVDelay())
            {
                ScalerVgaTopSetCaptureVDelay(shVDelay);
            }
            else
            {
                if((ScalerVgaTopGetCaptureVDelay() - shVDelay) <= usVDelayAdjustDeltaLimit)
                {
                    ScalerVgaTopSetCaptureVDelay(shVDelay);
                }
                else
                {
                    ScalerVgaTopSetCaptureVDelay(ScalerVgaTopGetCaptureVDelay() - usVDelayAdjustDeltaLimit);
                }
            }

            ScalerVgaTopDoubleBufferApply();

            ucTimeoutCounter--;
        }
        while((shVDelay != ScalerVgaTopGetCaptureVDelay()) && (ucTimeoutCounter > 0));

        // VGA Top capture adjust need wait one full ivs time
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);

        // Enable Wach dog
        ScalerGlobalWatchDog(_ENABLE);
    }
    else
#endif
    {
        if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
        {
            // Disable Wach dog
            ScalerGlobalWatchDog(_DISABLE);

            shVDelay = (SWORD)usTargetIVStart - (SWORD)ScalerVgipGetCaptureVStartPosition();

            shVDelay = (shVDelay < 0) ? 0 : shVDelay;

            // Get current V adjust limit
            usVDelayAdjustDeltaLimit = ScalerMDomainGetVerticalAdjustLimit(SysSourceGetSourceType());

            ucTimeoutCounter = (abs(shVDelay - ScalerVgipGetCaptureVDelay()) / usVDelayAdjustDeltaLimit) + 1;

            do
            {
                if(shVDelay > ScalerVgipGetCaptureVDelay())
                {
                    ScalerVgipSetCaptureVDelay(shVDelay);
                }
                else
                {
                    if((ScalerVgipGetCaptureVDelay() - shVDelay) <= usVDelayAdjustDeltaLimit)
                    {
                        ScalerVgipSetCaptureVDelay(shVDelay);
                    }
                    else
                    {
                        ScalerVgipSetCaptureVDelay(ScalerVgipGetCaptureVDelay() - usVDelayAdjustDeltaLimit);
                    }
                }

                ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);

                ucTimeoutCounter--;
            }
            while((shVDelay != ScalerVgipGetCaptureVDelay()) && (ucTimeoutCounter > 0));

            ScalerTimerWaitForEvent(_EVENT_IVS);

            // Enable Wach dog
            ScalerGlobalWatchDog(_ENABLE);
        }
    }
}
#endif // End of #if(_TRANSLATOR_SUPPORT == _OFF)

//--------------------------------------------------
// Description  :  Calculate value to percent for input range for 2 Sectors
// Input Value  :  usRealValue --> input real value
//                 usMax       --> the max value
//                 usMin       --> the min value
//                 usCenter    --> the Center Value
// Output Value :  Percent
//--------------------------------------------------
BYTE UserCommonAdjustRealValueToPercent(WORD usRealValue, WORD usMax, WORD usMin, WORD usCenter)
{
    WORD usTemp = 0;
    usRealValue = MINOF(usRealValue, usMax);
    usRealValue = MAXOF(usRealValue, usMin);

    if((usMax <= usMin) || (usCenter <= usMin) || (usCenter >= usMax))
    {
        usTemp = 0;
    }
    else
    {
        if(usRealValue < usCenter)
        {
            usTemp = (((DWORD)(usRealValue - usMin) * 10000) / (usCenter - usMin)) / 2;
        }
        else if(usRealValue > usCenter)
        {
            usTemp = (((DWORD)(usRealValue - usCenter) * 10000) / (usMax - usCenter)) / 2 + 5000;
        }
        else
        {
            return 50;
        }
    }

    if((usTemp % 100) > 49)
    {
        usTemp = usTemp + 100;
    }

    usTemp = usTemp / 100;

    return ((BYTE)usTemp);
}

//--------------------------------------------------
// Description  :  Calculate percent to real value for input range for 2 Sectors
// Input Value  :  ucPercentValue --> input percent value
//                 usMax          --> the max value
//                 usMin          --> the min value
//                 usCenter       --> the Center Value
// Output Value :  Real value
//--------------------------------------------------
WORD UserCommonAdjustPercentToRealValue(BYTE ucPercentValue, WORD usMax, WORD usMin, WORD usCenter)
{
    DWORD ulTemp = 0;

    ucPercentValue = MINOF(100, ucPercentValue);

    if(ucPercentValue > 50)
    {
        ulTemp = (((DWORD)(ucPercentValue - 50) * (usMax - usCenter) * 10) / 50);
    }
    else if(ucPercentValue < 50)
    {
        ulTemp = (((DWORD)ucPercentValue * (usCenter - usMin) * 10) / 50);
    }
    else
    {
        return usCenter;
    }

    if((ulTemp % 10) > 5)
    {
        ulTemp = ulTemp + 10;
    }

    if(ucPercentValue > 50)
    {
        return (WORD)((ulTemp / 10) + usCenter);
    }
    else
    {
        return (WORD)((ulTemp / 10) + usMin); // <= 50
    }
}

#if(_CUSTOMER == _CUS_TOSHIBA)
void Set_1600_1024_State(bit state)
{
    if(state == _ON)
        SET_1600_1024_COM();
    else
        CLR_1600_1024_COM();
}
#endif

#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Overscan
// Input Value  : Current Input Timing
// Output Value : Modified Input Timing
//--------------------------------------------------
void UserCommonAdjustOverScan(void)
{
    BYTE ucDelta = 0;

    if(UserInterfaceGetOverScanStatus() == _FALSE)
    {
        return;
    }

#if(_CUSTOMER == _CUS_TOSHIBA)
#if(TOSHIBA_DC_POWER == _OFF)
    if(GET_OSD_ASPECT_RATIO_TYPE() == _ASPECT_RATIO_1280x1024) 
    {
        if((GET_INPUT_TIMING_HWIDTH() == 1600) && (GET_INPUT_TIMING_VHEIGHT() == 1024))
        {
            if(GET_1600_1024_COM() == _ON)
            {
                 SET_MDOMAIN_INPUT_VHEIGHT(900);    

            }
           else
           {
                 SET_MDOMAIN_INPUT_VHEIGHT(1024);    
           }
       }
    }
     if(GET_OSD_ASPECT_RATIO_TYPE() == _ASPECT_RATIO_FULL) 
    {
        if((GET_INPUT_TIMING_HWIDTH() == 1600) && (GET_INPUT_TIMING_VHEIGHT() == 1024))
        {

                 SET_MDOMAIN_INPUT_VHEIGHT(900);    

       }
    }

    if(GET_OSD_ASPECT_RATIO_TYPE() == _ASPECT_RATIO_VMAXIMAGE) 
    {
       if((GET_INPUT_TIMING_HWIDTH() == 1600) && (GET_INPUT_TIMING_VHEIGHT() == 900))
       {
               SET_MDOMAIN_INPUT_VHEIGHT(598);    
               SET_MDOMAIN_INPUT_HWIDTH(900);
        }
    }
#endif
#else
    // Modify Over Scanned H
    ucDelta = (BYTE)((DWORD)GET_MDOMAIN_INPUT_HWIDTH() * _OVERSCAN_H_RATIO / 1000);

    // Let Adjusted Value be 2's multiple
    ucDelta += ucDelta % 2;

    SET_MDOMAIN_INPUT_HSTART(GET_MDOMAIN_INPUT_HSTART() + ucDelta);
    SET_MDOMAIN_INPUT_HWIDTH(GET_MDOMAIN_INPUT_HWIDTH() - 2 * ucDelta);

    // Modify Over Scanned V
    ucDelta = (BYTE)((DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * _OVERSCAN_V_RATIO / 1000);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        // Let Adjusted Value be 2's multiple under E/O mode
        ucDelta += ucDelta % 2;
    }
#endif

    SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() + ucDelta);
    SET_MDOMAIN_INPUT_VHEIGHT(GET_MDOMAIN_INPUT_VHEIGHT() - 2 * ucDelta);
#endif
}
#endif  // End of #if(_OVERSCAN_SUPPORT == _ON)

#if(_UNDERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Underscan
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustUnderScan(void)
{
    if(UserInterfaceAdjustUnderScan() == _FALSE)
    {
        return;
    }

    if(GET_MDOMAIN_INPUT_VHEIGHT() < GET_UNDERSCAN_VHEIGHT())
    {
        // Adjust M-domain Vstart for underscan; Default center-positioned
        WORD usVdiff = (GET_UNDERSCAN_VHEIGHT() - GET_MDOMAIN_INPUT_VHEIGHT()) / 2;

        if(GET_MDOMAIN_INPUT_VSTART() > (usVdiff + ScalerIDomainVgipGetVCaptureStartMinValue()))
        {
            SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() - usVdiff);
        }
        else
        {
            SET_MDOMAIN_INPUT_VSTART(ScalerIDomainVgipGetVCaptureStartMinValue());
        }

        SET_MDOMAIN_INPUT_VHEIGHT(GET_UNDERSCAN_VHEIGHT());
    }
}
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)

void UserAdjustZoomRatio(WORD ucWidth, WORD ucHeight)
{

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    ScalerMDomainAspectOriginMode(_TRUE);
#endif
    // Consider Panel Height and target Height
    if(GET_MDOMAIN_OUTPUT_VHEIGHT() > ucHeight)
    {
        // Double V height for interlaced timing

        PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_VHEIGHT() - ucHeight;
        PDATA_WORD(0) &= 0xFFFC; // V start should be even
        SET_MDOMAIN_OUTPUT_VHEIGHT(ucHeight);       
        SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + (PDATA_WORD(0) / 2));
    }
    
    // Consider Panel Width and target Width
    if(GET_MDOMAIN_OUTPUT_HWIDTH() > ucWidth)
    {
        PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_HWIDTH() - ucWidth;
        PDATA_WORD(0) &= 0xFFFC; // H start should be even
        SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + (PDATA_WORD(0) / 2));
        SET_MDOMAIN_OUTPUT_HWIDTH(ucWidth);
    }

}


//--------------------------------------------------
// Description  : Modify Display Timing For Aspect Ratio
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonAdjustAspectRatio(void)
{
    WORD usHRatio = 0x0000;
    WORD usVRatio = 0x0000;

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    // No aspect ratio allowed in rotation 90/270
    if((ScalerRotationCheckStatus() == _TRUE) &&
       ((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270)))
    {
        return;
    }
#endif
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
    SET_ASPECT_RATIO_MIN_DVH(0);
#endif

    switch(UserInterfaceGetAspectRatioType())
    {
        case _ASPECT_RATIO_FULL:

        default:

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
            ScalerMDomainAspectOriginMode(_FALSE);
#endif
            break;

        case _ASPECT_RATIO_FIXED:

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
            ScalerMDomainAspectOriginMode(_FALSE);
#endif

            UserInterfaceGetAspectRatio(&usHRatio, &usVRatio);

            // Calculate H Width
            PDATA_WORD(0) = (DWORD)GET_MDOMAIN_OUTPUT_VHEIGHT() * usHRatio / usVRatio;

            // H Width Should be 4x
            PDATA_WORD(0) &= 0xFFFC;

            if(PDATA_WORD(0) > GET_MDOMAIN_OUTPUT_HWIDTH())
            {
                // Calculate V Height
                PDATA_WORD(0) = (DWORD)GET_MDOMAIN_OUTPUT_HWIDTH() * usVRatio / usHRatio;

                // V Height Should be 4x
                PDATA_WORD(0) &= 0xFFFC;

                // Set V Start, V Height
                SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + ((GET_MDOMAIN_OUTPUT_VHEIGHT() - PDATA_WORD(0)) / 2));
                SET_MDOMAIN_OUTPUT_VHEIGHT(PDATA_WORD(0));
            }
            else if(PDATA_WORD(0) < GET_MDOMAIN_OUTPUT_HWIDTH())
            {
                // Calculate H Start
                PDATA_WORD(1) = GET_MDOMAIN_OUTPUT_HSTART() + ((GET_MDOMAIN_OUTPUT_HWIDTH() - PDATA_WORD(0)) / 2);

                // Set H Start, H Width
                SET_MDOMAIN_OUTPUT_HSTART(PDATA_WORD(1));
                SET_MDOMAIN_OUTPUT_HWIDTH(PDATA_WORD(0));
            }

            break;

        case _ASPECT_RATIO_1280x960:       
            UserAdjustZoomRatio(1280,960);
            break;

        case _ASPECT_RATIO_17Inch_Full:       
            UserAdjustZoomRatio(1239,701);
            break;

        case _ASPECT_RATIO_17Inch_4x3:       
            UserAdjustZoomRatio(930,701);
            break;

        case _ASPECT_RATIO_17Inch_5x4:       
            UserAdjustZoomRatio(873,701);
            break;

        case _ASPECT_RATIO_1024x768:       
            UserAdjustZoomRatio(1024,768);
            break;
            
        case _ASPECT_RATIO_800x600:
            UserAdjustZoomRatio(800,600);
            break;

        case _ASPECT_RATIO_640x480:
            UserAdjustZoomRatio(640,480);
            break;

        case _ASPECT_RATIO_1400x1050:
            UserAdjustZoomRatio(1400,1050);
            break;

        case _ASPECT_RATIO_1280x1024:
#if(_CUSTOMER == _CUS_TOSHIBA)
            UserInterfaceAdjustAspectRatio();
#else
            UserAdjustZoomRatio(1280,1024);
#endif
            break;

        case _ASPECT_RATIO_870x625:
            UserAdjustZoomRatio(870,625);
            break;
            
        case _ASPECT_RATIO_MAXIMAGE:
        case _ASPECT_RATIO_HMAXIMAGE:
        case _ASPECT_RATIO_VMAXIMAGE:
        case _ASPECT_RATIO_USER:
            // User defined adjust aspect ratio
            UserInterfaceAdjustAspectRatio();
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
            SET_ASPECT_RATIO_MIN_DVH(UserInterfaceGetAspectRatioMinDVHeight());
#endif
            break;

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
        case _ASPECT_RATIO_ORIGIN:

            ScalerMDomainAspectOriginMode(_TRUE);

            // Consider Panel Height and Input Height
            if(GET_MDOMAIN_OUTPUT_VHEIGHT() > GET_MDOMAIN_INPUT_VHEIGHT())
            {
                // Double V height for interlaced timing
                if((GET_MDOMAIN_INPUT_INTERLACE_FLG() == _TRUE) &&
                   (GET_MDOMAIN_INPUT_HWIDTH() > (GET_MDOMAIN_INPUT_VHEIGHT() << 1)))
                {
                    // Check if output V height > (input V height x 2)
                    if(GET_MDOMAIN_OUTPUT_VHEIGHT() > (GET_MDOMAIN_INPUT_VHEIGHT() << 1))
                    {
                        PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_VHEIGHT() - (GET_MDOMAIN_INPUT_VHEIGHT() << 1);
                        SET_MDOMAIN_OUTPUT_VHEIGHT(GET_MDOMAIN_INPUT_VHEIGHT() << 1);
                    }
                    else
                    {
                        // Output V height unchanged
                        PDATA_WORD(0) = 0x00;
                    }
                }
                else
                {
                    PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_VHEIGHT() - GET_MDOMAIN_INPUT_VHEIGHT();
                    SET_MDOMAIN_OUTPUT_VHEIGHT(GET_MDOMAIN_INPUT_VHEIGHT());
                }

                PDATA_WORD(0) &= 0xFFFC; // V start should be even
                SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + (PDATA_WORD(0) / 2));
            }
            else
            {
                usHRatio = 0x01;
            }

            // Consider Panel Width and Input Width
            if(GET_MDOMAIN_OUTPUT_HWIDTH() > GET_MDOMAIN_INPUT_HWIDTH())
            {
                PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_HWIDTH() - GET_MDOMAIN_INPUT_HWIDTH();
                PDATA_WORD(0) &= 0xFFFC; // H start should be even
                SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + (PDATA_WORD(0) / 2));
                SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_INPUT_HWIDTH());
            }
            else
            {
                usVRatio = 0x01;
            }

            if((usHRatio != 1) || (usVRatio != 1))
            {
                // Enlarge or Maintain Vertical
                PDATA_WORD(1) = GET_MDOMAIN_OUTPUT_VSTART() - ((DWORD)GET_MDOMAIN_OUTPUT_VSTART() * UserInterfaceGetAspectRatioOriginalRatio() / 0xFF);
                PDATA_WORD(1) &= 0xFFFE; // V start should be even

                // Enlarge Vertical
                if(PDATA_WORD(1) != 0)
                {
                    SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() - PDATA_WORD(1));
                    SET_MDOMAIN_OUTPUT_VHEIGHT(GET_MDOMAIN_OUTPUT_VHEIGHT() + PDATA_WORD(1) * 2);
                }
                // Maintain or Decrease Vertical
                else
                {
                    PDATA_WORD(1) = GET_MDOMAIN_OUTPUT_VSTART() - ((DWORD)GET_MDOMAIN_OUTPUT_VSTART() * UserInterfaceGetAspectRatioOriginalRatioSmall() / 0xFF);
                    PDATA_WORD(1) &= 0xFFFE; // V start should be even

                    // Decrease Vertical
                    if(PDATA_WORD(1) != 0)
                    {
                        // Add NO Support Check
                        if((GET_MDOMAIN_OUTPUT_VHEIGHT() > (PDATA_WORD(1) * 2)) &&
                           (GET_MDOMAIN_INPUT_VHEIGHT() / _VSD_MAX_RATIO < GET_MDOMAIN_OUTPUT_VHEIGHT() - PDATA_WORD(1) * 2))
                        {
                            SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + PDATA_WORD(1));
                            SET_MDOMAIN_OUTPUT_VHEIGHT(GET_MDOMAIN_OUTPUT_VHEIGHT() - PDATA_WORD(1) * 2);
                        }
                        else
                        {
                            DebugMessageMemory("Exceed Minimum Limit", UserInterfaceGetAspectRatioOriginalRatioSmall());

                            // GET_MDOMAIN_OUTPUT_VHEIGHT() = GET_MDOMAIN_INPUT_VHEIGHT() / _VSD_MAX_RATIO
                            PDATA_WORD(1) = GET_MDOMAIN_OUTPUT_VHEIGHT() - GET_MDOMAIN_INPUT_VHEIGHT() / _VSD_MAX_RATIO;
                            PDATA_WORD(1) &= 0xFFFC; // H start should be even

                            SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + PDATA_WORD(1) / 2);
                            SET_MDOMAIN_OUTPUT_VHEIGHT(GET_MDOMAIN_OUTPUT_VHEIGHT() - PDATA_WORD(1));
                        }
                    }
                }

                // Enlarge or Maintain Horizontal
                PDATA_WORD(1) = GET_MDOMAIN_OUTPUT_HSTART() - ((DWORD)GET_MDOMAIN_OUTPUT_HSTART() * UserInterfaceGetAspectRatioOriginalRatio() / 0xFF);
                PDATA_WORD(1) &= 0xFFFE; // H start should be even

                // Enlarge Horizontal
                if(PDATA_WORD(1) != 0)
                {
                    SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() - PDATA_WORD(1));
                    SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH() + PDATA_WORD(1) * 2);
                }
                // Maintain or Decrease Horizontal
                else
                {
                    PDATA_WORD(1) = GET_MDOMAIN_OUTPUT_HSTART() - ((DWORD)GET_MDOMAIN_OUTPUT_HSTART() * UserInterfaceGetAspectRatioOriginalRatioSmall() / 0xFF);
                    PDATA_WORD(1) &= 0xFFFE; // H start should be even

                    // Decrease Horizontal
                    if(PDATA_WORD(1) != 0)
                    {
                        // Add NO Support Check
                        if((GET_MDOMAIN_OUTPUT_HWIDTH() > (PDATA_WORD(1) * 2)) &&
                           (GET_MDOMAIN_INPUT_HWIDTH() / _HSD_MAX_RATIO < GET_MDOMAIN_OUTPUT_HWIDTH() - PDATA_WORD(1) * 2))
                        {
                            SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + PDATA_WORD(1));
                            SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH() - PDATA_WORD(1) * 2);
                        }
                        else
                        {
                            DebugMessageMemory("Exceed Minimum Limit", UserInterfaceGetAspectRatioOriginalRatioSmall());

                            // GET_MDOMAIN_OUTPUT_HWIDTH() = GET_MDOMAIN_INPUT_HWIDTH() / _HSD_MAX_RATIO
                            PDATA_WORD(1) = GET_MDOMAIN_OUTPUT_HWIDTH() - GET_MDOMAIN_INPUT_HWIDTH() / _HSD_MAX_RATIO;
                            PDATA_WORD(1) &= 0xFFFC; // H start should be even

                            SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + PDATA_WORD(1) / 2);
                            SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH() - PDATA_WORD(1));
                        }
                    }
                }
            }

            break;
#endif // End of #if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    }
}
#endif // End of #if(_ASPECT_RATIO_SUPPORT == _ON)

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust input size for rotation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustRotationInputSize(void)
{
    if((ScalerRotationCheckStatus() == _FALSE) ||
       ((GET_ROT_TYPE() != _ROT_CW90) && (GET_ROT_TYPE() != _ROT_CW270)))
    {
        return;
    }

    switch(GET_ROT_DISP_SIZE())
    {
        default:
            break;

        case _ROT_PIXEL_BY_PIXEL:
            // Calculate / Set V
            if(_PANEL_DH_WIDTH < GET_INPUT_TIMING_VHEIGHT())
            {
                PDATA_WORD(0) = ((GET_INPUT_TIMING_VHEIGHT() - _PANEL_DH_WIDTH) / 2);
                PDATA_WORD(0) += GET_INPUT_TIMING_VSTART();

                // VStart / VHeight
                SET_MDOMAIN_INPUT_VSTART(PDATA_WORD(0));
                SET_MDOMAIN_INPUT_VHEIGHT(_PANEL_DH_WIDTH);
            }

            // Calculate / Set H
            if(_PANEL_DV_HEIGHT < GET_INPUT_TIMING_HWIDTH())
            {
                PDATA_WORD(0) = (GET_INPUT_TIMING_HWIDTH() - _PANEL_DV_HEIGHT);
                PDATA_WORD(0) += GET_INPUT_TIMING_HSTART();
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);

                // HStart / HWidth
                SET_MDOMAIN_INPUT_HSTART(PDATA_WORD(0));
                SET_MDOMAIN_INPUT_HWIDTH(_PANEL_DV_HEIGHT);
            }

            break;
    }
}

//--------------------------------------------------
// Description  : Adjust display size for rotation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustRotationDisplaySize(void)
{
    if((ScalerRotationCheckStatus() == _FALSE) ||
       ((GET_ROT_TYPE() != _ROT_CW90) && (GET_ROT_TYPE() != _ROT_CW270)))
    {
        return;
    }

    switch(GET_ROT_DISP_SIZE())
    {
        default:
        case _ROT_FULL:

            // Set Size
            SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
            SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
            SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
            SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT);

            break;

        case _ROT_PIXEL_BY_PIXEL:

            PDATA_WORD(0) = _PANEL_DH_START;
            PDATA_WORD(1) = _PANEL_DH_WIDTH;
            PDATA_WORD(2) = _PANEL_DV_START;
            PDATA_WORD(3) = _PANEL_DV_HEIGHT;

            // Calculate / Set Display Window H
            if(_PANEL_DH_WIDTH > GET_MDOMAIN_INPUT_VHEIGHT())
            {
                // Underscan
                PDATA_WORD(0) += ((_PANEL_DH_WIDTH - GET_MDOMAIN_INPUT_VHEIGHT()) / 2);
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);
                PDATA_WORD(1) = GET_INPUT_TIMING_VHEIGHT();
            }

            // Calculate / Set Display Window V Start
            if(_PANEL_DV_HEIGHT > GET_MDOMAIN_INPUT_HWIDTH())
            {
                // Underscan
                PDATA_WORD(2) += ((_PANEL_DV_HEIGHT - GET_MDOMAIN_INPUT_HWIDTH()) / 2);
                PDATA_WORD(3) = GET_MDOMAIN_INPUT_HWIDTH();
            }

            // Set Display Window H Start/Width
            SET_MDOMAIN_OUTPUT_HSTART(PDATA_WORD(0));
            SET_MDOMAIN_OUTPUT_HWIDTH(PDATA_WORD(1));

            // Set Display Window V Start/Height
            SET_MDOMAIN_OUTPUT_VSTART(PDATA_WORD(2));
            SET_MDOMAIN_OUTPUT_VHEIGHT(PDATA_WORD(3));

            break;

        case _ROT_KEEP_SRC_ASPECT_RATIO:

            // Double V height for interlaced timing
            if((GET_MDOMAIN_INPUT_INTERLACE_FLG() == _TRUE) &&
               (GET_MDOMAIN_INPUT_VHEIGHT() < (GET_MDOMAIN_INPUT_HWIDTH() / 2)))
            {
                PDATA_WORD(1) = GET_MDOMAIN_INPUT_VHEIGHT() * 2;
            }
            else
            {
                PDATA_WORD(1) = GET_MDOMAIN_INPUT_VHEIGHT();
            }

            // Calculate VHeight
            PDATA_WORD(0) = ((DWORD)_PANEL_DH_WIDTH * GET_MDOMAIN_INPUT_HWIDTH()) / PDATA_WORD(1);

            if(PDATA_WORD(0) > _PANEL_DV_HEIGHT)
            {
                // Calculate HWidth
                PDATA_WORD(0) = ((DWORD)_PANEL_DV_HEIGHT * PDATA_WORD(1)) / GET_MDOMAIN_INPUT_HWIDTH();

                // Set HWidth / VHeight
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);
                SET_MDOMAIN_OUTPUT_HWIDTH(PDATA_WORD(0));
                SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT);

                // HStart / VStart
                PDATA_WORD(0) = (_PANEL_DH_START + (_PANEL_DH_WIDTH - PDATA_WORD(0)) / 2);
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);
                SET_MDOMAIN_OUTPUT_HSTART(PDATA_WORD(0));
                SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
            }
            else
            {
                // HWidth / VHeight
                SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
                SET_MDOMAIN_OUTPUT_VHEIGHT(PDATA_WORD(0));

                // HStart / VStart
                SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                SET_MDOMAIN_OUTPUT_VSTART((_PANEL_DV_START + (_PANEL_DV_HEIGHT - PDATA_WORD(0)) / 2));
            }

            break;
    }
}
#endif  // #if(_DISPLAY_ROTATION_SUPPORT == _ON)

#if(_I_DITHER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set IDither Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustIDither(void)
{
#if(_IDITHER_TYPE == _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT)
    BYTE code *pucTempoTable = _NULL_POINTER;
#else
    BYTE code *pucTempoTable = tIDITHER_TEMPOFFSET_TABLE;
#endif

#if(_IDITHER_SD_MASK_SUPPORT == _ON)
    ScalerColorSetScalingDownMaskLSB();
#endif

    if(ScalerMDomainGetColorDepth() == _COLOR_DEPTH_8_BITS)
    {
        ScalerColorIDitherAdjust(tIDITHER_TABLE_FIFO8, tIDITHER_SEQ_TABLE, pucTempoTable, GET_CURRENT_BANK_NUMBER());
    }
    else if(ScalerMDomainGetColorDepth() == _COLOR_DEPTH_10_BITS)
    {
        ScalerColorIDitherAdjust(tIDITHER_TABLE_FIFO10, tIDITHER_SEQ_TABLE, pucTempoTable, GET_CURRENT_BANK_NUMBER());
    }
#if(_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT)
    else if(ScalerMDomainGetColorDepth() == _COLOR_DEPTH_6_BITS)
    {
        ScalerColorIDitherAdjust(tIDITHER_TABLE_FIFO8, tIDITHER_SEQ_TABLE, pucTempoTable, GET_CURRENT_BANK_NUMBER());
    }
#endif
}
#endif // End of #if(_I_DITHER_SUPPORT == _ON)

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set RGB Quantization Range
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustRGBQuantizationRange(void)
{
    EnumColorRGBQuantization enumColorRGBQuantization = ScalerColorGetRGBQuantizationRange();
    bit bRGBLimitRange = _FALSE;

#if(_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON)
    bRGBLimitRange = UserInterfaceGetRGBQuantizationLimitRangeStatus(enumColorRGBQuantization);
#else
    bRGBLimitRange = UserCommonInterfaceGetRGBQuantizationLimitRangeStatus(enumColorRGBQuantization);
#endif

    ScalerColorSetRGBLimitRange(bRGBLimitRange);
}
#endif // End of #if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)

#if(_ULTRA_VIVID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustUltraVivid(EnumFunctionOnOFF enumFunctionOnOFF, EnumColorSpace enumColorFormat, EnumDBApply enumDBApply)
{
#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
    ScalerGlobalForceDDomainDBRecovery(enumDBApply, _FALSE);
#endif

    if(enumFunctionOnOFF == _FUNCTION_ON)
    {
        if(ScalerColorUltraVividSetDisable() == _TRUE)
        {
#if(_YPEAKING_SUPPORT == _ON)
            UserInterfaceAdjustYpeaking();
#endif
            ScalerColorUltraVividEnable(_FUNCTION_OFF, _DB_APPLY_NONE);
        }
        else
        {
#if(_YPEAKING_SUPPORT == _ON)
            ScalerColorYpeaking(_OFF);
#endif
            UserInterfaceAdjustUltraVivid();
        }
    }
    else
    {
#if(_YPEAKING_SUPPORT == _ON)
        ScalerColorYpeaking(_OFF);
#endif
        ScalerColorUltraVividEnable(_FUNCTION_OFF, _DB_APPLY_NONE);
    }

    SysModeColorSpaceConvert(enumColorFormat, enumDBApply);
}
#endif  // End of #if(_ULTRA_VIVID_SUPPORT == _ON)

#if(_D_DITHER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DDither Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------

#if(_CUSTOMER == _CUS_MINDRAY)
#define CACHE_SIZE 16
void DitheDataWriteToFlsah(BYTE code *pTable, WORD usAddr, WORD usLength)
{
    BYTE mData_Cache[CACHE_SIZE];
    BYTE i= 0;
    BYTE count = 0;
    
    if((usLength/CACHE_SIZE) != 0)
    {
        count = (usLength/CACHE_SIZE) + 1;
    }
    else
    {
        count = (usLength/CACHE_SIZE);
    }
    
    for(i=0; i<count; i++)
    {
        memset(mData_Cache, 0, CACHE_SIZE);
        if(i == count - 1)
        {
            memcpy(mData_Cache, pTable + i*CACHE_SIZE, usLength - i*CACHE_SIZE);
            UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + i*CACHE_SIZE, usLength - i*CACHE_SIZE, mData_Cache);
        }
        else
        {
            memcpy(mData_Cache, pTable + i*CACHE_SIZE, CACHE_SIZE);
            UserCommonFlashWrite(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usAddr + i*CACHE_SIZE, CACHE_SIZE, mData_Cache);
        }       
    }    
}

void RTDFlashRestoreDitherData(void)
{

    
    UserCommonFlashErasePage(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, _DITHER_PAGE);

    //DDITHER_TEMPOFFSET_TABLE
    DitheDataWriteToFlsah(tDDITHER_TEMPOFFSET_TABLE,_TEMP_DITHER_TABLE_ADDR,_TEMP_DITHER_TABLE_SIZE);

    //DDITHER_SEQ_TABLE
    DitheDataWriteToFlsah(tDDITHER_SEQ_TABLE,_SEQ_TABLE_ADDR,_SEQ_TABLE_SIZE);

    //DDITHER_TABLE
#if(_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL)
    DitheDataWriteToFlsah(tDDITHER_TABLE18Bit,_DITHER_TABLE_18BIT_ADDR,_DITHER_TABLE_18BIT_SIZE);
#endif
    DitheDataWriteToFlsah(tDDITHER_TABLE24Bit,_DITHER_TABLE_24BIT_ADDR,_DITHER_TABLE_24BIT_SIZE);
    DitheDataWriteToFlsah(tDDITHER_TABLE30Bit,_DITHER_TABLE_30BIT_ADDR,_DITHER_TABLE_30BIT_SIZE);

}

extern void ScalerBurstWrite(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, WORD usHostAddr, BYTE ucTableType, bit bTableLocation);
extern void ScalerColorDDitherLoadSetting(DWORD ulSettingOption);
void RTDFlashLoadDitherData(void)
{
    DWORD ulSettingOption = 0x00000000;
    BYTE ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
    BYTE xdata ucDither[2];
    BYTE  j;

    ScalerSetBit(0x006A, ~(_BIT7 | _BIT6), 0x80);
    for(j=0;j< (144/2); j++)
    {
        if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
        {
#if(_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL)
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, _DITHER_TABLE_18BIT_ADDR+ 2*j, 2,  &ucDither[0]);
            ScalerBurstWrite(ucDither, 2, GET_CURRENT_BANK_NUMBER(), 0x0069, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
#endif
        }
        else if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_24_BIT)
        {
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, _DITHER_TABLE_24BIT_ADDR+ 2*j, 2,  &ucDither[0]);
            ScalerBurstWrite(ucDither, 2, GET_CURRENT_BANK_NUMBER(), 0x0069, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        }
        else
        {
            UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, _DITHER_TABLE_30BIT_ADDR + 2*j, 2,  &ucDither[0]);
            ScalerBurstWrite(ucDither, 2, GET_CURRENT_BANK_NUMBER(), 0x0069, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
        }
    }
    ScalerSetBit(0x006A, ~(_BIT7 | _BIT6), 0x00);

    ScalerSetBit(0x006A, ~(_BIT7 | _BIT6), 0x40);
    for(j=0;j<24;j++)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, _SEQ_TABLE_ADDR+ 2*j, 2,	&ucDither[0]);
        ScalerBurstWrite(ucDither, 2, GET_CURRENT_BANK_NUMBER(), 0x0069, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    }
    ScalerSetBit(0x006A, ~(_BIT7 | _BIT6), 0x00);

    ScalerSetBit(0x006A, ~(_BIT7 | _BIT6), 0xC0);
    for(j=0;j< (32/2); j++)
    {
        UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, _TEMP_DITHER_TABLE_ADDR+ 2*j, 2,  &ucDither[0]);
        ScalerBurstWrite(ucDither, 2, GET_CURRENT_BANK_NUMBER(), 0x0069, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_XRAM);
    }
    ScalerSetBit(0x006A, ~(_BIT7 | _BIT6), 0x00);

#if(((_D_DITHER_MULTI_SEQ_ENABLE == _ENABLE) && (_D_DITHER_SERIES_SEQ_ENABLE == _DISABLE)) ||\
    (_D_DITHER_SHARE_SEQ_ENABLE == _ENABLE) || (_D_DITHER_SEQ_INV_ENABLE == _ENABLE) ||\
    (_D_DITHER_V_FRAME_MOD == _ENABLE) || (_D_DITHER_H_FRAME_MOD == _ENABLE))

    switch(_D_DITHER_SUPER_PIXEL_SIZE)
    {
        case _DDITHER_SUPER_PIXEL_2X2:
            if((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) || (_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT))
            {
                ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_16_FRAME;
            }
            break;

        case _DDITHER_SUPER_PIXEL_2X4:
        case _DDITHER_SUPER_PIXEL_4X2:
            if((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) || (_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT))
            {
                ucKeepNFrame = _DDITHER_KEEP_2_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_8_FRAME;
            }
            break;

        case _DDITHER_SUPER_PIXEL_4X4:
            if((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) || (_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT))
            {
                ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
            }
            break;

        case _DDITHER_SUPER_PIXEL_4X8:
        case _DDITHER_SUPER_PIXEL_8X4:
            if((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) || (_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT))
            {
                ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_2_FRAME;
            }
            break;

            default:
            ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
            break;
    }

#endif

    ulSettingOption = (_D_DITHER_6BIT_PANEL_FUNC_ENABLE << 7) | (1 << 4) | (_D_DITHER_V_FRAME_MOD << 1) | _D_DITHER_H_FRAME_MOD;
    ulSettingOption = ulSettingOption | (((DWORD)((ucKeepNFrame << 4) | _D_DITHER_SUPER_PIXEL_SIZE)) << 8);
    ulSettingOption = ulSettingOption | (((DWORD)((_D_DITHER_SERIES_SEQ_ENABLE << 3) | (_D_DITHER_MULTI_SEQ_ENABLE << 2))) << 16);
    ulSettingOption = ulSettingOption | (((DWORD)((_D_DITHER_SHARE_SEQ_ENABLE << 3) | (_D_DITHER_SEQ_INV_ENABLE << 1) | _D_DITHER_SEQ_INV_MODE)) << 24);

    ScalerColorDDitherLoadSetting(ulSettingOption);

}

#endif

void UserCommonAdjustDDither(void)
{
#if(_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL)
    BYTE code *pucTempoTable = _NULL_POINTER;
#else
    BYTE code *pucTempoTable = tDDITHER_TEMPOFFSET_TABLE;
#endif

#if(_PANEL_EXIST_MULTIPANEL == _OFF)
#if(_CUSTOMER == _CUS_MINDRAY)
    RTDFlashLoadDitherData();
#else
    ScalerColorDDitherAdjust(tDDITHER_TABLE, tDDITHER_SEQ_TABLE, pucTempoTable, GET_CURRENT_BANK_NUMBER());
#endif
#else
    switch(_PANEL_DISP_BIT_MODE)
    {
        case _PANEL_DISP_18_BIT:
#if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
            ScalerColorDDitherAdjust(_NULL_POINTER, tDDITHER_SEQ_TABLE, pucTempoTable, GET_CURRENT_BANK_NUMBER());
#else
            ScalerColorDDitherAdjust(tDDITHER_TABLE18Bit, tDDITHER_SEQ_TABLE, pucTempoTable, GET_CURRENT_BANK_NUMBER());
#endif
            break;

        case _PANEL_DISP_24_BIT:
            ScalerColorDDitherAdjust(tDDITHER_TABLE24Bit, tDDITHER_SEQ_TABLE, pucTempoTable, GET_CURRENT_BANK_NUMBER());
            break;

        case _PANEL_DISP_30_BIT:
        default:
            ScalerColorDDitherAdjust(tDDITHER_TABLE30Bit, tDDITHER_SEQ_TABLE, pucTempoTable, GET_CURRENT_BANK_NUMBER());
            break;
    }
#endif

#if(_D_DITHER_ADVANCE_SETTING_ENABLE == _ENABLE)

#if((_PANEL_EXIST_MULTIPANEL == _OFF) && (_CUSTOMER != _CUS_MINDRAY))
    ScalerColorDDitherAdvanceSettingAdjust(tDDITHER_REALIGN_TABLE, tDDITHER_REALIGN_TEMPO_TABLE, tDDITHER_LSB_TABLE, tDDITHER_ADVANCE_SETTING_TABLE, GET_CURRENT_BANK_NUMBER());
#else
    switch(_PANEL_DISP_BIT_MODE)
    {
        case _PANEL_DISP_18_BIT:
#if((_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) || (_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
            ScalerColorDDitherAdvanceSettingAdjust(tDDITHER_REALIGN_TABLE, tDDITHER_REALIGN_TEMPO_TABLE, tDDITHER_LSB_TABLE18Bit, tDDITHER_ADVANCE_SETTING_TABLE18Bit, GET_CURRENT_BANK_NUMBER());
#endif
            break;

        case _PANEL_DISP_24_BIT:
            ScalerColorDDitherAdvanceSettingAdjust(tDDITHER_REALIGN_TABLE, tDDITHER_REALIGN_TEMPO_TABLE, tDDITHER_LSB_TABLE24Bit, tDDITHER_ADVANCE_SETTING_TABLE24Bit, GET_CURRENT_BANK_NUMBER());
            break;

        case _PANEL_DISP_30_BIT:
        default:
            ScalerColorDDitherAdvanceSettingAdjust(tDDITHER_REALIGN_TABLE, tDDITHER_REALIGN_TEMPO_TABLE, tDDITHER_LSB_TABLE30Bit, tDDITHER_ADVANCE_SETTING_TABLE30Bit, GET_CURRENT_BANK_NUMBER());
            break;
    }
#endif

#endif
}
#endif // End of #if(_D_DITHER_SUPPORT == _ON)

#if(_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)
//--------------------------------------------------
// Description  : Output Data
// Input Value  : Input Data
// Output Value : compensate value for 6bit panel
//--------------------------------------------------
WORD UserCommonAdjust6bitPanelCompensate(WORD usData)
{
#if(_TRANSLATOR_SUPPORT == _OFF)
    usData = (DWORD)usData * 252 / 255;
#endif

    return usData;
}
#endif

//--------------------------------------------------
// Description  : Set 10bit Panel Compesate
// Input Value  : Row Data
// Output Value : Compesate Data
//--------------------------------------------------
WORD UserCommonAdjust10bitPanelCompensate(WORD usData)
{
#if(_TRANSLATOR_SUPPORT == _OFF)
    if(ScalerColorGetColorDepth() == _COLOR_DEPTH_8_BITS)
    {
        usData = (WORD)(((DWORD)usData * 1023 / 1020) > 4095) ? 4095 : (WORD)((DWORD)usData * 1023 / 1020);
    }
#endif

    return usData;
}

#if(_SHARPNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Sharpness Table
// Input Value  : Request Sharpness Table
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustSharpness(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(ScalerScalingGetScalingUpType())
    {
        case _VSU_2D_4LINE_COEF:
#if(_CUSTOMER == _CUS_TOSHIBA)
            // 1:1 Mode Use Different Scaling Table
            if((ScalerColorScalingByPassTableSel() == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
            {
                ScalerMemorySetScalingCoef(UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_V_SU_128TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
            else
            {
                ScalerMemorySetScalingCoef(UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_V_SU_128TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
#else
            // 1:1 Mode Use Different Scaling Table
            if((ScalerColorScalingByPassTableSel() == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
            {
                ScalerMemorySetScalingCoef(UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
            else
            {
                ScalerMemorySetScalingCoef(UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
#endif
            break;

#if(_VSU_3L_SUPPORT == _ON)
        case _VSU_2D_3LINE_COEF:
#if(_CUSTOMER == _CUS_TOSHIBA)
            // 1:1 Mode Use Different Scaling Table
            if((ScalerColorScalingByPassTableSel() == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
            {
                ScalerMemorySetScalingCoef(UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_V_SU_96TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
            else
            {
                ScalerMemorySetScalingCoef(UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_V_SU_96TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
#else
            // 1:1 Mode Use Different Scaling Table
            if((ScalerColorScalingByPassTableSel() == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
            {
                ScalerMemorySetScalingCoef(UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_96TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
            else
            {
                ScalerMemorySetScalingCoef(UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_96TAPS_NORMAL, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
#endif
            break;
#endif

        default:

            break;
    }
}
#endif

#if(_FREEZE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Display freeze
// Input Value  : ON --> Display freeze
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustDisplayFreeze(bit bEn)
{
    ScalerFRCDisplayFreeze(bEn);
}
#endif // End of #if(_FREEZE_SUPPORT == _ON)

#if(_UNIFORMITY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Uniformity type level mode
// Input Value  : UniformityType Index
// Output Value : Level mode
//--------------------------------------------------
BYTE UserCommonAdjustGetUniformityType(BYTE ucIndex)
{
    return tUniformityType[ucIndex];
}
//--------------------------------------------------
// Description  : Load gain, offset and decay LUT, turn on/off offset function
// Input Value  : EnumUniformityType, EnumUniformityModeSelect
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustPanelUniformity(EnumUniformityTypeSelect enumUniformityType, EnumUniformityModeSelect enumUniformityMode)
{
    BYTE ucGainTableBank = 0;
    WORD usGainTableAddr = 0;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    BYTE ucOffsetTableBank = 0;
    WORD usOffsetTableAddr = 0;
    WORD usDecayTableAddr = 0;
#endif
    ucGainTableBank = UserCommonAdjustPanelUniformityGainBank(enumUniformityType);
    usGainTableAddr = UserCommonAdjustPanelUniformityGainAddr(enumUniformityType);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)

    if(tUNIFORMITY_OSD_TYPE_OFFSET_ENABLE_INDEX[enumUniformityType] == _ON)
    {
        ucOffsetTableBank = UserCommonAdjustPanelUniformityOffsetBank(enumUniformityType);
        usOffsetTableAddr = UserCommonAdjustPanelUniformityOffsetAddr(enumUniformityType);
        usDecayTableAddr = UserCommonAdjustPanelUniformityDecayAddr(enumUniformityType);
        ScalerColorPanelUniformityOffsetAdjust(g_pucDISP_CALIBRATION_FLASH + usOffsetTableAddr, _PANEL_UNIFORMITY_OFFSET_LUT_SIZE, ucOffsetTableBank);
        ScalerColorPanelUniformityDecayAdjust(g_pucDISP_CALIBRATION_FLASH + usDecayTableAddr, _PANEL_UNIFORMITY_DECAY_LUT_SIZE, ucOffsetTableBank, enumUniformityMode, UserCommonAdjustGetUniformityType(enumUniformityType));
        ScalerColorPanelUniformityOffsetEnable(_FUNCTION_ON);
    }
    else
    {
        ScalerColorPanelUniformityOffsetEnable(_FUNCTION_OFF);
    }
#endif // End of #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)

    ScalerColorPanelUniformityAdjust(g_pucDISP_CALIBRATION_FLASH + usGainTableAddr, _PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonAdjustGetUniformityType(enumUniformityType), ucGainTableBank, enumUniformityMode, UserCommonAdjustGetUniformityType(enumUniformityType));
}
//--------------------------------------------------
// Description  : Calculate Uniformity Gain Bank
// Input Value  : enumUniformityType, ucStartBank, usUNILUTSize
// Output Value : usUniformityTypeBank
//--------------------------------------------------
BYTE UserCommonAdjustPanelUniformityGainBank(EnumUniformityTypeSelect enumUniformityType)
{
    BYTE ucUniformityTypeBank = 0;
    DWORD ulRemainder = 65536;
    BYTE ucUniformityTypeNum = 0;
    WORD usUniformityTableSize = 0;

    for(ucUniformityTypeNum = 0; ucUniformityTypeNum <= enumUniformityType; ucUniformityTypeNum++)
    {
        usUniformityTableSize = ((DWORD)_PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonAdjustGetUniformityType(ucUniformityTypeNum) + 1); // +1 checksum address size

        if(ulRemainder < usUniformityTableSize)
        {
            ulRemainder = 65536;
            ucUniformityTypeBank++;
        }
        ulRemainder = (ulRemainder - usUniformityTableSize);
    }

    return ucUniformityTypeBank + _UNIFORMITY_FLASH_BANK0;
}
//--------------------------------------------------
// Description  : Calculate Panel Uniformity Gain Table Address
// Input Value  : enumUniformityType, usUNILUTSize
// Output Value : usUniformityTypeAddr
//--------------------------------------------------
WORD UserCommonAdjustPanelUniformityGainAddr(EnumUniformityTypeSelect enumUniformityType)
{
    WORD usUniformityTypeAddr = 0;
    DWORD ulRemainder = 0;
    BYTE ucUniformityTypeNum = 0;
    BYTE ucQuotient = 0;
    WORD usUniformityTableSize = 0;

    for(ucUniformityTypeNum = 0; ucUniformityTypeNum <= enumUniformityType; ucUniformityTypeNum++)
    {
        usUniformityTableSize = ((DWORD)_PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonAdjustGetUniformityType(ucUniformityTypeNum) + 1);
        if(ulRemainder < usUniformityTableSize)
        {
            if(ucQuotient == 0)
            {
                ulRemainder = 65536 - _UNIFORMITY_FINISH_ADDRESS - 1;
                usUniformityTypeAddr = _UNIFORMITY_FINISH_ADDRESS + 1;
            }
            else
            {
                ulRemainder = 65536;
                usUniformityTypeAddr = 0;
            }
            ucQuotient++;
        }
        else
        {
            usUniformityTypeAddr += (_PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonAdjustGetUniformityType(ucUniformityTypeNum - 1) + 1);
        }
        ulRemainder = (ulRemainder - usUniformityTableSize);
    }
    return usUniformityTypeAddr;
}
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate Uniformity Offset and Decay Table Bank
// Input Value  : enumUniformityType, ucStartBank, usUNILUTSize, usUNIOffsetLUTSize, usUNIDecayLUTSize
// Output Value : usUniformityTypeOffsetBank
//--------------------------------------------------
BYTE UserCommonAdjustPanelUniformityOffsetBank(EnumUniformityTypeSelect enumUniformityType)
{
    BYTE ucTotalGainBank = 0;
    BYTE ucDivisor = 0;
    BYTE ucQuotient = 0;
    DWORD ulRemainder = 65536;
    BYTE ucUniformityTypeNum = 0;
    WORD usUniformityTableSize = 0;

    ucDivisor = (BYTE)(65536 / ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + (DWORD)_PANEL_UNIFORMITY_DECAY_LUT_SIZE + 2)); // +2 Offset and Decay table checksum address size
    ucQuotient = enumUniformityType / ucDivisor;

    for(ucUniformityTypeNum = 0; ucUniformityTypeNum <= _UNIFORMITY_TOTAL_SET; ucUniformityTypeNum++)
    {
        usUniformityTableSize = ((DWORD)_PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonAdjustGetUniformityType(ucUniformityTypeNum) + 1);
        if(ulRemainder < usUniformityTableSize)
        {
            ulRemainder = 65536;
            ucTotalGainBank++;
        }
        ulRemainder = (ulRemainder - usUniformityTableSize);
    }
    ucTotalGainBank++;
    return ucQuotient + _UNIFORMITY_FLASH_BANK0 + ucTotalGainBank;
}
//--------------------------------------------------
// Description  : Calculate Panel Uniformity Offset Table Address
// Input Value  : enumUniformityType, usUNILUTSize
// Output Value : usUniformityTypeAddr
//--------------------------------------------------
WORD UserCommonAdjustPanelUniformityOffsetAddr(EnumUniformityTypeSelect enumUniformityType)
{
    WORD usUniformityTypeOffsetAddr = 0;
    BYTE ucDivisor = 0;
    BYTE ucQuotient = 0;
    BYTE ucRemainder = 0;

    ucDivisor = (BYTE)(65536 / ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + (DWORD)_PANEL_UNIFORMITY_DECAY_LUT_SIZE + 2)); // +2 offset and decay checksum address size
    ucQuotient = enumUniformityType / ucDivisor;
    ucRemainder = enumUniformityType % ucDivisor;

    usUniformityTypeOffsetAddr = ucRemainder * (_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + _PANEL_UNIFORMITY_DECAY_LUT_SIZE + 2);

    if(ucQuotient == 0)
    {
        usUniformityTypeOffsetAddr = usUniformityTypeOffsetAddr + _UNIFORMITY_OFFSET_FINISH_ADDRESS + 1;
    }

    return usUniformityTypeOffsetAddr;
}
//--------------------------------------------------
// Description  : Load Panel Uniformity LUT
// Input Value  : enumUniformityType, usUNIOffsetLUTSize, usUNIDecayLUTSize
// Output Value : usUniformityTypeAddr
//--------------------------------------------------
WORD UserCommonAdjustPanelUniformityDecayAddr(EnumUniformityTypeSelect enumUniformityType)
{
    return UserCommonAdjustPanelUniformityOffsetAddr(enumUniformityType) + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1;
}
#endif
#endif // End of #if(_UNIFORMITY_SUPPORT == _ON)

#if(_OGC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustOGCColorTempGain(BYTE ucColorTemp, BYTE ucGammaMode, BYTE *pucData, EnumOGCModeSelect enumOGCModeSelect)
{
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
#if(_LOCAL_DIMMING_SUPPORT == _ON)
    if(UserCommonLocalDimmingGetEnableStatus() == _LD_ENABLE)
    {
        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTemp * _OGC_TOTAL_GAMMA * 6 + ucGammaMode * 6 + _DIMMING_OGC_RGB_GAIN_ADDRESS), 6, pucData);
    }
    else
#endif
    {
#if(_GLOBAL_DIMMING_SUPPORT == _ON)
        if(UserCommonGlobalDimmingGetEnableStatus() == _GD_ENABLE)
        {
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTemp * _OGC_TOTAL_GAMMA * 6 + ucGammaMode * 6 + _DIMMING_OGC_RGB_GAIN_ADDRESS), 6, pucData);
        }
        else
#endif
        {
#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            if(enumOGCModeSelect > _OGC_NORMAL_TYPE)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTemp * _OGC_TOTAL_GAMMA * 6 + ucGammaMode * 6 + _OGC_RGB_GAIN_MAX_BRI_ADDRESS), 6, pucData);
            }
            else
#endif
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTemp * _OGC_TOTAL_GAMMA * 6 + ucGammaMode * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pucData);
                enumOGCModeSelect = enumOGCModeSelect;
            }
        }
    }
#elif(_CTS_TYPE == _CTS_GEN_0_8BIT)
    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTemp * _OGC_TOTAL_GAMMA * 3 + ucGammaMode * 3 + _OGC_RGB_GAIN_ADDRESS), 3, pucData);
    enumOGCModeSelect = enumOGCModeSelect;
#endif
}
#endif

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Calculate OutputGamma LUT Bank
// Input Value  : enumOGCTypeSelect, enumOGCModeSelect
// Output Value : usOutputGammaTypeBank
//--------------------------------------------------
BYTE UserCommonAdjustOGCBank(EnumOGCTypeSelect enumOGCTypeSelect, EnumOGCModeSelect enumOGCModeSelect)
{
#if(_OGC_GEN_TYPE == _OGC_GEN_1)
    BYTE ucDivisor_HeaderBank = 0;
    BYTE ucDivisor = 0;
    BYTE ucQuotient = 0;
    BYTE ucGammaNum = 0;

    ucDivisor_HeaderBank = (BYTE)((65536 - _DISP_CALIBRATION_PCM_END) / (DWORD)_OGC_GAMMA_TABLE_SIZE);
    ucDivisor = (BYTE)(65536 / (DWORD)_OGC_GAMMA_TABLE_SIZE);

#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
    if(enumOGCModeSelect > _OGC_NORMAL_TYPE)
    {
        ucGammaNum = enumOGCTypeSelect + _OGC_TOTAL_GAMMA;
    }
    else
#endif
    {
        ucGammaNum = enumOGCTypeSelect;
        enumOGCModeSelect = enumOGCModeSelect;
    }


    if(ucGammaNum < ucDivisor_HeaderBank)
    {
        ucQuotient = 0;
    }
    else
    {
        ucQuotient = (ucGammaNum - ucDivisor_HeaderBank) / ucDivisor + 1;
    }

    return ucQuotient + _OGC_FLASH_BANK;
#else
    enumOGCTypeSelect = enumOGCTypeSelect;
    enumOGCModeSelect = enumOGCModeSelect;

    return _OGC_FLASH_BANK;
#endif
}
//--------------------------------------------------
// Description  : Calculate OutputGamma LUT Address
// Input Value  : enumOGCTypeSelect, enumOGCModeSelect
// Output Value : usOutputGammaTypeAddr
//--------------------------------------------------
BYTE *UserCommonAdjustOGCAddr(EnumOGCTypeSelect enumOGCTypeSelect, EnumOGCModeSelect enumOGCModeSelect)
{
    BYTE *pucOutputGammaTypeAddr = _NULL_POINTER;
#if(_OGC_GEN_TYPE == _OGC_GEN_1)
    BYTE ucDivisor_HeaderBank = 0;
    BYTE ucDivisor = 0;
    BYTE ucGammaNum = 0;

    ucDivisor_HeaderBank = (BYTE)((65536 - _DISP_CALIBRATION_PCM_END) / (DWORD)_OGC_GAMMA_TABLE_SIZE);
    ucDivisor = (BYTE)(65536 / (DWORD)_OGC_GAMMA_TABLE_SIZE);

#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
    if(enumOGCModeSelect > _OGC_NORMAL_TYPE)
    {
        ucGammaNum = enumOGCTypeSelect + _OGC_TOTAL_GAMMA;
    }
    else
#endif
    {
        ucGammaNum = enumOGCTypeSelect;
        enumOGCModeSelect = enumOGCModeSelect;
    }

    if(ucGammaNum < ucDivisor_HeaderBank)
    {
        pucOutputGammaTypeAddr = g_pucDISP_CALIBRATION_FLASH + _DISP_CALIBRATION_PCM_END + ucGammaNum * _OGC_GAMMA_TABLE_SIZE;
    }
    else
    {
        pucOutputGammaTypeAddr = g_pucDISP_CALIBRATION_FLASH + (ucGammaNum - ucDivisor_HeaderBank) % ucDivisor * _OGC_GAMMA_TABLE_SIZE;
    }
#else
    enumOGCModeSelect = enumOGCModeSelect;

    if(enumOGCTypeSelect == _OGC_GAMMA1_TYPE)
    {
        pucOutputGammaTypeAddr = g_pucDISP_CALIBRATION_FLASH + _OGC_GAMMA1_ADDRESS;
    }
    else if(enumOGCTypeSelect == _OGC_GAMMA2_TYPE)
    {
        pucOutputGammaTypeAddr = g_pucDISP_CALIBRATION_FLASH + _OGC_GAMMA2_ADDRESS;
    }
    else if(enumOGCTypeSelect == _OGC_GAMMA3_TYPE)
    {
        pucOutputGammaTypeAddr = g_pucDISP_CALIBRATION_FLASH + _OGC_GAMMA3_ADDRESS;
    }
    else if(enumOGCTypeSelect == _OGC_GAMMA4_TYPE)
    {
        pucOutputGammaTypeAddr = g_pucDISP_CALIBRATION_FLASH + _OGC_GAMMA4_ADDRESS;
    }
    else if(enumOGCTypeSelect == _OGC_GAMMA5_TYPE)
    {
        pucOutputGammaTypeAddr = g_pucDISP_CALIBRATION_FLASH + _OGC_GAMMA5_ADDRESS;
    }
#endif

    return pucOutputGammaTypeAddr;
}
#endif

#if(_PCM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustPCM(EnumPCMType enumPCMMode, BYTE *pucIGammaTableArray, BYTE *pucOGammaTableArray, BYTE *pucColorMatrixArray, BYTE ucPCMBankNum, WORD usLength)
{
    BYTE ucGammaBankNum = ucPCMBankNum;
#if(_LOCAL_DIMMING_SUPPORT == _ON)
    EnumLDStatus enumLDStatus = UserCommonLocalDimmingGetEnableStatus();
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
#if(_OGC_SUPPORT == _ON)
    EnumSDROGCStatus enumGammaIndex = 0;
    WORD code tusDIMMING_GAMMA_OSD_INDEX[] =
    {
        _DIMMING_OGC_GAMMA1_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 1)
        _DIMMING_OGC_GAMMA2_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 2)
        _DIMMING_OGC_GAMMA3_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 3)
        _DIMMING_OGC_GAMMA4_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 4)
        _DIMMING_OGC_GAMMA5_ADDRESS,
#endif
#endif
#endif
#endif
    };
    enumGammaIndex = UserInterfaceGetSDROGCMode();
    if(enumGammaIndex > _OGC_TOTAL_GAMMA)
    {
        enumGammaIndex = 0;
    }
#endif

#endif // End of #if(_BACKLIGHT_DIMMING_SUPPORT == _ON)

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
    ScalerColorSRGBEnable(_FUNCTION_OFF);
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);

#if(_LOCAL_DIMMING_SUPPORT == _ON)
    if(enumLDStatus == _LD_ENABLE)
    {
        ScalerColorPanelUniformityEnable(_FUNCTION_OFF);

        if(ScalerColorDCRGetLocalDimmingHistoEnable() == _FALSE)
        {
            UserCommonLocalDimmingInitialSetting(_ENABLE);
        }

#if(_OGC_SUPPORT == _ON)
        if(enumPCMMode == _PCM_BYPASS)
        {
            pucIGammaTableArray = g_pucDISP_CALIBRATION_FLASH + tusDIMMING_GAMMA_OSD_INDEX[enumGammaIndex];
        }
#endif
        ucGammaBankNum = _OGC_FLASH_BANK;
        ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, (g_pucDISP_CALIBRATION_FLASH + _DIMMING_OCC_GAMMA10_ADDRESS), pucColorMatrixArray, ucPCMBankNum, usLength, ucGammaBankNum);
    }
    else
#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)
    {
#if(_GLOBAL_DIMMING_SUPPORT == _ON)
        if(UserCommonGlobalDimmingGetEnableStatus() == _GD_ENABLE)
        {
#if(_OGC_SUPPORT == _ON)
            if(enumPCMMode == _PCM_BYPASS)
            {
                pucIGammaTableArray = g_pucDISP_CALIBRATION_FLASH + tusDIMMING_GAMMA_OSD_INDEX[enumGammaIndex];
            }
#endif
            ucGammaBankNum = _OGC_FLASH_BANK;
            ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, (g_pucDISP_CALIBRATION_FLASH + _DIMMING_OCC_GAMMA10_ADDRESS), pucColorMatrixArray, ucPCMBankNum, usLength, ucGammaBankNum);
            UserCommonGlobalDimmingInitialSetting(_ENABLE);
        }
        else
#endif
        {
            ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength, ucGammaBankNum);
        }
    }

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerColorOutputGammaEnable(_FUNCTION_ON);
    ScalerColorSRGBEnable(_FUNCTION_ON);
    ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

#if(_LOCAL_DIMMING_SUPPORT == _ON)
    if(enumLDStatus == _LD_ENABLE)
    {
        ScalerColorPanelUniformityEnable(_FUNCTION_ON);
    }
#endif
}
#endif // End of #if(_PCM_FUNCTION == _ON)

#if(_GAMMA_FUNCTION == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustGamma(BYTE *pucOGammaTableArray, BYTE ucGammaBankNum)
{
#if(_LOCAL_DIMMING_SUPPORT == _ON)
    if(UserCommonLocalDimmingGetEnableStatus() == _LD_ENABLE)
    {
        UserCommonAdjustPCM(_PCM_BYPASS, (_NULL_POINTER),
                            (g_pucDISP_CALIBRATION_FLASH + _DIMMING_OCC_GAMMA10_ADDRESS),
                            _NULL_POINTER, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
    }
    else
#endif
    {
#if(_GLOBAL_DIMMING_SUPPORT == _ON)
        if(UserCommonGlobalDimmingGetEnableStatus() == _GD_ENABLE)
        {
            UserCommonAdjustPCM(_PCM_BYPASS, (_NULL_POINTER),
                                (g_pucDISP_CALIBRATION_FLASH + _DIMMING_OCC_GAMMA10_ADDRESS),
                                _NULL_POINTER, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else
#endif
        {
            ScalerColorOutputGammaAdjust(pucOGammaTableArray, ucGammaBankNum);
        }
    }
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustGammaRegionEnable(EnumFunctionOnOFF enumOn)
{
#if(_LOCAL_DIMMING_SUPPORT == _ON)
    if(UserCommonLocalDimmingGetEnableStatus() == _LD_ENABLE)
    {
        ScalerColorPanelUniformityEnable(enumOn);
        ScalerColorSRGBEnable(enumOn);
        ScalerColorPCMInputGammaEnable(enumOn);
    }
    else
    {
        // Local dimming enable status disable, uniformity local dimming function should be off.
        if(ScalerColorPanelUniformityGetLDStatus() == _ON)
        {
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
        }
    }
#endif

#if(_GLOBAL_DIMMING_SUPPORT == _ON)
    if(UserCommonGlobalDimmingGetEnableStatus() == _GD_ENABLE)
    {
        ScalerColorSRGBEnable(enumOn);
        ScalerColorPCMInputGammaEnable(enumOn);
    }
    else
    {
        if((UserInterfaceSDROCCOGCMode() == _SDR_CALIBRATION_BY_OGC_TOOL) &&
           (UserInterfaceGetGlobalDimmingStatus() == _GD_ENABLE))
        {
            ScalerColorSRGBEnable(enumOn);
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
        }
    }
#endif

    //check user native flag,if native flag is true, force off gamma enable
#if(_NATIVE_COLORTEMP == _ON)
    if(enumOn == _FUNCTION_ON)
    {   
        if(GET_NATIVE_COLOR_TEMP())
        {
            enumOn = _FUNCTION_OFF;
        }
    }
#endif

    ScalerColorOutputGammaEnable(enumOn);
}
#endif // End of #if(_GAMMA_FUNCTION == _ON)

#if(_SDR_TO_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustSDRToHDR(BYTE *pucIGammaTableArray, BYTE *pucICMTableArray, BYTE *pucDCCTableArray, BYTE ucSDRtoHDRBank)
{
#if(_LOCAL_DIMMING_SUPPORT == _ON)

    EnumLDStatus enumLDStatus = UserCommonLocalDimmingGetEnableStatus();

    if(enumLDStatus == _LD_ENABLE)
    {
        ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
    }
#endif

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerColorDCCEnable(_FUNCTION_OFF);
    ScalerColorICMEnable(_FUNCTION_OFF);

    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
    ScalerColorSRGBEnable(_FUNCTION_OFF);
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);

    // load DCC table
    ScalerColorDCCAdjust(pucDCCTableArray, ucSDRtoHDRBank);
    // load ICM table
    ScalerColorICMLoadTable(pucICMTableArray, ucSDRtoHDRBank);

    // Set InputGamma LUT
    ScalerColorPCMInputGammaAdjust(pucIGammaTableArray, ucSDRtoHDRBank);

#if(_LOCAL_DIMMING_SUPPORT == _ON)
    if(enumLDStatus == _LD_ENABLE)
    {
        ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _DIMMING_OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);
    }
    else
#endif
    {
#if(_GLOBAL_DIMMING_SUPPORT == _ON)
        if(UserCommonGlobalDimmingGetEnableStatus() == _GD_ENABLE)
        {
            ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _DIMMING_OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);
        }
        else
#endif
        {
            // Load Gamma table
            ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);
        }
    }

#if(_SDR_TO_HDR_ADOBE_RGB_SUPPORT == _ON)
    ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
#else
    ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
#endif

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_LOCAL_DIMMING_SUPPORT == _ON)
    if(enumLDStatus == _LD_ENABLE)
    {
        ScalerColorPanelUniformityEnable(_FUNCTION_ON);
    }
#endif
    ScalerColorDCCEnable(_FUNCTION_ON);
    ScalerColorICMEnable(_FUNCTION_ON);
    ScalerColorOutputGammaEnable(_FUNCTION_ON);
    ScalerColorSRGBEnable(_FUNCTION_ON);
    ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
}
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
//--------------------------------------------------
// Description  : Adjust Global Hue Saturation
// Input Value  : Hue and Saturation
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustGlobalHueSat(SWORD shHue, WORD usSat)
{
#if((_LOCAL_DIMMING_SUPPORT == _ON) && (_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1))
    if(UserCommonLocalDimmingGetEnableStatus() == _LD_DISABLE)
#endif
    {
#if(_GLOBAL_DIMMING_SUPPORT == _ON)
        if(UserCommonGlobalDimmingGetEnableStatus() == _GD_DISABLE)
#endif
        {
            ScalerColorSetSRGBGlobalHueSat(shHue, usSat);
        }
    }
}
#endif  // Enf of #if(_GLOBAL_HUE_SATURATION == _ON)

