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
// ID Code      : ScalerDPRx0_SeptPhy.c No.0000
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
#if(_D0_DP_EXIST == _ON)
BYTE g_ucDpRx0PhyCtsCtrl;
EnumHDCPType g_enumDpRx0HdcpMode;
StructDpLanesMapping g_stDpRx0LanesMapping;

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
bit g_bDpRx0SourceTypeJudge = _FALSE;
#endif

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT != _ON)
BYTE g_ucDpRx0DPCD02200hValue = _DP_VERSION_1_4;
BYTE g_ucDpRx0DPCD02201hValue = _D0_DP_LINK_CLK_RATE;
BYTE g_ucDpRx0DPCD02210hValue;
#endif

#if(_DP_MST_SUPPORT == _ON)
StructDPRxMiscInfo g_stDpRx0MiscInfo;
BYTE g_pucDpRx0MstTimeSlotBackup[13];
BYTE g_pucDpMacRx0MstStMuxBackup[5];
#endif

#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_D0_DP_EXIST == _ON)
void ScalerDpRx0AdjustVsyncDelay(void);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
bit ScalerDpRx0CheckVgipVsBypass(void);
#endif

void ScalerDpRx0SetNoVideoStreamIRQ(bit bEn);
void ScalerDpRx0DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);
DWORD ScalerDpRx0GetBStoVSDelay(void);
void ScalerDpRx0Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
bit ScalerDpRx0MarginLinkCheck(void);
void ScalerDpRx0LinkStatusIRQ(void);
void ScalerDpRx0AuxSet(void);
void ScalerDpRx0HpdIrqAssert(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
void ScalerDpRx0HpdIrqAssert_EXINT0(void);
void ScalerDpRx0CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType);
#endif
EnumDpHotPlugTime ScalerDpRx0BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType);
void ScalerDpRx0AfterHpdToggleProc(void);

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
bit ScalerDpRx0DecodeErrorCountCheck(WORD usTimeCriteria, BYTE ucErrorCriteria);
bit ScalerDpRx0DecodeErrorCountLaneMeasure(BYTE ucErrorCriteria, BYTE ucDpRx0LaneNumber);
bit ScalerDpRx0LaneBsCheck(void);
#endif

bit ScalerDpRx0ChangeSrambleSeed(void);
#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)
bit ScalerDpRx0VbiosAssrCheck(bit bMSACheckResult);
#endif
bit ScalerDpRx0PSPreDetect(void);
void ScalerDpRx0SetDpLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
void ScalerDpRx6Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport);
#endif

#if(_DP_MST_SUPPORT == _ON)
void ScalerDpRx0MstInfoBackup(EnumDpMstBackup enumDpMstBackup);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
bit ScalerDpRx6AuxChSourcePowerCheck(void);
void ScalerDpRx6AuxChPowerStatusCheck(bit bCableStatus);
void ScalerDpRx6MstInfoBackup(EnumDpMstBackup enumDpMstBackup);
#endif

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRx0HDCPAuthShaRun(bit bIsFirst);
void ScalerDpRx0HDCPChangeAuthState(EnumDPRxHDCPAuthState enumHDCPAuthState);
bit ScalerDpRx0HDCPCheckBinfo(void);
bit ScalerDpRx0HDCPCheckLvp(void);
void ScalerDpRx0HDCPFakeAuthenProc(void);
void ScalerDpRx0HDCPHandler(void);
void ScalerDpRx0HDCPLoadKsvFifo(void);
void ScalerDpRx0HDCPLoadShaToDpcd(void);
void ScalerDpRx0HDCPSetKsvFifoFirst(void);
void ScalerDpRx0HDCPSetReadIrqTimeout(void);
void ScalerDpRx0HDCPSetRepeaterProcTimeout(void);
void ScalerDpRx0HDCPSha1Calculate(BYTE *pucInputArray, BYTE ucCalCount);
void ScalerDpRx0HDCPWriteShaInput(void);
#if(_DP_HDCP14_CTS_SUPPORT == _ON)
bit ScalerDpRx0HDCPDeviceCountChange(void);
#endif
void ScalerDpRx0MstToSstAdjustVsyncDelay(void);
DWORD ScalerDpRx0MstToSstGetBStoVSDelay(void);
bit ScalerDpRx0MstToSstGetVideoStream(void);
bit ScalerDpRx0MstToSstMSAActiveChange(void);
bit ScalerDpRx0MstToSstMSACheck(void);
void ScalerDpRx0MstToSstProc(void);
BYTE ScalerDpRx0MstToSstScanInputPort(void);
bit ScalerDpRx0MstToSstStableDetect(void);

#if(_DP_FREESYNC_SUPPORT == _ON)
WORD ScalerDpRx0MstToSstGetBStoHSDelay(WORD usDpHtotal);
#endif

void ScalerDpRx0DfpDeviceDetailConfigReset(void);
void ScalerDpRx0DfpDeviceDetailConfig(void);
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#endif // End of #if(_DP_MST_SUPPORT == _ON)

void ScalerDpRx0AdjustLaneFLDBand(BYTE ucDpRx0LaneNumber, WORD usVCOBandDiff);
bit ScalerDpRx0CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
void ScalerDpRx0CpIRQ(EnumDpRxBStatusType enumBStatusType);
bit ScalerDpRx0DFECheck(void);
bit ScalerDpRx0AlignCheck(void);
bit ScalerDpRx0DecodeCheck(void);
bit ScalerDpRx0DisplayFormatSetting(void);
bit ScalerDpRx0FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
void ScalerDpRx0HDCPBlockReset(void);
bit ScalerDpRx0HdcpCheckValid(void);
bit ScalerDpRx0HdcpCheckEnabled(void);
bit ScalerDpRx0HdcpMeasureCheck(void);
bit ScalerDpRx0HdcpReAuthStatusCheck(void);
void ScalerDpRx0MacInitial(void);
bit ScalerDpRx0MeasureLaneCDRClk(BYTE ucDpLinkRate, BYTE ucDpRx0LaneNumber);
bit ScalerDpRx0PhyCtsTp1Check(void);
bit ScalerDpRx0PhyCtsTp2Check(void);
void ScalerDpRx0PhyInitial(void);
BYTE ScalerDpRx0ScanInputPort(void);
void ScalerDpRx0SetDFEInitial(EnumDpLinkRate enumDpLinkRate);
void ScalerDpRx0SetFifoIRQ(bit bEn);
void ScalerDpRx0SetFifoWD(bit bEn);
bit ScalerDpRx0StableDetect(void);
void ScalerDpRx0SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
void ScalerDpRx0TimingInfoBackup(void);
#endif

#if(_DP_MST_SUPPORT == _ON)
bit ScalerDpRx0LTStatusCheck(void);

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRx0HDCPEnableReadIrq(bit bEnable);
bit ScalerDpRx0MstToSstDisplayFormatSetting(void);
bit ScalerDpRx0MstToSstFifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
bit ScalerDpRx0MstToSstMeasureInput(void);
#endif

#endif
StructDpRxErrorCount ScalerDpRx0GetErrorCount(void);
#endif // End of #if(_D0_DP_EXIST == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D0_DP_EXIST == _ON)
//--------------------------------------------------
// Description  : DP Adjust Vsync Delay
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AdjustVsyncDelay(void)
{
    DWORD ulBStoVSDelayDeltaOverflow = 0;
    DWORD ulBStoVSDelayDeltaUnderflow = 0;

    if(ScalerGetBit(PB5_21_PG_CTRL_1, (_BIT1 | _BIT0)) == 0x00)// Fifo Ok
    {
        return;
    }
    else if(ScalerGetBit(PB5_21_PG_CTRL_1, _BIT0) == _BIT0) // Fifo Overflow
    {
        // Get Htotal
        ScalerRead(PB6_08_MSA_HTT_0, 2, &pData[0], _AUTOINC);

        // ((Link Clk * 256)/ Stream CLK) * Htotal / 256 --> 1 Line
        ulBStoVSDelayDeltaOverflow = (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 270UL) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(0)) / 256;

        DebugMessageRx0("7. Fifo Overflow --> nVidia Case", ulBStoVSDelayDeltaOverflow);
    }
    else if(ScalerGetBit(PB5_21_PG_CTRL_1, _BIT1) == _BIT1) // Fifo Underflow
    {
        // Get Hactive
        ScalerRead(PB6_0C_MSA_HWD_0, 2, &pData[0], _AUTOINC);

        if(PDATA_WORD(0) != 1366)
        {
            return;
        }

        PDATA_WORD(0) = PDATA_WORD(0) - 2;

        // Set Hactive
        ScalerSetByte(PB5_45_MN_DPF_HWD_M, pData[0]);
        ScalerSetByte(PB5_46_MN_DPF_HWD_L, pData[1]);

        // ((Link Clk * 2)/ Stream CLK) --> 2 pixels
        ulBStoVSDelayDeltaUnderflow = (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 270) * 2) / ((DWORD)GET_INPUT_PIXEL_CLK());

        DebugMessageRx0("7. Fifo Underflow --> QD882 Case", ulBStoVSDelayDeltaUnderflow);
    }

    // For Initial Value Before Use PDATA_DWORD(0)
    pData[0] = 0;

    // Get BStoVSDelay Even
    ScalerRead(PB5_32_EVBLK2VS_H, 3, &pData[1], _AUTOINC);

    // For Initial Value Before Use PDATA_DWORD(1)
    pData[4] = 0;

    // Get BStoVSDelay Odd
    ScalerRead(PB5_35_OVBLK2VS_H, 3, &pData[5], _AUTOINC);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    PDATA_DWORD(0) = PDATA_DWORD(0) - ((ulBStoVSDelayDeltaOverflow + ulBStoVSDelayDeltaUnderflow) / 2);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    PDATA_DWORD(1) = PDATA_DWORD(1) - ((ulBStoVSDelayDeltaOverflow + ulBStoVSDelayDeltaUnderflow) / 2);

    // Set Even Field BS to VS Delay
    ScalerSetByte(PB5_32_EVBLK2VS_H, pData[1]);
    ScalerSetByte(PB5_33_EVBLK2VS_M, pData[2]);
    ScalerSetByte(PB5_34_EVBLK2VS_L, pData[3]);

    // Set Odd Field BS to VS Delay
    ScalerSetByte(PB5_35_OVBLK2VS_H, pData[5]);
    ScalerSetByte(PB5_36_OVBLK2VS_M, pData[6]);
    ScalerSetByte(PB5_37_OVBLK2VS_L, pData[7]);

    // Enable Double Buffer
    ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT6, _BIT6);

    // Reset Display Format Gen
    ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT7, _BIT7);

    // Polling Vertical BS
    ScalerTimerPollingFlagProc(50, PB6_01_DP_VBID, _BIT0, _TRUE);

    // Delay for PG Stable
    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);
}

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check VGIP VS bypass for DP
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpRx0CheckVgipVsBypass(void)
{
    // Get Hstart
    ScalerRead(PB5_43_MN_DPF_HST_M, 2, &pData[0], _AUTOINC);

    // Get Vstart
    ScalerRead(PB5_4B_MN_DPF_VST_M, 2, &pData[2], _AUTOINC);

    // Check for nVedia 2560x1440@144Hz timing (reduced blanking)
    if((PDATA_WORD(0) < _VGIP_IH_CAPTURE_MIN_VALUE) ||
       (PDATA_WORD(1) <= _VGIP_IV_CAPTURE_MIN_VALUE))
    {
        DebugMessageRx0("DP RX0 VGIP VS Bypass Mode", PDATA_WORD(0));

        return _TRUE;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetNoVideoStreamIRQ(bit bEn)
{
    // VB-ID[3] Change Flag
    ScalerSetBit(PB6_36_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

    // VB-ID[3] Change IRQ
    ScalerSetBit(PB6_3B_DP_IRQ_CTRL1, ~_BIT4, ((bEn == _ENABLE) ? _BIT4 : 0x00));
}

//--------------------------------------------------
// Description  : DPCD Link Status Field Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus)
{
    DebugMessageRx0("DP Rx0 Dpcd Link Status Reset", 0);

    pData[0] = ScalerGetByte(PB7_D0_AUX_MODE_SET);

    SET_DP_RX0_AUX_MANUAL_MODE();

    if(enumDpResetStatus == _DP_DPCD_LINK_STATUS_INITIAL)
    {
        // Set DPCD 00600h to 0x01
        ScalerDpRx0SetDpcdBitValue(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x04, 0x80);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x05, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x06, 0x00);
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x07, 0x00);

    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    CLR_DP_RX0_BACKUP_PD_LINK_STATUS_FLG();

    if((pData[0] & _BIT1) == _BIT1)
    {
        SET_DP_RX0_AUX_AUTO_MODE();
    }

#if(_DP_MST_SUPPORT == _ON)

    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
    {
        pData[0] = ScalerGetByte(PB7_D0_AUX_MODE_SET);

        SET_DP_RX0_AUX_AUTO_MODE();

        pData[1] = ScalerDpRx0GetDpcdInfo(0x00, 0x20, 0x05);
        ScalerDpRx0SetDpcdValue(0x00, 0x20, 0x05, (pData[1] | _BIT1));

        ScalerDpRx0SetDpcdValue(0x00, 0x02, 0xC0, (ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0xC0) & ~_BIT1));

        if((pData[0] & _BIT1) != _BIT1)
        {
            SET_DP_RX0_AUX_MANUAL_MODE();
        }
    }

#endif
}
//--------------------------------------------------
// Description  : DP BS to VS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
DWORD ScalerDpRx0GetBStoVSDelay(void)
{
    DWORD ulVFrontPorch = 0;
    DWORD ulHFrontPorch = 0;
    WORD usFifoOffset = 0;

    // Get Htotal
    ScalerRead(PB6_08_MSA_HTT_0, 2, &pData[2], _AUTOINC);

    // VFrontPorch = 3 * Htotal * (Link Clk / Stream CLK)
    ulVFrontPorch = ((DWORD)GET_DP_RX0_VFRONT_PORCH()) * ((DWORD)PDATA_WORD(1) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) *
                    ((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 270) / 256;

    // Get Hactive
    ScalerRead(PB6_0C_MSA_HWD_0, 2, pData, _AUTOINC);

    // Get HSW
    pData[4] = ScalerGetBit(PB6_0E_MSA_HSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    pData[5] = ScalerGetByte(PB6_0F_MSA_HSW_1);

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
    ulHFrontPorch = (((DWORD)(PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(4))) * (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_INPUT_PIXEL_CLK()));

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
    usFifoOffset = (WORD)(((DWORD)usFifoOffset) * (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_INPUT_PIXEL_CLK()));

    return ((ulVFrontPorch + ulHFrontPorch + (DWORD)usFifoOffset) / 2);
}
//--------------------------------------------------
// Description  : Initial Setting for DP
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport)
{
    ScalerDpRx0AuxPowerOnInitial();

    ScalerDpRx0DpcdInitial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumFreeSyncSupport);

    // Must be initialized "AFTER DPCD setting" to avoid entering interruption unexpectively
    ScalerDpRx0AuxIntInitial();

    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    SET_DP_RX0_FAKE_LINK_TRAINING();

    SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
    SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);
    SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

    SET_DP_RX0_HDCP_MODE_BACKUP(_HDCP_14);

    ScalerDpRx0SetDpLaneMapping(_TYPE_C_PIN_ASSIGNMENT_C, _TYPE_C_ORIENTATION_UNFLIP);

#if(_DP_MST_SUPPORT == _ON)
    CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
    CLR_DP_RX0_CHECK_AUX_CH_POWER_STATUS();
#endif

#if(_DP_TX_SUPPORT == _ON)
    CLR_DP_RX0_HDCP_AUTH_AKSV_WRITTEN();
#endif
}

//--------------------------------------------------
// Description  : DP Margin Link Check
// Input Value  : None
// Output Value : _TRUE : Link ok ; _FALSE : Margin Link
//--------------------------------------------------
bit ScalerDpRx0MarginLinkCheck(void)
{
    switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00))
    {
        case _DP_LINK_HBR2:

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
            if((ScalerDpRx0DFECheck() == _TRUE) &&
               (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               (ScalerDpRx0LaneBsCheck() == _TRUE) &&
               (ScalerDpRx0DecodeErrorCountCheck(_DP_HBR2_MARGIN_LINK_TIME_CRITERIA, _DP_HBR2_MARGIN_LINK_ERROR_CRITERIA) == _FALSE))
            {
                if((ScalerDpRx0DFECheck() == _TRUE) &&
                   (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
                   (ScalerDpRx0LaneBsCheck() == _TRUE))
                {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                    if((GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT) && (ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE))
                    {
                        SET_DP_RX_D0_MARGIN_LINK_HBR2();
                        return _FALSE;
                    }
                    else if((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (ScalerSyncDpCableStatus(_D6_INPUT_PORT) == _TRUE))
                    {
                        SET_DP_RX_D6_MARGIN_LINK_HBR2();
                        return _FALSE;
                    }
#else
                    if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
                    {
                        SET_DP_RX_D0_MARGIN_LINK_HBR2();
                        return _FALSE;
                    }
#endif
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
void ScalerDpRx0LinkStatusIRQ(void)
{
    SET_DP_RX0_AUX_MANUAL_MODE();

    if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_FAIL) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
    {
        ScalerDpRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_RESET);

        SET_DP_RX0_AUX_AUTO_MODE();

        ScalerDpRx0HDCPBlockReset();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        ScalerDpRx0Hdcp2ResetProc();
#endif

        if((ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
           (ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_WD_TIMER_INT_SUPPORT == _ON))
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_RX0_HDCP2_SKE);
#endif

            ScalerDpRx0HpdIrqAssert();
        }
    }

    SET_DP_RX0_AUX_AUTO_MODE();
}

//-------------------------------------------------------
// Description  : Set Aux Diff mode or Single-eneded mode
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpRx0AuxSet(void)
{
    if(GET_DP_AUX_DIFF_MODE() == _FALSE)
    {
        // Set TX VLDO = 1.05V, Open AUX ADJR_P, Rx Common Mode from 3.3V
        ScalerSetByte(PB7_61_AUX_1, ((_DP_AUX_SWING_1050_MV << 5) | _BIT4));

        // [5]Enable Single-Ended Mode, [4:3]Aux Vth-->50mV, [0]Aux 50ohm auto K(Enable Big_Z0_P)
        ScalerSetByte(PB7_62_AUX_2, 0x29);

        // [4]Enable Big_Z0_N, [3:0]Open ADJR_N
        ScalerSetBit(PB7_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    }
    else
    {
        // Set TX VLDO = 1.05V, Rx Common Mode from 3.3V
        ScalerSetBit(PB7_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((_DP_AUX_SWING_1050_MV << 5) | _BIT4));

        // [5]Disable Single-Ended Mode, [4:3]Aux Vth-->50mV, [0]Aux 50ohm auto K(Enable Big_Z0_P)
        ScalerSetByte(PB7_62_AUX_2, 0x09);

        // [4]Enable Big_Z0_N
        ScalerSetBit(PB7_66_AUX_6, ~_BIT4, _BIT4);

        // AUX RX0 P Channel Resistance Setting
        ScalerSetBit(PB7_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());

        // AUX RX0 N Channel Resistance Setting
        ScalerSetBit(PB7_66_AUX_6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());
    }
}

//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HpdIrqAssert(void)
{
    if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
    {
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
        SET_DP_D0_HPD_IRQ_ASSERT_T2_EVENT();
#else

        BYTE ucBackUp2 = ScalerGetByte(PB7_D0_AUX_MODE_SET);

#if(_DP_TX_SUPPORT == _ON)
        // Disable IRQs that take too long
        BYTE ucBackUp1 = ScalerGetBit(PBB_72_HPD_IRQ_EN, _BIT6);
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);
#endif

        SET_DP_RX0_AUX_MANUAL_MODE();

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);

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

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);

        if((ucBackUp2 & _BIT1) == _BIT1)
        {
            SET_DP_RX0_AUX_AUTO_MODE();
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
void ScalerDpRx0HpdIrqAssert_EXINT0(void) using 1
{
    if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
    {
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
        SET_DP_D0_HPD_IRQ_ASSERT_T2_EVENT();
#else

        BYTE ucBackUp2 = ScalerGetByte_EXINT(PB7_D0_AUX_MODE_SET);

#if(_DP_TX_SUPPORT == _ON)
        // Disable IRQs that take too long
        BYTE ucBackUp1 = ScalerGetBit_EXINT(PBB_72_HPD_IRQ_EN, _BIT6);
        ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);
#endif

        SET_DP_RX0_AUX_MANUAL_MODE_EXINT();

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);

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

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);

        if((ucBackUp2 & _BIT1) == _BIT1)
        {
            SET_DP_RX0_AUX_AUTO_MODE_EXINT();
        }

#if(_DP_TX_SUPPORT == _ON)
        ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, ucBackUp1);
#endif
#endif
    }
}

//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0CpIRQ_EXINT0(EnumDpRxBStatusType enumBStatusType) using 1
{
    BYTE ucBackUp = 0;

    ucBackUp = ScalerGetByte_EXINT(PB7_D0_AUX_MODE_SET);

    switch(enumBStatusType)
    {
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpRx0SetDpcdValue_EXINT0(0x06, 0x94, 0x93, (ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;

        default:

            break;
    }

    // Link Status CPIRQ Flag
    pData_EXINT[0] = (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x01) | _BIT2);

    // SET AUX AUTO MODE
    SET_DP_RX0_AUX_AUTO_MODE_EXINT();

    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x01, pData_EXINT[0]);

    if((ucBackUp & _BIT1) == 0x00)
    {
        // SET AUX MANUAL MODE
        SET_DP_RX0_AUX_MANUAL_MODE_EXINT();
    }

    ScalerDpRx0HpdIrqAssert_EXINT0();
}
#endif

//--------------------------------------------------
// Description  : Dp Before Hpd Toggle Process
// Input Value  : EnumDpHotPlugAssertType
// Output Value : None
//--------------------------------------------------
EnumDpHotPlugTime ScalerDpRx0BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType)
{
    if(enumHpdType == _DP_HPD_NONE)
    {
        return _DP_HPD_TIME_NONE;
    }

    if(enumHpdType == _DP_HPD_ASSERTED)
    {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if((PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH) && (GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_ON))
#else
        if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
#endif
        {
            return _DP_HPD_TIME_NONE;
        }
    }

    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_WD_TIMER_INT_SUPPORT == _ON))
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_RX0_HDCP2_SKE);
#endif

#if(_DP_MST_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
#if(_DP_TX_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_CPIRQ_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_REPEATER_PROC_TIMEOUT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_READ_IRQ_TIMEOUT);
#endif
#endif

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if((enumHpdType != _DP_HDCP_LONG_HPD_EVENT) && (enumHpdType != _DP_HBR2_MARGIN_LINK_HPD_EVENT) && ((ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x00) >= _DP_VERSION_1_2) || (ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)))
    {
        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
        {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D0_DP_LINK_CLK_RATE)) ||
               ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpRx0GetDpcdInfo(0x00, 0x22, 0x01) < _D0_DP_LINK_CLK_RATE)))
#else
            if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D0_DP_LINK_CLK_RATE)) ||
               ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (g_ucDpRx0DPCD02201hValue < _D0_DP_LINK_CLK_RATE)))
#endif
            {
                if(_D0_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
                {
                    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
                }
                else
                {
                    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
                }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                // When Define Extended Rx Cap Should Set DPCD 0x02201
                ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D0_DP_LINK_CLK_RATE);
#else
                // When Define Extended Rx Cap Should Set DPCD 0x02201
                g_ucDpRx0DPCD02201hValue = _D0_DP_LINK_CLK_RATE;
#endif
                DebugMessageRx0("Flag Clear_Hotplug Event_D0", _D0_DP_LINK_CLK_RATE);
            }
        }
        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
        {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D6_DP_LINK_CLK_RATE)) ||
               ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpRx0GetDpcdInfo(0x00, 0x22, 0x01) < _D6_DP_LINK_CLK_RATE)))
#else
            if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D6_DP_LINK_CLK_RATE)) ||
               ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (g_ucDpRx0DPCD02201hValue < _D6_DP_LINK_CLK_RATE)))
#endif
            {
                if(_D6_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
                {
                    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
                }
                else
                {
                    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D6_DP_LINK_CLK_RATE);
                }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                // When Define Extended Rx Cap Should Set DPCD 0x02201
                ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D6_DP_LINK_CLK_RATE);
#else
                // When Define Extended Rx Cap Should Set DPCD 0x02201
                g_ucDpRx0DPCD02201hValue = _D6_DP_LINK_CLK_RATE;
#endif
                DebugMessageRx0("Flag Clear_Hotplug Event_D6", _D6_DP_LINK_CLK_RATE);
            }
        }
    }
#else // else of #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if((enumHpdType != _DP_HDCP_LONG_HPD_EVENT) && (enumHpdType != _DP_HBR2_MARGIN_LINK_HPD_EVENT) && ((ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x00) >= _DP_VERSION_1_2) || (ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)))
    {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D0_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpRx0GetDpcdInfo(0x00, 0x22, 0x01) < _D0_DP_LINK_CLK_RATE)))
#else
        if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D0_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (g_ucDpRx0DPCD02201hValue < _D0_DP_LINK_CLK_RATE)))
#endif
        {
            if(_D0_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D0_DP_LINK_CLK_RATE);
#else
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            g_ucDpRx0DPCD02201hValue = _D0_DP_LINK_CLK_RATE;
#endif
            DebugMessageRx0("Flag Clear_Hotplug Event_D0", _D0_DP_LINK_CLK_RATE);
        }
    }
#endif // end of #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
#endif

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
    if(enumHpdType != _DP_HBR2_MARGIN_LINK_HPD_EVENT)
    {
        ScalerDpRx0CalculateLinkRate(GET_DP_RX_D0_PORT_TARGET_LANE_COUNT());
    }
#endif

    if(enumHpdType != _DP_HPD_ASSERTED)
    {
        ScalerDpRx0AVMute();

        ScalerDpRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);

#if(_DP_MST_SUPPORT == _ON)
        if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
        {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
            {
                ScalerDpRx0MstInfoBackup(_DP_MST_BACKUP_INFO);
            }
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
            {
                ScalerDpRx6MstInfoBackup(_DP_MST_BACKUP_INFO);
            }
#endif
            ScalerDpMstReset(_DP_MST_RX0_PORT);
        }
#endif

#if(_DP_TX_SUPPORT == _ON)
        if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
        {
            ScalerDpTxForceIdlePatternSetting();
        }
#endif

#if(_DP_HPD_LOW_AUX_NOT_REPLY_SUPPORT == _ON)
        // Reset Aux Phy
        ScalerSetBit(PB7_65_AUX_5, ~_BIT7, 0x00);
#endif
    }

    if(enumHpdType == _DP_HPD_LOW)
    {
        DebugMessageRx0("_D0_HOT_PLUG_LOW", 0);

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);

        return _DP_HPD_TIME_NONE;
    }
    else if(enumHpdType == _DP_HPD_LOW_RESET_AUX)
    {
        // Reset Aux Phy
        ScalerSetBit(PB7_65_AUX_5, ~_BIT7, 0x00);

        DebugMessageRx0("_D0_HOT_PLUG_LOW", 0);

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);

        return _DP_HPD_TIME_NONE;
    }

    // Reset DDC0
    MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT1;

#if(_DP_FREESYNC_SUPPORT == _ON)
    SET_DP_RX0_AUX_MANUAL_MODE();
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x07, 0x00);
    SET_DP_RX0_AUX_AUTO_MODE();
#endif

    ScalerDpRx0HDCPUnplugReset();

#if(_D0_DP_ASSR_MODE_SUPPORT == _ON)
    SET_DP_RX0_AUX_MANUAL_MODE();
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
    SET_DP_RX0_AUX_AUTO_MODE();
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
        ScalerSetBit(PB7_65_AUX_5, ~_BIT7, 0x00);

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
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
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
        {
            PCB_DIGITAL_D0_D6_SWITCH_LANE(_DP_D0_D6_SWITCH_D0);
            PCB_DIGITAL_D0_D6_SWITCH_AUX_HPD(_DP_D0_D6_SWITCH_D0);
            ScalerMcuDdcRamEDIDAddrSelect(_D0_DDCRAM, _DDCRAM_TOP_ADDR);
        }
        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
        {
            PCB_DIGITAL_D0_D6_SWITCH_LANE(_DP_D0_D6_SWITCH_D6);
            PCB_DIGITAL_D0_D6_SWITCH_AUX_HPD(_DP_D0_D6_SWITCH_D6);
            ScalerMcuDdcRamEDIDAddrSelect(_D0_DDCRAM, _DDCRAM_BOTTOM_ADDR);
        }

        PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_ON);
        SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_ON);
#endif
        return _DP_HPD_ASSERTED_TIME;
    }

    return _DP_HPD_TIME_NONE;
}

//--------------------------------------------------
// Description  : Dp After Hpd Toggle Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AfterHpdToggleProc(void)
{
    // Release Aux Phy
    ScalerSetBit(PB7_65_AUX_5, ~_BIT7, _BIT7);

    SET_DP_RX0_AUX_MANUAL_MODE();

    if((GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS) && (GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_FAKE_LINK_TRAINING_PASS))
    {
        ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x00, 0x00);
        ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x01, (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0xE0));
    }

    SET_DP_RX0_AUX_AUTO_MODE();

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if((GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_ON) && (GET_DP_AUTO_SEARCH_SWITCH() == _FALSE) &&
       (((GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT) && (ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)) ||
        ((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (ScalerSyncDpCableStatus(_D6_INPUT_PORT) == _TRUE))))
#else
    if(ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _TRUE)
#endif
    {
#if(_DP_MST_SUPPORT == _ON)
        ScalerTimerActiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);
#else
        ScalerTimerActiveTimerEvent(SEC(1.2), _SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);
#endif

#if(_DP_TX_SUPPORT == _ON)
#if(_DP_DPCD_DFP_PRESENT_REF_TO == _DP_MST_CAPABILITY)
        if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == 0x00)
        {
            ScalerDpRx0UpdateSinkCount(1);
        }
        else
#endif
        {
            ScalerDpRx0UpdateSinkCount(GET_DP_TX_DOWNSTREAM_SINK_COUNT() + 1);
        }
#endif
    }
}

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check 8b10b Error Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx0DecodeErrorCountCheck(WORD usTimeCriteria, BYTE ucErrorCriteria)
{
    ScalerDpRx0DecodeErrorCountReset();

    ScalerTimerDelayXms(usTimeCriteria);

    switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_ONE_LANE:

            if(ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE0) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_TWO_LANE:

            if((ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE0) == _TRUE) &&
               (ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE1) == _TRUE))
            {
                return _TRUE;
            }

            break;

        case _DP_FOUR_LANE:
        default:

            if((ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE0) == _TRUE) &&
               (ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE1) == _TRUE) &&
               (ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE2) == _TRUE) &&
               (ScalerDpRx0DecodeErrorCountLaneMeasure(ucErrorCriteria, _D0_DP_LANE3) == _TRUE))
            {
                return _TRUE;
            }

            break;
    }

    DebugMessageRx0("7. DP Error Count Fail", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description : Measure 8b10b Error Count Per Lane
// Input Value  : DP Lane
// Output Value : True --> locked; False --> unlocked
//--------------------------------------------------
bit ScalerDpRx0DecodeErrorCountLaneMeasure(BYTE ucErrorCriteria, BYTE ucDpRx0LaneNumber)
{
    WORD usErrorCountLaneMeasure = 0;

    // Select Lane
    ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (ucDpRx0LaneNumber << 3));

    usErrorCountLaneMeasure = ((((WORD)ScalerGetByte(PB_0B_BIST_PATTERN3)) << 8) | ScalerGetByte(PB_0C_BIST_PATTERN4));

    if(usErrorCountLaneMeasure > ucErrorCriteria)
    {
        DebugMessageRx0("DP Lane", ucDpRx0LaneNumber);
        DebugMessageRx0("DP Lane Burst Error", usErrorCountLaneMeasure);

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : Check Lane BS
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx0LaneBsCheck(void)
{
    // Detect Enable
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT3, 0x00);
    ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT3, _BIT3);

    // Delay for 8192 x 10 x 8 x 2 / 1.62G = 809us
    DELAY_XUS(850);

    // Check Lane Bs
    if(ScalerGetBit(PB_00_HD_DP_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Change Dp Scramble Seed
// Input Value  : None
// Output Value : False --> Change Scrmable Seed Finish
//--------------------------------------------------
bit ScalerDpRx0ChangeSrambleSeed(void)
{
#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)

    if(ScalerGetBit(PB_07_SCRAMBLE_CTRL, _BIT4) == 0x00)
    {
        // Try Scramble Seed = 0xFFFE
        ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);

        return _TRUE;
    }
    else
#endif
    {
        return _FALSE;
    }
}

#if(_DP_RX0_ASSR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : VBIOS ASSR Detect
// Input Value  : bMSACheckResult
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpRx0VbiosAssrCheck(bit bMSACheckResult)
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
        if(bMSACheckResult == _TRUE)
        {
            if(ScalerGetBit(PB_07_SCRAMBLE_CTRL, _BIT4) == _BIT4)
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, _BIT0);
            }
            else
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, 0x00);
            }
        }
        else
        {
            // Set Scramble Seed = Default 0xFFFF
            ScalerSetBit(PB_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);

            ScalerDpRx0SetDpcdBitValue(0x00, 0x01, 0x0A, ~_BIT0, 0x00);
        }
    }
    else
    {
        bMSACheckResult = _FALSE;
    }

    SET_DP_RX0_AUX_AUTO_MODE();

    return bMSACheckResult;
}
#endif

//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpRx0PSPreDetect(void)
{
    // Back to noraml for DP PHY CTS
    if(GET_DP_RX0_PHY_CTS_FLG() == _TRUE)
    {
        return _TRUE;
    }

    if(GET_DP_RX0_VALID_VIDEO_CHECK() == _TRUE)
    {
        DebugMessageRx0("7. Valid Video Check", 0);

        return _TRUE;
    }

    if(GET_DP_RX0_PS_AUX_TOGGLE() == _TRUE)
    {
        DebugMessageRx0("7. Power Saving Aux Handshake", 0);

        return _TRUE;
    }

    if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        DebugMessageRx0("7. Normal Link Training under Fake Power Saving Case", 0);

        return _TRUE;
    }

#if(_DP_MST_SUPPORT == _ON)

    if(ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE1) != 0x00)
    {
        return _TRUE;
    }

    if(GET_DP_RX0_AUX_CH_POWER_ON_WAKE_UP() == _TRUE)
    {
        CLR_DP_RX0_AUX_CH_POWER_ON_WAKE_UP();

        return _TRUE;
    }
#endif

    if(((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) &&
        ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
         (ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))) ||
       (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
    {
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))

        if(ScalerAudioGetDigitalAudioSource(_D0_INPUT_PORT) == _DIGITAL_AUDIO_SOURCE_DP)
        {
            DebugMessageAudio("00. DP Power Saving Audio : Idle Pattern Case", ScalerAudioGetDigitalAudioSource(_D0_INPUT_PORT));
            return _TRUE;
        }
#endif
        DebugMessageRx0("7. Idle Pattern Case", 0);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set DP Lane Mapping Type
// Input Value  : ucLanetype --> Lane Mapping Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDpLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation)
{
    if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
    {
        if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Lane 0 <--> Lane 2
            // Lane 1 <--> Lane 3
            SET_DP_RX0_PCB_LANE0_MAPPING(_D0_DP_PCB_LANE2_MAPPING);
            SET_DP_RX0_PCB_LANE1_MAPPING(_D0_DP_PCB_LANE3_MAPPING);
            SET_DP_RX0_PCB_LANE2_MAPPING(_D0_DP_PCB_LANE0_MAPPING);
            SET_DP_RX0_PCB_LANE3_MAPPING(_D0_DP_PCB_LANE1_MAPPING);
            SET_DP_RX0_PCB_LANE0_PN_SWAP(!_D0_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX0_PCB_LANE1_PN_SWAP(!_D0_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX0_PCB_LANE2_PN_SWAP(!_D0_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX0_PCB_LANE3_PN_SWAP(!_D0_DP_PCB_LANE3_PN_SWAP);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
            {
#if(_D0_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
                // Enable Aux PN Pull High Low Swap PCB Function
                PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_ON);

                // Enable Aux Digital Phy PN Swap
                ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
#else
                // Disable Aux PN Pull High Low Swap PCB Function
                PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);

                // Disable Aux Digital Phy PN Swap
                ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
#endif
            }

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
            {
#if(_D6_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
                // Enable Aux PN Pull High Low Swap PCB Function
                PCB_D6_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_ON);

                // Enable Aux Digital Phy PN Swap
                ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
#else
                // Disable Aux PN Pull High Low Swap PCB Function
                PCB_D6_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);

                // Disable Aux Digital Phy PN Swap
                ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
#endif
            }
#endif
        }
        else // Normal Cable Mode
        {
            SET_DP_RX0_PCB_LANE0_MAPPING(_D0_DP_PCB_LANE0_MAPPING);
            SET_DP_RX0_PCB_LANE1_MAPPING(_D0_DP_PCB_LANE1_MAPPING);
            SET_DP_RX0_PCB_LANE2_MAPPING(_D0_DP_PCB_LANE2_MAPPING);
            SET_DP_RX0_PCB_LANE3_MAPPING(_D0_DP_PCB_LANE3_MAPPING);
            SET_DP_RX0_PCB_LANE0_PN_SWAP(_D0_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX0_PCB_LANE1_PN_SWAP(_D0_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX0_PCB_LANE2_PN_SWAP(_D0_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX0_PCB_LANE3_PN_SWAP(_D0_DP_PCB_LANE3_PN_SWAP);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
            {
                // Disable Aux PN Pull High Low Swap PCB Function
                PCB_D6_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);
            }
            else
#endif
            {
                // Disable Aux PN Pull High Low Swap PCB Function
                PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);
            }

            // Disable Aux Digital Phy PN Swap
            ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
        }
    }
    else
    {
        if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Lane 0 <--> Lane 2
            // Lane 1 <--> Lane 3
            SET_DP_RX0_PCB_LANE0_MAPPING(_D0_DP_PCB_LANE1_MAPPING);
            SET_DP_RX0_PCB_LANE1_MAPPING(_D0_DP_PCB_LANE0_MAPPING);
            SET_DP_RX0_PCB_LANE2_MAPPING(_D0_DP_PCB_LANE3_MAPPING);
            SET_DP_RX0_PCB_LANE3_MAPPING(_D0_DP_PCB_LANE2_MAPPING);
            SET_DP_RX0_PCB_LANE0_PN_SWAP(!_D0_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX0_PCB_LANE1_PN_SWAP(!_D0_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX0_PCB_LANE2_PN_SWAP(!_D0_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX0_PCB_LANE3_PN_SWAP(!_D0_DP_PCB_LANE3_PN_SWAP);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
            {
                // Disable Aux PN Pull High Low Swap PCB Function
                PCB_D6_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);
            }
            else
#endif
            {
                // Disable Aux PN Pull High Low Swap PCB Function
                PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);
            }

            // Disable Aux Digital Phy PN Swap
            ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
        }
        else // Normal Cable Mode
        {
            SET_DP_RX0_PCB_LANE0_MAPPING(_D0_DP_PCB_LANE3_MAPPING);
            SET_DP_RX0_PCB_LANE1_MAPPING(_D0_DP_PCB_LANE2_MAPPING);
            SET_DP_RX0_PCB_LANE2_MAPPING(_D0_DP_PCB_LANE1_MAPPING);
            SET_DP_RX0_PCB_LANE3_MAPPING(_D0_DP_PCB_LANE0_MAPPING);
            SET_DP_RX0_PCB_LANE0_PN_SWAP(_D0_DP_PCB_LANE0_PN_SWAP);
            SET_DP_RX0_PCB_LANE1_PN_SWAP(_D0_DP_PCB_LANE1_PN_SWAP);
            SET_DP_RX0_PCB_LANE2_PN_SWAP(_D0_DP_PCB_LANE2_PN_SWAP);
            SET_DP_RX0_PCB_LANE3_PN_SWAP(_D0_DP_PCB_LANE3_PN_SWAP);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
            {
                // Enable Aux PN Pull High Low Swap PCB Function
                PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_ON);

                // Enable Aux Digital Phy PN Swap
                ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
            }

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
            {
                // Enable Aux PN Pull High Low Swap PCB Function
                PCB_D6_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_ON);

                // Enable Aux Digital Phy PN Swap
                ScalerSetBit(PB7_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
            }
#endif
        }
    }
}

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
//--------------------------------------------------
// Description  : Initial Setting for DP
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx6Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumFreeSyncSupport enumFreeSyncSupport)
{
    ScalerDpRx0AuxPowerOnInitial();

    ScalerDpRx0DpcdInitial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumFreeSyncSupport);

    // Must be initialized "AFTER DPCD setting" to avoid entering interruption unexpectively
    ScalerDpRx0AuxIntInitial();

    SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    SET_DP_RX0_FAKE_LINK_TRAINING();

    SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
    SET_DP_RX_D6_PORT_TARGET_VERSION(enumDpVersion);
    SET_DP_RX_D6_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

    ScalerDpRx0SetDpLaneMapping(_TYPE_C_PIN_ASSIGNMENT_C, _TYPE_C_ORIENTATION_UNFLIP);

#if(_DP_MST_SUPPORT == _ON)
    CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
    CLR_DP_RX0_CHECK_AUX_CH_POWER_STATUS();
#endif

#if(_DP_TX_SUPPORT == _ON)
    CLR_DP_RX0_HDCP_AUTH_AKSV_WRITTEN();
#endif
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Backup MST Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0MstInfoBackup(EnumDpMstBackup enumDpMstBackup)
{
    EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

    switch(enumDpMstBackup)
    {
        case _DP_MST_BACKUP_INFO:

            if((ScalerGetBit(PB_01_PHY_DIG_RESET_CTRL, _BIT7) == _BIT7) &&
               (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS))
            {
                // Backup MST Enable
                g_stDpRx0MiscInfo.b1DpMstEnableBackup = _TRUE;
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                g_stDpRx0MiscInfo.b1DpRx6MstEnableBackup = _FALSE;
#endif
                // Backup Link Config
                g_stDpRx0MiscInfo.ucDpRxLinkRateBackup = ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00);
                g_stDpRx0MiscInfo.ucDpRxLaneCountBackup = (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F);

                // Backup TimeSlot Info
                memcpy(g_pucDpRx0MstTimeSlotBackup, (volatile BYTE xdata *)PB5_03_STHD_CTRL_2, sizeof(g_pucDpRx0MstTimeSlotBackup));

                for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE5; enumSourceNum++)
                {
                    g_pucDpMacRx0MstStMuxBackup[enumSourceNum] = GET_DP_RX_MST_ST_SOURCE_BACKUP(enumSourceNum);
                }
            }

            break;

        case _DP_MST_BACKUP_INFO_RESTORE:

            if(((ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x21) & _BIT0) == _BIT0) && (g_stDpRx0MiscInfo.b1DpMstEnableBackup == _TRUE))
            {
                // Enable MST Decode
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT7, _BIT7);

                // Restore TimeSlot Info
                memcpy((volatile BYTE xdata *)PB5_03_STHD_CTRL_2, g_pucDpRx0MstTimeSlotBackup, sizeof(g_pucDpRx0MstTimeSlotBackup));

                for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE5; enumSourceNum++)
                {
                    ScalerDpRxMstStreamMuxBackup(enumSourceNum, g_pucDpMacRx0MstStMuxBackup[enumSourceNum]);
                }
            }
            g_stDpRx0MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;

        case _DP_MST_BACKUP_INFO_RESET:
        default:

            g_stDpRx0MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;
    }
}

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
//--------------------------------------------------
// Description  : Dp Rx Aux Ch Source Power Check
// Input Value  : None
// Output Value : _ON / _OFF
//--------------------------------------------------
bit ScalerDpRx6AuxChSourcePowerCheck(void)
{
    if(PCB_GET_D6_AUX_PN_1M_PULL_H_L_SWAP() == _AUX_PN_1M_PULL_HI_LOW_SWAP_ON)
    {
        return GET_PCB_D6_DP_SOURCE_POWER_PN_SWAP();
    }
    else
    {
        return GET_PCB_D6_DP_SOURCE_POWER();
    }
}

//--------------------------------------------------
// Description  : Dp Rx Aux Ch Power Status Check
// Input Value  : bCableStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpRx6AuxChPowerStatusCheck(bit bCableStatus)
{
    BYTE ucDebounceCnt = 0;

    if((GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_ON) && (GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (g_enumDpMSTCapablePort == _DP_MST_RX0_PORT))
    {
        if(bCableStatus == _TRUE)
        {
            if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
            {
                // First time check power on with debounce to avoid AUX N always low case
                if((GET_DP_RX0_CHECK_AUX_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_NONE) && (ScalerDpRx6AuxChSourcePowerCheck() == _ON))
                {
                    // Debounce for 10ms
                    for(ucDebounceCnt = 0; ucDebounceCnt < 5; ucDebounceCnt++)
                    {
                        ScalerTimerDelayXms(2);

                        if(ScalerDpRx6AuxChSourcePowerCheck() == _OFF)
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
                if((ScalerDpRx6AuxChSourcePowerCheck() == _OFF) &&
                   (GET_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE() == _FALSE) &&
                   (GET_DP_RX0_CHECK_AUX_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_ON))
                {
                    SET_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();

                    ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                }

                // Debouncing
                if(GET_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE() == _TRUE)
                {
                    if(ScalerDpRx6AuxChSourcePowerCheck() == _ON)
                    {
                        CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                    }
                }

                // 1.5s HotPlug has been removed because NVIDIA GTX-1080 failed while HPD togglled at the moment of PC waked up from sleep.
                if((GET_DP_RX0_CHECK_AUX_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_OFF) && (ScalerDpRx6AuxChSourcePowerCheck() == _ON))
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
//--------------------------------------------------
// Description  : Backup MST Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx6MstInfoBackup(EnumDpMstBackup enumDpMstBackup)
{
    EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

    switch(enumDpMstBackup)
    {
        case _DP_MST_BACKUP_INFO:

            if((ScalerGetBit(PB_01_PHY_DIG_RESET_CTRL, _BIT7) == _BIT7) &&
               (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS))
            {
                // Backup MST Enable
                g_stDpRx0MiscInfo.b1DpRx6MstEnableBackup = _TRUE;
                g_stDpRx0MiscInfo.b1DpMstEnableBackup = _FALSE;

                // Backup Link Config
                g_stDpRx0MiscInfo.ucDpRxLinkRateBackup = ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00);
                g_stDpRx0MiscInfo.ucDpRxLaneCountBackup = (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F);

                // Backup TimeSlot Info
                memcpy(g_pucDpRx0MstTimeSlotBackup, (volatile BYTE xdata *)PB5_03_STHD_CTRL_2, sizeof(g_pucDpRx0MstTimeSlotBackup));

                for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE5; enumSourceNum++)
                {
                    g_pucDpMacRx0MstStMuxBackup[enumSourceNum] = GET_DP_RX_MST_ST_SOURCE_BACKUP(enumSourceNum);
                }
            }

            break;

        case _DP_MST_BACKUP_INFO_RESTORE:

            if(((ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x21) & _BIT0) == _BIT0) && (g_stDpRx0MiscInfo.b1DpRx6MstEnableBackup == _TRUE))
            {
                // Enable MST Decode
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT7, _BIT7);

                // Restore TimeSlot Info
                memcpy((volatile BYTE xdata *)PB5_03_STHD_CTRL_2, g_pucDpRx0MstTimeSlotBackup, sizeof(g_pucDpRx0MstTimeSlotBackup));

                for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE5; enumSourceNum++)
                {
                    ScalerDpRxMstStreamMuxBackup(enumSourceNum, g_pucDpMacRx0MstStMuxBackup[enumSourceNum]);
                }
            }
            g_stDpRx0MiscInfo.b1DpRx6MstEnableBackup = _FALSE;

            break;

        case _DP_MST_BACKUP_INFO_RESET:
        default:

            g_stDpRx0MiscInfo.b1DpRx6MstEnableBackup = _FALSE;

            break;
    }
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx HDCP - SHA circuit Run
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPAuthShaRun(bit bIsFirst)
{
    // Set First Run For SHA-1 Circuit
    ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT1, ((bIsFirst == _TRUE) ? _BIT1 : 0x00));

    // Run SHA-1 Circuit
    ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT2, _BIT2);

    ScalerTimerPollingFlagProc(5, PB_30_SHA_CONTRL, _BIT4, _TRUE);

    // Disable First Run and Disable SHA-1 Circuit
    ScalerSetBit(PB_30_SHA_CONTRL, ~(_BIT2 | _BIT1), 0x00);
}

//--------------------------------------------------
// Description  : Change HDCP Auth State
// Input Value  : Target HDCP Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPChangeAuthState(EnumDPRxHDCPAuthState enumHDCPAuthState)
{
    SET_DP_RX0_HDCP_AUTH_STATE(enumHDCPAuthState);
    SET_DP_RX0_HDCP_AUTH_STATE_CHANGE();
}
//--------------------------------------------------
// Description  : Check B info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx0HDCPCheckBinfo(void)
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

    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x2A, ucBInfoDevice);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x2B, ucBInfoDepth);

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
bit ScalerDpRx0HDCPCheckLvp(void)
{
    if(((ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
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
void ScalerDpRx0HDCPFakeAuthenProc(void)
{
    BYTE pucSHAInput[64];

    // Set Device Count and Depth
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x2A, 0x01);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x2B, 0x01);

    // Load KSV
    memcpy(pucSHAInput, g_pucHdcpAksvBackup, 5);

    // Load Device Count and Depth
    pucSHAInput[5] = ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2A);
    pucSHAInput[6] = ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2B);

    // Load M0'
    for(pData[0] = 0; pData[0] < 8; pData[0]++)
    {
        pucSHAInput[7 + pData[0]] = ScalerGetByte(PB_2F_M0_BYTE_0 - pData[0]);
    }

    memset(&pucSHAInput[15], 0, 49);

    pucSHAInput[15] = 0x80;

    // Total bit numbers of SHA-1 input = KSV FIFO + B_info + M0'
    pucSHAInput[63] = 0x78;

    // Compute V'
    ScalerDpRx0HDCPSha1Calculate(pucSHAInput, 0);

    // Write Ksv to DPCD table
    SET_DP_RX0_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 15; pData[0]++)
    {
        if(pData[0] < 5)
        {
            ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), g_pucHdcpAksvBackup[pData[0]]);
        }
        else
        {
            ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), 0x00);
        }
    }

    SET_DP_RX0_AUX_AUTO_MODE();

    // Write V' to DPCD table
    ScalerDpRx0HDCPLoadShaToDpcd();
}
//--------------------------------------------------
// Description  : Dp Rx HDCP Auth Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPHandler(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if((GET_DP_RX0_HDCP2_MODE() == _DISABLE) && (GET_DP_RX0_HDCP_REPEATER_SUPPORT() == _TRUE))
#else
    if(GET_DP_RX0_HDCP_REPEATER_SUPPORT() == _TRUE)
#endif
    {
        // After receiving AKSV, handler must initialize authentication
        if(GET_DP_RX0_HDCP_AUTH_AKSV_WRITTEN() == _TRUE)
        {
            CLR_DP_RX0_HDCP_AUTH_AKSV_WRITTEN();
            CLR_DP_RX0_HDCP_AUTH_CPIRQ_TIMRE();

            ScalerDpRx0HDCPChangeAuthState(_DP_RX_HDCP_STATE_IDLE);

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_CPIRQ_EVENT);
        }

        if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
        {
            // In MST mode
            if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x11) & _BIT0) == _BIT0)
            {
                if((ScalerDpRx0HdcpCheckValid() == _TRUE) && (GET_DP_RX0_HDCP_AUTH_CPIRQ_TIMRE() == _FALSE))
                {
                    if(ScalerDpRx0HDCPCheckLvp() == _FALSE)
                    {
                        SET_DP_RX0_HDCP_AUTH_CPIRQ_TIMRE();

                        ScalerDpRx0CpIRQ(_DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

                        ScalerTimerActiveTimerEvent(SEC(0.02), _SCALER_TIMER_EVENT_DP_RX0_HDCP_CPIRQ_EVENT);
                    }
                }
            }
            else
            {
                // In SST mode, issue HPD event for upstream device if DPTX connect a new downstream device.
                if((GET_DP_RX0_HDCP_AUTH_STATE() != _DP_RX_HDCP_STATE_IDLE) &&
                   (ScalerDpRx0HdcpCheckValid() == _TRUE) &&
                   (ScalerDpRx0HDCPCheckLvp() == _TRUE))
                {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                    {
                        if(GET_DP_TX_HDCP2_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_REAUTH)
                        {
                            ScalerDpRx0SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
                        }
                    }
                    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#else
                    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#endif
                    {
                        if(GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH)
                        {
                            ScalerDpRx0SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
                        }
                    }
                }
            }
        }

        if((GET_DP_RX0_HDCP_AUTH_STATE() != _DP_RX_HDCP_STATE_IDLE) && (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE))
        {
            ScalerDpRx0HDCPChangeAuthState(_DP_RX_HDCP_STATE_IDLE);
        }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
        {
            if((ScalerDpRx0HdcpCheckValid() == _TRUE) &&
               (GET_DP_RX0_HDCP_AUTH_STATE() >= _DP_RX_HDCP_STATE_AUTH_2) &&
               (GET_DP_TX_HDCP2_MODE() == _TRUE))
            {
                SET_DP_RX0_HDCP2_HDCP1_CONTENT_STREAM_MANAGEMENT();
            }
        }
#endif
    }

    switch(GET_DP_RX0_HDCP_AUTH_STATE())
    {
        case _DP_RX_HDCP_STATE_IDLE:

            if(GET_DP_RX0_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX0_HDCP_AUTH_STATE_CHANGE();
                CLR_DP_RX0_HDCP_AUTH_REPEATER_PROC_TIMEOUT();
                CLR_DP_RX0_HDCP_AUTH_CPIRQ_TIMRE();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                CLR_DP_RX0_HDCP2_HDCP1_CONTENT_STREAM_MANAGEMENT();
#endif

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_REPEATER_PROC_TIMEOUT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_READ_IRQ_TIMEOUT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_CPIRQ_EVENT);

                ScalerDpRx0HDCPEnableReadIrq(_DISABLE);

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
                ScalerDpTxHDCPResetKsvBackup();
#endif

                SET_DP_RX0_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION);
            }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if((GET_DP_RX0_HDCP2_MODE() == _DISABLE) && (GET_DP_RX0_HDCP_REPEATER_SUPPORT() == _TRUE))
#else
            if(GET_DP_RX0_HDCP_REPEATER_SUPPORT() == _TRUE)
#endif
            {
                // Check if R0' was read already by upstream device.
                if((ScalerGetBit(PB_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5)) &&
                   ((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x05) != 0x00) || (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x06) != 0x00)) &&
                   ((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x29) & _DP_HDCP_BSTATUS_R0_AVAILABLE) == 0x00) &&
                   ((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) ||
                    (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
                    (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) ||
                    (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
                    (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00)))
                {
                    ScalerDpRx0HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_1);
                }
            }

            break;

        case _DP_RX_HDCP_STATE_AUTH_1:

            if(GET_DP_RX0_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX0_HDCP_AUTH_STATE_CHANGE();

                if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
                {
                    // Check if downstream device support HDCP capability.
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                    {
                        // Issue event to make DPTX start HDCP2 handshake.
                        SET_DP_RX0_HDCP2_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX0_HDCP_REPEATER_PROC_TIMEOUT);
                    }
                    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#else
                    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#endif
                    {
                        // Issue event to make DPTX start HDCP handshake.
                        SET_DP_RX0_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX0_HDCP_REPEATER_PROC_TIMEOUT);
                    }
                    else
                    {
                        ScalerDpRx0HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_2);
                    }
                }
                else
                {
                    ScalerDpRx0HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_FAKE);
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
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_REPEATER_PROC_TIMEOUT);

                ScalerDpRx0HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_2);
            }
            else if(GET_DP_RX0_HDCP_AUTH_REPEATER_PROC_TIMEOUT() == _TRUE)
            {
                CLR_DP_RX0_HDCP_AUTH_REPEATER_PROC_TIMEOUT();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                {
                    SET_DP_RX0_HDCP2_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_TIMEOUT);
                }
                else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#else
                if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#endif
                {
                    SET_DP_RX0_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT);
                }

                ScalerDpRx0HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP_STATE_AUTH_2:

            if(GET_DP_RX0_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX0_HDCP_AUTH_STATE_CHANGE();
            }

            if(ScalerDpRx0HDCPCheckBinfo() == _TRUE)
            {
                // Load KSV List to RX KSV FIFO
                ScalerDpRx0HDCPLoadKsvFifo();

                // Input KSV FIFO to SHA-1 and Compute V'
                ScalerDpRx0HDCPWriteShaInput();

                // Write V' into DPCD table
                ScalerDpRx0HDCPLoadShaToDpcd();

                // Set 1st KSV FIFO to DPCD table
                ScalerDpRx0HDCPSetKsvFifoFirst();

                // Enable 68xxx Read INT
                ScalerDpRx0HDCPEnableReadIrq(_ENABLE);

                ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_DP_RX0_HDCP_READ_IRQ_TIMEOUT);
            }

            // Set V' Ready Bit and Issue CP_IRQ
            ScalerDpRx0CpIRQ(_DP_HDCP_BSTATUS_V_READY);

            ScalerDpRx0HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);

            break;

        case _DP_RX_HDCP_STATE_AUTH_FAKE:

            if(GET_DP_RX0_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX0_HDCP_AUTH_STATE_CHANGE();
            }

            // Enable 68xxx Read INT
            ScalerDpRx0HDCPEnableReadIrq(_DISABLE);

            // Fake Authentication
            ScalerDpRx0HDCPFakeAuthenProc();

            // Set V' Ready Bit and Issue CP_IRQ
            ScalerDpRx0CpIRQ(_DP_HDCP_BSTATUS_V_READY);

            ScalerDpRx0HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);

            break;

        case _DP_RX_HDCP_STATE_AUTH_DONE:

            if(GET_DP_RX0_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX0_HDCP_AUTH_STATE_CHANGE();
            }

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
            if(GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS)
            {
                // In SST mode
                if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x11) & _BIT0) == 0x00)
                {
                    if((ScalerDpRx0HDCPDeviceCountChange() == _TRUE) &&
                       (ScalerDpRx0HdcpCheckValid() == _TRUE) &&
                       (ScalerDpRx0HDCPCheckLvp() == _TRUE))
                    {
                        ScalerDpRx0SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
                    }
                }
            }
#endif

            if(GET_DP_RX0_HDCP_AUTH_READ_IRQ_TIMEOUT() == _TRUE)
            {
                ScalerDpRx0HDCPEnableReadIrq(_DISABLE);
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
void ScalerDpRx0HDCPLoadKsvFifo(void)
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
void ScalerDpRx0HDCPLoadShaToDpcd(void)
{
    SET_DP_RX0_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        for(pData[1] = 0; pData[1] < 4; pData[1]++)
        {
            ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x14 + (pData[0] * 4) + pData[1]), ScalerGetByte(PB_39_SHA_3 + (pData[0] * 4) - pData[1]));
        }
    }

    SET_DP_RX0_AUX_AUTO_MODE();
}
//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPSetKsvFifoFirst(void)
{
    SET_DP_RX0_AUX_MANUAL_MODE();

    for(g_usDpRx0HdcpKsvFifoOffset = 0; g_usDpRx0HdcpKsvFifoOffset < 15; g_usDpRx0HdcpKsvFifoOffset++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x2C + g_usDpRx0HdcpKsvFifoOffset), g_pucDpTxHdcpKsvFifo[g_usDpRx0HdcpKsvFifoOffset]);
    }

    // Aux HW Control
    SET_DP_RX0_AUX_AUTO_MODE();
}
//--------------------------------------------------
// Description  : Set HDCP Read IRQ Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPSetReadIrqTimeout(void)
{
    SET_DP_RX0_HDCP_AUTH_READ_IRQ_TIMEOUT();
}
//--------------------------------------------------
// Description  : Set HDCP Repeater Proc Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPSetRepeaterProcTimeout(void)
{
    SET_DP_RX0_HDCP_AUTH_REPEATER_PROC_TIMEOUT();
}
//--------------------------------------------------
// Description  : Calculate SHA-1 Input
// Input Value  : Inpute Array, First Run
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPSha1Calculate(BYTE *pucInputArray, BYTE ucCalCount)
{
    // Reset SHA Block counter
    ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT3, _BIT3);

    // Start to Write SHA-1 Transform Input
    ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT3, 0x00);

    // Write SHA-1 Input Data, Total 512 bits
    for(pData[1] = 0; pData[1] < 16; pData[1]++)
    {
        ScalerSetByte(PB_31_SHA_DATA1, pucInputArray[pData[1] * 4]);
        ScalerSetByte(PB_32_SHA_DATA2, pucInputArray[1 + pData[1] * 4]);
        ScalerSetByte(PB_33_SHA_DATA3, pucInputArray[2 + pData[1] * 4]);
        ScalerSetByte(PB_34_SHA_DATA4, pucInputArray[3 + pData[1] * 4]);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);
    }

    ScalerDpRx0HDCPAuthShaRun(((ucCalCount == 0x00) ? _TRUE : _FALSE));
}
//--------------------------------------------------
// Description  : Load KSV FIFO to SHA-1 Input
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPWriteShaInput(void)
{
    WORD usKsvFifoLength = 0;
    WORD usShaInputBitNumbers = 0;
    WORD usKsvLengthTemp = 0;

    usKsvFifoLength = (WORD) ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2A) * 5;

    // Total bit numbers of SHA-1 input = KSV FIFO + B_info + M0'
    usShaInputBitNumbers = (usKsvFifoLength + 2 + 8) * 8;

    // Reset SHA Block counter
    ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT3, _BIT3);

    // Start to Write SHA-1 Transform Input
    ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT3, 0x00);

    // Write the KSV List into SHA-1 Transform Input
    do
    {
        ScalerSetByte(PB_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
        ScalerSetByte(PB_32_SHA_DATA2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
        ScalerSetByte(PB_33_SHA_DATA3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 2]);
        ScalerSetByte(PB_34_SHA_DATA4, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 3]);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }
    while((usKsvFifoLength - usKsvLengthTemp) >= 4);

    // Write the remaining KSV, B info and M0' into SHA-1 Transform Input
    switch(usKsvFifoLength - usKsvLengthTemp)
    {
        case 1:

            ScalerSetByte(PB_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB_32_SHA_DATA2, ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2A));
            ScalerSetByte(PB_33_SHA_DATA3, ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2B));
            ScalerSetByte(PB_34_SHA_DATA4, GET_DP_RX0_HDCP_M0_0());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB_31_SHA_DATA1, GET_DP_RX0_HDCP_M0_1());
            ScalerSetByte(PB_32_SHA_DATA2, GET_DP_RX0_HDCP_M0_2());
            ScalerSetByte(PB_33_SHA_DATA3, GET_DP_RX0_HDCP_M0_3());
            ScalerSetByte(PB_34_SHA_DATA4, GET_DP_RX0_HDCP_M0_4());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB_31_SHA_DATA1, GET_DP_RX0_HDCP_M0_5());
            ScalerSetByte(PB_32_SHA_DATA2, GET_DP_RX0_HDCP_M0_6());
            ScalerSetByte(PB_33_SHA_DATA3, GET_DP_RX0_HDCP_M0_7());
            ScalerSetByte(PB_34_SHA_DATA4, 0x80);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 2:

            ScalerSetByte(PB_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB_32_SHA_DATA2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PB_33_SHA_DATA3, ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2A));
            ScalerSetByte(PB_34_SHA_DATA4, ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2B));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB_31_SHA_DATA1, GET_DP_RX0_HDCP_M0_0());
            ScalerSetByte(PB_32_SHA_DATA2, GET_DP_RX0_HDCP_M0_1());
            ScalerSetByte(PB_33_SHA_DATA3, GET_DP_RX0_HDCP_M0_2());
            ScalerSetByte(PB_34_SHA_DATA4, GET_DP_RX0_HDCP_M0_3());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB_31_SHA_DATA1, GET_DP_RX0_HDCP_M0_4());
            ScalerSetByte(PB_32_SHA_DATA2, GET_DP_RX0_HDCP_M0_5());
            ScalerSetByte(PB_33_SHA_DATA3, GET_DP_RX0_HDCP_M0_6());
            ScalerSetByte(PB_34_SHA_DATA4, GET_DP_RX0_HDCP_M0_7());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB_31_SHA_DATA1, 0x80);
            ScalerSetByte(PB_32_SHA_DATA2, 0x00);
            ScalerSetByte(PB_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 3:

            ScalerSetByte(PB_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB_32_SHA_DATA2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PB_33_SHA_DATA3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 2]);
            ScalerSetByte(PB_34_SHA_DATA4, ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2A));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB_31_SHA_DATA1, ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2B));
            ScalerSetByte(PB_32_SHA_DATA2, GET_DP_RX0_HDCP_M0_0());
            ScalerSetByte(PB_33_SHA_DATA3, GET_DP_RX0_HDCP_M0_1());
            ScalerSetByte(PB_34_SHA_DATA4, GET_DP_RX0_HDCP_M0_2());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB_31_SHA_DATA1, GET_DP_RX0_HDCP_M0_3());
            ScalerSetByte(PB_32_SHA_DATA2, GET_DP_RX0_HDCP_M0_4());
            ScalerSetByte(PB_33_SHA_DATA3, GET_DP_RX0_HDCP_M0_5());
            ScalerSetByte(PB_34_SHA_DATA4, GET_DP_RX0_HDCP_M0_6());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB_31_SHA_DATA1, GET_DP_RX0_HDCP_M0_7());
            ScalerSetByte(PB_32_SHA_DATA2, 0x80);
            ScalerSetByte(PB_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        default:

            ScalerSetByte(PB_31_SHA_DATA1, ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2A));
            ScalerSetByte(PB_32_SHA_DATA2, ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2B));
            ScalerSetByte(PB_33_SHA_DATA3, GET_DP_RX0_HDCP_M0_0());
            ScalerSetByte(PB_34_SHA_DATA4, GET_DP_RX0_HDCP_M0_1());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB_31_SHA_DATA1, GET_DP_RX0_HDCP_M0_2());
            ScalerSetByte(PB_32_SHA_DATA2, GET_DP_RX0_HDCP_M0_3());
            ScalerSetByte(PB_33_SHA_DATA3, GET_DP_RX0_HDCP_M0_4());
            ScalerSetByte(PB_34_SHA_DATA4, GET_DP_RX0_HDCP_M0_5());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB_31_SHA_DATA1, GET_DP_RX0_HDCP_M0_6());
            ScalerSetByte(PB_32_SHA_DATA2, GET_DP_RX0_HDCP_M0_7());
            ScalerSetByte(PB_33_SHA_DATA3, 0x80);
            ScalerSetByte(PB_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;
    }

    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 60)
    {
        ScalerSetByte(PB_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB_33_SHA_DATA3, 0x00);
        ScalerSetByte(PB_34_SHA_DATA4, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }

    // Write 0x00 into the remaining SHA-1 Transform Input space
    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) <= 56)
    {
        while((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) < 56)
        {
            ScalerSetByte(PB_31_SHA_DATA1, 0x00);
            ScalerSetByte(PB_32_SHA_DATA2, 0x00);
            ScalerSetByte(PB_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;
        }

        // The length of SHA-1 input is equal to 2^64(8 bytes)
        ScalerSetByte(PB_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB_33_SHA_DATA3, 0x00);
        ScalerSetByte(PB_34_SHA_DATA4, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

        // Write the valid bit numbers into SHA-1 Transform Input
        ScalerSetByte(PB_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB_33_SHA_DATA3, HIBYTE(usShaInputBitNumbers));
        ScalerSetByte(PB_34_SHA_DATA4, LOBYTE(usShaInputBitNumbers));

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB_30_SHA_CONTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 8;

        ScalerDpRx0HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
    }
}

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Downstream Device Count/Depth is changed or not
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpRx0HDCPDeviceCountChange(void)
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

    if((ucBInfoDevice != ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2A)) ||
       (ucBInfoDepth != ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2B)))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DP Adjust Vsync Delay
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0MstToSstAdjustVsyncDelay(void)
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
        ulBStoVSDelayDeltaOverflow = (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 270UL) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(0)) / 256;

        DebugMessageRx0("DP MST2SST : Fifo Overflow --> nVidia Case", ulBStoVSDelayDeltaOverflow);
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
        ulBStoVSDelayDeltaUnderflow = (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 270) * 2) / ((DWORD)GET_INPUT_PIXEL_CLK());

        DebugMessageRx0("DP MST2SST : Fifo Underflow --> QD882 Case", ulBStoVSDelayDeltaUnderflow);
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
// Description  : DP MST2SST BS to VS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
DWORD ScalerDpRx0MstToSstGetBStoVSDelay(void)
{
    DWORD ulVFrontPorch = 0;
    DWORD ulHFrontPorch = 0;
    WORD usFifoOffset = 0;

    // Get Htotal
    ScalerRead(PA_10_MSA_HTT_0, 2, &pData[2], _AUTOINC);

    // VFrontPorch = 3 * Htotal * (Link Clk / Stream CLK)
    ulVFrontPorch = ((DWORD)GET_DP_RX0_MST_TO_SST_VFRONT_PORCH()) * ((DWORD)PDATA_WORD(1) * 256) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK()) *
                    (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / 256;

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
    ulHFrontPorch = (((DWORD)(PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(4))) * (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK()));

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
    usFifoOffset = (WORD)(((DWORD)usFifoOffset) * (((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK()));

    return ((ulVFrontPorch + ulHFrontPorch + (DWORD)usFifoOffset) / 2);
}
//--------------------------------------------------
// Description  : Check Dp Video Straam VBID
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpRx0MstToSstGetVideoStream(void)
{
    // Check if ST2_Source is Assigned the STx Stream In MST Mode
    if((ScalerGetBit(PB_01_PHY_DIG_RESET_CTRL, _BIT7) == _BIT7) &&
       (ScalerGetBit(PB5_0D_SOURCE_SEL_0, (_BIT2 | _BIT1 | _BIT0)) == 0x00))
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
bit ScalerDpRx0MstToSstMSAActiveChange(void)
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
bit ScalerDpRx0MstToSstMSACheck(void)
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
// Description  : Handle DP MST to SST Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0MstToSstProc(void)
{
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE)
    {
        if(ScalerDpRx0MstToSstScanInputPort() == _TRUE)
        {
            if(ScalerDpRx0MstToSstMeasureInput() == _TRUE)
            {
                ScalerDpTxSetStreamSource(_DP_TX_SOURCE_MST2SST);
            }
        }
    }
    else
    {
        // Stable Check
        if(ScalerDpRx0MstToSstStableDetect() == _FALSE)
        {
            ScalerDpTxForceIdlePatternSetting();
            ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

            // Disabel MST2SST Watch Dog
            CLR_REG_DP_RX_MST2SST_WATCH_DOG_ENABLE();
        }
    }
}
//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : None
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDpRx0MstToSstScanInputPort(void)
{
    if(ScalerDpRx0MstToSstGetVideoStream() == _FALSE)
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

    if(ScalerDpRx0MstToSstMSACheck() == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx0MstToSstGetVideoInfo() == _FALSE)
    {
        return _FALSE;
    }
    else
    {
        ScalerDpRx0MstToSstSetColorInfo();
    }

    if(ScalerDpRx0MstToSstDisplayFormatSetting() == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx0MstToSstStreamClkRegenerate() == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx0MstToSstFifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
    {
        ScalerDpRx0MstToSstAdjustVsyncDelay();

        if(ScalerDpRx0MstToSstFifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
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
// Description  : On Line Check DP MST2SST stability
// Input Value  : None
// Output Value : True --> DP MST2SST Stable
//                False --> DP MST2SST Unstable
//--------------------------------------------------
bit ScalerDpRx0MstToSstStableDetect(void)
{
    if(ScalerDpRx0MstToSstMiscCheck() == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx0MstToSstFifoCheck(_DP_FIFO_POLLING_CHECK) == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx0MstToSstMSAActiveChange() == _TRUE)
    {
        return _FALSE;
    }

    if(ScalerDpRxMstToSstTxMeasureTimingChange() == _TRUE)
    {
        return _FALSE;
    }

    return _TRUE;
}

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP BS to HS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
WORD ScalerDpRx0MstToSstGetBStoHSDelay(WORD usDpHtotal)
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

//--------------------------------------------------
// Description  : Set DP Rx DPCD DFP Detail Cap Reset
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0DfpDeviceDetailConfigReset(void)
{
#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _OFF)
    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x80, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Set DP Rx DPCD DFP Detail Set
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0DfpDeviceDetailConfig(void)
{
#if(_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _OFF)
    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x80, (_BIT6 | _BIT4 | _BIT3));
#endif
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#endif // End of #if(_DP_MST_SUPPORT == _ON)

//--------------------------------------------------
// Description  : DP FLD Band Finetune
// Input Value  : LaneNumber
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AdjustLaneFLDBand(BYTE ucDpRx0LaneNumber, WORD usVCOBandDiff)
{
    BYTE ucBestVCOBand = 0;
    BYTE ucAutoVCOBand = 0;

    switch(ucDpRx0LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ucAutoVCOBand = (ScalerGetByte(P1D_36_ANA_CDR_11) & 0x7F);

            break;

        case _DP_SCALER_LANE1:

            ucAutoVCOBand = (ScalerGetByte(P1D_37_ANA_CDR_12) & 0x7F);

            break;

        case _DP_SCALER_LANE2:

            ucAutoVCOBand = (ScalerGetByte(P1D_38_ANA_CDR_13) & 0x7F);

            break;

        case _DP_SCALER_LANE3:

            ucAutoVCOBand = (ScalerGetByte(P1D_39_ANA_CDR_14) & 0x7F);

            break;
    }

    // [1:0] freqdet_lane_sel
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), ucDpRx0LaneNumber);

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
            break;
        }
    }

    if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        if(g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] < g_pusDpRx0ClockCount[ucDpRx0LaneNumber])
        {
            ucBestVCOBand = ucAutoVCOBand + (((g_pusDpRx0ClockCount[ucDpRx0LaneNumber] - g_pusDpRx0ClockCount1[ucDpRx0LaneNumber]) / usVCOBandDiff) + 1);
        }
        else
        {
            ucBestVCOBand = ucAutoVCOBand - ((g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] - g_pusDpRx0ClockCount[ucDpRx0LaneNumber]) / usVCOBandDiff);
        }
    }
    else
    {
        ucBestVCOBand = ucAutoVCOBand;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // Manually Reload FLD Band
    switch(ucDpRx0LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ScalerSetBit(P1D_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE1:

            ScalerSetBit(P1D_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE2:

            ScalerSetBit(P1D_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE3:

            ScalerSetBit(P1D_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;
    }
}
//--------------------------------------------------
// Description  : Check Valid Lane CDR
// Input Value  : None
// Output Value : True --> CDR Lock
//--------------------------------------------------
bit ScalerDpRx0CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
    CLR_DP_RX0_SIGNALDETECT_INT_HAPPENED();
#endif

    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            if(ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE0) == _TRUE)
            {
                return _TRUE;
            }

            break;

        case _DP_TWO_LANE:

            if((ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE0) == _TRUE) &&
               (ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE1) == _TRUE))
            {
                return _TRUE;
            }

            break;

        case _DP_FOUR_LANE:
        default:

            if((ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE0) == _TRUE) &&
               (ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE1) == _TRUE) &&
               (ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE2) == _TRUE) &&
               (ScalerDpRx0MeasureLaneCDRClk(ucDpLinkRate, _D0_DP_LANE3) == _TRUE))
            {
                return _TRUE;
            }

            break;
    }

#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
    if(GET_DP_RX0_SIGNALDETECT_INT_HAPPENED() == _TRUE)
    {
        return _TRUE;
    }
    else
#endif
    {
        DebugMessageRx0("7. wuzanne test : DP CDR Unlock", 0);

        return _FALSE;
    }
}
//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0CpIRQ(EnumDpRxBStatusType enumBStatusType)
{
    switch(enumBStatusType)
    {
        case _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL:

            if(GET_DP_RX0_HDCP_MODE() == _HDCP_14)
            {
#if(_DP_MST_SUPPORT == _ON)
                if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x11) & _BIT0) == 0x00)
                {
                    // Reset HDCP Block
                    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
                }

                if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x11) & _BIT1) == _BIT1)
                {
                    ScalerDpRx0SetDpcdValue(0x00, 0x20, 0x05, (ScalerDpRx0GetDpcdInfo(0x00, 0x20, 0x05) | _BIT2));
                }
#else
                // Reset HDCP Block
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
#endif

                SET_DP_RX0_AUX_MANUAL_MODE();

                // Clear Aksv
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x07, 0x00);
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x08, 0x00);
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x09, 0x00);
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0A, 0x00);
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0B, 0x00);

                SET_DP_RX0_AUX_AUTO_MODE();

                // Set B Status
                ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x29) | enumBStatusType));
            }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            else
            {
                // Disable HDCP 2.2 Module
                SET_DP_RX0_HDCP_MODE(_HDCP_14);

                // Disable HDCP2.2 Auth. Done
                ScalerSetBit(PB_20_HDCP_DEBUG, ~_BIT4, 0x00);

                // Reset HDCP Block
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

                ScalerDpRx0SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx0GetDpcdInfo(0x06, 0x94, 0x93) | _BIT4));

                // Clear Authentication Done Flag
                CLR_DP_RX0_HDCP2_AUTHENTICATION_DONE();
            }
#endif
            break;

        case _DP_HDCP_BSTATUS_REAUTH_REQ:

            ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x29) | _BIT3));

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_RXSTATUS_REAUTH_REQ:

            ScalerDpRx0SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx0GetDpcdInfo(0x06, 0x94, 0x93) | _BIT3));

            break;
#endif

        case _DP_HDCP_BSTATUS_V_READY:
        case _DP_HDCP_BSTATUS_R0_AVAILABLE:

            // Set B Status
            ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x29) | enumBStatusType));

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpRx0SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx0GetDpcdInfo(0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;

        case _DP_HDCP2_V_READY:

            ScalerDpRx0SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx0GetDpcdInfo(0x06, 0x94, 0x93) | (enumBStatusType >> 6)));

            break;
#endif

        default:

            break;
    }

    // Link Status CPIRQ Flag
    ScalerDpRx0SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx0GetDpcdInfo(0x00, 0x02, 0x01) | _BIT2));

    ScalerDpRx0HpdIrqAssert();
}

//--------------------------------------------------
// Description : check DFE Coef
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx0DFECheck(void)
{
    if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_FOUR_LANE:

            // Read Lane2 DFE
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx0("7. Lane2 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane3 DFE
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx0("7. Lane3 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx0("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx0("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx0("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx0("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx0("7. Lane0 DFE Fail", 0);

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
// Description  : Check Valid Lane Alignment
// Input Value  : None
// Output Value : True --> Align
//--------------------------------------------------
bit ScalerDpRx0AlignCheck(void)
{
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)

    if(GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE)
    {
        if(GET_DP_RX0_SOURCE_TYPE_JUDGE() == _FALSE)
        {
#if(_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON)
            if(ScalerDpRx0LaneValidCheck() == _FALSE)
            {
                return _TRUE;
            }
#else
            return _TRUE;
#endif
        }
    }

#endif

    if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F) == _DP_ONE_LANE)
    {
        return _TRUE;
    }
    else
    {
        if(ScalerGetBit(PB_0E_DESKEW_PHY, _BIT4) == 0x00)
        {
            if(ScalerGetBit(PB_0E_DESKEW_PHY, (_BIT7 | _BIT6)) != (_BIT7 | _BIT6))
            {
                ScalerSetBit(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

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
// Description : check DP 8b/10b Decode Error
// Input Value  : None
// Output Value : True --> ok, False --> 8b/10b Decode Error
//--------------------------------------------------
bit ScalerDpRx0DecodeCheck(void)
{
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)

    if(GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE)
    {
        if(GET_DP_RX0_SOURCE_TYPE_JUDGE() == _FALSE)
        {
#if(_HW_DP_LANE_VALID_CHECK_SUPPORT == _ON)
            if(ScalerDpRx0LaneValidCheck() == _FALSE)
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
        ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [150,x]
        DELAY_XUS(150);

        switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                if(((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                {
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if(((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT1 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2))) &&
                    (ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2)) == 0x00)))
                {
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:

                if(ScalerGetBit(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
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

    DebugMessageRx0("7. DP 8b/10b Decode Error", 0);

    return _FALSE;
}
//--------------------------------------------------
// Description  : DP Display Format Generator Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx0DisplayFormatSetting(void)
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
        ulVBs2BsCount = g_stDpRx0LinkInfo.ulVBsToBsCountN;
    }
    else
#endif
    {
        // Measurement Enable
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB5_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
        {
            return _FALSE;
        }

        // Pop up The result
        SET_DP_RX0_MEASURE_POP_UP();

        // Measurement Disable
        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);

        // VBs2BS count in GDI clk
        ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB5_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB5_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB5_5A_MN_MEAS_VLN_L)));
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
        usHBs2BsCount = (((DWORD)ScalerGetByte(PB5_5B_MN_MEAS_HLN_M)) << 8) | ((DWORD)ScalerGetByte(PB5_5C_MN_MEAS_HLN_L));

        // VTotal in line, Link Clk / 2 : (Link Rate * 27 / 2)
        usDpVtotal = ulVBs2BsCount * (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2) / usHBs2BsCount * 1000 / _GDI_CLK_KHZ;

        ulDpMvidValue = ((((DWORD)ScalerGetByte(PB6_1A_MSA_MVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1B_MSA_MVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1C_MSA_MVID_2)));

        ulDpNvidValue = ((((DWORD)ScalerGetByte(PB6_1D_MSA_NVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1E_MSA_NVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1F_MSA_NVID_2)));

        // [5] ln_ck_sel = 1'b1 -> CDR Clock
        // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

        // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
        ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

        // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
        ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

        // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

        // Waiting for Measure Done
        ScalerTimerDelayXms(2);

        PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

        PDATA_DWORD(0) = ((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ;

        // Calculate streamclk
        ulStreamClkValue = ((DWORD)ulDpMvidValue * (PDATA_DWORD(0) / ulDpNvidValue) + (PDATA_DWORD(0) % ulDpNvidValue * 100 / ulDpNvidValue * (DWORD)ulDpMvidValue / 100));
    }
    else
#endif
    {
        usDpVtotal = ((((WORD)ScalerGetByte(PB6_10_MSA_VTTE_0)) << 8) | ((WORD)ScalerGetByte(PB6_11_MSA_VTTE_1)));

        // Calculate streamclk (Unit is Hz)
        ulStreamClkValue = (((((((DWORD)ScalerGetByte(PB6_08_MSA_HTT_0)) << 8) | ((WORD)ScalerGetByte(PB6_09_MSA_HTT_1))) * ((DWORD)usDpVtotal) * 100) / ulVBs2BsCount) * _GDI_CLK_KHZ * 10);
    }

    // Input Pixel CLK Unit is 0.1 M
    SET_INPUT_PIXEL_CLK(ulStreamClkValue / 100000);

    // Disable Generate Display Format
    ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT7, 0x00);

    // DP Display Format Generator Reset
    ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(PB5_00_MAC_DIG_RESET_CTRL, ~_BIT7, 0x00);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
    {
        // Delay a Complete Frame
        ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);
    }

    // Set Vactive
    ScalerRead(PB6_16_MSA_VHT_0, 2, &pData[4], _AUTOINC);
    ScalerSetByte(PB5_4D_MN_DPF_VHT_M, pData[4]);
    ScalerSetByte(PB5_4E_MN_DPF_VHT_L, pData[5]);

    // Set Hactive
    ScalerRead(PB6_0C_MSA_HWD_0, 2, pData, _AUTOINC);
    ScalerSetByte(PB5_45_MN_DPF_HWD_M, pData[0]);
    ScalerSetByte(PB5_46_MN_DPF_HWD_L, pData[1]);
    usDpHactive = PDATA_WORD(0);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // HTotal in Pixel Clk, Link Clk / 2 : (Link Rate * 27 / 2)
        WORD usDpHtotal = (DWORD)usHBs2BsCount * (GET_INPUT_PIXEL_CLK() / 10) / (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2);

        // Set Htotal
        ScalerSetByte(PB5_41_MN_DPF_HTT_M, HIBYTE(usDpHtotal));
        ScalerSetByte(PB5_42_MN_DPF_HTT_L, LOBYTE(usDpHtotal));

        // Set Hstart
        ScalerSetByte(PB5_43_MN_DPF_HST_M, HIBYTE(_DP_DE_ONLY_MODE_HSTART));
        ScalerSetByte(PB5_44_MN_DPF_HST_L, LOBYTE(_DP_DE_ONLY_MODE_HSTART));

        // Set HSW
        ScalerSetByte(PB5_47_MN_DPF_HSW_M, HIBYTE(_DP_DE_ONLY_MODE_HSW));
        ScalerSetByte(PB5_48_MN_DPF_HSW_L, LOBYTE(_DP_DE_ONLY_MODE_HSW));

        // Set Vstart
        ScalerSetByte(PB5_4B_MN_DPF_VST_M, HIBYTE(_DP_DE_ONLY_MODE_VSTART));
        ScalerSetByte(PB5_4C_MN_DPF_VST_L, LOBYTE(_DP_DE_ONLY_MODE_VSTART));

        // Set VSW
        ScalerSetByte(PB5_4F_MN_DPF_VSW_M, HIBYTE(_DP_DE_ONLY_MODE_VSW));
        ScalerSetByte(PB5_50_MN_DPF_VSW_L, LOBYTE(_DP_DE_ONLY_MODE_VSW));

        PDATA_WORD(0) = GET_DPRX0_BS_TO_HS_DELAY(usDpHtotal);

        // Set HBs2Bs
        ScalerSetByte(PB5_38_BS2HS_0, pData[0]);
        ScalerSetByte(PB5_39_BS2HS_1, pData[1]);

        ScalerDpRx0InterlaceCheck(&usDpVtotal, &ucOddFlg);

        // Set DE Only Mode Vsync Front Porch
        ScalerSetByte(PB5_40_VS_FRONT_PORCH, GET_DP_RX0_VFRONT_PORCH());

        // Set DE Only Mode
        ScalerSetBit(PB5_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), _BIT4);

        // Choose Frame start BE to Reset FIFO
        ScalerSetBit(PB5_20_PG_CTRL_0, ~_BIT5, 0x00);

        // Set DP FREESYNC Mode Enable
        ScalerSetBit(PB5_F0_DP_RSV0, ~_BIT0, _BIT0);

        ScalerDpRx0SetFREESYNCMsaForLut(usDpHtotal);

        DebugMessageRx0("FREESYNC Mode Enabled!!", ScalerGetByte(PB5_30_DPF_CTRL_0));
    }
    else
#endif
    {
        DWORD ulBs2VsDelay = 0;

        // Set Htotal
        ScalerRead(PB6_08_MSA_HTT_0, 2, &pData[2], _AUTOINC);
        ScalerSetByte(PB5_41_MN_DPF_HTT_M, pData[2]);
        ScalerSetByte(PB5_42_MN_DPF_HTT_L, pData[3]);

        // Get HSW
        pData[4] = ScalerGetBit(PB6_0E_MSA_HSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        pData[5] = ScalerGetByte(PB6_0F_MSA_HSW_1);

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
        ScalerSetByte(PB5_47_MN_DPF_HSW_M, (pData[4] & ~_BIT7));
        ScalerSetByte(PB5_48_MN_DPF_HSW_L, pData[5]);

        // Set Hstart
        ScalerSetByte(PB5_43_MN_DPF_HST_M, pData[8]);
        ScalerSetByte(PB5_44_MN_DPF_HST_L, pData[9]);

        DebugMessageRx0("###Origin usVTotal###", usDpVtotal);

        if(ScalerDpRx0InterlaceCheck(&usDpVtotal, &ucOddFlg) == _TRUE) // Interlace
        {
            DebugMessageRx0("7. IIIIIInterLace Vtotal", usDpVtotal);
        }
        else // Progressive
        {
            DebugMessageRx0("7. PPPPProgressive", 0);
        }

        // Set Vtotal
        ScalerSetByte(PB5_49_MN_DPF_VTT_M, (usDpVtotal >> 8));
        ScalerSetByte(PB5_4A_MN_DPF_VTT_L, (usDpVtotal & 0xFF));

        // Get Vactive
        ScalerRead(PB6_16_MSA_VHT_0, 2, &pData[4], _AUTOINC);

        // V Front porch must not be less than 2 because of V scaling down.
        // Set Vstart -> (Vtotal - Vactive - Frontporch)
        PDATA_WORD(0) = usDpVtotal - PDATA_WORD(2) - GET_DP_RX0_VFRONT_PORCH();
        ScalerSetByte(PB5_4B_MN_DPF_VST_M, pData[0]);
        ScalerSetByte(PB5_4C_MN_DPF_VST_L, pData[1]);

        // Set VSW; Set VSP => Positive
        ScalerSetByte(PB5_4F_MN_DPF_VSW_M, (HIBYTE(_DP_VSYNC_WIDTH) & ~_BIT7));
        ScalerSetByte(PB5_50_MN_DPF_VSW_L, LOBYTE(_DP_VSYNC_WIDTH));

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
        if(GET_AIO_MODERN_STANDBY_MODE() == _TRUE)
        {
            // Set Odd Field BS to VS Delay
            ScalerSetByte(PB5_35_OVBLK2VS_H, (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayOdd >> 16));
            ScalerSetByte(PB5_36_OVBLK2VS_M, (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayOdd >> 8));
            ScalerSetByte(PB5_37_OVBLK2VS_L, (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayOdd >> 0));

            // Set Even Field BS to VS Delay
            ScalerSetByte(PB5_32_EVBLK2VS_H, (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayEven >> 16));
            ScalerSetByte(PB5_33_EVBLK2VS_M, (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayEven >> 8));
            ScalerSetByte(PB5_34_EVBLK2VS_L, (BYTE)(g_stDpRx0LinkInfo.ulVBsToBsDelayEven >> 0));
        }
        else
#endif
        {
            ulBs2VsDelay = ScalerDpRx0GetBStoVSDelay();

            // Set Odd Field BS to VS Delay
            ScalerSetByte(PB5_35_OVBLK2VS_H, (BYTE)(ulBs2VsDelay >> 16));
            ScalerSetByte(PB5_36_OVBLK2VS_M, (BYTE)(ulBs2VsDelay >> 8));
            ScalerSetByte(PB5_37_OVBLK2VS_L, (BYTE)(ulBs2VsDelay >> 0));

            if((bit)ucOddFlg == _TRUE)
            {
                // Get Htotal
                ScalerRead(PB6_08_MSA_HTT_0, 2, &pData[10], _AUTOINC);

                // BStoVSDelay = BStoVSDelay + (Link Clk * 256 / Stream Clk) * ((DWORD)Htotal) / 256;
                ulBs2VsDelay += ((((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00)) * 270UL) * 256) / ((DWORD)GET_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(5)) / 256 / 2;

                SET_DP_RX0_INTERLACE_VTOTAL_NUMBER(_ODD);
            }
            else
            {
                SET_DP_RX0_INTERLACE_VTOTAL_NUMBER(_EVEN);
            }

            // Set Even Field BS to VS Delay
            ScalerSetByte(PB5_32_EVBLK2VS_H, (BYTE)(ulBs2VsDelay >> 16));
            ScalerSetByte(PB5_33_EVBLK2VS_M, (BYTE)(ulBs2VsDelay >> 8));
            ScalerSetByte(PB5_34_EVBLK2VS_L, (BYTE)(ulBs2VsDelay >> 0));
        }

        // Choose VS Rising to Reset FIFO
        ScalerSetBit(PB5_20_PG_CTRL_0, ~_BIT5, 0x00);

        // Set DP FREESYNC Mode Disable
        ScalerSetBit(PB5_F0_DP_RSV0, ~_BIT0, 0x00);

        // Set full last line Mode
        ScalerSetBit(PB5_30_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

        DebugMessageRx0("FREESYNC Mode Disabled", ScalerGetByte(PB5_30_DPF_CTRL_0));
    }

    // Double Buffer to Apply Display Format Setting
    ScalerSetBit(PB5_30_DPF_CTRL_0, ~_BIT6, _BIT6);

    ScalerDpRx0VideoSetting();

    return _TRUE;
}
//--------------------------------------------------
// Description  : DP Video Fifo Check
// Input Value  : Fifo Check Condition
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerDpRx0FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition)
{
    if(enumFifoCheckCondition == _DP_FIFO_DELAY_CHECK)
    {
        ScalerSetBit(PB5_21_PG_CTRL_1, ~(_BIT4 | _BIT2 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
        if(GET_AIO_MODERN_STANDBY_MODE() == _FALSE)
#endif
        {
            ScalerTimerDelayXms(_DP_TWO_FRAME_TIME_MAX);

            pData[0] = 0;

            while(pData[0] < 6)
            {
                ScalerTimerDelayXms(10);

                if((ScalerGetBit(PB5_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PB5_21_PG_CTRL_1, _BIT2) == _BIT2))
                {
                    return _FALSE;
                }

                pData[0]++;
            }
        }
    }
    else
    {
        if((ScalerGetBit(PB5_21_PG_CTRL_1, _BIT4) == _BIT4) || (ScalerGetBit(PB5_21_PG_CTRL_1, _BIT2) == _BIT2))
        {
            return _FALSE;
        }
    }

    if(ScalerGetBit(PB6_3B_DP_IRQ_CTRL1, _BIT4) == 0x00)
    {
        // Enable DP No Video Stream IRQ
        ScalerDpRx0SetNoVideoStreamIRQ(_ENABLE);
    }

    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x05, _BIT0) == 0x00)
    {
        // Set DP Receive Port0 In Sync
        ScalerDpRx0SinkStatusSet(_DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : HDCP Reset For Dp Rx0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0HDCPBlockReset(void)
{
    // Reset HDCP Block
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x29, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x2A, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x2B, 0x00);

    for(pData[0] = 0; pData[0] < 20; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x14 + pData[0]), 0x00);
    }

    for(pData[0] = 0; pData[0] < 15; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), 0x00);
    }

    SET_DP_RX0_AUX_MANUAL_MODE();

    // Clear Aksv
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x07, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x08, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x09, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0A, 0x00);
    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x0B, 0x00);

    SET_DP_RX0_AUX_AUTO_MODE();

#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    ScalerDpRx0HDCPChangeAuthState(_DP_RX_HDCP_STATE_IDLE);
#endif
}

//--------------------------------------------------
// Description  : Check whether HDCP is valid
// Input Value  : None
// Output Value : TRUE => HDCP valid
//--------------------------------------------------
bit ScalerDpRx0HdcpCheckValid(void)
{
    if(GET_DP_RX0_HDCP_MODE() == _HDCP_14)
    {
        if(ScalerGetBit(PB_20_HDCP_DEBUG, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
        {
            return _TRUE;
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(ScalerGetBit(PB_20_HDCP_DEBUG, _BIT4) == _BIT4)
        {
            if((ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
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
bit ScalerDpRx0HdcpCheckEnabled(void)
{
    if(GET_DP_RX0_HDCP_MODE() == _HDCP_14)
    {
        if(ScalerGetBit(PB_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5))
        {
            if((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) ||
               (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
               (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) ||
               (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
               (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00))
            {
                return _TRUE;
            }
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(ScalerGetBit(PB_20_HDCP_DEBUG, _BIT4) == _BIT4)
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
bit ScalerDpRx0HdcpMeasureCheck(void)
{
    DWORD ulLinkClk = 0;
    WORD usHTotalCount = 0;

    // Pop up Main Stream Attributes
    ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Vtotal
    ScalerRead(PB6_10_MSA_VTTE_0, 2, &pData[10], _AUTOINC);

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
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Waiting for Measure Done
    ScalerTimerDelayXms(2);

    if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));
    }
    else
    {
        if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = 0x4E20;
        }
        else if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
        {
            PDATA_WORD(0) = 0x2710;
        }
        else // Both Default && _DP_LINK_RBR Case
        {
            PDATA_WORD(0) = 0x1770;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

    // Link Clk in KHz
    ulLinkClk = (PDATA_DWORD(0) / 1000);

    DebugMessageRx0("Current Link Clk", ulLinkClk);

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
    ScalerRead(PB5_58_MN_MEAS_CTRL, 3, &pData[1], _AUTOINC);

    // Get Measure Htotal Counts
    ScalerRead(PB5_5B_MN_MEAS_HLN_M, 2, &pData[6], _AUTOINC);

    // Disable Measure Block
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);

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
bit ScalerDpRx0HdcpReAuthStatusCheck(void)
{
    if(GET_DP_RX0_HDCP_MODE() == _HDCP_14)
    {
        if((ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) || (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) || (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
           (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00))
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
void ScalerDpRx0MacInitial(void)
{
    // Set Digital Phy to Normal
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // DP RGB Output Enable
    ScalerSetBit(PB5_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // DP CLK Output Enable
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, _BIT6);

    // 0x00:disable error correction, 0xF4:enable all error correction
    ScalerSetBit(PB6_00_MN_STRM_ATTR_CTRL, ~_BIT1, _BIT1);

    // Disable DP Fifo Under/OverFlow Watch Dog
    ScalerDpRx0SetFifoWD(_DISABLE);

    // Disable DP Fifo Under/OverFlow IRQ
    ScalerDpRx0SetFifoIRQ(_DISABLE);

    // Disable DP No Video Stream IRQ
    ScalerDpRx0SetNoVideoStreamIRQ(_DISABLE);

    ScalerDpRx0SetInitialRSV0InfoType();

#if((_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON) && (_HW_DP_VSC_SDP_REG_SUPPORT != _ON))
    ScalerDpRx0SetInitialRSV1InfoType();
#endif

    CLR_DP_RX0_MSA_FAIL_MAC_RESET_COUNT();
}
//--------------------------------------------------
// Description : check DP CDR locked or unlocked
// Input Value  : DP Lane
// Output Value : True --> locked; False --> unlocked
//--------------------------------------------------
bit ScalerDpRx0MeasureLaneCDRClk(BYTE ucDpLinkRate, BYTE ucDpRx0LaneNumber)
{
    WORD usCDRClockCount = 0;

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            if((abs(g_pusDpRx0ClockCount[ucDpRx0LaneNumber] - 0x2710)) > (0x2710 >> 4))
            {
                return _TRUE;
            }

            break;

        case _DP_LINK_HBR:

            if((abs(g_pusDpRx0ClockCount[ucDpRx0LaneNumber] - 0x1388)) > (0x1388 >> 4))
            {
                return _TRUE;
            }

            break;

        default:
        case _DP_LINK_RBR:

            if((abs(g_pusDpRx0ClockCount[ucDpRx0LaneNumber] - 0xBB8)) > (0xBB8 >> 4))
            {
                return _TRUE;
            }

            break;
    }

    // Select Measure CDR Clock & XTAL 27M Count 1000 Times
    ScalerSetByte(PB_50_DP_SIG_DET_0, 0x23);

    // Select CDR Lane
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), ucDpRx0LaneNumber);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // Toggle Start Measure
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(pData[0] = 0; pData[0] <= 30; pData[0]++)
    {
        DELAY_5US();

        if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            break;
        }
    }

    if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == 0x00)
    {
        return _FALSE;
    }

    usCDRClockCount = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

    if(abs(g_pusDpRx0ClockCount[ucDpRx0LaneNumber] - usCDRClockCount) > (g_pusDpRx0ClockCount[ucDpRx0LaneNumber] >> 7))
    {
        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 1 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
bit ScalerDpRx0PhyCtsTp1Check(void)
{
    // Wait for 10ms
    ScalerTimerDelayXms(10);

    // Clear 8B/10B Decode Error Flags
    ScalerSetBit(PB_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Wait for 2ms
    ScalerTimerDelayXms(2);

    ScalerSetByte(P1D_0C_SDM_01, ScalerGetByte(PB_06_DECODE_10B8B_ERROR));
    ScalerSetByte(P1D_0D_SDM_02, ScalerGetByte(PB_14_EQ_CRC_3));

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
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

    if(((ScalerGetByte(P1D_0C_SDM_01) & 0x0F) == 0x00) &&
       ((ScalerGetByte(P1D_0D_SDM_02) & pData[0]) != 0x00))
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
bit ScalerDpRx0PhyCtsTp2Check(void)
{
    ScalerTimerDelayXms(10);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
    {
        case 0x00: // Lane0 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), 0x00);

            break;

        case 0x10: // Lane1 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case 0x20: // Lane2 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case 0x30: // Lane3 Test

            ScalerSetBit(PB_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;

        default:
            break;
    }

    // Mac Use Xtal Clk
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    // Clear EQ-CRC
    ScalerSetBit(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

    // Start Calculate EQ-CRC
    ScalerSetBit(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    ScalerTimerDelayXms(2);

    ScalerSetByte(P1D_0C_SDM_01, ScalerGetByte(PB_12_EQ_CRC_1));
    ScalerSetByte(P1D_0D_SDM_02, ScalerGetByte(PB_13_EQ_CRC_2));

    // Stop Calculate EQ-CRC
    ScalerSetBit(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

    switch(g_ucDpRx0PhyCtsCtrl & 0x30)
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

    if((ScalerGetByte(P1D_0C_SDM_01) & pData[0]) != 0x00)
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
void ScalerDpRx0PhyInitial(void)
{
    /////////////
    // Rx Misc //
    /////////////

    // [1] mhl_mode = 1'b0 --> Disable MHL Mode
    ScalerSetBit(P1D_17_BANDGAP_03, ~_BIT1, 0x00);

    // [4] en_mhl_op = 1'b0 --> Disable D0 Port MHL OP
    // [2] HST_BUF_SEL = 1'b0 --> Disable Hysteresis Amplifier in Clock Lane
    ScalerSetBit(P1D_1B_CMU_01, ~(_BIT4 | _BIT2), 0x00);


    /////////////////////
    // CDR DFE Setting //
    /////////////////////

    // [3:1] LE_lowgain_highboost = 3'b100 --> LE HighGain Mode
    ScalerSetBit(P1D_22_CMU_08, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

    // [7] SEL_DFE_DELAY = 1'b0 --> Normal DFE Delay
    ScalerSetBit(P1D_22_CMU_08, ~_BIT7, 0x00);

    // [0] De_brank_en = 1'b0 --> Disable Blank Function
    ScalerSetBit(P1D_AF_L0_GDI_DE, ~_BIT0, 0x00);
    ScalerSetBit(P1D_BF_L1_GDI_DE, ~_BIT0, 0x00);
    ScalerSetBit(P1D_CF_L2_GDI_DE, ~_BIT0, 0x00);
    ScalerSetBit(P1D_DF_L3_GDI_DE, ~_BIT0, 0x00);

    // [3:0] Set Digital PHY Sampling Edge (APHY to DPHY), Spec Suggest Use 0x0F in 6410/6432
    ScalerSetBit(PB_05_SAMPLE_EDGE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [7] en_wide_temp = 1'b1 --> Vcp-Vcn = -0.1V
    ScalerSetBit(P1D_35_ANA_CDR_10, ~_BIT7, _BIT7);

    // [3:2] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 700M/v
    // [1:0] reg_vcm_tune = 2'b11 --> Vcm = VDD/2
    ScalerSetBit(P1D_30_ANA_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [4] sel_cont3 = 1'b1 --> BBPD UP/DN Pulse Div 3
    ScalerSetBit(P1D_2D_ANA_CDR_02, ~_BIT4, _BIT4);

    // [3:2] ENHANCE_SA_BIAS = 2'b00 --> SumAmp Bias = Normal
    ScalerSetBit(P1D_1D_CMU_03, ~(_BIT3 | _BIT2), 0x00);

    // [7:4] Enable Data Stream Signal Detection
    ScalerSetBit(P1D_19_IMPEDANCE_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // DP Global Parameter MeasureCount Initial
    ScalerSyncDpMeasureCountInitial();
}
//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : None
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDpRx0ScanInputPort(void)
{
    if(GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _SOURCE_NONE;
    }

    // 2nd Scramble Setting Sync
    ScalerDpRx0ScrambleSetting();

    if(ScalerDpRx0HdcpCheck() == _FALSE)
    {
        DebugMessageRx0("7. DP HDCP Check Fail", 0);

        ScalerDpRx0CpIRQ(_DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

#if(_DP_LONG_HPD_AFTER_CPIRQ_SUPPORT == _ON)
        if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x11) & _BIT0) == 0x00)
        {
            ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
        }
#endif

        return _SOURCE_NONE;
    }

    if(ScalerDpRx0GetVideoStream() == _FALSE)
    {
        DebugMessageRx0("7. DP Video Stream Fail", 0);

        return _SOURCE_NONE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if((ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x07) & _BIT7) == _BIT7)
    {
        SET_DP_FREESYNC_ENABLED();
    }
    else
    {
        CLR_FREESYNC_ENABLED();
    }
#endif

    if(ScalerDpRx0MSACheck() == _FALSE)
    {
        DebugMessageRx0("7. DP MSA Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx0GetVideoInfo() == _FALSE)
    {
        DebugMessageRx0("7. DP Get Video Info Fail", 0);

        return _SOURCE_NONE;
    }
    else
    {
        ScalerDpRx0SetColorInfo();
    }

    if(ScalerDpRx0DisplayFormatSetting() == _FALSE)
    {
        DebugMessageRx0("7. DP Display Format Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx0StreamClkRegenerate() == _FALSE)
    {
        DebugMessageRx0("7. DP SteamClk Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx0FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
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

            ScalerDpRx0AdjustVsyncDelay();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if((ScalerSyncCheckUrgentEvent() == _TRUE))
            {
                return _SOURCE_NONE;
            }
#endif

            if(ScalerDpRx0FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
            {
#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if((ScalerSyncCheckUrgentEvent() == _TRUE))
                {
                    return _SOURCE_NONE;
                }
#endif

                ScalerDpRx0AdjustVsyncDelay();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if((ScalerSyncCheckUrgentEvent() == _TRUE))
                {
                    return _SOURCE_NONE;
                }
#endif

                if(ScalerDpRx0FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
                {
                    DebugMessageRx0("7. DP Fifo Fail", 0);

                    return _SOURCE_NONE;
                }
            }
        }
    }

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);

#if(_DP_FREESYNC_SUPPORT == _ON)
    // Measurement Enable for On-Line VFreq check
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);
#endif

    ScalerSetBit(PB5_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

#if(_AUDIO_SUPPORT == _ON)
    // Enable Audio Channel
    ScalerAudioDpAudioEnable(_ENABLE, _D0_INPUT_PORT);
#endif

#if(_DP_MST_SUPPORT == _ON)
    CLR_DP_RX0_SOURCE_FIRST_POWER_ON();
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    ScalerDpRx0InfoFrameRSV0Initial();
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    ScalerFreeSyncDpRx0GetSPDVfreqMaxMin();
#endif

#if((_DP_HDR10_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
    ScalerDpRx0SwitchHDR10CmpAudioInfo();
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    ScalerDpRx0TimingInfoBackup();
#endif

    DebugMessageRx0("Source DP Rx0 Found", 0);

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    SET_DP_RX0_SOURCE_TYPE_JUDGE();
#endif

    return _SOURCE_DP;
}
//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDFEInitial(EnumDpLinkRate enumDpLinkRate)
{
    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [3] Disable Running Length Detection
    // [2] bypass Blank out Case-3 Symbol
    ScalerSetBit(P1D_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    ScalerSetBit(P1D_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    ScalerSetBit(P1D_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    ScalerSetBit(P1D_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

    // [7:6] adapt_mode[1:0] = 2'b11 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 3)
    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetByte(P1D_E0_MODE_TIMER, 0xF2);

    // Set DFE Delay Time
    ScalerSetByte(P1D_E1_TIMER, 0x01);

    // Tap0,Tap1 Loop Gain 1/512
    ScalerSetBit(P1D_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap2,Tap3 Loop Gain 1/512
    ScalerSetBit(P1D_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4,Servo Loop Gain 1/512
    ScalerSetBit(P1D_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // LE Gain1 Loop Gain 1/256, LE Gain2 Loop Gain 0, LE Pre-Courser Gain 0
    ScalerSetBit(P1D_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit(P1D_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap0 Max is 21
    ScalerSetByte(P1D_E6_LIMIT_1, 0x35);

    if(enumDpLinkRate == _DP_LINK_HBR2)
    {
        if(GET_DP_RX0_PHY_CTS_FLG() == _TRUE)
        {
            // Tap1 Min is 49
            ScalerSetBit(P1D_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));
        }
        else
        {
            // Tap1 Min is 46
            ScalerSetBit(P1D_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT2 | _BIT1));
        }
    }
    else
    {
        // Tap1 Min is 51
        ScalerSetBit(P1D_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
    }

    // Tap2 Max is 6, Min is -6
    ScalerSetBit(P1D_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit(P1D_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P1D_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 0, Min is -3
    ScalerSetBit(P1D_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1D_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 0, Min is -3
    ScalerSetBit(P1D_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1D_EB_LIMIT_6, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P1D_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Tap0 Threshold = 10
    ScalerSetBit(P1D_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == 0x00)
    {
        // Set Vth Max = 6, Min = 0
        ScalerSetByte(P1D_F9_LIMIT_10, 0x60);
    }
    else if(enumDpLinkRate == _DP_LINK_HBR2)
    {
        // Set Vth Max = 6, Min = 4
        ScalerSetByte(P1D_F9_LIMIT_10, 0x64);
    }
    else
    {
        // Set Vth Max = 6, Min = 2
        ScalerSetByte(P1D_F9_LIMIT_10, 0x62);
    }

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetByte(P1D_EC_LOOP_DIV_1, 0xA3);

    // Tap Divider = 10 for TP2
    ScalerSetByte(P1D_ED_LOOP_DIV_2, 0xCA);

    // [1] tap1_trans = 1'b0 --> Tap1 is Effective every bit
    // [0] tap0_trans = 1'b0 --> Tap0 is Effective every bit
    ScalerSetBit(P1D_E3_GAIN_2, ~(_BIT1 | _BIT0), 0x00);

    if(enumDpLinkRate == _DP_LINK_HBR2)
    {
        // [1:0] trans_rlength = 2'b01 --> Tap0 Run Length = 3
        ScalerSetBit(P1D_E4_GAIN_3, ~(_BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // [1:0] trans_rlength = 2'b00 --> Tap0 Run Length = 2
        ScalerSetBit(P1D_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);
    }

    // [5] servo_notrans = 1'b0 --> Servo is Effective every bit
    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective every bit
    ScalerSetBit(P1D_F8_GRAY_DEC_2, ~(_BIT5 | _BIT4), 0x00);


    /////////////////////////
    // DFE Code Initialize //
    /////////////////////////

    if(enumDpLinkRate == _DP_LINK_HBR2)
    {
        if((GET_DP_RX0_PHY_CTS_FLG() == _TRUE) || (ScalerDpRx0GetDpcdBitInfo(0x00, 0x02, 0x70, _BIT7) == _BIT7))
        {
            // LE Max = 18, Initial = 16, Servo Initial = 16
            ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x20);
            ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x20);
            ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x20);
            ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x20);
            ScalerSetByte(P1D_A3_L0_INIT_1, 0xD0);
            ScalerSetByte(P1D_B3_L1_INIT_1, 0xD0);
            ScalerSetByte(P1D_C3_L2_INIT_1, 0xD0);
            ScalerSetByte(P1D_D3_L3_INIT_1, 0xD0);
        }
        else
        {
            // LE Max = 20, Initial = 12, Servo Initial = 16
            ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x4C);
            ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x4C);
            ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x4C);
            ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x4C);
            ScalerSetByte(P1D_A3_L0_INIT_1, 0x90);
            ScalerSetByte(P1D_B3_L1_INIT_1, 0x90);
            ScalerSetByte(P1D_C3_L2_INIT_1, 0x90);
            ScalerSetByte(P1D_D3_L3_INIT_1, 0x90);
        }
    }
    else
    {
        // LE Max = 20, Initial = 16, Servo Initial = 16
        ScalerSetByte(P1D_A2_L0_LIMIT_INIT, 0x40);
        ScalerSetByte(P1D_B2_L1_LIMIT_INIT, 0x40);
        ScalerSetByte(P1D_C2_L2_LIMIT_INIT, 0x40);
        ScalerSetByte(P1D_D2_L3_LIMIT_INIT, 0x40);
        ScalerSetByte(P1D_A3_L0_INIT_1, 0xD0);
        ScalerSetByte(P1D_B3_L1_INIT_1, 0xD0);
        ScalerSetByte(P1D_C3_L2_INIT_1, 0xD0);
        ScalerSetByte(P1D_D3_L3_INIT_1, 0xD0);
    }

    // Tap0 Initial Value = 18
    ScalerSetByte(P1D_A4_L0_INIT_2, 0x12);
    ScalerSetByte(P1D_B4_L1_INIT_2, 0x12);
    ScalerSetByte(P1D_C4_L2_INIT_2, 0x12);
    ScalerSetByte(P1D_D4_L3_INIT_2, 0x12);

    // Tap1 Initial Value = 15
    ScalerSetByte(P1D_A5_L0_INIT_3, 0x0F);
    ScalerSetByte(P1D_B5_L1_INIT_3, 0x0F);
    ScalerSetByte(P1D_C5_L2_INIT_3, 0x0F);
    ScalerSetByte(P1D_D5_L3_INIT_3, 0x0F);

    // Tap2 Initial Value = 0
    ScalerSetByte(P1D_A6_L0_INIT_4, 0x00);
    ScalerSetByte(P1D_B6_L1_INIT_4, 0x00);
    ScalerSetByte(P1D_C6_L2_INIT_4, 0x00);
    ScalerSetByte(P1D_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 4
    ScalerSetByte(P1D_A9_L0_INIT_7, 0x04);
    ScalerSetByte(P1D_B9_L1_INIT_7, 0x04);
    ScalerSetByte(P1D_C9_L2_INIT_7, 0x04);
    ScalerSetByte(P1D_D9_L3_INIT_7, 0x04);

    // Load Intial DFE Code
    ScalerSetByte(P1D_AA_L0_INIT_8, 0xFF);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0xFF);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0xFF);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0xFF);

    ScalerSetByte(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte(P1D_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(P1D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P1D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetByte(P1D_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(P1D_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(P1D_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(P1D_D1_L3_DFE_EN_2, 0x00);
}
//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow IRQ
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetFifoIRQ(bit bEn)
{
    ScalerSetBit(PB6_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), ((bEn == _ENABLE) ? (_BIT1 | _BIT0) : 0x00));
}
//--------------------------------------------------
// Description  : Enable DP Fifo Under/OverFlow Watch Dog
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetFifoWD(bit bEn)
{
    ScalerSetBit(PB6_38_DP_VWD_CTRL, ~(_BIT5 | _BIT4), ((bEn == _ENABLE) ? (_BIT5 | _BIT4) : 0x00));
}

//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : None
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpRx0StableDetect(void)
{
#if(_DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER == _ON)
    if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
#else
    if((ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
       (ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
#endif
    {
        DebugMessageRx0("7. DP Power Down", 0);

        return _FALSE;
    }

    if((ScalerDpRx0CDRCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE) ||
       (ScalerDpRx0AlignCheck() == _FALSE) ||
       (ScalerDpRx0DecodeCheck() == _FALSE) ||
       ((ScalerDpRx0DFECheck() == _FALSE) && (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE)))
    {
        DebugMessageRx0("7. DP Link Fail", 0);

        return _FALSE;
    }

    if(ScalerDpRx0GetVideoStream() == _FALSE)
    {
        DebugMessageRx0("7. DP Video Stream Fail", 0);

        return _FALSE;
    }

    if(ScalerDpRx0MiscCheck() == _FALSE)
    {
        DebugMessageRx0("7. DP Misc Change", 0);

        return _FALSE;
    }

    if(ScalerDpRx0FifoCheck(_DP_FIFO_POLLING_CHECK) == _FALSE)
    {
        DebugMessageRx0("7. Fifo Under/Overflow", 0);

        return _FALSE;
    }

    if(ScalerDpRx0MSAActiveChange() == _TRUE)
    {
        DebugMessageRx0("7. MSA Timing Change", 0);

        return _FALSE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(ScalerDpRx0GetFREESYNCStatusChange() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Clear CPIRQ Flag
    ScalerDpRx0CheckHdcpCpirqStatus();

    ScalerDpRx0CrcCalculate();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Dp HotPlug Event
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetHotPlugEvent(EnumDpHotPlugAssertType enumHpdType)
{
#if(!((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
    if((enumHpdType > _DP_HPD_LOW) && (ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _FALSE))
    {
        return;
    }
#endif

    // If the priority of enumHpdType is higher
    if(enumHpdType < GET_DP_RX0_HOTPLUG_ASSERT_TYPE())
    {
        SET_DP_RX0_HOTPLUG_ASSERT_TYPE(enumHpdType);
    }
}

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Backup Timing Info for Modern Standby
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0TimingInfoBackup(void)
{
    // Backup Offset Value of Stream Clock
    g_stDpRx0LinkInfo.lStreamClockOffset = ((((SDWORD)ScalerGetBit(PB5_BA_MN_SCLKG_SDM_SUMC_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << 16) |
                                            (((WORD)ScalerGetByte(PB5_BB_MN_SCLKG_SDM_SUMC_M)) << 8) |
                                            (ScalerGetByte(PB5_BC_MN_SCLKG_SDM_SUMC_L))) >> 1;

    // Backup VBs2Bs Delay of Even Field
    g_stDpRx0LinkInfo.ulVBsToBsDelayEven = (((DWORD)ScalerGetByte(PB5_32_EVBLK2VS_H)) << 16) |
                                           (((WORD)ScalerGetByte(PB5_33_EVBLK2VS_M)) << 8) |
                                           (ScalerGetByte(PB5_34_EVBLK2VS_L));

    // Backup VBs2Bs Delay of Odd Field
    g_stDpRx0LinkInfo.ulVBsToBsDelayOdd = (((DWORD)ScalerGetByte(PB5_35_OVBLK2VS_H)) << 16) |
                                          (((WORD)ScalerGetByte(PB5_36_OVBLK2VS_M)) << 8) |
                                          (ScalerGetByte(PB5_37_OVBLK2VS_L));
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx LT Status Check
// Input Value  : None
// Output Value : True --> LT Status Pass
//                False --> LT Status Fail
//--------------------------------------------------
bit ScalerDpRx0LTStatusCheck(void)
{
    if((ScalerDpRx0CDRCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
       (ScalerDpRx0AlignCheck() == _TRUE) &&
       (ScalerDpRx0DecodeCheck() == _TRUE) &&
       ((ScalerDpRx0DFECheck() == _TRUE) || (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE)))
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
void ScalerDpRx0HDCPEnableReadIrq(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x2A) > 3)
        {
            ScalerSetBit(PB7_FA_DUMMY_0, ~_BIT0, _BIT0);

            ScalerSetBit(PB7_FA_DUMMY_0, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));
        }
    }
    else
    {
        ScalerSetBit(PB7_FA_DUMMY_0, ~(_BIT3 | _BIT1), 0x00);

        CLR_DP_RX0_HDCP_AUTH_READ_IRQ_TIMEOUT();
    }
}
//--------------------------------------------------
// Description  : DP MST2SST Display Format Generator Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx0MstToSstDisplayFormatSetting(void)
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
    SET_DP_RX0_MEASURE_POP_UP_MST2SST();

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
        usDpVtotal = ulVBs2BsCount * (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2) / usHBs2BsCount * 1000 / _GDI_CLK_KHZ;

        ulDpMvidValue = ((((DWORD)ScalerGetByte(PA_20_MSA_MVID_00)) << 16) | (((DWORD)ScalerGetByte(PA_21_MSA_MVID_01)) << 8) | ((DWORD)ScalerGetByte(PA_22_MSA_MVID_02)));

        ulDpNvidValue = ((((DWORD)ScalerGetByte(PA_23_MSA_NVID_00)) << 16) | (((DWORD)ScalerGetByte(PA_24_MSA_NVID_01)) << 8) | ((DWORD)ScalerGetByte(PA_25_MSA_NVID_02)));

        // [5] ln_ck_sel = 1'b1 -> CDR Clock
        // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

        // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
        ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

        // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
        ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

        // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

        // Waiting for Measure Done
        ScalerTimerDelayXms(2);

        PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

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
        WORD usDpHtotal = (DWORD)usHBs2BsCount * (GET_DP_TX_INPUT_PIXEL_CLK() / 10) / (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2);

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

        PDATA_WORD(0) = ScalerDpRx0MstToSstGetBStoHSDelay(usDpHtotal);

        // Set HBs2Bs
        ScalerSetByte(PA_3D_BS2HS_0, pData[0]);
        ScalerSetByte(PA_3E_BS2HS_1, pData[1]);

        ScalerDpRx0MstToSstInterlaceCheck(&usDpVtotal, &ucOddFlg);

        // Set DE Only Mode Vsync Front Porch
        ScalerSetByte(PA_3F_VS_FRONT_PORCH, GET_DP_RX0_VFRONT_PORCH());

        // Set DE Only Mode
        ScalerSetBit(PA_35_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), _BIT4);

        // Choose Frame start BE to Reset FIFO
        ScalerSetBit(PA_30_PG_CTRL_0, ~_BIT5, 0x00);

        // Set DP FREESYNC Mode Enable
        ScalerSetBit(PA_F0_DP_RSV0, ~_BIT0, _BIT0);

        DebugMessageRx0("MST FREESYNC Mode Enabled!!", ScalerGetByte(PA_35_DPF_CTRL_0));
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

        DebugMessageRx0("###Origin usVTotal###", usDpVtotal);

        if(ScalerDpRx0MstToSstInterlaceCheck(&usDpVtotal, &ucOddFlg) == _TRUE) // Interlace
        {
            DebugMessageRx0("7. MST IIIIIInterLace Vtotal", usDpVtotal);

            SET_DP_TX_INPUT_INTERLACE_MODE(_ON);
        }
        else // Progressive
        {
            DebugMessageRx0("7. MST PPPPProgressive", 0);

            SET_DP_TX_INPUT_INTERLACE_MODE(_OFF);
        }

        // Set Vtotal
        ScalerSetByte(PA_48_MN_DPF_VTT_M, (usDpVtotal >> 8));
        ScalerSetByte(PA_49_MN_DPF_VTT_L, (usDpVtotal & 0xFF));

        // Get Vactive
        ScalerRead(PA_1C_MSA_VHT_0, 2, &pData[4], _AUTOINC);

        // V Front porch must not be less than 2 because of V scaling down.
        // Set Vstart -> (Vtotal - Vactive - Frontporch)
        PDATA_WORD(0) = usDpVtotal - PDATA_WORD(2) - GET_DP_RX0_MST_TO_SST_VFRONT_PORCH();
        ScalerSetByte(PA_4A_MN_DPF_VST_M, pData[0]);
        ScalerSetByte(PA_4B_MN_DPF_VST_L, pData[1]);

        // Set VSW; Set VSP => Positive
        ScalerSetByte(PA_4E_MN_DPF_VSW_M, (HIBYTE(_DP_VSYNC_WIDTH_MST2SST) & ~_BIT7));
        ScalerSetByte(PA_4F_MN_DPF_VSW_L, LOBYTE(_DP_VSYNC_WIDTH_MST2SST));

        ulBs2VsDelay = ScalerDpRx0MstToSstGetBStoVSDelay();

        // Set Odd Field BS to VS Delay
        ScalerSetByte(PA_3A_OVBLK2VS_H, (BYTE)(ulBs2VsDelay >> 16));
        ScalerSetByte(PA_3B_OVBLK2VS_M, (BYTE)(ulBs2VsDelay >> 8));
        ScalerSetByte(PA_3C_OVBLK2VS_L, (BYTE)(ulBs2VsDelay >> 0));

        if((bit)ucOddFlg == _TRUE)
        {
            // Get Htotal
            ScalerRead(PA_10_MSA_HTT_0, 2, &pData[0], _AUTOINC);

            // BStoVSDelay = BStoVSDelay + (Link Clk * 256 / Stream Clk) * ((DWORD)Htotal) / 256;
            ulBs2VsDelay += ((((DWORD)ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00)) * 270UL) * 256) / ((DWORD)GET_DP_TX_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(0)) / 256 / 2;

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

        DebugMessageRx0("MST FREESYNC Mode Disabled!!", ScalerGetByte(PA_35_DPF_CTRL_0));
    }

    // Double Buffer to Apply Display Format Setting
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT6, _BIT6);

    ScalerDpRx0MstToSstVideoSetting();

    return _TRUE;
}
//--------------------------------------------------
// Description  : DP MST2SST Video Fifo Check
// Input Value  : Fifo Check Condition
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerDpRx0MstToSstFifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition)
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
// Description  : DP Rx0 MST to SST Measure
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx0MstToSstMeasureInput(void)
{
    // Format Conversion Select to SST_D0
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
#endif

#endif

//--------------------------------------------------
// Description  : Read DP Rx Error Count
// Input Value  : DP Input Port
// Output Value : DP 4 Lane Error Count & Valid Flag
//--------------------------------------------------
StructDpRxErrorCount ScalerDpRx0GetErrorCount(void)
{
    StructDpRxErrorCount stDpRxErrorCount;

    if((ScalerDpRx0CDRCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE) ||
       (ScalerDpRx0SignalCheck(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE))
    {
        DebugMessageSystem("Rx Fail to Report Valid Error Counter", 0x00);

        switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
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
        switch(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            case _DP_TWO_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE1);
                stDpRxErrorCount.usDpRxLane2ErrorCount = 0;
                stDpRxErrorCount.usDpRxLane3ErrorCount = 0;

                break;

            default:
            case _DP_FOUR_LANE:

                stDpRxErrorCount.usDpRxLane0ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE0);
                stDpRxErrorCount.usDpRxLane1ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE1);
                stDpRxErrorCount.usDpRxLane2ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE2);
                stDpRxErrorCount.usDpRxLane3ErrorCount = ScalerDpRx0GetDecodeErrorCount(_D0_DP_LANE3);

                break;
        }
    }

    // Reset Error Counter
    ScalerDpRx0DecodeErrorCountReset();

    return stDpRxErrorCount;
}
#endif // End of #if(_D0_DP_EXIST == _ON)


