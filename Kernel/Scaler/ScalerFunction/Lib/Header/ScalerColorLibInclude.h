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
// ID Code      : ScalerColorLibInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
// Color Conversion
extern EnumColorSpace ScalerColorGetColorSpace(void);
extern bit ScalerColorGetColorSpaceRGB(EnumColorSpace enumColorSpace);
extern void ScalerColorSpaceLoadYuv2RgbTable(EnumColorSpace enumColorSpace, bit bUltraVividSupport);

// IDither
extern void ScalerColorIDitherEnable(EnumFunctionOnOFF enumOn);

// DDither
extern void ScalerColorDDitherEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorDDitherLoadSeqTable(BYTE code *pucSeqTable, BYTE ucSeqLength, BYTE ucBankAddress);

// Digital Filter
extern void ScalerColorDigitalFilterNSmearAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterNRDisableAdjust(void);
extern void ScalerColorDigitalFilterPSmearAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterNRingAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterPRingAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterExtensionAdjust(void);

// Highlight Window
extern void ScalerColorHLWDDomainAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
extern void ScalerColorHLWDDomainEnable(EnumFunctionOnOFF enumOn);

// IDither
extern void ScalerColorIDitherLoadDitherTable(BYTE code *pucDitherTable, BYTE ucBankAddress);
extern void ScalerColorIDitherLoadSeqTable(BYTE code *pucSeqTable, BYTE ucSeqLength, BYTE ucBankAddress);
extern void ScalerColorIDitherLoadTemporalTable(BYTE code *pucTempoTable, BYTE ucBankAddress);
extern void ScalerColorIDitherLoadSetting(WORD usAdjustOption);

// DCC
extern void ScalerColorDCCSetMeasureRegion(EnumHLWType enumHLWType);

// ICM
extern void ScalerColorICMAdjust(BYTE ucAdjustOption1, BYTE ucAdjustOption2);

// Other
extern BYTE ScalerColorGetColorDepth(void);
extern BYTE ScalerColorSpaceConvertIDomainWaitEventForAutoBlockToggle(void);
extern void ScalerColorSpaceConvertDDomainWaitEventForAutoBlockToggle(BYTE ucDVSCnt);

