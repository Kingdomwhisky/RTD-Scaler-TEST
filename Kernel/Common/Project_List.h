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
// ID Code      : Project_List.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_LIST_H__
#define __PROJECT_LIST_H__

//--------------------------------------------------
//  Project Define
//--------------------------------------------------
#define _RL6193_PROJECT                                   0
#define _RL6369_PROJECT                                   1
#define _RL6410_PROJECT                                   2
#define _RL6432_PROJECT                                   3
#define _RL6449_PROJECT                                   4
#define _RLE0779_PROJECT                                  5
#define _RL6463_PROJECT                                   6
#define _RL6492_PROJECT                                   7

#define _RL6432_BEACON_PROJECT                            10

//--------------------------------------------------
//  RLxxxx Gen None Define
//--------------------------------------------------
#define _GEN_NONE                                         0xFF

//--------------------------------------------------
//  RLxxxx Input Port None Define
//--------------------------------------------------
#define _INPUT_NONE                                       0

//--------------------------------------------------
//  User Osd Architecture Define
//--------------------------------------------------
#define _USER_OSD_GEN_1                                   0
#define _USER_OSD_GEN_2                                   1
#define _USER_OSD_GEN_3                                   2

//--------------------------------------------------
//  HDCP Feature Define
//--------------------------------------------------
#define _HDCP_FEATURE_1_0                                 0
#define _HDCP_FEATURE_1_1                                 1
#define _HDCP_FEATURE_2_2                                 2
#define _HDCP_FEATURE_BY_INPUT                            3

//--------------------------------------------------
//  TMDS Z0 Option in PS Define
//--------------------------------------------------
#define _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS                0
#define _ALL_CHANNEL_CONNECTED_FOR_CTS                    1

//--------------------------------------------------
//  GDIPHY Z0 Impedance Option
//--------------------------------------------------
#define _BY_CONNECTOR                                     0
#define _LG_90_OHM                                        1 // for HDMI Port
#define _U3_90_OHM                                        2 // for DP Port

//--------------------------------------------------
//  MHL Version Define
//--------------------------------------------------
#define _MHL_VERSION_NULL                                 0x00
#define _MHL_VERSION_1_2                                  0x12
#define _MHL_VERSION_2_0                                  0x20
#define _MHL_VERSION_2_1                                  0x21
#define _MHL_VERSION_2_2                                  0x22
#define _MHL_VERSION_3_0                                  0x30
#define _MHL_VERSION_3_2                                  0x32

//--------------------------------------------------
// Definitions of eCBUS-S Sync Lost Solution
//--------------------------------------------------
#define _ECBUS_SYNC_LOST_REINIT                           0
#define _ECBUS_SYNC_LOST_RETRY                            1

//--------------------------------------------------
//  Video 8 Type Option
//--------------------------------------------------
#define _SV_ONLY                                          0
#define _AV_ONLY                                          1
#define _SV_WITH_AV                                       2
#define _AV_WITH_SV                                       3

//--------------------------------------------------
// CLUT Location Option List
//--------------------------------------------------
#define _GAMMA_LUT_LOCATION_CODE                          0
#define _GAMMA_LUT_LOCATION_FLASH                         1

//--------------------------------------------------
// Table Location Option List
//--------------------------------------------------
#define _TABLE_LOCATION_CODE                              0
#define _TABLE_LOCATION_SYSTEM_EEPROM                     1
#define _TABLE_LOCATION_FLASH                             2
#define _TABLE_LOCATION_EFUSE                             3
#define _TABLE_LOCATION_USER                              4

//--------------------------------------------------
//  Audio Options
//--------------------------------------------------
#define _PS_AUDIO_DP                                      0
#define _PS_AUDIO_LINE_IN                                 1
#define _PS_AUDIO_BOTH                                    2

//--------------------------------------------------
//  Audio DVC Mode Options
//--------------------------------------------------
#define _DB_GAIN                                          0
#define _VOLUME_STEP_SIZE                                 1

//--------------------------------------------------
//  Audio DVC DB Mode Options
//--------------------------------------------------
#define _DB_GAIN_1_DB                                     0
#define _DB_GAIN_1_2_DB                                   1
#define _DB_GAIN_1_4_DB                                   2
#define _DB_GAIN_1_8_DB                                   3

//--------------------------------------------------
//  Audio Manual Sampling Frequency Options
//--------------------------------------------------
#define _FIX_FREQ_32KHZ                                   0
#define _FIX_FREQ_44_1KHZ                                 1
#define _FIX_FREQ_48KHZ                                   2

//--------------------------------------------------
//  Audio Hard Gain Options
//--------------------------------------------------
#define _HARD_GAIN_0_DB                                   0
#define _HARD_GAIN_ADD_6_DB                               1
#define _HARD_GAIN_ADD_12_DB                              2
#define _HARD_GAIN_ADD_18_DB                              3
#define _HARD_GAIN_ADD_24_DB                              4
#define _HARD_GAIN_MINUS_6_DB                             5
#define _HARD_GAIN_MINUS_12_DB                            6
#define _HARD_GAIN_MINUS_18_DB                            7
#define _HARD_GAIN_MINUS_24_DB                            8

//--------------------------------------------------
//  DP Bit Rate
//--------------------------------------------------
#define _DP_LINK_SPEED_NONE                               0x00
#define _DP_LOW_SPEED_162MHZ                              0x06
#define _DP_HIGH_SPEED_270MHZ                             0x0A
#define _DP_HIGH_SPEED2_540MHZ                            0x14
#define _DP_HIGH_SPEED3_810MHZ                            0x1E

//--------------------------------------------------
//  DP Lane Count
//--------------------------------------------------
#define _DP_LANE_AUTO_MODE                                0
#define _DP_ONE_LANE                                      1
#define _DP_TWO_LANE                                      2
#define _DP_FOUR_LANE                                     4

//--------------------------------------------------
//  DP MST BandWidth
//--------------------------------------------------
#define _DP_MST_PBN_NO_SUPPORT                            0
#define _DP_MST_PBN_1280                                  1280
#define _DP_MST_PBN_2560                                  2560
#define _DP_MST_PBN_3840                                  3840

//--------------------------------------------------
//  Type C Ext Port Ctrl Lane Swap Option
//--------------------------------------------------
#define _TYPE_C_LANE_SWAP_BY_PORT_CTRL                    0x00
#define _TYPE_C_LANE_SWAP_BY_SCALER                       0x01

//--------------------------------------------------
//  Type C Version (HW Gen Constrain)
//--------------------------------------------------
#define _TYPE_C_VERSION_NULL                              0x00
#define _TYPE_C_VERSION_1_1                               0x01
#define _TYPE_C_VERSION_1_2                               0x02

//--------------------------------------------------
//  Power Delivery Version (HW Gen Constrain)
//--------------------------------------------------
#define _PD_VERSION_NULL                                  0x00
#define _PD_VERSION_2_0                                   0x01
#define _PD_VERSION_3_0                                   0x02

//--------------------------------------------------
//  Type C Port Type
//--------------------------------------------------
#define _TYPE_C_PORT_SRC_ONLY                             0x00
#define _TYPE_C_PORT_SNK_ONLY                             0x01
#define _TYPE_C_PORT_DRP                                  0x02

//--------------------------------------------------
//  Type C DRP Port Power Role Preference
//--------------------------------------------------
#define _TYPE_C_DRP_NO_PREFERENCE                         0x00
#define _TYPE_C_DRP_TRY_SNK                               0x01
#define _TYPE_C_DRP_TRY_SRC                               0x02

//--------------------------------------------------
//  Type C Port SRC Default Current Provide
//--------------------------------------------------
#define _TYPE_C_SRC_DEF_USB                               0x00
#define _TYPE_C_SRC_DEF_1P5A                              0x01
#define _TYPE_C_SRC_DEF_3P0A                              0x02

//--------------------------------------------------
//  Type C Port Accessry Support
//--------------------------------------------------
#define _TYPE_C_ACC_NO_SUPPORT                            0x00
#define _TYPE_C_ACC_POWER                                 0x01
#define _TYPE_C_ACC_AUDIO                                 0x02
#define _TYPE_C_ACC_AUDIO_POWER                           0x03
#define _TYPE_C_ACC_DEBUG                                 0x04
#define _TYPE_C_ACC_DEBUG_POWER                           0x05
#define _TYPE_C_ACC_DEBUG_AUDIO                           0x06
#define _TYPE_C_ACC_ALL                                   0x07

//--------------------------------------------------
//  Type C Vendor Defined Alt Mode List
//--------------------------------------------------
#define _TYPE_C_VENDOR_ALT_MODE_NONE                      0x00
#define _TYPE_C_LENOVO_ALT_MODE                           0x01
#define _TYPE_C_ACER_ALT_MODE                             0x02
#define _TYPE_C_HP_ALT_MODE                               0x03

//--------------------------------------------------
//  Type C Port SRC Default Current Provide
//--------------------------------------------------
#define _TYPE_C_SELF_POWER_ONLY                           0x00     // System Need Adaptor
#define _TYPE_C_VBUS_POWER_ONLY                           0x01     // System Has No Adaptor, Power From Vbus Only
#define _TYPE_C_SELF_AND_VBUS_POWER                       0x02     // System Works From Both Adaptor and Vbus Power

//--------------------------------------------------
//  Type C Port Vbus Protect Mode
//--------------------------------------------------
#define _VBUS_PROTECT_BY_KERNEL                           0x00
#define _VBUS_PROTECT_BY_USER                             0x01

//--------------------------------------------------
//  Type C Port USB Role
//--------------------------------------------------
#define _TYPE_C_USB_NOT_SUPPORT                           0x00
#define _TYPE_C_USB_HOST_ONLY                             0x01
#define _TYPE_C_USB_DEVICE_ONLY                           0x02
#define _TYPE_C_USB_HOST_DEVICE                           0x03

//--------------------------------------------------
//  Type C Port USB Speed
//--------------------------------------------------
#define _TYPE_C_USB_2                                     0x00
#define _TYPE_C_USB_3_GEN1                                0x01
#define _TYPE_C_USB_3_GEN2                                0x02
#define _TYPE_C_USB_BILLBOARD_ONLY                        0x03

//--------------------------------------------------
//  Type C DC Off Option
//--------------------------------------------------
#define _TYPE_C_DC_OFF_NO_FUNCTION                        0x00     // DC Off No TypeC Function (CC Pin Floating)
#define _TYPE_C_DC_OFF_POWER_BANK_CC                      0x01     // DC Off Reconnect to CC SRC-Only (Max Cur = 3.0A, No PD)
#define _TYPE_C_DC_OFF_POWER_BANK_PD                      0x02     // DC Off Reconnect to CC SRC-Only (PD but no Alt Mode)
#define _TYPE_C_DC_OFF_FULL_FUNCTION                      0x03     // DC Off Not Effect to CC / PD / Alt Mode, All Feature Remained

//--------------------------------------------------
//  HDMI2.0 HW Mode
//--------------------------------------------------
#define _HDMI_2_0_NONE                                    0
#define _HDMI_2_0_D0_D1                                   1
#define _HDMI_2_0_D2_D3_D4_D5                             2
#define _HDMI_2_0_D1_D2_D3                                3
#define _HDMI_2_0_D2_D3                                   4
#define _HDMI_2_0_D2                                      5
#define _HDMI_2_0_D1_D2                                   6

//--------------------------------------------------
//  HDCP2.2 Gen Define
//--------------------------------------------------
#define _HDCP_2_2_GEN_1                                   1
#define _HDCP_2_2_GEN_2                                   2

//--------------------------------------------------
//  HW DP RX HDCP2 Online AES Circuit Count
//--------------------------------------------------
#define _DP_RX_HDCP2_ONLINE_AES_NONE                      0
#define _DP_RX_HDCP2_ONLINE_AES_1SET                      1
#define _DP_RX_HDCP2_ONLINE_AES_2SET                      2

//--------------------------------------------------
//  Dual Link DVI HW Mode
//--------------------------------------------------
#define _DUAL_LINK_DVI_NONE                               0
#define _DUAL_LINK_DVI_D2                                 1
#define _DUAL_LINK_DVI_D4                                 2
#define _DUAL_LINK_DVI_D2_D3_D4                           3

//--------------------------------------------------
//  HW Digital Port Combo Phy Mode
//--------------------------------------------------
#define _DIGITAL_PORT_COMBO_PHY_NONE                      0
#define _DIGITAL_PORT_COMBO_PHY_ALL                       1
#define _DIGITAL_PORT_COMBO_PHY_D1_D2                     2

//--------------------------------------------------
//  TMDS Combo MAC Mode
//--------------------------------------------------
#define _TMDS_COMBO_MAC_NONE                              0
#define _TMDS_COMBO_MAC_D1_FROM_D2                        1

//--------------------------------------------------
//  Flash Clock Speed Option List
//--------------------------------------------------
#define _FLASH_LOW_SPEED                                  0
#define _FLASH_FAST_SPEED                                 1

//--------------------------------------------------
//  Flash Clock Source Option List
//--------------------------------------------------
#define _FLASH_EXT_XTAL_CLK                               0
#define _FLASH_IOSC_CLK                                   1

//---------------------------------------------------------
// OSD Type
//---------------------------------------------------------
#define _NONE_OSD                                         0
#define _REALTEK_2014_OSD                                 1
#define _BEACON_OSD                                       2

//------------------------------------------------
//  Memory Density Options
//------------------------------------------------
#define _MEMORY_DENSITY_MASK                              0x0F00
#define _MEMORY_DENSITY_1M_16                             0x0000 // 16 Mb
#define _MEMORY_DENSITY_4M_16                             0x0200 // 64 Mb
#define _MEMORY_DENSITY_16M_16                            0x0400 // 256 Mb
#define _MEMORY_DENSITY_64M_16                            0x0600 // 1 Gb
#define _MEMORY_DENSITY_128M_16                           0x0700 // 2 Gb
#define _MEMORY_DENSITY_256M_16                           0x0800 // 4 Gb

//------------------------------------------------
//  Memory Number Options
//------------------------------------------------
#define _MEMORY_NUM_MASK                                  0x00F0
#define _MEMORY_1PC                                       0x0000
#define _MEMORY_2PCS                                      0x0010

//------------------------------------------------
//  Memory Type Options
//------------------------------------------------
#define _MEMORY_TYPE_CONFIG_MASK                          0x000F
#define _NO_MEMORY                                        0x0000
#define _MEMORY_SDRAM                                     0x0001
#define _MEMORY_DDR1                                      0x0002
#define _MEMORY_DDR2                                      0x0003
#define _MEMORY_DDR3                                      0x0004

//------------------------------------------------
// Embedded Memory Size Options
//------------------------------------------------
#define _EMBEDDED_MEMORY_SIZE_NONE                        _NO_MEMORY
#define _1M_16BIT_SDRAM                                   (_MEMORY_DENSITY_1M_16 | _MEMORY_1PC | _MEMORY_SDRAM)
#define _4M_16BIT_DDR1_1PC                                (_MEMORY_DENSITY_4M_16 | _MEMORY_1PC | _MEMORY_DDR1)
#define _4M_16BIT_DDR1_2PCS                               (_MEMORY_DENSITY_4M_16 | _MEMORY_2PCS | _MEMORY_DDR1)
#define _16M_16BIT_DDR2_1PC                               (_MEMORY_DENSITY_16M_16 | _MEMORY_1PC | _MEMORY_DDR2)
#define _16M_16BIT_DDR2_2PCS                              (_MEMORY_DENSITY_16M_16 | _MEMORY_2PCS | _MEMORY_DDR2)

//------------------------------------------------
// Memory Speed
//------------------------------------------------
#define _MEMORY_SPEED_100MHZ                              100U
#define _MEMORY_SPEED_120MHZ                              120U
#define _MEMORY_SPEED_166MHZ                              166U
#define _MEMORY_SPEED_195MHZ                              195U
#define _MEMORY_SPEED_198MHZ                              198U
#define _MEMORY_SPEED_215MHZ                              215U
#define _MEMORY_SPEED_220MHZ                              220U
#define _MEMORY_SPEED_333MHZ                              333U
#define _MEMORY_SPEED_400MHZ                              400U
#define _MEMORY_SPEED_533MHZ                              533U
#define _MEMORY_SPEED_600MHZ                              600U
#define _MEMORY_SPEED_667MHZ                              667U
#define _MEMORY_SPEED_720MHZ                              720U
#define _MEMORY_SPEED_800MHZ                              800U

//--------------------------------------------------
// Memory Size
//--------------------------------------------------
#define _MEMORY_16MB                                      16U
#define _MEMORY_32MB                                      32U
#define _MEMORY_64MB                                      64U
#define _MEMORY_128MB                                     128U
#define _MEMORY_256MB                                     256U
#define _MEMORY_512MB                                     512U
#define _MEMORY_1GB                                       1024U
#define _MEMORY_2GB                                       2048U
#define _MEMORY_4GB                                       4096U

//--------------------------------------------------
// Global DB Type
//--------------------------------------------------
#define _GLOBAL_DB_GEN_I                                  0
#define _GLOBAL_DB_GEN_II                                 1
#define _GLOBAL_DB_GEN_III                                2

//-------------------------------------------------
// Display Format DB Type
//-------------------------------------------------
#define _DIS_FORMAT_DB_GEN_I                              0 // dis_v, dis_h, fixed_dvtotal, fixed_last_line
#define _DIS_FORMAT_DB_GEN_II                             1 // dis_v

//--------------------------------------------------
// Display Rotation Type
//--------------------------------------------------
#define _DISPLAY_ROTATION_GEN_I                           0 // 90, 180, 270
#define _DISPLAY_ROTATION_GEN_II                          1 // 180

//--------------------------------------------------
// M2PLL Struct Generation
//--------------------------------------------------
#define _M2PLL_STRUCT_M_N                                 0
#define _M2PLL_STRUCT_N_F                                 1

//--------------------------------------------------
// MPLL Struct Generation
//--------------------------------------------------
#define _MPLL_STRUCT_M_N                                  0
#define _MPLL_STRUCT_COMBO_M2PLL                          1

//--------------------------------------------------
// DPLL Struct Generation
//--------------------------------------------------
#define _DPLL_STRUCT_M_N                                  0
#define _DPLL_STRUCT_M_N_CASCADE_N_F                      1
#define _DPLL_STRUCT_N_F_COMBO_LVDSPLL                    2
#define _DPLL_STRUCT_N_F                                  3

//--------------------------------------------------
// PLL Edge
//--------------------------------------------------
#define _PLL_EDGE_GEN_0_DEFAULT_NEGATIVE                  0
#define _PLL_EDGE_GEN_1_DEFAULT_POSITIVE                  1

//--------------------------------------------------
// Definitions of D Domain Data Path
//--------------------------------------------------
#define _D_DOMAIN_1_PATH                                  0
#define _D_DOMAIN_2_PATH                                  1
#define _D_DOMAIN_4_PATH                                  2

//--------------------------------------------------
// OD Generation
//--------------------------------------------------
#define _OD_GEN_0                                         0
#define _OD_GEN_1                                         1
#define _OD_GEN_2                                         2

//--------------------------------------------------
// Scaling Up Generation
//--------------------------------------------------
#define _SU_GEN_0                                         0
#define _SU_GEN_1                                         1
#define _SU_GEN_2                                         2

//--------------------------------------------------
// Scaling Down Generation
//--------------------------------------------------
#define _SD_GEN_0                                         0
#define _SD_GEN_1                                         1

//--------------------------------------------------
// DCR Bit Mode
//--------------------------------------------------
#define _DCR_GEN_0_0_8BIT                                 0
#define _DCR_GEN_0_1_8BIT                                 1
#define _DCR_GEN_1_0_10BIT                                2

//--------------------------------------------------
// IAPS Generation
//--------------------------------------------------
#define _IAPS_GAIN_COMPENSATION_GEN_0                     0
#define _IAPS_GAIN_COMPENSATION_GEN_1                     1

//--------------------------------------------------
// DCC Generation
//--------------------------------------------------
#define _DCC_GEN_0                                        0
#define _DCC_GEN_1                                        1

//--------------------------------------------------
// DCC Y Bit Mode
//--------------------------------------------------
#define _DCC_Y_8BIT                                       0
#define _DCC_Y_10BIT                                      1

//--------------------------------------------------
// AUX Talk Mode LDO Voltage Generation
//--------------------------------------------------
#define _AUX_TALK_MODE_GEN_0_ADJR_0_LDO_3BIT              0
#define _AUX_TALK_MODE_GEN_1_ADJR_1_LDO_3BIT              1
#define _AUX_TALK_MODE_GEN_2_ADJR_1_LDO_4BIT              2

//--------------------------------------------------
// ICM Generation
//--------------------------------------------------
#define _ICM_GEN_0                                        0
#define _ICM_GEN_1                                        1
#define _ICM_GEN_2                                        2
#define _ICM_GEN_3                                        3

//--------------------------------------------------
// Six Color ICM TYPE
//--------------------------------------------------
#define _SIX_COLOR_ICM_NORMAL_MODE                        0
#define _SIX_COLOR_ICM_DELL_MODE                          1

//--------------------------------------------------
// Ultra Vivid Generation
//--------------------------------------------------
#define _ULTRA_VIVID_GEN_0                                0
#define _ULTRA_VIVID_GEN_1                                1
#define _ULTRA_VIVID_GEN_2                                2
#define _ULTRA_VIVID_GEN_3                                3
#define _ULTRA_VIVID_GEN_4                                4
#define _ULTRA_VIVID_GEN_5                                5

//-------------------------------------------------
// Color Conversion Generation
//-------------------------------------------------
#define _COLOR_CONVERSION_GEN_0                           0
#define _COLOR_CONVERSION_GEN_1                           1
#define _COLOR_CONVERSION_GEN_2                           2
#define _COLOR_CONVERSION_GEN_3                           3

//--------------------------------------------------
// Input Gamma Generation
//--------------------------------------------------
#define _INPUT_GAMMA_GEN_0                                0
#define _INPUT_GAMMA_GEN_1                                1

//--------------------------------------------------
// Output Gamma Generation
//--------------------------------------------------
#define _OUTPUT_GAMMA_GEN_0                               0
#define _OUTPUT_GAMMA_GEN_1                               1

//--------------------------------------------------
// 3D Gamma Calibration Generation
//--------------------------------------------------
#define _3D_GAMMA_GEN_0                                   0
#define _3D_GAMMA_GEN_1                                   1

//--------------------------------------------------
// PCM Generation
//--------------------------------------------------
#define _PCM_GEN_0                                        0
#define _PCM_GEN_1                                        1

//--------------------------------------------------
// Output Gamma Calibration Generation
//--------------------------------------------------
#define _OGC_GEN_0                                        0
#define _OGC_GEN_1                                        1

//--------------------------------------------------
// Output Gamma Calibration two result setting
//--------------------------------------------------
#define _TWO_BRI_CALIBRATION_NONE                         0
#define _TWO_BRI_CALIBRATION_DICOM_HDR                    1
#define _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR            2

//--------------------------------------------------
// IDither Generation
//--------------------------------------------------
#define _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT             0
#define _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT             1
#define _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT    2
#define _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT           3

//--------------------------------------------------
// DDither Generation
//--------------------------------------------------
#define _DDITHER_GEN_0_4BIT_DITHERTBL                     0
#define _DDITHER_GEN_1_6BIT_DITHERTBL                     1
#define _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL      2
#define _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL          3
#define _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2       4

//--------------------------------------------------
// Local Dimming Generation
//--------------------------------------------------
#define _LOCAL_DIMMING_OFF                                0
#define _LOCAL_DIMMING_GEN1                               1
#define _LOCAL_DIMMING_GEN2                               2

//--------------------------------------------------
// CtsBri Generation
//--------------------------------------------------
#define _CTS_GEN_0_8BIT                                   0
#define _CTS_GEN_1_12BIT                                  1

#define _BRI_GEN_0_8BIT                                   0
#define _BRI_GEN_1_10BIT                                  1

//--------------------------------------------------
// Multi Region Color Calibration List
//--------------------------------------------------
#define _COLOR_NONE                                       0
#define _COLOR_1_REGION                                   1
#define _COLOR_2_REGION                                   2
#define _COLOR_3_REGION                                   3

//--------------------------------------------------
// Definations of YPBPR Auto Color Method
//--------------------------------------------------
#define _YPBPR_AUTO_BY_SOURCE                             0x00
#define _YPBPR_AUTO_BY_FORMULA                            0x01

//--------------------------------------------------
// Definations of Clock Save Value
//--------------------------------------------------
#define _CLOCK_SAVE_PERCENT_VALUE                         0
#define _CLOCK_SAVE_REAL_VALUE                            1

//--------------------------------------------------
// Definitions of Auto Search Style
//--------------------------------------------------
#define _SOURCE_POLLING_IN_SEARCH_STATE                   0
#define _SOURCE_POLLING_AFTER_NOSIGNAL_STATE              1
#define _SOURCE_POLLING_ACER_STYLE                        2
#define _SOURCE_POLLING_ASUS_STYLE                        3
#define _SOURCE_POLLING_DELL_STYLE                        4
#define _SOURCE_POLLING_EIZO_STYLE                        5
#define _SOURCE_POLLING_FUJITSU_STYLE                     6

//--------------------------------------------------
// Definitions of System Eeprom Emulation Page ID
//--------------------------------------------------
#define _PAGEID_0                                         0
#define _PAGEID_1                                         1
#define _PAGEID_2                                         2
#define _PAGEID_3                                         3
#define _PAGEID_4                                         4

//--------------------------------------------------
// Definitions of MHL Audio Channel
//--------------------------------------------------
#define _MHL_AUD_2CH                                      0x01
#define _MHL_AUD_8CH                                      0x02

//--------------------------------------------------
// Option for Display Garbage Prevent
//--------------------------------------------------
#define _GARBAGE_PREVENT_BY_WATCH_DOG                     0
#define _GARBAGE_PREVENT_BY_BACKLIGHT                     1

//--------------------------------------------------
// IRDA receiver type
//--------------------------------------------------
#define _IR_OFF                                           0
#define _IR_HW_SUPPORT                                    1
#define _IR_SW_SUPPORT                                    2

//--------------------------------------------------
// Definitions of pixel shift mode
//--------------------------------------------------
#define _PIXEL_SHIFT_IN_IDOMAIN                           0
#define _PIXEL_SHIFT_IN_MDOMAIN                           1

//--------------------------------------------------
// Definitions of Momory Type
//--------------------------------------------------
#define _EXTERNAL_MEMORY                                  0
#define _EMBEDDED_MEMORY                                  1

//-------------------------------------------------
// Definitions of Flash Partition
//-------------------------------------------------
#define _FLASH_PARTITION_NONE                             0
#define _FLASH_PARTITION_BOOT                             1
#define _FLASH_PARTITION_USER                             2

//--------------------------------------------------
//  Power Flow Gen Define
//--------------------------------------------------
#define _POWER_FLOW_GEN_1                                 1
#define _POWER_FLOW_GEN_2                                 2

//--------------------------------------------------
//  GDI DFE TYPE Define
//--------------------------------------------------
#define _NONE_DFE                                         0
#define _ADAPTIVE_DFE                                     1
#define _PASSIVE_DFE                                      2

//--------------------------------------------------
//  GDI Passive DFE Fine Tune Flow
//--------------------------------------------------
#define _FINE_TUNE_DFE_BY_1_LANE                          0
#define _FINE_TUNE_DFE_BY_4_LANE                          1

//--------------------------------------------------
//  FRC TYPE Define
//--------------------------------------------------
#define _FRC_GEN_NONE                                     0
#define _FRC_GEN_0                                        1
#define _FRC_GEN_1                                        2

//--------------------------------------------------
// HS TRACKING GEN Define
//--------------------------------------------------
#define _HS_TRACKING_GEN_1                                1
#define _HS_TRACKING_GEN_2                                2

//--------------------------------------------------
// Signal Detection Measure GEN Define
//--------------------------------------------------
#define _SIGNAL_MEASURE_GEN_1                             1 // dp_xtal_cycle[4:0]
#define _SIGNAL_MEASURE_GEN_2                             2 // dp_xtal_cycle[0]

//--------------------------------------------------
// DPLL Generation Define
//--------------------------------------------------
#define _MN_DPLL_PATH1                                    1
#define _MN_DPLL_PATH2                                    0 // reg spec: path0

//--------------------------------------------------
// MPLL Generation Define
//--------------------------------------------------
#define _MN_MPLL_PATH1                                    1
#define _MN_MPLL_PATH2                                    0 // reg spec: path0

//--------------------------------------------------
// Definitions of 5400 Spec Version
//--------------------------------------------------
#define _RTS5400_SERIES_FW_SPEC_VERSION_V0D4              4 // Mapping to spec version v0.4
#define _RTS5400_SERIES_FW_SPEC_VERSION_V0D5              5 // Mapping to spec version v0.5
#define _RTS5400_SERIES_FW_SPEC_VERSION_V0D6              6 // Mapping to spec version v0.6
#define _RTS5400_SERIES_FW_SPEC_VERSION_V0D7              7 // Mapping to spec version v0.7
#define _RTS5400_SERIES_FW_SPEC_VERSION_V0D8              8 // Mapping to spec version v0.8
#define _RTS5400_SERIES_FW_SPEC_VERSION_V0D9              9 // Mapping to spec version v0.9

//--------------------------------------------------
// SMBus Arbitration Type List
//--------------------------------------------------
#define _RTS_SMBUS_ARBITRATION_NONE                       0
#define _RTS_SMBUS_ARBITRATION_DELAY_MODE                 1
#define _RTS_SMBUS_ARBITRATION_HANDSHAKE_MODE             2

//--------------------------------------------------
// Code Digital Signature Type
//--------------------------------------------------
#define _SIGNATURE_TYPE_OFF                               0
#define _SIGNATURE_TYPE_EXTERNAL                          1
#define _SIGNATURE_TYPE_INTERNAL                          2

//--------------------------------------------------
// Code Digital Signature Vendor Type
//--------------------------------------------------
#define _SIGNATURE_VENDOR_NONE                            0xFF, 0xFF, 0xFF, 0xFF // default
#define _SIGNATURE_VENDOR_HP                              0x48, 0x50, 0x51, 0xFF // "HPQ" ASCII code

//--------------------------------------------------
// HW SARADC Support and Bit Num
//--------------------------------------------------
#define _SARADC_NONE                                      0
#define _SARADC_5BIT_MSB                                  1
#define _SARADC_5BIT_LSB                                  2
#define _SARADC_8BIT                                      3

//--------------------------------------------------
// DPLL Jitter Margin
//--------------------------------------------------
#define _DPLL_NO_JITTER_MARGIN                            0
#define _DPLL_1_PERCENT_JITTER_MARGIN                     1

//--------------------------------------------------
// DP DPCD DFP Present (00005h) Set Reference Option
//--------------------------------------------------
#define _DP_MST_CAPABILITY                                0
#define _DP_TX_EXISTENCE                                  1

//--------------------------------------------------
// DP Long HPD Implementation Mode
//--------------------------------------------------
#define _DP_LONG_HPD_DELAY_MODE                           0
#define _DP_LONG_HPD_TIMEREVENT_MODE                      1

//--------------------------------------------------
// DP Aux Ref. Clk Select From
//--------------------------------------------------
#define _DP_AUX_REPLY_SEL_IOSC                            0
#define _DP_AUX_REPLY_SEL_SOURCE                          1

//--------------------------------------------------
// Vsync Delay Delay Line
//--------------------------------------------------
#define _VSYNC_DELAY_2_LINES                              0
#define _VSYNC_DELAY_4_LINES                              1
#define _VSYNC_DELAY_6_LINES                              2
#define _VSYNC_DELAY_8_LINES                              3

//--------------------------------------------------
// HW Audio Line In For ADC Front and ckt Power control
//--------------------------------------------------
#define _ADC_AFE_POWER_CONTROL_GEN_1                      0
#define _ADC_AFE_POWER_CONTROL_GEN_2                      1

//--------------------------------------------------
// Display HDR Version
//--------------------------------------------------
#define _DISPLAY_HDR_VERSION_1_0                          0
#define _DISPLAY_HDR_VERSION_1_1                          1

//--------------------------------------------------
// DP IRQ HPD Implementation Mode
//--------------------------------------------------
#define _DP_IRQ_HPD_DELAY_MODE                            0
#define _DP_IRQ_HPD_T2_MODE                               1

//--------------------------------------------------
// HW Digital Audio Frequency Detection Type
//--------------------------------------------------
#define _AUDIO_AFD_HW_MODE                                0
#define _AUDIO_AFD_FW_MODE                                1

//--------------------------------------------------
// Senser Type
//--------------------------------------------------
#define _SENSER_NONE                                      0
#define _SENSER_TSL45315                                  1
#define _SENSER_TSL2581                                   2
#define _SENSER_TSL25721                                  3
#define _SENSER_TSL45315_TSL25721                         4

//--------------------------------------------------
// Customer Type
//--------------------------------------------------
#define _CUS_DEFAULT                                      0
#define _CUS_MINDRAY                                      1  //ÂõÈð
#define _CUS_TOSHIBA                                      2  //¶«Ö¥
#define _CUS_BAISHENG                                     3  //°ÙÊ¢


#endif // End of #ifndef __PROJECT_LIST_H__
