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
// ID Code      : RL6492_Series_PLLInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
// HW Fixed div 2 is disable (div2 of MPLL no control register)
#define _MPLL_FIXED_DIV                               _DIV_2// 1 -- > div2 is disable  2 --> div2 is enable

#define _REG_DPLL_N_F_CODE_0                          (P1_C0_DPLL_N_F_CODE_1)
#define _REG_DPLL_N_F_CODE_1                          (P1_C1_DPLL_N_F_CODE_2)
#define _REG_DPLL_N_F_CODE_2                          (P1_C2_DPLL_N_F_CODE_3)
#define _REG_DPLL_N_F_CODE_3                          (P1_C3_DPLL_N_F_CODE_4)
#define _REG_DPLL_SSCG_0                              (P1_CA_DPLL_SSCG_0)
#define _REG_DPLL_SSCG_1                              (P1_CB_DPLL_SSCG_1)
#define _REG_DPLL_SSCG_2                              (P1_CC_DPLL_SSCG_2)
#define _REG_DPLL_SSCG_3                              (P1_CD_DPLL_SSCG_3)
#define _REG_DPLL_SSCG_4                              (P1_CE_DPLL_SSCG_4)
#define _REG_DPLL_SSCG_5                              (P1_CF_DPLL_SSCG_5)
#define _REG_DPLL_ANALOG_SETTING_0                    (P1_D0_DPLL_ANALOG_SETTING_0)

#define GET_N_F_PLL_PREDIVIDER()                      (ScalerGetByte(P1_C9_DPLL_CLK_CTRL_1) + 2)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_DPTX)
extern bit ScalerPLLGetDptxPowerStatus(void);
#endif
extern DWORD ScalerPLLGetDPLLRefClk(DWORD ulFreq);

#if(_PANEL_STYLE == _PANEL_LVDS)
extern void ScalerPLLSetDisplayPLL(DWORD ulFreq);
#elif((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
extern void ScalerPLLSetDPLLRefPLL(DWORD ulFreq);
extern void ScalerPLLDPTxPLLReset(void);
#endif
