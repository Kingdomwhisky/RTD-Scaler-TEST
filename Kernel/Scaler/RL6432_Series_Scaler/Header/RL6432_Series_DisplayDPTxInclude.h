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
// ID Code      : RL6432_Series_DisplayDPTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_PANEL_STYLE == _PANEL_DPTX)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#define SET_DISPLAY_DP_TX1_MVID_FW_MODE()                   (ScalerSetBit(P9C_F3_DPTX_TOP_RSV6, ~_BIT0, 0x00))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDisplayDPTxSSCSet(bit bSscEn);
extern void ScalerDisplayDPTxPhy(bit bOn);
extern void ScalerDisplayDPTxPLL(bit bOn);
extern void ScalerDisplayDPTxPower(bit bOn);
extern void ScalerDisplayDPTxSetLinkRate(void);

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
extern void ScalerDisplayDPTx1AuxPHYSet(BYTE ucMode);
extern void ScalerDisplayDPTx1SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
extern void ScalerDisplayDPTx1SignalInitialSetting(void);
extern EnumDisplayDPTxTrainPattern ScalerDisplayDPTx1SetTp2PatternType(void);
#endif

#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)
