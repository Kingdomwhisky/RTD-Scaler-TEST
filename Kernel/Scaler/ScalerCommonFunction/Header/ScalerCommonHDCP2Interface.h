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
// ID Code      : ScalerCommonHDCP2Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_HDCP_2_2_FUNCTION_GEN == _HDCP_2_2_GEN_2)
#if(_HDCP_2_2_SUPPORT == _ON)
extern void ScalerHdcp2DownLoadCalculateKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray, BYTE ucRSAType);
extern void ScalerHdcp2Handler(void);
extern void ScalerHdcp2IntHandler_EXINT0(void);
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && (_HDMI_PORT_EXIST == _ON))
extern void ScalerHdcp2ResetTMDSProc(BYTE ucInputPort);
#endif
extern bit ScalerHdcp2RxPairingCalculate(BYTE *pucHdcp2KPriv, BYTE ucIndex);
#endif

#if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT))
extern bit ScalerHdcp2DeRsaCalculateforSign(void);
extern bit ScalerHdcp2RxSha256CalculateforSign(BYTE *pucInputArray, BYTE ucCalCount);
extern void ScalerHdcp2DownLoadCalculateKeyforSign(WORD usLength, BYTE *pucReadArray, EnumSignKeyInfo enumRSAType);
extern void ScalerHdcp2ReadoutRsaforSign(BYTE *pucArray);
extern void ScalerHdcp2ReadoutHashforSign(BYTE *pucArray);
extern void ScalerHdcp2ReleaseRsaforSign(void);
#endif
#endif
