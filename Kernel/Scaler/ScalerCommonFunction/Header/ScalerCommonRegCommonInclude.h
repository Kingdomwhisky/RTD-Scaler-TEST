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
// ID Code      : ScalerCommonRegCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of  Control Register Address
//--------------------------------------------------

//--------------------------------------------------
// Macros of controlling the scaler registers
//--------------------------------------------------
#define ScalerSetBit(usAddr, ucAnd, ucOr)           (*((volatile BYTE xdata *)(usAddr)) = (*((volatile BYTE xdata *)(usAddr)) & (ucAnd)) | (ucOr))
#define ScalerGetBit(usAddr, ucAnd)                 (*((volatile BYTE xdata *)(usAddr)) & (ucAnd))
#define ScalerGetByte(usAddr)                       (*((volatile BYTE xdata *)(usAddr)))
#define ScalerSetByte(usAddr, ucValue)              (*((volatile BYTE xdata *)(usAddr)) = (ucValue))
#define ScalerGetWord(usAddr)                       (*((volatile WORD xdata *)(usAddr)))
#define ScalerSetWord(usAddr, usValue)              (*((volatile WORD xdata *)(usAddr)) = (usValue))
#define ScalerGetDWord(usAddr)                      (*((volatile DWORD xdata *)(usAddr)))
#define ScalerSetDWord(usAddr, ulValue)             (*((volatile DWORD xdata *)(usAddr)) = (ulValue))
#define ScalerMaskSetDWord(usAddr, ulMask, ulValue) (*((volatile DWORD xdata *)(usAddr)) = (((DWORD)ulMask) & ScalerGetDWord(usAddr)) | ((~((DWORD)ulMask)) & ulValue))

//--------------------------------------------------
// Macros of controlling the scaler registers for EXINT1
//--------------------------------------------------
#define ScalerSetBit_EXINT(usAddr, ucAnd, ucOr)     (*((volatile BYTE xdata *)(usAddr)) = (*((volatile BYTE xdata *)(usAddr)) & (ucAnd)) | (ucOr))
#define ScalerGetBit_EXINT(usAddr, ucAnd)           (*((volatile BYTE xdata *)(usAddr)) & (ucAnd))
#define ScalerGetByte_EXINT(usAddr)                 (*((volatile BYTE xdata *)(usAddr)))
#define ScalerSetByte_EXINT(usAddr, ucValue)        (*((volatile BYTE xdata *)(usAddr)) = (ucValue))
#define ScalerGetWord_EXINT(usAddr)                 (*((volatile WORD xdata *)(usAddr)))
#define ScalerSetWord_EXINT(usAddr, usValue)        (*((volatile WORD xdata *)(usAddr)) = (usValue))

//--------------------------------------------------
// Macros of controlling the scaler registers for EXINT3
//--------------------------------------------------
#define ScalerSetBit_EXINT3(usAddr, ucAnd, ucOr)    (*((volatile BYTE xdata *)(usAddr)) = (*((volatile BYTE xdata *)(usAddr)) & (ucAnd)) | (ucOr))
#define ScalerGetBit_EXINT3(usAddr, ucAnd)          (*((volatile BYTE xdata *)(usAddr)) & (ucAnd))
#define ScalerGetByte_EXINT3(usAddr)                (*((volatile BYTE xdata *)(usAddr)))
#define ScalerSetByte_EXINT3(usAddr, ucValue)       (*((volatile BYTE xdata *)(usAddr)) = (ucValue))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

