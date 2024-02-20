/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerMbrInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#define _MBR_DRR_COMP_DUTY_OFFSET               (0)

#define _MBR_DRR_FLICKER_IVF_LO                 (750)
#define _MBR_DRR_FLICKER_IVF_HI                 (800)
#define _MBR_DRR_SWITCH_FRAME_COUNT             (100)
#define _MBR_DRR_TRANSITION_FRAME_CNT           (2)
#define _MBR_DRR_AVG_IVF_FRAME_CNT              (4)

#define GET_MBR_DVTOTAL()                       (g_usMbrDVTotal)
#define SET_MBR_DVTOTAL(x)                      (g_usMbrDVTotal = (x))

#define GET_MBR_BACKLIGHT_MODE()                (g_enumMbrBacklightMode)
#define GET_MBR_BACKLIGHT_MODE_EXINT0()         (g_enumMbrBacklightMode)
#define SET_MBR_BACKLIGHT_MODE(x)               (g_enumMbrBacklightMode = (x))

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#define GET_MBR_DRR_VFREQ_AVG()                 (g_usMbrDrrVFreq_avg)
#define SET_MBR_DRR_VFREQ_AVG(x)                (g_usMbrDrrVFreq_avg = (x))
#define SET_MBR_DRR_VFREQ_AVG_EXINT0(x)         (g_usMbrDrrVFreq_avg = (x))

#define GET_MBR_DRR_STEP_CHG_CNT()              (g_ucMbrDrrStepChangeCnt)
#define SET_MBR_DRR_STEP_CHG_CNT(x)             (g_ucMbrDrrStepChangeCnt = (x))

#define GET_MBR_DRR_VFREQ(x)                    (g_pusMbrDrrVFreq[x])
#define SET_MBR_DRR_VFREQ(x, y)                 (g_pusMbrDrrVFreq[x] = (y))
#define SET_MBR_DRR_VFREQ_EXINT0(x, y)          (g_pusMbrDrrVFreq[x] = (y))

#define GET_MBR_DRR_BACKLIGHT_MODE()            (g_enumMbrDrrBacklightMode)
#define SET_MBR_DRR_BACKLIGHT_MODE(x)           (g_enumMbrDrrBacklightMode = (x))

#define GET_MBR_DRR_SAFE_CNT()                  (g_usMbrDrrSafeCount)
#define SET_MBR_DRR_SAFE_CNT()                  (g_usMbrDrrSafeCount = MINOF(g_usMbrDrrSafeCount + 1, 0xFFFF))
#define SET_MBR_DRR_SAFE_CNT_EXINT0()           (g_usMbrDrrSafeCount = MINOF(g_usMbrDrrSafeCount + 1, 0xFFFF))
#define CLR_MBR_DRR_SAFE_CNT()                  (g_usMbrDrrSafeCount = 0)
#define CLR_MBR_DRR_SAFE_CNT_EXINT0()           (g_usMbrDrrSafeCount = 0)

#define GET_MBR_DRR_TCON_TOGGLE_TIME()          (g_ucMbrDrrTconToggleTime)
#define SET_MBR_DRR_TCON_TOGGLE_TIME(x)         (g_ucMbrDrrTconToggleTime = (x))

#define GET_MBR_DRR_HW_SUPPORT()                (g_bMbrDrrHWSupport)
#define SET_MBR_DRR_HW_SUPPORT(x)               (g_bMbrDrrHWSupport = (x))
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern WORD g_usMbrDVTotal;
extern EnumMbrBacklightMode g_enumMbrBacklightMode;
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern EnumMbrDrrBacklightMode g_enumMbrDrrBacklightMode;
extern WORD g_pusMbrDrrVFreq[_MBR_DRR_AVG_IVF_FRAME_CNT];
extern volatile WORD g_usMbrDrrVFreq_avg;
extern volatile WORD g_usMbrDrrSafeCount;
extern BYTE g_ucMbrDrrStepChangeCnt;
extern BYTE g_ucMbrDrrTconToggleTime;
extern bit g_bMbrDrrHWSupport;
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern EnumMbrBacklightMode ScalerMbrCheckBacklightMode(EnumMbrBacklightMode enumBacklightMode);
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void ScalerMbrDrrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
extern void ScalerMbrSetTconToggleSequence(BYTE ucTconEnd, BYTE ucDuty, WORD usHTotal);
extern void ScalerMbrDrrStepChange(BYTE ucTcon, WORD usStrobePeriod, WORD usStrobePeriod_prev, BYTE ucDuty, BYTE ucPosition);
extern void ScalerMbrDrrAdjust(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
extern void ScalerMbrDrrClearSetting(BYTE ucTcon);
extern void ScalerMbrSetIntEnable(EnumMbrBacklightMode enumMbrBacklightMode, bit bEnable);
extern WORD ScalerMbrGetDHFreq(void);
extern void ScalerMbrIntHandler_EXINT0(void);
#endif

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void ScalerMbrRtkAdvMbrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
#endif
#endif

