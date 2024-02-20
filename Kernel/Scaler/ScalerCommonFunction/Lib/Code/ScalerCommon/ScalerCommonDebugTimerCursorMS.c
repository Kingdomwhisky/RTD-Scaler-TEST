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

#include "ScalerCommonLibInternalInclude.h"

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonDebugTimerCursorMS.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructTimerSampleMS g_pstTimerCursorMS[_DEBUG_TIME_CURSOR_END];
BYTE g_ucTimerCursorUsedMS;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
WORD ScalerDebugGetTimerCursorMSDifference(EnumDebugTimeCursor enumIndex);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Time Cursor Difference for MS
// Input Value  : Debug Time Cursor
// Output Value : Time Difference for Ms
//--------------------------------------------------
WORD ScalerDebugGetTimerCursorMSDifference(EnumDebugTimeCursor enumIndex)
{
    // Check if cursor is used
    if(((g_ucTimerCursorUsedMS >> enumIndex) & _BIT0) == _DISABLE)
    {
        return 0xFFFF;
    }
    else
    {
        // Calculate counter difference
        if(g_pstTimerCursorMS[enumIndex].usCounter_Start <= g_pstTimerCursorMS[enumIndex].usCounter_End)
        {
            return g_pstTimerCursorMS[enumIndex].usCounter_End - g_pstTimerCursorMS[enumIndex].usCounter_Start;
        }
        else
        {
            return 0xFFFF - g_pstTimerCursorMS[enumIndex].usCounter_Start + g_pstTimerCursorMS[enumIndex].usCounter_End;
        }
    }
}

