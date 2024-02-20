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
// ID Code      : ScalerFRCInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#define GET_DISP_LATENCY_RATIO()                                  (g_ucDispLatecnyRatio)
#define SET_DISP_LATENCY_RATIO(x)                                 (g_ucDispLatecnyRatio = (x))
#endif

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
#define GET_ASPECT_RATIO_MIN_DVH()                                (g_usAspectRatioMinDVHeight)
#define SET_ASPECT_RATIO_MIN_DVH(x)                               (g_usAspectRatioMinDVHeight = (x))
#endif
//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
extern BYTE g_ucDispLatecnyRatio;
#endif

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
extern WORD g_usAspectRatioMinDVHeight;
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************

