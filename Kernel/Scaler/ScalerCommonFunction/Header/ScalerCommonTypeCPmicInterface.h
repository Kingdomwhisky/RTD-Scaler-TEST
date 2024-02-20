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
// ID Code      : ScalerCommonTypeCPmicInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON) && (_TYPE_C_PMIC_TYPE != _PMIC_NONE))
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
extern bit ScalerTypeCPmicIICRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
extern BYTE ScalerTypeCPmicIICRead_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
#endif
extern bit ScalerTypeCPmicIICWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
extern BYTE ScalerTypeCPmicIICWrite_EXINT0(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
extern BYTE ScalerTypeCPmicIICWrite_WDINT(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
#endif // End of #if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicOperationMode ScalerTypeCPmicRx0ReadPpsOperationModeStatus_EXINT0(void);
#endif // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON) && (_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON))
