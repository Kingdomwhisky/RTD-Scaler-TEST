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
// ID Code      : ScalerPLLInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#define _DDRPLL_VCO_CLK_1X                          0
#define _DDRPLL_VCO_CLK_2X                          1
#define _DDRPLL_CLK_SOURCE                          _DDRPLL_VCO_CLK_2X
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
extern void ScalerPLLM2PLLPower(BYTE ucOn);
extern void ScalerM2PLLDiv(BYTE ucDiv);
extern void ScalerPLLSetDPLLReset(void);
extern void ScalerPLLSetDPLLSSC(BYTE ucDclkSpreadSpeed, BYTE ucSpreadRange);
extern void ScalerPLLSetDPLLFreq(DWORD ulFreq);
extern void ScalerDPLLFineTuneFrameSyncLineBuffer(void);

#if(_FRC_SUPPORT == _ON)
extern void ScalerDPLLFineTuneFrameSyncFrameBuffer(void);
#endif

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
#if(_MPLL_STRUCT_TYPE != _MPLL_STRUCT_COMBO_M2PLL)
extern void ScalerPLLSetMPLLFreq(DWORD ulFreq);
#endif
#endif

#if(_VGA_SUPPORT == _ON)
extern bit ScalerAPLLAdjust(WORD usCurrHTotal, WORD usCurrHFreq);
extern WORD ScalerAPLLGetIHTotal(void);
#endif

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
extern void ScalerPLLDDR2PLLCtrl(bit bEnable);
extern void ScalerPLLDDR2PLLOutputCtrl(bit bEnable);
extern void ScalerPLLSetDDR2PLLFreq(DWORD ulFreq);
#endif

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
extern void ScalerPLLSetDDRPLLFreq(DWORD ulFreq);
#endif

