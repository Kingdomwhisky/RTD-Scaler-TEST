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
// ID Code      : RL6432_Series_QCInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
#define GET_DDR1_MEMORY_SIZE()                 (g_stDdr1MemorySizeInfo.b2Ddr1MemorySize)
#define SET_DDR1_MEMORY_SIZE(x)                (g_stDdr1MemorySizeInfo.b2Ddr1MemorySize = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _IMD_CRC_I_AFTER_VGIP = 0,
    _IMD_CRC_I_AFTER_IDITHER,
    _IMD_CRC_I_AFTER_SD,
    _IMD_CRC_M_AFTER_FIFO = 0,    
    _IMD_CRC_D_AFTER_DDITHER = 0,
    _IMD_CRC_D_AFTER_OD,    
}EnumCRCPosition;

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

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
typedef struct
{
    BYTE b2Ddr1MemorySize : 2;
} StructDdr1MemorySizeInfo;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#define _I_DOMAIN_CRC                               0
#define _M_DOMAIN_CRC                               1
#define _D_DOMAIN_CRC                               2

#define _FRAME_DELAY_TIME                           30
#define _CRC_DELAY_TIME                             30
#define _DISPLAY_DELAY_TIME                         1000

#define _TEST_PASS                                  0
#define _TEST_FAIL                                  1
#define _BIT_MODE_10                                0
#define _BIT_MODE_12                                1

//----------------------------------------------------------------------------
// BIST QC Test
//----------------------------------------------------------------------------
#define _BIST_TIMEOUT                               120

#define _GRAY                                       0
#define _MASS                                       1

#define _MSB                                        0
#define _LSB                                        1

#define _M1                                         _BIT3
#define _M2                                         _BIT2
#define _S1                                         _BIT1
#define _S2                                         _BIT0
#define _ROT_M1                                     _BIT5
#define _ROT_M2                                     _BIT4

#define _HSD_TABLE_SIZE                             128
#define _VSD_TABLE_SIZE                             64
#define _SU_TABLE_SIZE                              128

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
extern StructDdr1MemorySizeInfo g_stDdr1MemorySizeInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
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
extern void ScalerQCPrintCRC(BYTE ucFrame, BYTE ucPath, BYTE *ucCRC, BYTE ucNum);
extern bit ScalerQCCRCCompare(BYTE ucDomain, EnumCRCPosition enumPosition, BYTE ucSourceSel, BYTE *ucCRC, BYTE ucFrameNum);
extern bit ScalerQCDebug(BYTE ucNum, BYTE ucResult);

// D-domain
extern bit ScalerQCDPGTest(void);
extern bit ScalerQCDPGRandomTest(void);
extern bit ScalerQCSHPTest(void);
extern bit ScalerQCDDomainColorConvTest(void);

extern bit ScalerQCCTSBRITest(void);
extern bit ScalerQCIAPSGainTest(void);
extern bit ScalerQC3DGammaTest(void);
extern bit ScalerQCRGBGammaTest(void);
extern bit ScalerQCPCMTest(void);
extern bit ScalerQCsRGBTest(void);
extern bit ScalerQCGammaTest(void);
extern void ScalerQCGammaOff(void);
extern bit ScalerQCPanelUniformityTest(void);
extern bit ScalerQCDDitherTest(void);

#if(_PCB_TYPE == _RL6432_QA_B_1A2MHL2DP_DPTX_LVDS_eDP)
extern bit ScalerQCDSPCTest(void);
extern bit ScalerQCDPMSTTest(void);
extern bit ScalerQCeDPTXTest(void);
#endif

extern bit ScalerQCDCRTest(void); 
extern bit ScalerQCDCCTest(void);     
extern bit ScalerQCICMTest(void);

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
extern bit ScalerQCBistTest(void);
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
extern bit ScalerQCBistTest_D0(void);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
extern bit ScalerQCBistTest_D1(void);
#endif

// RL6432_Series_QC_OSD
extern bit ScalerQCOSDTest(void);

// RL6432_Series_QC_OD_FRC
extern bit ScalerQCFRCTest(void);
extern bit ScalerQCRotationTest(void);

extern void ScalerQCODDDomainPattern1(void);
extern void ScalerQCODDDomainPattern2(void);
extern bit ScalerQCODTest(void);

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
extern bit ScalerQCDDRTest(void);
extern void ScalerDDR1QcPowerControl(bit bOn);
extern void ScalerDDR1QcControlReset(void);
extern void ScalerDDR1QcSearchPhase();
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
extern bit ScalerQCSDRAMTest(void);
#endif

#endif

