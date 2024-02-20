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
// ID Code      : RL6410_Project_Default.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


/////////////
// General //
/////////////

//--------------------------------------------------
// Pcb Option
//--------------------------------------------------
#ifndef _PCB_TYPE
#define _PCB_TYPE                                               _RL6410_PCB_EXAMPLE
#endif

//--------------------------------------------------
// Panel Option
//--------------------------------------------------
#ifndef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_NONE
#endif

#ifndef _PANEL_POW_SEQ_FAST_MODE
#define _PANEL_POW_SEQ_FAST_MODE                                _ON
#endif

//==================== START ======================
#ifndef _PANEL_POW_SEQ_T6_TIMER_EVENT_MODE
#define _PANEL_POW_SEQ_T6_TIMER_EVENT_MODE                      _OFF
#endif

#ifndef _PANEL_POWER_ON_BEFORE_COLOR_SETTING
#define _PANEL_POWER_ON_BEFORE_COLOR_SETTING                    _OFF
#endif

#ifndef _PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING
#define _PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING                    _OFF
#endif

#ifndef _VBO_BACKLIGHT_BY_USER
#define _VBO_BACKLIGHT_BY_USER                                  _DISABLE
#endif
//===================== END =======================

//--------------------------------------------------
// Osd Option
//--------------------------------------------------
#ifndef _OSD_TYPE
#define _OSD_TYPE                                               _NONE_OSD
#endif

//--------------------------------------------------
// OSD Window & Font Align to DEN Option
//--------------------------------------------------
#ifndef _OSD_POSITION_OFFSET_CORRECTION
#define _OSD_POSITION_OFFSET_CORRECTION                         _OFF
#endif

//--------------------------------------------------
// OSD Position Align Option
//--------------------------------------------------
#ifndef _OSD_POSITION_SELF_ALIGNMENT
#define _OSD_POSITION_SELF_ALIGNMENT                            _OFF
#endif

//==================== START ======================

//--------------------------------------------------
// Scaler or Translator Option
//--------------------------------------------------
#ifndef _TRANSLATOR_SUPPORT
#define _TRANSLATOR_SUPPORT                                     _OFF
#endif

//--------------------------------------------------
// Flash Partition
//--------------------------------------------------
#ifndef _FLASH_PARTITION_TYPE
#define _FLASH_PARTITION_TYPE                                   _FLASH_PARTITION_NONE
#endif

//===================== END =======================


///////////
// DDCCI //
///////////

//-------------------------------------------------
// DDCCI Option
//-------------------------------------------------
#ifndef _DDCCI_RXBUF_LENGTH
#define _DDCCI_RXBUF_LENGTH                                     16
#endif

#ifndef _DDCCI_TXBUF_LENGTH
#define _DDCCI_TXBUF_LENGTH                                     16
#endif

#ifndef _DDCCI_TIMEOUT_LIMIT
#define _DDCCI_TIMEOUT_LIMIT                                    50 // 0~65535ms
#endif

#ifndef _CAPABILITIES_STRING_VGA
#define _CAPABILITIES_STRING_VGA                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_DVI
#define _CAPABILITIES_STRING_DVI                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_HDMI
#define _CAPABILITIES_STRING_HDMI                               "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_DP
#define _CAPABILITIES_STRING_DP                                 "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

//==================== START ======================

//-------------------------------------------------
// DDCCI Auto Switch Option
//-------------------------------------------------
#ifndef _DDCCI_AUTO_SWITCH_SUPPORT
#define _DDCCI_AUTO_SWITCH_SUPPORT                              _OFF
#endif

//-------------------------------------------------
// DDCCI On Line Display Calibration OP Code Option
//-------------------------------------------------
#ifndef _DDCCI_OPCODE_VCP_DISP_CALIBRATION
#define _DDCCI_OPCODE_VCP_DISP_CALIBRATION                      0xFC
#endif

//--------------------------------------------------
// Definitions for custom capability support
//--------------------------------------------------
#ifndef _DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT
#define _DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT                    _OFF
#endif

//===================== END =======================


/////////////////////
// Display Setting //
/////////////////////
//==================== START ======================

//-------------------------------------------------
// I domian and D domain High Speed Option
//-------------------------------------------------
#ifndef _IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT
#define _IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT                    _OFF
#endif

//===================== END =======================

//-------------------------------------------------
// OD Option
//-------------------------------------------------
#ifndef _OD_SUPPORT
#define _OD_SUPPORT                                             _OFF
#endif

//-------------------------------------------------
// FRC Option
//-------------------------------------------------
#ifndef _FRC_SUPPORT
#define _FRC_SUPPORT                                            _OFF
#endif

//-------------------------------------------------
// Display Rotation Option
//-------------------------------------------------
#ifndef _DISPLAY_ROTATION_SUPPORT
#define _DISPLAY_ROTATION_SUPPORT                               _OFF
#endif

//==================== START ======================
#ifndef _DISPLAY_HOR_MIRROR_SUPPORT
#define _DISPLAY_HOR_MIRROR_SUPPORT                             _OFF
#endif

#ifndef _DISPLAY_VER_MIRROR_SUPPORT
#define _DISPLAY_VER_MIRROR_SUPPORT                             _OFF
#endif
//===================== END =======================

//-------------------------------------------------
// Motion Blur Reduction Option
//-------------------------------------------------
#ifndef _MOTION_BLUR_REDUCTION_SUPPORT
#define _MOTION_BLUR_REDUCTION_SUPPORT                          _OFF
#endif

#ifndef _MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT
#define _MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT      _OFF
#endif

#ifndef _DRR_MOTION_BLUR_REDUCTION_SUPPORT
#define _DRR_MOTION_BLUR_REDUCTION_SUPPORT                      _OFF
#endif

//--------------------------------------------------
// Aspect Ratio Option
//--------------------------------------------------
#ifndef _ASPECT_RATIO_SUPPORT
#define _ASPECT_RATIO_SUPPORT                                   _OFF
#endif

#ifndef _ASPECT_ORIGINAL_MODE_SUPPORT
#define _ASPECT_ORIGINAL_MODE_SUPPORT                           _OFF
#endif

//==================== START ======================
#ifndef _ASPECT_RATIO_WITHOUT_MUTE
#define _ASPECT_RATIO_WITHOUT_MUTE                              _OFF
#endif
//===================== END =======================

//--------------------------------------------------
// Overscan Option
//--------------------------------------------------
#ifndef _OVERSCAN_VGA_SUPPORT
#define _OVERSCAN_VGA_SUPPORT                                   _OFF
#endif

#ifndef _OVERSCAN_DVI_SUPPORT
#define _OVERSCAN_DVI_SUPPORT                                   _OFF
#endif

#ifndef _OVERSCAN_HDMI_SUPPORT
#define _OVERSCAN_HDMI_SUPPORT                                  _OFF
#endif

#ifndef _OVERSCAN_DP_SUPPORT
#define _OVERSCAN_DP_SUPPORT                                    _OFF
#endif

#ifndef _OVERSCAN_H_RATIO
#define _OVERSCAN_H_RATIO                                       30
#endif

#ifndef _OVERSCAN_V_RATIO
#define _OVERSCAN_V_RATIO                                       30
#endif

//-------------------------------------------------
// Adjust H & V Position Max Range Option
//-------------------------------------------------
#ifndef _MAX_H_POSITION_RANGE
#define _MAX_H_POSITION_RANGE                                   100 // Pixel
#endif

#ifndef _MAX_V_POSITION_RANGE
#define _MAX_V_POSITION_RANGE                                   100 // Line
#endif

//==================== START ======================

//-------------------------------------------------
// Force Display Free Run Option --> For Last Line Issue Panel
//-------------------------------------------------
#ifndef _FORCE_TO_FREE_RUN_SUPPORT
#define _FORCE_TO_FREE_RUN_SUPPORT                              _OFF
#endif

//-------------------------------------------------
// Disable MN Frame Sync -> Force to Free Run
//-------------------------------------------------
#ifndef _MN_FRAMESYNC_FORCE_TO_FREERUN
#define _MN_FRAMESYNC_FORCE_TO_FREERUN                          _OFF
#endif

//--------------------------------------------------
// Display Frame Sync Line Buffer Option
//--------------------------------------------------
#ifndef _FRAME_SYNC_LINE_BUFFER_SUPPORT
#define _FRAME_SYNC_LINE_BUFFER_SUPPORT                         _ON
#endif

//-------------------------------------------------
// Freeze Mode Option
//-------------------------------------------------
#ifndef _FREEZE_SUPPORT
#define _FREEZE_SUPPORT                                         _OFF
#endif

#ifndef _ROTATION_FREEZE_FORCE_TO_BACKGROUND
#define _ROTATION_FREEZE_FORCE_TO_BACKGROUND                    _OFF
#endif

//--------------------------------------------------
// Display Frame Sync Frame Buffer Latency Option
//--------------------------------------------------
#ifndef _DISP_LATENCY_ADJUST_SUPPORT
#define _DISP_LATENCY_ADJUST_SUPPORT                            _OFF
#endif

//--------------------------------------------------
// Force Even/Odd Mode Option
//--------------------------------------------------
#ifndef _FORMAT_CONVERSION_FORCE_EO_MODE
#define _FORMAT_CONVERSION_FORCE_EO_MODE                        _OFF
#endif

//-------------------------------------------------
// Display PLL Jitter Margin
//-------------------------------------------------
#ifndef _DPLL_JITTER_MARGIN
#define _DPLL_JITTER_MARGIN                                     _DPLL_1_PERCENT_JITTER_MARGIN
#endif

//-------------------------------------------------
// MN Display PLL WD Set Reference Power
//-------------------------------------------------
#ifndef _DPLL_WD_SET_REF_POWER
#define _DPLL_WD_SET_REF_POWER                                  _OFF
#endif

//-------------------------------------------------
// Eizo Request Dclk Accuracy
//-------------------------------------------------
#ifndef _DCLK_ACCURACY
#define _DCLK_ACCURACY                                          _OFF
#endif

//-------------------------------------------------
// Adjust measure H/V freq.
//-------------------------------------------------
#ifndef _MEASURE_ADJUSTED_IHF_SUPPORT
#define _MEASURE_ADJUSTED_IHF_SUPPORT                           _OFF
#endif

#ifndef _MEASURE_ADJUSTED_IVF_SUPPORT
#define _MEASURE_ADJUSTED_IVF_SUPPORT                           _OFF
#endif

//===================== END =======================


////////////////////
// Color Function //
////////////////////

//--------------------------------------------------
// Digital Functional Option
//--------------------------------------------------
#ifndef _I_DITHER_SUPPORT
#define _I_DITHER_SUPPORT                                       _OFF
#endif

#ifndef _D_DITHER_SUPPORT
#define _D_DITHER_SUPPORT                                       _OFF
#endif

#ifndef _GAMMA_FUNCTION
#define _GAMMA_FUNCTION                                         _OFF
#endif

#ifndef _COLOR_FORMAT_CONVERT
#define _COLOR_FORMAT_CONVERT                                   _OFF
#endif

#ifndef _RGB_QUANTIZATION_RANGE_SUPPORT
#define _RGB_QUANTIZATION_RANGE_SUPPORT                         _OFF
#endif
//==================== START ======================
#ifndef _RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER
#define _RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER           _OFF
#endif
//===================== END ======================

#ifndef _YCC_QUANTIZATION_RANGE_SUPPORT
#define _YCC_QUANTIZATION_RANGE_SUPPORT                         _OFF
#endif

#ifndef _ULTRA_VIVID_SUPPORT
#define _ULTRA_VIVID_SUPPORT                                    _OFF
#endif

#ifndef _DCR_SUPPORT
#define _DCR_SUPPORT                                            _OFF
#endif

#ifndef _DCC_FUNCTION
#define _DCC_FUNCTION                                           _OFF
#endif

#ifndef _DCC_HISTOGRM_INFO
#define _DCC_HISTOGRM_INFO                                      _OFF
#endif

#ifndef _ICM_SUPPORT
#define _ICM_SUPPORT                                            _OFF
#endif

#ifndef _ICM_BRI_SUPPORT
#define _ICM_BRI_SUPPORT                                        _OFF
#endif

#ifndef _SCM_SUPPORT
#define _SCM_SUPPORT                                            _OFF
#endif

#ifndef _SIX_COLOR_SUPPORT
#define _SIX_COLOR_SUPPORT                                      _OFF
#endif

#ifndef _HIGHLIGHT_WINDOW_SUPPORT
#define _HIGHLIGHT_WINDOW_SUPPORT                               _OFF
#endif

#ifndef _RINGING_FILTER_SUPPORT
#define _RINGING_FILTER_SUPPORT                                 _OFF
#endif

#ifndef _SHARPNESS_SUPPORT
#define _SHARPNESS_SUPPORT                                      _OFF
#endif

#ifndef _CONTRAST_SUPPORT
#define _CONTRAST_SUPPORT                                       _OFF
#endif

#ifndef _BRIGHTNESS_SUPPORT
#define _BRIGHTNESS_SUPPORT                                     _OFF
#endif

//==================== START ======================
#ifndef _ADCNR_SUPPORT
#define _ADCNR_SUPPORT                                          _ON
#endif
//===================== END ======================

//==================== START ======================
#ifndef _SIX_COLOR_ICM_TYPE
#define _SIX_COLOR_ICM_TYPE                                     _SIX_COLOR_ICM_NORMAL_MODE
#endif
//===================== END ======================

//-------------------------------------------------
// Hue and Saturation Option
//-------------------------------------------------
#ifndef _GLOBAL_HUE_SATURATION
#define _GLOBAL_HUE_SATURATION                                  _OFF
#endif

#ifndef _HUE_MAX
#define _HUE_MAX                                                230
#endif

#ifndef _HUE_MIN
#define _HUE_MIN                                                30
#endif

#ifndef _SATURATION_MAX
#define _SATURATION_MAX                                         200
#endif

#ifndef _SATURATION_MIN
#define _SATURATION_MIN                                         0
#endif

//-------------------------------------------------
// IAPS Option
//-------------------------------------------------
#ifndef _IAPS_SUPPORT
#define _IAPS_SUPPORT                                           _OFF
#endif

//==================== START ======================
#ifndef _IAPS_CONTRAST_TARGET
#define _IAPS_CONTRAST_TARGET                                   0x2000
#endif

#ifndef _IAPS_GAIN_CLAMP_FACTOR
#define _IAPS_GAIN_CLAMP_FACTOR                                 0xB0
#endif
//===================== END ======================

//==================== START ======================

//--------------------------------------------------
// Force YUV format conversion Option
//--------------------------------------------------
#ifndef _M_DOMAIN_FORCE_YUV_FORMAT
#define _M_DOMAIN_FORCE_YUV_FORMAT                              _OFF
#endif

//===================== END ======================


////////////////////////////////////////
// Off-Line Display Color Calibration //
////////////////////////////////////////

//-------------------------------------------------
// PCM (Load Code Table) Option
//-------------------------------------------------
#ifndef _PCM_FUNCTION
#define _PCM_FUNCTION                                           _OFF
#endif

//-------------------------------------------------
// 3D Gamma (Load Code Table) Option
//-------------------------------------------------
#ifndef _RGB_3D_GAMMA
#define _RGB_3D_GAMMA                                           _OFF
#endif

//-------------------------------------------------
// RGB Gamma (Load Code Table) Option
//-------------------------------------------------
#ifndef _RGB_GAMMA_FUNCTION
#define _RGB_GAMMA_FUNCTION                                     _OFF
#endif


////////////////////////////////////////
// On-Line Display Color Calibration //
////////////////////////////////////////

//-------------------------------------------------
// OGC and OCC (On-Line Calibration) Option
//-------------------------------------------------
#ifndef _OCC_SUPPORT
#define _OCC_SUPPORT                                            _OFF
#endif

#ifndef _OGC_SUPPORT
#define _OGC_SUPPORT                                            _OFF
#endif

#ifndef _OGC_DICOM_SUPPORT
#define _OGC_DICOM_SUPPORT                                      _OFF
#endif

#ifndef _TWO_BRI_CALIBRATION_TYPE
#define _TWO_BRI_CALIBRATION_TYPE                               _TWO_BRI_CALIBRATION_NONE
#endif

#ifndef _OGC_TOTAL_GAMMA
#define _OGC_TOTAL_GAMMA                                        1 // 1/2/3/4/5/6
#endif

#ifndef _OGC_TOTAL_CT
#define _OGC_TOTAL_CT                                           1
#endif

#ifndef _OGC_FLASH_BANK
#define _OGC_FLASH_BANK                                         0
#endif

//-------------------------------------------------
// FreesyncII Option
//-------------------------------------------------
#ifndef _FREESYNC_II_GLOBAL_BACKLIGHT_SUPPORT
#define _FREESYNC_II_GLOBAL_BACKLIGHT_SUPPORT                   _OFF
#endif

#ifndef _FREESYNC_II_FLASH_BANK
#define _FREESYNC_II_FLASH_BANK                                 0
#endif

#ifndef _FREESYNC_II_FLASH_PAGE
#define _FREESYNC_II_FLASH_PAGE                                 0
#endif

//-------------------------------------------------
// Uniformity (On-Line Calibration) Option
//-------------------------------------------------
#ifndef _UNIFORMITY_SUPPORT
#define _UNIFORMITY_SUPPORT                                     _OFF
#endif


#ifndef _UNIFORMITY_FLASH_BANK0
#define _UNIFORMITY_FLASH_BANK0                                 0
#endif

#ifndef _UNIFORMITY_1ST_TABLE_LEVEL
#define _UNIFORMITY_1ST_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_2ND_TABLE_LEVEL
#define _UNIFORMITY_2ND_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_3RD_TABLE_LEVEL
#define _UNIFORMITY_3RD_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_4TH_TABLE_LEVEL
#define _UNIFORMITY_4TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_5TH_TABLE_LEVEL
#define _UNIFORMITY_5TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_6TH_TABLE_LEVEL
#define _UNIFORMITY_6TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif
//==================== START ======================
#ifndef _UNIFORMITY_LEVEL0_SUPPORT
#define _UNIFORMITY_LEVEL0_SUPPORT                              _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE0
#define _UNIFORMITY_OFFSET_TYPE0                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE1
#define _UNIFORMITY_OFFSET_TYPE1                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE2
#define _UNIFORMITY_OFFSET_TYPE2                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE3
#define _UNIFORMITY_OFFSET_TYPE3                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE4
#define _UNIFORMITY_OFFSET_TYPE4                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE5
#define _UNIFORMITY_OFFSET_TYPE5                                _OFF
#endif

#ifndef _COLORIMETRY_SEAMLESS_CHANGE_SUPPORT
#define _COLORIMETRY_SEAMLESS_CHANGE_SUPPORT                    _OFF
#endif
//===================== END ======================

//-------------------------------------------------
// Backlight dimming Option
//-------------------------------------------------
#ifndef _LOCAL_DIMMING_SUPPORT
#define _LOCAL_DIMMING_SUPPORT                                  _OFF
#endif

#ifndef _DISPLAY_HDR_VERSION
#define _DISPLAY_HDR_VERSION                                    _DISPLAY_HDR_VERSION_1_0
#endif


#ifndef _GLOBAL_DIMMING_SUPPORT
#define _GLOBAL_DIMMING_SUPPORT                                 _OFF
#endif

#ifndef _LD_TUNNEL_DETECT_SUPPORT
#define _LD_TUNNEL_DETECT_SUPPORT                               _OFF
#endif

#ifndef _LD_HDR10_BOOST_SUPPORT
#define _LD_HDR10_BOOST_SUPPORT                                 _OFF
#endif

#ifndef _GLOBAL_DIMMING_LOW_SENSITIVITY_SUPPORT
#define _GLOBAL_DIMMING_LOW_SENSITIVITY_SUPPORT                 _OFF
#endif

#ifndef _LD_FREESYNC_MODE_SUPPORT
#define _LD_FREESYNC_MODE_SUPPORT                               _OFF
#endif

#ifndef _LD_FREESYNC_II_BOOST_SUPPORT
#define _LD_FREESYNC_II_BOOST_SUPPORT                           _OFF
#endif

//==================== START ======================
#ifndef _SDR_TO_HDR_SUPPORT
#define _SDR_TO_HDR_SUPPORT                                     _OFF
#endif

#ifndef _SDR_TO_HDR_ADOBE_RGB_SUPPORT
#define _SDR_TO_HDR_ADOBE_RGB_SUPPORT                           _OFF
#endif

//-------------------------------------------------
// HDR10 Color Enhance & Light Enhance Option
//-------------------------------------------------
#ifndef _HDR10_COLOR_ENHANCE_SUPPORT
#define _HDR10_COLOR_ENHANCE_SUPPORT                            _OFF
#endif
#ifndef _HDR10_LIGHT_ENHANCE_SUPPORT
#define _HDR10_LIGHT_ENHANCE_SUPPORT                            _OFF
#endif
//===================== END ======================

//-------------------------------------------------
// HDR10 FIXED POINT TONEMAPPING
//-------------------------------------------------
#ifndef _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT
#define _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT                  _OFF
#endif

//-------------------------------------------------
// HDR10 User Define Panel Max Lv
//-------------------------------------------------
#ifndef _HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT
#define _HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT                 _OFF
#endif


////////////
// Eeprom //
////////////

//-------------------------------------------------
// Eeprom Access Function Option
//-------------------------------------------------
#ifndef _EEPROM_ACCESS_FUNCTION_SUPPORT
#define _EEPROM_ACCESS_FUNCTION_SUPPORT                         _OFF
#endif

#ifndef _EEPROM_KERNEL_START_ADDRESS
#define _EEPROM_KERNEL_START_ADDRESS                            (_EEPROM_PAGE0_BANK0)
#endif


///////////
// Flash //
///////////

//-------------------------------------------------
// Flash Clock Option
//-------------------------------------------------
#ifndef _FLASH_CLK_SPEED
#define _FLASH_CLK_SPEED                                        _FLASH_FAST_SPEED
#endif

//-------------------------------------------------
// Flash Access Function Option
//-------------------------------------------------
#ifndef _FLASH_WRITE_FUNCTION_SUPPORT
#define _FLASH_WRITE_FUNCTION_SUPPORT                           _OFF
#endif

#ifndef _FLASH_READ_FUNCTION_SUPPORT
#define _FLASH_READ_FUNCTION_SUPPORT                            _OFF
#endif

#ifndef _FLASH_TYPE_W25X20A_OR_W25X21CL
#define _FLASH_TYPE_W25X20A_OR_W25X21CL                         _FLASH_W25X20A
#endif

#ifndef _FLASH_TYPE_W25X40CL_OR_W25X41CL
#define _FLASH_TYPE_W25X40CL_OR_W25X41CL                        _FLASH_W25X40CL
#endif

#ifndef _FLASH_TYPE_GD25Q16C_OR_GD25Q16
#define _FLASH_TYPE_GD25Q16C_OR_GD25Q16                         _FLASH_GD25Q16C
#endif

#ifndef _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F
#define _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F      _FLASH_MX25L3233F
#endif

#ifndef _FLASH_TYPE_GD25Q40B_OR_GD25Q41B
#define _FLASH_TYPE_GD25Q40B_OR_GD25Q41B                        _FLASH_GD25Q41B
#endif

#ifndef _FLASH_TYPE_W25Q16DV_OR_W25Q16JVSIQ
#define _FLASH_TYPE_W25Q16DV_OR_W25Q16JVSIQ                     _FLASH_W25Q16JVSIQ
#endif

#ifndef _FLASH_TYPE_FM25Q08_OR_FM25Q08A
#define _FLASH_TYPE_FM25Q08_OR_FM25Q08A                         _FLASH_FM25Q08A
#endif

#ifndef _FLASH_TYPE_BY25D40C_OR_BY25D40ASTIG
#define _FLASH_TYPE_BY25D40C_OR_BY25D40ASTIG                    _FLASH_BY25D40C
#endif

#ifndef _FLASH_TYPE_W25Q32F_OR_W25Q32JVSSIQ
#define _FLASH_TYPE_W25Q32F_OR_W25Q32JVSSIQ                     _FLASH_W25Q32F
#endif

#ifndef _FLASH_TYPE_BY25D80ASTIG_OR_BY25Q80BSTIG
#define _FLASH_TYPE_BY25D80ASTIG_OR_BY25Q80BSTIG                _FLASH_BY25D80ASTIG
#endif

//-------------------------------------------------
// EEPROM Emulation Option
//-------------------------------------------------
#ifndef _SYSTEM_EEPROM_EMULATION_SUPPORT
#define _SYSTEM_EEPROM_EMULATION_SUPPORT                        _OFF
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_FLASH_BANK
#define _SYSTEM_EEPROM_EMULATION_FLASH_BANK                     0
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_START_PAGE
#define _SYSTEM_EEPROM_EMULATION_START_PAGE                     0
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_END_PAGE
#define _SYSTEM_EEPROM_EMULATION_END_PAGE                       0
#endif

#ifndef _START_OF_PAGEID
#define _START_OF_PAGEID                                        _PAGEID_0
#endif

#ifndef _END_OF_PAGEID
#define _END_OF_PAGEID                                          _PAGEID_0
#endif

#ifndef _CHECKSUM_VERSIONCODE_ID
#define _CHECKSUM_VERSIONCODE_ID                                _PAGEID_0
#endif

//==================== START ======================

//--------------------------------------------------
// SPI Option
//--------------------------------------------------
#ifndef _SPI_SUPPORT
#define _SPI_SUPPORT                                            _OFF
#endif

//===================== END ======================


//////////
// EDID //
//////////

//-------------------------------------------------
// EDID Location Option
//-------------------------------------------------
#ifndef _EDID_ADDRESS_EEPROM
#define _EDID_ADDRESS_EEPROM                                    (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _EDID_ADDRESS_FLASH
#define _EDID_ADDRESS_FLASH                                     (0)
#endif

#ifndef _EDID_FLASH_BANK
#define _EDID_FLASH_BANK                                        (0)
#endif

//-------------------------------------------------
// HDR10 EDID Auto Switch Option
//-------------------------------------------------
#ifndef _EDID_HDR10_AUTO_SWITCH
#define _EDID_HDR10_AUTO_SWITCH                                 _ON
#endif

//==================== START ======================
#ifndef _WRITE_EDID_TO_SYSTEM_EEPROM
#define _WRITE_EDID_TO_SYSTEM_EEPROM                            _OFF
#endif
//===================== END =======================


//////////////
// HDCP Key //
//////////////

//-------------------------------------------------
// HDCP Key Location Option
//-------------------------------------------------
#ifndef _HDCP_1_4_KEY_LOCATION
#define _HDCP_1_4_KEY_LOCATION                                  _TABLE_LOCATION_SYSTEM_EEPROM
#endif

#ifndef _HDCP_2_2_KEY_LOCATION
#define _HDCP_2_2_KEY_LOCATION                                  _TABLE_LOCATION_CODE
#endif

#ifndef _RX_HDCP_1_4_KEY_ADDRESS_EEPROM
#define _RX_HDCP_1_4_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _RX_HDCP_1_4_KEY_ADDRESS_FLASH
#define _RX_HDCP_1_4_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _RX_HDCP_1_4_KEY_FLASH_BANK
#define _RX_HDCP_1_4_KEY_FLASH_BANK                             (0)
#endif

#ifndef _RX_HDCP_2_2_KEY_ADDRESS_EEPROM
#define _RX_HDCP_2_2_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _RX_HDCP_2_2_KEY_ADDRESS_FLASH
#define _RX_HDCP_2_2_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _RX_HDCP_2_2_KEY_FLASH_BANK
#define _RX_HDCP_2_2_KEY_FLASH_BANK                             (0)
#endif

#ifndef _TX_HDCP_1_4_KEY_ADDRESS_EEPROM
#define _TX_HDCP_1_4_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _TX_HDCP_1_4_KEY_ADDRESS_FLASH
#define _TX_HDCP_1_4_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _TX_HDCP_1_4_KEY_FLASH_BANK
#define _TX_HDCP_1_4_KEY_FLASH_BANK                             (0)
#endif

#ifndef _TX_HDCP_2_2_KEY_ADDRESS_EEPROM
#define _TX_HDCP_2_2_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _TX_HDCP_2_2_KEY_ADDRESS_FLASH
#define _TX_HDCP_2_2_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _TX_HDCP_2_2_KEY_FLASH_BANK
#define _TX_HDCP_2_2_KEY_FLASH_BANK                             (0)
#endif

//==================== START ======================
#ifndef _WRITE_HDCP_TO_SYSTEM_EEPROM
#define _WRITE_HDCP_TO_SYSTEM_EEPROM                            _OFF
#endif
//===================== END =======================


///////////////////
// System Source //
///////////////////

//-------------------------------------------------
// System Auto Search Style Option
//-------------------------------------------------
#ifndef _SOURCE_AUTO_SEARCH_STYLE
#define _SOURCE_AUTO_SEARCH_STYLE                               _SOURCE_POLLING_IN_SEARCH_STATE
#endif

//-------------------------------------------------
// System Source Search Time Option
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_VGA
#define _SOURCE_DEFAULT_SEARCH_TIME_VGA                         SEC(0.5)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_HDMI
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI                        SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DVI
#define _SOURCE_DEFAULT_SEARCH_TIME_DVI                         SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DP
#define _SOURCE_DEFAULT_SEARCH_TIME_DP                          SEC(3)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C
#define _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C                      SEC(4.5)
#endif

//-------------------------------------------------
// System Source Background Detection
//-------------------------------------------------
#ifndef _SOURCE_BACKGROUND_DETECT_SUPPORT
#define _SOURCE_BACKGROUND_DETECT_SUPPORT                       _OFF
#endif

//==================== START ======================

//-------------------------------------------------
// System Default Search Time for all Port --> (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT
#define _SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT                    SEC(2)
#endif

//-------------------------------------------------
// System Default Search Time When No Cable Option
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_VGA_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_VGA_NO_CABLE                SEC(0.5)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE               SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DVI_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_DVI_NO_CABLE                SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE                 SEC(3)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C_NO_CABLE             SEC(4.5)
#endif

//-------------------------------------------------
// System Required Time for External or Embedded DP Switch
//-------------------------------------------------
#ifndef _SOURCE_DP_SWITCH_TIMEOUT_TIME
#define _SOURCE_DP_SWITCH_TIMEOUT_TIME                          SEC(4)
#endif

//--------------------------------------------------
// Double Check NVRAM Port When Searching In Polling Mode Option
//--------------------------------------------------
#ifndef _SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT
#define _SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT                 _OFF
#endif

#ifndef _SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT
#define _SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT             SEC(0.5)
#endif

//===================== END =======================


//////////////////
// System Judge //
//////////////////

//-------------------------------------------------
// System Display Setting Check Time Option
//-------------------------------------------------
#ifndef _WAIT_TIME_TO_ACTIVE_VGA
#define _WAIT_TIME_TO_ACTIVE_VGA                                SEC(0.05)
#endif

#ifndef _WAIT_TIME_TO_ACTIVE_DVI
#define _WAIT_TIME_TO_ACTIVE_DVI                                SEC(0.1)
#endif

#ifndef _WAIT_TIME_TO_ACTIVE_HDMI
#define _WAIT_TIME_TO_ACTIVE_HDMI                               SEC(0.1)
#endif

#ifndef _WAIT_TIME_TO_ACTIVE_DP
#define _WAIT_TIME_TO_ACTIVE_DP                                 SEC(0.1)
#endif

//--------------------------------------------------
// System Support Timing Option
//--------------------------------------------------
#ifndef _OOR_H_FREQ_UPPER_BOUND
#define _OOR_H_FREQ_UPPER_BOUND                                 2200 // Unit in 0.1 kHZ
#endif

#ifndef _OOR_H_FREQ_LOWER_BOUND
#define _OOR_H_FREQ_LOWER_BOUND                                 100  // Unit in 0.1 kHZ
#endif

#ifndef _OOR_V_FREQ_UPPER_BOUND
#define _OOR_V_FREQ_UPPER_BOUND                                 1500 // Unit in 0.1 HZ
#endif

#ifndef _OOR_V_FREQ_LOWER_BOUND
#define _OOR_V_FREQ_LOWER_BOUND                                 230  // Unit in 0.1 HZ
#endif

#ifndef _OOR_H_WIDTH_UPPER_BOUND
#define _OOR_H_WIDTH_UPPER_BOUND                                4096 // Unit in pixel
#endif

#ifndef _OOR_V_HEIGHT_LOWER_BOUND
#define _OOR_V_HEIGHT_LOWER_BOUND                               240  // Unit in line
#endif

#ifndef _FAIL_SAVE_H_FREQ_UPPER_BOUND
#define _FAIL_SAVE_H_FREQ_UPPER_BOUND                           2200 // Unit in 0.1 kHZ
#endif

#ifndef _FAIL_SAVE_H_FREQ_LOWER_BOUND
#define _FAIL_SAVE_H_FREQ_LOWER_BOUND                           110  // Unit in 0.1 kHZ
#endif

#ifndef _FAIL_SAVE_V_FREQ_UPPER_BOUND
#define _FAIL_SAVE_V_FREQ_UPPER_BOUND                           1500 // Unit in 0.1 HZ
#endif

#ifndef _FAIL_SAVE_V_FREQ_LOWER_BOUND
#define _FAIL_SAVE_V_FREQ_LOWER_BOUND                           230  // Unit in 0.1 HZ
#endif

#ifndef _INPUTCLOCK_RANG_VGA
#define _INPUTCLOCK_RANG_VGA                                    2100 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_DVI
#define _INPUTCLOCK_RANG_DVI                                    6000 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_HDMI
#define _INPUTCLOCK_RANG_HDMI                                   6000 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_DP
#define _INPUTCLOCK_RANG_DP                                     6000 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_USBC
#define _INPUTCLOCK_RANG_USBC                                   6000 // Unit in 0.1 MHz
#endif


//////////////////
// System Power //
//////////////////
//==================== START ======================

//--------------------------------------------------
// Power Fake Off to Off Timeout
//--------------------------------------------------
#ifndef _POWER_FAKE_OFF_TO_OFF_TIMEOUT
#define _POWER_FAKE_OFF_TO_OFF_TIMEOUT                          SEC(8)
#endif

//===================== END =======================


/////////
// VGA //
/////////

//--------------------------------------------------
// VGA YPBPR Option
//--------------------------------------------------
#ifndef _YPBPR_SUPPORT
#define _YPBPR_SUPPORT                                          _ON
#endif

#ifndef _SOG_SUPPORT
#define _SOG_SUPPORT                                            _ON
#endif

#ifndef _VGA_COMPOSITE_SUPPORT
#define _VGA_COMPOSITE_SUPPORT                                  _ON
#endif

//--------------------------------------------------
// VGA Mode Search condition reference by picture width Option
//--------------------------------------------------
#ifndef _MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT
#define _MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT                  _OFF
#endif

//--------------------------------------------------
// VGA Auto Adjust Clock Setup Option
//--------------------------------------------------
#ifndef _AUTO_CLOCK_STEP
#define _AUTO_CLOCK_STEP                                        2  // 1 or 2
#endif

#ifndef _AUTO_CLOCK_RANGE
#define _AUTO_CLOCK_RANGE                                       95 // Set Clock Non-adjusting Range (%) by the active region
#endif

#ifndef _AUTO_TOLERANCE_PIXEL
#define _AUTO_TOLERANCE_PIXEL                                   2  // Definitions Of tolerance pixel for Auto Clock
#endif

#ifndef _AUTO_CLOCK_SAVE_VALUE_OPTION
#define _AUTO_CLOCK_SAVE_VALUE_OPTION                           _CLOCK_SAVE_PERCENT_VALUE
#endif

//--------------------------------------------------
// VGA Gain & Offset Defualt Option
//--------------------------------------------------
#ifndef _ADC_RGB_DEFAULT_RED_GAIN
#define _ADC_RGB_DEFAULT_RED_GAIN                               128
#endif

#ifndef _ADC_RGB_DEFAULT_GREEN_GAIN
#define _ADC_RGB_DEFAULT_GREEN_GAIN                             128
#endif

#ifndef _ADC_RGB_DEFAULT_BLUE_GAIN
#define _ADC_RGB_DEFAULT_BLUE_GAIN                              128
#endif

#ifndef _ADC_RGB_DEFAULT_RED_OFFSET
#define _ADC_RGB_DEFAULT_RED_OFFSET                             128
#endif

#ifndef _ADC_RGB_DEFAULT_GREEN_OFFSET
#define _ADC_RGB_DEFAULT_GREEN_OFFSET                           128
#endif

#ifndef _ADC_RGB_DEFAULT_BLUE_OFFSET
#define _ADC_RGB_DEFAULT_BLUE_OFFSET                            128
#endif

#ifndef _ADC_YPBPR_DEFAULT_Y_GAIN
#define _ADC_YPBPR_DEFAULT_Y_GAIN                               159
#endif

#ifndef _ADC_YPBPR_DEFAULT_PB_GAIN
#define _ADC_YPBPR_DEFAULT_PB_GAIN                              154
#endif

#ifndef _ADC_YPBPR_DEFAULT_PR_GAIN
#define _ADC_YPBPR_DEFAULT_PR_GAIN                              154
#endif

#ifndef _ADC_YPBPR_DEFAULT_Y_OFFSET
#define _ADC_YPBPR_DEFAULT_Y_OFFSET                             112
#endif

#ifndef _ADC_YPBPR_DEFAULT_PB_OFFSET
#define _ADC_YPBPR_DEFAULT_PB_OFFSET                            128
#endif

#ifndef _ADC_YPBPR_DEFAULT_PR_OFFSET
#define _ADC_YPBPR_DEFAULT_PR_OFFSET                            128
#endif

//==================== START ======================
#ifndef _ADC_RGB_DEFAULT_PGA_VALUE
#define _ADC_RGB_DEFAULT_PGA_VALUE                              8 // 0 ~ 15
#endif

#ifndef _ADC_YPBPR_DEFAULT_PGA_VALUE
#define _ADC_YPBPR_DEFAULT_PGA_VALUE                            8 // 0 ~ 15
#endif
//===================== END =======================

//--------------------------------------------------
// VGA Self-Calibration Option
//--------------------------------------------------
#ifndef _ADC_SELF_CALIBRATION
#define _ADC_SELF_CALIBRATION                                   _OFF
#endif

#ifndef _CALIBRATION_R_GAIN_BIAS
#define _CALIBRATION_R_GAIN_BIAS                                (0)  // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_G_GAIN_BIAS
#define _CALIBRATION_G_GAIN_BIAS                                (0)  // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_B_GAIN_BIAS
#define _CALIBRATION_B_GAIN_BIAS                                (0)  // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_R_OFFSET_BIAS
#define _CALIBRATION_R_OFFSET_BIAS                              (-3) // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_G_OFFSET_BIAS
#define _CALIBRATION_G_OFFSET_BIAS                              (-3) // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_B_OFFSET_BIAS
#define _CALIBRATION_B_OFFSET_BIAS                              (-3) // Needs modification for EVERY single source
#endif

//==================== START ======================
#ifndef _SELF_CALIBRATION_CLK
#define _SELF_CALIBRATION_CLK                                   (148) // MHz
#endif
//===================== END =======================

//--------------------------------------------------
// VGA YPBPR Auto Color Method Option
//--------------------------------------------------
#ifndef _YPBPR_AUTO_METHOD
#define _YPBPR_AUTO_METHOD                                      _YPBPR_AUTO_BY_SOURCE
#endif

#ifndef _AUTO_PB_GAIN_BIAS
#define _AUTO_PB_GAIN_BIAS                                      (5)
#endif

#ifndef _AUTO_PR_GAIN_BIAS
#define _AUTO_PR_GAIN_BIAS                                      (5)
#endif

#ifndef _AUTO_Y_GAIN_BIAS
#define _AUTO_Y_GAIN_BIAS                                       (0)
#endif

#ifndef _AUTO_PB_OFFSET_BIAS
#define _AUTO_PB_OFFSET_BIAS                                    (-8)
#endif

#ifndef _AUTO_PR_OFFSET_BIAS
#define _AUTO_PR_OFFSET_BIAS                                    (-8)
#endif

#ifndef _AUTO_Y_OFFSET_BIAS
#define _AUTO_Y_OFFSET_BIAS                                     (-16)
#endif

//--------------------------------------------------
// VGA Digital Filter Option
//--------------------------------------------------
#ifndef _DIG_FILTER_NSMEAR_ENABLE
#define _DIG_FILTER_NSMEAR_ENABLE                               _ENABLE
#endif

#ifndef _DIG_FILTER_PSMEAR_ENABLE
#define _DIG_FILTER_PSMEAR_ENABLE                               _ENABLE
#endif

#ifndef _DIG_FILTER_NRING_ENABLE
#define _DIG_FILTER_NRING_ENABLE                                _ENABLE
#endif

#ifndef _DIG_FILTER_PRING_ENABLE
#define _DIG_FILTER_PRING_ENABLE                                _ENABLE
#endif

#ifndef _DIG_FILTER_EXTENSION_ENABLE
#define _DIG_FILTER_EXTENSION_ENABLE                            _ENABLE
#endif

#ifndef _DIG_FILTER_ENHANCE_PHASE_ENABLE
#define _DIG_FILTER_ENHANCE_PHASE_ENABLE                        _ENABLE
#endif

//==================== START ======================

//--------------------------------------------------
// VGA Digital Phase Filter Option
//--------------------------------------------------
#ifndef _DIG_FILTER_PHASE_ENABLE
#define _DIG_FILTER_PHASE_ENABLE                                _ENABLE
#endif

#ifndef _DIG_FILTER_PHASE_THD
#define _DIG_FILTER_PHASE_THD                                   192 // effective:0~255
#endif

#ifndef _DIG_FILTER_PHASE_DIV_VALUE
#define _DIG_FILTER_PHASE_DIV_VALUE                             0   // effective:0~3
#endif

#ifndef _DIG_FILTER_PHASE_HIGHFREQ_ADCCLOCKTHD
#define _DIG_FILTER_PHASE_HIGHFREQ_ADCCLOCKTHD                  0   // effective:0~210 (MHz)
#endif

#ifndef _DIG_FILTER_PHASE_HIGHFREQ_THD
#define _DIG_FILTER_PHASE_HIGHFREQ_THD                          160 // effective:0~255
#endif

#ifndef _DIG_FILTER_PHASE_HIGHFREQ_DIV_VALUE
#define _DIG_FILTER_PHASE_HIGHFREQ_DIV_VALUE                    0   // effective:0~3
#endif

//--------------------------------------------------
// VGA Chroma Pattern 12 Option
//--------------------------------------------------
#ifndef _VGA_CHROMA_PATTERN12_SUPPORT
#define _VGA_CHROMA_PATTERN12_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// VGA 25MHz Noise Reduce by SF/SHA LPF Option
//--------------------------------------------------
#ifndef _VGA_ADC_SF_SHA_LPF_UNDER_25MHZ_SUPPORT
#define _VGA_ADC_SF_SHA_LPF_UNDER_25MHZ_SUPPORT                 _OFF
#endif

//===================== END =======================

//==================== START ======================
#ifndef _FREESYNC_GET_IVTOTAL_BY_SPD
#define _FREESYNC_GET_IVTOTAL_BY_SPD                            _OFF
#endif
//===================== END =======================


////////////////
// DVI & HDMI //
////////////////

//--------------------------------------------------
// DVI & HDMI Option
//--------------------------------------------------
#ifndef _DVI_DE_ONLY_SUPPORT
#define _DVI_DE_ONLY_SUPPORT                                    _OFF
#endif

#ifndef _HDMI_FROM_DVI_CONNECT
#define _HDMI_FROM_DVI_CONNECT                                  _OFF
#endif

#ifndef _HDMI_FREESYNC_SUPPORT
#define _HDMI_FREESYNC_SUPPORT                                  _OFF
#endif

#ifndef _HDMI_FREESYNC_II_SUPPORT
#define _HDMI_FREESYNC_II_SUPPORT                               _OFF
#endif

#ifndef _HDMI_HDR10_SUPPORT
#define _HDMI_HDR10_SUPPORT                                     _OFF
#endif

//==================== START ======================
#ifndef _HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD
#define _HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD                 _MCCS_SWITCH_MODE
#endif

#ifndef _HDMI_FREESYNC_ENLARGE_FRONT_PORCH
#define _HDMI_FREESYNC_ENLARGE_FRONT_PORCH                      _OFF
#endif

#ifndef _HDMI_FREESYNC_ENLARGE_FRONT_PORCH_LINE
#define _HDMI_FREESYNC_ENLARGE_FRONT_PORCH_LINE                 _VSYNC_DELAY_4_LINES
#endif

//-------------------------------------------------
// HDMI HDCP Re-auth Option
//-------------------------------------------------
#ifndef _HDMI_HDCP22_REAUTH_IN_RESET_PROC
#define _HDMI_HDCP22_REAUTH_IN_RESET_PROC                       _OFF
#endif

//--------------------------------------------------
// TMDS Z0's HPD DDC Check Optional
//--------------------------------------------------
#ifndef _TMDS_DDC_CHECK_BUSY_BEFORE_HPD
#define _TMDS_DDC_CHECK_BUSY_BEFORE_HPD                         _OFF
#endif

#ifndef _HDMI_FREESYNC_MCCS_VCP
#define _HDMI_FREESYNC_MCCS_VCP                                 0xE6
#endif
//===================== END =======================

#ifndef _TMDS_HDCP_2_2_SUPPORT
#define _TMDS_HDCP_2_2_SUPPORT                                  _OFF
#endif

//--------------------------------------------------
// HDMI CTS Option
//--------------------------------------------------
#ifndef _TMDS_HDCP_FEATURE
#define _TMDS_HDCP_FEATURE                                      _HDCP_FEATURE_BY_INPUT
#endif

#ifndef _TMDS_Z0_POWER_SAVING_OPTION
#define _TMDS_Z0_POWER_SAVING_OPTION                            _ALL_CHANNEL_CONNECTED_FOR_CTS
#endif

//==================== START ======================
#ifndef _TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT
#define _TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT                      _OFF
#endif

#ifndef _D0_DP_Z0_IMPEDANCE_OPTION
#define _D0_DP_Z0_IMPEDANCE_OPTION                              _BY_CONNECTOR
#endif

#ifndef _D1_DP_Z0_IMPEDANCE_OPTION
#define _D1_DP_Z0_IMPEDANCE_OPTION                              _BY_CONNECTOR
#endif

#ifndef _D2_TMDS_Z0_IMPEDANCE_OPTION
#define _D2_TMDS_Z0_IMPEDANCE_OPTION                            _BY_CONNECTOR
#endif

#ifndef _D3_TMDS_Z0_IMPEDANCE_OPTION
#define _D3_TMDS_Z0_IMPEDANCE_OPTION                            _BY_CONNECTOR
#endif

#ifndef _D4_TMDS_Z0_IMPEDANCE_OPTION
#define _D4_TMDS_Z0_IMPEDANCE_OPTION                            _BY_CONNECTOR
#endif

#ifndef _D5_TMDS_Z0_IMPEDANCE_OPTION
#define _D5_TMDS_Z0_IMPEDANCE_OPTION                            _BY_CONNECTOR
#endif
//===================== END =======================


////////
// DP //
////////

//-------------------------------------------------
// DP Capability Option
//-------------------------------------------------
#ifndef _DP_MST_SUPPORT
#define _DP_MST_SUPPORT                                         _OFF
#endif

#ifndef _DP_TX_SUPPORT
#define _DP_TX_SUPPORT                                          _OFF
#endif

#ifndef _DP_FREESYNC_SUPPORT
#define _DP_FREESYNC_SUPPORT                                    _OFF
#endif

#ifndef _DP_FREESYNC_II_SUPPORT
#define _DP_FREESYNC_II_SUPPORT                                 _OFF
#endif

#ifndef _DP_HDR10_SUPPORT
#define _DP_HDR10_SUPPORT                                       _OFF
#endif

#ifndef _DP_HDCP_2_2_SUPPORT
#define _DP_HDCP_2_2_SUPPORT                                    _OFF
#endif

#ifndef _DP_HDCP14_CTS_SUPPORT
#define _DP_HDCP14_CTS_SUPPORT                                  _OFF
#endif

//--------------------------------------------------
// DP DPCD DFP Present (00005h) Set Option
//--------------------------------------------------
#ifndef _DP_DPCD_DFP_PRESENT_REF_TO
#define _DP_DPCD_DFP_PRESENT_REF_TO                             _DP_MST_CAPABILITY
#endif

//==================== START ======================

#ifndef _DP_TX_SSC_SUPPORT
#define _DP_TX_SSC_SUPPORT                                      _OFF
#endif

//--------------------------------------------------
// Eizo DP Illegal Idle Pattern Check Support
//--------------------------------------------------
#ifndef _DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT
#define _DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT                  _OFF
#endif

//--------------------------------------------------
// Rebuild PHY when DP Source Change Link Rate without Link Training
//--------------------------------------------------
#ifndef _DP_LINK_RATE_CHANGE_WO_LT_SUPPORT
#define _DP_LINK_RATE_CHANGE_WO_LT_SUPPORT                      _OFF
#endif

//--------------------------------------------------
// DP HBR & RBR Link Training Force Marginal Link(N+1)
//--------------------------------------------------
#ifndef _DP_HBR_RBR_LT_FORCE_MARGINAL_LINK
#define _DP_HBR_RBR_LT_FORCE_MARGINAL_LINK                      _ON
#endif

//--------------------------------------------------
// DP HBR2 Marginal Link Reduce to HBR
//--------------------------------------------------
#ifndef _DP_HBR2_MARGIN_LINK_SUPPORT
#define _DP_HBR2_MARGIN_LINK_SUPPORT                            _OFF
#endif

//--------------------------------------------------
// DP Link Training Directly Request Swing Level 2 at TP1 (Skip Swing Level 1)
//--------------------------------------------------
#ifndef _DP_LT_DIRECT_REQUEST_SWING_LEVEL_2
#define _DP_LT_DIRECT_REQUEST_SWING_LEVEL_2                     _ON
#endif

//--------------------------------------------------
// DP Input(Rx) Port Link Training Permit Swing Level 0 for Specific Source
//--------------------------------------------------
#ifndef _DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI
#define _DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI _OFF
#endif

//--------------------------------------------------
// DP Rx Compatilbe Solution to MI Dongle (Fake LT Lane Count + Long HPD after Timeout)
//--------------------------------------------------
#ifndef _DP_RX_MI_DONGLE_SUPPORT
#define _DP_RX_MI_DONGLE_SUPPORT                                _OFF
#endif

//--------------------------------------------------
//  GDI Passive DFE Fine Tune Flow
//--------------------------------------------------
#if(_HW_DP_GDI_RX0_DFE_TYPE == _PASSIVE_DFE)
#ifndef _DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE
#define _DP_RX0_PASSIVE_DFE_FINE_TUNE_TYPE                      _FINE_TUNE_DFE_BY_1_LANE
#endif
#endif

#if(_HW_DP_GDI_RX1_DFE_TYPE == _PASSIVE_DFE)
#ifndef _DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE
#define _DP_RX1_PASSIVE_DFE_FINE_TUNE_TYPE                      _FINE_TUNE_DFE_BY_1_LANE
#endif
#endif

//--------------------------------------------------
// DP ASSR Option
//--------------------------------------------------
#ifndef _D0_DP_ASSR_MODE_SUPPORT
#define _D0_DP_ASSR_MODE_SUPPORT                                _OFF
#endif

#ifndef _D1_DP_ASSR_MODE_SUPPORT
#define _D1_DP_ASSR_MODE_SUPPORT                                _OFF
#endif

//--------------------------------------------------
// DP Aux Reply Timeout by User Option
//--------------------------------------------------
#ifndef _DP_AUX_REPLY_TIMEOUT_BY_USER
#define _DP_AUX_REPLY_TIMEOUT_BY_USER                           _OFF
#endif

#ifndef _DP_AUX_REPLY_TIMEOUT_USER_SETTING
#define _DP_AUX_REPLY_TIMEOUT_USER_SETTING                      0x0D
#endif

//--------------------------------------------------
// DP Aux Reply Ref. Clk Select From
//--------------------------------------------------
#ifndef _DP_AUX_REPLY_CLK_SEL_FROM
#define _DP_AUX_REPLY_CLK_SEL_FROM                              _DP_AUX_REPLY_SEL_IOSC
#endif

//--------------------------------------------------
// DP pull-up Long HPD or not (after CPIRQ) by User Option
//--------------------------------------------------
#ifndef _DP_LONG_HPD_AFTER_CPIRQ_SUPPORT
#define _DP_LONG_HPD_AFTER_CPIRQ_SUPPORT                        _ON
#endif

//--------------------------------------------------
// DP MST Option
//--------------------------------------------------
#ifndef _D0_DP_MST_PORT_SUPPORT
#if(_DP_MST_SUPPORT == _ON)
#define _D0_DP_MST_PORT_SUPPORT                                 _ON
#else
#define _D0_DP_MST_PORT_SUPPORT                                 _OFF
#endif
#endif

#ifndef _D1_DP_MST_PORT_SUPPORT
#if(_DP_MST_SUPPORT == _ON)
#define _D1_DP_MST_PORT_SUPPORT                                 _ON
#else
#define _D1_DP_MST_PORT_SUPPORT                                 _OFF
#endif
#endif

//--------------------------------------------------
// DP MST CAP ON to OFF No HPD (For EIZO USE)
//--------------------------------------------------
#ifndef _DP_MST_CAP_ON_TO_OFF_NO_HPD
#define _DP_MST_CAP_ON_TO_OFF_NO_HPD                            _OFF
#endif

//--------------------------------------------------
// DC On DP Long HPD Toggled Control By User
//--------------------------------------------------
#ifndef _DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT
#define _DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT                   _OFF
#endif

//--------------------------------------------------
// DP MST Cap On Inactive Port HPD Low (For EIZO USE)
//--------------------------------------------------
#ifndef _DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW
#define _DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW                    _OFF
#endif

//--------------------------------------------------
// DP Tx Link Config Control by User (For EIZO USE)
//--------------------------------------------------
#ifndef _DP_TX_CONFIG_BY_USER_SUPPORT
#define _DP_TX_CONFIG_BY_USER_SUPPORT                           _OFF
#endif

//-------------------------------------------------
// MST Auto Search Support
//-------------------------------------------------
#ifndef _DP_MST_AUTO_SEARCH_SUPPORT
#define _DP_MST_AUTO_SEARCH_SUPPORT                             _OFF
#endif

//--------------------------------------------------
// DP Rx Interlace New mode for VG877 and QD980 Certain Interlace Timing
//--------------------------------------------------
#ifndef _DP_RX_INTERLACE_NEW_MODE_SUPPORT
#define _DP_RX_INTERLACE_NEW_MODE_SUPPORT                       _OFF
#endif

//--------------------------------------------------
// DP IRQ HPD Implementation Mode
//--------------------------------------------------
#ifndef _DP_IRQ_HPD_MODE
#define _DP_IRQ_HPD_MODE                                        _DP_IRQ_HPD_T2_MODE
#endif

//-------------------------------------------------
// DP MST Down Reply IRQ Retry
//-------------------------------------------------
#ifndef _DP_MST_DOWN_REPLY_MSG_TIME_OUT_RETRY_MAX
#define _DP_MST_DOWN_REPLY_MSG_TIME_OUT_RETRY_MAX               4
#endif

//--------------------------------------------------
// DP MST DC Off HPD High Tx Active (for HP Use)
//--------------------------------------------------
#ifndef _DP_MST_DC_OFF_HPD_HIGH_TX_ACTIVE_SUPPORT
#define _DP_MST_DC_OFF_HPD_HIGH_TX_ACTIVE_SUPPORT               _OFF
#endif
//===================== END =======================


////////////
// TYPE C //
////////////

//--------------------------------------------------
// USB Type C PD Controller Alt Mode Option
//--------------------------------------------------
#ifndef _TYPE_C_VENDOR_ALT_MODE
#define _TYPE_C_VENDOR_ALT_MODE                                 _TYPE_C_VENDOR_ALT_MODE_NONE
#endif

//==================== START ======================

//-------------------------------------------------
// USB Type C PD Controller Pin Assignment E Support Switch Option
//-------------------------------------------------
#ifndef _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT
#define _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT         _OFF
#endif

//--------------------------------------------------
// USB Type C External PD Controller Option
//--------------------------------------------------
#ifndef _TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION
#define _TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION                  _TYPE_C_LANE_SWAP_BY_PORT_CTRL
#endif

//===================== END =======================


/////////
// MHL //
/////////

//--------------------------------------------------
// MHL2.x Option
//--------------------------------------------------
#ifndef _MHL_CBUS_CTS_MODE
#define _MHL_CBUS_CTS_MODE                                      _OFF
#endif

#ifndef _MHL2_UCP_SUPPORT
#define _MHL2_UCP_SUPPORT                                       _OFF
#endif

#ifndef _MHL2_AUD_CHANNEL
#define _MHL2_AUD_CHANNEL                                       _MHL_AUD_2CH
#endif

#ifndef _MHL2_ADOPTER_ID
#define _MHL2_ADOPTER_ID                                        0x0000
#endif

#ifndef _MHL2_DEVICE_ID
#define _MHL2_DEVICE_ID                                         0x0000
#endif

#ifndef _MHL2_PP_MODE_SUPPORT
#define _MHL2_PP_MODE_SUPPORT                                   _ON
#endif

//==================== START ======================

//--------------------------------------------------
// MHL3.x Option
//--------------------------------------------------
#ifndef _MHL3_UCP_SUPPORT
#define _MHL3_UCP_SUPPORT                                       _OFF
#endif

#ifndef _MHL3_AUD_CHANNEL
#define _MHL3_AUD_CHANNEL                                       _MHL_AUD_2CH
#endif

#ifndef _MHL3_ECBUS_HID_SUPPORT
#define _MHL3_ECBUS_HID_SUPPORT                                 _OFF
#endif

#ifndef _MHL3_ADOPTER_ID
#define _MHL3_ADOPTER_ID                                        0x0000
#endif

#ifndef _MHL3_DEVICE_ID
#define _MHL3_DEVICE_ID                                         0x0000
#endif

#ifndef _MHL3_16_BIT_MODE_SUPPORT
#define _MHL3_16_BIT_MODE_SUPPORT                               _ON
#endif

#ifndef _MHL3_ECBUS_HID_SUPPORT
#define _MHL3_ECBUS_HID_SUPPORT                                 _OFF
#endif

//===================== END =======================


///////////
// Audio //
///////////

//-------------------------------------------------
// Audio Option
//-------------------------------------------------
#ifndef _AUDIO_SUPPORT
#define _AUDIO_SUPPORT                                          _OFF
#endif

//==================== START ======================

//--------------------------------------------------
// Audio Manual Sampling Frequency Option
//--------------------------------------------------
#ifndef _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT
#define _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT                     _OFF
#endif

#ifndef _FIX_SAMPLING_FREQ_TYPE
#define _FIX_SAMPLING_FREQ_TYPE                                 _FIX_FREQ_48KHZ
#endif

//===================== END =======================

//-------------------------------------------------
// Audio DAC Option
//-------------------------------------------------
#ifndef _EMBEDDED_DAC_SUPPORT
#define _EMBEDDED_DAC_SUPPORT                                   _OFF
#endif

//==================== START ======================
#ifndef _DAC_SPEAKER_OUTPUT_SUPPORT
#define _DAC_SPEAKER_OUTPUT_SUPPORT                             _ON // Should be _OFF if the related pinout is used as GPIO funtion
#endif

#ifndef _DAC_HP_OUTPUT_SUPPORT
#define _DAC_HP_OUTPUT_SUPPORT                                  _ON // Should be _OFF if the related pinout is used as GPIO funtion
#endif

#ifndef _DAC_SPEAKER_OUTPUT_SWAP
#define _DAC_SPEAKER_OUTPUT_SWAP                                _OFF
#endif

#ifndef _DAC_HP_OUTPUT_SWAP
#define _DAC_HP_OUTPUT_SWAP                                     _OFF
#endif

#ifndef _DAC_DEPOP_TO_NORMAL_WAIT_TIME
#define _DAC_DEPOP_TO_NORMAL_WAIT_TIME                          SEC(0.1)
#endif

#ifndef _DAC_DITHER_FUNCTION_LEVEL
#define _DAC_DITHER_FUNCTION_LEVEL                              _AUDIO_DAC_DITHER_LEVEL_OFF
#endif
//===================== END =======================

//-------------------------------------------------
// Audio Line In Option
//-------------------------------------------------
#ifndef _LINE_IN_SUPPORT
#define _LINE_IN_SUPPORT                                        _OFF
#endif

#ifndef _LINE_IN_DAC_AOUT_GAIN_DB
#define _LINE_IN_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _LINE_IN_DAC_HPOUT_GAIN_DB
#define _LINE_IN_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _LINE_IN_BOOST_GAIN_DB
#define _LINE_IN_BOOST_GAIN_DB                                  0x17                        // 0dB, 1.5dB for each step, Max Gain: 0x3F(30dB)
#endif

#ifndef _LINE_IN_VOLUME_MAX
#define _LINE_IN_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#endif

#ifndef _LINE_IN_VOLUME_MIN
#define _LINE_IN_VOLUME_MIN                                     0x0000
#endif

//==================== START ======================

//--------------------------------------------------
// Audio Line In AA DAC Bypass Option
//--------------------------------------------------
#ifndef _LINE_IN_AA_PATH_SUPPORT
#define _LINE_IN_AA_PATH_SUPPORT                                _OFF
#endif

//--------------------------------------------------
// Audio Line In Support For DP TX Clone Option
//--------------------------------------------------
#ifndef _LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT
#define _LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT                      _ON
#endif

//===================== END =======================

//-------------------------------------------------
// Audio Digital Option
//-------------------------------------------------
#ifndef _DIGITAL_DAC_AOUT_GAIN_DB
#define _DIGITAL_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _DIGITAL_DAC_HPOUT_GAIN_DB
#define _DIGITAL_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _DIGITAL_VOLUME_MAX
#define _DIGITAL_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#endif

#ifndef _DIGITAL_VOLUME_MIN
#define _DIGITAL_VOLUME_MIN                                     0x0000
#endif

//-------------------------------------------------
// Audio PS Option
//-------------------------------------------------
#ifndef _SLEEP_AUDIO_SUPPORT
#define _SLEEP_AUDIO_SUPPORT                                    _OFF
#endif

#ifndef _PS_AUDIO_INPUT
#define _PS_AUDIO_INPUT                                         _PS_AUDIO_LINE_IN
#endif

//==================== START ======================

//--------------------------------------------------
// Digital Volume Control Option --> For Audio Mute
//--------------------------------------------------
#ifndef _DVC_ADJUST_TYPE
#define _DVC_ADJUST_TYPE                                        _DB_GAIN
#endif

#ifndef _DB_GAIN_DOWN_VALUE
#define _DB_GAIN_DOWN_VALUE                                     _DB_GAIN_1_8_DB   // For _DB_GAIN
#endif

#ifndef _DB_GAIN_UP_VALUE
#define _DB_GAIN_UP_VALUE                                       _DB_GAIN_1_8_DB   // For _DB_GAIN
#endif

#ifndef _VOLUME_STEP_SIZE_VALUE
#define _VOLUME_STEP_SIZE_VALUE                                 (0x0040 & 0x3FFF) // For _VOLUME_STEP_SIZE
#endif

#ifndef _DVC_VOLUME_MUTE_TIMER
#define _DVC_VOLUME_MUTE_TIMER                                  400 // ms
#endif

//--------------------------------------------------
// DP Volume Control Option --> For Audio Mute / Unmute
//--------------------------------------------------
#ifndef _DP_DVC_ADJUST_TYPE
#define _DP_DVC_ADJUST_TYPE                                     _DB_GAIN
#endif

#ifndef _DP_DB_GAIN_DOWN_VALUE
#define _DP_DB_GAIN_DOWN_VALUE                                  _DB_GAIN_1_8_DB   // For _DB_GAIN Mode
#endif

#ifndef _DP_DB_GAIN_UP_VALUE
#define _DP_DB_GAIN_UP_VALUE                                    _DB_GAIN_1_8_DB   // For _DB_GAIN Mode
#endif

#ifndef _DP_VOLUME_STEP_SIZE_VALUE
#define _DP_VOLUME_STEP_SIZE_VALUE                              (0x40 & 0xFF) // For _VOLUME_STEP Mode
#endif

#ifndef _DP_DVC_VOLUME_MUTE_TIMER
#define _DP_DVC_VOLUME_MUTE_TIMER                               400 // ms
#endif

//--------------------------------------------------
// Audio Manual Sampling Frequency Option
//--------------------------------------------------
#ifndef _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT
#define _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT                     _OFF
#endif

#ifndef _FIX_SAMPLING_FREQ_TYPE
#define _FIX_SAMPLING_FREQ_TYPE                                 _FIX_FREQ_48KHZ
#endif

//--------------------------------------------------
// Switch Audio Source to Line In When Entering Power Saving Mode Option
//--------------------------------------------------
#ifndef _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE
#define _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE           _OFF
#endif

//-------------------------------------------------
// Audio Hard Gain Option
//-------------------------------------------------
#ifndef _AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT
#define _AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT                     _OFF
#endif

#ifndef _LINE_IN_HARD_GAIN_VALUE
#define _LINE_IN_HARD_GAIN_VALUE                                _HARD_GAIN_0_DB
#endif

#ifndef _DIGITAL_HARD_GAIN_VALUE
#define _DIGITAL_HARD_GAIN_VALUE                                _HARD_GAIN_0_DB
#endif

//-------------------------------------------------
// Audio Digital Output(I2S/SPDIF) Adjust Volume Option
//-------------------------------------------------
#ifndef _DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT
#define _DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT             _OFF
#endif

//===================== END =======================


///////////////////
// Misc Function //
///////////////////

//-------------------------------------------------
// Instant Timer Events Option
//-------------------------------------------------
#ifndef _INSTANT_TIMER_EVENT_0
#define _INSTANT_TIMER_EVENT_0                                  _OFF
#endif

#ifndef _INSTANT_TIMER_EVENT_1
#define _INSTANT_TIMER_EVENT_1                                  _OFF
#endif

//==================== START ======================

//--------------------------------------------------
// Code Digital Signature Support Option
//--------------------------------------------------
#ifndef _CODE_DIGITAL_SIGNATURE_SUPPORT
#define _CODE_DIGITAL_SIGNATURE_SUPPORT                         _SIGNATURE_TYPE_OFF
#endif

#ifndef _SIGNATURE_INTERNAL_ISP_START_BANK
#define _SIGNATURE_INTERNAL_ISP_START_BANK                      0
#endif

#ifndef _SIGNATURE_INTERNAL_BIN_BANK_SIZE
#define _SIGNATURE_INTERNAL_BIN_BANK_SIZE                       0
#endif

#ifndef _SIGNATURE_INTERNAL_PROTECT_DATA_BANK
#define _SIGNATURE_INTERNAL_PROTECT_DATA_BANK                   0
#endif

//--------------------------------------------------
// Code Digital Signature Vendor Type
//--------------------------------------------------
#ifndef _CODE_DIGITAL_SIGNATURE_VENDOR_TYPE
#define _CODE_DIGITAL_SIGNATURE_VENDOR_TYPE                     _SIGNATURE_VENDOR_NONE
#endif
//===================== END =======================

//--------------------------------------------------
// IRDA Option
//--------------------------------------------------
#ifndef _IR_SUPPORT
#define _IR_SUPPORT                                             _IR_OFF
#endif

//==================== START ======================

//--------------------------------------------------
// UART Option
//--------------------------------------------------
#ifndef _UART_SUPPORT
#define _UART_SUPPORT                                           _OFF
#endif

#ifndef _UART_BAUD_RATE_POWER_NORMAL
#define _UART_BAUD_RATE_POWER_NORMAL                            9600 // 9600/19200/14400/28800/38400/56000 Baud (Unit in Baud)
#endif

#ifndef _UART_BAUD_RATE_POWER_SAVING
#define _UART_BAUD_RATE_POWER_SAVING                            9600 // 9600/19200/14400/28800/38400/56000 Baud (Unit in Baud)
#endif

//-------------------------------------------------
// System Timer 250us Option --> SW IR Application
//-------------------------------------------------
#ifndef _SYSTEM_TIMER_QUARTER_RESOLUTION
#define _SYSTEM_TIMER_QUARTER_RESOLUTION                        _OFF
#endif

//--------------------------------------------------
//  Factory Debug Option --> Extern ScalerSetByte, ScalerGetByte, ScalerSetBit, ScalerGetBit to User
//--------------------------------------------------
#ifndef _FACTORY_DEBUG_SUPPORT
#define _FACTORY_DEBUG_SUPPORT                                  _OFF
#endif

//--------------------------------------------------
// Display Garbage Prevent Method Option
//--------------------------------------------------
#ifndef _DISPLAY_PREVENT_GARBAGE_METHOD
#define _DISPLAY_PREVENT_GARBAGE_METHOD                         _GARBAGE_PREVENT_BY_WATCH_DOG
#endif

//-------------------------------------------------
// Panel Power Sequence Control by User Option
//-------------------------------------------------
#ifndef _PANEL_POWER_SEQUENCE_CONTROL_BY_USER
#define _PANEL_POWER_SEQUENCE_CONTROL_BY_USER                   _OFF
#endif

//-------------------------------------------------
// Color Process Control by User Option
//-------------------------------------------------
#ifndef _COLOR_PROCESS_CONTROL_BY_USER
#define _COLOR_PROCESS_CONTROL_BY_USER                          _OFF
#endif

//-------------------------------------------------
// Flash Enable Write protect Option
//-------------------------------------------------
#ifndef _FLASH_WR_PROTECT
#define _FLASH_WR_PROTECT                                       _OFF
#endif

//--------------------------------------------------
// FLASH Write SR Mode Select Eable Write SR CMD
//--------------------------------------------------
#ifndef _FLASH_EWSR_FUNCTION_SUPPORT
#define _FLASH_EWSR_FUNCTION_SUPPORT                            _OFF
#endif

//--------------------------------------------------
// Power Saving Precision Clock Option
//--------------------------------------------------
#ifndef _SYS_PS_TIMER_PRECISION_SUPPPORT
#define _SYS_PS_TIMER_PRECISION_SUPPPORT                        _OFF
#endif

//-----------------------------------------------------
// Hw DDCCI Buffer None Reply Null Msg Support
// For HP case, return Null Msg if Command isn't finish
//-----------------------------------------------------
#ifndef HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT
#define HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT            _OFF
#endif


/////////
// AIO //
/////////

//-------------------------------------------------
// AIO Modern Standby Support Option
//-------------------------------------------------
#ifndef _AIO_MODERN_STANDBY_SUPPORT
#define _AIO_MODERN_STANDBY_SUPPORT                             _OFF
#endif


//////////
// Acer //
//////////

//-------------------------------------------------
// Acer TMDS Toggle HPD & Z0 Option
//-------------------------------------------------
#ifndef _TMDS_TOGGLE_HPD_Z0_FOR_ACER
#define _TMDS_TOGGLE_HPD_Z0_FOR_ACER                            _OFF
#endif


//////////
// Asus //
//////////

//-------------------------------------------------
// Asus Auto Search Time Option --> (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)
//-------------------------------------------------
#ifndef _SOURCE_ASUS_START_AUTO_TIME
#define _SOURCE_ASUS_START_AUTO_TIME                            SEC(2)
#endif


//////////
// DELL //
//////////

//--------------------------------------------------
// DELL DP D3 Options --> for DELL
//--------------------------------------------------
#ifndef _DP_DELL_D3_TEST_SUPPORT
#define _DP_DELL_D3_TEST_SUPPORT                                _OFF
#endif

//--------------------------------------------------
// DELL DP Dynamic Adjust Link Rate --> for DELL
//--------------------------------------------------
#ifndef _DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT
#define _DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT                    _OFF
#endif

//--------------------------------------------------
// DELL AUX not reply when DP HPD low
//--------------------------------------------------
#ifndef _DP_HPD_LOW_AUX_NOT_REPLY_SUPPORT
#define _DP_HPD_LOW_AUX_NOT_REPLY_SUPPORT                       _OFF
#endif


/////////////
// PHILIPS //
/////////////

//--------------------------------------------------
// PHILIPS Pixel-shift Support Option
//--------------------------------------------------
#ifndef _PIXEL_SHIFT_SUPPORT
#define _PIXEL_SHIFT_SUPPORT                                    _OFF
#endif


////////
// HP //
////////

//--------------------------------------------------
// HP Source Scan Define Option
//--------------------------------------------------
#ifndef _HP_SOURCE_SCAN_SUPPORT
#define _HP_SOURCE_SCAN_SUPPORT                                 _OFF
#endif

#ifndef _HP_SOURCE_SCAN_TYPE
#define _HP_SOURCE_SCAN_TYPE                                    _HP_SOURCE_SCAN_TYPE_F
#endif


//////////
// Eizo //
//////////

//--------------------------------------------------
// Eizo DP Sink Support OUI Under Ver1.1 Option
//--------------------------------------------------
#ifndef _DP_SINK_VER11_OUI_SUPPORT
#define _DP_SINK_VER11_OUI_SUPPORT                              _ON
#endif

//--------------------------------------------------
// Eizo DP Customized Value of DPCD Option
//--------------------------------------------------
#ifndef _EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT
#define _EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT                  _OFF
#endif

//--------------------------------------------------
// Eizo DP Tx Aux Communication Option
//--------------------------------------------------
#ifndef _DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT
#define _DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT               _OFF
#endif

//--------------------------------------------------
// Eizo DP DPCD Down Stream Port Count
//--------------------------------------------------
#ifndef _DP_1_1_DOWN_STREAM_PORT_COUNT
#define _DP_1_1_DOWN_STREAM_PORT_COUNT                          0x01
#endif

#ifndef _DP_1_2_DOWN_STREAM_PORT_COUNT
#define _DP_1_2_DOWN_STREAM_PORT_COUNT                          0x01
#endif

//--------------------------------------------------
// Eizo DP Ver1.1 DPCD Table Value of Sink IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_1_1_SINK_RTK_IEEE_OUI_L
#define _DP_1_1_SINK_RTK_IEEE_OUI_L                             0x00
#endif

#ifndef _DP_1_1_SINK_RTK_IEEE_OUI_M
#define _DP_1_1_SINK_RTK_IEEE_OUI_M                             0xE0
#endif

#ifndef _DP_1_1_SINK_RTK_IEEE_OUI_H
#define _DP_1_1_SINK_RTK_IEEE_OUI_H                             0x4C
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_0
#define _DP_1_1_SINK_RTK_ID_STRING_0                            0x00
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_1
#define _DP_1_1_SINK_RTK_ID_STRING_1                            0x00
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_2
#define _DP_1_1_SINK_RTK_ID_STRING_2                            0x00
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_3
#define _DP_1_1_SINK_RTK_ID_STRING_3                            0x00
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_4
#define _DP_1_1_SINK_RTK_ID_STRING_4                            0x00
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_5
#define _DP_1_1_SINK_RTK_ID_STRING_5                            0x00
#endif

//--------------------------------------------------
// Eizo DP Ver1.1 DPCD Table Value Of Sink HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_1_1_SINK_RTK_HW_VERSION
#define _DP_1_1_SINK_RTK_HW_VERSION                             0x00
#endif

#ifndef _DP_1_1_SINK_RTK_FW_VERSION_H
#define _DP_1_1_SINK_RTK_FW_VERSION_H                           0x00
#endif

#ifndef _DP_1_1_SINK_RTK_FW_VERSION_L
#define _DP_1_1_SINK_RTK_FW_VERSION_L                           0x00
#endif

//--------------------------------------------------
// Eizo DP Ver1.2 DPCD Table Value of Sink IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_1_2_SINK_RTK_IEEE_OUI_L
#define _DP_1_2_SINK_RTK_IEEE_OUI_L                             0x00
#endif

#ifndef _DP_1_2_SINK_RTK_IEEE_OUI_M
#define _DP_1_2_SINK_RTK_IEEE_OUI_M                             0xE0
#endif

#ifndef _DP_1_2_SINK_RTK_IEEE_OUI_H
#define _DP_1_2_SINK_RTK_IEEE_OUI_H                             0x4C
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_0
#define _DP_1_2_SINK_RTK_ID_STRING_0                            0x44
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_1
#define _DP_1_2_SINK_RTK_ID_STRING_1                            0x70
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_2
#define _DP_1_2_SINK_RTK_ID_STRING_2                            0x31
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_3
#define _DP_1_2_SINK_RTK_ID_STRING_3                            0x2E
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_4
#define _DP_1_2_SINK_RTK_ID_STRING_4                            0x32
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_5
#define _DP_1_2_SINK_RTK_ID_STRING_5                            0x00
#endif

//--------------------------------------------------
// Eizo DP Ver1.2 DPCD Table Value Of Sink HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_1_2_SINK_RTK_HW_VERSION
#define _DP_1_2_SINK_RTK_HW_VERSION                             0x00
#endif

#ifndef _DP_1_2_SINK_RTK_FW_VERSION_H
#define _DP_1_2_SINK_RTK_FW_VERSION_H                           0x00
#endif

#ifndef _DP_1_2_SINK_RTK_FW_VERSION_L
#define _DP_1_2_SINK_RTK_FW_VERSION_L                           0x00
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value Of Branch IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_1_1_BRANCH_RTK_IEEE_OUI_L
#define _DP_1_1_BRANCH_RTK_IEEE_OUI_L                           0x00
#endif

#ifndef _DP_1_1_BRANCH_RTK_IEEE_OUI_M
#define _DP_1_1_BRANCH_RTK_IEEE_OUI_M                           0xE0
#endif

#ifndef _DP_1_1_BRANCH_RTK_IEEE_OUI_H
#define _DP_1_1_BRANCH_RTK_IEEE_OUI_H                           0x4C
#endif

#ifndef _DP_1_2_BRANCH_RTK_IEEE_OUI_L
#define _DP_1_2_BRANCH_RTK_IEEE_OUI_L                           0x00
#endif

#ifndef _DP_1_2_BRANCH_RTK_IEEE_OUI_M
#define _DP_1_2_BRANCH_RTK_IEEE_OUI_M                           0xE0
#endif

#ifndef _DP_1_2_BRANCH_RTK_IEEE_OUI_H
#define _DP_1_2_BRANCH_RTK_IEEE_OUI_H                           0x4C
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_0
#define _DP_BRANCH_RTK_ID_STRING_0                              0x44
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_1
#define _DP_BRANCH_RTK_ID_STRING_1                              0x70
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_2
#define _DP_BRANCH_RTK_ID_STRING_2                              0x31
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_3
#define _DP_BRANCH_RTK_ID_STRING_3                              0x2E
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_4
#define _DP_BRANCH_RTK_ID_STRING_4                              0x32
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_5
#define _DP_BRANCH_RTK_ID_STRING_5                              0x00
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value Of Branch HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_BRANCH_RTK_HW_VERSION
#define _DP_BRANCH_RTK_HW_VERSION                               0x00
#endif

#ifndef _DP_BRANCH_RTK_FW_VERSION_H
#define _DP_BRANCH_RTK_FW_VERSION_H                             0x00
#endif

#ifndef _DP_BRANCH_RTK_FW_VERSION_L
#define _DP_BRANCH_RTK_FW_VERSION_L                             0x00
#endif


////////
// LG //
////////

//--------------------------------------------------
//  LG DP Power Management
//--------------------------------------------------
#ifndef _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER
#define _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER           _OFF
#endif

//===================== END =======================

