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
// ID Code      : ScalerCommonDPTxHDCP2Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_TX_HDCP2_LOAD_KEY_EN()                          (bit)(g_ucDpTxHdcp2LoadKey & _BIT7)
#define SET_DP_TX_HDCP2_LOAD_KEY_EN()                          (g_ucDpTxHdcp2LoadKey |= _BIT7)
#define CLR_DP_TX_HDCP2_LOAD_KEY_EN()                          (g_ucDpTxHdcp2LoadKey &= ~_BIT7)

#define GET_DP_TX_HDCP2_LOAD_KEY_FINISH()                      (bit)(g_ucDpTxHdcp2LoadKey & _BIT6)
#define SET_DP_TX_HDCP2_LOAD_KEY_FINISH()                      (g_ucDpTxHdcp2LoadKey |= _BIT6)
#define CLR_DP_TX_HDCP2_LOAD_KEY_FINISH()                      (g_ucDpTxHdcp2LoadKey &= ~_BIT6)

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern BYTE g_ucDpTxHdcp2LoadKey;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerDpTxHdcp2DcpLlcRsaInit(void);
extern void ScalerDpTxHdcp2LoadKeyProc(BYTE ucLoadKeyType, BYTE *pucDpTxHdcp2Key);
#endif // End of #if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

