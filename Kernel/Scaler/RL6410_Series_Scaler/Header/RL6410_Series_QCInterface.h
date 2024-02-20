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
// ID Code      : RL6410_Series_QCInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern BYTE xdata g_ucTestCount;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_FACTORY_RTD_QC_SUPPORT == _ON)

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
extern BYTE ScalerQCA0PortTest(void);
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
extern BYTE ScalerQCD0PortTest(void);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
extern BYTE ScalerQCD1PortTest(void);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
extern BYTE ScalerQCD2PortTest(void);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
extern BYTE ScalerQCD3PortTest(void);
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
extern BYTE ScalerQCD4PortTest(void);
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
extern BYTE ScalerQCD5PortTest(void);
#endif

extern void ScalerQCAllDigitalFunctionDisable(void);
extern bit ScalerQCDebug(BYTE ucNum, BYTE ucResult);
extern BYTE ScalerQCGetIPCount(void);
#endif
