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
// ID Code      : RL6410_Series_ColorDCRGetAverage.c
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
WORD ScalerColorDCRGetAverage(EnumDCRAverageOption enumDCRAverageOption, DWORD ulDivider);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get DCR Average Result
// Input Value  : stDCRResult : DCR Measute Result
//                ulDivider   : GET_MDOMAIN_OUTPUT_HWIDTH() * GET_MDOMAIN_OUTPUT_VHEIGHT() * n(3 or 8)
//                              n = 3; when DCR Measure _MEASURE_AVERAGE(R+G+B)
//                              n = 8; when DCR Measure _MEASURE_Y(2R+5G+B)
// Output Value : None
//--------------------------------------------------
WORD ScalerColorDCRGetAverage(EnumDCRAverageOption enumDCRAverageOption, DWORD ulDivider)
{
    WORD usResult = 0;

    BYTE ucHighPart = 0;
    DWORD ulLowPart = 0;

    if((ScalerGetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, _BIT0) == _BIT0) ||
       (GET_DCR_READY_STATUS() == _FALSE))
    {
        return 0;
    }

    switch(enumDCRAverageOption)
    {
        case _DCR_ABOVE_TH1_VAL_TOTAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_05_DCR_ABOVE_TH1_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
            ucHighPart = ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT7 | _BIT6 | _BIT5)) >> 3) | ((pData[0] & 0xC0) >> 6);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
            ulLowPart = (PDATA_DWORD(0) << 2) | ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT7 | _BIT6)) >> 6);
            break;

        case _DCR_ABOVE_TH2_VAL_TOTAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_0C_DCR_ABOVE_TH2_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5 << 2) | _BIT1 | _BIT0);
            ucHighPart = ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT3 | _BIT2 | _BIT1)) << 1) | ((pData[0] & 0xC0) >> 6);
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0 << 2) | _BIT1 | _BIT0);
            ulLowPart = (PDATA_DWORD(0) << 2) | ((ScalerGetByte(P7_D9_DCR_DATA_PORT) & (_BIT3 | _BIT2)) >> 2);
            break;

        default:
            break;
    }

    if(ucHighPart > 15)
    {
        usResult = (((((((DWORD)ucHighPart) << 27) % ulDivider) << 5) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 27) / ulDivider) << 5);
    }
    else if(ucHighPart > 7)
    {
        usResult = (((((((DWORD)ucHighPart) << 28) % ulDivider) << 4) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 28) / ulDivider) << 4);
    }
    else if(ucHighPart > 3)
    {
        usResult = (((((((DWORD)ucHighPart) << 29) % ulDivider) << 3) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 29) / ulDivider) << 3);
    }
    else if(ucHighPart > 1)
    {
        usResult = (((((((DWORD)ucHighPart) << 30) % ulDivider) << 2) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 30) / ulDivider) << 2);
    }
    else if(ucHighPart > 0)
    {
        usResult = (((((((DWORD)ucHighPart) << 31) % ulDivider) << 1) + (ulLowPart % ulDivider)) / ulDivider) + (ulLowPart / ulDivider) + (((((DWORD)ucHighPart) << 31) / ulDivider) << 1);
    }
    else
    {
        usResult = ulLowPart / ulDivider;
    }

    return usResult;
}
