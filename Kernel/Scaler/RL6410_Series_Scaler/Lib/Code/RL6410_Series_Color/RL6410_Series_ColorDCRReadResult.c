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
// ID Code      : RL6410_Series_ColorDCRReadResult.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_ColorLibInternalInclude.h"

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
DWORD ScalerColorDCRReadResult(EnumDCRAdjOption enumDCRReadOption);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Read DCR Histogram Result
// Input Value  : DCR Histogram Information Option
// Output Value : DCR Histogram Information
// Note         : When get _DCR_ABOVE_TH_VAL(8bit or 10bit), should get _DCR_ABOVE_TH_VAL_HIGH / _DCR_ABOVE_TH_VAL_10BIT_HIGH first
//              : then get _DCR_ABOVE_TH_VAL / _DCR_ABOVE_TH_VAL_10BIT
//--------------------------------------------------
DWORD ScalerColorDCRReadResult(EnumDCRAdjOption enumDCRReadOption)
{
    DWORD ulResult = 0;

    if((GET_DCR_READY_STATUS() == _FALSE) ||
       (ScalerGetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, _BIT0) == _BIT0))
    {
        return 0;
    }

    switch(enumDCRReadOption)
    {
        case _DCR_ABOVE_TH1_NUM:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_02_DCR_ABOVE_TH1_NUM_2 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 3, pData, _NON_AUTOINC);
            ulResult = PDATA_DWORD(0) >> 8;
            break;

        case _DCR_ABOVE_TH1_VAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_05_DCR_ABOVE_TH1_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
            ulResult = (PDATA_DWORD(0) << 2) | ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT7 | _BIT6)) >> 6);
            break;

        case _DCR_ABOVE_TH1_VAL_HIGH:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_05_DCR_ABOVE_TH1_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
            ulResult = ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT7 | _BIT6 | _BIT5)) >> 3) | ((pData[0] & 0xC0) >> 6);
            break;

        case _DCR_ABOVE_TH2_NUM:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_09_DCR_ABOVE_TH2_NUM_2 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 3, pData, _NON_AUTOINC);
            ulResult = PDATA_DWORD(0) >> 8;
            break;

        case _DCR_ABOVE_TH2_VAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_0C_DCR_ABOVE_TH2_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
            ulResult = (PDATA_DWORD(0) << 2) | ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT3 | _BIT2)) >> 2);
            break;

        case _DCR_ABOVE_TH2_VAL_HIGH:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_0C_DCR_ABOVE_TH2_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
            ulResult = ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT3 | _BIT2 | _BIT1)) << 1) | ((pData[0] & 0xC0) >> 6);
            break;

        case _DCR_HIGH_LV_VAL_R:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_14_DCR_HIGH_LV_VAL_R_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2C_DCR_HIGH_LV_VAL_R_0 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, &pData[1], _NON_AUTOINC);
            ulResult = PDATA_DWORD(0) >> 22;
            break;

        case _DCR_LOW_LV_VAL_R:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_15_DCR_LOW_LV_VAL_R_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2D_DCR_LOW_LV_VAL_R_0 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, &pData[1], _NON_AUTOINC);
            ulResult = PDATA_DWORD(0) >> 22;
            break;

        case _DCR_HIGH_LV_VAL_G:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1A_DCR_HIGH_LV_VAL_G_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2E_DCR_HIGH_LV_VAL_G_0 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, &pData[1], _NON_AUTOINC);
            ulResult = PDATA_DWORD(0) >> 22;
            break;

        case _DCR_LOW_LV_VAL_G:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1B_DCR_LOW_LV_VAL_G_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2F_DCR_LOW_LV_VAL_G_0 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, &pData[1], _NON_AUTOINC);
            ulResult = PDATA_DWORD(0) >> 22;
            break;

        case _DCR_HIGH_LV_VAL_B:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_20_DCR_HIGH_LV_VAL_B_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_30_DCR_HIGH_LV_VAL_B_0 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, &pData[1], _NON_AUTOINC);
            ulResult = PDATA_DWORD(0) >> 22;
            break;

        case _DCR_LOW_LV_VAL_B:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_21_DCR_LOW_LV_VAL_B_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_31_DCR_LOW_LV_VAL_B_0 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, &pData[1], _NON_AUTOINC);
            ulResult = PDATA_DWORD(0) >> 22;
            break;

        case _DCR_Y_MAX_VAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_28_DCR_Y_MAX_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_32_DCR_Y_MAX_0 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, &pData[1], _NON_AUTOINC);
            ulResult = PDATA_DWORD(0) >> 22;
            break;

        case _DCR_Y_MIN_VAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_29_DCR_Y_MIN_1 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_33_DCR_Y_MIN_0 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 1, &pData[1], _NON_AUTOINC);
            ulResult = PDATA_DWORD(0) >> 22;
            break;

        default:
            break;
    }

    return ulResult;
}
