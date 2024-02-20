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
// ID Code      : ScalerMbr.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MBR__

#include "ScalerFunctionInclude.h"

//--------------------------------------------------
// Note Message For RTK Adv MBR Enable
//--------------------------------------------------
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#warning "NOTE: RTK Adv MBR support is ON, Memory BW may be affected. Please check with SD!!!"
#endif
#endif

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
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
WORD g_usMbrDVTotal;
EnumMbrBacklightMode g_enumMbrBacklightMode = _BACKLIGHT_MODE_CONSTANT;

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
EnumMbrDrrBacklightMode g_enumMbrDrrBacklightMode;
WORD g_pusMbrDrrVFreq[_MBR_DRR_AVG_IVF_FRAME_CNT];
volatile WORD g_usMbrDrrSafeCount;
volatile WORD g_usMbrDrrVFreq_avg;
BYTE g_ucMbrDrrStepChangeCnt;
BYTE g_ucMbrDrrVFreqIndex;
BYTE g_ucMbrDrrTconToggleTime;
bit g_bMbrDrrHWSupport;
#endif
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
EnumMbrBacklightMode ScalerMbrCheckBacklightMode(EnumMbrBacklightMode enumBacklightMode);
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
void ScalerMbrDrrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
void ScalerMbrSetTconToggleSequence(BYTE ucTconEnd, BYTE ucDuty, WORD usHTotal);
void ScalerMbrDrrStepChange(BYTE ucTcon, WORD usStrobePeriod, WORD usStrobePeriod_prev, BYTE ucDuty, BYTE ucPosition);
void ScalerMbrDrrAdjust(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
void ScalerMbrDrrClearSetting(BYTE ucTcon);
void ScalerMbrSetIntEnable(EnumMbrBacklightMode enumMbrBacklightMode, bit bEnable);
WORD ScalerMbrGetDHFreq(void);
void ScalerMbrIntHandler_EXINT0(void);
#endif
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
void ScalerMbrRtkAdvMbrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Kernel check/overwrite backlight mode if the mode
//                doesn't even support
// Input Value  : enumBacklightMode - user MBR backlight mode
// Output Value : altered backlight mode
//--------------------------------------------------
EnumMbrBacklightMode ScalerMbrCheckBacklightMode(EnumMbrBacklightMode enumBacklightMode)
{
    // If DRR enable but DRR MBR not supported, use constant backlight
#if((_FREESYNC_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _OFF))
    if(enumBacklightMode != _BACKLIGHT_MODE_CONSTANT)
    {
        if(ScalerSyncGetFREESYNCEnable() == _TRUE)
        {
            return _BACKLIGHT_MODE_CONSTANT;
        }
    }
#endif

    // If DRR MBR is selected but FW/DRR status/HW do not support, use constant backlight
    if(enumBacklightMode == _BACKLIGHT_MODE_STROBE_DRR_MBR)
    {
#if((_FREESYNC_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
        if((ScalerSyncGetFREESYNCEnable() == _DISABLE) || (GET_MBR_DRR_HW_SUPPORT() == _FALSE))
        {
            return _BACKLIGHT_MODE_CONSTANT;
        }
#else
        return _BACKLIGHT_MODE_CONSTANT;
#endif
    }

    // If RTK Adv MBR is selected but FW/kernel status do not support, use constant backlight
    if(enumBacklightMode == _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR)
    {
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        if(ScalerMbrGetAdvMbrStatus() == _DISABLE)
        {
            return _BACKLIGHT_MODE_CONSTANT;
        }
#else
        return _BACKLIGHT_MODE_CONSTANT;
#endif
    }

    return enumBacklightMode;
}
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate & Set TCON Parameters for DRR MBR
// Input Value  : ucTcon - TCON Number
//                ucBacklightDuty - User OSD Backlight Duty Setting
//                ucBacklightPos - User OSD Backlight Position Setting
//                bLightCtrl - Backlight ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl)
{
    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        WORD usDVTotal = 0;
        WORD usDENStop = 0;
        WORD usStrobeVWidth = 0;
        WORD usStrobeVPos = 0;
        WORD usDHTotal = 0;

        usDVTotal = GET_MBR_DVTOTAL();
        ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H, 2, &pData[0], _AUTOINC);
        usDENStop = ((pData[0] & 0x1F) << 8) | (pData[1]);
        usStrobeVWidth = (WORD)((DWORD)ucBacklightDuty * GET_MBR_DVTOTAL() / 100L);
        usStrobeVPos = MINOF((WORD)((DWORD)ucBacklightPos * GET_MBR_DVTOTAL() / 100L), usDENStop - usStrobeVWidth); // we dont want the strobe to exceed DEN Stop

        // Toggle Setting
        usDHTotal = GET_DIS_TIMING_GEN_H_TOTAL();
        ScalerMbrSetTconToggleSequence(ucTcon - 2, ucBacklightDuty + _MBR_DRR_COMP_DUTY_OFFSET, usDHTotal);

        // Compensation Setting
        ScalerTconAdjustByIndex(ucTcon - 1, 0x0000, 0x1FFF, 0x0000, usDVTotal);
        ScalerTconInvEnableByIndex(ucTcon - 1, _ENABLE);
        ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)(ucTcon - 1), _TCON_LOGICAL_OP_AND, _ENABLE);
        ScalerTconEnableByIndex(ucTcon - 1, _ENABLE);

        // Strobe Setting
        if(ucBacklightDuty == 100)
        {
            ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
        }
        else
        {
            ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, usStrobeVPos, (usStrobeVPos + usStrobeVWidth));
        }
        ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTcon, _TCON_LOGICAL_OP_OR, _ENABLE);
        ScalerTconEnableByIndex(ucTcon, _ENABLE);

        SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_STROBE);
        DebugMessageScaler("MBR: DRR Ctrl ON", 0);
    }
    else
    {
        // Setting in _LIGHT_CONTROL_OFF case
        ScalerTconEnableByIndex(ucTcon, _DISABLE);
        SET_MBR_DRR_BACKLIGHT_MODE(_MBR_DRR_MODE_OFF);
        DebugMessageScaler("MBR: DRR Ctrl OFF", 0);
    }
}

//--------------------------------------------------
// Description  : Calculate TCON Setting for Division of Frequency
// Input Value  : enumOutputTcon - Selected TCON Number
//                ucDuty - Final Output Duty Ratio (x/100)
//                usHTotal - Current Timing HTotal
//                usHFreq - Current Timing H-frequency
//                usMaxFreq - Current Timing(DRR) Max Frequency
// Output Value : None
//--------------------------------------------------
void ScalerMbrSetTconToggleSequence(BYTE ucTconEnd, BYTE ucDuty, WORD usHTotal)
{
    BYTE ucToggleTimeTotal = 0;
    BYTE ucToggleTime = 0;
    BYTE ucTconStart = ucTconEnd;

    ucToggleTimeTotal = GET_MBR_DRR_TCON_TOGGLE_TIME();

    DebugMessageScaler("MBR: ucToggleTimeTotal", ucToggleTimeTotal);

    // Calculate & Set Toggle Operation Sequence
    for(ucToggleTime = 0; ucToggleTime < ucToggleTimeTotal; ucToggleTime++)
    {
        if(ucTconStart < _TCON3)
        {
            break;
        }

        if(ucDuty == 50)
        {
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTconStart, _TCON_TOGGLE_OP_NORMAL, _ENABLE);
            ScalerTconEnableByIndex(ucTconStart, _ENABLE);
        }
        else if(ucDuty < 50)
        {
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTconStart, _TCON_TOGGLE_OP_AND, _ENABLE);
            ScalerTconEnableByIndex(ucTconStart, _ENABLE);
            ucDuty *= 2;
        }
        else // ucDuty > 50
        {
            ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTconStart, _TCON_TOGGLE_OP_OR, _ENABLE);
            ScalerTconEnableByIndex(ucTconStart, _ENABLE);
            ucDuty = 2 * (ucDuty - 50);
        }

        DebugMessageScaler("MBR: ucTconStart", ucTconStart);
        ucTconStart--;
    }

    // Set the Original TCON
    ScalerTconAdjustByIndex(ucTconStart, 0x0000, (DWORD)usHTotal * ucDuty / 100L, 0x0000, 0x3FFF);
    ScalerTconEnableByIndex(ucTconStart, _ENABLE);
}

//--------------------------------------------------
// Description  : By step change the backlight parameters
// Input Value  : ucTcon - Output TCON number
//                enumMode - Backlight mode(change direction)
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrStepChange(BYTE ucTcon, WORD usStrobePeriod, WORD usStrobePeriod_prev, BYTE ucDuty, BYTE ucPosition)
{
    WORD usStrobeVWidth = 0; // Backlight ON lines
    WORD usStrobeVPos = 0; // Backlight ON Position (lines)
    WORD usDENStop = 0;

    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H, 2, &pData[0], _AUTOINC);
    usDENStop = ((pData[0] & 0x1F) << 8) | (pData[1]);

    // Adjust Strobe
    usStrobeVWidth = (WORD)((DWORD)ucDuty * usStrobePeriod / 100L);
    usStrobeVPos = MINOF((WORD)((DWORD)ucPosition * usStrobePeriod / 100L), MINOF(usStrobePeriod, usDENStop) - usStrobeVWidth);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    if(ucDuty == 100)
    {
        ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
    }
    else
    {
        ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, usStrobeVPos, (usStrobeVPos + usStrobeVWidth));
    }

    // Adjust Compensation
    if(usStrobePeriod_prev >= usDENStop)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
    ScalerTconAdjustByIndex((ucTcon - 1), 0x0000, 0x1FFF, 0x0000, usStrobePeriod);
}

//--------------------------------------------------
// Description  : Adjust DRR MBR Parameters
// Input Value  : ucTcon - TCON Number
//                ucBacklightDuty - User OSD Backlight Duty Setting
//                ucBacklightPos - User OSD Backlight Position Setting
//                bLightCtrl - Backlight ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrAdjust(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl)
{
    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        WORD usDENStop = 0;
        WORD usStrobeVWidth = 0;
        WORD usStrobeVPos = 0;
        WORD usDHTotal = 0;

        ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H, 2, &pData[0], _AUTOINC);
        usDENStop = ((pData[0] & 0x1F) << 8) | (pData[1]);
        usStrobeVWidth = (WORD)((DWORD)ucBacklightDuty * GET_MBR_DVTOTAL() / 100L);
        usStrobeVPos = MINOF((WORD)((DWORD)ucBacklightPos * GET_MBR_DVTOTAL() / 100L), usDENStop - usStrobeVWidth); // we dont want the strobe to exceed DEN Stop
        usDHTotal = GET_DIS_TIMING_GEN_H_TOTAL();

        // Adjust Toggle Setting
        ScalerMbrSetTconToggleSequence(ucTcon - 2, ucBacklightDuty + _MBR_DRR_COMP_DUTY_OFFSET, usDHTotal);

        // Adjust Strobe
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        if(ucBacklightDuty == 100)
        {
            ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
        }
        else
        {
            ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x1FFF, usStrobeVPos, (usStrobeVPos + usStrobeVWidth));
        }
    }
    else
    {
        ScalerTconAdjustByIndex(ucTcon - 1, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
        ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x0000, 0x0000, 0x0000);
    }
}

//--------------------------------------------------
// Description  : Disable DRR MBR unused setting
// Input Value  : ucTcon -> PCB output TCON pin
// Output Value : None
//--------------------------------------------------
void ScalerMbrDrrClearSetting(BYTE ucTcon)
{
    BYTE ucIndex = 0;

    // Reset Toggle Setting
    // Clear all setting from smallest possible TCON
    ScalerTconAdjustByIndex(_TCON2, 0x0000, 0x0000, 0x0000, 0x0000);
    ScalerTconEnableByIndex(_TCON2, _DISABLE);
    for(ucIndex = _TCON3; ucIndex < (ucTcon - 1); ucIndex++)
    {
        ScalerTconEnableByIndex(_TCON2, _DISABLE);
        ScalerTconAdjustByIndex(_TCON2, 0x0000, 0x0000, 0x0000, 0x0000);
        ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucIndex, _TCON_TOGGLE_OP_NORMAL, _DISABLE);
    }

    // Reset Compensation Setting
    ScalerTconEnableByIndex((ucTcon - 1), _DISABLE);
    ScalerTconAdjustByIndex((ucTcon - 1), 0x0000, 0x0000, 0x0000, 0x0000);
    ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)(ucTcon - 1), _TCON_LOGICAL_OP_AND, _DISABLE);
    ScalerTconInvEnableByIndex((ucTcon - 1), _DISABLE);

    // Reset Strobe Setting
#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _OFF)
    ScalerTconEnableByIndex(ucTcon, _DISABLE);
    ScalerTconAdjustByIndex(ucTcon, 0x0000, 0x0000, 0x0000, 0x0000);
#endif
    ScalerTconLogicalOpEnable((EnumTconLogicalOpSet)ucTcon, _TCON_LOGICAL_OP_OR, _DISABLE);

    // Reset MBR global variables
    CLR_MBR_DRR_SAFE_CNT();
    SET_MBR_DRR_VFREQ_AVG(_MBR_DRR_FLICKER_IVF_HI);
    SET_MBR_DRR_STEP_CHG_CNT(0);
    for(ucIndex = 0; ucIndex < _MBR_DRR_AVG_IVF_FRAME_CNT; ucIndex++)
    {
        SET_MBR_DRR_VFREQ(ucIndex, _MBR_DRR_FLICKER_IVF_HI);
    }
}

//--------------------------------------------------
// Description  : Enable interrupt according to backlight mode
// Input Value  : enumMbrBacklightMode - MBR backlight mode
// Output Value : None
//--------------------------------------------------
void ScalerMbrSetIntEnable(EnumMbrBacklightMode enumMbrBacklightMode, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(enumMbrBacklightMode == _BACKLIGHT_MODE_STROBE_DRR_MBR)
        {
            ScalerGlobalSetInterrupt(_IRQ_DVS, _ENABLE);
        }
        else
        {
            ScalerGlobalSetInterrupt(_IRQ_DVS, _DISABLE);
        }
    }
    else
    {
        ScalerGlobalSetInterrupt(_IRQ_DVS, _DISABLE);
    }
}

//--------------------------------------------------
// Description  : Get D-HFreq
// Input Value  : None
// Output Value : D-HFreq
//--------------------------------------------------
WORD ScalerMbrGetDHFreq(void)
{
    return (WORD)(GET_D_CLK_FREQ() / GET_DIS_TIMING_GEN_H_TOTAL());
}

//--------------------------------------------------
// Description  : DRR MBR handler interrupt process (EXINT0 only)
//                Recording & calculating input & average framerate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMbrIntHandler_EXINT0(void) using 1
{
    // DVS event
    if(ScalerGetBit_EXINT(P0_08_IRQ_CTRL2, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        // Clear DVS IRQ flag
        ScalerSetBit_EXINT(P0_08_IRQ_CTRL2, ~(_BIT6 | _BIT4 | _BIT2), _BIT4);

        if(GET_MBR_BACKLIGHT_MODE_EXINT0() == _BACKLIGHT_MODE_STROBE_DRR_MBR)
        {
            WORD usMbrVFreq_avg = 0;
            BYTE ucCnt = g_ucMbrDrrVFreqIndex % _MBR_DRR_AVG_IVF_FRAME_CNT;

            SET_MBR_DRR_VFREQ_EXINT0(ucCnt, GET_INPUT_TIMING_VFREQ());
            for(ucCnt = 0; ucCnt < _MBR_DRR_AVG_IVF_FRAME_CNT; ucCnt++)
            {
                usMbrVFreq_avg += GET_MBR_DRR_VFREQ(ucCnt);
            }
            SET_MBR_DRR_VFREQ_AVG_EXINT0(usMbrVFreq_avg / _MBR_DRR_AVG_IVF_FRAME_CNT);

            if(GET_MBR_DRR_VFREQ_AVG() < _MBR_DRR_FLICKER_IVF_LO)
            {
                CLR_MBR_DRR_SAFE_CNT_EXINT0();
            }
            else
            {
                SET_MBR_DRR_SAFE_CNT_EXINT0();
            }

            g_ucMbrDrrVFreqIndex++;
        }
    }
}
#endif

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Prepare & set the necessary parameters for RTK Adv MBR
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMbrRtkAdvMbrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl)
{
    StructRtkAdvMbrTimingInfo stTimingInfo;
    memset(&stTimingInfo, 0, sizeof(StructRtkAdvMbrTimingInfo));

    DebugMessageScaler("MBR Adv: bLightCtrl", bLightCtrl);
    DebugMessageScaler("MBR Adv: VTotal", GET_MBR_DVTOTAL());
    DebugMessageScaler("MBR Adv: ucBacklightDuty", ucBacklightDuty);
    DebugMessageScaler("MBR Adv: ucBacklightPos", ucBacklightPos);

    stTimingInfo.usDclk = GET_D_CLK_FREQ();
    stTimingInfo.usHTotal = GET_MDOMAIN_OUTPUT_HTOTAL();
    stTimingInfo.usVTotal = GET_MBR_DVTOTAL(); // from measure result
    stTimingInfo.usVFreq = g_usDVFreq;

    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        ScalerMbrRtkAdvMbrAdjust(&stTimingInfo, ucTcon, ucBacklightDuty, ucBacklightPos, _ENABLE);
    }
    else
    {
        ScalerMbrRtkAdvMbrAdjust(&stTimingInfo, ucTcon, ucBacklightDuty, ucBacklightPos, _DISABLE);
    }
}
#endif // End of #if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#endif // End of #if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)

