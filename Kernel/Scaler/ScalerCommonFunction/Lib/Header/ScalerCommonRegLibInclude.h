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
// ID Code      : ScalerCommonRegLibInclude.h No.0000
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

extern void ScalerWrite(WORD usAddr, WORD usLength, BYTE *pucArray, bit bAutoInc);
extern void ScalerRead(WORD usAddr, WORD usLength, BYTE *pucArray, bit bAutoInc);

extern void ScalerSetDataPortByte(WORD usAddr, BYTE ucValue1, BYTE ucValue2);
extern void ScalerGetDataPortByte(WORD usAddr, BYTE ucValue, WORD usLength, BYTE *pucArray, bit bAutoInc);
extern void ScalerSetDataPortBit(WORD usAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr);
extern BYTE ScalerGetDataPortBit(WORD usAddr, BYTE ucValue, BYTE ucAnd);

extern BYTE ScalerGetDataPortSingleByte(WORD usAddr, BYTE ucValue);
extern void ScalerSetDataPortWord(WORD usAddr, BYTE ucValue1, WORD usValue2);
extern WORD ScalerGetDataPortWord(WORD usAddr, BYTE ucValue, bit bAutoInc);
extern void ScalerSetDataPortDword(WORD usAddr, BYTE ucValue1, DWORD ulValue2);
extern DWORD ScalerGetDataPortDword(WORD usAddr, BYTE ucValue, bit bAutoInc);

extern void ScalerBurstWrite(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, WORD usHostAddr, BYTE ucTableType, bit bTableLocation);

extern BYTE ScalerGlobalGetIDCode(void);
extern BYTE ScalerGlobalGetIDCode_EXINT0(void);
extern BYTE ScalerGlobalGetIDCode_WDINT(void);

