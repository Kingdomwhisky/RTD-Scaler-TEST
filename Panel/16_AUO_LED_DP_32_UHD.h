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

#if(_PANEL_TYPE == _AUO_LED_DP_32_UHD)
//----------------------------------------------------------------------------------------------------
// ID Code      : _AUO_LED_DP_32_UHD.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_DPTX

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_8

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_SAMSUNG

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_30_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   610
#define _PANEL_MIN_FRAME_RATE                   590


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48
#define _PANEL_DH_WIDTH                         3840
#define _PANEL_DH_END                           3888

#define _PANEL_DH_TOTAL                         4200
#define _PANEL_DH_TOTAL_MAX                     4352
#define _PANEL_DH_TOTAL_MIN                     4072

#define _PANEL_DV_START                         6
#define _PANEL_DV_HEIGHT                        2160
#define _PANEL_DV_END                           2166

#define _PANEL_DV_TOTAL                         2200
#define _PANEL_DV_TOTAL_MAX                     2372
#define _PANEL_DV_TOTAL_MIN                     2180

#define _PANEL_DH_SYNC_WIDTH                    4
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      554
#define _PANEL_PIXEL_CLOCK_MAX                  560
#define _PANEL_PIXEL_CLOCK_MIN                  514


#define _PANEL_POWER_ON_T1                      10
#define _PANEL_POWER_ON_T2                      150
#define _PANEL_POWER_ON_T3                      550

#define _PANEL_POWER_OFF_T4                     150
#define _PANEL_POWER_OFF_T5                     40
#define _PANEL_POWER_OFF_T6                     1200


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


////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#define _PANEL_ADC_OFFSET_BIAS                  (0)
#define _PANEL_ADC_GAIN_BIAS                    (0)


///////////////////////////
// Color Characteristics //
///////////////////////////

//--------------------------------------------------
// Definitions for Display HDR
//--------------------------------------------------
#define _PANEL_MAX_LUMINANCE                    0x62 // from OGC Tool
#define _PANEL_MAX_FRAME_AVERAGE_LUMINANCE      0x62 // from OGC Tool
#define _PANEL_MAX_USER_DEFINE_LUMINANCE        0x62 // from OGC Tool

//--------------------------------------------------
// Definitions for FreeSync II Global Backlight Control
//--------------------------------------------------
#define _PANEL_FREESYNC_II_MIN_BACKLIGHT        0x00 // 0x00~0xFF

//--------------------------------------------------
// Definitions for Local Dimming PWM
//--------------------------------------------------
#define _DEVICE_LED_DRIVER_TYPE                 _DEVICE_LED_DRIVER_01_O2_OZ9913
#define _DEVICE_LED_DRIVER_COMMUNICATE_TYPE     _INTERFACE_SPI

#define _PANEL_PWM_SMOOTH_MAX                   ((_PANEL_PWM_DELTA_MAX) / 10)
#define _PANEL_PWM_SMOOTH_MIN                   ((_PANEL_PWM_DELTA_MAX) / 2)
#define _PANEL_PWM_RECOVER_ADJUST_STEPS         (20)
#define _PANEL_REGION_MODE                      _LD_1X8_MODE

#define _PANEL_PWM_LOCAL_1                      _DEVICE_LED_DRIVER_PWM_1
#define _PANEL_PWM_LOCAL_2                      _DEVICE_LED_DRIVER_PWM_2
#define _PANEL_PWM_LOCAL_3                      _DEVICE_LED_DRIVER_PWM_3
#define _PANEL_PWM_LOCAL_4                      _DEVICE_LED_DRIVER_PWM_4
#define _PANEL_PWM_LOCAL_5                      _DEVICE_LED_DRIVER_PWM_5
#define _PANEL_PWM_LOCAL_6                      _DEVICE_LED_DRIVER_PWM_6
#define _PANEL_PWM_LOCAL_7                      _DEVICE_LED_DRIVER_PWM_7
#define _PANEL_PWM_LOCAL_8                      _DEVICE_LED_DRIVER_PWM_8
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

/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include "./RTDColorDefaultTable/ColorTableInclude.h"

#endif // End of #if(_PANEL_TYPE == _AUO_LED_DP_32_UHD)
