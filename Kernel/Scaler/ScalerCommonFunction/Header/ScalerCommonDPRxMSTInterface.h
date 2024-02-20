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
// ID Code      : ScalerCommonDPRxMSTInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_MST_SUPPORT == _ON)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerDpRxMstPowerOnInitial(void);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
extern void ScalerDpRxMstInitial(EnumDPMSTPort enumRxMstPort);
extern void ScalerDpRxMstRx0Rx1switch(EnumDPMSTPort enumMstCapablePort);
#endif

extern void ScalerDpRxMstInfoBackup(BYTE ucInputPort, EnumDpMstBackup enumDpMstBackup);
extern void ScalerDpRxMstHandler(void);
extern void ScalerDpRxMstStreamsHandler(void);

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpRxMstCheckMsgTransition(void);
#endif

extern void ScalerDpRxMstCableUnplugReset(BYTE ucInputPort);
extern void ScalerDpRxMstStreamMuxChangeHandler(void);
extern EnumDPMSTPort ScalerDpRxMstGetCapablePort(void);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
extern EnumSourceSearchPort ScalerDpRxMstGetInputPort(EnumDPMSTPort enumMstPort);
extern bit ScalerDpRxMstGetSrcMsgEnable(EnumSourceSearchPort enumInputPort);
extern bit ScalerDpRxMstGetMstCapability(EnumSourceSearchPort enumInputPort);
extern void ScalerDpRxMstCapabilitySwitch(EnumSourceSearchPort enumInputPort, bit bEn);
#endif

#endif

