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
// ID Code      : RL6492_Series_QC_Main.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_QC_MAIN__

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
//RLE0638
#define _DP_CRC0                                0x65
#define _DP_CRC1                                0xBD
#define _DP_CRC2                                0xD8
#define _DP_CRC3                                0x22
#define _DP_CRC4                                0xB4
#define _DP_CRC5                                0x24
#endif


/*
// VG870
#define _DP_CRC0                                0x65
#define _DP_CRC1                                0xBD
#define _DP_CRC2                                0xD8
#define _DP_CRC3                                0x22
#define _DP_CRC4                                0xB4
#define _DP_CRC5                                0x24
#endif
*/

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
// HDMI Port 1920 x 1080 @ 60Hz, 12bpc
//----------------------------------------------------------------------------
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
// VG870
#define _HDMI_CRC0               0x3A
#define _HDMI_CRC1               0xCD
#define _HDMI_CRC2               0xB3
#define _HDMI_CRC3               0x6A
#define _HDMI_CRC4               0xA8
#define _HDMI_CRC5               0x69


/*
// RLE0638
#define _HDMI_CRC0               0x9F
#define _HDMI_CRC1               0x15
#define _HDMI_CRC2               0x64
#define _HDMI_CRC3               0x00
#define _HDMI_CRC4               0x00
#define _HDMI_CRC5               0x00
*/
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


//----------------------------------------------------------------------------
// Macro of EQC Switch Control
//----------------------------------------------------------------------------
#define bEQC_SWITCH_CONTROL1                    _PIN_15_MCU_REG
#define bEQC_SWITCH_CONTROL2                    _PIN_16_MCU_REG

#define _EQC_SWITCH_DP                          0
#define _EQC_SWITCH_USB1                        1
#define _EQC_SWITCH_USB2                        2

#define PCB_EQC_SWITCH(x)                       {\
                                                    if((x) == _EQC_SWITCH_DP)\
                                                    {\
                                                        bEQC_SWITCH_CONTROL1 = 0;\
                                                    }\
                                                    else if((x) == _EQC_SWITCH_USB1)\
                                                    {\
                                                        bEQC_SWITCH_CONTROL1 = 1;\
                                                        bEQC_SWITCH_CONTROL2 = 0;\
                                                    }\
                                                    else if((x) == _EQC_SWITCH_USB2)\
                                                    {\
                                                        bEQC_SWITCH_CONTROL1 = 1;\
                                                        bEQC_SWITCH_CONTROL2 = 1;\
                                                    }\
                                                }

//----------------------------------------------------------------------------
// Macro of EQC BillBord Test
//----------------------------------------------------------------------------
#define bBB_START                               _PIN_30_MCU_REG
#define bBB_RESULT                              _PIN_32_MCU_REG

#define PCB_BB_START_DETECT()                   (bBB_START)
#define PCB_BB_RESULT_DETECT()                  (bBB_RESULT)

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
DWORD ScalerQCA0PortTest(void);
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
BYTE ScalerQCD0PortTest(void);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
WORD ScalerQCD1PortTest(void);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
BYTE ScalerQCD2PortTest(void);
#endif

#if(_D0_HDMI_SUPPORT == _ON)
bit ScalerQCD0HdmiTest(void);
#endif

#if(_D1_HDMI_SUPPORT == _ON)
bit ScalerQCD1HdmiTest(void);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
bit ScalerQCD2HdmiTest(void);
#if(_AUDIO_SUPPORT == _ON)
bit ScalerQCD2AudioTest(void);
extern void ScalerAudioD0HDMIAudioInitial(void);
extern EnumAudioSamplingFreqPacket ScalerAudioSamplingFreqDetect(BYTE ucInputPort);
#endif
#endif

#if((_DP_SUPPORT == _ON) && (_D0_DP_EXIST == _ON))
bit ScalerQCD0DpTest(void);
#endif

#if((_DP_SUPPORT == _ON) && (_D1_DP_EXIST == _ON))
bit ScalerQCD1DpTest(void);
#endif

#if((_DP_SUPPORT == _ON) && (_D2_DP_EXIST == _ON))
bit ScalerQCD2DpTest(void);
#endif

bit ScalerQCU3UfpTest(void);
bit ScalerQCU3DfpTest(void);
bit ScalerQCUSBBillBoardTest(void);
bit ScalerQCUSBTypeCTest(void);

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
DWORD ScalerQCA0PortTest(void)
{
    BYTE ucResult0 = 0x00;
    BYTE ucResult1 = 0x00;
    BYTE ucResult2 = 0x00;
    BYTE ucResult3 = 0x00;

    // Initail Setting
    ScalerSetByte(P10_15_PIN_SHARE_CTRL15__ON1, 0x01);
    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON1, 0x01);
    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__ON1, 0x00);
    ScalerSetByte(P10_32_PIN_SHARE_CTRL32__ON1, 0x00);
    PCB_EQC_SWITCH(_EQC_SWITCH_DP);

    // Result0
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
    ucResult0 = (ucResult0 | ((BYTE)ScalerQCDDRTest()));
#else
    ucResult0 = (ucResult0 | ((BYTE)ScalerQCSDRAMTest()));
#endif

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCODTest() << 1));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCFRCTest() << 2));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCRotationTest() << 3));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCADCNRTest() << 4));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCRingingFilterTest() << 5));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCDigitalFilterTest() << 6));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCScaleUpTest() << 7));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    // Result1
    ucResult1 = (ucResult1 | ((BYTE)ScalerQCLSRTest() << 0));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCOSDTest() << 1));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCBistTest() << 2));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQC422to444Test() << 3));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCVGAPGTest() << 4));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCDDomainColorConvTest() << 5));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCSHPTest() << 6));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCHLWTest() << 7));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    // Result2
    ucResult2 = (ucResult2 | (BYTE)ScalerQCDPGTest());

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCDPGRandomTest() << 1));

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | (BYTE)ScalerQCDCRTest() << 2);

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | (BYTE)ScalerQCDCCTest() << 3);

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | (BYTE)ScalerQCICMTest() << 4);

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCCTSBRITest() << 5));

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCIAPSGainTest() << 6));

    if(ucResult2 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    // ucResult3
    ucResult3 = (ucResult3 | ((BYTE)ScalerQCDDitherTest()));

    if(ucResult3 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    ucResult3 = (ucResult3 | ((BYTE)ScalerQCBackGroundColor() << 1));

    if(ucResult3 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    return ((DWORD)ucResult0 | ((DWORD)ucResult1 << 8) | ((DWORD)ucResult2 << 16) | ((DWORD)ucResult3 << 24));
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
    BYTE ucResult0 = 0x00;

ucResult0 = (ucResult0 | ((BYTE)ScalerQCUSBTypeCTest() << 0));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
    ucResult0 = (ucResult0 | ((BYTE)ScalerQCD0HdmiTest()) << 1));
#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ucResult0 = (ucResult0 | ((BYTE)ScalerQCD0DpTest() << 1));
#endif

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCU3UfpTest() << 2));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCU3DfpTest() << 3));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCUSBBillBoardTest() << 4));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    return ucResult0;
}
#endif  // End of #if(_D0_INPUT_PORT_TYPE != D0_NO_PORT)

//--------------------------------------------------
// Description  : Test Process for D1 Port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
WORD ScalerQCD1PortTest(void)
{
    BYTE ucResult0 = 0x00;
    BYTE ucResult1 = 0x00;

#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
    ucResult0 |= (ucResult0 | (BYTE)ScalerQCD1HdmiTest());
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ucResult0 |= (ucResult0 | (BYTE)ScalerQCD1DpTest());
#endif

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCFormatConversionTest() << 1));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIPGTest() << 2));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIDomainColorConvTest() << 3));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIDLTITest() << 4));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIDitherTest() << 5));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCScaleDownTest() << 6));


    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    // ucResult1
    ucResult1 = (ucResult1 | ((BYTE)ScalerQC3DGammaTest()));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCRGBGammaTest() << 1));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCGammaTest() << 2));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCPCMTest() << 3));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCsRGBTest() << 4));

    if(ucResult1 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    return ((WORD)ucResult0 | (WORD)ucResult1 << 8);
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
    BYTE ucResult0 = 0x00;

#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
    ucResult0 |= (ucResult0 | (BYTE)ScalerQCD2HdmiTest());
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    ucResult0 |= (ucResult0 | (BYTE)ScalerQCD2DpTest());
#endif

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

#if(_AUDIO_SUPPORT == _ON)
    ucResult0 = (ucResult0 | ((BYTE)ScalerQCD2AudioTest() << 1));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }
#endif

    // LVDS QC Test
    ucResult0 = (ucResult0 | ((BYTE)ScalerQCDSPCTest() << 2));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCeDPTXTest() << 3));

    if(ucResult0 != 0x00)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    return ucResult0;

}
#endif  // End of #if(_D2_INPUT_PORT_TYPE != D2_NO_PORT)


//--------------------------------------------------
// Description  : D0 Hdmi Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if(_D0_HDMI_SUPPORT == _ON)
bit ScalerQCD0HdmiTest(void)
{
    return 0;
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

            break;

        case _HDMI_CRC4:

            if((pData[0] == _HDMI_CRC4) && (pData[1] == _HDMI_CRC5) && (pData[2] == _HDMI_CRC0) &&
               (pData[3] == _HDMI_CRC1) && (pData[4] == _HDMI_CRC2) && (pData[5] == _HDMI_CRC3))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            break;

        case _HDMI_CRC5:

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

//--------------------------------------------------
// Description  : D2 Hdmi Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if(_D2_HDMI_SUPPORT == _ON)
bit ScalerQCD2HdmiTest(void)
{
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

            break;

        case _HDMI_CRC4:

            if((pData[0] == _HDMI_CRC4) && (pData[1] == _HDMI_CRC5) && (pData[2] == _HDMI_CRC0) &&
               (pData[3] == _HDMI_CRC1) && (pData[4] == _HDMI_CRC2) && (pData[5] == _HDMI_CRC3))
            {
                DebugMessageQC("6. HDMI Test Pass", 0x00);
                return _TEST_PASS;
            }

            break;

        case _HDMI_CRC5:

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

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Test Process for Audio D2 port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
bit ScalerQCD2AudioTest(void)
{
#if(_D2_HDMI_SUPPORT == _ON)

    ScalerAudioD0HDMIAudioInitial();

    ScalerTimerDelayXms(5);

    if(ScalerAudioSamplingFreqDetect(_D2_INPUT_PORT) == _AUDIO_FREQ_PACKET_48K)
    {
        // Clear HDMI audio FIFO overflow and underflow status
        ScalerSetBit(P2_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        ScalerTimerDelayXms(5);

        // Check HDMI audio FIFO overflow and underflow
        if(ScalerGetBit(P2_CB_HDMI_SR, (_BIT2 | _BIT1)) == 0x00)
        {
            DebugMessageQC("6. Audio Test Pass", 0x00);

            return _TEST_PASS;
        }
    }
#endif

    DebugMessageQC("6. Audio Test Fail", 0x00);

    return _TEST_FAIL;
}
#endif

#endif

//--------------------------------------------------
// Description  : D0 DP Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if((_DP_SUPPORT == _ON) && (_D0_DP_EXIST == _ON))
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
    ScalerSetByte(PB6_4F_SRAM_BIST_1, 0x00);
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
        if((ScalerGetByte(PB5_71_DP_CRC_R_M) != _DP_CRC0) || (ScalerGetByte(PB5_72_DP_CRC_R_L) != _DP_CRC1) ||
           (ScalerGetByte(PB5_73_DP_CRC_G_M) != _DP_CRC2) || (ScalerGetByte(PB5_74_DP_CRC_G_L) != _DP_CRC3) ||
           (ScalerGetByte(PB5_75_DP_CRC_B_M) != _DP_CRC4) || (ScalerGetByte(PB5_76_DP_CRC_B_L) != _DP_CRC5))
        {
            DebugMessageQC("5. DP CRC Value Mismatch", 0x00);
            ucResult |= _BIT0;
        }
    }

    if((bit)ucResult == 0x00)
    {
        DebugMessageQC("6. DP0 Test PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("5. DP0 Check CRC0", ScalerGetByte(PB5_71_DP_CRC_R_M));
        DebugMessageQC("5. DP0 Check CRC1", ScalerGetByte(PB5_72_DP_CRC_R_L));
        DebugMessageQC("5. DP0 Check CRC2", ScalerGetByte(PB5_73_DP_CRC_G_M));
        DebugMessageQC("5. DP0 Check CRC3", ScalerGetByte(PB5_74_DP_CRC_G_L));
        DebugMessageQC("5. DP0 Check CRC4", ScalerGetByte(PB5_75_DP_CRC_B_M));
        DebugMessageQC("5. DP0 Check CRC5", ScalerGetByte(PB5_76_DP_CRC_B_L));

        DebugMessageQC("6. DP0 Fail Mode", ucResult);
        DebugMessageQC("6. DP0 Test FAIL", 0x00);
        return _TEST_FAIL;
    }
}
#endif

//--------------------------------------------------
// Description  : D1 DP Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if((_DP_SUPPORT == _ON) && (_D1_DP_EXIST == _ON))
bit ScalerQCD1DpTest(void)
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
    ScalerSetByte(PB6_4F_SRAM_BIST_1, 0x00);
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
    ScalerSetBit(PB6_4F_SRAM_BIST_1, ~_BIT4, 0x00);

    // =====================Test for D0 Video buf BIST=======================
    // Enable bist clock
    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT7, _BIT7);

    // Bist Reset
    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT2, _BIT2);
    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT2, 0x00);

/*
    while(ScalerGetByte(0x0006) == 0x00)
    {
        ScalerDebug();
    }
*/

    // Enable Bist
    ScalerSetBit(PB5_25_SRAM_BIST_0, ~_BIT3, _BIT3);

    // Wait Video Bist Done
    if(ScalerTimerPollingFlagProc(500, PB5_25_SRAM_BIST_0, _BIT1, _BIT1) == _TRUE)
    {
        // Get Bist Result
        if(ScalerGetBit(PB5_25_SRAM_BIST_0, _BIT0) == _BIT0)
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
        if((ScalerGetByte(PB5_71_DP_CRC_R_M) != _DP_CRC0) || (ScalerGetByte(PB5_72_DP_CRC_R_L) != _DP_CRC1) ||
           (ScalerGetByte(PB5_73_DP_CRC_G_M) != _DP_CRC2) || (ScalerGetByte(PB5_74_DP_CRC_G_L) != _DP_CRC3) ||
           (ScalerGetByte(PB5_75_DP_CRC_B_M) != _DP_CRC4) || (ScalerGetByte(PB5_76_DP_CRC_B_L) != _DP_CRC5))
        {
            DebugMessageQC("5. DP CRC Value Mismatch", 0x00);
            ucResult |= _BIT0;
        }
    }

    if((bit)ucResult == 0x00)
    {
        DebugMessageQC("6. DP1 Test PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("5. DP1 Check CRC0", ScalerGetByte(PB5_71_DP_CRC_R_M));
        DebugMessageQC("5. DP1 Check CRC1", ScalerGetByte(PB5_72_DP_CRC_R_L));
        DebugMessageQC("5. DP1 Check CRC2", ScalerGetByte(PB5_73_DP_CRC_G_M));
        DebugMessageQC("5. DP1 Check CRC3", ScalerGetByte(PB5_74_DP_CRC_G_L));
        DebugMessageQC("5. DP1 Check CRC4", ScalerGetByte(PB5_75_DP_CRC_B_M));
        DebugMessageQC("5. DP1 Check CRC5", ScalerGetByte(PB5_76_DP_CRC_B_L));

        DebugMessageQC("6. DP1 Fail Mode", ucResult);
        DebugMessageQC("6. DP1 Test FAIL", 0x00);
        return _TEST_FAIL;
    }
}
#endif

//--------------------------------------------------
// Description  : D2 DP Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if((_DP_SUPPORT == _ON) && (_D2_DP_EXIST == _ON))
bit ScalerQCD2DpTest(void)
{
    return _TEST_FAIL;
}
#endif
//--------------------------------------------------
// Description  : U3 UFP
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
bit ScalerQCU3UfpTest(void)
{
    PCB_EQC_SWITCH(_EQC_SWITCH_USB1);

    PCB_EQC_SWITCH(_EQC_SWITCH_USB2);

    return _TEST_FAIL;
}

//--------------------------------------------------
// Description  : U3 DFP
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
bit ScalerQCU3DfpTest(void)
{
    return _TEST_FAIL;
}

//--------------------------------------------------
// Description  : USB Bill Board
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
bit ScalerQCUSBBillBoardTest(void)
{
    return _TEST_FAIL;
}

//--------------------------------------------------
// Description  : USB TypeC
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
bit ScalerQCUSBTypeCTest(void)
{
    return _TEST_FAIL;
}

//--------------------------------------------------
// Description  : Disable All Digital Function & Watch Dog
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCAllDigitalFunctionDisable(void)
{
    BYTE ucCtrlReg = 0;

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
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));
    ucCtrlReg = ScalerGetByte(P0_99_DIGITAL_FILTER_PORT);
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));
    ScalerSetByte(P0_99_DIGITAL_FILTER_PORT, (ucCtrlReg & (~(_BIT7 | _BIT6 | _BIT5))));

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
    ScalerSetBit(P9_A1_INPUT_GAMMA_CTRL_SETA, ~_BIT6, 0x00);             // Disable I-Gamma
    ScalerSetBit(P0_62_SRGB_CTRL, ~_BIT2, 0x00);        // Disable SRGB
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT6, 0x00);              // Diable O-Gamma
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT0, 0x00);     // Disable OSD
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
