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
// ID Code      : UserCommonLocalDimming.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_LOCAL_DIMMING__

#include "UserCommonInclude.h"

#if(_LOCAL_DIMMING_SUPPORT == _ON)

#pragma OT(8)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _TUNNELPATTERN_DCR_THESHOLD1                            383
#define _TUNNELPATTERN_DCR_THESHOLD2                            15 // 12

#define _TUNNELPATTERN_LDREGION_TOLERANCE                       2
#define _TUNNELPATTERN_LDREGION_ABOVE_FACTOR                    (128 + _TUNNELPATTERN_LDREGION_TOLERANCE)
#define _TUNNELPATTERN_LDREGION_BELOW_FACTOR                    (128 - _TUNNELPATTERN_LDREGION_TOLERANCE)

#define _TUNNELPATTERN_PHASE1_THD1_ABOVE_FACTOR                 ((DWORD)_PANEL_DH_WIDTH * _PANEL_DV_HEIGHT / 20)
#define _TUNNELPATTERN_PHASE1_THD1_BELOW_FACTOR                 ((DWORD)_PANEL_DH_WIDTH * _PANEL_DV_HEIGHT * 4 / 100)

#define _TUNNELPATTERN_PHASE1_THD2_ABOVE_FACTOR                 ((DWORD)_PANEL_DH_WIDTH * _PANEL_DV_HEIGHT * 97 / 100)
#define _TUNNELPATTERN_PHASE1_THD2_BELOW_FACTOR                 ((DWORD)_PANEL_DH_WIDTH * _PANEL_DV_HEIGHT * 90 / 100)

#define _TUNNELPATTERN_FAIL_COUNT                               4
#define _TUNNELPATTERN_PHASE1_COUNT                             2
#define _TUNNELPATTERN_PHASE2_COUNT                             2

#define _TUNNELPATTERN_LV                                       70

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
StructLocalDimmingInfo g_stLocalDimmingInfo;

typedef enum
{
    _LD_NONE_TUNNEL_PATTERN,
    _LD_TUNNEL_PHASE1_PASS,
    _LD_TUNNEL_PHASE2_PASS,
} EnumLDDetectTunnelPatternStatus;


//****************************************************************************
// CODE TABLES
//****************************************************************************
WORD code tLDHDRToneMappingLv540[256] =
{
#include _LD_HDR_TONE_MAPPING_LV540
};

WORD code tLDHDR2084Lv[256] =
{
#include _LD_HDR_2084_LV
};

WORD code tLDSDRGamma22Lv[256] =
{
#include _LD_SDR_GAMMA_22_LV
};

WORD code tLDSDRGamma24Lv[256] =
{
#include _LD_SDR_GAMMA_24_LV
};

WORD code tLDSDRGamma26Lv[256] =
{
#include _LD_SDR_GAMMA_26_LV
};

WORD code tLDSDROGCCase1Lv[256] =
{
#include _LD_SDR_OGC_CASE_1_LV
};

WORD code tLDSDROGCCase2Lv[256] =
{
#include _LD_SDR_OGC_CASE_2_LV
};

WORD code tLDSDROGCCase3Lv[256] =
{
#include _LD_SDR_OGC_CASE_3_LV
};

WORD code tLDSDROGCCase4Lv[256] =
{
#include _LD_SDR_OGC_CASE_4_LV
};

WORD code tLDSDROGCCase5Lv[256] =
{
#include _LD_SDR_OGC_CASE_5_LV
};

WORD code tStepLDRTable[256] =
{
#include _LD_STEP_R_TABLE
};

BYTE code tBaseLv[8] =
{
#include _LD_BASE_LV
};

BYTE code tNodeLvMerged[((_PANEL_UNIFORMITY_LD_HOR_GRIDS * _PANEL_UNIFORMITY_LD_HOR_GRIDS) * 9)] =
{
#include _LD_NODE_LV_MERGED
};

BYTE code tLocalDimmingUniformityLvMergeTable[(_PANEL_LV_MAX - _PANEL_LV_MIN + 1) * 5] =
{
#include _LD_UNIFORMITY_LV_MERGED
};

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
BYTE code tLocalDimmingUniformityBoostLvMergeTable[(_PANEL_LV_BOOST_MAX - _PANEL_LV_BOOST_MIN + 1) * 5] =
{
#include _LD_UNIFORMITY_BOOST_LV_MERGED
};
#endif

#if(_LD_FREESYNC_II_BOOST_SUPPORT == _ON)
WORD code tFREESYNCIILv[256] =
{
#include _LD_FREESYNC_II_LV
};
#endif

#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
WORD code tLDDarkGain[256] =
{
#include _LD_DARK_GAIN
};
#endif



//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_pucUnifotmityGainTable[_GROUP_NODE_NUMBER * 5];
WORD g_pusUniformityGainNode[_GROUP_NODE_NUMBER];

WORD g_pusDCRToLV[_TOTAL_REGION];
WORD g_pusLastDCRToLV[_TOTAL_REGION] =
{
    _PANEL_LV_MAX, _PANEL_LV_MAX, _PANEL_LV_MAX, _PANEL_LV_MAX,
    _PANEL_LV_MAX, _PANEL_LV_MAX, _PANEL_LV_MAX, _PANEL_LV_MAX,
};
WORD g_pusApplyPWM[_TOTAL_REGION];
WORD g_pusLastApplyPWM[_TOTAL_REGION] =
{
    _PANEL_PWM_MAX, _PANEL_PWM_MAX, _PANEL_PWM_MAX, _PANEL_PWM_MAX,
    _PANEL_PWM_MAX, _PANEL_PWM_MAX, _PANEL_PWM_MAX, _PANEL_PWM_MAX,
};
BYTE g_pucLastDCRResult[_TOTAL_REGION];
WORD g_pusSmoothLV[_TOTAL_REGION];
WORD g_pusApplyLV[_TOTAL_REGION];
WORD g_pusLastApplyLV[_TOTAL_REGION];
WORD g_pusLDR[_TOTAL_REGION];
WORD g_pusLastDeltaPWM[_TOTAL_REGION] =
{
    _PANEL_PWM_DELTA_MAX, _PANEL_PWM_DELTA_MAX, _PANEL_PWM_DELTA_MAX, _PANEL_PWM_DELTA_MAX,
    _PANEL_PWM_DELTA_MAX, _PANEL_PWM_DELTA_MAX, _PANEL_PWM_DELTA_MAX, _PANEL_PWM_DELTA_MAX,
};

// Variable for Dark Scene
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
WORD g_usSRGBGain = 512;
WORD g_usLastSRGBGain = 512;
bit g_bDarkScene = _FALSE;
BYTE g_pucSRGBMatrixOriginal[24];
BYTE g_ucMaxDCR;
#endif


#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
EnumLDDetectTunnelPatternStatus g_enumDetectCTunnelPatternStatus = _LD_NONE_TUNNEL_PATTERN;
BYTE g_ucWaitForStable;
#endif

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
WORD g_usLDPeakLv = _PANEL_LV_BOOST_MAX;
BYTE g_ucLDBoostGain = (DWORD)_PANEL_LV_BOOST_MAX * 100 / _PANEL_LV_MAX;
BYTE g_ucLastLDBoostGain = (DWORD)_PANEL_LV_BOOST_MAX * 100 / _PANEL_LV_MAX;
WORD g_usLDBoostR;
bit g_bLDBoostMod = _FALSE;
EnumLDBoostMode g_enumLDBoostMode = _LD_BOOST_USER;
BYTE g_pucLDSRGBMatrixOriginal[24];
WORD g_pusLastBoostPWM[_TOTAL_REGION] =
{
    _PANEL_PWM_MAX, _PANEL_PWM_MAX, _PANEL_PWM_MAX, _PANEL_PWM_MAX,
    _PANEL_PWM_MAX, _PANEL_PWM_MAX, _PANEL_PWM_MAX, _PANEL_PWM_MAX,
};
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonLocalDimmingHandler(void);
EnumLDStatus UserCommonLocalDimmingGetEnableStatus(void);
void UserCommonLocalDimmingAdjust(void);
void UserCommonLocalDimmingDCRToLv(BYTE *pucDCRData8bit, WORD *pusDCRToLV);
void UserCommonLocalDimmingSetPWM1x8(WORD *pusApplyLv, WORD *pusApplyPWM);
void UserCommonLocalDimmingUniformityNodetoGainTable(WORD *pusUniformityGainNode, BYTE *pucUnifotmityGainTable, BYTE ucNodeClass);
void UserCommonLocalDimmingInitialSetting(bit bEn);
void UserCommonLocalDimmingSetLastPWMFull(void);
void UserCommonLocalDimmingStepToGDHDR(void);
void UserCommonLocalDimmingGetNodeLV1X8(WORD *pusUniformityGainNode, WORD *pusPWM, BYTE ucNodeClass);
void UserCommonLocalDimmingEnable(bit bEn);
void UserCommonLocalDimmingSetPWMValue(WORD *pusPWM);
void UserCommonLocalDimmingDCRToLvVerifyMode(BYTE *pucDCRData8bit, WORD *pusDCRToLV);
void UserCommonLocalDimmingDCRToLvNormalMode(BYTE *pucDCRData8bit, WORD *pusDCRToLV);
void UserCommonLocalDimmingSmoothLv(WORD *pusSmoothLV, WORD *pusDCRToLV, BYTE ucSmoothLevel);
void UserCommonLocalDimmingStepToTarget(WORD *pusApplyLv, WORD *pusTargetLv, WORD *pusLastApplyLv, BYTE *pucDCRResult, BYTE *pucLastDCRResult);

#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
void UserCommonLocalDimmingSetHLWDetectTunnelPattern(EnumFunctionOnOFF enumOn);
void UserCommonLocalDimmingDetectTunnelPattern(BYTE *pucDCRLDData8bit);
#endif

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
void UserCommonLocalDimmingLvBoostGainValue(BYTE *pucBoostGain);
EnumLDBoostMode UserCommonLocalDimmingGetBoostMode(void);
#endif

#if((_ASPECT_RATIO_SUPPORT == _ON) || (_ASPECT_ORIGINAL_MODE_SUPPORT == _ON))
void UserCommonLocalDimmingAspectRatioAdjust(void);
#endif

#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
void UserCommonLocalDimmingDarkSceneGain(void);
void UserCommonLocalDimmingDarkSceneInitial(bit bEN);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonLocalDimmingHandler(void)
{
    if(UserCommonLocalDimmingGetEnableStatus() == _LD_ENABLE)
    {
        if(UserInterfaceGetLocaldimmingActionMode() == _LD_ACTION_MODE_DIMMING)
        {
            UserCommonLocalDimmingAdjust();
            SET_LD_ACTION_MODE_STATUS(_LD_ACTION_MODE_DIMMING);
        }
        else
        {
            if(GET_LD_ACTION_MODE_STATUS() == _LD_ACTION_MODE_DIMMING)
            {
                UserCommonLocalDimmingStepToGDHDR();
                SET_LD_ACTION_MODE_STATUS(_LD_ACTION_MODE_NORNAL);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Judge Local Dimming ON or OFF
// Input Value  : None
// Output Value : LD_ENABLE OR LD_DISABLE
//--------------------------------------------------
EnumLDStatus UserCommonLocalDimmingGetEnableStatus(void)
{
    if((GET_ON_LINE_CALIBRATION_STATUS() == _CALIBRATION_OFF) && (UserInterfaceGetLocalDimmingStatus() == _LD_ENABLE))
    {
#if(_LD_FREESYNC_MODE_SUPPORT == _OFF)
#if(_FREESYNC_SUPPORT == _ON)
        if(ScalerSyncGetFREESYNCEnable() == _TRUE)
        {
            return _LD_DISABLE;
        }
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
        if(GET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING() == _ON)
        {
            return _LD_DISABLE;
        }
#endif

#if(_HDR10_SUPPORT == _ON)
        if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
        {
            return _LD_ENABLE;
        }
        else
#endif
        {
#if((_LD_FREESYNC_MODE_SUPPORT == _ON) && (_FREESYNC_II_SUPPORT == _ON))
            if(UserCommonHDRGetFreeSyncIILDDisable() == _OFF)
            {
                return _LD_ENABLE;
            }
            else
#endif
            {
                if(UserInterfaceGetLocalDimmingNoSupportStatus() == _LD_DISABLE)
                {
                    return _LD_DISABLE;
                }
                else
                {
                    return _LD_ENABLE;
                }
            }
        }
    }
    else
    {
        return _LD_DISABLE;
    }
    return _LD_DISABLE;
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonLocalDimmingAdjust(void)
{
    // Check if DCR data and DB ready
    if(ScalerColorDDomainDBStatus() == _NOT_WAIT)
    {
        BYTE pucDCRResult[_TOTAL_REGION];
        BYTE ucNodeClass = 0;
        memset(pucDCRResult, 255UL, _TOTAL_REGION);

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
        g_enumLDBoostMode = UserCommonLocalDimmingGetBoostMode();
#endif

        ScalerColorDCRLocalDimmingReadResult(pucDCRResult);
        DebugMessageHDR("pucDCRResult[0]", pucDCRResult[0]);
        DebugMessageHDR("pucDCRResult[1]", pucDCRResult[1]);
        DebugMessageHDR("pucDCRResult[2]", pucDCRResult[2]);
        DebugMessageHDR("pucDCRResult[3]", pucDCRResult[3]);
        DebugMessageHDR("pucDCRResult[4]", pucDCRResult[4]);
        DebugMessageHDR("pucDCRResult[5]", pucDCRResult[5]);
        DebugMessageHDR("pucDCRResult[6]", pucDCRResult[6]);
        DebugMessageHDR("pucDCRResult[7]", pucDCRResult[7]);

#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
        if(ScalerColorGlobalDBStatus() == _NOT_WAIT)
        {
            // Detect Tunnel Pattern
            UserCommonLocalDimmingDetectTunnelPattern(pucDCRResult);
        }
        DebugMessageHDR("Status", g_enumDetectCTunnelPatternStatus);
#endif

        UserCommonLocalDimmingDCRToLv(pucDCRResult, g_pusDCRToLV);
        UserCommonLocalDimmingSmoothLv(g_pusSmoothLV, g_pusDCRToLV, UserInterfaceGetLocalDimmingPWMSmoothLevel());
        UserCommonLocalDimmingStepToTarget(g_pusApplyLV, g_pusSmoothLV, g_pusLastApplyLV, pucDCRResult, g_pucLastDCRResult);

#if(_PANEL_REGION_MODE == _LD_1X8_MODE)
        UserCommonLocalDimmingSetPWM1x8(g_pusApplyLV, g_pusApplyPWM);
#endif

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
        UserCommonLocalDimmingLvBoostGainValue(&g_ucLDBoostGain);
        DebugMessageHDR("g_ucLDBoostGain", g_ucLDBoostGain);
#endif

        UserCommonLocalDimmingSetPWMValue(g_pusApplyPWM);

        DebugMessageHDR("g_pusApplyPWM[0]", g_pusApplyPWM[0]);
        DebugMessageHDR("g_pusApplyPWM[1]", g_pusApplyPWM[1]);
        DebugMessageHDR("g_pusApplyPWM[2]", g_pusApplyPWM[2]);
        DebugMessageHDR("g_pusApplyPWM[3]", g_pusApplyPWM[3]);
        DebugMessageHDR("g_pusApplyPWM[4]", g_pusApplyPWM[4]);
        DebugMessageHDR("g_pusApplyPWM[5]", g_pusApplyPWM[5]);
        DebugMessageHDR("g_pusApplyPWM[6]", g_pusApplyPWM[6]);
        DebugMessageHDR("g_pusApplyPWM[7]", g_pusApplyPWM[7]);

        for(ucNodeClass = 0; ucNodeClass < _NODE_CLASS_NUMBER; ucNodeClass++)
        {
#if(_PANEL_REGION_MODE == _LD_1X8_MODE)
            UserCommonLocalDimmingGetNodeLV1X8(g_pusUniformityGainNode, g_pusApplyPWM, ucNodeClass);
#endif
            // get uniformity table
            UserCommonLocalDimmingUniformityNodetoGainTable(g_pusUniformityGainNode, g_pucUnifotmityGainTable, ucNodeClass);

            // Write Uniformity table
            if(ucNodeClass == _NODE_CLASS_NUMBER - 1)
            {
                ScalerColorPanelUniformityLDTargetLUTAdjust(g_pucUnifotmityGainTable, ucNodeClass * _GROUP_NODE_NUMBER, _REMAINDER_NODE_NUMBER * 5);
                ScalerColorPanelUniformityLDSramToggle(_DB_APPLY_NO_POLLING);
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
                UserCommonLocalDimmingDarkSceneGain();
#endif
            }
            else
            {
                ScalerColorPanelUniformityLDTargetLUTAdjust(g_pucUnifotmityGainTable, ucNodeClass * _GROUP_NODE_NUMBER, _GROUP_NODE_NUMBER * 5);
            }
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonLocalDimmingDCRToLv(BYTE *pucDCRData8bit, WORD *pusDCRToLV)
{
    if(UserInterfaceGetPCHDRVerifyMode() == _LD_PCHDR_VERIFY_MODE)
    {
        UserCommonLocalDimmingDCRToLvVerifyMode(pucDCRData8bit, pusDCRToLV);
    }
    else
    {
        UserCommonLocalDimmingDCRToLvNormalMode(pucDCRData8bit, pusDCRToLV);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonLocalDimmingSetPWM1x8(WORD *pusApplyLv, WORD *pusApplyPWM)
{
    BYTE data ucRegionInd = 0;
    WORD pusMaxDelPWM[_TOTAL_REGION] = {0};
    // set increase PWM
    for(ucRegionInd = 0; ucRegionInd < _TOTAL_REGION; ucRegionInd++)
    {
        switch(ucRegionInd)
        {
            case 0:
                pusApplyPWM[0] = pusApplyLv[0] * _REGION0_PWM_TO_LV_OWN;
                break;

            case 1:

                pusApplyPWM[1] = pusApplyLv[1] * _REGION1_PWM_TO_LV_OWN;
                break;

            case 2:

                pusApplyPWM[2] = pusApplyLv[2] * _REGION2_PWM_TO_LV_OWN;
                break;

            case 3:

                pusApplyPWM[3] = pusApplyLv[3] * _REGION3_PWM_TO_LV_OWN;

                break;

            case 4:

                pusApplyPWM[4] = pusApplyLv[4] * _REGION4_PWM_TO_LV_OWN;

                break;

            case 5:

                pusApplyPWM[5] = pusApplyLv[5] * _REGION5_PWM_TO_LV_OWN;

                break;

            case 6:

                pusApplyPWM[6] = pusApplyLv[6] * _REGION6_PWM_TO_LV_OWN;


                break;

            case 7:

                pusApplyPWM[7] = pusApplyLv[7] * _REGION7_PWM_TO_LV_OWN;

                break;

            default:

                break;
        }
    }
    for(ucRegionInd = 0; ucRegionInd < 8; ucRegionInd++)
    {
        pusMaxDelPWM[ucRegionInd] = ((((DWORD)g_pusLDR[ucRegionInd] * pusApplyPWM[ucRegionInd]) + ((DWORD)(1024 - g_pusLDR[ucRegionInd]) * g_pusLastApplyPWM[ucRegionInd]))) / 1024;

        if(pusApplyPWM[ucRegionInd] > g_pusLastApplyPWM[ucRegionInd])
        {
            if(pusApplyPWM[ucRegionInd] > pusMaxDelPWM[ucRegionInd])
            {
                pusApplyPWM[ucRegionInd] = pusMaxDelPWM[ucRegionInd];
            }
        }
        else
        {
            if(pusApplyPWM[ucRegionInd] < pusMaxDelPWM[ucRegionInd])
            {
                pusApplyPWM[ucRegionInd] = pusMaxDelPWM[ucRegionInd];
            }
        }
        if(pusApplyPWM[ucRegionInd] > _PANEL_PWM_MAX)
        {
            pusApplyPWM[ucRegionInd] = _PANEL_PWM_MAX;
        }
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_0)
        if(pusApplyPWM[ucRegionInd] < _PANEL_PWM_MIN)
        {
            pusApplyPWM[ucRegionInd] = _PANEL_PWM_MIN;
        }
#endif
    }

    memcpy(g_pusLastApplyPWM, pusApplyPWM, 8 * sizeof(pusApplyPWM[0]));
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonLocalDimmingUniformityNodetoGainTable(WORD *pusUniformityGainNode, BYTE *pucUnifotmityGainTable, BYTE ucNodeClass)
{
    BYTE data ucI = 0;
    BYTE data ucJ = 0;
    WORD *pusUniformityGainNodeOffset;
    data WORD usUniformityGainTablePosition = 0;
    BYTE data ucMaxIdx = 0;
    BYTE data ucQuot = 0;
    BYTE data ucRemind = 0;

    if(ucNodeClass < (_NODE_CLASS_NUMBER - 1))
    {
        ucQuot = _GROUP_NODE_NUMBER / 255;
        ucRemind = _GROUP_NODE_NUMBER % 255;
    }
    else if(ucNodeClass == (_NODE_CLASS_NUMBER - 1))
    {
        ucQuot = _REMAINDER_NODE_NUMBER / 255;
        ucRemind = _REMAINDER_NODE_NUMBER % 255;
    }

    for(ucI = 0; ucI <= ucQuot; ucI++)
    {
        pusUniformityGainNodeOffset = &pusUniformityGainNode[(WORD)(ucI)*0xFF];

        if(ucI != ucQuot)
        {
            ucMaxIdx = 0xFF;
        }
        else
        {
            ucMaxIdx = ucRemind;
        }
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
        if(g_enumLDBoostMode == _LD_BOOST_KERNAL)
        {
            for(ucJ = 0; ucJ < ucMaxIdx; ucJ++)
            {
                data WORD usUniformityGainNode_ucI = pusUniformityGainNodeOffset[ucJ];

                if((usUniformityGainNode_ucI > _PANEL_LV_BOOST_MAX))
                {
                    usUniformityGainTablePosition = (_PANEL_LV_BOOST_MAX - _PANEL_LV_BOOST_MIN);
                }
                else if(usUniformityGainNode_ucI < _PANEL_LV_BOOST_MIN)
                {
                    usUniformityGainTablePosition = (_PANEL_LV_BOOST_MIN - _PANEL_LV_BOOST_MIN);
                }
                else
                {
                    usUniformityGainTablePosition = usUniformityGainNode_ucI - _PANEL_LV_BOOST_MIN;
                }

                memcpy(pucUnifotmityGainTable, tLocalDimmingUniformityBoostLvMergeTable + ((WORD)usUniformityGainTablePosition) * 5, 5);
                pucUnifotmityGainTable += 5;
            }
        }
        else
#endif
        {
            for(ucJ = 0; ucJ < ucMaxIdx; ucJ++)
            {
                data WORD usUniformityGainNode_ucI = pusUniformityGainNodeOffset[ucJ];

                if((usUniformityGainNode_ucI > _PANEL_LV_MAX))
                {
                    usUniformityGainTablePosition = (_PANEL_LV_MAX - _PANEL_LV_MIN);
                }
                else if(usUniformityGainNode_ucI < _PANEL_LV_MIN)
                {
                    usUniformityGainTablePosition = (_PANEL_LV_MIN - _PANEL_LV_MIN);
                }
                else
                {
                    usUniformityGainTablePosition = usUniformityGainNode_ucI - _PANEL_LV_MIN;
                }

                memcpy(pucUnifotmityGainTable, tLocalDimmingUniformityLvMergeTable + ((WORD)usUniformityGainTablePosition) * 5, 5);
                pucUnifotmityGainTable += 5;
            }
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonLocalDimmingInitialSetting(bit bEn)
{
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
    BYTE pucTemp[4];
    memset(pucTemp, 0, sizeof(pucTemp));
#endif

#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
    UserCommonLocalDimmingDarkSceneInitial(bEn);
#endif

    if(bEn == _ENABLE)
    {
        ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
        ScalerTimerWaitForEvent(_EVENT_DVS);
        ScalerTimerDelayXms(2);

        // DCR
        ScalerColorDCRLocalDimmingEnable(_FUNCTION_ON);
        ScalerColorDCRLocalDimmingSetMode(_LOCAL_DIMMING_1X8_MODE);
        ScalerColorDCRLocalDimmingSetTCon(_LOCAL_DIMMING_1X8_MODE);

#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
        // Tunnel pattern HLW
        UserCommonLocalDimmingSetHLWDetectTunnelPattern(_FUNCTION_ON);
#endif

        // Uniformity
        ScalerColorPanelUniformityLDInitial(_UNIFORMITY_PCM_MODE);
        ScalerColorPanelUniformityLDEnable(_FUNCTION_ON, _DB_APPLY_POLLING);
        UserCommonLocalDimmingSetLastPWMFull();

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III)
        // Global DB
        ScalerColorDDomainDBEnable(_ENABLE);
        ScalerColorDDomainDBTriggerEvent(_DB_VS_TRIGGER);
#endif

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
        UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_NOTM_BOUND_ADDRESS), 4, pucTemp);
        g_usLDPeakLv = ((WORD)pucTemp[2] << 8) + pucTemp[3];
#endif
    }
    else
    {
        // DCR
        ScalerColorDCRLocalDimmingEnable(_FUNCTION_OFF);

        // Uniformity
        ScalerColorPanelUniformityLDEnable(_FUNCTION_OFF, _DB_APPLY_POLLING);

#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
        // Tunnel pattern HLW
        UserCommonLocalDimmingSetHLWDetectTunnelPattern(_FUNCTION_OFF);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
        ScalerColorPanelUniformityInitial();
        if(UserInterfaceGetUniformityStatus() == _PANEL_UNIFORMITY_OFF)
#endif
        {
            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
        }

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III)
        // Global DB
        ScalerColorDDomainDBEnable(_DISABLE);
#endif
    }

    SET_LD_ACTION_MODE_STATUS(_LD_ACTION_MODE_NORNAL);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonLocalDimmingSetLastPWMFull(void)
{
    BYTE ucI = 0;

    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
    {
        g_pusLastDeltaPWM[ucI] = _PANEL_PWM_DELTA_MAX;
        g_pusLastApplyLV[ucI] = _PANEL_LV_MAX;
        g_pusLastApplyPWM[ucI] = _PANEL_PWM_MAX;
        g_pucLastDCRResult[ucI] = 255UL;
    }
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
    g_ucMaxDCR = 255;
    g_usLastSRGBGain = 512;
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonLocalDimmingStepToGDHDR(void)
{
    BYTE ucI = 0;
    BYTE ucFinishFlag = 0;
    BYTE ucTimeout = 30;
    BYTE pucRegionFlag[_TOTAL_REGION] = {0};
    BYTE ucNodeClass = 0;

    if(ScalerColorDDomainDBStatus() == _WAIT)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
    g_ucMaxDCR = 255;
#endif
    while(ucFinishFlag != _TOTAL_REGION)
    {
        ucFinishFlag = 0;
        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
        {
            g_pusApplyPWM[ucI] = g_pusApplyPWM[ucI] + _PANEL_PWM_STEP_TO_GOLBAL;

            if(g_pusApplyPWM[ucI] >= _PANEL_PWM_MAX)
            {
                g_pusApplyPWM[ucI] = _PANEL_PWM_MAX;
                pucRegionFlag[ucI] = 1;
            }
            else
            {
                pucRegionFlag[ucI] = 0;
            }
        }

        UserCommonLocalDimmingSetPWMValue(g_pusApplyPWM);

        DebugMessageHDR("StepToGB[0]", g_pusApplyPWM[0]);
        DebugMessageHDR("StepToGB[1]", g_pusApplyPWM[1]);
        DebugMessageHDR("StepToGB[2]", g_pusApplyPWM[2]);
        DebugMessageHDR("StepToGB[3]", g_pusApplyPWM[3]);
        DebugMessageHDR("StepToGB[4]", g_pusApplyPWM[4]);
        DebugMessageHDR("StepToGB[5]", g_pusApplyPWM[5]);
        DebugMessageHDR("StepToGB[6]", g_pusApplyPWM[6]);
        DebugMessageHDR("StepToGB[7]", g_pusApplyPWM[7]);

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
        g_ucLDBoostGain = (DWORD)_PANEL_LV_BOOST_MAX * 100 / _PANEL_LV_MAX;
#endif

        for(ucNodeClass = 0; ucNodeClass < _NODE_CLASS_NUMBER; ucNodeClass++)
        {
            UserCommonLocalDimmingGetNodeLV1X8(g_pusUniformityGainNode, g_pusApplyPWM, ucNodeClass);
            UserCommonLocalDimmingUniformityNodetoGainTable(g_pusUniformityGainNode, g_pucUnifotmityGainTable, ucNodeClass);
            if(ucNodeClass == _NODE_CLASS_NUMBER - 1)
            {
                ScalerColorPanelUniformityLDTargetLUTAdjust(g_pucUnifotmityGainTable, ucNodeClass * _GROUP_NODE_NUMBER, _REMAINDER_NODE_NUMBER * 5);
                ScalerColorPanelUniformityLDSramToggle(_DB_APPLY_POLLING);
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
                UserCommonLocalDimmingDarkSceneGain();
#endif
            }
            else
            {
                ScalerColorPanelUniformityLDTargetLUTAdjust(g_pucUnifotmityGainTable, ucNodeClass * _GROUP_NODE_NUMBER, _GROUP_NODE_NUMBER * 5);
            }
        }

        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
        {
            ucFinishFlag += pucRegionFlag[ucI];
        }

        // Check timeout counter
        if(ucTimeout-- == 0)
        {
            for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
            {
                g_pusApplyPWM[ucI] = _PANEL_PWM_MAX;
            }
            UserCommonLocalDimmingSetPWMValue(g_pusApplyPWM);

            for(ucNodeClass = 0; ucNodeClass < _NODE_CLASS_NUMBER; ucNodeClass++)
            {
                UserCommonLocalDimmingGetNodeLV1X8(g_pusUniformityGainNode, g_pusApplyPWM, ucNodeClass);
                UserCommonLocalDimmingUniformityNodetoGainTable(g_pusUniformityGainNode, g_pucUnifotmityGainTable, ucNodeClass);
                if(ucNodeClass == _NODE_CLASS_NUMBER - 1)
                {
                    ScalerColorPanelUniformityLDTargetLUTAdjust(g_pucUnifotmityGainTable, ucNodeClass * _GROUP_NODE_NUMBER, _REMAINDER_NODE_NUMBER * 5);
                    ScalerColorPanelUniformityLDSramToggle(_DB_APPLY_POLLING);
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
                    UserCommonLocalDimmingDarkSceneGain();
#endif
                }
                else
                {
                    ScalerColorPanelUniformityLDTargetLUTAdjust(g_pucUnifotmityGainTable, ucNodeClass * _GROUP_NODE_NUMBER, _GROUP_NODE_NUMBER * 5);
                }
            }

            break;
        }
    }

    UserCommonLocalDimmingSetLastPWMFull();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonLocalDimmingGetNodeLV1X8(WORD *pusUniformityGainNode, WORD *pusPWM, BYTE ucNodeClass)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;
    data BYTE code *pucData = tNodeLvMerged;
    WORD data usNodeIndex = 0;
    WORD data pusLocalPwm[_TOTAL_REGION];
    BYTE data ucMaxIdx = 0;
    BYTE ucQuot = 0;
    BYTE ucRemind = 0;

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
    if(g_enumLDBoostMode == _LD_BOOST_KERNAL)
    {
        WORD pusMaxDelPWM[_TOTAL_REGION] = {0};

        for(ucI = 0; ucI < (sizeof(pusLocalPwm) / sizeof(pusLocalPwm[0])); ++ucI)
        {
            pusLocalPwm[ucI] = (DWORD)pusPWM[ucI] * g_ucLDBoostGain / 100;

            pusMaxDelPWM[ucI] = ((((DWORD)g_usLDBoostR * pusLocalPwm[ucI]) + ((DWORD)(1024 - g_usLDBoostR) * pusLocalPwm[ucI]))) / 1024;
            if(pusLocalPwm[ucI] > g_pusLastBoostPWM[ucI])
            {
                if(pusLocalPwm[ucI] > pusMaxDelPWM[ucI])
                {
                    pusLocalPwm[ucI] = pusMaxDelPWM[ucI];
                }
            }
            else
            {
                if(pusLocalPwm[ucI] < pusMaxDelPWM[ucI])
                {
                    pusLocalPwm[ucI] = pusMaxDelPWM[ucI];
                }
            }
            memcpy(g_pusLastBoostPWM, pusLocalPwm, 8 * sizeof(pusLocalPwm[0]));
            pusLocalPwm[ucI] *= 16;
            if(LOBYTE(pusLocalPwm[ucI]) >= 128)
            {
                pusLocalPwm[ucI] += 256;
            }
        }
    }
    else
#endif
    {
        for(ucI = 0; ucI < (sizeof(pusLocalPwm) / sizeof(pusLocalPwm[0])); ++ucI)
        {
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
            if(pusPWM[ucI] < _PANEL_PWM_MIN)
            {
                pusLocalPwm[ucI] = 0;
            }
            else
#endif
            {
                pusLocalPwm[ucI] = pusPWM[ucI] - _PANEL_PWM_MIN;
            }

            pusLocalPwm[ucI] *= 16;

            if(LOBYTE(pusLocalPwm[ucI]) >= 128)
            {
                pusLocalPwm[ucI] += 256;
            }
        }
    }

    if(ucNodeClass < (_NODE_CLASS_NUMBER - 1))
    {
        ucQuot = _GROUP_NODE_NUMBER / 255;
        ucRemind = _GROUP_NODE_NUMBER % 255;
    }
    else if(ucNodeClass == (_NODE_CLASS_NUMBER - 1))
    {
        ucQuot = _REMAINDER_NODE_NUMBER / 255;
        ucRemind = _REMAINDER_NODE_NUMBER % 255;
    }

    pucData = pucData + ucNodeClass * _GROUP_NODE_NUMBER * 9;

    for(ucI = 0; ucI <= ucQuot; ucI++)
    {
        if(ucI != ucQuot)
        {
            ucMaxIdx = 0xFF;
        }
        else
        {
            ucMaxIdx = ucRemind;
        }

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
        if(g_enumLDBoostMode == _LD_BOOST_KERNAL)
        {
            for(ucJ = 0; ucJ < ucMaxIdx; ucJ++)
            {
                pusUniformityGainNode[usNodeIndex] =
                    ((BYTEPTR(pusLocalPwm)[0] * pucData[0] +
                      BYTEPTR(pusLocalPwm)[2] * pucData[1] +
                      BYTEPTR(pusLocalPwm)[4] * pucData[2] +
                      BYTEPTR(pusLocalPwm)[6] * pucData[3] +
                      BYTEPTR(pusLocalPwm)[8] * pucData[4] +
                      BYTEPTR(pusLocalPwm)[10] * pucData[5] +
                      BYTEPTR(pusLocalPwm)[12] * pucData[6] +
                      BYTEPTR(pusLocalPwm)[14] * pucData[7]) / 32);
                usNodeIndex++;
                pucData += 9;
            }
        }
        else
#endif
        {
            for(ucJ = 0; ucJ < ucMaxIdx; ucJ++)
            {
                pusUniformityGainNode[usNodeIndex] =
                    ((BYTEPTR(pusLocalPwm)[0] * pucData[0] +
                      BYTEPTR(pusLocalPwm)[2] * pucData[1] +
                      BYTEPTR(pusLocalPwm)[4] * pucData[2] +
                      BYTEPTR(pusLocalPwm)[6] * pucData[3] +
                      BYTEPTR(pusLocalPwm)[8] * pucData[4] +
                      BYTEPTR(pusLocalPwm)[10] * pucData[5] +
                      BYTEPTR(pusLocalPwm)[12] * pucData[6] +
                      BYTEPTR(pusLocalPwm)[14] * pucData[7]) / 32 + pucData[8]);
                usNodeIndex++;
                pucData += 9;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Enable Local Dimming Function in OSD
// Input Value  : EnumSelRegion, _Enable or _Disable
// Output Value : void
//--------------------------------------------------
void UserCommonLocalDimmingEnable(bit bEn)
{
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
    ScalerColorSRGBEnable(_FUNCTION_OFF);
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);

    UserCommonLocalDimmingInitialSetting(bEn);

#if(_HDR10_SUPPORT == _ON)
    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
    {
        WORD usOCCGammaTableArray = ((bEn == _ON) ? _DIMMING_OCC_GAMMA10_ADDRESS : _OCC_GAMMA10_ADDRESS);

        ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + usOCCGammaTableArray, _OGC_FLASH_BANK);

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorPanelUniformityEnable((EnumFunctionOnOFF)bEn);
        ScalerColorOutputGammaEnable(_FUNCTION_ON);
        ScalerColorSRGBEnable(_FUNCTION_ON);
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
    }
    else
#endif
    {
        UserInterfaceLocalDimmingAdjustPCM();
    }
}

//--------------------------------------------------
// Description  : Set driver PWM
// Input Value  : Panel Apply PWM
// Output Value : void
//--------------------------------------------------
void UserCommonLocalDimmingSetPWMValue(WORD *pusPWM)
{
    BYTE ucI = 0;
    WORD pusNormPWM[_TOTAL_REGION];

    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
    {
        pusNormPWM[ucI] = ((DWORD)pusPWM[ucI] * _DEVICE_LED_DRIVER_PWM_MAX) / _PANEL_PWM_MAX;
    }
    DebugMessageHDR("pusNormPWM", pusNormPWM[0]);


#if(_LD_HDR10_BOOST_SUPPORT == _ON)
    if(GET_ON_LINE_CALIBRATION_STATUS() == _CALIBRATION_OFF)
    {
        ExternalDeviceInterfaceLedDriverPwmArrayBoostMode(pusNormPWM, g_ucLDBoostGain);
    }
    else
    {
        ExternalDeviceInterfaceLedDriverPwmArrayBoostMode(pusNormPWM, 100);
    }
#else
    ExternalDeviceInterfaceLedDriverPwmArray(pusNormPWM);
#endif
}

//--------------------------------------------------
// Description  : DCR to Lv PCHDR mode
// Input Value  : DCR 1*8 regions data
// Output Value : void
//--------------------------------------------------
void UserCommonLocalDimmingDCRToLvVerifyMode(BYTE *pucDCRData8bit, WORD *pusDCRToLV)
{
    BYTE ucI = 0;
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
    g_bLDBoostMod = _FALSE;
#endif

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

        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
        {
            usLightEnhanceCode = (pucDCRData8bit[ucI] * ucGainValue / 100);
            if(usLightEnhanceCode > 255)
            {
                usLightEnhanceCode = 255;
            }
            pucDCRData8bit[ucI] = usLightEnhanceCode;
        }
#endif

        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
        {
            pusDCRToLV[ucI] = tLDHDR2084Lv[pucDCRData8bit[ucI]];
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
            if(g_enumLDBoostMode == _LD_BOOST_KERNAL)
            {
                if(pusDCRToLV[ucI] > _PANEL_LV_MAX)
                {
                    g_bLDBoostMod = _TRUE;
                }
            }
#endif
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

                    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                    {
                        pusDCRToLV[ucI] = tLDSDRGamma22Lv[pucDCRData8bit[ucI]];
                    }

                    break;

                case _SDR_EBU_MODE:
                case _SDR_REC_709:

                    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                    {
                        pusDCRToLV[ucI] = tLDSDRGamma24Lv[pucDCRData8bit[ucI]];
                    }

                    break;

                case _SDR_DCI_P3:

                    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                    {
                        pusDCRToLV[ucI] = tLDSDRGamma26Lv[pucDCRData8bit[ucI]];
                    }

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

                    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                    {
                        pusDCRToLV[ucI] = tLDSDROGCCase1Lv[pucDCRData8bit[ucI]];
                    }

                    break;

                case _SDR_OGC_CASE_2:

                    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                    {
                        pusDCRToLV[ucI] = tLDSDROGCCase2Lv[pucDCRData8bit[ucI]];
                    }

                    break;

                case _SDR_OGC_CASE_3:

                    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                    {
                        pusDCRToLV[ucI] = tLDSDROGCCase3Lv[pucDCRData8bit[ucI]];
                    }

                    break;

                case _SDR_OGC_CASE_4:

                    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                    {
                        pusDCRToLV[ucI] = tLDSDROGCCase4Lv[pucDCRData8bit[ucI]];
                    }

                    break;

                case _SDR_OGC_CASE_5:

                    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                    {
                        pusDCRToLV[ucI] = tLDSDROGCCase5Lv[pucDCRData8bit[ucI]];
                    }

                    break;

                default:

                    break;
            }
        }
        else
        {
            for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
            {
                pusDCRToLV[ucI] = tLDSDRGamma22Lv[pucDCRData8bit[ucI]];
            }
        }
    }

    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
    {
        if(pusDCRToLV[ucI] > _PANEL_LV_MAX)
        {
            pusDCRToLV[ucI] = _PANEL_LV_MAX;
        }
    }
}

//--------------------------------------------------
// Description  : DCR to Lv NONEPCHDR mode
// Input Value  : DCR 1*8 regions data
// Output Value : void
//--------------------------------------------------
void UserCommonLocalDimmingDCRToLvNormalMode(BYTE *pucDCRData8bit, WORD *pusDCRToLV)
{
    BYTE ucI = 0;
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
    BYTE ucDarkSceneRegion = 0;
    WORD usMaxDCRLv = 0;
    g_ucMaxDCR = 0;
#endif
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
    g_bLDBoostMod = _FALSE;
#endif

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

        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
        {
            usLightEnhanceCode = (pucDCRData8bit[ucI] * ucGainValue / 100);
            if(usLightEnhanceCode > 255)
            {
                usLightEnhanceCode = 255;
            }
            pucDCRData8bit[ucI] = usLightEnhanceCode;
        }
#endif
        if(UserCommonHDRGetHDR10LvType() == _HDR10_MAX_MASTERING_LV_TYPE_NOTM)
        {
            for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
            {
                pusDCRToLV[ucI] = tLDHDR2084Lv[pucDCRData8bit[ucI]];
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
                if(g_enumLDBoostMode == _LD_BOOST_KERNAL)
                {
                    if(pusDCRToLV[ucI] > _PANEL_LV_MAX)
                    {
                        g_bLDBoostMod = _TRUE;
                    }
                }
#endif
            }
        }
        else
        {
            for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
            {
                pusDCRToLV[ucI] = tLDHDRToneMappingLv540[pucDCRData8bit[ucI]];
            }
        }
    }
    else
#endif
    {
#if((_LD_FREESYNC_MODE_SUPPORT == _ON) && (_FREESYNC_II_SUPPORT == _ON))
        if(UserCommonHDRGetFreeSyncIILDDisable() == _OFF)
        {
#if(_LD_FREESYNC_II_BOOST_SUPPORT == _ON)
            if(UserCommonHDRGetFreesynIIStatus() == _ON)
            {
                for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                {
                    pusDCRToLV[ucI] = tFREESYNCIILv[pucDCRData8bit[ucI]];
                    if(g_enumLDBoostMode == _LD_BOOST_KERNAL)
                    {
                        if(pusDCRToLV[ucI] > _PANEL_LV_MAX)
                        {
                            g_bLDBoostMod = _TRUE;
                        }
                    }
                }
            }
            else
#endif
            {
                switch(UserCommonHDRGetFreeSyncIIEOTFType())
                {
                    case _FREESYNC_II_EOTF_SRGB:
                    case _FREESYNC_II_EOTF_BT709:
                    case _FREESYNC_II_EOTF_GAMMA_22:

                        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                        {
                            pusDCRToLV[ucI] = tLDSDRGamma22Lv[pucDCRData8bit[ucI]];
                        }
                        break;

                    case _FREESYNC_II_EOTF_GAMMA_26:

                        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                        {
                            pusDCRToLV[ucI] = tLDSDRGamma26Lv[pucDCRData8bit[ucI]];
                        }
                        break;

                    default:
                        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                        {
                            pusDCRToLV[ucI] = tLDSDRGamma22Lv[pucDCRData8bit[ucI]];
                        }
                        break;
                }
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

                        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                        {
                            pusDCRToLV[ucI] = tLDSDRGamma22Lv[pucDCRData8bit[ucI]];
                        }

                        break;

                    case _SDR_EBU_MODE:
                    case _SDR_REC_709:

                        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                        {
                            pusDCRToLV[ucI] = tLDSDRGamma24Lv[pucDCRData8bit[ucI]];
                        }

                        break;

                    case _SDR_DCI_P3:

                        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                        {
                            pusDCRToLV[ucI] = tLDSDRGamma26Lv[pucDCRData8bit[ucI]];
                        }

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

                        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                        {
                            pusDCRToLV[ucI] = tLDSDROGCCase1Lv[pucDCRData8bit[ucI]];
                        }

                        break;

                    case _SDR_OGC_CASE_2:

                        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                        {
                            pusDCRToLV[ucI] = tLDSDROGCCase2Lv[pucDCRData8bit[ucI]];
                        }

                        break;

                    case _SDR_OGC_CASE_3:

                        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                        {
                            pusDCRToLV[ucI] = tLDSDROGCCase3Lv[pucDCRData8bit[ucI]];
                        }

                        break;

                    case _SDR_OGC_CASE_4:

                        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                        {
                            pusDCRToLV[ucI] = tLDSDROGCCase4Lv[pucDCRData8bit[ucI]];
                        }

                        break;

                    case _SDR_OGC_CASE_5:

                        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                        {
                            pusDCRToLV[ucI] = tLDSDROGCCase5Lv[pucDCRData8bit[ucI]];
                        }

                        break;

                    default:

                        break;
                }
            }
            else
            {
                for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
                {
                    pusDCRToLV[ucI] = tLDSDRGamma22Lv[pucDCRData8bit[ucI]];
                }
            }
        }
    }

    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
    {
#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_0)
        if((pusDCRToLV[ucI] < _PANEL_LV_MIN) && (pucDCRData8bit[ucI] != 0))
        {
            pusDCRToLV[ucI] = _PANEL_LV_MIN;
        }
#else

#if(_HDR10_SUPPORT == _ON)
        if((UserCommonHDRGetHDR10LvType() == _HDR10_MAX_MASTERING_LV_TYPE_NOTM) &&
           (UserCommonHDRGetHDR10Status() == _HDR10_ON))
        {
            if(pusDCRToLV[ucI] < _PANEL_LV_DARK_SCENE)
            {
                ucDarkSceneRegion++;
            }

            if(pusDCRToLV[ucI] > usMaxDCRLv)
            {
                usMaxDCRLv = pusDCRToLV[ucI];
            }
            if(pucDCRData8bit[ucI] > g_ucMaxDCR)
            {
                g_ucMaxDCR = pucDCRData8bit[ucI];
            }
        }
#endif
#endif
    }

#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
    if(ucDarkSceneRegion == _TOTAL_REGION)
    {
        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
        {
            if(pucDCRData8bit[ucI] != 0)
            {
                pusDCRToLV[ucI] = usMaxDCRLv;
            }
        }
        g_bDarkScene = _TRUE;
    }
    else
    {
        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
        {
            if((pusDCRToLV[ucI] < _PANEL_LV_DARK_SCENE) && (pucDCRData8bit[ucI] != 0))
            {
                pusDCRToLV[ucI] = _PANEL_LV_DARK_SCENE;
            }
        }
        g_bDarkScene = _FALSE;
    }
    DebugMessageHDR("g_bDarkScene", g_bDarkScene);
#endif
}

//--------------------------------------------------
// Description  : Smooth Lv process
// Input Value  : Target LV,
// Output Value : void
//--------------------------------------------------
void UserCommonLocalDimmingSmoothLv(WORD *pusSmoothLV, WORD *pusDCRToLV, BYTE ucSmoothLevel)
{
    BYTE ucI = 0;

#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
    if(g_enumDetectCTunnelPatternStatus == _LD_TUNNEL_PHASE2_PASS)
    {
        DebugMessageHDR("tunnel pattern", 0);
        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
        {
            pusSmoothLV[ucI] = _TUNNELPATTERN_LV;
        }
    }
    else
#endif
    {
        if(UserInterfaceGetPCHDRVerifyMode() == _LD_PCHDR_NORMAL_MODE)
        {
            WORD usSmoothLv = 0;
            usSmoothLv = ((DWORD)(100 -  ucSmoothLevel) * _PANEL_LV_MAX + 50) / 100;
            memcpy(pusSmoothLV, pusDCRToLV, _TOTAL_REGION * sizeof(pusDCRToLV[0]));
            for(ucI = 0; ucI < 7; ucI++)
            {
                if(pusSmoothLV[ucI] > (pusSmoothLV[ucI + 1] + usSmoothLv))
                {
                    pusSmoothLV[ucI + 1] = pusSmoothLV[ucI] - usSmoothLv;
                }
                if(pusSmoothLV[ucI + 1] > (pusSmoothLV[ucI] + usSmoothLv))
                {
                    pusSmoothLV[ucI] = pusSmoothLV[ucI + 1] - usSmoothLv;
                }
            }

            for(ucI = 6; ucI > 0; ucI--)
            {
                if(pusSmoothLV[ucI] > (pusSmoothLV[ucI - 1] + usSmoothLv))
                {
                    pusSmoothLV[ucI - 1] = pusSmoothLV[ucI] - usSmoothLv;
                }
                if(pusSmoothLV[ucI - 1] > (pusSmoothLV[ucI] + usSmoothLv))
                {
                    pusSmoothLV[ucI] = pusSmoothLV[ucI - 1] - usSmoothLv;
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : step Lv process
// Input Value  : Target LV,
// Output Value : void
//--------------------------------------------------
void UserCommonLocalDimmingStepToTarget(WORD *pusApplyLv, WORD *pusTargetLv, WORD *pusLastApplyLv, BYTE *pucDCRResult, BYTE *pucLastDCRResult)
{
    BYTE data ucI = 0;
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
    g_usLDBoostR = 32;
#endif

    for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
    {
        if(pucDCRResult[ucI] >= pucLastDCRResult[ucI])
        {
            if((pucLastDCRResult[ucI] == 0) &&
               ((g_pusDCRToLV[ucI] - g_pusLastDCRToLV[ucI]) >= (_PANEL_LV_MAX - _PANEL_LV_MIN)))
            {
                g_pusLDR[ucI] = 1024;
            }
            else
            {
                g_pusLDR[ucI] = tStepLDRTable[pucDCRResult[ucI] - pucLastDCRResult[ucI]];
            }
        }
        else
        {
            if((pucDCRResult[ucI] == 0) &&
               ((g_pusLastDCRToLV[ucI] - g_pusDCRToLV[ucI]) >= (_PANEL_LV_MAX - _PANEL_LV_MIN)))
            {
                g_pusLDR[ucI] = 1024;
            }
            else
            {
                g_pusLDR[ucI] = tStepLDRTable[pucLastDCRResult[ucI] - pucDCRResult[ucI]];
            }
        }

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
        if(g_pusLDR[ucI] == 1024)
        {
            g_usLDBoostR = 1024;
        }
#endif
        pusApplyLv[ucI] = ((((DWORD)g_pusLDR[ucI] * pusTargetLv[ucI]) + ((DWORD)(1024 - g_pusLDR[ucI]) * pusLastApplyLv[ucI])) + 512) / 1024;

        if(pusApplyLv[ucI] == pusLastApplyLv[ucI])
        {
            if(pusTargetLv[ucI] > pusApplyLv[ucI])
            {
                pusApplyLv[ucI] = pusApplyLv[ucI] + 1;
            }
            else if(pusTargetLv[ucI] < pusApplyLv[ucI])
            {
                pusApplyLv[ucI] = pusApplyLv[ucI] - 1;
            }
        }
        pusLastApplyLv[ucI] = pusApplyLv[ucI];
        pucLastDCRResult[ucI] = pucDCRResult[ucI];
        g_pusLastDCRToLV[ucI] = g_pusDCRToLV[ucI];
    }
}

#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Tunnel Pattern HLW
// Input Value  : _FUNCTION_ON/_FUNCTION_OFF
// Output Value : NONE
//--------------------------------------------------
void UserCommonLocalDimmingSetHLWDetectTunnelPattern(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        // set HLW
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
        ScalerColorHLWBRICTSAdjust(_BRI_CON_A_ON_FULL_WINDOW, _DB_APPLY_NONE);
#endif

#if(_DCC_FUNCTION == _ON)
        ScalerColorHLWDCCAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NONE);
#endif

#if(_GAMMA_FUNCTION == _ON)
        ScalerColorHLWOutputGammaAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NONE);
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
        ScalerColorHLWSRGBAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NONE);
#endif

#if(_IAPS_SUPPORT == _ON)
        ScalerColorHLWIAPSGainAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NONE);
#endif

#if(_ICM_SUPPORT == _ON)
        ScalerColorHLWICMAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NONE);
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
        ScalerColorHLWUltraVividAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NONE);
#endif

#if(_YPEAKING_SUPPORT == _ON)
        ScalerColorHLWYpeakingAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NONE);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
        ScalerColorHLWPanelUniformityAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NONE);
#endif

#if(_PCM_FUNCTION == _ON)
        ScalerColorHLWPCMAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NONE);
#endif

#if(_RGB_3D_GAMMA == _ON)
        ScalerColorHLWRGB3DGammaAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NONE);
#endif
        // For tunnel pattern HLW
        ScalerColorHLWDCRAdjust(_HLW_FULL_WINDOW, _DB_APPLY_POLLING);
        ScalerColorHLWDDomainAdjust(_PANEL_DH_WIDTH * 4 / 10 + 2, _PANEL_DH_WIDTH * 2 / 10 - 4, _PANEL_DV_HEIGHT * 4 / 10 + 2, _PANEL_DV_HEIGHT * 2 / 10 - 4);
        ScalerColorHLWBorderEnable(_OFF, _OFF, _OFF, _OFF);
        ScalerColorHLWEnable(_FUNCTION_ON, _DB_APPLY_NO_POLLING);

        // set DCR thd
        ScalerColorDCRAdjust(_TUNNELPATTERN_DCR_THESHOLD1, _TUNNELPATTERN_DCR_THESHOLD2, _MEASURE_AVERAGE);
    }
    else
    {
        // recover HLW
        ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_NO_POLLING);
        UserInterfaceTunnelPatternDetectOff();

        g_enumDetectCTunnelPatternStatus = _LD_NONE_TUNNEL_PATTERN;
        g_ucWaitForStable = 0;
    }
}

//--------------------------------------------------
// Description  : Detect Tunnel Pattern
// Input Value  : DCRLDData
// Output Value : NONE
//--------------------------------------------------
void UserCommonLocalDimmingDetectTunnelPattern(BYTE *pucDCRLDData8bit)
{
    BYTE ucI = 0;
    DWORD ulAboveTh1Num = 0;
    DWORD ulAboveTh2Num = 0;

    /**************** phase 1 **********************/
    if(g_enumDetectCTunnelPatternStatus != _LD_TUNNEL_PHASE1_PASS)
    {
        ulAboveTh1Num = ScalerColorDCRLocalDimmingReadTHDResult(_DCR_LD_ABOVE_TH1_NUM);
        ulAboveTh2Num = ScalerColorDCRLocalDimmingReadTHDResult(_DCR_LD_ABOVE_TH2_NUM);

        // win 0 ~ win 7 are the same
        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
        {
            if((pucDCRLDData8bit[ucI] > _TUNNELPATTERN_LDREGION_ABOVE_FACTOR) || (pucDCRLDData8bit[ucI] < _TUNNELPATTERN_LDREGION_BELOW_FACTOR))
            {
                DebugMessageHDR("LD", pucDCRLDData8bit[ucI]);
                if(g_enumDetectCTunnelPatternStatus == _LD_TUNNEL_PHASE2_PASS)
                {
                    g_ucWaitForStable++;
                    if(g_ucWaitForStable > _TUNNELPATTERN_FAIL_COUNT)
                    {
                        g_ucWaitForStable = 0;
                        g_enumDetectCTunnelPatternStatus = _LD_NONE_TUNNEL_PATTERN;
                        return;
                    }
                }
                else
                {
                    g_enumDetectCTunnelPatternStatus = _LD_NONE_TUNNEL_PATTERN;
                    return;
                }
            }
        }

        // the number of brightness and black
        if((ulAboveTh1Num > _TUNNELPATTERN_PHASE1_THD1_ABOVE_FACTOR) || (ulAboveTh1Num < _TUNNELPATTERN_PHASE1_THD1_BELOW_FACTOR) || (ulAboveTh2Num > _TUNNELPATTERN_PHASE1_THD2_ABOVE_FACTOR) || (ulAboveTh2Num < _TUNNELPATTERN_PHASE1_THD2_BELOW_FACTOR))
        {
            DebugMessageHDR("phase 1 fail_brightness", ulAboveTh1Num);
            DebugMessageHDR("phase 1 fail_black", ulAboveTh2Num);
            if(g_enumDetectCTunnelPatternStatus == _LD_TUNNEL_PHASE2_PASS)
            {
                g_ucWaitForStable++;
                if(g_ucWaitForStable > _TUNNELPATTERN_FAIL_COUNT)
                {
                    g_ucWaitForStable = 0;
                    g_enumDetectCTunnelPatternStatus = _LD_NONE_TUNNEL_PATTERN;
                    return;
                }
            }
            else
            {
                g_enumDetectCTunnelPatternStatus = _LD_NONE_TUNNEL_PATTERN;
                return;
            }
        }

        /**************** phase 2 **********************/
        if(g_enumDetectCTunnelPatternStatus != _LD_TUNNEL_PHASE2_PASS)
        {
            g_ucWaitForStable++;
            if(g_ucWaitForStable > _TUNNELPATTERN_PHASE1_COUNT)
            {
                g_enumDetectCTunnelPatternStatus = _LD_TUNNEL_PHASE1_PASS;
                ScalerColorHLWDCRAdjust(_HLW_INSIDE_WINDOW, _DB_APPLY_NO_POLLING);
                g_ucWaitForStable = 0;
            }
        }
    }
    else
    {
        ulAboveTh2Num = ScalerColorDCRLocalDimmingReadTHDResult(_DCR_LD_ABOVE_TH2_NUM);

        if(ulAboveTh2Num != 0)
        {
            DebugMessageHDR("phass 2 fail", ulAboveTh2Num);
            g_ucWaitForStable++;
            if(g_ucWaitForStable > _TUNNELPATTERN_PHASE2_COUNT)
            {
                g_enumDetectCTunnelPatternStatus = _LD_NONE_TUNNEL_PATTERN;
                ScalerColorHLWDCRAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NO_POLLING);
                g_ucWaitForStable = 0;
            }
        }
        else
        {
            g_enumDetectCTunnelPatternStatus = _LD_TUNNEL_PHASE2_PASS;
            ScalerColorHLWDCRAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NO_POLLING);
            g_ucWaitForStable = 0;
        }
    }
}
#endif

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Local dimming boost gain value
// Input Value  : DCRToLV, BoostGain
// Output Value : void
//--------------------------------------------------
void UserCommonLocalDimmingLvBoostGainValue(BYTE *pucBoostGain)
{
    BYTE ucIdealBoostGain = 100;

    if(g_bLDBoostMod == _TRUE)
    {
        ucIdealBoostGain = (DWORD)_PANEL_LV_BOOST_MAX * 100 / _PANEL_LV_MAX;
    }

    *pucBoostGain = ((((DWORD)g_usLDBoostR * ucIdealBoostGain) + ((DWORD)g_ucLastLDBoostGain * (1024 - g_usLDBoostR))) + 512) / 1024;

    if(*pucBoostGain == g_ucLastLDBoostGain)
    {
        if(ucIdealBoostGain > *pucBoostGain)
        {
            *pucBoostGain = *pucBoostGain + 1;
        }
        else if(ucIdealBoostGain < *pucBoostGain)
        {
            *pucBoostGain = *pucBoostGain - 1;
        }
    }

    g_ucLastLDBoostGain = *pucBoostGain;
}
//--------------------------------------------------
// Description  : whether user can change boost gain value
// Input Value  : void
// Output Value : _LD_BOOST_KERNAL/ _LD_BOOST_USER
//--------------------------------------------------
EnumLDBoostMode UserCommonLocalDimmingGetBoostMode(void)
{
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonHDRGetHDR10LvType() == _HDR10_MAX_MASTERING_LV_TYPE_NOTM)
    {
        return _LD_BOOST_KERNAL;
    }
#endif

#if(_LD_FREESYNC_II_BOOST_SUPPORT == _ON)
    if(UserCommonHDRGetFreesynIIStatus() == _ON)
    {
        return _LD_BOOST_KERNAL;
    }
#endif

    return _LD_BOOST_USER;
}
#endif // End of #if(_LD_HDR10_BOOST_SUPPORT == _ON)

#if((_ASPECT_RATIO_SUPPORT == _ON) || (_ASPECT_ORIGINAL_MODE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : adjust tcon setting when adjust Aspect Ratio
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonLocalDimmingAspectRatioAdjust(void)
{
    ScalerColorDCRLocalDimmingSetTCon(_LOCAL_DIMMING_1X8_MODE);
}
#endif // End of #if((_ASPECT_RATIO_SUPPORT == _ON) || (_ASPECT_ORIGINAL_MODE_SUPPORT == _ON))

#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
//--------------------------------------------------
// Description  :
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonLocalDimmingDarkSceneGain(void)
{
    WORD usIdealSRGBGain = 512;
    BYTE ucI = 0;
    BYTE pucSRGBMatrix[24] = {0};
    WORD usDarkSceneStep = g_pusLDR[0];

    if(g_bDarkScene == _TRUE)
    {
        usIdealSRGBGain = tLDDarkGain[g_ucMaxDCR];
    }
    else
    {
        usIdealSRGBGain = 512;
    }

    for(ucI = 1; ucI < _TOTAL_REGION; ucI++)
    {
        if(g_pusLDR[ucI] > usDarkSceneStep)
        {
            usDarkSceneStep = g_pusLDR[ucI];
        }
    }
    DebugMessageHDR("g_ucMaxDCR", g_ucMaxDCR);
    DebugMessageHDR("tLDDarkGain", tLDDarkGain[g_ucMaxDCR]);
    DebugMessageHDR("usDarkSceneStep", usDarkSceneStep);

    g_usSRGBGain = ((((DWORD)usDarkSceneStep * usIdealSRGBGain) + ((DWORD)g_usLastSRGBGain * (1024 - usDarkSceneStep))) + 512) / 1024;


    if(g_usSRGBGain == g_usLastSRGBGain)
    {
        if(usIdealSRGBGain > g_usSRGBGain)
        {
            g_usSRGBGain = g_usSRGBGain + 1;
        }
        else if(usIdealSRGBGain < g_usSRGBGain)
        {
            g_usSRGBGain = g_usSRGBGain - 1;
        }
    }

    if(g_usSRGBGain > 870)
    {
        g_usSRGBGain = 870;
    }
    else if(g_usSRGBGain < 512)
    {
        g_usSRGBGain = 512;
    }

    DebugMessageHDR("g_usSRGBGain", g_usSRGBGain);

    g_usLastSRGBGain = g_usSRGBGain;

    for(ucI = 0; ucI < 9; ucI++)
    {
        SDWORD lSRGBApplylValue = 0;
        SWORD shValue = (((WORD)(g_pucSRGBMatrixOriginal[2 * ucI] & 0x01) << 15) |
                         ((WORD)g_pucSRGBMatrixOriginal[(2 * ucI) + 1] << 7) |
                         ((g_pucSRGBMatrixOriginal[2 * ucI] & 0xE0) >> 1));
        shValue >>= 4;

        if((ucI % 4) == 0)
        {
            lSRGBApplylValue = (((SDWORD)shValue * (SDWORD)g_usSRGBGain + 0x100) >> 9) +
                               ((((SDWORD)g_usSRGBGain * 0x200) + 0x100) >> 9) - 0x200;
        }
        else
        {
            lSRGBApplylValue = ((SDWORD)shValue * (SDWORD)g_usSRGBGain + 0x100) >> 9;
        }

        if(lSRGBApplylValue > 0x7CC)
        {
            lSRGBApplylValue = 0x7CC;
        }

        pucSRGBMatrix[2 * ucI] = ((lSRGBApplylValue & 0x07) << 5) | ((lSRGBApplylValue >> 11) & 0x01);
        pucSRGBMatrix[2 * ucI + 1] = (lSRGBApplylValue >> 3) & 0xFF;
    }

    ScalerColorLDSRGBAdjust(pucSRGBMatrix, _SRGB_3_BIT_SHIFT_LEFT);
}

//--------------------------------------------------
// Description  :
// Input Value  : Enable/ Disable
// Output Value : void
//--------------------------------------------------
void UserCommonLocalDimmingDarkSceneInitial(bit bEN)
{
    BYTE pucSRGBMatrixOriginal[24] = {0};
    BYTE ucDecimalNum = 0;
    BYTE ucShiftNum = 0;
    BYTE ucI = 0;
    SWORD shSRGBValueOriginal = 0;
    g_ucMaxDCR = 0;
    g_usLastSRGBGain = 512;
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
                case _SDR_SMPTE_C:
                    UserCommonFlashRead(_OGC_FLASH_BANK, _OCC_SMPTEC_ADDRESS, 18, pucSRGBMatrixOriginal);
                    ucDecimalNum = 12;
                    break;

                case _SDR_DISPLAYP3:
                    UserCommonFlashRead(_OGC_FLASH_BANK, _OCC_DISPLAYP3_ADDRESS, 18, pucSRGBMatrixOriginal);
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

    if(bEN == _ENABLE)
    {
        for(ucI = 0; ucI < 9; ucI++)
        {
            SWORD shValue = (((WORD)(pucSRGBMatrixOriginal[2 * ucI] & 0x01) << 15) |
                             ((WORD)pucSRGBMatrixOriginal[(2 * ucI) + 1] << 7) |
                             ((pucSRGBMatrixOriginal[2 * ucI] & 0xE0) >> 1));
            shValue >>= 4;

            shSRGBValueOriginal = shValue >> ucShiftNum;

            g_pucSRGBMatrixOriginal[2 * ucI] = ((shSRGBValueOriginal & 0x07) << 5) | ((shSRGBValueOriginal >> 11) & 0x01);
            g_pucSRGBMatrixOriginal[2 * ucI + 1] = (shSRGBValueOriginal >> 3) & 0xFF;
        }
        ScalerColorSRGBAdjust(g_pucSRGBMatrixOriginal, _SRGB_3_BIT_SHIFT_LEFT);
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
#endif  // End of  #if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)

#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)

