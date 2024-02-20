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
// ID Code      : RL6449_Series_QCInclude.h No.0000
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

typedef enum
{
    _I_CRC_AFTER_VGIP = 0,
    _I_CRC_AFTER_IDITHER,
    _I_CRC_AFTER_SD,
    _M_CRC_AFTER_FIFO = 0,
}EnumIMCRCPosition;

typedef enum
{
    _D_CRC_AFTER_DDITHER,
    _D_CRC_AFTER_OD,
}EnumDCRCPosition;


#define _HSD_TABLE_SIZE                                 128
#define _VSD_TABLE_SIZE                                 64
#define _SU_TABLE_SIZE                                  128

//----------------------------------------------------------------------------
// 4P Mode, PBP_LR Mode Test
//----------------------------------------------------------------------------
#if(_QC_4P_MODE_ == _ON)
#define _4P                                     0
#define _PBP_LR                                 1
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _INPUT_PATH_NONE = 0,
    _INPUT_PATH_M1 = 0x01,
    _INPUT_PATH_M2 = 0x02,
    _INPUT_PATH_M1_M2 = 0x03,
    _INPUT_PATH_S1 = 0x04,
    _INPUT_PATH_S2 = 0x08,
    _INPUT_PATH_S1_S2 = 0x0C,
    _INPUT_PATH_ALL = 0x0F,
} EnumInputDataPath;

typedef enum
{
    _DISPLAY_PATH_NONE = 0,
    _DISPLAY_PATH_M1 = 0x01,
    _DISPLAY_PATH_M2 = 0x02,
    _DISPLAY_PATH_M1_M2 = 0x03,
    _DISPLAY_PATH_S1 = 0x04,
    _DISPLAY_PATH_S2 = 0x08,
    _DISPLAY_PATH_S1_S2 = 0x0C,
    _DISPLAY_PATH_ALL = 0x0F,
} EnumDisplayDataPath;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

extern bit ScalerQCVGAPGTest(void);
extern bit ScalerQCADCNRTest(void);
extern bit ScalerQCRingingFilterTest(void);
extern bit ScalerQCDigitalFilterTest(void);

// I-domain
extern bit ScalerQC422to444Test(void);
extern bit ScalerQCFormatConversionTest(void);
extern bit ScalerQCIPGTest(void);
extern bit ScalerQCIDomainColorConvTest(void);
extern bit ScalerQCIDLTITest(void);
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
extern void ScalerQCDDomainRandomGenOn(bit bRandomSelect, bit bModeSel);
extern void ScalerQCDDomainPatternGenOff(void);
extern bit ScalerQCWaitForIDDomainEvent(EnumWaitEventType enumEvent, BYTE ucDataPath);
extern bit ScalerQCCRCCompare(BYTE ucDomain, EnumIMCRCPosition enumPosition, BYTE ucSourceSel, BYTE *ucCRC, BYTE ucFrameNum);
extern void ScalerQCDebug(BYTE ucNum, BYTE ucResult);

// D-domain
extern bit ScalerQCDPGTest(void);
extern bit ScalerQCDPGRandomTest(void);
extern bit ScalerQCSHPTest(void);
extern bit ScalerQCDDomainColorConvTest(void);

extern bit ScalerQCCTSBRITest(void);
extern bit ScalerQCIAPSGainTest(void);
extern bit ScalerQC3DGammaTest(void);
extern bit ScalerQCPCMTest(void);
extern bit ScalerQCsRGBTest(void);
extern bit ScalerQCGammaTest(void);
extern void ScalerQCGammaOff(void);
extern bit ScalerQCDDitherTest(void);
extern bit ScalerQCRGBGammaTest(void);
extern bit ScalerQCPanelUniformityTest(void);

#if(_QC_4P_MODE_ == _ON)
extern void ScalerQCSetScaling(bit bMode);
extern bit ScalerQC4PFormatConversionTest(void);
extern bit ScalerQC4PIDomainColorConvTest(void);
extern bit ScalerQC4PIDLTITest(void);
extern bit ScalerQC4PIDitherTest(void);
extern bit ScalerQC4PScaleDownTest(void);
extern bit ScalerQC4PLSRTest(void);
extern bit ScalerQC4PScaleUpTest(void);
extern bit ScalerQC4PSHPTest(void);
extern bit ScalerQC4PDDomainColorConvTest(void);
extern bit ScalerQC4PBistTest(void);

extern bit ScalerQC4P422to444Test(void);
extern bit ScalerQC2PFormatConversionTest(void);
extern bit ScalerQC2PIPGTest(void);
extern bit ScalerQC2PIDomainColorConvTest(void);
extern bit ScalerQC2PIDLTITest(void);
extern bit ScalerQC2PIDitherTest(void);
extern bit ScalerQC2PScaleDownTest(void);
extern bit ScalerQC2PLSRTest(void);
extern bit ScalerQC2PSHPTest(void);
extern bit ScalerQC2PDPGTest(void);
extern bit ScalerQC2PDPGRandomTest(void);
extern bit ScalerQC2PSHPTest(void);
extern bit ScalerQC2PDDomainColorConvTest(void);
#endif  // End of #if(_QC_4P_MODE_ == _ON)

extern bit ScalerQCDSPCTest(void);
extern bit ScalerQCDPTXTest(void);
extern bit ScalerQCVBY1TXTest(void);
extern bit ScalerQCDPTXTest(void);
extern bit ScalerQCDCRTest(void);
extern bit ScalerQCDCCTest(void);
extern bit ScalerQCICMTest(void);

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
extern bit ScalerQCBistTest(void);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
extern bit ScalerQC420D2BistTest(void);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
extern bit ScalerQC420D3BistTest(void);
#endif

// Bank30: RL6410_Series_QC_OSD!G
extern bit ScalerQCOSDTest(void);

// Bank31: RL6410_Series_QC_OD_FRC!G
extern bit ScalerQCFRCTest(void);
extern void ScalerQCODDDomainPattern1(void);
extern void ScalerQCODDDomainPattern2(void);
extern bit ScalerQCODTest(void);

#if(_QC_4P_MODE_ == _ON)
extern void ScalerQCFRC(BYTE ucDispMode);
extern bit ScalerQCFRC4PTest(BYTE ucDispMode);
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif

