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
// ID Code      : ScalerIDomainInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of underscan info
//--------------------------------------------------
#define GET_UNDERSCAN_VHEIGHT()                       (g_usUnderScanIVheight)
#define SET_UNDERSCAN_VHEIGHT(x)                      (g_usUnderScanIVheight = (x))

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_UNDERSCAN_SUPPORT == _ON)
extern WORD g_usUnderScanIVheight;
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerIDomainVgipSetInputCapture(void);
extern WORD ScalerIDomainVgipIHCaptureMaxEstimate(WORD usHPosition);

#if(_UNDERSCAN_SUPPORT == _ON)
extern WORD ScalerIDomainVgipGetVCaptureStartMinValue(void);
#endif
