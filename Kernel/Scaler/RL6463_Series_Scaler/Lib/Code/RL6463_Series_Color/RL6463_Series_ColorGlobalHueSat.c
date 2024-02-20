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
//-------------------------------------------------------------------------------------//
// ID Code      : RL6463_Series_ColorGlobalHueSat.c
// Update Note  :
//-------------------------------------------------------------------------------------//
#include "RL6463_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Table Length
//--------------------------------------------------
#define _SRGB_TABLE_SIZE                        24


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tCosCurveAngle[] = {0, 6, 12, 18, 24, 30, 37, 44, 52, 60, 68, 78, 90};
WORD code tCosCurveValue[] = {4096, 4074, 4006, 3896, 3742, 3547, 3271, 2946, 2522, 2048, 1534, 852, 0};

BYTE code tSinCurveAngle[] = {0, 6, 12, 18, 24, 30, 37, 44, 52, 60, 68, 78, 90};
WORD code tSinCurveValue[] = {0, 428, 852, 1266, 1666, 2048, 2465, 2845, 3228, 3547, 3798, 4006, 4096};

// 1->1024
SWORD code tYUV2RGB[][3] =
{
    { 4096,       0,    5744,  },
    { 4096,   -1408,   -2924,  },
    { 4096,    7260,       0,  }
};


// 1->1024
SWORD code tRGB2YUV[][3] =
{
    {  1224,    2405,    467,  },
    {  -691,   -1357,   2048,  },
    {  2048,   -1715,   -333,  }
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************

SWORD ScalerColorSRGBCosine(SWORD shDegree);
SWORD ScalerColorSRGBSine(SWORD shDegree);
void ScalerColorSRGBMatrixMultiply(SWORD (*ppshArrayA)[3], SWORD (*ppshArrayB)[3], SWORD (*ppshArrayC)[3]);
void ScalerColorSetSRGBGlobalHueSat(SWORD shDeltaHue, WORD usDeltaSat);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Enable/Disable SRGB function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------

//--------------------------------------------------
// Description  : Calculate Cos(x)
// Input Value  : shDegree x (in 360 unit)
// Output Value : SWORD Cos(x)
//--------------------------------------------------
SWORD ScalerColorSRGBCosine(SWORD shDegree)
{
    BYTE ucI = 0;
    BYTE ucQuadrant = 0;
    BYTE ucDegreeTemp = 0;
    BYTE ucDegreeSpan = 0;
    SWORD shCosValueSpan = 0;
    SWORD shCosValue = 0;

    if(shDegree < 0)
    {
        shDegree += 360;
    }

    shDegree = shDegree % 360;

    // Locate degree on which quadrant
    ucQuadrant = (BYTE)(shDegree / 90);
    ucQuadrant++;

    switch(ucQuadrant)
    {
        // First quadrant
        case 1:

            shDegree = shDegree;

            break;

        // Second quadrant
        case 2:

            shDegree = 180 - shDegree;

            break;

        // Third quadrant
        case 3:

            shDegree = shDegree - 180;

            break;

        // Forth quadrant
        case 4:

            shDegree = 360 - shDegree;

            break;

        default:

            break;
    }

    // Locate degree on which quadrant
    if(shDegree <= tCosCurveAngle[0])
    {
        shCosValue = tCosCurveValue[0];
    }
    else
    {
        for(ucI = 0; tCosCurveAngle[ucI] < shDegree; ucI++) {}

        ucI--;

        ucDegreeTemp = shDegree - tCosCurveAngle[ucI];
        ucDegreeSpan = tCosCurveAngle[ucI + 1] - tCosCurveAngle[ucI];
        shCosValueSpan = tCosCurveValue[ucI + 1] - tCosCurveValue[ucI];
        shCosValue = tCosCurveValue[ucI] + (SWORD)ucDegreeTemp * shCosValueSpan / ucDegreeSpan;
    }

    if((ucQuadrant == 2) || (ucQuadrant == 3))
    {
        shCosValue = shCosValue * (-1);
    }

    return shCosValue;
}

//--------------------------------------------------
// Description  : Calculate Sin(x)
// Input Value  : shDegree x (in 360 unit)
// Output Value : SWORD Sin(x)
//--------------------------------------------------
SWORD ScalerColorSRGBSine(SWORD shDegree)
{
    BYTE ucI = 0;
    BYTE ucQuadrant = 0;
    BYTE ucDegreeTemp = 0;
    BYTE ucDegreeSpan = 0;
    WORD usSinValueSpan = 0;
    SWORD shSinValue = 0;


    if(shDegree < 0)
    {
        shDegree += 360;
    }

    shDegree = shDegree % 360;

    // Locate degree on which quadrant
    ucQuadrant = (BYTE)(shDegree / 90);
    ucQuadrant++;

    switch(ucQuadrant)
    {
        // First quadrant
        case 1:

            shDegree = shDegree;

            break;

        // Second quadrant
        case 2:

            shDegree = 180 - shDegree;

            break;

        // Third quadrant
        case 3:

            shDegree = shDegree - 180;

            break;

        // Forth quadrant
        case 4:

            shDegree = 360 - shDegree;

            break;

        default:

            break;
    }

    // Locate degree on which quadrant
    if(shDegree <= tSinCurveAngle[0])
    {
        shSinValue = tSinCurveValue[0];
    }
    else
    {
        for(ucI = 0; tSinCurveAngle[ucI] < shDegree; ucI++) {}

        ucI--;

        ucDegreeTemp = shDegree - tSinCurveAngle[ucI];
        ucDegreeSpan = tSinCurveAngle[ucI + 1] - tSinCurveAngle[ucI];
        usSinValueSpan = tSinCurveValue[ucI + 1] - tSinCurveValue[ucI];
        shSinValue = tSinCurveValue[ucI] + (WORD)ucDegreeTemp * usSinValueSpan / ucDegreeSpan;
    }

    if((ucQuadrant == 3) || (ucQuadrant == 4))
    {
        shSinValue = shSinValue * (-1);
    }

    return shSinValue;
}

//--------------------------------------------------
// Description  : Do matrix multiply(3x3)  C = A*B
// Input Value  : shArrayA, shArrayB
// Output Value : shArrayC
//--------------------------------------------------
void ScalerColorSRGBMatrixMultiply(SWORD (*ppshArrayA)[3], SWORD (*ppshArrayB)[3], SWORD (*ppshArrayC)[3])
{
    BYTE ucI = 0;
    BYTE ucJ = 0;

    for(ucJ = 0; ucJ < 3; ucJ++)
    {
        for(ucI = 0; ucI < 3; ucI++)
        {
            PDATA_DWORD(ucI) = (((SDWORD)ppshArrayA[ucI][0] * ppshArrayB[0][ucJ] + 2) >> 4) +
                               (((SDWORD)ppshArrayA[ucI][1] * ppshArrayB[1][ucJ] + 2) >> 4) +
                               (((SDWORD)ppshArrayA[ucI][2] * ppshArrayB[2][ucJ] + 2) >> 4);
        }

        for(ucI = 0; ucI < 3; ucI++)
        {
            ppshArrayC[ucI][ucJ] = (SWORD)((PDATA_DWORD(ucI) + 128) >> 8);
        }
    }
}

//--------------------------------------------------
// Description  : Set global Hue&Sat
// Input Value  : DeltaHue(-180~180), DeltaSat(0-330)
// Default Value: Delta Hue = 0, Delta Sat = 100;
// Notice !! Rightnow the Hue/Sat value is saved to NVRAM as BYTE, if you
// want to expand the Range, please edit relative functions and parameters.
// Output Value : pColorMatrix(3x3, set to SRGB Matrix)
//--------------------------------------------------
void ScalerColorSetSRGBGlobalHueSat(SWORD shDeltaHue, WORD usDeltaSat)
{
    SWORD ppshTempBuff[3][3];
    memset(ppshTempBuff, 0, sizeof(ppshTempBuff));

    if(_TRUE)
    {
        SWORD ppshMATRIX[3][3];
        memset(ppshMATRIX, 0, sizeof(ppshMATRIX));

        // 1->1024
        ppshMATRIX[0][0] = 4096;
        ppshMATRIX[0][1] = 0;
        ppshMATRIX[0][2] = 0;
        ppshMATRIX[1][0] = 0;
        ppshMATRIX[1][1] = (DWORD)usDeltaSat * 4096 / 100;
        ppshMATRIX[1][2] = 0;
        ppshMATRIX[2][0] = 0;
        ppshMATRIX[2][1] = 0;
        ppshMATRIX[2][2] = ppshMATRIX[1][1];

        ScalerColorSRGBMatrixMultiply(ppshMATRIX, tRGB2YUV, ppshTempBuff);

        ppshMATRIX[0][0] = 4096;
        ppshMATRIX[0][1] = 0;
        ppshMATRIX[0][2] = 0;
        ppshMATRIX[1][0] = 0;
        ppshMATRIX[1][1] = ScalerColorSRGBCosine(shDeltaHue);
        ppshMATRIX[1][2] = (-1) * ScalerColorSRGBSine(shDeltaHue);
        ppshMATRIX[2][0] = 0;
        ppshMATRIX[2][1] = (-1) * ppshMATRIX[1][2];
        ppshMATRIX[2][2] = ppshMATRIX[1][1];

        ScalerColorSRGBMatrixMultiply(ppshMATRIX, ppshTempBuff, ppshTempBuff);
    }

    ScalerColorSRGBMatrixMultiply(tYUV2RGB, ppshTempBuff, ppshTempBuff);

    if(_TRUE)
    {
        BYTE pucColorMatrix[24];
        memset(pucColorMatrix, 0, sizeof(pucColorMatrix));

        // set 1+RR,  1+GG, 1+BB
        for(pData[0] = 0; pData[0] < 3; pData[0]++)
        {
            for(pData[1] = 0; pData[1] < 3; pData[1]++)
            {
                if(pData[0] == pData[1])
                {
                    ppshTempBuff[pData[0]][pData[1]] -= 4096; // 12bit data = 4096; 6369
                }

                if(ppshTempBuff[pData[0]][pData[1]] >= 0)
                {
                    ppshTempBuff[pData[0]][pData[1]] = ((ppshTempBuff[pData[0]][pData[1]] + 4) / 8);
                }
                else
                {
                    ppshTempBuff[pData[0]][pData[1]] = ((ppshTempBuff[pData[0]][pData[1]] - 4) / 8);
                }

                if(ppshTempBuff[pData[0]][pData[1]] > 2047)
                {
                    ppshTempBuff[pData[0]][pData[1]] = 2047;
                }
                else if(ppshTempBuff[pData[0]][pData[1]] < -2048)  // 2.9 = 2048
                {
                    ppshTempBuff[pData[0]][pData[1]] = -2048;
                }

                if((ppshTempBuff[pData[0]][pData[1]] & (1 << (2 - 1))) != 0)
                {
                    ppshTempBuff[pData[0]][pData[1]] = ppshTempBuff[pData[0]][pData[1]] + (1 << (2 - 1));
                }
                ppshTempBuff[pData[0]][pData[1]] = ppshTempBuff[pData[0]][pData[1]] >> 2;

                // Set sign byteXXH
                pucColorMatrix[2 * (3 * pData[0] + pData[1])] = (ppshTempBuff[pData[0]][pData[1]] < 0) ? 1 : 0;  // [0] sign
                pucColorMatrix[2 * (3 * pData[0] + pData[1])] += (((WORD)ppshTempBuff[pData[0]][pData[1]] & 0x01) << 7); // [7] bit0

                // Set data byte XXL
                pucColorMatrix[2 * (3 * pData[0] + pData[1]) + 1] = ((WORD)ppshTempBuff[pData[0]][pData[1]] >> 1) & 0xFF;// [7:0] bit8~1

            }
        }

        for(pData[0] = 18; pData[0] < 24; pData[0]++)
        {
            pucColorMatrix[pData[0]] = 0;
        }

        ScalerColorSRGBAdjust(pucColorMatrix, _SRGB_3_BIT_SHIFT_LEFT);
    }
}

