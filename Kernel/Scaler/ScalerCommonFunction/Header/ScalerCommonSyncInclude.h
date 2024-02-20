/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonSyncInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DP MN PLL Settings
//--------------------------------------------------
#define _PATH1                                              1
#define _PATH2                                              0
#define _PLL_FREQ_DOWN                                      1
#define _PLL_FREQ_UP                                        0
#define _DP_MN_PLL_PATH_TYPE                                _PATH1
#define _DP_MN_PLL_FREQUENCY_TREND                          _PLL_FREQ_UP
#define _DP_MN_PLL_VCO_FREQ_RANGE                           ((_DP_MN_PLL_PATH_TYPE == _PATH2) ? ((_DP_MN_PLL_FREQUENCY_TREND == _PLL_FREQ_UP) ? 7 : 9) : 8)
#define _DP_MN_PLL_DECIDE_M_CODE_FACTOR                     80 // Determine Target VCO Frequency is Within Ratio(100%) of VCO Frequency
#define _DP_HS_TRACKING_STABLE_PE_THRESHOLD                 31 // Threshold of Phase Error Lock of HS Tracking

#if(!(((_DP_MN_PLL_PATH_TYPE == _PATH1) && (_DP_MN_PLL_FREQUENCY_TREND == _PLL_FREQ_UP)) ||\
      ((_DP_MN_PLL_PATH_TYPE == _PATH2) && (_DP_MN_PLL_FREQUENCY_TREND == _PLL_FREQ_DOWN))))
#warning "DP MN_PLL Config Can't be Supported!!!"
#endif

//--------------------------------------------------
// Definition of Margin Link Parameter
//--------------------------------------------------
#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
#define _DP_HBR2_MARGIN_LINK_TIME_CRITERIA                  30
#define _DP_HBR2_MARGIN_LINK_ERROR_CRITERIA                 10
#endif
#endif

//--------------------------------------------------
// TMDS Options for HDMI 2.0
//--------------------------------------------------

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Define for Clk Freq Detection
//--------------------------------------------------
#define _TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND            (WORD)((DWORD)600 * 1040 / ((_GDI_CLK_KHZ * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER)) // (600 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz)
#define _TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND             (WORD)((DWORD)340 * 1040 / ((_GDI_CLK_KHZ * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER)) // (340 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz)
#define _TMDS_FREQ_NORMAL_LOWER_BOUND                       (WORD)((DWORD)_TMDS_CLOCK_MEASURE_LOWER_BOUNDARY * 960 / ((_GDI_CLK_KHZ * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER)) // (25 / _TMDS_MEASURE_CLOCK_DIVIDER) * (0.96) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz)

#define _TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND                (WORD)((DWORD)600 * 1040 * 10 / ((_INTERNAL_OSC_XTAL * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER * 9)) // (600 / _TMDS_MEASURE_CLOCK_DIVIDER) * 1.04 * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 0.9)
#define _TMDS_FREQ_PS_LOW_SPEED_UPPER_BOUND                 (WORD)((DWORD)340 * 1040 * 10 / ((_INTERNAL_OSC_XTAL * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER * 9)) // (340 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 0.9)
#define _TMDS_FREQ_PS_LOWER_BOUND                           (WORD)((DWORD)_TMDS_CLOCK_MEASURE_LOWER_BOUNDARY * 960 * 10 / ((_INTERNAL_OSC_XTAL * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER * 11)) // (25 / _TMDS_MEASURE_CLOCK_DIVIDER) * (0.96) * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 1.1)

#if(_MHL_SUPPORT == _ON)

#define _TMDS_MHL_FREQ_NORMAL_UPPER_BOUND                   (WORD)((((DWORD)150 * 1040 + (_TMDS_MEASURE_CLOCK_DIVIDER * (_GDI_CLK_KHZ / _TMDS_MEASURE_CLOCK_COUNTER)) / 2) / (_GDI_CLK_KHZ / _TMDS_MEASURE_CLOCK_COUNTER)) / _TMDS_MEASURE_CLOCK_DIVIDER) // (150 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz) + 0.5
#define _TMDS_MHL_FREQ_PS_UPPER_BOUND                       (WORD)((((DWORD)150 * 1040 * 10 + (_TMDS_MEASURE_CLOCK_DIVIDER * (_INTERNAL_OSC_XTAL / _TMDS_MEASURE_CLOCK_COUNTER * 9))) / (_INTERNAL_OSC_XTAL / _TMDS_MEASURE_CLOCK_COUNTER * 9)) / _TMDS_MEASURE_CLOCK_DIVIDER) // (150 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 0.9) + 1 = 3210

#endif // End of #if(_MHL_SUPPORT == _ON)

//--------------------------------------------------
// Define for Video Detect
//--------------------------------------------------
#define _TMDS_VIDEO_DATA_NONE                               0
#define _TMDS_VIDEO_DATA_DE_ONLY                            1
#define _TMDS_VIDEO_DATA_RGBHV                              2

//--------------------------------------------------
// Define for Watch Dog Type
//--------------------------------------------------
#define _HDMI_AVI_INFO_VARIATION_WD                         _BIT0
#define _HDMI_AV_MUTE_WD                                    _BIT1

//--------------------------------------------------
// Define for Packet Type
//--------------------------------------------------
#define _HDMI_3D_FORMAT                                     0x81
#define _HDMI_AVI_INFO_TYPE                                 0x82
#define _HDMI_AUDIO_INFO_TYPE                               0x84
#define _HDMI_GENERAL_CONTROL_TYPE                          0x03

//--------------------------------------------------
// Definitions of MHL Mode for Physical Settings
//--------------------------------------------------
#define _TMDS_24BIT_PHY_SETTING                             0x00
#define _TMDS_MHL_PPMODE_PHY_SETTING                        0x01
#define _TMDS_MHL_ECBUS_PHY_SETTING                         0x02

#if(_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of HDMI 2.0 SCDC Read Request Done Outcome
//--------------------------------------------------
#define _HDMI_2_0_READ_REQUEST_ACK_DONE                     0x00
#define _HDMI_2_0_READ_REQUEST_ACK_STOP                     0x10
#define _HDMI_2_0_READ_REQUEST_NACK1                        0x20
#define _HDMI_2_0_READ_REQUEST_NACK2                        0x30
#define _HDMI_2_0_READ_REQUEST_NONE                         0x70
#endif // #if(_HDMI_2_0_SUPPORT == _ON)

//--------------------------------------------------
// Definitions of TMDS HPD Time
//--------------------------------------------------
#define _TMDS_HPD_TIME_NONE                                 0
#define _TMDS_HDCP_2_2_HPD_TIME                             1000
#define _TMDS_ACER_HPD_TIME                                 130
#define _TMDS_EDID_SWITCH_HPD_TIME                          600
#endif // #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

//--------------------------------------------------
// Define for SPD Packet Type
//--------------------------------------------------
#if((_FREESYNC_SUPPORT == _ON) || (_FREESYNC_II_SUPPORT == _ON))
#define _SPD_INFO_TYPE                                      0x83
#endif

//--------------------------------------------------
// Define for HDR Packet Type
//--------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
#define _HDR_INFO_TYPE                                      0x87
#endif

//--------------------------------------------------
// Define for Audio Time Stamp Packet Type
//--------------------------------------------------
#define _DP_AUDIO_TIMESTAMP                                 0x01

//--------------------------------------------------
// Definition of Max of Measure timeout
//--------------------------------------------------
#define _DP_MEASURE_POLLING_TIMEOUT                         100

//--------------------------------------------------
// Definition of DP Display Format Parameter
//--------------------------------------------------
#define _DP_VSYNC_FRONT_PORCH                               4 // For VS bypass
#define _DP_HSYNC_FRONT_PORCH                               8
#define _DP_VSYNC_FRONT_PORCH_MST2SST                       (WORD)((((WORD)ScalerGetByte(PA_18_MSA_VTT_0) << 8) | ScalerGetByte(PA_19_MSA_VTT_1)) - (((WORD)ScalerGetByte(PA_1A_MSA_VST_0) << 8) | ScalerGetByte(PA_1B_MSA_VST_1)) - (((WORD)ScalerGetByte(PA_1C_MSA_VHT_0) << 8) | ScalerGetByte(PA_1D_MSA_VHT_1)))
#define _DP_VSYNC_WIDTH                                     3
#define _DP_VSYNC_WIDTH_MST2SST                             (WORD)(((WORD)ScalerGetByte(PA_1E_MSA_VSW_0) << 8) | ScalerGetByte(PA_1F_MSA_VSW_1))
#define _DP_HSYNC_WIDTH_MEASURE_COUNTER                     2 // = HSW msa * Measure clk / Pixel clk
#define _DP_DE_ONLY_MODE_HSW                                20
#define _DP_DE_ONLY_MODE_HSTART                             18
#define _DP_DE_ONLY_MODE_VSW                                2
#define _DP_DE_ONLY_MODE_VSTART                             8
#define _DP_FREESYNC_DV_SYNC_HEIGHT                         1
#define _DP_ONE_FRAME_TIME_MAX                              45 // in ms @ 23Hz
#define _DP_TWO_FRAME_TIME_MAX                              (_DP_ONE_FRAME_TIME_MAX * 2) // in ms @ 23Hz

//--------------------------------------------------
// Definitions of DP Link Training Stage
//--------------------------------------------------
#define _DP_TRAINING_PATTERN_END                            0
#define _DP_TRAINING_PATTERN_1                              1
#define _DP_TRAINING_PATTERN_2                              2
#define _DP_TRAINING_PATTERN_3                              3
#define _DP_TRAINING_PATTERN_4                              7

//--------------------------------------------------
// Definitions of DP Aux Setting Initial Value
//--------------------------------------------------
#define _DP_AUX_INITIAL_DIFF_MODE                           1
#define _DP_AUX_INITIAL_ADJR                                3

//--------------------------------------------------
// Definitions of DP HDCP Info
//--------------------------------------------------
#define _DP_HDCP_SHA1_INPUT_SIZE                            64

#if(_MHL_SUPPORT == _ON)
//****************************************************************************
// Definitions of MHL Packets
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Reply List
//--------------------------------------------------
#define _MHL_SUCCESS                                        0
#define _MHL_FAIL                                           1
#define _MHL_ABORT_FAIL                                     2
#define _MHL_PROTOCOL_ERROR                                 3

//--------------------------------------------------
// Definitions of MHL Status
//--------------------------------------------------
#define _MHL_STATE_INITIAL                                  0
#define _MHL_STATE_WAKE_UP_DONE                             1
#define _MHL_STATE_DISCOVERY_DONE                           2
#define _MHL_STATE_SET_DEV_CAP_DONE                         3
#define _MHL_STATE_DEV_CAP_RDY                              4
#define _MHL_STATE_HPD_DONE                                 5
#define _MHL_STATE_PATH_EN_DONE                             6
#define _MHL_STATE_DONE                                     7

//--------------------------------------------------
// Definitions of MHL Packet Types
//--------------------------------------------------
#define _DDC_PACKET                                         0
#define _MSC_PACKET                                         2

#define _MSC_SEND_DATA                                      0
#define _MSC_SEND_COMMAND                                   1
#define _MSC_SEND_COM_DAT                                   2
#define _MSC_SEND_COM_OFF_DAT                               3
#define _MSC_SEND_COM_OFF_DAT_COM                           4
#define _MSC_SEND_COM_OFF                                   5

#define _MSC_WAIT_NULL                                      0
#define _MSC_WAIT_COMMAND                                   1
#define _MSC_WAIT_DATA                                      2
#define _MSC_WAIT_COM_DAT                                   3

#define _MSC_ACK_PACKET                                     0x33
#define _MSC_NACK_PACKET                                    0x34
#define _MSC_ABORT_PACKET                                   0x35
#define _MSC_EOF_PACKET                                     0x32
#define _MSC_PROTOCOL_ERROR                                 0x02

//--------------------------------------------------
// Definitions of MHL Adopter ID
//--------------------------------------------------
#define _HTC_BUTTERFLY_ADOPTER_ID_HBYTE                     0x01
#define _HTC_BUTTERFLY_ADOPTER_ID_LBYTE                     0x6F

#define _SAMSUNG_SII_ADOPTER_ID_HBYTE                       0x00
#define _SAMSUNG_SII_ADOPTER_ID_LBYTE                       0x00

#define _UTS800_SL863_ADOPTER_ID_HBYTE                      0x01
#define _UTS800_SL863_ADOPTER_ID_LBYTE                      0x42

#define _HUAWEI_D2_ADOPTER_ID_HBYTE                         0x01
#define _HUAWEI_D2_ADOPTER_ID_LBYTE                         0x42

#define _ZTE_NUBIA_Z5_ADOPTER_ID_HBYTE                      0x01
#define _ZTE_NUBIA_Z5_ADOPTER_ID_LBYTE                      0x42

#define _ASUS_PADFONE2_ADOPTER_ID_HBYTE                     0x05
#define _ASUS_PADFONE2_ADOPTER_ID_LBYTE                     0x2C

#define _CHROMA_MHL_ADOPTER_ID_HBYTE                        0x05
#define _CHROMA_MHL_ADOPTER_ID_LBYTE                        0xB2

#define _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE                     0x01
#define _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE                     0x41

//--------------------------------------------------
// Macros of MHL Write Burst ID
//--------------------------------------------------
#define _MHL_3D_VIC_HB                                      0x00
#define _MHL_3D_VIC_LB                                      0x10
#define _MHL_3D_DTD_HB                                      0x00
#define _MHL_3D_DTD_LB                                      0x11
#define _MSC_NONE                                           0xFF

#endif // End of #if(_MHL_SUPPORT == _ON)

//--------------------------------------------------
// Macro of Input Pixel Clk (Unit in 0.1MHz)
//--------------------------------------------------
#define GET_INPUT_PIXEL_CLK()                               (g_usInputPixelClk)
#define SET_INPUT_PIXEL_CLK(x)                              (g_usInputPixelClk = (x))
#define CLR_INPUT_PIXEL_CLK()                               (g_usInputPixelClk = 0)

//--------------------------------------------------
// Macro of Input Pixel Clk (Unit in 0.1MHz)
//--------------------------------------------------
#define GET_TMDS_OFFLINE_MEASURE_CLK()                      (g_usTmdsOffLineMeasureClk)
#define SET_TMDS_OFFLINE_MEASURE_CLK(x)                     (g_usTmdsOffLineMeasureClk = (x))
#define CLR_TMDS_OFFLINE_MEASURE_CLK()                      (g_usTmdsOffLineMeasureClk = 0)

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Digital Input Port Switch
//--------------------------------------------------
#define GET_DIGITAL_PORT_SWITCH_TO_D0()                     ((g_ucDigitalSwitch & _BIT5) >> 5)
#define SET_DIGITAL_PORT_SWITCH_TO_D0()                     (g_ucDigitalSwitch |= _BIT5)
#define CLR_DIGITAL_PORT_SWITCH_TO_D0()                     (g_ucDigitalSwitch &= ~_BIT5)

#define GET_DIGITAL_PORT_SWITCH_TO_D1()                     ((g_ucDigitalSwitch & _BIT4) >> 4)
#define SET_DIGITAL_PORT_SWITCH_TO_D1()                     (g_ucDigitalSwitch |= _BIT4)
#define CLR_DIGITAL_PORT_SWITCH_TO_D1()                     (g_ucDigitalSwitch &= ~_BIT4)

#define GET_DIGITAL_PORT_SWITCH_TO_D2()                     ((g_ucDigitalSwitch & _BIT3) >> 3)
#define SET_DIGITAL_PORT_SWITCH_TO_D2()                     (g_ucDigitalSwitch |= _BIT3)
#define CLR_DIGITAL_PORT_SWITCH_TO_D2()                     (g_ucDigitalSwitch &= ~_BIT3)

#define GET_DIGITAL_PORT_SWITCH_TO_D3()                     ((g_ucDigitalSwitch & _BIT2) >> 2)
#define SET_DIGITAL_PORT_SWITCH_TO_D3()                     (g_ucDigitalSwitch |= _BIT2)
#define CLR_DIGITAL_PORT_SWITCH_TO_D3()                     (g_ucDigitalSwitch &= ~_BIT2)

#define GET_DIGITAL_PORT_SWITCH_TO_D4()                     ((g_ucDigitalSwitch & _BIT1) >> 1)
#define SET_DIGITAL_PORT_SWITCH_TO_D4()                     (g_ucDigitalSwitch |= _BIT1)
#define CLR_DIGITAL_PORT_SWITCH_TO_D4()                     (g_ucDigitalSwitch &= ~_BIT1)

#define GET_DIGITAL_PORT_SWITCH_TO_D5()                     ((g_ucDigitalSwitch & _BIT0) >> 0)
#define SET_DIGITAL_PORT_SWITCH_TO_D5()                     (g_ucDigitalSwitch |= _BIT0)
#define CLR_DIGITAL_PORT_SWITCH_TO_D5()                     (g_ucDigitalSwitch &= ~_BIT0)

#define GET_DIGITAL_PORT_SWITCH_TO_D6()                     ((g_ucDigitalSwitch & _BIT6) >> 6)
#define SET_DIGITAL_PORT_SWITCH_TO_D6()                     (g_ucDigitalSwitch |= _BIT6)
#define CLR_DIGITAL_PORT_SWITCH_TO_D6()                     (g_ucDigitalSwitch &= ~_BIT6)

#define GET_DP_DC_OFF_HPD_HIGH()                            (g_bDpDCOffHPDHigh)
#define SET_DP_DC_OFF_HPD_HIGH()                            (g_bDpDCOffHPDHigh = _TRUE)
#define CLR_DP_DC_OFF_HPD_HIGH()                            (g_bDpDCOffHPDHigh = _FALSE)

#define GET_PS_WAKEUP_HPD_TOGGLE()                          (g_bPsWakeupHpd)
#define SET_PS_WAKEUP_HPD_TOGGLE()                          (g_bPsWakeupHpd = _TRUE)
#define CLR_PS_WAKEUP_HPD_TOGGLE()                          (g_bPsWakeupHpd = _FALSE)

#define GET_HDMI_HOTPLUG_TOGGLE()                           ((g_ucHDMIHotPlug & _BIT7) >> 7)
#define SET_HDMI_HOTPLUG_TOGGLE()                           (g_ucHDMIHotPlug |= _BIT7)
#define CLR_HDMI_HOTPLUG_TOGGLE()                           (g_ucHDMIHotPlug &= ~_BIT7)

#define GET_HDMI_HOTPLUG_TIME()                             ((WORD)(g_ucHDMIHotPlug & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) * 100)
#define SET_HDMI_HOTPLUG_TIME(x)                            (g_ucHDMIHotPlug = (g_ucHDMIHotPlug & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | (x))

#define GET_DP_AUX_DIFF_MODE()                              (g_stDpAuxSetting.b1DpAuxMode)
#define SET_DP_AUX_DIFF_MODE()                              (g_stDpAuxSetting.b1DpAuxMode = _TRUE)
#define CLR_DP_AUX_DIFF_MODE()                              (g_stDpAuxSetting.b1DpAuxMode = _FALSE)

#define GET_DP_AUX_ADJR_SETTING()                           (g_stDpAuxSetting.b4DpAuxAdjrSet)
#define SET_DP_AUX_ADJR_SETTING(x)                          (g_stDpAuxSetting.b4DpAuxAdjrSet = (x))

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
#define GET_TMDS_RX0_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx0Z0Toggle)
#define SET_TMDS_RX0_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx0Z0Toggle = _TRUE)
#define CLR_TMDS_RX0_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx0Z0Toggle = _FALSE)

#define GET_TMDS_RX0_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx0GlobalZ0Toggle)
#define SET_TMDS_RX0_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx0GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX0_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx0GlobalZ0Toggle = _FALSE)

#define GET_TMDS_RX1_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx1Z0Toggle)
#define SET_TMDS_RX1_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx1Z0Toggle = _TRUE)
#define CLR_TMDS_RX1_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx1Z0Toggle = _FALSE)

#define GET_TMDS_RX1_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx1GlobalZ0Toggle)
#define SET_TMDS_RX1_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx1GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX1_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx1GlobalZ0Toggle = _FALSE)

#define GET_TMDS_RX2_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx2Z0Toggle)
#define SET_TMDS_RX2_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx2Z0Toggle = _TRUE)
#define CLR_TMDS_RX2_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx2Z0Toggle = _FALSE)

#define GET_TMDS_RX2_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx2GlobalZ0Toggle)
#define SET_TMDS_RX2_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx2GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX2_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx2GlobalZ0Toggle = _FALSE)

#define GET_TMDS_RX3_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx3Z0Toggle)
#define SET_TMDS_RX3_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx3Z0Toggle = _TRUE)
#define CLR_TMDS_RX3_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx3Z0Toggle = _FALSE)

#define GET_TMDS_RX3_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx3GlobalZ0Toggle)
#define SET_TMDS_RX3_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx3GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX3_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx3GlobalZ0Toggle = _FALSE)

#define GET_TMDS_RX4_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx4Z0Toggle)
#define SET_TMDS_RX4_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx4Z0Toggle = _TRUE)
#define CLR_TMDS_RX4_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx4Z0Toggle = _FALSE)

#define GET_TMDS_RX4_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx4GlobalZ0Toggle)
#define SET_TMDS_RX4_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx4GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX4_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx4GlobalZ0Toggle = _FALSE)

#define GET_TMDS_RX5_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx5Z0Toggle)
#define SET_TMDS_RX5_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx5Z0Toggle = _TRUE)
#define CLR_TMDS_RX5_TOGGLE_Z0()                            (g_stTmdsToggleZ0Flag.b1TMDSRx5Z0Toggle = _FALSE)

#define GET_TMDS_RX5_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx5GlobalZ0Toggle)
#define SET_TMDS_RX5_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx5GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_RX5_TOGGLE_Z0_EVENT()                      (g_stTmdsToggleZ0Flag.b1TMDSRx5GlobalZ0Toggle = _FALSE)
#endif
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#define GET_D0_HDMI_5V_STATUS()                             ((bit)(g_stDpHdmiCompatibleInfo.b1D0Hdmi5VStatus))
#define SET_D0_HDMI_5V_STATUS()                             (g_stDpHdmiCompatibleInfo.b1D0Hdmi5VStatus = 1)
#define CLR_D0_HDMI_5V_STATUS()                             (g_stDpHdmiCompatibleInfo.b1D0Hdmi5VStatus = 0)

#define GET_D1_HDMI_5V_STATUS()                             ((bit)(g_stDpHdmiCompatibleInfo.b1D1Hdmi5VStatus))
#define SET_D1_HDMI_5V_STATUS()                             (g_stDpHdmiCompatibleInfo.b1D1Hdmi5VStatus = 1)
#define CLR_D1_HDMI_5V_STATUS()                             (g_stDpHdmiCompatibleInfo.b1D1Hdmi5VStatus = 0)

#define GET_D2_HDMI_5V_STATUS()                             ((bit)(g_stDpHdmiCompatibleInfo.b1D2Hdmi5VStatus))
#define SET_D2_HDMI_5V_STATUS()                             (g_stDpHdmiCompatibleInfo.b1D2Hdmi5VStatus = 1)
#define CLR_D2_HDMI_5V_STATUS()                             (g_stDpHdmiCompatibleInfo.b1D2Hdmi5VStatus = 0)

#define GET_D3_HDMI_5V_STATUS()                             ((bit)(g_stDpHdmiCompatibleInfo.b1D3Hdmi5VStatus))
#define SET_D3_HDMI_5V_STATUS()                             (g_stDpHdmiCompatibleInfo.b1D3Hdmi5VStatus = 1)
#define CLR_D3_HDMI_5V_STATUS()                             (g_stDpHdmiCompatibleInfo.b1D3Hdmi5VStatus = 0)

#define GET_D0_HDMI_PS_WAKEUP()                             ((bit)(g_stDpHdmiCompatibleInfo.b1D0HdmiPSWakeUp))
#define SET_D0_HDMI_PS_WAKEUP()                             (g_stDpHdmiCompatibleInfo.b1D0HdmiPSWakeUp = 1)
#define CLR_D0_HDMI_PS_WAKEUP()                             (g_stDpHdmiCompatibleInfo.b1D0HdmiPSWakeUp = 0)

#define GET_D1_HDMI_PS_WAKEUP()                             ((bit)(g_stDpHdmiCompatibleInfo.b1D1HdmiPSWakeUp))
#define SET_D1_HDMI_PS_WAKEUP()                             (g_stDpHdmiCompatibleInfo.b1D1HdmiPSWakeUp = 1)
#define CLR_D1_HDMI_PS_WAKEUP()                             (g_stDpHdmiCompatibleInfo.b1D1HdmiPSWakeUp = 0)

#define GET_D2_HDMI_PS_WAKEUP()                             ((bit)(g_stDpHdmiCompatibleInfo.b1D2HdmiPSWakeUp))
#define SET_D2_HDMI_PS_WAKEUP()                             (g_stDpHdmiCompatibleInfo.b1D2HdmiPSWakeUp = 1)
#define CLR_D2_HDMI_PS_WAKEUP()                             (g_stDpHdmiCompatibleInfo.b1D2HdmiPSWakeUp = 0)

#define GET_D3_HDMI_PS_WAKEUP()                             ((bit)(g_stDpHdmiCompatibleInfo.b1D3HdmiPSWakeUp))
#define SET_D3_HDMI_PS_WAKEUP()                             (g_stDpHdmiCompatibleInfo.b1D3HdmiPSWakeUp = 1)
#define CLR_D3_HDMI_PS_WAKEUP()                             (g_stDpHdmiCompatibleInfo.b1D3HdmiPSWakeUp = 0)
#endif

#endif

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of Dp Rx Capability Switch
//--------------------------------------------------
#define GET_DP_RX_D0_PORT_TARGET_VERSION()                  (g_stDpCapSwitch.ucD0Version)
#define SET_DP_RX_D0_PORT_TARGET_VERSION(x)                 (g_stDpCapSwitch.ucD0Version = (x))

#define GET_DP_RX_D1_PORT_TARGET_VERSION()                  (g_stDpCapSwitch.ucD1Version)
#define SET_DP_RX_D1_PORT_TARGET_VERSION(x)                 (g_stDpCapSwitch.ucD1Version = (x))

#define GET_DP_RX_D6_PORT_TARGET_VERSION()                  (g_stDpCapSwitch.ucD6Version)
#define SET_DP_RX_D6_PORT_TARGET_VERSION(x)                 (g_stDpCapSwitch.ucD6Version = (x))

#define GET_DP_RX_D0_PORT_TARGET_LANE_COUNT()               (g_stDpCapSwitch.ucD0LaneCount)
#define SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(x)              (g_stDpCapSwitch.ucD0LaneCount = (x))

#define GET_DP_RX_D1_PORT_TARGET_LANE_COUNT()               (g_stDpCapSwitch.ucD1LaneCount)
#define SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(x)              (g_stDpCapSwitch.ucD1LaneCount = (x))

#define GET_DP_RX_D6_PORT_TARGET_LANE_COUNT()               (g_stDpCapSwitch.ucD6LaneCount)
#define SET_DP_RX_D6_PORT_TARGET_LANE_COUNT(x)              (g_stDpCapSwitch.ucD6LaneCount = (x))

#define GET_DP_RX_D0_EDID_SWITCH()                          (g_stDpCapSwitch.b1D0Edid)
#define SET_DP_RX_D0_EDID_SWITCH()                          (g_stDpCapSwitch.b1D0Edid = _TRUE)
#define CLR_DP_RX_D0_EDID_SWITCH()                          (g_stDpCapSwitch.b1D0Edid = _FALSE)

#define GET_DP_RX_D1_EDID_SWITCH()                          (g_stDpCapSwitch.b1D1Edid)
#define SET_DP_RX_D1_EDID_SWITCH()                          (g_stDpCapSwitch.b1D1Edid = _TRUE)
#define CLR_DP_RX_D1_EDID_SWITCH()                          (g_stDpCapSwitch.b1D1Edid = _FALSE)

#define GET_DP_RX_D6_EDID_SWITCH()                          (g_stDpCapSwitch.b1D6Edid)
#define SET_DP_RX_D6_EDID_SWITCH()                          (g_stDpCapSwitch.b1D6Edid = _TRUE)
#define CLR_DP_RX_D6_EDID_SWITCH()                          (g_stDpCapSwitch.b1D6Edid = _FALSE)

#define GET_DP_RX_TARGET_MST_PORT()                         (g_stDpCapSwitch.b2MSTPort)
#define SET_DP_RX_TARGET_MST_PORT(x)                        (g_stDpCapSwitch.b2MSTPort = (x))

#define GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD()              (g_bDpMstDCOffHPDToggleHoldFlag)
#define SET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD()              (g_bDpMstDCOffHPDToggleHoldFlag = _TRUE)
#define CLR_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD()              (g_bDpMstDCOffHPDToggleHoldFlag = _FALSE)

#define GET_DP_DC_OFF_HPD_TOGGLE_FLAG()                     (g_bDpDCOffHPDToggleFlag)
#define SET_DP_DC_OFF_HPD_TOGGLE_FLAG()                     (g_bDpDCOffHPDToggleFlag = 1)
#define CLR_DP_DC_OFF_HPD_TOGGLE_FLAG()                     (g_bDpDCOffHPDToggleFlag = 0)

#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE != _DIGITAL_PORT_COMBO_PHY_ALL)
#define _DP_VCO_TARGET_COUNT_1000_RBR_SAVED                 (g_usSyncDpVcoTargetCount1000RBR)
#define _DP_VCO_TARGET_COUNT_1000_HBR_SAVED                 (g_usSyncDpVcoTargetCount1000HBR)
#define _DP_VCO_TARGET_COUNT_1000_HBR2_SAVED                (g_usSyncDpVcoTargetCount1000HBR2)

#define _DP_VCO_TARGET_COUNT_2000_RBR_SAVED                 (g_usSyncDpVcoTargetCount2000RBR)
#define _DP_VCO_TARGET_COUNT_2000_HBR_SAVED                 (g_usSyncDpVcoTargetCount2000HBR)
#define _DP_VCO_TARGET_COUNT_2000_HBR2_SAVED                (g_usSyncDpVcoTargetCount2000HBR2)

#define _DP_COUNT_SST_UPPER_BOUND_2000_RBR_SAVED            (g_usSyncDpCountSSTUpperBound2000RBR)
#define _DP_COUNT_SST_UPPER_BOUND_2000_HBR_SAVED            (g_usSyncDpCountSSTUpperBound2000HBR)
#define _DP_COUNT_SST_UPPER_BOUND_2000_HBR2_SAVED           (g_usSyncDpCountSSTUpperBound2000HBR2)

#define _DP_COUNT_SST_LOWER_BOUND_2000_RBR_SAVED            (g_usSyncDpCountSSTLowerBound2000RBR)
#define _DP_COUNT_SST_LOWER_BOUND_2000_HBR_SAVED            (g_usSyncDpCountSSTLowerBound2000HBR)
#define _DP_COUNT_SST_LOWER_BOUND_2000_HBR2_SAVED           (g_usSyncDpCountSSTLowerBound2000HBR2)

#define _DP_COUNT_MST_UPPER_BOUND_2000_RBR_SAVED            (g_usSyncDpCountMSTUpperBound2000RBR)
#define _DP_COUNT_MST_UPPER_BOUND_2000_HBR_SAVED            (g_usSyncDpCountMSTUpperBound2000HBR)
#define _DP_COUNT_MST_UPPER_BOUND_2000_HBR2_SAVED           (g_usSyncDpCountMSTUpperBound2000HBR2)

#define _DP_COUNT_MST_LOWER_BOUND_2000_RBR_SAVED            (g_usSyncDpCountMSTLowerBound2000RBR)
#define _DP_COUNT_MST_LOWER_BOUND_2000_HBR_SAVED            (g_usSyncDpCountMSTLowerBound2000HBR)
#define _DP_COUNT_MST_LOWER_BOUND_2000_HBR2_SAVED           (g_usSyncDpCountMSTLowerBound2000HBR2)

#define _DP_COUNT_D10P2_UPPER_BOUND_1000_RBR_SAVED          (g_usSyncDpCountD10P2UpperBound1000RBR)
#define _DP_COUNT_D10P2_UPPER_BOUND_1000_HBR_SAVED          (g_usSyncDpCountD10P2UpperBound1000HBR)
#define _DP_COUNT_D10P2_UPPER_BOUND_1000_HBR2_SAVED         (g_usSyncDpCountD10P2UpperBound1000HBR2)

#define _DP_COUNT_D10P2_LOWER_BOUND_1000_RBR_SAVED          (g_usSyncDpCountD10P2LowerBound1000RBR)
#define _DP_COUNT_D10P2_LOWER_BOUND_1000_HBR_SAVED          (g_usSyncDpCountD10P2LowerBound1000HBR)
#define _DP_COUNT_D10P2_LOWER_BOUND_1000_HBR2_SAVED         (g_usSyncDpCountD10P2LowerBound1000HBR2)
#else
#define _DP_VCO_TARGET_COUNT_1000_RBR_SAVED                 (_DP_VCO_TARGET_COUNT_1000_RBR)
#define _DP_VCO_TARGET_COUNT_1000_HBR_SAVED                 (_DP_VCO_TARGET_COUNT_1000_HBR)
#define _DP_VCO_TARGET_COUNT_1000_HBR2_SAVED                (_DP_VCO_TARGET_COUNT_1000_HBR2)

#define _DP_VCO_TARGET_COUNT_2000_RBR_SAVED                 (_DP_VCO_TARGET_COUNT_2000_RBR)
#define _DP_VCO_TARGET_COUNT_2000_HBR_SAVED                 (_DP_VCO_TARGET_COUNT_2000_HBR)
#define _DP_VCO_TARGET_COUNT_2000_HBR2_SAVED                (_DP_VCO_TARGET_COUNT_2000_HBR2)

#define _DP_COUNT_SST_UPPER_BOUND_2000_RBR_SAVED            (_DP_RAWDATA_COUNT_SST_UPPER_BOUND_2000_RBR)
#define _DP_COUNT_SST_UPPER_BOUND_2000_HBR_SAVED            (_DP_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR)
#define _DP_COUNT_SST_UPPER_BOUND_2000_HBR2_SAVED           (_DP_RAWDATA_COUNT_SST_UPPER_BOUND_2000_HBR2)

#define _DP_COUNT_SST_LOWER_BOUND_2000_RBR_SAVED            (_DP_RAWDATA_COUNT_SST_LOWER_BOUND_2000_RBR)
#define _DP_COUNT_SST_LOWER_BOUND_2000_HBR_SAVED            (_DP_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR)
#define _DP_COUNT_SST_LOWER_BOUND_2000_HBR2_SAVED           (_DP_RAWDATA_COUNT_SST_LOWER_BOUND_2000_HBR2)

#define _DP_COUNT_MST_UPPER_BOUND_2000_RBR_SAVED            (_DP_RAWDATA_COUNT_MST_UPPER_BOUND_2000_RBR)
#define _DP_COUNT_MST_UPPER_BOUND_2000_HBR_SAVED            (_DP_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR)
#define _DP_COUNT_MST_UPPER_BOUND_2000_HBR2_SAVED           (_DP_RAWDATA_COUNT_MST_UPPER_BOUND_2000_HBR2)

#define _DP_COUNT_MST_LOWER_BOUND_2000_RBR_SAVED            (_DP_RAWDATA_COUNT_MST_LOWER_BOUND_2000_RBR)
#define _DP_COUNT_MST_LOWER_BOUND_2000_HBR_SAVED            (_DP_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR)
#define _DP_COUNT_MST_LOWER_BOUND_2000_HBR2_SAVED           (_DP_RAWDATA_COUNT_MST_LOWER_BOUND_2000_HBR2)

#define _DP_COUNT_D10P2_UPPER_BOUND_1000_RBR_SAVED          (_DP_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_RBR)
#define _DP_COUNT_D10P2_UPPER_BOUND_1000_HBR_SAVED          (_DP_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR)
#define _DP_COUNT_D10P2_UPPER_BOUND_1000_HBR2_SAVED         (_DP_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR)

#define _DP_COUNT_D10P2_LOWER_BOUND_1000_RBR_SAVED          (_DP_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_RBR)
#define _DP_COUNT_D10P2_LOWER_BOUND_1000_HBR_SAVED          (_DP_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR)
#define _DP_COUNT_D10P2_LOWER_BOUND_1000_HBR2_SAVED         (_DP_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR2)
#endif


#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
#if(_D0_DP_EXIST == _ON)
#define GET_DP_RX0_TARGET_HDCP_CAPABILITY()                 (g_stDpCapSwitch.b1Rx0HdcpCap)
#define SET_DP_RX0_TARGET_HDCP_CAPABILITY(x)                (g_stDpCapSwitch.b1Rx0HdcpCap = (x))
#endif

#if(_D1_DP_EXIST == _ON)
#define GET_DP_RX1_TARGET_HDCP_CAPABILITY()                 (g_stDpCapSwitch.b1Rx1HdcpCap)
#define SET_DP_RX1_TARGET_HDCP_CAPABILITY(x)                (g_stDpCapSwitch.b1Rx1HdcpCap = (x))
#endif
#endif

#define GET_DP_RX_CAPABILITY_SWITCHED()                     (g_stDpCapSwitch.b1MsgSwitched)
#define SET_DP_RX_CAPABILITY_SWITCHED()                     (g_stDpCapSwitch.b1MsgSwitched = _TRUE)
#define CLR_DP_RX_CAPABILITY_SWITCHED()                     (g_stDpCapSwitch.b1MsgSwitched = _FALSE)

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDCP handshake without HDCP capability event occured
//--------------------------------------------------
#if(_D0_DP_EXIST == _ON)
#define GET_DP_RX0_HDCP_HANDSHAKE_WO_CAP()                  ((bit) g_bDpRx0HdcpHandshakeWOCap)
#define SET_DP_RX0_HDCP_HANDSHAKE_WO_CAP()                  (g_bDpRx0HdcpHandshakeWOCap = _TRUE)
#define CLR_DP_RX0_HDCP_HANDSHAKE_WO_CAP()                  (g_bDpRx0HdcpHandshakeWOCap = _FALSE)
#endif

#if(_D1_DP_EXIST == _ON)
#define GET_DP_RX1_HDCP_HANDSHAKE_WO_CAP()                  ((bit) g_bDpRx1HdcpHandshakeWOCap)
#define SET_DP_RX1_HDCP_HANDSHAKE_WO_CAP()                  (g_bDpRx1HdcpHandshakeWOCap = _TRUE)
#define CLR_DP_RX1_HDCP_HANDSHAKE_WO_CAP()                  (g_bDpRx1HdcpHandshakeWOCap = _FALSE)
#endif
#endif

//--------------------------------------------------
// Definitions of DP IRQ Time Setting
//--------------------------------------------------
#define GET_DP_IRQ_TIME_10US()                              (g_ucDpIrqTime_10us)
#define SET_DP_IRQ_TIME_10US(x)                             (g_ucDpIrqTime_10us = (x))

//--------------------------------------------------
// Macro of Hot Plug Event Assert Type
//--------------------------------------------------
#if(_D0_DP_EXIST == _ON)
#define GET_DP_RX0_HOTPLUG_ASSERT_TYPE()                    (g_stHpdType.enumD0HpdAssertType)
#define SET_DP_RX0_HOTPLUG_ASSERT_TYPE(x)                   {\
                                                                DebugMessageRx0("SET_DP_RX0_HOTPLUG_ASSERT_TYPE", (x));\
                                                                (g_stHpdType.enumD0HpdAssertType = (x));\
                                                            }
#define CLR_DP_RX0_HOTPLUG_ASSERT_TYPE()                    (g_stHpdType.enumD0HpdAssertType = _DP_HPD_NONE)

#define GET_DP_RX0_HOTPLUG_ASSERT_TYPE_EXINT()              (g_stHpdType.enumD0HpdAssertType)
#define SET_DP_RX0_HOTPLUG_ASSERT_TYPE_EXINT(x)             (g_stHpdType.enumD0HpdAssertType = (x))

#define GET_DP_RX0_HDCP_CHECK_ENABLE()                      (g_bDpRx0HdcpCheckEnable)
#define SET_DP_RX0_HDCP_CHECK_ENABLE()                      (g_bDpRx0HdcpCheckEnable = _TRUE)
#define CLR_DP_RX0_HDCP_CHECK_ENABLE()                      (g_bDpRx0HdcpCheckEnable = _FALSE)
#endif

#if(_D1_DP_EXIST == _ON)
#define GET_DP_RX1_HOTPLUG_ASSERT_TYPE()                    (g_stHpdType.enumD1HpdAssertType)
#define SET_DP_RX1_HOTPLUG_ASSERT_TYPE(x)                   {\
                                                                DebugMessageRx1("SET_DP_RX1_HOTPLUG_ASSERT_TYPE", (x));\
                                                                (g_stHpdType.enumD1HpdAssertType = (x));\
                                                            }
#define CLR_DP_RX1_HOTPLUG_ASSERT_TYPE()                    (g_stHpdType.enumD1HpdAssertType = _DP_HPD_NONE)

#define GET_DP_RX1_HOTPLUG_ASSERT_TYPE_EXINT()              (g_stHpdType.enumD1HpdAssertType)
#define SET_DP_RX1_HOTPLUG_ASSERT_TYPE_EXINT(x)             (g_stHpdType.enumD1HpdAssertType = (x))

#define GET_DP_RX1_HDCP_CHECK_ENABLE()                      (g_bDpRx1HdcpCheckEnable)
#define SET_DP_RX1_HDCP_CHECK_ENABLE()                      (g_bDpRx1HdcpCheckEnable = _TRUE)
#define CLR_DP_RX1_HDCP_CHECK_ENABLE()                      (g_bDpRx1HdcpCheckEnable = _FALSE)
#endif

#if(_D2_DP_EXIST == _ON)
#define GET_DP_RX2_HOTPLUG_ASSERT_TYPE()                    (g_stHpdType.enumD2HpdAssertType)
#define SET_DP_RX2_HOTPLUG_ASSERT_TYPE(x)                   {\
                                                                DebugMessageRx2("SET_DP_RX2_HOTPLUG_ASSERT_TYPE", (x));\
                                                                (g_stHpdType.enumD2HpdAssertType = (x));\
                                                            }
#define CLR_DP_RX2_HOTPLUG_ASSERT_TYPE()                    (g_stHpdType.enumD2HpdAssertType = _DP_HPD_NONE)
#endif

//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX0_BACKUP_PD_LINK_STATUS_FLG()              (g_bDpMSTRx0BackupLinkStatusFlg_INT)
#define SET_DP_RX0_BACKUP_PD_LINK_STATUS_FLG()              (g_bDpMSTRx0BackupLinkStatusFlg_INT = _TRUE)
#define CLR_DP_RX0_BACKUP_PD_LINK_STATUS_FLG()              (g_bDpMSTRx0BackupLinkStatusFlg_INT = _FALSE)

#define GET_DP_RX1_BACKUP_PD_LINK_STATUS_FLG()              (g_bDpMSTRx1BackupLinkStatusFlg_INT)
#define SET_DP_RX1_BACKUP_PD_LINK_STATUS_FLG()              (g_bDpMSTRx1BackupLinkStatusFlg_INT = _TRUE)
#define CLR_DP_RX1_BACKUP_PD_LINK_STATUS_FLG()              (g_bDpMSTRx1BackupLinkStatusFlg_INT = _FALSE)

//--------------------------------------------------
// Definitions of DP Marginal Link
//--------------------------------------------------
#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
#define GET_DP_RX_D0_MARGIN_LINK_HBR2()                     (g_stDpMarginLink.b1D0MarginLinkHBR2)
#define SET_DP_RX_D0_MARGIN_LINK_HBR2()                     (g_stDpMarginLink.b1D0MarginLinkHBR2 = _TRUE)
#define CLR_DP_RX_D0_MARGIN_LINK_HBR2()                     (g_stDpMarginLink.b1D0MarginLinkHBR2 = _FALSE)
#endif

#define GET_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane0MarginLinkHBRRBR)
#define SET_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane0MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane0MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D0_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane1MarginLinkHBRRBR)
#define SET_DP_RX_D0_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane1MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D0_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane1MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D0_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane2MarginLinkHBRRBR)
#define SET_DP_RX_D0_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane2MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D0_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane2MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D0_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane3MarginLinkHBRRBR)
#define SET_DP_RX_D0_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane3MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D0_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane3MarginLinkHBRRBR = _FALSE)

//--------------------------------------------------
// Definitions of DP Illegal Idle Pattern Check
//--------------------------------------------------
#define GET_DP_ILLEGAL_IDLE_PATTERN_CHECK()                 (g_bDpIllegalIdlePatternCheck)
#define SET_DP_ILLEGAL_IDLE_PATTERN_CHECK()                 (g_bDpIllegalIdlePatternCheck = _TRUE)
#define CLR_DP_ILLEGAL_IDLE_PATTERN_CHECK()                 (g_bDpIllegalIdlePatternCheck = _FALSE)

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
#define GET_DP_RX_D1_MARGIN_LINK_HBR2()                     (g_stDpMarginLink.b1D1MarginLinkHBR2)
#define SET_DP_RX_D1_MARGIN_LINK_HBR2()                     (g_stDpMarginLink.b1D1MarginLinkHBR2 = _TRUE)
#define CLR_DP_RX_D1_MARGIN_LINK_HBR2()                     (g_stDpMarginLink.b1D1MarginLinkHBR2 = _FALSE)
#endif

#define GET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane0MarginLinkHBRRBR)
#define SET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane0MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane0MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane1MarginLinkHBRRBR)
#define SET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane1MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane1MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane2MarginLinkHBRRBR)
#define SET_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane2MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane2MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane3MarginLinkHBRRBR)
#define SET_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane3MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane3MarginLinkHBRRBR = _FALSE)

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
#define GET_DP_RX_D6_MARGIN_LINK_HBR2()                     (g_stDpMarginLink.b1D6MarginLinkHBR2)
#define SET_DP_RX_D6_MARGIN_LINK_HBR2()                     (g_stDpMarginLink.b1D6MarginLinkHBR2 = _TRUE)
#define CLR_DP_RX_D6_MARGIN_LINK_HBR2()                     (g_stDpMarginLink.b1D6MarginLinkHBR2 = _FALSE)
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
#define GET_DP_RX_HDCP_UPSTREAM_PORT()                      (g_stDpTxStatus.b2HdcpUpstreamPort)
#define SET_DP_RX_HDCP_UPSTREAM_PORT(x)                     (g_stDpTxStatus.b2HdcpUpstreamPort = (x))

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#define GET_DP_RX_HDCP2_UPSTREAM_PORT()                     (g_stDpTxStatus.b2Hdcp2UpstreamPort)
#define SET_DP_RX_HDCP2_UPSTREAM_PORT(x)                    (g_stDpTxStatus.b2Hdcp2UpstreamPort = (x))
#endif
#endif

#if(_FREESYNC_SUPPORT == _ON)
#if((_DP_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
#define GET_FREESYNC_ENABLED()                              ((bit)(GET_DP_FREESYNC_ENABLED() | GET_HDMI_FREESYNC_ENABLED()))
#define CLR_FREESYNC_ENABLED()                              {\
                                                                CLR_DP_FREESYNC_ENABLED();\
                                                                CLR_HDMI_FREESYNC_ENABLED();\
                                                            }
#elif(_DP_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_ENABLED()                              (GET_DP_FREESYNC_ENABLED())
#define CLR_FREESYNC_ENABLED()                              {\
                                                                CLR_DP_FREESYNC_ENABLED();\
                                                            }
#else
#define GET_FREESYNC_ENABLED()                              (GET_HDMI_FREESYNC_ENABLED())
#define CLR_FREESYNC_ENABLED()                              {\
                                                                CLR_HDMI_FREESYNC_ENABLED();\
                                                            }
#endif

#define GET_FREESYNC_SPD_INFO_FRAME_RECEIVED()              (g_bFREESYNCSPDInfoReceive)
#define SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(x)             (g_bFREESYNCSPDInfoReceive = (x))

#define GET_FREESYNC_IVF_INFO()                             (g_bFREESYNCGetIVFInfo)
#define SET_FREESYNC_IVF_INFO(x)                            (g_bFREESYNCGetIVFInfo = (x))

#define GET_FREESYNC_VFREQ_MAX()                            (g_usFREESYNCVFreq_max)
#define SET_FREESYNC_VFREQ_MAX(x)                           (g_usFREESYNCVFreq_max = (x))

#define GET_FREESYNC_VFREQ_MIN()                            (g_usFREESYNCVFreq_min)
#define SET_FREESYNC_VFREQ_MIN(x)                           (g_usFREESYNCVFreq_min = (x))

#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_DP_FREESYNC_ENABLED()                           (g_stDpFREESYNCInfo.b1DPFREESYNCEnable)
#define SET_DP_FREESYNC_ENABLED()                           (g_stDpFREESYNCInfo.b1DPFREESYNCEnable = _ENABLE)
#define CLR_DP_FREESYNC_ENABLED()                           (g_stDpFREESYNCInfo.b1DPFREESYNCEnable = _DISABLE)

#define GET_DP_RX0_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX0FREESYNCCapabilitySwitch)
#define SET_DP_RX0_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX0FREESYNCCapabilitySwitch = _TRUE)
#define CLR_DP_RX0_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX0FREESYNCCapabilitySwitch = _FALSE)

#define GET_DP_RX1_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX1FREESYNCCapabilitySwitch)
#define SET_DP_RX1_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX1FREESYNCCapabilitySwitch = _TRUE)
#define CLR_DP_RX1_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX1FREESYNCCapabilitySwitch = _FALSE)

#define GET_DP_RX2_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX2FREESYNCCapabilitySwitch)
#define SET_DP_RX2_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX2FREESYNCCapabilitySwitch = _TRUE)
#define CLR_DP_RX2_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX2FREESYNCCapabilitySwitch = _FALSE)

#define GET_DP_RX6_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX6FREESYNCCapabilitySwitch)
#define SET_DP_RX6_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX6FREESYNCCapabilitySwitch = _TRUE)
#define CLR_DP_RX6_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX6FREESYNCCapabilitySwitch = _FALSE)

#define GET_DP_RX0_FREESYNC_SUPPORT()                       (g_stDpFREESYNCInfo.enumDPRX0FREESYNCSupport)
#define SET_DP_RX0_FREESYNC_SUPPORT(x)                      (g_stDpFREESYNCInfo.enumDPRX0FREESYNCSupport = (x))

#define GET_DP_RX1_FREESYNC_SUPPORT()                       (g_stDpFREESYNCInfo.enumDPRX1FREESYNCSupport)
#define SET_DP_RX1_FREESYNC_SUPPORT(x)                      (g_stDpFREESYNCInfo.enumDPRX1FREESYNCSupport = (x))

#define GET_DP_RX2_FREESYNC_SUPPORT()                       (g_stDpFREESYNCInfo.enumDPRX2FREESYNCSupport)
#define SET_DP_RX2_FREESYNC_SUPPORT(x)                      (g_stDpFREESYNCInfo.enumDPRX2FREESYNCSupport = (x))

#define GET_DP_RX6_FREESYNC_SUPPORT()                       (g_stDpFREESYNCInfo.enumDPRX6FREESYNCSupport)
#define SET_DP_RX6_FREESYNC_SUPPORT(x)                      (g_stDpFREESYNCInfo.enumDPRX6FREESYNCSupport = (x))

#define GET_DP_RX0_SPD_INFO_FRAME_RECEIVED()                (g_stDpFREESYNCInfo.b1DPRX0SPDInfoFrameReceived)
#define SET_DP_RX0_SPD_INFO_FRAME_RECEIVED()                (g_stDpFREESYNCInfo.b1DPRX0SPDInfoFrameReceived = _TRUE)
#define CLR_DP_RX0_SPD_INFO_FRAME_RECEIVED()                (g_stDpFREESYNCInfo.b1DPRX0SPDInfoFrameReceived = _FALSE)

#define GET_DP_RX1_SPD_INFO_FRAME_RECEIVED()                (g_stDpFREESYNCInfo.b1DPRX1SPDInfoFrameReceived)
#define SET_DP_RX1_SPD_INFO_FRAME_RECEIVED()                (g_stDpFREESYNCInfo.b1DPRX1SPDInfoFrameReceived = _TRUE)
#define CLR_DP_RX1_SPD_INFO_FRAME_RECEIVED()                (g_stDpFREESYNCInfo.b1DPRX1SPDInfoFrameReceived = _FALSE)

#define GET_DP_RX0_HTOTAL()                                 (g_stDpFREESYNCInfo.usDPRX0FREESYNCMSAHtotal)
#define SET_DP_RX0_HTOTAL(x)                                (g_stDpFREESYNCInfo.usDPRX0FREESYNCMSAHtotal = (x))

#define GET_DP_RX1_HTOTAL()                                 (g_stDpFREESYNCInfo.usDPRX1FREESYNCMSAHtotal)
#define SET_DP_RX1_HTOTAL(x)                                (g_stDpFREESYNCInfo.usDPRX1FREESYNCMSAHtotal = (x))

#define GET_DP_RX0_HTOTAL_MARGIN()                          (g_stDpFREESYNCInfo.usDPRX0FREESYNCHtotalMargin)
#define SET_DP_RX0_HTOTAL_MARGIN(x)                         (g_stDpFREESYNCInfo.usDPRX0FREESYNCHtotalMargin = (x))

#define GET_DP_RX1_HTOTAL_MARGIN()                          (g_stDpFREESYNCInfo.usDPRX1FREESYNCHtotalMargin)
#define SET_DP_RX1_HTOTAL_MARGIN(x)                         (g_stDpFREESYNCInfo.usDPRX1FREESYNCHtotalMargin = (x))

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#define GET_DP_MST_FREESYNC_ENABLED()                       (g_stDpFREESYNCInfo.b1DPMSTFREESYNCEnable)
#define SET_DP_MST_FREESYNC_ENABLED()                       (g_stDpFREESYNCInfo.b1DPMSTFREESYNCEnable = _ENABLE)
#define CLR_DP_MST_FREESYNC_ENABLED()                       (g_stDpFREESYNCInfo.b1DPMSTFREESYNCEnable = _DISABLE)
#endif // End of #if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#define GET_HDMI_FREESYNC_ENABLED()                         (g_stHDMIFREESYNCInfo.b1HDMIFREESYNCEnable)
#define SET_HDMI_FREESYNC_ENABLED()                         (g_stHDMIFREESYNCInfo.b1HDMIFREESYNCEnable = _ENABLE)
#define CLR_HDMI_FREESYNC_ENABLED()                         (g_stHDMIFREESYNCInfo.b1HDMIFREESYNCEnable = _DISABLE)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#define GET_HDMI_FREESYNC_VCP()                             (g_ucHDMIFREESYNCVCPReceive)
#endif

#define GET_TMDS_RX0_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.enumHDMIRX0FREESYNCSupport)
#define SET_TMDS_RX0_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.enumHDMIRX0FREESYNCSupport = (x))

#define GET_TMDS_RX1_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.enumHDMIRX1FREESYNCSupport)
#define SET_TMDS_RX1_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.enumHDMIRX1FREESYNCSupport = (x))

#define GET_TMDS_RX2_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.enumHDMIRX2FREESYNCSupport)
#define SET_TMDS_RX2_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.enumHDMIRX2FREESYNCSupport = (x))

#define GET_TMDS_RX3_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.enumHDMIRX3FREESYNCSupport)
#define SET_TMDS_RX3_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.enumHDMIRX3FREESYNCSupport = (x))

#define GET_TMDS_RX4_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.enumHDMIRX4FREESYNCSupport)
#define SET_TMDS_RX4_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.enumHDMIRX4FREESYNCSupport = (x))

#define GET_TMDS_RX5_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.enumHDMIRX5FREESYNCSupport)
#define SET_TMDS_RX5_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.enumHDMIRX5FREESYNCSupport = (x))
#endif // End of #if(_HDMI_FREESYNC_SUPPORT == _ON)
#endif // End of #if(_FREESYNC_SUPPORT == _ON)

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
#define GET_TMDS_RX0_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX0SPDInfoFrameReceived)
#define SET_TMDS_RX0_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX0SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX0_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX0SPDInfoFrameReceived = _FALSE)

#define GET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX1SPDInfoFrameReceived)
#define SET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX1SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX1_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX1SPDInfoFrameReceived = _FALSE)

#define GET_TMDS_RX2_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX2SPDInfoFrameReceived)
#define SET_TMDS_RX2_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX2SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX2_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX2SPDInfoFrameReceived = _FALSE)

#define GET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX3SPDInfoFrameReceived)
#define SET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX3SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX3_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX3SPDInfoFrameReceived = _FALSE)

#define GET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX4SPDInfoFrameReceived)
#define SET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX4SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX4_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX4SPDInfoFrameReceived = _FALSE)

#define GET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX5SPDInfoFrameReceived)
#define SET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX5SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX5_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX5SPDInfoFrameReceived = _FALSE)
#endif // End of #if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define GET_TMDS_RX0_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[0])
#define SET_TMDS_RX0_AVI_PIXEL_REPETITION(x)                (g_pucTMDSRxAviInfo[0] = (x))
#define CLR_TMDS_RX0_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[0] = 0)

#define GET_TMDS_RX1_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[1])
#define SET_TMDS_RX1_AVI_PIXEL_REPETITION(x)                (g_pucTMDSRxAviInfo[1] = (x))
#define CLR_TMDS_RX1_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[1] = 0)

#define GET_TMDS_RX2_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[2])
#define SET_TMDS_RX2_AVI_PIXEL_REPETITION(x)                (g_pucTMDSRxAviInfo[2] = (x))
#define CLR_TMDS_RX2_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[2] = 0)

#define GET_TMDS_RX3_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[3])
#define SET_TMDS_RX3_AVI_PIXEL_REPETITION(x)                (g_pucTMDSRxAviInfo[3] = (x))
#define CLR_TMDS_RX3_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[3] = 0)

#define GET_TMDS_RX4_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[4])
#define SET_TMDS_RX4_AVI_PIXEL_REPETITION(x)                (g_pucTMDSRxAviInfo[4] = (x))
#define CLR_TMDS_RX4_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[4] = 0)

#define GET_TMDS_RX5_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[5])
#define SET_TMDS_RX5_AVI_PIXEL_REPETITION(x)                (g_pucTMDSRxAviInfo[5] = (x))
#define CLR_TMDS_RX5_AVI_PIXEL_REPETITION()                 (g_pucTMDSRxAviInfo[5] = 0)

//--------------------------------------------------
// Macro of DDCCI PS to Normal HPD Toggle
//--------------------------------------------------
#define GET_TMDS_RX0_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx0PsWakeupHpd)
#define SET_TMDS_RX0_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx0PsWakeupHpd = _TRUE)
#define CLR_TMDS_RX0_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx0PsWakeupHpd = _FALSE)

#define GET_TMDS_RX1_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx1PsWakeupHpd)
#define SET_TMDS_RX1_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx1PsWakeupHpd = _TRUE)
#define CLR_TMDS_RX1_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx1PsWakeupHpd = _FALSE)

#define GET_TMDS_RX2_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx2PsWakeupHpd)
#define SET_TMDS_RX2_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx2PsWakeupHpd = _TRUE)
#define CLR_TMDS_RX2_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx2PsWakeupHpd = _FALSE)

#define GET_TMDS_RX3_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx3PsWakeupHpd)
#define SET_TMDS_RX3_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx3PsWakeupHpd = _TRUE)
#define CLR_TMDS_RX3_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx3PsWakeupHpd = _FALSE)

#define GET_TMDS_RX4_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx4PsWakeupHpd)
#define SET_TMDS_RX4_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx4PsWakeupHpd = _TRUE)
#define CLR_TMDS_RX4_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx4PsWakeupHpd = _FALSE)

#define GET_TMDS_RX5_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx5PsWakeupHpd)
#define SET_TMDS_RX5_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx5PsWakeupHpd = _TRUE)
#define CLR_TMDS_RX5_PS_WAKEUP_HPD_TOGGLE()                 (g_stHdmiPsWakeupHPD.b1Rx5PsWakeupHpd = _FALSE)
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Digital color info change
//--------------------------------------------------
#define GET_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bDigitalColorInfoChangeReset)
#define SET_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bDigitalColorInfoChangeReset = _TRUE)
#define CLR_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bDigitalColorInfoChangeReset = _FALSE)

#if(((_D0_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF)) || ((_HDMI_SUPPORT == _ON) && (_TMDS_PAGE2_COMBO_EXIST == _ON)))
#define GET_TMDS_RX0_COLOR_SPACE_PREVALUE()                 (g_stTMDSRx0ColorInfo.ucDigitalColorSpacePreValue)
#define SET_TMDS_RX0_COLOR_SPACE_PREVALUE(X)                (g_stTMDSRx0ColorInfo.ucDigitalColorSpacePreValue = (X))

#define GET_TMDS_RX0_COLOR_DEPTH_PREVALUE()                 (g_stTMDSRx0ColorInfo.b3DigitalColorDepthPreValue)
#define SET_TMDS_RX0_COLOR_DEPTH_PREVALUE(X)                (g_stTMDSRx0ColorInfo.b3DigitalColorDepthPreValue = (X))

#define GET_TMDS_RX0_COLORIMETRY_PREVALUE()                 (g_stTMDSRx0ColorInfo.b4DigitalColorimetryPreValue)
#define SET_TMDS_RX0_COLORIMETRY_PREVALUE(X)                (g_stTMDSRx0ColorInfo.b4DigitalColorimetryPreValue = (X))

#define GET_TMDS_RX0_COLORIMETRY_EXT_PREVALUE()             (g_stTMDSRx0ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_TMDS_RX0_COLORIMETRY_EXT_PREVALUE(X)            (g_stTMDSRx0ColorInfo.b4DigitalColorimetryExtPreValue = (X))

#define GET_TMDS_RX0_QUANTIZATION_PREVALUE()                (g_stTMDSRx0ColorInfo.b2DigitalQuantizationPreValue)
#define SET_TMDS_RX0_QUANTIZATION_PREVALUE(X)               (g_stTMDSRx0ColorInfo.b2DigitalQuantizationPreValue = (X))

#define GET_TMDS_RX0_COLORIMETRY_CHANGED()                  (g_stTMDSRx0ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_TMDS_RX0_COLORIMETRY_CHANGED()                  (g_stTMDSRx0ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_TMDS_RX0_COLORIMETRY_CHANGED()                  (g_stTMDSRx0ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_TMDS_RX0_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx0ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_TMDS_RX0_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx0ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_TMDS_RX0_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx0ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_TMDS_RX0_QUANTIZATION_CHANGED()                 (g_stTMDSRx0ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_TMDS_RX0_QUANTIZATION_CHANGED()                 (g_stTMDSRx0ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_TMDS_RX0_QUANTIZATION_CHANGED()                 (g_stTMDSRx0ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)
#endif

#if((_D1_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#define GET_TMDS_RX1_COLOR_SPACE_PREVALUE()                 (g_stTMDSRx1ColorInfo.ucDigitalColorSpacePreValue)
#define SET_TMDS_RX1_COLOR_SPACE_PREVALUE(X)                (g_stTMDSRx1ColorInfo.ucDigitalColorSpacePreValue = (X))

#define GET_TMDS_RX1_COLOR_DEPTH_PREVALUE()                 (g_stTMDSRx1ColorInfo.b3DigitalColorDepthPreValue)
#define SET_TMDS_RX1_COLOR_DEPTH_PREVALUE(X)                (g_stTMDSRx1ColorInfo.b3DigitalColorDepthPreValue = (X))

#define GET_TMDS_RX1_COLORIMETRY_PREVALUE()                 (g_stTMDSRx1ColorInfo.b4DigitalColorimetryPreValue)
#define SET_TMDS_RX1_COLORIMETRY_PREVALUE(X)                (g_stTMDSRx1ColorInfo.b4DigitalColorimetryPreValue = (X))

#define GET_TMDS_RX1_COLORIMETRY_EXT_PREVALUE()             (g_stTMDSRx1ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_TMDS_RX1_COLORIMETRY_EXT_PREVALUE(X)            (g_stTMDSRx1ColorInfo.b4DigitalColorimetryExtPreValue = (X))

#define GET_TMDS_RX1_QUANTIZATION_PREVALUE()                (g_stTMDSRx1ColorInfo.b2DigitalQuantizationPreValue)
#define SET_TMDS_RX1_QUANTIZATION_PREVALUE(X)               (g_stTMDSRx1ColorInfo.b2DigitalQuantizationPreValue = (X))

#define GET_TMDS_RX1_COLORIMETRY_CHANGED()                  (g_stTMDSRx1ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_TMDS_RX1_COLORIMETRY_CHANGED()                  (g_stTMDSRx1ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_TMDS_RX1_COLORIMETRY_CHANGED()                  (g_stTMDSRx1ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_TMDS_RX1_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx1ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_TMDS_RX1_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx1ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_TMDS_RX1_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx1ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_TMDS_RX1_QUANTIZATION_CHANGED()                 (g_stTMDSRx1ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_TMDS_RX1_QUANTIZATION_CHANGED()                 (g_stTMDSRx1ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_TMDS_RX1_QUANTIZATION_CHANGED()                 (g_stTMDSRx1ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)
#endif

#if((_D2_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#define GET_TMDS_RX2_COLOR_SPACE_PREVALUE()                 (g_stTMDSRx2ColorInfo.ucDigitalColorSpacePreValue)
#define SET_TMDS_RX2_COLOR_SPACE_PREVALUE(X)                (g_stTMDSRx2ColorInfo.ucDigitalColorSpacePreValue = (X))

#define GET_TMDS_RX2_COLOR_DEPTH_PREVALUE()                 (g_stTMDSRx2ColorInfo.b3DigitalColorDepthPreValue)
#define SET_TMDS_RX2_COLOR_DEPTH_PREVALUE(X)                (g_stTMDSRx2ColorInfo.b3DigitalColorDepthPreValue = (X))

#define GET_TMDS_RX2_COLORIMETRY_PREVALUE()                 (g_stTMDSRx2ColorInfo.b4DigitalColorimetryPreValue)
#define SET_TMDS_RX2_COLORIMETRY_PREVALUE(X)                (g_stTMDSRx2ColorInfo.b4DigitalColorimetryPreValue = (X))

#define GET_TMDS_RX2_COLORIMETRY_EXT_PREVALUE()             (g_stTMDSRx2ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_TMDS_RX2_COLORIMETRY_EXT_PREVALUE(X)            (g_stTMDSRx2ColorInfo.b4DigitalColorimetryExtPreValue = (X))

#define GET_TMDS_RX2_QUANTIZATION_PREVALUE()                (g_stTMDSRx2ColorInfo.b2DigitalQuantizationPreValue)
#define SET_TMDS_RX2_QUANTIZATION_PREVALUE(X)               (g_stTMDSRx2ColorInfo.b2DigitalQuantizationPreValue = (X))

#define GET_TMDS_RX2_COLORIMETRY_CHANGED()                  (g_stTMDSRx2ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_TMDS_RX2_COLORIMETRY_CHANGED()                  (g_stTMDSRx2ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_TMDS_RX2_COLORIMETRY_CHANGED()                  (g_stTMDSRx2ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_TMDS_RX2_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx2ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_TMDS_RX2_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx2ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_TMDS_RX2_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx2ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_TMDS_RX2_QUANTIZATION_CHANGED()                 (g_stTMDSRx2ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_TMDS_RX2_QUANTIZATION_CHANGED()                 (g_stTMDSRx2ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_TMDS_RX2_QUANTIZATION_CHANGED()                 (g_stTMDSRx2ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#define GET_TMDS_RX3_COLOR_SPACE_PREVALUE()                 (g_stTMDSRx3ColorInfo.ucDigitalColorSpacePreValue)
#define SET_TMDS_RX3_COLOR_SPACE_PREVALUE(X)                (g_stTMDSRx3ColorInfo.ucDigitalColorSpacePreValue = (X))

#define GET_TMDS_RX3_COLOR_DEPTH_PREVALUE()                 (g_stTMDSRx3ColorInfo.b3DigitalColorDepthPreValue)
#define SET_TMDS_RX3_COLOR_DEPTH_PREVALUE(X)                (g_stTMDSRx3ColorInfo.b3DigitalColorDepthPreValue = (X))

#define GET_TMDS_RX3_COLORIMETRY_PREVALUE()                 (g_stTMDSRx3ColorInfo.b4DigitalColorimetryPreValue)
#define SET_TMDS_RX3_COLORIMETRY_PREVALUE(X)                (g_stTMDSRx3ColorInfo.b4DigitalColorimetryPreValue = (X))

#define GET_TMDS_RX3_COLORIMETRY_EXT_PREVALUE()             (g_stTMDSRx3ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_TMDS_RX3_COLORIMETRY_EXT_PREVALUE(X)            (g_stTMDSRx3ColorInfo.b4DigitalColorimetryExtPreValue = (X))

#define GET_TMDS_RX3_QUANTIZATION_PREVALUE()                (g_stTMDSRx3ColorInfo.b2DigitalQuantizationPreValue)
#define SET_TMDS_RX3_QUANTIZATION_PREVALUE(X)               (g_stTMDSRx3ColorInfo.b2DigitalQuantizationPreValue = (X))

#define GET_TMDS_RX3_COLORIMETRY_CHANGED()                  (g_stTMDSRx3ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_TMDS_RX3_COLORIMETRY_CHANGED()                  (g_stTMDSRx3ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_TMDS_RX3_COLORIMETRY_CHANGED()                  (g_stTMDSRx3ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_TMDS_RX3_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx3ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_TMDS_RX3_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx3ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_TMDS_RX3_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx3ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_TMDS_RX3_QUANTIZATION_CHANGED()                 (g_stTMDSRx3ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_TMDS_RX3_QUANTIZATION_CHANGED()                 (g_stTMDSRx3ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_TMDS_RX3_QUANTIZATION_CHANGED()                 (g_stTMDSRx3ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#define GET_TMDS_RX4_COLOR_SPACE_PREVALUE()                 (g_stTMDSRx4ColorInfo.ucDigitalColorSpacePreValue)
#define SET_TMDS_RX4_COLOR_SPACE_PREVALUE(X)                (g_stTMDSRx4ColorInfo.ucDigitalColorSpacePreValue = (X))

#define GET_TMDS_RX4_COLOR_DEPTH_PREVALUE()                 (g_stTMDSRx4ColorInfo.b3DigitalColorDepthPreValue)
#define SET_TMDS_RX4_COLOR_DEPTH_PREVALUE(X)                (g_stTMDSRx4ColorInfo.b3DigitalColorDepthPreValue = (X))

#define GET_TMDS_RX4_COLORIMETRY_PREVALUE()                 (g_stTMDSRx4ColorInfo.b4DigitalColorimetryPreValue)
#define SET_TMDS_RX4_COLORIMETRY_PREVALUE(X)                (g_stTMDSRx4ColorInfo.b4DigitalColorimetryPreValue = (X))

#define GET_TMDS_RX4_COLORIMETRY_EXT_PREVALUE()             (g_stTMDSRx4ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_TMDS_RX4_COLORIMETRY_EXT_PREVALUE(X)            (g_stTMDSRx4ColorInfo.b4DigitalColorimetryExtPreValue = (X))

#define GET_TMDS_RX4_QUANTIZATION_PREVALUE()                (g_stTMDSRx4ColorInfo.b2DigitalQuantizationPreValue)
#define SET_TMDS_RX4_QUANTIZATION_PREVALUE(X)               (g_stTMDSRx4ColorInfo.b2DigitalQuantizationPreValue = (X))

#define GET_TMDS_RX4_COLORIMETRY_CHANGED()                  (g_stTMDSRx4ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_TMDS_RX4_COLORIMETRY_CHANGED()                  (g_stTMDSRx4ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_TMDS_RX4_COLORIMETRY_CHANGED()                  (g_stTMDSRx4ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_TMDS_RX4_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx4ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_TMDS_RX4_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx4ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_TMDS_RX4_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx4ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_TMDS_RX4_QUANTIZATION_CHANGED()                 (g_stTMDSRx4ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_TMDS_RX4_QUANTIZATION_CHANGED()                 (g_stTMDSRx4ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_TMDS_RX4_QUANTIZATION_CHANGED()                 (g_stTMDSRx4ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#define GET_TMDS_RX5_COLOR_SPACE_PREVALUE()                 (g_stTMDSRx5ColorInfo.ucDigitalColorSpacePreValue)
#define SET_TMDS_RX5_COLOR_SPACE_PREVALUE(X)                (g_stTMDSRx5ColorInfo.ucDigitalColorSpacePreValue = (X))

#define GET_TMDS_RX5_COLOR_DEPTH_PREVALUE()                 (g_stTMDSRx5ColorInfo.b3DigitalColorDepthPreValue)
#define SET_TMDS_RX5_COLOR_DEPTH_PREVALUE(X)                (g_stTMDSRx5ColorInfo.b3DigitalColorDepthPreValue = (X))

#define GET_TMDS_RX5_COLORIMETRY_PREVALUE()                 (g_stTMDSRx5ColorInfo.b4DigitalColorimetryPreValue)
#define SET_TMDS_RX5_COLORIMETRY_PREVALUE(X)                (g_stTMDSRx5ColorInfo.b4DigitalColorimetryPreValue = (X))

#define GET_TMDS_RX5_COLORIMETRY_EXT_PREVALUE()             (g_stTMDSRx5ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_TMDS_RX5_COLORIMETRY_EXT_PREVALUE(X)            (g_stTMDSRx5ColorInfo.b4DigitalColorimetryExtPreValue = (X))

#define GET_TMDS_RX5_QUANTIZATION_PREVALUE()                (g_stTMDSRx5ColorInfo.b2DigitalQuantizationPreValue)
#define SET_TMDS_RX5_QUANTIZATION_PREVALUE(X)               (g_stTMDSRx5ColorInfo.b2DigitalQuantizationPreValue = (X))

#define GET_TMDS_RX5_COLORIMETRY_CHANGED()                  (g_stTMDSRx5ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_TMDS_RX5_COLORIMETRY_CHANGED()                  (g_stTMDSRx5ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_TMDS_RX5_COLORIMETRY_CHANGED()                  (g_stTMDSRx5ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_TMDS_RX5_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx5ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_TMDS_RX5_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx5ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_TMDS_RX5_COLORIMETRY_EXT_CHANGED()              (g_stTMDSRx5ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_TMDS_RX5_QUANTIZATION_CHANGED()                 (g_stTMDSRx5ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_TMDS_RX5_QUANTIZATION_CHANGED()                 (g_stTMDSRx5ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_TMDS_RX5_QUANTIZATION_CHANGED()                 (g_stTMDSRx5ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)
#endif

#if(_D0_DP_EXIST == _ON)
#define GET_DP_RX0_COLOR_SPACE_PREVALUE()                   (g_stDpRx0ColorInfo.ucDigitalColorSpacePreValue)
#define SET_DP_RX0_COLOR_SPACE_PREVALUE(X)                  (g_stDpRx0ColorInfo.ucDigitalColorSpacePreValue = (X))

#define GET_DP_RX0_COLOR_DEPTH_PREVALUE()                   (g_stDpRx0ColorInfo.b3DigitalColorDepthPreValue)
#define SET_DP_RX0_COLOR_DEPTH_PREVALUE(X)                  (g_stDpRx0ColorInfo.b3DigitalColorDepthPreValue = (X))

#define GET_DP_RX0_COLORIMETRY_PREVALUE()                   (g_stDpRx0ColorInfo.b4DigitalColorimetryPreValue)
#define SET_DP_RX0_COLORIMETRY_PREVALUE(X)                  (g_stDpRx0ColorInfo.b4DigitalColorimetryPreValue = (X))

#define GET_DP_RX0_COLORIMETRY_EXT_PREVALUE()               (g_stDpRx0ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_DP_RX0_COLORIMETRY_EXT_PREVALUE(X)              (g_stDpRx0ColorInfo.b4DigitalColorimetryExtPreValue = (X))

#define GET_DP_RX0_QUANTIZATION_PREVALUE()                  (g_stDpRx0ColorInfo.b2DigitalQuantizationPreValue)
#define SET_DP_RX0_QUANTIZATION_PREVALUE(X)                 (g_stDpRx0ColorInfo.b2DigitalQuantizationPreValue = (X))

#define GET_DP_RX0_COLORIMETRY_CHANGED()                    (g_stDpRx0ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_DP_RX0_COLORIMETRY_CHANGED()                    (g_stDpRx0ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_DP_RX0_COLORIMETRY_CHANGED()                    (g_stDpRx0ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_DP_RX0_COLORIMETRY_EXT_CHANGED()                (g_stDpRx0ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_DP_RX0_COLORIMETRY_EXT_CHANGED()                (g_stDpRx0ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_DP_RX0_COLORIMETRY_EXT_CHANGED()                (g_stDpRx0ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_DP_RX0_QUANTIZATION_CHANGED()                   (g_stDpRx0ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_DP_RX0_QUANTIZATION_CHANGED()                   (g_stDpRx0ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_DP_RX0_QUANTIZATION_CHANGED()                   (g_stDpRx0ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)
#endif

#if(_D1_DP_EXIST == _ON)
#define GET_DP_RX1_COLOR_SPACE_PREVALUE()                   (g_stDpRx1ColorInfo.ucDigitalColorSpacePreValue)
#define SET_DP_RX1_COLOR_SPACE_PREVALUE(X)                  (g_stDpRx1ColorInfo.ucDigitalColorSpacePreValue = (X))

#define GET_DP_RX1_COLOR_DEPTH_PREVALUE()                   (g_stDpRx1ColorInfo.b3DigitalColorDepthPreValue)
#define SET_DP_RX1_COLOR_DEPTH_PREVALUE(X)                  (g_stDpRx1ColorInfo.b3DigitalColorDepthPreValue = (X))

#define GET_DP_RX1_COLORIMETRY_PREVALUE()                   (g_stDpRx1ColorInfo.b4DigitalColorimetryPreValue)
#define SET_DP_RX1_COLORIMETRY_PREVALUE(X)                  (g_stDpRx1ColorInfo.b4DigitalColorimetryPreValue = (X))

#define GET_DP_RX1_COLORIMETRY_EXT_PREVALUE()               (g_stDpRx1ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_DP_RX1_COLORIMETRY_EXT_PREVALUE(X)              (g_stDpRx1ColorInfo.b4DigitalColorimetryExtPreValue = (X))

#define GET_DP_RX1_QUANTIZATION_PREVALUE()                  (g_stDpRx1ColorInfo.b2DigitalQuantizationPreValue)
#define SET_DP_RX1_QUANTIZATION_PREVALUE(X)                 (g_stDpRx1ColorInfo.b2DigitalQuantizationPreValue = (X))

#define GET_DP_RX1_COLORIMETRY_CHANGED()                    (g_stDpRx1ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_DP_RX1_COLORIMETRY_CHANGED()                    (g_stDpRx1ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_DP_RX1_COLORIMETRY_CHANGED()                    (g_stDpRx1ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_DP_RX1_COLORIMETRY_EXT_CHANGED()                (g_stDpRx1ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_DP_RX1_COLORIMETRY_EXT_CHANGED()                (g_stDpRx1ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_DP_RX1_COLORIMETRY_EXT_CHANGED()                (g_stDpRx1ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_DP_RX1_QUANTIZATION_CHANGED()                   (g_stDpRx1ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_DP_RX1_QUANTIZATION_CHANGED()                   (g_stDpRx1ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_DP_RX1_QUANTIZATION_CHANGED()                   (g_stDpRx1ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)
#endif

#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
#define GET_URGENT_EVENT_OCCUR_FLG()                        (g_ucCheckUrgentEventOccured)
#define SET_URGENT_EVENT_OCCUR_FLG()                        (g_ucCheckUrgentEventOccured = _TRUE)
#define CLR_URGENT_EVENT_OCCUR_FLG()                        (g_ucCheckUrgentEventOccured = _FALSE)
#endif

#if(_HDR10_SUPPORT == _ON)
#define CLR_HDR10_SETTING_DATA()                            (memset(&g_stHDR10Setting, 0, sizeof(StructHDR10Setting)))
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
#define CLR_FREESYNC_II_SETTING_DATA()                      (memset(&g_stFreeSyncIISetting, 0, sizeof(StructFreeSyncIIInfo)))
#endif

//--------------------------------------------------
// Macro of HDR10 Setting
//--------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
#define GET_HDR10_EOTF_SETTING()                            (g_stHDR10Setting.enumHDR10EOTFSetting)
#define SET_HDR10_EOTF_SETTING(x)                           (g_stHDR10Setting.enumHDR10EOTFSetting = (x))

#define GET_HDR10_MAX_LV_SETTING()                          (g_stHDR10Setting.enumHDR10MaxLVSetting)
#define SET_HDR10_MAX_LV_SETTING(x)                         (g_stHDR10Setting.enumHDR10MaxLVSetting = (x))

#define GET_RX0_HDR10_SUPPORT()                             (g_stHDR10PortSettingInfo.enumHDR10RX0Support)
#define SET_RX0_HDR10_SUPPORT(x)                            (g_stHDR10PortSettingInfo.enumHDR10RX0Support = (x))

#define GET_RX1_HDR10_SUPPORT()                             (g_stHDR10PortSettingInfo.enumHDR10RX1Support)
#define SET_RX1_HDR10_SUPPORT(x)                            (g_stHDR10PortSettingInfo.enumHDR10RX1Support = (x))

#define GET_RX2_HDR10_SUPPORT()                             (g_stHDR10PortSettingInfo.enumHDR10RX2Support)
#define SET_RX2_HDR10_SUPPORT(x)                            (g_stHDR10PortSettingInfo.enumHDR10RX2Support = (x))

#define GET_RX3_HDR10_SUPPORT()                             (g_stHDR10PortSettingInfo.enumHDR10RX3Support)
#define SET_RX3_HDR10_SUPPORT(x)                            (g_stHDR10PortSettingInfo.enumHDR10RX3Support = (x))

#define GET_RX4_HDR10_SUPPORT()                             (g_stHDR10PortSettingInfo.enumHDR10RX4Support)
#define SET_RX4_HDR10_SUPPORT(x)                            (g_stHDR10PortSettingInfo.enumHDR10RX4Support = (x))

#define GET_RX5_HDR10_SUPPORT()                             (g_stHDR10PortSettingInfo.enumHDR10RX5Support)
#define SET_RX5_HDR10_SUPPORT(x)                            (g_stHDR10PortSettingInfo.enumHDR10RX5Support = (x))

#define GET_RX6_HDR10_SUPPORT()                             (g_stHDR10PortSettingInfo.enumHDR10RX6Support)
#define SET_RX6_HDR10_SUPPORT(x)                            (g_stHDR10PortSettingInfo.enumHDR10RX6Support = (x))
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
#define GET_AIO_MODERN_STANDBY_MODE()                       (g_bAIOModernStandbyMode)
#define SET_AIO_MODERN_STANDBY_MODE()                       (g_bAIOModernStandbyMode = _TRUE)
#define CLR_AIO_MODERN_STANDBY_MODE()                       (g_bAIOModernStandbyMode = _FALSE)
#endif

//--------------------------------------------------
// Macro of DP Timer2 IRQ Delay Counter
//--------------------------------------------------
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
#define DP_RX_HPD_IRQ_ASSERT_T2_DELAY_INITIAL()             (g_ucDpRxHpdIrqAssertT2EventDelayXus_Counter = ((WORD)((95 - GET_DP_IRQ_TIME_10US()) * 10) >> 2))
#define DP_RX_HPD_IRQ_ASSERT_T2_DELAY()                     {\
                                                                if(g_ucDpRxHpdIrqAssertT2EventDelayXus_Counter > 0)\
                                                                {\
                                                                    ScalerSyncDpAuxManualModeSetting_EXINT(_DP_AUX_MANUAL_MODE_SET);\
                                                                    do\
                                                                    {\
                                                                        g_ucDpRxHpdIrqAssertT2EventDelay5usI = g_ucDelay5usN_Base;\
                                                                        while(--g_ucDpRxHpdIrqAssertT2EventDelay5usI) {};\
                                                                    }\
                                                                    while(--g_ucDpRxHpdIrqAssertT2EventDelayXus_Counter);\
                                                                    ScalerSyncDpAuxManualModeSetting_EXINT(_DP_AUX_MANUAL_MODE_RECOVER);\
                                                                }\
                                                            }

//--------------------------------------------------
// Macro of DP IRQ Assert Timer2 Event
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define GET_DP_D0_HPD_IRQ_ASSERT_T2_EVENT()                 (g_bDpD0HpdIrqAssertT2Event)
#define SET_DP_D0_HPD_IRQ_ASSERT_T2_EVENT()                 {\
                                                                g_bDpD0HpdIrqAssertT2Event = _TRUE;\
                                                                DP_RX_HPD_IRQ_ASSERT_T2_DELAY_INITIAL();\
                                                            }
#define CLR_DP_D0_HPD_IRQ_ASSERT_T2_EVENT()                 (g_bDpD0HpdIrqAssertT2Event = _FALSE)
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define GET_DP_D1_HPD_IRQ_ASSERT_T2_EVENT()                 (g_bDpD1HpdIrqAssertT2Event)
#define SET_DP_D1_HPD_IRQ_ASSERT_T2_EVENT()                 {\
                                                                g_bDpD1HpdIrqAssertT2Event = _TRUE;\
                                                                DP_RX_HPD_IRQ_ASSERT_T2_DELAY_INITIAL();\
                                                            }
#define CLR_DP_D1_HPD_IRQ_ASSERT_T2_EVENT()                 (g_bDpD1HpdIrqAssertT2Event = _FALSE)
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#define GET_DP_D2_HPD_IRQ_ASSERT_T2_EVENT()                 (g_bDpD2HpdIrqAssertT2Event)
#define SET_DP_D2_HPD_IRQ_ASSERT_T2_EVENT()                 {\
                                                                g_bDpD2HpdIrqAssertT2Event = _TRUE;\
                                                                DP_RX_HPD_IRQ_ASSERT_T2_DELAY_INITIAL();\
                                                            }
#define CLR_DP_D2_HPD_IRQ_ASSERT_T2_EVENT()                 (g_bDpD2HpdIrqAssertT2Event = _FALSE)
#endif
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Structure of TMDS Control Definitions
//--------------------------------------------------
typedef struct
{
    BYTE b1RGBHVDetecting : 1;
    BYTE b1PacketDetecting : 1;
    BYTE b1AVIInfoFrameReceived : 1;
    BYTE b1GCPReceived : 1;
    BYTE b1Z0Asserted : 1;
    BYTE b1TMDSDdcDetected : 1;
    BYTE b1TMDSPhySet : 1;

#if(_HDMI_2_0_SUPPORT == _ON)
    BYTE b1HDMI2FormatResetWaiting : 1;
    BYTE b1HDMI2RREnable : 1;
    BYTE b1HDMI2HighSpeedMode : 1;
#endif

#if(_HDR10_SUPPORT == _ON)
    BYTE b1HDRInfoFrameReceived : 1;
#endif

    BYTE b3HPDTriggerEvent : 3;
} StructTMDSCtrlInfo;

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
typedef struct
{
    BYTE b1TMDSRx0Z0Toggle : 1;
    BYTE b1TMDSRx1Z0Toggle : 1;
    BYTE b1TMDSRx2Z0Toggle : 1;
    BYTE b1TMDSRx3Z0Toggle : 1;
    BYTE b1TMDSRx4Z0Toggle : 1;
    BYTE b1TMDSRx5Z0Toggle : 1;
    BYTE b1TMDSRx0GlobalZ0Toggle : 1;
    BYTE b1TMDSRx1GlobalZ0Toggle : 1;
    BYTE b1TMDSRx2GlobalZ0Toggle : 1;
    BYTE b1TMDSRx3GlobalZ0Toggle : 1;
    BYTE b1TMDSRx4GlobalZ0Toggle : 1;
    BYTE b1TMDSRx5GlobalZ0Toggle : 1;
} StructTmdsZ0ToggleFlag;
#endif


//--------------------------------------------------
// Struct of TMDS HPD Sequence
//--------------------------------------------------
typedef struct
{
    EnumSourceSearchPort enumPort;
    WORD usHpdTime;
} StructTmdsHpdSequence;

#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

#if(_MHL_SUPPORT == _ON)
//--------------------------------------------------
// Structure of MHL State Definitions
//--------------------------------------------------
typedef struct
{
    BYTE b4MHLProcessState : 4;
    BYTE b1MHLTransmitStatus : 1;
    BYTE b1MHLResendStatus : 1;
    BYTE b1MHLSwitchPortDiscoveryDoneStatus : 1;
} StructMHLProcessInfo;
#endif // End of #if(_MHL_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Structure of DP Port Hot Plug Assert Type
//--------------------------------------------------
typedef struct
{
#if(_D0_DP_EXIST == _ON)
    EnumDpHotPlugAssertType enumD0HpdAssertType;
#endif
#if(_D1_DP_EXIST == _ON)
    EnumDpHotPlugAssertType enumD1HpdAssertType;
#endif
#if(_D2_DP_EXIST == _ON)
    EnumDpHotPlugAssertType enumD2HpdAssertType;
#endif
} StructDpPortHpdAssertType;

//--------------------------------------------------
// Structure of DP Port Hot Plug Time
//--------------------------------------------------
typedef struct
{
#if(_D0_DP_EXIST == _ON)
    EnumDpHotPlugTime enumD0HpdTime;
#endif
#if(_D1_DP_EXIST == _ON)
    EnumDpHotPlugTime enumD1HpdTime;
#endif
#if(_D2_DP_EXIST == _ON)
    EnumDpHotPlugTime enumD2HpdTime;
#endif
} StructDpPortHpdTime;

//--------------------------------------------------
// Struct of HPD Sequence for HotPlugHandler
//--------------------------------------------------
typedef struct
{
    EnumSourceSearchPort enumPort;
    EnumDpHotPlugTime enumHpdTime;
} StructHpdSequence;

//--------------------------------------------------
// Definitions for DP Capability Switch
//--------------------------------------------------
typedef struct
{
    BYTE ucD0Version;
    BYTE ucD1Version;
    BYTE ucD6Version;
    BYTE ucD0LaneCount;
    BYTE ucD1LaneCount;
    BYTE ucD6LaneCount;
    BYTE b1D0Edid : 1;
    BYTE b1D1Edid : 1;
    BYTE b1D6Edid : 1;
    BYTE b2MSTPort : 2;
    BYTE b1Rx0HdcpCap : 1;
    BYTE b1Rx1HdcpCap : 1;
    BYTE b1MsgSwitched : 1;
} StructDPCapSwitchInfo;

typedef struct
{
    BYTE b1CloneModeCap : 1;
} StructCloneModeSwitchInfo;

//--------------------------------------------------
// Definitions for DP Tx
//--------------------------------------------------
typedef struct
{
    BYTE b2HdcpUpstreamPort : 2;
    BYTE b2Hdcp2UpstreamPort : 2;
} StructDPTxStatusInfo;

//--------------------------------------------------
// Struct of DP Cable Status
//--------------------------------------------------
typedef struct
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    BYTE b1D0Status : 1;
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    BYTE b1D1Status : 1;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    BYTE b1D2Status : 1;
#endif
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
    BYTE b1D6Status : 1;
#endif
} StructDpCableStatus;

//--------------------------------------------------
// Enumerations for DP Maunual Mode Setting
//--------------------------------------------------
typedef enum
{
    _DP_AUX_MANUAL_MODE_SET = 0x00,
    _DP_AUX_MANUAL_MODE_RECOVER = 0x01,
} EnumDpAuxManualModeSetting;

//--------------------------------------------------
// Enumerations for DP Action after Check Source OUI
//--------------------------------------------------
typedef enum
{
    _LT_TP1_PERMIT_SWING_LEVEL_0,
}EnumDpRxCheckSourceOUI;
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Struct of HDMI Rx PS Wakeup HPD Toggle
//--------------------------------------------------
typedef struct
{
    BYTE b1Rx0PsWakeupHpd : 1;
    BYTE b1Rx1PsWakeupHpd : 1;
    BYTE b1Rx2PsWakeupHpd : 1;
    BYTE b1Rx3PsWakeupHpd : 1;
    BYTE b1Rx4PsWakeupHpd : 1;
    BYTE b1Rx5PsWakeupHpd : 1;
} StructHdmiRxPsWakeupHpd;

//--------------------------------------------------
// Definitions of AVI Info Content Types
//--------------------------------------------------
typedef enum
{
    _AVI_COLOR_SPACE_00 = _AVI_COLOR_SPACE_RGB,
    _AVI_COLOR_SPACE_01 = _AVI_COLOR_SPACE_YCC_422,
    _AVI_COLOR_SPACE_10 = _AVI_COLOR_SPACE_YCC_444,
    _AVI_COLOR_SPACE_11 = _AVI_COLOR_SPACE_YCC_420,
    _AVI_COLOR_SPACE_KERNEL_RESERVED = 0x04,
} EnumAviInfoColorSpaceKernel;

typedef enum
{
    _AVI_COLORIMETRY_00 = _AVI_COLORIMETRY_NONE,
    _AVI_COLORIMETRY_01 = _AVI_COLORIMETRY_ITU601,
    _AVI_COLORIMETRY_10 = _AVI_COLORIMETRY_ITU709,
    _AVI_COLORIMETRY_11 = 0x03,
} EnumAviInfoColorimetryKernel;

typedef enum
{
    _AVI_COLORIMETRY_EXT_000 = _AVI_COLORIMETRY_EXT_XVYCC601,
    _AVI_COLORIMETRY_EXT_001 = _AVI_COLORIMETRY_EXT_XVYCC709,
    _AVI_COLORIMETRY_EXT_010 = _AVI_COLORIMETRY_EXT_SYCC601,
    _AVI_COLORIMETRY_EXT_011 = _AVI_COLORIMETRY_EXT_ADOBEYCC601,
    _AVI_COLORIMETRY_EXT_100 = _AVI_COLORIMETRY_EXT_ADOBERGB,
    _AVI_COLORIMETRY_EXT_101 = _AVI_COLORIMETRY_EXT_ITUR_BT2020_1,
    _AVI_COLORIMETRY_EXT_110 = _AVI_COLORIMETRY_EXT_ITUR_BT2020_2,
    _AVI_COLORIMETRY_EXT_111 = 0x07,
} EnumAviInfoColorimetryExtKernel;

#endif

//--------------------------------------------------
// Definitions of DP SDP Packet Type
//--------------------------------------------------
typedef enum
{
    _DP_SDP_TYPE_AUD_TIMESTAMP = 0x01,
    _DP_SDP_TYPE_AUD_STREAM,
    _DP_SDP_TYPE_EXTENSION = 0x04,
    _DP_SDP_TYPE_AUD_COPYMANAGEMENT,
    _DP_SDP_TYPE_ISRC,
    _DP_SDP_TYPE_VSC,
    _DP_SDP_TYPE_CAM_GEN_0,
    _DP_SDP_TYPE_CAM_GEN_1,
    _DP_SDP_TYPE_CAM_GEN_2,
    _DP_SDP_TYPE_CAM_GEN_3,
    _DP_SDP_TYPE_CAM_GEN_4,
    _DP_SDP_TYPE_CAM_GEN_5,
    _DP_SDP_TYPE_CAM_GEN_6,
    _DP_SDP_TYPE_CAM_GEN_7,
    _DP_SDP_TYPE_PPS,
    _DP_SDP_TYPE_VSC_EXT_VESA = 0x20,
    _DP_SDP_TYPE_VSC_EXT_CEA,
    _DP_SDP_TYPE_INFOFRAME_RSV = 0x80,
    _DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC,
    _DP_SDP_TYPE_INFOFRAME_AUX_VID_INFO,
    _DP_SDP_TYPE_INFOFRAME_SRC_PROD_DESC,
    _DP_SDP_TYPE_INFOFRAME_AUDIO,
    _DP_SDP_TYPE_INFOFRAME_MPEG,
    _DP_SDP_TYPE_INFOFRAME_NTSC_VBI,
}EnumDpSdpType;

#if(_HW_DP_INFOFRAME_RSV1_LENGTH != 0)
//--------------------------------------------------
// Definitions for DP Infoframe RSV1 SRAM Address
//--------------------------------------------------
typedef enum
{
    _DP_INFO_RSV1_DB0 = 0x3D,
    _DP_INFO_RSV1_DB1,
    _DP_INFO_RSV1_DB2,
    _DP_INFO_RSV1_DB3,
    _DP_INFO_RSV1_DB4,
    _DP_INFO_RSV1_DB5,
    _DP_INFO_RSV1_DB6,
    _DP_INFO_RSV1_DB7,
    _DP_INFO_RSV1_DB8,
    _DP_INFO_RSV1_DB9,
    _DP_INFO_RSV1_DB10,
    _DP_INFO_RSV1_DB11,
    _DP_INFO_RSV1_DB12,
    _DP_INFO_RSV1_DB13,
    _DP_INFO_RSV1_DB14,
    _DP_INFO_RSV1_DB15,
    _DP_INFO_RSV1_DB16,
    _DP_INFO_RSV1_DB17,
    _DP_INFO_RSV1_DB18,
    _DP_INFO_RSV1_DB19,
    _DP_INFO_RSV1_DB20,
    _DP_INFO_RSV1_DB21,
    _DP_INFO_RSV1_DB22,
    _DP_INFO_RSV1_DB23,
    _DP_INFO_RSV1_DB24,
    _DP_INFO_RSV1_DB25,
    _DP_INFO_RSV1_DB26,
    _DP_INFO_RSV1_DB27,
#if(_HW_DP_INFOFRAME_RSV1_LENGTH == 32)
    _DP_INFO_RSV1_DB28,
    _DP_INFO_RSV1_DB29,
    _DP_INFO_RSV1_DB30,
    _DP_INFO_RSV1_DB31,
#endif
}EnumDpInfoFrameRsv1;
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of VSC Color Format Types
//--------------------------------------------------
typedef enum
{
    _VSC_COLOR_SPACE_0 = 0x00,
    _VSC_COLOR_SPACE_1 = 0x10,
    _VSC_COLOR_SPACE_2 = 0x20,
    _VSC_COLOR_SPACE_3 = 0x30,
    _VSC_COLOR_SPACE_4 = 0x40,
    _VSC_COLOR_SPACE_5 = 0x50,
} EnumVscColorSpace;

typedef enum
{
    _VSC_COLORIMETRY_0 = 0x00,
    _VSC_COLORIMETRY_1 = 0x01,
    _VSC_COLORIMETRY_2 = 0x02,
    _VSC_COLORIMETRY_3 = 0x03,
    _VSC_COLORIMETRY_4 = 0x04,
    _VSC_COLORIMETRY_5 = 0x05,
    _VSC_COLORIMETRY_6 = 0x06,
    _VSC_COLORIMETRY_7 = 0x07,
} EnumVscColorimetry;
#endif

typedef enum
{
    _DP_COLOR_QUANTIZATION_FULL = 0x00,
    _DP_COLOR_QUANTIZATION_LIMIT = 0x01,
} EnumDPColorQuantization;

//--------------------------------------------------
// Definitions for DP training Pattern 1 FLD Reference Clock Select
//--------------------------------------------------
typedef enum
{
    _DP_NF_REF_XTAL = 0x00,
    _DP_NF_REF_D10_2,
} EnumDpNFCodeRef;

//--------------------------------------------------
// Enumerations of DP Reset Status
//--------------------------------------------------
typedef enum
{
    _DP_DPCD_LINK_STATUS_INITIAL = 0x00,
    _DP_DPCD_LINK_STATUS_RESET = 0x01,
} EnumDpResetStatus;

//--------------------------------------------------
// Enumerations of DP HDCP B Status Type
//--------------------------------------------------
typedef enum
{
    _DP_HDCP_BSTATUS_V_READY = _BIT0,
    _DP_HDCP_BSTATUS_R0_AVAILABLE = _BIT1,
    _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL = _BIT2,
    _DP_HDCP_BSTATUS_REAUTH_REQ = _BIT3,
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    _DP_HDCP2_H_PRIME_AVAILABLE = _BIT4,
    _DP_HDCP2_PARING_AVAILABLE = _BIT5,
    _DP_HDCP2_V_READY = _BIT6,
    _DP_HDCP2_RXSTATUS_REAUTH_REQ = _BIT7,
#endif
} EnumDpRxBStatusType;

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of HDCP Rx Port
//--------------------------------------------------
typedef enum
{
    _HDCP_NO_PORT,
    _HDCP_D0_PORT,
    _HDCP_D1_PORT,
} EnumDpHdcpUpstreamPort;

//--------------------------------------------------
// Definitions of DP Tx Color Info PreValue
//--------------------------------------------------
typedef struct
{
    BYTE ucColorSpacePreValue;
    BYTE b3ColorDepthPreValue : 3;
} StructDpTxColorInfo;
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DP Source Write 600h = 0x01 Status
//--------------------------------------------------
typedef enum
{
    _DP_SOURCE_WRITE_POWER_UP_NONE,
    _DP_SOURCE_WRITE_POWER_UP_TRIGGERED,
    _DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE,
} EnumDpSourceWritePowerUpState;

//--------------------------------------------------
// Struct for RX Aux Ch Power Detect
//--------------------------------------------------
typedef struct
{
    BYTE b1DpCheckAuxChNoPowerDebounce : 1;
    BYTE b1DpAuxChPowerOnWakeUp : 1;
    BYTE b2DpCheckAuxChPowerStatus : 2;
    BYTE b1DpSourceFirstPowerOn : 1;
    BYTE b1DpMstEnableBackup : 1;
    EnumDpSourceWritePowerUpState enumDpSourceWritePowerUp;
    BYTE ucDpRxLinkRateBackup;
    BYTE ucDpRxLaneCountBackup;
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    BYTE b1DpRx6MstEnableBackup : 1;
#endif
} StructDPRxMiscInfo;

//--------------------------------------------------
// AUX Channel Power Status
//--------------------------------------------------
typedef enum
{
    _DP_RX_AUX_POWER_STATUS_NONE,
    _DP_RX_AUX_POWER_STATUS_ON,
    _DP_RX_AUX_POWER_STATUS_OFF,
} EnumDPRxAuxPowerStatus;

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Struct for RX HDCP Authentication
//--------------------------------------------------
typedef struct
{
    BYTE b4AuthState : 4;
    BYTE b1AuthStateChange : 1;
    BYTE b1AuthRepeaterProcTimeout : 1;
    BYTE b1AuthReadIrqTimeout : 1;
    BYTE ucAuthUpstreamEvent;
    BYTE b1AuthCpIrqTimer : 1;
} StructDPRxHDCPAuthInfo;

//--------------------------------------------------
//HDCP RX Authentication State
//--------------------------------------------------
typedef enum
{
    _DP_RX_HDCP_STATE_IDLE = 0,
    _DP_RX_HDCP_STATE_AUTH_FAKE,
    _DP_RX_HDCP_STATE_AUTH_1,
    _DP_RX_HDCP_STATE_AUTH_2,
    _DP_RX_HDCP_STATE_AUTH_DONE,
} EnumDPRxHDCPAuthState;

//--------------------------------------------------
//HDCP RX Authentication Upstream Event
//--------------------------------------------------
typedef enum
{
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE = 0,
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION,
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS,
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT,
} EnumDPRxHDCPUpstreamAuthStatus;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
//HDCP RX Authentication State
//--------------------------------------------------
typedef enum
{
    _DP_RX_HDCP2_REPEATER_STATE_IDLE = 0,
    _DP_RX_HDCP2_REPEATER_STATE_AUTH_FAKE,
    _DP_RX_HDCP2_REPEATER_STATE_AUTH_1,
    _DP_RX_HDCP2_REPEATER_STATE_AUTH_2,
    _DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE,
} EnumDpRxHdcp2RepeaterAuthState;

//--------------------------------------------------
//HDCP RX Authentication Upstream Event
//--------------------------------------------------
typedef enum
{
    _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_NONE = 0,
    _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION,
    _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE,
    _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_TIMEOUT,
} EnumDpRxHdcp2UpstreamAuthStatus;
#endif
#endif
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
typedef struct
{
    BYTE b1DigitalColorimetryChanged : 1;
    BYTE b1DigitalColorimetryExtChanged : 1;
    BYTE b1DigitalQuantizationChanged : 1;
} StructDigitalColorInfoChanged;

typedef struct
{
    BYTE ucDigitalColorSpacePreValue;
    BYTE b4DigitalColorimetryPreValue : 4;
    BYTE b4DigitalColorimetryExtPreValue : 4;
    BYTE b3DigitalColorDepthPreValue : 3;
    BYTE b2DigitalQuantizationPreValue : 2;
} StructDigitalColorInfo;
#endif

typedef enum
{
    _DP_INFO_RSV0_DB0 = 0x21,
    _DP_INFO_RSV0_DB1 = 0x22,
    _DP_INFO_RSV0_DB2 = 0x23,
    _DP_INFO_RSV0_DB3 = 0x24,
    _DP_INFO_RSV0_DB4 = 0x25,
    _DP_INFO_RSV0_DB5 = 0x26,
    _DP_INFO_RSV0_DB6 = 0x27,
    _DP_INFO_RSV0_DB7 = 0x28,
    _DP_INFO_RSV0_DB8 = 0x29,
    _DP_INFO_RSV0_DB9 = 0x2A,
    _DP_INFO_RSV0_DB10 = 0x2B,
    _DP_INFO_RSV0_DB11 = 0x2C,
    _DP_INFO_RSV0_DB12 = 0x2D,
    _DP_INFO_RSV0_DB13 = 0x2E,
    _DP_INFO_RSV0_DB14 = 0x2F,
    _DP_INFO_RSV0_DB15 = 0x30,
    _DP_INFO_RSV0_DB16 = 0x31,
    _DP_INFO_RSV0_DB17 = 0x32,
    _DP_INFO_RSV0_DB18 = 0x33,
    _DP_INFO_RSV0_DB19 = 0x34,
    _DP_INFO_RSV0_DB20 = 0x35,
    _DP_INFO_RSV0_DB21 = 0x36,
    _DP_INFO_RSV0_DB22 = 0x37,
    _DP_INFO_RSV0_DB23 = 0x38,
    _DP_INFO_RSV0_DB24 = 0x39,
    _DP_INFO_RSV0_DB25 = 0x3A,
    _DP_INFO_RSV0_DB26 = 0x3B,
    _DP_INFO_RSV0_DB27 = 0x3C,
}EnumDPInfoFrameRSV0;

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Enum for Freesync II
//--------------------------------------------------
typedef enum
{
    _TMDS_INFO_RSV2_DB0 = 0x8F,
    _TMDS_INFO_RSV2_DB1 = 0x90,
}EnumHdrMasteringInfoFrameTMDSRSV2;
#endif // End of (_HDMI_FREESYNC_II_SUPPORT == _ON)

#if(_HDMI_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Enum for HDR
//--------------------------------------------------
typedef enum
{
    _HDR10_INFO_HDMI_VERSION = 0xAC,
    _HDR10_INFO_HDMI_LENGTH = 0xAD,
    _HDR10_INFO_HDMI_CHECKSUM = 0xAE,

    // A:chg_
    _HDR10_INFO_HDMI_EOTF = 0xAF,

    // B_
    _HDR10_INFO_HDMI_STATIC_METADATA_DESCRIPTOR_ID = 0xB0,

    // C:chg
    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB = 0xB1,

    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_Y0_LSB = 0xB3,

    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X1_LSB = 0xB5,

    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_Y1_LSB = 0xB7,

    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_X2_LSB = 0xB9,

    _HDR10_INFO_HDMI_DISPLAY_PRIMARIES_Y2_LSB = 0xBB,

    _HDR10_INFO_HDMI_WHITE_POINT_X_LSB = 0xBD,

    _HDR10_INFO_HDMI_WHITE_POINT_Y_LSB = 0xBF,

    // D:chg
    _HDR10_INFO_HDMI_MAX_LUMINANCE_LSB = 0xC1,

    // E
    _HDR10_INFO_HDMI_MIN_LUMINANCE_LSB = 0xC3,

    // F
    _HDR10_INFO_HDMI_MAX_CLL_LSB = 0xC5,

    // G
    _HDR10_INFO_HDMI_MAX_FALL_LSB = 0xC7,
}EnumHdr10MasteringInfoFrameTMDSRSV3;
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
typedef struct
{
    BYTE b1RSV0PacketDetecting : 1;
    BYTE b1HDRInfoFrameReceive : 1;
    BYTE b1AMDSPDInfoFrameReceive : 1;
    BYTE b1AudioInfoFrameReceive : 1;
} StructDPInfoFrameRSV0Ctrl;
#endif

#if((_DP_SUPPORT == _ON) && (_AIO_MODERN_STANDBY_SUPPORT == _ON))
typedef struct
{
    DWORD ulVBsToBsCountN;         // V BS to BS Count of The Nth Frame
    DWORD ulVBsToBsCountN1;        // V BS to BS Count of The (N+1)th Frame
    DWORD ulVBsToBsDelayEven;      // VBs2Bs Delay of Even Field
    DWORD ulVBsToBsDelayOdd;       // VBs2Bs Delay of Odd Field
    SDWORD lStreamClockOffset;      // Offset of Stream Clock
    BYTE bInterlaceFieldN : 1;     // VBID[1] Inerlace Field Flag of The Nth Frame
    BYTE bInterlaceFieldN1 : 1;    // VBID[1] Inerlace Field Flag of The (N+1)th Frame
    BYTE bInterlaceOddMode : 1;    // VBID[1] Inerlace Field Mode (Even or Odd)
}StructDpLinkInfo;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE data pData_EXINT[6];
extern WORD g_usInputPixelClk;
extern WORD g_usTmdsOffLineMeasureClk;

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern BYTE g_ucDigitalSwitch;
extern bit g_bDpDCOffHPDHigh;
extern BYTE g_ucHDMIHotPlug;
extern bit g_bDigitalColorInfoChangeReset;
extern StructDigitalColorInfo g_stDigitalColorInfo;

#if(((_D0_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF)) || ((_HDMI_SUPPORT == _ON) && (_TMDS_PAGE2_COMBO_EXIST == _ON)))
extern StructDigitalColorInfo g_stTMDSRx0ColorInfo;
extern StructDigitalColorInfoChanged g_stTMDSRx0ColorInfoChanged;
#endif

#if((_D1_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
extern StructDigitalColorInfo g_stTMDSRx1ColorInfo;
extern StructDigitalColorInfoChanged g_stTMDSRx1ColorInfoChanged;
#endif

#if((_D2_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
extern StructDigitalColorInfo g_stTMDSRx2ColorInfo;
extern StructDigitalColorInfoChanged g_stTMDSRx2ColorInfoChanged;
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
extern StructDigitalColorInfo g_stTMDSRx3ColorInfo;
extern StructDigitalColorInfoChanged g_stTMDSRx3ColorInfoChanged;
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
extern StructDigitalColorInfo g_stTMDSRx4ColorInfo;
extern StructDigitalColorInfoChanged g_stTMDSRx4ColorInfoChanged;
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
extern StructDigitalColorInfo g_stTMDSRx5ColorInfo;
extern StructDigitalColorInfoChanged g_stTMDSRx5ColorInfoChanged;
#endif

#if(_D0_DP_EXIST == _ON)
extern StructDigitalColorInfo g_stDpRx0ColorInfo;
extern StructDigitalColorInfoChanged g_stDpRx0ColorInfoChanged;
#endif

#if(_D1_DP_EXIST == _ON)
extern StructDigitalColorInfo g_stDpRx1ColorInfo;
extern StructDigitalColorInfoChanged g_stDpRx1ColorInfoChanged;
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
extern StructDpHdmiCompatibleInfo g_stDpHdmiCompatibleInfo;
#endif

#endif

#if(_DP_SUPPORT == _ON)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE != _DIGITAL_PORT_COMBO_PHY_ALL)
extern WORD g_usSyncDpVcoTargetCount1000RBR;
extern WORD g_usSyncDpVcoTargetCount1000HBR;
extern WORD g_usSyncDpVcoTargetCount1000HBR2;

extern WORD g_usSyncDpVcoTargetCount2000RBR;
extern WORD g_usSyncDpVcoTargetCount2000HBR;
extern WORD g_usSyncDpVcoTargetCount2000HBR2;

extern WORD g_usSyncDpCountSSTUpperBound2000RBR;
extern WORD g_usSyncDpCountSSTUpperBound2000HBR;
extern WORD g_usSyncDpCountSSTUpperBound2000HBR2;

extern WORD g_usSyncDpCountSSTLowerBound2000RBR;
extern WORD g_usSyncDpCountSSTLowerBound2000HBR;
extern WORD g_usSyncDpCountSSTLowerBound2000HBR2;

extern WORD g_usSyncDpCountMSTUpperBound2000RBR;
extern WORD g_usSyncDpCountMSTUpperBound2000HBR;
extern WORD g_usSyncDpCountMSTUpperBound2000HBR2;

extern WORD g_usSyncDpCountMSTLowerBound2000RBR;
extern WORD g_usSyncDpCountMSTLowerBound2000HBR;
extern WORD g_usSyncDpCountMSTLowerBound2000HBR2;

extern WORD g_usSyncDpCountD10P2UpperBound1000RBR;
extern WORD g_usSyncDpCountD10P2UpperBound1000HBR;
extern WORD g_usSyncDpCountD10P2UpperBound1000HBR2;

extern WORD g_usSyncDpCountD10P2LowerBound1000RBR;
extern WORD g_usSyncDpCountD10P2LowerBound1000HBR;
extern WORD g_usSyncDpCountD10P2LowerBound1000HBR2;
#endif

extern bit g_bDpMSTRx0BackupLinkStatusFlg_INT;
extern bit g_bDpMSTRx1BackupLinkStatusFlg_INT;
extern BYTE g_pucDpRx0LinkStatusBackup_INT[3];
extern BYTE g_pucDpRx1LinkStatusBackup_INT[3];
extern StructDPCapSwitchInfo g_stDpCapSwitch;
extern StructDPMarginLinkInfo g_stDpMarginLink;
extern StructDpPortHpdAssertType g_stHpdType;
extern bit g_bDpMstDCOffHPDToggleHoldFlag;
extern bit g_bDpDCOffHPDToggleFlag;
extern StructDpAuxSetting g_stDpAuxSetting;
extern BYTE g_ucDpIrqTime_10us;
extern bit g_bDpIllegalIdlePatternCheck;

#if(_D0_DP_EXIST == _ON)
extern bit g_bDpRx0HdcpCheckEnable;
#endif

#if(_D1_DP_EXIST == _ON)
extern bit g_bDpRx1HdcpCheckEnable;
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
#if(_D0_DP_EXIST == _ON)
extern bit g_bDpRx0HdcpHandshakeWOCap;
#endif
#if(_D1_DP_EXIST == _ON)
extern bit g_bDpRx1HdcpHandshakeWOCap;
#endif
#endif

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
extern volatile BYTE data g_ucDpRxHpdIrqAssertT2EventDelayXus_Counter;
extern BYTE data g_ucDpRxHpdIrqAssertT2EventDelay5usI;

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
extern volatile bit g_bDpD0HpdIrqAssertT2Event;
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
extern volatile bit g_bDpD1HpdIrqAssertT2Event;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
extern volatile bit g_bDpD2HpdIrqAssertT2Event;
#endif
#endif

#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
extern StructDPTxStatusInfo g_stDpTxStatus;
extern StructDpTxColorInfo g_stDpTxColorInfo;
#endif

#if(_FREESYNC_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
extern StructDPFREESYNCENABLE g_stDpFREESYNCInfo;
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE g_ucHDMIFREESYNCVCPReceive;
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
extern StructHDMIFREESYNCENABLE g_stHDMIFREESYNCInfo;
#endif

extern WORD g_usFREESYNCVFreq_max;
extern WORD g_usFREESYNCVFreq_min;
extern bit g_bFREESYNCSPDInfoReceive;
extern bit g_bFREESYNCGetIVFInfo;
#endif // End of #if(_FREESYNC_SUPPORT == _ON)

#if(_HDR10_SUPPORT == _ON)
extern StructHDR10Setting g_stHDR10Setting;
extern StructHDR10PortSettingInfo g_stHDR10PortSettingInfo;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
extern WORD g_usDDCDebounceCnt;

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
extern StructTmdsZ0ToggleFlag g_stTmdsToggleZ0Flag;
#endif

#endif

#if(_DP_TX_SUPPORT == _ON)
extern BYTE idata g_pucHdcpAksvBackup[5];
#endif

#if(_HDMI_SUPPORT == _ON)
extern BYTE g_pucTMDSRxAviInfo[6];
extern StructHdmiRxPsWakeupHpd g_stHdmiPsWakeupHPD;
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
extern bit g_bAIOModernStandbyMode;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
extern bit ScalerSyncGetFREESYNCEnable(void);
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
extern void ScalerSyncDpSecDataResetProc(BYTE ucInputPort);
#endif

#if(_DP_SUPPORT == _ON)
extern bit ScalerSyncDpCableStatus(EnumSourceSearchPort enumInputPort);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerSyncDpTxPowerProc(EnumPowerAction enumPowerAction);
extern EnumDPRxHDCPUpstreamAuthStatus ScalerSyncDpHdcpGetUpstreamEvent(void);
extern bit ScalerSyncDpHdcpGetUpstreamEncryptStatus(void);

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
extern bit ScalerSyncDpHdcpDownstreamReAuthCheck(void);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern EnumDpRxHdcp2UpstreamAuthStatus ScalerSyncDpHdcp2GetUpstreamEvent(void);
extern bit ScalerSyncDpHdcp2GetContentStreamManagementStatus(void);
extern bit ScalerSyncDpGetHdcp2ModeStatus(void);
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
void ScalerSyncDpRxClrSourceWritePowerUp(EnumSourceSearchPort enumInputPort);
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
extern bit ScalerSyncCheckUrgentEvent(void);
#endif

#if(_MHL_SUPPORT == _ON)
extern bit ScalerSyncMHLVBusPowerExist(void);
#endif

extern void ScalerSyncResetProc(BYTE ucInputPort);

#if(((_D0_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF)) || ((_HDMI_SUPPORT == _ON) && (_TMDS_PAGE2_COMBO_EXIST == _ON)))
extern void ScalerSyncTMDSRx0HdmiVideoSetting(void);
extern bit ScalerSyncTMDSRx0HdmiColorInfoChanged(void);
#endif

#if((_D1_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
extern void ScalerSyncTMDSRx1HdmiVideoSetting(void);
extern bit ScalerSyncTMDSRx1HdmiColorInfoChanged(void);
#endif

#if((_D2_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
extern void ScalerSyncTMDSRx2HdmiVideoSetting(void);
#endif
extern bit ScalerSyncTMDSRx2HdmiColorInfoChanged(void);
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
void ScalerSyncTMDSRx3HdmiVideoSetting(void);
#endif
extern bit ScalerSyncTMDSRx3HdmiColorInfoChanged(void);
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
void ScalerSyncTMDSRx4HdmiVideoSetting(void);
#endif
extern bit ScalerSyncTMDSRx4HdmiColorInfoChanged(void);
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
extern void ScalerSyncTMDSRx5HdmiVideoSetting(void);
extern bit ScalerSyncTMDSRx5HdmiColorInfoChanged(void);
#endif
