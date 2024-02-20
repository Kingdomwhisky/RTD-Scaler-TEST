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
// ID Code      : ScalerGlobal.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_GLOBAL__

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
#if(_WD_TIMER_INT_SUPPORT == _ON)
EnumGlobalXtalClkSelect g_enumGlobalXtalClkSelect = _GLOBAL_XTAL_CLK_SEL_UNCHANGE;
#endif

#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_II) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III))
StructGlobalForceDDomainDB g_stGlobalForceDDomainDB;
#endif
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerGlobalIRQControl(bit bEn);
void ScalerGlobalSetIRQControl(BYTE ucIRQControl);
BYTE ScalerGlobalGetIRQControl(void);
void ScalerGlobalWholeChipReset(void);
void ScalerGlobalOsdInitial(void);
void ScalerGlobalResetProc(BYTE ucResetTarget, BYTE ucGetInputPort);
void ScalerGlobalFirstActiveProc(BYTE ucSourceType, BYTE ucGetInputPort);
void ScalerGlobalSystemClkSel(EnumClkSel enumClockSel);

#if(((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON)) || (_XTALESS_SUPPORT == _ON))
void ScalerGlobalSetInterrupt(EnumIRQ enumIRQType, BYTE ucEn);
#endif

#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) ||\
    ((_LOCAL_DIMMING_SUPPORT == _ON) && (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III)))
bit ScalerGlobalGetDDomainDBStatus(void);
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
bit ScalerGlobalGetIDomainDBStatus(void);

#if(_FRC_SUPPORT == _ON)
void ScalerGlobalIDDomainDBSetBufferAddress(void);
#endif
#endif

#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_II) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III))
void ScalerGlobalForceDDomainDBApply(EnumDBApply enumDBApply);
void ScalerGlobalForceDDomainDBEnable(bit bEn);
bit ScalerGlobalForceDDomainDBRecovery(EnumDBApply enumDBApply, bit bForDDB);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Set Global IRQ Control Register
// Input Value  : CM_14_IRQ_CTRL0 Register Value
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIRQControl(bit bEn)
{
    if(bEn == _ENABLE)
    {
        ScalerSetBit(P0_04_IRQ_CTRL0, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P0_04_IRQ_CTRL0, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set Global IRQ Control Register
// Input Value  : P0_04 and P40_04 register
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetIRQControl(BYTE ucIRQControl)
{
    ScalerSetByte(P0_04_IRQ_CTRL0, ucIRQControl);
}

//--------------------------------------------------
// Description  : Get Global IRQ Control Register
// Input Value  : None
// Output Value : P0_04 and P40_04 register
//--------------------------------------------------
BYTE ScalerGlobalGetIRQControl(void)
{
    return (ScalerGetByte(P0_04_IRQ_CTRL0));
}

//--------------------------------------------------
// Description  : Scaler Whole Chip Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalWholeChipReset(void)
{
    // Whole chip reset
    ScalerSetBit(P0_01_HOST_CTRL, ~_BIT0, _BIT0);

    // For Delay 10 ms
    ScalerTimerDelayXms(10);

    // Clear to 0
    ScalerSetBit(P0_01_HOST_CTRL, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : Initialize OSD Position Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalOsdInitial(void)
{
    OSD_SET_INITIAL();

    ScalerOsdWriteAllByte(_OSD_SRAM, 0x00, 0x00, 0x00, 0x00);

    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
    ScalerOsdGlobalDoubleBuffer(_DISABLE);

#if(_OSD_POSITION_OFFSET_CORRECTION == _ON)
    ScalerOsdPositionOffsetCorrection();

    // window & font alignment
    ScalerOsdFontWindowVericalAlignemnt(_ENABLE);
    ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_WINDOW, X_POS(_OSD_OFFSET_DRAW_WINDOW_H), Y_POS(_OSD_OFFSET_DRAW_WINDOW_V));

#else

    // Set OSD position global offset
    ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL,
                            (ScalerOsdGetDoubleFunctionH() == _ENABLE) ? X_POS(_OSD_DOUBLE_POSITION_OFFSET_H) : X_POS(_OSD_POSITION_OFFSET_H),
                            (ScalerOsdGetDoubleFunctionV() == _ENABLE) ? Y_POS(_OSD_DOUBLE_POSITION_OFFSET_V) : Y_POS(_OSD_POSITION_OFFSET_V));

#if(_OSD_POSITION_SELF_ALIGNMENT == _ON)
    ScalerOsdFontWindowVericalAlignemnt(_ENABLE);
    ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_WINDOW, X_POS(_OSD_OFFSET_DRAW_WINDOW_H), Y_POS(_OSD_OFFSET_DRAW_WINDOW_V));
#else
    ScalerOsdFontWindowVericalAlignemnt(_DISABLE);
    ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_WINDOW, X_POS(0), Y_POS(0));
#endif

#endif // End of #if(_OSD_POSITION_OFFSET_CORRECTION == _OFF)

#if(_D_DITHER_SUPPORT == _ON)
#if(_D_DITHER_FREERUNEN_SUPPORT == _ENABLE)
    // Reset DDither By Enable Rising Edge Signal
    ScalerColorDDitherEnable(_FUNCTION_OFF);
    ScalerColorDDitherEnable(_FUNCTION_ON);
#endif
#endif
}

//--------------------------------------------------
// Description  : Global Reset Event
// Input Value  : ucResetTarget --> Reset target action
//                ucGetInputPort --> Reset port
// Output Value : None
//--------------------------------------------------
void ScalerGlobalResetProc(BYTE ucResetTarget, BYTE ucGetInputPort)
{
    switch(ucResetTarget)
    {
        case _MODE_ACTION_RESET_TO_SEARCH:

            // Set Background Color to Black
            ScalerDDomainBackgroundSetColor(0, 0, 0);
            ScalerDDomainBackgroundEnable(_ENABLE);

            ScalerGlobalWatchDog(_DISABLE);

#if(_VGA_SUPPORT == _ON)
            // Disable Vga Top Double Buffer
            ScalerVgaTopDoubleBufferEnable(_DISABLE);
#endif

            ScalerGlobalDoubleBufferEnable(_DISABLE);

#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
            // FRC Disable M1/M2 Capture/Display
            ScalerFRCEn(_FRC_CAP_DISP_ALL, _DISABLE);
#endif

            // Set Frame sync with line buffer mode
            ScalerFRCSetDDomainSourceSelect(_DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            // Reset Functions related to Rotation
            ScalerRotationResetProc();
#endif

#if(_OD_SUPPORT == _ON)
            ScalerODEnable(_FUNCTION_OFF);
#endif

#if(_XTALESS_SUPPORT == _ON)
#if(_LC_TANK_SUPPORT == _ON)
            ScalerGlobalSetInterrupt(_IRQ_DEN_STOP, _DISABLE);
#endif
#endif

            ScalerSyncResetProc(ucGetInputPort);

            // Scaling down initial
            ScalerIDomainScalingDownInitial();

#if(_SDRAM_PHASE_CALIBRATION == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_SDRAM_PHASE_CNT_CHECK);

#elif(_DDR1_PHASE_CALIBRATION == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DDR_PHASE_CNT_CHECK);
#endif
            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING:
        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG:

            if(ucResetTarget == _MODE_ACTION_RESET_TO_DISPLAY_SETTING)
            {
                // Set Background Color to Black
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                ScalerDDomainBackgroundSetColor(0, 0, 0);
                ScalerDDomainBackgroundEnable(_ENABLE);
            }

            ScalerGlobalWatchDog(_DISABLE);
            ScalerGlobalDoubleBufferConfigReset();

#if(_XTALESS_SUPPORT == _ON)
#if(_LC_TANK_SUPPORT == _ON)
            ScalerGlobalSetInterrupt(_IRQ_DEN_STOP, _DISABLE);
#endif
#endif

#if(_SDRAM_PHASE_CALIBRATION == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_SDRAM_PHASE_CNT_CHECK);

#elif(_DDR1_PHASE_CALIBRATION == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DDR_PHASE_CNT_CHECK);
#endif
            break;

        case _MODE_ACTION_RESET_TO_POWER_SAVING:
        case _MODE_ACTION_RESET_TO_POWER_OFF:

            // Reset OSD Setting
            ScalerOsdReset();

            // Disable WD
            ScalerGlobalWatchDog(_DISABLE);

            // Reset all interface block WD/Irq/Timer Event....
            ScalerSyncResetProc(ucGetInputPort);

#if(_XTALESS_SUPPORT == _ON)
#if(_LC_TANK_SUPPORT == _ON)
            ScalerGlobalSetInterrupt(_IRQ_DEN_STOP, _DISABLE);
#endif
#endif

#if(_SDRAM_PHASE_CALIBRATION == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_SDRAM_PHASE_CNT_CHECK);

#elif(_DDR1_PHASE_CALIBRATION == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DDR_PHASE_CNT_CHECK);
#endif
            break;

        default:

            break;
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    ScalerRotationSetEnable(_DISABLE);
#endif

#if(_OD_SUPPORT == _ON)
    ScalerODEnable(_FUNCTION_OFF);
#endif

#if((_MOTION_BLUR_REDUCTION_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
    ScalerMbrSetIntEnable(_BACKLIGHT_MODE_CONSTANT, _DISABLE);
#endif
}

//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerGlobalFirstActiveProc(BYTE ucSourceType, BYTE ucGetInputPort)
{
    ucGetInputPort = ucGetInputPort;

    // Enable Watch Dog
    ScalerGlobalWatchDog(_ENABLE);

    ScalerGlobalDoubleBufferEnable(_ENABLE);

    switch(ucSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Enable Vga Top Double Buffer
            ScalerVgaTopDoubleBufferEnable(_ENABLE);

            break;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            ScalerTMDSFirstActiveProc(ucGetInputPort, ucSourceType);

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            ScalerDpFirstActiveProc(ucGetInputPort);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Internal Clock Selection.
// Input Value  : bSel    --> _TRUE: Xtal, _FALSE: M2PLL.
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSystemClkSel(EnumClkSel enumClockSel)
{
    if(enumClockSel == _M2PLL_CLK)
    {
        // System clock select to M2PLL/div.
        ScalerM2PLLDiv(_M2PLL_SYS_DIV);

        // Bit2: Internal Xtal Freq. Select to M2PLL/div
        ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~_BIT2, _BIT2);

        // SyncProcessor Clock Select to M2PLL & Set Divider
        ScalerSetBit(P40_06_SYNCPROC_CLK_DIVIDER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _M2PLL_SYS_DIV));

        // Measure Block Clock Select to M2PLL & Set Divider
        ScalerSetBit(P40_07_MEASURE_CLK_DIVIDER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _M2PLL_MEASURE_DIV));

        // GDI Clock Select to M2PLL & Set Divider
        ScalerSetBit(P80_06_GDI_CLK_DIVIDER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _M2PLL_SYS_DIV));

        // SCDC Select to External Xtal
        ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT7, 0x00);
    }
    else
    {
        // Internal Xtal Freq. Select to cystal.
        ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~_BIT2, 0x00);

        // Sync Processor Clock select to Xtal
        ScalerSetBit(P40_06_SYNCPROC_CLK_DIVIDER, ~_BIT4, 0x00);

        // Measure Block Clock Select to Xtal
        ScalerSetBit(P40_07_MEASURE_CLK_DIVIDER, ~_BIT4, 0x00);

        // GDI Clock Select to Xtal
        ScalerSetBit(P80_06_GDI_CLK_DIVIDER, ~_BIT4, 0x00);

        if(enumClockSel == _IOSC_CLK)
        {
            // SCDC Select to INOSC
            ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT7, _BIT7);
        }
        else
        {
            // SCDC Select to External Xtal
            ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT7, 0x00);
        }
    }
}

#if(((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON)) || (_XTALESS_SUPPORT == _ON) || ((_MOTION_BLUR_REDUCTION_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)))
//--------------------------------------------------
// Description  : Set IRQ
// Input Value  : En : Enable / Disable
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetInterrupt(EnumIRQ enumIRQType, BYTE ucEn)
{
    if(ucEn == _ENABLE)
    {
        // Internal IRQ Enable (Global)
        ScalerGlobalIRQControl(_ENABLE);

        // Enable INT0
        EX0 = 1;
    }

    switch(enumIRQType)
    {
        case _IRQ_DVS:
            // Clear DVS IRQ flag
            ScalerSetBit(P0_08_IRQ_CTRL2, ~(_BIT6 | _BIT4 | _BIT2), _BIT4);

            // Enable/Disable DVS IRQ
            ScalerSetBit(P0_08_IRQ_CTRL2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2), (ucEn << 5));
            break;

        case _IRQ_DEN_START:
            // Clear DEN start IRQ flag
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT2);

            // Enable/Disable DEN start IRQ
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2), (ucEn << 3));
            break;

        case _IRQ_DEN_STOP:
            // Clear DEN stop IRQ flag
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT4);

            // Enable/Disable DEN stop IRQ
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2), (ucEn << 5));
            break;

        default:
            // For compiler warning
            ucEn = ucEn;
            break;
    }
}
#endif // End of #if(_OD_SUPPORT == _ON)

#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I) ||\
    ((_LOCAL_DIMMING_SUPPORT == _ON) && (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III)))
//--------------------------------------------------
// Description  : Get D-Domain double buffer status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerGlobalGetDDomainDBStatus(void)
{
    return ((bit)ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7));
}
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
//--------------------------------------------------
// Description  : Get I-Domain double buffer status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerGlobalGetIDomainDBStatus(void)
{
    return ((bit)ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7));
}

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DB Cap/Disp buffer start address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBSetBufferAddress(void)
{
    DWORD ulCurrentStartAddress = 0;
    DWORD ulNextStartAddress = 0;
    DWORD ulBlockStep = 0;
    DWORD ulDispLineStep = 0;
    bit bSizeOverRange = _FALSE;

    ulCurrentStartAddress = ((DWORD)ScalerGetBit(P5_00_CAP_M1_MEM_ADDR_MSB, 0x0F) << 24) |
                            ((DWORD)ScalerGetByte(P5_01_CAP_M1_MEM_ADDR_H) << 16) |
                            ((DWORD)ScalerGetByte(P5_02_CAP_M1_MEM_ADDR_M) << 8) |
                            ((DWORD)ScalerGetByte(P5_03_CAP_M1_MEM_ADDR_L));

    ulBlockStep = ((DWORD)ScalerGetBit(P5_15_CAP_M1_BLOCK_STEP_MSB, 0x0F) << 24) |
                  ((DWORD)ScalerGetByte(P5_16_CAP_M1_BLOCK_STEP_H) << 16) |
                  ((DWORD)ScalerGetByte(P5_17_CAP_M1_BLOCK_STEP_M) << 8) |
                  ((DWORD)ScalerGetByte(P5_18_CAP_M1_BLOCK_STEP_L));

    if(ScalerFmtCnvFtoPGetStatus() == _FALSE)
    {
        ulDispLineStep = ((DWORD)ScalerGetBit(P5_99_DISP_M1_LINE_STEP_MSB, 0x0F) << 24) |
                         ((DWORD)ScalerGetByte(P5_9A_DISP_M1_LINE_STEP_H) << 16) |
                         ((DWORD)ScalerGetByte(P5_9B_DISP_M1_LINE_STEP_M) << 8) |
                         ((DWORD)ScalerGetByte(P5_9C_DISP_M1_LINE_STEP_L));

        ulDispLineStep = ulDispLineStep >> 1;
    }

    ulNextStartAddress = (ulCurrentStartAddress == _FRC_START_ADDRESS_M1) ? (_FRC_START_ADDRESS_M1 + ulBlockStep * 4) : _FRC_START_ADDRESS_M1;

    if(ScalerFmtCnvFtoPGetStatus() == _FALSE)
    {
        ScalerGetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_00_DISPLAY_READ_WID_BSU_H, 4, &pData[0], _AUTOINC);
        // FIFO H Width
        PDATA_WORD(2) = ((((WORD)pData[3] & 0x10) << 8) | (((WORD)pData[0] & 0xF0) << 4) | pData[1]);
        // FIFO V Height
        PDATA_WORD(3) = ((((WORD)pData[3] & 0x01) << 12) | (((WORD)pData[0] & 0x0F) << 8) | pData[2]);

        PDATA_DWORD(0) = (((DWORD)PDATA_WORD(2) * PDATA_WORD(3) * GET_MEMORY_DATA_BIT()) / _MEMORY_BIT_NUM / _MEMORY_BANK / _MEMORY_COL_PER_BANK);
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
        PDATA_DWORD(0) = (PDATA_DWORD(0) << 12);
#else
        PDATA_DWORD(0) = (PDATA_DWORD(0) << 11);
#endif

        if(PDATA_DWORD(0) > _FRC_MEMORY_SIZE_4K1K)
        {
            bSizeOverRange = _TRUE;
        }
    }

    // M1 Cap Block 0
    ScalerSetBit(P5_00_CAP_M1_MEM_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulNextStartAddress >> 24) & 0x0F));
    ScalerSetByte(P5_01_CAP_M1_MEM_ADDR_H, ((ulNextStartAddress >> 16) & 0xFF));
    ScalerSetByte(P5_02_CAP_M1_MEM_ADDR_M, ((ulNextStartAddress >> 8) & 0xFF));
    ScalerSetByte(P5_03_CAP_M1_MEM_ADDR_L, (ulNextStartAddress & 0xFF));

    // M1 Disp Block 0
    ScalerSetBit(P5_80_DISP_M1_READ_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulNextStartAddress >> 24) & 0x0F));
    ScalerSetByte(P5_81_DISP_M1_READ_ADDR_H, ((ulNextStartAddress >> 16) & 0xFF));
    ScalerSetByte(P5_82_DISP_M1_READ_ADDR_M, ((ulNextStartAddress >> 8) & 0xFF));
    ScalerSetByte(P5_83_DISP_M1_READ_ADDR_L, (ulNextStartAddress & 0xFF));

    // M1 Cap Block 1
    PDATA_DWORD(0) = (ulNextStartAddress + ulBlockStep);
    ScalerSetBit(P5_04_CAP_M1_BL2_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
    ScalerSetByte(P5_05_CAP_M1_BL2_ADDR_H, pData[1]);
    ScalerSetByte(P5_06_CAP_M1_BL2_ADDR_M, pData[2]);
    ScalerSetByte(P5_07_CAP_M1_BL2_ADDR_L, pData[3]);

    // M1 Disp Block 1
    ScalerSetBit(P5_84_DISP_M1_BL2_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
    ScalerSetByte(P5_85_DISP_M1_BL2_ADDR_H, pData[1]);
    ScalerSetByte(P5_86_DISP_M1_BL2_ADDR_M, pData[2]);
    ScalerSetByte(P5_87_DISP_M1_BL2_ADDR_L, pData[3]);

    // M2 Cap Block 0
    PDATA_DWORD(0) = (ulNextStartAddress + ulBlockStep * 2);
    ScalerSetBit(P45_00_CAP_M2_MEM_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
    ScalerSetByte(P45_01_CAP_M2_MEM_ADDR_H, pData[1]);
    ScalerSetByte(P45_02_CAP_M2_MEM_ADDR_M, pData[2]);
    ScalerSetByte(P45_03_CAP_M2_MEM_ADDR_L, pData[3]);

    // M2 Disp Block 0
    if(ScalerFmtCnvFtoPGetStatus() == _FALSE)
    {
        PDATA_DWORD(0) = (ulNextStartAddress + ulDispLineStep);
    }

    ScalerSetBit(P45_80_DISP_M2_READ_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
    ScalerSetByte(P45_81_DISP_M2_READ_ADDR_H, pData[1]);
    ScalerSetByte(P45_82_DISP_M2_READ_ADDR_M, pData[2]);
    ScalerSetByte(P45_83_DISP_M2_READ_ADDR_L, pData[3]);

    // M2 Cap Block 1
    if(bSizeOverRange == _TRUE)
    {
        PDATA_DWORD(0) = (ulNextStartAddress + ulBlockStep * 2);
        ScalerSetBit(P45_04_CAP_M2_BL2_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
        ScalerSetByte(P45_05_CAP_M2_BL2_ADDR_H, pData[1]);
        ScalerSetByte(P45_06_CAP_M2_BL2_ADDR_M, pData[2]);
        ScalerSetByte(P45_07_CAP_M2_BL2_ADDR_L, pData[3]);
    }
    else
    {
        PDATA_DWORD(0) = (ulNextStartAddress + ulBlockStep * 3);
        ScalerSetBit(P45_04_CAP_M2_BL2_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
        ScalerSetByte(P45_05_CAP_M2_BL2_ADDR_H, pData[1]);
        ScalerSetByte(P45_06_CAP_M2_BL2_ADDR_M, pData[2]);
        ScalerSetByte(P45_07_CAP_M2_BL2_ADDR_L, pData[3]);
    }

    // M2 Disp Block 1
    if(ScalerFmtCnvFtoPGetStatus() == _FALSE)
    {
        PDATA_DWORD(0) = (ulNextStartAddress + ulBlockStep + ulDispLineStep);
    }

    ScalerSetBit(P45_84_DISP_M2_BL2_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
    ScalerSetByte(P45_85_DISP_M2_BL2_ADDR_H, pData[1]);
    ScalerSetByte(P45_86_DISP_M2_BL2_ADDR_M, pData[2]);
    ScalerSetByte(P45_87_DISP_M2_BL2_ADDR_L, pData[3]);
}
#endif

#endif // End of #if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)

#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_II) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III))
//--------------------------------------------------
// Description  : Set D domain double buffer apply
// Input Value  : DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalForceDDomainDBApply(EnumDBApply enumDBApply)
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
// Description  : Enable/Disable double buffer
// Input Value  : bEn --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalForceDDomainDBEnable(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // D Domain Double Buffer Enable
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), _BIT7);
    }
    else
    {
        // D Domain Double Buffer Disable
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), 0x00);
    }
}


//--------------------------------------------------
// Description  : Recovery D domain double buffer setting
// Input Value  : None
// Output Value : _TRUE: ForceDDomainDBRecovery
//--------------------------------------------------
bit ScalerGlobalForceDDomainDBRecovery(EnumDBApply enumDBApply, bit bForDDB)
{
    if((GET_FORCE_D_DOMAIN_DB() == _TRUE) && (enumDBApply != _DB_APPLY_NONE))
    {
        if(bForDDB == _TRUE)
        {
            ScalerGlobalForceDDomainDBApply(enumDBApply);
        }

        // D Domain Double Buffer Recovery
#if((_LOCAL_DIMMING_SUPPORT == _ON) && (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III))
        if(GET_D_DOMAIN_DB_STATUS() == _ENABLE)
        {
            SET_D_DOMAIN_DB_STATUS(_FALSE);
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), _BIT7);
        }
        else
#endif
        {
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), 0x00);
        }

        // IMD Double Buffer Recovery
        ScalerGlobalDoubleBufferEnable(_ENABLE);

        SET_FORCE_D_DOMAIN_DB(_FALSE);

        return _TRUE;
    }

    return _FALSE;
}
#endif
#endif

