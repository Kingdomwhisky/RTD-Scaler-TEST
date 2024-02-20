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
// ID Code      : OsdBlankCommandColorExtension.c
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
void ScalerOsdBlankCommandColorExtension(bit bEnable);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set OSD blank command color extension enable/disable
// Input Value  : bEnable   -> _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerOsdBlankCommandColorExtension(bit bEnable)
{
    ScalerSetBit(P3A_33_FRAME_CTRL_33, ~(_BIT5), ((BYTE)(~bEnable) << 5));
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdBlankCommandColorExtension(_ENABLE);
    ScalerOsdBlankFont(ROW(0), COL(0), LENGTH(1), HEIGHT(1), VALUES(72), BGCOLOR(17), _OSD_BLINKING_EFFECT_DISABLE);

*/
