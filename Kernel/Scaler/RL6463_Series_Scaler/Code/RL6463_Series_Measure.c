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
// ID Code      : RL6463_Series_Measure.c No.0000
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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMeasureInterfaceInitial(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort *penumSourceSearchPort);
bit ScalerMeasureGetOfflineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV, EnumSourceSearchPort enumSourceSearchPort);
void ScalerMeasureSetOfflineMeasure(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourcePort);

#if(_DIGITAL_PORT_SUPPORT == _ON)
bit ScalerMeasureFinalSetting(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
void ScalerMeasureAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd);
bit ScalerMeasureGetAutoResult(StructAutoActiveData *pstActiveRegion, bit bWait);
bit ScalerMeasureInputInfo(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
void ScalerMeasureSetAuto(EnumMeasureFieldSelect enumFieldSelect);
#endif

void ScalerMeasureUpdateInputTimingPolarity(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, StructMeasureSyncData *pstMeasureSyncHV);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
bit ScalerMeasureCheckInterlaceVst(WORD usVstart, WORD usVend);
void ScalerMeasureCheckFirstLineShift(EnumSourceSearchPort enumSourceSearchPort, WORD usFrameHwidth);
#endif

void ScalerMeasureInterlaceInitial(BYTE ucSourceType, EnumSourceSearchPort enumSourceSearchPort);
bit ScalerMeasureInterlaceCheck(BYTE ucSourceType, EnumSourceSearchPort enumSourceSearchPort);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial measure interface
// Input Value  : enumSourceType: source type
//              : enumSourceSearchPort: port type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureInterfaceInitial(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort *penumSourceSearchPort)
{
    penumSourceSearchPort = penumSourceSearchPort;

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Special case for small DVS width
            if(ScalerGetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_05_CLAMP_CTRL1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
            {
                if(ScalerSyncProcGetDeVsyncWidth() >= 4)
                {
                    ScalerSetDataPortBit(P0_5C_SYNC_PROC_PORT_ADDR, _P0_5D_PT_05_CLAMP_CTRL1, ~(_BIT7 | _BIT6), 0x00);
                }
            }

            // Hsync Measure Source from SeHS or DeHS by CR49[6]
            ScalerSetBit(P0_49_SYNC_CTRL, ~_BIT2, _BIT2);

            break;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        case _SOURCE_HDMI:
        case _SOURCE_DVI:
            // Reset TMDS HS/VS polarity
            ScalerSetBit(P2_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Pop Up Sync Processor Measure Result
// Input Value  : stMeasureSyncHV --> measure result
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureGetOfflineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV, EnumSourceSearchPort enumSourceSearchPort)
{
    enumSourceSearchPort = enumSourceSearchPort;

    if(ScalerTimerPollingFlagProc(_MEASURE_TIMEOUT, P30_02_MEAS_CTL1, _BIT7, 0x00) == _FALSE)
    {
        return _FALSE;
    }

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
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
        // Check measure result status
        if(ScalerGetBit(P30_03_MEAS_ERROR_FLG0, (_BIT7 | _BIT5 | _BIT4)) != 0x00)
        {
            return _FALSE;
        }
    }

    // Pop up measurement result
    ScalerSetBit(P30_02_MEAS_CTL1, ~_BIT6, _BIT6);

    // Polarity
    pstMeasureSyncHV->b1HSP = (bit)ScalerGetBit(P30_04_MEAS_ERROR_FLG1, _BIT6);
    pstMeasureSyncHV->b1VSP = (bit)ScalerGetBit(P30_04_MEAS_ERROR_FLG1, _BIT7);

#if(_DP_FREESYNC_SUPPORT == _ON)
    // DP Freesync case, HSync Period, HSync Pulse Width and VSync Period use DP measure
    if(GET_DP_FREESYNC_ENABLED() == _TRUE)
    {
        // HSync Period
        pstMeasureSyncHV->usHSPeriod = ((DWORD)ScalerFreeSyncDpGetHSPeriod(enumSourceSearchPort) * _MEASURE_CLK / 1000000);

        // HSync Pulse Width
        pstMeasureSyncHV->usHSWidth = ScalerFreeSyncDpGetHSW(enumSourceSearchPort);

        // VSync Period
        pstMeasureSyncHV->usVSPeriod = ScalerFreeSyncDpGetVSPeriod(enumSourceSearchPort);
    }
    else
#endif
    {
        // HSync Period
        pstMeasureSyncHV->usHSPeriod = ((((WORD)ScalerGetByte(P30_05_MEAS_HS_PERIOD_A_M) & 0x1F) << 8) | (ScalerGetByte(P30_06_MEAS_HS_PERIOD_A_L))) + 1;

        // HSync Pulse Width
        pstMeasureSyncHV->usHSWidth = ((((WORD)ScalerGetByte(P30_0A_MEAS_HS_PULSE_A_M) & 0x1F) << 8) | (ScalerGetByte(P30_0B_MEAS_HS_PULSE_A_L))) + 1;

        // VSync Period
        pstMeasureSyncHV->usVSPeriod = ((((WORD)ScalerGetByte(P30_08_MEAS_VS_PERIOD_A_M) & 0x0F) << 8) | (ScalerGetByte(P30_09_MEAS_VS_PERIOD_A_L))) + 1;
    }

    // VSync Pulse Width
    pstMeasureSyncHV->usVSWidth = ((((WORD)ScalerGetByte(P30_0C_MEAS_VS_PULSE_A_M) & 0xF) << 8) | (ScalerGetByte(P30_0D_MEAS_VS_PULSE_A_L))) + 1;

    // H total
    pstMeasureSyncHV->usHTotal = ((((WORD)ScalerGetByte(P30_0E_MEAS_HS_PERIOD_D_M) & 0x1F) << 8) | (ScalerGetByte(P30_0F_MEAS_HS_PERIOD_D_L))) + 1;

    // V Height
    pstMeasureSyncHV->usVHeight = ((((WORD)ScalerGetByte(P30_11_MEAS_VS_PERIOD_D_M) & 0x0F) << 8) | (ScalerGetByte(P30_12_MEAS_VS_PERIOD_D_L))) + 1;

    // H Width
    pstMeasureSyncHV->usHWidth = ((((WORD)ScalerGetByte(P30_13_MEAS_HS_PULSE_D_M) & 0x1F) << 8) | (ScalerGetByte(P30_14_MEAS_HS_PULSE_D_L))) + 1;

    return _TRUE;
}
//--------------------------------------------------
// Description  : Set for Sync Processor Measure Input HV
// Input Value  : enumMeasureType --> Measure type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetOfflineMeasure(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourcePort)
{
    enumSourceType = enumSourceType;

    // Power up off-line measure; Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
    ScalerSetBit(P30_01_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT0), (_BIT7 | _BIT6));

    // Disable off-line measure
    ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

    if(enumSourcePort == _A0_INPUT_PORT)
    {
        // Set off line measure source; Disable clock divider
        ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
    }
    else
    {
        switch(enumSourcePort)
        {
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) || (_D1_INPUT_PORT_TYPE != _D1_NO_PORT))

            case _D0_INPUT_PORT:
            case _D1_INPUT_PORT:

                ScalerSetBit(P30_00_SYNC_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                break;

#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

            default:

                break;
        }
    }

    // Delay for measure reset
    ScalerTimerDelayXms(_MEASURE_RESET_TIME);

    // Enable off-line measure
    ScalerSetBit(P30_02_MEAS_CTL1, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial measure block
// Input Value  : enumSourceType: source type
//              : enumSourceSearchPort: port type
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureFinalSetting(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
    enumSourceType = enumSourceType;
    enumSourceSearchPort = enumSourceSearchPort;

    // Check timing validity
    if((GET_INPUT_TIMING_HWIDTH() >= GET_INPUT_TIMING_HTOTAL()) ||
       (GET_INPUT_TIMING_VHEIGHT() >= GET_INPUT_TIMING_VTOTAL()))
    {
        return _FALSE;
    }

#if((_MEASURE_ADJUSTED_IHF_SUPPORT == _ON) || (_MEASURE_ADJUSTED_IVF_SUPPORT == _ON))
    // Update active region count
    ScalerMeasureUpdateActiveRegion();
#endif

    return _TRUE;
}
//--------------------------------------------------
// Description  : Initial V Boundary for Auto Function Measure
// Input Value  : V Boundary Start/End
// Output Value : None
//--------------------------------------------------
void ScalerMeasureAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd)
{
    // Set V boundary
    ScalerSetByte(P0_73_V_BOUNDARY_H, (((HIBYTE(usVBoundStart) & 0x0F) << 4) | (HIBYTE(usVBoundEnd) & 0x0F)));
    ScalerSetByte(P0_74_V_BOUNDARY_STA_L, LOBYTE(usVBoundStart));
    ScalerSetByte(P0_75_V_BOUNDARY_END_L, LOBYTE(usVBoundEnd));
}

//--------------------------------------------------
// Description  : Pop Up Auto-Function Result
// Input Value  : stActiveRegion --> measure result
//                bWait --> wait auto-function stop or not
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureGetAutoResult(StructAutoActiveData *pstActiveRegion, bit bWait)
{
    if((bWait == _WAIT) || (ScalerGetBit(P0_7D_AUTO_ADJ_CTRL1, _BIT6) == 0x00))
    {
        if(ScalerMeasureAutoFuncWaitFinish() == _FALSE)
        {
            return _FALSE;
        }
    }

    pstActiveRegion->usVActiveStart = (((WORD)(ScalerGetByte(P0_7E_VER_START_END_H) & 0xF0) << 4) | ScalerGetByte(P0_7F_VER_START_L));
    pstActiveRegion->usVActiveEnd = (((WORD)(ScalerGetByte(P0_7E_VER_START_END_H) & 0x0F) << 8) | ScalerGetByte(P0_80_VER_END_L));
    pstActiveRegion->usHActiveStart = (((WORD)(ScalerGetByte(P0_81_H_START_END_H) & 0xF0) << 4) | ScalerGetByte(P0_82_H_START_L)) + 1;
    pstActiveRegion->usHActiveEnd = (((WORD)(ScalerGetByte(P0_81_H_START_END_H) & 0x0F) << 8) | ScalerGetByte(P0_83_H_END_L)) + 1;

    // Check auto-function measure result
    if(((pstActiveRegion->usVActiveStart == 0x00) &&
        (pstActiveRegion->usVActiveEnd == 0x00)) ||
       (pstActiveRegion->usHActiveStart == 0x00) ||
       (pstActiveRegion->usHActiveEnd == 0x00))
    {
        // No IDEN found.
        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : Measure Input Timing
// Input Value  : ucSourceType --> Input source type
// Output Value : _TURE => All Required Timing Info is done
//--------------------------------------------------
bit ScalerMeasureInputInfo(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
    //===========================================================================================
    // 0. Initialization
    //===========================================================================================

    // Initial the inteface to be measured
    ScalerMeasureInterfaceInitial(enumSourceType, &enumSourceSearchPort);

    // Initial measure & auto-function
    ScalerMeasureInitialSetting(enumSourceType, enumSourceSearchPort);

    // Initial Interlace Check Block
    ScalerMeasureInterlaceInitial(enumSourceType, enumSourceSearchPort);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        g_stActiveRegion = g_stSingleActiveRegion;
        g_stMeasureSyncHV = g_stSingleMeasureSyncHV;
        g_stInputTimingData = g_stSingleInputTimingData;
    }
    else
#endif
    {
        //===========================================================================================
        // 1. Start measure block & pop-out result
        //===========================================================================================

        // Wait for 2 raw IVS for digital; Pop out measure result
        if((ScalerTimerWaitForEvent(_EVENT_IVS) == _FALSE) ||
           (ScalerTimerWaitForEvent(_EVENT_IVS) == _FALSE) ||
           (ScalerMeasureGetOfflineMeasureResult(&g_stMeasureSyncHV, enumSourceSearchPort) == _FALSE))
        {
            DebugMessageMeasure("Digital off-line measure fail", 0x00);
            return _FALSE;
        }

        //===========================================================================================
        // 2. Check VGIP HS/VS polarity
        //===========================================================================================

        // Update input timing polarity
        ScalerMeasureUpdateInputTimingPolarity(enumSourceType, enumSourceSearchPort, &g_stMeasureSyncHV);

        // Modify VGIP sync polarity
        ScalerVgipModifyPolarity(enumSourceType);

        // Update input timing data from variable "g_stMeasureSyncHV"
        ScalerMeasureUpdateInputTimingData(&g_stMeasureSyncHV, &g_stActiveRegion);

        //===========================================================================================
        // 3. Start auto-function
        //===========================================================================================

        // Set auto-function digital measure
        ScalerMeasureSetAuto(_NORMAL_MEASURE);

        // Wait for 2 latched IVS; Pop out auto-function result
        if((ScalerTimerWaitForEvent(_EVENT_IVS) == _FALSE) ||
           (ScalerTimerWaitForEvent(_EVENT_IVS) == _FALSE) ||
           (ScalerMeasureGetAutoResult(&g_stActiveRegion, _NOT_WAIT) == _FALSE))
        {
            DebugMessageMeasure("Digital auto-function fail", 0x00);
            return _FALSE;
        }

        // Update input timing data
        ScalerMeasureUpdateInputTimingData(&g_stMeasureSyncHV, &g_stActiveRegion);

        //===========================================================================================
        // 4. Detect interlace format
        //===========================================================================================

        // Check interlace by flag
        if(ScalerMeasureInterlaceCheck(enumSourceType, enumSourceSearchPort) == _TRUE)
        {
            DebugMessageMeasure("Interlace: detect by flag", 0x00);
            g_stInputTimingData.b1Interlace = _TRUE;
        }

        // Update input timing data
        ScalerMeasureUpdateInputTimingData(&g_stMeasureSyncHV, &g_stActiveRegion);

        //===========================================================================================
        // 5. Double-check current timing
        //===========================================================================================

        // Check digital measure result
        if(abs(GET_SYNC_V_HEIGHT() - GET_INPUT_TIMING_VHEIGHT()) > 2)
        {
            DebugMessageMeasure("Digital check V height fail", 0x00);
            return _FALSE;
        }

        if(abs(GET_SYNC_H_WIDTH() - GET_INPUT_TIMING_HWIDTH()) > 2)
        {
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
            if((enumSourceType == _SOURCE_DVI) || (enumSourceType == _SOURCE_HDMI))
            {
                // Check first line width for DVI/HDMI
                ScalerMeasureCheckFirstLineShift(enumSourceSearchPort, GET_SYNC_H_WIDTH());
            }
#endif

            DebugMessageMeasure("Digital check H width fail", 0x00);
            return _FALSE;
        }

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
        g_stSingleActiveRegion = g_stActiveRegion;
        g_stSingleMeasureSyncHV = g_stMeasureSyncHV;
        g_stSingleInputTimingData = g_stInputTimingData;
#endif
    }

    //===========================================================================================
    // 6. Measure final settings
    //===========================================================================================

    // Perform measure final setting
    if(ScalerMeasureFinalSetting(enumSourceType, enumSourceSearchPort) == _FALSE)
    {
        DebugMessageMeasure("Final setting in measure fail", 0x00);
        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : Initialization for Picture Position <easure by Auto Function Measure
// Input Value  : EnumMeasureFieldSelect --> Measure for Even or Odd Field
// Output Value : None
//--------------------------------------------------
void ScalerMeasureSetAuto(EnumMeasureFieldSelect enumFieldSelect)
{
    // Disable auto-function
    ScalerSetBit(P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, 0x00);

    // Set auto VS delay to 0
    ScalerSetBit(P0_1E_M1_VGIP_HV_DELAY, ~(_BIT5 | _BIT4), 0x00);

    if(enumFieldSelect == _EVEN_FIELD_MEASURE)
    {
        // Field Select to Even, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        ScalerSetByte(P0_7A_AUTO_ADJ_CTRL0, 0x80);
    }
    else if(enumFieldSelect == _ODD_FIELD_MEASURE)
    {
        // Field Select to Odd, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        ScalerSetByte(P0_7A_AUTO_ADJ_CTRL0, 0xC0);
    }
    else
    {
        // Disable Field Select, Disable LPF, Disable Accelecration Mode, Vertical Boundary Search 1 pixel, Select B channel
        ScalerSetByte(P0_7A_AUTO_ADJ_CTRL0, 0x00);
    }

    // Set HW auto-phase: step = 31
    ScalerSetByte(P0_7B_HW_AUTO_PHASE_CTRL0, 0xF8);

    // Set H boundary
    ScalerMeasureAutoFuncHBoundInitial(0x0002, 0x0FFF);

    // Set V Boundary
    ScalerMeasureAutoFuncVBoundInitial(0x0000, 0x0FFF);

    // Digital Measure Mode, Select Auto Balance, Start Auto Function Measure; Start auto-function measure
    ScalerSetBit(P0_7D_AUTO_ADJ_CTRL1, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));
}
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Update timing info HS/VS polarity
// Input Value  : ucSourceType --> source type
//                stMeasureSyncHV --> measured timing data
// Output Value : None
//--------------------------------------------------
void ScalerMeasureUpdateInputTimingPolarity(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, StructMeasureSyncData *pstMeasureSyncHV)
{
    enumSourceSearchPort = enumSourceSearchPort;
    pstMeasureSyncHV = pstMeasureSyncHV;

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Get Raw HSync Polarity by SyncProcessor Auto Run
            if(ScalerGetBit(P0_47_SYNC_SELECT, _BIT6) == _BIT6)
            {
                g_stInputTimingData.b1HSP = (bit)(pstMeasureSyncHV->b1HSP ^ (((bit)ScalerGetBit(P0_48_SYNC_INVERT, _BIT3) ? _BIT0 : 0x00) ^ ((bit)ScalerGetBit(P0_50_STABLE_PERIOD_H, _BIT6) ? _BIT0 : 0x00)));
            }
            else
            {
                g_stInputTimingData.b1HSP = (bit)(pstMeasureSyncHV->b1HSP ^ (((bit)ScalerGetBit(P0_48_SYNC_INVERT, _BIT3) ? _BIT0 : 0x00)));
            }

            g_stInputTimingData.b1VSP = (pstMeasureSyncHV->b1VSP ^ (bit)ScalerGetBit(P30_01_MEAS_CTL0, _BIT3));

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            // Pop out DP polarity
            ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
            g_stInputTimingData.b1HSP = (bit)(ScalerGetBit(PB6_0E_MSA_HSW_0, _BIT7) == 0x00);
            g_stInputTimingData.b1VSP = (bit)(ScalerGetBit(PB6_18_MSA_VSW_0, _BIT7) == 0x00);

            break;
#endif

#if((_HDMI_SUPPORT == _ON) || (_DVI_SUPPORT == _ON))
        case _SOURCE_HDMI:
        case _SOURCE_DVI:

            if(ScalerGetBit(P2_A7_TMDS_PWDCTL, _BIT7) == _BIT7)
            {
                if(ScalerGetBit(P2_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
                {
                    // Read HS/VS polarity from MAC
                    g_stInputTimingData.b1HSP = (ScalerGetBit(P2_C0_HDCP_CR, _BIT6) == 0x00);
                    g_stInputTimingData.b1VSP = (ScalerGetBit(P2_C0_HDCP_CR, _BIT5) == 0x00);
                }
                else
                {
                    // Positive HS/VS under DE-only mode
                    g_stInputTimingData.b1HSP = _TRUE;
                    g_stInputTimingData.b1VSP = _TRUE;
                }
            }
            else
            {
                g_stInputTimingData.b1HSP = pstMeasureSyncHV->b1HSP;
                g_stInputTimingData.b1VSP = pstMeasureSyncHV->b1VSP;
            }

            break;
#endif
        default:
            break;
    }
}

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Check V start position for interlaced format
// Input Value  : usVstart --> alternative V start
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMeasureCheckInterlaceVst(WORD usVstart, WORD usVend)
{
    if(usVstart == g_stActiveRegion.usVActiveStart)
    {
        // For 1035i
        if((usVend - usVstart) == (g_stActiveRegion.usVActiveEnd - g_stActiveRegion.usVActiveStart))
        {
            // Toggle Video Compensation field
            ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT6, (~(ScalerGetByte(P0_32_SCALE_CONTROL_REG)) & _BIT6));
        }
        else if((usVend - usVstart) < 250)
        {
            // For 487i
            ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT6, (~(ScalerGetByte(P0_32_SCALE_CONTROL_REG)) & _BIT6));
        }
    }
    else if(abs(usVstart - g_stActiveRegion.usVActiveStart) == 0x01)
    {
        StructAutoActiveData stAutoActiveData;
        memset(&stAutoActiveData, 0, sizeof(StructAutoActiveData));

        // Store the smaller Vstart
        if(usVstart < g_stActiveRegion.usVActiveStart)
        {
            --g_stActiveRegion.usVActiveStart;
            --g_stActiveRegion.usVActiveEnd;
        }

        // Enable ODD delay one line
        ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6), _BIT6);

        // Toggle Video Compensation field
        ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT6, (~(ScalerGetByte(P0_32_SCALE_CONTROL_REG)) & _BIT6));

        if((ScalerTimerWaitForEvent(_EVENT_IVS) == _FALSE) ||
           (ScalerTimerWaitForEvent(_EVENT_IVS) == _FALSE) ||
           (ScalerTimerWaitForEvent(_EVENT_IVS) == _FALSE))
        {
            return _FALSE;
        }

        // Pop up auto-function result
        if(ScalerMeasureGetAutoResult(&stAutoActiveData, _NOT_WAIT) == _FALSE)
        {
            return _FALSE;
        }

        // Double-check delay-one-line field polarity
        if(stAutoActiveData.usVActiveStart != g_stActiveRegion.usVActiveStart)
        {
            // Toggle delay-one-line field
            ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~_BIT7, (~(ScalerGetByte(P0_13_M1_VGIP_ODD_CTRL)) & _BIT7));
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Measure H width for the first line
// Input Value  : usFrameHwidth: H width from measure block
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
void ScalerMeasureCheckFirstLineShift(EnumSourceSearchPort enumSourceSearchPort, WORD usFrameHwidth)
{
    enumSourceSearchPort = enumSourceSearchPort;

    // Check under DE-only mode with raw HS/VS
    if((ScalerGetBit(P2_A7_TMDS_PWDCTL, _BIT7) == _BIT7) &&
       (ScalerGetBit(P2_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3)))
    {
        // Stop auto-function
        ScalerSetBit(P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

        // Set measure boundary to first line
        ScalerMeasureAutoFuncHBoundInitial(0x0002, 0x1FFF);
        ScalerMeasureAutoFuncVBoundInitial((GET_ACTIVE_V_START() + 1), GET_INPUT_TIMING_VTOTAL());

        // Start auto-function measure
        ScalerSetBit(P0_7D_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

        if((ScalerTimerWaitForEvent(_EVENT_IVS) == _FAIL) ||
           (ScalerTimerWaitForEvent(_EVENT_IVS) == _FAIL))
        {
            return;
        }

        // Calculate first H width
        PDATA_WORD(0) = ((((WORD)ScalerGetBit(P0_81_H_START_END_H, 0xF0)) << 4) | ScalerGetByte(P0_82_H_START_L)); // H st
        PDATA_WORD(1) = ((((WORD)ScalerGetBit(P0_81_H_START_END_H, 0x0F)) << 8) | ScalerGetByte(P0_83_H_END_L)); // H end
        PDATA_WORD(2) = (PDATA_WORD(1) - PDATA_WORD(0) + 1); // H width

        if(abs(PDATA_WORD(2) - usFrameHwidth) <= 1)
        {
            // First line shift detected; Disable DE-only mode
            ScalerSetBit(P2_A7_TMDS_PWDCTL, ~_BIT7, 0x00);
        }
    }
}
#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Initial Interlace Detection Method
// Input Value  : Source Type
// Output Value : None
//--------------------------------------------------
void ScalerMeasureInterlaceInitial(BYTE ucSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
    enumSourceSearchPort = enumSourceSearchPort;

    // Disable IVS Delay one line; Default field source from VGIP
    ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~(_BIT7 | _BIT6 | _BIT0), _BIT0);

    // Clear VGIP Interlace Toggle Flag
    ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

    switch(ucSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Clear Interlace toggle flag
            ScalerSetBit(P0_4A_STABLE_HIGH_PERIOD_H, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

            break;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            // Clear Interlace toggle and error flag
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_50_PORT_PAGE2_HDMI_VCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            enumSourceSearchPort = enumSourceSearchPort; // For unreferenced local variable

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check Interlace
// Input Value  : Source Type
// Output Value : TRUE => Interlaced Detected
//--------------------------------------------------
bit ScalerMeasureInterlaceCheck(BYTE ucSourceType, EnumSourceSearchPort enumSourceSearchPort)
{
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    WORD usVstart = 0x0000;
    WORD usVend = 0x0000;
#endif

    enumSourceSearchPort = enumSourceSearchPort;

    switch(ucSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            if(ScalerMeasureVgaInterlaceCheck(enumSourceSearchPort) == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            // Clear VGIP Interlace Toggle Flag
            ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

            // Clear Interlace toggle flag
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_50_PORT_PAGE2_HDMI_VCR, ~_BIT6, _BIT6);

            // Delay until field stable
            if(GET_INPUT_TIMING_DOUBLE_CHECK() == _FALSE)
            {
                ScalerTimerWaitForEvent(_EVENT_IVS);
                g_stActiveRegion.usVActiveStart = (((WORD)(ScalerGetByte(P0_7E_VER_START_END_H) & 0xF0) << 4) | ScalerGetByte(P0_7F_VER_START_L));
                g_stActiveRegion.usVActiveEnd = (((WORD)(ScalerGetByte(P0_7E_VER_START_END_H) & 0x0F) << 8) | ScalerGetByte(P0_80_VER_END_L));

                // Get another V start
                ScalerTimerWaitForEvent(_EVENT_IVS);
                usVstart = (((WORD)(ScalerGetByte(P0_7E_VER_START_END_H) & 0xF0) << 4) | ScalerGetByte(P0_7F_VER_START_L));
                usVend = (((WORD)(ScalerGetByte(P0_7E_VER_START_END_H) & 0x0F) << 8) | ScalerGetByte(P0_80_VER_END_L));
            }
            else
            {
                ScalerTimerWaitForEvent(_EVENT_IVS);
                ScalerTimerWaitForEvent(_EVENT_IVS);
            }

#if(_DVI_DE_ONLY_SUPPORT == _ON)
            if(ScalerGetBit(P2_A4_TMDS_CTRL, (_BIT4 | _BIT3)) != (_BIT4 | _BIT3))
            {
                // Detect by Vtotal
                if(ScalerGetBit(P0_1A_M1_IPV_ACT_LEN_H, _BIT5) == _BIT5)
                {
                    if(GET_INPUT_TIMING_DOUBLE_CHECK() == _FALSE)
                    {
                        // Interlace field signal from VGIP
                        ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~_BIT0, _BIT0);

                        // Set Video Compensation to ODD Field
                        ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT6, 0x00);

                        // Check delay one line
                        ScalerMeasureCheckInterlaceVst(usVstart, usVend);
                    }

                    // Clear VGIP Interlace Toggle Flag
                    ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

                    return _TRUE;
                }
            }
            else
#endif
            {
                // Detect by VS Position
                if(ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_50_PORT_PAGE2_HDMI_VCR, _BIT6) == _BIT6)
                {
                    if(ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_50_PORT_PAGE2_HDMI_VCR, _BIT5) == 0x00)
                    {
                        if(GET_INPUT_TIMING_DOUBLE_CHECK() == _FALSE)
                        {
                            // Interlace field signal from interface
                            ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~_BIT0, 0x00);

                            // Set Video Compensation to EVEN Field
                            ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT6, _BIT6);

                            // Check delay one line
                            ScalerMeasureCheckInterlaceVst(usVstart, usVend);
                        }

                        // Clear Interlace toggle flag
                        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_50_PORT_PAGE2_HDMI_VCR, ~_BIT6, _BIT6);
                        return _TRUE;
                    }
                }
            }

            // Clear VGIP Interlace Toggle Flag
            ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

            // Clear Interlace toggle and error flag
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_50_PORT_PAGE2_HDMI_VCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            break;
#endif

#if(_DP_SUPPORT == _ON)

        case _SOURCE_DP:

            if(ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == _BIT7)
            {
                if(GET_INPUT_TIMING_DOUBLE_CHECK() == _FALSE)
                {
                    // Interlace field signal from interface
                    ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~_BIT0, 0x00);

                    // Set Video Compensation to EVEN Field
                    ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT6, _BIT6);
                }

                return _TRUE;
            }

            if(ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
            {
                if(ScalerGetBit(P0_1A_M1_IPV_ACT_LEN_H, _BIT5) == _BIT5)
                {
                    if(GET_INPUT_TIMING_DOUBLE_CHECK() == _FALSE)
                    {
                        // Select Filed Signal from VGIP
                        ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~_BIT0, _BIT0);

                        // Set Video Compensation to ODD Field
                        ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~_BIT6, 0x00);
                    }

                    // Clear VGIP Interlace Toggle Flag
                    ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

                    return _TRUE;
                }
            }

            if(ScalerGetBit(PB6_01_DP_VBID, _BIT2) == _BIT2)
            {
                g_stInputTimingData.b1DpInterlaceVBID = _TRUE;
            }

            // Clear VGIP Interlace Toggle Flag
            ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);

            break;
#endif
        default:
            break;
    }

    return _FALSE;
}
