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
// ID Code      : UserCommonDisplayCalibrationGen0.c No.0000
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

#if(_OGC_GEN_TYPE == _OGC_GEN_0)  // Gen 0 for 6369

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of OGC/OCC/DICOM
//--------------------------------------------------
#define _OGC_TYPE                   0
#define _OCC_TYPE                   1
#define _DICOM_TYPE                 2
#define _RGB_GAIN_TYPE              3
#define _COLOR_MATRIX_TYPE          4

#define _DISP_CALIB_START           0
#define _DISP_CALIB_PASS            1
#define _DISP_CALIB_ERASE_ERROR     2
#define _DISP_CALIB_FW_ERROR        3
#define _DISP_CALIB_CRC_ERROR       4
#define _DISP_CALIB_FAIL            5
#define _DISP_CALIB_USER_DEFINE     6

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
    _NONE_VALUE,
} EnumOGCTypePos;



//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// Table of OGC/OCC/DICOM
//--------------------------------------------------

BYTE code tOGC_GRAY_TABLE[] =
{
    252, 244, 232,
    216, 196, 172,
    148, 124, 96,
    68, 44, 24,
    12, 6, 2,
    0
};


#if(_OCC_SUPPORT == _ON)
//--------------------------------------------------
// sRGB Table for OCC
//--------------------------------------------------
BYTE code tOCC_SRGB_TABLE[] =
{
    192,  80,  80,
    192, 192,  80,
    96, 192,  96,
    96, 192, 192,
    128, 128, 192,
    192, 128, 192,
    255, 255, 255,
};
#endif

WORD code tGAMMA_INDEX[] =
{
#if(_OGC_SUPPORT == _ON)
    _OGC_GAMMA1_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 1)
    _OGC_GAMMA2_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 2)
    _OGC_GAMMA3_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 3)
    _OGC_GAMMA4_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 4)
    _OGC_GAMMA5_ADDRESS,
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
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
//BYTE xdata DISP_CALIBRATION_FLASH[_DISP_CALIBRATION_TOTAL_SPACE]      _at_ (_OGC_FLASH_PAGE * _FLASH_PAGE_SIZE);
BYTE xdata *g_pucDISP_CALIBRATION_FLASH = _OGC_FLASH_PAGE * _FLASH_PAGE_SIZE;

WORD g_ppusGammaCount[][3] =
{
#if(_OGC_SUPPORT == _ON)
    {387, 387, 387},
#if(_OGC_TOTAL_GAMMA > 1)
    {387, 387, 387},
#if(_OGC_TOTAL_GAMMA > 2)
    {387, 387, 387},
#if(_OGC_TOTAL_GAMMA > 3)
    {387, 387, 387},
#if(_OGC_TOTAL_GAMMA > 4)
    {387, 387, 387},
#endif
#endif
#endif
#endif
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_SUPPORT == _ON)
    {411, 411, 411},
#endif

#if(_OGC_DICOM_SUPPORT == _ON)
    {387, 387, 387},
#endif

};

BYTE g_ucCTGainSavePos;
WORD g_usColorMatrixSavePos;
BYTE g_ucCalibrationType;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonDdcciDispCalibProcess(void);
bit UserCommonDdcciDispCalibOGCStart(void);

#if(_OCC_SUPPORT == _ON)
BYTE UserCommonDdcciDispCalibOCCProcess(BYTE ucStep);
#endif

bit UserCommonDdcciDispCalibInitialCheck(void);
void UserCommonDdcciDispCalibSaveLUT(BYTE ucTotalLength);
BYTE UserCommonDdcciDispCalibCalCheckSum(BYTE ucCheckType);
void UserCommonDdcciDispCalibShowGamma(void);
BYTE UserCommonDdcciDispCalibCheckSum(void);
BYTE UserCommonDdcciDispCalibMatrixCheckSum(BYTE ucCheckType);
void UserCommonDdcciDispCalibReplyResult(BYTE ucType);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Do OGC/OCC/DICOM Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibProcess(void)
{
    BYTE ucCalibrationStep = 0;
#if(_OGC_SUPPORT == _ON)
    BYTE ucGammaIndex = 0;
    BYTE ucColorTempIndex = 0;
    WORD pusBriTemp[3] = {0x80, 0x80, 0x80};
#endif
    BYTE ucFlag = 1;

    EX1 = 0;

    ucCalibrationStep = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_STEP];

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
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_GET_USER_DEFINE)
        {
            UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_USER_DEFINE);
            ScalerMcuDdcciReleaseScl();
            return;
        }
        /////////////////////////////////////////////////////////////////
        /////////////////////END            /////////////////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_END)
        {
            UserInterfaceAdjustAfterDisplayCalibration(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_END_TYPE]);
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE START/////////////////
        //////////////DISPLAY CALIBRATION: MEASURE RED///////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_RED)
        {
            ucFlag = UserCommonDdcciDispCalibOGCStart();
            ScalerDDomainBackgroundEnable(_ENABLE);
            ScalerDDomainBackgroundSetColor(255, 0, 0);
            g_usColorMatrixSavePos = 0;
            g_ucCTGainSavePos = 0;
            ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE);
        }
        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE BLACK/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_BLACK)
        {
            ScalerDDomainBackgroundSetColor(0, 0, 0);
            if(_DISP_CALIBRATION_TOTAL_SPACE > _FLASH_PAGE_SIZE)
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 1);
            }
        }
        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE BLUE//////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_BLUE)
        {
            ScalerDDomainBackgroundSetColor(0, 0, 255);

            if(_DISP_CALIBRATION_TOTAL_SPACE > 2 * _FLASH_PAGE_SIZE)
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 2);
            }
        }
        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE GREEN/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GREEN)
        {
            ScalerDDomainBackgroundSetColor(0, 255, 0);
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE WHITE/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_WHITE)
        {
            ScalerDDomainBackgroundSetColor(255, 255, 255);
        }

        /////////////////////////////////////////////////////////////////
        ////////////DISPLAY CALIBRATION: MEASURE GRAY1 / GRAY2///////////
        /////////////////////Save RGB CT gains///////////////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1)
        {
            if(g_ucCTGainSavePos == 0)
            {
                ScalerDDomainBackgroundSetColor(tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);
            }

            /************** Save RGB Gain to Flash***********************/
            /* CT/Gamma   Gamma1     Gamma2    Gamma3   Gamma4   Gamma5 */
            /*    CT1     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B  */
            /*    CT2     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B  */
            /*    CT3     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B  */
            /*    CT4     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B  */
            /*    CT5     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B  */
            /*    User    R/G/B      R/G/B     R/G/B    R/G/B    R/G/B  */

#if(_OGC_SUPPORT == _ON)
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_ADDRESS + g_ucCTGainSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
            g_ucCTGainSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY2)
        {
            ScalerDDomainBackgroundSetColor(tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1], tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1], tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);
        }

        /////////////////////////////////////////////////////////////////
        ////////////DISPLAY CALIBRATION: MEASURE GRAY3 ~ GRAY15//////////
        //////////////////////////SAVE LUT///////////////////////////////
        /////////////////////////////////////////////////////////////////
        else if((ucCalibrationStep >= _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY3) && (ucCalibrationStep <= _DDCCI_DISP_CALIB_OGC_MEASURE_LAST_GRAY))
        {
            if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_LENGTH] == 2) && (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_ID] == 0xFF))
            {
                ScalerDDomainBackgroundSetColor(tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1], tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1], tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);
            }
            else
            {
                UserCommonDdcciDispCalibSaveLUT((g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) + 2);
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
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_HDR_BACKLIGHT)
        {
            UserInterfaceAdjustBacklight(0xFF);
        }

        /////////////////////////////////////////////////////////////////
        ////////////////////////OCC PROCESS//////////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OCC_SUPPORT == _ON)
        if(((g_ucCalibrationType >> _OCC_TYPE) & 0x01) == _TRUE)
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
            ScalerDDomainPatternGenAdjustColor(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED], g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN], g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE]);
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
            ScalerColorOutputGammaAdjust(&g_pucDISP_CALIBRATION_FLASH[tGAMMA_INDEX[ucGammaIndex]], _OGC_FLASH_BANK);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);

            ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusBriTemp);
            ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_B, pusBriTemp);

            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 3 + ucGammaIndex * 3), 3, pData);
            pData[5] = pData[2];
            pData[3] = pData[1];
            pData[1] = pData[0];
            pData[0] = 0;
            pData[2] = 0;
            pData[4] = 0;
            ScalerColorContrastAdjust(_CONTRAST_COEF_A, (WORD *)pData);
            ScalerColorContrastAdjust(_CONTRAST_COEF_B, (WORD *)pData);
            ScalerColorContrastEnable(_FUNCTION_ON);

#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

            ScalerColorSRGBEnable(_FUNCTION_OFF);
        }
#endif  // End of #if(_OGC_SUPPORT == _ON)

        /////////////////////////////////////////////////////////////////
        ////////////////////////SET PCM PROCESS//////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OCC_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_PCM)
        {
            // Set PCM Input Gamma
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
            ScalerColorPCMInputGammaLoadTable(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN]);

            // Set PCM Output Gamma
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);
            ScalerColorPCMOutputGammaAdjust(&g_pucDISP_CALIBRATION_FLASH[_OCC_GAMMA10_ADDRESS], _OGC_FLASH_BANK);

            // Set PCM Color Matrix
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, &g_pucDISP_CALIBRATION_FLASH[_OCC_SRGBMATRIX_ADDRESS], _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, &g_pucDISP_CALIBRATION_FLASH[_OCC_ADOBEMATRIX_ADDRESS], _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_MODE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, &g_pucDISP_CALIBRATION_FLASH[_OCC_USERDEFINE_ADDRESS], _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }

            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            ScalerColorSRGBEnable(_FUNCTION_ON);

            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);
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
            ScalerColorOutputGammaAdjust(&g_pucDISP_CALIBRATION_FLASH[_OGC_DICOM_ADDRESS], _OGC_FLASH_BANK);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);

#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

            ScalerColorSRGBEnable(_FUNCTION_OFF);
        }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)


        /////////////////////////////////////////////////////////////////
        ///////////////////////VERIFICATION END//////////////////////////
        /////////////////////////////////////////////////////////////////
        else if((ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_VERIFY_END) || (ucCalibrationStep == _DDCCI_DISP_CALIB_OCC_VERIFY_END))
        {
            ScalerDDomainPatternGenEnable(_DISABLE);
            ScalerDDomainPatternGenAdjustColor(0, 0, 0);
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
                if((ucCalibrationStep >= _DDCCI_DISP_CALIB_OGC_MEASURE_BLACK) && (ucCalibrationStep <= _DDCCI_DISP_CALIB_OGC_MEASURE_GREEN))
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

    // Get Counter Start
#if(_OGC_SUPPORT == _ON)
    for(ucCnt = 0; ucCnt < _OGC_TOTAL_GAMMA; ucCnt++)
    {
        g_ppusGammaCount[ucCnt][0] = 387;
        g_ppusGammaCount[ucCnt][1] = 387;
        g_ppusGammaCount[ucCnt][2] = 387;
    }
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_SUPPORT == _ON)
    g_ppusGammaCount[ucCnt][0] = 411;
    g_ppusGammaCount[ucCnt][1] = 411;
    g_ppusGammaCount[ucCnt][2] = 411;
    ucCnt++;
#endif  // End of #if(_OCC_SUPPORT == _ON)

#if(_OGC_DICOM_SUPPORT == _ON)
    g_ppusGammaCount[ucCnt][0] = 387;
    g_ppusGammaCount[ucCnt][1] = 387;
    g_ppusGammaCount[ucCnt][2] = 387;
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)

    // Get Counter End
    g_ucCalibrationType = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

#if(_OGC_SUPPORT == _OFF)
    if(((g_ucCalibrationType >> _OGC_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OGC_SUPPORT == _OFF)

#if(_OCC_SUPPORT == _OFF)
    if(((g_ucCalibrationType >> _OCC_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OCC_SUPPORT == _OFF)

#if(_OGC_DICOM_SUPPORT == _OFF)
    if(((g_ucCalibrationType >> _DICOM_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _OFF)

    if(((g_ucCalibrationType >> (_DICOM_TYPE + 1)) & 0x07) != _OGC_TOTAL_GAMMA)
    {
        ucFlag = 0;
    }


#if(_OCC_SUPPORT == _ON)
    if(((g_ucCalibrationType >> _OCC_TYPE) & _BIT0) == _TRUE)
    {
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
        ScalerColorPCMInputGammaLoadTable(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_COLORSPACE]);
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
        ScalerDDomainPatternGenEnable(_ENABLE);
        ScalerDDomainPatternGenAdjustColor(tOCC_SRGB_TABLE[0], tOCC_SRGB_TABLE[1], tOCC_SRGB_TABLE[2]);
    }
    else
#endif  // End of #if(_OCC_SUPPORT == _ON)
    {

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
        ScalerDDomainPatternGenEnable(_DISABLE);
#endif
    }

    ScalerColorSRGBEnable(_FUNCTION_OFF);
    ScalerColorBrightnessEnable(_FUNCTION_OFF);
    ScalerColorContrastEnable(_FUNCTION_OFF);

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

    if((ucStep >= _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1) && (ucStep < _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB7))
    {
        ScalerDDomainPatternGenAdjustColor(tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3],
                                           tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3 + 1],
                                           tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3 + 2]);
    }
    else if(ucStep == _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB7)
    {
        UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_SRGBMATRIX_ADDRESS + g_usColorMatrixSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_MATRIX]);
        g_usColorMatrixSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;

        // Set PCM Color Matrix
        if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
        {
            ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, &g_pucDISP_CALIBRATION_FLASH[_OCC_SRGBMATRIX_ADDRESS], _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
        {
            ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, &g_pucDISP_CALIBRATION_FLASH[_OCC_ADOBEMATRIX_ADDRESS], _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_MODE)
        {
            ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, &g_pucDISP_CALIBRATION_FLASH[_OCC_USERDEFINE_ADDRESS], _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }

        ScalerColorSRGBEnable(_FUNCTION_ON);

        // Disable Display Pattern Gen. & set (0,0,0)
        ScalerDDomainPatternGenEnable(_DISABLE);
        ScalerDDomainPatternGenAdjustColor(0, 0, 0);
    }

    return ucFlag;
}
#endif // End of #if(_OCC_SUPPORT == _ON)

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
// Description  : Save LUT Data from DDCCI Rx
// Input Value  : nAddress: address in DISP_CALIBRATION_FLASH;
//                nLength: Data Length
//                ucBuffer: pointer of databuffer
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibSaveLUT(BYTE ucTotalLength)
{
    BYTE ucLUTLength = 0;
    BYTE ucPointer = _DDCCI_DISP_CALIB_LUT_LENGTH;
    BYTE ucGammaIndex = 0;
    BYTE ucRGB = 0;
    WORD usStartAddr = _OGC_GAMMA1_ADDRESS;

    // ucTotalLength - 1: exclude checksum
    while(ucPointer < (ucTotalLength - 1))
    {
        // LUT Length (exclude ID and Length Bytes)
        ucLUTLength = g_pucDdcciRxBuf[ucPointer] - 2;

        ucGammaIndex = (g_pucDdcciRxBuf[ucPointer + 1] >> 4) & 0x0F;
        ucRGB = g_pucDdcciRxBuf[ucPointer + 1] & 0x0F;

        ucPointer += 2;

#if(_OCC_SUPPORT == _ON)
        if(ucGammaIndex == _OCC_POSITION)
        {
            usStartAddr = tGAMMA_INDEX[_OCC_POSITION] + (WORD)(ucRGB) * 411;
        }
        else
#endif

        {
            usStartAddr = tGAMMA_INDEX[ucGammaIndex] + (WORD)(ucRGB) * 387;
        }

        UserCommonFlashWrite(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + (usStartAddr + g_ppusGammaCount[ucGammaIndex][ucRGB] - ucLUTLength), ucLUTLength, &g_pucDdcciRxBuf[ucPointer]);
        g_ppusGammaCount[ucGammaIndex][ucRGB] = g_ppusGammaCount[ucGammaIndex][ucRGB] - ucLUTLength;

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

    if(_OGC_FLASH_BANK < MCU_FFFD_XDATA_BANK_START)
    {
        return _FALSE;
    }

    pData[1] = MCU_FFFE_XDATA_BANK_SEL;
    MCU_FFFE_XDATA_BANK_SEL = _OGC_FLASH_BANK - MCU_FFFD_XDATA_BANK_START;

    pData[0] = 0;

    switch(ucCheckType)
    {
        case _OGC_TYPE:

            for(usI = 0; usI < 3 * 387; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_GAMMA1_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

#if(_OGC_TOTAL_GAMMA == 1)
            MCU_FFFE_XDATA_BANK_SEL = pData[1];
            return pData[0];
#endif

            for(usI = 0; usI < 3 * 387; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_GAMMA2_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }
#if(_OGC_TOTAL_GAMMA == 2)
            MCU_FFFE_XDATA_BANK_SEL = pData[1];
            return pData[0];
#endif
            for(usI = 0; usI < 3 * 387; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_GAMMA3_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

#if(_OGC_TOTAL_GAMMA == 3)
            MCU_FFFE_XDATA_BANK_SEL = pData[1];
            return pData[0];
#endif

            for(usI = 0; usI < 3 * 387; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_GAMMA4_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }
#if(_OGC_TOTAL_GAMMA == 4)
            MCU_FFFE_XDATA_BANK_SEL = pData[1];
            return pData[0];
#endif

            for(usI = 0; usI < 3 * 387; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_GAMMA5_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

#if(_OGC_TOTAL_GAMMA == 5)
            MCU_FFFE_XDATA_BANK_SEL = pData[1];
            return pData[0];
#endif
            break;

        case _OCC_TYPE:

            for(usI = 0; usI < 411 * 3; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_GAMMA10_ADDRESS + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

        case _DICOM_TYPE:

            for(usI = 0; usI < 387 * 3; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_DICOM_ADDRESS + usI), 2, pData + 2);
                pData[0] += pData[2];
            }

            break;

        case _RGB_GAIN_TYPE:

            for(usI = _OGC_RGB_GAIN_ADDRESS; usI < (_OGC_RGB_GAIN_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_TYPE:

            for(usI = _OCC_SRGBMATRIX_ADDRESS; usI < (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * 3); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

        default:

            break;
    }

    MCU_FFFE_XDATA_BANK_SEL = pData[1];

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
    WORD pusBriTemp[3] = {0x80, 0x80, 0x80};
#endif

    ScalerColorOutputGammaEnable(_FUNCTION_OFF);

#if(_OGC_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE] == _OGC_TYPE)
    {
        ucGammaIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_GAMMA_CT_INFO] >> 4) & 0x0F;
        ucColorTempIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_GAMMA_CT_INFO] & 0x0F;

        ScalerColorOutputGammaAdjust(&g_pucDISP_CALIBRATION_FLASH[tGAMMA_INDEX[ucGammaIndex]], _OGC_FLASH_BANK);

        ScalerColorBrightnessAdjust(_BRIGHTNESS_COEF_A, pusBriTemp);

        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 3 + ucGammaIndex * 3), 3, pData);
        pData[5] = pData[2];
        pData[3] = pData[1];
        pData[1] = pData[0];
        pData[0] = 0;
        pData[2] = 0;
        pData[4] = 0;
        ScalerColorContrastAdjust(_CONTRAST_COEF_A, (WORD *)pData);

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif
    }
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE] == _OCC_TYPE)
    {
        ScalerColorPCMOutputGammaAdjust(&g_pucDISP_CALIBRATION_FLASH[_OCC_GAMMA10_ADDRESS], _OGC_FLASH_BANK);

        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

        ScalerColorBrightnessEnable(_FUNCTION_OFF);
        ScalerColorContrastEnable(_FUNCTION_OFF);

        ScalerColorSRGBEnable(_FUNCTION_OFF);
    }
#endif  // End of #if(_OCC_SUPPORT == _ON)

#if(_OGC_DICOM_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE] == _DICOM_TYPE)
    {
        ScalerColorOutputGammaAdjust(&g_pucDISP_CALIBRATION_FLASH[_OGC_DICOM_ADDRESS], _OGC_FLASH_BANK);

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

        ScalerColorBrightnessEnable(_FUNCTION_OFF);
        ScalerColorContrastEnable(_FUNCTION_OFF);

        ScalerColorSRGBEnable(_FUNCTION_OFF);
    }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)

    ScalerColorOutputGammaEnable(_FUNCTION_ON);

    ScalerDDomainBackgroundEnable(_DISABLE);
    ScalerDDomainBackgroundSetColor(0, 0, 0);
}

//--------------------------------------------------
// Description  : Display Calibration Measure End CheckSum
// Input Value  : None
// Output Value : _SUCCESS/_FAIL
//--------------------------------------------------
BYTE UserCommonDdcciDispCalibCheckSum(void)
{
    BYTE ucFlag = 1;

#if(_OGC_SUPPORT == _ON)
    if(((g_ucCalibrationType >> _OGC_TYPE) & 0x01) == _TRUE)
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
    if(((g_ucCalibrationType >> _OCC_TYPE) & 0x01) == _TRUE)
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
#endif  // End of #if(_OCC_SUPPORT == _ON)

#if(_OGC_DICOM_SUPPORT == _ON)
    if(((g_ucCalibrationType >> _DICOM_TYPE) & 0x01) == _TRUE)
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
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)

    return ucFlag;
}

//--------------------------------------------------
// Description  : Display Calibration OCC Measure End Matrix CheckSum
// Input Value  : ucCheckType: 3-RGB gain,4- color matrix
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
            break;

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
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_OGCOCCDICOM_SUPPORT] = (_OGC_DICOM_SUPPORT << 2) | (_OCC_SUPPORT << 1) | (_OGC_SUPPORT);
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_OGC_TOTAL_GAMMA] = _OGC_TOTAL_GAMMA;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_OGC_TOTAL_CT] = _OGC_TOTAL_CT;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_BITNUM] = ((_SRGB_PRECISION_9BIT << 4) | _PANEL_DISP_BIT_MODE);
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_BITNUM + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_USER_DEFINE:

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_USER_DEFINE_TYPE] == _DDCCI_DISP_CALIB_USER_DDCCI_LENGTH)
            {
                g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = _DDCCI_RXBUF_LENGTH;
                g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 0x00;
                g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 0x00;
                g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 0x00;
            }

            break;

        case _DISP_CALIB_PASS:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'P';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'A';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'S';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'S';

            break;

        case _DISP_CALIB_ERASE_ERROR:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'E';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'R';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'A';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'S';

            break;

        case _DISP_CALIB_FW_ERROR:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'F';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'W';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'E';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = g_ucCalibrationType;

            break;

        case _DISP_CALIB_CRC_ERROR:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'C';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'R';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'C';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'E';

            break;

        case _DISP_CALIB_FAIL:

        default:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'F';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'A';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'I';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'L';

            break;
    }

    g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);

    EX1 = 1;
}
#endif // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))

#endif // end if #if(_OGC_GEN_TYPE == _OGC_GEN_0)
