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
// ID Code      : ScalerCommonDPRx0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_DPRX0__

#include "ScalerCommonFunctionInclude.h"

#if(_D0_DP_EXIST == _ON)

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
#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
bit g_bDpRx0SignaldetectINTHappened;
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit g_bDpRx0VscSdpColorMode;

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
bit g_bDpRx0RSV1PacketDetecting;

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
bit g_bDpRx0MstToSstRSV1PacketDetecting;
#endif
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
WORD g_usDpRx0MstToSstVfrontporch;
#endif

BYTE g_ucDpRx0MSAFailMacRsetCount;
bit g_bDpRx0SourceRDErrorCount = _FALSE;
bit g_bDpRx0InterlaceVtotalNum;

#if(_DP_HDR10_SUPPORT == _ON)
BYTE g_ucDPRx0InfoTypeCompare;
BYTE g_pucDPRx0HDR10Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
BYTE g_pucDPRx0InfoTemp[_HW_DP_INFOFRAME_RSV0_LENGTH];
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
BYTE g_pucDPRx0RSV0Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
StructDPInfoFrameRSV0Ctrl g_stDPRx0InfoFrameRSV0Ctrl;
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
StructDpLinkInfo g_stDpRx0LinkInfo;
#endif

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
BYTE g_ucDpRx0AuxModeBackup_EXINT;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpRx0DecodeErrorCountReset(void);
WORD ScalerDpRx0GetDecodeErrorCount(BYTE ucDpRx0LaneNumber);
void ScalerDpRx0ValidSignalDetection(void);
BYTE ScalerDpRx0LinkRateDetect(void);
bit ScalerDpRx0LinkRateCheck(BYTE ucDpLinkRate);
WORD ScalerDpRx0SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);
bit ScalerDpRx0SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
bit ScalerDpRx0VBIOSMSACheck(bit bDeskewEnhanced);
bit ScalerDpRx0InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);
bit ScalerDpRx0GetVideoInfo(void);
void ScalerDpRx0SetColorInfo(void);
void ScalerDpRx0VideoSetting(void);
void ScalerDpRx0ColorimetrySetting(void);
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
void ScalerDpRx0ColorimetryExtSetting(void);
#endif
void ScalerDpRx0QuantizationSetting(void);

bit ScalerDpRx0MiscCheck(void);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit ScalerDpRx0VscCheck(void);

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
void ScalerDpRx0RSV1PacketDetectEvent(void);
void ScalerDpRx0SetInitialRSV1InfoType(void);
#endif

#endif

void ScalerDpRx0HDCPUnplugReset(void);

#if(_DP_MST_SUPPORT == _ON)
void ScalerDpRx0MstReset(void);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
void ScalerDpRx0MstReset_EXINT0(void);
#endif

bit ScalerDpRx0AuxChSourcePowerCheck(void);
void ScalerDpRx0AuxChPowerStatusCheck(bit bCableStatus);

#if(_DP_TX_SUPPORT == _ON)
bit ScalerDpRx0MstToSstGetVideoInfo(void);
void ScalerDpRx0MstToSstSetColorInfo(void);
void ScalerDpRx0MstToSstVideoSetting(void);
bit ScalerDpRx0MstToSstMiscCheck(void);
bit ScalerDpRx0MstToSstInterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit ScalerDpRx0MstToSstVscCheck(void);

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
void ScalerDpRx0MstToSstRSV1PacketDetectEvent(void);
#endif
#endif
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRx0UpdateSinkCount(BYTE ucSinkCount);
#endif

bit ScalerDpRx0MSACheck(void);
void ScalerDpRx0FakeLTProtect(void);
void ScalerDpRx0SetInitialRSV0InfoType(void);

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_ULTRA_HDR_SUPPORT == _ON))
void ScalerDpRx0GetInfoFrameRSV0(BYTE *pucDPRx0RSV0Data);
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
void ScalerDpRx0InfoFrameRSV0Check(void);
void ScalerDpRx0RSV0PacketDetectEvent(void);
void ScalerDpRx0InfoFrameRSV0Initial(void);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
BYTE ScalerDpRx0SelectInfoFrameType(BYTE ucInfoFrameTypeCurrent);

#if(_AUDIO_SUPPORT == _ON)
void ScalerDpRx0SwitchHDR10CmpAudioInfo(void);
#endif
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx0DecodeErrorCountReset_WDINT(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Reset 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0DecodeErrorCountReset(void)
{
    // Reset 8b10b Error Count Value
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Start Record 8b10b Error Count Value
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
}

//--------------------------------------------------
// Description  : Get 8b10b Error Count value
// Input Value  : Lane
// Output Value : Error Count
//--------------------------------------------------
WORD ScalerDpRx0GetDecodeErrorCount(BYTE ucDpRx0LaneNumber)
{
    // Select Lane
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (ucDpRx0LaneNumber << 3));

    return ((((WORD)ScalerGetByte(PB_0B_BIST_PATTERN3)) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));
}

//--------------------------------------------------
// Description  : Check Valid Video Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ValidSignalDetection(void)
{
    BYTE ucDpLinkRate = 0;
    BYTE ucDpLaneCount = _DP_FOUR_LANE;

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    if(ScalerTypeCRx0PdGetPinAssignment() == _TYPE_C_PIN_ASSIGNMENT_D)
    {
        ucDpLaneCount = _DP_TWO_LANE;
    }
#endif

#if(_DP_MST_SUPPORT == _ON)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if(((GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT) && (g_stDpRx0MiscInfo.b1DpMstEnableBackup == _TRUE)) ||
       ((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (g_stDpRx0MiscInfo.b1DpRx6MstEnableBackup == _TRUE)))
#else
    if(g_stDpRx0MiscInfo.b1DpMstEnableBackup == _TRUE)
#endif
    {
        SET_DP_RX0_AUX_MANUAL_MODE();

        if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
           (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == 0x00) &&
           (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) != _BIT1))
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x00, g_stDpRx0MiscInfo.ucDpRxLinkRateBackup);
            ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x01, ((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x60) | (g_stDpRx0MiscInfo.ucDpRxLaneCountBackup | _BIT7)));

            if(g_stDpRx0MiscInfo.ucDpRxLaneCountBackup == _DP_FOUR_LANE)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x77);
            }
            else if(g_stDpRx0MiscInfo.ucDpRxLaneCountBackup == _DP_TWO_LANE)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x00);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x07);
                ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x00);
            }

            ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x04, 0x01);

            SET_DP_RX0_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS_VBIOS);

            ScalerDpRx0MstInfoBackup(_DP_MST_BACKUP_INFO_RESTORE);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            ScalerDpRx6MstInfoBackup(_DP_MST_BACKUP_INFO_RESTORE);
#endif
        }

        SET_DP_RX0_AUX_AUTO_MODE();

        DebugMessageRx0("VBIOS_Link_Rate_MST", ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00));
        DebugMessageRx0("VBIOS_Lane_Count_MST", ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01));
    }
    else
#endif // End of #if(_DP_MST_SUPPORT == _ON)
    {
        SET_DP_RX0_AUX_MANUAL_MODE();

#if(_DP_MST_SUPPORT == _ON)
        if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
           (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == 0x00) &&
           (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) != _BIT1))
#else
        if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
           (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
#endif
        {
            ucDpLinkRate = ScalerDpRx0LinkRateDetect();

            SET_DP_RX0_AUX_AUTO_MODE();

            if(ucDpLinkRate == _DP_LINK_NONE)
            {
                return;
            }

            do
            {
                SET_DP_RX0_AUX_MANUAL_MODE();

#if(_DP_MST_SUPPORT == _ON)
                if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
                   (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == 0x00) &&
                   (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) != _BIT1))
#else
                if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
                   (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
#endif
                {
                    ScalerDpRx0RebuildPhy(ucDpLinkRate, (ucDpLaneCount | _BIT7));

                    SET_DP_RX0_AUX_AUTO_MODE();

                    if(ScalerDpRx0VBIOSMSACheck(_FALSE) == _TRUE)
                    {
                        break;
                    }
                    else
                    {
                        if(ScalerDpRx0VBIOSMSACheck(_TRUE) == _TRUE)
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
                    SET_DP_RX0_AUX_AUTO_MODE();

                    return;
                }
            }
            while((ucDpLaneCount == _DP_TWO_LANE) || (ucDpLaneCount == _DP_ONE_LANE));

            SET_DP_RX0_AUX_MANUAL_MODE();

#if(_DP_MST_SUPPORT == _ON)
            if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
               (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == 0x00) &&
               (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) != _BIT1))
#else
            if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) &&
               (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == 0x00))
#endif
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x00, ucDpLinkRate);
                ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x01, ((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x60) | (ucDpLaneCount | _BIT7)));

                if(ucDpLaneCount == _DP_FOUR_LANE)
                {
                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x77);
                }
                else if(ucDpLaneCount == _DP_TWO_LANE)
                {
                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x00);
                }
                else
                {
                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x07);
                    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x00);
                }

                ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x04, 0x01);

                SET_DP_RX0_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS_VBIOS);
            }

            SET_DP_RX0_AUX_AUTO_MODE();
        }

        SET_DP_RX0_AUX_AUTO_MODE();

        DebugMessageRx0("VBIOS_Link_Rate", ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00));
        DebugMessageRx0("VBIOS_Lane_Count", ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01));
    }
}

//--------------------------------------------------
// Description : DP Link Rate Detect
// Input Value  : None
// Output Value : Link Rate
//--------------------------------------------------
BYTE ScalerDpRx0LinkRateDetect(void)
{
    BYTE ucDpLinkRate = 0;
    BYTE ucDpLinkRateDecide = _DP_LINK_NONE;

    do
    {
        if(ucDpLinkRate == 0)
        {
            if(_HW_DP_D0_MAX_LINK_RATE_SUPPORT > ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01))
            {
                ucDpLinkRate = _HW_DP_D0_MAX_LINK_RATE_SUPPORT;
            }
            else
            {
                ucDpLinkRate = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01);
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

        if(ScalerDpRx0LinkRateCheck(ucDpLinkRate) == _TRUE)
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
bit ScalerDpRx0LinkRateCheck(BYTE ucDpLinkRate)
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

        ScalerDpRx0SignalDetectInitial(ucDpLinkRate, ucDpLEQScanValue);

        usDataStreamL0 = ScalerDpRx0SignalDetectMeasureCount(_D0_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

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
WORD ScalerDpRx0SignalDetectMeasureCount(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod)
{
    WORD usDpMeasureCount = 0;

    // [1:0] freqdet_lane_sel
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ucDpLaneSel & (_BIT1 | _BIT0)));

    // [5] ln_ck_sel
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT5, enumDpMeasureTarget);

    switch(enumDpMeasurePeriod)
    {
        case _DP_MEASURE_PERIOD_1000_CYCLE:

#if(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_1)
            // [4:0] DP_XTAL_CYCLE = 5'b00011
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
#elif(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_2)
            // [0] DP_XTAL_CYCLE = 1'b0
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT0, 0x00);
#endif
            break;

        case _DP_MEASURE_PERIOD_2000_CYCLE:
        default:

#if(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_1)
            // [4:0] DP_XTAL_CYCLE = 5'b00100
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
#elif(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_2)
            // [0] DP_XTAL_CYCLE = 1'b1
            ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT0, _BIT0);
#endif
            break;
    }

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            usDpMeasureCount = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

            break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    return usDpMeasureCount;
}

//--------------------------------------------------
// Description : Check Valid Signal
// Input Value  : DP Link Rate and Lane Count
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx0SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
    WORD usDataStreamL0 = 0;
    WORD usDataStreamL1 = 0;
    WORD usDataStreamL2 = 0;
    WORD usDataStreamL3 = 0;
    WORD usMeasureUpperBound = 0;
    WORD usMeasureLowerBound = 0;

    // Scrambling Disable Check
    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x02, _BIT5) == _BIT5)
    {
        return _TRUE;
    }

#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
    CLR_DP_RX0_SIGNALDETECT_INT_HAPPENED();
#endif

    // Measure Data Stream Count
    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            usDataStreamL0 = ScalerDpRx0SignalDetectMeasureCount(_D0_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;

        case _DP_TWO_LANE:

            usDataStreamL0 = ScalerDpRx0SignalDetectMeasureCount(_D0_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL1 = ScalerDpRx0SignalDetectMeasureCount(_D0_DP_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

            break;

        default:
        case _DP_FOUR_LANE:

            usDataStreamL0 = ScalerDpRx0SignalDetectMeasureCount(_D0_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL1 = ScalerDpRx0SignalDetectMeasureCount(_D0_DP_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL2 = ScalerDpRx0SignalDetectMeasureCount(_D0_DP_LANE2, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);
            usDataStreamL3 = ScalerDpRx0SignalDetectMeasureCount(_D0_DP_LANE3, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_2000_CYCLE);

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
#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
        if(GET_DP_RX0_SIGNALDETECT_INT_HAPPENED() == _FALSE)
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
#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_RX0_SIGNALDETECT_INT_HAPPENED() == _FALSE)
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
#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_RX0_SIGNALDETECT_INT_HAPPENED() == _FALSE)
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
#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
                if(GET_DP_RX0_SIGNALDETECT_INT_HAPPENED() == _FALSE)
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
bit ScalerDpRx0VBIOSMSACheck(bit bDeskewEnhanced)
{
    bit bMSACheckResult = _FALSE;

    do
    {
        // De-Skew Circuit Reset
        ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), (((bDeskewEnhanced == _TRUE) ? _BIT7 : 0x00) | _BIT6));

        // Mac Reset After Link Clock Stable
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

        // SEC Reset
        ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT4, _BIT4);
        ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT4, 0x00);

        // Wait Two Frame Time to Get MSA
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        // Pop up Main Stream Attributes
        ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

        // Get Nvid
        ScalerRead(PB6_1D_MSA_NVID_0, 3, pData, _AUTOINC);

        // Get Hactive
        ScalerRead(PB6_0C_MSA_HWD_0, 2, &pData[4], _AUTOINC);

        // Get Vactive
        ScalerRead(PB6_16_MSA_VHT_0, 2, &pData[6], _AUTOINC);

        // Get Hstart
        ScalerRead(PB6_0A_MSA_HST_0, 2, &pData[8], _AUTOINC);

        // Get Vstart
        ScalerRead(PB6_14_MSA_VST_0, 2, &pData[10], _AUTOINC);

        if(((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) != 0x00) &&
           (PDATA_WORD(2) != 0x00) && (PDATA_WORD(3) != 0x00) && (PDATA_WORD(4) != 0x00) && (PDATA_WORD(5) != 0x00) &&
           (PDATA_WORD(2) > PDATA_WORD(4)) && (PDATA_WORD(3) > PDATA_WORD(5)))
        {
            bMSACheckResult = _TRUE;

            break;
        }
    }while(ScalerDpRx0ChangeSrambleSeed() == _TRUE);

#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)
    bMSACheckResult = ScalerDpRx0VbiosAssrCheck(bMSACheckResult);
#endif

    return bMSACheckResult;
}

//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDpRx0InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg)
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
    SET_DP_RX0_VFRONT_PORCH(_DP_VSYNC_FRONT_PORCH);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        return _FALSE;
    }
#endif

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Field inverse disable and Clr Fake Interlace Flag
    ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));
#else
    ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), _BIT0);
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        // Restore DP Info
        PDATA_DWORD(1) = g_stDpRx0LinkInfo.ulVBsToBsCountN;
        PDATA_DWORD(2) = g_stDpRx0LinkInfo.ulVBsToBsCountN1;
        pData[1] = ((BYTE) g_stDpRx0LinkInfo.bInterlaceFieldN) << 1;
        pData[2] = ((BYTE) g_stDpRx0LinkInfo.bInterlaceFieldN1) << 1;
    }
    else
#endif
    {
        // =========== Link Clock Measure Start ===========
        PDATA_WORD(0) = ScalerDpRx0SignalDetectMeasureCount(_D0_DP_LANE0, _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_2000_CYCLE);

        if(PDATA_WORD(0) == 0)
        {
            if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR3)
            {
                PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR3;
            }
            else if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
            {
                PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR2;
            }
            else if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
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

        DebugMessageRx0("Current Link Clk", ulLinkClk);
        // =========== Link Clock Measure End ===========

        // =========== Continue Measure Two Frame Start ===========
        // Start to Measure Vertical BS to BS Counter by GDI Clock
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB5_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
        {
            return _FALSE;
        }

        // Pop up The result
        SET_DP_RX0_MEASURE_POP_UP();

        // Get Measure Result
        ScalerRead(PB5_58_MN_MEAS_CTRL, 3, &pData[5], _AUTOINC);

        // Delay 2ms To Get VBID
        ScalerTimerDelayXms(2);

        // Get VBID
        ScalerRead(PB6_01_DP_VBID, 1, &pData[1], _NON_AUTOINC);

        // Delay 1 frame
        ScalerTimerDelayXms((((PDATA_DWORD(1) & 0x001FFFFF) / (_GDI_CLK_KHZ)) + 2));

        // Pop up Measure Result
        SET_DP_RX0_MEASURE_POP_UP();

        // Get Measure Result
        ScalerRead(PB5_58_MN_MEAS_CTRL, 3, &pData[9], _AUTOINC);

        // Get Measure Htotal Counts
        ScalerRead(PB5_5B_MN_MEAS_HLN_M, 2, &pData[12], _AUTOINC);

        // Get VBID
        ScalerRead(PB6_01_DP_VBID, 1, &pData[2], _NON_AUTOINC);

        PDATA_DWORD(1) = (PDATA_DWORD(1) & 0x001FFFFF);
        PDATA_DWORD(2) = (PDATA_DWORD(2) & 0x001FFFFF);

        // Disable Measure Block
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
        // =========== Continue Measure Two Frame End ===========

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
        // Backup DP Info
        g_stDpRx0LinkInfo.ulVBsToBsCountN = PDATA_DWORD(1);
        g_stDpRx0LinkInfo.ulVBsToBsCountN1 = PDATA_DWORD(2);
        g_stDpRx0LinkInfo.bInterlaceFieldN = (bit)(pData[1] & _BIT1);
        g_stDpRx0LinkInfo.bInterlaceFieldN1 = (bit)(pData[2] & _BIT1);
#endif
    }

    // Convert HTotal Count from 1/2 Link Clk to GDI Clk
    usHTotalCount = ((DWORD)PDATA_WORD(6) * _GDI_CLK_KHZ * 2 + (ulLinkClk >> 1)) / ulLinkClk;

    DebugMessageRx0("HTotal Count", usHTotalCount);

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

    DebugMessageRx0("####Calculated usVTotal####", usTempVTotal);

    DebugMessageRx0("7. DelayTime", (((PDATA_DWORD(1) & 0x000FFFFF) / (_GDI_CLK_KHZ)) + 2));
    DebugMessageRx0("7. Frame[N] VBS2BS Counter", PDATA_DWORD(1));
    DebugMessageRx0("7. Frame[N + 1] VBS2BS Counter", PDATA_DWORD(2));
    DebugMessageRx0("7. Frame diff ABS", (ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))));

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Check N and N+1 Frame Vs2Vs Count
    if((*pucOddFlg) == _TRUE)
    {
        // Enable DP Interlace
        ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

        // Enable Field Sync by BE
        ScalerSetBit(PB5_F1_DP_RSV1, ~_BIT0, _BIT0);

        // HW Check Interlace
        if(ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, _BIT5) == _BIT5)
        {
            // Field reference HW
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);
        }
        else
        {
            // Field reference VBID
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);
        }

        // Set Vtt odd fw mode
        SET_DP_RX0_INTERLACE_VTT_FW_MODE(_ODD);

        *pusVTotal = usTempVTotal;

        return _TRUE;
    }
    else
    {
        // Check VBID Field Toggle and VBID Interlace Info
        if(((pData[1] & _BIT1) != (pData[2] & _BIT1)) && (ScalerGetBit(PB6_01_DP_VBID, _BIT2) == _BIT2))
        {
            // Enable DP Interlace
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

            // Field reference VBID
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

            // Enable Field Sync by BE
            ScalerSetBit(PB5_F1_DP_RSV1, ~_BIT0, _BIT0);

            // Set Vtt Even fw mode
            SET_DP_RX0_INTERLACE_VTT_FW_MODE(_EVEN);

            *pusVTotal = usTempVTotal;

            return _TRUE;
        }

        // Enable DP Progressive Mode
        ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), 0x00);

        // Field reference VBID
        ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

        // Enable Field Sync by VBID
        ScalerSetBit(PB5_F1_DP_RSV1, ~_BIT0, 0x00);

        // Set Vtt Even fw mode
        SET_DP_RX0_INTERLACE_VTT_FW_MODE(_EVEN);

        return _FALSE;
    }
#else
    if(ScalerGetBit(PB6_01_DP_VBID, _BIT2) == _BIT2) // Interlace
    {
        // Enable DP Interlace
        ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), _BIT7);

        if((*pucOddFlg) == _FALSE)
        {
            // Disable DP Interlace
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT5 | _BIT0), 0x00);
        }

        // Get VSW
        usVsyncWidth = ((WORD)ScalerGetByte(PB6_18_MSA_VSW_0) << 8) | ScalerGetByte(PB6_19_MSA_VSW_1);
        usVsyncWidth &= 0x7FFF;

        // Get VStart
        usVstart = ((WORD)ScalerGetByte(PB6_14_MSA_VST_0) << 8) | ScalerGetByte(PB6_15_MSA_VST_1);

        // usVbackporch = usVstart - Fixed V-Sync Pulse Width, usVbackporch > usVsyncWidth + 2 lines, here 2 lines is for V-Sync Falling edge to DEN Rising Edge distance margion
        if(((pData[1] & _BIT1) != (pData[2] & _BIT1)) && (usVstart > (usVsyncWidth + _DP_VSYNC_WIDTH + 2)))
        {
            // Field Information reference to VBID
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

            // Get Vactive
            usVactive = ((WORD)ScalerGetByte(PB6_16_MSA_VHT_0) << 8) | ScalerGetByte(PB6_17_MSA_VHT_1);

            // Set Front Porch = VTotal - Active height - MSA V Start + V Sync Pulse Width
            SET_DP_RX0_VFRONT_PORCH(usTempVTotal - usVactive - usVstart + usVsyncWidth);

            if((ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, _BIT0) == 0x00) &&
               ((((pData[1] & _BIT1) == _BIT1) && ((pData[2] & _BIT1) == 0x00) && (PDATA_DWORD(1) < PDATA_DWORD(2))) ||
                (((pData[1] & _BIT1) == 0x00) && ((pData[2] & _BIT1) == _BIT1) && (PDATA_DWORD(1) > PDATA_DWORD(2)))))
            {
                // Field inverse enable
                ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), _BIT4);
            }
        }
        else
        {
            // Field reference HW
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);
        }

        *pusVTotal = usTempVTotal;

        return _TRUE;
    }
    else if((ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))) > (usHTotalCount / 2))
    {
        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        if(ScalerGetBit(PB5_57_INTERLACE_MODE_CONFIG, _BIT0) == _BIT0)
        {
            DebugMessageRx0("Fake Interlace", 0);
            *pucOddFlg = _FALSE;
        }
        else
        {
            // Enable interlace mode, field reference HW
            ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), (_BIT7 | _BIT6));

            *pusVTotal = usTempVTotal;

            return _TRUE;
        }
    }

    // Disable DP Interlace
    ScalerSetBit(PB5_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), 0x00);

    return _FALSE;
#endif
}

//--------------------------------------------------
// Description  : DP Get Video Info
// Input Value  : None
// Output Value : TRUE --> Get successfully
//--------------------------------------------------
bit ScalerDpRx0GetVideoInfo(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    CLR_DP_RX0_VSC_SDP_COLOR_MODE();

    // Check MISC1[6]
    if((ScalerGetBit(PB6_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        SET_DP_RX0_VSC_SDP_COLOR_MODE();

#if(_HW_DP_VSC_SDP_REG_SUPPORT == _ON)

        // Read DB16~18 --> pData[0:2]
        ScalerRead(PB6_46_VSC15, 3, pData, _AUTOINC);
#else
        // Delay 2 frames for SRAM ready (worst case)
        ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX * 2);

        SET_DP_RX0_RSV1_DETECTING();

        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX0_RSV1_PACKET_DETECT);

        // Read DB16~18 --> pData[0:2]
        ScalerGetDataPortByte(PB6_30_DP_INFO_FM_ADR, _DP_INFO_RSV1_DB16, 3, pData, _AUTOINC);
#endif
        // Set ColorimetryExtPreValue & QuantizationPreValue & ColorDepthPreValue
        SET_DP_RX0_COLORIMETRY_EXT_PREVALUE(pData[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        SET_DP_RX0_QUANTIZATION_PREVALUE((pData[1] & _BIT7) >> 7);
        SET_DP_RX0_COLOR_DEPTH_PREVALUE(pData[1] & (_BIT2 | _BIT1 | _BIT0));
        SET_DP_RX0_COLOR_SPACE_PREVALUE(pData[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        DebugMessageRx0("VSC DB16", pData[0]);
        DebugMessageRx0("VSC DB17", pData[1]);
    }
    else
#endif
    {
        // Get MISC Info
        pData[0] = ScalerGetByte(PB6_02_MN_STRM_ATTR_MISC);

        // Set ColorimetryPreValue & QuantizationPreValue
        SET_DP_RX0_COLORIMETRY_PREVALUE((pData[0] & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
        SET_DP_RX0_QUANTIZATION_PREVALUE((pData[0] & _BIT3) >> 3);
        SET_DP_RX0_COLOR_DEPTH_PREVALUE((pData[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
        SET_DP_RX0_COLOR_SPACE_PREVALUE((ScalerGetBit(PB6_03_MN_STRM_ATTR_MISC1, _BIT7)) | (pData[0] & (_BIT2 | _BIT1)));
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetColorInfo(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    if(GET_DP_RX0_VSC_SDP_COLOR_MODE() == _TRUE)
    {
        // Use VSC SDP
        // Set Color Space Macro
        switch(GET_DP_RX0_COLOR_SPACE_PREVALUE())
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
        ScalerDpRx0ColorimetryExtSetting();
    }
    else
#endif
    {
        switch(GET_DP_RX0_COLOR_SPACE_PREVALUE())
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
        ScalerDpRx0ColorimetrySetting();
    }

    // Get Color Depth
    if(GET_COLOR_SPACE() != _COLOR_SPACE_RAW)
    {
        switch(GET_DP_RX0_COLOR_DEPTH_PREVALUE())
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
        switch(GET_DP_RX0_COLOR_DEPTH_PREVALUE())
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
        if(GET_DP_RX0_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_LIMIT)
        {
            SET_DP_RX0_PORCH_COLOR_YCC_LIMIT();
        }
        else if(GET_DP_RX0_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_DP_RX0_PORCH_COLOR_YCC_FULL();
        }
    }
    else
    {
        SET_DP_RX0_PORCH_COLOR_RGB();
    }

    // Set Quantization Range
    ScalerDpRx0QuantizationSetting();
}

//--------------------------------------------------
// Description  : DP Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0VideoSetting(void)
{
    // Set Color Space for Display Format Gen.
    switch(GET_COLOR_SPACE())
    {
        case _COLOR_SPACE_RGB:
            DebugMessageRx0("_COLOR_SPACE_RGB", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_YCBCR444:
            DebugMessageRx0("_COLOR_SPACE_YCBCR444", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), _BIT4);
            break;

        case _COLOR_SPACE_YCBCR422:
            DebugMessageRx0("_COLOR_SPACE_YCBCR422", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), _BIT3);
            break;

        case _COLOR_SPACE_YCBCR420:
            DebugMessageRx0("_COLOR_SPACE_YCBCR420", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_Y_ONLY:
            DebugMessageRx0("_COLOR_SPACE_Y_ONLY", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            break;

        case _COLOR_SPACE_RAW:
            DebugMessageRx0("_COLOR_SPACE_RAW", 0);
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        default:
            // RGB
            ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;
    }

    // Set Color Depth for Display Format Gen.
    ScalerSetBit(PB5_20_PG_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), GET_DP_RX0_COLOR_DEPTH_PREVALUE());
    DebugMessageRx0("_COLOR_DEPTH", GET_COLOR_DEPTH());
}

//--------------------------------------------------
// Description  : DP Rx0 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ColorimetrySetting(void)
{
    BYTE ucColorimetryValue = (GET_DP_RX0_COLORIMETRY_PREVALUE() << 1);

    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ucColorimetryValue & (_BIT4 | _BIT3))
        {
            case 0:
                SET_COLORIMETRY(_COLORIMETRY_YCC_XVYCC601);
                DebugMessageRx0("_COLORIMETRY_YCC_XVYCC601", 0);
                break;

            case _BIT3:
                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT601);
                DebugMessageRx0("_COLORIMETRY_YCC_ITUR_BT601", 0);
                break;

            case _BIT4:
                SET_COLORIMETRY(_COLORIMETRY_YCC_XVYCC709);
                DebugMessageRx0("_COLORIMETRY_YCC_XVYCC709", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT709);
                DebugMessageRx0("_COLORIMETRY_YCC_ITUR_BT709", 0);
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
                DebugMessageRx0("_COLORIMETRY_RGB_SRGB_VESA", 0);
                break;

            case _BIT3:
                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageRx0("_COLORIMETRY_RGB_SRGB_CEA", 0);
                break;

            case (_BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_XRRGB);
                DebugMessageRx0("_COLORIMETRY_RGB_XRRGB", 0);
                break;

            case (_BIT4 | _BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_SCRGB);
                DebugMessageRx0("_COLORIMETRY_RGB_SCRGB", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_COLORIMETRY(_COLORIMETRY_RGB_ADOBERGB);
                DebugMessageRx0("_COLORIMETRY_RGB_ADOBERGB", 0);
                break;

            case (_BIT3 | _BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_DCI_P3);
                DebugMessageRx0("_COLORIMETRY_RGB_DCI_P3", 0);
                break;

            case (_BIT4 | _BIT3 | _BIT2 | _BIT1):
                SET_COLORIMETRY(_COLORIMETRY_RGB_COLOR_PROFILE);
                DebugMessageRx0("_COLORIMETRY_RGB_COLOR_PROFILE", 0);
                break;

            default:
                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);
                DebugMessageRx0("_COLORIMETRY_RGB_SRGB", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
    {
        SET_COLORIMETRY(_COLORIMETRY_Y_ONLY);
        DebugMessageRx0("_COLORIMETRY_Y_ONLY", 0);
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        SET_COLORIMETRY(_COLORIMETRY_RAW);
        DebugMessageRx0("_COLORIMETRY_RAW", 0);
    }
}

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx0 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0ColorimetryExtSetting(void)
{
    SET_COLORIMETRY(_COLORIMETRY_EXT);

    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(GET_DP_RX0_COLORIMETRY_EXT_PREVALUE())
        {
            case _VSC_COLORIMETRY_0:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT601);
                DebugMessageRx0("_COLORIMETRY_EXT_YCC_ITUR_BT601", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT709);
                DebugMessageRx0("_COLORIMETRY_EXT_YCC_ITUR_BT709", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC601);
                DebugMessageRx0("_COLORIMETRY_EXT_YCC_XVYCC601", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC709);
                DebugMessageRx0("_COLORIMETRY_EXT_YCC_XVYCC709", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_SYCC601);
                DebugMessageRx0("_COLORIMETRY_EXT_YCC_SYCC601", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ADOBEYCC601);
                DebugMessageRx0("_COLORIMETRY_EXT_YCC_ADOBEYCC601", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);
                DebugMessageRx0("_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL", 0);
                break;

            case _VSC_COLORIMETRY_7:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);
                DebugMessageRx0("_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL", 0);
                break;

            default:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);
                DebugMessageRx0("_COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(GET_DP_RX0_COLORIMETRY_EXT_PREVALUE())
        {
            case _VSC_COLORIMETRY_0:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SRGB);
                DebugMessageRx0("_COLORIMETRY_EXT_RGB_SRGB", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_XRRGB);
                DebugMessageRx0("_COLORIMETRY_EXT_RGB_XRRGB", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_SCRGB);
                DebugMessageRx0("_COLORIMETRY_EXT_RGB_SCRGB", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ADOBERGB);
                DebugMessageRx0("_COLORIMETRY_EXT_RGB_ADOBERGB", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_DCI_P3);
                DebugMessageRx0("_COLORIMETRY_EXT_RGB_DCI_P3", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE);
                DebugMessageRx0("_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ITUR_BT2020);
                DebugMessageRx0("_COLORIMETRY_EXT_RGB_ITUR_BT2020", 0);
                break;

            default:
                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);
                DebugMessageRx0("_COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
    {
        SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_Y_ONLY_DICOM_PART14);
        DebugMessageRx0("_COLORIMETRY_EXT_Y_ONLY_DICOM_PART14", 0);
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE);
        DebugMessageRx0("_COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE", 0);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Rx0 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0QuantizationSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        if(GET_DP_RX0_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);
            DebugMessageRx0("_YCC_QUANTIZATION_FULL_RANGE", 0);
        }
        else
        {
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);
            DebugMessageRx0("_YCC_QUANTIZATION_LIMIT_RANGE", 0);
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
        if(GET_DP_RX0_QUANTIZATION_PREVALUE() == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);
            DebugMessageRx0("_RGB_QUANTIZATION_FULL_RANGE", 0);
        }
        else
        {
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_LIMIT_RANGE);
            DebugMessageRx0("_RGB_QUANTIZATION_LIMIT_RANGE", 0);
        }

        SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);
    }
}

//--------------------------------------------------
// Description  : Check DP Misc Information
// Input Value  : None
// Output Value : True --> DP Misc Check Ok
//--------------------------------------------------
bit ScalerDpRx0MiscCheck(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    // Check MISC1[6]
    if((ScalerGetBit(PB6_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        return ScalerDpRx0VscCheck();
    }
    else
#endif
    {
        // Get MISC Info
        BYTE ucMisc0 = ScalerGetByte(PB6_02_MN_STRM_ATTR_MISC);
        BYTE ucColorSpaceValue = (ScalerGetBit(PB6_03_MN_STRM_ATTR_MISC1, _BIT7)) | (ucMisc0 & (_BIT2 | _BIT1));

        // Color Space Check
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)

        // Color format info source change from VSC --> MISC
        if(GET_DP_RX0_VSC_SDP_COLOR_MODE() == _TRUE)
        {
            switch(ucColorSpaceValue)
            {
                case _BIT1:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422)
                    {
                        DebugMessageRx0("Misc change: Color Format, _COLOR_SPACE_YCBCR422", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT2:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR444)
                    {
                        DebugMessageRx0("Misc change: Color Format, _COLOR_SPACE_YCBCR444", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT7:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_Y_ONLY)
                    {
                        DebugMessageRx0("Misc change: Color Format, _COLOR_SPACE_Y_ONLY", 0);
                        return _FALSE;
                    }
                    break;

                case (_BIT7 | _BIT1):
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_RAW)
                    {
                        DebugMessageRx0("Misc change: Color Format, _COLOR_SPACE_RAW", 0);
                        return _FALSE;
                    }
                    break;

                default:
                    if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                    {
                        DebugMessageRx0("Misc change: Color Format, _COLOR_SPACE_RGB", 0);
                        return _FALSE;
                    }
                    break;
            }
        }
        else
#endif
        {
            if(ucColorSpaceValue != GET_DP_RX0_COLOR_SPACE_PREVALUE())
            {
                DebugMessageRx0("Misc change: Color Space", 0);
                return _FALSE;
            }
        }

        // Color Depth Check
        if((((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5) != GET_DP_RX0_COLOR_DEPTH_PREVALUE())
        {
            DebugMessageRx0("Misc change: Color Depth", (((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5));
            return _FALSE;
        }

        // Colorimetry Check
        if(GET_COLORIMETRY() != _COLORIMETRY_EXT)
        {
            if(((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1) != GET_DP_RX0_COLORIMETRY_PREVALUE())
            {
                DebugMessageRx0("Misc change: Colorimetry", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_RX0_COLORIMETRY_PREVALUE((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
                    ScalerDpRx0ColorimetrySetting();
                    SET_DP_RX0_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            DebugMessageRx0("Misc change: Ext Colorimetry", 0);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX0_COLORIMETRY_PREVALUE((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1);
                ScalerDpRx0ColorimetrySetting();
                SET_DP_RX0_COLORIMETRY_CHANGED();
            }
        }

        // Dynamic Range Check
#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
        if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422))
        {
            if(((ucMisc0 & _BIT3) >> 3) != GET_DP_RX0_QUANTIZATION_PREVALUE())
            {
                DebugMessageRx0("Misc change: Dynamic Range", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_RX0_QUANTIZATION_PREVALUE((ucMisc0 & _BIT3) >> 3);
                    ScalerDpRx0QuantizationSetting();
                    SET_DP_RX0_QUANTIZATION_CHANGED();
                }
            }
        }
        else
#endif
        {
#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
            if(((ucMisc0 & _BIT3) >> 3) != GET_DP_RX0_QUANTIZATION_PREVALUE())
            {
                DebugMessageRx0("Misc change: Dynamic Range", 0);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    return _FALSE;
                }
                else
                {
                    SET_DP_RX0_QUANTIZATION_PREVALUE((ucMisc0 & _BIT3) >> 3);
                    ScalerDpRx0QuantizationSetting();
                    SET_DP_RX0_QUANTIZATION_CHANGED();
                }
            }
#endif
        }

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() == _FALSE)
#endif
        {
            // Get HSW
            ScalerRead(PB6_0E_MSA_HSW_0, 2, &pData[0], _AUTOINC);

            // Get VSW
            ScalerRead(PB6_18_MSA_VSW_0, 2, &pData[2], _AUTOINC);

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
bit ScalerDpRx0VscCheck(void)
{
    BYTE pucVscColorFormat[3];

    memset(pucVscColorFormat, 0, sizeof(pucVscColorFormat));

#if(_HW_DP_VSC_SDP_REG_SUPPORT == _ON)

    // Read DB16~18 --> pucVscColorFormat[0:2]
    ScalerRead(PB6_46_VSC15, 3, pucVscColorFormat, _AUTOINC);
#else
    if(GET_DP_RX0_RSV1_DETECTING() == _FALSE)
    {
        // Read DB16~18 --> pucVscColorFormat[0:2]
        ScalerGetDataPortByte(PB6_30_DP_INFO_FM_ADR, _DP_INFO_RSV1_DB16, 3, pucVscColorFormat, _AUTOINC);

        SET_DP_RX0_RSV1_DETECTING();

        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX0_RSV1_PACKET_DETECT);
    }
    else
    {
        return _TRUE;
    }
#endif

    // Color Space Check
    if(GET_DP_RX0_VSC_SDP_COLOR_MODE() == _FALSE)
    {
        // Color format info source change from MISC --> VSC
        switch(pucVscColorFormat[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4))
        {
            case _VSC_COLOR_SPACE_0:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    DebugMessageRx0("VSC change: Color Space, _COLOR_SPACE_RGB", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_1:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR444)
                {
                    DebugMessageRx0("VSC change: Color Space, _COLOR_SPACE_YCBCR444", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_2:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422)
                {
                    DebugMessageRx0("VSC change: Color Space, _COLOR_SPACE_YCBCR422", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_3:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR420)
                {
                    DebugMessageRx0("VSC change: Color Space, _COLOR_SPACE_YCBCR420", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_4:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_Y_ONLY)
                {
                    DebugMessageRx0("VSC change: Color Space, _COLOR_SPACE_Y_ONLY", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_5:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_RAW)
                {
                    DebugMessageRx0("VSC change: Color Space, _COLOR_SPACE_RAW", 0);
                    return _FALSE;
                }

                break;

            default:
                if(GET_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    DebugMessageRx0("VSC change: Color Space, _COLOR_SPACE_RGB", 0);
                    return _FALSE;
                }

                break;
        }
    }
    else
    {
        if((pucVscColorFormat[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) != GET_DP_RX0_COLOR_SPACE_PREVALUE())
        {
            DebugMessageRx0("VSC change: Color Space", 0);
            return _FALSE;
        }
    }

    // Color Depth Check
    if((pucVscColorFormat[1] & (_BIT2 | _BIT1 | _BIT0)) != GET_DP_RX0_COLOR_DEPTH_PREVALUE())
    {
        DebugMessageRx0("VSC change: Color Depth", 0);
        return _FALSE;
    }

    // Colorimetry Ext Check
    if(GET_COLORIMETRY() == _COLORIMETRY_EXT)
    {
        if((pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX0_COLORIMETRY_EXT_PREVALUE())
        {
            DebugMessageRx0("VSC change: Colorimetry Ext", 0);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX0_COLORIMETRY_EXT_PREVALUE(pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerDpRx0ColorimetryExtSetting();
                SET_DP_RX0_COLORIMETRY_EXT_CHANGED();
            }
        }
    }
    else
    {
        DebugMessageRx0("VSC change: Colorimetry Ext", 0);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
        {
            return _FALSE;
        }
        else
        {
            SET_DP_RX0_COLORIMETRY_EXT_PREVALUE(pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerDpRx0ColorimetryExtSetting();
            SET_DP_RX0_COLORIMETRY_EXT_CHANGED();
        }
    }

    // Dynamic Range Check
#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420))
    {
        if(((pucVscColorFormat[1] & _BIT7) >> 7) != GET_DP_RX0_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx0("VSC change: Dynamic Range", ((pucVscColorFormat[1] & _BIT7) >> 7));

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX0_QUANTIZATION_PREVALUE((pucVscColorFormat[1] & _BIT7) >> 7);
                ScalerDpRx0QuantizationSetting();
                SET_DP_RX0_QUANTIZATION_CHANGED();
            }
        }
    }
    else
#endif
    {
#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
        if(((pucVscColorFormat[1] & _BIT7) >> 7) != GET_DP_RX0_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx0("VSC change: Dynamic Range", ((pucVscColorFormat[1] & _BIT7) >> 7));

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                return _FALSE;
            }
            else
            {
                SET_DP_RX0_QUANTIZATION_PREVALUE((pucVscColorFormat[1] & _BIT7) >> 7);
                ScalerDpRx0QuantizationSetting();
                SET_DP_RX0_QUANTIZATION_CHANGED();
            }
        }
#endif
    }

    return _TRUE;
}

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
//--------------------------------------------------
// Description  : DP Rx0 VSC Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RSV1PacketDetectEvent(void)
{
    CLR_DP_RX0_RSV1_DETECTING();
}

//--------------------------------------------------
// Description  : Set DP Rx0 RSV1 infoframe type to VSC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetInitialRSV1InfoType(void)
{
    // Set Packet Type of RSV1 to VSC
    ScalerSetByte(PB6_2D_DP_INFO_FM_RSV1, _DP_SDP_TYPE_VSC);

    CLR_DP_RX0_RSV1_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_RSV1_PACKET_DETECT);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
    ScalerSetByte(PBC_54_DP_INFO_FM_RSV1, _DP_SDP_TYPE_VSC);

    CLR_DP_RX0_MST2SST_RSV1_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_MST2SST_RSV1_PACKET_DETECT);
#endif
}
#endif
#endif

//--------------------------------------------------
// Description  : HDCP Unplug Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPUnplugReset(void)
{
    ScalerDpRx0HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpRx0Hdcp2ResetProc();
#endif

    // Clear CPIRQ flag while unplug
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x01) & ~_BIT2));
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx0 Mst Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0MstReset(void)
{
    SET_DP_RX0_AUX_MANUAL_MODE();

    // Reset GUID
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x00, 0x00, (0x30 + pData[0]), 0x00);
    }

    // Disable 0x111/1C2 IRQ
    ScalerSetBit(PB7_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);

    // Clear 0x111
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x11, 0x00);

    // Clear 0x1C0 ~ 0x1C2
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0xC0, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0xC1, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0xC2, 0x00);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
    {
        // Clear 0x111 IRQ Flag
        ScalerSetBit(PB7_B3_AUX_SPECIAL_IRQ_FLAG, ~_BIT7, _BIT7);

        // Enable 0x111 IRQ
        ScalerSetBit(PB7_B2_AUX_SPECIAL_IRQ_EN, ~_BIT7, _BIT7);

        // Enable 0x01000 write IRQ
        SET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE();
    }
#else

    // Clear 0x111/1C2 IRQ Flag
    ScalerSetBit(PB7_B3_AUX_SPECIAL_IRQ_FLAG, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

    // Enable 0x111/1C2 IRQ
    ScalerSetBit(PB7_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));
#endif

    SET_DP_RX0_AUX_AUTO_MODE();

    // Disable MST
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT7, 0x00);

    // Disable Read 2C0 INT
    CLR_REG_DP_RX_2C0_IRQ();

    // Clear 0x2C0
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0xC0, 0x00);

    // Clear Payload ID Table (0x2C1 ~ 0x2FF)
    ScalerSetBit(PB7_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, _BIT6);
    ScalerSetBit(PB7_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, 0x00);

    // Reset ST1 ~ ST5
    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        // Reset Start Position
        ScalerSetByte(PB5_03_STHD_CTRL_2 + (pData[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte(PB5_04_STHD_CTRL_3 + (pData[0] << 1), 0x00);
    }

    // Reset Daisy Chain ST3 ~ ST5
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        // Reset Start Position
        ScalerSetByte(RET_REG_ADDR_DP_RX0_DAIZY_ST3_START() + (pData[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte(RET_REG_ADDR_DP_RX0_DAIZY_ST3_END() + (pData[0] << 1), 0x00);
    }

    if((GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH() == 0x01) || (GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH() == 0x01))
    {
        SET_DP_RX0_AUX_COMMAND_NO_REPLY();
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
    ScalerSetBit(PB7_D1_DP_IIC_SET, ~_BIT3, 0x00);

    // Message Upstream Disable
    CLR_REG_DP_RX_UPSTREAM_REPLY();

    // Reset Rx MSG Block
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT6, 0x00);

    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
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
// Description  : DP Rx0 Mst Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0MstReset_EXINT0(void) using 1
{
    // Reset GUID
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x00, (0x30 + pData_EXINT[0]), 0x00);
    }

    // Disable 0x111/1C2 IRQ
    ScalerSetBit_EXINT(PB7_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);

    // Clear 0x111
    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0x11, 0x00);

    // Clear 0x1C0 ~ 0x1C2
    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0xC0, 0x00);
    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0xC1, 0x00);
    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0xC2, 0x00);

    if(ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x21, _BIT0) == _BIT0)
    {
        // Clear 0x111 IRQ Flag
        ScalerSetBit_EXINT(PB7_B3_AUX_SPECIAL_IRQ_FLAG, ~_BIT7, _BIT7);

        // Enable 0x111 IRQ
        ScalerSetBit_EXINT(PB7_B2_AUX_SPECIAL_IRQ_EN, ~_BIT7, _BIT7);

        // Enable 0x01000 write IRQ
        SET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE_EXINT();
    }

    // Disable MST
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT7, 0x00);

    // Disable Read 2C0 INT
    CLR_REG_DP_RX_2C0_IRQ_EXINT();

    // Clear 0x2C0
    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0xC0, 0x00);

    // Clear Payload ID Table (0x2C1 ~ 0x2FF)
    ScalerSetBit_EXINT(PB7_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(PB7_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, 0x00);

    // Reset ST1 ~ ST5
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 5; pData_EXINT[0]++)
    {
        // Reset Start Position
        ScalerSetByte_EXINT(PB5_03_STHD_CTRL_2 + (pData_EXINT[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte_EXINT(PB5_04_STHD_CTRL_3 + (pData_EXINT[0] << 1), 0x00);
    }

    // Reset Daisy Chain ST3 ~ ST5
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 3; pData_EXINT[0]++)
    {
        // Reset Start Position
        ScalerSetByte_EXINT(RET_REG_ADDR_DP_RX0_DAIZY_ST3_START() + (pData_EXINT[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte_EXINT(RET_REG_ADDR_DP_RX0_DAIZY_ST3_END() + (pData_EXINT[0] << 1), 0x00);
    }

    if((GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH_EXINT() == 0x01) || (GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH_EXINT() == 0x01))
    {
        SET_DP_RX0_AUX_COMMAND_NO_REPLY();
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
    ScalerSetBit_EXINT(PB7_D1_DP_IIC_SET, ~_BIT3, 0x00);

    // Message Upstream Disable
    CLR_REG_DP_RX_UPSTREAM_REPLY_EXINT();

    // Reset Rx MSG Block
    ScalerSetBit_EXINT(PB7_C0_DPCD_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(PB7_C0_DPCD_CTRL, ~_BIT6, 0x00);

    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
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
bit ScalerDpRx0AuxChSourcePowerCheck(void)
{
    if(PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP() == _AUX_PN_1M_PULL_HI_LOW_SWAP_ON)
    {
        return GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP();
    }
    else
    {
        return GET_PCB_D0_DP_SOURCE_POWER();
    }
}

//--------------------------------------------------
// Description  : Dp Rx Aux Ch Power Status Check
// Input Value  : bCableStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AuxChPowerStatusCheck(bit bCableStatus)
{
    BYTE ucDebounceCnt = 0;

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if((GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_ON) && (GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT) && (g_enumDpMSTCapablePort == _DP_MST_RX0_PORT))
#else
    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
#endif
    {
        if(bCableStatus == _TRUE)
        {
            if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
            {
                // First time check power on with debounce to avoid AUX N always low case
                if((GET_DP_RX0_CHECK_AUX_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_NONE) && (ScalerDpRx0AuxChSourcePowerCheck() == _ON))
                {
                    // Debounce for 10ms
                    for(ucDebounceCnt = 0; ucDebounceCnt < 5; ucDebounceCnt++)
                    {
                        ScalerTimerDelayXms(2);

                        if(ScalerDpRx0AuxChSourcePowerCheck() == _OFF)
                        {
                            break;
                        }
                    }

                    if(ucDebounceCnt == 5)
                    {
                        SET_DP_RX0_CHECK_AUX_CH_POWER_STATUS(_DP_RX_AUX_POWER_STATUS_ON);
                    }
                }

                // Whether to Start Debounce
                if((ScalerDpRx0AuxChSourcePowerCheck() == _OFF) &&
                   (GET_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE() == _FALSE) &&
                   (GET_DP_RX0_CHECK_AUX_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_ON))
                {
                    SET_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();

                    ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                }

                // Debouncing
                if(GET_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE() == _TRUE)
                {
                    if(ScalerDpRx0AuxChSourcePowerCheck() == _ON)
                    {
                        CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                    }
                }

                // 1.5s HotPlug has been removed because NVIDIA GTX-1080 failed while HPD togglled at the moment of PC waked up from sleep.
                if((GET_DP_RX0_CHECK_AUX_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_OFF) && (ScalerDpRx0AuxChSourcePowerCheck() == _ON))
                {
                    SET_DP_RX0_CHECK_AUX_CH_POWER_STATUS(_DP_RX_AUX_POWER_STATUS_ON);

                    SET_DP_RX0_AUX_CH_POWER_ON_WAKE_UP();

                    SET_DP_RX0_SOURCE_FIRST_POWER_ON();
                }
            }
        }
        else
        {
            CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
            CLR_DP_RX0_CHECK_AUX_CH_POWER_STATUS();

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
        }
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP MST2SST Get Video Info
// Input Value  : None
// Output Value : _TRUE --> Get Successfully
//--------------------------------------------------
bit ScalerDpRx0MstToSstGetVideoInfo(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)

    CLR_DP_TX_VSC_SDP_COLOR_MODE();

    // Check MISC1[6]
    if((ScalerGetBit(PA_27_MSA_MISC_1, _BIT6)) == _BIT6)
    {
        SET_DP_TX_VSC_SDP_COLOR_MODE();

#if(_HW_DP_VSC_SDP_REG_SUPPORT == _ON)

        // Read DB16~18 --> pData[0:2]
        ScalerRead(PBC_59_VSC_RX_DB16, 3, pData, _AUTOINC);
#else
        // Delay 2 frames for SRAM ready (worst case)
        ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX * 2);

        SET_DP_RX0_MST2SST_RSV1_DETECTING();

        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX0_MST2SST_RSV1_PACKET_DETECT);

        // Read DB16~18 --> pData[0:2]
        ScalerGetDataPortByte(PBC_55_DP_INFO_FM_ADR, _DP_INFO_RSV1_DB16, 3, pData, _AUTOINC);
#endif
        // Set Color Info PreValue
        g_stDpTxColorInfo.ucColorSpacePreValue = (pData[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4));
        g_stDpTxColorInfo.b3ColorDepthPreValue = (pData[1] & (_BIT2 | _BIT1 | _BIT0));
    }
    else
#endif
    {
        // Get MISC0 Info
        pData[0] = ScalerGetByte(PA_26_MSA_MISC_0);

        // Set Color Info PreValue
        g_stDpTxColorInfo.ucColorSpacePreValue = ((ScalerGetBit(PA_27_MSA_MISC_1, _BIT7)) | (pData[0] & (_BIT2 | _BIT1)));
        g_stDpTxColorInfo.b3ColorDepthPreValue = ((pData[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP MST2SST Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0MstToSstSetColorInfo(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    if(GET_DP_TX_VSC_SDP_COLOR_MODE() == _TRUE)
    {
        // Set Color Space Macro
        switch(g_stDpTxColorInfo.ucColorSpacePreValue)
        {
            case _VSC_COLOR_SPACE_0:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;

            case _VSC_COLOR_SPACE_1:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _VSC_COLOR_SPACE_2:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _VSC_COLOR_SPACE_3:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
                break;

            case _VSC_COLOR_SPACE_4:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case _VSC_COLOR_SPACE_5:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }
    }
    else
#endif
    {
        // Set Color Space Macro
        switch(g_stDpTxColorInfo.ucColorSpacePreValue)
        {
            case _BIT1:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _BIT2:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _BIT7:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case (_BIT7 | _BIT1):
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }
    }

    // Set Porch Color
    if((GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR420))
    {
        SET_DP_TX_PORCH_COLOR_YCC_FULL();
    }
    else
    {
        SET_DP_TX_PORCH_COLOR_RGB();
    }

    // Set Color Depth Macro
    SET_DP_TX_INPUT_COLOR_DEPTH(g_stDpTxColorInfo.b3ColorDepthPreValue);
}

//--------------------------------------------------
// Description  : DP MST2SST Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0MstToSstVideoSetting(void)
{
    // Set Color Space for Display Format Gen.
    switch(GET_DP_TX_INPUT_COLOR_SPACE())
    {
        case _COLOR_SPACE_RGB:
            ScalerSetBit(PA_30_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_YCBCR444:
            ScalerSetBit(PA_30_PG_CTRL_0, ~(_BIT4 | _BIT3), _BIT4);
            break;

        case _COLOR_SPACE_YCBCR422:
            ScalerSetBit(PA_30_PG_CTRL_0, ~(_BIT4 | _BIT3), _BIT3);
            break;

        case _COLOR_SPACE_YCBCR420:
            ScalerSetBit(PA_30_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_Y_ONLY:
            ScalerSetBit(PA_30_PG_CTRL_0, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            break;

        case _COLOR_SPACE_RAW:
            ScalerSetBit(PA_30_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        default:
            // RGB
            ScalerSetBit(PA_30_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;
    }

    // Set Color depth for Display Format Gen.
    ScalerSetBit(PA_30_PG_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), (g_stDpTxColorInfo.b3ColorDepthPreValue));
}

//--------------------------------------------------
// Description  : Check DP MST2SST Misc Information
// Input Value  : None
// Output Value : True --> DP Misc Check Ok
//--------------------------------------------------
bit ScalerDpRx0MstToSstMiscCheck(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    // Check MISC1[6]
    if((ScalerGetBit(PA_27_MSA_MISC_1, _BIT6)) == _BIT6)
    {
        return ScalerDpRx0MstToSstVscCheck();
    }
    else
#endif
    {
        // Get MISC0 Info
        BYTE ucMisc0 = ScalerGetByte(PA_26_MSA_MISC_0);
        BYTE ucColorSpaceValue = (ScalerGetBit(PA_27_MSA_MISC_1, _BIT7)) | (ucMisc0 & (_BIT2 | _BIT1));

        // Color Space Check
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)

        // Color format info source change from VSC --> MISC
        if(GET_DP_TX_VSC_SDP_COLOR_MODE() == _TRUE)
        {
            switch(ucColorSpaceValue)
            {
                case _BIT1:
                    if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_YCBCR422)
                    {
                        return _FALSE;
                    }
                    break;

                case _BIT2:
                    if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_YCBCR444)
                    {
                        return _FALSE;
                    }
                    break;

                case _BIT7:
                    if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_Y_ONLY)
                    {
                        return _FALSE;
                    }
                    break;

                case (_BIT7 | _BIT1):
                    if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_RAW)
                    {
                        return _FALSE;
                    }
                    break;

                default:
                    if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_RGB)
                    {
                        return _FALSE;
                    }
                    break;
            }
        }
        else
#endif
        {
            if(ucColorSpaceValue != g_stDpTxColorInfo.ucColorSpacePreValue)
            {
                return _FALSE;
            }
        }

        // Color Depth Check
        if(ScalerGetBit(PA_28_MSA_COLOR_BIT, (_BIT2 | _BIT1 | _BIT0)) != (g_stDpTxColorInfo.b3ColorDepthPreValue))
        {
            return _FALSE;
        }

        // Get HSW
        ScalerRead(PA_16_MSA_HSW_0, 2, pData, _AUTOINC);

        // Get VSW
        ScalerRead(PA_1E_MSA_VSW_0, 2, &pData[2], _AUTOINC);

        if(((PDATA_WORD(0) & 0x7FFF) == 0x00) || ((PDATA_WORD(1) & 0x7FFF) == 0x00))
        {
            return _FALSE;
        }

        return _TRUE;
    }
}
//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDpRx0MstToSstInterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg)
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
    SET_DP_RX0_MST_TO_SST_VFRONT_PORCH(_DP_VSYNC_FRONT_PORCH);

    if(GET_DP_MST_FREESYNC_ENABLED() == _TRUE)
    {
        return _FALSE;
    }
#else
    // Set Vfront Porch
    SET_DP_RX0_MST_TO_SST_VFRONT_PORCH(_DP_VSYNC_FRONT_PORCH_MST2SST);
#endif

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
    // Field inverse disable and Clr Fake Interlace Flag
    ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));
#else
    ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT5 | _BIT4 | _BIT0), _BIT0);
#endif

    // =========== Link Clock Measure Start ===========
    PDATA_WORD(0) = ScalerDpRx0SignalDetectMeasureCount(_D0_DP_LANE0, _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_2000_CYCLE);

    if(PDATA_WORD(0) == 0)
    {
        if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR3)
        {
            PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR3;
        }
        else if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = _DP_VCO_TARGET_COUNT_2000_HBR2;
        }
        else if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
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

    DebugMessageRx0("MST Current Link Clk", ulLinkClk);
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
    SET_DP_RX0_MEASURE_POP_UP_MST2SST();

    // Get Measure Result
    ScalerRead(PA_58_MN_MEAS_CTRL, 3, &pData[5], _AUTOINC);

    // Delay 2ms To Get VBID
    ScalerTimerDelayXms(2);

    // Get VBID
    ScalerRead(PA_29_MST2SST_VBID, 1, &pData[1], _NON_AUTOINC);

    // Delay 1 frame
    ScalerTimerDelayXms((((PDATA_DWORD(1) & 0x001FFFFF) / (_GDI_CLK_KHZ)) + 2));

    // Pop up Measure Result
    SET_DP_RX0_MEASURE_POP_UP_MST2SST();

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

    DebugMessageRx0("MST HTotal Count", usHTotalCount);

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

    DebugMessageRx0("MST ####Calculated usVTotal####", usTempVTotal);

    DebugMessageRx0("7.MST DelayTime", (((PDATA_DWORD(1) & 0x000FFFFF) / (_GDI_CLK_KHZ)) + 2));
    DebugMessageRx0("7.MST Frame[N] VBS2BS Counter", PDATA_DWORD(1));
    DebugMessageRx0("7.MST Frame[N + 1] VBS2BS Counter", PDATA_DWORD(2));
    DebugMessageRx0("7.MST Frame diff ABS", (ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))));

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
        SET_DP_RX0_INTERLACE_VTT_FW_MODE_MST2SST(_ODD);

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
            SET_DP_RX0_INTERLACE_VTT_FW_MODE_MST2SST(_EVEN);

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
        SET_DP_RX0_INTERLACE_VTT_FW_MODE_MST2SST(_EVEN);

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
            ScalerSetBit(PA_56_INTERLACE_MODE_CONFIG, ~(_BIT6 | _BIT5 | _BIT0), 0x00);

            // Get Vactive
            usVactive = ((WORD)ScalerGetByte(PA_1C_MSA_VHT_0) << 8) | ScalerGetByte(PA_1D_MSA_VHT_1);

            // Set Front Porch = VTotal - Active height - MSA V Start + V Sync Pulse Width
            SET_DP_RX0_MST_TO_SST_VFRONT_PORCH(usTempVTotal - usVactive - usVstart + usVsyncWidth);

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
            DebugMessageRx0("MST Fake Interlace", 0);
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
//--------------------------------------------------
// Description  : Check DP MST2SST VSC Information
// Input Value  : None
// Output Value : True --> DP VSC Check Ok
//--------------------------------------------------
bit ScalerDpRx0MstToSstVscCheck(void)
{
    BYTE pucVscColorFormat[3];

    memset(pucVscColorFormat, 0, sizeof(pucVscColorFormat));

#if(_HW_DP_VSC_SDP_REG_SUPPORT == _ON)

    // Read DB16~18 --> pucVscColorFormat[0:2]
    ScalerRead(PBC_59_VSC_RX_DB16, 3, pucVscColorFormat, _AUTOINC);
#else
    if(GET_DP_RX0_MST2SST_RSV1_DETECTING() == _FALSE)
    {
        // Read DB16~18 --> pucVscColorFormat[0:2]
        ScalerGetDataPortByte(PBC_55_DP_INFO_FM_ADR, _DP_INFO_RSV1_DB16, 3, pucVscColorFormat, _AUTOINC);

        SET_DP_RX0_MST2SST_RSV1_DETECTING();

        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX0_MST2SST_RSV1_PACKET_DETECT);
    }
    else
    {
        return _TRUE;
    }
#endif

    // Color Space Check
    if(GET_DP_TX_VSC_SDP_COLOR_MODE() == _FALSE)
    {
        // Color format info source change from MISC --> VSC
        switch(pucVscColorFormat[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4))
        {
            case _VSC_COLOR_SPACE_0:
                if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_1:
                if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_YCBCR444)
                {
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_2:
                if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_YCBCR422)
                {
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_3:
                if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_YCBCR420)
                {
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_4:
                if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_Y_ONLY)
                {
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_5:
                if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_RAW)
                {
                    return _FALSE;
                }

                break;

            default:
                if(GET_DP_TX_INPUT_COLOR_SPACE() != _COLOR_SPACE_RGB)
                {
                    return _FALSE;
                }

                break;
        }
    }
    else
    {
        if((pucVscColorFormat[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) != g_stDpTxColorInfo.ucColorSpacePreValue)
        {
            return _FALSE;
        }
    }

    // Color Depth Check
    if((pucVscColorFormat[1] & (_BIT2 | _BIT1 | _BIT0)) != (ScalerGetBit(PA_30_PG_CTRL_0, (_BIT2 | _BIT1 | _BIT0))))
    {
        return _FALSE;
    }

    return _TRUE;
}

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
//--------------------------------------------------
// Description  : DP Rx0 MstToSst VSC Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0MstToSstRSV1PacketDetectEvent(void)
{
    CLR_DP_RX0_MST2SST_RSV1_DETECTING();
}
#endif // End of #if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
#endif // End of #if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_DP_MST_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Sink Count Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0UpdateSinkCount(BYTE ucSinkCount)
{
    BYTE ucRxPreSinkCount = ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x00);
    BYTE ucRxCurSinkCount = ((ucRxPreSinkCount & _BIT6) | ucSinkCount);

    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x00, ucRxCurSinkCount);

    if(ucSinkCount > 1)
    {
        ScalerDpRx0DfpDeviceDetailConfig();
    }
    else
    {
        ScalerDpRx0DfpDeviceDetailConfigReset();
    }

    if((ucRxPreSinkCount != ucRxCurSinkCount) && (PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH))
    {
        ScalerDpRx0SetDpcdBitValue(0x00, 0x02, 0x04, ~_BIT6, _BIT6);
        ScalerDpRx0HpdIrqAssert();
    }
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check Dp Video Straam VBID
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpRx0MSACheck(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Hactive
    ScalerRead(PB6_0C_MSA_HWD_0, 2, &pData[4], _AUTOINC);

    // Get Vactive
    ScalerRead(PB6_16_MSA_VHT_0, 2, &pData[12], _AUTOINC);

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
        ScalerRead(PB6_08_MSA_HTT_0, 2, &pData[0], _AUTOINC);

        // Get Hstart
        ScalerRead(PB6_0A_MSA_HST_0, 2, &pData[2], _AUTOINC);

        // Get HSW
        ScalerRead(PB6_0E_MSA_HSW_0, 2, &pData[6], _AUTOINC);

        // Get Vtotal
        ScalerRead(PB6_10_MSA_VTTE_0, 2, &pData[8], _AUTOINC);

        // Get Vstart
        ScalerRead(PB6_14_MSA_VST_0, 2, &pData[10], _AUTOINC);

        // Get VSW
        ScalerRead(PB6_18_MSA_VSW_0, 2, &pData[14], _AUTOINC);

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
                    if(ScalerDpRx0HdcpCheckValid() == _TRUE)
                    {
                        if(GET_DP_RX0_MSA_FAIL_MAC_RESET_COUNT() < 10)
                        {
                            ADD_DP_RX0_MSA_FAIL_MAC_RESET_COUNT();
                        }
                        else
                        {
                            CLR_DP_RX0_MSA_FAIL_MAC_RESET_COUNT();

                            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
                            ScalerTimerDelayXms(30);
                            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

                            // Delay a Complete Frame
                            ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

                            ScalerDpRx0DecodeErrorCountReset();
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

        CLR_DP_RX0_MSA_FAIL_MAC_RESET_COUNT();
    }

    // Get Mvid
    ScalerRead(PB6_1A_MSA_MVID_0, 3, pData, _AUTOINC);

    if((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) == 0x00)
    {
        return _FALSE;
    }

    // Get Nvid
    ScalerRead(PB6_1D_MSA_NVID_0, 3, pData, _AUTOINC);

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
void ScalerDpRx0FakeLTProtect(void)
{
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY);

    SET_DP_RX0_FAKE_LINK_TRAINING();

    SET_DP_RX0_AUX_MANUAL_MODE();

    if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY))
    {
        SET_DP_RX0_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
    }

    SET_DP_RX0_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Set DP RSV0 infoframe type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetInitialRSV0InfoType(void)
{
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
    // Set Freesync Info Type to RSV0
    ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, _SPD_INFO_TYPE);
#else
#if((_DP_HDR10_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
    // Set Audio Info Type to RSV0
    ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, _DP_AUDIO_TIMESTAMP);
#endif
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    CLR_DP_RX0_RSV0_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_RSV0_PACKET_DETECT);
#endif
}

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_ULTRA_HDR_SUPPORT == _ON))
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpRx0GetInfoFrameRSV0(BYTE *pucDPRx0RSV0Data)
{
    BYTE ucTemp = 0;
    BYTE ucDebounceCnt = 5;

    BYTE pucTmepData1[_HW_DP_INFOFRAME_RSV0_LENGTH];
    BYTE pucTmepData2[_HW_DP_INFOFRAME_RSV0_LENGTH];

    do
    {
        ScalerSetByte(PB6_30_DP_INFO_FM_ADR, (_DP_INFO_RSV0_DB0 + ucTemp));
        pucTmepData1[ucTemp] = ScalerGetByte(PB6_31_DP_INFO_FM_DAT);

        ucTemp ++;
    }
    while(ucTemp < _HW_DP_INFOFRAME_RSV0_LENGTH);

    do
    {
        ucTemp = 0;

        do
        {
            ScalerSetByte(PB6_30_DP_INFO_FM_ADR, (_DP_INFO_RSV0_DB0 + ucTemp));
            pucTmepData2[ucTemp] = ScalerGetByte(PB6_31_DP_INFO_FM_DAT);

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

    memcpy(pucDPRx0RSV0Data, pucTmepData2, _HW_DP_INFOFRAME_RSV0_LENGTH);
}
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP InfoFrame RSV0 Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0InfoFrameRSV0Check(void)
{
    BYTE pucDPRx0RSV0Data[_HW_DP_INFOFRAME_RSV0_LENGTH];
    BYTE ucInfoFrameType = 0;

    memset(pucDPRx0RSV0Data, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
    ScalerDpRx0GetInfoFrameRSV0(pucDPRx0RSV0Data);

#if(_DP_HDR10_SUPPORT == _ON)
    ucInfoFrameType = ScalerGetByte(PB6_2C_DP_INFO_FM_RSV0);

    if(ucInfoFrameType == _HDR_INFO_TYPE)
    {
        switch(g_ucDPRx0InfoTypeCompare)
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
            case _SPD_INFO_TYPE:

                if(GET_DP_RX0_AMD_SPD_INFO_FRAME_RECEIVED() == _TRUE)
                {
                    if(memcmp(pucDPRx0RSV0Data, g_pucDPRx0InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                    {
                        if(memcmp(g_pucDPRx0RSV0Backup, g_pucDPRx0InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                        {
                            CLR_DP_RX0_HDR_INFO_FRAME_RECEIVED();
                            memset(g_pucDPRx0HDR10Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                        }
                        else
                        {
                            // Do nothing: confuse case, keep last time status
                        }
                    }
                    else
                    {
                        SET_DP_RX0_HDR_INFO_FRAME_RECEIVED();
                        memcpy(g_pucDPRx0HDR10Backup, pucDPRx0RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                }
                else
                {
                    SET_DP_RX0_HDR_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx0HDR10Backup, pucDPRx0RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;
#endif

            case _DP_AUDIO_TIMESTAMP:

                if(GET_DP_RX0_AUDIO_INFO_FRAME_RECEIVED() == _TRUE)
                {
                    // Maud:[0:15], Naud:[16:31] is constant, Check Naud (arrary[16:27])
                    if(memcmp(&pucDPRx0RSV0Data[16], &g_pucDPRx0InfoTemp[16], 12) == 0)
                    {
                        if(memcmp(g_pucDPRx0RSV0Backup, g_pucDPRx0InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                        {
                            CLR_DP_RX0_HDR_INFO_FRAME_RECEIVED();
                            memset(g_pucDPRx0HDR10Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                        }
                        else
                        {
                            // Do nothing: confuse case, keep last time status
                        }
                    }
                    else
                    {
                        SET_DP_RX0_HDR_INFO_FRAME_RECEIVED();
                        memcpy(g_pucDPRx0HDR10Backup, pucDPRx0RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                }
                else
                {
                    SET_DP_RX0_HDR_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx0HDR10Backup, pucDPRx0RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;

            default:
                break;
        }
    }
    else
    {
        switch(g_ucDPRx0InfoTypeCompare)
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
            case _SPD_INFO_TYPE:

                if(memcmp(pucDPRx0RSV0Data, g_pucDPRx0InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                {
                    if(memcmp(g_pucDPRx0HDR10Backup, g_pucDPRx0InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                    {
                        CLR_DP_RX0_AMD_SPD_INFO_FRAME_RECEIVED();
                        memset(g_pucDPRx0RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                    else
                    {
                        // Do nothing: confuse case, keep last time status
                    }
                }
                else
                {
                    SET_DP_RX0_AMD_SPD_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx0RSV0Backup, pucDPRx0RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;
#endif

            case _DP_AUDIO_TIMESTAMP:

                if(memcmp(pucDPRx0RSV0Data, g_pucDPRx0InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                {
                    if(memcmp(g_pucDPRx0HDR10Backup, g_pucDPRx0InfoTemp, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
                    {
                        CLR_DP_RX0_AUDIO_INFO_FRAME_RECEIVED();
                        memset(g_pucDPRx0RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
                    }
                    else
                    {
                        // Do nothing: confuse case, keep last time status
                    }
                }
                else
                {
                    SET_DP_RX0_AUDIO_INFO_FRAME_RECEIVED();
                    memcpy(g_pucDPRx0RSV0Backup, pucDPRx0RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
                }

                break;

            default:
                break;
        }
    }

    ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, ScalerDpRx0SelectInfoFrameType(ucInfoFrameType));

    // Get infoframe after switch infoframe header for check
    ScalerDpRx0GetInfoFrameRSV0(g_pucDPRx0InfoTemp);
#else
    ucInfoFrameType = ucInfoFrameType;
#endif
}

//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RSV0PacketDetectEvent(void)
{
    CLR_DP_RX0_RSV0_DETECTING();
}

//--------------------------------------------------
// Description  : DP InfoFrame RSV0 initial setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0InfoFrameRSV0Initial(void)
{
#if(_DP_HDR10_SUPPORT == _ON)
    CLR_DP_RX0_HDR_INFO_FRAME_RECEIVED();

    // Get RSV0 Infoframe
    ScalerDpRx0GetInfoFrameRSV0(g_pucDPRx0RSV0Backup);

    // Get Compare with HDR infoframe type
    g_ucDPRx0InfoTypeCompare = ScalerGetByte(PB6_2C_DP_INFO_FM_RSV0);

    // Set DP RSV0 info type: HDR
    ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, _HDR_INFO_TYPE);

    // Get infoframe after switch infoframe header for check
    ScalerDpRx0GetInfoFrameRSV0(g_pucDPRx0InfoTemp);
#endif
}
#endif // End of #if(_DP_ULTRA_HDR_SUPPORT == _ON)

#if(_DP_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Select InfoFrame Type
// Input Value  : None
// Output Value : InfoFrame Type
//--------------------------------------------------
BYTE ScalerDpRx0SelectInfoFrameType(BYTE ucInfoFrameTypeCurrent)
{
    BYTE ucInfoFrameTypeNext = 0;

    if(ucInfoFrameTypeCurrent == _HDR_INFO_TYPE)
    {
        ucInfoFrameTypeNext = g_ucDPRx0InfoTypeCompare;
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
void ScalerDpRx0SwitchHDR10CmpAudioInfo(void)
{
    BYTE pucRSV0Data1[_HW_DP_INFOFRAME_RSV0_LENGTH];
    BYTE pucRSV0Data2[_HW_DP_INFOFRAME_RSV0_LENGTH];

    memset(pucRSV0Data1, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
    memset(pucRSV0Data2, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_RX0_AMD_SPD_INFO_FRAME_RECEIVED() == _TRUE)
    {
        CLR_DP_RX0_AUDIO_INFO_FRAME_RECEIVED();
    }
    else
#endif
    {
        // Set Audio Info Type to RSV0
        ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, _DP_AUDIO_TIMESTAMP);

        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        ScalerDpRx0GetInfoFrameRSV0(pucRSV0Data1);

        // check pucRSV0Data1 not all 0
        if(memcmp(pucRSV0Data1, pucRSV0Data2, _HW_DP_INFOFRAME_RSV0_LENGTH) != 0)
        {
            // Get MSA Naud
            pucRSV0Data2[16] = ScalerGetByte(PB6_23_MSA_NAUD_0);
            pucRSV0Data2[17] = ScalerGetByte(PB6_24_MSA_NAUD_1);
            pucRSV0Data2[18] = ScalerGetByte(PB6_25_MSA_NAUD_2);
            pucRSV0Data2[19] = 0x00;

            // Check Audio time stamp info
            if((memcmp(&pucRSV0Data1[16], &pucRSV0Data2[16], 4) == 0) &&
               (memcmp(&pucRSV0Data1[16], &pucRSV0Data1[20], 4) == 0) &&
               (memcmp(&pucRSV0Data1[16], &pucRSV0Data1[24], 4) == 0))
            {
                SET_DP_RX0_AUDIO_INFO_FRAME_RECEIVED();
                memcpy(g_pucDPRx0RSV0Backup, pucRSV0Data1, _HW_DP_INFOFRAME_RSV0_LENGTH);
            }
            else
            {
                CLR_DP_RX0_AUDIO_INFO_FRAME_RECEIVED();
                memset(g_pucDPRx0RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
            }
        }
        else
        {
            CLR_DP_RX0_AUDIO_INFO_FRAME_RECEIVED();
            memset(g_pucDPRx0RSV0Backup, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);
        }

        // Get Compare with HDR infoframe type
        g_ucDPRx0InfoTypeCompare = ScalerGetByte(PB6_2C_DP_INFO_FM_RSV0);

        // Set DP RSV0 info type: HDR
        ScalerSetByte(PB6_2C_DP_INFO_FM_RSV0, _HDR_INFO_TYPE);

        // Get infoframe after switch infoframe header for check
        ScalerDpRx0GetInfoFrameRSV0(g_pucDPRx0InfoTemp);
    }
}
#endif
#endif // End of #if(_DP_HDR10_SUPPORT == _ON)

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0DecodeErrorCountReset_WDINT(void) using 3
{
    // Reset 8b10b Error Count Value
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Start Record 8b10b Error Count Value
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
}
#endif
#endif // End of #if(_D0_DP_EXIST == _ON)
