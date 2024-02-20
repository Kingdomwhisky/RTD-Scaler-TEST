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
// ID Code      : RL6449_Series_ColorDCRGetMaxRGB.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6449_Series_ColorLibInternalInclude.h"

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
WORD ScalerColorDCRGetMaxRGB(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get DCR Max RGB
// Input Value  : None
// Output Value : Max RGB
//--------------------------------------------------
WORD ScalerColorDCRGetMaxRGB(void)
{
    WORD usResult = 0;

    if((ScalerGetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, _BIT0) == _BIT0) ||
       (GET_DCR_READY_STATUS() == _FALSE))
    {
        return 0;
    }

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_14_DCR_HIGH_LV_VAL_R_1 << 2) | _BIT1 | _BIT0);
    ScalerRead(P7_D9_DCR_DATA_PORT, 1, pData, _NON_AUTOINC);
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2C_DCR_HIGH_LV_VAL_R_0 << 2) | _BIT1 | _BIT0);
    ScalerRead(P7_D9_DCR_DATA_PORT, 1, &pData[1], _NON_AUTOINC);
    usResult = PDATA_WORD(0) >> 6;

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1A_DCR_HIGH_LV_VAL_G_1 << 2) | _BIT1 | _BIT0);
    ScalerRead(P7_D9_DCR_DATA_PORT, 1, pData, _NON_AUTOINC);
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2E_DCR_HIGH_LV_VAL_G_0 << 2) | _BIT1 | _BIT0);
    ScalerRead(P7_D9_DCR_DATA_PORT, 1, &pData[1], _NON_AUTOINC);
    if(usResult < (PDATA_WORD(0) >> 6))
    {
        usResult = PDATA_WORD(0) >> 6;
    }

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_20_DCR_HIGH_LV_VAL_B_1 << 2) | _BIT1 | _BIT0);
    ScalerRead(P7_D9_DCR_DATA_PORT, 1, pData, _NON_AUTOINC);
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_30_DCR_HIGH_LV_VAL_B_0 << 2) | _BIT1 | _BIT0);
    ScalerRead(P7_D9_DCR_DATA_PORT, 1, &pData[1], _NON_AUTOINC);
    if(usResult < (PDATA_WORD(0) >> 6))
    {
        usResult = PDATA_WORD(0) >> 6;
    }
    return usResult;
}
