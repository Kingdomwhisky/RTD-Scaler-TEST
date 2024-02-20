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
// ID Code      : ScalerDPRx1_SeptPhy.c No.0000
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
#if(_D1_DP_EXIST == _ON)
BYTE g_ucDpRx1PhyCtsCtrl;
EnumHDCPType g_enumDpRx1HdcpMode;
StructDpLanesMapping g_stDpRx1LanesMapping;

#if(_DP_MST_SUPPORT == _ON)
StructDPRxMiscInfo g_stDpRx1MiscInfo;
BYTE g_pucDpRx1MstTimeSlotBackup[13];
BYTE g_pucDpMacRx1MstStMuxBackup[5];
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
StructDpLinkInfo g_stDpRx1LinkInfo;
#endif

bit g_bDpRx1Tp1Initial = _FALSE;
BYTE g_ucDpRx1LTPatternSet;
BYTE g_ucDpRx1Tp1PermitSwingLevel0;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpRx1AVMute(void);
void ScalerDpRx1AdjustVsyncDelay(void);
bit ScalerDpRx1AlignCheck(void);
void ScalerDpRx1ScrambleSetting(void);

#if((_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON) && (_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON))
bit ScalerDpRx1LaneValidCheck(void);
#endif

void ScalerDpRx1CheckHdcpCpirqStatus(void);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
bit ScalerDpRx1CheckVgipVsBypass(void);
#endif

void ScalerDpRx1CrcCalculate(void);

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
void ScalerDpRx1CalculateLinkRate(EnumDpLaneCount enumDpLaneCount);
#endif

#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
void ScalerDpRx1HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
#endif
void ScalerDpRx1SetNoVideoStreamIRQ(bit bEn);
void ScalerDpRx1DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);
DWORD ScalerDpRx1GetBStoVSDelay(void);
BYTE ScalerDpRx1GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
BYTE ScalerDpRx1GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
bit ScalerDpRx1GetVideoStream(void);
EnumDpHotPlugTime ScalerDpRx1BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType);
void ScalerDpRx1AfterHpdToggleProc(void);
void ScalerDpRx1Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
bit ScalerDpRx1MarginLinkCheck(void);
void ScalerDpRx1LinkStatusIRQ(void);
void ScalerDpRx1AuxSet(void);
void ScalerDpRx1ErrorCounterUpdate_EXINT0(void);
void ScalerDpRx1ErrorCounterDisable_EXINT0(void);
void ScalerDpRx1ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType);

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
bit ScalerDpRx1DecodeErrorCountCheck(WORD usTimeCriteria, BYTE ucErrorCriteria);
bit ScalerDpRx1DecodeErrorCountLaneMeasure(BYTE ucErrorCriteria, BYTE ucDpRx1LaneNumber);
bit ScalerDpRx1LaneBsCheck(void);
#endif

bit ScalerDpRx1MSAActiveChange(void);
bit ScalerDpRx1PSPreDetect(void);
void ScalerDpRx1SetDpLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation);
void ScalerDpRx1SecDataBlockReset(void);
void ScalerDpRx1SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
void ScalerDpRx1SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
void ScalerDpRx1SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
void ScalerDpRx1ChangeHdcpDpcdCapability(bit bEn);

#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
void ScalerDpRx1ASSRModeSetting(void);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
bit ScalerDpRx1GetFREESYNCStatusChange(void);
void ScalerDpRx1SetFREESYNCMsaForLut(WORD usDpHtotal);
#endif

#if(_DP_MST_SUPPORT == _ON)
void ScalerDpRx1MstInfoBackup(EnumDpMstBackup enumDpMstBackup);

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRx1HDCPAuthShaRun(bit bIsFirst);
void ScalerDpRx1HDCPChangeAuthState(EnumDPRxHDCPAuthState enumHDCPAuthState);
bit ScalerDpRx1HDCPCheckBinfo(void);
bit ScalerDpRx1HDCPCheckLvp(void);
void ScalerDpRx1HDCPFakeAuthenProc(void);
void ScalerDpRx1HDCPHandler(void);
void ScalerDpRx1HDCPLoadKsvFifo(void);
void ScalerDpRx1HDCPLoadShaToDpcd(void);
void ScalerDpRx1HDCPSetKsvFifoFirst(void);
void ScalerDpRx1HDCPSetReadIrqTimeout(void);
void ScalerDpRx1HDCPSetRepeaterProcTimeout(void);
void ScalerDpRx1HDCPSha1Calculate(BYTE *pucInputArray, BYTE ucCalCount);
void ScalerDpRx1HDCPWriteShaInput(void);
#if(_DP_HDCP14_CTS_SUPPORT == _ON)
bit ScalerDpRx1HDCPDeviceCountChange(void);
#endif
void ScalerDpRx1MstToSstProc(void);
void ScalerDpRx1MstToSstSetColorInfo(void);
bit ScalerDpRx1MstToSstStableDetect(void);
#endif

#endif

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRx1UpdateSinkCount(BYTE ucSinkCount);
#endif

void ScalerDpRx1AdjustLaneFLDBand(BYTE ucDpRx1LaneNumber, WORD usVCOBandDiff);
bit ScalerDpRx1CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
void ScalerDpRx1CpIRQ(EnumDpRxBStatusType enumBStatusType);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
void ScalerDpRx1CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType);
#endif
bit ScalerDpRx1DFECheck(void);
bit ScalerDpRx1DecodeCheck(void);
bit ScalerDpRx1DisplayFormatSetting(void);
bit ScalerDpRx1FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
void ScalerDpRx1HDCPBlockReset(void);
bit ScalerDpRx1HdcpCheckValid(void);
bit ScalerDpRx1HdcpCheckEnabled(void);
bit ScalerDpRx1HdcpMeasureCheck(void);
bit ScalerDpRx1HdcpReAuthStatusCheck(void);
void ScalerDpRx1MacInitial(void);
bit ScalerDpRx1MeasureLaneCDRClk(BYTE ucDpLinkRate, BYTE ucDpRx1LaneNumber);

#if(_DP_LINK_RATE_CHANGE_WO_LT_SUPPORT == _ON)
void ScalerDpRx1LinkRateChangeRebuildPhy(void);
bit ScalerDpRx1LinkRateChange(void);
#endif

bit ScalerDpRx1NormalPreDetect(void);
bit ScalerDpRx1PhyCtsTp1Check(void);
bit ScalerDpRx1PhyCtsTp2Check(void);
void ScalerDpRx1PhyInitial(void);
BYTE ScalerDpRx1ScanInputPort(void);
void ScalerDpRx1SetDFEInitial(EnumDpLinkRate enumDpLinkRate);
void ScalerDpRx1SetFifoIRQ(bit bEn);
void ScalerDpRx1SetFifoWD(bit bEn);
bit ScalerDpRx1StableDetect(void);
void ScalerDpRx1ValidSignalDetectionActiveEvent(void);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
void ScalerDpRx1TimingInfoBackup(void);
#endif

#if(_DP_MST_SUPPORT == _ON)
bit ScalerDpRx1LTStatusCheck(void);

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRx1HDCPEnableReadIrq(bit bEnable);
void ScalerDpRx1MstToSstAdjustVsyncDelay(void);
bit ScalerDpRx1MstToSstDisplayFormatSetting(void);
bit ScalerDpRx1MstToSstFifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
DWORD ScalerDpRx1MstToSstGetBStoVSDelay(void);
bit ScalerDpRx1MstToSstGetVideoInfo(void);
bit ScalerDpRx1MstToSstGetVideoStream(void);
bit ScalerDpRx1MstToSstMSAActiveChange(void);
bit ScalerDpRx1MstToSstMSACheck(void);
bit ScalerDpRx1MstToSstMeasureInput(void);
bit ScalerDpRx1MstToSstMiscCheck(void);
BYTE ScalerDpRx1MstToSstScanInputPort(void);
void ScalerDpRx1MstToSstVideoSetting(void);

#if(_DP_FREESYNC_SUPPORT == _ON)
WORD ScalerDpRx1MstToSstGetBStoHSDelay(WORD usDpHtotal);
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit ScalerDpRx1MstToSstVscCheck(void);
#endif

void ScalerDpRx1DfpDeviceDetailConfigReset(void);
void ScalerDpRx1DfpDeviceDetailConfig(void);
#endif

#endif
StructDpRxErrorCount ScalerDpRx1GetErrorCount(void);

#endif // #End of #if(_D1_DP_EXIST == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D1_DP_EXIST == _ON)
//--------------------------------------------------
// Description  : DP RGB Output Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AVMute(void)
{
    if(ScalerGetBit(PB9_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Set free run & force to BG
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT5 | _BIT3), _BIT5);
    }

    // Disable fifo overflwo/ underflwo IRQ
    ScalerSetBit(PB9_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

    // Disable RGB Output
    ScalerSetBit(PB8_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#if(_AUDIO_SUPPORT == _ON)
    // Disable Audio Channel
    ScalerAudioDpAudioEnable(_DISABLE, _D1_INPUT_PORT);
#endif
}
//--------------------------------------------------
// Description  : DP Adjust Vsync Delay
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AdjustVsyncDelay(void)
{
    DWORD ulBStoVSDelayDeltaOverflow = 0;
    DWORD ulBStoVSDelayDeltaUnderflow = 0;

    if(ScalerGetBit(PB8_21_PG_CTRL_1, (_BIT1 | _BIT0)) == 0x00)// Fifo Ok
    {
        return;
    }
    else if(ScalerGetBit(PB8_21_PG_CTRL_1, _BIT0) == _BIT0) // Fifo Overflow
    {
        // Get Htotal
        ScalerRead(PB9_08_MSA_HTT_0, 2, &pData[0], _AUTOINC);

        // ((Link Clk * 256)/ Stream CLK) * Htotal / 256 --> 1 Line
        ulBStoVSDelayDeltaOverflow = (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 270UL) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(0)) / 256;

        DebugMessageRx1("7. Fifo Overflow --> nVidia Case", ulBStoVSDelayDeltaOverflow);
    }
    else if(ScalerGetBit(PB8_21_PG_CTRL_1, _BIT1) == _BIT1) // Fifo Underflow
    {
        // Get Hactive
        ScalerRead(PB9_0C_MSA_HWD_0, 2, &pData[0], _AUTOINC);

        if(PDATA_WORD(0) != 1366)
        {
            return;
        }

        PDATA_WORD(0) = PDATA_WORD(0) - 2;

        // Set Hactive
        ScalerSetByte(PB8_45_MN_DPF_HWD_M, pData[0]);
        ScalerSetByte(PB8_46_MN_DPF_HWD_L, pData[1]);

        // ((Link Clk * 2)/ Stream CLK) --> 2 pixels
        ulBStoVSDelayDeltaUnderflow = (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 270) * 2) / ((DWORD)GET_INPUT_PIXEL_CLK());

        DebugMessageRx1("7. Fifo Underflow --> QD882 Case", ulBStoVSDelayDeltaUnderflow);
    }

    // For Initial Value Before Use PDATA_DWORD(0)
    pData[0] = 0;

    // Get BStoVSDelay Even
    ScalerRead(PB8_32_EVBLK2VS_H, 3, &pData[1], _AUTOINC);

    // For Initial Value Before Use PDATA_DWORD(1)
    pData[4] = 0;

    // Get BStoVSDelay Odd
    ScalerRead(PB8_35_OVBLK2VS_H, 3, &pData[5], _AUTOINC);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    PDATA_DWORD(0) = PDATA_DWORD(0) - ((ulBStoVSDelayDeltaOverflow + ulBStoVSDelayDeltaUnderflow) / 2);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    PDATA_DWORD(1) = PDATA_DWORD(1) - ((ulBStoVSDelayDeltaOverflow + ulBStoVSDelayDeltaUnderflow) / 2);

    // Set Even Field BS to VS Delay
    ScalerSetByte(PB8_32_EVBLK2VS_H, pData[1]);
    ScalerSetByte(PB8_33_EVBLK2VS_M, pData[2]);
    ScalerSetByte(PB8_34_EVBLK2VS_L, pData[3]);

    // Set Odd Field BS to VS Delay
    ScalerSetByte(PB8_35_OVBLK2VS_H, pData[5]);
    ScalerSetByte(PB8_36_OVBLK2VS_M, pData[6]);
    ScalerSetByte(PB8_37_OVBLK2VS_L, pData[7]);

    // Enable Double Buffer
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT6, _BIT6);

    // Reset Display Format Gen
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT7, _BIT7);

    // Polling Vertical BS
    ScalerTimerPollingFlagProc(50, PB9_01_DP_VBID, _BIT0, _TRUE);

    // Delay for PG Stable
    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);
}
//--------------------------------------------------
// Description  : Check Valid Lane Alignment
// Input Value  : None
// Output Value : True --> Align
//--------------------------------------------------
bit ScalerDpRx1AlignCheck(void)
{
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)

    if(GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE)
    {
        if(GET_DP_RX1_SOURCE_TYPE_JUDGE() == _FALSE)
        {
#if(_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON)
            if(ScalerDpRx1LaneValidCheck() == _FALSE)
            {
                return _TRUE;
            }
#else
            return _TRUE;
#endif
        }
    }

#endif

    if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F) == _DP_ONE_LANE)
    {
        return _TRUE;
    }
    else
    {
        if(ScalerGetBit(PB0_0E_DESKEW_PHY, _BIT4) == 0x00)
        {
            if(ScalerGetBit(PB0_0E_DESKEW_PHY, (_BIT7 | _BIT6)) != (_BIT7 | _BIT6))
            {
                ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                ScalerTimerDelayXms(3);
            }
            else
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Scramble Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ScrambleSetting(void)
{
    BYTE ucBackUp = ScalerGetByte(PBA_D0_AUX_MODE_SET);
    bit bEnhanceChange = _FALSE;
    bit bScrambleChange = _FALSE;

    SET_DP_RX1_AUX_MANUAL_MODE();

    if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x01, _BIT7) == _BIT7) != (ScalerGetBit(PB0_01_PHY_DIG_RESET_CTRL, _BIT2) == _BIT2))
    {
        bEnhanceChange = _TRUE;

        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x01, _BIT7) == _BIT7)
        {
            // Enable Enhancement Control Mode --> MAC
            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
        }
        else
        {
            // Disable Enhancement Control Mode --> MAC
            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
        }
    }

    if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x02, _BIT5) == _BIT5) != (ScalerGetBit(PB0_07_SCRAMBLE_CTRL, _BIT5) == _BIT5))
    {
        bScrambleChange = _TRUE;

        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x02, _BIT5) == _BIT5)
        {
            // Disable Scrambling
            ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
        }
        else
        {
            // Enable Scrambling
            ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
        }
    }

    if((bEnhanceChange == _TRUE) || (bScrambleChange == _TRUE))
    {
        SET_DP_RX1_AUX_AUTO_MODE();

        // Delay 2ms for Scramble
        ScalerTimerDelayXms(2);

        SET_DP_RX1_AUX_MANUAL_MODE();
    }

    if((ucBackUp & _BIT1) == _BIT1)
    {
        SET_DP_RX1_AUX_AUTO_MODE();
    }
}

#if((_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON) && (_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Check Lane Valid
// Input Value  : None
// Output Value : True --> ok, False --> Lane Valid Error
//--------------------------------------------------
bit ScalerDpRx1LaneValidCheck(void)
{
    // Enable Lane Valid Detect
    ScalerSetBit(PB0_00_HD_DP_SEL, ~_BIT3, 0x00);
    ScalerSetBit(PB0_00_HD_DP_SEL, ~_BIT3, _BIT3);

    // Delay Time us [150,x]
    DELAY_XUS(150);

    switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_ONE_LANE:

            if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT7) == 0x00)) ||
               ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT6) == 0x00)) ||
               ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT5) == 0x00)) ||
               ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit(PB0_00_HD_DP_SEL, _BIT4) == 0x00)))
            {
                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            if(((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                (ScalerGetBit(PB0_00_HD_DP_SEL, (_BIT7 | _BIT6)) == 0x00)) ||
               ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                (ScalerGetBit(PB0_00_HD_DP_SEL, (_BIT7 | _BIT5)) == 0x00)) ||
               ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                (ScalerGetBit(PB0_00_HD_DP_SEL, (_BIT7 | _BIT4)) == 0x00)) ||
               ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                (ScalerGetBit(PB0_00_HD_DP_SEL, (_BIT6 | _BIT5)) == 0x00)) ||
               ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                (ScalerGetBit(PB0_00_HD_DP_SEL, (_BIT6 | _BIT4)) == 0x00)) ||
               ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2))) &&
                (ScalerGetBit(PB0_00_HD_DP_SEL, (_BIT5 | _BIT4)) == 0x00)))
            {
                return _FALSE;
            }

            break;

        case _DP_FOUR_LANE:

            if(ScalerGetBit(PB0_00_HD_DP_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
            {
                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Clear CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CheckHdcpCpirqStatus(void)
{
    if((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
    {
        if((ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) & _BIT2) == _BIT2)
        {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Check HDCP22 decode
            if(GET_DP_RX1_HDCP_MODE() == _HDCP_22)
            {
                if(ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) == 0x00)
                {
                    // Clear Link Status CPIRQ Flag
                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) & ~_BIT2));
                }
            }
            else
#endif
            {
                if(ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) == 0x00)
                {
                    // Clear Link Status CPIRQ Flag
                    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) & ~_BIT2));
                }
            }
        }
    }
}

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check VGIP VS bypass for DP
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpRx1CheckVgipVsBypass(void)
{
    // Get Hstart
    ScalerRead(PB8_43_MN_DPF_HST_M, 2, &pData[0], _AUTOINC);

    // Get Vstart
    ScalerRead(PB8_4B_MN_DPF_VST_M, 2, &pData[2], _AUTOINC);

    // Check for nVedia 2560x1440@144Hz timing (reduced blanking)
    if((PDATA_WORD(0) < _VGIP_IH_CAPTURE_MIN_VALUE) ||
       (PDATA_WORD(1) <= _VGIP_IV_CAPTURE_MIN_VALUE))
    {
        DebugMessageRx1("DP RX1 VGIP VS Bypass Mode", PDATA_WORD(0));

        return _TRUE;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DP CRC Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CrcCalculate(void)
{
    if(GET_DP_RX1_CRC_CALCULATE() == _TRUE)
    {
        DebugMessageRx1("7. DP CRC Test Start", 0);

        if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
        {
            ScalerSetBit(PB8_70_DP_CRC_CTRL, ~_BIT4, _BIT4);
        }
        else
        {
            ScalerSetBit(PB8_70_DP_CRC_CTRL, ~_BIT4, 0x00);
        }

        // Start CRC Calculation
        ScalerSetBit(PB8_70_DP_CRC_CTRL, ~_BIT7, _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_70_DP_CRC_CTRL, _BIT6, _TRUE) == _TRUE)
        {
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x40, ScalerGetByte(PB8_72_DP_CRC_R_L));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x41, ScalerGetByte(PB8_71_DP_CRC_R_M));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x42, ScalerGetByte(PB8_74_DP_CRC_G_L));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x43, ScalerGetByte(PB8_73_DP_CRC_G_M));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x44, ScalerGetByte(PB8_76_DP_CRC_B_L));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x45, ScalerGetByte(PB8_75_DP_CRC_B_M));

            CLR_DP_RX1_CRC_CALCULATE();

            // Update _TEST_CRC_COUNT
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x46, 0x21);
        }

        // Stop CRC Calculation
        ScalerSetBit(PB8_70_DP_CRC_CTRL, ~_BIT7, 0x00);
    }
}

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Link Rate Set
// Input Value  : MST Port and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CalculateLinkRate(EnumDpLaneCount enumDpLaneCount)
{
    BYTE ucLinkRate = 0;

    if((ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x00) >= _DP_VERSION_1_2) || (ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7))
    {
        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == 0x00)
        {
#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

            ucLinkRate = DP_LINK_RATE_ADJUST(enumDpLaneCount, _INPUTCLOCK_RANG_USBC);

            if(ucLinkRate > _D1_DP_LINK_CLK_RATE)
            {
                ucLinkRate = _D1_DP_LINK_CLK_RATE;
            }

            if(ucLinkRate >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, ucLinkRate);
            }

            // When Define Extended Rx Cap Should Set DPCD 0x02201
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, ucLinkRate);
#else
            g_ucDpRx1DPCD02201hValue = ucLinkRate;
#endif

#else // Else of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

            ucLinkRate = DP_LINK_RATE_ADJUST(enumDpLaneCount, _INPUTCLOCK_RANG_DP);

            if(ucLinkRate > _D1_DP_LINK_CLK_RATE)
            {
                ucLinkRate = _D1_DP_LINK_CLK_RATE;
            }

            if(ucLinkRate >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, ucLinkRate);
            }

            // When Define Extended Rx Cap Should Set DPCD 0x02201
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, ucLinkRate);
#else
            g_ucDpRx1DPCD02201hValue = ucLinkRate;
#endif

#endif // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        }
        else
        {
            if(_D1_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _D1_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, _D1_DP_LINK_CLK_RATE);
#else
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            g_ucDpRx1DPCD02201hValue = _D1_DP_LINK_CLK_RATE;
#endif
        }
    }
}
#endif

#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
//--------------------------------------------------
// Description  : DP Hs Tracking Active Region Setting
// Input Value  : Hs Tracking Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType)
{
    if(enumHSTrackingType == _DP_HS_TRACKING_FW_MODE)
    {
        // HS Tracking Region By FW Setting
        ScalerSetBit(PB8_B9_MN_SCLKG_SDM_TEST, ~_BIT7, _BIT7);

        // BE Start Num = 2 line
        ScalerSetBit(PB8_C7_VBID_MAN_MADE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

        // BE End Num = 2 line
        ScalerSetBit(PB8_C7_VBID_MAN_MADE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // HS Tracking Region By FW Setting
        ScalerSetBit(PB8_B9_MN_SCLKG_SDM_TEST, ~_BIT7, 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetNoVideoStreamIRQ(bit bEn)
{
    // VB-ID[3] Change Flag
    ScalerSetBit(PB9_36_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

    // VB-ID[3] Change IRQ
    ScalerSetBit(PB9_3B_DP_IRQ_CTRL1, ~_BIT4, ((bEn == _ENABLE) ? _BIT4 : 0x00));
}

//--------------------------------------------------
// Description  : DPCD Link Status Field Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus)
{
    DebugMessageRx1("DP Rx1 Dpcd Link Status Reset", 0);

    pData[0] = ScalerGetByte(PBA_D0_AUX_MODE_SET);

    SET_DP_RX1_AUX_MANUAL_MODE();

    if(enumDpResetStatus == _DP_DPCD_LINK_STATUS_INITIAL)
    {
        // Set DPCD 00600h to 0x01
        ScalerDpRx1SetDpcdBitValue(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x04, 0x80);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x06, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x07, 0x00);

    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    CLR_DP_RX1_BACKUP_PD_LINK_STATUS_FLG();

    if((pData[0] & _BIT1) == _BIT1)
    {
        SET_DP_RX1_AUX_AUTO_MODE();
    }

#if(_DP_MST_SUPPORT == _ON)

    if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        pData[0] = ScalerGetByte(PBA_D0_AUX_MODE_SET);

        SET_DP_RX1_AUX_AUTO_MODE();

        pData[1] = ScalerDpRx1GetDpcdInfo(0x00, 0x20, 0x05);
        ScalerDpRx1SetDpcdValue(0x00, 0x20, 0x05, (pData[1] | _BIT1));

        ScalerDpRx1SetDpcdValue(0x00, 0x02, 0xC0, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0xC0) & ~_BIT1));

        if((pData[0] & _BIT1) != _BIT1)
        {
            SET_DP_RX1_AUX_MANUAL_MODE();
        }
    }

#endif
}
//--------------------------------------------------
// Description  : DP BS to VS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
DWORD ScalerDpRx1GetBStoVSDelay(void)
{
    DWORD ulVFrontPorch = 0;
    DWORD ulHFrontPorch = 0;
    WORD usFifoOffset = 0;

    // Get Htotal
    ScalerRead(PB9_08_MSA_HTT_0, 2, &pData[2], _AUTOINC);

    // VFrontPorch = 3 * Htotal * (Link Clk / Stream CLK)
    ulVFrontPorch = ((DWORD)GET_DP_RX1_VFRONT_PORCH()) * ((DWORD)PDATA_WORD(1) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) *
                    ((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 270) / 256;

    // Get Hactive
    ScalerRead(PB9_0C_MSA_HWD_0, 2, pData, _AUTOINC);

    // Get HSW
    pData[4] = ScalerGetBit(PB9_0E_MSA_HSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    pData[5] = ScalerGetByte(PB9_0F_MSA_HSW_1);

    // Get HSW min by Measure clock
    PDATA_WORD(3) = ((DWORD) _DP_HSYNC_WIDTH_MEASURE_COUNTER * GET_INPUT_PIXEL_CLK() * 100) / _MEASURE_CLK + 1;

    // Check HSW <= HSW min
    if(PDATA_WORD(2) <= PDATA_WORD(3))
    {
        // Check if H porch is more than HSW min
        if((PDATA_WORD(1) - PDATA_WORD(0)) >= PDATA_WORD(3))
        {
            // HSW = HSW min
            PDATA_WORD(2) = PDATA_WORD(3);
        }
        else
        {
            // HSW = Max H Porch
            PDATA_WORD(2) = (PDATA_WORD(1) - PDATA_WORD(0));
        }
    }

    // DPF H Front Porch must not be less than 8 (HW constraint)
    // Check if H porch is more than 8
    if((PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(2)) <= _DP_HSYNC_FRONT_PORCH)
    {
        // HSW < HSW min
        if(PDATA_WORD(2) < PDATA_WORD(3))
        {
            // Hstart = HSW
            PDATA_WORD(4) = PDATA_WORD(2);
        }
        else if((PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(3) >= _DP_HSYNC_FRONT_PORCH))
        {
            // HSW = H porch - _DP_HSYNC_FRONT_PORCH
            PDATA_WORD(2) = PDATA_WORD(1) - PDATA_WORD(0) - _DP_HSYNC_FRONT_PORCH;

            // Hstart = HSW
            PDATA_WORD(4) = PDATA_WORD(2);
        }
        else
        {
            // HSW = HSW min
            PDATA_WORD(2) = PDATA_WORD(3);

            // Hstart = HSW min
            PDATA_WORD(4) = PDATA_WORD(3);
        }
    }
    else
    {
        // Hstart = Htotal - Hactive - _DP_HSYNC_FRONT_PORCH
        PDATA_WORD(4) = PDATA_WORD(1) - PDATA_WORD(0) - _DP_HSYNC_FRONT_PORCH;
    }

    // HFrontPorch = (Htotal - Hactive - Hstart) * (Link Clk / Stream CLK)
    ulHFrontPorch = (((DWORD)(PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(4))) * (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_INPUT_PIXEL_CLK()));

    pData[15] = GET_COLOR_DEPTH();

    // DP fifo size = 256 x 96bit
    if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
    {
        // FifoOffset = (1/2 * (256 * 96) / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (4 * (WORD)pData[15]);
    }
    else
    {
        // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (6 * (WORD)pData[15]);
    }

    // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)) * (Link Clk / Stream CLK))
    usFifoOffset = (WORD)(((DWORD)usFifoOffset) * (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_INPUT_PIXEL_CLK()));

    return ((ulVFrontPorch + ulHFrontPorch + (DWORD)usFifoOffset) / 2);
}
//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetBit(PBA_C4_DPCD_DATA_PORT, ucDpcdBit);
}
//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte(PBA_C4_DPCD_DATA_PORT);
}
//--------------------------------------------------
// Description  : Check Dp Video Straam VBID
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpRx1GetVideoStream(void)
{
#if(_DP_MST_SUPPORT == _ON)
    if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        // Check if ST_Source is Assigned the STx Stream In MST Mode
        if((ScalerGetBit(PB0_01_PHY_DIG_RESET_CTRL, _BIT7) == _BIT7) &&
           (ScalerGetBit(PB8_0D_SOURCE_SEL_0, (_BIT6 | _BIT5 | _BIT4)) == 0x00))
        {
            return _FALSE;
        }
    }
#endif

    if(ScalerGetBit(PB9_01_DP_VBID, _BIT3) == 0x00)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Before Hpd Toggle Process
// Input Value  : EnumDpHotPlugAssertType
// Output Value : None
//--------------------------------------------------
EnumDpHotPlugTime ScalerDpRx1BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType)
{
    if(enumHpdType == _DP_HPD_NONE)
    {
        return _DP_HPD_TIME_NONE;
    }

    if(enumHpdType == _DP_HPD_ASSERTED)
    {
        if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
        {
            return _DP_HPD_TIME_NONE;
        }
    }

    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX1_DP_LINK_TRAINING_REBUILD_PHY);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_WD_TIMER_INT_SUPPORT == _ON))
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE);
#endif

#if(_DP_MST_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
#if(_DP_TX_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_CPIRQ_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_REPEATER_PROC_TIMEOUT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_READ_IRQ_TIMEOUT);
#endif
#endif

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
    if((enumHpdType != _DP_HDCP_LONG_HPD_EVENT) && (enumHpdType != _DP_HBR2_MARGIN_LINK_HPD_EVENT) && ((ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x00) >= _DP_VERSION_1_2) || (ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)))
    {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        if(((ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x01) < _D1_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpRx1GetDpcdInfo(0x00, 0x22, 0x01) < _D1_DP_LINK_CLK_RATE)))
#else
        if(((ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x01) < _D1_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (g_ucDpRx1DPCD02201hValue < _D1_DP_LINK_CLK_RATE)))
#endif
        {
            if(_D1_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _D1_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, _D1_DP_LINK_CLK_RATE);
#else
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            g_ucDpRx1DPCD02201hValue = _D1_DP_LINK_CLK_RATE;
#endif
            DebugMessageRx1("Flag Clear_Hotplug Event_D1", _D1_DP_LINK_CLK_RATE);
        }
    }
#endif

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
    if(enumHpdType != _DP_HBR2_MARGIN_LINK_HPD_EVENT)
    {
        ScalerDpRx1CalculateLinkRate(GET_DP_RX_D1_PORT_TARGET_LANE_COUNT());
    }
#endif

    if(enumHpdType != _DP_HPD_ASSERTED)
    {
        ScalerDpRx1AVMute();

        ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);

#if(_DP_MST_SUPPORT == _ON)
        if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
        {
            ScalerDpRx1MstInfoBackup(_DP_MST_BACKUP_INFO);

            ScalerDpMstReset(_DP_MST_RX1_PORT);
        }
#endif

#if(_DP_TX_SUPPORT == _ON)
        if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
        {
            ScalerDpTxForceIdlePatternSetting();
        }
#endif

#if(_DP_HPD_LOW_AUX_NOT_REPLY_SUPPORT == _ON)
        // Reset Aux Phy
        ScalerSetBit(PBA_65_AUX_5, ~_BIT7, 0x00);
#endif
    }

    if(enumHpdType == _DP_HPD_LOW)
    {
        DebugMessageRx1("_D1_HOT_PLUG_LOW", 0);

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

        return _DP_HPD_TIME_NONE;
    }
    else if(enumHpdType == _DP_HPD_LOW_RESET_AUX)
    {
        // Reset Aux Phy
        ScalerSetBit(PBA_65_AUX_5, ~_BIT7, 0x00);

        DebugMessageRx1("_D1_HOT_PLUG_LOW", 0);

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

        return _DP_HPD_TIME_NONE;
    }

    // Reset DDC1
    MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT1;

#if(_DP_FREESYNC_SUPPORT == _ON)
    SET_DP_RX1_AUX_MANUAL_MODE();
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x07, 0x00);
    SET_DP_RX1_AUX_AUTO_MODE();
#endif

    ScalerDpRx1HDCPUnplugReset();

#if(_D1_DP_ASSR_MODE_SUPPORT == _ON)
    SET_DP_RX1_AUX_MANUAL_MODE();
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
    SET_DP_RX1_AUX_AUTO_MODE();
#endif

    if(enumHpdType == _DP_LONG_HPD_EVENT)
    {
        return _DP_LONG_HPD_TIME;
    }
    else if(enumHpdType == _DP_HDCP_LONG_HPD_EVENT)
    {
        return _DP_HDCP_LONG_HPD_TIME;
    }
    else if(enumHpdType == _DP_MST_LONG_HPD_EVENT)
    {
        // Reset Aux Phy
        ScalerSetBit(PBA_65_AUX_5, ~_BIT7, 0x00);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        // No Receiving Topology Rebuild MSG within 4s
        if(GET_DP_TX_WAIT_TOPOLOGY_REBUILD_MSG() == _TRUE)
        {
            CLR_DP_TX_WAIT_TOPOLOGY_REBUILD_MSG();

            return _DP_MST_FORCE_LONG_HPD_TIME;
        }
        else
#endif
        {
            return _DP_MST_LONG_HPD_TIME;
        }
    }
#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
    else if(enumHpdType == _DP_HBR2_MARGIN_LINK_HPD_EVENT)
    {
        return _DP_HBR2_MARGIN_LINK_HPD_TIME;
    }
#endif
    else if(enumHpdType == _DP_HPD_ASSERTED)
    {
        return _DP_HPD_ASSERTED_TIME;
    }

    return _DP_HPD_TIME_NONE;
}

//--------------------------------------------------
// Description  : Dp After Hpd Toggle Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AfterHpdToggleProc(void)
{
    // Release Aux Phy
    ScalerSetBit(PBA_65_AUX_5, ~_BIT7, _BIT7);

    SET_DP_RX1_AUX_MANUAL_MODE();

    if((GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS) && (GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_LINK_TRAINING_PASS))
    {
        ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x00, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0xE0));
    }

    SET_DP_RX1_AUX_AUTO_MODE();

    if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
    {
        ScalerDpRx1ValidSignalDetectionActiveEvent();

#if(_DP_TX_SUPPORT == _ON)
#if(_DP_DPCD_DFP_PRESENT_REF_TO == _DP_MST_CAPABILITY)
        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == 0x00)
        {
            ScalerDpRx1UpdateSinkCount(1);
        }
        else
#endif
        {
            ScalerDpRx1UpdateSinkCount(GET_DP_TX_DOWNSTREAM_SINK_COUNT() + 1);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Initial Setting for DP
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport)
{
    ScalerDpRx1AuxPowerOnInitial();

    ScalerDpRx1DpcdInitial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumFreeSyncSupport);

    // Must be initialized "AFTER DPCD setting" to avoid entering interruption unexpectively
    ScalerDpRx1AuxIntInitial();

    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    SET_DP_RX1_FAKE_LINK_TRAINING();

    SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
    SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
    SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

    SET_DP_RX1_HDCP_MODE_BACKUP(_HDCP_14);

    ScalerDpRx1SetDpLaneMapping(_TYPE_C_PIN_ASSIGNMENT_C, _TYPE_C_ORIENTATION_UNFLIP);

#if(_DP_MST_SUPPORT == _ON)
    CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
    CLR_DP_RX1_CHECK_AUX_CH_POWER_STATUS();
#endif

#if(_DP_TX_SUPPORT == _ON)
    CLR_DP_RX1_HDCP_AUTH_AKSV_WRITTEN();
#endif
}

//--------------------------------------------------
// Description  : DP Margin Link Check
// Input Value  : None
// Output Value : _TRUE : Link ok ; _FALSE : Margin Link
//--------------------------------------------------
bit ScalerDpRx1MarginLinkCheck(void)
{
    switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00))
    {
        case _DP_LINK_HBR2:

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
            if((ScalerDpRx1DFECheck() == _TRUE) &&
               (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               (ScalerDpRx1LaneBsCheck() == _TRUE) &&
               (ScalerDpRx1DecodeErrorCountCheck(_DP_HBR2_MARGIN_LINK_TIME_CRITERIA, _DP_HBR2_MARGIN_LINK_ERROR_CRITERIA) == _FALSE))
            {
                if((ScalerDpRx1DFECheck() == _TRUE) &&
                   (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
                   (ScalerDpRx1LaneBsCheck() == _TRUE))
                {
                    if(ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _TRUE)
                    {
                        SET_DP_RX_D1_MARGIN_LINK_HBR2();
                        return _FALSE;
                    }
                }
            }
#else
            return _TRUE;
#endif
            break;

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1LinkStatusIRQ(void)
{
    SET_DP_RX1_AUX_MANUAL_MODE();

    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_FAIL) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
    {
        ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_RESET);

        SET_DP_RX1_AUX_AUTO_MODE();

        ScalerDpRx1HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        ScalerDpRx1Hdcp2ResetProc();
#endif

        if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
           (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_WD_TIMER_INT_SUPPORT == _ON))
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE);
#endif

            ScalerDpRx1HpdIrqAssert();
        }
    }

    SET_DP_RX1_AUX_AUTO_MODE();
}

//-------------------------------------------------------
// Description  : Set Aux Diff mode or Single-eneded mode
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpRx1AuxSet(void)
{
    if(GET_DP_AUX_DIFF_MODE() == _FALSE)
    {
        // Set TX VLDO = 1.05V, Open AUX ADJR_P, Rx Common Mode from 3.3V
        ScalerSetByte(PBA_61_AUX_1, ((_DP_AUX_SWING_1050_MV << 5) | _BIT4));

        // [5]Enable Single-Ended Mode, [4:3]Aux Vth-->50mV, [0]Aux 50ohm auto K(Enable Big_Z0_P)
        ScalerSetByte(PBA_62_AUX_2, 0x29);

        // [4]Enable Big_Z0_N, [3:0]Open ADJR_N
        ScalerSetBit(PBA_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    }
    else
    {
        // Set TX VLDO = 1.05V, Rx Common Mode from 3.3V
        ScalerSetBit(PBA_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((_DP_AUX_SWING_1050_MV << 5) | _BIT4));

        // [5]Disable Single-Ended Mode, [4:3]Aux Vth-->50mV, [0]Aux 50ohm auto K(Enable Big_Z0_P)
        ScalerSetByte(PBA_62_AUX_2, 0x09);

        // [4]Enable Big_Z0_N
        ScalerSetBit(PBA_66_AUX_6, ~_BIT4, _BIT4);

        // AUX RX1 P Channel Resistance Setting
        ScalerSetBit(PBA_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());

        // AUX RX1 N Channel Resistance Setting
        ScalerSetBit(PBA_66_AUX_6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());
    }
}

//--------------------------------------------------
// Description  : DP Error Counter Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ErrorCounterUpdate_EXINT0(void) using 1
{
    WORD usErrorTemp = 0;

    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            // Store Lane0 Error
            ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE0 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x10, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            break;

        case _DP_TWO_LANE:

            // Store Lane0 Error
            ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE0 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x10, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane1 Error
            ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE1 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x12, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            break;

        default:
        case _DP_FOUR_LANE:

            // Store Lane0 Error
            ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE0 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x10, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane1 Error
            ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE1 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x12, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane2 Error
            ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE2 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x14, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            // Store Lane3 Error
            ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_D1_DP_LANE3 << 3));

            usErrorTemp = (((WORD)ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) << 8) | (ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4)));

            if((usErrorTemp >= 49) && (usErrorTemp <= 100))
            {
                usErrorTemp = 50;
            }

            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x16, LOBYTE(usErrorTemp));
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorTemp));

            break;
    }

    // Reset 8B/10B Error Counter
    ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
}

//--------------------------------------------------
// Description  : DP Error Counter Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ErrorCounterDisable_EXINT0(void) using 1
{
    // Disable Wildcard IRQ for Error Counter
    ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), 0x00);

    // Disable 8B/10B Error Counter
    ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Enable DPCD Auto Increment
    ScalerSetBit_EXINT(PBA_C0_DPCD_CTRL, ~_BIT0, _BIT0);

    // Set DPCD 0x21xh
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, 0x00);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, 0x02);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, 0x10);

    // Set DPCD 0x210-0x217 = 0x00
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, 0x00);

    // Disable DPCD Auto Increment
    ScalerSetBit_EXINT(PBA_C0_DPCD_CTRL, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : DP Error Counter Enable
// Input Value  : DP Link Training Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ErrorCounterEnable_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    // Enable DPCD Error Count Valid Flag
    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);

            break;

        case _DP_TWO_LANE:

            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~_BIT7, _BIT7);

            break;

        default:
        case _DP_FOUR_LANE:

            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x11, ~_BIT7, _BIT7);
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x13, ~_BIT7, _BIT7);
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x15, ~_BIT7, _BIT7);
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x17, ~_BIT7, _BIT7);

            break;
    }

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        // Enable 8B/10B Error Counter
        ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
    }

    // Enable Read Error Counter IRQ, Clear IRQ Flag
    ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
}

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check 8b10b Error Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1DecodeErrorCountCheck(WORD usTimeCriteria, BYTE ucErrorCriteria)
{
    ScalerDpRx1DecodeErrorCountReset();

    ScalerTimerDelayXms(usTimeCriteria);

    switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_ONE_LANE:

            if(ScalerDpRx1DecodeErrorCountLaneMeasure(ucErrorCriteria, _D1_DP_LANE0) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_TWO_LANE:

            if((ScalerDpRx1DecodeErrorCountLaneMeasure(ucErrorCriteria, _D1_DP_LANE0) == _TRUE) &&
               (ScalerDpRx1DecodeErrorCountLaneMeasure(ucErrorCriteria, _D1_DP_LANE1) == _TRUE))
            {
                return _TRUE;
            }

            break;

        case _DP_FOUR_LANE:
        default:

            if((ScalerDpRx1DecodeErrorCountLaneMeasure(ucErrorCriteria, _D1_DP_LANE0) == _TRUE) &&
               (ScalerDpRx1DecodeErrorCountLaneMeasure(ucErrorCriteria, _D1_DP_LANE1) == _TRUE) &&
               (ScalerDpRx1DecodeErrorCountLaneMeasure(ucErrorCriteria, _D1_DP_LANE2) == _TRUE) &&
               (ScalerDpRx1DecodeErrorCountLaneMeasure(ucErrorCriteria, _D1_DP_LANE3) == _TRUE))
            {
                return _TRUE;
            }

            break;
    }

    DebugMessageRx1("7. DP Error Count Fail", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description : Measure 8b10b Error Count Per Lane
// Input Value  : DP Lane
// Output Value : True --> locked; False --> unlocked
//--------------------------------------------------
bit ScalerDpRx1DecodeErrorCountLaneMeasure(BYTE ucErrorCriteria, BYTE ucDpRx1LaneNumber)
{
    WORD usErrorCountLaneMeasure = 0;

    // Select Lane
    ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (ucDpRx1LaneNumber << 3));

    usErrorCountLaneMeasure = ((((WORD)ScalerGetByte(PB0_0B_BIST_PATTERN3)) << 8) | ScalerGetByte(PB0_0C_BIST_PATTERN4));

    if(usErrorCountLaneMeasure > ucErrorCriteria)
    {
        DebugMessageRx1("DP Lane", ucDpRx1LaneNumber);
        DebugMessageRx1("DP Lane Burst Error", usErrorCountLaneMeasure);

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : Check Lane BS
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx1LaneBsCheck(void)
{
    // Detect Enable
    ScalerSetBit(PB0_00_HD_DP_SEL, ~_BIT3, 0x00);
    ScalerSetBit(PB0_00_HD_DP_SEL, ~_BIT3, _BIT3);

    // Delay for 8192 x 10 x 8 x 2 / 1.62G = 809us
    DELAY_XUS(850);

    // Check Lane Bs
    if(ScalerGetBit(PB0_00_HD_DP_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Check DP Vactive / Hactive Information
// Input Value  : None
// Output Value : True --> DP Vactive / Hactive Information Check Ok
//--------------------------------------------------
bit ScalerDpRx1MSAActiveChange(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Display Format Hactive
    ScalerRead(PB8_45_MN_DPF_HWD_M, 2, &pData[0], _AUTOINC);

    // Get MSA Hactive
    ScalerRead(PB9_0C_MSA_HWD_0, 2, &pData[2], _AUTOINC);

    // Get Display Format Vactive
    ScalerRead(PB8_4D_MN_DPF_VHT_M, 2, &pData[4], _AUTOINC);

    // Get MSA Vactive
    ScalerRead(PB9_16_MSA_VHT_0, 2, &pData[6], _AUTOINC);

    if((PDATA_WORD(0) != PDATA_WORD(1)) || (PDATA_WORD(2) != PDATA_WORD(3)))
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpRx1PSPreDetect(void)
{
    // Back to noraml for DP PHY CTS
    if(GET_DP_RX1_PHY_CTS_FLG() == _TRUE)
    {
        return _TRUE;
    }

    if(GET_DP_RX1_VALID_VIDEO_CHECK() == _TRUE)
    {
        DebugMessageRx1("7. Valid Video Check", 0);

        return _TRUE;
    }

    if(GET_DP_RX1_PS_AUX_TOGGLE() == _TRUE)
    {
        DebugMessageRx1("7. Power Saving Aux Handshake", 0);

        return _TRUE;
    }

    if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        DebugMessageRx1("7. Normal Link Training under Fake Power Saving Case", 0);

        return _TRUE;
    }

#if(_DP_MST_SUPPORT == _ON)

    if(ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE1) != 0x00)
    {
        return _TRUE;
    }

    if(GET_DP_RX1_AUX_CH_POWER_ON_WAKE_UP() == _TRUE)
    {
        CLR_DP_RX1_AUX_CH_POWER_ON_WAKE_UP();

        return _TRUE;
    }
#endif

    if(((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) &&
        ((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
         (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))) ||
       (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
    {
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))

        if(ScalerAudioGetDigitalAudioSource(_D1_INPUT_PORT) == _DIGITAL_AUDIO_SOURCE_DP)
        {
            DebugMessageAudio("00. DP Power Saving Audio : Idle Pattern Case", ScalerAudioGetDigitalAudioSource(_D1_INPUT_PORT));
            return _TRUE;
        }
#endif
        DebugMessageRx1("7. Idle Pattern Case", 0);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set DP Lane Mapping Type
// Input Value  : ucLanetype --> Lane Mapping Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation)
{
    if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
    {
        if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Lane 0 <--> Lane 2
            // Lane 1 <--> Lane 3
            SET_DP_RX1_PCB_LANE0_MAPPING(_D1_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D1_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D1_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D1_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(!_D1_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(!_D1_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(!_D1_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(!_D1_DP_PCB_LANE3_PN_SWAP);

#if(_D1_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
            // Enable Aux PN Pull High Low Swap PCB Function
            PCB_D1_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_ON);

            // Enable Aux Digital Phy PN Swap
            ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
#else
            // Disable Aux PN Pull High Low Swap PCB Function
            PCB_D1_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);

            // Disable Aux Digital Phy PN Swap
            ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
#endif
        }
        else // Normal Cable Mode
        {
            SET_DP_RX1_PCB_LANE0_MAPPING(_D1_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D1_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D1_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D1_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(_D1_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(_D1_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(_D1_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(_D1_DP_PCB_LANE3_PN_SWAP);

            // Disable Aux PN Pull High Low Swap PCB Function
            PCB_D1_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);

            // Disable Aux Digital Phy PN Swap
            ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
        }
    }
    else
    {
        if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Lane 0 <--> Lane 2
            // Lane 1 <--> Lane 3
            SET_DP_RX1_PCB_LANE0_MAPPING(_D1_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D1_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D1_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D1_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(!_D1_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(!_D1_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(!_D1_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(!_D1_DP_PCB_LANE3_PN_SWAP);

            // Disable Aux PN Pull High Low Swap PCB Function
            PCB_D1_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);

            // Disable Aux Digital Phy PN Swap
            ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
        }
        else // Normal Cable Mode
        {
            SET_DP_RX1_PCB_LANE0_MAPPING(_D1_DP_PCB_LANE3_MAPPING);
            SET_DP_RX1_PCB_LANE1_MAPPING(_D1_DP_PCB_LANE2_MAPPING);
            SET_DP_RX1_PCB_LANE2_MAPPING(_D1_DP_PCB_LANE1_MAPPING);
            SET_DP_RX1_PCB_LANE3_MAPPING(_D1_DP_PCB_LANE0_MAPPING);
            SET_DP_RX1_PCB_LANE0_PN_SWAP(_D1_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX1_PCB_LANE1_PN_SWAP(_D1_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX1_PCB_LANE2_PN_SWAP(_D1_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX1_PCB_LANE3_PN_SWAP(_D1_DP_PCB_LANE3_PN_SWAP);

            // Enable Aux PN Pull High Low Swap PCB Function
            PCB_D1_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_ON);

            // Enable Aux Digital Phy PN Swap
            ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
        }
    }
}

//--------------------------------------------------
// Description  : Dp Secondary Data Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SecDataBlockReset(void)
{
    // Set S code by FW manual
    ScalerSetBit(PB9_58_SCODE_0, ~_BIT7, _BIT7);

    // Sec Data Block Reset
    ScalerSetBit(PB8_00_MAC_DIG_RESET_CTRL, ~_BIT4, _BIT4);
    ScalerSetBit(PB8_00_MAC_DIG_RESET_CTRL, ~_BIT4, 0x00);

    // Set S code by HW auto
    ScalerSetBit(PB9_58_SCODE_0, ~_BIT7, 0x00);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetBit(PBA_C4_DPCD_DATA_PORT, ~(~ucNotDpcdBit), ucDpcdBit);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetByte(PBA_C4_DPCD_DATA_PORT, ucDpcdValue);
}
//--------------------------------------------------
// Description  : DP Sink Status Setting
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync)
{
    if(enumInSync == _DP_SINK_IN_SYNC)
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 in Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) | _BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 in Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) | _BIT1));
        }
    }
    else
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 Out of Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) & ~_BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 Out of Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) & ~_BIT1));
        }
    }
}

//--------------------------------------------------
// Description  : Dp HDCP DPCD capability Switch
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ChangeHdcpDpcdCapability(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Clear flag for write 68xxx int
        ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~_BIT1, _BIT1);

        // Enable Write 68xxx int
        ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~_BIT2, _BIT2);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        // Clear flag for Write AKSV int
        ScalerSetBit(PBA_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

        // Enable Write AKSV int
        ScalerSetBit(PBA_A5_AUX_RESERVE5, ~_BIT6, _BIT6);

        // Enable HDCP and repeater support
        ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x03);
#else
        // Enable HDCP support
        ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x01);
#endif

#if((_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
        if(ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x00) > _DP_VERSION_1_1)
        {
            ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x03);
        }
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        // Enable the HDCP2.2 capability
        for(pData[0] = 0; pData[0] < 3; pData[0]++)
        {
            ScalerDpRx1SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), g_pucDPRx1Caps[pData[0]]);
        }
#endif
    }
    else
    {
        // Disable Write 68xxx int
        ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~_BIT2, 0x00);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        // Disable Write AKSV int
        ScalerSetBit(PBA_A5_AUX_RESERVE5, ~_BIT6, 0x00);
#endif
        // Disable HDCP support
        ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x00);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        // Disable the HDCP2.2 capability
        for(pData[0] = 0; pData[0] < 3; pData[0]++)
        {
            ScalerDpRx1SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), 0x00);
        }
#endif
    }
}

#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP ASSR Mode On/ Off
// Input Value  : _ON/ _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ASSRModeSetting(void)
{
    if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x0A) & _BIT0) == _BIT0)
    {
        // Scramble seed equal to 0xFFFE
        ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);
    }
    else
    {
        // Scramble seed equal to 0xFFFF
        ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);
    }
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check FREESYNC Enable
// Input Value  : None
// Output Value : _TRUE: FREESYNC change
//--------------------------------------------------
bit ScalerDpRx1GetFREESYNCStatusChange(void)
{
    if((GET_FREESYNC_ENABLED() == _TRUE) && ((g_stInputTimingData.usVFreq < (_PANEL_FREESYNC_MIN_FRAME_RATE - _FRAME_SYNC_MARGIN)) || (g_stInputTimingData.usVFreq > (_PANEL_FREESYNC_MAX_FRAME_RATE + _FRAME_SYNC_MARGIN))))
    {
        DebugMessageRx1("7.FREESYNC IVF out of panel range", g_stInputTimingData.usVFreq);
        return _TRUE;
    }

    if((bit)(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x07) & _BIT7) != GET_FREESYNC_ENABLED())
    {
        DebugMessageRx1("7.FREESYNC ignore MSA 0 -> 1", 0);
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set DP Freesync Htotal info
// Input Value  : Dp Timing Info
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetFREESYNCMsaForLut(WORD usDpHtotal)
{
    WORD usTempMeasureHtotal = usDpHtotal;
    WORD usTempMsaHtotal = ((((WORD)ScalerGetByte(PB9_08_MSA_HTT_0)) << 8) | ((WORD)ScalerGetByte(PB9_09_MSA_HTT_1)));
    WORD usTempMsaHtotalMargin = ((DWORD)usTempMeasureHtotal * _DP_FREESYNC_HTOTAL_MARGIN / 100);

    if((usTempMsaHtotal > (usTempMeasureHtotal + usTempMsaHtotalMargin)) || (usTempMsaHtotal < (usTempMeasureHtotal - usTempMsaHtotalMargin)))
    {
        SET_DP_RX1_HTOTAL(usTempMeasureHtotal);

        SET_DP_RX1_HTOTAL_MARGIN(usTempMsaHtotalMargin);

        DebugMessageRx1("7. DP Freesync Get MSA Htotal Fail", usTempMsaHtotal);
    }
    else
    {
        SET_DP_RX1_HTOTAL(usTempMsaHtotal);

        SET_DP_RX1_HTOTAL_MARGIN(1);
    }
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Backup MST Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstInfoBackup(EnumDpMstBackup enumDpMstBackup)
{
    EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

    switch(enumDpMstBackup)
    {
        case _DP_MST_BACKUP_INFO:

            if((ScalerGetBit(PB0_01_PHY_DIG_RESET_CTRL, _BIT7) == _BIT7) &&
               (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS))
            {
                // Backup MST Enable
                g_stDpRx1MiscInfo.b1DpMstEnableBackup = _TRUE;

                // Backup Link Config
                g_stDpRx1MiscInfo.ucDpRxLinkRateBackup = ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00);
                g_stDpRx1MiscInfo.ucDpRxLaneCountBackup = (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F);

                // Backup TimeSlot Info
                memcpy(g_pucDpRx1MstTimeSlotBackup, (volatile BYTE xdata *)PB8_03_STHD_CTRL_2, sizeof(g_pucDpRx1MstTimeSlotBackup));

                for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE5; enumSourceNum++)
                {
                    g_pucDpMacRx1MstStMuxBackup[enumSourceNum] = GET_DP_RX_MST_ST_SOURCE_BACKUP(enumSourceNum);
                }
            }

            break;

        case _DP_MST_BACKUP_INFO_RESTORE:

            if(((ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x21) & _BIT0) == _BIT0) && (g_stDpRx1MiscInfo.b1DpMstEnableBackup == _TRUE))
            {
                // Enable MST Decode
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT7, _BIT7);

                // Restore TimeSlot Info
                memcpy((volatile BYTE xdata *)PB8_03_STHD_CTRL_2, g_pucDpRx1MstTimeSlotBackup, sizeof(g_pucDpRx1MstTimeSlotBackup));

                for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE5; enumSourceNum++)
                {
                    ScalerDpRxMstStreamMuxBackup(enumSourceNum, g_pucDpMacRx1MstStMuxBackup[enumSourceNum]);
                }
            }
            g_stDpRx1MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;

        case _DP_MST_BACKUP_INFO_RESET:
        default:

            g_stDpRx1MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx HDCP - SHA circuit Run
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPAuthShaRun(bit bIsFirst)
{
    // Set First Run For SHA-1 Circuit
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT1, ((bIsFirst == _TRUE) ? _BIT1 : 0x00));

    // Run SHA-1 Circuit
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT2, _BIT2);

    ScalerTimerPollingFlagProc(5, PB0_30_SHA_CONTRL, _BIT4, _TRUE);

    // Disable First Run and Disable SHA-1 Circuit
    ScalerSetBit(PB0_30_SHA_CONTRL, ~(_BIT2 | _BIT1), 0x00);
}

//--------------------------------------------------
// Description  : Change HDCP Auth State
// Input Value  : Target HDCP Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPChangeAuthState(EnumDPRxHDCPAuthState enumHDCPAuthState)
{
    SET_DP_RX1_HDCP_AUTH_STATE(enumHDCPAuthState);
    SET_DP_RX1_HDCP_AUTH_STATE_CHANGE();
}
//--------------------------------------------------
// Description  : Check B info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1HDCPCheckBinfo(void)
{
    BYTE ucBInfoDevice = 0;
    BYTE ucBInfoDepth = 0;
    bit bBInfoDeviceExceed = _FALSE;
    bit bBInfoDepthExceed = _FALSE;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if(GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP2_REPEATER_SUPPORTED() == _TRUE)
        {
            if((GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT_EXCEED() == _TRUE) ||
               (GET_DP_TX_HDCP2_RXINFO_DEPTH_EXCEED() == _TRUE))
            {
                bBInfoDeviceExceed = (GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT_EXCEED() == _TRUE) ? _TRUE : _FALSE;
                bBInfoDepthExceed = (GET_DP_TX_HDCP2_RXINFO_DEPTH_EXCEED() == _TRUE) ? _TRUE : _FALSE;
            }
            else
            {
                ucBInfoDevice = GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT();
                ucBInfoDepth = GET_DP_TX_HDCP2_RXINFO_DEPTH();

                if(ucBInfoDevice > 125)
                {
                    ucBInfoDevice = 0x00;
                    bBInfoDeviceExceed = _TRUE;
                }

                if(ucBInfoDepth > 6)
                {
                    ucBInfoDepth = 0x00;
                    bBInfoDepthExceed = _TRUE;
                }
            }
        }

        if(bBInfoDeviceExceed == _FALSE)
        {
            ucBInfoDevice++;
        }
    }
    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#else
    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#endif
    {
        if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
        {
            if((GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_MAX() == _TRUE) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() > _DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_EXCEED))
            {
                bBInfoDeviceExceed = _TRUE;
            }
            else
            {
                ucBInfoDevice = GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT();
            }

            if((GET_DP_TX_HDCP_DOWNSTREAM_DEPTH_MAX() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_DEPTH() > 6))
            {
                bBInfoDepthExceed = _TRUE;
            }
            else
            {
                ucBInfoDepth = GET_DP_TX_HDCP_DOWNSTREAM_DEPTH();
            }
        }

        if(bBInfoDeviceExceed == _FALSE)
        {
            ucBInfoDevice++;
        }
    }

    if(bBInfoDeviceExceed == _FALSE)
    {
#if(_DP_HDCP14_CTS_SUPPORT == _ON)
        if(ucBInfoDevice == 0x00)
        {
            ucBInfoDevice = 0x01;
        }
#else
        ucBInfoDevice++;
#endif
    }
    else
    {
        ucBInfoDevice = 0x80;
    }

    if(bBInfoDepthExceed == _FALSE)
    {
        ucBInfoDepth++;
    }
    else
    {
        ucBInfoDepth = 0x08;
    }

    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2A, ucBInfoDevice);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2B, ucBInfoDepth);

    if((ucBInfoDevice == 0x80) || (ucBInfoDepth == 0x08))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Dp Rx HDCP Link Veriffication Pattern (0x531F) for MST Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1HDCPCheckLvp(void)
{
    if(((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Fake HDCP Authentication
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPFakeAuthenProc(void)
{
    BYTE pucSHAInput[64];

    // Set Device Count and Depth
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2A, 0x01);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2B, 0x01);

    // Load KSV
    memcpy(pucSHAInput, g_pucHdcpAksvBackup, 5);

    // Load Device Count and Depth
    pucSHAInput[5] = ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A);
    pucSHAInput[6] = ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2B);

    // Load M0'
    for(pData[0] = 0; pData[0] < 8; pData[0]++)
    {
        pucSHAInput[7 + pData[0]] = ScalerGetByte(PB0_2F_M0_BYTE_0 - pData[0]);
    }

    memset(&pucSHAInput[15], 0, 49);

    pucSHAInput[15] = 0x80;

    // Total bit numbers of SHA-1 input = KSV FIFO + B_info + M0'
    pucSHAInput[63] = 0x78;

    // Compute V'
    ScalerDpRx1HDCPSha1Calculate(pucSHAInput, 0);

    // Write Ksv to DPCD table
    SET_DP_RX1_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 15; pData[0]++)
    {
        if(pData[0] < 5)
        {
            ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), g_pucHdcpAksvBackup[pData[0]]);
        }
        else
        {
            ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), 0x00);
        }
    }

    SET_DP_RX1_AUX_AUTO_MODE();

    // Write V' to DPCD table
    ScalerDpRx1HDCPLoadShaToDpcd();
}
//--------------------------------------------------
// Description  : Dp Rx HDCP Auth Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPHandler(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if((GET_DP_RX1_HDCP2_MODE() == _DISABLE) && (GET_DP_RX1_HDCP_REPEATER_SUPPORT() == _TRUE))
#else
    if(GET_DP_RX1_HDCP_REPEATER_SUPPORT() == _TRUE)
#endif
    {
        // After receiving AKSV, handler must initialize authentication
        if(GET_DP_RX1_HDCP_AUTH_AKSV_WRITTEN() == _TRUE)
        {
            CLR_DP_RX1_HDCP_AUTH_AKSV_WRITTEN();
            CLR_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE();

            ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_IDLE);

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_CPIRQ_EVENT);
        }

        if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
        {
            // In MST mode
            if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & _BIT0) == _BIT0)
            {
                if((ScalerDpRx1HdcpCheckValid() == _TRUE) && (GET_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE() == _FALSE))
                {
                    if(ScalerDpRx1HDCPCheckLvp() == _FALSE)
                    {
                        SET_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE();

                        ScalerDpRx1CpIRQ(_DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

                        ScalerTimerActiveTimerEvent(SEC(0.02), _SCALER_TIMER_EVENT_DP_RX1_HDCP_CPIRQ_EVENT);
                    }
                }
            }
            else
            {
                // In SST mode, issue HPD event for upstream device if DPTX connect a new downstream device.
                if((GET_DP_RX1_HDCP_AUTH_STATE() != _DP_RX_HDCP_STATE_IDLE) &&
                   (ScalerDpRx1HdcpCheckValid() == _TRUE) &&
                   (ScalerDpRx1HDCPCheckLvp() == _TRUE))
                {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                    {
                        if(GET_DP_TX_HDCP2_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_REAUTH)
                        {
                            ScalerDpRx1SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
                        }
                    }
                    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#else
                    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#endif
                    {
                        if(GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH)
                        {
                            ScalerDpRx1SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
                        }
                    }
                }
            }
        }

        if((GET_DP_RX1_HDCP_AUTH_STATE() != _DP_RX_HDCP_STATE_IDLE) && (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE))
        {
            ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_IDLE);
        }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
        {
            if((ScalerDpRx1HdcpCheckValid() == _TRUE) &&
               (GET_DP_RX1_HDCP_AUTH_STATE() >= _DP_RX_HDCP_STATE_AUTH_2) &&
               (GET_DP_TX_HDCP2_MODE() == _TRUE))
            {
                SET_DP_RX1_HDCP2_HDCP1_CONTENT_STREAM_MANAGEMENT();
            }
        }
#endif
    }

    switch(GET_DP_RX1_HDCP_AUTH_STATE())
    {
        case _DP_RX_HDCP_STATE_IDLE:

            if(GET_DP_RX1_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE();
                CLR_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT();
                CLR_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                CLR_DP_RX1_HDCP2_HDCP1_CONTENT_STREAM_MANAGEMENT();
#endif

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_REPEATER_PROC_TIMEOUT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_READ_IRQ_TIMEOUT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_CPIRQ_EVENT);

                ScalerDpRx1HDCPEnableReadIrq(_DISABLE);

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
                ScalerDpTxHDCPResetKsvBackup();
#endif

                SET_DP_RX1_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION);
            }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if((GET_DP_RX1_HDCP2_MODE() == _DISABLE) && (GET_DP_RX1_HDCP_REPEATER_SUPPORT() == _TRUE))
#else
            if(GET_DP_RX1_HDCP_REPEATER_SUPPORT() == _TRUE)
#endif
            {
                // Check if R0' was read already by upstream device.
                if((ScalerGetBit(PB0_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5)) &&
                   ((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x05) != 0x00) || (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x06) != 0x00)) &&
                   ((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) & _DP_HDCP_BSTATUS_R0_AVAILABLE) == 0x00) &&
                   ((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) ||
                    (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
                    (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) ||
                    (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
                    (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00)))
                {
                    ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_1);
                }
            }

            break;

        case _DP_RX_HDCP_STATE_AUTH_1:

            if(GET_DP_RX1_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE();

                if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
                {
                    // Check if downstream device support HDCP capability.
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                    {
                        // Issue event to make DPTX start HDCP2 handshake.
                        SET_DP_RX1_HDCP2_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX1_HDCP_REPEATER_PROC_TIMEOUT);
                    }
                    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#else
                    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#endif
                    {
                        // Issue event to make DPTX start HDCP handshake.
                        SET_DP_RX1_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX1_HDCP_REPEATER_PROC_TIMEOUT);
                    }
                    else
                    {
                        ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_2);
                    }
                }
                else
                {
                    ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_FAKE);
                }
            }

            // Wait for downstream pass event or device/depth max event
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if((GET_DP_TX_HDCP2_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PASS) ||
               (GET_DP_TX_HDCP2_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_EXCEED) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX))
#else
            if((GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX))
#endif
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_REPEATER_PROC_TIMEOUT);

                ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_2);
            }
            else if(GET_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                {
                    SET_DP_RX1_HDCP2_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_TIMEOUT);
                }
                else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#else
                if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#endif
                {
                    SET_DP_RX1_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT);
                }

                ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP_STATE_AUTH_2:

            if(GET_DP_RX1_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE();
            }

            if(ScalerDpRx1HDCPCheckBinfo() == _TRUE)
            {
                // Load KSV List to RX KSV FIFO
                ScalerDpRx1HDCPLoadKsvFifo();

                // Input KSV FIFO to SHA-1 and Compute V'
                ScalerDpRx1HDCPWriteShaInput();

                // Write V' into DPCD table
                ScalerDpRx1HDCPLoadShaToDpcd();

                // Set 1st KSV FIFO to DPCD table
                ScalerDpRx1HDCPSetKsvFifoFirst();

                // Enable 68xxx Read INT
                ScalerDpRx1HDCPEnableReadIrq(_ENABLE);

                ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_DP_RX1_HDCP_READ_IRQ_TIMEOUT);
            }

            // Set V' Ready Bit and Issue CP_IRQ
            ScalerDpRx1CpIRQ(_DP_HDCP_BSTATUS_V_READY);

            ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);

            break;

        case _DP_RX_HDCP_STATE_AUTH_FAKE:

            if(GET_DP_RX1_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE();
            }

            // Enable 68xxx Read INT
            ScalerDpRx1HDCPEnableReadIrq(_DISABLE);

            // Fake Authentication
            ScalerDpRx1HDCPFakeAuthenProc();

            // Set V' Ready Bit and Issue CP_IRQ
            ScalerDpRx1CpIRQ(_DP_HDCP_BSTATUS_V_READY);

            ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);

            break;

        case _DP_RX_HDCP_STATE_AUTH_DONE:

            if(GET_DP_RX1_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE();
            }

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
            if(GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS)
            {
                // In SST mode
                if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & _BIT0) == 0x00)
                {
                    if((ScalerDpRx1HDCPDeviceCountChange() == _TRUE) &&
                       (ScalerDpRx1HdcpCheckValid() == _TRUE) &&
                       (ScalerDpRx1HDCPCheckLvp() == _TRUE))
                    {
                        ScalerDpRx1SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
                    }
                }
            }
#endif

            if(GET_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT() == _TRUE)
            {
                ScalerDpRx1HDCPEnableReadIrq(_DISABLE);
            }

            break;

        default:

            break;
    }
}
//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPLoadKsvFifo(void)
{
    bit bLoadAksv = _TRUE;

    PDATA_WORD(0) = 0;
    PDATA_WORD(1) = 0;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if(GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP2_REPEATER_SUPPORTED() == _TRUE)
        {
            PDATA_WORD(1) = GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT() * 5;

            memcpy(g_pucDpTxHdcpKsvFifo, g_pucDpTxHdcp2ReceiverIdList, PDATA_WORD(1));
        }

        memcpy(&g_pucDpTxHdcpKsvFifo[PDATA_WORD(1)], g_pucDpTxHdcp2ReceiverId, 5);
        PDATA_WORD(1) += 5;

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
        bLoadAksv = _FALSE;
#endif
    }
    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#else
    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#endif
    {
        if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
        {
            PDATA_WORD(1) = (WORD) GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() * 5;
        }

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
        // Backup BKSV of Downstream Device
        memcpy(g_pucDpTxHdcpKsvBackup, (volatile BYTE xdata *)PBB_4F_BKSV_0, 5);
#endif

        memcpy(&g_pucDpTxHdcpKsvFifo[PDATA_WORD(1)], (volatile BYTE xdata *)PBB_4F_BKSV_0, 5);
        PDATA_WORD(1) += 5;

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
        bLoadAksv = _FALSE;
#endif
    }

    if(bLoadAksv == _TRUE)
    {
        // Load KSV of TX into KSV FIFO
        memcpy(&g_pucDpTxHdcpKsvFifo[PDATA_WORD(1)], g_pucHdcpAksvBackup, 5);
        PDATA_WORD(1) += 5;
    }

    for(PDATA_WORD(0) = PDATA_WORD(1); PDATA_WORD(0) < ((WORD) _DP_TX_HDCP_DEVICE_COUNT_MAX * 5); PDATA_WORD(0)++)
    {
        g_pucDpTxHdcpKsvFifo[PDATA_WORD(0)] = 0x00;
    }
}

//--------------------------------------------------
// Description  : Dp Rx HDCP - Load SHA Result to DPCD table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPLoadShaToDpcd(void)
{
    SET_DP_RX1_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        for(pData[1] = 0; pData[1] < 4; pData[1]++)
        {
            ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x14 + (pData[0] * 4) + pData[1]), ScalerGetByte(PB0_39_SHA_3 + (pData[0] * 4) - pData[1]));
        }
    }

    SET_DP_RX1_AUX_AUTO_MODE();
}
//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPSetKsvFifoFirst(void)
{
    SET_DP_RX1_AUX_MANUAL_MODE();

    for(g_usDpRx1HdcpKsvFifoOffset = 0; g_usDpRx1HdcpKsvFifoOffset < 15; g_usDpRx1HdcpKsvFifoOffset++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x2C + g_usDpRx1HdcpKsvFifoOffset), g_pucDpTxHdcpKsvFifo[g_usDpRx1HdcpKsvFifoOffset]);
    }

    // Aux HW Control
    SET_DP_RX1_AUX_AUTO_MODE();
}
//--------------------------------------------------
// Description  : Set HDCP Read IRQ Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPSetReadIrqTimeout(void)
{
    SET_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT();
}
//--------------------------------------------------
// Description  : Set HDCP Repeater Proc Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPSetRepeaterProcTimeout(void)
{
    SET_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT();
}
//--------------------------------------------------
// Description  : Calculate SHA-1 Input
// Input Value  : Inpute Array, First Run
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPSha1Calculate(BYTE *pucInputArray, BYTE ucCalCount)
{
    // Reset SHA Block counter
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT3, _BIT3);

    // Start to Write SHA-1 Transform Input
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT3, 0x00);

    // Write SHA-1 Input Data, Total 512 bits
    for(pData[1] = 0; pData[1] < 16; pData[1]++)
    {
        ScalerSetByte(PB0_31_SHA_DATA1, pucInputArray[pData[1] * 4]);
        ScalerSetByte(PB0_32_SHA_DATA2, pucInputArray[1 + pData[1] * 4]);
        ScalerSetByte(PB0_33_SHA_DATA3, pucInputArray[2 + pData[1] * 4]);
        ScalerSetByte(PB0_34_SHA_DATA4, pucInputArray[3 + pData[1] * 4]);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);
    }

    ScalerDpRx1HDCPAuthShaRun(((ucCalCount == 0x00) ? _TRUE : _FALSE));
}
//--------------------------------------------------
// Description  : Load KSV FIFO to SHA-1 Input
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPWriteShaInput(void)
{
    WORD usKsvFifoLength = 0;
    WORD usShaInputBitNumbers = 0;
    WORD usKsvLengthTemp = 0;

    usKsvFifoLength = (WORD) ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A) * 5;

    // Total bit numbers of SHA-1 input = KSV FIFO + B_info + M0'
    usShaInputBitNumbers = (usKsvFifoLength + 2 + 8) * 8;

    // Reset SHA Block counter
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT3, _BIT3);

    // Start to Write SHA-1 Transform Input
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT3, 0x00);

    // Write the KSV List into SHA-1 Transform Input
    do
    {
        ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
        ScalerSetByte(PB0_32_SHA_DATA2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
        ScalerSetByte(PB0_33_SHA_DATA3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 2]);
        ScalerSetByte(PB0_34_SHA_DATA4, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 3]);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }
    while((usKsvFifoLength - usKsvLengthTemp) >= 4);

    // Write the remaining KSV, B info and M0' into SHA-1 Transform Input
    switch(usKsvFifoLength - usKsvLengthTemp)
    {
        case 1:

            ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A));
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2B));
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_RX1_HDCP_M0_0());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_RX1_HDCP_M0_1());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_RX1_HDCP_M0_2());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_RX1_HDCP_M0_3());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_RX1_HDCP_M0_4());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_RX1_HDCP_M0_5());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_RX1_HDCP_M0_6());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_RX1_HDCP_M0_7());
            ScalerSetByte(PB0_34_SHA_DATA4, 0x80);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 2:

            ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB0_32_SHA_DATA2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A));
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2B));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_RX1_HDCP_M0_0());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_RX1_HDCP_M0_1());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_RX1_HDCP_M0_2());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_RX1_HDCP_M0_3());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_RX1_HDCP_M0_4());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_RX1_HDCP_M0_5());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_RX1_HDCP_M0_6());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_RX1_HDCP_M0_7());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, 0x80);
            ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
            ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 3:

            ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB0_32_SHA_DATA2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PB0_33_SHA_DATA3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 2]);
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2B));
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_RX1_HDCP_M0_0());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_RX1_HDCP_M0_1());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_RX1_HDCP_M0_2());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_RX1_HDCP_M0_3());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_RX1_HDCP_M0_4());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_RX1_HDCP_M0_5());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_RX1_HDCP_M0_6());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_RX1_HDCP_M0_7());
            ScalerSetByte(PB0_32_SHA_DATA2, 0x80);
            ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        default:

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A));
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2B));
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_RX1_HDCP_M0_0());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_RX1_HDCP_M0_1());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_RX1_HDCP_M0_2());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_RX1_HDCP_M0_3());
            ScalerSetByte(PB0_33_SHA_DATA3, GET_DP_RX1_HDCP_M0_4());
            ScalerSetByte(PB0_34_SHA_DATA4, GET_DP_RX1_HDCP_M0_5());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, GET_DP_RX1_HDCP_M0_6());
            ScalerSetByte(PB0_32_SHA_DATA2, GET_DP_RX1_HDCP_M0_7());
            ScalerSetByte(PB0_33_SHA_DATA3, 0x80);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;
    }

    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 60)
    {
        ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
        ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }

    // Write 0x00 into the remaining SHA-1 Transform Input space
    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) <= 56)
    {
        while((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) < 56)
        {
            ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
            ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
            ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;
        }

        // The length of SHA-1 input is equal to 2^64(8 bytes)
        ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
        ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

        // Write the valid bit numbers into SHA-1 Transform Input
        ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB0_33_SHA_DATA3, HIBYTE(usShaInputBitNumbers));
        ScalerSetByte(PB0_34_SHA_DATA4, LOBYTE(usShaInputBitNumbers));

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 8;

        ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
    }
}

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Downstream Device Count/Depth is changed or not
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpRx1HDCPDeviceCountChange(void)
{
    BYTE ucBInfoDevice = 0;
    BYTE ucBInfoDepth = 0;
    bit bBInfoDeviceExceed = _FALSE;
    bit bBInfoDepthExceed = _FALSE;

    if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
    {
        if((GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_MAX() == _TRUE) ||
           (GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() > _DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_EXCEED))
        {
            bBInfoDeviceExceed = _TRUE;
        }
        else
        {
            ucBInfoDevice = GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT();
        }

        if((GET_DP_TX_HDCP_DOWNSTREAM_DEPTH_MAX() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_DEPTH() > 6))
        {
            bBInfoDepthExceed = _TRUE;
        }
        else
        {
            ucBInfoDepth = GET_DP_TX_HDCP_DOWNSTREAM_DEPTH();
        }
    }

    if(bBInfoDeviceExceed == _FALSE)
    {
        ucBInfoDevice++;
    }
    else
    {
        ucBInfoDevice = 0x80;
    }

    if(bBInfoDepthExceed == _FALSE)
    {
        ucBInfoDepth++;
    }
    else
    {
        ucBInfoDepth = 0x08;
    }

    if((ucBInfoDevice != ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A)) ||
       (ucBInfoDepth != ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2B)))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Handle DP MST to SST Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstToSstProc(void)
{
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE)
    {
        if(ScalerDpRx1MstToSstScanInputPort() == _TRUE)
        {
            if(ScalerDpRx1MstToSstMeasureInput() == _TRUE)
            {
                ScalerDpTxSetStreamSource(_DP_TX_SOURCE_MST2SST);
            }
        }
    }
    else
    {
        // Stable Check
        if(ScalerDpRx1MstToSstStableDetect() == _FALSE)
        {
            ScalerDpTxForceIdlePatternSetting();
            ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

            // Disabel MST2SST Watch Dog
            CLR_REG_DP_RX_MST2SST_WATCH_DOG_ENABLE();
        }
    }
}
//--------------------------------------------------
// Description  : DP MST2SST Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstToSstSetColorInfo(void)
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
// Description  : On Line Check DP MST2SST stability
// Input Value  : None
// Output Value : True --> DP MST2SST Stable
//                False --> DP MST2SST Unstable
//--------------------------------------------------
bit ScalerDpRx1MstToSstStableDetect(void)
{
    if(ScalerDpRx1MstToSstMiscCheck() == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx1MstToSstFifoCheck(_DP_FIFO_POLLING_CHECK) == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx1MstToSstMSAActiveChange() == _TRUE)
    {
        return _FALSE;
    }

    if(ScalerDpRxMstToSstTxMeasureTimingChange() == _TRUE)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Sink Count Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1UpdateSinkCount(BYTE ucSinkCount)
{
    BYTE ucRxPreSinkCount = ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x00);
    BYTE ucRxCurSinkCount = ((ucRxPreSinkCount & _BIT6) | ucSinkCount);

    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x00, ucRxCurSinkCount);

    if(ucSinkCount > 1)
    {
        ScalerDpRx1DfpDeviceDetailConfig();
    }
    else
    {
        ScalerDpRx1DfpDeviceDetailConfigReset();
    }

    if((ucRxPreSinkCount != ucRxCurSinkCount) && (PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH))
    {
        ScalerDpRx1SetDpcdBitValue(0x00, 0x02, 0x04, ~_BIT6, _BIT6);
        ScalerDpRx1HpdIrqAssert();
    }
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)

//--------------------------------------------------
// Description  : DP FLD Band Finetune
// Input Value  : LaneNumber
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AdjustLaneFLDBand(BYTE ucDpRx1LaneNumber, WORD usVCOBandDiff)
{
    BYTE ucBestVCOBand = 0;
    BYTE ucAutoVCOBand = 0;

    switch(ucDpRx1LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ucAutoVCOBand = (ScalerGetByte(P7A_36_ANA_CDR_11) & 0x7F);

            break;

        case _DP_SCALER_LANE1:

            ucAutoVCOBand = (ScalerGetByte(P7A_37_ANA_CDR_12) & 0x7F);

            break;

        case _DP_SCALER_LANE2:

            ucAutoVCOBand = (ScalerGetByte(P7A_38_ANA_CDR_13) & 0x7F);

            break;

        case _DP_SCALER_LANE3:

            ucAutoVCOBand = (ScalerGetByte(P7A_39_ANA_CDR_14) & 0x7F);

            break;
    }

    // [1:0] freqdet_lane_sel
    ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), ucDpRx1LaneNumber);

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
            break;
        }
    }

    if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        g_pusDpRx1ClockCount1[ucDpRx1LaneNumber] = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

        if(g_pusDpRx1ClockCount1[ucDpRx1LaneNumber] < g_pusDpRx1ClockCount[ucDpRx1LaneNumber])
        {
            ucBestVCOBand = ucAutoVCOBand + (((g_pusDpRx1ClockCount[ucDpRx1LaneNumber] - g_pusDpRx1ClockCount1[ucDpRx1LaneNumber]) / usVCOBandDiff) + 1);
        }
        else
        {
            ucBestVCOBand = ucAutoVCOBand - ((g_pusDpRx1ClockCount1[ucDpRx1LaneNumber] - g_pusDpRx1ClockCount[ucDpRx1LaneNumber]) / usVCOBandDiff);
        }
    }
    else
    {
        ucBestVCOBand = ucAutoVCOBand;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // Manually Reload FLD Band
    switch(ucDpRx1LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ScalerSetBit(P7A_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE1:

            ScalerSetBit(P7A_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE2:

            ScalerSetBit(P7A_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE3:

            ScalerSetBit(P7A_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;
    }
}
//--------------------------------------------------
// Description  : Check Valid Lane CDR
// Input Value  : None
// Output Value : True --> CDR Lock
//--------------------------------------------------
bit ScalerDpRx1CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
    CLR_DP_RX1_SIGNALDETECT_INT_HAPPENED();
#endif

    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            if(ScalerDpRx1MeasureLaneCDRClk(ucDpLinkRate, _D1_DP_LANE0) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_TWO_LANE:

            if((ScalerDpRx1MeasureLaneCDRClk(ucDpLinkRate, _D1_DP_LANE0) == _TRUE) &&
               (ScalerDpRx1MeasureLaneCDRClk(ucDpLinkRate, _D1_DP_LANE1) == _TRUE))
            {
                return _TRUE;
            }

            break;

        case _DP_FOUR_LANE:
        default:

            if((ScalerDpRx1MeasureLaneCDRClk(ucDpLinkRate, _D1_DP_LANE0) == _TRUE) &&
               (ScalerDpRx1MeasureLaneCDRClk(ucDpLinkRate, _D1_DP_LANE1) == _TRUE) &&
               (ScalerDpRx1MeasureLaneCDRClk(ucDpLinkRate, _D1_DP_LANE2) == _TRUE) &&
               (ScalerDpRx1MeasureLaneCDRClk(ucDpLinkRate, _D1_DP_LANE3) == _TRUE))
            {
                return _TRUE;
            }

            break;
    }

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
    if(GET_DP_RX1_SIGNALDETECT_INT_HAPPENED() == _TRUE)
    {
        return _TRUE;
    }
    else
#endif
    {
        DebugMessageRx1("7. wuzanne test : DP CDR Unlock", 0);

        return _FALSE;
    }
}
//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CpIRQ(EnumDpRxBStatusType enumBStatusType)
{
    switch(enumBStatusType)
    {
        case _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL:

            if(GET_DP_RX1_HDCP_MODE() == _HDCP_14)
            {
#if(_DP_MST_SUPPORT == _ON)
                if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & _BIT0) == 0x00)
                {
                    // Reset HDCP Block
                    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
                }

                if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & _BIT1) == _BIT1)
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x20, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x20, 0x05) | _BIT2));
                }
#else
                // Reset HDCP Block
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
#endif

                SET_DP_RX1_AUX_MANUAL_MODE();

                // Clear Aksv
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x07, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x08, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x09, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x0A, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x0B, 0x00);

                SET_DP_RX1_AUX_AUTO_MODE();

                // Set B Status
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) | enumBStatusType));
            }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            else
            {
                // Disable HDCP 2.2 Module
                SET_DP_RX1_HDCP_MODE(_HDCP_14);

                // Disable HDCP2.2 Auth. Done
                ScalerSetBit(PB0_20_HDCP_DEBUG, ~_BIT4, 0x00);

                // Reset HDCP Block
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

                ScalerDpRx1SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) | _BIT4));

                // Clear Authentication Done Flag
                CLR_DP_RX1_HDCP2_AUTHENTICATION_DONE();
            }
#endif
            break;

        case _DP_HDCP_BSTATUS_REAUTH_REQ:

            ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) | _BIT3));

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_RXSTATUS_REAUTH_REQ:

            ScalerDpRx1SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) | _BIT3));

            break;
#endif

        case _DP_HDCP_BSTATUS_V_READY:
        case _DP_HDCP_BSTATUS_R0_AVAILABLE:

            // Set B Status
            ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) | enumBStatusType));

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpRx1SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;

        case _DP_HDCP2_V_READY:

            ScalerDpRx1SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) | (enumBStatusType >> 6)));

            break;
#endif

        default:

            break;
    }

    // Link Status CPIRQ Flag
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) | _BIT2));

    ScalerDpRx1HpdIrqAssert();
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType) using 1
{
    BYTE ucBackUp = 0;

    ucBackUp = ScalerGetByte_EXINT(PBA_D0_AUX_MODE_SET);

    switch(enumBStatusType)
    {
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;

        default:

            break;
    }

    // Link Status CPIRQ Flag
    pData_EXINT[0] = (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x01) | _BIT2);

    // SET AUX AUTO MODE
    SET_DP_RX1_AUX_AUTO_MODE_EXINT();

    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x01, pData_EXINT[0]);

    if((ucBackUp & _BIT1) == 0x00)
    {
        // SET AUX MANUAL MODE
        SET_DP_RX1_AUX_MANUAL_MODE_EXINT();
    }

    ScalerDpRx1HpdIrqAssert_EXINT0();
}
#endif

//--------------------------------------------------
// Description : check DFE Coef
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx1DFECheck(void)
{
    if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_FOUR_LANE:

            // Read Lane2 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane2 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane3 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane3 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description : check DP 8b/10b Decode Error
// Input Value  : None
// Output Value : True --> ok, False --> 8b/10b Decode Error
//--------------------------------------------------
bit ScalerDpRx1DecodeCheck(void)
{
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)

    if(GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE)
    {
        if(GET_DP_RX1_SOURCE_TYPE_JUDGE() == _FALSE)
        {
#if(_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON)
            if(ScalerDpRx1LaneValidCheck() == _FALSE)
            {
                return _TRUE;
            }
#else
            return _TRUE;
#endif
        }
    }

#endif

    pData[1] = 3;

    while(pData[1] > 0)
    {
        // Clear 8b/10b Decode Error Flag
        ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [150,x]
        DELAY_XUS(150);

        switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                {
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if(((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT1 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2)) == 0x00)))
                {
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:

                if(ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
                {
                    return _TRUE;
                }

                break;

            default:

                return _FALSE;

                break;
        }

        pData[1]--;
    }

    DebugMessageRx1("7. DP 8b/10b Decode Error", 0);

    return _FALSE;
}
//--------------------------------------------------
// Description  : DP Display Format Generator Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1DisplayFormatSetting(void)
{
    BYTE ucOddFlg = 0;
    WORD usDpVtotal = 0;
    WORD usDpHactive = 0;
    DWORD ulStreamClkValue = 0;
    DWORD ulVBs2BsCount = 0;

#if(_DP_FREESYNC_SUPPORT == _ON)
    WORD usHBs2BsCount = 0;
    DWORD ulDpMvidValue = 0;
    DWORD ulDpNvidValue = 0;
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
    {
        // Restore VBs2Bs Count
        ulVBs2BsCount = g_stDpRx1LinkInfo.ulVBsToBsCountN;
    }
    else
#endif
    {
        // Measurement Enable
        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
        {
            return _FALSE;
        }

        // Pop up The result
        SET_DP_RX1_MEASURE_POP_UP();

        // Measurement Disable
        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);

        // VBs2BS count in GDI clk
        ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB8_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB8_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB8_5A_MN_MEAS_VLN_L)));
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // Get IVfreq
        PDATA_DWORD(0) = ((DWORD)_GDI_CLK_KHZ * 1000 / (ulVBs2BsCount / 10));

        if((PDATA_DWORD(0) < (_PANEL_FREESYNC_MIN_FRAME_RATE - _FRAME_SYNC_MARGIN)) || (PDATA_DWORD(0) > (_PANEL_FREESYNC_MAX_FRAME_RATE + _FRAME_SYNC_MARGIN)))
        {
            return _FALSE;
        }

        // HBs2Bs count in Link Clk / 2
        usHBs2BsCount = (((DWORD)ScalerGetByte(PB8_5B_MN_MEAS_HLN_M)) << 8) | ((DWORD)ScalerGetByte(PB8_5C_MN_MEAS_HLN_L));

        // VTotal in line, Link Clk / 2 : (Link Rate * 27 / 2)
        usDpVtotal = ulVBs2BsCount * (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2) / usHBs2BsCount * 1000 / _GDI_CLK_KHZ;

        ulDpMvidValue = ((((DWORD)ScalerGetByte(PB9_1A_MSA_MVID_0)) << 16) | (((DWORD)ScalerGetByte(PB9_1B_MSA_MVID_1)) << 8) | ((DWORD)ScalerGetByte(PB9_1C_MSA_MVID_2)));

        ulDpNvidValue = ((((DWORD)ScalerGetByte(PB9_1D_MSA_NVID_0)) << 16) | (((DWORD)ScalerGetByte(PB9_1E_MSA_NVID_1)) << 8) | ((DWORD)ScalerGetByte(PB9_1F_MSA_NVID_2)));

        // [5] ln_ck_sel = 1'b1 -> CDR Clock
        // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

        // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
        ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

        // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
        ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

        // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

        // Waiting for Measure Done
        ScalerTimerDelayXms(2);

        PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

        PDATA_DWORD(0) = ((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ;

        // Calculate streamclk
        ulStreamClkValue = ((DWORD)ulDpMvidValue * (PDATA_DWORD(0) / ulDpNvidValue) + (PDATA_DWORD(0) % ulDpNvidValue * 100 / ulDpNvidValue * (DWORD)ulDpMvidValue / 100));
    }
    else
#endif
    {
        usDpVtotal = ((((WORD)ScalerGetByte(PB9_10_MSA_VTTE_0)) << 8) | ((WORD)ScalerGetByte(PB9_11_MSA_VTTE_1)));

        // Calculate streamclk (Unit is Hz)
        ulStreamClkValue = (((((((DWORD)ScalerGetByte(PB9_08_MSA_HTT_0)) << 8) | ((WORD)ScalerGetByte(PB9_09_MSA_HTT_1))) * ((DWORD)usDpVtotal) * 100) / ulVBs2BsCount) * _GDI_CLK_KHZ * 10);
    }

    // Input Pixel CLK Unit is 0.1 M
    SET_INPUT_PIXEL_CLK(ulStreamClkValue / 100000);

    // Disable Generate Display Format
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT7, 0x00);

    // DP Display Format Generator Reset
    ScalerSetBit(PB8_00_MAC_DIG_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(PB8_00_MAC_DIG_RESET_CTRL, ~_BIT7, 0x00);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
    {
        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);
    }

    // Set Vactive
    ScalerRead(PB9_16_MSA_VHT_0, 2, &pData[4], _AUTOINC);
    ScalerSetByte(PB8_4D_MN_DPF_VHT_M, pData[4]);
    ScalerSetByte(PB8_4E_MN_DPF_VHT_L, pData[5]);

    // Set Hactive
    ScalerRead(PB9_0C_MSA_HWD_0, 2, pData, _AUTOINC);
    ScalerSetByte(PB8_45_MN_DPF_HWD_M, pData[0]);
    ScalerSetByte(PB8_46_MN_DPF_HWD_L, pData[1]);
    usDpHactive = PDATA_WORD(0);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // HTotal in Pixel Clk, Link Clk / 2 : (Link Rate * 27 / 2)
        WORD usDpHtotal = (DWORD)usHBs2BsCount * (GET_INPUT_PIXEL_CLK() / 10) / (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2);

        // Set Htotal
        ScalerSetByte(PB8_41_MN_DPF_HTT_M, HIBYTE(usDpHtotal));
        ScalerSetByte(PB8_42_MN_DPF_HTT_L, LOBYTE(usDpHtotal));

        // Set Hstart
        ScalerSetByte(PB8_43_MN_DPF_HST_M, HIBYTE(_DP_DE_ONLY_MODE_HSTART));
        ScalerSetByte(PB8_44_MN_DPF_HST_L, LOBYTE(_DP_DE_ONLY_MODE_HSTART));

        // Set HSW
        ScalerSetByte(PB8_47_MN_DPF_HSW_M, HIBYTE(_DP_DE_ONLY_MODE_HSW));
        ScalerSetByte(PB8_48_MN_DPF_HSW_L, LOBYTE(_DP_DE_ONLY_MODE_HSW));

        // Set Vstart
        ScalerSetByte(PB8_4B_MN_DPF_VST_M, HIBYTE(_DP_DE_ONLY_MODE_VSTART));
        ScalerSetByte(PB8_4C_MN_DPF_VST_L, LOBYTE(_DP_DE_ONLY_MODE_VSTART));

        // Set VSW
        ScalerSetByte(PB8_4F_MN_DPF_VSW_M, HIBYTE(_DP_DE_ONLY_MODE_VSW));
        ScalerSetByte(PB8_50_MN_DPF_VSW_L, LOBYTE(_DP_DE_ONLY_MODE_VSW));

        PDATA_WORD(0) = GET_DPRX1_BS_TO_HS_DELAY(usDpHtotal);

        // Set HBs2Bs
        ScalerSetByte(PB8_38_BS2HS_0, pData[0]);
        ScalerSetByte(PB8_39_BS2HS_1, pData[1]);

        ScalerDpRx1InterlaceCheck(&usDpVtotal, &ucOddFlg);

        // Set DE Only Mode Vsync Front Porch
        ScalerSetByte(PB8_40_VS_FRONT_PORCH, GET_DP_RX1_VFRONT_PORCH());

        // Set DE Only Mode
        ScalerSetBit(PB8_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), _BIT4);

        // Choose Frame start BE to Reset FIFO
        ScalerSetBit(PB8_20_PG_CTRL_0, ~_BIT5, 0x00);

        // Set DP FREESYNC Mode Enable
        ScalerSetBit(PB8_F0_DP_RSV0, ~_BIT0, _BIT0);

        ScalerDpRx1SetFREESYNCMsaForLut(usDpHtotal);

        DebugMessageRx1("FREESYNC Mode Enabled!!", ScalerGetByte(PB8_30_DPF_CTRL_0));
    }
    else
#endif
    {
        DWORD ulBs2VsDelay = 0;

        // Set Htotal
        ScalerRead(PB9_08_MSA_HTT_0, 2, &pData[2], _AUTOINC);
        ScalerSetByte(PB8_41_MN_DPF_HTT_M, pData[2]);
        ScalerSetByte(PB8_42_MN_DPF_HTT_L, pData[3]);

        // Get HSW
        pData[4] = ScalerGetBit(PB9_0E_MSA_HSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        pData[5] = ScalerGetByte(PB9_0F_MSA_HSW_1);

        // Get HSW min by Measure clock
        PDATA_WORD(3) = ((DWORD) _DP_HSYNC_WIDTH_MEASURE_COUNTER * GET_INPUT_PIXEL_CLK() * 100) / _MEASURE_CLK + 1;

        // Check HSW <= HSW min
        if(PDATA_WORD(2) <= PDATA_WORD(3))
        {
            // Check if H porch is more than HSW min
            if((PDATA_WORD(1) - usDpHactive) >= PDATA_WORD(3))
            {
                // HSW = HSW min
                PDATA_WORD(2) = PDATA_WORD(3);
            }
            else
            {
                // HSW = Max H Porch
                PDATA_WORD(2) = (PDATA_WORD(1) - usDpHactive);
            }
        }

        // DPF H Front Porch must not be less than 8 (HW constraint)
        // Check if H porch is more than 8
        if((PDATA_WORD(1) - usDpHactive - PDATA_WORD(2)) <= _DP_HSYNC_FRONT_PORCH)
        {
            // HSW < HSW min
            if(PDATA_WORD(2) < PDATA_WORD(3))
            {
                // Hstart = HSW
                PDATA_WORD(4) = PDATA_WORD(2);
            }
            else if((PDATA_WORD(1) - usDpHactive - PDATA_WORD(3) >= _DP_HSYNC_FRONT_PORCH))
            {
                // HSW = H porch - _DP_HSYNC_FRONT_PORCH
                PDATA_WORD(2) = PDATA_WORD(1) - usDpHactive - _DP_HSYNC_FRONT_PORCH;

                // Hstart = HSW
                PDATA_WORD(4) = PDATA_WORD(2);
            }
            else
            {
                // HSW = HSW min
                PDATA_WORD(2) = PDATA_WORD(3);

                // Hstart = HSW min
                PDATA_WORD(4) = PDATA_WORD(3);
            }
        }
        else
        {
            // Hstart = Htotal - Hactive - _DP_HSYNC_FRONT_PORCH
            PDATA_WORD(4) = PDATA_WORD(1) - usDpHactive - _DP_HSYNC_FRONT_PORCH;
        }

        // Set HSW and HSP => positive
        ScalerSetByte(PB8_47_MN_DPF_HSW_M, (pData[4] & ~_BIT7));
        ScalerSetByte(PB8_48_MN_DPF_HSW_L, pData[5]);

        // Set Hstart
        ScalerSetByte(PB8_43_MN_DPF_HST_M, pData[8]);
        ScalerSetByte(PB8_44_MN_DPF_HST_L, pData[9]);

        DebugMessageRx1("###Origin usVTotal###", usDpVtotal);

        if(ScalerDpRx1InterlaceCheck(&usDpVtotal, &ucOddFlg) == _TRUE) // Interlace
        {
            DebugMessageRx1("7. IIIIIInterLace Vtotal", usDpVtotal);
        }
        else // Progressive
        {
            DebugMessageRx1("7. PPPPProgressive", 0);
        }

        // Set Vtotal
        ScalerSetByte(PB8_49_MN_DPF_VTT_M, (usDpVtotal >> 8));
        ScalerSetByte(PB8_4A_MN_DPF_VTT_L, (usDpVtotal & 0xFF));

        // Get Vactive
        ScalerRead(PB9_16_MSA_VHT_0, 2, &pData[4], _AUTOINC);

        // V Front porch must not be less than 2 because of V scaling down.
        // Set Vstart -> (Vtotal - Vactive - Frontporch)
        PDATA_WORD(0) = usDpVtotal - PDATA_WORD(2) - GET_DP_RX1_VFRONT_PORCH();
        ScalerSetByte(PB8_4B_MN_DPF_VST_M, pData[0]);
        ScalerSetByte(PB8_4C_MN_DPF_VST_L, pData[1]);

        // Set VSW; Set VSP => Positive
        ScalerSetByte(PB8_4F_MN_DPF_VSW_M, (HIBYTE(_DP_VSYNC_WIDTH) & ~_BIT7));
        ScalerSetByte(PB8_50_MN_DPF_VSW_L, LOBYTE(_DP_VSYNC_WIDTH));

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
        if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
        {
            // Set Odd Field BS to VS Delay
            ScalerSetByte(PB8_35_OVBLK2VS_H, (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayOdd >> 16));
            ScalerSetByte(PB8_36_OVBLK2VS_M, (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayOdd >> 8));
            ScalerSetByte(PB8_37_OVBLK2VS_L, (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayOdd >> 0));

            // Set Even Field BS to VS Delay
            ScalerSetByte(PB8_32_EVBLK2VS_H, (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayEven >> 16));
            ScalerSetByte(PB8_33_EVBLK2VS_M, (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayEven >> 8));
            ScalerSetByte(PB8_34_EVBLK2VS_L, (BYTE)(g_stDpRx1LinkInfo.ulVBsToBsDelayEven >> 0));
        }
        else
#endif
        {
            ulBs2VsDelay = ScalerDpRx1GetBStoVSDelay();

            // Set Odd Field BS to VS Delay
            ScalerSetByte(PB8_35_OVBLK2VS_H, (BYTE)(ulBs2VsDelay >> 16));
            ScalerSetByte(PB8_36_OVBLK2VS_M, (BYTE)(ulBs2VsDelay >> 8));
            ScalerSetByte(PB8_37_OVBLK2VS_L, (BYTE)(ulBs2VsDelay >> 0));

            if((bit)ucOddFlg == _TRUE)
            {
                // Get Htotal
                ScalerRead(PB9_08_MSA_HTT_0, 2, &pData[10], _AUTOINC);

                // BStoVSDelay = BStoVSDelay + (Link Clk * 256 / Stream Clk) * ((DWORD)Htotal) / 256;
                ulBs2VsDelay += ((((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270UL) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(5)) / 256 / 2;

                SET_DP_RX1_INTERLACE_VTOTAL_NUMBER(_ODD);
            }
            else
            {
                SET_DP_RX1_INTERLACE_VTOTAL_NUMBER(_EVEN);
            }

            // Set Even Field BS to VS Delay
            ScalerSetByte(PB8_32_EVBLK2VS_H, (BYTE)(ulBs2VsDelay >> 16));
            ScalerSetByte(PB8_33_EVBLK2VS_M, (BYTE)(ulBs2VsDelay >> 8));
            ScalerSetByte(PB8_34_EVBLK2VS_L, (BYTE)(ulBs2VsDelay >> 0));
        }

        // Choose VS Rising to Reset FIFO
        ScalerSetBit(PB8_20_PG_CTRL_0, ~_BIT5, 0x00);

        // Set DP FREESYNC Mode Disable
        ScalerSetBit(PB8_F0_DP_RSV0, ~_BIT0, 0x00);

        // Set full last line Mode
        ScalerSetBit(PB8_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

        DebugMessageRx1("FREESYNC Mode Disabled", ScalerGetByte(PB8_30_DPF_CTRL_0));
    }

    // Double Buffer to Apply Display Format Setting
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT6, _BIT6);

    ScalerDpRx1VideoSetting();

    return _TRUE;
}
//--------------------------------------------------
// Description  : DP Video Fifo Check
// Input Value  : Fifo Check Condition
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerDpRx1FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition)
{
    if(enumFifoCheckCondition == _DP_FIFO_DELAY_CHECK)
    {
        ScalerSetBit(PB8_21_PG_CTRL_1, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
        if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
        {
            ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

            pData[0] = 0;

            while(pData[0] < 6)
            {
                ScalerTimerDelayXms(10);

                if((ScalerGetBit(PB8_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PB8_21_PG_CTRL_1, _BIT2) == _BIT2))
                {
                    return _FALSE;
                }

                pData[0]++;
            }
        }
    }
    else
    {
        if((ScalerGetBit(PB8_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PB8_21_PG_CTRL_1, _BIT2) == _BIT2))
        {
            return _FALSE;
        }
    }

    if(ScalerGetBit(PB9_3B_DP_IRQ_CTRL1, _BIT4) == 0x00)
    {
        // Enable DP No Video Stream IRQ
        ScalerDpRx1SetNoVideoStreamIRQ(_ENABLE);
    }

    if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x05, _BIT0) == 0x00)
    {
        // Set DP Receive Port0 In Sync
        ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : HDCP Reset For Dp Rx1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPBlockReset(void)
{
    // Reset HDCP Block
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x29, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2A, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2B, 0x00);

    for(pData[0] = 0; pData[0] < 20; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x14 + pData[0]), 0x00);
    }

    for(pData[0] = 0; pData[0] < 15; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), 0x00);
    }

    SET_DP_RX1_AUX_MANUAL_MODE();

    // Clear Aksv
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x07, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x08, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x09, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x0A, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x0B, 0x00);

    SET_DP_RX1_AUX_AUTO_MODE();

#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_IDLE);
#endif
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : None
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpRx1HdcpCheckValid(void)
{
    if(GET_DP_RX1_HDCP_MODE() == _HDCP_14)
    {
        if(ScalerGetBit(PB0_20_HDCP_DEBUG, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
        {
            return _TRUE;
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(ScalerGetBit(PB0_20_HDCP_DEBUG, _BIT4) == _BIT4)
        {
            if((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerDpRx1HdcpCheckEnabled(void)
{
    if(GET_DP_RX1_HDCP_MODE() == _HDCP_14)
    {
        if(ScalerGetBit(PB0_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5))
        {
            if((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) ||
               (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
               (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) ||
               (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
               (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00))
            {
                return _TRUE;
            }
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(ScalerGetBit(PB0_20_HDCP_DEBUG, _BIT4) == _BIT4)
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}
//--------------------------------------------------
// Description  : DP HDCP Measure Check
// Input Value  : None
// Output Value : FALSE => Measure Check Fail
//--------------------------------------------------
bit ScalerDpRx1HdcpMeasureCheck(void)
{
    DWORD ulLinkClk = 0;
    WORD usHTotalCount = 0;

    // Pop up Main Stream Attributes
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Vtotal
    ScalerRead(PB9_10_MSA_VTTE_0, 2, &pData[10], _AUTOINC);

    if(PDATA_WORD(5) == 0)
    {
        return _FALSE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Waiting for Measure Done
    ScalerTimerDelayXms(2);

    if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));
    }
    else
    {
        if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = 0x4E20;
        }
        else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
        {
            PDATA_WORD(0) = 0x2710;
        }
        else // Both Default && _DP_LINK_RBR Case
        {
            PDATA_WORD(0) = 0x1770;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

    // Link Clk in KHz
    ulLinkClk = (PDATA_DWORD(0) / 1000);

    DebugMessageRx1("Current Link Clk", ulLinkClk);

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
    ScalerRead(PB8_58_MN_MEAS_CTRL, 3, &pData[1], _AUTOINC);

    // Get Measure Htotal Counts
    ScalerRead(PB8_5B_MN_MEAS_HLN_M, 2, &pData[6], _AUTOINC);

    // Disable Measure Block
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);

    // Convert HTotal Count from 1/2 Link Clk to GDI Clk
    usHTotalCount = ((DWORD)PDATA_WORD(3) * _GDI_CLK_KHZ * 2 + (ulLinkClk >> 1)) / ulLinkClk;

    PDATA_DWORD(0) = (PDATA_DWORD(0) & 0x001FFFFF);
    PDATA_DWORD(1) = ((DWORD)usHTotalCount & 0x0000FFFF);

    PDATA_WORD(2) = PDATA_DWORD(0) / PDATA_DWORD(1);

    // 2% Tolerance
    if((ABSDWORD(PDATA_WORD(2), PDATA_WORD(5))) > (PDATA_WORD(5) * 2 / 100))
    {
        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : Check DP Hdcp ReAuth Process
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerDpRx1HdcpReAuthStatusCheck(void)
{
    if(GET_DP_RX1_HDCP_MODE() == _HDCP_14)
    {
        if((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) || (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
           (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) || (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
           (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Dp Mac Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MacInitial(void)
{
    // Set Digital Phy to Normal
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // DP RGB Output Enable
    ScalerSetBit(PB8_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // DP CLK Output Enable
    ScalerSetBit(PB8_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, _BIT6);

    // 0x00:disable error correction, 0xF4:enable all error correction
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~_BIT1, _BIT1);

    // Disable DP Fifo Under/OverFlow Watch Dog
    ScalerDpRx1SetFifoWD(_DISABLE);

    // Disable DP Fifo Under/OverFlow IRQ
    ScalerDpRx1SetFifoIRQ(_DISABLE);

    // Disable DP No Video Stream IRQ
    ScalerDpRx1SetNoVideoStreamIRQ(_DISABLE);

    ScalerDpRx1SetInitialRSV0InfoType();

#if((_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON) && (_HW_DP_VSC_SDP_REG_SUPPORT != _ON))
    ScalerDpRx1SetInitialRSV1InfoType();
#endif

    CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();
}
//--------------------------------------------------
// Description : check DP CDR locked or unlocked
// Input Value  : DP Lane
// Output Value : True --> locked; False --> unlocked
//--------------------------------------------------
bit ScalerDpRx1MeasureLaneCDRClk(BYTE ucDpLinkRate, BYTE ucDpRx1LaneNumber)
{
    WORD usCDRClockCount = 0;

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            if((abs(g_pusDpRx1ClockCount[ucDpRx1LaneNumber] - 0x2710)) > (0x2710 >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_HBR:

            if((abs(g_pusDpRx1ClockCount[ucDpRx1LaneNumber] - 0x1388)) > (0x1388 >> 4))
            {
                return _TRUE;
            }

            break;

        default:
        case _DP_LINK_RBR:

            if((abs(g_pusDpRx1ClockCount[ucDpRx1LaneNumber] - 0xBB8)) > (0xBB8 >> 4))
            {
                return _TRUE;
            }

            break;
    }

    // Select Measure CDR Clock & XTAL 27M Count 1000 Times
    ScalerSetByte(PB0_50_DP_SIG_DET_0, 0x23);

    // Select CDR Lane
    ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), ucDpRx1LaneNumber);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // Toggle Start Measure
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            break;
        }
    }

    if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == 0x00)
    {
        return _FALSE;
    }

    usCDRClockCount = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

    if(abs(g_pusDpRx1ClockCount[ucDpRx1LaneNumber] - usCDRClockCount) > (g_pusDpRx1ClockCount[ucDpRx1LaneNumber] >> 7))
    {
        return _FALSE;
    }

    return _TRUE;
}

#if(_DP_LINK_RATE_CHANGE_WO_LT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Rebuild PHY when DPCD Link Rate != PHY Link Rate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1LinkRateChangeRebuildPhy(void)
{
    SET_DP_RX1_AUX_MANUAL_MODE();

    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) && (ScalerDpRx1LinkRateChange() == _TRUE))
    {
        ScalerDpRx1RebuildPhy(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01));

        SET_DP_RX1_AUX_AUTO_MODE();

        // De-Skew Circuit Reset
        ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

        // Mac Reset After Link Clock Stable
        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

        // Delay for Lane Alignment after Mac Reset
        ScalerTimerDelayXms(2);
    }

    SET_DP_RX1_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Check DPCD Link Rate = PHY Link Rate?
// Input Value  : None
// Output Value : True : Link Rate Change
//              : False :
//--------------------------------------------------
bit ScalerDpRx1LinkRateChange(void)
{
    EnumDpLinkRate enumPhyRate = _DP_LINK_NONE;

    if(ScalerGetBit(P7A_23_CMU_09, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        enumPhyRate = _DP_LINK_HBR2;
    }
    else if(ScalerGetBit(P7A_23_CMU_09, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) == (_BIT5 | _BIT3))
    {
        enumPhyRate = _DP_LINK_HBR;
    }
    else if(ScalerGetBit(P7A_23_CMU_09, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) == (_BIT6 | _BIT5))
    {
        enumPhyRate = _DP_LINK_RBR;
    }

    if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == enumPhyRate)
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}
#endif

//--------------------------------------------------
// Description  : Signal PreDetection for DP(Power Normal)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpRx1NormalPreDetect(void)
{
    // For Dp PHY CTS Test
    if((GET_DP_RX1_PHY_CTS_FLG() == _TRUE) || (ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x70, _BIT7) == _BIT7))
    {
        ScalerDpRx1PhyCTS();

        return _FALSE;
    }

#if(_DP_MST_SUPPORT == _ON)

    if(GET_DP_RX1_AUX_CH_POWER_ON_WAKE_UP() == _TRUE)
    {
        CLR_DP_RX1_AUX_CH_POWER_ON_WAKE_UP();
    }

#endif

#if(_DP_RX1_ASSR_MODE_SUPPORT == _ON)

    // ASSR Mode Setting
    ScalerDpRx1ASSRModeSetting();

#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    CLR_DP_RX1_SOURCE_TYPE_JUDGE();
#endif

    switch(GET_DP_RX1_LINK_TRAINING_STATUS())
    {
        case _DP_NORMAL_LINK_TRAINING_PASS:
        case _DP_LINK_STATUS_FAIL:

            CLR_DP_RX1_VALID_VIDEO_CHECK();

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
            if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpRx1DFECheck() == _TRUE) || (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpRx1MarginLinkCheck() == _TRUE) &&
               (ScalerDpRx1AlignCheck() == _TRUE) &&
               (ScalerDpRx1DecodeCheck() == _TRUE))
            {
                /*
                DebugMessageRx1("9. Lane0 LE Diff", (g_pucDpRx1LEMaxTemp[0] - g_pucDpRx1LEMinTemp[0]));
                DebugMessageRx1("9. Lane1 LE Diff", (g_pucDpRx1LEMaxTemp[1] - g_pucDpRx1LEMinTemp[1]));
                DebugMessageRx1("9. Lane2 LE Diff", (g_pucDpRx1LEMaxTemp[2] - g_pucDpRx1LEMinTemp[2]));
                DebugMessageRx1("9. Lane3 LE Diff", (g_pucDpRx1LEMaxTemp[3] - g_pucDpRx1LEMinTemp[3]));
                DebugMessageRx1("9. Lane0 LE Min", g_pucDpRx1LEMinTemp[0]);
                DebugMessageRx1("9. Lane1 LE Min", g_pucDpRx1LEMinTemp[1]);
                DebugMessageRx1("9. Lane2 LE Min", g_pucDpRx1LEMinTemp[2]);
                DebugMessageRx1("9. Lane3 LE Min", g_pucDpRx1LEMinTemp[3]);
                DebugMessageRx1("9. Lane0 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[0] - g_pucDpRx1Tap0MinTemp[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[1] - g_pucDpRx1Tap0MinTemp[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[2] - g_pucDpRx1Tap0MinTemp[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[3] - g_pucDpRx1Tap0MinTemp[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max", g_pucDpRx1Tap0MaxTemp[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max", g_pucDpRx1Tap0MaxTemp[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max", g_pucDpRx1Tap0MaxTemp[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max", g_pucDpRx1Tap0MaxTemp[3]);
                DebugMessageRx1("9. FLD Band", ScalerGetByte(PB0_BF_LANE0_A_CDR_02));
                DebugMessageRx1("9. Best FLD Band", ScalerGetByte(PB0_BE_LANE0_A_CDR_01));
                DebugMessageRx1("9. Lane0 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[0] - g_pucDpRx1Tap0MinTemp2[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[1] - g_pucDpRx1Tap0MinTemp2[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[2] - g_pucDpRx1Tap0MinTemp2[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[3] - g_pucDpRx1Tap0MinTemp2[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[3]);
                DebugMessageRx1("9. TP2 Check Result", g_ucDpRx1EQCRC);
                */

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LONG_HOTPLUG_EVENT);

                g_ucDpRx1FakeLTLaneCount = g_ucDpRx1LaneCount;
#endif
                if(GET_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH() == _TRUE)
                {
#if(_DP_ULTRA_HDR_SUPPORT == _ON)
                    ScalerSyncDpSecDataResetProc(_D1_INPUT_PORT);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                    if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                    {
                        // Need to delay 3 Frames totally after Secondary Data Block Reset
                        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);
                    }
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                    if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                    {
                        ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);
                    }

                    CLR_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH();
                }

                SET_DP_RX1_AUX_MANUAL_MODE();

                if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL)
                {
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);

                    ScalerDpRx1ScrambleSetting();
                }

                SET_DP_RX1_AUX_AUTO_MODE();

                if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
                   (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
                {
                    return _FALSE;
                }

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
                CLR_DP_RX_D1_MARGIN_LINK_HBR2();
#endif

                return _TRUE;
            }
            else
            {
                DebugMessageRx1("7. Link Status Fail IRQ", 0);

#if(_DP_LINK_RATE_CHANGE_WO_LT_SUPPORT == _ON)
                ScalerDpRx1LinkRateChangeRebuildPhy();
#endif
                SET_DP_RX1_AUX_MANUAL_MODE();

                if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
                {
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_STATUS_FAIL);

                    ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
                }

                SET_DP_RX1_AUX_AUTO_MODE();
            }

            break;

        case _DP_LINK_TRAINING_FAIL:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);

            ScalerDpRx1LinkStatusIRQ();

            break;

        case _DP_FAKE_LINK_TRAINING_PASS:
        case _DP_FAKE_LINK_TRAINING_PASS_VBIOS:

            CLR_DP_RX1_VALID_VIDEO_CHECK();

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
            if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
            {
                ScalerTimerDelayXms(30);
            }

            DebugMessageRx1("7. DP Rebuild PHY", GET_DP_RX1_LINK_TRAINING_STATUS());

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);

            SET_DP_RX1_AUX_MANUAL_MODE();

            if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
            {
                ScalerDpRx1RebuildPhy(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01));
            }

            SET_DP_RX1_AUX_AUTO_MODE();

            // De-Skew Circuit Reset
            ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
            ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

            // Mac Reset After Link Clock Stable
            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

            // Delay for Lane Alignment after Mac Reset
            ScalerTimerDelayXms(2);

            if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS)
            {
                ScalerDpRx1DecodeErrorCountReset();
            }

            if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpRx1DFECheck() == _TRUE) || (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpRx1MarginLinkCheck() == _TRUE) &&
               (ScalerDpRx1AlignCheck() == _TRUE) &&
               (ScalerDpRx1DecodeCheck() == _TRUE))
            {
                DebugMessageRx1("7. Rebuild Phy Pass", 0);

                /*
                DebugMessageRx1("9. Lane0 LE Diff", (g_pucDpRx1LEMaxTemp[0] - g_pucDpRx1LEMinTemp[0]));
                DebugMessageRx1("9. Lane1 LE Diff", (g_pucDpRx1LEMaxTemp[1] - g_pucDpRx1LEMinTemp[1]));
                DebugMessageRx1("9. Lane2 LE Diff", (g_pucDpRx1LEMaxTemp[2] - g_pucDpRx1LEMinTemp[2]));
                DebugMessageRx1("9. Lane3 LE Diff", (g_pucDpRx1LEMaxTemp[3] - g_pucDpRx1LEMinTemp[3]));
                DebugMessageRx1("9. Lane0 LE Min", g_pucDpRx1LEMinTemp[0]);
                DebugMessageRx1("9. Lane1 LE Min", g_pucDpRx1LEMinTemp[1]);
                DebugMessageRx1("9. Lane2 LE Min", g_pucDpRx1LEMinTemp[2]);
                DebugMessageRx1("9. Lane3 LE Min", g_pucDpRx1LEMinTemp[3]);
                DebugMessageRx1("9. Lane0 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[0] - g_pucDpRx1Tap0MinTemp[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[1] - g_pucDpRx1Tap0MinTemp[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[2] - g_pucDpRx1Tap0MinTemp[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[3] - g_pucDpRx1Tap0MinTemp[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max", g_pucDpRx1Tap0MaxTemp[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max", g_pucDpRx1Tap0MaxTemp[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max", g_pucDpRx1Tap0MaxTemp[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max", g_pucDpRx1Tap0MaxTemp[3]);
                DebugMessageRx1("9. FLD Band", ScalerGetByte(PB0_BF_LANE0_A_CDR_02));
                DebugMessageRx1("9. Best FLD Band", ScalerGetByte(PB0_BE_LANE0_A_CDR_01));
                DebugMessageRx1("9. D10.2 Counter", g_usDpRx1ClockCount);
                DebugMessageRx1("9. D10.2 Counter1", g_usDpRx1ClockCount1);
                DebugMessageRx1("9. Lane0 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[0] - g_pucDpRx1Tap0MinTemp2[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[1] - g_pucDpRx1Tap0MinTemp2[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[2] - g_pucDpRx1Tap0MinTemp2[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[3] - g_pucDpRx1Tap0MinTemp2[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[3]);
                DebugMessageRx1("9. Best FLD Band", ScalerGetByte(PB0_BE_LANE0_A_CDR_01));
                DebugMessageRx1("9. TP2 Check Result", g_ucDpRx1EQCRC);
                DebugMessageRx1("9. DP Requeset", ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x06));
                DebugMessageRx1("9. DP Requeset", ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x07));
                DebugMessageRx1("9. Lane0 Tap1 Max", ScalerGetByte(P7A_A5_L0_INIT_3));
                DebugMessageRx1("9. Lane1 Tap1 Max", ScalerGetByte(P7A_B5_L1_INIT_3));
                DebugMessageRx1("9. Lane2 Tap1 Max", ScalerGetByte(P7A_C5_L2_INIT_3));
                DebugMessageRx1("9. Lane3 Tap1 Max", ScalerGetByte(P7A_D5_L3_INIT_3));
                */

                SET_DP_RX1_AUX_MANUAL_MODE();

                if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
                {
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);
                    CLR_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH();

                    ScalerDpRx1ScrambleSetting();
                }

                SET_DP_RX1_AUX_AUTO_MODE();

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
                ScalerSyncDpSecDataResetProc(_D1_INPUT_PORT);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                {
                    // Need to delay 3 Frames totally after Secondary Data Block Reset
                    ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);
                }
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
                {
                    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);
                }

                if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
                   (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
                {
                    return _FALSE;
                }

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
                CLR_DP_RX_D1_MARGIN_LINK_HBR2();
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
                if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
                {
                    // Reset Daisy Chain Async-fifo
                    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, _BIT6);
                    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT6, 0x00);
                }
#endif
                return _TRUE;
            }
            else
            {
                DebugMessageRx1("7. DP Rebuild PHY Fail", 0);

                SET_DP_RX1_AUX_MANUAL_MODE();

                if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS)
                {
                    ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);

                    ScalerDpRx1HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    ScalerDpRx1Hdcp2ResetProc();
#endif
                }
                else if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS)
                {
#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
                    ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX1_LONG_HOTPLUG_EVENT);
#endif
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_STATUS_FAIL);

                    SET_DP_RX1_AUX_AUTO_MODE();

                    return _TRUE;
                }

                SET_DP_RX1_AUX_AUTO_MODE();
            }

            break;

        case _DP_LINK_TRAINING_NONE:

            if(GET_DP_RX1_VALID_VIDEO_CHECK() == _TRUE)
            {
                ScalerDpRx1ValidSignalDetection();

                DebugMessageRx1("7. VBIOS Check !!!!!!!", GET_DP_RX1_FAKE_LINK_TRAINING());
            }

            break;

        default:

            break;
    }

    if(GET_DP_RX1_VALID_VIDEO_CHECK() == _TRUE)
    {
        CLR_DP_RX1_VALID_VIDEO_CHECK();

#if(_DP_MST_SUPPORT == _ON)
        ScalerDpRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 1 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
bit ScalerDpRx1PhyCtsTp1Check(void)
{
    // Wait for 10ms
    ScalerTimerDelayXms(10);

    // Clear 8B/10B Decode Error Flags
    ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Wait for 2ms
    ScalerTimerDelayXms(2);

    ScalerSetByte(P7A_0C_SDM_01, ScalerGetByte(PB0_06_DECODE_10B8B_ERROR));
    ScalerSetByte(P7A_0D_SDM_02, ScalerGetByte(PB0_14_EQ_CRC_3));

    switch(g_ucDpRx1PhyCtsCtrl & 0x30)
    {
        case 0x00: // Lane0 Test

            // EQ auto K,Check lane0 CRC
            pData[0] = 0x10;

            break;

        case 0x10: // Lane1 Test

            // EQ auto K,Check lane1 CRC
            pData[0] = 0x20;

            break;

        case 0x20: // Lane2 Test

            // EQ auto K,Check lane2 CRC
            pData[0] = 0x40;

            break;

        case 0x30: // Lane3 Test

            // EQ auto K,Check lane3 CRC
            pData[0] = 0x80;

            break;

        default:

            pData[0] = 0x00;

            break;
    }

    if(((ScalerGetByte(P7A_0C_SDM_01) & 0x0F) == 0x00) &&
       ((ScalerGetByte(P7A_0D_SDM_02) & pData[0]) != 0x00))
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 2 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
bit ScalerDpRx1PhyCtsTp2Check(void)
{
    ScalerTimerDelayXms(10);

    switch(g_ucDpRx1PhyCtsCtrl & 0x30)
    {
        case 0x00: // Lane0 Test

            ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), 0x00);

            break;

        case 0x10: // Lane1 Test

            ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case 0x20: // Lane2 Test

            ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case 0x30: // Lane3 Test

            ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;

        default:
            break;
    }

    // Mac Use Xtal Clk
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    // Clear EQ-CRC
    ScalerSetBit(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

    // Start Calculate EQ-CRC
    ScalerSetBit(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    ScalerTimerDelayXms(2);

    ScalerSetByte(P7A_0C_SDM_01, ScalerGetByte(PB0_12_EQ_CRC_1));
    ScalerSetByte(P7A_0D_SDM_02, ScalerGetByte(PB0_13_EQ_CRC_2));

    // Stop Calculate EQ-CRC
    ScalerSetBit(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

    switch(g_ucDpRx1PhyCtsCtrl & 0x30)
    {
        case 0x00: // Lane0 Test

            pData[0] = 0x01;

            break;

        case 0x10: // Lane1 Test

            pData[0] = 0x02;

            break;

        case 0x20: // Lane2 Test

            pData[0] = 0x04;

            break;

        case 0x30: // Lane3 Test

            pData[0] = 0x08;

            break;

        default:

            pData[0] = 0x00;

            break;
    }

    if((ScalerGetByte(P7A_0C_SDM_01) & pData[0]) != 0x00)
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : DP Phy Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1PhyInitial(void)
{
    /////////////
    // Rx Misc //
    /////////////

    // [1] mhl_mode = 1'b0 --> Disable MHL Mode
    ScalerSetBit(P7A_17_BANDGAP_03, ~_BIT1, 0x00);

    // [4] en_mhl_op = 1'b0 --> Disable D1 Port MHL OP
    // [2] HST_BUF_SEL = 1'b0 --> Disable Hysteresis Amplifier in Clock Lane
    ScalerSetBit(P7A_1B_CMU_01, ~(_BIT4 | _BIT2), 0x00);


    /////////////////////
    // CDR DFE Setting //
    /////////////////////

    // [3:1] LE_lowgain_highboost = 3'b100 --> LE HighGain Mode
    ScalerSetBit(P7A_22_CMU_08, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

    // [7] SEL_DFE_DELAY = 1'b0 --> Normal DFE Delay
    ScalerSetBit(P7A_22_CMU_08, ~_BIT7, 0x00);

    // [0] De_brank_en = 1'b0 --> Disable Blank Function
    ScalerSetBit(P7A_AF_L0_GDI_DE, ~_BIT0, 0x00);
    ScalerSetBit(P7A_BF_L1_GDI_DE, ~_BIT0, 0x00);
    ScalerSetBit(P7A_CF_L2_GDI_DE, ~_BIT0, 0x00);
    ScalerSetBit(P7A_DF_L3_GDI_DE, ~_BIT0, 0x00);

    // [3:0] Set Digital PHY Sampling Edge (APHY to DPHY), Spec Suggest Use 0x0F in 6410/6432
    ScalerSetBit(PB0_05_SAMPLE_EDGE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [7] en_wide_temp = 1'b1 --> Vcp-Vcn = -0.1V
    ScalerSetBit(P7A_35_ANA_CDR_10, ~_BIT7, _BIT7);

    // [3:2] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 700M/v
    // [1:0] reg_vcm_tune = 2'b11 --> Vcm = VDD/2
    ScalerSetBit(P7A_30_ANA_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [4] sel_cont3 = 1'b1 --> BBPD UP/DN Pulse Div 3
    ScalerSetBit(P7A_2D_ANA_CDR_02, ~_BIT4, _BIT4);

    // [3:2] ENHANCE_SA_BIAS = 2'b00 --> SumAmp Bias = Normal
    ScalerSetBit(P7A_1D_CMU_03, ~(_BIT3 | _BIT2), 0x00);

    // [7:4] Enable Data Stream Signal Detection
    ScalerSetBit(P7A_19_IMPEDANCE_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // DP Global Parameter MeasureCount Initial
    ScalerSyncDpMeasureCountInitial();
}
//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : None
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDpRx1ScanInputPort(void)
{
    if(GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _SOURCE_NONE;
    }

    // 2nd Scramble Setting Sync
    ScalerDpRx1ScrambleSetting();

    if(ScalerDpRx1HdcpCheck() == _FALSE)
    {
        DebugMessageRx1("7. DP HDCP Check Fail", 0);

        ScalerDpRx1CpIRQ(_DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

#if(_DP_LONG_HPD_AFTER_CPIRQ_SUPPORT == _ON)
        if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & _BIT0) == 0x00)
        {
            ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
        }
#endif

        return _SOURCE_NONE;
    }

    if(ScalerDpRx1GetVideoStream() == _FALSE)
    {
        DebugMessageRx1("7. DP Video Stream Fail", 0);

        return _SOURCE_NONE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x07) & _BIT7) == _BIT7)
    {
        SET_DP_FREESYNC_ENABLED();
    }
    else
    {
        CLR_FREESYNC_ENABLED();
    }
#endif

    if(ScalerDpRx1MSACheck() == _FALSE)
    {
        DebugMessageRx1("7. DP MSA Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx1GetVideoInfo() == _FALSE)
    {
        DebugMessageRx1("7. DP Get Video Info Fail", 0);

        return _SOURCE_NONE;
    }
    else
    {
        ScalerDpRx1SetColorInfo();
    }

    if(ScalerDpRx1DisplayFormatSetting() == _FALSE)
    {
        DebugMessageRx1("7. DP Display Format Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx1StreamClkRegenerate() == _FALSE)
    {
        DebugMessageRx1("7. DP SteamClk Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx1FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() == _TRUE)
        {
            return _SOURCE_NONE;
        }
        else
#endif
        {
#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if((ScalerSyncCheckUrgentEvent() == _TRUE))
            {
                return _SOURCE_NONE;
            }
#endif

            ScalerDpRx1AdjustVsyncDelay();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if((ScalerSyncCheckUrgentEvent() == _TRUE))
            {
                return _SOURCE_NONE;
            }
#endif

            if(ScalerDpRx1FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
            {
#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if((ScalerSyncCheckUrgentEvent() == _TRUE))
                {
                    return _SOURCE_NONE;
                }
#endif

                ScalerDpRx1AdjustVsyncDelay();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if((ScalerSyncCheckUrgentEvent() == _TRUE))
                {
                    return _SOURCE_NONE;
                }
#endif

                if(ScalerDpRx1FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
                {
                    DebugMessageRx1("7. DP Fifo Fail", 0);

                    return _SOURCE_NONE;
                }
            }
        }
    }

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);

#if(_DP_FREESYNC_SUPPORT == _ON)
    // Measurement Enable for On-Line VFreq check
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);
#endif

    ScalerSetBit(PB8_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

#if(_AUDIO_SUPPORT == _ON)
    // Enable Audio Channel
    ScalerAudioDpAudioEnable(_ENABLE, _D1_INPUT_PORT);
#endif

#if(_DP_MST_SUPPORT == _ON)
    CLR_DP_RX1_SOURCE_FIRST_POWER_ON();
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    ScalerDpRx1InfoFrameRSV0Initial();
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    ScalerFreeSyncDpRx1GetSPDVfreqMaxMin();
#endif

#if((_DP_HDR10_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
    ScalerDpRx1SwitchHDR10CmpAudioInfo();
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    ScalerDpRx1TimingInfoBackup();
#endif

    DebugMessageRx1("Source DP Rx1 Found", 0);

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    SET_DP_RX1_SOURCE_TYPE_JUDGE();
#endif

    return _SOURCE_DP;
}
//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDFEInitial(EnumDpLinkRate enumDpLinkRate)
{
    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [3] Disable Running Length Detection
    // [2] bypass Blank out Case-3 Symbol
    ScalerSetBit(P7A_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    ScalerSetBit(P7A_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    ScalerSetBit(P7A_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    ScalerSetBit(P7A_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

    // [7:6] adapt_mode[1:0] = 2'b11 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 3)
    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetByte(P7A_E0_MODE_TIMER, 0xF2);

    // Set DFE Delay Time
    ScalerSetByte(P7A_E1_TIMER, 0x01);

    // Tap0,Tap1 Loop Gain 1/512
    ScalerSetBit(P7A_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap2,Tap3 Loop Gain 1/512
    ScalerSetBit(P7A_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4,Servo Loop Gain 1/512
    ScalerSetBit(P7A_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // LE Gain1 Loop Gain 1/256, LE Gain2 Loop Gain 0, LE Pre-Courser Gain 0
    ScalerSetBit(P7A_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit(P7A_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap0 Max is 21
    ScalerSetByte(P7A_E6_LIMIT_1, 0x35);

    if(enumDpLinkRate == _DP_LINK_HBR2)
    {
        if(GET_DP_RX1_PHY_CTS_FLG() == _TRUE)
        {
            // Tap1 Min is 49
            ScalerSetBit(P7A_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));
        }
        else
        {
            // Tap1 Min is 46
            ScalerSetBit(P7A_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT2 | _BIT1));
        }
    }
    else
    {
        // Tap1 Min is 51
        ScalerSetBit(P7A_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
    }

    // Tap2 Max is 6, Min is -6
    ScalerSetBit(P7A_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit(P7A_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P7A_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 0, Min is -3
    ScalerSetBit(P7A_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P7A_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 0, Min is -3
    ScalerSetBit(P7A_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P7A_EB_LIMIT_6, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P7A_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Tap0 Threshold = 10
    ScalerSetBit(P7A_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00)
    {
        // Set Vth Max = 6, Min = 0
        ScalerSetByte(P7A_F9_LIMIT_10, 0x60);
    }
    else if(enumDpLinkRate == _DP_LINK_HBR2)
    {
        // Set Vth Max = 6, Min = 4
        ScalerSetByte(P7A_F9_LIMIT_10, 0x64);
    }
    else
    {
        // Set Vth Max = 6, Min = 2
        ScalerSetByte(P7A_F9_LIMIT_10, 0x62);
    }

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetByte(P7A_EC_LOOP_DIV_1, 0xA3);

    // Tap Divider = 10 for TP2
    ScalerSetByte(P7A_ED_LOOP_DIV_2, 0xCA);

    // [1] tap1_trans = 1'b0 --> Tap1 is Effective every bit
    // [0] tap0_trans = 1'b0 --> Tap0 is Effective every bit
    ScalerSetBit(P7A_E3_GAIN_2, ~(_BIT1 | _BIT0), 0x00);

    if(enumDpLinkRate == _DP_LINK_HBR2)
    {
        // [1:0] trans_rlength = 2'b01 --> Tap0 Run Length = 3
        ScalerSetBit(P7A_E4_GAIN_3, ~(_BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // [1:0] trans_rlength = 2'b00 --> Tap0 Run Length = 2
        ScalerSetBit(P7A_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);
    }

    // [5] servo_notrans = 1'b0 --> Servo is Effective every bit
    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective every bit
    ScalerSetBit(P7A_F8_GRAY_DEC_2, ~(_BIT5 | _BIT4), 0x00);


    /////////////////////////
    // DFE Code Initialize //
    /////////////////////////

    if(enumDpLinkRate == _DP_LINK_HBR2)
    {
        if((GET_DP_RX1_PHY_CTS_FLG() == _TRUE) || (ScalerDpRx1GetDpcdBitInfo(0x00, 0x02, 0x70, _BIT7) == _BIT7))
        {
            // LE Max = 18, Initial = 16, Servo Initial = 16
            ScalerSetByte(P7A_A2_L0_LIMIT_INIT, 0x20);
            ScalerSetByte(P7A_B2_L1_LIMIT_INIT, 0x20);
            ScalerSetByte(P7A_C2_L2_LIMIT_INIT, 0x20);
            ScalerSetByte(P7A_D2_L3_LIMIT_INIT, 0x20);
            ScalerSetByte(P7A_A3_L0_INIT_1, 0xD0);
            ScalerSetByte(P7A_B3_L1_INIT_1, 0xD0);
            ScalerSetByte(P7A_C3_L2_INIT_1, 0xD0);
            ScalerSetByte(P7A_D3_L3_INIT_1, 0xD0);
        }
        else
        {
            // LE Max = 20, Initial = 12, Servo Initial = 16
            ScalerSetByte(P7A_A2_L0_LIMIT_INIT, 0x4C);
            ScalerSetByte(P7A_B2_L1_LIMIT_INIT, 0x4C);
            ScalerSetByte(P7A_C2_L2_LIMIT_INIT, 0x4C);
            ScalerSetByte(P7A_D2_L3_LIMIT_INIT, 0x4C);
            ScalerSetByte(P7A_A3_L0_INIT_1, 0x90);
            ScalerSetByte(P7A_B3_L1_INIT_1, 0x90);
            ScalerSetByte(P7A_C3_L2_INIT_1, 0x90);
            ScalerSetByte(P7A_D3_L3_INIT_1, 0x90);
        }
    }
    else
    {
        // LE Max = 20, Initial = 16, Servo Initial = 16
        ScalerSetByte(P7A_A2_L0_LIMIT_INIT, 0x40);
        ScalerSetByte(P7A_B2_L1_LIMIT_INIT, 0x40);
        ScalerSetByte(P7A_C2_L2_LIMIT_INIT, 0x40);
        ScalerSetByte(P7A_D2_L3_LIMIT_INIT, 0x40);
        ScalerSetByte(P7A_A3_L0_INIT_1, 0xD0);
        ScalerSetByte(P7A_B3_L1_INIT_1, 0xD0);
        ScalerSetByte(P7A_C3_L2_INIT_1, 0xD0);
        ScalerSetByte(P7A_D3_L3_INIT_1, 0xD0);
    }

    // Tap0 Initial Value = 18
    ScalerSetByte(P7A_A4_L0_INIT_2, 0x12);
    ScalerSetByte(P7A_B4_L1_INIT_2, 0x12);
    ScalerSetByte(P7A_C4_L2_INIT_2, 0x12);
    ScalerSetByte(P7A_D4_L3_INIT_2, 0x12);

    // Tap1 Initial Value = 15
    ScalerSetByte(P7A_A5_L0_INIT_3, 0x0F);
    ScalerSetByte(P7A_B5_L1_INIT_3, 0x0F);
    ScalerSetByte(P7A_C5_L2_INIT_3, 0x0F);
    ScalerSetByte(P7A_D5_L3_INIT_3, 0x0F);

    // Tap2 Initial Value = 0
    ScalerSetByte(P7A_A6_L0_INIT_4, 0x00);
    ScalerSetByte(P7A_B6_L1_INIT_4, 0x00);
    ScalerSetByte(P7A_C6_L2_INIT_4, 0x00);
    ScalerSetByte(P7A_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 4
    ScalerSetByte(P7A_A9_L0_INIT_7, 0x04);
    ScalerSetByte(P7A_B9_L1_INIT_7, 0x04);
    ScalerSetByte(P7A_C9_L2_INIT_7, 0x04);
    ScalerSetByte(P7A_D9_L3_INIT_7, 0x04);

    // Load Intial DFE Code
    ScalerSetByte(P7A_AA_L0_INIT_8, 0xFF);
    ScalerSetByte(P7A_BA_L1_INIT_8, 0xFF);
    ScalerSetByte(P7A_CA_L2_INIT_8, 0xFF);
    ScalerSetByte(P7A_DA_L3_INIT_8, 0xFF);

    ScalerSetByte(P7A_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P7A_BA_L1_INIT_8, 0x00);
    ScalerSetByte(P7A_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P7A_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetByte(P7A_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P7A_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(P7A_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P7A_D1_L3_DFE_EN_2, 0x00);
}
//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetFifoIRQ(bit bEn)
{
    ScalerSetBit(PB9_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), ((bEn == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
}
//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow Watch Dog
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetFifoWD(bit bEn)
{
    ScalerSetBit(PB9_38_DP_VWD_CTRL, ~(_BIT5 | _BIT4), ((bEn == _ENABLE) ? (_BIT5 | _BIT4) : 0x00));
}

//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : None
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpRx1StableDetect(void)
{
#if(_DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER == _ON)
    if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
#else
    if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
       (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
#endif
    {
        DebugMessageRx1("7. DP Power Down", 0);

        return _FALSE;
    }

    if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE) ||
       (ScalerDpRx1AlignCheck() == _FALSE) ||
       (ScalerDpRx1DecodeCheck() == _FALSE) ||
       ((ScalerDpRx1DFECheck() == _FALSE) && (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE)))
    {
        DebugMessageRx1("7. DP Link Fail", 0);

        return _FALSE;
    }

    if(ScalerDpRx1GetVideoStream() == _FALSE)
    {
        DebugMessageRx1("7. DP Video Stream Fail", 0);

        return _FALSE;
    }

    if(ScalerDpRx1MiscCheck() == _FALSE)
    {
        DebugMessageRx1("7. DP Misc Change", 0);

        return _FALSE;
    }

    if(ScalerDpRx1FifoCheck(_DP_FIFO_POLLING_CHECK) == _FALSE)
    {
        DebugMessageRx1("7. Fifo Under/Overflow", 0);

        return _FALSE;
    }

    if(ScalerDpRx1MSAActiveChange() == _TRUE)
    {
        DebugMessageRx1("7. MSA Timing Change", 0);

        return _FALSE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(ScalerDpRx1GetFREESYNCStatusChange() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Clear CPIRQ Flag
    ScalerDpRx1CheckHdcpCpirqStatus();

    ScalerDpRx1CrcCalculate();

    return _TRUE;
}
//--------------------------------------------------
// Description  : Dp Rx Set Valid Signal Detection Active Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ValidSignalDetectionActiveEvent(void)
{
#if(_DP_MST_SUPPORT == _ON)
    ScalerTimerActiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);
#else
    ScalerTimerActiveTimerEvent(SEC(1.2), _SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);
#endif
}

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Backup Timing Info for Modern Standby
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1TimingInfoBackup(void)
{
    // Backup Offset Value of Stream Clock
    g_stDpRx1LinkInfo.lStreamClockOffset = ((((SDWORD)ScalerGetBit(PB8_BA_MN_SCLKG_SDM_SUMC_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << 16) |
                                            (((WORD)ScalerGetByte(PB8_BB_MN_SCLKG_SDM_SUMC_M)) << 8) |
                                            (ScalerGetByte(PB8_BC_MN_SCLKG_SDM_SUMC_L))) >> 1;

    // Backup VBs2Bs Delay of Even Field
    g_stDpRx1LinkInfo.ulVBsToBsDelayEven = (((DWORD)ScalerGetByte(PB8_32_EVBLK2VS_H)) << 16) |
                                           (((WORD)ScalerGetByte(PB8_33_EVBLK2VS_M)) << 8) |
                                           (ScalerGetByte(PB8_34_EVBLK2VS_L));

    // Backup VBs2Bs Delay of Odd Field
    g_stDpRx1LinkInfo.ulVBsToBsDelayOdd = (((DWORD)ScalerGetByte(PB8_35_OVBLK2VS_H)) << 16) |
                                          (((WORD)ScalerGetByte(PB8_36_OVBLK2VS_M)) << 8) |
                                          (ScalerGetByte(PB8_37_OVBLK2VS_L));
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx LT Status Check
// Input Value  : None
// Output Value : True --> LT Status Pass
//                False --> LT Status Fail
//--------------------------------------------------
bit ScalerDpRx1LTStatusCheck(void)
{
    if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
       (ScalerDpRx1AlignCheck() == _TRUE) &&
       (ScalerDpRx1DecodeCheck() == _TRUE) &&
       ((ScalerDpRx1DFECheck() == _TRUE) || (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE)))
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable HDCP Read IRQ Function
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPEnableReadIrq(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A) > 3)
        {
            ScalerSetBit(PBA_FA_DUMMY_0, ~_BIT0, _BIT0);

            ScalerSetBit(PBA_FA_DUMMY_0, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));
        }
    }
    else
    {
        ScalerSetBit(PBA_FA_DUMMY_0, ~(_BIT3 | _BIT1), 0x00);

        CLR_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT();
    }
}
//--------------------------------------------------
// Description  : DP Adjust Vsync Delay
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstToSstAdjustVsyncDelay(void)
{
    DWORD ulBStoVSDelayDeltaOverflow = 0;
    DWORD ulBStoVSDelayDeltaUnderflow = 0;

    if(ScalerGetBit(PA_31_PG_CTRL_1, (_BIT1 | _BIT0)) == 0x00)// Fifo Ok
    {
        return;
    }
    else if(ScalerGetBit(PA_31_PG_CTRL_1, _BIT0) == _BIT0) // Fifo Overflow
    {
        // Get Htotal
        ScalerRead(PA_10_MSA_HTT_0, 2, &pData[0], _AUTOINC);

        // ((Link Clk * 256)/ Stream CLK) * Htotal / 256 --> 1 Line
        ulBStoVSDelayDeltaOverflow = (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 270UL) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(0)) / 256;

        DebugMessageRx1("DP MST2SST : Fifo Overflow --> nVidia Case", ulBStoVSDelayDeltaOverflow);
    }
    else if(ScalerGetBit(PA_31_PG_CTRL_1, _BIT1) == _BIT1) // Fifo Underflow
    {
        // Get Hactive
        ScalerRead(PA_14_MSA_HWD_0, 2, &pData[0], _AUTOINC);

        if(PDATA_WORD(0) != 1366)
        {
            return;
        }

        PDATA_WORD(0) = PDATA_WORD(0) - 2;

        // Set Hactive
        ScalerSetByte(PA_44_MN_DPF_HWD_M, pData[0]);
        ScalerSetByte(PA_45_MN_DPF_HWD_L, pData[1]);

        // ((Link Clk * 2)/ Stream CLK) --> 2 pixels
        ulBStoVSDelayDeltaUnderflow = (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 270) * 2) / ((DWORD)GET_INPUT_PIXEL_CLK());

        DebugMessageRx1("DP MST2SST : Fifo Underflow --> QD882 Case", ulBStoVSDelayDeltaUnderflow);
    }

    // For Initial Value Before Use PDATA_DWORD(0)
    pData[0] = 0;

    // Get BStoVSDelay Even
    ScalerRead(PA_37_EVBLK2VS_H, 3, &pData[1], _AUTOINC);

    // For Initial Value Before Use PDATA_DWORD(1)
    pData[4] = 0;

    // Get BStoVSDelay Odd
    ScalerRead(PA_3A_OVBLK2VS_H, 3, &pData[5], _AUTOINC);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    PDATA_DWORD(0) = PDATA_DWORD(0) - ((ulBStoVSDelayDeltaOverflow + ulBStoVSDelayDeltaUnderflow) / 2);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    PDATA_DWORD(1) = PDATA_DWORD(1) - ((ulBStoVSDelayDeltaOverflow + ulBStoVSDelayDeltaUnderflow) / 2);

    // Set Even Field BS to VS Delay
    ScalerSetByte(PA_37_EVBLK2VS_H, pData[1]);
    ScalerSetByte(PA_38_EVBLK2VS_M, pData[2]);
    ScalerSetByte(PA_39_EVBLK2VS_L, pData[3]);

    // Set Odd Field BS to VS Delay
    ScalerSetByte(PA_3A_OVBLK2VS_H, pData[5]);
    ScalerSetByte(PA_3B_OVBLK2VS_M, pData[6]);
    ScalerSetByte(PA_3C_OVBLK2VS_L, pData[7]);

    // Enable Double Buffer
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT6, _BIT6);

    // Reset Display Format Gen
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT7, _BIT7);

    // Polling Vertical BS
    ScalerTimerPollingFlagProc(50, PA_29_MST2SST_VBID, _BIT0, _TRUE);

    // Delay for PG Stable
    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);
}
//--------------------------------------------------
// Description  : DP MST2SST Display Format Generator Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1MstToSstDisplayFormatSetting(void)
{
    BYTE ucOddFlg = 0;
    WORD usDpVtotal = 0;
    WORD usDpHactive = 0;
    DWORD ulStreamClkValue = 0;
    DWORD ulVBs2BsCount = 0;

#if(_DP_FREESYNC_SUPPORT == _ON)
    WORD usHBs2BsCount = 0;
    DWORD ulDpMvidValue = 0;
    DWORD ulDpNvidValue = 0;
#endif

    // Measurement Enable
    ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PA_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The result
    SET_DP_RX1_MEASURE_POP_UP_MST2SST();

    // Measurement Disable
    ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT7, 0x00);

    // VBs2BS count in GDI clk
    ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PA_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PA_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PA_5A_MN_MEAS_VLN_L)));

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MST_FREESYNC_ENABLED() == _TRUE)
    {
        // HBs2Bs count in Link Clk / 2
        usHBs2BsCount = (((DWORD)ScalerGetByte(PA_5B_MN_MEAS_HLN_M)) << 8) | ((DWORD)ScalerGetByte(PA_5C_MN_MEAS_HLN_L));

        // VTotal in line, Link Clk / 2 : (Link Rate * 27 / 2)
        usDpVtotal = ulVBs2BsCount * (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2) / usHBs2BsCount * 1000 / _GDI_CLK_KHZ;

        ulDpMvidValue = ((((DWORD)ScalerGetByte(PA_20_MSA_MVID_00)) << 16) | (((DWORD)ScalerGetByte(PA_21_MSA_MVID_01)) << 8) | ((DWORD)ScalerGetByte(PA_22_MSA_MVID_02)));

        ulDpNvidValue = ((((DWORD)ScalerGetByte(PA_23_MSA_NVID_00)) << 16) | (((DWORD)ScalerGetByte(PA_24_MSA_NVID_01)) << 8) | ((DWORD)ScalerGetByte(PA_25_MSA_NVID_02)));

        // [5] ln_ck_sel = 1'b1 -> CDR Clock
        // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

        // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
        ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

        // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
        ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

        // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

        // Waiting for Measure Done
        ScalerTimerDelayXms(2);

        PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

        PDATA_DWORD(0) = ((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ;

        // Calculate streamclk
        ulStreamClkValue = ((DWORD)ulDpMvidValue * (PDATA_DWORD(0) / ulDpNvidValue) + (PDATA_DWORD(0) % ulDpNvidValue * 100 / ulDpNvidValue * (DWORD)ulDpMvidValue / 100));
    }
    else
#endif
    {
        usDpVtotal = ((((WORD)ScalerGetByte(PA_18_MSA_VTT_0)) << 8) | ((WORD)ScalerGetByte(PA_19_MSA_VTT_1)));

        // Calculate streamclk (Unit is Hz)
        ulStreamClkValue = (((((((DWORD)ScalerGetByte(PA_10_MSA_HTT_0)) << 8) | ((WORD)ScalerGetByte(PA_11_MSA_HTT_1))) * ((DWORD)usDpVtotal) * 100) / ulVBs2BsCount) * _GDI_CLK_KHZ * 10);
    }

    // Input Pixel CLK Unit is 0.1 M
    SET_DP_TX_INPUT_PIXEL_CLK(ulStreamClkValue / 100000);

    // Disable Generate Display Format
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT7, 0x00);

    // DP Display Format Generator Reset
    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT0, _BIT0);
    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT0, 0x00);

    // Delay a Complete Frame
    ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

    // Set Vactive
    ScalerRead(PA_1C_MSA_VHT_0, 2, &pData[4], _AUTOINC);
    ScalerSetByte(PA_4C_MN_DPF_VHT_M, pData[4]);
    ScalerSetByte(PA_4D_MN_DPF_VHT_L, pData[5]);

    // Set Hactive
    ScalerRead(PA_14_MSA_HWD_0, 2, pData, _AUTOINC);
    ScalerSetByte(PA_44_MN_DPF_HWD_M, pData[0]);
    ScalerSetByte(PA_45_MN_DPF_HWD_L, pData[1]);
    usDpHactive = PDATA_WORD(0);

#if(_DP_FREESYNC_SUPPORT == _ON)

    ScalerDpTxSSTSetAmdSpdInfo(_ON);

    if(GET_DP_MST_FREESYNC_ENABLED() == _TRUE)
    {
        // HTotal in Pixel Clk, Link Clk / 2 : (Link Rate * 27 / 2)
        WORD usDpHtotal = (DWORD)usHBs2BsCount * (GET_DP_TX_INPUT_PIXEL_CLK() / 10) / (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2);

        // Set Htotal
        ScalerSetByte(PA_40_MN_DPF_HTT_M, HIBYTE(usDpHtotal));
        ScalerSetByte(PA_41_MN_DPF_HTT_L, LOBYTE(usDpHtotal));

        // Set Hstart
        ScalerSetByte(PA_42_MN_DPF_HST_M, HIBYTE(_DP_DE_ONLY_MODE_HSTART));
        ScalerSetByte(PA_43_MN_DPF_HST_L, LOBYTE(_DP_DE_ONLY_MODE_HSTART));

        // Set HSW
        ScalerSetByte(PA_46_MN_DPF_HSW_M, HIBYTE(_DP_DE_ONLY_MODE_HSW));
        ScalerSetByte(PA_47_MN_DPF_HSW_L, LOBYTE(_DP_DE_ONLY_MODE_HSW));

        // Set Vstart
        ScalerSetByte(PA_4A_MN_DPF_VST_M, HIBYTE(_DP_DE_ONLY_MODE_VSTART));
        ScalerSetByte(PA_4B_MN_DPF_VST_L, LOBYTE(_DP_DE_ONLY_MODE_VSTART));

        // Set VSW
        ScalerSetByte(PA_4E_MN_DPF_VSW_M, HIBYTE(_DP_DE_ONLY_MODE_VSW));
        ScalerSetByte(PA_4F_MN_DPF_VSW_L, LOBYTE(_DP_DE_ONLY_MODE_VSW));

        PDATA_WORD(0) = ScalerDpRx1MstToSstGetBStoHSDelay(usDpHtotal);

        // Set HBs2Bs
        ScalerSetByte(PA_3D_BS2HS_0, pData[0]);
        ScalerSetByte(PA_3E_BS2HS_1, pData[1]);

        ScalerDpRx1MstToSstInterlaceCheck(&usDpVtotal, &ucOddFlg);

        // Set DE Only Mode Vsync Front Porch
        ScalerSetByte(PA_3F_VS_FRONT_PORCH, GET_DP_RX1_VFRONT_PORCH());

        // Set DE Only Mode
        ScalerSetBit(PA_35_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), _BIT4);

        // Choose Frame start BE to Reset FIFO
        ScalerSetBit(PA_30_PG_CTRL_0, ~_BIT5, 0x00);

        // Set DP FREESYNC Mode Enable
        ScalerSetBit(PA_F0_DP_RSV0, ~_BIT0, _BIT0);

        DebugMessageRx1("MST FREESYNC Mode Enabled!!", ScalerGetByte(PA_35_DPF_CTRL_0));
    }
    else
#endif
    {
        DWORD ulBs2VsDelay = 0;

        // Set Htotal
        ScalerRead(PA_10_MSA_HTT_0, 2, &pData[2], _AUTOINC);
        ScalerSetByte(PA_40_MN_DPF_HTT_M, pData[2]);
        ScalerSetByte(PA_41_MN_DPF_HTT_L, pData[3]);

        // Get HSW
        pData[4] = ScalerGetBit(PA_16_MSA_HSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        pData[5] = ScalerGetByte(PA_17_MSA_HSW_1);

        // Get HSW min by Measure clock
        PDATA_WORD(3) = ((DWORD) _DP_HSYNC_WIDTH_MEASURE_COUNTER * GET_DP_TX_INPUT_PIXEL_CLK() * 100) / _MEASURE_CLK + 1;

        // Check HSW <= HSW min
        if(PDATA_WORD(2) <= PDATA_WORD(3))
        {
            // Check if H porch is more than HSW min
            if((PDATA_WORD(1) - usDpHactive) >= PDATA_WORD(3))
            {
                // HSW = HSW min
                PDATA_WORD(2) = PDATA_WORD(3);
            }
            else
            {
                // HSW = Max H Porch
                PDATA_WORD(2) = (PDATA_WORD(1) - usDpHactive);
            }
        }

        // Get Hstart
        pData[8] = ScalerGetByte(PA_12_MSA_HST_0);
        pData[9] = ScalerGetByte(PA_13_MSA_HST_1);

        // H Front Porch = (Htotal - Hactive - Hstart) < 8
        if((PDATA_WORD(1) - usDpHactive - PDATA_WORD(4)) < _DP_HSYNC_FRONT_PORCH)
        {
            // DPF H Front Porch must not be less than 8 (HW constraint)
            // Check if H porch is more than 8
            if((PDATA_WORD(1) - usDpHactive - PDATA_WORD(2)) <= _DP_HSYNC_FRONT_PORCH)
            {
                // HSW < HSW min
                if(PDATA_WORD(2) < PDATA_WORD(3))
                {
                    // Hstart = HSW
                    PDATA_WORD(4) = PDATA_WORD(2);
                }
                else if((PDATA_WORD(1) - usDpHactive - PDATA_WORD(3)) >= _DP_HSYNC_FRONT_PORCH)
                {
                    // HSW = H porch - _DP_HSYNC_FRONT_PORCH
                    PDATA_WORD(2) = PDATA_WORD(1) - usDpHactive - _DP_HSYNC_FRONT_PORCH;

                    // Hstart = HSW
                    PDATA_WORD(4) = PDATA_WORD(2);
                }
                else
                {
                    // HSW = HSW min
                    PDATA_WORD(2) = PDATA_WORD(3);

                    // Hstart = HSW min
                    PDATA_WORD(4) = PDATA_WORD(3);
                }
            }
            else
            {
                // Hstart = Htotal - Hactive - _DP_HSYNC_FRONT_PORCH
                PDATA_WORD(4) = PDATA_WORD(1) - usDpHactive - _DP_HSYNC_FRONT_PORCH;
            }
        }

        // Set HSW and HSP => positive
        ScalerSetByte(PA_46_MN_DPF_HSW_M, (pData[4] & ~_BIT7));
        ScalerSetByte(PA_47_MN_DPF_HSW_L, pData[5]);

        // Set Hstart
        ScalerSetByte(PA_42_MN_DPF_HST_M, pData[8]);
        ScalerSetByte(PA_43_MN_DPF_HST_L, pData[9]);

        DebugMessageRx1("###Origin usVTotal###", usDpVtotal);

        if(ScalerDpRx1MstToSstInterlaceCheck(&usDpVtotal, &ucOddFlg) == _TRUE) // Interlace
        {
            DebugMessageRx1("7. MST IIIIIInterLace Vtotal", usDpVtotal);

            SET_DP_TX_INPUT_INTERLACE_MODE(_ON);
        }
        else // Progressive
        {
            DebugMessageRx1("7. MST PPPPProgressive", 0);

            SET_DP_TX_INPUT_INTERLACE_MODE(_OFF);
        }

        // Set Vtotal
        ScalerSetByte(PA_48_MN_DPF_VTT_M, (usDpVtotal >> 8));
        ScalerSetByte(PA_49_MN_DPF_VTT_L, (usDpVtotal & 0xFF));

        // Get Vactive
        ScalerRead(PA_1C_MSA_VHT_0, 2, &pData[4], _AUTOINC);

        // V Front porch must not be less than 2 because of V scaling down.
        // Set Vstart -> (Vtotal - Vactive - Frontporch)
        PDATA_WORD(0) = usDpVtotal - PDATA_WORD(2) - GET_DP_RX1_MST_TO_SST_VFRONT_PORCH();
        ScalerSetByte(PA_4A_MN_DPF_VST_M, pData[0]);
        ScalerSetByte(PA_4B_MN_DPF_VST_L, pData[1]);

        // Set VSW; Set VSP => Positive
        ScalerSetByte(PA_4E_MN_DPF_VSW_M, (HIBYTE(_DP_VSYNC_WIDTH_MST2SST) & ~_BIT7));
        ScalerSetByte(PA_4F_MN_DPF_VSW_L, LOBYTE(_DP_VSYNC_WIDTH_MST2SST));

        ulBs2VsDelay = ScalerDpRx1MstToSstGetBStoVSDelay();

        // Set Odd Field BS to VS Delay
        ScalerSetByte(PA_3A_OVBLK2VS_H, (BYTE)(ulBs2VsDelay >> 16));
        ScalerSetByte(PA_3B_OVBLK2VS_M, (BYTE)(ulBs2VsDelay >> 8));
        ScalerSetByte(PA_3C_OVBLK2VS_L, (BYTE)(ulBs2VsDelay >> 0));

        if((bit)ucOddFlg == _TRUE)
        {
            // Get Htotal
            ScalerRead(PA_10_MSA_HTT_0, 2, &pData[0], _AUTOINC);

            // BStoVSDelay = BStoVSDelay + (Link Clk * 256 / Stream Clk) * ((DWORD)Htotal) / 256;
            ulBs2VsDelay += ((((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270UL) * 256) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(0)) / 256 / 2;

            SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(_ODD);
        }
        else
        {
            SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(_EVEN);
        }

        // Set Even Field BS to VS Delay
        ScalerSetByte(PA_37_EVBLK2VS_H, (BYTE)(ulBs2VsDelay >> 16));
        ScalerSetByte(PA_38_EVBLK2VS_M, (BYTE)(ulBs2VsDelay >> 8));
        ScalerSetByte(PA_39_EVBLK2VS_L, (BYTE)(ulBs2VsDelay >> 0));

        // Choose VS Rising to Reset FIFO
        ScalerSetBit(PA_30_PG_CTRL_0, ~_BIT5, 0x00);

        // Set DP FREESYNC Mode Disable
        ScalerSetBit(PA_F0_DP_RSV0, ~_BIT0, 0x00);

        // Set full last line Mode
        ScalerSetBit(PA_35_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

        DebugMessageRx1("MST FREESYNC Mode Disabled!!", ScalerGetByte(PA_35_DPF_CTRL_0));
    }

    // Double Buffer to Apply Display Format Setting
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT6, _BIT6);

    ScalerDpRx1MstToSstVideoSetting();

    return _TRUE;
}
//--------------------------------------------------
// Description  : DP MST2SST Video Fifo Check
// Input Value  : Fifo Check Condition
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerDpRx1MstToSstFifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition)
{
    if(enumFifoCheckCondition == _DP_FIFO_DELAY_CHECK)
    {
        ScalerSetBit(PA_31_PG_CTRL_1, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

        pData[0] = 0;

        while(pData[0] < 6)
        {
            ScalerTimerDelayXms(10);

            if((ScalerGetBit(PA_31_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PA_31_PG_CTRL_1, _BIT2) == _BIT2))
            {
                return _FALSE;
            }

            pData[0]++;
        }
    }
    else
    {
        if((ScalerGetBit(PA_31_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PA_31_PG_CTRL_1, _BIT2) == _BIT2))
        {
            return _FALSE;
        }
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : DP MST2SST BS to VS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
DWORD ScalerDpRx1MstToSstGetBStoVSDelay(void)
{
    DWORD ulVFrontPorch = 0;
    DWORD ulHFrontPorch = 0;
    WORD usFifoOffset = 0;

    // Get Htotal
    ScalerRead(PA_10_MSA_HTT_0, 2, &pData[2], _AUTOINC);

    // VFrontPorch = 3 * Htotal * (Link Clk / Stream CLK)
    ulVFrontPorch = ((DWORD)GET_DP_RX1_MST_TO_SST_VFRONT_PORCH()) * ((DWORD)PDATA_WORD(1) * 256) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK()) *
                    (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / 256;

    // Get Hactive
    ScalerRead(PA_14_MSA_HWD_0, 2, pData, _AUTOINC);

    // Get HSW
    pData[4] = ScalerGetBit(PA_16_MSA_HSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    pData[5] = ScalerGetByte(PA_17_MSA_HSW_1);

    // Get HSW min by Measure clock
    PDATA_WORD(3) = ((DWORD) _DP_HSYNC_WIDTH_MEASURE_COUNTER * GET_DP_TX_INPUT_PIXEL_CLK() * 100) / _MEASURE_CLK + 1;

    // Check HSW <= HSW min
    if(PDATA_WORD(2) <= PDATA_WORD(3))
    {
        // Check if H porch is more than HSW min
        if((PDATA_WORD(1) - PDATA_WORD(0)) >= PDATA_WORD(3))
        {
            // HSW = HSW min
            PDATA_WORD(2) = PDATA_WORD(3);
        }
        else
        {
            // HSW = Max H Porch
            PDATA_WORD(2) = (PDATA_WORD(1) - PDATA_WORD(0));
        }
    }

    // Get Hstart
    pData[8] = ScalerGetByte(PA_12_MSA_HST_0);
    pData[9] = ScalerGetByte(PA_13_MSA_HST_1);

    // H Front Porch = (Htotal - Hactive - Hstart) < 8
    if((PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(4)) < _DP_HSYNC_FRONT_PORCH)
    {
        // DPF H Front Porch must not be less than 8 (HW constraint)
        // Check if H porch is more than 8
        if((PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(2)) <= _DP_HSYNC_FRONT_PORCH)
        {
            // HSW < HSW min
            if(PDATA_WORD(2) < PDATA_WORD(3))
            {
                // Hstart = HSW
                PDATA_WORD(4) = PDATA_WORD(2);
            }
            else if((PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(3)) >= _DP_HSYNC_FRONT_PORCH)
            {
                // HSW = H porch - _DP_HSYNC_FRONT_PORCH
                PDATA_WORD(2) = PDATA_WORD(1) - PDATA_WORD(0) - _DP_HSYNC_FRONT_PORCH;

                // Hstart = HSW
                PDATA_WORD(4) = PDATA_WORD(2);
            }
            else
            {
                // HSW = HSW min
                PDATA_WORD(2) = PDATA_WORD(3);

                // Hstart = HSW min
                PDATA_WORD(4) = PDATA_WORD(3);
            }
        }
        else
        {
            // Hstart = Htotal - Hactive - _DP_HSYNC_FRONT_PORCH
            PDATA_WORD(4) = PDATA_WORD(1) - PDATA_WORD(0) - _DP_HSYNC_FRONT_PORCH;
        }
    }

    // HFrontPorch = (Htotal - Hactive - Hstart) * (Link Clk / Stream CLK)
    ulHFrontPorch = (((DWORD)(PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(4))) * (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK()));

    // Get MISC Info
    ScalerRead(PA_28_MSA_COLOR_BIT, 1, &pData[14], _NON_AUTOINC);

    switch(pData[14] & (_BIT2 | _BIT1 | _BIT0))
    {
        case 0x00:
            pData[15] = 6;
            break;

        case (_BIT0):
            pData[15] = 8;
            break;

        case (_BIT1):
            pData[15] = 10;
            break;

        case (_BIT1 | _BIT0):
            pData[15] = 12;
            break;

        case (_BIT2):
            pData[15] = 16;
            break;

        default:
            break;
    }

    // DP fifo size = 256 x 96bit
    if(ScalerGetBit(PA_28_MSA_COLOR_BIT, (_BIT4 | _BIT3)) == _BIT3)
    {
        // FifoOffset = (1/2 * (256 * 96) / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (4 * (WORD)pData[15]);
    }
    else
    {
        // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (6 * (WORD)pData[15]);
    }

    // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)) * (Link Clk / Stream CLK))
    usFifoOffset = (WORD)(((DWORD)usFifoOffset) * (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK()));

    return ((ulVFrontPorch + ulHFrontPorch + (DWORD)usFifoOffset) / 2);
}
//--------------------------------------------------
// Description  : DP MST2SST Get Video Info
// Input Value  : None
// Output Value : _TRUE --> Get Successfully
//--------------------------------------------------
bit ScalerDpRx1MstToSstGetVideoInfo(void)
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

        SET_DP_RX1_MST2SST_RSV1_DETECTING();

        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_MST2SST_RSV1_PACKET_DETECT);

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
// Description  : Check Dp Video Straam VBID
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpRx1MstToSstGetVideoStream(void)
{
    // Check if ST2_Source is Assigned the STx Stream In MST Mode
    if((ScalerGetBit(PB0_01_PHY_DIG_RESET_CTRL, _BIT7) == _BIT7) &&
       (ScalerGetBit(PB8_0D_SOURCE_SEL_0, (_BIT2 | _BIT1 | _BIT0)) == 0x00))
    {
        return _FALSE;
    }

    if(ScalerGetBit(PA_29_MST2SST_VBID, _BIT3) == 0x00)
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check DP Vactive / Hactive Information
// Input Value  : None
// Output Value : True --> DP Vactive / Hactive Information Check Ok
//--------------------------------------------------
bit ScalerDpRx1MstToSstMSAActiveChange(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT3, _BIT3);

    // Get Display Format Hactive
    ScalerRead(PA_44_MN_DPF_HWD_M, 2, &pData[0], _AUTOINC);

    // Get MSA Hactive
    ScalerRead(PA_14_MSA_HWD_0, 2, &pData[2], _AUTOINC);

    // Get Display Format Vactive
    ScalerRead(PA_4C_MN_DPF_VHT_M, 2, &pData[4], _AUTOINC);

    // Get MSA Vactive
    ScalerRead(PA_1C_MSA_VHT_0, 2, &pData[6], _AUTOINC);

    if((PDATA_WORD(0) != PDATA_WORD(1)) || (PDATA_WORD(2) != PDATA_WORD(3)))
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check Dp MST2SSST MSA info.
// Input Value  : None
// Output Value : True --> Get MSA
//--------------------------------------------------
bit ScalerDpRx1MstToSstMSACheck(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT3, _BIT3);

    // Get Hactive
    ScalerRead(PA_14_MSA_HWD_0, 2, &pData[4], _AUTOINC);

    // Get Vactive
    ScalerRead(PA_1C_MSA_VHT_0, 2, &pData[12], _AUTOINC);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MST_FREESYNC_ENABLED() == _TRUE)
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
        ScalerRead(PA_10_MSA_HTT_0, 2, &pData[0], _AUTOINC);

        // Get Hstart
        ScalerRead(PA_12_MSA_HST_0, 2, &pData[2], _AUTOINC);

        // Get HSW
        ScalerRead(PA_16_MSA_HSW_0, 2, &pData[6], _AUTOINC);

        // Get Vtotal
        ScalerRead(PA_18_MSA_VTT_0, 2, &pData[8], _AUTOINC);

        // Get Vstart
        ScalerRead(PA_1A_MSA_VST_0, 2, &pData[10], _AUTOINC);

        // Get VSW
        ScalerRead(PA_1E_MSA_VSW_0, 2, &pData[14], _AUTOINC);

        if((PDATA_WORD(0) == 0x00) || (PDATA_WORD(1) == 0x00) || (PDATA_WORD(2) == 0x00) || ((PDATA_WORD(3) & 0x7FFF) == 0x00) ||
           (PDATA_WORD(4) == 0x00) || (PDATA_WORD(5) == 0x00) || (PDATA_WORD(6) == 0x00) || ((PDATA_WORD(7) & 0x7FFF) == 0x00))
        {
            return _FALSE;
        }
    }

    // Get Mvid
    ScalerRead(PA_20_MSA_MVID_00, 3, pData, _AUTOINC);

    if((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) == 0x00)
    {
        return _FALSE;
    }

    // Get Nvid
    ScalerRead(PA_23_MSA_NVID_00, 3, pData, _AUTOINC);

    if((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) == 0x00)
    {
        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : DP Rx1 MST to SST Measure
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1MstToSstMeasureInput(void)
{
    // Format Conversion Select to SST_D1
    ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_SST << 4));

    // DPTx CTS Fifo reset
    ScalerSetBit(PBB_D7_DPTX_CTSFIFO_CTRL, ~_BIT2, 0x00);
    ScalerSetBit(PBB_D7_DPTX_CTSFIFO_CTRL, ~_BIT2, _BIT2);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MST_FREESYNC_ENABLED() == _TRUE)
    {
        return ScalerDpTxMeasureInputInfo();
    }
    else
#endif
    {
        return ScalerDpTxInputMSAInfo();
    }
}
//--------------------------------------------------
// Description  : Check DP MST2SST Misc Information
// Input Value  : None
// Output Value : True --> DP Misc Check Ok
//--------------------------------------------------
bit ScalerDpRx1MstToSstMiscCheck(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    // Check MISC1[6]
    if((ScalerGetBit(PA_27_MSA_MISC_1, _BIT6)) == _BIT6)
    {
        return ScalerDpRx1MstToSstVscCheck();
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
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : None
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDpRx1MstToSstScanInputPort(void)
{
    if(ScalerDpRx1MstToSstGetVideoStream() == _FALSE)
    {
        return _FALSE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    ScalerDpTxAuxNativeRead(0x00, 0x01, 0x07, 1, pData);

    if((pData[0] & _BIT7) == _BIT7)
    {
        SET_DP_MST_FREESYNC_ENABLED();
    }
    else
    {
        CLR_DP_MST_FREESYNC_ENABLED();
    }
#endif

    if(ScalerDpRx1MstToSstMSACheck() == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx1MstToSstGetVideoInfo() == _FALSE)
    {
        return _FALSE;
    }
    else
    {
        ScalerDpRx1MstToSstSetColorInfo();
    }

    if(ScalerDpRx1MstToSstDisplayFormatSetting() == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx1MstToSstStreamClkRegenerate() == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx1MstToSstFifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
    {
        ScalerDpRx1MstToSstAdjustVsyncDelay();

        if(ScalerDpRx1MstToSstFifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
        {
            return _FALSE;
        }
    }

    // DP MST2SST RGB Output Enable
    ScalerSetBit(PA_36_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // DP MST2SST CLK Output Enable
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, _BIT6);

    // Enable Under/OverFlow WatchDog
    SET_REG_DP_RX_MST2SST_WATCH_DOG_ENABLE();

    return _TRUE;
}
//--------------------------------------------------
// Description  : DP MST2SST Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstToSstVideoSetting(void)
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

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP BS to HS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
WORD ScalerDpRx1MstToSstGetBStoHSDelay(WORD usDpHtotal)
{
    WORD usFifoOffset = 0;

    // Get MISC Info
    ScalerRead(PA_28_MSA_COLOR_BIT, 1, &pData[14], _NON_AUTOINC);

    switch(pData[14] & (_BIT2 | _BIT1 | _BIT0))
    {
        case 0x00:
            pData[15] = 6;
            break;

        case (_BIT0):
            pData[15] = 8;
            break;

        case (_BIT1):
            pData[15] = 10;
            break;

        case (_BIT1 | _BIT0):
            pData[15] = 12;
            break;

        case (_BIT2):
            pData[15] = 16;
            break;

        default:
            pData[15] = 8;
            break;
    }

    // DP fifo size = 256 x 96bit
    if(ScalerGetBit(PA_28_MSA_COLOR_BIT, (_BIT4 | _BIT3)) == _BIT3)
    {
        // FifoOffset = (1/2 * (256 * 96) / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (4 * (WORD)pData[15]);
    }
    else
    {
        // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (6 * (WORD)pData[15]);
    }

    // Get Hstart
    ScalerRead(PA_42_MN_DPF_HST_M, 2, &pData[0], _AUTOINC);

    // Get Hactive
    ScalerRead(PA_44_MN_DPF_HWD_M, 2, &pData[2], _AUTOINC);

    // H Blanking = HTotal - HActive
    PDATA_WORD(2) = usDpHtotal - PDATA_WORD(1);

    // Set BS to HS delay to (HBlanking + 1/2 FIFO - HStart), BS2HS delay: 2 pixel mode
    return ((WORD)((PDATA_WORD(2) + usFifoOffset - PDATA_WORD(0)) >> 1));
}
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DP MST2SST VSC Information
// Input Value  : None
// Output Value : True --> DP VSC Check Ok
//--------------------------------------------------
bit ScalerDpRx1MstToSstVscCheck(void)
{
    BYTE pucVscColorFormat[3];

    memset(pucVscColorFormat, 0, sizeof(pucVscColorFormat));

#if(_HW_DP_VSC_SDP_REG_SUPPORT == _ON)

    // Read DB16~18 --> pucVscColorFormat[0:2]
    ScalerRead(PBC_59_VSC_RX_DB16, 3, pucVscColorFormat, _AUTOINC);
#else
    if(GET_DP_RX1_MST2SST_RSV1_DETECTING() == _FALSE)
    {
        // Read DB16~18 --> pucVscColorFormat[0:2]
        ScalerGetDataPortByte(PBC_55_DP_INFO_FM_ADR, _DP_INFO_RSV1_DB16, 3, pucVscColorFormat, _AUTOINC);

        SET_DP_RX1_MST2SST_RSV1_DETECTING();

        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_MST2SST_RSV1_PACKET_DETECT);
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
#endif

//--------------------------------------------------
// Description  : Set DP Rx DPCD DFP Detail Cap Reset
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DfpDeviceDetailConfigReset(void)
{
#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _OFF)
    ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x80, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Set DP Rx DPCD DFP Detail Set
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DfpDeviceDetailConfig(void)
{
#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _OFF)
    ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x80, (_BIT6 | _BIT4 | _BIT3));
#endif
}
#endif

#endif

//--------------------------------------------------
// Description  : Read DP Rx Error Count
// Input Value  : DP Input Port
// Output Value : DP 4 Lane Error Count & Valid Flag
//--------------------------------------------------
StructDpRxErrorCount ScalerDpRx1GetErrorCount(void)
{
    StructDpRxErrorCount stDpRxErrorCount;

    if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE) ||
       (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE))
    {
        DebugMessageSystem("Rx Fail to Report Valid Error Counter", 0x00);

        switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            case _DP_TWO_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            default:
            case _DP_FOUR_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0x7FFF;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0x7FFF;

                break;
        }
    }
    else
    {
        switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            case _DP_TWO_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE1);
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            default:
            case _DP_FOUR_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE1);
                stDpRxErrorCount.usDpRxLane2ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE2);
                stDpRxErrorCount.usDpRxLane3ErrorCount = ScalerDpRx1GetDecodeErrorCount(_D1_DP_LANE3);

                break;
        }
    }

    // Reset Error Counter
    ScalerDpRx1DecodeErrorCountReset();

    return stDpRxErrorCount;
}
#endif // End of #if(_D1_DP_EXIST == _ON)

