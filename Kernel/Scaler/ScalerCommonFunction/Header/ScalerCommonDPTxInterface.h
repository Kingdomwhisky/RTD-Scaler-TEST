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
// ID Code      : ScalerCommonDPTxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_DP_TX_SUPPORT == _ON)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
//--------------------------------------------------
// Macros of DP Tx Link Config Set by User
//--------------------------------------------------
#define GET_DP_TX_CONFIG_SETTING()                           (g_ucDpTxConfigSetting)
#define SET_DP_TX_CONFIG_SETTING(x)                          (g_ucDpTxConfigSetting = (x))
#endif

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
extern BYTE g_ucDpTxConfigSetting;
#endif


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerDpTxJudgeHandler(void);
extern void ScalerDpTxModeHandler(void);
extern void ScalerDpTxIntHandle_EXINT0(void);
extern void ScalerDpTxHPDProc(void);
extern void ScalerDpTxCloneOutputProc(BYTE ucInputPort, BYTE ucPortType, bit bClone);
#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
extern void ScalerDpTxCloneModeSwitch(bit bClone);
extern void ScalerDpTxBlockStatusCheck(void);
#endif
extern bit ScalerDpTxGetDownstreamHPDStatus(void);
extern WORD ScalerDpTxGetDownStreamEdidBw(void);
#endif // End of #if(_DP_TX_SUPPORT == _ON)

