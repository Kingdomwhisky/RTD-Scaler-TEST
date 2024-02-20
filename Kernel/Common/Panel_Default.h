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
// ID Code      : Panel_Default.h No.0000
// Update Note  :
//-----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#ifndef _PANEL_STYLE
#define _PANEL_STYLE                            _PANEL_NONE
#endif

//--------------------------------------------------
// Definitions for LVDS Panel Configuration
//--------------------------------------------------
#ifndef _LVDS_OUTPUT_PORT
#define _LVDS_OUTPUT_PORT                       _LVDS_2_PORT
#endif

#ifndef _LVDS_PANEL_SECTION
#define _LVDS_PANEL_SECTION                     _LVDS_PANEL_1_SECTION
#endif

#ifndef _LVDS_TABLE_TYPE
#define _LVDS_TABLE_TYPE                        _LVDS_BIT_MAP_TABLE_1_3
#endif

#ifndef _LVDS_CABLE_TYPE
#define _LVDS_CABLE_TYPE                        _LVDS_CABLE_TYPE_0
#endif

#ifndef _LVDS_PORT_SEL
#define _LVDS_PORT_SEL                          _LVDS_2_PORT_CD
#endif

#ifndef _LVDS_PORT_MIRROR
#define _LVDS_PORT_MIRROR                       _DISABLE
#endif

#ifndef _LVDS_PORT_AB_SWAP
#define _LVDS_PORT_AB_SWAP                      _DISABLE
#endif

#ifndef _LVDS_PORT_CD_SWAP
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#endif

#ifndef _LVDS_PORT_EF_SWAP
#define _LVDS_PORT_EF_SWAP                      _DISABLE
#endif

#ifndef _LVDS_PORT_GH_SWAP
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#endif

#ifndef _LVDS_PN_SWAP
#define _LVDS_PN_SWAP                           _DISABLE
#endif

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#ifndef _PANEL_DPTX_LINK_RATE
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR
#endif

#ifndef _PANEL_DPTX_LANE_NUMBER
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_4
#endif

#ifndef _PANEL_DPTX_PORT_NUMBER_SEL
#define _PANEL_DPTX_PORT_NUMBER_SEL             _DPTX_TX1_PORT
#endif

#ifndef _PANEL_DPTX_VENDOR_SPECIFIC_TYPE
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        _PANEL_DPTX_VENDOR_SPECIFIC_NONE
#endif

#ifndef _PANEL_DPTX_LINK_SEQUENCE_SWAP
#define _PANEL_DPTX_LINK_SEQUENCE_SWAP          _OFF
#endif

#ifndef _PANEL_DPTX_SCRAMBLE_SEED_TYPE
#define _PANEL_DPTX_SCRAMBLE_SEED_TYPE          _PANEL_DPTX_SCRAMBLE_SEED_AUTO
#endif

#ifndef _PANEL_DPTX_SET_LT_SIGNAL_LEVEL_MODE
#define _PANEL_DPTX_SET_LT_SIGNAL_LEVEL_MODE    _PANEL_DPTX_LT_MANUAL_MODE
#endif

#ifndef _PANEL_DPTX_FORCE_OUTPUT_SUPPORT
#define _PANEL_DPTX_FORCE_OUTPUT_SUPPORT        _OFF
#endif

#ifndef _PANEL_DPTX_LT_TPS3_SUPPORT_BY_USER
#define _PANEL_DPTX_LT_TPS3_SUPPORT_BY_USER     _ON
#endif

#ifndef _PANEL_DPTX_AUX_SET_TP_END_SEQUENCE
#define _PANEL_DPTX_AUX_SET_TP_END_SEQUENCE     _TRAIN_PATTERN_END_BEFORE_IDEL_PATTERN
#endif

#ifndef _PANEL_DPTX_HPD_DETECT
#define _PANEL_DPTX_HPD_DETECT                  _OFF
#endif

#ifndef _PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN
#define _PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN    _DISABLE
#endif

//--------------------------------------------------
// Definitions for OLED Panel Backlight Control Mode
//--------------------------------------------------
#ifndef _OLED_PANEL_BACKLIGHT_AUX_CONTROL
#define _OLED_PANEL_BACKLIGHT_AUX_CONTROL       _OFF
#endif

//--------------------------------------------------
// Definitions for TTL Panel Configuration
//--------------------------------------------------
#ifndef _TTL_OUTPUT_PORT
#define _TTL_OUTPUT_PORT                        _TTL_2_PORT
#endif

//--------------------------------------------------
// Definitions for VBO Panel Configuration
//--------------------------------------------------
#ifndef _VBO_BYTE_MODE
#define _VBO_BYTE_MODE                          _VBO_DISP_4_BYTE_MODE
#endif

#ifndef _VBO_OUTPUT_PORT
#define _VBO_OUTPUT_PORT                        _VBO_8_DATA_LANE
#endif

#ifndef _VBO_BIT_MODE
#define _VBO_BIT_MODE                           _VBO_DISP_30_BIT
#endif

#ifndef _VBO_PANEL_SECTION
#define _VBO_PANEL_SECTION                      _VBO_PANEL_1_SECTION
#endif

#ifndef _VBO_HS_CONTROL
#define _VBO_HS_CONTROL                         _VBO_HS_NORMAL
#endif

#ifndef _VBO_VS_CONTROL
#define _VBO_VS_CONTROL                         _VBO_VS_NORMAL
#endif

#ifndef _VBO_VIDEO_TRANSFER_TYPE
#define _VBO_VIDEO_TRANSFER_TYPE                _VBO_VIDEO_TRANSFER_IN_VERTICAL_BLANK
#endif

#ifndef _CDR_TRANSFER_ALN_LATENCY
#define _CDR_TRANSFER_ALN_LATENCY               0
#endif

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#ifndef _PANEL_EXIST_MULTIPANEL
#define _PANEL_EXIST_MULTIPANEL                 _OFF
#endif

#ifndef _PANEL_MULTIPANEL_VARIABLE
#define _PANEL_MULTIPANEL_VARIABLE              _OFF
#endif

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#ifndef _PANEL_MANUFACTURER
#define _PANEL_MANUFACTURER                     _PANEL_NONE_BRAND
#endif

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#ifndef _PANEL_DISP_BIT_MODE
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT
#endif

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#ifndef _PANEL_TYP_FRAME_RATE
#define _PANEL_TYP_FRAME_RATE                   600
#endif

#ifndef _PANEL_MAX_FRAME_RATE
#define _PANEL_MAX_FRAME_RATE                   860
#endif

#ifndef _PANEL_MIN_FRAME_RATE
#define _PANEL_MIN_FRAME_RATE                   460
#endif

//--------------------------------------------------
// Definitions for FREESYNC Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#ifndef _PANEL_FREESYNC_MAX_FRAME_RATE
#define _PANEL_FREESYNC_MAX_FRAME_RATE          1440
#endif

#ifndef _PANEL_FREESYNC_MIN_FRAME_RATE
#define _PANEL_FREESYNC_MIN_FRAME_RATE          300
#endif


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#ifndef _PANEL_DH_START
#define _PANEL_DH_START                         48                  // Display Horizontal Start Position
#endif

#ifndef _PANEL_DH_WIDTH
#define _PANEL_DH_WIDTH                         1920                // Display Horizontal Width
#endif

#ifndef _PANEL_DH_END
#define _PANEL_DH_END                           1968                // Display Horizontal End Position
#endif

#ifndef _PANEL_DH_TOTAL
#define _PANEL_DH_TOTAL                         2100                // Display Horizontal Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DH_TOTAL_MAX
#define _PANEL_DH_TOTAL_MAX                     2200                // Maxinum Display Horizontal Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DH_TOTAL_MIN
#define _PANEL_DH_TOTAL_MIN                     2048                // Mininum Display Horizontal Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DV_START
#define _PANEL_DV_START                         6                   // Display Vertical Start Position
#endif

#ifndef _PANEL_DV_HEIGHT
#define _PANEL_DV_HEIGHT                        1080                // Display Vertical Width
#endif

#ifndef _PANEL_DV_END
#define _PANEL_DV_END                           1086                // Display Vertical End Position
#endif

#ifndef _PANEL_DV_TOTAL
#define _PANEL_DV_TOTAL                         1150                // Display Vertical Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DV_TOTAL_MAX
#define _PANEL_DV_TOTAL_MAX                     1600                // Maxinum Display Vertical Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DV_TOTAL_MIN
#define _PANEL_DV_TOTAL_MIN                     1100                // Mininum Display Vertical Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DH_SYNC_WIDTH
#define _PANEL_DH_SYNC_WIDTH                    8                   // Display Horizontal Sync Width
#endif

#ifndef _PANEL_DV_SYNC_HEIGHT
#define _PANEL_DV_SYNC_HEIGHT                   2                   // Display Vertical Sync Height
#endif

#ifndef _PANEL_PIXEL_CLOCK
#define _PANEL_PIXEL_CLOCK                      144                 // Typical Pixel Clock in MHz
#endif

#ifndef _PANEL_PIXEL_CLOCK_MAX
#define _PANEL_PIXEL_CLOCK_MAX                  230                 // Maxinum Pixel Clock in MHz
#endif

#ifndef _PANEL_PIXEL_CLOCK_MIN
#define _PANEL_PIXEL_CLOCK_MIN                  110                 // Mininum Pixel Clock in MHz
#endif

#ifndef _PANEL_POWER_ON_T1
#define _PANEL_POWER_ON_T1                      100                 // Panel Power On T1 (ms)
#endif

#ifndef _PANEL_POWER_ON_T2
#define _PANEL_POWER_ON_T2                      40                  // Panel Power On T2 (ms)
#endif

#ifndef _PANEL_POWER_ON_T3
#define _PANEL_POWER_ON_T3                      300                 // Panel Power On T3 (ms)
#endif

#ifndef _PANEL_POWER_OFF_T4
#define _PANEL_POWER_OFF_T4                     20                  // Panel Power Off T4 (ms)
#endif

#ifndef _PANEL_POWER_OFF_T5
#define _PANEL_POWER_OFF_T5                     40                  // Panel Power Off T5 (ms)
#endif

#ifndef _PANEL_POWER_OFF_T6
#define _PANEL_POWER_OFF_T6                     600                 // Panel Power Off T6 (ms)
#endif

#ifndef _PANEL_POWER_ON_BL_TO_PWM               
#define _PANEL_POWER_ON_BL_TO_PWM               50                  // backlight onoff to pwm delay
#endif

#ifndef _PANEL_POWER_OFF_PWM_TO_BL               
#define _PANEL_POWER_OFF_PWM_TO_BL              50                  // pwm to backlight onoff delay
#endif

#ifndef _PANEL_PWM_BEFORE_BL_CONTROL               
#define _PANEL_PWM_BEFORE_BL_CONTROL            _OFF                // pwm before backlight onoff control
#endif

/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Enable
//--------------------------------------------------
#ifndef _LAST_LINE_FINETUNE_ENABLE
#define _LAST_LINE_FINETUNE_ENABLE              _ENABLE
#endif


//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#ifndef _LAST_LINE_TARGET
#define _LAST_LINE_TARGET                       (_PANEL_DH_TOTAL - 150)
#endif

//--------------------------------------------------
// MN Frame Tracking Fine Tune Last Line
//--------------------------------------------------
#ifndef _MN_FINE_TUNE_LASTLINE_SUPPORT
#define _MN_FINE_TUNE_LASTLINE_SUPPORT          _OFF
#endif

#ifndef _MN_LAST_LINE_MAX
#define _MN_LAST_LINE_MAX                       (_LAST_LINE_TARGET + 25)
#endif

#ifndef _MN_LAST_LINE_MIN
#define _MN_LAST_LINE_MIN                       (_LAST_LINE_TARGET - 25)
#endif

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#ifndef _FRAME_SYNC_MARGIN
#define _FRAME_SYNC_MARGIN                      0
#endif

//--------------------------------------------------
// Definitions for panel DVtotal adjust limit
//--------------------------------------------------
#ifndef _PANEL_DV_LINE_CHG_LIMIT
#define _PANEL_DV_LINE_CHG_LIMIT                (_PANEL_DV_TOTAL)
#endif

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#ifndef _PANEL_PIXEL_CLOCK_UNIT
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ
#endif

//--------------------------------------------------
// Definitions for fine tune margin Frame Sync line buffer dvtotal
//--------------------------------------------------
#ifndef _PANEL_DV_TOTAL_FINE_TUNE_MARGIN
#define _PANEL_DV_TOTAL_FINE_TUNE_MARGIN        1
#endif

//--------------------------------------------------
// Definitions for video compensation
//--------------------------------------------------
#ifndef BYPASS_VIDEO_COMPENSATION
#define BYPASS_VIDEO_COMPENSATION(Vin, Vout)    (_FALSE)
#endif

//--------------------------------------------------
// Definitions for rotation pass
//--------------------------------------------------
#ifndef _DISPLAY_ROTATION_SET_ROTATION_PASS
#define _DISPLAY_ROTATION_SET_ROTATION_PASS     _OFF
#endif

////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#ifndef _PANEL_ADC_OFFSET_BIAS
#define _PANEL_ADC_OFFSET_BIAS                  (0) // 0~5
#endif

#ifndef _PANEL_ADC_GAIN_BIAS
#define _PANEL_ADC_GAIN_BIAS                    (0) // -5~0
#endif


///////////////////////////
// Color Characteristics //
///////////////////////////
//--------------------------------------------------
// HDR10 Option
//--------------------------------------------------
#ifndef _PANEL_MAX_LUMINANCE
#define _PANEL_MAX_LUMINANCE                    0x62 // from OGC Tool
#endif

#ifndef _PANEL_MAX_FRAME_AVERAGE_LUMINANCE
#define _PANEL_MAX_FRAME_AVERAGE_LUMINANCE      0x62 // from OGC Tool
#endif

#ifndef _PANEL_MAX_USER_DEFINE_LUMINANCE
#define _PANEL_MAX_USER_DEFINE_LUMINANCE        0x62 // from OGC Tool
#endif

//--------------------------------------------------
// FreeSync II Global Backlight Control Option
//--------------------------------------------------
#ifndef _PANEL_FREESYNC_II_MIN_BACKLIGHT
#define _PANEL_FREESYNC_II_MIN_BACKLIGHT        0x00 // 0x00~0xFF
#endif

//--------------------------------------------------
// I Dither Option
//--------------------------------------------------
#ifndef _I_DITHER_TEMP
#define _I_DITHER_TEMP                          _ENABLE
#endif

#ifndef _I_DITHER_VALUE_SIGN
#define _I_DITHER_VALUE_SIGN                    _DISABLE
#endif

#ifndef _I_DITHER_V_FRAME_MOD
#define _I_DITHER_V_FRAME_MOD                   _DISABLE
#endif

#ifndef _I_DITHER_H_FRAME_MOD
#define _I_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#ifndef _I_DITHER_MULTI_SEQ_ENABLE
#define _I_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#endif

#ifndef _I_DITHER_SHARE_SEQ_ENABLE
#define _I_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#endif

#ifndef _I_DITHER_SERIES_SEQ_ENABLE
#define _I_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#endif

#ifndef _I_DITHER_SEQ_INV_ENABLE
#define _I_DITHER_SEQ_INV_ENABLE                _DISABLE
#endif

#ifndef _I_DITHER_SEQ_INV_MODE
#define _I_DITHER_SEQ_INV_MODE                  0
#endif

#ifndef _I_DITHER_12_TO_10_TEMP
#define _I_DITHER_12_TO_10_TEMP                 _I_DITHER_TEMP
#endif

#ifndef _I_DITHER_12_TO_10_VALUE_SIGN
#define _I_DITHER_12_TO_10_VALUE_SIGN           _I_DITHER_VALUE_SIGN
#endif

#ifndef _I_DITHER_12_TO_10_V_FRAME_MOD
#define _I_DITHER_12_TO_10_V_FRAME_MOD          _I_DITHER_V_FRAME_MOD
#endif

#ifndef _I_DITHER_12_TO_10_H_FRAME_MOD
#define _I_DITHER_12_TO_10_H_FRAME_MOD          _I_DITHER_H_FRAME_MOD
#endif

#ifndef _I_DITHER_12_TO_10_MULTI_SEQ_ENABLE
#define _I_DITHER_12_TO_10_MULTI_SEQ_ENABLE     _I_DITHER_MULTI_SEQ_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SHARE_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SHARE_SEQ_ENABLE     _I_DITHER_SHARE_SEQ_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SERIES_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SERIES_SEQ_ENABLE    _I_DITHER_SERIES_SEQ_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SEQ_INV_ENABLE
#define _I_DITHER_12_TO_10_SEQ_INV_ENABLE       _I_DITHER_SEQ_INV_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SEQ_INV_MODE
#define _I_DITHER_12_TO_10_SEQ_INV_MODE         _I_DITHER_SEQ_INV_MODE  // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b
#endif

//--------------------------------------------------
// D Dither Option
//--------------------------------------------------
#ifndef _D_DITHER_TEMP
#define _D_DITHER_TEMP                          _ENABLE
#endif

#ifndef _D_DITHER_V_FRAME_MOD
#define _D_DITHER_V_FRAME_MOD                   _DISABLE
#endif

#ifndef _D_DITHER_H_FRAME_MOD
#define _D_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#ifndef _D_DITHER_MULTI_SEQ_ENABLE
#define _D_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#endif

#ifndef _D_DITHER_SHARE_SEQ_ENABLE
#define _D_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#endif

#ifndef _D_DITHER_SEQ_INV_ENABLE
#define _D_DITHER_SEQ_INV_ENABLE                _DISABLE
#endif

#ifndef _D_DITHER_SEQ_INV_MODE
#define _D_DITHER_SEQ_INV_MODE                  0  // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b
#endif

#ifndef _D_DITHER_SERIES_SEQ_ENABLE
#define _D_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#endif

#ifndef _D_DITHER_ADVANCE_SETTING_ENABLE
#define _D_DITHER_ADVANCE_SETTING_ENABLE        _DISABLE
#endif

#ifndef _D_DITHER_FREERUNEN_SUPPORT
#define _D_DITHER_FREERUNEN_SUPPORT             _DISABLE
#endif

#if((_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#ifndef _D_DITHER_SUPER_PIXEL_SIZE
#define _D_DITHER_SUPER_PIXEL_SIZE              ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT) ? _DDITHER_SUPER_PIXEL_4X4 : _DDITHER_SUPER_PIXEL_4X8)
#endif
#elif(_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)
#ifndef _D_DITHER_SUPER_PIXEL_SIZE
#define _D_DITHER_SUPER_PIXEL_SIZE              (((_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT) || (_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)) ? _DDITHER_SUPER_PIXEL_4X4 : _DDITHER_SUPER_PIXEL_4X8)
#endif
#endif

#if((_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) || (_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#define _D_DITHER_6BIT_PANEL_FUNC_ENABLE        ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) ? _ENABLE : _DISABLE)
#else
#define _D_DITHER_6BIT_PANEL_FUNC_ENABLE        _DISABLE
#endif

//--------------------------------------------------
// Definitions for Local Dimming PWM
//--------------------------------------------------
#ifndef _DEVICE_LED_DRIVER_TYPE
#define _DEVICE_LED_DRIVER_TYPE                 _DEVICE_LED_DRIVER_NONE
#endif

#ifndef _DEVICE_LED_DRIVER_COMMUNICATE_TYPE
#define _DEVICE_LED_DRIVER_COMMUNICATE_TYPE     _INTERFACE_SPI
#endif

#ifndef _DEVICE_LED_DRIVER_PWM_MAX
#define _DEVICE_LED_DRIVER_PWM_MAX              0x800
#endif

#ifndef _DEVICE_LED_DRIVER_PWM_MIN
#define _DEVICE_LED_DRIVER_PWM_MIN              0x00
#endif

#ifndef _DEVICE_LED_DRIVER_WRITE_SLAVE_ADDRESS
#define _DEVICE_LED_DRIVER_WRITE_SLAVE_ADDRESS  0x40
#endif

#ifndef _PANEL_PWM_SMOOTH_MAX
#define _PANEL_PWM_SMOOTH_MAX                   ((_PANEL_PWM_DELTA_MAX) / 10)
#endif

#ifndef _PANEL_PWM_SMOOTH_MIN
#define _PANEL_PWM_SMOOTH_MIN                   ((_PANEL_PWM_DELTA_MAX) / 2)
#endif

#ifndef _PANEL_PWM_RECOVER_ADJUST_STEPS
#define _PANEL_PWM_RECOVER_ADJUST_STEPS         (20)
#endif

#ifndef _PANEL_REGION_MODE
#define _PANEL_REGION_MODE                      _LD_1X8_MODE
#endif

#ifndef _PANEL_PWM_LOCAL_1
#define _PANEL_PWM_LOCAL_1                      _DEVICE_LED_DRIVER_PWM_8
#endif

#ifndef _PANEL_PWM_LOCAL_2
#define _PANEL_PWM_LOCAL_2                      _DEVICE_LED_DRIVER_PWM_7
#endif

#ifndef _PANEL_PWM_LOCAL_3
#define _PANEL_PWM_LOCAL_3                      _DEVICE_LED_DRIVER_PWM_6
#endif

#ifndef _PANEL_PWM_LOCAL_4
#define _PANEL_PWM_LOCAL_4                      _DEVICE_LED_DRIVER_PWM_5
#endif

#ifndef _PANEL_PWM_LOCAL_5
#define _PANEL_PWM_LOCAL_5                      _DEVICE_LED_DRIVER_PWM_4
#endif

#ifndef _PANEL_PWM_LOCAL_6
#define _PANEL_PWM_LOCAL_6                      _DEVICE_LED_DRIVER_PWM_3
#endif

#ifndef _PANEL_PWM_LOCAL_7
#define _PANEL_PWM_LOCAL_7                      _DEVICE_LED_DRIVER_PWM_2
#endif

#ifndef _PANEL_PWM_LOCAL_8
#define _PANEL_PWM_LOCAL_8                      _DEVICE_LED_DRIVER_PWM_1
#endif

#ifndef _PANEL_PWM_LOCAL_9
#define _PANEL_PWM_LOCAL_9                      _DEVICE_LED_DRIVER_PWM_NONE
#endif

#ifndef _PANEL_PWM_LOCAL_10
#define _PANEL_PWM_LOCAL_10                     _DEVICE_LED_DRIVER_PWM_NONE
#endif

#ifndef _PANEL_PWM_LOCAL_11
#define _PANEL_PWM_LOCAL_11                     _DEVICE_LED_DRIVER_PWM_NONE
#endif

#ifndef _PANEL_PWM_LOCAL_12
#define _PANEL_PWM_LOCAL_12                     _DEVICE_LED_DRIVER_PWM_NONE
#endif

#ifndef _PANEL_PWM_LOCAL_13
#define _PANEL_PWM_LOCAL_13                     _DEVICE_LED_DRIVER_PWM_NONE
#endif

#ifndef _PANEL_PWM_LOCAL_14
#define _PANEL_PWM_LOCAL_14                     _DEVICE_LED_DRIVER_PWM_NONE
#endif

#ifndef _PANEL_PWM_LOCAL_15
#define _PANEL_PWM_LOCAL_15                     _DEVICE_LED_DRIVER_PWM_NONE
#endif

#ifndef _PANEL_PWM_LOCAL_16
#define _PANEL_PWM_LOCAL_16                     _DEVICE_LED_DRIVER_PWM_NONE
#endif

#ifndef _PANEL_PWM_LOCAL_ALL
#define _PANEL_PWM_LOCAL_ALL                    _DEVICE_LED_DRIVER_PWM_ALL
#endif

#ifndef _PANEL_PWM_LOCAL_START
#define _PANEL_PWM_LOCAL_START                  _DEVICE_LED_DRIVER_PWM_1
#endif

#ifndef _PANEL_PWM_LOCAL_END
#define _PANEL_PWM_LOCAL_END                    _DEVICE_LED_DRIVER_PWM_8
#endif

#ifndef _PANEL_LV_MAX
#define _PANEL_LV_MAX                           0x01EC
#endif

#ifndef _PANEL_LV_MIN
#define _PANEL_LV_MIN                           0x007B
#endif

#ifndef _PANEL_LV_DARK_SCENE
#define _PANEL_LV_DARK_SCENE                    0x0046
#endif

#ifndef _PANEL_LV_BOOST_MAX
#define _PANEL_LV_BOOST_MAX                     0x0220
#endif

#ifndef _PANEL_LV_BOOST_MIN
#define _PANEL_LV_BOOST_MIN                     0x0DA
#endif

#ifndef _LOCAL_DIMMING_MAXCLL
#define _LOCAL_DIMMING_MAXCLL                   600
#endif

#ifndef _LOCAL_DIMMING_MAXFALL
#define _LOCAL_DIMMING_MAXFALL                  400
#endif

#ifndef _PANEL_PWM_MAX
#define _PANEL_PWM_MAX                          0x800
#endif

#ifndef _PANEL_PWM_MIN
#define _PANEL_PWM_MIN                          0x56
#endif

#ifndef _REGION0_PWM_TO_LV_OWN
#define _REGION0_PWM_TO_LV_OWN                  4
#endif

#ifndef _REGION0_PWM_TO_LV_REGION1
#define _REGION0_PWM_TO_LV_REGION1              19
#endif

#ifndef _REGION1_PWM_TO_LV_OWN
#define _REGION1_PWM_TO_LV_OWN                  5
#endif

#ifndef _REGION1_PWM_TO_LV_REGION0
#define _REGION1_PWM_TO_LV_REGION0              21
#endif

#ifndef _REGION1_PWM_TO_LV_REGION2
#define _REGION1_PWM_TO_LV_REGION2              20
#endif

#ifndef _REGION2_PWM_TO_LV_OWN
#define _REGION2_PWM_TO_LV_OWN                  5
#endif

#ifndef _REGION2_PWM_TO_LV_REGION1
#define _REGION2_PWM_TO_LV_REGION1              21
#endif

#ifndef _REGION2_PWM_TO_LV_REGION3
#define _REGION2_PWM_TO_LV_REGION3              20
#endif

#ifndef _REGION3_PWM_TO_LV_OWN
#define _REGION3_PWM_TO_LV_OWN                  5
#endif

#ifndef _REGION3_PWM_TO_LV_REGION2
#define _REGION3_PWM_TO_LV_REGION2              20
#endif

#ifndef _REGION3_PWM_TO_LV_REGION4
#define _REGION3_PWM_TO_LV_REGION4              21
#endif

#ifndef _REGION4_PWM_TO_LV_OWN
#define _REGION4_PWM_TO_LV_OWN                  5
#endif

#ifndef _REGION4_PWM_TO_LV_REGION3
#define _REGION4_PWM_TO_LV_REGION3              21
#endif

#ifndef _REGION4_PWM_TO_LV_REGION5
#define _REGION4_PWM_TO_LV_REGION5              21
#endif

#ifndef _REGION5_PWM_TO_LV_OWN
#define _REGION5_PWM_TO_LV_OWN                  5
#endif

#ifndef _REGION5_PWM_TO_LV_REGION4
#define _REGION5_PWM_TO_LV_REGION4              20
#endif

#ifndef _REGION5_PWM_TO_LV_REGION6
#define _REGION5_PWM_TO_LV_REGION6              21
#endif

#ifndef _REGION6_PWM_TO_LV_OWN
#define _REGION6_PWM_TO_LV_OWN                  5
#endif

#ifndef _REGION6_PWM_TO_LV_REGION5
#define _REGION6_PWM_TO_LV_REGION5              19
#endif

#ifndef _REGION6_PWM_TO_LV_REGION7
#define _REGION6_PWM_TO_LV_REGION7              20
#endif

#ifndef _REGION7_PWM_TO_LV_OWN
#define _REGION7_PWM_TO_LV_OWN                  4
#endif

#ifndef _REGION7_PWM_TO_LV_REGION6
#define _REGION7_PWM_TO_LV_REGION6              18
#endif

#ifndef _PANEL_FRONT_PORCH_LIMIT
#define _PANEL_FRONT_PORCH_LIMIT                2
#endif

//--------------------------------------------------
// Definitions for Global dimming table
//--------------------------------------------------
#ifndef _GD_PANEL_PWM_MAX
#define _GD_PANEL_PWM_MAX                       0x800
#endif

#ifndef _GD_PANEL_PWM_MIN
#define _GD_PANEL_PWM_MIN                       0x0FF
#endif

#ifndef _GD_PANEL_PWM_DELTA_MAX
#define _GD_PANEL_PWM_DELTA_MAX                 (_GD_PANEL_PWM_MAX - _GD_PANEL_PWM_MIN)
#endif

#ifndef _GD_PANEL_LV_MAX
#define _GD_PANEL_LV_MAX                        0x140
#endif

#ifndef _GD_PANEL_LV_MIN
#define _GD_PANEL_LV_MIN                        0x046
#endif

#ifndef _GD_STEP_R_TABLE
#define _GD_STEP_R_TABLE                        "ZeroTable.h"
#endif

#ifndef _GD_PWM_LUT_TABLE
#define _GD_PWM_LUT_TABLE                       "ZeroTable.h"
#endif

#ifndef _GD_PWM_LUT_TABLE
#define _GD_PWM_LUT_TABLE                       "ZeroTable.h"
#endif

#ifndef _GD_HDR_TONE_MAPPING_LV540
#define _GD_HDR_TONE_MAPPING_LV540              "ZeroTable.h"
#endif

#ifndef _GD_HDR_2084_LV
#define _GD_HDR_2084_LV                         "ZeroTable.h"
#endif

#ifndef _GD_SDR_GAMMA_22_LV
#define _GD_SDR_GAMMA_22_LV                     "ZeroTable.h"
#endif

#ifndef _GD_SDR_GAMMA_24_LV
#define _GD_SDR_GAMMA_24_LV                     "ZeroTable.h"
#endif

#ifndef _GD_SDR_GAMMA_26_LV
#define _GD_SDR_GAMMA_26_LV                     "ZeroTable.h"
#endif

#ifndef _GD_SDR_OGC_CASE_1_LV
#define _GD_SDR_OGC_CASE_1_LV                   "ZeroTable.h"
#endif

#ifndef _GD_SDR_OGC_CASE_2_LV
#define _GD_SDR_OGC_CASE_2_LV                   "ZeroTable.h"
#endif

#ifndef _GD_SDR_OGC_CASE_3_LV
#define _GD_SDR_OGC_CASE_3_LV                   "ZeroTable.h"
#endif

#ifndef _GD_SDR_OGC_CASE_4_LV
#define _GD_SDR_OGC_CASE_4_LV                   "ZeroTable.h"
#endif

#ifndef _GD_SDR_OGC_CASE_5_LV
#define _GD_SDR_OGC_CASE_5_LV                   "ZeroTable.h"
#endif


//--------------------------------------------------
// Definitions for Local dimming table
//--------------------------------------------------
#ifndef _LD_PANEL_PARA
#define _LD_PANEL_PARA                          "ZeroTable.h"
#endif

#ifndef _LD_STEP_R_TABLE
#define _LD_STEP_R_TABLE                        "ZeroTable.h"
#endif

#ifndef _LD_BASE_LV
#define _LD_BASE_LV                             "ZeroTable.h"
#endif

#ifndef _LD_NODE_LV_MERGED
#define _LD_NODE_LV_MERGED                      "ZeroTable.h"
#endif

#ifndef _LD_UNIFORMITY_LV_MERGED
#define _LD_UNIFORMITY_LV_MERGED                "ZeroTable.h"
#endif

#ifndef _LD_UNIFORMITY_BOOST_LV_MERGED
#define _LD_UNIFORMITY_BOOST_LV_MERGED          "ZeroTable.h"
#endif

#ifndef _LD_FREESYNC_II_LV
#define _LD_FREESYNC_II_LV                      "ZeroTable.h"
#endif

#ifndef _LD_HDR_TONE_MAPPING_LV540
#define _LD_HDR_TONE_MAPPING_LV540              "ZeroTable.h"
#endif

#ifndef _LD_HDR_2084_LV
#define _LD_HDR_2084_LV                         "ZeroTable.h"
#endif

#ifndef _LD_DARK_GAIN
#define _LD_DARK_GAIN                           "ZeroTable.h"
#endif

#ifndef _LD_SDR_GAMMA_22_LV
#define _LD_SDR_GAMMA_22_LV                     "ZeroTable.h"
#endif

#ifndef _LD_SDR_GAMMA_24_LV
#define _LD_SDR_GAMMA_24_LV                     "ZeroTable.h"
#endif

#ifndef _LD_SDR_GAMMA_26_LV
#define _LD_SDR_GAMMA_26_LV                     "ZeroTable.h"
#endif

#ifndef _LD_SDR_OGC_CASE_1_LV
#define _LD_SDR_OGC_CASE_1_LV                   "ZeroTable.h"
#endif

#ifndef _LD_SDR_OGC_CASE_2_LV
#define _LD_SDR_OGC_CASE_2_LV                   "ZeroTable.h"
#endif

#ifndef _LD_SDR_OGC_CASE_3_LV
#define _LD_SDR_OGC_CASE_3_LV                   "ZeroTable.h"
#endif

#ifndef _LD_SDR_OGC_CASE_4_LV
#define _LD_SDR_OGC_CASE_4_LV                   "ZeroTable.h"
#endif

#ifndef _LD_SDR_OGC_CASE_5_LV
#define _LD_SDR_OGC_CASE_5_LV                   "ZeroTable.h"
#endif


