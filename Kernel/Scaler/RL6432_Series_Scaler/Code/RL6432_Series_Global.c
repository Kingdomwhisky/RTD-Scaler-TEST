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
// ID Code      : RL6432_Series_Global.c No.0000
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
    if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_5_FRAME_BUFFER)
    {
        // IMD Double Buffer Disable
        ScalerSetBit(P31_C0_I_DB_CTRL, ~(_BIT7 | _BIT6), 0x00);

        // I Domain Double Buffer Disable
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT7 | _BIT3), 0x00);

        // D Domain Double Buffer Disable
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), 0x00);

        ScalerVgipDoubleBufferEnable(bEn);
        ScalerMDomainDisplayTimingGenDBEnable(bEn);
    }
    else
    {
        ScalerVgipDoubleBufferEnable(_DISABLE);
        ScalerMDomainDisplayTimingGenDBEnable(_DISABLE);

        if(bEn == _ENABLE)
        {
            // IMD Double Buffer Enable
            ScalerSetBit(P31_C0_I_DB_CTRL, ~(_BIT7 | _BIT6), _BIT7);

            // I Domain Double Buffer Disable
            ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT7 | _BIT3), 0x00);

            // D Domain Double Buffer Disable
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), 0x00);
        }
        else
        {
            ScalerSetBit(P31_C0_I_DB_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Set I domain double buffer trigger event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBSetTriggerEvent(void)
{
#if(_FRC_SUPPORT == _ON)
    if((GET_MEMORY_FRAME_BUFFER() == _MEMORY_2_FRAME_BUFFER) || (GET_MEMORY_FRAME_BUFFER() == _MEMORY_3_FRAME_BUFFER))
    {
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        if((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR))
        {
            if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_3_FRAME_BUFFER)
            {
                if(ScalerGetBit(P5_CF_MN_DISP_CTRL, _BIT3) == _BIT3)
                {
                    // Input fast case
                    ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, (_BIT5 | _BIT2));
                    ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, _BIT7);
                }
                else
                {
                    // Input slow case
                    ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, (_BIT2 | _BIT0));
                    ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, (_BIT7 | _BIT6));
                }
            }
            else
            {
                // Input slow & fast case
                ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, (_BIT2 | _BIT0));
                ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, (_BIT7 | _BIT6));
            }
        }
        else
#endif
        {
            if(ScalerGetBit(P5_CF_MN_DISP_CTRL, _BIT3) == _BIT3)
            {
                // Input fast case
                ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, _BIT5);
                ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, _BIT7);
            }
            else
            {
                // Input slow case
                ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, (_BIT2 | _BIT0));
                ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, (_BIT7 | _BIT6));
            }
        }
    }
    else if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_5_FRAME_BUFFER)
    {
        // IVS/ DVS for M:N = 2:5 or 1:3 case
        ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, 0x00);
        ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, 0x00);
    }
    else
    {
        switch(GET_MEMORY_SELECT())
        {
            case _FREE_RUN_MEMORY:

                // One frame FRC
                ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, 0x00);
                ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, _BIT6);

                break;

            case _MN_FRAME_SYNC_MEMORY:

                // IVS/ DDEN stop for M:N = 1:2 case
                ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, (_BIT4));
                ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, 0x00);

                break;

            case _FRAME_SYNC_LINE_BUFFER:
            case _FRAME_SYNC_MEMORY:
            default:

#if(_FREESYNC_SUPPORT == _ON)
                if(GET_FREESYNC_ENABLED() == _TRUE)
                {
                    // IVS/ DDEN stop
                    ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, (_BIT4));
                    ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, 0x00);
                }
                else
#endif
                {
                    // IVS/ DVS
                    ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, 0x00);
                    ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, 0x00);
                }

                break;
        }
    }
#else

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // IVS/ DDEN stop
        ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, (_BIT4));
        ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, 0x00);
    }
    else
#endif
    {
        // IVS/ DVS
        ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, 0x00);
        ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, 0x00);
    }
#endif
}

//--------------------------------------------------
// Description  : Set D domain double buffer apply
// Input Value  : DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDDomainDBApply(EnumDBApply enumDBApply)
{
#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
    if(ScalerGlobalForceDDomainDBRecovery(enumDBApply, _TRUE) == _TRUE)
    {
        return;
    }
#endif

    // Check IMD Doube Buffer Enable
    if(ScalerGlobalGetDBStatus() == _ENABLE)
    {
        ScalerGlobalIDDomainDBApply(enumDBApply);
    }
    else
    {
        // Display timing gen double buffer apply
        ScalerMDomainDisplayTimingGenDBApply(enumDBApply);
    }
}

//--------------------------------------------------
// Description  : Set I domain double buffer apply
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDomainDBApply(EnumDBApply enumDBApply)
{
    // Check IMD Doube Buffer Enable
    if(ScalerGlobalGetDBStatus() == _ENABLE)
    {
        ScalerGlobalIDDomainDBApply(enumDBApply);
    }
    else
    {
        // I-domain double buffer apply
        ScalerVgipVgipDoubleBufferApply(enumDBApply);
    }
}

//--------------------------------------------------
// Description  : Set I and D domain double buffer apply
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBApply(EnumDBApply enumDBApply)
{
#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
    if(ScalerGlobalForceDDomainDBRecovery(enumDBApply, _TRUE) == _TRUE)
    {
        return;
    }
#endif

    // Check IMD Doube Buffer Enable
    if(ScalerGlobalGetDBStatus() == _ENABLE)
    {
        if(enumDBApply != _DB_APPLY_NONE)
        {
            // Check I/D domain status
            if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
               (GET_DPLL_POWER_STATUS() == _FALSE) ||
               (ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT0) == 0x00))
            {
                // Disable Double Buffer
                ScalerSetBit(P31_C0_I_DB_CTRL, ~_BIT7, 0x00);
                return;
            }

#if(_FREESYNC_SUPPORT == _ON)
            if((GET_FREESYNC_ENABLED() == _TRUE) && ((GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER) || (GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY)))
            {
                if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT5) == 0x00)
                {
                    // IDEN stop/ DDEN stop
                    ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, (_BIT5 | _BIT4));
                    ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, 0x00);
                }
                else
                {
                    // IVS/ DDEN stop
                    ScalerSetBit(P31_C0_I_DB_CTRL, ~0x3F, (_BIT4));
                    ScalerSetBit(P31_C1_D_DB_CTRL, ~0xFF, 0x00);
                }
            }
#endif

            // Set IMD apply bit
            ScalerSetBit(P31_C0_I_DB_CTRL, ~_BIT6, _BIT6);

            if(enumDBApply == _DB_APPLY_POLLING)
            {
                // Wait IMD double buffer
                if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_C0_I_DB_CTRL, _BIT6, 0) == _FALSE)
                {
                    // Disable Double Buffer
                    ScalerSetBit(P31_C0_I_DB_CTRL, ~_BIT7, 0x00);
                }
            }
        }
    }
    else
    {
        if(enumDBApply != _DB_APPLY_NONE)
        {
            // I-domain double buffer apply
            ScalerVgipVgipDoubleBufferApply(enumDBApply);

            // Display timing gen double buffer apply
            ScalerMDomainDisplayTimingGenDBApply(enumDBApply);
        }
    }
}

//--------------------------------------------------
// Description  : Global Double Buffer Config Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDoubleBufferConfigReset(void)
{
    ScalerGlobalDoubleBufferEnable(_DISABLE);

    // Enable I-domain double buffer
    ScalerVgipDoubleBufferEnable(_ENABLE);

    // Enable Display timing gen double buffer
    ScalerMDomainDisplayTimingGenDBEnable(_ENABLE);
}

//--------------------------------------------------
// Description  : Get double buffer status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerGlobalGetDBStatus(void)
{
    return ((bit)ScalerGetBit(P31_C0_I_DB_CTRL, _BIT7));
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

        // Enable Input HVsync error IRQ and fifo under/overflow IRQ
        ScalerSetBit(P0_04_IRQ_CTRL0, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));

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
        ScalerSetBit(P0_0C_WATCH_DOG_CTRL0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1));

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
        // Disable Input HVsync error IRQ and fifo under/overflow IRQ
        ScalerSetBit(P0_04_IRQ_CTRL0, ~(_BIT5 | _BIT1), 0x00);
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
// Description  : Check if fifo underflow or overflow or IHV error, turn off backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalPreventGarbageByBacklight_EXINT0(void) using 1
{
    if(((ScalerGetBit_EXINT(P0_02_STATUS0, (_BIT1 | _BIT0)) != 0x00) && (ScalerGetBit_EXINT(P0_04_IRQ_CTRL0, _BIT1) == _BIT1)) ||
       ((ScalerGetBit_EXINT(P0_02_STATUS0, (_BIT6 | _BIT5)) != 0x00) && (ScalerGetBit_EXINT(P0_04_IRQ_CTRL0, _BIT5) == _BIT5)))
    {
        PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);

        // Set force to background and free run mode
        ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT5 | _BIT3), _BIT5);

        // Disable Input HVsync error IRQ and fifo under/overflow IRQ
        ScalerSetBit_EXINT(P0_04_IRQ_CTRL0, ~(_BIT5 | _BIT1), 0x00);
    }
}
#endif // End of #if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)

