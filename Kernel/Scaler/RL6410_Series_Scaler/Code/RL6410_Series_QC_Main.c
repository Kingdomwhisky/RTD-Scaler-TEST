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
// ID Code      : RL6410_Series_QC_Main.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6410_SERIES_QC_MAIN__

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


//----------------------------------------------------------------------------
// HDMI QC Test
// HDMI D5 Port For Audio 1920x1080@60Hz
//----------------------------------------------------------------------------
#if(_D5_TMDS_SUPPORT == _ON)
/*
// 2048x1152@60Hz
#define _HDMI_D5_CRC0                           0xC5
#define _HDMI_D5_CRC1                           0x91
#define _HDMI_D5_CRC2                           0x0E
#define _HDMI_D5_CRC3                           0x00
#define _HDMI_D5_CRC4                           0x00
#define _HDMI_D5_CRC5                           0x00
*/
// 1920x1080@60Hz
#define _HDMI_D5_CRC0                           0xA8
#define _HDMI_D5_CRC1                           0x69
#define _HDMI_D5_CRC2                           0x3A
#define _HDMI_D5_CRC3                           0xCD
#define _HDMI_D5_CRC4                           0xB3
#define _HDMI_D5_CRC5                           0x6A
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
//----- A0 item -----//
    _QC_SCALERQCVGAPGTEST = 0x01,
    _QC_SCALERQCADCNRTEST,
    _QC_SCALERQCRINGINGFILTERTEST,
    _QC_SCALERQCDIGITALFILTERTEST,
    _QC_SCALERQCSCALEUPTEST,
    _QC_SCALERQCLSRTEST,
    _QC_SCALERQCOSDTEST_DISABLE,
    _QC_SCALERQCBISTTEST,

#if(_QC_4P_MODE_ == _ON)
    _QC_SCALERQCFRC4PTEST_4P_A0,
    _QC_SCALERQC4PSCALEUPTEST,
    _QC_SCALERQC4PLSRTEST,
    _QC_SCALERQC4PBISTTEST,
#endif

//----- D0 item -----//
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
    _QC_SCALERQCD0DPTEST,
#endif
    _QC_SCALERQC422TO444TEST,
    _QC_SCALERQCFORMATCONVERSIONTEST,
    _QC_SCALERQCSCALEDOWNTEST,

#if(_QC_4P_MODE_ == _ON)
    _QC_SCALERQCFRC4PTEST_4P_D0,
    _QC_SCALERQC4PSCALEDOWNTEST,
    _QC_SCALERQC4PSHPTEST,
    _QC_SCALERQC4PDDOMAINCOLORCONVTEST,
    _QC_SCALERQC4PFORMATCONVERSIONTEST,
    _QC_SCALERQC4P422TO444TEST,
    _QC_SCALERQC4PIDOMAINCOLORCONVTEST,
    _QC_SCALERQC4PIDLTITEST,
    _QC_SCALERQC4PIDITHERTEST,
#endif

#if(_QC_5K3K_MODE_ == _ON)
    _QC_SCALERQCFRC4PTEST_5K3K_1P,
    _QC_SCALERQC5K3KFORMATCONVERSIONTEST,
    _QC_SCALERQC5K3KIPGTEST,
    _QC_SCALERQC5K3KIDOMAINCOLORCONVTEST,
    _QC_SCALERQC5K3KIDLTITEST,
    _QC_SCALERQC5K3KIDITHERTEST,
    _QC_SCALERQC5K3KSCALEUPTEST,
    _QC_SCALERQC5K3KLSRTEST,
    _QC_SCALERQC5K3KHLWTEST,
    _QC_SCALERQC5K3KDPGTEST,
    _QC_SCALERQC5K3KDPGRANDOMTEST,
    _QC_SCALERQC5K3KSHPTEST,
    _QC_SCALERQC5K3KDDOMAINCOLORCONVTEST_5K3K_1P,
    _QC_SCALERQC5K3KDCRTEST,
    _QC_SCALERQC5K3KDCCTEST,
    _QC_SCALERQC5K3KICMTEST,
    _QC_SCALERQC5K3KCTSBRITEST,
    _QC_SCALERQC5K3KIAPSGAINTEST,
    _QC_SCALERQC5K3K3DGAMMATEST,
    _QC_SCALERQC5K3KRGBGAMMATEST,
    _QC_SCALERQC5K3KPCMTEST,
    _QC_SCALERQC5K3KPANELUNIFORMITYTEST,
    _QC_SCALERQC5K3KDDITHERTEST,
    _QC_SCALERQCOSDTEST_ENABLE,
    _QC_SCALERQC5K3KODTEST,

    _QC_SCALERQCFRC4PTEST_5K3K_PBP,
    _QC_SCALERQC5K3KSCALEDOWNTEST,
    _QC_SCALERQC5K3KDDOMAINCOLORCONVTEST_5K3K_PBP,
#endif

//----- D1 item -----//
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
    _QC_SCALERQCD1DPTEST,
#endif
    _QC_SCALERQCHLWTEST,
    _QC_SCALERQCIPGTEST,
    _QC_SCALERQCIDOMAINCOLORCONVTEST,
    _QC_SCALERQCIDLTITEST,
    _QC_SCALERQCIDITHERTEST,
    _QC_SCALERQCDPGTEST,
    _QC_SCALERQCDPGRANDOMTEST,
    _QC_SCALERQCSHPTEST,
    _QC_SCALERQCDDOMAINCOLORCONVTEST,
    _QC_SCALERQCDCRTEST,
    _QC_SCALERQCDCCTEST,
    _QC_SCALERQCICMTEST,
    _QC_SCALERQCCTSBRITEST,
    _QC_SCALERQCIAPSGAINTEST,
    _QC_SCALERQC3DGAMMATEST,
    _QC_SCALERQCSRGBTEST,
    _QC_SCALERQCRGBGAMMATEST,
    _QC_SCALERQCPCMTEST,
    _QC_SCALERQCPANELUNIFORMITYTEST,
    _QC_SCALERQCGAMMATEST,
    _QC_SCALERQCDDITHERTEST,

#if(_QC_4P_MODE_ == _ON)
    _QC_SCALERQCFRC4PTEST_PBP_LR,
    _QC_SCALERQC2PDPGTEST,
    _QC_SCALERQC2PDPGRANDOMTEST,
    _QC_SCALERQC2PSHPTEST,
    _QC_SCALERQC2PDDOMAINCOLORCONVTEST,
    _QC_SCALERQC2PSCALEDOWNTEST,
    _QC_SCALERQC2PLSRTEST,
    _QC_SCALERQC2PFORMATCONVERSIONTEST,
    _QC_SCALERQC2PIPGTEST,
    _QC_SCALERQC2PIDOMAINCOLORCONVTEST,
    _QC_SCALERQC2PIDLTITEST,
    _QC_SCALERQC2PIDITHERTEST,
#endif

//----- D2 item -----//
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
    _QC_SCALERQCD2HDMITEST,
#endif
    _QC_SCALERQC420D2BISTTEST,
    _QC_SCALERQCFRCTEST,

//----- D3 item -----//
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
    _QC_SCALERQCD3HDMITEST,
#endif
    _QC_SCALERQC420D3BISTTEST,
    _QC_SCALERQCODTEST,

//----- D4 item -----//
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
    _QC_SCALERQCD4HDMITEST,
#endif
    _QC_SCALERQCDSPCTEST,
    _QC_SCALERQCDPTXTEST,
    _QC_SCALERQCVBY1TXTEST,
    _QC_SCALERQCVBY1TXTEST2,

//----- D5 item -----//
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
    _QC_SCALERQCD5HDMITEST,
#if(_AUDIO_SUPPORT == _ON)
    _QC_SCALERQCD5AUDIOTEST,
#endif
#endif
    _QC_SCALERQC_COUNT,
};

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE xdata g_ucErrorCount;
BYTE xdata g_ucTestCount;

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
#if(_AUDIO_SUPPORT == _ON)
bit ScalerQCD5AudioTest(void);
extern void ScalerAudioD5HDMIAudioInitial(void);
extern EnumAudioSamplingFreqType ScalerAudioD5SamplingFreqDetect(void);
#endif
#endif

#if((_DP_SUPPORT == _ON) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
bit ScalerQCD0DpTest(void);
bit ScalerQCD0MstToSstSetting(void);
#endif

#if((_DP_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
bit ScalerQCD1DpTest(void);
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

void ScalerQCAllDigitalFunctionDisable(void);
bit ScalerQCWaitForIDDomainEvent(EnumWaitEventType enumEvent, BYTE ucDataPath);

#if((_QC_4P_MODE_ == _ON) || (_QC_5K3K_MODE_ == _ON))
void ScalerVGIPModeSwitch(BYTE ucMode);
void ScalerQCScalingDownDisable(void);
void ScalerQCModeSwitch(BYTE ucMode);
void ScalerQCSetDisplayTimingGenActiveRegion(BYTE ucMode);
void ScalerQCSetDisplayTimingGenBackground(BYTE ucMode);
#endif

bit ScalerQCDebug(BYTE ucNum, BYTE ucResult);
#if(_PCB_TYPE == _RL6410_QA_B_1A6mDP_DPTX_LVDS_eDP)
void ScalerQC7SegmentDisplay(BYTE ucNum);
#endif

BYTE ScalerQCGetIPCount(void);
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
    g_ucErrorCount = 0;
#if(_A0_PORT_TEST == _OFF)
    return _TRUE;
#endif

    if(ScalerQCDebug(_QC_SCALERQCVGAPGTEST, ScalerQCVGAPGTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCADCNRTEST, ScalerQCADCNRTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCRINGINGFILTERTEST, ScalerQCRingingFilterTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCDIGITALFILTERTEST, ScalerQCDigitalFilterTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCSCALEUPTEST, ScalerQCScaleUpTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCLSRTEST, ScalerQCLSRTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCOSDTEST_DISABLE, ScalerQCOSDTest(_DISABLE)) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCBISTTEST, ScalerQCBistTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

#if(_QC_4P_MODE_ == _ON)
// 4P Mode Test
    ScalerQCModeSwitch(_4P);

    if(ScalerQCDebug(_QC_SCALERQCFRC4PTEST_4P_A0, ScalerQCFRC4PTest(_4P)) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC4PSCALEUPTEST, ScalerQC4PScaleUpTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC4PLSRTEST, ScalerQC4PLSRTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC4PBISTTEST, ScalerQC4PBistTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }
#endif  // End of #if(_QC_4P_MODE_ == _ON)

    DebugMessageQC("6. #### A0 Port Done ####", 0x00);

    return g_ucErrorCount;
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
    g_ucErrorCount = 0;
#if(_D0_PORT_TEST == _OFF)
    return _TRUE;
#endif

#if((_DP_SUPPORT == _ON) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
    if(ScalerQCDebug(_QC_SCALERQCD0DPTEST, ScalerQCD0DpTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }
#endif // End of #if((_DP_SUPPORT == _ON) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))

    if(ScalerQCDebug(_QC_SCALERQC422TO444TEST, ScalerQC422to444Test()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCFORMATCONVERSIONTEST, ScalerQCFormatConversionTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCSCALEDOWNTEST, ScalerQCScaleDownTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

#if(_QC_4P_MODE_ == _ON)
// 4P Mode Test
    ScalerQCModeSwitch(_4P);

    if(ScalerQCDebug(_QC_SCALERQCFRC4PTEST_4P_D0, ScalerQCFRC4PTest(_4P)) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC4PSCALEDOWNTEST, ScalerQC4PScaleDownTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC4PSHPTEST, ScalerQC4PSHPTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC4PDDOMAINCOLORCONVTEST, ScalerQC4PDDomainColorConvTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC4PFORMATCONVERSIONTEST, ScalerQC4PFormatConversionTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC4P422TO444TEST, ScalerQC4P422to444Test()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC4PIDOMAINCOLORCONVTEST, ScalerQC4PIDomainColorConvTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC4PIDLTITEST, ScalerQC4PIDLTITest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC4PIDITHERTEST, ScalerQC4PIDitherTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }
#endif // #if(_QC_4P_MODE_ == _ON)

#if(_QC_5K3K_MODE_ == _ON)
// 5K3K_1P Mode Test
    ScalerQCModeSwitch(_5k3k_1P);

    if(ScalerQCDebug(_QC_SCALERQCFRC4PTEST_5K3K_1P, ScalerQCFRC4PTest(_5k3k_1P)) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KFORMATCONVERSIONTEST, ScalerQC5K3KFormatConversionTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KIPGTEST, ScalerQC5K3KIPGTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KIDOMAINCOLORCONVTEST, ScalerQC5K3KIDomainColorConvTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KIDLTITEST, ScalerQC5K3KIDLTITest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KIDITHERTEST, ScalerQC5K3KIDitherTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KSCALEUPTEST, ScalerQC5K3KScaleUpTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }
// 5K3K LSR Test must after SU
    if(ScalerQCDebug(_QC_SCALERQC5K3KLSRTEST, ScalerQC5K3KLSRTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KHLWTEST, ScalerQC5K3KHLWTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KDPGTEST, ScalerQC5K3KDPGTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KDPGRANDOMTEST, ScalerQC5K3KDPGRandomTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KSHPTEST, ScalerQC5K3KSHPTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KDDOMAINCOLORCONVTEST_5K3K_1P, ScalerQC5K3KDDomainColorConvTest(_5k3k_1P)) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KDCRTEST, ScalerQC5K3KDCRTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KDCCTEST, ScalerQC5K3KDCCTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KICMTEST, ScalerQC5K3KICMTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KCTSBRITEST, ScalerQC5K3KCTSBRITest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KIAPSGAINTEST, ScalerQC5K3KIAPSGainTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3K3DGAMMATEST, ScalerQC5K3K3DGammaTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KRGBGAMMATEST, ScalerQC5K3KRGBGammaTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KPCMTEST, ScalerQC5K3KPCMTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KPANELUNIFORMITYTEST, ScalerQC5K3KPanelUniformityTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KDDITHERTEST, ScalerQC5K3KDDitherTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCOSDTEST_ENABLE, ScalerQCOSDTest(_ENABLE)) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KODTEST, ScalerQC5K3KODTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

// 5K3K_PBP Mode Test
    ScalerQCModeSwitch(_5k3k_PBP);

    if(ScalerQCDebug(_QC_SCALERQCFRC4PTEST_5K3K_PBP, ScalerQCFRC4PTest(_5k3k_PBP)) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KSCALEDOWNTEST, ScalerQC5K3KScaleDownTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC5K3KDDOMAINCOLORCONVTEST_5K3K_PBP, ScalerQC5K3KDDomainColorConvTest(_5k3k_PBP)) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    // Disable Front/Back mode
    ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~(_BIT1 | _BIT0), 0x00);

#endif // End of #if(_QC_5K3K_MODE_ == _ON)

    DebugMessageQC("6. #### D0 Port Done ####", 0x00);

    return g_ucErrorCount;
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
    g_ucErrorCount = 0;
#if(_D1_PORT_TEST == _OFF)
    return _TRUE;
#endif

#if((_DP_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))

    if(ScalerQCDebug(_QC_SCALERQCD1DPTEST, ScalerQCD1DpTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }
#endif // End of #if((_DP_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))

    if(ScalerQCDebug(_QC_SCALERQCHLWTEST, ScalerQCHLWTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCIPGTEST, ScalerQCIPGTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCIDOMAINCOLORCONVTEST, ScalerQCIDomainColorConvTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCIDLTITEST, ScalerQCIDLTITest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCIDITHERTEST, ScalerQCIDitherTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCDPGTEST, ScalerQCDPGTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCDPGRANDOMTEST, ScalerQCDPGRandomTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCSHPTEST, ScalerQCSHPTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCDDOMAINCOLORCONVTEST, ScalerQCDDomainColorConvTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCDCRTEST, ScalerQCDCRTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCDCCTEST, ScalerQCDCCTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCICMTEST, ScalerQCICMTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCCTSBRITEST, ScalerQCCTSBRITest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCIAPSGAINTEST, ScalerQCIAPSGainTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC3DGAMMATEST, ScalerQC3DGammaTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCSRGBTEST, ScalerQCsRGBTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCRGBGAMMATEST, ScalerQCRGBGammaTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCPCMTEST, ScalerQCPCMTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCPANELUNIFORMITYTEST, ScalerQCPanelUniformityTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCGAMMATEST, ScalerQCGammaTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCDDITHERTEST, ScalerQCDDitherTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

#if(_QC_4P_MODE_ == _ON)
// PBP_LR Mode Test
    ScalerQCModeSwitch(_PBP_LR);

    if(ScalerQCDebug(_QC_SCALERQCFRC4PTEST_PBP_LR, ScalerQCFRC4PTest(_PBP_LR)) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC2PDPGTEST, ScalerQC2PDPGTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC2PDPGRANDOMTEST, ScalerQC2PDPGRandomTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC2PSHPTEST, ScalerQC2PSHPTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC2PDDOMAINCOLORCONVTEST, ScalerQC2PDDomainColorConvTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC2PSCALEDOWNTEST, ScalerQC2PScaleDownTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC2PLSRTEST, ScalerQC2PLSRTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    // I-domain IP
    ScalerQCScalingDownDisable();

    if(ScalerQCDebug(_QC_SCALERQC2PFORMATCONVERSIONTEST, ScalerQC2PFormatConversionTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC2PIPGTEST, ScalerQC2PIPGTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC2PIDOMAINCOLORCONVTEST, ScalerQC2PIDomainColorConvTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC2PIDLTITEST, ScalerQC2PIDLTITest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQC2PIDITHERTEST, ScalerQC2PIDitherTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

#endif  // End of #if(_QC_4P_MODE_ == _ON)

    DebugMessageQC("6. #### D1 Port Done ####", 0x00);

    return g_ucErrorCount;
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
    g_ucErrorCount = 0;
#if(_D2_PORT_TEST == _OFF)
    return _TRUE;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
    if(ScalerQCDebug(_QC_SCALERQCD2HDMITEST, ScalerQCD2HdmiTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }
#endif // End of #if(_D2_HDMI_SUPPORT == _ON)

    if(ScalerQCDebug(_QC_SCALERQC420D2BISTTEST, ScalerQC420D2BistTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCFRCTEST, ScalerQCFRCTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    DebugMessageQC("6. #### D2 Port Done ####", 0x00);

    return g_ucErrorCount;
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
    g_ucErrorCount = 0;
#if(_D3_PORT_TEST == _OFF)
    return _TRUE;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    if(ScalerQCDebug(_QC_SCALERQCD3HDMITEST, ScalerQCD3HdmiTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }
#endif // End of #if(_D3_HDMI_SUPPORT == _ON)

    if(ScalerQCDebug(_QC_SCALERQC420D3BISTTEST, ScalerQC420D3BistTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCODTEST, ScalerQCODTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    DebugMessageQC("6. #### D3 Port Done ####", 0x00);

    return g_ucErrorCount;
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
    g_ucErrorCount = 0;
#if(_D4_PORT_TEST == _OFF)
    return _TRUE;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
    if(ScalerQCDebug(_QC_SCALERQCD4HDMITEST, ScalerQCD4HdmiTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }
#endif

    // LVDS QC Test
    if(ScalerQCDebug(_QC_SCALERQCDSPCTEST, ScalerQCDSPCTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    // DPTx QC Test
    if(ScalerQCDebug(_QC_SCALERQCDPTXTEST, ScalerQCDPTXTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    // Vby1 QC Test
    if(ScalerQCDebug(_QC_SCALERQCVBY1TXTEST, ScalerQCVBY1TXTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    if(ScalerQCDebug(_QC_SCALERQCVBY1TXTEST2, ScalerQCVBY1TXTest2()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }

    DebugMessageQC("6. #### D4 Port Done ####", 0x00);

    return g_ucErrorCount;
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
    g_ucErrorCount = 0;
#if(_D5_PORT_TEST == _OFF)
    return _TRUE;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
    if(ScalerQCDebug(_QC_SCALERQCD5HDMITEST, ScalerQCD5HdmiTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }
#endif // End of #if(_D5_HDMI_SUPPORT == _ON)

#if(_AUDIO_SUPPORT == _ON)
    if(ScalerQCDebug(_QC_SCALERQCD5AUDIOTEST, ScalerQCD5AudioTest()) == _FALSE)
    {
#if(_QC_TEST_DEBUG  == _OFF)
        return g_ucErrorCount;
#endif
    }
#endif //End of #if(_AUDIO_SUPPORT == _ON)

    DebugMessageQC("6. #### D5 Port Done ####", 0x00);

    return g_ucErrorCount;
}

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Test Process for Audio D5 port
// Input Value  : None
// Output Value : Test Result
//--------------------------------------------------
bit ScalerQCD5AudioTest(void)
{
#if(_D5_HDMI_SUPPORT == _ON)

    ScalerAudioD5HDMIAudioInitial();

    ScalerTimerDelayXms(5);

    if(ScalerAudioD5SamplingFreqDetect() != 0x00)
    {
        // Clear HDMI audio FIFO overflow and underflow status
        ScalerSetBit(P74_CB_HDMI_SR, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        ScalerTimerDelayXms(5);

        // Check HDMI audio FIFO overflow and underflow
        if(ScalerGetBit(P74_CB_HDMI_SR, (_BIT2 | _BIT1)) == 0x00)
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
/*
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
*/
    if((pData[0] == _HDMI_D5_CRC0) && (pData[1] == _HDMI_D5_CRC1) && (pData[2] == _HDMI_D5_CRC2) &&
       (pData[3] == _HDMI_D5_CRC3) && (pData[4] == _HDMI_D5_CRC4) && (pData[5] == _HDMI_D5_CRC5))
    {
        DebugMessageQC("6. HDMI Test Pass", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_D5_CRC1) && (pData[1] == _HDMI_D5_CRC2) && (pData[2] == _HDMI_D5_CRC3) &&
       (pData[3] == _HDMI_D5_CRC4) && (pData[4] == _HDMI_D5_CRC5) && (pData[5] == _HDMI_D5_CRC0))
    {
        DebugMessageQC("6. HDMI Test Pass", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_D5_CRC2) && (pData[1] == _HDMI_D5_CRC3) && (pData[2] == _HDMI_D5_CRC4) &&
       (pData[3] == _HDMI_D5_CRC5) && (pData[4] == _HDMI_D5_CRC0) && (pData[5] == _HDMI_D5_CRC1))
    {
        DebugMessageQC("6. HDMI Test Pass", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_D5_CRC3) && (pData[1] == _HDMI_D5_CRC4) && (pData[2] == _HDMI_D5_CRC5) &&
       (pData[3] == _HDMI_D5_CRC0) && (pData[4] == _HDMI_D5_CRC1) && (pData[5] == _HDMI_D5_CRC2))
    {
        DebugMessageQC("6. HDMI Test Pass", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_D5_CRC4) && (pData[1] == _HDMI_D5_CRC5) && (pData[2] == _HDMI_D5_CRC0) &&
       (pData[3] == _HDMI_D5_CRC1) && (pData[4] == _HDMI_D5_CRC2) && (pData[5] == _HDMI_D5_CRC3))
    {
        DebugMessageQC("6. HDMI Test Pass", 0x00);
        return _TEST_PASS;
    }

    if((pData[0] == _HDMI_D5_CRC5) && (pData[1] == _HDMI_D5_CRC0) && (pData[2] == _HDMI_D5_CRC1) &&
       (pData[3] == _HDMI_D5_CRC2) && (pData[4] == _HDMI_D5_CRC3) && (pData[5] == _HDMI_D5_CRC4))
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
    BYTE ucplln = 0;
    WORD usDpHtotal = 0;
    WORD usDpVtotal = 0;
    DWORD ulVBs2BsCount = 0;
    DWORD ulDpNvidValue = 0;
    DWORD ulStreamClkValue = 0;
    DWORD ulXtal_clk = 0;

    if(ScalerGlobalGetIDCode() != _RL6410_VER_A_ID_CODE)
    {
        ulDpNvidValue = ((((DWORD)ScalerGetByte(PB6_1D_MSA_NVID_0)) << 16) | (((DWORD)ScalerGetByte(PB6_1E_MSA_NVID_1)) << 8) | ((DWORD)ScalerGetByte(PB6_1F_MSA_NVID_2)));

        usDpHtotal = ((((WORD)ScalerGetByte(PB5_41_MN_DPF_HTT_M)) << 8) | ((WORD)ScalerGetByte(PB5_42_MN_DPF_HTT_L)));

        usDpVtotal = ((((WORD)ScalerGetByte(PB5_49_MN_DPF_VTT_M)) << 8) | ((WORD)ScalerGetByte(PB5_4A_MN_DPF_VTT_L)));
    }

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

    // PLL Input Clock select to Link Clock/2, Output Clock Select to PLL Clock, Double Buffer.
    // PLL Input Clock select to Link Clock/2 for 6410-B, select to Crystal Clock for 6410-A
    if(ScalerGlobalGetIDCode() == _RL6410_VER_A_ID_CODE)
    {
        ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
    }
    else
    {
        ScalerSetBit(PA_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
    }

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

    if(ScalerGlobalGetIDCode() == _RL6410_VER_A_ID_CODE)
    {
        ulpllm = (SDWORD)((540 / 27) * ((((ScalerGetByte(0xB5A0) & 0x03) << 8) | ScalerGetByte(0xB5A1)) + 2) / (ScalerGetByte(0xB5A2) + 2) *
                 ((SDWORD)16384 * 32 * 4 + (((SDWORD)(ScalerGetByte(0xB5A4) & 0x07) << 16) | (SDWORD)(ScalerGetByte(0xB5A5) << 8) | (SDWORD)ScalerGetByte(0xB5A6))) * 2) / 16384 / 32 / 4;

        lOffsetValue = (SDWORD)((540 / 27) * ((((ScalerGetByte(0xB5A0) & 0x03) << 8) | ScalerGetByte(0xB5A1)) + 2) / (ScalerGetByte(0xB5A2) + 2) * 2 *
                       (((SDWORD)16384 * 32 * 4 + (((SDWORD)(ScalerGetByte(0xB5A4) & 0x07) << 16) | (SDWORD)(ScalerGetByte(0xB5A5) << 8) | (SDWORD)ScalerGetByte(0xB5A6))) / (SDWORD)ulpllm));

        lOffsetValue = lOffsetValue - (SDWORD)16384 * 32 * 4;
    }
    else
    {
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

        // PLL Reference Clock is Lin_Clk/2 (For 6410-B ECO)
        ulXtal_clk = (PDATA_DWORD(0) / 1000) / 2;

        ucplln = ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) / 2;

        ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB5_58_MN_MEAS_CTRL) & 0x1F)) << 16) | ((DWORD)ScalerGetByte(PB5_59_MN_MEAS_VLN_M) << 8) | ((DWORD)ScalerGetByte(PB5_5A_MN_MEAS_VLN_L)));

        ulStreamClkValue = (((((DWORD)usDpHtotal) * ((DWORD)usDpVtotal) * 100) / ulVBs2BsCount) * _GDI_CLK_KHZ * 10);

        ulpllm = (((ulStreamClkValue / 4) * ucplln / 250) / (ulXtal_clk));

        lOffsetValue = ((SDWORD)ulStreamClkValue - (SDWORD)((ulXtal_clk * 1000 / ucplln) * ulpllm)) * 32 / ulpllm * ucplln / ulXtal_clk * 16384 / 1000 * 4;
    }

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
    if(ScalerGlobalGetIDCode() == _RL6410_VER_A_ID_CODE)
    {
        ScalerSetByte(PA_A2_MN_SCLKG_DIVN, 0x00);
    }
    else
    {
        ScalerSetByte(PA_A2_MN_SCLKG_DIVN, ucplln - 2);
    }
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
#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
    // Disable Input HVsync error IRQ
    ScalerSetBit(P0_04_IRQ_CTRL0, ~_BIT5, 0x00);
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

                case _INPUT_PATH_ALL:
                    if(ScalerGetBit(P31_60_FRONT_BACK_CTRL, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6)) // 5K3K_1P Mode
                    {
                        if(enumEvent == _EVENT_IEN_START)
                        {
                            usEventFlagAddr = P0_03_STATUS1;
                        }
                        else
                        {
                            usEventFlagAddr = PC0_03_S2_STATUS1;
                        }
                    }
                    else // All Path use one source, only for QC
                    {
                        usEventFlagAddr = P0_03_STATUS1;
                    }
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

#if((_QC_4P_MODE_ == _ON) || (_QC_5K3K_MODE_ == _ON))
//--------------------------------------------------
// Description  : Mode Switch
// Input Value  : _4P       --> 4P Mode
//                _PBP_LR   --> PBP_LR Mode
// Output Value : None
//--------------------------------------------------
void ScalerQCModeSwitch(BYTE ucMode)
{
    switch(ucMode)
    {
        case _4P:
            DebugMessageQC("6. #### Mode Switch to 4P mode =", ucMode);
            break;
        case _PBP_LR:
            DebugMessageQC("6. #### Mode Switch to PBP_LR mode =", ucMode);
            break;
        case _5k3k_1P:
            DebugMessageQC("6. #### Mode Switch to 5K3K_1P mode =", ucMode);
            break;
        case _5k3k_PBP:
            DebugMessageQC("6. #### Mode Switch to 5K3K_PBP mode =", ucMode);
            break;
    }
    ScalerQCSetDisplayTimingGenActiveRegion(ucMode);
    ScalerQCSetDisplayTimingGenBackground(ucMode);
    ScalerQCSetScaling(ucMode);

    ScalerVGIPModeSwitch(ucMode);
    ScalerQCFRC(ucMode);
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
void ScalerVGIPModeSwitch(BYTE ucMode)
{
    switch(ucMode)
    {
        case _4P:
            // Disable full-to-FB
            ScalerSetBit(P31_60_FRONT_BACK_CTRL, ~(_BIT7 | _BIT6), 0x00);

            // Set extension length to 0
            ScalerSetByte(P31_66_EXTENSION_NUM, 0);

            ScalerVgipSetCaptureHWidth(GET_INPUT_TIMING_HWIDTH());
            ScalerVgipSetCaptureVHeight(GET_INPUT_TIMING_VHEIGHT());

            // Set horizontal width
            ScalerSetBit(P31_07_FC_FORMAT_PRO_MAIN_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(GET_INPUT_TIMING_HWIDTH()) & 0x1F));
            ScalerSetByte(P31_08_FC_FORMAT_PRO_MAIN_1, LOBYTE(GET_INPUT_TIMING_HWIDTH()));

            // Set formatconversion for S1/S2
            ScalerSetByte(P31_01_FC_INPUT_SEL_P23, ScalerGetByte(P31_00_FC_INPUT_SEL_P01));

            // Enable clock
            ScalerSetByte(P31_0D_FC_INPUT_CLK_GATING, 0x0F);

            // Disable E/O
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT7, 0x00);

            // Set Sub E/O width; Enable E/O for sub
            ScalerSetWord(P31_09_FC_FORMAT_PRO_SUB_0, ScalerGetWord(P31_07_FC_FORMAT_PRO_MAIN_0));
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
            ScalerSetWord(P31_61_FULLTOFB_HWIDTH_H, 0x00);

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
            break;

        case _5k3k_1P:

            // Enable F-to-P
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

            // Disable 1/2 SD
            ScalerSetBit(P31_05_FC_SD_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // Enable full-to-FB; size = 4k
            ScalerSetBit(P31_60_FRONT_BACK_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerSetWord(P31_61_FULLTOFB_HWIDTH_H, GET_INPUT_TIMING_HWIDTH());

            // Set extension length to _EXTENSION_PIXEL
            ScalerSetByte(P31_66_EXTENSION_NUM, _EXTENSION_PIXEL);

            // Set horizontal width
            ScalerSetBit(P31_07_FC_FORMAT_PRO_MAIN_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(GET_INPUT_TIMING_HWIDTH() / 2) & 0x1F));
            ScalerSetByte(P31_08_FC_FORMAT_PRO_MAIN_1, LOBYTE(GET_INPUT_TIMING_HWIDTH() / 2));

            // Set formatconversion for sub
            ScalerSetByte(P31_01_FC_INPUT_SEL_P23, ScalerGetByte(P31_00_FC_INPUT_SEL_P01));
            ScalerSetByte(P31_0D_FC_INPUT_CLK_GATING, 0x0F);

            // Set Sub E/O width; Enable E/O for sub
            ScalerSetWord(P31_09_FC_FORMAT_PRO_SUB_0, ScalerGetWord(P31_07_FC_FORMAT_PRO_MAIN_0));
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));

            // Set M1 capture to 2k1k; Set I-domain extension; Enlarge capture size;
            ScalerGlobalDoubleBufferEnable(_DISABLE);
            ScalerVgipSetCaptureHWidth(GET_INPUT_TIMING_HWIDTH() / 2 + _EXTENSION_PIXEL);
            ScalerVgipSetCaptureVHeight(GET_INPUT_TIMING_VHEIGHT());

            // Copy M1, M2 to S1, S2
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
            break;

        case _5k3k_PBP:
        case _PBP_LR:

            if(ucMode == _5k3k_PBP)
            {
                   // Enable F-to-P
                ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

                // Disable 1/2 SD
                ScalerSetBit(P31_05_FC_SD_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

                ScalerVgipSetCaptureHWidth(GET_INPUT_TIMING_HWIDTH());
                ScalerVgipSetCaptureVHeight(GET_INPUT_TIMING_VHEIGHT());

                // Set horizontal width
                ScalerSetBit(P31_07_FC_FORMAT_PRO_MAIN_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(GET_INPUT_TIMING_HWIDTH()) & 0x1F));
                ScalerSetByte(P31_08_FC_FORMAT_PRO_MAIN_1, LOBYTE(GET_INPUT_TIMING_HWIDTH()));
             }

            // Disable full-to-FB
            ScalerSetBit(P31_60_FRONT_BACK_CTRL, ~(_BIT7 | _BIT6), 0x00);

            // Set extension length to 0
            ScalerSetByte(P31_66_EXTENSION_NUM, 0);

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
            break;
    }
}

//--------------------------------------------------
// Description  : Display Timing Gen Background
// Input Value  : _4P       --> 4P Mode
//                _PBP_LR   --> PBP_LR Mode
// Output Value : None
//--------------------------------------------------
void ScalerQCSetDisplayTimingGenBackground(BYTE ucMode)
{
    WORD usDHTotal = _PANEL_DH_TOTAL;
    WORD usDHSyncWidth = _PANEL_DH_SYNC_WIDTH;
    WORD usDVSyncWidth = _PANEL_DV_SYNC_HEIGHT;
    WORD usDHStart = _PANEL_DH_START;
    WORD usDHWidth = _PANEL_DH_WIDTH;
    WORD usDVStart = _PANEL_DV_START;
    WORD usDVHeight = _PANEL_DV_HEIGHT;
    WORD usDVTotal = _PANEL_DV_TOTAL;
    BYTE ucExtension = 0;

    if((ucMode == _5k3k_1P) || (ucMode == _5k3k_PBP))
    {
        usDHTotal = 5320;
        usDHSyncWidth = 8;
        usDVSyncWidth = 2;
        usDHStart = 112;
        usDHWidth = 5120;
        usDVStart = 10;
        usDVHeight = 2880;
        usDVTotal = 2962;
    }

    if(ucMode == _5k3k_1P)
    {
#if(_EXTENSION_PIXEL == 20)
        ucExtension = 24;
#elif(_EXTENSION_PIXEL == 8)
        ucExtension = 0x0B;
#endif
    }

    // Set DHtotal
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHTotal - 4) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHTotal - 4));

    // Set DVtotal
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVTotal) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVTotal));

    // Set Free Run DVTotal = WD-Triggering DVTotal + 1 to Prevent DVTotal Too Long
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVTotal + 1) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVTotal + 1));

    // Set H sync width, must by 2x in even-odd-mode
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (usDHSyncWidth + usDHSyncWidth % 2));

    // Set V sync height
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0D_DISPLAY_VER_SYNC_END);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVSyncWidth));

    // Set Main H background st/ ed (Panel size)
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHStart) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHStart));

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHStart + usDHWidth) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHStart + usDHWidth));

    // Set Main V background st/ ed (Panel size)
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVStart) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVStart));

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVStart + usDVHeight) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVStart + usDVHeight));

    if((ucMode == _4P) || (ucMode == _PBP_LR) || (ucMode == _5k3k_PBP))
    {
        // Set Sub H background st/ ed (Panel size)
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_03_DISPLAY_HOR_BG_STA_H_S);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDHStart + usDHWidth/2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDHStart + usDHWidth/2));

        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_09_DISPLAY_HOR_BG_END_H_S);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDHStart + usDHWidth) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDHStart + usDHWidth));

        // Set Sub V background st/ ed (Panel size)
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_0E_DISPLAY_VER_BG_STA_H_S);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDVStart) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDVStart));

        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_14_DISPLAY_VER_BG_END_H_S);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDVStart + usDVHeight) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDVStart + usDVHeight));
    }

    // extension
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_MAIN);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, ucExtension);

    ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_1F_DISPLAY_EXTENSION_FB_SUB);
    ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, ucExtension);

    if(ucExtension != 0x00)
    {
        ScalerSetBit(P35_30_EXTENSION_EXTRA_WIN, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(P35_30_EXTENSION_EXTRA_WIN, ~_BIT0, 0x00);
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
    if(ucMode == _4P)
    {
        ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit(P35_00_MULTI_PIC_BLENDING, ~_BIT0, 0x00);
    }
    else if(ucMode == _PBP_LR)
    {
        ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT4 | _BIT3 | _BIT2));
        ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit(P35_00_MULTI_PIC_BLENDING, ~_BIT0, 0x00);
    }
    else if(ucMode == _5k3k_1P)
    {
        ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT4 | _BIT3 | _BIT2));
        ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~(_BIT1 | _BIT0), _BIT0);
        ScalerSetBit(P35_00_MULTI_PIC_BLENDING, ~_BIT0, _BIT0);
    }
    else if(ucMode == _5k3k_PBP)
    {
        ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT4 | _BIT3 | _BIT2));
        ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P35_00_MULTI_PIC_BLENDING, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(P0_2E_VIDEO_DISPLAY_CONTROL_REG1, ~(0x1F), (_BIT4 | _BIT3));
        ScalerSetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit(P35_00_MULTI_PIC_BLENDING, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set Display Timgin Gen: Diaplay active region
// Input Value  : NA
// Output Value : NA
//--------------------------------------------------
void ScalerQCSetDisplayTimingGenActiveRegion(BYTE ucMode)
{
    WORD usDHStart = _PANEL_DH_START;
    WORD usDHWidth = _PANEL_DH_WIDTH;
    WORD usDVStart = _PANEL_DV_START;
    WORD usDVHeight = _PANEL_DV_HEIGHT;

    if((ucMode == _5k3k_1P) || (ucMode == _5k3k_PBP))
    {
        usDHStart = 112;
        usDHWidth = 5120;
        usDVStart = 10;
        usDVHeight = 2880;
    }

    if(ucMode == _4P)
    {
        // Main1 Active
        // Set Main1 H Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHStart) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHStart));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHStart + usDHWidth / 2) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHStart + usDHWidth / 2));

        // Set Main1 V Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVStart) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVStart));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVStart + usDVHeight / 2) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVStart + usDVHeight / 2));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, 0x00);

        // Main2 Active
        // Set Main2 H Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_16_DISPLAY_HOR_ACT_STA_H_M2);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHStart) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHStart));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHStart + usDHWidth / 2) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHStart + usDHWidth / 2));

        // Set Main2 V Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1A_DISPLAY_VER_ACT_STA_H_M2);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVStart + usDVHeight / 2) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVStart + usDVHeight / 2));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVStart + usDVHeight) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVStart + usDVHeight));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG + 0x4000, ~_BIT5, 0x00);

        // Sub1 Active
        // Set Sub1 H Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_05_DISPLAY_HOR_ACT_STA_H_S1);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDHStart + usDHWidth / 2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDHStart + usDHWidth / 2));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDHStart + usDHWidth) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDHStart + usDHWidth));

        // Set Sub1 V Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_10_DISPLAY_VER_ACT_STA_H_S1);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDVStart) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDVStart));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDVStart + usDVHeight / 2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDVStart + usDVHeight / 2));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG + 0x8000, ~_BIT5, 0x00);

        // Sub2 Active
        // Set Sub2 H Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_16_DISPLAY_HOR_ACT_STA_H_S2);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDHStart + usDHWidth / 2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDHStart + usDHWidth / 2));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDHStart + usDHWidth) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDHStart + usDHWidth));

        // Set Sub2 V Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_1A_DISPLAY_VER_ACT_STA_H_S2);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDVStart + usDVHeight / 2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDVStart + usDVHeight / 2));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDVStart + usDVHeight) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDVStart + usDVHeight));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG + 0xC000, ~_BIT5, 0x00);
    }
    else if((ucMode == _PBP_LR) || (ucMode == _5k3k_PBP))
    {
        // Main1 Active
        // Set Main1 H Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHStart) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHStart));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHStart + usDHWidth / 2) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHStart + usDHWidth / 2));

        // Set Main1 V Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVStart + usDVHeight / 4) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVStart + usDVHeight / 4));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVStart + usDVHeight / 2 + usDVHeight / 4) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVStart + usDVHeight / 2 + usDVHeight / 4));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, 0x00);

        // Sub1 Active
        // Set Sub1 H Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_05_DISPLAY_HOR_ACT_STA_H_S1);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDHStart + usDHWidth / 2) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDHStart + usDHWidth / 2));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDHStart + usDHWidth) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDHStart + usDHWidth));

        // Set Sub1 V Active Start / End
        ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_10_DISPLAY_VER_ACT_STA_H_S1);
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDVStart + usDVHeight / 4) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDVStart + usDVHeight / 4));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, (HIBYTE(usDVStart + usDVHeight / 2 + usDVHeight / 4) & 0x1F));
        ScalerSetByte(P80_2B_DISPLAY_FORMAT_DATA_PORT_S, LOBYTE(usDVStart + usDVHeight / 2 + usDVHeight / 4));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG + 0x8000, ~_BIT5, 0x00);
    }
    else if(ucMode == _5k3k_1P)
    {
        // Main1 Active
        // Set Main1 H Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHStart) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHStart));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDHStart + usDHWidth) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDHStart + usDHWidth));

        // Set Main1 V Active Start / End
        ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H);
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVStart) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVStart));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usDVStart + usDVHeight) & 0x1F));
        ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usDVStart + usDVHeight));

        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, 0x00);
    }
}

#endif  // End of #if((_QC_4P_MODE_ == _ON) || (_QC_5K3K_MODE_ == _ON))

//--------------------------------------------------
// Description  : For QC Test Debug 7-segment Display
// Input Value  : ucNum: Error Number, ucResult: Result
// Output Value : None
//--------------------------------------------------
bit ScalerQCDebug(BYTE ucNum, BYTE ucResult)
{
    g_ucTestCount++;
    if(ucResult != 0x00)
    {
        ScalerSetByte(0x0006, ucNum);
        ScalerSetByte(0x000D, ucResult);

#if(_PCB_TYPE == _RL6410_QA_B_1A6mDP_DPTX_LVDS_eDP)
        ucNum = ((ucNum / 10) * 6) + ucNum;

        if(ucNum >= 0xA0)
        {
            ucNum -= 0xA0;
            MCU_FE48_PORTD0_PIN_REG = 1;
            ucNum += 1; // avoid show zero
        }
        ScalerQC7SegmentDisplay(ucNum);
#endif
        g_ucErrorCount++;
        return _FALSE;
    }
    else if(ucNum == 0x00)
    {
        ScalerQC7SegmentDisplay(ucNum);
    }
    return _TRUE;
}

//--------------------------------------------------
// Description  : Number change for 7-segment Display
// Input Value  : ucNum: Display Number
// Output Value : None
//--------------------------------------------------
#if(_PCB_TYPE == _RL6410_QA_B_1A6mDP_DPTX_LVDS_eDP)
void ScalerQC7SegmentDisplay(BYTE ucNum)
{
    BYTE ucNumH = (ucNum & 0xF0) >> 4;
    BYTE ucNumL = ucNum & 0x0F;

    switch(ucNumH)
    {
        case 0:
            PCB_LED1_Display_0();
            break;
        case 1:
            PCB_LED1_Display_1();
            break;
        case 2:
            PCB_LED1_Display_2();
            break;
        case 3:
            PCB_LED1_Display_3();
            break;
        case 4:
            PCB_LED1_Display_4();
            break;
        case 5:
            PCB_LED1_Display_5();
            break;
        case 6:
            PCB_LED1_Display_6();
            break;
        case 7:
            PCB_LED1_Display_7();
            break;
        case 8:
            PCB_LED1_Display_8();
            break;
        case 9:
            PCB_LED1_Display_9();
            break;
        default:
            PCB_LED1_Display_None();
            DebugMessageQC("7Segment fail - H", ucNumH);
            break;
    }

    switch(ucNumL)
    {
        case 0:
            PCB_LED2_Display_0();
            break;
        case 1:
            PCB_LED2_Display_1();
            break;
        case 2:
            PCB_LED2_Display_2();
            break;
        case 3:
            PCB_LED2_Display_3();
            break;
        case 4:
            PCB_LED2_Display_4();
            break;
        case 5:
            PCB_LED2_Display_5();
            break;
        case 6:
            PCB_LED2_Display_6();
            break;
        case 7:
            PCB_LED2_Display_7();
            break;
        case 8:
            PCB_LED2_Display_8();
            break;
        case 9:
            PCB_LED2_Display_9();
            break;
        default:
            PCB_LED2_Display_None();
            DebugMessageQC("7Segment fail - L", ucNumL);
            break;
    }
}
#endif // End of #if(_PCB_TYPE == _RL6410_QA_B_1A6mDP_DPTX_LVDS_eDP)

//--------------------------------------------------
// Description  : Return IP Count
// Input Value  : None
// Output Value : IP Count
//--------------------------------------------------
BYTE ScalerQCGetIPCount(void)
{
    return (_QC_SCALERQC_COUNT - 1);
}
#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)
