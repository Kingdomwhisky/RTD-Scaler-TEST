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
// ID Code      : RL6463_Series_ColorDCRGetAverage.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6463_Series_ColorLibInternalInclude.h"

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

    if(GET_DCR_READY_STATUS() == _FALSE)
    {
        return 0;
    }

    switch(enumDCRAverageOption)
    {
        case _DCR_ABOVE_TH1_VAL_TOTAL:
            ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_05_DCR_ABOVE_TH1_VAL_4 << 2) | _BIT1 | _BIT0);
            ScalerRead(P7_D9_DCR_DATA_PORT, 4, pData, _NON_AUTOINC);
            usResult = PDATA_DWORD(0) / ulDivider;
            break;

        default:
            break;
    }

    return usResult;
}
