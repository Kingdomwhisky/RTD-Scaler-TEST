/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonDPTxHDCP2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_TX_HDCP2_IRQ_TYPE(x)                          (g_enumDpTxHdcp2CpirqType & (x))
#define SET_DP_TX_HDCP2_IRQ_TYPE(x)                          (g_enumDpTxHdcp2CpirqType |= (x))
#define CLR_DP_TX_HDCP2_IRQ_TYPE()                           (g_enumDpTxHdcp2CpirqType &= 0x00)
#define CLR_DP_TX_HDCP2_IRQ_TARGET_TYPE(x)                   (g_enumDpTxHdcp2CpirqType &= ~(x))

#define GET_DP_TX_HDCP2_AUTH_STATE()                         (g_stDpTxHdcp2AuthInfo.b4AuthState)
#define SET_DP_TX_HDCP2_AUTH_STATE(x)                        (g_stDpTxHdcp2AuthInfo.b4AuthState = (x))

#define GET_DP_TX_HDCP2_AUTH_STATE_CHANGE()                  (g_stDpTxHdcp2AuthInfo.b1AuthStateChange)
#define SET_DP_TX_HDCP2_AUTH_STATE_CHANGE()                  (g_stDpTxHdcp2AuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE()                  (g_stDpTxHdcp2AuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_TX_HDCP2_VERSION_SUPPORTED()                  (g_stDpTxHdcp2AuthInfo.b1Hdcp2Version)
#define SET_DP_TX_HDCP2_VERSION_SUPPORTED()                  (g_stDpTxHdcp2AuthInfo.b1Hdcp2Version = _TRUE)
#define CLR_DP_TX_HDCP2_VERSION_SUPPORTED()                  (g_stDpTxHdcp2AuthInfo.b1Hdcp2Version = _FALSE)

#define GET_DP_TX_HDCP2_CAPABLE_SUPPORTED()                  (g_stDpTxHdcp2AuthInfo.b1Hdcp2Capable)
#define SET_DP_TX_HDCP2_CAPABLE_SUPPORTED()                  (g_stDpTxHdcp2AuthInfo.b1Hdcp2Capable = _TRUE)
#define CLR_DP_TX_HDCP2_CAPABLE_SUPPORTED()                  (g_stDpTxHdcp2AuthInfo.b1Hdcp2Capable = _FALSE)

#define GET_DP_TX_HDCP2_REPEATER_SUPPORTED()                 (g_stDpTxHdcp2AuthInfo.b1Hdcp2Repeater)
#define SET_DP_TX_HDCP2_REPEATER_SUPPORTED()                 (g_stDpTxHdcp2AuthInfo.b1Hdcp2Repeater = _TRUE)
#define CLR_DP_TX_HDCP2_REPEATER_SUPPORTED()                 (g_stDpTxHdcp2AuthInfo.b1Hdcp2Repeater = _FALSE)

#define GET_DP_TX_HDCP2_AUTH_START()                         (g_stDpTxHdcp2AuthInfo.b1AuthStart)
#define SET_DP_TX_HDCP2_AUTH_START()                         (g_stDpTxHdcp2AuthInfo.b1AuthStart = _TRUE)
#define CLR_DP_TX_HDCP2_AUTH_START()                         (g_stDpTxHdcp2AuthInfo.b1AuthStart = _FALSE)

#define GET_DP_TX_HDCP2_CERTIFICATE_TIMEOUT()                (g_stDpTxHdcp2AuthInfo.b1CertificateTimeout)
#define SET_DP_TX_HDCP2_CERTIFICATE_TIMEOUT()                (g_stDpTxHdcp2AuthInfo.b1CertificateTimeout = _TRUE)
#define CLR_DP_TX_HDCP2_CERTIFICATE_TIMEOUT()                (g_stDpTxHdcp2AuthInfo.b1CertificateTimeout = _FALSE)

#define GET_DP_TX_HDCP2_H_PRIME_TIMEOUT()                    (g_stDpTxHdcp2AuthInfo.b1HprimeTimeout)
#define SET_DP_TX_HDCP2_H_PRIME_TIMEOUT()                    (g_stDpTxHdcp2AuthInfo.b1HprimeTimeout = _TRUE)
#define CLR_DP_TX_HDCP2_H_PRIME_TIMEOUT()                    (g_stDpTxHdcp2AuthInfo.b1HprimeTimeout = _FALSE)

#define GET_DP_TX_HDCP2_AUTH_HOLD()                          (g_stDpTxHdcp2AuthInfo.b1AuthHold)
#define SET_DP_TX_HDCP2_AUTH_HOLD()                          (g_stDpTxHdcp2AuthInfo.b1AuthHold = _TRUE)
#define CLR_DP_TX_HDCP2_AUTH_HOLD()                          (g_stDpTxHdcp2AuthInfo.b1AuthHold = _FALSE)

#define GET_DP_TX_HDCP2_LC_RETRY_COUNTER()                   (g_stDpTxHdcp2AuthInfo.usLcRetryCounter)
#define ADD_DP_TX_HDCP2_LC_RETRY_COUNTER()                   (g_stDpTxHdcp2AuthInfo.usLcRetryCounter++)
#define CLR_DP_TX_HDCP2_LC_RETRY_COUNTER()                   (g_stDpTxHdcp2AuthInfo.usLcRetryCounter = 0)

#define GET_DP_TX_HDCP2_ENCRYPT_DATA_TIMEOUT()               (g_stDpTxHdcp2AuthInfo.b1EncryptDataTimeout)
#define SET_DP_TX_HDCP2_ENCRYPT_DATA_TIMEOUT()               (g_stDpTxHdcp2AuthInfo.b1EncryptDataTimeout = _TRUE)
#define CLR_DP_TX_HDCP2_ENCRYPT_DATA_TIMEOUT()               (g_stDpTxHdcp2AuthInfo.b1EncryptDataTimeout = _FALSE)

#define GET_DP_TX_HDCP2_V_READY_TIMEOUT()                    (g_stDpTxHdcp2AuthInfo.b1VReadyTimeout)
#define SET_DP_TX_HDCP2_V_READY_TIMEOUT()                    (g_stDpTxHdcp2AuthInfo.b1VReadyTimeout = _TRUE)
#define CLR_DP_TX_HDCP2_V_READY_TIMEOUT()                    (g_stDpTxHdcp2AuthInfo.b1VReadyTimeout = _FALSE)

#define GET_DP_TX_HDCP2_POLLING_V_READY()                    (g_stDpTxHdcp2AuthInfo.b1PollingVReady)
#define SET_DP_TX_HDCP2_POLLING_V_READY()                    (g_stDpTxHdcp2AuthInfo.b1PollingVReady = _TRUE)
#define CLR_DP_TX_HDCP2_POLLING_V_READY()                    (g_stDpTxHdcp2AuthInfo.b1PollingVReady = _FALSE)

#define GET_DP_TX_HDCP2_V_READY_BIT()                        (g_stDpTxHdcp2AuthInfo.b1VReadyBit)
#define SET_DP_TX_HDCP2_V_READY_BIT()                        (g_stDpTxHdcp2AuthInfo.b1VReadyBit = _TRUE)
#define CLR_DP_TX_HDCP2_V_READY_BIT()                        (g_stDpTxHdcp2AuthInfo.b1VReadyBit = _FALSE)

#define GET_DP_TX_HDCP2_SEQUENCE_NUMBER_V()                  (g_ulDpTxHdcp2SeqNumV)
#define SET_DP_TX_HDCP2_SEQUENCE_NUMBER_V(x)                 (g_ulDpTxHdcp2SeqNumV = (x))
#define CLR_DP_TX_HDCP2_SEQUENCE_NUMBER_V()                  (g_ulDpTxHdcp2SeqNumV = 0)

#define GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT()                (g_stDpTxHdcp2AuthInfo.b5RxInfoDevice)
#define SET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT(x)               (g_stDpTxHdcp2AuthInfo.b5RxInfoDevice = ((x) & 0x1F))

#define GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT_EXCEED()         (g_stDpTxHdcp2AuthInfo.b1RxInfoDeviceExceed)
#define SET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT_EXCEED()         (g_stDpTxHdcp2AuthInfo.b1RxInfoDeviceExceed = _TRUE)
#define CLR_DP_TX_HDCP2_RXINFO_DEVICE_COUNT_EXCEED()         (g_stDpTxHdcp2AuthInfo.b1RxInfoDeviceExceed = _FALSE)

#define GET_DP_TX_HDCP2_RXINFO_DEPTH()                       (g_stDpTxHdcp2AuthInfo.b3RxInfoDepth)
#define SET_DP_TX_HDCP2_RXINFO_DEPTH(x)                      (g_stDpTxHdcp2AuthInfo.b3RxInfoDepth = ((x) & 0x07))

#define GET_DP_TX_HDCP2_RXINFO_DEPTH_EXCEED()                (g_stDpTxHdcp2AuthInfo.b1RxInfoDepthExceed)
#define SET_DP_TX_HDCP2_RXINFO_DEPTH_EXCEED()                (g_stDpTxHdcp2AuthInfo.b1RxInfoDepthExceed = _TRUE)
#define CLR_DP_TX_HDCP2_RXINFO_DEPTH_EXCEED()                (g_stDpTxHdcp2AuthInfo.b1RxInfoDepthExceed = _FALSE)

#define GET_DP_TX_HDCP2_RXINFO_HDCP20_REPEATER_DOWNSTREAM()  (g_stDpTxHdcp2AuthInfo.b1Hdcp20RepeaterDownstream)
#define SET_DP_TX_HDCP2_RXINFO_HDCP20_REPEATER_DOWNSTREAM()  (g_stDpTxHdcp2AuthInfo.b1Hdcp20RepeaterDownstream = _TRUE)
#define CLR_DP_TX_HDCP2_RXINFO_HDCP20_REPEATER_DOWNSTREAM()  (g_stDpTxHdcp2AuthInfo.b1Hdcp20RepeaterDownstream = _FALSE)

#define GET_DP_TX_HDCP2_RXINFO_HDCP1_DOWNSTREAM()            (g_stDpTxHdcp2AuthInfo.b1Hdcp1DeviceDownstream)
#define SET_DP_TX_HDCP2_RXINFO_HDCP1_DOWNSTREAM()            (g_stDpTxHdcp2AuthInfo.b1Hdcp1DeviceDownstream = _TRUE)
#define CLR_DP_TX_HDCP2_RXINFO_HDCP1_DOWNSTREAM()            (g_stDpTxHdcp2AuthInfo.b1Hdcp1DeviceDownstream = _FALSE)

#define GET_DP_TX_HDCP2_DOWNSTREAM_EVENT()                   (g_stDpTxHdcp2AuthInfo.ucAuthDownstreamEvent)
#define SET_DP_TX_HDCP2_DOWNSTREAM_EVENT(x)                  (g_stDpTxHdcp2AuthInfo.ucAuthDownstreamEvent = (x))
#define CLR_DP_TX_HDCP2_DOWNSTREAM_EVENT()                   (g_stDpTxHdcp2AuthInfo.ucAuthDownstreamEvent = _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_NONE)

#define GET_DP_TX_HDCP2_CONTENT_STREAM_MANAGEMENT()          (g_stDpTxHdcp2AuthInfo.b1AuthContentStreamManage)
#define SET_DP_TX_HDCP2_CONTENT_STREAM_MANAGEMENT()          (g_stDpTxHdcp2AuthInfo.b1AuthContentStreamManage = _TRUE)
#define CLR_DP_TX_HDCP2_CONTENT_STREAM_MANAGEMENT()          (g_stDpTxHdcp2AuthInfo.b1AuthContentStreamManage = _FALSE)

#define GET_DP_TX_HDCP2_SEQUENCE_NUMBER_M()                  (g_ulDpTxHdcp2SeqNumM)
#define ADD_DP_TX_HDCP2_SEQUENCE_NUMBER_M()                  (g_ulDpTxHdcp2SeqNumM++)
#define CLR_DP_TX_HDCP2_SEQUENCE_NUMBER_M()                  (g_ulDpTxHdcp2SeqNumM = 0)

#define GET_DP_TX_HDCP2_M_PRIME_TIMEOUT()                    (g_stDpTxHdcp2AuthInfo.b1MprimeTimeout)
#define SET_DP_TX_HDCP2_M_PRIME_TIMEOUT()                    (g_stDpTxHdcp2AuthInfo.b1MprimeTimeout = _TRUE)
#define CLR_DP_TX_HDCP2_M_PRIME_TIMEOUT()                    (g_stDpTxHdcp2AuthInfo.b1MprimeTimeout = _FALSE)

#define GET_DP_TX_HDCP2_STOP_CONTENT_STREAM()                (g_stDpTxHdcp2AuthInfo.b1StopContentStream)
#define SET_DP_TX_HDCP2_STOP_CONTENT_STREAM()                (g_stDpTxHdcp2AuthInfo.b1StopContentStream = _TRUE)
#define CLR_DP_TX_HDCP2_STOP_CONTENT_STREAM()                (g_stDpTxHdcp2AuthInfo.b1StopContentStream = _FALSE)

#define GET_DP_TX_HDCP2_BACKUP_CONTENT_STREAM()              (g_stDpTxHdcp2AuthInfo.b1BackupContentStream)
#define SET_DP_TX_HDCP2_BACKUP_CONTENT_STREAM()              (g_stDpTxHdcp2AuthInfo.b1BackupContentStream = _TRUE)
#define CLR_DP_TX_HDCP2_BACKUP_CONTENT_STREAM()              (g_stDpTxHdcp2AuthInfo.b1BackupContentStream = _FALSE)

#define GET_DP_TX_HDCP2_PAIRING_INFO_READY()                 (g_stDpTxHdcp2AuthInfo.b1PairingInfoReady)
#define SET_DP_TX_HDCP2_PAIRING_INFO_READY()                 (g_stDpTxHdcp2AuthInfo.b1PairingInfoReady = _TRUE)
#define CLR_DP_TX_HDCP2_PAIRING_INFO_READY()                 (g_stDpTxHdcp2AuthInfo.b1PairingInfoReady = _FALSE)

#define GET_DP_TX_HDCP2_PAIRING_INFO_TIMEOUT()               (g_stDpTxHdcp2AuthInfo.b1PairingInfoTimeout)
#define SET_DP_TX_HDCP2_PAIRING_INFO_TIMEOUT()               (g_stDpTxHdcp2AuthInfo.b1PairingInfoTimeout = _TRUE)
#define CLR_DP_TX_HDCP2_PAIRING_INFO_TIMEOUT()               (g_stDpTxHdcp2AuthInfo.b1PairingInfoTimeout = _FALSE)

#define GET_DP_TX_HDCP2_DOWNSTREAM_PLUG_CHANGE()             (g_stDpTxHdcp2AuthInfo.b1DownstreamPlugChange)
#define SET_DP_TX_HDCP2_DOWNSTREAM_PLUG_CHANGE()             (g_stDpTxHdcp2AuthInfo.b1DownstreamPlugChange = _TRUE)
#define CLR_DP_TX_HDCP2_DOWNSTREAM_PLUG_CHANGE()             (g_stDpTxHdcp2AuthInfo.b1DownstreamPlugChange = _FALSE)

#define GET_DP_TX_HDCP2_MODE()                               (ScalerGetBit(PBB_90_HDCP22_CTRL, _BIT0) == _BIT0)

#if((_D0_DP_EXIST == _ON) && (_D1_DP_EXIST == _ON))
#define GET_DP_TX_HDCP2_RX_STX_TYPE(x)                       ((bit)ScalerGetBit(((GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT) ? PB_95_HDCP_ST_TYPE : PB0_95_HDCP_ST_TYPE), (_BIT7 >> (x))))
#define GET_DP_TX_HDCP2_DPCD_INFO(x, y, z)                   ((GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT) ? ScalerDpRx0GetDpcdInfo((x), (y), (z)) : ScalerDpRx1GetDpcdInfo((x), (y), (z)))
#elif(_D0_DP_EXIST == _ON)
#define GET_DP_TX_HDCP2_RX_STX_TYPE(x)                       ((bit)ScalerGetBit(PB_95_HDCP_ST_TYPE, (_BIT7 >> (x))))
#define GET_DP_TX_HDCP2_DPCD_INFO(x, y, z)                   (ScalerDpRx0GetDpcdInfo((x), (y), (z)))
#elif(_D1_DP_EXIST == _ON)
#define GET_DP_TX_HDCP2_RX_STX_TYPE(x)                       ((bit)ScalerGetBit(PB0_95_HDCP_ST_TYPE, (_BIT7 >> (x))))
#define GET_DP_TX_HDCP2_DPCD_INFO(x, y, z)                   (ScalerDpRx1GetDpcdInfo((x), (y), (z)))
#endif

#define GET_DP_TX_HDCP2_LOAD_KEY_EN()                        (bit)(g_ucDpTxHdcp2LoadKey & _BIT7)
#define SET_DP_TX_HDCP2_LOAD_KEY_EN()                        (g_ucDpTxHdcp2LoadKey |= _BIT7)
#define CLR_DP_TX_HDCP2_LOAD_KEY_EN()                        (g_ucDpTxHdcp2LoadKey &= ~_BIT7)

#define GET_DP_TX_HDCP2_LOAD_KEY_FINISH()                    (bit)(g_ucDpTxHdcp2LoadKey & _BIT6)
#define SET_DP_TX_HDCP2_LOAD_KEY_FINISH()                    (g_ucDpTxHdcp2LoadKey |= _BIT6)
#define CLR_DP_TX_HDCP2_LOAD_KEY_FINISH()                    (g_ucDpTxHdcp2LoadKey &= ~_BIT6)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDCP 2.2 Tx Authentication State
//--------------------------------------------------
typedef enum
{
    _HDCP_2_2_TX_STATE_IDLE = 0,
    _HDCP_2_2_TX_STATE_AKE_INIT,
    _HDCP_2_2_TX_STATE_VERIFY_SIGNATURE,
    _HDCP_2_2_TX_STATE_NO_STORED_KM,
    _HDCP_2_2_TX_STATE_STORED_KM,
    _HDCP_2_2_TX_STATE_VERIFY_H_PRIME,
    _HDCP_2_2_TX_STATE_PAIRING,
    _HDCP_2_2_TX_STATE_LOCALITY_CHECK,
    _HDCP_2_2_TX_STATE_SKE,
    _HDCP_2_2_TX_STATE_VERIFY_V_PRIME,
    _HDCP_2_2_TX_STATE_AUTHEN_DONE,
} EnumHdcp2TxAuthState;

//--------------------------------------------------
// Definitions of HDCP2 Tx CPIRQ Type
//--------------------------------------------------
typedef enum
{
    _HDCP_2_2_TX_CPIRQ_NONE = 0,
    _HDCP_2_2_TX_CPIRQ_V_READY = _BIT0,
    _HDCP_2_2_TX_CPIRQ_H_PRIME_AVAILABLE = _BIT1,
    _HDCP_2_2_TX_CPIRQ_PAIRING_AVAILABLE = _BIT2,
    _HDCP_2_2_TX_CPIRQ_REAUTH_REQUEST = _BIT3,
    _HDCP_2_2_TX_CPIRQ_LINK_INTEGRITY_FAIL = _BIT4,
} EnumHdcp2TxCpirqType;

//--------------------------------------------------
//HDCP RX Authentication Downstream Event
//--------------------------------------------------
typedef enum
{
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_NONE = 0,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_LINK_INTEGRITY_FAIL,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_REAUTH,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_MSG_QUERY_REAUTH,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PLUG_CHANGED,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PASS,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_EXCEED,
} EnumDpTxHdcp2DownstreamAuthEvent;

//--------------------------------------------------
// Struct for RX HDCP Authentication
//--------------------------------------------------
typedef struct
{
    BYTE b4AuthState : 4;
    BYTE b1AuthStateChange : 1;
    BYTE b1Hdcp2Version : 1;
    BYTE b1Hdcp2Capable : 1;
    BYTE b1Hdcp2Repeater : 1;
    BYTE b1AuthStart : 1;
    BYTE b1CertificateTimeout : 1;
    BYTE b1HprimeTimeout : 1;
    BYTE b1AuthHold : 1;
    BYTE b1EncryptDataTimeout : 1;
    BYTE b1VReadyTimeout : 1;
    BYTE b1PollingVReady : 1;
    BYTE b1VReadyBit : 1;
    WORD usLcRetryCounter;
    BYTE b5RxInfoDevice : 5;
    BYTE b3RxInfoDepth : 3;
    BYTE ucAuthDownstreamEvent;
    BYTE b1RxInfoDeviceExceed : 1;
    BYTE b1RxInfoDepthExceed : 1;
    BYTE b1Hdcp20RepeaterDownstream : 1;
    BYTE b1Hdcp1DeviceDownstream : 1;
    BYTE b1AuthContentStreamManage : 1;
    BYTE b1MprimeTimeout : 1;
    BYTE b1StopContentStream : 1;
    BYTE b1BackupContentStream : 1;
    BYTE b1PairingInfoReady : 1;
    BYTE b1PairingInfoTimeout : 1;
    BYTE b1DownstreamPlugChange : 1;
} StructHdcp2TxAuthInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructHdcp2TxAuthInfo g_stDpTxHdcp2AuthInfo;
extern EnumHdcp2TxCpirqType g_enumDpTxHdcp2CpirqType;
extern BYTE g_pucDpTxHdcp2ReceiverId[5];
extern BYTE g_pucDpTxHdcp2ReceiverIdList[155];

extern BYTE g_ucDpTxHdcp2LoadKey;
extern BYTE g_pucDpTxHdcp2dKey0[16];
extern BYTE g_pucDpTxHdcp2dKey1[16];
extern BYTE g_pucDpTxHdcp2DownStreamV[20];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpTxHdcp2Handler(void);
extern void ScalerDpTxHdcp2Initial(void);
extern void ScalerDpTxHdcp2CheckCapability(void);
extern void ScalerDpTxHdcp2TimeoutToReadCertificateEvent(void);
extern void ScalerDpTxHdcp2TimeoutToReadHPrimeEvent(void);
extern void ScalerDpTxHdcp2TimeoutToReadPairingInfoEvent(void);
extern void ScalerDpTxHdcp2TimeoutToEncyptDataEvent(void);
extern void ScalerDpTxHdcp2TimeoutForVReadyEvent(void);
extern void ScalerDpTxHdcp2PollingVReadyEvent(void);
extern void ScalerDpTxHdcp2TimeoutToReadMPrimeEvent(void);
extern void ScalerDpTxHdcp2OutputContentStreamHandler(void);
extern void ScalerDpTxHdcp2EncryptSignalProc(bit bEnable);
#endif // End of #if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

