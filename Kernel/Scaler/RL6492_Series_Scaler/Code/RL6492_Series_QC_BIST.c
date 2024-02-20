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
// ID Code      : RL6492_Series_QC_BIST.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_QC_BIST__

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
bit ScalerQCDTGBistTest(void);
bit ScalerQCDCCBistTest(void);
bit ScalerQCRGBGammaBistTest(void);
bit ScalerQCGammaBistTest(void);
bit ScalerQC3DGammaBistTest(void);
bit ScalerQCDSPCBistTest(void);
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

    // DCC
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCDCCBistTest() << 1));

    // RGB Gamma BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCRGBGammaBistTest() << 2));

    // Gamma BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCGammaBistTest() << 3));

    // 3D Gamma BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQC3DGammaBistTest() << 4));

    // DisplayTimingGen BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCDTGBistTest() << 5));

    // DSPC BIST
    ucBistResult = (ucBistResult | ((BYTE)ScalerQCDSPCBistTest() << 6));

    return ucBistResult;

}
#endif

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
