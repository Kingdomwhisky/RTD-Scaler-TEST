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

#include "ScalerCommonLibInternalInclude.h"

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonComputeDwordMulDiv.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define MULTIPLY_OVERFLOW32_CHECK(x, y)                      (((x) == 0) || ((y) == 0) || ((DWORD)(x) < (0xFFFFFFFF / (DWORD)(y))))

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
DWORD ScalerComputeDwordPowDiv(DWORD ulA, BYTE ucPow, DWORD ulB);
DWORD ScalerComputeDwordMulDiv(DWORD ulA, DWORD ulB, DWORD ulC);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Division for (A * 2^pow) / ulB
// Input Value  : A, ucPow, ulB
// Output Value : (A * 2^pow) / B ratio in 32-bit precision
//--------------------------------------------------
DWORD ScalerComputeDwordPowDiv(DWORD ulA, BYTE ucPow, DWORD ulB)
{
    DWORD ulResult = 0;

    do
    {
        ulResult <<= 1;

        if(ulA >= ulB)
        {
            ulResult += (ulA / ulB);
            ulA %= ulB;
        }

        ulA <<= 1;
    }
    while(ucPow-- != 0);

    return (ulA >= ulB) ? (ulResult + 1) : ulResult;
}

//--------------------------------------------------
// Description  : Multiplication and Division for DWORD
// Input Value  : A, B, C
// Output Value : A * B / C in 32-bit precision
//--------------------------------------------------
DWORD ScalerComputeDwordMulDiv(DWORD ulA, DWORD ulB, DWORD ulC)
{
    if(MULTIPLY_OVERFLOW32_CHECK(ulA, ulB) == _TRUE)
    {
        return ulA * ulB / ulC;
    }
    else
    {
        /// Let A = x1 * 2^16 + x2, B = x3 * 2^16 + x4
        /// --> A * B = (x1 * x3) * 2^32 + ((x1 * x4) + (x2 * x3)) * 2^16 + (x2 * x4)
        ///           = factor_32 * 2^32 + factor_00
        DWORD ulBase16_0 = (DWORD)HIWORD(ulA) * LOWORD(ulB);
        DWORD ulBase16_1 = (DWORD)LOWORD(ulA) * HIWORD(ulB);

        DWORD ulBase00 = (DWORD)LOWORD(ulA) * LOWORD(ulB);
        DWORD ulBase32 = (DWORD)HIWORD(ulA) * HIWORD(ulB);

        DWORD ulBuffer = ((DWORD)LOWORD(ulBase16_0) + LOWORD(ulBase16_1) + HIWORD(ulBase00));

        ulBase00 = ((((DWORD)LOWORD(ulBuffer)) << 16) | LOWORD(ulBase00));
        ulBase32 += ((DWORD)HIWORD(ulBase16_0) + HIWORD(ulBase16_1) + HIWORD(ulBuffer));

        return ScalerComputeDwordPowDiv(ulBase32, 32, ulC) +
               ScalerComputeDwordPowDiv(ulBase00, 0, ulC);
    }

    /*
    if((ulA >= ulC) &&
            (MULTIPLY_OVERFLOW_CHECK(ulB, ulC - 1) == _TRUE))
    {
        return (ulA / ulC * ulB) + ((ulA % ulC) * ulB / ulC);
    }
    else if((ulB >= ulC) &&
            (MULTIPLY_OVERFLOW_CHECK(ulA, ulC - 1) == _TRUE))
    {
        return (ulB / ulC * ulA) + ((ulB % ulC) * ulA / ulC);
    }
    else
    {
        DWORD ulRemainA = ulA % ulC;
        DWORD ulRemainB = ulB % ulC;
        DWORD ulResult = ((ulA / ulC) * (ulB / ulC) * ulC) +
                         ((ulA / ulC) * ulRemainB + (ulB / ulC) * ulRemainA);

        if(MULTIPLY_OVERFLOW_CHECK(ulRemainA, ulRemainB) == _TRUE)
        {
            return ulResult + (ulRemainA * ulRemainB / ulC);
        }
        else if(MULTIPLY_OVERFLOW_CHECK(ulRemainA, ulC - ulRemainB) == _TRUE)
        {
            return ulResult + ulRemainA - (ulRemainA * (ulC - ulRemainB) / ulC);
        }
        else if(MULTIPLY_OVERFLOW_CHECK(ulRemainB, ulC - ulRemainA) == _TRUE)
        {
            return ulResult + ulRemainB - (ulRemainB * (ulC - ulRemainA) / ulC);
        }
    }
    */
}

