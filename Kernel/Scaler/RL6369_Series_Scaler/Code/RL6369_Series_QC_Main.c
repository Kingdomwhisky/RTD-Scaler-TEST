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
// ID Code      : RL6369_Series_QC_Main.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6369_SERIES_QC_MAIN__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// DP QC Test (For Timing 4096 x 2160 @ 30 & 60 Hz)
//----------------------------------------------------------------------------
#if(_DP_SUPPORT == _ON)
#define _DP_CRC0                     0x4D
#define _DP_CRC1                     0x81
#define _DP_CRC2                     0x4D
#define _DP_CRC3                     0x81
#define _DP_CRC4                     0x4D
#define _DP_CRC5                     0x81
#endif

//----------------------------------------------------------------------------
// HDMI QC Test
// HDMI Port D1 1920 x 1200 @ 70Hz
//----------------------------------------------------------------------------
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
#define _HDMI_CRC0               0x3E
#define _HDMI_CRC1               0x87
#define _HDMI_CRC2               0xF3
#define _HDMI_CRC3               0x00
#define _HDMI_CRC4               0x00
#define _HDMI_CRC5               0x00
#endif

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
BYTE ScalerQCA0PortTest(void);
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
BYTE ScalerQCD0PortTest(void);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
BYTE ScalerQCD1PortTest(void);

#if(_AUDIO_SUPPORT == _ON)
BYTE ScalerQCD1AudioTest(void);
void ScalerQCAudioSourceInputSwitch(EnumAudioInputSource bAudioSource, BYTE ucInputPort);
#endif
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
BYTE ScalerQCD2PortTest(void);
#endif

#if(_HDMI_SUPPORT == _ON)
bit ScalerQCHdmiTest(void);
#endif

#if(_DP_SUPPORT == _ON)
bit ScalerQCDpTest(void);
#endif

void ScalerQCAllDigitalFunctionDisable(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//----------------------------------------------------------------------------
// QC Main Flow Process
//----------------------------------------------------------------------------
//--------------------------------------------------
// Description  : Test Process for A0 Port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
#if (_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
BYTE ScalerQCA0PortTest(void)
{
    BYTE ucResult = 0x00;
    BYTE ucResult1 = 0x00;
    BYTE ucResult2 = 0x00;
    BYTE ucResult3 = 0x00;
    BYTE ucTemp = 0xFF;

    ucResult = (ucResult | ((BYTE)ScalerQCODTest()));

    if(ucResult != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

//#if(_PCB_TYPE == _RL6369_DEMO_1A2MHL1DP)
//    ucResult = (ucResult | ((BYTE)ScalerQCDSPCTest() << 1)); // Move to D1 PORT
//#endif

    if(ucResult != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        ScalerSetByte(0x0006, 0x06);
        ScalerSetByte(0x000D, ucResult);
        return ucResult;
#endif
    }

    ucResult = (ucResult | ((BYTE)ScalerQCOSDTest() << 2));

    if(ucResult != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        ScalerSetByte(0x0006, 0x07);
        ScalerSetByte(0x000D, ucResult);
        return ucResult;
#endif
    }

    ucResult = (ucResult | (BYTE)ScalerQCVGAPGTest() << 3);

    if(ucResult != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    ucResult = (ucResult | ((BYTE)ScalerQCADCNRTest() << 4));

    if(ucResult != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    ucResult = (ucResult | ((BYTE)ScalerQCRingingFilterTest() << 5));

    if(ucResult != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    ucResult = (ucResult | ((BYTE)ScalerQCDigitalFilterTest() << 6));

    if(ucResult != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    ucResult = (ucResult | ((BYTE)ScalerQCIPGTest() << 7));

    if(ucResult != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQC422to444Test()));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCIDomainColorConvTest() << 1));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCIDitherTest() << 2));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCDPGRandomTest() << 3));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | (BYTE)ScalerQCDPGTest() << 4);

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCHLWTest() << 5));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | (BYTE)ScalerQCDDomainColorConvTest() << 6);

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | (BYTE)ScalerQCDCRTest() << 7);

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult2 = (ucResult2 | (BYTE)ScalerQCDCCTest());

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCYPeakingTest() << 1));

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | (BYTE)ScalerQCICMTest() << 2);

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCCTSBRITest() << 3));

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCPCMTest() << 4));

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCsRGBTest() << 5));

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCGammaTest() << 6));

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCBackGroundColor() << 7));

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult3 = (ucResult3 | ((BYTE)ScalerQCDDitherTest()));

    if(ucResult3 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    ucResult3 = (ucResult3 | ((BYTE)ScalerQCScaleUpTest() << 1));

    if(ucResult3 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    ucResult3 = (ucResult3 | ((BYTE)ScalerQCLSRTest() << 2));

    if(ucResult3 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }


    ucResult3 = (ucResult3 | ((BYTE)ScalerQCBistTest() << 3));    // BIST Test

    if(ucResult3 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

#if (_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_1PC)
    ucResult3 = (ucResult3 | ((BYTE)ScalerQCFRCTest() << 4));
#endif

    if(ucResult3 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    return (ucResult | ucResult1 | ucResult2 | ucResult3);
}
#endif  // End of #if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)

#if (_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
BYTE ScalerQCD0PortTest(void)
{
    BYTE ucResult = 0x00;

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
    ucResult |= (ucResult | (BYTE)ScalerQCHdmiTest());
#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ucResult |= (ucResult | (BYTE)ScalerQCDpTest());
#endif

    if(ucResult != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    return ucResult;
}
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

//--------------------------------------------------
// Description  : Test Process for D1 Port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
#if (_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
BYTE ScalerQCD1PortTest(void)
{
    BYTE ucResult0 = 0x00;

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
    ucResult0 = (ucResult0 | (BYTE)ScalerQCHdmiTest());
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ucResult0 |= ScalerQCDpTest();
#endif

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

#if(_AUDIO_SUPPORT == _ON)
    ucResult0 = (ucResult0 | ((BYTE)ScalerQCD1AudioTest() << 1));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }
#endif

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCScaleDownTest() << 2));


    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

//Result0 = (ucResult0 | ((BYTE)ScalerQCBistTest_D1() << 7));
// TEST  Gary Modify

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

#if(_PCB_TYPE == _RL6369_QA_1A2MHL1DP)
    ucResult0 = (ucResult0 | ((BYTE)ScalerQCDSPCTest() << 3));
#endif

    return (ucResult0);
}

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Test Process for Audio D0 port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
BYTE ScalerQCD1AudioTest(void)
{
#if(_LINE_IN_SUPPORT == _ON)

    ScalerQCAudioSourceInputSwitch(_LINE_IN_AUDIO, _D1_INPUT_PORT);

    return _TEST_PASS;
#endif

}

//--------------------------------------------------
// Description  : Switch audio Input (AIN / DAC)
// Input Value  : bAudioSource
// Output Value : None
//--------------------------------------------------
void ScalerQCAudioSourceInputSwitch(EnumAudioInputSource enumAudioSource, BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    if(enumAudioSource == _DIGITAL_AUDIO)
    {
        // Select DAC Mux to Digital input
        ScalerSetBit(P6_D1_DA_MUTE, ~_BIT3, 0x00);

        ScalerAudioInputPortSwitch(_AUDIO_FROM_D0_PORT);

        // Reset DVC Counter
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, _BIT6);
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, 0x00);
    }
#if(_LINE_IN_SUPPORT == _ON)
    else if(enumAudioSource == _LINE_IN_AUDIO)
    {
        // Select DAC Mux to ADC input
        ScalerSetBit(P6_D1_DA_MUTE, ~_BIT3, _BIT3);

        ScalerAudioInputPortSwitch(_AUDIO_FROM_ADC_PORT);

        // Reset DVC Counter
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, _BIT6);
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, 0x00);
    }
#endif
}
#endif
#endif  // End of #if(_D1_INPUT_PORT_TYPE != D1_NO_PORT)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
BYTE ScalerQCD2PortTest(void)
{
    BYTE ucResult = 0x00;

#if ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
    ucResult |= ScalerQCHdmiTest();
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    ucResult |= ScalerQCDpTest();
#endif

    if(ucResult != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    return ucResult;
}
#endif

//--------------------------------------------------
// Description  : D1 Hdmi Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if (_HDMI_SUPPORT == _ON)
bit ScalerQCHdmiTest(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

    if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
    {
#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)
    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_04_CBUS0_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    if(ScalerTimerPollingFlagProc(200, P28_A7_CBUS_CTRL_07, (_BIT4 | _BIT3), _TRUE) == _TRUE)
    {
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);

        DebugMessageQC("6. MHL CBUS0 SINK ON", 0x00);
    }
    else
    {
        DebugMessageQC("6. HDMI CBUS0 Test Fail", 0x00);

        return _TEST_FAIL;
    }

#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)
    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_05_CBUS1_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    if(ScalerTimerPollingFlagProc(200, P29_A7_CBUS_CTRL_07, (_BIT4 | _BIT3), _TRUE) == _TRUE)
    {
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);

        DebugMessageQC("6. MHL CBUS1 SINK ON", 0x00);
    }
    else
    {
        DebugMessageQC("6. HDMI CBUS1 Test Fail", 0x00);

        return _TEST_FAIL;
    }

#endif

    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

    if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
    {
#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_04_CBUS0_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);

    if(ScalerTimerPollingFlagProc(200, P28_A7_CBUS_CTRL_07, (_BIT4 | _BIT3), _TRUE) == _TRUE)
    {
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);

        DebugMessageQC("6. MHL CBUS0 SINK ON", 0x00);
    }
    else
    {
        DebugMessageQC("6. HDMI CBUS0 Test Fail", 0x00);

        return _TEST_FAIL;
    }

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_05_CBUS1_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);

    if(ScalerTimerPollingFlagProc(200, P29_A7_CBUS_CTRL_07, (_BIT4 | _BIT3), _TRUE) == _TRUE)
    {
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);

        DebugMessageQC("6. MHL CBUS1 SINK ON", 0x00);
    }
    else
    {
        DebugMessageQC("6. HDMI CBUS1 Test Fail", 0x00);

        return _TEST_FAIL;
    }

#endif

    }
#endif

    // Read HDMI CRC Value
    ScalerSetBit(P2_A4_TMDS_CTRL, _BIT0, _BIT0);

    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);

    pData[0] = ScalerGetByte(P2_A5_TMDS_CRCOB2);
    pData[1] = ScalerGetByte(P2_A5_TMDS_CRCOB2);
    pData[2] = ScalerGetByte(P2_A5_TMDS_CRCOB2);
    pData[3] = ScalerGetByte(P2_A5_TMDS_CRCOB2);
    pData[4] = ScalerGetByte(P2_A5_TMDS_CRCOB2);
    pData[5] = ScalerGetByte(P2_A5_TMDS_CRCOB2);

    ScalerSetBit(P2_A4_TMDS_CTRL, _BIT0, 0x00);

    DebugMessageQC("5. HDMI Check CRC0", pData[0]);
    DebugMessageQC("5. HDMI Check CRC1", pData[1]);
    DebugMessageQC("5. HDMI Check CRC2", pData[2]);
    DebugMessageQC("5. HDMI Check CRC3", pData[3]);
    DebugMessageQC("5. HDMI Check CRC4", pData[4]);
    DebugMessageQC("5. HDMI Check CRC5", pData[5]);

    // Rearrange CRC Order
    switch(pData[0])
    {
        case _HDMI_CRC0:

            if((pData[0] == _HDMI_CRC0) && (pData[1] == _HDMI_CRC1) && (pData[2] == _HDMI_CRC2) &&
               (pData[3] == _HDMI_CRC3) && (pData[4] == _HDMI_CRC4) && (pData[5] == _HDMI_CRC5))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            break;

        case _HDMI_CRC1:

            if((pData[0] == _HDMI_CRC1) && (pData[1] == _HDMI_CRC2) && (pData[2] == _HDMI_CRC3) &&
               (pData[3] == _HDMI_CRC4) && (pData[4] == _HDMI_CRC5) && (pData[5] == _HDMI_CRC0))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            break;

        case _HDMI_CRC2:

            if((pData[0] == _HDMI_CRC2) && (pData[1] == _HDMI_CRC3) && (pData[2] == _HDMI_CRC4) &&
               (pData[3] == _HDMI_CRC5) && (pData[4] == _HDMI_CRC0) && (pData[5] == _HDMI_CRC1))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            break;

        case _HDMI_CRC3:

            if((pData[0] == _HDMI_CRC3) && (pData[1] == _HDMI_CRC4) && (pData[2] == _HDMI_CRC5) &&
               (pData[3] == _HDMI_CRC0) && (pData[4] == _HDMI_CRC1) && (pData[5] == _HDMI_CRC2))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            if((pData[0] == _HDMI_CRC4) && (pData[1] == _HDMI_CRC5) && (pData[2] == _HDMI_CRC0) &&
               (pData[3] == _HDMI_CRC1) && (pData[4] == _HDMI_CRC2) && (pData[5] == _HDMI_CRC3))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            if((pData[0] == _HDMI_CRC5) && (pData[1] == _HDMI_CRC0) && (pData[2] == _HDMI_CRC1) &&
               (pData[3] == _HDMI_CRC2) && (pData[4] == _HDMI_CRC3) && (pData[5] == _HDMI_CRC4))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }
            break;

        default:

            break;
    }

    DebugMessageQC("6. HDMI Test Fail", 0x00);

    return _TEST_FAIL;

 return _TEST_PASS;
}
#endif

#if(_DP_SUPPORT == _ON)
bit ScalerQCDpTest(void)
{
    BYTE ucResult = 0;

    // Enable Bist CLK
    ScalerSetBit(PB6_4E_SRAM_BIST_0, ~_BIT7, _BIT7);

    // =====================Test for Audio buf BIST=======================
    // Bist Reset
    ScalerSetBit(PB6_4E_SRAM_BIST_0, ~_BIT2, _BIT2);
    ScalerSetBit(PB6_4E_SRAM_BIST_0, ~_BIT2, 0x00);

    // Enable Bist
    ScalerSetBit(PB6_4E_SRAM_BIST_0, ~_BIT3, _BIT3);

    // Wait Audio Bist Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB6_4E_SRAM_BIST_0, _BIT1, _BIT1) == _TRUE)
    {
        // Get Bist Result
        if(ScalerGetBit(PB6_4E_SRAM_BIST_0, _BIT0) == _BIT0)
        {
            DebugMessageQC("5. DP0 Abuf Bist Fail1", 0x00);
            ucResult |= _BIT7;
        }
    }
    else
    {
        DebugMessageQC("5. DP0 Abuf Bist Fail2", 0x00);
        ucResult |= _BIT7;
    }

    // =====================Test for Audio buf DRF BIST=======================
    // Bist Reset
    ScalerSetByte(PB6_4E_SRAM_BIST_0, 0x80);
    ScalerSetBit(PB6_4E_SRAM_BIST_0, ~_BIT2, _BIT2);
    ScalerSetBit(PB6_4E_SRAM_BIST_0, ~_BIT2, 0x00);

    // Enable DRF Bist
    ScalerSetBit(PB6_4F_SRAM_BIST_1, ~_BIT4, _BIT4);

    ScalerSetByte(PB6_4E_SRAM_BIST_0, 0x80);


    // Wait DRF Srart Pause
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB6_4F_SRAM_BIST_1, _BIT2, _BIT2) == _TRUE)
    {
        // Wait Random Time
        for(pData[0] = 0; pData[0] < 10; pData[0]++)
        {
            DELAY_20US();
        }

        // Test Resume time
        ScalerSetBit(PB6_4F_SRAM_BIST_1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        ScalerSetBit(PB6_4F_SRAM_BIST_1, ~(_BIT4 | _BIT3), _BIT4);

        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB6_4F_SRAM_BIST_1, _BIT2, _BIT2) == _TRUE)
        {
            // Wait Random Time
            for(pData[0] = 0; pData[0] < 10; pData[0]++)
            {
                DELAY_20US();
            }

            // TEST RESUME pulse for negative checkerboard
            ScalerSetBit(PB6_4F_SRAM_BIST_1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            ScalerSetBit(PB6_4F_SRAM_BIST_1, ~(_BIT4 | _BIT3), _BIT4);

            // Wait DRF Bist Done
            if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB6_4F_SRAM_BIST_1, _BIT1, _BIT1) == _TRUE)
            {
                // Get Bist Result
                if(ScalerGetBit(PB6_4F_SRAM_BIST_1, _BIT0) == _BIT0)
                {
                    DebugMessageQC("5. DP0 Abuf DRF Bist Fail1", 0x00);
                    ucResult |= _BIT6;
                }
            }
            else
            {
                DebugMessageQC("5. DP0 Abuf DRF Bist Fail2", 0x00);
                ucResult |= _BIT6;
            }
        }
        else
        {
            DebugMessageQC("5. DP0 Abuf DRF Bist Fail3", 0x00);
            ucResult |= _BIT6;
        }
    }
    else
    {
        DebugMessageQC("5. DP0 Abuf DRF Bist Fail4", 0x00);
        ucResult |= _BIT6;
    }

    // Disable DRF Bist
    ScalerSetBit(PB6_4F_SRAM_BIST_1, ~_BIT4, 0x00);

    // =====================Test for D0 Video buf DRF BIST=======================
    // Bist Reset
    ScalerSetByte(PB5_25_SRAM_BIST_0, 0x80);
    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT2, _BIT2);
    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT2, 0x00);

    // Enable DRF Bist
    ScalerSetBit(PB5_26_SRAM_BIST_1, ~_BIT4, _BIT4);

    ScalerSetByte(PB5_25_SRAM_BIST_0, 0x80);

    // Wait DRF Srart Pause
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB5_26_SRAM_BIST_1, _BIT2, _BIT2) == _TRUE)
    {
        // Wait Random Time
        for(pData[0] = 0; pData[0] < 10; pData[0]++)
        {
            DELAY_20US();
        }

        // Test Resume time
        ScalerSetBit(PB5_26_SRAM_BIST_1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        ScalerSetBit(PB5_26_SRAM_BIST_1, ~(_BIT4 | _BIT3), _BIT4);

        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB5_26_SRAM_BIST_1, _BIT2, _BIT2) == _TRUE)
        {
            // Wait Random Time
            for(pData[0] = 0; pData[0] < 10; pData[0]++)
            {
                DELAY_20US();
            }

            // TEST RESUME pulse for negative checkerboard
            ScalerSetBit(PB5_26_SRAM_BIST_1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            ScalerSetBit(PB5_26_SRAM_BIST_1, ~(_BIT4 | _BIT3), _BIT4);

            // Wait DRF Bist Done
            if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB5_26_SRAM_BIST_1, _BIT1, _BIT1) == _TRUE)
            {
                // Get Bist Result
                if(ScalerGetBit(PB5_26_SRAM_BIST_1, _BIT0) == _BIT0)
                {
                    DebugMessageQC("5. DP Vbuf DRF Bist Fail1", 0x00);
                    ucResult |= _BIT4;
                }
            }
            else
            {
                DebugMessageQC("5. DP Vbuf DRF Bist Fail2", 0x00);
                ucResult |= _BIT4;
            }
        }
        else
        {
            DebugMessageQC("5. DP Vbuf DRF Bist Fail3", 0x00);
            ucResult |= _BIT4;
        }
    }
    else
    {
        DebugMessageQC("5. DP Vbuf DRF Bist Fail4", 0x00);
        ucResult |= _BIT4;
    }

    // Disable DRF Bist
    ScalerSetBit(PB5_26_SRAM_BIST_1, ~_BIT4, 0x00);

    // =====================Test for DP CRC=======================
    // Reserved for DP Test
    ScalerSetBit(PB5_70_DP_CRC_CTRL, ~(_BIT7 | _BIT5), 0x00);
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerSetBit(PB5_70_DP_CRC_CTRL, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));
    if(ScalerTimerPollingFlagProc(80, PB5_70_DP_CRC_CTRL, _BIT6, _TRUE) == _FALSE)

    {
        DebugMessageQC("5. DP CRC Calculation Timeout", 0x00);
        ucResult |= _BIT0;
    }
    else
    {
        if((ScalerGetByte(PB5_71_DP_CRC_R_M) != _DP_CRC0) || (ScalerGetByte(PB5_72_DP_CRC_R_L) != _DP_CRC1) || \
           (ScalerGetByte(PB5_73_DP_CRC_G_M) != _DP_CRC2) || (ScalerGetByte(PB5_74_DP_CRC_G_L) != _DP_CRC3) || \
           (ScalerGetByte(PB5_75_DP_CRC_B_M) != _DP_CRC4) || (ScalerGetByte(PB5_76_DP_CRC_B_L) != _DP_CRC5))
        {
            DebugMessageQC("5. DP CRC Value Mismatch", 0x00);
            ucResult |= _BIT0;
        }
    }


    // Disable Bist CLK
    ScalerSetBit(PB6_4E_SRAM_BIST_0, ~_BIT7, 0x00);

    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT7, 0x00);

    if((bit)ucResult == 0x00)
    {
        DebugMessageQC("6. DP Test PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. DP Test Fail", ucResult);

        return _TEST_FAIL;
    }
}
#endif

//--------------------------------------------------
// Description  : Disable All Digital Function & Watch Dog
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCAllDigitalFunctionDisable(void)
{
    ScalerDDomainBackgroundEnable(_DISABLE);
    // Disable Watch Dog
#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
    // Disable Input HVsync error IRQ and fifo under/overflow IRQ
    ScalerSetBit(P0_04_IRQ_CTRL0, ~(_BIT5 | _BIT1), 0x00);
#else
    // Disable Input H/V Error WD & Enable Frame Sync WD & Input H/Vsync overflow WD
    ScalerSetByte(P0_0C_WATCH_DOG_CTRL0, 0x00);
    ScalerSetByte(P16_18_MEAS_HS_VS_ERROR_WD, 0x00);
#endif

    // Disable Double Buffer
    ScalerSetByte(P31_C0_I_DB_CTRL, 0x00);
    ScalerSetByte(P31_C1_D_DB_CTRL, 0x00);
    ScalerSetByte(P31_C2_IMD_DB_STATUS, 0x00);

    //--------------------I Domain------------------//
    ScalerQCVGATopRandomGenOff();                      // Disable VGA Random Generator
    ScalerQCIDomainRandomGenOff();                      // Disable I Domain Random Generator

    ScalerSetBit(P31_40_YUV422_TO_444_PATH0, ~_BIT3, 0x00);         // Disable YUV422 to 444

    ScalerSetBit(P33_00_ADCNR_CTRL1, ~_BIT7, 0x00);     // Disable ADCNR
    ScalerSetBit(P33_02_ADCNR_CTRL3, ~(_BIT7 | _BIT6), 0x00);       // No Truncate LSB
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4)); // Disable Digital Filter
    ScalerSetBit(P0_99_DIGITAL_FILTER_PORT, ~(_BIT7 | _BIT6 | _BIT5 ), 0x00);

    ScalerSetBit(P25_A0_RFILTER_CTRL, ~_BIT7, 0x00);    // Disable Ringing Filter
    ScalerSetByte(P0_9C_RGB2YCC_CTRL, 0x00);            // Disable I-ColorConv
    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, 0x00);   // Disable I-Dither


    //--------------------D Domain------------------//
    ScalerQCHighlightWindowOff();                       // Disable Highlight Window
    ScalerQCDDomainPatternGenOff();                     // Disable D Domain Pattern Generator

    ScalerSetBit(P14_C0_LSR_CTRL, ~_BIT7, 0x00);        // Disable LSR
    ScalerSetByte(P14_A1_SR_YCC2RGB_CTRL, 0x00);        // Disable D-ColorConv
    ScalerSetBit(P7_D8_DCR_ADDRESS_PORT, ~_BIT0, 0x00); // Disable DCR
    ScalerSetBit(P7_C7_DCC_CTRL_0, ~_BIT7, 0x00);       // Disable DCC
    ScalerSetBit(P7_D0_ICM_CONTROL, ~(_BIT7), 0x00);    // Disable ICM
    ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT1, 0x00);        // Disable Contrast
    ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT0, 0x00);        // Disable Brightness
    ScalerSetByte(P7_D6_PEAKING_CORING_ACCESS_PORT_CTL, 0x00);
    ScalerSetBit(P9_A1_INPUT_GAMMA_CTRL, ~_BIT6, 0x00);             // Disable I-Gamma
    ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT2, 0x00);        // Dialbe SRGB
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT6, 0x00);              // Diable O-Gamma
    ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~_BIT5, 0x00);        // Disable D-Dither
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);           // Disable OD
}

#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)
