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
// ID Code      : ScalerVGATop.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_VGATOP__

#include "ScalerFunctionInclude.h"

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions Of VGA noise margin
//--------------------------------------------------
#define _VGA_NOISE_MARGIN                               (0x40)

//--------------------------------------------------
// Noise width definitions
//--------------------------------------------------
#define _NOISE_WIDTH_AFTER_HSYNC                        (0x3C)
#define _NOISE_WIDTH_AFTER_VSYNC                        (0x01)

//--------------------------------------------------
// Noise Delay before hs definitions, Unit: ns
//--------------------------------------------------
#define _NOISE_DELAY_BEFORE_HSYNC_POSITIVE              (80) // Unit: ns
#define _NOISE_DELAY_BEFORE_HSYNC_NEGTIVE               (100) // Unit: ns

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructRegVgaCapture xdata g_stRegVgaCapture           _at_     _VGATOP_CAPTURE_ADDRESS;
volatile StructRegVgaAuto xdata g_stRegVgaAuto                 _at_     _VGATOP_AUTO_ADDRESS;


WORD g_usPhaseDelayTimeShortPath;
WORD g_usPhaseDelayTimeLongPath;

WORD g_usVgaModeHstart;
WORD g_usVgaModeVstart;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************

#if(_VGA_CAPTURE_SUPPORT == _ON)
void ScalerVgaTopInputInitial(void);
void ScalerVgaTopModifyPolarity(void);
#endif

void ScalerVgaTopSetCapture(void);
bit ScalerVgaTopModifyVsLatchEdge(bit bWait);

void ScalerVgaTopAutoFuncHBoundInitial(WORD usHBoundStart, WORD usHBoundEnd);
void ScalerVgaTopAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd);
void ScalerVgaTopSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal);
bit ScalerVgaTopGetAutoResult(StructAutoActiveData *pstActiveRegion, bit bWait);
bit ScalerVgaTopHWAutoPhaseSearch(EnumAutoPhaseSearchStep enumPhaseStep, BYTE *pucPhaseResult, DWORD *pulSODMax, DWORD *pulSODMin, EnumAutoPhaseSearchSODMethod enumSODMethod, BYTE ucSODThreshold);
bit ScalerVgaTopAutoPhaseGetSOD(DWORD *pulSODValue);
bit ScalerVgaTopMeasureActiveRegion(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal);

bit ScalerVgaTopAutoFuncWaitFinish(void);
bit ScalerVgaTopWaitForEvent(EnumVgaTopWaitEventType enumEvent);

void ScalerVgaTopDoubleBufferApply(void);
void ScalerVgaTopDoubleBufferEnable(bit bEn);
WORD ScalerVgaTopGetCaptureVStartPosition(void);
void ScalerVgaTopSetCaptureVStartPosition(WORD usIVstart);
WORD ScalerVgaTopGetCaptureVHeight(void);
void ScalerVgaTopSetCaptureVHeight(WORD usIVheight);
WORD ScalerVgaTopGetCaptureVDelay(void);
void ScalerVgaTopSetCaptureVDelay(WORD usIVSDelay);
WORD ScalerVgaTopGetCaptureHStartPosition(void);
void ScalerVgaTopSetCaptureHStartPosition(WORD usIHstart);
WORD ScalerVgaTopGetCaptureHWidth(void);
void ScalerVgaTopSetCaptureHWidth(WORD usIHwidth);
void ScalerVgaTopSetCaptureHDelay(WORD usIHSDelay);
WORD ScalerVgaTopGetCaptureHDelay(void);

WORD ScalerVgaTopSearchHsEdge(void);
void ScalerVgaTopModifyHsLatchEdgeDelay(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_VGA_CAPTURE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial for VGIP Input
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopInputInitial(void)
{
    // Set Input Pixel Format, Disable Double buffer, Analog Capture, and Start generate DE
    ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Reset field detect edge
    ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~(_BIT6 | _BIT5 | _BIT3), 0x00);

    // HS Sync Edge select to Positive, Disable 1 clock Delay Mode
    ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3 | _BIT2), 0x00);

    // Initial IVS/IHS Delay for Capture and Auto
    ScalerSetByte(P30_AC_VGATOP_IVS_DELAY, 0x00);
    ScalerSetByte(P30_AD_VGATOP_IHS_DELAY, 0x00);
    ScalerSetBit(P30_AE_VGATOP_VGIP_HV_DELAY, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : Initial H Boundary for Auto Function Measure
// Input Value  : H Boundary Start/End
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopModifyPolarity(void)
{
    if(GET_SYNC_V_POLARITY() == _POSITIVE)
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT3, 0x00);
    }
    else
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT3, _BIT3);
    }

    if(GET_SYNC_H_POLARITY() == _POSITIVE)
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT2, 0x00);
    }
    else
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT2, _BIT2);
    }
}
#endif // End of #if(_VGA_CAPTURE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Set VGATOP capture start & size
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCapture(void)
{
#if(_VGA_CAPTURE_SUPPORT == _ON)
    WORD usVgaTopVstartLimit = (DWORD)_PANEL_DV_START * GET_INPUT_TIMING_VHEIGHT() / _PANEL_DV_HEIGHT + 2;

    if(usVgaTopVstartLimit < _VGIP_IV_CAPTURE_MIN_VALUE)
    {
        usVgaTopVstartLimit = _VGIP_IV_CAPTURE_MIN_VALUE;
    }
#endif

    // Store mode table H/V start
    SET_VGA_MODE_HSTART(GET_INPUT_TIMING_HSTART());
    SET_VGA_MODE_VSTART(GET_INPUT_TIMING_VSTART());

#if(_VGA_CAPTURE_SUPPORT == _ON)

    SET_INPUT_TIMING_HSTART(_VGIP_IH_CAPTURE_MIN_VALUE + 2);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        SET_INPUT_TIMING_VSTART(usVgaTopVstartLimit);
    }
    else
#endif
    {
        SET_INPUT_TIMING_VSTART(usVgaTopVstartLimit + 2);
    }

    ScalerVgaTopSetCaptureHWidth(GET_INPUT_TIMING_HWIDTH());
    ScalerVgaTopSetCaptureVHeight(GET_INPUT_TIMING_VHEIGHT());
    ScalerVgaTopSetCaptureHStartPosition(_VGIP_IH_CAPTURE_MIN_VALUE + 2);
    ScalerVgaTopSetCaptureVStartPosition(usVgaTopVstartLimit);

#endif // End of #if(_VGA_CAPTURE_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Modify VS latch edge
// Input Value  : Input Source Type
// Output Value : None
//--------------------------------------------------
bit ScalerVgaTopModifyVsLatchEdge(bit bWait)
{
    if(bWait == _WAIT)
    {
        ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);
    }

    pData[0] = g_stRegVgaCapture.b3_02_5_DELAYVSLATCH_VSLATCHHSM_VSLATCH_DELAY;

    // Wait One More Frame in case of Interlaced Mode
    if(pData[0] == 0x00)
    {
        ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);
        pData[0] = g_stRegVgaCapture.b3_02_5_DELAYVSLATCH_VSLATCHHSM_VSLATCH_DELAY;
    }

    // If the edge between H-Sync and V-Sync is too close.
    switch(pData[0])
    {
        case 0x00:
        case 0x04:
        case 0x06:
        case 0x07:
            // Field detection by hs positive edge
            g_stRegVgaCapture.b1_01_5_FIELD_HS_INV = _TRUE;

            // V-Sync latched by H-Sync positive edge
            g_stRegVgaCapture.b1_02_2_VS_SYNCEDGE = _TRUE;

            return _TRUE;

        default:
            // Field detection by hs negative edge
            g_stRegVgaCapture.b1_01_5_FIELD_HS_INV = _FALSE;

            // V-Sync latched by H-Sync negative edge
            g_stRegVgaCapture.b1_02_2_VS_SYNCEDGE = _FALSE;

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Initial H Boundary for Auto Function Measure
// Input Value  : H Boundary Start/End
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopAutoFuncHBoundInitial(WORD usHBoundStart, WORD usHBoundEnd)
{
    // Set H boundary
    g_stRegVgaAuto.b4_00_4_HB_STA_HI = HIBYTE(usHBoundStart) & 0x0F;
    g_stRegVgaAuto.uc_01_HB_STA_LO = LOBYTE(usHBoundStart);

    g_stRegVgaAuto.b4_00_0_HB_END_HI = HIBYTE(usHBoundEnd) & 0x0F;
    g_stRegVgaAuto.uc_02_HB_END_LO = LOBYTE(usHBoundEnd);
}

//--------------------------------------------------
// Description  : Initial V Boundary for Auto Function Measure
// Input Value  : V Boundary Start/End
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd)
{
    // Set V boundary
    g_stRegVgaAuto.b4_03_4_VB_STA_HI = HIBYTE(usVBoundStart) & 0x0F;
    g_stRegVgaAuto.uc_04_VB_STA_LO = LOBYTE(usVBoundStart);

    g_stRegVgaAuto.b4_03_0_VB_END_HI = HIBYTE(usVBoundEnd) & 0x0F;
    g_stRegVgaAuto.uc_05_VB_END_LO = LOBYTE(usVBoundEnd);
}

//--------------------------------------------------
// Description  : Initialization for Picture Position <easure by Auto Function Measure
// Input Value  : EnumMeasureFieldSelect --> Measure for Even or Odd Field
//                EnumMeasureBoundType --> OverScan Boundary or Normal Boundary
//                usHTotal --> H Total
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal)
{
    WORD usHLbound = 0;
    WORD usHRbound = 0;
    WORD usHSWidth = 0;
    WORD usVSWidth = 0;

    // Disable auto-function
    g_stRegVgaAuto.b1_0D_0_NOW_AF = 0;

    // Set active measured V-Sync delay 3 lines for auto function
    g_stRegVgaCapture.b2_0E_4_AUTO_IVS_DLY = 0x01;

    // Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
    g_stRegVgaAuto.b1_0A_5_FILTER_SEL = _FALSE;
    g_stRegVgaAuto.b1_0A_4_RGB_IN_ONE_EN = _FALSE;
    g_stRegVgaAuto.b2_0A_2_VB_TH = 0;
    g_stRegVgaAuto.b2_0A_0_COLOR_SEL = 0;

    if(enumFieldSelect == _EVEN_FIELD_MEASURE)
    {
        // Field Select to Even
        g_stRegVgaAuto.b1_0A_7_ODD_SEL_EN = _TRUE;
        g_stRegVgaAuto.b1_0A_6_ODD_SEL = _FALSE;
    }
    else if(enumFieldSelect == _ODD_FIELD_MEASURE)
    {
        // Field Select to Odd
        g_stRegVgaAuto.b1_0A_7_ODD_SEL_EN = _TRUE;
        g_stRegVgaAuto.b1_0A_6_ODD_SEL = _TRUE;
    }
    else
    {
        // Disable Field Select
        g_stRegVgaAuto.b1_0A_7_ODD_SEL_EN = _FALSE;
        g_stRegVgaAuto.b1_0A_6_ODD_SEL = _FALSE;
    }

    // Convert to positive if input sync is negative.
    usHSWidth = GET_INPUT_TIMING_HSYNCWIDTH();

    // Sync Pulse should be smaller than 1/2 period.
    usVSWidth = GET_INPUT_TIMING_VSYNCWIDTH();

    // L Boundary position reference clamp signal end position add 0x05 tolerance
    // Notice: clamp signal start position reference HS trailing edge
    usHLbound = ScalerSyncProcGetClampEndPosition() + 0x05;

    // Calculate left boundary.
    // Unit Conversion Formula: Left Boundary = HPeriod Pixel Clock * (H-Sync Pulse Didth / H-Sync Period) + Clamp End
    usHLbound += (((DWORD)usHTotal * usHSWidth) / GET_SYNC_H_PERIOD());

    // Input signal is positive polarity
    if((bit)GET_INPUT_TIMING_H_POLARITY() == _TRUE)
    {
        usHRbound = (((DWORD)_NOISE_DELAY_BEFORE_HSYNC_POSITIVE * GET_INPUT_PIXEL_CLK()) / 10000) + 1;
    }
    else
    {
        usHRbound = (((DWORD)_NOISE_DELAY_BEFORE_HSYNC_NEGTIVE * GET_INPUT_PIXEL_CLK()) / 10000) + 1;
    }

    usHRbound = usHTotal - usHRbound;

    // Set H boundary
    ScalerVgaTopAutoFuncHBoundInitial(usHLbound, usHRbound);

    // Set V Boundary
    if((enumBoundType == _OVERSCAN_BOUNDARY) &&
       (GET_INPUT_TIMING_VHEIGHT() >= ScalerVgaTopGetCaptureVHeight()))
    {
        ScalerVgaTopAutoFuncVBoundInitial((usVSWidth + _NOISE_WIDTH_AFTER_VSYNC + ((GET_INPUT_TIMING_VHEIGHT() - ScalerVgaTopGetCaptureVHeight()) / 2)), (GET_INPUT_TIMING_VTOTAL() - 2 - ((GET_INPUT_TIMING_VHEIGHT() - ScalerVgaTopGetCaptureVHeight()) / 2)));
    }
    else
    {
        ScalerVgaTopAutoFuncVBoundInitial((usVSWidth + _NOISE_WIDTH_AFTER_VSYNC), (GET_INPUT_TIMING_VTOTAL() - 2));
    }

    // Set noice margin according to current clamp type for VGA
    ScalerRead(P0_CF_ADC_CTL_RED, 3, pData, _AUTOINC);

    if(((pData[0] & _BIT7) == _BIT7) && ((pData[2] & _BIT7) == _BIT7) && ((pData[1] & _BIT7) == 0x00))
    {
        // Set Noise Margin
        g_stRegVgaAuto.b6_06_2_RED_NM = (0xFC >> 2);
        g_stRegVgaAuto.b6_07_2_GRN_NM = (_VGA_NOISE_MARGIN >> 2);
        g_stRegVgaAuto.b6_08_2_BLU_NM = (0xFC >> 2);
    }
    else
    {
        // Set Noise Margin
        g_stRegVgaAuto.b6_06_2_RED_NM = (_VGA_NOISE_MARGIN >> 2);
        g_stRegVgaAuto.b6_07_2_GRN_NM = (_VGA_NOISE_MARGIN >> 2);
        g_stRegVgaAuto.b6_08_2_BLU_NM = (_VGA_NOISE_MARGIN >> 2);
    }

    // Analog Measure Mode, Select Software Mode, Select Auto Balance, Start Auto Function Measure
    g_stRegVgaAuto.b1_0D_7_M_VGEN_EN = _FALSE;
    g_stRegVgaAuto.b1_0D_6_AUTOPHASE_EN = _FALSE;
    g_stRegVgaAuto.b1_0D_1_DIFF_EN = _FALSE;

    if(enumBoundType == _OVERSCAN_BOUNDARY)
    {
        if(GET_INPUT_TIMING_VHEIGHT() >= ScalerVgipGetCaptureVHeight())
        {
            // Set V Boundary
            ScalerVgaTopAutoFuncVBoundInitial((usVSWidth + _NOISE_WIDTH_AFTER_VSYNC + ((GET_INPUT_TIMING_VHEIGHT() - ScalerVgaTopGetCaptureVHeight()) / 2)), (GET_INPUT_TIMING_VTOTAL() - 2 - ((GET_INPUT_TIMING_VHEIGHT() - ScalerVgaTopGetCaptureVHeight()) / 2)));

            // Analog Measure Mode, Select Software Mode, Select Software Mode, Select Auto Balance, Start Auto Function Measure
            g_stRegVgaAuto.b1_0D_7_M_VGEN_EN = _FALSE;
            g_stRegVgaAuto.b1_0D_6_AUTOPHASE_EN = _FALSE;
            g_stRegVgaAuto.b1_0D_1_DIFF_EN = _FALSE;
        }
    }

    // Start auto-function measure
    g_stRegVgaAuto.b1_0D_0_NOW_AF = _TRUE;
}

//--------------------------------------------------
// Description  : Pop Up Auto-Function Result
// Input Value  : stActiveRegion --> measure result
//                bWait --> wait auto-function stop or not
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerVgaTopGetAutoResult(StructAutoActiveData *pstActiveRegion, bit bWait)
{
    BYTE ucVdelayCount = 0;
    BYTE ucRepeatCount = 0;

    while(ucRepeatCount < 2) // Maximum Measure Time is 2 times
    {
        if((bWait == _WAIT) || (g_stRegVgaAuto.b1_0D_6_AUTOPHASE_EN == _FALSE))
        {
            if(ScalerVgaTopAutoFuncWaitFinish() == _FALSE)
            {
                return _FALSE;
            }
        }

        // Calculate delay for auto-function VS
        switch(g_stRegVgaCapture.b2_0E_4_AUTO_IVS_DLY)
        {
            default:
            case 0x00:
                ucVdelayCount = 0;
                break;

            case _BIT0:
                ucVdelayCount = 3;
                break;

            case _BIT1:
                ucVdelayCount = 7;
                break;

            case (_BIT1 | _BIT0):
                ucVdelayCount = 15;
                break;
        }

        pstActiveRegion->usVActiveStart = (((WORD)g_stRegVgaAuto.b4_0E_4_VX_STA_HI << 8) | g_stRegVgaAuto.uc_0F_VX_STA_LO) + ucVdelayCount;
        pstActiveRegion->usVActiveEnd = (((WORD)g_stRegVgaAuto.b4_0E_0_VX_END_HI << 8) | g_stRegVgaAuto.uc_10_VX_END_LO) + ucVdelayCount;

        // Add offset for V start/end
        pstActiveRegion->usVActiveStart += _VGATOP_VSTART_OFFSET;
        pstActiveRegion->usVActiveEnd += _VGATOP_VSTART_OFFSET;

        DebugMessageAnalog("5.Active Measure H-ActiveStart", pstActiveRegion->usHActiveStart);
        DebugMessageAnalog("5.Active Measure H-VActiveEnd", pstActiveRegion->usHActiveEnd);
        DebugMessageAnalog("5.Active Measure V-ActiveStart", pstActiveRegion->usVActiveStart);
        DebugMessageAnalog("5.Active Measure V-VActiveEnd", pstActiveRegion->usVActiveEnd);

        pstActiveRegion->usHActiveStart = (((WORD)g_stRegVgaAuto.b4_11_4_HX_STA_HI << 8) | g_stRegVgaAuto.uc_12_HX_STA_LO);
        pstActiveRegion->usHActiveEnd = (((WORD)g_stRegVgaAuto.b4_11_0_HX_END_HI << 8) | g_stRegVgaAuto.uc_13_HX_END_LO);

        if(g_stRegVgaAuto.b1_0D_7_M_VGEN_EN == _TRUE)
        {
            pstActiveRegion->usHActiveStart += 1;
            pstActiveRegion->usHActiveEnd += 1;
        }

        // Check auto-function measure result
        if((pstActiveRegion->usVActiveStart == ucVdelayCount) ||
           (pstActiveRegion->usVActiveEnd == ucVdelayCount) ||
           (pstActiveRegion->usHActiveStart == 0x00) ||
           (pstActiveRegion->usHActiveEnd == 0x00))
        {
            pstActiveRegion->usHActiveStart = 0x00;
            pstActiveRegion->usHActiveEnd = 0x00;
            pstActiveRegion->usVActiveStart = 0x00;
            pstActiveRegion->usVActiveEnd = 0x00;

            // Return fail for digital measure
            if(g_stRegVgaAuto.b1_0D_7_M_VGEN_EN == _TRUE)
            {
                return _FALSE;
            }
        }

        // Check auto-function boundary setting for analog measure
        if((g_stRegVgaAuto.b1_0D_7_M_VGEN_EN == _FALSE) &&
           (ucRepeatCount == 0))
        {
            // Clear wait flag
            bWait = _NOT_WAIT;

            // Get current auto-function boundories
            PDATA_WORD(0) = ((WORD)g_stRegVgaAuto.b4_00_4_HB_STA_HI << 8) + g_stRegVgaAuto.uc_01_HB_STA_LO; // H start
            PDATA_WORD(1) = ((WORD)g_stRegVgaAuto.b4_00_0_HB_END_HI << 8) + g_stRegVgaAuto.uc_02_HB_END_LO; // H end
            PDATA_WORD(2) = ((WORD)g_stRegVgaAuto.b4_03_4_VB_STA_HI << 8) + g_stRegVgaAuto.uc_04_VB_STA_LO + ucVdelayCount; // V start

            // Check auto-boundary H start
            if(pstActiveRegion->usHActiveStart == PDATA_WORD(0))
            {
                // Set H start = H_width + H_clamp_end + 2
                PDATA_WORD(0) -= 3;

                bWait = _WAIT;
            }

            // Check auto-boundary H end
            if(pstActiveRegion->usHActiveEnd == PDATA_WORD(1))
            {
                // Enlarge H R-Bounday delta = 1/2 noise margin width
                if(GET_INPUT_TIMING_H_POLARITY() == _TRUE)
                {
                    PDATA_WORD(1) += (((DWORD)_NOISE_DELAY_BEFORE_HSYNC_POSITIVE * GET_INPUT_PIXEL_CLK()) / 20000);
                }
                else
                {
                    PDATA_WORD(1) += (((DWORD)_NOISE_DELAY_BEFORE_HSYNC_NEGTIVE * GET_INPUT_PIXEL_CLK()) / 20000);
                }

                bWait = _WAIT;
            }

            // Check auto-boundary V start
            if(pstActiveRegion->usVActiveStart == PDATA_WORD(2))
            {
                if(g_stRegVgaCapture.b2_0E_4_AUTO_IVS_DLY != 0x00)
                {
                    // Disable IVS delay when V porch region is too short
                    g_stRegVgaCapture.b2_0E_4_AUTO_IVS_DLY = 0x00;
                    bWait = _WAIT;
                }
            }

            // Restart auto-function measure
            if(bWait == _WAIT)
            {
                // Adjust auto-function H boundary
                ScalerVgaTopAutoFuncHBoundInitial(PDATA_WORD(0), PDATA_WORD(1));

                // Restart auto-function measure
                g_stRegVgaAuto.b1_0D_0_NOW_AF = _FALSE;
                g_stRegVgaAuto.b1_0D_0_NOW_AF = _TRUE;

                ++ucRepeatCount;
                continue;
            }
            else
            {
                break;
            }
        }

        break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Phase, MaxSOD, MinSOD Search
// Input Value  : enumPhaseStep --> Hardware Auto Search Phase Step
//                ucPhaseResult --> Best Phase(with Max SOD)
//                ulSODMax --> Max SOD Value
//                ulSODMin --> Min SOD Value
//                enumSODMethod --> SOD or WSOD Selection
// Output Value : True --> SOD Measurement ok, False --> SOD Measurement Fail
//--------------------------------------------------
bit ScalerVgaTopHWAutoPhaseSearch(EnumAutoPhaseSearchStep enumPhaseStep, BYTE *pucPhaseResult, DWORD *pulSODMax, DWORD *pulSODMin, EnumAutoPhaseSearchSODMethod enumSODMethod, BYTE ucSODThreshold)
{
    BYTE ucTargetPhase = 0;
    BYTE ucBestPhase = 0;
    BYTE ucPhaseStepNum = 0;
    DWORD ulSOD1st = 0;
    DWORD ulSOD2nd = 0;

    *pulSODMax = 0;

    *pulSODMin = 0xffffffff;

    // Set Difference Threshold
    g_stRegVgaAuto.uc_09_DIFF_TH = ucSODThreshold;

    // Hardware Auto Measure Trigger Select to IVS, Initial Phase --> 0.
    g_stRegVgaAuto.b1_0C_7_AUTOPHASE_SEL_TRI = _FALSE;
    g_stRegVgaAuto.b7_0C_0_INIT_PHASE = 0;

    // Field Select Disable, LPF Disable, 1 pixel over Threshold, Enable Accelaration Mode, Select R or G or B Channel
    g_stRegVgaAuto.b1_0A_7_ODD_SEL_EN = _FALSE;
    g_stRegVgaAuto.b1_0A_6_ODD_SEL = _FALSE;
    g_stRegVgaAuto.b1_0A_5_FILTER_SEL = _FALSE;
    g_stRegVgaAuto.b1_0A_4_RGB_IN_ONE_EN = _TRUE;
    g_stRegVgaAuto.b2_0A_2_VB_TH = (1 - 1);
    g_stRegVgaAuto.b2_0A_0_COLOR_SEL = 0;

    ucPhaseStepNum = (64 / (1 << enumPhaseStep));

    if(ScalerGetBit(P1_B1_PLLDIV_H, _BIT4) == _BIT4)
    {
        enumPhaseStep = enumPhaseStep + 1;
    }

    // Set Phase Step and Number
    g_stRegVgaAuto.b3_0B_0_AUTOPHASE_STEP = enumPhaseStep;
    g_stRegVgaAuto.b5_0B_3_AUTOSOD_STEP_NUM = (ucPhaseStepNum - 1);

    enumPhaseStep = (1 << enumPhaseStep);

    ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);

    // Hardware Auto Measure Setting, and stop Auto-Function Measure Function, Start Measure
    g_stRegVgaAuto.b1_0D_7_M_VGEN_EN = _FALSE;
    g_stRegVgaAuto.b1_0D_6_AUTOPHASE_EN = _TRUE;
    g_stRegVgaAuto.b1_0D_5_FORCE_FLIP = _TRUE;
    g_stRegVgaAuto.b1_0D_4_SUM_MAX = _TRUE;
    g_stRegVgaAuto.b1_0D_3_PULSE_DET_EN = _TRUE;
    g_stRegVgaAuto.b1_0D_2_SQUARE_EN = _FALSE;
    g_stRegVgaAuto.b1_0D_1_DIFF_EN = _TRUE;
    g_stRegVgaAuto.b1_0D_0_NOW_AF = _TRUE;

    ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS);

    if(enumSODMethod == _PHASE_SEARCH_SOD)
    {
        do
        {
            if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
            {
                return _FALSE;
            }

            PDATA_DWORD(0) = GET_AUTO_RESULT_DWORD();

            if(PDATA_DWORD(0) > *pulSODMax)
            {
                *pulSODMax = PDATA_DWORD(0);
                ucBestPhase = ucTargetPhase;
            }

            if(PDATA_DWORD(0) < *pulSODMin)
            {
                *pulSODMin = PDATA_DWORD(0);
            }

            ucTargetPhase += enumPhaseStep;

            ucPhaseStepNum--;
        }
        while(ucPhaseStepNum > 0);
    }
    else
    {
        ucPhaseStepNum = ucPhaseStepNum + 2;

        PDATA_DWORD(1) = 0;
        PDATA_DWORD(2) = 0;
        PDATA_DWORD(3) = 0;

        do
        {
            PDATA_DWORD(3) = PDATA_DWORD(2);

            PDATA_DWORD(2) = PDATA_DWORD(1);

            if(ucPhaseStepNum == 2)
            {
                PDATA_DWORD(1) = ulSOD1st;
            }
            else if(ucPhaseStepNum == 1)
            {
                PDATA_DWORD(1) = ulSOD2nd;
            }
            else
            {
                if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
                {
                    return _FALSE;
                }

                PDATA_DWORD(0) = GET_AUTO_RESULT_DWORD();
                PDATA_DWORD(1) = PDATA_DWORD(0);

                if(ucTargetPhase == 0x00)
                {
                    ulSOD1st = PDATA_DWORD(0);
                }

                if(ucTargetPhase == enumPhaseStep)
                {
                    ulSOD2nd = PDATA_DWORD(0);
                }
            }

            if(PDATA_DWORD(2) > (ABSDWORD(PDATA_DWORD(3), PDATA_DWORD(2)) + ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))))
            {
                PDATA_DWORD(0) = PDATA_DWORD(2) - ((ABSDWORD(PDATA_DWORD(3), PDATA_DWORD(2)) + ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))));

                if(PDATA_DWORD(0) > *pulSODMax)
                {
                    *pulSODMax = PDATA_DWORD(0);

                    ucBestPhase = ucTargetPhase - enumPhaseStep;
                }
            }

            ucTargetPhase += enumPhaseStep;

            ucPhaseStepNum--;
        }
        while(ucPhaseStepNum > 0);
    }

    // Stop Hardware Auto-Function Measure
    g_stRegVgaAuto.b1_0D_0_NOW_AF = _FALSE;
    g_stRegVgaAuto.b1_0D_6_AUTOPHASE_EN = _FALSE;

    if(ScalerGetBit(P1_B1_PLLDIV_H, _BIT4) != 0x00) // DotClock < _APLL_VCO_DEVIDER_4_2_THERSHOLD
    {
        *pucPhaseResult = ((ucBestPhase / 2) % 64);
    }
    else
    {
        *pucPhaseResult = (ucBestPhase % 64);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  :
// Input Value  : Firmware Auto Measure SOD Value
// Output Value : True --> Measure Success
//                False --> Measure Fail
//--------------------------------------------------
bit ScalerVgaTopAutoPhaseGetSOD(DWORD *pulSODValue)
{
    // Firmware Measure Setting, and stop Auto-Function Measure Function, Start Measure
    g_stRegVgaAuto.b1_0D_7_M_VGEN_EN = _FALSE;
    g_stRegVgaAuto.b1_0D_6_AUTOPHASE_EN = _FALSE;
    g_stRegVgaAuto.b1_0D_5_FORCE_FLIP = _TRUE;
    g_stRegVgaAuto.b1_0D_4_SUM_MAX = _TRUE;
    g_stRegVgaAuto.b1_0D_3_PULSE_DET_EN = _TRUE;
    g_stRegVgaAuto.b1_0D_2_SQUARE_EN = _FALSE;
    g_stRegVgaAuto.b1_0D_1_DIFF_EN = _TRUE;
    g_stRegVgaAuto.b1_0D_0_NOW_AF = _TRUE;

    if(ScalerVgaTopAutoFuncWaitFinish() == _FALSE)
    {
        // Hw Auto Status Initial
        g_stRegVgaAuto.b1_0D_0_NOW_AF = _FALSE;
        g_stRegVgaAuto.b1_0D_7_M_VGEN_EN = _FALSE;
        g_stRegVgaAuto.b1_0D_6_AUTOPHASE_EN = _FALSE;
        g_stRegVgaAuto.b1_0D_5_FORCE_FLIP = _FALSE;
        g_stRegVgaAuto.b1_0D_4_SUM_MAX = _FALSE;
        g_stRegVgaAuto.b1_0D_3_PULSE_DET_EN = _FALSE;
        g_stRegVgaAuto.b1_0D_2_SQUARE_EN = _FALSE;
        g_stRegVgaAuto.b1_0D_1_DIFF_EN = _FALSE;

        return _FALSE;
    }

    // Get Phase Result
    *pulSODValue = GET_AUTO_RESULT_DWORD();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Measure Active Start / End using auto-funcgion
// Input Value  : EnumMeasureModeType --> Analog or Digital Mode Measure
//                EnumMeasureFieldSelect --> Measure for Even or Odd Field
//                EnumMeasureBoundType --> OverScan Boundary or Normal Boundary
//                usHTotal --> H Total
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerVgaTopMeasureActiveRegion(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal)
{
    ScalerVgaTopSetAuto(enumFieldSelect, enumBoundType, usHTotal);

    return (ScalerVgaTopGetAutoResult(&g_stActiveRegion, _WAIT));
}

//--------------------------------------------------
// Description  : Waiting for Auto Function Measure Finish
// Input Value  : None
// Output Value : True --> Measure Finish
//                False --> Measure Timeout or Fail
//--------------------------------------------------
bit ScalerVgaTopAutoFuncWaitFinish(void)
{
    BYTE ucIvsCnt = (g_stRegVgaAuto.b2_0A_0_COLOR_SEL == 0x03) ? 3 : 1;

    if(g_stRegVgaAuto.b1_0A_7_ODD_SEL_EN == _TRUE)
    {
        ucIvsCnt *= 2;
    }
    ucIvsCnt += 2;

    do
    {
        if(ScalerGetBit(P0_4E_HSYNC_TYPE_DETECTION_FLAG, (_BIT7 | _BIT6 | _BIT5 | _BIT3)) != 0x00)
        {
            // Sync is changing
            return _FALSE;
        }

        if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
        {
            return _FALSE;
        }

        if(g_stRegVgaAuto.b1_0D_0_NOW_AF == _FALSE)
        {
            return _TRUE;
        }
    }
    while(--ucIvsCnt);

    if(ucIvsCnt == 0)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit ScalerVgaTopWaitForEvent(EnumVgaTopWaitEventType enumEvent)
{
#if(_VGA_CAPTURE_SUPPORT == _ON)

    // Clear VGATOP event status
    ScalerSetBit(P30_E4_VGATOP_IRQ_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
    return (ScalerTimerPollingFlagProc(60, P30_E4_VGATOP_IRQ_CTRL, enumEvent, _TRUE));

#else

    switch(enumEvent)
    {
        case _EVENT_VGA_IVS:
            return ScalerTimerWaitForEvent(_EVENT_IVS);

        case _EVENT_VGA_IEN_START:
            return ScalerTimerWaitForEvent(_EVENT_IEN_START);

        case _EVENT_VGA_IEN_STOP:
            return ScalerTimerWaitForEvent(_EVENT_IEN_STOP);

        default:
            return _FALSE;
    }
#endif
}

//--------------------------------------------------
// Description  : Apply double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopDoubleBufferApply(void)
{
#if(_VGA_CAPTURE_SUPPORT == _ON)

    if(ScalerGetBit(P30_A0_VGATOP_VGIP_CTRL, _BIT4) != 0x00)
    {
        ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~_BIT5, _BIT5);

        ScalerTimerPollingFlagProc(60, P30_A0_VGATOP_VGIP_CTRL, _BIT5, _FALSE);
    }

#else

    ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);

#endif
}

//--------------------------------------------------
// Description  : Disable double buffer
// Input Value  : bEn --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopDoubleBufferEnable(bit bEn)
{
#if(_VGA_CAPTURE_SUPPORT == _ON)

    if(bEn == _ENABLE)
    {
        ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~_BIT4, _BIT4);
    }
    else
    {
        ScalerSetBit(P30_A0_VGATOP_VGIP_CTRL, ~_BIT4, 0x00);
    }

#else

    ScalerVgipDoubleBufferEnable(bEn);

#endif
}

//--------------------------------------------------
// Description  : Get VGATOP Capture V Start
// Input Value  : None
// Output Value : V start
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureVStartPosition(void)
{
    return (((WORD)g_stRegVgaCapture.b4_08_0_IV_ACT_STA_HI << 8) | g_stRegVgaCapture.uc_09_IV_ACT_STA_LO);
}

//--------------------------------------------------
// Description  : Set VGATOP Capture V start
// Input Value  : usIVstart --> V start
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureVStartPosition(WORD usIVstart)
{
#if(_VGA_CAPTURE_SUPPORT == _ON)

    usIVstart += 3;

    // Set VGATOP V capture start
    ScalerSetBit(P30_A8_VGATOP_IPV_ACT_STA_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usIVstart) & 0x0F));
    ScalerSetByte(P30_A9_VGATOP_IPV_ACT_STA_L, LOBYTE(usIVstart));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    ScalerFmtCnvFtoPSetFifo(ScalerVgaTopGetCaptureHWidth(), (ScalerVgaTopGetCaptureVStartPosition() + 1));
#endif

#else

    // Set VGIP V capture start
    ScalerVgipSetCaptureVStartPosition(usIVstart);

#endif
}

//--------------------------------------------------
// Description  : Get VGATOP Capture V Height
// Input Value  : None
// Output Value : Capture V Height
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureVHeight(void)
{
    return (((WORD)g_stRegVgaCapture.b4_08_4_IV_ACT_LEN_HI << 8) | g_stRegVgaCapture.uc_0B_IV_ACT_LEN_LO);
}

//--------------------------------------------------
// Description  : Get VGATOP Capture V height
// Input Value  : usIVheight --> V height
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureVHeight(WORD usIVheight)
{
#if(_VGA_CAPTURE_SUPPORT == _ON)

    // Set M1 V capture height
    ScalerSetBit(P30_A8_VGATOP_IPV_ACT_STA_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((HIBYTE(usIVheight) & 0x0F) << 4));
    ScalerSetByte(P30_AB_VGATOP_IPV_ACT_LEN_L, LOBYTE(usIVheight));

#else

    ScalerVgipSetCaptureVHeight(usIVheight);

#endif
}

//--------------------------------------------------
// Description  : Get VGATOP Capture V Delay
// Input Value  : None
// Output Value : Capture V Delay
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureVDelay(void)
{
    return (((WORD)g_stRegVgaCapture.b1_0E_1_IVS_DLY_8 << 8) | g_stRegVgaCapture.uc_0C_IVS_DLY_LO);
}

//--------------------------------------------------
// Description  : Set VGATOP Capture V Delay
// Input Value  : usIVSDelay --> V Delay
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureVDelay(WORD usIVSDelay)
{
#if(_VGA_CAPTURE_SUPPORT == _ON)

    // Set M1 capture V delay
    ScalerSetBit(P30_AE_VGATOP_VGIP_HV_DELAY, ~_BIT1, ((HIBYTE(usIVSDelay) & _BIT0) << 1));
    ScalerSetByte(P30_AC_VGATOP_IVS_DELAY, LOBYTE(usIVSDelay));

#else

    ScalerVgipSetCaptureVDelay(usIVSDelay);

#endif
}

//--------------------------------------------------
// Description  : Get VGATOP Capture H-Start Position
// Input Value  : None
// Output Value : Capture H Start
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureHStartPosition(void)
{
    return (((WORD)g_stRegVgaCapture.b4_04_0_IH_ACT_STA_HI << 8) | g_stRegVgaCapture.uc_05_IH_ACT_STA_LO) + 2;
}

//--------------------------------------------------
// Description  : Set VGATOP Capture H start
// Input Value  : usIHstart --> H start
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureHStartPosition(WORD usIHstart)
{
#if(_VGA_CAPTURE_SUPPORT == _ON)

    usIHstart -= 2;

    // Set M1 H capture start
    ScalerSetBit(P30_A4_VGATOP_IPH_ACT_STA_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usIHstart) & 0x0F));
    ScalerSetByte(P30_A5_VGATOP_IPH_ACT_STA_L, LOBYTE(usIHstart));

#else

    ScalerVgipSetCaptureHStartPosition(usIHstart);

#endif
}

//--------------------------------------------------
// Description  : Get VGATOP Capture H width
// Input Value  : None
// Output Value : VGATOP H width
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureHWidth(void)
{
    return (((WORD)g_stRegVgaCapture.b4_04_4_IH_ACT_WID_HI << 8) | g_stRegVgaCapture.uc_07_IH_ACT_WID_LO);
}

//--------------------------------------------------
// Description  : Set VGATOP Capture H width
// Input Value  : usIHwidth --> H width
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureHWidth(WORD usIHwidth)
{
#if(_VGA_CAPTURE_SUPPORT == _ON)

    // Set M1 H capture width
    ScalerSetBit(P30_A4_VGATOP_IPH_ACT_STA_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((HIBYTE(usIHwidth) & 0x0F) << 4));
    ScalerSetByte(P30_A7_VGATOP_IPH_ACT_WID_L, LOBYTE(usIHwidth));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Set main F-to-P FIFO
    ScalerFmtCnvFtoPSetFifo(usIHwidth, (ScalerVgaTopGetCaptureVStartPosition() + 1));
#endif

#else

    ScalerVgipSetCaptureHWidth(usIHwidth);

#endif
}

//--------------------------------------------------
// Description  : Set VGATOP Capture V Delay
// Input Value  : usIHSDelay --> H Delay
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopSetCaptureHDelay(WORD usIHSDelay)
{
#if(_VGA_CAPTURE_SUPPORT == _ON)

    ScalerSetBit(P30_AE_VGATOP_VGIP_HV_DELAY, ~(_BIT2 | _BIT0), (((HIBYTE(usIHSDelay) & _BIT1) << 1) | (HIBYTE(usIHSDelay) & _BIT0)));
    ScalerSetByte(P30_AD_VGATOP_IHS_DELAY, LOBYTE(usIHSDelay));

#else

    ScalerVgipSetCaptureHDelay(usIHSDelay);

#endif
}

//--------------------------------------------------
// Description  : Get VGATOP Capture H Delay
// Input Value  : None
// Output Value : H Delay
//--------------------------------------------------
WORD ScalerVgaTopGetCaptureHDelay(void)
{
    return (((WORD)g_stRegVgaCapture.b1_0E_2_IHS_DLY_9 << 9) |
            ((WORD)g_stRegVgaCapture.b1_0E_0_IHS_DLY_8 << 8) |
            g_stRegVgaCapture.uc_0D_IHS_DLY_LO);
}

//--------------------------------------------------
// Description  : Find metastable phase for current APLL rate
// Input Value  : None
// Output Value : current HS delay value (0.01ns * 64)
//--------------------------------------------------
WORD ScalerVgaTopSearchHsEdge(void)
{
    BYTE ucCurrPhase = 0;
    BYTE ucTargetPhase = 0xFF;
    DWORD ulMax = 0;

    // Stop auto-function; HW auto; Measure min; Accumulation
    g_stRegVgaAuto.b1_0D_0_NOW_AF = _FALSE;
    g_stRegVgaAuto.b1_0D_4_SUM_MAX = _TRUE;
    g_stRegVgaAuto.b1_0D_6_AUTOPHASE_EN = _TRUE;

    // Set VGIP latch edge
    SET_HS_DELAY_LATCH_EDGE();

    if(g_stRegVgaCapture.b1_00_4_DOUBLE_ENABLE == _TRUE)
    {
        g_stRegVgaCapture.b1_00_5_DOUBLE_READY = _TRUE;
    }

#if(_VGA_CAPTURE_SUPPORT == _ON)
    // Enable VGATOP pattern gen to output 0;
    ScalerSetByte(P30_DF_VGATOP_PAT_GEN_RED_INI_L, 0x00);
    ScalerSetByte(P30_E0_VGATOP_PAT_GEN_GRN_INI_L, 0x00);
    ScalerSetByte(P30_E1_VGATOP_PAT_GEN_BLU_INI_L, 0x00);
    ScalerSetByte(P30_E2_VGATOP_PAT_GEN_INI_H, 0x00);
#endif

    // Set auto-balance old mode
    g_stRegVgaAuto.b1_06_0_NEW_RESULT_MODE = _FALSE;
    g_stRegVgaAuto.b6_06_2_RED_NM = 16;

    // Set phase step = 32
    g_stRegVgaAuto.b5_0B_3_AUTOSOD_STEP_NUM = (32 - 1);

    if(ScalerGetBit(P1_B1_PLLDIV_H, _BIT4) == _BIT4)
    {
        // step size = 2
        g_stRegVgaAuto.b3_0B_0_AUTOPHASE_STEP = (0x02 - 1);
    }
    else
    {
        // step size = 1
        g_stRegVgaAuto.b3_0B_0_AUTOPHASE_STEP = (0x01 - 1);
    }

    // Set auto function boundary to max
    ScalerVgaTopAutoFuncHBoundInitial((ScalerGetWord(P1_B1_PLLDIV_H) & 0x0FFF), 0x0FFF);
    ScalerVgaTopAutoFuncVBoundInitial(0x0000, 0x0FFF);

    // for each phase
    for(ucCurrPhase = 0; ucCurrPhase < 64; ++ucCurrPhase)
    {
        if((ucCurrPhase == 0) || (ucCurrPhase == 32))
        {
            // Stop auto-function
            g_stRegVgaAuto.b1_0D_0_NOW_AF = _FALSE;

            if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
            {
                break;
            }

            // Set initial phase
            if(ScalerGetBit(P1_B1_PLLDIV_H, _BIT4) == _BIT4)
            {
                g_stRegVgaAuto.b7_0C_0_INIT_PHASE = (ucCurrPhase << 1);
            }
            else
            {
                g_stRegVgaAuto.b7_0C_0_INIT_PHASE = ucCurrPhase;
            }

            // Start auto-function
            g_stRegVgaAuto.b1_0D_0_NOW_AF = _TRUE;

            if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
            {
                break;
            }
        }

        if(ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)
        {
            break;
        }

        // Pop out result
        PDATA_DWORD(0) = GET_AUTO_RESULT_DWORD();

        if(PDATA_DWORD(0) > ulMax)
        {
            ulMax = PDATA_DWORD(0);
            ucTargetPhase = ucCurrPhase;
        }
    }

    // Stop auto-function; Disable HW auto
    g_stRegVgaAuto.b1_0D_0_NOW_AF = _FALSE;
    g_stRegVgaAuto.b1_0D_6_AUTOPHASE_EN = _FALSE;

    ucTargetPhase = (ucTargetPhase + _PHASE_DELAY_HALF_PERIOD_SHIFT) % 64;

    // Calculate HS delay (unit: 1/64 ns)
    if(ulMax == 0x00)
    {
        DebugMessageAnalog("meta edge not found", 0);
        return ~0;
    }
    else
    {
        DebugMessageAnalog("meta edge", ucTargetPhase);
        return (WORD)((DWORD)10000 * ucTargetPhase / GET_INPUT_PIXEL_CLK());
    }
}

//--------------------------------------------------
// Description  : HS delay Calibration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerVgaTopModifyHsLatchEdgeDelay(void)
{
    BYTE pucBackup[8] = {0};
    BYTE ucLoop = 0;
    BYTE ucCount = 0;
    WORD usCurrentPhaseDelayTime = 0;

    if(g_usPhaseDelayTimeShortPath != 0x00)
    {
        // HS delay already calibrated
        DebugMessageAnalog("HS Short Path Delay Value", g_usPhaseDelayTimeShortPath);
        DebugMessageAnalog("HS Long Path Delay Value", g_usPhaseDelayTimeLongPath);
        return;
    }

    /////////////////////////////////////////////////////////////////////////
    // 1. Initial Display format/APLL/VGIP
    /////////////////////////////////////////////////////////////////////////

    // Backup Display format gen setting
    SAVE_HS_DELAY_SETTING(pucBackup);

    // Disable DPLL spread spectrum if enabled
    ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, _OFF);

    // Set new DVtotal
    SET_FREE_RUN_DVTOTAL((WORD)_HS_DELAY_DVTOTAL);

    // Update last line = DHtotal
    SET_FREE_RUN_LAST_LINE(_HS_DELAY_DHTOTAL);

    // Set new DHtotal
    SET_DIS_TIMING_GEN_H_TOTAL(_HS_DELAY_DHTOTAL);

    ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END, 0x08);

    // ADC LDO Power On, ADC Clock Power On, SOG_ADC0 Power On, R/G/B ADC Power On
    // ADC ldo Output Not Short to Ground
    ScalerSetBit(P0_C6_ADC_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0));

    // Disable ADC power saving mode
    ScalerSetBit(P0_C7_ADC_VOLT_SEL, ~_BIT2, 0x00);

    // Reset ADC clock delay
    ScalerSetBit(P0_BC_ADC_CK_OUT_CTRL, ~(_BIT4 | _BIT3), 0x00);

    // Adc output clock setting
    ScalerADCOutputClkSetting();

    // Switch sync-processor HS/VS source from D-domain; Bypass HS output
    ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT1, _BIT1);
    ScalerSetByte(P0_47_SYNC_SELECT, _BIT2);
    ScalerSetByte(P0_48_SYNC_INVERT, _BIT4);
    ScalerSetByte(P0_49_SYNC_CTRL, (_BIT2 | _BIT1));

#if(_VGA_CAPTURE_SUPPORT == _ON)
    // Enable I-domain pattern gen;
    g_stRegVgaCapture.b1_00_7_RAMDOM_EN = _TRUE;
#else
    // Enable ADC calibration
    ScalerSetBit(P0_D2_ADC_GAIN_CALI, ~_BIT4, _BIT4);
#endif

    // Disable double buffer; Enable ADC input;
    g_stRegVgaCapture.b1_00_4_DOUBLE_ENABLE = _FALSE;
    g_stRegVgaCapture.b1_00_0_IVRUN_EN = _TRUE;

    // Set VGATOP capture to max
    ScalerVgaTopSetCaptureHStartPosition(0x0001);
    ScalerVgaTopSetCaptureVStartPosition(0x0001);
    ScalerVgaTopSetCaptureHWidth(0x0FFF);
    ScalerVgaTopSetCaptureVHeight(0x0FFF);

    // Load default value for short path
#if(_PHASE_DELAY_TIME_VALUE_SHORT_PATH >= 0)
    g_usPhaseDelayTimeShortPath = _PHASE_DELAY_TIME_VALUE_SHORT_PATH;
#else
    g_usPhaseDelayTimeShortPath = -(_PHASE_DELAY_TIME_VALUE_SHORT_PATH);
#endif
    // Load default value for long path
#if(_PHASE_DELAY_TIME_VALUE_LONG_PATH >= 0)
    g_usPhaseDelayTimeLongPath = _PHASE_DELAY_TIME_VALUE_LONG_PATH;
#else
    g_usPhaseDelayTimeLongPath = -(_PHASE_DELAY_TIME_VALUE_LONG_PATH);
#endif

    /////////////////////////////////////////////////////////////////////////
    // 2. Detect HS/clock meta-stability
    /////////////////////////////////////////////////////////////////////////

    // Set APLL clock to target freq. by calculating IHtotal
    if(ScalerAPLLAdjust(_HS_DELAY_IHTOTAL, _HS_DELAY_REAL_DHFREQ) == _TRUE)
    {
        for(ucCount = 0; ucCount <= 1; ucCount++)
        {
            ucLoop = 0;
            if(ucCount != 0)
            {
                // Detect HS meta-stable for long path
                SET_THERMO_LONG_PATH_STATUS();
            }

            ScalerSetBit(P0_BC_ADC_CK_OUT_CTRL, ~(_BIT4 | _BIT3), (ucLoop << 3));
            while((ucLoop++) <= 3)
            {
                if((PDATA_WORD(0) = ScalerVgaTopSearchHsEdge()) != ~0)
                {
                    usCurrentPhaseDelayTime = PDATA_WORD(0);

                    DebugMessageAnalog("HS edge found", usCurrentPhaseDelayTime);
                    // Calculate current pixel clock period
                    PDATA_WORD(0) = (WORD)((DWORD)640000 / GET_INPUT_PIXEL_CLK()); // 1T

                    if(ucCount == 0)
                    {
#if(_PHASE_DELAY_TIME_VALUE_SHORT_PATH >= 0)

                        // Check whether HS delay over 1T
                        if(abs(PDATA_WORD(0) + usCurrentPhaseDelayTime - _PHASE_DELAY_TIME_VALUE_SHORT_PATH) < abs(usCurrentPhaseDelayTime - _PHASE_DELAY_TIME_VALUE_SHORT_PATH))
                        {
                            usCurrentPhaseDelayTime += PDATA_WORD(0);
                        }

#else

                        // Calculate negative HS delay
                        usCurrentPhaseDelayTime = PDATA_WORD(0) - usCurrentPhaseDelayTime;

                        // Check whether HS delay over 1T
                        if(abs(PDATA_WORD(0) + usCurrentPhaseDelayTime - (-(_PHASE_DELAY_TIME_VALUE_SHORT_PATH))) < abs(usCurrentPhaseDelayTime - (-(_PHASE_DELAY_TIME_VALUE_SHORT_PATH))))
                        {
                            usCurrentPhaseDelayTime += PDATA_WORD(0);
                        }

#endif
                        g_usPhaseDelayTimeShortPath = usCurrentPhaseDelayTime;
                    }
                    else
                    {
#if(_PHASE_DELAY_TIME_VALUE_LONG_PATH >= 0)

                        // Check whether HS delay over 1T
                        if(abs(PDATA_WORD(0) + usCurrentPhaseDelayTime - _PHASE_DELAY_TIME_VALUE_LONG_PATH) < abs(usCurrentPhaseDelayTime - _PHASE_DELAY_TIME_VALUE_LONG_PATH))
                        {
                            usCurrentPhaseDelayTime += PDATA_WORD(0);
                        }

#else

                        // Calculate negative HS delay
                        usCurrentPhaseDelayTime = PDATA_WORD(0) - usCurrentPhaseDelayTime;

                        // Check whether HS delay over 1T
                        if(abs(PDATA_WORD(0) + usCurrentPhaseDelayTime - (-(_PHASE_DELAY_TIME_VALUE_LONG_PATH))) < abs(usCurrentPhaseDelayTime - (-(_PHASE_DELAY_TIME_VALUE_LONG_PATH))))
                        {
                            usCurrentPhaseDelayTime += PDATA_WORD(0);
                        }

#endif
                        g_usPhaseDelayTimeLongPath = usCurrentPhaseDelayTime;
                    }

                    break;
                }

                // Adjust ADC clock delay
                ScalerSetBit(P0_BC_ADC_CK_OUT_CTRL, ~(_BIT4 | _BIT3), (ucLoop << 3));
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////
    // 3. Restore default setting
    /////////////////////////////////////////////////////////////////////////

    // Disable VGIP
    g_stRegVgaCapture.b1_00_0_IVRUN_EN = _FALSE;

#if(_VGA_CAPTURE_SUPPORT == _ON)
    // Disable I-domain pattern gen;
    g_stRegVgaCapture.b1_00_7_RAMDOM_EN = _FALSE;
#else
    // Disable ADC calibration
    ScalerSetBit(P0_D2_ADC_GAIN_CALI, ~_BIT4, 0x00);
#endif

    // Reset thermo path
    CLR_THERMO_LONG_PATH_STATUS();

    // Set sync processsor HS/VS source from ADC
    ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT2, 0x00);
    ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT1, 0x00);

    // Reset ADC power saving mode
    ScalerSetBit(P0_C7_ADC_VOLT_SEL, ~_BIT2, _BIT2);

    // Power down ADC VCM/ADC clock/SOG Power/RGB Channel
    ScalerSetBit(P0_C6_ADC_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Reset ADC clock delay
    ScalerSetBit(P0_BC_ADC_CK_OUT_CTRL, ~(_BIT4 | _BIT3), 0x00);

    // Power down APLL
    ScalerSetBit(P1_AF_PLL_WD, ~_BIT0, _BIT0);

    // Load DPLL setting
    LOAD_HS_DELAY_SETTING(pucBackup);

#if(_PHASE_DELAY_TIME_VALUE_SHORT_PATH >= 0)
    DebugMessageAnalog("Positive Short Path HS Delay Calibrated", g_usPhaseDelayTimeShortPath);
#else
    DebugMessageAnalog("Negative Short Path HS Delay Calibrated", g_usPhaseDelayTimeShortPath);
#endif

#if(_PHASE_DELAY_TIME_VALUE_LONG_PATH >= 0)
    DebugMessageAnalog("Positive Long Path HS Delay Calibrated", g_usPhaseDelayTimeLongPath);
#else
    DebugMessageAnalog("Negative Long Path HS Delay Calibrated", g_usPhaseDelayTimeLongPath);
#endif
}

#endif // End of #if(_VGA_SUPPORT == _ON)
