/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6463_Series_ColorLibInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
// Color Conversion
extern void ScalerColorSpaceConvert(EnumColorSpace enumColorSpace, EnumDBApply enumDBApply);
extern void ScalerColorSpaceConvertUltraVividSupport(EnumColorSpace enumColorSpace, EnumDBApply enumDBApply);
extern void ScalerColorMdomainForceYUV(EnumColorSpace enumColorSpace, EnumDBApply enumDBApply);

// DCC
extern void ScalerColorDCCEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorDCCNormalizeFactorAdjust(void);
extern void ScalerColorDCCAdjust(BYTE code *pucDccTable, BYTE ucBankAddress);
extern void ScalerColorDCCHistoSetting(void);
extern void ScalerColorDCCGetHistoInfo(BYTE *pucReadArray);

// DCR
extern void ScalerColorDCRAdjust(WORD usThreshold1, WORD usThreshold2, EnumDCRMeasureSel enumDCRMeasureSel);
extern DWORD ScalerColorDCRReadResult(EnumDCRAdjOption enumDCRReadOption);
extern WORD ScalerColorDCRGetAverage(EnumDCRAverageOption enumDCRAverageOption, DWORD ulDivider);

// HLW
extern void ScalerColorHLWUltraVividAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWYpeakingAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWPCMAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWIAPSGainAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);

// ICM
extern void ScalerColorICMEnable(EnumFunctionOnOFF enumOn);

// Output Gamma
extern void ScalerColorOutputGammaEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorOutputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorOutputGammaWriteTable(BYTE *pucGammaTableArray, EnumGammaChannel enumGammaChannel, BYTE ucOffset, WORD usDataLength);

// PCM
extern void ScalerColorPCMInputGammaEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorPCMInputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);

extern void ScalerColorPCMLoadTable(EnumPCMType enumPCMMode, BYTE *pucIGammaTableArray, BYTE *pucOGammaTableArray, BYTE *pucColorMatrixArray, BYTE ucBankNum, WORD usLength, BYTE ucGammaBankNum);
extern void ScalerColorPCMOutputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorPCMSRGBAdjust(EnumSrgbPrecision enumSrgbPrecision, BYTE *pucColorMatrixArray, BYTE ucBankNum, WORD usLength);

// SRGB
extern void ScalerColorSRGBEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorSetSRGBGlobalHueSat(SWORD shDeltaHue, WORD usDeltaSat);
extern bit ScalerColorSRGBAdjust(BYTE *pucSRGBArray, EnumSrgbPrecision enumPrecision);

// UltraVivid
extern void ScalerColorUltraVividAdjust(BYTE code *pucUltraVividSetting, BYTE ucBankNum);
extern void ScalerColorUltraVividEnable(EnumFunctionOnOFF enumFunctionOnOff, EnumDBApply enumDBApply);
extern  bit ScalerColorUltraVividSetDisable(void);

// Ypeaking
extern void ScalerColorYpeaking(bit bOn);

// Highlight Window
extern void ScalerColorHLWBRICTSAdjust(EnumBriConHLWType enumHLWActive, EnumDBApply enumDBApply);

// Contrast
extern void ScalerColorContrastAdjust(EnumBriConCoefType enumBriConCoefType, WORD *pusData);

// Brightness
extern void ScalerColorBrightnessAdjust(EnumBriConCoefType enumBriConCoefType, WORD *pusData);

// Ringing Filter
extern void ScalerColorRingingFilterAdjust(BYTE *pucOffsetCoef);
