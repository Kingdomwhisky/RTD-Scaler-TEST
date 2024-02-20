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
// ID Code      : Project_Config_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_CONFIG_CHECK_H__
#define __PROJECT_CONFIG_CHECK_H__

//--------------------------------------------------
// Memory Config Check
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6369_SERIES) ||\
    (_SCALER_TYPE == _RL6463_SERIES) ||\
    (_SCALER_TYPE == _RL6492_SERIES))
#if((_MEMORY_SIZE_CONFIG != _EMBEDDED_MEMORY_SIZE_NONE) && (_MEMORY_SIZE_CONFIG != _1M_16BIT_SDRAM) && (_MEMORY_SIZE_CONFIG != _4M_16BIT_DDR1_1PC))
#warning "_MEMORY_SIZE_CONFIG is not supported!!!"
#endif
#endif

#if(_SCALER_TYPE == _RL6432_SERIES)
#if((_MEMORY_SIZE_CONFIG != _EMBEDDED_MEMORY_SIZE_NONE) && (_MEMORY_SIZE_CONFIG != _1M_16BIT_SDRAM) && (_MEMORY_SIZE_CONFIG != _4M_16BIT_DDR1_1PC) && (_MEMORY_SIZE_CONFIG != _4M_16BIT_DDR1_2PCS))
#warning "RL6432 Can Not Support This Memory Size!!!"
#endif
#endif

#if(_SCALER_TYPE == _RL6449_SERIES)
#if((_MEMORY_SIZE_CONFIG != _EMBEDDED_MEMORY_SIZE_NONE) && (_MEMORY_SIZE_CONFIG != _16M_16BIT_DDR2_1PC) && (_MEMORY_SIZE_CONFIG != _16M_16BIT_DDR2_2PCS))
#warning "RL6449 Can Not Support This Memory Size!!!"
#endif
#endif

#if(_OD_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_OD_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_FRC_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_FRC_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISPLAY_ROTATION_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISPLAY_HOR_MIRROR_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISPLAY_VER_MIRROR_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_FRC_FIXED_30_BIT_DATA_FORMAT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_FRC_FIXED_30_BIT_DATA_FORMAT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISP_LATENCY_ADJUST_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_FRC_SUPPORT == _ON)
#if(_HW_FRC_TYPE == _FRC_GEN_NONE)
#warning "_FRC_SUPPORT Can Not Be Supported With No FRC!!!"
#endif
#endif

//--------------------------------------------------
// Display Setting Check
//--------------------------------------------------
#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FORCE_TO_FREE_RUN_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FREEZE_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FRC_FIXED_30_BIT_DATA_FORMAT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_FRAME_SYNC_LINE_BUFFER_SUPPORT == _OFF) && (_FRC_SUPPORT == _OFF))
#if(_PANEL_STYLE != _PANEL_NONE)
#warning "_FRAME_SYNC_LINE_BUFFER_SUPPORT or _FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
#if(_ASPECT_RATIO_SUPPORT == _OFF)
#warning "_ASPECT_RATIO_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_DISPLAY_HOR_MIRROR_SUPPORT == _ON) || (_DISPLAY_VER_MIRROR_SUPPORT == _ON))
#if(_DISPLAY_ROTATION_SUPPORT == _OFF)
#warning "_DISPLAY_ROTATION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_FORCE_TO_FREE_RUN_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
#warning "_FRAME_SYNC_LINE_BUFFER_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if((_FREEZE_SUPPORT == _ON) && (_DISPLAY_ROTATION_SUPPORT == _ON))
#if(_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_I)
#if(_ROTATION_FREEZE_FORCE_TO_BACKGROUND == _OFF)
#warning "_ROTATION_FREEZE_FORCE_TO_BACKGROUND Should Be _ON!!!"
#endif
#elif(_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_II)
#warning "_FREEZE_SUPPORT and _DISPLAY_ROTATION_SUPPORT Can Not Be _ON At The Same Time!!!"
#endif
#endif

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
#if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
#warning "_ASPECT_RATIO_WITHOUT_MUTE Do Not Support VBO/eDP Panel!!!"
#endif
#endif

#if((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F))
#if(_MN_DPLL_PATH_TYPE == _MN_DPLL_PATH2)
#if(_MN_DPLL_FREQ_UP == _ON)
#warning "_MN_DPLL_PATH2 Can Not Support_MN_DPLL_FREQ_UP!!!"
#endif
#endif
#endif

#if(_MPLL_STRUCT_TYPE == _MPLL_STRUCT_M_N)
#if(_MN_MPLL_PATH_TYPE == _MN_MPLL_PATH2)
#if(_MN_MPLL_FREQ_UP == _ON)
#warning "_MN_MPLL_PATH2 Can Not _MN_MPLL_FREQ_UP!!!"
#endif
#endif
#endif

//--------------------------------------------------
// Motion Blur Reduction Check
//--------------------------------------------------
#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _ON)
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#warning "_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_FREESYNC_SUPPORT == _OFF)
#warning "_FREESYNC_SUPPORT Should Be _ON!!!"
#endif

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _OFF)
#warning "_MOTION_BLUR_REDUCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _OFF)
#warning "_MOTION_BLUR_REDUCTION_SUPPORT Should Be _ON!!!"
#endif

#if(_FORCE_TO_FREE_RUN_SUPPORT == _ON)
#warning "_FORCE_TO_FREE_RUN_SUPPORT Should Be _OFF!!!"
#endif
#endif

//-------------------------------------------------
// YPeaking & UltraVivid
//-------------------------------------------------
#if(_ULTRA_VIVID_SUPPORT == _ON)
#if(((_SCALER_TYPE == _RL6369_SERIES) && (_FREESYNC_SUPPORT == _ON)) ||\
    (_SCALER_TYPE == _RL6463_SERIES))

#if(_YPEAKING_SUPPORT == _OFF)
#warning "_YPEAKING_SUPPORT and _ULTRA_VIVID_SUPPORT Should Same Setting!!!"
#endif

#else

#if(_YPEAKING_SUPPORT == _ON)
#warning "_YPEAKING_SUPPORT or _ULTRA_VIVID_SUPPORT Should Be _OFF!!!"
#endif

#endif
#endif

//-------------------------------------------------
// ICM
//-------------------------------------------------
#if(_ICM_BRI_SUPPORT == _ON)
#if(_ICM_SUPPORT == _OFF)
#warning "_ICM_SUPPORT Should Be _ON!!!"
#endif
#endif

//--------------------------------------------------
// SCM Config Check
//--------------------------------------------------
#if(_SCM_SUPPORT == _ON)
#if((_SCALER_TYPE == _RL6369_SERIES) || (_SCALER_TYPE == _RL6463_SERIES))
#warning "_SCM_SUPPORT Should Be _OFF!!!"
#elif(_ICM_SUPPORT == _OFF)
#warning "_ICM_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
#if(_ICM_SUPPORT == _OFF)
#warning "_ICM_SUPPORT Should Be _ON!!!"
#endif
#endif

//--------------------------------------------------
// SixColor Config Check
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6369_SERIES)
#if(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_DELL_MODE)
#warning "_SIX_COLOR_ICM_DELL_MODE Can Not Be Supported!!!"
#endif
#endif

//-------------------------------------------------
// IAPS & DCR & DCC
//-------------------------------------------------
#if((_IAPS_SUPPORT == _ON) && (_DCR_SUPPORT == _ON))
#warning "_IAPS_SUPPORT or _DCR_SUPPORT Should Be _OFF!!!"
#endif

#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)

#if(_IAPS_SUPPORT == _ON)
#if(_DCC_HISTOGRM_INFO == _OFF)
#warning "_DCC_HISTOGRM_INFO Should Be _ON!!!"
#endif
#endif

#if((_IAPS_SUPPORT == _ON) && (_DCC_FUNCTION == _ON))
#warning "_IAPS_SUPPORT or _DCC_FUNCTION Should Be _OFF!!!"
#endif

#endif // End of #if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)

//-------------------------------------------------
// Dimming
//-------------------------------------------------
#if(_LOCAL_DIMMING_SUPPORT == _ON)

#if(_MCU_SPEED_UP_SUPPORT == _OFF)
#warning "_MCU_SPEED_UP_SUPPORT Should Be _ON!!!"
#endif

#if(_PCM_FUNCTION == _OFF)
#warning "_PCM_FUNCTION Should be _ON!!!"
#endif

#if(_OCC_SUPPORT == _OFF)
#warning " _OCC_SUPPORT Should be _ON!!!"
#endif

#endif

#if(_GLOBAL_DIMMING_SUPPORT == _ON)

#if(_PCM_FUNCTION == _OFF)
#warning "_PCM_FUNCTION Should be _ON!!!"
#endif

#if(_OCC_SUPPORT == _OFF)
#warning " _OCC_SUPPORT Should be _ON!!!"
#endif

#endif

#if(_GLOBAL_DIMMING_SUPPORT == _OFF)
#if(_GLOBAL_DIMMING_LOW_SENSITIVITY_SUPPORT == _ON)
#warning " _GLOBAL_DIMMING_LOW_SENSITIVITY_SUPPORT Should be _OFF!!!"
#endif
#endif

#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)

#if(_HIGHLIGHT_WINDOW_SUPPORT == _OFF)
#warning " _HIGHLIGHT_WINDOW_SUPPORT Should be _ON!!!"
#endif

#endif

#if(_LOCAL_DIMMING_SUPPORT == _OFF)

#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
#warning " _LD_TUNNEL_DETECT_SUPPORT Should be _OFF!!!"
#endif

#endif

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
#if((_LOCAL_DIMMING_SUPPORT == _OFF) || (_HDR10_SUPPORT == _OFF))
#warning " _LD_HDR10_BOOST_SUPPORT Should be _OFF!!!"
#endif
#endif

#if(_LD_FREESYNC_MODE_SUPPORT == _ON)
#if(_FREESYNC_SUPPORT == _OFF)
#warning " _FREESYNC_SUPPORT Should be _ON!!!"
#endif
#if(_LOCAL_DIMMING_SUPPORT == _OFF)
#warning " _LOCAL_DIMMING_SUPPORT Should be _ON!!!"
#endif
#endif

#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1)
#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
#warning " _LD_TUNNEL_DETECT_SUPPORT Should be _OFF!!!"
#endif
#endif


#if(_LD_FREESYNC_II_BOOST_SUPPORT == _ON)
#if(_LD_FREESYNC_MODE_SUPPORT == _OFF)
#warning " _LD_FREESYNC_MODE_SUPPORT Should be _ON!!!"
#endif

#if(_LD_HDR10_BOOST_SUPPORT == _OFF)
#warning " _LD_HDR10_BOOST_SUPPORT Should be _ON!!!"
#endif

#if(_FREESYNC_II_SUPPORT == _OFF)
#warning "FREESYNC_II_SUPPORT Should be _ON!!!"
#endif
#endif

//-------------------------------------------------
// Device
//-------------------------------------------------

#if((_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE) &&\
    (_DEVICE_LED_DRIVER_COMMUNICATE_TYPE == _INTERFACE_SPI) &&\
    (_SPI_SUPPORT == _OFF))
#warning "_SPI_SUPPORT Should Be _ON!!!"
#endif

//-------------------------------------------------
// Color effect of SDR to HDR
//-------------------------------------------------
#if(_SDR_TO_HDR_SUPPORT == _ON)

#if(_PCM_FUNCTION == _OFF)
#warning "_PCM_FUNCTION Should Be _ON!!!"
#endif

#if(_OCC_SUPPORT == _OFF)
#warning "_OCC_SUPPORT Should Be _ON!!!"
#endif

#if(_ICM_SUPPORT == _OFF)
#warning "_ICM_SUPPORT Should Be _ON!!!"
#endif

#if(_DCC_FUNCTION == _OFF)
#warning "_DCC_FUNCTION Should Be _ON!!!"
#endif

#endif

//-------------------------------------------------
// HDR10 Color Enhance & Light Enhance
//-------------------------------------------------
#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON!!!"
#endif
#if(_ICM_SUPPORT == _OFF)
#warning "_ICM_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON!!!"
#endif
#if(_IAPS_SUPPORT == _ON)
#warning "_IAPS_SUPPORT Should Be _OFF!!!"
#endif
#if(_DCC_FUNCTION == _OFF)
#warning "_DCC_FUNCTION Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// FreeSync2
//-------------------------------------------------
#if(_FREESYNC_II_SUPPORT == _ON)
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _OFF)
#warning "_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT Should Be _ON!!!"
#endif
#if((_LOCAL_DIMMING_SUPPORT == _ON) && (_FREESYNC_II_GLOBAL_BACKLIGHT_SUPPORT == _ON))
#warning "_LOCAL_DIMMING_SUPPORT and _FREESYNC_II_GLOBAL_BACKLIGHT_SUPPORT Should Not Be _ON at the same time!!!"
#endif
#endif

#if(_DP_FREESYNC_II_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _OFF)
#warning "_DP_FREESYNC_SUPPORT Should Be _ON!!!"
#endif
#if(_DP_HDR10_SUPPORT == _OFF)
#warning "_DP_HDR10_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _OFF)
#warning "_HDMI_FREESYNC_SUPPORT Should Be _ON!!!"
#endif
#if(_HDMI_HDR10_SUPPORT == _OFF)
#warning "_HDMI_HDR10_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FREESYNC_II_GLOBAL_BACKLIGHT_SUPPORT == _ON)
#if(_FREESYNC_II_SUPPORT == _OFF)
#warning "_FREESYNC_II_SUPPORT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// Color Cailibration
//-------------------------------------------------
#if(_OGC_SUPPORT == _ON)
#if((_SCALER_TYPE == _RL6369_SERIES) || (_SCALER_TYPE == _RL6463_SERIES))
#if(_OGC_TOTAL_GAMMA > 5)
#warning "_OGC_TOTAL_GAMMA Should Be <= 5!!!"
#endif
#else
#if(_OGC_TOTAL_GAMMA > 6)
#warning "_OGC_TOTAL_GAMMA Should Be <= 6!!!"
#endif
#endif
#endif

#if(_OGC_SUPPORT == _ON)
#if((_SCALER_TYPE == _RL6369_SERIES) || (_SCALER_TYPE == _RL6463_SERIES))
#if(_OGC_TOTAL_CT > 6)
#warning "_OGC_TOTAL_CT Should Be <= 6!!!"
#endif
#else
#if(_OGC_TOTAL_CT > 12)
#warning "_OGC_TOTAL_CT Should Be <= 12!!!"
#endif
#endif
#endif

#if(_OGC_SUPPORT == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_GAMMA_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_OGC_SUPPORT == _ON)
#if(_CONTRAST_SUPPORT == _OFF)
#warning "_CONTRAST_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_OCC_SUPPORT == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_GAMMA_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_RGB_GAMMA_FUNCTION == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_GAMMA_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_OGC_DICOM_SUPPORT == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_GAMMA_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_OCC_SUPPORT == _ON)
#if(_PCM_FUNCTION == _OFF)
#warning "_PCM_FUNCTION Should Be _ON!!!"
#endif
#endif

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
#if(_DDCCI_RXBUF_LENGTH < 128)
#if((_SCALER_TYPE == _RL6369_SERIES) ||\
    (_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6432_SERIES) ||\
    (_SCALER_TYPE == _RL6449_SERIES) ||\
    (_SCALER_TYPE == _RL6492_SERIES))
#warning "_DDCCI_RXBUF_LENGTH Should Be >= 128!!!"
#endif
#endif

#if((_DDCCI_OPCODE_VCP_DISP_CALIBRATION < 0xF0) || (_DDCCI_OPCODE_VCP_DISP_CALIBRATION > 0xFF))
#warning "Unreasonable OPCODE for Color Calibration!!!"
#endif

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_WRITE_FUNCTION_SUPPORT Should Be _ON!!!"
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
#if((_OGC_SUPPORT == _OFF) && (_OCC_SUPPORT == _OFF))
#warning "_OGC_SUPPORT or _OGC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_UNIFORMITY_SUPPORT == _OFF)
#if((_UNIFORMITY_1ST_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_2ND_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_3RD_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_4TH_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_5TH_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_6TH_TABLE_LEVEL != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_SUPPORT  Should Be  _ON!!!"
#endif
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#warning "_UNIFORMITY_SUPPORT Should BE _ON!!!"
#endif
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
#if((_UNIFORMITY_1ST_TABLE_LEVEL == _UNIFORMITY_NONE))
#warning "_UNIFORMITY_1ST_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#if((_UNIFORMITY_2ND_TABLE_LEVEL == _UNIFORMITY_NONE) && ((_UNIFORMITY_3RD_TABLE_LEVEL + _UNIFORMITY_4TH_TABLE_LEVEL + _UNIFORMITY_5TH_TABLE_LEVEL + _UNIFORMITY_6TH_TABLE_LEVEL) != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_2ND_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#if((_UNIFORMITY_3RD_TABLE_LEVEL == _UNIFORMITY_NONE) && ((_UNIFORMITY_4TH_TABLE_LEVEL + _UNIFORMITY_5TH_TABLE_LEVEL + _UNIFORMITY_6TH_TABLE_LEVEL) != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_3RD_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#if((_UNIFORMITY_4TH_TABLE_LEVEL == _UNIFORMITY_NONE) && ((_UNIFORMITY_5TH_TABLE_LEVEL + _UNIFORMITY_6TH_TABLE_LEVEL) != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_4TH_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#if((_UNIFORMITY_5TH_TABLE_LEVEL == _UNIFORMITY_NONE) && ((_UNIFORMITY_6TH_TABLE_LEVEL) != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_5TH_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#endif

#if 0//(_PANEL_EXIST_MULTIPANEL == _OFF)
#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
#if(_CONTRAST_SUPPORT == _OFF)
#warning "_CONTRAST_SUPPORT Should Be _ON!!!"
#endif
#endif
#endif

#if((_ULTRA_HDR_SUPPORT == _ON) && (_HW_DP_VSC_SDP_EXT_CAPABILITY_SUPPORT == _OFF))
#warning "_ULTRA_HDR_SUPPORT Should Be _OFF!!!"
#endif

#if((_ULTRA_HDR_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON) && (_HW_DP_TX_VSC_SDP_TRANSMIT_SUPPORT == _OFF) && (_EDID_HDR10_AUTO_SWITCH == _OFF))
#warning "DP Tx Clone Mode can't Support When _EDID_HDR10_AUTO_SWITCH is _OFF!!!"
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_OCC_SUPPORT == _OFF)
#warning "_OCC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_COLOR_PROCESS_CONTROL_BY_USER == _ON)
#warning "_COLOR_PROCESS_CONTROL_BY_USER Should Be _OFF!!!"
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
#if(_CONTRAST_SUPPORT == _OFF)
#warning "_CONTRAST_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_RGB_GAMMA_FUNCTION == _ON)
#warning "NOTE: _RGB_GAMMA_FUNCTION is _ON, please contact SD!!!"
#endif

//-------------------------------------------------
// Color Conversion Check
//-------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _OFF) ||\
    (_YCC_QUANTIZATION_RANGE_SUPPORT == _OFF))
#warning "_RGB_QUANTIZATION_RANGE_SUPPORT and _YCC_QUANTIZATION_RANGE_SUPPORT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// System Eeprom Check
//-------------------------------------------------
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _OFF)
#warning "_EEPROM_ACCESS_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// System Eeprom Emulation
//-------------------------------------------------
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_WRITE_FUNCTION_SUPPORT Should Be _ON!!!"
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif

#if((_SCALER_TYPE == _RL6369_SERIES) || (_SCALER_TYPE == _RL6463_SERIES))
#if((_OGC_FLASH_BANK == _SYSTEM_EEPROM_EMULATION_FLASH_BANK) &&\
    ((_SYSTEM_EEPROM_EMULATION_END_PAGE >= _OGC_FLASH_PAGE) &&\
    (_SYSTEM_EEPROM_EMULATION_START_PAGE < (_OGC_FLASH_PAGE + (((_OGC_SUPPORT == _ON) ? 2 : 0) + (((_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON)) ? 1 : 0))))))
#error "System Data Page & Color Calibration Data Page Overlap!!!"
#endif
#else
#if(_OGC_FLASH_BANK == _SYSTEM_EEPROM_EMULATION_FLASH_BANK)
#error "System Data Bank & Color Calibration Data Bank Overlap!!!"
#endif
#endif

#if(_SYSTEM_EEPROM_EMULATION_END_PAGE > 14)
#error "System Eeprom Emulation End Page Error!!!"
#endif

#if((_SYSTEM_EEPROM_EMULATION_END_PAGE - _SYSTEM_EEPROM_EMULATION_START_PAGE) < (_END_OF_PAGEID - _START_OF_PAGEID + 1))
#warning "Flash Page Number and Page ID Number Warning!!!"
#endif
#endif

//-------------------------------------------------
// EDID Check
//-------------------------------------------------
#if(_EDID_TABLE_LOCATED_IN_FLASH == _ON)
#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_WRITE_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// HDCP 2.2 Check
//-------------------------------------------------
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)

#if(_TMDS_HDCP_2_2_FUNCTION_SUPPORT == _OFF)
#warning "_TMDS_HDCP_2_2_SUPPORT Can Not Be Supported!!!"
#endif

#if(_HDMI_PORT_EXIST == _OFF)
#warning "_TMDS_HDCP_2_2_SUPPORT Can Not Be Supported!!!"
#endif

#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_DP_HDCP_2_2_FUNCTION_SUPPORT == _OFF)
#warning "_DP_HDCP_2_2_SUPPORT Can Not Be Supported!!!"
#endif
#endif

//--------------------------------------------------
// HDCP Key Location Check
//--------------------------------------------------
#ifdef __USER_COMMON_INTERFACE__

#if 0//((_DIGITAL_PORT_SUPPORT == _ON) && ((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE) || ((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE))))
#warning "NOTE: Please check HDCP KEY location!!"
#endif

#endif // End of #ifdef __USER_COMMON_INTERFACE__

//-------------------------------------------------
// HDCP Key Check
//-------------------------------------------------
#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_WRITE_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_EFUSE)
#if(_HDCP_1_4_KEY_EFUSE_SUPPORT == _OFF)
#warning "_HDCP_1_4_KEY_LOCATION Should Be _OFF!!! "
#endif
#endif

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_EFUSE)
#warning "_HDCP_2_2_KEY_LOCATION eFuse Can Not Be Supported!!! "
#endif

//--------------------------------------------------
// Write EDID/HDCP Table to NVRAM Check
//--------------------------------------------------
#ifdef __USER_COMMON_NVRAM_SYSTEM__

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#warning "NOTE: _WRITE_HDCP_TO_SYSTEM_EEPROM _ON!!"
#endif

#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
#warning "NOTE: _WRITE_EDID_TO_SYSTEM_EEPROM _ON!!"
#endif

#endif // End of #ifdef __USER_COMMON_NVRAM_SYSTEM__

//--------------------------------------------------
// External or Embedded 2 DP Switch Config Check
//--------------------------------------------------
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) || (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP))
#if((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE) ||\
    (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_DELL_STYLE))
#warning "_SOURCE_AUTO_SEARCH_STYLE you choose can't be supported when using External or Embedded DP Switch!!!"
#endif
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && ((_DP_HDR10_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON) || (_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)))
#if(_D0_DP_LINK_CLK_RATE != _D6_DP_LINK_CLK_RATE)
#warning "_D6_DP_LINK_CLK_RATE must equal to _D0_DP_LINK_CLK_RATE!!!"
#endif
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) &&\
    (_D2_INPUT_PORT_TYPE == _D2_DP_PORT) &&\
    ((_DP_HDR10_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON) || (_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)))
#warning "_D1_DP_PORT and _D2_DP_PORT Can't Support DP HDR in The Same Time!!!"
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) &&\
    (_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_DP_HDR10_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON) || (_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)))
#warning "_D0_DP_PORT and _D6_DP_PORT Can't Support DP HDR in The Same Time!!!"
#endif

//--------------------------------------------------
// VGA Check
//--------------------------------------------------
#if((_YPBPR_SUPPORT == _ON) && (_SOG_SUPPORT == _OFF))
#if(_SOG_SUPPORT == _OFF)
#warning "_SOG_SUPPORT Should Be _ON!!!"
#endif
#endif

//--------------------------------------------------
// Free Sync Check
//--------------------------------------------------
#if((_FORCE_TO_FREE_RUN_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
#if(_FREESYNC_SUPPORT == _ON)
#warning "_FREESYNC_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _OFF)
#warning "_DDCCI_AUTO_SWITCH_SUPPORT Should Be _ON!!!"
#endif

#if((_HDMI_FREESYNC_MCCS_VCP < 0xE0) || (_HDMI_FREESYNC_MCCS_VCP > 0xFF))
#warning "_HDMI_FREESYNC_MCCS_VCP Should Be in [0xE0:0xFF]!!!"
#endif

#endif
#endif

//--------------------------------------------------
// Source Switch Check
//--------------------------------------------------
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
#warning "_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT Should Be _OFF!!!"
#endif
#endif

//-------------------------------------------------
// HDMI Check
//-------------------------------------------------
#if(_HDMI_SUPPORT == _OFF)
#if(_DVI_DE_ONLY_SUPPORT == _ON)
#warning "_DVI_DE_ONLY_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI_FROM_DVI_CONNECT == _ON)
#warning "_HDMI_FROM_DVI_CONNECT Should Be _OFF!!!"
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#warning "_HDMI_FREESYNC_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#warning "_HDMI_FREESYNC_II_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
#warning "_HDMI_HDR10_SUPPORT Should Be _OFF!!!"
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#warning "_TMDS_HDCP_2_2_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
#if(_TMDS_HDCP_2_2_SUPPORT == _OFF)
#warning "_TMDS_HDCP_2_2_SUPPORT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// DP Check
//-------------------------------------------------
#if(_DP_MST_SUPPORT == _ON)
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))

#if((_D0_DP_MST_PORT_SUPPORT == _OFF) && (_D1_DP_MST_PORT_SUPPORT == _OFF))
#warning "_D0_DP_MST_PORT_SUPPORT or _D1_DP_MST_PORT_SUPPORT Should Be _ON!!!"
#endif

#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D0_DP_MST_PORT_SUPPORT == _OFF)
#warning "_D0_DP_MST_PORT_SUPPORT Should Be _ON!!!"
#endif

#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_D1_DP_MST_PORT_SUPPORT == _OFF)
#warning "_D1_DP_MST_PORT_SUPPORT Should Be _ON!!!"
#endif

#endif
#endif // End of #if(_DP_MST_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)
#if((_DP_HBR_RBR_LT_FORCE_MARGINAL_LINK == _OFF) && (_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON))
#warning "_DP_HBR_RBR_LT_FORCE_MARGINAL_LINK Should Be _ON when _DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON !!!"
#endif
#endif

#if(_OUTPUT_TYPE_PATH == _DP_TX_4_PATH)
#if(_DP_MST_SUPPORT == _ON)
#warning "_DP_MST_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_TX_SUPPORT == _ON)
#warning "_DP_TX_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_DP_TX_SUPPORT == _OFF)
#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
#warning "_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT Should Be _OFF!!!"
#endif
#endif

#if(_FW_DP_HDMI_COMPATIBLE_MODE_SUPPORT == _OFF)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#warning "_DP_HDMI_COMPATIBLE_MODE Should Be _OFF!!!"
#endif
#endif

#if(_FW_DP_POWER_OFF_HDCP_SUPPORT == _OFF)
#if(_DP_POWER_OFF_HDCP_SUPPORT == _ON)
#warning "_DP_POWER_OFF_HDCP_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if((_DP_HDMI_COMPATIBLE_MODE == _ON) || (_DP_POWER_OFF_HDCP_SUPPORT == _ON))
#warning "_DP_HDMI_COMPATIBLE_MODE & _DP_POWER_OFF_HDCP_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_DP_SUPPORT == _OFF)
#if(_DP_MST_SUPPORT == _ON)
#warning "_DP_MST_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
#warning "_DP_FREESYNC_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_FREESYNC_II_SUPPORT == _ON)
#warning "_DP_FREESYNC_II_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#warning "_DP_HDR10_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#warning "_DP_HDCP_2_2_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if((_AUDIO_SUPPORT == _OFF) && (_DP_FREESYNC_SUPPORT == _OFF))
#warning "Either _AUDIO_SUPPORT Should Be _ON or _DP_FREESYNC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDCP_2_2_SUPPORT == _OFF)
#warning "_DP_HDCP_2_2_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_LINK_CLK_RATE == _DP_LOW_SPEED_162MHZ)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_LINK_CLK_RATE == _DP_LOW_SPEED_162MHZ)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_LINK_CLK_RATE == _DP_LOW_SPEED_162MHZ)))
#if(_INPUTCLOCK_RANG_DP > 2160)
#warning "_INPUTCLOCK_RANG_DP must less than Link CLK Rate!!!"
#endif
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED_270MHZ)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED_270MHZ)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED_270MHZ)))
#if(_INPUTCLOCK_RANG_DP > 3600)
#warning "_INPUTCLOCK_RANG_DP must less than Link CLK Rate!!!"
#endif
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ)))
#if(_INPUTCLOCK_RANG_DP > 7200)
#warning "_INPUTCLOCK_RANG_DP must less than Link CLK Rate!!!"
#endif
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ)))
#if(_INPUTCLOCK_RANG_DP > 10800)
#warning "_INPUTCLOCK_RANG_DP must less than Link CLK Rate!!!"
#endif
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if(_INPUTCLOCK_RANG_DP > (_D0_DP_LINK_CLK_RATE * _D0_DP_MAIN_LINK_LANES * 90))
#warning "_D0_DP_LINK_CLK_RATE is not enough!!!"
#endif

#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_INPUTCLOCK_RANG_USBC > (_D0_DP_LINK_CLK_RATE * _D0_DP_MAIN_LINK_LANES * 90))
#warning "_D0_DP_LINK_CLK_RATE is not enough!!!"
#endif
#endif
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if(_INPUTCLOCK_RANG_DP > (_D1_DP_LINK_CLK_RATE * _D1_DP_MAIN_LINK_LANES * 90))
#warning "_D1_DP_LINK_CLK_RATE is not enough!!!"
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_INPUTCLOCK_RANG_USBC > (_D1_DP_LINK_CLK_RATE * _D1_DP_MAIN_LINK_LANES * 90))
#warning "_D1_DP_LINK_CLK_RATE is not enough!!!"
#endif
#endif
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if(_INPUTCLOCK_RANG_DP > (_D2_DP_LINK_CLK_RATE * _D2_DP_MAIN_LINK_LANES * 90))
#warning "_D2_DP_LINK_CLK_RATE is not enough!!!"
#endif
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_INPUTCLOCK_RANG_USBC > _INPUTCLOCK_RANG_DP)
#warning "_INPUTCLOCK_RANG_USBC must less than _INPUTCLOCK_RANG_DP!!!"
#endif
#endif
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if((_INPUTCLOCK_RANG_DP * 100000) > _HW_D0_INPUT_CLOCK_MAX)
#warning "_INPUTCLOCK_RANG_DP must less than _HW_D0_INPUT_CLOCK_MAX!!!"
#endif

#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_INPUTCLOCK_RANG_USBC * 100000) > _HW_D0_INPUT_CLOCK_MAX)
#warning "_INPUTCLOCK_RANG_USBC must less than _HW_D0_INPUT_CLOCK_MAX!!!"
#endif
#endif

#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if((_INPUTCLOCK_RANG_DP * 100000) > _HW_D1_INPUT_CLOCK_MAX)
#warning "_INPUTCLOCK_RANG_DP must less than _HW_D1_INPUT_CLOCK_MAX!!!"
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_INPUTCLOCK_RANG_USBC * 100000) > _HW_D1_INPUT_CLOCK_MAX)
#warning "_INPUTCLOCK_RANG_USBC must less than _HW_D1_INPUT_CLOCK_MAX!!!"
#endif
#endif

#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if((_INPUTCLOCK_RANG_DP * 100000) > _HW_D2_INPUT_CLOCK_MAX)
#warning "_INPUTCLOCK_RANG_DP must less than _HW_D2_INPUT_CLOCK_MAX!!!"
#endif
#endif

#if((_SCALER_TYPE == _RL6369_SERIES) || (_SCALER_TYPE == _RL6463_SERIES))
#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
#warning "_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT is not supported!!!"
#endif
#endif

//--------------------------------------------------
// Audio Check
//--------------------------------------------------
#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_PS_AUDIO_INPUT != _PS_AUDIO_DP))
#if(_LINE_IN_SUPPORT == _OFF)
#warning "_LINE_IN_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_PS_AUDIO_INPUT != _PS_AUDIO_LINE_IN))
#if(_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON)
#warning "_PS_AUDIO_INPUT Should Be _PS_AUDIO_LINE_IN!!!"
#endif
#endif

#if((_EMBEDDED_DAC_SUPPORT == _OFF) || (_LINE_IN_SUPPORT == _OFF))
#if(_LINE_IN_AA_PATH_SUPPORT == _ON)
#warning "_LINE_IN_AA_PATH_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_HW_AUDIO_DIGITAL_OUTPUT_ADJUST_VOLUME == _OFF)
#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
#warning "_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT Can Not Be Supported!!!"
#endif
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
#if((_DAC_SPEAKER_OUTPUT_SUPPORT == _OFF) && (_DAC_HP_OUTPUT_SUPPORT == _OFF))
#warning "_DAC_SPEAKER_OUTPUT_SUPPORT or _DAC_HP_OUTPUT_SUPPORT Should Be _ON!!!"
#endif
#endif // End of #if(_DAC_SPEAKER_OUTPUT_SUPPORT == _OFF) || (_DAC_HP_OUTPUT_SUPPORT == _OFF))

//--------------------------------------------------
// Type-C Check
//--------------------------------------------------
#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_DP_SUPPORT == _OFF))
#warning "Type-C Can't Work Under DP OFF Case ~ !!"
#endif

#if(_TYPE_C_EMB_DRP_PREFER == _TYPE_C_DRP_TRY_SRC)
#warning "'_TYPE_C_EMB_DRP_PREFER' Should Use '_TYPE_C_DRP_NO_PREFERENCE' or '_TYPE_C_DRP_TRY_SNK' for DP Rx Port"
#endif

#if(((_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0) || (_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_DRP)) && (_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON))
#warning "Type-C Fast Role Swap is Only Support in PD 3.0 and DRP Port !!!"
#endif

#if(((_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0) || (_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY)) && (_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON))
#warning "Type-C Programmable Power Supply(PPS) is Only Support in PD 3.0 and DRP/Source-only Port !!!"
#endif

#if(_TYPE_C_EMB_PD_VERSION > _HW_PD_SUPPORT_VERSION)
#warning "_TYPE_C_EMB_PD_VERSION is HIGHER than _HW_PD_SUPPORT_VERSION!!!"
#endif

#if((_TYPE_C_EMD_USB_SPEED == _TYPE_C_USB_2) && (_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_NOT_SUPPORT))
#warning "_TYPE_C_EMD_USB_SPEED(_TYPE_C_USB_2) should NOT higher _HW_USB_MAX_LINK_RATE_SUPPORT!!!"
#endif

#if((_TYPE_C_EMD_USB_SPEED == _TYPE_C_USB_3_GEN1) && (_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_5G))
#warning "_TYPE_C_EMD_USB_SPEED(_TYPE_C_USB_3_GEN1) should NOT higher _HW_USB_MAX_LINK_RATE_SUPPORT!!!"
#endif

#if((_TYPE_C_EMD_USB_SPEED == _TYPE_C_USB_3_GEN2) && (_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_10G))
#warning "_TYPE_C_EMD_USB_SPEED(_TYPE_C_USB_3_GEN2) should NOT higher _HW_USB_MAX_LINK_RATE_SUPPORT!!!"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_NOT_SUPPORT) && (_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT))
#warning "_HW_USB_SUPPORT_ROLE = _TYPE_C_USB_NOT_SUPPORT, _TYPE_C_EMB_USB_ROLE Should be _TYPE_C_USB_NOT_SUPPORT!!!"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_DEVICE_ONLY) && (_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_DEVICE_ONLY))
#warning "_HW_USB_SUPPORT_ROLE = _TYPE_C_USB_DEVICE_ONLY, _TYPE_C_EMB_USB_ROLE Should be _TYPE_C_USB_NOT_SUPPORT or _TYPE_C_USB_DEVICE_ONLY!!!"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_HOST_ONLY) && (_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_HOST_ONLY))
#warning "_HW_USB_SUPPORT_ROLE = _TYPE_C_USB_HOST_ONLY, _TYPE_C_EMB_USB_ROLE Should be _TYPE_C_USB_NOT_SUPPORT or _TYPE_C_USB_HOST_ONLY!!!"
#endif

#if((_TYPE_C_EMB_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_SNK_ONLY))
#warning "If _TYPE_C_EMB_POWER_SOURCE is _TYPE_C_VBUS_POWER_ONLY, _TYPE_C_EMB_PORT_ROLE should be _TYPE_C_PORT_SNK_ONLY!!!"
#endif

#if((_TYPE_C_EMB_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && ((_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_POWER_BANK_CC) || (_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_POWER_BANK_PD)))
#warning "If _TYPE_C_EMB_POWER_SOURCE is _TYPE_C_VBUS_POWER_ONLY, _TYPE_C_EMB_DC_OFF_OPTION Should NOT be _TYPE_C_DC_OFF_POWER_BANK_CC / _TYPE_C_DC_OFF_POWER_BANK_PD"
#endif

//--------------------------------------------------
// Acer Toggle Z0/HPD Check
//--------------------------------------------------
#if((_DVI_SUPPORT != _ON) && (_HDMI_SUPPORT != _ON))
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
#warning "_TMDS_TOGGLE_HPD_Z0_FOR_ACER Should Be _OFF!!!!"
#endif
#endif

//--------------------------------------------------
// Eizo Clock Lane Z0 Toggle in Power Saving Check
//--------------------------------------------------
#if((_HDMI_SUPPORT != _ON) || (!(_SCALER_TYPE == _RL6432_SERIES)))
#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
#warning "_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT Should Be _OFF!!!!"
#endif
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
#if(_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY < 50)
#warning "_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY Should Bigger Than 50!!!!"
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY > 1000)
#warning "_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY Should Smaller Than 1000!!!!"
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY < 50)
#warning "_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY Should Bigger Than 50!!!!"
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY > 1000)
#warning "_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY Should Smaller Than 1000!!!!"
#endif
#endif

//--------------------------------------------------
// TMDS HDMI 2.0 SCDC CTS Check
//--------------------------------------------------
#if(_HDMI_2_0_SUPPORT == _OFF)
#if(_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON)
#warning "_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT Should Be _OFF!!!"
#endif
#endif

//--------------------------------------------------
// Code Digital Signature Check
//--------------------------------------------------
#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_WRITE_FUNCTION_SUPPORT Should Be _ON!!!"
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif

#if(_DDCCI_RXBUF_LENGTH < 32)
#warning "_DDCCI_RXBUF_LENGTH Should Be >= 32!!!"
#endif

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL)
#if(_FLASH_PARTITION_RELOCATABLE_SUPPORT == _OFF)
#warning "_FLASH_PARTITION_RELOCATABLE_SUPPORT Should Be _ON!!!"
#endif

#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_NONE)
#warning "_FLASH_PARTITION_TYPE Should Not Be _FLASH_PARTITION_NONE!!!"
#endif
#endif
#endif

//--------------------------------------------------
// Flash Partition Boot/User Check
//--------------------------------------------------
#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

//--------------------------------------------------
// System Source Background Detection Define Check
//--------------------------------------------------
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)

#if(_SCALER_TYPE == _RL6492_SERIES)
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DP_PORT))
#warning "_SOURCE_BACKGROUND_DETECT_SUPPORT Should Not Be _ON while D1 DP or D2 DP Support ON!!!"
#endif
#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D2_INPUT_PORT_TYPE != _D2_NO_PORT))
#warning "_SOURCE_BACKGROUND_DETECT_SUPPORT Should Not Be _ON while D1 & D2 Both Support ON!!!"
#endif
#elif((_SCALER_TYPE == _RL6369_SERIES) || (_SCALER_TYPE == _RL6463_SERIES))
#warning "_SOURCE_BACKGROUND_DETECT_SUPPORT Should Not Be _ON for This IC!!!"
#endif

#if(_VGA_SUPPORT == _ON)
#warning "_SOURCE_BACKGROUND_DETECT_SUPPORT Should Not Be _ON while VGA Support!!!"
#endif

#endif

//--------------------------------------------------
// ID Domain High Speed Define Check
//--------------------------------------------------
#if(_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON)
#if((_SCALER_TYPE == _RL6449_SERIES) && (_DDR2_MEMORY_CLK_1200M_SUPPORT == _OFF))
#warning "_DDR2_MEMORY_CLK_1200M_SUPPORT Should Be _ON when _IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT is _ON!!!"
#endif
#endif

//-------------------------------------------------
// DP MST Auto Seaech Define Check
//-------------------------------------------------
#if((_DP_MST_AUTO_SEARCH_SUPPORT == _ON) && (_DP_MST_SUPPORT == _OFF))
#warning "_DP_MST_SUPPORT Should Be _ON while _DP_MST_AUTO_SEARCH_SUPPORT ON!!!"
#endif

//--------------------------------------------------
//  System Low Power Idle Define Check
//--------------------------------------------------
#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#warning "_SYSTEM_LOW_POWER_IDLE_SUPPORT Should Be _OFF when _SYSTEM_TIMER_QUARTER_RESOLUTION is _ON!!!"
#endif
#endif

#endif // End of #ifndef __PROJECT_CONFIG_CHECK_H__
