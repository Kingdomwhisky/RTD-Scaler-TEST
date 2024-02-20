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
// ID Code      : RL6492_Series_ColorLibInclude.h No.0000
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
// IDither
extern void ScalerColorIDitherResetFrameCnt(void);

// DDither
extern void ScalerColorDDitherLoadDitherTable(BYTE code *pucDitherTable, BYTE ucBankAddress);
extern void ScalerColorDDitherLoadTempoTable(BYTE code *pucTempoTable, BYTE ucBankAddress);
extern void ScalerColorDDitherLoadSetting(DWORD ulSettingOption);

// HLW
extern void ScalerColorHLWIDLTILSRAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
extern void ScalerColorHLWIDLTILSREnable(EnumFunctionOnOFF enumOn);

// ICM
extern void ScalerColorICMUVOffsetLoadTable(BYTE code *pucICMTable, BYTE ucBankNum);
extern void ScalerColorICMBRILoadTable(BYTE code *pucICMTable, BYTE ucBankNum);

// Six Color ICM
extern void ScalerColorSixColorInitialNormal(void);
extern void ScalerColorSixColorAdjustNormal(BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);
extern void ScalerColorSixColorInitialDell(void);
extern void ScalerColorSixColorAdjustDell(BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);

// PCM
extern void ScalerColorPCMInputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern WORD ScalerColorPCMGetTableAddress(EnumPCMType enumPCMMode);
extern BYTE ScalerColorPCMGetTableBank(void);

