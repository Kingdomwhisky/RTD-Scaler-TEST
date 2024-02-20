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
// ID Code      : ScalerColorLibInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of DCR Adjust Option
//--------------------------------------------------
typedef enum
{
    _DCR_ABOVE_TH1_NUM,
    _DCR_ABOVE_TH1_VAL,
#if(_DCR_BIT_MODE != _DCR_GEN_0_1_8BIT)
    _DCR_ABOVE_TH2_NUM,
    _DCR_ABOVE_TH2_VAL,
#endif
    _DCR_HIGH_LV_VAL_R,
    _DCR_LOW_LV_VAL_R,
    _DCR_HIGH_LV_VAL_G,
    _DCR_LOW_LV_VAL_G,
    _DCR_HIGH_LV_VAL_B,
    _DCR_LOW_LV_VAL_B,
#if(_DCR_BIT_MODE != _DCR_GEN_0_1_8BIT)
    _DCR_Y_MAX_VAL,
    _DCR_Y_MIN_VAL,
#endif
    _DCR_ABOVE_TH1_VAL_HIGH,
#if(_DCR_BIT_MODE != _DCR_GEN_0_1_8BIT)
    _DCR_ABOVE_TH2_VAL_HIGH,
#endif
} EnumDCRAdjOption;

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
// Brightness & Contrast
extern void ScalerColorBrightnessEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorBrightnessGetSetting(EnumBriConCoefType enumBriConCoefType, WORD *pusData);
extern void ScalerColorContrastEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorContrastGetSetting(EnumBriConCoefType enumBriConCoefType, WORD *pusData);

// Color Sampling
extern void ScalerColor422To444(void);

// Color Conversion
extern EnumColorSpace ScalerColorGetColorSpace(void);
extern bit ScalerColorGetColorSpaceRGB(EnumColorSpace enumColorSpace);
extern void ScalerColorSetRGBLimitRange(bit bRGBLimitRange);
extern EnumColorRGBQuantization ScalerColorGetRGBQuantizationRange(void);
extern EnumColorimetry ScalerColorGetColorimetry(void);
extern EnumColorimetryExt ScalerColorGetExtColorimetry(void);
extern void ScalerColorSetYCCFullRange(bit bYCCFullRange);
extern EnumColorYCCQuantization ScalerColorGetYCCQuantizationRange(void);
extern void ScalerColorSetColorimetry(bit bHDTVMode);
extern void ScalerColorSpaceConvertIDomainEnable(bit bOn);
extern void ScalerColorSpaceConvertDDomainEnable(bit bOn);
extern void ScalerColorSpaceConvertLoadTable(void);

// DCC
extern bit ScalerColorDCCGetDataReadyStatus(void);
extern void ScalerColorDCCClrDataReadyStatus(void);
extern WORD ScalerColorDCCReadResult(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption);

// DCR
extern void ScalerColorDCREnable(EnumFunctionOnOFF enumOn);
extern bit ScalerColorDCRGetDataReadyStatus(void);
extern void ScalerColorDCRClrDataReadyStatus(void);
extern void ScalerColorDCRDataRefreshControl(bit bEnable);

// Digital Filter
extern void ScalerColorDigitalFilterEnhancePhaseAdjust(BYTE *pucBGRGain);
extern void ScalerColorDigitalFilterEnable(EnumFunctionOnOFF enumOn);

// Highlight Window
extern void ScalerColorHLWDDomainAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
extern void ScalerColorHLWDDomainEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorHLWBorderAdjust(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
extern void ScalerColorHLWBorderEnable(bit bTopBorderEn, bit bBottomBorderEn, bit bLeftBorderEn, bit bRightBorderEn);

extern void ScalerColorHLWDCCAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWDCRAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWOutputGammaAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWSRGBAdjust(EnumHLWType enumHLWType, EnumDBApply enumDBApply);
extern void ScalerColorHLWICMAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWPanelUniformityAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);
extern void ScalerColorHLWRGB3DGammaAdjust(EnumHLWType enumHLWActive, EnumDBApply enumDBApply);

// IDither
extern void ScalerColorIDitherEnable(EnumFunctionOnOFF enumOn);

// PCM
extern void ScalerColorPCMInputGammaLoadTable(BYTE ucSelect);

// Ringing Filter
extern void ScalerColorRingingFilterOff(void);

// Other
extern BYTE ScalerColorGetColorDepth(void);

// Scaling
extern bit ScalerColorScalingByPassTableSel(void);

// Double Buffer
extern bit ScalerColorWaitDDomainDBApply(void);
