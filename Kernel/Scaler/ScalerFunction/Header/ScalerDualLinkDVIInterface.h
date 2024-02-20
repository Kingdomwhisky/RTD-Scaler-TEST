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

#if(_DUAL_DVI_SUPPORT == _ON)

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerDualLinkDVIInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Enumerations of VGATOP Waiting Events (P30_E4)
//--------------------------------------------------

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerDualLinkDVIScanInitial(BYTE ucInputPort);
extern bit ScalerDualLinkDVIPSPreDetect(BYTE ucInputPort);
extern bit ScalerDualLinkDVINormalPreDetect(BYTE ucInputPort);
extern BYTE ScalerDualLinkDVIScanInputPort(BYTE ucInputPort);
#endif
