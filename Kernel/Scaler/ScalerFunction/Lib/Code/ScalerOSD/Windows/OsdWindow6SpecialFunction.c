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
// ID Code      : OsdWindow6SpecialFunction.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerOSDLibInternalInclude.h"

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


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerOsdWindow6SpecialFunction(EnumOsdWindow6FunctionType enumOsdWindow6FunctionType);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set window 6 Special function
// Input Value  : enumOsdWindow6FunctionType   -> _OSD_WINDOW_6_FUNCTION_DISABLE                    or _OSD_WINDOW_6_FUNCTION_NO_BLENDING_BOTH                  or
//                                                _OSD_WINDOW_6_FUNCTION_NO_BLENDING_FOREGROUND     or _OSD_WINDOW_6_FUNCTION_NO_BLENDING_BACKGROUND            or
//                                                _OSD_WINDOW_6_FUNCTION_BLENDING_BOTH
// Output Value :
//--------------------------------------------------
void ScalerOsdWindow6SpecialFunction(EnumOsdWindow6FunctionType enumOsdWindow6FunctionType)
{
    if(enumOsdWindow6FunctionType != _OSD_WINDOW_6_FUNCTION_DISABLE)
    {
        ScalerSetBit(P3A_21_FRAME_CTRL_21, ~(_BIT6 | _BIT3 | _BIT2), (_BIT6 | ((enumOsdWindow6FunctionType - _OSD_WINDOW_6_FUNCTION_NO_BLENDING_BOTH) << 2)));
    }
    else
    {
        ScalerSetBit(P3A_21_FRAME_CTRL_21, ~(_BIT6 | _BIT3 | _BIT2), 0x00);
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdWindow6SpecialFunction(_OSD_WINDOW_6_FUNCTION_NO_BLENDING_FOREGROUND);
*/
