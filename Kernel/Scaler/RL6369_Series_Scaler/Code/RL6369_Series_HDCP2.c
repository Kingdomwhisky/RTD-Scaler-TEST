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
// ID Code      : RL6369_Series_HDCP2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6369_SERIES_HDCP2__

#include "ScalerFunctionInclude.h"

#if(_HDCP_2_2_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Define of HDCP 2.2 AES CTRL Type
//--------------------------------------------------
#define _AUTHENTICATE_PROTOCOL                                      0
#define _DECRYPTION_PROTOCOL                                        1


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructHdcp2HDCPAuthInfo g_stRxHdcp2AuthInfo;
StructHdcp2DownLoadKeyType g_stRxHdcpDownLoadKeyType;
BYTE g_ucHdcp2Ctrl;

BYTE g_pucM[16];
BYTE g_pucRtx[8];
BYTE g_pucTxCaps[3];
BYTE g_pucRn[8];
BYTE g_pucSHA256[32];
BYTE g_pucRrx[8];
BYTE g_pucdKey0[16];
BYTE g_pucdKey1[16];
BYTE g_pucKm[16];
BYTE g_pucKh[16];
BYTE g_pucHdcp2SHA256Input[64];
BYTE g_pucHMACSHA256Input[64];
BYTE g_pucHMACSHA256CipherInput[64];
BYTE g_pucHdcp2BackUp[4];
BYTE g_pucKs[16];
BYTE g_pucEDkeyKs[16];
BYTE g_pucRiv[8];
BYTE g_pucInputCipher[16];
BYTE g_pucAESInput[16];
BYTE g_pucAESCipherInput[16];
BYTE g_pucDpHdcp2RrxErrta0[8] = {0x3B, 0xA0,0xBE,0xDE, 0x0C, 0x46, 0xA9, 0x91};
BYTE g_pucDpHdcp2RrxErrta1[8] = {0xE1, 0x7A,0xB0,0xFD, 0x0F, 0x54, 0x40, 0x52};

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerHdcp2Enable_EXINT0(void);
void ScalerHdcp2Initial(void);
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && (_HDMI_PORT_EXIST == _ON))
void ScalerHdcp2ResetTMDSProc(BYTE ucInputPort);
void ScalerHdcp2ReAuthEvent(EnumScalerTimerEventID enumEventID);
#endif
void ScalerHdcp2Handler(void);
BYTE ScalerHdcp2TMDSRxRsaCalculate_EXINT0(void);
void ScalerHdcp2IntHandler_EXINT0(void);
void ScalerHdcp2ResetProc_EXINT0(BYTE ucInputPort);
void ScalerHdcp2DownLoadCalculateKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray, BYTE ucRSAType);
//void ScalerHdcp2DownLoadWriteSRAMValue(BYTE ucSubAddr, BYTE ucLength, BYTE *pReadArray);
void ScalerHdcp2DownLoadWriteSRAMValue_EXINT0(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
void ScalerHdcp2AESCtrl(BYTE ucAESCtrl, BYTE *pucInputArray, BYTE *pucCipherArray);
bit ScalerHdcp2RsaCalculate(BYTE *pucEkpubKmArray);
bit ScalerHdcp2RsaOaepCalculate(void);
bit ScalerHdcp2HMACSHA256Calculate(void);
bit ScalerHdcp2HPrimeCalculate(void);
bit ScalerHdcp2LPrimeCalculate(void);
void ScalerHdcp2DkeyCalculate(BYTE ucDkeyCount);
void ScalerHdcp2SetRdMsgValue(WORD usAddress, BYTE *pucReadArray, WORD usLength);
void ScalerHdcp2SetRdMsgIDCode(BYTE ucValue);
void ScalerHdcp2LargerNumberAddCal(BYTE *pucLargeNumA, BYTE ucNum, BYTE ucLength);
SBYTE ScalerHdcp2LargerNumberCmp(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength);
void ScalerHdcp2LargerNumberABigerBSub(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength);
void ScalerHdcp2LargeNumSubCal(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength);
#endif

void ScalerHdcp2AESCtrl_EXINT0(BYTE ucAESCtrl, BYTE *pucInputArray, BYTE *pucCipherArray);
BYTE ScalerHdcp2RsaCalculate_EXINT0(BYTE *pucEkpubKmArray);
BYTE ScalerHdcp2RsaOaepCalculate_EXINT0(void);
bit ScalerHdcp2SHA256Calculate(BYTE *pucInputArray, BYTE ucCalCount);
BYTE ScalerHdcp2SHA256Calculate_EXINT0(BYTE *pucInputArray, BYTE ucCalCount);
BYTE ScalerHdcp2HMACSHA256Calculate_EXINT0(void);
BYTE ScalerHdcp2HPrimeCalculate_EXINT0(void);
bit ScalerHdcp2RxPairingCalculate(BYTE *pucHdcp2KPriv, BYTE ucIndex);
BYTE ScalerHdcp2LPrimeCalculate_EXINT0(void);
void ScalerHdcp2DkeyCalculate_EXINT0(BYTE ucDkeyCount);
void ScalerHdcp2SetRdMsgValue_EXINT0(WORD usAddress, BYTE *pucReadArray, WORD usLength);
void ScalerHdcp2SetRdMsgIDCode_EXINT0(BYTE ucValue);
void ScalerHdcp2GetRrx_EXINT0(void);
void ScalerHdcp2LargerNumberAddCal_EXINT0(BYTE *pucLargeNumA, BYTE ucNum, BYTE ucLength);
SBYTE ScalerHdcp2LargerNumberCmp_EXINT0(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength);
void ScalerHdcp2LargerNumberABigerBSub_EXINT0(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength);
void ScalerHdcp2LargeNumSubCal_EXINT0(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength);
void ScalerHdcp2RxGenRrx_EXINT0(void);
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 1.4 Switch to HDCP 2.2 (Can't change the enable/disable procedure)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2Enable_EXINT0(void) using 1
{
    WORD usTimeout = 0;

    // set a check duration = 30ms for cover max time(= 20ms)of EDID read duration
    // each loop time = 40us
    for(usTimeout = 0; usTimeout < 750; usTimeout++)
    {
#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC0)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC0)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC0)))
        MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
#endif

#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC1)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC1)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC1)))
        MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
#endif

#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC2)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC2)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC2)))
        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
#endif

        DELAY_40US_EXINT();

#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC0)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC0)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC0)))
        if((MCU_FFE4_DDC0_EDID_IRQ & _BIT2) == _BIT2)
        {
            continue;
        }
#endif

#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC1)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC1)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC1)))

        if((MCU_FFE5_DDC1_EDID_IRQ & _BIT2) == _BIT2)
        {
            continue;
        }
#endif

#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC2)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC2)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC2)))
        if((MCU_FE69_DDC2_EDID_IRQ & _BIT2) == _BIT2)
        {
            continue;
        }
#endif

        break;
    }

    // Detectd DDC non-Toggle or Timeout to Enable HDCP 2.2 Function
    // Enable HDCP 2.2 Module
    ScalerSetBit_EXINT(P63_A0_HDCP_I2C_CTRL_A0, ~_BIT7, _BIT7);

    // Disable HDCP 1.4 Module
    ScalerSetBit_EXINT(P2_C0_HDCP_CR, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2Initial(void)
{
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

    // Enable HDCP 2 Write SRAM Auto Increase Function
    ScalerSetBit(P63_00_HDCP_MSG_CTRL, ~_BIT0, _BIT0);

    if(ScalerGlobalGetIDCode() <= _RL6369_VER_B_ID_CODE)
    {
        // Disable HDCP 2 Read SRAM Auto Increase Function
        ScalerSetBit(P63_03_HDCP_MSGRAP_H, ~_BIT2, 0x00);
    }
    else
    {
        // Enable HDCP 2 Read SRAM Auto Increase Function
        ScalerSetBit(P63_03_HDCP_MSGRAP_H, ~_BIT2, _BIT2);
    }
}

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && (_HDMI_PORT_EXIST == _ON))
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2ResetTMDSProc(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // Disable Read Msg Done IRQ
    ScalerSetBit(P63_C0_HDCP_I2C_CTRL_C0, ~_BIT1, 0x00);

    // Clear Reading Msg Size & Judge REAUTH_REQ Set or not
    ScalerSetBit(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, _BIT0);
    ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_70_PORT_PAGE2_HDCP2_STATUS1, 0x00);

#if(_HDMI_HDCP22_REAUTH_IN_RESET_PROC == _ON)
    if((ScalerGetBit(P63_A0_HDCP_I2C_CTRL_A0, _BIT7) == _BIT7) && (GET_HDCP_2_2_AUTHENTICATION_DONE() == _TRUE))
    {
        ScalerSetDataPortBit(P2_C3_HDCP_AP, _P2_C4_PT_71_PORT_PAGE2_HDCP2_STATUS2, ~(_BIT3 | _BIT1 | _BIT0), _BIT3);
    }
    else
#endif
    {
        ScalerSetDataPortBit(P2_C3_HDCP_AP, _P2_C4_PT_71_PORT_PAGE2_HDCP2_STATUS2, ~(_BIT3 | _BIT1 | _BIT0), 0x00);
    }

    ScalerSetBit(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, 0x00);

    // Reset Authenticated FSM
    ScalerSetByte(P63_A2_HDCP_I2C_CTRL_A2, 0x01);
    ScalerSetBit(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT6, _BIT6);

    // Disable Link Interity Check
    ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_63_PORT_PAGE2_HDMI_PEAC1, ~(_BIT7 | _BIT6), 0x00);

    // Cancel HDCP 2.2 Re-Auth Timer Event
    if(ucInputPort == _D0_INPUT_PORT)
    {
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX0_HDCP2_REAUTH);
#endif
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX1_HDCP2_REAUTH);
#endif
    }
    else if(ucInputPort == _D2_INPUT_PORT)
    {
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH);
#endif
    }

    CLR_HDCP_2_2_AUTHENTICATION_DONE();
    CLR_HDCP_2_2_AKE_INIT_RECEIVED();
    CLR_HDCP_2_2_AKE_NO_STORED_KM_RECEIVED();
    CLR_HDCP_2_2_AKE_STORED_KM_RECEIVED();
    CLR_HDCP_2_2_LC_INIT_RECEIVED();
    CLR_HDCP_2_2_SKE_SEND_EKS_RECEIVED();
    CLR_HDCP_2_2_AUTHENTICATION_ACTIVE();

    // HDCP disable cause AVMute issue enable 1.4 disable 2.2
    ScalerSetBit(P63_A0_HDCP_I2C_CTRL_A0, ~_BIT7, 0x00);
    ScalerSetBit(P2_C0_HDCP_CR, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : HDCP2.2 Re-Auth Timer Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2ReAuthEvent(EnumScalerTimerEventID enumEventID)
{
    if(ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_63_PORT_PAGE2_HDMI_PEAC1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        switch(enumEventID)
        {
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
            case _SCALER_TIMER_EVENT_RX0_HDCP2_REAUTH:

                SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_HDCP_2_2);

                DebugMessageHDCP2("[D0]BCH ERR FOR HPD EVENT", 0);

                break;
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
            case _SCALER_TIMER_EVENT_RX1_HDCP2_REAUTH:

                SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_HDCP_2_2);

                DebugMessageHDCP2("[D1]BCH ERR FOR HPD EVENT", 0);

                break;
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
            case _SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH:

                SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_HDCP_2_2);

                DebugMessageHDCP2("[D2]BCH ERR FOR HPD EVENT", 0);

                break;
#endif

            default:

                break;
        }
    }
}

#endif

//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2Handler(void)
{
    // Receiver Has Received AKE_INIT
    if(GET_HDCP_2_2_AKE_INIT_RECEIVED() == _TRUE)
    {
        CLR_HDCP_2_2_AKE_INIT_RECEIVED();

        DebugMessageHDCP2("AKE_INIT", 0);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)

        g_pucRtx[0] = 0x18;
        g_pucRtx[1] = 0xfa;
        g_pucRtx[2] = 0xe4;
        g_pucRtx[3] = 0x20;
        g_pucRtx[4] = 0x6a;
        g_pucRtx[5] = 0xfb;
        g_pucRtx[6] = 0x51;
        g_pucRtx[7] = 0x49;

        g_pucRrx[0] = 0x3b;
        g_pucRrx[1] = 0xa0;
        g_pucRrx[2] = 0xbe;
        g_pucRrx[3] = 0xde;
        g_pucRrx[4] = 0x0c;
        g_pucRrx[5] = 0x46;
        g_pucRrx[6] = 0xa9;
        g_pucRrx[7] = 0x91;

        g_pucTxCaps[0] = 0x02;
        g_pucTxCaps[1] = 0x00;
        g_pucTxCaps[2] = 0x00;

        g_pucRxCaps[0] = 0x02;
        g_pucRxCaps[1] = 0x00;
        g_pucRxCaps[2] = 0x01;

        // Load Certrx to Read SRAM
        ScalerHdcp2SetRdMsgValue(0x01, g_stRxHdcpDownLoadKeyType.pucHdcp2Certrx, 522);

#endif
    }

    // Receiver Has received AKE_NO_STORED_KM
    if(GET_HDCP_2_2_AKE_NO_STORED_KM_RECEIVED() == _TRUE)
    {
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)

        BYTE pucKpubKm[128];

        memset(pucKpubKm, 0, sizeof(pucKpubKm));

        // Save Transmitter Ekpub[km] to FW
        ScalerSetByte(P63_01_HDCP_MSGWAP, 0x01);

        for(pData[0] = 0; pData[0] < 128; ++pData[0])
        {
            pucKpubKm[pData[0]] = g_stRxHdcp2DownLoadKeyType.pucHdcp2KpubKm[pData[0]];

            DebugMessageHDCP2("Ekpub(km)", pucKpubKm[pData[0]]);
        }

        // Decrypt Ekpub[km]
        if(ScalerHdcp2RsaCalculate(pucKpubKm) == _TRUE)
        {
            // Decrypt Km by FW to Get 128 bit Km
            if(ScalerHdcp2RsaOaepCalculate() == _TRUE)
            {
                ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_0);

                memcpy(g_pucdKey0, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

                ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_1);

                memcpy(g_pucdKey1, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);


                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                {
                    DebugMessageHDCP2("Dkey0", g_pucdKey0[pData[0]]);
                }

                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                {
                    DebugMessageHDCP2("Dkey1", g_pucdKey1[pData[0]]);
                }

                if(ScalerHdcp2HPrimeCalculate() == _TRUE)
                {
                    // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 0x07
                    ScalerHdcp2SetRdMsgIDCode(_HDCP_2_2_AKE_SEND_H_PRIME);

                    memcpy(g_pucSHA256, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

                    for(pData[0] = 0; pData[0] < 32; pData[0]++)
                    {
                        DebugMessageHDCP2("H prime", g_pucSHA256[pData[0]]);
                    }

                    // Load Km to Read SRAM
                    ScalerHdcp2SetRdMsgValue(0x01, g_pucSHA256, 32);

                    // Set Message Size = 0x21
                    ScalerSetBit(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, _BIT0);
                    ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_70_PORT_PAGE2_HDCP2_STATUS1, 0x21);
                    ScalerSetDataPortByte(P2_C3_HDCP_AP, _P2_C4_PT_71_PORT_PAGE2_HDCP2_STATUS2, 0x00);
                    ScalerSetBit(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, 0x00);

                    // Enable HDCP2 Source Read Done IRQ
                    ScalerSetBit(P63_C1_HDCP_I2C_CTRL_C1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetBit(P63_C0_HDCP_I2C_CTRL_C0, ~_BIT1, _BIT1);

                    // Start Pairing AES Calculate
                    for(pData[0] = 0; pData[0] < 16; ++pData[0])
                    {
                        if(pData[0] < 8)
                        {
                            g_pucM[pData[0]] = g_pucRtx[pData[0]];
                        }
                        else
                        {
                            g_pucM[pData[0]] = g_pucRrx[pData[0] - 8];
                        }
                    }

                    // AES Cipher Calculate Ekh[km]
                    ScalerHdcp2AESCtrl(_AUTHENTICATE_PROTOCOL, g_pucM, g_pucKh);

                    // Calculate Ekh[km] = kh AES m XOR Km
                    for(pData[0] = 0; pData[0] < 16; ++pData[0])
                    {
                        g_pucKh[pData[0]] = ScalerGetByte(P63_81_HDCP_AES_OUT_15 + pData[0]) ^ g_pucKm[pData[0]];

                        DebugMessageHDCP2("g_pucKh", g_pucKh[pData[0]]);
                    }
                }
            }
        }
#endif
        CLR_HDCP_2_2_AKE_NO_STORED_KM_RECEIVED();
        CLR_HDCP_2_2_AUTHENTICATION_ACTIVE();

        DebugMessageHDCP2("AKE_NO_STORED_KM", 0);
    }

    if(GET_HDCP_2_2_AKE_STORED_KM_RECEIVED() == _TRUE)
    {
        CLR_HDCP_2_2_AKE_STORED_KM_RECEIVED();

        DebugMessageHDCP2("AKE_STORED_KM", 0);
    }

    if(GET_HDCP_2_2_LC_INIT_RECEIVED() == _TRUE)
    {
        CLR_HDCP_2_2_LC_INIT_RECEIVED();

        DebugMessageHDCP2("LC_INIT", 0);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)

        g_pucRn[0] = 0x32;
        g_pucRn[1] = 0x75;
        g_pucRn[2] = 0x3e;
        g_pucRn[3] = 0xa8;
        g_pucRn[4] = 0x78;
        g_pucRn[5] = 0xa6;
        g_pucRn[6] = 0x38;
        g_pucRn[7] = 0x1c;

        if(ScalerHdcp2LPrimeCalculate() == _TRUE)
        {
            // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 10
            ScalerHdcp2SetRdMsgIDCode(_HDCP_2_2_LC_SEND_L_PRIME);

            memcpy(g_pucSHA256, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

            ScalerHdcp2SetRdMsgValue(0x01, g_pucSHA256, 32);

            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                DebugMessageHDCP2("L Prime", g_pucSHA256[pData[0]]);
            }

            // Set Message Size = 0x21
            ScalerSetBit(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, _BIT0);
            ScalerSetByte(P2_C3_HDCP_AP, 0x70);
            ScalerSetByte(P2_C4_HDCP_DP, 0x21);
            ScalerSetByte(P2_C3_HDCP_AP, 0x71);
            ScalerSetByte(P2_C4_HDCP_DP, 0x00);
            ScalerSetBit(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, 0x00);
        }
#endif
    }

    if(GET_HDCP_2_2_SKE_SEND_EKS_RECEIVED() == _TRUE)
    {
        CLR_HDCP_2_2_SKE_SEND_EKS_RECEIVED();

        DebugMessageHDCP2("SKE_SEND_EKS", 0);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        // Calculate Dkey 2
        ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_2);

        g_pucEDkeyKs[0] = 0x4c;
        g_pucEDkeyKs[1] = 0x32;
        g_pucEDkeyKs[2] = 0x47;
        g_pucEDkeyKs[3] = 0x12;
        g_pucEDkeyKs[4] = 0xc4;
        g_pucEDkeyKs[5] = 0xbe;
        g_pucEDkeyKs[6] = 0xc6;
        g_pucEDkeyKs[7] = 0x69;
        g_pucEDkeyKs[8] = 0x0a;
        g_pucEDkeyKs[9] = 0xc2;
        g_pucEDkeyKs[10] = 0x19;
        g_pucEDkeyKs[11] = 0x64;
        g_pucEDkeyKs[12] = 0xde;
        g_pucEDkeyKs[13] = 0x91;
        g_pucEDkeyKs[14] = 0xf1;
        g_pucEDkeyKs[15] = 0x83;

        g_pucRiv[0] = 0x40;
        g_pucRiv[1] = 0x2b;
        g_pucRiv[2] = 0x6b;
        g_pucRiv[3] = 0x43;
        g_pucRiv[4] = 0xc5;
        g_pucRiv[5] = 0xe8;
        g_pucRiv[6] = 0x86;
        g_pucRiv[7] = 0xd8;

        // Decode Ks
        for(pData[0] = 0; pData[0] < 8; ++pData[0])
        {
            g_pucKs[pData[0]] = g_pucEDkeyKs[pData[0]] ^ ScalerGetByte((P63_81_HDCP_AES_OUT_15 + pData[0]));
        }

        for(pData[0] = 8; pData[0] < 16; ++pData[0])
        {
            g_pucKs[pData[0]] = g_pucEDkeyKs[pData[0]] ^ (ScalerGetByte((P63_81_HDCP_AES_OUT_15 + pData[0])) ^ g_pucRrx[pData[0] - 8]);
        }


        for(pData[0] = 0; pData[0] < 16; pData[0]++)
        {
            DebugMessageHDCP2("Ks", g_pucKs[pData[0]]);
        }

        SET_HDCP_2_2_AUTHENTICATION_DONE();

        // Enable HDMI Link Integrity Check
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_63_PORT_PAGE2_HDMI_PEAC1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        SET_HDCP_2_2_AUTH_STATE(_HDCP_2_2_STATE_AUTHENTICATED);

        // Enable Decryption
        for(pData[0] = 0; pData[0] < 16; ++pData[0])
        {
            g_pucInputCipher[pData[0]] = g_pucKs[pData[0]] ^ g_stRxHdcpDownLoadKeyType.pucHdcp2Lc[pData[0]];
        }

        // Enable AES Decryption Cipher
        ScalerHdcp2AESCtrl(_DECRYPTION_PROTOCOL, g_pucRiv, g_pucInputCipher);
#endif
    }

    if(GET_HDCP_2_2_AUTHENTICATION_DONE() == _TRUE)
    {
        // Check BCH Error or Not
        if(ScalerGetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_63_PORT_PAGE2_HDMI_PEAC1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear BCH Error Flag
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_63_PORT_PAGE2_HDMI_PEAC1, ~_BIT6, _BIT6);

            // Clear Authentication Done Flag
            CLR_HDCP_2_2_AUTHENTICATION_DONE();

            DebugMessageHDCP2("REAUTH_REQ", 0);

            // Set HDCP 2.2 Authentication State = UnAuthenticated
            SET_HDCP_2_2_AUTH_STATE(_HDCP_2_2_STATE_UNAUTHENTICATED);

            // Set RxStatus REAUTH_REQ
            ScalerSetBit(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, _BIT0);
            ScalerSetDataPortBit(P2_C3_HDCP_AP, _P2_C4_PT_71_PORT_PAGE2_HDCP2_STATUS2, ~_BIT3, _BIT3);
            ScalerSetBit(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, 0x00);

            // Active HDCP 2.2 Re-Auth Timer Event for HPD Trigger Event Usage
            if(CHECK_TMDS_DPHY_SWITCH(_D0_INPUT_PORT) == _TRUE)
            {
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
                ScalerTimerActiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_RX0_HDCP2_REAUTH);
#endif
            }
            else if(CHECK_TMDS_DPHY_SWITCH(_D1_INPUT_PORT) == _TRUE)
            {
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
                ScalerTimerActiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_RX1_HDCP2_REAUTH);
#endif
            }
            else if(CHECK_TMDS_DPHY_SWITCH(_D2_INPUT_PORT) == _TRUE)
            {
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
                ScalerTimerActiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH);
#endif
            }
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Calculate in INT
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
BYTE ScalerHdcp2TMDSRxRsaCalculate_EXINT0(void) using 1
{
    BYTE pucHdcp2KpubKm[128];
    BYTE ucIndex = 0;

    // Save Transmitter Ekpub[km] to FW
    ScalerSetByte_EXINT(P63_01_HDCP_MSGWAP, 0x01);

    for(ucIndex = 0; ucIndex < 128; ++ucIndex)
    {
        pucHdcp2KpubKm[ucIndex] = ScalerGetByte_EXINT(P63_02_HDCP_MSGWDP);
    }

    // Decrypt Ekpub[km]
    return (ScalerHdcp2RsaCalculate_EXINT0(pucHdcp2KpubKm) == _TRUE);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Int Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2IntHandler_EXINT0(void) using 1
{
    // Backup W/R Sram & HDCP Port Addr.
    g_pucHdcp2BackUp[0] = ScalerGetByte_EXINT(P63_01_HDCP_MSGWAP);
    g_pucHdcp2BackUp[1] = ScalerGetByte_EXINT(P63_03_HDCP_MSGRAP_H);
    g_pucHdcp2BackUp[2] = ScalerGetByte_EXINT(P63_04_HDCP_MSGRAP_L);
    g_pucHdcp2BackUp[3] = ScalerGetByte_EXINT(P2_C3_HDCP_AP);

    // Detect HDCP 2.2 Write Message Done IRQ
    if((ScalerGetBit_EXINT(P63_C0_HDCP_I2C_CTRL_C0, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P63_C1_HDCP_I2C_CTRL_C1, _BIT0) == _BIT0))
    {
        // Clear HDCP 2.2 Write Message Done Flag
        ScalerSetBit_EXINT(P63_C1_HDCP_I2C_CTRL_C1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        // Judge HDCP Switch to 2.2 Mode or not
        if((ScalerGetBit_EXINT(P63_A0_HDCP_I2C_CTRL_A0, _BIT7) == 0x00) && (ScalerGetBit_EXINT(P2_C0_HDCP_CR, _BIT0) == _BIT0))
        {
            ScalerHdcp2Enable_EXINT0();
        }

        ScalerSetByte_EXINT(P63_01_HDCP_MSGWAP, 0x00);

        // Detect HDCP 2.2 Transmitter Write AKE_Init Message, Message ID = 2
        switch(ScalerGetByte_EXINT(P63_02_HDCP_MSGWDP))
        {
            case _HDCP_2_2_AKE_INIT:

                // HDCP2 Reset Proc
                ScalerHdcp2ResetProc_EXINT0(_D0_INPUT_PORT);

                // Save Transmitter Rtx to FW
                ScalerHdcp2DownLoadWriteSRAMValue_EXINT0(0x01, 8, g_pucRtx);

                // Save TxCaps to FW
                ScalerHdcp2DownLoadWriteSRAMValue_EXINT0(0x09, 3, g_pucTxCaps);

                // Generate the psudo-random key of Rrx
                ScalerHdcp2RxGenRrx_EXINT0();

                // Load Certrx to Read SRAM
                ScalerHdcp2SetRdMsgValue_EXINT0(0x01, g_stRxHdcpDownLoadKeyType.pucHdcp2Certrx, 522);

                // Load Rrx to Read SRAM
                ScalerHdcp2SetRdMsgValue_EXINT0(0x020B, g_pucRrx, 8);

                // Load RxCaps HDCP 2.2 Support to Read SRAM
                ScalerHdcp2SetRdMsgValue_EXINT0(0x0213, g_pucRxCaps, 3);

                // Load Message ID = 3
                ScalerHdcp2SetRdMsgIDCode_EXINT0(_HDCP_2_2_AKE_SEND_CERT);

                // Set AKE_SEND_CERT Message Size = 534
                ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, _BIT0);
                ScalerSetByte_EXINT(P2_C3_HDCP_AP, 0x70);
                ScalerSetByte_EXINT(P2_C4_HDCP_DP, 0x16);
                ScalerSetByte_EXINT(P2_C3_HDCP_AP, 0x71);
                ScalerSetByte_EXINT(P2_C4_HDCP_DP, 0x02);
                ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, 0x00);

                SET_HDCP_2_2_AKE_INIT_RECEIVED();

                break;

            case _HDCP_2_2_AKE_NO_STORED_KM:

                SET_HDCP_2_2_AKE_NO_STORED_KM_RECEIVED();
                SET_HDCP_2_2_AUTHENTICATION_ACTIVE();

                // Decrypt Ekpub[km]
                if(ScalerHdcp2TMDSRxRsaCalculate_EXINT0() == _TRUE)
                {
                    // Decrypt Km by FW to Get 128 bit Km
                    if(ScalerHdcp2RsaOaepCalculate_EXINT0() == _TRUE)
                    {
                        ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_0);

                        memcpy(g_pucdKey0, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

                        ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_1);

                        memcpy(g_pucdKey1, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

                        if(ScalerHdcp2HPrimeCalculate_EXINT0() == _TRUE)
                        {
                            // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 0x07
                            ScalerHdcp2SetRdMsgIDCode_EXINT0(_HDCP_2_2_AKE_SEND_H_PRIME);

                            memcpy(g_pucSHA256, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

                            // Load Km to Read SRAM
                            ScalerHdcp2SetRdMsgValue_EXINT0(0x01, g_pucSHA256, 32);

                            // Set Message Size = 0x21
                            ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, _BIT0);
                            ScalerSetByte_EXINT(P2_C3_HDCP_AP, 0x70);
                            ScalerSetByte_EXINT(P2_C4_HDCP_DP, 0x21);
                            ScalerSetByte_EXINT(P2_C3_HDCP_AP, 0x71);
                            ScalerSetByte_EXINT(P2_C4_HDCP_DP, 0x00);
                            ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, 0x00);

                            // Enable HDCP2 Source Read Done IRQ
                            ScalerSetBit_EXINT(P63_C1_HDCP_I2C_CTRL_C1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                            ScalerSetBit_EXINT(P63_C0_HDCP_I2C_CTRL_C0, ~_BIT1, _BIT1);
                        }
                    }
                }

                // Set HDCP 2.2 State to Compute Km
                SET_HDCP_2_2_AUTH_STATE(_HDCP_2_2_STATE_COMPUTE_KM);

                break;

            case _HDCP_2_2_AKE_STORED_KM:

                // Save Ekh[km] From Transmitter to FW
                ScalerHdcp2DownLoadWriteSRAMValue_EXINT0(0x01, 16, g_pucKm);

                // Save m From Transmitter to FW
                ScalerHdcp2DownLoadWriteSRAMValue_EXINT0(0x11, 16, g_pucM);

                // Calculate Km use AES Cipher, Input Value = m, Input Cipher = Kh
                ScalerHdcp2AESCtrl_EXINT0(_AUTHENTICATE_PROTOCOL, g_pucM, g_pucKh);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 0x10; ++pData_EXINT[0])
                {
                    g_pucKm[pData_EXINT[0]] = g_pucKm[pData_EXINT[0]] ^ ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate DKey0
                ScalerHdcp2DkeyCalculate_EXINT0(0);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucdKey0[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate Dkey1
                ScalerHdcp2DkeyCalculate_EXINT0(1);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucdKey1[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate H'
                if(ScalerHdcp2HPrimeCalculate_EXINT0() == _TRUE)
                {
                    // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 0x07
                    ScalerHdcp2SetRdMsgIDCode_EXINT0(_HDCP_2_2_AKE_SEND_H_PRIME);

                    for(pData_EXINT[2] = 0; pData_EXINT[2] < 32; pData_EXINT[2]++)
                    {
                        g_pucSHA256[pData_EXINT[2]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[2]);
                    }

                    ScalerHdcp2SetRdMsgValue_EXINT0(0x01, g_pucSHA256, 32);

                    // Set Message Size = 0x21
                    ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, _BIT0);
                    ScalerSetByte_EXINT(P2_C3_HDCP_AP, 0x70);
                    ScalerSetByte_EXINT(P2_C4_HDCP_DP, 0x21);
                    ScalerSetByte_EXINT(P2_C3_HDCP_AP, 0x71);
                    ScalerSetByte_EXINT(P2_C4_HDCP_DP, 0x00);
                    ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, 0x00);
                }

                SET_HDCP_2_2_AKE_STORED_KM_RECEIVED();

                // Set HDCP 2.2 State to Compute Km
                SET_HDCP_2_2_AUTH_STATE(_HDCP_2_2_STATE_COMPUTE_KM);

                break;

            case _HDCP_2_2_LC_INIT:

                // Save Transmitter Rn to FW
                ScalerHdcp2DownLoadWriteSRAMValue_EXINT0(0x01, 8, g_pucRn);

                if(ScalerHdcp2LPrimeCalculate_EXINT0() == _TRUE)
                {
                    // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 10
                    ScalerHdcp2SetRdMsgIDCode_EXINT0(_HDCP_2_2_LC_SEND_L_PRIME);

                    for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
                    {
                        g_pucSHA256[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[0]);
                    }

                    ScalerHdcp2SetRdMsgValue_EXINT0(0x01, g_pucSHA256, 32);

                    // Set Message Size = 0x21
                    ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, _BIT0);
                    ScalerSetByte_EXINT(P2_C3_HDCP_AP, 0x70);
                    ScalerSetByte_EXINT(P2_C4_HDCP_DP, 0x21);
                    ScalerSetByte_EXINT(P2_C3_HDCP_AP, 0x71);
                    ScalerSetByte_EXINT(P2_C4_HDCP_DP, 0x00);
                    ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, 0x00);
                }

                SET_HDCP_2_2_LC_INIT_RECEIVED();

                // Set HDCP 2.2 State to Compute L'
                SET_HDCP_2_2_AUTH_STATE(_HDCP_2_2_STATE_COMPUTE_L_PRIME);

                break;

            case _HDCP_2_2_SKE_SEND_EKS:

                // Calculate Dkey 2
                ScalerHdcp2DkeyCalculate_EXINT0(2);

                // Save EDkeyKs from Write SRAM to FW
                ScalerHdcp2DownLoadWriteSRAMValue_EXINT0(0x01, 16, g_pucEDkeyKs);

                // Save Riv from Write SRAM to FW
                ScalerHdcp2DownLoadWriteSRAMValue_EXINT0(0x11, 8, g_pucRiv);

                // Decode Ks
                for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; ++pData_EXINT[0])
                {
                    g_pucKs[pData_EXINT[0]] = g_pucEDkeyKs[pData_EXINT[0]] ^ ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]));
                }

                for(pData_EXINT[0] = 8; pData_EXINT[0] < 16; ++pData_EXINT[0])
                {
                    g_pucKs[pData_EXINT[0]] = g_pucEDkeyKs[pData_EXINT[0]] ^ (ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + pData_EXINT[0])) ^ g_pucRrx[pData_EXINT[0] - 8]);
                }

                SET_HDCP_2_2_AUTHENTICATION_DONE();

                // Enable HDMI Link Integrity Check
                ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_63_PORT_PAGE2_HDMI_PEAC1);
                pData_EXINT[0] = ((ScalerGetByte_EXINT(P2_CA_HDMI_DP) & (~_BIT7)) | _BIT7 | _BIT6);
                ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_63_PORT_PAGE2_HDMI_PEAC1);
                ScalerSetByte_EXINT(P2_CA_HDMI_DP, pData_EXINT[0]);

                SET_HDCP_2_2_AUTH_STATE(_HDCP_2_2_STATE_AUTHENTICATED);

                // Enable Decryption
                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; ++pData_EXINT[0])
                {
                    g_pucInputCipher[pData_EXINT[0]] = g_pucKs[pData_EXINT[0]] ^ g_stRxHdcpDownLoadKeyType.pucHdcp2Lc[pData_EXINT[0]];
                }

                // Enable AES Decryption Cipher
                ScalerHdcp2AESCtrl_EXINT0(_DECRYPTION_PROTOCOL, g_pucRiv, g_pucInputCipher);

                SET_HDCP_2_2_SKE_SEND_EKS_RECEIVED();

                break;

            default:
                break;
        }
    }

    // Source Has Read Msg Done IRQ
    if((ScalerGetBit_EXINT(P63_C0_HDCP_I2C_CTRL_C0, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P63_C1_HDCP_I2C_CTRL_C1, _BIT1) == _BIT1))
    {
        // Clear Read Msg Done Flag
        ScalerSetBit_EXINT(P63_C1_HDCP_I2C_CTRL_C1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

        // Disable Read Msg Done IRQ
        ScalerSetBit_EXINT(P63_C0_HDCP_I2C_CTRL_C0, ~_BIT1, 0x00);

        // Start Pairing AES Calculate
        for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; ++pData_EXINT[0])
        {
            if(pData_EXINT[0] < 8)
            {
                g_pucM[pData_EXINT[0]] = g_pucRtx[pData_EXINT[0]];
            }
            else
            {
                g_pucM[pData_EXINT[0]] = g_pucRrx[pData_EXINT[0] - 8];
            }
        }

        // AES Cipher Calculate Ekh[km]
        ScalerHdcp2AESCtrl_EXINT0(_AUTHENTICATE_PROTOCOL, g_pucM, g_pucKh);

        // Calculate Ekh[km] = kh AES m XOR Km
        for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; ++pData_EXINT[0])
        {
            g_pucKh[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]) ^ g_pucKm[pData_EXINT[0]];
        }

        ScalerHdcp2SetRdMsgValue_EXINT0(0x01, g_pucKh, 16);

        // Load AKE Send Pairing Info
        ScalerHdcp2SetRdMsgIDCode_EXINT0(_HDCP_2_2_AKE_SEND_PAIRING_INFO);

        // Set Message Size = 0x11
        ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, _BIT0);
        ScalerSetByte_EXINT(P2_C3_HDCP_AP, 0x70);
        ScalerSetByte_EXINT(P2_C4_HDCP_DP, 0x11);
        ScalerSetByte_EXINT(P2_C3_HDCP_AP, 0x71);
        ScalerSetByte_EXINT(P2_C4_HDCP_DP, 0x00);
        ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, 0x00);
    }

    // Recover Backup for  W/R Sram & HDCP Port Addr.
    ScalerSetByte_EXINT(P63_01_HDCP_MSGWAP, g_pucHdcp2BackUp[0]);
    ScalerSetByte_EXINT(P63_03_HDCP_MSGRAP_H, g_pucHdcp2BackUp[1]);
    ScalerSetByte_EXINT(P63_04_HDCP_MSGRAP_L, g_pucHdcp2BackUp[2]);
    ScalerSetByte_EXINT(P2_C3_HDCP_AP, g_pucHdcp2BackUp[3]);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2ResetProc_EXINT0(BYTE ucInputPort) using 1
{
    ucInputPort = ucInputPort;

    // Disable Read Msg Done IRQ
    ScalerSetBit_EXINT(P63_C0_HDCP_I2C_CTRL_C0, ~_BIT1, 0x00);

    // Clear Reading Msg Size & RxStatus REAUTH_REQ
    ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, _BIT0);
    ScalerSetByte_EXINT(P2_C3_HDCP_AP, _P2_C4_PT_70_PORT_PAGE2_HDCP2_STATUS1);
    ScalerSetByte_EXINT(P2_C4_HDCP_DP, 0x00);
    ScalerSetByte_EXINT(P2_C3_HDCP_AP, _P2_C4_PT_71_PORT_PAGE2_HDCP2_STATUS2);
    ScalerSetBit_EXINT(P2_C4_HDCP_DP, ~(_BIT3 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P63_E0_HDCP_I2C_DUMMY_0, ~_BIT0, 0x00);

    // Disable Link Interity Check
    ScalerSetByte_EXINT(P2_C9_HDMI_AP, _P2_CA_PT_63_PORT_PAGE2_HDMI_PEAC1);
    ScalerSetBit_EXINT(P2_CA_HDMI_DP, ~(_BIT7 | _BIT6), 0x00);

    // Reset Authenticated FSM
    ScalerSetByte_EXINT(P63_A2_HDCP_I2C_CTRL_A2, 0x01);
    ScalerSetBit_EXINT(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT6, _BIT6);

    // Cancel HDCP 2.2 Re-Auth Timer Event
    if(ucInputPort == _D0_INPUT_PORT)
    {
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX0_HDCP2_REAUTH);
#endif
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX1_HDCP2_REAUTH);
#endif
    }
    else if(ucInputPort == _D2_INPUT_PORT)
    {
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH);
#endif
    }

    CLR_HDCP_2_2_AUTHENTICATION_DONE();
    CLR_HDCP_2_2_AKE_INIT_RECEIVED();
    CLR_HDCP_2_2_AKE_NO_STORED_KM_RECEIVED();
    CLR_HDCP_2_2_AKE_STORED_KM_RECEIVED();
    CLR_HDCP_2_2_LC_INIT_RECEIVED();
    CLR_HDCP_2_2_SKE_SEND_EKS_RECEIVED();
    CLR_HDCP_2_2_AUTHENTICATION_ACTIVE();
}


//--------------------------------------------------------------------------------------------------------------------------
// Description  : HDCP 2.2 Down Load RSA Key
// Input Value  : usSubAddr == > start address, usLength == > key Length,
//                pReadArray == > Key Array, ucRSAType == > Key Type
// Output Value : None
//--------------------------------------------------------------------------------------------------------------------------
void ScalerHdcp2DownLoadCalculateKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray, BYTE ucRSAType)
{
    switch(ucRSAType)
    {
        case _HDCP_2_2_RSA_D_KEY:

            memcpy(&g_stRxHdcpDownLoadKeyType.pucHdcp2DKey[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP_2_2_RSA_RRMODN_KEY:

            memcpy(&g_stRxHdcpDownLoadKeyType.pucHdcp2Rrmodn[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP_2_2_RSA_N_PINV:

            memcpy(&g_stRxHdcpDownLoadKeyType.pucHdcp2Npinv[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP_2_2_CERT_RX:

            memcpy(&g_stRxHdcpDownLoadKeyType.pucHdcp2Certrx[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP_2_2_LC:

            memcpy(&g_stRxHdcpDownLoadKeyType.pucHdcp2Lc[usSubAddr], pucReadArray, usLength);

            break;

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        case _HDCP_2_2_KPUB_KM:

            memcpy(&g_stRxHdcpDownLoadKeyType.pucHdcp2KpubKm[usSubAddr], pucReadArray, usLength);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Down Load Value
// Input Value  : usSubAddr == > start address, usLength == > key Length,
//                pReadArray == > Key Array
// Output Value : None
//--------------------------------------------------
//void ScalerHdcp2DownLoadWriteSRAMValue(BYTE ucSubAddr, BYTE ucLength, BYTE *pReadArray)
//{
//    // Load Value To FW
//    ScalerSetByte(P63_01_HDCP_MSGWAP, ucSubAddr);
//
//    for(pData[0] = ucSubAddr; pData[0] < (ucSubAddr + ucLength); pData[0]++)
//    {
//        pReadArray[pData[0] - ucSubAddr] = ScalerGetByte(P63_02_HDCP_MSGWDP);
//    }
//}

//--------------------------------------------------
// Description  : HDCP 2.2 Down Load Value in INT
// Input Value  : usSubAddr == > start address, usLength == > key Length,
//                pReadArray == > Key Array
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2DownLoadWriteSRAMValue_EXINT0(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray) using 1
{
    ScalerSetByte_EXINT(P63_01_HDCP_MSGWAP, ucSubAddr);

    // Load Value To FW
    for(pData_EXINT[0] = ucSubAddr; pData_EXINT[0] < (ucSubAddr + ucLength); pData_EXINT[0]++)
    {
        pucReadArray[pData_EXINT[0] - ucSubAddr] = ScalerGetByte_EXINT(P63_02_HDCP_MSGWDP);
    }
}

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 AES Ctrl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2AESCtrl(BYTE ucAESCtrl, BYTE *pucInputArray, BYTE *pucCipherArray)
{
    switch(ucAESCtrl)
    {
        case _AUTHENTICATE_PROTOCOL:

            // HDCP 2.2 Reset
            ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, 0x00);
            ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

            // Set bit 7: AES FW Mode, bit6: AES FW Enable, bit5: AES Random Disable bit 4:3: Reference Xtal Clock
            ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

            // Load Input Value
            for(pData[0] = 0; pData[0] < 16; pData[0]++)
            {
                ScalerSetByte((P63_61_HDCP_AES_DATA_IN_15 + pData[0]), pucInputArray[pData[0]]);

                ScalerSetByte((P63_71_HDCP_AES_CIPHER_KEY_15 + pData[0]), pucCipherArray[pData[0]]);
            }

            // Start AES Calculation
            ScalerSetBit(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

            ScalerTimerDelayXms(2);

            break;

        case _DECRYPTION_PROTOCOL:

            memcpy((volatile BYTE xdata *)P63_71_HDCP_AES_CIPHER_KEY_15, pucCipherArray, 16);

            // Set bit 7: AES FW Mode , bit6: AES FW Enable , bit5: AES Random Disable bit 4:3: Reference HDMI Clock
            ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT4);

            if(ScalerGlobalGetIDCode() <= _RL6369_VER_B_ID_CODE)
            {
                memcpy((volatile BYTE xdata *)P63_AB_HDCP_I2C_CTRL_RIV3, pucInputArray, 4);
                memcpy((volatile BYTE xdata *)P63_A7_HDCP_I2C_CTRL_RIV7, (pucInputArray + 4), 4);
            }
            else
            {
                memcpy((volatile BYTE xdata *)P63_A7_HDCP_I2C_CTRL_RIV7, pucInputArray, 8);
            }

            // Riv from FW
            ScalerSetBit(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT7, _BIT7);

            // Start AES Calculation
            ScalerSetBit(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

            // Set HW to Authenticated State
            ScalerSetByte(P63_A2_HDCP_I2C_CTRL_A2, 0x10);
            ScalerSetBit(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT6, _BIT6);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RsaCalculate(BYTE *pucEkpubKmArray)
{
    // Enable HDCP 2.2 RSA Module
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));

    // Select RSA Key Download Data Length
    ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT7);

    // Load Ekpub[km] to RSA Module as cipher text
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Enable write cipher text to RSA Module
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (15 - (BYTE)pData[0]));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEkpubKmArray[pData[0] << 3], 8);
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load RRmodN
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x10 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcpDownLoadKeyType.pucHdcp2Rrmodn[pData[0] << 3], 8);
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load N Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcpDownLoadKeyType.pucHdcp2Certrx[(pData[0] << 3) + 5], 8);
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load D Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x40 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcpDownLoadKeyType.pucHdcp2DKey[pData[0] << 3], 8);
    }

    // Load Npinv to RSA Module
    memcpy((volatile BYTE xdata *)P63_12_HDCP_RSA_NP_INV_3, &g_stRxHdcpDownLoadKeyType.pucHdcp2Npinv, 4);

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
// Description  : HDCP 2.2 RSA Oaep Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RsaOaepCalculate(void)
{
    BYTE pucSHA256Input[64];
    BYTE pucRsaOaepInput[128];

    // Read Out RSA Message
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5), _BIT6);

    if((bit)ScalerGetBit(P63_92_HDCP_DUMMY1, _BIT7) != (bit)ScalerGetBit(P63_10_HDCP_RSA_CTRL0, _BIT1))
    {
        // Read Message From One of 2 Address
        if(ScalerGetBit(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
        {
            for(pData[0] = 0; pData[0] < 16; pData[0]++)
            {
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x10 | pData[0]));
                memcpy(&pucRsaOaepInput[(15 - pData[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
            }
        }
        else
        {
            for(pData[0] = 0; pData[0] < 16; pData[0]++)
            {
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, pData[0]);
                memcpy(&pucRsaOaepInput[(15 - pData[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
            }
        }
    }
    else
    {
        // Read RSA Output from 0x6310[1] Address, low 64bit
        if(ScalerGetBit(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, 0x00);
            memcpy(&pucSHA256Input[0], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
        else
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, 0x10);
            memcpy(&pucSHA256Input[0], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }

        // Read N low 64bit
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, 0x30);
        memcpy(&pucRsaOaepInput[0], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);

        // RSA output low 64 bit - N low 64 bit
        ScalerHdcp2LargeNumSubCal(pucSHA256Input, pucRsaOaepInput, 8);

        memcpy(&pucRsaOaepInput[120], &pucSHA256Input[0], 8);

        // Read RSA Output from 0x6392[7] Address
        if(ScalerGetBit(P63_92_HDCP_DUMMY1, _BIT7) == 0x00)
        {
            for(pData[0] = 1; pData[0] < 16; pData[0]++)
            {
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, pData[0]);
                memcpy(&pucRsaOaepInput[(15 - pData[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
            }
        }
        else
        {
            for(pData[0] = 1; pData[0] < 16; pData[0]++)
            {
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x10 | pData[0]));
                memcpy(&pucRsaOaepInput[(15 - pData[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
            }
        }
    }

    // Calculate First Block 512 Bit SHA256 Calculate, Calculate MGF(maskDB, 32)
    if(ScalerHdcp2SHA256Calculate(&pucRsaOaepInput[33], 0) == _TRUE)
    {
        // Load Second Block 512 Bit Data
        memcpy(pucSHA256Input, &pucRsaOaepInput[97], 31);
        memset(&pucSHA256Input[31], 0, 33);
        pucSHA256Input[35] = 0x80;
        pucSHA256Input[62] = 0x03;
        pucSHA256Input[63] = 0x18;

        // Calculate Second Block 512 Bit Data
        if(ScalerHdcp2SHA256Calculate(pucSHA256Input, 1) == _TRUE)
        {
            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                pucSHA256Input[pData[0]] = pucRsaOaepInput[1 + pData[0]] ^ ScalerGetByte((P63_35_HDCP_SHA_0 + pData[0]));
            }

            memset(&pucSHA256Input[32], 0, 32);
            pucSHA256Input[36] = 0x80;
            pucSHA256Input[62] = 0x01;
            pucSHA256Input[63] = 0x20;

            // Calculte MGF(Seed, 95), Seed = 32 byte SHA256 output + C 0x0000000x + 0x80 + Stream Length
            pucSHA256Input[35] = 0;
            ScalerHdcp2SHA256Calculate(pucSHA256Input, 0);
            pucSHA256Input[35] = 1;
            ScalerHdcp2SHA256Calculate(pucSHA256Input, 0);
            pucSHA256Input[35] = 2;
            ScalerHdcp2SHA256Calculate(pucSHA256Input, 0);

            // DB maskDB XOR DBmask
            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                pucSHA256Input[pData[0]] = pucRsaOaepInput[33 + pData[0] + 64] ^ ScalerGetByte((P63_35_HDCP_SHA_0 + pData[0]));
            }

            pucSHA256Input[31] = ScalerGetByte((P63_35_HDCP_SHA_0 + 31));

            for(pData[0] = 0; pData[0] < 16; pData[0]++)
            {
                DebugMessageHDCP2("Km", pucSHA256Input[pData[0] + 15]);
            }

            if(pucSHA256Input[14] == 0x01)
            {
                memcpy(g_pucKm, &pucSHA256Input[15], 16);

                return _TRUE;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 HMACSHA 256 Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2HMACSHA256Calculate(void)
{
    for(pData[0] = 0; pData[0] < 64; pData[0]++)
    {
        // K0 XOR ipad = 512 bit
        g_pucHMACSHA256CipherInput[pData[0]] = g_pucHMACSHA256CipherInput[pData[0]] ^ 0x36;
    }

    // Calculate SHA256((K0 XOR ipad) || text)
    if(ScalerHdcp2SHA256Calculate(g_pucHMACSHA256CipherInput, 0) == _TRUE)
    {
        if(ScalerHdcp2SHA256Calculate(g_pucHMACSHA256Input, 1) == _TRUE)
        {
            // KO XOR opad
            for(pData[0] = 0; pData[0] < 64; pData[0]++)
            {
                g_pucHMACSHA256CipherInput[pData[0]] = (g_pucHMACSHA256CipherInput[pData[0]] ^ 0x36) ^ 0x5C;
            }

            memcpy(g_pucHMACSHA256Input, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);
            memset(&g_pucHMACSHA256Input[32], 0, 32);
            g_pucHMACSHA256Input[32] = 0x80;
            g_pucHMACSHA256Input[62] = 0x03;

            // SHA256((KO XOR opad) || SHA256(KO XOR ipad) || text)
            if(ScalerHdcp2SHA256Calculate(g_pucHMACSHA256CipherInput, 0) == _TRUE)
            {
                if(ScalerHdcp2SHA256Calculate(g_pucHMACSHA256Input, 1) == _TRUE)
                {
                    return _TRUE;
                }
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Hprime Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2HPrimeCalculate(void)
{
    // H = HMAC-SHA256(rtx || RxCaps || TxCaps, kd)
    // HMAC(text) = HMAC(K, text) = SHA256((K0 XOR opad) || SHA256((KO XOR ipad) || text))
    // Calculate SHA256((KO XOR ipad) || text)

    memcpy(g_pucHMACSHA256CipherInput, g_pucdKey0, 16);
    memcpy(&g_pucHMACSHA256CipherInput[16], g_pucdKey1, 16);
    memcpy(g_pucHMACSHA256Input, g_pucRtx, 8);
    memcpy(&g_pucHMACSHA256Input[8], g_pucRxCaps, 3);
    memcpy(&g_pucHMACSHA256Input[11], g_pucTxCaps, 3);
    g_pucHMACSHA256Input[14] = 0x80;
    memset(&g_pucHMACSHA256Input[15], 0, 47);
    g_pucHMACSHA256Input[62] = 0x02;
    g_pucHMACSHA256Input[63] = 0x70;

    memset(&g_pucHMACSHA256CipherInput[32], 0, 32);

    if(ScalerHdcp2HMACSHA256Calculate() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Lprime Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2LPrimeCalculate(void)
{
    memcpy(g_pucHMACSHA256CipherInput, g_pucdKey0, 16);

    for(pData[0] = 16; pData[0] < 32; pData[0]++)
    {
        g_pucHMACSHA256CipherInput[pData[0]] = g_pucdKey1[pData[0] - 16];

        if(pData[0] > 23)
        {
            g_pucHMACSHA256CipherInput[pData[0]] = g_pucHMACSHA256CipherInput[pData[0]] ^ g_pucRrx[pData[0] - 24];
        }
    }

    memset(&g_pucHMACSHA256CipherInput[32], 0, 32);
    memcpy(g_pucHMACSHA256Input, g_pucRn, 8);
    g_pucHMACSHA256Input[8] = 0x80;
    memset(&g_pucHMACSHA256Input[9], 0, 53);
    g_pucHMACSHA256Input[62] = 0x02;
    g_pucHMACSHA256Input[63] = 0x40;

    if(ScalerHdcp2HMACSHA256Calculate() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Dkey Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2DkeyCalculate(BYTE ucDkeyCount)
{
    BYTE pucAESInput[16];
    BYTE pucAESCipherInput[16];

    memset(pucAESInput, 0, sizeof(pucAESInput));
    memset(pucAESCipherInput, 0, sizeof(pucAESCipherInput));

    switch(ucDkeyCount)
    {
        case _HDCP_2_2_DKEY_0:

            // Initial AES Input Value
            memcpy(pucAESInput, g_pucRtx, 8);
            memcpy(&pucAESInput[8], g_pucRrx, 8);
            memcpy(pucAESCipherInput, g_pucKm, 16);

            // AES Calculate
            ScalerHdcp2AESCtrl(_AUTHENTICATE_PROTOCOL, pucAESInput, pucAESCipherInput);

            break;

        case _HDCP_2_2_DKEY_1:

            // Initial AES Input Value
            memcpy(pucAESInput, g_pucRtx, 8);
            memcpy(&pucAESInput[8], g_pucRrx, 7);
            pucAESInput[15] = g_pucRrx[7] ^ 0x01;
            memcpy(pucAESCipherInput, g_pucKm, 16);

            // AES Calculate
            ScalerHdcp2AESCtrl(_AUTHENTICATE_PROTOCOL, pucAESInput, pucAESCipherInput);

            break;

        case _HDCP_2_2_DKEY_2:

            // Initial AES Input Value
            memcpy(pucAESInput, g_pucRtx, 8);
            memcpy(&pucAESInput[8], g_pucRrx, 7);
            pucAESInput[15] = g_pucRrx[7] ^ 0x02;

            memcpy(pucAESCipherInput, g_pucKm, 8);

            for(pData[0] = 8; pData[0] < 16; pData[0]++)
            {
                pucAESCipherInput[pData[0]] = g_pucKm[pData[0]] ^ g_pucRn[pData[0] - 8];
            }

            // AES Calculate
            ScalerHdcp2AESCtrl(_AUTHENTICATE_PROTOCOL, pucAESInput, pucAESCipherInput);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2SetRdMsgValue(WORD usAddress, BYTE *pucReadArray, WORD usLength)
{
    WORD usTemp = 0;

    if(ScalerGlobalGetIDCode() >= _RL6369_VER_C_ID_CODE)
    {
        ScalerSetBit(P63_03_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), usAddress >> 8);
        ScalerSetByte(P63_04_HDCP_MSGRAP_L, usAddress);

        // Set HDCP 2 Read SRAM Message Value, Disable HDCP 2 Read SRAM auto Increase
        for(usTemp = usAddress; usTemp < (usAddress + usLength); usTemp++)
        {
            ScalerSetByte(P63_05_HDCP_MSGRDP, pucReadArray[usTemp - usAddress]);
        }
    }
    else
    {
        for(usTemp = usAddress; usTemp < (usAddress + usLength); usTemp++)
        {
            ScalerSetBit(P63_03_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), usTemp >> 8);
            ScalerSetByte(P63_04_HDCP_MSGRAP_L, usTemp);
            ScalerSetByte(P63_05_HDCP_MSGRDP, pucReadArray[usTemp - usAddress]);
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message ID Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2SetRdMsgIDCode(BYTE ucValue)
{
    ScalerSetBit(P63_03_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte(P63_04_HDCP_MSGRAP_L, 0x00);
    ScalerSetByte(P63_05_HDCP_MSGRDP, ucValue);
}

//--------------------------------------------------
// Description  : Two large number add
// Input Value  : A and B, ucLength = sizeof(pLargeNumA)
// Output Value : A + B
//--------------------------------------------------
void ScalerHdcp2LargerNumberAddCal(BYTE *pucLargeNumA, BYTE ucNum, BYTE ucLength)
{
    WORD usSum = 0;
    BYTE ucCarry = 0;

    for(pData[0] = ucLength - 1; pData[0] < ucLength; pData[0]--)
    {
        usSum = pucLargeNumA[pData[0]];

        usSum = usSum + ucNum + ucCarry;

        pucLargeNumA[pData[0]] = (BYTE)(usSum & 0xFF);

        ucCarry = (BYTE)(usSum >> 8);

        ucNum = 0;
    }
}

//--------------------------------------------------
// Description  : Compare Two large number
// Input Value  : A and B, ucLength = sizeof max(A, B)
// Output Value : 1: A > B; -1: A < B; 0: A = B
//--------------------------------------------------
SBYTE ScalerHdcp2LargerNumberCmp(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength)
{
    BYTE ucInx = 0;

    for(ucInx = 0; ucInx < ucLength; ucInx++)
    {
        if(pucLargeNumA[ucInx] > pucLargeNumB[ucInx])
        {
            DebugMessageHDCP2("A > B = ", ucInx);

            return 1;
        }

        if(pucLargeNumA[ucInx] < pucLargeNumB[ucInx])
        {
            DebugMessageHDCP2("A < B = ", ucInx);
            return -1;
        }
    }

    DebugMessageHDCP2("A = B = ", ucInx);

    return 0;
}

//--------------------------------------------------
// Description  : Two large number Sub, Condition: must A >= B
// Input Value  : A and B
// Output Value : A - B
//--------------------------------------------------
void ScalerHdcp2LargerNumberABigerBSub(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength)
{
    BYTE ucCarry = 0;
    BYTE ucInx = 0;
    WORD usNum = 0;

    for(ucInx = ucLength - 1; ucInx < ucLength; ucInx--)
    {
        if((pucLargeNumA[ucInx] > pucLargeNumB[ucInx]) || ((pucLargeNumA[ucInx] == pucLargeNumB[ucInx]) && (ucCarry == 0)))
        {
            pucLargeNumA[ucInx] = pucLargeNumA[ucInx] - ucCarry - pucLargeNumB[ucInx];

            ucCarry = 0;
        }
        else
        {
            usNum = 0x100 + pucLargeNumA[ucInx];
            pucLargeNumA[ucInx] = (BYTE)(usNum - ucCarry - pucLargeNumB[ucInx]);
            ucCarry = 1;
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Large Number Add Calculate
// Input Value  : pResult = pArrayL - pArrayR, ucLength = Large number Length
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2LargeNumSubCal(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength)
{
    BYTE ucInx = 0;

    if(ScalerHdcp2LargerNumberCmp(pucLargeNumA, pucLargeNumB, ucLength) >= 0) // A >= B
    {
        ScalerHdcp2LargerNumberABigerBSub(pucLargeNumA, pucLargeNumB, ucLength);
    }
    else // A < B
    {
        ScalerHdcp2LargerNumberABigerBSub(pucLargeNumB, pucLargeNumA, ucLength);

        for(ucInx = 0; ucInx < ucLength; ucInx++)
        {
            pucLargeNumB[ucInx] = ~pucLargeNumB[ucInx];
        }

        ScalerHdcp2LargerNumberAddCal(pucLargeNumB, 1, ucLength);

        memcpy(pucLargeNumA, pucLargeNumB, ucLength);
    }
}
#endif

//--------------------------------------------------
// Description  : HDCP 2.2 AES Ctrl in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2AESCtrl_EXINT0(BYTE ucAESCtrl, BYTE *pucInputArray, BYTE *pucCipherArray) using 1
{
    if(ucAESCtrl == _AUTHENTICATE_PROTOCOL)
    {
        // HDCP 2.2 Reset
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

        // Set bit 7: AES FW Mode, bit6: AES FW Enable, bit5: AES Random Disable bit 4:3: Reference Xtal Clock
        ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

        // Load Input Value
        for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
        {
            ScalerSetByte_EXINT((P63_61_HDCP_AES_DATA_IN_15 + pData_EXINT[0]), pucInputArray[pData_EXINT[0]]);

            ScalerSetByte_EXINT((P63_71_HDCP_AES_CIPHER_KEY_15 + pData_EXINT[0]), pucCipherArray[pData_EXINT[0]]);
        }

        // Start AES Calculation
        ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

        DELAY_XUS_EXINT(1000);
        DELAY_XUS_EXINT(800);
    }
    else if(ucAESCtrl == _DECRYPTION_PROTOCOL)
    {
        for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
        {
            ScalerSetByte_EXINT(P63_71_HDCP_AES_CIPHER_KEY_15 + pData_EXINT[0], pucCipherArray[pData_EXINT[0]]);
        }


        // Set bit 7: AES FW Mode , bit6: AES FW Enable , bit5: AES Random Disable bit 4:3: Reference HDMI Clock
        ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT4);

        if(ScalerGlobalGetIDCode_EXINT0() <= _RL6369_VER_B_ID_CODE)
        {
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 4; pData_EXINT[0]++)
            {
                ScalerSetByte_EXINT(P63_AB_HDCP_I2C_CTRL_RIV3 + pData_EXINT[0], pucInputArray[pData_EXINT[0]]);
            }

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 4; pData_EXINT[0]++)
            {
                ScalerSetByte_EXINT(P63_A7_HDCP_I2C_CTRL_RIV7 + pData_EXINT[0], pucInputArray[4 + pData_EXINT[0]]);
            }
        }
        else
        {
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
            {
                ScalerSetByte_EXINT(P63_A7_HDCP_I2C_CTRL_RIV7 + pData_EXINT[0], pucInputArray[pData_EXINT[0]]);
            }
        }

        // Riv from FW
        ScalerSetBit_EXINT(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT7, _BIT7);

        // Start AES Calculation
        ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

        // Set HW to Authenticated State
        ScalerSetByte_EXINT(P63_A2_HDCP_I2C_CTRL_A2, 0x10);
        ScalerSetBit_EXINT(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT6, _BIT6);
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2RsaCalculate_EXINT0(BYTE *pucEkpubKmArray) using 1
{
    // Enable HDCP 2.2 RSA Module
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));

    // Select RSA Key Download Data Length
    ScalerSetBit_EXINT(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT7);

    // Load Ekpub[km] to RSA Module as cipher text
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Enable write cipher text to RSA Module
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (15 - (BYTE)pData_EXINT[0]));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEkpubKmArray[pData_EXINT[0] << 3], 8);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load RRmodN
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x10 + (15 - pData_EXINT[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcpDownLoadKeyType.pucHdcp2Rrmodn[pData_EXINT[0] << 3], 8);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load N Key
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (15 - pData_EXINT[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcpDownLoadKeyType.pucHdcp2Certrx[(pData_EXINT[0] << 3) + 5], 8);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load D Key
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x40 + (15 - pData_EXINT[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcpDownLoadKeyType.pucHdcp2DKey[pData_EXINT[0] << 3], 8);
    }

    // Load Npinv to RSA Module
    memcpy((volatile BYTE xdata *)P63_12_HDCP_RSA_NP_INV_3, &g_stRxHdcpDownLoadKeyType.pucHdcp2Npinv, 4);

    // Set RSA Write key done
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

    // Enable RSA Calculate
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT4, 0x00);

    // Polling 100ms for RSA Module Done
    if(ScalerTimerPollingFlagProc_EXINT0(100, P63_10_HDCP_RSA_CTRL0, _BIT2, _SUCCESS) == _TRUE)
    {
        // Disable RSA Module
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT7, 0x00);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Oaep Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2RsaOaepCalculate_EXINT0(void) using 1
{
    BYTE pucHdcp2RsaOaepInput[128];

    // Read Out RSA Message
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5), _BIT6);

    if((bit)ScalerGetBit_EXINT(P63_92_HDCP_DUMMY1, _BIT7) != (bit)ScalerGetBit_EXINT(P63_10_HDCP_RSA_CTRL0, _BIT1))
    {
        // Read Message From One of 2 Address
        if(ScalerGetBit_EXINT(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
        {
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
            {
                ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (0x10 | pData_EXINT[0]));
                memcpy(&pucHdcp2RsaOaepInput[(15 - pData_EXINT[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
            }
        }
        else
        {
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
            {
                ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, pData_EXINT[0]);
                memcpy(&pucHdcp2RsaOaepInput[(15 - pData_EXINT[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
            }
        }
    }
    else
    {
        // Read RSA Output from 0x6310[1] Address, low 64bit
        if(ScalerGetBit_EXINT(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
        {
            ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, 0x00);
            memcpy(&g_pucHdcp2SHA256Input[0], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
        else
        {
            ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, 0x10);
            memcpy(&g_pucHdcp2SHA256Input[0], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }

        // Read N low 64bit
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, 0x30);
        memcpy(&pucHdcp2RsaOaepInput[0], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);

        // RSA output low 64 bit - N low 64 bit
        ScalerHdcp2LargeNumSubCal_EXINT0(g_pucHdcp2SHA256Input, pucHdcp2RsaOaepInput, 8);

        memcpy(&pucHdcp2RsaOaepInput[120], &g_pucHdcp2SHA256Input[0], 8);

        // Read RSA Output from 0x6392[7] Address
        if(ScalerGetBit_EXINT(P63_92_HDCP_DUMMY1, _BIT7) == 0x00)
        {
            for(pData_EXINT[0] = 1; pData_EXINT[0] < 16; pData_EXINT[0]++)
            {
                ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, pData_EXINT[0]);
                memcpy(&pucHdcp2RsaOaepInput[(15 - pData_EXINT[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
            }
        }
        else
        {
            for(pData_EXINT[0] = 1; pData_EXINT[0] < 16; pData_EXINT[0]++)
            {
                ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (0x10 | pData_EXINT[0]));
                memcpy(&pucHdcp2RsaOaepInput[(15 - pData_EXINT[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
            }
        }
    }

    // Calculate First Block 512 Bit SHA256 Calculate, Calculate MGF(maskDB, 32)
    if(ScalerHdcp2SHA256Calculate_EXINT0(&pucHdcp2RsaOaepInput[33], 0) == _TRUE)
    {
        // Load Second Block 512 Bit Data
        memcpy(g_pucHdcp2SHA256Input, &pucHdcp2RsaOaepInput[97], 31);
        memset(&g_pucHdcp2SHA256Input[31], 0, 33);
        g_pucHdcp2SHA256Input[35] = 0x80;
        g_pucHdcp2SHA256Input[62] = 0x03;
        g_pucHdcp2SHA256Input[63] = 0x18;

        // Calculate Second Block 512 Bit Data
        if(ScalerHdcp2SHA256Calculate_EXINT0(g_pucHdcp2SHA256Input, 1) == _TRUE)
        {
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
            {
                g_pucHdcp2SHA256Input[pData_EXINT[0]] = pucHdcp2RsaOaepInput[1 + pData_EXINT[0]] ^ ScalerGetByte_EXINT((P63_35_HDCP_SHA_0 + pData_EXINT[0]));
            }

            memset(&g_pucHdcp2SHA256Input[32], 0, 32);
            g_pucHdcp2SHA256Input[36] = 0x80;
            g_pucHdcp2SHA256Input[62] = 0x01;
            g_pucHdcp2SHA256Input[63] = 0x20;

            // Calculte MGF(Seed, 95), Seed = 32 byte SHA256 output + C 0x0000000x + 0x80 + Stream Length
            g_pucHdcp2SHA256Input[35] = 0;
            ScalerHdcp2SHA256Calculate_EXINT0(g_pucHdcp2SHA256Input, 0);
            g_pucHdcp2SHA256Input[35] = 1;
            ScalerHdcp2SHA256Calculate_EXINT0(g_pucHdcp2SHA256Input, 0);
            g_pucHdcp2SHA256Input[35] = 2;
            ScalerHdcp2SHA256Calculate_EXINT0(g_pucHdcp2SHA256Input, 0);

            // DB maskDB XOR DBmask
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
            {
                g_pucHdcp2SHA256Input[pData_EXINT[0]] = pucHdcp2RsaOaepInput[33 + pData_EXINT[0] + 64] ^ ScalerGetByte_EXINT((P63_35_HDCP_SHA_0 + pData_EXINT[0]));
            }

            g_pucHdcp2SHA256Input[31] = ScalerGetByte_EXINT((P63_35_HDCP_SHA_0 + 31));

            if(g_pucHdcp2SHA256Input[14] == 0x01)
            {
                memcpy(g_pucKm, &g_pucHdcp2SHA256Input[15], 16);

                return _TRUE;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 SHA 256 Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2SHA256Calculate(BYTE *pucInputArray, BYTE ucCalCount)
{
    // Set 1, Then Set 0 for Reset SHA256 Module
    ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT3, _BIT3);

    ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT3, 0x00);

    // Write SHA256 Input Data, Total 512 bits
    for(pData[1] = 0; pData[1] < 16; pData[1]++)
    {
        ScalerSetByte(P63_31_HDCP_SHA_DATA1, pucInputArray[pData[1] * 4]);
        ScalerSetByte(P63_32_HDCP_SHA_DATA2, pucInputArray[1 + pData[1] * 4]);
        ScalerSetByte(P63_33_HDCP_SHA_DATA3, pucInputArray[2 + pData[1] * 4]);
        ScalerSetByte(P63_34_HDCP_SHA_DATA4, pucInputArray[3 + pData[1] * 4]);

        // Inform HW SHA data Has been set first 32 bit
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT0, _BIT0);
    }

    if(ucCalCount == 0)
    {
        // Set First Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT1), _BIT1);

        // Enable SHA256 Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable First Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT1), 0x00);

        // Enable SHA256 Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT2, _BIT2);
    }

    // Polling 10ms for HDCP Sha Done
    if(ScalerTimerPollingFlagProc(10, P63_30_HDCP_SHA_CONTRL, _BIT4, _TRUE) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 SHA 256 Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2SHA256Calculate_EXINT0(BYTE *pucInputArray, BYTE ucCalCount) using 1
{
    // Set 1, Then Set 0 for Reset SHA256 Module
    ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~_BIT3, _BIT3);

    ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~_BIT3, 0x00);

    // Write SHA256 Input Data, Total 512 bits
    for(pData_EXINT[1] = 0; pData_EXINT[1] < 16; pData_EXINT[1]++)
    {
        ScalerSetByte_EXINT(P63_31_HDCP_SHA_DATA1, pucInputArray[pData_EXINT[1] * 4]);
        ScalerSetByte_EXINT(P63_32_HDCP_SHA_DATA2, pucInputArray[1 + pData_EXINT[1] * 4]);
        ScalerSetByte_EXINT(P63_33_HDCP_SHA_DATA3, pucInputArray[2 + pData_EXINT[1] * 4]);
        ScalerSetByte_EXINT(P63_34_HDCP_SHA_DATA4, pucInputArray[3 + pData_EXINT[1] * 4]);

        // Inform HW SHA data Has been set first 32 bit
        ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~_BIT0, _BIT0);
    }

    if(ucCalCount == 0)
    {
        // Set First Calculate
        ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT1), _BIT1);

        // Enable SHA256 Calculate
        ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable First Calculate
        ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT1), 0x00);

        // Enable SHA256 Calculate
        ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~_BIT2, _BIT2);
    }

    // Polling 10ms for HDCP Sha Done
    if(ScalerTimerPollingFlagProc_EXINT0(10, P63_30_HDCP_SHA_CONTRL, _BIT4, _TRUE) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 HMACSHA 256 Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2HMACSHA256Calculate_EXINT0(void) using 1
{
    for(pData_EXINT[1] = 0; pData_EXINT[1] < 64; pData_EXINT[1]++)
    {
        // K0 XOR ipad = 512 bit
        g_pucHMACSHA256CipherInput[pData_EXINT[1]] = g_pucHMACSHA256CipherInput[pData_EXINT[1]] ^ 0x36;
    }

    // Calculate SHA256((K0 XOR ipad) || text)
    if(ScalerHdcp2SHA256Calculate_EXINT0(g_pucHMACSHA256CipherInput, 0) == _TRUE)
    {
        if(ScalerHdcp2SHA256Calculate_EXINT0(g_pucHMACSHA256Input, 1) == _TRUE)
        {
            // KO XOR opad
            for(pData_EXINT[1] = 0; pData_EXINT[1] < 64; pData_EXINT[1]++)
            {
                g_pucHMACSHA256CipherInput[pData_EXINT[1]] = g_pucHMACSHA256CipherInput[pData_EXINT[1]] ^ 0x36 ^ 0x5C;
            }

            for(pData_EXINT[1] = 0; pData_EXINT[1] < 64; pData_EXINT[1]++)
            {
                if(pData_EXINT[1] < 32)
                {
                    g_pucHMACSHA256Input[pData_EXINT[1]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[1]);
                }
                else
                {
                    g_pucHMACSHA256Input[pData_EXINT[1]] = 0;
                }
            }

            g_pucHMACSHA256Input[32] = 0x80;
            g_pucHMACSHA256Input[62] = 0x03;

            // SHA256((KO XOR opad) || SHA256(KO XOR ipad) || text)
            if(ScalerHdcp2SHA256Calculate_EXINT0(g_pucHMACSHA256CipherInput, 0) == _TRUE)
            {
                if(ScalerHdcp2SHA256Calculate_EXINT0(g_pucHMACSHA256Input, 1) == _TRUE)
                {
                    return _TRUE;
                }
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Hprime Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2HPrimeCalculate_EXINT0(void) using 1
{
    // H = HMAC-SHA256(rtx || RxCaps || TxCaps, kd)
    // HMAC(text) = HMAC(K, text) = SHA256((K0 XOR opad) || SHA256((KO XOR ipad) || text))
    // Calculate SHA256((KO XOR ipad) || text)

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        g_pucHMACSHA256CipherInput[pData_EXINT[0]] = g_pucdKey0[pData_EXINT[0]];
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        g_pucHMACSHA256CipherInput[16 + pData_EXINT[0]] = g_pucdKey1[pData_EXINT[0]];
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
    {
        g_pucHMACSHA256Input[pData_EXINT[0]] = g_pucRtx[pData_EXINT[0]];
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 3; pData_EXINT[0]++)
    {
        g_pucHMACSHA256Input[8 + pData_EXINT[0]] = g_pucRxCaps[pData_EXINT[0]];
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 3; pData_EXINT[0]++)
    {
        g_pucHMACSHA256Input[11 + pData_EXINT[0]] = g_pucTxCaps[pData_EXINT[0]];
    }

    g_pucHMACSHA256Input[14] = 0x80;

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 47; pData_EXINT[0]++)
    {
        g_pucHMACSHA256Input[15 + pData_EXINT[0]] = 0;
    }

    g_pucHMACSHA256Input[62] = 0x02;
    g_pucHMACSHA256Input[63] = 0x70;

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
    {
        g_pucHMACSHA256CipherInput[32 + pData_EXINT[0]] = 0;
    }

    if(ScalerHdcp2HMACSHA256Calculate_EXINT0() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Pairing Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxPairingCalculate(BYTE *pucHdcp2KPriv, BYTE ucIndex)
{
    // Disable HDCP 2.2 Software Reset
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

    // Calculate Kh = SHA256(Kprivrx), Need 3 SHA256 Block
    if(ucIndex < 5)
    {
        ScalerHdcp2SHA256Calculate(pucHdcp2KPriv, ucIndex);
        return _TRUE;
    }
    else
    {
        pucHdcp2KPriv[0] = 0x80;
        memset(&pucHdcp2KPriv[1], 0, 63);
        pucHdcp2KPriv[62] = 0x0A;

        if(ScalerHdcp2SHA256Calculate(pucHdcp2KPriv, ucIndex) == _TRUE)
        {
            memcpy(g_pucKh, (volatile BYTE xdata *)(P63_35_HDCP_SHA_0 + 16), 16);
            return _TRUE;
        }
        else
        {
            DebugMessageHDCP2("HDCP2 Pairing Fail", 0x00);
            return _FALSE;
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Lprime Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2LPrimeCalculate_EXINT0(void) using 1
{
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 64; pData_EXINT[0]++)
    {
        if(pData_EXINT[0] < 8)
        {
            g_pucHMACSHA256Input[pData_EXINT[0]] = g_pucRn[pData_EXINT[0]];
        }
        else
        {
            g_pucHMACSHA256Input[pData_EXINT[0]] = 0;
        }
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 64; pData_EXINT[0]++)
    {
        if(pData_EXINT[0] < 16)
        {
            g_pucHMACSHA256CipherInput[pData_EXINT[0]] = g_pucdKey0[pData_EXINT[0]];
        }
        else if(pData_EXINT[0] < 32)
        {
            g_pucHMACSHA256CipherInput[pData_EXINT[0]] = g_pucdKey1[pData_EXINT[0] - 16];

            if(pData_EXINT[0] > 23)
            {
                g_pucHMACSHA256CipherInput[pData_EXINT[0]] = g_pucHMACSHA256CipherInput[pData_EXINT[0]] ^ g_pucRrx[pData_EXINT[0] - 24];
            }
        }
        else
        {
            g_pucHMACSHA256CipherInput[pData_EXINT[0]] = 0;
        }
    }


    g_pucHMACSHA256Input[8] = 0x80;
    g_pucHMACSHA256Input[62] = 0x02;
    g_pucHMACSHA256Input[63] = 0x40;

    if((bit)ScalerHdcp2HMACSHA256Calculate_EXINT0() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Dkey Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2DkeyCalculate_EXINT0(BYTE ucDkeyCount) using 1
{
    switch(ucDkeyCount)
    {
        case 0:

            // Initial AES Input Value
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
            {
                g_pucAESInput[pData_EXINT[0]] = g_pucRtx[pData_EXINT[0]];
            }

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
            {
                g_pucAESInput[8 + pData_EXINT[0]] = g_pucRrx[pData_EXINT[0]];
            }

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
            {
                g_pucAESCipherInput[pData_EXINT[0]] = g_pucKm[pData_EXINT[0]];
            }

            // AES Calculate
            ScalerHdcp2AESCtrl_EXINT0(_AUTHENTICATE_PROTOCOL, g_pucAESInput, g_pucAESCipherInput);

            break;

        case 1:

            // Initial AES Input Value
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
            {
                g_pucAESInput[pData_EXINT[0]] = g_pucRtx[pData_EXINT[0]];
            }

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 7; pData_EXINT[0]++)
            {
                g_pucAESInput[8 + pData_EXINT[0]] = g_pucRrx[pData_EXINT[0]];
            }

            g_pucAESInput[15] = g_pucRrx[7] ^ 0x01;

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
            {
                g_pucAESCipherInput[pData_EXINT[0]] = g_pucKm[pData_EXINT[0]];
            }

            // AES Calculate
            ScalerHdcp2AESCtrl_EXINT0(_AUTHENTICATE_PROTOCOL, g_pucAESInput, g_pucAESCipherInput);

            break;

        case 2:

            // Initial AES Input Value
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
            {
                g_pucAESInput[pData_EXINT[0]] = g_pucRtx[pData_EXINT[0]];
            }

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 7; pData_EXINT[0]++)
            {
                g_pucAESInput[8 + pData_EXINT[0]] = g_pucRrx[pData_EXINT[0]];
            }

            g_pucAESInput[15] = g_pucRrx[7] ^ 0x02;

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
            {
                g_pucAESCipherInput[pData_EXINT[0]] = g_pucKm[pData_EXINT[0]];
            }

            for(pData_EXINT[0] = 8; pData_EXINT[0] < 16; pData_EXINT[0]++)
            {
                g_pucAESCipherInput[pData_EXINT[0]] = g_pucKm[pData_EXINT[0]] ^ g_pucRn[pData_EXINT[0] - 8];
            }

            // AES Calculate
            ScalerHdcp2AESCtrl_EXINT0(_AUTHENTICATE_PROTOCOL, g_pucAESInput, g_pucAESCipherInput);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message Value in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2SetRdMsgValue_EXINT0(WORD usAddress, BYTE *pucReadArray, WORD usLength) using 1
{
    WORD usTemp = 0;

    if(ScalerGlobalGetIDCode_EXINT0() >= _RL6369_VER_C_ID_CODE)
    {
        ScalerSetBit_EXINT(P63_03_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), usAddress >> 8);
        ScalerSetByte_EXINT(P63_04_HDCP_MSGRAP_L, usAddress);

        // Set HDCP 2 Read SRAM Message Value, Disable HDCP 2 Read SRAM auto Increase
        for(usTemp = usAddress; usTemp < (usAddress + usLength); usTemp++)
        {
            ScalerSetByte_EXINT(P63_05_HDCP_MSGRDP, pucReadArray[usTemp - usAddress]);
        }
    }
    else
    {
        for(usTemp = usAddress; usTemp < (usAddress + usLength); usTemp++)
        {
            ScalerSetBit_EXINT(P63_03_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), usTemp >> 8);
            ScalerSetByte_EXINT(P63_04_HDCP_MSGRAP_L, usTemp);
            ScalerSetByte_EXINT(P63_05_HDCP_MSGRDP, pucReadArray[usTemp - usAddress]);
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message ID Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2SetRdMsgIDCode_EXINT0(BYTE ucValue) using 1
{
    ScalerSetBit_EXINT(P63_03_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte_EXINT(P63_04_HDCP_MSGRAP_L, 0x00);
    ScalerSetByte_EXINT(P63_05_HDCP_MSGRDP, ucValue);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Down Load Rrx Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2GetRrx_EXINT0(void) using 1
{
    // Load Rrx to Read SRAM
    g_pucRrx[0] = ScalerGetByte_EXINT(P63_89_HDCP_AES_OUT_7);
    g_pucRrx[1] = ScalerGetByte_EXINT(P63_8A_HDCP_AES_OUT_6);
    g_pucRrx[2] = ScalerGetByte_EXINT(P63_8B_HDCP_AES_OUT_5);
    g_pucRrx[3] = ScalerGetByte_EXINT(P63_8C_HDCP_AES_OUT_4);
    g_pucRrx[4] = ScalerGetByte_EXINT(P63_8D_HDCP_AES_OUT_3);
    g_pucRrx[5] = ScalerGetByte_EXINT(P63_8E_HDCP_AES_OUT_2);
    g_pucRrx[6] = ScalerGetByte_EXINT(P63_8F_HDCP_AES_OUT_1);
    g_pucRrx[7] = ScalerGetByte_EXINT(P63_90_HDCP_AES_OUT_0);
}

//--------------------------------------------------
// Description  : Two large number add in INT
// Input Value  : A and B, ucLength = sizeof(pLargeNumA)
// Output Value : A + B
//--------------------------------------------------
void ScalerHdcp2LargerNumberAddCal_EXINT0(BYTE *pucLargeNumA, BYTE ucNum, BYTE ucLength) using 1
{
    WORD usSum = 0;
    BYTE ucCarry = 0;

    for(pData_EXINT[0] = ucLength - 1; pData_EXINT[0] < ucLength; pData_EXINT[0]--)
    {
        usSum = pucLargeNumA[pData_EXINT[0]];

        usSum = usSum + ucNum + ucCarry;

        pucLargeNumA[pData_EXINT[0]] = (BYTE)(usSum & 0xFF);

        ucCarry = (BYTE)(usSum >> 8);

        ucNum = 0;
    }
}

//--------------------------------------------------
// Description  : Compare Two large number
// Input Value  : A and B, ucLength = sizeof max(A, B)
// Output Value : 1: A > B; -1: A < B; 0: A = B
//--------------------------------------------------
SBYTE ScalerHdcp2LargerNumberCmp_EXINT0(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength) using 1
{
    BYTE ucInx = 0;

    for(ucInx = 0; ucInx < ucLength; ucInx++)
    {
        if(pucLargeNumA[ucInx] > pucLargeNumB[ucInx])
        {
            return 1;
        }

        if(pucLargeNumA[ucInx] < pucLargeNumB[ucInx])
        {
            return -1;
        }
    }
    return 0;
}

//--------------------------------------------------
// Description  : Two large number Sub, Condition: must A >= B
// Input Value  : A and B
// Output Value : A - B
//--------------------------------------------------
void ScalerHdcp2LargerNumberABigerBSub_EXINT0(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength) using 1
{
    BYTE ucCarry = 0;
    BYTE ucInx = 0;
    WORD usNum = 0;

    for(ucInx = ucLength - 1; ucInx < ucLength; ucInx--)
    {
        if((pucLargeNumA[ucInx] > pucLargeNumB[ucInx]) || ((pucLargeNumA[ucInx] == pucLargeNumB[ucInx]) && (ucCarry == 0)))
        {
            pucLargeNumA[ucInx] = pucLargeNumA[ucInx] - ucCarry - pucLargeNumB[ucInx];

            ucCarry = 0;
        }
        else
        {
            usNum = 0x100 + pucLargeNumA[ucInx];
            pucLargeNumA[ucInx] = (BYTE)(usNum - ucCarry - pucLargeNumB[ucInx]);
            ucCarry = 1;
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Large Number Add Calculate
// Input Value  : pResult = pArrayL - pArrayR, ucLength = Large number Length
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2LargeNumSubCal_EXINT0(BYTE *pucLargeNumA, BYTE *pucLargeNumB, BYTE ucLength) using 1
{
    BYTE ucInx = 0;

    if(ScalerHdcp2LargerNumberCmp_EXINT0(pucLargeNumA, pucLargeNumB, ucLength) >= 0) // A >= B
    {
        ScalerHdcp2LargerNumberABigerBSub_EXINT0(pucLargeNumA, pucLargeNumB, ucLength);
    }
    else // A < B
    {
        ScalerHdcp2LargerNumberABigerBSub_EXINT0(pucLargeNumB, pucLargeNumA, ucLength);

        for(ucInx = 0; ucInx < ucLength; ucInx++)
        {
            pucLargeNumB[ucInx] = ~pucLargeNumB[ucInx];
        }

        ScalerHdcp2LargerNumberAddCal_EXINT0(pucLargeNumB, 1, ucLength);

        memcpy(pucLargeNumA, pucLargeNumB, ucLength);
    }
}

//--------------------------------------------------
// Description  : Get psudo-random Rrx Key for HDCP 2.2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxGenRrx_EXINT0(void) using 1
{
    BYTE ucDelayXus_Cnt = 0x00;
    BYTE ucLoop = 0x00;
    BYTE ucDelay = 0x00;

    do
    {
        // Rrx Gen
        // Set bit 7: AES FW Mode, bit6: AES FW Enable, bit5: AES Random Enable bit 4:3: Reference Xtal Clock
        ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

        // Active AES Random Gen
        ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

        // Delay [1, x]ms Randon Time
        ucDelayXus_Cnt = ((5 * (TL2 >> 2)) % 1000) >> 2;
        do
        {
            DELAY_XUS_BASE_EXINT();
        }
        while(--ucDelayXus_Cnt);

        // Disable AES Random Gen
        ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

        // Get Rrx from HW
        ScalerHdcp2GetRrx_EXINT0();

        if((memcmp(g_pucRrx, g_pucDpHdcp2RrxErrta0, 8) != 0x00) && (memcmp(g_pucRrx, g_pucDpHdcp2RrxErrta1, 8) != 0x00))
        {
            break;
        }
        else
        {
            ucLoop++;
        }
    }
    while(ucLoop < 3);

    if(ucLoop == 0x03)
    {
        // Force Assign a default Rrx Key
        g_pucRrx[0] = 0x11;
        g_pucRrx[1] = 0x22;
        g_pucRrx[2] = 0x33;
        g_pucRrx[3] = 0x44;
        g_pucRrx[4] = 0x55;
        g_pucRrx[5] = 0x66;
        g_pucRrx[6] = 0x77;
        g_pucRrx[7] = 0x88;
    }
}
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)
