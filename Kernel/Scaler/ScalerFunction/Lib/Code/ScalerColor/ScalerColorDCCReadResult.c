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
// ID Code      : ScalerColorDCCReadResult.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerColorLibInternalInclude.h"

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
WORD ScalerColorDCCReadResult(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Read DCC Statistic Result
// Input Value  : pucReadArray, DCCReadOption
// Output Value : Read Result
// Notice : Under _DCC_GEN_0, all result are one byte. Under _DCC_GEN_0, S0~S6 are one byte, but Y_MAX and Y_MIN are one word.
//--------------------------------------------------
WORD ScalerColorDCCReadResult(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption)
{
    WORD usResult = 0;

    if(pucReadArray == _NULL_POINTER)
    {
        return 0;
    }

    switch(enumDCCReadOption)
    {
        case _DCC_S0:
            usResult = pucReadArray[2];
            break;

        case _DCC_S1:
            usResult = pucReadArray[3];
            break;

        case _DCC_S2:
            usResult = pucReadArray[4];
            break;

        case _DCC_S3:
            usResult = pucReadArray[5];
            break;

        case _DCC_S4:
            usResult = pucReadArray[6];
            break;

        case _DCC_S5:
            usResult = pucReadArray[7];
            break;

        case _DCC_S6:
            usResult = pucReadArray[8];
            break;

        case _DCC_Y_MAX:
#if(_DCC_Y_BIT_MODE == _DCC_Y_8BIT)
            usResult = pucReadArray[0];
#elif(_DCC_Y_BIT_MODE == _DCC_Y_10BIT)
            usResult = (((WORD)pucReadArray[0]) << 2) + (pucReadArray[9] >> 6);
#endif
            break;

        case _DCC_Y_MIN:
#if(_DCC_Y_BIT_MODE == _DCC_Y_8BIT)
            usResult = pucReadArray[1];
#elif(_DCC_Y_BIT_MODE == _DCC_Y_10BIT)
            usResult = (((WORD)pucReadArray[1]) << 2) + (pucReadArray[10] >> 6);
#endif
            break;

        default:
            break;
    }

    return usResult;
}
