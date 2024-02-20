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
// ID Code      : ScalerCommonDPRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_DPRX1__

#include "ScalerCommonFunctionInclude.h"

#if(_D1_DP_EXIST == _ON)

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
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
bit g_bDpRx1SignaldetectINTHappened;
#endif

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT != _ON)
BYTE g_ucDpRx1DPCD02200hValue = _DP_VERSION_1_4;
BYTE g_ucDpRx1DPCD02201hValue = _D1_DP_LINK_CLK_RATE;
BYTE g_ucDpRx1DPCD02210hValue;
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit g_bDpRx1VscSdpColorMode;

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
bit g_bDpRx1RSV1PacketDetecting;

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
bit g_bDpRx1MstToSstRSV1PacketDetecting;
#endif
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
WORD g_usDpRx1MstToSstVfrontporch;
#endif

BYTE g_ucDpRx1MSAFailMacRsetCount;
bit g_bDpRx1SourceRDErrorCount = _FALSE;
bit g_bDpRx1InterlaceVtotalNum;

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
bit g_bDpRx1SourceTypeJudge = _FALSE;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
BYTE g_ucDPRx1InfoTypeCompare;
BYTE g_pucDPRx1HDR10Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
BYTE g_pucDPRx1InfoTemp[_HW_DP_INFOFRAME_RSV0_LENGTH];
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
BYTE g_pucDPRx1RSV0Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
StructDPInfoFrameRSV0Ctrl g_stDPRx1InfoFrameRSV0Ctrl;
#endif

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
BYTE g_ucDpRx1AuxModeBackup_EXINT;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx1DecodeErrorCountReset_WDINT(void);
#endif

void ScalerDpRx1DecodeErrorCountReset(void);
WORD ScalerDpRx1GetDecodeErrorCount(BYTE ucDpRx1LaneNumber);
void ScalerDpRx1ValidSignalDetection(void);
BYTE ScalerDpRx1LinkRateDetect(void);
bit ScalerDpRx1LinkRateCheck(BYTE ucDpLinkRate);
WORD ScalerDpRx1SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);
bit ScalerDpRx1SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
bit ScalerDpRx1VBIOSMSACheck(bit bDeskewEnhanced);
#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
bit ScalerDpRx1VbiosAssrCheck(bit bMSACheckResult);
#endif
bit ScalerDpRx1ChangeSrambleSeed(void);
bit ScalerDpRx1InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);
bit ScalerDpRx1GetVideoInfo(void);
void ScalerDpRx1SetColorInfo(void);
void ScalerDpRx1VideoSetting(void);
void ScalerDpRx1ColorimetrySetting(void);
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
void ScalerDpRx1ColorimetryExtSetting(void);
#endif
void ScalerDpRx1QuantizationSetting(void);

bit ScalerDpRx1MiscCheck(void);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit ScalerDpRx1VscCheck(void);

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
void ScalerDpRx1RSV1PacketDetectEvent(void);
void ScalerDpRx1SetInitialRSV1InfoType(void);
#endif

#endif

void ScalerDpRx1HDCPUnplugReset(void);

#if(_DP_MST_SUPPORT == _ON)
void ScalerDpRx1MstReset(void);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
void ScalerDpRx1MstReset_EXINT0(void);
#endif

bit ScalerDpRx1AuxChSourcePowerCheck(void);
void ScalerDpRx1AuxChPowerStatusCheck(bit bCableStatus);

#if(_DP_TX_SUPPORT == _ON)
bit ScalerDpRx1MstToSstInterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
void ScalerDpRx1MstToSstRSV1PacketDetectEvent(void);
#endif
#endif
#endif
#endif

bit ScalerDpRx1MSACheck(void);
void ScalerDpRx1FakeLTProtect(void);
void ScalerDpRx1SetInitialRSV0InfoType(void);
void ScalerDpRx1SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType);
void ScalerDpRx1HpdIrqAssert(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
void ScalerDpRx1HpdIrqAssert_EXINT0(void);
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_ULTRA_HDR_SUPPORT == _ON))
void ScalerDpRx1GetInfoFrameRSV0(BYTE *pucDPRx1RSV0Data);
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
void ScalerDpRx1InfoFrameRSV0Check(void);
void ScalerDpRx1RSV0PacketDetectEvent(void);
void ScalerDpRx1InfoFrameRSV0Initial(void);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
BYTE ScalerDpRx1SelectInfoFrameType(BYTE ucInfoFrameTypeCurrent);

#if(_AUDIO_SUPPORT == _ON)
void ScalerDpRx1SwitchHDR10CmpAudioInfo(void);
#endif
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DecodeErrorCountReset_WDINT(void) using 3
{
    // Reset 8b10b Error Count Value
    ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Start Record 8b10b Error Count Value
    ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
}
#endif

//--------------------------------------------------
// Description  : Reset 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DecodeErrorCountReset(void)
{
    // Reset 8b10b Error Count Value
    ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Start Record 8b10b Error Count Value
    ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
}

//--------------------------------------------------
// Description  : Get 8b10b Error Count value
// Input Value  : Lane
// Output Value : Error Count
//--------------------------------------------------
WORD ScalerDpRx1GetDecodeErrorCount(BYTE ucDpRx1LaneNumber)
{
    // Select Lane
    ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (ucDpRx1LaneNumber << 3));

    return ((((WORD)ScalerGetByte(PB0_0B_BIST_PATTERN3)) << 8) | ScalerGetByte(PB0_0C_BIST_PATTERN4));
}

//--------------------------------------------------
// Description  : Check Valid Video Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ValidSignalDetection(void)
{
    BYTE ucDpLinkRate = 0;
    BYTE ucDpLaneCount = _DP_FOUR_LANE;

#if(_DP_MST_SUPPORT == _ON)

    if(g_stDpRx1MiscInfo.b1DpMstEnableBackup == _TRUE)
    {
        SET_DP_RX1_AUX_MANUAL_MODE();

        if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
           (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00) &&
           (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) != _BIT1))
        {
            ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x00, g_stDpRx1MiscInfo.ucDpRxLinkRateBackup);
            ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x01, ((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x60) | (g_stDpRx1MiscInfo.ucDpRxLaneCountBackup | _BIT7)));

            if(g_stDpRx1MiscInfo.ucDpRxLaneCountBackup == _DP_FOUR_LANE)
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x77);
            }
            else if(g_stDpRx1MiscInfo.ucDpRxLaneCountBackup == _DP_TWO_LANE)
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x00);
            }
            else
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x07);
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x00);
            }

            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x04, 0x01);

            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS_VBIOS);

            ScalerDpRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESTORE);
        }

        SET_DP_RX1_AUX_AUTO_MODE();

        DebugMessageRx1("VBIOS_Link_Rate_MST", ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00));
        DebugMessageRx1("VBIOS_Lane_Count_MST", ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01));
    }
    else
#endif // End of #if(_DP_MST_SUPPORT == _ON)
    {
        SET_DP_RX1_AUX_MANUAL_MODE();

#if(_DP_MST_SUPPORT == _ON)
        if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
           (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00) &&
           (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) != _BIT1))
#else
        if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
           (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
#endif
        {
            ucDpLinkRate = ScalerDpRx1LinkRateDetect();

            SET_DP_RX1_AUX_AUTO_MODE();

            if(ucDpLinkRate == _DP_LINK_NONE)
            {
                return;
            }

            do
            {
                SET_DP_RX1_AUX_MANUAL_MODE();

#if(_DP_MST_SUPPORT == _ON)
                if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
                   (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00) &&
                   (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) != _BIT1))
#else
                if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
                   (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
#endif
                {
                    ScalerDpRx1RebuildPhy(ucDpLinkRate, (ucDpLaneCount | _BIT7));

                    SET_DP_RX1_AUX_AUTO_MODE();

                    if(ScalerDpRx1VBIOSMSACheck(_FALSE) == _TRUE)
                    {
                        break;
                    }
                    else
                    {
                        if(ScalerDpRx1VBIOSMSACheck(_TRUE) == _TRUE)
                        {
                            break;
                        }
                    }

                    if(ucDpLaneCount == _DP_FOUR_LANE)
                    {
                        ucDpLaneCount = _DP_TWO_LANE;
                    }
                    else if(ucDpLaneCount == _DP_TWO_LANE)
                    {
                        ucDpLaneCount = _DP_ONE_LANE;
                    }
                    else if(ucDpLaneCount == _DP_ONE_LANE)
                    {
                        ucDpLaneCount = 0x00;
                    }
                }
                else
                {
                    SET_DP_RX1_AUX_AUTO_MODE();

                    return;
                }
            }
            while((ucDpLaneCount == _DP_TWO_LANE) || (ucDpLaneCount == _DP_ONE_LANE));

            SET_DP_RX1_AUX_MANUAL_MODE();

#if(_DP_MST_SUPPORT == _ON)
            if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
               (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00) &&
               (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) != _BIT1))
#else
            if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
               (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
#endif
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x00, ucDpLinkRate);
                ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x01, ((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x60) | (ucDpLaneCount | _BIT7)));

                if(ucDpLaneCount == _DP_FOUR_LANE)
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x77);
                }
                else if(ucDpLaneCount == _DP_TWO_LANE)
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x00);
                }
                else
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x07);
                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x00);
                }

                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x04, 0x01);

                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS_VBIOS);
            }

            SET_DP_RX1_AUX_AUTO_MODE();
        }

        SET_DP_RX1_AUX_AUTO_MODE();

        DebugMessageRx1("VBIOS_Link_Rate", ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00));
        DebugMessageRx1("VBIOS_Lane_Count", ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01));
    }
}

//--------------------------------------------------
// Description : DP Link Rate Detect
// Input Value  : None
// Output Value : Link Rate
//--------------------------------------------------
BYTE ScalerDpRx1LinkRateDetect(void)
{
    BYTE ucDpLinkRate = 0;
    BYTE ucDpLinkRateDecide = _DP_LINK_NONE;

    do
    {
        if(ucDpLinkRate == 0)
        {
            if(_HW_DP_D1_MAX_LINK_RATE_SUPPORT > ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x01))
            {
                ucDpLinkRate = _HW_DP_D1_MAX_LINK_RATE_SUPPORT;
            }
            else
            {
                ucDpLinkRate = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x01);
            }
        }
        else if(ucDpLinkRate == _DP_LINK_HBR3)
        {
            ucDpLinkRate = _DP_LINK_HBR2;
        }
        else if(ucDpLinkRate == _DP_LINK_HBR2)
        {
            ucDpLinkRate = _DP_LINK_HBR;
        }
        else if(ucDpLinkRate == _DP_LINK_HBR)
        {
            ucDpLinkRate = _DP_LINK_RBR;
        }

        if(ScalerDpRx1LinkRateCheck(ucDpLinkRate) == _TRUE)
        {
            ucDpLinkRateDecide = ucDpLinkRate;

            break;
        }
    }
    while(ucDpLinkRate != _DP_LINK_RBR);

    return ucDpLinkRateDecide;
}

//--------------------------------------------------
// Description : Check Valid Lane
// Input Value  : ucDpLinkRate -> DP Link Rate
// Output Value : _TRUE -> Valid Signal
//--------------------------------------------------
bit ScalerDpRx1LinkRateCheck(BYTE ucDpLinkRate)
{
    WORD usDataStreamL0 = 0;
    BYTE ucDpLEQScanValue = _DP_RELOAD_LEQ_INITIAL;
    WORD usMeasureUpperBound = 0;
    WORD usMeasureLowerBound = 0;

    do
    {
        if(ucDpLEQScanValue == _DP_RELOAD_LEQ_INITIAL)
        {
            ucDpLEQScanValue = _DP_RELOAD_LEQ_LARGE;
        }
        else if(ucDpLEQScanValue == _DP_RELOAD_LEQ_LARGE)
        {
            ucDpLEQScanValue = _DP_RELOAD_LEQ_DEFAULT;
        }

        ScalerDpRx1SignalDetectInitial(ucDpLinkRate, ucDpLEQScanValue);

        usDataStreamL0 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

        switch(ucDpLinkRate)
        {
            case _DP_LINK_HBR2:

                usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_HBR2_SAVED;
                usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_HBR2_SAVED;

                break;

            case _DP_LINK_HBR:

                usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_HBR_SAVED;
                usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_HBR_SAVED;

                break;

            case _DP_LINK_RBR:

                usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_RBR_SAVED;
                usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_RBR_SAVED;

                break;

            default:

                break;
        }

        if((usDataStreamL0 < usMeasureUpperBound) && (usDataStreamL0 > usMeasureLowerBound))
        {
            return _TRUE;
        }
    }
    while(ucDpLEQScanValue != _DP_RELOAD_LEQ_DEFAULT);

    return _FALSE;
}

//--------------------------------------------------
// Description : DP Signal Detection Measure
// Input Value  : DP Lane Select, Measure target, Measure Period
// Output Value : Measure Counter
//--------------------------------------------------
WORD ScalerDpRx1SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod)
{
    WORD usDpMeasureCount = 0;

    // [1:0] freqdet_lane_sel
    ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ucDpLaneSel & (_BIT1 | _BIT0)));

    // [5] ln_ck_sel
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT5, enumDpMeasureTarget);

    switch(enumDpMeasurePeriod)
    {
        case _DP_MEASURE_PERIOD_1000_CYCLE:

#if(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_1)
            // [4:0] DP_XTAL_CYCLE = 5'b00011
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
#elif(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_2)
            // [0] DP_XTAL_CYCLE = 1'b0
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT0, 0x00);
#endif
            break;

        case _DP_MEASURE_PERIOD_2000_CYCLE:
        default:

#if(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_1)
            // [4:0] DP_XTAL_CYCLE = 5'b00100
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
#elif(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_2)
            // [0] DP_XTAL_CYCLE = 1'b1
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT0, _BIT0);
#endif
            break;
    }

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            usDpMeasureCount = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

            break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    return usDpMeasureCount;
}

//--------------------------------------------------
// Description : Check Valid Signal
// Input Value  : DP Link Rate and Lane Count
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx1SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
    WORD usDataStreamL0 = 0;
    WORD usDataStreamL1 = 0;
    WORD usDataStreamL2 = 0;
    WORD usDataStreamL3 = 0;
    WORD usMeasureUpperBound = 0;
    WORD usMeasureLowerBound = 0;

    // Scrambling Disable Check
    if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x02, _BIT5) == _BIT5)
    {
        return _TRUE;
    }

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
    CLR_DP_RX1_SIGNALDETECT_INT_HAPPENED();
#endif

    // Measure Data Stream Count
    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            usDataStreamL0 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;

        case _DP_TWO_LANE:

            usDataStreamL0 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL1 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;

        default:
        case _DP_FOUR_LANE:

            usDataStreamL0 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL1 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL2 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE2, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL3 = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE3, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;
    }

    // Data Stream Count Upper Bound = (VCO target count) x 2 x 0.65
    // Data Stream Count Lower Bound = (VCO target count) x 2 x 0.55
    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_HBR2_SAVED;
            usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_HBR2_SAVED;

            break;

        case _DP_LINK_HBR:

            usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_HBR_SAVED;
            usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_HBR_SAVED;

            break;

        case _DP_LINK_RBR:

            usMeasureUpperBound = _DP_COUNT_SST_UPPER_BOUND_2000_RBR_SAVED;
            usMeasureLowerBound = _DP_COUNT_SST_LOWER_BOUND_2000_RBR_SAVED;

            break;

        default:

            break;
    }

    // Link Rate is a Unreasonable Value
    if((usMeasureUpperBound == 0) || (usMeasureLowerBound == 0))
    {
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
        if(GET_DP_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
        {
            return _FALSE;
        }
    }

    // Check Data Stream Count
    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            if((usDataStreamL0 > usMeasureUpperBound) || (usDataStreamL0 < usMeasureLowerBound))
            {
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
                {
                    return _FALSE;
                }
            }

            break;

        case _DP_TWO_LANE:

            if(((usDataStreamL0 > usMeasureUpperBound) || (usDataStreamL0 < usMeasureLowerBound)) ||
               ((usDataStreamL1 > usMeasureUpperBound) || (usDataStreamL1 < usMeasureLowerBound)))
            {
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
                {
                    return _FALSE;
                }
            }

            break;

        default:
        case _DP_FOUR_LANE:

            if(((usDataStreamL0 > usMeasureUpperBound) || (usDataStreamL0 < usMeasureLowerBound)) ||
               ((usDataStreamL1 > usMeasureUpperBound) || (usDataStreamL1 < usMeasureLowerBound)) ||
               ((usDataStreamL2 > usMeasureUpperBound) || (usDataStreamL2 < usMeasureLowerBound)) ||
               ((usDataStreamL3 > usMeasureUpperBound) || (usDataStreamL3 < usMeasureLowerBound)))
            {
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_RX1_SIGNALDETECT_INT_HAPPENED() == _FALSE)
#endif
                {
                    return _FALSE;
                }
            }

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : VBIOS Lane Adjust
// Input Value  : DP Lane Count
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpRx1VBIOSMSACheck(bit bDeskewEnhanced)
{
    bit bMSACheckResult = _FALSE;

    do
    {
        // De-Skew Circuit Reset
        ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), (((bDeskewEnhanced == _TRUE) ? _BIT7 : 0x00) | _BIT6));

        // Mac Reset After Link Clock Stable
        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

        // SEC Reset
        ScalerSetBit(PB8_00_MAC_DIG_RESET_CTRL, ~_BIT4, _BIT4);
        ScalerSetBit(PB8_00_MAC_DIG_RESET_CTRL, ~_BIT4, 0x00);

        // Wait Two Frame Time to Get MSA
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        // Pop up Main Stream Attributes
        ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

        // Get Nvid
        ScalerRead(PB9_1D_MSA_NVID_0, 3, pData, _AUTOINC);

        // Get Hactive
        ScalerRead(PB9_0C_MSA_HWD_0, 2, &pData[4], _AUTOINC);

        // Get Vactive
        ScalerRead(PB9_16_MSA_VHT_0, 2, &pData[6], _AUTOINC);

        // Get Hstart
        ScalerRead(PB9_0A_MSA_HST_0, 2, &pData[8], _AUTOINC);

        // Get Vstart
        ScalerRead(PB9_14_MSA_VST_0, 2, &pData[10], _AUTOINC);

        if(((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) != 0x00) &&
           (PDATA_WORD(2) != 0x00) && (PDATA_WORD(3) != 0x00) && (PDATA_WORD(4) != 0x00) && (PDATA_WORD(5) != 0x00) &&
           (PDATA_WORD(2) > PDATA_WORD(4)) && (PDATA_WORD(3) > PDATA_WORD(5)))
        {
            bMSACheckResult = _TRUE;

            break;
        }
    }while(ScalerDpRx1ChangeSrambleSeed() == _TRUE);

#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
    bMSACheckResult = ScalerDpRx1VbiosAssrCheck(bMSACheckResult);
#endif

    return bMSACheckResult;
}

#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : VBIOS ASSR Detect
// Input Value  : bMSACheckResult
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpRx1VbiosAssrCheck(bit bMSACheckResult)
{
    SET_DP_RX1_AUX_MANUAL_MODE();

#if(_DP_MST_SUPPORT == _ON)
    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
       (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00) &&
       (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) != _BIT1))
#else
    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
       (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
#endif
    {
        if(bMSACheckResult == _TRUE)
        {
            if(ScalerGetBit(PB0_07_SCRAMBLE_CTRL, _BIT4) == _BIT4)
            {
                ScalerDpRx1SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, _BIT0);
            }
            else
            {
                ScalerDpRx1SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, 0x00);
            }
        }
        else
        {
            // Set Scramble Seed = Default 0xFFFF
            ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);

            ScalerDpRx1SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, 0x00);
        }
    }
    else
    {
        bMSACheckResult = _FALSE;
    }

    SET_DP_RX1_AUX_AUTO_MODE();

    return bMSACheckResult;
}
#endif

//--------------------------------------------------
// Description  : Change Dp Scramble Seed
// Input Value  : None
// Output Value : False --> Change Scrmable Seed Finish
//--------------------------------------------------
bit ScalerDpRx1ChangeSrambleSeed(void)
{
#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)

    if(ScalerGetBit(PB0_07_SCRAMBLE_CTRL, _BIT4) == 0x00)
    {
        // Try Scramble Seed = 0xFFFE
        ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);

        return _TRUE;
    }
    else
#endif
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDpRx1InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg)
{
    DWORD ulLinkClk = 0;
    WORD usTempVTotal = *pusVTotal;
    WORD usHTotalCount = 0;

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _OFF)
    WORD usVsyncWidth = 0;
    WORD usVstart = 0;
    WORD usVactive = 0;
#endif

    // Set Vfront Porch
    SET_DP_RX1_VFRONT_PORCH(_DP_VSYNC_FRONT_PORCH);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        return _FALSE;
    }
#endif

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Field inverse disable and Clr Fake Interlace Flag
    ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));
#else
    ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), _BIT0);
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        // Restore DP Info
        PDATA_DWORD(1) = g_stDpRx1LinkInfo.ulVBsToBsCountN;
        PDATA_DWORD(2) = g_stDpRx1LinkInfo.ulVBsToBsCountN1;
        pData[1] = ((BYTE) g_stDpRx1LinkInfo.bInterlaceFieldN) << 1;
        pData[2] = ((BYTE) g_stDpRx1LinkInfo.bInterlaceFieldN1) << 1;
    }
    else
#endif
    {
        // =========== Link Clock Measure Start ===========
        PDATA_WORD(0) = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE0, _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_2000_CYCLE);

        if(PDATA_WORD(0) == 0)
        {
            if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR3)
            {
                PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR3;
            }
            else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
            {
                PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR2;
            }
            else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
            {
                PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR;
            }
            else // Both Default && _DP_LINK_RBR Case
            {
                PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_RBR;
            }
        }

        PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

        // Link Clk in KHz
        ulLinkClk = (PDATA_DWORD(0) / 1000);

        DebugMessageRx1("Current Link Clk", ulLinkClk);
        // =========== Link Clock Measure End ===========

        // =========== Continue Measure Two Frame Start ===========
        // Start to Measure Vertical BS to BS Counter by GDI Clock
        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
        {
            return _FALSE;
        }

        // Pop up The result
        SET_DP_RX1_MEASURE_POP_UP();

        // Get Measure Result
        ScalerRead(PB8_58_MN_MEAS_CTRL, 3, &pData[5], _AUTOINC);

        // Delay 2ms To Get VBID
        ScalerTimerDelayXms(2);

        // Get VBID
        ScalerRead(PB9_01_DP_VBID, 1, &pData[1], _NON_AUTOINC);

        // Delay 1 frame
        ScalerTimerDelayXms((((PDATA_DWORD(1) & 0x001FFFFF) / (_GDI_CLK_KHZ)) + 2));

        // Pop up Measure Result
        SET_DP_RX1_MEASURE_POP_UP();

        // Get Measure Result
        ScalerRead(PB8_58_MN_MEAS_CTRL, 3, &pData[9], _AUTOINC);

        // Get Measure Htotal Counts
        ScalerRead(PB8_5B_MN_MEAS_HLN_M, 2, &pData[12], _AUTOINC);

        // Get VBID
        ScalerRead(PB9_01_DP_VBID, 1, &pData[2], _NON_AUTOINC);

        PDATA_DWORD(1) = (PDATA_DWORD(1) & 0x001FFFFF);
        PDATA_DWORD(2) = (PDATA_DWORD(2) & 0x001FFFFF);

        // Disable Measure Block
        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
        // =========== Continue Measure Two Frame End ===========

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
        // Backup DP Info
        g_stDpRx1LinkInfo.ulVBsToBsCountN = PDATA_DWORD(1);
        g_stDpRx1LinkInfo.ulVBsToBsCountN1 = PDATA_DWORD(2);
        g_stDpRx1LinkInfo.bInterlaceFieldN = (bit)(pData[1] & _BIT1);
        g_stDpRx1LinkInfo.bInterlaceFieldN1 = (bit)(pData[2] & _BIT1);
#endif
    }

    // Convert HTotal Count from 1/2 Link Clk to GDI Clk
    usHTotalCount = ((DWORD)PDATA_WORD(6) * _GDI_CLK_KHZ * 2 + (ulLinkClk >> 1)) / ulLinkClk;

    DebugMessageRx1("HTotal Count", usHTotalCount);

    // if VTotal Difference > 1/2 HTotal
    if((ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))) > (usHTotalCount / 2))
    {
        if(PDATA_DWORD(1) < PDATA_DWORD(2))
        {
            usTempVTotal = ((PDATA_DWORD(1) + (usHTotalCount >> 1)) / usHTotalCount);
        }
        else
        {
            usTempVTotal = ((PDATA_DWORD(2) + (usHTotalCount >> 1)) / usHTotalCount);
        }

        *pucOddFlg = _TRUE;
    }
    else
    {
        *pucOddFlg = _FALSE;
    }

    DebugMessageRx1("####Calculated usVTotal####", usTempVTotal);

    DebugMessageRx1("7. DelayTime", (((PDATA_DWORD(1) & 0x000FFFFF) / (_GDI_CLK_KHZ)) + 2));
    DebugMessageRx1("7. Frame[N] VBS2BS Counter", PDATA_DWORD(1));
    DebugMessageRx1("7. Frame[N + 1] VBS2BS Counter", PDATA_DWORD(2));
    DebugMessageRx1("7. Frame diff ABS", (ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))));

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Check N and N+1 Frame Vs2Vs Count
    if((*pucOddFlg) == _TRUE)
    {
        // Enable DP Interlace
        ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

        // Enable Field Sync by BE
        ScalerSetBit(PB8_F1_DP_RSV1, ~_BIT0, _BIT0);

        // HW Check Interlace
        if(ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, _BIT5) == _BIT5)
        {
            // Field reference HW
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);
        }
        else
        {
            // Field reference VBID
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);
        }

        // Set Vtt odd fw mode
        SET_DP_RX1_INTERLACE_VTT_FW_MODE(_ODD);

        *pusVTotal = usTempVTotal;

        return _TRUE;
    }
    else
    {
        // Check VBID Field Toggle and VBID Interlace Info
        if(((pData[1] & _BIT1) != (pData[2] & _BIT1)) && (ScalerGetBit(PB9_01_DP_VBID, _BIT2) == _BIT2))
        {
            // Enable DP Interlace
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

            // Field reference VBID
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

            // Enable Field Sync by BE
            ScalerSetBit(PB8_F1_DP_RSV1, ~_BIT0, _BIT0);

            // Set Vtt Even fw mode
            SET_DP_RX1_INTERLACE_VTT_FW_MODE(_EVEN);

            *pusVTotal = usTempVTotal;

            return _TRUE;
        }

        // Enable DP Progressive Mode
        ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), 0x00);

        // Field reference VBID
        ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

        // Enable Field Sync by VBID
        ScalerSetBit(PB8_F1_DP_RSV1, ~_BIT0, 0x00);

        // Set Vtt Even fw mode
        SET_DP_RX1_INTERLACE_VTT_FW_MODE(_EVEN);

        return _FALSE;
    }
#else
    if(ScalerGetBit(PB9_01_DP_VBID, _BIT2) == _BIT2) // Interlace
    {
        // Enable DP Interlace
        ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

        if((*pucOddFlg) == _FALSE)
        {
            // Disable DP Interlace
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), 0x00);
        }

        // Get VSW
        usVsyncWidth = ((WORD)ScalerGetByte(PB9_18_MSA_VSW_0) << 8) | ScalerGetByte(PB9_19_MSA_VSW_1);
        usVsyncWidth &= 0x7FFF;

        // Get VStart
        usVstart = ((WORD)ScalerGetByte(PB9_14_MSA_VST_0) << 8) | ScalerGetByte(PB9_15_MSA_VST_1);

        // usVbackporch = usVstart - Fixed V-Sync Pulse Width, usVbackporch > usVsyncWidth + 2 lines, here 2 lines is for V-Sync Falling edge to DEN Rising Edge distance margion
        if(((pData[1] & _BIT1) != (pData[2] & _BIT1)) && (usVstart > (usVsyncWidth + _DP_VSYNC_WIDTH + 2)))
        {
            // Field Information reference to VBID
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

            // Get Vactive
            usVactive = ((WORD)ScalerGetByte(PB9_16_MSA_VHT_0) << 8) | ScalerGetByte(PB9_17_MSA_VHT_1);

            // Set Front Porch = VTotal - Active height - MSA V Start + V Sync Pulse Width
            SET_DP_RX1_VFRONT_PORCH(usTempVTotal - usVactive - usVstart + usVsyncWidth);

            if((ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, _BIT0) == 0x00) &&
               ((((pData[1] & _BIT1) == _BIT1) && ((pData[2] & _BIT1) == 0x00) && (PDATA_DWORD(1) < PDATA_DWORD(2))) ||
                (((pData[1] & _BIT1) == 0x00) && ((pData[2] & _BIT1) == _BIT1) && (PDATA_DWORD(1) > PDATA_DWORD(2)))))
            {
                // Field inverse enable
                ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), _BIT4);
            }
        }
        else
        {
            // Field reference HW
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);
        }

        *pusVTotal = usTempVTotal;

        return _TRUE;
    }
    else if((ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))) > (usHTotalCount / 2))
    {
        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        if(ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, _BIT0) == _BIT0)
        {
            DebugMessageRx1("Fake Interlace", 0);
            *pucOddFlg = _FALSE;
        }
        else
        {
            // Enable interlace mode, field reference HW
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), (_BIT7 | _BIT6));

            *pusVTotal = usTempVTotal;

            return _TRUE;
        }
    }

    // Disable DP Interlace
    ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), 0x00);

    return _FALSE;
#endif
}

//--------------------------------------------------
// Description  : DP Get Video Info
// Input Value  : None
// Output Value : TRUE --> Get successfully
//--------------------------------------------------
bit ScalerDpRx1GetVideoInfo(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    CLR_DP_RX1_VSC_SDP_COLOR_MODE();

    // Check MISC1[6]
    if((ScalerGetBit(PB9_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        SET_DP_RX1_VSC_SDP_COLOR_MODE();

#if(_HW_DP_VSC_SDP_REG_SUPPORT == _ON)

        // Read DB16~18 --> pData[0:2]
        ScalerRead(PB9_46_VSC15, 3, pData, _AUTOINC);
#else
        // Delay 2 frames for SRAM ready (worst case)
        ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX * 2);

        SET_DP_RX1_RSV1_DETECTING();

        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_RSV1_PACKET_DETECT);

        // Read DB16~18 --> pData[0:2]
        ScalerGetDataPortByte(PB9_30_DP_INFO_FM_ADR, _DP_INFO_RSV1_DB16, 3, pData, _AUTOINC);
#endif
        // Set ColorimetryExtPreValue & QuantizationPreValue & ColorDepthPreValue
        SET_DP_RX1_COLORIMETRY_EXT_PREVALUE(pData[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        SET_DP_RX1_QUANTIZATION_PREVALUE((pData[1] & _BIT7) >> 7);
        SET_DP_RX1_COLOR_DEPTH_PREVALUE(pData[1] & (_BIT2 | _BIT1 | _BIT0));
        SET_DP_RX1_COLOR_SPACE_PREVALUE(pData[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        DebugMessageRx1("VSC DB16", pData[0]);
        DebugMessageRx1("VSC DB17", pData[1]);
    }
    else
#endif
    {
        // Get MISC Info
        pData[0] = ScalerGetByte(PB9_02_MN_STRM_ATTR_MISC);

        // Set ColorimetryPreValue & QuantizationPreValue
        SET_DP_RX1_COLORIMETRY_PREVALUE((pData[0] & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
        SET_DP_RX1_QUANTIZATION_PREVALUE((pData[0] & _BIT3) >> 3);
        SET_DP_RX1_COLOR_DEPTH_PREVALUE((pData[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
        SET_DP_RX1_COLOR_SPACE_PREVALUE((ScalerGetBit(PB9_03_MN_STRM_ATTR_MISC1, _BIT7)) | (pData[0] & (_BIT2 | _BIT1)));
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetColorInfo(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    if(GET_DP_RX1_VSC_SDP_COLOR_MODE() == _TRUE)
    {
        // Use VSC SDP
        // Set Color Space Macro
        switch(GET_DP_RX1_COLOR_SPACE_PREVALUE())
        {
            case _VSC_COLOR_SPACE_0:
                SET_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;

            case _VSC_COLOR_SPACE_1:
                SET_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _VSC_COLOR_SPACE_2:
                SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _VSC_COLOR_SPACE_3:
                SET_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
                break;

            case _VSC_COLOR_SPACE_4:
                SET_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case _VSC_COLOR_SPACE_5:
                SET_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }

        // Set Colorimetry Ext
        ScalerDpRx1ColorimetryExtSetting();
    }
    else
#endif
    {
        switch(GET_DP_RX1_COLOR_SPACE_PREVALUE())
        {
            case _BIT1:
                SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _BIT2:
                SET_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _BIT7:
                SET_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case (_BIT7 | _BIT1):
                SET_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }

        // Set Colorimetry
        ScalerDpRx1ColorimetrySetting();
    }

    // Get Color Depth
    if(GET_COLOR_SPACE() != _COLOR_SPACE_RAW)
    {
        switch(GET_DP_RX1_COLOR_DEPTH_PREVALUE())
        {
            case 0:
                SET_COLOR_DEPTH(_COLOR_DEPTH_6_BITS);
                break;

            case 1:
                SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);
                break;

            case 2:
                SET_COLOR_DEPTH(_COLOR_DEPTH_10_BITS);
                break;

            case 3:
                SET_COLOR_DEPTH(_COLOR_DEPTH_12_BITS);
                break;

            case 4:
                SET_COLOR_DEPTH(_COLOR_DEPTH_16_BITS);
                break;

            default:
                SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);
                break;
        }
    }
    else
    {
        switch(GET_DP_RX1_COLOR_DEPTH_PREVALUE())
        {
            case 1:
                SET_COLOR_DEPTH(_COLOR_DEPTH_6_BITS);
                break;

            case 2:
                SET_COLOR_DEPTH(_COLOR_DEPTH_7_BITS);
                break;

            case 3:
                SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);
                break;

            case 4:
                SET_COLOR_DEPTH(_COLOR_DEPTH_10_BITS);
                break;

            case 5:
                SET_COLOR_DEPTH(_COLOR_DEPTH_12_BITS);
                break;

            case 6:
                SET_COLOR_DEPTH(_COLOR_DEPTH_14_BITS);
                break;

            case 7:
                SET_COLOR_DEPTH(_COLOR_DEPTH_16_BITS);
                break;

            default:
                SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);
                break;
        }
    }

    // Set Porch Color
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420))
    {
        if(GET_DP_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_LIMIT)
        {
            SET_DP_RX1_PORCH_COLOR_YCC_LIMIT();
        }
        else if(GET_DP_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_DP_RX1_PORCH_COLOR_YCC_FULL();
        }
    }
    else
    {
        SET_DP_RX1_PORCH_COLOR_RGB();
    }

    // Set Quantization Range
    ScalerDpRx1QuantizationSetting();
}

//--------------------------------------------------
// Description  : DP Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1VideoSetting(void)
{
    // Set Color Space for Display Format Gen.
    switch(GET_COLOR_SPACE())
    {
        case _COLOR_SPACE_RGB:
            DebugMessageRx1("_COLOR_SPACE_RGB", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_YCBCR444:
            DebugMessageRx1("_COLOR_SPACE_YCBCR444", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), _BIT4);
            break;

        case _COLOR_SPACE_YCBCR422:
            DebugMessageRx1("_COLOR_SPACE_YCBCR422", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), _BIT3);
            break;

        case _COLOR_SPACE_YCBCR420:
            DebugMessageRx1("_COLOR_SPACE_YCBCR420", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_Y_ONLY:
            DebugMessageRx1("_COLOR_SPACE_Y_ONLY", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            break;

        case _COLOR_SPACE_RAW:
            DebugMessageRx1("_COLOR_SPACE_RAW", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        default:
            // RGB
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;
    }

    // Set Color Depth for Display Format Gen.
    ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), GET_DP_RX1_COLOR_DEPTH_PREVALUE());
    DebugMessageRx1("_COLOR_DEPTH", GET_COLOR_DEPTH());
}


//--------------------------------------------------
// Description  : DP Rx1 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ColorimetrySetting(void)
{
    BYTE ucColorimetryValue = (GET_DP_RX1_COLORIMETRY_PREVALUE() << 1);

    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ucColorimetryValue & (_BIT4 | _BIT3))
        {
            case 0:
                SET_COLORIMETRY(_COLORIMETRY_YCC_XVYCC601);
                DebugMessageRx1("_COLORIMETRY_YCC_XVYCC601", 0);
                break;

            case _BIT3:
                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT601);
                DebugMessageRx1("_COLORIMETRY_YCC_ITUR_BT601", 0);
                break;

            case _BIT4:
                SET_COLORIMETRY(_COLORIMETRY_YCC_XVYCC709);
                DebugMessageRx1("_COLORIMETRY_YCC_XVYCC709", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT709);
                DebugMessageRx1("_COLORIMETRY_YCC_ITUR_BT709", 0);
                break;

            default:
                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(ucColorimetryValue & (_BIT4 | _BIT3 | _BIT2 | _BIT1))
        {
            case 0:
                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SRGB_VESA", 0);
                break;

            case _BIT3:
                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SRGB_CEA", 0);
                break;

            case (_BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_XRRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_XRRGB", 0);
                break;

            case (_BIT4 | _BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_SCRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SCRGB", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_COLORIMETRY(_COLORIMETRY_RGB_ADOBERGB);
                DebugMessageRx1("_COLORIMETRY_RGB_ADOBERGB", 0);
                break;

            case (_BIT3 | _BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_DCI_P3);
                DebugMessageRx1("_COLORIMETRY_RGB_DCI_P3", 0);
                break;

            case (_BIT4 | _BIT3 | _BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_COLOR_PROFILE);
                DebugMessageRx1("_COLORIMETRY_RGB_COLOR_PROFILE", 0);
                break;

            default:
                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SRGB", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
    {
        SET_COLORIMETRY(_COLORIMETRY_Y_ONLY);
        DebugMessageRx1("_COLORIMETRY_Y_ONLY", 0);
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        SET_COLORIMETRY(_COLORIMETRY_RAW);
        DebugMessageRx1("_COLORIMETRY_RAW", 0);
    }
}

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx1 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ColorimetryExtSetting(void)
{
    SET_COLORIMETRY(_COLORIMETRY_EXT);

    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(GET_DP_RX1_COLORIMETRY_EXT_PREVALUE())
        {
            case _VSC_COLORIMETRY_0:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT601", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT709);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT709", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_XVYCC601", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC709);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_XVYCC709", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_SYCC601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_SYCC601", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ADOBEYCC601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ADOBEYCC601", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL", 0);
                break;

            case _VSC_COLORIMETRY_7:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL", 0);
                break;

            default:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);
                DebugMessageRx1("_COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(GET_DP_RX1_COLORIMETRY_EXT_PREVALUE())
        {
            case _VSC_COLORIMETRY_0:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_SRGB", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_XRRGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_XRRGB", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SCRGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_SCRGB", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ADOBERGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_ADOBERGB", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_DCI_P3);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_DCI_P3", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ITUR_BT2020);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_ITUR_BT2020", 0);
                break;

            default:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);
                DebugMessageRx1("_COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
    {
        SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_Y_ONLY_DICOM_PART14);
        DebugMessageRx1("_COLORIMETRY_EXT_Y_ONLY_DICOM_PART14", 0);
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE);
        DebugMessageRx1("_COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE", 0);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Rx1 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1QuantizationSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        if(GET_DP_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);
            DebugMessageRx1("_YCC_QUANTIZATION_FULL_RANGE", 0);
        }
        else
        {
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);
            DebugMessageRx1("_YCC_QUANTIZATION_LIMIT_RANGE", 0);
        }

        SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);
    }
    else if(GET_COLORIMETRY() == _COLORIMETRY_RGB_ADOBERGB) // Special case for AdobeRGB
    {
        SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);
        SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);
    }
    else
    {
        if(GET_DP_RX1_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);
            DebugMessageRx1("_RGB_QUANTIZATION_FULL_RANGE", 0);
        }
        else
        {
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_LIMIT_RANGE);
            DebugMessageRx1("_RGB_QUANTIZATION_LIMIT_RANGE", 0);
        }

        SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);
    }
}

//--------------------------------------------------
// Description  : Check DP Misc Information
// Input Value  : None
// Output Value : True --> DP Misc Check Ok
//--------------------------------------------------
bit ScalerDpRx1MiscCheck(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    // Check MISC1[6]
    if((ScalerGetBit(PB9_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        return ScalerDpRx1VscCheck();
    }
    else
#endif
    {
        // Get MISC Info
        BYTE ucMisc0 = ScalerGetByte(PB9_02_MN_STRM_ATTR_MISC);
        BYTE ucColorSpaceValue = (ScalerGetBit(PB9_03_MN_STRM_ATTR_MISC1, _BIT7)) | (ucMisc0 & (_BIT2 | _BIT1));

        // Color Space Check
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)

        // Color format info source change from VSC --> MISC
        if(GET_DP_RX1_VSC_SDP_COLOR_MODE() == _TRUE)
        {
            switch(ucColorSpaceValue)
            {
                case _BIT1:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_YCBCR422", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT2:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR444)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_YCBCR444", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT7:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_Y_ONLY)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_Y_ONLY", 0);
                        return _FALSE;
                    }
                    break;

                case (_BIT7 | _BIT1):
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_RAW)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_RAW", 0);
                        return _FALSE;
                    }
                    break;

                default:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_RGB", 0);
                        return _FALSE;
                    }
                    break;
            }
        }
        else
#endif
        {
            if(ucColorSpaceValue != GET_DP_RX1_COLOR_SPACE_PREVALUE())
            {
                DebugMessageRx1("Misc change: Color Space", 0);
                return _FALSE;
            }
        }

        // Color Depth Check
        if((((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5) != GET_DP_RX1_COLOR_DEPTH_PREVALUE())
        {
            DebugMessageRx1("Misc change: Color Depth", (((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5));
            return _FALSE;
        }

        // Colorimetry Check
        if(GET_COLORIMETRY() != _COLORIMETRY_EXT)
        {
            if(((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1) != GET_DP_RX1_COLORIMETRY_PREVALUE())
            {
                DebugMessageRx1("Misc change: Colorimetry", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_RX1_COLORIMETRY_PREVALUE((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
                    ScalerDpRx1ColorimetrySetting();
                    SET_DP_RX1_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            DebugMessageRx1("Misc change: Ext Colorimetry", 0);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX1_COLORIMETRY_PREVALUE((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
                ScalerDpRx1ColorimetrySetting();
                SET_DP_RX1_COLORIMETRY_CHANGED();
            }
        }

        // Dynamic Range Check
#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
        if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422))
        {
            if(((ucMisc0 & _BIT3) >> 3) != GET_DP_RX1_QUANTIZATION_PREVALUE())
            {
                DebugMessageRx1("Misc change: Dynamic Range", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_RX1_QUANTIZATION_PREVALUE((ucMisc0 & _BIT3) >> 3);
                    ScalerDpRx1QuantizationSetting();
                    SET_DP_RX1_QUANTIZATION_CHANGED();
                }
            }
        }
        else
#endif
        {
#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
            if(((ucMisc0 & _BIT3) >> 3) != GET_DP_RX1_QUANTIZATION_PREVALUE())
            {
                DebugMessageRx1("Misc change: Dynamic Range", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_RX1_QUANTIZATION_PREVALUE((ucMisc0 & _BIT3) >> 3);
                    ScalerDpRx1QuantizationSetting();
                    SET_DP_RX1_QUANTIZATION_CHANGED();
                }
            }
#endif
        }

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() == _FALSE)
#endif
        {
            // Get HSW
            ScalerRead(PB9_0E_MSA_HSW_0, 2, &pData[0], _AUTOINC);

            // Get VSW
            ScalerRead(PB9_18_MSA_VSW_0, 2, &pData[2], _AUTOINC);

            if(((PDATA_WORD(0) & 0x7FFF) == 0x00) || ((PDATA_WORD(1) & 0x7FFF) == 0x00))
            {
                return _FALSE;
            }
        }

        return _TRUE;
    }
}

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DP VSC SDP Information
// Input Value  : None
// Output Value : True --> DP VSC SDP Check Ok
//--------------------------------------------------
bit ScalerDpRx1VscCheck(void)
{
    BYTE pucVscColorFormat[3];

    memset(pucVscColorFormat, 0, sizeof(pucVscColorFormat));

#if(_HW_DP_VSC_SDP_REG_SUPPORT == _ON)

    // Read DB16~18 --> pucVscColorFormat[0:2]
    ScalerRead(PB9_46_VSC15, 3, pucVscColorFormat, _AUTOINC);
#else
    if(GET_DP_RX1_RSV1_DETECTING() == _FALSE)
    {
        // Read DB16~18 --> pucVscColorFormat[0:2]
        ScalerGetDataPortByte(PB9_30_DP_INFO_FM_ADR, _DP_INFO_RSV1_DB16, 3, pucVscColorFormat, _AUTOINC);

        SET_DP_RX1_RSV1_DETECTING();

        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_RSV1_PACKET_DETECT);
    }
    else
    {
        return _TRUE;
    }
#endif

    // Color Space Check
    if(GET_DP_RX1_VSC_SDP_COLOR_MODE() == _FALSE)
    {
        // Color format info source change from MISC --> VSC
        switch(pucVscColorFormat[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4))
        {
            case _VSC_COLOR_SPACE_0:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_RGB", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_1:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR444)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_YCBCR444", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_2:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_YCBCR422", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_3:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR420)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_YCBCR420", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_4:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_Y_ONLY)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_Y_ONLY", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_5:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_RAW)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_RAW", 0);
                    return _FALSE;
                }

                break;

            default:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_RGB", 0);
                    return _FALSE;
                }

                break;
        }
    }
    else
    {
        if((pucVscColorFormat[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) != GET_DP_RX1_COLOR_SPACE_PREVALUE())
        {
            DebugMessageRx1("VSC change: Color Space", 0);
            return _FALSE;
        }
    }

    // Color Depth Check
    if((pucVscColorFormat[1] & (_BIT2 | _BIT1 | _BIT0)) != GET_DP_RX1_COLOR_DEPTH_PREVALUE())
    {
        DebugMessageRx1("VSC change: Color Depth", 0);
        return _FALSE;
    }

    // Colorimetry Ext Check
    if(GET_COLORIMETRY() == _COLORIMETRY_EXT)
    {
        if((pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX1_COLORIMETRY_EXT_PREVALUE())
        {
            DebugMessageRx1("VSC change: Colorimetry Ext", 0);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX1_COLORIMETRY_EXT_PREVALUE(pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerDpRx1ColorimetryExtSetting();
                SET_DP_RX1_COLORIMETRY_EXT_CHANGED();
            }
        }
    }
    else
    {
        DebugMessageRx1("VSC change: Colorimetry Ext", 0);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
        {
            return _FALSE;
        }
        else
        {
            SET_DP_RX1_COLORIMETRY_EXT_PREVALUE(pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerDpRx1ColorimetryExtSetting();
            SET_DP_RX1_COLORIMETRY_EXT_CHANGED();
        }
    }

    // Dynamic Range Check
#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420))
    {
        if(((pucVscColorFormat[1] & _BIT7) >> 7) != GET_DP_RX1_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx1("VSC change: Dynamic Range", ((pucVscColorFormat[1] & _BIT7) >> 7));

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX1_QUANTIZATION_PREVALUE((pucVscColorFormat[1] & _BIT7) >> 7);
                ScalerDpRx1QuantizationSetting();
                SET_DP_RX1_QUANTIZATION_CHANGED();
            }
        }
    }
    else
#endif
    {
#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
        if(((pucVscColorFormat[1] & _BIT7) >> 7) != GET_DP_RX1_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx1("VSC change: Dynamic Range", ((pucVscColorFormat[1] & _BIT7) >> 7));

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX1_QUANTIZATION_PREVALUE((pucVscColorFormat[1] & _BIT7) >> 7);
                ScalerDpRx1QuantizationSetting();
                SET_DP_RX1_QUANTIZATION_CHANGED();
            }
        }
#endif
    }

    return _TRUE;
}

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
//--------------------------------------------------
// Description  : DP Rx1 VSC Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1RSV1PacketDetectEvent(void)
{
    CLR_DP_RX1_RSV1_DETECTING();
}

//--------------------------------------------------
// Description  : Set DP Rx1 RSV1 infoframe type to VSC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetInitialRSV1InfoType(void)
{
    // Set Packet Type of RSV1 to VSC
    ScalerSetByte(PB9_2D_DP_INFO_FM_RSV1, _DP_SDP_TYPE_VSC);

    CLR_DP_RX1_RSV1_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_RSV1_PACKET_DETECT);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
    ScalerSetByte(PBC_54_DP_INFO_FM_RSV1, _DP_SDP_TYPE_VSC);

    CLR_DP_RX1_MST2SST_RSV1_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_MST2SST_RSV1_PACKET_DETECT);
#endif
}
#endif
#endif

//--------------------------------------------------
// Description  : HDCP Unplug Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPUnplugReset(void)
{
    ScalerDpRx1HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpRx1Hdcp2ResetProc();
#endif

    // Clear CPIRQ flag while unplug
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) & ~_BIT2));
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx1 Mst Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstReset(void)
{
    SET_DP_RX1_AUX_MANUAL_MODE();

    // Reset GUID
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x00, 0x00, (0x30 + pData[0]), 0x00);
    }

    // Disable 0x111/1C2 IRQ
    ScalerSetBit(PBA_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);

    // Clear 0x111
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x11, 0x00);

    // Clear 0x1C0 ~ 0x1C2
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0xC0, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0xC1, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0xC2, 0x00);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
    if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
    {
        // Clear 0x111 IRQ Flag
        ScalerSetBit(PBA_B3_AUX_SPECIAL_IRQ_FLAG, ~_BIT7, _BIT7);

        // Enable 0x111 IRQ
        ScalerSetBit(PBA_B2_AUX_SPECIAL_IRQ_EN, ~_BIT7, _BIT7);

        // Enable 0x01000 write IRQ
        SET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE();
    }
#else

    // Clear 0x111/1C2 IRQ Flag
    ScalerSetBit(PBA_B3_AUX_SPECIAL_IRQ_FLAG, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

    // Enable 0x111/1C2 IRQ
    ScalerSetBit(PBA_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));
#endif

    SET_DP_RX1_AUX_AUTO_MODE();

    // Disable MST
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT7, 0x00);

    // Disable Read 2C0 INT
    CLR_REG_DP_RX_2C0_IRQ();

    // Clear 0x2C0
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0xC0, 0x00);

    // Clear Payload ID Table (0x2C1 ~ 0x2FF)
    ScalerSetBit(PBA_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, _BIT6);
    ScalerSetBit(PBA_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, 0x00);

    // Reset ST1 ~ ST5
    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        // Reset Start Position
        ScalerSetByte(PB8_03_STHD_CTRL_2 + (pData[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte(PB8_04_STHD_CTRL_3 + (pData[0] << 1), 0x00);
    }

    // Reset Daisy Chain ST3 ~ ST5
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        // Reset Start Position
        ScalerSetByte(RET_REG_ADDR_DP_RX1_DAIZY_ST3_START() + (pData[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte(RET_REG_ADDR_DP_RX1_DAIZY_ST3_END() + (pData[0] << 1), 0x00);
    }

    if((GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH() == 0x01) || (GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH() == 0x01))
    {
        SET_DP_RX1_AUX_COMMAND_NO_REPLY();
    }

    // Clr Buf0/Buf1 DownRequest MSG Finish Flag
    CLR_REG_DP_RX_DOWN_REQUEST_MSG_FINISH();

    // Clr Buf0 / Buf1
    CLR_REG_DP_RX_DOWN_REQUEST_BUF0_BUF1();

    // Clr Buf0/Buf1 MSG Error Flag
    CLR_REG_DP_RX_DOWN_REQUEST_MSG_ERROR();

    // Disable MST Related IRQ
    CLR_REG_DP_RX_DOWN_REPLY_UP_REQUEST_READY_BIT_IRQ();

    // Clr 1000h Has Been Write
    CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();

    // Clr 1200h Has Been Write
    CLR_REG_DP_RX_UP_REPLY_ADDR_WRITTEN();

    // Disable Rx Igrone Error
    ScalerSetBit(PBA_D1_DP_IIC_SET, ~_BIT3, 0x00);

    // Message Upstream Disable
    CLR_REG_DP_RX_UPSTREAM_REPLY();

    // Reset Rx MSG Block
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT6, 0x00);

    if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        // Clear Flag
        CLR_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH();
        CLR_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH();

        // Clear BUF0
        CLR_REG_DP_RX_DOWN_REQUEST_BUF0();
        CLR_REG_DP_RX_DOWN_REQUEST_BUF1();

        // Enable DownRequest Buf0 / Buf1 Receive Capability
        SET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE();
        SET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE();

        // Clear Flag
        CLR_REG_DP_RX_UP_REPLY_BUF0_MSG_FINISH();
        CLR_REG_DP_RX_UP_REPLY_BUF1_MSG_FINISH();

        // Clear BUF0
        CLR_REG_DP_RX_UP_REPLY_BUF0();
        CLR_REG_DP_RX_UP_REPLY_BUF1();

        // Enable UpReply Buf0 / Buf1 Receive Capability
        SET_REG_DP_RX_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE();
        SET_REG_DP_RX_UP_REPLY_BUF1_MSG_RECEIVE_ENABLE();
    }
}

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx1 Mst Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstReset_EXINT0(void) using 1
{
    // Reset GUID
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x00, (0x30 + pData_EXINT[0]), 0x00);
    }

    // Disable 0x111/1C2 IRQ
    ScalerSetBit_EXINT(PBA_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);

    // Clear 0x111
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x11, 0x00);

    // Clear 0x1C0 ~ 0x1C2
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0xC0, 0x00);
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0xC1, 0x00);
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0xC2, 0x00);

    if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x21, _BIT0) == _BIT0)
    {
        // Clear 0x111 IRQ Flag
        ScalerSetBit_EXINT(PBA_B3_AUX_SPECIAL_IRQ_FLAG, ~_BIT7, _BIT7);

        // Enable 0x111 IRQ
        ScalerSetBit_EXINT(PBA_B2_AUX_SPECIAL_IRQ_EN, ~_BIT7, _BIT7);

        // Enable 0x01000 write IRQ
        SET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE_EXINT();
    }

    // Disable MST
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT7, 0x00);

    // Disable Read 2C0 INT
    CLR_REG_DP_RX_2C0_IRQ_EXINT();

    // Clear 0x2C0
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0xC0, 0x00);

    // Clear Payload ID Table (0x2C1 ~ 0x2FF)
    ScalerSetBit_EXINT(PBA_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(PBA_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, 0x00);

    // Reset ST1 ~ ST5
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 5; pData_EXINT[0]++)
    {
        // Reset Start Position
        ScalerSetByte_EXINT(PB8_03_STHD_CTRL_2 + (pData_EXINT[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte_EXINT(PB8_04_STHD_CTRL_3 + (pData_EXINT[0] << 1), 0x00);
    }

    // Reset Daisy Chain ST3 ~ ST5
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 3; pData_EXINT[0]++)
    {
        // Reset Start Position
        ScalerSetByte_EXINT(RET_REG_ADDR_DP_RX1_DAIZY_ST3_START() + (pData_EXINT[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte_EXINT(RET_REG_ADDR_DP_RX1_DAIZY_ST3_END() + (pData_EXINT[0] << 1), 0x00);
    }

    if((GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH_EXINT() == 0x01) || (GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH_EXINT() == 0x01))
    {
        SET_DP_RX1_AUX_COMMAND_NO_REPLY();
    }

    // Clr Buf0/Buf1 DownRequest MSG Finish Flag
    CLR_REG_DP_RX_DOWN_REQUEST_MSG_FINISH_EXINT();

    // Clr Buf0 / Buf1
    CLR_REG_DP_RX_DOWN_REQUEST_BUF0_BUF1_EXINT();

    // Clr Buf0/Buf1 MSG Error Flag
    CLR_REG_DP_RX_DOWN_REQUEST_MSG_ERROR_EXINT();

    // Disable MST Related IRQ
    CLR_REG_DP_RX_DOWN_REPLY_UP_REQUEST_READY_BIT_IRQ_EXINT();

    // Clr 1000h Has Been Write
    CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN_EXINT();

    // Clr 1200h Has Been Write
    CLR_REG_DP_RX_UP_REPLY_ADDR_WRITTEN_EXINT();

    // Disable Rx Igrone Error
    ScalerSetBit_EXINT(PBA_D1_DP_IIC_SET, ~_BIT3, 0x00);

    // Message Upstream Disable
    CLR_REG_DP_RX_UPSTREAM_REPLY_EXINT();

    // Reset Rx MSG Block
    ScalerSetBit_EXINT(PBA_C0_DPCD_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(PBA_C0_DPCD_CTRL, ~_BIT6, 0x00);

    if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        // Clear Flag
        CLR_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH_EXINT();
        CLR_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH_EXINT();

        // Clear BUF0
        CLR_REG_DP_RX_DOWN_REQUEST_BUF0_EXINT();
        CLR_REG_DP_RX_DOWN_REQUEST_BUF1_EXINT();

        // Enable DownRequest Buf0 / Buf1 Receive Capability
        SET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE_EXINT();
        SET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE_EXINT();

        // Clear Flag
        CLR_REG_DP_RX_UP_REPLY_BUF0_MSG_FINISH_EXINT();
        CLR_REG_DP_RX_UP_REPLY_BUF1_MSG_FINISH_EXINT();

        // Clear BUF0
        CLR_REG_DP_RX_UP_REPLY_BUF0_EXINT();
        CLR_REG_DP_RX_UP_REPLY_BUF1_EXINT();

        // Enable UpReply Buf0 / Buf1 Receive Capability
        SET_REG_DP_RX_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE_EXINT();
        SET_REG_DP_RX_UP_REPLY_BUF1_MSG_RECEIVE_ENABLE_EXINT();
    }
}
#endif

//--------------------------------------------------
// Description  : Dp Rx Aux Ch Source Power Check
// Input Value  : None
// Output Value : _ON / _OFF
//--------------------------------------------------
bit ScalerDpRx1AuxChSourcePowerCheck(void)
{
    if(PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP() == _AUX_PN_1M_PULL_HI_LOW_SWAP_ON)
    {
        return GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP();
    }
    else
    {
        return GET_PCB_D1_DP_SOURCE_POWER();
    }
}

//--------------------------------------------------
// Description  : Dp Rx Aux Ch Power Status Check
// Input Value  : bCableStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AuxChPowerStatusCheck(bit bCableStatus)
{
    BYTE ucDebounceCnt = 0;

    if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        if(bCableStatus == _TRUE)
        {
            if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
            {
                // First time check power on with debounce to avoid AUX N always low case
                if((GET_DP_RX1_CHECK_AUX_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_NONE) && (ScalerDpRx1AuxChSourcePowerCheck() == _ON))
                {
                    // Debounce for 10ms
                    for(ucDebounceCnt = 0; ucDebounceCnt < 5; ucDebounceCnt++)
                    {
                        ScalerTimerDelayXms(2);

                        if(ScalerDpRx1AuxChSourcePowerCheck() == _OFF)
                        {
                            break;
                        }
                    }

                    if(ucDebounceCnt == 5)
                    {
                        SET_DP_RX1_CHECK_AUX_CH_POWER_STATUS(_DP_RX_AUX_POWER_STATUS_ON);
                    }
                }

                // Whether to Start Debounce
                if((ScalerDpRx1AuxChSourcePowerCheck() == _OFF) &&
                   (GET_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE() == _FALSE) &&
                   (GET_DP_RX1_CHECK_AUX_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_ON))
                {
                    SET_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();

                    ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                }

                // Debouncing
                if(GET_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE() == _TRUE)
                {
                    if(ScalerDpRx1AuxChSourcePowerCheck() == _ON)
                    {
                        CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                    }
                }

                // 1.5s HotPlug has been removed because NVIDIA GTX-1080 failed while HPD togglled at the moment of PC waked up from sleep.
                if((GET_DP_RX1_CHECK_AUX_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_OFF) && (ScalerDpRx1AuxChSourcePowerCheck() == _ON))
                {
                    SET_DP_RX1_CHECK_AUX_CH_POWER_STATUS(_DP_RX_AUX_POWER_STATUS_ON);

                    SET_DP_RX1_AUX_CH_POWER_ON_WAKE_UP();

                    SET_DP_RX1_SOURCE_FIRST_POWER_ON();
                }
            }
        }
        else
        {
            CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
            CLR_DP_RX1_CHECK_AUX_CH_POWER_STATUS();

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
        }
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDpRx1MstToSstInterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg)
{
    DWORD ulLinkClk = 0;
    WORD usTempVTotal = *pusVTotal;
    WORD usHTotalCount = 0;

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _OFF)
    WORD usVsyncWidth = 0;
    WORD usVstart = 0;
    WORD usVactive = 0;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    // Set Vfront Porch
    SET_DP_RX1_MST_TO_SST_VFRONT_PORCH(_DP_VSYNC_FRONT_PORCH);

    if(GET_DP_MST_FREESYNC_ENABLED() == _TRUE)
    {
        return _FALSE;
    }
#else
    // Set Vfront Porch
    SET_DP_RX1_MST_TO_SST_VFRONT_PORCH(_DP_VSYNC_FRONT_PORCH_MST2SST);
#endif

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Field inverse disable and Clr Fake Interlace Flag
    ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));
#else
    ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), _BIT0);
#endif

    // =========== Link Clock Measure Start ===========
    PDATA_WORD(0) = ScalerDpRx1SignalDetectMeasureCount(_D1_DP_LANE0, _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_2000_CYCLE);

    if(PDATA_WORD(0) == 0)
    {
        if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR3)
        {
            PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR3;
        }
        else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR2;
        }
        else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
        {
            PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR;
        }
        else // Both Default && _DP_LINK_RBR Case
        {
            PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_RBR;
        }
    }

    PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

    // Link Clk in KHz
    ulLinkClk = (PDATA_DWORD(0) / 1000);

    DebugMessageRx1("MST Current Link Clk", ulLinkClk);
    // =========== Link Clock Measure End ===========

    // =========== Continue Measure Two Frame Start ===========
    // Start to Measure Vertical BS to BS Counter by GDI Clock
    ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PA_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The result
    SET_DP_RX1_MEASURE_POP_UP_MST2SST();

    // Get Measure Result
    ScalerRead(PA_58_MN_MEAS_CTRL, 3, &pData[5], _AUTOINC);

    // Delay 2ms To Get VBID
    ScalerTimerDelayXms(2);

    // Get VBID
    ScalerRead(PA_29_MST2SST_VBID, 1, &pData[1], _NON_AUTOINC);

    // Delay 1 frame
    ScalerTimerDelayXms((((PDATA_DWORD(1) & 0x001FFFFF) / (_GDI_CLK_KHZ)) + 2));

    // Pop up Measure Result
    SET_DP_RX1_MEASURE_POP_UP_MST2SST();

    // Get Measure Result
    ScalerRead(PA_58_MN_MEAS_CTRL, 3, &pData[9], _AUTOINC);

    // Get Measure Htotal Counts
    ScalerRead(PA_5B_MN_MEAS_HLN_M, 2, &pData[12], _AUTOINC);

    // Get VBID
    ScalerRead(PA_29_MST2SST_VBID, 1, &pData[2], _NON_AUTOINC);

    PDATA_DWORD(1) = (PDATA_DWORD(1) & 0x001FFFFF);
    PDATA_DWORD(2) = (PDATA_DWORD(2) & 0x001FFFFF);

    // Disable Measure Block
    ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    // =========== Continue Measure Two Frame End ===========

    // Convert HTotal Count from 1/2 Link Clk to GDI Clk
    usHTotalCount = ((DWORD)PDATA_WORD(6) * _GDI_CLK_KHZ * 2 + (ulLinkClk >> 1)) / ulLinkClk;

    DebugMessageRx1("MST HTotal Count", usHTotalCount);

    // if VTotal Difference > 1/2 HTotal
    if((ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))) > (usHTotalCount / 2))
    {
        if(PDATA_DWORD(1) < PDATA_DWORD(2))
        {
            usTempVTotal = ((PDATA_DWORD(1) + (usHTotalCount >> 1)) / usHTotalCount);
        }
        else
        {
            usTempVTotal = ((PDATA_DWORD(2) + (usHTotalCount >> 1)) / usHTotalCount);
        }

        *pucOddFlg = _TRUE;
    }
    else
    {
        *pucOddFlg = _FALSE;
    }

    DebugMessageRx1("MST ####Calculated usVTotal####", usTempVTotal);

    DebugMessageRx1("7.MST DelayTime", (((PDATA_DWORD(1) & 0x000FFFFF) / (_GDI_CLK_KHZ)) + 2));
    DebugMessageRx1("7.MST Frame[N] VBS2BS Counter", PDATA_DWORD(1));
    DebugMessageRx1("7.MST Frame[N + 1] VBS2BS Counter", PDATA_DWORD(2));
    DebugMessageRx1("7.MST Frame diff ABS", (ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))));

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Check N and N+1 Frame Vs2Vs Count
    if((*pucOddFlg) == _TRUE)
    {
        // Enable DP Interlace
        ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

        // Enable Field Sync by BE
        ScalerSetBit(PA_F1_DP_RSV1, ~_BIT0, _BIT0);

        // HW Check Interlace
        if(ScalerGetBit(PA_56_INTERLACE_MODE_CONFIG, _BIT5) == _BIT5)
        {
            // Field reference HW
            ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);
        }
        else
        {
            // Field reference VBID
            ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);
        }

        // Set Vtt odd fw mode
        SET_DP_RX1_INTERLACE_VTT_FW_MODE_MST2SST(_ODD);

        *pusVTotal = usTempVTotal;

        return _TRUE;
    }
    else
    {
        // Check VBID Field Toggle and VBID Interlace Info
        if(((pData[1] & _BIT1) != (pData[2] & _BIT1)) && (ScalerGetBit(PA_29_MST2SST_VBID, _BIT2) == _BIT2))
        {
            // Enable DP Interlace
            ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

            // Field reference VBID
            ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

            // Enable Field Sync by BE
            ScalerSetBit(PA_F1_DP_RSV1, ~_BIT0, _BIT0);

            // Set Vtt Even fw mode
            SET_DP_RX1_INTERLACE_VTT_FW_MODE_MST2SST(_EVEN);

            *pusVTotal = usTempVTotal;

            return _TRUE;
        }

        // Enable DP Progressive Mode
        ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), 0x00);

        // Field reference VBID
        ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

        // Enable Field Sync by VBID
        ScalerSetBit(PA_F1_DP_RSV1, ~_BIT0, 0x00);

        // Set Vtt Even fw mode
        SET_DP_RX1_INTERLACE_VTT_FW_MODE_MST2SST(_EVEN);

        return _FALSE;
    }
#else
    if(ScalerGetBit(PA_29_MST2SST_VBID, _BIT2) == _BIT2) // Interlace
    {
        // Enable DP Interlace
        ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

        if((*pucOddFlg) == _FALSE)
        {
            // Disable DP Interlace
            ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), 0x00);
        }

        // Get VSW
        usVsyncWidth = ((WORD)ScalerGetByte(PA_1E_MSA_VSW_0) << 8) | ScalerGetByte(PA_1F_MSA_VSW_1);
        usVsyncWidth &= 0x7FFF;

        // Get VStart
        usVstart = ((WORD)ScalerGetByte(PA_1A_MSA_VST_0) << 8) | ScalerGetByte(PA_1B_MSA_VST_1);

        // usVbackporch = usVstart - Fixed V-Sync Pulse Width, usVbackporch > usVsyncWidth + 2 lines, here 2 lines is for V-Sync Falling edge to DEN Rising Edge distance margion
        if(((pData[1] & _BIT1) != (pData[2] & _BIT1)) && (usVstart > (usVsyncWidth + _DP_VSYNC_WIDTH + 2)))
        {
            // Field Information reference to VBID
            ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~_BIT6, 0x00);

            // Get Vactive
            usVactive = ((WORD)ScalerGetByte(PA_1C_MSA_VHT_0) << 8) | ScalerGetByte(PA_1D_MSA_VHT_1);

            // Set Front Porch = VTotal - Active height - MSA V Start + V Sync Pulse Width
            SET_DP_RX1_MST_TO_SST_VFRONT_PORCH(usTempVTotal - usVactive - usVstart + usVsyncWidth);

            if((ScalerGetBit(PA_56_INTERLACE_MODE_CONFIG, _BIT0) == 0x00) &&
               ((((pData[1] & _BIT1) == _BIT1) && ((pData[2] & _BIT1) == 0x00) && (PDATA_DWORD(1) < PDATA_DWORD(2))) ||
                (((pData[1] & _BIT1) == 0x00) && ((pData[2] & _BIT1) == _BIT1) && (PDATA_DWORD(1) > PDATA_DWORD(2)))))
            {
                // Field inverse enable
                ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), _BIT4);
            }
        }
        else
        {
            // Field reference HW
            ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);
        }

        *pusVTotal = usTempVTotal;

        return _TRUE;
    }
    else if((ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))) > (usHTotalCount / 2))
    {
        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        if(ScalerGetBit(PA_56_INTERLACE_MODE_CONFIG, _BIT0) == _BIT0)
        {
            DebugMessageRx1("MST Fake Interlace", 0);
            *pucOddFlg = _FALSE;
        }
        else
        {
            // Enable interlace mode, field reference HW
            ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), (_BIT7 | _BIT6));

            *pusVTotal = usTempVTotal;

            return _TRUE;
        }
    }

    // Disable DP Interlace
    ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), 0x00);

    return _FALSE;
#endif
}

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
//--------------------------------------------------
// Description  : DP Rx1 MstToSst VSC Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstToSstRSV1PacketDetectEvent(void)
{
    CLR_DP_RX1_MST2SST_RSV1_DETECTING();
}
#endif // End of #if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
#endif // End of #if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_DP_MST_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check Dp Video Straam VBID
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpRx1MSACheck(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Hactive
    ScalerRead(PB9_0C_MSA_HWD_0, 2, &pData[4], _AUTOINC);

    // Get Vactive
    ScalerRead(PB9_16_MSA_VHT_0, 2, &pData[12], _AUTOINC);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        if((PDATA_WORD(2) == 0x00) || (PDATA_WORD(6) == 0x00))
        {
            return _FALSE;
        }
    }
    else
#endif
    {
        // Get Htotal
        ScalerRead(PB9_08_MSA_HTT_0, 2, &pData[0], _AUTOINC);

        // Get Hstart
        ScalerRead(PB9_0A_MSA_HST_0, 2, &pData[2], _AUTOINC);

        // Get HSW
        ScalerRead(PB9_0E_MSA_HSW_0, 2, &pData[6], _AUTOINC);

        // Get Vtotal
        ScalerRead(PB9_10_MSA_VTTE_0, 2, &pData[8], _AUTOINC);

        // Get Vstart
        ScalerRead(PB9_14_MSA_VST_0, 2, &pData[10], _AUTOINC);

        // Get VSW
        ScalerRead(PB9_18_MSA_VSW_0, 2, &pData[14], _AUTOINC);

        if((PDATA_WORD(0) == 0x00) || (PDATA_WORD(1) == 0x00) || (PDATA_WORD(2) == 0x00) || ((PDATA_WORD(3) & 0x7FFF) == 0x00) ||
           (PDATA_WORD(4) == 0x00) || (PDATA_WORD(5) == 0x00) || (PDATA_WORD(6) == 0x00) || ((PDATA_WORD(7) & 0x7FFF) == 0x00))
        {
            if((PDATA_WORD(0) == 0x00) && (PDATA_WORD(1) == 0x00) && (PDATA_WORD(2) == 0x00) && ((PDATA_WORD(3) & 0x7FFF) == 0x00) &&
               (PDATA_WORD(4) == 0x00) && (PDATA_WORD(5) == 0x00) && (PDATA_WORD(6) == 0x00) && ((PDATA_WORD(7) & 0x7FFF) == 0x00))
            {
#if(_DP_MST_SUPPORT == _ON)
                if(GET_REG_DP_RX_MST_ENABLE() == _FALSE)
#endif
                {
                    if(ScalerDpRx1HdcpCheckValid() == _TRUE)
                    {
                        if(GET_DP_RX1_MSA_FAIL_MAC_RESET_COUNT() < 10)
                        {
                            ADD_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();
                        }
                        else
                        {
                            CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();

                            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
                            ScalerTimerDelayXms(30);
                            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

                            // Delay a Complete Frame
                            ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

                            ScalerDpRx1DecodeErrorCountReset();
                        }
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            return _FALSE;
        }

        CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();
    }

    // Get Mvid
    ScalerRead(PB9_1A_MSA_MVID_0, 3, pData, _AUTOINC);

    if((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) == 0x00)
    {
        return _FALSE;
    }

    // Get Nvid
    ScalerRead(PB9_1D_MSA_NVID_0, 3, pData, _AUTOINC);

    if((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) == 0x00)
    {
        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : PS Mode Set Fake LT Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1FakeLTProtect(void)
{
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX1_DP_LINK_TRAINING_REBUILD_PHY);

    SET_DP_RX1_FAKE_LINK_TRAINING();

    SET_DP_RX1_AUX_MANUAL_MODE();

    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY))
    {
        SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
    }

    SET_DP_RX1_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Set DP RSV0 infoframe type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetInitialRSV0InfoType(void)
{
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
    // Set Freesync Info Type to RSV0
    ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, _SPD_INFO_TYPE);
#else
#if((_DP_HDR10_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
    // Set Audio Info Type to RSV0
    ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, _DP_AUDIO_TIMESTAMP);
#endif
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    CLR_DP_RX1_RSV0_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_RSV0_PACKET_DETECT);
#endif
}

//--------------------------------------------------
// Description  : Set Dp HotPlug Event
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType)
{
    if((enumHpdType > _DP_HPD_LOW) && (ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _FALSE))
    {
        return;
    }

    // If the priority of enumHpdType is higher
    if(enumHpdType < GET_DP_RX1_HOTPLUG_ASSERT_TYPE())
    {
        SET_DP_RX1_HOTPLUG_ASSERT_TYPE(enumHpdType);
    }
}

//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HpdIrqAssert(void)
{
    if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
    {
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
        SET_DP_D1_HPD_IRQ_ASSERT_T2_EVENT();
#else

        BYTE ucBackUp2 = ScalerGetByte(PBA_D0_AUX_MODE_SET);

#if(_DP_TX_SUPPORT == _ON)
        // Disable IRQs that take too long
        BYTE ucBackUp1 = ScalerGetBit(PBB_72_HPD_IRQ_EN, _BIT6);
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);
#endif

        SET_DP_RX1_AUX_MANUAL_MODE();

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

        // Default = 750us
        switch(GET_DP_IRQ_TIME_10US())
        {
            case 55:
                DELAY_XUS(500);
                break;

            case 60:
                DELAY_XUS(546);
                break;

            case 65:
                DELAY_XUS(588);
                break;

            case 70:
                DELAY_XUS(634);
                break;

            case 75:
                DELAY_XUS(682);
                break;

            case 80:
                DELAY_XUS(728);
                break;

            case 85:
                DELAY_XUS(768);
                break;

            case 90:
                DELAY_XUS(816);
                break;

            case 95:
                DELAY_XUS(862);
                break;

            default:
                DELAY_XUS(682);
                break;
        }

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);

        if((ucBackUp2 & _BIT1) == _BIT1)
        {
            SET_DP_RX1_AUX_AUTO_MODE();
        }

#if(_DP_TX_SUPPORT == _ON)
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, ucBackUp1);
#endif
#endif

        // For Meeting Spec of HPD_IRQ Minimum Spacing >= 2 ms
        ScalerTimerDelayXms(3);
    }
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HpdIrqAssert_EXINT0(void) using 1
{
    if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
    {
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
        SET_DP_D1_HPD_IRQ_ASSERT_T2_EVENT();
#else

        BYTE ucBackUp2 = ScalerGetByte_EXINT(PBA_D0_AUX_MODE_SET);

#if(_DP_TX_SUPPORT == _ON)
        // Disable IRQs that take too long
        BYTE ucBackUp1 = ScalerGetBit_EXINT(PBB_72_HPD_IRQ_EN, _BIT6);
        ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);
#endif

        SET_DP_RX1_AUX_MANUAL_MODE_EXINT();

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

        // Default = 750us
        switch(GET_DP_IRQ_TIME_10US())
        {
            case 55:
                DELAY_XUS_EXINT(500);
                break;

            case 60:
                DELAY_XUS_EXINT(546);
                break;

            case 65:
                DELAY_XUS_EXINT(588);
                break;

            case 70:
                DELAY_XUS_EXINT(634);
                break;

            case 75:
                DELAY_XUS_EXINT(682);
                break;

            case 80:
                DELAY_XUS_EXINT(728);
                break;

            case 85:
                DELAY_XUS_EXINT(768);
                break;

            case 90:
                DELAY_XUS_EXINT(816);
                break;

            case 95:
                DELAY_XUS_EXINT(862);
                break;

            default:
                DELAY_XUS_EXINT(682);
                break;
        }

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);

        if((ucBackUp2 & _BIT1) == _BIT1)
        {
            SET_DP_RX1_AUX_AUTO_MODE_EXINT();
        }

#if(_DP_TX_SUPPORT == _ON)
        ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, ucBackUp1);
#endif
#endif
    }
}
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_ULTRA_HDR_SUPPORT == _ON))
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpRx1GetInfoFrameRSV0(BYTE *pucDPRx1RSV0Data)
{
    BYTE ucTemp = 0;
    BYTE ucDebounceCnt = 5;

    BYTE pucTmepData1[_HW_DP_INFOFRAME_RSV0_LENGTH];
    BYTE pucTmepData2[_HW_DP_INFOFRAME_RSV0_LENGTH];

    do
    {
        ScalerSetByte(PB9_30_DP_INFO_FM_ADR, (_DP_INFO_RSV0_DB0 + ucTemp));
        pucTmepData1[ucTemp] = ScalerGetByte(PB9_31_DP_INFO_FM_DAT);

        ucTemp ++;
    }
    while(ucTemp < _HW_DP_INFOFRAME_RSV0_LENGTH);

    do
    {
        ucTemp = 0;

        do
        {
            ScalerSetByte(PB9_30_DP_INFO_FM_ADR, (_DP_INFO_RSV0_DB0 + ucTemp));
            pucTmepData2[ucTemp] = ScalerGetByte(PB9_31_DP_INFO_FM_DAT);

            ucTemp ++;
        }
        while(ucTemp < _HW_DP_INFOFRAME_RSV0_LENGTH);

        if(memcmp(pucTmepData1, pucTmepData2, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
        {
            break;
        }
        else
        {
            memcpy(pucTmepData1, pucTmepData2, _HW_DP_INFOFRAME_RSV0_LENGTH);
        }

        ucDebounceCnt --;
    }
    while(ucDebounceCnt > 0);

    memcpy(pucDPRx1RSV0Data, pucTmepData2, _HW_DP_INFOFRAME_RSV0_LENGTH);
}
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP InfoFrame RSV0 Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1InfoFrameRSV0Check(void)
{
    BYTE pucDPRx1RSV0Data[_HW_DP_INFOFRAME_RSV0_LENGTH];
    BYTE ucInfoFrameType = 0;

    memset(pucDPRx1RSV0Data, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
    ScalerDpRx1GetInfoFrameRSV0(pucDPRx1RSV0Data);

#if(_DP_HDR10_SUPPORT == _ON)
    ucInfoFrameType = ScalerGetByte(PB9_2C_DP_INFO_FM_RSV0);

    if(ucInfoFrameType == _HDR_INFO_TYPE)
    {
        switch(g_ucDPRx1InfoTypeCompare)
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
            case _SPD_INFO_TYPE:

                if(GET_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED() == _TRUE)
                {
                    if(memcmp(pucDPRx1RSV0Data, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                    {
                        if(memcmp(g_pucDPRx1RSV0Backup, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                        {
                            CLR_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                            memset(g_pucDPRx1HDR10Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                        }
                        else
                        {
                            // Do nothing: confuse case, keep last time status
                        }
                    }
                    else
                    {
                        SET_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                        memcpy(g_pucDPRx1HDR10Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                }
                else
                {
                    SET_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx1HDR10Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;
#endif

            case _DP_AUDIO_TIMESTAMP:

                if(GET_DP_RX1_AUDIO_INFO_FRAME_RECEIVED() == _TRUE)
                {
                    // Maud:[0:15], Naud:[16:31] is constant, Check Naud (arrary[16:27])
                    if(memcmp(&pucDPRx1RSV0Data[16], &g_pucDPRx1InfoTemp[16], 12) == 0)
                    {
                        if(memcmp(g_pucDPRx1RSV0Backup, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                        {
                            CLR_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                            memset(g_pucDPRx1HDR10Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                        }
                        else
                        {
                            // Do nothing: confuse case, keep last time status
                        }
                    }
                    else
                    {
                        SET_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                        memcpy(g_pucDPRx1HDR10Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                }
                else
                {
                    SET_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx1HDR10Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;

            default:
                break;
        }
    }
    else
    {
        switch(g_ucDPRx1InfoTypeCompare)
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
            case _SPD_INFO_TYPE:

                if(memcmp(pucDPRx1RSV0Data, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                {
                    if(memcmp(g_pucDPRx1HDR10Backup, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                    {
                        CLR_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED();
                        memset(g_pucDPRx1RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                    else
                    {
                        // Do nothing: confuse case, keep last time status
                    }
                }
                else
                {
                    SET_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx1RSV0Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;
#endif

            case _DP_AUDIO_TIMESTAMP:

                if(memcmp(pucDPRx1RSV0Data, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                {
                    if(memcmp(g_pucDPRx1HDR10Backup, g_pucDPRx1InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                    {
                        CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
                        memset(g_pucDPRx1RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                    else
                    {
                        // Do nothing: confuse case, keep last time status
                    }
                }
                else
                {
                    SET_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx1RSV0Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;

            default:
                break;
        }
    }

    ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, ScalerDpRx1SelectInfoFrameType(ucInfoFrameType));

    // Get infoframe after switch infoframe header for check
    ScalerDpRx1GetInfoFrameRSV0(g_pucDPRx1InfoTemp);
#else
    ucInfoFrameType = ucInfoFrameType;
#endif
}

//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1RSV0PacketDetectEvent(void)
{
    CLR_DP_RX1_RSV0_DETECTING();
}

//--------------------------------------------------
// Description  : DP InfoFrame RSV0 initial setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1InfoFrameRSV0Initial(void)
{
#if(_DP_HDR10_SUPPORT == _ON)
    CLR_DP_RX1_HDR_INFO_FRAME_RECEIVED();

    // Get RSV0 Infoframe
    ScalerDpRx1GetInfoFrameRSV0(g_pucDPRx1RSV0Backup);

    // Get Compare with HDR infoframe type
    g_ucDPRx1InfoTypeCompare = ScalerGetByte(PB9_2C_DP_INFO_FM_RSV0);

    // Set DP RSV0 info type: HDR
    ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, _HDR_INFO_TYPE);

    // Get infoframe after switch infoframe header for check
    ScalerDpRx1GetInfoFrameRSV0(g_pucDPRx1InfoTemp);
#endif
}
#endif // End of #if(_DP_ULTRA_HDR_SUPPORT == _ON)

#if(_DP_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Select InfoFrame Type
// Input Value  : None
// Output Value : InfoFrame Type
//--------------------------------------------------
BYTE ScalerDpRx1SelectInfoFrameType(BYTE ucInfoFrameTypeCurrent)
{
    BYTE ucInfoFrameTypeNext = 0;

    if(ucInfoFrameTypeCurrent == _HDR_INFO_TYPE)
    {
        ucInfoFrameTypeNext = g_ucDPRx1InfoTypeCompare;
    }
    else
    {
        ucInfoFrameTypeNext = _HDR_INFO_TYPE;
    }

    return ucInfoFrameTypeNext;
}

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch DP HDR10 comapre info type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SwitchHDR10CmpAudioInfo(void)
{
    BYTE pucRSV0Data1[_HW_DP_INFOFRAME_RSV0_LENGTH];
    BYTE pucRSV0Data2[_HW_DP_INFOFRAME_RSV0_LENGTH];

    memset(pucRSV0Data1, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
    memset(pucRSV0Data2, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED() == _TRUE)
    {
        CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
    }
    else
#endif
    {
        // Set Audio Info Type to RSV0
        ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, _DP_AUDIO_TIMESTAMP);

        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        ScalerDpRx1GetInfoFrameRSV0(pucRSV0Data1);

        // check pucRSV0Data1 not all 0
        if(memcmp(pucRSV0Data1, pucRSV0Data2, _HW_DP_INFOFRAME_RSV0_LENGTH) != 0)
        {
            // Get MSA Naud
            pucRSV0Data2[16] = ScalerGetByte(PB9_23_MSA_NAUD_0);
            pucRSV0Data2[17] = ScalerGetByte(PB9_24_MSA_NAUD_1);
            pucRSV0Data2[18] = ScalerGetByte(PB9_25_MSA_NAUD_2);
            pucRSV0Data2[19] = 0x00;

            // Check Audio time stamp info
            if((memcmp(&pucRSV0Data1[16], &pucRSV0Data2[16], 4) == 0) &&
               (memcmp(&pucRSV0Data1[16], &pucRSV0Data1[20], 4) == 0) &&
               (memcmp(&pucRSV0Data1[16], &pucRSV0Data1[24], 4) == 0))
            {
                SET_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
                memcpy(g_pucDPRx1RSV0Backup, pucRSV0Data1, _HW_DP_INFOFRAME_RSV0_LENGTH);
            }
            else
            {
                CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
                memset(g_pucDPRx1RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
            }
        }
        else
        {
            CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
            memset(g_pucDPRx1RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
        }

        // Get Compare with HDR infoframe type
        g_ucDPRx1InfoTypeCompare = ScalerGetByte(PB9_2C_DP_INFO_FM_RSV0);

        // Set DP RSV0 info type: HDR
        ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, _HDR_INFO_TYPE);

        // Get infoframe after switch infoframe header for check
        ScalerDpRx1GetInfoFrameRSV0(g_pucDPRx1InfoTemp);
    }
}
#endif
#endif // End of #if(_DP_HDR10_SUPPORT == _ON)

#endif // End of #if(_D1_DP_EXIST == _ON)
