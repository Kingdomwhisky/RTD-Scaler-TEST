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
// ID Code      : ScalerCommonLibInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define GET_DWORD_MUL_DIV(x, y, z)                        (ScalerComputeDwordMulDiv((x), (y), (z)))

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
extern StructTimerSampleMS g_pstTimerCursorMS[];
extern StructTimerSampleUS g_pstTimerCursorUS[];

extern BYTE g_ucTimerCursorUsedMS;
extern BYTE g_ucTimerCursorUsedUS;
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern DWORD ScalerComputeDwordMulDiv(DWORD ulA, DWORD ulB, DWORD ulC);

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
extern WORD ScalerDebugGetTimerCursorMSDifference(EnumDebugTimeCursor enumIndex);
extern WORD ScalerDebugGetTimerCursorUSDifference(EnumDebugTimeCursor enumIndex);
#endif

