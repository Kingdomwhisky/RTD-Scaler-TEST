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
// ID Code      : ScalerFRC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_FRC__

#include "ScalerFunctionInclude.h"

#if(_FRC_SUPPORT == _ON)
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
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
BYTE g_ucDispLatecnyRatio;
#endif
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
WORD g_usAspectRatioMinDVHeight;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
WORD ScalerFRCGetIVS2DVSDelayMax(WORD usFRCVerSize);
#endif

WORD ScalerFRCCalculatePreReadLine(WORD usFRCVerSize);
void ScalerFRCAdjustIVS2DVSDelay(WORD usFRCVerSize);
#if((_FRC_MEMORY_2_FRAME_SUPPORT == _ON) && (_ONE_FRAME_FRC_SUPPORT == _ON))
bit ScalerFRCCheckDoubleFrameBuffer(WORD usInputHWidth, WORD usInputVHeight);
#endif
BYTE ScalerFRCIVS2DVSDelayMargin(void);

#if(_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
void ScalerFRCSetDisplayAutoBlkToggle(void);
void ScalerFRCSetDisplayAutoBlkToggleEnable(bit bEn);
void ScalerFRCSetHWAutoBlockToggle(void);
void ScalerFRCSetInputAutoBlkToggle(void);
#endif
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
void ScalerFRCSetAspectRatioDDomain(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get IVS2DVSDelay Max Value in Frame Sync Mode
// Input Value  : usFRCVerSize : Input VHeight
// Output Value : IVS2DVSDelay Max Value
//--------------------------------------------------
WORD ScalerFRCGetIVS2DVSDelayMax(WORD usFRCVerSize)
{
    WORD usDHF = 0x00;
    WORD usIPeriod = 0x00;
    WORD usDStartPeriod = 0x00;

    if(GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY)
    {
        // DHFreq
        usDHF = ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal);

        // (IVStart + IDEN) Period
        usIPeriod = (g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight);

        // Pre-read Period
        usDStartPeriod = ((DWORD)ScalerFRCCalculatePreReadLine(usFRCVerSize) * g_stMDomainInputData.usHFreq / usDHF);

        return (usIPeriod - (usDStartPeriod + _FRC_IVS2DVSDELAY_MARGIN));
    }

    return 0;
}
#endif // End of #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Calculate FRC Pre-read Line
// Input Value  : usFRCVerSize --> FRC Output Vertical Size
// Output Value : The line after DVS that FRC display start to access
//--------------------------------------------------
WORD ScalerFRCCalculatePreReadLine(WORD usFRCVerSize)
{
    // preread = den_start - _PRE_READ_MEMORY x VSU factor - 1
    // VSU >= 1
    usFRCVerSize = (((DWORD)g_stMDomainOutputData.usVHeight * 10) / usFRCVerSize) * _PRE_READ_MEMORY + 1;
    usFRCVerSize = ((usFRCVerSize % 10) ? (usFRCVerSize / 10 + 1) : (usFRCVerSize / 10));

    return ((g_stMDomainOutputData.usVStart > usFRCVerSize) ? ((g_stMDomainOutputData.usVStart - usFRCVerSize)) : (0));
}

//--------------------------------------------------
// Description  : Adjust IVS2DVS Delay for Aspect Ratio Function
// Input Value  : usFRCVerSize : FRC Veritcal Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCAdjustIVS2DVSDelay(WORD usFRCVerSize)
{
    WORD usPreReadLine = 0;
    WORD usIHFreq = 0;
    WORD usDHFreq = 0;

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
    WORD usDelayMax = 0;
#endif
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
    WORD usVstbk = GET_MDOMAIN_OUTPUT_VSTART();
    WORD usVHeightbk = GET_MDOMAIN_OUTPUT_VHEIGHT();
    WORD usVBHeightbk = GET_MDOMAIN_OUTPUT_VBHEIGHT();
#endif

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_II))
    WORD usInputVHeight = 0;
#endif

    BYTE ucMargin = ScalerFRCIVS2DVSDelayMargin();
    DWORD ulIVStoDVSPixels = 0;

    // IHFreq, unit: 0.01kHz
    // IHF = Measure_clk * (IHtotal * IVheight' + IHwidth') / (IHtotal * Active_count)
    // IHF = (Measure_clk * IHtotal * IVheight'/ (IHtotal * Active_count)) + (Measure_clk * (IHtotal - IHporch) * (E/O or single) / (IHtotal * Active_count))
    // IHF = (Measure_clk * IVheight'/ Active_count) + (Measure_clk * (E/O or single) / Active_count) - (Measure_clk * (E/O or single) * (IHtotal - IHwidth) / (IHtotal * Active_count))

    // input region cnt calculation:
    // vsd disable single   = IHtotal * (IVheight - 1) + IHwidth
    // vsd enable single    = IHtotal * (IVheight - 1 + 1(SD)) + IHwidth
    // vsd disable even/odd = (IHtotal * (IVheight / 2 - 1) + IHwidth) * 2
    ///                     = IHtotal * (IVheight - 2) + IHwidth * 2
    // vsd enable even/odd  = (IHtotal * (IVheight / 2 - 1 + 1(SD)) + IHwidth) * 2
    ///                     = IHtotal * IVheight + IHwidth * 2

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        pData[0] = 2;
        if(GET_V_SCALE_DOWN() == _TRUE)
        {
            PDATA_WORD(2) = (g_stMDomainInputData.usVHeight);
        }
        else
        {
            PDATA_WORD(2) = g_stMDomainInputData.usVHeight - 2;
        }
    }
    else
#endif
    {
        pData[0] = 1;
        if(GET_V_SCALE_DOWN() == _TRUE)
        {
            PDATA_WORD(2) = (g_stMDomainInputData.usVHeight);
        }
        else
        {
            PDATA_WORD(2) = (g_stMDomainInputData.usVHeight - 1);
        }
    }

    usIHFreq = ((DWORD)_MEASURE_CLK * 10 * PDATA_WORD(2) / g_ulInputActiveRegionBackUp * 10) +
               (((DWORD)_MEASURE_CLK * 10 * PDATA_WORD(2)) % g_ulInputActiveRegionBackUp * 10 / g_ulInputActiveRegionBackUp) +
               ((DWORD)_MEASURE_CLK * 100 * pData[0] / g_ulInputActiveRegionBackUp) -
               ((DWORD)_MEASURE_CLK * 10 * pData[0] * (g_stMDomainInputData.usHTotal - g_stMDomainInputData.usHWidth) / g_ulInputActiveRegionBackUp / g_stMDomainInputData.usHTotal * 10);

    // DHFreq, unit: 0.01kHz
    usDHFreq = ((DWORD)GET_D_CLK_FREQ() * 100 / g_stMDomainOutputData.usHTotal);

    switch(GET_MEMORY_SELECT())
    {
        case _FRAME_SYNC_MEMORY:

            // IVS2DVS line skip disable
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT3, _BIT3);
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
            ScalerFRCSetAspectRatioDDomain();
#endif
            usPreReadLine = ScalerFRCCalculatePreReadLine(usFRCVerSize);
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
            usDelayMax = ScalerFRCGetIVS2DVSDelayMax(usFRCVerSize);
#endif

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_II))

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
            {
                // I_M2_DEN_stop should be finish before D_M1_preread
                usInputVHeight = g_stMDomainInputData.usVHeight + 1;
            }
            else
#endif
            {
                usInputVHeight = g_stMDomainInputData.usVHeight;
            }

            if((GET_ROT_TYPE() == _ROT_CW180) || (GET_ROT_TYPE() == _ROT_VER_MIRROR))
            {
                // Consider IDEN period and (DDEN + pre-read) period
                if(usInputVHeight >= ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight - usPreReadLine) * usIHFreq / usDHFreq))
                {
                    // Roundup: (IVS2DVS_delay_min + IVS2DVS_delay_max) / 2
                    PDATA_WORD(0) = ((g_stMDomainInputData.usVStart + usInputVHeight) + g_stMDomainInputData.usVTotal);
                    PDATA_WORD(0) = (PDATA_WORD(0) >> 1) + (PDATA_WORD(0) % 2);
                }
                else
                {
                    // IVS2DVS delay max
                    PDATA_WORD(0) = g_stMDomainInputData.usVTotal + g_stMDomainInputData.usVStart + usInputVHeight -
                                    ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight) * usIHFreq / usDHFreq) -
                                    ((((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight) * usIHFreq % usDHFreq) != 0x00) ? 1 : 0);

                    if(PDATA_WORD(0) > g_stMDomainInputData.usVTotal)
                    {
                        PDATA_WORD(0) = g_stMDomainInputData.usVTotal;
                    }

                    // Rounddown (IVS2DVS_delay_min + IVS2DVS_delay_max) / 2
                    PDATA_WORD(0) = (((g_stMDomainInputData.usVStart + usInputVHeight) + PDATA_WORD(0)) / 2);
                }

                PDATA_WORD(0) -= ((DWORD)usPreReadLine * usIHFreq / usDHFreq);
            }
            else
#endif
            {
                // Consider IDEN period and (DDEN + pre-read) period
                if(g_stMDomainInputData.usVHeight >= ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight - usPreReadLine) * usIHFreq / usDHFreq))
                {
                    // (IVStart + IDEN) Period
                    PDATA_WORD(0) = (g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight);

                    // (DVStart + DDEN) Period
                    PDATA_WORD(1) = ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight) * usIHFreq / usDHFreq);
                }
                else
                {
                    // IVStart Period
                    PDATA_WORD(0) = g_stMDomainInputData.usVStart;

                    // FRC_Display pre-read Period
                    PDATA_WORD(1) = (DWORD)usPreReadLine * usIHFreq / usDHFreq;
                }

                if(PDATA_WORD(0) > PDATA_WORD(1))
                {
                    PDATA_WORD(0) = PDATA_WORD(0) - PDATA_WORD(1) + ucMargin;
                }
                else
                {
                    PDATA_WORD(0) = ucMargin;
                }

                PDATA_WORD(1) = ((g_stMDomainInputData.usVStart + ucMargin) > ((DWORD)usPreReadLine * usIHFreq / usDHFreq)) ? ((g_stMDomainInputData.usVStart + ucMargin) - ((DWORD)usPreReadLine * usIHFreq / usDHFreq)) : 0;

                if(PDATA_WORD(1) > PDATA_WORD(0))
                {
                    PDATA_WORD(0) = PDATA_WORD(1);
                }

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
                PDATA_WORD(1) = ((DWORD)usDelayMax - PDATA_WORD(0)) * GET_DISP_LATENCY_RATIO() / 100;
                PDATA_WORD(0) += PDATA_WORD(1);

                // ivs2dvsdelay must be smaller than IVTotal when frame sync
                if(PDATA_WORD(0) >= g_stMDomainInputData.usVTotal)
                {
                    PDATA_WORD(0) = g_stMDomainInputData.usVTotal - 1;
                }
#endif
            }

            break;

        case _FREE_RUN_MEMORY:

            PDATA_WORD(0) = (g_stMDomainInputData.usVTotal + g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight);
            PDATA_WORD(0) -= ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight) * usIHFreq / usDHFreq);

            if(PDATA_WORD(0) > 255)
            {
                PDATA_WORD(0) = 0xFE - 32;
            }
            else
            {
                PDATA_WORD(0) -= 32;
            }

            break;

        default:
        case _MN_FRAME_SYNC_MEMORY:

#if(_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
            switch(GET_MEMORY_DVF_SELECT())
            {
                case _6_5_IVF:
                case _5_4_IVF:

                    PDATA_WORD(0) = g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight - ((DWORD)usPreReadLine * usIHFreq / usDHFreq) + 1;

                    break;

                case _2_5_IVF:

                    // lower bound : dvtotal+dvstart+dvheight+ivs2dvsdelay > ivstart + ivheight
                    PDATA_WORD(0) = g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight;
                    PDATA_WORD(0) -= ((DWORD)(g_stMDomainOutputData.usVTotal + g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight) * usIHFreq / usDHFreq);

                    // upper bound : 3 * dvtotal+dvstart+ivs2dvsdelay < IVtotal + ivstart + ivheight/2
                    PDATA_WORD(1) = g_stMDomainInputData.usVTotal + g_stMDomainInputData.usVStart + (g_stMDomainInputData.usVHeight / 2);
                    PDATA_WORD(1) -= ((DWORD)((g_stMDomainOutputData.usVTotal * 3) + g_stMDomainOutputData.usVStart) * usIHFreq / usDHFreq);

                    PDATA_WORD(0) = (PDATA_WORD(0) + PDATA_WORD(1)) / 2;

                    break;

                default:

                    PDATA_WORD(0) = 0x01;
                    break;
            }
#else
            PDATA_WORD(0) = 0x01;
#endif
            if((GET_MEMORY_DVF_SELECT() == _2_IVF) && (GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER))
            {
                // dden start must be ahead of iden start : ivs > ivs2dvsdelay + dvs
                if(g_stMDomainInputData.usVStart <= (PDATA_WORD(0) + CEILING_OF_INT_DIVISION(((DWORD)g_stMDomainOutputData.usVStart * usIHFreq), usDHFreq)))
                {
                    // ivs + ivs2dvsdelay < dvs + dvh + ivs2dvsdelay
                    PDATA_WORD(0) = g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight + 1; // 1 (margin)
                    PDATA_WORD(0) -= ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight) * usIHFreq / usDHFreq);
                }
            }
            break;
    }

    if((PDATA_WORD(0) > 0xF00) || (PDATA_WORD(0) == 0))
    {
        PDATA_WORD(0) = 0x01;
    }

    // Disable Frame Sync Fine Tune
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);

    ulIVStoDVSPixels = (DWORD)PDATA_WORD(0) * g_stMDomainInputData.usHTotal;

    if(GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY)
    {
        if(ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE)
        {
            // Convert DVline limit to IVline
            WORD usIVS2DVSChgLimit = ((DWORD)_PANEL_DV_LINE_CHG_LIMIT * g_stMDomainOutputData.usHTotal / GET_D_CLK_FREQ() * g_stMDomainInputData.usHFreq / 10) +
                                     ((DWORD)_PANEL_DV_LINE_CHG_LIMIT * g_stMDomainOutputData.usHTotal % GET_D_CLK_FREQ() * g_stMDomainInputData.usHFreq / 10 / GET_D_CLK_FREQ());

            // Get Old IVS2DVS + IVSdelay (I line)
            PDATA_WORD(0) = (ScalerMemoryGetIVS2DVSDelayPixel() / g_stMDomainInputData.usHTotal);

            ScalerMemoryFineTuneIVS2DVSDelay(PDATA_WORD(0), (ulIVStoDVSPixels / g_stMDomainInputData.usHTotal), usIVS2DVSChgLimit);
        }

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
        {
            ulIVStoDVSPixels = (ulIVStoDVSPixels >> 1);
        }
#endif

        PDATA_WORD(2) = (ulIVStoDVSPixels / g_stMDomainInputData.usHTotal);
        PDATA_WORD(3) = (ulIVStoDVSPixels - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> 4;
        PDATA_WORD(4) = 0x0000;

        pData[10] = ulIVStoDVSPixels - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << 4);
        pData[11] = 0x00;

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
    else
    {
        ScalerMemorySetIVS2DVSLineDelay((ulIVStoDVSPixels / g_stMDomainInputData.usHTotal));

        // Set Frame Sync Mode Delay Fine Tune = 0
        SET_IVS2DVS_DELAY_16ICLK1(0x0000);
        SET_IVS2DVS_DELAY_16ICLK2(0x0000);

        // IVS2DVS iclk1 delay, unit: 1 pixel
        ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0xF0, 0x00);

        // IVS2DVS iclk2 delay, unit: 1 pixel
        ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0x0F, 0x00);
    }

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
    SET_MDOMAIN_OUTPUT_VSTART(usVstbk);
    SET_MDOMAIN_OUTPUT_VHEIGHT(usVHeightbk);
    SET_MDOMAIN_OUTPUT_VBHEIGHT(usVBHeightbk);
#endif
}

#if((_FRC_MEMORY_2_FRAME_SUPPORT == _ON) && (_ONE_FRAME_FRC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : FRC 2 Frame Buffer Case
// Input Value  : N.A.
// Output Value : _TRUE: 2 Frame Buffer
//--------------------------------------------------
bit ScalerFRCCheckDoubleFrameBuffer(WORD usInputHWidth, WORD usInputVHeight)
{
    WORD usDHF = ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal); // unit: 0.1ms
    WORD usPreReadLine = ScalerFRCCalculatePreReadLine(usInputVHeight);

    // Consider Double Frame Size
    if(_MEMORY_ROW > ((DWORD)usInputHWidth * GET_MEMORY_DATA_BIT() / _MEMORY_BIT_NUM * usInputVHeight * 2 / _MEMORY_COL_PER_BANK / _MEMORY_BANK))
    {
        return _TRUE;
    }
    else
    {
        // the number that multiple by 10 or 100 below is to get the digit after decimal point
        PDATA_WORD(0) = (DWORD)(usPreReadLine + g_stMDomainOutputData.usVHeight) * 100 / usDHF;
        PDATA_WORD(1) = (DWORD)g_stMDomainInputData.usVHeight * 100 / g_stMDomainInputData.usHFreq;

        // get the ratio of ((dden/dhf) / (iden/ihf)) or ((iden/ihf) / (dden/dhf))
        if(PDATA_WORD(0) > PDATA_WORD(1))
        {
            PDATA_WORD(0) = PDATA_WORD(0) * 10 / PDATA_WORD(1);
        }
        else
        {
            PDATA_WORD(0) = PDATA_WORD(1) * 10 / PDATA_WORD(0);
        }

        // 11 & 18 are from experiment
        // >18 or <11 are not suitable for one frame frc, force to double frame
        if((PDATA_WORD(0) < 11) || (PDATA_WORD(0) > 18))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Calculate IVS2DVS delay margin
// Input Value  : N.A.
// Output Value : IVS2DVS delay margin
//--------------------------------------------------
BYTE ScalerFRCIVS2DVSDelayMargin(void)
{
#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // Margin need to consider Fifo margin, line buffer margin and setting margin
        // Fifo margin: FIFO size/ format/ IHwidth * 2
        pData[0] = ((DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() / g_stMDomainInputData.usHWidth);
        pData[0] += ((((DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() % g_stMDomainInputData.usHWidth) != 0x00) ? 1 : 0);

        pData[0] += (_FRC_IVS2DVSDELAY_LINE_BUFFER_MARGIN + _FRC_IVS2DVSDELAY_MARGIN_FREESYNC);
    }
    else
#endif
    {
        pData[0] = _FRC_IVS2DVSDELAY_MARGIN;
    }

    return pData[0];
}

#if(_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set display adderss for auto block toggle
// Input Value  : ulBlockStep --> block step(single frame input and display)
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDisplayAutoBlkToggle(void)
{
    // 1st Read Address
    PDATA_DWORD(0) = (((DWORD)_FRC_R_1ST_BLOCK_STA_ADDR_H << 16) | ((DWORD)_FRC_R_1ST_BLOCK_STA_ADDR_M << 8) | 0x00);

#if((_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM) || (_MEMORY_TYPE_CONFIG == _MEMORY_DDR1))
    // Column = 256 :
    // Capture Column [9:0] --> 1'b0, Col[8:0]
    // Display Column [8:0]
    PDATA_DWORD(0) = (PDATA_DWORD(0) >> 1);
#if(_MEMORY_BANK == 2)
    // Capture Bank [1:0] --> 1'b0, Bank[0]
    // Display Bank [0]
    PDATA_DWORD(0) = (PDATA_DWORD(0) >> 1);
#endif
#endif

    ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetByte(P5_C6_MN_READ_ADDR_H, pData[1]);
    ScalerSetByte(P5_C7_MN_READ_ADDR_M, pData[2]);
    ScalerSetByte(P5_C8_MN_READ_ADDR_L, pData[3]);
    DebugMessageFRC("-D addr1 FRC", PDATA_DWORD(0));

    // 2nd Read Address
    PDATA_DWORD(0) = (((DWORD)_FRC_R_2ND_BLOCK_STA_ADDR_H << 16) | ((DWORD)_FRC_R_2ND_BLOCK_STA_ADDR_M << 8) | 0x00);

#if((_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM) || (_MEMORY_TYPE_CONFIG == _MEMORY_DDR1))
    // Column = 256 :
    // Capture Column [9:0] --> 1'b0, Col[8:0]
    // Display Column [8:0]
    PDATA_DWORD(0) = (PDATA_DWORD(0) >> 1);
#if(_MEMORY_BANK == 2)
    // Capture Bank [1:0] --> 1'b0, Bank[0]
    // Display Bank [0]
    PDATA_DWORD(0) = (PDATA_DWORD(0) >> 1);
#endif
#endif

    ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT2);
    ScalerSetByte(P5_C6_MN_READ_ADDR_H, pData[1]);
    ScalerSetByte(P5_C7_MN_READ_ADDR_M, pData[2]);
    ScalerSetByte(P5_C8_MN_READ_ADDR_L, pData[3]);
    DebugMessageFRC("-D addr2 FRC", PDATA_DWORD(0));

    // 3rd Read Address
    PDATA_DWORD(0) = (((DWORD)_FRC_R_3RD_BLOCK_STA_ADDR_H << 16) | ((DWORD)_FRC_R_3RD_BLOCK_STA_ADDR_M << 8) | 0x00);

#if((_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM) || (_MEMORY_TYPE_CONFIG == _MEMORY_DDR1))
    // Column = 256 :
    // Capture Column [9:0] --> 1'b0, Col[8:0]
    // Display Column [8:0]
    PDATA_DWORD(0) = (PDATA_DWORD(0) >> 1);
#if(_MEMORY_BANK == 2)
    // Capture Bank [1:0] --> 1'b0, Bank[0]
    // Display Bank [0]
    PDATA_DWORD(0) = (PDATA_DWORD(0) >> 1);
#endif
#endif

    ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT3);
    ScalerSetByte(P5_C6_MN_READ_ADDR_H, pData[1]);
    ScalerSetByte(P5_C7_MN_READ_ADDR_M, pData[2]);
    ScalerSetByte(P5_C8_MN_READ_ADDR_L, pData[3]);
    DebugMessageFRC("-D addr3 FRC", PDATA_DWORD(0));
}

//--------------------------------------------------
// Description  : Set display adderss for auto block toggle
// Input Value  : En: enable / disable
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDisplayAutoBlkToggleEnable(bit bEn)
{
    // Enable M:N HW auto toggle's double buffer
    ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~_BIT5, _BIT5);

    if(bEn == _ENABLE)
    {
        // Input Hardware auto toggle address enable
        ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~_BIT4, _BIT4);

        // Display Hardware auto toggle among address enable
        ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~_BIT4, _BIT4);
    }
    else
    {
        // Input Hardware auto toggle address disable
        ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~_BIT4, 0x00);

        // Display Hardware auto toggle among address disable
        ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~_BIT4, 0x00);
    }

    // Hardware auto toggle M:N double buffer ready
    ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~_BIT6, _BIT6);

    // Wait dobule buffer
    ScalerTimerPollingFlagProc(_M_N_AUTO_BLK_TOGGLE_STABLE_TIME, P5_BA_IN1_MADDR_TOG_CTL, _BIT6, 0);
}

//--------------------------------------------------
// Description  : Set auto block toggle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetHWAutoBlockToggle(void)
{
    BYTE ucM = 1;
    BYTE ucN = 1;

    PDATA_WORD(0) = ScalerMemoryGetMNRatio();

    ucM = (PDATA_WORD(0) >> 8) & 0xFF;
    ucN = PDATA_WORD(0) & 0xFF;

    // IVS to DVS shift value for hardware auto toggle among three initial read address
    // Set Shift = 2 _3_IVF, _2_5_IVF
    ScalerSetBit(P5_CB_MN_BLOCK_STEP_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 2 << 4);

    // Multiple of hardware auto toggle among three initial read address, it is (N/M - 1)
    PDATA_WORD(0) = ucN / ucM - 1;

    ScalerSetBit(P5_BE_MN_PXL_NUM_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (PDATA_WORD(0) << 4));

    // Remain of hardware auto toggle among three initial read address, and it is (N%M)/N * 2^10.(11bit in total)
    PDATA_WORD(0) = ((ucN % ucM) << 10) / ucN;
    PDATA_WORD(0) += 1;

    ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT7 | _BIT6 | _BIT5), ((pData[0] << 5) & 0xFF));
    ScalerSetByte(P5_EB_MN_MADDR_TOG_REM, (pData[1] & 0xFF));
}

//--------------------------------------------------
// Description  : Set Input adderss for auto block toggle
// Input Value  : ulBlockStep --> block step(single frame input and display)
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetInputAutoBlkToggle(void)
{
    // 1st write address
    PDATA_DWORD(0) = ((DWORD)_FRC_R_2ND_BLOCK_STA_ADDR_H << 16) + ((DWORD)_FRC_R_2ND_BLOCK_STA_ADDR_M << 8);

    ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
    ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
    ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
    DebugMessageFRC("-I_addr1 FRC", PDATA_DWORD(0));

    // 2nd write address
    PDATA_DWORD(0) = ((DWORD)_FRC_R_3RD_BLOCK_STA_ADDR_H << 16) + ((DWORD)_FRC_R_3RD_BLOCK_STA_ADDR_M << 8);

    ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT2);
    ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
    ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
    ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
    DebugMessageFRC("-I_addr2 FRC", PDATA_DWORD(0));

    // 3rd write address
    PDATA_DWORD(0) = ((DWORD)_FRC_R_1ST_BLOCK_STA_ADDR_H << 16) + ((DWORD)_FRC_R_1ST_BLOCK_STA_ADDR_M << 8);

    ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT3);
    ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
    ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
    ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
    DebugMessageFRC("-I_addr3 FRC", PDATA_DWORD(0));
}
#endif // End of #if(_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
//--------------------------------------------------
// Description  : Set Dvst, Dvheight when aspect ratio wothout mute
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetAspectRatioDDomain(void)
{
    WORD usAspNewDVst = 0;
    if(GET_ASPECT_RATIO_MIN_DVH() != 0)
    {
        if(GET_MDOMAIN_OUTPUT_VHEIGHT() > GET_ASPECT_RATIO_MIN_DVH())
        {
            usAspNewDVst = GET_MDOMAIN_OUTPUT_VHEIGHT() - GET_ASPECT_RATIO_MIN_DVH();
            usAspNewDVst &= 0xFFFC;
            usAspNewDVst = GET_MDOMAIN_OUTPUT_VSTART() + (usAspNewDVst / 2);
        }
        else
        {
            usAspNewDVst = GET_ASPECT_RATIO_MIN_DVH() - GET_MDOMAIN_OUTPUT_VHEIGHT();
            usAspNewDVst &= 0xFFFC;
            usAspNewDVst = GET_MDOMAIN_OUTPUT_VSTART() - (usAspNewDVst / 2);
        }

        SET_MDOMAIN_OUTPUT_VSTART(usAspNewDVst);
        SET_MDOMAIN_OUTPUT_VHEIGHT(GET_ASPECT_RATIO_MIN_DVH());
        SET_MDOMAIN_OUTPUT_VBHEIGHT(GET_ASPECT_RATIO_MIN_DVH());
    }
}
#endif
#endif // End of #if(_FRC_SUPPORT == _ON)

