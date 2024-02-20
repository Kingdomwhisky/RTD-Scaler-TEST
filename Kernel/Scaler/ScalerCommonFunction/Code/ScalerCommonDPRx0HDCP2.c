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
// ID Code      : ScalerCommonDPRx0HDCP2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerCommonFunctionInclude.h"

#if(_DP_HDCP_2_2_SUPPORT == _ON)
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
//----------------------------------------------------------------------------
// Global Variables (XDATA) for Each Interface = 77 Bytes
//----------------------------------------------------------------------------
BYTE g_ucDPRx0Hdcp2Ctrl0;
BYTE g_ucDPRx0Hdcp2Ctrl1;
BYTE g_pucDpRx0Hdcp2dKey0[16];
BYTE g_pucDpRx0Hdcp2dKey1[16];
BYTE g_pucDpRx0Hdcp2Km[16];
BYTE g_pucDpRx0Hdcp2Rtx[8];
BYTE g_pucDpRx0Hdcp2TxCaps[3];
BYTE g_pucDpRx0Hdcp2Rn[8];
BYTE g_pucDpRx0Hdcp2Rrx[8];
BYTE g_pucDpRx0Hdcp2VPrime[20];

#if(_DP_TX_SUPPORT == _ON)
StructDpRxHdcp2AuthInfo g_stDpRx0Hdcp2AuthInfo;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpRx0Hdcp2Handler(void);
void ScalerDpRx0Hdcp2Handler_EXINT0(void);
BYTE ScalerDpRx0Hdcp2GetMessageID_EXINT0(void);
void ScalerDpRx0Hdcp2LoadCertRrxKey(void);
void ScalerDpRx0Hdcp2LoadDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray);
BYTE ScalerDpRx0Hdcp2MPrimeCalculate_EXINT0(void);
void ScalerDpRx0Hdcp2ResetProc(void);
void ScalerDpRx0Hdcp2ResetProc_EXINT0(void);
void ScalerDpRx0Hdcp2SetAESType_EXINT0(void);
void ScalerDpRx0Hdcp2SetDpcdReadValue_EXINT0(BYTE ucRSAType, BYTE *pucReadArray, WORD usLength);
void ScalerDpRx0Hdcp2ClearDpcdReadValue_EXINT0(BYTE ucRSAType, WORD usLength);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
void ScalerDpRx0Hdcp2AesOnlineCtrlErrata(BYTE *pucInputArray, BYTE *pucCipherArray);
BYTE ScalerDpRx0Hdcp2MPrimeCalculate(void);
#endif

bit ScalerDpRx0Hdcp2CaptureKpubKm(void);
void ScalerDpRx0Hdcp2CalculateKmKh(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx0Hdcp2SkeProc_WDINT(void);
void ScalerDpRx0Hdcp2LoadDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray);
#endif

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRx0Hdcp2RepeaterHandler(void);
void ScalerDpRx0Hdcp2ChangeAuthState(EnumDpRxHdcp2RepeaterAuthState enumHdcp2AuthState);
void ScalerDpRx0Hdcp2SetRepeaterProcTimeout(void);
bit ScalerDpRx0Hdcp2CheckRxInfo(void);
void ScalerDpRx0Hdcp2LoadReceiverIdList(void);
bit ScalerDpRx0Hdcp2VComputeProc(void);
bit ScalerDpRx0Hdcp2FakeAuthenProc(void);
void ScalerDpRx0Hdcp2RepeaterCapableProc(BYTE ucInputPort, BYTE ucPortType);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process for DP Rx0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2Handler(void)
{
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    SET_DP_RX0_HDCP2_AKE_INIT_RECEIVED();
#endif

    // Receiver Has Received AKE_INIT
    if(GET_DP_RX0_HDCP2_AKE_INIT_RECEIVED() == _TRUE)
    {
        CLR_DP_RX0_HDCP2_AKE_INIT_RECEIVED();

#if(_DP_TX_SUPPORT == _ON)
        if(GET_DP_RX0_HDCP2_REPEATER_CAPABLE() == _TRUE)
        {
            SET_DP_RX0_HDCP2_REPEATER_AUTH_1_START();
        }
#endif

        DebugMessageHDCP2("[D0]AKE_INIT", 0);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        // Reset HDCP Cipher
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, 0x00);
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

        g_pucDpRx0Hdcp2Rtx[0] = 0x18;
        g_pucDpRx0Hdcp2Rtx[1] = 0xfa;
        g_pucDpRx0Hdcp2Rtx[2] = 0xe4;
        g_pucDpRx0Hdcp2Rtx[3] = 0x20;
        g_pucDpRx0Hdcp2Rtx[4] = 0x6a;
        g_pucDpRx0Hdcp2Rtx[5] = 0xfb;
        g_pucDpRx0Hdcp2Rtx[6] = 0x51;
        g_pucDpRx0Hdcp2Rtx[7] = 0x49;

        g_pucDpRx0Hdcp2Rrx[0] = 0x3b;
        g_pucDpRx0Hdcp2Rrx[1] = 0xa0;
        g_pucDpRx0Hdcp2Rrx[2] = 0xbe;
        g_pucDpRx0Hdcp2Rrx[3] = 0xde;
        g_pucDpRx0Hdcp2Rrx[4] = 0x0c;
        g_pucDpRx0Hdcp2Rrx[5] = 0x46;
        g_pucDpRx0Hdcp2Rrx[6] = 0xa9;
        g_pucDpRx0Hdcp2Rrx[7] = 0x91;

        g_pucDpRx0Hdcp2TxCaps[0] = 0x02;
        g_pucDpRx0Hdcp2TxCaps[1] = 0x00;
        g_pucDpRx0Hdcp2TxCaps[2] = 0x00;

        g_pucDPRx0Caps[0] = 0x02;
        g_pucDPRx0Caps[1] = 0x00;
        g_pucDPRx0Caps[2] = 0x03;

        // Load Certrx to DPCD Table
        ScalerDpRx0Hdcp2LoadCertRrxKey();
#endif
    }

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    SET_DP_RX0_HDCP2_AKE_NO_STORED_KM_RECEIVED();
#endif

    // Receiver Has received AKE_NO_STORED_KM
    if(GET_DP_RX0_HDCP2_AKE_NO_STORED_KM_RECEIVED() == _TRUE)
    {
        if(ScalerDpRx0Hdcp2CaptureKpubKm() == _TRUE)
        {
            // Decrypt Km by FW to Get 128 bit Km
            if(ScalerHdcp2RxRsaOaepCalculate(g_pucDpRx0Hdcp2Km) == _TRUE)
            {
                ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_0, g_pucDpRx0Hdcp2Rtx, g_pucDpRx0Hdcp2Rrx, g_pucDpRx0Hdcp2Km, g_pucDpRx0Hdcp2Rn);

                memcpy(g_pucDpRx0Hdcp2dKey0, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

                ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_1, g_pucDpRx0Hdcp2Rtx, g_pucDpRx0Hdcp2Rrx, g_pucDpRx0Hdcp2Km, g_pucDpRx0Hdcp2Rn);

                memcpy(g_pucDpRx0Hdcp2dKey1, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                {
                    DebugMessageHDCP2("Dkey0", g_pucDpRx0Hdcp2dKey0[pData[0]]);
                }

                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                {
                    DebugMessageHDCP2("Dkey1", g_pucDpRx0Hdcp2dKey1[pData[0]]);
                }
#endif

                if(ScalerHdcp2HPrimeCalculate(g_pucDpRx0Hdcp2dKey0, g_pucDpRx0Hdcp2dKey1, g_pucDpRx0Hdcp2Rtx, g_pucDpRx0Hdcp2TxCaps, g_pucDPRx0Caps) == _TRUE)
                {
                    ScalerDpRx0Hdcp2CalculateKmKh();
                }
            }
        }
    }

    if(GET_DP_RX0_HDCP2_AKE_STORED_KM_RECEIVED() == _TRUE)
    {
        CLR_DP_RX0_HDCP2_AKE_STORED_KM_RECEIVED();
        CLR_DP_RX0_HDCP2_AUTHENTICATION_ACTIVE();

        DebugMessageHDCP2("[D0]AKE_STORED_KM", 0);
    }

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    SET_DP_RX0_HDCP2_LC_INIT_RECEIVED();
#endif

    if(GET_DP_RX0_HDCP2_LC_INIT_RECEIVED() == _TRUE)
    {
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        BYTE pucSHA256[32];
        memset(pucSHA256, 0, sizeof(pucSHA256));

        g_pucDpRx0Hdcp2Rn[0] = 0x32;
        g_pucDpRx0Hdcp2Rn[1] = 0x75;
        g_pucDpRx0Hdcp2Rn[2] = 0x3e;
        g_pucDpRx0Hdcp2Rn[3] = 0xa8;
        g_pucDpRx0Hdcp2Rn[4] = 0x78;
        g_pucDpRx0Hdcp2Rn[5] = 0xa6;
        g_pucDpRx0Hdcp2Rn[6] = 0x38;
        g_pucDpRx0Hdcp2Rn[7] = 0x1c;

        if(ScalerHdcp2LPrimeCalculate(g_pucDpRx0Hdcp2dKey0, g_pucDpRx0Hdcp2dKey1, g_pucDpRx0Hdcp2Rrx, g_pucDpRx0Hdcp2Rn) == _TRUE)
        {
            // Load L prime to pucSHA256
            memcpy(pucSHA256, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                DebugMessageHDCP2("L Prime", pucSHA256[pData[0]]);
            }
        }
#endif

        CLR_DP_RX0_HDCP2_LC_INIT_RECEIVED();

        DebugMessageHDCP2("[D0]LC_INIT", 0);
    }

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    SET_DP_RX0_HDCP2_SKE_SEND_EKS_RECEIVED();
#endif

    if(GET_DP_RX0_HDCP2_SKE_SEND_EKS_RECEIVED() == _TRUE)
    {
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        BYTE pucEDkeyKs[16];
        BYTE pucInputCipher[16];
        BYTE pucRiv[8];
        BYTE pucKs[16];

        memset(pucInputCipher, 0, sizeof(pucInputCipher));
        memset(pucKs, 0, sizeof(pucKs));

        // Calculate Dkey 2
        ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_2, g_pucDpRx0Hdcp2Rtx, g_pucDpRx0Hdcp2Rrx, g_pucDpRx0Hdcp2Km, g_pucDpRx0Hdcp2Rn);

        pucEDkeyKs[0] = 0x4c;
        pucEDkeyKs[1] = 0x32;
        pucEDkeyKs[2] = 0x47;
        pucEDkeyKs[3] = 0x12;
        pucEDkeyKs[4] = 0xc4;
        pucEDkeyKs[5] = 0xbe;
        pucEDkeyKs[6] = 0xc6;
        pucEDkeyKs[7] = 0x69;
        pucEDkeyKs[8] = 0x0a;
        pucEDkeyKs[9] = 0xc2;
        pucEDkeyKs[10] = 0x19;
        pucEDkeyKs[11] = 0x64;
        pucEDkeyKs[12] = 0xde;
        pucEDkeyKs[13] = 0x91;
        pucEDkeyKs[14] = 0xf1;
        pucEDkeyKs[15] = 0x83;

        pucRiv[0] = 0x40;
        pucRiv[1] = 0x2b;
        pucRiv[2] = 0x6b;
        pucRiv[3] = 0x43;
        pucRiv[4] = 0xc5;
        pucRiv[5] = 0xe8;
        pucRiv[6] = 0x86;
        pucRiv[7] = 0xd8;

        // Decode Ks
        for(pData[0] = 0; pData[0] < 8; ++pData[0])
        {
            pucKs[pData[0]] = pucEDkeyKs[pData[0]] ^ ScalerGetByte((P63_81_HDCP_AES_OUT_15 + pData[0]));
        }

        for(pData[0] = 8; pData[0] < 16; ++pData[0])
        {
            pucKs[pData[0]] = pucEDkeyKs[pData[0]] ^ (ScalerGetByte((P63_81_HDCP_AES_OUT_15 + pData[0])) ^ g_pucDpRx0Hdcp2Rrx[pData[0] - 8]);
        }

        for(pData[0] = 0; pData[0] < 16; pData[0]++)
        {
            DebugMessageHDCP2("Ks", pucKs[pData[0]]);
        }

        SET_DP_RX0_HDCP2_AUTHENTICATION_DONE();

        // Enable DP Link Integrity Check
        ScalerSetBit(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

        // Enable Decryption
        for(pData[0] = 0; pData[0] < 16; ++pData[0])
        {
            pucInputCipher[pData[0]] = pucKs[pData[0]] ^ g_stRxHdcp2DownLoadKeyType.pucHdcp2Lc[pData[0]];
        }

        // Enable AES Decryption Cipher
        ScalerDpRx0Hdcp2AesOnlineCtrlErrata(pucRiv, pucInputCipher);
#endif

        CLR_DP_RX0_HDCP2_SKE_SEND_EKS_RECEIVED();

#if(_DP_TX_SUPPORT == _ON)
        if(GET_DP_RX0_HDCP2_REPEATER_CAPABLE() == _TRUE)
        {
            SET_DP_RX0_HDCP2_REPEATER_AUTH_2_START();
        }
#endif

        DebugMessageHDCP2("[D0]SKE_SEND_EKS", 0);
    }

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    SET_DP_RX0_HDCP2_STREAM_MANAGE_RECEIVED();
#endif

    if(GET_DP_RX0_HDCP2_STREAM_MANAGE_RECEIVED() == _TRUE)
    {
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        // Get M Prime
        if(ScalerDpRx0Hdcp2MPrimeCalculate() == _TRUE)
        {
            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                g_pucHdcp2Sha256[pData[0]] = ScalerGetByte(P63_35_HDCP_SHA_0 + pData[0]);

                DebugMessageHDCP2("M prime", g_pucHdcp2Sha256[pData[0]]);
            }
        }
#endif

        CLR_DP_RX0_HDCP2_STREAM_MANAGE_RECEIVED();

#if(_DP_TX_SUPPORT == _ON)
        SET_DP_RX0_HDCP2_CONTENT_STREAM_MANAGEMENT();
#endif
    }
}
//--------------------------------------------------
// Description  : HDCP 2.2 Int Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2Handler_EXINT0(void) using 1
{
    BYTE ucMessageId = 0;

    // DP Global IRQ Flag
    if(ScalerGetBit_EXINT(PB7_DC_AUX_IRQ_STATUS, _BIT7) == _BIT7)
    {
        g_pucDpRx0Backup[0] = ScalerGetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H);
        g_pucDpRx0Backup[1] = ScalerGetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M);
        g_pucDpRx0Backup[2] = ScalerGetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L);

        // Get HDCP2.2 Message ID
        ucMessageId = ScalerDpRx0Hdcp2GetMessageID_EXINT0();

        if(ucMessageId == _HDCP_2_2_NONE)
        {
            ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, g_pucDpRx0Backup[0]);
            ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, g_pucDpRx0Backup[1]);
            ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, g_pucDpRx0Backup[2]);

            return;
        }
        else
        {
            // Switch HDCP to 2.2 Module from 1.4 Module
            if(GET_DP_RX0_HDCP_MODE_EXINT() == _HDCP_14)
            {
                // Enable HDCP 2.2 Module
                SET_DP_RX0_HDCP_MODE_EXINT(_HDCP_22);
            }
        }

        switch(ucMessageId)
        {
            case _HDCP_2_2_AKE_INIT:

                // HDCP2 Reset Proc
                ScalerDpRx0Hdcp2ResetProc_EXINT0();

                // Save Transmitter Rtx to FW (MSB located at index 0)
                ScalerDpRx0Hdcp2LoadDpcdValue_EXINT0(0x06, 0x90, 0x00, 8, g_pucDpRx0Hdcp2Rtx);

                // Save TxCaps to FW (MSB located at index 0)
                ScalerDpRx0Hdcp2LoadDpcdValue_EXINT0(0x06, 0x90, 0x08, 3, g_pucDpRx0Hdcp2TxCaps);

                // Generate the psudo-random key of Rrx
                ScalerHdcp2RxGenRrx_EXINT0(g_pucDpRx0Hdcp2Rrx);

                // Load Rrx to DPCD Table (MSB located at index 0)
                ScalerDpRx0Hdcp2SetDpcdReadValue_EXINT0(_HDCP_2_2_RRX, g_pucDpRx0Hdcp2Rrx, 8);

                ScalerDpRx0Hdcp2ClearDpcdReadValue_EXINT0(_HDCP_2_2_RX_H_PRIME, 32);
                ScalerDpRx0Hdcp2ClearDpcdReadValue_EXINT0(_HDCP_2_2_RX_L_PRIME, 32);
                ScalerDpRx0Hdcp2ClearDpcdReadValue_EXINT0(_HDCP_2_2_RX_M_PRIME, 32);
                ScalerDpRx0Hdcp2ClearDpcdReadValue_EXINT0(_HDCP_2_2_RX_PAIRING_INFO, 16);

#if(_DP_TX_SUPPORT == _ON)
                ScalerDpRx0HDCPResetDpcdInfo_EXINT0();
                ScalerDpRx0Hdcp2ClearDpcdReadValue_EXINT0(_HDCP_2_2_RX_V_PRIME, 190);
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_RX0_HDCP2_SKE);
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
                // Check if source doing HDCP handshake while HDCP capability disable
                if(ScalerDpRx0GetDpcdBitInfo_EXINT0(0x06, 0x92, 0x1F, _BIT1) == 0x00)
                {
                    SET_DP_RX0_HDCP_HANDSHAKE_WO_CAP();
                }
#endif

                SET_DP_RX0_HDCP2_AKE_INIT_RECEIVED();

                break;

            case _HDCP_2_2_AKE_NO_STORED_KM:

                SET_DP_RX0_HDCP2_AKE_NO_STORED_KM_RECEIVED();

                break;

            case _HDCP_2_2_AKE_SEND_PAIRING_INFO:

                // Start Pairing AES Calculate
                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    if(pData_EXINT[0] < 8)
                    {
                        g_pucHdcp2M[pData_EXINT[0]] = g_pucDpRx0Hdcp2Rtx[pData_EXINT[0]];
                    }
                    else
                    {
                        g_pucHdcp2M[pData_EXINT[0]] = g_pucDpRx0Hdcp2Rrx[pData_EXINT[0] - 8];
                    }
                }

                // AES Cipher Calculate Ekh[km]
                ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2M, g_pucHdcp2Kh);

                // Calculate Ekh[km] = kh AES m XOR Km
                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucHdcp2EkhKm[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]) ^ g_pucDpRx0Hdcp2Km[pData_EXINT[0]];
                }

                // Load Ekh_km prime to DPCD Table
                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    ScalerDpRx0SetDpcdValue_EXINT0(0x06, 0x92, (0xE0 + pData_EXINT[0]), g_pucHdcp2EkhKm[pData_EXINT[0]]);
                }

                // Doesn't Assert Pairing Available CPIRQ Before H Prime CPIRQ
                if(GET_DP_RX0_HDCP2_WAITING_H_PRIME_CPIRQ_ASSERTED() == _FALSE)
                {
                    // Set Pairing Available Flag
                    ScalerDpRx0CpIRQ_EXINT0(_DP_HDCP2_PARING_AVAILABLE);
                }
                else
                {
                    // Recoed Pairing Available CPIRQ Asserted Sataus
                    SET_DP_RX0_HDCP2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED();
                }

                break;

            case _HDCP_2_2_AKE_STORED_KM:

                // Save Ekh[km] From Transmitter to FW
                ScalerDpRx0Hdcp2LoadDpcdValue_EXINT0(0x06, 0x92, 0xA0, 16, g_pucDpRx0Hdcp2Km);

                // Save m From Transmitter to FW
                ScalerDpRx0Hdcp2LoadDpcdValue_EXINT0(0x06, 0x92, 0xB0, 16, g_pucHdcp2M);

                // Calculate Km use AES Cipher, Input Value = m, Input Cipher = Kh
                ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2M, g_pucHdcp2Kh);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucDpRx0Hdcp2Km[pData_EXINT[0]] = g_pucDpRx0Hdcp2Km[pData_EXINT[0]] ^ ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate DKey0
                ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_0, g_pucDpRx0Hdcp2Rtx, g_pucDpRx0Hdcp2Rrx, g_pucDpRx0Hdcp2Km, g_pucDpRx0Hdcp2Rn);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucDpRx0Hdcp2dKey0[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate Dkey1
                ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_1, g_pucDpRx0Hdcp2Rtx, g_pucDpRx0Hdcp2Rrx, g_pucDpRx0Hdcp2Km, g_pucDpRx0Hdcp2Rn);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucDpRx0Hdcp2dKey1[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate H'
                if(ScalerHdcp2HPrimeCalculate_EXINT0(g_pucDpRx0Hdcp2dKey0, g_pucDpRx0Hdcp2dKey1, g_pucDpRx0Hdcp2Rtx, g_pucDpRx0Hdcp2TxCaps, g_pucDPRx0Caps) == _TRUE)
                {
                    for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
                    {
                        g_pucHdcp2Sha256[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[0]);
                    }

                    // Load H prime to DPCD Table
                    ScalerDpRx0Hdcp2SetDpcdReadValue_EXINT0(_HDCP_2_2_RX_H_PRIME, g_pucHdcp2Sha256, 32);
                }

                ScalerDpRx0CpIRQ_EXINT0(_DP_HDCP2_H_PRIME_AVAILABLE);

                SET_DP_RX0_HDCP2_AKE_STORED_KM_RECEIVED();
                SET_DP_RX0_HDCP2_AUTHENTICATION_ACTIVE();

                break;

            case _HDCP_2_2_LC_INIT:

                // Save Transmitter Rn to FW
                ScalerDpRx0Hdcp2LoadDpcdValue_EXINT0(0x06, 0x92, 0xF0, 8, g_pucDpRx0Hdcp2Rn);

                if(ScalerHdcp2LPrimeCalculate_EXINT0(g_pucDpRx0Hdcp2dKey0, g_pucDpRx0Hdcp2dKey1, g_pucDpRx0Hdcp2Rrx, g_pucDpRx0Hdcp2Rn) == _TRUE)
                {
                    // Load L prime to g_pucHdcp2Sha256
                    for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
                    {
                        g_pucHdcp2Sha256[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[0]);
                    }

                    // Load L prime to DPCD Table
                    ScalerDpRx0Hdcp2SetDpcdReadValue_EXINT0(_HDCP_2_2_RX_L_PRIME, g_pucHdcp2Sha256, 32);
                }

                SET_DP_RX0_HDCP2_LC_INIT_RECEIVED();

                break;

            case _HDCP_2_2_SKE_SEND_EKS:

                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_RX0_HDCP2_SKE);

                // Execute Ske_Send_Eks Procedure after 4msec
                ScalerTimerWDActivateTimerEvent_EXINT0(4, _SCALER_WD_TIMER_EVENT_DP_RX0_HDCP2_SKE);

                break;

            case _HDCP_2_2_SKE_TYPE_VALUE:

                // Set AES Type
                if(ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x94, 0x94) == 0x00)
                {
                    // Type = 0x00
                    ScalerSetByte_EXINT(PB_93_HDCP_TYPE_AES_0, 0x00);
                }
                else
                {
                    // Disable HDCP2.2 Auth. Done for S8_TW issue
                    ScalerSetBit_EXINT(PB_20_HDCP_DEBUG, ~_BIT4, 0x00);

                    // Delay Time us [200, x]
                    for(pData_EXINT[0] = 0; pData_EXINT[0] < 40; pData_EXINT[0]++)
                    {
                        DELAY_5US_EXINT();
                    }

                    // Type = 0x01 or Type = 0x02 - 0xFF
                    ScalerSetByte_EXINT(PB_93_HDCP_TYPE_AES_0, 0x01);
                }

                // Enable HDCP2.2 Auth. Done
                ScalerSetBit_EXINT(PB_20_HDCP_DEBUG, ~_BIT4, _BIT4);

                SET_DP_RX0_HDCP2_AUTHENTICATION_DONE();

                break;

            case _HDCP_2_2_REPEATERAUTH_STREAM_MANAGE:

                // Get M Prime
                if(ScalerDpRx0Hdcp2MPrimeCalculate_EXINT0() == _TRUE)
                {
                    for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
                    {
                        g_pucHdcp2Sha256[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[0]);
                    }

                    // Load M prime to DPCD Table
                    ScalerDpRx0Hdcp2SetDpcdReadValue_EXINT0(_HDCP_2_2_RX_M_PRIME, g_pucHdcp2Sha256, 32);

                    // Set AES Type
                    ScalerDpRx0Hdcp2SetAESType_EXINT0();

                    // Enable HDCP2.2 Auth. Done
                    ScalerSetBit_EXINT(PB_20_HDCP_DEBUG, ~_BIT4, _BIT4);

                    SET_DP_RX0_HDCP2_AUTHENTICATION_DONE();

                    SET_DP_RX0_HDCP2_STREAM_MANAGE_RECEIVED();
                }

                break;

            default:
                break;
        }

        ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, g_pucDpRx0Backup[0]);
        ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, g_pucDpRx0Backup[1]);
        ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, g_pucDpRx0Backup[2]);
    }
}
//--------------------------------------------------
// Description  : Get HDCP 2.2 Message ID Code
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
BYTE ScalerDpRx0Hdcp2GetMessageID_EXINT0(void) using 1
{
    // Write Ake Initial
    if((ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A3, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A4, _BIT3) == _BIT3))
    {
        // CLR Flag
        ScalerSetByte_EXINT(_REG_DP_RX0_HDCP2_ADDR_A4, _BIT3);

        return _HDCP_2_2_AKE_INIT;
    }

    // Write AKE No Store Km
    if((ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A3, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A4, _BIT7) == _BIT7))
    {
        // CLR Flag
        ScalerSetByte_EXINT(_REG_DP_RX0_HDCP2_ADDR_A4, _BIT7);

        return _HDCP_2_2_AKE_NO_STORED_KM;
    }

    // Read HPrime
    if((ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_FB, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_FB, _BIT5) == _BIT5))
    {
        // Disable INT
        ScalerSetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), 0x00);

        // CLR Flag
        ScalerSetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT5);

        return _HDCP_2_2_AKE_SEND_PAIRING_INFO;
    }

    // Write AKE Store Km
    if((ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A3, _BIT6) == _BIT6) && (ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A4, _BIT6) == _BIT6))
    {
        // CLR Flag
        ScalerSetByte_EXINT(_REG_DP_RX0_HDCP2_ADDR_A4, _BIT6);

        return _HDCP_2_2_AKE_STORED_KM;
    }

    // Write Locality Check Initial
    if((ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A3, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A4, _BIT4) == _BIT4))
    {
        // CLR Flag
        ScalerSetByte_EXINT(_REG_DP_RX0_HDCP2_ADDR_A4, _BIT4);

        return _HDCP_2_2_LC_INIT;
    }

    // Write SEK Send
    if((ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A5, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A5, _BIT0) == _BIT0))
    {
        // CLR Flag
        ScalerSetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A5, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

        return _HDCP_2_2_SKE_SEND_EKS;
    }

    // Write Cipher Type
    if((ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A5, _BIT5) == _BIT5) && (ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A5, _BIT1) == _BIT1))
    {
        // CLR Flag
        ScalerSetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A5, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        return _HDCP_2_2_SKE_TYPE_VALUE;
    }

    // Write Stream ID Type
    if((ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A3, _BIT5) == _BIT5) && (ScalerGetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A4, _BIT5) == _BIT5))
    {
        // CLR Flag
        ScalerSetByte_EXINT(_REG_DP_RX0_HDCP2_ADDR_A4, _BIT5);

        return _HDCP_2_2_REPEATERAUTH_STREAM_MANAGE;
    }

    return _HDCP_2_2_NONE;
}
//--------------------------------------------------
// Description  : HDCP 2.2 Load Certificate Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2LoadCertRrxKey(void)
{
    for(PDATA_WORD(0) = 0; PDATA_WORD(0) < 522; PDATA_WORD(0)++)
    {
        PDATA_WORD(1) = 0x900B + PDATA_WORD(0);

        ScalerDpRx0SetDpcdValue(0x06, pData[2], pData[3], g_stRxHdcp2DownLoadKeyType.pucHdcp2Certrx[PDATA_WORD(0)]);
    }
}
//--------------------------------------------------
// Description  : HDCP 2.2 Down Load Value in INT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                usLength == > Length,
//                pReadArray == > Key Array
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2LoadDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray) using 1
{
    pData_EXINT[2] = ucDpcdAccessPortM;
    pData_EXINT[3] = ucDpcdAccessPortL;

    // Load Value To FW
    for(pData_EXINT[0] = 0; pData_EXINT[0] < ucLength; pData_EXINT[0]++)
    {
        pucReadArray[pData_EXINT[0]] = ScalerDpRx0GetDpcdInfo_EXINT0(ucDpcdAccessPortH, pData_EXINT[2], pData_EXINT[3]);

        PDATA_WORD_EXINT(1) = PDATA_WORD_EXINT(1) + 1;
    }
}
//--------------------------------------------------
// Description  : Get M Prime
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpRx0Hdcp2MPrimeCalculate_EXINT0(void) using 1
{
    BYTE pucSHA256Input[64];
    memset(pucSHA256Input, 0, sizeof(pucSHA256Input));

    // Get kd
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 64; pData_EXINT[0]++)
    {
        if(pData_EXINT[0] < 16)
        {
            pucSHA256Input[pData_EXINT[0]] = g_pucDpRx0Hdcp2dKey0[pData_EXINT[0]];
        }
        else if(pData_EXINT[0] < 32)
        {
            pucSHA256Input[pData_EXINT[0]] = g_pucDpRx0Hdcp2dKey1[pData_EXINT[0] - 16];
        }
        else
        {
            pucSHA256Input[pData_EXINT[0]] = 0;
        }
    }

    pucSHA256Input[32] = 0x80;
    pucSHA256Input[62] = 0x01;

    // Get SHA256(kd)
    if(ScalerHdcp2RxSha256Calculate_EXINT0(pucSHA256Input, 0) == _TRUE)
    {
        for(pData_EXINT[0] = 0; pData_EXINT[0] < 64; pData_EXINT[0]++)
        {
            if(pData_EXINT[0] < 32)
            {
                g_pucHdcp2HmacSha256CipherInput[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[0]);
            }
            else
            {
                g_pucHdcp2HmacSha256CipherInput[pData_EXINT[0]] = 0;
            }
        }
    }

    // Get # of StreamID_Type Length, StreamID_Type = stream_ID1 || Type || stream_ID2 || Type || .....
    pData_EXINT[1] = ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x93, 0xF4) * 2;

    // Stuff streamID_Type
    for(pData_EXINT[0] = 0; pData_EXINT[0] < pData_EXINT[1]; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256Input[pData_EXINT[0]] = ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x93, 0xF5 + pData_EXINT[0]);
    }

    // Stuff seq_num_M
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 3; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256Input[pData_EXINT[1] + pData_EXINT[0]] = ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x93, (0xF0 + pData_EXINT[0]));
    }

    g_pucHdcp2HmacSha256Input[pData_EXINT[1] + 3] = 0x80;

    for(pData_EXINT[0] = pData_EXINT[1] + 4; pData_EXINT[0] < 64; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256Input[pData_EXINT[0]] = 0;
    }

    // 8 * (StreamID_Type + seq_num_M + SHA256(kd))
    PDATA_WORD_EXINT(1) = 8 * (pData_EXINT[1] + 3 + 64);

    g_pucHdcp2HmacSha256Input[62] = pData_EXINT[2];
    g_pucHdcp2HmacSha256Input[63] = pData_EXINT[3];

    if(ScalerHdcp2RxHmacSha256Calculate_EXINT0(g_pucHdcp2HmacSha256Input, g_pucHdcp2HmacSha256CipherInput) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2ResetProc(void)
{
#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    if(GET_REG_DP_RX0_MAC_ASSIGNED() == _TRUE)
#endif
    {
        // Disable HDCP2.2 Auth. Done
        ScalerSetBit(PB_20_HDCP_DEBUG, ~_BIT4, 0x00);

        // Clear Type Value
        ScalerSetByte(PB_93_HDCP_TYPE_AES_0, 0x00);

        // Clear AES STx Type
#if(_HW_DP_RX_HDCP2_ONLINE_AES_COUNT == _DP_RX_HDCP2_ONLINE_AES_2SET)
        ScalerSetBit(PB_95_HDCP_ST_TYPE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
#endif

        // Reset HDCP Block
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

        // Disable HDCP2.2
        SET_DP_RX0_HDCP_MODE(_HDCP_14);
    }

    // Disable Type INT
    ScalerSetBit(_REG_DP_RX0_HDCP2_ADDR_A5, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);

    SET_DP_RX0_AUX_MANUAL_MODE();

    // Reset 69494h Type Value. Be Careful. If Clear this Address which is Writed by Source, Must Disable INT Function First.
    ScalerDpRx0SetDpcdValue(0x06, 0x94, 0x94, 0x00);

    SET_DP_RX0_AUX_AUTO_MODE();

    // Clear Type INT Flag
    ScalerSetBit(_REG_DP_RX0_HDCP2_ADDR_A5, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Enable Type INT
    ScalerSetBit(_REG_DP_RX0_HDCP2_ADDR_A5, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), _BIT5);

    // Disable Read DPCD 692DFh(HPrime) INT
    ScalerSetBit(_REG_DP_RX0_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), 0x00);

    // Clear Read DPCD 692DF(HPrime) INT Flag
    ScalerSetBit(_REG_DP_RX0_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT5);

    // Clear RxStatus REAUTH_REQ
    ScalerDpRx0SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx0GetDpcdInfo(0x06, 0x94, 0x93) & 0xE0));

    CLR_DP_RX0_HDCP2_AUTHENTICATION_DONE();
    CLR_DP_RX0_HDCP2_AKE_INIT_RECEIVED();
    CLR_DP_RX0_HDCP2_AKE_NO_STORED_KM_RECEIVED();
    CLR_DP_RX0_HDCP2_AKE_STORED_KM_RECEIVED();
    CLR_DP_RX0_HDCP2_LC_INIT_RECEIVED();
    CLR_DP_RX0_HDCP2_SKE_SEND_EKS_RECEIVED();
    CLR_DP_RX0_HDCP2_AUTHENTICATION_ACTIVE();

#if(_DP_TX_SUPPORT == _ON)
    CLR_DP_RX0_HDCP2_REPEATER_AUTH_1_START();
    CLR_DP_RX0_HDCP2_REPEATER_AUTH_2_START();
#endif
}
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2ResetProc_EXINT0(void) using 1
{
#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    if(GET_REG_DP_RX0_MAC_ASSIGNED_EXINT() == _TRUE)
#endif
    {
        // Disable HDCP2.2 Auth. Done
        ScalerSetBit_EXINT(PB_20_HDCP_DEBUG, ~_BIT4, 0x00);

        // Clear Type Value
        ScalerSetByte_EXINT(PB_93_HDCP_TYPE_AES_0, 0x00);

        // Clear AES STx Type
#if(_HW_DP_RX_HDCP2_ONLINE_AES_COUNT == _DP_RX_HDCP2_ONLINE_AES_2SET)
        ScalerSetBit_EXINT(PB_95_HDCP_ST_TYPE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
#endif
    }

    // Disable Type INT
    ScalerSetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A5, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Reset 69494h Type Value. Be Careful. If Clear this Address which is Writed by Source, Must Disable INT Function First.
    ScalerDpRx0SetDpcdValue_EXINT0(0x06, 0x94, 0x94, 0x00);

    // Clear Type INT Flag
    ScalerSetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A5, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Enable Type INT
    ScalerSetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_A5, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), _BIT5);

    // Disable Read DPCD 692DFh(HPrime) INT
    ScalerSetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), 0x00);

    // Clear Read DPCD 692DF(HPrime) INT Flag
    ScalerSetBit_EXINT(_REG_DP_RX0_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT5);

    // Clear RxStatus REAUTH_REQ and Link Intergrity Failure for HDCP 2.2
    ScalerDpRx0SetDpcdValue_EXINT0(0x06, 0x94, 0x93, (ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x94, 0x93) & 0xE0));

    // Clear Bstatus REAUTH_REQ and Link Intergrity Failure for HDCP 1.4
    ScalerDpRx0SetDpcdValue_EXINT0(0x06, 0x80, 0x29, (ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x80, 0x29) & 0xF0));

    CLR_DP_RX0_HDCP2_AUTHENTICATION_DONE();
    CLR_DP_RX0_HDCP2_AKE_INIT_RECEIVED();
    CLR_DP_RX0_HDCP2_AKE_NO_STORED_KM_RECEIVED();
    CLR_DP_RX0_HDCP2_AKE_STORED_KM_RECEIVED();
    CLR_DP_RX0_HDCP2_LC_INIT_RECEIVED();
    CLR_DP_RX0_HDCP2_SKE_SEND_EKS_RECEIVED();
    CLR_DP_RX0_HDCP2_AUTHENTICATION_ACTIVE();

#if(_DP_TX_SUPPORT == _ON)
    CLR_DP_RX0_HDCP2_REPEATER_AUTH_1_START();
    CLR_DP_RX0_HDCP2_REPEATER_AUTH_2_START();
#endif
}

//--------------------------------------------------
// Description  : Set AES Type
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpRx0Hdcp2SetAESType_EXINT0(void) using 1
{
    // StreamID = 0 for SST Case
    if(ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x93, 0xF5) == 0x00)
    {
        // Set AES Type
        if(ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x93, 0xF6) == 0x00)
        {
            // Type = 0x00
            ScalerSetByte_EXINT(_REG_DP_RX0_HDCP2_TYPE_AES0_VALUE, 0x00);
        }
        else
        {
            // Type = 0x01 or Type = 0x02 - 0xFF
            ScalerSetByte_EXINT(_REG_DP_RX0_HDCP2_TYPE_AES0_VALUE, 0x01);
        }
    }
#if((_DP_MST_SUPPORT == _ON) && (_HW_DP_RX_HDCP2_ONLINE_AES_COUNT == _DP_RX_HDCP2_ONLINE_AES_2SET))
    else
    {
        // Get # of Stream
        pData_EXINT[3] = ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x93, 0xF4);

        // Set STx AES Type
        for(pData_EXINT[0] = 0; pData_EXINT[0] < pData_EXINT[3]; pData_EXINT[0]++)
        {
            for(pData_EXINT[1] = 0; pData_EXINT[1] < 5; pData_EXINT[1]++)
            {
                if(g_pucDpStreamToIdMapping[pData_EXINT[1]] == ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x93, 0xF5 + (2 * pData_EXINT[0])))
                {
                    pData_EXINT[2] = ScalerDpRx0GetDpcdInfo_EXINT0(0x06, 0x93, 0xF5 + (2 * pData_EXINT[0]) + 1);

                    if(pData_EXINT[2] == 0x00)
                    {
                        // Type = 0x00
                        ScalerSetBit_EXINT(PB_95_HDCP_ST_TYPE, ~(_BIT7 >> pData_EXINT[1]), 0x00);
                    }
                    else
                    {
                        // Type = 0x01 or Type = 0x02 - 0xFF
                        ScalerSetBit_EXINT(PB_95_HDCP_ST_TYPE, ~(_BIT7 >> pData_EXINT[1]), (_BIT7 >> pData_EXINT[1]));
                    }
                }
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Download HDCP Receiver Public Key Certificate
// Input Value  : Public Key / Write Length
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2SetDpcdReadValue_EXINT0(BYTE ucRSAType, BYTE *pucReadArray, WORD usLength) using 1
{
    switch(ucRSAType)
    {
        case _HDCP_2_2_RRX:

            pData_EXINT[1] = 0x06;
            pData_EXINT[2] = 0x92;
            pData_EXINT[3] = 0x15;

            break;

        case _HDCP_2_2_RX_H_PRIME:

            pData_EXINT[1] = 0x06;
            pData_EXINT[2] = 0x92;
            pData_EXINT[3] = 0xC0;

            break;

        case _HDCP_2_2_RX_L_PRIME:

            pData_EXINT[1] = 0x06;
            pData_EXINT[2] = 0x92;
            pData_EXINT[3] = 0xF8;

            break;

        case _HDCP_2_2_RX_M_PRIME:

            pData_EXINT[1] = 0x06;
            pData_EXINT[2] = 0x94;
            pData_EXINT[3] = 0x73;

            break;

        default:

            return;
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < usLength; pData_EXINT[0]++)
    {
        ScalerDpRx0SetDpcdValue_EXINT0(pData_EXINT[1], pData_EXINT[2], pData_EXINT[3], pucReadArray[pData_EXINT[0]]);
        PDATA_WORD_EXINT(1) = PDATA_WORD_EXINT(1) + 1;
    }
}

//--------------------------------------------------
// Description  : Clear HDCP Receiver Public Key Certificate
// Input Value  : Public Key / Write Length
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2ClearDpcdReadValue_EXINT0(BYTE ucRSAType, WORD usLength) using 1
{
    switch(ucRSAType)
    {
        case _HDCP_2_2_RRX:

            pData_EXINT[1] = 0x06;
            pData_EXINT[2] = 0x92;
            pData_EXINT[3] = 0x15;

            break;

        case _HDCP_2_2_RX_H_PRIME:

            pData_EXINT[1] = 0x06;
            pData_EXINT[2] = 0x92;
            pData_EXINT[3] = 0xC0;

            break;

        case _HDCP_2_2_RX_PAIRING_INFO:

            pData_EXINT[1] = 0x06;
            pData_EXINT[2] = 0x92;
            pData_EXINT[3] = 0xE0;

            break;

        case _HDCP_2_2_RX_L_PRIME:

            pData_EXINT[1] = 0x06;
            pData_EXINT[2] = 0x92;
            pData_EXINT[3] = 0xF8;

            break;

        case _HDCP_2_2_RX_M_PRIME:

            pData_EXINT[1] = 0x06;
            pData_EXINT[2] = 0x94;
            pData_EXINT[3] = 0x73;

            break;

        case _HDCP_2_2_RX_V_PRIME:

            pData_EXINT[1] = 0x06;
            pData_EXINT[2] = 0x93;
            pData_EXINT[3] = 0x32;

            break;

        default:

            return;
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < usLength; pData_EXINT[0]++)
    {
        ScalerDpRx0SetDpcdValue_EXINT0(pData_EXINT[1], pData_EXINT[2], pData_EXINT[3], 0x00);
        PDATA_WORD_EXINT(1) = PDATA_WORD_EXINT(1) + 1;
    }
}

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 On-Line AES Ctrl
// Input Value  : *pucInputArray, *pucCipherArray
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2AesOnlineCtrlErrata(BYTE *pucInputArray, BYTE *pucCipherArray)
{
    memcpy((volatile BYTE xdata *)PB_81_HDCP_AES_CIPHER_KEY_15, pucCipherArray, 16);
    memcpy((volatile BYTE xdata *)PB_55_RIV0, pucInputArray, 8);
}

//--------------------------------------------------
// Description  : Get M Prime
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpRx0Hdcp2MPrimeCalculate(void)
{
    BYTE pucSHA256Input[64];
    BYTE pucKd[32];

    memset(pucSHA256Input, 0, sizeof(pucSHA256Input));

    pucKd[0] = 0x4f;
    pucKd[1] = 0x14;
    pucKd[2] = 0x8d;
    pucKd[3] = 0x11;
    pucKd[4] = 0xdd;
    pucKd[5] = 0x49;
    pucKd[6] = 0x18;
    pucKd[7] = 0x10;
    pucKd[8] = 0x6f;
    pucKd[9] = 0xab;
    pucKd[10] = 0x16;
    pucKd[11] = 0x6f;
    pucKd[12] = 0xf6;
    pucKd[13] = 0xfd;
    pucKd[14] = 0xa6;
    pucKd[15] = 0xed;
    pucKd[16] = 0xb5;
    pucKd[17] = 0x02;
    pucKd[18] = 0x0c;
    pucKd[19] = 0x0d;
    pucKd[20] = 0xf2;
    pucKd[21] = 0x81;
    pucKd[22] = 0xba;
    pucKd[23] = 0xdf;
    pucKd[24] = 0xe4;
    pucKd[25] = 0x19;
    pucKd[26] = 0x77;
    pucKd[27] = 0xfa;
    pucKd[28] = 0xd0;
    pucKd[29] = 0xac;
    pucKd[30] = 0x61;
    pucKd[31] = 0x17;

    // Get kd
    for(pData[0] = 0; pData[0] < 64; pData[0]++)
    {
        if(pData[0] < 32)
        {
            pucSHA256Input[pData[0]] = pucKd[pData[0]];
        }
        else
        {
            pucSHA256Input[pData[0]] = 0;
        }
    }

    pucSHA256Input[32] = 0x80;
    pucSHA256Input[62] = 0x01;

    // Get SHA256(kd)
    if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 0) == _TRUE)
    {
        for(pData[0] = 0; pData[0] < 64; pData[0]++)
        {
            if(pData[0] < 32)
            {
                g_pucHdcp2HmacSha256CipherInput[pData[0]] = ScalerGetByte(P63_35_HDCP_SHA_0 + pData[0]);
            }
            else
            {
                g_pucHdcp2HmacSha256CipherInput[pData[0]] = 0;
            }
        }
    }

    for(pData[0] = 0; pData[0] < 64; pData[0]++)
    {
        DebugMessageHDCP2("SHA256(kd)", g_pucHdcp2HmacSha256CipherInput[pData[0]]);
    }

    // StreamID
    g_pucHdcp2HmacSha256Input[0] = 0x00;

    // Type
    g_pucHdcp2HmacSha256Input[1] = 0x01;

    // Stuff seq_num_M
    g_pucHdcp2HmacSha256Input[2] = 0x00;
    g_pucHdcp2HmacSha256Input[3] = 0x00;
    g_pucHdcp2HmacSha256Input[4] = 0x00;

    g_pucHdcp2HmacSha256Input[5] = 0x80;

    for(pData[0] = 6; pData[0] < 64; pData[0]++)
    {
        g_pucHdcp2HmacSha256Input[pData[0]] = 0;
    }

    // 8 * ( StreamID_Type + seq_M + Kd )
    PDATA_WORD(1) = 8 * (2 + 3 + 64);

    g_pucHdcp2HmacSha256Input[62] = pData[2];
    g_pucHdcp2HmacSha256Input[63] = pData[3];

    if(ScalerHdcp2RxHmacSha256Calculate(g_pucHdcp2HmacSha256Input, g_pucHdcp2HmacSha256CipherInput) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif // End of #if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Capture Kpub/Km
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpRx0Hdcp2CaptureKpubKm(void)
{
    BYTE pucKpubKm[128];
    memset(pucKpubKm, 0, sizeof(pucKpubKm));

    CLR_DP_RX0_HDCP2_AKE_NO_STORED_KM_RECEIVED();

    DebugMessageHDCP2("[D0]AKE_NO_STORED_KM", 0);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    for(pData[0] = 0; pData[0] < 128; pData[0]++)
    {
        pucKpubKm[pData[0]] = g_stRxHdcp2DownLoadKeyType.pucHdcp2KpubKm[pData[0]];

        DebugMessageHDCP2("[D0]Ekpub(km)", pucKpubKm[pData[0]]);
    }
#else
    // Save Transmitter Ekpub[km] to FW
    for(pData[0] = 0; pData[0] < 128; pData[0]++)
    {
        pucKpubKm[pData[0]] = ScalerDpRx0GetDpcdInfo(0x06, 0x92, (0x20 + pData[0]));
    }
#endif

    // Decrypt Ekpub[km]
    return (ScalerHdcp2RxRsaCalculate(pucKpubKm) == _TRUE);
}

//--------------------------------------------------
// Description  : Load H_Prime and Calculate Pairing
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2CalculateKmKh(void)
{
    BYTE pucSHA256[32];

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    BYTE pucM[16];
    memset(pucM, 0, sizeof(pucM));
#endif
    memset(pucSHA256, 0, sizeof(pucSHA256));

    // Load H prime to pucSHA256
    memcpy(pucSHA256, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    for(pData[0] = 0; pData[0] < 32; pData[0]++)
    {
        DebugMessageHDCP2("H prime", pucSHA256[pData[0]]);
    }
#endif

    SET_DP_RX0_AUX_MANUAL_MODE();

    // Load H prime to DPCD Table
    for(pData[0] = 0; pData[0] < 32; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x92, (0xC0 + pData[0]), pucSHA256[pData[0]]);
    }

    // Initialize Waiting To Assert H Prime_CPIRQ To Check if H' Is Read By Source Before CPIRQ With H Pirme Available Is Asserted
    SET_DP_RX0_HDCP2_WAITING_H_PRIME_CPIRQ_ASSERTED();

    // Initialize Pairing Available CPIRQ Flag To Record Pairing Available CPIRQ Asserted Status
    CLR_DP_RX0_HDCP2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED();

    // Clear Read DPCD 692DF(HPrime) INT Flag
    ScalerSetBit(_REG_DP_RX0_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT5);

    // Enable Read DPCD 692DFh(HPrime) INT
    ScalerSetBit(_REG_DP_RX0_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT4);

    SET_DP_RX0_AUX_AUTO_MODE();

    // Set H Prime Available Flag
    ScalerDpRx0CpIRQ(_DP_HDCP2_H_PRIME_AVAILABLE);

    // Clear H Prime Available CPIRQ Status
    CLR_DP_RX0_HDCP2_WAITING_H_PRIME_CPIRQ_ASSERTED();

    // Assert Pairing Available CPIRQ If No Asserting in Pairing Info INT State
    if(GET_DP_RX0_HDCP2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED() == _TRUE)
    {
        // Clear Pairing Available CPIRQ Status
        CLR_DP_RX0_HDCP2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED();

        // Set Pairing Available Flag
        ScalerDpRx0CpIRQ(_DP_HDCP2_PARING_AVAILABLE);
    }

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    // Start Pairing AES Calculate
    for(pData[0] = 0; pData[0] < 16; ++pData[0])
    {
        if(pData[0] < 8)
        {
            pucM[pData[0]] = g_pucDpRx0Hdcp2Rtx[pData[0]];
        }
        else
        {
            pucM[pData[0]] = g_pucDpRx0Hdcp2Rrx[pData[0] - 8];
        }
    }

    // AES Cipher Calculate Ekh[km]
    ScalerHdcp2RxAesOfflineCtrl(pucM, g_pucHdcp2Kh);

    // Calculate Ekh[km] = kh AES m XOR Km
    for(pData[0] = 0; pData[0] < 16; ++pData[0])
    {
        g_pucHdcp2Kh[pData[0]] = ScalerGetByte(P63_81_HDCP_AES_OUT_15 + pData[0]) ^ g_pucDpRx0Hdcp2Km[pData[0]];

        DebugMessageHDCP2("g_ucHdcp2Kh", g_pucHdcp2Kh[pData[0]]);
    }
#endif
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : WD Timer Event Proc of DP RX0 HDCP2 SKE Proc
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2SkeProc_WDINT(void) using 3
{
    // Calculate Dkey 2
    ScalerHdcp2DkeyCalculate_WDINT(_HDCP_2_2_DKEY_2, g_pucDpRx0Hdcp2Rtx, g_pucDpRx0Hdcp2Rrx, g_pucDpRx0Hdcp2Km, g_pucDpRx0Hdcp2Rn);

    // Save Edkey_ks to g_pucHdcp2EDkeyKs
    ScalerDpRx0Hdcp2LoadDpcdValue_WDINT(0x06, 0x93, 0x18, 16, g_pucHdcp2EDkeyKs);

    // Save Riv to g_pucHdcp2Riv
    ScalerDpRx0Hdcp2LoadDpcdValue_WDINT(0x06, 0x93, 0x28, 8, g_pucHdcp2Riv);

    // Decode Ks
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; ++pData_EXINT[0])
    {
        g_pucHdcp2Ks[pData_EXINT[0]] = g_pucHdcp2EDkeyKs[pData_EXINT[0]] ^ ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]));
    }

    for(pData_EXINT[0] = 8; pData_EXINT[0] < 16; ++pData_EXINT[0])
    {
        g_pucHdcp2Ks[pData_EXINT[0]] = g_pucHdcp2EDkeyKs[pData_EXINT[0]] ^ (ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + pData_EXINT[0])) ^ g_pucDpRx0Hdcp2Rrx[pData_EXINT[0] - 8]);
    }

    // Enable DP Link Integrity Check
    ScalerSetBit_EXINT(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

    // Enable Decryption
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        g_pucHdcp2InputCipher[pData_EXINT[0]] = g_pucHdcp2Ks[pData_EXINT[0]] ^ g_stRxHdcp2DownLoadKeyType.pucHdcp2Lc[pData_EXINT[0]];

        ScalerSetByte_EXINT(PB_81_HDCP_AES_CIPHER_KEY_15 + pData_EXINT[0], g_pucHdcp2InputCipher[pData_EXINT[0]]);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
    {
        ScalerSetByte_EXINT(PB_55_RIV0 + pData_EXINT[0], g_pucHdcp2Riv[pData_EXINT[0]]);
    }

    // Solve Mute Issue For S8_TW Which Has Not Sent Type Value After SKE
    if(ScalerDpRx0GetDpcdBitInfo_WDINT(0x06, 0x92, 0x1F, (_BIT1 | _BIT0)) == _BIT1)
    {
        // Enable HDCP2.2 Auth. Done
        ScalerSetBit_EXINT(PB_20_HDCP_DEBUG, ~_BIT4, _BIT4);

        SET_DP_RX0_HDCP2_AUTHENTICATION_DONE();
    }

    SET_DP_RX0_HDCP2_SKE_SEND_EKS_RECEIVED();
}

//--------------------------------------------------
// Description  : HDCP 2.2 Down Load Value in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                usLength == > Length,
//                pReadArray == > Key Array
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2LoadDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray) using 3
{
    BYTE ucIndex = 0x00;
    WORD usDpcdAddress = 0;

    usDpcdAddress = (((WORD)ucDpcdAccessPortM << 8) | ((WORD)ucDpcdAccessPortL));

    // Load Value To FW
    for(ucIndex = 0; ucIndex < ucLength; ucIndex++)
    {
        pucReadArray[ucIndex] = ScalerDpRx0GetDpcdInfo_WDINT(ucDpcdAccessPortH, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress));

        usDpcdAddress = usDpcdAddress + 1;
    }
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2RepeaterHandler(void)
{
    if(GET_DP_RX0_HDCP2_MODE() == _ENABLE)
    {
        if(GET_DP_RX0_HDCP2_REPEATER_CAPABLE() == _TRUE)
        {
            if(GET_DP_RX0_HDCP2_REPEATER_AUTH_1_START() == _TRUE)
            {
                DebugMessageHDCP2("DPRX0 HDCP2 - Get AKE INIT", 0);

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP2_CPIRQ_EVENT);

                CLR_DP_RX0_HDCP2_AUTH_CPIRQ_TIMRE();

                ScalerDpRx0Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_IDLE);
            }

            if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT)
            {
                // For MST mode
                if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT0) == _BIT0)
                {
                    if((ScalerDpRx0HdcpCheckValid() == _TRUE) && (GET_DP_RX0_HDCP2_AUTH_CPIRQ_TIMRE() == _FALSE))
                    {
                        if(ScalerDpRx0HDCPCheckLvp() == _FALSE)
                        {
                            SET_DP_RX0_HDCP2_AUTH_CPIRQ_TIMRE();

                            ScalerDpRx0CpIRQ(_DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

                            ScalerTimerActiveTimerEvent(SEC(0.02), _SCALER_TIMER_EVENT_DP_RX0_HDCP2_CPIRQ_EVENT);
                        }
                    }
                }
                else
                {
                    // In SST mode, issue HPD event for upstream device if DPTX connect a new downstream device.
                    if((GET_DP_RX0_HDCP2_AUTH_STATE() != _DP_RX_HDCP2_REPEATER_STATE_IDLE) &&
                       (ScalerDpRx0HdcpCheckValid() == _TRUE))
                    {
                        if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                        {
                            if(GET_DP_TX_HDCP2_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_REAUTH)
                            {
                                ScalerDpRx0SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
                            }
                        }
                        else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                        {
                            if(GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH)
                            {
                                ScalerDpRx0SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
                            }
                        }
                    }
                }
            }

            if((GET_DP_RX0_HDCP2_AUTH_STATE() != _DP_RX_HDCP2_REPEATER_STATE_IDLE) && (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE))
            {
                ScalerDpRx0Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_IDLE);
            }
        }
    }

    switch(GET_DP_RX0_HDCP2_AUTH_STATE())
    {
        case _DP_RX_HDCP2_REPEATER_STATE_IDLE:

            if(GET_DP_RX0_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX0_HDCP2_AUTH_STATE_CHANGE();
                CLR_DP_RX0_HDCP2_AUTH_REPEATER_PROC_TIMEOUT();
                CLR_DP_RX0_HDCP2_AUTH_CPIRQ_TIMRE();
                CLR_DP_RX0_HDCP2_CONTENT_STREAM_MANAGEMENT();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP2_REPEATER_PROC_TIMEOUT);

                SET_DP_RX0_HDCP2_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION);
            }

            if((GET_DP_RX0_HDCP2_MODE() == _ENABLE) && (GET_DP_RX0_HDCP2_REPEATER_CAPABLE() == _TRUE))
            {
                if(GET_DP_RX0_HDCP2_REPEATER_AUTH_1_START() == _TRUE)
                {
                    CLR_DP_RX0_HDCP2_REPEATER_AUTH_1_START();

                    ScalerDpRx0Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_1);
                }
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_1:

            if(GET_DP_RX0_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX0 HDCP2 - Auth 1", 0);

                CLR_DP_RX0_HDCP2_AUTH_STATE_CHANGE();

                if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT)
                {
                    // Check if downstream device support HDCP2 capability.
                    if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                    {
                        DebugMessageHDCP2("DPRX0 HDCP2 - To DPTX HDCP2", 0);

                        // Issue event to make DPTX start HDCP2 handshake.
                        SET_DP_RX0_HDCP2_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX0_HDCP2_REPEATER_PROC_TIMEOUT);
                    }
                    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                    {
                        DebugMessageHDCP2("DPRX0 HDCP2 - To DPTX HDCP1", 0);

                        // Issue event to make DPTX start HDCP handshake.
                        SET_DP_RX0_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX0_HDCP2_REPEATER_PROC_TIMEOUT);
                    }
                    else
                    {
                        ScalerDpRx0Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_2);
                    }
                }
                else
                {
                    ScalerDpRx0Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_FAKE);
                }
            }

            // Wait for downstream pass event or device/depth max event
            if((GET_DP_TX_HDCP2_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PASS) ||
               (GET_DP_TX_HDCP2_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_EXCEED) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX))
            {
                DebugMessageHDCP2("DPRX0 HDCP2 - TX PASS", 0);

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP2_REPEATER_PROC_TIMEOUT);

                ScalerDpRx0Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_2);
            }
            else if(GET_DP_RX0_HDCP2_AUTH_REPEATER_PROC_TIMEOUT() == _TRUE)
            {
                CLR_DP_RX0_HDCP2_AUTH_REPEATER_PROC_TIMEOUT();

                if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                {
                    SET_DP_RX0_HDCP2_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_TIMEOUT);
                }
                else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                {
                    SET_DP_RX0_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT);
                }

                ScalerDpRx0Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_2:

            if(GET_DP_RX0_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX0 HDCP2 - Auth 2", 0);

                CLR_DP_RX0_HDCP2_AUTH_STATE_CHANGE();
            }

            if(GET_DP_RX0_HDCP2_REPEATER_AUTH_2_START() == _TRUE)
            {
                CLR_DP_RX0_HDCP2_REPEATER_AUTH_2_START();

                if(ScalerDpRx0Hdcp2CheckRxInfo() == _TRUE)
                {
                    ScalerDpRx0Hdcp2LoadReceiverIdList();

                    ScalerDpRx0Hdcp2VComputeProc();
                }

                DebugMessageHDCP2("DPRX0 HDCP2 - V Ready", 0);

                // Set V' Ready Bit and Issue CP_IRQ
                ScalerDpRx0CpIRQ(_DP_HDCP2_V_READY);

                ScalerDpRx0Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_FAKE:

            if(GET_DP_RX0_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX0 HDCP2 - Fake", 0);

                CLR_DP_RX0_HDCP2_AUTH_STATE_CHANGE();
            }

            if(GET_DP_RX0_HDCP2_REPEATER_AUTH_2_START() == _TRUE)
            {
                CLR_DP_RX0_HDCP2_REPEATER_AUTH_2_START();

                // Fake Authentication
                ScalerDpRx0Hdcp2FakeAuthenProc();

                // Set V' Ready Bit and Issue CP_IRQ
                ScalerDpRx0CpIRQ(_DP_HDCP2_V_READY);

                ScalerDpRx0Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE:

            if(GET_DP_RX0_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX0 HDCP2 - Done", 0);

                CLR_DP_RX0_HDCP2_AUTH_STATE_CHANGE();
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Change HDCP2 Auth State
// Input Value  : Target HDCP2 Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2ChangeAuthState(EnumDpRxHdcp2RepeaterAuthState enumHdcp2AuthState)
{
    SET_DP_RX0_HDCP2_AUTH_STATE(enumHdcp2AuthState);
    SET_DP_RX0_HDCP2_AUTH_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Set HDCP2 Repeater Proc Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2SetRepeaterProcTimeout(void)
{
    SET_DP_RX0_HDCP2_AUTH_REPEATER_PROC_TIMEOUT();
}

//--------------------------------------------------
// Description  : Check B info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx0Hdcp2CheckRxInfo(void)
{
    BYTE ucRxInfoDevice = 0;
    BYTE ucRxInfoDepth = 0;
    bit bRxInfoDeviceExceed = _FALSE;
    bit bRxInfoDepthExceed = _FALSE;
    bit bRxInfoHdcp1Dowstream = _FALSE;

    if(GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP2_REPEATER_SUPPORTED() == _TRUE)
        {
            if((GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT_EXCEED() == _TRUE) ||
               (GET_DP_TX_HDCP2_RXINFO_DEPTH_EXCEED() == _TRUE))
            {
                bRxInfoDeviceExceed = (GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT_EXCEED() == _TRUE) ? _TRUE : _FALSE;
                bRxInfoDepthExceed = (GET_DP_TX_HDCP2_RXINFO_DEPTH_EXCEED() == _TRUE) ? _TRUE : _FALSE;
            }
            else
            {
                ucRxInfoDevice = GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT();
                ucRxInfoDepth = GET_DP_TX_HDCP2_RXINFO_DEPTH();

                if(ucRxInfoDevice > 30)
                {
                    ucRxInfoDevice = 0x00;
                    bRxInfoDeviceExceed = _TRUE;
                }

                if(ucRxInfoDepth > 3)
                {
                    ucRxInfoDepth = 0x00;
                    bRxInfoDepthExceed = _TRUE;
                }
            }
        }

        if(bRxInfoDeviceExceed == _FALSE)
        {
            ucRxInfoDevice++;
        }

        bRxInfoHdcp1Dowstream = GET_DP_TX_HDCP2_RXINFO_HDCP1_DOWNSTREAM();
    }
    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
        {
            if((GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_MAX() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() > 30))
            {
                bRxInfoDeviceExceed = _TRUE;
            }
            else
            {
                ucRxInfoDevice = GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT();
            }

            if((GET_DP_TX_HDCP_DOWNSTREAM_DEPTH_MAX() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_DEPTH() > 3))
            {
                bRxInfoDepthExceed = _TRUE;
            }
            else
            {
                ucRxInfoDepth = GET_DP_TX_HDCP_DOWNSTREAM_DEPTH();
            }
        }

        if(bRxInfoDeviceExceed == _FALSE)
        {
            ucRxInfoDevice++;
        }

        bRxInfoHdcp1Dowstream = _TRUE;
    }

    if(bRxInfoDepthExceed == _FALSE)
    {
        ucRxInfoDepth++;
    }

    pData[0] = (ucRxInfoDepth << 1) | (ucRxInfoDevice >> 4);
    pData[1] = (ucRxInfoDevice << 4) |
               ((BYTE)bRxInfoDeviceExceed << 3) |
               ((BYTE)bRxInfoDepthExceed << 2) |
               ((BYTE)GET_DP_TX_HDCP2_RXINFO_HDCP20_REPEATER_DOWNSTREAM() << 1) |
               (bRxInfoHdcp1Dowstream);

    ScalerDpRx0SetDpcdValue(0x06, 0x93, 0x30, pData[0]);
    ScalerDpRx0SetDpcdValue(0x06, 0x93, 0x31, pData[1]);

    if((bRxInfoDeviceExceed == _TRUE) || (bRxInfoDepthExceed == _TRUE))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Load Receiver ID List
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2LoadReceiverIdList(void)
{
    pData[0] = 0;

    if(GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP2_REPEATER_SUPPORTED() == _TRUE)
        {
            pData[0] = GET_DP_TX_HDCP2_RXINFO_DEVICE_COUNT() * 5;
        }
        else
        {
            memset(g_pucDpTxHdcp2ReceiverIdList, 0, sizeof(g_pucDpTxHdcp2ReceiverIdList));
        }

        memcpy(&g_pucDpTxHdcp2ReceiverIdList[pData[0]], g_pucDpTxHdcp2ReceiverId, 5);
    }
    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
        {
            pData[0] = GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() * 5;

            memcpy(g_pucDpTxHdcp2ReceiverIdList, g_pucDpTxHdcpKsvFifo, pData[0]);
        }
        else
        {
            memset(g_pucDpTxHdcp2ReceiverIdList, 0, sizeof(g_pucDpTxHdcp2ReceiverIdList));
        }

        memcpy(&g_pucDpTxHdcp2ReceiverIdList[pData[0]], (volatile BYTE xdata *)PBB_4F_BKSV_0, 5);
    }
    else
    {
        memset(g_pucDpTxHdcp2ReceiverIdList, 0, sizeof(g_pucDpTxHdcp2ReceiverIdList));
    }

    SET_DP_RX0_AUX_MANUAL_MODE();

    for(pData[1] = 0; pData[1] < 155; pData[1]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x93, (0x45 + pData[1]), g_pucDpTxHdcp2ReceiverIdList[pData[1]]);
    }

    SET_DP_RX0_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx0Hdcp2VComputeProc(void)
{
    BYTE pucRxInfo[2] = {0};
    BYTE pucSeqNumV[3] = {0};

    pucRxInfo[0] = ScalerDpRx0GetDpcdInfo(0x06, 0x93, 0x30);
    pucRxInfo[1] = ScalerDpRx0GetDpcdInfo(0x06, 0x93, 0x31);

    // Compute V = HMAC-SHA256(Receiver ID List || RxInfo || seq_num_V, kd)
    if(ScalerHdcp2VprimeCalculate(g_pucDpRx0Hdcp2dKey0, g_pucDpRx0Hdcp2dKey1, g_pucDpTxHdcp2ReceiverIdList, pucRxInfo, pucSeqNumV) == _FALSE)
    {
        return _FALSE;
    }

    SET_DP_RX0_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        // Load MSB of V' into DPCD table
        ScalerDpRx0SetDpcdValue(0x06, 0x93, (0x32 + pData[0]), pucSeqNumV[pData[0]]);
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        // Load MSB of V' into DPCD table
        g_pucDpRx0Hdcp2VPrime[pData[0]] = ScalerGetByte(P63_35_HDCP_SHA_0 + pData[0]);
        ScalerDpRx0SetDpcdValue(0x06, 0x93, (0x35 + pData[0]), g_pucDpRx0Hdcp2VPrime[pData[0]]);
    }

    for(pData[0] = 16; pData[0] < 20; pData[0]++)
    {
        g_pucDpRx0Hdcp2VPrime[pData[0]] = ScalerGetByte(P63_35_HDCP_SHA_0 + pData[0]);
    }

    SET_DP_RX0_AUX_AUTO_MODE();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Fake HDCP Authentication
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx0Hdcp2FakeAuthenProc(void)
{
    BYTE pucRxInfo[2] = {0};
    BYTE pucSeqNumV[3] = {0};

    ScalerDpRx0SetDpcdValue(0x06, 0x93, 0x30, pucRxInfo[0]);
    ScalerDpRx0SetDpcdValue(0x06, 0x93, 0x31, pucRxInfo[1]);

    SET_DP_RX0_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x93, (0x45 + pData[0]), g_pucHdcpAksvBackup[pData[0]]);
    }

    for(pData[0] = 0; pData[0] < 150; pData[0]++)
    {
        ScalerDpRx0SetDpcdValue(0x06, 0x93, (0x4A + pData[0]), 0x00);
    }

    SET_DP_RX0_AUX_AUTO_MODE();

    // Compute V = HMAC-SHA256(Receiver ID List || RxInfo || seq_num_V, kd)
    if(ScalerHdcp2VprimeCalculate(g_pucDpRx0Hdcp2dKey0, g_pucDpRx0Hdcp2dKey1, g_pucHdcpAksvBackup, pucRxInfo, pucSeqNumV) == _FALSE)
    {
        return _FALSE;
    }

    SET_DP_RX0_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        // Load MSB of V' into DPCD table
        ScalerDpRx0SetDpcdValue(0x06, 0x93, (0x35 + pData[0]), ScalerGetByte(P63_35_HDCP_SHA_0 + pData[0]));
    }

    SET_DP_RX0_AUX_AUTO_MODE();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Change DP HDCP2.2 Repeater Capable for Rx0 Base On DPTX Clone Status
// Input Value  : InputPort, PortType, Clone Mode or not
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Hdcp2RepeaterCapableProc(BYTE ucInputPort, BYTE ucPortType)
{
    bit bDPRx0Hdcp2SetRepeater = _OFF;

    if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() != _DP_UNPLUG)
    {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if((ucPortType == _PORT_DP) && ((ucInputPort == _D0_INPUT_PORT) || (ucInputPort == _D6_INPUT_PORT)))
#else
        if((ucPortType == _PORT_DP) && (ucInputPort == _D0_INPUT_PORT))
#endif
        {
            bDPRx0Hdcp2SetRepeater = _ON;
        }
    }

    if(bDPRx0Hdcp2SetRepeater != GET_DP_RX0_HDCP2_REPEATER_CAPABLE())
    {
        if(bDPRx0Hdcp2SetRepeater == _ON)
        {
            SET_DP_RX0_HDCP2_REPEATER_CAPABLE();
        }
        else
        {
            CLR_DP_RX0_HDCP2_REPEATER_CAPABLE();
        }

        switch(GET_DP_RX0_HOTPLUG_ASSERT_TYPE())
        {
            case _DP_HPD_NONE:

                if(!((GET_DP_RX0_HDCP_MODE() == _HDCP_14) &&
                     ((ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))))
                {
                    if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
                    {
                        ScalerDpRx0CpIRQ(_DP_HDCP2_RXSTATUS_REAUTH_REQ);
                    }
                }

                break;

            case _DP_HPD_ASSERTED:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if(GET_D6_SWITCH_POWER_STATUS() != _DIGITAL_D6_SWITCH_POWER_ON)
                {
                    break;
                }
#endif
                if(!((GET_DP_RX0_HDCP_MODE() == _HDCP_14) &&
                     ((ScalerGetByte(PB_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))))
                {
                    if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
                    {
                        ScalerDpRx0CpIRQ(_DP_HDCP2_RXSTATUS_REAUTH_REQ);
                    }
                }

                break;

            default:
                break;
        }
    }
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_D0_DP_EXIST == _ON)
#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)
