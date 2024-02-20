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
// ID Code      : RL6432_Series_QC_BIST.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6432_SERIES_QC_BIST__

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


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
bit ScalerQCBistTest(void);
bit ScalerQCADCNRBistTest(void);
bit ScalerQCSDBistTest(void);
bit ScalerQCDTGBistTest(void);
bit ScalerQCSHPBistTest(void);
bit ScalerQCDCCBistTest(void);
bit ScalerQCRGBGammaBistTest(void);
bit ScalerQCGammaBistTest(void);
bit ScalerQC3DGammaBistTest(void);
bit ScalerQCPanelUniformityBistTest(void);
bit ScalerQCODBistTest(void);
bit ScalerQCOSDBistTest(void);
bit ScalerQCDSPCBistTest(void);
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
bit ScalerQCBistTest_D0(void);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
bit ScalerQCBistTest_D1(void);
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
    BYTE ucCnt = 0;

    DebugMessageQC("5. Bist Test Start", 0x00);

// ADCNR BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCADCNRBistTest() << 0));

// Scaling Down BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCSDBistTest() << 1));

// DisplayTimingGen BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCDTGBistTest() << 2));

// Sharpness BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCSHPBistTest() << 3));

// DCC
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCDCCBistTest() << 4));

// RGB Gamma BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCRGBGammaBistTest() << 5));

// Gamma BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCGammaBistTest() << 6));

// 3D Gamma BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQC3DGammaBistTest() << 7));

// Panel Uniformity
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCPanelUniformityBistTest() << 0));

// Live Show (OD)
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCODBistTest() << 1));

// OSD
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCOSDBistTest() << 2));

// DSPC BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCDSPCBistTest() << 7));

    return ucBistResult;
}
#endif

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
    ScalerSetBit(P33_2A_BIST_CTRL, ~_BIT3, 0x00);
    ScalerTimerDelayXms(2);

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
    ScalerSetBit(P33_2A_BIST_CTRL, ~_BIT5, _BIT5);

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
// Description  : Scaling Down BIST
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
    ScalerTimerDelayXms(2);

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
    ScalerTimerDelayXms(2);

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

    // Disable BIST Clock and Disable BIST Mode
    ScalerSetBit(P12_A2_SR_SHP_BIST_CTRL_0, ~(_BIT6 | _BIT3), 0x00);

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
    ScalerTimerDelayXms(2);

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

    // Disable BIST Clock and Disable DRF BIST Mode
    ScalerSetBit(P12_A2_SR_SHP_BIST_CTRL_0, ~_BIT6, 0x00);
    ScalerSetBit(P12_E7_SR_SHP_BIST_CTRL_1, ~_BIT3, 0x00);

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
    ScalerTimerDelayXms(2);

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

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_11_RGB_GAMMA_BIST_CTRL0_M1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_11_RGB_GAMMA_BIST_CTRL0_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. RGB Gamma M1 SetA Bist Even Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }

    // Disable BIST Clock and Disable BIST Mode
    ScalerSetBit(P9_10_RGB_GAMMA_CLK_M1, ~_BIT0, 0x00);
    ScalerSetBit(P9_11_RGB_GAMMA_BIST_CTRL0_M1, ~_BIT7, 0x00);

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
    ScalerTimerDelayXms(2);

    // Enable DRF BIST Mode
    ScalerSetBit(P9_12_RGB_GAMMA_BIST_CTRL1_M1, ~_BIT7, _BIT7);

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

    // Disable BIST Clock and Disable DRF BIST Mode
    ScalerSetBit(P9_10_RGB_GAMMA_CLK_M1, ~_BIT1, 0x00);
    ScalerSetBit(P9_12_RGB_GAMMA_BIST_CTRL1_M1, ~_BIT7, 0x00);

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
// Output Value : None
//--------------------------------------------------
bit ScalerQCGammaBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    // Test Gamma M1/M2 Bist Mode
    DebugMessageQC("5. ====Gamma Bist Test Start", 0x00);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P9_00_GAMMA_BIST_SET_M1, ~_BIT1, 0x00);
    ScalerSetBit(P9_00_GAMMA_BIST_SET_M1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(P9_01_GAMMA_BIST_CTRL0_M1, ~_BIT7, _BIT7);


    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_01_GAMMA_BIST_CTRL0_M1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_01_GAMMA_BIST_CTRL0_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma M1 SetA Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }

	ScalerSetBit(P9_01_GAMMA_BIST_CTRL0_M1, ~_BIT7, 0x00);

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
    DebugMessageQC("5. ====Gamma DRF Bist Test Start", 0x00);


    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P9_00_GAMMA_BIST_SET_M1, ~_BIT1, 0x00);
    ScalerSetBit(P9_00_GAMMA_BIST_SET_M1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerTimerDelayXms(2);

    // Enable DRF BIST Mode
    ScalerSetBit(P9_02_GAMMA_BIST_CTRL1_M1, ~_BIT7, _BIT7);


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
            DebugMessageQC("5. Gamma DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_02_GAMMA_BIST_CTRL1_M1, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P9_03_GAMMA_BIST_CTRL2_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma DRF Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    else
    {
        DebugMessageQC("5. Gamma DRF Bist Start Pause Time Out Fail", 0x00);
        ucBistResult |= _BIT7;
    }


    ScalerSetBit(P9_02_GAMMA_BIST_CTRL1_M1, ~_BIT7, 0x00);
    ScalerSetByte(P9_00_GAMMA_BIST_SET_M1, 0x00);

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
// Description  : Gamma Bist
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQC3DGammaBistTest(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    // Test Gamma M1/M2 Bist Mode
    DebugMessageQC("5. ====3D Gamma Bist Test Start", 0x00);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~_BIT1, 0x00);
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_B5_RGB_3D_GAMMA_BIST_CTRL_MAIN1_2, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        }

    }

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_B5_RGB_3D_GAMMA_BIST_CTRL_MAIN1_2, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P9_B5_RGB_3D_GAMMA_BIST_CTRL_MAIN1_2, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
        {
            DebugMessageQC("5. 3D Gamma Bist Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }

    // Disable BIST Clock and Disable BIST Mode
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~_BIT0, 0x00);
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~_BIT7, 0x00);
    ScalerSetBit(P9_B5_RGB_3D_GAMMA_BIST_CTRL_MAIN1_2, ~_BIT7, 0x00);

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
    DebugMessageQC("5. ====3D Gamma DRF Bist Test Start", 0x00);

    // Enable BIST Clock, Reset BIST, and Enable BIST Mode
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~_BIT1, 0x00);
    ScalerSetBit(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerTimerDelayXms(2);

    // Enable DRF BIST Mode
    ScalerSetBit(P9_B8_RGB_3D_GAMMA_DRF_BIST_MAIN1_1, ~_BIT7, _BIT7);
    ScalerSetBit(P9_B9_RGB_3D_GAMMA_DRF_BIST_MAIN1_2, ~_BIT7, _BIT7);

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
            DebugMessageQC("5. Gamma DRF Bist Start Pause Time Out Fail", 0x00);
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
    }
    else
    {
            DebugMessageQC("5. 3D Gamma M1 DRF Bist Start Pause Time Out Fail", 0x00);
			ucBistResult |= _BIT7;
    }

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_B9_RGB_3D_GAMMA_DRF_BIST_MAIN1_2, _BIT5, _BIT5) == _TRUE)
        {
            // Wait 1ms
            ScalerTimerDelayXms(1);
            ScalerSetBit(P9_B9_RGB_3D_GAMMA_DRF_BIST_MAIN1_2, ~_BIT6, 0x00);
            ScalerSetBit(P9_B9_RGB_3D_GAMMA_DRF_BIST_MAIN1_2, ~_BIT6, _BIT6);
            ScalerSetBit(P9_B9_RGB_3D_GAMMA_DRF_BIST_MAIN1_2, ~_BIT6, 0x00);
        }
        else
        {
            DebugMessageQC("5. 3D Gamma M2 DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT6;
        }
    }

    // Wait DRF BIST Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9_B9_RGB_3D_GAMMA_DRF_BIST_MAIN1_2, _BIT4, _BIT4) == _TRUE)
    {
        if(ScalerGetBit(P9_B9_RGB_3D_GAMMA_DRF_BIST_MAIN1_2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
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


    ScalerSetByte(P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1, 0x00);
    ScalerSetBit(P9_B8_RGB_3D_GAMMA_DRF_BIST_MAIN1_1, ~_BIT7, 0x00);
    ScalerSetBit(P9_B9_RGB_3D_GAMMA_DRF_BIST_MAIN1_2, ~_BIT7, 0x00);

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

    // Test Panel Uniformity Gain LUT BIST
    ScalerSetBit(P34_09_UN_SRAM_BIST, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(P34_09_UN_SRAM_BIST, ~_BIT3, 0x00);
    ScalerSetBit(P34_09_UN_SRAM_BIST, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P34_09_UN_SRAM_BIST, _BIT6, _BIT6) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(P34_09_UN_SRAM_BIST, _BIT5) != 0x00)
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
        if(ScalerGetBit(P34_10_UN_OFFSET_SRAM_BIST, _BIT5) != 0x00)
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

    // Test Panel Uniformity Gain LUT DRF BIST
    ScalerSetBit(P34_09_UN_SRAM_BIST, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(P34_09_UN_SRAM_BIST, ~_BIT3, 0x00);
    ScalerTimerDelayXms(2);

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
        if(ScalerGetBit(P34_0A_UN_SRAM_DRF_BIST, _BIT2) != 0x00)
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
        if(ScalerGetBit(P34_11_UN_OFFSET_SRAM_DRF_BIST, _BIT2) != 0x00)
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
// Description  : LiveShow(OD) BIST
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCODBistTest(void)
{
    BYTE ucBistResult = 0;

    DebugMessageQC("5. ====OD Bist Test Start", 0x00);

    // Test M1 OD Capture SRAM
    ScalerSetBit(P3_CA_CAP_BIST_CTRL0, ~_BIT7, _BIT7);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P3_CA_CAP_BIST_CTRL0, _BIT6, _TRUE) == _TRUE)
    {
        // M1 Cap BIST No.0 Fail
        if(ScalerGetBit(P3_CB_CAP_BIST_CTRL1, _BIT7) != 0x00)
        {
            DebugMessageQC("5. OD M1 Cap Bist No.0 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        // M1 Cap BIST No.1 Fail
        if(ScalerGetBit(P3_CB_CAP_BIST_CTRL1, _BIT6) != 0x00)
        {
            DebugMessageQC("5. OD M1 Cap Bist No.0 Fail", 0x00);
            ucBistResult |= _BIT0;
        }

        if((ucBistResult & _BIT0) != _BIT0)
        {
            DebugMessageQC("5. OD M1 Cap Bist Pass", 0x00);
        }
    }
    else
    {
        DebugMessageQC("5. OD M1 Cap Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }
    ScalerSetBit(P3_CA_CAP_BIST_CTRL0, ~_BIT7, 0x00);

    // Test M1 OD Display SRAM
    ScalerSetBit(P3_CD_DIS_BIST_CTRL0, ~_BIT7, _BIT7);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P3_CD_DIS_BIST_CTRL0, _BIT6, _TRUE) == _TRUE)
    {
        // M1 Dis BIST No.0 Fail
        if(ScalerGetBit(P3_CE_DIS_BIST_CTRL1, _BIT7) != 0x00)
        {
            DebugMessageQC("5. OD M1 Dis Bist No.0 Fail", 0x00);
            ucBistResult |= _BIT2;
        }

        // M1 Dis BIST No.1 Fail
        if(ScalerGetBit(P3_CE_DIS_BIST_CTRL1, _BIT6) != 0x00)
        {
            DebugMessageQC("5. OD M1 Dis Bist No.0 Fail", 0x00);
            ucBistResult |= _BIT2;
        }

        if((ucBistResult & _BIT2) != _BIT2)
        {
            DebugMessageQC("5. OD M1 Dis Bist Pass", 0x00);
        }
    }
    else
    {
        DebugMessageQC("5. OD M1 Dis Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT3;
    }
    ScalerSetBit(P3_CD_DIS_BIST_CTRL0, ~_BIT7, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. OD Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. OD Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. OD Bist FAIL", 0x00);

        return _TEST_FAIL;
    }

    return _TEST_PASS;
}

//--------------------------------------------------
// Description  : OSD BIST
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCOSDBistTest(void)
{
    BYTE ucBistResult0 = 0;
    BYTE ucCnt = 0;

    // Test OSD Table SRAM
    DebugMessageQC("5. ====OSD Bist Test Start", 0x00);

    // Enable OSD Bist Clk
    ScalerSetBit(P3A_90_OSD_LUT_BIST_CTRL, ~_BIT1, _BIT1);

    ScalerSetBit(P3A_90_OSD_LUT_BIST_CTRL, ~_BIT7, _BIT7);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P3A_90_OSD_LUT_BIST_CTRL, _BIT6, _BIT6) == _TRUE)
    {
        // OSD BIST Fail
        if(ScalerGetBit(P3A_90_OSD_LUT_BIST_CTRL, _BIT5) != 0x00)
        {
            DebugMessageQC("5. OSD Bist No.3 Fail", 0x00);
            ucBistResult0 |= _BIT0;
        }

        if(ScalerGetBit(P3A_90_OSD_LUT_BIST_CTRL, _BIT4) != 0x00)
        {
            DebugMessageQC("5. OSD Bist No.2 Fail", 0x00);
            ucBistResult0 |= _BIT0;
        }

        if(ScalerGetBit(P3A_90_OSD_LUT_BIST_CTRL, _BIT3) != 0x00)
        {
            DebugMessageQC("5. OSD Bist No.1 Fail", 0x00);
            ucBistResult0 |= _BIT0;
        }

        if(ScalerGetBit(P3A_90_OSD_LUT_BIST_CTRL, _BIT2) != 0x00)
        {
            DebugMessageQC("5. OSD Bist No.0 Fail", 0x00);
            ucBistResult0 |= _BIT0;
        }

        if((ucBistResult0 & _BIT0) != _BIT0)
        {
            DebugMessageQC("5. OSD Bist Pass", 0x00);
        }
    }
    else
    {
        DebugMessageQC("5. OSD Bist Time Out Fail", 0x00);
        ucBistResult0 |= _BIT1;
    }
    ScalerSetBit(P3A_90_OSD_LUT_BIST_CTRL, ~_BIT7, 0x00);

    DebugMessageQC("5. ====OSD Bist Test End", 0x00);

    // OSD Bist Software Reset
    ScalerSetBit(P3A_90_OSD_LUT_BIST_CTRL, ~_BIT0, 0x00);
    ScalerSetBit(P3A_90_OSD_LUT_BIST_CTRL, ~_BIT0, _BIT0);

    if(ucBistResult0 == 0x00)
    {
        DebugMessageQC("6. OSD Bist PASS", 0x00);

        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. OSD Bist Fail Mode", ucBistResult0);
        DebugMessageQC("6. OSD Bist FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : Display Cnversion BIST
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
bit ScalerQCDSPCBistTest(void)
{
    BYTE ucBistResult0 = 0;
    BYTE ucBistResult1 = 0;
    BYTE ucCnt = 0;

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
            ucBistResult0 |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT4) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.4 Fail", 0x00);
            ucBistResult0 |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT3) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.3 Fail", 0x00);
            ucBistResult0 |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT2) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.2 Fail", 0x00);
            ucBistResult0 |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT1) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.1 Fail", 0x00);
            ucBistResult0 |= _BIT0;
        }

        if(ScalerGetBit(P39_21_LVDS_BIST_CTRL, _BIT0) != 0x00)
        {
            DebugMessageQC("5. LVDS Bist No.0 Fail", 0x00);
            ucBistResult0 |= _BIT0;
        }

        if((ucBistResult0 & _BIT0) != _BIT0)
        {
            DebugMessageQC("5. LVDS Bist Pass", 0x00);
        }
    }
    else
    {
        DebugMessageQC("5. LVDS Bist Time Out Fail", 0x00);
        ucBistResult0 |= _BIT1;
    }
    ScalerSetBit(P39_21_LVDS_BIST_CTRL, ~_BIT7, 0x00);

    DebugMessageQC("5. ====LVDS Bist Test End", 0x00);

    // LVDS Bist Software Reset
    ScalerSetBit(P39_24_LVDS_DRF_BIST_CTRL2, ~_BIT7, 0x00);
    ScalerSetBit(P39_24_LVDS_DRF_BIST_CTRL2, ~_BIT7, _BIT7);
    ScalerTimerDelayXms(2);

    DebugMessageQC("5. ====LVDS DRF Bist Test Start", 0x00);

    ScalerSetBit(P39_22_LVDS_DRF_BIST_CTRL0, ~_BIT7, _BIT7);

    // Wait LVDS DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(10, P39_22_LVDS_DRF_BIST_CTRL0, _BIT5, _BIT5) == _TRUE)
        {
            // Toggle drf_test_resume
            ScalerSetBit(P39_22_LVDS_DRF_BIST_CTRL0, ~_BIT6, 0x00);
            ScalerSetBit(P39_22_LVDS_DRF_BIST_CTRL0, ~_BIT6, _BIT6);
        }
        else
        {
            DebugMessageQC("5. LVDS Drf Bist Time Out Fail: 0", 0x00);
            ucBistResult0 |= _BIT2;
        }
    }

    if((ucBistResult0 & _BIT2) != _BIT2)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P39_22_LVDS_DRF_BIST_CTRL0, _BIT4, _BIT4) == _TRUE)
        {
            // BIST Fail
            if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT5) != 0x00)
            {
                DebugMessageQC("5. LVDS Drf Bist No.5 Fail", 0x00);
                ucBistResult0 |= _BIT3;
            }

            if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT4) != 0x00)
            {
                DebugMessageQC("5. LVDS Drf Bist No.4 Fail", 0x00);
                ucBistResult0 |= _BIT3;
            }

            if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT3) != 0x00)
            {
                DebugMessageQC("5. LVDS Drf Bist No.3 Fail", 0x00);
                ucBistResult0 |= _BIT3;
            }

            if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT2) != 0x00)
            {
                DebugMessageQC("5. LVDS Drf Bist No.2 Fail", 0x00);
                ucBistResult0 |= _BIT3;
            }

            if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT1) != 0x00)
            {
                DebugMessageQC("5. LVDS Drf Bist No.1 Fail", 0x00);
                ucBistResult0 |= _BIT3;
            }

            if(ScalerGetBit(P39_23_LVDS_DRF_BIST_CTRL1, _BIT0) != 0x00)
            {
                DebugMessageQC("5. LVDS Drf Bist No.0 Fail", 0x00);
                ucBistResult0 |= _BIT3;
            }

            if((ucBistResult0 & _BIT3) != _BIT3)
            {
                DebugMessageQC("5. LVDS Drf Bist Pass", 0x00);
            }
        }
        else
        {
            DebugMessageQC("5. LVDS Drf Bist Time Out Fail: 2", 0x00);
            ucBistResult0 |= _BIT4;
        }
    }
    ScalerSetBit(P39_22_LVDS_DRF_BIST_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    // Disable LVDS Bist Clk
    ScalerSetBit(P39_24_LVDS_DRF_BIST_CTRL2, ~_BIT6, 0x00);

    DebugMessageQC("5. ====LVDS Drf Bist Test End", 0x00);


    // Test eDPTX Table SRAM
    DebugMessageQC("5. ====eDPTX Bist Test Start", 0x00);

    // Enable eDPTX Bist Clk
    ScalerSetBit(P9C_E2_PG_DRF_MBIST_CTRL, ~_BIT1, _BIT1);

    // Enable eDPTX Bist
    ScalerSetBit(P9C_E1_PG_MBIST_CTRL, ~_BIT7, _BIT7);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9C_E1_PG_MBIST_CTRL, _BIT6, _BIT6) == _TRUE)
    {
        // BIST Fail
        if(ScalerGetBit(P9C_E1_PG_MBIST_CTRL, _BIT5) != 0x00)
        {
            DebugMessageQC("5. eDPTX Bist Fail", 0x00);
            ucBistResult1 |= _BIT0;
        }
        else
        {
            DebugMessageQC("5. eDPTX Bist Pass", 0x00);
        }
    }
    else
    {
        DebugMessageQC("5. eDPTX Bist Time Out Fail", 0x00);
        ucBistResult1 |= _BIT1;
    }
    // Disable eDPTX Bist
    ScalerSetBit(P9C_E1_PG_MBIST_CTRL, ~_BIT7, 0x00);

    // eDPTX Bist Software Reset
    ScalerSetBit(P9C_E2_PG_DRF_MBIST_CTRL, ~_BIT0, _BIT0);
    ScalerSetBit(P9C_E2_PG_DRF_MBIST_CTRL, ~_BIT0, 0x00);
    ScalerTimerDelayXms(2);

    DebugMessageQC("5. ====eDPTX DRF Bist Test Start", 0x00);

    // Enable eDPTX Drf Bist
    ScalerSetBit(P9C_E2_PG_DRF_MBIST_CTRL, ~_BIT7, _BIT7);

    // Wait eDPTX DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9C_E2_PG_DRF_MBIST_CTRL, _BIT5, _BIT5) == _TRUE)
        {
            // Toggle drf_test_resume
            ScalerSetBit(P9C_E2_PG_DRF_MBIST_CTRL, ~_BIT6, _BIT6);
            ScalerTimerDelayXms(2);
            ScalerSetBit(P9C_E2_PG_DRF_MBIST_CTRL, ~_BIT6, 0x00);
            ScalerTimerDelayXms(2);
        }
        else
        {
            DebugMessageQC("5. eDPTX Drf Bist Time Out Fail: 0", 0x00);
            ucBistResult1 |= _BIT2;
        }
    }

    if((ucBistResult1 & _BIT2) != _BIT2)
    {
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P9C_E2_PG_DRF_MBIST_CTRL, _BIT4, _BIT4) == _TRUE)
        {
            // BIST Fail
            if(ScalerGetBit(P9C_E2_PG_DRF_MBIST_CTRL, _BIT3) != 0x00)
            {
                DebugMessageQC("5. eDPTX Drf Bist Fail", 0x00);
                ucBistResult1 |= _BIT3;
            }
            else
            {
                DebugMessageQC("5. eDPTX Drf Bist Pass", 0x00);
            }
        }
        else
        {
            DebugMessageQC("5. eDPTX Drf Bist Time Out Fail: 2", 0x00);
            ucBistResult1 |= _BIT4;
        }
    }

    // Disable eDPTX Drf Bist
    ScalerSetBit(P9C_E2_PG_DRF_MBIST_CTRL, ~(_BIT7 | _BIT6), 0x00);

    // Disalbe eDPTX Bist Clk
    ScalerSetBit(P9C_E2_PG_DRF_MBIST_CTRL, ~_BIT1, 0x00);

    if((ucBistResult0 | ucBistResult1) == 0x00)
    {
        DebugMessageQC("6. Display Conversion Bist PASS", 0x00);

        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Display Conversion Bist Fail Mode", (ucBistResult0 | ucBistResult1));
        DebugMessageQC("6. Display Conversion Bist FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : Test D0 Memory BIST
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
bit ScalerQCBistTest_D0(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

    return _TEST_PASS;
}
#endif

//--------------------------------------------------
// Description  : Test D1 Memory BIST
// Input Value  : None
// Output Value : TEST_PASS or TEST_FAIL
//--------------------------------------------------
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
bit ScalerQCBistTest_D1(void)
{
    BYTE ucBistResult = 0;
    BYTE ucCnt = 0;

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
