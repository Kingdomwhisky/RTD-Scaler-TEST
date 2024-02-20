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
// ID Code      : UserCommonDdcciDefine.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of DDCCI Address
//--------------------------------------------------
#define _DDCCI_DEST_ADDRESS                         0x6E
#define _DDCCI_SRC_ADDRESS                          0x51
#define _DDCCI_CONTROL_STATUS_FLAG                  0x80

//--------------------------------------------------
// Definitions of DDCCI Protocol Items
//--------------------------------------------------
#define _DDCCI_SOURCE                               0
#define _DDCCI_LENGTH                               1
#define _DDCCI_COMMAND                              2
#define _DDCCI_SOURCE_OPCODE                        3

#define _DDCCI_RESULT_CODE                          3
#define _DDCCI_SINK_OPCODE                          4
#define _DDCCI_TYPE_CODE                            5
#define _DDCCI_MAX_HIGH_BYTE                        6
#define _DDCCI_MAX_LOW_BYTE                         7
#define _DDCCI_PRESENT_HIGH_BYTE                    8
#define _DDCCI_PRESENT_LOW_BYTE                     9

#define _DDCCI_SET_HIGH_BYTE                        4
#define _DDCCI_SET_LOW_BYTE                         5

#define _DDCCI_OFS_HIGH_BYTE                        3
#define _DDCCI_OFS_LOW_BYTE                         4

#define _DDCCI_TIMING_MSG_COMMAND                   1
#define _DDCCI_TIMING_MSG_OPCODE                    2
#define _DDCCI_TIMING_STATUS                        3
#define _DDCCI_TIMING_HFREQ_HBYTE                   4
#define _DDCCI_TIMING_HFREQ_LBYTE                   5
#define _DDCCI_TIMING_VFREQ_HBYTE                   6
#define _DDCCI_TIMING_VFREQ_LBYTE                   7

//--------------------------------------------------
// Definitions of DDCCI Commands
//--------------------------------------------------
#define _DDCCI_CMD_GET_VCP_FEATURE                  0x01
#define _DDCCI_CMD_GET_VCP_FEATURE_REPLY            0x02
#define _DDCCI_CMD_SET_VCP_FEATURE                  0x03
#define _DDCCI_CMD_REPLY_TIMING_MESSAGE             0x06
#define _DDCCI_CMD_GET_TIMING_REPORT                0x07
#define _DDCCI_CMD_SAVE_CURRENT_SETTINGS            0x0C
#define _DDCCI_CMD_FACTORY_GAMMA_ADJUST             0xC0
#define _DDCCI_CMD_CAPABILITIES_REQUEST_REPLY       0xE3
#define _DDCCI_CMD_CAPABILITIES_REQUEST             0xF3
#define _DDCCI_CMD_UPDATE_GAMMA_DATA                0xC8

#define _DDCCI_VIRTUAL_HOST_ADDRESS                 0x50

//--------------------------------------------------
// Definitions of DDCCI VCP Opcode
//--------------------------------------------------
#define _DDCCI_OPCODE_VCP_CODE_PAGE                 0x00
#define _DDCCI_OPCODE_VCP_DEGAUSS                   0x01
#define _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE         0x02
#define _DDCCI_OPCODE_VCP_SOFT_CONTROLS             0x03
#define _DDCCI_OPCODE_VCP_FACTORY_RESET             0x04
#define _DDCCI_OPCODE_VCP_RECAL_BRI_CON             0x05
#define _DDCCI_OPCODE_VCP_GEOMETRY_RESET            0x06
#define _DDCCI_OPCODE_VCP_COLOR_RESET               0x08
#define _DDCCI_OPCODE_VCP_FACTORY_TV_RESET          0x0A
#define _DDCCI_OPCODE_VCP_COLOR_TEMP_INCREMENT      0x0B
#define _DDCCI_OPCODE_VCP_COLOR_TEMP_REQUEST        0x0C
#define _DDCCI_OPCODE_VCP_CLOCK                     0x0E

#define _DDCCI_OPCODE_VCP_PWM_Value                 0x0F

#define _DDCCI_OPCODE_VCP_BACKLIGHT                 0x10
#define _DDCCI_OPCODE_VCP_FLESH_TONE_ENHANCEMENT    0x11
#define _DDCCI_OPCODE_VCP_CONTRAST                  0x12
#define _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET       0x14
#define _DDCCI_OPCODE_VCP_RED_GAIN                  0x16
#define _DDCCI_OPCODE_VCP_COLOR_VISION_COMPENSATION 0x17
#define _DDCCI_OPCODE_VCP_GREEN_GAIN                0x18
#define _DDCCI_OPCODE_VCP_BLUE_GAIN                 0x1A
#define _DDCCI_OPCODE_VCP_FOCUS                     0x1C
#define _DDCCI_OPCODE_VCP_AUTO_SET_UP               0x1E
#define _DDCCI_OPCODE_VCP_AUTO_COLOR                0x1F
#define _DDCCI_OPCODE_VCP_HPOSITION                 0x20
#define _DDCCI_OPCODE_VCP_HSIZE                     0x22
#define _DDCCI_OPCODE_VCP_HPINCUSHION               0x24
#define _DDCCI_OPCODE_VCP_HPINCUSHION_BALANCE       0x26
#define _DDCCI_OPCODE_VCP_HCONVERGENCE_RB           0x28
#define _DDCCI_OPCODE_VCP_HCONVERGENCE_MG           0x29
#define _DDCCI_OPCODE_VCP_HLINEARITY                0x2A
#define _DDCCI_OPCODE_VCP_HLINEARITY_BALANCE        0x2C
#define _DDCCI_OPCODE_VCP_GRAY_SCALE_EXPANSION      0x2E
#define _DDCCI_OPCODE_VCP_VPOSITION                 0x30
#define _DDCCI_OPCODE_VCP_VSIZE                     0x32
#define _DDCCI_OPCODE_VCP_VPINCUSHION               0x34
#define _DDCCI_OPCODE_VCP_VPINCUSHION_BALANCE       0x36
#define _DDCCI_OPCODE_VCP_VCONVERGENCE_RB           0x38
#define _DDCCI_OPCODE_VCP_VCONVERGENCE_MG           0x39
#define _DDCCI_OPCODE_VCP_VLINEARITY                0x3A
#define _DDCCI_OPCODE_VCP_VLINEARITY_BALANCE        0x3C
#define _DDCCI_OPCODE_VCP_CLOCK_PHASE               0x3E
#define _DDCCI_OPCODE_VCP_HPARALLELOGRAM            0x40
//#define _DDCCI_OPCODE_VCP_VPARALLELOGRAM            0x41
//#define _DDCCI_OPCODE_VCP_HKEYSTONE                 0x42
//#define _DDCCI_OPCODE_VCP_VKEYSTONE                 0x43
//#define _DDCCI_OPCODE_VCP_ROTATION                  0x44
//#define _DDCCI_OPCODE_VCP_TOP_CORNER_FLARE          0x46
#define _DDCCI_OPCODE_VCP_HV_FREQ                   0x41
#define _DDCCI_OPCODE_VCP_HV_TOTAL                  0x42
#define _DDCCI_OPCODE_VCP_HV_PIXEL                  0x43
#define _DDCCI_OPCODE_VCP_HV_SYNC_WIDTH             0x44
#define _DDCCI_OPCODE_VCP_HV_START                  0x45
#define _DDCCI_OPCODE_VCP_CURRENT_STATE             0x46

#define _DDCCI_OPCODE_VCP_g_SignalUnstable          0x47
#define _DDCCI_OPCODE_VCP_g_IssueState              0x49

#define _DDCCI_OPCODE_VCP_TOP_CORNER_HOOK           0x48
#define _DDCCI_OPCODE_VCP_BOTTOM_CORNER_FLARE       0x4A
#define _DDCCI_OPCODE_VCP_BOTTOM_CORNER_HOOK        0x4C
#define _DDCCI_OPCODE_TIMING_MSG                    0x4E
#define _DDCCI_OPCODE_VCP_ACTIVE_CONTROL            0x52
#define _DDCCI_OPCODE_VCP_COLORTEMP                 0x54
#define _DDCCI_OPCODE_VCP_HMOIRE                    0x56
#define _DDCCI_OPCODE_VCP_VMOIRE                    0x58
#define _DDCCI_OPCODE_VCP_SAT_RED                   0x59
#define _DDCCI_OPCODE_VCP_SAT_YELLOW                0x5A
#define _DDCCI_OPCODE_VCP_SAT_GREEN                 0x5B
#define _DDCCI_OPCODE_VCP_SAT_CYAN                  0x5C
#define _DDCCI_OPCODE_VCP_SAT_BLUE                  0x5D
#define _DDCCI_OPCODE_VCP_SAT_MAGENTA               0x5E
#define _DDCCI_OPCODE_VCP_INPUT_SOURCE              0x60
#define _DDCCI_OPCODE_VCP_AUDIO_VOLUME              0x62
#define _DDCCI_OPCODE_VCP_SPEAKER_SELECT            0x63
#define _DDCCI_OPCODE_VCP_MICROPHONE_VOLUME         0x64

#define _DDCCI_OPCODE_VCP_AUTO_AMBIENT_LIGHT_SENSOR 0x66
#define _DDCCI_OPCODE_VCP_AMBIENT_LIGHT_SENSOR      0x67

#define _DDCCI_OPCODE_VCP_BACKLIGHT_LEVEL_WHITE     0x6B
#define _DDCCI_OPCODE_VCP_RED_BLACK_LEVEL           0x6C
#define _DDCCI_OPCODE_VCP_BACKLIGHT_LEVEL_RED       0x6D
#define _DDCCI_OPCODE_VCP_GREEN_BLACK_LEVEL         0x6E
#define _DDCCI_OPCODE_VCP_BACKLIGHT_LEVEL_GREEN     0x6F
#define _DDCCI_OPCODE_VCP_BLUE_BLACK_LEVEL          0x70
#define _DDCCI_OPCODE_VCP_BACKLIGHT_LEVEL_BLUE      0x71
#define _DDCCI_OPCODE_VCP_GAMMA                     0x72
#define _DDCCI_OPCODE_VCP_LUT_SIZE                  0x73
#define _DDCCI_OPCODE_VCP_SINGLE_POINT_LUT          0x74
#define _DDCCI_OPCODE_VCP_BLOCK_LUT                 0x75
#define _DDCCI_OPCODE_VCP_REMOTE_PROC_CALL          0x76
#define _DDCCI_OPCODE_VCP_ID_DATA_OPERATION         0x78
#define _DDCCI_OPCODE_VCP_ADJUST_ZOOM               0x7C
#define _DDCCI_OPCODE_VCP_PRODUCTKEY                0x7E
#define _DDCCI_OPCODE_VCP_HMIRROR                   0x82
#define _DDCCI_OPCODE_VCP_VMIRROR                   0x84
#define _DDCCI_OPCODE_VCP_DISPLAY_SCALING           0x86
#define _DDCCI_OPCODE_VCP_SHARPNESS                 0x87
#define _DDCCI_OPCODE_VCP_VELOCITY_SCAN_MODULATION  0x88
#define _DDCCI_OPCODE_VCP_TV_SATURATION             0x8A
#define _DDCCI_OPCODE_VCP_TV_CHANNEL_UP_DOWN        0x8B
#define _DDCCI_OPCODE_VCP_TV_SHARPNESS              0x8C
#define _DDCCI_OPCODE_VCP_AUDIO_MUTE                0x8D
#define _DDCCI_OPCODE_VCP_TV_CONTRAST               0x8E
#define _DDCCI_OPCODE_VCP_AUDIO_TREBLE              0x8F
#define _DDCCI_OPCODE_VCP_HUE                       0x90
#define _DDCCI_OPCODE_VCP_AUDIO_BASS                0x91
#define _DDCCI_OPCODE_VCP_TV_BLACK_LEVEL            0x92
#define _DDCCI_OPCODE_VCP_AUDIO_BALANCE             0x93
#define _DDCCI_OPCODE_VCP_AUDIO_PROCESSOR_MODE      0x94
#define _DDCCI_OPCODE_VCP_WINDOW_POSITION_TL_X      0x95
#define _DDCCI_OPCODE_VCP_WINDOW_POSITION_TL_Y      0x96
#define _DDCCI_OPCODE_VCP_WINDOW_POSITION_BR_X      0x97
#define _DDCCI_OPCODE_VCP_WINDOW_POSITION_BR_Y      0x98
#define _DDCCI_OPCODE_VCP_WINDOW_BACKGROUND         0x9A
#define _DDCCI_OPCODE_VCP_RED                       0x9B
#define _DDCCI_OPCODE_VCP_YELLOW                    0x9C
#define _DDCCI_OPCODE_VCP_GREEN                     0x9D
#define _DDCCI_OPCODE_VCP_CYAN                      0x9E
#define _DDCCI_OPCODE_VCP_BLUE                      0x9F
#define _DDCCI_OPCODE_VCP_MAGENDA                   0xA0
#define _DDCCI_OPCODE_VCP_AUTO_SETUP                0xA2
#define _DDCCI_OPCODE_VCP_WINDOW_MASK_CONTROL       0xA4
#define _DDCCI_OPCODE_VCP_WINDOW_SELECT             0xA5
#define _DDCCI_OPCODE_VCP_WINDOW_SIZE               0xA6
#define _DDCCI_OPCODE_VCP_WINDOW_TRANSPARENCY       0xA7
#define _DDCCI_OPCODE_VCP_SYNC_TYPE                 0xA8
#define _DDCCI_OPCODE_VCP_HFREQ                     0xAC
#define _DDCCI_OPCODE_VCP_VFREQ                     0xAE
#define _DDCCI_OPCODE_VCP_STORE_SETTING             0xB0
#define _DDCCI_OPCODE_VCP_PANEL_TYPE                0xB2
#define _DDCCI_OPCODE_VCP_RGB_ORDERING              0xB4
#define _DDCCI_OPCODE_VCP_COLOR_CODING              0xB5
#define _DDCCI_OPCODE_VCP_MONITOR_TYPE              0xB6
#define _DDCCI_OPCODE_VCP_MONITOR_STATUS            0xB7
#define _DDCCI_OPCODE_VCP_PACKET_COUNT              0xB8
#define _DDCCI_OPCODE_VCP_MONITOR_X_ORIGIN          0xB9
#define _DDCCI_OPCODE_VCP_MONITOR_Y_ORIGIN          0xBA
#define _DDCCI_OPCODE_VCP_HEADER_ERROR_COUNT        0xBB
#define _DDCCI_OPCODE_VCP_BODY_CRC_ERROR_COUNT      0xBC
#define _DDCCI_OPCODE_VCP_CLIENT_ID                 0xBD
#define _DDCCI_OPCODE_VCP_LINK_CONTROL              0xBE
#define _DDCCI_OPCODE_VCP_USAGE_TIME                0xC0
#define _DDCCI_OPCODE_VCP_DISP_DESCRIPTOR_LENGTH    0xC2
#define _DDCCI_OPCODE_VCP_TRANSMIT_DISP_DESCRIPTOR  0xC3
#define _DDCCI_OPCODE_VCP_DISP_DESCRIPTOR_EN        0xC4
#define _DDCCI_OPCODE_VCP_APPLICATION_ENABLE        0xC6
#define _DDCCI_OPCODE_VCP_DISP_ENABLE_KEY           0xC7
#define _DDCCI_OPCODE_VCP_CONTROLLER_TYPE           0xC8
#define _DDCCI_OPCODE_VCP_FW_LEVEL                  0xC9
#define _DDCCI_OPCODE_VCP_OSD_ON_OFF                0xCA
#define _DDCCI_OPCODE_VCP_OSD_LANGUAGE              0xCC
#define _DDCCI_OPCODE_VCP_STATUS_INDICATOR          0xCD
#define _DDCCI_OPCODE_VCP_AUXILIARY_DISP_SIZE       0xCE
#define _DDCCI_OPCODE_VCP_AUXILIARY_DISP_DATA       0xCF
#define _DDCCI_OPCODE_VCP_OUTPUT_SELECT             0xD0
#define _DDCCI_OPCODE_VCP_ASSET_TAG                 0xD2
#define _DDCCI_OPCODE_VCP_STEREO_VIDEO_MODE         0xD4
#define _DDCCI_OPCODE_VCP_POWER_MODE                0xD6
#define _DDCCI_OPCODE_VCP_AUXILIARY_POWER_OUTPUT    0xD7
#define _DDCCI_OPCODE_VCP_SCAN_MODE                 0xDA
#define _DDCCI_OPCODE_VCP_IMAGE_MODE                0xDB
#define _DDCCI_OPCODE_VCP_DISPLAY_APPLICATION       0xDC
#define _DDCCI_OPCODE_VCP_SCRACHPAD                 0xDE
#define _DDCCI_OPCODE_VCP_VERSION                   0xDF

#define _DDCCI_OPCODE_VCP_GET_HardwareVersion       0xE0

#if(_GET_HARD_ID == _ON)
#define _DDCCI_OPCODE_VCP_GET_HardID                0xE1
#endif

#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
#define _DDCCI_OPCODE_VCP_BACKLIGHTSENSOR_ONOFF     0xE2
#endif

#define _DDCCI_OPCODE_VCP_CONTROL_LOCK              0xE3

#if(_SUPPORT_GET_LUT == _ON)
#define _DDCCI_OPCODE_VCP_LUT_TABLE                 0xE4
#define _DDCCI_OPCODE_VCP_RECOVER_EDID              0xE5
#endif

#if(_KL_5V_12V_GPIO_CONTROL == _ON)
#define _DDCCI_OPCODE_VCP_CONTROL_PANEL_5V_PCTR     0xEE
#define _DDCCI_OPCODE_VCP_CONTROL_PANEL_12V_PCTR    0xEF
#endif

#if(_CUSTOMER == _CUS_BAISHENG)
#define _DDCCI_OPCODE_VCP_BACKLIGHT_FOR_BS          0xF8
#define _DDCCI_OPCODE_VCP_RESET_FOR_BS              0xFF
#endif

#define _DDCCI_OPCODE_VCP_GET_SVNVERSION            0xF9
#define _DDCCI_OPCODE_VCP_MANUFACTURER              0xFD

#if(_OGC_GEN_TYPE == _OGC_GEN_1)
//--------------------------------------------------
// Definitions of Display Calibration Protocol Items
//--------------------------------------------------
// Display Calibration Start
#define _DDCCI_DISP_CALIB_STEP                      4
#define _DDCCI_DISP_CALIB_TYPE                      5
#define _DDCCI_DISP_CALIB_OCC_COLORSPACE            6
#define _DDCCI_DISP_CALIB_HDR_FLAG                  7
#define _DDCCI_DISP_CALIB_TYPE_II                   8

// Display Calibration Save RGB Gain
#define _DDCCI_DISP_CALIB_RGB_GAIN                  5

// Display Calibration Measure Gray Patterns
#define _DDCCI_DISP_CALIB_LUT_LENGTH                5
#define _DDCCI_DISP_CALIB_LUT_ID                    6

// Display Calibration OCC Matrix
#define _DDCCI_DISP_CALIB_OCC_MATRIX                6

// Display Calibration Show Gray1~7 10bit
#define _DDCCI_DISP_CALIB_GRAY_HIGH                 5
#define _DDCCI_DISP_CALIB_GRAY_LOW                  6

// Display Calibration Show Results
#define _DDCCI_DISP_CALIB_FINAL_TYPE                5
#define _DDCCI_DISP_CALIB_OGC_CHKSUM                6
#define _DDCCI_DISP_CALIB_OCC_CHKSUM                7
#define _DDCCI_DISP_CALIB_DICOM_CHKSUM              8
#define _DDCCI_DISP_CALIB_OGC_GAMMA_CT_INFO         9
#define _DDCCI_DISP_CALIB_OGC_RGBGAMMA_CHKSUM       10
#define _DDCCI_DISP_CALIB_DIMMING_OCC_CHKSUM        11
#define _DDCCI_DISP_CALIB_FREESYNC_II_CHKSUM        12
#define _DDCCI_DISP_CALIB_RGB_GAIN_CHKSUM           6
#define _DDCCI_DISP_CALIB_HEADER_CHKSUM             7

#define _DDCCI_DISP_CALIB_END_TYPE                  5

// Display Calibration Verification
#define _DDCCI_DISP_CALIB_VERIFY_RED                5
#define _DDCCI_DISP_CALIB_VERIFY_GREEN              7
#define _DDCCI_DISP_CALIB_VERIFY_BLUE               9

// Display Calibration Set FW Info
#define _DDCCI_DISP_CALIB_FW_INFO                   5

// Display Calibration Set Gamma
#define _DDCCI_DISP_CALIB_INDEX                     5

// Display Calibration Set PCM
#define _DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN          5

// Display Calibration Reply Project Support
#define _DDCCI_DISP_CALIB_OGCOCCDICOM_SUPPORT       2
#define _DDCCI_DISP_CALIB_OGC_TOTAL_GAMMA           3
#define _DDCCI_DISP_CALIB_OGC_TOTAL_CT              4
#define _DDCCI_DISP_CALIB_PANEL_BITNUM              5

// Display Calibration Reply FW Version
#define _DDCCI_DISP_CALIB_FW_VERSION_H              2
#define _DDCCI_DISP_CALIB_FW_VERSION_L              3

// Display Calibration Reply No Tone Mapping Info
#define _DDCCI_DISP_CALIB_MAX_LV                    2
#define _DDCCI_DISP_CALIB_MAX_FRAME_AVE_LV          3
#define _DDCCI_DISP_CALIB_MIN_LV                    4

// Display Calibration Reply FW Mode
#define _DDCCI_DISP_CALIB_FW_SUPPORT                2

// Display Calibration Reply Progress
#define _DDCCI_DISP_CALIB_STRING_1                  2
#define _DDCCI_DISP_CALIB_STRING_2                  3
#define _DDCCI_DISP_CALIB_STRING_3                  4
#define _DDCCI_DISP_CALIB_STRING_4                  5

// Save Headers
#define _OGC_HEADER_IF_DO_OGC                       5
#define _OGC_HEADER_GAMMA_CT_INDEX                  6
#define _OCC_HEADER_IF_DO_OCC                       (6 + 2 + _OGC_TOTAL_CT + _OGC_TOTAL_GAMMA)
#define _OCC_HEADER_MATRIX_NUMBER                   (_OCC_HEADER_IF_DO_OCC + 1)
#define _DICOM_HEADER_IF_DO_DICOM                   (_OCC_HEADER_MATRIX_NUMBER + 1)
#define _DICOM_HEADER_MODE                          (_DICOM_HEADER_IF_DO_DICOM + 1)
#define _WHITE_LV_HEADER                            (_DICOM_HEADER_MODE + 1)

// Display Calibration Write Uniformity LUT
#define _DDCCI_DISP_CALIB_UNIFORMITY_INDEX          5
#define _DDCCI_DISP_CALIB_UNIFORMITY_CHKSUM         6
// Save HDR IG LUT
#define _DDCCI_DISP_CALIB_IGLUT_INDEX               5
#define _DDCCI_DISP_CALIB_IGLUT_START               6
#define _DDCCI_DISP_CALIB_HDRMATRIX_START           5
#define _DDCCI_DISP_CALIB_SET_HDR_IG_INDEX          5
#define _DDCCI_DISP_CALIB_SET_HDR_COLOR_MATRIX      6
#define _DDCCI_DISP_CALIB_HDR10_NOTM_BOUND_INDEX    5

#define _DDCCI_DISP_CALIB_COLORMATRIX_TYPE          5
#define _DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM      6

#define _DDCCI_DISP_CALIB_COLORMATRIX2_TYPE         5
#define _DDCCI_DISP_CALIB_COLORMATRIX2_NUM          6
#define _DDCCI_DISP_CALIB_COLORMATRIX2_CHECKSUM     7

// Local Dimming Command Type
#define _DIMMING_COMMAND_SAVE_IG                    0
#define _DIMMING_COMMAND_SAVE_GAIN                  1
#define _DIMMING_COMMAND_SET_GAMMMA                 2

//Save Freesync II EDID info
#define _DDCCI_DISP_CALIB_EDID_INDEX                5
#define _DDCCI_DISP_CALIB_FREESYNC_II_IGLUT_INDEX   5
#define _DDCCI_DISP_CALIB_FREESYNC_II_IGLUT_START   6
#define _DDCCI_DISP_CALIB_FREESYNC_II_MATRIX_START  5

//Save DIMMING NOTM DCR THD
#define _DDCCI_DISP_CALIB_NOTM_DCR_THD_INDEX        5

//Set Backlight
#define _DDCCI_DISP_CALIB_BACKLIGHT_INDEX           5

// Set Boost
#define _DDCCI_DISP_CALIB_BOOST_INDEX               5

//OGC OCC all mode Lv Ratio Data
#define _DDCCI_DISP_CALIB_LVRATIO_INDEX             5

// OCC Multi Panel Color Matching Data Access
#define _DDCCI_DISP_CALIB_COLOR_MATCHING_INDEX      5

// dimming Data start index
#define _DDCCI_DISP_DIMMING_TYPE_LOCAL              0
#define _DDCCI_DISP_DIMMING_TYPE_GLOBAL             1
#define _DDCCI_DISP_CALIB_DIMMING_INDEX             5
#define _DDCCI_DISP_CALIB_DIMMING_DATA_START        6

//Get Panel Info Command Type
#define _DDCCI_DISP_CALIB_GET_FW_VERSION            1
#define _DDCCI_DISP_CALIB_GET_PANEL_LV_INFO         2
#define _DDCCI_DISP_CALIB_GET_UNIFORMITY_FW_VERSION 3
#define _DDCCI_DISP_CALIB_GET_FW_SUPPORT            4

// LD Boost Command Type
#define _DDCCI_DISP_CALIB_BOOST_OFF                 0
#define _DDCCI_DISP_CALIB_BOOST_ON                  1

// OCC Multi Panel Color Matching Data COMMAND
#define _DDCCI_DISP_CALIB_COLOR_MATCHING_WRITE      0
#define _DDCCI_DISP_CALIB_COLOR_MATCHING_READ       1
#define _DDCCI_DISP_CALIB_COLOR_MATCHING_ERASE      2

//--------------------------------------------------
// Definitions of Display Calibration Opcode
//--------------------------------------------------
#define _DDCCI_DISP_CALIB_OGC_MEASURE_RED           0x00
#define _DDCCI_DISP_CALIB_OGC_MEASURE_BLACK         0x01
#define _DDCCI_DISP_CALIB_OGC_MEASURE_BLUE          0x02
#define _DDCCI_DISP_CALIB_OGC_MEASURE_GREEN         0x03
#define _DDCCI_DISP_CALIB_OGC_MEASURE_WHITE         0x04
#define _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1         0x05
#define _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY2         0x06
#define _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY3         0x07
#define _DDCCI_DISP_CALIB_OGC_MEASURE_LAST_GRAY     0x14
#define _DDCCI_DISP_CALIB_OGC_MEASURE_END           0xAA
#define _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1TO7      0xA0

#define _DDCCI_DISP_CALIB_END                       0x8F

#define _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1         0x1D
#define _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB7         0x23
#define _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB21        0x31

#define _DDCCI_DISP_CALIB_OGC_VERIFY_END            0x48
#define _DDCCI_DISP_CALIB_OCC_VERIFY_END            0x50

#define _DDCCI_DISP_CALIB_VERIFICATION              0xBB
#define _DDCCI_DISP_CALIB_SET_GAMMA                 0xCC
#define _DDCCI_DISP_CALIB_SET_PCM                   0xDD
#define _DDCCI_DISP_CALIB_SET_DICOM                 0xEE
#define _DDCCI_DISP_CALIB_GET_DEFINE                0xFF

#define _DDCCI_DISP_CALIB_MEASURE_BG                0xAB
#define _DDCCI_DISP_CALIB_BG_OFF                    0xAC
#define _DDCCI_DISP_CALIB_GET_FW_INFO               0xAD

#define _DDCCI_DISP_CALIB_SAVE_IGLUT                0xBC
#define _DDCCI_DISP_CALIB_SAVE_HDR_MATRIX           0xBD
#define _DDCCI_DISP_CALIB_CHK_COLORMATRIX           0xBE
#define _DDCCI_DISP_CALIB_SET_HDR_MODE              0xBF

#define _DDCCI_DISP_CALIB_LD_COMMAND                0xC0
#define _DDCCI_DISP_CALIB_LD_BOOST_COMMAND          0xC1

#define _DDCCI_DISP_CALIB_SET_BACKLIGHT             0xCD

#define _DDCCI_DISP_CALIB_SAVE_FREESYNC_II_IGLUT    0xDB
#define _DDCCI_DISP_CALIB_SAVE_PANEL_NATIVE_MATRIX  0xDC
#define _DDCCI_DISP_CALIB_SET_FREESYNC_II           0xDE
#define _DDCCI_DISP_CALIB_SAVE_EDID_INFO            0xDF
#define _DDCCI_DISP_CALIB_SAVE_HDR10_NOTM_BOUNG     0xD0
#define _DDCCI_DISP_CALIB_FREESYNC_II_MEASURE_WHITE 0xD1
#define _DDCCI_DISP_CALIB_SAVE_NOTM_DCR_THD         0xD2
#define _DDCCI_DISP_CALIB_PANEL_COLOR_MATCHING_DATA 0xD3
#define _DDCCI_DISP_CALIB_PANEL_OGCOCC_LVRATIO      0xD4

#if(_UNIFORMITY_SUPPORT == _ON)
#define _DDCCI_DISP_CALIB_UNIFORMITY_GET_OGC_HEADER 0x90
#define _DDCCI_DISP_CALIB_UNIFORMITY_ERASE_FLASH    0x91
#define _DDCCI_DISP_CALIB_UNIFORMITY_SET_GAMMA      0x92
#define _DDCCI_DISP_CALIB_UNIFORMITY_GET_PCM_MATRIX 0x93
#define _DDCCI_DISP_CALIB_UNIFORMITY_WRITE_START    0x94
#define _DDCCI_DISP_CALIB_UNIFORMITY_WRITE          0x95
#define _DDCCI_DISP_CALIB_UNIFORMITY_WRITE_END      0x96
#define _DDCCI_DISP_CALIB_UNIFORMITY_VERIFY_START   0x97
#define _DDCCI_DISP_CALIB_UNIFORMITY_VERIFY_END     0x98
#define _DDCCI_DISP_CALIB_UNIFORMITY_GET_DEFINE     0x99
#define _DDCCI_DISP_CALIB_UNIFORMITY_GET_CCT_GAIN   0x9A
#define _DDCCI_DISP_CALIB_UNIFORMITY_GET_FM_DATA    0x9F
#define _DDCCI_DISP_CALIB_UNIFORMITY_SET_PCM        0xA1
#define _DDCCI_DISP_CALIB_UNIFORMITY_GET_LVRATIO    0xA2
#define _DDCCI_DISP_CALIB_UNIFORMITY_GET_LEVEL_MODE 0xA3

// level0
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#define _DDCCI_DISP_CALIB_UNIFORMITY_W_OFFSET       0x9B
#define _DDCCI_DISP_CALIB_UNIFORMITY_W_OFFSET_END   0x9C
#define _DDCCI_DISP_CALIB_UNIFORMITY_W_DECAY        0x9D
#define _DDCCI_DISP_CALIB_UNIFORMITY_W_DECAY_END    0x9E
#endif// #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
#define _DDCCI_DISP_CALIB_DIMMING_START             0xE0
#define _DDCCI_DISP_CALIB_DIMMING_END               0xE1
#define _DDCCI_DISP_CALIB_DIMMING_CHECKFW           0xE2
#define _DDCCI_DISP_CALIB_DIMMING_SETPWM            0xE3
#define _DDCCI_DISP_CALIB_DIMMING_SHOW_WHITE        0xE4
#define _DDCCI_DISP_CALIB_DIMMING_SHOW_BLACK        0xE5
#endif


#elif(_OGC_GEN_TYPE == _OGC_GEN_0)
//--------------------------------------------------
// Definitions of Display Calibration Protocol Items
//--------------------------------------------------
#define _SRGB_PRECISION_9BIT                        1
// Display Calibration Start
#define _DDCCI_DISP_CALIB_STEP                      4
#define _DDCCI_DISP_CALIB_TYPE                      5
#define _DDCCI_DISP_CALIB_OCC_COLORSPACE            6

// Display Calibration Reply User Define Type
#define _DDCCI_DISP_CALIB_USER_DEFINE_TYPE          5

// Display Calibration Save RGB Gain
#define _DDCCI_DISP_CALIB_RGB_GAIN                  5

// Display Calibration Measure Gray Patterns
#define _DDCCI_DISP_CALIB_LUT_LENGTH                5
#define _DDCCI_DISP_CALIB_LUT_ID                    6

// Display Calibration OCC Matrix
#define _DDCCI_DISP_CALIB_OCC_MATRIX                6

// Display Calibration Show Results
#define _DDCCI_DISP_CALIB_OGC_CHKSUM                6
#define _DDCCI_DISP_CALIB_OCC_CHKSUM                8
#define _DDCCI_DISP_CALIB_DICOM_CHKSUM              9
#define _DDCCI_DISP_CALIB_OGC_GAMMA_CT_INFO         10

#define _DDCCI_DISP_CALIB_RGB_GAIN_CHKSUM           6

#define _DDCCI_DISP_CALIB_END_TYPE                  5

// Display Calibration Verification
#define _DDCCI_DISP_CALIB_VERIFY_RED                5
#define _DDCCI_DISP_CALIB_VERIFY_GREEN              6
#define _DDCCI_DISP_CALIB_VERIFY_BLUE               7

// Display Calibration Set Gamma
#define _DDCCI_DISP_CALIB_INDEX                     5

// Display Calibration Set PCM
#define _DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN          5

// Display Calibration Reply Project Support
#define _DDCCI_DISP_CALIB_OGCOCCDICOM_SUPPORT       2
#define _DDCCI_DISP_CALIB_OGC_TOTAL_GAMMA           3
#define _DDCCI_DISP_CALIB_OGC_TOTAL_CT              4
#define _DDCCI_DISP_CALIB_PANEL_BITNUM              5

// Display Calibration Reply Progress
#define _DDCCI_DISP_CALIB_STRING_1                  2
#define _DDCCI_DISP_CALIB_STRING_2                  3
#define _DDCCI_DISP_CALIB_STRING_3                  4
#define _DDCCI_DISP_CALIB_STRING_4                  5

#define _DDCCI_DISP_CALIB_COLORMATRIX_TYPE          5
#define _DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM      6

// Display Calibration User Define
#define _DDCCI_DISP_CALIB_USER_DDCCI_LENGTH         0

//--------------------------------------------------
// Definitions of Display Calibration Opcode
//--------------------------------------------------
#define _DDCCI_DISP_CALIB_OGC_MEASURE_RED           0
#define _DDCCI_DISP_CALIB_OGC_MEASURE_BLACK         1
#define _DDCCI_DISP_CALIB_OGC_MEASURE_BLUE          2
#define _DDCCI_DISP_CALIB_OGC_MEASURE_GREEN         3
#define _DDCCI_DISP_CALIB_OGC_MEASURE_WHITE         4
#define _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1         5
#define _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY2         6
#define _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY3         7
#define _DDCCI_DISP_CALIB_OGC_MEASURE_LAST_GRAY     20  // 19 in 17 Gray Pattern. 24 in 22 Gray Pattern, 27 in 25 Gray Pattern;
#define _DDCCI_DISP_CALIB_OGC_MEASURE_END           0xAA

#define _DDCCI_DISP_CALIB_END                       0x8F

#define _DDCCI_DISP_CALIB_SET_HDR_BACKLIGHT         0xCD

#define _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1         29
#define _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB7         35

#define _DDCCI_DISP_CALIB_OGC_VERIFY_END            72
#define _DDCCI_DISP_CALIB_OCC_VERIFY_END            80

#define _DDCCI_DISP_CALIB_VERIFICATION              0xBB
#define _DDCCI_DISP_CALIB_SET_GAMMA                 0xCC
#define _DDCCI_DISP_CALIB_SET_PCM                   0xDD
#define _DDCCI_DISP_CALIB_SET_DICOM                 0xEE
#define _DDCCI_DISP_CALIB_GET_USER_DEFINE           0xF0
#define _DDCCI_DISP_CALIB_GET_DEFINE                0xFF

#define _DDCCI_DISP_CALIB_CHK_COLORMATRIX           0xBE
#endif

#if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE != Gamma_default))  
//--------------------------------------------------
//Definitions of DDCCI On Line Beacon Gamma Auto Processing cmd
//--------------------------------------------------
#define	_DDCCI_GAMMA_ADJUST_SET_ADC_OFFSET                  0x50
#define	_DDCCI_GAMMA_ADJUST_SET_ADC_GAIN                    0x52

#define	_DDCCI_GAMMA_ADJUST_SET_BACKLIGHT_LOW               0x55
#define	_DDCCI_GAMMA_ADJUST_SET_BACKLIGHT_MID               0x56
#define	_DDCCI_GAMMA_ADJUST_SET_BACKLIGHT_HIGH              0x57

#define	_DDCCI_GAMMA_ADJUST_GET_BACKLIGHT_SENSOR_PWM        0x71

#define	_DDCCI_GAMMA_ADJUST_SET_BACKLIGHT                   0x90
#define	_DDCCI_GAMMA_ADJUST_SET_GAMMA_TYPE                  0x91 // 0-Gamma1, 1-Gamma2, 2-Gamma3
#define	_DDCCI_GAMMA_ADJUST_SET_CTEMP_TYPE                  0x92 // 0-9300K, 1-6500K
#define	_DDCCI_GAMMA_ADJUST_SET_AUTO_ADJUST                 0x93
#define	_DDCCI_GAMMA_ADJUST_SET_AUTO_COLOR                  0x94
#define	_DDCCI_GAMMA_ADJUST_SET_CONTRAST                    0x95
#define	_DDCCI_GAMMA_ADJUST_SET_DDCCI2_KEY                  0x96 // Beacon DDC-CI Test Tool

#define	_DDCCI_GAMMA_ADJUST_GET_COMMAND_STATUS              0x98

#define	_DDCCI_GAMMA_ADJUST_SEND_GAMMA_RGB_VALUE            0x99

#define	_DDCCI_GAMMA_ADJUST_GET_DICOM_SUPPORT               0x9A
#define	_DDCCI_GAMMA_ADJUST_SAVE_DICOM_BACKLIGHT            0x9B
#define	_DDCCI_GAMMA_ADJUST_SET_DICOM_TYPE                  0x9C
#define	_DDCCI_GAMMA_ADJUST_SET_DICOM_BACKLIGHT             0x9D


#define _DDCCI_GAMMA_ADJUST_GET_FAC_MONITOR_SN              0x9E
#define _DDCCI_GAMMA_ADJUST_SET_FAC_MONITOR_SN              0x9F

#define _DDCCI_GAMMA_ADJUST_SET_MONITOR_EDID_IDSN           0xA0
#define _DDCCI_GAMMA_ADJUST_GET_MONITOR_EDID_IDSN           0xA1

#define _DDCCI_GAMMA_ADJUST_SET_GAMMA_BYPASS                0xA3 // 1-Bypass Enable, 0-Bypass Disable              

#define _DDCCI_GAMMA_ADJUST_SET_EDID_PROTECT_EXT_EEPROM     0xA6 // 1-WP Enable, 0-WP Disable
#define _DDCCI_GAMMA_ADJUST_SET_EDID_BANKSEL_EXT_EEPROM     0xA7 

#define _DDCCI_GAMMA_ADJUST_SET_PANEL_LUX_AB_COEFFICENT     0xA8 // Set Backlight A,B Value
#define _DDCCI_GAMMA_ADJUST_GET_PANEL_LUX_AB_COEFFICENT     0xAB // Get Backlight A,B Value
#define _DDCCI_GAMMA_ADJUST_GET_BK_SENSOR_TO_PANEL_LUX      0xA9
#define _DDCCI_GAMMA_ADJUST_SET_PANEL_LUX_RANGE_PARAMTER    0xAA
#define _DDCCI_GAMMA_ADJUST_GET_PANEL_LUX_RANGE_PARAMTER    0xAC

#define _DDCCI_GAMMA_ADJUST_SET_LOCAL_ENHANCEMENT_ON_OFF    0xE0 
#define _DDCCI_GAMMA_ADJUST_SET_ENHANCEMENT_HVPOS_TYPE1     0xE1 
#define _DDCCI_GAMMA_ADJUST_SET_ENHANCEMENT_HVPOS_TYPE2     0xE2 
#define _DDCCI_GAMMA_ADJUST_SET_ENHANCEMENT_HVPOS_ZOOM      0xE3 

#define _DDCCI_GAMMA_ADJUST_SET_AMBI_DICOM_BACKLIGHT        0xEE  
#define _DDCCI_GAMMA_ADJUST_GET_AMBI_DICOM_BACKLIGHT        0xEF  

#define _DDCCI_GAMMA_ADJUST_ENTER_BRUNIN                    0xF0  
#else
#define	_DDCCI_OPCODE_FACTORY_GET_BACKLIGHT_SENSOR_PWM      0x71
#define _DDCCI_OPCODE_FACTORY_SET_BACKLIGHT                 0x90
#define _DDCCI_OPCODE_FACTORY_SET_GAMMA_TYPE                0x91
#define _DDCCI_OPCODE_FACTORY_SET_CTEMP_TYPE                0x92
#define _DDCCI_OPCODE_FACTORY_SET_CONTRAST                  0x95
#define _DDCCI_OPCODE_FACTORY_SET_KEY                       0x96
#define	_DDCCI_OPCODE_FACTORY_GET_COMMAND_STATUS            0x98
#endif

#if(_HDMI_SPLITTER_1X2_EN == _ON)
#define _DDCCI_OPCODE_HDMISPLITTER_GET_DATA                 0x60
#define _DDCCI_OPCODE_HDMISPLITTER_SET_PORTACONTROL         0x61
#define _DDCCI_OPCODE_HDMISPLITTER_SET_EQUALIZATION         0x62
#define _DDCCI_OPCODE_HDMISPLITTER_SET_PORTBCONTROL         0x63
#endif

//--------------------------------------------------
//Definitions of DDCCI Update Gamma Data process cmd
//--------------------------------------------------
#define _DDCCI_UPATE_GAMMA_GET_GAMMA_INDEX                  0x8F
#define _DDCCI_UPATE_GAMMA_GET_GAMMA_NUMS                   0x90
#define _DDCCI_UPATE_GAMMA_SET_GAMMA_INDEX                  0x91
#define _DDCCI_UPATE_GAMMA_SET_GAMMA_DATA                   0x92
#define _DDCCI_UPATE_GAMMA_SEND_DATA_FINISH                 0x93

#define _DDCCI_UPATE_GAMMA_GET_BACKLIGTH_THREE_POINT        0xA0
#define _DDCCI_UPATE_GAMMA_SET_BACKLIGTH_MIN                0xA1
#define _DDCCI_UPATE_GAMMA_SET_BACKLIGTH_MID                0xA2
#define _DDCCI_UPATE_GAMMA_SET_BACKLIGTH_MAX                0xA3

#define _DDCCI_UPATE_GAMMA_CHECK_COMMAN_STATUS              0xA9

#define _DDCCI_UPATE_GAMMA_SET_MONITOR_SN                   0xC2


