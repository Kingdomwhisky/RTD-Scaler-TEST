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
// ID Code      : RL6369_Series_QC_BIST.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6369_SERIES_QC_BIST__

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

//------------ADCNR BIST---------------

    DebugMessageQC("5. ====ADCNR Bist Test Start", 0x00);
    ScalerSetBit(P33_2A_BIST_CTRL, ~_BIT6, _BIT6);
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
    //disable ADCNR bist test
    ScalerSetBit(P33_2A_BIST_CTRL, ~_BIT6, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. ADCNR Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. ADCNR Bist FAIL", ucBistResult);
    }
    ucBistResult = 0x00;

//------------DisplayTimingGen BIST---------------

//DisplayTimingGen Even  Bist Test

    DebugMessageQC("5. ====DisplayTimingGen Even Bist Test Start", 0x00);
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
            ucBistResult |= _BIT7;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT5) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even BIST Fail for SRAM No.1", 0x00);
            ucBistResult |= _BIT7;
        }

        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT4) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even BIST Fail for SRAM No.0", 0x00);
            ucBistResult |= _BIT7;
        }
    }
    else
    {
        DebugMessageQC("5. DisplayTimingGen Even Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT0;
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
    }
    ucBistResult = 0x00;

//------------GAMMA BIST---------------

//Gamma  Bist Test

    //ScalerColorOutputGammaEnable(_FUNCTION_OFF);
    DebugMessageQC("5. ====Gamma Bist Test Start", 0x00);

    // Normal Bist

    ScalerSetBit(P2F_01_GAMMA_BIST_CTRL0_M1, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P2F_01_GAMMA_BIST_CTRL0_M1, _BIT6, _BIT6) == _TRUE)
    {
        if(ScalerGetBit(P2F_01_GAMMA_BIST_CTRL0_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageQC("5. Gamma Normal Bist M1 Fail", 0x00);
            ucBistResult |= _BIT7;
        }
    }

    // turn off Normal BIST
    ScalerSetBit(P2F_01_GAMMA_BIST_CTRL0_M1, ~_BIT7, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. Gamma Normal Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. Gamma Normal Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. Gamma Normal Bist FAIL", 0x00);
    }

    // Test SDRAM Controller
    // IN1 BIST Test
    ScalerSetBit(P5_A1_IN1_FIFO_STATUS, ~_BIT5, _BIT5);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_A1_IN1_FIFO_STATUS, _BIT7, 0x00) == _TRUE)
    {
        if(ScalerGetBit(P5_A1_IN1_FIFO_STATUS, _BIT6) != _BIT6)
        {
            DebugMessageScaler("5. SDRAM IN1 Bist Fail", 0x00);
            ucBistResult |= _BIT1;
        }
    }
    else
    {
        DebugMessageScaler("5. SDRAM IN1 Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT2;
    }
    ScalerSetBit(P5_A1_IN1_FIFO_STATUS, ~_BIT5, 0x00);

    // MN BIST Test
    ScalerSetBit(P5_A2_MAIN_FIFO_STATUS, ~_BIT5, _BIT5);
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_A2_MAIN_FIFO_STATUS, _BIT7, 0x00) == _TRUE)
    {
        if(ScalerGetBit(P5_A2_MAIN_FIFO_STATUS, _BIT6) != _BIT6)
        {
            DebugMessageScaler("5. SDRAM MN Bist Fail", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    else
    {
        DebugMessageScaler("5. SDRAM MN Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT4;
    }
    ScalerSetByte(P5_A1_IN1_FIFO_STATUS, 0x00);
    ScalerSetByte(P5_A2_MAIN_FIFO_STATUS, 0x00);
    DebugMessageQC("6. SDRAM Bist Test Done", 0x00);
    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. SDRAM Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. SDRAM Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. SDRAM Bist FAIL", 0x00);
    }
    ucBistResult = 0x00;

    // Test SDRAM Controller
    //IN1 DRF BIST Test
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_A1_IN1_FIFO_STATUS, _BIT7, 0x00) == _TRUE)
    {
        ScalerSetByte(P5_F0_IN1_BIST_CTRL, 0x80);
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_F0_IN1_BIST_CTRL, 0xFF, 0xA0) == _TRUE)
        {
            ScalerSetByte(P5_F0_IN1_BIST_CTRL, 0x80);
            ScalerSetByte(P5_F0_IN1_BIST_CTRL, 0xC0);
            ScalerSetByte(P5_F0_IN1_BIST_CTRL, 0x80);
            if((ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_F0_IN1_BIST_CTRL, 0xFF, 0xA0) == _TRUE) || (ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_A1_IN1_FIFO_STATUS, 0xF0, 0xC0) == _TRUE))
            {
                ScalerSetByte(P5_F0_IN1_BIST_CTRL, 0x80);
                ScalerSetByte(P5_F0_IN1_BIST_CTRL, 0xC0);
                ScalerSetByte(P5_F0_IN1_BIST_CTRL, 0x80);
                if((ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_F0_IN1_BIST_CTRL, 0xFF, 0x80) == _TRUE) || (ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_A1_IN1_FIFO_STATUS, 0xF0, 0x40) == _TRUE))
                {
                    DebugMessageScaler("5. SDRAM IN1 DRF Bist Pass", 0x00);
                }
                else
                {
                    DebugMessageScaler("5. SDRAM IN1 DRF Bist P3 Fail", 0x00);
                    ucBistResult |= _BIT3;
                }
            }
            else
            {
                DebugMessageScaler("5. SDRAM IN1 DRF Bist P2 Fail", 0x00);
                ucBistResult |= _BIT2;
            }

        }
        else
        {
            DebugMessageScaler("5. SDRAM IN1 DRF Bist P1 Fail", 0x00);
            ucBistResult |= _BIT1;
        }

    }
    else
    {
        DebugMessageScaler("5. SDRAM IN1 Bist is still going", 0x00);
        ucBistResult |= _BIT0;
    }
    //MN DRF BIST Test
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_A2_MAIN_FIFO_STATUS, _BIT7, 0x00) == _TRUE)
    {
        ScalerSetByte(P5_F1_MN_BIST_CTRL, 0x80);
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_F1_MN_BIST_CTRL, 0xFF, 0xA0) == _TRUE)
        {
            ScalerSetByte(P5_F1_MN_BIST_CTRL, 0x80);
            ScalerSetByte(P5_F1_MN_BIST_CTRL, 0xC0);
            ScalerSetByte(P5_F1_MN_BIST_CTRL, 0x80);
            if((ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_F1_MN_BIST_CTRL, 0xFF, 0xA0) == _TRUE) || (ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_A2_MAIN_FIFO_STATUS, 0xF0, 0xC0) == _TRUE))
            {
                ScalerSetByte(P5_F1_MN_BIST_CTRL, 0x80);
                ScalerSetByte(P5_F1_MN_BIST_CTRL, 0xC0);
                ScalerSetByte(P5_F1_MN_BIST_CTRL, 0x80);
                if((ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_F1_MN_BIST_CTRL, 0xFF, 0x80) == _TRUE) || (ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P5_A2_MAIN_FIFO_STATUS, 0xF0, 0x40) == _TRUE))
                {
                    DebugMessageScaler("5. SDRAM MN DRF Bist Pass", 0x00);
                }
                else
                {
                    DebugMessageScaler("5. SDRAM MN DRF Bist P3 Fail", 0x00);
                    ucBistResult |= _BIT7;
                }
            }
            else
            {
                DebugMessageScaler("5. SDRAM MN DRF Bist P2 Fail", 0x00);
                ucBistResult |= _BIT6;
            }

        }
        else
        {
            DebugMessageScaler("5. SDRAM MN DRF Bist P1 Fail", 0x00);
            ucBistResult |= _BIT5;
        }

    }
    else
    {
        DebugMessageScaler("5. SDRAM MN Bist is still going", 0x00);
        ucBistResult |= _BIT4;
    }
    ScalerSetByte(P5_A1_IN1_FIFO_STATUS, 0x00);
    ScalerSetByte(P5_A2_MAIN_FIFO_STATUS, 0x00);
    ScalerSetByte(P5_F0_IN1_BIST_CTRL, 0x00);
    ScalerSetByte(P5_F1_MN_BIST_CTRL, 0x00);
    DebugMessageQC("6. SDRAM DRF Bist Test Done", 0x00);
    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. SDRAM DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. SDRAM DRF Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. SDRAM DRF Bist FAIL", 0x00);
    }
    ucBistResult = 0x00;


/*------------Display Conversion BIST---------------*/
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

    DebugMessageQC("5. ====DisplayTimingGen Even DRF Bist Test Start", 0x00);
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, ~_BIT5, _BIT5);

    //Wait DRF Start Pause
    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ScalerQCTimerPollingPortFlagProc(1000, P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, _BIT0, _TRUE) == _TRUE)
        {
            //Wait 1ms
            //ScalerTimerDelayXms(2);
            //DRF Test Resume Start
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, ~_BIT4, _BIT4);
            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, ~_BIT4, 0x00);
        }
        else
        {
            DebugMessageQC("5. DisplayTimingGen Even DRF Bist Start Pause Time Out Fail", 0x00);
            ucBistResult |= _BIT0;
        }
    }

    //Wait DRF Bist Done
    if(ScalerQCTimerPollingPortFlagProc(_BIST_TIMEOUT, P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, _BIT1, _TRUE) == _TRUE)
    {
        //Check Bist Pass or Fail
        if(ScalerGetDataPortBit( P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT3) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even DRF BIST Fail Flag for SRAM No.3", 0x00);
            ucBistResult |= _BIT7;
        };

        if(ScalerGetDataPortBit( P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT2) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even DRF BIST Fail Flag for SRAM No.2", 0x00);
            ucBistResult |= _BIT7;
        };

        if(ScalerGetDataPortBit( P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT1) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even DRF BIST Fail Flag for SRAM No.1", 0x00);
            ucBistResult |= _BIT7;
        };

        if(ScalerGetDataPortBit( P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_41_EVEN_BIST_RESULT, _BIT0) != 0x00)
        {
            DebugMessageQC("5. DisplayTimingGen Even DRF BIST Fail Flag for SRAM No.0", 0x00);
            ucBistResult |= _BIT7;
        };
    }
    else
    {
        DebugMessageQC("5. DisplayTimingGen Even DRF Bist Time Out Fail", 0x00);
        ucBistResult |= _BIT1;
    }
    //DisplayTimingGen diable Even DRF Bist test
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_40_EVEN_BIST_CTRL, ~_BIT5, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. DisplayTimingGen Even DRF Bist PASS", 0x00);
    }
    else
    {
        DebugMessageQC("6. DisplayTimingGen Even DRF Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. DisplayTimingGen Even DRF Bist FAIL ", 0x00);
    }
    ucBistResult = 0x00;

//------------GAMMA DRF BIST---------------//

    DebugMessageQC("5. ====Gamma DRF Bist Test Start", 0x00);

    ScalerSetBit(P2F_02_GAMMA_BIST_CTRL1_M1, ~_BIT7,_BIT7);

    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P2F_02_GAMMA_BIST_CTRL1_M1, _BIT5, _BIT5) == _TRUE)
    {
        ScalerTimerDelayXms(2);
        ScalerSetBit(P2F_02_GAMMA_BIST_CTRL1_M1, ~_BIT6, 0x00);
        ScalerSetBit(P2F_02_GAMMA_BIST_CTRL1_M1, ~_BIT6, _BIT6);
        ScalerSetBit(P2F_02_GAMMA_BIST_CTRL1_M1, ~_BIT6, 0x00);

        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P2F_02_GAMMA_BIST_CTRL1_M1, _BIT5, _BIT5) == _TRUE)
        {
            ScalerTimerDelayXms(2);
            ScalerSetBit(P2F_02_GAMMA_BIST_CTRL1_M1, ~_BIT6, 0x00);
            ScalerSetBit(P2F_02_GAMMA_BIST_CTRL1_M1, ~_BIT6, _BIT6);
            ScalerSetBit(P2F_02_GAMMA_BIST_CTRL1_M1, ~_BIT6, 0x00);

        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, P2F_02_GAMMA_BIST_CTRL1_M1, _BIT4, _BIT4) == _TRUE)
            {
                    if(ScalerGetBit(P2F_03_GAMMA_BIST_CTRL2_M1, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
                    {
                        DebugMessageQC("5. Gamma DRF Bist M1 Fail", 0x00);
                        ucBistResult |= _BIT3;
                    }
        }
        else
            {
                DebugMessageQC("5. Gamma DRF Bist M1 Time Out 3", 0x00);
                ucBistResult |= _BIT3;
            }
        }
        else
        {
            DebugMessageQC("5. Gamma DRF Bist M1 Time Out 2", 0x00);
            ucBistResult |= _BIT3;
        }
    }
    else
    {
        DebugMessageQC("5. Gamma DRF Bist M1 Time Out 1", 0x00);
        ucBistResult |= _BIT3;
    }

    // turn off drf bist
    ScalerSetBit(P2F_02_GAMMA_BIST_CTRL1_M1, ~_BIT7, 0x00);

    if(ucBistResult == 0x00)
    {
        DebugMessageQC("6. Gamma DRF Bist PASS", 0x00);
    return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Gamma DRF Bist Fail Mode", ucBistResult);
        DebugMessageQC("6. Gamma DRF Bist FAIL", 0x00);
        DebugMessageQC("6. Gamma DRF Bist FAIL ", 0x00);
    return _TEST_FAIL;
    }

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
