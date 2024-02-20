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
// ID Code      : ScalerDPTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_TX_SUPPORT == _ON)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_TX_DOWNSTREAM_MAIN_LINK_POWER_STATUS()       (ScalerGetBit(PBC_A1_DPTX_PHY_CTRL1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != (_BIT3 | _BIT2 | _BIT1 | _BIT0))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpTxInitialReset(void);
extern void ScalerDpTxSSTDisplayFormatSetting(void);
extern BYTE ScalerDpTxSetTPSxPattern(void);
extern bit ScalerDpTxLinkRateReduce(EnumDPTxLTResult enumDPTxLTResult);
extern bit ScalerDpTxLaneCountReduce(EnumDPTxLTResult enumDPTxLTResult);
extern void ScalerDpTxAuxPowerOffProc(void);
extern void ScalerDpTxAuxSwingSetting(void);
extern void ScalerDpTxSignalInitialSetting(void);
extern bit ScalerDpTxMeasureGetMeasureResult(StructMeasureSyncData *pstMeasureSyncHV);
extern bit ScalerDpTxMeasureInputInfo(void);
extern bit ScalerDpTxInputMSAInfo(void);
extern bit ScalerDpTxCloneCheckMSAInfo(BYTE ucInputPort);
extern bit ScalerDpTxCloneCheckInterlaceVtotal(void);
extern void ScalerDpTxCloneSwitchFormatConversionMux(BYTE ucInputPort);
extern bit ScalerDpTxLinkStatusCheck(void);

#endif // End of #if(_DP_TX_SUPPORT == _ON)
