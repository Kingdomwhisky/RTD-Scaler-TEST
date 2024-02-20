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
// ID Code      : ScalerCommonDPRx0HDCP2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_D0_DP_EXIST == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_TX_SUPPORT == _ON)
#define _DP_RX0_HDCP_2_2_REPEATER_SUPPORT                         _ON
#else
#define _DP_RX0_HDCP_2_2_REPEATER_SUPPORT                         _OFF
#endif

//--------------------------------------------------
// DP HDCP2 Type Value Reg Address
//--------------------------------------------------
#define _REG_DP_RX0_HDCP2_TYPE_AES0_VALUE                         PB_93_HDCP_TYPE_AES_0

//--------------------------------------------------
// Definitions of HDCP 2.2 Authentication State
//--------------------------------------------------
#define GET_DP_RX0_HDCP2_AKE_INIT_RECEIVED()                      (bit)(g_ucDPRx0Hdcp2Ctrl0 & _BIT7)
#define SET_DP_RX0_HDCP2_AKE_INIT_RECEIVED()                      (g_ucDPRx0Hdcp2Ctrl0 |= _BIT7)
#define CLR_DP_RX0_HDCP2_AKE_INIT_RECEIVED()                      (g_ucDPRx0Hdcp2Ctrl0 &= ~_BIT7)

#define GET_DP_RX0_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (bit)(g_ucDPRx0Hdcp2Ctrl0 & _BIT6)
#define SET_DP_RX0_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (g_ucDPRx0Hdcp2Ctrl0 |= _BIT6)
#define CLR_DP_RX0_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (g_ucDPRx0Hdcp2Ctrl0 &= ~_BIT6)

#define GET_DP_RX0_HDCP2_AKE_STORED_KM_RECEIVED()                 (bit)(g_ucDPRx0Hdcp2Ctrl0 & _BIT5)
#define SET_DP_RX0_HDCP2_AKE_STORED_KM_RECEIVED()                 (g_ucDPRx0Hdcp2Ctrl0 |= _BIT5)
#define CLR_DP_RX0_HDCP2_AKE_STORED_KM_RECEIVED()                 (g_ucDPRx0Hdcp2Ctrl0 &= ~_BIT5)

#define GET_DP_RX0_HDCP2_LC_INIT_RECEIVED()                       (bit)(g_ucDPRx0Hdcp2Ctrl0 & _BIT4)
#define SET_DP_RX0_HDCP2_LC_INIT_RECEIVED()                       (g_ucDPRx0Hdcp2Ctrl0 |= _BIT4)
#define CLR_DP_RX0_HDCP2_LC_INIT_RECEIVED()                       (g_ucDPRx0Hdcp2Ctrl0 &= ~_BIT4)

#define GET_DP_RX0_HDCP2_SKE_SEND_EKS_RECEIVED()                  (bit)(g_ucDPRx0Hdcp2Ctrl0 & _BIT3)
#define SET_DP_RX0_HDCP2_SKE_SEND_EKS_RECEIVED()                  (g_ucDPRx0Hdcp2Ctrl0 |= _BIT3)
#define CLR_DP_RX0_HDCP2_SKE_SEND_EKS_RECEIVED()                  (g_ucDPRx0Hdcp2Ctrl0 &= ~_BIT3)

#define GET_DP_RX0_HDCP2_STREAM_MANAGE_RECEIVED()                 (bit)(g_ucDPRx0Hdcp2Ctrl0 & _BIT2)
#define SET_DP_RX0_HDCP2_STREAM_MANAGE_RECEIVED()                 (g_ucDPRx0Hdcp2Ctrl0 |= _BIT2)
#define CLR_DP_RX0_HDCP2_STREAM_MANAGE_RECEIVED()                 (g_ucDPRx0Hdcp2Ctrl0 &= ~_BIT2)

#define GET_DP_RX0_HDCP2_AUTHENTICATION_DONE()                    (bit)(g_ucDPRx0Hdcp2Ctrl0 & _BIT1)
#define SET_DP_RX0_HDCP2_AUTHENTICATION_DONE()                    (g_ucDPRx0Hdcp2Ctrl0 |= _BIT1)
#define CLR_DP_RX0_HDCP2_AUTHENTICATION_DONE()                    (g_ucDPRx0Hdcp2Ctrl0 &= ~_BIT1)

#define GET_DP_RX0_HDCP2_WAITING_H_PRIME_CPIRQ_ASSERTED()         (bit)(g_ucDPRx0Hdcp2Ctrl1 & _BIT1)
#define SET_DP_RX0_HDCP2_WAITING_H_PRIME_CPIRQ_ASSERTED()         (g_ucDPRx0Hdcp2Ctrl1 |= _BIT1)
#define CLR_DP_RX0_HDCP2_WAITING_H_PRIME_CPIRQ_ASSERTED()         (g_ucDPRx0Hdcp2Ctrl1 &= ~_BIT1)

#define GET_DP_RX0_HDCP2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED()  (bit)(g_ucDPRx0Hdcp2Ctrl1 & _BIT0)
#define SET_DP_RX0_HDCP2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED()  (g_ucDPRx0Hdcp2Ctrl1 |= _BIT0)
#define CLR_DP_RX0_HDCP2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED()  (g_ucDPRx0Hdcp2Ctrl1 &= ~_BIT0)

#define SET_DP_RX0_HDCP2_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive |= _BIT0)
#define CLR_DP_RX0_HDCP2_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive &= ~_BIT0)

#define GET_DP_RX0_HDCP2_MODE()                                   (ScalerGetBit(PB_1A_HDCP_IRQ, _BIT1) == _BIT1)

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Macro of RX HDCP2 Authentication
//--------------------------------------------------
#define GET_DP_RX0_HDCP2_AUTH_STATE()                             (g_stDpRx0Hdcp2AuthInfo.b4AuthState)
#define SET_DP_RX0_HDCP2_AUTH_STATE(x)                            (g_stDpRx0Hdcp2AuthInfo.b4AuthState = (x))

#define GET_DP_RX0_HDCP2_AUTH_STATE_CHANGE()                      (g_stDpRx0Hdcp2AuthInfo.b1AuthStateChange)
#define SET_DP_RX0_HDCP2_AUTH_STATE_CHANGE()                      (g_stDpRx0Hdcp2AuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_RX0_HDCP2_AUTH_STATE_CHANGE()                      (g_stDpRx0Hdcp2AuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_RX0_HDCP2_AUTH_REPEATER_PROC_TIMEOUT()             (g_stDpRx0Hdcp2AuthInfo.b1AuthRepeaterProcTimeout)
#define SET_DP_RX0_HDCP2_AUTH_REPEATER_PROC_TIMEOUT()             (g_stDpRx0Hdcp2AuthInfo.b1AuthRepeaterProcTimeout = _TRUE)
#define CLR_DP_RX0_HDCP2_AUTH_REPEATER_PROC_TIMEOUT()             (g_stDpRx0Hdcp2AuthInfo.b1AuthRepeaterProcTimeout = _FALSE)

#define GET_DP_RX0_HDCP2_UPSTREAM_EVENT()                         (g_stDpRx0Hdcp2AuthInfo.ucAuthUpstreamEvent)
#define SET_DP_RX0_HDCP2_UPSTREAM_EVENT(x)                        (g_stDpRx0Hdcp2AuthInfo.ucAuthUpstreamEvent = (x))
#define CLR_DP_RX0_HDCP2_UPSTREAM_EVENT()                         (g_stDpRx0Hdcp2AuthInfo.ucAuthUpstreamEvent = _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_NONE)

#define GET_DP_RX0_HDCP2_AUTH_CPIRQ_TIMRE()                       (g_stDpRx0Hdcp2AuthInfo.b1AuthCpIrqTimer)
#define SET_DP_RX0_HDCP2_AUTH_CPIRQ_TIMRE()                       (g_stDpRx0Hdcp2AuthInfo.b1AuthCpIrqTimer = _TRUE)
#define CLR_DP_RX0_HDCP2_AUTH_CPIRQ_TIMRE()                       (g_stDpRx0Hdcp2AuthInfo.b1AuthCpIrqTimer = _FALSE)

#define GET_DP_RX0_HDCP2_CONTENT_STREAM_MANAGEMENT()              (g_stDpRx0Hdcp2AuthInfo.b1AuthHdcp2ContentStreamManage)
#define SET_DP_RX0_HDCP2_CONTENT_STREAM_MANAGEMENT()              (g_stDpRx0Hdcp2AuthInfo.b1AuthHdcp2ContentStreamManage = _TRUE)
#define CLR_DP_RX0_HDCP2_CONTENT_STREAM_MANAGEMENT()              (g_stDpRx0Hdcp2AuthInfo.b1AuthHdcp2ContentStreamManage = _FALSE)

#define GET_DP_RX0_HDCP2_HDCP1_CONTENT_STREAM_MANAGEMENT()        (g_stDpRx0Hdcp2AuthInfo.b1AuthHdcp1ContentStreamManage)
#define SET_DP_RX0_HDCP2_HDCP1_CONTENT_STREAM_MANAGEMENT()        (g_stDpRx0Hdcp2AuthInfo.b1AuthHdcp1ContentStreamManage = _TRUE)
#define CLR_DP_RX0_HDCP2_HDCP1_CONTENT_STREAM_MANAGEMENT()        (g_stDpRx0Hdcp2AuthInfo.b1AuthHdcp1ContentStreamManage = _FALSE)

#define GET_DP_RX0_HDCP2_REPEATER_AUTH_1_START()                  (g_stDpRx0Hdcp2AuthInfo.b1AuthRepeaterAuth1Start)
#define SET_DP_RX0_HDCP2_REPEATER_AUTH_1_START()                  (g_stDpRx0Hdcp2AuthInfo.b1AuthRepeaterAuth1Start = _TRUE)
#define CLR_DP_RX0_HDCP2_REPEATER_AUTH_1_START()                  (g_stDpRx0Hdcp2AuthInfo.b1AuthRepeaterAuth1Start = _FALSE)

#define GET_DP_RX0_HDCP2_REPEATER_AUTH_2_START()                  (g_stDpRx0Hdcp2AuthInfo.b1AuthRepeaterAuth2Start)
#define SET_DP_RX0_HDCP2_REPEATER_AUTH_2_START()                  (g_stDpRx0Hdcp2AuthInfo.b1AuthRepeaterAuth2Start = _TRUE)
#define CLR_DP_RX0_HDCP2_REPEATER_AUTH_2_START()                  (g_stDpRx0Hdcp2AuthInfo.b1AuthRepeaterAuth2Start = _FALSE)

#define GET_DP_RX0_HDCP2_REPEATER_CAPABLE()                       (ScalerDpRx0GetDpcdBitInfo(0x06, 0x92, 0x1F, _BIT0) == _BIT0)

#define SET_DP_RX0_HDCP2_REPEATER_CAPABLE()                       {\
                                                                    ScalerDpRx0SetDpcdBitValue(0x06, 0x92, 0x1F, ~_BIT0, _BIT0);\
                                                                    g_pucDPRx0Caps[2] |= _BIT0;\
                                                                  }

#define CLR_DP_RX0_HDCP2_REPEATER_CAPABLE()                       {\
                                                                    ScalerDpRx0SetDpcdBitValue(0x06, 0x92, 0x1F, ~_BIT0, 0x00);\
                                                                    g_pucDPRx0Caps[2] &= 0xFE;\
                                                                  }
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucDPRx0Hdcp2Ctrl0;
extern BYTE g_ucDPRx0Hdcp2Ctrl1;
extern BYTE g_pucDpRx0Hdcp2dKey0[16];
extern BYTE g_pucDpRx0Hdcp2dKey1[16];
extern BYTE g_pucDpRx0Hdcp2VPrime[20];

#if(_DP_TX_SUPPORT == _ON)
extern StructDpRxHdcp2AuthInfo g_stDpRx0Hdcp2AuthInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx0Hdcp2Handler(void);
extern void ScalerDpRx0Hdcp2Handler_EXINT0(void);
extern void ScalerDpRx0Hdcp2LoadCertRrxKey(void);
extern void ScalerDpRx0Hdcp2ResetProc(void);
extern void ScalerDpRx0Hdcp2ResetProc_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerDpRx0Hdcp2SkeProc_WDINT(void);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx0Hdcp2RepeaterHandler(void);
extern void ScalerDpRx0Hdcp2SetRepeaterProcTimeout(void);
extern void ScalerDpRx0Hdcp2RepeaterCapableProc(BYTE ucInputPort, BYTE ucPortType);
#endif

#endif // End of #if(_D0_DP_EXIST == _ON)
#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)
