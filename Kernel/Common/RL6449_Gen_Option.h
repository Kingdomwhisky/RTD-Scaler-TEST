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
// ID Code      : RL6449_Gen_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_SCALER_TYPE == _RL6449_SERIES)

#ifndef __RL6449_GEN_OPTION__
#define __RL6449_GEN_OPTION__


////////
// HW //
////////

//--------------------------------------------------
// HW Input Port TMDS MAC USE
//--------------------------------------------------
#define _D0_TMDS_MAC_USE                                        _PAGE_NONE
#define _D1_TMDS_MAC_USE                                        _PAGE_NONE
#define _D2_TMDS_MAC_USE                                        _PAGE71
#define _D3_TMDS_MAC_USE                                        _PAGE72
#define _D4_TMDS_MAC_USE                                        _PAGE_NONE
#define _D5_TMDS_MAC_USE                                        _PAGE_NONE

//--------------------------------------------------
// HW Input Port Clock Max
//--------------------------------------------------
#define _HW_A0_INPUT_CLOCK_MAX                                  210000000 // Unit: Hz , VGA
#define _HW_D0_INPUT_CLOCK_MAX                                  ((_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON) ? (685000000) : (600000000)) // Unit: Hz , DP 1.2
#define _HW_D1_INPUT_CLOCK_MAX                                  ((_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON) ? (685000000) : (600000000)) // Unit: Hz , DP 1.2
#define _HW_D2_INPUT_CLOCK_MAX                                  600000000 // Unit: Hz , HDMI2.0 , MHL3.2
#define _HW_D3_INPUT_CLOCK_MAX                                  600000000 // Unit: Hz , HDMI2.0 , MHL3.2
#define _HW_D4_INPUT_CLOCK_MAX                                  _INPUT_NONE
#define _HW_D5_INPUT_CLOCK_MAX                                  _INPUT_NONE

//--------------------------------------------------
// HW Input Port DP MAC USE
//--------------------------------------------------
#define _D0_DP_MAC_USE                                          _PAGEB5
#define _D1_DP_MAC_USE                                          _PAGEB8
#define _D2_DP_MAC_USE                                          _PAGE_NONE

//--------------------------------------------------
// HW CEC Function Support
//--------------------------------------------------
#define _HW_HDMI_CEC_GEN                                        _HW_CEC_GEN_TYPE_0

//--------------------------------------------------
// HW PC99 FUNCTION SUPPORT
//--------------------------------------------------
#define _HW_PC99_SUPPORT                                        _OFF
#define _HW_PC99_VGADDC2_SUPPORT                                _OFF

//--------------------------------------------------
// Definitions of XRAM addresses
//--------------------------------------------------
#define _XRAM_ADDR_START                                        (0xD700)
#define _XRAM_ADDR_END                                          (0xF6FF)

//--------------------------------------------------
// Definitions of Combo Phy Support
//--------------------------------------------------
#define _HW_DIGITAL_PORT_COMBO_PHY_TYPE                         _DIGITAL_PORT_COMBO_PHY_NONE

//--------------------------------------------------
// HW DP Lane Swap Support
//--------------------------------------------------
#define _HW_DP_LANE_SWAP_SUPPORT                                _ON

//--------------------------------------------------
// HW DP PN Swap Support
//--------------------------------------------------
#define _HW_DP_PN_SWAP_SUPPORT                                  _ON

//--------------------------------------------------
// HW DP Aux Single Ended Mode Support
//--------------------------------------------------
#define _HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT                    _ON

//--------------------------------------------------
// DDC Mapping Switch
//--------------------------------------------------
#define _DDC_CHANNEL_SWITCH_SUPPORT                             _OFF

//--------------------------------------------------
// HW SarADC Support and Bit Num
//--------------------------------------------------
#define _HW_MCU_SARADC_SUPPORT                                  _SARADC_5BIT_MSB

//--------------------------------------------------
// MCU PWM Hw Clock Source refence M2Pll / 2
//--------------------------------------------------
#define _HW_MCU_PWM_HW_REF_HALF_OF_M2PLL                        _OFF

//--------------------------------------------------
// MCU PWM Support Bit
//--------------------------------------------------
#define _MCU_PWM_BIT_SUPPORT                                    _PWM_12BIT

//-------------------------------------------------
// FW Flash Clock Option
//-------------------------------------------------
#define _FLASH_CLK_SOURCE                                       _FLASH_EXT_XTAL_CLK

//-------------------------------------------------
// FW Access Flash Method
//-------------------------------------------------
#define _HW_FLASH_ACCESS_METHOD                                 _FLASH_PORT_ACCESS

//--------------------------------------------------
// HW Support LC Tank
//--------------------------------------------------
#define _LC_TANK_SUPPORT                                        _OFF

//--------------------------------------------------
// eFuse Support
//--------------------------------------------------
#define _EFUSE_SUPPORT                                          _OFF

//--------------------------------------------------
// IOSC Clock Frequncy Define
//--------------------------------------------------
#define _INTERNAL_OSC_XTAL                                      _IOSC28000K

//-------------------------------------------------
// M2PLL Structure
//-------------------------------------------------
#define _M2PLL_STRUCT_TYPE                                      _M2PLL_STRUCT_M_N

//-------------------------------------------------
// MPLL Structure
//-------------------------------------------------
#define _MPLL_STRUCT_TYPE                                       _MPLL_STRUCT_M_N

//--------------------------------------------------
// M-Domain Data Bit Max
//--------------------------------------------------
#define _M_DOMAIN_DATA_BIT_MAX                                  (_COLOR_DEPTH_10_BITS * 3)

//-------------------------------------------------
// DPLL Structure
//-------------------------------------------------
#define _DPLL_STRUCT_TYPE                                       _DPLL_STRUCT_M_N_CASCADE_N_F

//-------------------------------------------------
// DPLL Support Vco Band11
//-------------------------------------------------
#define _DPLL_BAND11_SUPPORT                                    _ON

//--------------------------------------------------
// DPLL vcorstb setting
//--------------------------------------------------
#define _DPLL_VCORSTB_NORMAL_VALUE                              0

//-------------------------------------------------
// PLL Edge Select Type
//-------------------------------------------------
#define _HW_PLL_EDGE_SELECT_TYPE                                _PLL_EDGE_GEN_1_DEFAULT_POSITIVE

//-------------------------------------------------
// PLL Auto Edge Select
//-------------------------------------------------
#define _HW_PLL_AUTO_EDGE_SELECT_SUPPORT                        _OFF

//--------------------------------------------------
// Select Fifo Frequency Reference Clk
//--------------------------------------------------
#define _FIFO_FREQ_LINE_BUFFER_SEL                              _SCALER_FIFO_FREQ_MPLL
#define _FIFO_FREQ_FRAME_BUFFER_SEL                             _SCALER_FIFO_FREQ_MPLL

//--------------------------------------------------
// TMDS Input Clock Online Measure Divider
//--------------------------------------------------
#define _TMDS_MEASURE_CLOCK_DIVIDER                             2

//--------------------------------------------------
// TMDS Input Clock Online Measure Counter
//--------------------------------------------------
#define _TMDS_MEASURE_CLOCK_COUNTER                             2000

//--------------------------------------------------
// TMDS 420 duplcate mode support
//--------------------------------------------------
#define _HW_TMDS_YUV420_DUPLICATE_MODE_SUPPORT                  _LOCAL_DIMMING_SUPPORT

//--------------------------------------------------
// ADC Support --> VGA & ADC Bandgap
//--------------------------------------------------
#define _ADC_SUPPORT                                            _ON

//--------------------------------------------------
// VGA capture Support
//--------------------------------------------------
#define _VGA_CAPTURE_SUPPORT                                    _ON

//--------------------------------------------------
// ADC Sampling Limitation
//--------------------------------------------------
#define _ADC_SAMPLE_CLOCK_LIMIT                                 2100000

//--------------------------------------------------
// ADC Limit Out Of Range
//--------------------------------------------------
#define _ADC_PIXEL_WIDTH_LIMIT                                  3200

//--------------------------------------------------
// Memory Type
//--------------------------------------------------
#define _MEMORY_TYPE                                            _EMBEDDED_MEMORY

//--------------------------------------------------
// FRC 3 Block Toggle Option
//--------------------------------------------------
#define _FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT                      _OFF

//--------------------------------------------------
// MN Frame Tracking Support
//--------------------------------------------------
#define _MN_FRAME_TRACKING_SUPPORT                              _ON

//--------------------------------------------------
// FRC Memory 2 frame
//--------------------------------------------------
#define _FRC_MEMORY_2_FRAME_SUPPORT                             _ON

//--------------------------------------------------
// One Frame FRC Support
//--------------------------------------------------
#define _ONE_FRAME_FRC_SUPPORT                                  _ON

//--------------------------------------------------
// FRC supports only for DOS-mode
//--------------------------------------------------
#define _HW_FRC_DOSMODE_ONLY_SUPPORT                            _OFF

//-------------------------------------------------
// OD Gen
//-------------------------------------------------
#define _OD_TABLE_TYPE                                          _OD_GEN_1
#define _OD_LUT_MODE                                            _OD_8BIT_LUT

//-------------------------------------------------
// Global DB Gen
//-------------------------------------------------
#define _HW_GLOBAL_DB_TYPE                                      _GLOBAL_DB_GEN_III

//-------------------------------------------------
// Display Format DB Gen
//-------------------------------------------------
#define _HW_DISPLAY_FORMAT_DB_TYPE                              _DIS_FORMAT_DB_GEN_I

//-------------------------------------------------
// Display Rotation Gen
//-------------------------------------------------
#define _DISPLAY_ROTATION_TYPE                                  _DISPLAY_ROTATION_GEN_II

//--------------------------------------------------
// I Domain Format Conversion
//--------------------------------------------------
#define _FORMAT_CONVERSION_SUPPORT                              _ON

//--------------------------------------------------
// On-line measure
//--------------------------------------------------
#define _IDOMAIN_ONLINE_MEASURE_SUPPORT                         _ON

//-------------------------------------------------
// IDither Gen
//-------------------------------------------------
#define _IDITHER_TYPE                                           _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT
#define _IDITHER_SD_MASK_SUPPORT                                _ON

//-------------------------------------------------
// Scale Down Gen
//-------------------------------------------------
#define _SCALING_DOWN_TYPE                                      _SD_GEN_1 // H_SD: 128 taps, V_SD: 64 taps

//-------------------------------------------------
// Scale Down Ratio
//-------------------------------------------------
#define _VSD_MAX_RATIO                                          15
#define _HSD_MAX_RATIO                                          15

//-------------------------------------------------
// Scale Up Gen
//-------------------------------------------------
#define _SCALING_UP_TYPE                                        _SU_GEN_0 // H_SU: 128 taps, V_SU: 128 taps
#define _HSU_128TAPS_SUPPORT                                    _ON
#define _HSU_96TAPS_SUPPORT                                     _OFF
#define _VSU_128TAPS_SUPPORT                                    _ON

//-------------------------------------------------
// UltraVivid Gen
//-------------------------------------------------
#define _ULTRA_VIVID_TABLE_TYPE                                 _ULTRA_VIVID_GEN_3

//-------------------------------------------------
// Color Conversion
//-------------------------------------------------
#define _COLOR_CONVERSION_TYPE                                  _COLOR_CONVERSION_GEN_2

//-------------------------------------------------
// DCC Gen
//-------------------------------------------------
#define _DCC_TABLE_TYPE                                         _DCC_GEN_1
#define _DCC_Y_BIT_MODE                                         _DCC_Y_10BIT

//-------------------------------------------------
// AUX TALK MODE LDO VOL Gen
//-------------------------------------------------
#define _HW_AUX_TALK_MODE_LDO_VOL_TYPE                          _AUX_TALK_MODE_GEN_1_ADJR_1_LDO_3BIT

//-------------------------------------------------
// ICM Gen
//-------------------------------------------------
#define _ICM_TABLE_TYPE                                         _ICM_GEN_3

//-------------------------------------------------
// Contrast Gen
//-------------------------------------------------
#define _CTS_TYPE                                               _CTS_GEN_1_12BIT

//-------------------------------------------------
// Brightness Gen
//-------------------------------------------------
#define _BRI_TYPE                                               _BRI_GEN_1_10BIT

//-------------------------------------------------
// DCR Gen
//-------------------------------------------------
#define _DCR_BIT_MODE                                           _DCR_GEN_1_0_10BIT

//-------------------------------------------------
// IAPS Gain Gen
//-------------------------------------------------
#define _IAPS_GAIN_COMPENSATION_TYPE                            _IAPS_GAIN_COMPENSATION_GEN_1

//-------------------------------------------------
// RGB 3D Gamma Gen
//-------------------------------------------------
#define _3D_GAMMA_TABLE_TYPE                                    _3D_GAMMA_GEN_1

//-------------------------------------------------
// PCM Gen
//-------------------------------------------------
#define _PCM_TABLE_TYPE                                         _PCM_GEN_0

//-------------------------------------------------
// Input Gamma Gen
//-------------------------------------------------
#define _INPUT_GAMMA_TABLE_TYPE                                 _INPUT_GAMMA_GEN_1

//-------------------------------------------------
// Output Gamma Gen
//-------------------------------------------------
#define _OUTPUT_GAMMA_TABLE_TYPE                                _OUTPUT_GAMMA_GEN_1

//-------------------------------------------------
// DDither Gen
//-------------------------------------------------
#define _DDITHER_TYPE                                           _DDITHER_GEN_1_6BIT_DITHERTBL

//-------------------------------------------------
// Multi Region Color Calibration Support
//-------------------------------------------------
#define _COLOR_CALIBRATION_SUPPORT_REGION_NUM                   _COLOR_1_REGION

//--------------------------------------------------
// HDCP2.2 Gen
//--------------------------------------------------
#define _HDCP_2_2_FUNCTION_GEN                                  _HDCP_2_2_GEN_2

//--------------------------------------------------
// TMDS HDCP2.2 Online AES Page Assign
//--------------------------------------------------
#define _TMDS_HDCP_2_2_RX0_ONLINE_AES_PAGE                      _PAGE_NONE
#define _TMDS_HDCP_2_2_RX1_ONLINE_AES_PAGE                      _PAGE2D
#define _TMDS_HDCP_2_2_RX2_ONLINE_AES_PAGE                      _PAGE2D
#define _TMDS_HDCP_2_2_RX3_ONLINE_AES_PAGE                      _PAGE2E
#define _TMDS_HDCP_2_2_RX4_ONLINE_AES_PAGE                      _PAGE_NONE
#define _TMDS_HDCP_2_2_RX5_ONLINE_AES_PAGE                      _PAGE_NONE

//--------------------------------------------------
// TMDS HDCP2.2 Support
//--------------------------------------------------
#define _TMDS_HDCP_2_2_FUNCTION_SUPPORT                         _ON

//--------------------------------------------------
// DP HDCP2.2 Support
//--------------------------------------------------
#define _DP_HDCP_2_2_FUNCTION_SUPPORT                           _ON

//--------------------------------------------------
// HDCP1.4 Key eFuse
//--------------------------------------------------
#define _HDCP_1_4_KEY_EFUSE_SUPPORT                             _OFF

//--------------------------------------------------
// HW HDMI 2.0 Support
//--------------------------------------------------
#define _HW_HDMI_2_0_SUPPORT_PORT                               _HDMI_2_0_D2_D3

//--------------------------------------------------
// HW Dual Link DVI Support
//--------------------------------------------------
#define _HW_DUAL_LINK_DVI_SUPPORT_PORT                          _DUAL_LINK_DVI_NONE

//--------------------------------------------------
// HW DP VSC SDP Colorimetry Support
//--------------------------------------------------
#define _HW_DP_VSC_SDP_EXT_CAPABILITY_SUPPORT                   _ON

//--------------------------------------------------
// HW DP DPCD Extension Physical Address (02200h ~ 02211h)
//--------------------------------------------------
#define _HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT            _OFF

//--------------------------------------------------
// HW DP VSC SDP Registers Support
//--------------------------------------------------
#define _HW_DP_VSC_SDP_REG_SUPPORT                              _OFF

//--------------------------------------------------
// HW DP Tx Mst2Sst VSC SDP Bypass Support
//--------------------------------------------------
#define _HW_DP_TX_VSC_SDP_TRANSMIT_SUPPORT                      _OFF

//--------------------------------------------------
// HW DP Video Fifo Size
//--------------------------------------------------
#define _HW_DP_RX_VIDEO_FIFO_SIZE                               (256 * 96)

//--------------------------------------------------
// HW Audio Line In Swap
//--------------------------------------------------
#define _HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP                    _OFF

//--------------------------------------------------
// HW Audio Line In For ADC Front and ckt Power control
//--------------------------------------------------
#define _HW_AUDIO_LINE_IN_AFE_POWER_TYPE                        _ADC_AFE_POWER_CONTROL_GEN_2

//--------------------------------------------------
// HW Digital Audio (I2S/SPDIF) Adjust Volume
//--------------------------------------------------
#define _HW_AUDIO_DIGITAL_OUTPUT_ADJUST_VOLUME                  _ON

//--------------------------------------------------
// DP InfoFrame Length
//--------------------------------------------------
#define _HW_DP_INFOFRAME_RSV0_LENGTH                            28
#define _HW_DP_INFOFRAME_RSV1_LENGTH                            28
#define _HW_DP_INFOFRAME_RSV2_LENGTH                            0

//--------------------------------------------------
// HW GDI DFE TYPE
//--------------------------------------------------
#define _HW_DP_GDI_RX0_DFE_TYPE                                 _ADAPTIVE_DFE
#define _HW_DP_GDI_RX1_DFE_TYPE                                 _ADAPTIVE_DFE

//--------------------------------------------------
// HW FRC TYPE
//--------------------------------------------------
#define _HW_FRC_TYPE                                            _FRC_GEN_1

//--------------------------------------------------
// HW GDI DFE TYPE
//--------------------------------------------------
#define _HW_HS_TRACKING_GEN_TYPE                                _HS_TRACKING_GEN_2

//--------------------------------------------------
// _PWM_RST_BY_TCON SELECT
//--------------------------------------------------
#define _HW_PWM_RST_BY_TCON_SELECT                              _TCON8

//--------------------------------------------------
// USB3 Retimer Support
//--------------------------------------------------
#define _HW_USB3_RETIMER_SUPPORT                                _OFF

//--------------------------------------------------
// _TYPE_C_SUPPORT_VERSION SELECT
//--------------------------------------------------
#define _HW_TYPE_C_SUPPORT_VERSION                              _TYPE_C_VERSION_NULL

//--------------------------------------------------
// _PD_SUPPORT_VERSION SELSCT
//--------------------------------------------------
#define _HW_PD_SUPPORT_VERSION                                  _PD_VERSION_3_0

//--------------------------------------------------
// _HW_USB_SUPPORT_ROLE SELSCT
//--------------------------------------------------
#define _HW_USB_SUPPORT_ROLE                                    _TYPE_C_USB_NOT_SUPPORT

//--------------------------------------------------
// _HW_USB_MAX_LINK_RATE_SUPPORT SELSCT
//--------------------------------------------------
#define _HW_USB_MAX_LINK_RATE_SUPPORT                           _USB_SPEED_NOT_SUPPORT

//--------------------------------------------------
// HW GDI DFE TYPE
//--------------------------------------------------
#define _HW_SIGNAL_MEASURE_GEN_TYPE                             _SIGNAL_MEASURE_GEN_1

//--------------------------------------------------
// HW DP Lane Valid Check Support
//--------------------------------------------------
#define _HW_DP_LANE_VALID_CHECK_SUPPORT                         _ON

//--------------------------------------------------
// HW DP D0 MAX LINK RATE
//--------------------------------------------------
#define _HW_DP_D0_MAX_LINK_RATE_SUPPORT                         _DP_HIGH_SPEED2_540MHZ

//--------------------------------------------------
// HW DP D1 MAX LINK RATE
//--------------------------------------------------
#define _HW_DP_D1_MAX_LINK_RATE_SUPPORT                         _DP_HIGH_SPEED2_540MHZ

//--------------------------------------------------
// HW DP D2 MAX LINK RATE
//--------------------------------------------------
#define _HW_DP_D2_MAX_LINK_RATE_SUPPORT                         _DP_LINK_SPEED_NONE

//--------------------------------------------------
// HW DP HDCP circuit count
//--------------------------------------------------
#define _HW_DP_HDCP_CIRCUIT_COUNT                               2

//--------------------------------------------------
// HW DP RX HDCP2 Online AES Circuit Count
//--------------------------------------------------
#define _HW_DP_RX_HDCP2_ONLINE_AES_COUNT                        _DP_RX_HDCP2_ONLINE_AES_2SET

//--------------------------------------------------
// HW DP MST MAC MAX Bandwidth
//--------------------------------------------------
#define _HW_DP_MST_MAC_MAX_BW                                   _DP_MST_PBN_2560

//--------------------------------------------------
// HW DP Tx MAX DPCD VERSION
//--------------------------------------------------
#define _HW_DP_TX_MAX_LINK_RATE_SUPPORT                         _DP_HIGH_SPEED2_540MHZ

//--------------------------------------------------
// HW VGIP Bit
//--------------------------------------------------
#define _HW_VGIP_H_WIDTH_BIT_WIDTH                              (_13_BIT)

#define _HW_VGIP_V_START_BIT_WIDTH                              (_13_BIT)
#define _HW_VGIP_V_HEIGHT_BIT_WIDTH                             (_13_BIT)
#define _HW_VGIP_V_DELAY_BIT_WIDTH                              (_10_BIT)

//--------------------------------------------------
// HW DVtotal Bit
//--------------------------------------------------
#define _HW_DIS_TIMING_GEN_VTOTAL_BIT                           (_14_BIT)

//--------------------------------------------------
// HW HDMI Audio Frequency Detection for 176.4kHz/192kHz
//--------------------------------------------------
#define _HW_HDMI_AUDIO_AFD_MODE_FOR_176P4_192                   _AUDIO_AFD_HW_MODE


////////
// FW //
////////

//-------------------------------------------------
// FW Project Default Include
//-------------------------------------------------
#define _RLXXXX_PROJECT_DEFAULT                                 "RL6449_Project_Default.h"

//-------------------------------------------------
// FW Pcb Default Include
//-------------------------------------------------
#define _RLXXXX_PCB_DEFAULT                                     "RL6449_Pcb_Default.h"

//-------------------------------------------------
// FW M2PLL Freq
//-------------------------------------------------
#define _M2PLL_FREQ_SEL                                         _M2PLL_FREQ_351M

//-------------------------------------------------
// FW TMDS DDC Debounce Counter
//-------------------------------------------------
#define _TMDS_DDC_DEBOUNCE_NORMAL                               ((_MCU_SPEED_UP_SUPPORT == _ON) ? 230 * 2 : 230)
#define _TMDS_DDC_DEBOUNCE_PS                                   55

//--------------------------------------------------
// FW Underscan
//--------------------------------------------------
#define _UNDERSCAN_SUPPORT                                      _OFF

//-------------------------------------------------
// FW Display Rotation
//-------------------------------------------------
#define _DISPLAY_ROTATION_90_SUPPORT                            _OFF
#define _DISPLAY_ROTATION_180_SUPPORT                           _ON
#define _DISPLAY_ROTATION_270_SUPPORT                           _OFF

//--------------------------------------------------
// FW Pixel Shift Mode
//--------------------------------------------------
#define _PIXEL_SHIFT_MODE                                       _PIXEL_SHIFT_IN_IDOMAIN

//--------------------------------------------------
// Panel Uniformity SRAM MAX SIZE
//--------------------------------------------------
#define _PANEL_UNIFORMITY_MAX_GAIN_LUT_SIZE                     46200

//--------------------------------------------------
// _TYPE_C_ACC_SUPPORT_TYPE SELSCT
//--------------------------------------------------
#define _TYPE_C_ACC_SUPPORT_TYPE                                _TYPE_C_ACC_NO_SUPPORT

//--------------------------------------------------
// FW Support DP/HDMI Compatible Mode Support for Eizo
//--------------------------------------------------
#define _FW_DP_HDMI_COMPATIBLE_MODE_SUPPORT                     _OFF

//--------------------------------------------------
// FW Support DP Power OFF HDCP1.4 Handshake
//--------------------------------------------------
#define _FW_DP_POWER_OFF_HDCP_SUPPORT                           _OFF

//--------------------------------------------------
// Definitions PWM Frequency
//--------------------------------------------------
#define _PWM_FREQ_DVSRST_BOUND                                  1000

#define _PWM_ACT_MODE_FREQ_LOW_BOUND                            16
#define _PWM_ACT_MODE_FREQ_UPPER_BOUND                          55000

#define _PWM_PSPD_MODE_FREQ_LOW_BOUND                           2
#define _PWM_PSPD_MODE_FREQ_UPPER_BOUND                         3417

//--------------------------------------------------
// FW Support System Low Power Idle
//--------------------------------------------------
#define _FW_SYSTEM_LOW_POWER_IDLE_SUPPORT                       _OFF

//--------------------------------------------------
// FW Signature Move Key Define
//-------------------------------------------------

// Xdata limit for Move Key
#define _FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT                     _OFF

// Max xdata buf can Userd for Signature Move Key
// effective when _FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT = _ON
// value Should be >=2
#define _FW_MOVE_SIGNATURE_INFO_XDATA_LIMIT_MAX_BUF             20

////////
// IP //
////////

#include "RL6449_OSD_Gen_Option.h"

#endif // End of #ifndef __RL6449_GEN_OPTION__
#endif // End of #if(_SCALER_TYPE == _RL6449_SERIES)
