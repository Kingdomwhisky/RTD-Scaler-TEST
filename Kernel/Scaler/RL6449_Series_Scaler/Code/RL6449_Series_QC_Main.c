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
// ID Code      : RL6449_Series_QC_Main.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6449_SERIES_QC_MAIN__

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
#define _D4_PORT_TEST                           _ON
#define _D5_PORT_TEST                           _ON


#if(_A0_PORT_TEST == _OFF)
#warning "A0 Port Disable !!"
#endif

#if(_D0_PORT_TEST == _OFF)
#warning "D0 Port Disable !!"
#endif

#if(_D1_PORT_TEST == _OFF)
#warning "D1 Port Disable !!"
#endif

#if(_D2_PORT_TEST == _OFF)
#warning "D2 Port Disable !!"
#endif

#if(_D3_PORT_TEST == _OFF)
#warning "D3 Port Disable !!"
#endif

//----------------------------------------------------------------------------
// DP QC Test (For Timing 4096 x 2160 @ 30 & 60 Hz)
//----------------------------------------------------------------------------
#if(_DP_SUPPORT == _ON)
#define _DP_CRC0                                0x38
#define _DP_CRC1                                0x67
#define _DP_CRC2                                0xE0
#define _DP_CRC3                                0x49
#define _DP_CRC4                                0xB1
#define _DP_CRC5                                0x30
#endif


//----------------------------------------------------------------------------
// HDMI QC Test
// HDMI Low Speed 3840x2160@30Hz
//----------------------------------------------------------------------------
#if((_D2_TMDS_SUPPORT == _ON) || (_D3_TMDS_SUPPORT == _ON) || (_D4_TMDS_SUPPORT == _ON) || (_D5_TMDS_SUPPORT == _ON))
#define _HDMI_LOW_SPEED_CRC0                    0xAF //0x9B
#define _HDMI_LOW_SPEED_CRC1                    0xD3 //0x1E
#define _HDMI_LOW_SPEED_CRC2                    0x30 //0x66
#define _HDMI_LOW_SPEED_CRC3                    0x00
#define _HDMI_LOW_SPEED_CRC4                    0x00
#define _HDMI_LOW_SPEED_CRC5                    0x00
#endif

/*
//----------------------------------------------------------------------------
// HDMI QC Test
// HDMI D5 Port For Audio 1920x1080@60Hz
//----------------------------------------------------------------------------
#if(_D5_TMDS_SUPPORT == _ON)
// 2048x1152@60Hz
#define _HDMI_D5_CRC0                           0xC5
#define _HDMI_D5_CRC1                           0x91
#define _HDMI_D5_CRC2                           0x0E
#define _HDMI_D5_CRC3                           0x00
#define _HDMI_D5_CRC4                           0x00
#define _HDMI_D5_CRC5                           0x00
// 1920x1080@60Hz
#define _HDMI_D5_CRC0                           0xA8
#define _HDMI_D5_CRC1                           0x69
#define _HDMI_D5_CRC2                           0x3A
#define _HDMI_D5_CRC3                           0xCD
#define _HDMI_D5_CRC4                           0xB3
#define _HDMI_D5_CRC5                           0x6A
#endif
*/

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

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
BYTE ScalerQCD4PortTest(void);
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
BYTE ScalerQCD5PortTest(void);

#endif

#if(_D2_HDMI_SUPPORT == _ON)
bit ScalerQCD2HdmiTest(void);
#endif

#if(_D3_HDMI_SUPPORT == _ON)
bit ScalerQCD3HdmiTest(void);
#endif

#if(_D4_HDMI_SUPPORT == _ON)
bit ScalerQCD4HdmiTest(void);
#endif

#if(_D5_HDMI_SUPPORT == _ON)
bit ScalerQCD5HdmiTest(void);
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

#if(_QC_4P_MODE_ == _ON)
void ScalerVGIPModeSwitch(bit bMode);
void ScalerQCScalingDownDisable(void);
void ScalerQCModeSwitch(bit bMode);
void ScalerQCSetDisplayTimingGenActiveRegion(bit bMode);
void ScalerQCSetDisplayTimingGenBackground(bit bMode);
#endif  // End of #if(_QC_4P_MODE_ == _ON)

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
    BYTE ucResult0 = 0x00;

#if(_QC_4P_MODE_ == _ON)
    BYTE ucResult1 = 0x00;
#endif

#if(_A0_PORT_TEST == _OFF)
    if(ucResult0 == 0x00)
    {
        return ucResult0;
    }
#endif

    ucResult0 = (ucResult0 | (BYTE)ScalerQCVGAPGTest());

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x01, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCADCNRTest() << 1));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x02, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCRingingFilterTest() << 2));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x03, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCDigitalFilterTest() << 3));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x04, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCScaleUpTest() << 4));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x05, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCLSRTest() << 5));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x06, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCOSDTest() << 6));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x07, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCBistTest() << 7));    // BIST Test

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x08, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

#if(_QC_4P_MODE_ == _ON)

    ScalerQCModeSwitch(_4P);

    ucResult1 = (ucResult1 | (BYTE)ScalerQCFRC4PTest(_4P));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x10, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQC4PScaleUpTest() << 1));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x11, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQC4PLSRTest() << 2));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x12, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQC4PBistTest() << 3));    // BIST Test

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x13, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    DebugMessageQC("6. #### A0 Port ucResult0 =", ucResult0);
    DebugMessageQC("6. #### A0 Port ucResult1 =", ucResult1);

    ScalerSetByte(0x0006, ucResult0);
    ScalerSetByte(0x000D, ucResult1);

    return (ucResult0 | ucResult1);

#endif  // End of #if(_QC_4P_MODE_ == _ON)

    return ucResult0;
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

#if(_QC_4P_MODE_ == _ON)
    BYTE ucResult1 = 0x00;
#endif

#if(_D0_PORT_TEST == _OFF)
    if(ucResult0 == 0x00)
    {
        return ucResult0;
    }
#endif

#if((_DP_SUPPORT == _ON) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))

    ucResult0 = (ucResult0 | (BYTE)ScalerQCD0DpTest());

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x20, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }
#endif

    ucResult0 = (ucResult0 | ((BYTE)ScalerQC422to444Test() << 1));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x22, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCFormatConversionTest() << 2));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x23, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCScaleDownTest() << 3));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x24, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

#if(_QC_4P_MODE_ == _ON)

    ScalerQCModeSwitch(_4P);

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCFRC4PTest(_4P) << 5));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x26, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQC4PScaleDownTest() << 6));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x27, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQC4PSHPTest() << 7));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x28, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult1 = (ucResult1 | (BYTE)ScalerQC4PDDomainColorConvTest());

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x29, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    // I-domain IP
    ScalerQCScalingDownDisable();

    ucResult1 = (ucResult1 | ((BYTE)ScalerQC4PFormatConversionTest() << 1));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x30, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQC4P422to444Test() << 2));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x31, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQC4PIDomainColorConvTest() << 3));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x32, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQC4PIDLTITest() << 4));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x33, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQC4PIDitherTest() << 5));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x34, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    DebugMessageQC("6. #### D0 Port ucResult0 =", ucResult0);
    DebugMessageQC("6. #### D0 Port ucResult1 =", ucResult1);

    ScalerSetByte(0x0006, ucResult0);
    ScalerSetByte(0x000D, ucResult1);

    return (ucResult0 | ucResult1);

#endif  // End of #if(_QC_4P_MODE_ == _ON)

    return ucResult0;
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

#if(_QC_4P_MODE_ == _ON)
    BYTE ucResult3 = 0x00;
    BYTE ucResult4 = 0x00;
#endif

#if(_D1_PORT_TEST == _OFF)
    if(ucResult0 == 0x00)
    {
        return ucResult0;
    }
#endif

#if((_DP_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))

    ucResult0 = (ucResult0 | (BYTE)ScalerQCD1DpTest());

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x40, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }
#endif

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCHLWTest() << 3));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x42, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIPGTest() << 4));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x43, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIDomainColorConvTest() << 5));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x44, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIDLTITest() << 6));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x45, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

    ucResult0 = (ucResult0 | ((BYTE)ScalerQCIDitherTest() << 7));

    if(ucResult0 != 0x00)
    {
        ScalerQCDebug(0x46, ucResult0);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult0;
#endif
    }

// D-Domain Test
    ucResult1 = (ucResult1 | (BYTE)ScalerQCDPGTest());

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x47, ucResult1);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCDPGRandomTest() << 1));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x48, ucResult1);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCDDomainColorConvTest() << 2));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x49, ucResult1);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCDCCTest() << 4));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x50, ucResult1);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCDCRTest() << 3));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x51, ucResult1);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCICMTest() << 5));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x52, ucResult1);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCCTSBRITest() << 6));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x53, ucResult1);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult1 = (ucResult1 | ((BYTE)ScalerQCIAPSGainTest() << 7));

    if(ucResult1 != 0x00)
    {
        ScalerQCDebug(0x54, ucResult1);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult1;
#endif
    }

    ucResult2 = (ucResult2 | (BYTE)ScalerQC3DGammaTest());

    if(ucResult2 != 0x00)
    {
        ScalerQCDebug(0x55, ucResult2);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | (BYTE)ScalerQCRGBGammaTest());

    if(ucResult2 != 0x00)
    {
        ScalerQCDebug(0x56, ucResult2);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCPCMTest() << 1));

    if(ucResult2 != 0x00)
    {
        ScalerQCDebug(0x57, ucResult2);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCsRGBTest() << 2));

    if(ucResult2 != 0x00)
    {
        ScalerQCDebug(0x58, ucResult2);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif

    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCGammaTest() << 3));

    if(ucResult2 != 0x00)
    {
        ScalerQCDebug(0x59, ucResult2);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCPanelUniformityTest() << 4));

    if(ucResult2 != 0x00)
    {
        ScalerQCDebug(0x60, ucResult2);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCDDitherTest() << 5));

    if(ucResult2 != 0x00)
    {
        ScalerQCDebug(0x61, ucResult2);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

    ucResult2 = (ucResult2 | ((BYTE)ScalerQCSHPTest() << 6));

    if(ucResult2 != 0x00)
    {
        ScalerQCDebug(0x62, ucResult2);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult2;
#endif
    }

#if(_QC_4P_MODE_ == _ON)

    ScalerQCModeSwitch(_PBP_LR);

    ucResult3 = (ucResult3 | (BYTE)ScalerQCFRC4PTest(_PBP_LR));

    if(ucResult3 != 0x00)
    {
        ScalerQCDebug(0x64, ucResult3);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    ucResult3 = (ucResult3 | ((BYTE)ScalerQC2PDPGTest() << 1));

    if(ucResult3 != 0x00)
    {
        ScalerQCDebug(0x65, ucResult3);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    ucResult3 = (ucResult3 | ((BYTE)ScalerQC2PDPGRandomTest() << 2));

    if(ucResult3 != 0x00)
    {
        ScalerQCDebug(0x66, ucResult3);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    ucResult3 = (ucResult3 | ((BYTE)ScalerQC2PSHPTest() << 3));

    if(ucResult3 != 0x00)
    {
        ScalerQCDebug(0x67, ucResult3);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    ucResult3 = (ucResult3 | ((BYTE)ScalerQC2PDDomainColorConvTest() << 4));

    if(ucResult3 != 0x00)
    {
        ScalerQCDebug(0x68, ucResult3);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    ucResult3 = (ucResult3 | ((BYTE)ScalerQC2PScaleDownTest() << 5));

    if(ucResult3 != 0x00)
    {
        ScalerQCDebug(0x69, ucResult3);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    ucResult3 = (ucResult3 | ((BYTE)ScalerQC2PLSRTest() << 6));

    if(ucResult3 != 0x00)
    {
        ScalerQCDebug(0x70, ucResult3);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult3;
#endif
    }

    // I-domain IP
    ScalerQCScalingDownDisable();

    ucResult4 = (ucResult4 | (BYTE)ScalerQC2PIPGTest());

    if(ucResult4 != 0x00)
    {
        ScalerQCDebug(0x71, ucResult4);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult4;
#endif
    }

    ucResult4 = (ucResult4 | ((BYTE)ScalerQC2PIDomainColorConvTest() << 1));

    if(ucResult4 != 0x00)
    {
        ScalerQCDebug(0x72, ucResult4);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult4;
#endif
    }

    ucResult4 = (ucResult4 | ((BYTE)ScalerQC2PIDLTITest() << 2));

    if(ucResult4 != 0x00)
    {
        ScalerQCDebug(0x73, ucResult4);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult4;
#endif
    }

    ucResult4 = (ucResult4 | ((BYTE)ScalerQC2PIDitherTest() << 3));

    if(ucResult4 != 0x00)
    {
        ScalerQCDebug(0x74, ucResult4);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult4;
#endif
    }

    ucResult4 = (ucResult4 | ((BYTE)ScalerQC2PFormatConversionTest() << 4));

    if(ucResult4 != 0x00)
    {
        ScalerQCDebug(0x75, ucResult4);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult4;
#endif
    }

    DebugMessageQC("6. #### D1 Port ucResult0 =", ucResult0);
    DebugMessageQC("6. #### D1 Port ucResult1 =", ucResult1);
    DebugMessageQC("6. #### D1 Port ucResult2 =", ucResult2);
    DebugMessageQC("6. #### D1 Port ucResult3 =", ucResult3);
    DebugMessageQC("6. #### D1 Port ucResult4 =", ucResult4);

    return (ucResult0 | ucResult1 | ucResult2 | ucResult3 | ucResult4);


#endif  // End of #if(_QC_4P_MODE_ == _ON)

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

    ucResult = (ucResult | (BYTE)ScalerQCD2HdmiTest());

    if(ucResult != 0x00)
    {
        ScalerQCDebug(0x80, ucResult);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }
#endif


    ucResult = (ucResult | ((BYTE)ScalerQC420D2BistTest() << 1));

    if(ucResult != 0x00)
    {
        ScalerQCDebug(0x81, ucResult);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    ucResult = (ucResult | ((BYTE)ScalerQCFRCTest() << 2));

    if(ucResult != 0x00)
    {
        ScalerQCDebug(0x82, ucResult);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

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
    ucResult = (ucResult | (BYTE)ScalerQCD3HdmiTest());

    if(ucResult != 0x00)
    {
        ScalerQCDebug(0x85, ucResult);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }
#endif

    ucResult = (ucResult | ((BYTE)ScalerQC420D3BistTest() << 1));

    if(ucResult != 0x00)
    {
        ScalerQCDebug(0x86, ucResult);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    ucResult = (ucResult | ((BYTE)ScalerQCODTest() << 2));

    if(ucResult != 0x00)
    {
        ScalerQCDebug(0x87, ucResult);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    return ucResult;
}
#endif  // End of #if(_D3_INPUT_PORT_TYPE != D3_NO_PORT)

//--------------------------------------------------
// Description  : Test Process for D4 Port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
BYTE ScalerQCD4PortTest(void)
{
    BYTE ucResult = 0x00;

#if(_D4_PORT_TEST == _OFF)
    if(ucResult == 0x00)
    {
        return ucResult;
    }
#endif

#if(_D4_HDMI_SUPPORT == _ON)
    ucResult = (ucResult | (BYTE)ScalerQCD4HdmiTest());

    if(ucResult != 0x00)
    {
        ScalerQCDebug(0x90, ucResult);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }
#endif

    // LVDS QC Test
    ucResult = (ucResult | ((BYTE)ScalerQCDSPCTest() << 1));

    if(ucResult != 0x00)
    {
        ScalerQCDebug(0x91, ucResult);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    // DPTx QC Test
    ucResult = (ucResult | ((BYTE)ScalerQCDPTXTest()) << 2);

    if(ucResult != 0x00)
    {
        ScalerQCDebug(0x92, ucResult);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    // Vby1 QC Test
    ucResult = (ucResult | ((BYTE)ScalerQCVBY1TXTest()) << 3);

    if(ucResult != 0x00)
    {
        ScalerQCDebug(0x93, ucResult);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }

    return ucResult;
}
#endif  // End of #if(_D4_INPUT_PORT_TYPE != D4_NO_PORT)

//--------------------------------------------------
// Description  : Test Process for D5 Port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
BYTE ScalerQCD5PortTest(void)
{
    BYTE ucResult = 0x00;

#if(_D5_PORT_TEST == _OFF)
    if(ucResult == 0x00)
    {
        return ucResult;
    }
#endif

#if(_D5_HDMI_SUPPORT == _ON)
    ucResult = (ucResult | (BYTE)ScalerQCD5HdmiTest());

    if(ucResult != 0x00)
    {
        ScalerQCDebug(0x95, ucResult);
#if(_QC_TEST_DEBUG  == _OFF)
        return ucResult;
#endif
    }
#endif

    return ucResult;
}

#endif  // End of #if(_D5_INPUT_PORT_TYPE != D5_NO_PORT)

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
// Description  : D4 Hdmi Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if(_D4_HDMI_SUPPORT == _ON)
bit ScalerQCD4HdmiTest(void)
{
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

    if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        if(ScalerTimerPollingFlagProc(200, P69_A7_CBUS_CTRL_07, (_BIT4 | _BIT3), _TRUE) == _TRUE)
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
    ScalerSetBit(P73_A4_TMDS_CTRL, ~_BIT0, _BIT0);

    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);

    ScalerSetBit(P73_A4_TMDS_CTRL, ~_BIT0, 0x00);

    pData[0] = ScalerGetByte(P73_A5_TMDS_CRCOB2);
    pData[1] = ScalerGetByte(P73_A5_TMDS_CRCOB2);
    pData[2] = ScalerGetByte(P73_A5_TMDS_CRCOB2);
    pData[3] = ScalerGetByte(P73_A5_TMDS_CRCOB2);
    pData[4] = ScalerGetByte(P73_A5_TMDS_CRCOB2);
    pData[5] = ScalerGetByte(P73_A5_TMDS_CRCOB2);

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
// Description  : D5 Hdmi Test
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
#if(_D5_HDMI_SUPPORT == _ON)
bit ScalerQCD5HdmiTest(void)
{
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        if(ScalerTimerPollingFlagProc(200, P6A_A7_CBUS_CTRL_07, (_BIT4 | _BIT3), _TRUE) == _TRUE)
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
    ScalerSetBit(P74_A4_TMDS_CTRL, ~_BIT0, _BIT0);

    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);
    ScalerTimerWaitForEvent(_EVENT_IVS);

    ScalerSetBit(P74_A4_TMDS_CTRL, ~_BIT0, 0x00);

    pData[0] = ScalerGetByte(P74_A5_TMDS_CRCOB2);
    pData[1] = ScalerGetByte(P74_A5_TMDS_CRCOB2);
    pData[2] = ScalerGetByte(P74_A5_TMDS_CRCOB2);
    pData[3] = ScalerGetByte(P74_A5_TMDS_CRCOB2);
    pData[4] = ScalerGetByte(P74_A5_TMDS_CRCOB2);
    pData[5] = ScalerGetByte(P74_A5_TMDS_CRCOB2);

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
//            ScalerSetBit(PB6_4F_SRAM_BIST_1, ~(_BIT4 | _BIT3), _BIT4);

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
//                ScalerSetBit(PA_66_SRAM_BIST_1, ~(_BIT4 | _BIT3), _BIT4);

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

    // Set mst_en = SST mode
    ScalerSetBit(PA_80_MST2SST_CONFIG, ~(_BIT7 | _BIT2), _BIT2);

    // Enable MST2SST Received SST
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
    ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT4));

    // DPPLL Power Down
    ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Disable M/N Tracking
    //ScalerSetBit(PA_A7_MN_SCLKG_TRK_CTRL, ~_BIT7, 0x00);

    // Disable HSync Tracking
    ScalerSetBit(PA_A7_MN_SCLKG_TRK_CTRL, ~_BIT6, 0x00);

    // Set VCOMD, phase Swallow Circuit Clock Select, SCLKGSTOP
    ScalerSetBit(PA_BF_MN_SCLKG_PLL_WD, ~(0x7F), 0x16);

    // Set DPPLL Div_2 & Div_s
    ScalerSetByte(PA_A3_MN_SCLKG_DIVS, 0x00);
    //ScalerSetByte(PA_A3_MN_SCLKG_DIVS, ScalerGetByte(PB5_A3_MN_SCLKG_DIVS));

    // Set DPPLL Div_O.
    ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0),0x00);
    //ScalerSetBit(PA_BD_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0),(ScalerGetByte(PB5_BD_MN_SCLKG_PLL_PWR) & (_BIT1 | _BIT0)));

    ulpllm = (SDWORD)((540 / 27) * ((((ScalerGetByte(0xB5A0) & 0x03) << 8) | ScalerGetByte(0xB5A1)) + 2) / (ScalerGetByte(0xB5A2) + 2) *
             ((SDWORD)16384 * 32 * 4 + (((SDWORD)(ScalerGetByte(0xB5A4) & 0x07) << 16) | (SDWORD)(ScalerGetByte(0xB5A5) << 8) | (SDWORD)ScalerGetByte(0xB5A6))) * 2) / 16384 / 32 / 4;

    lOffsetValue = (SDWORD)((540 / 27) * ((((ScalerGetByte(0xB5A0) & 0x03) << 8) | ScalerGetByte(0xB5A1)) + 2) / (ScalerGetByte(0xB5A2) + 2) * 2 *
                   (((SDWORD)16384 * 32 * 4 + (((SDWORD)(ScalerGetByte(0xB5A4) & 0x07) << 16) | (SDWORD)(ScalerGetByte(0xB5A5) << 8) | (SDWORD)ScalerGetByte(0xB5A6))) / (SDWORD)ulpllm));

    lOffsetValue = lOffsetValue - (SDWORD)16384 * 32 * 4;

    DebugMessageQC("ulpllm", ulpllm);
    DebugMessageQC("lOffsetValue2", lOffsetValue);

    // Offset Value Setting
    ScalerSetByte(PA_A6_MN_SCLKG_OFFS_L, lOffsetValue & 0xFF);
    ScalerSetByte(PA_A5_MN_SCLKG_OFFS_M, (lOffsetValue >> 8) & 0xFF);
    ScalerSetBit(PA_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 |_BIT0), (lOffsetValue >> 16) & 0x07);
/*
    // Offset Value Setting
    ScalerSetByte(PA_A6_MN_SCLKG_OFFS_L, 0x00);
    ScalerSetByte(PA_A5_MN_SCLKG_OFFS_M, 0x25);
    ScalerSetBit(PA_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 |_BIT0), 0x00);
*/
    /*
    ScalerSetByte(PA_A6_MN_SCLKG_OFFS_L, ScalerGetByte(PB5_A6_MN_SCLKG_OFFS_L));
    ScalerSetByte(PA_A5_MN_SCLKG_OFFS_M, ScalerGetByte(PB5_A5_MN_SCLKG_OFFS_M));
    ScalerSetBit(PA_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 |_BIT0), (ScalerGetByte(PB5_A4_MN_SCLKG_OFFS_H) & (_BIT2 | _BIT1 | _BIT0)));
    */

    // Enable phase swallow
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), _BIT4);

    // Set DPPLL M Code
    ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), ((ulpllm - 2) >> 8));
    ScalerSetByte(PA_A1_MN_SCLKG_DIVM, ((ulpllm - 2) & 0xFF));

/*
    // Set DPPLL M Code
    ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte(PA_A1_MN_SCLKG_DIVM, 0x27);
*/
    //ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), (ScalerGetByte(PB5_A0_MN_SCLKG_CTRL) & (_BIT1 | _BIT0)));
    //ScalerSetByte(PA_A1_MN_SCLKG_DIVM, ScalerGetByte(PB5_A1_MN_SCLKG_DIVM));

    // Set DPPLL N Code
    ScalerSetByte(PA_A2_MN_SCLKG_DIVN, 0x00);
    //ScalerSetByte(PA_A2_MN_SCLKG_DIVN, ScalerGetByte(PB5_A2_MN_SCLKG_DIVN));

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

    // Disable Tracking New Mode
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~(_BIT2 | _BIT1), _BIT1);

    // Set Initial I/P Code
    ScalerSetByte(PA_B1_MN_SCLKG_TRK_VS_I_M, 0x00);
    ScalerSetByte(PA_B2_MN_SCLKG_TRK_VS_I_L, 0x04);
    ScalerSetByte(PA_B3_MN_SCLKG_TRK_VS_P_H, 0x07);
    ScalerSetByte(PA_B4_MN_SCLKG_TRK_VS_P_M, 0xFF);
    ScalerSetByte(PA_B5_MN_SCLKG_TRK_VS_P_L, 0xFF);

    // Set Tracking Freq
    ScalerSetBit(PA_A8_MN_SCLKG_TRK_MN_I_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4),  (ScalerGetByte(PB5_A8_MN_SCLKG_TRK_MN_I_H) & 0xF0));

    // Set Tracking Lock PE
    ScalerSetByte(PA_B7_MN_SCLKG_TRK_VS_NLOCK, 0x7F);

    // Enable H Sync Tracking
    ScalerSetByte(PA_A7_MN_SCLKG_TRK_CTRL, 0x58);

    // Double Buffer for H Sync Tracking
    ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    /*
    while(ScalerGetByte(0x0006) == 0x00)
    {
        ScalerDebug();
    }
    */


    ScalerTimerDelayXms(30);

    // Set Final I/P Code
    ScalerSetByte(PA_B1_MN_SCLKG_TRK_VS_I_M, 0x00);
    ScalerSetByte(PA_B2_MN_SCLKG_TRK_VS_I_L, 0x02);

    // Start Generate Display Format
    ScalerSetBit(PA_35_DPF_CTRL_0, ~_BIT7, _BIT7);

    ScalerSetByte(PA_C2_HS_TRACKING_NEW_MODE1, ScalerGetByte(PB5_C2_HS_TRACKING_NEW_MODE1));
    ScalerSetByte(PA_C3_HS_TRACKING_NEW_MODE2, ScalerGetByte(PB5_C3_HS_TRACKING_NEW_MODE2));

    // Enable Tracking New Mode
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~_BIT2, _BIT2);

    ScalerTimerDelayXms(10);

    if(ScalerDpRx0MstToSstFifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
    {
        DebugMessageQC("D0 MST2SST FIFO Failed", 0);
        return _FALSE;
    }

    // DP MST2SST RGB Output Enable
    ScalerSetBit(PA_36_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // DP MST2SST CLK Output Enable
    ScalerSetBit(PA_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, _BIT6);

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
    // Set Free Run
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

    ScalerDDomainBackgroundEnable(_DISABLE);
    // Disable Watch Dog
    ScalerSetBit(P0_0D_WATCH_DOG_CTRL1, ~_BIT7, 0x00);
#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
    // Disable Input HVsync error IRQ
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

    //--------------------I Domain------------------//
    ScalerQCVGATopRandomGenOff();                      // Disable VGA Random Generator
    ScalerQCIDomainRandomGenOff();                      // Disable I Domain Random Generator

    ScalerSetBit(P31_32_YUV420_TO_YUV422_D2, ~_BIT7, 0x00);         // Disable YUV420 to 422
    ScalerSetBit(P31_33_YUV420_TO_YUV422_D3, ~_BIT7, 0x00);
    ScalerSetBit(P31_40_YUV422_TO_444_PATH0, ~_BIT3, 0x00);         // Disable YUV422 to 444

    ScalerSetBit(P33_00_ADCNR_CTRL1, ~_BIT7, 0x00);     // Disable ADCNR
    ScalerSetBit(P33_02_ADCNR_CTRL3, ~(_BIT7 | _BIT6), 0x00);       // No Truncate LSB
    ScalerSetBit(P0_98_DIGITAL_FILTER_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4)); // Disable Digital Filter
    ScalerSetBit(P0_99_DIGITAL_FILTER_PORT, ~(_BIT7 | _BIT6 | _BIT5 ), 0x00);

    ScalerSetBit(P25_A0_RFILTER_CTRL, ~_BIT7, 0x00);    // Disable Ringing Filter
    ScalerSetByte(P0_9C_RGB2YCC_CTRL, 0x00);            // Disable I-ColorConv
    ScalerSetBit(P11_A1_I_DLTI_CTRL_M1, ~_BIT0, 0x00);  // Disable IDLTI
    ScalerSetBit(P0_89_I_DITHER_COMMON_CTRL1_SETA, ~_BIT5, 0x00);   // Disable I-Dither


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
    ScalerSetBit(P47_E0_IAPS_GAIN_CTRL_M2, ~_BIT0, 0x00);
    ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT7, 0x00);            // Disable 3DGamma
    ScalerSetBit(P9_A1_INPUT_GAMMA_CTRL_SETA, ~_BIT6, 0x00);             // Disable I-Gamma
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

#if(_QC_4P_MODE_ == _ON)
//--------------------------------------------------
// Description  : Mode Switch
// Input Value  : _4P       --> 4P Mode
//                _PBP_LR   --> PBP_LR Mode
// Output Value : None
//--------------------------------------------------
void ScalerQCModeSwitch(bit bMode)
{
    ScalerQCSetDisplayTimingGenActiveRegion(bMode);
    ScalerQCSetDisplayTimingGenBackground(bMode);
    ScalerQCSetScaling(bMode);

    ScalerVGIPModeSwitch(bMode);
    ScalerQCFRC(bMode);
}

//--------------------------------------------------
// Description  : Disable SD for 2P/4P I-domain Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCScalingDownDisable(void)
{
    // Close V Scale Down, For Test
    ScalerSetByte(0x0023, 0x00);
    ScalerSetByte(0x4023, 0x00);
    ScalerSetByte(0x8023, 0x00);
    ScalerSetByte(0xC023, 0x00);
}

//--------------------------------------------------
// Description  : VGIP Mode Switch
// Input Value  : _4P       --> 4P Mode
//                _PBP_LR   --> PBP_LR Mode
// Output Value : None
//--------------------------------------------------
void ScalerVGIPModeSwitch(bit bMode)
{
    if(bMode == _4P) // 4P
    {
        // Set formatconversion for S1/S2
        ScalerSetByte(P31_01_FC_INPUT_SEL_P23, ScalerGetByte(P31_00_FC_INPUT_SEL_P01));

        // Enable clock
        ScalerSetByte(P31_0D_FC_INPUT_CLK_GATING, 0x0F);

        // Disable E/O
        ScalerSetByte(P31_06_FC_EO_LINE_CTRL, 0x00);

        // Enable 1/2 SD
        if(GET_MDOMAIN_INPUT_HWIDTH() != 1280)
        {
            ScalerSetByte(P31_05_FC_SD_CTRL, 0x00);
        }

        // Disable DB
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~_BIT7, 0x00);

        // Enlarge M1 capture: V x 2, H / 2
        // V start
        PDATA_WORD(0) = ((((WORD)(ScalerGetByte(P0_18_M1_IPV_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P0_19_M1_IPV_ACT_STA_L)));
        // V delay
        PDATA_WORD(1) = (((((WORD)(ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY) & _BIT1)) << 7) | ScalerGetByte(P0_1C_M1_IVS_DELAY)));
        // V height
        PDATA_WORD(2) = ((((WORD)(ScalerGetByte(P0_18_M1_IPV_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P0_1B_M1_IPV_ACT_LEN_L)));
        PDATA_WORD(0) = (PDATA_WORD(0) << 1);
        PDATA_WORD(1) = (PDATA_WORD(1) << 1);
        PDATA_WORD(2) = (PDATA_WORD(2) << 1);
        ScalerSetByte(P0_18_M1_IPV_ACT_STA_H, ((HIBYTE(PDATA_WORD(2)) << 4) | (HIBYTE(PDATA_WORD(0)) & 0x0F)));
        ScalerSetByte(P0_19_M1_IPV_ACT_STA_L, LOBYTE(PDATA_WORD(0)));
        ScalerSetByte(P0_1B_M1_IPV_ACT_LEN_L, LOBYTE(PDATA_WORD(2)));
        ScalerSetByte(P0_1C_M1_IVS_DELAY, LOBYTE(PDATA_WORD(1)));
        ScalerSetBit(P0_1E_M1_VGIP_HV_DELAY, ~_BIT1, ((HIBYTE(PDATA_WORD(1)) & _BIT0) << 1));

        // H start
        PDATA_WORD(3) = ((((WORD)(ScalerGetByte(P0_14_M1_IPH_ACT_STA_H) & 0x0F) << 8) | ScalerGetByte(P0_15_M1_IPH_ACT_STA_L)) + 2);
        // H delay
        PDATA_WORD(4) = ((((WORD)ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY) & _BIT2) << 7) | (((WORD)ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY) & _BIT0) << 8) | ScalerGetByte(P0_1D_M1_IHS_DELAY));
        // H width
        PDATA_WORD(5) = (((WORD)ScalerGetBit(P0_16_M1_IPH_ACT_WID_H, _BIT0) << 12) | (((WORD)ScalerGetByte(P0_14_M1_IPH_ACT_STA_H) & 0xF0) << 4) | ScalerGetByte(P0_17_M1_IPH_ACT_WID_L));
        if(GET_MDOMAIN_INPUT_HWIDTH() != 1280)
        {
            PDATA_WORD(3) = (PDATA_WORD(3) - 2);
            PDATA_WORD(4) = PDATA_WORD(4);
            PDATA_WORD(5) = (PDATA_WORD(5) >> 1);
        }
        else
        {
            PDATA_WORD(3) = ((PDATA_WORD(3) << 1) - 2);
            PDATA_WORD(4) = (PDATA_WORD(4) << 1);
            PDATA_WORD(5) = PDATA_WORD(5);
        }
        ScalerSetByte(P0_14_M1_IPH_ACT_STA_H, ((HIBYTE(PDATA_WORD(5)) << 4) | (HIBYTE(PDATA_WORD(3)) & 0x0F)));
        ScalerSetByte(P0_15_M1_IPH_ACT_STA_L, LOBYTE(PDATA_WORD(3)));
        ScalerSetBit(P0_16_M1_IPH_ACT_WID_H, ~_BIT0, ((HIBYTE(PDATA_WORD(5)) & _BIT4) >> 4));
        ScalerSetByte(P0_17_M1_IPH_ACT_WID_L, LOBYTE(PDATA_WORD(5)));
        ScalerSetByte(P0_1D_M1_IHS_DELAY, LOBYTE(PDATA_WORD(4)));
        ScalerSetBit(P0_1E_M1_VGIP_HV_DELAY, ~(_BIT2 | _BIT0), (((HIBYTE(PDATA_WORD(4)) & _BIT1) << 1) | (HIBYTE(PDATA_WORD(4)) & _BIT0)));

        // Copy M2, S1, S2 from M1
        ScalerSetByte(P40_10_M2_VGIP_CTRL, 0x00);
        ScalerSetByte(P40_11_M2_VGIP_SIGINV, ScalerGetByte(P0_11_M1_VGIP_SIGINV));
        ScalerSetByte(P40_12_M2_VGIP_DELAY_CTRL, ScalerGetByte(P0_12_M1_VGIP_DELAY_CTRL));
        ScalerSetByte(P40_13_M2_VGIP_ODD_CTRL, ScalerGetByte(P0_13_M1_VGIP_ODD_CTRL));
        ScalerSetByte(P40_14_M2_IPH_ACT_STA_H, ScalerGetByte(P0_14_M1_IPH_ACT_STA_H));
        ScalerSetByte(P40_15_M2_IPH_ACT_STA_L, ScalerGetByte(P0_15_M1_IPH_ACT_STA_L));
        ScalerSetByte(P40_16_M2_IPH_ACT_WID_H, ScalerGetByte(P0_16_M1_IPH_ACT_WID_H));
        ScalerSetByte(P40_17_M2_IPH_ACT_WID_L, ScalerGetByte(P0_17_M1_IPH_ACT_WID_L));
        ScalerSetByte(P40_18_M2_IPV_ACT_STA_H, ScalerGetByte(P0_18_M1_IPV_ACT_STA_H));
        ScalerSetByte(P40_19_M2_IPV_ACT_STA_L, ScalerGetByte(P0_19_M1_IPV_ACT_STA_L));
        ScalerSetByte(P40_1A_M2_IPV_ACT_LEN_H, ScalerGetByte(P0_1A_M1_IPV_ACT_LEN_H));
        ScalerSetByte(P40_1B_M2_IPV_ACT_LEN_L, ScalerGetByte(P0_1B_M1_IPV_ACT_LEN_L));
        ScalerSetByte(P40_1C_M2_IVS_DELAY, ScalerGetByte(P0_1C_M1_IVS_DELAY));
        ScalerSetByte(P40_1D_M2_IHS_DELAY, ScalerGetByte(P0_1D_M1_IHS_DELAY));
        ScalerSetByte(P40_1E_M2_VGIP_HV_DELAY, ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY));
        ScalerSetByte(P40_1F_M2_ICLK_GATED_CTRL1, ScalerGetByte(P0_1F_M1_ICLK_GATED_CTRL1));
        ScalerSetByte(P40_10_M2_VGIP_CTRL, ScalerGetByte(P0_10_M1_VGIP_CTRL));

        ScalerSetByte(P80_10_S1_VGIP_CTRL, 0x00);
        ScalerSetByte(P80_11_S1_VGIP_SIGINV, ScalerGetByte(P0_11_M1_VGIP_SIGINV));
        ScalerSetByte(P80_12_S1_VGIP_DELAY_CTRL, ScalerGetByte(P0_12_M1_VGIP_DELAY_CTRL));
        ScalerSetByte(P80_13_S1_VGIP_ODD_CTRL, ScalerGetByte(P0_13_M1_VGIP_ODD_CTRL));
        ScalerSetByte(P80_14_S1_IPH_ACT_STA_H, ScalerGetByte(P0_14_M1_IPH_ACT_STA_H));
        ScalerSetByte(P80_15_S1_IPH_ACT_STA_L, ScalerGetByte(P0_15_M1_IPH_ACT_STA_L));
        ScalerSetByte(P80_16_S1_IPH_ACT_WID_H, ScalerGetByte(P0_16_M1_IPH_ACT_WID_H));
        ScalerSetByte(P80_17_S1_IPH_ACT_WID_L, ScalerGetByte(P0_17_M1_IPH_ACT_WID_L));
        ScalerSetByte(P80_18_S1_IPV_ACT_STA_H, ScalerGetByte(P0_18_M1_IPV_ACT_STA_H));
        ScalerSetByte(P80_19_S1_IPV_ACT_STA_L, ScalerGetByte(P0_19_M1_IPV_ACT_STA_L));
        ScalerSetByte(P80_1A_S1_IPV_ACT_LEN_H, ScalerGetByte(P0_1A_M1_IPV_ACT_LEN_H));
        ScalerSetByte(P80_1B_S1_IPV_ACT_LEN_L, ScalerGetByte(P0_1B_M1_IPV_ACT_LEN_L));
        ScalerSetByte(P80_1C_S1_IVS_DELAY, ScalerGetByte(P0_1C_M1_IVS_DELAY));
        ScalerSetByte(P80_1D_S1_IHS_DELAY, ScalerGetByte(P0_1D_M1_IHS_DELAY));
        ScalerSetByte(P80_1E_S1_VGIP_HV_DELAY, ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY));
        ScalerSetByte(P80_1F_S1_ICLK_GATED_CTRL1, ScalerGetByte(P0_1F_M1_ICLK_GATED_CTRL1));
        ScalerSetByte(P80_10_S1_VGIP_CTRL, ScalerGetByte(P0_10_M1_VGIP_CTRL));

        ScalerSetByte(PC0_10_S2_VGIP_CTRL, 0x00);
        ScalerSetByte(PC0_11_S2_VGIP_SIGINV, ScalerGetByte(P0_11_M1_VGIP_SIGINV));
        ScalerSetByte(PC0_12_S2_VGIP_DELAY_CTRL, ScalerGetByte(P0_12_M1_VGIP_DELAY_CTRL));
        ScalerSetByte(PC0_13_S2_VGIP_ODD_CTRL, ScalerGetByte(P0_13_M1_VGIP_ODD_CTRL));
        ScalerSetByte(PC0_14_S2_IPH_ACT_STA_H, ScalerGetByte(P0_14_M1_IPH_ACT_STA_H));
        ScalerSetByte(PC0_15_S2_IPH_ACT_STA_L, ScalerGetByte(P0_15_M1_IPH_ACT_STA_L));
        ScalerSetByte(PC0_16_S2_IPH_ACT_WID_H, ScalerGetByte(P0_16_M1_IPH_ACT_WID_H));
        ScalerSetByte(PC0_17_S2_IPH_ACT_WID_L, ScalerGetByte(P0_17_M1_IPH_ACT_WID_L));
        ScalerSetByte(PC0_18_S2_IPV_ACT_STA_H, ScalerGetByte(P0_18_M1_IPV_ACT_STA_H));
        ScalerSetByte(PC0_19_S2_IPV_ACT_STA_L, ScalerGetByte(P0_19_M1_IPV_ACT_STA_L));
        ScalerSetByte(PC0_1A_S2_IPV_ACT_LEN_H, ScalerGetByte(P0_1A_M1_IPV_ACT_LEN_H));
        ScalerSetByte(PC0_1B_S2_IPV_ACT_LEN_L, ScalerGetByte(P0_1B_M1_IPV_ACT_LEN_L));
        ScalerSetByte(PC0_1C_S2_IVS_DELAY, ScalerGetByte(P0_1C_M1_IVS_DELAY));
        ScalerSetByte(PC0_1D_S2_IHS_DELAY, ScalerGetByte(P0_1D_M1_IHS_DELAY));
        ScalerSetByte(PC0_1E_S2_VGIP_HV_DELAY, ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY));
        ScalerSetByte(PC0_1F_S2_ICLK_GATED_CTRL1, ScalerGetByte(P0_1F_M1_ICLK_GATED_CTRL1));
        ScalerSetByte(PC0_10_S2_VGIP_CTRL, ScalerGetByte(P0_10_M1_VGIP_CTRL));
    }
    else if(bMode == _PBP_LR)
    {
        // Set formatconversion for S1/S2
        ScalerSetByte(P31_01_FC_INPUT_SEL_P23, ScalerGetByte(P31_00_FC_INPUT_SEL_P01));

        // Enable clock
        ScalerSetByte(P31_0D_FC_INPUT_CLK_GATING, 0x0F);

        // Set E/O width
        ScalerSetWord(P31_09_FC_FORMAT_PRO_SUB_0, ScalerGetWord(P31_07_FC_FORMAT_PRO_MAIN_0));

        // Enable E/O for sub
        ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));

        // Disable DB
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~_BIT7, 0x00);

        // Copy M1 setting to S1
        ScalerSetByte(P80_10_S1_VGIP_CTRL, 0x00);
        ScalerSetByte(P80_11_S1_VGIP_SIGINV, ScalerGetByte(P0_11_M1_VGIP_SIGINV));
        ScalerSetByte(P80_12_S1_VGIP_DELAY_CTRL, ScalerGetByte(P0_12_M1_VGIP_DELAY_CTRL));
        ScalerSetByte(P80_13_S1_VGIP_ODD_CTRL, ScalerGetByte(P0_13_M1_VGIP_ODD_CTRL));
        ScalerSetByte(P80_14_S1_IPH_ACT_STA_H, ScalerGetByte(P0_14_M1_IPH_ACT_STA_H));
        ScalerSetByte(P80_15_S1_IPH_ACT_STA_L, ScalerGetByte(P0_15_M1_IPH_ACT_STA_L));
        ScalerSetByte(P80_16_S1_IPH_ACT_WID_H, ScalerGetByte(P0_16_M1_IPH_ACT_WID_H));
        ScalerSetByte(P80_17_S1_IPH_ACT_WID_L, ScalerGetByte(P0_17_M1_IPH_ACT_WID_L));
        ScalerSetByte(P80_18_S1_IPV_ACT_STA_H, ScalerGetByte(P0_18_M1_IPV_ACT_STA_H));
        ScalerSetByte(P80_19_S1_IPV_ACT_STA_L, ScalerGetByte(P0_19_M1_IPV_ACT_STA_L));
        ScalerSetByte(P80_1A_S1_IPV_ACT_LEN_H, ScalerGetByte(P0_1A_M1_IPV_ACT_LEN_H));
        ScalerSetByte(P80_1B_S1_IPV_ACT_LEN_L, ScalerGetByte(P0_1B_M1_IPV_ACT_LEN_L));
        ScalerSetByte(P80_1C_S1_IVS_DELAY, ScalerGetByte(P0_1C_M1_IVS_DELAY));
        ScalerSetByte(P80_1D_S1_IHS_DELAY, ScalerGetByte(P0_1D_M1_IHS_DELAY));
        ScalerSetByte(P80_1E_S1_VGIP_HV_DELAY, ScalerGetByte(P0_1E_M1_VGIP_HV_DELAY));
        ScalerSetByte(P80_1F_S1_ICLK_GATED_CTRL1, ScalerGetByte(P0_1F_M1_ICLK_GATED_CTRL1));
        ScalerSetByte(P80_10_S1_VGIP_CTRL, ScalerGetByte(P0_10_M1_VGIP_CTRL));

        // Copy M2 setting to S2
        ScalerSetByte(PC0_10_S2_VGIP_CTRL, 0x00);
        ScalerSetByte(PC0_11_S2_VGIP_SIGINV, ScalerGetByte(P40_11_M2_VGIP_SIGINV));
        ScalerSetByte(PC0_12_S2_VGIP_DELAY_CTRL, ScalerGetByte(P40_12_M2_VGIP_DELAY_CTRL));
        ScalerSetByte(PC0_13_S2_VGIP_ODD_CTRL, ScalerGetByte(P40_13_M2_VGIP_ODD_CTRL));
        ScalerSetByte(PC0_14_S2_IPH_ACT_STA_H, ScalerGetByte(P40_14_M2_IPH_ACT_STA_H));
        ScalerSetByte(PC0_15_S2_IPH_ACT_STA_L, ScalerGetByte(P40_15_M2_IPH_ACT_STA_L));
        ScalerSetByte(PC0_16_S2_IPH_ACT_WID_H, ScalerGetByte(P40_16_M2_IPH_ACT_WID_H));
        ScalerSetByte(PC0_17_S2_IPH_ACT_WID_L, ScalerGetByte(P40_17_M2_IPH_ACT_WID_L));
        ScalerSetByte(PC0_18_S2_IPV_ACT_STA_H, ScalerGetByte(P40_18_M2_IPV_ACT_STA_H));
        ScalerSetByte(PC0_19_S2_IPV_ACT_STA_L, ScalerGetByte(P40_19_M2_IPV_ACT_STA_L));
        ScalerSetByte(PC0_1A_S2_IPV_ACT_LEN_H, ScalerGetByte(P40_1A_M2_IPV_ACT_LEN_H));
        ScalerSetByte(PC0_1B_S2_IPV_ACT_LEN_L, ScalerGetByte(P40_1B_M2_IPV_ACT_LEN_L));
        ScalerSetByte(PC0_1C_S2_IVS_DELAY, ScalerGetByte(P40_1C_M2_IVS_DELAY));
        ScalerSetByte(PC0_1D_S2_IHS_DELAY, ScalerGetByte(P40_1D_M2_IHS_DELAY));
        ScalerSetByte(PC0_1E_S2_VGIP_HV_DELAY, ScalerGetByte(P40_1E_M2_VGIP_HV_DELAY));
        ScalerSetByte(PC0_1F_S2_ICLK_GATED_CTRL1, ScalerGetByte(P40_1F_M2_ICLK_GATED_CTRL1));
        ScalerSetByte(PC0_10_S2_VGIP_CTRL, ScalerGetByte(P40_10_M2_VGIP_CTRL));
    }
}

//--------------------------------------------------
// Description  : Display Timing Gen Background
// Input Value  : _4P       --> 4P Mode
//                _PBP_LR   --> PBP_LR Mode
// Output Value : None
//--------------------------------------------------
void ScalerQCSetDisplayTimingGenBackground(bit bMode)
{
    // Set DHtotal
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DH_TOTAL - 4) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DH_TOTAL - 4));

    // Set H sync width, must by 2x in even-odd-mode
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (_PANEL_DH_SYNC_WIDTH + _PANEL_DH_SYNC_WIDTH % 2));

    // Set V sync height
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0D_DISPLAY_VER_SYNC_END);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_SYNC_HEIGHT));

    // Set Main H background st/ ed (Panel size)
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DH_START) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DH_START));

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH));

    // Set Main V background st/ ed (Panel size)
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DV_START) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_START));

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT));

    if(bMode == _4P || bMode == _PBP_LR)
    {
        // Set Sub H background st/ ed (Panel size)
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_03_DISPLAY_HOR_BG_STA_H_S);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH/2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH/2));

        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_09_DISPLAY_HOR_BG_END_H_S);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH));

        // Set Sub V background st/ ed (Panel size)
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_0E_DISPLAY_VER_BG_STA_H_S);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DV_START) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DV_START));

        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_14_DISPLAY_VER_BG_END_H_S);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT));
    }

    // Set Background color
    // M1 Reset Port index
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, 0x00);
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, _BIT5);

    // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, 0x00);
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, 0x00);
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, 0x00);
    ScalerSetByte(P0_6D_BG_COLOR_DATA_PORT_M1, 0x00);

    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT5, 0x00);

    // M2 Reset Port index
    ScalerSetBit(P40_6C_BG_COLOR_ACCESS_EN_M2, ~_BIT5, 0x00);
    ScalerSetBit(P40_6C_BG_COLOR_ACCESS_EN_M2, ~_BIT5, _BIT5);

    // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
    ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, 0x00);
    ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, 0x00);
    ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, 0x00);
    ScalerSetByte(P40_6D_BG_COLOR_DATA_PORT_M2, 0x00);

    ScalerSetBit(P40_6C_BG_COLOR_ACCESS_EN_M2, ~_BIT5, 0x00);

    // S1 Reset Port index
    ScalerSetBit(P80_6C_BG_COLOR_ACCESS_EN_S1, ~_BIT5, 0x00);
    ScalerSetBit(P80_6C_BG_COLOR_ACCESS_EN_S1, ~_BIT5, _BIT5);

    // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
    ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, 0x00);
    ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, 0x00);
    ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, 0x00);
    ScalerSetByte(P80_6D_BG_COLOR_DATA_PORT_S1, 0x00);

    ScalerSetBit(P80_6C_BG_COLOR_ACCESS_EN_S1, ~_BIT5, 0x00);

    // S2 Reset Port index
    ScalerSetBit(PC0_6C_BG_COLOR_ACCESS_EN_S2, ~_BIT5, 0x00);
    ScalerSetBit(PC0_6C_BG_COLOR_ACCESS_EN_S2, ~_BIT5, _BIT5);

    // 10bits RGB color, Use MSB 8bits, LSB 2bits == 00
    ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, 0x00);
    ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, 0x00);
    ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, 0x00);
    ScalerSetByte(PC0_6D_BG_COLOR_DATA_PORT_S2, 0x00);

    ScalerSetBit(PC0_6C_BG_COLOR_ACCESS_EN_S2, ~_BIT5, 0x00);
    // [4]: Main source type: !4P
    // [3]: Dtime Main mode: select even/ odd
    // [2]: Dtime Sub mode: select disable
    // [1]: Main active num: one
    // [0]: Sub active num: one
    if(bMode == _4P)
    {
        ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    }
    else if(bMode == _PBP_LR)
    {
        ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT4 | _BIT3 | _BIT2));
    }
    else
    {
        ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT4 | _BIT3));
    }
}

//--------------------------------------------------
// Description  : Set Display Timgin Gen: Diaplay active region
// Input Value  : NA
// Output Value : NA
//--------------------------------------------------
void ScalerQCSetDisplayTimingGenActiveRegion(bit bMode)
{
    if(bMode == _4P)
    {
        // Main1 Active
        // Set Main1 H Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DH_START) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DH_START));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2));

        // Set Main1 V Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DV_START) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_START));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, 0x00);

        // Main2 Active
        // Set Main2 H Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_16_DISPLAY_HOR_ACT_STA_H_M2);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DH_START) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DH_START));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2));

        // Set Main2 V Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1A_DISPLAY_VER_ACT_STA_H_M2);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG + 0x4000, ~_BIT5, 0x00);

        // Sub1 Active
        // Set Sub1 H Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_05_DISPLAY_HOR_ACT_STA_H_S1);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH));

        // Set Sub1 V Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_10_DISPLAY_VER_ACT_STA_H_S1);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DV_START) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DV_START));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG + 0x8000, ~_BIT5, 0x00);

        // Sub2 Active
        // Set Sub2 H Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_16_DISPLAY_HOR_ACT_STA_H_S2);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH));

        // Set Sub2 V Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_1A_DISPLAY_VER_ACT_STA_H_S2);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DV_START + _PANEL_DV_HEIGHT));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG + 0xC000, ~_BIT5, 0x00);
    }
    else if(bMode == _PBP_LR)
    {
        // Main1 Active
        // Set Main1 H Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DH_START) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DH_START));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2));

        // Set Main1 V Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DV_START + 540) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_START + 540));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(_PANEL_DV_START + 1080 + 540) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(_PANEL_DV_START + 1080 + 540));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, 0x00);

        // Sub1 Active
        // Set Sub1 H Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_05_DISPLAY_HOR_ACT_STA_H_S1);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH / 2));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DH_START + _PANEL_DH_WIDTH));

        // Set Sub1 V Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_10_DISPLAY_VER_ACT_STA_H_S1);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DV_START + 540) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DV_START + 540));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(_PANEL_DV_START + 1080 + 540) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(_PANEL_DV_START + 1080 + 540));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG + 0x8000, ~_BIT5, 0x00);
    }
}

#endif  // End of #if(_QC_4P_MODE_ == _ON)

#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)
