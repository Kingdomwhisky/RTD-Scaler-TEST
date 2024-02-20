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
// ID Code      : OsdCompressionCtrl.c
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
void ScalerOsdCompressionCtrl(EnumOsdDecodeCompressionType enumDecodeCompression, bit bCompressionEnable);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set decode compression data or not, Compression enable/disable
// Input Value  : enumDecodeCompression -> _OSD_DECODE_COMPRESSED or _OSD_DECODE_NON_COMPRESSED
// Input Value  : ucConpressionEn -> _OSD_COMPRESSION_DISABLE or _OSD_COMPRESSION_ENABLE
// Output Value :
//--------------------------------------------------
void ScalerOsdCompressionCtrl(EnumOsdDecodeCompressionType enumDecodeCompression, bit bCompressionEnable)
{
    ScalerSetBit(P3A_17_FRAME_CTRL_17, ~(_BIT1), enumDecodeCompression);
    ScalerSetBit(P3A_17_FRAME_CTRL_17, ~(_BIT0), bCompressionEnable);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdCompressionCtrl(_OSD_DECODE_NON_COMPRESSED, _OSD_COMPRESSION_ENABLE);
*/


