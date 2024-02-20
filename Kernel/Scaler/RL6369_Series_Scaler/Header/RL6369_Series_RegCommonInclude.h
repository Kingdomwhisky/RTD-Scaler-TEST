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
// ID Code      : RL6369_Series_RegCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of  Control Register Address
//--------------------------------------------------

//--------------------------------------------------
// Scaling Down Control (Page 0)
//--------------------------------------------------
#define _P0_25_PT_00_V_SD_INIT_M1                                   0x00
#define _P0_25_PT_01_V_SD_FACTOR_H_M1                               0x01
#define _P0_25_PT_02_V_SD_FACTOR_M_M1                               0x02
#define _P0_25_PT_03_V_SD_FACTOR_L_M1                               0x03
#define _P0_25_PT_04_H_SD_INIT_M1                                   0x04
#define _P0_25_PT_05_H_SD_FACTOR_H_M1                               0x05
#define _P0_25_PT_06_H_SD_FACTOR_M_M1                               0x06
#define _P0_25_PT_07_H_SD_FACTOR_L_M1                               0x07


//--------------------------------------------------
// I Domain Pattern Generator (Page 0)
//--------------------------------------------------
#define _P0_25_PT_10_I_PG_CTRL_0_M1                                 0x10
#define _P0_25_PT_11_I_PG_CTRL_1_M1                                 0x11
#define _P0_25_PT_12_INITIAL_R_L_M1                                 0x12
#define _P0_25_PT_13_INITIAL_G_L_M1                                 0x13
#define _P0_25_PT_14_INITIAL_B_L_M1                                 0x14
#define _P0_25_PT_15_INITIAL_RGB_M_M1                               0x15
#define _P0_25_PT_16_INITIAL_RGB_H_M1                               0x16
#define _P0_25_PT_17_PATTERN_RESET_M1                               0x17
#define _P0_25_PT_46_SD_BIST_CTRL1_M1                               0x46
#define _P0_25_PT_47_SD_DUMMY                                       0x47


//--------------------------------------------------
// Display Format (Page 0)
//--------------------------------------------------
#define _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H                            0x00
#define _P0_2B_PT_01_DISPLAY_HOR_TOTAL_L                            0x01
#define _P0_2B_PT_02_DISPLAY_HOR_SYNC_END                           0x02
#define _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H                           0x03
#define _P0_2B_PT_04_DISPLAY_HOR_BG_STA_L                           0x04
#define _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H                          0x05
#define _P0_2B_PT_06_DISPLAY_HOR_ACT_STA_L                          0x06
#define _P0_2B_PT_07_DISPLAY_HOR_ACT_END_H                          0x07
#define _P0_2B_PT_08_DISPLAY_HOR_ACT_END_L                          0x08
#define _P0_2B_PT_09_DISPLAY_HOR_BG_END_H                           0x09
#define _P0_2B_PT_0A_DISPLAY_HOR_BG_END_L                           0x0A
#define _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H                            0x0B
#define _P0_2B_PT_0C_DISPLAY_VER_TOTAL_L                            0x0C
#define _P0_2B_PT_0D_DISPLAY_VER_SYNC_END                           0x0D
#define _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H                           0x0E
#define _P0_2B_PT_0F_DISPLAY_VER_BG_STA_L                           0x0F
#define _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H                          0x10
#define _P0_2B_PT_11_DISPLAY_VER_ACT_STA_L                          0x11
#define _P0_2B_PT_12_DISPLAY_VER_ACT_END_H                          0x12
#define _P0_2B_PT_13_DISPLAY_VER_ACT_END_L                          0x13
#define _P0_2B_PT_14_DISPLAY_VER_BG_END_H                           0x14
#define _P0_2B_PT_15_DISPLAY_VER_BG_END_L                           0x15


//--------------------------------------------------
// Display Fine Tune (Page 0)
//--------------------------------------------------
#define _P0_2B_PT_20_DISPLAY_CLOCK_FINE_TUNE                        0x20
#define _P0_2B_PT_21_OSD_REF_DEN                                    0x21
#define _P0_2B_PT_22_DUMMY_REGISTER1                                0x22
#define _P0_2B_PT_23_DUMMY_REGISTER2                                0x23
#define _P0_2B_PT_25_MN_FRAME_RATE_EN                               0x25
#define _P0_2B_PT_26_M_FOR_MN_FRAME_RATE                            0x26
#define _P0_2B_PT_27_N_FOR_MN_FRAME_RATE                            0x27
#define _P0_2B_PT_28_FREE_RUN_DVS_CNT                               0x28
#define _P0_2B_PT_29_FRAME_SYNC_DVS_FLAG                            0x29
#define _P0_2B_PT_30_FIXED_DVTOTAL_MSB                              0x30
#define _P0_2B_PT_31_FIXED_DVTOTAL_LSB                              0x31
#define _P0_2B_PT_32_FIXED_LAST_LINE_MSB                            0x32
#define _P0_2B_PT_33_FIXED_LAST_LINE_LSB                            0x33
#define _P0_2B_PT_34_TRANSIENT_DVTOTAL_MSB                          0x34
#define _P0_2B_PT_35_TRANSIENT_DVTOTAL_LSB                          0x35
#define _P0_2B_PT_36_DVS_DIFF_LOBD_MSB                              0x36
#define _P0_2B_PT_37_DVS_DIFF_LOBD_LSB                              0x37
#define _P0_2B_PT_38_DVS_DIFF_UPBD_MSB                              0x38
#define _P0_2B_PT_39_DVS_DIFF_UPBD_LSB                              0x39
#define _P0_2B_PT_40_EVEN_BIST_CTRL                                 0x40
#define _P0_2B_PT_41_EVEN_BIST_RESULT                               0x41
#define _P0_2B_PT_48_D_DOMAIN_TESTOUT                               0x48


//--------------------------------------------------
// FIFO Window (Page 0)
//--------------------------------------------------
#define _P0_31_PT_00_DISPLAY_READ_WID_BSU_H                         0x00
#define _P0_31_PT_01_DISPLAY_READ_WID_BSU_L                         0x01
#define _P0_31_PT_02_DISPLAY_READ_LEN_BSU_L                         0x02


//--------------------------------------------------
// Scaling Up Function (Page 0)
//--------------------------------------------------
#define _P0_34_PT_00_HOR_SCALE_FACTOR_H                             0x00
#define _P0_34_PT_01_HOR_SCALE_FACTOR_M                             0x01
#define _P0_34_PT_02_HOR_SCALE_FACTOR_L                             0x02
#define _P0_34_PT_03_VER_SCALE_FACTOR_H                             0x03
#define _P0_34_PT_04_VER_SCALE_FACTOR_M                             0x04
#define _P0_34_PT_05_VER_SCALE_FACTOR_L                             0x05
#define _P0_34_PT_10_HOR_FILTER_COEF_INI                            0x10
#define _P0_34_PT_11_VER_FILTER_COEF_INI                            0x11
#define _P0_34_PT_13_HOR_FILTER_COEF_INI_CONTROL                    0x13


//--------------------------------------------------
// Sync Processor Overview (Page 0)
//--------------------------------------------------
#define _P0_5D_PT_00_G_CLAMP_START                                  0x00
#define _P0_5D_PT_01_G_CLAMP_END                                    0x01
#define _P0_5D_PT_02_BR_CLAMP_START                                 0x02
#define _P0_5D_PT_03_BR_CLAMP_END                                   0x03
#define _P0_5D_PT_04_CLAMP_CTRL0                                    0x04
#define _P0_5D_PT_05_CLAMP_CTRL1                                    0x05
#define _P0_5D_PT_06_CLAMP_CTRL2                                    0x06
#define _P0_5D_PT_07_COAST_CTRL                                     0x07
#define _P0_5D_PT_08_CAPTURE_WINDOW_SETTING                         0x08
#define _P0_5D_PT_09_DETECTION_TOLERANCE_SETTING                    0x09
#define _P0_5D_PT_0A_DEVS_CAP_NUM_H                                 0x0A
#define _P0_5D_PT_0B_DEVS_CAP_NUM_L                                 0x0B
#define _P0_5D_PT_0C_HSYNC_GLITCH_COUNTER_CTRL                      0x0C
#define _P0_5D_PT_0D_G_CLAMP_START_H                                0x0D
#define _P0_5D_PT_0E_BR_CLAMP_START_H                               0x0E
#define _P0_5D_PT_0F_CLAMP_POS_H                                    0x0F
#define _P0_5D_PT_10_MACROVISIONCONTROL                             0x10
#define _P0_5D_PT_11_MACROVISIONSTARTLINEINEVENFIELD                0x11
#define _P0_5D_PT_12_MACROVISIONENDLINEINEVENFIELD                  0x12
#define _P0_5D_PT_13_MACROVISIONSTARTLINEINODDFIELD                 0x13
#define _P0_5D_PT_14_MACROVISIONENDLINEINODDFIELD                   0x14
#define _P0_5D_PT_15_MACROVISIONETECTDEBOUNCE                       0x15
#define _P0_5D_PT_18_SYNC_PROCESSOR_TEST_MODE                       0x18
#define _P0_5D_PT_19_HS_DETECT_SETTING                              0x19


//--------------------------------------------------
// Highlight window (Page 0)
//--------------------------------------------------
#define _P0_61_PT_00_HLW_HOR_START_H                                0x00
#define _P0_61_PT_01_HLW_HOR_START_L                                0x01
#define _P0_61_PT_02_HLW_HOR_END_H                                  0x02
#define _P0_61_PT_03_HLW_HOR_END_L                                  0x03
#define _P0_61_PT_04_HLW_VER_START_H                                0x04
#define _P0_61_PT_05_HLW_VER_START_L                                0x05
#define _P0_61_PT_06_HLW_VER_END_H                                  0x06
#define _P0_61_PT_07_HLW_VER_END_L                                  0x07
#define _P0_61_PT_08_HLW_BORDER_WIDTH                               0x08
#define _P0_61_PT_09_HLW_BORDER_RED                                 0x09
#define _P0_61_PT_0A_HLW_BORDER_GRN                                 0x0A
#define _P0_61_PT_0B_HLW_BORDER_BLU                                 0x0B
#define _P0_61_PT_0C_HLW_BORDER_EN                                  0x0C
#define _P0_61_PT_0D_HLW_CONTROL1                                   0x0D
#define _P0_61_PT_0E_HLW_CONTROL0                                   0x0E
#define _P0_61_PT_0F_HLW_CONTROL2                                   0x0F
#define _P0_61_PT_10_HLW_CONTROL3                                   0x10


//--------------------------------------------------
// Color Processor Control (Page 0)
//--------------------------------------------------
#define _P0_65_PT_28_SRGB_DUMMY                                     0x28


//--------------------------------------------------
// Contrast & Brightness (Page 0)
//--------------------------------------------------
#define _P0_65_PT_00_BRI_RED_COE_SETA_H                             0x00
#define _P0_65_PT_01_BRI_GRN_COE_SETA_H                             0x01
#define _P0_65_PT_02_BRI_BLU_COE_SETA_H                             0x02
#define _P0_65_PT_03_CTS_RED_COE_SETA_H                             0x03
#define _P0_65_PT_04_CTS_GRN_COE_SETA_H                             0x04
#define _P0_65_PT_05_CTS_BLU_COE_SETA_H                             0x05
#define _P0_65_PT_06_BRI_RED_COE_SETB_H                             0x06
#define _P0_65_PT_07_BRI_GRN_COE_SETB_H                             0x07
#define _P0_65_PT_08_BRI_BLU_COE_SETB_H                             0x08
#define _P0_65_PT_09_CTS_RED_COE_SETB_H                             0x09
#define _P0_65_PT_0A_CTS_GRN_COE_SETB_H                             0x0A
#define _P0_65_PT_0B_CTS_BLU_COE_SETB_H                             0x0B
#define _P0_65_PT_26_CTS_BRI_SWAP                                   0x26
#define _P0_65_PT_28_SRGB_DUMMY                                     0x28


//--------------------------------------------------
// Dithering Control (For Display Domain) (Page 0)
//--------------------------------------------------
#define _P0_69_PT_00_D_DITHER_COMMON_SET0                           0x00
#define _P0_69_PT_02_D_DITHER_COMMON_SET2                           0x02
#define _P0_69_PT_0D_D_DITHER_COMMON_CTRL2                          0x0D


//--------------------------------------------------
// Back ground color (Page 0)
//--------------------------------------------------
#define _P0_6D_PT_00_BG_COLOR_VALUE_R_M1                            0x00
#define _P0_6D_PT_01_BG_COLOR_VALUE_G_M1                            0x01
#define _P0_6D_PT_02_BG_COLOR_VALUE_B_M1                            0x02


//--------------------------------------------------
// Test Function (Page 0)
//--------------------------------------------------
#define _P0_8E_PT_00_TEST_MODE                                      0x00
#define _P0_8E_PT_01_TEST_MODE_CTRL                                 0x01
#define _P0_8E_PT_02_TST_CLK_CTRL0                                  0x02
#define _P0_8E_PT_03_TST_CLK_CTRL2                                  0x03
#define _P0_8E_PT_04_TST_CLK_CTRL3                                  0x04
#define _P0_8E_PT_05_TST_CLK_CTRL4                                  0x05
#define _P0_8E_PT_06_TST_CLK_CTRL5                                  0x06
#define _P0_8E_PT_07_TST_CLK_CTRL6                                  0x07
#define _P0_8E_PT_08_TST_CLK_CTRL7                                  0x08
#define _P0_8E_PT_09_TST_CLK_CTRL8                                  0x09
#define _P0_8E_PT_0A_TST_CLK_CTRL9                                  0x0A
#define _P0_8E_PT_0B_TST_CLK_CTRLA                                  0x0B
#define _P0_8E_PT_10_SELECT_TSTINCLOCK                              0x10
#define _P0_8E_PT_20_TESTOUT_SEL0                                   0x20
#define _P0_8E_PT_21_TESTOUT_SEL1                                   0x21
#define _P0_8E_PT_22_TESTOUT_SEL2                                   0x22
#define _P0_8E_PT_23_TESTOUT_SEL3                                   0x23
#define _P0_8E_PT_27_ADC_TEST_MODE                                  0x27
#define _P0_8E_PT_28_ADC_TEST_MODE_ADDR_MSB                         0x28
#define _P0_8E_PT_29_ADC_TEST_MODE_ADDR_LSB                         0x29
#define _P0_8E_PT_30_EMCU_EN                                        0x30


//--------------------------------------------------
// OSD Access Port (Page 0)
//--------------------------------------------------
#define _P0_92_PT_100_WIN0_ADR0_LSB                                 0x1000
#define _P0_92_PT_100_WIN0_ADR0_MSB                                 0x1001
#define _P0_92_PT_100_WIN0_ADR0_HSB                                 0x1002
#define _P0_92_PT_101_WIN0_ADR1_LSB                                 0x1010
#define _P0_92_PT_101_WIN0_ADR1_MSB                                 0x1011
#define _P0_92_PT_101_WIN0_ADR1_HSB                                 0x1012
#define _P0_92_PT_102_WIN0_ADR2_LSB                                 0x1020
#define _P0_92_PT_102_WIN0_ADR2_MSB                                 0x1021
#define _P0_92_PT_102_WIN0_ADR2_HSB                                 0x1022
#define _P0_92_PT_103_WIN0_ADR3_LSB                                 0x1030
#define _P0_92_PT_103_WIN0_ADR3_MSB                                 0x1031
#define _P0_92_PT_103_WIN0_ADR3_HSB                                 0x1032
#define _P0_92_PT_104_WIN1_ADR0_LSB                                 0x1040
#define _P0_92_PT_104_WIN1_ADR0_MSB                                 0x1041
#define _P0_92_PT_104_WIN1_ADR0_HSB                                 0x1042
#define _P0_92_PT_105_WIN1_ADR1_LSB                                 0x1050
#define _P0_92_PT_105_WIN1_ADR1_MSB                                 0x1051
#define _P0_92_PT_105_WIN1_ADR1_HSB                                 0x1052
#define _P0_92_PT_106_WIN1_ADR2_LSB                                 0x1060
#define _P0_92_PT_106_WIN1_ADR2_MSB                                 0x1061
#define _P0_92_PT_106_WIN1_ADR2_HSB                                 0x1062
#define _P0_92_PT_107_WIN1_ADR3_LSB                                 0x1070
#define _P0_92_PT_107_WIN1_ADR3_MSB                                 0x1071
#define _P0_92_PT_107_WIN1_ADR3_HSB                                 0x1072
#define _P0_92_PT_108_WIN2_ADR0_LSB                                 0x1080
#define _P0_92_PT_108_WIN2_ADR0_MSB                                 0x1081
#define _P0_92_PT_108_WIN2_ADR0_HSB                                 0x1082
#define _P0_92_PT_109_WIN2_ADR1_LSB                                 0x1090
#define _P0_92_PT_109_WIN2_ADR1_MSB                                 0x1091
#define _P0_92_PT_109_WIN2_ADR1_HSB                                 0x1092
#define _P0_92_PT_10A_WIN2_ADR2_LSB                                 0x10A0
#define _P0_92_PT_10A_WIN2_ADR2_MSB                                 0x10A1
#define _P0_92_PT_10A_WIN2_ADR2_HSB                                 0x10A2
#define _P0_92_PT_10B_WIN2_ADR3_LSB                                 0x10B0
#define _P0_92_PT_10B_WIN2_ADR3_MSB                                 0x10B1
#define _P0_92_PT_10B_WIN2_ADR3_HSB                                 0x10B2
#define _P0_92_PT_10C_WIN3_ADR0_LSB                                 0x10C0
#define _P0_92_PT_10C_WIN3_ADR0_MSB                                 0x10C1
#define _P0_92_PT_10C_WIN3_ADR0_HSB                                 0x10C2
#define _P0_92_PT_10D_WIN3_ADR1_LSB                                 0x10D0
#define _P0_92_PT_10D_WIN3_ADR1_MSB                                 0x10D1
#define _P0_92_PT_10D_WIN3_ADR1_HSB                                 0x10D2
#define _P0_92_PT_10E_WIN3_ADR2_LSB                                 0x10E0
#define _P0_92_PT_10E_WIN3_ADR2_MSB                                 0x10E1
#define _P0_92_PT_10E_WIN3_ADR2_HSB                                 0x10E2
#define _P0_92_PT_10F_WIN3_ADR3_LSB                                 0x10F0
#define _P0_92_PT_10F_WIN3_ADR3_MSB                                 0x10F1
#define _P0_92_PT_10F_WIN3_ADR3_HSB                                 0x10F2
#define _P0_92_PT_110_WIN4_ADR0_LSB                                 0x1100
#define _P0_92_PT_110_WIN4_ADR0_MSB                                 0x1101
#define _P0_92_PT_110_WIN4_ADR0_HSB                                 0x1102
#define _P0_92_PT_111_WIN4_ADR1_LSB                                 0x1110
#define _P0_92_PT_111_WIN4_ADR1_MSB                                 0x1111
#define _P0_92_PT_111_WIN4_ADR1_HSB                                 0x1112
#define _P0_92_PT_112_WIN4_ADR2_LSB                                 0x1120
#define _P0_92_PT_112_WIN4_ADR2_MSB                                 0x1121
#define _P0_92_PT_112_WIN4_ADR2_HSB                                 0x1122
#define _P0_92_PT_113_WIN4_ADR3_LSB                                 0x1130
#define _P0_92_PT_113_WIN4_ADR3_MSB                                 0x1131
#define _P0_92_PT_113_WIN4_ADR3_HSB                                 0x1132
#define _P0_92_PT_114_WIN5_ADR0_LSB                                 0x1140
#define _P0_92_PT_114_WIN5_ADR0_MSB                                 0x1141
#define _P0_92_PT_114_WIN5_ADR0_HSB                                 0x1142
#define _P0_92_PT_115_WIN5_ADR1_LSB                                 0x1150
#define _P0_92_PT_115_WIN5_ADR1_MSB                                 0x1151
#define _P0_92_PT_115_WIN5_ADR1_HSB                                 0x1152
#define _P0_92_PT_116_WIN5_ADR2_LSB                                 0x1160
#define _P0_92_PT_116_WIN5_ADR2_MSB                                 0x1161
#define _P0_92_PT_116_WIN5_ADR2_HSB                                 0x1162
#define _P0_92_PT_117_WIN5_ADR3_LSB                                 0x1170
#define _P0_92_PT_117_WIN5_ADR3_MSB                                 0x1171
#define _P0_92_PT_117_WIN5_ADR3_HSB                                 0x1172
#define _P0_92_PT_118_WIN6_ADR0_LSB                                 0x1180
#define _P0_92_PT_118_WIN6_ADR0_MSB                                 0x1181
#define _P0_92_PT_118_WIN6_ADR0_HSB                                 0x1182
#define _P0_92_PT_119_WIN6_ADR1_LSB                                 0x1190
#define _P0_92_PT_119_WIN6_ADR1_MSB                                 0x1191
#define _P0_92_PT_119_WIN6_ADR1_HSB                                 0x1192
#define _P0_92_PT_11A_WIN6_ADR2_LSB                                 0x11A0
#define _P0_92_PT_11A_WIN6_ADR2_MSB                                 0x11A1
#define _P0_92_PT_11A_WIN6_ADR2_HSB                                 0x11A2
#define _P0_92_PT_11B_WIN6_ADR3_LSB                                 0x11B0
#define _P0_92_PT_11B_WIN6_ADR3_MSB                                 0x11B1
#define _P0_92_PT_11B_WIN6_ADR3_HSB                                 0x11B2
#define _P0_92_PT_11C_WIN7_ADR0_LSB                                 0x11C0
#define _P0_92_PT_11C_WIN7_ADR0_MSB                                 0x11C1
#define _P0_92_PT_11C_WIN7_ADR0_HSB                                 0x11C2
#define _P0_92_PT_11D_WIN7_ADR1_LSB                                 0x11D0
#define _P0_92_PT_11D_WIN7_ADR1_MSB                                 0x11D1
#define _P0_92_PT_11D_WIN7_ADR1_HSB                                 0x11D2
#define _P0_92_PT_11E_WIN7_ADR2_LSB                                 0x11E0
#define _P0_92_PT_11E_WIN7_ADR2_MSB                                 0x11E1
#define _P0_92_PT_11E_WIN7_ADR2_HSB                                 0x11E2
#define _P0_92_PT_11F_WIN7_ADR3_LSB                                 0x11F0
#define _P0_92_PT_11F_WIN7_ADR3_MSB                                 0x11F1
#define _P0_92_PT_11F_WIN7_ADR3_HSB                                 0x11F2
#define _P0_92_PT_120_WIN8_ADR0_LSB                                 0x1200
#define _P0_92_PT_120_WIN8_ADR0_MSB                                 0x1201
#define _P0_92_PT_120_WIN8_ADR0_HSB                                 0x1202
#define _P0_92_PT_121_WIN8_ADR1_LSB                                 0x1210
#define _P0_92_PT_121_WIN8_ADR1_MSB                                 0x1211
#define _P0_92_PT_121_WIN8_ADR1_HSB                                 0x1212
#define _P0_92_PT_122_WIN8_ADR2_LSB                                 0x1220
#define _P0_92_PT_122_WIN8_ADR2_MSB                                 0x1221
#define _P0_92_PT_122_WIN8_ADR2_HSB                                 0x1222
#define _P0_92_PT_123_WIN8_ADR3_LSB                                 0x1230
#define _P0_92_PT_123_WIN8_ADR3_MSB                                 0x1231
#define _P0_92_PT_123_WIN8_ADR3_HSB                                 0x1232
#define _P0_92_PT_124_WIN9_ADR0_LSB                                 0x1240
#define _P0_92_PT_124_WIN9_ADR0_MSB                                 0x1241
#define _P0_92_PT_124_WIN9_ADR0_HSB                                 0x1242
#define _P0_92_PT_125_WIN9_ADR1_LSB                                 0x1250
#define _P0_92_PT_125_WIN9_ADR1_MSB                                 0x1251
#define _P0_92_PT_125_WIN9_ADR1_HSB                                 0x1252
#define _P0_92_PT_126_WIN9_ADR2_LSB                                 0x1260
#define _P0_92_PT_126_WIN9_ADR2_MSB                                 0x1261
#define _P0_92_PT_126_WIN9_ADR2_HSB                                 0x1262
#define _P0_92_PT_127_WIN9_ADR3_LSB                                 0x1270
#define _P0_92_PT_127_WIN9_ADR3_MSB                                 0x1271
#define _P0_92_PT_127_WIN9_ADR3_HSB                                 0x1272
#define _P0_92_PT_200_WIN4_1_ADR0_LSB                               0x2000
#define _P0_92_PT_200_WIN4_1_ADR0_MSB                               0x2001
#define _P0_92_PT_200_WIN4_1_ADR0_HSB                               0x2002
#define _P0_92_PT_201_WIN4_1_ADR1_LSB                               0x2010
#define _P0_92_PT_201_WIN4_1_ADR1_MSB                               0x2011
#define _P0_92_PT_201_WIN4_1_ADR1_HSB                               0x2012
#define _P0_92_PT_202_WIN4_1_ADR2_LSB                               0x2020
#define _P0_92_PT_202_WIN4_1_ADR2_MSB                               0x2021
#define _P0_92_PT_202_WIN4_1_ADR2_HSB                               0x2022
#define _P0_92_PT_203_WIN4_1_ADR3_LSB                               0x2030
#define _P0_92_PT_203_WIN4_1_ADR3_MSB                               0x2031
#define _P0_92_PT_203_WIN4_1_ADR3_HSB                               0x2032
#define _P0_92_PT_204_WIN4_2_ADR0_LSB                               0x2040
#define _P0_92_PT_204_WIN4_2_ADR0_MSB                               0x2041
#define _P0_92_PT_204_WIN4_2_ADR0_HSB                               0x2042
#define _P0_92_PT_205_WIN4_2_ADR1_LSB                               0x2050
#define _P0_92_PT_205_WIN4_2_ADR1_MSB                               0x2051
#define _P0_92_PT_205_WIN4_2_ADR1_HSB                               0x2052
#define _P0_92_PT_206_WIN4_2_ADR2_LSB                               0x2060
#define _P0_92_PT_206_WIN4_2_ADR2_MSB                               0x2061
#define _P0_92_PT_206_WIN4_2_ADR2_HSB                               0x2062
#define _P0_92_PT_207_WIN4_2_ADR3_LSB                               0x2070
#define _P0_92_PT_207_WIN4_2_ADR3_MSB                               0x2071
#define _P0_92_PT_207_WIN4_2_ADR3_HSB                               0x2072
#define _P0_92_PT_208_WIN4_3_ADR0_LSB                               0x2080
#define _P0_92_PT_208_WIN4_3_ADR0_MSB                               0x2081
#define _P0_92_PT_208_WIN4_3_ADR0_HSB                               0x2082
#define _P0_92_PT_209_WIN4_3_ADR1_LSB                               0x2090
#define _P0_92_PT_209_WIN4_3_ADR1_MSB                               0x2091
#define _P0_92_PT_209_WIN4_3_ADR1_HSB                               0x2092
#define _P0_92_PT_20A_WIN4_3_ADR2_LSB                               0x20A0
#define _P0_92_PT_20A_WIN4_3_ADR2_MSB                               0x20A1
#define _P0_92_PT_20A_WIN4_3_ADR2_HSB                               0x20A2
#define _P0_92_PT_20B_WIN4_3_ADR3_LSB                               0x20B0
#define _P0_92_PT_20B_WIN4_3_ADR3_MSB                               0x20B1
#define _P0_92_PT_20B_WIN4_3_ADR3_HSB                               0x20B2
#define _P0_92_PT_20C_WIN4_4_ADR0_LSB                               0x20C0
#define _P0_92_PT_20C_WIN4_4_ADR0_MSB                               0x20C1
#define _P0_92_PT_20C_WIN4_4_ADR0_HSB                               0x20C2
#define _P0_92_PT_20D_WIN4_4_ADR1_LSB                               0x20D0
#define _P0_92_PT_20D_WIN4_4_ADR1_MSB                               0x20D1
#define _P0_92_PT_20D_WIN4_4_ADR1_HSB                               0x20D2
#define _P0_92_PT_20E_WIN4_4_ADR2_LSB                               0x20E0
#define _P0_92_PT_20E_WIN4_4_ADR2_MSB                               0x20E1
#define _P0_92_PT_20E_WIN4_4_ADR2_HSB                               0x20E2
#define _P0_92_PT_20F_WIN4_4_ADR3_LSB                               0x20F0
#define _P0_92_PT_20F_WIN4_4_ADR3_MSB                               0x20F1
#define _P0_92_PT_20F_WIN4_4_ADR3_HSB                               0x20F2
#define _P0_92_PT_210_WIN4_5_ADR0_LSB                               0x2100
#define _P0_92_PT_210_WIN4_5_ADR0_MSB                               0x2101
#define _P0_92_PT_210_WIN4_5_ADR0_HSB                               0x2102
#define _P0_92_PT_211_WIN4_5_ADR1_LSB                               0x2110
#define _P0_92_PT_211_WIN4_5_ADR1_MSB                               0x2111
#define _P0_92_PT_211_WIN4_5_ADR1_HSB                               0x2112
#define _P0_92_PT_212_WIN4_5_ADR2_LSB                               0x2120
#define _P0_92_PT_212_WIN4_5_ADR2_MSB                               0x2121
#define _P0_92_PT_212_WIN4_5_ADR2_HSB                               0x2122
#define _P0_92_PT_213_WIN4_5_ADR3_LSB                               0x2130
#define _P0_92_PT_213_WIN4_5_ADR3_MSB                               0x2131
#define _P0_92_PT_213_WIN4_5_ADR3_HSB                               0x2132
#define _P0_92_PT_214_WIN4_6_ADR0_LSB                               0x2140
#define _P0_92_PT_214_WIN4_6_ADR0_MSB                               0x2141
#define _P0_92_PT_214_WIN4_6_ADR0_HSB                               0x2142
#define _P0_92_PT_215_WIN4_6_ADR1_LSB                               0x2150
#define _P0_92_PT_215_WIN4_6_ADR1_MSB                               0x2151
#define _P0_92_PT_215_WIN4_6_ADR1_HSB                               0x2152
#define _P0_92_PT_216_WIN4_6_ADR2_LSB                               0x2160
#define _P0_92_PT_216_WIN4_6_ADR2_MSB                               0x2161
#define _P0_92_PT_216_WIN4_6_ADR2_HSB                               0x2162
#define _P0_92_PT_217_WIN4_6_ADR3_LSB                               0x2170
#define _P0_92_PT_217_WIN4_6_ADR3_MSB                               0x2171
#define _P0_92_PT_217_WIN4_6_ADR3_HSB                               0x2172
#define _P0_92_PT_218_WIN4_7_ADR0_LSB                               0x2180
#define _P0_92_PT_218_WIN4_7_ADR0_MSB                               0x2181
#define _P0_92_PT_218_WIN4_7_ADR0_HSB                               0x2182
#define _P0_92_PT_219_WIN4_7_ADR1_LSB                               0x2190
#define _P0_92_PT_219_WIN4_7_ADR1_MSB                               0x2191
#define _P0_92_PT_219_WIN4_7_ADR1_HSB                               0x2192
#define _P0_92_PT_21A_WIN4_7_ADR2_LSB                               0x21A0
#define _P0_92_PT_21A_WIN4_7_ADR2_MSB                               0x21A1
#define _P0_92_PT_21A_WIN4_7_ADR2_HSB                               0x21A2
#define _P0_92_PT_21B_WIN4_7_ADR3_LSB                               0x21B0
#define _P0_92_PT_21B_WIN4_7_ADR3_MSB                               0x21B1
#define _P0_92_PT_21B_WIN4_7_ADR3_HSB                               0x21B2
#define _P0_92_PT_21C_WIN4_8_ADR0_LSB                               0x21C0
#define _P0_92_PT_21C_WIN4_8_ADR0_MSB                               0x21C1
#define _P0_92_PT_21C_WIN4_8_ADR0_HSB                               0x21C2
#define _P0_92_PT_21D_WIN4_8_ADR1_LSB                               0x21D0
#define _P0_92_PT_21D_WIN4_8_ADR1_MSB                               0x21D1
#define _P0_92_PT_21D_WIN4_8_ADR1_HSB                               0x21D2
#define _P0_92_PT_21E_WIN4_8_ADR2_LSB                               0x21E0
#define _P0_92_PT_21E_WIN4_8_ADR2_MSB                               0x21E1
#define _P0_92_PT_21E_WIN4_8_ADR2_HSB                               0x21E2
#define _P0_92_PT_21F_WIN4_8_ADR3_LSB                               0x21F0
#define _P0_92_PT_21F_WIN4_8_ADR3_MSB                               0x21F1
#define _P0_92_PT_21F_WIN4_8_ADR3_HSB                               0x21F2
#define _P0_92_PT_220_WIN5_1_ADR0_LSB                               0x2200
#define _P0_92_PT_220_WIN5_1_ADR0_MSB                               0x2201
#define _P0_92_PT_220_WIN5_1_ADR0_HSB                               0x2202
#define _P0_92_PT_221_WIN5_1_ADR1_LSB                               0x2210
#define _P0_92_PT_221_WIN5_1_ADR1_MSB                               0x2211
#define _P0_92_PT_221_WIN5_1_ADR1_HSB                               0x2212
#define _P0_92_PT_222_WIN5_1_ADR2_LSB                               0x2220
#define _P0_92_PT_222_WIN5_1_ADR2_MSB                               0x2221
#define _P0_92_PT_222_WIN5_1_ADR2_HSB                               0x2222
#define _P0_92_PT_223_WIN5_1_ADR3_LSB                               0x2230
#define _P0_92_PT_223_WIN5_1_ADR3_MSB                               0x2231
#define _P0_92_PT_223_WIN5_1_ADR3_HSB                               0x2232
#define _P0_92_PT_224_WIN5_2_ADR0_LSB                               0x2240
#define _P0_92_PT_224_WIN5_2_ADR0_MSB                               0x2241
#define _P0_92_PT_224_WIN5_2_ADR0_HSB                               0x2242
#define _P0_92_PT_225_WIN5_2_ADR1_LSB                               0x2250
#define _P0_92_PT_225_WIN5_2_ADR1_MSB                               0x2251
#define _P0_92_PT_225_WIN5_2_ADR1_HSB                               0x2252
#define _P0_92_PT_226_WIN5_2_ADR2_LSB                               0x2260
#define _P0_92_PT_226_WIN5_2_ADR2_MSB                               0x2261
#define _P0_92_PT_226_WIN5_2_ADR2_HSB                               0x2262
#define _P0_92_PT_227_WIN5_2_ADR3_LSB                               0x2270
#define _P0_92_PT_227_WIN5_2_ADR3_MSB                               0x2271
#define _P0_92_PT_227_WIN5_2_ADR3_HSB                               0x2272
#define _P0_92_PT_228_WIN5_3_ADR0_LSB                               0x2280
#define _P0_92_PT_228_WIN5_3_ADR0_MSB                               0x2281
#define _P0_92_PT_228_WIN5_3_ADR0_HSB                               0x2282
#define _P0_92_PT_229_WIN5_3_ADR1_LSB                               0x2290
#define _P0_92_PT_229_WIN5_3_ADR1_MSB                               0x2291
#define _P0_92_PT_229_WIN5_3_ADR1_HSB                               0x2292
#define _P0_92_PT_22A_WIN5_3_ADR2_LSB                               0x22A0
#define _P0_92_PT_22A_WIN5_3_ADR2_MSB                               0x22A1
#define _P0_92_PT_22A_WIN5_3_ADR2_HSB                               0x22A2
#define _P0_92_PT_22B_WIN5_3_ADR3_LSB                               0x22B0
#define _P0_92_PT_22B_WIN5_3_ADR3_MSB                               0x22B1
#define _P0_92_PT_22B_WIN5_3_ADR3_HSB                               0x22B2
#define _P0_92_PT_22C_WIN5_4_ADR0_LSB                               0x22C0
#define _P0_92_PT_22C_WIN5_4_ADR0_MSB                               0x22C1
#define _P0_92_PT_22C_WIN5_4_ADR0_HSB                               0x22C2
#define _P0_92_PT_22D_WIN5_4_ADR1_LSB                               0x22D0
#define _P0_92_PT_22D_WIN5_4_ADR1_MSB                               0x22D1
#define _P0_92_PT_22D_WIN5_4_ADR1_HSB                               0x22D2
#define _P0_92_PT_22E_WIN5_4_ADR2_LSB                               0x22E0
#define _P0_92_PT_22E_WIN5_4_ADR2_MSB                               0x22E1
#define _P0_92_PT_22E_WIN5_4_ADR2_HSB                               0x22E2
#define _P0_92_PT_22F_WIN5_4_ADR3_LSB                               0x22F0
#define _P0_92_PT_22F_WIN5_4_ADR3_MSB                               0x22F1
#define _P0_92_PT_22F_WIN5_4_ADR3_HSB                               0x22F2
#define _P0_92_PT_230_WIN5_5_ADR0_LSB                               0x2300
#define _P0_92_PT_230_WIN5_5_ADR0_MSB                               0x2301
#define _P0_92_PT_230_WIN5_5_ADR0_HSB                               0x2302
#define _P0_92_PT_231_WIN5_5_ADR1_LSB                               0x2310
#define _P0_92_PT_231_WIN5_5_ADR1_MSB                               0x2311
#define _P0_92_PT_231_WIN5_5_ADR1_HSB                               0x2312
#define _P0_92_PT_232_WIN5_5_ADR2_LSB                               0x2320
#define _P0_92_PT_232_WIN5_5_ADR2_MSB                               0x2321
#define _P0_92_PT_232_WIN5_5_ADR2_HSB                               0x2322
#define _P0_92_PT_233_WIN5_5_ADR3_LSB                               0x2330
#define _P0_92_PT_233_WIN5_5_ADR3_MSB                               0x2331
#define _P0_92_PT_233_WIN5_5_ADR3_HSB                               0x2332
#define _P0_92_PT_234_WIN5_6_ADR0_LSB                               0x2340
#define _P0_92_PT_234_WIN5_6_ADR0_MSB                               0x2341
#define _P0_92_PT_234_WIN5_6_ADR0_HSB                               0x2342
#define _P0_92_PT_235_WIN5_6_ADR1_LSB                               0x2350
#define _P0_92_PT_235_WIN5_6_ADR1_MSB                               0x2351
#define _P0_92_PT_235_WIN5_6_ADR1_HSB                               0x2352
#define _P0_92_PT_236_WIN5_6_ADR2_LSB                               0x2360
#define _P0_92_PT_236_WIN5_6_ADR2_MSB                               0x2361
#define _P0_92_PT_236_WIN5_6_ADR2_HSB                               0x2362
#define _P0_92_PT_237_WIN5_6_ADR3_LSB                               0x2370
#define _P0_92_PT_237_WIN5_6_ADR3_MSB                               0x2371
#define _P0_92_PT_237_WIN5_6_ADR3_HSB                               0x2372
#define _P0_92_PT_238_WIN5_7_ADR0_LSB                               0x2380
#define _P0_92_PT_238_WIN5_7_ADR0_MSB                               0x2381
#define _P0_92_PT_238_WIN5_7_ADR0_HSB                               0x2382
#define _P0_92_PT_239_WIN5_7_ADR1_LSB                               0x2390
#define _P0_92_PT_239_WIN5_7_ADR1_MSB                               0x2391
#define _P0_92_PT_239_WIN5_7_ADR1_HSB                               0x2392
#define _P0_92_PT_23A_WIN5_7_ADR2_LSB                               0x23A0
#define _P0_92_PT_23A_WIN5_7_ADR2_MSB                               0x23A1
#define _P0_92_PT_23A_WIN5_7_ADR2_HSB                               0x23A2
#define _P0_92_PT_23B_WIN5_7_ADR3_LSB                               0x23B0
#define _P0_92_PT_23B_WIN5_7_ADR3_MSB                               0x23B1
#define _P0_92_PT_23B_WIN5_7_ADR3_HSB                               0x23B2
#define _P0_92_PT_23C_WIN5_8_ADR0_LSB                               0x23C0
#define _P0_92_PT_23C_WIN5_8_ADR0_MSB                               0x23C1
#define _P0_92_PT_23C_WIN5_8_ADR0_HSB                               0x23C2
#define _P0_92_PT_23D_WIN5_8_ADR1_LSB                               0x23D0
#define _P0_92_PT_23D_WIN5_8_ADR1_MSB                               0x23D1
#define _P0_92_PT_23D_WIN5_8_ADR1_HSB                               0x23D2
#define _P0_92_PT_23E_WIN5_8_ADR2_LSB                               0x23E0
#define _P0_92_PT_23E_WIN5_8_ADR2_MSB                               0x23E1
#define _P0_92_PT_23E_WIN5_8_ADR2_HSB                               0x23E2
#define _P0_92_PT_23F_WIN5_8_ADR3_LSB                               0x23F0
#define _P0_92_PT_23F_WIN5_8_ADR3_MSB                               0x23F1
#define _P0_92_PT_23F_WIN5_8_ADR3_HSB                               0x23F2
#define _P0_92_PT_150_WIN0_ADR4_LSB                                 0x1500
#define _P0_92_PT_150_WIN0_ADR4_MSB                                 0x1501
#define _P0_92_PT_150_WIN0_ADR4_HSB                                 0x1502
#define _P0_92_PT_15A_WIN5_ADR4_LSB                                 0x15A0
#define _P0_92_PT_15A_WIN5_ADR4_MSB                                 0x15A1
#define _P0_92_PT_15A_WIN5_ADR4_HSB                                 0x15A2
#define _P0_92_PT_15C_WIN6_ADR4_LSB                                 0x15C0
#define _P0_92_PT_15C_WIN6_ADR4_MSB                                 0x15C1
#define _P0_92_PT_15C_WIN6_ADR4_HSB                                 0x15C2
#define _P0_92_PT_15E_WIN7_ADR4_LSB                                 0x15E0
#define _P0_92_PT_15E_WIN7_ADR4_MSB                                 0x15E1
#define _P0_92_PT_15E_WIN7_ADR4_HSB                                 0x15E2
#define _P0_92_PT_160_WIN8_ADR4_LSB                                 0x1600
#define _P0_92_PT_160_WIN8_ADR4_MSB                                 0x1601
#define _P0_92_PT_160_WIN8_ADR4_HSB                                 0x1602
#define _P0_92_PT_162_WIN9_ADR4_LSB                                 0x1620
#define _P0_92_PT_162_WIN9_ADR4_MSB                                 0x1621
#define _P0_92_PT_162_WIN9_ADR4_HSB                                 0x1622
#define _P0_92_PT_164_WIN4_1_ADR4_LSB                               0x1640
#define _P0_92_PT_164_WIN4_1_ADR4_MSB                               0x1641
#define _P0_92_PT_164_WIN4_1_ADR4_HSB                               0x1642
#define _P0_92_PT_166_WIN4_2_ADR4_LSB                               0x1660
#define _P0_92_PT_166_WIN4_2_ADR4_MSB                               0x1661
#define _P0_92_PT_166_WIN4_2_ADR4_HSB                               0x1662
#define _P0_92_PT_168_WIN4_3_ADR4_LSB                               0x1680
#define _P0_92_PT_168_WIN4_3_ADR4_MSB                               0x1681
#define _P0_92_PT_168_WIN4_3_ADR4_HSB                               0x1682
#define _P0_92_PT_16A_WIN4_4_ADR4_LSB                               0x16A0
#define _P0_92_PT_16A_WIN4_4_ADR4_MSB                               0x16A1
#define _P0_92_PT_16A_WIN4_4_ADR4_HSB                               0x16A2
#define _P0_92_PT_16C_WIN4_5_ADR4_LSB                               0x16C0
#define _P0_92_PT_16C_WIN4_5_ADR4_MSB                               0x16C1
#define _P0_92_PT_16C_WIN4_5_ADR4_HSB                               0x16C2
#define _P0_92_PT_16E_WIN4_6_ADR4_LSB                               0x16E0
#define _P0_92_PT_16E_WIN4_6_ADR4_MSB                               0x16E1
#define _P0_92_PT_16E_WIN4_6_ADR4_HSB                               0x16E2
#define _P0_92_PT_170_WIN4_7_ADR4_LSB                               0x1700
#define _P0_92_PT_170_WIN4_7_ADR4_MSB                               0x1701
#define _P0_92_PT_170_WIN4_7_ADR4_HSB                               0x1702
#define _P0_92_PT_172_WIN4_8_ADR4_LSB                               0x1720
#define _P0_92_PT_172_WIN4_8_ADR4_MSB                               0x1721
#define _P0_92_PT_172_WIN4_8_ADR4_HSB                               0x1722
#define _P0_92_PT_2A0_WIN5_1_ADR4_LSB                               0x2A00
#define _P0_92_PT_2A0_WIN5_1_ADR4_MSB                               0x2A01
#define _P0_92_PT_2A0_WIN5_1_ADR4_HSB                               0x2A02
#define _P0_92_PT_2AA_WIN5_2_ADR4_LSB                               0x2AA0
#define _P0_92_PT_2AA_WIN5_2_ADR4_MSB                               0x2AA1
#define _P0_92_PT_2AA_WIN5_2_ADR4_HSB                               0x2AA2
#define _P0_92_PT_2B4_WIN5_3_ADR4_LSB                               0x2B40
#define _P0_92_PT_2B4_WIN5_3_ADR4_MSB                               0x2B41
#define _P0_92_PT_2B4_WIN5_3_ADR4_HSB                               0x2B42
#define _P0_92_PT_2BE_WIN5_4_ADR4_LSB                               0x2BE0
#define _P0_92_PT_2BE_WIN5_4_ADR4_MSB                               0x2BE1
#define _P0_92_PT_2BE_WIN5_4_ADR4_HSB                               0x2BE2
#define _P0_92_PT_2C8_WIN5_5_ADR4_LSB                               0x2C80
#define _P0_92_PT_2C8_WIN5_5_ADR4_MSB                               0x2C81
#define _P0_92_PT_2C8_WIN5_5_ADR4_HSB                               0x2C82
#define _P0_92_PT_2D2_WIN5_6_ADR4_LSB                               0x2D20
#define _P0_92_PT_2D2_WIN5_6_ADR4_MSB                               0x2D21
#define _P0_92_PT_2D2_WIN5_6_ADR4_HSB                               0x2D22
#define _P0_92_PT_2DC_WIN5_7_ADR4_LSB                               0x2DC0
#define _P0_92_PT_2DC_WIN5_7_ADR4_MSB                               0x2DC1
#define _P0_92_PT_2DC_WIN5_7_ADR4_HSB                               0x2DC2
#define _P0_92_PT_2E6_WIN5_8_ADR4_LSB                               0x2E60
#define _P0_92_PT_2E6_WIN5_8_ADR4_MSB                               0x2E61
#define _P0_92_PT_2E6_WIN5_8_ADR4_HSB                               0x2E62
#define _P0_92_PT_161_WIN8_ADR5_LSB                                 0x1610
#define _P0_92_PT_161_WIN8_ADR5_MSB                                 0x1611
#define _P0_92_PT_161_WIN8_ADR5_HSB                                 0x1612
#define _P0_92_PT_163_WIN9_ADR5_LSB                                 0x1630
#define _P0_92_PT_163_WIN9_ADR5_MSB                                 0x1631
#define _P0_92_PT_163_WIN9_ADR5_HSB                                 0x1632
#define _P0_92_PT_174_WIN0_ADR6_LSB                                 0x1740
#define _P0_92_PT_174_WIN0_ADR6_MSB                                 0x1741
#define _P0_92_PT_174_WIN0_ADR6_HSB                                 0x1742
#define _P0_92_PT_197_WIN5_ADR6_LSB                                 0x1970
#define _P0_92_PT_197_WIN5_ADR6_MSB                                 0x1971
#define _P0_92_PT_197_WIN5_ADR6_HSB                                 0x1972
#define _P0_92_PT_19E_WIN6_ADR6_LSB                                 0x19E0
#define _P0_92_PT_19E_WIN6_ADR6_MSB                                 0x19E1
#define _P0_92_PT_19E_WIN6_ADR6_HSB                                 0x19E2
#define _P0_92_PT_1A5_WIN7_ADR6_LSB                                 0x1A50
#define _P0_92_PT_1A5_WIN7_ADR6_MSB                                 0x1A51
#define _P0_92_PT_1A5_WIN7_ADR6_HSB                                 0x1A52
#define _P0_92_PT_1AC_WIN8_ADR6_LSB                                 0x1AC0
#define _P0_92_PT_1AC_WIN8_ADR6_MSB                                 0x1AC1
#define _P0_92_PT_1AC_WIN8_ADR6_HSB                                 0x1AC2
#define _P0_92_PT_1B3_WIN9_ADR6_LSB                                 0x1B30
#define _P0_92_PT_1B3_WIN9_ADR6_MSB                                 0x1B31
#define _P0_92_PT_1B3_WIN9_ADR6_HSB                                 0x1B32
#define _P0_92_PT_183_WIN2_ADR7_LSB                                 0x1830
#define _P0_92_PT_183_WIN2_ADR7_MSB                                 0x1831
#define _P0_92_PT_183_WIN2_ADR7_HSB                                 0x1832
#define _P0_92_PT_184_WIN2_ADR8_LSB                                 0x1840
#define _P0_92_PT_184_WIN2_ADR8_MSB                                 0x1841
#define _P0_92_PT_184_WIN2_ADR8_HSB                                 0x1842
#define _P0_92_PT_18A_WIN3_ADR7_LSB                                 0x18A0
#define _P0_92_PT_18A_WIN3_ADR7_MSB                                 0x18A1
#define _P0_92_PT_18A_WIN3_ADR7_HSB                                 0x18A2
#define _P0_92_PT_18B_WIN3_ADR8_LSB                                 0x18B0
#define _P0_92_PT_18B_WIN3_ADR8_MSB                                 0x18B1
#define _P0_92_PT_18B_WIN3_ADR8_HSB                                 0x18B2
#define _P0_92_PT_191_WIN4_ADR7_LSB                                 0x1910
#define _P0_92_PT_191_WIN4_ADR7_MSB                                 0x1911
#define _P0_92_PT_191_WIN4_ADR7_HSB                                 0x1912
#define _P0_92_PT_192_WIN4_ADR8_LSB                                 0x1920
#define _P0_92_PT_192_WIN4_ADR8_MSB                                 0x1921
#define _P0_92_PT_192_WIN4_ADR8_HSB                                 0x1922
#define _P0_92_PT_176_WIN0_ADR8_LSB                                 0x1760
#define _P0_92_PT_176_WIN0_ADR8_MSB                                 0x1761
#define _P0_92_PT_176_WIN0_ADR8_HSB                                 0x1762
#define _P0_92_PT_199_WIN5_ADR8_LSB                                 0x1990
#define _P0_92_PT_199_WIN5_ADR8_MSB                                 0x1991
#define _P0_92_PT_199_WIN5_ADR8_HSB                                 0x1992
#define _P0_92_PT_1A0_WIN6_ADR8_LSB                                 0x1A00
#define _P0_92_PT_1A0_WIN6_ADR8_MSB                                 0x1A01
#define _P0_92_PT_1A0_WIN6_ADR8_HSB                                 0x1A02
#define _P0_92_PT_1A7_WIN7_ADR8_LSB                                 0x1A70
#define _P0_92_PT_1A7_WIN7_ADR8_MSB                                 0x1A71
#define _P0_92_PT_1A7_WIN7_ADR8_HSB                                 0x1A72
#define _P0_92_PT_1AE_WIN8_ADR8_LSB                                 0x1AE0
#define _P0_92_PT_1AE_WIN8_ADR8_MSB                                 0x1AE1
#define _P0_92_PT_1AE_WIN8_ADR8_HSB                                 0x1AE2
#define _P0_92_PT_1B5_WIN9_ADR8_LSB                                 0x1B50
#define _P0_92_PT_1B5_WIN9_ADR8_MSB                                 0x1B51
#define _P0_92_PT_1B5_WIN9_ADR8_HSB                                 0x1B52
#define _P0_92_PT_177_WIN0_ADR9_LSB                                 0x1770
#define _P0_92_PT_177_WIN0_ADR9_MSB                                 0x1771
#define _P0_92_PT_177_WIN0_ADR9_HSB                                 0x1772
#define _P0_92_PT_17E_WIN1_ADR9_LSB                                 0x17E0
#define _P0_92_PT_17E_WIN1_ADR9_MSB                                 0x17E1
#define _P0_92_PT_17E_WIN1_ADR9_HSB                                 0x17E2
#define _P0_92_PT_185_WIN2_ADR9_LSB                                 0x1850
#define _P0_92_PT_185_WIN2_ADR9_MSB                                 0x1851
#define _P0_92_PT_185_WIN2_ADR9_HSB                                 0x1852
#define _P0_92_PT_18C_WIN3_ADR9_LSB                                 0x18C0
#define _P0_92_PT_18C_WIN3_ADR9_MSB                                 0x18C1
#define _P0_92_PT_18C_WIN3_ADR9_HSB                                 0x18C2
#define _P0_92_PT_193_WIN4_ADR9_LSB                                 0x1930
#define _P0_92_PT_193_WIN4_ADR9_MSB                                 0x1931
#define _P0_92_PT_193_WIN4_ADR9_HSB                                 0x1932
#define _P0_92_PT_19A_WIN5_ADR9_LSB                                 0x19A0
#define _P0_92_PT_19A_WIN5_ADR9_MSB                                 0x19A1
#define _P0_92_PT_19A_WIN5_ADR9_HSB                                 0x19A2
#define _P0_92_PT_1A1_WIN6_ADR9_LSB                                 0x1A10
#define _P0_92_PT_1A1_WIN6_ADR9_MSB                                 0x1A11
#define _P0_92_PT_1A1_WIN6_ADR9_HSB                                 0x1A12
#define _P0_92_PT_1A8_WIN7_ADR9_LSB                                 0x1A80
#define _P0_92_PT_1A8_WIN7_ADR9_MSB                                 0x1A81
#define _P0_92_PT_1A8_WIN7_ADR9_HSB                                 0x1A82
#define _P0_92_PT_1AF_WIN8_ADR9_LSB                                 0x1AF0
#define _P0_92_PT_1AF_WIN8_ADR9_MSB                                 0x1AF1
#define _P0_92_PT_1AF_WIN8_ADR9_HSB                                 0x1AF2
#define _P0_92_PT_1B6_WIN9_ADR9_LSB                                 0x1B60
#define _P0_92_PT_1B6_WIN9_ADR9_MSB                                 0x1B61
#define _P0_92_PT_1B6_WIN9_ADR9_HSB                                 0x1B62
#define _P0_92_PT_1BD_WIN4_1_ADR9_LSB                               0x1BD0
#define _P0_92_PT_1BD_WIN4_1_ADR9_MSB                               0x1BD1
#define _P0_92_PT_1BD_WIN4_1_ADR9_HSB                               0x1BD2
#define _P0_92_PT_1C4_WIN4_2_ADR9_LSB                               0x1C40
#define _P0_92_PT_1C4_WIN4_2_ADR9_MSB                               0x1C41
#define _P0_92_PT_1C4_WIN4_2_ADR9_HSB                               0x1C42
#define _P0_92_PT_1CB_WIN4_3_ADR9_LSB                               0x1CB0
#define _P0_92_PT_1CB_WIN4_3_ADR9_MSB                               0x1CB1
#define _P0_92_PT_1CB_WIN4_3_ADR9_HSB                               0x1CB2
#define _P0_92_PT_1D2_WIN4_4_ADR9_LSB                               0x1D20
#define _P0_92_PT_1D2_WIN4_4_ADR9_MSB                               0x1D21
#define _P0_92_PT_1D2_WIN4_4_ADR9_HSB                               0x1D22
#define _P0_92_PT_1D9_WIN4_5_ADR9_LSB                               0x1D90
#define _P0_92_PT_1D9_WIN4_5_ADR9_MSB                               0x1D91
#define _P0_92_PT_1D9_WIN4_5_ADR9_HSB                               0x1D92
#define _P0_92_PT_1E0_WIN4_6_ADR9_LSB                               0x1E00
#define _P0_92_PT_1E0_WIN4_6_ADR9_MSB                               0x1E01
#define _P0_92_PT_1E0_WIN4_6_ADR9_HSB                               0x1E02
#define _P0_92_PT_1E7_WIN4_7_ADR9_LSB                               0x1E70
#define _P0_92_PT_1E7_WIN4_7_ADR9_MSB                               0x1E71
#define _P0_92_PT_1E7_WIN4_7_ADR9_HSB                               0x1E72
#define _P0_92_PT_1EE_WIN4_8_ADR9_LSB                               0x1EE0
#define _P0_92_PT_1EE_WIN4_8_ADR9_MSB                               0x1EE1
#define _P0_92_PT_1EE_WIN4_8_ADR9_HSB                               0x1EE2
#define _P0_92_PT_2A5_WIN5_1_ADR9_LSB                               0x2A50
#define _P0_92_PT_2A5_WIN5_1_ADR9_MSB                               0x2A51
#define _P0_92_PT_2A5_WIN5_1_ADR9_HSB                               0x2A52
#define _P0_92_PT_2AF_WIN5_2_ADR9_LSB                               0x2AF0
#define _P0_92_PT_2AF_WIN5_2_ADR9_MSB                               0x2AF1
#define _P0_92_PT_2AF_WIN5_2_ADR9_HSB                               0x2AF2
#define _P0_92_PT_2B9_WIN5_3_ADR9_LSB                               0x2B90
#define _P0_92_PT_2B9_WIN5_3_ADR9_MSB                               0x2B91
#define _P0_92_PT_2B9_WIN5_3_ADR9_HSB                               0x2B92
#define _P0_92_PT_2C3_WIN5_4_ADR9_LSB                               0x2C30
#define _P0_92_PT_2C3_WIN5_4_ADR9_MSB                               0x2C31
#define _P0_92_PT_2C3_WIN5_4_ADR9_HSB                               0x2C32
#define _P0_92_PT_2CD_WIN5_5_ADR9_LSB                               0x2CD0
#define _P0_92_PT_2CD_WIN5_5_ADR9_MSB                               0x2CD1
#define _P0_92_PT_2CD_WIN5_5_ADR9_HSB                               0x2CD2
#define _P0_92_PT_2D7_WIN5_6_ADR9_LSB                               0x2D70
#define _P0_92_PT_2D7_WIN5_6_ADR9_MSB                               0x2D71
#define _P0_92_PT_2D7_WIN5_6_ADR9_HSB                               0x2D72
#define _P0_92_PT_2E1_WIN5_7_ADR9_LSB                               0x2E10
#define _P0_92_PT_2E1_WIN5_7_ADR9_MSB                               0x2E11
#define _P0_92_PT_2E1_WIN5_7_ADR9_HSB                               0x2E12
#define _P0_92_PT_2EB_WIN5_8_ADR9_LSB                               0x2EB0
#define _P0_92_PT_2EB_WIN5_8_ADR9_MSB                               0x2EB1
#define _P0_92_PT_2EB_WIN5_8_ADR9_HSB                               0x2EB2
#define _P0_92_PT_178_WIN0_ADR10_LSB                                0x1780
#define _P0_92_PT_178_WIN0_ADR10_MSB                                0x1781
#define _P0_92_PT_178_WIN0_ADR10_HSB                                0x1782
#define _P0_92_PT_19B_WIN5_ADR10_LSB                                0x19B0
#define _P0_92_PT_19B_WIN5_ADR10_MSB                                0x19B1
#define _P0_92_PT_19B_WIN5_ADR10_HSB                                0x19B2
#define _P0_92_PT_1BE_WIN4_1_ADR10_LSB                              0x1BE0
#define _P0_92_PT_1BE_WIN4_1_ADR10_MSB                              0x1BE1
#define _P0_92_PT_1BE_WIN4_1_ADR10_HSB                              0x1BE2
#define _P0_92_PT_1C5_WIN4_2_ADR10_LSB                              0x1C50
#define _P0_92_PT_1C5_WIN4_2_ADR10_MSB                              0x1C51
#define _P0_92_PT_1C5_WIN4_2_ADR10_HSB                              0x1C52
#define _P0_92_PT_1CC_WIN4_3_ADR10_LSB                              0x1CC0
#define _P0_92_PT_1CC_WIN4_3_ADR10_MSB                              0x1CC1
#define _P0_92_PT_1CC_WIN4_3_ADR10_HSB                              0x1CC2
#define _P0_92_PT_1D3_WIN4_4_ADR10_LSB                              0x1D30
#define _P0_92_PT_1D3_WIN4_4_ADR10_MSB                              0x1D31
#define _P0_92_PT_1D3_WIN4_4_ADR10_HSB                              0x1D32
#define _P0_92_PT_1DA_WIN4_5_ADR10_LSB                              0x1DA0
#define _P0_92_PT_1DA_WIN4_5_ADR10_MSB                              0x1DA1
#define _P0_92_PT_1DA_WIN4_5_ADR10_HSB                              0x1DA2
#define _P0_92_PT_1E1_WIN4_6_ADR10_LSB                              0x1E10
#define _P0_92_PT_1E1_WIN4_6_ADR10_MSB                              0x1E11
#define _P0_92_PT_1E1_WIN4_6_ADR10_HSB                              0x1E12
#define _P0_92_PT_1E8_WIN4_7_ADR10_LSB                              0x1E80
#define _P0_92_PT_1E8_WIN4_7_ADR10_MSB                              0x1E81
#define _P0_92_PT_1E8_WIN4_7_ADR10_HSB                              0x1E82
#define _P0_92_PT_1EF_WIN4_8_ADR10_LSB                              0x1EF0
#define _P0_92_PT_1EF_WIN4_8_ADR10_MSB                              0x1EF1
#define _P0_92_PT_1EF_WIN4_8_ADR10_HSB                              0x1EF2
#define _P0_92_PT_2A6_WIN5_1_ADR10_LSB                              0x2A60
#define _P0_92_PT_2A6_WIN5_1_ADR10_MSB                              0x2A61
#define _P0_92_PT_2A6_WIN5_1_ADR10_HSB                              0x2A62
#define _P0_92_PT_2B0_WIN5_2_ADR10_LSB                              0x2B00
#define _P0_92_PT_2B0_WIN5_2_ADR10_MSB                              0x2B01
#define _P0_92_PT_2B0_WIN5_2_ADR10_HSB                              0x2B02
#define _P0_92_PT_2BA_WIN5_3_ADR10_LSB                              0x2BA0
#define _P0_92_PT_2BA_WIN5_3_ADR10_MSB                              0x2BA1
#define _P0_92_PT_2BA_WIN5_3_ADR10_HSB                              0x2BA2
#define _P0_92_PT_2C4_WIN5_4_ADR10_LSB                              0x2C40
#define _P0_92_PT_2C4_WIN5_4_ADR10_MSB                              0x2C41
#define _P0_92_PT_2C4_WIN5_4_ADR10_HSB                              0x2C42
#define _P0_92_PT_2CE_WIN5_5_ADR10_LSB                              0x2CE0
#define _P0_92_PT_2CE_WIN5_5_ADR10_MSB                              0x2CE1
#define _P0_92_PT_2CE_WIN5_5_ADR10_HSB                              0x2CE2
#define _P0_92_PT_2D8_WIN5_6_ADR10_LSB                              0x2D80
#define _P0_92_PT_2D8_WIN5_6_ADR10_MSB                              0x2D81
#define _P0_92_PT_2D8_WIN5_6_ADR10_HSB                              0x2D82
#define _P0_92_PT_2E2_WIN5_7_ADR10_LSB                              0x2E20
#define _P0_92_PT_2E2_WIN5_7_ADR10_MSB                              0x2E21
#define _P0_92_PT_2E2_WIN5_7_ADR10_HSB                              0x2E22
#define _P0_92_PT_2EC_WIN5_8_ADR10_LSB                              0x2EC0
#define _P0_92_PT_2EC_WIN5_8_ADR10_MSB                              0x2EC1
#define _P0_92_PT_2EC_WIN5_8_ADR10_HSB                              0x2EC2


//--------------------------------------------------
// Digital Filter (Page 0)
//--------------------------------------------------
#define _P0_99_PT_01_DIGITAL_PHASE_CTRL                             0x01
#define _P0_99_PT_02_DIGITAL_NEGATIVE_SMEAR_CTRL                    0x02
#define _P0_99_PT_03_DIGITAL_POSITIVE_SMEAR_CTRL                    0x03
#define _P0_99_PT_04_DIGITAL_NEGATIVE_RINGING_CTRL                  0x04
#define _P0_99_PT_05_DIGITAL_POSITIVE_RINGING_CTRL                  0x05
#define _P0_99_PT_06_DIGITAL_MISMATCH_CTRL                          0x06
#define _P0_99_PT_07_DIGITAL_COLOR_CTRL                             0x07
#define _P0_99_PT_08_DIGITAL_NOISE_CTRL                             0x08
#define _P0_99_PT_09_DIGITAL_OLD_PHASE_THD                          0x09
#define _P0_99_PT_01_DIGITAL_NEW_PHASE_CTRL                         0x01
#define _P0_99_PT_02_DIGITAL_NEW_PHASE_THD1_R                       0x02
#define _P0_99_PT_03_DIGITAL_NEW_PHASE_THD_OFF_R                    0x03
#define _P0_99_PT_04_DIGITAL_NEW_PHASE_GAIN_R                       0x04
#define _P0_99_PT_05_DIGITAL_NEW_PHASE_THD1_G                       0x05
#define _P0_99_PT_06_DIGITAL_NEW_PHASE_THD_OFF_G                    0x06
#define _P0_99_PT_07_DIGITAL_NEW_PHASE_GAIN_G                       0x07
#define _P0_99_PT_08_DIGITAL_NEW_PHASE_THD1_B                       0x08
#define _P0_99_PT_09_DIGITAL_NEW_PHASE_THD_OFF_B                    0x09
#define _P0_99_PT_0A_DIGITAL_NEW_PHASE_GAIN_B                       0x0A


//--------------------------------------------------
// Color Conversion - RGBtoYCC 10bit In / 10bit Out (Page 0)
//--------------------------------------------------
#define _P0_9D_PT_00_H00_HIGH_BYTE                                  0x00
#define _P0_9D_PT_01_H00_LOW_BYTE                                   0x01
#define _P0_9D_PT_02_H01_HIGH_BYTE                                  0x02
#define _P0_9D_PT_03_H01_LOW_BYTE                                   0x03
#define _P0_9D_PT_04_H02_HIGH_BYTE                                  0x04
#define _P0_9D_PT_05_H02_LOW_BYTE                                   0x05
#define _P0_9D_PT_06_H10_HIGH_BYTE                                  0x06
#define _P0_9D_PT_07_H10_LOW_BYTE                                   0x07
#define _P0_9D_PT_08_H11_HIGH_BYTE                                  0x08
#define _P0_9D_PT_09_H11_LOW_BYTE                                   0x09
#define _P0_9D_PT_0A_H12_HIGH_BYTE                                  0x0A
#define _P0_9D_PT_0B_H12_LOW_BYTE                                   0x0B
#define _P0_9D_PT_0C_H20_HIGH_BYTE                                  0x0C
#define _P0_9D_PT_0D_H20_LOW_BYTE                                   0x0D
#define _P0_9D_PT_0E_H21_HIGH_BYTE                                  0x0E
#define _P0_9D_PT_0F_H21_LOW_BYTE                                   0x0F
#define _P0_9D_PT_10_H22_HIGH_BYTE                                  0x10
#define _P0_9D_PT_11_H22_LOW_BYTE                                   0x11


//--------------------------------------------------
// HDMI2.0 Function (Page 2)
//--------------------------------------------------
#define _P2_3A_PT_01_PORT_PAGE2_HDMI_SCDC_01                        0x01
#define _P2_3A_PT_02_PORT_PAGE2_HDMI_SCDC_02                        0x02
#define _P2_3A_PT_10_PORT_PAGE2_HDMI_SCDC_10                        0x10
#define _P2_3A_PT_11_PORT_PAGE2_HDMI_SCDC_11                        0x11
#define _P2_3A_PT_20_PORT_PAGE2_HDMI_SCDC_20                        0x20
#define _P2_3A_PT_21_PORT_PAGE2_HDMI_SCDC_21                        0x21
#define _P2_3A_PT_30_PORT_PAGE2_HDMI_SCDC_30                        0x30
#define _P2_3A_PT_40_PORT_PAGE2_HDMI_SCDC_40                        0x40
#define _P2_3A_PT_41_PORT_PAGE2_HDMI_SCDC_41                        0x41
#define _P2_3A_PT_50_PORT_PAGE2_HDMI_SCDC_50                        0x50
#define _P2_3A_PT_51_PORT_PAGE2_HDMI_SCDC_51                        0x51
#define _P2_3A_PT_52_PORT_PAGE2_HDMI_SCDC_52                        0x52
#define _P2_3A_PT_53_PORT_PAGE2_HDMI_SCDC_53                        0x53
#define _P2_3A_PT_54_PORT_PAGE2_HDMI_SCDC_54                        0x54
#define _P2_3A_PT_55_PORT_PAGE2_HDMI_SCDC_55                        0x55
#define _P2_3A_PT_56_PORT_PAGE2_HDMI_SCDC_56                        0x56
#define _P2_3A_PT_C0_PORT_PAGE2_HDMI_SCDC_C0                        0xC0
#define _P2_3A_PT_D0_PORT_PAGE2_HDMI_SCDC_D0                        0xD0
#define _P2_3A_PT_D1_PORT_PAGE2_HDMI_SCDC_D1                        0xD1
#define _P2_3A_PT_D2_PORT_PAGE2_HDMI_SCDC_D2                        0xD2
#define _P2_3A_PT_D3_PORT_PAGE2_HDMI_SCDC_D3                        0xD3
#define _P2_3A_PT_D4_PORT_PAGE2_HDMI_SCDC_D4                        0xD4
#define _P2_3A_PT_D5_PORT_PAGE2_HDMI_SCDC_D5                        0xD5
#define _P2_3A_PT_D6_PORT_PAGE2_HDMI_SCDC_D6                        0xD6
#define _P2_3A_PT_D7_PORT_PAGE2_HDMI_SCDC_D7                        0xD7
#define _P2_3A_PT_D8_PORT_PAGE2_HDMI_SCDC_D8                        0xD8
#define _P2_3A_PT_D9_PORT_PAGE2_HDMI_SCDC_D9                        0xD9
#define _P2_3A_PT_DA_PORT_PAGE2_HDMI_SCDC_DA                        0xDA
#define _P2_3A_PT_DB_PORT_PAGE2_HDMI_SCDC_DB                        0xDB
#define _P2_3A_PT_DC_PORT_PAGE2_HDMI_SCDC_DC                        0xDC
#define _P2_3A_PT_DD_PORT_PAGE2_HDMI_SCDC_DD                        0xDD
#define _P2_3A_PT_DE_PORT_PAGE2_HDMI_SCDC_DE                        0xDE
#define _P2_3A_PT_DF_PORT_PAGE2_HDMI_SCDC_DF                        0xDF
#define _P2_3A_PT_E0_PORT_PAGE2_HDMI_SCDC_E0                        0xE0
#define _P2_3A_PT_E1_PORT_PAGE2_HDMI_SCDC_E1                        0xE1
#define _P2_3A_PT_E2_PORT_PAGE2_HDMI_SCDC_E2                        0xE2
#define _P2_3A_PT_E3_PORT_PAGE2_HDMI_SCDC_E3                        0xE3
#define _P2_3A_PT_E4_PORT_PAGE2_HDMI_SCDC_E4                        0xE4
#define _P2_3A_PT_E5_PORT_PAGE2_HDMI_SCDC_E5                        0xE5
#define _P2_3A_PT_E6_PORT_PAGE2_HDMI_SCDC_E6                        0xE6
#define _P2_3A_PT_E7_PORT_PAGE2_HDMI_SCDC_E7                        0xE7
#define _P2_3A_PT_E8_PORT_PAGE2_HDMI_SCDC_E8                        0xE8
#define _P2_3A_PT_E9_PORT_PAGE2_HDMI_SCDC_E9                        0xE9
#define _P2_3A_PT_EA_PORT_PAGE2_HDMI_SCDC_EA                        0xEA
#define _P2_3A_PT_EB_PORT_PAGE2_HDMI_SCDC_EB                        0xEB
#define _P2_3A_PT_EC_PORT_PAGE2_HDMI_SCDC_EC                        0xEC
#define _P2_3A_PT_ED_PORT_PAGE2_HDMI_SCDC_ED                        0xED
#define _P2_3A_PT_EE_PORT_PAGE2_HDMI_SCDC_EE                        0xEE
#define _P2_3A_PT_EF_PORT_PAGE2_HDMI_SCDC_EF                        0xEF
#define _P2_3A_PT_F0_PORT_PAGE2_HDMI_SCDC_F0                        0xF0
#define _P2_3A_PT_F1_PORT_PAGE2_HDMI_SCDC_F1                        0xF1
#define _P2_3A_PT_F2_PORT_PAGE2_HDMI_SCDC_F2                        0xF2
#define _P2_3A_PT_F3_PORT_PAGE2_HDMI_SCDC_F3                        0xF3
#define _P2_3A_PT_F4_PORT_PAGE2_HDMI_SCDC_F4                        0xF4
#define _P2_3A_PT_F5_PORT_PAGE2_HDMI_SCDC_F5                        0xF5
#define _P2_3A_PT_F6_PORT_PAGE2_HDMI_SCDC_F6                        0xF6
#define _P2_3A_PT_F7_PORT_PAGE2_HDMI_SCDC_F7                        0xF7
#define _P2_3A_PT_F8_PORT_PAGE2_HDMI_SCDC_F8                        0xF8
#define _P2_3A_PT_F9_PORT_PAGE2_HDMI_SCDC_F9                        0xF9
#define _P2_3A_PT_FA_PORT_PAGE2_HDMI_SCDC_FA                        0xFA
#define _P2_3A_PT_FB_PORT_PAGE2_HDMI_SCDC_FB                        0xFB
#define _P2_3A_PT_FC_PORT_PAGE2_HDMI_SCDC_FC                        0xFC
#define _P2_3A_PT_FD_PORT_PAGE2_HDMI_SCDC_FD                        0xFD
#define _P2_3A_PT_FE_PORT_PAGE2_HDMI_SCDC_FE                        0xFE
#define _P2_3A_PT_FF_PORT_PAGE2_HDMI_SCDC_FF                        0xFF
#define _P2_C4_PT_00_PORT_PAGE2_BKSV0                               0x00
#define _P2_C4_PT_01_PORT_PAGE2_BKSV1                               0x01
#define _P2_C4_PT_02_PORT_PAGE2_BKSV2                               0x02
#define _P2_C4_PT_03_PORT_PAGE2_BKSV3                               0x03
#define _P2_C4_PT_04_PORT_PAGE2_BKSV4                               0x04
#define _P2_C4_PT_08_PORT_PAGE2_RI0                                 0x08
#define _P2_C4_PT_09_PORT_PAGE2_RI1                                 0x09
#define _P2_C4_PT_0A_PORT_PAGE2_PJ                                  0x0A
#define _P2_C4_PT_10_PORT_PAGE2_AKSV0                               0x10
#define _P2_C4_PT_11_PORT_PAGE2_AKSV1                               0x11
#define _P2_C4_PT_12_PORT_PAGE2_AKSV2                               0x12
#define _P2_C4_PT_13_PORT_PAGE2_AKSV3                               0x13
#define _P2_C4_PT_14_PORT_PAGE2_AKSV4                               0x14
#define _P2_C4_PT_15_PORT_PAGE2_AINFO                               0x15
#define _P2_C4_PT_18_PORT_PAGE2_AN0                                 0x18
#define _P2_C4_PT_19_PORT_PAGE2_AN1                                 0x19
#define _P2_C4_PT_1A_PORT_PAGE2_AN2                                 0x1A
#define _P2_C4_PT_1B_PORT_PAGE2_AN3                                 0x1B
#define _P2_C4_PT_1C_PORT_PAGE2_AN4                                 0x1C
#define _P2_C4_PT_1D_PORT_PAGE2_AN5                                 0x1D
#define _P2_C4_PT_1E_PORT_PAGE2_AN6                                 0x1E
#define _P2_C4_PT_1F_PORT_PAGE2_AN7                                 0x1F
#define _P2_C4_PT_40_PORT_PAGE2_BCAPS                               0x40
#define _P2_C4_PT_41_PORT_PAGE2_BSTATUS                             0x41
#define _P2_C4_PT_43_PORT_PAGE2_KSV_FIFO                            0x43
#define _P2_C4_PT_C0_PORT_PAGE2_HDCP_FCR                            0xC0
#define _P2_C4_PT_C1_PORT_PAGE2_HDCP_SIR                            0xC1
#define _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD                      0xC2
#define _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR                            0x00
#define _P2_CA_PT_01_PORT_PAGE2_HDMI_N_VAL                          0x01
#define _P2_CA_PT_02_PORT_PAGE2_HDMI_BCHCR                          0x02
#define _P2_CA_PT_03_PORT_PAGE2_HDMI_AFCR                           0x03
#define _P2_CA_PT_04_PORT_PAGE2_HDMI_AFSR                           0x04
#define _P2_CA_PT_05_PORT_PAGE2_HDMI_MAGCR1                         0x05
#define _P2_CA_PT_06_PORT_PAGE2_HDMI_MAGCR2                         0x06
#define _P2_CA_PT_07_PORT_PAGE2_HDMI_MAG_M_FINAL                    0x07
#define _P2_CA_PT_08_PORT_PAGE2_HDMI_MAG_L_FINAL                    0x08
#define _P2_CA_PT_09_PORT_PAGE2_HDMI_MAG_R_FINAL                    0x09
#define _P2_CA_PT_0A_PORT_PAGE2_AUDIO_LD_P_TIME_M                   0x0A
#define _P2_CA_PT_0B_PORT_PAGE2_AUDIO_LD_P_TIME_N                   0x0B
#define _P2_CA_PT_0C_PORT_PAGE2_ZCD_CTRL                            0x0C
#define _P2_CA_PT_0D_PORT_PAGE2_ZCD_TIMEOUT                         0x0D
#define _P2_CA_PT_0E_PORT_PAGE2_ZCD_STATUS                          0x0E
#define _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR                           0x10
#define _P2_CA_PT_11_PORT_PAGE2_HDMI_MCAPR                          0x11
#define _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR                          0x12
#define _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0                         0x13
#define _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1                         0x14
#define _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR                           0x15
#define _P2_CA_PT_16_PORT_PAGE2_HDMI_FDDR                           0x16
#define _P2_CA_PT_17_PORT_PAGE2_HDMI_FDDF                           0x17
#define _P2_CA_PT_18_PORT_PAGE2_HDMI_MFDDR                          0x18
#define _P2_CA_PT_19_PORT_PAGE2_HDMI_MFDDF                          0x19
#define _P2_CA_PT_1A_PORT_PAGE2_HDMI_FTR                            0x1A
#define _P2_CA_PT_1B_PORT_PAGE2_HDMI_FBR                            0x1B
#define _P2_CA_PT_1C_PORT_PAGE2_HDMI_ICPSNCR0                       0x1C
#define _P2_CA_PT_1D_PORT_PAGE2_HDMI_ICPSNCR1                       0x1D
#define _P2_CA_PT_1E_PORT_PAGE2_HDMI_PCPSNCR0                       0x1E
#define _P2_CA_PT_1F_PORT_PAGE2_HDMI_PCPSNCR1                       0x1F
#define _P2_CA_PT_20_PORT_PAGE2_HDMI_ICTPSR0                        0x20
#define _P2_CA_PT_21_PORT_PAGE2_HDMI_ICTPSR1                        0x21
#define _P2_CA_PT_22_PORT_PAGE2_HDMI_PCTPSR0                        0x22
#define _P2_CA_PT_23_PORT_PAGE2_HDMI_PCTPSR1                        0x23
#define _P2_CA_PT_24_PORT_PAGE2_HDMI_ICBPSR0                        0x24
#define _P2_CA_PT_25_PORT_PAGE2_HDMI_ICBPSR1                        0x25
#define _P2_CA_PT_26_PORT_PAGE2_HDMI_PCBPSR0                        0x26
#define _P2_CA_PT_27_PORT_PAGE2_HDMI_PCBPSR1                        0x27
#define _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0                     0x28
#define _P2_CA_PT_29_PORT_PAGE2_HDMI_NTX1024TR1                     0x29
#define _P2_CA_PT_2A_PORT_PAGE2_HDMI_STBPR                          0x2A
#define _P2_CA_PT_2B_PORT_PAGE2_HDMI_NCPER                          0x2B
#define _P2_CA_PT_2C_PORT_PAGE2_HDMI_PETR                           0x2C
#define _P2_CA_PT_2D_PORT_PAGE2_HDMI_AAPNR                          0x2D
#define _P2_CA_PT_2E_PORT_PAGE2_HDMI_APDMCR                         0x2E
#define _P2_CA_PT_30_PORT_PAGE2_HDMI_AVMCR                          0x30
#define _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0                          0x31
#define _P2_CA_PT_32_PORT_PAGE2_HDMI_WDCR1                          0x32
#define _P2_CA_PT_33_PORT_PAGE2_HDMI_WDCR2                          0x33
#define _P2_CA_PT_34_PORT_PAGE2_HDMI_DBCR                           0x34
#define _P2_CA_PT_35_PORT_PAGE2_HDMI_APTMCR0                        0x35
#define _P2_CA_PT_36_PORT_PAGE2_HDMI_APTMCR1                        0x36
#define _P2_CA_PT_38_PORT_PAGE2_HDMI_DPCR0                          0x38
#define _P2_CA_PT_39_PORT_PAGE2_HDMI_DPCR1                          0x39
#define _P2_CA_PT_3A_PORT_PAGE2_HDMI_DPCR2                          0x3A
#define _P2_CA_PT_3B_PORT_PAGE2_HDMI_DPCR3                          0x3B
#define _P2_CA_PT_3C_PORT_PAGE2_HDMI_SUMCM                          0x3C
#define _P2_CA_PT_3D_PORT_PAGE2_HDMI_SUMCL                          0x3D
#define _P2_CA_PT_3E_PORT_PAGE2_DPLL_M_N_MSB                        0x3E
#define _P2_CA_PT_3F_PORT_PAGE2_DPLL_LDO                            0x3F
#define _P2_CA_PT_40_PORT_PAGE2_HDMI_AWDSR                          0x40
#define _P2_CA_PT_41_PORT_PAGE2_HDMI_VWDSR                          0x41
#define _P2_CA_PT_42_PORT_PAGE2_HDMI_PAMICR                         0x42
#define _P2_CA_PT_43_PORT_PAGE2_HDMI_PTRSV0                         0x43
#define _P2_CA_PT_44_PORT_PAGE2_HDMI_PTRSV1                         0x44
#define _P2_CA_PT_45_PORT_PAGE2_HDMI_PVGCR0                         0x45
#define _P2_CA_PT_46_PORT_PAGE2_HDMI_PVGCR1                         0x46
#define _P2_CA_PT_47_PORT_PAGE2_HDMI_PVGCR2                         0x47
#define _P2_CA_PT_48_PORT_PAGE2_HDMI_PVSR0                          0x48
#define _P2_CA_PT_49_PORT_PAGE2_HDMI_PVSR1                          0x49
#define _P2_CA_PT_4A_PORT_PAGE2_HDMI_PVSR2                          0x4A
#define _P2_CA_PT_50_PORT_PAGE2_HDMI_VCR                            0x50
#define _P2_CA_PT_51_PORT_PAGE2_HDMI_ACRCR                          0x51
#define _P2_CA_PT_52_PORT_PAGE2_HDMI_ACRSR0                         0x52
#define _P2_CA_PT_53_PORT_PAGE2_HDMI_ACRSR1                         0x53
#define _P2_CA_PT_54_PORT_PAGE2_HDMI_ACRSR2                         0x54
#define _P2_CA_PT_55_PORT_PAGE2_HDMI_ACRSR3                         0x55
#define _P2_CA_PT_56_PORT_PAGE2_HDMI_ACRSR4                         0x56
#define _P2_CA_PT_57_PORT_PAGE2_HDMI_ACS0                           0x57
#define _P2_CA_PT_58_PORT_PAGE2_HDMI_ACS1                           0x58
#define _P2_CA_PT_59_PORT_PAGE2_HDMI_ACS2                           0x59
#define _P2_CA_PT_5A_PORT_PAGE2_HDMI_ACS3                           0x5A
#define _P2_CA_PT_5B_PORT_PAGE2_HDMI_ACS4                           0x5B
#define _P2_CA_PT_60_PORT_PAGE2_HDMI_INTCR                          0x60
#define _P2_CA_PT_61_PORT_PAGE2_HDMI_ALCR                           0x61
#define _P2_CA_PT_62_PORT_PAGE2_HDMI_AOCR                           0x62
#define _P2_CA_PT_70_PORT_PAGE2_HDMI_BCSR                           0x70
#define _P2_CA_PT_71_PORT_PAGE2_HDMI_ASR0                           0x71
#define _P2_CA_PT_72_PORT_PAGE2_HDMI_ASR1                           0x72
#define _P2_CA_PT_80_PORT_PAGE2_HDMI_DPC_SET0                       0x80
#define _P2_CA_PT_81_PORT_PAGE2_HDMI_DPC_SET1                       0x81
#define _P2_CA_PT_82_PORT_PAGE2_HDMI_DPC_SET2                       0x82
#define _P2_CA_PT_83_PORT_PAGE2_HDMI_DPC_SET3                       0x83
#define _P2_CA_PT_84_PORT_PAGE2_HDMI_DET_0                          0x84
#define _P2_CA_PT_85_PORT_PAGE2_HDMI_DET_1                          0x85
#define _P2_CA_PT_86_PORT_PAGE2_HDMI_DET_2                          0x86
#define _P2_CA_PT_87_PORT_PAGE2_HDMI_DET_3                          0x87
#define _P2_CA_PT_88_PORT_PAGE2_HDMI_DET_4                          0x88
#define _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET                       0x8A
#define _P2_CA_PT_8B_PORT_PAGE2_AUDIO_FREQ_RESULT                   0x8B
#define _P2_CA_PT_8C_PORT_PAGE2_AUDIO_FREQ_RESULT_M                 0x8C
#define _P2_CA_PT_8D_PORT_PAGE2_AUDIO_FREQ_RESULT_L                 0x8D
#define _P2_CA_PT_8E_PORT_PAGE2_XTAL_DIV                            0x8E
#define _P2_CA_PT_8F_PORT_PAGE2_TH0                                 0x8F
#define _P2_CA_PT_90_PORT_PAGE2_TH1                                 0x90
#define _P2_CA_PT_91_PORT_PAGE2_TH2                                 0x91
#define _P2_CA_PT_92_PORT_PAGE2_TH3                                 0x92
#define _P2_CA_PT_93_PORT_PAGE2_TH4                                 0x93
#define _P2_CA_PT_94_PORT_PAGE2_TH5                                 0x94
#define _P2_CA_PT_95_PORT_PAGE2_PRESET_S_CODE0                      0x95
#define _P2_CA_PT_96_PORT_PAGE2_PRESET_S_CODE1                      0x96
#define _P2_CA_PT_97_PORT_PAGE2_PRESET_S_CODE2                      0x97
#define _P2_CA_PT_98_PORT_PAGE2_PRESET_S2_CODE                      0x98
#define _P2_CA_PT_99_PORT_PAGE2_PRESET_D_CODE_0                     0x99
#define _P2_CA_PT_9A_PORT_PAGE2_PRESET_D_CODE_1                     0x9A
#define _P2_CA_PT_9B_PORT_PAGE2_PRESET_D_CODE_2                     0x9B
#define _P2_CA_PT_9C_PORT_PAGE2_PRESET_D_CODE_3                     0x9C
#define _P2_CA_PT_9D_PORT_PAGE2_PRESET_D_CODE_4                     0x9D
#define _P2_CA_PT_9E_PORT_PAGE2_PRESET_D_CODE_5                     0x9E
#define _P2_CA_PT_9F_PORT_PAGE2_PRESET_AFSM_MOD                     0x9F
#define _P2_CA_PT_A4_PORT_PAGE2_HDMI_PTRSV_2                        0xA4
#define _P2_CA_PT_A5_PORT_PAGE2_HDMI_PTRSV_3                        0xA5
#define _P2_CA_PT_A6_PORT_PAGE2_HDMI_PARSV                          0xA6
#define _P2_CA_PT_A7_PORT_PAGE2_HDMI_GPVS_0                         0xA7
#define _P2_CA_PT_A8_PORT_PAGE2_HDMI_PVSR_3                         0xA8
#define _P2_CA_PT_A9_PORT_PAGE2_HDMI_PVSR_4                         0xA9
#define _P2_CA_PT_AA_PORT_PAGE2_HDMI_PVGCR3                         0xAA
#define _P2_CA_PT_AB_PORT_PAGE2_HDMI_PVGCR4                         0xAB
#define _P2_CA_PT_AE_PORT_PAGE2_HDMI_GDI_TEST_FUNC                  0xAE
#define _P2_CA_PT_AF_PORT_PAGE2_HDMI_BED_FUNC_0                     0xAF
#define _P2_CA_PT_B0_PORT_PAGE2_HDMI_BED_FUNC_1                     0xB0
#define _P2_CA_PT_B1_PORT_PAGE2_HDMI_BED_FUNC_2                     0xB1
#define _P2_CA_PT_B2_PORT_PAGE2_HDMI_BED_FUNC_3                     0xB2
#define _P2_CA_PT_B3_PORT_PAGE2_HDMI_BED_FUNC_4                     0xB3
#define _P2_CA_PT_B4_PORT_PAGE2_HDMI_BED_FUNC_5                     0xB4
#define _P2_CA_PT_B5_PORT_PAGE2_HDMI_BED_FUNC_6                     0xB5
#define _P2_CA_PT_B6_PORT_PAGE2_HDMI_BED_FUNC_7                     0xB6
#define _P2_CA_PT_B7_PORT_PAGE2_HDMI_BED_FUNC_8                     0xB7
#define _P2_CA_PT_B8_PORT_PAGE2_HDMI_BED_FUNC_9                     0xB8


//--------------------------------------------------
// Overall HDMI System Function Block (Page 2)
//--------------------------------------------------
#define _P2_C4_PT_00_PORT_PAGE2_BKSV0                               0x00
#define _P2_C4_PT_01_PORT_PAGE2_BKSV1                               0x01
#define _P2_C4_PT_02_PORT_PAGE2_BKSV2                               0x02
#define _P2_C4_PT_03_PORT_PAGE2_BKSV3                               0x03
#define _P2_C4_PT_04_PORT_PAGE2_BKSV4                               0x04
#define _P2_C4_PT_08_PORT_PAGE2_RI0                                 0x08
#define _P2_C4_PT_09_PORT_PAGE2_RI1                                 0x09
#define _P2_C4_PT_0A_PORT_PAGE2_PJ                                  0x0A
#define _P2_C4_PT_10_PORT_PAGE2_AKSV0                               0x10
#define _P2_C4_PT_11_PORT_PAGE2_AKSV1                               0x11
#define _P2_C4_PT_12_PORT_PAGE2_AKSV2                               0x12
#define _P2_C4_PT_13_PORT_PAGE2_AKSV3                               0x13
#define _P2_C4_PT_14_PORT_PAGE2_AKSV4                               0x14
#define _P2_C4_PT_15_PORT_PAGE2_AINFO                               0x15
#define _P2_C4_PT_18_PORT_PAGE2_AN0                                 0x18
#define _P2_C4_PT_19_PORT_PAGE2_AN1                                 0x19
#define _P2_C4_PT_1A_PORT_PAGE2_AN2                                 0x1A
#define _P2_C4_PT_1B_PORT_PAGE2_AN3                                 0x1B
#define _P2_C4_PT_1C_PORT_PAGE2_AN4                                 0x1C
#define _P2_C4_PT_1D_PORT_PAGE2_AN5                                 0x1D
#define _P2_C4_PT_1E_PORT_PAGE2_AN6                                 0x1E
#define _P2_C4_PT_1F_PORT_PAGE2_AN7                                 0x1F
#define _P2_C4_PT_40_PORT_PAGE2_BCAPS                               0x40
#define _P2_C4_PT_42_PORT_PAGE2_BSTATUS                             0x42
#define _P2_C4_PT_43_PORT_PAGE2_KSV_FIFO                            0x43
#define _P2_C4_PT_50_PORT_PAGE2_HDCP2_VER                           0x50
#define _P2_C4_PT_60_PORT_PAGE2_HDCP2_WR_MSG                        0x60
#define _P2_C4_PT_70_PORT_PAGE2_HDCP2_STATUS1                       0x70
#define _P2_C4_PT_71_PORT_PAGE2_HDCP2_STATUS2                       0x71
#define _P2_C4_PT_80_PORT_PAGE2_HDCP2_RDMSG                         0x80
#define _P2_C4_PT_C0_PORT_PAGE2_HDCP_FCR                            0xC0
#define _P2_C4_PT_C1_PORT_PAGE2_HDCP_SIR                            0xC1
#define _P2_C4_PT_C2_PORT_PAGE2_HDCP_SLAVE_ADD                      0xC2
#define _P2_CA_PT_00_PORT_PAGE2_HDMI_SCR                            0x00
#define _P2_CA_PT_01_PORT_PAGE2_HDMI_N_VAL                          0x01
#define _P2_CA_PT_02_PORT_PAGE2_HDMI_BCHCR                          0x02
#define _P2_CA_PT_03_PORT_PAGE2_HDMI_AFCR                           0x03
#define _P2_CA_PT_04_PORT_PAGE2_HDMI_AFSR                           0x04
#define _P2_CA_PT_05_PORT_PAGE2_HDMI_MAGCR1                         0x05
#define _P2_CA_PT_06_PORT_PAGE2_HDMI_MAGCR2                         0x06
#define _P2_CA_PT_07_PORT_PAGE2_HDMI_MAG_M_FINAL                    0x07
#define _P2_CA_PT_08_PORT_PAGE2_HDMI_MAG_L_FINAL                    0x08
#define _P2_CA_PT_09_PORT_PAGE2_HDMI_MAG_R_FINAL                    0x09
#define _P2_CA_PT_0A_PORT_PAGE2_AUDIO_LD_P_TIME_M                   0x0A
#define _P2_CA_PT_0B_PORT_PAGE2_AUDIO_LD_P_TIME_N                   0x0B
#define _P2_CA_PT_0C_PORT_PAGE2_ZCD_CTRL                            0x0C
#define _P2_CA_PT_0D_PORT_PAGE2_ZCD_TIMEOUT                         0x0D
#define _P2_CA_PT_0E_PORT_PAGE2_ZCD_STATUS                          0x0E
#define _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR                           0x10
#define _P2_CA_PT_11_PORT_PAGE2_HDMI_MCAPR                          0x11
#define _P2_CA_PT_12_PORT_PAGE2_HDMI_SCAPR                          0x12
#define _P2_CA_PT_13_PORT_PAGE2_HDMI_DCAPR0                         0x13
#define _P2_CA_PT_14_PORT_PAGE2_HDMI_DCAPR1                         0x14
#define _P2_CA_PT_15_PORT_PAGE2_HDMI_PSCR                           0x15
#define _P2_CA_PT_16_PORT_PAGE2_HDMI_FDDR                           0x16
#define _P2_CA_PT_17_PORT_PAGE2_HDMI_FDDF                           0x17
#define _P2_CA_PT_18_PORT_PAGE2_HDMI_MFDDR                          0x18
#define _P2_CA_PT_19_PORT_PAGE2_HDMI_MFDDF                          0x19
#define _P2_CA_PT_1A_PORT_PAGE2_HDMI_FTR                            0x1A
#define _P2_CA_PT_1B_PORT_PAGE2_HDMI_FBR                            0x1B
#define _P2_CA_PT_1C_PORT_PAGE2_HDMI_ICPSNCR0                       0x1C
#define _P2_CA_PT_1D_PORT_PAGE2_HDMI_ICPSNCR1                       0x1D
#define _P2_CA_PT_1E_PORT_PAGE2_HDMI_PCPSNCR0                       0x1E
#define _P2_CA_PT_1F_PORT_PAGE2_HDMI_PCPSNCR1                       0x1F
#define _P2_CA_PT_20_PORT_PAGE2_HDMI_ICTPSR0                        0x20
#define _P2_CA_PT_21_PORT_PAGE2_HDMI_ICTPSR1                        0x21
#define _P2_CA_PT_22_PORT_PAGE2_HDMI_PCTPSR0                        0x22
#define _P2_CA_PT_23_PORT_PAGE2_HDMI_PCTPSR1                        0x23
#define _P2_CA_PT_24_PORT_PAGE2_HDMI_ICBPSR0                        0x24
#define _P2_CA_PT_25_PORT_PAGE2_HDMI_ICBPSR1                        0x25
#define _P2_CA_PT_26_PORT_PAGE2_HDMI_PCBPSR0                        0x26
#define _P2_CA_PT_27_PORT_PAGE2_HDMI_PCBPSR1                        0x27
#define _P2_CA_PT_28_PORT_PAGE2_HDMI_NTX1024TR0                     0x28
#define _P2_CA_PT_29_PORT_PAGE2_HDMI_NTX1024TR1                     0x29
#define _P2_CA_PT_2A_PORT_PAGE2_HDMI_STBPR                          0x2A
#define _P2_CA_PT_2B_PORT_PAGE2_HDMI_NCPER                          0x2B
#define _P2_CA_PT_2C_PORT_PAGE2_HDMI_PETR                           0x2C
#define _P2_CA_PT_2D_PORT_PAGE2_HDMI_AAPNR                          0x2D
#define _P2_CA_PT_2E_PORT_PAGE2_HDMI_APDMCR                         0x2E
#define _P2_CA_PT_30_PORT_PAGE2_HDMI_AVMCR                          0x30
#define _P2_CA_PT_31_PORT_PAGE2_HDMI_WDCR0                          0x31
#define _P2_CA_PT_32_PORT_PAGE2_HDMI_WDCR1                          0x32
#define _P2_CA_PT_33_PORT_PAGE2_HDMI_WDCR2                          0x33
#define _P2_CA_PT_34_PORT_PAGE2_HDMI_DBCR                           0x34
#define _P2_CA_PT_35_PORT_PAGE2_HDMI_APTMCR0                        0x35
#define _P2_CA_PT_36_PORT_PAGE2_HDMI_APTMCR1                        0x36
#define _P2_CA_PT_38_PORT_PAGE2_HDMI_DPCR0                          0x38
#define _P2_CA_PT_39_PORT_PAGE2_HDMI_DPCR1                          0x39
#define _P2_CA_PT_3A_PORT_PAGE2_HDMI_DPCR2                          0x3A
#define _P2_CA_PT_3B_PORT_PAGE2_HDMI_DPCR3                          0x3B
#define _P2_CA_PT_3C_PORT_PAGE2_HDMI_SUMCM                          0x3C
#define _P2_CA_PT_3D_PORT_PAGE2_HDMI_SUMCL                          0x3D
#define _P2_CA_PT_3E_PORT_PAGE2_DPLL_M_N_MSB                        0x3E
#define _P2_CA_PT_3F_PORT_PAGE2_DPLL_LDO                            0x3F
#define _P2_CA_PT_40_PORT_PAGE2_HDMI_AWDSR                          0x40
#define _P2_CA_PT_41_PORT_PAGE2_HDMI_VWDSR                          0x41
#define _P2_CA_PT_42_PORT_PAGE2_HDMI_PAMICR                         0x42
#define _P2_CA_PT_43_PORT_PAGE2_HDMI_PTRSV0                         0x43
#define _P2_CA_PT_44_PORT_PAGE2_HDMI_PTRSV1                         0x44
#define _P2_CA_PT_45_PORT_PAGE2_HDMI_PVGCR0                         0x45
#define _P2_CA_PT_46_PORT_PAGE2_HDMI_PVGCR1                         0x46
#define _P2_CA_PT_47_PORT_PAGE2_HDMI_PVGCR2                         0x47
#define _P2_CA_PT_48_PORT_PAGE2_HDMI_PVSR0                          0x48
#define _P2_CA_PT_49_PORT_PAGE2_HDMI_PVSR1                          0x49
#define _P2_CA_PT_4A_PORT_PAGE2_HDMI_PVSR2                          0x4A
#define _P2_CA_PT_50_PORT_PAGE2_HDMI_VCR                            0x50
#define _P2_CA_PT_51_PORT_PAGE2_HDMI_ACRCR                          0x51
#define _P2_CA_PT_52_PORT_PAGE2_HDMI_ACRSR0                         0x52
#define _P2_CA_PT_53_PORT_PAGE2_HDMI_ACRSR1                         0x53
#define _P2_CA_PT_54_PORT_PAGE2_HDMI_ACRSR2                         0x54
#define _P2_CA_PT_55_PORT_PAGE2_HDMI_ACRSR3                         0x55
#define _P2_CA_PT_56_PORT_PAGE2_HDMI_ACRSR4                         0x56
#define _P2_CA_PT_57_PORT_PAGE2_HDMI_ACS0                           0x57
#define _P2_CA_PT_58_PORT_PAGE2_HDMI_ACS1                           0x58
#define _P2_CA_PT_59_PORT_PAGE2_HDMI_ACS2                           0x59
#define _P2_CA_PT_5A_PORT_PAGE2_HDMI_ACS3                           0x5A
#define _P2_CA_PT_5B_PORT_PAGE2_HDMI_ACS4                           0x5B
#define _P2_CA_PT_60_PORT_PAGE2_HDMI_INTCR                          0x60
#define _P2_CA_PT_61_PORT_PAGE2_HDMI_ALCR                           0x61
#define _P2_CA_PT_62_PORT_PAGE2_HDMI_AOCR                           0x62
#define _P2_CA_PT_63_PORT_PAGE2_HDMI_PEAC1                          0x63
#define _P2_CA_PT_64_PORT_PAGE2_HDMI_PEAC2                          0x64
#define _P2_CA_PT_70_PORT_PAGE2_HDMI_BCSR                           0x70
#define _P2_CA_PT_71_PORT_PAGE2_HDMI_ASR0                           0x71
#define _P2_CA_PT_72_PORT_PAGE2_HDMI_ASR1                           0x72
#define _P2_CA_PT_80_PORT_PAGE2_HDMI_DPC_SET0                       0x80
#define _P2_CA_PT_81_PORT_PAGE2_HDMI_DPC_SET1                       0x81
#define _P2_CA_PT_82_PORT_PAGE2_HDMI_DPC_SET2                       0x82
#define _P2_CA_PT_83_PORT_PAGE2_HDMI_DPC_SET3                       0x83
#define _P2_CA_PT_84_PORT_PAGE2_HDMI_DET_0                          0x84
#define _P2_CA_PT_85_PORT_PAGE2_HDMI_DET_1                          0x85
#define _P2_CA_PT_86_PORT_PAGE2_HDMI_DET_2                          0x86
#define _P2_CA_PT_87_PORT_PAGE2_HDMI_DET_3                          0x87
#define _P2_CA_PT_88_PORT_PAGE2_HDMI_DET_4                          0x88
#define _P2_CA_PT_8A_PORT_PAGE2_AUDIO_FREQDET                       0x8A
#define _P2_CA_PT_8B_PORT_PAGE2_AUDIO_FREQ_RESULT                   0x8B
#define _P2_CA_PT_8C_PORT_PAGE2_AUDIO_FREQ_RESULT_M                 0x8C
#define _P2_CA_PT_8D_PORT_PAGE2_AUDIO_FREQ_RESULT_L                 0x8D
#define _P2_CA_PT_8E_PORT_PAGE2_XTAL_DIV                            0x8E
#define _P2_CA_PT_8F_PORT_PAGE2_TH0                                 0x8F
#define _P2_CA_PT_90_PORT_PAGE2_TH1                                 0x90
#define _P2_CA_PT_91_PORT_PAGE2_TH2                                 0x91
#define _P2_CA_PT_92_PORT_PAGE2_TH3                                 0x92
#define _P2_CA_PT_93_PORT_PAGE2_TH4                                 0x93
#define _P2_CA_PT_94_PORT_PAGE2_TH5                                 0x94
#define _P2_CA_PT_95_PORT_PAGE2_PRESET_S_CODE0                      0x95
#define _P2_CA_PT_96_PORT_PAGE2_PRESET_S_CODE1                      0x96
#define _P2_CA_PT_97_PORT_PAGE2_PRESET_S_CODE2                      0x97
#define _P2_CA_PT_98_PORT_PAGE2_PRESET_S2_CODE                      0x98
#define _P2_CA_PT_99_PORT_PAGE2_PRESET_D_CODE_0                     0x99
#define _P2_CA_PT_9A_PORT_PAGE2_PRESET_D_CODE_1                     0x9A
#define _P2_CA_PT_9B_PORT_PAGE2_PRESET_D_CODE_2                     0x9B
#define _P2_CA_PT_9C_PORT_PAGE2_PRESET_D_CODE_3                     0x9C
#define _P2_CA_PT_9D_PORT_PAGE2_PRESET_D_CODE_4                     0x9D
#define _P2_CA_PT_9E_PORT_PAGE2_PRESET_D_CODE_5                     0x9E
#define _P2_CA_PT_9F_PORT_PAGE2_PRESET_AFSM_MOD                     0x9F
#define _P2_CA_PT_A4_PORT_PAGE2_HDMI_PTRSV_2                        0xA4
#define _P2_CA_PT_A5_PORT_PAGE2_HDMI_PTRSV_3                        0xA5
#define _P2_CA_PT_A6_PORT_PAGE2_HDMI_PARSV                          0xA6
#define _P2_CA_PT_A7_PORT_PAGE2_HDMI_GPVS_0                         0xA7
#define _P2_CA_PT_A8_PORT_PAGE2_HDMI_PVSR_3                         0xA8
#define _P2_CA_PT_A9_PORT_PAGE2_HDMI_PVSR_4                         0xA9
#define _P2_CA_PT_AA_PORT_PAGE2_HDMI_PVGCR3                         0xAA
#define _P2_CA_PT_AB_PORT_PAGE2_HDMI_PVGCR4                         0xAB
#define _P2_CA_PT_AE_PORT_PAGE2_HDMI_GDI_TEST_FUNC                  0xAE
#define _P2_CA_PT_AF_PORT_PAGE2_HDMI_BED_FUNC_0                     0xAF
#define _P2_CA_PT_B0_PORT_PAGE2_HDMI_BED_FUNC_1                     0xB0
#define _P2_CA_PT_B1_PORT_PAGE2_HDMI_BED_FUNC_2                     0xB1
#define _P2_CA_PT_B2_PORT_PAGE2_HDMI_BED_FUNC_3                     0xB2
#define _P2_CA_PT_B3_PORT_PAGE2_HDMI_BED_FUNC_4                     0xB3
#define _P2_CA_PT_B4_PORT_PAGE2_HDMI_BED_FUNC_5                     0xB4
#define _P2_CA_PT_B5_PORT_PAGE2_HDMI_BED_FUNC_6                     0xB5
#define _P2_CA_PT_B6_PORT_PAGE2_HDMI_BED_FUNC_7                     0xB6
#define _P2_CA_PT_B7_PORT_PAGE2_HDMI_BED_FUNC_8                     0xB7
#define _P2_CA_PT_B8_PORT_PAGE2_HDMI_BED_FUNC_9                     0xB8


//--------------------------------------------------
// DCC (Page 7)
//--------------------------------------------------
#define _P7_CA_PT_00_PORT_PAGE0_NOR_FACTOR_H                        0x00
#define _P7_CA_PT_01_PORT_PAGE0_NOR_FACTOR_M                        0x01
#define _P7_CA_PT_02_PORT_PAGE0_NOR_FACTOR_L                        0x02
#define _P7_CA_PT_06_PORT_PAGE0_SOFT_CLAMP                          0x06
#define _P7_CA_PT_07_PORT_PAGE0_Y_MAX_LB_H                          0x07
#define _P7_CA_PT_08_PORT_PAGE0_Y_MIN_HB_H                          0x08
#define _P7_CA_PT_0C_PORT_PAGE0_POPUP_CTRL                          0x0C
#define _P7_CA_PT_0E_PORT_PAGE0_Y_MAX_VAL_H                         0x0E
#define _P7_CA_PT_0F_PORT_PAGE0_Y_MIN_VAL_H                         0x0F
#define _P7_CA_PT_10_PORT_PAGE0_S0_VALUE                            0x10
#define _P7_CA_PT_11_PORT_PAGE0_S1_VALUE                            0x11
#define _P7_CA_PT_12_PORT_PAGE0_S2_VALUE                            0x12
#define _P7_CA_PT_13_PORT_PAGE0_S3_VALUE                            0x13
#define _P7_CA_PT_14_PORT_PAGE0_S4_VALUE                            0x14
#define _P7_CA_PT_15_PORT_PAGE0_S5_VALUE                            0x15
#define _P7_CA_PT_16_PORT_PAGE0_S6_VALUE                            0x16
#define _P7_CA_PT_1E_PORT_PAGE0_READY_TO_READ                       0x1E
#define _P7_CA_PT_00_PORT_PAGE1_DEF_CRV01_H                         0x00
#define _P7_CA_PT_01_PORT_PAGE1_DEF_CRV02_H                         0x01
#define _P7_CA_PT_02_PORT_PAGE1_DEF_CRV03_H                         0x02
#define _P7_CA_PT_03_PORT_PAGE1_DEF_CRV04_H                         0x03
#define _P7_CA_PT_04_PORT_PAGE1_DEF_CRV05_H                         0x04
#define _P7_CA_PT_05_PORT_PAGE1_DEF_CRV06_H                         0x05
#define _P7_CA_PT_06_PORT_PAGE1_DEF_CRV07_H                         0x06
#define _P7_CA_PT_07_PORT_PAGE1_DEF_CRV08_H                         0x07
#define _P7_CA_PT_08_PORT_PAGE1_DEF_CRV09_H                         0x08
#define _P7_CA_PT_09_PORT_PAGE1_DEF_CRV10_H                         0x09
#define _P7_CA_PT_0A_PORT_PAGE1_DEF_CRV11_H                         0x0A
#define _P7_CA_PT_0B_PORT_PAGE1_DEF_CRV12_H                         0x0B
#define _P7_CA_PT_0C_PORT_PAGE1_DEF_CRV13_H                         0x0C
#define _P7_CA_PT_0D_PORT_PAGE1_DEF_CRV14_H                         0x0D
#define _P7_CA_PT_0E_PORT_PAGE1_DEF_CRV15_H                         0x0E
#define _P7_CA_PT_0F_PORT_PAGE1_DEF_CRV16_H                         0x0F
#define _P7_CA_PT_12_PORT_PAGE1_SAT_FACTOR                          0x12


//--------------------------------------------------
// ICM (Page 7)
//--------------------------------------------------
#define _P7_D3_PT_03_PORT_CMN_MST_00_DU_H                           0x03
#define _P7_D3_PT_04_PORT_CMN_MST_00_DV_H                           0x04
#define _P7_D3_PT_05_PORT_CMN_MST_01_DU_H                           0x05
#define _P7_D3_PT_06_PORT_CMN_MST_01_DV_H                           0x06
#define _P7_D3_PT_07_PORT_CMN_MST_02_DU_H                           0x07
#define _P7_D3_PT_08_PORT_CMN_MST_02_DV_H                           0x08
#define _P7_D3_PT_09_PORT_CMN_MST_03_DU_H                           0x09
#define _P7_D3_PT_0A_PORT_CMN_MST_03_DV_H                           0x0A
#define _P7_D3_PT_0B_PORT_CMN_MST_04_DU_H                           0x0B
#define _P7_D3_PT_0C_PORT_CMN_MST_04_DV_H                           0x0C
#define _P7_D3_PT_0D_PORT_CMN_MST_05_DU_H                           0x0D
#define _P7_D3_PT_0E_PORT_CMN_MST_05_DV_H                           0x0E
#define _P7_D3_PT_0F_PORT_CMN_MST_06_DU_H                           0x0F
#define _P7_D3_PT_10_PORT_CMN_MST_06_DV_H                           0x10
#define _P7_D3_PT_11_PORT_CMN_MST_07_DU_H                           0x11
#define _P7_D3_PT_12_PORT_CMN_MST_07_DV_H                           0x12
#define _P7_D3_PT_13_PORT_CMN_RWID_00_DU_H                          0x13
#define _P7_D3_PT_14_PORT_CMN_RWID_00_DV_H                          0x14
#define _P7_D3_PT_15_PORT_CMN_RWID_01_DU_H                          0x15
#define _P7_D3_PT_16_PORT_CMN_RWID_01_DV_H                          0x16
#define _P7_D3_PT_17_PORT_CMN_RWID_02_DU_H                          0x17
#define _P7_D3_PT_18_PORT_CMN_RWID_02_DV_H                          0x18
#define _P7_D3_PT_19_PORT_CMN_RWID_03_DU_H                          0x19
#define _P7_D3_PT_1A_PORT_CMN_RWID_03_DV_H                          0x1A
#define _P7_D3_PT_1B_PORT_CMN_RWID_04_DU_H                          0x1B
#define _P7_D3_PT_1C_PORT_CMN_RWID_04_DV_H                          0x1C
#define _P7_D3_PT_1D_PORT_CMN_RWID_05_DU_H                          0x1D
#define _P7_D3_PT_1E_PORT_CMN_RWID_05_DV_H                          0x1E
#define _P7_D3_PT_1F_PORT_CMN_RWID_06_DU_H                          0x1F
#define _P7_D3_PT_20_PORT_CMN_RWID_06_DV_H                          0x20
#define _P7_D3_PT_21_PORT_CMN_RWID_07_DU_H                          0x21
#define _P7_D3_PT_22_PORT_CMN_RWID_07_DV_H                          0x22
#define _P7_D3_PT_23_PORT_CMN_LWID_00_DU_H                          0x23
#define _P7_D3_PT_24_PORT_CMN_LWID_00_DV_H                          0x24
#define _P7_D3_PT_25_PORT_CMN_LWID_01_DU_H                          0x25
#define _P7_D3_PT_26_PORT_CMN_LWID_01_DV_H                          0x26
#define _P7_D3_PT_27_PORT_CMN_LWID_02_DU_H                          0x27
#define _P7_D3_PT_28_PORT_CMN_LWID_02_DV_H                          0x28
#define _P7_D3_PT_29_PORT_CMN_LWID_03_DU_H                          0x29
#define _P7_D3_PT_2A_PORT_CMN_LWID_03_DV_H                          0x2A
#define _P7_D3_PT_2B_PORT_CMN_LWID_04_DU_H                          0x2B
#define _P7_D3_PT_2C_PORT_CMN_LWID_04_DV_H                          0x2C
#define _P7_D3_PT_2D_PORT_CMN_LWID_05_DU_H                          0x2D
#define _P7_D3_PT_2E_PORT_CMN_LWID_05_DV_H                          0x2E
#define _P7_D3_PT_2F_PORT_CMN_LWID_06_DU_H                          0x2F
#define _P7_D3_PT_30_PORT_CMN_LWID_06_DV_H                          0x30
#define _P7_D3_PT_31_PORT_CMN_LWID_07_DU_H                          0x31
#define _P7_D3_PT_32_PORT_CMN_LWID_07_DV_H                          0x32
#define _P7_D3_PT_33_PORT_CMN_RBUF_00_DU_H                          0x33
#define _P7_D3_PT_34_PORT_CMN_RBUF_00_DV_H                          0x34
#define _P7_D3_PT_35_PORT_CMN_RBUF_01_DU_H                          0x35
#define _P7_D3_PT_36_PORT_CMN_RBUF_01_DV_H                          0x36
#define _P7_D3_PT_37_PORT_CMN_RBUF_02_DU_H                          0x37
#define _P7_D3_PT_38_PORT_CMN_RBUF_02_DV_H                          0x38
#define _P7_D3_PT_39_PORT_CMN_RBUF_03_DU_H                          0x39
#define _P7_D3_PT_3A_PORT_CMN_RBUF_03_DV_H                          0x3A
#define _P7_D3_PT_3B_PORT_CMN_RBUF_04_DU_H                          0x3B
#define _P7_D3_PT_3C_PORT_CMN_RBUF_04_DV_H                          0x3C
#define _P7_D3_PT_3D_PORT_CMN_RBUF_05_DU_H                          0x3D
#define _P7_D3_PT_3E_PORT_CMN_RBUF_05_DV_H                          0x3E
#define _P7_D3_PT_3F_PORT_CMN_RBUF_06_DU_H                          0x3F
#define _P7_D3_PT_40_PORT_CMN_RBUF_06_DV_H                          0x40
#define _P7_D3_PT_41_PORT_CMN_RBUF_07_DU_H                          0x41
#define _P7_D3_PT_42_PORT_CMN_RBUF_07_DV_H                          0x42
#define _P7_D3_PT_43_PORT_CMN_LBUF_00_DU_H                          0x43
#define _P7_D3_PT_44_PORT_CMN_LBUF_00_DV_H                          0x44
#define _P7_D3_PT_45_PORT_CMN_LBUF_01_DU_H                          0x45
#define _P7_D3_PT_46_PORT_CMN_LBUF_01_DV_H                          0x46
#define _P7_D3_PT_47_PORT_CMN_LBUF_02_DU_H                          0x47
#define _P7_D3_PT_48_PORT_CMN_LBUF_02_DV_H                          0x48
#define _P7_D3_PT_49_PORT_CMN_LBUF_03_DU_H                          0x49
#define _P7_D3_PT_4A_PORT_CMN_LBUF_03_DV_H                          0x4A
#define _P7_D3_PT_4B_PORT_CMN_LBUF_04_DU_H                          0x4B
#define _P7_D3_PT_4C_PORT_CMN_LBUF_04_DV_H                          0x4C
#define _P7_D3_PT_4D_PORT_CMN_LBUF_05_DU_H                          0x4D
#define _P7_D3_PT_4E_PORT_CMN_LBUF_05_DV_H                          0x4E
#define _P7_D3_PT_4F_PORT_CMN_LBUF_06_DU_H                          0x4F
#define _P7_D3_PT_50_PORT_CMN_LBUF_06_DV_H                          0x50
#define _P7_D3_PT_51_PORT_CMN_LBUF_07_DU_H                          0x51
#define _P7_D3_PT_52_PORT_CMN_LBUF_07_DV_H                          0x52
#define _P7_D3_PT_53_PORT_CMN_MST_UMAX_H                            0x53
#define _P7_D3_PT_54_PORT_CMN_MST_UMAX_M                            0x54
#define _P7_D3_PT_55_PORT_CMN_RWID_UMAX_H                           0x55
#define _P7_D3_PT_56_PORT_CMN_RWID_UMAX_M                           0x56
#define _P7_D3_PT_57_PORT_CMN_LWID_UMAX_H                           0x57
#define _P7_D3_PT_58_PORT_CMN_LWID_UMAX_M                           0x58
#define _P7_D3_PT_59_PORT_CMN_RBUF_UMAX_H                           0x59
#define _P7_D3_PT_5A_PORT_CMN_RBUF_UMAX_M                           0x5A
#define _P7_D3_PT_5B_PORT_CMN_LBUF_UMAX_H                           0x5B
#define _P7_D3_PT_5C_PORT_CMN_LBUF_UMAX_M                           0x5C
#define _P7_D3_PT_5D_PORT_CMN_RBUF_HUE_H                            0x5D
#define _P7_D3_PT_5E_PORT_CMN_RBUF_HUE_M                            0x5E
#define _P7_D3_PT_5F_PORT_CMN_RWID_RANGE_H                          0x5F
#define _P7_D3_PT_60_PORT_CMN_RWID_RANGE_M                          0x60
#define _P7_D3_PT_61_PORT_CMN_MST_RANGE_H                           0x61
#define _P7_D3_PT_62_PORT_CMN_MST_RANGE_M                           0x62
#define _P7_D3_PT_63_PORT_CMN_LWID_RANGE_H                          0x63
#define _P7_D3_PT_64_PORT_CMN_LWID_RANGE_M                          0x64
#define _P7_D3_PT_65_PORT_CMN_LBUF_RANGE_H                          0x65
#define _P7_D3_PT_66_PORT_CMN_LBUF_RANGE_M                          0x66
#define _P7_D3_PT_67_PORT_CMN_BRI_RANGE                             0x67
#define _P7_D3_PT_68_PORT_CMN_BRI_BUF_EN                            0x68
#define _P7_D3_PT_69_PORT_CMN_M_AXIS_DELY_H                         0x69
#define _P7_D3_PT_6A_PORT_CMN_M_AXIS_DELY_L                         0x6A
#define _P7_D3_PT_6B_PORT_CMN_R_AXIS_DELY_H                         0x6B
#define _P7_D3_PT_6C_PORT_CMN_R_AXIS_DELY_L                         0x6C
#define _P7_D3_PT_6D_PORT_CMN_L_AXIS_DELY_H                         0x6D
#define _P7_D3_PT_6E_PORT_CMN_L_AXIS_DELY_L                         0x6E


//--------------------------------------------------
// Y-Peaking and Coring (D-Domain) (Page 7)
//--------------------------------------------------
#define _P7_D7_PT_00_PEAKING_C0                                     0x00
#define _P7_D7_PT_01_PEAKING_C1                                     0x01
#define _P7_D7_PT_02_PEAKING_C2                                     0x02
#define _P7_D7_PT_03_CORING_MIN                                     0x03
#define _P7_D7_PT_04_CORING_MAX_POS                                 0x04
#define _P7_D7_PT_05_CORING_MAX_NEG                                 0x05


//--------------------------------------------------
// DCR (Page 7)
//--------------------------------------------------
#define _P7_D9_PT_00_DCR_THESHOLD1_1                                0x00
#define _P7_D9_PT_01_DCR_THESHOLD2_1                                0x01
#define _P7_D9_PT_02_DCR_ABOVE_TH1_NUM_2                            0x02
#define _P7_D9_PT_03_DCR_ABOVE_TH1_NUM_1                            0x03
#define _P7_D9_PT_04_DCR_ABOVE_TH1_NUM_0                            0x04
#define _P7_D9_PT_05_DCR_ABOVE_TH1_VAL_4                            0x05
#define _P7_D9_PT_06_DCR_ABOVE_TH1_VAL_3                            0x06
#define _P7_D9_PT_07_DCR_ABOVE_TH1_VAL_2                            0x07
#define _P7_D9_PT_08_DCR_ABOVE_TH1_VAL_1                            0x08
#define _P7_D9_PT_09_DCR_ABOVE_TH2_NUM_2                            0x09
#define _P7_D9_PT_0A_DCR_ABOVE_TH2_NUM_1                            0x0A
#define _P7_D9_PT_0B_DCR_ABOVE_TH2_NUM_0                            0x0B
#define _P7_D9_PT_0C_DCR_ABOVE_TH2_VAL_4                            0x0C
#define _P7_D9_PT_0D_DCR_ABOVE_TH2_VAL_3                            0x0D
#define _P7_D9_PT_0E_DCR_ABOVE_TH2_VAL_2                            0x0E
#define _P7_D9_PT_0F_DCR_ABOVE_TH2_VAL_1                            0x0F
#define _P7_D9_PT_10_DCR_HIGH_LV_NUM_R_1                            0x10
#define _P7_D9_PT_11_DCR_HIGH_LV_NUM_R_0                            0x11
#define _P7_D9_PT_12_DCR_LOW_LV_NUM_R_1                             0x12
#define _P7_D9_PT_13_DCR_LOW_LV_NUM_R_0                             0x13
#define _P7_D9_PT_14_DCR_HIGH_LV_VAL_R_1                            0x14
#define _P7_D9_PT_15_DCR_LOW_LV_VAL_R_1                             0x15
#define _P7_D9_PT_16_DCR_HIGH_LV_NUM_G_1                            0x16
#define _P7_D9_PT_17_DCR_HIGH_LV_NUM_G_0                            0x17
#define _P7_D9_PT_18_DCR_LOW_LV_NUM_G_1                             0x18
#define _P7_D9_PT_19_DCR_LOW_LV_NUM_G_0                             0x19
#define _P7_D9_PT_1A_DCR_HIGH_LV_VAL_G_1                            0x1A
#define _P7_D9_PT_1B_DCR_LOW_LV_VAL_G_1                             0x1B
#define _P7_D9_PT_1C_DCR_HIGH_LV_NUM_B_1                            0x1C
#define _P7_D9_PT_1D_DCR_HIGH_LV_NUM_B_0                            0x1D
#define _P7_D9_PT_1E_DCR_LOW_LV_NUM_B_1                             0x1E
#define _P7_D9_PT_1F_DCR_LOW_LV_NUM_B_0                             0x1F
#define _P7_D9_PT_20_DCR_HIGH_LV_VAL_B_1                            0x20
#define _P7_D9_PT_21_DCR_LOW_LV_VAL_B_1                             0x21
#define _P7_D9_PT_22_DCR_HIGH_LV_NUM_R_2                            0x22
#define _P7_D9_PT_23_DCR_LOW_LV_NUM_R_2                             0x23
#define _P7_D9_PT_24_DCR_HIGH_LV_NUM_G_2                            0x24
#define _P7_D9_PT_25_DCR_LOW_LV_NUM_G_2                             0x25
#define _P7_D9_PT_26_DCR_HIGH_LV_NUM_B_2                            0x26
#define _P7_D9_PT_27_DCR_LOW_LV_NUM_B_2                             0x27
#define _P7_D9_PT_28_DCR_Y_MAX_1                                    0x28
#define _P7_D9_PT_29_DCR_Y_MIN_1                                    0x29


//--------------------------------------------------
// Embedded Timing Controller (Page 15)
//--------------------------------------------------
#define _P15_A4_PT_00_TC_CTRL0                                      0x00
#define _P15_A4_PT_01_TC_CTRL1                                      0x01
#define _P15_A4_PT_02_FLICK_CTRL0                                   0x02
#define _P15_A4_PT_03_FLICK_CTRL1                                   0x03
#define _P15_A4_PT_04_FLICK_CTRL2                                   0x04
#define _P15_A4_PT_05_FLICK_CTRL3                                   0x05
#define _P15_A4_PT_06_TC_CTRL2                                      0x06
#define _P15_A4_PT_07_TC_CTRL3                                      0x07
#define _P15_A4_PT_08_TC_CTRL4                                      0x08
#define _P15_A4_PT_09_TC_CTRL5                                      0x09
#define _P15_A4_PT_80_TC7_VS_MSB                                    0x80
#define _P15_A4_PT_81_TC7_VS_LSB                                    0x81
#define _P15_A4_PT_82_TC7_VE_MSB                                    0x82
#define _P15_A4_PT_83_TC7_VE_LSB                                    0x83
#define _P15_A4_PT_84_TC7_HS_MSB                                    0x84
#define _P15_A4_PT_85_TC7_HS_LSB                                    0x85
#define _P15_A4_PT_86_TC7_HE_MSB                                    0x86
#define _P15_A4_PT_87_TC7_HE_LSB                                    0x87
#define _P15_A4_PT_88_TC7_CTRL                                      0x88
#define _P15_A4_PT_89_TC7_RESERVE                                   0x89
#define _P15_A4_PT_90_TC8_VS_MSB                                    0x90
#define _P15_A4_PT_91_TC8_VS_LSB                                    0x91
#define _P15_A4_PT_92_TC8_VE_MSB                                    0x92
#define _P15_A4_PT_93_TC8_VE_LSB                                    0x93
#define _P15_A4_PT_94_TC8_HS_MSB                                    0x94
#define _P15_A4_PT_95_TC8_HS_LSB                                    0x95
#define _P15_A4_PT_96_TC8_HE_MSB                                    0x96
#define _P15_A4_PT_97_TC8_HE_LSB                                    0x97
#define _P15_A4_PT_98_TC8_CTRL                                      0x98
#define _P15_A4_PT_99_TC8_RESERVE                                   0x99
#define _P15_A4_PT_A0_TC9_VS_MSB                                    0xA0
#define _P15_A4_PT_A1_TC9_VS_LSB                                    0xA1
#define _P15_A4_PT_A2_TC9_VE_MSB                                    0xA2
#define _P15_A4_PT_A3_TC9_VE_LSB                                    0xA3
#define _P15_A4_PT_A4_TC9_HS_MSB                                    0xA4
#define _P15_A4_PT_A5_TC9_HS_LSB                                    0xA5
#define _P15_A4_PT_A6_TC9_HE_MSB                                    0xA6
#define _P15_A4_PT_A7_TC9_HE_LSB                                    0xA7
#define _P15_A4_PT_A8_TC9_CTRL                                      0xA8
#define _P15_A4_PT_A9_TC9_RESERVE                                   0xA9
#define _P15_A4_PT_C0_TC11_VS_MSB                                   0xC0
#define _P15_A4_PT_C1_TC11_VS_LSB                                   0xC1
#define _P15_A4_PT_C2_TC11_VE_MSB                                   0xC2
#define _P15_A4_PT_C3_TC11_VE_LSB                                   0xC3
#define _P15_A4_PT_C4_TC11_HS_MSB                                   0xC4
#define _P15_A4_PT_C5_TC11_HS_LSB                                   0xC5
#define _P15_A4_PT_C6_TC11_HE_MSB                                   0xC6
#define _P15_A4_PT_C7_TC11_HE_LSB                                   0xC7
#define _P15_A4_PT_C8_TC11_CTRL                                     0xC8
#define _P15_A4_PT_C9_TC11_DOT_MASK                                 0xC9
#define _P15_A4_PT_CA_TC11_RESERVE                                  0xCA
#define _P15_A4_PT_D0_TC12_VS_MSB                                   0xD0
#define _P15_A4_PT_D1_TC12_VS_LSB                                   0xD1
#define _P15_A4_PT_D2_TC12_VE_MSB                                   0xD2
#define _P15_A4_PT_D3_TC12_VE_LSB                                   0xD3
#define _P15_A4_PT_D4_TC12_HS_MSB                                   0xD4
#define _P15_A4_PT_D5_TC12_HS_LSB                                   0xD5
#define _P15_A4_PT_D6_TC12_HE_MSB                                   0xD6
#define _P15_A4_PT_D7_TC12_HE_LSB                                   0xD7
#define _P15_A4_PT_D8_TC12_CTRL                                     0xD8
#define _P15_A4_PT_D9_TC12_DOT_MASK                                 0xD9
#define _P15_A4_PT_DA_TC12_RESERVE                                  0xDA
#define _P15_A4_PT_E0_TC13_VS_MSB                                   0xE0
#define _P15_A4_PT_E1_TC13_VS_LSB                                   0xE1
#define _P15_A4_PT_E2_TC13_VE_MSB                                   0xE2
#define _P15_A4_PT_E3_TC13_VE_LSB                                   0xE3
#define _P15_A4_PT_E4_TC13_HS_MSB                                   0xE4
#define _P15_A4_PT_E5_TC13_HS_LSB                                   0xE5
#define _P15_A4_PT_E6_TC13_HE_MSB                                   0xE6
#define _P15_A4_PT_E7_TC13_HE_LSB                                   0xE7
#define _P15_A4_PT_E8_TC13_CTRL                                     0xE8
#define _P15_A4_PT_E9_TC13_DOT_MASK                                 0xE9
#define _P15_A4_PT_EA_TC13_RESERVE                                  0xEA


//--------------------------------------------------
// CBUS0 MAC (Page 28)
//--------------------------------------------------
#define _P28_AD_PT_00_MSC_REG_00                                    0x00
#define _P28_AD_PT_01_MSC_REG_01                                    0x01
#define _P28_AD_PT_02_MSC_REG_02                                    0x02
#define _P28_AD_PT_03_MSC_REG_03                                    0x03
#define _P28_AD_PT_04_MSC_REG_04                                    0x04
#define _P28_AD_PT_05_MSC_REG_05                                    0x05
#define _P28_AD_PT_06_MSC_REG_06                                    0x06
#define _P28_AD_PT_07_MSC_REG_07                                    0x07
#define _P28_AD_PT_08_MSC_REG_08                                    0x08
#define _P28_AD_PT_09_MSC_REG_09                                    0x09
#define _P28_AD_PT_0A_MSC_REG_0A                                    0x0A
#define _P28_AD_PT_0B_MSC_REG_0B                                    0x0B
#define _P28_AD_PT_0C_MSC_REG_0C                                    0x0C
#define _P28_AD_PT_0D_MSC_REG_0D                                    0x0D
#define _P28_AD_PT_0E_MSC_REG_0E                                    0x0E
#define _P28_AD_PT_0F_MSC_REG_0F                                    0x0F
#define _P28_AD_PT_20_MSC_REG_20                                    0x20
#define _P28_AD_PT_21_MSC_REG_21                                    0x21
#define _P28_AD_PT_22_MSC_REG_22                                    0x22
#define _P28_AD_PT_23_MSC_REG_23                                    0x23
#define _P28_AD_PT_24_MSC_REG_24                                    0x24
#define _P28_AD_PT_25_MSC_REG_25                                    0x25
#define _P28_AD_PT_26_MSC_REG_26                                    0x26
#define _P28_AD_PT_27_MSC_REG_27                                    0x27
#define _P28_AD_PT_30_MSC_REG_30                                    0x30
#define _P28_AD_PT_31_MSC_REG_31                                    0x31
#define _P28_AD_PT_32_MSC_REG_32                                    0x32
#define _P28_AD_PT_33_MSC_REG_33                                    0x33
#define _P28_AD_PT_34_MSC_REG_34                                    0x34
#define _P28_AD_PT_35_MSC_REG_35                                    0x35
#define _P28_AD_PT_36_MSC_REG_36                                    0x36
#define _P28_AD_PT_37_MSC_REG_37                                    0x37
#define _P28_AD_PT_40_MSC_REG_40                                    0x40
#define _P28_AD_PT_41_MSC_REG_41                                    0x41
#define _P28_AD_PT_42_MSC_REG_42                                    0x42
#define _P28_AD_PT_43_MSC_REG_43                                    0x43
#define _P28_AD_PT_44_MSC_REG_44                                    0x44
#define _P28_AD_PT_45_MSC_REG_45                                    0x45
#define _P28_AD_PT_46_MSC_REG_46                                    0x46
#define _P28_AD_PT_47_MSC_REG_47                                    0x47
#define _P28_AD_PT_48_MSC_REG_48                                    0x48
#define _P28_AD_PT_49_MSC_REG_49                                    0x49
#define _P28_AD_PT_4A_MSC_REG_4A                                    0x4A
#define _P28_AD_PT_4B_MSC_REG_4B                                    0x4B
#define _P28_AD_PT_4C_MSC_REG_4C                                    0x4C
#define _P28_AD_PT_4D_MSC_REG_4D                                    0x4D
#define _P28_AD_PT_4E_MSC_REG_4E                                    0x4E
#define _P28_AD_PT_4F_MSC_REG_4F                                    0x4F
#define _P28_AD_PT_50_MSC_REG_50                                    0x50
#define _P28_AD_PT_51_MSC_REG_51                                    0x51
#define _P28_AD_PT_52_MSC_REG_52                                    0x52
#define _P28_AD_PT_53_MSC_REG_53                                    0x53
#define _P28_AD_PT_54_MSC_REG_54                                    0x54
#define _P28_AD_PT_55_MSC_REG_55                                    0x55
#define _P28_AD_PT_56_MSC_REG_56                                    0x56
#define _P28_AD_PT_57_MSC_REG_57                                    0x57
#define _P28_AD_PT_58_MSC_REG_58                                    0x58
#define _P28_AD_PT_59_MSC_REG_59                                    0x59
#define _P28_AD_PT_5A_MSC_REG_5A                                    0x5A
#define _P28_AD_PT_5B_MSC_REG_5B                                    0x5B
#define _P28_AD_PT_5C_MSC_REG_5C                                    0x5C
#define _P28_AD_PT_5D_MSC_REG_5D                                    0x5D
#define _P28_AD_PT_5E_MSC_REG_5E                                    0x5E
#define _P28_AD_PT_5F_MSC_REG_5F                                    0x5F
#define _P28_AD_PT_80_MSC_REG_80                                    0x80
#define _P28_AD_PT_81_MSC_REG_81                                    0x81
#define _P28_AD_PT_82_MSC_REG_82                                    0x82
#define _P28_AD_PT_83_MSC_REG_83                                    0x83
#define _P28_AD_PT_84_MSC_REG_84                                    0x84
#define _P28_AD_PT_85_MSC_REG_85                                    0x85
#define _P28_AD_PT_86_MSC_REG_86                                    0x86
#define _P28_AD_PT_87_MSC_REG_87                                    0x87
#define _P28_AD_PT_88_MSC_REG_88                                    0x88
#define _P28_AD_PT_89_MSC_REG_89                                    0x89
#define _P28_AD_PT_8A_MSC_REG_8A                                    0x8A
#define _P28_AD_PT_8B_MSC_REG_8B                                    0x8B
#define _P28_AD_PT_8C_MSC_REG_8C                                    0x8C
#define _P28_AD_PT_8D_MSC_REG_8D                                    0x8D
#define _P28_AD_PT_8E_MSC_REG_8E                                    0x8E
#define _P28_AD_PT_8F_MSC_REG_8F                                    0x8F
#define _P28_AD_PT_90_MSC_REG_90                                    0x90
#define _P28_AD_PT_91_MSC_REG_91                                    0x91
#define _P28_AD_PT_92_MSC_REG_92                                    0x92
#define _P28_AD_PT_93_MSC_REG_93                                    0x93
#define _P28_AD_PT_94_MSC_REG_94                                    0x94
#define _P28_AD_PT_95_MSC_REG_95                                    0x95
#define _P28_AD_PT_96_MSC_REG_96                                    0x96
#define _P28_AD_PT_97_MSC_REG_97                                    0x97
#define _P28_AD_PT_98_MSC_REG_98                                    0x98
#define _P28_AD_PT_99_MSC_REG_99                                    0x99
#define _P28_AD_PT_9A_MSC_REG_9A                                    0x9A
#define _P28_AD_PT_9B_MSC_REG_9B                                    0x9B
#define _P28_AD_PT_9C_MSC_REG_9C                                    0x9C
#define _P28_AD_PT_9D_MSC_REG_9D                                    0x9D
#define _P28_AD_PT_9E_MSC_REG_9E                                    0x9E
#define _P28_AD_PT_9F_MSC_REG_9F                                    0x9F
#define _P28_AD_PT_A0_MSC_REG_A0                                    0xA0
#define _P28_AD_PT_A1_MSC_REG_A1                                    0xA1
#define _P28_AD_PT_A2_MSC_REG_A2                                    0xA2
#define _P28_AD_PT_A3_MSC_REG_A3                                    0xA3
#define _P28_AD_PT_A4_MSC_REG_A4                                    0xA4
#define _P28_AD_PT_A5_MSC_REG_A5                                    0xA5
#define _P28_AD_PT_A6_MSC_REG_A6                                    0xA6
#define _P28_AD_PT_A7_MSC_REG_A7                                    0xA7
#define _P28_AD_PT_A8_MSC_REG_A8                                    0xA8
#define _P28_AD_PT_A9_MSC_REG_A9                                    0xA9
#define _P28_AD_PT_AA_MSC_REG_AA                                    0xAA
#define _P28_AD_PT_AB_MSC_REG_AB                                    0xAB
#define _P28_AD_PT_AC_MSC_REG_AC                                    0xAC
#define _P28_AD_PT_AD_MSC_REG_AD                                    0xAD
#define _P28_AD_PT_AE_MSC_REG_AE                                    0xAE
#define _P28_AD_PT_AF_MSC_REG_AF                                    0xAF
#define _P28_FC_PT_00_MISC_CTRL_00                                  0x00
#define _P28_FC_PT_01_MISC_CTRL_01                                  0x01
#define _P28_FC_PT_02_MISC_CTRL_02                                  0x02
#define _P28_FC_PT_03_MISC_CTRL_03                                  0x03
#define _P28_FC_PT_04_MISC_CTRL_04                                  0x04
#define _P28_FC_PT_08_MISC_CTRL_08                                  0x08
#define _P28_FC_PT_09_MISC_CTRL_09                                  0x09
#define _P28_FC_PT_0A_MISC_CTRL_0A                                  0x0A
#define _P28_FC_PT_0B_MISC_CTRL_0B                                  0x0B
#define _P28_FC_PT_0C_MISC_CTRL_0C                                  0x0C
#define _P28_FC_PT_0D_MISC_CTRL_0D                                  0x0D
#define _P28_FC_PT_0E_MISC_CTRL_0E                                  0x0E
#define _P28_FC_PT_10_MISC_CTRL_10                                  0x10
#define _P28_FC_PT_11_MISC_CTRL_11                                  0x11
#define _P28_FC_PT_12_MISC_CTRL_12                                  0x12
#define _P28_FC_PT_13_MISC_CTRL_13                                  0x13
#define _P28_FC_PT_14_MISC_CTRL_14                                  0x14
#define _P28_FC_PT_15_MISC_CTRL_15                                  0x15
#define _P28_FC_PT_16_MISC_CTRL_16                                  0x16
#define _P28_FC_PT_17_MISC_CTRL_17                                  0x17
#define _P28_FC_PT_18_MISC_CTRL_18                                  0x18
#define _P28_FC_PT_20_MISC_CTRL_20                                  0x20
#define _P28_FC_PT_21_MISC_CTRL_21                                  0x21
#define _P28_FC_PT_22_MISC_CTRL_22                                  0x22
#define _P28_FC_PT_23_MISC_CTRL_23                                  0x23
#define _P28_FC_PT_24_MISC_CTRL_24                                  0x24
#define _P28_FC_PT_25_MISC_CTRL_25                                  0x25
#define _P28_FC_PT_26_MISC_CTRL_26                                  0x26
#define _P28_FC_PT_27_MISC_CTRL_27                                  0x27
#define _P28_FC_PT_30_MISC_CTRL_30                                  0x30
#define _P28_FC_PT_31_MISC_CTRL_31                                  0x31
#define _P28_FC_PT_32_MISC_CTRL_32                                  0x32
#define _P28_FC_PT_40_MISC_CTRL_40                                  0x40
#define _P28_FC_PT_41_MISC_CTRL_41                                  0x41
#define _P28_FC_PT_42_MISC_CTRL_42                                  0x42
#define _P28_FC_PT_45_MISC_CTRL_43                                  0x45
#define _P28_FC_PT_46_MISC_CTRL_44                                  0x46
#define _P28_FC_PT_47_MISC_CTRL_45                                  0x47
#define _P28_FC_PT_48_MISC_CTRL_46                                  0x48
#define _P28_FC_PT_49_MISC_CTRL_47                                  0x49
#define _P28_FC_PT_4A_MISC_CTRL_48                                  0x4A
#define _P28_FC_PT_4B_MISC_CTRL_49                                  0x4B


//--------------------------------------------------
// CBUS1 MAC (Page 29)
//--------------------------------------------------
#define _P29_AD_PT_00_MSC_REG_00                                    0x00
#define _P29_AD_PT_01_MSC_REG_01                                    0x01
#define _P29_AD_PT_02_MSC_REG_02                                    0x02
#define _P29_AD_PT_03_MSC_REG_03                                    0x03
#define _P29_AD_PT_04_MSC_REG_04                                    0x04
#define _P29_AD_PT_05_MSC_REG_05                                    0x05
#define _P29_AD_PT_06_MSC_REG_06                                    0x06
#define _P29_AD_PT_07_MSC_REG_07                                    0x07
#define _P29_AD_PT_08_MSC_REG_08                                    0x08
#define _P29_AD_PT_09_MSC_REG_09                                    0x09
#define _P29_AD_PT_0A_MSC_REG_0A                                    0x0A
#define _P29_AD_PT_0B_MSC_REG_0B                                    0x0B
#define _P29_AD_PT_0C_MSC_REG_0C                                    0x0C
#define _P29_AD_PT_0D_MSC_REG_0D                                    0x0D
#define _P29_AD_PT_0E_MSC_REG_0E                                    0x0E
#define _P29_AD_PT_0F_MSC_REG_0F                                    0x0F
#define _P29_AD_PT_20_MSC_REG_20                                    0x20
#define _P29_AD_PT_21_MSC_REG_21                                    0x21
#define _P29_AD_PT_22_MSC_REG_22                                    0x22
#define _P29_AD_PT_23_MSC_REG_23                                    0x23
#define _P29_AD_PT_24_MSC_REG_24                                    0x24
#define _P29_AD_PT_25_MSC_REG_25                                    0x25
#define _P29_AD_PT_26_MSC_REG_26                                    0x26
#define _P29_AD_PT_27_MSC_REG_27                                    0x27
#define _P29_AD_PT_30_MSC_REG_30                                    0x30
#define _P29_AD_PT_31_MSC_REG_31                                    0x31
#define _P29_AD_PT_32_MSC_REG_32                                    0x32
#define _P29_AD_PT_33_MSC_REG_33                                    0x33
#define _P29_AD_PT_34_MSC_REG_34                                    0x34
#define _P29_AD_PT_35_MSC_REG_35                                    0x35
#define _P29_AD_PT_36_MSC_REG_36                                    0x36
#define _P29_AD_PT_37_MSC_REG_37                                    0x37
#define _P29_AD_PT_40_MSC_REG_40                                    0x40
#define _P29_AD_PT_41_MSC_REG_41                                    0x41
#define _P29_AD_PT_42_MSC_REG_42                                    0x42
#define _P29_AD_PT_43_MSC_REG_43                                    0x43
#define _P29_AD_PT_44_MSC_REG_44                                    0x44
#define _P29_AD_PT_45_MSC_REG_45                                    0x45
#define _P29_AD_PT_46_MSC_REG_46                                    0x46
#define _P29_AD_PT_47_MSC_REG_47                                    0x47
#define _P29_AD_PT_48_MSC_REG_48                                    0x48
#define _P29_AD_PT_49_MSC_REG_49                                    0x49
#define _P29_AD_PT_4A_MSC_REG_4A                                    0x4A
#define _P29_AD_PT_4B_MSC_REG_4B                                    0x4B
#define _P29_AD_PT_4C_MSC_REG_4C                                    0x4C
#define _P29_AD_PT_4D_MSC_REG_4D                                    0x4D
#define _P29_AD_PT_4E_MSC_REG_4E                                    0x4E
#define _P29_AD_PT_4F_MSC_REG_4F                                    0x4F
#define _P29_AD_PT_50_MSC_REG_50                                    0x50
#define _P29_AD_PT_51_MSC_REG_51                                    0x51
#define _P29_AD_PT_52_MSC_REG_52                                    0x52
#define _P29_AD_PT_53_MSC_REG_53                                    0x53
#define _P29_AD_PT_54_MSC_REG_54                                    0x54
#define _P29_AD_PT_55_MSC_REG_55                                    0x55
#define _P29_AD_PT_56_MSC_REG_56                                    0x56
#define _P29_AD_PT_57_MSC_REG_57                                    0x57
#define _P29_AD_PT_58_MSC_REG_58                                    0x58
#define _P29_AD_PT_59_MSC_REG_59                                    0x59
#define _P29_AD_PT_5A_MSC_REG_5A                                    0x5A
#define _P29_AD_PT_5B_MSC_REG_5B                                    0x5B
#define _P29_AD_PT_5C_MSC_REG_5C                                    0x5C
#define _P29_AD_PT_5D_MSC_REG_5D                                    0x5D
#define _P29_AD_PT_5E_MSC_REG_5E                                    0x5E
#define _P29_AD_PT_5F_MSC_REG_5F                                    0x5F
#define _P29_AD_PT_80_MSC_REG_80                                    0x80
#define _P29_AD_PT_81_MSC_REG_81                                    0x81
#define _P29_AD_PT_82_MSC_REG_82                                    0x82
#define _P29_AD_PT_83_MSC_REG_83                                    0x83
#define _P29_AD_PT_84_MSC_REG_84                                    0x84
#define _P29_AD_PT_85_MSC_REG_85                                    0x85
#define _P29_AD_PT_86_MSC_REG_86                                    0x86
#define _P29_AD_PT_87_MSC_REG_87                                    0x87
#define _P29_AD_PT_88_MSC_REG_88                                    0x88
#define _P29_AD_PT_89_MSC_REG_89                                    0x89
#define _P29_AD_PT_8A_MSC_REG_8A                                    0x8A
#define _P29_AD_PT_8B_MSC_REG_8B                                    0x8B
#define _P29_AD_PT_8C_MSC_REG_8C                                    0x8C
#define _P29_AD_PT_8D_MSC_REG_8D                                    0x8D
#define _P29_AD_PT_8E_MSC_REG_8E                                    0x8E
#define _P29_AD_PT_8F_MSC_REG_8F                                    0x8F
#define _P29_AD_PT_90_MSC_REG_90                                    0x90
#define _P29_AD_PT_91_MSC_REG_91                                    0x91
#define _P29_AD_PT_92_MSC_REG_92                                    0x92
#define _P29_AD_PT_93_MSC_REG_93                                    0x93
#define _P29_AD_PT_94_MSC_REG_94                                    0x94
#define _P29_AD_PT_95_MSC_REG_95                                    0x95
#define _P29_AD_PT_96_MSC_REG_96                                    0x96
#define _P29_AD_PT_97_MSC_REG_97                                    0x97
#define _P29_AD_PT_98_MSC_REG_98                                    0x98
#define _P29_AD_PT_99_MSC_REG_99                                    0x99
#define _P29_AD_PT_9A_MSC_REG_9A                                    0x9A
#define _P29_AD_PT_9B_MSC_REG_9B                                    0x9B
#define _P29_AD_PT_9C_MSC_REG_9C                                    0x9C
#define _P29_AD_PT_9D_MSC_REG_9D                                    0x9D
#define _P29_AD_PT_9E_MSC_REG_9E                                    0x9E
#define _P29_AD_PT_9F_MSC_REG_9F                                    0x9F
#define _P29_AD_PT_A0_MSC_REG_A0                                    0xA0
#define _P29_AD_PT_A1_MSC_REG_A1                                    0xA1
#define _P29_AD_PT_A2_MSC_REG_A2                                    0xA2
#define _P29_AD_PT_A3_MSC_REG_A3                                    0xA3
#define _P29_AD_PT_A4_MSC_REG_A4                                    0xA4
#define _P29_AD_PT_A5_MSC_REG_A5                                    0xA5
#define _P29_AD_PT_A6_MSC_REG_A6                                    0xA6
#define _P29_AD_PT_A7_MSC_REG_A7                                    0xA7
#define _P29_AD_PT_A8_MSC_REG_A8                                    0xA8
#define _P29_AD_PT_A9_MSC_REG_A9                                    0xA9
#define _P29_AD_PT_AA_MSC_REG_AA                                    0xAA
#define _P29_AD_PT_AB_MSC_REG_AB                                    0xAB
#define _P29_AD_PT_AC_MSC_REG_AC                                    0xAC
#define _P29_AD_PT_AD_MSC_REG_AD                                    0xAD
#define _P29_AD_PT_AE_MSC_REG_AE                                    0xAE
#define _P29_AD_PT_AF_MSC_REG_AF                                    0xAF
#define _P29_FC_PT_00_MISC_CTRL_00                                  0x00
#define _P29_FC_PT_01_MISC_CTRL_01                                  0x01
#define _P29_FC_PT_02_MISC_CTRL_02                                  0x02
#define _P29_FC_PT_03_MISC_CTRL_03                                  0x03
#define _P29_FC_PT_04_MISC_CTRL_04                                  0x04
#define _P29_FC_PT_08_MISC_CTRL_08                                  0x08
#define _P29_FC_PT_09_MISC_CTRL_09                                  0x09
#define _P29_FC_PT_0A_MISC_CTRL_0A                                  0x0A
#define _P29_FC_PT_0B_MISC_CTRL_0B                                  0x0B
#define _P29_FC_PT_0C_MISC_CTRL_0C                                  0x0C
#define _P29_FC_PT_0D_MISC_CTRL_0D                                  0x0D
#define _P29_FC_PT_0E_MISC_CTRL_0E                                  0x0E
#define _P29_FC_PT_10_MISC_CTRL_10                                  0x10
#define _P29_FC_PT_11_MISC_CTRL_11                                  0x11
#define _P29_FC_PT_12_MISC_CTRL_12                                  0x12
#define _P29_FC_PT_13_MISC_CTRL_13                                  0x13
#define _P29_FC_PT_14_MISC_CTRL_14                                  0x14
#define _P29_FC_PT_15_MISC_CTRL_15                                  0x15
#define _P29_FC_PT_16_MISC_CTRL_16                                  0x16
#define _P29_FC_PT_17_MISC_CTRL_17                                  0x17
#define _P29_FC_PT_18_MISC_CTRL_18                                  0x18
#define _P29_FC_PT_20_MISC_CTRL_20                                  0x20
#define _P29_FC_PT_21_MISC_CTRL_21                                  0x21
#define _P29_FC_PT_22_MISC_CTRL_22                                  0x22
#define _P29_FC_PT_23_MISC_CTRL_23                                  0x23
#define _P29_FC_PT_24_MISC_CTRL_24                                  0x24
#define _P29_FC_PT_25_MISC_CTRL_25                                  0x25
#define _P29_FC_PT_26_MISC_CTRL_26                                  0x26
#define _P29_FC_PT_27_MISC_CTRL_27                                  0x27
#define _P29_FC_PT_30_MISC_CTRL_30                                  0x30
#define _P29_FC_PT_31_MISC_CTRL_31                                  0x31
#define _P29_FC_PT_32_MISC_CTRL_32                                  0x32
#define _P29_FC_PT_40_MISC_CTRL_40                                  0x40
#define _P29_FC_PT_41_MISC_CTRL_41                                  0x41
#define _P29_FC_PT_42_MISC_CTRL_42                                  0x42
#define _P29_FC_PT_45_MISC_CTRL_43                                  0x45
#define _P29_FC_PT_46_MISC_CTRL_44                                  0x46
#define _P29_FC_PT_47_MISC_CTRL_45                                  0x47
#define _P29_FC_PT_48_MISC_CTRL_46                                  0x48
#define _P29_FC_PT_49_MISC_CTRL_47                                  0x49
#define _P29_FC_PT_4A_MISC_CTRL_48                                  0x4A
#define _P29_FC_PT_4B_MISC_CTRL_49                                  0x4B


//--------------------------------------------------
// USB 2.0 EHCI Host Controller (Page 61)
//--------------------------------------------------
#define _P61_04_PT_000_EHCI_CAP_LENGTH                              0x0000
#define _P61_04_PT_000_EHCI_CAP_RSV                                 0x0001
#define _P61_04_PT_000_EHCI_HCI_VERSION_0                           0x0002
#define _P61_04_PT_000_EHCI_HCI_VERSION_1                           0x0003
#define _P61_04_PT_004_EHCI_HCS_PARAMS_0                            0x0040
#define _P61_04_PT_004_EHCI_HCS_PARAMS_1                            0x0041
#define _P61_04_PT_004_EHCI_HCS_PARAMS_2                            0x0042
#define _P61_04_PT_004_EHCI_HCS_PARAMS_3                            0x0043
#define _P61_04_PT_008_EHCI_HCC_PARAMS_0                            0x0080
#define _P61_04_PT_008_EHCI_HCC_PARAMS_1                            0x0081
#define _P61_04_PT_008_EHCI_HCC_PARAMS_2                            0x0082
#define _P61_04_PT_008_EHCI_HCC_PARAMS_3                            0x0083
#define _P61_04_PT_00C_EHCI_HCSP_PORTROUTE_0                        0x00C0
#define _P61_04_PT_00C_EHCI_HCSP_PORTROUTE_1                        0x00C1
#define _P61_04_PT_00C_EHCI_HCSP_PORTROUTE_2                        0x00C2
#define _P61_04_PT_00C_EHCI_HCSP_PORTROUTE_3                        0x00C3
#define _P61_04_PT_010_EHCI_USB_CMD_0                               0x0100
#define _P61_04_PT_010_EHCI_USB_CMD_1                               0x0101
#define _P61_04_PT_010_EHCI_USB_CMD_2                               0x0102
#define _P61_04_PT_010_EHCI_USB_CMD_3                               0x0103
#define _P61_04_PT_014_EHCI_USB_STS_0                               0x0140
#define _P61_04_PT_014_EHCI_USB_STS_1                               0x0141
#define _P61_04_PT_014_EHCI_USB_STS_2                               0x0142
#define _P61_04_PT_014_EHCI_USB_STS_3                               0x0143
#define _P61_04_PT_018_EHCI_USB_INTR_0                              0x0180
#define _P61_04_PT_018_EHCI_USB_INTR_1                              0x0181
#define _P61_04_PT_018_EHCI_USB_INTR_2                              0x0182
#define _P61_04_PT_018_EHCI_USB_INTR_3                              0x0183
#define _P61_04_PT_01C_EHCI_FRINDEX_0                               0x01C0
#define _P61_04_PT_01C_EHCI_FRINDEX_1                               0x01C1
#define _P61_04_PT_01C_EHCI_FRINDEX_2                               0x01C2
#define _P61_04_PT_01C_EHCI_FRINDEX_3                               0x01C3
#define _P61_04_PT_020_EHCI_CTRLDS_SEGMENT_0                        0x0200
#define _P61_04_PT_020_EHCI_CTRLDS_SEGMENT_1                        0x0201
#define _P61_04_PT_020_EHCI_CTRLDS_SEGMENT_2                        0x0202
#define _P61_04_PT_020_EHCI_CTRLDS_SEGMENT_3                        0x0203
#define _P61_04_PT_024_EHCI_PERIODIC_LIST_BASE_0                    0x0240
#define _P61_04_PT_024_EHCI_PERIODIC_LIST_BASE_1                    0x0241
#define _P61_04_PT_024_EHCI_PERIODIC_LIST_BASE_2                    0x0242
#define _P61_04_PT_024_EHCI_PERIODIC_LIST_BASE_3                    0x0243
#define _P61_04_PT_028_EHCI_ASYNC_LIST_ADDR_0                       0x0280
#define _P61_04_PT_028_EHCI_ASYNC_LIST_ADDR_1                       0x0281
#define _P61_04_PT_028_EHCI_ASYNC_LIST_ADDR_2                       0x0282
#define _P61_04_PT_028_EHCI_ASYNC_LIST_ADDR_3                       0x0283
#define _P61_04_PT_050_EHCI_CONFIG_FLAG_0                           0x0500
#define _P61_04_PT_050_EHCI_CONFIG_FLAG_1                           0x0501
#define _P61_04_PT_050_EHCI_CONFIG_FLAG_2                           0x0502
#define _P61_04_PT_050_EHCI_CONFIG_FLAG_3                           0x0503
#define _P61_04_PT_054_EHCI_PORTSC_0                                0x0540
#define _P61_04_PT_054_EHCI_PORTSC_1                                0x0541
#define _P61_04_PT_054_EHCI_PORTSC_2                                0x0542
#define _P61_04_PT_054_EHCI_PORTSC_3                                0x0543
#define _P61_04_PT_090_EHCI_INSNREG00_0                             0x0900
#define _P61_04_PT_090_EHCI_INSNREG00_1                             0x0901
#define _P61_04_PT_090_EHCI_INSNREG00_2                             0x0902
#define _P61_04_PT_090_EHCI_INSNREG00_3                             0x0903
#define _P61_04_PT_094_EHCI_INSNREG01_0                             0x0940
#define _P61_04_PT_094_EHCI_INSNREG01_1                             0x0941
#define _P61_04_PT_094_EHCI_INSNREG01_2                             0x0942
#define _P61_04_PT_094_EHCI_INSNREG01_3                             0x0943
#define _P61_04_PT_098_EHCI_INSNREG02_0                             0x0980
#define _P61_04_PT_098_EHCI_INSNREG02_1                             0x0981
#define _P61_04_PT_098_EHCI_INSNREG02_2                             0x0982
#define _P61_04_PT_098_EHCI_INSNREG02_3                             0x0983
#define _P61_04_PT_09C_EHCI_INSNREG03_0                             0x09C0
#define _P61_04_PT_09C_EHCI_INSNREG03_1                             0x09C1
#define _P61_04_PT_09C_EHCI_INSNREG03_2                             0x09C2
#define _P61_04_PT_09C_EHCI_INSNREG03_3                             0x09C3
#define _P61_04_PT_0A0_EHCI_INSNREG04_0                             0x0A00
#define _P61_04_PT_0A0_EHCI_INSNREG04_1                             0x0A01
#define _P61_04_PT_0A0_EHCI_INSNREG04_2                             0x0A02
#define _P61_04_PT_0A0_EHCI_INSNREG04_3                             0x0A03
#define _P61_04_PT_0A4_EHCI_INSNREG05_0                             0x0A40
#define _P61_04_PT_0A4_EHCI_INSNREG05_1                             0x0A41
#define _P61_04_PT_0A4_EHCI_INSNREG05_2                             0x0A42
#define _P61_04_PT_0A4_EHCI_INSNREG05_3                             0x0A43
#define _P61_04_PT_0A8_EHCI_INSNREG06_0                             0x0A80
#define _P61_04_PT_0A8_EHCI_INSNREG06_1                             0x0A81
#define _P61_04_PT_0A8_EHCI_INSNREG06_2                             0x0A82
#define _P61_04_PT_0A8_EHCI_INSNREG06_3                             0x0A83
#define _P61_04_PT_0AC_EHCI_INSNREG07_0                             0x0AC0
#define _P61_04_PT_0AC_EHCI_INSNREG07_1                             0x0AC1
#define _P61_04_PT_0AC_EHCI_INSNREG07_2                             0x0AC2
#define _P61_04_PT_0AC_EHCI_INSNREG07_3                             0x0AC3

//--------------------------------------------------
// USB OHCI Host Controller (Page 61)
//--------------------------------------------------
#define _P61_04_PT_100_OHCI_HCREVISION_0                            0x1000
#define _P61_04_PT_100_OHCI_HCREVISION_1                            0x1001
#define _P61_04_PT_100_OHCI_HCREVISION_2                            0x1002
#define _P61_04_PT_100_OHCI_HCREVISION_3                            0x1003
#define _P61_04_PT_104_OHCI_HCCONTROL_0                             0x1040
#define _P61_04_PT_104_OHCI_HCCONTROL_1                             0x1041
#define _P61_04_PT_104_OHCI_HCCONTROL_2                             0x1042
#define _P61_04_PT_104_OHCI_HCCONTROL_3                             0x1043
#define _P61_04_PT_108_OHCI_HCCOMMAND_STS_0                         0x1080
#define _P61_04_PT_108_OHCI_HCCOMMAND_STS_1                         0x1081
#define _P61_04_PT_108_OHCI_HCCOMMAND_STS_2                         0x1082
#define _P61_04_PT_108_OHCI_HCCOMMAND_STS_3                         0x1083
#define _P61_04_PT_10C_OHCI_HCINTERRUPT_STS_0                       0x10C0
#define _P61_04_PT_10C_OHCI_HCINTERRUPT_STS_1                       0x10C1
#define _P61_04_PT_10C_OHCI_HCINTERRUPT_STS_2                       0x10C2
#define _P61_04_PT_10C_OHCI_HCINTERRUPT_STS_3                       0x10C3
#define _P61_04_PT_110_OHCI_HCINTERRUPT_EN_0                        0x1100
#define _P61_04_PT_110_OHCI_HCINTERRUPT_EN_1                        0x1101
#define _P61_04_PT_110_OHCI_HCINTERRUPT_EN_2                        0x1102
#define _P61_04_PT_110_OHCI_HCINTERRUPT_EN_3                        0x1103
#define _P61_04_PT_114_OHCI_HCINTERRUPT_DIS_0                       0x1140
#define _P61_04_PT_114_OHCI_HCINTERRUPT_DIS_1                       0x1141
#define _P61_04_PT_114_OHCI_HCINTERRUPT_DIS_2                       0x1142
#define _P61_04_PT_114_OHCI_HCINTERRUPT_DIS_3                       0x1143
#define _P61_04_PT_118_OHCI_HCCA_0                                  0x1180
#define _P61_04_PT_118_OHCI_HCCA_1                                  0x1181
#define _P61_04_PT_118_OHCI_HCCA_2                                  0x1182
#define _P61_04_PT_118_OHCI_HCCA_3                                  0x1183
#define _P61_04_PT_11C_OHCI_HCPERIODCURR_ED_0                       0x11C0
#define _P61_04_PT_11C_OHCI_HCPERIODCURR_ED_1                       0x11C1
#define _P61_04_PT_11C_OHCI_HCPERIODCURR_ED_2                       0x11C2
#define _P61_04_PT_11C_OHCI_HCPERIODCURR_ED_3                       0x11C3
#define _P61_04_PT_120_OHCI_HCCONTROLHEAD_ED_0                      0x1200
#define _P61_04_PT_120_OHCI_HCCONTROLHEAD_ED_1                      0x1201
#define _P61_04_PT_120_OHCI_HCCONTROLHEAD_ED_2                      0x1202
#define _P61_04_PT_120_OHCI_HCCONTROLHEAD_ED_3                      0x1203
#define _P61_04_PT_124_OHCI_HCCONTROLCURR_ED_0                      0x1240
#define _P61_04_PT_124_OHCI_HCCONTROLCURR_ED_1                      0x1241
#define _P61_04_PT_124_OHCI_HCCONTROLCURR_ED_2                      0x1242
#define _P61_04_PT_124_OHCI_HCCONTROLCURR_ED_3                      0x1243
#define _P61_04_PT_128_OHCI_HCBULK_ED_0                             0x1280
#define _P61_04_PT_128_OHCI_HCBULK_ED_1                             0x1281
#define _P61_04_PT_128_OHCI_HCBULK_ED_2                             0x1282
#define _P61_04_PT_128_OHCI_HCBULK_ED_3                             0x1283
#define _P61_04_PT_12C_OHCI_HCBULKCURR_ED_0                         0x12C0
#define _P61_04_PT_12C_OHCI_HCBULKCURR_ED_1                         0x12C1
#define _P61_04_PT_12C_OHCI_HCBULKCURR_ED_2                         0x12C2
#define _P61_04_PT_12C_OHCI_HCBULKCURR_ED_3                         0x12C3
#define _P61_04_PT_130_OHCI_HCDONEHEAD_0                            0x1300
#define _P61_04_PT_130_OHCI_HCDONEHEAD_1                            0x1301
#define _P61_04_PT_130_OHCI_HCDONEHEAD_2                            0x1302
#define _P61_04_PT_130_OHCI_HCDONEHEAD_3                            0x1303
#define _P61_04_PT_134_OHCI_HCFMINTERVAL_0                          0x1340
#define _P61_04_PT_134_OHCI_HCFMINTERVAL_1                          0x1341
#define _P61_04_PT_134_OHCI_HCFMINTERVAL_2                          0x1342
#define _P61_04_PT_134_OHCI_HCFMINTERVAL_3                          0x1343
#define _P61_04_PT_138_OHCI_HCFMREMAINING_0                         0x1380
#define _P61_04_PT_138_OHCI_HCFMREMAINING_1                         0x1381
#define _P61_04_PT_138_OHCI_HCFMREMAINING_2                         0x1382
#define _P61_04_PT_138_OHCI_HCFMREMAINING_3                         0x1383
#define _P61_04_PT_13C_OHCI_HCFMNUMBER_0                            0x13C0
#define _P61_04_PT_13C_OHCI_HCFMNUMBER_1                            0x13C1
#define _P61_04_PT_13C_OHCI_HCFMNUMBER_2                            0x13C2
#define _P61_04_PT_13C_OHCI_HCFMNUMBER_3                            0x13C3
#define _P61_04_PT_140_OHCI_HCPERIODICSTART_0                       0x1400
#define _P61_04_PT_140_OHCI_HCPERIODICSTART_1                       0x1401
#define _P61_04_PT_140_OHCI_HCPERIODICSTART_2                       0x1402
#define _P61_04_PT_140_OHCI_HCPERIODICSTART_3                       0x1403
#define _P61_04_PT_144_OHCI_HCLSTHRESHOLD_0                         0x1440
#define _P61_04_PT_144_OHCI_HCLSTHRESHOLD_1                         0x1441
#define _P61_04_PT_144_OHCI_HCLSTHRESHOLD_2                         0x1442
#define _P61_04_PT_144_OHCI_HCLSTHRESHOLD_3                         0x1443
#define _P61_04_PT_148_OHCI_HCRHDESCRIPTORA_0                       0x1480
#define _P61_04_PT_148_OHCI_HCRHDESCRIPTORA_1                       0x1481
#define _P61_04_PT_148_OHCI_HCRHDESCRIPTORA_2                       0x1482
#define _P61_04_PT_148_OHCI_HCRHDESCRIPTORA_3                       0x1483
#define _P61_04_PT_14C_OHCI_HCRHDESCRIPTORB_0                       0x14C0
#define _P61_04_PT_14C_OHCI_HCRHDESCRIPTORB_1                       0x14C1
#define _P61_04_PT_14C_OHCI_HCRHDESCRIPTORB_2                       0x14C2
#define _P61_04_PT_14C_OHCI_HCRHDESCRIPTORB_3                       0x14C3
#define _P61_04_PT_150_OHCI_HCRHSTATUS_0                            0x1500
#define _P61_04_PT_150_OHCI_HCRHSTATUS_1                            0x1501
#define _P61_04_PT_150_OHCI_HCRHSTATUS_2                            0x1502
#define _P61_04_PT_150_OHCI_HCRHSTATUS_3                            0x1503
#define _P61_04_PT_154_OHCI_HCRHPORTSTATUS_0                        0x1540
#define _P61_04_PT_154_OHCI_HCRHPORTSTATUS_1                        0x1541
#define _P61_04_PT_154_OHCI_HCRHPORTSTATUS_2                        0x1542
#define _P61_04_PT_154_OHCI_HCRHPORTSTATUS_3                        0x1543
#define _P61_04_PT_198_OHCI_INSNREG06_0                             0x1980
#define _P61_04_PT_198_OHCI_INSNREG06_1                             0x1981
#define _P61_04_PT_198_OHCI_INSNREG06_2                             0x1982
#define _P61_04_PT_198_OHCI_INSNREG06_3                             0x1983
#define _P61_04_PT_19C_OHCI_INSNREG07_0                             0x19C0
#define _P61_04_PT_19C_OHCI_INSNREG07_1                             0x19C1
#define _P61_04_PT_19C_OHCI_INSNREG07_2                             0x19C2
#define _P61_04_PT_19C_OHCI_INSNREG07_3                             0x19C3

//--------------------------------------------------
// USB 2.0 PHY (Page 61)
//--------------------------------------------------
#define _P61_62_PT_E0_USB_PHY_CTR_REG_0                             0xE0
#define _P61_62_PT_E1_USB_PHY_CTR_REG_1                             0xE1
#define _P61_62_PT_E2_USB_PHY_CTR_REG_2                             0xE2
#define _P61_62_PT_E3_USB_PHY_CTR_REG_3                             0xE3
#define _P61_62_PT_E4_USB_PHY_CTR_REG_4                             0xE4
#define _P61_62_PT_E5_USB_PHY_CTR_REG_5                             0xE5
#define _P61_62_PT_E6_USB_PHY_CTR_REG_6                             0xE6
#define _P61_62_PT_E7_USB_PHY_CTR_REG_7                             0xE7
#define _P61_62_PT_F0_USB_PHY_CTR_REG_8                             0xF0
#define _P61_62_PT_F1_USB_PHY_CTR_REG_9                             0xF1
#define _P61_62_PT_F2_USB_PHY_CTR_REG_A                             0xF2
#define _P61_62_PT_F3_USB_PHY_CTR_REG_B                             0xF3
#define _P61_62_PT_F4_USB_PHY_CTR_REG_C                             0xF4
#define _P61_62_PT_F5_USB_PHY_CTR_REG_D                             0xF5
#define _P61_62_PT_F6_USB_PHY_CTR_REG_E                             0xF6
#define _P61_62_PT_F7_USB_PHY_CTR_REG_F                             0xF7
#define _P61_62_PT_E0_USB_PHY_CTR_REG_10                            0xE0
#define _P61_62_PT_E1_USB_PHY_CTR_REG_11                            0xE1

//--------------------------------------------------
// Chip Control (Page 0)
//--------------------------------------------------
#define P0_00_ID_REG                                                0x0000
#define P0_01_HOST_CTRL                                             0x0001
#define P0_0E_I_D_MAPPING                                           0x000E
#define P0_0F_ID_REG_02                                             0x000F


//--------------------------------------------------
// IRQ Status (Page 0)
//--------------------------------------------------
#define P0_02_STATUS0                                               0x0002
#define P0_03_STATUS1                                               0x0003
#define P0_04_IRQ_CTRL0                                             0x0004
#define P0_05_IRQ_CTRL1                                             0x0005
#define P0_06_TOP_DUMMY1                                            0x0006
#define P0_07_RESERVED_STATUS                                       0x0007
#define P0_08_IRQ_CTRL2                                             0x0008


//--------------------------------------------------
// Power Control (Page 0)
//--------------------------------------------------
#define P0_09_TOP_POWER_CTRL                                        0x0009
#define P0_0A_GDI_POWER_CTRL                                        0x000A
#define P0_0B_POWER_CTRL                                            0x000B


//--------------------------------------------------
// Watch Dog (Page 0)
//--------------------------------------------------
#define P0_0C_WATCH_DOG_CTRL0                                       0x000C
#define P0_0D_TOP_DUMMY2                                            0x000D


//--------------------------------------------------
// Input Video Capture (Page 0)
//--------------------------------------------------
#define P0_10_M1_VGIP_CTRL                                          0x0010
#define P0_11_M1_VGIP_SIGINV                                        0x0011
#define P0_12_M1_VGIP_DELAY_CTRL                                    0x0012
#define P0_13_M1_VGIP_ODD_CTRL                                      0x0013


//--------------------------------------------------
// Input Frame Window (Page 0)
//--------------------------------------------------
#define P0_14_M1_IPH_ACT_STA_H                                      0x0014
#define P0_15_M1_IPH_ACT_STA_L                                      0x0015
#define P0_16_M1_IPH_ACT_WID_H                                      0x0016
#define P0_17_M1_IPH_ACT_WID_L                                      0x0017
#define P0_18_M1_IPV_ACT_STA_H                                      0x0018
#define P0_19_M1_IPV_ACT_STA_L                                      0x0019
#define P0_1A_M1_IPV_ACT_LEN_H                                      0x001A
#define P0_1B_M1_IPV_ACT_LEN_L                                      0x001B
#define P0_1C_M1_IVS_DELAY                                          0x001C
#define P0_1D_M1_IHS_DELAY                                          0x001D
#define P0_1E_M1_VGIP_HV_DELAY                                      0x001E
#define P0_1F_M1_ICLK_GATED_CTRL1                                   0x001F
#define P0_20_M1_DUMMY2                                             0x0020
#define P0_21_M1_I_DOMAIN_TEST_SELECT                               0x0021


//--------------------------------------------------
// FIFO Frequency (Page 0)
//--------------------------------------------------
#define P0_22_M1_FIFO_CLOCK_SELECT                                  0x0022


//--------------------------------------------------
// Scaling Down Control (Page 0)
//--------------------------------------------------
#define P0_23_SCALE_DOWN_CTRL_M1                                    0x0023
#define P0_24_SD_ADDRESS_PORT_M1                                    0x0024
#define P0_25_SD_DATA_PORT_M1                                       0x0025
#define P0_26_SD_FILTER_CONTROL_REG_M1                              0x0026


//--------------------------------------------------
// Display Format (Page 0)
//--------------------------------------------------
#define P0_28_VIDEO_DISPLAY_CONTROL_REG                             0x0028
#define P0_29_VDISP_SIGINV                                          0x0029
#define P0_2A_DISPLAY_FORMAT_ADDR_PORT                              0x002A
#define P0_2B_DISPLAY_FORMAT_DATA_PORT                              0x002B
#define P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER                          0x002F


//--------------------------------------------------
// FIFO Window (Page 0)
//--------------------------------------------------
#define P0_30_FIFO_WINDOW_ADDR_PORT                                 0x0030
#define P0_31_FIFO_WINDOW_DATA_PORT                                 0x0031


//--------------------------------------------------
// Scaling Up Function (Page 0)
//--------------------------------------------------
#define P0_32_SCALE_CONTROL_REG                                     0x0032
#define P0_33_SF_ADDR_PORT                                          0x0033
#define P0_34_SF_DATA_PORT                                          0x0034
#define P0_35_FILTER_CONTROL_REG                                    0x0035
#define P0_36_USER_DEF_FILTER_ACCESS_PORT                           0x0036
#define P0_37_SCALE_UP_FOR_LINE_INTERLEAVE                          0x0037


//--------------------------------------------------
// Frame Sync Fine Tune (Page 0)
//--------------------------------------------------
#define P0_3D_IV_DV_DELAY_CLK_FINE                                  0x003D
#define P0_3E_IVS2DVS_DLY_LINE_H                                    0x003E
#define P0_3F_DISPLAY_ALIGN_CONTROL                                 0x003F
#define P0_40_IVS2DVS_DLY_LINE_L                                    0x0040
#define P0_41_IVS2DVS_DLY_TUNE_ODD                                  0x0041
#define P0_42_IVS2DVS_DLY_TUNE_EVEN                                 0x0042
#define P0_43_FS_DELAY_FINE_TUNE                                    0x0043
#define P0_44_LAST_LINE_H                                           0x0044
#define P0_45_LAST_LINE_L                                           0x0045


//--------------------------------------------------
// Sync Processor Overview (Page 0)
//--------------------------------------------------
#define P0_47_SYNC_SELECT                                           0x0047
#define P0_48_SYNC_INVERT                                           0x0048
#define P0_49_SYNC_CTRL                                             0x0049
#define P0_4A_STABLE_HIGH_PERIOD_H                                  0x004A
#define P0_4B_STABLE_HIGH_PERIOD_L                                  0x004B
#define P0_4C_VSYNC_COUNTER_LEVEL_MSB                               0x004C
#define P0_4D_VSYNC_COUNTER_LEVEL_LSB                               0x004D
#define P0_4E_HSYNC_TYPE_DETECTION_FLAG                             0x004E
#define P0_4F_STABLE_MEASURE                                        0x004F
#define P0_50_STABLE_PERIOD_H                                       0x0050
#define P0_51_STABLE_PERIOD_L                                       0x0051
#define P0_52_STABLE_PERIOD_PULSE_H                                 0x0052
#define P0_5A_SYNC_TEST_MISC                                        0x005A
#define P0_5B_HS_DETECT                                             0x005B
#define P0_5C_SYNC_PROC_PORT_ADDR                                   0x005C
#define P0_5D_SYNC_PROC_PORT_DATA                                   0x005D
#define P0_5E_SYNCPROC_DUMMY0                                       0x005E
#define P0_5F_SYNCPROC_DUMMY1                                       0x005F


//--------------------------------------------------
// Highlight window (Page 0)
//--------------------------------------------------
#define P0_60_HLW_ADDR_PORT                                         0x0060
#define P0_61_HLW_DATA_PORT                                         0x0061


//--------------------------------------------------
// Color Processor Control (Page 0)
//--------------------------------------------------
#define P0_63_SRGB_ACCESS_PORT_SETA                                 0x0063
#define P0_68_GAMMA_BIST_DITHER_SETA                                0x0068


//--------------------------------------------------
// Contrast & Brightness (Page 0)
//--------------------------------------------------
#define P0_62_SRGB_CTRL                                             0x0062
#define P0_64_CTS_BRI_PORT_ADD                                      0x0064
#define P0_65_CTS_BRI_PORT_DATA                                     0x0065


//--------------------------------------------------
// Gamma Control (Page 0)
//--------------------------------------------------
#define P0_66_GAMMA_PORT_SETA                                       0x0066
#define P0_67_GAMMA_CTRL_SETA                                       0x0067


//--------------------------------------------------
// Dithering Control (For Display Domain) (Page 0)
//--------------------------------------------------
#define P0_69_D_DITHER_DATA_ACCESS                                  0x0069
#define P0_6A_D_DITHER_COMMON_CTRL1                                 0x006A
#define P0_6B_D_DITHER_REGISTER_ADDR                                0x006B


//--------------------------------------------------
// Back ground color (Page 0)
//--------------------------------------------------
#define P0_6C_OVERLAY_CTRL                                          0x006C
#define P0_6D_BG_COLOR_DATA_PORT_M1                                 0x006D
#define P0_8F_OVERLAY_CTRL1_M1                                      0x008F


//--------------------------------------------------
// OSD Color Palette (Page 0)
//--------------------------------------------------
#define P0_6E_OVERLAY_LUT_ADDR                                      0x006E
#define P0_6F_COLOR_LUT_PORT                                        0x006F


//--------------------------------------------------
// Image Auto Function (Page 0)
//--------------------------------------------------
#define P0_70_H_BOUNDARY_H                                          0x0070
#define P0_71_H_BOUNDARY_STA_L                                      0x0071
#define P0_72_H_BOUNDARY_END_L                                      0x0072
#define P0_73_V_BOUNDARY_H                                          0x0073
#define P0_74_V_BOUNDARY_STA_L                                      0x0074
#define P0_75_V_BOUNDARY_END_L                                      0x0075
#define P0_76_RED_NOISE_MARGIN                                      0x0076
#define P0_77_GRN_NOISE_MARGIN                                      0x0077
#define P0_78_BLU_NOISE_MARGIN                                      0x0078
#define P0_79_DIFF_THRESHOLD                                        0x0079
#define P0_7A_AUTO_ADJ_CTRL0                                        0x007A
#define P0_7B_HW_AUTO_PHASE_CTRL0                                   0x007B
#define P0_7C_AUTO_DUMMY                                            0x007C
#define P0_7D_AUTO_ADJ_CTRL1                                        0x007D
#define P0_7E_VER_START_END_H                                       0x007E
#define P0_7F_VER_START_L                                           0x007F
#define P0_80_VER_END_L                                             0x0080
#define P0_81_H_START_END_H                                         0x0081
#define P0_82_H_START_L                                             0x0082
#define P0_83_H_END_L                                               0x0083
#define P0_84_AUTO_PHASE_3                                          0x0084
#define P0_85_AUTO_PHASE_2                                          0x0085
#define P0_86_AUTO_PHASE_1                                          0x0086
#define P0_87_AUTO_PHASE_0                                          0x0087


//--------------------------------------------------
// Dithering Control (For Input Domain) (Page 0)
//--------------------------------------------------
#define P0_88_I_DITHER_DATA_ACCESS_SETA                             0x0088
#define P0_89_I_DITHER_COMMON_CTRL1_SETA                            0x0089
#define P0_8A_I_DITHER_COMMON_CTRL2_SETA                            0x008A


//--------------------------------------------------
// Test Function (Page 0)
//--------------------------------------------------
#define P0_8D_TEST_MODE_PORT_ADDR                                   0x008D
#define P0_8E_TEST_MODE_PORT_DATA                                   0x008E


//--------------------------------------------------
// OSD Access Port (Page 0)
//--------------------------------------------------
#define P0_90_OSD_ADR_PORT_MSB                                      0x0090
#define P0_91_OSD_ADR_PORT_LSB                                      0x0091
#define P0_92_OSD_DATA_PORT                                         0x0092
#define P0_93_OSD_MISC_PORT                                         0x0093
#define P0_94_OSD_WRITE_OPTION                                      0x0094


//--------------------------------------------------
// Digital Filter (Page 0)
//--------------------------------------------------
#define P0_98_DIGITAL_FILTER_CTRL                                   0x0098
#define P0_99_DIGITAL_FILTER_PORT                                   0x0099


//--------------------------------------------------
// Color Conversion - RGBtoYCC 10bit In / 10bit Out (Page 0)
//--------------------------------------------------
#define P0_9C_RGB2YCC_CTRL                                          0x009C
#define P0_9D_RGB2YCC_COEF_DATA                                     0x009D


//--------------------------------------------------
// Page Control(Page 0)
//--------------------------------------------------
#define P0_9F_PAGE_SEL                                              0x009F


//--------------------------------------------------
// Embedded ADC (Page 0)
//--------------------------------------------------
#define P0_BB_ADC_CK_IN_CTRL                                        0x00BB
#define P0_BC_ADC_CK_OUT_CTRL                                       0x00BC
#define P0_BD_ADC_TEST                                              0x00BD
#define P0_BE_ADC_GAI_LSB                                           0x00BE
#define P0_BF_ADC_OFF_LSB                                           0x00BF
#define P0_C0_ADC_GAI_RED_MSB                                       0x00C0
#define P0_C1_ADC_GAI_GRN_MSB                                       0x00C1
#define P0_C2_ADC_GAI_BLU_MSB                                       0x00C2
#define P0_C3_ADC_OFF_RED_MSB                                       0x00C3
#define P0_C4_ADC_OFF_GRN_MSB                                       0x00C4
#define P0_C5_ADC_OFF_BLU_MSB                                       0x00C5
#define P0_C6_ADC_POWER                                             0x00C6
#define P0_C7_ADC_VOLT_SEL                                          0x00C7
#define P0_C8_ADC_SF_CTRL                                           0x00C8
#define P0_C9_ADC_CLAMP_CTRL                                        0x00C9
#define P0_CD_ADC_COMPARE_FLAG                                      0x00CD
#define P0_CE_ADC_VMID_FINETUNE                                     0x00CE
#define P0_CF_ADC_CTL_RED                                           0x00CF
#define P0_D0_ADC_CTL_GRN                                           0x00D0
#define P0_D1_ADC_CTL_BLU                                           0x00D1
#define P0_D2_ADC_GAIN_CALI                                         0x00D2
#define P0_D3_ADC_OFF_LSB2                                          0x00D3
#define P0_D4_ADC_SOG_CTRL                                          0x00D4
#define P0_D5_ADC_SAR_CTRL                                          0x00D5
#define P0_D6_ADC_CLAMP_TOP                                         0x00D6
#define P0_D7_ADC_SOG_DAC                                           0x00D7
#define P0_D8_ADC_REG0                                              0x00D8
#define P0_D9_ADC_REG1                                              0x00D9
#define P0_DA_ADC_REG2                                              0x00DA


//--------------------------------------------------
// ABL (Page 0)
//--------------------------------------------------
#define P0_E2_AUTO_BLACK_LEVEL_CTRL1                                0x00E2
#define P0_E3_AUTO_BLACK_LEVEL_CTRL2                                0x00E3
#define P0_E4_AUTO_BLACK_LEVEL_CTRL3                                0x00E4
#define P0_E5_AUTO_BLACK_LEVEL_CTRL4                                0x00E5
#define P0_E6_AUTO_BLACK_LEVEL_CTRL5                                0x00E6
#define P0_E7_AUTO_BLACK_LEVEL_CTRL6                                0x00E7
#define P0_E8_AUTO_BLACK_LEVEL_CTRL7                                0x00E8
#define P0_E9_AUTO_BLACK_LEVEL_RED_VALUE                            0x00E9
#define P0_EA_AUTO_BLACK_LEVEL_GREEN_VALUE                          0x00EA
#define P0_EB_AUTO_BLACK_LEVEL_BLUE_VALUE                           0x00EB
#define P0_EC_AUTO_BLACK_LEVEL_R_NOISE_VALUE                        0x00EC
#define P0_ED_AUTO_BLACK_LEVEL_G_NOISE_VALUE                        0x00ED
#define P0_EE_AUTO_BLACK_LEVEL_B_NOISE_VALUE                        0x00EE
#define P0_EF_AUTO_BLACK_LEVEL_CTRL8                                0x00EF


//--------------------------------------------------
// LVR (Page 0)
//--------------------------------------------------
#define P0_F0_VCCKOFF_CONTROL0                                      0x00F0
#define P0_F1_VCCKOFF_CONTROL1                                      0x00F1
#define P0_F3_POWER_ON_RESET                                        0x00F3


//--------------------------------------------------
// Schmitt Trigger (Page 0)
//--------------------------------------------------
#define P0_F2_HS_SCHMITT_TRIGGE_CTRL2                               0x00F2
#define P0_F4_HS_SCHMITT_TRIGGE_CTRL                                0x00F4


//--------------------------------------------------
// MEMORY PLL (Page 0)
//--------------------------------------------------
#define P0_F5_MPLL_M                                                0x00F5
#define P0_F6_MPLL_N                                                0x00F6
#define P0_F7_MPLL_CRNT                                             0x00F7
#define P0_F8_MPLL_WD                                               0x00F8
#define P0_F9_MPLL_CAL                                              0x00F9


//--------------------------------------------------
// MCLK Spread Spectrum (Page 0)
//--------------------------------------------------
#define P0_FA_MCLK_FINE_TUNE_OFFSET_MSB                             0x00FA
#define P0_FB_MCLK_FINE_TUNE_OFFSET_LSB                             0x00FB
#define P0_FC_MCLK_SPREAD_SPECTRUM                                  0x00FC
#define P0_FD_MPLL_RESULT                                           0x00FD
#define P0_FE_MPLL_RESER                                            0x00FE
#define P0_FF_MPLL_M_N_MSB                                          0x00FF


//--------------------------------------------------
// APLL&DDS (Page 1)
//--------------------------------------------------
#define P1_A0_PLL_DIV_CTRL                                          0x01A0
#define P1_A1_I_CODE_M                                              0x01A1
#define P1_A2_I_CODE_L                                              0x01A2
#define P1_A3_P_CODE                                                0x01A3
#define P1_A4_PFD_CALIBRATED_RESULTS_H                              0x01A4
#define P1_A5_PFD_CALIBRATED_RESULTS_L                              0x01A5
#define P1_A6_PE_MEASURE_H                                          0x01A6
#define P1_A7_PE_MEASURE_L                                          0x01A7
#define P1_A8_PE_MAX_MEASURE_H                                      0x01A8
#define P1_A9_PE_MAX_MEASURE_L                                      0x01A9
#define P1_AA_FAST_PLL_CTRL                                         0x01AA
#define P1_AC_PLL_M                                                 0x01AC
#define P1_AD_PLL_N                                                 0x01AD
#define P1_AE_PLL_CRNT                                              0x01AE
#define P1_AF_PLL_WD                                                0x01AF
#define P1_B0_PLL_MIX                                               0x01B0
#define P1_B1_PLLDIV_H                                              0x01B1
#define P1_B2_PLLDIV_L                                              0x01B2
#define P1_B3_PLLPHASE_CTRL0                                        0x01B3
#define P1_B4_PLLPHASE_CTRL1                                        0x01B4
#define P1_B5_PLL_PHASE_INTERPOLATION                               0x01B5
#define P1_B6_P_CODE_MAPPING_METHOD                                 0x01B6
#define P1_B7_PE_TRACKING_METHOD                                    0x01B7
#define P1_B8_DDS_MIX_1                                             0x01B8
#define P1_B9_DDS_MIX_2                                             0x01B9
#define P1_BA_DDS_MIX_3                                             0x01BA
#define P1_BB_DDS_MIX_4                                             0x01BB
#define P1_BC_DDS_MIX_5                                             0x01BC
#define P1_BD_DDS_MIX_6                                             0x01BD
#define P1_BE_DDS_MIX_7                                             0x01BE
#define P1_F0_RESERVED_RG                                           0x01F0
#define P1_F1_APLL_RESERVED                                         0x01F1
#define P1_F2_APLL_MISC                                             0x01F2
#define P1_F3_APLL_STATUS                                           0x01F3
#define P1_F4_APLL_IRQ                                              0x01F4
#define P1_F5_APLL_WD                                               0x01F5
#define P1_F6_SELECT_TEST_SLS2                                      0x01F6
#define P1_F7_FAST_PLL_SUM_I_26_24                                  0x01F7
#define P1_F8_FAST_PLL_SUM_I_23_16                                  0x01F8
#define P1_F9_FAST_PLL_SUM_I_15_8                                   0x01F9
#define P1_FA_FAST_PLL_SUM_I_7_0                                    0x01FA
#define P1_FB_FAST_PLL_SUM_I_MEASURE_26_24                          0x01FB
#define P1_FC_FAST_PLL_SUM_I_MEASURE_23_16                          0x01FC
#define P1_FD_FAST_PLL_SUM_I_MEASURE_15_8                           0x01FD
#define P1_FE_FAST_PLL_SUM_I_MEASURE_7_0                            0x01FE
#define P1_FF_APLL_THERMO_CTRL_0                                    0x01FF


//--------------------------------------------------
// DISPLAY PLL (Page 1)
//--------------------------------------------------
#define P1_BF_DPLL_M                                                0x01BF
#define P1_C0_DPLL_N                                                0x01C0
#define P1_C1_DPLL_CRNT                                             0x01C1
#define P1_C2_DPLL_WD                                               0x01C2
#define P1_C3_DPLL_CAL                                              0x01C3
#define P1_C4_DCLK_FINE_TUNE_OFFSET_MSB                             0x01C4
#define P1_C5_DCLK_FINE_TUNE_OFFSET_LSB                             0x01C5
#define P1_C6_DCLK_SPREAD_SPECTRUM                                  0x01C6
#define P1_CA_FIXED_LAST_LINE_CTRL                                  0x01CA
#define P1_CE_FIXED_LAST_LINE_TRACKING_TIME                         0x01CE
#define P1_CF_PHASE_RESULT_MSB                                      0x01CF
#define P1_D0_PHASE_LINE_LSB                                        0x01D0
#define P1_D1_PHASE_PIXEL_LSB                                       0x01D1
#define P1_D2_TARGET_DCLK_FINE_TUNE_OFFSET_MSB                      0x01D2
#define P1_D3_TARGET_DCLK_FINE_TUNE_OFFSET_LSB                      0x01D3
#define P1_D4_DPLL_RESULT                                           0x01D4
#define P1_D5_SSC_REF_SEL                                           0x01D5
#define P1_D6_DCLK_SSC_COUNT                                        0x01D6
#define P1_D7_DPLL_LDO                                              0x01D7
#define P1_D8_DPLL_RELOAD_CTRL                                      0x01D8
#define P1_D9_DPLL_M_N_MSB                                          0x01D9
#define P1_DA_DPLL_OUTPUT_CLK_DIV                                   0x01DA
#define P1_DB_DCLK_GATED_CTRL1                                      0x01DB
#define P1_DC_DCLK_GATED_CTRL2                                      0x01DC
#define P1_BF_DPLL_M                                                0x01BF
#define P1_C0_DPLL_N                                                0x01C0
#define P1_C1_DPLL_CRNT                                             0x01C1
#define P1_C2_DPLL_WD                                               0x01C2
#define P1_C3_DPLL_CAL                                              0x01C3
#define P1_C4_DCLK_FINE_TUNE_OFFSET_MSB                             0x01C4
#define P1_C5_DCLK_FINE_TUNE_OFFSET_LSB                             0x01C5
#define P1_C6_DCLK_SPREAD_SPECTRUM                                  0x01C6
#define P1_CA_FIXED_LAST_LINE_CTRL                                  0x01CA
#define P1_CE_FIXED_LAST_LINE_TRACKING_TIME                         0x01CE
#define P1_CF_PHASE_RESULT_MSB                                      0x01CF
#define P1_D0_PHASE_LINE_LSB                                        0x01D0
#define P1_D1_PHASE_PIXEL_LSB                                       0x01D1
#define P1_D2_TARGET_DCLK_FINE_TUNE_OFFSET_MSB                      0x01D2
#define P1_D3_TARGET_DCLK_FINE_TUNE_OFFSET_LSB                      0x01D3
#define P1_D4_DPLL_RESULT                                           0x01D4
#define P1_D5_SSC_REF_SEL                                           0x01D5
#define P1_D6_DCLK_SSC_COUNT                                        0x01D6
#define P1_D7_DPLL_LDO                                              0x01D7
#define P1_D8_DPLL_RELOAD_CTRL                                      0x01D8
#define P1_D9_DPLL_M_N_MSB                                          0x01D9
#define P1_DA_DPLL_OUTPUT_CLK_DIV                                   0x01DA
#define P1_DB_DCLK_GATED_CTRL1                                      0x01DB
#define P1_DC_DCLK_GATED_CTRL2                                      0x01DC


//--------------------------------------------------
// Multiply PLL for Input Crystal (Page 1)
//--------------------------------------------------
#define P1_E0_M2PLL_M                                               0x01E0
#define P1_E1_M2PLL_N                                               0x01E1
#define P1_E4_M2PLL_CRNT                                            0x01E4
#define P1_E5_M2PLL_WD                                              0x01E5
#define P1_E6_M2PLL_LDO                                             0x01E6
#define P1_E7_M2PLL_M_N_MSB                                         0x01E7
#define P1_E8_M2PLL_CAL                                             0x01E8
#define P1_E9_M2PLL_RESULT                                          0x01E9


//--------------------------------------------------
// M2PLL SSCG (Page 1)
//--------------------------------------------------
#define P1_EA_M2PLL_FINE_TUNE_OFFSET_MSB                            0x01EA
#define P1_EB_M2PLL_FINE_TUNE_OFFSET_LSB                            0x01EB
#define P1_EC_M2PLL_SSCG_CTRL                                       0x01EC


//--------------------------------------------------
// HDMI2.0 Function (Page 2)
//--------------------------------------------------
#define P2_00_HDMI_CTRL_00                                          0x0200
#define P2_01_HDMI_CTRL_01                                          0x0201
#define P2_02_HDMI_CTRL_02                                          0x0202
#define P2_03_HDMI_CTRL_03                                          0x0203
#define P2_04_HDMI_CTRL_04                                          0x0204
#define P2_05_HDMI_CTRL_05                                          0x0205
#define P2_06_HDMI_CTRL_06                                          0x0206
#define P2_07_HDMI_CTRL_07                                          0x0207
#define P2_08_HDMI_CTRL_08                                          0x0208
#define P2_0B_HDMI_CTRL_0B                                          0x020B
#define P2_0C_HDMI_CTRL_0C                                          0x020C
#define P2_0D_HDMI_CTRL_0D                                          0x020D
#define P2_0E_HDMI_CTRL_0E                                          0x020E
#define P2_0F_HDMI_CTRL_0F                                          0x020F
#define P2_10_HDMI_CTRL_10                                          0x0210
#define P2_11_HDMI_CTRL_11                                          0x0211
#define P2_12_HDMI_CTRL_12                                          0x0212
#define P2_13_HDMI_CTRL_13                                          0x0213
#define P2_14_HDMI_CTRL_14                                          0x0214
#define P2_15_HDMI_CTRL_15                                          0x0215
#define P2_16_HDMI_CTRL_16                                          0x0216
#define P2_17_HDMI_CTRL_17                                          0x0217
#define P2_18_HDMI_CTRL_18                                          0x0218
#define P2_19_HDMI_CTRL_19                                          0x0219
#define P2_1A_HDMI_CTRL_1A                                          0x021A
#define P2_1B_HDMI_CTRL_1B                                          0x021B
#define P2_1C_HDMI_CTRL_1C                                          0x021C
#define P2_1D_HDMI_CTRL_1D                                          0x021D
#define P2_1E_HDMI_CTRL_1E                                          0x021E
#define P2_1F_HDMI_CTRL_1F                                          0x021F
#define P2_20_HDMI_CTRL_20                                          0x0220
#define P2_21_HDMI_CTRL_21                                          0x0221
#define P2_22_HDMI_CTRL_22                                          0x0222
#define P2_23_HDMI_CTRL_23                                          0x0223
#define P2_24_HDMI_CTRL_24                                          0x0224
#define P2_25_HDMI_CTRL_25                                          0x0225
#define P2_26_HDMI_CTRL_26                                          0x0226
#define P2_27_HDMI_CTRL_27                                          0x0227
#define P2_28_HDMI_CTRL_28                                          0x0228
#define P2_29_HDMI_CTRL_29                                          0x0229
#define P2_2A_HDMI_CTRL_2A                                          0x022A
#define P2_2B_HDMI_CTRL_2B                                          0x022B
#define P2_2C_HDMI_CTRL_2C                                          0x022C
#define P2_2D_HDMI_CTRL_2D                                          0x022D
#define P2_2E_HDMI_CTRL_2E                                          0x022E
#define P2_38_HDMI_CTRL_38                                          0x0238
#define P2_39_HDMI_CTRL_39                                          0x0239
#define P2_3A_HDMI_CTRL_3A                                          0x023A
#define P2_40_HDMI_PCK_40                                           0x0240
#define P2_41_HDMI_PCK_41                                           0x0241
#define P2_42_HDMI_PCK_42                                           0x0242
#define P2_43_HDMI_PCK_43                                           0x0243
#define P2_44_HDMI_PCK_44                                           0x0244
#define P2_45_HDMI_PCK_45                                           0x0245
#define P2_46_HDMI_PCK_46                                           0x0246
#define P2_47_HDMI_PCK_47                                           0x0247
#define P2_48_HDMI_PCK_48                                           0x0248
#define P2_49_HDMI_20_49                                            0x0249
#define P2_50_HDMI_20_50                                            0x0250
#define P2_51_HDMI_20_51                                            0x0251


//--------------------------------------------------
// Overall HDMI System Function Block (Page 2)
//--------------------------------------------------
#define P2_A1_TMDS_MSR                                              0x02A1
#define P2_A2_TMDS_MRR0                                             0x02A2
#define P2_A3_TMDS_MRR1                                             0x02A3
#define P2_A4_TMDS_CTRL                                             0x02A4
#define P2_A5_TMDS_CRCOB2                                           0x02A5
#define P2_A6_TMDS_OUTCTL                                           0x02A6
#define P2_A7_TMDS_PWDCTL                                           0x02A7
#define P2_A8_TMDS_ACC0                                             0x02A8
#define P2_A9_TMDS_ABC0                                             0x02A9
#define P2_AA_TMDS_ABC1                                             0x02AA
#define P2_AB_TMDS_ACC2                                             0x02AB
#define P2_AC_TMDS_Z0CC2                                            0x02AC
#define P2_AD_TMDS_CPS                                              0x02AD
#define P2_AE_TMDS_RPS                                              0x02AE
#define P2_AF_TMDS_WDC                                              0x02AF
#define P2_B0_TMDS_CHANNEL_FIFO                                     0x02B0
#define P2_B4_TMDS_DPC0                                             0x02B4
#define P2_B5_TMDS_UDC0                                             0x02B5
#define P2_B6_TMDS_UDC1                                             0x02B6
#define P2_B7_TMDS_UDC2                                             0x02B7
#define P2_B8_TMDS_DPC1                                             0x02B8
#define P2_B9_TMDS_OUT_CTRL                                         0x02B9
#define P2_BA_TMDS_ROUT_HIGH_BYTE                                   0x02BA
#define P2_BB_TMDS_ROUT_LOW_BYTE                                    0x02BB
#define P2_BC_TMDS_GOUT_HIGH_BYTE                                   0x02BC
#define P2_BD_TMDS_GOUT_LOW_BYTE                                    0x02BD
#define P2_BE_TMDS_BOUT_HIGH_BYTE                                   0x02BE
#define P2_BF_TMDS_BOUT_LOW_BYTE                                    0x02BF
#define P2_C0_HDCP_CR                                               0x02C0
#define P2_C1_HDCP_DKAP                                             0x02C1
#define P2_C2_HDCP_PCR                                              0x02C2
#define P2_C3_HDCP_AP                                               0x02C3
#define P2_C4_HDCP_DP                                               0x02C4
#define P2_C8_HDMI_APC                                              0x02C8
#define P2_C9_HDMI_AP                                               0x02C9
#define P2_CA_HDMI_DP                                               0x02CA
#define P2_CB_HDMI_SR                                               0x02CB
#define P2_CC_HDMI_GPVS                                             0x02CC
#define P2_CD_HDMI_PSAP                                             0x02CD
#define P2_CE_HDMI_PSDP                                             0x02CE
#define P2_E0_AUX_PS_CTRL                                           0x02E0
#define P2_E1_AUX_PS_REPLY                                          0x02E1
#define P2_E6_HDMI_FREQDET_CTRL                                     0x02E6
#define P2_E7_HDMI_FREQDET_OFFSET                                   0x02E7
#define P2_E8_HDMI_FREQDET_UPPER_M                                  0x02E8
#define P2_E9_HDMI_FREQDET_UPPER_L                                  0x02E9
#define P2_EA_HDMI_FREQDET_LOWER_M                                  0x02EA
#define P2_EB_HDMI_FREQDET_LOWER_L                                  0x02EB
#define P2_EC_HDMI_FREQDET_STABLE                                   0x02EC
#define P2_ED_HDMI_FREQDET_RESULT_M                                 0x02ED
#define P2_EE_HDMI_FREQDET_RESULT_L                                 0x02EE
#define P2_EF_HDMI_ERROR_TH                                         0x02EF
#define P2_F6_HDMI_FREQDET_BOUND_H                                  0x02F6
#define P2_F7_HDMI_FREQDET_RESULT_H                                 0x02F7


//--------------------------------------------------
// LiveShowTM Control (Page 3)
//--------------------------------------------------
#define P3_A1_LS_CTRL0                                              0x03A1
#define P3_A2_LS_CTRL1                                              0x03A2
#define P3_A3_DELTA_GAIN                                            0x03A3
#define P3_A4_LS_STATUS0                                            0x03A4
#define P3_A5_LS_STATUS1                                            0x03A5
#define P3_A6_LS_WTLVL_W                                            0x03A6
#define P3_A7_LS_WTLVL_R                                            0x03A7
#define P3_A8_LS_MEM_FIFO_RW_NUM_H                                  0x03A8
#define P3_A9_LS_MEM_FIFO_RW_NUM_L                                  0x03A9
#define P3_AA_LS_MEM_FIFO_RW_LEN                                    0x03AA
#define P3_AB_LS_MEM_FIFO_RW_REMAIN                                 0x03AB
#define P3_AC_LS_MEM_START_ADDR_H                                   0x03AC
#define P3_AD_LS_MEM_START_ADDR_M                                   0x03AD
#define P3_AE_LS_MEM_START_ADDR_L                                   0x03AE
#define P3_AF_LS_BIST_CTRL                                          0x03AF
#define P3_B0_LS_FRAME0                                             0x03B0
#define P3_B1_LS_FRAME1                                             0x03B1
#define P3_B2_LS_FRAME2                                             0x03B2
#define P3_B3_LS_FRAME4                                             0x03B3
#define P3_B4_LS_FRAME5                                             0x03B4
#define P3_B5_LS_BYPOS0                                             0x03B5
#define P3_B6_LS_BYPOS1                                             0x03B6
#define P3_B7_LS_GAIN_BASE                                          0x03B7
#define P3_B8_LS_GAIN_SLOPE                                         0x03B8
#define P3_BF_LS_LUT_CTRL                                           0x03BF
#define P3_C0_LS_LUT_DATA                                           0x03C0
#define P3_C1_LS_LUT_READ                                           0x03C1
#define P3_C2_LS_LUT_ROW                                            0x03C2
#define P3_C3_LS_LUT_COL                                            0x03C3
#define P3_CA_CAP_BIST_CTRL0                                        0x03CA
#define P3_CB_CAP_BIST_CTRL1                                        0x03CB
#define P3_CD_DIS_BIST_CTRL0                                        0x03CD
#define P3_CE_DIS_BIST_CTRL1                                        0x03CE
#define P3_D0_LS_DDR_FIFO_WTLVL_W_H                                 0x03D0
#define P3_D1_LS_DDR_FIFO_WTLVL_W_L                                 0x03D1
#define P3_D2_LS_DDR_FIFO_WTLVL_R_H                                 0x03D2
#define P3_D3_LS_DDR_FIFO_WTLVL_R_L                                 0x03D3
#define P3_D4_LS_DDR_FIFO_RW_NUM_H                                  0x03D4
#define P3_D5_LS_DDR_FIFO_RW_NUM_L                                  0x03D5
#define P3_D6_LS_DDR_FIFO_RW_LEN_H                                  0x03D6
#define P3_D7_LS_DDR_FIFO_RW_LEN_L                                  0x03D7
#define P3_D8_LS_DDR_FIFO_RW_REMAIN_H                               0x03D8
#define P3_D9_LS_DDR_FIFO_RW_REMAIN_L                               0x03D9
#define P3_DA_LS_DDR_START_ADDR_MSB                                 0x03DA
#define P3_DB_LS_DDR_START_ADDR_H                                   0x03DB
#define P3_DC_LS_DDR_START_ADDR_M                                   0x03DC
#define P3_DD_LS_DDR_START_ADDR_L                                   0x03DD


//--------------------------------------------------
// SDRAM Control (Page 4)
//--------------------------------------------------
#define P4_00_SDDR_CTRL                                             0x0400
#define P4_01_SDDR_CLK_CTRL0                                        0x0401
#define P4_02_SDDR_CLK_CTRL1                                        0x0402
#define P4_03_SDDR_CDAR_CTRL                                        0x0403
#define P4_04_SDDR_DQSX0_CTRL0                                      0x0404
#define P4_05_SDDR_DQSX0_CTRL1                                      0x0405
#define P4_06_SDDR_DQX0_CTRL0                                       0x0406
#define P4_07_SDDR_DQX0_CTRL1                                       0x0407
#define P4_08_SDDR_DQSX1_CTRL0                                      0x0408
#define P4_09_SDDR_DQSX1_CTRL1                                      0x0409
#define P4_0A_SDDR_DQX1_CTRL0                                       0x040A
#define P4_0B_SDDR_DQX1_CTRL1                                       0x040B

#define P4_A1_SDR_CTRL0                                             0x04A1 // SDRAM Control Register0
#define P4_A2_SDR_CTRL1                                             0x04A2 // SDRAM Control Register1
#define P4_A3_SDR_AREF_TIME                                         0x04A3 // SDRAM Auto Refresh Time
#define P4_A4_SDR_PRCG                                              0x04A4 // SDRAM Precharge Control Register
#define P4_A5_SDR_MEM_TYPE                                          0x04A5 // SDRAM Memory Size Select
#define P4_A6_SDR_SLEW_RATE                                         0x04A6 // SDRAM Slew Rate Control Register
#define P4_A7_SDR_AREF_CNT                                          0x04A7 // Number Of Auto Refresh
#define P4_A8_SDR_CLK_ALIGN                                         0x04A8 // SDRAM Clock Align
#define P4_AA_SDR_RSC_AREF                                          0x04AA // SDRAM Arbiter Token Ring For Auto Refresh
#define P4_AB_SDR_RSC_MCU                                           0x04AB // SDRAM Arbiter Token Ring For MCU
#define P4_AC_SDR_RSC_CAP1                                          0x04AC // SDRAM Arbiter Token Ring For CAP1
#define P4_AE_SDR_RSC_MAIN                                          0x04AE // SDRAM Arbiter Token Ring For Main
#define P4_B0_SDR_RSC_RTC_RD                                        0x04B0 // SDRAM Arbiter Token Ring For RD
#define P4_B1_SDR_RSC_RTC_WR                                        0x04B1 // SDRAM Arbiter Token Ring For WR

#define P4_B4_SDR_ABTR_STATUS0                                      0x04B4 // SDRAM Arbiter Status Register0
#define P4_B5_SDR_ABTR_STATUS1                                      0x04B5 // SDRAM Arbiter Status Register1
#define P4_B7_SDR_POWER_CTRL0                                       0x04B7 // SDRAM Power Down Mode Control
#define P4_B8_SDR_ADDR_H                                            0x04B8 // SDRAM Access Address HByte
#define P4_B9_SDR_ADDR_M                                            0x04B9 // SDRAM Access Address MByte
#define P4_BA_SDR_ADDR_L                                            0x04BA // SDRAM Access Address LByte
#define P4_BB_SDR_ACCESS_CMD                                        0x04BB // SDRAM Access Command
#define P4_BC_SDR_DATA_BUF                                          0x04BC // SDRAM Data Buffer
#define P4_BD_SDR_MCU_RD_LEN                                        0x04BD // SDRAM MCU Read SdRAM Lengh
#define P4_BE_SDR_RX_PHASE_CALIBRATION                              0x04BE // SDRAM Phase Calibration
#define P4_BF_SDR_RX_CALIBRATION_RESULT                             0x04BF // SDRAM Calibration Result

#define P4_C0_TX_CLK_DLY1                                           0x04C0 // SDRAM Mclk Output
#define P4_C1_TX_CLK_DLY2                                           0x04C1 // SDRAM Mclk Delay Fine Tune
#define P4_C2_SDR_RX_CLK_DLY1                                       0x04C2 // SDRAM DQS0 Coarse Delay
#define P4_C3_SDR_RX_CLK_DLY2                                       0x04C3 // SDRAM DQS0 Data Fine Delay
#define P4_C4_SDR_RX_CLK_DLY3                                       0x04C4 // SDRAM DQS1 Coarse Delay
#define P4_C5_SDR_RX_CLK_DLY4                                       0x04C5 // SDRAM DQS1 Data Fine Delay
#define P4_C6_SEC_SDR_RX_DLY5                                       0x04C6 // SDRAM DQS2 Coarse Delay
#define P4_C7_SEC_SDR_RX_DLY6                                       0x04C7 // SDRAM DQS2 Data Fine Delay
#define P4_C8_MCLK_CTRL                                             0x04C8 // SDRAM DQS3 Coarse Delay
#define P4_C9_SDR_STOPCLK_CNT                                       0x04C9 // SDRAM DQS3 Data Fine Delay
#define P4_CA_STOP_WAIT_CNT                                         0x04CA // SDRAM DQS0 Second Data Fine Delay
#define P4_CB_TX_PHASE_CALIBRATION                                  0x04CB // SDRAM DQS1 Second Data Fine Delay
#define P4_CC_TX_CALIBRATION_RESULT                                 0x04CC // SDRAM DQS2 Second Data Fine Delay

#define P4_CD_DDR_TX_DLY0                                           0x04CD // SDRAM DQS3 Second Data Fine Delay
#define P4_CE_DDR_TX_DLY1                                           0x04CE
#define P4_CF_DDR_RX_DLY0                                           0x04CF

#define P4_D0_DDR_RX_DLY1                                           0x04D0
#define P4_D1_DDR_RX_DLY2                                           0x04D1
#define P4_D2_DDR_RX_DLY3                                           0x04D2
#define P4_D3_DDR_RX_DLY4                                           0x04D3
#define P4_D4_DDR_RX_DLY5                                           0x04D4
#define P4_D5_DDR_RX_DLY6                                           0x04D5
#define P4_D6_DDR_RX_DLY7                                           0x04D6
#define P4_D7_DDR_RX_DLY8                                           0x04D7
#define P4_D8_DDR_MEASURE                                           0x04D8
#define P4_D9_DDR_AUTO_CALIB0                                       0x04D9
#define P4_DA_DDR_AUTO_CALIB_RLT0                                   0x04DA
#define P4_DB_DDR_AUTO_CALIB1                                       0x04DB
#define P4_DC_DDR_AUTO_CALIB_RLT1                                   0x04DC
#define P4_DD_DDR_AUTO_CALIB2                                       0x04DD
#define P4_DE_DDR_AUTO_CALIB_RLT2                                   0x04DE
#define P4_DF_DDR_AUTO_CALIB3                                       0x04DF

#define P4_E0_DDR_AUTO_CALIB_RLT3                                   0x04E0
#define P4_E1_DDR_AUTO_CALIB_DQS0_SEL0                              0x04E1
#define P4_E2_DDR_AUTO_CALIB_DQS0_SEL1                              0x04E2
#define P4_E3_DDR_AUTO_CALIB_DQS1_SEL0                              0x04E3
#define P4_E4_DDR_AUTO_CALIB_DQS1_SEL1                              0x04E4
#define P4_E5_DDR_AUTO_CALIB_RLT_SEL                                0x04E5
#define P4_E6_DDR_AUTO_CALIB_DQS0_R_RLT0                            0x04E6
#define P4_E7_DDR_AUTO_CALIB_DQS0_R_RLT1                            0x04E7
#define P4_E8_DDR_AUTO_CALIB_DQS0_R_RLT2                            0x04E8
#define P4_E9_DDR_AUTO_CALIB_DQS0_R_RLT3                            0x04E9
#define P4_EA_DDR_AUTO_CALIB_DQS0_F_RLT0                            0x04EA
#define P4_EB_DDR_AUTO_CALIB_DQS0_F_RLT0                            0x04EB
#define P4_EC_DDR_AUTO_CALIB_DQS0_F_RLT2                            0x04EC
#define P4_ED_DDR_AUTO_CALIB_DQS0_F_RLT3                            0x04ED
#define P4_EE_DDR_AUTO_CALIB_DQS1_R_RLT0                            0x04EE
#define P4_EF_DDR_AUTO_CALIB_DQS1_R_RLT1                            0x04EF

#define P4_F0_DDR_AUTO_CALIB_DQS1_R_RLT2                            0x04F0
#define P4_F1_DDR_AUTO_CALIB_DQS1_R_RLT3                            0x04F1
#define P4_F2_DDR_AUTO_CALIB_DQS1_F_RLT0                            0x04F2
#define P4_F3_DDR_AUTO_CALIB_DQS1_F_RLT1                            0x04F3
#define P4_F4_DDR_AUTO_CALIB_DQS1_F_RLT2                            0x04F4
#define P4_F5_DDR_AUTO_CALIB_DQS1_F_RLT3                            0x04F5
#define P4_F6_DDR_AUTO_CALIB4                                       0x04F6
#define P4_F7_DDR_AUTO_CALIB_RLT4                                   0x04F7
#define P4_F8_DDR_AUTO_CALIB5                                       0x04F8
#define P4_F9_DDR_AUTO_CALIB_RLT5                                   0x04F9
#define P4_FA_DDR_AUTO_CALIB_RLT_SEL1                               0x04FA

#define P4_FC_EXTENDED_MODE_REGISTER0                               0x04FC // SDRAM Extended Mode Register HByte
#define P4_FD_EXTENDED_MODE_REGISTER1                               0x04FD // SDRAM Extended Mode Register LByte
#define P4_FE_RANDOM_GENERATOR                                      0x04FE // SDRAM Random Generator
#define P4_FF_CRC_DATA_PORT                                         0x04FF // SDRAM CRC Data Port

//--------------------------------------------------
// FIFO Control (Page 5)
//--------------------------------------------------
#define P5_A1_IN1_FIFO_STATUS                                       0x05A1
#define P5_A2_MAIN_FIFO_STATUS                                      0x05A2
#define P5_A3_IN1_SFIFO_STATUS                                      0x05A3
#define P5_A4_IN1_ONEF_STATUS                                       0x05A4
#define P5_A8_IN1_WATER_LEVEL                                       0x05A8
#define P5_A9_IN1_WR_NUM_H                                          0x05A9
#define P5_AA_IN1_WR_NUM_L                                          0x05AA
#define P5_AB_IN1_WR_LEN                                            0x05AB
#define P5_AC_IN1_WR_REMAIN                                         0x05AC
#define P5_AD_IN1_MEM_ADDR_H                                        0x05AD
#define P5_AE_IN1_MEM_ADDR_M                                        0x05AE
#define P5_AF_IN1_MEM_ADDR_L                                        0x05AF
#define P5_B0_IN1_LINE_STEP_H                                       0x05B0
#define P5_B1_IN1_LINE_STEP_L                                       0x05B1
#define P5_B2_IN1_BLOCK_STEP_H                                      0x05B2
#define P5_B3_IN1_BLOCK_STEP_L                                      0x05B3
#define P5_B4_IN1_BL2_ADDR_H                                        0x05B4
#define P5_B5_IN1_BL2_ADDR_M                                        0x05B5
#define P5_B6_IN1_BL2_ADDR_L                                        0x05B6
#define P5_B7_IN1_LINE_NUM_H                                        0x05B7
#define P5_B8_IN1_LINE_NUM_L                                        0x05B8
#define P5_B9_IN1_SDR_CTRL                                          0x05B9
#define P5_BA_IN1_MADDR_TOG_CTL                                     0x05BA
#define P5_BB_IN1_SDR_STATUS                                        0x05BB
#define P5_BC_MN_PRRD_VST_H                                         0x05BC
#define P5_BD_MN_PRRD_VST_L                                         0x05BD
#define P5_BE_MN_PXL_NUM_H                                          0x05BE
#define P5_BF_MN_PXL_NUM_L                                          0x05BF
#define P5_C0_MN_WTLVL                                              0x05C0
#define P5_C1_MN_MADDR_TOG_CTL                                      0x05C1
#define P5_C2_MN_READ_NUM_H                                         0x05C2
#define P5_C3_MN_READ_NUM_L                                         0x05C3
#define P5_C4_MN_READ_LEN                                           0x05C4
#define P5_C5_MN_READ_REMAIN                                        0x05C5
#define P5_C6_MN_READ_ADDR_H                                        0x05C6
#define P5_C7_MN_READ_ADDR_M                                        0x05C7
#define P5_C8_MN_READ_ADDR_L                                        0x05C8
#define P5_C9_MN_LINE_STEP_H                                        0x05C9
#define P5_CA_MN_LINE_STEP_L                                        0x05CA
#define P5_CB_MN_BLOCK_STEP_H                                       0x05CB
#define P5_CC_MN_BLOCK_STEP_L                                       0x05CC
#define P5_CD_MN_LINE_NUM_H                                         0x05CD
#define P5_CE_MN_LINE_NUM_L                                         0x05CE
#define P5_CF_MN_DISP_CTRL                                          0x05CF
#define P5_D0_MN_SDR_STATUS                                         0x05D0
#define P5_D6_ADC_TEST                                              0x05D6
#define P5_E3_MN_FIFO_422_SET                                       0x05E3
#define P5_E4_IN1_ONEF_DHF_H                                        0x05E4
#define P5_E5_IN1_ONEF_DHF_M                                        0x05E5
#define P5_E6_IN1_ONEF_DHF_L                                        0x05E6
#define P5_E7_IN1_ONEF_IHF                                          0x05E7
#define P5_E8_IN1_LINE_MAGN_L                                       0x05E8
#define P5_E9_IN1_ONEF_MAGN_H                                       0x05E9
#define P5_EA_IN1_PRRD_MAGN_L                                       0x05EA
#define P5_EB_MN_MADDR_TOG_REM                                      0x05EB
#define P5_F0_IN1_BIST_CTRL                                         0x05F0
#define P5_F1_MN_BIST_CTRL                                          0x05F1
#define P5_F2_IN1_TEST                                              0x05F2
#define P5_F3_MN_TEST                                               0x05F3


//--------------------------------------------------
// Internal OSC (Page 6)
//--------------------------------------------------
#define P6_A0_OSC_TRIM_CTRL0                                        0x06A0
#define P6_A1_OSC_TRIM_CTRL1                                        0x06A1
#define P6_A2_OSC_TRIM_CTRL2                                        0x06A2
#define P6_A3_EMBEDDED_OSC_CTRL                                     0x06A3
#define P6_A4_OSC_TRIM_CNT                                          0x06A4
#define P6_A5_EMB_BGRES                                             0x06A5
#define P6_A6_EMB_BGRES1                                            0x06A6


//--------------------------------------------------
// Audio (Page 6)
//--------------------------------------------------
#define P6_B0_REG_ADC_POWER                                         0x06B0
#define P6_B1_REG_ADC_CUR                                           0x06B1
#define P6_B2_REG_ADC_CTRL                                          0x06B2
#define P6_B3_REG_AFE_GAIN                                          0x06B3
#define P6_B4_AD_CTRL                                               0x06B4
#define P6_B5_AD_MUTE                                               0x06B5
#define P6_B6_AD_GAIN_L                                             0x06B6
#define P6_B7_AD_GAIN_R                                             0x06B7
#define P6_B8_AD_DUMMY_0                                            0x06B8
#define P6_B9_AD_DUMMY_1                                            0x06B9
#define P6_C0_REG_DAC_POWER0                                        0x06C0
#define P6_C1_REG_DAC_POWER1                                        0x06C1
#define P6_C2_REG_DAC_CUR0                                          0x06C2
#define P6_C3_REG_DAC_CUR1                                          0x06C3
#define P6_C4_REG_DAC_CUR2                                          0x06C4
#define P6_C5_REG_ANA_CTRL                                          0x06C5
#define P6_C6_REG_AOUT_CTRL                                         0x06C6
#define P6_C7_REG_HPOUT_CTRL                                        0x06C7
#define P6_C8_REG_OUT_GAIN                                          0x06C8
#define P6_C9_REG_ANA_RESERVE0                                      0x06C9
#define P6_CA_REG_ANA_RESERVE1                                      0x06CA
#define P6_CB_REG_ANA_RESERVE2                                      0x06CB
#define P6_CC_REG_ANA_RESERVE3                                      0x06CC
#define P6_D0_DA_CTRL                                               0x06D0
#define P6_D1_DA_MUTE                                               0x06D1
#define P6_D2_DA_GAIN_L                                             0x06D2
#define P6_D3_DA_GAIN_R                                             0x06D3
#define P6_D4_DA_CLK_CTRL                                           0x06D4
#define P6_D5_DA_DUMMY_0                                            0x06D5
#define P6_D6_DA_DUMMY_1                                            0x06D6
#define P6_E0_REG_MUX_ANA_OUT                                       0x06E0
#define P6_E1_AD_SPDIF_CTRL                                         0x06E1
#define P6_E2_AD_SPDIF_CS_0                                         0x06E2
#define P6_E3_AD_SPDIF_CS_1                                         0x06E3
#define P6_E4_AD_SPDIF_CS_2                                         0x06E4
#define P6_E5_AD_SPDIF_CS_3                                         0x06E5
#define P6_E6_AD_SPDIF_CS_4                                         0x06E6
#define P6_E7_AD_I2S_CTRL                                           0x06E7
#define P6_E8_AUD_TEST_PIN                                          0x06E8
#define P6_E9_AUD_ADC_SRAM_BIST_0                                   0x06E9
#define P6_EA_AUD_ADC_SRAM_BIST_1                                   0x06EA
#define P6_EB_AUD_DAC_SRAM_BIST_0                                   0x06EB
#define P6_EC_AUD_DAC_SRAM_BIST_1                                   0x06EC
#define P6_ED_AUD_DUMMY_0                                           0x06ED
#define P6_EE_AUD_DUMMY_1                                           0x06EE


//--------------------------------------------------
// DCC (Page 7)
//--------------------------------------------------
#define P7_C7_DCC_CTRL_0                                            0x07C7
#define P7_C8_DCC_CTRL_1                                            0x07C8
#define P7_C9_DCC_ADDRESS_PORT                                      0x07C9
#define P7_CA_DCC_DATA_PORT                                         0x07CA


//--------------------------------------------------
// ICM (Page 7)
//--------------------------------------------------
#define P7_D0_ICM_CONTROL                                           0x07D0
#define P7_D1_ICM_SEL                                               0x07D1
#define P7_D2_ICM_ADDR                                              0x07D2
#define P7_D3_ICM_DATA                                              0x07D3
#define P7_D4_ICM_SEL2                                              0x07D4


//--------------------------------------------------
// Y-Peaking and Coring (D-Domain) (Page 7)
//--------------------------------------------------
#define P7_D6_PEAKING_CORING_ACCESS_PORT_CTL                        0x07D6
#define P7_D7_PEAKING_CORING_DATA_PORT                              0x07D7


//--------------------------------------------------
// DCR (Page 7)
//--------------------------------------------------
#define P7_D8_DCR_ADDRESS_PORT                                      0x07D8
#define P7_D9_DCR_DATA_PORT                                         0x07D9
#define P7_DA_DCR_CTRL                                              0x07DA


//--------------------------------------------------
// D-domain Pattern Generator (Page 7)
//--------------------------------------------------
#define P7_F0_DISP_PG_R_CTRL                                        0x07F0
#define P7_F1_DISP_PG_G_CTRL                                        0x07F1
#define P7_F2_DISP_PG_B_CTRL                                        0x07F2
#define P7_F3_DISP_PG_R_INITIAL                                     0x07F3
#define P7_F4_DISP_PG_G_INITIAL                                     0x07F4
#define P7_F5_DISP_PG_B_INITIAL                                     0x07F5
#define P7_F6_DISP_PG_PIXEL_DELTA_H                                 0x07F6
#define P7_F7_DISP_PG_LINE_DELTA_H                                  0x07F7
#define P7_F8_DISP_PG_PIXEL_STEP_H                                  0x07F8
#define P7_F9_DISP_PG_LINE_STEP_H                                   0x07F9
#define P7_FA_DISP_PG_DELTA_H_STEP_M                                0x07FA
#define P7_FB_D_PG_CTRL_0                                           0x07FB
#define P7_FC_D_PG_INITIAL_M_STEP_L                                 0x07FC
#define P7_FD_D_PG_INITIAL_L_CTRL                                   0x07FD
#define P7_FF_D_PATTERN_RESET                                       0x07FF


//--------------------------------------------------
// Audio Control (Page 8)
//--------------------------------------------------
#define P8_A0_DVC_EN                                                0x08A0
#define P8_A1_DVC_VA_MSB                                            0x08A1
#define P8_A2_DVC_VA_LSB                                            0x08A2
#define P8_A3_DVC_ZC_WIN_CTRL_0                                     0x08A3
#define P8_A4_DVC_ZC_WIN_CTRL_1                                     0x08A4
#define P8_A5_DVC_GAIN_MSB                                          0x08A5
#define P8_A6_DVC_GAIN_LSB                                          0x08A6
#define P8_A7_DVC_GAIN_READ_MSB                                     0x08A7
#define P8_A8_DVC_GAIN_READ_LSB                                     0x08A8
#define P8_A9_DVC_GAIN_DONE                                         0x08A9
#define P8_AA_DVC_RESERVE1                                          0x08AA
#define P8_AB_DVC_RESERVE2                                          0x08AB
#define P8_C0_PEAK_CTRL_0                                           0x08C0
#define P8_C1_PEAK_CTRL_1                                           0x08C1
#define P8_C2_PEAK_CTRL_L_0                                         0x08C2
#define P8_C3_PEAK_CTRL_L_1                                         0x08C3
#define P8_C4_PEAK_CTRL_L_2                                         0x08C4
#define P8_C5_PEAK_CTRL_L_3                                         0x08C5
#define P8_C6_PEAK_CTRL_L_4                                         0x08C6
#define P8_C7_PEAK_CTRL_R_0                                         0x08C7
#define P8_C8_PEAK_CTRL_R_1                                         0x08C8
#define P8_C9_PEAK_CTRL_R_2                                         0x08C9
#define P8_CA_PEAK_CTRL_R_3                                         0x08CA
#define P8_CB_PEAK_CTRL_R_4                                         0x08CB
#define P8_CC_PEAK_RESERVE1                                         0x08CC
#define P8_CD_PEAK_RESERVE2                                         0x08CD


//--------------------------------------------------
// Input Gamma Control (Page 9)
//--------------------------------------------------
#define P9_A0_INPUT_GAMMA_PORT                                      0x09A0
#define P9_A1_INPUT_GAMMA_CTRL                                      0x09A1
#define P9_A2_INPUT_GAMMA_LOW_THRE                                  0x09A2
#define P9_A3_INPUT_GAMMA_HIGH_THRE                                 0x09A3
#define P9_A4_IG_DUMMY                                              0x09A4


//--------------------------------------------------
// D0 Port DisplayPort 1.2 Digital PHY(Page B)
//--------------------------------------------------
#define PB_00_HD_DP_SEL                                             0x0B00
#define PB_01_PHY_DIG_RESET_CTRL                                    0x0B01
#define PB_02_PHY_DIG_RESET2_CTRL                                   0x0B02
#define PB_03_LANE_MUX                                              0x0B03
#define PB_04_CHANNEL_FIFO_SYNC                                     0x0B04
#define PB_05_SAMPLE_EDGE                                           0x0B05
#define PB_06_DECODE_10B8B_ERROR                                    0x0B06
#define PB_07_SCRAMBLE_CTRL                                         0x0B07
#define PB_08_BIST_PATTERN_SEL                                      0x0B08
#define PB_09_BIST_PATTERN1                                         0x0B09
#define PB_0A_BIST_PATTERN2                                         0x0B0A
#define PB_0B_BIST_PATTERN3                                         0x0B0B
#define PB_0C_BIST_PATTERN4                                         0x0B0C
#define PB_0D_BIST_SEED_0                                           0x0B0D
#define PB_0E_DESKEW_PHY                                            0x0B0E
#define PB_0F_DESKEW_PHY2                                           0x0B0F
#define PB_10_DUMMY1                                                0x0B10
#define PB_11_PHY_CH_FIFO_SYNC                                      0x0B11
#define PB_12_EQ_CRC_1                                              0x0B12
#define PB_13_EQ_CRC_2                                              0x0B13
#define PB_14_EQ_CRC_3                                              0x0B14
#define PB_15_EQ_CRC_4                                              0x0B15
#define PB_16_EQ_CRC_5                                              0x0B16
#define PB_17_DP_HDCP_CONTROL                                       0x0B17
#define PB_18_DP_HDCP_DOWNLOAD_PORT                                 0x0B18
#define PB_19_DP_HDCP_KEY_OUTPUT                                    0x0B19
#define PB_1A_HDCP_IRQ                                              0x0B1A
#define PB_1B_HDCP_INTGT_VRF                                        0x0B1B
#define PB_1C_HDCP_INTGT_VRF_PAT_MSB                                0x0B1C
#define PB_1D_HDCP_INTGT_VRF_PAT_LSB                                0x0B1D
#define PB_1E_HDCP_INTGT_VRF_ANS_MSB                                0x0B1E
#define PB_1F_HDCP_INTGT_VRF_ANS_LSB                                0x0B1F
#define PB_20_HDCP_DEBUG                                            0x0B20
#define PB_21_KM_BYTE_6                                             0x0B21
#define PB_22_KM_BYTE_5                                             0x0B22
#define PB_23_KM_BYTE_4                                             0x0B23
#define PB_24_KM_BYTE_3                                             0x0B24
#define PB_25_KM_BYTE_2                                             0x0B25
#define PB_26_KM_BYTE_1                                             0x0B26
#define PB_27_KM_BYTE_0                                             0x0B27
#define PB_4A_TYPE_0                                                0x0B4A
#define PB_50_DP_SIG_DET_0                                          0x0B50
#define PB_51_DP_SIG_DET_1                                          0x0B51
#define PB_52_DP_SIG_DET_2                                          0x0B52
#define PB_53_DP_SIG_DET_3                                          0x0B53
#define PB_54_DP_SIG_DET_4                                          0x0B54
#define PB_60_DEBUG0                                                0x0B60
#define PB_61_DEBUG1                                                0x0B61
#define PB_62_DEBUG2                                                0x0B62
#define PB_63_DUMMY2                                                0x0B63
#define PB_64_DUMMY3                                                0x0B64


//--------------------------------------------------
// GDI PHY Power On Region (Page B)
//--------------------------------------------------
#define PB_A0_DIG_00                                                0x0BA0
#define PB_A1_DIG_01                                                0x0BA1
#define PB_A2_DIG_02                                                0x0BA2
#define PB_A3_DIG_03                                                0x0BA3
#define PB_A4_DIG_04                                                0x0BA4
#define PB_A5_DIG_05                                                0x0BA5
#define PB_A6_DIG_06                                                0x0BA6
#define PB_A7_DIG_07                                                0x0BA7
#define PB_A8_DIG_08                                                0x0BA8
#define PB_A9_DIG_09                                                0x0BA9
#define PB_AA_DIG_10                                                0x0BAA
#define PB_AB_SDM_01                                                0x0BAB
#define PB_AC_SDM_02                                                0x0BAC
#define PB_AD_SDM_03                                                0x0BAD
#define PB_AE_SDM_04                                                0x0BAE
#define PB_AF_WD                                                    0x0BAF
#define PB_B0_EQEN_TIMER                                            0x0BB0
#define PB_B1_DATA_TIMER                                            0x0BB1
#define PB_B2_ANA_CDR                                               0x0BB2
#define PB_B3_CLK_DET                                               0x0BB3
#define PB_B4_BANDGAP_00                                            0x0BB4
#define PB_B5_BANDGAP_01                                            0x0BB5
#define PB_B6_BANDGAP_02                                            0x0BB6
#define PB_B7_IMPEDANCE_00                                          0x0BB7
#define PB_B8_IMPEDANCE_01                                          0x0BB8
#define PB_B9_IMPEDANCE_02                                          0x0BB9
#define PB_BA_IMPEDANCE_03                                          0x0BBA
#define PB_BB_IMPEDANCE_04                                          0x0BBB
#define PB_BC_CMU_LDO                                               0x0BBC
#define PB_BD_CMU_00                                                0x0BBD
#define PB_BE_CMU_01                                                0x0BBE
#define PB_BF_CMU_02                                                0x0BBF
#define PB_C0_CMU_03                                                0x0BC0
#define PB_C1_CMU_04                                                0x0BC1
#define PB_C2_CMU_05                                                0x0BC2
#define PB_C3_CMU_06                                                0x0BC3
#define PB_C4_CMU_07                                                0x0BC4
#define PB_C5_CMU_08                                                0x0BC5
#define PB_C6_KOFFSET_00                                            0x0BC6
#define PB_C7_KOFFSET_01                                            0x0BC7
#define PB_C8_KOFFSET_02                                            0x0BC8
#define PB_C9_KOFFSET_03                                            0x0BC9
#define PB_CA_KOFFSET_04                                            0x0BCA
#define PB_CB_KOFFSET_05                                            0x0BCB
#define PB_CC_KOFFSET_06                                            0x0BCC
#define PB_CD_KOFFSET_07                                            0x0BCD
#define PB_CE_ANA_CDR_00                                            0x0BCE
#define PB_CF_ANA_CDR_01                                            0x0BCF
#define PB_D0_ANA_CDR_02                                            0x0BD0
#define PB_D1_ANA_CDR_03                                            0x0BD1
#define PB_D2_ANA_CDR_04                                            0x0BD2
#define PB_D3_ANA_CDR_05                                            0x0BD3
#define PB_D4_ANA_CDR_06                                            0x0BD4
#define PB_D5_ANA_CDR_07                                            0x0BD5
#define PB_D6_ANA_CDR_08                                            0x0BD6
#define PB_D7_ANA_CDR_09                                            0x0BD7
#define PB_D8_TMDS_RESET                                            0x0BD8
#define PB_D9_TMDS_CONT_0                                           0x0BD9
#define PB_DA_TMDS_CONT_1                                           0x0BDA
#define PB_DB_TMDS_CONT_2                                           0x0BDB
#define PB_DC_TMDS_CONT_3                                           0x0BDC
#define PB_DD_TMDS_CONT_4                                           0x0BDD
#define PB_DE_TMDS_CONT_5                                           0x0BDE
#define PB_DF_TMDS_CONT_6                                           0x0BDF
#define PB_E0_EN_00                                                 0x0BE0
#define PB_E1_EN_01                                                 0x0BE1
#define PB_E2_EN_02                                                 0x0BE2
#define PB_E3_EN_03                                                 0x0BE3
#define PB_E4_ST_00                                                 0x0BE4
#define PB_E5_ST_01                                                 0x0BE5
#define PB_E6_ST_02                                                 0x0BE6
#define PB_E7_ST_03                                                 0x0BE7
#define PB_E8_ST_04                                                 0x0BE8
#define PB_E9_ERROR_COUNT_0                                         0x0BE9
#define PB_EA_ERROR_COUNT_1                                         0x0BEA
#define PB_EB_ERROR_COUNT_2                                         0x0BEB
#define PB_EC_ERROR_COUNT_3                                         0x0BEC
#define PB_ED_ERROR_COUNT_4                                         0x0BED
#define PB_EE_ERROR_COUNT_5                                         0x0BEE
#define PB_EF_DEBUG                                                 0x0BEF
#define PB_F0_CDR_01                                                0x0BF0
#define PB_F1_CDR_02                                                0x0BF1
#define PB_F2_CDR_03                                                0x0BF2
#define PB_F3_CDR_04                                                0x0BF3
#define PB_F4_CDR_05                                                0x0BF4
#define PB_F5_CDR_06                                                0x0BF5
#define PB_F6_CDR_07                                                0x0BF6
#define PB_F7_CDR_08                                                0x0BF7
#define PB_F8_CDR_09                                                0x0BF8
#define PB_F9_CDR_10                                                0x0BF9
#define PB_FA_ACC_00                                                0x0BFA
#define PB_FB_ACC_01                                                0x0BFB
#define PB_FC_TIMER_BER_0                                           0x0BFC
#define PB_FD_TIMER_BER_1                                           0x0BFD


//--------------------------------------------------
// Pin Share Register (Page 10)
//--------------------------------------------------
#define P10_00_PIN_SHARE_CTRL10                                     0x1000
#define P10_01_PIN_SHARE_CTRL11                                     0x1001
#define P10_02_PIN_SHARE_CTRL12                                     0x1002
#define P10_03_PIN_SHARE_CTRL13                                     0x1003
#define P10_04_PIN_SHARE_CTRL14                                     0x1004
#define P10_05_PIN_SHARE_CTRL15                                     0x1005
#define P10_06_PIN_SHARE_CTRL16                                     0x1006
#define P10_07_PIN_SHARE_CTRL17                                     0x1007
#define P10_08_PIN_SHARE_CTRL30                                     0x1008
#define P10_09_PIN_SHARE_CTRL31                                     0x1009
#define P10_0A_PIN_SHARE_CTRL32                                     0x100A
#define P10_0B_PIN_SHARE_CTRL33                                     0x100B
#define P10_0C_PIN_SHARE_CTRL34                                     0x100C
#define P10_0D_PIN_SHARE_CTRL35                                     0x100D
#define P10_0E_PIN_SHARE_CTRL36                                     0x100E
#define P10_0F_PIN_SHARE_CTRL37                                     0x100F
#define P10_10_PIN_SHARE_CTRL40                                     0x1010
#define P10_11_PIN_SHARE_CTRL41                                     0x1011
#define P10_12_PIN_SHARE_CTRL42                                     0x1012
#define P10_13_PIN_SHARE_CTRL43                                     0x1013
#define P10_14_PIN_SHARE_CTRL44                                     0x1014
#define P10_15_PIN_SHARE_CTRL45                                     0x1015
#define P10_16_PIN_SHARE_CTRL46                                     0x1016
#define P10_17_PIN_SHARE_CTRL47                                     0x1017
#define P10_18_PIN_SHARE_CTRL50                                     0x1018
#define P10_19_PIN_SHARE_CTRL51                                     0x1019
#define P10_1A_PIN_SHARE_CTRL52                                     0x101A
#define P10_1B_PIN_SHARE_CTRL53                                     0x101B
#define P10_1C_PIN_SHARE_CTRL54                                     0x101C
#define P10_1D_PIN_SHARE_CTRL55                                     0x101D
#define P10_1E_PIN_SHARE_CTRL56                                     0x101E
#define P10_1F_PIN_SHARE_CTRL57                                     0x101F
#define P10_20_PIN_SHARE_CTRL60                                     0x1020
#define P10_21_PIN_SHARE_CTRL61                                     0x1021
#define P10_22_PIN_SHARE_CTRL62                                     0x1022
#define P10_23_PIN_SHARE_CTRL63                                     0x1023
#define P10_24_PIN_SHARE_CTRL64                                     0x1024
#define P10_25_PIN_SHARE_CTRL65                                     0x1025
#define P10_26_PIN_SHARE_CTRL66                                     0x1026
#define P10_27_PIN_SHARE_CTRL67                                     0x1027
#define P10_28_PIN_SHARE_CTRL70                                     0x1028
#define P10_29_PIN_SHARE_CTRL71                                     0x1029
#define P10_2A_PIN_SHARE_CTRL72                                     0x102A
#define P10_2B_PIN_SHARE_CTRL73                                     0x102B
#define P10_2C_PIN_SHARE_CTRL74                                     0x102C
#define P10_2D_PIN_SHARE_CTRL75                                     0x102D
#define P10_2E_PIN_SHARE_CTRL76                                     0x102E
#define P10_2F_PIN_SHARE_CTRL77                                     0x102F
#define P10_30_PIN_SHARE_CTRL80                                     0x1030
#define P10_31_PIN_SHARE_CTRL81                                     0x1031
#define P10_32_PIN_SHARE_CTRL82                                     0x1032
#define P10_33_PIN_SHARE_CTRL83                                     0x1033
#define P10_34_PIN_SHARE_CTRL84                                     0x1034
#define P10_35_PIN_SHARE_CTRL85                                     0x1035
#define P10_36_PIN_SHARE_CTRL86                                     0x1036
#define P10_38_DUMMY                                                0x1038
#define P10_39_DUMMY                                                0x1039
#define P10_3A_DUMMY                                                0x103A
#define P10_3B_LVDS_TTL_SELECT0                                     0x103B
#define P10_3C_LVDS_TTL_SELECT1                                     0x103C
#define P10_3D_LVDS_TTL_SELECT2                                     0x103D
#define P10_3E_LVDS_TTL_SELECT3                                     0x103E
#define P10_3F_LVDS_TTL_SELECT4                                     0x103F
#define P10_40_LVDS_TTL_SELECT5                                     0x1040
#define P10_41_LVDS_TTL_SELECT6                                     0x1041
#define P10_42_LVDS_TTL_SELECT7                                     0x1042
#define P10_43_LVDS_TTL_SELECT8                                     0x1043
#define P10_44_LVDS_TTL_SELECT9                                     0x1044
#define P10_75_PIN_SLEW_RATE_CTRL0                                  0x1075
#define P10_77_PIN_SCHMITT_CTRL0                                    0x1077
#define P10_78_PIN_SCHMITT_CTRL1                                    0x1078
#define P10_79_DUMMY                                                0x1079
#define P10_7A_PIN_PULLUP_CTRL00                                    0x107A
#define P10_7B_PIN_PULLUP_CTRL01                                    0x107B
#define P10_7C_PIN_PULLUP_CTRL02                                    0x107C
#define P10_7D_PIN_PULLUP_CTRL03                                    0x107D
#define P10_7E_PIN_PULLUP_CTRL04                                    0x107E
#define P10_7F_PIN_PULLUP_CTRL05                                    0x107F
#define P10_80_PIN_PULLUP_CTRL06                                    0x1080
#define P10_81_PIN_PULLUP_CTRL07                                    0x1081
#define P10_82_PIN_PULLUP_CTRL08                                    0x1082
#define P10_83_PIN_PULLUP_CTRL09                                    0x1083
#define P10_84_PIN_PULLUP_CTRL0A                                    0x1084
#define P10_85_PIN_PULLUP_CTRL0B                                    0x1085
#define P10_86_PIN_PULLUP_CTRL0C                                    0x1086
#define P10_87_PIN_PULLUP_CTRL0D                                    0x1087
#define P10_88_DUMMY                                                0x1088
#define P10_A0_INT_PIN_SCHMITT_CTRL0                                0x10A0
#define P10_A1_DUMMY                                                0x10A1
#define P10_B0_PIN_DRIVING_CTRL00                                   0x10B0
#define P10_B1_PIN_DRIVING_CTRL01                                   0x10B1
#define P10_B2_PIN_DRIVING_CTRL02                                   0x10B2
#define P10_B3_DUMMY                                                0x10B3
#define P10_B4_PIN_DRIVING_CTRL04                                   0x10B4
#define P10_B5_PIN_DRIVING_CTRL05                                   0x10B5
#define P10_B6_PIN_DRIVING_CTRL06                                   0x10B6
#define P10_C0_DVI_CTRL_OUT_SEL                                     0x10C0


//--------------------------------------------------
// Light Super Resolution (LSR) (Page 11)
//--------------------------------------------------
#define P11_B9_SCALER_LSR_HLW                                       0x11B9
#define P11_CC_LSR_HLW_H_START_HIGH                                 0x11CC
#define P11_CD_LSR_HLW_H_START_LOW                                  0x11CD
#define P11_CE_LSR_HLW_H_END_HIGH                                   0x11CE
#define P11_CF_LSR_HLW_H_END_LOW                                    0x11CF
#define P11_D0_LSR_HLW_V_START_HIGH                                 0x11D0
#define P11_D1_LSR_HLW_V_START_LOW                                  0x11D1
#define P11_D2_LSR_HLW_V_END_HIGH                                   0x11D2
#define P11_D3_LSR_HLW_V_END_LOW                                    0x11D3


//--------------------------------------------------
// Light Super Resolution (LSR) (Page 14)
//--------------------------------------------------
#define P14_00_LSR_V_SOB_SLP_LSB                                    0x1400
#define P14_01_LSR_V_SOB_TXT_COR_G_HP_UB_LSB                        0x1401
#define P14_02_LSR_V_HP_UP_COR_THD_LSB                              0x1402
#define P14_03_LSR_V_COR_THD_HP_LB_LSB                              0x1403
#define P14_04_LSR_V_HP_LB_SOB_TXT_LB_G_LSB                         0x1404
#define P14_05_LSR_V_SOB_TXT_COR_TXT_LB_G_LSB                       0x1405
#define P14_10_LSR_TL_THD_MSB                                       0x1410
#define P14_11_LSR_TL_THD_LSB                                       0x1411
#define P14_12_LSR_TL_OFFSET                                        0x1412
#define P14_13_LSR_BG_THD_MSB                                       0x1413
#define P14_14_LSR_BG_THD_LSB                                       0x1414
#define P14_15_LSR_BG_OFFSET                                        0x1415
#define P14_16_LSR_SUMDIFF_RSFT                                     0x1416
#define P14_17_LSR_SUMDIFF_THD                                      0x1417
#define P14_18_LSR_SUMDIFF_OFFSET                                   0x1418
#define P14_19_LSR_TL_GAIN                                          0x1419
#define P14_1A_LSR_TEST_OUT                                         0x141A
#define P14_C0_LSR_CTRL                                             0x14C0
#define P14_C1_LSR_H_HP_FILTER_C0                                   0x14C1
#define P14_C2_LSR_H_HP_FILTER_C1C2                                 0x14C2
#define P14_C3_LSR_H_SOB_5TAP                                       0x14C3
#define P14_C4_LSR_H_SOB_THD2_MSB                                   0x14C4
#define P14_C5_LSR_H_SOB_THD2_LSB                                   0x14C5
#define P14_C6_LSR_H_SOB_THD1_MSB                                   0x14C6
#define P14_C7_LSR_H_SOB_THD1_LSB                                   0x14C7
#define P14_C8_LSR_H_SOB_THD0                                       0x14C8
#define P14_C9_LSR_H_SOB_BASE                                       0x14C9
#define P14_CA_LSR_H_SOB_SLP_R                                      0x14CA
#define P14_CB_LSR_H_SOB_SLP_F                                      0x14CB
#define P14_CC_LSR_H_SOB_TXT_COR_G_P_MSB                            0x14CC
#define P14_CD_LSR_H_SOB_TXT_COR_G_P_LSB                            0x14CD
#define P14_CE_LSR_H_HP_UB_P                                        0x14CE
#define P14_CF_LSR_H_HP_UB_N                                        0x14CF
#define P14_D0_LSR_H_COR_THD_P                                      0x14D0
#define P14_D1_LSR_H_COR_THD_N                                      0x14D1
#define P14_D2_LSR_H_HP_LB_P                                        0x14D2
#define P14_D3_LSR_H_HP_LB_N                                        0x14D3
#define P14_D4_LSR_H_SOB_TXT_LB_G_P_MSB                             0x14D4
#define P14_D5_LSR_H_SOB_TXT_LB_G_P_LSB                             0x14D5
#define P14_D6_LSR_H_SOB_TXT_COR_G_N_MSB                            0x14D6
#define P14_D7_LSR_H_SOB_TXT_COR_G_N_LSB                            0x14D7
#define P14_D8_LSR_H_SOB_TXT_LB_G_N_MSB                             0x14D8
#define P14_D9_LSR_H_SOB_TXT_LB_G_N_LSB                             0x14D9
#define P14_E0_LSR_V_SOB_THD2_MSB                                   0x14E0
#define P14_E1_LSR_V_SOB_THD2_LSB                                   0x14E1
#define P14_E2_LSR_V_SOB_THD1_MSB                                   0x14E2
#define P14_E3_LSR_V_SOB_THD1_LSB                                   0x14E3
#define P14_E4_SR_V_SOB_THD0                                        0x14E4
#define P14_E5_LSR_V_SOB_BASE                                       0x14E5
#define P14_E6_LSR_V_SOB_SLP_R                                      0x14E6
#define P14_E7_LSR_V_SOB_SLP_F                                      0x14E7
#define P14_E8_LSR_V_SOB_TXT_COR_G_P_MSB                            0x14E8
#define P14_E9_LSR_V_SOB_TXT_COR_G_P_LSB                            0x14E9
#define P14_EA_LSR_V_HP_UB_P                                        0x14EA
#define P14_EB_LSR_V_HP_UB_N                                        0x14EB
#define P14_EC_LSR_V_COR_THD_P                                      0x14EC
#define P14_ED_LSR_V_COR_THD_N                                      0x14ED
#define P14_EE_LSR_V_HP_LB_P                                        0x14EE
#define P14_EF_LSR_V_HP_LB_N                                        0x14EF
#define P14_F0_LSR_V_SOB_TXT_LB_G_P_MSB                             0x14F0
#define P14_F1_LSR_V_SOB_TXT_LB_G_P_LSB                             0x14F1
#define P14_F2_LSR_V_SOB_TXT_COR_G_N_MSB                            0x14F2
#define P14_F3_LSR_V_SOB_TXT_COR_G_N_LSB                            0x14F3
#define P14_F4_LSR_V_SOB_TXT_LB_G_N_MSB                             0x14F4
#define P14_F5_LSR_V_SOB_TXT_LB_G_N_LSB                             0x14F5
#define P14_F6_LSR_H_SOB_THD12_LSB                                  0x14F6
#define P14_F7_LSR_H_SOB_THD0_BASE_LSB                              0x14F7
#define P14_F8_LSR_H_SOB_SLP_LSB                                    0x14F8
#define P14_F9_LSR_H_SOB_TXT_COR_G_HP_UB_LSB                        0x14F9
#define P14_FA_LSR_H_HP_UB_COR_THD_LSB                              0x14FA
#define P14_FB_LSR_H_COR_THD_HP_LB_LSB                              0x14FB
#define P14_FC_LSR_H_HP_LB_SOB_TXT_LB_G_LSB                         0x14FC
#define P14_FD_LSR_H_SOB_TXT_COR_TXT_LB_G_LSB                       0x14FD
#define P14_FE_LSR_V_SOB_THD12_LSB                                  0x14FE
#define P14_FF_LSR_V_SOB_THD0_BASE_LSB                              0x14FF


//--------------------------------------------------
// Color Conversion - YCCtoRGB 10bit In / 10bit Out (Page 14)
//--------------------------------------------------
#define P14_A1_SR_YCC2RGB_CTRL                                      0x14A1
#define P14_A2_SR_YCC2RGB_COEF_K11_MSB                              0x14A2
#define P14_A3_SR_YCC2RGB_COEF_K11_LSB                              0x14A3
#define P14_A4_SR_YCC2RGB_COEF_K13_MSB                              0x14A4
#define P14_A5_SR_YCC2RGB_COEF_K13_LSB                              0x14A5
#define P14_A6_SR_YCC2RGB_COEF_K22_MSB                              0x14A6
#define P14_A7_SR_YCC2RGB_COEF_K22_LSB                              0x14A7
#define P14_A8_SR_YCC2RGB_COEF_K23_MSB                              0x14A8
#define P14_A9_SR_YCC2RGB_COEF_K23_LSB                              0x14A9
#define P14_AA_SR_YCC2RGB_COEF_K32_MSB                              0x14AA
#define P14_AB_SR_YCC2RGB_COEF_K32_LSB                              0x14AB
#define P14_AC_SR_YCC2RGB_R_OFFSET_MSB                              0x14AC
#define P14_AD_SR_YCC2RGB_R_OFFSET_LSB                              0x14AD
#define P14_AE_SR_YCC2RGB_G_OFFSET_MSB                              0x14AE
#define P14_AF_SR_YCC2RGB_G_OFFSET_LSB                              0x14AF
#define P14_B0_SR_YCC2RGB_B_OFFSET_MSB                              0x14B0
#define P14_B1_SR_YCC2RGB_B_OFFSET_LSB                              0x14B1
#define P14_B2_SR_YCC2RGB_R_GAIN_MSB                                0x14B2
#define P14_B3_SR_YCC2RGB_R_GAIN_LSB                                0x14B3
#define P14_B4_SR_YCC2RGB_G_GAIN_MSB                                0x14B4
#define P14_B5_SR_YCC2RGB_G_GAIN_LSB                                0x14B5
#define P14_B6_SR_YCC2RGB_B_GAIN_MSB                                0x14B6
#define P14_B7_SR_YCC2RGB_B_GAIN_LSB                                0x14B7
#define P14_B8_SR_YCC2RGB_DUMMY                                     0x14B8


//--------------------------------------------------
// TXAB Port Control for Analog LVDS (Page 15)
//--------------------------------------------------
#define P15_00_LVDS_COMMON_AB_CTRL0                                 0x1500
#define P15_01_LVDS_COMMON_AB_CTRL1                                 0x1501
#define P15_02_LVDS_COMMON_AB_CTRL2                                 0x1502
#define P15_03_LVDS_COMMON_AB_CTRL3                                 0x1503
#define P15_04_LVDS_COMMON_AB_CTRL4                                 0x1504
#define P15_05_LVDS_COMMON_AB_CTRL5                                 0x1505
#define P15_06_LVDS_COMMON_AB_CTRL6                                 0x1506
#define P15_07_LVDS_COMMON_AB_CTRL7                                 0x1507
#define P15_08_LVDS_COMMON_AB_CTRL8                                 0x1508
#define P15_09_LVDS_COMMON_AB_CTRL9                                 0x1509
#define P15_0A_LVDS_COMMON_AB_CTRL10                                0x150A
#define P15_0B_LVDS_COMMON_AB_CTRL11                                0x150B
#define P15_0C_LVDS_COMMON_AB_CTRL12                                0x150C
#define P15_0D_LVDS_COMMON_AB_CTRL13                                0x150D
#define P15_0E_LVDS_COMMON_AB_CTRL14                                0x150E
#define P15_0F_LVDS_COMMON_AB_CTRL15                                0x150F
#define P15_10_LVDS_COMMON_AB_CTRL16                                0x1510
#define P15_11_LVDS_COMMON_AB_CTRL17                                0x1511
#define P15_20_LVDS_PORTA_CTRL0                                     0x1520
#define P15_21_LVDS_PORTA_CTRL1                                     0x1521
#define P15_22_LVDS_PORTA_CTRL2                                     0x1522
#define P15_23_LVDS_PORTA_CTRL3                                     0x1523
#define P15_24_LVDS_PORTA_CTRL4                                     0x1524
#define P15_25_LVDS_PORTA_CTRL5                                     0x1525
#define P15_26_LVDS_PORTA_CTRL6                                     0x1526
#define P15_27_LVDS_PORTA_CTRL7                                     0x1527
#define P15_28_LVDS_PORTA_CTRL8                                     0x1528
#define P15_29_LVDS_PORTA_CTRL9                                     0x1529
#define P15_2A_LVDS_PORTA_CTRL10                                    0x152A
#define P15_2B_LVDS_PORTA_CTRL11                                    0x152B
#define P15_30_LVDS_PORTB_CTRL0                                     0x1530
#define P15_31_LVDS_PORTB_CTRL1                                     0x1531
#define P15_32_LVDS_PORTB_CTRL2                                     0x1532
#define P15_33_LVDS_PORTB_CTRL3                                     0x1533
#define P15_34_LVDS_PORTB_CTRL4                                     0x1534
#define P15_35_LVDS_PORTB_CTRL5                                     0x1535
#define P15_36_LVDS_PORTB_CTRL6                                     0x1536
#define P15_37_LVDS_PORTB_CTRL7                                     0x1537
#define P15_38_LVDS_PORTB_CTRL8                                     0x1538
#define P15_39_LVDS_PORTB_CTRL9                                     0x1539
#define P15_3A_LVDS_PORTB_CTRL10                                    0x153A
#define P15_3B_LVDS_PORTB_CTRL11                                    0x153B


//--------------------------------------------------
// Embedded Timing Controller (Page 15)
//--------------------------------------------------
#define P15_A3_TCON_ADDR                                            0x15A3
#define P15_A4_TCON_DATA                                            0x15A4


//--------------------------------------------------
// On-line Measure Block Overview (Page 16)
//--------------------------------------------------
#define P16_01_MEAS_CTL0                                            0x1601
#define P16_02_MEAS_CTL1                                            0x1602
#define P16_03_MEAS_ERROR_FLG0                                      0x1603
#define P16_04_MEAS_ERROR_FLG1                                      0x1604
#define P16_05_MEAS_HS_PERIOD_A_M                                   0x1605
#define P16_06_MEAS_HS_PERIOD_A_L                                   0x1606
#define P16_07_MEAS_HS_PERIOD_FRA_A                                 0x1607
#define P16_08_MEAS_VS_PERIOD_A_M                                   0x1608
#define P16_09_MEAS_VS_PERIOD_A_L                                   0x1609
#define P16_0A_MEAS_HS_PULSE_A_M                                    0x160A
#define P16_0B_MEAS_HS_PULSE_A_L                                    0x160B
#define P16_0C_MEAS_VS_PULSE_A_M                                    0x160C
#define P16_0D_MEAS_VS_PULSE_A_L                                    0x160D
#define P16_0E_MEAS_HS_PERIOD_D_M                                   0x160E
#define P16_0F_MEAS_HS_PERIOD_D_L                                   0x160F
#define P16_10_MEAS_HS_PERIOD_FRA_D                                 0x1610
#define P16_11_MEAS_VS_PERIOD_D_M                                   0x1611
#define P16_12_MEAS_VS_PERIOD_D_L                                   0x1612
#define P16_13_MEAS_HS_PULSE_D_M                                    0x1613
#define P16_14_MEAS_HS_PULSE_D_L                                    0x1614
#define P16_15_MEAS_HS_VS_DELTA_CTL                                 0x1615
#define P16_16_MEAS_HS_VS_DELTA_IRQ                                 0x1616
#define P16_17_MEAS_HS_VS_DELTA_WD                                  0x1617
#define P16_18_MEAS_HS_VS_ERROR_WD                                  0x1618
#define P16_19_MEAS_HS_VS_ERROR_IRQ                                 0x1619
#define P16_1A_MEAS2_HS_VS_DLY                                      0x161A
#define P16_1C_M1_MEASURE_DUMMY0                                    0x161C
#define P16_1D_M1_MEASURE_DUMMY1                                    0x161D


//--------------------------------------------------
// GDI DFE (Page 1D)
//--------------------------------------------------
#define P1D_A0_L0_DFE_EN_1                                          0x1DA0
#define P1D_A1_L0_DFE_EN_2                                          0x1DA1
#define P1D_A2_L0_LIMIT_INIT                                        0x1DA2
#define P1D_A3_L0_INIT_1                                            0x1DA3
#define P1D_A4_L0_INIT_2                                            0x1DA4
#define P1D_A5_L0_INIT_3                                            0x1DA5
#define P1D_A6_L0_INIT_4                                            0x1DA6
#define P1D_A7_L0_INIT_5                                            0x1DA7
#define P1D_A8_L0_INIT_6                                            0x1DA8
#define P1D_A9_L0_INIT_7                                            0x1DA9
#define P1D_AA_L0_INIT_8                                            0x1DAA
#define P1D_AB_L0_STABLE_FLAG                                       0x1DAB
#define P1D_AF_L0_GDI_DE                                            0x1DAF
#define P1D_B0_L1_DFE_EN_1                                          0x1DB0
#define P1D_B1_L1_DFE_EN_2                                          0x1DB1
#define P1D_B2_L1_LIMIT_INIT                                        0x1DB2
#define P1D_B3_L1_INIT_1                                            0x1DB3
#define P1D_B4_L1_INIT_2                                            0x1DB4
#define P1D_B5_L1_INIT_3                                            0x1DB5
#define P1D_B6_L1_INIT_4                                            0x1DB6
#define P1D_B7_L1_INIT_5                                            0x1DB7
#define P1D_B8_L1_INIT_6                                            0x1DB8
#define P1D_B9_L1_INIT_7                                            0x1DB9
#define P1D_BA_L1_INIT_8                                            0x1DBA
#define P1D_BB_L1_STABLE_FLAG                                       0x1DBB
#define P1D_BF_L1_GDI_DE                                            0x1DBF
#define P1D_C0_L2_DFE_EN_1                                          0x1DC0
#define P1D_C1_L2_DFE_EN_2                                          0x1DC1
#define P1D_C2_L2_LIMIT_INIT                                        0x1DC2
#define P1D_C3_L2_INIT_1                                            0x1DC3
#define P1D_C4_L2_INIT_2                                            0x1DC4
#define P1D_C5_L2_INIT_3                                            0x1DC5
#define P1D_C6_L2_INIT_4                                            0x1DC6
#define P1D_C7_L2_INIT_5                                            0x1DC7
#define P1D_C8_L2_INIT_6                                            0x1DC8
#define P1D_C9_L2_INIT_7                                            0x1DC9
#define P1D_CA_L2_INIT_8                                            0x1DCA
#define P1D_CB_L2_STABLE_FLAG                                       0x1DCB
#define P1D_CF_L2_GDI_DE                                            0x1DCF
#define P1D_D0_L3_DFE_EN_1                                          0x1DD0
#define P1D_D1_L3_DFE_EN_2                                          0x1DD1
#define P1D_D2_L3_LIMIT_INIT                                        0x1DD2
#define P1D_D3_L3_INIT_1                                            0x1DD3
#define P1D_D4_L3_INIT_2                                            0x1DD4
#define P1D_D5_L3_INIT_3                                            0x1DD5
#define P1D_D6_L3_INIT_4                                            0x1DD6
#define P1D_D7_L3_INIT_5                                            0x1DD7
#define P1D_D8_L3_INIT_6                                            0x1DD8
#define P1D_D9_L3_INIT_7                                            0x1DD9
#define P1D_DA_L3_INIT_8                                            0x1DDA
#define P1D_DB_L3_STABLE_FLAG                                       0x1DDB
#define P1D_DF_L3_GDI_DE                                            0x1DDF
#define P1D_E0_MODE_TIMER                                           0x1DE0
#define P1D_E1_TIMER                                                0x1DE1
#define P1D_E2_GAIN_1                                               0x1DE2
#define P1D_E3_GAIN_2                                               0x1DE3
#define P1D_E4_GAIN_3                                               0x1DE4
#define P1D_E5_GAIN_4                                               0x1DE5
#define P1D_E6_LIMIT_1                                              0x1DE6
#define P1D_E7_LIMIT_2                                              0x1DE7
#define P1D_E8_LIMIT_3                                              0x1DE8
#define P1D_E9_LIMIT_4                                              0x1DE9
#define P1D_EA_LIMIT_5                                              0x1DEA
#define P1D_EB_LIMIT_6                                              0x1DEB
#define P1D_EC_LOOP_DIV_1                                           0x1DEC
#define P1D_ED_LOOP_DIV_2                                           0x1DED
#define P1D_EE_GRAY_DEC                                             0x1DEE
#define P1D_EF_RESET_1                                              0x1DEF
#define P1D_F0_COEF_1                                               0x1DF0
#define P1D_F1_COEF_2                                               0x1DF1
#define P1D_F2_COEF_3                                               0x1DF2
#define P1D_F3_COEF_4                                               0x1DF3
#define P1D_F8_GRAY_DEC_2                                           0x1DF8
#define P1D_F9_LIMIT_10                                             0x1DF9
#define P1D_FA_GAIN_PREC                                            0x1DFA
#define P1D_FB_DEBUG                                                0x1DFB


//--------------------------------------------------
// Step Trace Debug Interface (Page 21)
//--------------------------------------------------
#define P21_A0_STEP_DEBG_CTRL                                       0x21A0
#define P21_A1_BP_EN_CTRL                                           0x21A1
#define P21_A2_BP0_ADDR_BANK                                        0x21A2
#define P21_A3_BP0_ADDR_MSB                                         0x21A3
#define P21_A4_BP0_ADDR_LSB                                         0x21A4
#define P21_A5_BP1_ADDR_BANK                                        0x21A5
#define P21_A6_BP1_ADDR_MSB                                         0x21A6
#define P21_A7_BP1_ADDR_LSB                                         0x21A7
#define P21_A8_BP2_ADDR_BANK                                        0x21A8
#define P21_A9_BP2_ADDR_MSB                                         0x21A9
#define P21_AA_BP2_ADDR_LSB                                         0x21AA
#define P21_AB_BP3_ADDR_BANK                                        0x21AB
#define P21_AC_BP3_ADDR_MSB                                         0x21AC
#define P21_AD_BP3_ADDR_LSB                                         0x21AD
#define P21_D0_DBG_ACC_CTRL                                         0x21D0
#define P21_D1_IRAM_ADDR                                            0x21D1
#define P21_D2_IRAM_DATA                                            0x21D2
#define P21_D3_SFR_ADDR                                             0x21D3
#define P21_D4_SFR_DATA                                             0x21D4
#define P21_D5_XDATA_ADDR_MSB                                       0x21D5
#define P21_D6_XDATA_ADDR_LSB                                       0x21D6
#define P21_D7_XDATA_DATA                                           0x21D7
#define P21_D8_CURRENT_PC_BANK                                      0x21D8
#define P21_D9_CURRENT_PC_MSB                                       0x21D9
#define P21_DA_CURRENT_PC_LSB                                       0x21DA


//--------------------------------------------------
// e-Fuse Data (Page 24)
//--------------------------------------------------
#define P24_A0_EFUSE_LOCK                                           0x24A0
#define P24_A1_EFUSE_BURN_IN_1                                      0x24A1
#define P24_A2_EFUSE_BURN_IN_2                                      0x24A2
#define P24_A3_EFUSE_CTRL_0                                         0x24A3
#define P24_A4_EFUSE_CTRL1                                          0x24A4
#define P24_A5_EFUSE_CTRL_2                                         0x24A5
#define P24_A6_EFUSE_DATA0                                          0x24A6
#define P24_A7_EFUSE_DATA1                                          0x24A7
#define P24_A8_EFUSE_DATA2                                          0x24A8
#define P24_A9_EFUSE_DATA3                                          0x24A9
#define P24_AA_EFUSE_DATA4                                          0x24AA
#define P24_AB_EFUSE_DATA5                                          0x24AB
#define P24_AC_EFUSE_DATA6                                          0x24AC
#define P24_AD_EFUSE_DATA7                                          0x24AD
#define P24_AE_EFUSE_DATA8                                          0x24AE
#define P24_AF_EFUSE_DATA9                                          0x24AF
#define P24_B0_EFUSE_DATA10                                         0x24B0
#define P24_B1_EFUSE_DATA11                                         0x24B1
#define P24_B2_EFUSE_DATA12                                         0x24B2
#define P24_B3_EFUSE_DATA13                                         0x24B3
#define P24_B4_EFUSE_DATA14                                         0x24B4
#define P24_B5_EFUSE_DATA15                                         0x24B5


//--------------------------------------------------
// Ringing Filter (Page 25)
//--------------------------------------------------
#define P25_A0_RFILTER_CTRL                                         0x25A0
#define P25_A1_RFILTER_THD                                          0x25A1
#define P25_A2_RFILTER_THD_RNG_EXP                                  0x25A2
#define P25_A3_RFILTER_OFS_COEF                                     0x25A3
#define P25_A4_RFILTER_OFS_RNG_EXP                                  0x25A4
#define P25_A5_RFILTER_DIFF_THD_UB                                  0x25A5
#define P25_A6_RFILTER_DIFF_THD_LB                                  0x25A6
#define P25_A7_RFILTER_FACTOR_TEST_CTRL                             0x25A7


//--------------------------------------------------
// MHL3.0 (Page 26)
//--------------------------------------------------
#define P26_00_MHL_EN                                               0x2600
#define P26_01_MHL_FIFO_CTRL                                        0x2601
#define P26_02_MHL_BIST_CTRL                                        0x2602
#define P26_03_MHL_BIST_CONFIG_1                                    0x2603
#define P26_04_MHL_BIST_CONFIG_2                                    0x2604
#define P26_05_MHL_BIST_ERR_CNT_H                                   0x2605
#define P26_06_MHL_BIST_ERR_CNT_L                                   0x2606
#define P26_07_MHL_DATA_ALIGN_CTRL                                  0x2607
#define P26_08_MHL_PKT_DECODE_CONFIG                                0x2608
#define P26_09_MHL_PKT_DECODE_SEED_H                                0x2609
#define P26_0A_MHL_PKT_DECODE_SEED_L                                0x260A
#define P26_0B_MHL_S2P                                              0x260B
#define P26_0C_MHL_FIFO_FLAG                                        0x260C
#define P26_0D_MHL_BIST_DURATION                                    0x260D
#define P26_0E_MHL_BIST_FIFO_FLAG2                                  0x260E
#define P26_0F_MHL_BIST_RESERVED_2                                  0x260F
#define P26_10_REG_MHL3_OUTPUT_0                                    0x2610
#define P26_11_REG_MHL3_OUTPUT_1                                    0x2611
#define P26_12_REG_MHL3_OUTPUT_2                                    0x2612
#define P26_13_REG_MHL3_OUTPUT_3                                    0x2613
#define P26_14_REG_MHL3_OUTPUT_4                                    0x2614
#define P26_15_REG_MHL3_OUTPUT_5                                    0x2615
#define P26_16_REG_MHL3_OUTPUT_6                                    0x2616
#define P26_17_REG_MHL3_OUTPUT_7                                    0x2617
#define P26_18_REG_MHL3_OUTPUT_8                                    0x2618
#define P26_19_REG_MHL3_OUTPUT_9                                    0x2619
#define P26_1A_REG_MHL3_OUTPUT_A                                    0x261A
#define P26_1B_REG_MHL3_OUTPUT_B                                    0x261B


//--------------------------------------------------
// MHL3.0 Mac Measure (Page 26)
//--------------------------------------------------
#define P26_20_MHL_MEASURE_0                                        0x2620
#define P26_21_MHL_MEASURE_1                                        0x2621
#define P26_22_MHL_MEASURE_2                                        0x2622
#define P26_23_MHL_MEASURE_3                                        0x2623
#define P26_24_MHL_MEASURE_4                                        0x2624
#define P26_25_MHL_MEASURE_5                                        0x2625
#define P26_26_MHL_MEASURE_6                                        0x2626
#define P26_27_MHL_MEASURE_7                                        0x2627
#define P26_28_MHL_MEASURE_8                                        0x2628
#define P26_29_MHL_MEASURE_9                                        0x2629
#define P26_2A_MHL_MEASURE_10                                       0x262A
#define P26_2B_MHL_MEASURE_11                                       0x262B
#define P26_2C_MHL_MEASURE_12                                       0x262C
#define P26_2D_MHL_MEASURE_13                                       0x262D
#define P26_2E_MHL_MEASURE_14                                       0x262E
#define P26_2F_MHL_MEASURE_15                                       0x262F
#define P26_30_MHL_MEASURE_16                                       0x2630
#define P26_31_MHL_MEASURE_17                                       0x2631
#define P26_32_MHL_MEASURE_18                                       0x2632
#define P26_33_MHL_MEASURE_19                                       0x2633
#define P26_34_MHL_MEASURE_20                                       0x2634
#define P26_35_MHL_MEASURE_21                                       0x2635
#define P26_36_MHL_MEASURE_22                                       0x2636
#define P26_37_MHL_MEASURE_23                                       0x2637
#define P26_38_MHL_MEASURE_24                                       0x2638
#define P26_39_MHL_MEASURE_27                                       0x2639
#define P26_3A_MHL_MEASURE_28                                       0x263A
#define P26_3B_MHL_MEASURE_29                                       0x263B
#define P26_3C_MHL_MEASURE_30                                       0x263C
#define P26_3D_MHL_MEASURE_31                                       0x263D
#define P26_3E_MHL_MEASURE_32                                       0x263E
#define P26_3F_MHL_MEASURE_33                                       0x263F
#define P26_40_MHL_MEASURE_34                                       0x2640


//--------------------------------------------------
// DPF (Page 26)
//--------------------------------------------------
#define P26_41_DPF_CTRL_0                                           0x2641
#define P26_42_DP_OUTPUT_CTRL                                       0x2642
#define P26_43_EVBLK2VS_H                                           0x2643
#define P26_44_EVBLK2VS_M                                           0x2644
#define P26_45_EVBLK2VS_L                                           0x2645
#define P26_46_OVBLK2VS_H                                           0x2646
#define P26_47_OVBLK2VS_M                                           0x2647
#define P26_48_OVBLK2VS_L                                           0x2648
#define P26_49_BS2HS_0                                              0x2649
#define P26_4A_BS2HS_1                                              0x264A
#define P26_4B_VS_FRONT_PORCH                                       0x264B
#define P26_4C_MN_DPF_HTT_M                                         0x264C
#define P26_4D_MN_DPF_HTT_L                                         0x264D
#define P26_4E_MN_DPF_HST_M                                         0x264E
#define P26_4F_MN_DPF_HST_L                                         0x264F
#define P26_50_MN_DPF_HWD_M                                         0x2650
#define P26_51_MN_DPF_HWD_L                                         0x2651
#define P26_52_MN_DPF_HSW_M                                         0x2652
#define P26_53_MN_DPF_HSW_L                                         0x2653
#define P26_54_MN_DPF_VTT_M                                         0x2654
#define P26_55_MN_DPF_VTT_L                                         0x2655
#define P26_56_MN_DPF_VST_M                                         0x2656
#define P26_57_MN_DPF_VST_L                                         0x2657
#define P26_58_MN_DPF_VHT_M                                         0x2658
#define P26_59_MN_DPF_VHT_L                                         0x2659
#define P26_5A_MN_DPF_VSW_M                                         0x265A
#define P26_5B_MN_DPF_VSW_L                                         0x265B
#define P26_5C_INTERLACE_MODE_CONFIG                                0x265C
#define P26_5D_TEST0                                                0x265D


//--------------------------------------------------
// CP Control Packet (Page 26)
//--------------------------------------------------
#define P26_80_REG_MHL3_CP0                                         0x2680
#define P26_81_REG_MHL3_CP1                                         0x2681
#define P26_82_REG_MHL3_CP2                                         0x2682
#define P26_83_REG_MHL3_CP3                                         0x2683
#define P26_84_REG_MHL3_CP4                                         0x2684
#define P26_85_REG_MHL3_CP5                                         0x2685
#define P26_86_REG_MHL3_CP6                                         0x2686
#define P26_87_REG_MHL3_CP7                                         0x2687
#define P26_88_REG_MHL3_CP8                                         0x2688
#define P26_89_REG_MHL3_CP9                                         0x2689
#define P26_8A_REG_MHL3_CP10                                        0x268A
#define P26_8B_REG_MHL3_CP11                                        0x268B
#define P26_8C_REG_MHL3_CP12                                        0x268C
#define P26_8D_REG_MHL3_CP13                                        0x268D
#define P26_8E_REG_MHL3_CP14                                        0x268E
#define P26_8F_REG_MHL3_CP15                                        0x268F
#define P26_90_REG_MHL3_CP16                                        0x2690
#define P26_91_REG_MHL3_CP17                                        0x2691
#define P26_92_REG_MHL3_CP18                                        0x2692
#define P26_93_REG_MHL3_CP19                                        0x2693


//--------------------------------------------------
// MHL2.0
//--------------------------------------------------
#define P26_A0_MHL_CTRL_00                                          0x26A0
#define P26_A1_MHL_CTRL_01                                          0x26A1
#define P26_A2_MHL_CTRL_02                                          0x26A2
#define P26_A3_MHL_CTRL_03                                          0x26A3
#define P26_A4_MHL_CTRL_04                                          0x26A4
#define P26_A5_MHL_CTRL_05                                          0x26A5
#define P26_A6_MHL_CTRL_06                                          0x26A6
#define P26_A7_MHL_CTRL_07                                          0x26A7
#define P26_A8_MHL_CTRL_08                                          0x26A8
#define P26_A9_MHL_CTRL_09                                          0x26A9
#define P26_AA_MHL_CTRL_0A                                          0x26AA
#define P26_AB_MHL_CTRL_0B                                          0x26AB
#define P26_AC_MHL_CTRL_0C                                          0x26AC
#define P26_AD_MHL_CTRL_0D                                          0x26AD
#define P26_AE_MHL_CTRL_0E                                          0x26AE
#define P26_AF_MHL_CTRL_0F                                          0x26AF
#define P26_B0_MHL_CTRL_10                                          0x26B0
#define P26_B1_MHL_CTRL_11                                          0x26B1
#define P26_B2_MHL_CTRL_12                                          0x26B2
#define P26_B3_MHL_CTRL_13                                          0x26B3
#define P26_B4_MHL_CTRL_14                                          0x26B4
#define P26_B5_MHL_CTRL_15                                          0x26B5
#define P26_B6_MHL_CTRL_16                                          0x26B6


//--------------------------------------------------
// ECBUS A-PHY (Page 27)
//--------------------------------------------------
#define P27_00_ECBUS_EN                                             0x2700
#define P27_01_ECBUS_STEP_CTRL                                      0x2701
#define P27_02_ECBUS_SWITCH_CTRL                                    0x2702
#define P27_03_ECBUS_FEEDBACK_CTRL                                  0x2703
#define P27_04_EBUS_VREF_CTRL_0                                     0x2704
#define P27_05_EBUS_VREF_CTRL_1                                     0x2705
#define P27_06_ECBUS_Z0_CTRL_0                                      0x2706
#define P27_07_ECBUS_Z0_CTRL_1                                      0x2707
#define P27_08_ECBUS_DATA_CTRL                                      0x2708
#define P27_09_ECBUS_RESERVED_0                                     0x2709
#define P27_0A_ECBUS_RESERVED_1                                     0x270A
#define P27_0B_ECBUS_RESERVED_2                                     0x270B
#define P27_0C_ECBUS_PHY_BIST                                       0x270C


//--------------------------------------------------
// CBUS PHY (Page 27)
//--------------------------------------------------
#define P27_A0_CBUS_EN_0                                            0x27A0
#define P27_A1_CBUS_EN_1                                            0x27A1
#define P27_A2_CBUS_RES_AUTOK_0                                     0x27A2
#define P27_A3_CBUS_RES_AUTOK_1                                     0x27A3
#define P27_A4_CBUS_RES_AUTOK_2                                     0x27A4
#define P27_A5_CBUS_RES_AUTOK_3                                     0x27A5
#define P27_A6_CBUS_INPUT_CONTROL                                   0x27A6
#define P27_A7_CBUS_OUTPUT_CONTROL_0                                0x27A7
#define P27_A8_CBUS_OUTPUT_CONTROL_1                                0x27A8


//--------------------------------------------------
// OCBUS for MHL3.0
//--------------------------------------------------
#define P28_00_OCBUS_CTRL_00                                        0x2800
#define P28_01_OCBUS_CTRL_01                                        0x2801
#define P28_10_OCBUS_CTRL_10                                        0x2810
#define P28_11_OCBUS_CTRL_11                                        0x2811
#define P28_12_OCBUS_CTRL_12                                        0x2812
#define P28_13_OCBUS_CTRL_13                                        0x2813
#define P28_14_OCBUS_CTRL_14                                        0x2814
#define P28_15_OCBUS_CTRL_15                                        0x2815
#define P28_16_OCBUS_CTRL_16                                        0x2816
#define P28_17_OCBUS_CTRL_17                                        0x2817
#define P28_18_OCBUS_CTRL_18                                        0x2818
#define P28_19_OCBUS_CTRL_19                                        0x2819
#define P28_1A_OCBUS_CTRL_1A                                        0x281A
#define P28_1B_OCBUS_CTRL_1B                                        0x281B
#define P28_1C_OCBUS_CTRL_1C                                        0x281C
#define P28_1D_OCBUS_CTRL_1D                                        0x281D
#define P28_1E_OCBUS_CTRL_1E                                        0x281E
#define P28_1F_OCBUS_CTRL_1F                                        0x281F
#define P28_20_OCBUS_CTRL_20                                        0x2820
#define P28_21_OCBUS_CTRL_21                                        0x2821
#define P28_22_OCBUS_CTRL_22                                        0x2822
#define P28_23_OCBUS_CTRL_23                                        0x2823
#define P28_24_OCBUS_CTRL_24                                        0x2824
#define P28_25_OCBUS_CTRL_25                                        0x2825


//--------------------------------------------------
// CBUS0 MAC (Page 28)
//--------------------------------------------------
#define P28_A0_CBUS_CTRL_00                                         0x28A0
#define P28_A1_CBUS_CTRL_01                                         0x28A1
#define P28_A2_CBUS_CTRL_02                                         0x28A2
#define P28_A3_CBUS_CTRL_03                                         0x28A3
#define P28_A4_CBUS_CTRL_04                                         0x28A4
#define P28_A5_CBUS_CTRL_05                                         0x28A5
#define P28_A6_CBUS_CTRL_06                                         0x28A6
#define P28_A7_CBUS_CTRL_07                                         0x28A7
#define P28_A8_CBUS_CTRL_08                                         0x28A8
#define P28_A9_CBUS_CTRL_09                                         0x28A9
#define P28_AA_CBUS_CTRL_0A                                         0x28AA
#define P28_AB_CBUS_CTRL_0B                                         0x28AB
#define P28_AC_CBUS_CTRL_0C                                         0x28AC
#define P28_AD_CBUS_CTRL_0D                                         0x28AD
#define P28_AE_CBUS_CTRL_0E                                         0x28AE
#define P28_AF_CBUS_CTRL_0F                                         0x28AF
#define P28_B0_CBUS_CTRL_10                                         0x28B0
#define P28_B1_CBUS_CTRL_11                                         0x28B1
#define P28_B2_CBUS_CTRL_12                                         0x28B2
#define P28_B3_CBUS_CTRL_13                                         0x28B3
#define P28_B4_CBUS_CTRL_14                                         0x28B4
#define P28_B5_CBUS_CTRL_15                                         0x28B5
#define P28_B6_CBUS_CTRL_16                                         0x28B6
#define P28_B7_CBUS_CTRL_17                                         0x28B7
#define P28_B8_CBUS_CTRL_18                                         0x28B8
#define P28_BA_CBUS_CTRL_1A                                         0x28BA
#define P28_BB_CBUS_CTRL_1B                                         0x28BB
#define P28_BC_CBUS_CTRL_1C                                         0x28BC
#define P28_BD_CBUS_CTRL_1D                                         0x28BD
#define P28_BE_CBUS_CTRL_1E                                         0x28BE
#define P28_BF_CBUS_CTRL_1F                                         0x28BF
#define P28_C0_CBUS_CTRL_20                                         0x28C0
#define P28_C1_CBUS_CTRL_21                                         0x28C1
#define P28_C2_CBUS_CTRL_22                                         0x28C2
#define P28_C3_CBUS_CTRL_23                                         0x28C3
#define P28_C4_CBUS_CTRL_24                                         0x28C4
#define P28_C5_CBUS_CTRL_25                                         0x28C5
#define P28_C6_CBUS_CTRL_26                                         0x28C6
#define P28_C8_CBUS_CTRL_28                                         0x28C8
#define P28_C9_CBUS_CTRL_29                                         0x28C9
#define P28_CA_CBUS_CTRL_2A                                         0x28CA
#define P28_CB_CBUS_CTRL_2B                                         0x28CB
#define P28_CC_CBUS_CTRL_2C                                         0x28CC
#define P28_CD_CBUS_CTRL_2D                                         0x28CD
#define P28_CE_CBUS_CTRL_2E                                         0x28CE
#define P28_CF_CBUS_CTRL_2F                                         0x28CF
#define P28_D0_CBUS_CTRL_30                                         0x28D0
#define P28_D1_CBUS_CTRL_31                                         0x28D1
#define P28_D2_CBUS_CTRL_32                                         0x28D2
#define P28_D3_CBUS_CTRL_33                                         0x28D3
#define P28_D4_CBUS_CTRL_34                                         0x28D4
#define P28_D5_CBUS_CTRL_35                                         0x28D5
#define P28_D6_CBUS_CTRL_36                                         0x28D6
#define P28_D7_CBUS_CTRL_37                                         0x28D7
#define P28_D8_CBUS_CTRL_38                                         0x28D8
#define P28_D9_CBUS_CTRL_39                                         0x28D9
#define P28_DA_CBUS_CTRL_3A                                         0x28DA
#define P28_DB_CBUS_CTRL_3B                                         0x28DB
#define P28_DC_CBUS_CTRL_3C                                         0x28DC
#define P28_DD_CBUS_CTRL_3D                                         0x28DD
#define P28_DE_CBUS_CTRL_3E                                         0x28DE
#define P28_DF_CBUS_CTRL_3F                                         0x28DF
#define P28_E0_CBUS_CTRL_40                                         0x28E0
#define P28_E1_CBUS_CTRL_41                                         0x28E1
#define P28_E2_CBUS_CTRL_42                                         0x28E2
#define P28_E3_CBUS_CTRL_43                                         0x28E3
#define P28_E4_CBUS_CTRL_44                                         0x28E4
#define P28_E5_CBUS_CTRL_45                                         0x28E5
#define P28_E6_CBUS_CTRL_46                                         0x28E6
#define P28_E7_CBUS_CTRL_47                                         0x28E7
#define P28_E8_CBUS_CTRL_48                                         0x28E8
#define P28_E9_CBUS_CTRL_49                                         0x28E9
#define P28_EA_CBUS_CTRL_4A                                         0x28EA
#define P28_EB_CBUS_CTRL_4B                                         0x28EB
#define P28_EC_CBUS_CTRL_4C                                         0x28EC
#define P28_ED_CBUS_CTRL_4D                                         0x28ED
#define P28_EE_CBUS_CTRL_4E                                         0x28EE
#define P28_EF_CBUS_CTRL_4F                                         0x28EF
#define P28_F0_CBUS_CTRL_50                                         0x28F0
#define P28_F1_CBUS_CTRL_51                                         0x28F1
#define P28_F2_CBUS_CTRL_52                                         0x28F2
#define P28_F3_CBUS_CTRL_53                                         0x28F3
#define P28_F4_CBUS_CTRL_54                                         0x28F4
#define P28_F5_CBUS_CTRL_55                                         0x28F5
#define P28_F6_CBUS_CTRL_56                                         0x28F6
#define P28_F7_CBUS_CTRL_57                                         0x28F7
#define P28_F8_CBUS_CTRL_58                                         0x28F8
#define P28_F9_CBUS_CTRL_59                                         0x28F9
#define P28_FA_CBUS_CTRL_5A                                         0x28FA
#define P28_FB_CBUS_CTRL_5B                                         0x28FB
#define P28_FC_CBUS_CTRL_5C                                         0x28FC
#define P28_FD_CBUS_CTRL_5D                                         0x28FD


//--------------------------------------------------
// CBUS1 MAC (Page 29)
//--------------------------------------------------
#define P29_A0_CBUS_CTRL_00                                         0x29A0
#define P29_A1_CBUS_CTRL_01                                         0x29A1
#define P29_A2_CBUS_CTRL_02                                         0x29A2
#define P29_A3_CBUS_CTRL_03                                         0x29A3
#define P29_A4_CBUS_CTRL_04                                         0x29A4
#define P29_A5_CBUS_CTRL_05                                         0x29A5
#define P29_A6_CBUS_CTRL_06                                         0x29A6
#define P29_A7_CBUS_CTRL_07                                         0x29A7
#define P29_A8_CBUS_CTRL_08                                         0x29A8
#define P29_A9_CBUS_CTRL_09                                         0x29A9
#define P29_AA_CBUS_CTRL_0A                                         0x29AA
#define P29_AB_CBUS_CTRL_0B                                         0x29AB
#define P29_AC_CBUS_CTRL_0C                                         0x29AC
#define P29_AD_CBUS_CTRL_0D                                         0x29AD
#define P29_AE_CBUS_CTRL_0E                                         0x29AE
#define P29_AF_CBUS_CTRL_0F                                         0x29AF
#define P29_B0_CBUS_CTRL_10                                         0x29B0
#define P29_B1_CBUS_CTRL_11                                         0x29B1
#define P29_B2_CBUS_CTRL_12                                         0x29B2
#define P29_B3_CBUS_CTRL_13                                         0x29B3
#define P29_B4_CBUS_CTRL_14                                         0x29B4
#define P29_B5_CBUS_CTRL_15                                         0x29B5
#define P29_B6_CBUS_CTRL_16                                         0x29B6
#define P29_B7_CBUS_CTRL_17                                         0x29B7
#define P29_B8_CBUS_CTRL_18                                         0x29B8
#define P29_BA_CBUS_CTRL_1A                                         0x29BA
#define P29_BB_CBUS_CTRL_1B                                         0x29BB
#define P29_BC_CBUS_CTRL_1C                                         0x29BC
#define P29_BD_CBUS_CTRL_1D                                         0x29BD
#define P29_BE_CBUS_CTRL_1E                                         0x29BE
#define P29_BF_CBUS_CTRL_1F                                         0x29BF
#define P29_C0_CBUS_CTRL_20                                         0x29C0
#define P29_C1_CBUS_CTRL_21                                         0x29C1
#define P29_C2_CBUS_CTRL_22                                         0x29C2
#define P29_C3_CBUS_CTRL_23                                         0x29C3
#define P29_C4_CBUS_CTRL_24                                         0x29C4
#define P29_C5_CBUS_CTRL_25                                         0x29C5
#define P29_C6_CBUS_CTRL_26                                         0x29C6
#define P29_C8_CBUS_CTRL_28                                         0x29C8
#define P29_C9_CBUS_CTRL_29                                         0x29C9
#define P29_CA_CBUS_CTRL_2A                                         0x29CA
#define P29_CB_CBUS_CTRL_2B                                         0x29CB
#define P29_CC_CBUS_CTRL_2C                                         0x29CC
#define P29_CD_CBUS_CTRL_2D                                         0x29CD
#define P29_CE_CBUS_CTRL_2E                                         0x29CE
#define P29_CF_CBUS_CTRL_2F                                         0x29CF
#define P29_D0_CBUS_CTRL_30                                         0x29D0
#define P29_D1_CBUS_CTRL_31                                         0x29D1
#define P29_D2_CBUS_CTRL_32                                         0x29D2
#define P29_D3_CBUS_CTRL_33                                         0x29D3
#define P29_D4_CBUS_CTRL_34                                         0x29D4
#define P29_D5_CBUS_CTRL_35                                         0x29D5
#define P29_D6_CBUS_CTRL_36                                         0x29D6
#define P29_D7_CBUS_CTRL_37                                         0x29D7
#define P29_D8_CBUS_CTRL_38                                         0x29D8
#define P29_D9_CBUS_CTRL_39                                         0x29D9
#define P29_DA_CBUS_CTRL_3A                                         0x29DA
#define P29_DB_CBUS_CTRL_3B                                         0x29DB
#define P29_DC_CBUS_CTRL_3C                                         0x29DC
#define P29_DD_CBUS_CTRL_3D                                         0x29DD
#define P29_DE_CBUS_CTRL_3E                                         0x29DE
#define P29_DF_CBUS_CTRL_3F                                         0x29DF
#define P29_E0_CBUS_CTRL_40                                         0x29E0
#define P29_E1_CBUS_CTRL_41                                         0x29E1
#define P29_E2_CBUS_CTRL_42                                         0x29E2
#define P29_E3_CBUS_CTRL_43                                         0x29E3
#define P29_E4_CBUS_CTRL_44                                         0x29E4
#define P29_E5_CBUS_CTRL_45                                         0x29E5
#define P29_E6_CBUS_CTRL_46                                         0x29E6
#define P29_E7_CBUS_CTRL_47                                         0x29E7
#define P29_E8_CBUS_CTRL_48                                         0x29E8
#define P29_E9_CBUS_CTRL_49                                         0x29E9
#define P29_EA_CBUS_CTRL_4A                                         0x29EA
#define P29_EB_CBUS_CTRL_4B                                         0x29EB
#define P29_EC_CBUS_CTRL_4C                                         0x29EC
#define P29_ED_CBUS_CTRL_4D                                         0x29ED
#define P29_EE_CBUS_CTRL_4E                                         0x29EE
#define P29_EF_CBUS_CTRL_4F                                         0x29EF
#define P29_F0_CBUS_CTRL_50                                         0x29F0
#define P29_F1_CBUS_CTRL_51                                         0x29F1
#define P29_F2_CBUS_CTRL_52                                         0x29F2
#define P29_F3_CBUS_CTRL_53                                         0x29F3
#define P29_F4_CBUS_CTRL_54                                         0x29F4
#define P29_F5_CBUS_CTRL_55                                         0x29F5
#define P29_F6_CBUS_CTRL_56                                         0x29F6
#define P29_F7_CBUS_CTRL_57                                         0x29F7
#define P29_F8_CBUS_CTRL_58                                         0x29F8
#define P29_F9_CBUS_CTRL_59                                         0x29F9
#define P29_FA_CBUS_CTRL_5A                                         0x29FA
#define P29_FB_CBUS_CTRL_5B                                         0x29FB
#define P29_FC_CBUS_CTRL_5C                                         0x29FC
#define P29_FD_CBUS_CTRL_5D                                         0x29FD


//--------------------------------------------------
// ECBUS MAC (Page 2B)
//--------------------------------------------------
#define P2B_00_ECBUS_STARTUP_CTRL                                   0x2B00
#define P2B_01_ECBUS_STARTUP_CONFIG                                 0x2B01
#define P2B_02_ECBUS_STARTUP_DET                                    0x2B02
#define P2B_03_ECBUS_STARTUP_RESERVE                                0x2B03
#define P2B_04_ECBUS_TDM_SYNC_CTRL                                  0x2B04
#define P2B_05_ECBUS_TDM_SYNC_CONFIG_1                              0x2B05
#define P2B_06_ECBUS_TDM_SYNC_CONFIG_2                              0x2B06
#define P2B_07_ECBUS_TDM_SYNC_DET_1                                 0x2B07
#define P2B_08_ECBUS_TDM_SYNC_DET_2                                 0x2B08
#define P2B_09_ECBUS_TDM_SYNC_TX_OFFSET                             0x2B09
#define P2B_0A_ECBUS_TDM_SYNC_RX_OFFSET                             0x2B0A
#define P2B_0B_ECBUS_TDM_SYNC_RESERVE                               0x2B0B
#define P2B_0C_ECBUS_EMSC_SYNC_CTRL                                 0x2B0C
#define P2B_0D_ECBUS_EMSC_SYNC_CONFIG_1                             0x2B0D
#define P2B_0E_ECBUS_EMSC_SYNC_CONFIG_2                             0x2B0E
#define P2B_0F_ECBUS_EMSC_SYNC_DET                                  0x2B0F
#define P2B_10_ECBUS_EMSC_SLOT_MAP_1                                0x2B10
#define P2B_11_ECBUS_EMSC_SLOT_MAP_2                                0x2B11
#define P2B_12_ECBUS_EMSC_SLOT_MAP_3                                0x2B12
#define P2B_13_ECBUS_EMSC_SOURCE_SLOT_DET_1                         0x2B13
#define P2B_14_ECBUS_EMSC_SOURCE_SLOT_DET_2                         0x2B14
#define P2B_15_ECBUS_EMSC_SOURCE_SLOT_DET_3                         0x2B15
#define P2B_16_ECBUS_EMSC_SYNC_RESERVE                              0x2B16
#define P2B_17_ECBUS_EMSC_RX_ADDR                                   0x2B17
#define P2B_18_ECBUS_EMSC_RX_DATA                                   0x2B18
#define P2B_19_ECBUS_EMSC_TX_ADDR                                   0x2B19
#define P2B_1A_ECBUS_EMSC_TX_DATA                                   0x2B1A
#define P2B_1B_ECBUS_EMSC_TX_RD_ADDR                                0x2B1B
#define P2B_1C_ECBUS_EMSC_TX_RD_DATA                                0x2B1C
#define P2B_1D_ECBUS_EMSC_TRANS_CTRL                                0x2B1D
#define P2B_1E_ECBUS_EMSC_RX_BLK_CNT                                0x2B1E
#define P2B_1F_ECBUS_EMSC_RX_WRT_PNT                                0x2B1F
#define P2B_20_ECBUS_EMSC_TX_WRT_PNT                                0x2B20
#define P2B_21_ECBUS_EMSC_RX_REQ_CNT                                0x2B21
#define P2B_22_ECBUS_EMSC_TX_REQ_CNT                                0x2B22
#define P2B_23_ECBUS_EMSC_TRANS_CONFIG_1                            0x2B23
#define P2B_24_ECBUS_EMSC_TRANS_CONFIG_2                            0x2B24
#define P2B_25_ECBUS_EMSC_TRANS_DET_1                               0x2B25
#define P2B_26_ECBUS_EMSC_TRANS_DET_2                               0x2B26
#define P2B_27_ECBUS_EMSC_TRANS_DET_3                               0x2B27
#define P2B_28_ECBUS_EMSC_TRANS_DET_4                               0x2B28
#define P2B_29_ECBUS_EMSC_TX_ERR_CODE                               0x2B29
#define P2B_2A_ECBUS_EMSC_TRANS_RESERVE                             0x2B2A
#define P2B_2B_ECBUS_EMSC_RX_CRC_1                                  0x2B2B
#define P2B_2C_ECBUS_EMSC_RX_CRC_2                                  0x2B2C
#define P2B_2D_ECBUS_EMSC_RX_CRC_3                                  0x2B2D
#define P2B_2E_ECBUS_EMSC_RX_CRC_4                                  0x2B2E
#define P2B_2F_ECBUS_EMSC_TX_CRC_1                                  0x2B2F
#define P2B_30_ECBUS_EMSC_TX_CRC_2                                  0x2B30
#define P2B_31_ECBUS_EMSC_TX_CRC_3                                  0x2B31
#define P2B_32_ECBUS_EMSC_TX_CRC_4                                  0x2B32
#define P2B_33_ECBUS_EMSC_CRC_RESERVE                               0x2B33
#define P2B_34_ECBUS_BIST_CTRL                                      0x2B34
#define P2B_35_ECBUS_BIST_CONFIG                                    0x2B35
#define P2B_36_ECBUS_BIST_FIXED8                                    0x2B36
#define P2B_37_ECBUS_BIST_RX_INIT                                   0x2B37
#define P2B_38_ECBUS_BIST_TX_INIT                                   0x2B38
#define P2B_39_ECBUS_BIST_ERR_CNT_H                                 0x2B39
#define P2B_3A_ECBUS_BIST_ERR_CNT_L                                 0x2B3A
#define P2B_3B_ECBUS_BIST_RESERVE                                   0x2B3B
#define P2B_3C_ECBUS_SRAM_BIST                                      0x2B3C
#define P2B_3D_ECBUS_SRAM_DRF_BIST                                  0x2B3D
#define P2B_3E_ECBUS_GLOBAL_CTRL                                    0x2B3E
#define P2B_3F_CBUS1_FW_CRC_B0_H                                    0x2B3F
#define P2B_40_CBUS1_FW_CRC_B0_L                                    0x2B40
#define P2B_41_CBUS1_FW_CRC_B1_H                                    0x2B41
#define P2B_42_CBUS1_FW_CRC_B1_L                                    0x2B42
#define P2B_43_CBUS1_FW_CRC_B2_H                                    0x2B43
#define P2B_44_CBUS1_FW_CRC_B2_L                                    0x2B44
#define P2B_45_CBUS1_FW_CRC_B3_H                                    0x2B45
#define P2B_46_CBUS1_FW_CRC_B3_L                                    0x2B46
#define P2B_47_CBUS1_FW_CRC_B4_H                                    0x2B47
#define P2B_48_CBUS1_FW_CRC_B4_L                                    0x2B48
#define P2B_49_ECBUS_TIMEOUT_CLK1                                   0x2B49
#define P2B_4A_ECBUS_TIMEOUT_CLK2                                   0x2B4A
#define P2B_4B_ECBUS_TIMEOUT_RESERVE                                0x2B4B
#define P2B_4C_ECBUS_HW_FSM_1                                       0x2B4C
#define P2B_4D_ECBUS_HW_FSM_2                                       0x2B4D
#define P2B_4E_ECBUS_HW_FSM_3                                       0x2B4E
#define P2B_4F_ECBUS_HW_FSM_4                                       0x2B4F
#define P2B_50_ECBUS_HW_FSM_5                                       0x2B50
#define P2B_51_ECBUS_HW_FSM_6                                       0x2B51
#define P2B_52_ECBUS_TEST_FORCE_OUT                                 0x2B52


//--------------------------------------------------
// ECBUS D-PHY (Page 2B)
//--------------------------------------------------
#define P2B_A0_ECBUS_DPHY_CTRL                                      0x2BA0
#define P2B_A1_ECBUS_DPHY_EDGE_CTRL                                 0x2BA1
#define P2B_A2_ECBUS_DPHY_EDGE_RESULT                               0x2BA2
#define P2B_A3_ECBUS_DPHY_STAT_CTRL                                 0x2BA3
#define P2B_A4_ECBUS_DPHY_STAT_CONFIG_1                             0x2BA4
#define P2B_A5_ECBUS_DPHY_STAT_CONFIG_2                             0x2BA5
#define P2B_A6_ECBUS_DPHY_STAT_RESULT_1                             0x2BA6
#define P2B_A7_ECBUS_DPHY_STAT_RESULT_2                             0x2BA7
#define P2B_A8_ECBUS_DPHY_STAT_RESULT_3                             0x2BA8
#define P2B_A9_ECBUS_DPHY_CALIB_CTRL                                0x2BA9
#define P2B_AA_ECBUS_DPHY_INI_CONFIG_1                              0x2BAA
#define P2B_AB_ECBUS_DPHY_INI_CONFIG_2                              0x2BAB
#define P2B_AC_ECBUS_DPHY_INI_CONFIG_3                              0x2BAC
#define P2B_AD_ECBUS_DPHY_INI_CONFIG_4                              0x2BAD
#define P2B_AE_ECBUS_DPHY_INI_CONFIG_5                              0x2BAE
#define P2B_AF_ECBUS_DPHY_INI_RESULT_1                              0x2BAF
#define P2B_B0_ECBUS_DPHY_INI_RESULT_2                              0x2BB0
#define P2B_B1_ECBUS_DPHY_INI_RESULT_3                              0x2BB1
#define P2B_B2_ECBUS_DPHY_INI_RESULT_4                              0x2BB2
#define P2B_B3_ECBUS_DPHY_TX_PHASE_CONFIG_1                         0x2BB3
#define P2B_B4_ECBUS_DPHY_TX_PHASE_CONFIG_2                         0x2BB4
#define P2B_B5_ECBUS_DPHY_TX_PHASE_CONFIG_3                         0x2BB5
#define P2B_B6_ECBUS_DPHY_TX_PHASE_CONFIG_4                         0x2BB6
#define P2B_B7_ECBUS_DPHY_TX_PHASE_RESULT                           0x2BB7
#define P2B_B8_ECBUS_DPHY_ADAPT_CTRL                                0x2BB8
#define P2B_B9_ECBUS_DPHY_ADAPT_CONFIG_1                            0x2BB9
#define P2B_BA_ECBUS_DPHY_ADAPT_CONFIG_2                            0x2BBA
#define P2B_BB_ECBUS_DPHY_ADAPT_CONFIG_3                            0x2BBB
#define P2B_BC_ECBUS_DPHY_ADAPT_RESULT_1                            0x2BBC
#define P2B_BD_ECBUS_DPHY_ADAPT_RESULT_2                            0x2BBD
#define P2B_BE_ECBUS_DPHY_ADAPT_RESULT_3                            0x2BBE
#define P2B_BF_ECBUS_DPHY_CALIB_RESULT                              0x2BBF
#define P2B_C0_ECBUS_DPHY_CONFIG                                    0x2BC0
#define P2B_C1_ECBUS_DPHY_PATTERN_1                                 0x2BC1
#define P2B_C2_ECBUS_DPHY_PATTERN_2                                 0x2BC2
#define P2B_C3_ECBUS_DPHY_FLAG                                      0x2BC3
#define P2B_C4_ECBUS_DPHY_IRQ                                       0x2BC4
#define P2B_C5_ECBUS_DPHY_DEBUG                                     0x2BC5
#define P2B_C6_ECBUS_DPHY_RESERVE                                   0x2BC6
#define P2B_C9_ECBUS_DPHY_CAP0                                      0x2BC9
#define P2B_CA_ECBUS_DPHY_CAP1                                      0x2BCA


//--------------------------------------------------
// Gamma Control (Page 2F)
//--------------------------------------------------
#define P2F_00_GAMMA_DUMMY                                          0x2F00
#define P2F_01_GAMMA_BIST_CTRL0_M1                                  0x2F01
#define P2F_02_GAMMA_BIST_CTRL1_M1                                  0x2F02
#define P2F_03_GAMMA_BIST_CTRL2_M1                                  0x2F03


//--------------------------------------------------
// Off-line Measure Block Overview (Page 30)
//--------------------------------------------------
#define P30_00_SYNC_SELECT                                          0x3000
#define P30_01_MEAS_CTL0                                            0x3001
#define P30_02_MEAS_CTL1                                            0x3002
#define P30_03_MEAS_ERROR_FLG0                                      0x3003
#define P30_04_MEAS_ERROR_FLG1                                      0x3004
#define P30_05_MEAS_HS_PERIOD_A_M                                   0x3005
#define P30_06_MEAS_HS_PERIOD_A_L                                   0x3006
#define P30_07_MEAS_HS_PERIOD_FRA_A                                 0x3007
#define P30_08_MEAS_VS_PERIOD_A_M                                   0x3008
#define P30_09_MEAS_VS_PERIOD_A_L                                   0x3009
#define P30_0A_MEAS_HS_PULSE_A_M                                    0x300A
#define P30_0B_MEAS_HS_PULSE_A_L                                    0x300B
#define P30_0C_MEAS_VS_PULSE_A_M                                    0x300C
#define P30_0D_MEAS_VS_PULSE_A_L                                    0x300D
#define P30_0E_MEAS_HS_PERIOD_D_M                                   0x300E
#define P30_0F_MEAS_HS_PERIOD_D_L                                   0x300F
#define P30_10_MEAS_HS_PERIOD_FRA_D                                 0x3010
#define P30_11_MEAS_VS_PERIOD_D_M                                   0x3011
#define P30_12_MEAS_VS_PERIOD_D_L                                   0x3012
#define P30_13_MEAS_HS_PULSE_D_M                                    0x3013
#define P30_14_MEAS_HS_PULSE_D_L                                    0x3014
#define P30_15_MEAS_HS_VS_DELTA_CTL                                 0x3015
#define P30_16_MEAS_HS_VS_DELTA_IRQ                                 0x3016
#define P30_1A_MEAS2_HS_VS_DLY                                      0x301A
#define P30_1B_MEAS_FIELD_TOGGLE                                    0x301B
#define P30_1C_MEASURE_DUMMY0                                       0x301C
#define P30_1D_MEASURE_DUMMY1                                       0x301D


//--------------------------------------------------
// Active Measure Block Overview (Page 30)
//--------------------------------------------------
#define P30_40_I_ACT_MEAS_CTRL                                      0x3040
#define P30_41_I_ACT_MEAS_ERROR_FLG                                 0x3041
#define P30_42_I_ACT_MEAS_RESULT_H                                  0x3042
#define P30_43_I_ACT_MEAS_RESULT_M                                  0x3043
#define P30_44_I_ACT_MEAS_RESULT_L                                  0x3044
#define P30_45_D_ACT_MEAS_CTRL                                      0x3045
#define P30_46_D_ACT_MEAS_ERROR_FLG                                 0x3046
#define P30_47_D_ACT_MEAS_RESULT_H                                  0x3047
#define P30_48_D_ACT_MEAS_RESULT_M                                  0x3048
#define P30_49_D_ACT_MEAS_RESULT_L                                  0x3049


//--------------------------------------------------
// VGATOP Input Video Capture (Page 30)
//--------------------------------------------------
#define P30_A0_VGATOP_VGIP_CTRL                                     0x30A0
#define P30_A1_VGATOP_VGIP_SIGINV                                   0x30A1
#define P30_A2_VGATOP_VGIP_DELAY_CTRL                               0x30A2
#define P30_A3_VGATOP_VGIP_ODD_CTRL                                 0x30A3


//--------------------------------------------------
// VGATOP Input Frame Window (Page 30)
//--------------------------------------------------
#define P30_A4_VGATOP_IPH_ACT_STA_H                                 0x30A4
#define P30_A5_VGATOP_IPH_ACT_STA_L                                 0x30A5
#define P30_A6_VGATOP_IPH_ACT_WID_H                                 0x30A6
#define P30_A7_VGATOP_IPH_ACT_WID_L                                 0x30A7
#define P30_A8_VGATOP_IPV_ACT_STA_H                                 0x30A8
#define P30_A9_VGATOP_IPV_ACT_STA_L                                 0x30A9
#define P30_AA_VGATOP_IPV_ACT_LEN_H                                 0x30AA
#define P30_AB_VGATOP_IPV_ACT_LEN_L                                 0x30AB
#define P30_AC_VGATOP_IVS_DELAY                                     0x30AC
#define P30_AD_VGATOP_IHS_DELAY                                     0x30AD
#define P30_AE_VGATOP_VGIP_HV_DELAY                                 0x30AE
#define P30_AF_VGATOP_V8_SOURCE_SELECT                              0x30AF
#define P30_B0_VGATOP_V8CLK_SEL                                     0x30B0


//--------------------------------------------------
// VGATOP Image Auto Function (Page 30)
//--------------------------------------------------
#define P30_C0_VGATOP_H_BOUNDARY_H                                  0x30C0
#define P30_C1_VGATOP_H_BOUNDARY_STA_L                              0x30C1
#define P30_C2_VGATOP_H_BOUNDARY_END_L                              0x30C2
#define P30_C3_VGATOP_V_BOUNDARY_H                                  0x30C3
#define P30_C4_VGATOP_V_BOUNDARY_STA_L                              0x30C4
#define P30_C5_VGATOP_V_BOUNDARY_END_L                              0x30C5
#define P30_C6_VGATOP_RED_NOISE_MARGIN                              0x30C6
#define P30_C7_VGATOP_GRN_NOISE_MARGIN                              0x30C7
#define P30_C8_VGATOP_BLU_NOISE_MARGIN                              0x30C8
#define P30_C9_VGATOP_DIFF_THRESHOLD                                0x30C9
#define P30_CA_VGATOP_AUTO_ADJ_CTRL0                                0x30CA
#define P30_CB_VGATOP_HW_AUTO_PHASE_CTRL0                           0x30CB
#define P30_CC_VGATOP_HW_AUTO_PHASE_CTRL1                           0x30CC
#define P30_CD_VGATOP_AUTO_ADJ_CTRL1                                0x30CD
#define P30_CE_VGATOP_VER_START_END_H                               0x30CE
#define P30_CF_VGATOP_VER_START_L                                   0x30CF
#define P30_D0_VGATOP_VER_END_L                                     0x30D0
#define P30_D1_VGATOP_H_START_END_H                                 0x30D1
#define P30_D2_VGATOP_H_START_L                                     0x30D2
#define P30_D3_VGATOP_H_END_L                                       0x30D3
#define P30_D4_VGATOP_AUTO_PHASE_3                                  0x30D4
#define P30_D5_VGATOP_AUTO_PHASE_2                                  0x30D5
#define P30_D6_VGATOP_AUTO_PHASE_1                                  0x30D6
#define P30_D7_VGATOP_AUTO_PHASE_0                                  0x30D7
#define P30_DA_VGATOP_HS_EDGE_CHANGE_ST                             0x30DA
#define P30_DB_VGATOP_HS_EDGE_CHANGE_END                            0x30DB
#define P30_DC_VGATOP_HS_EDGE_CHANGE_CTRL                           0x30DC


//--------------------------------------------------
// VGATOP Input Pattern Generator (Page 30)
//--------------------------------------------------
#define P30_DD_VGATOP_PAT_GEN_CTRL0                                 0x30DD
#define P30_DE_VGATOP_PAT_GEN_CTRL1                                 0x30DE
#define P30_DF_VGATOP_PAT_GEN_RED_INI_L                             0x30DF
#define P30_E0_VGATOP_PAT_GEN_GRN_INI_L                             0x30E0
#define P30_E1_VGATOP_PAT_GEN_BLU_INI_L                             0x30E1
#define P30_E2_VGATOP_PAT_GEN_INI_H                                 0x30E2
#define P30_E3_VGA_PATTERN_RESET                                    0x30E3


//--------------------------------------------------
// VGATOP Flag (Page 30)
//--------------------------------------------------
#define P30_E4_VGATOP_IRQ_CTRL                                      0x30E4
#define P30_E5_VGATOP_DUMMY                                         0x30E5


//--------------------------------------------------
// YUV422 to YUV444 Conversion (Page 31)
//--------------------------------------------------
#define P31_40_YUV422_TO_444_PATH0                                  0x3140


//--------------------------------------------------
// DB Mechanism (Page 31)
//--------------------------------------------------
#define P31_C0_I_DB_CTRL                                            0x31C0
#define P31_C1_D_DB_CTRL                                            0x31C1
#define P31_C2_IMD_DB_STATUS                                        0x31C2


//--------------------------------------------------
// ADC Noise Reduction (Page 33)
//--------------------------------------------------
#define P33_00_ADCNR_CTRL1                                          0x3300
#define P33_01_ADCNR_CTRL2                                          0x3301
#define P33_02_ADCNR_CTRL3                                          0x3302
#define P33_03_ADCNR_HOR_START_H                                    0x3303
#define P33_04_ADCNR_HOR_START_L                                    0x3304
#define P33_05_ADCNR_VER_START_H                                    0x3305
#define P33_06_ADCNR_VER_START_L                                    0x3306
#define P33_07_ADCNR_HOR_END_H                                      0x3307
#define P33_08_ADCNR_HOR_END_L                                      0x3308
#define P33_09_ADCNR_VER_END_H                                      0x3309
#define P33_0A_ADCNR_VER_END_L                                      0x330A
#define P33_0B_ADCNR_GRAY256_DETECT                                 0x330B
#define P33_0C_ADCNR_GRAY256_THD                                    0x330C
#define P33_0D_ADCNR_CONST                                          0x330D
#define P33_0E_ADCNR_MODIFY                                         0x330E
#define P33_0F_ADCNR_ALONE_TONE_CTL                                 0x330F
#define P33_10_ADCNR_CONTINUED_TONE                                 0x3310
#define P33_11_ADCNR_PATTERN_CHANGE_DET1                            0x3311
#define P33_12_ADCNR_PATTERN_CHANGE_DET2                            0x3312
#define P33_13_ADCNR_PATTERN_CHANGE_DET3                            0x3313
#define P33_14_ADCNR_PATTERN_CHANGE_DET4                            0x3314
#define P33_15_ADCNR_REPLACE_FLAG                                   0x3315
#define P33_16_ADCNR_DEBUG_MODE_CTRL1                               0x3316
#define P33_17_ADCNR_DEBUG_MODE_CTRL2                               0x3317
#define P33_18_ADCNR_TOTAL_COUNT1                                   0x3318
#define P33_19_ADCNR_TOTAL_COUNT2                                   0x3319
#define P33_1A_ADCNR_TOTAL_COUNT3                                   0x331A
#define P33_1B_ADCNR_SINGLE_COUNT1                                  0x331B
#define P33_1C_ADCNR_SINGLE_COUNT2                                  0x331C
#define P33_1D_ADCNR_SINGLE_COUNT3                                  0x331D
#define P33_1E_ADCNR_TONE_COUNT                                     0x331E
#define P33_1F_ADCNR_READ_DATA_CTRL1                                0x331F
#define P33_20_ADCNR_READ_DATA_CTRL2                                0x3320
#define P33_21_ADCNR_CODE_COUNT_RESULT1                             0x3321
#define P33_22_ADCNR_CODE_COUNT_RESULT2                             0x3322
#define P33_23_ADCNR_CODE_COUNT_RESULT3                             0x3323
#define P33_24_ADCNR_TABLE_RESULT                                   0x3324
#define P33_25_ADCNR_DUMMY1                                         0x3325
#define P33_2A_BIST_CTRL                                            0x332A
#define P33_2B_BIST_RESULT                                          0x332B


//--------------------------------------------------
// Cyclic-Redundant-Check(Page 36)
//--------------------------------------------------
#define P36_00_I_CRC_CTRL                                           0x3600
#define P36_01_I_MAIN1_CRC_1                                        0x3601
#define P36_02_I_MAIN1_CRC_2                                        0x3602
#define P36_03_I_MAIN1_CRC_3                                        0x3603
#define P36_04_I_MAIN1_CRC_4                                        0x3604
#define P36_05_I_MAIN1_CRC_5                                        0x3605
#define P36_06_I_MAIN1_CRC_6                                        0x3606
#define P36_2C_D_CRC_CTRL                                           0x362C
#define P36_2D_D_MAIN1_CRC_1                                        0x362D
#define P36_2E_D_MAIN1_CRC_2                                        0x362E
#define P36_2F_D_MAIN1_CRC_3                                        0x362F
#define P36_30_D_MAIN1_CRC_4                                        0x3630
#define P36_31_D_MAIN1_CRC_5                                        0x3631
#define P36_32_D_MAIN1_CRC_6                                        0x3632
#define P36_40_M_CRC_CTRL                                           0x3640
#define P36_41_M_M1_CRC_1                                           0x3641
#define P36_42_M_M1_CRC_2                                           0x3642
#define P36_43_M_M1_CRC_3                                           0x3643
#define P36_44_M_M1_CRC_4                                           0x3644
#define P36_45_M_M1_CRC_5                                           0x3645
#define P36_46_M_M1_CRC_6                                           0x3646


//--------------------------------------------------
// Control for LVDS display convertion (Page 39)
//--------------------------------------------------
#define P39_00_LVDS_DISP_TYPE                                       0x3900
#define P39_01_LVDS_DISPLAY_CONV_CTRL0                              0x3901
#define P39_02_LVDS_DISPLAY_CONV_CTRL1                              0x3902
#define P39_03_LVDS_DISPLAY_CONV_CTRL2                              0x3903
#define P39_04_LVDS_DISPLAY_CONV_CTRL3                              0x3904
#define P39_05_LVDS_DISPLAY_CONV_CTRL4                              0x3905
#define P39_06_LVDS_DISPLAY_CONV_CTRL5                              0x3906
#define P39_07_LVDS_DISPLAY_CONV_CTRL6                              0x3907
#define P39_08_LVDS_PORCH_RED_CTRL0                                 0x3908
#define P39_09_LVDS_PORCH_RED_CTRL1                                 0x3909
#define P39_0A_LVDS_PORCH_GREEN_CTRL0                               0x390A
#define P39_0B_LVDS_PORCH_GREEN_CTRL1                               0x390B
#define P39_0C_LVDS_PORCH_BLUE_CTRL0                                0x390C
#define P39_0D_LVDS_PORCH_BLUE_CTRL1                                0x390D
#define P39_0E_LVDS_PORTA_DATA_BIT_CTRL                             0x390E
#define P39_0F_LVDS_PORTB_DATA_BIT_CTRL                             0x390F
#define P39_10_LVDS_PORTC_DATA_BIT_CTRL                             0x3910
#define P39_11_LVDS_PORTD_DATA_BIT_CTRL                             0x3911
#define P39_12_LVDS_PORTE_DATA_BIT_CTRL                             0x3912
#define P39_13_LVDS_PORTF_DATA_BIT_CTRL                             0x3913
#define P39_14_LVDS_PORTG_DATA_BIT_CTRL                             0x3914
#define P39_15_LVDS_PORTH_DATA_BIT_CTRL                             0x3915
#define P39_16_LVDS_LR_CTRL                                         0x3916
#define P39_17_LVDS_RSV0_CTRL0                                      0x3917
#define P39_18_LVDS_RSV0_CTRL1                                      0x3918
#define P39_19_LVDS_RSV1_CTRL0                                      0x3919
#define P39_1A_LVDS_RSV1_CTRL1                                      0x391A
#define P39_1B_LVDS_RSV1_CTRL2                                      0x391B
#define P39_1C_LVDS_RSV1_CTRL3                                      0x391C
#define P39_1D_LVDS_CLK_CTRL                                        0x391D
#define P39_20_LVDS_TEST_MODE                                       0x3920
#define P39_21_LVDS_BIST_CTRL                                       0x3921
#define P39_22_LVDS_DRF_BIST_CTRL0                                  0x3922
#define P39_23_LVDS_DRF_BIST_CTRL1                                  0x3923
#define P39_30_D_CONV_CRC_CTRL                                      0x3930
#define P39_31_D_CONV_CRC_0_H                                       0x3931
#define P39_32_D_CONV_CRC_0_L                                       0x3932
#define P39_33_D_CONV_CRC_1_H                                       0x3933
#define P39_34_D_CONV_CRC_1_L                                       0x3934
#define P39_35_D_CONV_CRC_2_H                                       0x3935
#define P39_36_D_CONV_CRC_2_L                                       0x3936
#define P39_37_D_CONV_CRC_3_H                                       0x3937
#define P39_38_D_CONV_CRC_3_L                                       0x3938
#define P39_39_D_CONV_CRC_4_H                                       0x3939
#define P39_3A_D_CONV_CRC_4_L                                       0x393A
#define P39_3B_D_CONV_CRC_5_H                                       0x393B
#define P39_3C_D_CONV_CRC_5_L                                       0x393C
#define P39_3D_D_CONV_CRC_6_H                                       0x393D
#define P39_3E_D_CONV_CRC_6_L                                       0x393E
#define P39_3F_D_CONV_CRC_7_H                                       0x393F
#define P39_40_D_CONV_CRC_7_L                                       0x3940
#define P39_41_D_CONV_CRC_8_H                                       0x3941
#define P39_42_D_CONV_CRC_8_L                                       0x3942
#define P39_43_D_CONV_CRC_9_H                                       0x3943
#define P39_44_D_CONV_CRC_9_L                                       0x3944
#define P39_45_D_CONV_CRC_10_H                                      0x3945
#define P39_46_D_CONV_CRC_10_L                                      0x3946
#define P39_47_D_CONV_CRC_11_H                                      0x3947
#define P39_48_D_CONV_CRC_11_L                                      0x3948


//--------------------------------------------------
// OSD Frame Control Registers (Page 3A)
//--------------------------------------------------
#define P3A_00_FRAME_CTRL_00                                        0x3A00
#define P3A_01_FRAME_CTRL_01                                        0x3A01
#define P3A_02_FRAME_CTRL_02                                        0x3A02
#define P3A_03_FRAME_CTRL_03                                        0x3A03
#define P3A_04_FRAME_CTRL_04                                        0x3A04
#define P3A_05_FRAME_CTRL_05                                        0x3A05
#define P3A_06_FRAME_CTRL_06                                        0x3A06
#define P3A_07_FRAME_CTRL_07                                        0x3A07
#define P3A_08_FRAME_CTRL_08                                        0x3A08
#define P3A_09_FRAME_CTRL_09                                        0x3A09
#define P3A_0A_FRAME_CTRL_0A                                        0x3A0A
#define P3A_0B_FRAME_CTRL_0B                                        0x3A0B
#define P3A_0C_FRAME_CTRL_0C                                        0x3A0C
#define P3A_0D_FRAME_CTRL_0D                                        0x3A0D
#define P3A_0E_FRAME_CTRL_0E                                        0x3A0E
#define P3A_0F_FRAME_CTRL_0F                                        0x3A0F
#define P3A_10_FRAME_CTRL_10                                        0x3A10
#define P3A_11_FRAME_CTRL_11                                        0x3A11
#define P3A_12_FRAME_CTRL_12                                        0x3A12
#define P3A_13_FRAME_CTRL_13                                        0x3A13
#define P3A_14_FRAME_CTRL_14                                        0x3A14
#define P3A_15_FRAME_CTRL_15                                        0x3A15
#define P3A_16_FRAME_CTRL_16                                        0x3A16
#define P3A_17_FRAME_CTRL_17                                        0x3A17
#define P3A_18_FRAME_CTRL_18                                        0x3A18
#define P3A_19_FRAME_CTRL_19                                        0x3A19
#define P3A_1A_FRAME_CTRL_1A                                        0x3A1A
#define P3A_1B_FRAME_CTRL_1B                                        0x3A1B
#define P3A_1C_FRAME_CTRL_1C                                        0x3A1C
#define P3A_1D_FRAME_CTRL_1D                                        0x3A1D
#define P3A_1E_FRAME_CTRL_1E                                        0x3A1E
#define P3A_1F_FRAME_CTRL_1F                                        0x3A1F
#define P3A_20_FRAME_CTRL_20                                        0x3A20
#define P3A_21_FRAME_CTRL_21                                        0x3A21
#define P3A_22_FRAME_CTRL_22                                        0x3A22
#define P3A_23_FRAME_CTRL_23                                        0x3A23
#define P3A_24_FRAME_CTRL_24                                        0x3A24
#define P3A_25_FRAME_CTRL_25                                        0x3A25
#define P3A_26_FRAME_CTRL_26                                        0x3A26
#define P3A_27_FRAME_CTRL_27                                        0x3A27
#define P3A_28_FRAME_CTRL_28                                        0x3A28
#define P3A_29_FRAME_CTRL_29                                        0x3A29
#define P3A_2A_FRAME_CTRL_2A                                        0x3A2A
#define P3A_2B_FRAME_CTRL_2B                                        0x3A2B
#define P3A_2C_FRAME_CTRL_2C                                        0x3A2C
#define P3A_2D_FRAME_CTRL_2D                                        0x3A2D
#define P3A_2E_FRAME_CTRL_2E                                        0x3A2E
#define P3A_2F_FRAME_CTRL_2F                                        0x3A2F
#define P3A_30_FRAME_CTRL_30                                        0x3A30
#define P3A_31_FRAME_CTRL_31                                        0x3A31
#define P3A_32_FRAME_CTRL_32                                        0x3A32
#define P3A_33_FRAME_CTRL_33                                        0x3A33
#define P3A_34_FRAME_CTRL_34                                        0x3A34
#define P3A_35_FRAME_CTRL_35                                        0x3A35
#define P3A_36_FRAME_CTRL_36                                        0x3A36
#define P3A_37_FRAME_CTRL_37                                        0x3A37
#define P3A_38_FRAME_CTRL_38                                        0x3A38
#define P3A_39_FRAME_CTRL_39                                        0x3A39
#define P3A_3A_FRAME_CTRL_3A                                        0x3A3A
#define P3A_3B_FRAME_CTRL_3B                                        0x3A3B
#define P3A_3C_FRAME_CTRL_3C                                        0x3A3C
#define P3A_3D_FRAME_CTRL_3D                                        0x3A3D
#define P3A_3E_FRAME_CTRL_3E                                        0x3A3E
#define P3A_3F_FRAME_CTRL_3F                                        0x3A3F
#define P3A_40_FRAME_CTRL_40                                        0x3A40
#define P3A_41_FRAME_CTRL_41                                        0x3A41
#define P3A_42_FRAME_CTRL_42                                        0x3A42
#define P3A_43_FRAME_CTRL_43                                        0x3A43
#define P3A_44_FRAME_CTRL_44                                        0x3A44
#define P3A_45_FRAME_CTRL_45                                        0x3A45
#define P3A_46_FRAME_CTRL_46                                        0x3A46
#define P3A_47_FRAME_CTRL_47                                        0x3A47
#define P3A_48_FRAME_CTRL_48                                        0x3A48
#define P3A_49_FRAME_CTRL_49                                        0x3A49
#define P3A_4A_FRAME_CTRL_4A                                        0x3A4A
#define P3A_4B_FRAME_CTRL_4B                                        0x3A4B
#define P3A_4C_FRAME_CTRL_4C                                        0x3A4C
#define P3A_4D_FRAME_CTRL_4D                                        0x3A4D
#define P3A_4E_FRAME_CTRL_4E                                        0x3A4E
#define P3A_4F_FRAME_CTRL_4F                                        0x3A4F
#define P3A_50_FRAME_CTRL_50                                        0x3A50
#define P3A_51_FRAME_CTRL_51                                        0x3A51
#define P3A_52_FRAME_CTRL_52                                        0x3A52
#define P3A_53_FRAME_CTRL_53                                        0x3A53
#define P3A_54_FRAME_CTRL_54                                        0x3A54
#define P3A_55_FRAME_CTRL_55                                        0x3A55
#define P3A_56_FRAME_CTRL_56                                        0x3A56
#define P3A_57_FRAME_CTRL_57                                        0x3A57
#define P3A_58_FRAME_CTRL_58                                        0x3A58
#define P3A_59_FRAME_CTRL_59                                        0x3A59
#define P3A_5A_FRAME_CTRL_5A                                        0x3A5A
#define P3A_5B_FRAME_CTRL_5B_DUMMY                                  0x3A5B
#define P3A_5C_FRAME_CTRL_5C_DUMMY                                  0x3A5C
#define P3A_60_FRAME_CTRL_60                                        0x3A60
#define P3A_61_FRAME_CTRL_61                                        0x3A61
#define P3A_62_FRAME_CTRL_62                                        0x3A62
#define P3A_63_FRAME_CTRL_63                                        0x3A63
#define P3A_64_FRAME_CTRL_64                                        0x3A64
#define P3A_65_FRAME_CTRL_65                                        0x3A65
#define P3A_66_FRAME_CTRL_66                                        0x3A66
#define P3A_67_FRAME_CTRL_67                                        0x3A67
#define P3A_68_FRAME_CTRL_68                                        0x3A68
#define P3A_69_FRAME_CTRL_69                                        0x3A69
#define P3A_6A_FRAME_CTRL_6A                                        0x3A6A
#define P3A_6B_FRAME_CTRL_6B                                        0x3A6B
#define P3A_6C_FRAME_CTRL_6C                                        0x3A6C
#define P3A_6D_FRAME_CTRL_6D                                        0x3A6D
#define P3A_6E_FRAME_CTRL_6E                                        0x3A6E
#define P3A_6F_FRAME_CTRL_6F                                        0x3A6F
#define P3A_70_FRAME_CTRL_70                                        0x3A70
#define P3A_71_FRAME_CTRL_71                                        0x3A71
#define P3A_72_FRAME_CTRL_72                                        0x3A72
#define P3A_73_FRAME_CTRL_73                                        0x3A73
#define P3A_74_FRAME_CTRL_74                                        0x3A74
#define P3A_75_FRAME_CTRL_75                                        0x3A75
#define P3A_76_FRAME_CTRL_76                                        0x3A76
#define P3A_77_FRAME_CTRL_77                                        0x3A77
#define P3A_78_FRAME_CTRL_78                                        0x3A78
#define P3A_79_FRAME_CTRL_79                                        0x3A79
#define P3A_7A_FRAME_CTRL_7A                                        0x3A7A
#define P3A_7B_FRAME_CTRL_7B                                        0x3A7B
#define P3A_7C_FRAME_CTRL_7C                                        0x3A7C
#define P3A_7D_FRAME_CTRL_7D                                        0x3A7D
#define P3A_7E_FRAME_CTRL_7E                                        0x3A7E
#define P3A_7F_FRAME_CTRL_7F                                        0x3A7F
#define P3A_80_FRAME_CTRL_80                                        0x3A80
#define P3A_81_FRAME_CTRL_81                                        0x3A81
#define P3A_82_FRAME_CTRL_82                                        0x3A82
#define P3A_83_FRAME_CTRL_83                                        0x3A83
#define P3A_84_FRAME_CTRL_84                                        0x3A84
#define P3A_85_FRAME_CTRL_85                                        0x3A85
#define P3A_86_FRAME_CTRL_86                                        0x3A86
#define P3A_87_FRAME_CTRL_87                                        0x3A87
#define P3A_88_FRAME_CTRL_88                                        0x3A88
#define P3A_89_FRAME_CTRL_89                                        0x3A89
#define P3A_8A_FRAME_CTRL_8A                                        0x3A8A
#define P3A_8B_FRAME_CTRL_8B                                        0x3A8B
#define P3A_8C_FRAME_CTRL_8C_DUMMY                                  0x3A8C
#define P3A_8D_FRAME_CTRL_8D_DUMMY                                  0x3A8D
#define P3A_8E_FRAME_CTRL_8E_DUMMY                                  0x3A8E
#define P3A_8F_FRAME_CTRL_8F_DUMMY                                  0x3A8F
#define P3A_90_OSD_LUT_BIST_CTRL                                    0x3A90
#define P3A_91_OSD_LUT_DRF_BIST_CTRL                                0x3A91
#define P3A_92_OSD_LUT_M2_BIST_CTRL                                 0x3A92
#define P3A_93_OSD_LUT_M2_DRF_BIST_CTRL                             0x3A93
#define P3A_94_OSD_VLB_BIST_CTRL                                    0x3A94
#define P3A_95_OSD_VLB_DRF_BIST_CTRL                                0x3A95


//--------------------------------------------------
// Flash Partition (Page 3F)
//--------------------------------------------------
#define P3F_A0_FLASH_SIZE_HEADER_H                                  0x3FA0
#define P3F_A1_FLASH_SIZE_HEADER_L                                  0x3FA1
#define P3F_A2_FLASH_SIZE_TOTAL_BANK_H                              0x3FA2
#define P3F_A3_FLASH_SIZE_TOTAL_BANK_L                              0x3FA3
#define P3F_A4_FLASH_SIZE_TAIL_H                                    0x3FA4
#define P3F_A5_FLASH_SIZE_TAIL_L                                    0x3FA5
#define P3F_A6_BT_FW_INFO_SEL                                       0x3FA6
#define P3F_A7_CRC_OPTION_H                                         0x3FA7
#define P3F_A8_CRC_OPTION_L                                         0x3FA8
#define P3F_A9_SPECIAL_STRING_0                                     0x3FA9
#define P3F_AA_SPECIAL_STRING_1                                     0x3FAA
#define P3F_AB_SPECIAL_STRING_2                                     0x3FAB
#define P3F_AC_SPECIAL_STRING_3                                     0x3FAC
#define P3F_AD_SPECIAL_STR_CHECK_FLAG                               0x3FAD
#define P3F_AE_PARTITION_STATE                                      0x3FAE
#define P3F_AF_BANK_SHIFT_NO                                        0x3FAF
#define P3F_B0_BANK0_LENGTH_H                                       0x3FB0
#define P3F_B1_BANK0_LENGTH_L                                       0x3FB1
#define P3F_B2_BANK0_CRC                                            0x3FB2
#define P3F_B3_BANK0_HW_CRC                                         0x3FB3
#define P3F_B4_BANK0_CRC_CHECK_FLAG                                 0x3FB4
#define P3F_B5_BANK1_LENGTH_H                                       0x3FB5
#define P3F_B6_BANK1_LENGTH_L                                       0x3FB6
#define P3F_B7_BANK1_CRC                                            0x3FB7
#define P3F_B8_BANK1_HW_CRC                                         0x3FB8
#define P3F_B9_BANK1_CRC_CHECK_FLAG                                 0x3FB9
#define P3F_BA_BANK2_LENGTH_H                                       0x3FBA
#define P3F_BB_BANK2_LENGTH_L                                       0x3FBB
#define P3F_BC_BANK2_CRC                                            0x3FBC
#define P3F_BD_BANK2_HW_CRC                                         0x3FBD
#define P3F_BE_BANK2_CRC_CHECK_FLAG                                 0x3FBE
#define P3F_BF_BANK3_LENGTH_H                                       0x3FBF
#define P3F_C0_BANK3_LENGTH_L                                       0x3FC0
#define P3F_C1_BANK3_CRC                                            0x3FC1
#define P3F_C2_BANK3_HW_CRC                                         0x3FC2
#define P3F_C3_BANK3_CRC_CHECK_FLAG                                 0x3FC3
#define P3F_C4_BANK4_LENGTH_H                                       0x3FC4
#define P3F_C5_BANK4_LENGTH_L                                       0x3FC5
#define P3F_C6_BANK4_CRC                                            0x3FC6
#define P3F_C7_BANK4_HW_CRC                                         0x3FC7
#define P3F_C8_BANK4_CRC_CHECK_FLAG                                 0x3FC8
#define P3F_C9_BANK5_LENGTH_H                                       0x3FC9
#define P3F_CA_BANK5_LENGTH_L                                       0x3FCA
#define P3F_CB_BANK5_CRC                                            0x3FCB
#define P3F_CC_BANK5_HW_CRC                                         0x3FCC
#define P3F_CD_BANK5_CRC_CHECK_FLAG                                 0x3FCD
#define P3F_CE_BANK6_LENGTH_H                                       0x3FCE
#define P3F_CF_BANK6_LENGTH_L                                       0x3FCF
#define P3F_D0_BANK6_CRC                                            0x3FD0
#define P3F_D1_BANK6_HW_CRC                                         0x3FD1
#define P3F_D2_BANK6_CRC_CHECK_FLAG                                 0x3FD2
#define P3F_D3_BANK7_LENGTH_H                                       0x3FD3
#define P3F_D4_BANK7_LENGTH_L                                       0x3FD4
#define P3F_D5_BANK7_CRC                                            0x3FD5
#define P3F_D6_BANK7_HW_CRC                                         0x3FD6
#define P3F_D7_BANK7_CRC_CHECK_FLAG                                 0x3FD7
#define P3F_D8_BANK8_LENGTH_H                                       0x3FD8
#define P3F_D9_BANK8_LENGTH_L                                       0x3FD9
#define P3F_DA_BANK8_CRC                                            0x3FDA
#define P3F_DB_BANK8_HW_CRC                                         0x3FDB
#define P3F_DC_BANK8_CRC_CHECK_FLAG                                 0x3FDC
#define P3F_DD_BANK9_LENGTH_H                                       0x3FDD
#define P3F_DE_BANK9_LENGTH_L                                       0x3FDE
#define P3F_DF_BANK9_CRC                                            0x3FDF
#define P3F_E0_BANK9_HW_CRC                                         0x3FE0
#define P3F_E1_BANK9_CRC_CHECK_FLAG                                 0x3FE1
#define P3F_E2_BANK10_LENGTH_H                                      0x3FE2
#define P3F_E3_BANK10_LENGTH_L                                      0x3FE3
#define P3F_E4_BANK10_CRC                                           0x3FE4
#define P3F_E5_BANK10_HW_CRC                                        0x3FE5
#define P3F_E6_BANK10_CRC_CHECK_FLAG                                0x3FE6
#define P3F_E7_BANK11_LENGTH_H                                      0x3FE7
#define P3F_E8_BANK11_LENGTH_L                                      0x3FE8
#define P3F_E9_BANK11_CRC                                           0x3FE9
#define P3F_EA_BANK11_HW_CRC                                        0x3FEA
#define P3F_EB_BANK11_CRC_CHECK_FLAG                                0x3FEB
#define P3F_EC_BANK12_LENGTH_H                                      0x3FEC
#define P3F_ED_BANK12_LENGTH_L                                      0x3FED
#define P3F_EE_BANK12_CRC                                           0x3FEE
#define P3F_EF_BANK12_HW_CRC                                        0x3FEF
#define P3F_F0_BANK12_CRC_CHECK_FLAG                                0x3FF0
#define P3F_F1_BANK13_LENGTH_H                                      0x3FF1
#define P3F_F2_BANK13_LENGTH_L                                      0x3FF2
#define P3F_F3_BANK13_CRC                                           0x3FF3
#define P3F_F4_BANK13_HW_CRC                                        0x3FF4
#define P3F_F5_BANK13_CRC_CHECK_FLAG                                0x3FF5
#define P3F_F6_BANK14_LENGTH_H                                      0x3FF6
#define P3F_F7_BANK14_LENGTH_L                                      0x3FF7
#define P3F_F8_BANK14_CRC                                           0x3FF8
#define P3F_F9_BANK14_HW_CRC                                        0x3FF9
#define P3F_FA_BANK14_CRC_CHECK_FLAG                                0x3FFA
#define P3F_FB_BANK15_LENGTH_H                                      0x3FFB
#define P3F_FC_BANK15_LENGTH_L                                      0x3FFC
#define P3F_FD_BANK15_CRC                                           0x3FFD
#define P3F_FE_BANK15_HW_CRC                                        0x3FFE
#define P3F_FF_BANK15_CRC_CHECK_FLAG                                0x3FFF


//--------------------------------------------------
// Sync Processor Clock Divider (Page 40)
//--------------------------------------------------
#define P40_06_SYNCPROC_CLK_DIVIDER                                 0x4006


//--------------------------------------------------
// Measure Block Clock Divider (Page 40)
//--------------------------------------------------
#define P40_07_MEASURE_CLK_DIVIDER                                  0x4007
#define P40_09_TOP_DUMMY3                                           0x4009


//--------------------------------------------------
// GDI_2 Power Control (Page 40)
//--------------------------------------------------
#define P40_0A_GDI_2_POWER_CTRL                                     0x400A
#define P40_0B_TOP_DUMMY4                                           0x400B
#define P40_0D_TOP_DUMMY5                                           0x400D


//--------------------------------------------------
// USB 2.0 Host Controller (Page 61)
//--------------------------------------------------
#define P61_00_USB_CTR0_REG_1                                       0x6100
#define P61_01_USB_DIVIDER                                          0x6101
#define P61_02_USB_REGIF_CTRL                                       0x6102
#define P61_03_USB_REG_ADDR                                         0x6103
#define P61_04_USB_REG_DATA0                                        0x6104
#define P61_05_USB_REG_DATA1                                        0x6105
#define P61_06_USB_REG_DATA2                                        0x6106
#define P61_07_USB_REG_DATA3                                        0x6107
#define P61_11_USB_BUF_CTRL                                         0x6111
#define P61_12_USB_BUF_ADR_MSB                                      0x6112
#define P61_13_USB_BUF_ADR_LSB                                      0x6113
#define P61_14_USB_BUF_DATA0                                        0x6114
#define P61_15_USB_BUF_DATA1                                        0x6115
#define P61_16_USB_BUF_DATA2                                        0x6116
#define P61_17_USB_BUF_DATA3                                        0x6117
#define P61_18_USB_BIST_CTRL                                        0x6118
#define P61_20_USB_ADDR_MAP_CTRL0                                   0x6120
#define P61_21_USB_ADDR_MAP_ADDR0                                   0x6121
#define P61_22_USB_ADDR_DEST_MSB0                                   0x6122
#define P61_23_USB_ADDR_DEST_LSB0                                   0x6123
#define P61_24_USB_ADDR_MAP_CTRL1                                   0x6124
#define P61_25_USB_ADDR_MAP_ADDR1                                   0x6125
#define P61_26_USB_ADDR_DEST_MSB1                                   0x6126
#define P61_27_USB_ADDR_DEST_LSB1                                   0x6127
#define P61_28_USB_ADDR_MAP_CTRL2                                   0x6128
#define P61_29_USB_ADDR_MAP_ADDR2                                   0x6129
#define P61_2A_USB_ADDR_DEST_MSB2                                   0x612A
#define P61_2B_USB_ADDR_DEST_LSB2                                   0x612B
#define P61_2C_USB_ADDR_DEST_ELSE_MSB                               0x612C
#define P61_2D_USB_ADDR_DEST_ELSE_LSB0                              0x612D
#define P61_60_USB_WRAPP_REG_0                                      0x6160
#define P61_61_USB_WRAPP_REG_1                                      0x6161
#define P61_62_USB_VSTATUS_REG                                      0x6162
#define P61_63_USB_SYS_INT_REG                                      0x6163
#define P61_64_USB_EHCI_POWMANAGE_REG                               0x6164
#define P61_65_USB_EHCI_STRAP_SIG_REG_0                             0x6165
#define P61_66_USB_EHCI_STRAP_SIG_REG_1                             0x6166
#define P61_67_USB_UTMI_STRAP_SIG_REG                               0x6167
#define P61_68_USB_OHCI_SIG_REG                                     0x6168
#define P61_69_USB_OHCI_LEG_SIG_REG                                 0x6169
#define P61_6A_USB_MUX_SIG_REG                                      0x616A
#define P61_6B_USB_RESET_UTMI_REG                                   0x616B
#define P61_6C_USB_SELF_LOOP_BACK_REG_0                             0x616C
#define P61_6D_USB_SELF_LOOP_BACK_REG_1                             0x616D
#define P61_6E_USB_PHY_SLB0_REG                                     0x616E
#define P61_6F_USB_CTR0_REG_0                                       0x616F

//--------------------------------------------------
// Embedded LDO(Page 62)
//--------------------------------------------------
#define P62_00_EBD_REGLATOR_A_CTRL1                                 0x6200
#define P62_01_EBD_REGLATOR_A_CTRL2                                 0x6201
#define P62_02_EBD_REGLATOR_A_CTRL3                                 0x6202
#define P62_03_EBD_REGLATOR_D_CTRL1                                 0x6203
#define P62_04_EBD_REGLATOR_D_CTRL2                                 0x6204
#define P62_05_EBD_REGLATOR_D_CTRL3                                 0x6205


//--------------------------------------------------
// HDCP 2.2 Overview (Page 63)
//--------------------------------------------------

#define P63_00_HDCP_MSG_CTRL                                        0x6300
#define P63_01_HDCP_MSGWAP                                          0x6301
#define P63_02_HDCP_MSGWDP                                          0x6302
#define P63_03_HDCP_MSGRAP_H                                        0x6303
#define P63_04_HDCP_MSGRAP_L                                        0x6304
#define P63_05_HDCP_MSGRDP                                          0x6305
#define P63_10_HDCP_RSA_CTRL0                                       0x6310
#define P63_11_HDCP_RSA_CTRL1                                       0x6311
#define P63_12_HDCP_RSA_NP_INV_3                                    0x6312
#define P63_13_HDCP_RSA_NP_INV_2                                    0x6313
#define P63_14_HDCP_RSA_NP_INV_1                                    0x6314
#define P63_15_HDCP_RSA_NP_INV_0                                    0x6315
#define P63_16_HDCP_RSA_DATA_ADDR                                   0x6316
#define P63_17_HDCP_RSA_DATA_IN_DATA7                               0x6317
#define P63_18_HDCP_RSA_DATA_IN_DATA6                               0x6318
#define P63_19_HDCP_RSA_DATA_IN_DATA5                               0x6319
#define P63_1A_HDCP_RSA_DATA_IN_DATA4                               0x631A
#define P63_1B_HDCP_RSA_DATA_IN_DATA3                               0x631B
#define P63_1C_HDCP_RSA_DATA_IN_DATA2                               0x631C
#define P63_1D_HDCP_RSA_DATA_IN_DATA1                               0x631D
#define P63_1E_HDCP_RSA_DATA_IN_DATA0                               0x631E
#define P63_20_HDCP_RSA_DATA_OUT_DATA7                              0x6320
#define P63_21_HDCP_RSA_DATA_OUT_DATA6                              0x6321
#define P63_22_HDCP_RSA_DATA_OUT_DATA5                              0x6322
#define P63_23_HDCP_RSA_DATA_OUT_DATA4                              0x6323
#define P63_24_HDCP_RSA_DATA_OUT_DATA3                              0x6324
#define P63_25_HDCP_RSA_DATA_OUT_DATA2                              0x6325
#define P63_26_HDCP_RSA_DATA_OUT_DATA1                              0x6326
#define P63_27_HDCP_RSA_DATA_OUT_DATA0                              0x6327
#define P63_30_HDCP_SHA_CONTRL                                      0x6330
#define P63_31_HDCP_SHA_DATA1                                       0x6331
#define P63_32_HDCP_SHA_DATA2                                       0x6332
#define P63_33_HDCP_SHA_DATA3                                       0x6333
#define P63_34_HDCP_SHA_DATA4                                       0x6334
#define P63_35_HDCP_SHA_0                                           0x6335
#define P63_36_HDCP_SHA_1                                           0x6336
#define P63_37_HDCP_SHA_2                                           0x6337
#define P63_38_HDCP_SHA_3                                           0x6338
#define P63_39_HDCP_SHA_4                                           0x6339
#define P63_3A_HDCP_SHA_5                                           0x633A
#define P63_3B_HDCP_SHA_6                                           0x633B
#define P63_3C_HDCP_SHA_7                                           0x633C
#define P63_3D_HDCP_SHA_8                                           0x633D
#define P63_3E_HDCP_SHA_9                                           0x633E
#define P63_3F_HDCP_SHA_10                                          0x633F
#define P63_40_HDCP_SHA_11                                          0x6340
#define P63_41_HDCP_SHA_12                                          0x6341
#define P63_42_HDCP_SHA_13                                          0x6342
#define P63_43_HDCP_SHA_14                                          0x6343
#define P63_44_HDCP_SHA_15                                          0x6344
#define P63_45_HDCP_SHA_16                                          0x6345
#define P63_46_HDCP_SHA_17                                          0x6346
#define P63_47_HDCP_SHA_18                                          0x6347
#define P63_48_HDCP_SHA_19                                          0x6348
#define P63_49_HDCP_SHA_20                                          0x6349
#define P63_4A_HDCP_SHA_21                                          0x634A
#define P63_4B_HDCP_SHA_22                                          0x634B
#define P63_4C_HDCP_SHA_23                                          0x634C
#define P63_4D_HDCP_SHA_24                                          0x634D
#define P63_4E_HDCP_SHA_25                                          0x634E
#define P63_4F_HDCP_SHA_26                                          0x634F
#define P63_50_HDCP_SHA_27                                          0x6350
#define P63_51_HDCP_SHA_28                                          0x6351
#define P63_52_HDCP_SHA_29                                          0x6352
#define P63_53_HDCP_SHA_30                                          0x6353
#define P63_54_HDCP_SHA_31                                          0x6354
#define P63_60_HDCP_AES_CTRL                                        0x6360
#define P63_61_HDCP_AES_DATA_IN_15                                  0x6361
#define P63_62_HDCP_AES_DATA_IN_14                                  0x6362
#define P63_63_HDCP_AES_DATA_IN_13                                  0x6363
#define P63_64_HDCP_AES_DATA_IN_12                                  0x6364
#define P63_65_HDCP_AES_DATA_IN_11                                  0x6365
#define P63_66_HDCP_AES_DATA_IN_10                                  0x6366
#define P63_67_HDCP_AES_DATA_IN_9                                   0x6367
#define P63_68_HDCP_AES_DATA_IN_8                                   0x6368
#define P63_69_HDCP_AES_DATA_IN_7                                   0x6369
#define P63_6A_HDCP_AES_DATA_IN_6                                   0x636A
#define P63_6B_HDCP_AES_DATA_IN_5                                   0x636B
#define P63_6C_HDCP_AES_DATA_IN_4                                   0x636C
#define P63_6D_HDCP_AES_DATA_IN_3                                   0x636D
#define P63_6E_HDCP_AES_DATA_IN_2                                   0x636E
#define P63_6F_HDCP_AES_DATA_IN_1                                   0x636F
#define P63_70_HDCP_AES_DATA_IN_0                                   0x6370
#define P63_71_HDCP_AES_CIPHER_KEY_15                               0x6371
#define P63_72_HDCP_AES_CIPHER_KEY_14                               0x6372
#define P63_73_HDCP_AES_CIPHER_KEY_13                               0x6373
#define P63_74_HDCP_AES_CIPHER_KEY_12                               0x6374
#define P63_75_HDCP_AES_CIPHER_KEY_11                               0x6375
#define P63_76_HDCP_AES_CIPHER_KEY_10                               0x6376
#define P63_77_HDCP_AES_CIPHER_KEY_9                                0x6377
#define P63_78_HDCP_AES_CIPHER_KEY_8                                0x6378
#define P63_79_HDCP_AES_CIPHER_KEY_7                                0x6379
#define P63_7A_HDCP_AES_CIPHER_KEY_6                                0x637A
#define P63_7B_HDCP_AES_CIPHER_KEY_5                                0x637B
#define P63_7C_HDCP_AES_CIPHER_KEY_4                                0x637C
#define P63_7D_HDCP_AES_CIPHER_KEY_3                                0x637D
#define P63_7E_HDCP_AES_CIPHER_KEY_2                                0x637E
#define P63_7F_HDCP_AES_CIPHER_KEY_1                                0x637F
#define P63_80_HDCP_AES_CIPHER_KEY_0                                0x6380
#define P63_81_HDCP_AES_OUT_15                                      0x6381
#define P63_82_HDCP_AES_OUT_14                                      0x6382
#define P63_83_HDCP_AES_OUT_13                                      0x6383
#define P63_84_HDCP_AES_OUT_12                                      0x6384
#define P63_85_HDCP_AES_OUT_11                                      0x6385
#define P63_86_HDCP_AES_OUT_10                                      0x6386
#define P63_87_HDCP_AES_OUT_9                                       0x6387
#define P63_88_HDCP_AES_OUT_8                                       0x6388
#define P63_89_HDCP_AES_OUT_7                                       0x6389
#define P63_8A_HDCP_AES_OUT_6                                       0x638A
#define P63_8B_HDCP_AES_OUT_5                                       0x638B
#define P63_8C_HDCP_AES_OUT_4                                       0x638C
#define P63_8D_HDCP_AES_OUT_3                                       0x638D
#define P63_8E_HDCP_AES_OUT_2                                       0x638E
#define P63_8F_HDCP_AES_OUT_1                                       0x638F
#define P63_90_HDCP_AES_OUT_0                                       0x6390
#define P63_91_HDCP_BIST_CTRL                                       0x6391
#define P63_92_HDCP_DUMMY1                                          0x6392
#define P63_93_HDCP_DUMMY2                                          0x6393
#define P63_A0_HDCP_I2C_CTRL_A0                                     0x63A0
#define P63_A1_HDCP_I2C_CTRL_A1                                     0x63A1
#define P63_A2_HDCP_I2C_CTRL_A2                                     0x63A2
#define P63_A3_HDCP_I2C_CTRL_A3                                     0x63A3
#define P63_A4_HDCP_I2C_CTRL_A4                                     0x63A4
#define P63_A5_HDCP_I2C_CTRL_A5                                     0x63A5
#define P63_A6_HDCP_I2C_CTRL_A6                                     0x63A6
#define P63_A7_HDCP_I2C_CTRL_RIV7                                   0x63A7
#define P63_A8_HDCP_I2C_CTRL_RIV6                                   0x63A8
#define P63_A9_HDCP_I2C_CTRL_RIV5                                   0x63A9
#define P63_AA_HDCP_I2C_CTRL_RIV4                                   0x63AA
#define P63_AB_HDCP_I2C_CTRL_RIV3                                   0x63AB
#define P63_AC_HDCP_I2C_CTRL_RIV2                                   0x63AC
#define P63_AD_HDCP_I2C_CTRL_RIV1                                   0x63AD
#define P63_AE_HDCP_I2C_CTRL_RIV0                                   0x63AE
#define P63_C0_HDCP_I2C_CTRL_C0                                     0x63C0
#define P63_C1_HDCP_I2C_CTRL_C1                                     0x63C1
#define P63_D0_HDCP_I2C_M0_MBIST_CTRL_0                             0x63D0
#define P63_D1_HDCP_I2C_M0_MBIST_CTRL_1                             0x63D1
#define P63_D3_HDCP_I2C_M1_MBIST_CTRL_0                             0x63D3
#define P63_D4_HDCP_I2C_M1_MBIST_CTRL_1                             0x63D4
#define P63_E0_HDCP_I2C_DUMMY_0                                     0x63E0
#define P63_E1_HDCP_I2C_DUMMY_1                                     0x63E1

//--------------------------------------------------
// ADI Global Control (Page 6F)
//--------------------------------------------------
#define P6F_00_MUX_DIG_OUT                                          0x6F00
#define P6F_01_MUX_DA_DVC_IN                                        0x6F01
#define P6F_02_MUX_DP_I2S_IN                                        0x6F02
#define P6F_03_MUX_TST_OUT                                          0x6F03
#define P6F_04_CBUS0_MAP_DDC                                        0x6F04
#define P6F_05_CBUS1_MAP_DDC                                        0x6F05
#define P6F_09_AUX_MAP_DDC                                          0x6F09
#define P6F_10_ADI_IRQ_CTRL                                         0x6F10
#define P6F_11_ADI_HALF_SD                                          0x6F11
#define P6F_12_MHL_TST_OUT                                          0x6F12


//--------------------------------------------------
// GDI Clock Divider (Page 80)
//--------------------------------------------------
#define P80_06_GDI_CLK_DIVIDER                                      0x8006


//--------------------------------------------------
// GDI PHY Power Control (Page 80)
//--------------------------------------------------
#define P80_0A_GDI_PHY_POWER_CTRL                                   0x800A
#define P80_0B_TOP_DUMMY6                                           0x800B
#define P80_0D_TOP_DUMMY7                                           0x800D


//--------------------------------------------------
// XTAL (Page 80)
//--------------------------------------------------
#define P80_0E_XTAL_CTRL0                                           0x800E
#define P80_0F_XTAL_CTRL1                                           0x800F


//--------------------------------------------------
// D0 Port DisplayPort 1.2 Digital MAC(Page B5)
//--------------------------------------------------
#define PB5_00_MAC_DIG_RESET_CTRL                                   0xB500
#define PB5_01_STHD_CTRL_0                                          0xB501
#define PB5_20_PG_CTRL_0                                            0xB520
#define PB5_21_PG_CTRL_1                                            0xB521
#define PB5_22_PG_CTRL_2                                            0xB522
#define PB5_23_PG_CTRL_3                                            0xB523
#define PB5_24_RB422_YONLY                                          0xB524
#define PB5_25_SRAM_BIST_0                                          0xB525
#define PB5_26_SRAM_BIST_1                                          0xB526
#define PB5_30_DPF_CTRL_0                                           0xB530
#define PB5_31_DP_OUTPUT_CTRL                                       0xB531
#define PB5_32_EVBLK2VS_H                                           0xB532
#define PB5_33_EVBLK2VS_M                                           0xB533
#define PB5_34_EVBLK2VS_L                                           0xB534
#define PB5_35_OVBLK2VS_H                                           0xB535
#define PB5_36_OVBLK2VS_M                                           0xB536
#define PB5_37_OVBLK2VS_L                                           0xB537
#define PB5_38_BS2HS_0                                              0xB538
#define PB5_39_BS2HS_1                                              0xB539
#define PB5_40_VS_FRONT_PORCH                                       0xB540
#define PB5_41_MN_DPF_HTT_M                                         0xB541
#define PB5_42_MN_DPF_HTT_L                                         0xB542
#define PB5_43_MN_DPF_HST_M                                         0xB543
#define PB5_44_MN_DPF_HST_L                                         0xB544
#define PB5_45_MN_DPF_HWD_M                                         0xB545
#define PB5_46_MN_DPF_HWD_L                                         0xB546
#define PB5_47_MN_DPF_HSW_M                                         0xB547
#define PB5_48_MN_DPF_HSW_L                                         0xB548
#define PB5_49_MN_DPF_VTT_M                                         0xB549
#define PB5_4A_MN_DPF_VTT_L                                         0xB54A
#define PB5_4B_MN_DPF_VST_M                                         0xB54B
#define PB5_4C_MN_DPF_VST_L                                         0xB54C
#define PB5_4D_MN_DPF_VHT_M                                         0xB54D
#define PB5_4E_MN_DPF_VHT_L                                         0xB54E
#define PB5_4F_MN_DPF_VSW_M                                         0xB54F
#define PB5_50_MN_DPF_VSW_L                                         0xB550
#define PB5_51_MN_DPF_BG_RED_M                                      0xB551
#define PB5_52_MN_DPF_BG_RED_L                                      0xB552
#define PB5_53_MN_DPF_BG_GRN_M                                      0xB553
#define PB5_54_MN_DPF_BG_GRN_L                                      0xB554
#define PB5_55_MN_DPF_BG_BLU_M                                      0xB555
#define PB5_56_MN_DPF_BG_BLU_L                                      0xB556
#define PB5_57_INTERLACE_MODE_CONFIG                                0xB557
#define PB5_58_MN_MEAS_CTRL                                         0xB558
#define PB5_59_MN_MEAS_VLN_M                                        0xB559
#define PB5_5A_MN_MEAS_VLN_L                                        0xB55A
#define PB5_5B_MN_MEAS_HLN_M                                        0xB55B
#define PB5_5C_MN_MEAS_HLN_L                                        0xB55C
#define PB5_5D_VHEIGHT_MSB                                          0xB55D
#define PB5_5E_VHEIGHT_LSB                                          0xB55E
#define PB5_5F_VBLANK_MSB                                           0xB55F
#define PB5_60_VBLANK_LSB                                           0xB560
#define PB5_61_HBLANK_MSB                                           0xB561
#define PB5_62_HBLANK_LSB                                           0xB562
#define PB5_70_DP_CRC_CTRL                                          0xB570
#define PB5_71_DP_CRC_R_M                                           0xB571
#define PB5_72_DP_CRC_R_L                                           0xB572
#define PB5_73_DP_CRC_G_M                                           0xB573
#define PB5_74_DP_CRC_G_L                                           0xB574
#define PB5_75_DP_CRC_B_M                                           0xB575
#define PB5_76_DP_CRC_B_L                                           0xB576
#define PB5_77_DP_CRC_CB_M                                          0xB577
#define PB5_78_DP_CRC_CB_L                                          0xB578
#define PB5_E0_TEST0                                                0xB5E0
#define PB5_E1_TEST1                                                0xB5E1
#define PB5_E2_CPMODE                                               0xB5E2
#define PB5_F0_DP_RSV0                                              0xB5F0
#define PB5_F1_DP_RSV1                                              0xB5F1
#define PB5_F2_DP_RSV2                                              0xB5F2
#define PB5_F3_DP_RSV3                                              0xB5F3
#define PB5_F4_DP_RSV4                                              0xB5F4
#define PB5_F5_DP_RSV5                                              0xB5F5
#define PB5_F6_DP_RSV6                                              0xB5F6
#define PB5_F7_DP_RSV7                                              0xB5F7
#define PB5_F8_DP_RSV8                                              0xB5F8
#define PB5_F9_DP_RSV9                                              0xB5F9
#define PB5_FA_DP_RSVA                                              0xB5FA


//--------------------------------------------------
// D0 Port DisplayPort 1.2 Digital MAC (Page B5)
//--------------------------------------------------
#define PB5_A0_MN_SCLKG_CTRL                                        0xB5A0
#define PB5_A1_MN_SCLKG_DIVM                                        0xB5A1
#define PB5_A2_MN_SCLKG_DIVN                                        0xB5A2
#define PB5_A3_MN_SCLKG_DIVS                                        0xB5A3
#define PB5_A4_MN_SCLKG_OFFS_H                                      0xB5A4
#define PB5_A5_MN_SCLKG_OFFS_M                                      0xB5A5
#define PB5_A6_MN_SCLKG_OFFS_L                                      0xB5A6
#define PB5_A7_MN_SCLKG_TRK_CTRL                                    0xB5A7
#define PB5_A8_MN_SCLKG_TRK_MN_I_H                                  0xB5A8
#define PB5_A9_MN_SCLKG_TRK_MN_I_M                                  0xB5A9
#define PB5_AA_MN_SCLKG_TRK_MN_I_L                                  0xB5AA
#define PB5_AB_MN_SCLKG_TRK_MN_P_H                                  0xB5AB
#define PB5_AC_MN_SCLKG_TRK_MN_P_M                                  0xB5AC
#define PB5_AD_MN_SCLKG_TRK_MN_P_L                                  0xB5AD
#define PB5_AE_MN_SCLKG_TRK_MN_PE                                   0xB5AE
#define PB5_AF_MN_SCLKG_TRK_MN_NLOCK                                0xB5AF
#define PB5_B0_MN_SCLKG_TRK_VS_I_H                                  0xB5B0
#define PB5_B1_MN_SCLKG_TRK_VS_I_M                                  0xB5B1
#define PB5_B2_MN_SCLKG_TRK_VS_I_L                                  0xB5B2
#define PB5_B3_MN_SCLKG_TRK_VS_P_H                                  0xB5B3
#define PB5_B4_MN_SCLKG_TRK_VS_P_M                                  0xB5B4
#define PB5_B5_MN_SCLKG_TRK_VS_P_L                                  0xB5B5
#define PB5_B6_MN_SCLKG_TRK_VS_PE                                   0xB5B6
#define PB5_B7_MN_SCLKG_TRK_VS_NLOCK                                0xB5B7
#define PB5_B8_MN_SCLKG_SDM_CTRL                                    0xB5B8
#define PB5_B9_MN_SCLKG_SDM_TEST                                    0xB5B9
#define PB5_BA_MN_SCLKG_SDM_SUMC_H                                  0xB5BA
#define PB5_BB_MN_SCLKG_SDM_SUMC_M                                  0xB5BB
#define PB5_BC_MN_SCLKG_SDM_SUMC_L                                  0xB5BC
#define PB5_BD_MN_SCLKG_PLL_PWR                                     0xB5BD
#define PB5_BE_MN_SCLKG_PLL_CHP                                     0xB5BE
#define PB5_BF_MN_SCLKG_PLL_WD                                      0xB5BF
#define PB5_C0_MN_SCLKG_PLL_INSEL                                   0xB5C0
#define PB5_C1_MN_SCLKG_PLL_RESERVE                                 0xB5C1
#define PB5_C2_HS_TRACKING_NEW_MODE1                                0xB5C2
#define PB5_C3_HS_TRACKING_NEW_MODE2                                0xB5C3
#define PB5_C4_DUMMY_0                                              0xB5C4
#define PB5_C5_DUMMY_1                                              0xB5C5
#define PB5_C6_DUMMY_2                                              0xB5C6
#define PB5_C7_DUMMY_3                                              0xB5C7


//--------------------------------------------------
// D0 DisplayPort SEC DATA (Page B6)
//--------------------------------------------------
#define PB6_00_MN_STRM_ATTR_CTRL                                    0xB600
#define PB6_01_DP_VBID                                              0xB601
#define PB6_02_MN_STRM_ATTR_MISC                                    0xB602
#define PB6_03_MN_STRM_ATTR_MISC1                                   0xB603
#define PB6_08_MSA_HTT_0                                            0xB608
#define PB6_09_MSA_HTT_1                                            0xB609
#define PB6_0A_MSA_HST_0                                            0xB60A
#define PB6_0B_MSA_HST_1                                            0xB60B
#define PB6_0C_MSA_HWD_0                                            0xB60C
#define PB6_0D_MSA_HWD_1                                            0xB60D
#define PB6_0E_MSA_HSW_0                                            0xB60E
#define PB6_0F_MSA_HSW_1                                            0xB60F
#define PB6_10_MSA_VTTE_0                                           0xB610
#define PB6_11_MSA_VTTE_1                                           0xB611
#define PB6_12_MSA_VTTO_0                                           0xB612
#define PB6_13_MSA_VTTO_1                                           0xB613
#define PB6_14_MSA_VST_0                                            0xB614
#define PB6_15_MSA_VST_1                                            0xB615
#define PB6_16_MSA_VHT_0                                            0xB616
#define PB6_17_MSA_VHT_1                                            0xB617
#define PB6_18_MSA_VSW_0                                            0xB618
#define PB6_19_MSA_VSW_1                                            0xB619
#define PB6_1A_MSA_MVID_0                                           0xB61A
#define PB6_1B_MSA_MVID_1                                           0xB61B
#define PB6_1C_MSA_MVID_2                                           0xB61C
#define PB6_1D_MSA_NVID_0                                           0xB61D
#define PB6_1E_MSA_NVID_1                                           0xB61E
#define PB6_1F_MSA_NVID_2                                           0xB61F
#define PB6_20_MSA_MAUD_0                                           0xB620
#define PB6_21_MSA_MAUD_1                                           0xB621
#define PB6_22_MSA_MAUD_2                                           0xB622
#define PB6_23_MSA_NAUD_0                                           0xB623
#define PB6_24_MSA_NAUD_1                                           0xB624
#define PB6_25_MSA_NAUD_2                                           0xB625
#define PB6_26_DP_AUD_CH_STATUS0                                    0xB626
#define PB6_27_DP_AUD_CH_STATUS1                                    0xB627
#define PB6_28_DP_AUD_CH_STATUS2                                    0xB628
#define PB6_29_DP_AUD_CH_STATUS3                                    0xB629
#define PB6_2A_DP_AUD_CH_STATUS4                                    0xB62A
#define PB6_2B_MN_RS_DEC_CTRL                                       0xB62B
#define PB6_2C_DP_INFO_FM_RSV0                                      0xB62C
#define PB6_2D_DP_INFO_FM_RSV1                                      0xB62D
#define PB6_30_DP_INFO_FM_ADR                                       0xB630
#define PB6_31_DP_INFO_FM_DAT                                       0xB631
#define PB6_32_DP_INFO_VAR_EN_M                                     0xB632
#define PB6_33_DP_INFO_VAR_EN_L                                     0xB633
#define PB6_34_DP_INFO_VAR_ST_M                                     0xB634
#define PB6_35_DP_INFO_VAR_ST_L                                     0xB635
#define PB6_36_DP_GLB_STATUS                                        0xB636
#define PB6_37_DP_AVWD_CTRL                                         0xB637
#define PB6_38_DP_VWD_CTRL                                          0xB638
#define PB6_39_DP_AWD_CTRL                                          0xB639
#define PB6_3A_DP_IRQ_CTRL0                                         0xB63A
#define PB6_3B_DP_IRQ_CTRL1                                         0xB63B
#define PB6_40_VSC0                                                 0xB640
#define PB6_41_VSC1                                                 0xB641
#define PB6_42_VSC2                                                 0xB642
#define PB6_43_VSC3                                                 0xB643
#define PB6_44_VSC4                                                 0xB644
#define PB6_45_VSC5                                                 0xB645
#define PB6_46_VSC6                                                 0xB646
#define PB6_47_VSC7                                                 0xB647
#define PB6_48_VSC8                                                 0xB648
#define PB6_49_VSC9                                                 0xB649
#define PB6_4A_VSCA                                                 0xB64A
#define PB6_4B_VSCB                                                 0xB64B
#define PB6_4C_VSCC                                                 0xB64C
#define PB6_4D_DP_LR_SEL                                            0xB64D
#define PB6_4E_SRAM_BIST_0                                          0xB64E
#define PB6_4F_SRAM_BIST_1                                          0xB64F
#define PB6_50_AUD_FREQUENY_DET_0                                   0xB650
#define PB6_51_AUD_FREQUENY_DET_1                                   0xB651
#define PB6_52_AUD_FREQUENY_TH_0                                    0xB652
#define PB6_53_AUD_FREQUENY_TH_1                                    0xB653
#define PB6_54_AUD_FREQUENY_TH_2                                    0xB654
#define PB6_55_AUD_FREQUENY_TH_3                                    0xB655
#define PB6_56_AUD_FREQUENY_TH_4                                    0xB656
#define PB6_57_AUD_FREQUENY_TH_5                                    0xB657
#define PB6_58_SCODE_0                                              0xB658
#define PB6_59_SCODE_1                                              0xB659
#define PB6_5A_SCODE_2                                              0xB65A
#define PB6_5B_DCODE_0                                              0xB65B
#define PB6_5C_DCODE_1                                              0xB65C
#define PB6_5D_DCODE_2                                              0xB65D
#define PB6_5E_DCODE_3                                              0xB65E
#define PB6_5F_DCODE_4                                              0xB65F
#define PB6_60_DCODE_5                                              0xB660
#define PB6_61_AUD_SAMPLE_CNT_0                                     0xB661
#define PB6_62_AUD_SAMPLE_CNT_1                                     0xB662
#define PB6_63_AUD_DEPTH_TRACKING_NUM_0                             0xB663
#define PB6_64_AUD_DEPTH_TRACKING_NUM_1                             0xB664
#define PB6_65_AUD_DEPTH_TRACKING_NUM_2                             0xB665
#define PB6_66_AUD_DEPTH_TRACKING_NUM_3                             0xB666
#define PB6_67_AUD_DEPTH_TRACKING_NUM_4                             0xB667
#define PB6_68_AUD_DEPTH_ICODE_0                                    0xB668
#define PB6_69_AUD_DEPTH_ICODE_1                                    0xB669
#define PB6_6A_AUD_DEPTH_ICODE_2                                    0xB66A
#define PB6_6B_AUD_DEPTH_ICODE_3                                    0xB66B
#define PB6_6C_AUD_DEPTH_ICODE_4                                    0xB66C
#define PB6_6D_AUD_DEPTH_IGAIN_0                                    0xB66D
#define PB6_6E_AUD_DEPTH_IGAIN_1                                    0xB66E
#define PB6_70_AUD_BUFFER_CTRL_0                                    0xB670
#define PB6_71_AUD_BUFFER_CTRL_1                                    0xB671
#define PB6_72_AUD_BUFFER_CTRL_2                                    0xB672
#define PB6_73_AUD_BUFFER_CTRL_3                                    0xB673
#define PB6_74_AUD_FSM_CTRL_0                                       0xB674
#define PB6_75_AUD_MAN_FSM_CTRL_1                                   0xB675
#define PB6_76_DVC_CTRL                                             0xB676
#define PB6_77_DVC_VA                                               0xB677
#define PB6_78_DVC_WINDOW_CONTROL_0                                 0xB678
#define PB6_79_DVC_WINDOW_CONTROL_1                                 0xB679
#define PB6_7A_DVC_GAIN_READ_MSB                                    0xB67A
#define PB6_7B_DVC_GAIN_READ_LSB                                    0xB67B
#define PB6_7C_AUD_FSM_CTRL_1                                       0xB67C
#define PB6_7D_AUD_FSM_CTRL_2                                       0xB67D
#define PB6_7E_DVC_WINDOW_CONTROL_FAN_OUT                           0xB67E
#define PB6_80_AUD_PS_CTRL_0                                        0xB680
#define PB6_81_AUD_BDRY_0                                           0xB681
#define PB6_82_AUD_BDRY_1                                           0xB682
#define PB6_83_AUD_BDRY_2                                           0xB683
#define PB6_84_AUD_BDRY_3                                           0xB684
#define PB6_85_AUD_BDRY_4                                           0xB685
#define PB6_86_AUD_BDRY_5                                           0xB686
#define PB6_87_AUD_DEPTH_0                                          0xB687
#define PB6_88_AUD_DEPTH_1                                          0xB688
#define PB6_89_AUD_DEPTH_2                                          0xB689
#define PB6_8A_AUD_DEPTH_5                                          0xB68A
#define PB6_8B_AUD_DEPTH_6                                          0xB68B
#define PB6_8C_AUD_MN_DEPTH                                         0xB68C
#define PB6_8D_AUD_MN_0                                             0xB68D
#define PB6_8E_AUD_MN_1                                             0xB68E
#define PB6_8F_AUD_MN_2                                             0xB68F
#define PB6_90_AUD_MN_3                                             0xB690
#define PB6_91_AUD_MN_4                                             0xB691
#define PB6_92_AUD_TRND_0                                           0xB692
#define PB6_93_AUD_TRND_1                                           0xB693
#define PB6_94_AUD_TRND_2                                           0xB694
#define PB6_95_AUD_TRND_3                                           0xB695
#define PB6_96_AUD_TRND_4                                           0xB696
#define PB6_97_AUD_TRND_5                                           0xB697
#define PB6_98_AUD_TRND_6                                           0xB698
#define PB6_99_AUD_TRND_7                                           0xB699
#define PB6_9A_AUD_TRND_8                                           0xB69A
#define PB6_9B_AUD_TRND_9                                           0xB69B
#define PB6_9C_AUD_TRND_10                                          0xB69C
#define PB6_9D_AUD_D_CODE_0                                         0xB69D
#define PB6_A0_AUD_D_CODE_1                                         0xB6A0
#define PB6_A1_AUD_SUMC_MSB                                         0xB6A1
#define PB6_A2_AUD_SUMC_LSB                                         0xB6A2
#define PB6_A9_SPDIF_TX_0                                           0xB6A9
#define PB6_AA_SPDIF_CS_0                                           0xB6AA
#define PB6_AB_SPDIF_CS_1                                           0xB6AB
#define PB6_AC_SPDIF_CS_2                                           0xB6AC
#define PB6_AD_SPDIF_CS_3                                           0xB6AD
#define PB6_AE_SPDIF_CS_4                                           0xB6AE
#define PB6_B0_DP_AUD_CTRL                                          0xB6B0
#define PB6_B1_DP_AUD_ID                                            0xB6B1
#define PB6_B2_DP_AUD_ID_DETECT                                     0xB6B2
#define PB6_B3_DP_CHANNEL_EN                                        0xB6B3
#define PB6_B4_DP_SEC_MISC                                          0xB6B4
#define PB6_B5_DP_AUD_CRC                                           0xB6B5
#define PB6_B6_DP_AUD_CRC_1                                         0xB6B6
#define PB6_B7_TEST_PIN                                             0xB6B7
#define PB6_B8_DP_I2S_CTRL                                          0xB6B8
#define PB6_B9_AUD_I2S_CRC_HB                                       0xB6B9
#define PB6_BA_AUD_I2S_CRC_LB                                       0xB6BA
#define PB6_BB_TO_DAC_CH_SEL                                        0xB6BB
#define PB6_C0_AUD_DEPTH_7                                          0xB6C0
#define PB6_C1_AUD_DEPTH_8                                          0xB6C1
#define PB6_FC_DUMMY_0                                              0xB6FC
#define PB6_FD_DUMMY_1                                              0xB6FD
#define PB6_FE_DUMMY_2                                              0xB6FE
#define PB6_FF_DUMMY_3                                              0xB6FF


//--------------------------------------------------
// D0 Port DisplayPort 1.2 AUX (Page B7)
//--------------------------------------------------
#define PB7_60_DIG_TX_04                                            0xB760
#define PB7_61_AUX_1                                                0xB761
#define PB7_62_AUX_2                                                0xB762
#define PB7_63_AUX_3                                                0xB763
#define PB7_64_AUX_4                                                0xB764
#define PB7_65_AUX_5                                                0xB765
#define PB7_66_AUX_6                                                0xB766
#define PB7_67_DIG_TX_03                                            0xB767
#define PB7_70_AUX_DIG_PHY0                                         0xB770
#define PB7_71_AUX_DIG_PHY1                                         0xB771
#define PB7_72_AUX_DIG_PHY2                                         0xB772
#define PB7_73_AUX_DIG_PHY3                                         0xB773
#define PB7_74_AUX_DIG_PHY4                                         0xB774
#define PB7_75_AUX_DIG_PHY5                                         0xB775
#define PB7_76_AUX_DIG_PHY6                                         0xB776
#define PB7_77_AUX_DIG_PHY7                                         0xB777
#define PB7_78_AUX_DIG_PHY8                                         0xB778
#define PB7_79_AUX_DIG_PHY9                                         0xB779
#define PB7_7A_AUX_DIG_PHYA                                         0xB77A
#define PB7_7B_GDI_POWER_TIMER                                      0xB77B
#define PB7_7C_GDI_POWER_FLAG                                       0xB77C
#define PB7_7D_AUX_DELAY_TIMER                                      0xB77D
#define PB7_7E_AUX_DELAY_FIFO                                       0xB77E
#define PB7_7F_AUX_DEBUG                                            0xB77F
#define PB7_A0_AUX_RESERVE0                                         0xB7A0
#define PB7_A1_AUX_RESERVE1                                         0xB7A1
#define PB7_A2_AUX_RESERVE2                                         0xB7A2
#define PB7_A3_AUX_RESERVE3                                         0xB7A3
#define PB7_A4_AUX_RESERVE4                                         0xB7A4
#define PB7_A5_AUX_RESERVE5                                         0xB7A5
#define PB7_B4_AUX_IRQ_ADDR0_MSB                                    0xB7B4
#define PB7_B5_AUX_IRQ_ADDR0_MSB1                                   0xB7B5
#define PB7_B6_AUX_IRQ_ADDR0_LSB                                    0xB7B6
#define PB7_B7_AUX_IRQ_ADDR1_MSB                                    0xB7B7
#define PB7_B8_AUX_IRQ_ADDR1_MSB1                                   0xB7B8
#define PB7_B9_AUX_IRQ_ADDR1_LSB                                    0xB7B9
#define PB7_BA_AUX_IRQ_ADDR2_MSB                                    0xB7BA
#define PB7_BB_AUX_IRQ_ADDR2_MSB1                                   0xB7BB
#define PB7_BC_AUX_IRQ_ADDR2_LSB                                    0xB7BC
#define PB7_BD_AUX_IRQ_ADDR3_MSB                                    0xB7BD
#define PB7_BE_AUX_IRQ_ADDR3_MSB1                                   0xB7BE
#define PB7_BF_AUX_IRQ_ADDR3_LSB                                    0xB7BF
#define PB7_C0_DPCD_CTRL                                            0xB7C0
#define PB7_C1_DPCD_ADDR_PORT_H                                     0xB7C1
#define PB7_C2_DPCD_ADDR_PORT_M                                     0xB7C2
#define PB7_C3_DPCD_ADDR_PORT_L                                     0xB7C3
#define PB7_C4_DPCD_DATA_PORT                                       0xB7C4
#define PB7_C6_AUX_PHY_DIG2                                         0xB7C6
#define PB7_C7_TP1_OCCR                                             0xB7C7
#define PB7_D0_AUX_MODE_SET                                         0xB7D0
#define PB7_D1_DP_IIC_SET                                           0xB7D1
#define PB7_D2_AUX_RX_CMD                                           0xB7D2
#define PB7_D3_AUX_RX_ADDR_M                                        0xB7D3
#define PB7_D4_AUX_RX_ADDR_L                                        0xB7D4
#define PB7_D5_AUX_RXLEN                                            0xB7D5
#define PB7_D6_AUX_RX_DATA                                          0xB7D6
#define PB7_D7_AUX_TX_CMD                                           0xB7D7
#define PB7_D8_AUX_TX_LEN                                           0xB7D8
#define PB7_D9_AUX_TX_DATA                                          0xB7D9
#define PB7_DA_AUX_FIFO_RST                                         0xB7DA
#define PB7_DB_AUX_STATUS                                           0xB7DB
#define PB7_DC_AUX_IRQ_STATUS                                       0xB7DC
#define PB7_DD_AUX_DPCD_IRQ                                         0xB7DD
#define PB7_DE_AUX_DPCD_IRQ_EN                                      0xB7DE
#define PB7_DF_AUX_IIC_MASTER_CTRL                                  0xB7DF
#define PB7_F0_AUX_TX_TIMER                                         0xB7F0
#define PB7_F1_AUX_TX_TIMER_2                                       0xB7F1
#define PB7_F2_IIC_DEBOUNCE                                         0xB7F2
#define PB7_F3_IIC_SLAVE_ADD                                        0xB7F3
#define PB7_F4_MCUIIC                                               0xB7F4
#define PB7_F5_MCUNA_MSB_1                                          0xB7F5
#define PB7_F6_MCUNA_MSB_2                                          0xB7F6
#define PB7_FA_DUMMY_0                                              0xB7FA
#define PB7_FB_DUMMY_1                                              0xB7FB
#define PB7_FF_TEST_FUNCTION                                        0xB7FF


//--------------------------------------------------
// Audio Power Control (Page C0)
//--------------------------------------------------
#define PC0_0A_AUDIO_POWER_CTRL                                     0xC00A


//--------------------------------------------------
// M1 Scan FIFO Frequency (Page C0)
//--------------------------------------------------
#define PC0_0D_M1_SCAN_FIFO_CLOCK_SELECT                            0xC00D

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
