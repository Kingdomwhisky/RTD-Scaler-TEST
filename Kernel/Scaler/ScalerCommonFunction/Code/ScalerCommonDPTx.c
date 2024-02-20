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
// ID Code      : ScalerCommonDPTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_DP_TX__

#include "ScalerCommonFunctionInclude.h"

#if(_DP_TX_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#define _DP_TX_SST_TU_SIZE                          32

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructDPTxModeInfoType g_stTxModeInfo;
StructDPTxInputInfo g_stTxInputInfo;
EnumDPTxIRQEventType g_enumDpTxIRQType = _DP_TX_IRQ_HPD_NONE;
EnumDPTxIRQEventType g_enumDpTxIRQTypeInt = _DP_TX_IRQ_HPD_NONE;
EnumDPTxTRQEventHDCPType g_enumDpTxIRQHDCPType = _DP_TX_IRQ_HDCP_NONE;
StructTimingInfo g_stDPTxInputTimingInfo;
StructDPTxHDCPAuthInfo g_stTxHDCPAuthInfo;
StructCloneModeSwitchInfo g_stCloneModeSwitch;
BYTE g_pucDpTxHdcpKsvFifo[_DP_TX_HDCP_DEVICE_COUNT_MAX * 5];
#if(_DP_HDCP14_CTS_SUPPORT == _ON)
BYTE g_pucDpTxHdcpKsvBackup[5];
#endif
BYTE g_pucDpTxHdcpDownStreamV[20];
BYTE g_pucDpTxAudioInfoframeCurrent[10];

bit g_bDpTxExceedBW = _FALSE;
bit g_bDpTxIRQHPDDetected = _FALSE;
bit g_bDpTxSourceChanged = _FALSE;
BYTE g_ucDpTxStreamSource = _DP_TX_SOURCE_NONE;
BYTE g_ucDpTxCtsRequestType = _DP_TX_CTS_NONE;

#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
BYTE g_ucDpTxConfigSetting = _DP_TX_CONFIG_NONE;
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit g_bDpTxVscSdpColorMode;
#endif

WORD g_usDpTxEdidBw;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpTxJudgeHandler(void);
void ScalerDpTxModeHandler(void);
void ScalerDpTxInitial(void);
bit ScalerDpTxLinkConfig(void);

#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
void ScalerDpTxLinkConfigAdjust(EnumDpTxConfig enumDpTxConfig);
#endif

void ScalerDpTxVersionCheck(BYTE ucDpVersion);
void ScalerDpTxLinkRateCheck(BYTE ucDpTxLinkRate);
void ScalerDpTxStreamHandler(void);
void ScalerDpTxForceIdlePatternSetting(void);
void ScalerDpTxForceIdlePattern_EXINT0(void);
void ScalerDpTxSSTSetting(void);
void ScalerDpTxSSTMSASetting(void);
void ScalerDpTxConfigMstStreamLaneNum(void);
void ScalerDpTxStateChangeEvent(EnumDPTxModeStatus enumModeState);
void ScalerDpTxIntHandle_EXINT0(void);
void ScalerDpTxLinkTraining(void);
void ScalerDpTxTPInitialSet(void);
BYTE ScalerDpTxTrainPattern2(void);
void ScalerDpTxTrainPatternEnd(void);
void ScalerDpTxHPDProc(void);
void ScalerDpTxIRQEventCheck(void);
void ScalerDpTxSetStreamSource(EnumDPTxInputSource enumStreamSource);
void ScalerDpTxSetStreamSource_EXINT0(EnumDPTxInputSource enumStreamSource);
void ScalerDpTxAudioSetting(void);
bit ScalerDpTxAudioGetChannelChange(void);
WORD ScalerDpTxAudioGetSamplingFreqPacket(void);
void ScalerDpTxSetSecDataHeader(EnumDPTxSecDataPacketType enumPackettype);
void ScalerDpTxClearSecDataHeader(EnumDPTxSecDataPacketType enumPackettype);
BYTE ScalerDpTxAudioGetSecDataParity(BYTE ucHeader);
void ScalerDpTxAudioSetAudioInfoFrame(void);
void ScalerDpTxAudioMonitoringAudioInfoFrameChanged(void);
BYTE ScalerDpTxTrainPattern1(void);
bit ScalerDpTxTP1Lane0Adjust(void);
bit ScalerDpTxTP1Lane1Adjust(void);
bit ScalerDpTxTP1Lane2Adjust(void);
bit ScalerDpTxTP1Lane3Adjust(void);
void ScalerDpTxTP2Lane0Adjust(void);
void ScalerDpTxTP2Lane1Adjust(void);
void ScalerDpTxTP2Lane2Adjust(void);
void ScalerDpTxTP2Lane3Adjust(void);
void ScalerDpTxSignalReset(void);
void ScalerDpTxAuxPHYSet(BYTE ucMode);
void ScalerDpTxCloneOutputProc(BYTE ucInputPort, BYTE ucPortType, bit bClone);
void ScalerDpTxColorInfoSetting(void);
void ScalerDpTxInterlaceInfoSetting(BYTE ucInputPort, BYTE ucPortType);
#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
void ScalerDpTxCloneModeSwitch(bit bClone);
void ScalerDpTxBlockStatusCheck(void);
void ScalerDpTxBlockStatusSet(bit bEnable);
#endif
bit ScalerDpTxGetDownstreamHPDStatus(void);
void ScalerDpTxHDCPHandler(void);
void ScalerDpTxHDCPCheckDownstreamCapability(void);
bit ScalerDpTxHDCPAuth1Proc(void);
bit ScalerDpTxHDCPAuth1CheckBksv(void);
void ScalerDpTxHDCPAuth1GenAn(void);
void ScalerDpTxHDCPAuth1WriteAnAkey(void);
bit ScalerDpTxHDCPAuth1GenKm(void);
bit ScalerDpTxHDCPAuth1CompareR0(void);
bit ScalerDpTxHDCPAuth2Proc(void);
void ScalerDpTxHDCPAuth2WriteShaInput(void);
void ScalerDpTxHDCPAuth2ShaRun(bit bIsFirst);
bit ScalerDpTxHDCPCheckBinfo(void);
bit ScalerDpTxHDCPAuth2CompareV(void);
void ScalerDpTxHDCPChangeAuthState(EnumDPTxHDCPAuthState enumHDCPAuthState);
void ScalerDpTxHDCPTimeoutToReadR0Event(void);
void ScalerDpTxHDCPTimeoutForVReadyEvent(void);
void ScalerDpTxHDCPPollingVReadyEvent(void);
EnumDPTxTRQEventHDCPType ScalerDpTxHDCPPollingCpIrqType(void);
void ScalerDpTxHDCPEncryptSignalProc(bit bEnable);
void ScalerDpTxHDCPResetInfo(void);
#if(_DP_HDCP14_CTS_SUPPORT == _ON)
void ScalerDpTxHDCPResetKsvBackup(void);
bit ScalerDpTxHDCPDownstreamBksvChange(void);
#endif
#if(_DP_MST_SUPPORT == _ON)
bit ScalerDpTxGenConnectStatusNotifyMsgCheck(void);
bit ScalerDpTxSinkCountUpdate(void);
bit ScalerDpTxGetUpReqEnableStatusChange(void);
void ScalerDpTxUpdateDfpDeviceMsgCapFieldStatus(void);
#endif

void ScalerDpTxDownStreamEdidBwSetting(void);
WORD ScalerDpTxGetDownStreamEdidBw(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Tx Mode Judge
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxJudgeHandler(void)
{
    CLR_DP_TX_MODE_STATE_CHANGE();

    switch(GET_DP_TX_MODE_STATE())
    {
        case _DP_TX_MODE_STATUS_UNPLUG:

            if(GET_DP_TX_HPD_EVENT() == _DP_TX_HPD_PLUG_EVENT)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_INITIAL);
            }

            break;

        case _DP_TX_MODE_STATUS_INITIAL:

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
            {
                CLR_DP_TX_DOWNSTREAM_INFO_READY();
            }

            if(GET_DP_TX_DOWNSTREAM_INFO_READY() == _TRUE)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_TRAINING:

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
            {
                CLR_DP_TX_DOWNSTREAM_INFO_READY();
            }

            if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_ON);
            }

            // HPD short plug event && Link status fail
            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
                CLR_DP_TX_DOWNSTREAM_INFO_READY();
            }

            // For Link CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_ON:

            // HPD short plug event && Link status fail
            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
                CLR_DP_TX_DOWNSTREAM_INFO_READY();
            }

            // For Link CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            break;

        default:

            break;
    }

    if(GET_DP_TX_HPD_EVENT() == _DP_TX_HPD_UNPLUG_EVENT)
    {
        ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_UNPLUG);
    }

    if(GET_DP_TX_FORCE_LINK_TRAINING() == _TRUE)
    {
        CLR_DP_TX_FORCE_LINK_TRAINING();

        if((GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG) && (GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_INITIAL))
        {
            ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
        }
    }

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
    // Mode Status Change to Unplug For Contol Aux Communication When HPD Detection Disable
    if(GET_DP_TX_HPD_DETECTION_ENABLE() == _DISABLE)
    {
        if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG)
        {
            DebugMessageMst("8. Dp Tx State Change to Unplug For Contol Aux Communication", 1);

            ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_UNPLUG);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : DP Tx Mode Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxModeHandler(void)
{
    // Get Rx Cap if Rx Cap Changed IRQ Received
    if((GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG) && (GET_DP_TX_DOWNSTREAM_INFO_READY() == _FALSE))
    {
        // Get Downstream Link Configuration
        if(ScalerDpTxLinkConfig() == _TRUE)
        {
            SET_DP_TX_DOWNSTREAM_INFO_READY();
        }
    }

#if(_DP_MST_SUPPORT == _ON)

    if(g_enumDpMSTCapablePort != _DP_MST_NO_PORT)
    {
        if(ScalerDpTxGenConnectStatusNotifyMsgCheck() == _TRUE)
        {
            CLR_DP_RX_SELF_GEN_UP_REQUEST_RETRY();

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                // Set 1s to Notify as to avoid DownRequest MSG traffic things
                ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_TX_CABLE_STATUS_CHANGE_EVENT);
            }
            else
            {
                // Clear Up_Req Bypass MSG Back Up
                CLR_DP_TX_UP_REQUEST_BACKUP_DATA();

                CLR_DP_TX_BYPASS_UNPLUG_CSN_IS_PENDING();

                // Clear Up Req Msg Header
                CLR_DP_TX_UP_REQUEST_MSG_HEADER();

                // Align Reported Cable Status with Tx Cable Status
                SET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS());

                // Backup unplug event to avoid source missing the CSN and causing additional monitor to be recognized
                SET_DP_RX_REPORT_DOWNSTREAM_UNPLUG_EVENT();

                // Initiate Connection Status Notify
                SET_DP_GEN_UP_REQUEST_MSG(_DP_MSG_CONNECTION_STATUS_NOTIFY);
            }

            CLR_DP_TX_UP_REQUEST_BYPASS_REGEN();
        }

        if(GET_DP_RX_SELF_GEN_UP_REQUEST_RETRY() == _DP_MSG_CONNECTION_STATUS_NOTIFY)
        {
            CLR_DP_RX_SELF_GEN_UP_REQUEST_RETRY();

            ScalerTimerActiveTimerEvent(SEC(2), _SCALER_TIMER_EVENT_DP_TX_CABLE_STATUS_CHANGE_EVENT);
        }
    }

    if(ScalerDpTxGetUpReqEnableStatusChange() == _TRUE)
    {
        ScalerDpTxUpdateDfpDeviceMsgCapFieldStatus();
    }
#endif

    switch(GET_DP_TX_MODE_STATE())
    {
        case _DP_TX_MODE_STATUS_UNPLUG:

            if(GET_DP_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                // Power Down ML PHY
                ScalerGDIPhyTxMLPowerOff();

                // Reset Daisy Chian ST3 ~ ST5
                SET_REG_DP_RX_DAIZY_ST3_START(0x00);
                SET_REG_DP_RX_DAIZY_ST3_END(0x00);
                SET_REG_DP_RX_DAIZY_ST4_START(0x00);
                SET_REG_DP_RX_DAIZY_ST4_END(0x00);
                SET_REG_DP_RX_DAIZY_ST5_START(0x00);
                SET_REG_DP_RX_DAIZY_ST5_END(0x00);

                // Reset TX Buffer Status
                SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

                // Update Total Received Count
                if((GET_DP_TOTAL_RECEIVED_MSG_COUNT() >= GET_DP_TX_RECEIVED_MSG_COUNT()) && (GET_DP_TX_RECEIVED_MSG_COUNT() > 0))
                {
                    SET_DP_TOTAL_RECEIVED_MSG_COUNT(GET_DP_TOTAL_RECEIVED_MSG_COUNT() - GET_DP_TX_RECEIVED_MSG_COUNT());
                }
                else
                {
                    SET_DP_TOTAL_RECEIVED_MSG_COUNT(0);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
                }

                // Reset Tx Received Count
                SET_DP_TX_RECEIVED_MSG_COUNT(0);

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_MSG_COUNT_RESET_EVENT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_CABLE_STATUS_CHANGE_EVENT);

                SET_DP_TX_DOWNSTREAM_DPPLUG_STATUS(_DP_UNPLUG);
                SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_NO_DEVICE);
                SET_DP_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_MSG_NO_SUPPORT);

                SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
                CLR_DP_TX_DOWNSTREAM_TP3_SUPPORT();

                CLR_DP_TX_DOWNSTREAM_INFO_READY();
                CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
                CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER();
                CLR_DP_TX_HDCP_AUTH_START();
                CLR_DP_TX_HDCP_AUTH_HOLD();

                // CLR TX Read Buffer Status
                SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

                CLR_DP_TX_DOWN_REPLY_READ_DISABLE();

                SET_DP_TX_DOWNSTREAM_SINK_COUNT(0x00);

                SET_DP_TX_DOWNSTREAM_SINK_COUNT_CHANGE();

#if(_DP_MST_SUPPORT == _ON)
                CLR_DP_TX_UP_REQUEST_BYPASS_REGEN();

                // Clear Up_Req Bypass MSG Back Up
                CLR_DP_TX_UP_REQUEST_BACKUP_DATA();

                // Clear Up Req Msg Header
                CLR_DP_TX_UP_REQUEST_MSG_HEADER();

                CLR_DP_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE();
#endif
                CLR_DP_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();
            }

            break;

        case _DP_TX_MODE_STATUS_INITIAL:

            if(GET_DP_TX_DOWNSTREAM_INFO_READY() == _TRUE)
            {
#if(_DP_MST_SUPPORT == _ON)
                // Reset MST Related Status
                SET_DP_TX_LINK_PBN_PER_TIMESOLT(0);

                // Clear All ST3 ~ ST5 Time Slot
                for(pData[0] = 0; pData[0] < 3; pData[0]++)
                {
                    // CLR Daisy Chain Timeslot
                    ScalerSetBit((GET_DP_TX_STX_START_ADDRESS(pData[0] + 2)), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    ScalerSetBit((GET_DP_TX_STX_END_ADDRESS(pData[0] + 2)), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                }

#endif  // End of #if(_DP_MST_SUPPORT == _ON)

                SET_DP_TX_DOWNSTREAM_DPPLUG_STATUS(_DP_PLUG);
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_TRAINING:

            if(GET_DP_TX_DOWNSTREAM_INFO_READY() == _TRUE)
            {
                ScalerDpTxLinkTraining();
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_ON:

            if(GET_DP_TX_MODE_STATE_CHANGE() == _TRUE)
            {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                {
                    if(GET_DP_TX_HDCP2_AUTH_START() == _FALSE)
                    {
                        SET_DP_TX_HDCP2_DOWNSTREAM_EVENT(_DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_REAUTH);
                    }
                }
                else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#else
                if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
#endif
                {
#if(_DP_HDCP14_CTS_SUPPORT == _ON)
                    if(ScalerSyncDpHdcpDownstreamReAuthCheck() == _TRUE)
                    {
                        if(ScalerDpTxHDCPDownstreamBksvChange() == _FALSE)
                        {
                            SET_DP_TX_HDCP_AUTH_START();
                        }
                        else
                        {
                            SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH);
                        }
                    }
#else
                    if(GET_DP_TX_HDCP_AUTH_START() == _FALSE)
                    {
                        SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH);
                    }
#endif
                }
            }

            ScalerDpTxStreamHandler();

#if(_DP_MST_SUPPORT == _ON)

            if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST) || (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST))
            {
                // ScalerDpTxMonitorDownstreamBW();
            }
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxInitial(void)
{
    // Setting Aux
    ScalerDpTxAuxPHYSet(_DP_TX_AUX_DIFF_MODE);

    // For HDCP Auth
    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);

    // Set ECF by FW mode
    ScalerSetBit(PBB_64_HDCP_ECF_BYTE0, ~_BIT7, 0x00);

    // Set Aux Timeout
    ScalerSetByte(PBD_A1_AUX_TIMEOUT, 0x95);

    // Power Down ML PHY
    ScalerGDIPhyTxMLPowerOff();

    // Power CMU PHY
    ScalerGDIPhyTxCMUPowerOff();

    // Power On Aux CH
    ScalerSetBit(PBD_A0_AUX_TX_CTRL, ~_BIT0, _BIT0);

    // Sync end Pattern Error Handle Disable
    ScalerSetBit(PBD_F6_AUX_DIG_PHY8, ~_BIT1, _BIT1);

    SET_DP_TX_HPD_FIRST_PLUG();

    // Set HPD 1ms Timer to  2ms
    ScalerSetBit(PBB_73_HPD_TIMER1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
    ScalerSetByte(PBB_75_HPD_TIMER3, 0x2C);

    // Set HPD 10ms Timer to  2ms
    ScalerSetByte(PBB_78_HPD_TIMER6, 0x0D);
    ScalerSetByte(PBB_79_HPD_TIMER7, 0x2C);

    // Enable HPD Detection
    ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, _BIT7);

    // Clear HPD IRQ Flag
    ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);

    // Clear IRQ HPD Type Flag
    CLR_DP_TX_IRQ_HPD_TYPE();
    CLR_DP_TX_IRQ_HPD_TYPE_INT();
    CLR_DP_TX_IRQ_HPD_DETECTED();
    CLR_DP_TX_IRQ_HDCP_TYPE();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    CLR_DP_TX_HDCP2_IRQ_TYPE();
#endif

    // Enable Short IRQ and Disable Long IRQ
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~(_BIT6 | _BIT5), _BIT6);

    // Set Initial HPD Status
    SET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS(GET_DP_TX_HPD_DEBOUNCE_LEVEL());

#if(_DP_MST_SUPPORT == _ON)

    CLR_DP_TX_UP_REQUEST_BYPASS_REGEN();

    // Clear Up_Req Bypass MSG Back Up
    CLR_DP_TX_UP_REQUEST_BACKUP_DATA();

    // Clear Up Req Msg Header
    CLR_DP_TX_UP_REQUEST_MSG_HEADER();

    // HW will auto calculate Start and End
    SET_REG_DP_TX_DOWNSTREAM_MSG_AUTO_MODE();

    // Set TX MSG Aux Write Burst Length 16bytes
    SET_REG_DP_TX_DOWNSTREAM_MSG_BURST_LENGTH(_DP_TX_AUX_WRITE_BURST_LENGTH);

    // Enable Only Read One SBMSG
    ScalerSetBit(PBD_CA_AUX_TX_MSG_RD_CTRL, ~_BIT5, _BIT5);

    // Set TX MSG Aux Read Burst Length 16bytes
    SET_REG_DP_TX_UPSTREAM_MSG_READ_BURST_LENGTH(_DP_TX_AUX_READ_BURST_LENGTH);

    // Enable DP Tx Link Clock
    ScalerDpTxMstLinkClockEn(_ENABLE);

    // Mst Port Select
    ScalerDpRxMstPortSel();
#endif

    ScalerDpTxInitialReset();

    // Enable Arbiter Stuffing and Framing
    ScalerSetBit(PBB_C9_ARBITER_CTRL, ~_BIT0, _BIT0);

    // Clear HDCP Flag
    CLR_DP_TX_HDCP_AUTH_START();
    CLR_DP_TX_HDCP_AUTH_HOLD();

    // Clear Audio Flag
    CLR_DP_TX_AUDIO_READY_TO_PLAY();
    CLR_DP_TX_CURRENT_AUDIO_FREQUENCY();

    // Clear Link CTS Request Type
    CLR_DP_TX_CTS_TEST_REQUEST_TYPE();

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
    SET_DP_RX_CAPABILITY_SWITCHED();
#endif
}

//--------------------------------------------------
// Description  : Dp Tx Read DPCD Rx Capability
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxLinkConfig(void)
{
    BYTE pucData[16];

    memset(pucData, 0, sizeof(pucData));

    // Set Power Normal
    pucData[0] = 0x01;
    if(ScalerDpTxAuxNativeWrite(0x00, 0x06, 0x00, 1, pucData) == _FALSE)
    {
        return _FALSE;
    }

    ScalerTimerDelayXms(10);

    // Read Sink Power Status
    if(ScalerDpTxAuxNativeRead(0x00, 0x06, 0x00, 1, pucData) == _FALSE)
    {
        return _FALSE;
    }

    // Check if Power State is Normal
    if((pucData[0] & 0x07) != 0x01)
    {
        return _FALSE;
    }

    // Write OUI interactive
    pucData[0] = 0x4C;
    pucData[1] = 0xE0;
    pucData[2] = 0x00;
    if(ScalerDpTxAuxNativeWrite(0x00, 0x03, 0x00, 3, pucData) == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpTxAuxNativeRead(0x00, 0x00, 0x00, 16, pucData) == _FALSE)
    {
        return _FALSE;
    }

    if((pucData[14] & _BIT7) == _BIT7)
    {
        DebugMessageMst("Dp Tx Donwstream Caps. Extended Field Support", pucData[14]);

        if(ScalerDpTxAuxNativeRead(0x00, 0x22, 0x00, 16, pucData) == _FALSE)
        {
            return _FALSE;
        }

        // If 02200h = 0x00 try again to read capability
        if(pucData[0] == 0x00)
        {
            ScalerTimerDelayXms(2);

            if(ScalerDpTxAuxNativeRead(0x00, 0x22, 0x00, 16, pucData) == _FALSE)
            {
                return _FALSE;
            }
        }

        if(pucData[0] == 0x00)
        {
            ScalerTimerDelayXms(2);

            if(ScalerDpTxAuxNativeRead(0x00, 0x00, 0x00, 16, pucData) == _FALSE)
            {
                return _FALSE;
            }
        }
    }

    DebugMessageMst("DPTX Donwstream Caps. 0", pucData[0]);
    DebugMessageMst("DPTX Donwstream Caps. 1", pucData[1]);
    DebugMessageMst("DPTX Donwstream Caps. 2", pucData[2]);
    DebugMessageMst("DPTX Donwstream Caps. 3", pucData[3]);
    DebugMessageMst("DPTX Donwstream Caps. 4", pucData[4]);

    // Step1:Get DownStream infromation
    ScalerDpTxVersionCheck(pucData[0]);

#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
    // Set DP Tx Link Config by User
    ScalerDpTxLinkConfigAdjust(GET_DP_TX_CONFIG_SETTING());
#endif

    if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
    {
        // Disable Downstream MST Mode
        pucData[10] = 0x00;

        SET_DP_TX_DPCD_111(&pucData[10]);

        // Check TPS3 support
        if((pucData[2] & _BIT6) == _BIT6)
        {
            SET_DP_TX_DOWNSTREAM_TP3_SUPPORT();
        }
        else
        {
            CLR_DP_TX_DOWNSTREAM_TP3_SUPPORT();
        }

        if(ScalerDpTxAuxNativeRead(0x00, 0x00, 0x21, 1, (pucData + 10)) == _FALSE)
        {
            return _FALSE;
        }

        // MST_CAP = 1
        if((pucData[10] & _BIT0) == _BIT0)
        {
            // Set link Address Reply information
            SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_MST_OR_SST_BRANCH_DOWNSTREAM);
            SET_DP_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_MSG_SUPPORT);
            SET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);

            if(g_enumDpMSTCapablePort != _DP_MST_NO_PORT)
            {
                // Modify Downstream MST Mode
                pucData[10] = (GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1);

                SET_DP_TX_DPCD_111(&pucData[10]);
            }
        }
        else // MST_CAP = 0
        {
            SET_DP_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_MSG_NO_SUPPORT);

            if((pucData[4] & _BIT0) == 1)
            {
                SET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP(1);

                SET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK(1);
            }
            else
            {
                SET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP(0);

                SET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK(0);
            }

            if((pucData[5] & _BIT0) == 1)
            {
                // Link CTS 4.2.2.7 start
                if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0x00, 1, (pucData + 11)) == _FALSE)
                {
                    return _FALSE;
                }
                // Link CTS 4.2.2.7 end

                if((pucData[5] & 0x06) == _DP_TYPE) // MST Device with Branching Unit
                {
                    SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_MST_OR_SST_BRANCH_DOWNSTREAM);
                    SET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);
                }
                else // SST Legacy Converter Device
                {
                    SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_TO_LEGACY);
                    SET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_PLUG);
                }
            }
            else // SST Sink Device
            {
                SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_SST_SINK);
                SET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);
            }
        }
    }
    else // DPCD Revision 1.0/1.1
    {
        SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_SST_SINK);
        SET_DP_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_MSG_NO_SUPPORT);
        SET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);
    }

#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
    // Set DP Tx Link Config by User
    if(GET_DP_TX_CONFIG_SETTING() == _DP_TX_CONFIG_NONE)
#endif
    {
        // Step2:Get link Rate
        ScalerDpTxLinkRateCheck(pucData[1]);

        SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM((pucData[2] & 0x1F));
    }

    SET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING((bit)(pucData[2] & _BIT7));

    // Check Sink SSC Capability
#if(_DP_TX_SSC_SUPPORT == _ON)
    SET_DP_TX_DOWNSTREAM_DOWN_SPREAD((bit)(pucData[3] & _BIT0));
#else
    SET_DP_TX_DOWNSTREAM_DOWN_SPREAD(_DISABLE);
#endif

    // Check DownStream Detaile Capability Info for CTS 4.2.2.7
    if(ScalerDpTxAuxNativeRead(0x00, 0x00, 0x80, 16, pucData) == _FALSE)
    {
        return _FALSE;
    }

#if(_DP_MST_SUPPORT == _ON)
    if(ScalerDpTxSinkCountUpdate() == _FALSE)
    {
        DebugMessageMst("Tx Sink Count Update Fail", 0);

        return _FALSE;
    }
#endif

    ScalerDpTxHDCPCheckDownstreamCapability();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpTxHdcp2CheckCapability();
#endif

    ScalerDpTxDownStreamEdidBwSetting();

    return _TRUE;
}

#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Tx Link Config by User
// Input Value  : enumDpTxConfig
// Output Value :
//--------------------------------------------------
void ScalerDpTxLinkConfigAdjust(EnumDpTxConfig enumDpTxConfig)
{
    switch(enumDpTxConfig)
    {
        case _DP_TX_V11_1LANE_RBR:

            SET_DP_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_ONE_LANE);
            SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_RBR);

            break;

        case _DP_TX_V11_2LANE_RBR:

            SET_DP_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_TWO_LANE);
            SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_RBR);

            break;

        case _DP_TX_V11_4LANE_RBR:

            SET_DP_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_FOUR_LANE);
            SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_RBR);

            break;

        case _DP_TX_V11_1LANE_HBR:

            SET_DP_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_ONE_LANE);
            SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR);

            break;

        case _DP_TX_V11_2LANE_HBR:

            SET_DP_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_TWO_LANE);
            SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR);

            break;

        case _DP_TX_V11_4LANE_HBR:

            SET_DP_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_1);
            SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_FOUR_LANE);
            SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR);

            break;

        case _DP_TX_V12_1LANE_HBR2:

            SET_DP_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_2);
            SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_ONE_LANE);
            SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR2);

            break;

        case _DP_TX_V12_2LANE_HBR2:

            SET_DP_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_2);
            SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_TWO_LANE);
            SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR2);

            break;

        case _DP_TX_V12_4LANE_HBR2:

            SET_DP_TX_DOWNSTREAM_DPCD_REV(_DP_VERSION_1_2);
            SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM(_DP_FOUR_LANE);
            SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR2);

            break;

        case _DP_TX_CONFIG_NONE:
        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Handle Tx Dp Version
// Input Value  : DPCD 00000h
// Output Value : None
//--------------------------------------------------
void ScalerDpTxVersionCheck(BYTE ucDpVersion)
{
    if(ucDpVersion < _DP_VERSION_1_0)
    {
        ucDpVersion = _DP_VERSION_1_1;
    }
    else
    {
        ucDpVersion = ucDpVersion;
    }

    SET_DP_TX_DOWNSTREAM_DPCD_REV(ucDpVersion);
}

//--------------------------------------------------
// Description  : Handle Tx Link Rate
// Input Value  : DPCD 00001h
// Output Value : None
//--------------------------------------------------
void ScalerDpTxLinkRateCheck(BYTE ucDpTxLinkRate)
{
    BYTE ucDpSpecLinkRate = _DP_LINK_RBR;

    if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_3)
    {
        ucDpSpecLinkRate = _DP_LINK_HBR3;
    }
    else if(GET_DP_TX_DOWNSTREAM_DPCD_REV() == _DP_VERSION_1_2)
    {
        ucDpSpecLinkRate = _DP_LINK_HBR2;
    }
    else
    {
        ucDpSpecLinkRate = _DP_LINK_HBR;
    }

    if(ucDpTxLinkRate > ucDpSpecLinkRate)
    {
        if(_HW_DP_TX_MAX_LINK_RATE_SUPPORT > ucDpSpecLinkRate)
        {
            ucDpTxLinkRate = ucDpSpecLinkRate;
        }
        else
        {
            ucDpTxLinkRate = _HW_DP_TX_MAX_LINK_RATE_SUPPORT;
        }
    }
    else
    {
        if(ucDpTxLinkRate > _HW_DP_TX_MAX_LINK_RATE_SUPPORT)
        {
            ucDpTxLinkRate = _HW_DP_TX_MAX_LINK_RATE_SUPPORT;
        }
        else
        {
            ucDpTxLinkRate = ucDpTxLinkRate;
        }
    }

    SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(ucDpTxLinkRate);
}

//--------------------------------------------------
// Description  : Handle Tx Output stream
// Input Value  : DP Tx Input Source
// Output Value : None
//--------------------------------------------------
void ScalerDpTxStreamHandler(void)
{
    if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST) && (GET_REG_DP_RX_MST_ENABLE() == _FALSE))
    {
        ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);
    }

    if(GET_DP_TX_STREAM_SOURCE_CHANGE() == _TRUE)
    {
        CLR_DP_TX_STREAM_SOURCE_CHANGE();

        switch(GET_DP_TX_STREAM_SOURCE())
        {
            case _DP_TX_SOURCE_NONE:

                if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _TRUE)
                {
                    ScalerDpTxHDCPEncryptSignalProc(_DISABLE);

                    ScalerTimerDelayXms(2);
                }

                if((GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) && (GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2))
                {
                    ScalerDpTxAuxNativeRead(0x00, 0x01, 0x11, 1, pData);

                    if((pData[0] & _BIT0) == _BIT0)
                    {
                        pData[0] &= ~_BIT0;

                        SET_DP_TX_DPCD_111(pData);
                    }
                }

                // Disable Audio
                ScalerDpTxSSTAudioPlaySetting(_DP_TX_AUDIO_OFF);

                // Main Link switch to IDLE Pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_IDLE_PATTERN << 4));

                // Direct Apply Idle Pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

                // Phy Input Data from Tx Mac (SST)
                ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);

                break;

            case _DP_TX_SOURCE_MST:

                // Disable Audio
                ScalerDpTxSSTAudioPlaySetting(_DP_TX_AUDIO_OFF);

#if(_DP_FREESYNC_SUPPORT == _ON)
                ScalerDpTxSSTSetAmdSpdInfo(_OFF);
#endif

                // Enable Downstream MST Mode
                pData[0] = ((GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1) | _BIT0);

                SET_DP_TX_DPCD_111(pData);

                // Switch MST Daisy Chain From Rx0 or Rx1
                ScalerSetBit(PBB_D9_DPTX_TOP_CTL, ~_BIT0, ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? 0x00 : _BIT0));

                // Phy Input Data from Daizy chain (MST)
                ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, _BIT1);

                break;

            case _DP_TX_SOURCE_MST2SST:

                // Switch MST Daisy Chain From Rx0 or Rx1 for MST to SST Audio
                ScalerSetBit(PBB_D9_DPTX_TOP_CTL, ~_BIT0, ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? 0x00 : _BIT0));

                // Setting DP TX MAC
                ScalerDpTxSSTSetting();

                // Main Link switch to VIDEO pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_VIDEO_PATTERN << 4));

                // Double buffer only by Vsync
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);

                // Phy Input Data from Tx Mac (SST)
                ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);

                break;

            case _DP_TX_SOURCE_CLONE:

                // Setting DP TX MAC
                ScalerDpTxSSTSetting();

                // Main Link switch to VIDEO pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_VIDEO_PATTERN << 4));

                // Double buffer only by Vsync
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);

                // Phy Input Data from Tx Mac (SST)
                ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);

                break;

            default:
                break;
        }
    }

    // Play audio if get audio packet or replay audio if channel count is changed
    if((GET_DP_TX_AUDIO_READY_TO_PLAY() == _TRUE) && ((ScalerDpTxAudioGetSamplingFreqRange() != GET_DP_TX_CURRENT_AUDIO_FREQUENCY()) || (ScalerDpTxAudioGetChannelChange() == _TRUE)))
    {
        if(ScalerDpTxAudioGetSamplingFreqRange() != _DP_TX_AUDIO_FREQ_NO_AUDIO)
        {
            ScalerDpTxSSTAudioPlaySetting(_DP_TX_AUDIO_ON);
        }
        else
        {
            ScalerDpTxSSTAudioPlaySetting(_DP_TX_AUDIO_STANDBY);
        }

        SET_DP_TX_CURRENT_AUDIO_FREQUENCY(ScalerDpTxAudioGetSamplingFreqRange());
    }

    if(GET_DP_TX_AUDIO_INFOFRAME_SEND_STATUS() == _TRUE)
    {
        ScalerDpTxAudioMonitoringAudioInfoFrameChanged();
    }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpTxHdcp2OutputContentStreamHandler();
#endif
}
//--------------------------------------------------
// Description  : Handle Tx Output stream
// Input Value  : DP Tx Input Source
// Output Value : None
//--------------------------------------------------
void ScalerDpTxForceIdlePatternSetting(void)
{
    if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
    {
        if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _TRUE)
        {
            ScalerDpTxHDCPEncryptSignalProc(_DISABLE);

            ScalerTimerDelayXms(2);
        }

        if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
        {
            pData[0] = (GET_DP_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS() << 1);

            SET_DP_TX_DPCD_111(pData);
        }

        // Disable Audio
        ScalerDpTxSSTAudioPlaySetting(_DP_TX_AUDIO_OFF);

        // Main Link switch to IDLE Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_IDLE_PATTERN << 4));

        // Direct Apply Idle Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

        // Phy Input Data from Tx Mac (SST)
        ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);

        if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE)
        {
            ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

            CLR_DP_TX_STREAM_SOURCE_CHANGE();
        }
    }
}

//--------------------------------------------------
// Description  : Handle Tx Output stream for EXINT
// Input Value  : DP Tx Input Source
// Output Value : None
//--------------------------------------------------
void ScalerDpTxForceIdlePattern_EXINT0(void) using 1
{
    // Main Link switch to IDLE Pattern
    ScalerSetBit_EXINT(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_IDLE_PATTERN << 4));

    // Direct Apply Idle Pattern
    ScalerSetBit_EXINT(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

    // Phy Input Data from Tx Mac (SST)
    ScalerSetBit_EXINT(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);

    if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE)
    {
        ScalerDpTxSetStreamSource_EXINT0(_DP_TX_SOURCE_NONE);
    }
}

//--------------------------------------------------
// Description  : DP Tx MAC Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxSSTSetting(void)
{
    bit bMvidHWMode = _TRUE;
    BYTE ucCnt = 0;
    BYTE ucValidHwMvidMeaCnt = 0;
    WORD usLoopCnt = 0;
    WORD usMeasureTime = 0;
    DWORD ulHwMvidMin = 0xFFFFFFFF;
    DWORD ulHwMvidMax = 0x00000000;
    PDATA_DWORD(0) = 0;
    PDATA_DWORD(1) = 0x8000;
    PDATA_DWORD(2) = 0;
    PDATA_DWORD(3) = 0;

    // Mvid = Stream clk x Nvid / Link clk
    PDATA_DWORD(0) = (DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * PDATA_DWORD(1);
    PDATA_DWORD(0) /= ((GET_DP_TX_DOWNSTREAM_DOWN_SPREAD() == _ENABLE) ? (27UL * (DWORD)GET_DP_TX_DOWNSTREAM_LINK_RATE() * 9975UL / 10000UL) : (27UL * (DWORD)GET_DP_TX_DOWNSTREAM_LINK_RATE()));

    PDATA_DWORD(0) = PDATA_DWORD(0) / 10 + (PDATA_DWORD(0) % 10 > 5 ? 1 : 0);

    // Calculate HW measure Mvid period time, / 5 for get 5us times
    usMeasureTime = (WORD)(PDATA_DWORD(1) / ((GET_DP_TX_DOWNSTREAM_DOWN_SPREAD() == _ENABLE) ? (27UL * GET_DP_TX_DOWNSTREAM_LINK_RATE() * 9975UL / 10000UL) : (27UL * (DWORD)GET_DP_TX_DOWNSTREAM_LINK_RATE())) / 5UL);
    usMeasureTime *= 2;

    // Debounce 10 times
    ucCnt = 0x0A;

    do
    {
        --ucCnt;

        // Enable HW Mvid measure
        ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~_BIT7, _BIT7);

        // Delay time for one HW mvid measurement period time
        for(usLoopCnt = 0; usLoopCnt < usMeasureTime; usLoopCnt++)
        {
            DELAY_5US();
        }

        // Disable HW Mvid measure
        ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~_BIT7, 0x00);

        PDATA_DWORD(2) = (((DWORD)ScalerGetByte(PBB_AF_MVID_AUTO_H) << 16) | ((DWORD)ScalerGetByte(PBB_B0_MVID_AUTO_M) << 8) | ScalerGetByte(PBB_B1_MVID_AUTO_L));

        // For RLE0779A/RL6449A disable auto Mvid is zero
        if(PDATA_DWORD(2) == 0)
        {
            // HW Auto Mvid is wrong Set Mvid for FW mode
            ScalerSetByte(PBB_A9_MN_M_VID_H, pData[1]);
            ScalerSetByte(PBB_AA_MN_M_VID_M, pData[2]);
            ScalerSetByte(PBB_AB_MN_M_VID_L, pData[3]);

            bMvidHWMode = _FALSE;

            break;
        }

        // (abs(PDATA_DWORD(0) - PDATA_DWORD(2)) > (PDATA_DWORD(0) >> 2)) for HW measure abnormal
        if(abs(PDATA_DWORD(0) - PDATA_DWORD(2)) > (PDATA_DWORD(0) >> 2))
        {
            // Drop this time measure result
            continue;
        }

        // (PDATA_DWORD(3) != 0) for get the first time measurement result
        if(PDATA_DWORD(3) == 0)
        {
            if(PDATA_DWORD(2) < ulHwMvidMin)
            {
                ulHwMvidMin = PDATA_DWORD(2);
            }

            if(PDATA_DWORD(2) > ulHwMvidMax)
            {
                ulHwMvidMax = PDATA_DWORD(2);
            }

            PDATA_DWORD(3) = PDATA_DWORD(2);

            // Record total valid hw measure times
            ucValidHwMvidMeaCnt++;

            continue;
        }

        // (abs(PDATA_DWORD(2) - PDATA_DWORD(3)) < 0x50) for avoid get the measurement value far away from the average value
        if(abs(((PDATA_DWORD(3) + (ucValidHwMvidMeaCnt / 2)) / ucValidHwMvidMeaCnt) - PDATA_DWORD(2)) < 0x50)
        {
            if(PDATA_DWORD(2) < ulHwMvidMin)
            {
                ulHwMvidMin = PDATA_DWORD(2);
            }

            if(PDATA_DWORD(2) > ulHwMvidMax)
            {
                ulHwMvidMax = PDATA_DWORD(2);
            }

            // Accumulate every hw measure mvid
            PDATA_DWORD(3) += PDATA_DWORD(2);

            // Record total valid hw measure times
            ucValidHwMvidMeaCnt++;
        }
    }
    while(ucCnt > 0);

    if(bMvidHWMode == _TRUE)
    {
        // Drop the min and max value of hw mvid measurement result
        if(ucValidHwMvidMeaCnt > 2)
        {
            PDATA_DWORD(3) -= (ulHwMvidMax + ulHwMvidMin);
            ucValidHwMvidMeaCnt -= 2;

            // Calculate the hw mvid average value
            PDATA_DWORD(3) = ((PDATA_DWORD(3) + (ucValidHwMvidMeaCnt / 2)) / ucValidHwMvidMeaCnt);

            if(abs(PDATA_DWORD(0) - PDATA_DWORD(3)) > (PDATA_DWORD(0) >> 1))
            {
                // HW Auto Mvid is wrong Set Mvid for FW mode
                PDATA_DWORD(3) = PDATA_DWORD(0);
            }
        }
        else
        {
            // HW Auto Mvid is wrong Set Mvid for FW mode
            PDATA_DWORD(3) = PDATA_DWORD(0);
        }

        // Set Mvid value
        ScalerSetByte(PBB_A9_MN_M_VID_H, pData[13]);
        ScalerSetByte(PBB_AA_MN_M_VID_M, pData[14]);
        ScalerSetByte(PBB_AB_MN_M_VID_L, pData[15]);
    }

    // Set Nvid for FW mode
    ScalerSetByte(PBB_AC_MN_N_VID_H, pData[5]);
    ScalerSetByte(PBB_AD_MN_N_VID_M, pData[6]);
    ScalerSetByte(PBB_AE_MN_N_VID_L, pData[7]);

    // Set Mvid DB Direct Effective
    ScalerSetBit(PBB_B4_MSA_CTRL, ~_BIT6, 0x00);

    // Set Mvid DB for FW mode
    ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6), _BIT6);

    // For Mvid Auto New Mode, M/N mode Measure and Generate are Independant.
    // SET_DP_TX_MVID_FW_MODE -> FW Manually Set Mvid/Nvid
    SET_DP_TX_MVID_FW_MODE();

    // MSA fill
    ScalerDpTxSSTMSASetting();

    // DP Tx TU Setting
    ScalerDpTxSSTDisplayFormatSetting();

    // Set up Audio Output
    ScalerDpTxSSTAudioPlaySetting(_DP_TX_AUDIO_PRESET);
}

//--------------------------------------------------
// Description  : DP Tx MSA Generation
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxSSTMSASetting(void)
{
    // Reset MSA Generation Block and SEC Block
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT6, 0x00);

    // Set Htotal
    ScalerSetByte(PBB_B7_MN_STRM_ATTR_HTT_M, HIBYTE(g_stDPTxInputTimingInfo.usHTotal));
    ScalerSetByte(PBB_B8_MN_STRM_ATTR_HTT_L, LOBYTE(g_stDPTxInputTimingInfo.usHTotal));

    // Set Hstart
    ScalerSetByte(PBB_B9_MN_STRM_ATTR_HST_M, HIBYTE(g_stDPTxInputTimingInfo.usHStart));
    ScalerSetByte(PBB_BA_MN_STRM_ATTR_HST_L, LOBYTE(g_stDPTxInputTimingInfo.usHStart));

    // Set Hwidth
    ScalerSetByte(PBB_BB_MN_STRM_ATTR_HWD_M, HIBYTE(g_stDPTxInputTimingInfo.usHWidth));
    ScalerSetByte(PBB_BC_MN_STRM_ATTR_HWD_L, LOBYTE(g_stDPTxInputTimingInfo.usHWidth));

    // Set Hsyc and Polarity
    pData[0] = ((HIBYTE(g_stDPTxInputTimingInfo.usHSWidth) & 0x7F) | ((BYTE)g_stDPTxInputTimingInfo.b1HSP << 7));

    // Set Hsyc and Polarity
    ScalerSetByte(PBB_BD_MN_STRM_ATTR_HSW_M, pData[0]);
    ScalerSetByte(PBB_BE_MN_STRM_ATTR_HSW_L, LOBYTE(g_stDPTxInputTimingInfo.usHSWidth));

    // Set Vtotal
    ScalerSetByte(PBB_BF_MN_STRM_ATTR_VTTE_M, HIBYTE(g_stDPTxInputTimingInfo.usVTotal));
    ScalerSetByte(PBB_C0_MN_STRM_ATTR_VTTE_L, LOBYTE(g_stDPTxInputTimingInfo.usVTotal));

    // Set VStart
    ScalerSetByte(PBB_C1_MN_STRM_ATTR_VST_M, HIBYTE(g_stDPTxInputTimingInfo.usVStart));
    ScalerSetByte(PBB_C2_MN_STRM_ATTR_VST_L, LOBYTE(g_stDPTxInputTimingInfo.usVStart));

    // Set VHeight
    ScalerSetByte(PBB_C3_MN_STRM_ATTR_VHT_M, HIBYTE(g_stDPTxInputTimingInfo.usVHeight));
    ScalerSetByte(PBB_C4_MN_STRM_ATTR_VHT_L, LOBYTE(g_stDPTxInputTimingInfo.usVHeight));

    // Set Vsyc and Polarity
    pData[0] = ((HIBYTE(g_stDPTxInputTimingInfo.usVSWidth) & 0x7F) | ((BYTE)g_stDPTxInputTimingInfo.b1VSP << 7));

    // Set Vsyc and Polarity
    ScalerSetByte(PBB_C5_MN_STRM_ATTR_VSW_M, pData[0]);
    ScalerSetByte(PBB_C6_MN_STRM_ATTR_VSW_L, LOBYTE(g_stDPTxInputTimingInfo.usVSWidth));

    // Set color depth
    SET_DP_TX_MSA_COLOR_DEPTH(GET_DP_TX_INPUT_COLOR_DEPTH());

    // Set Color Space & Colorimetry
    switch(GET_DP_TX_INPUT_COLOR_SPACE())
    {
        case _COLOR_SPACE_RGB:
        default:

            switch(GET_DP_TX_INPUT_COLORIMETRY())
            {
                case _COLORIMETRY_RGB_SRGB:
                default:

                    if(GET_DP_TX_RGB_QUANTIZATION_RANGE() == _RGB_QUANTIZATION_FULL_RANGE)
                    {
                        SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_SRGB_VESA);
                    }
                    else
                    {
                        SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_SRGB_CEA);
                    }

                    break;

                case _COLORIMETRY_RGB_XRRGB:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_XRRGB);
                    break;

                case _COLORIMETRY_RGB_SCRGB:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_SCRGB);
                    break;

                case _COLORIMETRY_RGB_ADOBERGB:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_ADOBERGB);
                    break;

                case _COLORIMETRY_RGB_DCI_P3:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_DCI_P3);
                    break;

                case _COLORIMETRY_RGB_COLOR_PROFILE:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_COLOR_PROFILE);
                    break;

                case _COLORIMETRY_EXT:

                    switch(GET_DP_TX_INPUT_EXT_COLORIMETRY())
                    {
                        case _COLORIMETRY_EXT_RGB_SRGB:
                        default:

                            if(GET_DP_TX_RGB_QUANTIZATION_RANGE() == _RGB_QUANTIZATION_FULL_RANGE)
                            {
                                SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_SRGB_VESA);
                            }
                            else
                            {
                                SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_SRGB_CEA);
                            }

                            break;

                        case _COLORIMETRY_EXT_RGB_XRRGB:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_XRRGB);
                            break;

                        case _COLORIMETRY_EXT_RGB_SCRGB:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_SCRGB);
                            break;

                        case _COLORIMETRY_EXT_RGB_ADOBERGB:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_ADOBERGB);
                            break;

                        case _COLORIMETRY_EXT_RGB_DCI_P3:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_DCI_P3);
                            break;

                        case _COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RGB_COLOR_PROFILE);
                            break;
                    }

                    break;
            }

            break;

        case _COLOR_SPACE_YCBCR422:
        case _COLOR_SPACE_YCBCR420:

            switch(GET_DP_TX_INPUT_COLORIMETRY())
            {
                case _COLORIMETRY_YCC_ITUR_BT601:
                default:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC422_ITUR_BT601);
                    break;

                case _COLORIMETRY_YCC_ITUR_BT709:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC422_ITUR_BT709);
                    break;

                case _COLORIMETRY_YCC_XVYCC601:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC422_XVYCC601);
                    break;

                case _COLORIMETRY_YCC_XVYCC709:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC422_XVYCC709);
                    break;

                case _COLORIMETRY_EXT:

                    switch(GET_DP_TX_INPUT_EXT_COLORIMETRY())
                    {
                        case _COLORIMETRY_EXT_YCC_ITUR_BT601:
                        default:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC422_ITUR_BT601);
                            break;

                        case _COLORIMETRY_EXT_YCC_ITUR_BT709:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC422_ITUR_BT709);
                            break;

                        case _COLORIMETRY_EXT_YCC_XVYCC601:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC422_XVYCC601);
                            break;

                        case _COLORIMETRY_EXT_YCC_XVYCC709:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC422_XVYCC709);
                            break;
                    }

                    break;
            }

            break;

        case _COLOR_SPACE_YCBCR444:

            switch(GET_DP_TX_INPUT_COLORIMETRY())
            {
                case _COLORIMETRY_YCC_ITUR_BT601:
                default:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC444_ITUR_BT601);
                    break;

                case _COLORIMETRY_YCC_ITUR_BT709:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC444_ITUR_BT709);
                    break;

                case _COLORIMETRY_YCC_XVYCC601:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC444_XVYCC601);
                    break;

                case _COLORIMETRY_YCC_XVYCC709:
                    SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC444_XVYCC709);
                    break;

                case _COLORIMETRY_EXT:

                    switch(GET_DP_TX_INPUT_EXT_COLORIMETRY())
                    {
                        case _COLORIMETRY_EXT_YCC_ITUR_BT601:
                        default:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC444_ITUR_BT601);
                            break;

                        case _COLORIMETRY_EXT_YCC_ITUR_BT709:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC444_ITUR_BT709);
                            break;

                        case _COLORIMETRY_EXT_YCC_XVYCC601:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC444_XVYCC601);
                            break;

                        case _COLORIMETRY_EXT_YCC_XVYCC709:
                            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_YCC444_XVYCC709);
                            break;
                    }

                    break;
            }

            break;

        case _COLOR_SPACE_Y_ONLY:

            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_Y_ONLY);
            break;

        case _COLOR_SPACE_RAW:
            SET_DP_TX_MSA_COLORIMETRY_VALUE(_DP_MSA_COLORIMETRY_RAW);

            break;
    }

    DebugMessageMst("DP Tx MSA Color Space 1", GET_DP_TX_INPUT_COLOR_SPACE());

    if(GET_DP_TX_INPUT_INTERLACE_MODE() == _ON)
    {
        // Set MISC1
        if(GET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER() == _EVEN)
        {
            ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT0, _BIT0);
        }
        else
        {
            ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT0, 0x00);
        }
    }

    // MSA_DB = 1
    ScalerSetBit(PBB_B4_MSA_CTRL, ~_BIT7, _BIT7);

    DebugMessageMst("DP Tx MSA Color Space 2", ScalerGetBit(PBB_B5_MSA_MISC0, (_BIT2 | _BIT1)));
}

//--------------------------------------------------
// Description  : Switch Tx Stream Source Lane Num
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxConfigMstStreamLaneNum(void)
{
    if(g_enumDpMSTCapablePort != _DP_MST_NO_PORT)
    {
        // Swtich MST Daisy Chain or MST2SST Lane Num
        switch(GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x01) & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0))
        {
            case _DP_ONE_LANE:

                ScalerSetBit(PA_80_MST2SST_CONFIG, ~(_BIT4 | _BIT3), _BIT3);

                break;

            case _DP_TWO_LANE:

                ScalerSetBit(PA_80_MST2SST_CONFIG, ~(_BIT4 | _BIT3), _BIT4);

                break;

            default:
            case _DP_FOUR_LANE:

                ScalerSetBit(PA_80_MST2SST_CONFIG, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Switch to Active State
// Input Value  : Target Tx Mode
// Output Value : None
//--------------------------------------------------
void ScalerDpTxStateChangeEvent(EnumDPTxModeStatus enumModeState)
{
    SET_DP_TX_MODE_STATE(enumModeState);
    SET_DP_TX_MODE_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Tx INT Handle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxIntHandle_EXINT0(void) using 1
{
    // Short HPD IRQ
    if((ScalerGetBit_EXINT(PBB_72_HPD_IRQ_EN, _BIT6) == _BIT6) &&
       (ScalerGetBit_EXINT(PBB_71_HPD_IRQ, _BIT6) == _BIT6))
    {
        ScalerSetBit_EXINT(PBB_71_HPD_IRQ, ~(_BIT6 | _BIT4 | _BIT2), _BIT6);

        if(ScalerDpTxAuxNativeRead_EXINT0(0x00, 0x02, 0x00, 6, pData_EXINT) == _TRUE)
        {
            SET_DP_TX_IRQ_HPD_DETECTED();

            if(((GET_DP_TX_DOWNSTREAM_LANE_NUM() == 1) && ((pData_EXINT[2] & 0x07) != 0x07)) ||
               ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == 2) && ((pData_EXINT[2] & 0x77) != 0x77)) ||
               ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == 4) && (((pData_EXINT[2] & 0x77) != 0x77) || ((pData_EXINT[3] & 0x77) != 0x77))) ||
               ((GET_DP_TX_DOWNSTREAM_LANE_NUM() != 1) && ((pData_EXINT[4] & 0x01) != 0x01)))
            {
                SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
            }

            if((pData_EXINT[1] & _BIT2) == _BIT2)
            {
                SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_CP_IRQ);
            }

            if((pData_EXINT[1] & _BIT1) == _BIT1)
            {
                SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST);
            }

            if((pData_EXINT[4] & _BIT6) == _BIT6)
            {
                SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_DOWNSTREAM_PORT_STATUS_CHANGE);
            }
        }

        if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
        {
            // Get IRQ Event Status Indicator
            if(ScalerDpTxAuxNativeRead_EXINT0(0x00, 0x20, 0x03, 3, pData_EXINT) == _TRUE)
            {
                SET_DP_TX_IRQ_HPD_DETECTED();

                if((pData_EXINT[0] & _BIT1) == _BIT1)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST);
                }

                if((pData_EXINT[0] & _BIT2) == _BIT2)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_CP_IRQ);
                }

                if((pData_EXINT[0] & _BIT3) == _BIT3)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_MCCS_IRQ);
                }

                if(((pData_EXINT[0] & _BIT4) == _BIT4) && (GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ) == 0x00))
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ);
                }

                if(((pData_EXINT[0] & _BIT5) == _BIT5) && (GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ) == 0x00))
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ);
                }

                if((pData_EXINT[2] & _BIT0) == _BIT0)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ);
                }

                if((pData_EXINT[2] & _BIT1) == _BIT1)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                }

                if((pData_EXINT[2] & _BIT2) == _BIT2)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxLinkTraining(void)
{
    if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
    {
        // Read TEST_LINK_RATE
        ScalerDpTxAuxNativeRead(0x00, 0x02, 0x19, 1, pData);

        SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(pData[0]);

        // Read TEST_LANE_COUNT
        ScalerDpTxAuxNativeRead(0x00, 0x02, 0x20, 1, pData);

        SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM((pData[0] & 0x1F));

        CLR_DP_TX_CTS_TEST_REQUEST_TARGET_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING);
    }
    else if(GET_DP_TX_DOWNSTREAM_MAIN_LINK_POWER_STATUS() == _TRUE)
    {
        // Read Lane0/Lane1/Lane2/Lane3 CR_DONE/EQ_DONE/Symbol Locked/Lane Align
        ScalerDpTxAuxNativeRead(0x00, 0x02, 0x02, 3, pData);

        if(((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_FOUR_LANE) && (pData[0] == 0x77) && (pData[1] == 0x77) && ((pData[2] & _BIT0) == _BIT0)) ||
           ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_TWO_LANE) && (pData[0] == 0x77) && ((pData[2] & _BIT0) == _BIT0)) ||
           ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_ONE_LANE) && (pData[0] == 0x07)))
        {
            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_PASS);
            return;
        }
    }

    ScalerDpTxTPInitialSet();

    while((GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS) && (GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_FAIL))
    {
        switch(GET_DP_TX_LT_STATE())
        {
            case _DP_TX_TRAINING_PATTERN1:

                SET_DP_TX_LT_RESULT(ScalerDpTxTrainPattern1());

                if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN1_PASS)
                {
                    SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN2);
                }
                else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL)
                {
                    ScalerDpTxTrainPatternEnd();

                    if(ScalerDpTxLinkRateReduce(_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL) == _FAIL)
                    {
                        if(ScalerDpTxLaneCountReduce(_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL) == _FAIL)
                        {
                            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                        }
                        else
                        {
                            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
                        }
                    }
                    else
                    {
                        SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
                    }
                }

                break;

            case _DP_TX_TRAINING_PATTERN2:

                SET_DP_TX_LT_RESULT(ScalerDpTxTrainPattern2());

                if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN2_PASS)
                {
                    SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                }
                else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL)
                {
                    ScalerDpTxTrainPatternEnd();

                    if(ScalerDpTxLinkRateReduce(_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL) == _FAIL)
                    {
                        if(ScalerDpTxLaneCountReduce(_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL) == _FAIL)
                        {
                            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                        }
                        else
                        {
                            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);
                            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
                        }
                    }
                    else
                    {
                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);
                        SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
                    }
                }
                else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL)
                {
                    ScalerDpTxTrainPatternEnd();

                    if(ScalerDpTxLaneCountReduce(_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL) == _FAIL)
                    {
                        if(ScalerDpTxLinkRateReduce(_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL) == _FAIL)
                        {
                            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                        }
                        else
                        {
                            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);
                            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
                        }
                    }
                    else
                    {
                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);
                        SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
                    }
                }

                break;

            case _DP_TX_TRAINING_PATTERN_END:

                if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN2_PASS)
                {
                    SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_PASS);
                }
                else
                {
                    SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_FAIL);
                }

                ScalerDpTxTrainPatternEnd();

                break;

            default:

                break;
        }

        if(GET_DP_TX_HPD_STATUS_CHANGE() == _TRUE)
        {
            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_FAIL);

            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Inital Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTPInitialSet(void)
{
    SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
    SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);

    SET_DP_TX_DOWNSTREAM_LINK_RATE(GET_DP_TX_DOWNSTREAM_MAX_LINK_RATE());
    SET_DP_TX_DOWNSTREAM_LANE_NUM(GET_DP_TX_DOWNSTREAM_MAX_LANE_NUM());
    SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM_TEMP(GET_DP_TX_DOWNSTREAM_MAX_LANE_NUM());

    // Set Analog PHY CMU to gen Link Rate
    ScalerGDIPhyTxCMUPowerOn();

    // Initialize Main Link Signal
    ScalerDpTxSignalInitialSetting();

    // Set Tx Power On
    pData[0] = 0x01;
    ScalerDpTxAuxNativeWrite(0x00, 0x06, 0x00, 1, pData);

    ScalerDpTxAuxNativeRead(0x00, 0x01, 0x07, 1, pData);

    // Set Down Spread
    pData[0] = ((pData[0] & ~_BIT4) | ((BYTE)GET_DP_TX_DOWNSTREAM_DOWN_SPREAD() << 4));
    ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x07, 1, pData);

    // Set Link Rate
    ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x00, 1, &GET_DP_TX_DOWNSTREAM_MAX_LINK_RATE());

    // Set Link Count and Enhance Framing
    pData[0] = ((BYTE)GET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING() << 7) | GET_DP_TX_DOWNSTREAM_LANE_NUM();
    ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x01, 1, pData);
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpTxTrainPattern2(void)
{
    // Start TP2 Process
    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN1_PASS)
    {
        // Get TPSx Pattern
        pData[0] = ScalerDpTxSetTPSxPattern();

        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

        // Disable Scrambling Besides Sending TPS4 Pattern
        // DPCD 00102h BIT5 = 0: Enable Scramble; BIT5 = 1: Disable Scramble;
        if(pData[0] != _DP_TP_4)
        {
            pData[0] |= _DP_SCRAMBLING_DISABLE;
        }

        pData[1] = g_stTxLTInfo.ucLane0Adjust;
        pData[2] = g_stTxLTInfo.ucLane1Adjust;
        pData[3] = g_stTxLTInfo.ucLane2Adjust;
        pData[4] = g_stTxLTInfo.ucLane3Adjust;

        // Write DPCD 102h-106h to Start TP2
        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerGDIPhyTxMLPHYSet();

        pData[0] = g_stTxLTInfo.ucLane0Adjust;
        pData[1] = g_stTxLTInfo.ucLane1Adjust;
        pData[2] = g_stTxLTInfo.ucLane2Adjust;
        pData[3] = g_stTxLTInfo.ucLane3Adjust;

        // Write DPCD 103h-106h (Voltage Swing and Pre-emphasis)
        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x03, 4, pData);
    }

    if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
    {
        pData[0] = (_DP_LANE0_MAX_POST_CURSOR2_REACHED | _DP_LANE1_MAX_POST_CURSOR2_REACHED);
        pData[1] = (_DP_LANE2_MAX_POST_CURSOR2_REACHED | _DP_LANE3_MAX_POST_CURSOR2_REACHED);
        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x0F, 2, pData);

        // Read Training Aux Read Interval
        ScalerDpTxAuxNativeRead(0x00, 0x00, 0x0E, 1, pData);

        pData[0] &= 0x7F;

        if(pData[0] > 0x04)
        {
            pData[0] = 0;
        }
    }
    else
    {
        pData[0] = 0;
    }

    if(pData[0] != 0x00)
    {
        // Delay 4 * pData[0] ms
        ScalerTimerDelayXms(pData[0] << 2);
    }
    else
    {
        // Delay Time us [400,x]
        DELAY_XUS(400);
    }

    // Read Lane Status and Request Adjust Level
    ScalerDpTxAuxNativeRead(0x00, 0x02, 0x02, 6, pData);
    g_stTxLTInfo.ucLane01LTStatus = pData[0];
    g_stTxLTInfo.ucLane23LTStatus = pData[1];
    g_stTxLTInfo.ucLaneAlignStatus = pData[2];
    g_stTxLTInfo.ucAdjustReqLane01 = pData[4];
    g_stTxLTInfo.ucAdjustReqLane23 = pData[5];

    // CDR unlock => Reduce Link Rate or Lane Count and then return to TP1
    // EQ unlock => Adjust Swing and Pre-emphasis until retry more than 5 times
    switch(GET_DP_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            if((GET_DP_TX_LANE0_CR_DONE() == _TRUE) && (GET_DP_TX_LANE1_CR_DONE() == _TRUE) && (GET_DP_TX_LANE2_CR_DONE() == _TRUE) && (GET_DP_TX_LANE3_CR_DONE() == _TRUE))
            {
                if((GET_DP_TX_LANE0_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE1_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE2_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE3_EQ_DONE() == _TRUE) &&
                   (GET_DP_TX_LANE_ALIGN_DONE() == _TRUE))
                {
                    CLR_DP_TX_TP2_CNT();

                    return _DP_TX_TRAINING_PATTERN2_PASS;
                }
            }
            else if((GET_DP_TX_LANE0_CR_DONE() == _TRUE) || (GET_DP_TX_LANE1_CR_DONE() == _TRUE) || (GET_DP_TX_LANE2_CR_DONE() == _TRUE) || (GET_DP_TX_LANE3_CR_DONE() == _TRUE))
            {
                CLR_DP_TX_TP2_CNT();

                // Lane Count Reduce
                return _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
            }
            else
            {
                CLR_DP_TX_TP2_CNT();

                // Link Rate Reduce
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_TWO_LANE:

            if((GET_DP_TX_LANE0_CR_DONE() == _TRUE) && (GET_DP_TX_LANE1_CR_DONE() == _TRUE))
            {
                if((GET_DP_TX_LANE0_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE1_EQ_DONE() == _TRUE) &&
                   (GET_DP_TX_LANE_ALIGN_DONE() == _TRUE))
                {
                    CLR_DP_TX_TP2_CNT();

                    return _DP_TX_TRAINING_PATTERN2_PASS;
                }
            }
            else if((GET_DP_TX_LANE0_CR_DONE() == _TRUE) || (GET_DP_TX_LANE1_CR_DONE() == _TRUE))
            {
                CLR_DP_TX_TP2_CNT();

                // Lane Count Reduce
                return _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
            }
            else
            {
                CLR_DP_TX_TP2_CNT();

                // Link Rate Reduce
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_ONE_LANE:
        default:

            if(GET_DP_TX_LANE0_CR_DONE() == _TRUE)
            {
                if((GET_DP_TX_LANE0_EQ_DONE() == _TRUE) &&
                   (GET_DP_TX_LANE_ALIGN_DONE() == _TRUE))
                {
                    CLR_DP_TX_TP2_CNT();

                    return _DP_TX_TRAINING_PATTERN2_PASS;
                }
            }
            else
            {
                CLR_DP_TX_TP2_CNT();

                // Link Rate Reduce
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;
    }

    // EQ unlock => Reduce Lane Count
    if(GET_DP_TX_TP2_CNT() >= 5)
    {
        CLR_DP_TX_TP2_CNT();

        // Lane Count Reduce
        return _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
    }
    else
    {
        ADD_DP_TX_TP2_CNT();
    }

    switch(GET_DP_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            ScalerDpTxTP2Lane3Adjust();
            ScalerDpTxTP2Lane2Adjust();
            ScalerDpTxTP2Lane1Adjust();
            ScalerDpTxTP2Lane0Adjust();

            break;

        case _DP_TWO_LANE:

            ScalerDpTxTP2Lane1Adjust();
            ScalerDpTxTP2Lane0Adjust();

            break;

        case _DP_ONE_LANE:
        default:

            ScalerDpTxTP2Lane0Adjust();

            break;
    }

    return _DP_TX_TRAINING_PATTERN2_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training Pattern End
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTrainPatternEnd(void)
{
    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
    {
        // Restore Enhanced Mode because Scramble Circuit can't Match SR-BS-BS-SR(TPS4 pattern) to Reset LFSR with TPS4 pattern in TP2 stage if Enhanced Mode is enable
        ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, (GET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING() << 2));

        // Enable Scramble and Enable BS replaced by SR
        ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT4, _BIT4);
        ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, _BIT0);

        // Main Link switch to IDLE Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_IDLE_PATTERN << 4));

        // Direct Apply Idle Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

        // Phy Input Data from Tx Mac (SST)
        ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);

        if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE)
        {
            ScalerDpTxSetStreamSource(GET_DP_TX_STREAM_SOURCE());
        }
    }
    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_FAIL)
    {
        // Power Down ML PHY
        ScalerGDIPhyTxMLPowerOff();

        // Main Link switch to IDLE Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_IDLE_PATTERN << 4));

        // Direct Apply Idle Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);
    }

    // Write TRAINING_PATTERN_SET = 00
    pData[0] = _DP_TP_NONE;
    ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x02, 1, pData);
}

//--------------------------------------------------
// Description  : DP Tx HPD Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHPDProc(void)
{
    SET_DP_TX_HPD_EVENT(_DP_TX_HPD_NO_EVENT);
    CLR_DP_TX_IRQ_HPD_TYPE();

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
    if(GET_DP_TX_HPD_DETECTION_ENABLE() == _DISABLE)
    {
        DebugMessageMst("8. Dp Tx HPD Proc Return Directly", 1);

        return;
    }
#endif

    // Disable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

    // Record which kind of HPD Change happened by now
    pData[0] = (ScalerGetByte(PBB_71_HPD_IRQ) | ((BYTE)GET_DP_TX_IRQ_HPD_DETECTED() << 6));

    // Copy IRQ type Detected In INT
    SET_DP_TX_IRQ_HPD_TYPE(GET_DP_TX_IRQ_HPD_TYPE_INT());

    CLR_DP_TX_IRQ_HPD_DETECTED();

    // Clear IRQ type of Int.
    CLR_DP_TX_IRQ_HPD_TYPE_INT();

    // Determine Current HPD Event Status
    // Current HPD Level HIGH
    if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _HIGH)
    {
        // First HPD From Low to High
        if(GET_DP_TX_HPD_FIRST_PLUG() == _TRUE)
        {
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_PLUG_EVENT);

            CLR_DP_TX_HPD_FIRST_PLUG();
        }

        if((pData[0] & _BIT4) == _BIT4)
        {
            // HPD unplug Event
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_UNPLUG_EVENT);

            // Clear Unplug Flag
            ScalerSetBit(PBB_71_HPD_IRQ, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT4);
        }
        else if((pData[0] & _BIT2) == _BIT2)
        {
            // Long HPD
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_PLUG_EVENT);

            // Clr All flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);
        }
        else if((pData[0] & _BIT6) == _BIT6)
        {
            // Short HPD
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_IRQ_EVENT);
        }
    }
    else
    {
        if((pData[0] & _BIT4) == _BIT4)
        {
            // HPD unplug Event
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_UNPLUG_EVENT);

            // Clr All flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);
        }
    }

    switch(GET_DP_TX_HPD_EVENT())
    {
        case _DP_TX_HPD_PLUG_EVENT:

            CLR_DP_TX_DOWNSTREAM_INFO_READY();

            break;

        case _DP_TX_HPD_IRQ_EVENT:

            // Check Short HPD IRQ Type
            ScalerDpTxIRQEventCheck();

            break;

        case _DP_TX_HPD_UNPLUG_EVENT:

            break;

        default:
            break;
    }

    // Enable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : Dp Tx Link Maintance
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxIRQEventCheck(void)
{
    BYTE pucData[4];

    memset(pucData, 0, sizeof(pucData));

    if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
    {
        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
        {
            pucData[0] |= _BIT0;
        }

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
        {
            pucData[0] |= _BIT1;

            // Get Link Status
            ScalerDpTxAuxNativeRead(0x00, 0x20, 0x0C, 3, &pucData[1]);

            switch(GET_DP_TX_DOWNSTREAM_LANE_NUM())
            {
                case _DP_ONE_LANE:
                    if((pucData[1] & 0x07) == 0x07)
                    {
                        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                    }
                    break;

                case _DP_TWO_LANE:
                    if(((pucData[1] & 0x77) == 0x77) && ((pucData[3] & 0x01) == 0x01))
                    {
                        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                    }
                    break;

                case _DP_FOUR_LANE:
                    if(((pucData[1] & 0x77) == 0x77) && ((pucData[2] & 0x77) == 0x77) && ((pucData[3] & 0x01) == 0x01))
                    {
                        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                    }
                    break;

                default:
                    break;
            }
        }

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ)
        {
            pucData[0] |= _BIT2;

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ);
            }
        }

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_DOWNSTREAM_PORT_STATUS_CHANGE) == _DP_TX_IRQ_HPD_DOWNSTREAM_PORT_STATUS_CHANGE)
        {
            // Read DownStream Sink Count
            ScalerDpTxAuxNativeRead(0x00, 0x02, 0x00, 1, &pucData[1]);

            SET_DP_TX_DOWNSTREAM_SINK_COUNT(pucData[1] & 0xBF);
            SET_DP_TX_DOWNSTREAM_SINK_COUNT_CHANGE();

            CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_DOWNSTREAM_PORT_STATUS_CHANGE);
        }

        // CLR Rx_Cap_IRQ and Link_Status_CHG_IRQ and Stream_Status_CHG_IRQ
        if(pucData[0] != 0x00)
        {
            ScalerDpTxAuxNativeWrite(0x00, 0x20, 0x05, 1, pucData);
        }

        pucData[0] = 0x00;

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_CP_IRQ) == _DP_TX_IRQ_HPD_CP_IRQ)
        {
            pucData[0] |= _BIT2;

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_CP_IRQ);
            }
            else
            {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if((GET_DP_TX_HDCP2_MODE() == _ENABLE) && (GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE))
                {
                    // Read HDCP2 B Status
                    if(ScalerDpTxAuxNativeRead(0x06, 0x94, 0x93, 1, &pucData[1]) == _TRUE)
                    {
                        SET_DP_TX_HDCP2_IRQ_TYPE(pucData[1]);
                    }
                }
                else
#endif
                {
                    // Read HDCP B Status
                    if(ScalerDpTxAuxNativeRead(0x06, 0x80, 0x29, 1, &pucData[1]) == _TRUE)
                    {
                        SET_DP_TX_IRQ_HDCP_TYPE(pucData[1]);
                    }
                }
            }
        }

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_MCCS_IRQ) == _DP_TX_IRQ_HPD_MCCS_IRQ)
        {
            pucData[0] |= _BIT3;
        }
    }
    else
    {
        // CLR CP IRQ
        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_CP_IRQ) == _DP_TX_IRQ_HPD_CP_IRQ)
        {
            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_CP_IRQ);
            }
            else
            {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if(GET_DP_TX_HDCP2_MODE() == _ENABLE)
                {
                    // Read HDCP2 B Status
                    if(ScalerDpTxAuxNativeRead(0x06, 0x94, 0x93, 1, &pucData[1]) == _TRUE)
                    {
                        SET_DP_TX_HDCP2_IRQ_TYPE(pucData[1]);
                    }
                }
                else
#endif
                {
                    // Read HDCP B Status
                    if(ScalerDpTxAuxNativeRead(0x06, 0x80, 0x29, 1, &pucData[1]) == _TRUE)
                    {
                        SET_DP_TX_IRQ_HDCP_TYPE(pucData[1]);
                    }
                }
            }

            pucData[0] |= _BIT2;
        }
    }

    if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST) == _DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST)
    {
        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST);

        pucData[0] |= _BIT1;

        // Read CTS Test Request Type
        if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0x18, 1, &pucData[1]) == _TRUE)
        {
            SET_DP_TX_CTS_TEST_REQUEST_TYPE(pucData[1]);
        }

        // Support TEST_LINK_TRAINING
        if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
        {
            pucData[1] = _TEST_ACK;
        }
        else
        {
            pucData[1] = _TEST_NAK;

            CLR_DP_TX_CTS_TEST_REQUEST_TYPE();
        }

        // Write TEST Response
        ScalerDpTxAuxNativeWrite(0x00, 0x02, 0x60, 1, &pucData[1]);
    }

    if(pucData[0] != 0x00)
    {
        if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
        {
            // CLR CP_IRQ and MCCS_IRQ
            ScalerDpTxAuxNativeWrite(0x00, 0x20, 0x03, 1, pucData);
        }

        // CLR CP_IRQ and AUTOMATED_TEST_REQUEST
        ScalerDpTxAuxNativeWrite(0x00, 0x02, 0x01, 1, pucData);
    }
}

//--------------------------------------------------
// Description  : Set DP Tx Stream Source
// Input Value  : EnumDPTxInputSource
// Output Value : None
//--------------------------------------------------
void ScalerDpTxSetStreamSource(EnumDPTxInputSource enumStreamSource)
{
    SET_DP_TX_STREAM_SOURCE(enumStreamSource);
    SET_DP_TX_STREAM_SOURCE_CHANGE();

    if(enumStreamSource == _DP_TX_SOURCE_NONE)
    {
        // Clear Exceed BW Flag for Clone Mode
        CLR_DP_TX_EXCEED_LINK_BANDWIDTH();
    }
    else
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        CLR_DP_TX_HDCP2_BACKUP_CONTENT_STREAM();
#endif
    }
}

//--------------------------------------------------
// Description  : Set DP Tx Stream Source for EXINT
// Input Value  : EnumDPTxInputSource
// Output Value : None
//--------------------------------------------------
void ScalerDpTxSetStreamSource_EXINT0(EnumDPTxInputSource enumStreamSource) using 1
{
    SET_DP_TX_STREAM_SOURCE(enumStreamSource);
    SET_DP_TX_STREAM_SOURCE_CHANGE();

    if(enumStreamSource == _DP_TX_SOURCE_NONE)
    {
        // Clear Exceed BW Flag for Clone Mode
        CLR_DP_TX_EXCEED_LINK_BANDWIDTH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Set Audio Channel Count
// Input Value  :
// Output Value : Changed => _TRUE or No Changed => _FALSE
//--------------------------------------------------
void ScalerDpTxAudioSetting(void)
{
    BYTE ucPacketPerSample = 0;
    WORD usMaxAudioPacket = 0;
    WORD usBe2Be = 0;

    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        SET_DP_TX_AUDIO_CHANNEL_COUNT(ScalerGetBit(PBC_4A_MST_SEC_PKT_HB3, (_BIT6 | _BIT5 | _BIT4)) >> 4);

        if(GET_DP_TX_AUDIO_CHANNEL_COUNT() > _AUDIO_CHANNEL_COUNT_2)
        {
            // Set 8 channel layout and audio source from MST
            ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Set Audio Packet Per Sample
            ucPacketPerSample = 40;
        }
        else
        {
            // Set 2 channel layout and audio source from MST
            ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~(_BIT7 | _BIT6), _BIT7);

            // Set Audio Packet Per Sample
            ucPacketPerSample = 20;
        }
    }
    else
    {
        SET_DP_TX_AUDIO_CHANNEL_COUNT(_AUDIO_CHANNEL_COUNT_2);

        // Set 2 channel layout and audio source from I2S
        ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~(_BIT7 | _BIT6), 0x00);

        // Set Audio Packet Per Sample
        ucPacketPerSample = 20;
    }

    // sec_end_cnt = max_audio_packet (lane_num, max_long_packet_cnt) + safe_margin
    // max_audio_packet = SS&SE + HEADER&ECC BYTES / lane_num + [(max_long_packet_cnt+1) * (minimum packet payload + 4)] / lane_num.
    usMaxAudioPacket = 2 + ((8 + ucPacketPerSample) / GET_DP_TX_DOWNSTREAM_LANE_NUM());

    // Get BE2BE Period with Htotal
    usBe2Be = (DWORD)g_stDPTxInputTimingInfo.usHTotal * 270 * GET_DP_TX_DOWNSTREAM_LINK_RATE() / GET_DP_TX_INPUT_PIXEL_CLK();

    // Get 70% of blanking period
    usBe2Be = (DWORD)(usBe2Be - GET_DP_TX_HORIZONTAL_DE_PERIOD()) * 7 / 10;

    // if BS2BE > max_audio_packet, Sec_end_count = BS2BE - max_audio_packet
    // else Sec_end_count = 0;
    if(usBe2Be > usMaxAudioPacket)
    {
        // Set Seccondary End Count
        ScalerSetByte(PBB_D4_ARBITER_SEC_END_CNT_HB, HIBYTE(usBe2Be - usMaxAudioPacket));
        ScalerSetByte(PBB_D5_ARBITER_SEC_END_CNT_LB, LOBYTE(usBe2Be - usMaxAudioPacket));
    }
    else
    {
        // Set Seccondary End Count
        ScalerSetByte(PBB_D4_ARBITER_SEC_END_CNT_HB, 0x00);
        ScalerSetByte(PBB_D5_ARBITER_SEC_END_CNT_LB, 0x00);
    }
}

//--------------------------------------------------
// Description  : DP Tx Get Audio Channel Count Change
// Input Value  :
// Output Value : Changed => _TRUE or No Changed => _FALSE
//--------------------------------------------------
bit ScalerDpTxAudioGetChannelChange(void)
{
    // Get Channel Count from DP Source
    if((ScalerGetBit(PBC_4A_MST_SEC_PKT_HB3, (_BIT6 | _BIT5 | _BIT4)) >> 4) > _AUDIO_CHANNEL_COUNT_2)
    {
        // Campare 8 channel count with DP TX audio
        return (ScalerGetBit(PBC_18_AUD_FUNCTION_CTRL1, _BIT6) == _BIT6) ? _FALSE : _TRUE;
    }
    else
    {
        // Campare 2 channel count with DP TX audio
        return (ScalerGetBit(PBC_18_AUD_FUNCTION_CTRL1, _BIT6) == 0x00) ? _FALSE : _TRUE;
    }
}

//--------------------------------------------------
// Description  : DP Tx Get Audio Sampling Frequency Packet
// Input Value  :
// Output Value : Packet Number
//--------------------------------------------------
WORD ScalerDpTxAudioGetSamplingFreqPacket(void)
{
    CLR_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ();

    switch(ScalerDpTxAudioGetSamplingFreqRange())
    {
        case _DP_TX_AUDIO_FREQ_32K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_32K);
            return 320;

        case _DP_TX_AUDIO_FREQ_44_1K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_44_1K);
            return 441;

        case _DP_TX_AUDIO_FREQ_48K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_48K);
            return 480;

        case _DP_TX_AUDIO_FREQ_64K:

            return 640;

        case _DP_TX_AUDIO_FREQ_88_2K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_88_2K);
            return 882;

        case _DP_TX_AUDIO_FREQ_96K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_96K);
            return 960;

        case _DP_TX_AUDIO_FREQ_128K:

            return 1280;

        case _DP_TX_AUDIO_FREQ_176_4K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_176_4K);
            return 1764;

        case _DP_TX_AUDIO_FREQ_192K:

            SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(_DP_TX_AUDIO_INFOFRAME_FREQ_192K);
            return 1920;

        case _DP_TX_AUDIO_FREQ_256K:

            return 2560;

        case _DP_TX_AUDIO_FREQ_352_8K:

            return 3528;

        case _DP_TX_AUDIO_FREQ_384K:

            return 3840;

        case _DP_TX_AUDIO_FREQ_512K:

            return 5120;

        case _DP_TX_AUDIO_FREQ_705_6K:

            return 7056;

        case _DP_TX_AUDIO_FREQ_768K:

            return 7680;

        case _DP_TX_AUDIO_FREQ_NO_AUDIO:
        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : DP Tx Set Header byte for Sec Data
// Input Value  : Packet Header
// Output Value : Packet Parity
//--------------------------------------------------
void ScalerDpTxSetSecDataHeader(EnumDPTxSecDataPacketType enumPackettype)
{
    BYTE pucData[4];

    memset(pucData, 0, sizeof(pucData));

    // Sec Data Packet ID
    pucData[0] = 0x00;

    // Packet Type
    pucData[1] = enumPackettype;

    // Select Packet Type
    ScalerSetBit(PBC_7B_SEC_PH_PACKET_TYPE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), pucData[1]);

    switch(enumPackettype)
    {
        case _SEC_PACKET_TYPE_AUDIO_TIMESTAMP:

            // Audio Timestamp LSB of (Data Byte count - 1)
            pucData[2] = 0x17;

            // [1:0]: Audio Timestamp MSB of (Data Byte count - 1), [7:2] DP version number
            pucData[3] = (_DP_VERSION_1_1 << 2);

            break;

        case _SEC_PACKET_TYPE_AUDIO_STREAM:

            // Reserved
            pucData[2] = 0x00;

            // [7:4]: Coding type
            pucData[3] = (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST) ? ScalerGetBit(PBC_4A_MST_SEC_PKT_HB3, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) : 0x00;

            // [2:0]: Channel count
            pucData[3] = (pucData[3] << 4) | GET_DP_TX_AUDIO_CHANNEL_COUNT();

            break;

        case _SEC_PACKET_TYPE_VSC:

            // [4:0]: Revision number
            pucData[2] = 0x01;

            // [4:0]: Number of valid data bytes
            pucData[3] = 0x01;

            break;

        case _SEC_PACKET_TYPE_INFOFRAME_AVI:
        case _SEC_PACKET_TYPE_INFOFRAME_AUDIO:
        case _SEC_PACKET_TYPE_INFOFRAME_MPEG:

            // Set CEA-861 InfoFrame
            pucData[1] = _BIT7 | (pucData[1] & 0x07);

            // LSB of (Data Byte count - 1)
            pucData[2] = 0x1B;

            // [1:0]: MSB of (Data Byte count - 1), [7:2] DP version number
            if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
            {
                pucData[3] = (_INFOFRAME_SDP_VERSION_1_2 << 2);
            }
            else
            {
                pucData[3] = (_INFOFRAME_SDP_VERSION_1_1 << 2);
            }

            break;

        case _SEC_PACKET_TYPE_INFOFRAME_RSV:

            // DP AMD SPD Info
            pucData[1] = 0x83;

            // DP AMD SPD Info
            pucData[2] = 0x01;

            // DP AMD SPD Info
            pucData[3] = 0x08;

            break;

        default:
            break;
    }

    // Set Header Byte
    ScalerSetByte(PBC_73_SEC_PH_HB0, pucData[0]);
    ScalerSetByte(PBC_74_SEC_PH_HB1, pucData[1]);
    ScalerSetByte(PBC_75_SEC_PH_HB2, pucData[2]);
    ScalerSetByte(PBC_76_SEC_PH_HB3, pucData[3]);

    // Set Parity Byte
    ScalerSetByte(PBC_77_SEC_PH_PB0, ScalerDpTxAudioGetSecDataParity(pucData[0]));
    ScalerSetByte(PBC_78_SEC_PH_PB1, ScalerDpTxAudioGetSecDataParity(pucData[1]));
    ScalerSetByte(PBC_79_SEC_PH_PB2, ScalerDpTxAudioGetSecDataParity(pucData[2]));
    ScalerSetByte(PBC_7A_SEC_PH_PB3, ScalerDpTxAudioGetSecDataParity(pucData[3]));

    // Set Double Buffer
    ScalerSetBit(PBC_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : DP Tx Clear Header byte for Sec Data
// Input Value  : Packet Header
// Output Value : Packet Parity
//--------------------------------------------------
void ScalerDpTxClearSecDataHeader(EnumDPTxSecDataPacketType enumPackettype)
{
    // Select Packet Type
    ScalerSetBit(PBC_7B_SEC_PH_PACKET_TYPE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumPackettype);

    // Set Header Byte
    ScalerSetByte(PBC_73_SEC_PH_HB0, 0x00);
    ScalerSetByte(PBC_74_SEC_PH_HB1, 0x00);
    ScalerSetByte(PBC_75_SEC_PH_HB2, 0x00);
    ScalerSetByte(PBC_76_SEC_PH_HB3, 0x00);

    // Set Parity Byte
    ScalerSetByte(PBC_77_SEC_PH_PB0, 0x00);
    ScalerSetByte(PBC_78_SEC_PH_PB1, 0x00);
    ScalerSetByte(PBC_79_SEC_PH_PB2, 0x00);
    ScalerSetByte(PBC_7A_SEC_PH_PB3, 0x00);

    // Set Double Buffer
    ScalerSetBit(PBC_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : DP Tx Get Parity byte for Audio Packet Header
// Input Value  : Packet Header
// Output Value : Packet Parity
//--------------------------------------------------
BYTE ScalerDpTxAudioGetSecDataParity(BYTE ucHeader)
{
    BYTE ucParity = 0;

    // Bit 7
    ucParity |= ((BYTE)(GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT6(ucHeader))) << 7;

    // Bit 6
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT5(ucHeader))) << 6;

    // Bit 5
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT4(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 5;

    // Bit 4
    ucParity |= ((BYTE)(GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 4;

    // Bit 3
    ucParity |= ((BYTE)(GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT6(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 3;

    // Bit 2
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT5(ucHeader) ^ GET_DATA_BIT6(ucHeader))) << 2;

    // Bit 1
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT4(ucHeader) ^ GET_DATA_BIT5(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 1;

    // Bit 0
    ucParity |= (GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT4(ucHeader) ^ GET_DATA_BIT7(ucHeader));

    return ucParity;
}


//--------------------------------------------------
// Description  : Set Audio InfoFrame refer to CTA-861-G
// Input Value  : None
// Output Value : Node
//--------------------------------------------------
void ScalerDpTxAudioSetAudioInfoFrame(void)
{
    BYTE ucAudioInfoFrameStartIndex = 0;

    memset(g_pucDpTxAudioInfoframeCurrent, 0, sizeof(g_pucDpTxAudioInfoframeCurrent));

    ucAudioInfoFrameStartIndex = 13;

    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        for(pData[0] = ucAudioInfoFrameStartIndex; pData[0] < (ucAudioInfoFrameStartIndex + sizeof(g_pucDpTxAudioInfoframeCurrent)); pData[0]++)
        {
            ScalerSetBit(PBC_55_DP_INFO_FM_ADR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[0]);
            g_pucDpTxAudioInfoframeCurrent[pData[0] - ucAudioInfoFrameStartIndex] = ScalerGetByte(PBC_56_DP_INFO_FM_DAT);
        }
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
    {
        // [7:4] = Coding Type, [3] = 0, [2:1] = Channel Count
        g_pucDpTxAudioInfoframeCurrent[0] = GET_DP_TX_AUDIO_CHANNEL_COUNT();

        // [7:5] = 0, [4:2] = Sampling Frequency, [1:0] = Sample Size
        g_pucDpTxAudioInfoframeCurrent[1] = ((BYTE)GET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ() << 2);

        // [7:5] = 0, [5:0] = Coding Extension Type
        g_pucDpTxAudioInfoframeCurrent[2] = 0x00;

        // [7:0] = Channel Allocation
        g_pucDpTxAudioInfoframeCurrent[3] = 0x00;

        // [7] = Down-mix Inhibit Flag, [6:3] = Level Shift Infomation, [2] = 0, [1:0] = LFE playback level
        g_pucDpTxAudioInfoframeCurrent[4] = 0x00;
    }

    // Set Audio Infoframe to Register
    memcpy((volatile BYTE xdata *)PBC_26_SEC_INFO_AUD_DB0, g_pucDpTxAudioInfoframeCurrent, sizeof(g_pucDpTxAudioInfoframeCurrent));

    // Set Header for Audio InfoFrame
    ScalerDpTxSetSecDataHeader(_SEC_PACKET_TYPE_INFOFRAME_AUDIO);
}

//--------------------------------------------------
// Description  : Monitoring if Audio InfoFrame is changed
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxAudioMonitoringAudioInfoFrameChanged(void)
{
    BYTE ucAudioInfoFrameStartIndex = 13;
    bit bAIFChanged = _FALSE;

    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        for(pData[0] = ucAudioInfoFrameStartIndex; pData[0] < (ucAudioInfoFrameStartIndex + sizeof(g_pucDpTxAudioInfoframeCurrent)); pData[0]++)
        {
            ScalerSetBit(PBC_55_DP_INFO_FM_ADR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[0]);

            if(g_pucDpTxAudioInfoframeCurrent[pData[0] - ucAudioInfoFrameStartIndex] != ScalerGetByte(PBC_56_DP_INFO_FM_DAT))
            {
                g_pucDpTxAudioInfoframeCurrent[pData[0] - ucAudioInfoFrameStartIndex] = ScalerGetByte(PBC_56_DP_INFO_FM_DAT);

                bAIFChanged = _TRUE;
            }
        }

        if(bAIFChanged == _TRUE)
        {
            ScalerSetBit(PBC_71_SEC_AWD_STATUS_0, ~_BIT4, _BIT4);

            // Wait 1 frame time(frame rate = 23Hz x 10% margin)
            ScalerTimerPollingFlagProc(48, PBC_71_SEC_AWD_STATUS_0, _BIT4, _TRUE);

            CLR_DP_TX_AUDIO_INFOFRAME_SEND_STATUS();

            // Set Audio Infoframe to Register
            memcpy((volatile BYTE xdata *)PBC_26_SEC_INFO_AUD_DB0, g_pucDpTxAudioInfoframeCurrent, sizeof(g_pucDpTxAudioInfoframeCurrent));

            // Set Header for Audio InfoFrame
            ScalerDpTxSetSecDataHeader(_SEC_PACKET_TYPE_INFOFRAME_AUDIO);

            SET_DP_TX_AUDIO_INFOFRAME_SEND_STATUS();
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpTxTrainPattern1(void)
{
    // Start TP1 Process or Start Link Rate Reduce or Lane Count Reduce
    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_NO_RESULT)
    {
        // Disable scramble
        ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, 0x00);

        // Main Link switch to TP1 Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_TPS1 << 4));
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

        pData[0] = _DP_TP_1 | _DP_SCRAMBLING_DISABLE;
        pData[1] = g_stTxLTInfo.ucLane0Adjust;
        pData[2] = g_stTxLTInfo.ucLane1Adjust;
        pData[3] = g_stTxLTInfo.ucLane2Adjust;
        pData[4] = g_stTxLTInfo.ucLane3Adjust;

        // Write DPCD 102h to Start TP1
        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerGDIPhyTxMLPHYSet();

        pData[0] = g_stTxLTInfo.ucLane0Adjust;
        pData[1] = g_stTxLTInfo.ucLane1Adjust;
        pData[2] = g_stTxLTInfo.ucLane2Adjust;
        pData[3] = g_stTxLTInfo.ucLane3Adjust;

        // Write DPCD 103h-107h (Voltage Swing and Pre-emphasis)
        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x03, 4, pData);
    }

    if(GET_DP_TX_DOWNSTREAM_DPCD_REV() == _DP_VERSION_1_2)
    {
        // Read Training Aux Read Interval
        ScalerDpTxAuxNativeRead(0x00, 0x00, 0x0E, 1, pData);

        pData[0] &= 0x7F;

        if(pData[0] > 0x04)
        {
            pData[0] = 0;
        }
    }
    else
    {
        pData[0] = 0;
    }

    if(pData[0] != 0x00)
    {
        // Delay 4*pData[0] ms
        ScalerTimerDelayXms(pData[0] << 2);
    }
    else
    {
        // Delay Time us [100,x]
        DELAY_XUS(100);
    }

    // Read Lane Status and Request Adjust Level
    ScalerDpTxAuxNativeRead(0x00, 0x02, 0x02, 6, pData);
    g_stTxLTInfo.ucLane01LTStatus = pData[0];
    g_stTxLTInfo.ucLane23LTStatus = pData[1];
    g_stTxLTInfo.ucAdjustReqLane01 = pData[4];
    g_stTxLTInfo.ucAdjustReqLane23 = pData[5];

    if(((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DP_TX_LANE3_CR_DONE() & GET_DP_TX_LANE2_CR_DONE() & GET_DP_TX_LANE1_CR_DONE() & GET_DP_TX_LANE0_CR_DONE()) == _TRUE)) ||
       ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_TWO_LANE) && ((GET_DP_TX_LANE1_CR_DONE() & GET_DP_TX_LANE0_CR_DONE()) == _TRUE)) ||
       ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_ONE_LANE) && (GET_DP_TX_LANE0_CR_DONE() == _TRUE)))
    {
        return _DP_TX_TRAINING_PATTERN1_PASS;
    }

    switch(GET_DP_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            if(ScalerDpTxTP1Lane3Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpTxTP1Lane2Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpTxTP1Lane1Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpTxTP1Lane0Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_TWO_LANE:

            if(ScalerDpTxTP1Lane1Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpTxTP1Lane0Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_ONE_LANE:
        default:

            if(ScalerDpTxTP1Lane0Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;
    }

    return _DP_TX_TRAINING_PATTERN1_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane0 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxTP1Lane0Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE0_ADJUST_VOL_SWING() + GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE0_CURRENT_VOL_SWING() == GET_DP_TX_LANE0_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE0_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE0_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE0_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE0_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE0_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE0_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE0_CURRENT_VOL_SWING(GET_DP_TX_LANE0_ADJUST_VOL_SWING());
    SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE0_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane1 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxTP1Lane1Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE1_ADJUST_VOL_SWING() + GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE1_CURRENT_VOL_SWING() == GET_DP_TX_LANE1_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE1_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE1_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE1_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE1_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE1_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE1_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE1_CURRENT_VOL_SWING(GET_DP_TX_LANE1_ADJUST_VOL_SWING());
    SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE1_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane2 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxTP1Lane2Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE2_ADJUST_VOL_SWING() + GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE2_CURRENT_VOL_SWING() == GET_DP_TX_LANE2_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE2_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE2_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE2_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE2_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE2_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE2_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE2_CURRENT_VOL_SWING(GET_DP_TX_LANE2_ADJUST_VOL_SWING());
    SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE2_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane3 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxTP1Lane3Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE3_ADJUST_VOL_SWING() + GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE3_CURRENT_VOL_SWING() == GET_DP_TX_LANE3_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE3_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE3_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE3_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE3_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE3_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE3_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE3_CURRENT_VOL_SWING(GET_DP_TX_LANE3_ADJUST_VOL_SWING());
    SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE3_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane0  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTP2Lane0Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE0_CURRENT_VOL_SWING() + GET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE0_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE0_CURRENT_VOL_SWING(GET_DP_TX_LANE0_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE0_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane1  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTP2Lane1Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE1_CURRENT_VOL_SWING() + GET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE1_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE1_CURRENT_VOL_SWING(GET_DP_TX_LANE1_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE1_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane2  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTP2Lane2Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE2_CURRENT_VOL_SWING() + GET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE2_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE2_CURRENT_VOL_SWING(GET_DP_TX_LANE2_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE2_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane3  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTP2Lane3Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE3_CURRENT_VOL_SWING() + GET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE3_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE3_CURRENT_VOL_SWING(GET_DP_TX_LANE3_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE3_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training Link Rate Reduce
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxSignalReset(void)
{
    // Set Voltage Swing and pre-emphasis Variable to level 0
    CLR_DP_TX_TP1_LANE0_SAME_VOL_CNT();
    CLR_DP_TX_TP1_LANE1_SAME_VOL_CNT();
    CLR_DP_TX_TP1_LANE2_SAME_VOL_CNT();
    CLR_DP_TX_TP1_LANE3_SAME_VOL_CNT();

    SET_DP_TX_LANE0_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DP_TX_LANE1_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DP_TX_LANE2_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DP_TX_LANE3_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();

    // Clear TP2 Count
    CLR_DP_TX_TP2_CNT();

    ScalerGDIPhyTxMLPHYSet();
}

//--------------------------------------------------
// Description  : Dp Tx Aux PHY Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxAuxPHYSet(BYTE ucMode)
{
    if(ucMode == _DP_TX_AUX_SINGLE_MODE)
    {
        // Set Aux Tx LDO = 1.05V
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), (_DP_AUX_SWING_1050_MV << 5));

        // Set ADJR P
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Single End Mode and Enlarge Z0-P
        ScalerSetBit(PBD_62_AUX_2, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

        // Enable Enlarge Z0-N and Set ADJR-N = 0
        ScalerSetBit(PBD_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    }
    else
    {
        ScalerDpTxAuxSwingSetting();

        // Set ADJR P
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Disable Single End Mode and Enlarge Z0-P
        ScalerSetBit(PBD_62_AUX_2, ~(_BIT5 | _BIT0), _BIT0);

        // Disable Enlarge Z0-N and Set ADJR N
        ScalerSetBit(PBD_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1 | _BIT0));
    }

    // Set TX ADJR-P and ADJR-N
    ScalerSetByte(PBD_67_DIG_TX_03, 0xFF);
}

//--------------------------------------------------
// Description  : DP Tx Clone Output Process
// Input Value  : Input Port Type to be Cloned
// Output Value : None
//--------------------------------------------------
void ScalerDpTxCloneOutputProc(BYTE ucInputPort, BYTE ucPortType, bit bClone)
{
    // Do Nothing if Downstram unplug
    if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_UNPLUG)
    {
        return;
    }

    // Only do This when Input is not DP or DP MST is Off
    if((ucPortType != _PORT_DP) || (GET_REG_DP_RX_MST_ENABLE() == _DISABLE))
    {
        if(bClone == _FALSE)
        {
            // DebugMessageMst("Clone Off", 0);

            if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE)
            {
                ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);
            }
        }
        else
        {
            if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE) && (GET_DP_TX_EXCEED_LINK_BANDWIDTH() == _FALSE))
            {
                // Check if Input Port is Supported
                if(ScalerDpTxCloneCheckInputPortSupport(ucInputPort) == _FALSE)
                {
                    return;
                }

                // DebugMessageMst("ScalerDpTxCloneOutputProc", GET_DP_TX_STREAM_SOURCE());

                pData[0] = (GET_DP_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS() << 1);

                SET_DP_TX_DPCD_111(pData);

                // Link Training if Required
                if(((GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON) && (GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_TRAINING)) ||
                   (ScalerDpTxLinkStatusCheck() == _FAIL))
                {
                    // DebugMessageMst("Clone Mode Tx State Not Link ON", GET_DP_TX_MODE_STATE());

                    SET_DP_TX_FORCE_LINK_TRAINING();

                    return;
                }

                // Set Format Conversion for DP Tx Input
                ScalerDpTxCloneSwitchFormatConversionMux(ucInputPort);

                // Set Dp Tx Pixel Clk
                SET_DP_TX_INPUT_PIXEL_CLK(GET_INPUT_PIXEL_CLK());

                // DPTx CTS Fifo reset
                ScalerSetBit(PBB_D7_DPTX_CTSFIFO_CTRL, ~_BIT2, 0x00);
                ScalerSetBit(PBB_D7_DPTX_CTSFIFO_CTRL, ~_BIT2, _BIT2);

                // Get Tx Input Timing
                if(((ucPortType != _PORT_DP) && (ScalerDpTxMeasureInputInfo() == _TRUE)) ||
                   ((ucPortType == _PORT_DP) && (ScalerDpTxCloneCheckMSAInfo(ucInputPort) == _TRUE)))
                {
                    // DPTX Color Info Get
                    ScalerDpTxColorInfoSetting();

                    // Dp Tx Interlace info
                    ScalerDpTxInterlaceInfoSetting(ucInputPort, ucPortType);

                    if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
                    {
                        pData[4] = GET_COLOR_DEPTH();
                    }
                    else if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
                    {
                        pData[4] = GET_COLOR_DEPTH() * 2;
                    }
                    else
                    {
                        pData[4] = GET_COLOR_DEPTH() * 3;
                    }

                    // Get Link Bandwidth 0.1MHz
                    PDATA_DWORD(0) = (DWORD) GET_DP_TX_DOWNSTREAM_LANE_NUM() * _DP_TX_LINK_CLK_MHZ * 8 * 10;

                    // Check if Link BW is enough
                    if(PDATA_DWORD(0) >= ((DWORD) GET_DP_TX_INPUT_PIXEL_CLK() * pData[4] * 1006 / 1000))
                    {
                        ScalerDpTxSetStreamSource(_DP_TX_SOURCE_CLONE);
                    }
                    else
                    {
                        DebugMessageMst("Link BW is not enough for DP TX Clone", ((DWORD) GET_DP_TX_INPUT_PIXEL_CLK() * pData[4] * 1006 / 1000));

                        SET_DP_TX_EXCEED_LINK_BANDWIDTH();
                    }

                    DebugMessageMst("DP Tx Measure Done Set Source", GET_DP_TX_STREAM_SOURCE());
                }
            }
            else
            {
                // DebugMessageMst("No Clone!! Stream Source", GET_DP_TX_STREAM_SOURCE());

                if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON)
                {
                    DebugMessageMst("Tx Link Fail=> Reset Stream", GET_DP_TX_STREAM_SOURCE());

                    ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx MSA MISC0/MISC1 Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxColorInfoSetting(void)
{
    // Set Color Space
    switch(GET_COLOR_SPACE())
    {
        case _COLOR_SPACE_RGB:
        default:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
            break;

        case _COLOR_SPACE_YCBCR444:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
            break;

        case _COLOR_SPACE_YCBCR422:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
            break;

        case _COLOR_SPACE_YCBCR420:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR422);

            // Set Dp Tx Pixel Clk
            SET_DP_TX_INPUT_PIXEL_CLK(GET_DP_TX_INPUT_PIXEL_CLK() << 1);
            break;

        case _COLOR_SPACE_Y_ONLY:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
            break;

        case _COLOR_SPACE_RAW:
            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RAW);
            break;
    }

    DebugMessageMst("Get DP Tx Color Space", GET_DP_TX_INPUT_COLOR_SPACE());

    // Set Colorimetry
    SET_DP_TX_INPUT_COLORIMETRY(GET_COLORIMETRY());

    // Set Ext Colorimetry
    SET_DP_TX_INPUT_EXT_COLORIMETRY(GET_EXT_COLORIMETRY());

    // Set RGB Quantization Range
    SET_DP_TX_RGB_QUANTIZATION_RANGE(GET_COLOR_RGB_QUANTIZATION_RANGE());

    // Set YCC Quantization Range
    SET_DP_TX_YCC_QUANTIZATION_RANGE(GET_COLOR_YCC_QUANTIZATION_RANGE());

    // Set Color Depth
    if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_RAW)
    {
        switch(GET_COLOR_DEPTH())
        {
            case _COLOR_DEPTH_6_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x01);
                break;

            case _COLOR_DEPTH_7_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x02);
                break;

            case _COLOR_DEPTH_8_BITS:
            default:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x03);
                break;

            case _COLOR_DEPTH_10_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x04);
                break;

            case _COLOR_DEPTH_12_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x05);
                break;

            case _COLOR_DEPTH_14_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x06);
                break;

            case _COLOR_DEPTH_16_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x07);
                break;
        }
    }
    else
    {
        switch(GET_COLOR_DEPTH())
        {
            case _COLOR_DEPTH_6_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x00);
                break;

            case _COLOR_DEPTH_8_BITS:
            default:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x01);
                break;

            case _COLOR_DEPTH_10_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x02);
                break;

            case _COLOR_DEPTH_12_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x03);
                break;

            case _COLOR_DEPTH_16_BITS:
                SET_DP_TX_INPUT_COLOR_DEPTH(0x04);
                break;
        }
    }

    DebugMessageMst("Get DP Tx Color Depth", GET_DP_TX_INPUT_COLOR_DEPTH());
}

//--------------------------------------------------
// Description  : DP Tx Interlace Info Setting
// Input Value  : InputPort & PortType
// Output Value : None
//--------------------------------------------------
void ScalerDpTxInterlaceInfoSetting(BYTE ucInputPort, BYTE ucPortType)
{
    if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
    {
        SET_DP_TX_INPUT_INTERLACE_MODE(_ON);

        if(ucPortType != _PORT_DP)
        {
            SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(ScalerDpTxCloneCheckInterlaceVtotal());
        }
        else
        {
            // Set Dp Tx Vtotal Number By Dp Rx Vtotal Number Info
            switch(ucInputPort)
            {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

                case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                case _D6_INPUT_PORT:
#endif
                    SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(GET_DP_RX0_INTERLACE_VTOTAL_NUMBER());

                    break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                case _D1_INPUT_PORT:

                    SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(GET_DP_RX1_INTERLACE_VTOTAL_NUMBER());

                    break;
#endif

                default:
                    break;
            }
        }
    }
    else
    {
        SET_DP_TX_INPUT_INTERLACE_MODE(_OFF);
    }
}

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
//--------------------------------------------------
// Description  : DP Tx Clone Mode Switch
// Input Value  : Clone Mode on/off
// Output Value : None
//--------------------------------------------------
void ScalerDpTxCloneModeSwitch(bit bClone)
{
    SET_DP_TX_TARGET_CLONE_MODE(bClone);
    SET_DP_RX_CAPABILITY_SWITCHED();
}

//--------------------------------------------------
// Description  : DP Tx Block Status Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxBlockStatusCheck(void)
{
    if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_NO_PORT) && (GET_DP_TX_TARGET_CLONE_MODE() == _FALSE))
    {
        DebugMessageMst("8. Dp Tx Block OFF", 0);

        ScalerDpTxBlockStatusSet(_DISABLE);
    }
    else
    {
        DebugMessageMst("8. Dp Tx Block ON", 1);

        ScalerDpTxBlockStatusSet(_ENABLE);
    }
}

//--------------------------------------------------
// Description  : DP Tx Block Status Set
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpTxBlockStatusSet(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(GET_DP_TX_HPD_DETECTION_ENABLE() == _DISABLE)
        {
            // Clr All flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);

            // Enable Short IRQ and Disable Long IRQ
            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~(_BIT6 | _BIT5), _BIT6);

            // Enable HPD Detection
            ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, _BIT7);

            // For DP Tx HPD Proc Judge First HPD From Low to High
            SET_DP_TX_HPD_FIRST_PLUG();
        }
    }
    else
    {
        if(GET_DP_TX_HPD_DETECTION_ENABLE() == _ENABLE)
        {
            // Disable HPD Detection
            ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, 0x00);

            // Disable HPD IRQ
            ScalerSetByte(PBB_72_HPD_IRQ_EN, 0x00);

            // Clr All flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Dp Tx Get Downstream DP Plug Status
// Input Value  : None
// Output Value : _FALSE => _DP_UNPLUG or _TRUE => _DP_PLUG
//--------------------------------------------------
bit ScalerDpTxGetDownstreamHPDStatus(void)
{
    return (GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG);
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPHandler(void)
{
    CLR_DP_TX_HDCP_DOWNSTREAM_EVENT();

    if(ScalerSyncDpHdcpGetUpstreamEvent() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT)
    {
        CLR_DP_TX_HDCP_AUTH_START();

        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
    }
    else if(ScalerSyncDpHdcpGetUpstreamEvent() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS)
    {
        SET_DP_TX_HDCP_AUTH_START();

        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
    }
    else if(ScalerSyncDpHdcpGetUpstreamEvent() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION)
    {
        CLR_DP_TX_HDCP_AUTH_START();

        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
    }
    else if(GET_DP_TX_IRQ_HDCP_TYPE(_DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL) == _DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL)
    {
        CLR_DP_TX_IRQ_HDCP_TARGET_TYPE(_DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL);

        if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _TRUE)
        {
            ScalerDpTxHDCPEncryptSignalProc(_DISABLE);

            SET_DP_TX_HDCP_AUTH_START();

            ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
        }
    }
    else if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON)
    {
        if(GET_DP_TX_HDCP_AUTH_STATE() != _DP_TX_HDCP_STATE_IDLE)
        {
            ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
        }
    }

    if((GET_DP_TX_HDCP_AUTH_STATE() >= _DP_TX_HDCP_STATE_AUTH_2) && (GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE))
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        if((ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE) &&
           (GET_DP_TX_HDCP2_STOP_CONTENT_STREAM() == _FALSE))
#else
        if(ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE)
#endif
        {
            if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _FALSE)
            {
                ScalerDpTxHDCPEncryptSignalProc(_ENABLE);
            }
        }
        else
        {
            if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _TRUE)
            {
                ScalerDpTxHDCPEncryptSignalProc(_DISABLE);
            }
        }
    }

    switch(GET_DP_TX_HDCP_AUTH_STATE())
    {
        case _DP_TX_HDCP_STATE_IDLE:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();
                CLR_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT();
                CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT();
                CLR_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY();
                CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT();
                CLR_DP_TX_HDCP_AUTH_HOLD();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_TO_READ_R0);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_FOR_V_READY);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);

                ScalerDpTxHDCPEncryptSignalProc(_DISABLE);

                ScalerDpTxHDCPCheckDownstreamCapability();

                ScalerDpTxHDCPResetInfo();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                CLR_DP_TX_HDCP2_STOP_CONTENT_STREAM();
#endif
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
            {
                if((GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_ON) && (GET_DP_TX_HDCP_AUTH_START() == _TRUE))
                {
                    CLR_DP_TX_HDCP_AUTH_START();
                    CLR_DP_TX_IRQ_HDCP_TYPE();

                    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_AUTH_1);
                }
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_1:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();

                if(ScalerDpTxHDCPAuth1Proc() == _SUCCESS)
                {
                    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_AUTH_1_COMPARE_R0);
                }
                else
                {
                    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                }
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_1_COMPARE_R0:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();

                // Wait 100ms to read R0'
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_TO_READ_R0);

                SET_DP_TX_HDCP_AUTH_HOLD();
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_HOLD();
                CLR_DP_TX_IRQ_HDCP_TARGET_TYPE(_DP_TX_IRQ_HDCP_R0_AVAILABLE);

                if(ScalerDpTxHDCPAuth1CompareR0() == _SUCCESS)
                {
                    if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
                    {
                        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_AUTH_2);
                    }
                    else
                    {
                        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_AUTH_PASS);

                        SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS);
                    }
                }
                else
                {
                    SET_DP_TX_HDCP_AUTH_START();

                    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                }
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_2:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();

                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_FOR_V_READY);
                ScalerTimerActiveTimerEvent(SEC(0.25), _SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY() == _TRUE)
            {
                CLR_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY();
                CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT();

                if(ScalerDpTxHDCPPollingCpIrqType() == _DP_TX_IRQ_HDCP_V_READY)
                {
                    SET_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT();
                }
                else
                {
                    ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);
                }
            }

            if((GET_DP_TX_IRQ_HDCP_TYPE(_DP_TX_IRQ_HDCP_V_READY) == _DP_TX_IRQ_HDCP_V_READY) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT() == _TRUE))
            {
                CLR_DP_TX_IRQ_HDCP_TARGET_TYPE(_DP_TX_IRQ_HDCP_V_READY);

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_FOR_V_READY);

                if(ScalerDpTxHDCPCheckBinfo() == _TRUE)
                {
                    if(ScalerDpTxHDCPAuth2Proc() == _SUCCESS)
                    {
                        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_AUTH_PASS);

                        SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS);
                    }
                    else
                    {
                        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                    }
                }
                else
                {
                    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);

                    SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX);
                }
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT() == _TRUE)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);

                SET_DP_TX_HDCP_AUTH_START();

                ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_PASS:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();
            }

            if((ScalerGetByte(PBB_64_HDCP_ECF_BYTE0) != 0x7F) && (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST) && (GET_DP_TX_HDCP_ENCRYPT_STATUS() == _TRUE))
            {
                // Set ECF by FW
                ScalerSetByte(PBB_64_HDCP_ECF_BYTE0, 0x7F);
                ScalerSetByte(PBB_65_HDCP_ECF_BYTE1, 0xFF);
                ScalerSetByte(PBB_66_HDCP_ECF_BYTE2, 0xFF);
                ScalerSetByte(PBB_67_HDCP_ECF_BYTE3, 0xFF);
                ScalerSetByte(PBB_68_HDCP_ECF_BYTE4, 0xFF);
                ScalerSetByte(PBB_69_HDCP_ECF_BYTE5, 0xFF);
                ScalerSetByte(PBB_6A_HDCP_ECF_BYTE6, 0xFF);
                ScalerSetByte(PBB_6B_HDCP_ECF_BYTE7, 0xFF);

                // Double Buffer by ACT
                SET_REG_DP_RX_SEND_ACT_ENABLE();
            }

            if(GET_DP_TX_HDCP_AUTH_START() == _TRUE)
            {
                ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check Downstream HDCP Capability
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPCheckDownstreamCapability(void)
{
    CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
    CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER();

    if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG)
    {
        // Read HDCP capability from DPCD table of DownStream
        if(ScalerDpTxAuxNativeRead(0x06, 0x80, 0x28, 1, pData) == _TRUE)
        {
            // Check if Rx HDCP is capable
            if((pData[0] & _BIT0) == _BIT0)
            {
                SET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
            }

            // Check if Rx is repeater
            if((pData[0] & _BIT1) == _BIT1)
            {
                SET_DP_TX_HDCP_DOWNSTREAM_REPEATER();

                ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT4, _BIT4);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth1Proc(void)
{
    // Enable DP Tx HDCP Tx function .
    ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT0, _BIT0);

    // Step1: Read Bcap from DPCD
    ScalerDpTxAuxNativeRead(0x06, 0x80, 0x28, 1, pData);

    // Check if Downstream's HDCP is capable
    if((pData[0] & _BIT0) == _BIT0)
    {
        SET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
    }
    else
    {
        CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();

        return _FAIL;
    }

    // Check if Downstream is HDCP repeater
    if((pData[0] & _BIT1) == _BIT1)
    {
        SET_DP_TX_HDCP_DOWNSTREAM_REPEATER();

        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT4, _BIT4);
    }
    else
    {
        CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER();

        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT4, 0x00);
    }

    // Step2: Check Bksv
    if(ScalerDpTxHDCPAuth1CheckBksv() == _FAIL)
    {
        SET_DP_TX_HDCP_AUTH_START();

        return _FAIL;
    }

    // Step3: Generate An
    ScalerDpTxHDCPAuth1GenAn();

    // Step4: Write Akey and write Aksv
    ScalerDpTxHDCPAuth1WriteAnAkey();

    // Step5: Geneate Km,Ks,M0 and R0
    if(ScalerDpTxHDCPAuth1GenKm() == _FAIL)
    {
        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1 -Check Bksv
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth1CheckBksv(void)
{
    bit bResult = _FAIL;

    // Read Bksv
    ScalerDpTxAuxNativeRead(0x06, 0x80, 0x00, 5, pData);

    ScalerWrite(PBB_4F_BKSV_0, 5, pData, _AUTOINC);

    // Turn on circuit that check BKSV
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT2, _BIT2);

    if(ScalerTimerPollingFlagProc(5, PBB_56_DP_HDCP_TX, _BIT1, 1) == _SUCCESS)
    {
        bResult = (ScalerGetBit(PBB_56_DP_HDCP_TX, _BIT0) == 0x00) ? _SUCCESS : _FAIL;
    }
    else
    {
        bResult = _FAIL;
    }

    // Turn Off circuit that check BKSV
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT2, 0x00);

    return bResult;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1- Gen An
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPAuth1GenAn(void)
{
    // Write an_gen_start = 1 , and An gen start to run
    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT3, _BIT3);

    // Write reg_freerun_init an initial value
    ScalerSetByte(PBB_58_DP_HDCP_AN_SEED, TL2);

    // Write reg_freerun_init_en 0 to 1 to load init value
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT3, _BIT3);

    ScalerTimerDelayXms(2);

    // Write an_gen_start = 0 , An gen stop
    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT3, 0x00);

    // Disable load init value
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT3, 0x00);
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1- Gen Aksv
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPAuth1WriteAnAkey(void)
{
    BYTE ucI = 0;

    for(ucI = 0; ucI < 8; ucI++)
    {
        pData[ucI] = ScalerGetByte(PBB_3B_AN_BYTE_0 - ucI);
    }

    // Write An to Downstream DPCD
    ScalerDpTxAuxNativeWrite(0x06, 0x80, 0x0C, 8, pData);

    // Write Aksv to Downstream DPCD
    ScalerDpTxAuxNativeWrite(0x06, 0x80, 0x07, 5, g_pucHdcpAksvBackup);
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1 -Gen Km
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth1GenKm(void)
{
    bit bResult = _FAIL;

    // Turn on computation
    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT1, _BIT1);

    // Km = Akey over Bksv
    // (Ks,M0,R0) = Km,Repeater||An

    if(ScalerTimerPollingFlagProc(5, PBB_31_DPTX_HDCP_CTRL2, _BIT0, 1) == _SUCCESS)
    {
        bResult = _SUCCESS;
    }

    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT1, 0x00);

    return bResult;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1 Compare R0 and R0'
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth1CompareR0(void)
{
    BYTE ucCompareCounter = 0;

    do
    {
        // Read R0'
        ScalerDpTxAuxNativeRead(0x06, 0x80, 0x05, 2, pData);

        // Compare R0 and R0'
        if((ScalerGetByte(PBB_4C_R0_BYTE_LSB) == pData[0]) &&
           (ScalerGetByte(PBB_4B_R0_BYTE_MSB) == pData[1]))
        {
            return _SUCCESS;
        }

        ScalerTimerDelayXms(2);

        ucCompareCounter++;
    }
    while(ucCompareCounter < 3);

    return _FAIL;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth2Proc(void)
{
    BYTE ucCompareCounter = 0;

    do
    {
        // Load SHA-1 Input Data
        ScalerDpTxHDCPAuth2WriteShaInput();

        // Compare V and V'
        if(ScalerDpTxHDCPAuth2CompareV() == _SUCCESS)
        {
            return _SUCCESS;
        }

        ucCompareCounter++;
    }
    while(ucCompareCounter < 3);

    SET_DP_TX_HDCP_AUTH_START();

    return _FAIL;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2-Wrtie Data to SHA input
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPAuth2WriteShaInput(void)
{
    WORD usKsvFifoLength = GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() * 5;
    WORD usShaInputBitNumbers = 0;
    WORD usKsvLengthTemp = 0;

    // Read KSV FIFO List from Downstream Device
    do
    {
        ScalerDpTxAuxNativeRead(0x06, 0x80, 0x2C, ((usKsvFifoLength > 15) ? 15 : usKsvFifoLength), pData);

        usKsvLengthTemp = 0;

        do
        {
            g_pucDpTxHdcpKsvFifo[usShaInputBitNumbers] = pData[usKsvLengthTemp];

            usKsvLengthTemp++;
            usShaInputBitNumbers++;
        }
        while((usKsvLengthTemp < 15) && (usShaInputBitNumbers < usKsvFifoLength));
    }
    while(usShaInputBitNumbers < usKsvFifoLength);

    // Total bit numbers of SHA-1 input = the length of KSV FIFO + the length of B_info + the length of M0'
    usShaInputBitNumbers = (usKsvFifoLength + 2 + 8) * 8;

    // Reset SHA Block counter
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT1, _BIT1);

    // Start to Write SHA-1 Transform Input
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT1, 0x00);

    // Initialize The Index of KSV FIFO List
    usKsvLengthTemp = 0;

    // Write the KSV List into SHA-1 Transform Input
    do
    {
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 2]);
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 3]);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }
    while((usKsvFifoLength - usKsvLengthTemp) >= 4);

    // Write the remaining KSV, B info and M0' into SHA-1 Transform Input
    switch(usKsvFifoLength - usKsvLengthTemp)
    {
        case 1:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_M0_0());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_M0_1());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_M0_2());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_M0_3());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_M0_4());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_M0_5());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_M0_6());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_M0_7());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x80);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 2:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_M0_0());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_M0_1());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_M0_2());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_M0_3());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_M0_4());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_M0_5());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_M0_6());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_M0_7());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x80);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 3:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 2]);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_M0_0());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_M0_1());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_M0_2());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_M0_3());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_M0_4());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_M0_5());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_M0_6());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_M0_7());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x80);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        default:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_M0_0());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_M0_1());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_M0_2());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_M0_3());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_M0_4());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_M0_5());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_M0_6());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_M0_7());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x80);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;
    }

    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 60)
    {
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }

    // Write 0x00 into the remaining SHA-1 Transform Input space
    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) <= 56)
    {
        while((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) < 56)
        {
            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;
        }

        // The input length is equal to 2^64
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        // Write the valid bit numbers into SHA-1 Transform Input
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, HIBYTE(usShaInputBitNumbers));
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, LOBYTE(usShaInputBitNumbers));

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 8;

        ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
    }
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2 -SHA circuit Run
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPAuth2ShaRun(bit bIsFirst)
{
    // Set First Run For SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT3, ((bIsFirst == _TRUE) ? _BIT3 : 0x00));

    // Run SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT2, _BIT2);

    ScalerTimerPollingFlagProc(5, PBB_5B_DP_HDCP_TX_SHA_CTRL, _BIT4, _TRUE);

    // Disable First Run and Disable SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT3 | _BIT2), 0x00);
}

//--------------------------------------------------
// Description  : Check Binfo of Downstream port
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPCheckBinfo(void)
{
    // Read Binfo(Device Count and Depth)
    ScalerDpTxAuxNativeRead(0x06, 0x80, 0x2A, 2, pData);

    // Record Binfo of Downstream
    SET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE(pData[0]);
    SET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH(pData[1]);

    // Check if MAX_DEVS_EXCEEDED or MAX_CASCADE_EXCEEDED is 1 and then abort authentication
    if(((pData[0] & _BIT7) == _BIT7) || ((pData[1] & _BIT3) == _BIT3))
    {
        return _FAIL;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2 -Compare V and V'
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth2CompareV(void)
{
    BYTE ucSha1VHx = 0;
    BYTE ucIndex = 4;

    for(ucSha1VHx = 0; ucSha1VHx < 5; ucSha1VHx++)
    {
        ScalerDpTxAuxNativeRead(0x06, 0x80, (0x14 + (ucSha1VHx * 4)), 4, pData);

        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT7 | _BIT6 | _BIT5), ((ucIndex - ucSha1VHx) << 5));

        // Compare V with V'
        if((ScalerGetByte(PBB_63_DP_HDCP_TX_SHA_OUT_0) != pData[0]) ||
           (ScalerGetByte(PBB_62_DP_HDCP_TX_SHA_OUT_1) != pData[1]) ||
           (ScalerGetByte(PBB_61_DP_HDCP_TX_SHA_OUT_2) != pData[2]) ||
           (ScalerGetByte(PBB_60_DP_HDCP_TX_SHA_OUT_3) != pData[3]))
        {
            return _FAIL;
        }

        g_pucDpTxHdcpDownStreamV[(ucSha1VHx * 4)] = pData[0];
        g_pucDpTxHdcpDownStreamV[(ucSha1VHx * 4) + 1] = pData[1];
        g_pucDpTxHdcpDownStreamV[(ucSha1VHx * 4) + 2] = pData[2];
        g_pucDpTxHdcpDownStreamV[(ucSha1VHx * 4) + 3] = pData[3];
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Change HDCP Auth State
// Input Value  : Target HDCP Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHDCPChangeAuthState(EnumDPTxHDCPAuthState enumHDCPAuthState)
{
    SET_DP_TX_HDCP_AUTH_STATE(enumHDCPAuthState);
    SET_DP_TX_HDCP_AUTH_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Change HDCP Auth State to Compare R0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHDCPTimeoutToReadR0Event(void)
{
    SET_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT();
}

//--------------------------------------------------
// Description  : Waiting for V ready of downstream
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHDCPTimeoutForVReadyEvent(void)
{
    SET_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT();
}

//--------------------------------------------------
// Description  : Polling V ready of downstream
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHDCPPollingVReadyEvent(void)
{
    SET_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY();
}

//--------------------------------------------------
// Description  : Polling IRQ status of Downstream
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxTRQEventHDCPType ScalerDpTxHDCPPollingCpIrqType(void)
{
    ScalerDpTxAuxNativeRead(0x06, 0x80, 0x29, 1, pData);

    if((pData[0] & _BIT3) == _BIT3)
    {
        return _DP_TX_IRQ_HDCP_REAUTH_REQUEST;
    }
    else if((pData[0] & _BIT2) == _BIT2)
    {
        return _DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL;
    }
    else if((pData[0] & _BIT1) == _BIT1)
    {
        return _DP_TX_IRQ_HDCP_R0_AVAILABLE;
    }
    else if((pData[0] & _BIT0) == _BIT0)
    {
        return _DP_TX_IRQ_HDCP_V_READY;
    }

    return _DP_TX_IRQ_HDCP_NONE;
}

//--------------------------------------------------
// Description  : Enable HDCP TX Encryption
// Input Value  : _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPEncryptSignalProc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // HDCP encryption enable.
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT1, _BIT1);
    }
    else
    {
        // Disable HDCP function, Encryption and Reset Repeater Flag
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT1, 0x00);

        // Output MST type
        if(GET_DP_TX_MST_ENABLE() == _TRUE)
        {
            // Set ECF by FW
            ScalerSetByte(PBB_64_HDCP_ECF_BYTE0, 0x00);
            ScalerSetByte(PBB_65_HDCP_ECF_BYTE1, 0x00);
            ScalerSetByte(PBB_66_HDCP_ECF_BYTE2, 0x00);
            ScalerSetByte(PBB_67_HDCP_ECF_BYTE3, 0x00);
            ScalerSetByte(PBB_68_HDCP_ECF_BYTE4, 0x00);
            ScalerSetByte(PBB_69_HDCP_ECF_BYTE5, 0x00);
            ScalerSetByte(PBB_6A_HDCP_ECF_BYTE6, 0x00);
            ScalerSetByte(PBB_6B_HDCP_ECF_BYTE7, 0x00);

            // Double Buffer by ACT
            SET_REG_DP_RX_SEND_ACT_ENABLE();
        }
    }
}

//--------------------------------------------------
// Description  : Reset HDCP TX Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHDCPResetInfo(void)
{
    CLR_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE();
    CLR_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH();

    memset(g_pucDpTxHdcpKsvFifo, 0, sizeof(g_pucDpTxHdcpKsvFifo));
}

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset HDCP TX KSV Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHDCPResetKsvBackup(void)
{
    memset(g_pucDpTxHdcpKsvBackup, 0, sizeof(g_pucDpTxHdcpKsvBackup));
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Check DownStream Device is Same or not
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHDCPDownstreamBksvChange(void)
{
    // Read Bksv
    ScalerDpTxAuxNativeRead(0x06, 0x80, 0x00, 5, pData);

    // Compare Bksv
    if((g_pucDpTxHdcpKsvBackup[0] != pData[0]) ||
       (g_pucDpTxHdcpKsvBackup[1] != pData[1]) ||
       (g_pucDpTxHdcpKsvBackup[2] != pData[2]) ||
       (g_pucDpTxHdcpKsvBackup[3] != pData[3]) ||
       (g_pucDpTxHdcpKsvBackup[4] != pData[4]))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Generation of Dp Tx Connection Status Notify MSG Check
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
bit ScalerDpTxGenConnectStatusNotifyMsgCheck(void)
{
    if((GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1) == 0x00)
    {
        return _FALSE;
    }

    if(GET_DP_RX_MST_MODE_STATE() == _DP_RX_MST_MODE_STATUS_NONE_MSG)
    {
        return _FALSE;
    }

    if(GET_DP_TX_DOWNSTREAM_DPPLUG_CHANGE() == _FALSE)
    {
        if(GET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS() == GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS())
        {
            return _FALSE;
        }
        else
        {
            // Record Tx Status Change to Wait Safe interval time to issue Up Request MSG
            SET_DP_TX_DOWNSTREAM_DPPLUG_CHANGE();
        }
    }

    if((GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) && (GET_DP_TX_DOWNSTREAM_INFO_READY() == _FALSE))
    {
        return _FALSE;
    }

    if(ScalerDpRxMstCheckMsgBufferFree() != _TRUE)
    {
        return _FALSE;
    }

    CLR_DP_TX_DOWNSTREAM_DPPLUG_CHANGE();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Update Downstream Sink Count
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
bit ScalerDpTxSinkCountUpdate(void)
{
    // Read Sink Count
    if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0x00, 1, pData) == _TRUE)
    {
        SET_DP_TX_DOWNSTREAM_SINK_COUNT(pData[0] & 0xBF);
        SET_DP_TX_DOWNSTREAM_SINK_COUNT_CHANGE();

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get MSG Cap Status Change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpTxGetUpReqEnableStatusChange(void)
{
    if(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_NO_SUPPORT)
    {
        return _FALSE;
    }

    if(GET_DP_TX_DOWNSTREAM_DPCD_REV() < _DP_VERSION_1_2)
    {
        return _FALSE;
    }

    if(GET_DP_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS() == _FALSE)
    {
        if(g_enumDpMSTCapablePort == _DP_MST_NO_PORT)
        {
            return _FALSE;
        }

        if((bit)(GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1) == _TRUE)
        {
            return _TRUE;
        }
    }
    else
    {
        // Check if Tx is sending or waiting a MSG before clear 111h[1]
        if((GET_DP_GEN_DOWN_REQUEST_MSG() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE) ||
           (GET_DP_RX_SELF_GEN_DOWN_REQUEST_MSG() == _TRUE) || (GET_DP_TX_RECEIVED_MSG_COUNT() > 0))
        {
            return _FALSE;
        }

        if(g_enumDpMSTCapablePort == _DP_MST_NO_PORT)
        {
            return _TRUE;
        }

        if((bit)(GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1) == _FALSE)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Update DFP Device MSG Cap Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxUpdateDfpDeviceMsgCapFieldStatus(void)
{
    if(ScalerDpTxAuxNativeRead(0x00, 0x01, 0x11, 1, pData) == _TRUE)
    {
        pData[0] = (pData[0] & ~_BIT1) | ((!GET_DP_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS()) << 1);

        SET_DP_TX_DPCD_111(pData);

        // Clear Payload ID Only if Downstream PID Table is Not Empty
        if((GET_DP_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS() == _TRUE) && (GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_MST) &&
           (ScalerDpTxAuxNativeRead(0x00, 0x02, 0xC1, 1, pData) == _TRUE))
        {
            if(pData[0] != 0x00)
            {
                // Set Flag to Gen Clear ID Table Msg
                SET_DP_GEN_DOWN_REQUEST_MSG(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Downsteram Edid Bw Settinf
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxDownStreamEdidBwSetting(void)
{
    BYTE pucPixClkArray[2] = {0, 0};
    BYTE ucEdidOffset = 0x36;

    SET_DP_TX_EDID_BW(0);

    if(ScalerDpTxAuxI2CoverWrite(0x50, 1, &ucEdidOffset, 1) == _FALSE)
    {
        return;
    }

    if(ScalerDpTxAuxI2CoverRead(0x50, 2, pucPixClkArray, 0) == _FALSE)
    {
        return;
    }

    // Unit: 0.01M
    SET_DP_TX_EDID_BW((((WORD)pucPixClkArray[1] << 8) | pucPixClkArray[0]));

    DebugMessageMst("Dp Tx Port Downstream Edid Native Bw = ", GET_DP_TX_EDID_BW());
}

//--------------------------------------------------
// Description  : Get Dp Tx Edid Bandwith
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD ScalerDpTxGetDownStreamEdidBw(void)
{
    return GET_DP_TX_EDID_BW();
}

#endif // End for #if(_DP_TX_SUPPORT == _ON)
