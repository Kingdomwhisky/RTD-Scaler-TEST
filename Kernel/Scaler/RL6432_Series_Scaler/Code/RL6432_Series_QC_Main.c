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
// ID Code      : RL6432_Series_QC_Main.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6432_SERIES_QC_MAIN__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// QC Port Test Enable
//----------------------------------------------------------------------------
#define _A0_PORT_TEST                           _ON
#define _D0_PORT_TEST                           _ON
#define _D1_PORT_TEST                           _ON
#define _D2_PORT_TEST                           _ON
#define _D3_PORT_TEST                           _ON


//----------------------------------------------------------------------------
// DP QC Test (For Timing 4096 x 2160 @ 30 & 60 Hz)
//----------------------------------------------------------------------------
#if(_DP_SUPPORT == _ON)
#define _DP_CRC0                                0x65
#define _DP_CRC1                                0xBD
#define _DP_CRC2                                0xD8
#define _DP_CRC3                                0x22
#define _DP_CRC4                                0xB4
#define _DP_CRC5                                0x24
#endif

//----------------------------------------------------------------------------
// HDMI QC Test
// HDMI High Speed 4096x2160@60Hz & 4096x2160@30Hz
//----------------------------------------------------------------------------
//#if((_D0_TMDS_SUPPORT == _ON) || (_D1_TMDS_SUPPORT == _ON))
#if((_D0_TMDS_SUPPORT == _ON) || (_D1_TMDS_SUPPORT == _ON))
#define _HDMI_HIGH_SPEED_CRC0                   0x5C
#define _HDMI_HIGH_SPEED_CRC1                   0x11
#define _HDMI_HIGH_SPEED_CRC2                   0x70
#define _HDMI_HIGH_SPEED_CRC3                   0x00
#define _HDMI_HIGH_SPEED_CRC4                   0x00
#define _HDMI_HIGH_SPEED_CRC5                   0x00
#endif

//----------------------------------------------------------------------------
// HDMI QC Test
// HDMI Low Speed 2560x1600@60Hz
//----------------------------------------------------------------------------
#if((_D2_TMDS_SUPPORT == _ON) || (_D3_TMDS_SUPPORT == _ON))
#define _HDMI_LOW_SPEED_CRC0                    0x83
#define _HDMI_LOW_SPEED_CRC1                    0x22
#define _HDMI_LOW_SPEED_CRC2                    0x20
#define _HDMI_LOW_SPEED_CRC3                    0x00
#define _HDMI_LOW_SPEED_CRC4                    0x00
#define _HDMI_LOW_SPEED_CRC5                    0x00
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
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
BYTE ScalerQCD2PortTest(void);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
BYTE ScalerQCD3PortTest(void);
#endif

#if(_D0_HDMI_SUPPORT == _ON)
bit ScalerQCD0HdmiTest(void);
#endif

#if(_D1_HDMI_SUPPORT == _ON)
bit ScalerQCD1HdmiTest(void);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
bit ScalerQCD2HdmiTest(void);
#endif

#if(_D3_HDMI_SUPPORT == _ON)
bit ScalerQCD3HdmiTest(void);
#endif

#if((_DP_SUPPORT == _ON) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
bit ScalerQCD0DpTest(void);
bit ScalerQCD0MstToSstSetting(void);
#endif

#if((_DP_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
bit ScalerQCD1DpTest(void);
#endif

void ScalerQCAllDigitalFunctionDisable(void);
bit ScalerQCWaitForIDDomainEvent(EnumWaitEventType enumEvent, BYTE ucDataPath);

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
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
BYTE ScalerQCA0PortTest(void)
{
    BYTE ucResult = 0x00;
    BYTE ucMemoryResult = 0x00;

#if(_A0_PORT_TEST == _OFF)
    if(ucResult == 0x00)
    {
        return ucResult;
    }
#endif

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
    ucMemoryResult = (ucMemoryResult | ((BYTE)ScalerQCDDRTest() << 0));
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
    ucMemoryResult = (ucMemoryResult | ((BYTE)ScalerQCSDRAMTest() << 0));
#endif

    if(ScalerQCDebug(0x01, ucMemoryResult) == _FALSE)
    {
        return ucMemoryResult;
    }

    ucResult = (ucResult | ((BYTE)ScalerQCVGAPGTest() << 0));

    if(ScalerQCDebug(0x02, ucResult) == _FALSE)
    {
        return ucResult;
    }

    ucResult = (ucResult | ((BYTE)ScalerQCADCNRTest() << 1));

    if(ScalerQCDebug(0x03, ucResult) == _FALSE)
    {
        return ucResult;
    }

    ucResult = (ucResult | ((BYTE)ScalerQCRingingFilterTest() << 2));

    if(ScalerQCDebug(0x04, ucResult) == _FALSE)
    {
        return ucResult;
    }

    ucResult = (ucResult | ((BYTE)ScalerQCDigitalFilterTest() << 3));

    if(ScalerQCDebug(0x05, ucResult) == _FALSE)
    {
        return ucResult;
    }

    ucMemoryResult = (ucMemoryResult | ((BYTE)ScalerQCScaleUpTest() << 1));

    if(ScalerQCDebug(0x06, ucMemoryResult) == _FALSE)
    {
        return ucMemoryResult;
    }

    ucMemoryResult = (ucMemoryResult | ((BYTE)ScalerQCLSRTest() << 2));

    if(ScalerQCDebug(0x07, ucMemoryResult) == _FALSE)
    {
        return ucMemoryResult;
    }

    ucResult = (ucResult | ((BYTE)ScalerQCOSDTest() << 4));

    if(ScalerQCDebug(0x08, ucResult) == _FALSE)
    {
        return ucResult;
    }

    ucMemoryResult = (ucMemoryResult | ((BYTE)ScalerQCFRCTest() << 3));

    if(ScalerQCDebug(0x09, ucMemoryResult) == _FALSE)
    {
        return ucMemoryResult;
    }

    ucMemoryResult = (ucMemoryResult | ((BYTE)ScalerQCRotationTest() << 4));

    if(ScalerQCDebug(0x0A, ucMemoryResult) == _FALSE)
    {
        return ucMemoryResult;
    }

    ucResult = (ucResult | ((BYTE)ScalerQCBistTest() << 5));

    if(ScalerQCDebug(0x0B, ucResult) == _FALSE)
    {
        return ucResult;
    }

    return (ucResult | ucMemoryResult);
}
#endif  // End of #if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)

//--------------------------------------------------
// Description  : Test Process for D0 Port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
BYTE ScalerQCD0PortTest(void)
{
    BYTE ucResult = 0x00;

#if(_D0_PORT_TEST == _OFF)
    if(ucResult == 0x00)
    {
        return ucResult;
    }
#endif

#if((_DP_SUPPORT == _ON) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
    ucResult = (ucResult | ((BYTE)ScalerQCD0DpTest() << 0));

    if(ScalerQCDebug(0x21, ucResult) == _FALSE)
    {
        return ucResult;
    }
#endif

    ucResult = (ucResult | ((BYTE)ScalerQC422to444Test() << 1));

    if(ScalerQCDebug(0x22, ucResult) == _FALSE)
    {
        return ucResult;
    }

    ucResult = (ucResult | ((BYTE)ScalerQCFormatConversionTest() << 2));

    if(ScalerQCDebug(0x23, ucResult) == _FALSE)
    {
        return ucResult;
    }

    ucResult = (ucResult | ((BYTE)ScalerQCScaleDownTest() << 3));

    if(ScalerQCDebug(0x24, ucResult) == _FALSE)
    {
        return ucResult;
    }

#if((_PCB_TYPE == _RL6432_QA_B_1A2MHL2DP_DPTX_LVDS_eDP))
    // DPMST QC Test
    ucResult = (ucResult | ((BYTE)ScalerQCDPMSTTest()) << 4);

    if(ScalerQCDebug(0x25, ucResult) == _FALSE)
    {
        return ucResult;
    }
#endif

    ucResult = (ucResult | ((BYTE)ScalerQCBistTest_D0() << 5));

    if(ScalerQCDebug(0x26, ucResult) == _FALSE)
    {
        return ucResult;
    }

    return ucResult;
}
#endif  // End of #if(_D0_INPUT_PORT_TYPE != D0_NO_PORT)

//--------------------------------------------------
// Description  : Test Process for D1 Port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
BYTE ScalerQCD1PortTest(void)
{
    BYTE ucResult0 = 0x00;
    BYTE ucResult1 = 0x00;
    BYTE ucResult2 = 0x00;

#if(_D1_PORT_TEST == _OFF)
    if(ucResult0 == 0x00)
    {
        return ucResult0;
    }
#endif

#if((_DP_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
    ucResult0 = (ucResult0 | ((BYTE)ScalerQCD1DpTest() << 0));

    if(ScalerQCDebug(0x41, ucResult0) == _FALSE)
    {
        return ucResult0;
    }
#endif

#if(_D1_HDMI_SUPPORT == _ON)
    ucResult0 = (ucResult0 | ((BYTE)ScalerQCD1HdmiTest() << 1));

    if(ScalerQCDebug(0x42, ucResult0) == _FALSE)
    {
        return ucResult0;
    }
#endif

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCHLWTest() << 2));

    if(ScalerQCDebug(0x43, ucResult0) == _FALSE)
    {
        return ucResult0;
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIPGTest() << 3));

    if(ScalerQCDebug(0x44, ucResult0) == _FALSE)
    {
        return ucResult0;
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIDomainColorConvTest() << 4));

    if(ScalerQCDebug(0x45, ucResult0) == _FALSE)
    {
        return ucResult0;
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIDLTITest() << 5));

    if(ScalerQCDebug(0x46, ucResult0) == _FALSE)
    {
        return ucResult0;
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIDitherTest() << 6));

    if(ScalerQCDebug(0x47, ucResult0) == _FALSE)
    {
        return ucResult0;
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCDPGTest() << 7));

    if(ScalerQCDebug(0x48, ucResult0) == _FALSE)
    {
        return ucResult0;
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCDPGRandomTest() << 0));

    if(ScalerQCDebug(0x49, ucResult1) == _FALSE)
    {
        return ucResult1;
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCDDomainColorConvTest() << 1));

    if(ScalerQCDebug(0x4A, ucResult1) == _FALSE)
    {
        return ucResult1;
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCDCRTest() << 2));

    if(ScalerQCDebug(0x4B, ucResult1) == _FALSE)
    {
        return ucResult1;
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCDCCTest() << 3));

    if(ScalerQCDebug(0x4C, ucResult1) == _FALSE)
    {
        return ucResult1;
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCICMTest() << 4));

    if(ScalerQCDebug(0x4D, ucResult1) == _FALSE)
    {
        return ucResult1;
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCCTSBRITest() << 5));

    if(ScalerQCDebug(0x4E, ucResult1) == _FALSE)
    {
        return ucResult1;
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCIAPSGainTest() << 6));

    if(ScalerQCDebug(0x4F, ucResult1) == _FALSE)
    {
        return ucResult1;
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQC3DGammaTest() << 7));

    if(ScalerQCDebug(0x51, ucResult1) == _FALSE)
    {
        return ucResult1;
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCRGBGammaTest() << 0));

    if(ScalerQCDebug(0x52, ucResult2) == _FALSE)
    {
        return ucResult2;
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCPCMTest() << 1));

    if(ScalerQCDebug(0x53, ucResult2) == _FALSE)
    {
        return ucResult2;
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCsRGBTest() << 2));

    if(ScalerQCDebug(0x54, ucResult2) == _FALSE)
    {
        return ucResult2;
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCGammaTest() << 3));

    if(ScalerQCDebug(0x55, ucResult2) == _FALSE)
    {
        return ucResult2;
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCPanelUniformityTest() << 4));

    if(ScalerQCDebug(0x56, ucResult2) == _FALSE)
    {
        return ucResult2;
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCDDitherTest() << 5));

    if(ScalerQCDebug(0x57, ucResult2) == _FALSE)
    {
        return ucResult2;
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCSHPTest() << 6));

    if(ScalerQCDebug(0x58, ucResult2) == _FALSE)
    {
        return ucResult2;
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCBistTest_D1() << 7));

    if(ScalerQCDebug(0x59, ucResult2) == _FALSE)
    {
        return ucResult2;
    }

    return (ucResult0 | ucResult1 | ucResult2);
}
#endif  // End of #if(_D1_INPUT_PORT_TYPE != D1_NO_PORT)

//--------------------------------------------------
// Description  : Test Process for D2 Port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
BYTE ScalerQCD2PortTest(void)
{
    BYTE ucResult = 0x00;

#if(_D2_PORT_TEST == _OFF)
    if(ucResult == 0x00)
    {
        return ucResult;
    }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
    ucResult = (ucResult | ((BYTE)ScalerQCD2HdmiTest() << 0));

    if(ScalerQCDebug(0x71, ucResult) == _FALSE)
    {
        return ucResult;
    }
#endif

    return ucResult;
}
#endif  // End of #if(_D2_INPUT_PORT_TYPE != D2_NO_PORT)

//--------------------------------------------------
// Description  : Test Process for D3 Port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
BYTE ScalerQCD3PortTest(void)
{
    BYTE ucResult = 0x00;

#if(_D3_PORT_TEST == _OFF)
    if(ucResult == 0x00)
    {
        return ucResult;
    }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    ucResult = (ucResult | ((BYTE)ScalerQCD3HdmiTest() << 0));

    if(ScalerQCDebug(0x91, ucResult) == _FALSE)
    {
        return ucResult;
    }
#endif

    ucResult = (ucResult | ((BYTE)ScalerQCODTest() << 1));

    if(ScalerQCDebug(0x92, ucResult) == _FALSE)
    {
        return ucResult;
    }

#if(_PCB_TYPE == _RL6432_QA_B_1A2MHL2DP_DPTX_LVDS_eDP)
    // eDPTX QC Test
    ucResult = (ucResult | ((BYTE)ScalerQCeDPTXTest()) << 2);

    if(ScalerQCDebug(0x93, ucResult) == _FALSE)
    {
        return ucResult;
    }

    // LVDS QC Test
    ucResult = (ucResult | ((BYTE)ScalerQCDSPCTest() << 3));

    if(ScalerQCDebug(0x94, ucResult) == _FALSE)
    {
        return ucResult;
    }
#endif // End of #if(_PCB_TYPE == _RL6432_QA_B_1A2MHL2DP_DPTX_LVDS_eDP)

    return ucResult;
}
#endif  // End of #if(_D3_INPUT_PORT_TYPE != D3_NO_PORT)

//--------------------------------------------------
// Description  : D0 Hdmi Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if(_D0_HDMI_SUPPORT == _ON)
bit ScalerQCD0HdmiTest(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

    if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
    {

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)
    // DDC0 CBUS Swap Settings
    ScalerSetBit(P6F_04_CBUS0_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)
    // DDC0 CBUS Swap Settings
    ScalerSetBit(P6F_05_CBUS1_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D0_CBUS_CHANNEL_SEL == _CBUS2)
    // DDC0 CBUS Swap Settings
    ScalerSetBit(P6F_06_CBUS2_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D0_CBUS_CHANNEL_SEL == _CBUS3)
    // DDC0 CBUS Swap Settings
    ScalerSetBit(P6F_07_CBUS3_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

        if(ScalerTimerPollingFlagProc(200, P28_A7_CBUS_CTRL_07, (_BIT4 | _BIT3), _TRUE) == _TRUE)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);

            DebugMessageQC("6. MHL CBUS SINK ON", 0x00);
        }
        else
        {
            DebugMessageQC("6. HDMI CBUS Test Fail", 0x00);

            return _TEST_FAIL;
        }
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
        case _HDMI_HIGH_SPEED_CRC0:

            if((pData[0] == _HDMI_HIGH_SPEED_CRC0) && (pData[1] == _HDMI_HIGH_SPEED_CRC1) && (pData[2] == _HDMI_HIGH_SPEED_CRC2) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC3) && (pData[4] == _HDMI_HIGH_SPEED_CRC4) && (pData[5] == _HDMI_HIGH_SPEED_CRC5))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            break;

        case _HDMI_HIGH_SPEED_CRC1:

            if((pData[0] == _HDMI_HIGH_SPEED_CRC1) && (pData[1] == _HDMI_HIGH_SPEED_CRC2) && (pData[2] == _HDMI_HIGH_SPEED_CRC3) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC4) && (pData[4] == _HDMI_HIGH_SPEED_CRC5) && (pData[5] == _HDMI_HIGH_SPEED_CRC0))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            break;

        case _HDMI_HIGH_SPEED_CRC2:

            if((pData[0] == _HDMI_HIGH_SPEED_CRC2) && (pData[1] == _HDMI_HIGH_SPEED_CRC3) && (pData[2] == _HDMI_HIGH_SPEED_CRC4) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC5) && (pData[4] == _HDMI_HIGH_SPEED_CRC0) && (pData[5] == _HDMI_HIGH_SPEED_CRC1))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            break;

        case _HDMI_HIGH_SPEED_CRC3:

            if((pData[0] == _HDMI_HIGH_SPEED_CRC3) && (pData[1] == _HDMI_HIGH_SPEED_CRC4) && (pData[2] == _HDMI_HIGH_SPEED_CRC5) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC0) && (pData[4] == _HDMI_HIGH_SPEED_CRC1) && (pData[5] == _HDMI_HIGH_SPEED_CRC2))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            if((pData[0] == _HDMI_HIGH_SPEED_CRC4) && (pData[1] == _HDMI_HIGH_SPEED_CRC5) && (pData[2] == _HDMI_HIGH_SPEED_CRC0) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC1) && (pData[4] == _HDMI_HIGH_SPEED_CRC2) && (pData[5] == _HDMI_HIGH_SPEED_CRC3))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            if((pData[0] == _HDMI_HIGH_SPEED_CRC5) && (pData[1] == _HDMI_HIGH_SPEED_CRC0) && (pData[2] == _HDMI_HIGH_SPEED_CRC1) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC2) && (pData[4] == _HDMI_HIGH_SPEED_CRC3) && (pData[5] == _HDMI_HIGH_SPEED_CRC4))
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
}
#endif

//--------------------------------------------------
// Description  : D1 Hdmi Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if(_D1_HDMI_SUPPORT == _ON)
bit ScalerQCD1HdmiTest(void)
{
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

    if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
    {

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_04_CBUS0_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_05_CBUS1_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS2)
    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_06_CBUS2_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS3)
    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_07_CBUS3_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);
#endif

        if(ScalerTimerPollingFlagProc(200, P29_A7_CBUS_CTRL_07, (_BIT4 | _BIT3), _TRUE) == _TRUE)
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
    }
#endif

    // Read HDMI CRC Value
    ScalerSetBit(P70_A4_TMDS_CTRL, _BIT0, _BIT0);

    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);

    pData[0] = ScalerGetByte(P70_A5_TMDS_CRCOB2);
    pData[1] = ScalerGetByte(P70_A5_TMDS_CRCOB2);
    pData[2] = ScalerGetByte(P70_A5_TMDS_CRCOB2);
    pData[3] = ScalerGetByte(P70_A5_TMDS_CRCOB2);
    pData[4] = ScalerGetByte(P70_A5_TMDS_CRCOB2);
    pData[5] = ScalerGetByte(P70_A5_TMDS_CRCOB2);

    ScalerSetBit(P70_A4_TMDS_CTRL, _BIT0, 0x00);

    DebugMessageQC("5. HDMI Check CRC0", pData[0]);
    DebugMessageQC("5. HDMI Check CRC1", pData[1]);
    DebugMessageQC("5. HDMI Check CRC2", pData[2]);
    DebugMessageQC("5. HDMI Check CRC3", pData[3]);
    DebugMessageQC("5. HDMI Check CRC4", pData[4]);
    DebugMessageQC("5. HDMI Check CRC5", pData[5]);

    // Rearrange CRC Order
    switch(pData[0])
    {
        case _HDMI_HIGH_SPEED_CRC0:

            if((pData[0] == _HDMI_HIGH_SPEED_CRC0) && (pData[1] == _HDMI_HIGH_SPEED_CRC1) && (pData[2] == _HDMI_HIGH_SPEED_CRC2) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC3) && (pData[4] == _HDMI_HIGH_SPEED_CRC4) && (pData[5] == _HDMI_HIGH_SPEED_CRC5))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            break;

        case _HDMI_HIGH_SPEED_CRC1:

            if((pData[0] == _HDMI_HIGH_SPEED_CRC1) && (pData[1] == _HDMI_HIGH_SPEED_CRC2) && (pData[2] == _HDMI_HIGH_SPEED_CRC3) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC4) && (pData[4] == _HDMI_HIGH_SPEED_CRC5) && (pData[5] == _HDMI_HIGH_SPEED_CRC0))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            break;

        case _HDMI_HIGH_SPEED_CRC2:

            if((pData[0] == _HDMI_HIGH_SPEED_CRC2) && (pData[1] == _HDMI_HIGH_SPEED_CRC3) && (pData[2] == _HDMI_HIGH_SPEED_CRC4) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC5) && (pData[4] == _HDMI_HIGH_SPEED_CRC0) && (pData[5] == _HDMI_HIGH_SPEED_CRC1))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            break;

        case _HDMI_HIGH_SPEED_CRC3:

            if((pData[0] == _HDMI_HIGH_SPEED_CRC3) && (pData[1] == _HDMI_HIGH_SPEED_CRC4) && (pData[2] == _HDMI_HIGH_SPEED_CRC5) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC0) && (pData[4] == _HDMI_HIGH_SPEED_CRC1) && (pData[5] == _HDMI_HIGH_SPEED_CRC2))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            if((pData[0] == _HDMI_HIGH_SPEED_CRC4) && (pData[1] == _HDMI_HIGH_SPEED_CRC5) && (pData[2] == _HDMI_HIGH_SPEED_CRC0) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC1) && (pData[4] == _HDMI_HIGH_SPEED_CRC2) && (pData[5] == _HDMI_HIGH_SPEED_CRC3))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            if((pData[0] == _HDMI_HIGH_SPEED_CRC5) && (pData[1] == _HDMI_HIGH_SPEED_CRC0) && (pData[2] == _HDMI_HIGH_SPEED_CRC1) &&
               (pData[3] == _HDMI_HIGH_SPEED_CRC2) && (pData[4] == _HDMI_HIGH_SPEED_CRC3) && (pData[5] == _HDMI_HIGH_SPEED_CRC4))
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
}
#endif

//--------------------------------------------------
// Description  : D2 Hdmi Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if(_D2_HDMI_SUPPORT == _ON)
bit ScalerQCD2HdmiTest(void)
{
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

    if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        if(ScalerTimerPollingFlagProc(200, P2A_A7_CBUS_CTRL_07, (_BIT4 | _BIT3), _TRUE) == _TRUE)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);

	    DebugMessageQC("6. MHL CBUS SINK ON", 0x00);
        }
        else
        {
            DebugMessageQC("6. HDMI CBUS Test Fail", 0x00);

            return _TEST_FAIL;
        }
    }
#endif

    // Read HDMI CRC Value
    ScalerSetBit(P71_A4_TMDS_CTRL, ~_BIT0, _BIT0);

    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);

    ScalerSetBit(P71_A4_TMDS_CTRL, ~_BIT0, 0x00);

    pData[0] = ScalerGetByte(P71_A5_TMDS_CRCOB2);
    pData[1] = ScalerGetByte(P71_A5_TMDS_CRCOB2);
    pData[2] = ScalerGetByte(P71_A5_TMDS_CRCOB2);
    pData[3] = ScalerGetByte(P71_A5_TMDS_CRCOB2);
    pData[4] = ScalerGetByte(P71_A5_TMDS_CRCOB2);
    pData[5] = ScalerGetByte(P71_A5_TMDS_CRCOB2);

    DebugMessageQC("5. HDMI Check CRC0", pData[0]);
    DebugMessageQC("5. HDMI Check CRC1", pData[1]);
    DebugMessageQC("5. HDMI Check CRC2", pData[2]);
    DebugMessageQC("5. HDMI Check CRC3", pData[3]);
    DebugMessageQC("5. HDMI Check CRC4", pData[4]);
    DebugMessageQC("5. HDMI Check CRC5", pData[5]);

    if((pData[0] == _HDMI_LOW_SPEED_CRC0) && (pData[1] == _HDMI_LOW_SPEED_CRC1) && (pData[2] == _HDMI_LOW_SPEED_CRC2) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC3) && (pData[4] == _HDMI_LOW_SPEED_CRC4) && (pData[5] == _HDMI_LOW_SPEED_CRC5))
    {
        DebugMessageQC("6. HDMI Test Pass CRC", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_LOW_SPEED_CRC1) && (pData[1] == _HDMI_LOW_SPEED_CRC2) && (pData[2] == _HDMI_LOW_SPEED_CRC3) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC4) && (pData[4] == _HDMI_LOW_SPEED_CRC5) && (pData[5] == _HDMI_LOW_SPEED_CRC0))
    {
        DebugMessageQC("6. HDMI Test Pass CRC", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_LOW_SPEED_CRC2) && (pData[1] == _HDMI_LOW_SPEED_CRC3) && (pData[2] == _HDMI_LOW_SPEED_CRC4) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC5) && (pData[4] == _HDMI_LOW_SPEED_CRC0) && (pData[5] == _HDMI_LOW_SPEED_CRC1))
    {
        DebugMessageQC("6. HDMI Test Pass CRC", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_LOW_SPEED_CRC3) && (pData[1] == _HDMI_LOW_SPEED_CRC4) && (pData[2] == _HDMI_LOW_SPEED_CRC5) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC0) && (pData[4] == _HDMI_LOW_SPEED_CRC1) && (pData[5] == _HDMI_LOW_SPEED_CRC2))
    {
        DebugMessageQC("6. HDMI Test Pass CRC", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_LOW_SPEED_CRC4) && (pData[1] == _HDMI_LOW_SPEED_CRC5) && (pData[2] == _HDMI_LOW_SPEED_CRC0) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC1) && (pData[4] == _HDMI_LOW_SPEED_CRC2) && (pData[5] == _HDMI_LOW_SPEED_CRC3))
    {
        DebugMessageQC("6. HDMI Test Pass CRC", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_LOW_SPEED_CRC5) && (pData[1] == _HDMI_LOW_SPEED_CRC0) && (pData[2] == _HDMI_LOW_SPEED_CRC1) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC2) && (pData[4] == _HDMI_LOW_SPEED_CRC3) && (pData[5] == _HDMI_LOW_SPEED_CRC4))
    {
        DebugMessageQC("6. HDMI Test Pass CRC", 0x00);
        return _TEST_PASS;
    }

    DebugMessageQC("6. HDMI Test Fail", 0x00);

    return _TEST_FAIL;
}
#endif

//--------------------------------------------------
// Description  : D3 Hdmi Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if(_D3_HDMI_SUPPORT == _ON)
bit ScalerQCD3HdmiTest(void)
{
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

    if(GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        if(ScalerTimerPollingFlagProc(200, P68_A7_CBUS_CTRL_07, (_BIT4 | _BIT3), _TRUE) == _TRUE)
        {
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);

            DebugMessageQC("6. MHL CBUS SINK ON", 0x00);
        }
        else
        {
            DebugMessageQC("6. HDMI CBUS Test Fail", 0x00);

            return _TEST_FAIL;
        }
    }
#endif

    // Read HDMI CRC Value
    ScalerSetBit(P72_A4_TMDS_CTRL, ~_BIT0, _BIT0);

    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);

    ScalerSetBit(P72_A4_TMDS_CTRL, ~_BIT0, 0x00);

    pData[0] = ScalerGetByte(P72_A5_TMDS_CRCOB2);
    pData[1] = ScalerGetByte(P72_A5_TMDS_CRCOB2);
    pData[2] = ScalerGetByte(P72_A5_TMDS_CRCOB2);
    pData[3] = ScalerGetByte(P72_A5_TMDS_CRCOB2);
    pData[4] = ScalerGetByte(P72_A5_TMDS_CRCOB2);
    pData[5] = ScalerGetByte(P72_A5_TMDS_CRCOB2);

    DebugMessageQC("5. HDMI Check CRC0", pData[0]);
    DebugMessageQC("5. HDMI Check CRC1", pData[1]);
    DebugMessageQC("5. HDMI Check CRC2", pData[2]);
    DebugMessageQC("5. HDMI Check CRC3", pData[3]);
    DebugMessageQC("5. HDMI Check CRC4", pData[4]);
    DebugMessageQC("5. HDMI Check CRC5", pData[5]);

    if((pData[0] == _HDMI_LOW_SPEED_CRC0) && (pData[1] == _HDMI_LOW_SPEED_CRC1) && (pData[2] == _HDMI_LOW_SPEED_CRC2) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC3) && (pData[4] == _HDMI_LOW_SPEED_CRC4) && (pData[5] == _HDMI_LOW_SPEED_CRC5))
    {
        DebugMessageQC("6. HDMI Test Pass", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_LOW_SPEED_CRC1) && (pData[1] == _HDMI_LOW_SPEED_CRC2) && (pData[2] == _HDMI_LOW_SPEED_CRC3) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC4) && (pData[4] == _HDMI_LOW_SPEED_CRC5) && (pData[5] == _HDMI_LOW_SPEED_CRC0))
    {
        DebugMessageQC("6. HDMI Test Pass", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_LOW_SPEED_CRC2) && (pData[1] == _HDMI_LOW_SPEED_CRC3) && (pData[2] == _HDMI_LOW_SPEED_CRC4) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC5) && (pData[4] == _HDMI_LOW_SPEED_CRC0) && (pData[5] == _HDMI_LOW_SPEED_CRC1))
    {
        DebugMessageQC("6. HDMI Test Pass", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_LOW_SPEED_CRC3) && (pData[1] == _HDMI_LOW_SPEED_CRC4) && (pData[2] == _HDMI_LOW_SPEED_CRC5) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC0) && (pData[4] == _HDMI_LOW_SPEED_CRC1) && (pData[5] == _HDMI_LOW_SPEED_CRC2))
    {
        DebugMessageQC("6. HDMI Test Pass", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_LOW_SPEED_CRC4) && (pData[1] == _HDMI_LOW_SPEED_CRC5) && (pData[2] == _HDMI_LOW_SPEED_CRC0) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC1) && (pData[4] == _HDMI_LOW_SPEED_CRC2) && (pData[5] == _HDMI_LOW_SPEED_CRC3))
    {
        DebugMessageQC("6. HDMI Test Pass", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_LOW_SPEED_CRC5) && (pData[1] == _HDMI_LOW_SPEED_CRC0) && (pData[2] == _HDMI_LOW_SPEED_CRC1) &&
       (pData[3] == _HDMI_LOW_SPEED_CRC2) && (pData[4] == _HDMI_LOW_SPEED_CRC3) && (pData[5] == _HDMI_LOW_SPEED_CRC4))
    {
        DebugMessageQC("6. HDMI Test Pass", 0x00);
        return _TEST_PASS;
    }

    DebugMessageQC("6. HDMI Test Fail", 0x00);

    return _TEST_FAIL;
}
#endif

//--------------------------------------------------
// Description  : D0 DP Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if((_DP_SUPPORT == _ON) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
bit ScalerQCD0DpTest(void)
{
    BYTE ucResult = 0;

    // =====================Test for Audio buf BIST=======================
    // Enable bist clock
    ScalerSetBit(PB6_4E_SRAM_BIST_0, ~_BIT7, _BIT7);

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
        ScalerTimerDelayXms(5);
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

    // =====================Test for D0 Video buf BIST=======================
    // Enable bist clock
    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT7, _BIT7);

    // Bist Reset
    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT2, _BIT2);
    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT2, 0x00);

    // Enable Bist
    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT3, _BIT3);

    // Wait Video Bist Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB5_25_SRAM_BIST_0, _BIT1, _BIT1) == _TRUE)
    {
        // Get Bist Result
        if(ScalerGetBit(PB5_25_SRAM_BIST_0, _BIT0) == _BIT0)
        {
            DebugMessageQC("5. DP0 Vbuf Bist Fail1", 0x00);
            ucResult |= _BIT5;
        }
    }
    else
    {
        DebugMessageQC("5. DP0 Vbuf Bist Fail2", 0x00);
        ucResult |= _BIT5;
    }

    // =====================Test for D0 Video buf DRF BIST=======================
    // Bist Reset
    ScalerSetByte(PB5_25_SRAM_BIST_0, 0x80);

    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT2, _BIT2);
    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT2, 0x00);

    // Enable DRF Bist
    ScalerSetBit(PB5_26_SRAM_BIST_1, ~_BIT4, _BIT4);

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

    if(ScalerQCD0MstToSstSetting() == _TRUE)
    {
        // =====================Test for D0 MST2SST Video buf BIST=======================
        // Enable bist clock
        ScalerSetBit(PA_65_SRAM_BIST_0, ~_BIT7, _BIT7);

        // Bist Reset
        ScalerSetBit(PA_65_SRAM_BIST_0, ~_BIT2, _BIT2);
        ScalerSetBit(PA_65_SRAM_BIST_0, ~_BIT2, 0x00);

        // Enable Bist
        ScalerSetBit(PA_65_SRAM_BIST_0, ~_BIT3, _BIT3);

        // Wait Video Bist Done
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PA_65_SRAM_BIST_0, _BIT1, _BIT1) == _TRUE)
        {
            // Get Bist Result
            if(ScalerGetBit(PA_65_SRAM_BIST_0, _BIT0) == _BIT0)
            {
                DebugMessageQC("5. DP MST2SST Vbuf Bist Fail1", 0x00);
                ucResult |= _BIT3;
            }
        }
        else
        {
            DebugMessageQC("5. DP MST2SST Vbuf Bist Fail2", 0x00);
            ucResult |= _BIT3;
        }

        // =====================Test for D0 MST2SST Video buf DRF BIST=======================
        // Bist Reset
        ScalerSetByte(PA_65_SRAM_BIST_0, 0x80);
        ScalerSetBit(PA_65_SRAM_BIST_0, ~_BIT2, _BIT2);
        ScalerSetBit(PA_65_SRAM_BIST_0, ~_BIT2, 0x00);


        // Enable DRF Bist
        ScalerSetBit(PA_66_SRAM_BIST_1, ~_BIT4, _BIT4);

        ScalerSetByte(PA_65_SRAM_BIST_0, 0x80);

        // Wait DRF Srart Pause
        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PA_66_SRAM_BIST_1, _BIT2, _BIT2) == _TRUE)
        {
            // Wait Random Time
            for(pData[0] = 0; pData[0] < 10; pData[0]++)
            {
                DELAY_20US();
            }
            ScalerTimerDelayXms(2);

            // Test Resume time
            ScalerSetBit(PA_66_SRAM_BIST_1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            ScalerTimerDelayXms(5);
            ScalerSetBit(PA_66_SRAM_BIST_1, ~(_BIT4 | _BIT3), _BIT4);

            if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PA_66_SRAM_BIST_1, _BIT2, _BIT2) == _TRUE)
            {
                // Wait Random Time
                for(pData[0] = 0; pData[0] < 10; pData[0]++)
                {
                    DELAY_20US();
                }

                // TEST RESUME pulse for negative checkerboard
                ScalerSetBit(PA_66_SRAM_BIST_1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

                // Wait DRF Bist Done
                if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PA_66_SRAM_BIST_1, _BIT1, _BIT1) == _TRUE)
                {
                    // Get Bist Result
                    if(ScalerGetBit(PA_66_SRAM_BIST_1, _BIT0) == _BIT0)
                    {
                        DebugMessageQC("5. DP MST2SST Vbuf DRF Bist Fail1", 0x00);
                        ucResult |= _BIT2;
                    }
                }
                else
                {
                    DebugMessageQC("5. DP MST2SST Vbuf DRF Bist Fail2", 0x00);
                    ucResult |= _BIT2;
                }
            }
            else
            {
                DebugMessageQC("5. DP MST2SST Vbuf DRF Bist Fail3", 0x00);
                ucResult |= _BIT2;
            }
        }
        else
        {
            DebugMessageQC("5. DP MST2SST Vbuf DRF Bist Fail4", 0x00);
            ucResult |= _BIT2;
        }

        // Disable DRF Bist
        ScalerSetBit(PA_66_SRAM_BIST_1, ~_BIT4, 0x00);

        // =====================Test for DP CRC=======================
        // Reserved for DP Test
        ScalerSetBit(PA_70_DP_CRC_CTRL, ~(_BIT7 | _BIT5), 0x00);
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerSetBit(PA_70_DP_CRC_CTRL, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

        if(ScalerTimerPollingFlagProc(120, PA_70_DP_CRC_CTRL, _BIT6, _TRUE) == _FALSE)
        {
            DebugMessageQC("5. DP MST2SST CRC Calculation Timeout", 0x00);
            ucResult |= _BIT1;
        }
        else
        {
            if((ScalerGetByte(PA_71_DP_CRC_R_M) != _DP_CRC0) || (ScalerGetByte(PA_72_DP_CRC_R_L) != _DP_CRC1) || \
               (ScalerGetByte(PA_73_DP_CRC_G_M) != _DP_CRC2) || (ScalerGetByte(PA_74_DP_CRC_G_L) != _DP_CRC3) || \
               (ScalerGetByte(PA_75_DP_CRC_B_M) != _DP_CRC4) || (ScalerGetByte(PA_76_DP_CRC_B_L) != _DP_CRC5))
            {
                DebugMessageQC("5. DP MST2SST CRC Value Mismatch", 0x00);
                DebugMessageQC("5. DP MST2SST CRC - 0", ScalerGetByte(PA_71_DP_CRC_R_M));
                DebugMessageQC("5. DP MST2SST CRC - 1", ScalerGetByte(PA_72_DP_CRC_R_L));
                DebugMessageQC("5. DP MST2SST CRC - 2", ScalerGetByte(PA_73_DP_CRC_G_M));
                DebugMessageQC("5. DP MST2SST CRC - 3", ScalerGetByte(PA_74_DP_CRC_G_L));
                DebugMessageQC("5. DP MST2SST CRC - 4", ScalerGetByte(PA_75_DP_CRC_B_M));
                DebugMessageQC("5. DP MST2SST CRC - 5", ScalerGetByte(PA_76_DP_CRC_B_L));
                ucResult |= _BIT1;
            }
            else
            {
                DebugMessageQC("5. DP MST2SST CRC Value Pass", 0x00);
            }
        }
    }
    else
    {
        DebugMessageQC("5. DP0 MST2SST FIFO Failed", 0x00);
        ucResult |= (_BIT3| _BIT2 | _BIT1);
    }

    // =====================Test for DP CRC=======================
    // Reserved for DP Test
    ScalerSetBit(PB5_70_DP_CRC_CTRL, ~(_BIT7 | _BIT5), 0x00);
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerSetBit(PB5_70_DP_CRC_CTRL, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));
    if(ScalerTimerPollingFlagProc(120, PB5_70_DP_CRC_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        DebugMessageQC("5. DP CRC Calculation Timeout", 0x00);
        ucResult |= _BIT0;
    }
    else
    {
        ScalerTimerWaitForEvent(_EVENT_IVS);
        if((ScalerGetByte(PB5_71_DP_CRC_R_M) != _DP_CRC0) || (ScalerGetByte(PB5_72_DP_CRC_R_L) != _DP_CRC1) || \
           (ScalerGetByte(PB5_73_DP_CRC_G_M) != _DP_CRC2) || (ScalerGetByte(PB5_74_DP_CRC_G_L) != _DP_CRC3) || \
           (ScalerGetByte(PB5_75_DP_CRC_B_M) != _DP_CRC4) || (ScalerGetByte(PB5_76_DP_CRC_B_L) != _DP_CRC5))
        {
            DebugMessageQC("5. DP CRC Value Mismatch", 0x00);
            ucResult |= _BIT0;
        }
    }

    if((bit)ucResult == 0x00)
    {
        DebugMessageQC("6. DP Test PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. DP Fail Mode", ucResult);
        DebugMessageQC("6. DP Test FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : D1 DP Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
bit ScalerQCD0MstToSstSetting(void)
{
    SDWORD lOffsetValue = 0;
    DWORD ulpllm = 0;
    BYTE ucplln = 0;
    WORD usDpHtotal = 0;
    WORD usDpVtotal = 0;
    DWORD ulVBs2BsCount = 0;
    DWORD ulStreamClkValue = 0;
    DWORD ulXtal_clk = 0;
    BYTE ucdiv_pllo = 1;
    BYTE ucdiv_divs = 1;

#if(_DP_FREESYNC_SUPPORT == _ON)
    DWORD ulDpNvidValue = 0;
    DWORD ulDpMvidValue = 0;
#endif

    // Set mst_en = SST mode
    ScalerSetBit(PA_80_MST2SST_CONFIG, ~(_BIT7 | _BIT2), _BIT2);

    // MST2SST Block Support SST Mode
    ScalerSetBit(PB5_02_STHD_CTRL_1, ~_BIT0, _BIT0);

    // Disable Generate Display Format
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT7, 0x00);

    // DP Display Format Generator Reset
    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT0, _BIT0);
    ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT0, 0x00);

    // Set Odd Field BS to VS Delay
    ScalerSetByte(PA_3A_OVBLK2VS_H, ScalerGetByte(PB5_35_OVBLK2VS_H));
    ScalerSetByte(PA_3B_OVBLK2VS_M, ScalerGetByte(PB5_36_OVBLK2VS_M));
    ScalerSetByte(PA_3C_OVBLK2VS_L, ScalerGetByte(PB5_37_OVBLK2VS_L));

    // Double Buffer to Apply Display Format Setting
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT6, _BIT6);

    // Set Even Field BS to VS Delay
    ScalerSetByte(PA_37_EVBLK2VS_H, ScalerGetByte(PB5_32_EVBLK2VS_H));
    ScalerSetByte(PA_38_EVBLK2VS_M, ScalerGetByte(PB5_33_EVBLK2VS_M));
    ScalerSetByte(PA_39_EVBLK2VS_L, ScalerGetByte(PB5_34_EVBLK2VS_L));

    //Set Htotal
    ScalerSetByte(PA_40_MN_DPF_HTT_M, ScalerGetByte(PB5_41_MN_DPF_HTT_M));
    ScalerSetByte(PA_41_MN_DPF_HTT_L, ScalerGetByte(PB5_42_MN_DPF_HTT_L));

    //Set Hstart
    ScalerSetByte(PA_42_MN_DPF_HST_M, ScalerGetByte(PB5_43_MN_DPF_HST_M));
    ScalerSetByte(PA_43_MN_DPF_HST_L, ScalerGetByte(PB5_44_MN_DPF_HST_L));

    //Set Hactive
    ScalerSetByte(PA_44_MN_DPF_HWD_M, ScalerGetByte(PB5_45_MN_DPF_HWD_M));
    ScalerSetByte(PA_45_MN_DPF_HWD_L, ScalerGetByte(PB5_46_MN_DPF_HWD_L));

    //Set HSW
    ScalerSetByte(PA_46_MN_DPF_HSW_M, ScalerGetByte(PB5_47_MN_DPF_HSW_M));
    ScalerSetByte(PA_47_MN_DPF_HSW_L, ScalerGetByte(PB5_48_MN_DPF_HSW_L));

    //Set Vtotal
    ScalerSetByte(PA_48_MN_DPF_VTT_M, ScalerGetByte(PB5_49_MN_DPF_VTT_M));
    ScalerSetByte(PA_49_MN_DPF_VTT_L, ScalerGetByte(PB5_4A_MN_DPF_VTT_L));

    //Set Vactive
    ScalerSetByte(PA_4C_MN_DPF_VHT_M, ScalerGetByte(PB5_4D_MN_DPF_VHT_M));
    ScalerSetByte(PA_4D_MN_DPF_VHT_L, ScalerGetByte(PB5_4E_MN_DPF_VHT_L));

    //Set Vstart
    ScalerSetByte(PA_4A_MN_DPF_VST_M, ScalerGetByte(PB5_4B_MN_DPF_VST_M));
    ScalerSetByte(PA_4B_MN_DPF_VST_L, ScalerGetByte(PB5_4C_MN_DPF_VST_L));

    //Set VSW
    ScalerSetByte(PA_4E_MN_DPF_VSW_M, ScalerGetByte(PB5_4F_MN_DPF_VSW_M) );
    ScalerSetByte(PA_4F_MN_DPF_VSW_L, ScalerGetByte(PB5_50_MN_DPF_VSW_L));

    // Set full last line Mode
    ScalerSetBit(PA_35_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

    // Double Buffer to Apply Display Format Setting
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT6, _BIT6);

    // Get color format and cplor depth
    pData[0] = ScalerGetBit(PB5_20_PG_CTRL_0, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set color format and cplor depth
    ScalerSetBit(PA_30_PG_CTRL_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[0]);

    // PLL Input Clock select to Link Clock, Output Clock Select to PLL Clock, Double Buffer.
    // ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

    if(ScalerGlobalGetIDCode() == _RL6432_VER_A_ID_CODE)
    {
        // PLL Input Clock select to Crystal Clock, Output Clock Select to PLL Clock, Double Buffer.
        ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6), 0x00);
    }
    else
    {
        // PLL Input Clock select to Link Clock/2, Output Clock Select to PLL Clock, Double Buffer.
        ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
    }

    // DPPLL Power Down
    ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Disable M/N Tracking
    // ScalerSetBit(PA_A7_MN_SCLKG_TRK_CTRL, ~_BIT7, 0x00);

    // Disable HSync Tracking
    ScalerSetBit(PA_A7_MN_SCLKG_TRK_CTRL, ~_BIT6, 0x00);

    // Set VCOMD, phase Swallow Circuit Clock Select, SCLKGSTOP
    ScalerSetBit(PA_BF_MN_SCLKG_PLL_WD, ~(0x7F), 0x16);

    // Set DPPLL Div_2 & Div_s
    ScalerSetByte(PA_A3_MN_SCLKG_DIVS, 0x00);

    // Set DPPLL Div_O.
    ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0), 0x00);

#if(_DP_FREESYNC_SUPPORT == _ON)
    ulDpNvidValue = ((((DWORD)ScalerGetByte(PB6_1D_MSA_NVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1E_MSA_NVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1F_MSA_NVID_2)));
#endif

    usDpHtotal = ((((WORD)ScalerGetByte(PB5_41_MN_DPF_HTT_M)) << 8) | ((WORD)ScalerGetByte(PB5_42_MN_DPF_HTT_L)));

    usDpVtotal = ((((WORD)ScalerGetByte(PB5_49_MN_DPF_VTT_M)) << 8) | ((WORD)ScalerGetByte(PB5_4A_MN_DPF_VTT_L)));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), 0x00);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Waiting for Measure Done
    ScalerTimerDelayXms(2);

    if(ScalerGetBit(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB_54_DP_SIG_DET_4));
    }
    else
    {
        if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = 0x4E20;
        }
        else if(ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
        {
            PDATA_WORD(0) = 0x2710;
        }
        else // Both Default && _DP_LINK_RBR Case
        {
            PDATA_WORD(0) = 0x1770;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

    if(ScalerGetBit(PA_A0_MN_SCLKG_CTRL, (_BIT7 | _BIT6)) == 0x00)
    {
        // PLL Reference Clock is GDI Clock (For 6432-A)
        ulXtal_clk = _GDI_CLK_KHZ;

        ucplln = 2;
    }
    else
    {
        // PLL Reference Clock is Lin_Clk/2 (For 6432-B ECO)
        ulXtal_clk = (PDATA_DWORD(0) / 1000 / 2);

        ucplln = (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) / 2);
    }

    // Measurement Enable
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB5_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The result
    SET_DP_RX0_MEASURE_POP_UP();

    ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB5_58_MN_MEAS_CTRL) & 0x1F)) << 16) | ((DWORD)ScalerGetByte(PB5_59_MN_MEAS_VLN_M) << 8) | ((DWORD)ScalerGetByte(PB5_5A_MN_MEAS_VLN_L)));

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MST_FREESYNC_ENABLED() == _TRUE)
    {
        ulDpMvidValue = ((((DWORD)ScalerGetByte(PB6_1A_MSA_MVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1B_MSA_MVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1C_MSA_MVID_2)));

        // Calculate streamclk
        ulStreamClkValue = ((DWORD)ulDpMvidValue * (PDATA_DWORD(0) / ulDpNvidValue) + (PDATA_DWORD(0) % ulDpNvidValue * 100 / ulDpNvidValue * (DWORD)ulDpMvidValue / 100));
    }
    else
#endif

    {
    // Calculate streamclk (Unit is Hz)
    ulStreamClkValue = (((((DWORD)usDpHtotal) * ((DWORD)usDpVtotal) * 100) / ulVBs2BsCount) * _GDI_CLK_KHZ * 10);
    }

    ulpllm = ((((ulStreamClkValue / 4) * ucdiv_divs * ucdiv_pllo) * ucplln / 250) / (ulXtal_clk));

    // offset = (f - m/n*f_ref)/(m/n*f_ref)*2^21
    // seperate *2^21 to *32*16384*4
    lOffsetValue = ((SDWORD)(ulStreamClkValue * ucdiv_pllo * ucdiv_divs) - (SDWORD)((ulXtal_clk * 1000 / ucplln) * ulpllm)) * 32 / ulpllm * ucplln / ulXtal_clk * 16384 / 1000 * 4;

    // Offset Value Setting
    ScalerSetByte(PA_A6_MN_SCLKG_OFFS_L, lOffsetValue & 0xFF);
    ScalerSetByte(PA_A5_MN_SCLKG_OFFS_M, (lOffsetValue >> 8) & 0xFF);
    ScalerSetBit(PA_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 |_BIT0), (lOffsetValue >> 16) & 0x07);

    // Enable phase swallow
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), _BIT4);

    // Set DPPLL M Code
    ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), ((ulpllm - 2) >> 8));
    ScalerSetByte(PA_A1_MN_SCLKG_DIVM, ((ulpllm - 2) & 0xFF));

    // Set DPPLL N Code
    ScalerSetByte(PA_A2_MN_SCLKG_DIVN, ucplln - 2);

    // Load offset value
    ScalerSetBit(PA_A4_MN_SCLKG_OFFS_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

    // Double Buffer for M/N Tracking
    ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(PA_C0_MN_SCLKG_PLL_INSEL, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL Power On
    ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~_BIT7, 0x00);

    ScalerSetBit(PA_C0_MN_SCLKG_PLL_INSEL, ~(_BIT5 | _BIT4),(ScalerGetByte(PB5_C0_MN_SCLKG_PLL_INSEL) & (_BIT5 | _BIT4)));

    // Set PLL Charge Pump Current
    ScalerSetByte(PA_BE_MN_SCLKG_PLL_CHP, ScalerGetByte(PB5_BE_MN_SCLKG_PLL_CHP));
/*
    ScalerSetBit(PA_A8_MN_SCLKG_TRK_MN_I_H, ~(_BIT2 | _BIT1 | _BIT0), (ScalerGetByte(PB5_A8_MN_SCLKG_TRK_MN_I_H) & 0x03));
    ScalerSetByte(PA_A9_MN_SCLKG_TRK_MN_I_M, ScalerGetByte(PB5_A9_MN_SCLKG_TRK_MN_I_M));
    ScalerSetByte(PA_AA_MN_SCLKG_TRK_MN_I_L, ScalerGetByte(PB5_AA_MN_SCLKG_TRK_MN_I_L));

    // Set P Code
    ScalerSetBit(PA_AB_MN_SCLKG_TRK_MN_P_H, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetByte(PA_AC_MN_SCLKG_TRK_MN_P_M, 0xFF);
    ScalerSetByte(PA_AD_MN_SCLKG_TRK_MN_P_L, 0xFF);

    // Set I/P Code
    ScalerSetByte(PA_B1_MN_SCLKG_TRK_VS_I_M, 0x00);
    ScalerSetByte(PA_B2_MN_SCLKG_TRK_VS_I_L, 0x1F);
    ScalerSetByte(PA_B4_MN_SCLKG_TRK_VS_P_M, 0x1F);
    ScalerSetByte(PA_B5_MN_SCLKG_TRK_VS_P_L, 0xFF);

    // Set Tracking Freq
    ScalerSetBit(PA_A8_MN_SCLKG_TRK_MN_I_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4),  0x00);
*/
    // Disable Tracking New Mode
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~(_BIT2 | _BIT1), _BIT1);

    // Set Initial I/P Code
    ScalerSetByte(PA_B1_MN_SCLKG_TRK_VS_I_M, 0x00);
    ScalerSetByte(PA_B2_MN_SCLKG_TRK_VS_I_L, 0x04);
    ScalerSetByte(PA_B3_MN_SCLKG_TRK_VS_P_H, 0x07);
    ScalerSetByte(PA_B4_MN_SCLKG_TRK_VS_P_M, 0xFF);
    ScalerSetByte(PA_B5_MN_SCLKG_TRK_VS_P_L, 0xFF);

    // Set Tracking Freq
    ScalerSetBit(PA_A8_MN_SCLKG_TRK_MN_I_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ScalerGetByte(PB5_A8_MN_SCLKG_TRK_MN_I_H) & 0xF0));

    // Set Tracking Lock PE
    ScalerSetByte(PA_B7_MN_SCLKG_TRK_VS_NLOCK, 0x7F);

    // Enable H Sync Tracking
    ScalerSetByte(PA_A7_MN_SCLKG_TRK_CTRL, 0x58);

    // Double Buffer for H Sync Tracking
    ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // Set Final I/P Code
    ScalerSetByte(PA_B1_MN_SCLKG_TRK_VS_I_M, 0x00);
    ScalerSetByte(PA_B2_MN_SCLKG_TRK_VS_I_L, 0x02);
    // ScalerSetByte(PA_B3_MN_SCLKG_TRK_VS_P_H, 0x00);
    // ScalerSetByte(PA_B4_MN_SCLKG_TRK_VS_P_M, 0x1F);
    // ScalerSetByte(PA_B5_MN_SCLKG_TRK_VS_P_L, 0xFF);

    // Enable Tracking New Mode
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~_BIT2, _BIT2);

    ScalerSetByte(PA_C2_HS_TRACKING_NEW_MODE1, ScalerGetByte(PB5_C2_HS_TRACKING_NEW_MODE1));
    ScalerSetByte(PA_C3_HS_TRACKING_NEW_MODE2, ScalerGetByte(PB5_C3_HS_TRACKING_NEW_MODE2));

    // Start Generate Display Format
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT7, _BIT7);

    ScalerTimerDelayXms(10);

    if(ScalerDpRx0MstToSstFifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
    {
        DebugMessageQC("5. D0 MST2SST FIFO Failed", 0);

        return _FALSE;
    }

    // DP MST2SST RGB Output Enable
    ScalerSetBit(PA_36_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // DP MST2SST CLK Output Enable
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, _BIT6);

    DebugMessageQC("5. D0 MST2SST FIFO Pass", 0);
    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : D1 DP Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if((_DP_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
bit ScalerQCD1DpTest(void)
{
    BYTE ucResult = 0;

    // =====================Test for Audio buf BIST=======================
    // Enable bist clock
    ScalerSetBit(PB9_4E_SRAM_BIST_0, ~_BIT7, _BIT7);

    // Bist Reset
    ScalerSetBit(PB9_4E_SRAM_BIST_0, ~_BIT2, _BIT2);
    ScalerSetBit(PB9_4E_SRAM_BIST_0, ~_BIT2, 0x00);

    // Enable Bist
    ScalerSetBit(PB9_4E_SRAM_BIST_0, ~_BIT3, _BIT3);


    // Wait Video Bist Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB9_4E_SRAM_BIST_0, _BIT1, _BIT1) == _TRUE)
    {
        // Get Bist Result
        if(ScalerGetBit(PB9_4E_SRAM_BIST_0, _BIT0) == _BIT0)
        {
            DebugMessageQC("5. DP1 Abuf Bist Fail1", 0x00);
            ucResult |= _BIT7;
        }
    }
    else
    {
        DebugMessageQC("5. DP1 Abuf Bist Fail2", 0x00);
        ucResult |= _BIT7;
    }

    // =====================Test for Audio buf DRF BIST=======================
    // Bist Reset
    ScalerSetByte(PB9_4E_SRAM_BIST_0, 0x80);

    ScalerSetBit(PB9_4E_SRAM_BIST_0, ~_BIT2, _BIT2);
    ScalerSetBit(PB9_4E_SRAM_BIST_0, ~_BIT2, 0x00);

    // Enable DRF Bist
    ScalerSetBit(PB9_4F_SRAM_BIST_1, ~_BIT4, _BIT4);

    ScalerSetByte(PB9_4E_SRAM_BIST_0, 0x80);

    // Wait DRF Srart Pause
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB9_4F_SRAM_BIST_1, _BIT2, _BIT2) == _TRUE)
    {
        // Wait Random Time
        for(pData[0] = 0; pData[0] < 10; pData[0]++)
        {
            DELAY_20US();
        }

        // Test Resume time
        ScalerSetBit(PB9_4F_SRAM_BIST_1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        ScalerSetBit(PB9_4F_SRAM_BIST_1, ~(_BIT4 | _BIT3), _BIT4);

        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB9_4F_SRAM_BIST_1, _BIT2, _BIT2) == _TRUE)
        {
            // Wait Random Time
            for(pData[0] = 0; pData[0] < 10; pData[0]++)
            {
                DELAY_20US();
            }

            // TEST RESUME pulse for negative checkerboard
            ScalerSetBit(PB9_4F_SRAM_BIST_1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            ScalerSetBit(PB9_4F_SRAM_BIST_1, ~(_BIT4 | _BIT3), _BIT4);

            // Wait DRF Bist Done
            if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB9_4F_SRAM_BIST_1, _BIT1, _BIT1) == _TRUE)
            {
                // Get Bist Result
                if(ScalerGetBit(PB9_4F_SRAM_BIST_1, _BIT0) == _BIT0)
                {
                    DebugMessageQC("5. DP1 Abuf DRF Bist Fail1", 0x00);
                    ucResult |= _BIT6;
                }
            }
            else
            {
                DebugMessageQC("5. DP1 Abuf DRF Bist Fail2", 0x00);
                ucResult |= _BIT6;
            }
        }
        else
        {
            DebugMessageQC("5. DP1 Abuf DRF Bist Fail3", 0x00);
            ucResult |= _BIT6;
        }
    }
    else
    {
        DebugMessageQC("5. DP1 Abuf DRF Bist Fail4", 0x00);
        ucResult |= _BIT6;
    }

    // Disable DRF Bist
    ScalerSetBit(PB9_4F_SRAM_BIST_1, ~_BIT4, 0x00);

    // =====================Test for D1 Video buf BIST=======================
    // Enable bist clock
    ScalerSetBit(PB8_25_SRAM_BIST_0, ~_BIT7, _BIT7);

    // Bist Reset
    ScalerSetBit(PB8_25_SRAM_BIST_0, ~_BIT2, _BIT2);
    ScalerSetBit(PB8_25_SRAM_BIST_0, ~_BIT2, 0x00);

    // Enable Bist
    ScalerSetBit(PB8_25_SRAM_BIST_0, ~_BIT3, _BIT3);

    // Wait Video Bist Done
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB8_25_SRAM_BIST_0, _BIT1, _BIT1) == _TRUE)
    {
        // Get Bist Result
        if(ScalerGetBit(PB8_25_SRAM_BIST_0, _BIT0) == _BIT0)
        {
            DebugMessageQC("5. DP1 Vbuf Bist Fail1", 0x00);
            ucResult |= _BIT5;
        }
    }
    else
    {
        DebugMessageQC("5. DP1 Vbuf Bist Fail2", 0x00);
        ucResult |= _BIT5;
    }

    // =====================Test for D1 Video buf DRF BIST=======================
    // Bist Reset
    ScalerSetByte(PB8_25_SRAM_BIST_0, 0x80);
    ScalerSetBit(PB8_25_SRAM_BIST_0, ~_BIT2, _BIT2);
    ScalerSetBit(PB8_25_SRAM_BIST_0, ~_BIT2, 0x00);

    // Enable DRF Bist
    ScalerSetBit(PB8_26_SRAM_BIST_1, ~_BIT4, _BIT4);

    // Wait DRF Srart Pause
    if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB8_26_SRAM_BIST_1, _BIT2, _BIT2) == _TRUE)
    {
        // Wait Random Time
        for(pData[0] = 0; pData[0] < 10; pData[0]++)
        {
            DELAY_20US();
        }

        // Test Resume time
        ScalerSetBit(PB8_26_SRAM_BIST_1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        ScalerSetBit(PB8_26_SRAM_BIST_1, ~(_BIT4 | _BIT3), _BIT4);

        if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB8_26_SRAM_BIST_1, _BIT2, _BIT2) == _TRUE)
        {
            // Wait Random Time
            for(pData[0] = 0; pData[0] < 10; pData[0]++)
            {
                DELAY_20US();
            }

            // TEST RESUME pulse for negative checkerboard
            ScalerSetBit(PB8_26_SRAM_BIST_1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            ScalerSetBit(PB8_26_SRAM_BIST_1, ~(_BIT4 | _BIT3), _BIT4);

            // Wait DRF Bist Done
            if(ScalerTimerPollingFlagProc(_BIST_TIMEOUT, PB8_26_SRAM_BIST_1, _BIT1, _BIT1) == _TRUE)
            {
                // Get Bist Result
                if(ScalerGetBit(PB8_26_SRAM_BIST_1, _BIT0) == _BIT0)
                {
                    DebugMessageQC("5. DP1 Vbuf DRF Bist Fail1", 0x00);
                    ucResult |= _BIT4;
                }
            }
            else
            {
                DebugMessageQC("5. DP1 Vbuf DRF Bist Fail2", 0x00);
                ucResult |= _BIT4;
            }
        }
        else
        {
            DebugMessageQC("5. DP1 Vbuf DRF Bist Fail3", 0x00);
            ucResult |= _BIT4;
        }
    }
    else
    {
        DebugMessageQC("5. DP1 Vbuf DRF Bist Fail4", 0x00);
        ucResult |= _BIT4;
    }

    // Disable DRF Bist
    ScalerSetBit(PB8_26_SRAM_BIST_1, ~_BIT4, 0x00);

    ScalerSetBit(0x0A90, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

    // =====================Test for DP CRC=======================
    // Reserved for DP Test
    ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT7 | _BIT5), 0x00);
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerSetBit(PB8_70_DP_CRC_CTRL, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));
    if(ScalerTimerPollingFlagProc(120, PB8_70_DP_CRC_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        DebugMessageQC("5. DP CRC Calculation Timeout", 0x00);
        ucResult |= _BIT0;
    }
    else
    {
        if((ScalerGetByte(PB8_71_DP_CRC_R_M) != _DP_CRC0) || (ScalerGetByte(PB8_72_DP_CRC_R_L) != _DP_CRC1) || \
           (ScalerGetByte(PB8_73_DP_CRC_G_M) != _DP_CRC2) || (ScalerGetByte(PB8_74_DP_CRC_G_L) != _DP_CRC3) || \
           (ScalerGetByte(PB8_75_DP_CRC_B_M) != _DP_CRC4) || (ScalerGetByte(PB8_76_DP_CRC_B_L) != _DP_CRC5))
        {
            DebugMessageQC("5. DP CRC Value Mismatch", 0x00);
            ucResult |= _BIT0;
        }
    }

    if((bit)ucResult == 0x00)
    {
        DebugMessageQC("6. DP Test PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. DP Fail Mode", ucResult);
        DebugMessageQC("6. DP Test FAIL", 0x00);
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
    ScalerSetByte(P31_A0_I_DB_CTRL0, 0x00);
    ScalerSetByte(P31_A1_I_DB_CTRL1, 0x00);
    ScalerSetByte(P31_B0_D_DB_CTRL0, 0x00);
    ScalerSetByte(P31_C0_I_DB_CTRL, 0x00);
    ScalerSetByte(P31_C1_D_DB_CTRL, 0x00);

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
    ScalerSetBit(P11_A1_I_DLTI_CTRL_M1, ~_BIT0, 0x00);  // Disable IDLTI
    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, 0x00);   // Disable I-Dither

    ScalerSetByte(P0_23_SCALE_DOWN_CTRL_M1, 0x00); // Disable SD
    ScalerSetByte(P0_32_SCALE_CONTROL_REG, 0x00); // Disable SU

    //--------------------D Domain------------------//
    ScalerQCHighlightWindowOff();                       // Disable Highlight Window
    ScalerQCDDomainPatternGenOff();                     // Disable D Domain Pattern Generator

    ScalerSetBit(P14_C0_LSR_CTRL, ~_BIT7, 0x00);        // Disable LSR
    ScalerSetBit(P12_A0_SR_SHP_CTRL_0, ~_BIT7, 0x00);   // Disable SHP
    ScalerSetByte(P14_A1_SR_YCC2RGB_CTRL, 0x00);        // Disable D-ColorConv
    ScalerSetBit(P7_D8_DCR_ADDRESS_PORT, ~_BIT0, 0x00); // Disable DCR
    ScalerSetBit(P7_C7_DCC_CTRL_0, ~_BIT7, 0x00);       // Disable DCC
    ScalerSetBit(P7_D0_ICM_CONTROL, ~(_BIT7), 0x00);    // Disable ICM
    ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT1, 0x00);        // Disable Contrast
    ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT0, 0x00);        // Disable Brightness
    ScalerSetBit(P7_E0_IAPS_GAIN_CTRL_M1, ~_BIT0, 0x00);          // Disable IAPSGain
    ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT7, 0x00);            // Disable 3DGamma
    ScalerSetBit(P9_A1_INPUT_GAMMA_CTRL, ~_BIT6, 0x00);             // Disable I-Gamma
    ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT2, 0x00);        // Dialbe SRGB
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~_BIT7, 0x00);              // Disable Panel Uniformity
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT6, 0x00);              // Diable O-Gamma
    ScalerSetBit(P0_6A_D_DITHER_COMMON_CTRL1, ~_BIT5, 0x00);        // Disable D-Dither
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);           // Disable OD
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit ScalerQCWaitForIDDomainEvent(EnumWaitEventType enumEvent, BYTE ucDataPath)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;
    WORD usEventFlagAddr = 0;

    switch(enumEvent)
    {
        case _EVENT_IVS:
        case _EVENT_IEN_START:
        case _EVENT_IEN_STOP:
            switch((EnumInputDataPath)ucDataPath)
            {
                case _INPUT_PATH_M1:
                    usEventFlagAddr = P0_03_STATUS1;
                    break;
/*
                case _INPUT_PATH_M1_M2: // EO
                    if(enumEvent == _EVENT_IEN_START)
                    {
                        usEventFlagAddr = P0_03_STATUS1;
                    }
                    else
                    {
                        usEventFlagAddr = P40_03_M2_STATUS1;
                    }
                    break;

                case _INPUT_PATH_M2:
                    usEventFlagAddr = P40_03_M2_STATUS1;
                    break;

                case _INPUT_PATH_S1:
                    usEventFlagAddr = P80_03_S1_STATUS1;
                    break;

                case _INPUT_PATH_S1_S2: // EO
                    if(enumEvent == _EVENT_IEN_START)
                    {
                        usEventFlagAddr = P80_03_S1_STATUS1;
                    }
                    else
                    {
                        usEventFlagAddr = PC0_03_S2_STATUS1;
                    }
                    break;

                case _INPUT_PATH_S2:
                    usEventFlagAddr = PC0_03_S2_STATUS1;
                    break;
*/
                case _INPUT_PATH_ALL: // All Path use one source, only for QC
                    usEventFlagAddr = P0_03_STATUS1;
                    break;

                default:
                    return _FALSE;
            }

            break;

        case _EVENT_DVS:
            if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00)
            {
                // Display format gen disabled
                return _FALSE;
            }
            usEventFlagAddr = P0_03_STATUS1; // Only Total DVS
            break;

        case _EVENT_DEN_START:
        case _EVENT_DEN_STOP:
            if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00)
            {
                // Display format gen disabled
                return _FALSE;
            }

            usEventFlagAddr = P0_05_IRQ_CTRL1; // Total DEN
            if(enumEvent == _EVENT_DEN_START)
            {
                enumEvent = _BIT2;
            }
            else
            {
                enumEvent = _BIT4;
            }

            break;

        default:
            return _FALSE;
    }

    // Clear status (status register will be cleared after write)
    ScalerSetByte(usEventFlagAddr, _EVENT_ALL);

    usPreviousTime = g_usTimerCounter;

    do
    {
        if((ScalerGetByte(usEventFlagAddr) & enumEvent) == enumEvent)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while(usTimeElapsed <= 120);

    return _FALSE;
}
#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)

