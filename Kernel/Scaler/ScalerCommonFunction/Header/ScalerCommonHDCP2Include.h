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
// ID Code      : ScalerCommonHDCP2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of HDCP 2.2 Write & Read Message ID
//--------------------------------------------------
#define _HDCP_2_2_NONE                                              0x00
#define _HDCP_2_2_AKE_INIT                                          0x02
#define _HDCP_2_2_AKE_SEND_CERT                                     0x03
#define _HDCP_2_2_AKE_NO_STORED_KM                                  0x04
#define _HDCP_2_2_AKE_STORED_KM                                     0x05
#define _HDCP_2_2_AKE_SEND_H_PRIME                                  0x07
#define _HDCP_2_2_AKE_SEND_PAIRING_INFO                             0x08
#define _HDCP_2_2_LC_INIT                                           0x09
#define _HDCP_2_2_LC_SEND_L_PRIME                                   0x0A
#define _HDCP_2_2_SKE_SEND_EKS                                      0x0B
#define _HDCP_2_2_REPEATERAUTH_SEND_RECID_LIST                      0x0C
#define _HDCP_2_2_REPEATERAUTH_SEND_ACK                             0x0F
#define _HDCP_2_2_REPEATERAUTH_STREAM_MANAGE                        0x10
#define _HDCP_2_2_REPEATERAUTH_STREAM_READY                         0x11
#define _HDCP_2_2_SKE_TYPE_VALUE                                    0x12

#if(_HDCP_2_2_FUNCTION_GEN == _HDCP_2_2_GEN_2)
#define GET_HDCP_2_2_AUTHENTICATION_ACTIVE()                        (bit)(g_ucHdcp2AuthActive)
#endif

//--------------------------------------------------
// Definitions of HDCP 2.2 Online AES Page
//--------------------------------------------------
#define SET_HDCP_2_2_ONLINE_AES_PAGEB(x, y)\
{\
    memcpy((volatile BYTE xdata *)PB_81_HDCP_AES_CIPHER_KEY_15, (x), 16);\
    memcpy((volatile BYTE xdata *)PB_55_RIV0, (y), 8);\
}

#define SET_HDCP_2_2_ONLINE_AES_PAGE2D(x, y)\
{\
    memcpy((volatile BYTE xdata *)P2D_00_HDCP_AES_CIPHER_KEY_15, (x), 16);\
    memcpy((volatile BYTE xdata *)P2D_2D_HDCP_I2C_CTRL_RIV7, (y), 8);\
}

#define SET_HDCP_2_2_ONLINE_AES_PAGE2E(x, y)\
{\
    memcpy((volatile BYTE xdata *)P2E_00_HDCP_AES_CIPHER_KEY_15, (x), 16);\
    memcpy((volatile BYTE xdata *)P2E_2D_HDCP_I2C_CTRL_RIV7, (y), 8);\
}

#define SET_HDCP_2_2_ONLINE_AES_PAGE6D(x, y)\
{\
    memcpy((volatile BYTE xdata *)P6D_00_HDCP_AES_CIPHER_KEY_15, (x), 16);\
    memcpy((volatile BYTE xdata *)P6D_2D_HDCP_I2C_CTRL_RIV7, (y), 8);\
}

#define SET_HDCP_2_2_ONLINE_AES_PAGE6E(x, y)\
{\
    memcpy((volatile BYTE xdata *)P6E_00_HDCP_AES_CIPHER_KEY_15, (x), 16);\
    memcpy((volatile BYTE xdata *)P6E_2D_HDCP_I2C_CTRL_RIV7, (y), 8);\
}

#if(_TMDS_HDCP_2_2_RX1_ONLINE_AES_PAGE == _PAGEB)
#define SET_HDCP_2_2_RX1_ONLINE_AES(x, y)                           {SET_HDCP_2_2_ONLINE_AES_PAGEB((x), (y))}
#elif(_TMDS_HDCP_2_2_RX1_ONLINE_AES_PAGE == _PAGE2D)
#define SET_HDCP_2_2_RX1_ONLINE_AES(x, y)                           {SET_HDCP_2_2_ONLINE_AES_PAGE2D((x), (y))}
#endif

#if(_TMDS_HDCP_2_2_RX2_ONLINE_AES_PAGE == _PAGEB)
#define SET_HDCP_2_2_RX2_ONLINE_AES(x, y)                           {SET_HDCP_2_2_ONLINE_AES_PAGEB((x), (y))}
#elif(_TMDS_HDCP_2_2_RX2_ONLINE_AES_PAGE == _PAGE2D)
#define SET_HDCP_2_2_RX2_ONLINE_AES(x, y)                           {SET_HDCP_2_2_ONLINE_AES_PAGE2D((x), (y))}
#endif

#define SET_HDCP_2_2_RX3_ONLINE_AES(x, y)                           {SET_HDCP_2_2_ONLINE_AES_PAGE2E((x), (y))}
#define SET_HDCP_2_2_RX4_ONLINE_AES(x, y)                           {SET_HDCP_2_2_ONLINE_AES_PAGE6D((x), (y))}
#define SET_HDCP_2_2_RX5_ONLINE_AES(x, y)                           {SET_HDCP_2_2_ONLINE_AES_PAGE6E((x), (y))}

#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of HDCP 2.2 Authentication State
//--------------------------------------------------
typedef enum
{
    _HDCP_2_2_STATE_UNAUTHENTICATED = 0,
    _HDCP_2_2_STATE_COMPUTE_KM,
    _HDCP_2_2_STATE_COMPUTE_L_PRIME,
    _HDCP_2_2_STATE_COMPUTE_KS,
    _HDCP_2_2_STATE_AUTHENTICATED,
    _HDCP_2_2_STATE_WAIT_FOR_DOWNSTREAM,
    _HDCP_2_2_STATE_ASS_RECEIVER_ID_LIST,
    _HDCP_2_2_STATE_VERIFY_RECEIVER_ID_LIST,
    _HDCP_2_2_STATE_CONTENT_STREAM_MANAGEMENT,
} EnumHdcp2AuthState;

//--------------------------------------------------
// Definitions of HDCP 2.2 D-KEY No.
//--------------------------------------------------
typedef enum
{
    _HDCP_2_2_DKEY_0 = 0,
    _HDCP_2_2_DKEY_1,
    _HDCP_2_2_DKEY_2,
} EnumHdcp2DKey;

//--------------------------------------------------
// Struct for RX HDCP Authentication
//--------------------------------------------------
typedef struct
{
    BYTE b4AuthState : 4;
} StructHdcp2HDCPAuthInfo;

typedef struct
{
#if(_HDCP_2_2_TX_RSA3072_MODE == _ON)
    BYTE pucHdcp2Certrx[384];
    BYTE pucHdcp2DKey[384];
    BYTE pucHdcp2Rrmodn[384];
    BYTE pucHdcp2Lc[16];
    BYTE pucHdcp2Npinv[4];
    BYTE pucHdcp2KpubKm[384];
#else
    BYTE pucHdcp2Certrx[522];
    BYTE pucHdcp2DKey[128];
    BYTE pucHdcp2Rrmodn[128];
    BYTE pucHdcp2Lc[16];
    BYTE pucHdcp2Npinv[4];
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    BYTE pucHdcp2KpubKm[128];
#endif
#endif
} StructHdcp2DownLoadKeyType;
#endif

#if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT))
typedef struct
{
    BYTE pucSignFile[128];
    BYTE pucSignNKey[128];
    BYTE pucSignRrmodn[128];
    BYTE pucSignNpinv[4];
    BYTE pucSignEKey[128];
}StructSignKeyInfoType;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HDCP_2_2_FUNCTION_GEN == _HDCP_2_2_GEN_2)
#if(_HDCP_2_2_SUPPORT == _ON)
extern StructHdcp2DownLoadKeyType g_stRxHdcp2DownLoadKeyType;

extern BYTE g_ucHdcp2AuthActive;

extern BYTE g_pucHdcp2HmacSha256Input[64];
extern BYTE g_pucHdcp2HmacSha256CipherInput[64];

extern BYTE g_pucHdcp2Sha256[32];

extern BYTE g_pucHdcp2BackUp[4];

extern BYTE g_pucHdcp2M[16];
extern BYTE g_pucHdcp2Kh[16];
extern BYTE g_pucHdcp2EkhKm[16];
extern BYTE g_pucHdcp2Ks[16];
extern BYTE g_pucHdcp2EDkeyKs[16];
extern BYTE g_pucHdcp2Riv[8];

extern BYTE g_pucHdcp2InputCipher[16];
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HDCP_2_2_FUNCTION_GEN == _HDCP_2_2_GEN_2)
#if(_HDCP_2_2_SUPPORT == _ON)
extern void ScalerHdcp2DkeyCalculate_EXINT0(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn);
extern BYTE ScalerHdcp2HPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps);
extern void ScalerHdcp2Initial(void);
extern BYTE ScalerHdcp2LPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn);
extern void ScalerHdcp2RxAesOfflineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray);
extern void ScalerHdcp2RxGetRrx_EXINT0(BYTE *pucHdcp2Rrx);
extern BYTE ScalerHdcp2RxHmacSha256Calculate_EXINT0(BYTE *pucInputArray1, BYTE *pucInputArray2);
extern bit ScalerHdcp2RxSha256Calculate(BYTE *pucInputArray, BYTE ucCalCount);
extern BYTE ScalerHdcp2RxSha256Calculate_EXINT0(BYTE *pucInputArray, BYTE ucCalCount);
extern void ScalerHdcp2RxGenRrx_EXINT0(BYTE *pucInputArray);

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_WD_TIMER_INT_SUPPORT == _ON))
extern void ScalerHdcp2DkeyCalculate_WDINT(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn);
#endif

#if((_DP_HDCP_2_2_SUPPORT == _ON) || (_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON))
extern void ScalerHdcp2DkeyCalculate(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn);
extern bit ScalerHdcp2HPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps);
extern void ScalerHdcp2RxAesOfflineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray);
extern bit ScalerHdcp2RxHmacSha256Calculate(BYTE *pucInputArray1, BYTE *pucInputArray2);
#if(_DP_MST_SUPPORT == _ON)
extern bit ScalerHdcp2RepeaterLPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucInputArray);
#endif
extern bit ScalerHdcp2RxRsaCalculate(BYTE *pucEkpubKmArray);
extern bit ScalerHdcp2RxRsaOaepCalculate(BYTE *pucKmArray);
#endif

#if((_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON) || ((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON)))
extern bit ScalerHdcp2LPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn);
#endif

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && (_HDMI_PORT_EXIST == _ON))
extern void ScalerHdcp2ResetTMDSProc(BYTE ucInputPort);
extern void ScalerHdcp2ReAuthEvent(EnumScalerTimerEventID enumEventID);
extern BYTE ScalerHdcp2RxRsaCalculate_EXINT0(BYTE *pucEkpubKmArray);
extern BYTE ScalerHdcp2RxRsaOaepCalculate_EXINT0(BYTE *pucKmArray);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerHdcp2VprimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucReceiverIdList, BYTE *pucRxinfo, BYTE *pucSeqNumV);
extern bit ScalerHdcp2MprimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucStreamIdType, DWORD ulSeqNumM, WORD usK);
#endif
#endif
#endif

