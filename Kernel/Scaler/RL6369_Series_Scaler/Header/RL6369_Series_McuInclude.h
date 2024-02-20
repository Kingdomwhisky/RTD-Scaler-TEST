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
// ID Code      : RL6369_Series_McuInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// MACRO for DDC Channel Select
//--------------------------------------------------
#define GET_DDC_CHANNEL()                               (MCU_FF22_IIC_CH_SEL & (_BIT2 | _BIT1 | _BIT0))

//--------------------------------------------------
// MACRO for VGADDC Channel SCL force low
//--------------------------------------------------
#define SET_VGADDC_SCL_FORCE_LOW()                      (MCU_FF1D_ADC_DDC_CONTROL_2 |= _BIT0)
#define CLR_VGADDC_SCL_FORCE_LOW()                      (MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT0)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMcuDdcDebounceSel(EnumClkSel enumClock);
extern void ScalerMcuDdcciSwitchPort(EnumDDCCIDebugMode enumMode, BYTE ucInputPort);
extern void ScalerMcuGpioInitial(void);
extern void ScalerMcuDdcInitial(void);
extern void ScalerMcuDdcRamEnable(void);
extern void ScalerMcuDdcciInitial(void);

#if((_DEBUG_MESSAGE_SUPPORT == _OFF) && ((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON)))
extern void ScalerMcuDdcciHoldScl_EXINT1(void);
#endif

extern void ScalerMcuSetISPChannel(WORD usISPChannel);
