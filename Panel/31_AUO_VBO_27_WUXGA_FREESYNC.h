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

#if(_PANEL_TYPE == _AUO_VBO_27_WUXGA_FREESYNC)
//----------------------------------------------------------------------------------------------------
// ID Code      : _AUO_VBO_27_WUXGA_FREESYNC.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_VBO

//--------------------------------------------------
// Definitions for VBO Panel Configuration
//--------------------------------------------------
#define _VBO_BYTE_MODE                          _VBO_DISP_3_BYTE_MODE
#define _VBO_OUTPUT_PORT                        _VBO_8_DATA_LANE
#define _VBO_BIT_MODE                           _VBO_DISP_24_BIT
#define _VBO_PANEL_SECTION                      _VBO_PANEL_2_SECTION
#define _VBO_HS_CONTROL                         _VBO_HS_NORMAL
#define _VBO_VS_CONTROL                         _VBO_VS_NORMAL
#define _VBO_VIDEO_TRANSFER_TYPE                _VBO_VIDEO_TRANSFER_IN_VERTICAL_BLANK
#define _CDR_TRANSFER_ALN_LATENCY               0

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_AUO

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   2000
#define _PANEL_MAX_FRAME_RATE                   2400
#define _PANEL_MIN_FRAME_RATE                   480

//--------------------------------------------------
// Definitions for FREESYNC Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_FREESYNC_MAX_FRAME_RATE          2400
#define _PANEL_FREESYNC_MIN_FRAME_RATE          480


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48
#define _PANEL_DH_WIDTH                         1920
#define _PANEL_DH_END                           1968

#define _PANEL_DH_TOTAL                         2160
#define _PANEL_DH_TOTAL_MAX                     4088
#define _PANEL_DH_TOTAL_MIN                     2152

#define _PANEL_DV_START                         6
#define _PANEL_DV_HEIGHT                        1080
#define _PANEL_DV_END                           1086

#define _PANEL_DV_TOTAL                         1315
#define _PANEL_DV_TOTAL_MAX                     6600
#define _PANEL_DV_TOTAL_MIN                     1100

#define _PANEL_DH_SYNC_WIDTH                    8
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      568
#define _PANEL_PIXEL_CLOCK_MAX                  620
#define _PANEL_PIXEL_CLOCK_MIN                  536


#define _PANEL_POWER_ON_T1                      10
#define _PANEL_POWER_ON_T2                      40
#define _PANEL_POWER_ON_T3                      610

#define _PANEL_POWER_OFF_T4                     130
#define _PANEL_POWER_OFF_T5                     20
#define _PANEL_POWER_OFF_T6                     1100


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _LAST_LINE_TARGET                       (_PANEL_DH_TOTAL - 300)

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _FRAME_SYNC_MARGIN                      20

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ


///////////////////////////
// Color Characteristics //
///////////////////////////



/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include "./RTDColorDefaultTable/ColorTableInclude.h"

#define _DEVICE_LED_DRIVER_TYPE                 _DEVICE_LED_DRIVER_01_O2_OZ9913
#define _PANEL_MAX_LUMINANCE                    0x66 // from OGC Tool
#define _PANEL_MAX_FRAME_AVERAGE_LUMINANCE      0x66 // from OGC Tool
#define _PANEL_MAX_USER_DEFINE_LUMINANCE        0x62 // from OGC Tool


#define _PANEL_PWM_LOCAL_1                      _DEVICE_LED_DRIVER_PWM_4
#define _PANEL_PWM_LOCAL_2                      _DEVICE_LED_DRIVER_PWM_3
#define _PANEL_PWM_LOCAL_3                      _DEVICE_LED_DRIVER_PWM_2
#define _PANEL_PWM_LOCAL_4                      _DEVICE_LED_DRIVER_PWM_1
#define _PANEL_PWM_LOCAL_5                      _DEVICE_LED_DRIVER_PWM_8
#define _PANEL_PWM_LOCAL_6                      _DEVICE_LED_DRIVER_PWM_7
#define _PANEL_PWM_LOCAL_7                      _DEVICE_LED_DRIVER_PWM_6
#define _PANEL_PWM_LOCAL_8                      _DEVICE_LED_DRIVER_PWM_5
#define _PANEL_PWM_LOCAL_9                      _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_10                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_11                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_12                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_13                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_14                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_15                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_16                     _DEVICE_LED_DRIVER_PWM_NONE
#define _PANEL_PWM_LOCAL_ALL                    _DEVICE_LED_DRIVER_PWM_ALL

#define _PANEL_PWM_LOCAL_START                  _DEVICE_LED_DRIVER_PWM_1
#define _PANEL_PWM_LOCAL_END                    _DEVICE_LED_DRIVER_PWM_8

//--------------------------------------------------
// Definitions for Global Dimming
//--------------------------------------------------
#include "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/GDPanelPara.h"
#define _GD_STEP_R_TABLE                        "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tStepRTable.h"
#define _GD_PWM_LUT_TABLE                       "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tPWMLUT.h"

#define _GD_HDR_TONE_MAPPING_LV540              "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tHDRToneMappingLv540.h"
#define _GD_HDR_2084_LV                         "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tHDR2084Lv.h"
#define _GD_SDR_GAMMA_22_LV                     "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tSDRGamma22Lv.h"
#define _GD_SDR_GAMMA_24_LV                     "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tSDRGamma24Lv.h"
#define _GD_SDR_GAMMA_26_LV                     "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tSDRGamma26Lv.h"
#define _GD_SDR_OGC_CASE_1_LV                   "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tSDROGCCase1Lv.h"
#define _GD_SDR_OGC_CASE_2_LV                   "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tSDROGCCase2Lv.h"
#define _GD_SDR_OGC_CASE_3_LV                   "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tSDROGCCase3Lv.h"
#define _GD_SDR_OGC_CASE_4_LV                   "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tSDROGCCase4Lv.h"
#define _GD_SDR_OGC_CASE_5_LV                   "./RTDGlobalDimmingTable/31_AUO_VBO_27_WUXGA_FREESYNC/tSDROGCCase5Lv.h"

#endif // End of #if(_PANEL_TYPE == _AUO_VBO_27_WUXGA_FREESYNC)
