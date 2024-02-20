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
// ID Code      : RL6410_Series_Global.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

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
#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
BYTE g_ucGlobalIntEventDenStart = _FALSE;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerGlobalDoubleBufferEnable(bit bEn);
void ScalerGlobalIDDomainDBSetTriggerEvent(void);
void ScalerGlobalDDomainDBApply(EnumDBApply enumDBApply);
void ScalerGlobalIDomainDBApply(EnumDBApply enumDBApply);
void ScalerGlobalIDDomainDBApply(EnumDBApply enumDBApply);
void ScalerGlobalDoubleBufferConfigReset(void);
bit ScalerGlobalGetDBStatus(void);
void ScalerGlobalCrystalClkSel(EnumClkSel enumClkSel);

void ScalerGlobalWatchDog(bit bEnable);

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
void ScalerGlobalPreventGarbageByBacklight_EXINT0(void);
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Enable/Disable double buffer
// Input Value  : bEn --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDoubleBufferEnable(bit bEn)
{
    if(bEn == _ENABLE)
    {
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), _BIT7);
    }
    else
    {
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), 0x00);
    }
}


//--------------------------------------------------
// Description  : Set I domain double buffer trigger event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBSetTriggerEvent(void)
{
    // Set I DB trigger event: I_Den_stop
    ScalerSetByte(P31_A1_I_DB_CTRL1, 0xFF);
}

//--------------------------------------------------
// Description  : Set D domain double buffer apply
// Input Value  : DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDDomainDBApply(EnumDBApply enumDBApply)
{
    // Set D-domain DB trigger source & trigger event
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, _BIT5);

    if(enumDBApply != _DB_APPLY_NONE)
    {
        // Check D domain status
        if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
           (GET_DPLL_POWER_STATUS() == _FALSE))
        {
            return;
        }
    }

    switch(enumDBApply)
    {
        case _DB_APPLY_NO_POLLING:

            // Set D apply bit
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));

            break;

        case _DB_APPLY_POLLING:

            // Set D apply bit
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));

            if(enumDBApply == _DB_APPLY_POLLING)
            {
                // Wait D double buffer
                ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, (_BIT6), 0);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set I domain double buffer apply
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDomainDBApply(EnumDBApply enumDBApply)
{
    if(enumDBApply != _DB_APPLY_NONE)
    {
        // Set I apply bit
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

        if(enumDBApply == _DB_APPLY_POLLING)
        {
            // Wait I double buffer
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A0_I_DB_CTRL0, (_BIT3 | _BIT2), 0);
        }
    }
}

//--------------------------------------------------
// Description  : Set I and D domain double buffer apply
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBApply(EnumDBApply enumDBApply)
{
#if(_FRC_SUPPORT != _ON)
    enumDBApply = enumDBApply;
#else

    if(enumDBApply != _DB_APPLY_NONE)
    {
        // Check I/D domain status
        if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
           (GET_DPLL_POWER_STATUS() == _FALSE))
        {
            return;
        }
    }

    if(enumDBApply == _DB_APPLY_POLLING)
    {
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        if((ScalerRotationCheckStatus() == _TRUE) ||
           (GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER) ||
           ((GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY) && (GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)))
#else
        if((GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER) ||
           ((GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY) && (GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)))
#endif
        {
            ScalerTimerWaitForEvent(_EVENT_DEN_START);

            // Set I M1/M2 apply bit
            ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

            // Set D apply bit
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));

            // Wait D double buffer
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0);
        }
        else
        {
            // Set DB buffer start address
            ScalerGlobalIDDomainDBSetBufferAddress();

            // Wait Iden_start event
            ScalerTimerWaitForEvent(_EVENT_IEN_START);
            ScalerTimerDelayXms(2);

            // Set I apply bit
            ScalerSetByte(P31_A1_I_DB_CTRL1, 0xFF);
            ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // Get FRC cap current block num, and set to FRC display freeze block num
            pData[0] = (ScalerGetBit(P5_2A_CAP_M1_STATUS, _BIT6) >> 3);
            ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2, ~_BIT3, pData[0]);
            ScalerSetBit(P45_AE_DISP_M2_DISP_CTRL2, ~_BIT3, pData[0]);

            // if input fast than display
            if(ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1, _BIT3) != 0x00)
            {
                // Enable FRC cap block free
                ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT4, _BIT4);
                ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT4, _BIT4);
            }

            // Wait I double buffer
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A0_I_DB_CTRL0, (_BIT3 | _BIT2), 0);

            // Enable FRC display freeze mode
            ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2, ~_BIT2, _BIT2);
            ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
            ScalerSetBit(P45_AE_DISP_M2_DISP_CTRL2, ~_BIT2, _BIT2);
            ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);

            // Disable I DB ??????

            // Wait 2*IDEND at input fast case, wait 1*IDEND at input slow case
            ScalerTimerWaitForEvent(_EVENT_IEN_STOP);

            // if input fast than display
            if(ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1, _BIT3) != 0x00)
            {
                // Wait Iden_stop event
                ScalerTimerWaitForEvent(_EVENT_IEN_STOP);
            }

            // Set D apply bit
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, _BIT5);
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, _BIT6);

            // if input fast than display
            if(ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1, _BIT3) != 0x00)
            {
                // Disable FRC cap block free
                ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1, ~_BIT4, 0x00);
                ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT4, 0x00);
            }

            // Wait D double buffer
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0);

            // Disable FRC display freeze mode
            ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2, ~_BIT2, 0x00);
            ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
            ScalerSetBit(P45_AE_DISP_M2_DISP_CTRL2, ~_BIT2, 0x00);
            ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);
        }
    }
    else if(enumDBApply != _DB_APPLY_NONE)
#endif
    {
        // Wait DDEN Start
        ScalerTimerWaitForEvent(_EVENT_DEN_START);

        // Set I apply bit
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

        // Set D apply bit
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));
    }
}

//--------------------------------------------------
// Description  : Global Double Buffer Config Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDoubleBufferConfigReset(void)
{
}

//--------------------------------------------------
// Description  : Get double buffer status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerGlobalGetDBStatus(void)
{
    return (ScalerGlobalGetIDomainDBStatus() & ScalerGlobalGetDDomainDBStatus());
}

//--------------------------------------------------
// Description  : Select internal oscillator Clock.
// Input Value  : IOSC/ Xtal
// Output Value : None
//--------------------------------------------------
void ScalerGlobalCrystalClkSel(EnumClkSel enumClkSel)
{
    if(enumClkSel == _IOSC_CLK)
    {
        // Select at internal Xtal.
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT3, _BIT3);

#if(_WD_TIMER_INT_SUPPORT == _ON)
        // Record Global Xtal Clk Has been Switched, WD_Timer INT Ref Clk Change
        SET_GLOBAL_XTAL_CLK_SWITCH(_GLOBAL_XTAL_CLK_SEL_TO_INTERNAL);

        // Manual Trigger WD_Timer INT to Proc WDTimerProc_WDINT
        EXIF = (EXIF & (~_BIT4)) | _BIT4;
#endif
    }
    else if(enumClkSel == _EXT_XTAL_CLK)
    {
        // Select at external Xtal.
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT3, 0x00);

#if(_WD_TIMER_INT_SUPPORT == _ON)
        // Record Global Xtal Clk Has been Switched, WD_Timer INT Ref Clk Change
        SET_GLOBAL_XTAL_CLK_SWITCH(_GLOBAL_XTAL_CLK_SEL_TO_EXTERNAL);

        // Manual Trigger WD_Timer INT to Proc WDTimerProc_WDINT
        EXIF = (EXIF & (~_BIT4)) | _BIT4;
#endif
    }
}

//--------------------------------------------------
// Description  : Enabel Global Watch Dog
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalWatchDog(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER)
        {
            // Set Free Run DVTotal = WD-Triggering DVTotal + 1 to Prevent DVTotal Too Long
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H, 2, pData, _AUTOINC);
            PDATA_WORD(0) += 1;

            SET_FREE_RUN_DVTOTAL(PDATA_WORD(0));

            ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);
        }

        // Set Background Color to Black
        ScalerDDomainBackgroundSetColor(0x00, 0x00, 0x00);

        // Clear Display Vsync Timeout Flag
        ScalerSetByte(P0_0C_WATCH_DOG_CTRL0, 0x01);

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)

        // Clear Buffer Status and Input HVsync error flag
        ScalerSetByte(P0_02_STATUS0, 0xFF);

        // Internal IRQ Enable (Global)
        ScalerGlobalIRQControl(_ENABLE);

        // Enable Input HVsync error IRQ
        ScalerSetBit(P0_04_IRQ_CTRL0, ~_BIT5, _BIT5);

        EX0 = 1;
#else
        // Disable WD First
        ScalerSetBit(P16_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P16_18_MEAS_HS_VS_ERROR_WD, ~(_BIT5 | _BIT4), 0x00);
        ScalerSetBit(P16_1C_M1_MEASURE_DUMMY0, ~_BIT7, 0x00);

        // Clear flag
        ScalerSetByte(P0_02_STATUS0, 0xFF);
        ScalerSetBit(P16_16_MEAS_HS_VS_DELTA_IRQ, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
        ScalerSetByte(P16_03_MEAS_ERROR_FLG0, 0xFF);

        // Enable Input H/V Error WD & Enable Frame Sync WD & WD Action
        ScalerSetBit(P0_0C_WATCH_DOG_CTRL0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT5 | _BIT2 | _BIT1));

        // Enable measure overrange WD
#if(_VGA_SUPPORT == _ON)
        if(ScalerFmtCnvGetSourceType() != _FC_SOURCE_ADC)
#endif
        {
            ScalerSetBit(P16_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        }

        // Enable Input H/Vsync overflow WD (analog)
        ScalerSetBit(P16_18_MEAS_HS_VS_ERROR_WD, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

        // Enable Input Vsync timeout WD
        ScalerSetBit(P16_1C_M1_MEASURE_DUMMY0, ~_BIT7, _BIT7);
#endif
    }
    else
    {
#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
        // Disable Input HVsync error IRQ
        ScalerSetBit(P0_04_IRQ_CTRL0, ~_BIT5, 0x00);
#else
        // Disable Input H/V Error WD & Enable Frame Sync WD & Input H/Vsync overflow WD
        ScalerSetByte(P0_0C_WATCH_DOG_CTRL0, 0x00);
        ScalerSetBit(P16_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(P16_18_MEAS_HS_VS_ERROR_WD, ~(_BIT5 | _BIT4), 0x00);
        ScalerSetBit(P16_1C_M1_MEASURE_DUMMY0, ~_BIT7, 0x00);
#endif
    }
}

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
//--------------------------------------------------
// Description  : Check if IHV error, turn off backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalPreventGarbageByBacklight_EXINT0(void) using 1
{
    if((ScalerGetBit_EXINT(P0_02_STATUS0, (_BIT6 | _BIT5)) != 0x00) && (ScalerGetBit_EXINT(P0_04_IRQ_CTRL0, _BIT5) == _BIT5))
    {
        PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);

        // Set force to background and free run mode
        ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT5 | _BIT3), _BIT5);

        // Disable Input HVsync error IRQ
        ScalerSetBit_EXINT(P0_04_IRQ_CTRL0, ~_BIT5, 0x00);
    }
}
#endif // End of #if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)

