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
// ID Code      : RL6369_Series_HDCP2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDCP_2_2_SUPPORT == _ON)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDCP 2.2 Authentication State
//--------------------------------------------------

#define GET_HDCP_2_2_AKE_INIT_RECEIVED()                            (bit)(g_ucHdcp2Ctrl & _BIT7)
#define SET_HDCP_2_2_AKE_INIT_RECEIVED()                            (g_ucHdcp2Ctrl |= _BIT7)
#define CLR_HDCP_2_2_AKE_INIT_RECEIVED()                            (g_ucHdcp2Ctrl &= ~_BIT7)

#define GET_HDCP_2_2_AKE_NO_STORED_KM_RECEIVED()                    (bit)(g_ucHdcp2Ctrl & _BIT6)
#define SET_HDCP_2_2_AKE_NO_STORED_KM_RECEIVED()                    (g_ucHdcp2Ctrl |= _BIT6)
#define CLR_HDCP_2_2_AKE_NO_STORED_KM_RECEIVED()                    (g_ucHdcp2Ctrl &= ~_BIT6)

#define GET_HDCP_2_2_AKE_STORED_KM_RECEIVED()                       (bit)(g_ucHdcp2Ctrl & _BIT5)
#define SET_HDCP_2_2_AKE_STORED_KM_RECEIVED()                       (g_ucHdcp2Ctrl |= _BIT5)
#define CLR_HDCP_2_2_AKE_STORED_KM_RECEIVED()                       (g_ucHdcp2Ctrl &= ~_BIT5)

#define GET_HDCP_2_2_LC_INIT_RECEIVED()                             (bit)(g_ucHdcp2Ctrl & _BIT4)
#define SET_HDCP_2_2_LC_INIT_RECEIVED()                             (g_ucHdcp2Ctrl |= _BIT4)
#define CLR_HDCP_2_2_LC_INIT_RECEIVED()                             (g_ucHdcp2Ctrl &= ~_BIT4)

#define GET_HDCP_2_2_SKE_SEND_EKS_RECEIVED()                        (bit)(g_ucHdcp2Ctrl & _BIT3)
#define SET_HDCP_2_2_SKE_SEND_EKS_RECEIVED()                        (g_ucHdcp2Ctrl |= _BIT3)
#define CLR_HDCP_2_2_SKE_SEND_EKS_RECEIVED()                        (g_ucHdcp2Ctrl &= ~_BIT3)

#define GET_HDCP_2_2_AUTHENTICATION_DONE()                          (bit)(g_ucHdcp2Ctrl & _BIT2)
#define SET_HDCP_2_2_AUTHENTICATION_DONE()                          (g_ucHdcp2Ctrl |= _BIT2)
#define CLR_HDCP_2_2_AUTHENTICATION_DONE()                          (g_ucHdcp2Ctrl &= ~_BIT2)

#define GET_HDCP_2_2_AUTHENTICATION_ACTIVE()                        (bit)(g_ucHdcp2Ctrl & _BIT0)
#define SET_HDCP_2_2_AUTHENTICATION_ACTIVE()                        (g_ucHdcp2Ctrl |= _BIT0)
#define CLR_HDCP_2_2_AUTHENTICATION_ACTIVE()                        (g_ucHdcp2Ctrl &= ~_BIT0)

//--------------------------------------------------
// Macro of HDCP 2.2 Authentication State
//--------------------------------------------------
#define GET_HDCP_2_2_AUTH_STATE()                                   (g_stRxHdcp2AuthInfo.b4AuthState)
#define SET_HDCP_2_2_AUTH_STATE(x)                                  (g_stRxHdcp2AuthInfo.b4AuthState = (x))

#define GET_TMDS_RX0_HDCP2_MODE()                                   (ScalerGetBit(P63_A0_HDCP_I2C_CTRL_A0, _BIT7) == _BIT7)
#define GET_TMDS_RX1_HDCP2_MODE()                                   (ScalerGetBit(P63_A0_HDCP_I2C_CTRL_A0, _BIT7) == _BIT7)
#define GET_TMDS_RX2_HDCP2_MODE()                                   (ScalerGetBit(P63_A0_HDCP_I2C_CTRL_A0, _BIT7) == _BIT7)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructHdcp2HDCPAuthInfo g_stRxHdcp2AuthInfo;
extern BYTE g_ucHdcp2Ctrl;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerHdcp2Initial(void);
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && (_HDMI_PORT_EXIST == _ON))
extern void ScalerHdcp2ResetTMDSProc(BYTE ucInputPort);
extern void ScalerHdcp2ReAuthEvent(EnumScalerTimerEventID enumEventID);
#endif
extern void ScalerHdcp2ResetProc_EXINT0(BYTE ucInputPort);

#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

