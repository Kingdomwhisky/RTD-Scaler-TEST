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
// ID Code      : ScalerCommonDPRx1HDCP2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerCommonFunctionInclude.h"

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
//----------------------------------------------------------------------------
// Global Variables (XDATA) for Each Interface = 77 Bytes
//----------------------------------------------------------------------------
BYTE g_ucDPRx1Hdcp2Ctrl0;
BYTE g_ucDPRx1Hdcp2Ctrl1;
BYTE g_pucDpRx1Hdcp2dKey0[16];
BYTE g_pucDpRx1Hdcp2dKey1[16];
BYTE g_pucDpRx1Hdcp2Km[16];
BYTE g_pucDpRx1Hdcp2Rtx[8];
BYTE g_pucDpRx1Hdcp2TxCaps[3];
BYTE g_pucDpRx1Hdcp2Rn[8];
BYTE g_pucDpRx1Hdcp2Rrx[8];
BYTE g_pucDpRx1Hdcp2VPrime[20];

#if(_DP_TX_SUPPORT == _ON)
StructDpRxHdcp2AuthInfo g_stDpRx1Hdcp2AuthInfo;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE ScalerDpRx1Hdcp2GetMessageID_EXINT0(void);
void ScalerDpRx1Hdcp2LoadCertRrxKey(void);
void ScalerDpRx1Hdcp2LoadDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray);
BYTE ScalerDpRx1Hdcp2MPrimeCalculate_EXINT0(void);
void ScalerDpRx1Hdcp2SetAESType_EXINT0(void);
void ScalerDpRx1Hdcp2SetDpcdReadValue_EXINT0(BYTE ucRSAType, BYTE *pucReadArray, WORD usLength);
void ScalerDpRx1Hdcp2ClearDpcdReadValue_EXINT0(BYTE ucRSAType, WORD usLength);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
BYTE ScalerDpRx1Hdcp2MPrimeCalculate(void);
#endif

bit ScalerDpRx1Hdcp2CaptureKpubKm(void);
void ScalerDpRx1Hdcp2CalculateKmKh(void);

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRx1Hdcp2RepeaterHandler(void);
void ScalerDpRx1Hdcp2ChangeAuthState(EnumDpRxHdcp2RepeaterAuthState enumHdcp2AuthState);
void ScalerDpRx1Hdcp2SetRepeaterProcTimeout(void);
bit ScalerDpRx1Hdcp2CheckRxInfo(void);
void ScalerDpRx1Hdcp2LoadReceiverIdList(void);
bit ScalerDpRx1Hdcp2VComputeProc(void);
bit ScalerDpRx1Hdcp2FakeAuthenProc(void);
void ScalerDpRx1Hdcp2RepeaterCapableProc(BYTE ucInputPort, BYTE ucPortType);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get HDCP 2.2 Message ID Code
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
BYTE ScalerDpRx1Hdcp2GetMessageID_EXINT0(void) using 1
{
    // Write Ake Initial
    if((ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A3, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A4, _BIT3) == _BIT3))
    {
        // CLR Flag
        ScalerSetByte_EXINT(_REG_DP_RX1_HDCP2_ADDR_A4, _BIT3);

        return _HDCP_2_2_AKE_INIT;
    }

    // Write AKE No Store Km
    if((ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A3, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A4, _BIT7) == _BIT7))
    {
        // CLR Flag
        ScalerSetByte_EXINT(_REG_DP_RX1_HDCP2_ADDR_A4, _BIT7);

        return _HDCP_2_2_AKE_NO_STORED_KM;
    }

    // Read HPrime
    if((ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_FB, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_FB, _BIT5) == _BIT5))
    {
        // Disable INT
        ScalerSetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), 0x00);

        // CLR Flag
        ScalerSetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT5);

        return _HDCP_2_2_AKE_SEND_PAIRING_INFO;
    }

    // Write AKE Store Km
    if((ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A3, _BIT6) == _BIT6) && (ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A4, _BIT6) == _BIT6))
    {
        // CLR Flag
        ScalerSetByte_EXINT(_REG_DP_RX1_HDCP2_ADDR_A4, _BIT6);

        return _HDCP_2_2_AKE_STORED_KM;
    }

    // Write Locality Check Initial
    if((ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A3, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A4, _BIT4) == _BIT4))
    {
        // CLR Flag
        ScalerSetByte_EXINT(_REG_DP_RX1_HDCP2_ADDR_A4, _BIT4);

        return _HDCP_2_2_LC_INIT;
    }

    // Write SEK Send
    if((ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A5, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A5, _BIT0) == _BIT0))
    {
        // CLR Flag
        ScalerSetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A5, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

        return _HDCP_2_2_SKE_SEND_EKS;
    }

    // Write Cipher Type
    if((ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A5, _BIT5) == _BIT5) && (ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A5, _BIT1) == _BIT1))
    {
        // CLR Flag
        ScalerSetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A5, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        return _HDCP_2_2_SKE_TYPE_VALUE;
    }

    // Write Stream ID Type
    if((ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A3, _BIT5) == _BIT5) && (ScalerGetBit_EXINT(_REG_DP_RX1_HDCP2_ADDR_A4, _BIT5) == _BIT5))
    {
        // CLR Flag
        ScalerSetByte_EXINT(_REG_DP_RX1_HDCP2_ADDR_A4, _BIT5);

        return _HDCP_2_2_REPEATERAUTH_STREAM_MANAGE;
    }

    return _HDCP_2_2_NONE;
}
//--------------------------------------------------
// Description  : HDCP 2.2 Load Certificate Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Hdcp2LoadCertRrxKey(void)
{
    for(PDATA_WORD(0) = 0; PDATA_WORD(0) < 522; PDATA_WORD(0)++)
    {
        PDATA_WORD(1) = 0x900B + PDATA_WORD(0);

        ScalerDpRx1SetDpcdValue(0x06, pData[2], pData[3], g_stRxHdcp2DownLoadKeyType.pucHdcp2Certrx[PDATA_WORD(0)]);
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
void ScalerDpRx1Hdcp2LoadDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray) using 1
{
    pData_EXINT[2] = ucDpcdAccessPortM;
    pData_EXINT[3] = ucDpcdAccessPortL;

    // Load Value To FW
    for(pData_EXINT[0] = 0; pData_EXINT[0] < ucLength; pData_EXINT[0]++)
    {
        pucReadArray[pData_EXINT[0]] = ScalerDpRx1GetDpcdInfo_EXINT0(ucDpcdAccessPortH, pData_EXINT[2], pData_EXINT[3]);

        PDATA_WORD_EXINT(1) = PDATA_WORD_EXINT(1) + 1;
    }
}
//--------------------------------------------------
// Description  : Get M Prime
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpRx1Hdcp2MPrimeCalculate_EXINT0(void) using 1
{
    BYTE pucSHA256Input[64];
    memset(pucSHA256Input, 0, sizeof(pucSHA256Input));

    // Get kd
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 64; pData_EXINT[0]++)
    {
        if(pData_EXINT[0] < 16)
        {
            pucSHA256Input[pData_EXINT[0]] = g_pucDpRx1Hdcp2dKey0[pData_EXINT[0]];
        }
        else if(pData_EXINT[0] < 32)
        {
            pucSHA256Input[pData_EXINT[0]] = g_pucDpRx1Hdcp2dKey1[pData_EXINT[0] - 16];
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
    pData_EXINT[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x93, 0xF4) * 2;

    // Stuff streamID_Type
    for(pData_EXINT[0] = 0; pData_EXINT[0] < pData_EXINT[1]; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256Input[pData_EXINT[0]] = ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x93, 0xF5 + pData_EXINT[0]);
    }

    // Stuff seq_num_M
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 3; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256Input[pData_EXINT[1] + pData_EXINT[0]] = ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x93, (0xF0 + pData_EXINT[0]));
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
// Description  : Set AES Type
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpRx1Hdcp2SetAESType_EXINT0(void) using 1
{
    // StreamID = 0 for SST Case
    if(ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x93, 0xF5) == 0x00)
    {
        // Set AES Type
        if(ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x93, 0xF6) == 0x00)
        {
            // Type = 0x00
            ScalerSetByte_EXINT(_REG_DP_RX1_HDCP2_TYPE_AES0_VALUE, 0x00);
        }
        else
        {
            // Type = 0x01 or Type = 0x02 - 0xFF
            ScalerSetByte_EXINT(_REG_DP_RX1_HDCP2_TYPE_AES0_VALUE, 0x01);
        }
    }
#if((_DP_MST_SUPPORT == _ON) && (_HW_DP_RX_HDCP2_ONLINE_AES_COUNT == _DP_RX_HDCP2_ONLINE_AES_2SET))
    else
    {
        // Get # of Stream
        pData_EXINT[3] = ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x93, 0xF4);

        // Set STx AES Type
        for(pData_EXINT[0] = 0; pData_EXINT[0] < pData_EXINT[3]; pData_EXINT[0]++)
        {
            for(pData_EXINT[1] = 0; pData_EXINT[1] < 5; pData_EXINT[1]++)
            {
                if(g_pucDpStreamToIdMapping[pData_EXINT[1]] == ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x93, 0xF5 + (2 * pData_EXINT[0])))
                {
                    pData_EXINT[2] = ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x93, 0xF5 + (2 * pData_EXINT[0]) + 1);

                    if(pData_EXINT[2] == 0x00)
                    {
                        // Type = 0x00
                        ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~(_BIT7 >> pData_EXINT[1]), 0x00);
                    }
                    else
                    {
                        // Type = 0x01 or Type = 0x02 - 0xFF
                        ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~(_BIT7 >> pData_EXINT[1]), (_BIT7 >> pData_EXINT[1]));
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
void ScalerDpRx1Hdcp2SetDpcdReadValue_EXINT0(BYTE ucRSAType, BYTE *pucReadArray, WORD usLength) using 1
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
        ScalerDpRx1SetDpcdValue_EXINT0(pData_EXINT[1], pData_EXINT[2], pData_EXINT[3], pucReadArray[pData_EXINT[0]]);
        PDATA_WORD_EXINT(1) = PDATA_WORD_EXINT(1) + 1;
    }
}

//--------------------------------------------------
// Description  : Clear HDCP Receiver Public Key Certificate
// Input Value  : Public Key / Write Length
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Hdcp2ClearDpcdReadValue_EXINT0(BYTE ucRSAType, WORD usLength) using 1
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
        ScalerDpRx1SetDpcdValue_EXINT0(pData_EXINT[1], pData_EXINT[2], pData_EXINT[3], 0x00);
        PDATA_WORD_EXINT(1) = PDATA_WORD_EXINT(1) + 1;
    }
}

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get M Prime
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpRx1Hdcp2MPrimeCalculate(void)
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
bit ScalerDpRx1Hdcp2CaptureKpubKm(void)
{
    BYTE pucKpubKm[128];
    memset(pucKpubKm, 0, sizeof(pucKpubKm));

    CLR_DP_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED();

    DebugMessageHDCP2("[D1]AKE_NO_STORED_KM", 0);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    for(pData[0] = 0; pData[0] < 128; pData[0]++)
    {
        pucKpubKm[pData[0]] = g_stRxHdcp2DownLoadKeyType.pucHdcp2KpubKm[pData[0]];

        DebugMessageHDCP2("[D1]Ekpub(km)", pucKpubKm[pData[0]]);
    }
#else
    // Save Transmitter Ekpub[km] to FW
    for(pData[0] = 0; pData[0] < 128; pData[0]++)
    {
        pucKpubKm[pData[0]] = ScalerDpRx1GetDpcdInfo(0x06, 0x92, (0x20 + pData[0]));
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
void ScalerDpRx1Hdcp2CalculateKmKh(void)
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

    SET_DP_RX1_AUX_MANUAL_MODE();

    // Load H prime to DPCD Table
    for(pData[0] = 0; pData[0] < 32; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x92, (0xC0 + pData[0]), pucSHA256[pData[0]]);
    }

    // Initialize Waiting To Assert H Prime_CPIRQ To Check if H' Is Read By Source Before CPIRQ With H Pirme Available Is Asserted
    SET_DP_RX1_HDCP2_WAITING_H_PRIME_CPIRQ_ASSERTED();

    // Initialize Pairing Available CPIRQ Flag To Record Pairing Available CPIRQ Asserted Status
    CLR_DP_RX1_HDCP2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED();

    // Clear Read DPCD 692DF(HPrime) INT Flag
    ScalerSetBit(_REG_DP_RX1_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT5);

    // Enable Read DPCD 692DFh(HPrime) INT
    ScalerSetBit(_REG_DP_RX1_HDCP2_ADDR_FB, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT4);

    SET_DP_RX1_AUX_AUTO_MODE();

    // Set H Prime Available Flag
    ScalerDpRx1CpIRQ(_DP_HDCP2_H_PRIME_AVAILABLE);

    // Clear H Prime Available CPIRQ Status
    CLR_DP_RX1_HDCP2_WAITING_H_PRIME_CPIRQ_ASSERTED();

    // Assert Pairing Available CPIRQ If No Asserting in Pairing Info INT State
    if(GET_DP_RX1_HDCP2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED() == _TRUE)
    {
        // Clear Pairing Available CPIRQ Status
        CLR_DP_RX1_HDCP2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED();

        // Set Pairing Available Flag
        ScalerDpRx1CpIRQ(_DP_HDCP2_PARING_AVAILABLE);
    }

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    // Start Pairing AES Calculate
    for(pData[0] = 0; pData[0] < 16; ++pData[0])
    {
        if(pData[0] < 8)
        {
            pucM[pData[0]] = g_pucDpRx1Hdcp2Rtx[pData[0]];
        }
        else
        {
            pucM[pData[0]] = g_pucDpRx1Hdcp2Rrx[pData[0] - 8];
        }
    }

    // AES Cipher Calculate Ekh[km]
    ScalerHdcp2RxAesOfflineCtrl(pucM, g_pucHdcp2Kh);

    // Calculate Ekh[km] = kh AES m XOR Km
    for(pData[0] = 0; pData[0] < 16; ++pData[0])
    {
        g_pucHdcp2Kh[pData[0]] = ScalerGetByte(P63_81_HDCP_AES_OUT_15 + pData[0]) ^ g_pucDpRx1Hdcp2Km[pData[0]];

        DebugMessageHDCP2("g_ucHdcp2Kh", g_pucHdcp2Kh[pData[0]]);
    }
#endif
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Hdcp2RepeaterHandler(void)
{
    if(GET_DP_RX1_HDCP2_MODE() == _ENABLE)
    {
        if(GET_DP_RX1_HDCP2_REPEATER_CAPABLE() == _TRUE)
        {
            if(GET_DP_RX1_HDCP2_REPEATER_AUTH_1_START() == _TRUE)
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - Get AKE INIT", 0);

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP2_CPIRQ_EVENT);

                CLR_DP_RX1_HDCP2_AUTH_CPIRQ_TIMRE();

                ScalerDpRx1Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_IDLE);
            }

            if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
            {
                // For MST mode
                if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT0) == _BIT0)
                {
                    if((ScalerDpRx1HdcpCheckValid() == _TRUE) && (GET_DP_RX1_HDCP2_AUTH_CPIRQ_TIMRE() == _FALSE))
                    {
                        if(ScalerDpRx1HDCPCheckLvp() == _FALSE)
                        {
                            SET_DP_RX1_HDCP2_AUTH_CPIRQ_TIMRE();

                            ScalerDpRx1CpIRQ(_DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

                            ScalerTimerActiveTimerEvent(SEC(0.02), _SCALER_TIMER_EVENT_DP_RX1_HDCP2_CPIRQ_EVENT);
                        }
                    }
                }
                else
                {
                    // In SST mode, issue HPD event for upstream device if DPTX connect a new downstream device.
                    if((GET_DP_RX1_HDCP2_AUTH_STATE() != _DP_RX_HDCP2_REPEATER_STATE_IDLE) &&
                       (ScalerDpRx1HdcpCheckValid() == _TRUE))
                    {
                        if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                        {
                            if(GET_DP_TX_HDCP2_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_REAUTH)
                            {
                                ScalerDpRx1SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
                            }
                        }
                        else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                        {
                            if(GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH)
                            {
                                ScalerDpRx1SetHotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
                            }
                        }
                    }
                }
            }

            if((GET_DP_RX1_HDCP2_AUTH_STATE() != _DP_RX_HDCP2_REPEATER_STATE_IDLE) && (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE))
            {
                ScalerDpRx1Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_IDLE);
            }
        }
    }

    switch(GET_DP_RX1_HDCP2_AUTH_STATE())
    {
        case _DP_RX_HDCP2_REPEATER_STATE_IDLE:

            if(GET_DP_RX1_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX1_HDCP2_AUTH_STATE_CHANGE();
                CLR_DP_RX1_HDCP2_AUTH_REPEATER_PROC_TIMEOUT();
                CLR_DP_RX1_HDCP2_AUTH_CPIRQ_TIMRE();
                CLR_DP_RX1_HDCP2_CONTENT_STREAM_MANAGEMENT();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP2_REPEATER_PROC_TIMEOUT);

                SET_DP_RX1_HDCP2_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION);
            }

            if((GET_DP_RX1_HDCP2_MODE() == _ENABLE) && (GET_DP_RX1_HDCP2_REPEATER_CAPABLE() == _TRUE))
            {
                if(GET_DP_RX1_HDCP2_REPEATER_AUTH_1_START() == _TRUE)
                {
                    CLR_DP_RX1_HDCP2_REPEATER_AUTH_1_START();

                    ScalerDpRx1Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_1);
                }
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_1:

            if(GET_DP_RX1_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - Auth 1", 0);

                CLR_DP_RX1_HDCP2_AUTH_STATE_CHANGE();

                if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
                {
                    // Check if downstream device support HDCP2 capability.
                    if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                    {
                        DebugMessageHDCP2("DPRX1 HDCP2 - To DPTX HDCP2", 0);

                        // Issue event to make DPTX start HDCP2 handshake.
                        SET_DP_RX1_HDCP2_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX1_HDCP2_REPEATER_PROC_TIMEOUT);
                    }
                    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                    {
                        DebugMessageHDCP2("DPRX1 HDCP2 - To DPTX HDCP1", 0);

                        // Issue event to make DPTX start HDCP handshake.
                        SET_DP_RX1_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX1_HDCP2_REPEATER_PROC_TIMEOUT);
                    }
                    else
                    {
                        ScalerDpRx1Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_2);
                    }
                }
                else
                {
                    ScalerDpRx1Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_FAKE);
                }
            }

            // Wait for downstream pass event or device/depth max event
            if((GET_DP_TX_HDCP2_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PASS) ||
               (GET_DP_TX_HDCP2_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_EXCEED) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX))
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - TX PASS", 0);

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP2_REPEATER_PROC_TIMEOUT);

                ScalerDpRx1Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_2);
            }
            else if(GET_DP_RX1_HDCP2_AUTH_REPEATER_PROC_TIMEOUT() == _TRUE)
            {
                CLR_DP_RX1_HDCP2_AUTH_REPEATER_PROC_TIMEOUT();

                if((GET_DP_TX_HDCP2_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_TX_HDCP2_VERSION_SUPPORTED() == _TRUE))
                {
                    SET_DP_RX1_HDCP2_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_TIMEOUT);
                }
                else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                {
                    SET_DP_RX1_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT);
                }

                ScalerDpRx1Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_2:

            if(GET_DP_RX1_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - Auth 2", 0);

                CLR_DP_RX1_HDCP2_AUTH_STATE_CHANGE();
            }

            if(GET_DP_RX1_HDCP2_REPEATER_AUTH_2_START() == _TRUE)
            {
                CLR_DP_RX1_HDCP2_REPEATER_AUTH_2_START();

                if(ScalerDpRx1Hdcp2CheckRxInfo() == _TRUE)
                {
                    ScalerDpRx1Hdcp2LoadReceiverIdList();

                    ScalerDpRx1Hdcp2VComputeProc();
                }

                DebugMessageHDCP2("DPRX1 HDCP2 - V Ready", 0);

                // Set V' Ready Bit and Issue CP_IRQ
                ScalerDpRx1CpIRQ(_DP_HDCP2_V_READY);

                ScalerDpRx1Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_FAKE:

            if(GET_DP_RX1_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - Fake", 0);

                CLR_DP_RX1_HDCP2_AUTH_STATE_CHANGE();
            }

            if(GET_DP_RX1_HDCP2_REPEATER_AUTH_2_START() == _TRUE)
            {
                CLR_DP_RX1_HDCP2_REPEATER_AUTH_2_START();

                // Fake Authentication
                ScalerDpRx1Hdcp2FakeAuthenProc();

                // Set V' Ready Bit and Issue CP_IRQ
                ScalerDpRx1CpIRQ(_DP_HDCP2_V_READY);

                ScalerDpRx1Hdcp2ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE:

            if(GET_DP_RX1_HDCP2_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - Done", 0);

                CLR_DP_RX1_HDCP2_AUTH_STATE_CHANGE();
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
void ScalerDpRx1Hdcp2ChangeAuthState(EnumDpRxHdcp2RepeaterAuthState enumHdcp2AuthState)
{
    SET_DP_RX1_HDCP2_AUTH_STATE(enumHdcp2AuthState);
    SET_DP_RX1_HDCP2_AUTH_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Set HDCP2 Repeater Proc Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Hdcp2SetRepeaterProcTimeout(void)
{
    SET_DP_RX1_HDCP2_AUTH_REPEATER_PROC_TIMEOUT();
}

//--------------------------------------------------
// Description  : Check B info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1Hdcp2CheckRxInfo(void)
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

    ScalerDpRx1SetDpcdValue(0x06, 0x93, 0x30, pData[0]);
    ScalerDpRx1SetDpcdValue(0x06, 0x93, 0x31, pData[1]);

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
void ScalerDpRx1Hdcp2LoadReceiverIdList(void)
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

    SET_DP_RX1_AUX_MANUAL_MODE();

    for(pData[1] = 0; pData[1] < 155; pData[1]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x93, (0x45 + pData[1]), g_pucDpTxHdcp2ReceiverIdList[pData[1]]);
    }

    SET_DP_RX1_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1Hdcp2VComputeProc(void)
{
    BYTE pucRxInfo[2] = {0};
    BYTE pucSeqNumV[3] = {0};

    pucRxInfo[0] = ScalerDpRx1GetDpcdInfo(0x06, 0x93, 0x30);
    pucRxInfo[1] = ScalerDpRx1GetDpcdInfo(0x06, 0x93, 0x31);

    // Compute V = HMAC-SHA256(Receiver ID List || RxInfo || seq_num_V, kd)
    if(ScalerHdcp2VprimeCalculate(g_pucDpRx1Hdcp2dKey0, g_pucDpRx1Hdcp2dKey1, g_pucDpTxHdcp2ReceiverIdList, pucRxInfo, pucSeqNumV) == _FALSE)
    {
        return _FALSE;
    }

    SET_DP_RX1_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        // Load MSB of V' into DPCD table
        ScalerDpRx1SetDpcdValue(0x06, 0x93, (0x32 + pData[0]), pucSeqNumV[pData[0]]);
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        // Load MSB of V' into DPCD table
        g_pucDpRx1Hdcp2VPrime[pData[0]] = ScalerGetByte(P63_35_HDCP_SHA_0 + pData[0]);
        ScalerDpRx1SetDpcdValue(0x06, 0x93, (0x35 + pData[0]), g_pucDpRx1Hdcp2VPrime[pData[0]]);
    }

    for(pData[0] = 16; pData[0] < 20; pData[0]++)
    {
        g_pucDpRx1Hdcp2VPrime[pData[0]] = ScalerGetByte(P63_35_HDCP_SHA_0 + pData[0]);
    }

    SET_DP_RX1_AUX_AUTO_MODE();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Fake HDCP Authentication
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1Hdcp2FakeAuthenProc(void)
{
    BYTE pucRxInfo[2] = {0};
    BYTE pucSeqNumV[3] = {0};

    ScalerDpRx1SetDpcdValue(0x06, 0x93, 0x30, pucRxInfo[0]);
    ScalerDpRx1SetDpcdValue(0x06, 0x93, 0x31, pucRxInfo[1]);

    SET_DP_RX1_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x93, (0x45 + pData[0]), g_pucHdcpAksvBackup[pData[0]]);
    }

    for(pData[0] = 0; pData[0] < 150; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x93, (0x4A + pData[0]), 0x00);
    }

    SET_DP_RX1_AUX_AUTO_MODE();

    // Compute V = HMAC-SHA256(Receiver ID List || RxInfo || seq_num_V, kd)
    if(ScalerHdcp2VprimeCalculate(g_pucDpRx1Hdcp2dKey0, g_pucDpRx1Hdcp2dKey1, g_pucHdcpAksvBackup, pucRxInfo, pucSeqNumV) == _FALSE)
    {
        return _FALSE;
    }

    SET_DP_RX1_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        // Load MSB of V' into DPCD table
        ScalerDpRx1SetDpcdValue(0x06, 0x93, (0x35 + pData[0]), ScalerGetByte(P63_35_HDCP_SHA_0 + pData[0]));
    }

    SET_DP_RX1_AUX_AUTO_MODE();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Change DP HDCP2.2 Repeater Capable for Rx1 Base On DPTX Clone Status
// Input Value  : InputPort, PortType, Clone Mode or not
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Hdcp2RepeaterCapableProc(BYTE ucInputPort, BYTE ucPortType)
{
    bit bDPRx1Hdcp2SetRepeater = _OFF;

    if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() != _DP_UNPLUG)
    {
        if((ucPortType == _PORT_DP) && (ucInputPort == _D1_INPUT_PORT))
        {
            bDPRx1Hdcp2SetRepeater = _ON;
        }
    }

    if(bDPRx1Hdcp2SetRepeater != GET_DP_RX1_HDCP2_REPEATER_CAPABLE())
    {
        if(bDPRx1Hdcp2SetRepeater == _ON)
        {
            SET_DP_RX1_HDCP2_REPEATER_CAPABLE();
        }
        else
        {
            CLR_DP_RX1_HDCP2_REPEATER_CAPABLE();
        }

        switch(GET_DP_RX1_HOTPLUG_ASSERT_TYPE())
        {
            case _DP_HPD_NONE:

                if(!((GET_DP_RX1_HDCP_MODE() == _HDCP_14) &&
                     ((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))))
                {
                    if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
                    {
                        ScalerDpRx1CpIRQ(_DP_HDCP2_RXSTATUS_REAUTH_REQ);
                    }
                }

                break;

            case _DP_HPD_ASSERTED:

                if(!((GET_DP_RX1_HDCP_MODE() == _HDCP_14) &&
                     ((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))))
                {
                    if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
                    {
                        ScalerDpRx1CpIRQ(_DP_HDCP2_RXSTATUS_REAUTH_REQ);
                    }
                }

                break;

            default:
                break;
        }
    }
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_D1_DP_EXIST == _ON)
#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)
