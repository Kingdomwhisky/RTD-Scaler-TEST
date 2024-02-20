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
// ID Code      : RL6492_Series_DPRx1HDCP2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_DP_HDCP_2_2_SUPPORT == _ON)
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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpRx1Hdcp2Handler(void);
void ScalerDpRx1Hdcp2Handler_EXINT0(void);
void ScalerDpRx1Hdcp2ResetProc(void);
void ScalerDpRx1Hdcp2ResetProc_EXINT0(void);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
void ScalerDpRx1Hdcp2AesOnlineCtrlErrata(BYTE *pucInputArray, BYTE *pucCipherArray);
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx1Hdcp2SkeProc_WDINT(void);
void ScalerDpRx1Hdcp2LoadDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process for DP Rx1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Hdcp2Handler(void)
{
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    SET_DP_RX1_HDCP2_AKE_INIT_RECEIVED();
#endif

    // Receiver Has Received AKE_INIT
    if(GET_DP_RX1_HDCP2_AKE_INIT_RECEIVED() == _TRUE)
    {
        CLR_DP_RX1_HDCP2_AKE_INIT_RECEIVED();

        DebugMessageHDCP2("[D1]AKE_INIT", 0);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        // Reset HDCP Cipher
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, 0x00);
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

        g_pucDpRx1Hdcp2Rtx[0] = 0x18;
        g_pucDpRx1Hdcp2Rtx[1] = 0xfa;
        g_pucDpRx1Hdcp2Rtx[2] = 0xe4;
        g_pucDpRx1Hdcp2Rtx[3] = 0x20;
        g_pucDpRx1Hdcp2Rtx[4] = 0x6a;
        g_pucDpRx1Hdcp2Rtx[5] = 0xfb;
        g_pucDpRx1Hdcp2Rtx[6] = 0x51;
        g_pucDpRx1Hdcp2Rtx[7] = 0x49;

        g_pucDpRx1Hdcp2Rrx[0] = 0x3b;
        g_pucDpRx1Hdcp2Rrx[1] = 0xa0;
        g_pucDpRx1Hdcp2Rrx[2] = 0xbe;
        g_pucDpRx1Hdcp2Rrx[3] = 0xde;
        g_pucDpRx1Hdcp2Rrx[4] = 0x0c;
        g_pucDpRx1Hdcp2Rrx[5] = 0x46;
        g_pucDpRx1Hdcp2Rrx[6] = 0xa9;
        g_pucDpRx1Hdcp2Rrx[7] = 0x91;

        g_pucDpRx1Hdcp2TxCaps[0] = 0x02;
        g_pucDpRx1Hdcp2TxCaps[1] = 0x00;
        g_pucDpRx1Hdcp2TxCaps[2] = 0x00;

        g_pucDPRx1Caps[0] = 0x02;
        g_pucDPRx1Caps[1] = 0x00;
        g_pucDPRx1Caps[2] = 0x03;

        // Load Certrx to DPCD Table
        ScalerDpRx1Hdcp2LoadCertRrxKey();
#endif
    }

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    SET_DP_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED();
#endif

    // Receiver Has received AKE_NO_STORED_KM
    if(GET_DP_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED() == _TRUE)
    {
        if(ScalerDpRx1Hdcp2CaptureKpubKm() == _TRUE)
        {
            // Decrypt Km by FW to Get 128 bit Km
            if(ScalerHdcp2RxRsaOaepCalculate(g_pucDpRx1Hdcp2Km) == _TRUE)
            {
                ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_0, g_pucDpRx1Hdcp2Rtx, g_pucDpRx1Hdcp2Rrx, g_pucDpRx1Hdcp2Km, g_pucDpRx1Hdcp2Rn);

                memcpy(g_pucDpRx1Hdcp2dKey0, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

                ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_1, g_pucDpRx1Hdcp2Rtx, g_pucDpRx1Hdcp2Rrx, g_pucDpRx1Hdcp2Km, g_pucDpRx1Hdcp2Rn);

                memcpy(g_pucDpRx1Hdcp2dKey1, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                {
                    DebugMessageHDCP2("Dkey0", g_pucDpRx1Hdcp2dKey0[pData[0]]);
                }

                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                {
                    DebugMessageHDCP2("Dkey1", g_pucDpRx1Hdcp2dKey1[pData[0]]);
                }
#endif

                if(ScalerHdcp2HPrimeCalculate(g_pucDpRx1Hdcp2dKey0, g_pucDpRx1Hdcp2dKey1, g_pucDpRx1Hdcp2Rtx, g_pucDpRx1Hdcp2TxCaps, g_pucDPRx1Caps) == _TRUE)
                {
                    ScalerDpRx1Hdcp2CalculateKmKh();
                }
            }
        }
    }

    if(GET_DP_RX1_HDCP2_AKE_STORED_KM_RECEIVED() == _TRUE)
    {
        CLR_DP_RX1_HDCP2_AKE_STORED_KM_RECEIVED();
        CLR_DP_RX1_HDCP2_AUTHENTICATION_ACTIVE();

        DebugMessageHDCP2("[D1]AKE_STORED_KM", 0);
    }

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    SET_DP_RX1_HDCP2_LC_INIT_RECEIVED();
#endif

    if(GET_DP_RX1_HDCP2_LC_INIT_RECEIVED() == _TRUE)
    {
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        BYTE pucSHA256[32];
        memset(pucSHA256, 0, sizeof(pucSHA256));

        g_pucDpRx1Hdcp2Rn[0] = 0x32;
        g_pucDpRx1Hdcp2Rn[1] = 0x75;
        g_pucDpRx1Hdcp2Rn[2] = 0x3e;
        g_pucDpRx1Hdcp2Rn[3] = 0xa8;
        g_pucDpRx1Hdcp2Rn[4] = 0x78;
        g_pucDpRx1Hdcp2Rn[5] = 0xa6;
        g_pucDpRx1Hdcp2Rn[6] = 0x38;
        g_pucDpRx1Hdcp2Rn[7] = 0x1c;

        if(ScalerHdcp2LPrimeCalculate(g_pucDpRx1Hdcp2dKey0, g_pucDpRx1Hdcp2dKey1, g_pucDpRx1Hdcp2Rrx, g_pucDpRx1Hdcp2Rn) == _TRUE)
        {
            // Load L prime to pucSHA256
            memcpy(pucSHA256, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                DebugMessageHDCP2("L Prime", pucSHA256[pData[0]]);
            }
        }
#endif

        CLR_DP_RX1_HDCP2_LC_INIT_RECEIVED();

        DebugMessageHDCP2("[D1]LC_INIT", 0);
    }

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    SET_DP_RX1_HDCP2_SKE_SEND_EKS_RECEIVED();
#endif

    if(GET_DP_RX1_HDCP2_SKE_SEND_EKS_RECEIVED() == _TRUE)
    {
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        BYTE pucEDkeyKs[16];
        BYTE pucInputCipher[16];
        BYTE pucRiv[8];
        BYTE pucKs[16];

        memset(pucInputCipher, 0, sizeof(pucInputCipher));
        memset(pucKs, 0, sizeof(pucKs));

        // Calculate Dkey 2
        ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_2, g_pucDpRx1Hdcp2Rtx, g_pucDpRx1Hdcp2Rrx, g_pucDpRx1Hdcp2Km, g_pucDpRx1Hdcp2Rn);

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
            pucKs[pData[0]] = pucEDkeyKs[pData[0]] ^ (ScalerGetByte((P63_81_HDCP_AES_OUT_15 + pData[0])) ^ g_pucDpRx1Hdcp2Rrx[pData[0] - 8]);
        }

        for(pData[0] = 0; pData[0] < 16; pData[0]++)
        {
            DebugMessageHDCP2("Ks", pucKs[pData[0]]);
        }

        SET_DP_RX1_HDCP2_AUTHENTICATION_DONE();

        // Enable DP Link Integrity Check
        ScalerSetBit(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

        // Enable Decryption
        for(pData[0] = 0; pData[0] < 16; ++pData[0])
        {
            pucInputCipher[pData[0]] = pucKs[pData[0]] ^ g_stRxHdcp2DownLoadKeyType.pucHdcp2Lc[pData[0]];
        }

        // Enable AES Decryption Cipher
        ScalerDpRx1Hdcp2AesOnlineCtrlErrata(pucRiv, pucInputCipher);
#endif

        CLR_DP_RX1_HDCP2_SKE_SEND_EKS_RECEIVED();

        DebugMessageHDCP2("[D1]SKE_SEND_EKS", 0);
    }

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    SET_DP_RX1_HDCP2_STREAM_MANAGE_RECEIVED();
#endif

    if(GET_DP_RX1_HDCP2_STREAM_MANAGE_RECEIVED() == _TRUE)
    {
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        // Get M Prime
        if(ScalerDpRx1Hdcp2MPrimeCalculate() == _TRUE)
        {
            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                g_pucHdcp2Sha256[pData[0]] = ScalerGetByte(P63_35_HDCP_SHA_0 + pData[0]);

                DebugMessageHDCP2("M prime", g_pucHdcp2Sha256[pData[0]]);
            }
        }
#endif

        CLR_DP_RX1_HDCP2_STREAM_MANAGE_RECEIVED();
    }
}
//--------------------------------------------------
// Description  : HDCP 2.2 Int Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Hdcp2Handler_EXINT0(void) using 1
{
    BYTE ucMessageId = 0;

    // DP Global IRQ Flag
    if(ScalerGetBit_EXINT(PBA_DC_AUX_IRQ_STATUS, _BIT7) == _BIT7)
    {
        g_pucDpRx1Backup[0] = ScalerGetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H);
        g_pucDpRx1Backup[1] = ScalerGetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M);
        g_pucDpRx1Backup[2] = ScalerGetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L);

        // Get HDCP2.2 Message ID
        ucMessageId = ScalerDpRx1Hdcp2GetMessageID_EXINT0();

        if(ucMessageId == _HDCP_2_2_NONE)
        {
            ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, g_pucDpRx1Backup[0]);
            ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, g_pucDpRx1Backup[1]);
            ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, g_pucDpRx1Backup[2]);

            return;
        }
        else
        {
            // Switch HDCP to 2.2 Module from 1.4 Module
            if(GET_DP_RX1_HDCP_MODE_EXINT() == _HDCP_14)
            {
                // Enable HDCP 2.2 Module
                SET_DP_RX1_HDCP_MODE_EXINT(_HDCP_22);
            }
        }

        switch(ucMessageId)
        {
            case _HDCP_2_2_AKE_INIT:

                // HDCP2 Reset Proc
                ScalerDpRx1Hdcp2ResetProc_EXINT0();

                // Save Transmitter Rtx to FW (MSB located at index 0)
                ScalerDpRx1Hdcp2LoadDpcdValue_EXINT0(0x06, 0x90, 0x00, 8, g_pucDpRx1Hdcp2Rtx);

                // Save TxCaps to FW (MSB located at index 0)
                ScalerDpRx1Hdcp2LoadDpcdValue_EXINT0(0x06, 0x90, 0x08, 3, g_pucDpRx1Hdcp2TxCaps);

                // Generate the psudo-random key of Rrx
                ScalerHdcp2RxGenRrx_EXINT0(g_pucDpRx1Hdcp2Rrx);

                // Load Rrx to DPCD Table (MSB located at index 0)
                ScalerDpRx1Hdcp2SetDpcdReadValue_EXINT0(_HDCP_2_2_RRX, g_pucDpRx1Hdcp2Rrx, 8);

                ScalerDpRx1Hdcp2ClearDpcdReadValue_EXINT0(_HDCP_2_2_RX_H_PRIME, 32);
                ScalerDpRx1Hdcp2ClearDpcdReadValue_EXINT0(_HDCP_2_2_RX_L_PRIME, 32);
                ScalerDpRx1Hdcp2ClearDpcdReadValue_EXINT0(_HDCP_2_2_RX_M_PRIME, 32);
                ScalerDpRx1Hdcp2ClearDpcdReadValue_EXINT0(_HDCP_2_2_RX_PAIRING_INFO, 16);

#if(_WD_TIMER_INT_SUPPORT == _ON)
                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE);
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
                // Check if source doing HDCP handshake while HDCP capability disable
                if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x06, 0x92, 0x1F, _BIT1) == 0x00)
                {
                    SET_DP_RX1_HDCP_HANDSHAKE_WO_CAP();
                }
#endif

                SET_DP_RX1_HDCP2_AKE_INIT_RECEIVED();

                break;

            case _HDCP_2_2_AKE_NO_STORED_KM:

                SET_DP_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED();

                break;

            case _HDCP_2_2_AKE_SEND_PAIRING_INFO:

                // Start Pairing AES Calculate
                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    if(pData_EXINT[0] < 8)
                    {
                        g_pucHdcp2M[pData_EXINT[0]] = g_pucDpRx1Hdcp2Rtx[pData_EXINT[0]];
                    }
                    else
                    {
                        g_pucHdcp2M[pData_EXINT[0]] = g_pucDpRx1Hdcp2Rrx[pData_EXINT[0] - 8];
                    }
                }

                // AES Cipher Calculate Ekh[km]
                ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2M, g_pucHdcp2Kh);

                // Calculate Ekh[km] = kh AES m XOR Km
                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucHdcp2EkhKm[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]) ^ g_pucDpRx1Hdcp2Km[pData_EXINT[0]];
                }

                // Load Ekh_km prime to DPCD Table
                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x92, (0xE0 + pData_EXINT[0]), g_pucHdcp2EkhKm[pData_EXINT[0]]);
                }

                // Doesn't Assert Pairing Available CPIRQ Before H Prime CPIRQ
                if(GET_DP_RX1_HDCP2_WAITING_H_PRIME_CPIRQ_ASSERTED() == _FALSE)
                {
                    // Set Pairing Available Flag
                    ScalerDpRx1CpIRQ_EXINT0(_DP_HDCP2_PARING_AVAILABLE);
                }
                else
                {
                    // Recoed Pairing Available CPIRQ Asserted Sataus
                    SET_DP_RX1_HDCP2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED();
                }

                break;

            case _HDCP_2_2_AKE_STORED_KM:

                // Save Ekh[km] From Transmitter to FW
                ScalerDpRx1Hdcp2LoadDpcdValue_EXINT0(0x06, 0x92, 0xA0, 16, g_pucDpRx1Hdcp2Km);

                // Save m From Transmitter to FW
                ScalerDpRx1Hdcp2LoadDpcdValue_EXINT0(0x06, 0x92, 0xB0, 16, g_pucHdcp2M);

                // Calculate Km use AES Cipher, Input Value = m, Input Cipher = Kh
                ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2M, g_pucHdcp2Kh);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucDpRx1Hdcp2Km[pData_EXINT[0]] = g_pucDpRx1Hdcp2Km[pData_EXINT[0]] ^ ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate DKey0
                ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_0, g_pucDpRx1Hdcp2Rtx, g_pucDpRx1Hdcp2Rrx, g_pucDpRx1Hdcp2Km, g_pucDpRx1Hdcp2Rn);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucDpRx1Hdcp2dKey0[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate Dkey1
                ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_1, g_pucDpRx1Hdcp2Rtx, g_pucDpRx1Hdcp2Rrx, g_pucDpRx1Hdcp2Km, g_pucDpRx1Hdcp2Rn);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucDpRx1Hdcp2dKey1[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate H'
                if(ScalerHdcp2HPrimeCalculate_EXINT0(g_pucDpRx1Hdcp2dKey0, g_pucDpRx1Hdcp2dKey1, g_pucDpRx1Hdcp2Rtx, g_pucDpRx1Hdcp2TxCaps, g_pucDPRx1Caps) == _TRUE)
                {
                    for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
                    {
                        g_pucHdcp2Sha256[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[0]);
                    }

                    // Load H prime to DPCD Table
                    ScalerDpRx1Hdcp2SetDpcdReadValue_EXINT0(_HDCP_2_2_RX_H_PRIME, g_pucHdcp2Sha256, 32);
                }

                ScalerDpRx1CpIRQ_EXINT0(_DP_HDCP2_H_PRIME_AVAILABLE);

                SET_DP_RX1_HDCP2_AKE_STORED_KM_RECEIVED();
                SET_DP_RX1_HDCP2_AUTHENTICATION_ACTIVE();

                break;

            case _HDCP_2_2_LC_INIT:

                // Save Transmitter Rn to FW
                ScalerDpRx1Hdcp2LoadDpcdValue_EXINT0(0x06, 0x92, 0xF0, 8, g_pucDpRx1Hdcp2Rn);

                if(ScalerHdcp2LPrimeCalculate_EXINT0(g_pucDpRx1Hdcp2dKey0, g_pucDpRx1Hdcp2dKey1, g_pucDpRx1Hdcp2Rrx, g_pucDpRx1Hdcp2Rn) == _TRUE)
                {
                    // Load L prime to g_pucHdcp2Sha256
                    for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
                    {
                        g_pucHdcp2Sha256[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[0]);
                    }

                    // Load L prime to DPCD Table
                    ScalerDpRx1Hdcp2SetDpcdReadValue_EXINT0(_HDCP_2_2_RX_L_PRIME, g_pucHdcp2Sha256, 32);
                }

                SET_DP_RX1_HDCP2_LC_INIT_RECEIVED();

                break;

            case _HDCP_2_2_SKE_SEND_EKS:

                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE);

                // Execute Ske_Send_Eks Procedure after 4msec
                ScalerTimerWDActivateTimerEvent_EXINT0(4, _SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE);

                break;

            case _HDCP_2_2_SKE_TYPE_VALUE:

                // Set AES Type
                if(ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x94, 0x94) == 0x00)
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

                SET_DP_RX1_HDCP2_AUTHENTICATION_DONE();

                break;

            case _HDCP_2_2_REPEATERAUTH_STREAM_MANAGE:

                // Get M Prime
                if(ScalerDpRx1Hdcp2MPrimeCalculate_EXINT0() == _TRUE)
                {
                    for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
                    {
                        g_pucHdcp2Sha256[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[0]);
                    }

                    // Load M prime to DPCD Table
                    ScalerDpRx1Hdcp2SetDpcdReadValue_EXINT0(_HDCP_2_2_RX_M_PRIME, g_pucHdcp2Sha256, 32);

                    // Set AES Type
                    ScalerDpRx1Hdcp2SetAESType_EXINT0();

                    // Enable HDCP2.2 Auth. Done
                    ScalerSetBit_EXINT(PB_20_HDCP_DEBUG, ~_BIT4, _BIT4);

                    SET_DP_RX1_HDCP2_AUTHENTICATION_DONE();

                    SET_DP_RX1_HDCP2_STREAM_MANAGE_RECEIVED();
                }

                break;

            default:
                break;
        }

        ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, g_pucDpRx1Backup[0]);
        ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, g_pucDpRx1Backup[1]);
        ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, g_pucDpRx1Backup[2]);
    }
}
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Hdcp2ResetProc(void)
{
#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    if(GET_REG_DP_RX1_MAC_ASSIGNED() == _TRUE)
#endif
    {
        // Disable HDCP2.2 Auth. Done
        ScalerSetBit(PB_20_HDCP_DEBUG, ~_BIT4, 0x00);

        // Clear Type Value
        ScalerSetByte(PB_93_HDCP_TYPE_AES_0, 0x00);

        // Reset HDCP Block
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
        ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

        // Disable HDCP2.2
        SET_DP_RX1_HDCP_MODE(_HDCP_14);
    }

    // Disable Type INT
    ScalerSetBit(_REG_DP_RX1_HDCP2_ADDR_A5, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);

    SET_DP_RX1_AUX_MANUAL_MODE();

    // Reset 69494h Type Value. Be Careful. If Clear this Address which is Writed by Source, Must Disable INT Function First.
    ScalerDpRx1SetDpcdValue(0x06, 0x94, 0x94, 0x00);

    SET_DP_RX1_AUX_AUTO_MODE();

    // Clear Type INT Flag
    ScalerSetBit(_REG_DP_RX1_HDCP2_ADDR_A5, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Enable Type INT
    ScalerSetBit(_REG_DP_RX1_HDCP2_ADDR_A5, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), _BIT5);

    // Disable Read DPCD 692DFh(HPrime) INT
    ScalerSetBit(_REG_DP_RX1_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), 0x00);

    // Clear Read DPCD 692DF(HPrime) INT Flag
    ScalerSetBit(_REG_DP_RX1_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT5);

    // Clear RxStatus REAUTH_REQ
    ScalerDpRx1SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) & 0xE0));

    CLR_DP_RX1_HDCP2_AUTHENTICATION_DONE();
    CLR_DP_RX1_HDCP2_AKE_INIT_RECEIVED();
    CLR_DP_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED();
    CLR_DP_RX1_HDCP2_AKE_STORED_KM_RECEIVED();
    CLR_DP_RX1_HDCP2_LC_INIT_RECEIVED();
    CLR_DP_RX1_HDCP2_SKE_SEND_EKS_RECEIVED();
    CLR_DP_RX1_HDCP2_AUTHENTICATION_ACTIVE();
}
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Hdcp2ResetProc_EXINT0(void) using 1
{
#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    if(GET_REG_DP_RX1_MAC_ASSIGNED_EXINT() == _TRUE)
#endif
    {
        // Disable HDCP2.2 Auth. Done
        ScalerSetBit_EXINT(PB_20_HDCP_DEBUG, ~_BIT4, 0x00);

        // Clear Type Value
        ScalerSetByte_EXINT(PB_93_HDCP_TYPE_AES_0, 0x00);
    }

    // Disable Type INT
    ScalerSetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A5, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Reset 69494h Type Value. Be Careful. If Clear this Address which is Writed by Source, Must Disable INT Function First.
    ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x94, 0x94, 0x00);

    // Clear Type INT Flag
    ScalerSetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A5, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Enable Type INT
    ScalerSetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A5, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), _BIT5);

    // Disable Read DPCD 692DFh(HPrime) INT
    ScalerSetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), 0x00);

    // Clear Read DPCD 692DF(HPrime) INT Flag
    ScalerSetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT5);

    // Clear RxStatus REAUTH_REQ and Link Intergrity Failure for HDCP 2.2
    ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x94, 0x93) & 0xE0));

    // Clear Bstatus REAUTH_REQ and Link Intergrity Failure for HDCP 1.4
    ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, 0x29, (ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x80, 0x29) & 0xF0));

    CLR_DP_RX1_HDCP2_AUTHENTICATION_DONE();
    CLR_DP_RX1_HDCP2_AKE_INIT_RECEIVED();
    CLR_DP_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED();
    CLR_DP_RX1_HDCP2_AKE_STORED_KM_RECEIVED();
    CLR_DP_RX1_HDCP2_LC_INIT_RECEIVED();
    CLR_DP_RX1_HDCP2_SKE_SEND_EKS_RECEIVED();
    CLR_DP_RX1_HDCP2_AUTHENTICATION_ACTIVE();
}

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 On-Line AES Ctrl
// Input Value  : *pucInputArray, *pucCipherArray
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Hdcp2AesOnlineCtrlErrata(BYTE *pucInputArray, BYTE *pucCipherArray)
{
    memcpy((volatile BYTE xdata *)PB_81_HDCP_AES_CIPHER_KEY_15, pucCipherArray, 16);
    memcpy((volatile BYTE xdata *)PB_55_RIV0, pucInputArray, 8);
}
#endif // End of #if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : WD Timer Event Proc of DP RX1 HDCP2 SKE Proc
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Hdcp2SkeProc_WDINT(void) using 3
{
    // Calculate Dkey 2
    ScalerHdcp2DkeyCalculate_WDINT(_HDCP_2_2_DKEY_2, g_pucDpRx1Hdcp2Rtx, g_pucDpRx1Hdcp2Rrx, g_pucDpRx1Hdcp2Km, g_pucDpRx1Hdcp2Rn);

    // Save Edkey_ks to g_pucHdcp2EDkeyKs
    ScalerDpRx1Hdcp2LoadDpcdValue_WDINT(0x06, 0x93, 0x18, 16, g_pucHdcp2EDkeyKs);

    // Save Riv to g_pucHdcp2Riv
    ScalerDpRx1Hdcp2LoadDpcdValue_WDINT(0x06, 0x93, 0x28, 8, g_pucHdcp2Riv);

    // Decode Ks
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; ++pData_EXINT[0])
    {
        g_pucHdcp2Ks[pData_EXINT[0]] = g_pucHdcp2EDkeyKs[pData_EXINT[0]] ^ ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]));
    }

    for(pData_EXINT[0] = 8; pData_EXINT[0] < 16; ++pData_EXINT[0])
    {
        g_pucHdcp2Ks[pData_EXINT[0]] = g_pucHdcp2EDkeyKs[pData_EXINT[0]] ^ (ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + pData_EXINT[0])) ^ g_pucDpRx1Hdcp2Rrx[pData_EXINT[0] - 8]);
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
    if(ScalerDpRx1GetDpcdBitInfo_WDINT(0x06, 0x92, 0x1F, (_BIT1 | _BIT0)) == _BIT1)
    {
        // Enable HDCP2.2 Auth. Done
        ScalerSetBit_EXINT(PB_20_HDCP_DEBUG, ~_BIT4, _BIT4);

        SET_DP_RX1_HDCP2_AUTHENTICATION_DONE();
    }

    SET_DP_RX1_HDCP2_SKE_SEND_EKS_RECEIVED();
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
void ScalerDpRx1Hdcp2LoadDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray) using 3
{
    BYTE ucIndex = 0x00;
    WORD usDpcdAddress = 0;

    usDpcdAddress = (((WORD)ucDpcdAccessPortM << 8) | ((WORD)ucDpcdAccessPortL));

    // Load Value To FW
    for(ucIndex = 0; ucIndex < ucLength; ucIndex++)
    {
        pucReadArray[ucIndex] = ScalerDpRx1GetDpcdInfo_WDINT(ucDpcdAccessPortH, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress));

        usDpcdAddress = usDpcdAddress + 1;
    }
}
#endif // End of #if(_WD_TIMER_INT_SUPPORT == _ON)
#endif // End of #if(_D1_DP_EXIST == _ON)
#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)
