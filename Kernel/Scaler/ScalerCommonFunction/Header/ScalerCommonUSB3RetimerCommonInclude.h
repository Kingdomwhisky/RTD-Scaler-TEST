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
// ID Code      : ScalerCommonUSB3RetimerCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_USB3_RETIMER_INITIAL()               (g_b1Usb3SetInitial)
#define SET_USB3_RETIMER_INITIAL()               (g_b1Usb3SetInitial = _TRUE)
#define CLR_USB3_RETIMER_INITIAL()               (g_b1Usb3SetInitial = _FALSE)
#define GET_USB3_RETIMER_ENABLE()                (g_b1Usb3SetEnable)
#define SET_USB3_RETIMER_ENABLE()                (g_b1Usb3SetEnable = _TRUE)
#define CLR_USB3_RETIMER_ENABLE()                (g_b1Usb3SetEnable = _FALSE)
#define GET_USB3_DISABLE_BY_PINASS_C_E()         (g_b1Usb3DisableByPinAssCE)
#define SET_USB3_DISABLE_BY_PINASS_C_E()         (g_b1Usb3DisableByPinAssCE = _TRUE)
#define CLR_USB3_DISABLE_BY_PINASS_C_E()         (g_b1Usb3DisableByPinAssCE = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_b1Usb3SetInitial;
extern bit g_b1Usb3SetEnable;
extern bit g_b1Usb3DisableByPinAssCE;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerUSB3RetimerDisable_EXINT0(void);

