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
// ID Code      : RL6410_Series_ColorLibInternalInclude.h
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerFunctionCommonInclude.h"
#include "ScalerColorLibInterface.h"
#include "ScalerCommonRegLibInclude.h"
#include "ScalerCommonNVRamLibInclude.h"
#include "ScalerColorLibInclude.h"
#include "ScalerTconLibInclude.h"
#include "RL6410_Series_TconLibInclude.h"

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD ulDCR_LD_ABOVE_TH1_NUM;
    DWORD ulDCR_LD_ABOVE_TH2_NUM;
    BYTE pucWinMaxRGB[16];
} StructDCRStoreInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDCRStoreInfo g_stDCRStoreInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// Output Gamma
extern void ScalerColorOutputGammaChannelCtrl(BYTE ucColorChannel, WORD usOffset, bit bLocation);
extern void ScalerColorOutputGammaEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorRGBOutputGammaEnable(EnumFunctionOnOFF enumOn);

extern void ScalerColorRGB3DGammaEnable(EnumFunctionOnOFF enumOn);

extern void ScalerColorPCMInputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorPCMOutputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);
extern void ScalerColorPCMSRGBAdjust(EnumSrgbPrecision enumSrgbPrecision, BYTE *pucColorMatrixArray, BYTE ucBankNum, WORD usLength);

//SRGB
extern void ScalerColorSRGBSwap(EnumsRGBSwap enumsRGBSwap);
extern bit ScalerColorSRGBAdjust(BYTE *pucSRGBArray, EnumSrgbPrecision enumPrecision);

// UltraVivid
extern bit ScalerColorUltraVividGetStatus(void);

// ICM
extern void ScalerColorSCMAdjust(BYTE ucAdjustOption1, BYTE ucAdjustOption2);

// PCM
extern WORD ScalerColorPCMGetTableAddress(EnumPCMType enumPCMMode);
extern BYTE ScalerColorPCMGetTableBank(void);

extern bit ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(void);
extern bit ScalerColorSRGBAdjust(BYTE *pucSRGBArray, EnumSrgbPrecision enumPrecision);

extern void ScalerColorDDomainDBApply(EnumDBApply enumDBApply);
