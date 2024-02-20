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
// ID Code      : ScalerMeasure.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MEASURE__

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
StructAutoActiveData g_stActiveRegion;
StructMeasureSyncData g_stMeasureSyncHV;
StructTimingInfo g_stInputTimingData;

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
StructAutoActiveData g_stSingleActiveRegion;
StructMeasureSyncData g_stSingleMeasureSyncHV;
StructTimingInfo g_stSingleInputTimingData;
#endif

DWORD g_ulInputActiveRegionBackUp;
bit g_bInputTimingDoubleCheck = _FALSE;

#if((_MEASURE_ADJUSTED_IHF_SUPPORT == _ON) || (_MEASURE_ADJUSTED_IVF_SUPPORT == _ON))
DWORD g_ulActiveRegionCount;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************

#if(_VGA_SUPPORT == _ON)
bit ScalerMeasureVgaInputInfo(void);
bit ScalerMeasureGetStableMeasureResult(StructMeasureSyncData *pstMeasureSyncHV);
void ScalerMeasureVgaVsBypass(bit bEnable);
bit ScalerMeasureVgaInterlaceCheck(EnumSourceSearchPort enumSourceSearchPort);
#endif

void ScalerMeasureInitialSetting(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);

bit ScalerMeasureTimingChange(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
bit ScalerMeasureWatchdogStatus(void);
bit ScalerMeasureInputActiveRegionChange(void);
void ScalerMeasureUpdateOnlineMeasureResult(void);

void ScalerMeasureSetInputRegionCount(EnumActiveRegionType enumRegion);
DWORD ScalerMeasureGetInputRegionCountResult(bit bWait);
void ScalerMeasureSetDisplayRegionCount(EnumActiveRegionType enumRegion);
DWORD ScalerMeasureGetDisplayRegionCountResult(bit bWait);

#if((_MEASURE_ADJUSTED_IHF_SUPPORT == _ON) || (_MEASURE_ADJUSTED_IVF_SUPPORT == _ON))
DWORD ScalerMeasureGetdActiveRegionPixels(WORD usHWidth, WORD usVHeight, WORD usHTotal);
DWORD ScalerMeasureGetAdjustedActiveRegionCount(WORD usNewHWidth, WORD usNewVHeight);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
bit ScalerMeasureAutoFuncWaitFinish(void);
#endif

void ScalerMeasureUpdateInputTimingData(StructMeasureSyncData *pstMeasureSyncHV, StructAutoActiveData *pstActiveRegion);

#if((_MEASURE_ADJUSTED_IHF_SUPPORT == _ON) || (_MEASURE_ADJUSTED_IVF_SUPPORT == _ON))
void ScalerMeasureUpdateActiveRegion(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Measure Input Timing
// Input Value  : ucSourceType --> Input source type
// Output Value : _TURE => All Required Timing Info is done
//--------------------------------------------------
bit ScalerMeasureVgaInputInfo(void)
{
    DWORD pulActiveRegionCount[2];
    EnumSourceSearchPort enumSourceSearchPort = _A0_INPUT_PORT;

    pulActiveRegionCount[0] = 0;
    pulActiveRegionCount[1] = 0;

    //===========================================================================================
    // 0. Initialization
    //===========================================================================================

    // Initial the inteface to be measured
    ScalerMeasureInterfaceInitial(_SOURCE_VGA, &enumSourceSearchPort);

    // Initial Measure
    ScalerMeasureInitialSetting(_SOURCE_VGA, _A0_INPUT_PORT);

    // Initial Interlace Check Block
    ScalerMeasureInterlaceInitial(_SOURCE_VGA, _A0_INPUT_PORT);

    // Enable IVS bypass
    ScalerMeasureVgaVsBypass(_ENABLE);

    // Initial active region count block
    ScalerMeasureSetInputRegionCount(_WHOLE_FRAME_TYPE);

    //===========================================================================================
    // 1. Start measure block & region count(raw VS); pop-out result
    //===========================================================================================

    // Wait for 3raw IVS for VGA; Pop out measure result
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerMeasureGetOfflineMeasureResult(&g_stMeasureSyncHV, _A0_INPUT_PORT) == _FALSE) ||
       (ScalerMeasureGetStableMeasureResult(&g_stMeasureSyncHV) == _FALSE))
    {
        DebugMessageMeasure("VGA off-line measure fail", 0x00);
        return _FALSE;
    }

    ScalerTimerDelayXms(2);

    // Pop out active region count result (raw)
    if((pulActiveRegionCount[0] = ScalerMeasureGetInputRegionCountResult(_NOT_WAIT)) == 0x00)
    {
        return _FALSE;
    }

    // Disable IVS bypass
    ScalerMeasureVgaVsBypass(_DISABLE);

    // Restart active region count block;
    ScalerMeasureSetInputRegionCount(_WHOLE_FRAME_TYPE);

    //===========================================================================================
    // 2. Check VGIP HS/VS polarity
    //===========================================================================================

    // Update input timing polarity (MUST BE HERE)
    ScalerMeasureUpdateInputTimingPolarity(_SOURCE_VGA, _A0_INPUT_PORT, &g_stMeasureSyncHV);

    // Modify VGIP sync polarity
    ScalerVgipModifyPolarity(_SOURCE_VGA);

    // Update input timing data from variable "g_stMeasureSyncHV"
    ScalerMeasureUpdateInputTimingData(&g_stMeasureSyncHV, &g_stActiveRegion);

    //===========================================================================================
    // 3. Start auto-function & check VGIP VS latch edge
    //===========================================================================================

    // Start auto-function measure
    ScalerVgaTopSetAuto(_NORMAL_MEASURE, _FULL_BOUNDARY, ScalerAPLLGetIHTotal());

    // Check IVS latch edge after 1 IVS; Add additional 1 frame if latch edge changed
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       ((ScalerVgaTopModifyVsLatchEdge(_NOT_WAIT) == _TRUE) &&
        (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE)))
    {
        return _FALSE;
    }

    // Wait for 1 latched IVS; Pop out auto-function result
    if((ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE) ||
       (ScalerVgaTopGetAutoResult(&g_stActiveRegion, _NOT_WAIT) == _FALSE) ||
       (ScalerVgaTopWaitForEvent(_EVENT_VGA_IVS) == _FALSE))
    {
        DebugMessageMeasure("VGA auto-function fail", 0x00);
        return _FALSE;
    }

    //===========================================================================================
    // 4. Detect interlace format
    //===========================================================================================

    // Pop out active region count result (latched) for VGA
    pulActiveRegionCount[1] = ScalerMeasureGetInputRegionCountResult(_NOT_WAIT);

    // Check active region count result; Return _FALSE if the difference is too large
    if(ABSDWORD(pulActiveRegionCount[0], pulActiveRegionCount[1]) > (pulActiveRegionCount[1] >> 6))
    {
        DebugMessageMeasure("VGA active count difference fail", 0x00);
        return _FALSE;
    }

    // Get HS period in measure clock
    PDATA_WORD(1) = (((WORD)ScalerGetBit(P30_05_MEAS_HS_PERIOD_A_M, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) |
                     ((WORD)ScalerGetByte(P30_06_MEAS_HS_PERIOD_A_L)));

    // Calculate difference of V period
    PDATA_WORD(0) = (WORD)(ABSDWORD(pulActiveRegionCount[0], pulActiveRegionCount[1]) % PDATA_WORD(1));

    // Check half line length; flag interlace between [0.25:0.75] * H period
    if(abs(PDATA_WORD(0) - (PDATA_WORD(1) >> 1)) < (PDATA_WORD(1) >> 2))
    {
        DebugMessageMeasure("Interlace: detect by half line", PDATA_WORD(0));
        g_stInputTimingData.b1Interlace = _TRUE;
    }
    // Check full line length; flag interlace for 0.875 line difference
    else if(PDATA_WORD(0) > (PDATA_WORD(1) - (PDATA_WORD(1) >> 3)))
    {
        DebugMessageMeasure("Interlace: detect by full line", PDATA_WORD(1));
        g_stInputTimingData.b1Interlace = _TRUE;
    }

    // Check active measure overflow status
    if(ScalerGetBit(P30_41_I_ACT_MEAS_ERROR_FLG, _BIT6) == _BIT6)
    {
        DebugMessageMeasure("Interlace: detect by flag", PDATA_WORD(0));
        g_stInputTimingData.b1Interlace = ScalerMeasureInterlaceCheck(_SOURCE_VGA, _A0_INPUT_PORT);
    }

    //===========================================================================================
    // 5. Double-check current timing
    //===========================================================================================

    // Double-check for timing change
    if(ScalerMeasureTimingChange(_SOURCE_VGA, _A0_INPUT_PORT) == _TRUE)
    {
        DebugMessageMeasure("VGA off-line double check fail", 0x00);
        return _FALSE;
    }

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvGetHalfDataPathEvenOddModeStatus() == _FALSE)
    {
        // Final format conversion setting
        ScalerFmtCnvFinalSetting();
    }
#endif

    // Update input timing data
    ScalerMeasureUpdateInputTimingData(&g_stMeasureSyncHV, &g_stActiveRegion);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check timing change
// Input Value  : None
// Output Value : _TRUE if HV timing Changed
//--------------------------------------------------
bit ScalerMeasureGetStableMeasureResult(StructMeasureSyncData *pstMeasureSyncHV)
{
    if(ScalerGetBit(P0_4E_HSYNC_TYPE_DETECTION_FLAG, (_BIT7 | _BIT6 | _BIT5 | _BIT3)) != 0x00)
    {
        return _FALSE;
    }

    // Pop up stable measure result
    ScalerSetBit(P0_4F_STABLE_MEASURE, ~_BIT1, _BIT1);

    // Polarity
    pstMeasureSyncHV->b1HSP = (bit)ScalerGetBit(P0_4F_STABLE_MEASURE, _BIT6);

    // HSync Period
    pstMeasureSyncHV->usHSPeriod = ((((WORD)ScalerGetByte(P0_50_STABLE_PERIOD_H) & 0x07) << 8) | (ScalerGetByte(P0_51_STABLE_PERIOD_L))) + 1;

    // HSync Pulse Width
    pstMeasureSyncHV->usHSWidth = ((((WORD)ScalerGetByte(P0_4A_STABLE_HIGH_PERIOD_H) & 0x07) << 8) | (ScalerGetByte(P0_4B_STABLE_HIGH_PERIOD_L))) + 1;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set VGA VS bypass VGATOP
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerMeasureVgaVsBypass(bit bEnable)
{
#if(_VGA_CAPTURE_SUPPORT == _ON)
    // Switch VGATOP VS bypass
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT6, _BIT6);
    }
    else
    {
        ScalerSetBit(P30_A1_VGATOP_VGIP_SIGINV, ~_BIT6, 0x00);
    }
#endif

    // Switch VGIP VS bypass
    ScalerVgipVsBypassEnable(bEnable);
}

//--------------------------------------------------
// Description  : Check Interlace
// Input Value  : enumSourceSearchPort --> input port type
// Output Value : TRUE => Interlaced Detected
//--------------------------------------------------
bit ScalerMeasureVgaInterlaceCheck(EnumSourceSearchPort enumSourceSearchPort)
{
    enumSourceSearchPort = enumSourceSearchPort;

    // Clear VGIP Interlace Toggle Flag
    ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
    ScalerTimerDelayXms(2);

    if((ScalerGetBit(P0_1A_M1_IPV_ACT_LEN_H, _BIT5) == _BIT5) ||
       (ScalerGetBit(P0_4A_STABLE_HIGH_PERIOD_H, (_BIT6 | _BIT4)) != 0x00))
    {
        // Clear VGIP Interlace Toggle Flag
        ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

        // Clear Interlace toggle flag
        ScalerSetBit(P0_4A_STABLE_HIGH_PERIOD_H, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

        return _TRUE;
    }

    // Clear VGIP Interlace Toggle Flag
    ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

    // Clear Interlace toggle flag
    ScalerSetBit(P0_4A_STABLE_HIGH_PERIOD_H, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

    return _FALSE;
}
#endif // End of #if(_VGA_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check timing change
// Input Value  : enumSourceType: source type
//              : enumSourceSearchPort: port type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureInitialSetting(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
#if(_FREESYNC_SUPPORT == _ON)
    // Disable Shift One Line Before VGIP ivrun_en Disable
    // Avoid Lost IVS Event
    ScalerMemorySetShiftOneLine(_DISABLE);
#endif

    // Initial VGIP for input signal pass through
    ScalerVgipInputInitial(enumSourceType, enumSourceSearchPort);

    // Reset interlace flag
    g_stInputTimingData.b1Interlace = _FALSE;
    g_stInputTimingData.b1DpInterlaceVBID = _FALSE;
    g_stInputTimingData.b1VideoField = _FALSE;

    // Set off-line measure target
    ScalerMeasureSetOfflineMeasure(enumSourceType, enumSourceSearchPort);

#if(_IDOMAIN_ONLINE_MEASURE_SUPPORT == _ON)
    // Disable on-line measure
    ScalerSetBit(P16_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);
#endif
}

//--------------------------------------------------
// Description  : Check timing change
// Input Value  : None
// Output Value : _TRUE if HV timing Changed
//--------------------------------------------------
bit ScalerMeasureTimingChange(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
    bit bTimingChangeStatus = _FALSE;
    StructMeasureSyncData stMeasureSyncHV;
    memset(&stMeasureSyncHV, 0, sizeof(StructMeasureSyncData));

    enumSourceType = enumSourceType;
    enumSourceSearchPort = enumSourceSearchPort;

#if(_FREESYNC_SUPPORT == _ON)
    if((enumSourceType == _SOURCE_DP) && (GET_FREESYNC_ENABLED() == _TRUE))
    {
        // Check measure result status
        if(ScalerGetBit(P30_03_MEAS_ERROR_FLG0, (_BIT7 | _BIT4)) != 0x00)
        {
            return _FALSE;
        }
    }
    else
#endif
    {
        // Measure timeout or overflow
        if(ScalerGetBit(P30_03_MEAS_ERROR_FLG0, (_BIT7 | _BIT5 | _BIT4)) != 0x00)
        {
            return _TRUE;
        }
    }

    // Pop up if off-line measure complete
    if(ScalerGetBit(P30_02_MEAS_CTL1, _BIT7) == 0x00)
    {
        if(ScalerMeasureGetOfflineMeasureResult(&stMeasureSyncHV, enumSourceSearchPort) == _FALSE)
        {
            return _TRUE;
        }

#if(_VGA_SUPPORT == _ON)
        if(enumSourceType == _SOURCE_VGA)
        {
            if(ScalerMeasureGetStableMeasureResult(&stMeasureSyncHV) == _FALSE)
            {
                return _TRUE;
            }

            // Check off-line measure result
            bTimingChangeStatus = ((stMeasureSyncHV.b1HSP != GET_SYNC_H_POLARITY()) ||
                                   (abs(stMeasureSyncHV.usHSPeriod - GET_SYNC_H_PERIOD()) > 2));

            if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
            {
                bTimingChangeStatus |= (abs(stMeasureSyncHV.usVSPeriod - GET_SYNC_V_PERIOD()) > 3);
            }
            else
            {
                bTimingChangeStatus |= (abs(stMeasureSyncHV.usVSPeriod - GET_SYNC_V_PERIOD()) > 2);
            }
        }
        else
#endif
        {
#if(_FREESYNC_SUPPORT == _ON)
            if(GET_FREESYNC_ENABLED() == _TRUE)
            {
                // Check off-line measure result
                bTimingChangeStatus = ((stMeasureSyncHV.b1HSP != GET_SYNC_H_POLARITY()) ||
                                       (stMeasureSyncHV.b1VSP != GET_SYNC_V_POLARITY()) ||
                                       (abs(stMeasureSyncHV.usHWidth - GET_SYNC_H_WIDTH()) > 2) ||
                                       (abs(stMeasureSyncHV.usVHeight - GET_SYNC_V_HEIGHT()) > 2));

#if(_DP_FREESYNC_SUPPORT == _ON)
                // DP Freesync case
                if(GET_DP_FREESYNC_ENABLED() == _TRUE)
                {
                    g_stInputTimingData.usVTotal = ScalerFreeSyncDpGetVSPeriod(enumSourceSearchPort);
                    g_stInputTimingData.usVFreq = ScalerFreeSyncDpGetVFreq(enumSourceSearchPort);
                }
                else
#endif
                {
                    if(abs(stMeasureSyncHV.usVSPeriod - g_stInputTimingData.usVTotal) > 2)
                    {
                        g_stInputTimingData.usVTotal = stMeasureSyncHV.usVSPeriod;
                        g_stInputTimingData.usVFreq = (_MEASURE_CLK * 1000 * 10 * 2 / stMeasureSyncHV.usHSPeriod / stMeasureSyncHV.usVSPeriod + 1) / 2;
                    }
                }
            }
            else
#endif
            {
                // Check off-line measure result
                bTimingChangeStatus = ((stMeasureSyncHV.b1HSP != GET_SYNC_H_POLARITY()) ||
                                       (stMeasureSyncHV.b1VSP != GET_SYNC_V_POLARITY()) ||
                                       (abs(stMeasureSyncHV.usHSPeriod - GET_SYNC_H_PERIOD()) > 2) ||
                                       (abs(stMeasureSyncHV.usHTotal - GET_SYNC_H_TOTAL()) > 2) ||
                                       (abs(stMeasureSyncHV.usHWidth - GET_SYNC_H_WIDTH()) > 2) ||
                                       (abs(stMeasureSyncHV.usVHeight - GET_SYNC_V_HEIGHT()) > 2));

                if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
                {
                    bTimingChangeStatus |= (abs(stMeasureSyncHV.usVSPeriod - GET_SYNC_V_PERIOD()) > 3);
                }
                else
                {
                    bTimingChangeStatus |= (abs(stMeasureSyncHV.usVSPeriod - GET_SYNC_V_PERIOD()) > 2);
                }
            }
        }

#if(_DUAL_DVI_SUPPORT == _ON)
        if((enumSourceType == _SOURCE_DVI) && (bTimingChangeStatus == _FALSE))
        {
            // Perform dual DVI on-line check
            bTimingChangeStatus |= (ScalerMeasureDualDviOnlineCheck() == _FALSE);
        }
#endif
    }

    // Check WD status
    bTimingChangeStatus |= ScalerMeasureWatchdogStatus();

    return bTimingChangeStatus;
}

//--------------------------------------------------
// Description  : Check if WDs are triggered
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureWatchdogStatus(void)
{
#if(_IDOMAIN_ONLINE_MEASURE_SUPPORT == _ON)

    // Check over-range watchdog
    if(ScalerGetBit(P16_17_MEAS_HS_VS_DELTA_WD, (_BIT2 | _BIT1 | _BIT0)) != 0x00)
    {
        if(((ScalerGetBit(P16_16_MEAS_HS_VS_DELTA_IRQ, (_BIT6 | _BIT5 | _BIT4)) >> 4) &
            ScalerGetBit(P16_17_MEAS_HS_VS_DELTA_WD, (_BIT2 | _BIT1 | _BIT0))) != 0x00)
        {
            return _TRUE;
        }
    }

    // Check on-line measure timeout watchdog
    if(ScalerGetBit(P16_1C_M1_MEASURE_DUMMY0, _BIT7) == _BIT7)
    {
        if(ScalerGetBit(P16_03_MEAS_ERROR_FLG0, _BIT7) == _BIT7)
        {
            return _TRUE;
        }
    }

    // Check on-line measure overflow watchdog
    if(ScalerGetBit(P16_18_MEAS_HS_VS_ERROR_WD, (_BIT5 | _BIT4 | _BIT1 | _BIT0)) != 0x00)
    {
        if((ScalerGetBit(P16_18_MEAS_HS_VS_ERROR_WD, (_BIT5 | _BIT4 | _BIT1 | _BIT0)) &
            ScalerGetBit(P16_03_MEAS_ERROR_FLG0, (_BIT5 | _BIT4 | _BIT1 | _BIT0))) != 0x00)
        {
            return _TRUE;
        }
    }

#else

    // Check over-range watchdog
    if(ScalerGetBit(P30_17_MEAS_HS_VS_DELTA_WD, (_BIT2 | _BIT1 | _BIT0)) != 0x00)
    {
        if(((ScalerGetBit(P30_16_MEAS_HS_VS_DELTA_IRQ, (_BIT6 | _BIT5 | _BIT4)) >> 4) &
            ScalerGetBit(P30_17_MEAS_HS_VS_DELTA_WD, (_BIT2 | _BIT1 | _BIT0))) != 0x00)
        {
            return _TRUE;
        }
    }

    // Check on-line measure timeout watchdog
    if(ScalerGetBit(P30_1C_MEASURE_DUMMY0, _BIT7) == _BIT7)
    {
        if(ScalerGetBit(P30_03_MEAS_ERROR_FLG0, _BIT7) == _BIT7)
        {
            return _TRUE;
        }
    }

    // Check on-line measure overflow watchdog
    if(ScalerGetBit(P30_18_MEAS_HS_VS_ERROR_WD, (_BIT5 | _BIT4 | _BIT1 | _BIT0)) != 0x00)
    {
        if((ScalerGetBit(P30_18_MEAS_HS_VS_ERROR_WD, (_BIT5 | _BIT4 | _BIT1 | _BIT0)) &
            ScalerGetBit(P30_03_MEAS_ERROR_FLG0, (_BIT5 | _BIT4 | _BIT1 | _BIT0))) != 0x00)
        {
            return _TRUE;
        }
    }

#endif // End of #if(_ONLINE_MEASURE_SUPPORT == _ON)

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if active region changed
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureInputActiveRegionChange(void)
{
    // Pop out region count result
    PDATA_DWORD(0) = ScalerMeasureGetInputRegionCountResult(_NOT_WAIT);

    // Disable Input Region Measure
    ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~_BIT0, 0x00);

    // Compare with stored input active region count
    return (ABSDWORD(PDATA_DWORD(0), g_ulInputActiveRegionBackUp) > (g_ulInputActiveRegionBackUp >> 8));
}

//--------------------------------------------------
// Description  : Set on-line measure block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateOnlineMeasureResult(void)
{
#if(_IDOMAIN_ONLINE_MEASURE_SUPPORT == _ON)

    // Disable on-line measure
    ScalerSetBit(P16_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

    // Disable over-range enable bit
    ScalerSetBit(P16_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Clear over-range bit
    ScalerSetBit(P16_16_MEAS_HS_VS_DELTA_IRQ, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
        ScalerSetBit(P16_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), (_BIT7 | _BIT6));

        // Set over-range condition: HS = 16, VS = N/A, HSW = 16
        ScalerSetByte(P16_15_MEAS_HS_VS_DELTA_CTL, (_BIT7 | _BIT5 | _BIT2 | _BIT0));
    }
    else
#endif
    {
        // Calculate measure timeout period
        PDATA_WORD(0) = _MEASURE_CLK / 512 * 10000 / 2048;
        PDATA_WORD(1) = (PDATA_WORD(0) + (PDATA_WORD(0) >> 2)); // 1.5x margin

        if(GET_INPUT_TIMING_VFREQ() > PDATA_WORD(1))
        {
            // Measure Time Clock = 2048 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            ScalerSetBit(P16_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), 0x00);
        }
        else if(GET_INPUT_TIMING_VFREQ() > (PDATA_WORD(1) >> 1))
        {
            // Measure Time Clock = 4096 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            ScalerSetBit(P16_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), _BIT6);
        }
        else if(GET_INPUT_TIMING_VFREQ() > (PDATA_WORD(1) >> 2))
        {
            // Measure Time Clock = 8192 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            ScalerSetBit(P16_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), _BIT7);
        }
        else
        {
            // Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            ScalerSetBit(P16_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), (_BIT7 | _BIT6));
        }

        // Set over-range condition: HS = 16, VS = 4, HSW = 16
        ScalerSetByte(P16_15_MEAS_HS_VS_DELTA_CTL, (_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0));
    }

    // Delay for measure reset
    ScalerTimerDelayXms(_MEASURE_RESET_TIME);

    // Enable on-line measure
    ScalerSetBit(P16_02_MEAS_CTL1, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

#else // else of #if(_IDOMAIN_ONLINE_MEASURE_SUPPORT == _ON)

    // Disable off-line measure
    ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

    // Disable over-range enable bit
    ScalerSetBit(P30_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Clear over-range bit
    ScalerSetBit(P30_16_MEAS_HS_VS_DELTA_IRQ, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
        ScalerSetBit(P30_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), (_BIT7 | _BIT6));

        // Set over-range condition: HS = 16, VS = N/A, HSW = 16
        ScalerSetByte(P30_15_MEAS_HS_VS_DELTA_CTL, (_BIT7 | _BIT5 | _BIT2 | _BIT0));
    }
    else
#endif
    {
        // Calculate measure timeout period
        PDATA_WORD(0) = _MEASURE_CLK / 512 * 10000 / 2048;
        PDATA_WORD(1) = (PDATA_WORD(0) + (PDATA_WORD(0) >> 2)); // 1.5x margin

        if(GET_INPUT_TIMING_VFREQ() > PDATA_WORD(1))
        {
            // Measure Time Clock = 2048 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            ScalerSetBit(P30_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), 0x00);
        }
        else if(GET_INPUT_TIMING_VFREQ() > (PDATA_WORD(1) >> 1))
        {
            // Measure Time Clock = 4096 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            ScalerSetBit(P30_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), _BIT6);
        }
        else if(GET_INPUT_TIMING_VFREQ() > (PDATA_WORD(1) >> 2))
        {
            // Measure Time Clock = 8192 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            ScalerSetBit(P30_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), _BIT7);
        }
        else
        {
            // Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
            ScalerSetBit(P30_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3), (_BIT7 | _BIT6));
        }

        // Set over-range condition: HS = 16, VS = 4, HSW = 16
        ScalerSetByte(P30_15_MEAS_HS_VS_DELTA_CTL, (_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT0));
    }

    // Delay for measure reset
    ScalerTimerDelayXms(_MEASURE_RESET_TIME);

    // Enable off-line measure
    ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

#endif // End of #if(_ONLINE_MEASURE_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Set for Region Count Measure
// Input Value  : bTarget --> Measure type: digital or analog
//                ucRegion --> measure region type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetInputRegionCount(EnumActiveRegionType enumRegion)
{
    // Select source form M1; Set measure option; Disable Input Region Measure;
    ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0), (enumRegion & (_BIT4 | _BIT3)));

    // Enable Input Active Region Measure
    ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Pop Up Region Count result
// Input Value  : bWait --> wait for additional frames or not
// Output Value : measure region count
//--------------------------------------------------
DWORD ScalerMeasureGetInputRegionCountResult(bit bWait)
{
    if(bWait == _WAIT)
    {
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);
    }

    // Pop up Measure Results
    ScalerSetBit(P30_40_I_ACT_MEAS_CTRL, ~_BIT1, _BIT1);

    // Get Active Measure Clk Count
    PDATA_DWORD(0) = ScalerGetDWord(P30_41_I_ACT_MEAS_ERROR_FLG);
    pData[0] = 0x00;

    return PDATA_DWORD(0);
}

//--------------------------------------------------
// Description  : Set for Region Count Measure
// Input Value  : bTarget --> Measure type: digital or analog
//                ucRegion --> measure region type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetDisplayRegionCount(EnumActiveRegionType enumRegion)
{
    // Select source form M1; Set measure option; Disable Input Region Measure;
    ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0), (enumRegion & (_BIT4 | _BIT3)));

    // Disable Display  Active Region Measure
    ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Pop Up Region Count result
// Input Value  : bWait --> wait for additional frames or not
// Output Value : measure region count
//--------------------------------------------------
DWORD ScalerMeasureGetDisplayRegionCountResult(bit bWait)
{
    if(bWait == _WAIT)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }

    // Pop up Measure Results
    ScalerSetBit(P30_45_D_ACT_MEAS_CTRL, ~_BIT1, _BIT1);

    // Get Active Measure Clk Count
    PDATA_DWORD(0) = ScalerGetDWord(P30_46_D_ACT_MEAS_ERROR_FLG);
    pData[0] = 0x00;

    return PDATA_DWORD(0);
}

#if((_MEASURE_ADJUSTED_IHF_SUPPORT == _ON) || (_MEASURE_ADJUSTED_IVF_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Calculate active region area in pixles
// input region cnt calculation:
// single   = IHtotal * (IVheight - 1) + IHwidth
// even/odd = (IHtotal * (IVheight / 2 - 1) + IHwidth) * 2
//          = IHtotal * (IVheight - 2) + IHwidth * 2
// Input Value  : usHWidth       --> target H width
//                usVHeight      --> target V height
//                usHTotal      --> target H total
// Output Value : active region area in pixel
//--------------------------------------------------
DWORD ScalerMeasureGetdActiveRegionPixels(WORD usHWidth, WORD usVHeight, WORD usHTotal)
{
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        return (DWORD)(usVHeight - 2) * usHTotal + usHWidth * 2;
    }
#endif

    return (DWORD)(usVHeight - 1) * usHTotal + usHWidth;
}

//--------------------------------------------------
// Description  : Calculate active region measure with adjusted H/V size
// Input Value  : usNewHWidth       --> target H width
//                usNewVHeight      --> target V height
// Output Value : adjusted active region counter
//--------------------------------------------------
DWORD ScalerMeasureGetAdjustedActiveRegionCount(WORD usNewHWidth, WORD usNewVHeight)
{
    DWORD ulTotalCount = 0;
    DWORD ulNewTotalCount = 0;

    // Calculate pixel count
    ulTotalCount = ScalerMeasureGetdActiveRegionPixels(g_stInputTimingData.usHWidth,
                                                       g_stInputTimingData.usVHeight,
                                                       g_stInputTimingData.usHTotal);

    ulNewTotalCount = ScalerMeasureGetdActiveRegionPixels(usNewHWidth,
                                                          usNewVHeight,
                                                          g_stInputTimingData.usHTotal);

    return GET_DWORD_MUL_DIV(GET_INPUT_TIMING_ACTIVE_REGION(), ulNewTotalCount, ulTotalCount);
}
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Waiting for Auto Function Measure Finish
// Input Value  : None
// Output Value : True --> Measure Finish
//                False --> Measure Timeout or Fail
//--------------------------------------------------
bit ScalerMeasureAutoFuncWaitFinish(void)
{
    BYTE ucIvsCnt = 0;

    ucIvsCnt = (ScalerGetBit(P0_7A_AUTO_ADJ_CTRL0, _BIT1 | _BIT0) == 0x03) ? 3 : 1;
    ucIvsCnt = (ScalerGetBit(P0_7A_AUTO_ADJ_CTRL0, _BIT7) == _BIT7) ? ucIvsCnt * 2 : ucIvsCnt;
    ucIvsCnt += 2;

    do
    {
        if(ScalerTimerWaitForEvent(_EVENT_IVS) == _FALSE)
        {
            return _FALSE;
        }

        if(ScalerGetBit(P0_7D_AUTO_ADJ_CTRL1, _BIT0) == 0x00)
        {
            return _TRUE;
        }
    }
    while(--ucIvsCnt);

    return _FALSE;
}
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Update timing info from measure
// Input Value  : stMeasureSyncHV --> measure result
//                stActiveRegion --> auto-function result
//                stInputTimingData --> input timing data
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateInputTimingData(StructMeasureSyncData *pstMeasureSyncHV, StructAutoActiveData *pstActiveRegion)
{
    // Update measure result
    g_stInputTimingData.usHSWidth = ((pstMeasureSyncHV->b1HSP == _TRUE) ? pstMeasureSyncHV->usHSWidth : (pstMeasureSyncHV->usHSPeriod - pstMeasureSyncHV->usHSWidth));
    g_stInputTimingData.usVSWidth = ((pstMeasureSyncHV->b1VSP == _TRUE) ? pstMeasureSyncHV->usVSWidth : (pstMeasureSyncHV->usVSPeriod - pstMeasureSyncHV->usVSWidth));
    g_stInputTimingData.usVTotal = pstMeasureSyncHV->usVSPeriod;
    g_stInputTimingData.usHTotal = pstMeasureSyncHV->usHTotal;

#if(_VGA_SUPPORT == _ON)
    if(CHECK_MEASURE_FROM_VGA() == _TRUE)
    {
        g_stInputTimingData.usHFreq = (_SYNC_PROC_CLK * 10 * 2 / pstMeasureSyncHV->usHSPeriod + 1) / 2;
        g_stInputTimingData.usVFreq = (_SYNC_PROC_CLK * 1000 * 10 * 2 / pstMeasureSyncHV->usHSPeriod / pstMeasureSyncHV->usVSPeriod + 1) / 2;
    }
    else
#endif
    {
        g_stInputTimingData.usHFreq = (_MEASURE_CLK * 10 * 2 / pstMeasureSyncHV->usHSPeriod + 1) / 2;
        g_stInputTimingData.usVFreq = (_MEASURE_CLK * 1000 * 10 * 2 / pstMeasureSyncHV->usHSPeriod / pstMeasureSyncHV->usVSPeriod + 1) / 2;
    }

#if(_HDMI_2_0_SUPPORT == _ON)
    if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        g_stInputTimingData.usHTotal = (g_stInputTimingData.usHTotal << 1);
    }
#endif

    // Update auto-function result
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        g_stInputTimingData.usHStart = (pstActiveRegion->usHActiveStart << 1);
        g_stInputTimingData.usHWidth = ((pstActiveRegion->usHActiveEnd - pstActiveRegion->usHActiveStart) + 1);
    }
    else if(ScalerFmtCnvHalfSDGetStatus() == _TRUE)
    {
        g_stInputTimingData.usHStart = (pstActiveRegion->usHActiveStart << 1);
        g_stInputTimingData.usHWidth = (((pstActiveRegion->usHActiveEnd - pstActiveRegion->usHActiveStart) + 1) << 1);
    }
    else
#endif
    {
        g_stInputTimingData.usHStart = pstActiveRegion->usHActiveStart;
        g_stInputTimingData.usHWidth = ((pstActiveRegion->usHActiveEnd - pstActiveRegion->usHActiveStart) + 1);
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    // DP Freesync case, IVst = 1
    if(GET_DP_FREESYNC_ENABLED() == _TRUE)
    {
        PDATA_WORD(0) = _DP_FREESYNC_IVSTART;
    }
    else
#endif
    {
        PDATA_WORD(0) = pstActiveRegion->usVActiveStart;
    }

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
    {
        BYTE ucVstartLine = ((ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT4) == _BIT4) ? 0x00 : 0x01);
        g_stInputTimingData.usVStart = (PDATA_WORD(0) << 1) + ucVstartLine;
        g_stInputTimingData.usVHeight = (((pstActiveRegion->usVActiveEnd - pstActiveRegion->usVActiveStart) + 1) << 1);
    }
    else
#endif
    {
        g_stInputTimingData.usVStart = PDATA_WORD(0);
        g_stInputTimingData.usVHeight = (pstActiveRegion->usVActiveEnd - pstActiveRegion->usVActiveStart) + 1;
    }
}

#if((_MEASURE_ADJUSTED_IHF_SUPPORT == _ON) || (_MEASURE_ADJUSTED_IVF_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Update active region counter in measure flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateActiveRegion(void)
{
    WORD usHwidth = GET_INPUT_TIMING_HWIDTH();

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvHalfSDGetStatus() == _TRUE)
    {
        usHwidth /= 2;
    }
#endif

    // Set VGIP capture to input size
    ScalerVgipSetCaptureHWidth(usHwidth);
    ScalerVgipSetCaptureVHeight(GET_INPUT_TIMING_VHEIGHT());
    ScalerVgipCaptureEnable(_TRUE);

    // Set active region measure
    ScalerMeasureSetInputRegionCount(_ACTIVE_REGION_TYPE);
    SET_INPUT_TIMING_ACTIVE_REGION(ScalerMeasureGetInputRegionCountResult(_WAIT));

    DebugMessageMeasure("active region count", GET_INPUT_TIMING_ACTIVE_REGION());
}
#endif

