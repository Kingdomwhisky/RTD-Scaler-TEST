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
// ID Code      : UserCommonLocalDimmingInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_LOCAL_DIMMING_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_PANEL_REGION_MODE == _LD_1X8_MODE)
#define _TOTAL_REGION                               8

#elif(_PANEL_REGION_MODE == _LD_2X8_MODE)
#define _TOTAL_REGION                               16

#endif // End of #if(_PANEL_REGION_MODE == _LD_1X8_MODE)


#define _FRAME_NUMBER_TO_TARGET                     30

//--------------------------------------------------
// PWM Smooth Level
//--------------------------------------------------
#ifndef _NODE_CLASS_NUMBER
#if(_PANEL_DH_WIDTH * _PANEL_DV_HEIGHT <= (2560 * 1440))
#define _NODE_CLASS_NUMBER                          2
#else
#define _NODE_CLASS_NUMBER                          10
#endif
#endif

#define _GROUP_NODE_NUMBER                          ((_PANEL_UNIFORMITY_LD_HOR_GRIDS * _PANEL_UNIFORMITY_LD_VER_GRIDS) / (_NODE_CLASS_NUMBER - 1))
#define _REMAINDER_NODE_NUMBER                      ((_PANEL_UNIFORMITY_LD_HOR_GRIDS * _PANEL_UNIFORMITY_LD_VER_GRIDS) - (_NODE_CLASS_NUMBER - 1) * _GROUP_NODE_NUMBER)

//--------------------------------------------------
// PWM Smooth Level
//--------------------------------------------------
#define _PANEL_PWM_DELTA_MAX                        (_PANEL_PWM_MAX - _PANEL_PWM_MIN)
#define _PANEL_PWM_SMOOTH_SECTION                   100
#define _PANEL_PWM_STEP_TO_GOLBAL                   ((_PANEL_PWM_DELTA_MAX) / (_PANEL_PWM_RECOVER_ADJUST_STEPS))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _LD_DISABLE,
    _LD_ENABLE,

} EnumLDStatus;

typedef enum
{
    _LD_GAMMA_18 = 0,
    _LD_GAMMA_20,
    _LD_GAMMA_22,
    _LD_GAMMA_24,
    _LD_GAMMA_26,
    _LD_GAMMA_28,
    _LD_GAMMA_30,

    _LD_PCM_SRGB,
    _LD_PCM_ADOBE,

} EnumLDSDRColorMode;

typedef enum
{
    _LD_ACTION_MODE_NORNAL,
    _LD_ACTION_MODE_DIMMING,

} EnumLDActionMode;

typedef enum
{
    _LD_PCHDR_VERIFY_MODE,
    _LD_PCHDR_NORMAL_MODE,
} EnumLDPCHDRMode;

typedef enum
{
    _PANEL_UNIFORMITY_ON,
    _PANEL_UNIFORMITY_OFF,
} EnumUniformityStatus;

#if(_LOCAL_DIMMING_SUPPORT == _ON)
#define GET_LD_ACTION_MODE_STATUS()                 (g_stLocalDimmingInfo.b1LocalDimmingActiveMode)
#define SET_LD_ACTION_MODE_STATUS(x)                (g_stLocalDimmingInfo.b1LocalDimmingActiveMode = (x))

#else
#define GET_LD_ACTION_MODE_STATUS()                 (_LD_CALIBRATION_OFF)
#define SET_LD_ACTION_MODE_STATUS(x)                (_nop_())

#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)

#if(_LOCAL_DIMMING_SUPPORT == _ON)
typedef struct
{
    BYTE b1LocalDimmingActiveMode              : 1;

}StructLocalDimmingInfo;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_LOCAL_DIMMING_SUPPORT == _ON)
extern StructLocalDimmingInfo g_stLocalDimmingInfo;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonLocalDimmingHandler(void);
extern EnumLDStatus UserCommonLocalDimmingGetEnableStatus(void);
extern void UserCommonLocalDimmingAdjust(void);
extern void UserCommonLocalDimmingDCRToLv(BYTE *pucDCRData8bit, WORD *pusDCRToLV);
extern void UserCommonLocalDimmingSetPWM1x8(WORD *pusApplyLv, WORD *pusApplyPWM);
extern void UserCommonLocalDimmingUniformityNodetoGainTable(WORD *pusUniformityGainNode, BYTE *pucUnifotmityGainTable, BYTE ucNodeClass);
extern void UserCommonLocalDimmingInitialSetting(bit bEn);
extern void UserCommonLocalDimmingSetLastPWMFull(void);
extern void UserCommonLocalDimmingStepToGDHDR(void);
extern void UserCommonLocalDimmingGetNodeLV1X8(WORD *pusUniformityGainNode, WORD *pusPWM, BYTE ucNodeClass);
extern void UserCommonLocalDimmingEnable(bit bEn);
extern void UserCommonLocalDimmingSetPWMValue(WORD *pusPWM);
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
extern EnumLDBoostMode UserCommonLocalDimmingGetBoostMode(void);
#endif

#if((_ASPECT_RATIO_SUPPORT == _ON) || (_ASPECT_ORIGINAL_MODE_SUPPORT == _ON))
extern void UserCommonLocalDimmingAspectRatioAdjust(void);
#endif

#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)
