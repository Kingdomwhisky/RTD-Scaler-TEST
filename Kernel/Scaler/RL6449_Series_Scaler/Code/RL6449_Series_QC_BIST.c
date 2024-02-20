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
// ID Code      : RL6449_Series_QC_BIST.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6449_SERIES_QC_BIST__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************

BYTE code tQCVBO[] =
{
//*************************************************************************
//  DPTX DPll Initial Setting
//*************************************************************************
4,	_AUTOINC,   0x9F,   0x38, // page 38 (eDP combo VbyOne)
4,	_AUTOINC,   0xA0,   0x80, // Enable Power of DPTX
4,	_AUTOINC,   0xD5,   0x00, // Disable SSC Function, Set Down SSC
4,	_AUTOINC,   0xD2,   0x00, // Divider for Postdivider of CMU and Pre-divder of CMU
4,	_AUTOINC,   0xD0,   0x73, // CCO mode, Use PI

//*************************************************************************
//  DPTX DPll Parameters Setting
//  Vref = Crystal = 14.318M
//  Target Clock = 375M for Vbo Lclk Freq
//*************************************************************************
4,	_AUTOINC,   0x9F,   0x38, // page 38 (eDP combo VbyOne)
4,	_AUTOINC,   0xC3,   0x00, // PHY = 3~6 GHz, spdsel = div1
4,	_AUTOINC,   0xD1,   0x7E, // Set CMU'S LPF Rs, CP Current

4,	_AUTOINC,   0xDD,   0xEF, // Set N.F PLL: N[3:0], F[11:8]
4,	_AUTOINC,   0xDE,   0x43, // Set N.F PLL: F[7:0]
4,	_AUTOINC,   0xDC,   0x87, // Set N.F PLL: N[7:4], Double Buffer

4,	_AUTOINC,   0xA0,   0x90, // Enable CMU power

4,  _AUTOINC,   0x09,   0x6A, // DPLL for Vby1 lclk is stable
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
bit ScalerQCBistTest(void);
bit ScalerQCADCNRBistTest(void);
bit ScalerQCFormatConvBistTest(void);
bit ScalerQCSDBistTest(void);
bit ScalerQCDTGBistTest(void);
bit ScalerQCSHPBistTest(void);
bit ScalerQCDCCBistTest(void);
bit ScalerQCRGBGammaBistTest(void);
bit ScalerQCGammaBistTest(void);
bit ScalerQC3DGammaBistTest(void);
bit ScalerQCPanelUniformityBistTest(void);
bit ScalerQCDisplayConversionBistTest(void);

#if(_QC_4P_MODE_ == _ON)
bit ScalerQC4PBistTest(void);
bit ScalerQC4PFormatConvBistTest(void);
bit ScalerQC4PSDBistTest(void);
#endif

#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
bit ScalerQC420D2BistTest(void);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
bit ScalerQC420D3BistTest(void);
#endif

bit ScalerQCTimerPollingPortFlagProc(WORD usTimeout, WORD usPortAddress, WORD usRegister, BYTE ucBit, bit bSuccess);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Test All Memory BIST
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
bit ScalerQCBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucBistResult2 = 0;

    DebugMessageQC("5. Bist Test Start", 0x00);

// ADCNR BIST
    ucBistResult = ucBistResult | (BYTE)ScalerQCADCNRBistTest();
// FormatConv
    ucBistResult = ucBistResult | ((BYTE)ScalerQCFormatConvBistTest() << 1);
// Scaling Down BIST
    ucBistResult = ucBistResult | ((BYTE)ScalerQCSDBistTest() << 2);
// DisplayTimingGen BIST
    ucBistResult = ucBistResult | ((BYTE)ScalerQCDTGBistTest() << 3);
// Sharpness BIST
    ucBistResult = ucBistResult | ((BYTE)ScalerQCSHPBistTest() << 4);
// DCC
    ucBistResult = ucBistResult | ((BYTE)ScalerQCDCCBistTest() << 5);
// RGB Gamma BIST
    ucBistResult = ucBistResult | ((BYTE)ScalerQCRGBGammaBistTest() << 6);
// Gamma BIST
    ucBistResult = ucBistResult | ((BYTE)ScalerQCGammaBistTest() << 7);
// 3D Gamma BIST
    ucBistResult = ucBistResult2 | (BYTE)ScalerQC3DGammaBistTest();
// Panel Uniformity
    ucBistResult = ucBistResult2 | ((BYTE)ScalerQCPanelUniformityBistTest() << 1);
// Display Conversion
    ucBistResult = ucBistResult2 | ((BYTE)ScalerQCDisplayConversionBistTest() << 2);



//------------LiveShow(OD) BIST---------------
/*
    DebugMessageQC("5. ====OD Bist Test Start", 0x00);

    // Test M1 OD Capture SRAM
    ScalerSetBit(P3_DE_CAP_BIST_CTRL, ~_BIT1, _BIT1);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P3_DE_CAP_BIST_CTRL, _BIT7, _TRUE) == _TRUE)
    {
        // M1 Cap BIST Fail
        if(ScalerGetBit(P3_DE_CAP_BIST_CTRL, _BIT5) != 0x00)
        {
            DebugMessageQC("5. OD M1 Cap Bist Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. OD M1 Cap Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P3_DE_CAP_BIST_CTRL, ~_BIT1, 0x00);

    // Test M1 OD Display SRAM
    ScalerSetBit(P3_DF_DIS_BIST_CTRL, ~_BIT1, _BIT1);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P3_DF_DIS_BIST_CTRL, _BIT7, _TRUE) == _TRUE)
    {
        // M1 Dis BIST Fail
        if(ScalerGetBit(P3_DF_DIS_BIST_CTRL, _BIT5) != 0x00)
        {
            DebugMessageQC("5. OD M1 Dis Bist Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }
    else
    {
        DebugMessageQC("5. OD M1 Dis Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT3;
    }
    ScalerSetBit(P3_DF_DIS_BIST_CTRL, ~_BIT1, 0x00);

    // Test M2 OD Capture SRAM
    ScalerSetBit(P43_DE_CAP_BIST_CTRL, ~_BIT1, _BIT1);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P43_DE_CAP_BIST_CTRL, _BIT7, _TRUE) == _TRUE)
    {
        // M2 Cap BIST Fail
        if(ScalerGetBit(P43_DE_CAP_BIST_CTRL, _BIT5) != 0x00)
        {
            DebugMessageQC("5. OD M2 Cap Bist Fail", 0x00);
            ucBistResult |= _BIT4;
        }
    }
    else
    {
        DebugMessageQC("5. OD M2 Cap Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT5;
    }
    ScalerSetBit(P43_DE_CAP_BIST_CTRL, ~_BIT1, 0x00);

    // Test M2 OD Display SRAM
    ScalerSetBit(P43_DF_DIS_BIST_CTRL, ~_BIT1, _BIT1);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P43_DF_DIS_BIST_CTRL, _BIT7, _TRUE) == _TRUE)
    {
        // M2 Dis BIST Fail
        if(ScalerGetBit(P43_DF_DIS_BIST_CTRL, _BIT5) != 0x00)
        {
            DebugMessageQC("5. OD M2 Dis Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }
    else
    {
        DebugMessageQC("5. OD M2 Dis Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT7;
    }
    ScalerSetBit(P43_DF_DIS_BIST_CTRL, ~_BIT1, 0x00);


    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. OD Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. OD Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. OD Bist FAIL", 0x00);
    }
    ucBistResult = 0x00;

//------------Display Conversion BIST---------------

    DebugMessageQC("5. ====Display Conversion Bist Test Start", 0x00);

    // Test LVDS Table SRAM
    DebugMessageQC("5. ====LVDS Bist Test", 0x00);

    ScalerSetBit(P39_21_LVDS_BIST_CTRL, ~_BIT7, _BIT7);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P39_21_LVDS_BIST_CTRL, _BIT6, _BIT6) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT5) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.5 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT4) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.4 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT3) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.3 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT2) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.2 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT1) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.1 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT0) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.0 Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. LVDS Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P39_21_LVDS_BIST_CTRL, ~_BIT7, 0x00);

    // Test Vbyone Table SRAM
    DebugMessageQC("5. ====VBO Bist Test", 0x00);

    ScalerBurstWrite(tQCVBO, sizeof(tQCVBO), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    ScalerTimerDelayXms(10);

    // Test Vbyone BIST0
    ScalerSetBit(P38_19_VBY1_BIST_CON_0, ~_BIT0, _BIT0);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P38_19_VBY1_BIST_CON_0, _BIT3, _BIT3) == _TRUE)
    {
        // BIST0 Fail
        if(ScalerGetBit(P38_1B_VBY1_BIST0, _BIT7) != 0x00)
        {
            DebugMessageQC("5. VBO Bist0 SRAM 7 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1B_VBY1_BIST0, _BIT6) != 0x00)
        {
            DebugMessageQC("5. VBO Bist0 SRAM 6 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1B_VBY1_BIST0, _BIT5) != 0x00)
        {
            DebugMessageQC("5. VBO Bist0 SRAM 5 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1B_VBY1_BIST0, _BIT4) != 0x00)
        {
            DebugMessageQC("5. VBO Bist0 SRAM 4 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1B_VBY1_BIST0, _BIT3) != 0x00)
        {
            DebugMessageQC("5. VBO Bist0 SRAM 3 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1B_VBY1_BIST0, _BIT2) != 0x00)
        {
            DebugMessageQC("5. VBO Bist0 SRAM 2 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1B_VBY1_BIST0, _BIT1) != 0x00)
        {
            DebugMessageQC("5. VBO Bist0 SRAM 1 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1B_VBY1_BIST0, _BIT0) != 0x00)
        {
            DebugMessageQC("5. VBO Bist0 SRAM 0 Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. VBO Bist0 Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P38_19_VBY1_BIST_CON_0, ~_BIT0, 0x00);

    // Test Vbyone BIST1
    ScalerSetBit(P38_1A_VBY1_BIST_CON_1, ~_BIT0, _BIT0);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P38_1A_VBY1_BIST_CON_1, _BIT3, _BIT3) == _TRUE)
    {
        // BIST1 Fail
        if(ScalerGetBit(P38_1C_VBY1_BIST1, _BIT7) != 0x00)
        {
            DebugMessageQC("5. VBO Bist1 SRAM 7 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1C_VBY1_BIST1, _BIT6) != 0x00)
        {
            DebugMessageQC("5. VBO Bist1 SRAM 6 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1C_VBY1_BIST1, _BIT5) != 0x00)
        {
            DebugMessageQC("5. VBO Bist1 SRAM 5 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1C_VBY1_BIST1, _BIT4) != 0x00)
        {
            DebugMessageQC("5. VBO Bist1 SRAM 4 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1C_VBY1_BIST1, _BIT3) != 0x00)
        {
            DebugMessageQC("5. VBO Bist1 SRAM 3 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1C_VBY1_BIST1, _BIT2) != 0x00)
        {
            DebugMessageQC("5. VBO Bist1 SRAM 2 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1C_VBY1_BIST1, _BIT1) != 0x00)
        {
            DebugMessageQC("5. VBO Bist1 SRAM 1 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P38_1C_VBY1_BIST1, _BIT0) != 0x00)
        {
            DebugMessageQC("5. VBO Bist1 SRAM 0 Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. VBO Bist1 Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P38_1A_VBY1_BIST_CON_1, ~_BIT0, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. Display Conversion Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. Display Conversion Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. Display Conversion Bist FAIL", 0x00);
    }
    ucBistResult = 0x00;
*/

    if(ucBistResult == 0)
    {
        DebugMessageQC("6. Bist Test PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Bist Test FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : ADCNR BIST Test
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCADCNRBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    DebugMessageQC("5. ====ADCNR Bist Test Start", 0x00);
    ScalerSetBit(P33_2A_BIST_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P33_2A_BIST_CTRL, _BIT2, _TRUE) == _TRUE)
    {
        if(ScalerGetBit(P33_2B_BIST_RESULT, _BIT7) != 0x00)
        {
            DebugMessageQC("5. ADCNR bist_result_3 Fail", 0x00);
            ucBistResult |= _BIT7;
        }

        if(ScalerGetBit(P33_2B_BIST_RESULT, _BIT6) != 0x00)
        {
            DebugMessageQC("5. ADCNR bist_result_2 Fail", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetBit(P33_2B_BIST_RESULT, _BIT5) != 0x00)
        {
            DebugMessageQC("5. ADCNR bist_result_1 Fail", 0x00);
            ucBistResult |= _BIT5;
        }

        if(ScalerGetBit(P33_2B_BIST_RESULT, _BIT4) != 0x00)
        {
            DebugMessageQC("5. ADCNR bist_result_0 Fail", 0x00);
            ucBistResult |= _BIT4;
        }

    }
    else
    {
        DebugMessageQC("5. ADCNR Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT0;
    }
    // Disable ADCNR bist test
    ScalerSetBit(P33_2A_BIST_CTRL, ~(_BIT6 | _BIT3), _BIT3);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ADCNR Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ADCNR Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

//------------ADCNR DRF BIST---------------//

    DebugMessageQC("5. ====ADCNR DRF Bist Test Start", 0x00);

    //1.Start DRF BIST mode
    ScalerSetBit(P33_2A_BIST_CTRL, ~(_BIT5 | _BIT3), _BIT5);

    //2.Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P33_2A_BIST_CTRL, _BIT0, _TRUE) == _TRUE)
        {
            //3.Wait 1ms
            //ScalerTimerDelayXms(2);
            ScalerSetBit(P33_2A_BIST_CTRL, ~_BIT4, _BIT4);
            ScalerSetBit(P33_2A_BIST_CTRL, ~_BIT4, 0x00);
        }
        else
        {
            DebugMessageQC("5. ADCNR DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    //8.Wait DRF Bist Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P33_2A_BIST_CTRL, _BIT1, _TRUE) == _TRUE)
    {
        if(ScalerGetBit(P33_2B_BIST_RESULT, _BIT3) != 0x00)
        {
            DebugMessageQC("5. ADCNR DRF bist_result_3 Fail", 0x00);
            ucBistResult |= (_BIT7 | _BIT1);
        }

        if(ScalerGetBit(P33_2B_BIST_RESULT, _BIT2) != 0x00)
        {
            DebugMessageQC("5. ADCNR DRF bist_result_2 Fail", 0x00);
            ucBistResult |= (_BIT6 | _BIT1);
        }

        if(ScalerGetBit(P33_2B_BIST_RESULT, _BIT1) != 0x00)
        {
            DebugMessageQC("5. ADCNR DRF bist_result_1 Fail", 0x00);
            ucBistResult |= (_BIT5 | _BIT1);
        }

        if(ScalerGetBit(P33_2B_BIST_RESULT, _BIT0) != 0x00)
        {
            DebugMessageQC("5. ADCNR DRF bist_result_0 Fail", 0x00);
            ucBistResult |= (_BIT4 | _BIT1);
        }
    }
    else
    {
        DebugMessageQC("5. ADCNR DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }

    // Disable ADCNR bist test
    ScalerSetBit(P33_2A_BIST_CTRL, ~(_BIT7 | _BIT5), 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ADCNR DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ADCNR DRF Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : Format Conversion BIST Test
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCFormatConvBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    DebugMessageQC("5. ====FormatConv Bist Test Start", 0x00);
    ScalerSetBit(P31_2D_EVEN_ODD_BIST_CTRL_MAIN, ~(_BIT7 | _BIT1), _BIT7 | _BIT1);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_2D_EVEN_ODD_BIST_CTRL_MAIN, _BIT6, _TRUE) == _TRUE)
    {
        if(ScalerGetBit(P31_2D_EVEN_ODD_BIST_CTRL_MAIN, _BIT5) != 0x00)
        {
            DebugMessageQC("5. FormatConv bist_result_3 Fail", 0x00);
            ucBistResult |= _BIT7;
        }

        if(ScalerGetBit(P31_2D_EVEN_ODD_BIST_CTRL_MAIN, _BIT4) != 0x00)
        {
            DebugMessageQC("5. FormatConv bist_result_2 Fail", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetBit(P31_2D_EVEN_ODD_BIST_CTRL_MAIN, _BIT3) != 0x00)
        {
            DebugMessageQC("5. FormatConv bist_result_1 Fail", 0x00);
            ucBistResult |= _BIT5;
        }

        if(ScalerGetBit(P31_2D_EVEN_ODD_BIST_CTRL_MAIN, _BIT2) != 0x00)
        {
            DebugMessageQC("5. FormatConv bist_result_0 Fail", 0x00);
            ucBistResult |= _BIT4;
        }

    }
    else
    {
        DebugMessageQC("5. FormatConv Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT0;
    }

    ScalerSetBit(P31_2D_EVEN_ODD_BIST_CTRL_MAIN, ~_BIT7, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. FormatConv Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. FormatConv Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

//-----------FormatConv DRF BIST---------------//

    DebugMessageQC("5. ====FormatConv DRF Bist Test Start", 0x00);
    ScalerSetBit(P31_2D_EVEN_ODD_BIST_CTRL_MAIN, ~_BIT0, _BIT0);
    ScalerSetBit(P31_2D_EVEN_ODD_BIST_CTRL_MAIN, ~_BIT0, 0x00);
    //1.Start DRF BIST mode
    ScalerSetBit(P31_2E_EVEN_ODD_DRF_BIST_CTRL_MAIN, ~(_BIT7 | _BIT6), _BIT7);

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_2E_EVEN_ODD_DRF_BIST_CTRL_MAIN, _BIT5, _TRUE) == _TRUE)
        {
             //3.Wait 1ms
            ScalerTimerDelayXms(2);
            ScalerSetBit(P31_2E_EVEN_ODD_DRF_BIST_CTRL_MAIN, ~_BIT6, _BIT6);
            ScalerSetBit(P31_2E_EVEN_ODD_DRF_BIST_CTRL_MAIN, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. FormatConv DRF Bist Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_2E_EVEN_ODD_DRF_BIST_CTRL_MAIN, _BIT4, _TRUE) == _TRUE)
    {
        if(ScalerGetBit(P31_2E_EVEN_ODD_DRF_BIST_CTRL_MAIN, _BIT3) != 0x00)
        {
            DebugMessageQC("5. FormatConv DRF bist_result_3 Fail", 0x00);
            ucBistResult |= (_BIT7 | _BIT1);
        }

        if(ScalerGetBit(P31_2E_EVEN_ODD_DRF_BIST_CTRL_MAIN, _BIT2) != 0x00)
        {
            DebugMessageQC("5. FormatConv DRF bist_result_2 Fail", 0x00);
            ucBistResult |= (_BIT6 | _BIT1);
        }

        if(ScalerGetBit(P31_2E_EVEN_ODD_DRF_BIST_CTRL_MAIN, _BIT1) != 0x00)
        {
            DebugMessageQC("5. FormatConv DRF bist_result_1 Fail", 0x00);
            ucBistResult |= (_BIT5 | _BIT1);
        }

        if(ScalerGetBit(P31_2E_EVEN_ODD_DRF_BIST_CTRL_MAIN, _BIT0) != 0x00)
        {
            DebugMessageQC("5. FormatConv DRF bist_result_0 Fail", 0x00);
            ucBistResult |= (_BIT4 | _BIT1);
        }
    }
    else
    {
        DebugMessageQC("5. FormatConv DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }

    // Disable  bist test
    ScalerSetBit(P31_2E_EVEN_ODD_DRF_BIST_CTRL_MAIN, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P31_2D_EVEN_ODD_BIST_CTRL_MAIN, ~_BIT1, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. FormatConv DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. FormatConv DRF Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : Scaling Down BIST Test
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCSDBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    //Test ScaleDown M1 Bist Mode
    DebugMessageQC("5. ====ScaleDown M1 Bist Test Start", 0x00);
    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_51_SD_BIST_CTRL1_M1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_50_SD_BIST_CTRL0_M1, ~_BIT5, _BIT5);
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_50_SD_BIST_CTRL0_M1, _BIT7, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_50_SD_BIST_CTRL0_M1, _BIT6) != 0x00)
        {
            DebugMessageQC("5. ScaleDown M1 Linebuffer0 Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        };

        if(ScalerGetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_51_SD_BIST_CTRL1_M1, _BIT7) != 0x00)
        {
            DebugMessageQC("5. ScaleDown M1 Linebuffer1 Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }
    else
    {
        DebugMessageQC("5. ScaleDown M1 Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT5;
    }
    //disable ScaleDown M1 bist test
    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_50_SD_BIST_CTRL0_M1, ~_BIT5, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ScaleDown M1 Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ScaleDown M1 Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. ScaleDown M1 Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_51_SD_BIST_CTRL1_M1, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_51_SD_BIST_CTRL1_M1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    DebugMessageQC("5. ====ScaleDown M1 DRF Bist Test Start", 0x00);
    //1.Start DRF BIST mode
    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_50_SD_BIST_CTRL0_M1, ~_BIT2, _BIT2);

    //2.Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_50_SD_BIST_CTRL0_M1, _BIT1, _TRUE) == _TRUE)
        {
            //3.Wait 1ms
            ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_50_SD_BIST_CTRL0_M1, ~_BIT0, _BIT0);
            ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_50_SD_BIST_CTRL0_M1, ~_BIT0, 0x00);
        }
        else
        {
            DebugMessageQC("5. ScaleDown M1 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    //8.Wait DRF Bist Done
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_50_SD_BIST_CTRL0_M1, _BIT4, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_50_SD_BIST_CTRL0_M1, _BIT3) != 0x00)
        {
            DebugMessageQC("5. ScaleDown M1 Linebuffer0 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_51_SD_BIST_CTRL1_M1, _BIT6) != 0x00)
        {
            DebugMessageQC("5. ScaleDown M1 Linebuffer1 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT5;
        }
    }
    else
    {
        DebugMessageQC("5. ScaleDown M1 Linebuffer1 DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT4;
    }

    // Disable ScaleDown M1 DRF bist test
    ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_50_SD_BIST_CTRL0_M1, ~(_BIT2 | _BIT0), 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ScaleDown M1 DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ScaleDown M1 DRF Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. ScaleDown M1 DRF Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    // Test ScaleDown M2 Bist Mode
    DebugMessageQC("5. ====ScaleDown M2 Bist Test Start", 0x00);
    ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_51_SD_BIST_CTRL1_M2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_50_SD_BIST_CTRL0_M2, ~_BIT5, _BIT5);
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_50_SD_BIST_CTRL0_M2, _BIT7, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_50_SD_BIST_CTRL0_M2, _BIT6) != 0x00)
        {
            DebugMessageQC("5. ScaleDown M2 Linebuffer0 Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        };

        if(ScalerGetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_51_SD_BIST_CTRL1_M2, _BIT7) != 0x00)
        {
            DebugMessageQC("5. ScaleDown M2 Linebuffer1 Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }
    else
    {
        DebugMessageQC("5. ScaleDown M2 Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT5;
    }
    //disable ScaleDown M2 bist test
    ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_50_SD_BIST_CTRL0_M2, ~_BIT5, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ScaleDown M2 Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ScaleDown M2 Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. ScaleDown M2 Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_51_SD_BIST_CTRL1_M2, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_51_SD_BIST_CTRL1_M2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    DebugMessageQC("5. ====ScaleDown M2 DRF Bist Test Start", 0x00);
    //1.Start DRF BIST mode
    ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_50_SD_BIST_CTRL0_M2, ~_BIT2, _BIT2);

    //2.Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_50_SD_BIST_CTRL0_M2, _BIT1, _TRUE) == _TRUE)
        {
            //3.Wait 1ms
            ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_50_SD_BIST_CTRL0_M2, ~_BIT0, _BIT0);
            ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_50_SD_BIST_CTRL0_M2, ~_BIT0, 0x00);
        }
        else
        {
            DebugMessageQC("5. ScaleDown M2 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    //8.Wait DRF Bist Done
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_50_SD_BIST_CTRL0_M2, _BIT4, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_50_SD_BIST_CTRL0_M2, _BIT3) != 0x00)
        {
            DebugMessageQC("5. ScaleDown M2 Linebuffer0 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_51_SD_BIST_CTRL1_M2, _BIT6) != 0x00)
        {
            DebugMessageQC("5. ScaleDown M2 Linebuffer1 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT5;
        }
    }
    else
    {
        DebugMessageQC("5. ScaleDown M2 Linebuffer1 DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT4;
    }

    // Disable ScaleDown M2 DRF bist test
    ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_50_SD_BIST_CTRL0_M2, ~(_BIT2 | _BIT0), 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ScaleDown M2 DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ScaleDown M2 DRF Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. ScaleDown M2 DRF Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : DisplayTimingGen BIST Test
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCDTGBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    // Test DisplayTimingGen Even Bist Mode
    DebugMessageQC("5. ====DisplayTimingGen Even Bist Test Start", 0x00);
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_BIST_CLK_RST_EN, ~(_BIT7 | _BIT3), _BIT7);

    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, ~_BIT6, _BIT6);
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, _BIT2, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT7) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even BIST Fail for SRAM No.3", 0x00);
            ucBistResult |= _BIT7;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT6) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even BIST Fail for SRAM No.2", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT5) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even BIST Fail for SRAM No.1", 0x00);
            ucBistResult |= _BIT5;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT4) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even BIST Fail for SRAM No.0", 0x00);
            ucBistResult |= _BIT4;
        }
    }
    else
    {
        DebugMessageQC("5. DisplayTimingGen Even Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT3;
    }
    //disable DisplayTimingGen Even bist test
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, ~_BIT6, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. DisplayTimingGen Even Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. DisplayTimingGen Even Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. DisplayTimingGen Even Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_BIST_CLK_RST_EN, ~(_BIT7 | _BIT3), _BIT7 | _BIT3);
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_BIST_CLK_RST_EN, ~(_BIT7 | _BIT3), _BIT7);

    DebugMessageQC("5. ====DisplayTimingGen Even DRF Bist Test Start", 0x00);
    //1.Start DRF BIST mode
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, ~_BIT5, _BIT5);

    //2.Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, _BIT0, _TRUE) == _TRUE)
        {
            //3.Wait 1ms
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, ~_BIT4, _BIT4);
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, ~_BIT4, 0x00);
        }
        else
        {
            DebugMessageQC("5. DisplayTimingGen Even DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    //8.Wait DRF Bist Done
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, _BIT1, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT3) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even DRF BIST Fail for SRAM No.3", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT2) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even DRF BIST Fail for SRAM No.2", 0x00);
            ucBistResult |= _BIT5;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT1) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even DRF BIST Fail for SRAM No.1", 0x00);
            ucBistResult |= _BIT4;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT0) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even DRF BIST Fail for SRAM No.0", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    else
    {
        DebugMessageQC("5. DisplayTimingGen Even DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }

    // Disable DisplayTimingGen Even DRF bist test
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, ~(_BIT5 | _BIT4), 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. DisplayTimingGen Even DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. DisplayTimingGen Even DRF Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. DisplayTimingGen Even DRF Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    //Test DisplayTimingGen Odd Bist Mode
    DebugMessageQC("5. ====DisplayTimingGen Odd Bist Test Start", 0x00);
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_BIST_CLK_RST_EN, ~(_BIT6 | _BIT2), _BIT6);

    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_42_ODD_BIST_CTRL, ~_BIT6, _BIT6);
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_42_ODD_BIST_CTRL, _BIT2, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_43_ODD_BIST_RESULT, _BIT7) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Odd BIST Fail for SRAM No.3", 0x00);
            ucBistResult |= _BIT7;
        };

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_43_ODD_BIST_RESULT, _BIT6) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Odd BIST Fail for SRAM No.2", 0x00);
            ucBistResult |= _BIT6;
        };

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_43_ODD_BIST_RESULT, _BIT5) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Odd BIST Fail for SRAM No.1", 0x00);
            ucBistResult |= _BIT5;
        };

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_43_ODD_BIST_RESULT, _BIT4) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Odd BIST Fail for SRAM No.0", 0x00);
            ucBistResult |= _BIT4;
        };
    }
    else
    {
        DebugMessageQC("5. DisplayTimingGen Odd Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT3;
    }
    //disable DisplayTimingGen Odd bist test
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_42_ODD_BIST_CTRL, ~_BIT6, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. DisplayTimingGen Odd Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. DisplayTimingGen Odd Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. DisplayTimingGen Odd Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_BIST_CLK_RST_EN, ~(_BIT6 | _BIT2), _BIT6 | _BIT2);
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4B_BIST_CLK_RST_EN, ~(_BIT6 | _BIT2), _BIT6);

    DebugMessageQC("5. ====DisplayTimingGen Odd DRF Bist Test Start", 0x00);
    //1.Start DRF BIST mode
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_42_ODD_BIST_CTRL, ~_BIT5, _BIT5);

    //2.Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_42_ODD_BIST_CTRL, _BIT0, _TRUE) == _TRUE)
        {
            //3.Wait 1ms
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_42_ODD_BIST_CTRL, ~_BIT4, _BIT4);
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_42_ODD_BIST_CTRL, ~_BIT4, 0x00);
        }
        else
        {
            DebugMessageQC("5. DisplayTimingGen Odd DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    //8.Wait DRF Bist Done
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_42_ODD_BIST_CTRL, _BIT1, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_43_ODD_BIST_RESULT, _BIT3) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Odd DRF BIST Fail for SRAM No.3", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_43_ODD_BIST_RESULT, _BIT2) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Odd DRF BIST Fail for SRAM No.2", 0x00);
            ucBistResult |= _BIT5;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_43_ODD_BIST_RESULT, _BIT1) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Odd DRF BIST Fail for SRAM No.1", 0x00);
            ucBistResult |= _BIT4;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_43_ODD_BIST_RESULT, _BIT0) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Odd DRF BIST Fail for SRAM No.0", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    else
    {
        DebugMessageQC("5. DisplayTimingGen Odd DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }

    // Disable DisplayTimingGen Odd DRF bist test
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_42_ODD_BIST_CTRL, ~(_BIT5 | _BIT4), 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. DisplayTimingGen Odd DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. DisplayTimingGen Odd DRF Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. DisplayTimingGen Odd DRF Bist FAIL", 0x00);
        return _TEST_FAIL;
    }    


    //Test DisplayTimingGen Fifo Bist Mode
    DebugMessageQC("5. ====DisplayTimingGen FIFO Bist Test Start", 0x00);
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4C_BIST_CLK_RST1_EN, ~(_BIT4 | _BIT0), _BIT4);

    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_46_FIFO_BIST_CTRL, ~_BIT6, _BIT6);
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_46_FIFO_BIST_CTRL, _BIT2, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_47_FIFO_BIST_RESULT, _BIT5) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen FIFO BIST Fail for SRAM No.1", 0x00);
            ucBistResult |= _BIT7;
        };

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_47_FIFO_BIST_RESULT, _BIT4) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen FIFO BIST Fail for SRAM No.0", 0x00);
            ucBistResult |= _BIT6;
        };
    }
    else
    {
        DebugMessageQC("5. DisplayTimingGen FIFO Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT5;
    }
    //disable DisplayTimingGen Fifo bist test
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_46_FIFO_BIST_CTRL, ~_BIT6, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. DisplayTimingGen FIFO Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. DisplayTimingGen FIFO Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. DisplayTimingGen FIFO Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4C_BIST_CLK_RST1_EN, ~(_BIT4 | _BIT0), _BIT4 | _BIT0);
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_4C_BIST_CLK_RST1_EN, ~(_BIT4 | _BIT0), _BIT4);

    DebugMessageQC("5. ====DisplayTimingGen FIFO DRF Bist Test Start", 0x00);
    //1.Start DRF BIST mode
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_46_FIFO_BIST_CTRL, ~_BIT5, _BIT5);

    //2.Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_46_FIFO_BIST_CTRL, _BIT0, _TRUE) == _TRUE)
        {
            //3.Wait 1ms
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_46_FIFO_BIST_CTRL, ~_BIT4, _BIT4);
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_46_FIFO_BIST_CTRL, ~_BIT4, 0x00);
        }
        else
        {
            DebugMessageQC("5. DisplayTimingGen FIFO DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    //8.Wait DRF Bist Done
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_46_FIFO_BIST_CTRL, _BIT1, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_47_FIFO_BIST_RESULT, _BIT3) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen FIFO DRF BIST Fail for SRAM No.3", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_47_FIFO_BIST_RESULT, _BIT2) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen FIFO DRF BIST Fail for SRAM No.2", 0x00);
            ucBistResult |= _BIT5;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_47_FIFO_BIST_RESULT, _BIT1) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen FIFO DRF BIST Fail for SRAM No.1", 0x00);
            ucBistResult |= _BIT4;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_47_FIFO_BIST_RESULT, _BIT0) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen FIFO DRF BIST Fail for SRAM No.0", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    else
    {
        DebugMessageQC("5. DisplayTimingGen FIFO DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : Sharpness BIST
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCSHPBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    // Test SHP M1/M2 Bist Mode
    DebugMessageQC("5. ====SHP M1/M2 Bist Test Start", 0x00);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P12_A2_SR_SHP_BIST_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(P12_A2_SR_SHP_BIST_CTRL_0, ~(_BIT7 | _BIT6 | _BIT3), (_BIT7 | _BIT6 | _BIT3));

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P12_A2_SR_SHP_BIST_CTRL_0, _BIT2, _BIT2) == _TRUE)
    {
        if(ScalerGetBit(P12_A2_SR_SHP_BIST_CTRL_0, _BIT1) != 0x00)
        {
            DebugMessageQC("5. SHP M1 Bist Even Fail", 0x00);
            ucBistResult |= _BIT7;
        }

        if(ScalerGetBit(P12_A2_SR_SHP_BIST_CTRL_0, _BIT0) != 0x00)
        {
            DebugMessageQC("5. SHP M1 Bist Odd Fail", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetBit(P12_A2_SR_SHP_BIST_CTRL_0, _BIT5) != 0x00)
        {
            DebugMessageQC("5. SHP M2 Bist Even Fail", 0x00);
            ucBistResult |= _BIT5;
        }

        if(ScalerGetBit(P12_A2_SR_SHP_BIST_CTRL_0, _BIT4) != 0x00)
        {
            DebugMessageQC("5. SHP M2 Bist Odd Fail", 0x00);
            ucBistResult |= _BIT4;
        }
    }
    else
    {
        DebugMessageQC("5. SHP M1/M2 Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT0;
    }

    // Test Sharpness S1/S2 Bist Mode
    DebugMessageQC("5. ====SHP S1/S2 Bist Test Start", 0x00);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P92_A2_SR_SHP_BIST_CTRL_0_S1, ~_BIT7, 0x00);
    ScalerSetBit(P92_A2_SR_SHP_BIST_CTRL_0_S1, ~(_BIT7 | _BIT6 | _BIT3), (_BIT7 | _BIT6 | _BIT3));

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P92_A2_SR_SHP_BIST_CTRL_0_S1, _BIT2, _BIT2) == _TRUE)
    {
        if(ScalerGetBit(P92_A2_SR_SHP_BIST_CTRL_0_S1, _BIT1) != 0x00)
        {
            DebugMessageQC("5. SHP S1 Bist Even Fail", 0x00);
            ucBistResult |= _BIT7;
        }

        if(ScalerGetBit(P92_A2_SR_SHP_BIST_CTRL_0_S1, _BIT0) != 0x00)
        {
            DebugMessageQC("5. SHP S1 Bist Odd Fail", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetBit(P92_A2_SR_SHP_BIST_CTRL_0_S1, _BIT5) != 0x00)
        {
            DebugMessageQC("5. SHP S2 Bist Even Fail", 0x00);
            ucBistResult |= _BIT5;
        }

        if(ScalerGetBit(P92_A2_SR_SHP_BIST_CTRL_0_S1, _BIT4) != 0x00)
        {
            DebugMessageQC("5. SHP S2 Bist Odd Fail", 0x00);
            ucBistResult |= _BIT4;
        }
    }
    else
    {
        DebugMessageQC("5. SHP S1/S2 Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT0;
    }

    // Disable BIST Clock and Disable BIST Mode
    ScalerSetBit(P12_A2_SR_SHP_BIST_CTRL_0, ~(_BIT6 | _BIT3), 0x00);
    ScalerSetBit(P92_A2_SR_SHP_BIST_CTRL_0_S1, ~(_BIT6 | _BIT3), 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. SHP Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. SHP Bist FAIL", ucBistResult);
        DebugMessageQC("6. SHP Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    //---------------SHP DRF BIST---------------//

    // Test SHP M1/M2 DRF Bist Mode
    DebugMessageQC("5. ====SHP M1/M2 DRF Bist Test Start", 0x00);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P12_A2_SR_SHP_BIST_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(P12_A2_SR_SHP_BIST_CTRL_0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Enable DRF BIST Mode
    ScalerSetBit(P12_E7_SR_SHP_BIST_CTRL_1, ~_BIT3, _BIT3);

    // Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P12_E7_SR_SHP_BIST_CTRL_1, _BIT6, _BIT6) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P12_E7_SR_SHP_BIST_CTRL_1, ~_BIT7, 0x00);
            ScalerSetBit(P12_E7_SR_SHP_BIST_CTRL_1, ~_BIT7, _BIT7);
            ScalerSetBit(P12_E7_SR_SHP_BIST_CTRL_1, ~_BIT7, 0x00);
        }
        else
        {
            DebugMessageQC("5. SHP M1/M2 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P12_E7_SR_SHP_BIST_CTRL_1, _BIT2, _BIT2) == _TRUE)
    {
        if(ScalerGetBit(P12_E7_SR_SHP_BIST_CTRL_1, _BIT1) != 0x00)
        {
            DebugMessageQC("5. SHP M1 DRF Bist Even Fail", 0x00);
            ucBistResult |= (_BIT7 | _BIT2);
        }

        if(ScalerGetBit(P12_E7_SR_SHP_BIST_CTRL_1, _BIT0) != 0x00)
        {
            DebugMessageQC("5. SHP M1 DRF Bist Odd Fail", 0x00);
            ucBistResult |= (_BIT6 | _BIT2);
        }

        if(ScalerGetBit(P12_E7_SR_SHP_BIST_CTRL_1, _BIT5) != 0x00)
        {
            DebugMessageQC("5. SHP M2 DRF Bist Even Fail", 0x00);
            ucBistResult |= (_BIT5 | _BIT2);
        }

        if(ScalerGetBit(P12_E7_SR_SHP_BIST_CTRL_1, _BIT4) != 0x00)
        {
            DebugMessageQC("5. SHP M2 DRF Bist Even Fail", 0x00);
            ucBistResult |= (_BIT4 | _BIT2);
        }
    }
    else
    {
        DebugMessageQC("5. SHP M1/M2 DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }

    // Test SHP S1/S2 DRF Bist Mode
    DebugMessageQC("5. ====SHP S1/S2 DRF Bist Test Start", 0x00);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P92_A2_SR_SHP_BIST_CTRL_0_S1, ~_BIT7, 0x00);
    ScalerSetBit(P92_A2_SR_SHP_BIST_CTRL_0_S1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Enable DRF BIST Mode
    ScalerSetBit(P92_E7_SR_SHP_BIST_CTRL_1_S1, ~_BIT3, _BIT3);

    // Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P92_E7_SR_SHP_BIST_CTRL_1_S1, _BIT6, _BIT6) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P92_E7_SR_SHP_BIST_CTRL_1_S1, ~_BIT7, 0x00);
            ScalerSetBit(P92_E7_SR_SHP_BIST_CTRL_1_S1, ~_BIT7, _BIT7);
            ScalerSetBit(P92_E7_SR_SHP_BIST_CTRL_1_S1, ~_BIT7, 0x00);
        }
        else
        {
            DebugMessageQC("5. SHP S1/S2 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P92_E7_SR_SHP_BIST_CTRL_1_S1, _BIT2, _BIT2) == _TRUE)
    {
        if(ScalerGetBit(P92_E7_SR_SHP_BIST_CTRL_1_S1, _BIT1) != 0x00)
        {
            DebugMessageQC("5. SHP S1 DRF Bist Even Fail", 0x00);
            ucBistResult |= (_BIT7 | _BIT2);
        }

        if(ScalerGetBit(P92_E7_SR_SHP_BIST_CTRL_1_S1, _BIT0) != 0x00)
        {
            DebugMessageQC("5. SHP S1 DRF Bist Odd Fail", 0x00);
            ucBistResult |= (_BIT6 | _BIT2);
        }

        if(ScalerGetBit(P92_E7_SR_SHP_BIST_CTRL_1_S1, _BIT5) != 0x00)
        {
            DebugMessageQC("5. SHP S2 DRF Bist Even Fail", 0x00);
            ucBistResult |= (_BIT5 | _BIT2);
        }

        if(ScalerGetBit(P92_E7_SR_SHP_BIST_CTRL_1_S1, _BIT4) != 0x00)
        {
            DebugMessageQC("5. SHP S2 DRF Bist Even Fail", 0x00);
            ucBistResult |= (_BIT4 | _BIT2);
        }
    }
    else
    {
        DebugMessageQC("5. SHP S1/S2 DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }

    // Disable BIST Clock and Disable DRF BIST Mode
    ScalerSetBit(P92_A2_SR_SHP_BIST_CTRL_0_S1, ~_BIT6, 0x00);
    ScalerSetBit(P92_E7_SR_SHP_BIST_CTRL_1_S1, ~_BIT3, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. SHP DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. SHP DRF Bist FAIL", ucBistResult);
        DebugMessageQC("6. SHP DRF Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : Gamma Bist
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCGammaBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

     // Front/Back Register Seperate
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, _BIT7);

    // Test Gamma M1/M2 Bist Mode
    DebugMessageQC("5. ====Gamma M1/M2 Bist Test Start", 0x00);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P9_00_GAMMA_BIST_SET_M1, ~_BIT1, 0x00);
    ScalerSetBit(P9_00_GAMMA_BIST_SET_M1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(P9_01_GAMMA_BIST_CTRL0_M1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_04_GAMMA_BIST_CTRL3_M1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_07_GAMMA_BIST_CTRL0_M2, ~_BIT7, _BIT7);
    ScalerSetBit(P9_0A_GAMMA_BIST_CTRL3_M2, ~_BIT7, _BIT7);


    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_01_GAMMA_BIST_CTRL0_M1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_01_GAMMA_BIST_CTRL0_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma M1 SetA Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_04_GAMMA_BIST_CTRL3_M1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_04_GAMMA_BIST_CTRL3_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma M1 SetB Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_07_GAMMA_BIST_CTRL0_M2, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_07_GAMMA_BIST_CTRL0_M2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma M2 SetA Bist Fail", 0x00);
            ucBistResult |= _BIT5;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_0A_GAMMA_BIST_CTRL3_M2, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_0A_GAMMA_BIST_CTRL3_M2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma M2 SetB Bist Fail", 0x00);
            ucBistResult |= _BIT4;
        }
    }

    // Test RGB Gamma S1/S2 Bist Mode
    DebugMessageQC("5. ====Gamma S1/S2 Bist Test Start", 0x00);


    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P89_00_GAMMA_BIST_SET_S1, ~_BIT1, 0x00);
    ScalerSetBit(P89_00_GAMMA_BIST_SET_S1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(P89_01_GAMMA_BIST_CTRL0_S1, ~_BIT7, _BIT7);
    ScalerSetBit(P89_04_GAMMA_BIST_CTRL3_S1, ~_BIT7, _BIT7);
    ScalerSetBit(P89_07_GAMMA_BIST_CTRL0_S2, ~_BIT7, _BIT7);
    ScalerSetBit(P89_0A_GAMMA_BIST_CTRL3_S2, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_01_GAMMA_BIST_CTRL0_S1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P89_01_GAMMA_BIST_CTRL0_S1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma S1 SetA Bist Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_04_GAMMA_BIST_CTRL3_S1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P89_04_GAMMA_BIST_CTRL3_S1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma S1 SetB Bist Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_07_GAMMA_BIST_CTRL0_S2, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P89_07_GAMMA_BIST_CTRL0_S2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma S2 SetA Bist Fail", 0x00);
            ucBistResult |= _BIT1;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_0A_GAMMA_BIST_CTRL3_S2, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P89_0A_GAMMA_BIST_CTRL3_S2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma S2 SetB Bist Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }

    // Disable BIST Clock and Disable BIST Mode
    ScalerSetBit(P9_00_GAMMA_BIST_SET_M1, ~_BIT0, 0x00);
    ScalerSetBit(P9_01_GAMMA_BIST_CTRL0_M1, ~_BIT7, 0x00);
    ScalerSetBit(P9_04_GAMMA_BIST_CTRL3_M1, ~_BIT7, 0x00);
    ScalerSetBit(P9_07_GAMMA_BIST_CTRL0_M2, ~_BIT7, 0x00);
    ScalerSetBit(P9_0A_GAMMA_BIST_CTRL3_M2, ~_BIT7, 0x00);
    ScalerSetBit(P89_00_GAMMA_BIST_SET_S1, ~_BIT0, 0x00);
    ScalerSetBit(P89_01_GAMMA_BIST_CTRL0_S1, ~_BIT7, 0x00);
    ScalerSetBit(P89_04_GAMMA_BIST_CTRL3_S1, ~_BIT7, 0x00);
    ScalerSetBit(P89_07_GAMMA_BIST_CTRL0_S2, ~_BIT7, 0x00);
    ScalerSetBit(P89_0A_GAMMA_BIST_CTRL3_S2, ~_BIT7, 0x00);

     // Front/Back Register Seperate Disable
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. Gamma Normal Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. Gamma Normal Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

    //---------------Gamma DRF BIST---------------//

    // Test Gamma M1/M2 DRF Bist Mode
    DebugMessageQC("5. ====Gamma M1/M2 DRF Bist Test Start", 0x00);

     // Front/Back Register Seperate
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, _BIT7);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P9_00_GAMMA_BIST_SET_M1, ~_BIT1, 0x00);
    ScalerSetBit(P9_00_GAMMA_BIST_SET_M1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable DRF BIST Mode
    ScalerSetBit(P9_02_GAMMA_BIST_CTRL1_M1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_05_GAMMA_BIST_CTRL4_M1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_08_GAMMA_BIST_CTRL1_M2, ~_BIT7, _BIT7);
    ScalerSetBit(P9_0B_GAMMA_BIST_CTRL4_M2, ~_BIT7, _BIT7);

    // Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_02_GAMMA_BIST_CTRL1_M1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P9_02_GAMMA_BIST_CTRL1_M1, ~_BIT6, 0x00);
            ScalerSetBit(P9_02_GAMMA_BIST_CTRL1_M1, ~_BIT6, _BIT6);
            ScalerSetBit(P9_02_GAMMA_BIST_CTRL1_M1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Gamma M1 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_02_GAMMA_BIST_CTRL1_M1, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P9_03_GAMMA_BIST_CTRL2_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma M1 SetA DRF Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    else
    {
        DebugMessageQC("5. Gamma M1 SetA DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT7;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_05_GAMMA_BIST_CTRL4_M1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P9_05_GAMMA_BIST_CTRL4_M1, ~_BIT6, 0x00);
            ScalerSetBit(P9_05_GAMMA_BIST_CTRL4_M1, ~_BIT6, _BIT6);
            ScalerSetBit(P9_05_GAMMA_BIST_CTRL4_M1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Gamma M1 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_05_GAMMA_BIST_CTRL4_M1, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P9_06_GAMMA_BIST_CTRL5_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma M1 SetB DRF Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }
    else
    {
        DebugMessageQC("5. Gamma M1 SetB DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT6;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_08_GAMMA_BIST_CTRL1_M2, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P9_08_GAMMA_BIST_CTRL1_M2, ~_BIT6, 0x00);
            ScalerSetBit(P9_08_GAMMA_BIST_CTRL1_M2, ~_BIT6, _BIT6);
            ScalerSetBit(P9_08_GAMMA_BIST_CTRL1_M2, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Gamma M2 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT5;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_08_GAMMA_BIST_CTRL1_M2, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P9_09_GAMMA_BIST_CTRL2_M2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma M2 SetA DRF Bist Fail", 0x00);
            ucBistResult |= _BIT5;
        }
    }
    else
    {

        DebugMessageQC("5. Gamma M2 SetA DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT5;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_0B_GAMMA_BIST_CTRL4_M2, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P9_0B_GAMMA_BIST_CTRL4_M2, ~_BIT6, 0x00);
            ScalerSetBit(P9_0B_GAMMA_BIST_CTRL4_M2, ~_BIT6, _BIT6);
            ScalerSetBit(P9_0B_GAMMA_BIST_CTRL4_M2, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Gamma M2 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT4;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_0B_GAMMA_BIST_CTRL4_M2, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P9_0C_GAMMA_BIST_CTRL5_M2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma M2 SetB DRF Bist Fail", 0x00);
            ucBistResult |= _BIT4;
        }
    }
    else
    {
        DebugMessageQC("5. Gamma M2 SetB DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT4;
    }

    // Test Gamma S1/S2 DRF Bist Mode
    DebugMessageQC("5. ====Gamma S1/S2 DRF Bist Test Start", 0x00);


    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P89_00_GAMMA_BIST_SET_S1, ~_BIT1, 0x00);
    ScalerSetBit(P89_00_GAMMA_BIST_SET_S1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable DRF BIST Mode
    ScalerSetBit(P89_02_GAMMA_BIST_CTRL1_S1, ~_BIT7, _BIT7);
    ScalerSetBit(P89_05_GAMMA_BIST_CTRL4_S1, ~_BIT7, _BIT7);
    ScalerSetBit(P89_08_GAMMA_BIST_CTRL1_S2, ~_BIT7, _BIT7);
    ScalerSetBit(P89_0B_GAMMA_BIST_CTRL4_S2, ~_BIT7, _BIT7);

    // Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_02_GAMMA_BIST_CTRL1_S1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P89_02_GAMMA_BIST_CTRL1_S1, ~_BIT6, 0x00);
            ScalerSetBit(P89_02_GAMMA_BIST_CTRL1_S1, ~_BIT6, _BIT6);
            ScalerSetBit(P89_02_GAMMA_BIST_CTRL1_S1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Gamma S1 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_02_GAMMA_BIST_CTRL1_S1, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P89_03_GAMMA_BIST_CTRL2_S1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma S1 SetA DRF Bist Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    else
    {
        DebugMessageQC("5. Gamma S1 SetA DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT3;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_05_GAMMA_BIST_CTRL4_S1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P89_05_GAMMA_BIST_CTRL4_S1, ~_BIT6, 0x00);
            ScalerSetBit(P89_05_GAMMA_BIST_CTRL4_S1, ~_BIT6, _BIT6);
            ScalerSetBit(P89_05_GAMMA_BIST_CTRL4_S1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Gamma S1 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_05_GAMMA_BIST_CTRL4_S1, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P89_06_GAMMA_BIST_CTRL5_S1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma S1 SetB DRF Bist Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }
    else
    {
        DebugMessageQC("5. Gamma S1 SetB DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_08_GAMMA_BIST_CTRL1_S2, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P89_08_GAMMA_BIST_CTRL1_S2, ~_BIT6, 0x00);
            ScalerSetBit(P89_08_GAMMA_BIST_CTRL1_S2, ~_BIT6, _BIT6);
            ScalerSetBit(P89_08_GAMMA_BIST_CTRL1_S2, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Gamma S2 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT1;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_08_GAMMA_BIST_CTRL1_S2, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P89_09_GAMMA_BIST_CTRL2_S2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma S2 SetA DRF Bist Fail", 0x00);
            ucBistResult |= _BIT1;
        }
    }
    else
    {
        DebugMessageQC("5. Gamma S2 SetA DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_0B_GAMMA_BIST_CTRL4_S2, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P89_0B_GAMMA_BIST_CTRL4_S2, ~_BIT6, 0x00);
            ScalerSetBit(P89_0B_GAMMA_BIST_CTRL4_S2, ~_BIT6, _BIT6);
            ScalerSetBit(P89_0B_GAMMA_BIST_CTRL4_S2, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Gamma S2 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_0B_GAMMA_BIST_CTRL4_S2, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P89_0C_GAMMA_BIST_CTRL5_S2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma S2 SetB DRF Bist Fail", 0x00);

            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. Gamma S2 SetB DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT0;
    }

    // Disable BIST Clock and Disable DRF BIST Mode
   // ScalerSetBit(P9_00_GAMMA_BIST_SET_M1, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte(P9_00_GAMMA_BIST_SET_M1, 0x00);
    ScalerSetBit(P9_02_GAMMA_BIST_CTRL1_M1, ~_BIT7, 0x00);
    ScalerSetBit(P9_05_GAMMA_BIST_CTRL4_M1, ~_BIT7, 0x00);
    ScalerSetBit(P9_08_GAMMA_BIST_CTRL1_M2, ~_BIT7, 0x00);
    ScalerSetBit(P9_0B_GAMMA_BIST_CTRL4_M2, ~_BIT7, 0x00);

   // ScalerSetBit(P89_00_GAMMA_BIST_SET_S1, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte(P89_02_GAMMA_BIST_CTRL1_S1, 0x00);
    ScalerSetBit(P89_02_GAMMA_BIST_CTRL1_S1, ~_BIT7, 0x00);
    ScalerSetBit(P89_05_GAMMA_BIST_CTRL4_S1, ~_BIT7, 0x00);
    ScalerSetBit(P89_08_GAMMA_BIST_CTRL1_S2, ~_BIT7, 0x00);
    ScalerSetBit(P89_0B_GAMMA_BIST_CTRL4_S2, ~_BIT7, 0x00);


     // Front/Back Register Seperate Disable
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, 0x00);


    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. Gamma DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. Gamma DRF Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : DCC BIST Test
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCDCCBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    DebugMessageQC("5. ====DCC Bist Test Start", 0x00);
    ScalerSetBit(P7_C7_DCC_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    ScalerSetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_00_PORT_PAGE3_SRAM_BIST, ~(_BIT3 | _BIT2), _BIT3 | _BIT2);
    ScalerSetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_00_PORT_PAGE3_SRAM_BIST, ~(_BIT3 | _BIT2), _BIT2);
    ScalerSetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_00_PORT_PAGE3_SRAM_BIST, ~_BIT7, _BIT7);

    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_00_PORT_PAGE3_SRAM_BIST, _BIT1, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_00_PORT_PAGE3_SRAM_BIST, _BIT0) != 0x00)
        {
            DebugMessageQC("5. DCC Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        };
    }
    else
    {
        DebugMessageQC("5. DCC Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT6;
    }

    // DCC diable Bist test
    ScalerSetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_00_PORT_PAGE3_SRAM_BIST, ~_BIT7, 0x00);
    ScalerSetBit(P7_C7_DCC_CTRL_0, ~(_BIT1 | _BIT0), 0x00);

    //------------DCC DRF BIST---------------//
    ScalerSetBit(P7_C7_DCC_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_00_PORT_PAGE3_SRAM_BIST, ~(_BIT3 | _BIT2), _BIT3 | _BIT2);
    ScalerSetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_00_PORT_PAGE3_SRAM_BIST, ~(_BIT3 | _BIT2), _BIT2);
    DebugMessageQC("5. ====DCC DRF Bist Test Start", 0x00);

    //1.Start DRF BIST mode
    ScalerSetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_01_PORT_PAGE3_SRAM_DRF_BIST, ~_BIT7, _BIT7);

    //2.Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_01_PORT_PAGE3_SRAM_DRF_BIST, _BIT1, _TRUE) == _TRUE)
        {
            //3.Wait 1ms
            //ScalerTimerDelayXms(2);
            ScalerSetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_01_PORT_PAGE3_SRAM_DRF_BIST, ~_BIT6, _BIT6);
            ScalerSetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_01_PORT_PAGE3_SRAM_DRF_BIST, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. DCC DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    //8.Wait DRF Bist Done
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_01_PORT_PAGE3_SRAM_DRF_BIST, _BIT3, _TRUE) == _TRUE)
    {
        //9.Check Bist Pass or Fail
        if(ScalerGetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_01_PORT_PAGE3_SRAM_DRF_BIST, _BIT2) != 0x00)
        {
            DebugMessageQC("5. DCC DRF Bist Fail", 0x00);
            ucBistResult |= _BIT2;
        };
    }
    else
    {
        DebugMessageQC("5. DCC DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }

    // D1 DCC diable DRF Bist test
    ScalerSetDataPortBit(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_01_PORT_PAGE3_SRAM_DRF_BIST, ~_BIT7, 0x00);
    ScalerSetBit(P7_C7_DCC_CTRL_0, ~(_BIT1 | _BIT0), 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. DCC DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. DCC DRF Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. DCC DRF Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : RGB Gamma BIST
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCRGBGammaBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    // Test RGB Gamma M1/M2 Bist Mode
    DebugMessageQC("5. ====RGB Gamma M1/M2 Bist Test Start", 0x00);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P9_10_RGB_GAMMA_CLK_M1, ~_BIT1, 0x00);
    ScalerSetBit(P9_10_RGB_GAMMA_CLK_M1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(P9_11_RGB_GAMMA_BIST_CTRL0_M1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_14_RGB_GAMMA_BIST_CTRL3_M1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_17_RGB_GAMMA_BIST_CTRL0_M2, ~_BIT7, _BIT7);
    ScalerSetBit(P9_1A_RGB_GAMMA_BIST_CTRL3_M2, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_11_RGB_GAMMA_BIST_CTRL0_M1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_11_RGB_GAMMA_BIST_CTRL0_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma M1 SetA Bist Even Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_14_RGB_GAMMA_BIST_CTRL3_M1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_14_RGB_GAMMA_BIST_CTRL3_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma M1 SetB Bist Even Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_17_RGB_GAMMA_BIST_CTRL0_M2, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_17_RGB_GAMMA_BIST_CTRL0_M2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma M2 SetA Bist Even Fail", 0x00);
            ucBistResult |= _BIT5;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_1A_RGB_GAMMA_BIST_CTRL3_M2, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_1A_RGB_GAMMA_BIST_CTRL3_M2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma M2 SetB Bist Even Fail", 0x00);
            ucBistResult |= _BIT4;
        }
    }

    // Test RGB Gamma S1/S2 Bist Mode
    DebugMessageQC("5. ====RGB Gamma S1/S2 Bist Test Start", 0x00);

    // Front/Back Register Seperate
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, _BIT7);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P89_10_RGB_GAMMA_CLK_S1, ~_BIT1, 0x00);
    ScalerSetBit(P89_10_RGB_GAMMA_CLK_S1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(P89_11_RGB_GAMMA_BIST_CTRL0_S1, ~_BIT7, _BIT7);
    ScalerSetBit(P89_14_RGB_GAMMA_BIST_CTRL3_S1, ~_BIT7, _BIT7);
    ScalerSetBit(P89_17_RGB_GAMMA_BIST_CTRL0_S2, ~_BIT7, _BIT7);
    ScalerSetBit(P89_1A_RGB_GAMMA_BIST_CTRL3_S2, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_11_RGB_GAMMA_BIST_CTRL0_S1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P89_11_RGB_GAMMA_BIST_CTRL0_S1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma S1 SetA Bist Even Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_14_RGB_GAMMA_BIST_CTRL3_S1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P89_14_RGB_GAMMA_BIST_CTRL3_S1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma S1 SetB Bist Even Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_17_RGB_GAMMA_BIST_CTRL0_S2, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P89_17_RGB_GAMMA_BIST_CTRL0_S2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma S2 SetA Bist Even Fail", 0x00);
            ucBistResult |= _BIT5;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_1A_RGB_GAMMA_BIST_CTRL3_S2, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P89_1A_RGB_GAMMA_BIST_CTRL3_S2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma S2 SetB Bist Even Fail", 0x00);
            ucBistResult |= _BIT4;
        }
    }

    // Disable BIST Clock and Disable BIST Mode
    ScalerSetBit(P9_10_RGB_GAMMA_CLK_M1, ~_BIT0, 0x00);
    ScalerSetBit(P9_11_RGB_GAMMA_BIST_CTRL0_M1, ~_BIT7, 0x00);
    ScalerSetBit(P9_14_RGB_GAMMA_BIST_CTRL3_M1, ~_BIT7, 0x00);
    ScalerSetBit(P9_17_RGB_GAMMA_BIST_CTRL0_M2, ~_BIT7, 0x00);
    ScalerSetBit(P9_1A_RGB_GAMMA_BIST_CTRL3_M2, ~_BIT7, 0x00);
    ScalerSetBit(P89_10_RGB_GAMMA_CLK_S1, ~_BIT0, 0x00);
    ScalerSetBit(P89_11_RGB_GAMMA_BIST_CTRL0_S1, ~_BIT7, 0x00);
    ScalerSetBit(P89_14_RGB_GAMMA_BIST_CTRL3_S1, ~_BIT7, 0x00);
    ScalerSetBit(P89_17_RGB_GAMMA_BIST_CTRL0_S2, ~_BIT7, 0x00);
    ScalerSetBit(P89_1A_RGB_GAMMA_BIST_CTRL3_S2, ~_BIT7, 0x00);

    // Disable Front/Back Register Seperate
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. RGB Gamma Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. RGB Gamma Bist FAIL", ucBistResult);
        DebugMessageQC("6. RGB Gamma Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    //---------------RGB Gamma DRF BIST---------------//

    // Test RGB Gamma M1/M2 DRF Bist Mode
    DebugMessageQC("5. ====RGB Gamma M1/M2 DRF Bist Test Start", 0x00);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P9_10_RGB_GAMMA_CLK_M1, ~_BIT1, 0x00);
    ScalerSetBit(P9_10_RGB_GAMMA_CLK_M1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable DRF BIST Mode
    ScalerSetBit(P9_12_RGB_GAMMA_BIST_CTRL1_M1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_15_RGB_GAMMA_BIST_CTRL4_M1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_18_RGB_GAMMA_BIST_CTRL1_M2, ~_BIT7, _BIT7);
    ScalerSetBit(P9_1B_RGB_GAMMA_BIST_CTRL4_M2, ~_BIT7, _BIT7);

    // Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_12_RGB_GAMMA_BIST_CTRL1_M1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P9_12_RGB_GAMMA_BIST_CTRL1_M1, ~_BIT6, 0x00);
            ScalerSetBit(P9_12_RGB_GAMMA_BIST_CTRL1_M1, ~_BIT6, _BIT6);
            ScalerSetBit(P9_12_RGB_GAMMA_BIST_CTRL1_M1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. RGB Gamma M1 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }

    // Wait DRF BIST Done
    if(ScalerGetBit(P9_12_RGB_GAMMA_BIST_CTRL1_M1, _BIT4) == _BIT4)
    {
        if(ScalerGetBit(P9_13_RGB_GAMMA_BIST_CTRL2_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma M1 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    else
    {
        DebugMessageQC("5. RGB Gamma M1 SetA DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT3;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_15_RGB_GAMMA_BIST_CTRL4_M1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P9_15_RGB_GAMMA_BIST_CTRL4_M1, ~_BIT6, 0x00);
            ScalerSetBit(P9_15_RGB_GAMMA_BIST_CTRL4_M1, ~_BIT6, _BIT6);
            ScalerSetBit(P9_15_RGB_GAMMA_BIST_CTRL4_M1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. RGB Gamma M1 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }

    // Wait DRF BIST Done
    if(ScalerGetBit(P9_15_RGB_GAMMA_BIST_CTRL4_M1, _BIT4) == _BIT4)
    {
        if(ScalerGetBit(P9_16_RGB_GAMMA_BIST_CTRL5_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma M1 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }
    else
    {
        DebugMessageQC("5. RGB Gamma M1 SetB DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_18_RGB_GAMMA_BIST_CTRL1_M2, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P9_18_RGB_GAMMA_BIST_CTRL1_M2, ~_BIT6, 0x00);
            ScalerSetBit(P9_18_RGB_GAMMA_BIST_CTRL1_M2, ~_BIT6, _BIT6);
            ScalerSetBit(P9_18_RGB_GAMMA_BIST_CTRL1_M2, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. RGB Gamma M2 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT1;
        }
    }

    // Wait DRF BIST Done
    if(ScalerGetBit(P9_18_RGB_GAMMA_BIST_CTRL1_M2, _BIT4) == _BIT4)
    {
        if(ScalerGetBit(P9_19_RGB_GAMMA_BIST_CTRL2_M2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma M2 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT1;
        }
    }
    else
    {
        DebugMessageQC("5. RGB Gamma M2 SetA DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_1B_RGB_GAMMA_BIST_CTRL4_M2, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P9_1B_RGB_GAMMA_BIST_CTRL4_M2, ~_BIT6, 0x00);
            ScalerSetBit(P9_1B_RGB_GAMMA_BIST_CTRL4_M2, ~_BIT6, _BIT6);
            ScalerSetBit(P9_1B_RGB_GAMMA_BIST_CTRL4_M2, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. RGB Gamma M2 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }

    // Wait DRF BIST Done
    if(ScalerGetBit(P9_1B_RGB_GAMMA_BIST_CTRL4_M2, _BIT4) == _BIT4)
    {
        if(ScalerGetBit(P9_1C_RGB_GAMMA_BIST_CTRL5_M2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma M2 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. RGB Gamma M2 SetB DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT0;
    }

    // Test RGB Gamma S1/S2 DRF Bist Mode
    DebugMessageQC("5. ====RGB Gamma S1/S2 DRF Bist Test Start", 0x00);

    // Front/Back Register Seperate
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, _BIT7);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P89_10_RGB_GAMMA_CLK_S1, ~_BIT1, 0x00);
    ScalerSetBit(P89_10_RGB_GAMMA_CLK_S1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable DRF BIST Mode
    ScalerSetBit(P89_12_RGB_GAMMA_BIST_CTRL1_S1, ~_BIT7, _BIT7);
    ScalerSetBit(P89_15_RGB_GAMMA_BIST_CTRL4_S1, ~_BIT7, _BIT7);
    ScalerSetBit(P89_18_RGB_GAMMA_BIST_CTRL1_S2, ~_BIT7, _BIT7);
    ScalerSetBit(P89_1B_RGB_GAMMA_BIST_CTRL4_S2, ~_BIT7, _BIT7);

    // Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_12_RGB_GAMMA_BIST_CTRL1_S1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P89_12_RGB_GAMMA_BIST_CTRL1_S1, ~_BIT6, 0x00);
            ScalerSetBit(P89_12_RGB_GAMMA_BIST_CTRL1_S1, ~_BIT6, _BIT6);
            ScalerSetBit(P89_12_RGB_GAMMA_BIST_CTRL1_S1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. RGB Gamma S1 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }

    // Wait DRF BIST Done
    if(ScalerGetBit(P89_12_RGB_GAMMA_BIST_CTRL1_S1, _BIT4) == _BIT4)
    {
        if(ScalerGetBit(P89_13_RGB_GAMMA_BIST_CTRL2_S1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma S1 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    else
    {
        DebugMessageQC("5. RGB Gamma S1 SetA DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT3;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_15_RGB_GAMMA_BIST_CTRL4_S1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P89_15_RGB_GAMMA_BIST_CTRL4_S1, ~_BIT6, 0x00);
            ScalerSetBit(P89_15_RGB_GAMMA_BIST_CTRL4_S1, ~_BIT6, _BIT6);
            ScalerSetBit(P89_15_RGB_GAMMA_BIST_CTRL4_S1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. RGB Gamma S1 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }

    // Wait DRF BIST Done
    if(ScalerGetBit(P89_15_RGB_GAMMA_BIST_CTRL4_S1, _BIT4) == _BIT4)
    {
        if(ScalerGetBit(P89_16_RGB_GAMMA_BIST_CTRL5_S1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma S1 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }
    else
    {
        DebugMessageQC("5. RGB Gamma S1 SetB DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_18_RGB_GAMMA_BIST_CTRL1_S2, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P89_18_RGB_GAMMA_BIST_CTRL1_S2, ~_BIT6, 0x00);
            ScalerSetBit(P89_18_RGB_GAMMA_BIST_CTRL1_S2, ~_BIT6, _BIT6);
            ScalerSetBit(P89_18_RGB_GAMMA_BIST_CTRL1_S2, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. RGB Gamma S2 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT1;
        }
    }

    // Wait DRF BIST Done
    if(ScalerGetBit(P89_18_RGB_GAMMA_BIST_CTRL1_S2, _BIT4) == _BIT4)
    {
        if(ScalerGetBit(P89_19_RGB_GAMMA_BIST_CTRL2_S2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma S2 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT1;
        }
    }
    else
    {
        DebugMessageQC("5. RGB Gamma S2 SetA DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_1B_RGB_GAMMA_BIST_CTRL4_S2, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P89_1B_RGB_GAMMA_BIST_CTRL4_S2, ~_BIT6, 0x00);
            ScalerSetBit(P89_1B_RGB_GAMMA_BIST_CTRL4_S2, ~_BIT6, _BIT6);
            ScalerSetBit(P89_1B_RGB_GAMMA_BIST_CTRL4_S2, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. RGB Gamma S2 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }

    // Wait DRF BIST Done
    if(ScalerGetBit(P89_1B_RGB_GAMMA_BIST_CTRL4_S2, _BIT4) == _BIT4)
    {
        if(ScalerGetBit(P89_1C_RGB_GAMMA_BIST_CTRL5_S2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma S2 SetB DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. RGB Gamma S2 SetB DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT0;
    }

    // Disable BIST Clock and Disable DRF BIST Mode
    ScalerSetBit(P9_10_RGB_GAMMA_CLK_M1, ~_BIT1, 0x00);
    ScalerSetBit(P9_12_RGB_GAMMA_BIST_CTRL1_M1, ~_BIT7, 0x00);
    ScalerSetBit(P9_15_RGB_GAMMA_BIST_CTRL4_M1, ~_BIT7, 0x00);
    ScalerSetBit(P9_18_RGB_GAMMA_BIST_CTRL1_M2, ~_BIT7, 0x00);
    ScalerSetBit(P9_1B_RGB_GAMMA_BIST_CTRL4_M2, ~_BIT7, 0x00);
    ScalerSetBit(P89_10_RGB_GAMMA_CLK_S1, ~_BIT0, 0x00);
    ScalerSetBit(P89_12_RGB_GAMMA_BIST_CTRL1_S1, ~_BIT7, 0x00);
    ScalerSetBit(P89_15_RGB_GAMMA_BIST_CTRL4_S1, ~_BIT7, 0x00);
    ScalerSetBit(P89_18_RGB_GAMMA_BIST_CTRL1_S2, ~_BIT7, 0x00);
    ScalerSetBit(P89_1B_RGB_GAMMA_BIST_CTRL4_S2, ~_BIT7, 0x00);

    // Disable Front/Back Register Seperate
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. RGB Gamma DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. RGB Gamma DRF Bist FAIL", ucBistResult);
        DebugMessageQC("6. RGB Gamma DRF Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : Gamma Bist
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQC3DGammaBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

     // Front/Back Register Seperate
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, _BIT7);

    // Test Gamma M1/M2 Bist Mode
    DebugMessageQC("5. ====3D Gamma M1/M2 Bist Test Start", 0x00);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~_BIT1, 0x00);
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_B6_RGB_3D_GAMMA_BIST_CTRL_MAIN2_1, ~_BIT7, _BIT7);


    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma M1 Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        }

        if(ScalerGetBit(P9_B5_RGB_3D_GAMMA_BIST_CTRL_MAIN1_2, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma M1 Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_B6_RGB_3D_GAMMA_BIST_CTRL_MAIN2_1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_B6_RGB_3D_GAMMA_BIST_CTRL_MAIN2_1, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma M2 Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetBit(P9_B7_RGB_3D_GAMMA_BIST_CTRL_MAIN2_2, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma M2 Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }


    // Test RGB Gamma S1/S2 Bist Mode
    DebugMessageQC("5. ====Gamma S1/S2 Bist Test Start", 0x00);


    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P89_B4_RGB_3D_GAMMA_BIST_CTRL_SUB1_1, ~_BIT1, 0x00);
    ScalerSetBit(P89_B4_RGB_3D_GAMMA_BIST_CTRL_SUB1_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(P89_B4_RGB_3D_GAMMA_BIST_CTRL_SUB1_1, ~_BIT7, _BIT7);
    ScalerSetBit(P89_B6_RGB_3D_GAMMA_BIST_CTRL_SUB2_1, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_B4_RGB_3D_GAMMA_BIST_CTRL_SUB1_1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P89_B4_RGB_3D_GAMMA_BIST_CTRL_SUB1_1, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma S1 Bist Fail", 0x00);
            ucBistResult |= _BIT5;
        }

        if(ScalerGetBit(P89_B5_RGB_3D_GAMMA_BIST_CTRL_SUB1_2, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma S1 Bist Fail", 0x00);
            ucBistResult |= _BIT5;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_B6_RGB_3D_GAMMA_BIST_CTRL_SUB2_1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P89_B6_RGB_3D_GAMMA_BIST_CTRL_SUB2_1, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma S2 Bist Fail", 0x00);
            ucBistResult |= _BIT4;
        }

        if(ScalerGetBit(P89_B7_RGB_3D_GAMMA_BIST_CTRL_SUB2_2, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma S2 Bist Fail", 0x00);
            ucBistResult |= _BIT4;
        }
    }


    // Disable BIST Clock and Disable BIST Mode
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~_BIT0, 0x00);
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~_BIT7, 0x00);
    ScalerSetBit(P9_B6_RGB_3D_GAMMA_BIST_CTRL_MAIN2_1, ~_BIT7, 0x00);
    ScalerSetBit(P89_B4_RGB_3D_GAMMA_BIST_CTRL_SUB1_1, ~_BIT0, 0x00);
    ScalerSetBit(P89_B4_RGB_3D_GAMMA_BIST_CTRL_SUB1_1, ~_BIT7, 0x00);
    ScalerSetBit(P89_B6_RGB_3D_GAMMA_BIST_CTRL_SUB2_1, ~_BIT7, 0x00);

     // Front/Back Register Seperate Disable
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. 3D Gamma Normal Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. 3D Gamma Normal Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

    //---------------Gamma DRF BIST---------------//

    // Test Gamma M1/M2 DRF Bist Mode
    DebugMessageQC("5. ====3D Gamma M1/M2 DRF Bist Test Start", 0x00);

    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, _BIT7);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~_BIT1, 0x00);
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable DRF BIST Mode
    ScalerSetBit(P9_B8_RGB_3D_GAMMA_DRF_BIST_MAIN1_1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_BA_RGB_3D_GAMMA_DRF_BIST_MAIN2_1, ~_BIT7, _BIT7);

    // Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_B8_RGB_3D_GAMMA_DRF_BIST_MAIN1_1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P9_B8_RGB_3D_GAMMA_DRF_BIST_MAIN1_1, ~_BIT6, 0x00);
            ScalerSetBit(P9_B8_RGB_3D_GAMMA_DRF_BIST_MAIN1_1, ~_BIT6, _BIT6);
            ScalerSetBit(P9_B8_RGB_3D_GAMMA_DRF_BIST_MAIN1_1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Gamma M1 SetA DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_B8_RGB_3D_GAMMA_DRF_BIST_MAIN1_1, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P9_B8_RGB_3D_GAMMA_DRF_BIST_MAIN1_1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma M1 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        }

        if(ScalerGetBit(P9_B9_RGB_3D_GAMMA_DRF_BIST_MAIN1_2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma M1 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    else
    {
            DebugMessageQC("5. 3D Gamma M1 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_BA_RGB_3D_GAMMA_DRF_BIST_MAIN2_1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P9_BA_RGB_3D_GAMMA_DRF_BIST_MAIN2_1, ~_BIT6, 0x00);
            ScalerSetBit(P9_BA_RGB_3D_GAMMA_DRF_BIST_MAIN2_1, ~_BIT6, _BIT6);
            ScalerSetBit(P9_BA_RGB_3D_GAMMA_DRF_BIST_MAIN2_1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. 3D Gamma M2 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_BA_RGB_3D_GAMMA_DRF_BIST_MAIN2_1, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P9_BA_RGB_3D_GAMMA_DRF_BIST_MAIN2_1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma M2 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetBit(P9_BB_RGB_3D_GAMMA_DRF_BIST_MAIN2_2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma M2 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }
    else
    {
        DebugMessageQC("5. 3D Gamma M2 DRF Bist Start Pause Time Out Fail -1", 0x00);
        ucBistResult |= _BIT6;
    }


    // Test Gamma S1/S2 DRF Bist Mode
    DebugMessageQC("5. ====3D Gamma S1/S2 DRF Bist Test Start", 0x00);


    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P89_B4_RGB_3D_GAMMA_BIST_CTRL_SUB1_1, ~_BIT1, 0x00);
    ScalerSetBit(P89_B4_RGB_3D_GAMMA_BIST_CTRL_SUB1_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable DRF BIST Mode
    ScalerSetBit(P89_B8_RGB_3D_GAMMA_DRF_BIST_SUB1_1, ~_BIT7, _BIT7);
    ScalerSetBit(P89_BA_RGB_3D_GAMMA_DRF_BIST_SUB2_1, ~_BIT7, _BIT7);

    // Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_B8_RGB_3D_GAMMA_DRF_BIST_SUB1_1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P89_B8_RGB_3D_GAMMA_DRF_BIST_SUB1_1, ~_BIT6, 0x00);
            ScalerSetBit(P89_B8_RGB_3D_GAMMA_DRF_BIST_SUB1_1, ~_BIT6, _BIT6);
            ScalerSetBit(P89_B8_RGB_3D_GAMMA_DRF_BIST_SUB1_1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. 3D Gamma S1 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }


    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_B8_RGB_3D_GAMMA_DRF_BIST_SUB1_1, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P89_B8_RGB_3D_GAMMA_DRF_BIST_SUB1_1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma S1 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT3;
        }

        if(ScalerGetBit(P89_B9_RGB_3D_GAMMA_DRF_BIST_SUB1_2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma S1 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    else
    {
        DebugMessageQC("5. 3D Gamma S1 DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT3;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_BA_RGB_3D_GAMMA_DRF_BIST_SUB2_1, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P89_BA_RGB_3D_GAMMA_DRF_BIST_SUB2_1, ~_BIT6, 0x00);
            ScalerSetBit(P89_BA_RGB_3D_GAMMA_DRF_BIST_SUB2_1, ~_BIT6, _BIT6);
            ScalerSetBit(P89_BA_RGB_3D_GAMMA_DRF_BIST_SUB2_1, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. 3D Gamma S1 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }


    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P89_BA_RGB_3D_GAMMA_DRF_BIST_SUB2_1, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P89_BA_RGB_3D_GAMMA_DRF_BIST_SUB2_1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma S2 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT2;
        }

        if(ScalerGetBit(P89_BB_RGB_3D_GAMMA_DRF_BIST_SUB2_2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma S2 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }
    else
    {
        DebugMessageQC("5. 3D Gamma S2 DRF Bist Start Pause Time Out Fail -1 ", 0x00);
        ucBistResult |= _BIT2;
    }


    // Disable BIST Clock and Disable DRF BIST Mode
  //  ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~_BIT0, 0x00);
    ScalerSetByte(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, 0x00);
    ScalerSetBit(P9_B8_RGB_3D_GAMMA_DRF_BIST_MAIN1_1, ~_BIT7, 0x00);
    ScalerSetBit(P9_BA_RGB_3D_GAMMA_DRF_BIST_MAIN2_1, ~_BIT7, 0x00);
 //   ScalerSetBit(P89_B4_RGB_3D_GAMMA_BIST_CTRL_SUB1_1, ~_BIT0, 0x00);
    ScalerSetByte(P89_B4_RGB_3D_GAMMA_BIST_CTRL_SUB1_1, 0x00);
    ScalerSetBit(P89_B8_RGB_3D_GAMMA_DRF_BIST_SUB1_1, ~_BIT7, 0x00);
    ScalerSetBit(P89_BA_RGB_3D_GAMMA_DRF_BIST_SUB2_1, ~_BIT7, 0x00);

     // Front/Back Register Seperate Disable
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, 0x00);


    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. 3D Gamma DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. 3D RGB Gamma DRF Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : Panel Uniformity Bist
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCPanelUniformityBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

//------------Panel Uniformity BIST---------------
    DebugMessageQC("5. ====Panel Uniformity Bist Test Start", 0x00);

    // Front/Back Register Seperate Disable
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, _BIT7);

    // Test Panel Uniformity Gain LUT BIST
    ScalerSetBit(P34_09_UN_SRAM_BIST, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(P34_09_UN_SRAM_BIST, ~_BIT3, 0x00);
    ScalerSetBit(P34_09_UN_SRAM_BIST, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P34_09_UN_SRAM_BIST, _BIT6, _BIT6) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(P34_09_UN_SRAM_BIST, (_BIT5 | _BIT4)) != 0x00)
        {
            DebugMessageQC("5. Panel Uniformity Gain LUT Bist Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. Panel Uniformity Gain LUT Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT0;
    }
    ScalerSetBit(P34_09_UN_SRAM_BIST, ~_BIT7, 0x00);

    // Test Panel Uniformity Offset LUT BIST
    ScalerSetBit(P34_10_UN_OFFSET_SRAM_BIST, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(P34_10_UN_OFFSET_SRAM_BIST, ~_BIT3, 0x00);
    ScalerSetBit(P34_10_UN_OFFSET_SRAM_BIST, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P34_10_UN_OFFSET_SRAM_BIST, _BIT6, _BIT6) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(P34_10_UN_OFFSET_SRAM_BIST, (_BIT5 | _BIT4)) != 0x00)
        {
            DebugMessageQC("5. Panel Uniformity Offset LUT Bist Fail", 0x00);
            ucBistResult |= _BIT1;
        }
    }
    else
    {
        DebugMessageQC("5. Panel Uniformity Offset LUT Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P34_10_UN_OFFSET_SRAM_BIST, ~_BIT7, 0x00);

    // Test Panel Uniformity M1 Decay LUT BIST
    ScalerSetBit(P34_15_UN_DECAY_SRAM_BIST, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(P34_15_UN_DECAY_SRAM_BIST, ~_BIT3 , 0x00);
    ScalerSetBit(P34_15_UN_DECAY_SRAM_BIST, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P34_15_UN_DECAY_SRAM_BIST, _BIT6, _BIT6) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(P34_15_UN_DECAY_SRAM_BIST, (_BIT5 | _BIT4 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Panel Uniformity M1 Decay LUT Bist Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }
    else
    {
        DebugMessageQC("5. Panel Uniformity M1 Decay LUT Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }
    ScalerSetBit(P34_15_UN_DECAY_SRAM_BIST, ~_BIT7, 0x00);

    // Test Panel Uniformity S1 Decay LUT BIST
    ScalerSetBit(PB4_15_UN_DECAY_SRAM_BIST, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(PB4_15_UN_DECAY_SRAM_BIST, ~_BIT3, 0x00);
    ScalerSetBit(PB4_15_UN_DECAY_SRAM_BIST, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB4_15_UN_DECAY_SRAM_BIST, _BIT6, _BIT6) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(PB4_15_UN_DECAY_SRAM_BIST, (_BIT5 | _BIT4 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Panel Uniformity S1 Decay LUT Bist Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    else
    {
        DebugMessageQC("5. Panel Uniformity S1 Decay LUT Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT3;
    }
    ScalerSetBit(PB4_15_UN_DECAY_SRAM_BIST, ~_BIT7, 0x00);

     // Front/Back Register Seperate Disable
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. Panel Uniformity Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. Panel Uniformity Bist Fail Mode", ucBistResult);
        return _TEST_FAIL;
    }
    ucBistResult = 0x00;

//------------Panel Uniformity  DRF BIST---------------//
    DebugMessageQC("5. ====Panel Uniformity DRF Bist Test Start", 0x00);

    // Front/Back Register Seperate Disable
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, _BIT7);

    // Test Panel Uniformity Gain LUT DRF BIST
    ScalerSetBit(P34_09_UN_SRAM_BIST, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(P34_09_UN_SRAM_BIST, ~_BIT3, 0x00);
    ScalerSetBit(P34_0A_UN_SRAM_DRF_BIST, ~_BIT7, _BIT7);
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P34_0A_UN_SRAM_DRF_BIST, _BIT1, _BIT1) == _TRUE)
        {
            // DRF BIST Start Pause, Set DRF BIST Resume
            ScalerSetBit(P34_0A_UN_SRAM_DRF_BIST, ~_BIT6, _BIT6);
            ScalerSetBit(P34_0A_UN_SRAM_DRF_BIST, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Panel Uniformity Gain LUT DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P34_0A_UN_SRAM_DRF_BIST, _BIT3, _BIT3) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(P34_0A_UN_SRAM_DRF_BIST, (_BIT0 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. Panel Uniformity Gain LUT DRF Bist Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. Panel Uniformity Gain LUT DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT0;
    }

    ScalerSetBit(P34_0A_UN_SRAM_DRF_BIST, ~_BIT7, 0x00);

    // Test Panel Uniformity Offset LUT DRF BIST
    ScalerSetBit(P34_10_UN_OFFSET_SRAM_BIST, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(P34_10_UN_OFFSET_SRAM_BIST, ~_BIT3, 0x00);
    ScalerSetBit(P34_11_UN_OFFSET_SRAM_DRF_BIST, ~_BIT7, _BIT7);
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P34_11_UN_OFFSET_SRAM_DRF_BIST, _BIT1, _BIT1) == _TRUE)
        {
            // DRF BIST Start Pause, Set DRF BIST Resume
            ScalerSetBit(P34_11_UN_OFFSET_SRAM_DRF_BIST, ~_BIT6, _BIT6);
            ScalerSetBit(P34_11_UN_OFFSET_SRAM_DRF_BIST, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Panel Uniformity Offset LUT DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT1;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P34_11_UN_OFFSET_SRAM_DRF_BIST, _BIT3, _BIT3) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(P34_11_UN_OFFSET_SRAM_DRF_BIST, (_BIT0 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. Panel Uniformity Offset LUT DRF Bist Fail", 0x00);
            ucBistResult |= _BIT1;
        }
    }
    else
    {
        DebugMessageQC("5. Panel Uniformity Offset LUT DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }

    ScalerSetBit(P34_11_UN_OFFSET_SRAM_DRF_BIST, ~_BIT7, 0x00);

    // Test Panel Uniformity M1 Decay LUT DRF BIST
    ScalerSetBit(P34_15_UN_DECAY_SRAM_BIST, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(P34_15_UN_DECAY_SRAM_BIST, ~_BIT3, 0x00);
    ScalerSetBit(P34_16_UN_DECAY_SRAM_DRF_BIST, ~_BIT7, _BIT7);
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P34_16_UN_DECAY_SRAM_DRF_BIST, _BIT1, _BIT1) == _TRUE)
        {
            // DRF BIST Start Pause, Set DRF BIST Resume
            ScalerSetBit(P34_16_UN_DECAY_SRAM_DRF_BIST, ~_BIT6, _BIT6);
            ScalerSetBit(P34_16_UN_DECAY_SRAM_DRF_BIST, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Panel Uniformity M1 Decay LUT DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P34_16_UN_DECAY_SRAM_DRF_BIST, _BIT3, _BIT3) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(P34_16_UN_DECAY_SRAM_DRF_BIST, (_BIT5 | _BIT4 | _BIT2 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Panel Uniformity M1 Decay LUT DRF Bist Fail", 0x00);
            ucBistResult |= _BIT2;
        }
    }
    else
    {
        DebugMessageQC("5. Panel Uniformity M1 Decay LUT DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }

    ScalerSetBit(P34_16_UN_DECAY_SRAM_DRF_BIST, ~_BIT7, 0x00);

    // Test Panel Uniformity S1 Decay LUT DRF BIST
    ScalerSetBit(PB4_15_UN_DECAY_SRAM_BIST, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(PB4_15_UN_DECAY_SRAM_BIST, ~_BIT3, 0x00);
    ScalerSetBit(PB4_16_UN_DECAY_SRAM_DRF_BIST, ~_BIT7, _BIT7);
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB4_16_UN_DECAY_SRAM_DRF_BIST, _BIT1, _BIT1) == _TRUE)
        {
            // DRF BIST Start Pause, Set DRF BIST Resume
            ScalerSetBit(PB4_16_UN_DECAY_SRAM_DRF_BIST, ~_BIT6, _BIT6);
            ScalerSetBit(PB4_16_UN_DECAY_SRAM_DRF_BIST, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. Panel Uniformity S1 Decay LUT DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB4_16_UN_DECAY_SRAM_DRF_BIST, _BIT3, _BIT3) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(PB4_16_UN_DECAY_SRAM_DRF_BIST, (_BIT5 | _BIT4 | _BIT2 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Panel Uniformity S1 Decay LUT DRF Bist Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    else
    {
        DebugMessageQC("5. Panel Uniformity S1 Decay LUT DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT3;
    }

    ScalerSetBit(PB4_16_UN_DECAY_SRAM_DRF_BIST, ~_BIT7, 0x00);

    // Front/Back Register Seperate Disable
    ScalerSetBit(P31_F0_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. Panel Uniformity DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. Panel Uniformity DRF Bist Fail Mode", ucBistResult);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : Display Conversion Bist
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCDisplayConversionBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucDSPCTemp[10] = {0};

    DebugMessageQC("5. ====Display Conversion Bist Test Start", 0x00);

    // Test LVDS Table SRAM
    DebugMessageQC("5. ====LVDS Bist Test Start", 0x00);

    // Enable LVDS Bist Clk
    ScalerSetBit(P39_24_LVDS_DRF_BIST_CTRL2, ~_BIT6, _BIT6);

    ScalerSetBit(P39_21_LVDS_BIST_CTRL, ~_BIT7, _BIT7);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P39_21_LVDS_BIST_CTRL, _BIT6, _BIT6) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT5) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.5 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT4) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.4 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT3) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.3 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT2) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.2 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT1) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.1 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT0) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.0 Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. LVDS Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P39_21_LVDS_BIST_CTRL, ~_BIT7, 0x00);

    DebugMessageQC("5. ====LVDS Bist Test End", 0x00);

    // LVDS Bist Software Reset
    ScalerSetBit(P39_24_LVDS_DRF_BIST_CTRL2, ~_BIT7, 0x00);
    ScalerSetBit(P39_24_LVDS_DRF_BIST_CTRL2, ~_BIT7, _BIT7);

    DebugMessageQC("5. ====LVDS DRF Bist Test Start", 0x00);

    ScalerSetBit(P39_22_LVDS_DRF_BIST_CTRL0, ~_BIT7, _BIT7);
    if(ScalerTimerPollingFlagProc(10, P39_22_LVDS_DRF_BIST_CTRL0, _BIT5, _BIT5) == _TRUE)
    {
        // Toggle drf_test_resume
        ScalerSetBit(P39_22_LVDS_DRF_BIST_CTRL0, ~_BIT6, _BIT6);
        ScalerSetBit(P39_22_LVDS_DRF_BIST_CTRL0, ~_BIT6, 0x00);

        if(ScalerTimerPollingFlagProc(10, P39_22_LVDS_DRF_BIST_CTRL0, _BIT5, _BIT5) == _TRUE)
        {
            // Toggle drf_test_resume
            ScalerSetBit(P39_22_LVDS_DRF_BIST_CTRL0, ~_BIT6, _BIT6);
            ScalerSetBit(P39_22_LVDS_DRF_BIST_CTRL0, ~_BIT6, 0x00);

            if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P39_22_LVDS_DRF_BIST_CTRL0, _BIT4, _BIT4) == _TRUE)
            {
                // BIST Fail
                if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT5) != 0x00)
                {
                    DebugMessageQC("5. LVDS Drf Bist No.5 Fail", 0x00);
                    ucBistResult |= _BIT0;
                }

                if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT4) != 0x00)
                {
                    DebugMessageQC("5. LVDS Drf Bist No.4 Fail", 0x00);
                    ucBistResult |= _BIT0;
                }

                if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT3) != 0x00)
                {
                    DebugMessageQC("5. LVDS Drf Bist No.3 Fail", 0x00);
                    ucBistResult |= _BIT0;
                }

                if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT2) != 0x00)
                {
                    DebugMessageQC("5. LVDS Drf Bist No.2 Fail", 0x00);
                    ucBistResult |= _BIT0;
                }

                if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT1) != 0x00)
                {
                    DebugMessageQC("5. LVDS Drf Bist No.1 Fail", 0x00);
                    ucBistResult |= _BIT0;
                }

                if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT0) != 0x00)
                {
                    DebugMessageQC("5. LVDS Drf Bist No.0 Fail", 0x00);
                    ucBistResult |= _BIT0;
                }
            }
            else
            {
                DebugMessageQC("5. LVDS Drf Bist Time Out Fail: 2", 0x00);
                ucBistResult |= _BIT1;
            }
        }
        else
        {
            DebugMessageQC("5. LVDS Drf Bist Time Out Fail: 1", 0x00);
            ucBistResult |= _BIT1;
        }
    }
    else
    {
        DebugMessageQC("5. LVDS Drf Bist Time Out Fail: 0", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P39_22_LVDS_DRF_BIST_CTRL0, ~_BIT7, 0x00);

    // Disable LVDS Bist Clk
    ScalerSetBit(P39_24_LVDS_DRF_BIST_CTRL2, ~_BIT6, 0x00);

    DebugMessageQC("5. ====LVDS Drf Bist Test End", 0x00);

    // Test Vbyone Table SRAM
    DebugMessageQC("5. ====VBO Bist Test Start", 0x00);

    // Pop up the VBO Phy Setting
    ucDSPCTemp[0] = ScalerGetByte(P38_D5_DPTX_CMU5);
    ucDSPCTemp[1] = ScalerGetByte(P38_D2_DPTX_CMU2);
    ucDSPCTemp[2] = ScalerGetByte(P38_D0_DPTX_CMU0);
    ucDSPCTemp[3] = ScalerGetByte(P38_C3_DPTX_CKRDDUTY_SPD_SEL1);
    ucDSPCTemp[4] = ScalerGetByte(P38_D1_DPTX_CMU1);
    ucDSPCTemp[5] = ScalerGetByte(P38_DD_DPTX_CMU13);
    ucDSPCTemp[6] = ScalerGetByte(P38_DE_DPTX_CMU14);
    ucDSPCTemp[7] = ScalerGetByte(P38_DC_DPTX_CMU12);
    ucDSPCTemp[8] = ScalerGetByte(P38_A0_DPTX_PHY_CTRL0);
    ucDSPCTemp[9] = ScalerGetByte(P38_09_TRANSMIT_CONTROL_H2);

    ScalerBurstWrite(tQCVBO, sizeof(tQCVBO), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    ScalerTimerDelayXms(10);

    // Test Vbyone BIST0
    ScalerSetBit(P38_19_VBY1_BIST_CON_0, ~_BIT0, _BIT0);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P38_19_VBY1_BIST_CON_0, _BIT3, _BIT3) == _TRUE)
    {
        // BIST0 Fail
        if(ScalerGetBit(P38_19_VBY1_BIST_CON_0, _BIT4) == _BIT4)
        {
            DebugMessageQC("5. VBO Bist0 SRAM Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. VBO Bist0 Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P38_19_VBY1_BIST_CON_0, ~_BIT0, 0x00);

    // Test Vbyone BIST1
    ScalerSetBit(P38_1A_VBY1_BIST_CON_1, ~_BIT0, _BIT0);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P38_1A_VBY1_BIST_CON_1, _BIT3, _BIT3) == _TRUE)
    {
        // BIST1 Fail
        if(ScalerGetBit(P38_1A_VBY1_BIST_CON_1, _BIT4) == _BIT4)
        {
            DebugMessageQC("5. VBO Bist1 SRAM Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }
    else
    {
        DebugMessageQC("5. VBO Bist1 Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P38_1A_VBY1_BIST_CON_1, ~_BIT0, 0x00);

    DebugMessageQC("5. ====VBO Bist Test End", 0x00);

    // Vbo Bist Software Reset
    ScalerSetBit(P39_18_LVDS_RSV0_CTRL1, ~_BIT7, 0x00);
    ScalerSetBit(P39_18_LVDS_RSV0_CTRL1, ~_BIT7, _BIT7);

    DebugMessageQC("5. ====VBO DRF Bist Test Start", 0x00);

    // Test Vbyone DRF BIST0
    ScalerSetBit(P38_19_VBY1_BIST_CON_0, ~_BIT1, _BIT1);
    if(ScalerTimerPollingFlagProc(10, P38_19_VBY1_BIST_CON_0, _BIT7, _BIT7) == _TRUE)
    {
        // Toggle drf_resume
        ScalerSetBit(P38_19_VBY1_BIST_CON_0, ~_BIT2, 0x00);
        ScalerSetBit(P38_19_VBY1_BIST_CON_0, ~_BIT2, _BIT2);

        if(ScalerTimerPollingFlagProc(10, P38_19_VBY1_BIST_CON_0, _BIT7, _BIT7) == _TRUE)
        {
            // Toggle drf_resume
            ScalerSetBit(P38_19_VBY1_BIST_CON_0, ~_BIT2, 0x00);
            ScalerSetBit(P38_19_VBY1_BIST_CON_0, ~_BIT2, _BIT2);

            if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P38_19_VBY1_BIST_CON_0, _BIT5, _BIT5) == _TRUE)
            {
                // DRF BIST0 Fail
                if(ScalerGetBit(P38_19_VBY1_BIST_CON_0, _BIT6) == _BIT6)
                {
                    DebugMessageQC("5. VBO Drf Bist0 SRAM Fail", 0x00);
                    ucBistResult |= _BIT0;
                }
            }
            else
            {
                DebugMessageQC("5. VBO Drf Bist0 Time Out Fail: 2", 0x00);
                ucBistResult |= _BIT1;
            }
        }
        else
        {
            DebugMessageQC("5. VBO Drf Bist0 Time Out Fail: 1", 0x00);
            ucBistResult |= _BIT1;
        }
    }
    else
    {
        DebugMessageQC("5. VBO Drf Bist0 Time Out Fail: 0", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P38_19_VBY1_BIST_CON_0, ~_BIT1, 0x00);

    // Test Vbyone DRF BIST1
    ScalerSetBit(P38_1A_VBY1_BIST_CON_1, ~_BIT1, _BIT1);
    if(ScalerTimerPollingFlagProc(10, P38_1A_VBY1_BIST_CON_1, _BIT7, _BIT7) == _TRUE)
    {
        // Toggle drf_resume
        ScalerSetBit(P38_1A_VBY1_BIST_CON_1, ~_BIT2, 0x00);
        ScalerSetBit(P38_1A_VBY1_BIST_CON_1, ~_BIT2, _BIT2);

        if(ScalerTimerPollingFlagProc(10, P38_1A_VBY1_BIST_CON_1, _BIT7, _BIT7) == _TRUE)
        {
            // Toggle drf_resume
            ScalerSetBit(P38_1A_VBY1_BIST_CON_1, ~_BIT2, 0x00);
            ScalerSetBit(P38_1A_VBY1_BIST_CON_1, ~_BIT2, _BIT2);

            if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P38_1A_VBY1_BIST_CON_1, _BIT5, _BIT5) == _TRUE)
            {
                // DRF BIST1 Fail
                if(ScalerGetBit(P38_1A_VBY1_BIST_CON_1, _BIT6) == _BIT6)
                {
                    DebugMessageQC("5. VBO Drf Bist1 SRAM Fail", 0x00);
                    ucBistResult |= _BIT0;
                }
            }
            else
            {
                DebugMessageQC("5. VBO Drf Bist1 Time Out Fail: 2", 0x00);
                ucBistResult |= _BIT1;
            }
        }
        else
        {
            DebugMessageQC("5. VBO Drf Bist1 Time Out Fail: 1", 0x00);
            ucBistResult |= _BIT1;
        }
    }
    else
    {
        DebugMessageQC("5. VBO Drf Bist1 Time Out Fail: 0", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P38_1A_VBY1_BIST_CON_1, ~_BIT1, 0x00);
    DebugMessageQC("5. ====VBO DRF Bist Test End", 0x00);

    // Pop in the VBO Phy Setting
    ScalerSetByte(P38_D5_DPTX_CMU5, ucDSPCTemp[0]);
    ScalerSetByte(P38_D2_DPTX_CMU2, ucDSPCTemp[1]);
    ScalerSetByte(P38_D0_DPTX_CMU0, ucDSPCTemp[2]);
    ScalerSetByte(P38_C3_DPTX_CKRDDUTY_SPD_SEL1, ucDSPCTemp[3]);
    ScalerSetByte(P38_D1_DPTX_CMU1, ucDSPCTemp[4]);
    ScalerSetByte(P38_DD_DPTX_CMU13, ucDSPCTemp[5]);
    ScalerSetByte(P38_DE_DPTX_CMU14, ucDSPCTemp[6]);
    ScalerSetByte(P38_DC_DPTX_CMU12, ucDSPCTemp[7]);
    ScalerSetByte(P38_A0_DPTX_PHY_CTRL0, ucDSPCTemp[8]);
    ScalerSetByte(P38_09_TRANSMIT_CONTROL_H2, ucDSPCTemp[9]);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. Display Conversion Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. Display Conversion Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. Display Conversion Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

#if(_QC_4P_MODE_ == _ON)
//--------------------------------------------------
// Description  : Test MP All Memory BIST
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQC4PBistTest(void)
{
    BYTE ucBistResult = 0;

    DebugMessageQC("5. 4P Bist Test Start", 0x00);

// FormatConv BIST
    ucBistResult = ucBistResult | (BYTE)ScalerQC4PFormatConvBistTest();
// Scaling Down BIST
    ucBistResult = ucBistResult | ((BYTE)ScalerQC4PSDBistTest() << 1);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ScaleDown S1 & S2 Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ScaleDown S1 & S2 Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. ScaleDown S1 & S2 Bist FAIL", 0x00);
    }
    ucBistResult = 0x00;

    DebugMessageQC("6. 4P Bist Test Done", 0x00);
    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : FormatConv 4P BIST Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQC4PFormatConvBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    DebugMessageQC("5. ====FormatConv Sub Bist Test Start", 0x00);
    ScalerSetBit(P31_2F_EVEN_ODD_BIST_CTRL_SUB, ~(_BIT7 | _BIT1), _BIT7 | _BIT1);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_2F_EVEN_ODD_BIST_CTRL_SUB, _BIT6, _TRUE) == _TRUE)
    {
        if(ScalerGetBit(P31_2F_EVEN_ODD_BIST_CTRL_SUB, _BIT5) != 0x00)
        {
            DebugMessageQC("5. FormatConv Sub bist_result_3 Fail", 0x00);
            ucBistResult |= _BIT7;
        }

        if(ScalerGetBit(P31_2F_EVEN_ODD_BIST_CTRL_SUB, _BIT4) != 0x00)
        {
            DebugMessageQC("5. FormatConv Sub bist_result_2 Fail", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetBit(P31_2F_EVEN_ODD_BIST_CTRL_SUB, _BIT3) != 0x00)
        {
            DebugMessageQC("5. FormatConv Sub bist_result_1 Fail", 0x00);
            ucBistResult |= _BIT5;
        }

        if(ScalerGetBit(P31_2F_EVEN_ODD_BIST_CTRL_SUB, _BIT2) != 0x00)
        {
            DebugMessageQC("5. FormatConv Sub bist_result_0 Fail", 0x00);
            ucBistResult |= _BIT4;
        }

    }
    else
    {
        DebugMessageQC("5. FormatConv Sub Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT0;
    }

    ScalerSetBit(P31_2F_EVEN_ODD_BIST_CTRL_SUB, ~_BIT7, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. FormatConv Sub Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. FormatConv Sub Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

//-----------FormatConv DRF BIST---------------//

    DebugMessageQC("5. ====FormatConv Sub DRF Bist Test Start", 0x00);
    ScalerSetBit(P31_2F_EVEN_ODD_BIST_CTRL_SUB, ~_BIT0, _BIT0);
    ScalerSetBit(P31_2F_EVEN_ODD_BIST_CTRL_SUB, ~_BIT0, 0x00);
    //1.Start DRF BIST mode
    ScalerSetBit(P31_30_EVEN_ODD_DRF_BIST_CTRL_SUB, ~(_BIT7 | _BIT6), _BIT7);

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_30_EVEN_ODD_DRF_BIST_CTRL_SUB, _BIT5, _TRUE) == _TRUE)
        {
             //3.Wait 1ms
            ScalerTimerDelayXms(2);
            ScalerSetBit(P31_30_EVEN_ODD_DRF_BIST_CTRL_SUB, ~_BIT6, _BIT6);
            ScalerSetBit(P31_30_EVEN_ODD_DRF_BIST_CTRL_SUB, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. FormatConv Sub DRF Bist Time Out Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_30_EVEN_ODD_DRF_BIST_CTRL_SUB, _BIT4, _TRUE) == _TRUE)
    {
        if(ScalerGetBit(P31_30_EVEN_ODD_DRF_BIST_CTRL_SUB, _BIT3) != 0x00)
        {
            DebugMessageQC("5. FormatConv Sub DRF bist_result_3 Fail", 0x00);
            ucBistResult |= (_BIT7 | _BIT1);
        }

        if(ScalerGetBit(P31_30_EVEN_ODD_DRF_BIST_CTRL_SUB, _BIT2) != 0x00)
        {
            DebugMessageQC("5. FormatConv Sub DRF bist_result_2 Fail", 0x00);
            ucBistResult |= (_BIT6 | _BIT1);
        }

        if(ScalerGetBit(P31_30_EVEN_ODD_DRF_BIST_CTRL_SUB, _BIT1) != 0x00)
        {
            DebugMessageQC("5. FormatConv Sub DRF bist_result_1 Fail", 0x00);
            ucBistResult |= (_BIT5 | _BIT1);
        }

        if(ScalerGetBit(P31_30_EVEN_ODD_DRF_BIST_CTRL_SUB, _BIT0) != 0x00)
        {
            DebugMessageQC("5. FormatConv Sub DRF bist_result_0 Fail", 0x00);
            ucBistResult |= (_BIT4 | _BIT1);
        }
    }
    else
    {
        DebugMessageQC("5. FormatConv Sub DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }

    // Disable  bist test
    ScalerSetBit(P31_30_EVEN_ODD_DRF_BIST_CTRL_SUB, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P31_2F_EVEN_ODD_BIST_CTRL_SUB, ~_BIT1, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. FormatConv Sub DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. FormatConv Sub DRF Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : Scaling Down 4P BIST Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQC4PSDBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    DebugMessageQC("5. 4P Bist Test Start", 0x00);

    //Test ScaleDown S1 Bist Mode
    DebugMessageQC("5. ====ScaleDown S1 Bist Test Start", 0x00);
    ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_51_SD_BIST_CTRL1_S1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_50_SD_BIST_CTRL0_S1, ~_BIT5, _BIT5);
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_50_SD_BIST_CTRL0_S1, _BIT7, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_50_SD_BIST_CTRL0_S1, _BIT6) != 0x00)
        {
            DebugMessageQC("5. ScaleDown S1 Linebuffer0 Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        };

        if(ScalerGetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_51_SD_BIST_CTRL1_S1, _BIT7) != 0x00)
        {
            DebugMessageQC("5. ScaleDown S1 Linebuffer1 Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }
    else
    {
        DebugMessageQC("5. ScaleDown S1 Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT5;
    }
    //disable ScaleDown S1 bist test
    ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_50_SD_BIST_CTRL0_S1, ~_BIT5, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ScaleDown S1 Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ScaleDown S1 Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. ScaleDown S1 Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_51_SD_BIST_CTRL1_S1, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_51_SD_BIST_CTRL1_S1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    DebugMessageQC("5. ====ScaleDown S1 DRF Bist Test Start", 0x00);
    //1.Start DRF BIST mode
    ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_50_SD_BIST_CTRL0_S1, ~_BIT2, _BIT2);

    //2.Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_50_SD_BIST_CTRL0_S1, _BIT1, _TRUE) == _TRUE)
        {
            //3.Wait 1ms
            ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_50_SD_BIST_CTRL0_S1, ~_BIT0, _BIT0);
            ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_50_SD_BIST_CTRL0_S1, ~_BIT0, 0x00);
        }
        else
        {
            DebugMessageQC("5. ScaleDown S1 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    //8.Wait DRF Bist Done
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_50_SD_BIST_CTRL0_S1, _BIT4, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_50_SD_BIST_CTRL0_S1, _BIT3) != 0x00)
        {
            DebugMessageQC("5. ScaleDown S1 Linebuffer0 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_51_SD_BIST_CTRL1_S1, _BIT6) != 0x00)
        {
            DebugMessageQC("5. ScaleDown S1 Linebuffer1 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT5;
        }
    }
    else
    {
        DebugMessageQC("5. ScaleDown S1 Linebuffer1 DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT4;
    }

    // Disable ScaleDown S1 DRF bist test
    ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_50_SD_BIST_CTRL0_S1, ~(_BIT2 | _BIT0), 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ScaleDown S1 DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ScaleDown S1 DRF Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. ScaleDown S1 DRF Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    // Test ScaleDown S2 Bist Mode
    DebugMessageQC("5. ====ScaleDown S2 Bist Test Start", 0x00);
    ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_51_SD_BIST_CTRL1_S2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_50_SD_BIST_CTRL0_S2, ~_BIT5, _BIT5);
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_50_SD_BIST_CTRL0_S2, _BIT7, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_50_SD_BIST_CTRL0_S2, _BIT6) != 0x00)
        {
            DebugMessageQC("5. ScaleDown S2 Linebuffer0 Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        };

        if(ScalerGetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_51_SD_BIST_CTRL1_S2, _BIT7) != 0x00)
        {
            DebugMessageQC("5. ScaleDown S2 Linebuffer1 Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }
    else
    {
        DebugMessageQC("5. ScaleDown S2 Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT5;
    }
    //disable ScaleDown S2 bist test
    ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_50_SD_BIST_CTRL0_S2, ~_BIT5, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ScaleDown S2 Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ScaleDown S2 Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. ScaleDown S2 Bist FAIL", 0x00);
        return _TEST_FAIL;
    }

    ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_51_SD_BIST_CTRL1_S2, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_51_SD_BIST_CTRL1_S2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    DebugMessageQC("5. ====ScaleDown S2 DRF Bist Test Start", 0x00);
    //1.Start DRF BIST mode
    ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_50_SD_BIST_CTRL0_S2, ~_BIT2, _BIT2);

    //2.Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_50_SD_BIST_CTRL0_S2, _BIT1, _TRUE) == _TRUE)
        {
            //3.Wait 1ms
            ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_50_SD_BIST_CTRL0_S2, ~_BIT0, _BIT0);
            ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_50_SD_BIST_CTRL0_S2, ~_BIT0, 0x00);
        }
        else
        {
            DebugMessageQC("5. ScaleDown S2 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    //8.Wait DRF Bist Done
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_50_SD_BIST_CTRL0_S2, _BIT4, _TRUE) == _TRUE)
    {
        if(ScalerGetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_50_SD_BIST_CTRL0_S2, _BIT3) != 0x00)
        {
            DebugMessageQC("5. ScaleDown S2 Linebuffer0 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT6;
        }

        if(ScalerGetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_51_SD_BIST_CTRL1_S2, _BIT6) != 0x00)
        {
            DebugMessageQC("5. ScaleDown S2 Linebuffer1 DRF Bist Fail", 0x00);
            ucBistResult |= _BIT5;
        }
    }
    else
    {
        DebugMessageQC("5. ScaleDown S2 Linebuffer1 DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT4;
    }

    // Disable ScaleDown M2 DRF bist test
    ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_50_SD_BIST_CTRL0_S2, ~(_BIT2 | _BIT0), 0x00);


    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ScaleDown S2 DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ScaleDown S2 DRF Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. ScaleDown S2 DRF Bist FAIL", 0x00);
        return _TEST_FAIL;
    }


    DebugMessageQC("6. 4P Bist Test Done", 0x00);
    return _TEST_PASS;
}

#endif // End of #if(_QC_4P_MODE_ == _ON)

#endif // End of #if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
bit ScalerQC420D2BistTest()
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    DebugMessageQC("5. ====D2 420to422 Bist Test Start", 0x00);
    ScalerSetBit(P31_3A_BIST_D2_YUV420TO422, ~_BIT7, _BIT7);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_3A_BIST_D2_YUV420TO422, _BIT6, _TRUE) == _TRUE)
    {
        if(ScalerGetBit(P31_3A_BIST_D2_YUV420TO422, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. D2 420to422 Bist Fail", (ScalerGetByte(P31_3A_BIST_D2_YUV420TO422) & 0x3F));
            ucBistResult |= (ScalerGetByte(P31_3A_BIST_D2_YUV420TO422) & 0x3F);
        }
    }
    else
    {
        DebugMessageQC("5. D2 420to422 Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT7;
    }
    // Disable D2 420to422 bist test
    ScalerSetBit(P31_3A_BIST_D2_YUV420TO422, ~_BIT7, 0x00);

    // Reset Bist
    ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT3, _BIT3);
    ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT3, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. D2 420to422 Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. D2 420to422 Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

//------------DRF BIST---------------//

    DebugMessageQC("5. ====D2 420to422 DRF Bist Test Start", 0x00);

    //1.Start DRF BIST mode
    ScalerSetBit(P31_3B_DRF_BIST_D2_YUV420TO422, ~_BIT7, _BIT7);

    //2.Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_3E_DRF_BIST_D2D3_YUV420TO422, _BIT6, _TRUE) == _TRUE)
        {
            //3.Wait 1ms
            //ScalerTimerDelayXms(2);
            ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT7, _BIT7);
            ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT7, 0x00);
        }
        else
        {
            DebugMessageQC("5. D2 420to422 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    //8.Wait DRF Bist Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_3B_DRF_BIST_D2_YUV420TO422, _BIT6, _TRUE) == _TRUE)
    {
        if(ScalerGetBit(P31_3B_DRF_BIST_D2_YUV420TO422, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. D2 420to422 DRF Bist Fail", (ScalerGetByte(P31_3B_DRF_BIST_D2_YUV420TO422) & 0x3F));
            ucBistResult |= (ScalerGetByte(P31_3B_DRF_BIST_D2_YUV420TO422) & 0x3F);
        }
    }
    else
    {
        DebugMessageQC("5. D2 420to422 DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT6;
    }

    // Disable ADCNR bist test
    ScalerSetBit(P31_3B_DRF_BIST_D2_YUV420TO422, ~_BIT7, 0x00);

    // Reset Bist
    ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT3, _BIT3);
    ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT3, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. D2 420to422 DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. D2 420to422 DRF Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
bit ScalerQC420D3BistTest()
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    DebugMessageQC("5. ====D3 420to422 Bist Test Start", 0x00);
    ScalerSetBit(P31_3C_BIST_D3_YUV420TO422, ~_BIT7, _BIT7);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_3C_BIST_D3_YUV420TO422, _BIT6, _TRUE) == _TRUE)
    {
        if(ScalerGetBit(P31_3C_BIST_D3_YUV420TO422, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. D3 420to422 Bist Fail", (ScalerGetByte(P31_3C_BIST_D3_YUV420TO422) & 0x3F));
            ucBistResult |= (ScalerGetByte(P31_3C_BIST_D3_YUV420TO422) & 0x3F);
        }
    }
    else
    {
        DebugMessageQC("5. D3 420to422 Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT7;
    }
    // Disable D3 420to422 bist test
    ScalerSetBit(P31_3C_BIST_D3_YUV420TO422, ~_BIT7, 0x00);

    // Reset Bist
    ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT2, _BIT2);
    ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT2, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. D3 420to422 Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. D3 420to422 Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

//------------DRF BIST---------------//

    DebugMessageQC("5. ====D3 420to422 DRF Bist Test Start", 0x00);

    //1.Start DRF BIST mode
    ScalerSetBit(P31_3D_DRF_BIST_D3_YUV420TO422, ~_BIT7, _BIT7);

    //2.Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_3E_DRF_BIST_D2D3_YUV420TO422, _BIT4, _TRUE) == _TRUE)
        {
            //3.Wait 1ms
            //ScalerTimerDelayXms(2);
            ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT5, _BIT5);
            ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT5, 0x00);
        }
        else
        {
            DebugMessageQC("5. D3 420to422 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    //8.Wait DRF Bist Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P31_3D_DRF_BIST_D3_YUV420TO422, _BIT6, _TRUE) == _TRUE)
    {
        if(ScalerGetBit(P31_3D_DRF_BIST_D3_YUV420TO422, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. D3 420to422 DRF Bist Fail", (ScalerGetByte(P31_3D_DRF_BIST_D3_YUV420TO422) & 0x3F));
            ucBistResult |= (ScalerGetByte(P31_3D_DRF_BIST_D3_YUV420TO422) & 0x3F);
        }
    }
    else
    {
        DebugMessageQC("5. D3 420to422 DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT6;
    }

    // Disable ADCNR bist test
    ScalerSetBit(P31_3D_DRF_BIST_D3_YUV420TO422, ~_BIT7, 0x00);

    // Reset Bist
    ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT2, _BIT2);
    ScalerSetBit(P31_3E_DRF_BIST_D2D3_YUV420TO422, ~_BIT2, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. D3 420to422 DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. D3 420to422 DRF Bist FAIL", ucBistResult);
        return _TEST_FAIL;
    }

    return _TEST_PASS;
}
#endif
//----------------------------------------------------------------------
// Description  : Polling Scaler Flag Process
// Input Value  : ucTimeout --> Timeout number (Max: 255 ms)
//                usPortAddress--> Current Port Address
//                ucRegister--> Current Port Register
//                ucBit     --> Polling Bit
//                bSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------
bit ScalerQCTimerPollingPortFlagProc(WORD usTimeout, WORD usPortAddress, WORD usRegister, BYTE ucBit, bit bSuccess)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;

    usPreviousTime = g_usTimerCounter;

    do
    {
        if(((bit)ScalerGetDataPortBit(usPortAddress, usRegister, ucBit) ^ bSuccess) == _FALSE)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }while(usTimeElapsed <= usTimeout);

    return _FALSE;
}

#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)
