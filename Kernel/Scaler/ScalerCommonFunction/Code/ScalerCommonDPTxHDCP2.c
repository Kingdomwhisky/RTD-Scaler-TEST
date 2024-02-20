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
// ID Code      : ScalerCommonDPTxHDCP2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerCommonFunctionInclude.h"

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DP_TX_HDCP2_LC_RETRY_MAX_NUMBER                    1024

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructHdcp2TxAuthInfo g_stDpTxHdcp2AuthInfo;
EnumHdcp2TxCpirqType g_enumDpTxHdcp2CpirqType = _HDCP_2_2_TX_CPIRQ_NONE;
DWORD g_ulDpTxHdcp2SeqNumM;
DWORD g_ulDpTxHdcp2SeqNumV;

BYTE g_pucDpTxHdcp2TxCaps[3];
BYTE g_pucDpTxHdcp2ReceiverId[5];
BYTE g_pucDpTxHdcp2RxCaps[3];
BYTE g_pucDpTxHdcp2Rrx[8];
BYTE g_pucDpTxHdcp2Npub[128];
BYTE g_pucDpTxHdcp2Epub[3];
BYTE g_pucDpTxHdcp2dKey0[16];
BYTE g_pucDpTxHdcp2dKey1[16];
BYTE g_pucDpTxHdcp2ReceiverIdList[155];
BYTE g_pucDpTxHdcp2M[32];
BYTE g_pucDpTxHdcp2PairingEkhkm[16];
BYTE g_pucDpTxHdcp2PairingM[16];
BYTE g_pucDpTxHdcp2PairingKm[16];
BYTE g_pucDpTxHdcp2PairingReceiverID[5];
BYTE g_pucDpTxHdcp2H[32];
BYTE g_pucDpTxHdcp2DownStreamV[20];

BYTE g_ucDpTxHdcp2LoadKey;

#if(_DP_MST_SUPPORT == _ON)
BYTE g_pucDpTxHdcp2MstTimeSlotBackup[6];
#endif

#if(_HDCP_2_2_TX_ERRATA_TEST_SUPPORT == _ON)
BYTE g_pucDpTxHdcp2Rtx[8] =
{
    0x18, 0xfa, 0xe4, 0x20, 0x6a, 0xfb, 0x51, 0x49,
};
BYTE g_pucDpTxHdcp2Km[16] =
{
    0x68, 0xbc, 0xc5, 0x1b, 0xa9, 0xdb, 0x1b, 0xd0,
    0xfa, 0xf1, 0x5e, 0x9a, 0xd8, 0xa5, 0xaf, 0xb9,
};
BYTE g_pucDpTxHdcp2Rn[8] =
{
    0x32, 0x75, 0x3e, 0xa8, 0x78, 0xa6, 0x38, 0x1c,
};
#else
BYTE g_pucDpTxHdcp2Rtx[8];
BYTE g_pucDpTxHdcp2Km[16];
BYTE g_pucDpTxHdcp2Rn[8];
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpTxHdcp2Handler(void);
void ScalerDpTxHdcp2ResetAuthInfo(void);
void ScalerDpTxHdcp2ChangeAuthState(EnumHdcp2TxAuthState enumHdcp2AuthState);
EnumHdcp2TxCpirqType ScalerDpTxHdcp2PollingCpIrqType(void);
void ScalerDpTxHdcp2Initial(void);
void ScalerDpTxHdcp2CheckCapability(void);
bit ScalerDpTxHdcp2AkeInitial(void);
bit ScalerDpTxHdcp2RandomGenerate(void);
void ScalerDpTxHdcp2TimeoutToReadCertificateEvent(void);
void ScalerDpTxHdcp2DcpLlcRsaInit(void);
void ScalerDpTxHdcp2LoadKeyProc(BYTE ucLoadKeyType, BYTE *pucDpTxHdcp2Key);
bit ScalerDpTxHdcp2DcpLlcRsaCalculate(void);
bit ScalerDpTxHdcp2VerifySignature(void);
bit ScalerDpTxHdcp2RsaCalculate(BYTE *pucEmKmArray, BYTE *pucRrmodn);
bit ScalerDpTxHdcp2NoStoredKmProc(void);
bit ScalerDpTxHdcp2RrmodnCalculate(BYTE *pucPubN);
WORD ScalerDpTxHdcp2GetNShiftCounter(BYTE *pucPubN);
DWORD ScalerDpTxHdcp2NpinvCalculate(DWORD ulA);
bit ScalerDpTxHdcp2StoredKmProc(void);
void ScalerDpTxHdcp2TimeoutToReadHPrimeEvent(void);
bit ScalerDpTxHdcp2ComputeH(BYTE *pucDpTxHdcp2Rtx, BYTE *pucDpTxHdcp2Rrx, BYTE *pucDpTxHdcp2Km);
bit ScalerDpTxHdcp2VerifyHprime(void);
bit ScalerDpTxHdcp2StorePairingInfo(void);
void ScalerDpTxHdcp2ClearPairingInfo(void);
bit ScalerDpTxHdcp2CheckPairingInfo(void);
void ScalerDpTxHdcp2TimeoutToReadPairingInfoEvent(void);
bit ScalerDpTxHdcp2LocalityCheck(void);
bit ScalerDpTxHdcp2SessionKeyExchangeProc(void);
void ScalerDpTxHdcp2TimeoutToEncyptDataEvent(void);
void ScalerDpTxHdcp2TimeoutForVReadyEvent(void);
void ScalerDpTxHdcp2PollingVReadyEvent(void);
bit ScalerDpTxHdcp2ChecRxInfo(void);
bit ScalerDpTxHdcp2VerifyVprime(void);
bit ScalerDpTxHdcp2ContentStreamManagement(void);
void ScalerDpTxHdcp2TimeoutToReadMPrimeEvent(void);
bit ScalerDpTxHdcp2VerifyMprime(void);
void ScalerDpTxHdcp2ContentStreamManagementHandler(void);
void ScalerDpTxHdcp2OutputContentStreamHandler(void);
void ScalerDpTxHdcp2EncryptSignalProc(bit bEnable);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process for Dp Tx
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2Handler(void)
{
    CLR_DP_TX_HDCP2_DOWNSTREAM_EVENT();

    if(ScalerSyncDpHdcp2GetUpstreamEvent() == _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_TIMEOUT)
    {
        CLR_DP_TX_HDCP2_AUTH_START();

        ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
    }
    else if(ScalerSyncDpHdcp2GetUpstreamEvent() == _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE)
    {
        SET_DP_TX_HDCP2_AUTH_START();

        ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
    }
    else if(ScalerSyncDpHdcp2GetUpstreamEvent() == _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION)
    {
        CLR_DP_TX_HDCP2_AUTH_START();

        ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
    }
    else if(GET_DP_TX_HDCP2_IRQ_TYPE(_HDCP_2_2_TX_CPIRQ_LINK_INTEGRITY_FAIL) == _HDCP_2_2_TX_CPIRQ_LINK_INTEGRITY_FAIL)
    {
        CLR_DP_TX_HDCP2_IRQ_TARGET_TYPE(_HDCP_2_2_TX_CPIRQ_LINK_INTEGRITY_FAIL);

        if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _TRUE)
        {
            DebugMessageHDCP2("DPTX HDCP2 - CPIRQ LVP Fail", 0);

            ScalerDpTxHdcp2EncryptSignalProc(_DISABLE);

            SET_DP_TX_HDCP2_AUTH_START();

            ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
        }
    }
    else if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON)
    {
        if(GET_DP_TX_HDCP2_AUTH_STATE() != _HDCP_2_2_TX_STATE_IDLE)
        {
            ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
        }
    }
    else if(GET_DP_TX_HDCP2_IRQ_TYPE(_HDCP_2_2_TX_CPIRQ_V_READY) == _HDCP_2_2_TX_CPIRQ_V_READY)
    {
        if(GET_DP_TX_HDCP2_AUTH_STATE() == _HDCP_2_2_TX_STATE_AUTHEN_DONE)
        {
            ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_VERIFY_V_PRIME);
        }
    }

    switch(GET_DP_TX_HDCP2_AUTH_STATE())
    {
        case _HDCP_2_2_TX_STATE_IDLE:

            if(GET_DP_TX_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - Idle", 0);

                ScalerDpTxHdcp2ResetAuthInfo();

                ScalerDpTxHdcp2EncryptSignalProc(_DISABLE);

                ScalerDpTxHdcp2CheckCapability();
            }

            if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) &&
               (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE) &&
               (GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_ON) &&
               (GET_DP_TX_HDCP2_AUTH_START() == _TRUE))
            {
                CLR_DP_TX_HDCP2_AUTH_START();
                CLR_DP_TX_HDCP2_IRQ_TYPE();

                ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_AKE_INIT);
            }

            break;

        case _HDCP_2_2_TX_STATE_AKE_INIT:

            if(GET_DP_TX_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - AKE INIT", 0);

                CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE();
            }

            if(ScalerDpTxHdcp2AkeInitial() == _TRUE)
            {
                ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_VERIFY_SIGNATURE);
            }
            else
            {
                SET_DP_TX_HDCP2_AUTH_START();

                ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_VERIFY_SIGNATURE:

            if(GET_DP_TX_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - Verify S", 0);

                CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE();

                // Set up 100ms Timer Event
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_CERTIFICATE);

                SET_DP_TX_HDCP2_AUTH_HOLD();
            }

            if(GET_DP_TX_HDCP2_CERTIFICATE_TIMEOUT() == _TRUE)
            {
                CLR_DP_TX_HDCP2_CERTIFICATE_TIMEOUT();

                CLR_DP_TX_HDCP2_AUTH_HOLD();

                SET_DP_TX_HDCP2_LOAD_KEY_EN();
            }
            else if(GET_DP_TX_HDCP2_LOAD_KEY_FINISH() == _TRUE)
            {
                CLR_DP_TX_HDCP2_LOAD_KEY_FINISH();

                if(ScalerDpTxHdcp2VerifySignature() == _TRUE)
                {
                    DebugMessageHDCP2("DPTX HDCP2 - S_Verify Pass", 0);

                    // Go to No stored km or Stored km
                    if(ScalerDpTxHdcp2CheckPairingInfo() == _TRUE)
                    {
                        ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_STORED_KM);
                    }
                    else
                    {
                        ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_NO_STORED_KM);
                    }
                }
                else
                {
                    DebugMessageHDCP2("DPTX HDCP2 - S_Verify Fail", 0);

                    // DP HDCP2.2 CTS 3A-03(Same as 1A-08)
                    SET_DP_TX_HDCP2_AUTH_START();

                    ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                }
            }

            break;

        case _HDCP_2_2_TX_STATE_NO_STORED_KM:

            if(GET_DP_TX_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - No Stored Km", 0);

                CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE();
            }

            if(ScalerDpTxHdcp2NoStoredKmProc() == _TRUE)
            {
                ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_VERIFY_H_PRIME);

                // Set up 1s Timer Event
                ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_H_PRIME);
            }
            else
            {
                SET_DP_TX_HDCP2_AUTH_START();

                ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_STORED_KM:

            if(GET_DP_TX_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - Stored Km", 0);

                CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE();
            }

            if(ScalerDpTxHdcp2StoredKmProc() == _TRUE)
            {
                ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_VERIFY_H_PRIME);

                // Set up 200ms Timer Event
                ScalerTimerActiveTimerEvent(SEC(0.2), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_H_PRIME);
            }
            else
            {
                SET_DP_TX_HDCP2_AUTH_START();

                ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_VERIFY_H_PRIME:

            if(GET_DP_TX_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - H", 0);

                CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE();

                if(GET_DP_TX_HDCP2_PAIRING_INFO_READY() == _TRUE)
                {
                    // Compute H for Stored Km Flow
                    ScalerDpTxHdcp2ComputeH(g_pucDpTxHdcp2Rtx, g_pucDpTxHdcp2Rrx, g_pucDpTxHdcp2PairingKm);
                }
                else
                {
                    // Compute H for No Stored Km Flow
                    ScalerDpTxHdcp2ComputeH(g_pucDpTxHdcp2Rtx, g_pucDpTxHdcp2Rrx, g_pucDpTxHdcp2Km);
                }
            }

            if((GET_DP_TX_HDCP2_IRQ_TYPE(_HDCP_2_2_TX_CPIRQ_H_PRIME_AVAILABLE) == _HDCP_2_2_TX_CPIRQ_H_PRIME_AVAILABLE) ||
               (GET_DP_TX_HDCP2_H_PRIME_TIMEOUT() == _TRUE))
            {
                CLR_DP_TX_HDCP2_IRQ_TARGET_TYPE(_HDCP_2_2_TX_CPIRQ_H_PRIME_AVAILABLE);

                if(ScalerDpTxHdcp2VerifyHprime() == _TRUE)
                {
                    if(GET_DP_TX_HDCP2_PAIRING_INFO_READY() == _TRUE)
                    {
                        ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_LOCALITY_CHECK);
                    }
                    else
                    {
                        ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_PAIRING);

                        // Set up 200ms Timer Event
                        ScalerTimerActiveTimerEvent(SEC(0.2), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_PAIRING_INFO);
                    }
                }
                else
                {
                    // DP HDCP2.2 CTS 3A-04(Same as 1A-10)
                    SET_DP_TX_HDCP2_AUTH_START();

                    ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                }
            }

            break;

        case _HDCP_2_2_TX_STATE_PAIRING:

            if(GET_DP_TX_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - Pairing", 0);

                CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE();
            }

            if(GET_DP_TX_HDCP2_IRQ_TYPE(_HDCP_2_2_TX_CPIRQ_PAIRING_AVAILABLE) == _HDCP_2_2_TX_CPIRQ_PAIRING_AVAILABLE)
            {
                CLR_DP_TX_HDCP2_IRQ_TARGET_TYPE(_HDCP_2_2_TX_CPIRQ_PAIRING_AVAILABLE);

                if(ScalerDpTxHdcp2StorePairingInfo() == _TRUE)
                {
                    ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_LOCALITY_CHECK);
                }
                else
                {
                    // DP HDCP2.2 CTS 3A-05(Same as 1A-11)
                    SET_DP_TX_HDCP2_AUTH_START();

                    ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                }
            }
            else if(GET_DP_TX_HDCP2_PAIRING_INFO_TIMEOUT() == _TRUE)
            {
                // DP HDCP2.2 CTS 3A-05(Same as 1A-11)
                SET_DP_TX_HDCP2_AUTH_START();

                ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_LOCALITY_CHECK:

            if(GET_DP_TX_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - LC", 0);

                CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE();
            }

            if(GET_DP_TX_HDCP2_LC_RETRY_COUNTER() < _DP_TX_HDCP2_LC_RETRY_MAX_NUMBER)
            {
                if(ScalerDpTxHdcp2LocalityCheck() == _TRUE)
                {
                    ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_SKE);
                }
                else
                {
                    ADD_DP_TX_HDCP2_LC_RETRY_COUNTER();
                }
            }
            else
            {
                // DP HDCP2.2 CTS 3A-06(Same as 1A-12)
                SET_DP_TX_HDCP2_AUTH_START();

                ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_SKE:

            if(GET_DP_TX_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - SKE", 0);

                CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE();
            }

            if(ScalerDpTxHdcp2SessionKeyExchangeProc() == _TRUE)
            {
                if(GET_DP_TX_HDCP2_REPEATER_SUPPORTED() == _TRUE)
                {
                    ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_VERIFY_V_PRIME);
                }
                else
                {
                    ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_AUTHEN_DONE);

                    SET_DP_TX_HDCP2_DOWNSTREAM_EVENT(_DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PASS);
                }
            }
            else
            {
                SET_DP_TX_HDCP2_AUTH_START();

                ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_VERIFY_V_PRIME:

            if(GET_DP_TX_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - V", 0);

                CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE();

                ScalerTimerActiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_FOR_V_READY);
                ScalerTimerActiveTimerEvent(SEC(0.25), _SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY);
            }

            if(GET_DP_TX_HDCP2_POLLING_V_READY() == _TRUE)
            {
                CLR_DP_TX_HDCP2_POLLING_V_READY();
                CLR_DP_TX_HDCP2_V_READY_BIT();

                if(ScalerDpTxHdcp2PollingCpIrqType() == _HDCP_2_2_TX_CPIRQ_V_READY)
                {
                    SET_DP_TX_HDCP2_V_READY_BIT();
                }
                else
                {
                    ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY);
                }
            }

            if((GET_DP_TX_HDCP2_IRQ_TYPE(_HDCP_2_2_TX_CPIRQ_V_READY) == _HDCP_2_2_TX_CPIRQ_V_READY) ||
               (GET_DP_TX_HDCP2_V_READY_BIT() == _TRUE))
            {
                CLR_DP_TX_HDCP2_IRQ_TARGET_TYPE(_HDCP_2_2_TX_CPIRQ_V_READY);
                CLR_DP_TX_HDCP2_V_READY_BIT();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_FOR_V_READY);

                if(ScalerDpTxHdcp2ChecRxInfo() == _TRUE)
                {
                    if(ScalerDpTxHdcp2VerifyVprime() == _TRUE)
                    {
                        ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_AUTHEN_DONE);

                        SET_DP_TX_HDCP2_DOWNSTREAM_EVENT(_DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PASS);
                    }
                    else
                    {
                        // DP HDCP2.2 CTS 3B-03(Same as 1B-03)
                        SET_DP_TX_HDCP2_AUTH_START();

                        ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                    }
                }
                else
                {
                    // DP HDCP2.2 CTS 3B-04/05(Same as 1B-04/05)
                    SET_DP_TX_HDCP2_AUTH_START();

                    // DP HDCP2.2 CTS 3C-18
                    SET_DP_TX_HDCP2_DOWNSTREAM_EVENT(_DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_EXCEED);

                    ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                }
            }

            if(GET_DP_TX_HDCP2_V_READY_TIMEOUT() == _TRUE)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY);

                // DP HDCP2.2 CTS 3B-02(Same as 1B-02)
                SET_DP_TX_HDCP2_AUTH_START();

                ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_AUTHEN_DONE:

            if(GET_DP_TX_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - Done", 0);

                CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE();
            }

            break;

        default:

            break;
    }

    if((GET_DP_TX_HDCP2_AUTH_STATE() == _HDCP_2_2_TX_STATE_AUTHEN_DONE) ||
       (GET_DP_TX_HDCP_AUTH_STATE() == _DP_TX_HDCP_STATE_AUTH_PASS))
    {
        ScalerDpTxHdcp2ContentStreamManagementHandler();
    }

    if(ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE)
    {
        if((GET_DP_TX_HDCP2_AUTH_STATE() > _HDCP_2_2_TX_STATE_SKE) &&
           (GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE) &&
           (GET_DP_TX_HDCP2_ENCRYPT_DATA_TIMEOUT() == _TRUE))
        {
            if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _FALSE)
            {
                ScalerDpTxHdcp2EncryptSignalProc(_ENABLE);

                DebugMessageHDCP2("DPTX HDCP2 - Encrypt", 0);
            }
        }
    }
    else
    {
        if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _TRUE)
        {
            ScalerDpTxHdcp2EncryptSignalProc(_DISABLE);

            DebugMessageHDCP2("DPTX HDCP2 - Disable Encrypt", 0);
        }
    }
}

//--------------------------------------------------
// Description  : Clear HDCP2 Auth Flag and Timer Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2ResetAuthInfo(void)
{
    CLR_DP_TX_HDCP2_AUTH_STATE_CHANGE();
    CLR_DP_TX_HDCP2_CERTIFICATE_TIMEOUT();
    CLR_DP_TX_HDCP2_H_PRIME_TIMEOUT();
    CLR_DP_TX_HDCP2_PAIRING_INFO_TIMEOUT();
    CLR_DP_TX_HDCP2_AUTH_HOLD();
    CLR_DP_TX_HDCP2_LC_RETRY_COUNTER();
    CLR_DP_TX_HDCP2_ENCRYPT_DATA_TIMEOUT();
    CLR_DP_TX_HDCP2_V_READY_TIMEOUT();
    CLR_DP_TX_HDCP2_POLLING_V_READY();
    CLR_DP_TX_HDCP2_V_READY_BIT();
    CLR_DP_TX_HDCP2_SEQUENCE_NUMBER_M();
    CLR_DP_TX_HDCP2_M_PRIME_TIMEOUT();
    CLR_DP_TX_HDCP2_STOP_CONTENT_STREAM();
    CLR_DP_TX_HDCP2_CONTENT_STREAM_MANAGEMENT();
    CLR_DP_TX_HDCP2_SEQUENCE_NUMBER_V();

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_CERTIFICATE);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_H_PRIME);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_PAIRING_INFO);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_ENCRYPT_DATA);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_FOR_V_READY);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_M_PRIME);
}

//--------------------------------------------------
// Description  : Change HDCP2 Auth State
// Input Value  : Target HDCP2 Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2ChangeAuthState(EnumHdcp2TxAuthState enumHdcp2AuthState)
{
    SET_DP_TX_HDCP2_AUTH_STATE(enumHdcp2AuthState);
    SET_DP_TX_HDCP2_AUTH_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Polling IRQ status of Downstream
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumHdcp2TxCpirqType ScalerDpTxHdcp2PollingCpIrqType(void)
{
    if(ScalerDpTxAuxNativeRead(0x06, 0x94, 0x93, 1, pData) == _FALSE)
    {
        return _HDCP_2_2_TX_CPIRQ_NONE;
    }

    if((pData[0] & _BIT4) == _BIT4)
    {
        return _HDCP_2_2_TX_CPIRQ_LINK_INTEGRITY_FAIL;
    }
    else if((pData[0] & _BIT3) == _BIT3)
    {
        return _HDCP_2_2_TX_CPIRQ_REAUTH_REQUEST;
    }
    else if((pData[0] & _BIT2) == _BIT2)
    {
        return _HDCP_2_2_TX_CPIRQ_PAIRING_AVAILABLE;
    }
    else if((pData[0] & _BIT1) == _BIT1)
    {
        return _HDCP_2_2_TX_CPIRQ_H_PRIME_AVAILABLE;
    }
    else if((pData[0] & _BIT0) == _BIT0)
    {
        return _HDCP_2_2_TX_CPIRQ_V_READY;
    }

    return _HDCP_2_2_TX_CPIRQ_NONE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2Initial(void)
{
    // The HDCP Tx must set VERSION(0x6900A) to 0x02
    g_pucDpTxHdcp2TxCaps[0] = 0x02;
    g_pucDpTxHdcp2TxCaps[1] = 0x00;
    g_pucDpTxHdcp2TxCaps[2] = 0x00;
}

//--------------------------------------------------
// Description  : Authentication Key Exchange Initial(AKE_init)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2CheckCapability(void)
{
    CLR_DP_TX_HDCP2_CAPABLE_SUPPORTED();
    CLR_DP_TX_HDCP2_REPEATER_SUPPORTED();
    CLR_DP_TX_HDCP2_VERSION_SUPPORTED();
    CLR_DP_TX_HDCP2_RXINFO_HDCP20_REPEATER_DOWNSTREAM();

    if(GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_UNPLUG)
    {
        // Disable HDCP 2.2 function
        ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT0, 0x00);

        return;
    }

    // Check if Receiver support HDCP capable and version
    if(ScalerDpTxAuxNativeRead(0x06, 0x92, 0x1D, 3, pData) == _TRUE)
    {
        // Check HDCP Version
        if(((pData[0] == 0x02) || (pData[0] == 0x03) || (pData[0] == 0x04)) &&
           (pData[1] == 0x00) &&
           ((pData[2] & ~(_BIT1 | _BIT0)) == 0x00))
        {
            SET_DP_TX_HDCP2_VERSION_SUPPORTED();
        }

        // Check HDCP Capable
        if((pData[2] & _BIT1) == _BIT1)
        {
            SET_DP_TX_HDCP2_CAPABLE_SUPPORTED();
        }

        // Check HDCP Repeater
        if((pData[2] & _BIT0) == _BIT0)
        {
            SET_DP_TX_HDCP2_REPEATER_SUPPORTED();

            // Check  HDCP2.0 Repeater Downstream in the topology
            if(pData[0] < 0x02)
            {
                SET_DP_TX_HDCP2_RXINFO_HDCP20_REPEATER_DOWNSTREAM();
            }
        }

        if((GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE))
        {
            // Enable HDCP 2.2 function
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT0, _BIT0);
        }
        else
        {
            // Disable HDCP 2.2 function
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT0, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Authentication Key Exchange Initial(AKE_init)
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2AkeInitial(void)
{
    // Enable DP TX HDCP function
    ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT0, _BIT0);

    // Disable AES-Ctrl Cipher
    ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT1, 0x00);

#if(_HDCP_2_2_TX_ERRATA_TEST_SUPPORT == _OFF)
    // Generate Rtx
    if(ScalerDpTxHdcp2RandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    // Load Rtx
    for(pData[0] = 0; pData[0] < 8; pData[0]++)
    {
        g_pucDpTxHdcp2Rtx[pData[0]] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - pData[0]);
        PDATA_WORD(1) += g_pucDpTxHdcp2Rtx[pData[0]];
    }

    // Disable AES Random Gen
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }
#endif

    // Write Rtx to the DPCD Table of Downstream Device
    if(ScalerDpTxAuxNativeWrite(0x06, 0x90, 0x00, 8, g_pucDpTxHdcp2Rtx) == _FALSE)
    {
        return _FALSE;
    }

    // Write TxCaps to the DPCD Table of Downstream Device
    if(ScalerDpTxAuxNativeWrite(0x06, 0x90, 0x08, 3, g_pucDpTxHdcp2TxCaps) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : AES Random Pattern Generator
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2RandomGenerate(void)
{
    // Enable AES Random Gen
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), (_BIT5));

    // AES Trigger
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

    for(pData[0] = 0; pData[0] < (TL2 >> 2); pData[0]++)
    {
        DELAY_5US();
    }

    // Wait Finish for AES Random Gen
    pData[1] = 0x0A;

    do
    {
        DELAY_5US();
    }
    while((ScalerGetBit(P63_60_HDCP_AES_CTRL, _BIT6) == _BIT6) && ((--pData[1]) != 0));

    if(ScalerGetBit(P63_60_HDCP_AES_CTRL, _BIT5) == 0x00)
    {
        return _FALSE;
    }

    // Disable AES Random Gen
    // ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Timeout to Read Certificate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2TimeoutToReadCertificateEvent(void)
{
    SET_DP_TX_HDCP2_CERTIFICATE_TIMEOUT();
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Circuit Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2DcpLlcRsaInit(void)
{
    // Enable HDCP 2.2 RSA Module
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));

    // RSA Clock Select
    ScalerSetBit(P63_92_HDCP_DUMMY1, ~_BIT7, _BIT7);

    // Reset HDCP 2.2 RSA module
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, 0x00);
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

    // Select RSA Key Download Data Length
    ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), 0x00);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Load Key Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2LoadKeyProc(BYTE ucLoadKeyType, BYTE *pucDpTxHdcp2Key)
{
    switch(ucLoadKeyType)
    {
        case _DP_TX_HDCP2_KEY_SIGNATURE:

            for(pData[0] = 0; pData[0] < 48; pData[0]++)
            {
                ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

                // Enable write cipher text to RSA Module
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (47 - pData[0]));

                memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucDpTxHdcp2Key[pData[0] << 3], 8);

                /*
                for(pData[1] = 0; pData[1] < 8; pData[1]++)
                {
                    DebugMessageHDCP2("S'", pucSignature[(pData[0] << 3) + pData[1]]);
                }
                */
            }

            break;

        case _DP_TX_HDCP2_KEY_RRMODN:

            for(pData[0] = 0; pData[0] < 48; pData[0]++)
            {
                ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

                // Load RRmodN
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (47 - pData[0])));

                memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucDpTxHdcp2Key[pData[0] << 3], 8);
            }

            break;

        case _DP_TX_HDCP2_KEY_DCP_LLC_N:

            for(pData[0] = 0; pData[0] < 48; pData[0]++)
            {
                ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

                // Load DCP LLC Public N Key
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + (47 - pData[0])));

                memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucDpTxHdcp2Key[pData[0] << 3], 8);
            }

            break;

        case _DP_TX_HDCP2_KEY_EKEY1:

            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

                // Load e Key(0x00)
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (47 - pData[0])));

                for(pData[1] = 0; pData[1] < 8; pData[1]++)
                {
                    ScalerSetByte((P63_17_HDCP_RSA_DATA_IN_DATA7 + pData[1]), 0x00);
                }
            }

            break;

        case _DP_TX_HDCP2_KEY_EKEY2:

            for(pData[0] = 32; pData[0] < 48; pData[0]++)
            {
                ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

                // Load e Key
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (47 - pData[0])));
                memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucDpTxHdcp2Key[(pData[0] - 32) << 3], 8);
            }

            break;

        case _DP_TX_HDCP2_KEY_NPINV:

            memcpy((volatile BYTE xdata *)P63_12_HDCP_RSA_NP_INV_3, pucDpTxHdcp2Key, 4);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Start RSA Calculate
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2DcpLlcRsaCalculate(void)
{
    // Set RSA Write key done
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

    // Enable RSA Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT4, 0x00);

    // Polling 100ms for RSA Module Done
    if(ScalerTimerPollingFlagProc(100, P63_10_HDCP_RSA_CTRL0, _BIT2, _SUCCESS) == _TRUE)
    {
        // Disable RSA Module
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT7, 0x00);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signature Verification
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2VerifySignature(void)
{
    BYTE ucI = 0;
    WORD usDpcdAddress = 0;
    BYTE pucSha256Input[64];
    BYTE pucDpTxHdcp2CertificatePart1[138];
    BYTE pucDpTxHdcp2Signature[384];
    BYTE pucDigestInfo[20] =
    {
        0x00, 0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48,
        0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00, 0x04, 0x20
    };

    memset(pucSha256Input, 0, sizeof(pucSha256Input));
    memset(pucDpTxHdcp2CertificatePart1, 0, sizeof(pucDpTxHdcp2CertificatePart1));
    memset(pucDpTxHdcp2Signature, 0, sizeof(pucDpTxHdcp2Signature));

    // Read Certificate Part I: Receiver ID(5 bytes) + Public Key(131 bytes) + Reserved(2 bytes)
    // Read Receiver ID(5 Bytes)
    if(ScalerDpTxAuxNativeRead(0x06, 0x90, 0x0B, 5, pData) == _FALSE)
    {
        return _FALSE;
    }

    memcpy(pucDpTxHdcp2CertificatePart1, pData, 5);
    memcpy(g_pucDpTxHdcp2ReceiverId, pData, 5);

    // Read Public n(128 Bytes)
    for(ucI = 0; ucI < 8; ucI++)
    {
        if(ScalerDpTxAuxNativeRead(0x06, 0x90, (0x10 + ucI * 16), 16, pData) == _FALSE)
        {
            return _FALSE;
        }

        memcpy(&pucDpTxHdcp2CertificatePart1[5 + ucI * 16], pData, 16);
    }

    memcpy(g_pucDpTxHdcp2Npub, &pucDpTxHdcp2CertificatePart1[5], 128);

    // Read Public e(3 Bytes) and Reserved(2 Bytes)
    if(ScalerDpTxAuxNativeRead(0x06, 0x90, 0x90, 5, pData) == _FALSE)
    {
        return _FALSE;
    }

    memcpy(&pucDpTxHdcp2CertificatePart1[133], pData, 5);
    memcpy(g_pucDpTxHdcp2Epub, &pucDpTxHdcp2CertificatePart1[133], 3);

    // Read Certificate Part II: Signature
    // Initial DPCD Address of Signature
    usDpcdAddress = 0x9095;

    for(ucI = 0; ucI < 24; ucI++)
    {
        if(ScalerDpTxAuxNativeRead(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), 16, pData) == _FALSE)
        {
            return _FALSE;
        }

        memcpy(&pucDpTxHdcp2Signature[ucI * 16], pData, 16);

        usDpcdAddress += 16;
    }

    for(ucI = 0; ucI < 48; ucI++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Enable write cipher text to RSA Module
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (47 - ucI));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucDpTxHdcp2Signature[ucI << 3], 8);

        /*
        for(pData[1] = 0; pData[1] < 8; pData[1]++)
        {
            DebugMessageHDCP2("S'", pucSignature[(pData[0] << 3) + pData[1]]);
        }
        */
    }

    // Read Rrx
    if(ScalerDpTxAuxNativeRead(0x06, 0x92, 0x15, 8, pData) == _FALSE)
    {
        return _FALSE;
    }

    memcpy(g_pucDpTxHdcp2Rrx, pData, 8);

    // Read RxCaps
    if(ScalerDpTxAuxNativeRead(0x06, 0x92, 0x1D, 3, pData) == _FALSE)
    {
        return _FALSE;
    }

    memcpy(g_pucDpTxHdcp2RxCaps, pData, 3);

    CLR_DP_TX_HDCP2_CAPABLE_SUPPORTED();
    CLR_DP_TX_HDCP2_REPEATER_SUPPORTED();
    CLR_DP_TX_HDCP2_VERSION_SUPPORTED();
    CLR_DP_TX_HDCP2_RXINFO_HDCP20_REPEATER_DOWNSTREAM();

    // Check HDCP Version
    if(((pData[0] == 0x02) || (pData[0] == 0x03) || (pData[0] == 0x04)) &&
       (pData[1] == 0x00) &&
       ((pData[2] & ~(_BIT1 | _BIT0)) == 0x00))
    {
        SET_DP_TX_HDCP2_VERSION_SUPPORTED();
    }

    // Check HDCP Capable
    if((pData[2] & _BIT1) == _BIT1)
    {
        SET_DP_TX_HDCP2_CAPABLE_SUPPORTED();
    }

    // Check HDCP Repeater
    if((pData[2] & _BIT0) == _BIT0)
    {
        SET_DP_TX_HDCP2_REPEATER_SUPPORTED();

        // Check  HDCP2.0 Repeater Downstream in the topology
        if(pData[0] < 0x02)
        {
            SET_DP_TX_HDCP2_RXINFO_HDCP20_REPEATER_DOWNSTREAM();
        }
    }

    // Compute Encode Message(EM)
    for(ucI = 0; ucI < 2; ucI++)
    {
        memcpy(pucSha256Input, &pucDpTxHdcp2CertificatePart1[ucI * 64], 64);

        if(ScalerHdcp2RxSha256Calculate(pucSha256Input, ucI) == _FALSE)
        {
            return _FALSE;
        }
    }

    memcpy(pucSha256Input, &pucDpTxHdcp2CertificatePart1[128], 10);
    memset(&pucSha256Input[10], 0, 54);
    pucSha256Input[10] = 0x80;
    pucSha256Input[62] = 0x04;
    pucSha256Input[63] = 0x50;

    if(ScalerHdcp2RxSha256Calculate(pucSha256Input, 2) == _FALSE)
    {
        return _FALSE;
    }

    // Get SHA-256(M) of EM
    memcpy(pucSha256Input, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

    /*
    for(pData[0] = 0; pData[0] < 32; pData[0]++)
    {
        DebugMessageHDCP2("EM", ScalerGetByte(P63_35_HDCP_SHA_0 + pData[0]));
    }
    */

    // Compute Encode Message Prime(EM')
    ScalerDpTxHdcp2DcpLlcRsaCalculate();

    // Get EM'
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5), _BIT6);

    // Read Message From One of 2 Address
    if(ScalerGetBit(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
    {
        for(pData[0] = 0; pData[0] < 48; pData[0]++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (47 - pData[0]));

            memcpy(&pucDpTxHdcp2Signature[pData[0] << 3], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
    else
    {
        for(pData[0] = 0; pData[0] < 48; pData[0]++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x30 + (47 - pData[0])));

            memcpy(&pucDpTxHdcp2Signature[pData[0] << 3], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }

    // Compare EM with EM'
    // EM[3071:0] = 0x00 || 0x01 || PS || 0x00 || T(SHA256) || SHA-256(M), length = 3072 bits

    // Check 0x00 || 0x01
    if((pucDpTxHdcp2Signature[0] != 0x00) && (pucDpTxHdcp2Signature[1] != 0x01))
    {
        DebugMessageHDCP2("S - Fail 0", 0);

        return _FALSE;
    }

    // Check PS(330 bytes)
    for(PDATA_WORD(0) = 2; PDATA_WORD(0) < 332; PDATA_WORD(0)++)
    {
        if(pucDpTxHdcp2Signature[PDATA_WORD(0)] != 0xFF)
        {
            DebugMessageHDCP2("S - Fail 1", PDATA_WORD(0));

            return _FALSE;
        }
    }

    // Check T(SHA256)
    for(PDATA_WORD(0) = 332; PDATA_WORD(0) < 352; PDATA_WORD(0)++)
    {
        if(pucDpTxHdcp2Signature[PDATA_WORD(0)] != pucDigestInfo[PDATA_WORD(0) - 332])
        {
            DebugMessageHDCP2("S - Fail 2", PDATA_WORD(0));

            return _FALSE;
        }
    }

    // Check SHA-256(M)
    for(PDATA_WORD(0) = 352; PDATA_WORD(0) < 384; PDATA_WORD(0)++)
    {
        if(pucDpTxHdcp2Signature[PDATA_WORD(0)] != pucSha256Input[PDATA_WORD(0) - 352])
        {
            DebugMessageHDCP2("S - Fail 3", PDATA_WORD(0));

            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpTxHdcp2RsaCalculate(BYTE *pucEmKmArray, BYTE *pucRrmodn)
{
    BYTE pucEpubXorCode[128] =
    {
        0x07, 0x0B, 0x6B, 0x8A, 0x18, 0x0A, 0xEE, 0x41,
        0xDE, 0x41, 0x83, 0x25, 0x23, 0x8A, 0x12, 0x3F,
        0x35, 0x65, 0xB3, 0x07, 0x89, 0x48, 0x28, 0x5E,
        0x6C, 0x49, 0xA6, 0x48, 0x0E, 0x2A, 0x52, 0x1F,
        0x32, 0x9A, 0x7B, 0x80, 0x51, 0x08, 0x27, 0x81,
        0x0D, 0x7E, 0xFD, 0x1E, 0xA5, 0x1E, 0xFA, 0xC0,
        0xC3, 0x5F, 0xB6, 0xBA, 0xB1, 0xE6, 0xA9, 0x98,
        0x7D, 0x4B, 0xB4, 0xF2, 0x8A, 0x07, 0xD2, 0xC1,
        0x7D, 0x8E, 0xA5, 0x59, 0xA2, 0x56, 0xAF, 0x80,
        0xA7, 0x5F, 0x20, 0x23, 0x3F, 0x96, 0xDE, 0x8F,
        0x5A, 0xBF, 0x9C, 0x7B, 0x3A, 0x22, 0x3A, 0x22,
        0xD9, 0x42, 0x18, 0xF6, 0xDB, 0x65, 0x33, 0x76,
        0x1F, 0xC2, 0x5F, 0xBC, 0xBF, 0x56, 0x24, 0x16,
        0x7E, 0xDB, 0x27, 0x78, 0x8C, 0xFC, 0x64, 0x17,
        0xCD, 0x00, 0xD6, 0xB1, 0xF6, 0x71, 0x7A, 0xDC,
        0x30, 0xCB, 0xAA, 0xB8, 0x3E, 0x39, 0x64, 0xEA,
    };


    // Enable HDCP 2.2 RSA Module
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));

    // RSA Clock Select
    ScalerSetBit(P63_92_HDCP_DUMMY1, ~_BIT7, _BIT7);

    // Reset HDCP 2.2 RSA module
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, 0x00);
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

    // Select RSA Key Download Data Length
    ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT7);

    // Load EM_km to RSA Module as Plain text
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Enable write cipher text to RSA Module
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(15 - pData[0]));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEmKmArray[pData[0] << 3], 8);
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load RRmodN
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucRrmodn[pData[0] << 3], 8);
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load N Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_pucDpTxHdcp2Npub[pData[0] << 3], 8);
    }

    // Encrypted Epub Key
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        pucEpubXorCode[125 + pData[0]] = pucEpubXorCode[125 + pData[0]] ^ g_pucDpTxHdcp2Epub[pData[0]];
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load e Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEpubXorCode[pData[0] << 3], 8);
    }

    // Set RSA Write key done
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

    // Enable RSA Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT4, 0x00);

    // Polling 100ms for RSA Module Done
    if(ScalerTimerPollingFlagProc(100, P63_10_HDCP_RSA_CTRL0, _BIT2, _SUCCESS) == _TRUE)
    {
        // Disable RSA Module
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT7, 0x00);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : No Stored Km Procss
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2NoStoredKmProc(void)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;
    BYTE pucSHA256Input[64];
    BYTE pucEkpubKm[128];
    BYTE pucDB[95];
    BYTE pucRrmodn[128];
    BYTE pucLHash[32] =
    {
        0xE3, 0xB0, 0xC4, 0x42, 0x98, 0xFC, 0x1C, 0x14,
        0x9A, 0xFB, 0xF4, 0xC8, 0x99, 0x6F, 0xB9, 0x24,
        0x27, 0xAE, 0x41, 0xE4, 0x64, 0x9B, 0x93, 0x4C,
        0xA4, 0x95, 0x99, 0x1B, 0x78, 0x52, 0xB8, 0x55,
    };

#if(_HDCP_2_2_TX_ERRATA_TEST_SUPPORT == _ON)
    BYTE pucSeed[32] =
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    };
#else
    BYTE pucSeed[32];

    memset(pucSeed, 0, sizeof(pucSeed));
#endif

    memset(pucSHA256Input, 0, sizeof(pucSHA256Input));
    memset(pucEkpubKm, 0, sizeof(pucEkpubKm));
    memset(pucDB, 0, sizeof(pucDB));
    memset(pucRrmodn, 0, sizeof(pucRrmodn));

    // Encrypt Km
    // Step1: Hash stream  L = 32byte 0x00 stream, lHash = SHA256(L) = 0x e3 b0 04 42 == > hLen = 32byte
    // Step2: PS stream = 0x00 stream == > PS Length = length(n) - length(km)-2xhLen-2 = 128 - 16 - 2x32 -2 = 46bytes
    // Step3: M = km stream == > km length = 16bytes

#if(_HDCP_2_2_TX_ERRATA_TEST_SUPPORT == _OFF)
    // Generate Km
    if(ScalerDpTxHdcp2RandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    // Load Km
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        g_pucDpTxHdcp2Km[pData[0]] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - pData[0]);
        PDATA_WORD(1) += g_pucDpTxHdcp2Km[pData[0]];
    }

    // Disable AES Random Gen
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }
#endif

    // Step4: DB = lHash || PS || 0x01 || M == > DB Length = 95bytes
    memcpy(pucDB, pucLHash, 32);
    memset(&pucDB[32], 0, 46);
    pucDB[78] = 0x01;
    memcpy(&pucDB[79], g_pucDpTxHdcp2Km, 16);

    // Step5: Generate random stream seed == > Seed Length = hLen = 32bytes

#if(_HDCP_2_2_TX_ERRATA_TEST_SUPPORT == _OFF)
    // Generate 16 bytes for Msb part of Random Stream Seed
    if(ScalerDpTxHdcp2RandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        pucSeed[pData[0]] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - pData[0]);
        PDATA_WORD(1) += pucSeed[pData[0]];
    }

    // Disable AES Random Gen
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);
    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }

    // Generate 16 bytes for Lsb part of Random Stream Seed
    if(ScalerDpTxHdcp2RandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        pucSeed[pData[0] + 16] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - pData[0]);
        PDATA_WORD(1) += pucSeed[pData[0] + 16];
    }

    // Disable AES Random Gen
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }
#endif

    // Step6: dbMask = MGF (seed, k-hLen-1) == > dbMask Length = 95bytes
    memcpy(pucSHA256Input, pucSeed, 32);
    memset(&pucSHA256Input[32], 0, 32);
    pucSHA256Input[36] = 0x80;
    pucSHA256Input[62] = 0x01;
    pucSHA256Input[63] = 0x20;

    for(ucI = 0; ucI < 3; ucI++)
    {
        pucSHA256Input[35] = ucI;

        if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 0) == _FALSE)
        {
            return _FALSE;
        }

        for(ucJ = 0; ucJ < 32; ucJ++)
        {
            pucEkpubKm[(ucI * 32) + ucJ] = ScalerGetByte((P63_35_HDCP_SHA_0 + ucJ));
        }
    }

    // Step7: maskedDB = DB XOR dbMask; == > maskedDB = 95 bytes
    for(ucI = 0; ucI < 95; ucI++)
    {
        pucDB[ucI] = pucDB[ucI] ^ pucEkpubKm[ucI];
    }

    // Step8: seedMask = MGF(maskedDB, hLen) == > seedMask Length = 32bytes
    memcpy(pucSHA256Input, pucDB, 64);

    if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 0) == _FALSE)
    {
        return _FALSE;
    }

    memcpy(pucSHA256Input, &pucDB[64], 31);
    memset(&pucSHA256Input[31], 0, 33);
    pucSHA256Input[35] = 0x80;
    pucSHA256Input[62] = 0x03;
    pucSHA256Input[63] = 0x18;

    if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 1) == _FALSE)
    {
        return _FALSE;
    }

    // Step9: maskedSeed = seed XOR seedMask == > maskedSeed Length = 32bytes
    for(ucI = 0; ucI < 32; ucI++)
    {
        pucEkpubKm[1 + ucI] = pucSeed[ucI] ^ ScalerGetByte((P63_35_HDCP_SHA_0 + ucI));
    }

    // Step10: EM = 0x00 || maskedSeed || maskedDB ==> EM Length = 1+ 32 + 95 = 128bytes
    pucEkpubKm[0] = 0x00;
    memcpy(&pucEkpubKm[33], pucDB, 95);

    ScalerDpTxHdcp2RrmodnCalculate(g_pucDpTxHdcp2Npub);

    // Read Out RSA Message
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5), _BIT6);

    // Read RRmodN
    for(ucI = 0; ucI < 16; ucI++)
    {
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x30 + (15 - ucI)));
        memcpy(&pucRrmodn[ucI * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
    }

    // Generate Ekpub[km]
    ScalerDpTxHdcp2RsaCalculate(pucEkpubKm, pucRrmodn);

    // Read Out RSA Message
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5), _BIT6);

    // Read Message From One of 2 Address
    if(ScalerGetBit(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
    {
        for(ucI = 0; ucI < 16; ucI++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (15 - ucI));
            memcpy(&pucEkpubKm[ucI * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
    else
    {
        for(ucI = 0; ucI < 16; ucI++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x30 + (15 - ucI)));
            memcpy(&pucEkpubKm[ucI * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }

    // Write Ekpub[km]
    for(ucI = 0; ucI < 8; ucI++)
    {
        if(ScalerDpTxAuxNativeWrite(0x06, 0x92, (0x20 + ucI * 16), 16, &pucEkpubKm[ucI * 16]) == _FALSE)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Stored Km Procss
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2RrmodnCalculate(BYTE *pucPubN)
{
    BYTE pucEpubXorCode[] =
    {
        0x07, 0x0B, 0x6B, 0x8A, 0x18, 0x0A, 0xEE, 0x41,
        0xDE, 0x41, 0x83, 0x25, 0x23, 0x8A, 0x12, 0x3F,
        0x35, 0x65, 0xB3, 0x07, 0x89, 0x48, 0x28, 0x5E,
        0x6C, 0x49, 0xA6, 0x48, 0x0E, 0x2A, 0x52, 0x1F,
        0x32, 0x9A, 0x7B, 0x80, 0x51, 0x08, 0x27, 0x81,
        0x0D, 0x7E, 0xFD, 0x1E, 0xA5, 0x1E, 0xFA, 0xC0,
        0xC3, 0x5F, 0xB6, 0xBA, 0xB1, 0xE6, 0xA9, 0x98,
        0x7D, 0x4B, 0xB4, 0xF2, 0x8A, 0x07, 0xD2, 0xC1,
        0x7D, 0x8E, 0xA5, 0x59, 0xA2, 0x56, 0xAF, 0x80,
        0xA7, 0x5F, 0x20, 0x23, 0x3F, 0x96, 0xDE, 0x8F,
        0x5A, 0xBF, 0x9C, 0x7B, 0x3A, 0x22, 0x3A, 0x22,
        0xD9, 0x42, 0x18, 0xF6, 0xDB, 0x65, 0x33, 0x76,
        0x1F, 0xC2, 0x5F, 0xBC, 0xBF, 0x56, 0x24, 0x16,
        0x7E, 0xDB, 0x27, 0x78, 0x8C, 0xFC, 0x64, 0x17,
        0xCD, 0x00, 0xD6, 0xB1, 0xF6, 0x71, 0x7A, 0xDC,
        0x30, 0xCB, 0xAA, 0xB8, 0x3E, 0x39, 0x64, 0xEA,
    };

    // Enable HDCP 2.2 RSA Module
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));

    // RSA Clock Select
    ScalerSetBit(P63_92_HDCP_DUMMY1, ~_BIT7, _BIT7);

    // Reset HDCP 2.2 RSA module
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, 0x00);
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

    // Select RSA Key Download Data Length and RRMODN mode
    ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Enable write cipher text to RSA Module
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (15 - pData[0])));

        memset((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, 0, 8);

        if((0x30 + (15 - pData[0])) == 0x3F)
        {
            ScalerSetByte(P63_17_HDCP_RSA_DATA_IN_DATA7, 0x80);
        }
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load N Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucPubN[pData[0] << 3], 8);
    }

    // 1024 bits + 66 bits
    PDATA_WORD(0) = 1088;

    pucEpubXorCode[126] = pData[0] ^ pucEpubXorCode[126];
    pucEpubXorCode[127] = pData[1] ^ pucEpubXorCode[127];

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load e Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEpubXorCode[pData[0] << 3], 8);
    }

    // Get Npub Mod 2^32
    memcpy(pData, &g_pucDpTxHdcp2Npub[124], 4);

    // Get Npinv
    PDATA_DWORD(0) = ScalerDpTxHdcp2NpinvCalculate(PDATA_DWORD(0));

    // Load Npinv to RSA Module
    memcpy((volatile BYTE xdata *)P63_12_HDCP_RSA_NP_INV_3, pData, 4);

    // Set RSA Write key done
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

    // Get Mod N Shift Counter
    PDATA_WORD(0) = ScalerDpTxHdcp2GetNShiftCounter(pucPubN);

    // Set Mod N Shift Counter
    ScalerSetByte(P63_28_HDCP_RSA_TX_FUNTION1, (BYTE)(PDATA_WORD(0) >> 4));
    ScalerSetBit(P63_29_HDCP_RSA_TX_FUNTION0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (BYTE)(PDATA_WORD(0) << 4));

    // Enable RSA Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT4, 0x00);

    // Polling 100ms for RSA Module Done
    if(ScalerTimerPollingFlagProc(100, P63_10_HDCP_RSA_CTRL0, _BIT2, _SUCCESS) == _TRUE)
    {
        // Disable RSA Module
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT7, 0x00);

        // Disable RRMODN mode
        ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~_BIT5, 0x00);

        return _TRUE;
    }

    // Disable RRMODN mode
    ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~_BIT5, 0x00);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Calculate Mod N Shift Counter
// Input Value  : None
// Output Value : 66 ~ 1089 => (1023 - (MSB No. of Kpubdcp-key) + 66)
//--------------------------------------------------
WORD ScalerDpTxHdcp2GetNShiftCounter(BYTE *pucPubN)
{
    for(pData[0] = 0; pData[0] < 128; pData[0]++)
    {
        for(pData[1] = 0; pData[1] < 8; pData[1]++)
        {
            if((bit)(pucPubN[pData[0]] & (_BIT7 >> pData[1])) == 1)
            {
                return ((WORD)(pData[0] * 8) + pData[1] + 66);
            }
        }
    }

    return 0x0441;
}

//--------------------------------------------------
// Description  : Npinv Calculate by Euclidean Algorithm
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
DWORD ScalerDpTxHdcp2NpinvCalculate(DWORD ulA)
{
    DWORD ulM = 0xFFFFFFFF; // 2^32 - 1
    DWORD ulE = ulM - ulA + 1;
    DWORD ulX = 0;
    DWORD ulY = 1;
    DWORD ulx = 1;
    DWORD uly = 1;

    while(ulE != 0)
    {
        PDATA_DWORD(0) = ulM / ulE;
        PDATA_DWORD(1) = ulM % ulE;

        if(ulM == 0xFFFFFFFF)
        {
            PDATA_DWORD(1)++;
        }

        ulM = ulE;
        ulE = PDATA_DWORD(1);

        PDATA_DWORD(1) = ulY;

        ulY *= PDATA_DWORD(0);

        if(ulx == uly)
        {
            if(ulX >= ulY)
            {
                ulY = ulX - ulY;
            }
            else
            {
                ulY -= ulX;
                uly = 0;
            }
        }
        else
        {
            ulY += ulX;
            ulx = 1 - ulx;
            uly = 1 - uly;
        }

        ulX = PDATA_DWORD(1);
    }

    if(ulx == 0)
    {
        ulX = 0xFFFFFFFF - ulX + 1;
    }

    return ulX;
}

//--------------------------------------------------
// Description  : Stored Km Procss
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2StoredKmProc(void)
{
    // Send Ekh[km]
    if(ScalerDpTxAuxNativeWrite(0x06, 0x92, 0xA0, 16, g_pucDpTxHdcp2PairingEkhkm) == _FALSE)
    {
        return _FALSE;
    }

    // Send m
    if(ScalerDpTxAuxNativeWrite(0x06, 0x92, 0xB0, 16, g_pucDpTxHdcp2PairingM) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Timeout to Read H'
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2TimeoutToReadHPrimeEvent(void)
{
    SET_DP_TX_HDCP2_H_PRIME_TIMEOUT();
}

//--------------------------------------------------
// Description  : H Verification
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2ComputeH(BYTE *pucDpTxHdcp2Rtx, BYTE *pucDpTxHdcp2Rrx, BYTE *pucDpTxHdcp2Km)
{
    // Get Kd = dkey0 || dkey1
    ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_0, pucDpTxHdcp2Rtx, pucDpTxHdcp2Rrx, pucDpTxHdcp2Km, g_pucDpTxHdcp2Rn);

    memcpy(g_pucDpTxHdcp2dKey0, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

    ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_1, pucDpTxHdcp2Rtx, pucDpTxHdcp2Rrx, pucDpTxHdcp2Km, g_pucDpTxHdcp2Rn);

    memcpy(g_pucDpTxHdcp2dKey1, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

    // Compute H
    if(ScalerHdcp2HPrimeCalculate(g_pucDpTxHdcp2dKey0, g_pucDpTxHdcp2dKey1, pucDpTxHdcp2Rtx, g_pucDpTxHdcp2TxCaps, g_pucDpTxHdcp2RxCaps) == _FALSE)
    {
        return _FALSE;
    }

    // Get H
    memcpy(g_pucDpTxHdcp2H, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

    return _TRUE;
}

//--------------------------------------------------
// Description  : H Verification
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2VerifyHprime(void)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;

    // Read H' and Compare H' with H
    for(ucI = 0; ucI < 2; ucI++)
    {
        if(ScalerDpTxAuxNativeRead(0x06, 0x92, (0xC0 + ucI * 16), 16, pData) == _FALSE)
        {
            return _FALSE;
        }

        for(ucJ = 0; ucJ < 16; ucJ++)
        {
            if(g_pucDpTxHdcp2H[16 * ucI + ucJ] != pData[ucJ])
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Pairing Info
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2StorePairingInfo(void)
{
    // Store Ekn[km]
    if(ScalerDpTxAuxNativeRead(0x06, 0x92, 0xE0, 16, g_pucDpTxHdcp2PairingEkhkm) == _FALSE)
    {
        return _FALSE;
    }

    // Store Km. m, Receiver ID
    memcpy(g_pucDpTxHdcp2PairingKm, g_pucDpTxHdcp2Km, 16);
    memcpy(g_pucDpTxHdcp2PairingM, g_pucDpTxHdcp2Rtx, 8);
    memcpy(&g_pucDpTxHdcp2PairingM[8], g_pucDpTxHdcp2Rrx, 8);
    memcpy(g_pucDpTxHdcp2PairingReceiverID, g_pucDpTxHdcp2ReceiverId, 5);

    SET_DP_TX_HDCP2_PAIRING_INFO_READY();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Clear Pairing Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2ClearPairingInfo(void)
{
    // Clear Km. m, Receiver ID
    memset(g_pucDpTxHdcp2PairingKm, 0, sizeof(g_pucDpTxHdcp2PairingKm));
    memset(g_pucDpTxHdcp2PairingM, 0, sizeof(g_pucDpTxHdcp2PairingM));
    memset(g_pucDpTxHdcp2PairingReceiverID, 0, sizeof(g_pucDpTxHdcp2PairingReceiverID));

    CLR_DP_TX_HDCP2_PAIRING_INFO_READY();
}

//--------------------------------------------------
// Description  : Check Pairing Info
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2CheckPairingInfo(void)
{
    BYTE ucI = 0;

    if(GET_DP_TX_HDCP2_PAIRING_INFO_READY() == _FALSE)
    {
        return _FALSE;
    }

    for(ucI = 0; ucI < 5; ucI++)
    {
        if(g_pucDpTxHdcp2PairingReceiverID[ucI] != g_pucDpTxHdcp2ReceiverId[ucI])
        {
            ScalerDpTxHdcp2ClearPairingInfo();

            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Timeout to Read pairing Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2TimeoutToReadPairingInfoEvent(void)
{
    SET_DP_TX_HDCP2_PAIRING_INFO_TIMEOUT();
}

//--------------------------------------------------
// Description  : Locality Check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2LocalityCheck(void)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;
    WORD usDpcdAddress = 0;
    BYTE pucL[32];

    memset(pucL, 0, sizeof(pucL));

#if(_HDCP_2_2_TX_ERRATA_TEST_SUPPORT == _OFF)
    // Generate Rn
    if(ScalerDpTxHdcp2RandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    // Load Rn
    for(ucI = 0; ucI < 8; ucI++)
    {
        g_pucDpTxHdcp2Rn[ucI] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - ucI);
        PDATA_WORD(1) += g_pucDpTxHdcp2Rn[ucI];
    }

    // Disable AES Random Gen
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }
#endif

    // Write Rn
    if(ScalerDpTxAuxNativeWrite(0x06, 0x92, 0xF0, 8, g_pucDpTxHdcp2Rn) == _FALSE)
    {
        return _FALSE;
    }

    ScalerTimerDelayXms(20);

    // Compute L
    if(ScalerHdcp2LPrimeCalculate(g_pucDpTxHdcp2dKey0, g_pucDpTxHdcp2dKey1, g_pucDpTxHdcp2Rrx, g_pucDpTxHdcp2Rn) == _FALSE)
    {
        return _FALSE;
    }

    // Get L
    memcpy(pucL, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

    // Initial DPCD Address of L'
    usDpcdAddress = 0x92F8;

    // Read L' and Compare L' with L
    for(ucI = 0; ucI < 2; ucI++)
    {
        if(ScalerDpTxAuxNativeRead(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), 16, pData) == _FALSE)
        {
            return _FALSE;
        }

        for(ucJ = 0; ucJ < 16; ucJ++)
        {
            if(pucL[16 * ucI + ucJ] != pData[ucJ])
            {
                return _FALSE;
            }
        }

        usDpcdAddress += 16;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Session Key Exchange Proc
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2SessionKeyExchangeProc(void)
{
    BYTE ucI = 0;
    BYTE pucdKey2[16];

#if(_HDCP_2_2_TX_ERRATA_TEST_SUPPORT == _ON)
    BYTE pucKs[16] =
    {
        0xf3, 0xdf, 0x1d, 0xd9, 0x57, 0x96, 0x12, 0x3f,
        0x98, 0x97, 0x89, 0xb4, 0x21, 0xe1, 0x2d, 0xe1,
    };
    BYTE pucdRiv[8] = {0x40, 0x2b, 0x6b, 0x43, 0xc5, 0xe8, 0x86, 0xd8};
#else
    BYTE pucKs[16];
    BYTE pucdRiv[8];

    memset(pucKs, 0, sizeof(pucKs));
    memset(pucdRiv, 0, sizeof(pucdRiv));
#endif

    memset(pucdKey2, 0, sizeof(pucdKey2));

#if(_HDCP_2_2_TX_ERRATA_TEST_SUPPORT == _OFF)
    // Generate Ks(128 bits)
    if(ScalerDpTxHdcp2RandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    // Load Ks
    for(ucI = 0; ucI < 16; ucI++)
    {
        pucKs[ucI] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - ucI);
        PDATA_WORD(1) += pucKs[ucI];

        // Set Ks to Cipher
        ScalerSetByte((PBB_80_HDCP_AES_CIPHER_KEY_15 + ucI), (pucKs[ucI] ^ g_stRxHdcp2DownLoadKeyType.pucHdcp2Lc[ucI]));
    }

    // Disable AES Random Gen
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }
#else
    // Load Ks
    for(ucI = 0; ucI < 16; ucI++)
    {
        pucKs[ucI] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - ucI);

        // Set Ks to Cipher
        ScalerSetByte((PBB_80_HDCP_AES_CIPHER_KEY_15 + ucI), (pucKs[ucI] ^ g_stRxHdcp2DownLoadKeyType.pucHdcp2Lc[ucI]));
    }
#endif

    // Generate dkey2
    ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_2, g_pucDpTxHdcp2Rtx, g_pucDpTxHdcp2Rrx, g_pucDpTxHdcp2Km, g_pucDpTxHdcp2Rn);

    memcpy(pucdKey2, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

    // Compute Edkey(ks)
    // LSB 64bits of dkey2 ^ Rrx
    for(ucI = 0; ucI < 8; ucI++)
    {
        pucdKey2[ucI + 8] = g_pucDpTxHdcp2Rrx[ucI] ^ pucdKey2[ucI + 8];
    }

    // Edkey(ks) = ks ^ (dkey2 ^ Rrx)
    for(ucI = 0; ucI < 16; ucI++)
    {
        pucKs[ucI] = pucKs[ucI] ^ pucdKey2[ucI];
    }

    // Write Edkey(ks)
    if(ScalerDpTxAuxNativeWrite(0x06, 0x93, 0x18, 16, pucKs) == _FALSE)
    {
        return _FALSE;
    }

#if(_HDCP_2_2_TX_ERRATA_TEST_SUPPORT == _OFF)
    // Generate riv(64 bits)
    if(ScalerDpTxHdcp2RandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    // Load riv
    for(ucI = 0; ucI < 8; ucI++)
    {
        pucdRiv[ucI] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - ucI);
        PDATA_WORD(1) += pucdRiv[ucI];

        // Set Riv to Cipher
        ScalerSetByte((PBB_11_RIV0 + ucI), pucdRiv[ucI]);
    }

    // Disable AES Random Gen
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }
#else
    // Load riv
    for(ucI = 0; ucI < 8; ucI++)
    {
        pucdRiv[ucI] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - ucI);

        // Set Riv to Cipher
        ScalerSetByte((PBB_11_RIV0 + ucI), pucdRiv[ucI]);
    }
#endif

    // Write riv
    if(ScalerDpTxAuxNativeWrite(0x06, 0x93, 0x28, 8, pucdRiv) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Timeout to Encrypt Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2TimeoutToEncyptDataEvent(void)
{
    SET_DP_TX_HDCP2_ENCRYPT_DATA_TIMEOUT();
}

//--------------------------------------------------
// Description  : Waiting for V ready
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2TimeoutForVReadyEvent(void)
{
    SET_DP_TX_HDCP2_V_READY_TIMEOUT();
}

//--------------------------------------------------
// Description  : Polling V Ready bit
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2PollingVReadyEvent(void)
{
    SET_DP_TX_HDCP2_POLLING_V_READY();
}

//--------------------------------------------------
// Description  : Check Rx Info
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2ChecRxInfo(void)
{
    // Read Rxinfo(Device Count and Depth)
    ScalerDpTxAuxNativeRead(0x06, 0x93, 0x30, 2, pData);

    // Check if MAX_DEVS_EXCEEDED or MAX_CASCADE_EXCEEDED is 1 and then abort authentication
    if((pData[1] & _BIT3) == _BIT3)
    {
        SET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT_EXCEED();
    }
    else
    {
        CLR_DP_TX_HDCP2_RXINFO_DEVICE_COUNT_EXCEED();
    }

    if((pData[1] & _BIT2) == _BIT2)
    {
        SET_DP_TX_HDCP2_RXINFO_DEPTH_EXCEED();
    }
    else
    {
        CLR_DP_TX_HDCP2_RXINFO_DEPTH_EXCEED();
    }

    // Set Rx Info
    SET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT(((pData[0] & _BIT0) << 4) | (pData[1] & 0xF0) >> 4);
    SET_DP_TX_HDCP2_RXINFO_DEPTH((pData[0] & 0x0E) >> 1);

    if((GET_DP_TX_HDCP2_RXINFO_HDCP20_REPEATER_DOWNSTREAM() == _FALSE) && ((pData[1] & _BIT1) == _BIT1))
    {
        SET_DP_TX_HDCP2_RXINFO_HDCP20_REPEATER_DOWNSTREAM();
    }

    if((pData[1] & _BIT0) == _BIT0)
    {
        SET_DP_TX_HDCP2_RXINFO_HDCP1_DOWNSTREAM();
    }
    else
    {
        CLR_DP_TX_HDCP2_RXINFO_HDCP1_DOWNSTREAM();
    }

    if((GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT_EXCEED() == _TRUE) ||
       (GET_DP_TX_HDCP2_RXINFO_DEPTH_EXCEED() == _TRUE))
    {
        return _FALSE;
    }

    DebugMessageHDCP2("Get Downstream Device", GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT());
    DebugMessageHDCP2("Get Downstream Depth", GET_DP_TX_HDCP2_RXINFO_DEPTH());

    return _TRUE;
}

//--------------------------------------------------
// Description  : V Verification
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2VerifyVprime(void)
{
    BYTE pucRxInfo[2];
    BYTE pucSeqNumV[3];
    WORD usDpcdAddress = 0;
    BYTE pucV[32];

    memset(pucRxInfo, 0, sizeof(pucRxInfo));
    memset(pucSeqNumV, 0, sizeof(pucSeqNumV));
    memset(pucV, 0, sizeof(pucV));
    memset(g_pucDpTxHdcp2ReceiverIdList, 0, sizeof(g_pucDpTxHdcp2ReceiverIdList));


    // Read Rxinfo
    ScalerDpTxAuxNativeRead(0x06, 0x93, 0x30, 2, pucRxInfo);

    // Read seq_bum_V
    ScalerDpTxAuxNativeRead(0x06, 0x93, 0x32, 3, pucSeqNumV);

    PDATA_DWORD(0) = ((DWORD)pucSeqNumV[0] << 16) | ((DWORD)pucSeqNumV[1] << 8) | (DWORD)pucSeqNumV[2];

    if((GET_DP_TX_HDCP2_SEQUENCE_NUMBER_V() == 0x00FFFFFF) && (PDATA_DWORD(0) == 0x00))
    {
        return _FALSE;
    }

    SET_DP_TX_HDCP2_SEQUENCE_NUMBER_V(PDATA_DWORD(0));

    pucV[0] = GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT() * 5;

    // Initial DPCD Address of Receicer ID List
    usDpcdAddress = 0x9345;

    // Read KSV FIFO List from Downstream Device
    do
    {
        ScalerDpTxAuxNativeRead(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), ((pucV[0] > 15) ? 15 : pucV[0]), pData);

        memcpy(&g_pucDpTxHdcp2ReceiverIdList[pucV[1]], pData, ((pucV[0] > 15) ? 15 : pucV[0]));

        usDpcdAddress += 15;
        pucV[1] += 15;

        pucV[0] = (pucV[0] > 15) ? (pucV[0] - 15) : 0x00;
    }
    while(pucV[0] != 0x00);

    // Compute V = HMAC-SHA256(Receiver ID List || RxInfo || seq_num_V, kd)
    if(ScalerHdcp2VprimeCalculate(g_pucDpTxHdcp2dKey0, g_pucDpTxHdcp2dKey1, g_pucDpTxHdcp2ReceiverIdList, pucRxInfo, pucSeqNumV) == _FALSE)
    {
        return _FALSE;
    }

    // Get V
    memcpy(pucV, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);
    memcpy(g_pucDpTxHdcp2DownStreamV, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 20);

    // Read MSB of V'
    if(ScalerDpTxAuxNativeRead(0x06, 0x93, 0x35, 16, pData) == _FALSE)
    {
        return _FALSE;
    }

    for(usDpcdAddress = 0; usDpcdAddress < 16; usDpcdAddress++)
    {
        if(pucV[usDpcdAddress] != pData[usDpcdAddress])
        {
            return _FALSE;
        }
    }

    // Write LSB of V
    if(ScalerDpTxAuxNativeWrite(0x06, 0x93, 0xE0, 16, &pucV[16]) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Content Stream Management
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpTxHdcp2ContentStreamManagement(void)
{
    WORD usK = 0;
    BYTE pucStreamIDType[126];
    BYTE ucI = 0;
    BYTE ucStreamId = 0;
    WORD usDpcdAddress = 0;

    memset(pucStreamIDType, 0, sizeof(pucStreamIDType));

    // Reset type value of Tx_STx(x = 1~4)
    ScalerSetBit(PBB_90_HDCP22_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Clear Length of STx Encrypted Stream
    ScalerSetBit(PBB_6C_DP_STREAM_1_PBN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PBB_6D_DP_STREAM_2_PBN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PBB_6E_DP_STREAM_3_PBN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_DP_MST_SUPPORT == _ON)
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
    {
        if(ScalerSyncDpGetHdcp2ModeStatus() == _TRUE)
        {
            DebugMessageHDCP2("CSM - HDCP22 to 22", 0);

            usK = ((WORD)GET_DP_TX_HDCP2_DPCD_INFO(0x06, 0x93, 0xF3) << 8) | GET_DP_TX_HDCP2_DPCD_INFO(0x06, 0x93, 0xF4);

            usK = (usK > 1) ? (usK - 1) : 1;

            if(usK > 3)
            {
                // Max. Number of MST Stream can be transmitted by DPTX is 3
                usK = 3;
            }
        }
        else
        {
            DebugMessageHDCP2("CSM - HDCP13 to 22", 0);

            usK = (GET_REG_DP_RX_MST_ST3_SOURCE_STATUS() != 0) + (GET_REG_DP_RX_MST_ST4_SOURCE_STATUS() != 0) + (GET_REG_DP_RX_MST_ST5_SOURCE_STATUS() != 0);
        }

        DebugMessageHDCP2("CSM - MST2MST", 0);

        for(ucI = 0; ucI < usK; ucI++)
        {
            // Get Stream Source X Status
            ucStreamId = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE3 + ucI) - 1;

            // Get Stream IDx in STx
            pucStreamIDType[ucI * 2] = g_pucDpStreamToIdMapping[ucStreamId];

            if(ScalerSyncDpGetHdcp2ModeStatus() == _TRUE)
            {
                // Get Type of Stream IDx
                pucStreamIDType[(ucI * 2) + 1] = GET_DP_TX_HDCP2_RX_STX_TYPE(ucStreamId);
            }
            else
            {
                // Get Type of Stream IDx
                pucStreamIDType[(ucI * 2) + 1] = 0;
            }

            // Set Type of Tx_ST1
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~(_BIT7 >> ucI), (pucStreamIDType[(ucI * 2) + 1] << (7 - ucI)));

            // Set Length of STx Stream to Be Ready For Encryption
            ScalerSetBit((PBB_6C_DP_STREAM_1_PBN + ucI), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_TX_STX_TIMESLOT_LENGTH(_DP_ST_SOURCE3 + ucI));

            DebugMessageHDCP2("CSM - STx Source", ucStreamId);
            DebugMessageHDCP2("CSM - STx Stream ID", pucStreamIDType[ucI * 2]);
            DebugMessageHDCP2("CSM - TimeSlot Length", GET_DP_TX_STX_TIMESLOT_LENGTH(_DP_ST_SOURCE3 + ucI));
        }

        DebugMessageHDCP2("CSM - MST2SST Type", ScalerGetBit(PBB_90_HDCP22_CTRL, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)));
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        usK = 1;

        // Get Stream IDx
        pucStreamIDType[0] = 0x00;

        if(ScalerSyncDpGetHdcp2ModeStatus() == _TRUE)
        {
            DebugMessageHDCP2("CSM - HDCP22 to 22", 0);

            // Get Stream Source X Status
            ucStreamId = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE2) - 1;

            // Get Type Value
            pucStreamIDType[1] = GET_DP_TX_HDCP2_RX_STX_TYPE(ucStreamId);
        }
        else
        {
            DebugMessageHDCP2("CSM - HDCP13 to 22", 0);

            // Set Type Value = 0 for HDCP1.3
            pucStreamIDType[1] = 0x00;
        }

        DebugMessageHDCP2("CSM - MST2SST", 0);

        if(pucStreamIDType[1] == 0x00)
        {
            // Set Type Value of Tx_ST1 as 0
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT7, 0x00);
        }
        else
        {
            // Set Type Value of Tx_ST1 as 1
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT7, _BIT7);
        }

        DebugMessageHDCP2("CSM - MST2SST Type", pucStreamIDType[1]);
    }
    else
#endif
    {
        usK = 1;

        // Get Stream IDx
        pucStreamIDType[0] = 0x00;

        if(ScalerSyncDpGetHdcp2ModeStatus() == _TRUE)
        {
            DebugMessageHDCP2("CSM - HDCP22 to 22", 0);

            // Get Type of Rx_ST1
            pucStreamIDType[1] = GET_DP_TX_HDCP2_DPCD_INFO(0x06, 0x93, 0xF6);
        }
        else
        {
            DebugMessageHDCP2("CSM - HDCP13 to 22", 0);

            // Set Type = 00
            pucStreamIDType[1] = 0x00;
        }

        if(pucStreamIDType[1] == 0x00)
        {
            // Set Type Value of Tx_ST1 as 0
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT7, 0x00);
        }
        else
        {
            // Set Type Value of Tx_ST1 as 1
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT7, _BIT7);
        }

        DebugMessageHDCP2("CSM - SST2SST Type", pucStreamIDType[1]);
    }

    // Enable AES-Ctrl Cipher
    ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT1, _BIT1);

    // Write seq_num_M[23 : 0]
    PDATA_DWORD(0) = GET_DP_TX_HDCP2_SEQUENCE_NUMBER_M();
    ScalerDpTxAuxNativeWrite(0x06, 0x93, 0xF0, 3, &pData[1]);

    // Write k
    PDATA_WORD(0) = usK;
    ScalerDpTxAuxNativeWrite(0x06, 0x93, 0xF3, 2, pData);

    // Initial DPCD Address of Stream ID Type
    usDpcdAddress = 0x93F5;

    // Initial Length of Stream ID Type
    ucI = 126;

    do
    {
        // Write StreamID_Type
        ScalerDpTxAuxNativeWrite(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), 16, &pucStreamIDType[abs(usDpcdAddress - 0x93F5)]);

        usDpcdAddress += 16;
        ucI -= 16;

        if(ucI <= 16)
        {
            // Write StreamID_Type
            ScalerDpTxAuxNativeWrite(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), ucI, &pucStreamIDType[abs(usDpcdAddress - 0x93F5)]);
        }
    }
    while(ucI > 16);

    if(ScalerHdcp2MprimeCalculate(g_pucDpTxHdcp2dKey0, g_pucDpTxHdcp2dKey1, pucStreamIDType, GET_DP_TX_HDCP2_SEQUENCE_NUMBER_M(), usK) == _FALSE)
    {
        return _FALSE;
    }

    // Get M
    memcpy(g_pucDpTxHdcp2M, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Timeout to Read M'
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2TimeoutToReadMPrimeEvent(void)
{
    SET_DP_TX_HDCP2_M_PRIME_TIMEOUT();
}

//--------------------------------------------------
// Description  : M Verification
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxHdcp2VerifyMprime(void)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;

    // Read M' and Compare M' with M
    for(ucI = 0; ucI < 2; ucI++)
    {
        if(ScalerDpTxAuxNativeRead(0x06, 0x94, (0x73 + ucI * 16), 16, pData) == _FALSE)
        {
            return _FALSE;
        }

        for(ucJ = 0; ucJ < 16; ucJ++)
        {
            if(g_pucDpTxHdcp2M[16 * ucI + ucJ] != pData[ucJ])
            {
                DebugMessageHDCP2("CSM - M != M'", 16 * ucI + ucJ);

                return _FALSE;
            }
        }
    }

    DebugMessageHDCP2("CSM - M Pass", 0);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Content Stream Management Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2ContentStreamManagementHandler(void)
{
    BYTE ucI = 0;
    BYTE ucTypeValue = 0;
    WORD usKValue = 0;
    BYTE ucStreamId = 0;

    if((ScalerSyncDpHdcp2GetContentStreamManagementStatus() == _TRUE) && (GET_DP_TX_HDCP2_CONTENT_STREAM_MANAGEMENT() == _FALSE))
    {
        CLR_DP_TX_HDCP2_STOP_CONTENT_STREAM();

        if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) &&
           (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE) &&
           (GET_DP_TX_HDCP2_AUTH_STATE() > _HDCP_2_2_TX_STATE_SKE))
        {
            DebugMessageHDCP2("CSM - DPTX HDCP22", 0);

            ScalerDpTxHdcp2EncryptSignalProc(_DISABLE);

            if(GET_DP_TX_HDCP2_REPEATER_SUPPORTED() == _TRUE)
            {
                DebugMessageHDCP2("CSM - DPTX RP ON", 0);

                if(ScalerDpTxHdcp2ContentStreamManagement() == _TRUE)
                {
                    ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_M_PRIME);
                }
                else
                {
                    DebugMessageHDCP2("CSM - DPTX M Preset fail", 0);
                }
            }
            else
            {
                DebugMessageHDCP2("CSM - DPTX RP OFF", 0);

                if(ScalerSyncDpGetHdcp2ModeStatus() == _TRUE)
                {
                    DebugMessageHDCP2("CSM - HDCP22 to 22", 0);

                    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
                    {
                        // Get Stream Source X Status
                        ucStreamId = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE3) - 1;

                        // RX in MST Mode
                        ucTypeValue = GET_DP_TX_HDCP2_RX_STX_TYPE(ucStreamId);

                        DebugMessageHDCP2("CSM - MST2MST type", ucTypeValue);
                    }
                    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
                    {
                        // Get Stream Source X Status
                        ucStreamId = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE2) - 1;

                        // RX in MST Mode
                        ucTypeValue = GET_DP_TX_HDCP2_RX_STX_TYPE(ucStreamId);

                        DebugMessageHDCP2("CSM - MST2SST type", ucTypeValue);
                    }
                    else
                    {
                        // RX in SST Mode
                        ucTypeValue = (bit)GET_DP_TX_HDCP2_DPCD_INFO(0x06, 0x93, 0xF6);

                        DebugMessageHDCP2("CSM - SST2SST type", ucTypeValue);
                    }
                }
                else
                {
                    // Set Type Value = 0 when RX is HDCP1.3
                    ucTypeValue = 0x00;

                    DebugMessageHDCP2("CSM - HDCP13 to 22", 0x00);
                    DebugMessageHDCP2("CSM - type", ucTypeValue);
                }

                // Ser Type of Tx_ST1
                ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT7, (ucTypeValue << 7));

                // Enable AES-Ctrl Cipher
                ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT1, _BIT1);

                // Write Type Value to SST Sink
                ScalerDpTxAuxNativeWrite(0x06, 0x94, 0x94, 1, &ucTypeValue);

                // Set up 200ms Timer Event
                ScalerTimerActiveTimerEvent(SEC(0.2), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_ENCRYPT_DATA);
            }

            SET_DP_TX_HDCP2_CONTENT_STREAM_MANAGEMENT();
        }
        else if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) &&
                (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _FALSE) &&
                (GET_DP_TX_HDCP2_AUTH_STATE() > _HDCP_2_2_TX_STATE_SKE))
        {
            DebugMessageHDCP2("CSM - DPTX HDCP20", 0);

            // HDCP 2.0-compliant can't support content stream management
            ScalerDpTxHdcp2EncryptSignalProc(_DISABLE);

            // Reset type value of Tx_STx(x = 1~4)
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            if(ScalerSyncDpGetHdcp2ModeStatus() == _TRUE)
            {
                if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
                {
                    usKValue = ((WORD) GET_DP_TX_HDCP2_DPCD_INFO(0x06, 0x93, 0xF3) << 8) | GET_DP_TX_HDCP2_DPCD_INFO(0x06, 0x93, 0xF4);

                    usKValue = (usKValue > 1) ? (usKValue - 1) : 1;

                    if(usKValue > 3)
                    {
                        // Max. Number of MST Stream can be transmitted by DPTX is 3
                        usKValue = 3;
                    }

                    ucTypeValue = 0;

                    for(ucI = 0; ucI < usKValue; ucI++)
                    {
                        // Get Stream Source X Status
                        ucStreamId = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE3 + ucI) - 1;

                        // Check Type of Stream IDx
                        ucTypeValue = ucTypeValue + (BYTE)GET_DP_TX_HDCP2_RX_STX_TYPE(ucI);

                        // Set Length of STx Stream to Be Ready For Encryption
                        ScalerSetBit((PBB_6C_DP_STREAM_1_PBN + ucI), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_RX_MST_STREAM_TIME_SLOT(ucStreamId));
                    }
                }
                else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
                {
                    // Get Stream Source X Status
                    ucStreamId = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE2) - 1;

                    // RX in MST Mode
                    ucTypeValue = GET_DP_TX_HDCP2_RX_STX_TYPE(ucStreamId);
                }
                else
                {
                    // RX in SST Mode
                    ucTypeValue = GET_DP_TX_HDCP2_DPCD_INFO(0x06, 0x93, 0xF6);
                }
            }
            else
            {
                // Set Type Value = 0 when RX is HDCP1.3
                ucTypeValue = 0x00;
            }

            if(ucTypeValue == 0x00)
            {
                // Enable AES-Ctrl Cipher
                ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT1, _BIT1);

                // Set up 200ms Timer Event
                ScalerTimerActiveTimerEvent(SEC(0.2), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_ENCRYPT_DATA);
            }
            else
            {
                // Disable AES-Ctrl Cipher
                ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT1, 0x00);

                DebugMessageHDCP2("HDCP 2.0 must not be received stream with Type = 1", 0);

                SET_DP_TX_HDCP2_STOP_CONTENT_STREAM();
            }

            SET_DP_TX_HDCP2_CONTENT_STREAM_MANAGEMENT();
        }
        else if((ScalerSyncDpGetHdcp2ModeStatus() == _TRUE) &&
                (GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _FALSE) &&
                (GET_DP_TX_HDCP_AUTH_STATE() >= _DP_TX_HDCP_STATE_AUTH_2))
        {
            DebugMessageHDCP2("CSM - DPTX HDCP 1x", 0);

            // HDCP 1.x-compliant can't support content stream management
            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
            {
                usKValue = ((WORD) GET_DP_TX_HDCP2_DPCD_INFO(0x06, 0x93, 0xF3) << 8) | GET_DP_TX_HDCP2_DPCD_INFO(0x06, 0x93, 0xF4);

                usKValue = (usKValue > 1) ? (usKValue - 1) : 1;

                if(usKValue > 3)
                {
                    // Max. Number of MST Stream can be transmitted by DPTX is 3
                    usKValue = 3;
                }

                ucTypeValue = 0;

                for(ucI = 0; ucI < usKValue; ucI++)
                {
                    // Get Stream Source X Status
                    ucStreamId = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE3 + ucI) - 1;

                    // Check Type of Stream IDx
                    ucTypeValue = ucTypeValue + (BYTE)GET_DP_TX_HDCP2_RX_STX_TYPE(ucStreamId);
                }

                DebugMessageHDCP2("CSM - MST2MST type", ucTypeValue);
            }
            else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
            {
                // Get Stream Source X Status
                ucStreamId = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE2) - 1;

                // RX in MST Mode
                ucTypeValue = GET_DP_TX_HDCP2_RX_STX_TYPE(ucStreamId);

                DebugMessageHDCP2("CSM - MST2SST type", ucTypeValue);
            }
            else
            {
                // RX in SST Mode
                ucTypeValue = GET_DP_TX_HDCP2_DPCD_INFO(0x06, 0x93, 0xF6);

                DebugMessageHDCP2("CSM - SST2SST type", ucTypeValue);
            }

            if(ucTypeValue != 0x00)
            {
                DebugMessageHDCP2("HDCP 1.x must not be received stream with Type = 1", 0);

                SET_DP_TX_HDCP2_STOP_CONTENT_STREAM();
            }

            SET_DP_TX_HDCP2_CONTENT_STREAM_MANAGEMENT();
        }
    }

    if(GET_DP_TX_HDCP2_M_PRIME_TIMEOUT() == _TRUE)
    {
        CLR_DP_TX_HDCP2_M_PRIME_TIMEOUT();

        if(GET_DP_TX_HDCP2_AUTH_STATE() > _HDCP_2_2_TX_STATE_SKE)
        {
            if(ScalerDpTxHdcp2VerifyMprime() == _TRUE)
            {
                // Set up 200ms Timer Event
                ScalerTimerActiveTimerEvent(SEC(0.2), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_ENCRYPT_DATA);
            }
            else
            {
                DebugMessageHDCP2("CSM - DPTX M Verify fail", 0);

                // seq_num_M roll-over detected
                if(GET_DP_TX_HDCP2_SEQUENCE_NUMBER_M() >= 0x00FFFFFF)
                {
                    ScalerDpTxHdcp2ChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                }
                else
                {
                    ADD_DP_TX_HDCP2_SEQUENCE_NUMBER_M();

                    CLR_DP_TX_HDCP2_CONTENT_STREAM_MANAGEMENT();
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Content Stream Management Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHdcp2OutputContentStreamHandler(void)
{
    if((ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE) &&
       (GET_DP_TX_HDCP2_STOP_CONTENT_STREAM() == _TRUE))
    {
        if(GET_DP_TX_HDCP2_BACKUP_CONTENT_STREAM() == _FALSE)
        {
            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
            {
                // Main Link switch to IDLE Pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_IDLE_PATTERN << 4));

                // Direct Apply Idle Pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

                SET_DP_TX_HDCP2_BACKUP_CONTENT_STREAM();

                DebugMessageHDCP2("CSM - Back up Clone", 0);
            }
#if(_DP_MST_SUPPORT == _ON)
            else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
            {
                // Main Link switch to IDLE Pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_IDLE_PATTERN << 4));

                // Direct Apply Idle Pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

                SET_DP_TX_HDCP2_BACKUP_CONTENT_STREAM();

                DebugMessageHDCP2("CSM - Back up MST2SST", 0);
            }
            else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
            {
                // Backup TimeSlot Info of Daisy Chain
                memcpy(g_pucDpTxHdcp2MstTimeSlotBackup, (volatile BYTE xdata *)PA_92_DAISY_CTRL_1, 6);

                // Clear TimeSlot Info of Daisy Chain
                memset((volatile BYTE xdata *)PA_92_DAISY_CTRL_1, 0, 6);

                // Double Buffer by ACT
                SET_REG_DP_RX_SEND_ACT_ENABLE();

                // more than (1024 MTP + 5 MTP) x 64 timeslot, unit: link clock
                ScalerTimerDelayXms(2);

                SET_DP_TX_HDCP2_BACKUP_CONTENT_STREAM();

                DebugMessageHDCP2("CSM - Back up MST", 0);
            }
#endif
        }
    }
    else
    {
        if(GET_DP_TX_HDCP2_BACKUP_CONTENT_STREAM() == _TRUE)
        {
            DebugMessageHDCP2("CSM - Restore Stream", 0);

            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
            {
                // Main Link switch to VIDEO pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_VIDEO_PATTERN << 4));

                // Double buffer only by Vsync
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);

                DebugMessageHDCP2("CSM - Restore Clone", 0);
            }
#if(_DP_MST_SUPPORT == _ON)
            else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
            {
                // Main Link switch to VIDEO pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_VIDEO_PATTERN << 4));

                // Double buffer only by Vsync
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);

                DebugMessageHDCP2("CSM - Restore MST2SST", 0);
            }
            else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
            {
                // Restore TimeSlot Info of Daisy Chain
                memcpy((volatile BYTE xdata *)PA_92_DAISY_CTRL_1, g_pucDpTxHdcp2MstTimeSlotBackup, 6);

                // Clear Temp Timeslot Info
                memset(g_pucDpTxHdcp2MstTimeSlotBackup, 0, 6);

                // Double Buffer by ACT
                SET_REG_DP_RX_SEND_ACT_ENABLE();

                // more than (1024 MTP + 5 MTP) x 64 timeslot, unit: link clock
                ScalerTimerDelayXms(2);

                DebugMessageHDCP2("CSM - Restore MST Timeslot", 0);
            }
#endif
            CLR_DP_TX_HDCP2_BACKUP_CONTENT_STREAM();
        }
    }
}

//--------------------------------------------------
// Description  : Enable HDCP2.2 TX Encryption
// Input Value  : _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerDpTxHdcp2EncryptSignalProc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_MST_SUPPORT == _ON)
        // Output MST type
        if(GET_DP_TX_MST_ENABLE() == _TRUE)
        {
            // Set ECF by HW
            ScalerSetBit(PBB_64_HDCP_ECF_BYTE0, ~_BIT7, _BIT7);

            // Enable MST ST3 Stream Encryption
            if(ScalerGetBit(PBB_6C_DP_STREAM_1_PBN, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
            {
                ScalerSetBit(PBB_6C_DP_STREAM_1_PBN, ~_BIT6, _BIT6);
            }

            // Enable MST ST4 Stream Encryption
            if(ScalerGetBit(PBB_6D_DP_STREAM_2_PBN, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
            {
                ScalerSetBit(PBB_6D_DP_STREAM_2_PBN, ~_BIT6, _BIT6);
            }

            // Enable MST ST5 Stream Encryption
            if(ScalerGetBit(PBB_6E_DP_STREAM_3_PBN, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
            {
                ScalerSetBit(PBB_6E_DP_STREAM_3_PBN, ~_BIT6, _BIT6);
            }

            // Double Buffer by ACT
            SET_REG_DP_RX_SEND_ACT_ENABLE();

            // more than (1024 MTP + 5 MTP) x 64 timeslot, unit: link clock
            ScalerTimerDelayXms(2);
        }
#endif

        // Enable HDCP Encryption
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT1, _BIT1);
    }
    else
    {
        // Disable HDCP Encryption
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT1, 0x00);

#if(_DP_MST_SUPPORT == _ON)
        // Disable MST ST3/ST4/ST5 Stream Encryption
        ScalerSetBit(PBB_6C_DP_STREAM_1_PBN, ~_BIT6, 0x00);
        ScalerSetBit(PBB_6D_DP_STREAM_2_PBN, ~_BIT6, 0x00);
        ScalerSetBit(PBB_6E_DP_STREAM_3_PBN, ~_BIT6, 0x00);

        // Output MST type
        if(GET_DP_TX_MST_ENABLE() == _TRUE)
        {
            // Double Buffer by ACT
            SET_REG_DP_RX_SEND_ACT_ENABLE();

            // more than (1024 MTP + 5 MTP) x 64 timeslot, unit: link clock
            ScalerTimerDelayXms(2);
        }

        // Set ECF by FW
        ScalerSetBit(PBB_64_HDCP_ECF_BYTE0, ~_BIT7, 0x00);
#endif
    }
}
#endif // End of #if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
