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
// ID Code      : ScalerDualLinkDVIInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DUAL_DVI_SUPPORT == _ON)
extern bit ScalerDualLinkDVIGetDualDVIMode(EnumSourceSearchPort enumInputPort);
extern bit ScalerDualLinkDVIDoubleCheck(EnumSourceSearchPort enumSourceSearchPort, WORD usHwidth, WORD usVHeight);
extern void ScalerDualLinkDVIClockInvert(void);

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
extern void ScalerDualLinkDVIRx2Switch(bit bEnable);
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
extern void ScalerDualLinkDVIRx3Switch(bit bEnable);
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
extern void ScalerDualLinkDVIRx4Switch(bit bEnable);
#endif

#endif // End of #if(_DUAL_DVI_SUPPORT == _ON)

