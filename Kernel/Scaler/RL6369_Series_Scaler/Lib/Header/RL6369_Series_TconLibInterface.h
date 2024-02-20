/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6369_Series_TconLibInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerTcon7Enable(bit bEnable);
extern void ScalerTcon7Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon8Enable(bit bEnable);
extern void ScalerTcon8Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon9Enable(bit bEnable);
extern void ScalerTcon9Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon11Enable(bit bEnable);
extern void ScalerTcon11Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon12Enable(bit bEnable);
extern void ScalerTcon12Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon13Enable(bit bEnable);
extern void ScalerTcon13Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void ScalerTcon7InvEnable(bit bEnable);
extern void ScalerTcon8InvEnable(bit bEnable);
extern void ScalerTcon9InvEnable(bit bEnable);
extern void ScalerTcon11InvEnable(bit bEnable);
extern void ScalerTcon12InvEnable(bit bEnable);
extern void ScalerTcon13InvEnable(bit bEnable);
