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
// ID Code      : ScalerTMDSRx1HDCP2_SeptPhyInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
//--------------------------------------------------
// Definitions of HDCP 2.2 Authentication State
//--------------------------------------------------
#define GET_TMDS_RX1_HDCP2_AKE_INIT_RECEIVED()                      (bit)(g_ucTmdsRx1Hdcp2Ctrl & _BIT7)
#define SET_TMDS_RX1_HDCP2_AKE_INIT_RECEIVED()                      (g_ucTmdsRx1Hdcp2Ctrl |= _BIT7)
#define CLR_TMDS_RX1_HDCP2_AKE_INIT_RECEIVED()                      (g_ucTmdsRx1Hdcp2Ctrl &= ~_BIT7)

#define GET_TMDS_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (bit)(g_ucTmdsRx1Hdcp2Ctrl & _BIT6)
#define SET_TMDS_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (g_ucTmdsRx1Hdcp2Ctrl |= _BIT6)
#define CLR_TMDS_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (g_ucTmdsRx1Hdcp2Ctrl &= ~_BIT6)

#define GET_TMDS_RX1_HDCP2_AKE_STORED_KM_RECEIVED()                 (bit)(g_ucTmdsRx1Hdcp2Ctrl & _BIT5)
#define SET_TMDS_RX1_HDCP2_AKE_STORED_KM_RECEIVED()                 (g_ucTmdsRx1Hdcp2Ctrl |= _BIT5)
#define CLR_TMDS_RX1_HDCP2_AKE_STORED_KM_RECEIVED()                 (g_ucTmdsRx1Hdcp2Ctrl &= ~_BIT5)

#define GET_TMDS_RX1_HDCP2_LC_INIT_RECEIVED()                       (bit)(g_ucTmdsRx1Hdcp2Ctrl & _BIT4)
#define SET_TMDS_RX1_HDCP2_LC_INIT_RECEIVED()                       (g_ucTmdsRx1Hdcp2Ctrl |= _BIT4)
#define CLR_TMDS_RX1_HDCP2_LC_INIT_RECEIVED()                       (g_ucTmdsRx1Hdcp2Ctrl &= ~_BIT4)

#define GET_TMDS_RX1_HDCP2_SKE_SEND_EKS_RECEIVED()                  (bit)(g_ucTmdsRx1Hdcp2Ctrl & _BIT3)
#define SET_TMDS_RX1_HDCP2_SKE_SEND_EKS_RECEIVED()                  (g_ucTmdsRx1Hdcp2Ctrl |= _BIT3)
#define CLR_TMDS_RX1_HDCP2_SKE_SEND_EKS_RECEIVED()                  (g_ucTmdsRx1Hdcp2Ctrl &= ~_BIT3)

#define GET_TMDS_RX1_HDCP2_AUTHENTICATION_DONE()                    (bit)(g_ucTmdsRx1Hdcp2Ctrl & _BIT2)
#define SET_TMDS_RX1_HDCP2_AUTHENTICATION_DONE()                    (g_ucTmdsRx1Hdcp2Ctrl |= _BIT2)
#define CLR_TMDS_RX1_HDCP2_AUTHENTICATION_DONE()                    (g_ucTmdsRx1Hdcp2Ctrl &= ~_BIT2)

#define SET_TMDS_RX1_HDCP2_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive |= _BIT1)
#define CLR_TMDS_RX1_HDCP2_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive &= ~_BIT1)

//--------------------------------------------------
// Macro of HDCP 2.2 Authentication State
//--------------------------------------------------
#define GET_TMDS_RX1_HDCP2_AUTH_STATE()                             (g_stTmdsRx1Hdcp2AuthInfo.b4AuthState)
#define SET_TMDS_RX1_HDCP2_AUTH_STATE(x)                            (g_stTmdsRx1Hdcp2AuthInfo.b4AuthState = (x))

#define GET_TMDS_RX1_HDCP2_MODE()                                   (ScalerGetBit(P2D_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7)
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
extern BYTE g_ucTmdsRx1Hdcp2Ctrl;
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
extern void ScalerTMDSRx1Hdcp2Handler(void);
extern void ScalerTMDSRx1Hdcp2Initial(void);
extern void ScalerTMDSRx1Hdcp2IntHandler_EXINT0(void);
extern void ScalerTMDSRx1Hdcp2ReAuthEvent(void);
extern void ScalerTMDSRx1Hdcp2ResetProc(void);
extern void ScalerTMDSRx1Hdcp2ResetProc_EXINT0(void);
#endif
#endif

