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
// ID Code      : RL6492_Series_GlobalInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _M2PLL_SYS_DIV                                  13
#define _M2PLL_MEASURE_DIV                              4
#define _SYS_USE_ISO_CLK                                ((bit)ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT3) ? _TRUE : _FALSE)

//--------------------------------------------------
// Definition of Global Interrupt Event
//--------------------------------------------------
#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
#define SET_EVENT_DEN_START_INT(x)                      (g_ucGlobalIntEventDenStart = (x))
#define GET_EVENT_DEN_START_INT()                       (g_ucGlobalIntEventDenStart)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
extern BYTE g_ucGlobalIntEventDenStart;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerGlobalDoubleBufferEnable(bit bEn);
extern void ScalerGlobalIDDomainDBSetTriggerEvent(void);
extern void ScalerGlobalDoubleBufferConfigReset(void);
extern bit ScalerGlobalGetDBStatus(void);
extern void ScalerGlobalCrystalClkSel(EnumClkSel enumClkSel);
extern void ScalerGlobalWatchDog(bit bEnable);

