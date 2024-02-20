/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonUSB3RetimerInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB3_RETIMER_SUPPORT == _ON)
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
extern void ScalerUSB3RetimerHandler(BYTE ucPowerStatus);
extern void ScalerUSB3RetimerIntHandler_EXINT3(void);
extern void ScalerUSB3RetimerSetPSStatus(EnumUSBPSSupportStatus enumUSBPSSupportStatus);
extern void ScalerUSB3RetimerSetPDStatus(EnumUSBPDSupportStatus enumUSBPDSupportStatus);
extern EnumUSBPSSupportStatus ScalerUSB3RetimerGetPSStatus(void);
extern EnumUSBPDSupportStatus ScalerUSB3RetimerGetPDStatus(void);
extern void ScalerUSB3RetimerHubUfpSwitchProc(EnumHubInputPort enumHubInputPort);
extern void ScalerUSB3RetimerPowerSwitch(EnumPowerAction enumPowerAction);
extern void ScalerUSB3RetimerSetHubUfpStatus(EnumHubInputPort enumHubInputPort);
extern EnumHubInputPort ScalerUSB3RetimerGetHubUfpStatus(void);
#endif // End of #if(_USB3_RETIMER_SUPPORT == _ON)

