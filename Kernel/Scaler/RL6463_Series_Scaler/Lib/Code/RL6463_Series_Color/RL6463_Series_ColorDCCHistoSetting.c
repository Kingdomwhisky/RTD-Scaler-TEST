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
// ID Code      : RL6463_Series_ColorDCCHistoSetting.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6463_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of DCC Histogram
//--------------------------------------------------
#define _DCC_HISTO_YMAX_LB                    0x00
#define _DCC_HISTO_YMIN_HB                    0xFF

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
void ScalerColorDCCHistoSetting(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set Y_MAX_LB, Y_MIN_HB
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCHistoSetting(void)
{
    // Set Y max lower bound and Y min higher bound
    ScalerSetBit(P7_C7_DCC_CTRL_0, ~(_BIT1 | _BIT0), _PAGE0);
    ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_07_PORT_PAGE0_Y_MAX_LB_H);
    ScalerSetByte(P7_CA_DCC_DATA_PORT, (BYTE)_DCC_HISTO_YMAX_LB);
    ScalerSetByte(P7_CA_DCC_DATA_PORT, (BYTE)_DCC_HISTO_YMIN_HB);

    // Enable DCC
    ScalerSetBit(P7_C7_DCC_CTRL_0, ~_BIT7, _BIT7);
}
