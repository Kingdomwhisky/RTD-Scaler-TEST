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
// ID Code      : RL6432_Series_OsdFont24x36OnOff.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6432_Series_OSDLibInternalInclude.h"

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
void ScalerOsdFont24x36OnOff(bit bOnOff);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Font 24x36 mode
// Input Value  : ucRowStart
// Input Value  : ucRowEnd
// Input Value  : ucColumnStart
// Input Value  : ucColumnEnd
// Output Value :
//--------------------------------------------------
void ScalerOsdFont24x36OnOff(bit bOnOff)
{
    ScalerSetBit(P3A_43_FRAME_CTRL_43, ~_BIT6, ((BYTE)bOnOff << 6));
}


