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
// ID Code      : OsdReferenceDelay.c
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
void ScalerOsdReferenceDelay(EnumOsdMapType enumOsdMapType, EnumOsdReferenceType enumOsdReferenceType);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set osd delay reference to which osd
// Input Value  : enumOsdMapType       -> _OSD_A or _OSD_B
//                enumOsdReferenceType -> _OSD_FIRST_DELAY or _OSD_SECOND_DELAY
// Output Value :
//--------------------------------------------------
void ScalerOsdReferenceDelay(EnumOsdMapType enumOsdMapType, EnumOsdReferenceType enumOsdReferenceType)
{
    if(enumOsdMapType == _OSD_A)
    {
        ScalerSetBit(P3A_18_FRAME_CTRL_18, ~_BIT2, (enumOsdReferenceType << 2));
    }
    else
    {
        ScalerSetBit(P3A_18_FRAME_CTRL_18, ~_BIT1, (enumOsdReferenceType << 1));
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdReferenceDelay(_OSD_B, _OSD_SECOND_DELAY);
*/



