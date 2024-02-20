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
// ID Code      : ScalerCommonDPRxMST.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_DPRXMST__

#include "ScalerCommonFunctionInclude.h"

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// DP MSG Timeout
//--------------------------------------------------
#define _DOWN_REPLY_MSG_TIME_OUT            SEC(0.5)
#define _UP_REQUEST_MSG_TIME_OUT            SEC(0.5)

//--------------------------------------------------
// DP Message Error Type
//--------------------------------------------------
#define GET_DP_RX_MSG_ERROR_TYPE()          (g_ucMsgErrorType)
#define SET_DP_RX_MSG_ERROR_TYPE(x)         (g_ucMsgErrorType = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DOWN_REPLY_MANUAL_MODE_SUPPORT == _ON)
BYTE g_ucDpDownReplyManualMsgCount;
BYTE g_ucDpDownReplyManualMsgLength;
BYTE g_ucDpDownReplyManualMsgBodyLengthMax;
#endif

EnumDPMSTPort g_enumDpMSTCapablePort = _DP_MST_NO_PORT;
EnumDpMstModeStatus g_enumDpMSTModeStatus = _DP_RX_MST_MODE_STATUS_NONE_MSG;
BYTE g_pucDpStreamToIdMapping[5];
BYTE g_ucRxEvent = _DP_RX_NONE_EVENT;
//BYTE g_ucMsgErrorType = _NONE_MSG_ERROR;
WORD g_usDpMstDdcRamSize = _EDID_SIZE_NONE;

#if(_DP_TX_SUPPORT == _ON)
BYTE g_ucTotalReceivedMsgCount;
BYTE g_ucSelfGenUpRequestRetry = _DP_MSG_NONE;
#endif

UnionDpRxReqStrct g_unDpRequestPool;
UnionDpRxRepStrct g_unDpReplyPool;
StructPoolUsageInfo g_stPoolUsage;
StructRxMsgFunctionInfo g_stMsgFunction;
StructRxMsgOtherInfo g_stMsgOtherInfo;
StructTimingInfo g_stTxInputTimingData;

// INT Used Flags
bit g_bDpRxReplyBufFree;
bit g_bCancelMsgTimeoutEvent;
bit g_bMst2SstEnable;
bit g_bDpRxDownReplyHPD;
bit g_bUpRequestBypassDone;
BYTE g_ucDpMstRxDownReplyRetryCount;

BYTE g_pucDPMsgQueryEncryptClientId[7];

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
bit g_bDpMSTD6Capable = _FALSE;
#endif

BYTE g_pucDpRxMstStreamMuxBackup[5];
bit g_bDpRxMstStreamMuxChange;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
//--------------------------------------------------
void ScalerDpRxMstPowerOnInitial(void);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
void ScalerDpRxMstInitial(EnumDPMSTPort enumRxMstPort);
void ScalerDpRxMstRx0Rx1switch(EnumDPMSTPort enumMstCapablePort);
#endif

void ScalerDpRxMstInfoBackup(BYTE ucInputPort, EnumDpMstBackup enumDpMstBackup);

void ScalerDpRxMstHandler(void);
void ScalerDpRxMstStreamsHandler(void);
void ScalerDpRxMstModeStatusCheck(void);
void ScalerDpRxMstMsgHandler(void);
void ScalerDpRxMstResetStream_EXINT0(void);
void ScalerDpRxMstIntHandle_EXINT0(void);
void ScalerDpRxMstDownRequestProc(void);
void ScalerDpRxMstDownReplyProc(void);
void ScalerDpRxMstDownRequestAnal(void);
void ScalerDpRxMstDownReplyAnal(void);

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRxMstUpRequestProc(void);
void ScalerDpRxMstUpReplyProc(void);
void ScalerDpRxMstUpRequestAnal(void);
void ScalerDpRxMstUpReplyAnal(void);
bit ScalerDpRxMstCheckMsgTransition(void);
void ScalerDpRxMstMsgCountResetEvent(void);
#endif

void ScalerDpRxMstMsgTimeoutEvent(void);
void ScalerDpRxMstDownRequestEventProc(void);
bit ScalerDpRxMstMsgAnalysis(void);
void ScalerDpRxMstDownReplyDirectlyMsg(void);
void ScalerDpRxMstIllegalMsgReply(void);
bit ScalerDpRxMstCheckMsgCRC(BYTE ucMSGDirection);
void ScalerDpRxMstSyncPayloadIDTable_EXINT0(void);
void ScalerDpRxMstStreamPositionSetting_EXINT0(void);
BYTE ScalerDpRxMstStreamMuxCheck(BYTE ucSourceNum);
BYTE ScalerDpRxMstStreamMuxCheck_EXINT0(BYTE ucSourceNum);
bit ScalerDpRxMstCheckMsgBufferFree(void);
bit ScalerDpRxMstCheckIDExisted(BYTE ucPayloadID);
BYTE ScalerDpRxMstCheckIDExisted_EXINT0(BYTE ucPayloadID);
BYTE ScalerDpRxMstGetExistedIDLength_EXINT0(BYTE ucPayloadID, BYTE ucStartPosition);
BYTE ScalerDpRxMstGetSyncTableAction_EXINT0(BYTE ucPayloadID);
BYTE ScalerDpRxMstCheckAddPoistionLegal_EXINT0(BYTE ucIDStartPosition);
void ScalerDpRxMstModifyPayloadTable_EXINT0(BYTE ucSearchStartPoint, BYTE ucSearchEndPoint, BYTE ucInitialID, BYTE ucDuplicateNum, BYTE ucPayloadID, bit bShiftDirection);
EnumDpStreamNum ScalerDpRxMstSearchMatchStream(BYTE ucTargetID);
EnumDpStreamNum ScalerDpRxMstSearchMatchStream_EXINT0(BYTE ucTargetID);
void ScalerDpRxMstCableUnplugReset(BYTE ucInputPort);
void ScalerDpRxMstStreamPositionReset(void);
void ScalerDpRxMstStreamMuxReset(void);
void ScalerDpRxMstStreamMuxBackup(EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumStreamNum);
void ScalerDpRxMstStreamMuxBackup_EXINT0(EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumStreamNum);
void ScalerDpRxMstClrStreamMuxBackup(void);
void ScalerDpRxMstClrStreamMuxBackup_EXINT0(void);
void ScalerDpRxMstStreamMuxRestore(EnumDpStreamSourceNum enumSourceNum);
void ScalerDpRxMstStreamMuxRestore_EXINT0(EnumDpStreamSourceNum enumSourceNum);

void ScalerDpRxMstStreamMuxChangeHandler(void);
void ScalerDpRxMstBackupInfoReset(void);

EnumDpVersionType ScalerDpRxMstGetDpVersion(void);
EnumDPMSTPort ScalerDpRxMstGetCapablePort(void);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
EnumSourceSearchPort ScalerDpRxMstGetInputPort(EnumDPMSTPort enumMstPort);
bit ScalerDpRxMstGetSrcMsgEnable(EnumSourceSearchPort enumInputPort);
bit ScalerDpRxMstGetMstCapability(EnumSourceSearchPort enumInputPort);
void ScalerDpRxMstCapabilitySwitch(EnumSourceSearchPort enumInputPort, bit bEn);
#if((_D0_DP_EXIST == _ON) && (_D1_DP_EXIST == _ON))
void ScalerDpRxMstCapabilitySwitch_EXINT0(EnumSourceSearchPort enumInputPort, bit bEn);
#endif
void ScalerDpRxMstInitial_EXINT0(EnumDPMSTPort enumRxMstPort);
#endif

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRxMstQueryEncryptionWriteShaInput(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
void ScalerDpRxMstQueryEncryptionWriteSha256Input(bit bRepeater);
#endif
void ScalerDpRxMstQueryEncryptionBackupClientId(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP MST Power-On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstPowerOnInitial(void)
{
    SET_DP_RX_MST_MODE_STATE(_DP_RX_MST_MODE_STATUS_NONE_MSG);

    SET_DP_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_DOWN_REQUEST_BUF0);

    // Free Request Array
    SET_DP_REQUEST_POOL_FREE();

    // Free Reply Array
    SET_DP_REPLY_POOL_FREE();

    // Free Reply Buffer
    SET_DP_RX_REPLY_BUF_FREE();

    ScalerDpRxMstClrStreamMuxBackup();

    // Enable MSG Force Ack Address Unexpect
    SET_REG_DP_RX_DOWN_REQUEST_FORCE_ACK_ADDRESS_UNEXPECT();
    SET_REG_DP_RX_UP_REPLY_FORCE_ACK_ADDRESS_UNEXPECT();

    // Enable BUF0 / BUF1 MSG Receive Double Buffer
    SET_REG_DP_RX_DOWN_REQUEST_MSG_DOUBLE_BUFFER_ENABLE();

    // Rx0 Down Requeset BUF0 / BUF1 MSG Receive and Header/ Body Crc Ignore Enable
    SET_REG_DP_RX_DOWN_REQUEST_MSG_RECEIVE_CRC_IGNORE_ENABLE();

    // Rx0 Up Reply BUF0 / BUF1 MSG Receive and Header/ Body Crc Ignore Enable
    SET_REG_DP_RX_UP_REPLY_MSG_RECEIVE_CRC_IGNORE_ENABLE();
}

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : DP Rx Msg Initial
// Input Value  : _DP_MST_RX0_PORT or _DP_MST_RX0_PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstInitial(EnumDPMSTPort enumRxMstPort)
{
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)

    if(enumRxMstPort == _DP_MST_RX6_PORT)
    {
        g_bDpMSTD6Capable = _TRUE;

#if(_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)
        enumRxMstPort = _DP_MST_RX0_PORT;
#endif
    }
    else
    {
        g_bDpMSTD6Capable = _FALSE;
    }
#endif

    ScalerDpMstReset(g_enumDpMSTCapablePort);

    g_enumDpMSTCapablePort = enumRxMstPort;

    SET_DP_RX_MST_MODE_STATE(_DP_RX_MST_MODE_STATUS_NONE_MSG);

    SET_DP_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_DOWN_REQUEST_BUF0);

    // Free Request Array
    SET_DP_REQUEST_POOL_FREE();

    // Free Reply Array
    SET_DP_REPLY_POOL_FREE();

    // Free Reply Buffer
    SET_DP_RX_REPLY_BUF_FREE();

    ScalerDpRxMstClrStreamMuxBackup();

    // Reset MSG FSM as 0x01000 Writen
    RST_REG_DP_RX_DOWN_REQUEST_FSM_WRITTEN();
    RST_REG_DP_RX_UP_REPLY_FSM_WRITTEN();

    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
    {
#if((_D0_DP_EXIST == _ON) && (_D1_DP_EXIST == _ON))
        // Rx1 Disable DPCD 111/1C2 IRQ
        ScalerSetBit(PBA_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);
#endif

#if(_D0_DP_EXIST == _ON)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if(g_bDpMSTD6Capable == _TRUE)
        {
            SET_DP_MST_DDCRAM_SIZE(_D6_EMBEDDED_DDCRAM_MAX_SIZE);
        }
        else
#endif
        {
            SET_DP_MST_DDCRAM_SIZE(_D0_EMBEDDED_DDCRAM_MAX_SIZE);
        }

        // Enable Buf0 / Buf1 Receive Capability
        SET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE();
        SET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE();
        SET_REG_DP_RX_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE();
        SET_REG_DP_RX_UP_REPLY_BUF1_MSG_RECEIVE_ENABLE();

        // Rx0 Clear DPCD 111/ 1C2 IRQ Flag
        ScalerSetBit(PB7_B3_AUX_SPECIAL_IRQ_FLAG, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

        // Rx0 Enable DPCD 111/1C2 IRQ
        ScalerSetBit(PB7_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

        // Rx0 Clear Payload ID Table
        ScalerSetBit(PB7_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, _BIT6);
        ScalerSetBit(PB7_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, 0x00);
#endif
    }
    else if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
#if((_D0_DP_EXIST == _ON) && (_D1_DP_EXIST == _ON))
        // Rx0 Disable DPCD 111/1C2 IRQ
        ScalerSetBit(PB7_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);
#endif

#if(_D1_DP_EXIST == _ON)

        SET_DP_MST_DDCRAM_SIZE(_D1_EMBEDDED_DDCRAM_MAX_SIZE);

        // Enable Buf0 / Buf1 Receive Capability
        SET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE();
        SET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE();
        SET_REG_DP_RX_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE();
        SET_REG_DP_RX_UP_REPLY_BUF1_MSG_RECEIVE_ENABLE();

        // Rx1 Clear DPCD 111/ 1C2 IRQ Flag
        ScalerSetBit(PBA_B3_AUX_SPECIAL_IRQ_FLAG, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

        // Rx1 Enable DPCD 111/1C2 IRQ
        ScalerSetBit(PBA_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

        // Rx1 Clear Payload ID Table
        ScalerSetBit(PBA_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, _BIT6);
        ScalerSetBit(PBA_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, 0x00);
#endif
    }
    else
    {
        CLR_DP_MST_DDCRAM_SIZE();

        // Disable Buf0 / Buf1 Receive Capability
        CLR_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE();
        CLR_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE();
        CLR_REG_DP_RX_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE();
        CLR_REG_DP_RX_UP_REPLY_BUF1_MSG_RECEIVE_ENABLE();

#if(_D0_DP_EXIST == _ON)
        // Rx0 Disable DPCD 111/1C2 IRQ
        ScalerSetBit(PB7_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);
#endif

#if(_D1_DP_EXIST == _ON)
        // Rx1 Disable DPCD 111/1C2 IRQ
        ScalerSetBit(PBA_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);
#endif
    }

    // Mst Port Select
    ScalerDpRxMstPortSel();

    // Mst MSG Port Select
    ScalerDpRxMstMsgPortSel();
}

//--------------------------------------------------
// Description  : Mst Rx0 Rx1 Capable Port
// Input Value  : _DP_MST_RX0_PORT or _DP_MST_RX1_PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstRx0Rx1switch(EnumDPMSTPort enumMstCapablePort)
{
    DebugMessageMst("MST Rx0 Rx1 Switch to", enumMstCapablePort);

    SET_DP_RX_TARGET_MST_PORT(enumMstCapablePort);
    SET_DP_RX_CAPABILITY_SWITCHED();
}
#endif

//--------------------------------------------------
// Description  : Backup MST Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstInfoBackup(BYTE ucInputPort, EnumDpMstBackup enumDpMstBackup)
{
    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)
        case _D0_INPUT_PORT:
            ScalerDpRx0MstInfoBackup(enumDpMstBackup);
            break;
#endif

#if(_D1_DP_EXIST == _ON)
        case _D1_INPUT_PORT:
            ScalerDpRx1MstInfoBackup(enumDpMstBackup);
            break;
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:
            ScalerDpRx6MstInfoBackup(enumDpMstBackup);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp Message Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstHandler(void)
{
    if(g_enumDpMSTCapablePort == _DP_MST_NO_PORT)
    {
#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
        if(GET_DP_GEN_DOWN_REQUEST_MSG() == _DP_MSG_NONE)
#endif
        {
            return;
        }
    }

    ScalerDpRxMstModeStatusCheck();
    ScalerDpRxMstMsgHandler();
}

//--------------------------------------------------
// Description  : Dp Multi-Stream Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstStreamsHandler(void)
{
    if(g_enumDpMSTCapablePort == _DP_MST_NO_PORT)
    {
        return;
    }

#if(_DP_TX_SUPPORT == _ON)

    if(GET_DP_RX_MST2SST_ENABLE() == _ENABLE)
    {
#if((_D0_DP_EXIST == _ON) && (_D1_DP_EXIST == _ON))

        if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
        {
            ScalerDpRx0MstToSstProc();
        }
        else
        {
            ScalerDpRx1MstToSstProc();
        }

#elif(_D0_DP_EXIST == _ON)

        ScalerDpRx0MstToSstProc();

#elif(_D1_DP_EXIST == _ON)

        ScalerDpRx1MstToSstProc();

#endif
    }
#endif
}

//--------------------------------------------------
// Description  : Rx MST Mode Status Check for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstModeStatusCheck(void)
{
    switch(GET_DP_RX_MST_MODE_STATE())
    {
        case _DP_RX_MST_MODE_STATUS_NONE_MSG:

            break;

        case _DP_RX_MST_MODE_STATUS_BUILD_TOPOLOGY:

            if(ScalerDpRxMstCheckMsgBufferFree() == _TRUE)
            {
                SET_DP_RX_MST_MODE_STATE(_DP_RX_MST_MODE_STATUS_ALLOCATED_PBN);
            }

            break;

        case _DP_RX_MST_MODE_STATUS_ALLOCATED_PBN:

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Rx Mst Msg Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstMsgHandler(void)
{
    ScalerDpRxMstDownRequestProc();
    ScalerDpRxMstDownRequestAnal();
    ScalerDpRxMstDownRequestEventProc();

    ScalerDpRxMstDownReplyAnal();
    ScalerDpRxMstDownReplyProc();

#if(_DP_TX_SUPPORT == _ON)
    ScalerDpRxMstUpRequestProc();
    ScalerDpRxMstUpRequestAnal();

    ScalerDpRxMstUpReplyAnal();
    ScalerDpRxMstUpReplyProc();
#endif
}

//--------------------------------------------------
// Description  : DP Rx Mst reset stream
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstResetStream_EXINT0(void) using 1
{
    // Reset Stream ID Mapping Table
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 5; pData_EXINT[0]++)
    {
        g_pucDpStreamToIdMapping[pData_EXINT[0]] = 0;
    }

    // --- Reset Rx0 ---
    // Clear Payload ID Table
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

    // Reset ST1_Source ~ ST5_Source
    ScalerDpRxMstClrStreamMuxBackup_EXINT0();

    // Reset Daisy Chain ST3 ~ ST5
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 3; pData_EXINT[0]++)
    {
        // Reset Start Position
        ScalerSetByte_EXINT(RET_REG_ADDR_DP_RX0_DAIZY_ST3_START() + (pData_EXINT[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte_EXINT(RET_REG_ADDR_DP_RX0_DAIZY_ST3_END() + (pData_EXINT[0] << 1), 0x00);
    }

    // --- Reset Rx1 ---
    // Clear Payload ID Table
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

    // Reset ST1_Source ~ ST5_Source
    ScalerSetBit_EXINT(PB8_0D_SOURCE_SEL_0, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(PB8_0D_SOURCE_SEL_0, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB8_0E_SOURCE_SEL_1, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(PB8_0E_SOURCE_SEL_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB8_0F_SOURCE_SEL_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Reset Daisy Chain ST3 ~ ST5
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 3; pData_EXINT[0]++)
    {
        // Reset Start Position
        ScalerSetByte_EXINT(RET_REG_ADDR_DP_RX1_DAIZY_ST3_START() + (pData_EXINT[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte_EXINT(RET_REG_ADDR_DP_RX1_DAIZY_ST3_END() + (pData_EXINT[0] << 1), 0x00);
    }

#if(_DP_TX_SUPPORT == _ON)
    ScalerDpTxSetStreamSource_EXINT0(_DP_TX_SOURCE_NONE);

    SET_DP_RX_MST2SST_ENABLE(_DISABLE);

#endif
}

//--------------------------------------------------
// Description  : Rx MSG INT Handle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstIntHandle_EXINT0(void) using 1
{
    // Write 002003h Bit4 into INT0 (Down Reply Ready Bit)
    if((GET_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ() == _ENABLE) &&
       (GET_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ_FLAG() == _TRUE))
    {
        // Disable Down Reply Ready Bit IRQ
        CLR_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ();

        // Clear Flag
        CLR_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ_FLAG();

        // Set MSG Timer Flag
        SET_DP_RX_CANCEL_MSG_TIMEOUT_EVENT();

#if(_DOWN_REPLY_MANUAL_MODE_SUPPORT == _OFF)
        // Last Sideband MSG Have Been Read
        if(GET_REG_DP_RX_DOWN_REPLY_BUFFER_END_FLAG() == _TRUE)
        {
            // Message Upstream Disable
            CLR_REG_DP_RX_UPSTREAM_REPLY();

            // Free Reply Buffer
            SET_DP_RX_REPLY_BUF_FREE();
        }
        else
        {
            // HPD Event
            SET_DP_RX_DOWN_REPLY_SET_HPD();
        }
#else
        // Check Down Reply MSG Fragment Has Been Read
        if(GET_REG_DP_RX_DOWN_REPLY_MSG_IS_READ_EXINT() == _TRUE)
        {
            CLR_REG_DP_RX_DOWN_REPLY_MSG_IS_READ_EXINT();

            if(g_ucDpDownReplyManualMsgCount == 0)
            {
                // Message Upstream Disable
                CLR_REG_DP_RX_UPSTREAM_REPLY();

                // Free Reply Buffer
                SET_DP_RX_REPLY_BUF_FREE();
            }
            else
            {
                // Disable Upstream
                CLR_REG_DP_RX_UPSTREAM_REPLY();

                if(g_ucDpDownReplyManualMsgCount == 1)
                {
                    // Set Manual Mode Body Length
                    SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(g_ucDpDownReplyManualMsgLength);

                    g_ucDpDownReplyManualMsgLength = 0;

                    // Clear Start Bit
                    CLR_REG_DP_RX_UPSTREAM_START_BIT();

                    // Set End Bit
                    SET_REG_DP_RX_UPSTREAM_END_BIT();
                }
                else if(g_ucDpDownReplyManualMsgCount > 1)
                {
                    // Set Manual Mode Body Length
                    SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(g_ucDpDownReplyManualMsgBodyLengthMax);

                    g_ucDpDownReplyManualMsgLength = g_ucDpDownReplyManualMsgLength - g_ucDpDownReplyManualMsgBodyLengthMax;

                    // Clear Start Bit
                    CLR_REG_DP_RX_UPSTREAM_START_BIT();

                    // Clear End Bit
                    CLR_REG_DP_RX_UPSTREAM_END_BIT();
                }

                // Enable Upstream
                SET_REG_DP_RX_UPSTREAM_REPLY();

                g_ucDpDownReplyManualMsgCount = g_ucDpDownReplyManualMsgCount - 1;

                // HPD Event
                SET_DP_RX_DOWN_REPLY_SET_HPD();
            }
        }
        else
        {
            // Enable Upstream
            SET_REG_DP_RX_UPSTREAM_REPLY();

            // HPD Event
            SET_DP_RX_DOWN_REPLY_SET_HPD();
        }
#endif
    }

#if(_DP_TX_SUPPORT == _ON)
    // Write 002003h Bit5 into INT0 (Up Request Ready Bit)
    if((GET_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ() == _ENABLE) &&
       (GET_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ_FLAG() == _TRUE))
    {
        // Disable UP_REQ_MSG_RDY Bit INT
        CLR_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ();

        // Clear Flag
        CLR_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ_FLAG();

        // Set MSG Timer Flag
        SET_DP_RX_CANCEL_MSG_TIMEOUT_EVENT();

        // Message Upstream Disable
        CLR_REG_DP_RX_UPSTREAM_REPLY();

        // Free Reply Buffer
        SET_DP_RX_REPLY_BUF_FREE();

        if((GET_REG_DP_RX_DOWN_REPLY_BUFFER_END_FLAG() == _TRUE) && (GET_DP_RX_UP_REQUEST_RETRY_NUM() != 0))
        {
            // Set Up Request Bypass Done Flag
            SET_DP_RX_UP_REQUEST_BYPASS_DONE();
        }
    }
#endif

    // DPCD Write 111h
    if((GET_REG_DP_RX_111_IRQ() == _ENABLE) &&
       (GET_REG_DP_RX_111_IRQ_FLAG() == _TRUE))
    {
        // CLR Flag
        CLR_REG_DP_RX_111_IRQ_FLAG();

        if((GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x01, 0x11) & _BIT0) == _BIT0)
        {
            // Enable MST
            SET_REG_DP_RX_MST_ENABLE();

            // Enable Ignore Rx Error
            SET_REG_DP_IGNORE_RX_ERROR();
        }
        else
        {
            // Disable MST
            CLR_REG_DP_RX_MST_ENABLE();
            ScalerDpRxMstResetStream_EXINT0();

            // Disable Rx Igrone Error
            CLR_REG_DP_IGNORE_RX_ERROR();
        }
    }

    // Manual to Set ACT Flag to Avoid HW Missed ACT as Source Read 0x002C0
    if((GET_REG_DP_RX_2C0_IRQ() == _ENABLE) &&
       (GET_REG_DP_RX_2C0_IRQ_FLAG() == _TRUE))
    {
        CLR_REG_DP_RX_2C0_IRQ_FLAG();

        if(((GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0) & _BIT0) == _BIT0) ||
           (GET_DP_RX_MANUAL_FORCE_SET_ACT() == _TRUE))
        {
            // Aux Hardware Control
            SET_REG_DP_RX_AUX_TO_AUTO_MODE_EXINT();

            SET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0, (GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0) | _BIT1));
        }
    }

    // DPCD Write 1C2h
    if((GET_REG_DP_RX_1C2_IRQ() == _ENABLE) &&
       (GET_REG_DP_RX_1C2_IRQ_FLAG() == _TRUE))
    {
        if((GET_REG_DP_RX_MST_ENABLE() == _FALSE) &&
           !((GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x01, 0xC0) == 0x00) &&
             (GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x01, 0xC1) == 0x00) &&
             (GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x01, 0xC2) == 0x3F)))
        {
            if((GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x01, 0x11) & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0))
            {
                pData_EXINT[0] = (GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x01, 0x11) | _BIT1 | _BIT0);

                SET_REG_DP_RX_AUX_TO_MANUAL_MODE_EXINT();

                SET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x01, 0x11, pData_EXINT[0]);

                // CLR 0x111 IRQ Flag
                CLR_REG_DP_RX_111_IRQ_FLAG();

                SET_REG_DP_RX_AUX_TO_AUTO_MODE_EXINT();
            }

            // Enable MST
            SET_REG_DP_RX_MST_ENABLE();
        }

        // CLR Flag
        CLR_REG_DP_RX_1C2_IRQ_FLAG();

        // Aux Hardware Control
        SET_REG_DP_RX_AUX_TO_AUTO_MODE_EXINT();

        ScalerDpRxMstSyncPayloadIDTable_EXINT0();
    }
}

//--------------------------------------------------
// Description  : Rx Down Request MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstDownRequestProc(void)
{
    if(GET_DP_RX_DOWN_REQ_BUF_RELEASE() == _TRUE)
    {
        // Clear Flag
        CLR_DP_RX_DOWN_REQ_BUF_RELEASE();

        if(GET_DP_RX_DOWN_REQUEST_BUF_PRIORITY() == _DP_DOWN_REQUEST_BUF0)
        {
            // Clear Flag
            CLR_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH();

            // Clear BUF0
            CLR_REG_DP_RX_DOWN_REQUEST_BUF0();

            // Defer Any Other MSGs to Prevent Priority and Using Buf Conflict
            SET_REG_DP_RX_AUX_TO_MANUAL_MODE();

            if((GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) || (GET_REG_DP_RX_DOWN_REQUEST_BUF1_WRITE_PTR() != 0x00))
            {
                CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();

                SET_DP_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_DOWN_REQUEST_BUF1);
            }
            else
            {
                SET_DP_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_DOWN_REQUEST_BUF0);
            }

            // Enable BUF0 to Receive MSG
            SET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE();

            SET_REG_DP_RX_AUX_TO_AUTO_MODE();
        }
        else
        {
            // Clear BUF1
            CLR_REG_DP_RX_DOWN_REQUEST_BUF1();

            // Enable BUF1 to Receive MSG
            SET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE();

            SET_DP_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_DOWN_REQUEST_BUF0);
        }
    }

    if(GET_DP_RX_DOWN_REQUEST_BUF_PRIORITY() == _DP_DOWN_REQUEST_BUF0)
    {
        if((GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH() == _TRUE) && (GET_DP_REQUEST_POOL_FREE() == _TRUE))
        {
            // Clear Request Array Free Flag
            CLR_DP_REQUEST_POOL_FREE();

            // Clear Flag
            CLR_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH();

            // Set BUF0 Read PTR to 0
            SET_REG_DP_RX_DOWN_REQUEST_BUF0_READ_PTR(0);

            // Move BUF0 Down Request MSG to Request Array
            for(pData[0] = 0; pData[0] < GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_LENGTH(); pData[0]++)
            {
                SET_DP_MSG_REQUEST_ARRAY(pData[0], GET_REG_DP_RX_DOWN_REQUEST_BUF0_DATA());
            }

            // Select To Header 0
            SET_REG_DP_RX_DOWN_REQUEST_HEADER0_INFO();

            // Analysis Down Request MSG
            SET_DP_RX_DOWN_REQUEST_ANAL();
        }
    }
    else
    {
        if((GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH() == _TRUE) && (GET_DP_REQUEST_POOL_FREE() == _TRUE))
        {
            // Clear Request Array Free Flag
            CLR_DP_REQUEST_POOL_FREE();

            // Clear Flag
            CLR_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH();

            // Set BUF1 Read PTR to Zero
            SET_REG_DP_RX_DOWN_REQUEST_BUF1_READ_PTR(0);

            // Move BUF1 Down Request MSG to Request Array
            for(pData[0] = 0; pData[0] < GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_LENGTH(); pData[0]++)
            {
                SET_DP_MSG_REQUEST_ARRAY(pData[0], GET_REG_DP_RX_DOWN_REQUEST_BUF1_DATA());
            }

            // Select to Header 1
            SET_REG_DP_RX_DOWN_REQUEST_HEADER1_INFO();

            // Analysis Down Request MSG
            SET_DP_RX_DOWN_REQUEST_ANAL();
        }
    }

    // Prevent MSG BUF0 FSM Dead Lock
    if((GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_ERROR() != _NONE_MSG_ERROR) && (GET_DP_RX_DOWN_REQUEST_ANAL() == _FALSE))
    {
        SET_REG_DP_RX_AUX_TO_MANUAL_MODE();

        CLR_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_ERROR();

        CLR_REG_DP_RX_DOWN_REQUEST_BUF0();

        SET_REG_DP_RX_AUX_TO_AUTO_MODE();
    }

    // Prevent MSG BUF1 FSM Dead Lock
    if((GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_ERROR() != _NONE_MSG_ERROR) && (GET_DP_RX_DOWN_REQUEST_ANAL() == _FALSE))
    {
        SET_REG_DP_RX_AUX_TO_MANUAL_MODE();

        CLR_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_ERROR();

        CLR_REG_DP_RX_DOWN_REQUEST_BUF1();

        SET_REG_DP_RX_AUX_TO_AUTO_MODE();
    }
}

//--------------------------------------------------
// Description  : Rx Down Reply MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstDownReplyProc(void)
{
    if(GET_DP_RX_CANCEL_MSG_TIMEOUT_EVENT() == _TRUE)
    {
        // Clear Flag
        CLR_DP_RX_CANCEL_MSG_TIMEOUT_EVENT();

        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT);
    }

    if(GET_DP_RX_DOWN_REPLY_READY() == _TRUE)
    {
        // CLR Down Reply Ready Flag
        CLR_DP_RX_DOWN_REPLY_READY();

        if(GET_DP_MST_RX_CABLE_STATUS() == _TRUE)
        {
            if(GET_DP_MSG_REPLY_ID() == _DP_MSG_LINK_ADDRESS)
            {
                if(GET_DP_RX_MST_MODE_STATE() != _DP_RX_MST_MODE_STATUS_BUILD_TOPOLOGY)
                {
                    SET_DP_RX_MST_MODE_STATE(_DP_RX_MST_MODE_STATUS_BUILD_TOPOLOGY);
                }

#if(_DP_TX_SUPPORT == _ON)
                if((GET_REG_DP_RX_UPSTREAM_REPLY_LCT() != 1) && (GET_REG_DP_RX_UPSTREAM_REPLY_LCR() == 0))
                {
                    CLR_DP_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();
                }
#endif
            }

            if((GET_DP_MSG_REPLY_ID() == _DP_MSG_ALLOCATE_PAYLOAD) && (GET_DP_RX_MST_MODE_STATE() != _DP_RX_MST_MODE_STATUS_ALLOCATED_PBN))
            {
                SET_DP_RX_MST_MODE_STATE(_DP_RX_MST_MODE_STATUS_ALLOCATED_PBN);
            }

            // CLR Write Pointer to 0
            CLR_REG_DP_RX_UPSTREAM_REPLY_WRITE_PTR();

            // CLR Read Pointer to 0
            CLR_REG_DP_RX_USTERAM_REPLY_BUF();

            for(pData[0] = 0; pData[0] < GET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(); pData[0]++)
            {
                // Fill Reply Msg into Buffer
                SET_REG_DP_RX_UPSTREAM_REPLY_BUF_DATA(GET_DP_MSG_REPLY_ARRAY(pData[0]));
            }

            // Free Reply Array
            SET_DP_REPLY_POOL_FREE();

            // Select to Down Reply BUF Address
            SET_REG_DP_RX_UPSTREAM_REPLY_DOWN_REPLY_ADDRESS();

#if(_DOWN_REPLY_MANUAL_MODE_SUPPORT == _OFF)

            // Set Start and End Bit to HW Auto Mode
            SET_REG_DP_RX_UPSTREAM_HW_AUTO_MODE();
#else

            // Body length max = total length max - header length - 1byte body CRC
            // Header length = 3 + ((LCT - 1) / 2)
            g_ucDpDownReplyManualMsgBodyLengthMax = _DOWN_REPLY_MANUAL_MODE_MAX_LEN - (4 + ((GET_REG_DP_RX_UPSTREAM_REPLY_LCT() - 1) / 2) + ((GET_REG_DP_RX_UPSTREAM_REPLY_LCT() - 1) % 2));

            g_ucDpDownReplyManualMsgLength = GET_REG_DP_RX_UPSTREAM_REPLY_LENGTH();

            g_ucDpDownReplyManualMsgCount = (g_ucDpDownReplyManualMsgLength / g_ucDpDownReplyManualMsgBodyLengthMax) + (((g_ucDpDownReplyManualMsgLength % g_ucDpDownReplyManualMsgBodyLengthMax) > 0) ? 1 : 0);

            if(g_ucDpDownReplyManualMsgLength > g_ucDpDownReplyManualMsgBodyLengthMax)
            {
                // Set Start and End Bit to Manual Mode
                SET_REG_DP_RX_UPSTREAM_HW_MANUAL_MODE();

                // Set Start Bit
                SET_REG_DP_RX_UPSTREAM_START_BIT();

                // Clear End Bit
                CLR_REG_DP_RX_UPSTREAM_END_BIT();

                // Set Manual Mode Body Length
                SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(g_ucDpDownReplyManualMsgBodyLengthMax);

                g_ucDpDownReplyManualMsgLength = g_ucDpDownReplyManualMsgLength - g_ucDpDownReplyManualMsgBodyLengthMax;
            }
            else
            {
                // Set Start and End Bit to HW Auto Mode
                SET_REG_DP_RX_UPSTREAM_HW_AUTO_MODE();

                // Set Manual Mode Body Length
                SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(g_ucDpDownReplyManualMsgLength);

                g_ucDpDownReplyManualMsgLength = 0;
            }

            g_ucDpDownReplyManualMsgCount = g_ucDpDownReplyManualMsgCount - 1;

            // Clear Down Reply Is Read Flag
            CLR_REG_DP_RX_DOWN_REPLY_MSG_IS_READ();
#endif

            // Message Upstream Enable
            SET_REG_DP_RX_UPSTREAM_REPLY();

            // CLR DOWN_REP_MSG_RDY IRQ Flag
            CLR_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ_FLAG();

            // Enable DOWN_REP_MSG_RDY IRQ
            SET_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ();

            // Set Down Reply MSG Ready Bit of DPCD Table
            SET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03, (GET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03) | _BIT4));

            // Gen HPD With Duration 1 ms
            SET_DP_MST_HPD_IRQ();

            // Set Timer Event
            ScalerTimerActiveTimerEvent(_DOWN_REPLY_MSG_TIME_OUT, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT);

            g_ucDpMstRxDownReplyRetryCount = 0;

#if(_DP_TX_SUPPORT == _ON)
            // Delete DownRequest Msg Count
            if(GET_DP_TOTAL_RECEIVED_MSG_COUNT() > 0)
            {
                SET_DP_TOTAL_RECEIVED_MSG_COUNT(GET_DP_TOTAL_RECEIVED_MSG_COUNT() - 1);

                if(GET_DP_TOTAL_RECEIVED_MSG_COUNT() == 0)
                {
                    // Cancel Timer Event
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
                }
            }
#endif
        }
        else
        {
            if(GET_DP_REPLY_POOL_FREE() == _FALSE)
            {
                // Free Reply Array
                SET_DP_REPLY_POOL_FREE();
            }

            if(GET_DP_RX_REPLY_BUF_FREE() == _FALSE)
            {
                // Free Reply Buffer
                SET_DP_RX_REPLY_BUF_FREE();
            }
        }
    }

    if(GET_DP_RX_DOWN_REPLY_SET_HPD() == _TRUE)
    {
        CLR_DP_RX_DOWN_REPLY_SET_HPD();

        // CLR DOWN_REP_MSG_RDY IRQ Flag
        CLR_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ_FLAG();

        // Enable DOWN_REP_MSG_RDY IRQ
        SET_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ();

        // Set Down Reply Message Ready Bit of DPCD Table
        SET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03, (GET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03) | _BIT4));

        // Gen HPD With Duration 1 ms
        SET_DP_MST_HPD_IRQ();

        // Set Timer Event
        ScalerTimerReactiveTimerEvent(_DOWN_REPLY_MSG_TIME_OUT, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT);

        g_ucDpMstRxDownReplyRetryCount = 0;
    }
}

//--------------------------------------------------
// Description  : Rx Down Request MSG Analysis for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstDownRequestAnal(void)
{
    if(GET_DP_RX_DOWN_REQUEST_ANAL() == _TRUE)
    {
        if(ScalerDpRxMstCheckMsgCRC(_DP_DOWN_REQUEST_MSG) == _TRUE)
        {
            // Analyze Down Request MSG
            if(ScalerDpRxMstMsgAnalysis() == _TRUE)
            {
#if(_DP_TX_SUPPORT == _ON)
                // Count DownRequest Msg
                if(GET_DP_TOTAL_RECEIVED_MSG_COUNT() < 255)
                {
                    SET_DP_TOTAL_RECEIVED_MSG_COUNT(GET_DP_TOTAL_RECEIVED_MSG_COUNT() + 1);
                }

                ScalerTimerReactiveTimerEvent(SEC(10), _SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
#endif
                // CLR Flag
                CLR_DP_RX_DOWN_REQUEST_ANAL();
            }
        }
        else
        {
            // CRC Error
            SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();

            // CLR Flag
            CLR_DP_RX_DOWN_REQUEST_ANAL();
        }
    }

#if(_DP_TX_SUPPORT == _ON)
    // Generate Clear ID Table to Downstream if Uptream is Disconnected
    if((GET_DP_GEN_DOWN_REQUEST_MSG() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE) && (GET_DP_REQUEST_POOL_FREE() == _TRUE))
    {
        // Set Gen Msg to None
        CLR_DP_GEN_DOWN_REQUEST_MSG();

        // Occupy Request Memory Pool
        CLR_DP_REQUEST_POOL_FREE();

        //=== Set Header Info.===
        // Set LCT
        SET_REG_DP_TX_DOWNSTREAM_MSG_LCT(1);

        // Set LCR
        SET_REG_DP_TX_DOWNSTREAM_MSG_LCR(6);

        // Set Broadcast Bit
        SET_REG_DP_TX_DOWNSTREAM_MSG_BROADCAST(_TRUE);

        // Set Path Bit
        SET_REG_DP_TX_DOWNSTREAM_MSG_PATH(_TRUE);

        // Set TX MSG Write Total Length
        SET_REG_DP_TX_DOWNSTREAM_MSG_LENGTH(1);

        // Set MSN Bit
        SET_REG_DP_TX_DOWNSTREAM_MSG_MSN(0);

        //=== Set Body Info.===
        // Set Down Request ID
        SET_DP_DOWN_REQUEST_CLEAR_ID_TABLE_MSG_REQUEST_ID(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);

        // Set Dp Tx Down Request Analysis
        SET_DP_TX_DOWN_REQUEST_ANAL();

        SET_DP_RX_SELF_GEN_DOWN_REQUEST_MSG();
    }
#endif
}

//--------------------------------------------------
// Description  : Rx Down Reply MSG Analysis for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstDownReplyAnal(void)
{
    if(GET_DP_RX_DOWN_REPLY_DIRECTLY() == _TRUE)
    {
        // Clear Flag
        CLR_DP_RX_DOWN_REPLY_DIRECTLY();

        // Message Reply
        ScalerDpRxMstDownReplyDirectlyMsg();

        // Release Down Request Buffer
        SET_DP_RX_DOWN_REQ_BUF_RELEASE();

        CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();

        //========== Release FW Memory ==============

        // Free Request Array
        SET_DP_REQUEST_POOL_FREE();

        //========== Set Next Action ==============

        // Set Reply MSG Ready
        SET_DP_RX_DOWN_REPLY_READY();
    }

    if(GET_DP_RX_DOWN_REPLY_BYPASS() == _TRUE)
    {
        // Clear Flag
        CLR_DP_RX_DOWN_REPLY_BYPASS();

        //========== Set Next Action ==============

        // Set Reply MSG Ready
        SET_DP_RX_DOWN_REPLY_READY();
    }

    if((GET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG() == _TRUE) && (GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
    {
        // CLR Flag
        CLR_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();

        // Occupy Reply Pool
        CLR_DP_REPLY_POOL_FREE();

        // Disable Reply Buffer Free
        CLR_DP_RX_REPLY_BUF_FREE();

        // Error Reply
        ScalerDpRxMstIllegalMsgReply();

        // Release Down Request Buffer
        SET_DP_RX_DOWN_REQ_BUF_RELEASE();

        CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();

        //========== Release FW Memory ==============

        // Free Request Array
        SET_DP_REQUEST_POOL_FREE();

        //========== Set Next Action ==============

        // Set Reply MSG Ready
        SET_DP_RX_DOWN_REPLY_READY();
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Rx Up Request MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstUpRequestProc(void)
{
    if(GET_DP_RX_UP_REQUEST_READY() == _TRUE)
    {
        // Clear Flag
        CLR_DP_RX_UP_REQUEST_READY();

        if(((GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN() == _FALSE) &&
            (GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH() == _FALSE) &&
            (GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH() == _FALSE) &&
            (GET_DP_RX_MST_MODE_STATE() == _DP_RX_MST_MODE_STATUS_ALLOCATED_PBN)))
        {
            // CLR Write Pointer to 0
            CLR_REG_DP_RX_UPSTREAM_REPLY_WRITE_PTR();

            // CLR Read Pointer to 0
            CLR_REG_DP_RX_USTERAM_REPLY_BUF();

            for(pData[0] = 0; pData[0] < GET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(); pData[0]++)
            {
                // Fill Up Request MSG
                SET_REG_DP_RX_UPSTREAM_REPLY_BUF_DATA(GET_DP_MSG_REQUEST_ARRAY(pData[0]));
            }

            // Select To Up Request BUF Address
            SET_REG_DP_RX_UPSTREAM_REPLY_UP_REQUEST_ADDRESS();

            // Set Start and End Bit to HW Auto Mode
            SET_REG_DP_RX_UPSTREAM_HW_AUTO_MODE();

            // Increasing Retry number
            INCREASE_DP_RX_UP_REQUEST_RETRY_NUM();

            // Message Upstream Enable
            SET_REG_DP_RX_UPSTREAM_REPLY();

            // Set Up Request MSG Ready Bit of DPCD Table
            SET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03, (GET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03) | _BIT5));

            // Clear UP_REQ_MSG_RDY Bit IRQ Flag
            CLR_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ_FLAG();

            // Enable UP_REQ_MSG_RDY Bit IRQ
            SET_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ();

            // Gen HPD With Duration 1 ms
            SET_DP_MST_HPD_IRQ();

            // Free Request Pool
            SET_DP_REQUEST_POOL_FREE();

            // Set Timer Event
            ScalerTimerActiveTimerEvent(_UP_REQUEST_MSG_TIME_OUT, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT);
        }
        else
        {
            if(GET_DP_TX_UP_REQUEST_BYPASS_REGEN() == _FALSE)
            {
                if(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCR) != 0x00)
                {
                    SET_DP_TX_UP_REQUEST_BYPASS_REGEN();
                }
            }
            else
            {
                if(GET_DP_TX_SELF_GEN_UP_REQUEST_MSG() == _TRUE)
                {
                    CLR_DP_TX_UP_REQUEST_BYPASS_REGEN();

                    // Set Rx Sink Count
                    pData[0] = GET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00);

                    pData[0] = (pData[0] & _BIT6) | GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_DPCD_200_STATUS);

                    SET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00, pData[0]);

                    if((pData[0] & 0xBF) > 1)
                    {
                        SET_DP_RX_DFP_DEVICE_DETAIL_CONFIG();
                    }
                    else
                    {
                        RST_DP_RX_DFP_DEVICE_DETAIL_CONFIG();
                    }
                }
            }

            SET_DP_RX_SELF_GEN_UP_REQUEST_RETRY(_DP_MSG_CONNECTION_STATUS_NOTIFY);

            // Free Request Array
            SET_DP_REQUEST_POOL_FREE();

            // Free Reply Buffer
            SET_DP_RX_REPLY_BUF_FREE();
        }
    }
}

//--------------------------------------------------
// Description  : Rx Up Reply MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstUpReplyProc(void)
{
    if(GET_DP_RX_UP_REPLY_BUF_RELEASE() == _TRUE)
    {
        // CLR Flag
        CLR_DP_RX_UP_REPLY_BUF_RELEASE();

        // Buffer0 is processed
        if(GET_DP_RX_UP_REPLY_BUF_PRIORITY() == _DP_UP_REPLY_BUF0)
        {
            // Clear Flag
            CLR_REG_DP_RX_UP_REPLY_BUF0_MSG_FINISH();

            // Clear BUF0
            CLR_REG_DP_RX_UP_REPLY_BUF0();

            // Defer Any Other MSGs to Prevent Priority and Using Buf Conflict
            SET_REG_DP_RX_AUX_TO_MANUAL_MODE();

            if((GET_REG_DP_RX_UP_REPLY_ADDR_WRITTEN() == _TRUE) || (GET_REG_DP_RX_UP_REPLY_BUF1_WRITE_PTR() != 0x00))
            {
                CLR_REG_DP_RX_UP_REPLY_ADDR_WRITTEN();

                SET_DP_RX_UP_REPLY_BUF_PRIORITY(_DP_UP_REPLY_BUF1);
            }
            else
            {
                SET_DP_RX_UP_REPLY_BUF_PRIORITY(_DP_UP_REPLY_BUF0);
            }

            // Enable BUF0 to Receive MSG
            SET_REG_DP_RX_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE();

            SET_REG_DP_RX_AUX_TO_AUTO_MODE();
        }
        else
        {
            // Clear BUF1
            CLR_REG_DP_RX_UP_REPLY_BUF1();

            // Enable BUF1 to Receive MSG
            SET_REG_DP_RX_UP_REPLY_BUF1_MSG_RECEIVE_ENABLE();

            SET_DP_RX_UP_REPLY_BUF_PRIORITY(_DP_UP_REPLY_BUF0);
        }
    }

    if(GET_DP_RX_UP_REPLY_BUF_PRIORITY() == _DP_UP_REPLY_BUF0)
    {
        if((GET_REG_DP_RX_UP_REPLY_BUF0_MSG_FINISH() == _TRUE) && (GET_DP_REPLY_POOL_FREE() == _TRUE))
        {
            // Occupy Reply Pool
            CLR_DP_REPLY_POOL_FREE();

            // CLR Flag
            CLR_REG_DP_RX_UP_REPLY_BUF0_MSG_FINISH();

            // Set BUF0 Read PTR to 0
            SET_REG_DP_RX_UP_REPLY_BUF0_RDAD_PTR(0);

            // Get Up Reply MSG and Using Reply Pool to Analysis
            for(pData[0] = 0; pData[0] < GET_REG_DP_RX_UP_REPLY_BUF0_MSG_LENGTH(); pData[0]++)
            {
                SET_DP_MSG_REPLY_ARRAY(pData[0], GET_REG_DP_RX_UP_REPLY_BUF0_DATA());
            }

            // Select to Header 0
            SET_REG_DP_RX_UP_REPLY_HEADER0_INFO();

            // Analysis Up Reply MSG
            SET_DP_RX_UP_REPLY_ANAL();
        }
    }
    else
    {
        if((GET_REG_DP_RX_UP_REPLY_BUF1_MSG_FINISH() == _TRUE) && (GET_DP_REPLY_POOL_FREE() == _TRUE))
        {
            // Occupy Reply Pool
            CLR_DP_REPLY_POOL_FREE();

            // CLR Flag
            CLR_REG_DP_RX_UP_REPLY_BUF1_MSG_FINISH();

            // Set BUF1 Up Reply Read PTR to 0
            SET_REG_DP_RX_UP_REPLY_BUF1_RDAD_PTR(0);

            // Get Up Reply MSG and Using Reply Pool to Analysis
            for(pData[0] = 0; pData[0] < GET_REG_DP_RX_UP_REPLY_BUF1_MSG_LENGTH(); pData[0]++)
            {
                SET_DP_MSG_REPLY_ARRAY(pData[0], GET_REG_DP_RX_UP_REPLY_BUF1_DATA());
            }

            // Select to Header 1
            SET_REG_DP_RX_UP_REPLY_HEADER1_INFO();

            // Analysis Up Reply MSG
            SET_DP_RX_UP_REPLY_ANAL();
        }
    }

    // Prevent MSG BUF0 FSM Dead Lock
    if((GET_REG_DP_RX_UP_REPLY_BUF0_MSG_ERROR() != _NONE_MSG_ERROR) && (GET_DP_RX_UP_REPLY_ANAL() == _FALSE))
    {
        SET_REG_DP_RX_AUX_TO_MANUAL_MODE();

        CLR_REG_DP_RX_UP_REPLY_BUF0_MSG_ERROR();

        CLR_REG_DP_RX_UP_REPLY_BUF0();

        SET_REG_DP_RX_AUX_TO_AUTO_MODE();
    }

    // Prevent MSG BUF1 FSM Dead Lock
    if((GET_REG_DP_RX_UP_REPLY_BUF1_MSG_ERROR() != _NONE_MSG_ERROR) && (GET_DP_RX_UP_REPLY_ANAL() == _FALSE))
    {
        SET_REG_DP_RX_AUX_TO_MANUAL_MODE();

        CLR_REG_DP_RX_UP_REPLY_BUF1_MSG_ERROR();

        CLR_REG_DP_RX_UP_REPLY_BUF1();

        SET_REG_DP_RX_AUX_TO_AUTO_MODE();
    }
}

//--------------------------------------------------
// Description  : Rx Up Request MSG Analysis for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstUpRequestAnal(void)
{
    if(GET_DP_RX_UP_REQUEST_ANAL() == _TRUE)
    {
        // Clear Flag
        CLR_DP_RX_UP_REQUEST_ANAL();

        if(GET_DP_RX_UP_REQUEST_RETRY_NUM() <= 5)
        {
            // Bypass Up Request MSG
            SET_DP_RX_UP_REQUEST_READY();
        }
        else
        {
            // Reset Retry Number
            CLR_DP_RX_UP_REQUEST_RETRY_NUM();

            CLR_DP_RX_UP_REQUEST_CRC_FAIL_RETRY_NUM();

            CLR_REG_DP_RX_UP_REPLY_ADDR_WRITTEN();

            if(GET_DP_TX_UP_REQUEST_BYPASS_REGEN() == _FALSE)
            {
                if(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCR) != 0x00)
                {
                    SET_DP_TX_UP_REQUEST_BYPASS_REGEN();
                }
            }
            else
            {
                if(GET_DP_TX_SELF_GEN_UP_REQUEST_MSG() == _TRUE)
                {
                    CLR_DP_TX_UP_REQUEST_BYPASS_REGEN();

                    // Set Rx Sink Count
                    pData[0] = GET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00);

                    pData[0] = (pData[0] & _BIT6) | GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_DPCD_200_STATUS);

                    SET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00, pData[0]);

                    if((pData[0] & 0xBF) > 1)
                    {
                        SET_DP_RX_DFP_DEVICE_DETAIL_CONFIG();
                    }
                    else
                    {
                        RST_DP_RX_DFP_DEVICE_DETAIL_CONFIG();
                    }
                }
            }

            SET_DP_RX_SELF_GEN_UP_REQUEST_RETRY(_DP_MSG_CONNECTION_STATUS_NOTIFY);

            // Free Request Array
            SET_DP_REQUEST_POOL_FREE();

            // Free Reply Buffer
            SET_DP_RX_REPLY_BUF_FREE();
        }
    }

    if(GET_DP_RX_UP_REQUEST_BYPASS_DONE() == _TRUE)
    {
        // CLR Flag
        CLR_DP_RX_UP_REQUEST_BYPASS_DONE();

        CLR_DP_RX_SELF_GEN_UP_REQUEST_RETRY();

        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_CABLE_STATUS_CHANGE_EVENT);

        // Reset Retry Number
        CLR_DP_RX_UP_REQUEST_RETRY_NUM();

        // Update Current Tx Sink Count Status for Unplug CSN Even Stop Tx sink count update
        if(GET_DP_RX_REPORT_DOWNSTREAM_UNPLUG_EVENT() == _TRUE)
        {
            CLR_DP_RX_REPORT_DOWNSTREAM_UNPLUG_EVENT();
        }

        if(GET_DP_TX_BYPASS_UNPLUG_CSN_IS_PENDING() == _TRUE)
        {
            CLR_DP_TX_BYPASS_UNPLUG_CSN_IS_PENDING();

            // Set Rx Sink Count
            pData[0] = GET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00);

            // Back Up
            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_DPCD_200_STATUS, pData[0]);

            pData[0] = (pData[0] & _BIT6) | (GET_DP_TX_DOWNSTREAM_SINK_COUNT() + 1);

            SET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00, pData[0]);

            if((pData[0] & 0xBF) > 1)
            {
                SET_DP_RX_DFP_DEVICE_DETAIL_CONFIG();
            }
            else
            {
                RST_DP_RX_DFP_DEVICE_DETAIL_CONFIG();
            }
        }
        else
        {
            // Clear The Up Request Backup Data
            CLR_DP_TX_UP_REQUEST_BACKUP_DATA();
        }

        if(GET_DP_TX_UP_REQUEST_BYPASS_REGEN() == _FALSE)
        {
            CLR_DP_TX_SELF_GEN_UP_REQUEST_MSG();

            if(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCR) != 0x00)
            {
                SET_DP_TX_UP_REQUEST_BYPASS_REGEN();

                SET_DP_RX_SELF_GEN_UP_REQUEST_RETRY(_DP_MSG_CONNECTION_STATUS_NOTIFY);
            }
        }
        else
        {
            CLR_DP_TX_UP_REQUEST_BYPASS_REGEN();

            if(GET_DP_TX_SELF_GEN_UP_REQUEST_MSG() == _TRUE)
            {
                SET_DP_RX_SELF_GEN_UP_REQUEST_RETRY(_DP_MSG_CONNECTION_STATUS_NOTIFY);
            }
            else
            {
                // Add for GET_DP_TX_BYPASS_UNPLUG_CSN_IS_PENDING released case to regen the plug CSN
                if(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCR) != 0x00)
                {
                    SET_DP_TX_UP_REQUEST_BYPASS_REGEN();

                    SET_DP_RX_SELF_GEN_UP_REQUEST_RETRY(_DP_MSG_CONNECTION_STATUS_NOTIFY);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Rx Up Reply MSG Analysis for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstUpReplyAnal(void)
{
    if((GET_DP_RX_UP_REPLY_DIRECTLY() == _TRUE) && (GET_DP_REPLY_POOL_FREE() == _TRUE))
    {
        // CLR Flag
        CLR_DP_RX_UP_REPLY_DIRECTLY();

        // Occupy Reply Pool
        CLR_DP_REPLY_POOL_FREE();

        //========== Body Info ==============

        SET_DP_REPLY_MSG_CONNECTION_STATUS_NOTIFY_REPLY_TYPE(_DP_MSG_ACK);

        SET_DP_REPLY_MSG_CONNECTION_STATUS_NOTIFY_REQUEST_ID(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_ID));

        //========== Header Info ==============
        // Set LCT = 1
        SET_REG_DP_TX_DOWNSTREAM_MSG_LCT(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCT));

        // Set LCR = 0
        SET_REG_DP_TX_DOWNSTREAM_MSG_LCR(0);

        // Set Broadcast Bit
        SET_REG_DP_TX_DOWNSTREAM_MSG_BROADCAST(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_BROADCAST));

        // Set Path Bit
        SET_REG_DP_TX_DOWNSTREAM_MSG_PATH(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PATH));

        // Set TX MSG Write Total Length
        SET_REG_DP_TX_DOWNSTREAM_MSG_LENGTH(1);

        // Set MSN Bit
        SET_REG_DP_TX_DOWNSTREAM_MSG_MSN(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_MSN));

        //========== Release FW Memory ==============

        // Clear Up_Req Bypass MSG Back Up
        CLR_DP_TX_UP_REQUEST_BACKUP_DATA();

        // Clear Up Req Msg Header
        CLR_DP_TX_UP_REQUEST_MSG_HEADER();

        //========== Set Next Action ==============

        // Dp Rx Reply Up Reply (Ack) MSG to Down Stream
        SET_DP_TX_UP_REPLY_BYPASS();
    }

    if(GET_DP_RX_UP_REPLY_ANAL() == _TRUE)
    {
        CLR_DP_RX_UP_REPLY_ANAL();

        // Release Up Reply BUF
        SET_DP_RX_UP_REPLY_BUF_RELEASE();

        CLR_REG_DP_RX_UP_REPLY_ADDR_WRITTEN();

        if(GET_DP_RX_UP_REQUEST_RETRY_NUM() != 0)
        {
            if((ScalerDpRxMstCheckMsgCRC(_DP_UP_REPLY_MSG) == _TRUE) ||
               (GET_DP_MSG_UP_REPLY_TYPE() == _DP_MSG_ACK) ||
               (GET_DP_RX_UP_REQUEST_CRC_FAIL_RETRY_NUM() > 5))
            {
                CLR_DP_RX_UP_REQUEST_CRC_FAIL_RETRY_NUM();

                // Set Up Request Bypass Done Flag
                SET_DP_RX_UP_REQUEST_BYPASS_DONE();
            }
            else
            {
                if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
                {
                    // Make Up Request to Retry
                    SET_DP_RX_UP_REQUEST_ANAL();

                    INCREASE_DP_RX_UP_REQUEST_CRC_FAIL_RETRY_NUM();
                }
            }
        }

        // Free Reply Pool
        SET_DP_REPLY_POOL_FREE();
    }
}

//--------------------------------------------------
// Description  : Check Msg Transition
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpRxMstCheckMsgTransition(void)
{
    if(g_enumDpMSTCapablePort != _DP_MST_NO_PORT)
    {
        if(GET_DP_TOTAL_RECEIVED_MSG_COUNT() != 0)
        {
            return _TRUE;
        }

        if(GET_DP_TX_RECEIVED_MSG_COUNT() != 0)
        {
            return _TRUE;
        }

        if(ScalerDpRxMstCheckMsgBufferFree() == _FALSE)
        {
            return _TRUE;
        }

        if(GET_DP_TX_HDCP_AUTH_HOLD() == _TRUE)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Tx Mst Msg Count Check Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstMsgCountResetEvent(void)
{
    SET_DP_TOTAL_RECEIVED_MSG_COUNT(0);

    // Release Down Request Buffer
    SET_DP_RX_DOWN_REQ_BUF_RELEASE();

    CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT);

    CLR_DP_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();
}

#endif // End of #if(_DP_TX_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Rx MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstMsgTimeoutEvent(void)
{
    if(GET_DP_RX_CANCEL_MSG_TIMEOUT_EVENT() == _TRUE)
    {
        CLR_DP_RX_CANCEL_MSG_TIMEOUT_EVENT();

        return;
    }

    // Down Reply Ready bit unclear
    if(GET_REG_DP_RX_UPSTREAM_TRANSITION_ADDRESS() == 0x00)
    {
        if(g_ucDpMstRxDownReplyRetryCount >= _DP_MST_DOWN_REPLY_MSG_TIME_OUT_RETRY_MAX)
        {
            // Disable DOWN_REP_MSG_RDY Bit INT
            CLR_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ();

            // Clear DOWN_REP_MSG_RDY Bit of DPCD Table
            SET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03, (GET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03) & ~_BIT4));

            // Clear Buffer
            CLR_REG_DP_RX_USTERAM_REPLY_BUF();

            // Disable Message Upstream
            CLR_REG_DP_RX_UPSTREAM_REPLY();

            // Free Reply Buffer
            SET_DP_RX_REPLY_BUF_FREE();
        }
        else
        {
            // Gen HPD With Duration 1 ms
            SET_DP_MST_HPD_IRQ();

            // Set Timer Event
            ScalerTimerReactiveTimerEvent(_DOWN_REPLY_MSG_TIME_OUT, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT);

            g_ucDpMstRxDownReplyRetryCount ++;
        }
    }

#if(_DP_TX_SUPPORT == _ON)
    // Up Request Ready bit unclear
    if(GET_REG_DP_RX_UPSTREAM_TRANSITION_ADDRESS() == 0x01)
    {
        // Disable UP_REQ_MSG_RDY INT
        CLR_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ();

        // Clear UP_REQ_MSG_RDY Bit of DPCD Table
        SET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03, (GET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03) & ~_BIT5));

        // Clear Buffer
        CLR_REG_DP_RX_USTERAM_REPLY_BUF();

        // Message Upstream Disable
        CLR_REG_DP_RX_UPSTREAM_REPLY();

        // Free Reply Pool
        SET_DP_RX_REPLY_BUF_FREE();

        // Retry
        SET_DP_RX_SELF_GEN_UP_REQUEST_RETRY(_DP_MSG_CONNECTION_STATUS_NOTIFY);
    }
#endif
}

//--------------------------------------------------
// Description  : Rx MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstDownRequestEventProc(void)
{
    bit bIllegal = _FALSE;
    static bit sbEdidSegIsWritten = _FALSE;
    BYTE ucTemp = 0;
    BYTE ucSTMux = 0;
    BYTE ucLength = 0;
    static WORD susEdidReadPosition = 0;

    switch(GET_DP_RX_EVENT())
    {
        case _DP_RX_DPCD_READ_REQUEST:

            for(pData[0] = 0; pData[0] < GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ(); pData[0]++)
            {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _OFF)
                if((GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_H() == 0x00) && (GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M() == 0x22))
                {
                    switch(GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_L() + pData[0])
                    {
                        case 0x00:
                            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(pData[0]) = GET_DP_DPCD_02200H_STATUS();
                            break;

                        case 0x01:
                            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(pData[0]) = GET_DP_DPCD_02201H_STATUS();
                            break;

                        case 0x10:
                            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(pData[0]) = GET_DP_DPCD_02210H_STATUS();
                            break;

                        default:
                            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(pData[0]) = GET_REG_DP_DPCD_INFO(0x00, 0x00, pData[0]);
                            break;
                    }
                }
                else
#endif
                {
                    SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(pData[0]) = GET_REG_DP_DPCD_INFO(GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_H(),
                                                                                                 GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M(),
                                                                                                 GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_L() + pData[0]);
                }
            }

            // Set Native Reply Message
            SET_DP_RX_DOWN_REPLY_DIRECTLY();

            break;

        case _DP_RX_DPCD_WRITE_REQUEST:

            for(pData[0] = 0; pData[0] < GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_NUM_OF_WRITE(); pData[0]++)
            {
                SET_REG_DP_DPCD_INFO((GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_H() & 0x0F), GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_M(),
                                     (GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_L() + pData[0]), GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_DATA(pData[0]));
            }

            // Set Native Reply Message
            SET_DP_RX_DOWN_REPLY_DIRECTLY();

            break;

        case _DP_RX_NATIVE_DISPLAY_REQUEST:

            // Set Stream Mux Source
            ScalerDpRxMstStreamMuxBackup(_DP_ST_SOURCE1, ScalerDpRxMstSearchMatchStream(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()));

            SET_REG_DP_RX_AUX_TO_MANUAL_MODE();
            SET_REG_DP_DPCD_INFO(0x00, 0x06, 0x00, 0x01);
            SET_REG_DP_RX_AUX_TO_AUTO_MODE();

            break;


#if(_DP_TX_SUPPORT == _ON)

        case _DP_RX_REMOTE_MST_DISPLAY_REQUEST:

            for(ucTemp = _DP_ST_SOURCE3; ucTemp <= _DP_ST_SOURCE5; ucTemp++)
            {
                if(ScalerDpRxMstStreamMuxCheck(ucTemp) == 0)
                {
                    // Set Stream Mux Source
                    ScalerDpRxMstStreamMuxBackup(ucTemp, ScalerDpRxMstSearchMatchStream(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()));
                    break;
                }
            }

            SET_REG_DP_RX_AUX_TO_MANUAL_MODE();
            SET_REG_DP_DPCD_INFO(0x00, 0x06, 0x00, 0x01);
            SET_REG_DP_RX_AUX_TO_AUTO_MODE();

            if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_MST)
            {
                ScalerDpTxSetStreamSource(_DP_TX_SOURCE_MST);
            }

            if(GET_DP_RX_MST2SST_ENABLE() == _ENABLE)
            {
                SET_DP_RX_MST2SST_ENABLE(_DISABLE);
            }

            ScalerDpTxConfigMstStreamLaneNum();

            break;

        case _DP_RX_REMOTE_SST_DISPLAY_REQUEST:

            if(ScalerDpTxLinkStatusCheck() == _FAIL)
            {
                SET_DP_TX_FORCE_LINK_TRAINING();
            }

            // Set Stream Mux Source
            ScalerDpRxMstStreamMuxBackup(_DP_ST_SOURCE2, ScalerDpRxMstSearchMatchStream(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()));

            ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

            SET_DP_RX_MST2SST_ENABLE(_ENABLE);

            ScalerDpTxConfigMstStreamLaneNum();

            break;

        case _DP_RX_REMOTE_SST_WITH_AUDIO_DISPLAY_REQUEST:

            if(ScalerDpTxLinkStatusCheck() == _FAIL)
            {
                SET_DP_TX_FORCE_LINK_TRAINING();
            }

            // Search Payload ID Corresponding Stream Index
            ucSTMux = ScalerDpRxMstSearchMatchStream(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID());

            if(ucSTMux != _DP_ST_NONE)
            {
                // Set Daisy Chain3 Timeslot for Audio
                SET_REG_DP_RX_DAIZY_ST3_START(1);
                SET_REG_DP_RX_DAIZY_ST3_END(63);

                SET_REG_DP_RX_SEND_ACT_ENABLE();

                // Set Stream Mux Source for Video
                ScalerDpRxMstStreamMuxBackup(_DP_ST_SOURCE2, ucSTMux);

                // Set Stream Mux Source for Audio
                ScalerDpRxMstStreamMuxBackup(_DP_ST_SOURCE3, ucSTMux);

                ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

                SET_DP_RX_MST2SST_ENABLE(_ENABLE);
            }

            ScalerDpTxConfigMstStreamLaneNum();

            break;

        case _DP_RX_DELETE_REMOTE_DISPLAY_REQUEST:

            ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

            SET_DP_RX_MST2SST_ENABLE(_DISABLE);

            break;

#endif // End of #if(_DP_TX_SUPPORT == _ON)

        case _DP_RX_I2C_READ:

            // Clear the flag of EDID segmet been written
            sbEdidSegIsWritten = _FALSE;

            // The first position of I2C_Device_Identifier
            pData[0] = 2;

            if(GET_DP_DOWN_REQUEST_REMOTE_I2C_READ_MSG_NUM_OF_WRITE() > 0)
            {
                susEdidReadPosition = 0;

                // Handling Wtire Command
                for(pData[1] = 1; pData[1] <= GET_DP_DOWN_REQUEST_REMOTE_I2C_READ_MSG_NUM_OF_WRITE(); pData[1]++)
                {
                    // Get Number_Of_Bytes_To_Write
                    if((ucLength = g_unDpRequestPool.pucData[pData[0] + 1]) > 0)
                    {
                        // Get data (which is illegal if > 255)
                        for(pData[2] = 1; pData[2] < ucLength; pData[2]++)
                        {
                            if(g_unDpRequestPool.pucData[pData[0] + 1 + pData[2]] != 0)
                            {
                                bIllegal = _TRUE;
                                break;
                            }
                        }

                        ucTemp = g_unDpRequestPool.pucData[pData[0] + 1 + ucLength];

                        // Get Write I2C Device ID
                        switch(g_unDpRequestPool.pucData[pData[0]])
                        {
                            case _DP_MSG_IIC_DEVICE_EDID_SEGMENT:

                                if(ucTemp <= 1)
                                {
                                    susEdidReadPosition = ucTemp * 256;
                                }
                                else
                                {
                                    bIllegal = _TRUE;
                                }

                                break;

                            // Set Offset
                            case _DP_MSG_IIC_DEVICE_EDID:

                                if((susEdidReadPosition + ucTemp) < GET_DP_MST_DDCRAM_SIZE())
                                {
                                    susEdidReadPosition += ucTemp;
                                }
                                else
                                {
                                    bIllegal = _TRUE;
                                }

                                break;

                            case _DP_MSG_IIC_DEVICE_DDCCI:

                                break;

                            default:

                                bIllegal = _TRUE;

                                break;
                        }
                    }

                    if(bIllegal == _TRUE)
                    {
                        SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                        SET_DP_REPLY_REMOTE_I2C_READ_NAK_TRANSACTION(pData[1]);

                        SET_DP_REPLY_POOL_FREE();
                        SET_DP_RX_REPLY_BUF_FREE();
                        SET_DP_RX_EVENT(_DP_RX_NONE_EVENT);

                        return;
                    }

                    // Point to next I2C_Device_Identifier
                    pData[0] += (3 + g_unDpRequestPool.pucData[pData[0] + 1]);
                }
            }

            // Number of Bytes To Read
            ucLength = (g_unDpRequestPool.pucData[pData[0] + 1]);

            // Handling Read Command
            switch(g_unDpRequestPool.pucData[pData[0]])
            {
                case _DP_MSG_IIC_DEVICE_EDID:

                    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
                    {
#if(_D0_DP_EXIST == _ON)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

                        if(g_bDpMSTD6Capable == _TRUE)
                        {
                            memcpy(g_unDpReplyPool.stRemoteI2CRead.pucI2CRead, &MCU_DDCRAM_D6[susEdidReadPosition], ucLength);
                        }
                        else
#endif
                        {
                            memcpy(g_unDpReplyPool.stRemoteI2CRead.pucI2CRead, &MCU_DDCRAM_D0[susEdidReadPosition], ucLength);
                        }
#endif
                    }
#if(_D1_DP_EXIST == _ON)
                    else if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
                    {
                        memcpy(g_unDpReplyPool.stRemoteI2CRead.pucI2CRead, &MCU_DDCRAM_D1[susEdidReadPosition], ucLength);
                    }
#endif
                    susEdidReadPosition += ucLength;

                    if(susEdidReadPosition >= GET_DP_MST_DDCRAM_SIZE())
                    {
                        // Initialize the ReadPosition while EOF
                        susEdidReadPosition = 0;
                    }

                    // Set Number Of Byte Read
                    SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_NUM_OF_READ(ucLength);

                    // Set Message Body Length
                    SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(3 + ucLength);

                    // Set Native Reply Message
                    SET_DP_RX_DOWN_REPLY_DIRECTLY();

                    break;

                case _DP_MSG_IIC_DEVICE_DDCCI:

                    for(pData[1] = 0; pData[1] < ucLength; pData[1]++)
                    {
                        if(pData[1] > _DDCCI_TXBUF_LENGTH)
                        {
                            g_unDpReplyPool.stRemoteI2CRead.pucI2CRead[pData[1]] = 0;
                        }
                        else
                        {
                            g_unDpReplyPool.stRemoteI2CRead.pucI2CRead[pData[1]] = g_pucDdcciTxBuf[pData[1]];
                        }
                    }

                    // Set Number Of Byte Read
                    SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_NUM_OF_READ(ucLength);

                    // Set Message Body Length
                    SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(3 + ucLength);

                    // Set Native Reply Message
                    SET_DP_RX_DOWN_REPLY_DIRECTLY();

                    break;

                default:

                    // Release Down Request Buffer
                    SET_DP_RX_DOWN_REQ_BUF_RELEASE();

                    CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();

                    // Free Request Array
                    SET_DP_REQUEST_POOL_FREE();

                    // Set Reply Pool Free
                    SET_DP_REPLY_POOL_FREE();

                    // Set Reply Buffer Free
                    SET_DP_RX_REPLY_BUF_FREE();

#if(_DP_TX_SUPPORT == _ON)
                    SET_DP_TOTAL_RECEIVED_MSG_COUNT(GET_DP_TOTAL_RECEIVED_MSG_COUNT() - 1);

                    if(GET_DP_TOTAL_RECEIVED_MSG_COUNT() == 0)
                    {
                        // Cancel Timer Event
                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
                    }
#endif
                    break;
            }

            break;

        case _DP_RX_I2C_WRITE:

            switch(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_WRITE_DEVICE_ID())
            {
                case _DP_MSG_IIC_DEVICE_EDID_SEGMENT:

                    if(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() > 0)
                    {
                        PDATA_WORD(0) = GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() - 1) * 256;

                        if(PDATA_WORD(0) < GET_DP_MST_DDCRAM_SIZE())
                        {
                            susEdidReadPosition = PDATA_WORD(0);

                            sbEdidSegIsWritten = _TRUE;
                        }
                        else
                        {
                            susEdidReadPosition = 0;
                        }
                    }
                    else
                    {
                        susEdidReadPosition = 0;
                    }

                    // Set Native Reply Message
                    SET_DP_RX_DOWN_REPLY_DIRECTLY();

                    break;

                case _DP_MSG_IIC_DEVICE_EDID:

                    if(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() > 0)
                    {
                        if(sbEdidSegIsWritten == _TRUE)
                        {
                            susEdidReadPosition += GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() - 1);
                        }
                        else
                        {
                            susEdidReadPosition = GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() - 1);
                        }

                        if(susEdidReadPosition >= GET_DP_MST_DDCRAM_SIZE())
                        {
                            susEdidReadPosition = 0;
                        }
                    }
                    else
                    {
                        if(sbEdidSegIsWritten == _FALSE)
                        {
                            susEdidReadPosition = 0;
                        }
                    }

                    // Set Native Reply Message
                    SET_DP_RX_DOWN_REPLY_DIRECTLY();

                    break;

                case _DP_MSG_IIC_DEVICE_DDCCI:

                    pData[0] = GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE();

                    if(pData[0] <= _DDCCI_RXBUF_LENGTH)
                    {
                        ScalerMcuDdcciSetData(&GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(0), pData[0], _DDCCI_CMD_SRC_MST);
                    }

                    // Set Native Reply Message
                    SET_DP_RX_DOWN_REPLY_DIRECTLY();

                    break;

                default:

                    // Release Down Request Buffer
                    SET_DP_RX_DOWN_REQ_BUF_RELEASE();

                    CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();

                    // Free Request Array
                    SET_DP_REQUEST_POOL_FREE();

                    // Set Reply Pool Free
                    SET_DP_REPLY_POOL_FREE();

                    // Set Reply Buffer Free
                    SET_DP_RX_REPLY_BUF_FREE();

#if(_DP_TX_SUPPORT == _ON)
                    SET_DP_TOTAL_RECEIVED_MSG_COUNT(GET_DP_TOTAL_RECEIVED_MSG_COUNT() - 1);

                    if(GET_DP_TOTAL_RECEIVED_MSG_COUNT() == 0)
                    {
                        // Cancel Timer Event
                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
                    }
#endif
                    break;
            }
            break;

        case _DP_RX_QUERY_STREAM_ECRYPTION_STATUS:

            // Set Native Reply Message
            SET_DP_RX_DOWN_REPLY_DIRECTLY();

            break;

        default:
            break;
    }

    SET_DP_RX_EVENT(_DP_RX_NONE_EVENT);
}

//--------------------------------------------------
// Description  : Rx MSG Analysis for DP
// Input Value  : Request Message Type
// Output Value : None
//--------------------------------------------------
bit ScalerDpRxMstMsgAnalysis(void)
{
    BYTE ucTemp = 0;

    switch(GET_DP_MSG_REQUEST_ID())
    {
        case _DP_MSG_LINK_ADDRESS:

            if((GET_DP_MST_VBIOS_BACKUP_INFO() == _TRUE) && (GET_REG_DP_RX_DOWN_REQUEST_MSG_LCT() == 1))
            {
                CLR_DP_MST_VBIOS_BACKUP_INFO();

                ScalerDpRxMstBackupInfoReset();
            }

            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check RAD[0] = 1
                if((GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() == _DP_PORT1) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();

                    if((GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) &&
                       ((GET_REG_DP_RX_DOWN_REQUEST_MSG_LCT() - GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR()) == 1))
                    {
                        SET_DP_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();
                    }
                }
                else
#endif
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }
            else
            {
                if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                {
                    // CLR Flag
                    CLR_DP_REPLY_POOL_FREE();

                    // Disable Reply Buffer Free
                    CLR_DP_RX_REPLY_BUF_FREE();

                    // Set Native Reply Message
                    SET_DP_RX_DOWN_REPLY_DIRECTLY();
                }
                else
                {
                    return _FALSE;
                }
            }

            break;

        case _DP_MSG_ENUM_PATH_RESOURCES:

            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check RAD[0] = 1
                if((GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() == _DP_PORT1) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
                else
#endif
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }
            else
            {
                if(GET_DP_DOWN_REQUEST_ENUM_PATH_MSG_PORT_NUM() == _DP_PORT8)
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        // Set Native Reply Message
                        SET_DP_RX_DOWN_REPLY_DIRECTLY();
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if(GET_DP_DOWN_REQUEST_ENUM_PATH_MSG_PORT_NUM() == _DP_PORT1)
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }

            break;

        case _DP_MSG_ALLOCATE_PAYLOAD:

            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check RAD[0] = 1
                if((GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() == _DP_PORT1) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();

                    if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > 0)
                    {
                        // Steering Stream to Bypass FIFO
                        SET_DP_RX_EVENT(_DP_RX_REMOTE_MST_DISPLAY_REQUEST);
                    }
                }
                else
#endif
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }
            else
            {
                if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM() == _DP_PORT8)
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        // Set Native Reply Message
                        SET_DP_RX_DOWN_REPLY_DIRECTLY();
                    }
                    else
                    {
                        return _FALSE;
                    }

                    if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > 0)
                    {
                        SET_DP_RX_EVENT(_DP_RX_NATIVE_DISPLAY_REQUEST);
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM() == _DP_PORT1)
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();

                    if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > 0)
                    {
                        if(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_NO_SUPPORT)
                        {
                            if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_SDP_NUM() == 0)
                            {
                                // SET_DP_RX_EVENT(_DP_RX_REMOTE_SST_DISPLAY_REQUEST);
                                SET_DP_RX_EVENT(_DP_RX_REMOTE_SST_WITH_AUDIO_DISPLAY_REQUEST);
                            }
                            else
                            {
                                SET_DP_RX_EVENT(_DP_RX_REMOTE_SST_WITH_AUDIO_DISPLAY_REQUEST);
                            }
                        }
                        else
                        {
                            // Steering Stream to Bypass FIFO
                            SET_DP_RX_EVENT(_DP_RX_REMOTE_MST_DISPLAY_REQUEST);
                        }
                    }
                    else if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() == 0)
                    {
                        // Delete Downward Stream
                        SET_DP_RX_EVENT(_DP_RX_DELETE_REMOTE_DISPLAY_REQUEST);
                    }
                }
#endif
                else
                {
                    // Set event and perform in ERROR HANDLER
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }

            // Clear Allocated Flag Manual Mode
            CLR_DP_RX_MANUAL_FORCE_SET_ACT();

            // Disable Read 2C0 INT
            CLR_REG_DP_RX_2C0_IRQ();

            break;

        case _DP_MSG_QUERY_PAYLOAD:

            // LCR > 0
            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check RAD[0] = Port 1
                if((GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() == _DP_PORT1) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
                else
#endif
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }
            else
            {
                if(ScalerDpRxMstCheckIDExisted(GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PAYLOAD_ID()) == _TRUE)
                {
                    if(GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM() == _DP_PORT8)
                    {
                        if(g_pucDpStreamToIdMapping[ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE1) - 1] == GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PAYLOAD_ID())
                        {
                            if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                            {
                                // Clear Reply Array Free Flag
                                CLR_DP_REPLY_POOL_FREE();

                                // Disable Reply Buffer Free
                                CLR_DP_RX_REPLY_BUF_FREE();

                                // Set Native Reply Message
                                SET_DP_RX_DOWN_REPLY_DIRECTLY();
                            }
                            else
                            {
                                return _FALSE;
                            }
                        }
                        else
                        {
                            // Error Bad param
                            SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                        }
                    }
#if(_DP_TX_SUPPORT == _ON)
                    else if(GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM() == _DP_PORT1)
                    {
                        if(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_NO_SUPPORT)
                        {
                            if(g_pucDpStreamToIdMapping[ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE2) - 1] == GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PAYLOAD_ID())
                            {
                                if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                                {
                                    // Clear Reply Array Free Flag
                                    CLR_DP_REPLY_POOL_FREE();

                                    // Disable Reply Buffer Free
                                    CLR_DP_RX_REPLY_BUF_FREE();

                                    // Set Native Reply Message
                                    SET_DP_RX_DOWN_REPLY_DIRECTLY();
                                }
                                else
                                {
                                    return _FALSE;
                                }
                            }
                            else
                            {
                                // Error Bad param
                                SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                            }
                        }
                        else
                        {
                            // Set TX Down Request Analysis
                            SET_DP_TX_DOWN_REQUEST_ANAL();
                        }
                    }
#endif
                    else
                    {
                        // Error Bad param
                        SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    }
                }
                else
                {
                    // Error Bad param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }

            break;

        case _DP_MSG_CLEAR_PAYLOAD_ID_TABLE:

            // Clear Payload ID Table
            SET_REG_DP_RX_CLEAR_PAYLOAD_ID_TABLE();
            CLR_REG_DP_RX_CLEAR_PAYLOAD_ID_TABLE();

            // Reset ST1 ~ ST5
            ScalerDpRxMstStreamPositionReset();

            // Reset ST1_Source ~ ST5_Source
            ScalerDpRxMstClrStreamMuxBackup();

            for(pData[0] = 0; pData[0] < 5; pData[0]++)
            {
                g_pucDpStreamToIdMapping[pData[0]] = 0;
            }

#if(_DP_TX_SUPPORT == _ON)

            // Delete Downward Stream
            SET_DP_RX_EVENT(_DP_RX_DELETE_REMOTE_DISPLAY_REQUEST);

            if((GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0) && (GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) &&
               (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT) && (GET_DP_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE() == _FALSE))
            {
                // Set TX DownReq Analysis
                SET_DP_TX_DOWN_REQUEST_ANAL();

                if(GET_DP_GEN_DOWN_REQUEST_MSG() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE)
                {
                    // Set Gen Msg to None
                    CLR_DP_GEN_DOWN_REQUEST_MSG();
                }
            }
            else
            {
                if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                {
                    // Clear Reply Array Free Flag
                    CLR_DP_REPLY_POOL_FREE();

                    // Disable Reply Buffer Free
                    CLR_DP_RX_REPLY_BUF_FREE();

                    // Set Native Reply Message
                    SET_DP_RX_DOWN_REPLY_DIRECTLY();
                }
                else
                {
                    return _FALSE;
                }
            }
#else
            if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
            {
                // Clear Reply Array Free Flag
                CLR_DP_REPLY_POOL_FREE();

                // Disable Reply Buffer Free
                CLR_DP_RX_REPLY_BUF_FREE();

                // Set Native Reply Message
                SET_DP_RX_DOWN_REPLY_DIRECTLY();
            }
            else
            {
                return _FALSE;
            }
#endif

            // Clear Allocated Flag Manual Mode
            CLR_DP_RX_MANUAL_FORCE_SET_ACT();

            // Disable Read 2C0 INT
            CLR_REG_DP_RX_2C0_IRQ();

            break;

        case _DP_MSG_POWER_UP_PHY:

            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check RAD[0] = 1
                if((GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() == _DP_PORT1) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
                else
#endif
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }
            else // LCR = 0
            {
                if(GET_DP_DOWN_REQUEST_POWER_UP_MSG_PORT_NUM() == _DP_PORT8)
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        // Set Native Reply Message
                        SET_DP_RX_DOWN_REPLY_DIRECTLY();
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if(GET_DP_DOWN_REQUEST_POWER_UP_MSG_PORT_NUM() == _DP_PORT1)
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
                else
#endif
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }



            break;

        case _DP_MSG_POWER_DOWN_PHY:

            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check RAD[0] = 1
                if((GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() == _DP_PORT1) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
                else
#endif
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }
            else
            {
                if(GET_DP_DOWN_REQUEST_POWER_DOWN_MSG_PORT_NUM() == _DP_PORT8)
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        // Set Native Reply Message
                        SET_DP_RX_DOWN_REPLY_DIRECTLY();
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if(GET_DP_DOWN_REQUEST_POWER_DOWN_MSG_PORT_NUM() == _DP_PORT1)
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }

            break;

        case _DP_MSG_REMOTE_DPCD_READ:

            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check RAD[0] = 1
                if((GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() == _DP_PORT1) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
                else
#endif
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }
            else
            {
                if(GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_PORT_NUM() == _DP_PORT8)
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Rep Memory Pool Free
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        // Set Rx Event
                        SET_DP_RX_EVENT(_DP_RX_DPCD_READ_REQUEST);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if(GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_PORT_NUM() == _DP_PORT1)
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }

            break;

        case _DP_MSG_REMOTE_DPCD_WRITE:

            // LCR > 0
            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check RAD[0] = 1
                if((GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() == _DP_PORT1) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
                else
#endif
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }
            else // LCR = 0
            {
                if(GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_PORT_NUM() == _DP_PORT8)
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Rep Memory Pool Free
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        // Set Rx Event
                        SET_DP_RX_EVENT(_DP_RX_DPCD_WRITE_REQUEST);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if(GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_PORT_NUM() == _DP_PORT1)
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }

            break;

        case _DP_MSG_REMOTE_I2C_READ:

            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check RAD[0] = 1
                if((GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() == _DP_PORT1) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
                else
#endif
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }
            else
            {
                if(GET_DP_DOWN_REQUEST_REMOTE_I2C_READ_MSG_PORT_NUM() == _DP_PORT8)
                {
#if(_DP_TX_SUPPORT == _ON)
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_RX_REPLY_BUF_FREE() == _TRUE) &&
                       (GET_DP_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY() == _FALSE))
#else
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
#endif
                    {
                        // Clear Reply Pool Free
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        // Set Rx Event
                        SET_DP_RX_EVENT(_DP_RX_I2C_READ);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if(GET_DP_DOWN_REQUEST_REMOTE_I2C_READ_MSG_PORT_NUM() == _DP_PORT1)
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Handler
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }

            break;

        case _DP_MSG_REMOTE_I2C_WRITE:

            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check RAD[0] = 1
                if((GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() == _DP_PORT1) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
                else
#endif
                {
                    // Error Bad Param
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }
            else
            {
                if(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_PORT_NUM() == _DP_PORT8)
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Pool Free
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        // Set Rx Event
                        SET_DP_RX_EVENT(_DP_RX_I2C_WRITE);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_PORT_NUM() == _DP_PORT1)
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Handler
                    SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }

            break;

        case _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS:

            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Error Handler
                SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
            }
            else
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check Stream ID attached to which ST MUX
                ucTemp = ScalerDpRxMstSearchMatchStream(GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());

                // Back-up Q_ID
                ScalerDpRxMstQueryEncryptionBackupClientId();

                // Check if Stream ID of Down Request MSG is equal to Stream ID in the ST Source 1 and Stream ID is valid
                if((ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE1) != (ucTemp + 1)) && (ucTemp != _DP_ST_NONE))
                {
                    // Set TX DownReq Analysis
                    SET_DP_TX_DOWN_REQUEST_ANAL();

                    if(GET_DP_RX_DOWN_REQUEST_BUF_PRIORITY() == _DP_DOWN_REQUEST_BUF0)
                    {
                        SET_DP_TX_DOWN_REQUEST_BODY_LENGTH(GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_LENGTH());
                    }
                    else
                    {
                        SET_DP_TX_DOWN_REQUEST_BODY_LENGTH(GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_LENGTH());
                    }
                }
                else
#endif
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        // Set Rx Event
                        SET_DP_RX_EVENT(_DP_RX_QUERY_STREAM_ECRYPTION_STATUS);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            break;

        default:

            // Error Handler
            SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG();
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Rx MSG Reply for DP
// Input Value  : Reply Message Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstDownReplyDirectlyMsg(void)
{
    switch(GET_DP_MSG_REQUEST_ID())
    {
        case _DP_MSG_LINK_ADDRESS:

            // Set Message Body Length = 60
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(60);

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_REQUEST_ID(_DP_MSG_LINK_ADDRESS);

#if(_DP_SUPPORT == _ON)
            // Set GUID
            for(pData[0] = 0; pData[0] < 16; pData[0]++)
            {
                SET_DP_DOWN_REPLY_LINK_ADDR_MSG_GUID(pData[0], GET_REG_DP_DPCD_INFO(0x00, 0x00, (0x30 + pData[0])));
            }
#endif

            // Set Number of Ports
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_PORT(_DP_NUM_OF_PORTS);

            // Setting Port0 Is Input Port
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT0_TYPE(_DP_INPUT_PORT);

            // Setting Port Number Of Port0
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT0_NUM(_DP_PORT0);

            // Check Up Stream Is Source
            if((GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT2) == _BIT2)
            {
                // Set Peer Device Type
                SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT0_PEER_DEVICE_TYPE(1);
            }
            else
            {
                // Set Peer Device Type
                SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT0_PEER_DEVICE_TYPE(2);
            }

            // Set Message Capability status
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT0_MSG_CAP(1);

            // Setting Port0 Dp Plug Status
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT0_DP_PLUG_STATUS(_DP_PLUG);

            //===== Set Logical Port Info. ======
            // Setting Port8 is Output Port
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_TYPE(_DP_OUTPUT_PORT);

            // Set Logical Port 8 Peer Device Type
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_PEER_DEVICE_TYPE(3);

            // Set Logical Port Number
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_NUM(_DP_PORT8);

            // Set Logical Port 8 Message Capability
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_MSG_CAP(0);

            // Set Logical Port 8 Dp Plug Status
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_DP_PLUG_STATUS(_DP_PLUG);

            // Set Logical Port 8 Legacy Plug Status
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_LEGACY_PLUG_STATUS(_DP_UNPLUG);

            // Set Logical Port 8 DPCD Revision
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_DPCD_REV(ScalerDpRxMstGetDpVersion());

#if(_DP_SUPPORT == _ON)
            // Set Logical Port 8 GUID
            for(pData[0] = 0; pData[0] < 16; pData[0]++)
            {
                SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_GUID(pData[0], GET_REG_DP_DPCD_INFO(0x00, 0x00, (0x30 + pData[0])));
            }
#endif

            // Set Logical Port 8 Number Of Secondary Streams
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_NUM_OF_SDP(_DP_NUM_OF_SDP_STREAMS);

            // Set Logical Port 8 Number Of Secondary Stream Sinks
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_NUM_OF_SDP_SINK(_DP_NUM_OF_SDP_SINKS);

            //===== Set Physical Port Info. ======
#if(_DP_TX_SUPPORT == _ON)
            // Setting Physical Port1 is Output Port
            SET_DP_DOWN_REPLY_LINK_ADDR_PORT1_TYPE(_DP_OUTPUT_PORT);

            // Set Physical Port1 Peer Device Type
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_PEER_DEVICE_TYPE(GET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE());

            // Set Physical Port1 Message Capability
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_MSG_CAP(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS());

            // Set Physical Port1 Dp Plug Status
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_DP_PLUG_STATUS(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS());
            SET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS());

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                // Set Physical Port1 DPCD Revision
                SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_DPCD_REV(GET_DP_TX_DOWNSTREAM_DPCD_REV());

                if(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_NO_SUPPORT)
                {
                    // Set Physical Port1 Number Of Secondary Streams
                    SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_NUM_OF_SDP(GET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP());

                    // Set Physical Port1 Number Of Secondary Stream Sinks
                    SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_NUM_OF_SDP_SINK(GET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK());
                }
                else
                {
                    // Set Physical Port1 Number Of Secondary Streams
                    SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_NUM_OF_SDP(0);

                    // Set Physical Port1 Number Of Secondary Stream Sinks
                    SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_NUM_OF_SDP_SINK(0);
                }
            }
            else
            {
                // Set Physical Port1 DPCD Revision
                SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_DPCD_REV(0);

                // Set Physical Port1 Number Of Secondary Streams
                SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_NUM_OF_SDP(0);

                // Set Physical Port1 Number Of Secondary Stream Sinks
                SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_NUM_OF_SDP_SINK(0);
            }

            // Set Physical Port Number
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_NUM(_DP_PORT1);

            // Set Physical Port1 Legacy Plug Status
            SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_LEGACY_PLUG_STATUS(_DP_UNPLUG);

            // Set Physical Port1 GUID
            for(pData[0] = 0; pData[0] < 16; pData[0]++)
            {
                SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_GUID(pData[0], 0);
            }

#endif // End of #if(_DP_TX_SUPPORT == _ON)

            break;

        case _DP_MSG_ENUM_PATH_RESOURCES:

            // Set Message Body Length = 6
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(6);

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_ENUM_PATH_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_ENUM_PATH_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_ENUM_PATH_MSG_REQUEST_ID(_DP_MSG_ENUM_PATH_RESOURCES);

            // Set Port Num
            SET_DP_DOWN_REPLY_ENUM_PATH_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_ENUM_PATH_MSG_PORT_NUM());

            // Set Full PBN
            SET_DP_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN(_HW_DP_MST_MAC_MAX_BW);

            if(ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE1) == 0)
            {
                // Set Available PBN
                SET_DP_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(_HW_DP_MST_MAC_MAX_BW);
            }
            else
            {
                // Set Available PBN
                SET_DP_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(0);
            }

            break;

        case _DP_MSG_ALLOCATE_PAYLOAD:

            // Set Message Body Length = 5
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(5);

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REQUEST_ID(_DP_MSG_ALLOCATE_PAYLOAD);

            // Set Port Number
            SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM());

            // Set Payload ID
            SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID());

            if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM() == _DP_PORT8)
            {
                if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() <= _HW_DP_MST_MAC_MAX_BW)
                {
                    SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN());
                }
                else
                {
                    // Allocate Failed
                }
            }

            break;

        case _DP_MSG_QUERY_PAYLOAD:

            // Set Message Body Length = 4
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(4);

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_REQUEST_ID(_DP_MSG_QUERY_PAYLOAD);

            // Set Port Number
            SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM());

            // For Initial Stream Mux Source
            pData[0] = 0;

            if(GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM() == _DP_PORT8)
            {
                pData[0] = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE1) - 1;
            }
#if(_DP_TX_SUPPORT == _ON)
            else if(GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM() == _DP_PORT1)
            {
                pData[0] = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE2) - 1;
            }
#endif
            if(GET_DP_RX_MST_ST_START_POSITION(pData[0]) != 0)
            {
                // Calculate Allocated PBN
                PDATA_WORD(1) = (WORD)GET_DP_PBN_PER_TIME_SLOT(GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x00), (GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x01) & 0x1F)) * GET_DP_RX_MST_STREAM_TIME_SLOT(pData[0]);

                // Set Allocated PBN
                SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_ALLOCATED_PBN(PDATA_WORD(1));
            }
            else
            {
                // Set Allocated PBN
                SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_ALLOCATED_PBN(0);
            }

            break;

        case _DP_MSG_CLEAR_PAYLOAD_ID_TABLE:

            // Set Message Body Length = 1
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(1);

            // Set Reply Type
            SET_DP_DOWN_REPLY_CLEAR_ID_TABLE_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_CLEAR_ID_TABLE_MSG_REQUEST_ID(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);

            break;

        case _DP_MSG_POWER_UP_PHY:

            // Set Message Body Length = 2
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(2);

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_POWER_UP_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_POWER_UP_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_POWER_UP_MSG_REQUEST_ID(_DP_MSG_POWER_UP_PHY);

            // Set Port Number
            SET_DP_DOWN_REPLY_POWER_UP_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_POWER_UP_MSG_PORT_NUM());

            break;

        case _DP_MSG_POWER_DOWN_PHY:

            // Set Message Body Length = 2
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(2);

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_POWER_DOWN_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_POWER_DOWN_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_POWER_DOWN_MSG_REQ_ID(_DP_MSG_POWER_DOWN_PHY);

            // Set Port Number
            SET_DP_DOWN_REPLY_POWER_DOWN_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_POWER_DOWN_MSG_PORT_NUM());

            break;

        case _DP_MSG_REMOTE_DPCD_READ:

            // Set Message Body Length
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH((3 + GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ()));

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_MSG_REMOTE_DPCD_READ_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_REQUEST_ID(_DP_MSG_REMOTE_DPCD_READ);

            // Set Port Number
            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_PORT_NUM());

            // Set Number Of Read Byte
            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_NUM_OF_READ(GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ());

            break;

        case _DP_MSG_REMOTE_DPCD_WRITE:

            // Set Message Body Length
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(2);

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_REMOTE_DPCE_WRITE_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REQUEST_ID(_DP_MSG_REMOTE_DPCD_WRITE);

            // Set Port Number
            SET_DP_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_PORT_NUM());

            break;

        case _DP_MSG_REMOTE_I2C_READ:

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_REQUEST_ID(_DP_MSG_REMOTE_I2C_READ);

            // Set Port Number
            SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_REMOTE_I2C_READ_MSG_PORT_NUM());

            break;

        case _DP_MSG_REMOTE_I2C_WRITE:

            // Set Message Body Length
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(2);

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REQUEST_ID(_DP_MSG_REMOTE_I2C_WRITE);

            // Set Port Number
            SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_PORT_NUM());

            break;

#if(_DP_TX_SUPPORT == _ON)
        case _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS:

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REQUEST_ID(_DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS);

            pData[0] = ScalerDpRxMstSearchMatchStream(GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());

            // Check if Stream ID of Down Request MSG is equal to Stream ID in the ST Source 1 and Stream ID is valid
            if(pData[0] == _DP_ST_NONE)
            {
                pData[1] = _DP_STREAM_NOT_EXIST;
            }
            else
            {
                pData[1] = (GET_DP_RX_HDCP_POWER_STATUS_NORMAL() == _TRUE) ? _DP_STREAM_ACTIVE : _DP_STREAM_NOT_ACTIVE;
            }

            // Set Stream State
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE(pData[1]);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if(GET_DP_RX_HDCP2_MODE() == _ENABLE)
            {
                // Set Message Body Length = 36
                SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(36);

                // Set Stream Repeater Function Present
                SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT(GET_DP_RX_HDCP2_REPEATER_SUPPORTED());

                // Set Stream Authentication
                if(GET_DP_RX_HDCP2_REPEATER_SUPPORTED() == _TRUE)
                {
                    SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(GET_DP_RX_HDCP2_AUTH_PROC_DONE());
                }
                else
                {
                    SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(GET_DP_RX_HDCP_AUTH_ENCRYPTION());
                }

                // Set Stream Output CP Type => HDCP 2.x
                SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE(_HDCP_FEATURE_2_2);
            }
            else
#endif
            {
                // Set Message Body Length = 24
                SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(24);

                // Set Stream Repeater Function Present
                SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT(GET_DP_RX_HDCP_REPEATER_SUPPORTED());

                // Set Stream Authentication
                SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(GET_DP_RX_HDCP_AUTH_PROC_DONE());

                // Set Stream Output CP Type => HDCP 1.x
                SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE(_HDCP_FEATURE_1_1);
            }

            // Set Stream Encryption
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION(GET_DP_RX_HDCP_AUTH_ENCRYPTION());

            if(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT)
            {
                pData[0] = _DP_OUTPUT_SINK_TYPE_MSG_SUPPORT;
            }
            else
            {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                pData[0] = ((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)) ? _DP_OUTPUT_SINK_TYPE_MSG_NO_SUPPORT : _DP_OUTPUT_SINK_TYPE_NON_AUTHENTICABLE;
#else
                pData[0] = (GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE) ? _DP_OUTPUT_SINK_TYPE_MSG_NO_SUPPORT : _DP_OUTPUT_SINK_TYPE_NON_AUTHENTICABLE;
#endif
            }

            // Set Stream Output Sink Type
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE(pData[0]);

            // Set Signed
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED(_TRUE);

            // Set Stream ID
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID(GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if(GET_DP_RX_HDCP2_MODE() == _ENABLE)
            {
                DebugMessageHDCP2("[QSE] Rx : Cal Signature L'", 0);

                // Calculate Signature L'
                ScalerDpRxMstQueryEncryptionWriteSha256Input(GET_DP_RX_HDCP2_REPEATER_SUPPORTED());

                // Set Stream State Signature L'
                for(pData[0] = 0; pData[0] < 32; pData[0]++)
                {
                    SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(pData[0], GET_REG_DP_RX_HDCP_SHA256_RESULT(pData[0]));
                }
            }
            else
#endif
            {
                // Calculate Signature L'
                ScalerDpRxMstQueryEncryptionWriteShaInput();

                // Set Stream State Signature L'
                for(pData[0] = 0; pData[0] < 20; pData[0]++)
                {
                    SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(pData[0], GET_REG_DP_RX_HDCP_SHA_RESULT(pData[0]));
                }
            }

            break;
#endif // End of #if(_DP_TX_SUPPORT == _ON)

        default:

            break;
    }

    if(GET_DP_MSG_REQUEST_ID() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE)
    {
        // Set LCT
        SET_REG_DP_RX_UPSTREAM_REPLY_LCT(1);

        // Set LCR
        SET_REG_DP_RX_UPSTREAM_REPLY_LCR(0x00);
    }
    else
    {
        // Set LCT
        SET_REG_DP_RX_UPSTREAM_REPLY_LCT(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCT());

        // Set LCR
        SET_REG_DP_RX_UPSTREAM_REPLY_LCR(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCT() - 1);

        // Set RAD
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD0(GET_REG_DP_RX_DOWN_REQUEST_RAD0());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD1(GET_REG_DP_RX_DOWN_REQUEST_RAD1());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD2(GET_REG_DP_RX_DOWN_REQUEST_RAD2());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD3(GET_REG_DP_RX_DOWN_REQUEST_RAD3());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD4(GET_REG_DP_RX_DOWN_REQUEST_RAD4());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD5(GET_REG_DP_RX_DOWN_REQUEST_RAD5());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD6(GET_REG_DP_RX_DOWN_REQUEST_RAD6());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD7(GET_REG_DP_RX_DOWN_REQUEST_RAD7());
    }

    // Set Broadcast and Path
    SET_REG_DP_RX_UPSTREAM_REPLY_BROADCAST(GET_REG_DP_RX_DOWN_REQUEST_MSG_BROADCAST());
    SET_REG_DP_RX_UPSTREAM_REPLY_PATH(GET_REG_DP_RX_DOWN_REQUEST_MSG_PATH());

    // Set MSN
    SET_REG_DP_RX_UPSTREAM_REPLY_MSN(GET_REG_DP_RX_DOWN_REQUEST_MSG_MSN());
}

//--------------------------------------------------
// Description  : Rx Error MSG Reply for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstIllegalMsgReply(void)
{
    if(GET_DP_MSG_REQUEST_ID() == _DP_MSG_REMOTE_I2C_READ)
    {
        // Set Message Body Length
        SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(20);

        SET_DP_REPLY_REMOTE_I2C_READ_NAK_REP_TYPE(_DP_MSG_NACK);
        SET_DP_REPLY_REMOTE_I2C_READ_NAK_REQUESET_ID(_DP_MSG_REMOTE_I2C_READ);

#if(_DP_SUPPORT == _ON)
        // Set GUID
        for(pData[0] = 0; pData[0] < 16; pData[0]++)
        {
            SET_DP_REPLY_REMOTE_I2C_READ_NAK_GUID(pData[0], GET_REG_DP_DPCD_INFO(0x00, 0x00, (0x30 + pData[0])));
        }
#endif

        SET_DP_REPLY_REMOTE_I2C_READ_NAK_PORT(8);
        SET_DP_REPLY_REMOTE_I2C_READ_NAK_REASON(_BAD_PARAM);
        SET_DP_REPLY_REMOTE_I2C_READ_NAK_ZEROS();
    }
    else
    {
        // Set Message Body Length
        SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(19);

        // Set Reply Type
        SET_DP_REPLY_ILLEGAL_MSG_REPLY_TYPE(_DP_MSG_NACK);

        // Set Request ID
        SET_DP_REPLY_ILLEGAL_MSG_REQUESET_ID(GET_DP_MSG_REQUEST_ID());

#if(_DP_SUPPORT == _ON)
        // Set GUID
        for(pData[0] = 0; pData[0] < 16; pData[0]++)
        {
            SET_DP_REPLY_ILLEGAL_MSG_GUID(pData[0], GET_REG_DP_DPCD_INFO(0x00, 0x00, (0x30 + pData[0])));
        }
#endif

        // Set NACK Reason
        SET_DP_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);

        // Set NACK Data
        SET_DP_REPLY_ILLEGAL_MSG_NACK_DATA(0);
    }

    // Set LCT
    SET_REG_DP_RX_UPSTREAM_REPLY_LCT(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCT() - GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR());

    // Set LCR
    SET_REG_DP_RX_UPSTREAM_REPLY_LCR(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCT() - GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() - 1);

    // Valid # of RAD = LCT - 1, # of RAD Modify = LCT -1 - LCR
    // Set RAD
    if((GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() % 2) == 0)
    {
        pData[0] = GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() / 2;
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD0(GET_REG_DP_RX_DOWN_REQUEST_RAD_MSB(pData[0]));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD1(GET_REG_DP_RX_DOWN_REQUEST_RAD_LSB(pData[0]));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD2(GET_REG_DP_RX_DOWN_REQUEST_RAD_MSB(pData[0] + 1));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD3(GET_REG_DP_RX_DOWN_REQUEST_RAD_LSB(pData[0] + 1));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD4(GET_REG_DP_RX_DOWN_REQUEST_RAD_MSB(pData[0] + 2));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD5(GET_REG_DP_RX_DOWN_REQUEST_RAD_LSB(pData[0] + 2));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD6(GET_REG_DP_RX_DOWN_REQUEST_RAD_MSB(pData[0] + 3));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD7(GET_REG_DP_RX_DOWN_REQUEST_RAD_LSB(pData[0] + 3));
    }
    else
    {
        pData[0] = (GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() - 1) / 2;
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD0(GET_REG_DP_RX_DOWN_REQUEST_RAD_LSB(pData[0]));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD1(GET_REG_DP_RX_DOWN_REQUEST_RAD_MSB(pData[0] + 1));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD2(GET_REG_DP_RX_DOWN_REQUEST_RAD_LSB(pData[0] + 1));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD3(GET_REG_DP_RX_DOWN_REQUEST_RAD_MSB(pData[0] + 2));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD4(GET_REG_DP_RX_DOWN_REQUEST_RAD_LSB(pData[0] + 2));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD5(GET_REG_DP_RX_DOWN_REQUEST_RAD_MSB(pData[0] + 3));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD6(GET_REG_DP_RX_DOWN_REQUEST_RAD_LSB(pData[0] + 3));
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD7(GET_REG_DP_RX_DOWN_REQUEST_RAD_MSB(pData[0] + 4));
    }

    // Set Broadcast and Path
    SET_REG_DP_RX_UPSTREAM_REPLY_BROADCAST(GET_REG_DP_RX_DOWN_REQUEST_MSG_BROADCAST());
    SET_REG_DP_RX_UPSTREAM_REPLY_PATH(GET_REG_DP_RX_DOWN_REQUEST_MSG_PATH());

    // Set MSN
    SET_REG_DP_RX_UPSTREAM_REPLY_MSN(GET_REG_DP_RX_DOWN_REQUEST_MSG_MSN());

    /*
    if(GET_DP_RX_MSG_ERROR_TYPE() != _NONE_MSG_ERROR)
    {
        switch(GET_DP_RX_MSG_ERROR_TYPE())
        {
            case _WRITE_FAILURE:

                break;

            case _INVALID_RAD:

                break;

            case _CRC_FAILURE:

                break;

            case _BAD_PARAM:

                break;

            case _DEFER:

                break;

            case _LINK_FAILURE:

                break;

            case _NO_RESOURCES:

                break;

            case _DPCD_FAIL:

                break;

            case _I2C_NAK:

                break;

            case _ALLOCATE_FAIL:

                break;

            default:

                break;
        }

        //SET_DP_RX_EVENT(_NONE_MSG_ERROR);
    }
    */
}

//--------------------------------------------------
// Description  : Check MSG CRC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRxMstCheckMsgCRC(BYTE ucMSGDirection)
{
    if(ucMSGDirection == _DP_DOWN_REQUEST_MSG)
    {
        if(GET_DP_RX_DOWN_REQUEST_BUF_PRIORITY() == _DP_DOWN_REQUEST_BUF0)
        {
            // Check BUF0 Down Request CRC
            if(GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_ERROR() == _NONE_MSG_ERROR)
            {
                return _TRUE;
            }
            else
            {
                // CLR Flag
                CLR_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_ERROR();

                CLR_REG_DP_RX_DOWN_REQUEST_BUF0();

                return _FALSE;
            }
        }
        else
        {
            // Check BUF1 Down Request CRC
            if(GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_ERROR() == _NONE_MSG_ERROR)
            {
                return _TRUE;
            }
            else
            {
                // CLR Flag
                CLR_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_ERROR();

                CLR_REG_DP_RX_DOWN_REQUEST_BUF1();

                return _FALSE;
            }
        }
    }
    else if(ucMSGDirection == _DP_UP_REPLY_MSG)
    {
        if(GET_DP_RX_UP_REPLY_BUF_PRIORITY() == _DP_DOWN_REQUEST_BUF0)
        {
            // Check BUF0 Down Request CRC
            if(GET_REG_DP_RX_UP_REPLY_BUF0_MSG_ERROR() == _NONE_MSG_ERROR)
            {
                return _TRUE;
            }
            else
            {
                // CLR Flag
                CLR_REG_DP_RX_UP_REPLY_BUF0_MSG_ERROR();

                CLR_REG_DP_RX_UP_REPLY_BUF0();

                return _FALSE;
            }
        }
        else
        {
            // Check BUF1 Down Request CRC
            if(GET_REG_DP_RX_UP_REPLY_BUF1_MSG_ERROR() == _NONE_MSG_ERROR)
            {
                return _TRUE;
            }
            else
            {
                // CLR Flag
                CLR_REG_DP_RX_UP_REPLY_BUF1_MSG_ERROR();

                CLR_REG_DP_RX_UP_REPLY_BUF1();

                return _FALSE;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Rx Sync Payload ID Table with Upstream uPacket Tx
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstSyncPayloadIDTable_EXINT0(void) using 1
{
    EnumDpStreamNum enumID2ST = _DP_ST_NONE;
    BYTE ucPayloadID = GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x01, 0xC0);
    BYTE ucIDStartPosition = GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x01, 0xC1);
    BYTE ucTimeslotLength = GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x01, 0xC2);
    BYTE ucExistedIDLength = ScalerDpRxMstGetExistedIDLength_EXINT0(ucPayloadID, ucIDStartPosition);
    BYTE ucMstTempIndex = 0;

    if((ucIDStartPosition == 0) && (ucPayloadID != 0))
    {
        for(pData_EXINT[0] = 1; pData_EXINT[0] <= 63; pData_EXINT[0]++)
        {
            if(GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + pData_EXINT[0])) == ucPayloadID)
            {
                ucIDStartPosition = pData_EXINT[0];

                break;
            }
        }
    }

    switch(ScalerDpRxMstGetSyncTableAction_EXINT0(ucPayloadID))
    {
        case _DP_ADD_PAYLOAD_ID:

            if(ucTimeslotLength != 0)
            {
                enumID2ST = ScalerDpRxMstSearchMatchStream_EXINT0(0);

                if(enumID2ST != _DP_ST_NONE)
                {
                    // Mapping Payload ID to ST to ID Table
                    g_pucDpStreamToIdMapping[enumID2ST] = ucPayloadID;

                    // Modify Payload ID Table for Add ID
                    ScalerDpRxMstModifyPayloadTable_EXINT0(63, ucIDStartPosition, 0, ucTimeslotLength, ucPayloadID, _DP_TIMESLOT_SHIFT_DOWN);
                }
            }

            break;

        case _DP_CLEAR_PAYLOAD_ID_TABLE:

            // Clear Payload ID Table
            SET_REG_DP_RX_CLEAR_PAYLOAD_ID_TABLE();
            CLR_REG_DP_RX_CLEAR_PAYLOAD_ID_TABLE();

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 5; pData_EXINT[0]++)
            {
                g_pucDpStreamToIdMapping[pData_EXINT[0]] = 0;
            }

            break;

        case _DP_MODIFY_PAYLOAD_ID_TABLE:

            if(ucTimeslotLength == 0)
            {
                // Modify Payload ID Table for Del ID
                ScalerDpRxMstModifyPayloadTable_EXINT0((ucIDStartPosition + ucExistedIDLength), 63, ucPayloadID, ucExistedIDLength, 0, _DP_TIMESLOT_SHIFT_UP);

                enumID2ST = ScalerDpRxMstSearchMatchStream_EXINT0(ucPayloadID);

                if(enumID2ST != _DP_ST_NONE)
                {
                    // Delete Payload ID from ST to ID Table
                    g_pucDpStreamToIdMapping[enumID2ST] = 0;

                    for(ucMstTempIndex = _DP_ST_SOURCE1; ucMstTempIndex <= _DP_ST_SOURCE5; ucMstTempIndex++)
                    {
                        if((enumID2ST + 1) == ScalerDpRxMstStreamMuxCheck_EXINT0(ucMstTempIndex))
                        {
                            ScalerDpRxMstStreamMuxBackup_EXINT0(ucMstTempIndex, _DP_ST_NONE);
                        }
                    }
                }
            }
            else
            {
                // Increase Time Slots
                if(ucTimeslotLength > ucExistedIDLength)
                {
                    // Modify Payload ID Table for Increase ID Time slots
                    ScalerDpRxMstModifyPayloadTable_EXINT0(63, ucIDStartPosition, 0, (ucTimeslotLength - ucExistedIDLength), ucPayloadID, _DP_TIMESLOT_SHIFT_DOWN);
                }
                else
                {
                    // Modify Payload ID Table for Decrease ID Time slots
                    ScalerDpRxMstModifyPayloadTable_EXINT0((ucIDStartPosition + ucTimeslotLength), 63, ucPayloadID, (ucExistedIDLength - ucTimeslotLength), 0, _DP_TIMESLOT_SHIFT_UP);
                }
            }

            break;

        default:

            break;
    }

    // Exclude Clear ID Table
    if(!((ucPayloadID == 0x00) && (ucIDStartPosition == 0x00) && (ucTimeslotLength == 0x3F)))
    {
        if((enumID2ST != _DP_ST_NONE) && (ucTimeslotLength == 0))
        {
            // Setting Start Position
            SET_DP_RX_MST_ST_START_POSITION(enumID2ST, 0);

            // Setting End Position
            SET_DP_RX_MST_ST_END_POSITION(enumID2ST, 0);
        }

        // Set STx Start and End Position
        ScalerDpRxMstStreamPositionSetting_EXINT0();
    }

    // VC Payload ID Table Updated
    SET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0, ((GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, 0xC0) & ~(_BIT1 | _BIT0)) | _BIT0));

    // Manual Set Allocated Flag(HW may miss ACT sequence)
    SET_DP_RX_MANUAL_FORCE_SET_ACT();

    // Clr 0x002C0 IRQ Flag
    CLR_REG_DP_RX_2C0_IRQ_FLAG();

    // Enable 0x002C0 IRQ
    SET_REG_DP_RX_2C0_IRQ();
}

//--------------------------------------------------
// Description  : Setting StreamX Starting and End Position
// Input Value  : Stream Number and Time Slot Modification
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstStreamPositionSetting_EXINT0(void) using 1
{
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 63; pData_EXINT[0]++)
    {
        pData_EXINT[1] = GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC1 + pData_EXINT[0]));

        if(pData_EXINT[1] != 0)
        {
            for(pData_EXINT[2] = 0; pData_EXINT[2] < 5; pData_EXINT[2]++)
            {
                if((g_pucDpStreamToIdMapping[pData_EXINT[2]] == pData_EXINT[1]))
                {
                    // Setting Start Position
                    SET_DP_RX_MST_ST_START_POSITION(pData_EXINT[2], (pData_EXINT[0] + 1));

                    while(GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC1 + pData_EXINT[0] + 1)) == pData_EXINT[1])
                    {
                        pData_EXINT[0] = pData_EXINT[0] + 1;
                    }

                    // Setting End Position
                    SET_DP_RX_MST_ST_END_POSITION(pData_EXINT[2], (pData_EXINT[0] + 1));
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get Stream Source Status
// Input Value  : Source Number
// Output Value : Stream Number
//--------------------------------------------------
BYTE ScalerDpRxMstStreamMuxCheck(BYTE ucSourceNum)
{
    return (GET_DP_RX_MST_ST_SOURCE_BACKUP(ucSourceNum) == _DP_ST_NONE) ? 0 : (GET_DP_RX_MST_ST_SOURCE_BACKUP(ucSourceNum) + 1);
}

//--------------------------------------------------
// Description  : Get Stream Source Status
// Input Value  : Source Number
// Output Value : Stream Number
//--------------------------------------------------
BYTE ScalerDpRxMstStreamMuxCheck_EXINT0(BYTE ucSourceNum) using 1
{
    return (GET_DP_RX_MST_ST_SOURCE_BACKUP(ucSourceNum) == _DP_ST_NONE) ? 0 : (GET_DP_RX_MST_ST_SOURCE_BACKUP(ucSourceNum) + 1);
}

//--------------------------------------------------
// Description  : Check Msg Buffer Free
// Input Value  : None
// Output Value : True / False
//--------------------------------------------------
bit ScalerDpRxMstCheckMsgBufferFree(void)
{
    if(GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE)
    {
        return _FALSE;
    }

    if(GET_DP_REQUEST_POOL_FREE() == _FALSE)
    {
        return _FALSE;
    }

    if(GET_DP_REPLY_POOL_FREE() == _FALSE)
    {
        return _FALSE;
    }

    if(GET_DP_RX_REPLY_BUF_FREE() == _FALSE)
    {
        return _FALSE;
    }

    if(GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH() == _TRUE)
    {
        return _FALSE;
    }

    if(GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH() == _TRUE)
    {
        return _FALSE;
    }

#if(_DP_TX_SUPPORT == _ON)
    if(GET_DP_TX_RD_BUFFER_STATUS() != _DP_TX_READ_BUF_EMPTY)
    {
        return _FALSE;
    }
#endif

    return _TRUE;
}


//--------------------------------------------------
// Description  : Check Add Payload ID Whether Existed Or Not
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRxMstCheckIDExisted(BYTE ucPayloadID)
{
    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        // ID Exist in STx to ID Table
        if(ucPayloadID == g_pucDpStreamToIdMapping[pData[0]])
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Add Payload ID Whether Existed Or Not
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpRxMstCheckIDExisted_EXINT0(BYTE ucPayloadID) using 1
{
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 5; pData_EXINT[0]++)
    {
        // ID Exist in STx to ID Table
        if(ucPayloadID == g_pucDpStreamToIdMapping[pData_EXINT[0]])
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Calculate Existed ID Length
// Input Value  : None
// Output Value : Existed ID Length
//--------------------------------------------------
BYTE ScalerDpRxMstGetExistedIDLength_EXINT0(BYTE ucPayloadID, BYTE ucStartPosition) using 1
{
    pData_EXINT[1] = 0;

    for(pData_EXINT[0] = 0; pData_EXINT[0] < (64 - ucStartPosition); pData_EXINT[0]++)
    {
        if(GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + ucStartPosition + pData_EXINT[0])) == ucPayloadID)
        {
            pData_EXINT[1] = pData_EXINT[1] + 1;
        }
        else
        {
            break;
        }
    }

    return pData_EXINT[1];
}

//--------------------------------------------------
// Description  : Decide Payload ID Table Action
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpRxMstGetSyncTableAction_EXINT0(BYTE ucPayloadID) using 1
{
    if(ucPayloadID == 0)
    {
        return _DP_CLEAR_PAYLOAD_ID_TABLE;
    }
    else if(ScalerDpRxMstCheckIDExisted_EXINT0(ucPayloadID) == _TRUE)
    {
        return _DP_MODIFY_PAYLOAD_ID_TABLE;
    }
    else
    {
        return _DP_ADD_PAYLOAD_ID;
    }
}

//--------------------------------------------------
// Description  : Check Add Position Overlap
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpRxMstCheckAddPoistionLegal_EXINT0(BYTE ucIDStartPosition) using 1
{
    if(GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + ucIDStartPosition)) != 0)
    {
        for(pData_EXINT[0] = 0; pData_EXINT[0] < 5; pData_EXINT[0]++)
        {
            if(g_pucDpStreamToIdMapping[pData_EXINT[0]] == GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + ucIDStartPosition)))
            {
                if(GET_DP_RX_MST_ST_START_POSITION(pData_EXINT[0]) == ucIDStartPosition)
                {
                    return _TRUE;
                }
                else
                {
                    // Add Position Error
                    return _FALSE;
                }
            }
        }
    }
    else
    {
        // Add New Payload
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Modify Payload ID Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstModifyPayloadTable_EXINT0(BYTE ucSearchStartPoint, BYTE ucSearchEndPoint, BYTE ucInitialID, BYTE ucDuplicateNum, BYTE ucPayloadID, bit bShiftDirection) using 1
{
    if(bShiftDirection == _DP_TIMESLOT_SHIFT_DOWN)
    {
        if(ScalerDpRxMstCheckAddPoistionLegal_EXINT0(ucSearchEndPoint) == _TRUE)
        {
            for(pData_EXINT[1] = ucSearchStartPoint; pData_EXINT[1] >= ucSearchEndPoint; pData_EXINT[1]--)
            {
                if(GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + pData_EXINT[1])) != ucInitialID)
                {
                    ucInitialID = GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + pData_EXINT[1]));

                    for(pData_EXINT[2] = 0; pData_EXINT[2] < ucDuplicateNum; pData_EXINT[2]++)
                    {
                        SET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + pData_EXINT[1] + pData_EXINT[2] + 1), ucInitialID);
                    }
                }
            }
        }

        if(GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + ucSearchEndPoint)) != ucPayloadID)
        {
            for(pData_EXINT[0] = 0; pData_EXINT[0] < ucDuplicateNum; pData_EXINT[0]++)
            {
                SET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + ucSearchEndPoint + pData_EXINT[0]), ucPayloadID);
            }
        }
    }
    else if(bShiftDirection == _DP_TIMESLOT_SHIFT_UP)
    {
        for(pData_EXINT[1] = ucSearchStartPoint; pData_EXINT[1] <= ucSearchEndPoint; pData_EXINT[1]++)
        {
            if(GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + pData_EXINT[1])) != ucInitialID)
            {
                ucInitialID = GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + pData_EXINT[1]));

                for(pData_EXINT[2] = 0; pData_EXINT[2] < ucDuplicateNum; pData_EXINT[2]++)
                {
                    SET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + pData_EXINT[1] + pData_EXINT[2] - ucDuplicateNum), ucInitialID);
                }
            }
        }

        if((pData_EXINT[1] > 63) && (GET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, 0xFF) != 0))
        {
            for(pData_EXINT[2] = 0; pData_EXINT[2] < ucDuplicateNum; pData_EXINT[2]++)
            {
                SET_REG_DP_DPCD_INFO_EXINT0(0x00, 0x02, (0xC0 + ucSearchEndPoint - pData_EXINT[2]), 0);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Search ST1 ~ ST5 to Match Input Paramater
// Input Value  : Target ID
// Output Value : Match ST Number Index
//--------------------------------------------------
EnumDpStreamNum ScalerDpRxMstSearchMatchStream(BYTE ucTargetID)
{
    for(pData[0] = _DP_ST_1; pData[0] <= _DP_ST_5; pData[0]++)
    {
        // Setting STx to ID Table
        if(g_pucDpStreamToIdMapping[pData[0]] == ucTargetID)
        {
            return pData[0];
        }
    }
    return _DP_ST_NONE;
}

//--------------------------------------------------
// Description  : Search ST1 ~ ST5 to Match Input Paramater
// Input Value  : Target ID
// Output Value : Match ST Number Index
//--------------------------------------------------
EnumDpStreamNum ScalerDpRxMstSearchMatchStream_EXINT0(BYTE ucTargetID) using 1
{
    for(pData_EXINT[0] = _DP_ST_1; pData_EXINT[0] <= _DP_ST_5; pData_EXINT[0]++)
    {
        // Setting STx to ID Table
        if(g_pucDpStreamToIdMapping[pData_EXINT[0]] == ucTargetID)
        {
            return pData_EXINT[0];
        }
    }

    return _DP_ST_NONE;
}

//--------------------------------------------------
// Description  : Set Flag to Generate Clear Payload ID Table MSG
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstCableUnplugReset(BYTE ucInputPort)
{
    if(((ucInputPort == _D0_INPUT_PORT) && (g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)) ||
       ((ucInputPort == _D1_INPUT_PORT) && (g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)))
    {
        SET_DP_RX_MST_MODE_STATE(_DP_RX_MST_MODE_STATUS_NONE_MSG);

        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT);

        // Disable DOWN_REP_MSG_RDY Bit INT
        CLR_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ();

        // Disable UP_REQ_MSG_RDY INT
        CLR_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ();

        // Clear DOWN_REP_MSG_RDY & UP_REQ_MSG_RDY Bit of DPCD Table
        SET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03, (GET_REG_DP_DPCD_INFO(0x00, 0x20, 0x03) & ~(_BIT5 | _BIT4)));

        // Clear Buffer
        CLR_REG_DP_RX_USTERAM_REPLY_BUF();

        // Disable Message Upstream
        CLR_REG_DP_RX_UPSTREAM_REPLY();

        // Free Reply Buffer
        SET_DP_RX_REPLY_BUF_FREE();

#if(_D0_DP_EXIST == _ON)

        if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
        {
            // Clear Aux ch Power On Wake Up Flag
            CLR_DP_RX0_AUX_CH_POWER_ON_WAKE_UP();
        }
#endif

#if(_D1_DP_EXIST == _ON)

        if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
        {
            // Clear Aux ch Power On Wake Up Flag
            CLR_DP_RX1_AUX_CH_POWER_ON_WAKE_UP();
        }
#endif
        // Clear Payload ID Table
        SET_REG_DP_RX_CLEAR_PAYLOAD_ID_TABLE();
        CLR_REG_DP_RX_CLEAR_PAYLOAD_ID_TABLE();

        // Reset ST1 ~ ST5
        ScalerDpRxMstStreamPositionReset();

        // Reset ST1_Source ~ ST5_Source
        ScalerDpRxMstClrStreamMuxBackup();

        for(pData[0] = 0; pData[0] < 5; pData[0]++)
        {
            g_pucDpStreamToIdMapping[pData[0]] = 0;
        }

        // Disable MST
        CLR_REG_DP_RX_MST_ENABLE();

        // Reset 0x111h
        SET_REG_DP_RX_AUX_TO_MANUAL_MODE();

        // Disable 0x111 IRQ
        CLR_REG_DP_RX_111_IRQ();

        SET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11, 0x00);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
        if((GET_REG_DP_DPCD_INFO(0x00, 0x00, 0x21) & _BIT0) == _BIT0)
#endif
        {
            // CLR Flag
            CLR_REG_DP_RX_111_IRQ_FLAG();

            // Enable 0x111 IRQ
            SET_REG_DP_RX_111_IRQ();
        }

        SET_REG_DP_RX_AUX_TO_AUTO_MODE();

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
        // Disable 0x1C2 IRQ
        CLR_REG_DP_RX_1C2_IRQ();

        g_enumDpMSTCapablePort = _DP_MST_NO_PORT;

        // Sync MST Target Port
        SET_DP_RX_TARGET_MST_PORT(g_enumDpMSTCapablePort);
#endif

#if(_DP_TX_SUPPORT == _ON)

        CLR_DP_RX_SELF_GEN_UP_REQUEST_RETRY();

        CLR_DP_TX_SELF_GEN_UP_REQUEST_MSG();

        CLR_DP_TX_UP_REQUEST_BYPASS_REGEN();

        // Clear Up_Req Bypass MSG Back Up
        CLR_DP_TX_UP_REQUEST_BACKUP_DATA();

        CLR_DP_TX_BYPASS_UNPLUG_CSN_IS_PENDING();

        // Clear Up Req Msg Header
        CLR_DP_TX_UP_REQUEST_MSG_HEADER();

        SET_DP_TOTAL_RECEIVED_MSG_COUNT(0);

        SET_DP_TX_RECEIVED_MSG_COUNT(0);

        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_MSG_COUNT_RESET_EVENT);
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_CABLE_STATUS_CHANGE_EVENT);
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_FORCE_REBUILD_TOPOLOGY_EVENT);

        CLR_DP_TX_WAIT_TOPOLOGY_REBUILD_MSG();

        if((GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
        {
            // Clear Payload ID Only if Downstream PID Table is Not Empty
            if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0xC1, 1, pData) == _TRUE)
            {
                if(pData[0] != 0x00)
                {
                    // Set Flag to Gen Clear ID Table Msg
                    SET_DP_GEN_DOWN_REQUEST_MSG(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);
                }
            }
        }

        // Disable MST to SST
        SET_DP_RX_MST2SST_ENABLE(_DISABLE);

        // Set DPTx Force To Idle Pattern
        ScalerDpTxForceIdlePatternSetting();

        // Clear DP Tx Stream Source
        ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

        // CLR TX Read Buffer Status
        SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

        CLR_DP_TX_DOWN_REPLY_READ_DISABLE();

        CLR_DP_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();
#endif
    }

    ScalerSyncDpRxClrSourceWritePowerUp(ucInputPort);
}

//--------------------------------------------------
// Description  : Reset ST1 ~ ST5
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstStreamPositionReset(void)
{
    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        // Reset Start Position
        SET_DP_RX_MST_ST_START_POSITION(pData[0], 0x00);

        // Reset End Position
        SET_DP_RX_MST_ST_END_POSITION(pData[0], 0x00);
    }
}

//--------------------------------------------------
// Description  : Reset ST1_Source ~ ST5_Source Mux
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstStreamMuxReset(void)
{
    SET_REG_DP_RX_MST_ST1_SOURCE_STATUS(0x00);
    SET_REG_DP_RX_MST_ST2_SOURCE_STATUS(0x00);
    SET_REG_DP_RX_MST_ST3_SOURCE_STATUS(0x00);
    SET_REG_DP_RX_MST_ST4_SOURCE_STATUS(0x00);
    SET_REG_DP_RX_MST_ST5_SOURCE_STATUS(0x00);
}

//--------------------------------------------------
// Description  : Backup ST1_Source ~ ST5_Source Mux
// Input Value  : EnumDpStreamSourceNum, EnumDpStreamNum
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstStreamMuxBackup(EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumStreamNum)
{
    SET_DP_RX_MST_ST_SOURCE_BACKUP(enumSourceNum, enumStreamNum);

    // If deleting case, set directly
    if(enumStreamNum == _DP_ST_NONE)
    {
        ScalerDpRxMstStreamMuxRestore(enumSourceNum);
    }
    else
    {
        SET_DP_RX_MST_ST_SOURCE_CHANGE();
    }
}

//--------------------------------------------------
// Description  : Backup ST1_Source ~ ST5_Source Mux
// Input Value  : EnumDpStreamSourceNum, EnumDpStreamNum
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstStreamMuxBackup_EXINT0(EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumStreamNum) using 1
{
    SET_DP_RX_MST_ST_SOURCE_BACKUP(enumSourceNum, enumStreamNum);

    // If deleting case, set directly
    if(enumStreamNum == _DP_ST_NONE)
    {
        ScalerDpRxMstStreamMuxRestore_EXINT0(enumSourceNum);
    }
    else
    {
        SET_DP_RX_MST_ST_SOURCE_CHANGE();
    }
}

//--------------------------------------------------
// Description  : Backup ST1_Source ~ ST5_Source Clear
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstClrStreamMuxBackup(void)
{
    EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

    for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE5; enumSourceNum++)
    {
        ScalerDpRxMstStreamMuxBackup(enumSourceNum, _DP_ST_NONE);
    }
}

//--------------------------------------------------
// Description  : Backup ST1_Source ~ ST5_Source Clear
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstClrStreamMuxBackup_EXINT0(void) using 1
{
    EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

    for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE5; enumSourceNum++)
    {
        ScalerDpRxMstStreamMuxBackup_EXINT0(enumSourceNum, _DP_ST_NONE);
    }
}

//--------------------------------------------------
// Description  : Restore ST1_Source ~ ST5_Source Mux
// Input Value  : EnumDpStreamSourceNum
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstStreamMuxRestore(EnumDpStreamSourceNum enumSourceNum)
{
    switch(enumSourceNum)
    {
        case _DP_ST_SOURCE1:

            // Set ST_Source1
            SET_REG_DP_RX_MST_ST1_SOURCE_STATUS(ScalerDpRxMstStreamMuxCheck(enumSourceNum));

            break;

        case _DP_ST_SOURCE2:

            // Set ST_Source2
            SET_REG_DP_RX_MST_ST2_SOURCE_STATUS(ScalerDpRxMstStreamMuxCheck(enumSourceNum));

            break;

        case _DP_ST_SOURCE3:

            // Set ST_Source3
            SET_REG_DP_RX_MST_ST3_SOURCE_STATUS(ScalerDpRxMstStreamMuxCheck(enumSourceNum));

            break;

        case _DP_ST_SOURCE4:

            // Set ST_Source4
            SET_REG_DP_RX_MST_ST4_SOURCE_STATUS(ScalerDpRxMstStreamMuxCheck(enumSourceNum));

            break;

        case _DP_ST_SOURCE5:

            // Set ST_Source5
            SET_REG_DP_RX_MST_ST5_SOURCE_STATUS(ScalerDpRxMstStreamMuxCheck(enumSourceNum));

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Restore ST1_Source ~ ST5_Source Mux
// Input Value  : EnumDpStreamSourceNum
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstStreamMuxRestore_EXINT0(EnumDpStreamSourceNum enumSourceNum) using 1
{
    switch(enumSourceNum)
    {
        case _DP_ST_SOURCE1:

            // Set ST_Source1
            SET_REG_DP_RX_MST_ST1_SOURCE_STATUS_EXINT(ScalerDpRxMstStreamMuxCheck_EXINT0(enumSourceNum));

            break;

        case _DP_ST_SOURCE2:

            // Set ST_Source2
            SET_REG_DP_RX_MST_ST2_SOURCE_STATUS_EXINT(ScalerDpRxMstStreamMuxCheck_EXINT0(enumSourceNum));

            break;

        case _DP_ST_SOURCE3:

            // Set ST_Source3
            SET_REG_DP_RX_MST_ST3_SOURCE_STATUS_EXINT(ScalerDpRxMstStreamMuxCheck_EXINT0(enumSourceNum));

            break;

        case _DP_ST_SOURCE4:

            // Set ST_Source4
            SET_REG_DP_RX_MST_ST4_SOURCE_STATUS_EXINT(ScalerDpRxMstStreamMuxCheck_EXINT0(enumSourceNum));

            break;

        case _DP_ST_SOURCE5:

            // Set ST_Source5
            SET_REG_DP_RX_MST_ST5_SOURCE_STATUS_EXINT(ScalerDpRxMstStreamMuxCheck_EXINT0(enumSourceNum));

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check ST1_Source ~ ST5_Source Mux Change
// Input Value  : EnumDpStreamSourceNum
// Output Value : boolean
//--------------------------------------------------
void ScalerDpRxMstStreamMuxChangeHandler(void)
{
    if(GET_DP_RX_MST_ST_SOURCE_CHANGE() == _FALSE)
    {
        return;
    }
    else
    {
        EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

        for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE5; enumSourceNum++)
        {
            ScalerDpRxMstStreamMuxRestore(enumSourceNum);
        }

        CLR_DP_RX_MST_ST_SOURCE_CHANGE();
    }
}

//--------------------------------------------------
// Description  : Reset Backup Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstBackupInfoReset(void)
{
    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
    {
        // Reset Restore TimeSlot Info
        ScalerSetByte(PB5_03_STHD_CTRL_2, 0x00);
        ScalerSetByte(PB5_04_STHD_CTRL_3, 0x00);
        ScalerSetByte(PB5_05_STHD_CTRL_4, 0x00);
        ScalerSetByte(PB5_06_STHD_CTRL_5, 0x00);
        ScalerSetByte(PB5_07_STHD_CTRL_6, 0x00);
        ScalerSetByte(PB5_08_STHD_CTRL_7, 0x00);
        ScalerSetByte(PB5_09_STHD_CTRL_8, 0x00);
        ScalerSetByte(PB5_0A_STHD_CTRL_9, 0x00);
        ScalerSetByte(PB5_0B_STHD_CTRL_10, 0x00);
        ScalerSetByte(PB5_0C_STHD_CTRL_11, 0x00);
        ScalerSetByte(PB5_0D_SOURCE_SEL_0, 0x00);
        ScalerSetByte(PB5_0E_SOURCE_SEL_1, 0x00);
    }
    else if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        // Reset Restore TimeSlot Info
        ScalerSetByte(PB8_03_STHD_CTRL_2, 0x00);
        ScalerSetByte(PB8_04_STHD_CTRL_3, 0x00);
        ScalerSetByte(PB8_05_STHD_CTRL_4, 0x00);
        ScalerSetByte(PB8_06_STHD_CTRL_5, 0x00);
        ScalerSetByte(PB8_07_STHD_CTRL_6, 0x00);
        ScalerSetByte(PB8_08_STHD_CTRL_7, 0x00);
        ScalerSetByte(PB8_09_STHD_CTRL_8, 0x00);
        ScalerSetByte(PB8_0A_STHD_CTRL_9, 0x00);
        ScalerSetByte(PB8_0B_STHD_CTRL_10, 0x00);
        ScalerSetByte(PB8_0C_STHD_CTRL_11, 0x00);
        ScalerSetByte(PB8_0D_SOURCE_SEL_0, 0x00);
        ScalerSetByte(PB8_0E_SOURCE_SEL_1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Get DP Version
// Input Value  : None
// Output Value : DP Version
//--------------------------------------------------
EnumDpVersionType ScalerDpRxMstGetDpVersion(void)
{
    // Get Logical Port 8 DPCD Revision
    if((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) || (g_enumDpMSTCapablePort == _DP_MST_RX6_PORT))
    {
#if(_D0_DP_EXIST == _ON)
        if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)
        {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            return ScalerDpRx0GetDpcdInfo(0x00, 0x22, 0x00);
#else
            return g_ucDpRx0DPCD02200hValue;
#endif
        }
        else
        {
            return _DP_VERSION_1_2;
        }
#endif
    }
    else if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
#if(_D1_DP_EXIST == _ON)
        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)
        {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            return ScalerDpRx1GetDpcdInfo(0x00, 0x22, 0x00);
#else
            return g_ucDpRx1DPCD02200hValue;
#endif
        }
        else
        {
            return _DP_VERSION_1_2;
        }
#endif
    }

    return _DP_VERSION_1_2;
}

//--------------------------------------------------
// Description  : Get DP Mst Capable Port
// Input Value  : None
// Output Value : EnumDPMSTPort
//--------------------------------------------------
EnumDPMSTPort ScalerDpRxMstGetCapablePort(void)
{
    return g_enumDpMSTCapablePort;
}

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DP Mst Input Port
// Input Value  : None
// Output Value : EnumSourceSearchPort
//--------------------------------------------------
EnumSourceSearchPort ScalerDpRxMstGetInputPort(EnumDPMSTPort enumMstPort)
{
    switch(enumMstPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _DP_MST_RX0_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(g_bDpMSTD6Capable == _TRUE)
            {
                return _D6_INPUT_PORT;
            }
            else
#endif
            {
                return _D0_INPUT_PORT;
            }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _DP_MST_RX1_PORT:
            return _D1_INPUT_PORT;
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _DP_MST_RX6_PORT:
            return _D6_INPUT_PORT;
#endif

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Get DP Source Msg enable (DPCD 00111h[1])
// Input Value  : DP Input Port
// Output Value : _TRUE --> MST enable, _FALSE --> SST
//--------------------------------------------------
bit ScalerDpRxMstGetSrcMsgEnable(EnumSourceSearchPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) == _BIT1);
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:

            return (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) == _BIT1);
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get DP MST Capaility (DPCD 00021[0])
// Input Value  : DP Input Port
// Output Value : _TRUE --> MST enable, _FALSE --> SST
//--------------------------------------------------
bit ScalerDpRxMstGetMstCapability(EnumSourceSearchPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0);
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:

            return (ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0);
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Mst Capability Switch
// Input Value  : _ENABLE / _DISABLE
// Output Value : Change or not
//--------------------------------------------------
void ScalerDpRxMstCapabilitySwitch(EnumSourceSearchPort enumInputPort, bit bEn)
{
    switch(enumInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            if(bEn == _ENABLE)
            {
                if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == 0x00)
                {
                    SET_DP_RX0_AUX_MANUAL_MODE();

                    if(g_enumDpMSTCapablePort == _DP_MST_NO_PORT)
                    {
                        // Down Sream Port Present
                        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x01);

                        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x21, 0x01);

                        // Rx0 Clear DPCD 111 IRQ Flag
                        ScalerSetBit(PB7_B3_AUX_SPECIAL_IRQ_FLAG, ~_BIT7, _BIT7);

                        // Rx0 Enable DPCD 111 IRQ
                        ScalerSetBit(PB7_B2_AUX_SPECIAL_IRQ_EN, ~_BIT7, _BIT7);

                        ScalerDpRx0SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);

                        DebugMessageRx0("Rx0 MST cap on", 0);
                    }

                    SET_DP_RX0_AUX_AUTO_MODE();
                }
            }
            else
            {
                if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
                {
#if((_DP_DPCD_DFP_PRESENT_REF_TO == _DP_TX_EXISTENCE) && (_DP_TX_SUPPORT == _ON))
                    // Down Sream Port Present
                    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x01);
#else
                    // Down Sream Port isn't Present
                    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x05, 0x00);
#endif

                    ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x21, 0x00);

                    // Rx0 Disable DPCD 111/1C2 IRQ
                    ScalerSetBit(PB7_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);

                    ScalerDpRx0SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);

                    DebugMessageRx0("Rx0 MST cap off", 0);
                }
            }

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:

            if(bEn == _ENABLE)
            {
                if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == 0x00)
                {
                    SET_DP_RX1_AUX_MANUAL_MODE();

                    if(g_enumDpMSTCapablePort == _DP_MST_NO_PORT)
                    {
                        // Down Sream Port Present
                        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x05, 0x01);

                        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x21, 0x01);

                        // Rx1 Clear DPCD 111 IRQ Flag
                        ScalerSetBit(PBA_B3_AUX_SPECIAL_IRQ_FLAG, ~_BIT7, _BIT7);

                        // Rx1 Enable DPCD 111 IRQ
                        ScalerSetBit(PBA_B2_AUX_SPECIAL_IRQ_EN, ~_BIT7, _BIT7);

                        ScalerDpRx1SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);

                        DebugMessageRx1("Rx1 MST cap on", 0);
                    }

                    SET_DP_RX1_AUX_AUTO_MODE();
                }
            }
            else
            {
                if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
                {
#if((_DP_DPCD_DFP_PRESENT_REF_TO == _DP_TX_EXISTENCE) && (_DP_TX_SUPPORT == _ON))
                    // Down Sream Port Present
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x05, 0x01);
#else
                    // Down Sream Port isn't Present
                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x05, 0x00);
#endif

                    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x21, 0x00);

                    // Rx1 Disable DPCD 111/1C2 IRQ
                    ScalerSetBit(PBA_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);

                    ScalerDpRx1SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);

                    DebugMessageRx1("Rx1 MST cap off", 0);
                }
            }

            break;
#endif
        default:
            break;
    }
}

#if((_D0_DP_EXIST == _ON) && (_D1_DP_EXIST == _ON))
//--------------------------------------------------
// Description  : DP Mst Capability Switch
// Input Value  : _ENABLE / _DISABLE
// Output Value : Change or not
//--------------------------------------------------
void ScalerDpRxMstCapabilitySwitch_EXINT0(EnumSourceSearchPort enumInputPort, bit bEn) using 1
{
    switch(enumInputPort)
    {
#if(_D0_DP_EXIST == _ON)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            if(bEn == _ENABLE)
            {
                if(ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x21, _BIT0) == 0x00)
                {
                    SET_DP_RX0_AUX_MANUAL_MODE_EXINT();

                    if(g_enumDpMSTCapablePort == _DP_MST_NO_PORT)
                    {
                        // Down Sream Port Present
                        ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x00, 0x05, 0x01);

                        ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x00, 0x21, 0x01);

                        // Rx0 Clear DPCD 111 IRQ Flag
                        ScalerSetBit_EXINT(PB7_B3_AUX_SPECIAL_IRQ_FLAG, ~_BIT7, _BIT7);

                        // Rx0 Enable DPCD 111 IRQ
                        ScalerSetBit_EXINT(PB7_B2_AUX_SPECIAL_IRQ_EN, ~_BIT7, _BIT7);

                        ScalerDpRx0SetHotPlugEvent_EXINT0(_DP_MST_LONG_HPD_EVENT);
                    }

                    SET_DP_RX0_AUX_AUTO_MODE();
                }
            }
            else
            {
                if(ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x21, _BIT0) == _BIT0)
                {
#if((_DP_DPCD_DFP_PRESENT_REF_TO == _DP_TX_EXISTENCE) && (_DP_TX_SUPPORT == _ON))
                    // Down Sream Port Present
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x00, 0x05, 0x01);
#else
                    // Down Sream Port isn't Present
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x00, 0x05, 0x00);
#endif

                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x00, 0x21, 0x00);

                    // Rx0 Disable DPCD 111/1C2 IRQ
                    ScalerSetBit_EXINT(PB7_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);

                    ScalerDpRx0SetHotPlugEvent_EXINT0(_DP_MST_LONG_HPD_EVENT);
                }
            }

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _D1_INPUT_PORT:

            if(bEn == _ENABLE)
            {
                if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x21, _BIT0) == 0x00)
                {
                    SET_DP_RX1_AUX_MANUAL_MODE_EXINT();

                    if(g_enumDpMSTCapablePort == _DP_MST_NO_PORT)
                    {
                        // Down Sream Port Present
                        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x00, 0x05, 0x01);

                        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x00, 0x21, 0x01);

                        // Rx1 Clear DPCD 111 IRQ Flag
                        ScalerSetBit_EXINT(PBA_B3_AUX_SPECIAL_IRQ_FLAG, ~_BIT7, _BIT7);

                        // Rx1 Enable DPCD 111 IRQ
                        ScalerSetBit_EXINT(PBA_B2_AUX_SPECIAL_IRQ_EN, ~_BIT7, _BIT7);

                        ScalerDpRx1SetHotPlugEvent_EXINT0(_DP_MST_LONG_HPD_EVENT);
                    }

                    SET_DP_RX1_AUX_AUTO_MODE_EXINT();
                }
            }
            else
            {
                if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x21, _BIT0) == _BIT0)
                {
#if((_DP_DPCD_DFP_PRESENT_REF_TO == _DP_TX_EXISTENCE) && (_DP_TX_SUPPORT == _ON))
                    // Down Sream Port Present
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x00, 0x05, 0x01);
#else
                    // Down Sream Port isn't Present
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x00, 0x05, 0x00);
#endif

                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x00, 0x21, 0x00);

                    // Rx1 Disable DPCD 111/1C2 IRQ
                    ScalerSetBit_EXINT(PBA_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);

                    ScalerDpRx1SetHotPlugEvent_EXINT0(_DP_MST_LONG_HPD_EVENT);
                }
            }

            break;
#endif
        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : DP Rx Msg Initial
// Input Value  : _DP_MST_RX0_PORT or _DP_MST_RX0_PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstInitial_EXINT0(EnumDPMSTPort enumRxMstPort) using 1
{
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)

    if(enumRxMstPort == _DP_MST_RX6_PORT)
    {
        g_bDpMSTD6Capable = _TRUE;

#if(_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)
        enumRxMstPort = _DP_MST_RX0_PORT;
#endif
    }
    else
    {
        g_bDpMSTD6Capable = _FALSE;
    }
#endif

    ScalerDpMstReset_EXINT0(g_enumDpMSTCapablePort);

    g_enumDpMSTCapablePort = enumRxMstPort;

    // Sync MST Target Port
    SET_DP_RX_TARGET_MST_PORT(g_enumDpMSTCapablePort);

    SET_DP_RX_MST_MODE_STATE(_DP_RX_MST_MODE_STATUS_NONE_MSG);

    SET_DP_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_DOWN_REQUEST_BUF0);

    // Free Request Array
    SET_DP_REQUEST_POOL_FREE();

    // Free Reply Array
    SET_DP_REPLY_POOL_FREE();

    // Free Reply Buffer
    SET_DP_RX_REPLY_BUF_FREE();

    ScalerDpRxMstClrStreamMuxBackup_EXINT0();

    // Reset MSG FSM as 0x01000 Writen
    RST_REG_DP_RX_DOWN_REQUEST_FSM_WRITTEN_EXINT();
    RST_REG_DP_RX_UP_REPLY_FSM_WRITTEN_EXINT();

    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
    {
#if((_D0_DP_EXIST == _ON) && (_D1_DP_EXIST == _ON))
        // Rx1 Disable DPCD 1C2 IRQ
        ScalerSetBit_EXINT(PBA_B2_AUX_SPECIAL_IRQ_EN, ~_BIT4, 0x00);
#endif

#if(_D0_DP_EXIST == _ON)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if(g_bDpMSTD6Capable == _TRUE)
        {
            SET_DP_MST_DDCRAM_SIZE(_D6_EMBEDDED_DDCRAM_MAX_SIZE);
        }
        else
#endif
        {
            SET_DP_MST_DDCRAM_SIZE(_D0_EMBEDDED_DDCRAM_MAX_SIZE);
        }

        // Enable Buf0 / Buf1 Receive Capability
        SET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE_EXINT();
        SET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE_EXINT();
        SET_REG_DP_RX_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE_EXINT();
        SET_REG_DP_RX_UP_REPLY_BUF1_MSG_RECEIVE_ENABLE_EXINT();

        // Disable 0x01000 write IRQ
        CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE_EXINT();

        // Rx0 Clear DPCD 1C2 IRQ Flag
        ScalerSetBit_EXINT(PB7_B3_AUX_SPECIAL_IRQ_FLAG, ~_BIT4, _BIT4);

        // Rx0 Enable DPCD 1C2 IRQ
        ScalerSetBit_EXINT(PB7_B2_AUX_SPECIAL_IRQ_EN, ~_BIT4, _BIT4);

        // Rx0 Clear Payload ID Table
        ScalerSetBit_EXINT(PB7_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, _BIT6);
        ScalerSetBit_EXINT(PB7_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, 0x00);
#endif
    }
    else if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
#if((_D0_DP_EXIST == _ON) && (_D1_DP_EXIST == _ON))
        // Rx0 Disable DPCD 1C2 IRQ
        ScalerSetBit_EXINT(PB7_B2_AUX_SPECIAL_IRQ_EN, ~_BIT4, 0x00);
#endif

#if(_D1_DP_EXIST == _ON)

        SET_DP_MST_DDCRAM_SIZE(_D1_EMBEDDED_DDCRAM_MAX_SIZE);

        // Enable Buf0 / Buf1 Receive Capability
        SET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE_EXINT();
        SET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE_EXINT();
        SET_REG_DP_RX_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE_EXINT();
        SET_REG_DP_RX_UP_REPLY_BUF1_MSG_RECEIVE_ENABLE_EXINT();

        // Disable 0x01000 write IRQ
        CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE_EXINT();

        // Rx1 Clear DPCD 1C2 IRQ Flag
        ScalerSetBit_EXINT(PBA_B3_AUX_SPECIAL_IRQ_FLAG, ~_BIT4, _BIT4);

        // Rx1 Enable DPCD 1C2 IRQ
        ScalerSetBit_EXINT(PBA_B2_AUX_SPECIAL_IRQ_EN, ~_BIT4, _BIT4);

        // Rx1 Clear Payload ID Table
        ScalerSetBit_EXINT(PBA_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, _BIT6);
        ScalerSetBit_EXINT(PBA_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, 0x00);
#endif
    }
    else
    {
        CLR_DP_MST_DDCRAM_SIZE();

#if(_D0_DP_EXIST == _ON)
        // Rx0 Disable DPCD 1C2 IRQ
        ScalerSetBit_EXINT(PB7_B2_AUX_SPECIAL_IRQ_EN, ~_BIT4, 0x00);
#endif

#if(_D1_DP_EXIST == _ON)
        // Rx1 Disable DPCD 1C2 IRQ
        ScalerSetBit_EXINT(PBA_B2_AUX_SPECIAL_IRQ_EN, ~_BIT4, 0x00);
#endif
    }

    // Mst Port Select
    ScalerDpRxMstPortSel_EXINT0();

    // Mst MSG Port Select
    ScalerDpRxMstMsgPortSel_EXINT0();
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : L' = SHA-1(Stream-Status | Q_id | S_id | An | Bksv | V | M0)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstQueryEncryptionWriteShaInput(void)
{
    // Reset SHA Block counter
    CLR_REG_DP_RX_SHA_ENABLE();

    // Start to Write SHA-1 Transform Input
    SET_REG_DP_RX_SHA_ENABLE();

    // 1. Write Data into SHA-1 Transform Input
    SET_REG_DP_RX_SHA_INPUT_0(g_unDpReplyPool.pucData[1]);
    SET_REG_DP_RX_SHA_INPUT_1(g_unDpReplyPool.pucData[2]);
    SET_REG_DP_RX_SHA_INPUT_2(g_pucDPMsgQueryEncryptClientId[0]);
    SET_REG_DP_RX_SHA_INPUT_3(g_pucDPMsgQueryEncryptClientId[1]);

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_RX_SHA_INPUT_DB();

    // 2. Write Data into SHA-1 Transform Input
    SET_REG_DP_RX_SHA_INPUT_0(g_pucDPMsgQueryEncryptClientId[2]);
    SET_REG_DP_RX_SHA_INPUT_1(g_pucDPMsgQueryEncryptClientId[3]);
    SET_REG_DP_RX_SHA_INPUT_2(g_pucDPMsgQueryEncryptClientId[4]);
    SET_REG_DP_RX_SHA_INPUT_3(g_pucDPMsgQueryEncryptClientId[5]);

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_RX_SHA_INPUT_DB();

    // 3. Write Data into SHA-1 Transform Input
    SET_REG_DP_RX_SHA_INPUT_0(g_pucDPMsgQueryEncryptClientId[6]);
    SET_REG_DP_RX_SHA_INPUT_1(GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());
    SET_REG_DP_RX_SHA_INPUT_2(GET_DP_RX_HDCP_AN(0));
    SET_REG_DP_RX_SHA_INPUT_3(GET_DP_RX_HDCP_AN(1));

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_RX_SHA_INPUT_DB();

    // 4. Write Data into SHA-1 Transform Input
    SET_REG_DP_RX_SHA_INPUT_0(GET_DP_RX_HDCP_AN(2));
    SET_REG_DP_RX_SHA_INPUT_1(GET_DP_RX_HDCP_AN(3));
    SET_REG_DP_RX_SHA_INPUT_2(GET_DP_RX_HDCP_AN(4));
    SET_REG_DP_RX_SHA_INPUT_3(GET_DP_RX_HDCP_AN(5));

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_RX_SHA_INPUT_DB();

    // 5. Write Data into SHA-1 Transform Input
    SET_REG_DP_RX_SHA_INPUT_0(GET_DP_RX_HDCP_AN(6));
    SET_REG_DP_RX_SHA_INPUT_1(GET_DP_RX_HDCP_AN(7));
    SET_REG_DP_RX_SHA_INPUT_2(g_pucHdcpBksvBackup[0]);
    SET_REG_DP_RX_SHA_INPUT_3(g_pucHdcpBksvBackup[1]);

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_RX_SHA_INPUT_DB();

    // 6. Write Data into SHA-1 Transform Input
    SET_REG_DP_RX_SHA_INPUT_0(g_pucHdcpBksvBackup[2]);
    SET_REG_DP_RX_SHA_INPUT_1(g_pucHdcpBksvBackup[3]);
    SET_REG_DP_RX_SHA_INPUT_2(g_pucHdcpBksvBackup[4]);
    SET_REG_DP_RX_SHA_INPUT_3(GET_DP_RX_HDCP_V(0));

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_RX_SHA_INPUT_DB();

    pData[0] = 1;

    do
    {
        // 7~10. Write Data into SHA-1 Transform Input
        SET_REG_DP_RX_SHA_INPUT_0(GET_DP_RX_HDCP_V(pData[0]));
        SET_REG_DP_RX_SHA_INPUT_1(GET_DP_RX_HDCP_V(pData[0] + 1));
        SET_REG_DP_RX_SHA_INPUT_2(GET_DP_RX_HDCP_V(pData[0] + 2));
        SET_REG_DP_RX_SHA_INPUT_3(GET_DP_RX_HDCP_V(pData[0] + 3));

        // Enable write 32-bit data to SHA-1 block
        SET_REG_DP_RX_SHA_INPUT_DB();

        pData[0] += 4;
    }
    while(pData[0] < 17);

    // 11. Write Data into SHA-1 Transform Input
    SET_REG_DP_RX_SHA_INPUT_0(GET_DP_RX_HDCP_V(17));
    SET_REG_DP_RX_SHA_INPUT_1(GET_DP_RX_HDCP_V(18));
    SET_REG_DP_RX_SHA_INPUT_2(GET_DP_RX_HDCP_V(19));
    SET_REG_DP_RX_SHA_INPUT_3(GET_REG_DP_RX_HDCP_M0_0());

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_RX_SHA_INPUT_DB();

    // 12. Write Data into SHA-1 Transform Input
    SET_REG_DP_RX_SHA_INPUT_0(GET_REG_DP_RX_HDCP_M0_1());
    SET_REG_DP_RX_SHA_INPUT_1(GET_REG_DP_RX_HDCP_M0_2());
    SET_REG_DP_RX_SHA_INPUT_2(GET_REG_DP_RX_HDCP_M0_3());
    SET_REG_DP_RX_SHA_INPUT_3(GET_REG_DP_RX_HDCP_M0_4());

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_RX_SHA_INPUT_DB();

    // 13. Write Data into SHA-1 Transform Input
    SET_REG_DP_RX_SHA_INPUT_0(GET_REG_DP_RX_HDCP_M0_5());
    SET_REG_DP_RX_SHA_INPUT_1(GET_REG_DP_RX_HDCP_M0_6());
    SET_REG_DP_RX_SHA_INPUT_2(GET_REG_DP_RX_HDCP_M0_7());
    SET_REG_DP_RX_SHA_INPUT_3(0x80);

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_RX_SHA_INPUT_DB();

    for(pData[0] = 14; pData[0] < 16; pData[0]++)
    {
        // 14~15. Write 0x00 into the remaining SHA-1 Transform Input space
        SET_REG_DP_RX_SHA_INPUT_0(0x00);
        SET_REG_DP_RX_SHA_INPUT_1(0x00);
        SET_REG_DP_RX_SHA_INPUT_2(0x00);
        SET_REG_DP_RX_SHA_INPUT_3(0x00);

        // Enable write 32-bit data to SHA-1 block
        SET_REG_DP_RX_SHA_INPUT_DB();
    }

    // 16. Write 0x00 into the remaining SHA-1 Transform Input space
    SET_REG_DP_RX_SHA_INPUT_0(0x00);
    SET_REG_DP_RX_SHA_INPUT_1(0x00);
    SET_REG_DP_RX_SHA_INPUT_2(0x01);
    SET_REG_DP_RX_SHA_INPUT_3(0x98);

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_RX_SHA_INPUT_DB();

    // Run SHA-1 Process
    SET_DP_RX_HDCP_SHA_INPUT_RUN(_TRUE);
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : L' = SHA-256(Stream-Status | Q_id | S_id | Riv | Receiver_ID | V' | (Qid | Qid | Qid))
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstQueryEncryptionWriteSha256Input(bit bRepeater)
{
    BYTE pucHmacSha256Input[64];

    memset(pucHmacSha256Input, 0, sizeof(pucHmacSha256Input));

    // Load Stream-Status (16-Bits)
    for(pData[0] = 0; pData[0] < 2; pData[0]++)
    {
        pucHmacSha256Input[pData[0]] = g_unDpReplyPool.pucData[pData[0] + 1];
    }

    // Load Q_id (56-bits)
    for(pData[0] = 0; pData[0] < 7; pData[0]++)
    {
        pucHmacSha256Input[pData[0] + 2] = g_pucDPMsgQueryEncryptClientId[pData[0]];
    }

    // Load S_id (8-bits)
    pucHmacSha256Input[9] = GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID();

    // Load Link-id (64-bits) = riv
    for(pData[0] = 0; pData[0] < 8; pData[0]++)
    {
        pucHmacSha256Input[pData[0] + 10] = GET_REG_DP_DPCD_INFO(0x06, 0x93, (0x28 + pData[0]));
    }

    // Load Link_Pk (40-bits) = Receiver ID
    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        pucHmacSha256Input[pData[0] + 18] = g_stRxHdcp2DownLoadKeyType.pucHdcp2Certrx[pData[0]];
    }

    if(bRepeater == _TRUE)
    {
        // Load Link_S (160-bits) = V'
        for(pData[0] = 0; pData[0] < 20; pData[0]++)
        {
            pucHmacSha256Input[pData[0] + 23] = GET_DP_RX_HDCP2_V(pData[0]);
        }
    }
    else
    {
        // Load Link_S (160-bits) = (Qid | Qid | Qid[47:0])
        for(pData[0] = 0; pData[0] < 3; pData[0]++)
        {
            if(pData[0] == 2)
            {
                for(pData[1] = 0; pData[1] < 6; pData[1]++)
                {
                    pucHmacSha256Input[((pData[0] * 7) + pData[1]) + 23] = g_pucDPMsgQueryEncryptClientId[pData[1]];
                }
            }
            else
            {
                for(pData[1] = 0; pData[1] < 7; pData[1]++)
                {
                    pucHmacSha256Input[((pData[0] * 7) + pData[1]) + 23] = g_pucDPMsgQueryEncryptClientId[pData[1]];
                }
            }
        }
    }

    // Load SALT (168-bits) = Q_id | Q_id | Q_id
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        for(pData[1] = 0; pData[1] < 7; pData[1]++)
        {
            pucHmacSha256Input[((pData[0] * 7) + pData[1]) + 43] = g_pucDPMsgQueryEncryptClientId[pData[1]];
        }
    }

    SET_DP_RX_HDCP2_LPRIME_CAL(pucHmacSha256Input);
}
#endif // End for #if(_DP_HDCP_2_2_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Backup Client ID of MSG "QUERY_STREAM_ENCRYPTION_STATUS"
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRxMstQueryEncryptionBackupClientId(void)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < 7; ucIndex++)
    {
        g_pucDPMsgQueryEncryptClientId[ucIndex] = GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_CLIENT_ID(ucIndex);
    }
}
#endif // End for #if(_DP_TX_SUPPORT == _ON)

#endif // End for #if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))

