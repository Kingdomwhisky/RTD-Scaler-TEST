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
// ID Code      : RL6449_Series_DPInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_FREESYNC_SUPPORT == _ON)
#define _DP_FREESYNC_IVSTART                            0
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpSecDataReset(BYTE ucInputPort);
extern bit ScalerDpHdcpCheckValid(BYTE ucInputPort);
extern void ScalerDpFirstActiveProc(BYTE ucInputPort);
extern void ScalerDpPowerSwitch(EnumPowerAction enumPowerAction);

#if(_DP_FREESYNC_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpTxSSTSetAmdSpdInfo(bit bPlayback);
#endif
#endif

#endif
