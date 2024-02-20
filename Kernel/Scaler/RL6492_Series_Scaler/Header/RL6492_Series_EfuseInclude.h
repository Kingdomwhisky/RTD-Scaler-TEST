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
// ID Code      : RL6492_Series_EfuseInclude.h No.0000
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
#ifndef __RL6492_SERIES_EFUSE_H__
#define __RL6492_SERIES_EFUSE_H__
//--------------------------------------------------
// Enumerations of Efuse Data State
//--------------------------------------------------

typedef enum
{
    _EFUSE_NONE,
    _EFUSE_LVDS_DRIV,
    _EFUSE_TYPE_C_1M_OHM_RESISTOR,
    _EFUSE_CP_WAFER_INFO,
    _EFUSE_CC_RESISTANCE,
    _EFUSE_CC_ATTACH_VOLTAGE,
    _EFUSE_CC_BMC_TX_RX_VOLTAGE,
    _EFUSE_ADC_SLOP_OFFSET,
    _EFUSE_VBUS_COMPARATOR,
    _EFUSE_CHECK_BIT,
} EnumEfuseDataState;

#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerEfuseGetData(EnumEfuseDataState enumEfuseDataState, BYTE ucEfuseLength, BYTE *pucEfuseData);

