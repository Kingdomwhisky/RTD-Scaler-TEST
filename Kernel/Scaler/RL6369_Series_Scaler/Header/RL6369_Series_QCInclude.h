/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6369_Series_QCInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_FACTORY_RTD_QC_SUPPORT == _ON)

#define _I_DOMAIN_CRC                               0
#define _M_DOMAIN_CRC                               1
#define _D_DOMAIN_CRC                               2

#define _FRAME_DELAY_TIME                           30
#define _CRC_DELAY_TIME                             30
#define _DISPLAY_DELAY_TIME                         1000

#define _TEST_PASS                                      0
#define _TEST_FAIL                                      1
#define _BIT_MODE_10                                    0
#define _BIT_MODE_12                                    1

//----------------------------------------------------------------------------
// BIST QC Test
//----------------------------------------------------------------------------
#define _BIST_TIMEOUT                                   120

#define _GRAY                                           0
#define _MASS                                           1

#define _MSB                                            0
#define _LSB                                            1

#define _M1                                             _BIT3
#define _M2                                             _BIT2
#define _S1                                             _BIT1
#define _S2                                             _BIT0
#define _ROT_M1                                         _BIT5
#define _ROT_M2                                         _BIT4

#define _HSD_TABLE_SIZE                                 128
#define _VSD_TABLE_SIZE                                 64
#define _SU_TABLE_SIZE                                  128


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _I_CRC_AFTER_VGIP = 0,
    _I_CRC_AFTER_IDITHER,
    _I_CRC_AFTER_SD,
    _M_CRC_AFTER_FIFO,
    _D_CRC_AFTER_DDITHER,
    _D_CRC_AFTER_OD,
} EnumCRCPosition;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

extern bit ScalerQCVGAPGTest(void);
extern bit ScalerQCADCNRTest(void);
extern bit ScalerQCRingingFilterTest(void);
extern bit ScalerQCDigitalFilterTest(void);

// I-domain
extern bit ScalerQC422to444Test(void);
extern bit ScalerQCIPGTest(void);
extern bit ScalerQCIDomainColorConvTest(void);
extern bit ScalerQCIDitherTest(void);
extern bit ScalerQCScaleDownTest(void);
extern bit ScalerQCHLWTest(void);

// M-domain
extern bit ScalerQCLSRTest(void);
extern bit ScalerQCScaleUpTest(void);

// Common Function
extern void ScalerQCVGATopRandomGenOff(void);
extern void ScalerQCIDomainRandomGenOn(bit bRandomSelect);
extern void ScalerQCIDomainRandomGenOff(void);
extern void ScalerQCHighlightWindowOn(void);
extern void ScalerQCHighlightWindowOff(void);
extern void ScalerQCDDomainRandomGenOn(bit bRandomSelect);
extern void ScalerQCDDomainPatternGenOff(void);
extern void ScalerQCDDomainPatternGenOn(void);

// D-domain
extern bit ScalerQCDPGTest(void);
extern bit ScalerQCDPGRandomTest(void);
extern bit ScalerQCDDomainColorConvTest(void);

extern bit ScalerQCCTSBRITest(void);
extern bit ScalerQCPCMTest(void);
extern bit ScalerQCsRGBTest(void);
extern bit ScalerQCGammaTest(void);
extern bit ScalerQCDDitherTest(void);
extern bit ScalerQCBackGroundColor(void);
extern bit ScalerQCYPeakingTest(void);

#if(_PCB_TYPE == _RL6369_QA_1A2MHL1DP)
extern bit ScalerQCDSPCTest(void);
#endif

extern bit ScalerQCDCRTest(void);
extern bit ScalerQCDCCTest(void);
extern bit ScalerQCICMTest(void);
extern bit ScalerQCCRCCompare(EnumCRCPosition enumPosition, BYTE *ucCRC, BYTE ucFrameNum);

/*
// Bank24: RL6369_Series_QC!G
extern bit ScalerQCCRCCompare(BYTE ucDomain, BYTE ucPosition, BYTE ucSourceSel, BYTE *ucCRC, BYTE ucFrameNum);
extern void ScalerQCIDomainRandomGenOn(bit bRandomSelect);
extern void ScalerQCIDomainRandomGenOff(void);

// Bank24: RL6369_Series_QC_II!G
extern void ScalerQCHighlightWindowOn(void);
extern void ScalerQCHighlightWindowOff(void);

extern void ScalerQCDDomainPatternGenOff(void);
extern void ScalerQCDDomainRandomGenOn(bit bRandomSelect, bit bModeSel);

extern bit ScalerQCDPGTest(void);
extern bit ScalerQCDPGRandomTest(void);
extern bit ScalerQCCTSBRITest(void);
extern bit ScalerQCPCMTest(void);
extern bit ScalerQCsRGBTest(void);
extern bit ScalerQCGammaTest(void);
extern bit ScalerQCDDitherTest(void);
*/

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
extern bit ScalerQCBistTest(void);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
extern bit ScalerQCBistTest_D1(void);
#endif

// Bank30: RL6369_Series_QC_OSD!G
extern bit ScalerQCOSDTest(void);

// Bank31: RL6369_Series_QC_OD_FRC!G
extern bit ScalerQCFRCTest(void);
extern void ScalerQCODDDomainPattern1(void);
extern void ScalerQCODDDomainPattern2(void);
extern bit ScalerQCODTest(void);

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif

