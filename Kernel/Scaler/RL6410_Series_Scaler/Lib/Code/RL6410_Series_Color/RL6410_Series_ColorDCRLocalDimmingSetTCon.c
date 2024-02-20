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
// ID Code      : RL6410_Series_ColorDCRLocalDimmingSetTCon.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _FUNC_DLY          113
#define _TCON_INTER_DLY    7


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
void ScalerColorDCRLocalDimmingFinetuneTConSetting(WORD *pusHStart, WORD *pusHEnd, WORD *pusVStart, WORD *pusVEnd, WORD usActiveHStart, WORD usActiveHEnd, WORD usActiveVStart, WORD usActiveVEnd);
void ScalerColorDCRLocalDimmingSetTCon(EnumLocalDimmingHDRMode enumLocalDimmingHDRMode);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Local Dimming Fine tune TCon Setting
// Input Value  : Pointor of Local Dimming Information Result
// Output Value : none
//--------------------------------------------------
void ScalerColorDCRLocalDimmingFinetuneTConSetting(WORD *pusHStart, WORD *pusHEnd, WORD *pusVStart, WORD *pusVEnd, WORD usActiveHStart, WORD usActiveHEnd, WORD usActiveVStart, WORD usActiveVEnd)
{
    if(*pusHStart < usActiveHStart)
    {
        *pusHStart = usActiveHStart;
    }

    if(*pusHEnd > usActiveHEnd)
    {
        *pusHEnd = usActiveHEnd;
    }

    if(*pusVStart < usActiveVStart)
    {
        *pusVStart = usActiveVStart;
    }

    if(*pusVEnd > usActiveVEnd)
    {
        *pusVEnd = usActiveVEnd;
    }

    if(*pusHStart > *pusHEnd)
    {
        *pusHEnd = *pusHStart;
    }

    if(*pusVStart > *pusVEnd)
    {
        *pusVEnd = *pusVStart;
    }
}

//--------------------------------------------------
// Description  : Read DCR Local Dimming Information Result
// Input Value  : Pointor of Local Dimming Information Result
// Output Value : none
//--------------------------------------------------
void ScalerColorDCRLocalDimmingSetTCon(EnumLocalDimmingHDRMode enumLocalDimmingHDRMode)
{
    WORD usHTotal = 0;
    WORD usHWidth = 0;
    WORD usHStart = 0;
    WORD usHStep = 0;
    WORD usHEnd = 0;
    WORD usVStart = 0;
    WORD usVStep = 0;
    WORD usVEnd = 0;
    WORD usActiveHWidth = 0;
    WORD usActiveHStart = 0;
    WORD usActiveHEnd = 0;
    WORD usActiveVStart = 0;
    WORD usActiveVStep = 0;
    WORD usActiveVEnd = 0;
    WORD usHStartTmp = 0;
    DWORD ulTemp = 0;

    usHTotal = g_stMDomainOutputData.usHTotal;
    usHStart = g_stMDomainOutputData.usHBackStart;
    usHWidth = g_stMDomainOutputData.usHBackWidth;
    usVStart = g_stMDomainOutputData.usVBackStart;
    usVStep = g_stMDomainOutputData.usVBackHeight;
    usActiveHStart = g_stMDomainOutputData.usHStart;
    usActiveHWidth = g_stMDomainOutputData.usHWidth;
    usActiveVStart = g_stMDomainOutputData.usVStart;
    usActiveVStep = g_stMDomainOutputData.usVHeight;

    if(ScalerFmtCnvGetHalfDataPathEvenOddModeStatus() == _FALSE) // Even Odd Mode
    {
        ulTemp = ((DWORD)usHTotal * usVStart / 2 + usHStart / 2) - (usHWidth + _FUNC_DLY);
        usVStart = (WORD)((ulTemp / usHTotal) * 2);
        usHStart = (WORD)(((ulTemp % usHTotal) - _TCON_INTER_DLY) * 2 - 1);
        usHStep = usHWidth / 4;
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_B8_TC10_CTRL, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_C8_TC11_CTRL, ~_BIT3, _BIT3);
    }
    else
    {
        ulTemp = ((DWORD)usHTotal * usVStart + usHStart) - (usHWidth + _FUNC_DLY);
        usVStart = (WORD)(ulTemp / usHTotal);
        usHStart = (WORD)((ulTemp % usHTotal) - _TCON_INTER_DLY - 1);
        usHStep = usHWidth / 8;
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_B8_TC10_CTRL, ~_BIT3, 0x00);
        ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_C8_TC11_CTRL, ~_BIT3, 0x00);
    }

    usHEnd = usHStart + usHStep;
    usVEnd = usVStart + usVStep;

    ScalerTcon10Adjust((usHStart % usHTotal), (usHStart + usHWidth) % usHTotal, usVStart + (usHStart / usHTotal), usVEnd + ((usHStart + 7 * usHStep) / usHTotal));
    ScalerTcon11Adjust((usHStart + usHWidth) % usHTotal, (usHStart + (usHWidth << 1)) % usHTotal, usVStart + (usHStart / usHTotal) + (((usHStart % usHTotal) + (usHStep << 2)) / usHTotal), usVEnd + ((usHStart + 7 * usHStep) / usHTotal));

    if(enumLocalDimmingHDRMode == _LOCAL_DIMMING_1X8_MODE)
    {
        ScalerTcon12Adjust(usHStart % usHTotal, (usHStart + usHWidth) % usHTotal, usVStart + (usHStart / usHTotal), usVEnd + ((usHStart + 7 * usHStep) / usHTotal));
        ScalerTcon13Adjust((usHStart + usHWidth) % usHTotal, (usHStart + (usHWidth << 1)) % usHTotal, usVStart + (usHStart / usHTotal), usVEnd + ((usHStart + 7 * usHStep) / usHTotal));
    }
    else
    {
        ScalerTcon12Adjust(usHStart % usHTotal, (usHStart + usHWidth) % usHTotal, usVStart + (usHStart / usHTotal), usVStart + (usVStep >> 1));
        ScalerTcon13Adjust((usHStart + usHWidth) % usHTotal, (usHStart + (usHWidth << 1)) % usHTotal, usVStart + (usHStart / usHTotal), usVStart + (usVStep >> 1));
    }

    if(ScalerFmtCnvGetHalfDataPathEvenOddModeStatus() == _FALSE) // Even Odd Mode
    {
        ulTemp = ((DWORD)usHTotal * usActiveVStart / 2) + (g_stMDomainOutputData.usHBackStart / 2) + (usActiveHStart - g_stMDomainOutputData.usHBackStart) - (usHWidth + _FUNC_DLY);
        usActiveVStart = (WORD)((ulTemp / usHTotal) * 2);
        usActiveHStart = (WORD)(((ulTemp % usHTotal) - _TCON_INTER_DLY) * 2 - 1);
        usActiveHEnd = usActiveHStart + g_stMDomainOutputData.usHWidth * 2;
        usActiveVEnd = usActiveVStart + g_stMDomainOutputData.usVHeight;
    }
    else
    {
        ulTemp = ((DWORD)usHTotal * usActiveVStart) + (g_stMDomainOutputData.usHBackStart) + (usActiveHStart - g_stMDomainOutputData.usHBackStart) - (usHWidth + _FUNC_DLY);
        usActiveVStart = (WORD)(ulTemp / usHTotal);
        usActiveHStart = (WORD)((ulTemp % usHTotal) - _TCON_INTER_DLY - 1);
        usActiveHEnd = usActiveHStart + g_stMDomainOutputData.usHWidth;
        usActiveVEnd = usActiveVStart + g_stMDomainOutputData.usVHeight;
    }

    usHStartTmp = usHStart;

    ScalerColorDCRLocalDimmingFinetuneTConSetting(&usHStart, &usHEnd, &usVStart, &usVEnd, usActiveHStart, usActiveHEnd, usActiveVStart, usActiveVEnd);
    ScalerTcon0Adjust(usHStart % usHTotal, usHEnd % usHTotal, usVStart + (usHStart / usHTotal), usVEnd + (usHStart / usHTotal));

    usHStart = usHStartTmp + usHStep;
    usHEnd = usHStart + usHStep;

    ScalerColorDCRLocalDimmingFinetuneTConSetting(&usHStart, &usHEnd, &usVStart, &usVEnd, usActiveHStart, usActiveHEnd, usActiveVStart, usActiveVEnd);
    ScalerTcon1Adjust(usHStart % usHTotal, usHEnd % usHTotal, usVStart + (usHStart / usHTotal), usVEnd + (usHStart / usHTotal));

    usHStart = usHStartTmp + 2 * usHStep;
    usHEnd = usHStart + usHStep;

    ScalerColorDCRLocalDimmingFinetuneTConSetting(&usHStart, &usHEnd, &usVStart, &usVEnd, usActiveHStart, usActiveHEnd, usActiveVStart, usActiveVEnd);
    ScalerTcon2Adjust(usHStart % usHTotal, usHEnd % usHTotal, usVStart + (usHStart / usHTotal), usVEnd + (usHStart / usHTotal));

    usHStart = usHStartTmp + 3 * usHStep;
    usHEnd = usHStart + usHStep;

    ScalerColorDCRLocalDimmingFinetuneTConSetting(&usHStart, &usHEnd, &usVStart, &usVEnd, usActiveHStart, usActiveHEnd, usActiveVStart, usActiveVEnd);
    ScalerTcon3Adjust(usHStart % usHTotal, usHEnd % usHTotal, usVStart + (usHStart / usHTotal), usVEnd + (usHStart / usHTotal));

    usHStart = usHStartTmp + 4 * usHStep;
    usHEnd = usHStart + usHStep;

    ScalerColorDCRLocalDimmingFinetuneTConSetting(&usHStart, &usHEnd, &usVStart, &usVEnd, usActiveHStart, usActiveHEnd, usActiveVStart, usActiveVEnd);
    ScalerTcon5Adjust(usHStart % usHTotal, usHEnd % usHTotal, usVStart + (usHStart / usHTotal), usVEnd + (usHStart / usHTotal));

    usHStart = usHStartTmp + 5 * usHStep;
    usHEnd = usHStart + usHStep;

    ScalerColorDCRLocalDimmingFinetuneTConSetting(&usHStart, &usHEnd, &usVStart, &usVEnd, usActiveHStart, usActiveHEnd, usActiveVStart, usActiveVEnd);
    ScalerTcon6Adjust(usHStart % usHTotal, usHEnd % usHTotal, usVStart + (usHStart / usHTotal), usVEnd + (usHStart / usHTotal));

    usHStart = usHStartTmp + 6 * usHStep;
    usHEnd = usHStart + usHStep;

    ScalerColorDCRLocalDimmingFinetuneTConSetting(&usHStart, &usHEnd, &usVStart, &usVEnd, usActiveHStart, usActiveHEnd, usActiveVStart, usActiveVEnd);
    ScalerTcon7Adjust(usHStart % usHTotal, usHEnd % usHTotal, usVStart + (usHStart / usHTotal), usVEnd + (usHStart / usHTotal));

    usHStart = usHStartTmp + 7 * usHStep;
    usHEnd = usHStart + usHStep;

    ScalerColorDCRLocalDimmingFinetuneTConSetting(&usHStart, &usHEnd, &usVStart, &usVEnd, usActiveHStart, usActiveHEnd, usActiveVStart, usActiveVEnd);
    ScalerTcon9Adjust(usHStart % usHTotal, usHEnd % usHTotal, usVStart + (usHStart / usHTotal), usVEnd + (usHStart / usHTotal));


    ScalerTcon0Enable(_ON);
    ScalerTcon1Enable(_ON);
    ScalerTcon2Enable(_ON);
    ScalerTcon3Enable(_ON);
    ScalerTcon5Enable(_ON);
    ScalerTcon6Enable(_ON);
    ScalerTcon7Enable(_ON);
    ScalerTcon9Enable(_ON);
    ScalerTcon10Enable(_ON);
    ScalerTcon11Enable(_ON);
    ScalerTcon12Enable(_ON);
    ScalerTcon13Enable(_ON);

    // global enable
    ScalerSetDataPortBit(P15_A3_TCON_ADDR, _P15_A4_PT_00_TC_CTRL0, ~_BIT6, _BIT6);
    ScalerTconGlobalEnable(_ON);
}
