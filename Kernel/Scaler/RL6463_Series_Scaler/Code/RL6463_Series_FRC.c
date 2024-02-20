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
// ID Code      : RL6463_Series_FRC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __RL6463_SERIES_FRC__

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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
void ScalerFRCInitial(void);
void ScalerFRCEn(BYTE ucSettingPath, bit bEn);
#endif

#if(_FRC_SUPPORT == _ON)
WORD ScalerFRCSetOneFrameDVTotal(void);
void ScalerFRCControl(const StructSDRAMDataInfo *pstFIFOSize);
void ScalerFRCInputCtrl(WORD usHorSize, WORD usVerSize);
void ScalerFRCDisplayCtrl(WORD usHorSize, WORD usVerSize);
void ScalerFRCOneFrameCtrl(DWORD ulIHF, DWORD ulDHF);
void ScalerFRCCompareIHFandDHF(void);

void ScalerFRCWaitWriteFrameBufFinish(void);

#if(_FREEZE_SUPPORT == _ON)
void ScalerFRCDisplayFreeze(bit bEn);
#endif
#endif

void ScalerFRCSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_FRC_TYPE != _FRC_GEN_NONE)
//--------------------------------------------------
// Description  : FRC Initial
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCInitial(void)
{
    // Set memory FIFO MUX to FRC
    ScalerSetBit(P3_C9_LS_FIFO_CTRL0, ~_BIT7, _BIT7);

    // Memory Control Initial
    ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~0xF0, 0x40);

    ScalerSetByte(P5_CD_MN_LINE_NUM_H, 0x00);
    ScalerSetByte(P5_B9_IN1_SDR_CTRL, 0x82);
    ScalerSetByte(P5_CF_MN_DISP_CTRL, 0x05);
    ScalerSetByte(P5_E4_IN1_ONEF_DHF_H, 0x00);
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

    // Wait double buffer
    if(ScalerGlobalGetDBStatus() == _DISABLE)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : FRC function enable/disable
// Input Value  : ucSettingPath: path
// Input Value  : bEn: enable/disable
// Output Value : None
//--------------------------------------------------
void ScalerFRCEn(BYTE ucSettingPath, bit bEn)
{
    // FRC Capture M1
    if((ucSettingPath & _FRC_CAP_MAIN_1) == _FRC_CAP_MAIN_1)
    {
        if((ScalerGlobalGetDBStatus() == _DISABLE) && (ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0))
        {
            // Wait _EVENT_IEN_STOP before FRC Capture Disable
            ScalerTimerWaitForEvent(_EVENT_IEN_STOP);
        }

        if(bEn == _DISABLE)
        {
            // Disable Capture Block
            ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT7), 0x00);
        }
        else
        {
            if(ScalerGetBit(P5_B9_IN1_SDR_CTRL, _BIT7) == 0x00)
            {
                // Enable Capture Block
                ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT7), _BIT7);
            }
        }
    }

    // FRC Display M1
    if((ucSettingPath & _FRC_DISP_MAIN_1) == _FRC_DISP_MAIN_1)
    {
        if(bEn == _DISABLE)
        {
#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
            if((GET_AIO_MODERN_STANDBY_MODE() == _TRUE) &&
               (ScalerGetBit(P5_CF_MN_DISP_CTRL, _BIT0) == 0x00))
            {
                return;
            }
#endif

            // Disable Capture Block
            ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT0), 0x00);
        }
        else
        {
            if(ScalerGetBit(P5_CF_MN_DISP_CTRL, _BIT0) == 0x00)
            {
                // Enable Capture block
                ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT0), _BIT0);
            }
        }
        // Enable Display double buffer
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

        if(ScalerGlobalGetDBStatus() == _DISABLE)
        {
            ScalerTimerWaitForEvent(_EVENT_DVS);
        }
    }
}
#endif // End of #if(_HW_FRC_TYPE != _FRC_GEN_NONE)

#if(_FRC_SUPPORT == _ON)
//-------------------------------------------------
// Description  : Calculate DVTotal for OneFrame FRC
// Input Value  : None
// Output Value : usDVTotal
//-------------------------------------------------
WORD ScalerFRCSetOneFrameDVTotal(void)
{
    DWORD ulFrameDiff = 0;
    DWORD ulActiveRegionDiff = 0;
    WORD usIHF = 0;
    WORD usDHF = 0;
    WORD usDVTotal = 0;

    if((DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 < _PANEL_DV_TOTAL)
    {
        usDHF = (DWORD)_PANEL_MAX_FRAME_RATE * _PANEL_DV_TOTAL / 1000;
    }
    else
    {
        usDHF = (DWORD)_PANEL_MAX_FRAME_RATE * (DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 / 1000;
    }

    usIHF = (DWORD)g_stMDomainInputData.usVFreq * g_stMDomainInputData.usVTotal / 1000;
    ulFrameDiff = (DWORD)1000 * ((DWORD)1000 * g_stMDomainInputData.usVFreq - (DWORD)1000 * _PANEL_MAX_FRAME_RATE) / ((DWORD)g_stMDomainInputData.usVFreq * _PANEL_MAX_FRAME_RATE);
    ulActiveRegionDiff = (DWORD) 1000 * ((DWORD)g_stMDomainOutputData.usVHeight * usIHF - (DWORD)g_stMDomainInputData.usVHeight * usDHF) / ((DWORD)usIHF * usDHF);

    if((ulFrameDiff * 100 / ulActiveRegionDiff) < 125)
    {
        usDVTotal = (DWORD)1000 * g_stMDomainOutputData.usVHeight / ((ulFrameDiff * 100 / 125) + ((DWORD)1000 * g_stMDomainInputData.usVHeight / usIHF)) * 1000 / _PANEL_MAX_FRAME_RATE;
    }
    else if((DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 < _PANEL_DV_TOTAL)
    {
        usDVTotal = _PANEL_DV_TOTAL;
    }
    else
    {
        usDVTotal = (DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000;
    }

    if(usDVTotal > _PANEL_DV_TOTAL_MAX)
    {
        usDVTotal = _PANEL_DV_TOTAL_MAX;
    }
    else if(usDVTotal < _PANEL_DV_TOTAL_MIN)
    {
        usDVTotal = _PANEL_DV_TOTAL_MIN;
    }

    return usDVTotal;
}

//--------------------------------------------------
// Description  : FRC control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCControl(const StructSDRAMDataInfo *pstFIFOSize)
{
    // -----------------------
    // Set FRC IVS2DVSDelay
    // -----------------------
    ScalerFRCAdjustIVS2DVSDelay(pstFIFOSize->usInputVHeight);

    // -----------------------
    // Consider Input Faster Or Slower
    // -----------------------
    ScalerFRCCompareIHFandDHF();

    // -----------------------
    // Set Up FRC Capture
    // -----------------------
    ScalerFRCInputCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // -----------------------
    // Set Up FRC Display
    // -----------------------
    ScalerFRCDisplayCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        // -----------------------
        // Enable FRC
        // -----------------------
        ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT7, _BIT7);
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT0, _BIT0);

        // Enable Display double buffer
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

        // Wait _EVENT_IVS For FRC Run In Single Frame Buffer
        if(ScalerGlobalGetDBStatus() == _DISABLE)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
        }

        // Enable Display double buffer
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);
    }
    else
#endif
    {
        // Wait I-domain Stable Before FRC enable
        if(ScalerGlobalGetDBStatus() == _DISABLE)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
        }

        // -----------------------
        // Enable FRC
        // -----------------------
        ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT7, _BIT7);
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT0, _BIT0);

        // Enable Display double buffer
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

        // Wait _EVENT_IVS For FRC Run In Single Frame Buffer
        if(ScalerGlobalGetDBStatus() == _DISABLE)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
        }

        // Enable Display double buffer
        ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

        if(ScalerGlobalGetDBStatus() == _DISABLE)
        {
            ScalerTimerWaitForEvent(_EVENT_DVS);
        }
    }

    DebugMessageFRC("FRC-H", pstFIFOSize->usInputHWidth);
    DebugMessageFRC("FRC-V", pstFIFOSize->usInputVHeight);
}

//--------------------------------------------------
// Description  : IN1 FIFO Setting for FRC Mode
// Input Value  : ucHorSize --> Horizontal size
//                ucVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCInputCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep;
    DWORD ulTotalSize = 0;
    memset(&stStep, 0, sizeof(StructMemoryLineBlockStep));

    // _LINE_MODE for linestep, there's no blockstep in RL6463
    ulTotalSize = ScalerMemoryCalculateFrameLineTotalPixel(_LINE_MODE, usHorSize, usVerSize);

    // Set Frame mode (line mode may fail at some timing)
    ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~_BIT4, _BIT4);

    stStep.ulLineStep = ScalerMemoryAddressConversion(ulTotalSize);

    // One Frame total pixel for MEMORY (unit : 64 bits)
    ulTotalSize = ((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() % 64) ?
                  (((DWORD)usHorSize * usVerSize  * GET_MEMORY_DATA_BIT() / 64) + 1) :
                  ((DWORD)usHorSize * usVerSize  * GET_MEMORY_DATA_BIT() / 64);

    PDATA_DWORD(0) = ScalerMemoryCalculateNumberAndRemain(ulTotalSize, _FRC_ACCESS_WRITE_LENGTH, 1);

    // Set Capture addresss count = 0
    ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);

    ScalerSetByte(P5_A8_IN1_WATER_LEVEL, _FRC_ACCESS_WRITE_LENGTH);
    ScalerSetByte(P5_A9_IN1_WR_NUM_H, pData[2]);
    ScalerSetByte(P5_AA_IN1_WR_NUM_L, pData[3]);
    ScalerSetByte(P5_AB_IN1_WR_LEN, _FRC_ACCESS_WRITE_LENGTH);
    ScalerSetByte(P5_AC_IN1_WR_REMAIN, pData[1]);
    ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, (BYTE)(_FRC_R_1ST_BLOCK_STA_ADDR_H));
    ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, HIBYTE(_FRC_R_1ST_BLOCK_STA_ADDR_M));
    ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, LOBYTE(_FRC_R_1ST_BLOCK_STA_ADDR_M));
    ScalerSetByte(P5_B0_IN1_LINE_STEP_H, HIBYTE(stStep.ulLineStep));
    ScalerSetByte(P5_B1_IN1_LINE_STEP_L, LOBYTE(stStep.ulLineStep));

    // Set line number
    ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usVerSize >> 8) & 0x0F);
    ScalerSetByte(P5_B8_IN1_LINE_NUM_L, LOBYTE(usVerSize));

    // disable freeze mode
    ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT2), 0x00);

    // Use IVS as synchronous reset
    ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT1), _BIT1);
}

//--------------------------------------------------
// Description  : MAIN FIFO Setting for FRC Mode
// Input Value  : usHorSize --> Horizontal size
//                usVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCDisplayCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep;
    DWORD ulTotalSize = 0;
    memset(&stStep, 0, sizeof(StructMemoryLineBlockStep));

    // _LINE_MODE for linestep, there's no blockstep in RL6463
    ulTotalSize = ScalerMemoryCalculateFrameLineTotalPixel(_LINE_MODE, usHorSize, usVerSize);

    // Set Frame mode (line mode may fail at some timing)
    ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~_BIT4, _BIT4);
    stStep.ulLineStep = ScalerMemoryAddressConversion(ulTotalSize);


    // One Frame total pixel for MEMORY (unit : 64 bits)
    ulTotalSize = ((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() % 64) ?
                  (((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
                  ((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() / 64);

    // Set Pre-read
    PDATA_WORD(2) = ScalerFRCCalculatePreReadLine(usVerSize);
    ScalerSetByte(P5_BC_MN_PRRD_VST_H, pData[4]);
    ScalerSetByte(P5_BD_MN_PRRD_VST_L, pData[5]);

    // Set Pixel number
    ScalerSetBit(P5_BE_MN_PXL_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHorSize) & 0x0F));
    ScalerSetByte(P5_BF_MN_PXL_NUM_L, LOBYTE(usHorSize));

    // Set Water Level
    ScalerSetByte(P5_C0_MN_WTLVL, _FRC_ACCESS_READ_LENGTH);

    // Set Number, Length, Remain ( size = number x length +remain)
    PDATA_DWORD(0) = ScalerMemoryCalculateNumberAndRemain(ulTotalSize, _FRC_ACCESS_READ_LENGTH, 0);
    ScalerSetByte(P5_C2_MN_READ_NUM_H, pData[2]);
    ScalerSetByte(P5_C3_MN_READ_NUM_L, pData[3]);
    ScalerSetByte(P5_C4_MN_READ_LEN, _FRC_ACCESS_READ_LENGTH);
    ScalerSetByte(P5_C5_MN_READ_REMAIN, pData[1]);

    // Set Read address
    ScalerSetByte(P5_C6_MN_READ_ADDR_H, (BYTE)(_FRC_R_1ST_BLOCK_STA_ADDR_H));
    ScalerSetByte(P5_C7_MN_READ_ADDR_M, HIBYTE(_FRC_R_1ST_BLOCK_STA_ADDR_M));
    ScalerSetByte(P5_C8_MN_READ_ADDR_L, LOBYTE(_FRC_R_1ST_BLOCK_STA_ADDR_M));

    // Set Line step
    ScalerSetBit(P5_C9_MN_LINE_STEP_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(stStep.ulLineStep) & 0x3F);
    ScalerSetByte(P5_CA_MN_LINE_STEP_L, LOBYTE(stStep.ulLineStep));

    // Set Line number
    ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usVerSize >> 8) & 0x0F);
    ScalerSetByte(P5_CE_MN_LINE_NUM_L, LOBYTE(usVerSize));

    // Use information from Capture
    ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT2 | _BIT1), 0x00);

    // Enable Display double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

    // Wait double buffer
    if(ScalerGlobalGetDBStatus() == _DISABLE)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : Set OneFrame FRC
// Input Value  : IHF, DHF
// Output Value : None
//--------------------------------------------------
void ScalerFRCOneFrameCtrl(DWORD ulIHF, DWORD ulDHF)
{
    SWORD shMargin = 0;
    WORD usPreRead = 0;
    WORD usLeadingLine = 0;
    WORD usFIFOVHeight = 0;


    ScalerGetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_00_DISPLAY_READ_WID_BSU_H, 3, &pData[0], _AUTOINC);
    // FIFO V Height
    usFIFOVHeight = ((((WORD)pData[0] & 0x0F) << 8) | pData[2]);

    if(ulIHF > ulDHF)
    {
        usPreRead = g_stMDomainOutputData.usVStart - 3;
        shMargin = (SWORD)0 - (ulDHF * usFIFOVHeight / ulIHF - _LINE_MARGIN);
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT3, _BIT3);
    }
    else
    {
        // forbidden lines
        usPreRead = ((DWORD)g_stMDomainOutputData.usVHeight * ulDHF / ulIHF - g_stMDomainOutputData.usVHeight);
        usPreRead = (usPreRead < 10) ? 10 : usPreRead;

        if(g_stMDomainInputData.usVFreq > _PANEL_MAX_FRAME_RATE)
        {
            // input frame leading lines in display
            usLeadingLine = (DWORD)(g_stMDomainInputData.usVFreq - _PANEL_MAX_FRAME_RATE) * _PANEL_DV_TOTAL_MIN / g_stMDomainInputData.usVFreq;
        }
        else if(g_stMDomainInputData.usVFreq < _PANEL_MIN_FRAME_RATE)
        {
            // input frame leading lines in display
            usLeadingLine = (DWORD)(_PANEL_MAX_FRAME_RATE - g_stMDomainInputData.usVFreq) * _PANEL_DV_TOTAL_MIN / g_stMDomainInputData.usVFreq;
        }

        if(usPreRead <= g_stMDomainOutputData.usVStart)
        {
            if((usPreRead * 15 / 10) < usLeadingLine)
            {
                if((usPreRead * 15 / 10) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead = 0;
                }
                else
                {
                    usPreRead = g_stMDomainOutputData.usVStart - usPreRead * 15 / 10;
                }
            }
            else if((usPreRead * 13 / 10) < usLeadingLine)
            {
                if((usLeadingLine - 1) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead = 0;
                }
                else
                {
                    usPreRead = g_stMDomainOutputData.usVStart - (usLeadingLine - 1);
                }
            }
            else
            {
                if((usPreRead * 13 / 10) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead = 0;
                }
                else
                {
                    usPreRead = g_stMDomainOutputData.usVStart - usPreRead * 13 / 10;
                }
            }

            shMargin = (SWORD)0 - (g_stMDomainOutputData.usVHeight - 1 + _LINE_MARGIN);
        }
        else
        {
            usPreRead = g_stMDomainInputData.usVHeight;
            shMargin = ((SWORD)0 - (((ulDHF / ulIHF) - 1) * usFIFOVHeight + _LINE_MARGIN));
        }
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT3, 0x00);
    }

    ScalerSetByte(P5_E4_IN1_ONEF_DHF_H, (ulDHF >> 16) | _BIT7);
    ScalerSetByte(P5_E8_IN1_LINE_MAGN_L, LOBYTE(shMargin));
    ScalerSetByte(P5_E9_IN1_ONEF_MAGN_H, (HIBYTE(shMargin) << 4) + HIBYTE(usPreRead));
    ScalerSetByte(P5_EA_IN1_PRRD_MAGN_L, LOBYTE(usPreRead));

    // Write in double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~(_BIT4 | _BIT0), _BIT4);

    // Disable Osd Overlay In Case of Garbage
    pData[0] = ScalerGetByte(P0_6C_OVERLAY_CTRL);

    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT0, 0x00);

    // Set Frame sync
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    // Set Free Run
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT0, (pData[0] & _BIT0));
}

//--------------------------------------------------
// Description  : Compare which one of IHF and DHF is bigger, and see if they are too similar
// Input Value  : ulFreq --> DCLK
// Output Value : output is true when they are too similar
//--------------------------------------------------
void ScalerFRCCompareIHFandDHF(void)
{
    DWORD ulIHF = 0;
    DWORD ulDHF = 0;

    if(g_stMDomainOutputData.usVHeight > g_stMDomainInputData.usVHeight)
    {
        // IHF'
        ulIHF = (DWORD)g_stMDomainInputData.usHFreq;
        // DHF'
        ulDHF = ((DWORD)GET_D_CLK_FREQ() / g_stMDomainOutputData.usHTotal * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight * 10);
    }
    else
    {
        // IHF'
        ulIHF = GET_MDOMAIN_IHF_IN_DDOMAIN();
        // DHF'
        ulDHF = ((DWORD)GET_D_CLK_FREQ() / g_stMDomainOutputData.usHTotal * 10);
    }

    // Set FRC Style
    if(ulIHF > ulDHF)
    {
        // Set input fast than display
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT3, _BIT3);
    }
    else
    {
        // Set input slower than display
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT3, 0x00);
    }

    // Write in double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

    if(GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY)
    {
        // Set Frame sync when FRC
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerFRCOneFrameCtrl(ulIHF, ulDHF);
    }
}

//--------------------------------------------------
// Description  : Wait Capture Write Memory Block Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCWaitWriteFrameBufFinish(void)
{
    return;
}

#if(_FREEZE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FRC freeze mode
// Input Value  : ON --> Freeze
// Output Value : None
//--------------------------------------------------
void ScalerFRCDisplayFreeze(bit bEn)
{
    ScalerTimerWaitForEvent(_EVENT_IEN_STOP);

    if(bEn == _ON)
    {
        ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT7, 0x00);
    }
    else
    {
        ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT7, _BIT7);
    }
}
#endif // End of #if(_FREEZE_SUPPORT == _ON)

#endif // End of #if(_FRC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : D Domain Source Select
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect)
{
    if(enumSourceSelect == _DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE)
    {
        // Set Frame sync with line buffer mode
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT2 | _BIT1), _BIT2);
    }
    else
    {
        ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT2 | _BIT1), 0x00);
    }

    // Enable Display double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);
}

