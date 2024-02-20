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
// ID Code      : OsdEnableDisable.c
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
void ScalerOsdEnableOsd(void);
void ScalerOsdDisableOsd(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable Display OSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerOsdEnableOsd(void)
{
    ScalerOsdCircuitActivated(_ENABLE);

    // OSD Overlay Port Enable
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Disable Display OSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerOsdDisableOsd(void)
{
    // OSD Overlay Port Enable
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT0, 0x00);
}

