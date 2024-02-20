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
// ID Code      : ScalerCommonTypeCPowerInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
#define GET_RX0_OUTPUT_VOL()            ((WORD)(g_stTpcRx0PowerInfo.b12Rx0OutputVol))
#define GET_RX0_OUTPUT_CUR()            ((WORD)(g_stTpcRx0PowerInfo.b10Rx0OutputCur))
#endif // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern StructTypeCPowerInfo g_stTpcRx0PowerInfo;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerTypeCPowerClkSel(BYTE ucClockSel);
extern WORD ScalerTypeCPowerGetAdcOutput(EnumTypeCAdcChannel enumChannel);

