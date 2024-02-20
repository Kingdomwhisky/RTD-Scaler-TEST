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
// ID Code      : UserCommonDisplayCalibrationGen1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DISPLAY_CALIBRATION__

#include "UserCommonInclude.h"

#if(_SCALER_TYPE == _RL6369_SERIES)
#include "RL6369_Series_RegCommonInclude.h"
#elif(_SCALER_TYPE == _RL6410_SERIES)
#include "RL6410_Series_Common_RegCommonInclude.h"
#elif(_SCALER_TYPE == _RL6432_SERIES)
#include "RL6432_Series_Common_RegCommonInclude.h"
#elif(_SCALER_TYPE == _RL6449_SERIES)
#include "RL6449_Series_Common_RegCommonInclude.h"
#elif(_SCALER_TYPE == _RL6463_SERIES)
#include "RL6463_Series_RegCommonInclude.h"
#elif(_SCALER_TYPE == _RL6492_SERIES)
#include "RL6492_Series_Common_RegCommonInclude.h"
#endif

#if(_OGC_GEN_TYPE == _OGC_GEN_1)  // Gen 1 for RL6193

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//***************************************************************************
//--------------------------------------------------
// Definitions of OGC/OCC/DICOM
//--------------------------------------------------
//CheckSum Type
#define _OGC_TYPE                   0
#define _OCC_TYPE                   1
#define _DICOM_TYPE                 2
#define _RGB_GAIN_TYPE              3
#define _COLOR_MATRIX_TYPE          4
#define _OGC_RGBGAMMA_TYPE          5
#define _HDR_TYPE                   6
#define _HEADER_TYPE                7
#define _OCC_HDR_TYPE               8
#define _DIMMING_OG_TYPE            9
#define _DIMMING_IG_TYPE            10
#define _FREESYNC_II_OG_TYPE        11
#define _EDID_INFO_TYPE             12
#define _FREESYNC_II_IG_TYPE        13
#define _HDR10_NOTM_BOUND_TYPE      14
#define _COLOR_MATRIX_TYPE2         15
#define _HDRPLUS_TYPE               16
#define _RGB_GAIN_MAX_BRI_TYPE      17
#define _COLOR_MATRIX_MAX_BRI_TYPE  18
#define _COLOR_MATRIX_MAX_BRI_TYPE2 19
#define _NOTM_DCR_THD_TYPE          20
#define _OGC_MAX_BRI_TYPE           21

//Calibration Type
#define _OGC_CAL_TYPE               0
#define _OCC_CAL_TYPE               1
#define _DICOM_CAL_TYPE             2
#define _DIMMING_CAL_TYPE           7

#define _FREESYNC_II_CAL_TYPE       0

#define _DISP_CALIB_START           0
#define _DISP_CALIB_PASS            1
#define _DISP_CALIB_ERASE_ERROR     2
#define _DISP_CALIB_FW_ERROR        3
#define _DISP_CALIB_CRC_ERROR       4
#define _DISP_CALIB_FAIL            5
#define _DISP_CALIB_GET_VERSION     6
#define _DISP_CALIB_GET_NOTM_INFO   7
#define _DISP_CALIB_GET_UNI_VERSION 8
#define _DISP_CALIB_GET_FW_SUPPORT  9

#define _NORMAL_BACKLIGHT_CAL       0
#define _MAX_BACKLIGHT_CAL          1

#define _FREESYNC_II_WHITE          0
#define _LD_BOOST_WHITE             1

#define _BG_PATTERN                 0
#define _PG_PATTERN                 1
#define _PATTERN_TOP                ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT) ? 1023 : 1020)
#define _NOTM_DCR_THD_LENGTH        (_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT ? 6 : 2)
#if(_HDR10_SUPPORT == _ON)
#define _NOTM_BOUND_SAVE_LENGTH     (_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT ? 13 : 9)
#endif
//--------------------------------------------------
// Definitions of HDR Input Gamma
//--------------------------------------------------
#define _DISP_CALIB_VERSION         (3 + _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT)
#define _HDR_TOTAL_IG               (12 + 8 * _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT + 2 * (_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT ? 1 : 0) + ((_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1) ? 1 : 0))

//--------------------------------------------------
// Definitions of FW Version
//--------------------------------------------------
#define _DISP_CALIB_FW_VERSION      0x000E
#define _DISP_CALIB_UNI_VERSION     0x0006

#if(_DISP_CALIBRATION_PCM_END + _OGC_SUPPORT * _OGC_TOTAL_GAMMA * _OGC_GAMMA_TABLE_SIZE + (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0) * _OGC_SUPPORT * _OGC_TOTAL_GAMMA * _OGC_GAMMA_TABLE_SIZE > 0xFFFF)
#if(_FREESYNC_II_SUPPORT == _ON)
#warning "NOTE: Please check whether _FREESYNC_II_FLASH_BANK is lager than _OGC_FLASH_BANK + 1!"
#if(_UNIFORMITY_SUPPORT == _ON)
#warning "NOTE: Please check whether _UNIFORMITY_FLASH_BANK0 is lager than _OGC_FLASH_BANK + 2!"
#endif
#else
#if(_UNIFORMITY_SUPPORT == _ON)
#warning "NOTE: Please check whether _UNIFORMITY_FLASH_BANK0 is lager than _OGC_FLASH_BANK + 1!"
#endif
#endif
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
#warning "NOTE: PCM should use Max Backlight table when UNIFORMITY ON!!!"
#endif
#endif

typedef enum
{
#if(_OGC_SUPPORT == _ON)
    _GAMMA1_POSITION,
#if(_OGC_TOTAL_GAMMA > 1)
    _GAMMA2_POSITION,
#if(_OGC_TOTAL_GAMMA > 2)
    _GAMMA3_POSITION,
#if(_OGC_TOTAL_GAMMA > 3)
    _GAMMA4_POSITION,
#if(_OGC_TOTAL_GAMMA > 4)
    _GAMMA5_POSITION,
#if(_OGC_TOTAL_GAMMA > 5)
    _GAMMA6_POSITION,
#endif
#endif
#endif
#endif
#endif
#endif

#if(_OCC_SUPPORT == _ON)
    _OCC_POSITION,
#endif
#if(_OGC_DICOM_SUPPORT == _ON)
    _DICOM_POSITION,
#endif
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
    _DIMMING_POSITION,
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
    _OCC_FREESYNC_II_POSITION,
#endif
#if((_HDR10_SUPPORT == _ON) || (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR))
    _OCC_HDR_POSITION,
#endif
    _NONE_VALUE,
} EnumOGCTypePos;

//--------------------------------------------------
// Definitions of Uniformity
//--------------------------------------------------
#define _UNIFORMITY_GAIN_TYPE       7
#define _UNIFORMITY_OFFSET_TYPE     6
#define _UNIFORMITY_DECAY_TYPE      5

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
StructCalibrationInfo g_stCalibrationInfo;


//****************************************************************************
// CODE TABLES
//****************************************************************************

//--------------------------------------------------
// Table of OGC/OCC/DICOM
//--------------------------------------------------
WORD code tOGC_GRAY_TABLE[] =
{
    252 * 4, 244 * 4, 232 * 4,
    216 * 4, 196 * 4, 172 * 4,
    148 * 4, 124 * 4, 96 * 4,
    68 * 4,  44 * 4,  24 * 4,
    12 * 4,  6 * 4,   2 * 4,
    0
};

#if(_OCC_SUPPORT == _ON)
BYTE code tSRGBByPass[] =
{
    0,0,0,0,0,0,
    0,0,0,0,0,0,
    0,0,0,0,0,0
};

BYTE code tSRGBHalf[] =
{
    0x01, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x80,
};
//--------------------------------------------------
// sRGB Table for OCC
//--------------------------------------------------
#if(_OCC_LUT_MODE == _OFF)
WORD code tOCC_SRGB_TABLE[] =
{
    192 * 4,  80 * 4,  80 * 4,
    192 * 4, 192 * 4,  80 * 4,
    96 * 4, 192 * 4,  96 * 4,
    96 * 4, 192 * 4, 192 * 4,
    128 * 4, 128 * 4, 192 * 4,
    192 * 4, 128 * 4, 192 * 4,
    1023, 1023, 1023,
};
#else
WORD code tOCC_SRGB_TABLE[] =
{
    1023,0,0,
    0,1023,0,
    0,0,248 * 4,
    1023,1023,0,
    1023,0,248 * 4,
    0,1023,248 * 4,
    1023,1023,1023,

    128 * 4,0,0,
    0,128 * 4,0,
    0,0,128 * 4,
    128 * 4,128 * 4,0,
    128 * 4,0,128 * 4,
    0,128 * 4,128 * 4,
    96 * 4,96 * 4,96 * 4,

    192 * 4,0,0,
    0,192 * 4,0,
    0,0,192 * 4,
    192 * 4,192 * 4,0,
    192 * 4,0,192 * 4,
    0,192 * 4,192 * 4,
    192 * 4,192 * 4,192 * 4
};
#endif
#endif

WORD code tGAMMA_INDEX[] =
{
#if(_OGC_SUPPORT == _ON)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 1)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 2)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 3)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 4)
    _OGC_NONE_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 5)
    _OGC_NONE_ADDRESS,
#endif
#endif
#endif
#endif
#endif
#endif

#if(_OCC_SUPPORT == _ON)
    _OCC_GAMMA10_ADDRESS,
#endif

#if(_OGC_DICOM_SUPPORT == _ON)
    _OGC_DICOM_ADDRESS,
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
    _DIMMING_OCC_GAMMA10_ADDRESS,
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    _FREESYNC_II_OCC_GAMMA10_ADDRESS,
#endif

#if((_HDR10_SUPPORT == _ON) || (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR))
    _OCC_HDR10_GAMMA10_ADDRESS,
#endif
};

WORD code tHDR10IGAMMA_INDEX[] =
{
    _OGC_HDR10_IG_1200_NOR_ADDRESS,
    _OGC_HDR10_IG_1200_DARK_ADDRESS,
    _OGC_HDR10_IG_4000_NOR_ADDRESS,
    _OGC_HDR10_IG_4000_DARK_ADDRESS,
    _OGC_HDR10_IG_10000_NOR_ADDRESS,
    _OGC_HDR10_IG_10000_DARK_ADDRESS,
    _OGC_HDR10_IG_540_NOR_ADDRESS,
    _OGC_HDR10_IG_540_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_NOR_ADDRESS,
    _OGC_HDR10_IG_NOTM_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS,
    _OGC_HDR10_IG_NOTM_PEAK_DARK_ADDRESS,
    _OGC_HDR10_IG_540_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_540_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_1200_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_1200_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_4000_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_4000_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_10000_FIXED_POINT_NOR_ADDRESS,
    _OGC_HDR10_IG_10000_FIXED_POINT_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS,
    _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_DARK_ADDRESS,
    _OGC_HDR10_IG_NOTM_DISPLAY_HDR_1_1_ADDRESS,
};

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
#if(_OGC_SUPPORT == _ON)
WORD code tDIMMINGIGAMMA_INDEX[] =
{
    _DIMMING_OGC_GAMMA1_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 1)
    _DIMMING_OGC_GAMMA2_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 2)
    _DIMMING_OGC_GAMMA3_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 3)
    _DIMMING_OGC_GAMMA4_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 4)
    _DIMMING_OGC_GAMMA5_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 5)
    _DIMMING_OGC_GAMMA6_ADDRESS,
#endif
#endif
#endif
#endif
#endif
};
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
WORD code tFREESYNC2IGAMMA_INDEX[] =
{
    _FREESYNC_II_IG_SRGB_ADDRESS,
    _FREESYNC_II_IG_BT709_ADDRESS,
    _FREESYNC_II_IG_GAMMA22_ADDRESS,
    _FREESYNC_II_IG_GAMMA26_ADDRESS,
    _FREESYNC_II_IG_PQINTERIM_ADDRESS,
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE xdata *g_pucDISP_CALIBRATION_FLASH = _OGC_FLASH_PAGE * _FLASH_PAGE_SIZE;
BYTE xdata *g_pucDISP_FREESYNC_II_CALIBRATION_FLASH = _FREESYNC_II_FLASH_PAGE * _FLASH_PAGE_SIZE;

WORD g_ppusGammaCount[][3] =
{
#if(_OGC_SUPPORT == _ON)
    {2052, 2052, 2052},
#if(_OGC_TOTAL_GAMMA > 1)
    {2052, 2052, 2052},
#if(_OGC_TOTAL_GAMMA > 2)
    {2052, 2052, 2052},
#if(_OGC_TOTAL_GAMMA > 3)
    {2052, 2052, 2052},
#if(_OGC_TOTAL_GAMMA > 4)
    {2052, 2052, 2052},
#if(_OGC_TOTAL_GAMMA > 5)
    {2052, 2052, 2052},
#endif
#endif
#endif
#endif
#endif
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_SUPPORT == _ON)
    {2200, 2200, 2200},  // To be Edit
#endif

#if(_OGC_DICOM_SUPPORT == _ON)
    {2052, 2052, 2052},
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
    {2200, 2200, 2200},
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    {2200, 2200, 2200},
#endif
};

WORD g_usCTGainSavePos;
#if(_UNIFORMITY_SUPPORT == _ON)
BYTE g_ucUniformityLUTSaveBank = _UNIFORMITY_FLASH_BANK0;
BYTE g_ucUniformityLUTStartPosIndex;
WORD g_usUniformityLUTSavePos;
#endif
WORD g_usColorMatrixSavePos;

BYTE g_ucCalibrationType;
BYTE g_ucCalibrationTypeII;
BYTE g_ucUniformityChecksumType;
BYTE g_ucPatternType = _BG_PATTERN;

BYTE g_ucBacklightFlag;
#if((_HDR10_SUPPORT == _ON) || (_BACKLIGHT_DIMMING_SUPPORT == _ON) || (_FREESYNC_II_SUPPORT == _ON))
BYTE g_ucIGLUTSavePos;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonDdcciDispCalibShowCalibPattern(WORD usRed, WORD usGreen, WORD usBlue);
void UserCommonDdcciDispCalibCalibPatternEnable(bit bEnable);
void UserCommonDdcciDispCalibProcess(void);
bit UserCommonDdcciDispCalibOGCStart(void);

#if(_OCC_SUPPORT == _ON)
BYTE UserCommonDdcciDispCalibOCCProcess(BYTE ucStep);
#endif
void UserCommonDdcciDispCalibAccessPanelColorMatchingData(BYTE ucCommand);

bit UserCommonDdcciDispCalibInitialCheck(void);
void UserCommonDdcciDispCalibFlashData(bit bReadWrite, BYTE ucBank, BYTE ucIndex, WORD usAddr, WORD usLength, BYTE *pucData);
void UserCommonDdcciDispCalibSaveLUT(BYTE ucTotalLength);
BYTE UserCommonDdcciDispCalibCalCheckSum(BYTE ucCheckType);
void UserCommonDdcciDispCalibShowGamma(void);
BYTE UserCommonDdcciDispCalibCheckSum(void);

BYTE UserCommonDdcciDispCalibMatrixCheckSum(BYTE ucCheckType);

void UserCommonDdcciDispCalibReplyResult(BYTE ucType);
void UserCommonDdcciDispCalibSaveHeader(void);
void UserCommonDdcciDispCalibSaveEDIDInfo(void);
void UserCommonDdcciDispCalibSaveNoToneMappingDCRTHD(void);

#if(_HDR10_SUPPORT == _ON)
void UserCommonDdcciDispCalibSaveHDR10BoundInfo(void);
#endif

#if((_FREESYNC_II_SUPPORT == _ON) || (_LD_HDR10_BOOST_SUPPORT == _ON))
void UserCommonDdcciDispCalibShowWhite(BYTE ucPatternType);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)

void UserCommonDdcciDispCalibReplyOCCMatrix(BYTE ucPCMType);
void UserCommonDdcciDispCalibReplyOGCHeader(void);
void UserCommonDdcciDispCalibReplyOGCOCCLvRatio(void);
void UserCommonDdcciDispCalibReplyUniformityDefine(void);
void UserCommonDdcciDispCalibReplyCCTGain(void);
void UserCommonDdcciDispCalibReplyFastModeData(void);
void UserCommonDdcciDispCalibReplyUniformityLevelMode(void);
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
void UserCommonDdcciDispCalibReplyDimmingDefine(void);
void UserCommonDdcciDispCalibSetPWMValue(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#define _OGC_FLASH_PAGE             0

//--------------------------------------------------
// Description  : Show Calibration Pattern
// Input Value  : WORD usRed, WORD usGreen, WORD usBlue
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibShowCalibPattern(WORD usRed, WORD usGreen, WORD usBlue)
{
    if(g_ucPatternType == _PG_PATTERN)
    {
        ScalerDDomainPatternGenAdjustColor10bit(usRed, usGreen, usBlue);
    }
    else
    {
        ScalerDDomainBackgroundSetColor10bit(usRed, usGreen, usBlue);
    }
}
//--------------------------------------------------
// Description  : Calibration Pattern Enable
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibCalibPatternEnable(bit bEnable)
{
    if(g_ucPatternType == _PG_PATTERN)
    {
        ScalerDDomainPatternGenEnable(bEnable);
    }
    else
    {
        ScalerDDomainBackgroundEnable(bEnable);
    }
}
//--------------------------------------------------
// Description  : Do OGC/OCC/DICOM Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibProcess(void)
{
    BYTE ucCalibrationStep = 0;
    BYTE ucFlag = 1;
#if((_OGC_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON) || (_FREESYNC_II_SUPPORT == _ON))
    BYTE ucGammaIndex = 0;
#endif

#if(_OGC_SUPPORT == _ON)
    BYTE ucColorTempIndex = 0;
#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
    WORD pusBriTemp[3] = {0x200, 0x200, 0x200};
#else
    WORD pusBriTemp[3] = {0x80, 0x80, 0x80};
#endif
#endif

    WORD usR = 0;
    WORD usG = 0;
    WORD usB = 0;
    WORD usGray = 0;
    BYTE ucBackupDB = ScalerGetByte(P31_B0_D_DB_CTRL0);
    BYTE ucCountBank = 0;
    BYTE ucCountPage = 0;
    BYTE ucMaxPage = 0;
    BYTE ucOutputGammaType = 0;
    BYTE ucGammaBankNum = 0;
    BYTE *pucGammaBankAddr = _NULL_POINTER;
#if(_UNIFORMITY_SUPPORT == _ON)
    BYTE ucUniformityTypeIndex = 0;
    BYTE ucUniformityModeIndex = 0;
    BYTE ucGainTableBank = 0;
    WORD usGainTableAddr = 0;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    BYTE ucUniformityLevel0Enable = 0;
    BYTE ucOffsetTableBank = 0;
    BYTE ucOffsetTableStartBank = 0;
    WORD usOffsetTableAddr = 0;
    WORD usDecayTableAddr = 0;
#endif
#endif
    ScalerSetByte(P31_B0_D_DB_CTRL0, 0x00);

    EX1 = 0;

    ucCalibrationStep = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_STEP];

    SET_ON_LINE_CALIBRATION_STATUS(_CALIBRATION_ON);

    if(UserCommonDdcciDispCalibInitialCheck() == _SUCCESS)
    {
//****************************************************************************************//
//                               MEASURE PROCESS                                          //
//****************************************************************************************//
        /////////////////////////////////////////////////////////////////
        /////////////////////TOOL GET FW DEFINE//////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_GET_DEFINE)
        {
            UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_START);
            UserInterfaceAdjustBeforeDisplayCalibration(_OGC_CAL);
            ScalerMcuDdcciReleaseScl();

            return;
        }
        /////////////////////////////////////////////////////////////////
        /////////////////////TOOL GET FW INFO////////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_GET_FW_INFO)
        {
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_FW_VERSION)
            {
                UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_GET_VERSION);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_PANEL_LV_INFO)
            {
                UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_GET_NOTM_INFO);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_UNIFORMITY_FW_VERSION)
            {
                UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_GET_UNI_VERSION);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FW_INFO] == _DDCCI_DISP_CALIB_GET_FW_SUPPORT)
            {
                UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_GET_FW_SUPPORT);
            }
            ScalerMcuDdcciReleaseScl();
            return;
        }
        /////////////////////////////////////////////////////////////////
        /////////////////////END            /////////////////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_END)
        {
            pData[1] = 1;
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_OGC_CALIBRATION_FINISH_ADDRESS, 1, &pData[1]);
            SET_ON_LINE_CALIBRATION_STATUS(_CALIBRATION_OFF);
            UserInterfaceAdjustAfterDisplayCalibration(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_END_TYPE]);
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE START/////////////////
        //////////////DISPLAY CALIBRATION: MEASURE RED///////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_RED)
        {
            ucFlag = UserCommonDdcciDispCalibOGCStart();

            UserCommonDdcciDispCalibCalibPatternEnable(_ENABLE);
            UserCommonDdcciDispCalibShowCalibPattern(_PATTERN_TOP, 0, 0);

            g_usCTGainSavePos = 0;
            g_usColorMatrixSavePos = 0;
            if(g_ucBacklightFlag == _NORMAL_BACKLIGHT_CAL)
            {
                ucOutputGammaType = (_OGC_TOTAL_GAMMA * _OGC_SUPPORT);

                ucGammaBankNum = UserCommonAdjustOGCBank(ucOutputGammaType, _OGC_MAX_BACKLIGHT_TYPE);
                pucGammaBankAddr = UserCommonAdjustOGCAddr(ucOutputGammaType, _OGC_MAX_BACKLIGHT_TYPE);
                for(ucCountBank = _OGC_FLASH_BANK; ucCountBank <= ucGammaBankNum; ucCountBank++)
                {
                    if(ucCountBank < ucGammaBankNum)
                    {
                        ucMaxPage = 15;
                    }
                    else
                    {
                        ucMaxPage = ((WORD)pucGammaBankAddr + _OGC_GAMMA_TABLE_SIZE) / _FLASH_PAGE_SIZE;
                    }

                    for(ucCountPage = 0; ucCountPage <= ucMaxPage; ucCountPage++)
                    {
                        ucFlag &= UserCommonFlashErasePage(ucCountBank, ucCountPage);
                    }
                }
            }
#if(_FREESYNC_II_SUPPORT == _ON)
            ucFlag &= UserCommonFlashErasePage(_FREESYNC_II_FLASH_BANK, _FREESYNC_II_FLASH_PAGE);
            ucFlag &= UserCommonFlashErasePage(_FREESYNC_II_FLASH_BANK, _FREESYNC_II_FLASH_PAGE + 1);
#endif
        }
        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE BLACK/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_BLACK)
        {
            UserCommonDdcciDispCalibShowCalibPattern(0, 0, 0);
        }
        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE BLUE//////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_BLUE)
        {
            UserCommonDdcciDispCalibShowCalibPattern(0, 0, _PATTERN_TOP);
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE GREEN/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GREEN)
        {
            UserCommonDdcciDispCalibShowCalibPattern(0, _PATTERN_TOP, 0);
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE WHITE/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_WHITE)
        {
            UserCommonDdcciDispCalibShowCalibPattern(_PATTERN_TOP, _PATTERN_TOP, _PATTERN_TOP);
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE GRAY1~7///////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1TO7)
        {
            usGray = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_GRAY_HIGH] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_GRAY_LOW]);

            UserCommonDdcciDispCalibShowCalibPattern(usGray, usGray, usGray);
        }

        /////////////////////////////////////////////////////////////////
        ////////////DISPLAY CALIBRATION: MEASURE GRAY1 / GRAY2///////////
        /////////////////////Save RGB CT gains///////////////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1)
        {
            if(g_usCTGainSavePos == 0)
            {
                UserCommonDdcciDispCalibShowCalibPattern(tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                         tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                         tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);
            }

            /****************** Save RGB Gain to Flash******************/
            /* CT/Gamma   Gamma1     Gamma2    Gamma3   Gamma4   Gamma5*/
            /*    CT1     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT2     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT3     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT4     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT5     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    User    R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /************************************************************/

#if(_OGC_SUPPORT == _ON)
            if(g_ucBacklightFlag == _NORMAL_BACKLIGHT_CAL)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_ADDRESS + g_usCTGainSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
                g_usCTGainSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
            }
#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            else
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_MAX_BRI_ADDRESS + g_usCTGainSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
                g_usCTGainSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
            }
#endif
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY2)
        {
            UserCommonDdcciDispCalibShowCalibPattern(tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                     tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                     tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);

            if(g_ucBacklightFlag == _NORMAL_BACKLIGHT_CAL)
            {
                UserCommonDdcciDispCalibSaveHeader();
            }
        }

        /////////////////////////////////////////////////////////////////
        ////////////DISPLAY CALIBRATION: MEASURE GRAY3 ~ GRAY20//////////
        //////////////////////////SAVE LUT///////////////////////////////
        /////////////////////////////////////////////////////////////////
        else if((ucCalibrationStep >= _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY3) && (ucCalibrationStep <= _DDCCI_DISP_CALIB_OGC_MEASURE_LAST_GRAY))
        {
            if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_LENGTH] == 2) && (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_ID] == 0xFF))
            {
                UserCommonDdcciDispCalibShowCalibPattern(tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                         tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                         tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);
            }
            else
            {
                UserCommonDdcciDispCalibSaveLUT((g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F));
            }
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE END///////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_END)
        {
            ucFlag = UserCommonDdcciDispCalibCheckSum();

            UserCommonDdcciDispCalibShowGamma();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_CHK_COLORMATRIX)
        {
            ucFlag = UserCommonDdcciDispCalibMatrixCheckSum(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_TYPE]);

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
            g_ucIGLUTSavePos = 0;
            g_usCTGainSavePos = 0;
#endif
        }
#if(_HDR10_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_IGLUT)
        {
            if(g_ucIGLUTSavePos > 195)
            {
                g_ucIGLUTSavePos = 0;
            }

            UserCommonFlashWrite(_OGC_FLASH_BANK, tHDR10IGAMMA_INDEX[g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX]] + g_ucIGLUTSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START]);
            g_ucIGLUTSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_HDR_MODE)
        {
            // Set Input Gamma
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
            ScalerColorPCMInputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OGC_HDR10_IG_1200_NOR_ADDRESS + (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_SET_HDR_IG_INDEX] * _OGC_HDR10_IG_TABLE_SIZE), _OGC_FLASH_BANK);
            ScalerColorSRGBEnable(_FUNCTION_OFF);

            // Set Output Gamma
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);

            ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_HDR10_GAMMA10_ADDRESS, _OGC_FLASH_BANK);

            // Set Color Matrix
            ScalerColorPCMSRGBAdjust(_SRGB_1_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_HDR10_SRGB_MATRIX_ADDRESS + (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_SET_HDR_COLOR_MATRIX] * _OCC_COLORMATRIX_TABLE_SIZE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);

            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            ScalerColorSRGBEnable(_FUNCTION_ON);
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);
            ScalerColorSpaceConvertIDomainEnable(_OFF);
            ScalerColorSpaceConvertDDomainEnable(_OFF);

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif

#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#elif(_IAPS_SUPPORT == _ON)
#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_YPEAKING_SUPPORT == _ON)
            ScalerColorYpeaking(_OFF);
#endif
        }
#endif
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_BACKLIGHT)
        {
#if(_FREESYNC_II_GLOBAL_BACKLIGHT_SUPPORT == _OFF)
            UserInterfaceAdjustBacklight(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_BACKLIGHT_INDEX]);
#else
            UserInterfaceAdjustBacklight(((DWORD)g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_BACKLIGHT_INDEX] * (255 - _PANEL_FREESYNC_II_MIN_BACKLIGHT)) / 255 + _PANEL_FREESYNC_II_MIN_BACKLIGHT);
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_EDID_INFO)
        {
            UserCommonDdcciDispCalibSaveEDIDInfo();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_NOTM_DCR_THD)
        {
            UserCommonDdcciDispCalibSaveNoToneMappingDCRTHD();
        }
#if(_HDR10_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_HDR10_NOTM_BOUNG)
        {
            UserCommonDdcciDispCalibSaveHDR10BoundInfo();
        }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_FREESYNC_II_MEASURE_WHITE)
        {
            UserCommonDdcciDispCalibShowWhite(_FREESYNC_II_WHITE);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_FREESYNC_II_IGLUT)
        {
            if(g_ucIGLUTSavePos > 195)
            {
                g_ucIGLUTSavePos = 0;
            }

            UserCommonFlashWrite(_FREESYNC_II_FLASH_BANK, tFREESYNC2IGAMMA_INDEX[g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FREESYNC_II_IGLUT_INDEX] & 0x0F] + g_ucIGLUTSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FREESYNC_II_IGLUT_START]);
            g_ucIGLUTSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_PANEL_NATIVE_MATRIX)
        {
            UserCommonFlashWrite(_FREESYNC_II_FLASH_BANK, _FREESYNC_II_PANEL_NATIVE_MATRIX_ADDRESS, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FREESYNC_II_MATRIX_START]);
        }
#endif
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_LD_COMMAND)
        {
            if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX] >> 4) == _DIMMING_COMMAND_SAVE_IG)
            {
#if(_OGC_SUPPORT == _ON)
                if(g_ucIGLUTSavePos > 195)
                {
                    g_ucIGLUTSavePos = 0;
                }

                UserCommonFlashWrite(_OGC_FLASH_BANK, tDIMMINGIGAMMA_INDEX[g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX] & 0x0F] + g_ucIGLUTSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START]);
                g_ucIGLUTSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
#endif
            }
            else if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX] >> 4) == _DIMMING_COMMAND_SAVE_GAIN)
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_OGC_RGB_GAIN_ADDRESS + g_usCTGainSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START]);
                g_usCTGainSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
            }
#if(_OGC_SUPPORT == _ON)
            else if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX] >> 4) == _DIMMING_COMMAND_SET_GAMMMA)
            {
                ucGammaIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START] >> 4) & 0x0F;
                ucColorTempIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START] & 0x0F;

                // Set PCM Input Gamma
                ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);

                ScalerColorPCMInputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _DIMMING_OGC_GAMMA1_ADDRESS + (ucGammaIndex * _OGC_HDR10_IG_TABLE_SIZE), _OGC_FLASH_BANK);

                ScalerColorSRGBEnable(_FUNCTION_OFF);
                // Set PCM Output Gamma
                ScalerColorOutputGammaEnable(_FUNCTION_OFF);


                ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _DIMMING_OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);

                // Set PCM Color Matrix

                ScalerColorPCMSRGBAdjust(_SRGB_1_BIT_SHIFT_LEFT, tSRGBHalf, GET_CURRENT_BANK_NUMBER(), 18);

                ScalerColorOutputGammaEnable(_FUNCTION_ON);
                ScalerColorSRGBEnable(_FUNCTION_ON);
                ScalerColorPCMInputGammaEnable(_FUNCTION_ON);


                ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusBriTemp);

                if(ucColorTempIndex != 0x0F)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _DIMMING_OGC_RGB_GAIN_ADDRESS), 6, pData);
                }
                else // Native
                {
                    pData[0] = 0x08;
                    pData[1] = 0x00;
                    pData[2] = 0x08;
                    pData[3] = 0x00;
                    pData[4] = 0x08;
                    pData[5] = 0x00;
                }
                ScalerColorContrastAdjust(_CONTRAST_COEF_A, (WORD *)pData);
                ScalerColorContrastEnable(_FUNCTION_ON);
            }
#endif
        }
#endif
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_LD_BOOST_COMMAND)
        {
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_BOOST_INDEX] == _DDCCI_DISP_CALIB_BOOST_ON)
            {
                UserCommonDdcciDispCalibShowWhite(_LD_BOOST_WHITE);
                UserInterfaceAdjustLDBoostCalibration(_ON);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_BOOST_INDEX] == _DDCCI_DISP_CALIB_BOOST_OFF)
            {
                UserInterfaceAdjustLDBoostCalibration(_OFF);
            }
        }
#endif

        /////////////////////////////////////////////////////////////////
        ////////////////////////OCC PROCESS//////////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OCC_SUPPORT == _ON)
        if(((g_ucCalibrationType >> _OCC_CAL_TYPE) & 0x01) == _TRUE)
        {
            UserCommonDdcciDispCalibOCCProcess(ucCalibrationStep);
        }
#endif


//****************************************************************************************//
//                               VERIFICATION PROCESS                                     //
//****************************************************************************************//
        /////////////////////////////////////////////////////////////////
        //////////////////////////VERIFICATION///////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_VERIFICATION)
        {
            usR = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED + 1]);
            usG = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN + 1]);
            usB = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE + 1]);

            ScalerDDomainPatternGenAdjustColor10bit(usR, usG, usB);
            ScalerDDomainPatternGenEnable(_ENABLE);
            ScalerDDomainBackgroundEnable(_DISABLE);
        }

        /////////////////////////////////////////////////////////////////
        ///////////////////////SET GAMMA PROCESS/////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OGC_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_GAMMA)
        {
            ucGammaIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] >> 4) & 0x0F;
            ucColorTempIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] & 0x0F;

            // Set Output Gamma
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);
#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            ucGammaBankNum = UserCommonAdjustOGCBank(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
#else
            ucGammaBankNum = UserCommonAdjustOGCBank(ucGammaIndex, _OGC_NORMAL_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(ucGammaIndex, _OGC_NORMAL_TYPE);
#endif


            ScalerColorOutputGammaAdjust(pucGammaBankAddr, ucGammaBankNum);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);

            ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusBriTemp);
            ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_B, pusBriTemp);

            if(ucColorTempIndex != 0x0F)
            {
#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
                UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_MAX_BRI_ADDRESS), 6, pData);
#else
                UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pData);
#endif
            }
            else // Native
            {
                pData[0] = 0x08;
                pData[1] = 0x00;
                pData[2] = 0x08;
                pData[3] = 0x00;
                pData[4] = 0x08;
                pData[5] = 0x00;
            }
            ScalerColorContrastAdjust(_CONTRAST_COEF_A, (WORD *)pData);
            ScalerColorContrastAdjust(_CONTRAST_COEF_B, (WORD *)pData);
            ScalerColorContrastEnable(_FUNCTION_ON);

#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

            ScalerColorSRGBEnable(_FUNCTION_OFF);
#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
        }
#endif  // End of #if(_OGC_SUPPORT == _ON)

        /////////////////////////////////////////////////////////////////
        ////////////////////////SET PCM PROCESS//////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OCC_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_PCM)
        {
            // Set PCM Input Gamma
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
            ScalerColorPCMInputGammaLoadTable(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN]);

            ScalerColorSRGBEnable(_FUNCTION_OFF);

            // Set PCM Output Gamma
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);

#if(_TWO_BRI_CALIBRATION_TYPE != _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);

            // Set PCM Color Matrix
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_EBU_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DCIP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SMPTEC_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else // if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
#else
            ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_MAX_BRI_ADDRESS, _OGC_FLASH_BANK);

            // Set PCM Color Matrix
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_EBU_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DCIP3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SMPTEC_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else // if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
#endif
            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            ScalerColorSRGBEnable(_FUNCTION_ON);
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);
            ScalerColorSpaceConvertIDomainEnable(_OFF);
            ScalerColorSpaceConvertDDomainEnable(_OFF);

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif

#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#elif(_IAPS_SUPPORT == _ON)
#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_YPEAKING_SUPPORT == _ON)
            ScalerColorYpeaking(_OFF);
#endif
        }
#endif  // End of #if(_OCC_SUPPORT == _ON)

        /////////////////////////////////////////////////////////////////
        ///////////////////////SET DICOM PROCESS/////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OGC_DICOM_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_DICOM)
        {
            // Set DICOM
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);
            ScalerColorOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OGC_DICOM_ADDRESS, _OGC_FLASH_BANK);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);

#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif
            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);

            ScalerColorSRGBEnable(_FUNCTION_OFF);


#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
        }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)

        /////////////////////////////////////////////////////////////////
        ///////////////////////SET FREESYNC II PROCESS///////////////////
        /////////////////////////////////////////////////////////////////
#if(_FREESYNC_II_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_FREESYNC_II)
        {
            ucGammaIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] & 0x0F;

            // Set Freesync II Input Gamma
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
            ScalerColorPCMInputGammaAdjust(g_pucDISP_FREESYNC_II_CALIBRATION_FLASH + tFREESYNC2IGAMMA_INDEX[ucGammaIndex], _FREESYNC_II_FLASH_BANK);
            ScalerColorSRGBEnable(_FUNCTION_OFF);

            // Set Freesync II Output Gamma
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);

            ScalerColorPCMOutputGammaAdjust(g_pucDISP_FREESYNC_II_CALIBRATION_FLASH + _FREESYNC_II_OCC_GAMMA10_ADDRESS, _FREESYNC_II_FLASH_BANK);

            // Set Color Matrix
            ScalerColorPCMSRGBAdjust(_SRGB_1_BIT_SHIFT_LEFT, g_pucDISP_FREESYNC_II_CALIBRATION_FLASH + _FREESYNC_II_PANEL_NATIVE_MATRIX_ADDRESS, _FREESYNC_II_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);

            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            ScalerColorSRGBEnable(_FUNCTION_ON);
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
        }
#endif  // End of #if(_OGC_SUPPORT == _ON)

        /////////////////////////////////////////////////////////////////
        ///////////////////////VERIFICATION END//////////////////////////
        /////////////////////////////////////////////////////////////////
        else if((ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_VERIFY_END) || (ucCalibrationStep == _DDCCI_DISP_CALIB_OCC_VERIFY_END))
        {
            ScalerDDomainPatternGenEnable(_DISABLE);
            ScalerDDomainPatternGenAdjustColor10bit(0, 0, 0);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_MEASURE_BG)
        {
            ScalerDDomainBackgroundEnable(_ENABLE);
            usR = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED + 1]);
            usG = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN + 1]);
            usB = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE + 1]);

            ScalerDDomainBackgroundSetColor10bit(usR, usG, usB);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_BG_OFF)
        {
            ScalerDDomainBackgroundEnable(_DISABLE);
        }

#if(_UNIFORMITY_SUPPORT == _ON)

        /////////////////////////////////////////////////////////////////
        ///////////////////////SET UNIFORMITY LUT////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_OGC_HEADER)
        {
            UserCommonDdcciDispCalibReplyOGCHeader();
            ScalerMcuDdcciReleaseScl();

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_LVRATIO)
        {
            UserCommonDdcciDispCalibReplyOGCOCCLvRatio();
            ScalerMcuDdcciReleaseScl();

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_ERASE_FLASH)
        {
            ucUniformityTypeIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x0F);
            ucGainTableBank = UserCommonAdjustPanelUniformityGainBank(ucUniformityTypeIndex);
            usGainTableAddr = UserCommonAdjustPanelUniformityGainAddr(ucUniformityTypeIndex);
            for(ucCountBank = _UNIFORMITY_FLASH_BANK0; ucCountBank <= ucGainTableBank; ucCountBank++)
            {
                if(ucCountBank < ucGainTableBank)
                {
                    ucMaxPage = 15;
                }
                else
                {
                    ucMaxPage = (DWORD)((usGainTableAddr + _PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonAdjustGetUniformityType(ucUniformityTypeIndex)) / _FLASH_PAGE_SIZE); // ex: Total size = 4096bytes(4095 LUT + 1 checksum), only need Page0
                }

                for(ucCountPage = 0; ucCountPage <= ucMaxPage; ucCountPage++)
                {
                    ucFlag &= UserCommonFlashErasePage(ucCountBank, ucCountPage);
                }
            }
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
            ucOffsetTableBank = UserCommonAdjustPanelUniformityOffsetBank(ucUniformityTypeIndex);
            usOffsetTableAddr = UserCommonAdjustPanelUniformityOffsetAddr(ucUniformityTypeIndex);
            ucOffsetTableStartBank = UserCommonAdjustPanelUniformityOffsetBank(0);
            for(ucCountBank = ucOffsetTableStartBank; ucCountBank <= ucOffsetTableBank; ucCountBank++)
            {
                if(ucCountBank < ucOffsetTableBank)
                {
                    ucMaxPage = 15;
                }
                else
                {
                    ucMaxPage = (DWORD)((usOffsetTableAddr + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + _PANEL_UNIFORMITY_DECAY_LUT_SIZE) / _FLASH_PAGE_SIZE); // ex: Total size = 4096bytes(4095 LUT + 1 checksum), only need Page0
                }

                for(ucCountPage = 0; ucCountPage <= ucMaxPage; ucCountPage++)
                {
                    ucFlag &= UserCommonFlashErasePage(ucCountBank, ucCountPage);
                }
            }
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_SET_GAMMA)
        {
            ucGammaIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] & 0x0F;

            // Set Output Gamma
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);

            ucGammaBankNum = UserCommonAdjustOGCBank(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);

            ScalerColorOutputGammaAdjust(pucGammaBankAddr, ucGammaBankNum);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);

#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

            ScalerColorSRGBEnable(_FUNCTION_OFF);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_PCM_MATRIX)
        {
            switch(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x07)
            {
                case 0:
                    UserCommonDdcciDispCalibReplyOCCMatrix(_PCM_SRGB);
                    break;

                case 1:
                    UserCommonDdcciDispCalibReplyOCCMatrix(_PCM_ADOBE_RGB);
                    break;

                case 2:
                    UserCommonDdcciDispCalibReplyOCCMatrix(_PCM_DCI_P3);
                    break;

                case 3:
                    UserCommonDdcciDispCalibReplyOCCMatrix(_PCM_USER_DEFINE);
                    break;

                case 4:
                    UserCommonDdcciDispCalibReplyOCCMatrix(_PCM_USER_DEFINE_2);
                    break;

                case 5:
                    UserCommonDdcciDispCalibReplyOCCMatrix(_PCM_DISPLAY_P3);
                    break;

                default:
                    break;
            }
            // UserCommonDdcciDispCalibReplyOCCMatrix(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
            ScalerMcuDdcciReleaseScl();

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_WRITE_START)
        {
            g_usUniformityLUTSavePos = 0;
            g_ucUniformityLUTStartPosIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x0F;
            g_ucUniformityLUTSaveBank = UserCommonAdjustPanelUniformityGainBank(g_ucUniformityLUTStartPosIndex);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_WRITE)
        {
            usGainTableAddr = UserCommonAdjustPanelUniformityGainAddr(g_ucUniformityLUTStartPosIndex);
            UserCommonFlashWrite(g_ucUniformityLUTSaveBank, usGainTableAddr + g_usUniformityLUTSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
            g_usUniformityLUTSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_WRITE_END)
        {
            g_ucUniformityChecksumType = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

            g_ucCalibrationType = 0;
            ucFlag = UserCommonDdcciDispCalibCheckSum();
            g_usUniformityLUTSavePos = 0;// level0
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_VERIFY_START)
        {
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] == _ON)
            {
                ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
                ucUniformityTypeIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX + 1] & 0xF0) >> 4;
                ucUniformityModeIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX + 1] & 0x0F;
                ucGainTableBank = UserCommonAdjustPanelUniformityGainBank(ucUniformityTypeIndex);
                usGainTableAddr = UserCommonAdjustPanelUniformityGainAddr(ucUniformityTypeIndex);

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                ucUniformityLevel0Enable = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX + 2] & _BIT0;
                ucOffsetTableBank = UserCommonAdjustPanelUniformityOffsetBank(ucUniformityTypeIndex);
                usOffsetTableAddr = UserCommonAdjustPanelUniformityOffsetAddr(ucUniformityTypeIndex);
                usDecayTableAddr = UserCommonAdjustPanelUniformityDecayAddr(ucUniformityTypeIndex);
                if(ucUniformityLevel0Enable == _ON)
                {
                    ScalerColorPanelUniformityOffsetAdjust(g_pucDISP_CALIBRATION_FLASH + usOffsetTableAddr, _PANEL_UNIFORMITY_OFFSET_LUT_SIZE, ucOffsetTableBank);
                    ScalerColorPanelUniformityDecayAdjust(g_pucDISP_CALIBRATION_FLASH + usDecayTableAddr, _PANEL_UNIFORMITY_DECAY_LUT_SIZE, ucOffsetTableBank, ucUniformityModeIndex, UserCommonAdjustGetUniformityType(ucUniformityTypeIndex));
                }
                ScalerColorPanelUniformityOffsetEnable(ucUniformityLevel0Enable);
#endif
                ScalerColorPanelUniformityAdjust(g_pucDISP_CALIBRATION_FLASH + usGainTableAddr, _PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonAdjustGetUniformityType(ucUniformityTypeIndex), ucGainTableBank, ucUniformityModeIndex, UserCommonAdjustGetUniformityType(ucUniformityTypeIndex));
                ScalerColorPanelUniformityEnable(_FUNCTION_ON);
            }
            else
            {
                ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                ScalerColorPanelUniformityOffsetEnable(_FUNCTION_OFF);
#endif
            }
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_VERIFY_END)
        {
            // Turn off all of Ddoamin function
            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
            ScalerColorPanelUniformityOffsetEnable(_FUNCTION_OFF);
#endif

#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);
            ScalerColorSRGBEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);
            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorSpaceConvertIDomainEnable(_OFF);
            ScalerColorSpaceConvertDDomainEnable(_OFF);
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#elif(_IAPS_SUPPORT == _ON)
#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_DEFINE)
        {
            // UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_UNIFORMITY);
            UserInterfaceAdjustBeforeDisplayCalibration(_UNIFORMITY_CAL);
            UserCommonDdcciDispCalibReplyUniformityDefine();
            ScalerMcuDdcciReleaseScl();
            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_CCT_GAIN)
        {
            UserCommonDdcciDispCalibReplyCCTGain();
            ScalerMcuDdcciReleaseScl();

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_FM_DATA)
        {
            UserCommonDdcciDispCalibReplyFastModeData();
            ScalerMcuDdcciReleaseScl();

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_LEVEL_MODE)
        {
            UserCommonDdcciDispCalibReplyUniformityLevelMode();
            ScalerMcuDdcciReleaseScl();

            return;
        }

#if(_OCC_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_SET_PCM)
        {
            // Set PCM Input Gamma
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
            if ((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE) || (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2))
            {
                ScalerColorPCMInputGammaLoadTable(_PCM_ADOBE_RGB);
            }
            else
            {
                ScalerColorPCMInputGammaLoadTable(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN]);
            }
            ScalerColorSRGBEnable(_FUNCTION_OFF);

            // Set PCM Output Gamma
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);

#if(_TWO_BRI_CALIBRATION_TYPE != _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
            ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);

            // Set PCM Color Matrix
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_EBU_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DCIP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SMPTEC_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else // if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
#else
            ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_MAX_BRI_ADDRESS, _OGC_FLASH_BANK);

            // Set PCM Color Matrix
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_EBU_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DCIP3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SMPTEC_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else // if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
#endif
            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            ScalerColorSRGBEnable(_FUNCTION_ON);
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);

            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);

#if(_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
        }
#endif  // End of #if(_OCC_SUPPORT == _ON)

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_OFFSET)
        {
            ucOffsetTableBank = UserCommonAdjustPanelUniformityOffsetBank(g_ucUniformityLUTStartPosIndex);
            usOffsetTableAddr = UserCommonAdjustPanelUniformityOffsetAddr(g_ucUniformityLUTStartPosIndex);
            UserCommonFlashWrite(ucOffsetTableBank, usOffsetTableAddr + g_usUniformityLUTSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
            g_usUniformityLUTSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_OFFSET_END)
        {
            g_ucUniformityChecksumType = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

            g_ucCalibrationType = 0;
            ucFlag = UserCommonDdcciDispCalibCheckSum();
            g_usUniformityLUTSavePos = 0;// level0
        }

        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_DECAY)
        {
            ucOffsetTableBank = UserCommonAdjustPanelUniformityOffsetBank(g_ucUniformityLUTStartPosIndex);
            usDecayTableAddr = UserCommonAdjustPanelUniformityDecayAddr(g_ucUniformityLUTStartPosIndex);
            UserCommonFlashWrite(ucOffsetTableBank, usDecayTableAddr + g_usUniformityLUTSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
            g_usUniformityLUTSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_DECAY_END)
        {
            g_ucUniformityChecksumType = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

            g_ucCalibrationType = 0;
            ucFlag = UserCommonDdcciDispCalibCheckSum();
        }
#endif  // End of #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#endif  // End of #if(_UNIFORMITY_SUPPORT== _ON)

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_START)
        {
            ScalerColorSpaceConvertIDomainEnable(_OFF);
            ScalerColorSpaceConvertDDomainEnable(_OFF);
            UserInterfaceAdjustBeforeDimmingCalibration();
            ScalerMcuDdcciReleaseScl();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_END)
        {
            UserInterfaceAdjustAfterDimmingCalibration();
            ScalerMcuDdcciReleaseScl();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_CHECKFW)
        {
            UserCommonDdcciDispCalibReplyDimmingDefine();
            ScalerMcuDdcciReleaseScl();
            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_SETPWM)
        {
            UserCommonDdcciDispCalibSetPWMValue();
            ScalerMcuDdcciReleaseScl();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_SHOW_WHITE)
        {
            BYTE ucTempPatternType = g_ucPatternType;
            g_ucPatternType = _PG_PATTERN;
            UserCommonDdcciDispCalibCalibPatternEnable(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_DATA_START]);
            UserCommonDdcciDispCalibShowCalibPattern(_PATTERN_TOP, _PATTERN_TOP, _PATTERN_TOP);
            g_ucPatternType = ucTempPatternType;
            ScalerMcuDdcciReleaseScl();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_DIMMING_SHOW_BLACK)
        {
            BYTE ucTempPatternType = g_ucPatternType;
            g_ucPatternType = _PG_PATTERN;
            UserCommonDdcciDispCalibCalibPatternEnable(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_DATA_START]);
            UserCommonDdcciDispCalibShowCalibPattern(0, 0, 0);
            g_ucPatternType = ucTempPatternType;
            ScalerMcuDdcciReleaseScl();
        }
#endif
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_PANEL_COLOR_MATCHING_DATA)
        {
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLOR_MATCHING_INDEX] == _DDCCI_DISP_CALIB_COLOR_MATCHING_READ)
            {
                UserCommonDdcciDispCalibAccessPanelColorMatchingData(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLOR_MATCHING_INDEX]);
                ScalerMcuDdcciReleaseScl();
                return;
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLOR_MATCHING_INDEX] == _DDCCI_DISP_CALIB_COLOR_MATCHING_WRITE)
            {
                UserCommonDdcciDispCalibAccessPanelColorMatchingData(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLOR_MATCHING_INDEX]);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLOR_MATCHING_INDEX] == _DDCCI_DISP_CALIB_COLOR_MATCHING_ERASE)
            {
                for(ucCountPage = 0; ucCountPage <= 15; ucCountPage++)
                {
                    ucFlag &= UserCommonFlashErasePage(_OGC_FLASH_BANK, ucCountPage);
                }
            }
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_PANEL_OGCOCC_LVRATIO)
        {
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGCOCC_LV_RARIO_ADDRESS, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_LVRATIO_INDEX]);
        }
//****************************************************************************************//
//                               FINAL PROCESS                                            //
//****************************************************************************************//
        /////////////////////////////////////////////////////////////////
        ///////////////////////REPLY RESULTS/////////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_VERIFICATION)
        {
            UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_PASS);
        }
        else
        {
            if(ucFlag == 1)
            {
                UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_PASS);
            }
            else
            {
                if((ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_BLACK) || (ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GREEN))
                {
                    UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_ERASE_ERROR);
                }
                else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_RED)
                {
                    UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_FW_ERROR);
                }
                else
                {
                    UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_CRC_ERROR);
                }
            }
        }
    }
    else    // else of if(UserCommonDdcciDispCalibInitialCheck() == _SUCCESS)
    {
        UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_FAIL);
    }
    ScalerSetByte(P31_B0_D_DB_CTRL0, ucBackupDB);
    ScalerMcuDdcciReleaseScl();
}

//--------------------------------------------------
// Description  : OGC Measure Start Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonDdcciDispCalibOGCStart(void)
{
    BYTE ucCnt = 0;
    BYTE ucFlag = 1;

#if(_HDR10_SUPPORT == _ON)
    g_ucIGLUTSavePos = 0;
#endif

    // Get Counter Start
#if(_OGC_SUPPORT == _ON)
    for(ucCnt = 0; ucCnt < _OGC_TOTAL_GAMMA; ucCnt++)
    {
        g_ppusGammaCount[ucCnt][0] = 2052;
        g_ppusGammaCount[ucCnt][1] = 2052;
        g_ppusGammaCount[ucCnt][2] = 2052;
    }
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_SUPPORT == _ON)
    g_ppusGammaCount[ucCnt][0] = 2200;
    g_ppusGammaCount[ucCnt][1] = 2200;
    g_ppusGammaCount[ucCnt][2] = 2200;
    ucCnt++;
#endif  // End of #if(_OCC_SUPPORT == _ON)

#if(_OGC_DICOM_SUPPORT == _ON)
    g_ppusGammaCount[ucCnt][0] = 2052;
    g_ppusGammaCount[ucCnt][1] = 2052;
    g_ppusGammaCount[ucCnt][2] = 2052;
    ucCnt++;
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
    g_ppusGammaCount[ucCnt][0] = 2200;
    g_ppusGammaCount[ucCnt][1] = 2200;
    g_ppusGammaCount[ucCnt][2] = 2200;
    ucCnt++;
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
    g_ppusGammaCount[ucCnt][0] = 2200;
    g_ppusGammaCount[ucCnt][1] = 2200;
    g_ppusGammaCount[ucCnt][2] = 2200;
    ucCnt++;
#endif  // End of #if(_FREESYNC_II_SUPPORT == _ON)

    // Get Counter End
    g_ucCalibrationType = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

#if(_TWO_BRI_CALIBRATION_TYPE != _TWO_BRI_CALIBRATION_NONE)
    g_ucBacklightFlag = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_HDR_FLAG];
#endif

#if(_OGC_SUPPORT == _OFF)
    if(((g_ucCalibrationType >> _OGC_CAL_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OGC_SUPPORT == _OFF)

#if(_OCC_SUPPORT == _OFF)
    if(((g_ucCalibrationType >> _OCC_CAL_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OCC_SUPPORT == _OFF)

#if(_OGC_DICOM_SUPPORT == _OFF)
    if(((g_ucCalibrationType >> _DICOM_CAL_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _OFF)

    if(((g_ucCalibrationType >> (_DICOM_CAL_TYPE + 1)) & 0x07) != _OGC_TOTAL_GAMMA)
    {
        ucFlag = 0;
    }

    g_ucPatternType = (g_ucCalibrationType & _BIT6) >> 6;
    g_ucCalibrationTypeII = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE_II] & _BIT0) >> 0;

#if(_OCC_SUPPORT == _ON)
    if(((g_ucCalibrationType >> _OCC_CAL_TYPE) & _BIT0) == _TRUE)
    {
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#if(_HDR10_SUPPORT == _ON)
        ScalerColorPCMInputGammaLoadTable(_PCM_HDR_2084);
#else
        ScalerColorPCMInputGammaLoadTable(_PCM_SRGB);
#endif
        ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, tSRGBByPass, GET_CURRENT_BANK_NUMBER(), 18);
        ScalerDDomainPatternGenAdjustColor10bit(tOCC_SRGB_TABLE[0], tOCC_SRGB_TABLE[1], tOCC_SRGB_TABLE[2]);
        ScalerDDomainPatternGenEnable(_ENABLE);
    }
    else
#endif  // End of #if(_OCC_SUPPORT == _ON)
    {

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif
    }

    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
    ScalerColorSRGBEnable(_FUNCTION_OFF);
    ScalerColorContrastEnable(_FUNCTION_OFF);
    ScalerColorBrightnessEnable(_FUNCTION_OFF);
    // ScalerColorSpaceConvert(_COLOR_SPACE_RGB, _DB_APPLY_NO_POLLING);
    ScalerColorSpaceConvertIDomainEnable(_OFF);
    ScalerColorSpaceConvertDDomainEnable(_OFF);

#if(_DCC_FUNCTION == _ON)
    ScalerColorDCCEnable(_FUNCTION_OFF);
#elif(_IAPS_SUPPORT == _ON)
#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)
    ScalerColorDCCEnable(_FUNCTION_OFF);
#endif
#endif

#if(_ICM_SUPPORT == _ON)
    ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_YPEAKING_SUPPORT == _ON)
    ScalerColorYpeaking(_OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
    ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#endif

    return ucFlag;
}

#if(_OCC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Display Calibration OCC Process
// Input Value  : Calibration Step
// Output Value : ucFlag
//--------------------------------------------------
BYTE UserCommonDdcciDispCalibOCCProcess(BYTE ucStep)
{
    BYTE ucFlag = 1;
    BYTE ucPatternEnd = (_OCC_LUT_MODE == _ON) ? _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB21 : _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB7;


    if((ucStep >= _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1) && (ucStep < ucPatternEnd))
    {
        ScalerDDomainPatternGenAdjustColor10bit(tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3],
                                                tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3 + 1],
                                                tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3 + 2]);
        // ScalerDDomainPatternGenEnable(_ENABLE);
    }
    else if(ucStep == ucPatternEnd)
    {
        if(g_ucBacklightFlag == _NORMAL_BACKLIGHT_CAL)
        {
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_SRGBMATRIX_ADDRESS + g_usColorMatrixSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_MATRIX]);
            g_usColorMatrixSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
        else
        {
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_SRGBMATRIX_MAX_BRI_ADDRESS + g_usColorMatrixSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_MATRIX]);
            g_usColorMatrixSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
#endif

#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
        if(g_ucBacklightFlag == _MAX_BACKLIGHT_CAL)
        {
            // Set PCM Color Matrix
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_EBU_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DCIP3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SMPTEC_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else // if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_MAX_BRI_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
        }
        else
#endif
        {
            // Set PCM Color Matrix
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_EBU_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DCIP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SMPTE_C)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SMPTEC_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_2)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE2_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_4)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE4_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_5)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE5_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE_6)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE6_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else // if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DISPLAY_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DISPLAYP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
        }

        ScalerColorSRGBEnable(_FUNCTION_ON);

        // Disable Display Pattern Gen. & set (0,0,0)
        ScalerDDomainPatternGenEnable(_DISABLE);
        ScalerDDomainPatternGenAdjustColor10bit(0, 0, 0);
    }
#if(_HDR10_SUPPORT == _ON)
    else if(ucStep == _DDCCI_DISP_CALIB_SAVE_HDR_MATRIX)
    {
        UserCommonFlashWrite(_OGC_FLASH_BANK, _OCC_HDR10_SRGB_MATRIX_ADDRESS, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_HDRMATRIX_START]);
    }
#endif
    return ucFlag;
}
#endif // End of #if(_OCC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Access Multi panel color matching data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibAccessPanelColorMatchingData(BYTE ucCommand)
{
    BYTE pucTemp[12] = {0};

    if(ucCommand == _DDCCI_DISP_CALIB_COLOR_MATCHING_READ)
    {
        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | _OCC_PANEL_COLOR_MAPPING_DATA_ADDRESS, 12, pucTemp);
        g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
        g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x0C;
        g_pucDdcciTxBuf[2] = pucTemp[0];// xp
        g_pucDdcciTxBuf[3] = pucTemp[1];
        g_pucDdcciTxBuf[4] = pucTemp[2];// yp
        g_pucDdcciTxBuf[5] = pucTemp[3];
        g_pucDdcciTxBuf[6] = pucTemp[4];// xc
        g_pucDdcciTxBuf[7] = pucTemp[5];
        g_pucDdcciTxBuf[8] = pucTemp[6];// yc
        g_pucDdcciTxBuf[9] = pucTemp[7];
        g_pucDdcciTxBuf[10] = pucTemp[8];// xp_target
        g_pucDdcciTxBuf[11] = pucTemp[9];
        g_pucDdcciTxBuf[12] = pucTemp[10];// yp_target
        g_pucDdcciTxBuf[13] = pucTemp[11];
        g_pucDdcciTxBuf[14] = UserCommonDdcciCalCheckSum();// CYShih, 8
        ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
        EX1 = 1;
    }
    else if(ucCommand == _DDCCI_DISP_CALIB_COLOR_MATCHING_WRITE)
    {
        memcpy(pucTemp, (g_pucDdcciRxBuf + 6), 12);
        UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) | _OCC_PANEL_COLOR_MAPPING_DATA_ADDRESS, 12, pucTemp);
    }
}
//--------------------------------------------------
// Description  : Check if the checksum from Tool is equal to DDCCI data
// Input Value  : None
// Output Value : _SUCCESS/_FAIL
//--------------------------------------------------
bit UserCommonDdcciDispCalibInitialCheck(void)
{
    BYTE ucSum = 0;
    BYTE ucChecksum = 0;
    BYTE ucLength = 0;
    BYTE ucI = 0;

    ucLength = g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F;

    for(ucI = 2; ucI < (ucLength + 1); ucI++)
    {
        ucSum += g_pucDdcciRxBuf[ucI];
    }

    ucChecksum = g_pucDdcciRxBuf[ucLength + 1];

    if(ucSum == ucChecksum)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Read or Write LUT Data from Flash
// Input Value  : bReadWrite: Read or Write
//                ucBank: Bank index
//                ucIndex: Gamma index
//                usAddr: address in ucBank
//                ucLength: the data length to load
//                pucData: data buffer to save the load data
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibFlashData(bit bReadWrite, BYTE ucBank, BYTE ucIndex, WORD usAddr, WORD usLength, BYTE *pucData)
{
#if(_FREESYNC_II_SUPPORT == _ON)
    if(ucIndex == _OCC_FREESYNC_II_POSITION)
    {
        ucBank = _FREESYNC_II_FLASH_BANK;
        usAddr += ((WORD)_FREESYNC_II_FLASH_PAGE << 12);
    }
    else
#endif
    {
#if(_OCC_SUPPORT == _ON)
#if(_OGC_SUPPORT == _ON)
        if(ucIndex >= _OCC_POSITION)
#endif
        {
            ucBank = _OGC_FLASH_BANK;
        }
#elif(_OGC_DICOM_SUPPORT == _ON)
        if(ucIndex == _DICOM_POSITION)
        {
            ucBank = _OGC_FLASH_BANK;
        }
#endif

        usAddr += ((WORD)_OGC_FLASH_PAGE << 12);
        ucIndex = ucIndex;
    }

    if(bReadWrite == _READ)
    {
        UserCommonFlashRead(ucBank, usAddr, usLength, pucData);
    }
    else
    {
        UserCommonFlashWrite(ucBank, usAddr, usLength, pucData);
    }
}

//--------------------------------------------------
// Description  : Save LUT Data from DDCCI Rx
// Input Value  : nAddress: address in DISP_CALIBRATION_FLASH;
//                nLength: Data Length
//                ucBuffer: pointer of databuffer
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibSaveLUT(BYTE ucTotalLength)
{
    BYTE ucLUTLength = 0;
    BYTE ucPointer = 5;
    BYTE ucGammaIndex = 0;
    BYTE ucRGB = 0;
    WORD usStartAddr = 0;
    WORD usLastLUT = 0;
    WORD usCurrLUT = 0;
    BYTE pucIntoLUT[128] = {0};
    BYTE ucJ = 0;
    WORD usInto = 0;
    bit bIsLastLUT = _FALSE;
    SWORD shRemain = 0;
    SWORD shCnt = 0;
    // int nNum = 0;
    BYTE ucCurPointer = 0;
    SWORD shWriteCnt = 0;
#if(_OCC_SUPPORT == _ON)
    bit bWriteDirectly = _FALSE;
    bit bOCCMode = _FALSE;
#endif
    BYTE ucGammaBankNum = 0;
    BYTE *pucGammaBankAddr = _NULL_POINTER;
    WORD usFlashSaveAddr = 0;
    WORD usFlashSaveLength = 0;

    // ucTotalLength - 1: exclude checksum
    while(ucPointer < (ucTotalLength - 1))
    {
        // LUT Length (exclude ID and Length Bytes)
        ucLUTLength = g_pucDdcciRxBuf[ucPointer] - 2;

        ucGammaIndex = (g_pucDdcciRxBuf[ucPointer + 1] >> 4) & 0x0F;
        ucRGB = g_pucDdcciRxBuf[ucPointer + 1] & 0x0F;
        ucPointer += 2;

#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
        if(g_ucBacklightFlag == _MAX_BACKLIGHT_CAL)
        {
            ucGammaBankNum = UserCommonAdjustOGCBank(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
        }
        else
#endif
        {
            ucGammaBankNum = UserCommonAdjustOGCBank(ucGammaIndex, _OGC_NORMAL_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(ucGammaIndex, _OGC_NORMAL_TYPE);
        }

#if(_OCC_SUPPORT == _ON)

        if(ucGammaIndex == _OCC_POSITION)
        {
            bOCCMode = _TRUE;
        }
        else
        {
            bOCCMode = _FALSE;
        }

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        if(ucGammaIndex == _DIMMING_POSITION)
        {
            bOCCMode = _TRUE;
        }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
        if(ucGammaIndex == _OCC_FREESYNC_II_POSITION)
        {
            bOCCMode = _TRUE;
        }
#endif

        if(ucGammaIndex == _OCC_POSITION)
        {
#if(((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_DICOM_HDR) && (_HDR10_SUPPORT == _ON)) || (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR))
            if(g_ucBacklightFlag == _MAX_BACKLIGHT_CAL)
            {
                usStartAddr = tGAMMA_INDEX[_OCC_HDR_POSITION] + (ucRGB) * 2200;
            }
            else
#endif
            {
                usStartAddr = tGAMMA_INDEX[_OCC_POSITION] + (ucRGB) * 2200;
            }
        }
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        else if(ucGammaIndex == _DIMMING_POSITION)
        {
            usStartAddr = tGAMMA_INDEX[_DIMMING_POSITION] + (ucRGB) * 2200;
        }
#endif
#if(_FREESYNC_II_SUPPORT == _ON)
        else if(ucGammaIndex == _OCC_FREESYNC_II_POSITION)
        {
            usStartAddr = tGAMMA_INDEX[_OCC_FREESYNC_II_POSITION] + (ucRGB) * 2200;
        }
#endif
#if(_OGC_DICOM_SUPPORT == _ON)
        else if(ucGammaIndex == _DICOM_POSITION)
        {
            usStartAddr = tGAMMA_INDEX[_DICOM_POSITION] + (ucRGB) * 2052;
        }
#endif
        else
#endif
        {
            usStartAddr = (WORD)pucGammaBankAddr + (ucRGB) * 2052;
        }

        bIsLastLUT = _FALSE;
#if(_OCC_SUPPORT == _ON)
        if((bOCCMode == _TRUE) && (g_ppusGammaCount[ucGammaIndex][ucRGB] == 2200))
        {
            bIsLastLUT = _TRUE;
        }
        else if((bOCCMode == _FALSE) && (g_ppusGammaCount[ucGammaIndex][ucRGB] == 2052))
        {
            bIsLastLUT = _TRUE;
        }
#else
        if(g_ppusGammaCount[ucGammaIndex][ucRGB] == 2052)
        {
            bIsLastLUT = _TRUE;
        }
#endif
        if(bIsLastLUT == _TRUE)
        {
            shRemain = (ucLUTLength - 2) * 4 + 4;
        }
        else
        {
#if(_OCC_SUPPORT == _ON)
            if((bOCCMode == _TRUE) && (g_ppusGammaCount[ucGammaIndex][ucRGB] <= 164))
            {
                shRemain = ucLUTLength;
            }
            else
#endif
            {
                shRemain = ucLUTLength * 4;
            }
        }
        ucCurPointer = ucPointer + ucLUTLength - 1;

        while(shRemain > 0)
        {
            if(shRemain > 128)
            {
                shCnt = (bIsLastLUT == _TRUE) ? 124 : 128;
                shRemain -= shCnt;
            }
            else
            {
                shCnt = shRemain;
                shRemain = 0;
            }
            shWriteCnt = shCnt;
            shCnt--;
            while(shCnt > 0)
            {
                usCurrLUT = (g_pucDdcciRxBuf[ucCurPointer - 1] << 8) | g_pucDdcciRxBuf[ucCurPointer];

                if(ucCurPointer == ucPointer + ucLUTLength - 1)
                {
                    if(bIsLastLUT == _TRUE)
                    {
                        pucIntoLUT[shCnt--] = 0;
                        pucIntoLUT[shCnt--] = 0;

                        // Save 1024
                        pucIntoLUT[shCnt--] = usCurrLUT & 0xFF;
                        pucIntoLUT[shCnt--] = usCurrLUT >> 8;
                        ucCurPointer -= 2;
                        continue;
                    }
                    else
                    {
                        usFlashSaveLength = 2;
                        usFlashSaveAddr = (usStartAddr + g_ppusGammaCount[ucGammaIndex][ucRGB]);
                        UserCommonDdcciDispCalibFlashData(_READ, ucGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, pData);
                        usLastLUT = (pData[0] << 8) | pData[1];
                    }
                }
                else
                {
                    usLastLUT = (g_pucDdcciRxBuf[ucCurPointer + 1] << 8) | g_pucDdcciRxBuf[ucCurPointer + 2];
                }

                if(bIsLastLUT == _TRUE)
                {
                    // Last interpolation: 1020, 1021, 1022; 1023 = 1024
                    pucIntoLUT[shCnt--] = usLastLUT & 0xFF;
                    pucIntoLUT[shCnt--] = (usLastLUT >> 8) & 0x3F;

                    for(ucJ = 1; ucJ < 4; ucJ++)
                    {
                        usInto = usLastLUT - (2 * (DWORD)(usLastLUT - usCurrLUT) * ucJ + 3) / 6;
                        pucIntoLUT[shCnt--] = usInto & 0xFF;
                        pucIntoLUT[shCnt--] = (usInto >> 8);
                    }

                    bIsLastLUT = _FALSE;
                }
                else
                {
#if(_OCC_SUPPORT == _ON)
                    if(bOCCMode == _TRUE)
                    {
                        if(g_ppusGammaCount[ucGammaIndex][ucRGB] - (shWriteCnt - shCnt - 1) <= 164) // Latch: No Intopolation
                        {
                            bWriteDirectly = _TRUE;

                            if((shWriteCnt - shCnt - 1) != 0)
                            {
                                usFlashSaveLength = (shWriteCnt - shCnt - 1);
                                usFlashSaveAddr = (usStartAddr + g_ppusGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                                UserCommonDdcciDispCalibFlashData(_WRITE, ucGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, (pucIntoLUT + shCnt + 1));
                                g_ppusGammaCount[ucGammaIndex][ucRGB] -= shWriteCnt - shCnt - 1;
                            }
                            break;
                        }
                        else
                        {
                            for(ucJ = 1; ucJ <= 4; ucJ++)
                            {
                                usInto = usLastLUT - ((usLastLUT - usCurrLUT) * ucJ + 2) / 4;
                                pucIntoLUT[shCnt--] = usInto & 0xFF;
                                pucIntoLUT[shCnt--] = (usInto >> 8) & 0x3F;
                            }
                        }
                    }
                    else
#endif
                    {
                        for(ucJ = 1; ucJ <= 4; ucJ++)
                        {
                            usInto = usLastLUT - ((usLastLUT - usCurrLUT) * ucJ + 2) / 4;
                            pucIntoLUT[shCnt--] = usInto & 0xFF;
                            pucIntoLUT[shCnt--] = usInto >> 8;
                        }
                    }
                }
                ucCurPointer -= 2;
            }

#if(_OCC_SUPPORT == _ON)
            if(bWriteDirectly == _TRUE)
            {
                if(g_ppusGammaCount[ucGammaIndex][ucRGB] <= 148) // Latch: No Intopolation
                {
                    usFlashSaveLength = ucCurPointer - ucPointer + 1;
                    usFlashSaveAddr = (usStartAddr + g_ppusGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                    UserCommonDdcciDispCalibFlashData(_WRITE, ucGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, &g_pucDdcciRxBuf[ucPointer]);
                    g_ppusGammaCount[ucGammaIndex][ucRGB] = g_ppusGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength;
                    bWriteDirectly = _FALSE;
                    break;
                }
                else if(g_ppusGammaCount[ucGammaIndex][ucRGB] <= 164) // add 16 0s
                {
                    memset(pData, 0, 16);
                    usFlashSaveLength = 16;
                    usFlashSaveAddr = (usStartAddr + g_ppusGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                    UserCommonDdcciDispCalibFlashData(_WRITE, ucGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, pData);
                    g_ppusGammaCount[ucGammaIndex][ucRGB] = 148;

                    usFlashSaveLength = ucCurPointer - ucPointer + 1;
                    usFlashSaveAddr = (usStartAddr + g_ppusGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                    UserCommonDdcciDispCalibFlashData(_WRITE, ucGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, &g_pucDdcciRxBuf[ucPointer]);
                    g_ppusGammaCount[ucGammaIndex][ucRGB] = g_ppusGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength;
                    bWriteDirectly = _FALSE;
                    break;
                }
                bWriteDirectly = _FALSE;
            }
            else
#endif
            {
                usFlashSaveLength = shWriteCnt;
                usFlashSaveAddr = (usStartAddr + g_ppusGammaCount[ucGammaIndex][ucRGB] - usFlashSaveLength);
                UserCommonDdcciDispCalibFlashData(_WRITE, ucGammaBankNum, ucGammaIndex, usFlashSaveAddr, usFlashSaveLength, pucIntoLUT);
                g_ppusGammaCount[ucGammaIndex][ucRGB] -= shWriteCnt;
            }
        }
        ucPointer += ucLUTLength;
    }
}

//--------------------------------------------------
// Description  : Calculate the checksum of data in Flash
// Input Value  : ucCheckType: 0- OGC, 1-OCC, 2-DICOM, 3-RGB gain, other- color Matrix,
// Output Value : Checksum
//--------------------------------------------------
BYTE UserCommonDdcciDispCalibCalCheckSum(BYTE ucCheckType)
{
    WORD usI = 0;
    WORD usJ = 0;
    BYTE ucBank = 0;
    BYTE ucGammaBankNum = 0;
    BYTE *pucGammaBankAddr = _NULL_POINTER;

    if(ucCheckType != _UNIFORMITY_GAIN_TYPE)
    {
        if(_OGC_FLASH_BANK < MCU_FFFD_XDATA_BANK_START)
        {
            return _FALSE;
        }

        ucBank = MCU_FFFE_XDATA_BANK_SEL;
        MCU_FFFE_XDATA_BANK_SEL = _OGC_FLASH_BANK - MCU_FFFD_XDATA_BANK_START;
    }

    pData[0] = 0;

    switch(ucCheckType)
    {
        case _OGC_TYPE:
            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA1_TYPE, _OGC_NORMAL_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA1_TYPE, _OGC_NORMAL_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

#if(_OGC_TOTAL_GAMMA == 1)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA2_TYPE, _OGC_NORMAL_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA2_TYPE, _OGC_NORMAL_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }
#if(_OGC_TOTAL_GAMMA == 2)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA3_TYPE, _OGC_NORMAL_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA3_TYPE, _OGC_NORMAL_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

#if(_OGC_TOTAL_GAMMA == 3)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA4_TYPE, _OGC_NORMAL_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA4_TYPE, _OGC_NORMAL_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }
#if(_OGC_TOTAL_GAMMA == 4)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA5_TYPE, _OGC_NORMAL_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA5_TYPE, _OGC_NORMAL_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

#if(_OGC_TOTAL_GAMMA == 5)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA6_TYPE, _OGC_NORMAL_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA6_TYPE, _OGC_NORMAL_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

#if(_OGC_TOTAL_GAMMA == 6)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif
            break;

        case _OGC_MAX_BRI_TYPE:
            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA1_TYPE, _OGC_MAX_BACKLIGHT_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA1_TYPE, _OGC_MAX_BACKLIGHT_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

#if(_OGC_TOTAL_GAMMA == 1)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA2_TYPE, _OGC_MAX_BACKLIGHT_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA2_TYPE, _OGC_MAX_BACKLIGHT_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }
#if(_OGC_TOTAL_GAMMA == 2)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA3_TYPE, _OGC_MAX_BACKLIGHT_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA3_TYPE, _OGC_MAX_BACKLIGHT_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

#if(_OGC_TOTAL_GAMMA == 3)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA4_TYPE, _OGC_MAX_BACKLIGHT_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA4_TYPE, _OGC_MAX_BACKLIGHT_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }
#if(_OGC_TOTAL_GAMMA == 4)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA5_TYPE, _OGC_MAX_BACKLIGHT_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA5_TYPE, _OGC_MAX_BACKLIGHT_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

#if(_OGC_TOTAL_GAMMA == 5)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            ucGammaBankNum = UserCommonAdjustOGCBank(_OGC_GAMMA6_TYPE, _OGC_MAX_BACKLIGHT_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(_OGC_GAMMA6_TYPE, _OGC_MAX_BACKLIGHT_TYPE);

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(ucGammaBankNum, ((WORD)pucGammaBankAddr + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

#if(_OGC_TOTAL_GAMMA == 6)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif
            break;

        case _OCC_TYPE:

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 148; usI++)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_GAMMA10_ADDRESS + usJ * 2200 + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }

                for(usI = 164; usI < 2200; usI = usI + 8)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_GAMMA10_ADDRESS + usJ * 2200 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

            break;

        case _OCC_HDR_TYPE:

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 148; usI++)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_HDR10_GAMMA10_ADDRESS + usJ * 2200 + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }

                for(usI = 164; usI < 2200; usI = usI + 8)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_HDR10_GAMMA10_ADDRESS + usJ * 2200 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

            break;

        case _DICOM_TYPE:

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_DICOM_ADDRESS + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

            break;

        case _RGB_GAIN_TYPE:

            for(usI = _OGC_RGB_GAIN_ADDRESS; usI < (_OGC_RGB_GAIN_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;

        case _RGB_GAIN_MAX_BRI_TYPE:

            for(usI = _OGC_RGB_GAIN_MAX_BRI_ADDRESS; usI < (_OGC_RGB_GAIN_MAX_BRI_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;

        case _HEADER_TYPE:

            //==========Calculate OGC Header============
            for(usI = _OGC_HEADER_ADDRESS + 3; usI < _OCC_HEADER_ADDRESS; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }
            //==========Calculate OCC Header============
            for(usI = _OCC_HEADER_ADDRESS + 3; usI < _DICOM_HEADER_ADDRESS; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }
            //==========Calculate DICOM Header============
            for(usI = _DICOM_HEADER_ADDRESS + 3; usI < _WHITE_LV_HEADER_ADDRESS; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }
            //==========Calculate White Lv Header============
            for(usI = _WHITE_LV_HEADER_ADDRESS + 3; usI < (_WHITE_LV_HEADER_ADDRESS + _WHITE_LV_HEADER_LENGTH); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_TYPE:

            for(usI = _OCC_SRGBMATRIX_ADDRESS; usI < (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_TYPE2:

            for(usI = (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI < (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2 + g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_NUM])); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_MAX_BRI_TYPE:

            for(usI = _OCC_SRGBMATRIX_MAX_BRI_ADDRESS; usI < (_OCC_SRGBMATRIX_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_MAX_BRI_TYPE2:

            for(usI = (_OCC_SRGBMATRIX_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2)); usI < (_OCC_SRGBMATRIX_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_PCM_USER_DEFINE_2 + g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_NUM])); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

#if(_HDR10_SUPPORT == _ON)
        case _HDR_TYPE:

            for(usI = _OCC_HDR10_SRGB_MATRIX_ADDRESS; usI < (_OCC_HDR10_SRGB_MATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * 4); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            for(usJ = 0; usJ < _HDR_TOTAL_IG; usJ++)
            {
                for(usI = 0; usI < _OGC_HDR10_IG_TABLE_SIZE; usI++)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_IG_1200_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * usJ + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }
            }

            break;

        case _HDR10_NOTM_BOUND_TYPE:

            for(usI = 0; usI < _NOTM_BOUND_SAVE_LENGTH; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_NOTM_BOUND_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        case _DIMMING_OG_TYPE:

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 148; usI++)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_OCC_GAMMA10_ADDRESS + usJ * 2200 + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }

                for(usI = 164; usI < 2200; usI = usI + 8)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_OCC_GAMMA10_ADDRESS + usJ * 2200 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

            break;

#if(_OGC_SUPPORT == _ON)
        case _DIMMING_IG_TYPE:

            for(usJ = 0; usJ < _OGC_TOTAL_GAMMA; usJ++)
            {
                for(usI = 0; usI < _OGC_HDR10_IG_TABLE_SIZE; usI++)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_OGC_GAMMA1_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * usJ + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }
            }

            for(usI = _DIMMING_OGC_RGB_GAIN_ADDRESS; usI < (_DIMMING_OGC_RGB_GAIN_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;
#endif

#endif

        case _EDID_INFO_TYPE:
            for(usI = 0; usI < 14; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _EDID_INFO_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }
            break;

        case _NOTM_DCR_THD_TYPE:
            for(usI = 0; usI < _NOTM_DCR_THD_LENGTH; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_NOTM_DCR_THD_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }
            break;

#if(_FREESYNC_II_SUPPORT == _ON)
        case _FREESYNC_II_OG_TYPE:

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 148; usI++)
                {
                    UserCommonFlashRead(_FREESYNC_II_FLASH_BANK, ((((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_OCC_GAMMA10_ADDRESS + usJ * 2200 + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }

                for(usI = 164; usI < 2200; usI = usI + 8)
                {
                    UserCommonFlashRead(_FREESYNC_II_FLASH_BANK, ((((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_OCC_GAMMA10_ADDRESS + usJ * 2200 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }
            break;

        case _FREESYNC_II_IG_TYPE:
            for(usJ = 0; usJ < 5; usJ++)
            {
                for(usI = 0; usI < _OGC_HDR10_IG_TABLE_SIZE; usI++)
                {
                    UserCommonFlashRead(_FREESYNC_II_FLASH_BANK, ((((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_IG_SRGB_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * usJ + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }
            }
            break;
#endif
        default:
            break;
    }

    MCU_FFFE_XDATA_BANK_SEL = ucBank;

    return pData[0];
}

//--------------------------------------------------
// Description  : Measure End --> Show Gamma
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibShowGamma(void)
{
#if(_OGC_SUPPORT == _ON)
    BYTE ucGammaIndex = 0;
    BYTE ucColorTempIndex = 0;
    BYTE ucGammaBankNum = 0;
    BYTE *pucGammaBankAddr = _NULL_POINTER;
#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
    WORD pusBriTemp[3] = {0x200, 0x200, 0x200};
#else
    WORD pusBriTemp[3] = {0x80, 0x80, 0x80};
#endif
#endif

    ScalerColorOutputGammaEnable(_FUNCTION_OFF);

#if(_OGC_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FINAL_TYPE] == _OGC_CAL_TYPE)
    {
        ucGammaIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_GAMMA_CT_INFO] >> 4) & 0x0F;
        ucColorTempIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_GAMMA_CT_INFO] & 0x0F;

#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
        if(g_ucBacklightFlag == _MAX_BACKLIGHT_CAL)
        {
            ucGammaBankNum = UserCommonAdjustOGCBank(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(ucGammaIndex, _OGC_MAX_BACKLIGHT_TYPE);
        }
        else
#endif
        {
            ucGammaBankNum = UserCommonAdjustOGCBank(ucGammaIndex, _OGC_NORMAL_TYPE);
            pucGammaBankAddr = UserCommonAdjustOGCAddr(ucGammaIndex, _OGC_NORMAL_TYPE);
        }

        ScalerColorOutputGammaAdjust(pucGammaBankAddr, ucGammaBankNum);
        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusBriTemp);

        if(ucColorTempIndex != 0x0F)
        {
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pData);
        }
        else // Native
        {
            pData[0] = 0x08;
            pData[1] = 0x00;
            pData[2] = 0x08;
            pData[3] = 0x00;
            pData[4] = 0x08;
            pData[5] = 0x00;
        }
        ScalerColorContrastAdjust(_CONTRAST_COEF_A, ((WORD *)pData));
        ScalerColorContrastEnable(_FUNCTION_ON);

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
        ScalerColorSRGBEnable(_FUNCTION_OFF);
#endif

        UserCommonDdcciDispCalibCalibPatternEnable(_DISABLE);
    }
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FINAL_TYPE] == _OCC_CAL_TYPE)
    {
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
        ScalerColorOutputGammaEnable(_FUNCTION_OFF);
        ScalerColorSRGBEnable(_FUNCTION_OFF);


#if((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_DICOM_HDR) && (_HDR10_SUPPORT == _OFF))
        ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);
#else
        if(g_ucBacklightFlag == _NORMAL_BACKLIGHT_CAL)
        {
            ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);
        }
        else
        {
            ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_HDR10_GAMMA10_ADDRESS, _OGC_FLASH_BANK);
        }
#endif

        ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, tSRGBByPass, GET_CURRENT_BANK_NUMBER(), 18);
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

        ScalerColorOutputGammaEnable(_FUNCTION_ON);
        ScalerColorSRGBEnable(_FUNCTION_ON);
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

        ScalerColorBrightnessEnable(_FUNCTION_OFF);
        ScalerColorContrastEnable(_FUNCTION_OFF);

        if(g_ucPatternType == _PG_PATTERN)
        {
            ScalerDDomainPatternGenAdjustColor10bit(tOCC_SRGB_TABLE[0], tOCC_SRGB_TABLE[1], tOCC_SRGB_TABLE[2]);
        }
        else
        {
            ScalerDDomainBackgroundEnable(_FALSE);
            ScalerDDomainPatternGenAdjustColor10bit(tOCC_SRGB_TABLE[0], tOCC_SRGB_TABLE[1], tOCC_SRGB_TABLE[2]);
        }
    }
    else
    {
        UserCommonDdcciDispCalibCalibPatternEnable(_DISABLE);
    }
#endif  // End of #if(_OCC_SUPPORT == _ON)

#if(_OGC_DICOM_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FINAL_TYPE] == _DICOM_CAL_TYPE)
    {
        ScalerColorOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OGC_DICOM_ADDRESS, _OGC_FLASH_BANK);

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

        ScalerColorBrightnessEnable(_FUNCTION_OFF);
        ScalerColorContrastEnable(_FUNCTION_OFF);

        ScalerColorSRGBEnable(_FUNCTION_OFF);
        UserCommonDdcciDispCalibCalibPatternEnable(_DISABLE);
    }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)
    ScalerColorOutputGammaEnable(_FUNCTION_ON);
}

//--------------------------------------------------
// Description  : Display Calibration Measure End CheckSum
// Input Value  : None
// Output Value : _SUCCESS/_FAIL
//--------------------------------------------------
BYTE UserCommonDdcciDispCalibCheckSum(void)
{
    BYTE ucFlag = 1;
#if(_UNIFORMITY_SUPPORT == _ON)
    WORD usI = 0;
    BYTE pucTemp[2] = {0, 0};
    BYTE ucGainTableBank = 0;
    WORD usGainTableAddr = 0;
    WORD usGainCheckSumAddr = 0;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    BYTE ucOffsetTableBank = 0;
    BYTE ucOffsetTableStartBank = 0;
    WORD usOffsetTableAddr = 0;
    WORD usDecayTableAddr = 0;
    WORD usOffsetCheckSumAddr = 0;
    WORD usDecayCheckSumAddr = 0;
#endif
#endif

    if(g_ucBacklightFlag == _NORMAL_BACKLIGHT_CAL)
    {
#if(_OGC_SUPPORT == _ON)
        if(((g_ucCalibrationType >> _OGC_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[1] = UserCommonDdcciDispCalibCalCheckSum(_OGC_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_CHKSUM] == pData[1])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_CHKSUM_ADDRESS, 1, &pData[1]);
                pData[4] = _OGC_SUPPORT;
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_FINISH_ADDRESS, 1, &pData[4]);
            }
            else
            {
                ucFlag = _BIT1;
            }
        }
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_SUPPORT == _ON)
        if(((g_ucCalibrationType >> _OCC_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[2] = UserCommonDdcciDispCalibCalCheckSum(_OCC_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_CHKSUM] == pData[2])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_CHKSUM_ADDRESS, 1, &pData[2]);
                pData[4] = _OCC_SUPPORT;
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_FINISH_ADDRESS, 1, &pData[4]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
        }

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
        if(((g_ucCalibrationType >> _DIMMING_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[2] = UserCommonDdcciDispCalibCalCheckSum(_DIMMING_OG_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_OCC_CHKSUM] == pData[2])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_OCC_CHKSUM_ADDRESS, 1, &pData[2]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
        }
#endif
#endif  // End of #if(_OCC_SUPPORT == _ON)

    }

#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
    if(g_ucBacklightFlag == _MAX_BACKLIGHT_CAL)
    {
#if(_OGC_SUPPORT == _ON)
        if(((g_ucCalibrationType >> _OGC_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[1] = UserCommonDdcciDispCalibCalCheckSum(_OGC_MAX_BRI_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_CHKSUM] == pData[1])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_MAX_BRI_CHKSUM_ADDRESS, 1, &pData[1]);
            }
            else
            {
                ucFlag |= _BIT1;
            }
        }
#endif  // End of #if(_OGC_SUPPORT == _ON)
    }
#endif

#if(_OGC_DICOM_SUPPORT == _ON)
#if(_TWO_BRI_CALIBRATION_TYPE != _TWO_BRI_CALIBRATION_NONE)
    if(g_ucBacklightFlag == _MAX_BACKLIGHT_CAL)
#else
    if(g_ucBacklightFlag == _NORMAL_BACKLIGHT_CAL)
#endif
    {
        if(((g_ucCalibrationType >> _DICOM_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[3] = UserCommonDdcciDispCalibCalCheckSum(_DICOM_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DICOM_CHKSUM] == pData[3])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_DICOM_CHKSUM_ADDRESS, 1, &pData[3]);
                pData[4] = _OGC_DICOM_SUPPORT;
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_DICOM_FINISH_ADDRESS, 1, &pData[4]);
            }
            else
            {
                ucFlag |= _BIT3;
            }
        }
    }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)


#if(_TWO_BRI_CALIBRATION_TYPE != _TWO_BRI_CALIBRATION_NONE)
#if(_HDR10_SUPPORT == _ON)
    if(g_ucBacklightFlag == _MAX_BACKLIGHT_CAL)
    {
        if(((g_ucCalibrationType >> _OCC_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[2] = UserCommonDdcciDispCalibCalCheckSum(_OCC_HDR_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_CHKSUM] == pData[2])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_HDR_CHKSUM_ADDRESS, 1, &pData[2]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
        }
    }
#endif  // End of #if(_HDR10_SUPPORT == _ON)
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
#if(_TWO_BRI_CALIBRATION_TYPE != _TWO_BRI_CALIBRATION_NONE)
    if(g_ucBacklightFlag == _MAX_BACKLIGHT_CAL)
#else
    if(g_ucBacklightFlag == _NORMAL_BACKLIGHT_CAL)
#endif
    {
        if(((g_ucCalibrationTypeII >> _FREESYNC_II_CAL_TYPE) & 0x01) == _TRUE)
        {
            pData[2] = UserCommonDdcciDispCalibCalCheckSum(_FREESYNC_II_OG_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FREESYNC_II_CHKSUM] == pData[2])
            {
                UserCommonFlashWrite(_FREESYNC_II_FLASH_BANK, (((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_CHKSUM_ADDRESS, 1, &pData[2]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
        }
    }
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    if(((g_ucUniformityChecksumType >> _UNIFORMITY_GAIN_TYPE) & 0x01) == _TRUE)
    {
        // level0
        pucTemp[1] = 0;
        ucGainTableBank = UserCommonAdjustPanelUniformityGainBank(g_ucUniformityLUTStartPosIndex);
        usGainTableAddr = UserCommonAdjustPanelUniformityGainAddr(g_ucUniformityLUTStartPosIndex);
        usGainCheckSumAddr = usGainTableAddr + _PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonAdjustGetUniformityType(g_ucUniformityLUTStartPosIndex);
        for(usI = usGainTableAddr; usI < (usGainTableAddr + _PANEL_UNIFORMITY_1LEVEL_SIZE * UserCommonAdjustGetUniformityType(g_ucUniformityLUTStartPosIndex)); usI++)
        {
            UserCommonFlashRead(g_ucUniformityLUTSaveBank, usI, 1, &pucTemp[0]);
            pucTemp[1] += pucTemp[0];
        }
        //
        UserCommonFlashWrite(g_ucUniformityLUTSaveBank, usGainCheckSumAddr, 1, &pucTemp[1]);
        UserCommonFlashRead(g_ucUniformityLUTSaveBank, usGainCheckSumAddr, 1, &pData[5]);

        if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_CHKSUM] == pData[5]) &&
           (pucTemp[1] == pData[5]))
        {
            if((g_ucUniformityLUTStartPosIndex + 1) == _UNIFORMITY_TOTAL_SET)
            {
                pData[4] = _UNIFORMITY_SUPPORT;
                UserCommonFlashWrite(_UNIFORMITY_FLASH_BANK0, _UNIFORMITY_FINISH_ADDRESS, 1, &pData[4]);
            }
        }
        else
        {
            ucFlag |= _BIT4;
        }
    }
    // level0
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    if(((g_ucUniformityChecksumType >> _UNIFORMITY_OFFSET_TYPE) & 0x01) == _TRUE)
    {
        // level0
        pucTemp[1] = 0;
        ucOffsetTableBank = UserCommonAdjustPanelUniformityOffsetBank(g_ucUniformityLUTStartPosIndex);
        usOffsetTableAddr = UserCommonAdjustPanelUniformityOffsetAddr(g_ucUniformityLUTStartPosIndex);
        usOffsetCheckSumAddr = usOffsetTableAddr + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE;
        for(usI = usOffsetTableAddr; usI < (usOffsetTableAddr + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE); usI++)
        {
            UserCommonFlashRead(ucOffsetTableBank, usI, 1, &pucTemp[0]);
            pucTemp[1] += pucTemp[0];
        }
        //
        UserCommonFlashWrite(ucOffsetTableBank, usOffsetCheckSumAddr, 1, &pucTemp[1]);
        UserCommonFlashRead(ucOffsetTableBank, usOffsetCheckSumAddr, 1, &pData[5]);

        if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_CHKSUM] == pData[5]) &&
           (pucTemp[1] == pData[5]))
        {
            if((g_ucUniformityLUTStartPosIndex + 1) == _UNIFORMITY_TOTAL_SET)
            {
                pData[4] = _UNIFORMITY_LEVEL0_SUPPORT;
                ucOffsetTableStartBank = UserCommonAdjustPanelUniformityOffsetBank(0);
                UserCommonFlashWrite(ucOffsetTableStartBank, _UNIFORMITY_OFFSET_FINISH_ADDRESS, 1, &pData[4]);
            }
        }
        else
        {
            ucFlag |= _BIT4;
        }
    }
    if(((g_ucUniformityChecksumType >> _UNIFORMITY_DECAY_TYPE) & 0x01) == _TRUE)
    {
        // level0
        pucTemp[1] = 0;
        ucOffsetTableBank = UserCommonAdjustPanelUniformityOffsetBank(g_ucUniformityLUTStartPosIndex);
        usDecayTableAddr = UserCommonAdjustPanelUniformityDecayAddr(g_ucUniformityLUTStartPosIndex);
        usDecayCheckSumAddr = usDecayTableAddr + _PANEL_UNIFORMITY_DECAY_LUT_SIZE;
        for(usI = usDecayTableAddr; usI < (usDecayTableAddr + _PANEL_UNIFORMITY_DECAY_LUT_SIZE); usI++)
        {
            UserCommonFlashRead(ucOffsetTableBank, usI, 1, &pucTemp[0]);
            pucTemp[1] += pucTemp[0];
        }
        //
        UserCommonFlashWrite(ucOffsetTableBank, usDecayCheckSumAddr, 1, &pucTemp[1]);
        UserCommonFlashRead(ucOffsetTableBank, usDecayCheckSumAddr, 1, &pData[5]);

        if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_CHKSUM] != pData[5]) ||
           (pucTemp[1] != pData[5])) // do not set bit0 in flash
        {
            ucFlag |= _BIT4;
        }
    }
#endif
#endif  // End of #if(_UNIFORMITY_SUPPORT == _ON)

    return ucFlag;
}

//--------------------------------------------------
// Description  : Display Calibration OCC Measure End Matrix CheckSum
// Input Value  : ucCheckType: 5- color matrix
// Output Value : _SUCCESS/_FAIL
//--------------------------------------------------
BYTE UserCommonDdcciDispCalibMatrixCheckSum(BYTE ucCheckType)
{
    BYTE ucFlag = 1;
    BYTE pucTemp[2] = {0, 0};

    switch(ucCheckType)
    {
        case _COLOR_MATRIX_TYPE:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_COLOR_MATRIX_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

        case _COLOR_MATRIX_TYPE2:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_COLOR_MATRIX_TYPE2);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX2_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

        case _COLOR_MATRIX_MAX_BRI_TYPE:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_COLOR_MATRIX_MAX_BRI_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX_MAX_BRI_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

        case _COLOR_MATRIX_MAX_BRI_TYPE2:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_COLOR_MATRIX_MAX_BRI_TYPE2);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX2_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX2_MAX_BRI_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

#if(_HDR10_SUPPORT == _ON)
        case _HDR_TYPE:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_HDR_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_CHKSUM_ADDRESS, 1, &pucTemp[0]);
                pucTemp[1] = _HDR10_SUPPORT;
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_FINISH_ADDRESS, 1, &pucTemp[1]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;

        case _HDR10_NOTM_BOUND_TYPE:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_HDR10_NOTM_BOUND_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_NOTM_BOUND_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
#if(_OGC_SUPPORT == _ON)
        case _DIMMING_IG_TYPE:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_DIMMING_IG_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_IG_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;
#endif
#endif

        case _RGB_GAIN_TYPE:

#if(_OGC_SUPPORT == _ON)
            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_RGB_GAIN_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN_CHKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
#endif
            pucTemp[1] = UserCommonDdcciDispCalibCalCheckSum(_HEADER_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_HEADER_CHKSUM] == pucTemp[1])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HEADER_CHKSUM_ADDRESS, 1, &pucTemp[1]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;

        case _RGB_GAIN_MAX_BRI_TYPE:

#if(_OGC_SUPPORT == _ON)
            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_RGB_GAIN_MAX_BRI_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN_CHKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_MAX_BRI_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
#endif
            break;

        case _EDID_INFO_TYPE:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_EDID_INFO_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _EDID_INFO_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;

        case _NOTM_DCR_THD_TYPE:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_NOTM_DCR_THD_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _DIMMING_NOTM_DCR_THD_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;

#if(_FREESYNC_II_SUPPORT == _ON)
        case _FREESYNC_II_IG_TYPE:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_FREESYNC_II_IG_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_FREESYNC_II_FLASH_BANK, (((WORD)_FREESYNC_II_FLASH_PAGE) << 12) + _FREESYNC_II_IG_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;
#endif

        default:
            break;
    }

    return ucFlag;
}

//--------------------------------------------------
// Description  : Display Calibration Reply Results
// Input Value  : ucType --> Pass or other Fail Errors
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyResult(BYTE ucType)
{
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x04;

    switch(ucType)
    {
        case _DISP_CALIB_START:

            g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x04;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_OGCOCCDICOM_SUPPORT] =
                (_FREESYNC_II_SUPPORT << 7) |
                (_BACKLIGHT_DIMMING_SUPPORT << 6) |
                ((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_DICOM_HDR) << 5) |
                (_HDR10_SUPPORT << 4) |
                (_FREESYNC_II_GLOBAL_BACKLIGHT_SUPPORT << 3) |
                (_OGC_DICOM_SUPPORT << 2) |
                (_OCC_SUPPORT << 1) |
                (_OGC_SUPPORT);
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_OGC_TOTAL_GAMMA] = ((_DISP_CALIB_VERSION << 3) | _OGC_TOTAL_GAMMA);
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_OGC_TOTAL_CT] = _OGC_TOTAL_CT;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_BITNUM] = ((_PANEL_DISP_BIT_MODE << 4) | ((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR) << 2) | _OCC_LUT_MODE);
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_BITNUM + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_GET_VERSION:

            g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x02;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_H] = ((_DISP_CALIB_FW_VERSION & 0xFF00) >> 8);
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_L] = (_DISP_CALIB_FW_VERSION & 0xFF);
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_L + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_GET_NOTM_INFO:

            g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x03;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_MAX_LV] = _PANEL_MAX_LUMINANCE;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_MAX_FRAME_AVE_LV] = _PANEL_MAX_FRAME_AVERAGE_LUMINANCE;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_MIN_LV] = 0x00; // _PANEL_MIN_LUMINANCE tie to 0
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_MIN_LV + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_GET_UNI_VERSION:

            g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x02;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_H] = ((_DISP_CALIB_UNI_VERSION & 0xFF00) >> 8);
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_L] = (_DISP_CALIB_UNI_VERSION & 0xFF);
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_FW_VERSION_L + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_GET_FW_SUPPORT:

            g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x02;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_FW_SUPPORT] = ((_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1) << 2) | (_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT << 1) | _LD_HDR10_BOOST_SUPPORT;
#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_FW_SUPPORT + 1] = _PANEL_MAX_USER_DEFINE_LUMINANCE;
#else
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_FW_SUPPORT + 1] = 0x00;
#endif
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_FW_SUPPORT + 2] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_PASS:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'P';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'A';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'S';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'S';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_ERASE_ERROR:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'E';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'R';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'A';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'S';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_FW_ERROR:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'F';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'W';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'E';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = g_ucCalibrationType;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_CRC_ERROR:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'C';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'R';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'C';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'E';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_FAIL:

        default:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'F';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'A';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'I';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'L';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

            break;
    }

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);

    EX1 = 1;
}
//--------------------------------------------------
// Description  : Save OGC/OCC Header
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibSaveHeader(void)
{
    // UserCommonFlashWrite(_OGC_FLASH_BANK, 0x0030, g_pucDdcciRxBuf[1] & 0x7F, g_pucDdcciRxBuf);
    //==========Write OGC Header============
    pData[0] = 0x11;
    pData[1] = 0x11;
    pData[2] = _OGC_HEADER_LENGTH;
    pData[3] = g_pucDdcciRxBuf[_OGC_HEADER_IF_DO_OGC]; // 1: Do OGC; 0: not do OGC, even if OGC SUPPORT is on
    UserCommonFlashWrite(_OGC_FLASH_BANK, _OGC_HEADER_ADDRESS, 4, pData);
    UserCommonFlashWrite(_OGC_FLASH_BANK, _OGC_HEADER_ADDRESS + 4, 2 + _OGC_TOTAL_GAMMA + _OGC_TOTAL_CT, g_pucDdcciRxBuf + _OGC_HEADER_GAMMA_CT_INDEX);
    // Gamma Number, Gamma Index1, GammaIndex2,..., Gamma Index n;
    // CT Numer, CT Index1, CT Index 2, ..., CT Index n.

    //==========Write OCC Header============
    pData[0] = 0x22;
    pData[1] = 0x22;
    pData[2] = _OCC_HEADER_LENGTH;
    pData[3] = g_pucDdcciRxBuf[_OCC_HEADER_IF_DO_OCC]; // 1: do OCC; 0: not do OCC, even if OCC support is on
    pData[4] = g_pucDdcciRxBuf[_OCC_HEADER_MATRIX_NUMBER]; // Matrix Number:3/2/1. 1st is sRGB, 2nd is Adobe, 3rd is SoftProof
    UserCommonFlashWrite(_OGC_FLASH_BANK, _OCC_HEADER_ADDRESS, 5, pData);
    //==========Write DICOM Header============
    pData[0] = 0x33;
    pData[1] = 0x33;
    pData[2] = _DICOM_HEADER_LENGTH;
    pData[3] = g_pucDdcciRxBuf[_DICOM_HEADER_IF_DO_DICOM];
    pData[4] = g_pucDdcciRxBuf[_DICOM_HEADER_MODE]; // 0 - By RGB Mode; 1- By Gray Mod
    UserCommonFlashWrite(_OGC_FLASH_BANK, _DICOM_HEADER_ADDRESS, 5, pData);

    //==========Write White Lv Header============
    pData[0] = 0x44;
    pData[1] = 0x44;
    pData[2] = _WHITE_LV_HEADER_LENGTH;
    pData[3] = g_pucDdcciRxBuf[_WHITE_LV_HEADER];
    pData[4] = g_pucDdcciRxBuf[_WHITE_LV_HEADER + 1];
    UserCommonFlashWrite(_OGC_FLASH_BANK, _WHITE_LV_HEADER_ADDRESS, 5, pData);
}

//--------------------------------------------------
// Description  : Save EDID info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibSaveEDIDInfo(void)
{
    UserCommonFlashWrite(_OGC_FLASH_BANK, _EDID_INFO_ADDRESS, 14, g_pucDdcciRxBuf + _DDCCI_DISP_CALIB_EDID_INDEX);
}

//--------------------------------------------------
// Description  : Save No ToneMapping DCR THD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibSaveNoToneMappingDCRTHD(void)
{
    UserCommonFlashWrite(_OGC_FLASH_BANK, _DIMMING_NOTM_DCR_THD_ADDRESS, _NOTM_DCR_THD_LENGTH, g_pucDdcciRxBuf + _DDCCI_DISP_CALIB_NOTM_DCR_THD_INDEX);
}

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Save HDR10 No Tone Mapping Bound info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibSaveHDR10BoundInfo(void)
{
    UserCommonFlashWrite(_OGC_FLASH_BANK, _OGC_HDR10_NOTM_BOUND_ADDRESS, _NOTM_BOUND_SAVE_LENGTH, g_pucDdcciRxBuf + _DDCCI_DISP_CALIB_HDR10_NOTM_BOUND_INDEX);
}
#endif

#if((_FREESYNC_II_SUPPORT == _ON) || (_LD_HDR10_BOOST_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Show White Pattern
// Input Value  : BYTE ucPatternType
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibShowWhite(BYTE ucPatternType)
{
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
    ScalerColorSRGBEnable(_FUNCTION_OFF);

    if(ucPatternType == _FREESYNC_II_WHITE)
    {
        ScalerColorPCMOutputGammaAdjust(g_pucDISP_FREESYNC_II_CALIBRATION_FLASH + _FREESYNC_II_OCC_GAMMA10_ADDRESS, _FREESYNC_II_FLASH_BANK);
    }
    else if(ucPatternType == _LD_BOOST_WHITE)
    {
        ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_HDR10_GAMMA10_ADDRESS, _OGC_FLASH_BANK);
    }

    ScalerColorPCMSRGBAdjust(_SRGB_1_BIT_SHIFT_LEFT, tSRGBByPass, GET_CURRENT_BANK_NUMBER(), 18);

    ScalerColorOutputGammaEnable(_FUNCTION_ON);
    ScalerColorSRGBEnable(_FUNCTION_ON);
    ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

    ScalerColorBrightnessEnable(_FUNCTION_OFF);
    ScalerColorContrastEnable(_FUNCTION_OFF);

    if(g_ucPatternType == _PG_PATTERN)
    {
        ScalerDDomainPatternGenAdjustColor10bit(tOCC_SRGB_TABLE[18], tOCC_SRGB_TABLE[19], tOCC_SRGB_TABLE[20]);
    }
    else
    {
        ScalerDDomainBackgroundEnable(_FALSE);
        ScalerDDomainPatternGenAdjustColor10bit(tOCC_SRGB_TABLE[18], tOCC_SRGB_TABLE[19], tOCC_SRGB_TABLE[20]);
    }
}
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Display Calibration Reply PCM Matrix
// Input Value  : ucPCMType --> _PCM_OSD_SRGB or ADOBE_RGB
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyOCCMatrix(BYTE ucPCMType)
{
    /*if(g_ucUniformityLUTSaveBank < MCU_FFFD_XDATA_BANK_START)
    {
        return _FALSE;
    }*/

    WORD usReadStartPos = 0;
    WORD usTotalLength = 18;
    BYTE ucSendLength = 13;
    BYTE ucBank = 0;

#if(_OCC_LUT_MODE == _ON)
    usTotalLength = 306;
#endif

    ucBank = MCU_FFFE_XDATA_BANK_SEL;
    MCU_FFFE_XDATA_BANK_SEL = g_ucUniformityLUTSaveBank - MCU_FFFD_XDATA_BANK_START;

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;

    usReadStartPos = (WORD)ucSendLength * (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] >> 3);

    ucSendLength = ((usTotalLength - usReadStartPos) < 13) ? (usTotalLength - usReadStartPos) : 13;

#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
    switch(ucPCMType)
    {
        case _PCM_SRGB:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_SRGBMATRIX_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_ADOBE_RGB:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_ADOBEMATRIX_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_DCI_P3:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_DCIP3_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_2:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE2_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_DISPLAY_P3:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_DISPLAYP3_MAX_BRI_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        default:
            break;
    }
#else
    switch(ucPCMType)
    {
        case _PCM_SRGB:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_SRGBMATRIX_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_ADOBE_RGB:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_ADOBEMATRIX_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_DCI_P3:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_DCIP3_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_USER_DEFINE_2:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_USERDEFINE2_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_DISPLAY_P3:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_DISPLAYP3_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        default:
            break;
    }
#endif

    MCU_FFFE_XDATA_BANK_SEL = ucBank;

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    // ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);

    EX1 = 1;
}

//--------------------------------------------------
// Description  : Display Calibration Reply OGC Header
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyOGCHeader(void)
{
    WORD usReadStartPos = 0;
    BYTE ucSendLength = 13;
    BYTE ucBank = 0;

    ucBank = MCU_FFFE_XDATA_BANK_SEL;
    MCU_FFFE_XDATA_BANK_SEL = _OGC_FLASH_BANK - MCU_FFFD_XDATA_BANK_START;

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;

    usReadStartPos = (WORD)ucSendLength * (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x01);

    ucSendLength = ((_OGC_HEADER_LENGTH - usReadStartPos) < 13) ? (_OGC_HEADER_LENGTH - usReadStartPos) : 13;

    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OGC_HEADER_ADDRESS + usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
    g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

    MCU_FFFE_XDATA_BANK_SEL = ucBank;

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    // ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);

    EX1 = 1;
}

//--------------------------------------------------
// Description  : Reply the OGCOCC LV ratio to uniformity tool
// Input Value  : ucCTGammaIndex, the set of CT and gamma
// Output Value : CT_ratio,SRGB,AdobeRGB,DCIP3,displayP3,Userdefine--ratio
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyOGCOCCLvRatio(void)
{
    WORD usReadStartPos = 0;
    BYTE ucSendLength = 13;
    BYTE ucBank = 0;

    ucBank = MCU_FFFE_XDATA_BANK_SEL;
    MCU_FFFE_XDATA_BANK_SEL = _OGC_FLASH_BANK - MCU_FFFD_XDATA_BANK_START;
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    usReadStartPos = (WORD)ucSendLength * (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x0F);
    ucSendLength = ((_OGCOCC_LV_RARIO_LENGTH - usReadStartPos) < 13) ? (_OGCOCC_LV_RARIO_LENGTH - usReadStartPos) : 13;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OGCOCC_LV_RARIO_ADDRESS + usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
    g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

    MCU_FFFE_XDATA_BANK_SEL = ucBank;
    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);

    EX1 = 1;
}

//--------------------------------------------------
// Description  : Display Calibration Reply Define, which Uniformity Tool Needs
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyUniformityDefine(void)
{
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x08;

    g_pucDdcciTxBuf[2] = (_UNIFORMITY_1ST_TABLE_LEVEL << 4) |
                         (_OCC_LUT_MODE << 3) |
                         (_UNIFORMITY_TOTAL_SET & 0x07);

    g_pucDdcciTxBuf[3] = _PANEL_UNIFORMITY_HOR_INTERVAL;
    g_pucDdcciTxBuf[4] = (BYTE)_PANEL_DH_WIDTH;
    g_pucDdcciTxBuf[5] = (BYTE)(_PANEL_DH_WIDTH / 256);
    g_pucDdcciTxBuf[6] = (BYTE)_PANEL_DV_HEIGHT;
    g_pucDdcciTxBuf[7] = (BYTE)(_PANEL_DV_HEIGHT / 256);
    g_pucDdcciTxBuf[8] = (BYTE)_OGC_TOTAL_CT;

    // Level0
    // Offset
    g_pucDdcciTxBuf[9] = (_UNIFORMITY_OFFSET_TYPE5 << 5) |
                         (_UNIFORMITY_OFFSET_TYPE4 << 4) |
                         (_UNIFORMITY_OFFSET_TYPE3 << 3) |
                         (_UNIFORMITY_OFFSET_TYPE2 << 2) |
                         (_UNIFORMITY_OFFSET_TYPE1 << 1) |
                         _UNIFORMITY_OFFSET_TYPE0;

    g_pucDdcciTxBuf[10] = UserCommonDdcciCalCheckSum();// 8

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    // ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);

    EX1 = 1;
}
//--------------------------------------------------
// Description  : Reply the CCT gain to uniformity tool
// Input Value  : ucCTGammaIndex, the set of CT and gamma
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyCCTGain(void)
{
    BYTE ucGammaIndex = 0;
    BYTE ucColorTempIndex = 0;
    BYTE pucTemp[6] = {0, 0, 0, 0, 0, 0};
    ucGammaIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] >> 4) & 0x0F;
    ucColorTempIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] & 0x0F;
    if(ucColorTempIndex != 0x0F)
    {
#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_MAX_BRI_ADDRESS), 6, pucTemp);
#else
        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pucTemp);
#endif
    }
    else
    {
        pucTemp[0] = 0x08;
        pucTemp[1] = 0x00;
        pucTemp[2] = 0x08;
        pucTemp[3] = 0x00;
        pucTemp[4] = 0x08;
        pucTemp[5] = 0x00;
    }
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x06;
    g_pucDdcciTxBuf[2] = pucTemp[0];// R
    g_pucDdcciTxBuf[3] = pucTemp[1];
    g_pucDdcciTxBuf[4] = pucTemp[2];// G
    g_pucDdcciTxBuf[5] = pucTemp[3];
    g_pucDdcciTxBuf[6] = pucTemp[4];// B
    g_pucDdcciTxBuf[7] = pucTemp[5];
    g_pucDdcciTxBuf[8] = UserCommonDdcciCalCheckSum();// 8

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    // ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);

    EX1 = 1;
}

//--------------------------------------------------
// Description  : Reply the RGB x, y to uniformity tool
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyFastModeData(void)
{
    BYTE pucTemp[14] = {0};

    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12 | _EDID_INFO_ADDRESS), 14, pucTemp);

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x0A;
    g_pucDdcciTxBuf[2] = pucTemp[4];// rx, ry, gx, gy, 2 lsb
    g_pucDdcciTxBuf[3] = pucTemp[5];// bx, by, wx, wy, 2 lsb
    g_pucDdcciTxBuf[4] = pucTemp[6];// rx, 8msb
    g_pucDdcciTxBuf[5] = pucTemp[7];// ry, 8msb
    g_pucDdcciTxBuf[6] = pucTemp[8];// gx, 8msb
    g_pucDdcciTxBuf[7] = pucTemp[9];// gy, 8msb
    g_pucDdcciTxBuf[8] = pucTemp[10];// bx, 8msb
    g_pucDdcciTxBuf[9] = pucTemp[11];// by, 8msb
    g_pucDdcciTxBuf[10] = pucTemp[12];// wx, 8msb
    g_pucDdcciTxBuf[11] = pucTemp[13];// wy, 8msb
    g_pucDdcciTxBuf[12] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    // ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);

    EX1 = 1;
}
//--------------------------------------------------
// Description  : Reply uniformity level mode to uniformity tool
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyUniformityLevelMode(void)
{
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x03;
    g_pucDdcciTxBuf[2] = (_UNIFORMITY_1ST_TABLE_LEVEL << 4) | _UNIFORMITY_2ND_TABLE_LEVEL;
    g_pucDdcciTxBuf[3] = (_UNIFORMITY_3RD_TABLE_LEVEL << 4) | _UNIFORMITY_4TH_TABLE_LEVEL;
    g_pucDdcciTxBuf[4] = (_UNIFORMITY_5TH_TABLE_LEVEL << 4) | _UNIFORMITY_6TH_TABLE_LEVEL;

    g_pucDdcciTxBuf[5] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);

    EX1 = 1;
}

#endif // End of #if(_UNIFORMITY_SUPPORT == _ON)

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reply panel define
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyDimmingDefine(void)
{
#if(_LOCAL_DIMMING_SUPPORT == _ON)

#if(_LD_HDR10_BOOST_SUPPORT == _OFF)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_INDEX] == _DDCCI_DISP_DIMMING_TYPE_LOCAL)
    {
        g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
        g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x0D;
        g_pucDdcciTxBuf[2] = (BYTE)(_PANEL_DH_WIDTH / 256);
        g_pucDdcciTxBuf[3] = (BYTE)_PANEL_DH_WIDTH;
        g_pucDdcciTxBuf[4] = (BYTE)(_PANEL_DV_HEIGHT / 256);
        g_pucDdcciTxBuf[5] = (BYTE)_PANEL_DV_HEIGHT;
        g_pucDdcciTxBuf[6] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MAX / 256);
        g_pucDdcciTxBuf[7] = (BYTE)_DEVICE_LED_DRIVER_PWM_MAX;
        g_pucDdcciTxBuf[8] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MIN / 256);
        g_pucDdcciTxBuf[9] = (BYTE)_DEVICE_LED_DRIVER_PWM_MIN;
        g_pucDdcciTxBuf[10] = _TOTAL_REGION;
        g_pucDdcciTxBuf[11] = _LD_HDR10_BOOST_SUPPORT;
        g_pucDdcciTxBuf[12] = 0x00;
        g_pucDdcciTxBuf[13] = 0x00;
        g_pucDdcciTxBuf[14] = UserCommonDdcciCalCheckSum();
    }
#else
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_INDEX] == _DDCCI_DISP_DIMMING_TYPE_LOCAL)
    {
        BYTE pucTemp[4];
        memset(pucTemp, 0, sizeof(pucTemp));
        UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_NOTM_BOUND_ADDRESS), 4, pucTemp);
        g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
        g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x0D;
        g_pucDdcciTxBuf[2] = (BYTE)(_PANEL_DH_WIDTH / 256);
        g_pucDdcciTxBuf[3] = (BYTE)_PANEL_DH_WIDTH;
        g_pucDdcciTxBuf[4] = (BYTE)(_PANEL_DV_HEIGHT / 256);
        g_pucDdcciTxBuf[5] = (BYTE)_PANEL_DV_HEIGHT;
        g_pucDdcciTxBuf[6] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MAX / 256);
        g_pucDdcciTxBuf[7] = (BYTE)_DEVICE_LED_DRIVER_PWM_MAX;
        g_pucDdcciTxBuf[8] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MIN / 256);
        g_pucDdcciTxBuf[9] = (BYTE)_DEVICE_LED_DRIVER_PWM_MIN;
        g_pucDdcciTxBuf[10] = _TOTAL_REGION;
        g_pucDdcciTxBuf[11] = _LD_HDR10_BOOST_SUPPORT;
        g_pucDdcciTxBuf[12] = pucTemp[2];
        g_pucDdcciTxBuf[13] = pucTemp[3];
        g_pucDdcciTxBuf[14] = UserCommonDdcciCalCheckSum();
    }
#endif

#endif

#if(_GLOBAL_DIMMING_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_INDEX] == _DDCCI_DISP_DIMMING_TYPE_GLOBAL)
    {
#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
        g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
        g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x09;
        g_pucDdcciTxBuf[2] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MAX / 256);
        g_pucDdcciTxBuf[3] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MAX);
        g_pucDdcciTxBuf[4] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MIN / 256);
        g_pucDdcciTxBuf[5] = (BYTE)(_DEVICE_LED_DRIVER_PWM_MIN);
        g_pucDdcciTxBuf[6] = _HDR10_SUPPORT;
        g_pucDdcciTxBuf[7] = UserCommonDdcciCalCheckSum();
#elif(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
        g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
        g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x09;
        g_pucDdcciTxBuf[2] = (BYTE)(_BACKLIGHT_MAX / 256);
        g_pucDdcciTxBuf[3] = (BYTE)(_BACKLIGHT_MAX);
        g_pucDdcciTxBuf[4] = (BYTE)(_BACKLIGHT_MIN / 256);
        g_pucDdcciTxBuf[5] = (BYTE)(_BACKLIGHT_MIN);
        g_pucDdcciTxBuf[6] = _HDR10_SUPPORT;
        g_pucDdcciTxBuf[7] = UserCommonDdcciCalCheckSum();
#endif
    }
#endif // endif(_GLOBAL_DIMMING_SUPPORT == _ON)
    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    EX1 = 1;
}

//--------------------------------------------------
// Description  : Set scaler PWM value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibSetPWMValue(void)
{
#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
    ScalerColorDDomainDBEnable(_ENABLE);
    ScalerColorDDomainDBTriggerEvent(_DB_VS_TRIGGER);
#endif

#if(_LOCAL_DIMMING_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_INDEX] == _DDCCI_DISP_DIMMING_TYPE_LOCAL)
    {
        BYTE ucI = 0;
        WORD pusPWM[_TOTAL_REGION] = {0};
        for(ucI = 0; ucI < _TOTAL_REGION; ucI++)
        {
            pusPWM[ucI] = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_DATA_START + ucI * 2] << 8) +
                          (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_DATA_START + ucI * 2 + 1]);
        }
        UserCommonLocalDimmingSetPWMValue(pusPWM);
    }
#endif // endif(_LOCAL_DIMMING_SUPPORT == _ON)

#if(_GLOBAL_DIMMING_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_INDEX] == _DDCCI_DISP_DIMMING_TYPE_GLOBAL)
    {
        WORD usPWM = 0;
        usPWM = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_DATA_START] << 8) +
                (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DIMMING_DATA_START + 1]);
        UserCommonGlobalDimmingSetPWMValue(usPWM);
    }
#endif // endif(_Global_DIMMING_SUPPORT == _ON)

#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
    ScalerColorDDomainDBApply(_DB_APPLY_POLLING);
#endif
}

#endif

#endif // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))

#endif // end if #if(_OGC_GEN_TYPE == _OGC_GEN_1)
