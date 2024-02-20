/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonUSB3RetimerInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB3_RETIMER_SUPPORT == _ON)
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
extern void ScalerUSB3RetimerInitial(void);
extern void ScalerUSB3RetimerStartup(bit bEnable);
extern void ScalerUSB3RetimerUfpPhyConfig(void);
extern void ScalerUSB3RetimerUfpIrqEnable(bit bEnable);
// extern void ScalerUSB3RetimerUfpIrqEnable_EXINT3(bit bEnable);
// extern void ScalerUSB3RetimerUfpPhyConfig_EXINT3(void);
extern void ScalerUSB3RetimerDfpEnable(bit bControl);
// extern void ScalerUSB3RetimerDfpEnable_EXINT3(bit bControl);
#endif // End of #if(_USB3_RETIMER_SUPPORT == _ON)


