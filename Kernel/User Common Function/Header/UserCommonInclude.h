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
// ID Code      : UserCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "Global.h"
#include "Project.h"
#include "ScalerCommonFunctionInterface.h"

#if(_TRANSLATOR_SUPPORT == _OFF)
#include "ScalerFunctionInterface.h"
#else
#include "TranslatorFunctionInterface.h"
#endif

#include "SysInterface.h"
#include "UserCommonDdcciDefine.h"
#include "UserCommonHDRInclude.h"
#include "UserCommonLocalDimmingInclude.h"
#include "UserCommonGlobalDimmingInclude.h"
#include "UserCommonSeamlessChgInclude.h"
#include "UserCommonSignDdcciDefine.h"
#include "UserCommonSignParamDefine.h"
#include "ScalerCommonRegCommonInclude.h"
#include "UserCommonDataExchangeInclude.h"

#include _USER_FUNCTION_INCLUDE
#include _OSD_INCLUDE
#include _FACTORY_INCLUDE

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Eeprom Page address
//--------------------------------------------------
#define _EEPROM_PAGE0_BANK0                            0
#define _EEPROM_PAGE0_BANK1                            128
#define _EEPROM_PAGE1_BANK0                            256
#define _EEPROM_PAGE1_BANK1                            384
#define _EEPROM_PAGE2_BANK0                            512
#define _EEPROM_PAGE2_BANK1                            640
#define _EEPROM_PAGE3_BANK0                            768
#define _EEPROM_PAGE3_BANK1                            896
#define _EEPROM_PAGE4_BANK0                            1024
#define _EEPROM_PAGE4_BANK1                            1152
#define _EEPROM_PAGE5_BANK0                            1280
#define _EEPROM_PAGE5_BANK1                            1408
#define _EEPROM_PAGE6_BANK0                            1536
#define _EEPROM_PAGE6_BANK1                            1664
#define _EEPROM_PAGE7_BANK0                            1792
#define _EEPROM_PAGE7_BANK1                            1920
#define _EEPROM_PAGE8_BANK0                            2048
#define _EEPROM_PAGE8_BANK1                            2176
#define _EEPROM_PAGE9_BANK0                            2304
#define _EEPROM_PAGE9_BANK1                            2432
#define _EEPROM_PAGEA_BANK0                            2560
#define _EEPROM_PAGEA_BANK1                            2688
#define _EEPROM_PAGEB_BANK0                            2816
#define _EEPROM_PAGEB_BANK1                            2944
#define _EEPROM_PAGEC_BANK0                            3072
#define _EEPROM_PAGEC_BANK1                            3200
#define _EEPROM_PAGED_BANK0                            3328
#define _EEPROM_PAGED_BANK1                            3456
#define _EEPROM_PAGEE_BANK0                            3584
#define _EEPROM_PAGEE_BANK1                            3712
#define _EEPROM_PAGEF_BANK0                            3840
#define _EEPROM_PAGEF_BANK1                            3968
#define _EEPROM_PAGE10_BANK0                           4096
#define _EEPROM_PAGE10_BANK1                           4224
#define _EEPROM_PAGE11_BANK0                           4352
#define _EEPROM_PAGE11_BANK1                           4480
#define _EEPROM_PAGE12_BANK0                           4608
#define _EEPROM_PAGE12_BANK1                           4736
#define _EEPROM_PAGE13_BANK0                           4864
#define _EEPROM_PAGE13_BANK1                           4992
#define _EEPROM_PAGE14_BANK0                           5120
#define _EEPROM_PAGE14_BANK1                           5248
#define _EEPROM_PAGE15_BANK0                           5376
#define _EEPROM_PAGE15_BANK1                           5504
#define _EEPROM_PAGE16_BANK0                           5632
#define _EEPROM_PAGE16_BANK1                           5760
#define _EEPROM_PAGE17_BANK0                           5888
#define _EEPROM_PAGE17_BANK1                           6016
#define _EEPROM_PAGE18_BANK0                           6144
#define _EEPROM_PAGE18_BANK1                           6272
#define _EEPROM_PAGE19_BANK0                           6400
#define _EEPROM_PAGE19_BANK1                           6528
#define _EEPROM_PAGE1A_BANK0                           6656
#define _EEPROM_PAGE1A_BANK1                           6784
#define _EEPROM_PAGE1B_BANK0                           6912
#define _EEPROM_PAGE1B_BANK1                           7040
#define _EEPROM_PAGE1C_BANK0                           7168
#define _EEPROM_PAGE1C_BANK1                           7296
#define _EEPROM_PAGE1D_BANK0                           7424
#define _EEPROM_PAGE1D_BANK1                           7552
#define _EEPROM_PAGE1E_BANK0                           7680
#define _EEPROM_PAGE1E_BANK1                           7808
#define _EEPROM_PAGE1F_BANK0                           7936
#define _EEPROM_PAGE1F_BANK1                           8064

//---------------------------------------------------------------------------------------------------------------------------------------

#define _EEPROM_CHECKSUM_ADDRESS                       (_EEPROM_KERNEL_START_ADDRESS)
#define _EEPROM_VERSION_CODE_ADDRESS                   (_EEPROM_CHECKSUM_ADDRESS + 1)
#define _ADC_SETTING_ADDRESS                           (_EEPROM_VERSION_CODE_ADDRESS + 1)
#define _SYSTEM_DATA_ADDRESS                           (_ADC_SETTING_ADDRESS + sizeof(StructAdcDataType) * (_VGA_SUPPORT + _YPBPR_SUPPORT))
#define _SYSTEM_DATA_ADDRESS_END                       (_SYSTEM_DATA_ADDRESS + sizeof(StructSystemDataType))
//---------------------------------------------------------------------------------------------------------------------------------------

#define _MODE_USER_DATA_ADDRESS                        (_SYSTEM_DATA_ADDRESS_END)
#define _VGA_MODE_DATA_ADDRESS_END                     (_MODE_USER_DATA_ADDRESS + sizeof(StructVGAModeUserDataType) * _MODE_SLOT_AMOUNT * _VGA_SUPPORT)
//---------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Flash Page information
//--------------------------------------------------
#define _OCC_LUT_MODE                                  _OFF

#define _EDID_TABLE_FLASH_PAGE                         (_EDID_ADDRESS_FLASH / _FLASH_PAGE_SIZE)
#define _RX_HDCP_1_4_TABLE_FLASH_PAGE                  (_RX_HDCP_1_4_KEY_ADDRESS_FLASH / _FLASH_PAGE_SIZE)
#define _RX_HDCP_2_2_TABLE_FLASH_PAGE                  (_RX_HDCP_2_2_KEY_ADDRESS_FLASH / _FLASH_PAGE_SIZE)
#define _TX_HDCP_1_4_TABLE_FLASH_PAGE                  (_TX_HDCP_1_4_KEY_ADDRESS_FLASH / _FLASH_PAGE_SIZE)
#define _TX_HDCP_2_2_TABLE_FLASH_PAGE                  (_TX_HDCP_2_2_KEY_ADDRESS_FLASH / _FLASH_PAGE_SIZE)

//--------------------------------------------------
// Address for OGC/OCC/DICOM
//--------------------------------------------------
#if(_OGC_GEN_TYPE == _OGC_GEN_1)
#define _OGC_RGB_GAIN_TOTAL_SPACE                      (_OGC_TOTAL_CT > 6 ? 0x200 : 0x100)
#define _PANEL_EDID_TOTAL_SPACE                        0x10
#define _OGC_HDR10_NOTM_BOUND_TOTAL_SPACE              0x10 // LB_MSB, LB_LSB, UB_MSB, UB_LSB, PanelMaxLV_EDID_CV
#define _OGC_GAMMA_TABLE_SIZE                          0x1810UL // 2052 * 3 = 0x180C
#define _OCC_GAMMA_TABLE_SIZE                          0x19D0UL // 2200*3 = 0x19C8
#define _OGC_RGB_GAIN_ACTUAL_SIZE                      (_OGC_TOTAL_GAMMA * _OGC_TOTAL_CT * 6)
#define _OGC_HDR10_IG_TABLE_SIZE                       0xC5
#define _OCC_HDR10_COLOR_MATRIX_SIZE                   0x50
#define _OGC_HDR10_NOTM_DCR_THD_SIZE                   0x10
#define _CHECKSUM_TOTAL_SPACE                          0x50
#define _OCC_PANEL_COLOR_MAPPING_DATA_LENGTH           0x10

#define _OCC_COLOR_MATRIX_TOTAL_SPACE                  0x100UL // sRGB/Adobe/SoftProof/Userdefine/EBU/Rec709/DCI-P3/SMPTC/Userdefine2/Userdefine3/Userdefine4/Userdefine5/Userdefine6/DisplayP3
#define _OCC_COLORMATRIX_TABLE_SIZE                    (_OCC_LUT_MODE == _ON ? 312 : 18)
#define _FREESYNC_II_COLORMATRIX_TABLE_TOTAL_SIZE      0x20
#define _OGC_HEADER_LENGTH                             (4 + (_OGC_TOTAL_GAMMA + 1 + _OGC_TOTAL_CT + 1))
#define _OCC_HEADER_LENGTH                             5
#define _DICOM_HEADER_LENGTH                           5
#define _WHITE_LV_HEADER_LENGTH                        5
#define _OGCOCC_LV_RARIO_LENGTH                        ((_OGC_TOTAL_CT + 5) * 2)

#define _OGC_RGB_GAIN_ADDRESS                          0
#define _OGC_RGB_GAIN_MAX_BRI_ADDRESS                  (_OGC_RGB_GAIN_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE)
#define _OGC_HEADER_ADDRESS                            (_OGC_RGB_GAIN_MAX_BRI_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_HEADER_ADDRESS                            (_OGC_HEADER_ADDRESS + _OGC_HEADER_LENGTH)
#define _DICOM_HEADER_ADDRESS                          (_OCC_HEADER_ADDRESS + _OCC_HEADER_LENGTH)
#define _WHITE_LV_HEADER_ADDRESS                       (_DICOM_HEADER_ADDRESS + _DICOM_HEADER_LENGTH)
#define _EDID_INFO_ADDRESS                             (_OGC_RGB_GAIN_MAX_BRI_ADDRESS + _OGC_RGB_GAIN_TOTAL_SPACE)
#define _DIMMING_NOTM_DCR_THD_ADDRESS                  (_EDID_INFO_ADDRESS + _PANEL_EDID_TOTAL_SPACE)
#define _OCC_PANEL_COLOR_MAPPING_DATA_ADDRESS          (_DIMMING_NOTM_DCR_THD_ADDRESS + _OGC_HDR10_NOTM_DCR_THD_SIZE)
#define _OGCOCC_LV_RARIO_ADDRESS                       (_OCC_PANEL_COLOR_MAPPING_DATA_ADDRESS + _OCC_PANEL_COLOR_MAPPING_DATA_LENGTH)
#define _CHECKSUM_START_ADDRESS                        (_OGCOCC_LV_RARIO_ADDRESS + _OGCOCC_LV_RARIO_LENGTH)

#define _OCC_SRGBMATRIX_ADDRESS                        (_OGC_TOTAL_CT > 6 ? 0x500 : 0x400)
#define _OCC_ADOBEMATRIX_ADDRESS                       (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_USERDEFINE_ADDRESS                        (_OCC_ADOBEMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_EBU_ADDRESS                               (_OCC_USERDEFINE_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_SOFTPROOF_ADDRESS                         (_OCC_USERDEFINE_ADDRESS)
#define _OCC_REC709_ADDRESS                            (_OCC_EBU_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_DCIP3_ADDRESS                             (_OCC_REC709_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_SMPTEC_ADDRESS                            (_OCC_DCIP3_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_USERDEFINE2_ADDRESS                       (_OCC_SMPTEC_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_USERDEFINE3_ADDRESS                       (_OCC_USERDEFINE2_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_USERDEFINE4_ADDRESS                       (_OCC_USERDEFINE3_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_USERDEFINE5_ADDRESS                       (_OCC_USERDEFINE4_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_USERDEFINE6_ADDRESS                       (_OCC_USERDEFINE5_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_DISPLAYP3_ADDRESS                         (_OCC_USERDEFINE6_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_IPANEL_ADDRESS                            (_OCC_DISPLAYP3_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)

#define _OCC_SRGBMATRIX_MAX_BRI_ADDRESS                (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLOR_MATRIX_TOTAL_SPACE * _OCC_SUPPORT)
#define _OCC_ADOBEMATRIX_MAX_BRI_ADDRESS               (_OCC_SRGBMATRIX_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_USERDEFINE_MAX_BRI_ADDRESS                (_OCC_ADOBEMATRIX_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_EBU_MAX_BRI_ADDRESS                       (_OCC_USERDEFINE_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_SOFTPROOF_MAX_BRI_ADDRESS                 (_OCC_USERDEFINE_MAX_BRI_ADDRESS)
#define _OCC_REC709_MAX_BRI_ADDRESS                    (_OCC_EBU_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_DCIP3_MAX_BRI_ADDRESS                     (_OCC_REC709_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_SMPTEC_MAX_BRI_ADDRESS                    (_OCC_DCIP3_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_USERDEFINE2_MAX_BRI_ADDRESS               (_OCC_SMPTEC_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_USERDEFINE3_MAX_BRI_ADDRESS               (_OCC_USERDEFINE2_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_USERDEFINE4_MAX_BRI_ADDRESS               (_OCC_USERDEFINE3_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_USERDEFINE5_MAX_BRI_ADDRESS               (_OCC_USERDEFINE4_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_USERDEFINE6_MAX_BRI_ADDRESS               (_OCC_USERDEFINE5_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_DISPLAYP3_MAX_BRI_ADDRESS                 (_OCC_USERDEFINE6_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_IPANEL_MAX_BRI_ADDRESS                    (_OCC_DISPLAYP3_MAX_BRI_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))

#define _OCC_HDR10_SRGB_MATRIX_ADDRESS                 (_OCC_SRGBMATRIX_MAX_BRI_ADDRESS + _OCC_COLOR_MATRIX_TOTAL_SPACE * _OCC_SUPPORT * (_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR ? 1 : 0))
#define _OCC_HDR10_ADOBE_MATRIX_ADDRESS                (_OCC_HDR10_SRGB_MATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _HDR10_SUPPORT)
#define _OCC_HDR10_DCIP3_D65_MATRIX_ADDRESS            (_OCC_HDR10_ADOBE_MATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _HDR10_SUPPORT)
#define _OCC_HDR10_BT2020_MATRIX_ADDRESS               (_OCC_HDR10_DCIP3_D65_MATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _HDR10_SUPPORT)

#define _OGC_HDR10_IG_1200_NOR_ADDRESS                 (_OCC_HDR10_SRGB_MATRIX_ADDRESS + _OCC_HDR10_COLOR_MATRIX_SIZE * _HDR10_SUPPORT)
#define _OGC_HDR10_IG_1200_DARK_ADDRESS                (_OGC_HDR10_IG_1200_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)
#define _OGC_HDR10_IG_4000_NOR_ADDRESS                 (_OGC_HDR10_IG_1200_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)
#define _OGC_HDR10_IG_4000_DARK_ADDRESS                (_OGC_HDR10_IG_4000_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)
#define _OGC_HDR10_IG_10000_NOR_ADDRESS                (_OGC_HDR10_IG_4000_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)
#define _OGC_HDR10_IG_10000_DARK_ADDRESS               (_OGC_HDR10_IG_10000_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)
#define _OGC_HDR10_IG_540_NOR_ADDRESS                  (_OGC_HDR10_IG_10000_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)
#define _OGC_HDR10_IG_540_DARK_ADDRESS                 (_OGC_HDR10_IG_540_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)

#define _OGC_HDR10_IG_NOTM_NOR_ADDRESS                 (_OGC_HDR10_IG_540_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)
#define _OGC_HDR10_IG_NOTM_DARK_ADDRESS                (_OGC_HDR10_IG_NOTM_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)
#define _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS            (_OGC_HDR10_IG_NOTM_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)
#define _OGC_HDR10_IG_NOTM_PEAK_DARK_ADDRESS           (_OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)

#define _OGC_HDR10_IG_540_FIXED_POINT_NOR_ADDRESS      (_OGC_HDR10_IG_NOTM_PEAK_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT)
#define _OGC_HDR10_IG_540_FIXED_POINT_DARK_ADDRESS     (_OGC_HDR10_IG_540_FIXED_POINT_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT)
#define _OGC_HDR10_IG_1200_FIXED_POINT_NOR_ADDRESS     (_OGC_HDR10_IG_540_FIXED_POINT_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT)
#define _OGC_HDR10_IG_1200_FIXED_POINT_DARK_ADDRESS    (_OGC_HDR10_IG_1200_FIXED_POINT_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT)
#define _OGC_HDR10_IG_4000_FIXED_POINT_NOR_ADDRESS     (_OGC_HDR10_IG_1200_FIXED_POINT_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT)
#define _OGC_HDR10_IG_4000_FIXED_POINT_DARK_ADDRESS    (_OGC_HDR10_IG_4000_FIXED_POINT_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT)
#define _OGC_HDR10_IG_10000_FIXED_POINT_NOR_ADDRESS    (_OGC_HDR10_IG_4000_FIXED_POINT_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT)
#define _OGC_HDR10_IG_10000_FIXED_POINT_DARK_ADDRESS   (_OGC_HDR10_IG_10000_FIXED_POINT_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT)
#define _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS   (_OGC_HDR10_IG_10000_FIXED_POINT_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT)
#define _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_DARK_ADDRESS  (_OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT)
#define _OGC_HDR10_IG_NOTM_DISPLAY_HDR_1_1_ADDRESS     (_OGC_HDR10_IG_NOTM_USER_DEF_PEAK_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT)
#define _OGC_HDR10_NOTM_BOUND_ADDRESS                  (_OGC_HDR10_IG_NOTM_DISPLAY_HDR_1_1_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _HDR10_SUPPORT * (_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1 ? 1 : 0))

#define _DIMMING_OGC_GAMMA1_ADDRESS                    (_OGC_HDR10_NOTM_BOUND_ADDRESS + _OGC_HDR10_NOTM_BOUND_TOTAL_SPACE * _HDR10_SUPPORT)
#define _DIMMING_OGC_GAMMA2_ADDRESS                    (_DIMMING_OGC_GAMMA1_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _BACKLIGHT_DIMMING_SUPPORT * (_OGC_TOTAL_GAMMA > 1 ? 1 : 0))
#define _DIMMING_OGC_GAMMA3_ADDRESS                    (_DIMMING_OGC_GAMMA2_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _BACKLIGHT_DIMMING_SUPPORT * (_OGC_TOTAL_GAMMA > 2 ? 1 : 0))
#define _DIMMING_OGC_GAMMA4_ADDRESS                    (_DIMMING_OGC_GAMMA3_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _BACKLIGHT_DIMMING_SUPPORT * (_OGC_TOTAL_GAMMA > 3 ? 1 : 0))
#define _DIMMING_OGC_GAMMA5_ADDRESS                    (_DIMMING_OGC_GAMMA4_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _BACKLIGHT_DIMMING_SUPPORT * (_OGC_TOTAL_GAMMA > 4 ? 1 : 0))
#define _DIMMING_OGC_GAMMA6_ADDRESS                    (_DIMMING_OGC_GAMMA5_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _BACKLIGHT_DIMMING_SUPPORT * (_OGC_TOTAL_GAMMA > 5 ? 1 : 0))

#define _DIMMING_OGC_RGB_GAIN_ADDRESS                  (_DIMMING_OGC_GAMMA6_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _BACKLIGHT_DIMMING_SUPPORT)

#define _OGC_NONE_ADDRESS                              0
#define _OCC_GAMMA10_ADDRESS                           (_DIMMING_OGC_RGB_GAIN_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE * _BACKLIGHT_DIMMING_SUPPORT)

#define _OCC_HDR10_GAMMA10_ADDRESS                     ((_TWO_BRI_CALIBRATION_TYPE != _TWO_BRI_CALIBRATION_NONE) ? (_OCC_GAMMA10_ADDRESS + _OCC_GAMMA_TABLE_SIZE * _OCC_SUPPORT) : _OCC_GAMMA10_ADDRESS)
#define _OCC_GAMMA10_MAX_BRI_ADDRESS                   ((_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR) ? (_OCC_GAMMA10_ADDRESS + _OCC_GAMMA_TABLE_SIZE * _OCC_SUPPORT) : _OCC_GAMMA10_ADDRESS)

#define _OGC_DICOM_ADDRESS                             (_OCC_HDR10_GAMMA10_ADDRESS + _OCC_GAMMA_TABLE_SIZE * _OCC_SUPPORT)

#define _DIMMING_OCC_GAMMA10_ADDRESS                   (_OGC_DICOM_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_DICOM_SUPPORT)
#define _DISP_CALIBRATION_PCM_END                      (_DIMMING_OCC_GAMMA10_ADDRESS + _OCC_GAMMA_TABLE_SIZE * _BACKLIGHT_DIMMING_SUPPORT)

//--------------------------------------------------
// Address for FREESYNCII Mode
//--------------------------------------------------
#define _FREESYNC_II_OCC_GAMMA10_ADDRESS               0

#define _FREESYNC_II_PANEL_NATIVE_MATRIX_ADDRESS       (_FREESYNC_II_OCC_GAMMA10_ADDRESS + _OCC_GAMMA_TABLE_SIZE * _FREESYNC_II_SUPPORT)

#define _FREESYNC_II_IG_SRGB_ADDRESS                   (_FREESYNC_II_PANEL_NATIVE_MATRIX_ADDRESS + _FREESYNC_II_COLORMATRIX_TABLE_TOTAL_SIZE * _FREESYNC_II_SUPPORT)
#define _FREESYNC_II_IG_BT709_ADDRESS                  (_FREESYNC_II_IG_SRGB_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _FREESYNC_II_SUPPORT)
#define _FREESYNC_II_IG_GAMMA22_ADDRESS                (_FREESYNC_II_IG_BT709_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _FREESYNC_II_SUPPORT)
#define _FREESYNC_II_IG_GAMMA26_ADDRESS                (_FREESYNC_II_IG_GAMMA22_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _FREESYNC_II_SUPPORT)
#define _FREESYNC_II_IG_PQINTERIM_ADDRESS              (_FREESYNC_II_IG_GAMMA26_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _FREESYNC_II_SUPPORT)

#define _DISP_CALIBRATION_TOTAL_END2                   (_FREESYNC_II_IG_PQINTERIM_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * _FREESYNC_II_SUPPORT)
#define _DISP_CALIBRATION_TOTAL_SPACE2                 (_DISP_CALIBRATION_TOTAL_END2 - _FREESYNC_II_OCC_GAMMA10_ADDRESS)

#define _FREESYNC_II_CHKSUM_ADDRESS                    (_FREESYNC_II_PANEL_NATIVE_MATRIX_ADDRESS - 1)
#define _FREESYNC_II_FINISH_ADDRESS                    (_FREESYNC_II_CHKSUM_ADDRESS - 1)

#define _FREESYNC_II_IG_CHKSUM_ADDRESS                 (_FREESYNC_II_FINISH_ADDRESS - 1)

#define _OGC_CHKSUM_ADDRESS                            _CHECKSUM_START_ADDRESS
#define _OGC_RGB_GAIN_CHKSUM_ADDRESS                   (_CHECKSUM_START_ADDRESS + 1)
#define _OGC_HEADER_CHKSUM_ADDRESS                     (_CHECKSUM_START_ADDRESS + 2)
#define _OCC_CHKSUM_ADDRESS                            (_CHECKSUM_START_ADDRESS + 3)
#define _OCC_HDR_CHKSUM_ADDRESS                        (_CHECKSUM_START_ADDRESS + 4)
#define _OCC_COLOR_MATRIX_CHKSUM_ADDRESS               (_CHECKSUM_START_ADDRESS + 5)
#define _OCC_COLOR_MATRIX2_CHKSUM_ADDRESS              (_CHECKSUM_START_ADDRESS + 6)
#define _OGC_DICOM_CHKSUM_ADDRESS                      (_CHECKSUM_START_ADDRESS + 7)
#define _OGC_FINISH_ADDRESS                            (_CHECKSUM_START_ADDRESS + 8)
#define _OCC_FINISH_ADDRESS                            (_CHECKSUM_START_ADDRESS + 9)
#define _OGC_DICOM_FINISH_ADDRESS                      (_CHECKSUM_START_ADDRESS + 10)
#define _HDR_CHKSUM_ADDRESS                            (_CHECKSUM_START_ADDRESS + 11)
#define _HDR_FINISH_ADDRESS                            (_CHECKSUM_START_ADDRESS + 12)
#define _DIMMING_OCC_CHKSUM_ADDRESS                    (_CHECKSUM_START_ADDRESS + 13)
#define _DIMMING_IG_CHKSUM_ADDRESS                     (_CHECKSUM_START_ADDRESS + 14)
#define _EDID_INFO_CHKSUM_ADDRESS                      (_CHECKSUM_START_ADDRESS + 15)
#define _HDR_NOTM_BOUND_CHKSUM_ADDRESS                 (_CHECKSUM_START_ADDRESS + 16)
#define _HDRPLUS_CHKSUM_ADDRESS                        (_CHECKSUM_START_ADDRESS + 17)
#define _OGC_MAX_BRI_CHKSUM_ADDRESS                    (_CHECKSUM_START_ADDRESS + 18)
#define _OGC_RGB_GAIN_MAX_BRI_CHKSUM_ADDRESS           (_CHECKSUM_START_ADDRESS + 19)
#define _OCC_COLOR_MATRIX_MAX_BRI_CHKSUM_ADDRESS       (_CHECKSUM_START_ADDRESS + 20)
#define _OCC_COLOR_MATRIX2_MAX_BRI_CHKSUM_ADDRESS      (_CHECKSUM_START_ADDRESS + 21)
#define _DIMMING_NOTM_DCR_THD_CHKSUM_ADDRESS           (_CHECKSUM_START_ADDRESS + 22)
#define _OCC_OGC_CALIBRATION_FINISH_ADDRESS            (_CHECKSUM_START_ADDRESS + 23)

#else // else of (_OGC_GEN_TYPE == _OGC_GEN_1)
//--------------------------------------------------
// Address for OGC/OCC/DICOM
//--------------------------------------------------
#define _OGC_RGB_GAIN_TOTAL_SPACE                      0x100
#define _OGC_GAMMA_TABLE_SIZE                          0x500
#define _OGC_RGB_GAIN_ACTUAL_SIZE                      (_OGC_TOTAL_GAMMA * _OGC_TOTAL_CT * 3)

#define _OCC_COLOR_MATRIX_TOTAL_SPACE                  0x100
#define _OCC_COLORMATRIX_TABLE_SIZE                    0x12

#define _OGC_RGB_GAIN_ADDRESS                          0
#define _OGC_GAMMA1_ADDRESS                            (_OGC_RGB_GAIN_ADDRESS + _OGC_RGB_GAIN_TOTAL_SPACE * _OGC_SUPPORT)
#define _OGC_GAMMA2_ADDRESS                            (_OGC_GAMMA1_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_SUPPORT * (_OGC_TOTAL_GAMMA > 1 ? 1 : 0))
#define _OGC_GAMMA3_ADDRESS                            (_OGC_GAMMA2_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_SUPPORT * (_OGC_TOTAL_GAMMA > 2 ? 1 : 0))
#define _OGC_GAMMA4_ADDRESS                            (_OGC_GAMMA3_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_SUPPORT * (_OGC_TOTAL_GAMMA > 3 ? 1 : 0))
#define _OGC_GAMMA5_ADDRESS                            (_OGC_GAMMA4_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_SUPPORT * (_OGC_TOTAL_GAMMA > 4 ? 1 : 0))

#define _OCC_GAMMA10_ADDRESS                           (_OGC_GAMMA5_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_SUPPORT)
#define _OCC_SRGBMATRIX_ADDRESS                        (_OCC_GAMMA10_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_ADOBEMATRIX_ADDRESS                       (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_USERDEFINE_ADDRESS                        (_OCC_ADOBEMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)

#define _OGC_DICOM_ADDRESS                             (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLOR_MATRIX_TOTAL_SPACE * _OCC_SUPPORT)

#define _DISP_CALIBRATION_TOTAL_END                    (_OGC_DICOM_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_DICOM_SUPPORT)
#define _DISP_CALIBRATION_TOTAL_SPACE                  (_DISP_CALIBRATION_TOTAL_END - _OGC_RGB_GAIN_ADDRESS)

#define _OGC_CHKSUM_ADDRESS                            (_OCC_GAMMA10_ADDRESS - 1)
#define _OGC_RGB_GAIN_CHKSUM_ADDRESS                   (_OGC_GAMMA1_ADDRESS - 1)
#define _OCC_CHKSUM_ADDRESS                            (_OCC_SRGBMATRIX_ADDRESS - 1)
#define _OCC_COLOR_MATRIX_CHKSUM_ADDRESS               (_OGC_DICOM_ADDRESS - 1)
#define _OGC_DICOM_CHKSUM_ADDRESS                      (_OGC_DICOM_ADDRESS + _OGC_GAMMA_TABLE_SIZE - 1)
#define _OGC_FINISH_ADDRESS                            (_OGC_CHKSUM_ADDRESS - 1)
#define _OCC_FINISH_ADDRESS                            (_OCC_CHKSUM_ADDRESS - 1)
#define _OGC_DICOM_FINISH_ADDRESS                      (_OGC_DICOM_CHKSUM_ADDRESS - 1)

#endif // End of (_OGC_GEN_TYPE == _OGC_GEN_1)

//--------------------------------------------------
// MACRO of Panel Uniformity
//--------------------------------------------------
#define CEILING_OF_INT_DIVISION(x, y)                  (((x) % (y)) ? (((x) / (y)) + 1) : ((x) / (y)))

//--------------------------------------------------
// Address for Panel Uniformity
//--------------------------------------------------
#define _UNIFORMITY_FINISH_ADDRESS                     0
#define _UNIFORMITY_OFFSET_FINISH_ADDRESS              0

//--------------------------------------------------
// Auto config error status
//--------------------------------------------------
#define _AUTO_CONFIG_MEASURE_ERROR                     _BIT0
#define _AUTO_CONFIG_CLOCK_ABORT                       _BIT1
#define _AUTO_CONFIG_PHASE_ABORT                       _BIT2

//--------------------------------------------------
// Auto config Percentage Stage
//--------------------------------------------------
#define _AUTO_CONFIG_CHECK_MULTITIMES_FINISH           5
#define _AUTO_CONFIG_CLOCK_CHECK_WIDTH_FINISH          10
#define _AUTO_CONFIG_CLOCK_ROUGH_ADJUST_FINISH         20
#define _AUTO_CONFIG_CLOCK_FINETUNE_FINISH             75
#define _AUTO_CONFIG_CLOCK_FINISH                      80
#define _AUTO_CONFIG_PHASE_FINISH                      90
#define _AUTO_CONFIG_V_POSITION_FINISH                 95
#define _AUTO_CONFIG_H_POSITION_FINISH                 100


//--------------------------------------------------
// Definitions of HDMI Multi Edid Switch Related
//--------------------------------------------------
#define _HDMI_EXT_EDID_MAX_CNT                         12

//--------------------------------------------------
// Definitions of Clock Settings Used by COsdFxGetAdcClockRange()
//--------------------------------------------------
#ifndef _CUSTOM_CLOCK_BIAS_VALUE
#define _CLOCK_BIAS                                    50
#else
#define _CLOCK_BIAS                                    _CUSTOM_CLOCK_BIAS_VALUE
#endif

#define _GET_CLOCKRANGE_MAX                            0
#define _GET_CLOCKRANGE_MIN                            1

//--------------------------------------------------
// Definitions of Hor. Position Settings Used by COsdFxGetHPositionRange()
//--------------------------------------------------
#define _HPOSITION_BIAS                                (UserCommonAdjustGetHPositionHBiasValue())
#define _GET_HPOSITIONRANGE_MAX                        (0)
#define _GET_HPOSITIONRANGE_MIN                        (1)

//--------------------------------------------------
// Definitions of Ver. Position Settings Used by COsdFxGetVPositionRange()
//--------------------------------------------------
#define _VPOSITION_BIAS                                (UserCommonAdjustGetVPositionVBiasValue())
#define _GET_VPOSITIONRANGE_MAX                        (0)
#define _GET_VPOSITIONRANGE_MIN                        (1)

//--------------------------------------------------
// Definitions of Phase Range
//--------------------------------------------------
#define _ADJUST_PHASE_MAX                              63
#define _ADJUST_PHASE_MIN                              0
#define _ADJUST_PHASE_CENTER                           (((_ADJUST_PHASE_MAX - _ADJUST_PHASE_MIN) / 2) + _ADJUST_PHASE_MIN)

//--------------------------------------------------
// // MACRO for Digital H Position
//--------------------------------------------------
#define GET_DIGITAL_H_POSITION()                       (g_ucDigitalHPosition)
#define SET_DIGITAL_H_POSITION(x)                      (g_ucDigitalHPosition = (x))

//--------------------------------------------------
// // MACRO for Digital H Position
//--------------------------------------------------
#define GET_DIGITAL_V_POSITION()                       (g_ucDigitalVPosition)
#define SET_DIGITAL_V_POSITION(x)                      (g_ucDigitalVPosition = (x))

//--------------------------------------------------
// MACRO of Panel Power Sequence
//--------------------------------------------------
#define GET_PANELPOWERSTATUS()                         (g_stPanelPowerInfo.b3Status)
#define SET_PANELPOWERSTATUS(x)                        (g_stPanelPowerInfo.b3Status = (x))

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
#define GET_PANELPOWERACTION()                         (g_stPanelPowerInfo.b2Action)
#define SET_PANELPOWERACTION(x)                        (g_stPanelPowerInfo.b2Action = (x))
#endif

//--------------------------------------------------
// MACRO for OSD Fail Safe Mode
//--------------------------------------------------
#define GET_FAIL_SAFE_MODE()                           (g_bFailSafeMode)
#define SET_FAIL_SAFE_MODE(x)                          (g_bFailSafeMode = (x))

//--------------------------------------------------
// MACRO for Force SetPwmDuty flag
//--------------------------------------------------
#define GET_FORCESETPWMDUTY_FLAG()                     (g_bForceSetPwmDuty)
#define SET_FORCESETPWMDUTY_FLAG(x)                    (g_bForceSetPwmDuty = (x))

//--------------------------------------------------
// // MACRO for VGA Mode Adjust H Position
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_H_POSITION()               (g_stVGAModeUserData.ucUserHPosition)
#define SET_VGA_MODE_ADJUST_H_POSITION(x)              (g_stVGAModeUserData.ucUserHPosition = (x))

//--------------------------------------------------
// // MACRO for VGA Mode Adjust V Position
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_V_POSITION()               (g_stVGAModeUserData.ucUserVPosition)
#define SET_VGA_MODE_ADJUST_V_POSITION(x)              (g_stVGAModeUserData.ucUserVPosition = (x))

//--------------------------------------------------
// // MACRO for VGA Mode Adjust Clock
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_CLOCK()                    (g_stVGAModeUserData.usUserClock)
#define SET_VGA_MODE_ADJUST_CLOCK(x)                   (g_stVGAModeUserData.usUserClock = (x))

//--------------------------------------------------
// // MACRO for VGA Mode Adjust Phase
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_PHASE()                    (g_stVGAModeUserData.ucUserPhase)
#define SET_VGA_MODE_ADJUST_PHASE(x)                   (g_stVGAModeUserData.ucUserPhase = (x))

//--------------------------------------------------
// MACRO for VGA Mode Do Auto
//--------------------------------------------------
#define GET_VGA_MODE_DO_FIRST_AUTO()                   (g_stVGAModeUserData.b1DoFirstAuto)
#define SET_VGA_MODE_DO_FIRST_AUTO(x)                  (g_stVGAModeUserData.b1DoFirstAuto = (x))

//--------------------------------------------------
// 
//--------------------------------------------------
#if(_CUSTOMER == _CUS_TOSHIBA)
#define GET_1600_1024_COM()                            ((bit)(g_ucPictureChange & _BIT0))
#define SET_1600_1024_COM()                            (g_ucPictureChange |= _BIT0)
#define CLR_1600_1024_COM()                            (g_ucPictureChange &= ~_BIT0)
#endif


typedef enum
{
    _WRITE_SIZE_8 = 8,
    _WRITE_SIZE_16 = 16,
    _WRITE_SIZE_32 = 32,
} EnumEepromWriteSize;



#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
#define UserCommonNVRamRead(x, y, z)                   UserCommonEepromRead(x, y, z)
#define UserCommonNVRamSaveSystemData()                UserCommonEepromSaveSystemData()
#define UserCommonNVRamLoadSystemData()                UserCommonEepromLoadSystemData()
#define UserCommonNVRamRestoreSystemData()             UserCommonEepromRestoreSystemData()

#if(_VGA_SUPPORT == _ON)
#define UserCommonNVRamLoadModeUserData(x)             UserCommonEepromLoadModeUserData(x)
#define UserCommonNVRamSaveModeUserData()              UserCommonEepromSaveModeUserData()
#define UserCommonNVRamLoadModeUserModeNumberData(x)   UserCommonEepromLoadModeUserModeNumberData(x)
#define UserCommonNVRamRestoreModeUserData()           UserCommonEepromRestoreModeUserData()
#define UserCommonNVRamVGAFifoModeIndexOffsetInc()     UserCommonEepromVGAFifoModeIndexOffsetInc()
#define UserCommonNVRamGetMaxFifoGroupCnt()            UserCommonEepromGetMaxFifoGroupCnt()
#define UserCommonNVRamSaveADCSetting(x)               UserCommonEepromSaveADCSetting(x)
#define UserCommonNVRamLoadADCSetting(x)               UserCommonEepromLoadADCSetting(x)
#define UserCommonNVRamRestoreADCSetting()             UserCommonEepromRestoreADCSetting()
#endif // End of #if(_VGA_SUPPORT == _ON)

#else
#define UserCommonNVRamRead(x, y, z)                   UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, x, y, z)
#define UserCommonNVRamSaveSystemData()                UserCommonFlashSaveSystemData()
#define UserCommonNVRamLoadSystemData()                UserCommonFlashLoadSystemData()
#define UserCommonNVRamRestoreSystemData()             UserCommonFlashRestoreSystemData()

#if(_VGA_SUPPORT == _ON)
#define UserCommonNVRamLoadModeUserData(x)             UserCommonFlashLoadModeUserData(x)
#define UserCommonNVRamSaveModeUserData()              UserCommonFlashSaveModeUserData()
#define UserCommonNVRamLoadModeUserModeNumberData(x)   UserCommonFlashLoadModeUserModeNumberData(x)
#define UserCommonNVRamRestoreModeUserData()           UserCommonFlashRestoreModeUserData()
#define UserCommonNVRamVGAFifoModeIndexOffsetInc()     UserCommonFlashVGAFifoModeIndexOffsetInc()
#define UserCommonNVRamGetMaxFifoGroupCnt()            UserCommonFlashGetMaxFifoGroupCnt()
#define UserCommonNVRamSaveADCSetting(x)               UserCommonFlashSaveADCSetting(x)
#define UserCommonNVRamLoadADCSetting(x)               UserCommonFlashLoadADCSetting(x)
#define UserCommonNVRamRestoreADCSetting()             UserCommonFlashRestoreADCSetting()
#endif // End of #if(_VGA_SUPPORT == _ON)

#endif // End of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)


#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
#define UserCommonNVRamGetHDCPKeyBKsv(x, y, z)         UserCommonEepromGetHDCPKeyBKsv(x, y, z)
#define UserCommonNVRamGetHDCPKey(x, y, z)             UserCommonEepromGetHDCPKey(x, y, z)

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreHDCP1P4(x, y, z)         UserCommonEepromRestoreHDCP1P4(x, y, z)
#endif

#if(_DP_TX_SUPPORT == _ON)
#define UserCommonNVRamGetTxHDCPKeyAKsv(x, y, z)       UserCommonEepromGetTxHDCPKeyAKsv(x, y, z)
#define UserCommonNVRamGetTxHDCPKey(x, y, z)           UserCommonEepromGetTxHDCPKey(x, y, z)
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreTxHDCP1P4(x, y, z)       UserCommonEepromRestoreTxHDCP1P4(x, y, z)
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
#define UserCommonNVRamGetHDCPKeyBKsv(x, y, z)         UserCommonFlashGetHDCPKeyBKsv(x, y, z)
#define UserCommonNVRamGetHDCPKey(x, y, z)             UserCommonFlashGetHDCPKey(x, y, z)

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreHDCP1P4(x, y, z)         UserCommonFlashRestoreHDCP1P4(x, y, z)
#endif

#if(_DP_TX_SUPPORT == _ON)
#define UserCommonNVRamGetTxHDCPKeyAKsv(x, y, z)       UserCommonFlashGetTxHDCPKeyAKsv(x, y, z)
#define UserCommonNVRamGetTxHDCPKey(x, y, z)           UserCommonFlashGetTxHDCPKey(x, y, z)
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreTxHDCP1P4(x, y, z)       UserCommonFlashRestoreTxHDCP1P4(x, y, z)
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)

#if(_HDCP_2_2_SUPPORT == _ON)
#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
#define UserCommonNVRamGetHdcp2Certrx(x, y, z)         UserCommonEepromGetHdcp2Certrx(x, y, z)
#define UserCommonNVRamGetHdcp2RSADkey(x, y, z)        UserCommonEepromGetHdcp2RSADkey(x, y, z)
#define UserCommonNVRamGetHdcp2RSARRModN(x, y, z)      UserCommonEepromGetHdcp2RSARRModN(x, y, z)
#define UserCommonNVRamGetHdcp2RSAKPriv(x, y, z)       UserCommonEepromGetHdcp2RSAKPriv(x, y, z)
#define UserCommonNVRamGetHdcp2RSANpinv(x, y, z)       UserCommonEepromGetHdcp2RSANpinv(x, y, z)
#define UserCommonNVRamGetHdcp2LCKey(x, y, z)          UserCommonEepromGetHdcp2LCKey(x, y, z)

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreHDCP2(x, y, z)           UserCommonEepromRestoreHDCP2(x, y, z)
#endif

#if(_DP_TX_SUPPORT == _ON)
#define UserCommonNVRamGetTxHdcp2RRMODN(x, y, z)       UserCommonEepromGetTxHdcp2RRMODN(x, y, z)
#define UserCommonNVRamGetTxHdcp2DcpLlcN(x, y, z)      UserCommonEepromGetTxHdcp2DcpLlcN(x, y, z)
#define UserCommonNVRamGetTxHdcp2EKey(x, y, z)         UserCommonEepromGetTxHdcp2EKey(x, y, z)
#define UserCommonNVRamGetTxHdcp2NPinv(x, y, z)        UserCommonEepromGetTxHdcp2NPinv(x, y, z)
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreTxHDCP2(x, y, z)         UserCommonEepromRestoreTxHDCP2(x, y, z)
#endif
#endif

#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
#define UserCommonNVRamGetHdcp2Certrx(x, y, z)         UserCommonFlashGetHdcp2Certrx(x, y, z)
#define UserCommonNVRamGetHdcp2RSADkey(x, y, z)        UserCommonFlashGetHdcp2RSADkey(x, y, z)
#define UserCommonNVRamGetHdcp2RSARRModN(x, y, z)      UserCommonFlashGetHdcp2RSARRModN(x, y, z)
#define UserCommonNVRamGetHdcp2RSAKPriv(x, y, z)       UserCommonFlashGetHdcp2RSAKPriv(x, y, z)
#define UserCommonNVRamGetHdcp2RSANpinv(x, y, z)       UserCommonFlashGetHdcp2RSANpinv(x, y, z)
#define UserCommonNVRamGetHdcp2LCKey(x, y, z)          UserCommonFlashGetHdcp2LCKey(x, y, z)

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreHDCP2(x, y, z)           UserCommonFlashRestoreHDCP2(x, y, z)
#endif

#if(_DP_TX_SUPPORT == _ON)
#define UserCommonNVRamGetTxHdcp2RRMODN(x, y, z)       UserCommonFlashGetTxHdcp2RRMODN(x, y, z)
#define UserCommonNVRamGetTxHdcp2DcpLlcN(x, y, z)      UserCommonFlashGetTxHdcp2DcpLlcN(x, y, z)
#define UserCommonNVRamGetTxHdcp2EKey(x, y, z)         UserCommonFlashGetTxHdcp2EKey(x, y, z)
#define UserCommonNVRamGetTxHdcp2NPinv(x, y, z)        UserCommonFlashGetTxHdcp2NPinv(x, y, z)
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreTxHDCP2(x, y, z)         UserCommonFlashRestoreTxHDCP2(x, y, z)
#endif
#endif
#endif // End of #if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

//--------------------------------------------------
// MACRO for Type-C When _DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS
//--------------------------------------------------
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#define GET_D0_DP_TYPE_C_DETECT_CC_ATTACH()            ((bit)g_stTypeCPortControllerD0CommonInfo.b1DetectCcAttachFlag)
#define SET_D0_DP_TYPE_C_DETECT_CC_ATTACH()            (g_stTypeCPortControllerD0CommonInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_D0_DP_TYPE_C_DETECT_CC_ATTACH()            (g_stTypeCPortControllerD0CommonInfo.b1DetectCcAttachFlag = _FALSE)

#define GET_D0_DP_TYPE_C_DETECT_ALT_MODE()             ((bit)g_stTypeCPortControllerD0CommonInfo.b1DetectAltModeFlag)
#define SET_D0_DP_TYPE_C_DETECT_ALT_MODE()             (g_stTypeCPortControllerD0CommonInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_D0_DP_TYPE_C_DETECT_ALT_MODE()             (g_stTypeCPortControllerD0CommonInfo.b1DetectAltModeFlag = _FALSE)
#endif

#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#define GET_D1_DP_TYPE_C_DETECT_CC_ATTACH()            ((bit)g_stTypeCPortControllerD1CommonInfo.b1DetectCcAttachFlag)
#define SET_D1_DP_TYPE_C_DETECT_CC_ATTACH()            (g_stTypeCPortControllerD1CommonInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_D1_DP_TYPE_C_DETECT_CC_ATTACH()            (g_stTypeCPortControllerD1CommonInfo.b1DetectCcAttachFlag = _FALSE)

#define GET_D1_DP_TYPE_C_DETECT_ALT_MODE()             ((bit)g_stTypeCPortControllerD1CommonInfo.b1DetectAltModeFlag)
#define SET_D1_DP_TYPE_C_DETECT_ALT_MODE()             (g_stTypeCPortControllerD1CommonInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_D1_DP_TYPE_C_DETECT_ALT_MODE()             (g_stTypeCPortControllerD1CommonInfo.b1DetectAltModeFlag = _FALSE)
#endif

#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#define GET_D6_DP_TYPE_C_DETECT_CC_ATTACH()            ((bit)g_stTypeCPortControllerD6CommonInfo.b1DetectCcAttachFlag)
#define SET_D6_DP_TYPE_C_DETECT_CC_ATTACH()            (g_stTypeCPortControllerD6CommonInfo.b1DetectCcAttachFlag = _TRUE)
#define CLR_D6_DP_TYPE_C_DETECT_CC_ATTACH()            (g_stTypeCPortControllerD6CommonInfo.b1DetectCcAttachFlag = _FALSE)

#define GET_D6_DP_TYPE_C_DETECT_ALT_MODE()             ((bit)g_stTypeCPortControllerD6CommonInfo.b1DetectAltModeFlag)
#define SET_D6_DP_TYPE_C_DETECT_ALT_MODE()             (g_stTypeCPortControllerD6CommonInfo.b1DetectAltModeFlag = _TRUE)
#define CLR_D6_DP_TYPE_C_DETECT_ALT_MODE()             (g_stTypeCPortControllerD6CommonInfo.b1DetectAltModeFlag = _FALSE)
#endif

//--------------------------------------------------
// Calibration Active Mode
//--------------------------------------------------
typedef enum
{
    _CALIBRATION_OFF,
    _CALIBRATION_ON,

} EnumLDActiveMode;

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))

#define GET_ON_LINE_CALIBRATION_STATUS()               (g_stCalibrationInfo.b1CalibrationActiveMode)
#define SET_ON_LINE_CALIBRATION_STATUS(x)              (g_stCalibrationInfo.b1CalibrationActiveMode = (x))

#else

#define GET_ON_LINE_CALIBRATION_STATUS()               (_CALIBRATION_OFF)
#define SET_ON_LINE_CALIBRATION_STATUS(x)              (_nop_())

#endif // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))#if(_LOCAL_DIMMING_SUPPORT == _ON)
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b3Status : 3;

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
    BYTE b2Action : 2;
#endif

} StructPanelPowerInfo;

typedef struct
{
    BYTE b1IsPresetMode : 1;
    BYTE b1DoFirstAuto : 1;
    BYTE ucModeNumber;
    BYTE ucUserHPosition;
    BYTE ucUserVPosition;
    WORD usUserClock;
    BYTE ucUserPhase;
    WORD usCenterHPosition;
    WORD usCenterVPosition;
    WORD usCenterClock;
    BYTE ucCenterPhase;
} StructVGAModeUserDataType;

typedef struct
{
    BYTE ucModeSlotIndex;                       // Mode Slot Index
    BYTE ucSSC;
    BYTE ucDPEDIDSelect;                        // DP EDID Select

    BYTE b3HDMIHotPlugSupportTime : 3;          // HDMIHotPlugSupportTime(Unit : 100ms)
    BYTE b1HDMIHotPlugSupport : 1;              // HDMIHotPlugSupport
    BYTE b1SourceHPAutoSearch : 1;              // HP User Auto Search
    BYTE b3SourceHPDefaultSearchIndex : 3;      // HP User Defautl SearchIndex

    BYTE b1DPHotPlugDCOffHigh : 1;              // DPHotPlugDCOffHigh
    BYTE b1DPAuxDiffMode : 1;                   // DPAuxDiffMode
    BYTE b3D0DpLanes : 3;
    BYTE b3D1DpLanes : 3;

    BYTE b3D2DpLanes : 3;
    BYTE b3D6DpLanes : 3;
    BYTE b1PowerStatus : 1;                     // Monitor Power Status
    BYTE b1ColorSeamlessChange : 1;             // Colorimetry Seamless Change

    WORD b4SearchPort : 4;                      // Search Port
    WORD b3EdidD0 : 3;
    WORD b3EdidD1 : 3;
    WORD b3EdidD2 : 3;
    WORD b3EdidD3 : 3;

    WORD b3EdidD4 : 3;
    WORD b3EdidD5 : 3;
    WORD b3EdidD6 : 3;
    WORD b4SourceScanType : 4;                  // Source Scan Type
    BYTE b4DPAuxAdjrSetting : 4;                // DPAuxAdjrSetting
    BYTE ucDpIrqTime_10us;                      // DP IRQ HPD time (unit : 10us)
    BYTE b1DPIllegalIdlePatternCheck : 1;       // Eizo DP Illegal Idle Pattern Check Support
}StructSystemDataType;

typedef struct
{
    BYTE ucESDcrCurRGBAvgValue;
    BYTE ucESDcrPreRGBAvgValue;
    BYTE ucESDcrPWMTargetValue;
    BYTE ucESDcrPWMAdjustValue;
}StructESDcrInfo;

typedef struct
{
    BYTE b1DetectCcAttachFlag : 1;
    BYTE b1DetectAltModeFlag : 1;
}StructPortControllerCommonInfo;

typedef enum
{
    _DP_EDID_1080P = 0,
    _DP_EDID_2560_1440,
    _DP_EDID_4K2K_60HZ,
    _DP_EDID_AMOUNT = _DP_EDID_4K2K_60HZ,
    _DP_EDID_4K2K_30HZ,
}EnumDpEDIDSelection;



typedef enum
{
    _HDMI_1P4 = 0,
    _HDMI_2P0,
    _HDMI_2P1,
}EnumHDMIVerSelection;

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Struct for Type-C SMBus Command
//--------------------------------------------------
typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucOffset1;
    BYTE ucOffset2;
    BYTE ucReportDataLength;
} StructSMBusWRGetICStatus;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucFWMainVer;
    BYTE ucFWSubVer1;
    BYTE ucFWSubVer2;
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucPDTypeCStatus;
    BYTE ucByte9;
    BYTE ucByte10;
    BYTE ucByte11;
    BYTE ucByte12;
    BYTE ucSMBusReadyStatus;
    BYTE ucByte14;
    BYTE ucByte15;
    BYTE ucByte16;
    BYTE ucByte17;
    BYTE ucByte18;
    BYTE ucByte19;
} StructSMBusRDGetICStatus;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
    BYTE ucDPCapVDOByte0;
    BYTE ucDPCapVDOByte1;
    BYTE ucDPCapVDOByte2;
    BYTE ucDPCapVDOByte3;
} StructSMBusWRSetDPLanes;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
} StructSMBusWRReadDPLanes;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucPortNum;
    BYTE ucDPCapVDOByte0;
    BYTE ucDPCapVDOByte1;
    BYTE ucDPCapVDOByte2;
} StructSMBusRDReadDPLanes;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucDPCfgVDOByte0;
    BYTE ucDPCfgPinConfig;
    BYTE ucDPCfgVDOByte2;
    BYTE ucDPCfgVDOByte3;
} StructSMBusRDReadDPLanesCfg;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
    BYTE ucDPCapVDOByte0;
    BYTE ucDPCapVDOByte1;
    BYTE ucDPCapVDOByte2;
    BYTE ucDPCapVDOByte3;
} StructSMBusWRSetDPMultiFunction;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
} StructSMBusWRReadDPMultiFunction;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucDPStatusVDOByte0;
    BYTE ucDPStatusVDOByte1;
    BYTE ucDPStatusVDOByte2;
    BYTE ucDPStatusVDOByte3;
} StructSMBusRDReadDPMultiFunction;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucPortNum;
    BYTE ucByte2;
} StructSMBusWRReconnect;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
} StructSMBusWrSetSSMode;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucByte3;
} StructSMBusWRDetectDSPSSMode;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucDSP0;
    BYTE ucDSP1;
    BYTE ucDSP2;
    BYTE ucDSP3;
} StructSMBusRDDetectDSPSSMode;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucRsvByte;
    BYTE ucPortNum;
    BYTE ucStatusLen;
} StructSMBusWRGetStatus;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucByte3;                   // [1] VDM Received
    BYTE ucByte4;                   // [6] Power Role (SRC:1 / SNK:0)
    BYTE ucByte5;
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucByte8_LaneSwap;
    BYTE ucByte9;
    BYTE ucByte10_DFP_UFP;          // [2:0] Data Role
    BYTE ucByte11;
    BYTE ucByte12;
    BYTE ucByte13_AltModeStatus;    // [7] Fujitsu / Lenovo Alt Mode Ready, [2:0] DP Alt Mode Ready
} StructSMBusRDGetStatus;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
} StructSMBusWRGetCableInfo;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucVid_High;
    BYTE ucVid_Low;
    BYTE ucPid_High;
    BYTE ucPid_Low;
} StructSMBusRDGetCableInfo;

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucPdodata;
} StructSMBusWRGetPartnerPdo;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucByte3;
    BYTE ucByte4;
    BYTE ucByte5;
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucByte8;
    BYTE ucByte9;
    BYTE ucByte10;
    BYTE ucByte11;
    BYTE ucByte12;
    BYTE ucByte13;
    BYTE ucByte14;
    BYTE ucByte15;
    BYTE ucByte16;
    BYTE ucByte17;
    BYTE ucByte18;
    BYTE ucByte19;
    BYTE ucByte20;
    BYTE ucByte21;
    BYTE ucByte22;
    BYTE ucByte23;
    BYTE ucByte24;
    BYTE ucByte25;
    BYTE ucByte26;
    BYTE ucByte27;
} StructSMBusRDGetPartnerPdo;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
} StructSMBusWRGetPdoStatus;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucByte3;
} StructSMBusRDGetPdoStatus;
#endif

typedef struct
{
    BYTE ucCommandStatus;
    BYTE ucDataLength;
} StructSMBusRDCommandReadyStatus;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
} StructSMBusWREnableVenderCommand;

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
} StructSMBusWRGetLenovoInfo;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0_DeviceType;
    BYTE ucByte1_SystemState;
} StructSMBusRDGetLenovoInfo;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
} StructSMBusWRGetLenovoVdm;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucVdmHeader0;
    BYTE ucVdmHeader1;
    BYTE ucVdmHeader2;
    BYTE ucVdmHeader3;
    BYTE ucByte5;
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucByte8;
    BYTE ucByte9;
    BYTE ucByte10;
    BYTE ucByte11;
    BYTE ucByte12;
} StructSMBusRDGetLenovoVdm;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVdmHeader0;
    BYTE ucVdmHeader1;
    BYTE ucVdmHeader2;
    BYTE ucVdmHeader3;
    BYTE ucByte4;
    BYTE ucByte5;
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucByte8;
    BYTE ucByte9;
    BYTE ucByte10;
    BYTE ucByte11;
} StructSMBusWRSendLenovoVdmAck;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVdmHeader0;
    BYTE ucVdmHeader1;
    BYTE ucVdmHeader2;
    BYTE ucVdmHeader3;
} StructSMBusWRSendLenovoVdmReq;
#endif

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucRsvByte;
    BYTE ucPortNum;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucByte3;
    BYTE ucByte4;
} StructSMBusWRAckCCCI;

union UnionSMBusWRCommandStrct
{
    StructSMBusWRGetICStatus stWrGetICStatus;
    StructSMBusWRSetDPMultiFunction stWrSetDPMultiFunction;
    StructSMBusWRReadDPMultiFunction stWrReadDPMultiFunction;
    StructSMBusWRSetDPLanes stWrSetDPLanes;
    StructSMBusWRReadDPLanes stWrReadDPLanes;
    StructSMBusWRGetStatus stWRGetStatus;
    StructSMBusWRReconnect stWrReconnect;
    StructSMBusWrSetSSMode stWrSetSSMode;

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
    StructSMBusWRGetPartnerPdo stWrGetPartnerPdo;
    StructSMBusWRGetPdoStatus stWrGetPdoStatus;
#endif

    StructSMBusWRDetectDSPSSMode stWrSetDetectDspSSMode;
    StructSMBusWREnableVenderCommand stWrEnableVenderCommand;
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    StructSMBusWRGetLenovoInfo stWrGetLenovoInfo;
    StructSMBusWRGetLenovoVdm stWrGetLenovoVdm;
    StructSMBusWRSendLenovoVdmAck stWrSendLenovoVdmAck;
    StructSMBusWRSendLenovoVdmReq stWrSendLenovoVdmReq;
#endif
    StructSMBusWRAckCCCI stWrAckCCCI;
};

union UnionSMBusRDCommandStrct
{
    StructSMBusRDCommandReadyStatus stRdCommandReadyStatus;
    StructSMBusRDGetICStatus stRdGetICStatus;
    StructSMBusRDReadDPMultiFunction stRdDPMultiFunction;
    StructSMBusRDReadDPLanes stRdDPlanes;
    StructSMBusRDReadDPLanesCfg stRdDPlanesCfg;
    StructSMBusRDReadDPLanesCfg stRdDpCap;
    StructSMBusRDGetStatus stRdGetStatus;

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
    StructSMBusRDGetPartnerPdo stRdGetPartnerPdo;
    StructSMBusRDGetPdoStatus stRdGetPdoStatus;
#endif
    StructSMBusRDGetCableInfo stRdGetCableInfo;
    StructSMBusRDDetectDSPSSMode stRdDetectDspSSMode;
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    StructSMBusRDGetLenovoInfo stRdGetLenovoInfo;
    StructSMBusRDGetLenovoVdm stRdGetLenovoVdm;
#endif
};

typedef enum
{
    _SMBUS_CMD_STATUS_NOTPROCEED = 0x00,
    _SMBUS_CMD_STATUS_COMPLETE = 0x01,
    _SMBUS_CMD_STATUS_DEFER = 0x02,
} EnumSMBusCmdStatus;

#endif

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))

typedef struct
{
    BYTE b1CalibrationActiveMode                  : 1;

}StructCalibrationInfo;

extern StructCalibrationInfo g_stCalibrationInfo;

#endif // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from UserCommonAdjust.c
//----------------------------------------------------------------------------------------
#if(_CUSTOMER == _CUS_TOSHIBA)
extern BYTE g_ucPictureChange;
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonInterface.c
//----------------------------------------------------------------------------------------
extern BYTE g_ucDigitalHPosition;
extern BYTE g_ucDigitalVPosition;
extern StructPanelPowerInfo g_stPanelPowerInfo;
extern bit g_bFailSafeMode;
extern bit g_bForceSetPwmDuty;

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonAuto.c
//----------------------------------------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern BYTE g_ucAutoConfigStatus;
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonDdcciFunction.c
//----------------------------------------------------------------------------------------
#if(_SUPPORT_GET_LUT == _ON)
extern WORD g_ucLUTCheckSum;
extern BYTE g_ucLUTReadyFlag;
#endif

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
extern BYTE xdata *g_pucDISP_CALIBRATION_FLASH;
extern BYTE xdata *g_pucDISP_FREESYNC_II_CALIBRATION_FLASH;
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonNVRamSystem.c
//----------------------------------------------------------------------------------------
extern StructSystemDataType g_stSystemData;

#if(_CUSTOMER == _CUS_MINDRAY)
extern StructUserDataInflashType g_stUserDataInFlash; 
#endif

#if(_VGA_SUPPORT == _ON)
extern StructVGAModeUserDataType g_stVGAModeUserData;
extern StructAdcDataType g_stAdcData;
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//----------------------------------------------------------------------------------------
// Extern functions from UserCommonTypeCCommunication.c
//----------------------------------------------------------------------------------------
#if(_PORT_CONTROLLER_RTS_SMBUS_SUPPORT == _ON)
extern union UnionSMBusRDCommandStrct g_unSMBusRdDataPool;
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonPortControllerCommon.c
//----------------------------------------------------------------------------------------
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
extern StructPortControllerCommonInfo g_stTypeCPortControllerD0CommonInfo;
#endif

#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
extern StructPortControllerCommonInfo g_stTypeCPortControllerD1CommonInfo;
#endif

#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
extern StructPortControllerCommonInfo g_stTypeCPortControllerD6CommonInfo;
#endif

#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//----------------------------------------------------------------------------------------
// UserCommonInterface.c
//----------------------------------------------------------------------------------------
extern void UserCommonInterfacePanelPowerAction(BYTE ucEvent);
extern void UserCommonInterfaceOsdResetProc(void);

#if(_VGA_SUPPORT == _ON)
extern void UserCommonInterfaceAdjustADCData(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
extern EnumAspectRatioType UserInterfaceGetAspectRatioType(void);
extern void UserInterfaceGetAspectRatio(WORD *pusHRatio, WORD *pusVRatio);
extern void UserInterfaceAdjustAspectRatio(void);
#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern BYTE UserInterfaceGetAspectRatioOriginalRatio(void);
extern BYTE UserInterfaceGetAspectRatioOriginalRatioSmall(void);
#endif
#endif

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
extern void UserInterfaceAdjustBeforeDisplayCalibration(EnumCaliType enumMode);
extern void UserInterfaceAdjustAfterDisplayCalibration(EnumCaliType enumMode);
extern void UserInterfaceAdjustBacklight(BYTE ucBacklight);
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
extern void UserInterfaceAdjustBeforeDimmingCalibration(void);
extern void UserInterfaceAdjustAfterDimmingCalibration(void);
#endif

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
extern void UserInterfaceAdjustLDBoostCalibration(bit bBoost);
#endif

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
extern EnumDDCCIDebugMode UserInterfaceGetDdcciMode(void);
#endif

#if(_DP_SUPPORT == _ON)
extern void UserCommonInterfaceDpAuxSet(void);
extern void UserCommonInterfaceDpVersionSwitch(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
extern void UserCommonInterfaceDPSwitchAllPortDpVersion(void);
extern StructDpRxErrorCount UserCommonInterfaceDpRxGetErrorCount(BYTE ucInputPort);
extern EnumDPMSTPort UserCommonInterfaceGetDpMstCapablePort(void);
extern void UserCommonInterfaceMstRx0Rx1switch(EnumDPMSTPort enumMstCapablePort);
extern WORD UserCommonInterfaceDpGetEdidNativeTimingBw(EnumDpEdidPort enumDpEdidPort);
#endif

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
extern void UserCommonInterfaceCloneModeSwitch(bit bClone);
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
extern void UserCommonInterfaceTypeCU3ModeSwitch(BYTE ucInputPort);
extern void UserCommonInterfaceTypeCU3ModeAllPortCapabilitySwitch(void);
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
extern void UserCommonInterfaceTypeCPinAssignmentESupportSwitch(BYTE ucInputPort);
#endif
#endif

extern void UserCommonInterfaceDdcciSwitch(EnumDDCCIDebugMode enumMode, BYTE ucInputPort);

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
extern void UserCommonInterfaceDataExchangeAllDataReset(void);
#endif

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void UserCommonInterfaceMbrStrobeBacklightCtrl(bit bLightCtrl);
EnumMbrBacklightMode UserCommonInterfacceMbrGetBacklightMode(void);
EnumMbrBacklightMode UserCommonInterfacceMbrGetCurrentBacklightMode(void);
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void UserCommonInterfaceMbrDrrHandler(void);
extern bit UserCommonInterfaceMbrDrrCheckHW(void);
extern bit UserCommonInterfaceMbrDrrGetHWSupport(void);
#endif
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void UserCommonInterfaceAdjustRtkAdvMbr(void);
#endif
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
extern void UserCommonInterfaceMbrAdvAdjust(BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
#endif
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
extern void UserCommonInterfaceOledAdjustBackLight(BYTE value);
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
extern bit ScalerDisplayDPTx1NativeAuxWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
#endif
#endif

//----------------------------------------------------------------------------------------
// UserCommonAuto.c
//----------------------------------------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern void UserCommonAutoConfig(void);
extern bit UserCommonAutoMeasureMultiTimes(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonAdjust.c
//----------------------------------------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern WORD UserCommonAdjustGetAdcClockRange(BYTE ucPar);
#endif

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
extern void UserCommonAdjustEmbeddedDpSwitch(void);
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
extern WORD UserCommonAdjustGetHPositionRange(BYTE ucPar);
extern WORD UserCommonAdjustGetHPositionHBiasValue(void);
extern WORD UserCommonAdjustGetVPositionRange(BYTE ucPar);
extern WORD UserCommonAdjustGetVPositionVBiasValue(void);
extern void UserCommonAdjustHPosition(BYTE ucUserHPosition);
extern void UserCommonAdjustVPosition(BYTE ucUserVPosition);
#endif

#if(_VGA_SUPPORT == _ON)
extern void UserCommonAdjustClock(WORD usUserIHTotal);
extern void UserCommonAdjustPhase(BYTE ucPhase);

#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
extern void UserCommonAdjustDigitalFilterEnhancePhase(void);
#endif

#if(_RINGING_FILTER_SUPPORT == _ON)
extern void UserCommonAdjustRingingFilter(void);
#endif

#endif // End of #if(_VGA_SUPPORT == _ON)

extern BYTE UserCommonAdjustRealValueToPercent(WORD usRealValue, WORD usMax, WORD usMin, WORD usCenter);
extern WORD UserCommonAdjustPercentToRealValue(BYTE ucPercentValue, WORD usMax, WORD usMin, WORD usCenter);

#if(_OVERSCAN_SUPPORT == _ON)
extern void UserCommonAdjustOverScan(void);
#endif

#if(_UNDERSCAN_SUPPORT == _ON)
extern void UserCommonAdjustUnderScan(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
extern void UserCommonAdjustAspectRatio(void);
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
extern void UserCommonAdjustRotationInputSize(void);
extern void UserCommonAdjustRotationDisplaySize(void);
#endif

#if(_I_DITHER_SUPPORT == _ON)
extern void UserCommonAdjustIDither(void);
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
extern void UserCommonAdjustRGBQuantizationRange(void);
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
extern void UserCommonAdjustUltraVivid(EnumFunctionOnOFF enumFunctionOnOFF, EnumColorSpace enumColorFormat, EnumDBApply enumDBApply);
#endif

#if(_D_DITHER_SUPPORT == _ON)
extern void UserCommonAdjustDDither(void);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
extern BYTE UserCommonAdjustGetUniformityType(BYTE ucIndex);
extern void UserCommonAdjustPanelUniformity(EnumUniformityTypeSelect enumUniformityType, EnumUniformityModeSelect enumUniformityMode);
extern BYTE UserCommonAdjustPanelUniformityGainBank(EnumUniformityTypeSelect enumUniformityType);
extern WORD UserCommonAdjustPanelUniformityGainAddr(EnumUniformityTypeSelect enumUniformityType);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
extern BYTE UserCommonAdjustPanelUniformityOffsetBank(EnumUniformityTypeSelect enumUniformityType);
extern WORD UserCommonAdjustPanelUniformityOffsetAddr(EnumUniformityTypeSelect enumUniformityType);
extern WORD UserCommonAdjustPanelUniformityDecayAddr(EnumUniformityTypeSelect enumUniformityType);
#endif
#endif

#if(_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)
extern WORD UserCommonAdjust6bitPanelCompensate(WORD usData);
#endif

// 10  bit Panel
extern WORD UserCommonAdjust10bitPanelCompensate(WORD usData);

#if(_SHARPNESS_SUPPORT == _ON)
extern void UserCommonAdjustSharpness(EnumSourceSearchPort enumSourceSearchPort);
#endif

#if(_FREEZE_SUPPORT == _ON)
extern void UserCommonAdjustDisplayFreeze(bit bEn);
#endif

#if(_OGC_SUPPORT == _ON)
extern void UserCommonAdjustOGCColorTempGain(BYTE ucColorTemp, BYTE ucGammaMode, BYTE *pucData, EnumOGCModeSelect enumOGCModeSelect);
#endif

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
extern BYTE UserCommonAdjustOGCBank(EnumOGCTypeSelect enumOGCTypeSelect, EnumOGCModeSelect enumOGCModeSelect);
extern BYTE *UserCommonAdjustOGCAddr(EnumOGCTypeSelect enumOGCTypeSelect, EnumOGCModeSelect enumOGCModeSelect);
#endif

#if(_PCM_FUNCTION == _ON)
extern void UserCommonAdjustPCM(EnumPCMType enumPCMMode, BYTE *pucIGammaTableArray, BYTE *pucOGammaTableArray, BYTE *pucColorMatrixArray, BYTE ucPCMBankNum, WORD usLength);
#endif

#if(_GAMMA_FUNCTION == _ON)
extern void UserCommonAdjustGamma(BYTE *pucOGammaTableArray, BYTE ucGammaBankNum);
extern void UserCommonAdjustGammaRegionEnable(EnumFunctionOnOFF enumOn);
#endif

#if(_SDR_TO_HDR_SUPPORT == _ON)
extern void UserCommonAdjustSDRToHDR(BYTE *pucIGammaTableArray, BYTE *pucICMTableArray, BYTE *pucDCCTableArray, BYTE ucSDRtoHDRBank);
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
extern void UserCommonAdjustGlobalHueSat(SWORD shHue, WORD usSat);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonNVRamSystem.c
//----------------------------------------------------------------------------------------
extern BYTE UserCommonNVRamGetSystemData(EnumSystemDataItemDataType enumDataType);
extern void UserCommonNVRamSetSystemData(EnumSystemDataItemDataType enumDataType, BYTE ucValue);

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit UserCommonEepromIICRead(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
extern bit UserCommonEepromIICWrite(BYTE ucSlaveAddr, DWORD ulSubAddr, BYTE ucSubAddrLength, DWORD ulLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum, EnumEepromWriteSize enumWriteSize);
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//----------------------------------------------------------------------------------------
// Extern functions from UserCommonPortControllerCommon.c
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonPortControllerEmbedded.c
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonPortControllerRts5400.c/UserCommonPortControllerUser.c
//----------------------------------------------------------------------------------------
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
extern EnumTypeCAttachStatus UserCommonPortControllerGetD0CcAttachByI2C(void);
extern EnumTypeCAltModeStatus UserCommonPortControllerGetD0AltModeReadyByI2C(void);
#endif

#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
extern EnumTypeCAttachStatus UserCommonPortControllerGetD1CcAttachByI2C(void);
extern EnumTypeCAltModeStatus UserCommonPortControllerGetD1AltModeReadyByI2C(void);
#endif

#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
extern EnumTypeCAttachStatus UserCommonPortControllerGetD6CcAttachByI2C(void);
extern EnumTypeCAltModeStatus UserCommonPortControllerGetD6AltModeReadyByI2C(void);
#endif

#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
extern bit UserCommonPortControllerGet5400I2CEnabledFlag(BYTE ucInputPort);
extern void UserCommonPortControllerSet5400I2CEnabledFlag(BYTE ucInputPort);
extern bit UserCommonPortControllerEnable5400VenderCommand(BYTE ucInputPort);
extern bit UserCommonPortControllerGet5400InfoByI2C(BYTE ucInputPort, Enum5400InfoType enum5400InfoType, BYTE *pucReadInfo);
extern bit UserCommonPortControllerConfig5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment);
extern bit UserCommonPortControllerConfig5400MultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction);
#endif

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
extern bit UserCommonPortControllerConfigUserPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment);
extern bit UserCommonPortControllerConfigUserMultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonUsbHubRts5411.c
//----------------------------------------------------------------------------------------
#if((_USB_HUB_RTS5411_SERIES_SUPPORT == _ON) && (_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON))
extern BYTE UserCommonUsbHubGetDspInfo(EnumHubDsp enumHubDspx);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonTypecCommunication.c
//----------------------------------------------------------------------------------------
#if(_PORT_CONTROLLER_RTS_SMBUS_SUPPORT == _ON)
extern bit UserCommonTypecCommunicationWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, BYTE ucInputPort);
extern bit UserCommonTypecCommunicationRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, BYTE ucInputPort);
extern bit UserCommonTypecCommunicationShortRead(BYTE ucDeviceAddr, BYTE *pucReadArray, BYTE ucInputPort);
extern bit UserCommonTypecCommunicationPollingPDReady(BYTE ucDeviceAddr, WORD usTime, BYTE ucInputPort);
#endif
#endif
//-------------------------------------------------------

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
extern bit UserCommonEepromRead(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern bit UserCommonEepromWrite(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
extern void UserCommonEepromSaveSystemData(void);
extern void UserCommonEepromLoadSystemData(void);
extern void UserCommonEepromRestoreSystemData(void);

#if(_VGA_SUPPORT == _ON)
extern void UserCommonEepromLoadModeUserData(BYTE ucSlotIndex);
extern void UserCommonEepromSaveModeUserData(void);
extern BYTE UserCommonEepromLoadModeUserModeNumberData(BYTE ucSlotIndex);
extern void UserCommonEepromRestoreModeUserData(void);
extern BYTE UserCommonEepromVGAFifoModeIndexOffsetInc(BYTE ucStep);
extern BYTE UserCommonEepromGetMaxFifoGroupCnt(void);
extern void UserCommonEepromLoadADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonEepromSaveADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonEepromRestoreADCSetting(void);
#endif // End of #if(_VGA_SUPPORT == _ON)

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
extern bit UserCommonFlashLoadItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength);
extern bit UserCommonFlashSaveItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength);
extern BYTE UserCommonFlashCalculateCheckSumData(BYTE *pucData, BYTE ucLength);
extern void UserCommonFlashSaveSystemData(void);
extern void UserCommonFlashLoadSystemData(void);
extern void UserCommonFlashRestoreSystemData(void);

#if(_CUSTOMER == _CUS_MINDRAY)
extern void RTDFlashLoadUserData(void);
extern void RTDFlashRestoreUserData(void);
extern void RTDFlashSaveUserData(void);
#endif

#if(_VGA_SUPPORT == _ON)
extern void UserCommonFlashLoadModeUserData(BYTE ucSlotIndex);
extern void UserCommonFlashSaveModeUserData(void);
extern BYTE UserCommonFlashLoadModeUserModeNumberData(BYTE ucSlotIndex);
extern void UserCommonFlashRestoreModeUserData(void);
extern BYTE UserCommonFlashVGAFifoModeIndexOffsetInc(BYTE ucStep);
extern BYTE UserCommonFlashGetMaxFifoGroupCnt(void);
extern void UserCommonFlashLoadADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonFlashSaveADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonFlashRestoreADCSetting(void);
#endif

#endif // Else of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)


// EDID
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)))
extern void UserCommonEepromRestoreEDID(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
extern void UserCommonFlashRestoreEDID(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif


// HDCP
#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
extern void UserCommonEepromGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonEepromRestoreHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonEepromGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonEepromGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonEepromRestoreTxHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
extern void UserCommonFlashGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonFlashRestoreHDCP1P4(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonFlashGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonFlashGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonFlashRestoreTxHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)

#if(_HDCP_2_2_SUPPORT == _ON)
#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
extern void UserCommonEepromGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonEepromRestoreHDCP2(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonEepromGetTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonEepromRestoreTxHDCP2(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif

#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
extern void UserCommonFlashGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonFlashRestoreHDCP2(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonFlashGetTxHdcp2RRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetTxHdcp2DcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetTxHdcp2EKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetTxHdcp2NPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonFlashRestoreTxHDCP2(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif
#endif
#endif // End of #if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)
extern EnumDpAuxStatus UserCommonInterfaceDpTxAuxI2COverWrite(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray);
extern EnumDpAuxStatus UserCommonInterfaceDpTxAuxI2COverRead(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray);
#endif

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)


#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
extern bit UserCommonFlashErasePage(BYTE ucBank, BYTE ucPage);
extern bit UserCommonFlashWrite(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData);
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _ON)
extern bit UserCommonFlashRead(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData);
#endif


#if(_FLASH_WR_PROTECT == _ON)
extern void UserCommonFlashWRProtect(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonCec.c
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Extern functions from UserCommonDdcciFunction.c
//----------------------------------------------------------------------------------------
extern void UserCommonDdcciInitTx(void);
extern void UserCommonDdcciInitRx(void);
extern BYTE UserCommonDdcciCalCheckSum(void);
#if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE != Gamma_default)) 
extern BYTE UserCommonDdcciCalRxCheckSum(void); // for beacon gamma auto adjust function
#endif
extern void UserCommonDdcciSetVCPReplyValue(BYTE ucTypeOpcode, WORD usMax, WORD usPresent);
extern void UserCommonDdcciGetTimingReport(void);
extern void UserCommonDdcciGetCapabilitiesRequest(void);

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonDisplayCalibration.c
//----------------------------------------------------------------------------------------
#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
extern void UserCommonDdcciDispCalibProcess(void);
extern BYTE UserCommonDdcciDispCalibCalCheckSum(BYTE ucCheckType);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserModeSearch.c
//----------------------------------------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern BYTE UserCommonModeSearchCheckFIFOModeSaved(BYTE ucModeIndex);
extern void UserCommonModeSearchInitalUserAndCenterData(BYTE ucIndex);
extern WORD UserCommonModeSearchGetModetableTimingDataItem(BYTE ucModeNumber, EnumTimingInfoSelect enumTimingInfo);
extern bit UserCommonModeSearchCheckPresetModeTable(BYTE ucMatchmode);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserOsd.c
//----------------------------------------------------------------------------------------
extern void UserOsdHandler(void);

#if((_FREESYNC_SUPPORT == _ON) && (_TRANSLATOR_SUPPORT == _OFF))
extern void UserCommonInterfaceFreeSyncSupportSwitch(void);
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
extern void UserCommonInterfaceLoadEmbeddedEdidData(void);
#if(_DP_SUPPORT == _ON)
extern void UserCommonInterfaceDPSwitchEdid(BYTE ucSelectedPort);
extern void UserCommonInterfaceDPSwitchAllPortEdid(void);
#endif
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern void UserCommonInterfaceHDMISwitchEdid(BYTE ucInputport, EnumEdidSelection enumHDMIEDIDSelection);
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_HDR10_SUPPORT == _ON))
extern void UserCommonInterfaceHDMISwitchAllPortEdid(void);
#endif
extern EnumHdmiEdidLocation UserCommonInterfaceHDMIGetMultiEdidLocated(BYTE ucInputport, EnumEdidSelection enumHDMIEDIDSelection);
extern void UserCommonInterfaceHDMISwitchMultiEeprom(BYTE ucInputPort, EnumEdidSelection enumHDMIEDIDSelection);
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
extern bit UserCommonInterfaceGetRGBQuantizationLimitRangeStatus(EnumColorRGBQuantization enumColorRGBQuantization);
#endif

extern EnumColorSpace UserCommonInterfaceGetColorFormat(void);

#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_II) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III))
extern void UserCommonInterfaceForceUsingDDomainDB(void);
#endif
#endif

//----------------------------------------------------------------------------------------
// Code Digital Signature DDC-CI Handler Option
//----------------------------------------------------------------------------------------
#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
extern void UserCommonSignDdcciHandler(void);
#endif
