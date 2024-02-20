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
// ID Code      : RL6492_Series_Memory.c No.0000
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
#if(_OD_SUPPORT == _ON)
DWORD g_ulMemoryThreeBlockAddr1;
DWORD g_ulMemoryThreeBlockAddr2;
DWORD g_ulMemoryThreeBlockAddr3;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMemorySetFifoCapture(WORD usHWidth, WORD usVHeight);
WORD ScalerMemoryGetFifoWidth(void);
void ScalerMemoryFrameSyncSetDt(BYTE ucNum);
DWORD ScalerMemoryGetIVS2DVSDelayPixel(void);
void ScalerMemorySetFIFOFreq(EnumScalerFIFOFreq enumFIFOFreq);

#if(_FRC_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
void ScalerMemoryCalculateLineStepAndBlockStep(DWORD ulHorSize, WORD usVerSize, StructMemoryLineBlockStep *pstStep);
#endif
#endif

#if(_FREESYNC_SUPPORT == _ON)
void ScalerMemorySetShiftOneLine(bit bEnable);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set FIFO Capture
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetFifoCapture(WORD usHWidth, WORD usVHeight)
{
    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_00_DISPLAY_READ_WID_BSU_H), (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));
    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_01_DISPLAY_READ_WID_BSU_L), LOBYTE(usHWidth));
    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_02_DISPLAY_READ_LEN_BSU_L), LOBYTE(usVHeight));
    ScalerSetDataPortBit(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H), ~(_BIT4 | _BIT0), (((usHWidth & 0x1000) >> 8) | ((usVHeight & 0x1000) >> 12)));

    // Set Pre-Read line
    ScalerSetByte(P5_BC_MN_PRRD_VST_H, _PRE_READ_LINE_BUFFER);
    ScalerSetByte(P5_BD_MN_PRRD_VST_L, _PRE_READ_LINE_BUFFER);

    // Set Capture Line Pixel Number
    ScalerSetBit(P5_BE_MN_PXL_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHWidth) & 0x0F));
    ScalerSetByte(P5_BF_MN_PXL_NUM_L, LOBYTE(usHWidth));

    // Set Capture Line Number
    ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usVHeight >> 8) & 0x0F);
    ScalerSetByte(P5_B8_IN1_LINE_NUM_L, LOBYTE(usVHeight));

    // Set Display Line Number
    ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usVHeight >> 8) & 0x0F);
    ScalerSetByte(P5_CE_MN_LINE_NUM_L, LOBYTE(usVHeight));

    if(GET_MEMORY_DATA_BIT() == 30)
    {
        // Set input format 30 bit
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // Set input format 24 bit
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~(_BIT1 | _BIT0), 0x00);
    }

    // FRC display double buffer apply
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);
}

//--------------------------------------------------
// Description  : Get fifo width
// Input Value  : None
// Output Value : Fifo width
//--------------------------------------------------
WORD ScalerMemoryGetFifoWidth(void)
{
    //-------------------------------------------------
    // Get FIFO Input Width: 13 bit
    //-------------------------------------------------
    ScalerGetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_00_DISPLAY_READ_WID_BSU_H, 1, &pData[2], _NON_AUTOINC);
    ScalerGetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_01_DISPLAY_READ_WID_BSU_L, 1, &pData[3], _NON_AUTOINC);
    ScalerGetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H, 1, &pData[4], _NON_AUTOINC);

    PDATA_WORD(0) = ((((WORD)pData[4] << 8) & 0x1000) | (((WORD)pData[2] << 4) & 0xF00) | pData[3]);

    return PDATA_WORD(0);
}

//--------------------------------------------------
// Description  : Setup Frame Sync Dt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryFrameSyncSetDt(BYTE ucNum)
{
    DWORD ulIVStoDVSPixels = 0;
    DWORD ulIVstart = 0;
    DWORD ulDVstart = 0;
    DWORD ulDt_percent = 0;

    // Calculate DVS to DH Active in ICLK
    ulDVstart = ((DWORD)g_stMDomainOutputData.usHTotal * g_stMDomainOutputData.usVStart) + g_stMDomainOutputData.usHStart;
    ulDVstart = ulDVstart * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usHTotal;

    // Calculate IVS to IH Active in ICLK
    ulIVstart = ((DWORD)g_stMDomainInputData.usHTotal * g_stMDomainInputData.usVStart) + g_stMDomainInputData.usHStart;

    // IVS2DVS line skip disable
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT3, _BIT3);

    // Frame Sync Memory Settings
    if(GET_V_SCALE_UP() == _TRUE)    // Vertical Scaling Up
    {
        ulDt_percent = (DWORD)ScalerMemoryGetScaleUpDt() * ucNum / 50;
        ulIVstart += (DWORD)g_stMDomainInputData.usHTotal * ulDt_percent / 100;
    }
    else
    {
        if(GET_V_SCALE_DOWN() == _TRUE)    // Vertical Scaling Down
        {
            ulDt_percent = g_stMDomainInputData.usHTotal * 2 + ((DWORD)g_stMDomainInputData.usHTotal * g_stMDomainInputData.usVHeight / (g_stMDomainOutputData.usVHeight * 2));
        }
        else    // Vertical Scaling Bypass
        {
            ulDt_percent = g_stMDomainInputData.usHTotal * 2 + g_stMDomainInputData.usHTotal / 2;
        }
        ulDt_percent = (ulDt_percent * 100) / g_stMDomainInputData.usHTotal;
        ulDt_percent = ulDt_percent * ucNum / 50;
        ulIVstart += (DWORD)g_stMDomainInputData.usHTotal * ulDt_percent / 100;
    }

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        if(ulIVstart <= ulDVstart)
        {
            // DVst - (IVst + Dt) in D-line
            PDATA_DWORD(3) = (ulDVstart - ulIVstart) * g_stMDomainOutputData.usVHeight / g_stMDomainInputData.usVHeight / g_stMDomainInputData.usHTotal + 1;

            if(g_stMDomainOutputData.usVStart > PDATA_DWORD(3))
            {
                g_stMDomainOutputData.usVStart -= PDATA_DWORD(3);
            }
            else
            {
                g_stMDomainOutputData.usVStart = 1;
                DebugMessageFS("DRR Dt warning", 0);
            }
        }
        else
        {
            // (IVst + Dt) - DVst in D-line
            PDATA_DWORD(3) = (ulIVstart - ulDVstart) * g_stMDomainOutputData.usVHeight / g_stMDomainInputData.usVHeight / g_stMDomainInputData.usHTotal;

            g_stMDomainOutputData.usVStart += PDATA_DWORD(3);
        }

        // Calculate DVS to DH Active in ICLK
        ulDVstart = ((DWORD)g_stMDomainOutputData.usHTotal * g_stMDomainOutputData.usVStart) + g_stMDomainOutputData.usHStart;
        ulDVstart = ulDVstart * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usHTotal;

        // IVS2DVS delay
        ulIVStoDVSPixels = (ulIVstart > ulDVstart) ? (ulIVstart - ulDVstart) : 0;

        // Check MIn DVStart = 2
        if(g_stMDomainOutputData.usVStart < 2)
        {
            // Modify DVSt
            g_stMDomainOutputData.usVStart = 2;
            g_stMDomainOutputData.usVBackStart = 2;

            // Set ivs2dvs delay = 0
            ulIVStoDVSPixels = 0;
        }
        else
        {
            // Check ivs2dvs delay < FRC FIFO size
            if(ulIVStoDVSPixels > ((DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT()))
            {
                ulIVStoDVSPixels = 0;
            }
        }
    }
    else
#endif
    {
        // If DVSt > (IVSt + Dt) means no further IVS2DVSDelay can be added!!
        // Preserve 2 line margin in advance
        PDATA_DWORD(3) = ulDVstart + 2 * g_stMDomainInputData.usHTotal;

        if(PDATA_DWORD(3) > ulIVstart)
        {
            // Calculate insufficient line number
            WORD usInsufficientLines = (PDATA_DWORD(3) - ulIVstart) / g_stMDomainInputData.usHTotal + 1;

            DebugMessageFS("2. No Further IVS2DVSDelay Can Be Added", 0x00);

            // Enlarge IVSt for insufficient lines
            g_stMDomainInputData.usVStart += usInsufficientLines;

            if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
            {
                // Set new IVSt under analog capture
                ScalerVgipSetCaptureVStartPosition(g_stMDomainInputData.usVStart);
            }
            else
            {
                // Set new IVSt under digital capture
                ScalerVgipSetCaptureVStartPosition((GET_INPUT_TIMING_VHEIGHT() - GET_MDOMAIN_INPUT_VHEIGHT()) / 2 + usInsufficientLines);
            }

            // Modify Original (IVSt + Dt) Value
            ulIVstart += (DWORD)usInsufficientLines * g_stMDomainInputData.usHTotal;
        }

        // Set IVS to DVS Delay
        PDATA_DWORD(0) = (ulIVstart > ulDVstart) ? (ulIVstart - ulDVstart) : 0;

        DebugMessageFS("Target IVS to DVS Delay Value", PDATA_DWORD(0) * 10 / g_stMDomainInputData.usHTotal);

        // Get Current IVS2DVS Delay + DVS Width in Input Lines (Get Ceiling Value) + 1 line for margin
        PDATA_WORD(2) = (PDATA_DWORD(0) + (DWORD)(_PANEL_DV_SYNC_HEIGHT) * g_stMDomainInputData.usVHeight * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usVHeight) / g_stMDomainInputData.usHTotal + 1;
        PDATA_WORD(2) &= 0x1FFF;

        // Enlarge DVSt if IVS2DVS Delay + DVS Width is larger than IVSt
        if(PDATA_WORD(2) >= (g_stMDomainInputData.usVStart))
        {
            DebugMessageFS("2. Target IVS2DVS Delay too Large", pData[5]);

            // Get the difference between IVS2DVS Delay and IVSt
            PDATA_WORD(2) = PDATA_WORD(2) - g_stMDomainInputData.usVStart + 1;

            // Get Required Increment of DVSt
            PDATA_WORD(2) = PDATA_WORD(2) * g_stMDomainOutputData.usVHeight / g_stMDomainInputData.usVHeight + 1;

            // Modify DVSt & background DVSt
            g_stMDomainOutputData.usVStart += PDATA_WORD(2);
            g_stMDomainOutputData.usVBackStart += PDATA_WORD(2);

            // Modify IVS2DVS Delay
            PDATA_DWORD(0) -= (DWORD)PDATA_WORD(2) * g_stMDomainInputData.usHTotal * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight;
        }

        // Store IVS-to-DVS pixels
        ulIVStoDVSPixels = PDATA_DWORD(0);
    }

    // Before is frame sync mode, current is frame sync mode, check IVS2DVS delay change
    if(ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE)
    {
        // Get Old IVS2DVS + IVSdelay (I line)
        PDATA_WORD(0) = (ScalerMemoryGetIVS2DVSDelayPixel() / g_stMDomainInputData.usHTotal);

        // Calculate current frame sync fine-tune value
        PDATA_WORD(1) = (ulIVStoDVSPixels / g_stMDomainInputData.usHTotal);

        // IVS2DVS Change Limit (Convert DVline limit to IVline)
        PDATA_WORD(2) = (DWORD)_PANEL_DV_LINE_CHG_LIMIT * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight;

        ScalerMemoryFineTuneIVS2DVSDelay(PDATA_WORD(0), PDATA_WORD(1), PDATA_WORD(2));
    }

    if(GET_INTERLACED_MODE() == _TRUE)
    {
        // Video Compensation on Even Field
        if(ScalerGetBit(P0_32_SCALE_CONTROL_REG, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Enable Frame Sync Fine Tune on Odd Field
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        // Video Compensation on Odd Field
        else if(ScalerGetBit(P0_32_SCALE_CONTROL_REG, (_BIT7 | _BIT6)) == _BIT7)
        {
            // Enable Frame Sync Fine Tune on Even Field
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT1 | _BIT0), _BIT1);
        }
        else
        {
            // Disable Frame Sync Fine Tune
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);
        }
    }
    else
    {
        // Disable Frame Sync Fine Tune
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);
    }

    // Check frame sync fine-tune
    ScalerMemoryUpdateIVS2DVSLineDelay(ulIVStoDVSPixels);
}

//--------------------------------------------------
// Description  : Get IVS2DVS delay, unit: pixel
// Input Value  : None
// Output Value : IVS2DVS delay, unit: pixel
//--------------------------------------------------
DWORD ScalerMemoryGetIVS2DVSDelayPixel(void)
{
    DWORD ulIVS2DVSDelayPixel = 0;

    // Get Initial Dt Fine Tune Value
    ulIVS2DVSDelayPixel = (((((DWORD)ScalerGetByte(P0_3E_IVS2DVS_DLY_LINE_H) << 8) & 0x1F00) | ScalerGetByte(P0_40_IVS2DVS_DLY_LINE_L)) * g_stMDomainInputData.usHTotal) +
                          ((((((DWORD)ScalerGetByte(P0_3F_DISPLAY_ALIGN_CONTROL) << 4) & 0x300) | ScalerGetByte(P0_41_IVS2DVS_DLY_TUNE_ODD)) + 1) * 16) +
                          ((ScalerGetByte(P0_3D_IV_DV_DELAY_CLK_FINE) >> 4) & 0x0F);

    return ulIVS2DVSDelayPixel;
}

//--------------------------------------------------
// Description  : Set FIFO Clock
// Input Value  : Target FIFO Clock
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetFIFOFreq(EnumScalerFIFOFreq enumFIFOFreq)
{
    switch(enumFIFOFreq)
    {
        case _SCALER_FIFO_FREQ_M2PLL:
            ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _SCALER_FIFO_FREQ_MPLL:
            ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), 0x00);
            break;

        default:
            break;
    }
}

#if(_FRC_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate the Line Step and Block Step
// Input Value  : usHorSize --> Horizontal size (unit : 64 bits)
//                usVerSize --> Vertical size
// Output Value : Line Step and Block Step
//--------------------------------------------------
void ScalerMemoryCalculateLineStepAndBlockStep(DWORD ulHorSize, WORD usVerSize, StructMemoryLineBlockStep *pstStep)
{
    pstStep->ulLineStep = ScalerMemoryAddressConversion(ulHorSize);
    pstStep->ulBlockStep = ScalerMemoryAddressConversion((DWORD)usVerSize * ulHorSize);
}
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)
#endif // End of #if(_FRC_SUPPORT == _ON)

#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Shift One Line ON/OFF for Free Sync
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerMemorySetShiftOneLine(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable Function On The Porch
        if(ScalerGlobalGetDBStatus() == _FALSE)
        {
            ScalerTimerWaitForEvent(_EVENT_IEN_STOP);
        }

        // Enable Scale Down
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~_BIT0, _BIT0);

        // Enable Scale Down FREESYNC Mode
        ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~_BIT1, _BIT1);

        // Set IVst = 1
        g_stMDomainInputData.usVStart = 1;

        if(GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER)
        {
            // Set IVS Reset M-Domain FIFO
            ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~_BIT6, _BIT6);
        }
        else
        {
            // Set DVS Reset M-Domain FIFO
            ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~_BIT6, 0x00);
        }
    }
    else
    {
        // Disable M Domain FREESYNC Enable for VGIP IVS Event to be triggered
        ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~_BIT1, 0x00);

        // Set DVS Reset M-Domain FIFO
        ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~_BIT6, 0x00);
    }
}
#endif


