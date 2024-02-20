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
// ID Code      : RL6492_Series_DPRx1HDCP2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_D1_DP_EXIST == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDCP 2.2 Authentication State
//--------------------------------------------------
#define GET_DP_RX1_HDCP2_MODE()                                   (ScalerGetBit(PB_1A_HDCP_IRQ, _BIT1) == _BIT1)

//--------------------------------------------------
// DP HDCP2 Type Value Reg Address
//--------------------------------------------------
#define _REG_DP_RX1_HDCP2_TYPE_AES0_VALUE                         PB_93_HDCP_TYPE_AES_0

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx1Hdcp2Handler(void);
extern void ScalerDpRx1Hdcp2Handler_EXINT0(void);
extern void ScalerDpRx1Hdcp2ResetProc(void);
extern void ScalerDpRx1Hdcp2ResetProc_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx1Hdcp2SkeProc_WDINT(void);
#endif

#endif // End of #if(_D1_DP_EXIST == _ON)
#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)

