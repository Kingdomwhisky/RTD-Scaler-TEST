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
// ID Code      : RL6492_Series_ColorLibInterface.h No.0000
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
extern WORD ScalerColorDCRGetMaxRGB(void);

// DDither
extern void ScalerColorDDitherAdvanceSettingAdjust(BYTE code *pucReAlignTable, BYTE code *pucReAlignTempoTable, BYTE code *pucLsbTable, BYTE code *pucAdvanceSettingTable, BYTE ucBankAddress);

// HLW
extern void ScalerColorHLWUltraVividAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWPCMAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);

// IAPSGain
extern void ScalerColorIAPSGainEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorIAPSGainValueAdjust(WORD usGainValue);
extern void ScalerColorIAPSGainSoftClampAdjust(BYTE ucSoftClampFac);

// ICM
extern void ScalerColorICMEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorSCMLoadTable(BYTE code *pucSCMTable, BYTE ucBankNum);

// Output Gamma
extern void ScalerColorOutputGammaEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorOutputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorRGBOutputGammaInitial(void);
extern void ScalerColorRGBOutputGammaEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorRGBOutputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
// Panel Uniformity
extern void ScalerColorPanelUniformityEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorPanelUniformityAdjust(BYTE *pucUNILUT, WORD usUNILUTSize, BYTE ucBankNum, EnumUniformityModeSelect enumUniformityMode, EnumUniformityLevelSelect enumUniformityLevel);
extern void ScalerColorPanelUniformityOffsetEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorPanelUniformityOffsetAdjust(BYTE *pucUNILUT, WORD usUNILUTSize, BYTE ucBankNum);
extern void ScalerColorPanelUniformityDecayAdjust(BYTE *pucUNILUT, WORD usUNILUTSize, BYTE ucBankNum, EnumUniformityModeSelect enumUniformityMode, BYTE ucDecayDegree);

// PCM
extern void ScalerColorPCMInputGammaEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorPCMInputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorPCMRGBInputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);

extern void ScalerColorPCMLoadTable(EnumPCMType enumPCMMode, BYTE *pucIGammaTableArray, BYTE *pucOGammaTableArray, BYTE *pucColorMatrixArray, BYTE ucBankNum, WORD usLength, BYTE ucGammaBankNum);
extern void ScalerColorPCMOutputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorPCMSRGBAdjust(EnumSrgbPrecision enumSrgbPrecision, BYTE *pucColorMatrixArray, BYTE ucBankNum, WORD usLength);

// RGB 3D Gamma
extern void ScalerColorRGB3DGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorRGB3DGammaEnable(EnumFunctionOnOFF enumOn);

// ScaleDown
extern void ScalerColorSetScalingDownMaskLSB(void);

// SRGB
extern void ScalerColorSRGBEnable(EnumFunctionOnOFF enumOn);
#if(_GLOBAL_HUE_SATURATION == _ON)
extern void ScalerColorSetSRGBGlobalHueSat(SWORD shDeltaHue, WORD usDeltaSat);
#endif
extern void ScalerColorSRGBSwap(EnumsRGBSwap enumsRGBSwap);
extern bit ScalerColorSRGBAdjust(BYTE *pucSRGBArray, EnumSrgbPrecision enumPrecision);

// UltraVivid
extern void ScalerColorUltraVividAdjust(BYTE code *pucUltraVividSetting, BYTE ucBankNum);
extern void ScalerColorUltraVividEnable(EnumFunctionOnOFF enumFunctionOnOff, EnumDBApply enumDBApply);
extern bit ScalerColorUltraVividSetDisable(void);
extern void ScalerColorUltraVividInitial(void);

// Highlight Window
extern void ScalerColorHLWBRICTSAdjust(EnumBriConHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWIAPSGainAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);

// Contrast
extern void ScalerColorContrastAdjust(EnumBriConCoefType enumBriConCoefType, WORD *pusData);

// Brightness
extern void ScalerColorBrightnessAdjust(EnumBriConCoefType enumBriConCoefType, WORD *pusData);

// Ringing Filter
extern void ScalerColorRingingFilterAdjust(BYTE *pucOffsetCoef);
