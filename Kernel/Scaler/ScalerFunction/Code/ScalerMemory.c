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
// ID Code      : ScalerMemory.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MEMORY__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_SHARPNESS_SUPPORT == _ON)
#define _SHARPNESS_TABLE_SIZE                       (128)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_SHARPNESS_SUPPORT == _ON)
void ScalerMemorySetScalingCoef(BYTE code *pucAddress1, BYTE code *pucAddress2, BYTE ucBankNum);
#endif

void ScalerMemoryInitial(void);

#if(_LAST_LINE_FINETUNE_ENABLE == _ENABLE)
void ScalerMemoryCompensateDtForLastLine(DWORD ulTargetLastLine, DWORD ulCurrentLastLine);
#endif

void ScalerMemoryUpdateIVS2DVSLineDelay(DWORD ulCompsIVS2DVSpixel);
void ScalerMemorySetIVS2DVSLineDelay(WORD usIVS2DVSDelay);
void ScalerMemoryFineTuneIVS2DVSDelay(WORD usOldIVS2DVSDelay, WORD usNewIVS2DVSDelay, WORD usIVS2DVSChgLimit);
DWORD ScalerMemoryGetDtMaxMin(void);
WORD ScalerMemoryGetScaleUpDt(void);

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
void ScalerMemoryReset(void);
void ScalerMemoryPowerControl(bit bOnOff);
#endif

#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
#if(_MN_FRAME_TRACKING_SUPPORT == _ON)
void ScalerMemorySetFrameTrackingEnable(bit bEn);
#endif
#endif

#if(_FRC_SUPPORT == _ON)

#if(_MN_FRAME_TRACKING_SUPPORT == _ON)
void ScalerMemoryFrameTracking(void);
WORD ScalerMemoryGetMNRatio(void);
#endif

DWORD ScalerMemoryCalculateFrameLineTotalPixel(bit bLineFrameMode, WORD usHorSize, WORD usVerSize);
DWORD ScalerMemoryAddressConversion(DWORD ulTotalSize);
#endif

#if(_OD_SUPPORT == _ON)
#if(_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
void ScalerMemorySetODThreeBlockAddress(void);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SHARPNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Scale Up coef
// Input Value  : H/V coef table, length
// Output Value : none
//--------------------------------------------------
void ScalerMemorySetScalingCoef(BYTE code *pucAddress1, BYTE code *pucAddress2, BYTE ucBankNum)
{
    // Set Coefficient table 1
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(pucAddress1, _SHARPNESS_TABLE_SIZE, ucBankNum, P0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Set Coefficient table 2
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(pucAddress2, _SHARPNESS_TABLE_SIZE, ucBankNum, P0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);


    // Disable Coefficient Access, Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
}
#endif

//--------------------------------------------------
// Description  : M Domain Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryInitial(void)
{
#if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
    //------------------------------
    // SDRAM Initial
    //------------------------------
#endif

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
    //------------------------------
    // DDR1 Initial
    //------------------------------
#endif

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
    //------------------------------
    // DDR3 Initial
    //------------------------------
#endif

#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
    //------------------------------
    // FRC Initial
    //------------------------------
    ScalerFRCInitial();
#endif

#if(_OD_SUPPORT == _ON)
    //------------------------------
    // OD Initial
    //------------------------------
    ScalerODSetMemoryStartAddress();
#endif

#if(_FREESYNC_SUPPORT == _ON)
    //------------------------------
    // Free Sync Initial
    //------------------------------
    ScalerMemorySetShiftOneLine(GET_FREESYNC_ENABLED());
#endif
}

#if(_LAST_LINE_FINETUNE_ENABLE == _ENABLE)
//--------------------------------------------------
// Description  : Compensate Last Line Fine Tune
// Input Value  : Target Last Line, Current Last Line
// Output Value : None
//--------------------------------------------------
void ScalerMemoryCompensateDtForLastLine(DWORD ulTargetLastLine, DWORD ulCurrentLastLine)
{
    DWORD ulCompsIVS2DVSpixel = 0;

    // Get Initial Dt Fine Tune Value
    PDATA_DWORD(0) = ScalerMemoryGetIVS2DVSDelayPixel();

    DebugMessageFS("Original Dt", PDATA_DWORD(0));

    // Compensate Dt = Original Dt + ((Target Last Line - Current Last Line) * DVHeight / DVTotal * IVHeight / DVHeight * IHTotal / DHTotal) / 2
    ulCompsIVS2DVSpixel = (SDWORD)PDATA_DWORD(0) + ((((SDWORD)ulTargetLastLine - (SDWORD)ulCurrentLastLine) * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVTotal * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usHTotal) >> 1);

    DebugMessageFS("Last Line Difference", ((SDWORD)ulTargetLastLine - (SDWORD)ulCurrentLastLine));
    DebugMessageFS("Dt Compensate Value", (((SDWORD)ulTargetLastLine - (SDWORD)ulCurrentLastLine) * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVTotal * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usHTotal) >> 1);

    DebugMessageFS("Compensated Dt", ulCompsIVS2DVSpixel);
    ScalerMemoryUpdateIVS2DVSLineDelay(ulCompsIVS2DVSpixel);
}
#endif

//--------------------------------------------------
// Description  : Set IVS2DVS Delay (line)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryUpdateIVS2DVSLineDelay(DWORD ulCompsIVS2DVSpixel)
{
    BYTE ucEOshift = 0;
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        ucEOshift = 1;
    }
#endif

    ulCompsIVS2DVSpixel = ulCompsIVS2DVSpixel >> ucEOshift;

    if((ScalerGetBit(P0_43_FS_DELAY_FINE_TUNE, _BIT1) == _BIT1) &&
       (ulCompsIVS2DVSpixel >= (((g_stMDomainInputData.usHTotal >> 1) + 64) >> ucEOshift)))
    {
        // Preserve 0.5 lines + 64 pixel in Fine Tune Byte
        PDATA_WORD(2) = (ulCompsIVS2DVSpixel - (((g_stMDomainInputData.usHTotal >> 1) + 64) >> ucEOshift)) / g_stMDomainInputData.usHTotal;
        PDATA_WORD(3) = (ulCompsIVS2DVSpixel - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> 4;

        if(_VSU_INI_PHASE_LINES == _VSU_3_LINE)
        {
            PDATA_WORD(4) = (ulCompsIVS2DVSpixel + (g_stMDomainInputData.usHTotal >> (1 + ucEOshift)) - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> 4;
        }
        else
        {
            PDATA_WORD(4) = (ulCompsIVS2DVSpixel - (g_stMDomainInputData.usHTotal >> (1 + ucEOshift)) - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> 4;
        }
        pData[10] = (ulCompsIVS2DVSpixel - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << 4));
        pData[11] = (ulCompsIVS2DVSpixel - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(4) << 4));
    }
    else
    {
        PDATA_WORD(2) = ulCompsIVS2DVSpixel / g_stMDomainInputData.usHTotal;
        PDATA_WORD(3) = ulCompsIVS2DVSpixel - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) >> 4;
        PDATA_WORD(4) = 0x0000;
        pData[10] = (ulCompsIVS2DVSpixel - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << 4));
        pData[11] = 0x00;
    }

    //-------------------------------------------------
    // Apply updated Delay
    //-------------------------------------------------
    // IVS2DVS line delay, unit: line
    ScalerSetByte(P0_3E_IVS2DVS_DLY_LINE_H, (pData[4] & 0x1F));
    ScalerSetByte(P0_40_IVS2DVS_DLY_LINE_L, pData[5]);

    // IVS2DVS 16iclk1 delay, unit: 16 pixel
    PDATA_WORD(3) -= (PDATA_WORD(3) >= 1) ? 1 : 0;
    SET_IVS2DVS_DELAY_16ICLK1(PDATA_WORD(3));

    // IVS2DVS 16iclk2 delay, unit: 16 pixel
    PDATA_WORD(4) -= (PDATA_WORD(4) >= 1) ? 1 : 0;
    SET_IVS2DVS_DELAY_16ICLK2(PDATA_WORD(4));

    // IVS2DVS iclk1 delay, unit: 1 pixel
    ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0xF0, ((pData[10] & 0x0F) << 4));

    // IVS2DVS iclk2 delay, unit: 1 pixel
    ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0x0F, (pData[11] & 0x0F));
}

//--------------------------------------------------
// Description  : Set IVS2DVS Delay (line)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetIVS2DVSLineDelay(WORD usIVS2DVSDelay)
{
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        usIVS2DVSDelay = (usIVS2DVSDelay >> 1);
    }
#endif

    // IVS2DVS delay setting min=0x01
    if(usIVS2DVSDelay == 0)
    {
        usIVS2DVSDelay = 0x01;
    }

    ScalerSetByte(P0_3E_IVS2DVS_DLY_LINE_H, (HIBYTE(usIVS2DVSDelay) & 0x1F));
    ScalerSetByte(P0_40_IVS2DVS_DLY_LINE_L, LOBYTE(usIVS2DVSDelay));
}

//--------------------------------------------------
// Description  : IVS2DVS Delay Finetune
// Input Value  : Old IVS2DVS Delay/ New IVS2DVS Delay/ IVS2DVS Change limit
// Output Value : None
//--------------------------------------------------
void ScalerMemoryFineTuneIVS2DVSDelay(WORD usOldIVS2DVSDelay, WORD usNewIVS2DVSDelay, WORD usIVS2DVSChgLimit)
{
    WORD usDVTotalFrameSync = 0;
    WORD usDVTotalFreeRun = 0;
    WORD usRemainIVS2DVSDelay = 0;
    BYTE ucTimeoutCounter = 255;

    // Set Frame Sync Mode Delay Fine Tune = 0
    SET_IVS2DVS_DELAY_16ICLK1(0x0000);
    SET_IVS2DVS_DELAY_16ICLK2(0x0000);

    if(ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT1) == _BIT1)
    {
        // Avoid (Current_IVStart + IVHeight) > IVToal + New_IVSDelay in digital capture
        PDATA_WORD(0) = (g_stInputTimingData.usVStart + ScalerVgipGetCaptureVStartPosition() + g_stMDomainInputData.usVHeight);
    }
    else
    {
        // Avoid (Current_IVSDelay + IVStart + IVHeight) > IVToal + New_IVSDelay in analog capture
        PDATA_WORD(0) = (ScalerVgipGetCaptureVDelay() + ScalerVgipGetCaptureVStartPosition() + g_stMDomainInputData.usVHeight);
    }

    if(PDATA_WORD(0) > g_stMDomainInputData.usVTotal)
    {
        ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
        return;
    }

    // IVS2DVS delay from small to large
    if((usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay()) < (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY()))
    {
        usRemainIVS2DVSDelay = (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY()) - (usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay());

        while(usRemainIVS2DVSDelay > usIVS2DVSChgLimit)
        {
            usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
            usOldIVS2DVSDelay += usIVS2DVSChgLimit;

            ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay);
            ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);

            if(ucTimeoutCounter == 0)
            {
                break;
            }

            ucTimeoutCounter--;
        }

        ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
    }
    else if((usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay()) > (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY()))
    {
        // Get Frame Sync DVtotal
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
        GET_DVTOTAL_LASTLINE(usDVTotalFrameSync);

        // IVS2DVS  diff (D_line)
        usRemainIVS2DVSDelay = (usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay()) - (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY());
        usRemainIVS2DVSDelay = (DWORD)usRemainIVS2DVSDelay * g_stMDomainOutputData.usVBackHeight / g_stMDomainInputData.usVHeight;

        // Select smaller between measure DVtotal & Calculate DVtotal
        PDATA_WORD(0) = (usDVTotalFrameSync < g_stMDomainOutputData.usVTotal) ? usDVTotalFrameSync : g_stMDomainOutputData.usVTotal;

        // Display front porch
        PDATA_WORD(1) = (PDATA_WORD(0) > (g_stMDomainOutputData.usVBackHeight + g_stMDomainOutputData.usVStart)) ? (PDATA_WORD(0) - (g_stMDomainOutputData.usVBackHeight + g_stMDomainOutputData.usVStart)) : 0;

        // (IVS2DVS diff >= Display front porch) or (transient DVtotal < DVtotal min)
        if((usRemainIVS2DVSDelay >= PDATA_WORD(1)) || ((PDATA_WORD(0) - usRemainIVS2DVSDelay) <= _PANEL_DV_TOTAL_MIN))
        {
            // IVS2DVS delay from large to small --> small_IVS2DVS + IVtotal - large_IVS2DVS
            usRemainIVS2DVSDelay = (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY()) + g_stMDomainInputData.usVTotal - (usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay());

            while((usRemainIVS2DVSDelay > usIVS2DVSChgLimit) && ((usOldIVS2DVSDelay + usIVS2DVSChgLimit) < g_stMDomainInputData.usVTotal))
            {
                usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                usOldIVS2DVSDelay += usIVS2DVSChgLimit;

                ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay);
                ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);

                if(ucTimeoutCounter == 0)
                {
                    break;
                }

                ucTimeoutCounter--;
            }

            // Back up Free run DVtotal
            usDVTotalFreeRun = GET_FREE_RUN_DVTOTAL();

            if((usRemainIVS2DVSDelay > usIVS2DVSChgLimit) && ((usOldIVS2DVSDelay + usIVS2DVSChgLimit) >= g_stMDomainInputData.usVTotal))
            {
                usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                usOldIVS2DVSDelay = usOldIVS2DVSDelay + usIVS2DVSChgLimit - g_stMDomainInputData.usVTotal;

                PDATA_WORD(7) = ((DWORD)g_stMDomainInputData.usVTotal + usIVS2DVSChgLimit) * usDVTotalFrameSync / g_stMDomainInputData.usVTotal + 1;

                SET_FREE_RUN_DVTOTAL(PDATA_WORD(7));

                ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);

                ScalerTimerWaitForEvent(_EVENT_DVS);

                // Set to free-run mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

                if(usRemainIVS2DVSDelay > usIVS2DVSChgLimit)
                {
                    usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                    usOldIVS2DVSDelay += usIVS2DVSChgLimit;

                    ScalerTimerWaitForEvent(_EVENT_IEN_START);
                    ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay);
                    ScalerGlobalIDomainDBApply(_DB_APPLY_NO_POLLING);

                    ScalerTimerWaitForEvent(_EVENT_IEN_START);
                    ScalerTimerWaitForEvent(_EVENT_IVS);

                    // Set to frame-sync mode
                    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);

                    while(usRemainIVS2DVSDelay > usIVS2DVSChgLimit)
                    {
                        usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                        usOldIVS2DVSDelay += usIVS2DVSChgLimit;

                        ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay);
                        ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);

                        if(ucTimeoutCounter == 0)
                        {
                            break;
                        }

                        ucTimeoutCounter--;
                    }

                    ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
                }
                else
                {
                    ScalerTimerWaitForEvent(_EVENT_IEN_START);
                    ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
                    ScalerGlobalIDomainDBApply(_DB_APPLY_NO_POLLING);

                    ScalerTimerWaitForEvent(_EVENT_IEN_START);
                    ScalerTimerWaitForEvent(_EVENT_IVS);

                    // Set to frame-sync mode
                    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
                }
            }
            else if((usRemainIVS2DVSDelay <= usIVS2DVSChgLimit) && ((usOldIVS2DVSDelay + usIVS2DVSChgLimit) >= g_stMDomainInputData.usVTotal))
            {
                PDATA_WORD(7) = ((DWORD)g_stMDomainInputData.usVTotal * 2 - usOldIVS2DVSDelay + usNewIVS2DVSDelay) * usDVTotalFrameSync / g_stMDomainInputData.usVTotal + 1;

                SET_FREE_RUN_DVTOTAL(PDATA_WORD(7));

                ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);

                ScalerTimerWaitForEvent(_EVENT_DVS);

                // Set to free-run mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

                ScalerTimerWaitForEvent(_EVENT_IEN_START);

                ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
                ScalerGlobalIDomainDBApply(_DB_APPLY_NO_POLLING);

                ScalerTimerWaitForEvent(_EVENT_IEN_START);
                ScalerTimerWaitForEvent(_EVENT_IVS);

                // Set to frame-sync mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
            }
            else
            {
                ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
                DebugMessageFS("Error condition", 0);
            }

            SET_FREE_RUN_DVTOTAL(usDVTotalFreeRun);
        }
        else
        {
            ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
        }
    }

    DebugMessageFS("Timeout counter", ucTimeoutCounter);
}

//--------------------------------------------------
// Description  : Calculate Dt Max/Min Value for Scale Up
// Input Value  : None
// Output Value : Calculated Max/Min Dt in 0.01 Lines
//--------------------------------------------------
DWORD ScalerMemoryGetDtMaxMin(void)
{
    BYTE ucMax = 0;
    BYTE ucMin = 100;
    BYTE ucCount = 0;
    BYTE ucPhase = 0;
    WORD usDtMin = 0;
    WORD usDtMax = 0;
    WORD usSUF = 0;
    WORD usFIFOHWidth = 0;
    WORD usDt = 0;
    DWORD ulVFCI = 0;

    // Get Ver filter coef initial value: VFCI * 128
    GET_VER_FILTER_COEF_INI(ulVFCI);

    DebugMessageFS("7.ulVFCI", ulVFCI);

    // Since MSB would be Eliminated by Mod, Only WORD is Required
    usSUF = (WORD)(((DWORD)g_stMDomainInputData.usVHeight << 13) / g_stMDomainOutputData.usVHeight);

    // Get Min and Max Value
    do
    {
        // (VFCI + n * VSF) mod 1
        ucPhase = (BYTE)(((WORD)ulVFCI + (((WORD)ucCount * usSUF) >> 6)) & 0x7F);

        if(ucPhase > ucMax)
        {
            ucMax = ucPhase;
        }

        if(ucPhase < ucMin)
        {
            ucMin = ucPhase;
        }

        ucCount++;
    }
    while(ucCount < 255);

    DebugMessageFS("7.Calculated Max", ucMax);
    DebugMessageFS("7.Calculated Min", ucMin);

    //-------------------------------------------------
    // Get FIFO Input Width: 13 bit
    //-------------------------------------------------
    usFIFOHWidth = ScalerMemoryGetFifoWidth();

    // VFCI * 100
    ulVFCI = (ulVFCI * 100) >> 7;

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        // DtMin = 1  +(VFCI-min)/2+ VSF/2 - VSF*DHActiveEnd/DHTotal/2
        usDtMin = 100 + (ulVFCI >> 1) - (((WORD)ucMin * 100) >> 8) + (DWORD)g_stMDomainInputData.usVHeight  * 50 / g_stMDomainOutputData.usVHeight - (DWORD)g_stMDomainInputData.usVHeight * (g_stMDomainOutputData.usHStart + g_stMDomainOutputData.usHWidth) / g_stMDomainOutputData.usVHeight * 50 / g_stMDomainOutputData.usHWidth;
        usDtMin = usDtMin << 1;

        // DtMax = 1 + FIFODepth/FIFOHWidth each(max-VFCI)/2 each VSF*(DHActiveStart/DHTotal)
        usDtMax = 100 + (DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() * 100 / usFIFOHWidth + (ulVFCI >> 1) - (((WORD)ucMax * 100) >> 8) - (DWORD)g_stMDomainInputData.usVHeight * g_stMDomainOutputData.usHStart / g_stMDomainOutputData.usVHeight * 50 / g_stMDomainOutputData.usHTotal;
        usDtMax = usDtMax << 1;
    }
    else
#endif
    {
        // Dt min = 2 + (VFCI - min - VSF * DHActiveEnd / DHTotal)
        usDtMin = 200 + ulVFCI - (((WORD)ucMin * 100) >> 7) - (DWORD)g_stMDomainInputData.usVHeight * (g_stMDomainOutputData.usHStart + g_stMDomainOutputData.usHWidth) / g_stMDomainOutputData.usVHeight * 100 / g_stMDomainOutputData.usHTotal;

        // Dt max = 2 + FIFODepth / FIFOWIDTH - max + VFCI - VSF * DHActiveSt / DHTotal
        usDtMax = 200 + (DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() * 100 / usFIFOHWidth - (((WORD)ucMax * 100) >> 7) + ulVFCI - (DWORD)g_stMDomainInputData.usVHeight * g_stMDomainOutputData.usHStart / g_stMDomainOutputData.usVHeight * 100 / g_stMDomainOutputData.usHTotal;
    }
    DebugMessageFS("7. DtMax", usDtMax);
    DebugMessageFS("7. DtMin", usDtMin);

    if(GET_D_DOMAIN_REQUEST() == _7_LINES_BEFORE_DEN)
    {
        usDt = ((DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() * 90 / usFIFOHWidth + (DWORD)g_stMDomainInputData.usVHeight * 700 / g_stMDomainOutputData.usVHeight);

        if(usDtMax > usDt)
        {
            usDtMax = usDt;
            DebugMessageFS("7. dt max modifyed", usDtMax);
        }
    }

    return (((DWORD)usDtMax << 16) | usDtMin);
}

//--------------------------------------------------
// Description  : Calculate Dt Value for Scale Up
// Input Value  : None
// Output Value : Calculated Dt in 0.01 Lines
//--------------------------------------------------
WORD ScalerMemoryGetScaleUpDt(void)
{
    WORD usDtMin = 0;
    WORD usDtMax = 0;
    WORD usDt = 0;
    DWORD ulDtMaxMin = ScalerMemoryGetDtMaxMin();

    usDtMin = LOWORD(ulDtMaxMin);
    usDtMax = HIWORD(ulDtMaxMin);

    usDt = (usDtMax + usDtMin) / 2;
    DebugMessageFS("7. Target Dt Value", usDt);

    // Calculat (I porch - 2)
    PDATA_WORD(0) = (g_stMDomainInputData.usVTotal > (g_stMDomainInputData.usVHeight + 2)) ? (g_stMDomainInputData.usVTotal - (g_stMDomainInputData.usVHeight + 2)) : 0;

    // Dt must small than (I portch - 2)
    if(usDt >= (PDATA_WORD(0) * 100))
    {
        usDt = ((PDATA_WORD(0) * 100) + usDtMin) / 2;
        DebugMessageFS("7. Target Dt Value new", usDt);
    }

    return usDt;
}

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
//--------------------------------------------------
// Description  : Memory Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryReset(void)
{
#if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
    ScalerTimerWaitForEvent(_EVENT_IEN_STOP);
    ScalerSdramControlReset();
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
    ScalerTimerWaitForEvent(_EVENT_IEN_STOP);
    ScalerDDR1ControlReset();
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
    // DDR Reset
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
    // DDR Reset
#endif
}

//--------------------------------------------------
// Description  : Memory Power Control
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerMemoryPowerControl(bit bOnOff)
{
#if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)

    // SDRAM Power Control
    ScalerSdramPowerControl(bOnOff);

#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)

    // DDR1 Power Control
    ScalerDDR1PowerControl(bOnOff);

#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)

    // DDR2 Power Control
    ScalerDDR2PowerControl(bOnOff);

#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

    // DDR3 Power Control
    ScalerDDR3PowerControl(bOnOff);

#endif

    if(bOnOff == _ON)
    {
#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
        // FRC Disable capture and display
        ScalerFRCEn(_FRC_CAP_DISP_ALL, _DISABLE);
#endif

#if(_FRC_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_I)
        // Disable FRC
        ScalerRotationSetFRCEn(_FRC_ALL_ONOFF, _DISABLE);
#endif
#endif
#endif
    }
}
#endif // End of #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
#if(_MN_FRAME_TRACKING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : M:N frame tracking
// Input Value  : En: enable / disable
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetFrameTrackingEnable(bit bEn)
{
    // Enable/Disable M:N frame tracking function
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, (BYTE)bEn << 7);
}
#endif
#endif

#if(_FRC_SUPPORT == _ON)
#if(_MN_FRAME_TRACKING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set M:N frame tracking
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryFrameTracking(void)
{
    BYTE ucM = 1;
    BYTE ucN = 1;

    if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, _BIT7) == _BIT7)
    {
        return;
    }

    // Measure DVtotal in frame sync mode
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

    // Wait IVS for get correct data
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);

    PDATA_WORD(0) = ScalerMemoryGetMNRatio();

    ucM = (PDATA_WORD(0) >> 8) & 0xFF;
    ucN = PDATA_WORD(0) & 0xFF;

    // Read DVTotal result
    GET_DVTOTAL_LASTLINE(PDATA_WORD(1));

    // Set to read last line result
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, 0x00);

    // Read Last line result
    GET_DVTOTAL_LASTLINE(PDATA_WORD(0));
    PDATA_WORD(0) = (PDATA_WORD(0) << _D_DOMAIN_PATH);

    // Calulate Display total pixel: DHtotal * DVtotal + last line
    PDATA_DWORD(1) = (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * PDATA_WORD(1) + (PDATA_WORD(0));

    // Fine tune MN frame sync last line
#if(_MN_FINE_TUNE_LASTLINE_SUPPORT == _OFF)
    if(((PDATA_DWORD(1) * ucM) % GET_MDOMAIN_OUTPUT_HTOTAL()) > ((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * 90 / 100))
    {
        // Free run DVtotal
        PDATA_WORD(1) = (PDATA_DWORD(1) * ucM) / GET_MDOMAIN_OUTPUT_HTOTAL() / ucN + 1;

        // Free run Last line
        PDATA_WORD(0) = ((PDATA_DWORD(1) * ucM) % GET_MDOMAIN_OUTPUT_HTOTAL()) / ucN;
    }
    else if(((PDATA_DWORD(1) * ucM) % GET_MDOMAIN_OUTPUT_HTOTAL()) < ((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * 10 / 100))
    {
        // Free run DVtotal
        PDATA_WORD(1) = ((PDATA_DWORD(1) * ucM) - GET_MDOMAIN_OUTPUT_HTOTAL()) / GET_MDOMAIN_OUTPUT_HTOTAL() / ucN + 1;

        // Free run Last line
        PDATA_WORD(0) = (((PDATA_DWORD(1) * ucM) % GET_MDOMAIN_OUTPUT_HTOTAL()) + GET_MDOMAIN_OUTPUT_HTOTAL()) / ucN;
    }
    else
#endif // End of #if(_MN_FINE_TUNE_LASTLINE_SUPPORT == _OFF)
    {
        // Free run DVtotal
        PDATA_WORD(1) = PDATA_DWORD(1) * ucM / GET_MDOMAIN_OUTPUT_HTOTAL() / ucN;

        // Free run Last line
        PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_HTOTAL();
    }

    if(PDATA_WORD(1) < (g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight))
    {
        DebugMessageFRC("FrameTrack-DVT-Error", PDATA_WORD(1));
        PDATA_WORD(1) = _PANEL_DV_TOTAL;
    }

    // Set DVTotal
    SET_FREE_RUN_DVTOTAL(PDATA_WORD(1));

    // Set Frame Sync Watch Dog
    SET_DIS_TIMING_GEN_WD_VTOTAL(PDATA_WORD(1) + 64);

    // Lase line to be multiple of output port
    PDATA_WORD(2) = PDATA_WORD(0) - (PDATA_WORD(0) % _DHTOTAL_MULTIPLE);

    // Set Last line
    SET_FREE_RUN_LAST_LINE(PDATA_WORD(2));

    // Set M:N frame tracking function
    // Set ivs skipped, M = register value +1
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_26_M_FOR_MN_FRAME_RATE);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (ucM - 1));
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_27_N_FOR_MN_FRAME_RATE);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (ucN - 1));
}

//--------------------------------------------------
// Description  : Get M:N ratio
// Input Value  : None
// Output Value : M << 8 | N
//--------------------------------------------------
WORD ScalerMemoryGetMNRatio(void)
{
    BYTE ucM = 1;
    BYTE ucN = 1;

    switch(GET_MEMORY_DVF_SELECT())
    {
        case _2_IVF:

            ucM = 1;
            ucN = 2;

            break;

        case _3_IVF:

            ucM = 1;
            ucN = 3;

            break;

        case _2_5_IVF:

            ucM = 2;
            ucN = 5;

            break;
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if((_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_II) && (_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
        case _5_4_IVF:

            ucM = 5;
            ucN = 4;

            break;

        case _6_5_IVF:

            ucM = 6;
            ucN = 5;

            break;
#endif
#endif
        default:

            break;
    }

    return ((ucM << 8) | (ucN));
}
#endif // End of #if(_MN_FRAME_TRACKING_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Calculate the Line Step and Block Step
// Input Value  : usHorSize --> Horizontal size (unit : 64 bits)
//                usVerSize --> Vertical size
// Output Value : Line Step and Block Step
//--------------------------------------------------
DWORD ScalerMemoryCalculateFrameLineTotalPixel(bit bLineFrameMode, WORD usHorSize, WORD usVerSize)
{
    // FRC to DDR : /64
    DWORD ulHorSize = 0;

    if(bLineFrameMode == _FRAME_MODE) // frame mode
    {
        ulHorSize = ((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() % 64) ?
                    (((DWORD)usHorSize * usVerSize  * GET_MEMORY_DATA_BIT() / 64) + 1) :
                    ((DWORD)usHorSize * usVerSize  * GET_MEMORY_DATA_BIT() / 64);
    }
    else
    {
        // Line Mode
        ulHorSize = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() % 64) ?
                    (((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
                    ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64);

        if((ulHorSize & 0x03) != 0x00)
        {
            ulHorSize += (4 - (ulHorSize & 0x03));
        }
    }

    ulHorSize = ulHorSize * 64 / _MEMORY_BIT_NUM;
    return ulHorSize;
}

//--------------------------------------------------
// Description  : Transfer the Memory Size to Address
// Input Value  : ulTotalSize --> Total Memory size
// Output Value : Line Step Address or Block Step Address
//--------------------------------------------------
DWORD ScalerMemoryAddressConversion(DWORD ulTotalSize)
{
#if((_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM) || (_MEMORY_TYPE_CONFIG == _MEMORY_DDR1))

#if(_MEMORY_SIZE >= _MEMORY_64MB)
    return (((ulTotalSize & 0xFFFF00) << 1) | LOBYTE(ulTotalSize));
#else
    return (((ulTotalSize & 0x000100) << 1) | ((ulTotalSize & 0xFFFE00) << 2) | LOBYTE(ulTotalSize));
#endif

#else

    // _1G_16BIT_DDR3 or ... for 6410, 6193 frc unit : 64 bit (register setting)
    return ulTotalSize * _MEMORY_BIT_NUM / 64;

#endif
}
#endif // End of #if(_FRC_SUPPORT == _ON)

#if(_OD_SUPPORT == _ON)
#if(_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set OD address in 3-block-toggle case
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetODThreeBlockAddress(void)
{
    // 24->60Hz / 24->72Hz uses HW auto 3 block toggle
    if(GET_FRC_3BLOCK_TOGGLE_STATUS() == _ENABLE)
    {
        DWORD ulBlockAddr = 0;
        DWORD ulTotalMemSpace = 0;
        DWORD ulODUseSpace = 0;

        ulTotalMemSpace = (DWORD)_MEMORY_ROW << ((_MEMORY_COL_PER_BANK > 256) ? 11 : 10);
        ulODUseSpace = ((((DWORD)CEILING(_PANEL_DH_WIDTH, _OD_PIXEL_PER_COMP)) * _PANEL_DV_HEIGHT * GET_OD_USE_BIT() / _MEMORY_BIT_NUM) /
                        (_MEMORY_COL_PER_BANK * _MEMORY_BANK) / 10 + 1) << ((_MEMORY_COL_PER_BANK > 256) ? 11 : 10);

        //=========================================
        // Set OD 1st Address
        //=========================================
        // Get 1st Write Address
        ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);
        pData[0] = ScalerGetByte(P5_AD_IN1_MEM_ADDR_H);
        pData[1] = ScalerGetByte(P5_AE_IN1_MEM_ADDR_M);
        pData[2] = ScalerGetByte(P5_AF_IN1_MEM_ADDR_L);
        ulBlockAddr = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | pData[2]) >> ((_MEMORY_COL_PER_BANK > 256) ? 0 : 1);

        g_ulMemoryThreeBlockAddr1 = (ulBlockAddr + ulTotalMemSpace - ulODUseSpace) % ulTotalMemSpace;

        //=========================================
        // Set OD 2nd Address
        //=========================================
        // Get 2nd Write Address
        ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT2);
        pData[0] = ScalerGetByte(P5_AD_IN1_MEM_ADDR_H);
        pData[1] = ScalerGetByte(P5_AE_IN1_MEM_ADDR_M);
        pData[2] = ScalerGetByte(P5_AF_IN1_MEM_ADDR_L);
        ulBlockAddr = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | pData[2]) >> ((_MEMORY_COL_PER_BANK > 256) ? 0 : 1);

        g_ulMemoryThreeBlockAddr2 = (ulBlockAddr + ulTotalMemSpace - ulODUseSpace) % ulTotalMemSpace;

        //=========================================
        // Set OD 3rd Address
        //=========================================
        // Get 3rd Write Address
        ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT3);
        pData[0] = ScalerGetByte(P5_AD_IN1_MEM_ADDR_H);
        pData[1] = ScalerGetByte(P5_AE_IN1_MEM_ADDR_M);
        pData[2] = ScalerGetByte(P5_AF_IN1_MEM_ADDR_L);
        ulBlockAddr = (((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | pData[2]) >> ((_MEMORY_COL_PER_BANK > 256) ? 0 : 1);

        g_ulMemoryThreeBlockAddr3 = (ulBlockAddr + ulTotalMemSpace - ulODUseSpace) % ulTotalMemSpace;

        DebugMessageFRC("3Block-addr1", g_ulMemoryThreeBlockAddr1);
        DebugMessageFRC("3Block-addr2", g_ulMemoryThreeBlockAddr2);
        DebugMessageFRC("3Block-addr3", g_ulMemoryThreeBlockAddr3);
    }
}
#endif // End of #if(_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
#endif // End of #if(_OD_SUPPORT == _ON)

