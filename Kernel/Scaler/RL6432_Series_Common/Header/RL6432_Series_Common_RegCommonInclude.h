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
// ID Code      : RL6432_Series_Common_RegCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Scaling Down Control Port Register Part1 (Page 0)
//--------------------------------------------------
#define _P0_25_PT_00_V_SD_INIT_M1                                   0x00
#define _P0_25_PT_01_V_SD_FACTOR_H_M1                               0x01
#define _P0_25_PT_02_V_SD_FACTOR_M_M1                               0x02
#define _P0_25_PT_03_V_SD_FACTOR_L_M1                               0x03
#define _P0_25_PT_04_H_SD_INIT_M1                                   0x04
#define _P0_25_PT_05_H_SD_FACTOR_H_M1                               0x05
#define _P0_25_PT_06_H_SD_FACTOR_M_M1                               0x06
#define _P0_25_PT_07_H_SD_FACTOR_L_M1                               0x07
#define _P0_25_PT_08_H_SD_ACC_H_M1                                  0x08
#define _P0_25_PT_09_H_SD_ACC_M_M1                                  0x09
#define _P0_25_PT_0A_H_SD_ACC_WIDTH_H_M1                            0x0A
#define _P0_25_PT_0B_H_SD_ACC_WIDTH_L_M1                            0x0B
#define _P0_25_PT_0C_SD_FLAT_WIDTH_H_M1                             0x0C
#define _P0_25_PT_0D_SD_FLAT_WIDTH_L_M1                             0x0D
#define _P0_25_PT_0E_H_SD_ACC_L_M1                                  0x0E


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


//--------------------------------------------------
// Scaling Down Control Port Register Part2 (Page 0)
//--------------------------------------------------
#define _P0_25_PT_36_SD_OUT_WID_M_M1                                0x36
#define _P0_25_PT_37_SD_OUT_WID_L_M1                                0x37
#define _P0_25_PT_38_SD_OUT_LEN_M_M1                                0x38
#define _P0_25_PT_39_SD_OUT_LEN_L_M1                                0x39
#define _P0_25_PT_40_V_SD_INIT_M_M1                                 0x40
#define _P0_25_PT_41_V_SD_INIT_L_M1                                 0x41
#define _P0_25_PT_42_V_SD_FACTOR_L1_M1                              0x42
#define _P0_25_PT_43_H_SD_INIT_M_M1                                 0x43
#define _P0_25_PT_44_H_SD_INIT_L_M_M1                               0x44
#define _P0_25_PT_45_H_SD_INIT_H_M1                                 0x45
#define _P0_25_PT_46_DUMMY_REGISTER1_M1                             0x46
#define _P0_25_PT_47_DUMMY_REGISTER2_M1                             0x47
#define _P0_25_PT_50_SD_BIST_CTRL0_M1                               0x50
#define _P0_25_PT_51_SD_BIST_CTRL1_M1                               0x51


//--------------------------------------------------
// I Domain Pattern Generator Part2 (Page 0)
//--------------------------------------------------
#define _P0_25_PT_62_I_PG_R_CTRL_M1                                 0x62
#define _P0_25_PT_63_I_PG_G_CTRL_M1                                 0x63
#define _P0_25_PT_64_I_PG_B_CTRL_M1                                 0x64
#define _P0_25_PT_65_I_PG_R_INITIAL_M1                              0x65
#define _P0_25_PT_66_I_PG_G_INITIAL_M1                              0x66
#define _P0_25_PT_67_I_PG_B_INITIAL_M1                              0x67
#define _P0_25_PT_68_I_PG_PIXEL_DELTA_H_M1                          0x68
#define _P0_25_PT_69_I_PG_LINE_DELTA_H_M1                           0x69
#define _P0_25_PT_6A_I_PG_PIXEL_STEP_H_M1                           0x6A
#define _P0_25_PT_6B_I_PG_LINE_STEP_H_M1                            0x6B
#define _P0_25_PT_6C_I_PG_DELTA_H_STEP_M_M1                         0x6C
#define _P0_25_PT_6D_I_PG_STEP_L_M1                                 0x6D
#define _P0_25_PT_6E_I_PG_INITIAL_M_STEP_L_M1                       0x6E
#define _P0_25_PT_6F_I_PG_INITIAL_L_CTRL_M1                         0x6F
#define _P0_25_PT_70_I_PG_DELTA_L_M1                                0x70
#define _P0_25_PT_72_I_PG_DDR_TOGGLE_CONTROL_M1                     0x72
#define _P0_25_PT_73_I_PG_DDR_INITIAL_VALUE0_M1                     0x73
#define _P0_25_PT_74_I_PG_DDR_INITIAL_VALUE1_M1                     0x74
#define _P0_25_PT_75_I_PG_DDR_INITIAL_VALUE2_M1                     0x75
#define _P0_25_PT_76_I_PG_DDR_INITIAL_VALUE3_M1                     0x76


//--------------------------------------------------
// Display Format Port Register (Page 0)
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
#define _P0_2B_PT_3A_REQUEST_START_SET                              0x3A
#define _P0_2B_PT_40_EVEN_BIST_CTRL                                 0x40
#define _P0_2B_PT_41_EVEN_BIST_RESULT                               0x41
#define _P0_2B_PT_48_D_DOMAIN_TESTOUT                               0x48
#define _P0_2B_PT_4B_BIST_CLK_RST_EN                                0x4B


//--------------------------------------------------
// FIFO Window Port Register (Page 0)
//--------------------------------------------------
#define _P0_31_PT_00_DISPLAY_READ_WID_BSU_H                         0x00
#define _P0_31_PT_01_DISPLAY_READ_WID_BSU_L                         0x01
#define _P0_31_PT_02_DISPLAY_READ_LEN_BSU_L                         0x02
#define _P0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H                     0x03


//--------------------------------------------------
// Scaling Up Function Port Register (Page 0)
//--------------------------------------------------
#define _P0_34_PT_00_HOR_SCALE_FACTOR_H                             0x00
#define _P0_34_PT_01_HOR_SCALE_FACTOR_M                             0x01
#define _P0_34_PT_02_HOR_SCALE_FACTOR_L                             0x02
#define _P0_34_PT_03_VER_SCALE_FACTOR_H                             0x03
#define _P0_34_PT_04_VER_SCALE_FACTOR_M                             0x04
#define _P0_34_PT_05_VER_SCALE_FACTOR_L                             0x05
#define _P0_34_PT_06_HOR_SCALE_FACTOR_SEG1_H                        0x06
#define _P0_34_PT_07_HOR_SCALE_FACTOR_SEG1_L                        0x07
#define _P0_34_PT_08_HOR_SCALE_FACTOR_SEG2_H                        0x08
#define _P0_34_PT_09_HOR_SCALE_FACTOR_SEG2_L                        0x09
#define _P0_34_PT_0A_HOR_SCALE_FACTOR_SEG3_H                        0x0A
#define _P0_34_PT_0B_HOR_SCALE_FACTOR_SEG3_L                        0x0B
#define _P0_34_PT_0C_HOR_SCALE_FACTOR_DELTA1_H                      0x0C
#define _P0_34_PT_0D_HOR_SCALE_FACTOR_DELTA1_L                      0x0D
#define _P0_34_PT_0E_HOR_SCALE_FACTOR_DELTA2_H                      0x0E
#define _P0_34_PT_0F_HOR_SCALE_FACTOR_DELTA2_L                      0x0F
#define _P0_34_PT_10_HOR_FILTER_COEF_INI                            0x10
#define _P0_34_PT_11_VER_FILTER_COEF_INI                            0x11
#define _P0_34_PT_14_HOR_FILTER_COEF_INI_M                          0x14
#define _P0_34_PT_15_HOR_FILTER_COEF_INI_L                          0x15
#define _P0_34_PT_16_VER_FILTER_COEF_INI_M                          0x16
#define _P0_34_PT_17_VER_FILTER_COEF_INI_L                          0x17
#define _P0_34_PT_18_DUMMY                                          0x18


//--------------------------------------------------
// Sync Processor Port Register Overview (Page 0)
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
// Highlight window Port Register (Page 0)
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
// Contrast & Brightness Port Register (Page 0)
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
#define _P0_65_PT_20_BRI_COE_SETA_L                                 0x20
#define _P0_65_PT_21_CTS_COE_SETA_RG_L                              0x21
#define _P0_65_PT_22_CTS_COE_SETA_B_L                               0x22
#define _P0_65_PT_23_BRI_COE_SETB_L                                 0x23
#define _P0_65_PT_24_CTS_COE_SETB_RG_L                              0x24
#define _P0_65_PT_25_CTS_COE_SETB_B_L                               0x25
#define _P0_65_PT_26_CTS_BRI_SWAP                                   0x26
#define _P0_65_PT_27_CTS_BRI_SET                                    0x27


//--------------------------------------------------
// DDither Control Port Register (Page 0)
//--------------------------------------------------
#define _P0_69_PT_00_D_DITHER_COMMON_SET0                           0x00
#define _P0_69_PT_01_D_DITHER_COMMON_SET1                           0x01
#define _P0_69_PT_02_D_DITHER_COMMON_SET2                           0x02
#define _P0_69_PT_03_D_DITHER_COMMON_SET3                           0x03
#define _P0_69_PT_0D_D_DITHER_COMMON_CTRL2                          0x0D
#define _P0_69_PT_10_THDSET1_MIN_VALUE_THD_H                        0x10
#define _P0_69_PT_11_THDSET1_MIN_VALUE_THD_L                        0x11
#define _P0_69_PT_12_THDSET1_MAX_VALUE_THD_H                        0x12
#define _P0_69_PT_13_THDSET1_MAX_VALUE_THD_L                        0x13
#define _P0_69_PT_16_D_DITHER_THDSET1_CTRL1                         0x16
#define _P0_69_PT_17_D_DITHER_THDSET1_CTRL2                         0x17
#define _P0_69_PT_1A_THDSET2_MIN_VALUE_THD_H                        0x1A
#define _P0_69_PT_1B_THDSET2_MIN_VALUE_THD_L                        0x1B
#define _P0_69_PT_1C_THDSET2_MAX_VALUE_THD_H                        0x1C
#define _P0_69_PT_1D_THDSET2_MAX_VALUE_THD_L                        0x1D
#define _P0_69_PT_20_D_DITHER_THDSET2_CTRL1                         0x20
#define _P0_69_PT_21_D_DITHER_THDSET2_CTRL2                         0x21
#define _P0_69_PT_24_THDSET3_MIN_VALUE_THD_H                        0x24
#define _P0_69_PT_25_THDSET3_MIN_VALUE_THD_L                        0x25
#define _P0_69_PT_26_THDSET3_MAX_VALUE_THD_H                        0x26
#define _P0_69_PT_27_THDSET3_MAX_VALUE_THD_L                        0x27
#define _P0_69_PT_2A_D_DITHER_THDSET3_CTRL1                         0x2A
#define _P0_69_PT_2B_D_DITHER_THDSET3_CTRL2                         0x2B
#define _P0_69_PT_80_D_DITHER_REALIGN_SET_R0                        0x80
#define _P0_69_PT_81_D_DITHER_REALIGN_SET_R1                        0x81
#define _P0_69_PT_82_D_DITHER_REALIGN_SET_R2                        0x82
#define _P0_69_PT_83_D_DITHER_REALIGN_SET_R3                        0x83
#define _P0_69_PT_84_D_DITHER_REALIGN_SET_R4                        0x84
#define _P0_69_PT_85_D_DITHER_REALIGN_SET_R5                        0x85
#define _P0_69_PT_86_D_DITHER_REALIGN_SET_R6                        0x86
#define _P0_69_PT_87_D_DITHER_REALIGN_SET_R7                        0x87
#define _P0_69_PT_88_D_DITHER_REALIGN_SET_R8                        0x88
#define _P0_69_PT_89_D_DITHER_REALIGN_SET_R9                        0x89
#define _P0_69_PT_8A_D_DITHER_REALIGN_SET_R10                       0x8A
#define _P0_69_PT_8B_D_DITHER_REALIGN_SET_R11                       0x8B
#define _P0_69_PT_8C_D_DITHER_REALIGN_SET_R12                       0x8C
#define _P0_69_PT_8D_D_DITHER_REALIGN_SET_R13                       0x8D
#define _P0_69_PT_8E_D_DITHER_REALIGN_SET_R14                       0x8E
#define _P0_69_PT_8F_D_DITHER_REALIGN_SET_R15                       0x8F
#define _P0_69_PT_90_D_DITHER_REALIGN_SET_G0                        0x90
#define _P0_69_PT_91_D_DITHER_REALIGN_SET_G1                        0x91
#define _P0_69_PT_92_D_DITHER_REALIGN_SET_G2                        0x92
#define _P0_69_PT_93_D_DITHER_REALIGN_SET_G3                        0x93
#define _P0_69_PT_94_D_DITHER_REALIGN_SET_G4                        0x94
#define _P0_69_PT_95_D_DITHER_REALIGN_SET_G5                        0x95
#define _P0_69_PT_96_D_DITHER_REALIGN_SET_G6                        0x96
#define _P0_69_PT_97_D_DITHER_REALIGN_SET_G7                        0x97
#define _P0_69_PT_98_D_DITHER_REALIGN_SET_G8                        0x98
#define _P0_69_PT_99_D_DITHER_REALIGN_SET_G9                        0x99
#define _P0_69_PT_9A_D_DITHER_REALIGN_SET_G10                       0x9A
#define _P0_69_PT_9B_D_DITHER_REALIGN_SET_G11                       0x9B
#define _P0_69_PT_9C_D_DITHER_REALIGN_SET_G12                       0x9C
#define _P0_69_PT_9D_D_DITHER_REALIGN_SET_G13                       0x9D
#define _P0_69_PT_9E_D_DITHER_REALIGN_SET_G14                       0x9E
#define _P0_69_PT_9F_D_DITHER_REALIGN_SET_G15                       0x9F
#define _P0_69_PT_A0_D_DITHER_REALIGN_SET_B0                        0xA0
#define _P0_69_PT_A1_D_DITHER_REALIGN_SET_B1                        0xA1
#define _P0_69_PT_A2_D_DITHER_REALIGN_SET_B2                        0xA2
#define _P0_69_PT_A3_D_DITHER_REALIGN_SET_B3                        0xA3
#define _P0_69_PT_A4_D_DITHER_REALIGN_SET_B4                        0xA4
#define _P0_69_PT_A5_D_DITHER_REALIGN_SET_B5                        0xA5
#define _P0_69_PT_A6_D_DITHER_REALIGN_SET_B6                        0xA6
#define _P0_69_PT_A7_D_DITHER_REALIGN_SET_B7                        0xA7
#define _P0_69_PT_A8_D_DITHER_REALIGN_SET_B8                        0xA8
#define _P0_69_PT_A9_D_DITHER_REALIGN_SET_B9                        0xA9
#define _P0_69_PT_AA_D_DITHER_REALIGN_SET_B10                       0xAA
#define _P0_69_PT_AB_D_DITHER_REALIGN_SET_B11                       0xAB
#define _P0_69_PT_AC_D_DITHER_REALIGN_SET_B12                       0xAC
#define _P0_69_PT_AD_D_DITHER_REALIGN_SET_B13                       0xAD
#define _P0_69_PT_AE_D_DITHER_REALIGN_SET_B14                       0xAE
#define _P0_69_PT_AF_D_DITHER_REALIGN_SET_B15                       0xAF
#define _P0_69_PT_B0_D_DITHER_REALIGN_OFFSET0                       0xB0
#define _P0_69_PT_B1_D_DITHER_REALIGN_OFFSET1                       0xB1
#define _P0_69_PT_B2_D_DITHER_REALIGN_OFFSET2                       0xB2
#define _P0_69_PT_B3_D_DITHER_REALIGN_OFFSET3                       0xB3
#define _P0_69_PT_B4_D_DITHER_REALIGN_OFFSET4                       0xB4
#define _P0_69_PT_B5_D_DITHER_REALIGN_OFFSET5                       0xB5
#define _P0_69_PT_B6_D_DITHER_REALIGN_OFFSET6                       0xB6
#define _P0_69_PT_B7_D_DITHER_REALIGN_OFFSET7                       0xB7
#define _P0_69_PT_C0_D_DITHER_LSB_TABLE0                            0xC0
#define _P0_69_PT_C1_D_DITHER_LSB_TABLE1                            0xC1
#define _P0_69_PT_C2_D_DITHER_LSB_TABLE2                            0xC2
#define _P0_69_PT_C3_D_DITHER_LSB_TABLE3                            0xC3
#define _P0_69_PT_C4_D_DITHER_LSB_TABLE4                            0xC4
#define _P0_69_PT_C5_D_DITHER_LSB_TABLE5                            0xC5
#define _P0_69_PT_C6_D_DITHER_LSB_TABLE6                            0xC6
#define _P0_69_PT_C7_D_DITHER_LSB_TABLE7                            0xC7
#define _P0_69_PT_C8_D_DITHER_LSB_TABLE8                            0xC8
#define _P0_69_PT_C9_D_DITHER_LSB_TABLE9                            0xC9
#define _P0_69_PT_CA_D_DITHER_LSB_TABLE10                           0xCA
#define _P0_69_PT_CB_D_DITHER_LSB_TABLE11                           0xCB
#define _P0_69_PT_CC_D_DITHER_LSB_TABLE12                           0xCC
#define _P0_69_PT_CD_D_DITHER_LSB_TABLE13                           0xCD
#define _P0_69_PT_CE_D_DITHER_LSB_TABLE14                           0xCE
#define _P0_69_PT_CF_D_DITHER_LSB_TABLE15                           0xCF


//--------------------------------------------------
// Back ground color Port Register (Page 0)
//--------------------------------------------------
#define _P0_6D_PT_00_BG_COLOR_VALUE_R_M1                            0x00
#define _P0_6D_PT_01_BG_COLOR_VALUE_G_M1                            0x01
#define _P0_6D_PT_02_BG_COLOR_VALUE_B_M1                            0x02
#define _P0_6D_PT_03_BG_COLOR_VALUE_RGB_M1                          0x03


//--------------------------------------------------
// Test Function Port Register (Page 0)
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
#define _P0_8E_PT_0C_TST_CLK_CTRLB                                  0x0C
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
// Digital Filter Port Register Part1 (Page 0)
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


//--------------------------------------------------
// Digital Filter Port Register Part2 (Page 0)
//--------------------------------------------------
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
#define _P0_99_PT_0B_DIGITAL_DUMMY                                  0x0B


//--------------------------------------------------
// I-Domain Color Conversion Port Register (Page 0)
//--------------------------------------------------
#define _P0_9D_PT_00_H00_HIGH_BYTE                                  0x00
#define _P0_9D_PT_01_H00_MIDDLE_BYTE                                0x01
#define _P0_9D_PT_02_H01_HIGH_BYTE                                  0x02
#define _P0_9D_PT_03_H01_MIDDLE_BYTE                                0x03
#define _P0_9D_PT_04_H02_HIGH_BYTE                                  0x04
#define _P0_9D_PT_05_H02_MIDDLE_BYTE                                0x05
#define _P0_9D_PT_06_H10_HIGH_BYTE                                  0x06
#define _P0_9D_PT_07_H10_MIDDLE_BYTE                                0x07
#define _P0_9D_PT_08_H11_HIGH_BYTE                                  0x08
#define _P0_9D_PT_09_H11_MIDDLE_BYTE                                0x09
#define _P0_9D_PT_0A_H12_HIGH_BYTE                                  0x0A
#define _P0_9D_PT_0B_H12_MIDDLE_BYTE                                0x0B
#define _P0_9D_PT_0C_H20_HIGH_BYTE                                  0x0C
#define _P0_9D_PT_0D_H20_MIDDLE_BYTE                                0x0D
#define _P0_9D_PT_0E_H21_HIGH_BYTE                                  0x0E
#define _P0_9D_PT_0F_H21_MIDDLE_BYTE                                0x0F
#define _P0_9D_PT_10_H22_HIGH_BYTE                                  0x10
#define _P0_9D_PT_11_H22_MIDDLE_BYTE                                0x11
#define _P0_9D_PT_12_H00_H01_LOW_BYTE                               0x12
#define _P0_9D_PT_13_H02_H10_LOW_BYTE                               0x13
#define _P0_9D_PT_14_H11_H12_LOW_BYTE                               0x14
#define _P0_9D_PT_15_H20_H21_LOW_BYTE                               0x15
#define _P0_9D_PT_16_H22_LOW_BYTE                                   0x16


//--------------------------------------------------
// DCC Port1 Register (Page 7)
//--------------------------------------------------
#define _P7_CA_PT_00_PORT_PAGE0_NOR_FACTOR_H                        0x00
#define _P7_CA_PT_01_PORT_PAGE0_NOR_FACTOR_M                        0x01
#define _P7_CA_PT_02_PORT_PAGE0_NOR_FACTOR_L                        0x02
#define _P7_CA_PT_03_PORT_PAGE0_BBE_CTRL                            0x03
#define _P7_CA_PT_04_PORT_PAGE0_NFLT_CTRL                           0x04
#define _P7_CA_PT_05_PORT_PAGE0_HIST_CTRL                           0x05
#define _P7_CA_PT_06_PORT_PAGE0_SOFT_CLAMP                          0x06
#define _P7_CA_PT_07_PORT_PAGE0_Y_MAX_LB_H                          0x07
#define _P7_CA_PT_08_PORT_PAGE0_Y_MIN_HB_H                          0x08
#define _P7_CA_PT_09_PORT_PAGE0_SCG_PERIOD                          0x09
#define _P7_CA_PT_0A_PORT_PAGE0_SCG_LB                              0x0A
#define _P7_CA_PT_0B_PORT_PAGE0_SCG_HB                              0x0B
#define _P7_CA_PT_0C_PORT_PAGE0_POPUP_CTRL                          0x0C
#define _P7_CA_PT_0D_PORT_PAGE0_SCG_DIFF                            0x0D
#define _P7_CA_PT_0E_PORT_PAGE0_Y_MAX_VAL_H                         0x0E
#define _P7_CA_PT_0F_PORT_PAGE0_Y_MIN_VAL_H                         0x0F
#define _P7_CA_PT_10_PORT_PAGE0_S0_VALUE                            0x10
#define _P7_CA_PT_11_PORT_PAGE0_S1_VALUE                            0x11
#define _P7_CA_PT_12_PORT_PAGE0_S2_VALUE                            0x12
#define _P7_CA_PT_13_PORT_PAGE0_S3_VALUE                            0x13
#define _P7_CA_PT_14_PORT_PAGE0_S4_VALUE                            0x14
#define _P7_CA_PT_15_PORT_PAGE0_S5_VALUE                            0x15
#define _P7_CA_PT_16_PORT_PAGE0_S6_VALUE                            0x16
#define _P7_CA_PT_17_PORT_PAGE0_YHL_THD                             0x17
#define _P7_CA_PT_18_PORT_PAGE0_BBE_THD_L                           0x18
#define _P7_CA_PT_19_PORT_PAGE0_YNFLT_THD_L                         0x19
#define _P7_CA_PT_1A_PORT_PAGE0_Y_MAX_LB_L                          0x1A
#define _P7_CA_PT_1B_PORT_PAGE0_Y_MIN_HB_L                          0x1B
#define _P7_CA_PT_1C_PORT_PAGE0_Y_MAX_VAL_L                         0x1C
#define _P7_CA_PT_1D_PORT_PAGE0_Y_MIN_VAL_L                         0x1D
#define _P7_CA_PT_1E_PORT_PAGE0_READY_TO_READ                       0x1E


//--------------------------------------------------
// DCC Port2 Register (Page 7)
//--------------------------------------------------
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
#define _P7_CA_PT_10_PORT_PAGE1_Y_BL_BIAS_H                         0x10
#define _P7_CA_PT_11_PORT_PAGE1_Y_WL_BIAS_H                         0x11
#define _P7_CA_PT_12_PORT_PAGE1_SAT_FACTOR                          0x12
#define _P7_CA_PT_13_PORT_PAGE1_BLD_UB_H                            0x13
#define _P7_CA_PT_14_PORT_PAGE1_BLD_LB_H                            0x14
#define _P7_CA_PT_15_PORT_PAGE1_DEV_FACTOR_H                        0x15
#define _P7_CA_PT_16_PORT_PAGE1_BLD_VAL_SEL                         0x16
#define _P7_CA_PT_17_PORT_PAGE1_BLD_VAL_H                           0x17
#define _P7_CA_PT_18_PORT_PAGE1_DEV_VAL_HI                          0x18
#define _P7_CA_PT_19_PORT_PAGE1_DEV_VAL_LO                          0x19
#define _P7_CA_PT_1A_PORT_PAGE1_BLD_VAL_L                           0x1A
#define _P7_CA_PT_1B_PORT_PAGE1_DEF_CRV00_HALF_H                    0x1B
#define _P7_CA_PT_1C_PORT_PAGE1_DEF_CRV00_HALF_L                    0x1C
#define _P7_CA_PT_1D_PORT_PAGE1_DEF_CRV01_L                         0x1D
#define _P7_CA_PT_1E_PORT_PAGE1_DEF_CRV01_HALF_H                    0x1E
#define _P7_CA_PT_1F_PORT_PAGE1_DEF_CRV01_HALF_L                    0x1F
#define _P7_CA_PT_20_PORT_PAGE1_DEF_CRV02_L                         0x20
#define _P7_CA_PT_21_PORT_PAGE1_DEF_CRV02_HALF_H                    0x21
#define _P7_CA_PT_22_PORT_PAGE1_DEF_CRV02_HALF_L                    0x22
#define _P7_CA_PT_23_PORT_PAGE1_DEF_CRV03_L                         0x23
#define _P7_CA_PT_24_PORT_PAGE1_DEF_CRV03_HALF_H                    0x24
#define _P7_CA_PT_25_PORT_PAGE1_DEF_CRV03_HALF_L                    0x25
#define _P7_CA_PT_26_PORT_PAGE1_DEF_CRV04_L                         0x26
#define _P7_CA_PT_27_PORT_PAGE1_DEF_CRV04_HALF_H                    0x27
#define _P7_CA_PT_28_PORT_PAGE1_DEF_CRV04_HALF_L                    0x28
#define _P7_CA_PT_29_PORT_PAGE1_DEF_CRV05_L                         0x29
#define _P7_CA_PT_2A_PORT_PAGE1_DEF_CRV05_HALF_H                    0x2A
#define _P7_CA_PT_2B_PORT_PAGE1_DEF_CRV05_HALF_L                    0x2B
#define _P7_CA_PT_2C_PORT_PAGE1_DEF_CRV06_L                         0x2C
#define _P7_CA_PT_2D_PORT_PAGE1_DEF_CRV06_HALF_H                    0x2D
#define _P7_CA_PT_2E_PORT_PAGE1_DEF_CRV06_HALF_L                    0x2E
#define _P7_CA_PT_2F_PORT_PAGE1_DEF_CRV07_L                         0x2F
#define _P7_CA_PT_30_PORT_PAGE1_DEF_CRV07_HALF_H                    0x30
#define _P7_CA_PT_31_PORT_PAGE1_DEF_CRV07_HALF_L                    0x31
#define _P7_CA_PT_32_PORT_PAGE1_DEF_CRV08_L                         0x32
#define _P7_CA_PT_33_PORT_PAGE1_DEF_CRV08_HALF_H                    0x33
#define _P7_CA_PT_34_PORT_PAGE1_DEF_CRV08_HALF_L                    0x34
#define _P7_CA_PT_35_PORT_PAGE1_DEF_CRV09_L                         0x35
#define _P7_CA_PT_36_PORT_PAGE1_DEF_CRV09_HALF_H                    0x36
#define _P7_CA_PT_37_PORT_PAGE1_DEF_CRV09_HALF_L                    0x37
#define _P7_CA_PT_38_PORT_PAGE1_DEF_CRV10_L                         0x38
#define _P7_CA_PT_39_PORT_PAGE1_DEF_CRV10_HALF_H                    0x39
#define _P7_CA_PT_3A_PORT_PAGE1_DEF_CRV10_HALF_L                    0x3A
#define _P7_CA_PT_3B_PORT_PAGE1_DEF_CRV11_L                         0x3B
#define _P7_CA_PT_3C_PORT_PAGE1_DEF_CRV11_HALF_H                    0x3C
#define _P7_CA_PT_3D_PORT_PAGE1_DEF_CRV11_HALF_L                    0x3D
#define _P7_CA_PT_3E_PORT_PAGE1_DEF_CRV12_L                         0x3E
#define _P7_CA_PT_3F_PORT_PAGE1_DEF_CRV12_HALF_H                    0x3F
#define _P7_CA_PT_40_PORT_PAGE1_DEF_CRV12_HALF_L                    0x40
#define _P7_CA_PT_41_PORT_PAGE1_DEF_CRV13_L                         0x41
#define _P7_CA_PT_42_PORT_PAGE1_DEF_CRV13_HALF_H                    0x42
#define _P7_CA_PT_43_PORT_PAGE1_DEF_CRV13_HALF_L                    0x43
#define _P7_CA_PT_44_PORT_PAGE1_DEF_CRV14_L                         0x44
#define _P7_CA_PT_45_PORT_PAGE1_DEF_CRV14_HALF_H                    0x45
#define _P7_CA_PT_46_PORT_PAGE1_DEF_CRV14_HALF_L                    0x46
#define _P7_CA_PT_47_PORT_PAGE1_DEF_CRV15_L                         0x47
#define _P7_CA_PT_48_PORT_PAGE1_DEF_CRV15_HALF_H                    0x48
#define _P7_CA_PT_49_PORT_PAGE1_DEF_CRV15_HALF_L                    0x49
#define _P7_CA_PT_4A_PORT_PAGE1_DEF_CRV16_L                         0x4A
#define _P7_CA_PT_4B_PORT_PAGE1_Y_BL_BIAS_L                         0x4B
#define _P7_CA_PT_4C_PORT_PAGE1_Y_WL_BIAS_L                         0x4C
#define _P7_CA_PT_4D_PORT_PAGE1_BLD_UB_L                            0x4D
#define _P7_CA_PT_4E_PORT_PAGE1_BLD_LB_L                            0x4E
#define _P7_CA_PT_4F_PORT_PAGE1_DEV_FACTOR_L                        0x4F
#define _P7_CA_PT_50_PORT_PAGE1_BLD_RANGE_L                         0x50
#define _P7_CA_PT_51_PORT_PAGE1_DUMMY                               0x51


//--------------------------------------------------
// DCC Port3 Register (Page 7)
//--------------------------------------------------
#define _P7_CA_PT_8F_PORT_PAGE2_SRAM_INITIAL_VAL                    0x8F


//--------------------------------------------------
// DCC Port4 Register (Page 7)
//--------------------------------------------------
#define _P7_CA_PT_00_PORT_PAGE3_SRAM_BIST                           0x00
#define _P7_CA_PT_01_PORT_PAGE3_SRAM_DRF_BIST                       0x01


//--------------------------------------------------
// ICM Port1 Register (Page 7)
//--------------------------------------------------
#define _P7_CF_PT_00_PORT_SCMN_SATURATION_SET_1                     0x00
#define _P7_CF_PT_01_PORT_SCMN_SATURATION_SET_2                     0x01
#define _P7_CF_PT_02_PORT_SCMN_SATURATION_SET_3                     0x02
#define _P7_CF_PT_03_PORT_SCMN_RBUF_HUE_H                           0x03
#define _P7_CF_PT_04_PORT_SCMN_RBUF_HUE_M                           0x04
#define _P7_CF_PT_05_PORT_SCMN_RWID_RANGE_H                         0x05
#define _P7_CF_PT_06_PORT_SCMN_RWID_RANGE_M                         0x06
#define _P7_CF_PT_07_PORT_SCMN_LWID_RANGE_H                         0x07
#define _P7_CF_PT_08_PORT_SCMN_LWID_RANGE_M                         0x08
#define _P7_CF_PT_09_PORT_SCMN_LBUF_RANGE_H                         0x09
#define _P7_CF_PT_0A_PORT_SCMN_LBUF_RANGE_M                         0x0A
#define _P7_CF_PT_0B_PORT_SCMN_MST_D_DU_H                           0x0B
#define _P7_CF_PT_0C_PORT_SCMN_MST_D_DV_H                           0x0C
#define _P7_CF_PT_0D_PORT_SCMN_MST_C_DU_H                           0x0D
#define _P7_CF_PT_0E_PORT_SCMN_MST_C_DV_H                           0x0E
#define _P7_CF_PT_0F_PORT_SCMN_MST_B_DU_H                           0x0F
#define _P7_CF_PT_10_PORT_SCMN_MST_B_DV_H                           0x10
#define _P7_CF_PT_11_PORT_SCMN_MST_A_DU_H                           0x11
#define _P7_CF_PT_12_PORT_SCMN_MST_A_DV_H                           0x12
#define _P7_CF_PT_13_PORT_SCMN_RWID_D_DU_H                          0x13
#define _P7_CF_PT_14_PORT_SCMN_RWID_D_DV_H                          0x14
#define _P7_CF_PT_15_PORT_SCMN_RWID_C_DU_H                          0x15
#define _P7_CF_PT_16_PORT_SCMN_RWID_C_DV_H                          0x16
#define _P7_CF_PT_17_PORT_SCMN_RWID_B_DU_H                          0x17
#define _P7_CF_PT_18_PORT_SCMN_RWID_B_DV_H                          0x18
#define _P7_CF_PT_19_PORT_SCMN_RWID_A_DU_H                          0x19
#define _P7_CF_PT_1A_PORT_SCMN_RWID_A_DV_H                          0x1A
#define _P7_CF_PT_1B_PORT_SCMN_LWID_D_DU_H                          0x1B
#define _P7_CF_PT_1C_PORT_SCMN_LWID_D_DV_H                          0x1C
#define _P7_CF_PT_1D_PORT_SCMN_LWID_C_DU_H                          0x1D
#define _P7_CF_PT_1E_PORT_SCMN_LWID_C_DV_H                          0x1E
#define _P7_CF_PT_1F_PORT_SCMN_LWID_B_DU_H                          0x1F
#define _P7_CF_PT_20_PORT_SCMN_LWID_B_DV_H                          0x20
#define _P7_CF_PT_21_PORT_SCMN_LWID_A_DU_H                          0x21
#define _P7_CF_PT_22_PORT_SCMN_LWID_A_DV_H                          0x22
#define _P7_CF_PT_23_PORT_SCMN_RBUF_D_DU_H                          0x23
#define _P7_CF_PT_24_PORT_SCMN_RBUF_D_DV_H                          0x24
#define _P7_CF_PT_25_PORT_SCMN_RBUF_C_DU_H                          0x25
#define _P7_CF_PT_26_PORT_SCMN_RBUF_C_DV_H                          0x26
#define _P7_CF_PT_27_PORT_SCMN_RBUF_B_DU_H                          0x27
#define _P7_CF_PT_28_PORT_SCMN_RBUF_B_DV_H                          0x28
#define _P7_CF_PT_29_PORT_SCMN_RBUF_A_DU_H                          0x29
#define _P7_CF_PT_2A_PORT_SCMN_RBUF_A_DV_H                          0x2A
#define _P7_CF_PT_2B_PORT_SCMN_LBUF_D_DU_H                          0x2B
#define _P7_CF_PT_2C_PORT_SCMN_LBUF_D_DV_H                          0x2C
#define _P7_CF_PT_2D_PORT_SCMN_LBUF_C_DU_H                          0x2D
#define _P7_CF_PT_2E_PORT_SCMN_LBUF_C_DV_H                          0x2E
#define _P7_CF_PT_2F_PORT_SCMN_LBUF_B_DU_H                          0x2F
#define _P7_CF_PT_30_PORT_SCMN_LBUF_B_DV_H                          0x30
#define _P7_CF_PT_31_PORT_SCMN_LBUF_A_DU_H                          0x31
#define _P7_CF_PT_32_PORT_SCMN_LBUF_A_DV_H                          0x32
#define _P7_CF_PT_33_PORT_SCMN_BRI_ENABLE                           0x33
#define _P7_CF_PT_34_PORT_SCMN_M_AXIS_DELY_H                        0x34
#define _P7_CF_PT_35_PORT_SCMN_M_AXIS_DELY_M                        0x35
#define _P7_CF_PT_36_PORT_SCMN_R_AXIS_DELY_H                        0x36
#define _P7_CF_PT_37_PORT_SCMN_R_AXIS_DELY_M                        0x37
#define _P7_CF_PT_38_PORT_SCMN_L_AXIS_DELY_H                        0x38
#define _P7_CF_PT_39_PORT_SCMN_L_AXIS_DELY_M                        0x39
#define _P7_CF_PT_3A_PORT_SCMN_RBUF_AXIS_DELY_H                     0x3A
#define _P7_CF_PT_3B_PORT_SCMN_RBUF_AXIS_DELY_M                     0x3B
#define _P7_CF_PT_3C_PORT_SCMN_LBUF_AXIS_DELY_H                     0x3C
#define _P7_CF_PT_3D_PORT_SCMN_LBUF_AXIS_DELY_M                     0x3D
#define _P7_CF_PT_3E_PORT_SCMN_BLOCK_DELY_H                         0x3E
#define _P7_CF_PT_3F_PORT_SCMN_BLOCK_DELY_M                         0x3F
#define _P7_CF_PT_40_PORT_SCMN_MST_DC_DUDV_L                        0x40
#define _P7_CF_PT_41_PORT_SCMN_MST_BA_DUDV_L                        0x41
#define _P7_CF_PT_42_PORT_SCMN_RWID_DC_DUDV_L                       0x42
#define _P7_CF_PT_43_PORT_SCMN_RWID_BA_DUDV_L                       0x43
#define _P7_CF_PT_44_PORT_SCMN_LWID_DC_DUDV_L                       0x44
#define _P7_CF_PT_45_PORT_SCMN_LWID_BA_DUDV_L                       0x45
#define _P7_CF_PT_46_PORT_SCMN_RBUF_DC_DUDV_L                       0x46
#define _P7_CF_PT_47_PORT_SCMN_RBUF_BA_DUDV_L                       0x47
#define _P7_CF_PT_48_PORT_SCMN_LBUF_DC_DUDV_L                       0x48
#define _P7_CF_PT_49_PORT_SCMN_LBUF_BA_DUDV_L                       0x49
#define _P7_CF_PT_4A_PORT_SCMN_SATURATION_SET_4                     0x4A
#define _P7_CF_PT_4B_PORT_SCMN_RBUF_HUE_L                           0x4B
#define _P7_CF_PT_4C_PORT_SCMN_AXIS_DELY1_L                         0x4C
#define _P7_CF_PT_4D_PORT_SCMN_AXIS_DELY0_L                         0x4D


//--------------------------------------------------
// ICM Port2 Register (Page 7)
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
#define _P7_D3_PT_6F_PORT_CMN_MST_00_01_UV_OFFSET_L                 0x6F
#define _P7_D3_PT_70_PORT_CMN_MST_02_03_UV_OFFSET_L                 0x70
#define _P7_D3_PT_71_PORT_CMN_MST_04_05_UV_OFFSET_L                 0x71
#define _P7_D3_PT_72_PORT_CMN_MST_06_07_UV_OFFSET_L                 0x72
#define _P7_D3_PT_73_PORT_CMN_RWID_00_01_UV_OFFSET_L                0x73
#define _P7_D3_PT_74_PORT_CMN_RWID_02_03_UV_OFFSET_L                0x74
#define _P7_D3_PT_75_PORT_CMN_RWID_04_05_UV_OFFSET_L                0x75
#define _P7_D3_PT_76_PORT_CMN_RWID_06_07_UV_OFFSET_L                0x76
#define _P7_D3_PT_77_PORT_CMN_LWID_00_01_UV_OFFSET_L                0x77
#define _P7_D3_PT_78_PORT_CMN_LWID_02_03_UV_OFFSET_L                0x78
#define _P7_D3_PT_79_PORT_CMN_LWID_04_05_UV_OFFSET_L                0x79
#define _P7_D3_PT_7A_PORT_CMN_LWID_06_07_UV_OFFSET_L                0x7A
#define _P7_D3_PT_7B_PORT_CMN_RBUF_00_01_UV_OFFSET_L                0x7B
#define _P7_D3_PT_7C_PORT_CMN_RBUF_02_03_UV_OFFSET_L                0x7C
#define _P7_D3_PT_7D_PORT_CMN_RBUF_04_05_UV_OFFSET_L                0x7D
#define _P7_D3_PT_7E_PORT_CMN_RBUF_06_07_UV_OFFSET_L                0x7E
#define _P7_D3_PT_7F_PORT_CMN_LBUF_00_01_UV_OFFSET_L                0x7F
#define _P7_D3_PT_80_PORT_CMN_LBUF_02_03_UV_OFFSET_L                0x80
#define _P7_D3_PT_81_PORT_CMN_LBUF_04_05_UV_OFFSET_L                0x81
#define _P7_D3_PT_82_PORT_CMN_LBUF_06_07_UV_OFFSET_L                0x82
#define _P7_D3_PT_83_PORT_CMN_MST_WID_UMAX_L                        0x83
#define _P7_D3_PT_84_PORT_CMN_BUFFER_UMAX_L                         0x84
#define _P7_D3_PT_85_PORT_CMN_HUE_SET1_L                            0x85
#define _P7_D3_PT_86_PORT_CMN_HUE_SET0_L                            0x86
#define _P7_D3_PT_87_PORT_CMN_AXIS_DELY_L                           0x87


//--------------------------------------------------
// DCR Port Register (Page 7)
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
#define _P7_D9_PT_2A_DCR_ABOVE_TH_VAL_5                             0x2A
#define _P7_D9_PT_2B_DCR_ABOVE_TH_VAL_0                             0x2B
#define _P7_D9_PT_2C_DCR_HIGH_LV_VAL_R_0                            0x2C
#define _P7_D9_PT_2D_DCR_LOW_LV_VAL_R_0                             0x2D
#define _P7_D9_PT_2E_DCR_HIGH_LV_VAL_G_0                            0x2E
#define _P7_D9_PT_2F_DCR_LOW_LV_VAL_G_0                             0x2F
#define _P7_D9_PT_30_DCR_HIGH_LV_VAL_B_0                            0x30
#define _P7_D9_PT_31_DCR_LOW_LV_VAL_B_0                             0x31
#define _P7_D9_PT_32_DCR_Y_MAX_0                                    0x32
#define _P7_D9_PT_33_DCR_Y_MIN_0                                    0x33
#define _P7_D9_PT_38_DCR_THESHOLD1_0                                0x38
#define _P7_D9_PT_39_DCR_THESHOLD2_0                                0x39


//--------------------------------------------------
// Embedded Timing Controller Port Register (Page 15)
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
#define _P15_A4_PT_10_TC0_VS_MSB                                    0x10
#define _P15_A4_PT_11_TC0_VS_LSB                                    0x11
#define _P15_A4_PT_12_TC0_VE_MSB                                    0x12
#define _P15_A4_PT_13_TC0_VE_LSB                                    0x13
#define _P15_A4_PT_14_TC0_HS_MSB                                    0x14
#define _P15_A4_PT_15_TC0_HS_LSB                                    0x15
#define _P15_A4_PT_16_TC0_HE_MSB                                    0x16
#define _P15_A4_PT_17_TC0_HE_LSB                                    0x17
#define _P15_A4_PT_18_TC0_CTRL                                      0x18
#define _P15_A4_PT_19_TC0_RESERVE                                   0x19
#define _P15_A4_PT_20_TC1_VS_MSB                                    0x20
#define _P15_A4_PT_21_TC1_VS_LSB                                    0x21
#define _P15_A4_PT_22_TC1_VE_MSB                                    0x22
#define _P15_A4_PT_23_TC1_VE_LSB                                    0x23
#define _P15_A4_PT_24_TC1_HS_MSB                                    0x24
#define _P15_A4_PT_25_TC1_HS_LSB                                    0x25
#define _P15_A4_PT_26_TC1_HE_MSB                                    0x26
#define _P15_A4_PT_27_TC1_HE_LSB                                    0x27
#define _P15_A4_PT_28_TC1_CTRL                                      0x28
#define _P15_A4_PT_29_TC1_RESERVE                                   0x29
#define _P15_A4_PT_30_TC2_VS_MSB                                    0x30
#define _P15_A4_PT_31_TC2_VS_LSB                                    0x31
#define _P15_A4_PT_32_TC2_VE_MSB                                    0x32
#define _P15_A4_PT_33_TC2_VE_LSB                                    0x33
#define _P15_A4_PT_34_TC2_HS_MSB                                    0x34
#define _P15_A4_PT_35_TC2_HS_LSB                                    0x35
#define _P15_A4_PT_36_TC2_HE_MSB                                    0x36
#define _P15_A4_PT_37_TC2_HE_LSB                                    0x37
#define _P15_A4_PT_38_TC2_CTRL                                      0x38
#define _P15_A4_PT_39_TC2_RESERVE                                   0x39
#define _P15_A4_PT_40_TC3_VS_MSB                                    0x40
#define _P15_A4_PT_41_TC3_VS_LSB                                    0x41
#define _P15_A4_PT_42_TC3_VE_MSB                                    0x42
#define _P15_A4_PT_43_TC3_VE_LSB                                    0x43
#define _P15_A4_PT_44_TC3_HS_MSB                                    0x44
#define _P15_A4_PT_45_TC3_HS_LSB                                    0x45
#define _P15_A4_PT_46_TC3_HE_MSB                                    0x46
#define _P15_A4_PT_47_TC3_HE_LSB                                    0x47
#define _P15_A4_PT_48_TC3_CTRL                                      0x48
#define _P15_A4_PT_49_TC3_RESERVE                                   0x49
#define _P15_A4_PT_50_TC4_VS_MSB                                    0x50
#define _P15_A4_PT_51_TC4_VS_LSB                                    0x51
#define _P15_A4_PT_52_TC4_VE_MSB                                    0x52
#define _P15_A4_PT_53_TC4_VE_LSB                                    0x53
#define _P15_A4_PT_54_TC4_HS_MSB                                    0x54
#define _P15_A4_PT_55_TC4_HS_LSB                                    0x55
#define _P15_A4_PT_56_TC4_HE_MSB                                    0x56
#define _P15_A4_PT_57_TC4_HE_LSB                                    0x57
#define _P15_A4_PT_58_TC4_CTRL                                      0x58
#define _P15_A4_PT_59_TC4_RESERVE                                   0x59
#define _P15_A4_PT_60_TC5_VS_MSB                                    0x60
#define _P15_A4_PT_61_TC5_VS_LSB                                    0x61
#define _P15_A4_PT_62_TC5_VE_MSB                                    0x62
#define _P15_A4_PT_63_TC5_VE_LSB                                    0x63
#define _P15_A4_PT_64_TC5_HS_MSB                                    0x64
#define _P15_A4_PT_65_TC5_HS_LSB                                    0x65
#define _P15_A4_PT_66_TC5_HE_MSB                                    0x66
#define _P15_A4_PT_67_TC5_HE_LSB                                    0x67
#define _P15_A4_PT_68_TC5_CTRL                                      0x68
#define _P15_A4_PT_69_TC5_RESERVE                                   0x69
#define _P15_A4_PT_70_TC6_VS_MSB                                    0x70
#define _P15_A4_PT_71_TC6_VS_LSB                                    0x71
#define _P15_A4_PT_72_TC6_VE_MSB                                    0x72
#define _P15_A4_PT_73_TC6_VE_LSB                                    0x73
#define _P15_A4_PT_74_TC6_HS_MSB                                    0x74
#define _P15_A4_PT_75_TC6_HS_LSB                                    0x75
#define _P15_A4_PT_76_TC6_HE_MSB                                    0x76
#define _P15_A4_PT_77_TC6_HE_LSB                                    0x77
#define _P15_A4_PT_78_TC6_CTRL                                      0x78
#define _P15_A4_PT_79_TC6_RESERVE                                   0x79
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
#define _P15_A4_PT_B0_TC10_VS_MSB                                   0xB0
#define _P15_A4_PT_B1_TC10_VS_LSB                                   0xB1
#define _P15_A4_PT_B2_TC10_VE_MSB                                   0xB2
#define _P15_A4_PT_B3_TC10_VE_LSB                                   0xB3
#define _P15_A4_PT_B4_TC10_HS_MSB                                   0xB4
#define _P15_A4_PT_B5_TC10_HS_LSB                                   0xB5
#define _P15_A4_PT_B6_TC10_HE_MSB                                   0xB6
#define _P15_A4_PT_B7_TC10_HE_LSB                                   0xB7
#define _P15_A4_PT_B8_TC10_CTRL                                     0xB8
#define _P15_A4_PT_B9_TC10_DOT_MASK                                 0xB9
#define _P15_A4_PT_BA_TC10_RESERVE                                  0xBA
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
// D2 CBUS MAC AD Port (Page 2A)
//--------------------------------------------------
#define _P2A_AD_PT_00_MSC_REG_00                                    0x00
#define _P2A_AD_PT_01_MSC_REG_01                                    0x01
#define _P2A_AD_PT_02_MSC_REG_02                                    0x02
#define _P2A_AD_PT_03_MSC_REG_03                                    0x03
#define _P2A_AD_PT_04_MSC_REG_04                                    0x04
#define _P2A_AD_PT_05_MSC_REG_05                                    0x05
#define _P2A_AD_PT_06_MSC_REG_06                                    0x06
#define _P2A_AD_PT_07_MSC_REG_07                                    0x07
#define _P2A_AD_PT_08_MSC_REG_08                                    0x08
#define _P2A_AD_PT_09_MSC_REG_09                                    0x09
#define _P2A_AD_PT_0A_MSC_REG_0A                                    0x0A
#define _P2A_AD_PT_0B_MSC_REG_0B                                    0x0B
#define _P2A_AD_PT_0C_MSC_REG_0C                                    0x0C
#define _P2A_AD_PT_0D_MSC_REG_0D                                    0x0D
#define _P2A_AD_PT_0E_MSC_REG_0E                                    0x0E
#define _P2A_AD_PT_0F_MSC_REG_0F                                    0x0F
#define _P2A_AD_PT_20_MSC_REG_20                                    0x20
#define _P2A_AD_PT_21_MSC_REG_21                                    0x21
#define _P2A_AD_PT_22_MSC_REG_22                                    0x22
#define _P2A_AD_PT_23_MSC_REG_23                                    0x23
#define _P2A_AD_PT_24_MSC_REG_24                                    0x24
#define _P2A_AD_PT_25_MSC_REG_25                                    0x25
#define _P2A_AD_PT_26_MSC_REG_26                                    0x26
#define _P2A_AD_PT_27_MSC_REG_27                                    0x27
#define _P2A_AD_PT_30_MSC_REG_30                                    0x30
#define _P2A_AD_PT_31_MSC_REG_31                                    0x31
#define _P2A_AD_PT_32_MSC_REG_32                                    0x32
#define _P2A_AD_PT_33_MSC_REG_33                                    0x33
#define _P2A_AD_PT_34_MSC_REG_34                                    0x34
#define _P2A_AD_PT_35_MSC_REG_35                                    0x35
#define _P2A_AD_PT_36_MSC_REG_36                                    0x36
#define _P2A_AD_PT_37_MSC_REG_37                                    0x37
#define _P2A_AD_PT_40_MSC_REG_40                                    0x40
#define _P2A_AD_PT_41_MSC_REG_41                                    0x41
#define _P2A_AD_PT_42_MSC_REG_42                                    0x42
#define _P2A_AD_PT_43_MSC_REG_43                                    0x43
#define _P2A_AD_PT_44_MSC_REG_44                                    0x44
#define _P2A_AD_PT_45_MSC_REG_45                                    0x45
#define _P2A_AD_PT_46_MSC_REG_46                                    0x46
#define _P2A_AD_PT_47_MSC_REG_47                                    0x47
#define _P2A_AD_PT_48_MSC_REG_48                                    0x48
#define _P2A_AD_PT_49_MSC_REG_49                                    0x49
#define _P2A_AD_PT_4A_MSC_REG_4A                                    0x4A
#define _P2A_AD_PT_4B_MSC_REG_4B                                    0x4B
#define _P2A_AD_PT_4C_MSC_REG_4C                                    0x4C
#define _P2A_AD_PT_4D_MSC_REG_4D                                    0x4D
#define _P2A_AD_PT_4E_MSC_REG_4E                                    0x4E
#define _P2A_AD_PT_4F_MSC_REG_4F                                    0x4F
#define _P2A_AD_PT_50_MSC_REG_50                                    0x50
#define _P2A_AD_PT_51_MSC_REG_51                                    0x51
#define _P2A_AD_PT_52_MSC_REG_52                                    0x52
#define _P2A_AD_PT_53_MSC_REG_53                                    0x53
#define _P2A_AD_PT_54_MSC_REG_54                                    0x54
#define _P2A_AD_PT_55_MSC_REG_55                                    0x55
#define _P2A_AD_PT_56_MSC_REG_56                                    0x56
#define _P2A_AD_PT_57_MSC_REG_57                                    0x57
#define _P2A_AD_PT_58_MSC_REG_58                                    0x58
#define _P2A_AD_PT_59_MSC_REG_59                                    0x59
#define _P2A_AD_PT_5A_MSC_REG_5A                                    0x5A
#define _P2A_AD_PT_5B_MSC_REG_5B                                    0x5B
#define _P2A_AD_PT_5C_MSC_REG_5C                                    0x5C
#define _P2A_AD_PT_5D_MSC_REG_5D                                    0x5D
#define _P2A_AD_PT_5E_MSC_REG_5E                                    0x5E
#define _P2A_AD_PT_5F_MSC_REG_5F                                    0x5F


//--------------------------------------------------
// D2 CBUS MAC FC Port (Page 2A)
//--------------------------------------------------
#define _P2A_FC_PT_00_MISC_CTRL_00                                  0x00
#define _P2A_FC_PT_01_MISC_CTRL_01                                  0x01
#define _P2A_FC_PT_02_MISC_CTRL_02                                  0x02
#define _P2A_FC_PT_03_MISC_CTRL_03                                  0x03
#define _P2A_FC_PT_04_MISC_CTRL_04                                  0x04
#define _P2A_FC_PT_08_MISC_CTRL_08                                  0x08
#define _P2A_FC_PT_09_MISC_CTRL_09                                  0x09
#define _P2A_FC_PT_0A_MISC_CTRL_0A                                  0x0A
#define _P2A_FC_PT_0B_MISC_CTRL_0B                                  0x0B
#define _P2A_FC_PT_0C_MISC_CTRL_0C                                  0x0C
#define _P2A_FC_PT_0D_MISC_CTRL_0D                                  0x0D
#define _P2A_FC_PT_0E_MISC_CTRL_0E                                  0x0E
#define _P2A_FC_PT_10_MISC_CTRL_10                                  0x10
#define _P2A_FC_PT_11_MISC_CTRL_11                                  0x11
#define _P2A_FC_PT_12_MISC_CTRL_12                                  0x12
#define _P2A_FC_PT_13_MISC_CTRL_13                                  0x13
#define _P2A_FC_PT_14_MISC_CTRL_14                                  0x14
#define _P2A_FC_PT_15_MISC_CTRL_15                                  0x15
#define _P2A_FC_PT_16_MISC_CTRL_16                                  0x16
#define _P2A_FC_PT_17_MISC_CTRL_17                                  0x17
#define _P2A_FC_PT_18_MISC_CTRL_18                                  0x18
#define _P2A_FC_PT_20_MISC_CTRL_20                                  0x20
#define _P2A_FC_PT_21_MISC_CTRL_21                                  0x21
#define _P2A_FC_PT_22_MISC_CTRL_22                                  0x22
#define _P2A_FC_PT_23_MISC_CTRL_23                                  0x23
#define _P2A_FC_PT_24_MISC_CTRL_24                                  0x24
#define _P2A_FC_PT_25_MISC_CTRL_25                                  0x25
#define _P2A_FC_PT_26_MISC_CTRL_26                                  0x26
#define _P2A_FC_PT_27_MISC_CTRL_27                                  0x27
#define _P2A_FC_PT_30_MISC_CTRL_30                                  0x30
#define _P2A_FC_PT_31_MISC_CTRL_31                                  0x31
#define _P2A_FC_PT_32_MISC_CTRL_32                                  0x32
#define _P2A_FC_PT_40_MISC_CTRL_40                                  0x40
#define _P2A_FC_PT_41_MISC_CTRL_41                                  0x41
#define _P2A_FC_PT_42_MISC_CTRL_42                                  0x42
#define _P2A_FC_PT_45_MISC_CTRL_43                                  0x45
#define _P2A_FC_PT_46_MISC_CTRL_44                                  0x46
#define _P2A_FC_PT_47_MISC_CTRL_45                                  0x47
#define _P2A_FC_PT_48_MISC_CTRL_46                                  0x48
#define _P2A_FC_PT_49_MISC_CTRL_47                                  0x49
#define _P2A_FC_PT_4A_MISC_CTRL_48                                  0x4A
#define _P2A_FC_PT_4B_MISC_CTRL_49                                  0x4B


//--------------------------------------------------
// D3 CBUS MAC AD Port (Page 68)
//--------------------------------------------------
#define _P68_AD_PT_00_MSC_REG_00                                    0x00
#define _P68_AD_PT_01_MSC_REG_01                                    0x01
#define _P68_AD_PT_02_MSC_REG_02                                    0x02
#define _P68_AD_PT_03_MSC_REG_03                                    0x03
#define _P68_AD_PT_04_MSC_REG_04                                    0x04
#define _P68_AD_PT_05_MSC_REG_05                                    0x05
#define _P68_AD_PT_06_MSC_REG_06                                    0x06
#define _P68_AD_PT_07_MSC_REG_07                                    0x07
#define _P68_AD_PT_08_MSC_REG_08                                    0x08
#define _P68_AD_PT_09_MSC_REG_09                                    0x09
#define _P68_AD_PT_0A_MSC_REG_0A                                    0x0A
#define _P68_AD_PT_0B_MSC_REG_0B                                    0x0B
#define _P68_AD_PT_0C_MSC_REG_0C                                    0x0C
#define _P68_AD_PT_0D_MSC_REG_0D                                    0x0D
#define _P68_AD_PT_0E_MSC_REG_0E                                    0x0E
#define _P68_AD_PT_0F_MSC_REG_0F                                    0x0F
#define _P68_AD_PT_20_MSC_REG_20                                    0x20
#define _P68_AD_PT_21_MSC_REG_21                                    0x21
#define _P68_AD_PT_22_MSC_REG_22                                    0x22
#define _P68_AD_PT_23_MSC_REG_23                                    0x23
#define _P68_AD_PT_24_MSC_REG_24                                    0x24
#define _P68_AD_PT_25_MSC_REG_25                                    0x25
#define _P68_AD_PT_26_MSC_REG_26                                    0x26
#define _P68_AD_PT_27_MSC_REG_27                                    0x27
#define _P68_AD_PT_30_MSC_REG_30                                    0x30
#define _P68_AD_PT_31_MSC_REG_31                                    0x31
#define _P68_AD_PT_32_MSC_REG_32                                    0x32
#define _P68_AD_PT_33_MSC_REG_33                                    0x33
#define _P68_AD_PT_34_MSC_REG_34                                    0x34
#define _P68_AD_PT_35_MSC_REG_35                                    0x35
#define _P68_AD_PT_36_MSC_REG_36                                    0x36
#define _P68_AD_PT_37_MSC_REG_37                                    0x37
#define _P68_AD_PT_40_MSC_REG_40                                    0x40
#define _P68_AD_PT_41_MSC_REG_41                                    0x41
#define _P68_AD_PT_42_MSC_REG_42                                    0x42
#define _P68_AD_PT_43_MSC_REG_43                                    0x43
#define _P68_AD_PT_44_MSC_REG_44                                    0x44
#define _P68_AD_PT_45_MSC_REG_45                                    0x45
#define _P68_AD_PT_46_MSC_REG_46                                    0x46
#define _P68_AD_PT_47_MSC_REG_47                                    0x47
#define _P68_AD_PT_48_MSC_REG_48                                    0x48
#define _P68_AD_PT_49_MSC_REG_49                                    0x49
#define _P68_AD_PT_4A_MSC_REG_4A                                    0x4A
#define _P68_AD_PT_4B_MSC_REG_4B                                    0x4B
#define _P68_AD_PT_4C_MSC_REG_4C                                    0x4C
#define _P68_AD_PT_4D_MSC_REG_4D                                    0x4D
#define _P68_AD_PT_4E_MSC_REG_4E                                    0x4E
#define _P68_AD_PT_4F_MSC_REG_4F                                    0x4F
#define _P68_AD_PT_50_MSC_REG_50                                    0x50
#define _P68_AD_PT_51_MSC_REG_51                                    0x51
#define _P68_AD_PT_52_MSC_REG_52                                    0x52
#define _P68_AD_PT_53_MSC_REG_53                                    0x53
#define _P68_AD_PT_54_MSC_REG_54                                    0x54
#define _P68_AD_PT_55_MSC_REG_55                                    0x55
#define _P68_AD_PT_56_MSC_REG_56                                    0x56
#define _P68_AD_PT_57_MSC_REG_57                                    0x57
#define _P68_AD_PT_58_MSC_REG_58                                    0x58
#define _P68_AD_PT_59_MSC_REG_59                                    0x59
#define _P68_AD_PT_5A_MSC_REG_5A                                    0x5A
#define _P68_AD_PT_5B_MSC_REG_5B                                    0x5B
#define _P68_AD_PT_5C_MSC_REG_5C                                    0x5C
#define _P68_AD_PT_5D_MSC_REG_5D                                    0x5D
#define _P68_AD_PT_5E_MSC_REG_5E                                    0x5E
#define _P68_AD_PT_5F_MSC_REG_5F                                    0x5F


//--------------------------------------------------
// D3 CBUS MAC FC Port (Page 68)
//--------------------------------------------------
#define _P68_FC_PT_00_MISC_CTRL_00                                  0x00
#define _P68_FC_PT_01_MISC_CTRL_01                                  0x01
#define _P68_FC_PT_02_MISC_CTRL_02                                  0x02
#define _P68_FC_PT_03_MISC_CTRL_03                                  0x03
#define _P68_FC_PT_04_MISC_CTRL_04                                  0x04
#define _P68_FC_PT_08_MISC_CTRL_08                                  0x08
#define _P68_FC_PT_09_MISC_CTRL_09                                  0x09
#define _P68_FC_PT_0A_MISC_CTRL_0A                                  0x0A
#define _P68_FC_PT_0B_MISC_CTRL_0B                                  0x0B
#define _P68_FC_PT_0C_MISC_CTRL_0C                                  0x0C
#define _P68_FC_PT_0D_MISC_CTRL_0D                                  0x0D
#define _P68_FC_PT_0E_MISC_CTRL_0E                                  0x0E
#define _P68_FC_PT_10_MISC_CTRL_10                                  0x10
#define _P68_FC_PT_11_MISC_CTRL_11                                  0x11
#define _P68_FC_PT_12_MISC_CTRL_12                                  0x12
#define _P68_FC_PT_13_MISC_CTRL_13                                  0x13
#define _P68_FC_PT_14_MISC_CTRL_14                                  0x14
#define _P68_FC_PT_15_MISC_CTRL_15                                  0x15
#define _P68_FC_PT_16_MISC_CTRL_16                                  0x16
#define _P68_FC_PT_17_MISC_CTRL_17                                  0x17
#define _P68_FC_PT_18_MISC_CTRL_18                                  0x18
#define _P68_FC_PT_20_MISC_CTRL_20                                  0x20
#define _P68_FC_PT_21_MISC_CTRL_21                                  0x21
#define _P68_FC_PT_22_MISC_CTRL_22                                  0x22
#define _P68_FC_PT_23_MISC_CTRL_23                                  0x23
#define _P68_FC_PT_24_MISC_CTRL_24                                  0x24
#define _P68_FC_PT_25_MISC_CTRL_25                                  0x25
#define _P68_FC_PT_26_MISC_CTRL_26                                  0x26
#define _P68_FC_PT_27_MISC_CTRL_27                                  0x27
#define _P68_FC_PT_30_MISC_CTRL_30                                  0x30
#define _P68_FC_PT_31_MISC_CTRL_31                                  0x31
#define _P68_FC_PT_32_MISC_CTRL_32                                  0x32
#define _P68_FC_PT_40_MISC_CTRL_40                                  0x40
#define _P68_FC_PT_41_MISC_CTRL_41                                  0x41
#define _P68_FC_PT_42_MISC_CTRL_42                                  0x42
#define _P68_FC_PT_45_MISC_CTRL_43                                  0x45
#define _P68_FC_PT_46_MISC_CTRL_44                                  0x46
#define _P68_FC_PT_47_MISC_CTRL_45                                  0x47
#define _P68_FC_PT_48_MISC_CTRL_46                                  0x48
#define _P68_FC_PT_49_MISC_CTRL_47                                  0x49
#define _P68_FC_PT_4A_MISC_CTRL_48                                  0x4A
#define _P68_FC_PT_4B_MISC_CTRL_49                                  0x4B


//--------------------------------------------------
// D2 Port HDMI2.0 Function SCDC Port Register (Page 71)
//--------------------------------------------------
#define _P71_3A_PT_01_PORT_PAGE71_HDMI_SCDC_01                      0x01
#define _P71_3A_PT_02_PORT_PAGE71_HDMI_SCDC_02                      0x02
#define _P71_3A_PT_10_PORT_PAGE71_HDMI_SCDC_10                      0x10
#define _P71_3A_PT_11_PORT_PAGE71_HDMI_SCDC_11                      0x11
#define _P71_3A_PT_20_PORT_PAGE71_HDMI_SCDC_20                      0x20
#define _P71_3A_PT_21_PORT_PAGE71_HDMI_SCDC_21                      0x21
#define _P71_3A_PT_30_PORT_PAGE71_HDMI_SCDC_30                      0x30
#define _P71_3A_PT_40_PORT_PAGE71_HDMI_SCDC_40                      0x40
#define _P71_3A_PT_41_PORT_PAGE71_HDMI_SCDC_41                      0x41
#define _P71_3A_PT_50_PORT_PAGE71_HDMI_SCDC_50                      0x50
#define _P71_3A_PT_51_PORT_PAGE71_HDMI_SCDC_51                      0x51
#define _P71_3A_PT_52_PORT_PAGE71_HDMI_SCDC_52                      0x52
#define _P71_3A_PT_53_PORT_PAGE71_HDMI_SCDC_53                      0x53
#define _P71_3A_PT_54_PORT_PAGE71_HDMI_SCDC_54                      0x54
#define _P71_3A_PT_55_PORT_PAGE71_HDMI_SCDC_55                      0x55
#define _P71_3A_PT_56_PORT_PAGE71_HDMI_SCDC_56                      0x56
#define _P71_3A_PT_C0_PORT_PAGE71_HDMI_SCDC_C0                      0xC0
#define _P71_3A_PT_D0_PORT_PAGE71_HDMI_SCDC_D0                      0xD0
#define _P71_3A_PT_D1_PORT_PAGE71_HDMI_SCDC_D1                      0xD1
#define _P71_3A_PT_D2_PORT_PAGE71_HDMI_SCDC_D2                      0xD2
#define _P71_3A_PT_D3_PORT_PAGE71_HDMI_SCDC_D3                      0xD3
#define _P71_3A_PT_D4_PORT_PAGE71_HDMI_SCDC_D4                      0xD4
#define _P71_3A_PT_D5_PORT_PAGE71_HDMI_SCDC_D5                      0xD5
#define _P71_3A_PT_D6_PORT_PAGE71_HDMI_SCDC_D6                      0xD6
#define _P71_3A_PT_D7_PORT_PAGE71_HDMI_SCDC_D7                      0xD7
#define _P71_3A_PT_D8_PORT_PAGE71_HDMI_SCDC_D8                      0xD8
#define _P71_3A_PT_D9_PORT_PAGE71_HDMI_SCDC_D9                      0xD9
#define _P71_3A_PT_DA_PORT_PAGE71_HDMI_SCDC_DA                      0xDA
#define _P71_3A_PT_DB_PORT_PAGE71_HDMI_SCDC_DB                      0xDB
#define _P71_3A_PT_DC_PORT_PAGE71_HDMI_SCDC_DC                      0xDC
#define _P71_3A_PT_DD_PORT_PAGE71_HDMI_SCDC_DD                      0xDD
#define _P71_3A_PT_DE_PORT_PAGE71_HDMI_SCDC_DE                      0xDE
#define _P71_3A_PT_DF_PORT_PAGE71_HDMI_SCDC_DF                      0xDF
#define _P71_3A_PT_E0_PORT_PAGE71_HDMI_SCDC_E0                      0xE0
#define _P71_3A_PT_E1_PORT_PAGE71_HDMI_SCDC_E1                      0xE1
#define _P71_3A_PT_E2_PORT_PAGE71_HDMI_SCDC_E2                      0xE2
#define _P71_3A_PT_E3_PORT_PAGE71_HDMI_SCDC_E3                      0xE3
#define _P71_3A_PT_E4_PORT_PAGE71_HDMI_SCDC_E4                      0xE4
#define _P71_3A_PT_E5_PORT_PAGE71_HDMI_SCDC_E5                      0xE5
#define _P71_3A_PT_E6_PORT_PAGE71_HDMI_SCDC_E6                      0xE6
#define _P71_3A_PT_E7_PORT_PAGE71_HDMI_SCDC_E7                      0xE7
#define _P71_3A_PT_E8_PORT_PAGE71_HDMI_SCDC_E8                      0xE8
#define _P71_3A_PT_E9_PORT_PAGE71_HDMI_SCDC_E9                      0xE9
#define _P71_3A_PT_EA_PORT_PAGE71_HDMI_SCDC_EA                      0xEA
#define _P71_3A_PT_EB_PORT_PAGE71_HDMI_SCDC_EB                      0xEB
#define _P71_3A_PT_EC_PORT_PAGE71_HDMI_SCDC_EC                      0xEC
#define _P71_3A_PT_ED_PORT_PAGE71_HDMI_SCDC_ED                      0xED
#define _P71_3A_PT_EE_PORT_PAGE71_HDMI_SCDC_EE                      0xEE
#define _P71_3A_PT_EF_PORT_PAGE71_HDMI_SCDC_EF                      0xEF
#define _P71_3A_PT_F0_PORT_PAGE71_HDMI_SCDC_F0                      0xF0
#define _P71_3A_PT_F1_PORT_PAGE71_HDMI_SCDC_F1                      0xF1
#define _P71_3A_PT_F2_PORT_PAGE71_HDMI_SCDC_F2                      0xF2
#define _P71_3A_PT_F3_PORT_PAGE71_HDMI_SCDC_F3                      0xF3
#define _P71_3A_PT_F4_PORT_PAGE71_HDMI_SCDC_F4                      0xF4
#define _P71_3A_PT_F5_PORT_PAGE71_HDMI_SCDC_F5                      0xF5
#define _P71_3A_PT_F6_PORT_PAGE71_HDMI_SCDC_F6                      0xF6
#define _P71_3A_PT_F7_PORT_PAGE71_HDMI_SCDC_F7                      0xF7
#define _P71_3A_PT_F8_PORT_PAGE71_HDMI_SCDC_F8                      0xF8
#define _P71_3A_PT_F9_PORT_PAGE71_HDMI_SCDC_F9                      0xF9
#define _P71_3A_PT_FA_PORT_PAGE71_HDMI_SCDC_FA                      0xFA
#define _P71_3A_PT_FB_PORT_PAGE71_HDMI_SCDC_FB                      0xFB
#define _P71_3A_PT_FC_PORT_PAGE71_HDMI_SCDC_FC                      0xFC
#define _P71_3A_PT_FD_PORT_PAGE71_HDMI_SCDC_FD                      0xFD
#define _P71_3A_PT_FE_PORT_PAGE71_HDMI_SCDC_FE                      0xFE
#define _P71_3A_PT_FF_PORT_PAGE71_HDMI_SCDC_FF                      0xFF


//--------------------------------------------------
// D2 Port Overall HDMI System Function Block HDCP Port Register (Page 71)
//--------------------------------------------------
#define _P71_C4_PT_00_PORT_PAGE71_BKSV0                             0x00
#define _P71_C4_PT_01_PORT_PAGE71_BKSV1                             0x01
#define _P71_C4_PT_02_PORT_PAGE71_BKSV2                             0x02
#define _P71_C4_PT_03_PORT_PAGE71_BKSV3                             0x03
#define _P71_C4_PT_04_PORT_PAGE71_BKSV4                             0x04
#define _P71_C4_PT_08_PORT_PAGE71_RI0                               0x08
#define _P71_C4_PT_09_PORT_PAGE71_RI1                               0x09
#define _P71_C4_PT_0A_PORT_PAGE71_PJ                                0x0A
#define _P71_C4_PT_10_PORT_PAGE71_AKSV0                             0x10
#define _P71_C4_PT_11_PORT_PAGE71_AKSV1                             0x11
#define _P71_C4_PT_12_PORT_PAGE71_AKSV2                             0x12
#define _P71_C4_PT_13_PORT_PAGE71_AKSV3                             0x13
#define _P71_C4_PT_14_PORT_PAGE71_AKSV4                             0x14
#define _P71_C4_PT_15_PORT_PAGE71_AINFO                             0x15
#define _P71_C4_PT_18_PORT_PAGE71_AN0                               0x18
#define _P71_C4_PT_19_PORT_PAGE71_AN1                               0x19
#define _P71_C4_PT_1A_PORT_PAGE71_AN2                               0x1A
#define _P71_C4_PT_1B_PORT_PAGE71_AN3                               0x1B
#define _P71_C4_PT_1C_PORT_PAGE71_AN4                               0x1C
#define _P71_C4_PT_1D_PORT_PAGE71_AN5                               0x1D
#define _P71_C4_PT_1E_PORT_PAGE71_AN6                               0x1E
#define _P71_C4_PT_1F_PORT_PAGE71_AN7                               0x1F
#define _P71_C4_PT_40_PORT_PAGE71_BCAPS                             0x40
#define _P71_C4_PT_42_PORT_PAGE71_BSTATUS                           0x42
#define _P71_C4_PT_43_PORT_PAGE71_KSV_FIFO                          0x43
#define _P71_C4_PT_50_PORT_PAGE71_HDCP2_VER                         0x50
#define _P71_C4_PT_60_PORT_PAGE71_HDCP2_WR_MSG                      0x60
#define _P71_C4_PT_70_PORT_PAGE71_HDCP2_STATUS1                     0x70
#define _P71_C4_PT_71_PORT_PAGE71_HDCP2_STATUS2                     0x71
#define _P71_C4_PT_80_PORT_PAGE71_HDCP2_RDMSG                       0x80
#define _P71_C4_PT_C0_PORT_PAGE71_HDCP_FCR                          0xC0
#define _P71_C4_PT_C1_PORT_PAGE71_HDCP_SIR                          0xC1
#define _P71_C4_PT_C2_PORT_PAGE71_HDCP_SLAVE_ADD                    0xC2


//--------------------------------------------------
// D2 Port Overall HDMI System Function Block Video Port Register (Page 71)
//--------------------------------------------------
#define _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR                          0x00
#define _P71_CA_PT_01_PORT_PAGE71_HDMI_N_VAL                        0x01
#define _P71_CA_PT_02_PORT_PAGE71_HDMI_BCHCR                        0x02
#define _P71_CA_PT_03_PORT_PAGE71_HDMI_AFCR                         0x03
#define _P71_CA_PT_04_PORT_PAGE71_HDMI_AFSR                         0x04
#define _P71_CA_PT_05_PORT_PAGE71_HDMI_MAGCR1                       0x05
#define _P71_CA_PT_06_PORT_PAGE71_HDMI_MAGCR2                       0x06
#define _P71_CA_PT_07_PORT_PAGE71_HDMI_MAG_M_FINAL                  0x07
#define _P71_CA_PT_08_PORT_PAGE71_HDMI_MAG_L_FINAL                  0x08
#define _P71_CA_PT_09_PORT_PAGE71_HDMI_MAG_R_FINAL                  0x09
#define _P71_CA_PT_0A_PORT_PAGE71_AUDIO_LD_P_TIME_M                 0x0A
#define _P71_CA_PT_0B_PORT_PAGE71_AUDIO_LD_P_TIME_N                 0x0B
#define _P71_CA_PT_0C_PORT_PAGE71_ZCD_CTRL                          0x0C
#define _P71_CA_PT_0D_PORT_PAGE71_ZCD_TIMEOUT                       0x0D
#define _P71_CA_PT_0E_PORT_PAGE71_ZCD_STATUS                        0x0E
#define _P71_CA_PT_10_PORT_PAGE71_HDMI_CMCR                         0x10
#define _P71_CA_PT_11_PORT_PAGE71_HDMI_MCAPR                        0x11
#define _P71_CA_PT_12_PORT_PAGE71_HDMI_SCAPR                        0x12
#define _P71_CA_PT_13_PORT_PAGE71_HDMI_DCAPR0                       0x13
#define _P71_CA_PT_14_PORT_PAGE71_HDMI_DCAPR1                       0x14
#define _P71_CA_PT_15_PORT_PAGE71_HDMI_PSCR                         0x15
#define _P71_CA_PT_16_PORT_PAGE71_HDMI_FDDR                         0x16
#define _P71_CA_PT_17_PORT_PAGE71_HDMI_FDDF                         0x17
#define _P71_CA_PT_18_PORT_PAGE71_HDMI_MFDDR                        0x18
#define _P71_CA_PT_19_PORT_PAGE71_HDMI_MFDDF                        0x19
#define _P71_CA_PT_1A_PORT_PAGE71_HDMI_FTR                          0x1A
#define _P71_CA_PT_1B_PORT_PAGE71_HDMI_FBR                          0x1B
#define _P71_CA_PT_1C_PORT_PAGE71_HDMI_ICPSNCR0                     0x1C
#define _P71_CA_PT_1D_PORT_PAGE71_HDMI_ICPSNCR1                     0x1D
#define _P71_CA_PT_1E_PORT_PAGE71_HDMI_PCPSNCR0                     0x1E
#define _P71_CA_PT_1F_PORT_PAGE71_HDMI_PCPSNCR1                     0x1F
#define _P71_CA_PT_20_PORT_PAGE71_HDMI_ICTPSR0                      0x20
#define _P71_CA_PT_21_PORT_PAGE71_HDMI_ICTPSR1                      0x21
#define _P71_CA_PT_22_PORT_PAGE71_HDMI_PCTPSR0                      0x22
#define _P71_CA_PT_23_PORT_PAGE71_HDMI_PCTPSR1                      0x23
#define _P71_CA_PT_24_PORT_PAGE71_HDMI_ICBPSR0                      0x24
#define _P71_CA_PT_25_PORT_PAGE71_HDMI_ICBPSR1                      0x25
#define _P71_CA_PT_26_PORT_PAGE71_HDMI_PCBPSR0                      0x26
#define _P71_CA_PT_27_PORT_PAGE71_HDMI_PCBPSR1                      0x27
#define _P71_CA_PT_28_PORT_PAGE71_HDMI_NTX1024TR0                   0x28
#define _P71_CA_PT_29_PORT_PAGE71_HDMI_NTX1024TR1                   0x29
#define _P71_CA_PT_2A_PORT_PAGE71_HDMI_STBPR                        0x2A
#define _P71_CA_PT_2B_PORT_PAGE71_HDMI_NCPER                        0x2B
#define _P71_CA_PT_2C_PORT_PAGE71_HDMI_PETR                         0x2C
#define _P71_CA_PT_2D_PORT_PAGE71_HDMI_AAPNR                        0x2D
#define _P71_CA_PT_2E_PORT_PAGE71_HDMI_APDMCR                       0x2E
#define _P71_CA_PT_30_PORT_PAGE71_HDMI_AVMCR                        0x30
#define _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0                        0x31
#define _P71_CA_PT_32_PORT_PAGE71_HDMI_WDCR1                        0x32
#define _P71_CA_PT_33_PORT_PAGE71_HDMI_WDCR2                        0x33
#define _P71_CA_PT_34_PORT_PAGE71_HDMI_DBCR                         0x34
#define _P71_CA_PT_35_PORT_PAGE71_HDMI_APTMCR0                      0x35
#define _P71_CA_PT_36_PORT_PAGE71_HDMI_APTMCR1                      0x36
#define _P71_CA_PT_38_PORT_PAGE71_HDMI_DPCR0                        0x38
#define _P71_CA_PT_39_PORT_PAGE71_HDMI_DPCR1                        0x39
#define _P71_CA_PT_3A_PORT_PAGE71_HDMI_DPCR2                        0x3A
#define _P71_CA_PT_3B_PORT_PAGE71_HDMI_DPCR3                        0x3B
#define _P71_CA_PT_3C_PORT_PAGE71_HDMI_SUMCM                        0x3C
#define _P71_CA_PT_3D_PORT_PAGE71_HDMI_SUMCL                        0x3D
#define _P71_CA_PT_3E_PORT_PAGE71_DPLL_M_N_MSB                      0x3E
#define _P71_CA_PT_3F_PORT_PAGE71_DPLL_LDO                          0x3F
#define _P71_CA_PT_40_PORT_PAGE71_HDMI_AWDSR                        0x40
#define _P71_CA_PT_41_PORT_PAGE71_HDMI_VWDSR                        0x41
#define _P71_CA_PT_42_PORT_PAGE71_HDMI_PAMICR                       0x42
#define _P71_CA_PT_43_PORT_PAGE71_HDMI_PTRSV0                       0x43
#define _P71_CA_PT_44_PORT_PAGE71_HDMI_PTRSV1                       0x44
#define _P71_CA_PT_45_PORT_PAGE71_HDMI_PVGCR0                       0x45
#define _P71_CA_PT_46_PORT_PAGE71_HDMI_PVGCR1                       0x46
#define _P71_CA_PT_47_PORT_PAGE71_HDMI_PVGCR2                       0x47
#define _P71_CA_PT_48_PORT_PAGE71_HDMI_PVSR0                        0x48
#define _P71_CA_PT_49_PORT_PAGE71_HDMI_PVSR1                        0x49
#define _P71_CA_PT_4A_PORT_PAGE71_HDMI_PVSR2                        0x4A
#define _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR                          0x50
#define _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR                        0x51
#define _P71_CA_PT_52_PORT_PAGE71_HDMI_ACRSR0                       0x52
#define _P71_CA_PT_53_PORT_PAGE71_HDMI_ACRSR1                       0x53
#define _P71_CA_PT_54_PORT_PAGE71_HDMI_ACRSR2                       0x54
#define _P71_CA_PT_55_PORT_PAGE71_HDMI_ACRSR3                       0x55
#define _P71_CA_PT_56_PORT_PAGE71_HDMI_ACRSR4                       0x56
#define _P71_CA_PT_57_PORT_PAGE71_HDMI_ACS0                         0x57
#define _P71_CA_PT_58_PORT_PAGE71_HDMI_ACS1                         0x58
#define _P71_CA_PT_59_PORT_PAGE71_HDMI_ACS2                         0x59
#define _P71_CA_PT_5A_PORT_PAGE71_HDMI_ACS3                         0x5A
#define _P71_CA_PT_5B_PORT_PAGE71_HDMI_ACS4                         0x5B
#define _P71_CA_PT_60_PORT_PAGE71_HDMI_INTCR                        0x60
#define _P71_CA_PT_61_PORT_PAGE71_HDMI_ALCR                         0x61
#define _P71_CA_PT_62_PORT_PAGE71_HDMI_AOCR                         0x62
#define _P71_CA_PT_63_PORT_PAGE71_HDMI_PEAC1                        0x63
#define _P71_CA_PT_64_PORT_PAGE71_HDMI_PEAC2                        0x64
#define _P71_CA_PT_70_PORT_PAGE71_HDMI_BCSR                         0x70
#define _P71_CA_PT_71_PORT_PAGE71_HDMI_ASR0                         0x71
#define _P71_CA_PT_72_PORT_PAGE71_HDMI_ASR1                         0x72
#define _P71_CA_PT_80_PORT_PAGE71_HDMI_DPC_SET0                     0x80
#define _P71_CA_PT_81_PORT_PAGE71_HDMI_DPC_SET1                     0x81
#define _P71_CA_PT_82_PORT_PAGE71_HDMI_DPC_SET2                     0x82
#define _P71_CA_PT_83_PORT_PAGE71_HDMI_DPC_SET3                     0x83
#define _P71_CA_PT_84_PORT_PAGE71_HDMI_DET_0                        0x84
#define _P71_CA_PT_85_PORT_PAGE71_HDMI_DET_1                        0x85
#define _P71_CA_PT_86_PORT_PAGE71_HDMI_DET_2                        0x86
#define _P71_CA_PT_87_PORT_PAGE71_HDMI_DET_3                        0x87
#define _P71_CA_PT_88_PORT_PAGE71_HDMI_DET_4                        0x88
#define _P71_CA_PT_8A_PORT_PAGE71_AUDIO_FREQDET                     0x8A
#define _P71_CA_PT_8B_PORT_PAGE71_AUDIO_FREQ_RESULT                 0x8B
#define _P71_CA_PT_8C_PORT_PAGE71_AUDIO_FREQ_RESULT_M               0x8C
#define _P71_CA_PT_8D_PORT_PAGE71_AUDIO_FREQ_RESULT_L               0x8D
#define _P71_CA_PT_8E_PORT_PAGE71_XTAL_DIV                          0x8E
#define _P71_CA_PT_8F_PORT_PAGE71_TH0                               0x8F
#define _P71_CA_PT_90_PORT_PAGE71_TH1                               0x90
#define _P71_CA_PT_91_PORT_PAGE71_TH2                               0x91
#define _P71_CA_PT_92_PORT_PAGE71_TH3                               0x92
#define _P71_CA_PT_93_PORT_PAGE71_TH4                               0x93
#define _P71_CA_PT_94_PORT_PAGE71_TH5                               0x94
#define _P71_CA_PT_95_PORT_PAGE71_PRESET_S_CODE0                    0x95
#define _P71_CA_PT_96_PORT_PAGE71_PRESET_S_CODE1                    0x96
#define _P71_CA_PT_97_PORT_PAGE71_PRESET_S_CODE2                    0x97
#define _P71_CA_PT_98_PORT_PAGE71_PRESET_S2_CODE                    0x98
#define _P71_CA_PT_99_PORT_PAGE71_PRESET_D_CODE_0                   0x99
#define _P71_CA_PT_9A_PORT_PAGE71_PRESET_D_CODE_1                   0x9A
#define _P71_CA_PT_9B_PORT_PAGE71_PRESET_D_CODE_2                   0x9B
#define _P71_CA_PT_9C_PORT_PAGE71_PRESET_D_CODE_3                   0x9C
#define _P71_CA_PT_9D_PORT_PAGE71_PRESET_D_CODE_4                   0x9D
#define _P71_CA_PT_9E_PORT_PAGE71_PRESET_D_CODE_5                   0x9E
#define _P71_CA_PT_9F_PORT_PAGE71_PRESET_AFSM_MOD                   0x9F
#define _P71_CA_PT_A4_PORT_PAGE71_HDMI_PTRSV_2                      0xA4
#define _P71_CA_PT_A5_PORT_PAGE71_HDMI_PTRSV_3                      0xA5
#define _P71_CA_PT_A6_PORT_PAGE71_HDMI_PARSV                        0xA6
#define _P71_CA_PT_A7_PORT_PAGE71_HDMI_GPVS_0                       0xA7
#define _P71_CA_PT_A8_PORT_PAGE71_HDMI_PVSR_3                       0xA8
#define _P71_CA_PT_A9_PORT_PAGE71_HDMI_PVSR_4                       0xA9
#define _P71_CA_PT_AA_PORT_PAGE71_HDMI_PVGCR3                       0xAA
#define _P71_CA_PT_AB_PORT_PAGE71_HDMI_PVGCR4                       0xAB
#define _P71_CA_PT_AE_PORT_PAGE71_HDMI_GDI_TEST_FUNC                0xAE
#define _P71_CA_PT_AF_PORT_PAGE71_HDMI_BED_FUNC_0                   0xAF
#define _P71_CA_PT_B0_PORT_PAGE71_HDMI_BED_FUNC_1                   0xB0
#define _P71_CA_PT_B1_PORT_PAGE71_HDMI_BED_FUNC_2                   0xB1
#define _P71_CA_PT_B2_PORT_PAGE71_HDMI_BED_FUNC_3                   0xB2
#define _P71_CA_PT_B3_PORT_PAGE71_HDMI_BED_FUNC_4                   0xB3
#define _P71_CA_PT_B4_PORT_PAGE71_HDMI_BED_FUNC_5                   0xB4
#define _P71_CA_PT_B5_PORT_PAGE71_HDMI_BED_FUNC_6                   0xB5
#define _P71_CA_PT_B6_PORT_PAGE71_HDMI_BED_FUNC_7                   0xB6
#define _P71_CA_PT_B7_PORT_PAGE71_HDMI_BED_FUNC_8                   0xB7
#define _P71_CA_PT_B8_PORT_PAGE71_HDMI_BED_FUNC_9                   0xB8


//--------------------------------------------------
// D3 Port HDMI2.0 Function SCDC Port Register (Page 72)
//--------------------------------------------------
#define _P72_3A_PT_01_PORT_PAGE72_HDMI_SCDC_01                      0x01
#define _P72_3A_PT_02_PORT_PAGE72_HDMI_SCDC_02                      0x02
#define _P72_3A_PT_10_PORT_PAGE72_HDMI_SCDC_10                      0x10
#define _P72_3A_PT_11_PORT_PAGE72_HDMI_SCDC_11                      0x11
#define _P72_3A_PT_20_PORT_PAGE72_HDMI_SCDC_20                      0x20
#define _P72_3A_PT_21_PORT_PAGE72_HDMI_SCDC_21                      0x21
#define _P72_3A_PT_30_PORT_PAGE72_HDMI_SCDC_30                      0x30
#define _P72_3A_PT_40_PORT_PAGE72_HDMI_SCDC_40                      0x40
#define _P72_3A_PT_41_PORT_PAGE72_HDMI_SCDC_41                      0x41
#define _P72_3A_PT_50_PORT_PAGE72_HDMI_SCDC_50                      0x50
#define _P72_3A_PT_51_PORT_PAGE72_HDMI_SCDC_51                      0x51
#define _P72_3A_PT_52_PORT_PAGE72_HDMI_SCDC_52                      0x52
#define _P72_3A_PT_53_PORT_PAGE72_HDMI_SCDC_53                      0x53
#define _P72_3A_PT_54_PORT_PAGE72_HDMI_SCDC_54                      0x54
#define _P72_3A_PT_55_PORT_PAGE72_HDMI_SCDC_55                      0x55
#define _P72_3A_PT_56_PORT_PAGE72_HDMI_SCDC_56                      0x56
#define _P72_3A_PT_C0_PORT_PAGE72_HDMI_SCDC_C0                      0xC0
#define _P72_3A_PT_D0_PORT_PAGE72_HDMI_SCDC_D0                      0xD0
#define _P72_3A_PT_D1_PORT_PAGE72_HDMI_SCDC_D1                      0xD1
#define _P72_3A_PT_D2_PORT_PAGE72_HDMI_SCDC_D2                      0xD2
#define _P72_3A_PT_D3_PORT_PAGE72_HDMI_SCDC_D3                      0xD3
#define _P72_3A_PT_D4_PORT_PAGE72_HDMI_SCDC_D4                      0xD4
#define _P72_3A_PT_D5_PORT_PAGE72_HDMI_SCDC_D5                      0xD5
#define _P72_3A_PT_D6_PORT_PAGE72_HDMI_SCDC_D6                      0xD6
#define _P72_3A_PT_D7_PORT_PAGE72_HDMI_SCDC_D7                      0xD7
#define _P72_3A_PT_D8_PORT_PAGE72_HDMI_SCDC_D8                      0xD8
#define _P72_3A_PT_D9_PORT_PAGE72_HDMI_SCDC_D9                      0xD9
#define _P72_3A_PT_DA_PORT_PAGE72_HDMI_SCDC_DA                      0xDA
#define _P72_3A_PT_DB_PORT_PAGE72_HDMI_SCDC_DB                      0xDB
#define _P72_3A_PT_DC_PORT_PAGE72_HDMI_SCDC_DC                      0xDC
#define _P72_3A_PT_DD_PORT_PAGE72_HDMI_SCDC_DD                      0xDD
#define _P72_3A_PT_DE_PORT_PAGE72_HDMI_SCDC_DE                      0xDE
#define _P72_3A_PT_DF_PORT_PAGE72_HDMI_SCDC_DF                      0xDF
#define _P72_3A_PT_E0_PORT_PAGE72_HDMI_SCDC_E0                      0xE0
#define _P72_3A_PT_E1_PORT_PAGE72_HDMI_SCDC_E1                      0xE1
#define _P72_3A_PT_E2_PORT_PAGE72_HDMI_SCDC_E2                      0xE2
#define _P72_3A_PT_E3_PORT_PAGE72_HDMI_SCDC_E3                      0xE3
#define _P72_3A_PT_E4_PORT_PAGE72_HDMI_SCDC_E4                      0xE4
#define _P72_3A_PT_E5_PORT_PAGE72_HDMI_SCDC_E5                      0xE5
#define _P72_3A_PT_E6_PORT_PAGE72_HDMI_SCDC_E6                      0xE6
#define _P72_3A_PT_E7_PORT_PAGE72_HDMI_SCDC_E7                      0xE7
#define _P72_3A_PT_E8_PORT_PAGE72_HDMI_SCDC_E8                      0xE8
#define _P72_3A_PT_E9_PORT_PAGE72_HDMI_SCDC_E9                      0xE9
#define _P72_3A_PT_EA_PORT_PAGE72_HDMI_SCDC_EA                      0xEA
#define _P72_3A_PT_EB_PORT_PAGE72_HDMI_SCDC_EB                      0xEB
#define _P72_3A_PT_EC_PORT_PAGE72_HDMI_SCDC_EC                      0xEC
#define _P72_3A_PT_ED_PORT_PAGE72_HDMI_SCDC_ED                      0xED
#define _P72_3A_PT_EE_PORT_PAGE72_HDMI_SCDC_EE                      0xEE
#define _P72_3A_PT_EF_PORT_PAGE72_HDMI_SCDC_EF                      0xEF
#define _P72_3A_PT_F0_PORT_PAGE72_HDMI_SCDC_F0                      0xF0
#define _P72_3A_PT_F1_PORT_PAGE72_HDMI_SCDC_F1                      0xF1
#define _P72_3A_PT_F2_PORT_PAGE72_HDMI_SCDC_F2                      0xF2
#define _P72_3A_PT_F3_PORT_PAGE72_HDMI_SCDC_F3                      0xF3
#define _P72_3A_PT_F4_PORT_PAGE72_HDMI_SCDC_F4                      0xF4
#define _P72_3A_PT_F5_PORT_PAGE72_HDMI_SCDC_F5                      0xF5
#define _P72_3A_PT_F6_PORT_PAGE72_HDMI_SCDC_F6                      0xF6
#define _P72_3A_PT_F7_PORT_PAGE72_HDMI_SCDC_F7                      0xF7
#define _P72_3A_PT_F8_PORT_PAGE72_HDMI_SCDC_F8                      0xF8
#define _P72_3A_PT_F9_PORT_PAGE72_HDMI_SCDC_F9                      0xF9
#define _P72_3A_PT_FA_PORT_PAGE72_HDMI_SCDC_FA                      0xFA
#define _P72_3A_PT_FB_PORT_PAGE72_HDMI_SCDC_FB                      0xFB
#define _P72_3A_PT_FC_PORT_PAGE72_HDMI_SCDC_FC                      0xFC
#define _P72_3A_PT_FD_PORT_PAGE72_HDMI_SCDC_FD                      0xFD
#define _P72_3A_PT_FE_PORT_PAGE72_HDMI_SCDC_FE                      0xFE
#define _P72_3A_PT_FF_PORT_PAGE72_HDMI_SCDC_FF                      0xFF


//--------------------------------------------------
// D3 Port Overall HDMI System Function Block HDCP Port Register (Page 72)
//--------------------------------------------------
#define _P72_C4_PT_00_PORT_PAGE72_BKSV0                             0x00
#define _P72_C4_PT_01_PORT_PAGE72_BKSV1                             0x01
#define _P72_C4_PT_02_PORT_PAGE72_BKSV2                             0x02
#define _P72_C4_PT_03_PORT_PAGE72_BKSV3                             0x03
#define _P72_C4_PT_04_PORT_PAGE72_BKSV4                             0x04
#define _P72_C4_PT_08_PORT_PAGE72_RI0                               0x08
#define _P72_C4_PT_09_PORT_PAGE72_RI1                               0x09
#define _P72_C4_PT_0A_PORT_PAGE72_PJ                                0x0A
#define _P72_C4_PT_10_PORT_PAGE72_AKSV0                             0x10
#define _P72_C4_PT_11_PORT_PAGE72_AKSV1                             0x11
#define _P72_C4_PT_12_PORT_PAGE72_AKSV2                             0x12
#define _P72_C4_PT_13_PORT_PAGE72_AKSV3                             0x13
#define _P72_C4_PT_14_PORT_PAGE72_AKSV4                             0x14
#define _P72_C4_PT_15_PORT_PAGE72_AINFO                             0x15
#define _P72_C4_PT_18_PORT_PAGE72_AN0                               0x18
#define _P72_C4_PT_19_PORT_PAGE72_AN1                               0x19
#define _P72_C4_PT_1A_PORT_PAGE72_AN2                               0x1A
#define _P72_C4_PT_1B_PORT_PAGE72_AN3                               0x1B
#define _P72_C4_PT_1C_PORT_PAGE72_AN4                               0x1C
#define _P72_C4_PT_1D_PORT_PAGE72_AN5                               0x1D
#define _P72_C4_PT_1E_PORT_PAGE72_AN6                               0x1E
#define _P72_C4_PT_1F_PORT_PAGE72_AN7                               0x1F
#define _P72_C4_PT_40_PORT_PAGE72_BCAPS                             0x40
#define _P72_C4_PT_42_PORT_PAGE72_BSTATUS                           0x42
#define _P72_C4_PT_43_PORT_PAGE72_KSV_FIFO                          0x43
#define _P72_C4_PT_50_PORT_PAGE72_HDCP2_VER                         0x50
#define _P72_C4_PT_60_PORT_PAGE72_HDCP2_WR_MSG                      0x60
#define _P72_C4_PT_70_PORT_PAGE72_HDCP2_STATUS1                     0x70
#define _P72_C4_PT_71_PORT_PAGE72_HDCP2_STATUS2                     0x71
#define _P72_C4_PT_80_PORT_PAGE72_HDCP2_RDMSG                       0x80
#define _P72_C4_PT_C0_PORT_PAGE72_HDCP_FCR                          0xC0
#define _P72_C4_PT_C1_PORT_PAGE72_HDCP_SIR                          0xC1
#define _P72_C4_PT_C2_PORT_PAGE72_HDCP_SLAVE_ADD                    0xC2


//--------------------------------------------------
// D3 Port Overall HDMI System Function Block Video Port Register(Page 72)
//--------------------------------------------------
#define _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR                          0x00
#define _P72_CA_PT_01_PORT_PAGE72_HDMI_N_VAL                        0x01
#define _P72_CA_PT_02_PORT_PAGE72_HDMI_BCHCR                        0x02
#define _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR                         0x03
#define _P72_CA_PT_04_PORT_PAGE72_HDMI_AFSR                         0x04
#define _P72_CA_PT_05_PORT_PAGE72_HDMI_MAGCR1                       0x05
#define _P72_CA_PT_06_PORT_PAGE72_HDMI_MAGCR2                       0x06
#define _P72_CA_PT_07_PORT_PAGE72_HDMI_MAG_M_FINAL                  0x07
#define _P72_CA_PT_08_PORT_PAGE72_HDMI_MAG_L_FINAL                  0x08
#define _P72_CA_PT_09_PORT_PAGE72_HDMI_MAG_R_FINAL                  0x09
#define _P72_CA_PT_0A_PORT_PAGE72_AUDIO_LD_P_TIME_M                 0x0A
#define _P72_CA_PT_0B_PORT_PAGE72_AUDIO_LD_P_TIME_N                 0x0B
#define _P72_CA_PT_0C_PORT_PAGE72_ZCD_CTRL                          0x0C
#define _P72_CA_PT_0D_PORT_PAGE72_ZCD_TIMEOUT                       0x0D
#define _P72_CA_PT_0E_PORT_PAGE72_ZCD_STATUS                        0x0E
#define _P72_CA_PT_10_PORT_PAGE72_HDMI_CMCR                         0x10
#define _P72_CA_PT_11_PORT_PAGE72_HDMI_MCAPR                        0x11
#define _P72_CA_PT_12_PORT_PAGE72_HDMI_SCAPR                        0x12
#define _P72_CA_PT_13_PORT_PAGE72_HDMI_DCAPR0                       0x13
#define _P72_CA_PT_14_PORT_PAGE72_HDMI_DCAPR1                       0x14
#define _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR                         0x15
#define _P72_CA_PT_16_PORT_PAGE72_HDMI_FDDR                         0x16
#define _P72_CA_PT_17_PORT_PAGE72_HDMI_FDDF                         0x17
#define _P72_CA_PT_18_PORT_PAGE72_HDMI_MFDDR                        0x18
#define _P72_CA_PT_19_PORT_PAGE72_HDMI_MFDDF                        0x19
#define _P72_CA_PT_1A_PORT_PAGE72_HDMI_FTR                          0x1A
#define _P72_CA_PT_1B_PORT_PAGE72_HDMI_FBR                          0x1B
#define _P72_CA_PT_1C_PORT_PAGE72_HDMI_ICPSNCR0                     0x1C
#define _P72_CA_PT_1D_PORT_PAGE72_HDMI_ICPSNCR1                     0x1D
#define _P72_CA_PT_1E_PORT_PAGE72_HDMI_PCPSNCR0                     0x1E
#define _P72_CA_PT_1F_PORT_PAGE72_HDMI_PCPSNCR1                     0x1F
#define _P72_CA_PT_20_PORT_PAGE72_HDMI_ICTPSR0                      0x20
#define _P72_CA_PT_21_PORT_PAGE72_HDMI_ICTPSR1                      0x21
#define _P72_CA_PT_22_PORT_PAGE72_HDMI_PCTPSR0                      0x22
#define _P72_CA_PT_23_PORT_PAGE72_HDMI_PCTPSR1                      0x23
#define _P72_CA_PT_24_PORT_PAGE72_HDMI_ICBPSR0                      0x24
#define _P72_CA_PT_25_PORT_PAGE72_HDMI_ICBPSR1                      0x25
#define _P72_CA_PT_26_PORT_PAGE72_HDMI_PCBPSR0                      0x26
#define _P72_CA_PT_27_PORT_PAGE72_HDMI_PCBPSR1                      0x27
#define _P72_CA_PT_28_PORT_PAGE72_HDMI_NTX1024TR0                   0x28
#define _P72_CA_PT_29_PORT_PAGE72_HDMI_NTX1024TR1                   0x29
#define _P72_CA_PT_2A_PORT_PAGE72_HDMI_STBPR                        0x2A
#define _P72_CA_PT_2B_PORT_PAGE72_HDMI_NCPER                        0x2B
#define _P72_CA_PT_2C_PORT_PAGE72_HDMI_PETR                         0x2C
#define _P72_CA_PT_2D_PORT_PAGE72_HDMI_AAPNR                        0x2D
#define _P72_CA_PT_2E_PORT_PAGE72_HDMI_APDMCR                       0x2E
#define _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR                        0x30
#define _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0                        0x31
#define _P72_CA_PT_32_PORT_PAGE72_HDMI_WDCR1                        0x32
#define _P72_CA_PT_33_PORT_PAGE72_HDMI_WDCR2                        0x33
#define _P72_CA_PT_34_PORT_PAGE72_HDMI_DBCR                         0x34
#define _P72_CA_PT_35_PORT_PAGE72_HDMI_APTMCR0                      0x35
#define _P72_CA_PT_36_PORT_PAGE72_HDMI_APTMCR1                      0x36
#define _P72_CA_PT_38_PORT_PAGE72_HDMI_DPCR0                        0x38
#define _P72_CA_PT_39_PORT_PAGE72_HDMI_DPCR1                        0x39
#define _P72_CA_PT_3A_PORT_PAGE72_HDMI_DPCR2                        0x3A
#define _P72_CA_PT_3B_PORT_PAGE72_HDMI_DPCR3                        0x3B
#define _P72_CA_PT_3C_PORT_PAGE72_HDMI_SUMCM                        0x3C
#define _P72_CA_PT_3D_PORT_PAGE72_HDMI_SUMCL                        0x3D
#define _P72_CA_PT_3E_PORT_PAGE72_DPLL_M_N_MSB                      0x3E
#define _P72_CA_PT_3F_PORT_PAGE72_DPLL_LDO                          0x3F
#define _P72_CA_PT_40_PORT_PAGE72_HDMI_AWDSR                        0x40
#define _P72_CA_PT_41_PORT_PAGE72_HDMI_VWDSR                        0x41
#define _P72_CA_PT_42_PORT_PAGE72_HDMI_PAMICR                       0x42
#define _P72_CA_PT_43_PORT_PAGE72_HDMI_PTRSV0                       0x43
#define _P72_CA_PT_44_PORT_PAGE72_HDMI_PTRSV1                       0x44
#define _P72_CA_PT_45_PORT_PAGE72_HDMI_PVGCR0                       0x45
#define _P72_CA_PT_46_PORT_PAGE72_HDMI_PVGCR1                       0x46
#define _P72_CA_PT_47_PORT_PAGE72_HDMI_PVGCR2                       0x47
#define _P72_CA_PT_48_PORT_PAGE72_HDMI_PVSR0                        0x48
#define _P72_CA_PT_49_PORT_PAGE72_HDMI_PVSR1                        0x49
#define _P72_CA_PT_4A_PORT_PAGE72_HDMI_PVSR2                        0x4A
#define _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR                          0x50
#define _P72_CA_PT_51_PORT_PAGE72_HDMI_ACRCR                        0x51
#define _P72_CA_PT_52_PORT_PAGE72_HDMI_ACRSR0                       0x52
#define _P72_CA_PT_53_PORT_PAGE72_HDMI_ACRSR1                       0x53
#define _P72_CA_PT_54_PORT_PAGE72_HDMI_ACRSR2                       0x54
#define _P72_CA_PT_55_PORT_PAGE72_HDMI_ACRSR3                       0x55
#define _P72_CA_PT_56_PORT_PAGE72_HDMI_ACRSR4                       0x56
#define _P72_CA_PT_57_PORT_PAGE72_HDMI_ACS0                         0x57
#define _P72_CA_PT_58_PORT_PAGE72_HDMI_ACS1                         0x58
#define _P72_CA_PT_59_PORT_PAGE72_HDMI_ACS2                         0x59
#define _P72_CA_PT_5A_PORT_PAGE72_HDMI_ACS3                         0x5A
#define _P72_CA_PT_5B_PORT_PAGE72_HDMI_ACS4                         0x5B
#define _P72_CA_PT_60_PORT_PAGE72_HDMI_INTCR                        0x60
#define _P72_CA_PT_61_PORT_PAGE72_HDMI_ALCR                         0x61
#define _P72_CA_PT_62_PORT_PAGE72_HDMI_AOCR                         0x62
#define _P72_CA_PT_63_PORT_PAGE72_HDMI_PEAC1                        0x63
#define _P72_CA_PT_64_PORT_PAGE72_HDMI_PEAC2                        0x64
#define _P72_CA_PT_70_PORT_PAGE72_HDMI_BCSR                         0x70
#define _P72_CA_PT_71_PORT_PAGE72_HDMI_ASR0                         0x71
#define _P72_CA_PT_72_PORT_PAGE72_HDMI_ASR1                         0x72
#define _P72_CA_PT_80_PORT_PAGE72_HDMI_DPC_SET0                     0x80
#define _P72_CA_PT_81_PORT_PAGE72_HDMI_DPC_SET1                     0x81
#define _P72_CA_PT_82_PORT_PAGE72_HDMI_DPC_SET2                     0x82
#define _P72_CA_PT_83_PORT_PAGE72_HDMI_DPC_SET3                     0x83
#define _P72_CA_PT_84_PORT_PAGE72_HDMI_DET_0                        0x84
#define _P72_CA_PT_85_PORT_PAGE72_HDMI_DET_1                        0x85
#define _P72_CA_PT_86_PORT_PAGE72_HDMI_DET_2                        0x86
#define _P72_CA_PT_87_PORT_PAGE72_HDMI_DET_3                        0x87
#define _P72_CA_PT_88_PORT_PAGE72_HDMI_DET_4                        0x88
#define _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET                     0x8A
#define _P72_CA_PT_8B_PORT_PAGE72_AUDIO_FREQ_RESULT                 0x8B
#define _P72_CA_PT_8C_PORT_PAGE72_AUDIO_FREQ_RESULT_M               0x8C
#define _P72_CA_PT_8D_PORT_PAGE72_AUDIO_FREQ_RESULT_L               0x8D
#define _P72_CA_PT_8E_PORT_PAGE72_XTAL_DIV                          0x8E
#define _P72_CA_PT_8F_PORT_PAGE72_TH0                               0x8F
#define _P72_CA_PT_90_PORT_PAGE72_TH1                               0x90
#define _P72_CA_PT_91_PORT_PAGE72_TH2                               0x91
#define _P72_CA_PT_92_PORT_PAGE72_TH3                               0x92
#define _P72_CA_PT_93_PORT_PAGE72_TH4                               0x93
#define _P72_CA_PT_94_PORT_PAGE72_TH5                               0x94
#define _P72_CA_PT_95_PORT_PAGE72_PRESET_S_CODE0                    0x95
#define _P72_CA_PT_96_PORT_PAGE72_PRESET_S_CODE1                    0x96
#define _P72_CA_PT_97_PORT_PAGE72_PRESET_S_CODE2                    0x97
#define _P72_CA_PT_98_PORT_PAGE72_PRESET_S2_CODE                    0x98
#define _P72_CA_PT_99_PORT_PAGE72_PRESET_D_CODE_0                   0x99
#define _P72_CA_PT_9A_PORT_PAGE72_PRESET_D_CODE_1                   0x9A
#define _P72_CA_PT_9B_PORT_PAGE72_PRESET_D_CODE_2                   0x9B
#define _P72_CA_PT_9C_PORT_PAGE72_PRESET_D_CODE_3                   0x9C
#define _P72_CA_PT_9D_PORT_PAGE72_PRESET_D_CODE_4                   0x9D
#define _P72_CA_PT_9E_PORT_PAGE72_PRESET_D_CODE_5                   0x9E
#define _P72_CA_PT_9F_PORT_PAGE72_PRESET_AFSM_MOD                   0x9F
#define _P72_CA_PT_A4_PORT_PAGE72_HDMI_PTRSV_2                      0xA4
#define _P72_CA_PT_A5_PORT_PAGE72_HDMI_PTRSV_3                      0xA5
#define _P72_CA_PT_A6_PORT_PAGE72_HDMI_PARSV                        0xA6
#define _P72_CA_PT_A7_PORT_PAGE72_HDMI_GPVS_0                       0xA7
#define _P72_CA_PT_A8_PORT_PAGE72_HDMI_PVSR_3                       0xA8
#define _P72_CA_PT_A9_PORT_PAGE72_HDMI_PVSR_4                       0xA9
#define _P72_CA_PT_AA_PORT_PAGE72_HDMI_PVGCR3                       0xAA
#define _P72_CA_PT_AB_PORT_PAGE72_HDMI_PVGCR4                       0xAB
#define _P72_CA_PT_AE_PORT_PAGE72_HDMI_GDI_TEST_FUNC                0xAE
#define _P72_CA_PT_AF_PORT_PAGE72_HDMI_BED_FUNC_0                   0xAF
#define _P72_CA_PT_B0_PORT_PAGE72_HDMI_BED_FUNC_1                   0xB0
#define _P72_CA_PT_B1_PORT_PAGE72_HDMI_BED_FUNC_2                   0xB1
#define _P72_CA_PT_B2_PORT_PAGE72_HDMI_BED_FUNC_3                   0xB2
#define _P72_CA_PT_B3_PORT_PAGE72_HDMI_BED_FUNC_4                   0xB3
#define _P72_CA_PT_B4_PORT_PAGE72_HDMI_BED_FUNC_5                   0xB4
#define _P72_CA_PT_B5_PORT_PAGE72_HDMI_BED_FUNC_6                   0xB5
#define _P72_CA_PT_B6_PORT_PAGE72_HDMI_BED_FUNC_7                   0xB6
#define _P72_CA_PT_B7_PORT_PAGE72_HDMI_BED_FUNC_8                   0xB7
#define _P72_CA_PT_B8_PORT_PAGE72_HDMI_BED_FUNC_9                   0xB8


//--------------------------------------------------
// Chip Control Part1 (Page 0)
//--------------------------------------------------
#define P0_00_ID_REG                                                0x0000
#define P0_01_HOST_CTRL                                             0x0001


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
#define P0_09_GA_POWER_CTRL                                         0x0009
#define P0_0A_GC_POWER_CTRL                                         0x000A
#define P0_0B_POWER_CTRL                                            0x000B


//--------------------------------------------------
// Watch Dog (Page 0)
//--------------------------------------------------
#define P0_0C_WATCH_DOG_CTRL0                                       0x000C
#define P0_0D_TOP_DUMMY2                                            0x000D


//--------------------------------------------------
// Chip Control Part2 (Page 0)
//--------------------------------------------------
#define P0_0E_I_D_MAPPING                                           0x000E
#define P0_0F_ID_REG_02                                             0x000F


//--------------------------------------------------
// M1 Input Video Capture (Page 0)
//--------------------------------------------------
#define P0_10_M1_VGIP_CTRL                                          0x0010
#define P0_11_M1_VGIP_SIGINV                                        0x0011
#define P0_12_M1_VGIP_DELAY_CTRL                                    0x0012
#define P0_13_M1_VGIP_ODD_CTRL                                      0x0013


//--------------------------------------------------
// M1 Input Frame Window (Page 0)
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
// M1 FIFO Frequency (Page 0)
//--------------------------------------------------
#define P0_22_M1_FIFO_CLOCK_SELECT                                  0x0022


//--------------------------------------------------
// Scaling Down Control (Page 0)
//--------------------------------------------------
#define P0_23_SCALE_DOWN_CTRL_M1                                    0x0023
#define P0_24_SD_ADDRESS_PORT_M1                                    0x0024
#define P0_25_SD_DATA_PORT_M1                                       0x0025
#define P0_26_SD_FILTER_CONTROL_REG_M1                              0x0026
#define P0_27_SD_USER_FILTER_ACCESS_PORT_M1                         0x0027


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
#define P0_46_LAST_LINE_H1                                          0x0046


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
// Contrast & Brightness (Page 0)
//--------------------------------------------------
#define P0_62_SRGB_CTRL                                             0x0062
#define P0_64_CTS_BRI_PORT_ADD                                      0x0064
#define P0_65_CTS_BRI_PORT_DATA                                     0x0065


//--------------------------------------------------
// Color Processor Control (Page 0)
//--------------------------------------------------
#define P0_63_SRGB_ACCESS_PORT_SETA                                 0x0063
#define P0_68_GAMMA_BIST_DITHER_SETA                                0x0068


//--------------------------------------------------
// Gamma Control (Page 0)
//--------------------------------------------------
#define P0_66_GAMMA_PORT_SETA                                       0x0066
#define P0_67_GAMMA_CTRL_SETA                                       0x0067


//--------------------------------------------------
// DDither Control (Page 0)
//--------------------------------------------------
#define P0_69_D_DITHER_DATA_ACCESS                                  0x0069
#define P0_6A_D_DITHER_COMMON_CTRL1                                 0x006A
#define P0_6B_D_DITHER_REGISTER_ADDR                                0x006B


//--------------------------------------------------
// Back ground color (Page 0)
//--------------------------------------------------
#define P0_6C_OVERLAY_CTRL                                          0x006C
#define P0_6D_BG_COLOR_DATA_PORT                                    0x006D
#define P0_8F_OVERLAY_CTRL1                                         0x008F


//--------------------------------------------------
// OSD Color Palette (Page 0)
//--------------------------------------------------
#define P0_6E_OVERLAY_LUT_ADDR                                      0x006E
#define P0_6F_COLOR_LUT_PORT                                        0x006F


//--------------------------------------------------
// M1 Image Auto Function (Page 0)
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
// IDither Control (Page 0)
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
// I-Domain Color Conversion (Page 0)
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
// LVR (Page 0)
//--------------------------------------------------
#define P0_E1_VCCKOFF_CONTROL2                                      0x00E1
#define P0_F0_VCCKOFF_CONTROL0                                      0x00F0
#define P0_F1_VCCKOFF_CONTROL1                                      0x00F1
#define P0_F3_POWER_ON_RESET                                        0x00F3


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


//--------------------------------------------------
// DCLK Spread Spectrum (Page 1)
//--------------------------------------------------
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
// SDR / DDR Pinshare Off Control (Page 4)
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


//--------------------------------------------------
// SDR / DDR Pinshare On Control (Page 4)
//--------------------------------------------------
#define P4_10_SDDR_CTRL                                             0x0410
#define P4_11_SDDR_CLK_CTRL0                                        0x0411
#define P4_12_SDDR_CLK_CTRL1                                        0x0412
#define P4_13_SDDR_CDAR_CTRL                                        0x0413
#define P4_14_SDDR_DQSX0_CTRL0                                      0x0414
#define P4_15_SDDR_DQSX0_CTRL1                                      0x0415
#define P4_16_SDDR_DQX0_CTRL0                                       0x0416
#define P4_17_SDDR_DQX0_CTRL1                                       0x0417
#define P4_18_SDDR_DQSX1_CTRL0                                      0x0418
#define P4_19_SDDR_DQSX1_CTRL1                                      0x0419
#define P4_1A_SDDR_DQX1_CTRL0                                       0x041A
#define P4_1B_SDDR_DQX1_CTRL1                                       0x041B


//--------------------------------------------------
// SDRAM / DDR Control (Page 4)
//--------------------------------------------------
#define P4_20_TX_PHASE_CALIBRATION_2                                0x0420
#define P4_21_TX_CALIBRATION_RESULT_2                               0x0421
#define P4_22_TX2_CLK_DLY                                           0x0422
#define P4_23_DDR_AUTO_CALIB6                                       0x0423
#define P4_24_DDR_AUTO_CALIB_RLT6                                   0x0424
#define P4_25_DDR_TX2_DLY2                                          0x0425
#define P4_26_DDR_TX2_DLY3                                          0x0426
#define P4_27_DDR_RX2_DLY0                                          0x0427
#define P4_28_DDR_AUTO_CALIB7                                       0x0428
#define P4_29_DDR_AUTO_CALIB_RLT7                                   0x0429
#define P4_2A_DDR_AUTO_CALIB8                                       0x042A
#define P4_2B_DDR_AUTO_CALIB_RLT8                                   0x042B
#define P4_2C_DDR_AUTO_CALIB9                                       0x042C
#define P4_2D_DDR_AUTO_CALIB_RLT9                                   0x042D
#define P4_2E_DDR_AUTO_CALIB10                                      0x042E
#define P4_2F_DDR_AUTO_CALIB_RLT10                                  0x042F
#define P4_30_DDR_RX2_DLY1                                          0x0430
#define P4_31_DDR_RX2_DLY2                                          0x0431
#define P4_32_DDR_RX2_DLY3                                          0x0432
#define P4_33_DDR_RX2_DLY4                                          0x0433
#define P4_34_DDR_RX2_DLY5                                          0x0434
#define P4_35_DDR_RX2_DLY6                                          0x0435
#define P4_36_DDR_RX2_DLY7                                          0x0436
#define P4_37_DDR_RX2_DLY8                                          0x0437
#define P4_38_DDR_MEASURE2                                          0x0438
#define P4_39_DDR_AUTO_CALIB_DQS2_SEL0                              0x0439
#define P4_3A_DDR_AUTO_CALIB_DQS2_SEL1                              0x043A
#define P4_3B_DDR_AUTO_CALIB_DQS3_SEL0                              0x043B
#define P4_3C_DDR_AUTO_CALIB_DQS3_SEL1                              0x043C
#define P4_3D_DDR_AUTO_CALIB_RLT_SEL2                               0x043D
#define P4_3E_DDR_AUTO_CALIB_DQS2_R_RLT0                            0x043E
#define P4_3F_DDR_AUTO_CALIB_DQS2_R_RLT1                            0x043F
#define P4_40_DDR_AUTO_CALIB_DQS2_R_RLT2                            0x0440
#define P4_41_DDR_AUTO_CALIB_DQS2_R_RLT3                            0x0441
#define P4_42_DDR_AUTO_CALIB_DQS2_F_RLT0                            0x0442
#define P4_43_DDR_AUTO_CALIB_DQS2_F_RLT1                            0x0443
#define P4_44_DDR_AUTO_CALIB_DQS2_F_RLT2                            0x0444
#define P4_45_DDR_AUTO_CALIB_DQS2_F_RLT3                            0x0445
#define P4_46_DDR_AUTO_CALIB_DQS3_R_RLT0                            0x0446
#define P4_47_DDR_AUTO_CALIB_DQS3_R_RLT1                            0x0447
#define P4_48_DDR_AUTO_CALIB_DQS3_R_RLT2                            0x0448
#define P4_49_DDR_AUTO_CALIB_DQS3_R_RLT3                            0x0449
#define P4_4A_DDR_AUTO_CALIB_DQS3_F_RLT0                            0x044A
#define P4_4B_DDR_AUTO_CALIB_DQS3_F_RLT1                            0x044B
#define P4_4C_DDR_AUTO_CALIB_DQS3_F_RLT2                            0x044C
#define P4_4D_DDR_AUTO_CALIB_DQS3_F_RLT3                            0x044D
#define P4_4E_DDR_AUTO_CALIB_RLT_SEL3                               0x044E
#define P4_A1_SDR_CTRL0                                             0x04A1
#define P4_A2_SDR_CTRL1                                             0x04A2
#define P4_A3_SDR_AREF_TIME                                         0x04A3
#define P4_A4_SDR_PRCG                                              0x04A4
#define P4_A5_SDR_MEM_TYPE                                          0x04A5
#define P4_A6_SDR_SLEW_RATE                                         0x04A6
#define P4_A7_SDR_AREF_CNT                                          0x04A7
#define P4_A8_SDR_CLK_ALIGN                                         0x04A8
#define P4_A9_RESERVED                                              0x04A9
#define P4_AA_SDR_RSC_AREF                                          0x04AA
#define P4_AB_SDR_RSC_MCU                                           0x04AB
#define P4_AC_SDR_RSC_CAP1                                          0x04AC
#define P4_AE_SDR_RSC_MAIN                                          0x04AE
#define P4_B0_SDR_RSC_RTC_RD                                        0x04B0
#define P4_B1_SDR_RSC_RTC_WR                                        0x04B1
#define P4_B2_RESERVED                                              0x04B2
#define P4_B3_RESERVED                                              0x04B3
#define P4_B4_SDR_ABTR_STATUS0                                      0x04B4
#define P4_B5_SDR_ABTR_STATUS1                                      0x04B5
#define P4_B6_RESERVED                                              0x04B6
#define P4_B7_SDR_POWER_CTRL0                                       0x04B7
#define P4_B8_SDR_ADDR_H                                            0x04B8
#define P4_B9_SDR_ADDR_M                                            0x04B9
#define P4_BA_SDR_ADDR_L                                            0x04BA
#define P4_BB_SDR_ACCESS_CMD                                        0x04BB
#define P4_BC_SDR_DATA_BUF                                          0x04BC
#define P4_BD_SDR_MCU_RD_LEN                                        0x04BD
#define P4_BE_SDR_RX_PHASE_CALIBRATION                              0x04BE
#define P4_BF_SDR_RX_CALIBRATION_RESULT                             0x04BF
#define P4_C0_TX_CLK_DLY1                                           0x04C0
#define P4_C1_TX_CLK_DLY2                                           0x04C1
#define P4_C2_SDR_RX_CLK_DLY1                                       0x04C2
#define P4_C3_SDR_RX_CLK_DLY2                                       0x04C3
#define P4_C4_SDR_RX_CLK_DLY3                                       0x04C4
#define P4_C5_SDR_RX_CLK_DLY4                                       0x04C5
#define P4_C6_SEC_SDR_RX_DLY5                                       0x04C6
#define P4_C7_SEC_SDR_RX_DLY6                                       0x04C7
#define P4_C8_MCLK_CTRL                                             0x04C8
#define P4_C9_SDR_STOPCLK_CNT                                       0x04C9
#define P4_CA_STOP_WAIT_CNT                                         0x04CA
#define P4_CB_TX_PHASE_CALIBRATION                                  0x04CB
#define P4_CC_TX_CALIBRATION_RESULT                                 0x04CC
#define P4_CD_DDR_TX_DLY0                                           0x04CD
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
#define P4_EB_DDR_AUTO_CALIB_DQS0_F_RLT1                            0x04EB
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
#define P4_FC_EXTENDED_MODE_REGISTER0                               0x04FC
#define P4_FD_EXTENDED_MODE_REGISTER1                               0x04FD
#define P4_FE_RANDOM_GENERATOR                                      0x04FE
#define P4_FF_CRC_DATA_PORT                                         0x04FF


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
#define P7_CC_SCM_BLOCK_ENABLE                                      0x07CC
#define P7_CD_SCM_BLOCK_SELECT                                      0x07CD
#define P7_CE_SCM_ACCESS_PORT_CONTROL                               0x07CE
#define P7_CF_SCM_ACCESS_PORT_DATA                                  0x07CF
#define P7_D0_ICM_CONTROL                                           0x07D0
#define P7_D1_ICM_SEL                                               0x07D1
#define P7_D2_ICM_ADDR                                              0x07D2
#define P7_D3_ICM_DATA                                              0x07D3
#define P7_D4_ICM_SEL2                                              0x07D4


//--------------------------------------------------
// DCR Part1 (Page 7)
//--------------------------------------------------
#define P7_D8_DCR_ADDRESS_PORT                                      0x07D8
#define P7_D9_DCR_DATA_PORT                                         0x07D9


//--------------------------------------------------
// DCR Part2 (Page 7)
//--------------------------------------------------
#define P7_DA_DCR_CTRL                                              0x07DA


//--------------------------------------------------
// IAPS Gain (Page 7)
//--------------------------------------------------
#define P7_E0_IAPS_GAIN_CTRL_M1                                     0x07E0
#define P7_E1_GAIN_VALUE1_M1                                        0x07E1
#define P7_E2_GAIN_VALUE0_M1                                        0x07E2
#define P7_E3_SOFT_CLAMP_M1                                         0x07E3
#define P7_E4_IAPS_GAIN_DB_CTRL_M1                                  0x07E4


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
#define P7_FE_DISP_PG_DELTA_L                                       0x07FE
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
// Gamma Bist Control (Page 9)
//--------------------------------------------------
#define P9_00_GAMMA_BIST_SET_M1                                     0x0900
#define P9_01_GAMMA_BIST_CTRL0_M1                                   0x0901
#define P9_02_GAMMA_BIST_CTRL1_M1                                   0x0902
#define P9_03_GAMMA_BIST_CTRL2_M1                                   0x0903
#define P9_10_RGB_GAMMA_CLK_M1                                      0x0910
#define P9_11_RGB_GAMMA_BIST_CTRL0_M1                               0x0911
#define P9_12_RGB_GAMMA_BIST_CTRL1_M1                               0x0912
#define P9_13_RGB_GAMMA_BIST_CTRL2_M1                               0x0913


//--------------------------------------------------
// Input Gamma Control (Page 9)
//--------------------------------------------------
#define P9_A0_INPUT_GAMMA_PORT                                      0x09A0
#define P9_A1_INPUT_GAMMA_CTRL                                      0x09A1
#define P9_A2_INPUT_GAMMA_LOW_THRE                                  0x09A2
#define P9_A3_INPUT_GAMMA_HIGH_THRE                                 0x09A3
#define P9_A8_IG_DUMMY                                              0x09A8


//--------------------------------------------------
// RGB 3D Gamma Control (Page 9)
//--------------------------------------------------
#define P9_B0_RGB_3D_GAMMA_CTRL                                     0x09B0
#define P9_B1_RGB_3D_GAMMA_ADDRESS_H                                0x09B1
#define P9_B2_RGB_3D_GAMMA_ADDRESS_L                                0x09B2
#define P9_B3_RGB_3D_GAMMA_PORT                                     0x09B3
#define P9_B4_RGB_3D_GAMMA_BIST_CTRL_MAIN1_1                        0x09B4
#define P9_B5_RGB_3D_GAMMA_BIST_CTRL_MAIN1_2                        0x09B5
#define P9_B6_RGB_3D_GAMMA_BIST_CTRL_MAIN2_1                        0x09B6
#define P9_B7_RGB_3D_GAMMA_BIST_CTRL_MAIN2_2                        0x09B7
#define P9_B8_RGB_3D_GAMMA_DRF_BIST_MAIN1_1                         0x09B8
#define P9_B9_RGB_3D_GAMMA_DRF_BIST_MAIN1_2                         0x09B9


//--------------------------------------------------
// M1 RGB Gamma Control (Page 9)
//--------------------------------------------------
#define P9_D0_RGB_GAMMA_CTRL_M1                                     0x09D0
#define P9_D1_RGB_GAMMA_START_POINT_M1                              0x09D1
#define P9_D2_RGB_GAMMA_ADJUST_M1                                   0x09D2
#define P9_D3_RGB_GAMMA_DUMMY_M1                                    0x09D3


//--------------------------------------------------
// DisplayPort 1.2 Digital MAC MST2SST PART(Page A)
//--------------------------------------------------
#define PA_00_MST2SST_RESET                                         0x0A00
#define PA_01_MST2SST_ASYNC_FIFO                                    0x0A01
#define PA_10_MSA_HTT_0                                             0x0A10
#define PA_11_MSA_HTT_1                                             0x0A11
#define PA_12_MSA_HST_0                                             0x0A12
#define PA_13_MSA_HST_1                                             0x0A13
#define PA_14_MSA_HWD_0                                             0x0A14
#define PA_15_MSA_HWD_1                                             0x0A15
#define PA_16_MSA_HSW_0                                             0x0A16
#define PA_17_MSA_HSW_1                                             0x0A17
#define PA_18_MSA_VTT_0                                             0x0A18
#define PA_19_MSA_VTT_1                                             0x0A19
#define PA_1A_MSA_VST_0                                             0x0A1A
#define PA_1B_MSA_VST_1                                             0x0A1B
#define PA_1C_MSA_VHT_0                                             0x0A1C
#define PA_1D_MSA_VHT_1                                             0x0A1D
#define PA_1E_MSA_VSW_0                                             0x0A1E
#define PA_1F_MSA_VSW_1                                             0x0A1F
#define PA_20_MSA_MVID_00                                           0x0A20
#define PA_21_MSA_MVID_01                                           0x0A21
#define PA_22_MSA_MVID_02                                           0x0A22
#define PA_23_MSA_NVID_00                                           0x0A23
#define PA_24_MSA_NVID_01                                           0x0A24
#define PA_25_MSA_NVID_02                                           0x0A25
#define PA_26_MSA_MISC_0                                            0x0A26
#define PA_27_MSA_MISC_1                                            0x0A27
#define PA_28_MSA_COLOR_BIT                                         0x0A28
#define PA_29_MST2SST_VBID                                          0x0A29
#define PA_30_PG_CTRL_0                                             0x0A30
#define PA_31_PG_CTRL_1                                             0x0A31
#define PA_32_PG_CTRL_2                                             0x0A32
#define PA_33_PG_CTRL_3                                             0x0A33
#define PA_34_RB422_YONLY                                           0x0A34
#define PA_35_DPF_CTRL_0                                            0x0A35
#define PA_36_DP_OUTPUT_CTRL                                        0x0A36
#define PA_37_EVBLK2VS_H                                            0x0A37
#define PA_38_EVBLK2VS_M                                            0x0A38
#define PA_39_EVBLK2VS_L                                            0x0A39
#define PA_3A_OVBLK2VS_H                                            0x0A3A
#define PA_3B_OVBLK2VS_M                                            0x0A3B
#define PA_3C_OVBLK2VS_L                                            0x0A3C
#define PA_3D_BS2HS_0                                               0x0A3D
#define PA_3E_BS2HS_1                                               0x0A3E
#define PA_3F_VS_FRONT_PORCH                                        0x0A3F
#define PA_40_MN_DPF_HTT_M                                          0x0A40
#define PA_41_MN_DPF_HTT_L                                          0x0A41
#define PA_42_MN_DPF_HST_M                                          0x0A42
#define PA_43_MN_DPF_HST_L                                          0x0A43
#define PA_44_MN_DPF_HWD_M                                          0x0A44
#define PA_45_MN_DPF_HWD_L                                          0x0A45
#define PA_46_MN_DPF_HSW_M                                          0x0A46
#define PA_47_MN_DPF_HSW_L                                          0x0A47
#define PA_48_MN_DPF_VTT_M                                          0x0A48
#define PA_49_MN_DPF_VTT_L                                          0x0A49
#define PA_4A_MN_DPF_VST_M                                          0x0A4A
#define PA_4B_MN_DPF_VST_L                                          0x0A4B
#define PA_4C_MN_DPF_VHT_M                                          0x0A4C
#define PA_4D_MN_DPF_VHT_L                                          0x0A4D
#define PA_4E_MN_DPF_VSW_M                                          0x0A4E
#define PA_4F_MN_DPF_VSW_L                                          0x0A4F
#define PA_50_MN_DPF_BG_RED_M                                       0x0A50
#define PA_51_MN_DPF_BG_RED_L                                       0x0A51
#define PA_52_MN_DPF_BG_GRN_M                                       0x0A52
#define PA_53_MN_DPF_BG_GRN_L                                       0x0A53
#define PA_54_MN_DPF_BG_BLU_M                                       0x0A54
#define PA_55_MN_DPF_BG_BLU_L                                       0x0A55
#define PA_56_INTERLACE_MODE_CONFIG                                 0x0A56
#define PA_58_MN_MEAS_CTRL                                          0x0A58
#define PA_59_MN_MEAS_VLN_M                                         0x0A59
#define PA_5A_MN_MEAS_VLN_L                                         0x0A5A
#define PA_5B_MN_MEAS_HLN_M                                         0x0A5B
#define PA_5C_MN_MEAS_HLN_L                                         0x0A5C
#define PA_5D_VHEIGHT_MSB                                           0x0A5D
#define PA_5E_VHEIGHT_LSB                                           0x0A5E
#define PA_60_VBLANK_MSB                                            0x0A60
#define PA_61_VBLANK_LSB                                            0x0A61
#define PA_62_HBLANK_MSB                                            0x0A62
#define PA_63_HBLANK_LSB                                            0x0A63
#define PA_65_SRAM_BIST_0                                           0x0A65
#define PA_66_SRAM_BIST_1                                           0x0A66
#define PA_67_VIDEO_EN_CNT_0                                        0x0A67
#define PA_68_VIDEO_EN_CNT_1                                        0x0A68
#define PA_70_DP_CRC_CTRL                                           0x0A70
#define PA_71_DP_CRC_R_M                                            0x0A71
#define PA_72_DP_CRC_R_L                                            0x0A72
#define PA_73_DP_CRC_G_M                                            0x0A73
#define PA_74_DP_CRC_G_L                                            0x0A74
#define PA_75_DP_CRC_B_M                                            0x0A75
#define PA_76_DP_CRC_B_L                                            0x0A76
#define PA_77_DP_CRC_CB_M                                           0x0A77
#define PA_78_DP_CRC_CB_L                                           0x0A78
#define PA_7A_MST2SST_IRQ                                           0x0A7A
#define PA_80_MST2SST_CONFIG                                        0x0A80
#define PA_81_MST2SST_CLK_GATE                                      0x0A81
#define PA_90_SOURCE_SEL_2                                          0x0A90
#define PA_91_DAISY_CTRL_0                                          0x0A91
#define PA_92_DAISY_CTRL_1                                          0x0A92
#define PA_93_DAISY_CTRL_2                                          0x0A93
#define PA_94_DAISY_CTRL_3                                          0x0A94
#define PA_95_DAISY_CTRL_4                                          0x0A95
#define PA_96_DAISY_CTRL_5                                          0x0A96
#define PA_97_DAISY_CTRL_6                                          0x0A97
#define PA_98_MIDFIFO_FLAG_0                                        0x0A98
#define PA_99_PREFIFO_FLAG_0                                        0x0A99
#define PA_9A_PREFIFO_FLAG_1                                        0x0A9A
#define PA_9B_ASYNC_FIFO_CLEAR                                      0x0A9B
#define PA_E0_MST2SST_TEST                                          0x0AE0
#define PA_E1_MST2SST_TEST1                                         0x0AE1
#define PA_F0_DP_RSV0                                               0x0AF0
#define PA_F1_DP_RSV1                                               0x0AF1
#define PA_F2_DP_RSV2                                               0x0AF2
#define PA_F3_DP_RSV3                                               0x0AF3
#define PA_F4_DP_RSV4                                               0x0AF4
#define PA_F5_DP_RSV5                                               0x0AF5
#define PA_F6_DP_RSV6                                               0x0AF6
#define PA_F7_DP_RSV7                                               0x0AF7
#define PA_F8_DP_RSV8                                               0x0AF8
#define PA_F9_DP_RSV9                                               0x0AF9
#define PA_FA_DP_RSVA                                               0x0AFA


//--------------------------------------------------
// DisplayPort 1.2 Digital MAC MST2SST PLL (Page A)
//--------------------------------------------------
#define PA_A0_MN_SCLKG_CTRL                                         0x0AA0
#define PA_A1_MN_SCLKG_DIVM                                         0x0AA1
#define PA_A2_MN_SCLKG_DIVN                                         0x0AA2
#define PA_A3_MN_SCLKG_DIVS                                         0x0AA3
#define PA_A4_MN_SCLKG_OFFS_H                                       0x0AA4
#define PA_A5_MN_SCLKG_OFFS_M                                       0x0AA5
#define PA_A6_MN_SCLKG_OFFS_L                                       0x0AA6
#define PA_A7_MN_SCLKG_TRK_CTRL                                     0x0AA7
#define PA_A8_MN_SCLKG_TRK_MN_I_H                                   0x0AA8
#define PA_A9_MN_SCLKG_TRK_MN_I_M                                   0x0AA9
#define PA_AA_MN_SCLKG_TRK_MN_I_L                                   0x0AAA
#define PA_AB_MN_SCLKG_TRK_MN_P_H                                   0x0AAB
#define PA_AC_MN_SCLKG_TRK_MN_P_M                                   0x0AAC
#define PA_AD_MN_SCLKG_TRK_MN_P_L                                   0x0AAD
#define PA_AE_MN_SCLKG_TRK_MN_PE                                    0x0AAE
#define PA_AF_MN_SCLKG_TRK_MN_NLOCK                                 0x0AAF
#define PA_B0_MN_SCLKG_TRK_VS_I_H                                   0x0AB0
#define PA_B1_MN_SCLKG_TRK_VS_I_M                                   0x0AB1
#define PA_B2_MN_SCLKG_TRK_VS_I_L                                   0x0AB2
#define PA_B3_MN_SCLKG_TRK_VS_P_H                                   0x0AB3
#define PA_B4_MN_SCLKG_TRK_VS_P_M                                   0x0AB4
#define PA_B5_MN_SCLKG_TRK_VS_P_L                                   0x0AB5
#define PA_B6_MN_SCLKG_TRK_VS_PE                                    0x0AB6
#define PA_B7_MN_SCLKG_TRK_VS_NLOCK                                 0x0AB7
#define PA_B8_MN_SCLKG_SDM_CTRL                                     0x0AB8
#define PA_B9_MN_SCLKG_SDM_TEST                                     0x0AB9
#define PA_BA_MN_SCLKG_SDM_SUMC_H                                   0x0ABA
#define PA_BB_MN_SCLKG_SDM_SUMC_M                                   0x0ABB
#define PA_BC_MN_SCLKG_SDM_SUMC_L                                   0x0ABC
#define PA_BD_MN_SCLKG_PLL_PWR                                      0x0ABD
#define PA_BE_MN_SCLKG_PLL_CHP                                      0x0ABE
#define PA_BF_MN_SCLKG_PLL_WD                                       0x0ABF
#define PA_C0_MN_SCLKG_PLL_INSEL                                    0x0AC0
#define PA_C1_MN_SCLKG_PLL_RESERVE                                  0x0AC1
#define PA_C2_HS_TRACKING_NEW_MODE1                                 0x0AC2
#define PA_C3_HS_TRACKING_NEW_MODE2                                 0x0AC3
#define PA_C4_M_CODE_ADJUST_0                                       0x0AC4
#define PA_C5_M_CODE_ADJUST_1                                       0x0AC5
#define PA_C6_M_CODE_ADJUST_2                                       0x0AC6
#define PA_C7_VBID_MAN_MADE                                         0x0AC7
#define PA_C8_DUMMY_1                                               0x0AC8
#define PA_C9_DUMMY_2                                               0x0AC9
#define PA_CA_DUMMY_3                                               0x0ACA


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
#define PB_10_PHY_CH_FIFO_SYNC0                                     0x0B10
#define PB_11_PHY_CH_FIFO_SYNC1                                     0x0B11
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
#define PB_28_M0_BYTE_7                                             0x0B28
#define PB_29_M0_BYTE_6                                             0x0B29
#define PB_2A_M0_BYTE_5                                             0x0B2A
#define PB_2B_M0_BYTE_4                                             0x0B2B
#define PB_2C_M0_BYTE_3                                             0x0B2C
#define PB_2D_M0_BYTE_2                                             0x0B2D
#define PB_2E_M0_BYTE_1                                             0x0B2E
#define PB_2F_M0_BYTE_0                                             0x0B2F
#define PB_30_SHA_CONTRL                                            0x0B30
#define PB_31_SHA_DATA1                                             0x0B31
#define PB_32_SHA_DATA2                                             0x0B32
#define PB_33_SHA_DATA3                                             0x0B33
#define PB_34_SHA_DATA4                                             0x0B34
#define PB_36_SHA_0                                                 0x0B36
#define PB_37_SHA_1                                                 0x0B37
#define PB_38_SHA_2                                                 0x0B38
#define PB_39_SHA_3                                                 0x0B39
#define PB_3A_SHA_4                                                 0x0B3A
#define PB_3B_SHA_5                                                 0x0B3B
#define PB_3C_SHA_6                                                 0x0B3C
#define PB_3D_SHA_7                                                 0x0B3D
#define PB_3E_SHA_8                                                 0x0B3E
#define PB_3F_SHA_9                                                 0x0B3F
#define PB_40_SHA_10                                                0x0B40
#define PB_41_SHA_11                                                0x0B41
#define PB_42_SHA_12                                                0x0B42
#define PB_43_SHA_13                                                0x0B43
#define PB_44_SHA_14                                                0x0B44
#define PB_45_SHA_15                                                0x0B45
#define PB_46_SHA_16                                                0x0B46
#define PB_47_SHA_17                                                0x0B47
#define PB_48_SHA_18                                                0x0B48
#define PB_49_SHA_19                                                0x0B49
#define PB_50_DP_SIG_DET_0                                          0x0B50
#define PB_51_DP_SIG_DET_1                                          0x0B51
#define PB_52_DP_SIG_DET_2                                          0x0B52
#define PB_53_DP_SIG_DET_3                                          0x0B53
#define PB_54_DP_SIG_DET_4                                          0x0B54


//--------------------------------------------------
// D0 HDCP 2.2 Module (Page B)
//--------------------------------------------------
#define PB_55_RIV0                                                  0x0B55
#define PB_56_RIV1                                                  0x0B56
#define PB_57_RIV2                                                  0x0B57
#define PB_58_RIV3                                                  0x0B58
#define PB_59_RIV4                                                  0x0B59
#define PB_5A_RIV5                                                  0x0B5A
#define PB_5B_RIV6                                                  0x0B5B
#define PB_5C_RIV7                                                  0x0B5C
#define PB_60_DEBUG0                                                0x0B60
#define PB_61_DEBUG1                                                0x0B61
#define PB_62_DEBUG2                                                0x0B62
#define PB_63_HDCP_OTHER                                            0x0B63
#define PB_64_HDCP_ENC_CTRL0                                        0x0B64
#define PB_65_HDCP_ENC_CTRL1                                        0x0B65
#define PB_66_HDCP_ENC_CTRL2                                        0x0B66
#define PB_67_HDCP_ENC_CTRL3                                        0x0B67
#define PB_68_HDCP_ENC_CTRL4                                        0x0B68
#define PB_69_HDCP_ENC_CTRL5                                        0x0B69
#define PB_6A_HDCP_ENC_CTRL6                                        0x0B6A
#define PB_6B_HDCP_ENC_CTRL7                                        0x0B6B
#define PB_81_HDCP_AES_CIPHER_KEY_15                                0x0B81
#define PB_82_HDCP_AES_CIPHER_KEY_14                                0x0B82
#define PB_83_HDCP_AES_CIPHER_KEY_13                                0x0B83
#define PB_84_HDCP_AES_CIPHER_KEY_12                                0x0B84
#define PB_85_HDCP_AES_CIPHER_KEY_11                                0x0B85
#define PB_86_HDCP_AES_CIPHER_KEY_10                                0x0B86
#define PB_87_HDCP_AES_CIPHER_KEY_9                                 0x0B87
#define PB_88_HDCP_AES_CIPHER_KEY_8                                 0x0B88
#define PB_89_HDCP_AES_CIPHER_KEY_7                                 0x0B89
#define PB_8A_HDCP_AES_CIPHER_KEY_6                                 0x0B8A
#define PB_8B_HDCP_AES_CIPHER_KEY_5                                 0x0B8B
#define PB_8C_HDCP_AES_CIPHER_KEY_4                                 0x0B8C
#define PB_8D_HDCP_AES_CIPHER_KEY_3                                 0x0B8D
#define PB_8E_HDCP_AES_CIPHER_KEY_2                                 0x0B8E
#define PB_8F_HDCP_AES_CIPHER_KEY_1                                 0x0B8F
#define PB_90_HDCP_AES_CIPHER_KEY_0                                 0x0B90
#define PB_93_HDCP_TYPE_AES_0                                       0x0B93
#define PB_94_HDCP_TYPE_AES_1                                       0x0B94
#define PB_95_HDCP_ST_TYPE                                          0x0B95
#define PB_96_DUMMY3                                                0x0B96
#define PB_97_DUMMY4                                                0x0B97


//--------------------------------------------------
// D0 Port DisplayPort 1.2 HDCP power on(Page B)
//--------------------------------------------------
#define PB_A0_DP_HDCP_CONTROL                                       0x0BA0
#define PB_A1_DP_HDCP_DOWNLOAD_PORT                                 0x0BA1
#define PB_A2_DP_HDCP_KEY_OUTPUT                                    0x0BA2
#define PB_A3_HDCP_IRQ                                              0x0BA3
#define PB_A4_HDCP_BIST                                             0x0BA4
#define PB_A5_HDCP_DEBUG                                            0x0BA5
#define PB_A6_KM                                                    0x0BA6
#define PB_AA_TEST_SEL                                              0x0BAA


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
#define P10_37_PIN_SHARE_CTRL87                                     0x1037
#define P10_38_PIN_SHARE_CTRL90                                     0x1038
#define P10_39_PIN_SHARE_CTRL91                                     0x1039
#define P10_3A_PIN_SHARE_CTRL92                                     0x103A
#define P10_3B_PIN_SHARE_CTRL93                                     0x103B
#define P10_3C_PIN_SHARE_CTRL94                                     0x103C
#define P10_3D_PIN_SHARE_CTRL95                                     0x103D
#define P10_3E_PIN_SHARE_CTRL96                                     0x103E
#define P10_3F_PIN_SHARE_CTRL97                                     0x103F
#define P10_40_PIN_SHARE_CTRLA0                                     0x1040
#define P10_41_PIN_SHARE_CTRLA1                                     0x1041
#define P10_42_PIN_SHARE_CTRLA2                                     0x1042
#define P10_43_PIN_SHARE_CTRLA3                                     0x1043
#define P10_44_PIN_SHARE_CTRLA4                                     0x1044
#define P10_45_PIN_SHARE_CTRLA5                                     0x1045
#define P10_46_PIN_SHARE_CTRLA6                                     0x1046
#define P10_47_PIN_SHARE_CTRLA7                                     0x1047
#define P10_48_PIN_SHARE_CTRLB0                                     0x1048
#define P10_49_PIN_SHARE_CTRLB1                                     0x1049
#define P10_4A_PIN_SHARE_CTRLB2                                     0x104A
#define P10_4B_PIN_SHARE_CTRLB3                                     0x104B
#define P10_4C_PIN_SHARE_CTRLB4                                     0x104C
#define P10_4D_PIN_SHARE_CTRLB5                                     0x104D
#define P10_4E_PIN_SHARE_CTRLB6                                     0x104E
#define P10_4F_PIN_SHARE_CTRLB7                                     0x104F
#define P10_50_PIN_SHARE_CTRLC0                                     0x1050
#define P10_51_PIN_SHARE_CTRLC1                                     0x1051
#define P10_52_PIN_SHARE_CTRLC2                                     0x1052
#define P10_53_PIN_SHARE_CTRLC3                                     0x1053
#define P10_54_PIN_SHARE_CTRLC4                                     0x1054
#define P10_55_PIN_SHARE_CTRLC5                                     0x1055
#define P10_56_PIN_SHARE_CTRLC6                                     0x1056
#define P10_57_PIN_SHARE_CTRLC7                                     0x1057
#define P10_58_PIN_SHARE_CTRLD0                                     0x1058
#define P10_59_PIN_SHARE_CTRLD1                                     0x1059
#define P10_5A_PIN_SHARE_CTRLD2                                     0x105A
#define P10_5B_PIN_SHARE_CTRLD3                                     0x105B
#define P10_5C_PIN_SHARE_CTRLD4                                     0x105C
#define P10_75_PIN_SLEW_RATE_CTRL0                                  0x1075
#define P10_76_PIN_SLEW_RATE_CTRL1                                  0x1076
#define P10_77_PIN_SCHMITT_CTRL0                                    0x1077
#define P10_78_PIN_SCHMITT_CTRL1                                    0x1078
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
#define P10_88_PIN_PULLUP_CTRL0E                                    0x1088
#define P10_89_PIN_PULLUP_CTRL0F                                    0x1089
#define P10_8A_PIN_PULLUP_CTRL10                                    0x108A
#define P10_8B_PIN_PULLUP_CTRL11                                    0x108B
#define P10_8C_PIN_PULLUP_CTRL12                                    0x108C
#define P10_A0_INT_PIN_SCHMITT_CTRL0                                0x10A0
#define P10_A1_INT_PIN_SCHMITT_CTRL1                                0x10A1
#define P10_B0_PIN_DRIVING_CTRL00                                   0x10B0
#define P10_B1_PIN_DRIVING_CTRL01                                   0x10B1
#define P10_B2_PIN_DRIVING_CTRL02                                   0x10B2
#define P10_B3_PIN_DRIVING_CTRL03                                   0x10B3
#define P10_B4_PIN_DRIVING_CTRL04                                   0x10B4
#define P10_B5_PIN_DRIVING_CTRL05                                   0x10B5
#define P10_B6_PIN_DRIVING_CTRL06                                   0x10B6
#define P10_B7_PIN_DRIVING_CTRL07                                   0x10B7
#define P10_B8_PIN_DRIVING_CTRL08                                   0x10B8
#define P10_B9_PIN_DRIVING_CTRL09                                   0x10B9
#define P10_BB_PIN_DRIVING_CTRL0B                                   0x10BB


//--------------------------------------------------
// M1 I Domain DLTI (Page 11)
//--------------------------------------------------
#define P11_A1_I_DLTI_CTRL_M1                                       0x11A1
#define P11_A2_I_DLTI_SEARCH_RANGE_M1                               0x11A2
#define P11_A3_I_DLTI_ADJUST_M1                                     0x11A3
#define P11_A4_I_DLTI_UPPER_THD_HSB_M1                              0x11A4
#define P11_A5_I_DLTI_UPPER_THD_LSB_M1                              0x11A5
#define P11_A6_I_DLTI_LOWER_THD_HSB_M1                              0x11A6
#define P11_A7_I_DLTI_LOWER_THD_LSB_M1                              0x11A7
#define P11_A8_I_DLTI_FILTER_C0_HSB_M1                              0x11A8
#define P11_A9_I_DLTI_FILTER_C0_LSB_M1                              0x11A9
#define P11_AA_I_DLTI_FILTER_C1_HSB_M1                              0x11AA
#define P11_AB_I_DLTI_FILTER_C1_LSB_M1                              0x11AB
#define P11_AC_I_DLTI_FILTER_C2_HSB_M1                              0x11AC
#define P11_AD_I_DLTI_FILTER_C2_LSB_M1                              0x11AD
#define P11_AE_I_DLTI_FILTER_C3_HSB_M1                              0x11AE
#define P11_AF_I_DLTI_FILTER_C3_LSB_M1                              0x11AF
#define P11_B0_I_DLTI_FILTER_C4_HSB_M1                              0x11B0
#define P11_B1_I_DLTI_FILTER_C4_LSB_M1                              0x11B1
#define P11_B2_I_DLTI_UPPER_LOWER_THD_M1                            0x11B2
#define P11_D4_I_DLTI_HLW_HOR_START_HSB_M1                          0x11D4
#define P11_D5_I_DLTI_HLW_HOR_START_LSB_M1                          0x11D5
#define P11_D6_I_DLTI_HLW_HOR_END_HSB_M1                            0x11D6
#define P11_D7_I_DLTI_HLW_HOR_END_LSB_M1                            0x11D7
#define P11_D8_I_DLTI_HLW_VER_START_HSB_M1                          0x11D8
#define P11_D9_I_DLTI_HLW_VER_START_LSB_M1                          0x11D9
#define P11_DA_I_DLTI_HLW_VER_END_HSB_M1                            0x11DA
#define P11_DB_I_DLTI_HLW_VER_END_LSB_M1                            0x11DB
#define P11_DC_I_DLTI_HLW_CTRL_M1                                   0x11DC
#define P11_DD_I_DLTI_DUMMY_M1                                      0x11DD


//--------------------------------------------------
// Light Super Resolution HLW (LSR) (Page 11)
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
// M1 SHP Part1 (Page 12)
//--------------------------------------------------
#define P12_A0_SR_SHP_CTRL_0                                        0x12A0
#define P12_A1_SR_SHP_CTRL_1                                        0x12A1
#define P12_A2_SR_SHP_BIST_CTRL_0                                   0x12A2
#define P12_A3_SR_DEBUGMODE_0                                       0x12A3
#define P12_A4_SR_DEBUGMODE_1                                       0x12A4
#define P12_A5_SR_EDGE_SOBEL                                        0x12A5
#define P12_A6_SR_EDGE_SOBEL_UB                                     0x12A6
#define P12_A7_SR_EDGE_HPF_C0_HSB                                   0x12A7
#define P12_A8_SR_EDGE_HPF_C0_LSB                                   0x12A8
#define P12_A9_SR_EDGE_HPF_C1_HSB                                   0x12A9
#define P12_AA_SR_EDGE_HPF_C1_LSB                                   0x12AA
#define P12_AB_SR_EDGE_HPF_C2                                       0x12AB
#define P12_AC_SR_EDGE_HPF_C3                                       0x12AC
#define P12_AD_SR_EDGE_HPF_C4                                       0x12AD
#define P12_AE_SR_EDGE_HPF_C5                                       0x12AE
#define P12_AF_SR_EDGE_HPF_SHIFT                                    0x12AF
#define P12_B0_SR_EDGE_PEAKING_GAIN_BLR                             0x12B0
#define P12_B1_SR_EDGE_PEAKING_GAIN_POS                             0x12B1
#define P12_B2_SR_EDGE_PEAKING_GAIN_NEG                             0x12B2
#define P12_B3_SR_EDGE_PEAKING_HV_POS_HSB                           0x12B3
#define P12_B4_SR_EDGE_PEAKING_HV_POS_LSB                           0x12B4
#define P12_B5_SR_EDGE_PEAKING_HV_NEG_HSB                           0x12B5
#define P12_B6_SR_EDGE_PEAKING_HV_NEG_LSB                           0x12B6
#define P12_B7_SR_EDGE_PEAKING_LV                                   0x12B7
#define P12_B8_SR_HOR_EMF_GAIN_1                                    0x12B8
#define P12_B9_SR_HOR_EMF_GAIN_2                                    0x12B9
#define P12_BA_SR_HOR_EMF_OFFSET_0_HSB                              0x12BA
#define P12_BB_SR_HOR_EMF_OFFSET_0_LSB                              0x12BB
#define P12_BC_SR_HOR_EMF_OFFSET_1_HSB                              0x12BC
#define P12_BD_SR_HOR_EMF_OFFSET_1_LSB                              0x12BD
#define P12_BE_SR_HOR_EMF_OFFSET_2_HSB                              0x12BE
#define P12_BF_SR_HOR_EMF_OFFSET_2_LSB                              0x12BF
#define P12_C0_SR_HOR_EMF_RANGE                                     0x12C0
#define P12_C1_SR_HOR_EMF_EXT                                       0x12C1
#define P12_C2_SR_HOR_EMFMK2_CTRL_0                                 0x12C2
#define P12_C3_SR_HOR_EMFMK2_CTRL_1                                 0x12C3
#define P12_C4_SR_HOR_EMFMK2_CTRL_2                                 0x12C4
#define P12_C5_SR_TEX_DET                                           0x12C5
#define P12_C6_SR_TEX_DET_UB                                        0x12C6
#define P12_C7_SR_TEX_HPF_C0_HSB                                    0x12C7
#define P12_C8_SR_TEX_HPF_C0_LSB                                    0x12C8
#define P12_C9_SR_TEX_HPF_C1_HSB                                    0x12C9
#define P12_CA_SR_TEX_HPF_C1_LSB                                    0x12CA
#define P12_CB_SR_TEX_HPF_C2                                        0x12CB
#define P12_CC_SR_TEX_HPF_C3                                        0x12CC
#define P12_CD_SR_TEX_HPF_C4                                        0x12CD
#define P12_CE_SR_TEX_HPF_C5                                        0x12CE
#define P12_CF_SR_TEX_HPF_SHIFT                                     0x12CF
#define P12_D0_SR_HOR_WTSUM                                         0x12D0
#define P12_D1_SR_TEX_PEAKING_GAIN_BLR                              0x12D1
#define P12_D2_SR_TEX_PEAKING_GAIN_POS                              0x12D2
#define P12_D3_SR_TEX_PEAKING_GAIN_NEG                              0x12D3
#define P12_D4_SR_TEX_PEAKING_HV_POS_HSB                            0x12D4
#define P12_D5_SR_TEX_PEAKING_HV_POS_LSB                            0x12D5
#define P12_D6_SR_TEX_PEAKING_HV_NEG_HSB                            0x12D6
#define P12_D7_SR_TEX_PEAKING_HV_NEG_LSB                            0x12D7
#define P12_D8_SR_TEX_PEAKING_LV                                    0x12D8
#define P12_D9_SR_TEX_EDGE_BLEND                                    0x12D9
#define P12_DE_SR_VER_WTSUM                                         0x12DE
#define P12_DF_SR_VER_PEAKING_GAIN_POS                              0x12DF
#define P12_E0_SR_VER_PEAKING_GAIN_NEG                              0x12E0
#define P12_E1_SR_VER_PEAKING_HV_POS                                0x12E1
#define P12_E2_SR_VER_PEAKING_HV_NEG                                0x12E2
#define P12_E3_SR_VER_PEAKING_LV                                    0x12E3
#define P12_E4_SR_VER_EMF                                           0x12E4
#define P12_E5_SR_VER_EMF_MODE                                      0x12E5
#define P12_E6_SR_DUMMY1                                            0x12E6
#define P12_E7_SR_SHP_BIST_CTRL_1                                   0x12E7


//--------------------------------------------------
// M1 SHP Part2 (Page 13)
//--------------------------------------------------
#define P13_A0_SR_CDS_CTRL_0                                        0x13A0
#define P13_A1_SR_CDS_CTRL_1                                        0x13A1
#define P13_A2_SR_CDS_CM1_U_UB0_HSB                                 0x13A2
#define P13_A3_SR_CDS_CM1_U_UB0_LSB                                 0x13A3
#define P13_A4_SR_CDS_CM1_U_LB0_HSB                                 0x13A4
#define P13_A5_SR_CDS_CM1_U_LB0_LSB                                 0x13A5
#define P13_A6_SR_CDS_CM1_V_UB0_HSB                                 0x13A6
#define P13_A7_SR_CDS_CM1_V_UB0_LSB                                 0x13A7
#define P13_A8_SR_CDS_CM1_V_LB0_HSB                                 0x13A8
#define P13_A9_SR_CDS_CM1_V_LB0_LSB                                 0x13A9
#define P13_AA_SR_CDS_CM5_U_UB0_HSB                                 0x13AA
#define P13_AB_SR_CDS_CM5_U_UB0_LSB                                 0x13AB
#define P13_AC_SR_CDS_CM5_U_LB0_HSB                                 0x13AC
#define P13_AD_SR_CDS_CM5_U_LB0_LSB                                 0x13AD
#define P13_AE_SR_CDS_CM5_V_UB0_HSB                                 0x13AE
#define P13_AF_SR_CDS_CM5_V_UB0_LSB                                 0x13AF
#define P13_B0_SR_CDS_CM5_V_LB0_HSB                                 0x13B0
#define P13_B1_SR_CDS_CM5_V_LB0_LSB                                 0x13B1
#define P13_B2_SR_CDS_PEAKING_GAIN_BLR_CM1                          0x13B2
#define P13_B3_SR_CDS_PEAKING_GAIN_POS_CM1                          0x13B3
#define P13_B4_SR_CDS_PEAKING_GAIN_NEG_CM1                          0x13B4
#define P13_B5_SR_CDS_PEAKING_HV_POS_CM1_HSB                        0x13B5
#define P13_B6_SR_CDS_PEAKING_HV_POS_CM1_LSB                        0x13B6
#define P13_B7_SR_CDS_PEAKING_HV_NEG_CM1_HSB                        0x13B7
#define P13_B8_SR_CDS_PEAKING_HV_NEG_CM1_LSB                        0x13B8
#define P13_B9_SR_CDS_PEAKING_LV_CM1                                0x13B9
#define P13_BA_SR_CDS_PEAKING_GAIN_BLR_CM5                          0x13BA
#define P13_BB_SR_CDS_PEAKING_GAIN_POS_CM5                          0x13BB
#define P13_BC_SR_CDS_PEAKING_GAIN_NEG_CM5                          0x13BC
#define P13_BD_SR_CDS_PEAKING_HV_POS_CM5_HSB                        0x13BD
#define P13_BE_SR_CDS_PEAKING_HV_POS_CM5_LSB                        0x13BE
#define P13_BF_SR_CDS_PEAKING_HV_NEG_CM5_HSB                        0x13BF
#define P13_C0_SR_CDS_PEAKING_HV_NEG_CM5_LSB                        0x13C0
#define P13_C1_SR_CDS_PEAKING_LV_CM5                                0x13C1
#define P13_C2_SR_CDS_CM1_U_UB1_HSB                                 0x13C2
#define P13_C3_SR_CDS_CM1_U_UB1_LSB                                 0x13C3
#define P13_C4_SR_CDS_CM1_U_LB1_HSB                                 0x13C4
#define P13_C5_SR_CDS_CM1_U_LB1_LSB                                 0x13C5
#define P13_C6_SR_CDS_CM1_V_UB1_HSB                                 0x13C6
#define P13_C7_SR_CDS_CM1_V_UB1_LSB                                 0x13C7
#define P13_C8_SR_CDS_CM1_V_LB1_HSB                                 0x13C8
#define P13_C9_SR_CDS_CM1_V_LB1_LSB                                 0x13C9
#define P13_CA_SR_CDS_CM5_U_UB1_HSB                                 0x13CA
#define P13_CB_SR_CDS_CM5_U_UB1_LSB                                 0x13CB
#define P13_CC_SR_CDS_CM5_U_LB1_HSB                                 0x13CC
#define P13_CD_SR_CDS_CM5_U_LB1_LSB                                 0x13CD
#define P13_CE_SR_CDS_CM5_V_UB1_HSB                                 0x13CE
#define P13_CF_SR_CDS_CM5_V_UB1_LSB                                 0x13CF
#define P13_D0_SR_CDS_CM5_V_LB1_HSB                                 0x13D0
#define P13_D1_SR_CDS_CM5_V_LB1_LSB                                 0x13D1
#define P13_D4_SR_SKIPIR_CTRL1                                      0x13D4
#define P13_D5_SR_SKIPIR_CTRL2                                      0x13D5
#define P13_D6_SR_SKIPIR_CTRL3                                      0x13D6
#define P13_D7_SR_SKIPIR_CTRL4                                      0x13D7
#define P13_D8_SR_SKIPIR_CTRL5                                      0x13D8
#define P13_D9_SR_SKIPIR_CTRL6                                      0x13D9
#define P13_DA_SR_SKIPIR_ISLETLV_UB                                 0x13DA
#define P13_DB_SR_SKIPIR_ISLETGAIN_UB                               0x13DB
#define P13_DC_SR_SKIPIR_REVLV_UB                                   0x13DC
#define P13_DD_SR_SKIPIR_REVGAIN_UB                                 0x13DD
#define P13_DE_SR_SKIPIR_DEBUG                                      0x13DE
#define P13_DF_SR_DNOISE_CTRL1                                      0x13DF
#define P13_E0_SR_DNOISE_CTRL2                                      0x13E0
#define P13_E1_SR_DNOISE_GAIN_UB                                    0x13E1
#define P13_E2_SR_DNOISE_LV_UB                                      0x13E2
#define P13_E3_SR_DNOISE_NOISE_GAIN_TH                              0x13E3
#define P13_E4_SR_DNOISE_NOISE_LV_TH                                0x13E4
#define P13_E5_SR_ECS_CTRL_0                                        0x13E5
#define P13_E6_SR_ECS_CTRL_1                                        0x13E6
#define P13_E7_SR_ECS_NOISE_LEVEL_HSB                               0x13E7
#define P13_E8_SR_ECS_NOISE_LEVEL_LSB                               0x13E8
#define P13_E9_SR_ECS_CTR_TH_HSB                                    0x13E9
#define P13_EA_SR_ECS_CTR_TH_LSB                                    0x13EA
#define P13_EB_SR_ECS_SAWTOOTH_TH_HSB                               0x13EB
#define P13_EC_SR_ECS_SAWTOOTH_TH_LSB                               0x13EC
#define P13_ED_SR_MF_UB                                             0x13ED
#define P13_EE_SR_MF_LB                                             0x13EE
#define P13_EF_SR_MF_WT                                             0x13EF
#define P13_F0_SR_TL_THD_MSB                                        0x13F0
#define P13_F1_SR_TL_THD_LSB                                        0x13F1
#define P13_F2_SR_TL_OFFSET                                         0x13F2
#define P13_F3_SR_BG_THD_MSB                                        0x13F3
#define P13_F4_SR_BG_THD_LSB                                        0x13F4
#define P13_F5_SR_BG_OFFSET                                         0x13F5
#define P13_F6_SR_SUMDIFF_RSFT                                      0x13F6
#define P13_F7_SR_SUMDIFF_THD                                       0x13F7
#define P13_F8_SR_SUMDIFF_OFFSET                                    0x13F8
#define P13_F9_SR_TL_GAIN                                           0x13F9
#define P13_FA_SR_TL_LEN                                            0x13FA
#define P13_FB_SR_DUMMY2                                            0x13FB


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
// D-Domain Color Conversion (Page 14)
//--------------------------------------------------
#define P14_40_SR_BT2020_COEF_H11_HSB                               0x1440
#define P14_41_SR_BT2020_COEF_H11_MSB                               0x1441
#define P14_42_SR_BT2020_COEF_H11_LSB                               0x1442
#define P14_43_SR_BT2020_COEF_H21_HSB                               0x1443
#define P14_44_SR_BT2020_COEF_H21_MSB                               0x1444
#define P14_45_SR_BT2020_COEF_H21_LSB                               0x1445
#define P14_46_SR_BT2020_COEF_H31_HSB                               0x1446
#define P14_47_SR_BT2020_COEF_H31_MSB                               0x1447
#define P14_48_SR_BT2020_COEF_H31_LSB                               0x1448
#define P14_49_SR_BT2020_COEF_H12A_HSB                              0x1449
#define P14_4A_SR_BT2020_COEF_H12A_MSB                              0x144A
#define P14_4B_SR_BT2020_COEF_H12A_LSB                              0x144B
#define P14_4C_SR_BT2020_COEF_H22A_HSB                              0x144C
#define P14_4D_SR_BT2020_COEF_H22A_MSB                              0x144D
#define P14_4E_SR_BT2020_COEF_H22A_LSB                              0x144E
#define P14_4F_SR_BT2020_COEF_H32A_HSB                              0x144F
#define P14_50_SR_BT2020_COEF_H32A_MSB                              0x1450
#define P14_51_SR_BT2020_COEF_H32A_LSB                              0x1451
#define P14_52_SR_BT2020_COEF_H13A_HSB                              0x1452
#define P14_53_SR_BT2020_COEF_H13A_MSB                              0x1453
#define P14_54_SR_BT2020_COEF_H13A_LSB                              0x1454
#define P14_55_SR_BT2020_COEF_H23A_HSB                              0x1455
#define P14_56_SR_BT2020_COEF_H23A_MSB                              0x1456
#define P14_57_SR_BT2020_COEF_H23A_LSB                              0x1457
#define P14_58_SR_BT2020_COEF_H33A_HSB                              0x1458
#define P14_59_SR_BT2020_COEF_H33A_MSB                              0x1459
#define P14_5A_SR_BT2020_COEF_H33A_LSB                              0x145A
#define P14_5B_SR_BT2020_COEF_H12B_HSB                              0x145B
#define P14_5C_SR_BT2020_COEF_H12B_MSB                              0x145C
#define P14_5D_SR_BT2020_COEF_H12B_LSB                              0x145D
#define P14_5E_SR_BT2020_COEF_H22B_HSB                              0x145E
#define P14_5F_SR_BT2020_COEF_H22B_MSB                              0x145F
#define P14_60_SR_BT2020_COEF_H22B_LSB                              0x1460
#define P14_61_SR_BT2020_COEF_H32B_HSB                              0x1461
#define P14_62_SR_BT2020_COEF_H32B_MSB                              0x1462
#define P14_63_SR_BT2020_COEF_H32B_LSB                              0x1463
#define P14_64_SR_BT2020_COEF_H13B_HSB                              0x1464
#define P14_65_SR_BT2020_COEF_H13B_MSB                              0x1465
#define P14_66_SR_BT2020_COEF_H13B_LSB                              0x1466
#define P14_67_SR_BT2020_COEF_H23B_HSB                              0x1467
#define P14_68_SR_BT2020_COEF_H23B_MSB                              0x1468
#define P14_69_SR_BT2020_COEF_H23B_LSB                              0x1469
#define P14_6A_SR_BT2020_COEF_H33B_HSB                              0x146A
#define P14_6B_SR_BT2020_COEF_H33B_MSB                              0x146B
#define P14_6C_SR_BT2020_COEF_H33B_LSB                              0x146C
#define P14_6D_SR_BT2020_COEF_CB_THD_MSB                            0x146D
#define P14_6E_SR_BT2020_COEF_CB_THD_LSB                            0x146E
#define P14_6F_SR_BT2020_COEF_CR_THD_MSB                            0x146F
#define P14_70_SR_BT2020_COEF_CR_THD_LSB                            0x1470
#define P14_71_SR_BT2020_COEF_DUMMY                                 0x1471
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
#define P15_2C_LVDS_PORTA_CTRL12                                    0x152C
#define P15_2D_LVDS_PORTA_CTRL13                                    0x152D
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
#define P15_3C_LVDS_PORTB_CTRL12                                    0x153C
#define P15_3D_LVDS_PORTB_CTRL13                                    0x153D


//--------------------------------------------------
// Embedded Timing Controller (Page 15)
//--------------------------------------------------
#define P15_A3_TCON_ADDR                                            0x15A3
#define P15_A4_TCON_DATA                                            0x15A4


//--------------------------------------------------
// M1 On-line Measure Block Overview (Page 16)
//--------------------------------------------------
#define P16_00_SYNC_SELECT                                          0x1600
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
// DPTx On-line Measure Block Overview (Page 16)
//--------------------------------------------------
#define P16_41_DPTX_MEAS_CTL0                                       0x1641
#define P16_42_DPTX_MEAS_CTL1                                       0x1642
#define P16_43_DPTX_MEAS_ERROR_FLG0                                 0x1643
#define P16_44_DPTX_MEAS_ERROR_FLG1                                 0x1644
#define P16_45_DPTX_MEAS_HS_PERIOD_A_M                              0x1645
#define P16_46_DPTX_MEAS_HS_PERIOD_A_L                              0x1646
#define P16_47_DPTX_MEAS_HS_PERIOD_FRA_A                            0x1647
#define P16_48_DPTX_MEAS_VS_PERIOD_A_M                              0x1648
#define P16_49_DPTX_MEAS_VS_PERIOD_A_L                              0x1649
#define P16_4A_DPTX_MEAS_HS_PULSE_A_M                               0x164A
#define P16_4B_DPTX_MEAS_HS_PULSE_A_L                               0x164B
#define P16_4C_DPTX_MEAS_VS_PULSE_A_M                               0x164C
#define P16_4D_DPTX_MEAS_VS_PULSE_A_L                               0x164D
#define P16_4E_DPTX_MEAS_HS_PERIOD_D_M                              0x164E
#define P16_4F_DPTX_MEAS_HS_PERIOD_D_L                              0x164F
#define P16_50_DPTX_MEAS_HS_PERIOD_FRA_D                            0x1650
#define P16_51_DPTX_MEAS_VS_PERIOD_D_M                              0x1651
#define P16_52_DPTX_MEAS_VS_PERIOD_D_L                              0x1652
#define P16_53_DPTX_MEAS_HS_PULSE_D_M                               0x1653
#define P16_54_DPTX_MEAS_HS_PULSE_D_L                               0x1654
#define P16_55_DPTX_MEAS_HS_VS_DELTA_CTL                            0x1655
#define P16_56_DPTX_MEAS_HS_VS_DELTA_IRQ                            0x1656
#define P16_57_DPTX_MEAS_HS_VS_DELTA_WD                             0x1657
#define P16_58_DPTX_MEAS_HS_VS_ERROR_WD                             0x1658
#define P16_59_DPTX_MEAS_HS_VS_ERROR_IRQ                            0x1659
#define P16_5A_DPTX_MEAS2_HS_VS_DLY                                 0x165A
#define P16_5C_DPTX_MEASURE_DUMMY0                                  0x165C
#define P16_5D_DPTX_MEASURE_DUMMY1                                  0x165D


//--------------------------------------------------
// DPTX VGIP (Page 16)
//--------------------------------------------------
#define P16_A0_DPTX_VGIP_CTRL                                       0x16A0
#define P16_A1_DPTX_VGIP_SIGINV                                     0x16A1
#define P16_A2_DPTX_VGIP_DELAY_CTRL                                 0x16A2
#define P16_A3_DPTX_VGIP_ODD_CTRL                                   0x16A3
#define P16_A4_DPTX_DUMMY                                           0x16A4
#define P16_AA_DPTX_VGIP_FIELD_DETECT                               0x16AA


//--------------------------------------------------
// DPTX Image Auto Function (Page 16)
//--------------------------------------------------
#define P16_C0_DPTX_H_BOUNDARY_H                                    0x16C0
#define P16_C1_DPTX_H_BOUNDARY_STA_L                                0x16C1
#define P16_C2_DPTX_H_BOUNDARY_END_L                                0x16C2
#define P16_C3_DPTX_V_BOUNDARY_H                                    0x16C3
#define P16_C4_DPTX_V_BOUNDARY_STA_L                                0x16C4
#define P16_C5_DPTX_V_BOUNDARY_END_L                                0x16C5
#define P16_C6_DPTX_RED_NOISE_MARGIN                                0x16C6
#define P16_C7_DPTX_GRN_NOISE_MARGIN                                0x16C7
#define P16_C8_DPTX_BLU_NOISE_MARGIN                                0x16C8
#define P16_C9_DPTX_DIFF_THRESHOLD                                  0x16C9
#define P16_CA_DPTX_AUTO_ADJ_CTRL0                                  0x16CA
#define P16_CB_DPTX_HW_AUTO_PHASE_CTRL0                             0x16CB
#define P16_CC_DPTX_AUTO_DUMMY                                      0x16CC
#define P16_CD_DPTX_AUTO_ADJ_CTRL1                                  0x16CD
#define P16_CE_DPTX_VER_START_END_H                                 0x16CE
#define P16_CF_DPTX_VER_START_L                                     0x16CF
#define P16_D0_DPTX_VER_END_L                                       0x16D0
#define P16_D1_DPTX_H_START_END_H                                   0x16D1
#define P16_D2_DPTX_H_START_L                                       0x16D2
#define P16_D3_DPTX_H_END_L                                         0x16D3
#define P16_D4_DPTX_AUTO_PHASE_3                                    0x16D4
#define P16_D5_DPTX_AUTO_PHASE_2                                    0x16D5
#define P16_D6_DPTX_AUTO_PHASE_1                                    0x16D6
#define P16_D7_DPTX_AUTO_PHASE_0                                    0x16D7


//--------------------------------------------------
// Overall CEC1 Function Block1 (Page 18)
//--------------------------------------------------
#define P18_A0_CEC1_CR0_1                                           0x18A0
#define P18_A1_CEC1_CR0_2                                           0x18A1
#define P18_A2_CEC1_CR0_3                                           0x18A2
#define P18_A3_CEC1_CR0_4                                           0x18A3
#define P18_A4_CEC1_CR0_5                                           0x18A4
#define P18_A5_CEC1_CR0_6                                           0x18A5
#define P18_A6_CEC1_CR0_7                                           0x18A6
#define P18_A7_CEC1_CR0_RSV_1                                       0x18A7
#define P18_A8_CEC1_RTCR0_1                                         0x18A8
#define P18_A9_CEC1_RTCR0_2                                         0x18A9
#define P18_AA_CEC1_RTCR0_RSV_0                                     0x18AA
#define P18_B0_CEC1_RXCR0_1                                         0x18B0
#define P18_B1_CEC1_RXCR0_2                                         0x18B1
#define P18_B2_CEC1_RTCR0_RSV_1                                     0x18B2
#define P18_B3_CEC1_RTCR1_RSV_0                                     0x18B3
#define P18_B4_CEC1_TXCR0_1                                         0x18B4
#define P18_B5_CEC1_TXCR0_2                                         0x18B5
#define P18_B6_CEC1_TX_CR0_3                                        0x18B6
#define P18_B7_CEC1_TXCR0_RSV_0                                     0x18B7
#define P18_B8_CEC1_TXCR0_RSV_1                                     0x18B8
#define P18_B9_CEC1_TXDR0                                           0x18B9
#define P18_BA_CEC1_TXDR0_RSV_0                                     0x18BA
#define P18_C0_CEC1_TXDR1_1                                         0x18C0
#define P18_C1_CEC1_TXDR1_2                                         0x18C1
#define P18_C2_CEC1_TXDR1_3                                         0x18C2
#define P18_C3_CEC1_TXDR1_4                                         0x18C3
#define P18_C4_CEC1_TXDR2_1                                         0x18C4
#define P18_C5_CEC1_TXDR2_2                                         0x18C5
#define P18_C6_CEC1_TXDR2_3                                         0x18C6
#define P18_C7_CEC1_TXDR2_4                                         0x18C7
#define P18_C8_CEC1_TXDR3_1                                         0x18C8
#define P18_C9_CEC1_TXDR3_2                                         0x18C9
#define P18_CA_CEC1_TXDR3_3                                         0x18CA
#define P18_CB_CEC1_TXDR3_4                                         0x18CB
#define P18_CC_CEC1_TXDR4_1                                         0x18CC
#define P18_CD_CEC1_TXDR4_2                                         0x18CD
#define P18_CE_CEC1_TXDR4_3                                         0x18CE
#define P18_CF_CEC1_TXDR4_4                                         0x18CF
#define P18_D0_CEC1_TXDR_FIFO_RSV_0                                 0x18D0
#define P18_D1_CEC1_TXDR_FIFO_RSV_1                                 0x18D1
#define P18_D2_CEC1_TXDR_FIFO_RSV_2                                 0x18D2
#define P18_D3_CEC1_RXDR1_1                                         0x18D3
#define P18_D4_CEC1_RXDR1_2                                         0x18D4
#define P18_D5_CEC1_RXDR1_3                                         0x18D5
#define P18_D6_CEC1_RXDR1_4                                         0x18D6
#define P18_D7_CEC1_RXDR2_1                                         0x18D7
#define P18_D8_CEC1_RXDR2_2                                         0x18D8
#define P18_D9_CEC1_RXDR2_3                                         0x18D9
#define P18_DA_CEC1_RXDR2_4                                         0x18DA
#define P18_DB_CEC1_RXDR3_1                                         0x18DB
#define P18_DC_CEC1_RXDR3_2                                         0x18DC
#define P18_DD_CEC1_RXDR3_3                                         0x18DD
#define P18_DE_CEC1_RXDR3_4                                         0x18DE
#define P18_DF_CEC1_RXDR4_1                                         0x18DF
#define P18_E0_CEC1_RXDR4_2                                         0x18E0
#define P18_E1_CEC1_RXDR4_3                                         0x18E1
#define P18_E2_CEC1_RXDR4_4                                         0x18E2
#define P18_E3_CEC_RX_FIFO_RSV_0                                    0x18E3
#define P18_E4_CEC1_RX_FIFO_RSV_1                                   0x18E4
#define P18_E5_CEC1_RXTCR0_1                                        0x18E5
#define P18_E6_CEC1_RXTCR0_2                                        0x18E6
#define P18_E7_CEC1_RXTCR0_3                                        0x18E7
#define P18_E8_CEC1_RXTCR0_4                                        0x18E8
#define P18_E9_CEC1_RXTCR0_5                                        0x18E9
#define P18_EA_CEC1_RTCR1_RSV_1                                     0x18EA
#define P18_EF_CEC1_TXTCR0_1                                        0x18EF
#define P18_F1_CEC1_TXTCR0_2                                        0x18F1
#define P18_F2_CEC1_TXTCR1_1                                        0x18F2
#define P18_F3_CEC1_TXTCR1_2                                        0x18F3
#define P18_F4_CEC1_TXTCR1_3                                        0x18F4
#define P18_F5_CEC1_RXTCR1_ACK_0                                    0x18F5
#define P18_F6_CEC1_RXTCR1_ACK_1                                    0x18F6
#define P18_F7_CEC1_RXTCR1_ACK_2                                    0x18F7
#define P18_F8_CEC1_RXTCR1_ERR                                      0x18F8
#define P18_F9_CEC1_RXTCR1_RSV_0                                    0x18F9
#define P18_FA_CEC1_TIMING_CTRL_DATA                                0x18FA
#define P18_FB_CEC1_TIMING_CTRL_0                                   0x18FB
#define P18_FC_CEC1_TIMING_CTRL_1                                   0x18FC
#define P18_FD_CEC1_TIMING_CTRL_COUNTER_0                           0x18FD
#define P18_FE_CEC1_TIMING_CTRL_COUNTER_1                           0x18FE


//--------------------------------------------------
// Overall CEC1 Function Block2 (Page 19)
//--------------------------------------------------
#define P19_A0_GDI_CEC1_COMPARE_OPCODE_01                           0x19A0
#define P19_A1_GDI_CEC1_SEND_OPCODE_01                              0x19A1
#define P19_A2_GDI_CEC1_SEND_OPERAND_NUMBER_01                      0x19A2
#define P19_A3_GDI_CEC1_OPERAND_01                                  0x19A3
#define P19_A4_GDI_CEC1_OPERAND_02                                  0x19A4
#define P19_A5_GDI_CEC1_OPERAND_03                                  0x19A5
#define P19_A6_GDI_CEC1_COMOP01_RSV_0                               0x19A6
#define P19_A7_GDI_CEC1_COMOP01_RSV_1                               0x19A7
#define P19_A8_GDI_CEC1_COMPARE_OPCODE_02                           0x19A8
#define P19_A9_GDI_CEC1_SEND_OPCODE_02                              0x19A9
#define P19_AA_GDI_CEC1_SEND_OPERAND_NUMBER_02                      0x19AA
#define P19_AB_GDI_CEC1_OPERAND_04                                  0x19AB
#define P19_AC_GDI_CEC1_OPERAND_05                                  0x19AC
#define P19_AD_GDI_CEC1_OPERAND_06                                  0x19AD
#define P19_AE_GDI_CEC1_COMOP02_RSV_0                               0x19AE
#define P19_AF_GDI_CEC1_COMOP02_RSV_1                               0x19AF
#define P19_B0_GDI_CEC1_COMPARE_OPCODE_03                           0x19B0
#define P19_B1_GDI_CEC1_SEND_OPCODE_03                              0x19B1
#define P19_B2_GDI_CEC1_SEND_OPERAND_NUMBER_03                      0x19B2
#define P19_B3_GDI_CEC1_OPERAND_07                                  0x19B3
#define P19_B4_GDI_CEC1_OPERAND_08                                  0x19B4
#define P19_B5_GDI_CEC1_OPERAND_09                                  0x19B5
#define P19_B6_GDI_CEC1_COMOP03_RSV_0                               0x19B6
#define P19_B7_GDI_CEC1_COMOP03_RSV_1                               0x19B7
#define P19_B8_GDI_CEC1_COMPARE_OPCODE_04                           0x19B8
#define P19_B9_GDI_CEC1_SEND_OPCODE_04                              0x19B9
#define P19_BA_GDI_CEC1_SEND_OPERAND_NUMBER_04                      0x19BA
#define P19_BB_GDI_CEC1_OPERAND_10                                  0x19BB
#define P19_BC_GDI_CEC1_OPERAND_11                                  0x19BC
#define P19_BD_GDI_CEC1_OPERAND_12                                  0x19BD
#define P19_BE_GDI_CEC1_COMOP04_RSV_0                               0x19BE
#define P19_BF_GDI_CEC1_COMOP04_RSV_1                               0x19BF
#define P19_C0_GDI_CEC1_COMPARE_OPCODE_05                           0x19C0
#define P19_C1_GDI_CEC1_COMPARE_OPCODE_06                           0x19C1
#define P19_C2_GDI_CEC1_COMPARE_OPCODE_07                           0x19C2
#define P19_C3_GDI_CEC1_COMPARE_OPCODE_08                           0x19C3
#define P19_C4_GDI_CEC1_COMPARE_OPCODE_09                           0x19C4
#define P19_C5_GDI_CEC1_COMPARE_OPCODE_10                           0x19C5
#define P19_C6_GDI_CEC1_COMPARE_OPCODE_11                           0x19C6
#define P19_C7_GDI_CEC1_COMPARE_OPCODE_12                           0x19C7
#define P19_C8_GDI_CEC1_COMPARE_OPCODE_13                           0x19C8
#define P19_C9_GDI_CEC1_COMPARE_OPCODE_14                           0x19C9
#define P19_CA_GDI_CEC1_COMPARE_OPCODE_15                           0x19CA
#define P19_CB_GDI_CEC1_TXOP_RSV_0                                  0x19CB
#define P19_CC_GDI_CEC1_TXOP_RSV_1                                  0x19CC
#define P19_CD_GDI_CEC1_TXOP_RSV_2                                  0x19CD
#define P19_D0_GDI_CEC1_OPCODE_ENABLE_1                             0x19D0
#define P19_D1_GDI_CEC1_OPCODE_ENABLE_2                             0x19D1
#define P19_D2_GDI_CEC1_HIT_OPCODE_0                                0x19D2
#define P19_D3_GDI_CEC1_HIT_OPCODE_1                                0x19D3
#define P19_D4_GDI_CEC1_HIT_OPCODE_RSV_0                            0x19D4
#define P19_D5_GDI_CEC1_HIT_OPCODE_RSV_1                            0x19D5
#define P19_D6_CEC1_FUN_DEBUG_0                                     0x19D6
#define P19_D7_CEC1_FUN_RESERVED_1                                  0x19D7
#define P19_D8_CEC1_WAIT_FALLING_15_8                               0x19D8
#define P19_D9_CEC1_WAIT_FALLING_7_0                                0x19D9
#define P19_DA_CEC1_FUN_RESERVED_4                                  0x19DA
#define P19_DB_CEC1_FUN_RESERVED_5                                  0x19DB
#define P19_E0_CEC1_POWER_SAVING_MODE                               0x19E0
#define P19_E1_CEC1_RTCR0_RSV_0                                     0x19E1
#define P19_E2_CEC1_RTCR0_RSV_1                                     0x19E2
#define P19_E3_CEC1_INTCR_01                                        0x19E3
#define P19_E4_CEC1_INTCR_02                                        0x19E4
#define P19_E5_CEC1_PS_RSV_0                                        0x19E5
#define P19_E6_CEC1_PS_RSV_1                                        0x19E6
#define P19_E7_CEC1_PS_RESERVED_1                                   0x19E7
#define P19_E8_CEC1_PS_RESERVED_2                                   0x19E8
#define P19_E9_CEC1_PS_RESERVED_3                                   0x19E9
#define P19_EA_CEC1_PS_RESERVED_4                                   0x19EA
#define P19_EB_CEC1_PS_RESERVED_5                                   0x19EB
#define P19_F0_GDI_CEC1_ANALOG_1                                    0x19F0
#define P19_F1_CEC1_POWER_SELECT                                    0x19F1
#define P19_F2_CEC1_DRV_CTRL                                        0x19F2
#define P19_F3_CEC1_PSM                                             0x19F3
#define P19_F4_CEC_RESERVED                                         0x19F4
#define P19_F5_CEC_PSM                                              0x19F5


//--------------------------------------------------
// D0 GDI PHY Power On Region (Page 1D)
//--------------------------------------------------
#define P1D_0A_DPHY_DEBUG                                           0x1D0A
#define P1D_0B_SDM_00                                               0x1D0B
#define P1D_0C_SDM_01                                               0x1D0C
#define P1D_0D_SDM_02                                               0x1D0D
#define P1D_0E_SDM_03                                               0x1D0E
#define P1D_0F_WD                                                   0x1D0F
#define P1D_10_EQEN_TIMER                                           0x1D10
#define P1D_11_DATA_TIMER                                           0x1D11
#define P1D_12_ANA_CDR                                              0x1D12
#define P1D_13_PHY_RESERVED                                         0x1D13
#define P1D_17_BANDGAP_03                                           0x1D17
#define P1D_18_IMPEDANCE_00                                         0x1D18
#define P1D_19_IMPEDANCE_01                                         0x1D19
#define P1D_1A_CMU_00                                               0x1D1A
#define P1D_1B_CMU_01                                               0x1D1B
#define P1D_1C_CMU_02                                               0x1D1C
#define P1D_1D_CMU_03                                               0x1D1D
#define P1D_1E_CMU_04                                               0x1D1E
#define P1D_1F_CMU_05                                               0x1D1F
#define P1D_20_CMU_06                                               0x1D20
#define P1D_21_CMU_07                                               0x1D21
#define P1D_22_CMU_08                                               0x1D22
#define P1D_23_CMU_09                                               0x1D23
#define P1D_24_KOFFSET_00                                           0x1D24
#define P1D_25_KOFFSET_01                                           0x1D25
#define P1D_26_KOFFSET_02                                           0x1D26
#define P1D_27_KOFFSET_03                                           0x1D27
#define P1D_28_KOFFSET_04                                           0x1D28
#define P1D_29_KOFFSET_05                                           0x1D29
#define P1D_2A_KOFFSET_06                                           0x1D2A
#define P1D_2B_KOFFSET_07                                           0x1D2B
#define P1D_2C_ANA_CDR_01                                           0x1D2C
#define P1D_2D_ANA_CDR_02                                           0x1D2D
#define P1D_2E_ANA_CDR_03                                           0x1D2E
#define P1D_2F_ANA_CDR_04                                           0x1D2F
#define P1D_30_ANA_CDR_05                                           0x1D30
#define P1D_31_ANA_CDR_06                                           0x1D31
#define P1D_32_ANA_CDR_07                                           0x1D32
#define P1D_33_ANA_CDR_08                                           0x1D33
#define P1D_34_ANA_CDR_09                                           0x1D34
#define P1D_35_ANA_CDR_10                                           0x1D35
#define P1D_36_ANA_CDR_11                                           0x1D36
#define P1D_37_ANA_CDR_12                                           0x1D37
#define P1D_38_ANA_CDR_13                                           0x1D38
#define P1D_39_ANA_CDR_14                                           0x1D39
#define P1D_3A_TMDS_RESET                                           0x1D3A
#define P1D_3B_TMDS_CONT_00                                         0x1D3B
#define P1D_3C_TMDS_CONT_01                                         0x1D3C
#define P1D_3D_TMDS_CONT_02                                         0x1D3D
#define P1D_3E_TMDS_CONT_03                                         0x1D3E
#define P1D_3F_TMDS_CONT_04                                         0x1D3F
#define P1D_40_EN_01                                                0x1D40
#define P1D_41_EN_02                                                0x1D41
#define P1D_42_EN_03                                                0x1D42
#define P1D_43_EN_04                                                0x1D43
#define P1D_44_ST_01                                                0x1D44
#define P1D_45_ST_02                                                0x1D45
#define P1D_46_ST_03                                                0x1D46
#define P1D_47_ST_04                                                0x1D47
#define P1D_48_ST_05                                                0x1D48
#define P1D_49_ST_06                                                0x1D49
#define P1D_4A_ST_07                                                0x1D4A
#define P1D_4B_ST_08                                                0x1D4B
#define P1D_4C_ST_09                                                0x1D4C
#define P1D_4D_ST_10                                                0x1D4D
#define P1D_4E_ST_11                                                0x1D4E
#define P1D_4F_PI_MANUAL                                            0x1D4F
#define P1D_50_CDR_00                                               0x1D50
#define P1D_51_CDR_01                                               0x1D51
#define P1D_52_CDR_02                                               0x1D52
#define P1D_53_CDR_03                                               0x1D53
#define P1D_54_ACC_00                                               0x1D54
#define P1D_55_ACC_01                                               0x1D55
#define P1D_56_KI_L0                                                0x1D56
#define P1D_57_KI_L1                                                0x1D57
#define P1D_58_KI_L2                                                0x1D58
#define P1D_59_KI_L3                                                0x1D59
#define P1D_5A_KP_L0                                                0x1D5A
#define P1D_5B_KP_L1                                                0x1D5B
#define P1D_5C_KP_L2                                                0x1D5C
#define P1D_5D_KP_L3                                                0x1D5D


//--------------------------------------------------
// GDI PHY Bandgap (Page 1D)
//--------------------------------------------------
#define P1D_14_BANDGAP_00                                           0x1D14
#define P1D_15_BANDGAP_01                                           0x1D15
#define P1D_16_BANDGAP_02                                           0x1D16


//--------------------------------------------------
// D0 GDI DFE (Page 1D)
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
#define P1D_EE_GRAY_DEC_1                                           0x1DEE
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
// Rotation (Page 20)
//--------------------------------------------------
#define P20_F0_ROTATION_CTRL0                                       0x20F0
#define P20_F1_ROTATION_IN_WID_H                                    0x20F1
#define P20_F2_ROTATION_IN_WID_L                                    0x20F2
#define P20_F8_ROTATION_BIST_CTRL1                                  0x20F8
#define P20_F9_ROTATION_BIST_CTRL2                                  0x20F9
#define P20_FA_ROTATION_BIST_CTRL3                                  0x20FA
#define P20_FE_DUMMY_1                                              0x20FE
#define P20_FF_DUMMY_2                                              0x20FF


//--------------------------------------------------
// Dump_Register (Page 21)
//--------------------------------------------------
#define P21_00_DUMP_REG_CTRL                                        0x2100
#define P21_01_PAGE_SEL                                             0x2101
#define P21_02_PAGE_MASK                                            0x2102
#define P21_03_MADR_SEL                                             0x2103
#define P21_04_MADR_MASK                                            0x2104
#define P21_05_DUMP_START                                           0x2105
#define P21_10_DUMP_COUNTER                                         0x2110
#define P21_11_FIFO_STATUS                                          0x2111
#define P21_12_RW_FLAG_H                                            0x2112
#define P21_13_RW_FLAG_L                                            0x2113
#define P21_20_BUF0                                                 0x2120
#define P21_21_BUF1                                                 0x2121
#define P21_22_BUF2                                                 0x2122
#define P21_23_BUF3                                                 0x2123
#define P21_24_BUF4                                                 0x2124
#define P21_25_BUF5                                                 0x2125
#define P21_26_BUF6                                                 0x2126
#define P21_27_BUF7                                                 0x2127
#define P21_28_BUF8                                                 0x2128
#define P21_29_BUF9                                                 0x2129
#define P21_2A_BUF10                                                0x212A
#define P21_2B_BUF11                                                0x212B
#define P21_2C_TX_SETTING                                           0x212C


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
// SPI Module Interface (Page 22)
//--------------------------------------------------
#define P22_A0_SPI_TRANSACTION_EN                                   0x22A0
#define P22_A1_SPI_TRANSACTION_STATUS                               0x22A1
#define P22_A2_SPI_MODULE_CTRL                                      0x22A2
#define P22_A3_SPI_MODULE_SETTING                                   0x22A3
#define P22_A4_SPI_SCLK_DIV                                         0x22A4
#define P22_A5_SPI_S0_PROTOCOL_MODE                                 0x22A5
#define P22_A6_SPI_S0_WRITE_LENGTH                                  0x22A6
#define P22_A7_SPI_S0_READ_LENGTH                                   0x22A7
#define P22_A8_SPI_S0_STATUS                                        0x22A8
#define P22_A9_SPI_S0_MASK                                          0x22A9
#define P22_AA_SPI_S0_STOP_CON                                      0x22AA
#define P22_AB_SPI_S0_TX_BUF                                        0x22AB
#define P22_AC_SPI_S0_RX_BUF_READ_ADR                               0x22AC
#define P22_AD_SPI_S0_RX_BUF                                        0x22AD
#define P22_AE_SPI_S0_TX_BUF_REMAIN                                 0x22AE
#define P22_AF_SPI_S0_RX_BUF_REMAIN                                 0x22AF
#define P22_B0_SPI_S0_TX_RX_BUF_FLAG                                0x22B0
#define P22_B1_SPI_S0_TX_RX_BUF_IRQ_EN                              0x22B1
#define P22_B2_SPI_S0_CMD_DATA                                      0x22B2
#define P22_B3_SPI_S1_CMD_DATA                                      0x22B3
#define P22_B4_SPI_S01_CMD_SETTING                                  0x22B4
#define P22_B5_SPI_S1_PROTOCOL_MODE                                 0x22B5
#define P22_B6_SPI_S1_WRITE_LENGTH                                  0x22B6
#define P22_B7_SPI_S1_READ_LENGTH                                   0x22B7
#define P22_B8_SPI_S1_STATUS                                        0x22B8
#define P22_B9_SPI_S1_MASK                                          0x22B9
#define P22_BA_SPI_S1_STOP_CON                                      0x22BA
#define P22_BB_SPI_S01_STATUS_EN                                    0x22BB
#define P22_BC_SPI_VARIANT_MODE_SETTINGS                            0x22BC
#define P22_BD_SPI_S1_TX_BUF                                        0x22BD
#define P22_BE_SPI_S1_RX_BUF_READ_ADR                               0x22BE
#define P22_BF_SPI_S1_RX_BUF                                        0x22BF
#define P22_C0_SPI_S1_TX_BUF_REMAIN                                 0x22C0
#define P22_C1_SPI_S1_RX_BUF_REMAIN                                 0x22C1
#define P22_C2_SPI_S1_TX_RX_BUF_FLAG                                0x22C2
#define P22_C3_SPI_S1_TX_RX_BUF_IRQ_EN                              0x22C3
#define P22_C4_SPI_BUF_CLR                                          0x22C4
#define P22_C5_SPI_DUMMY                                            0x22C5
#define P22_C6_SPI_CS_AUTO_CTRL                                     0x22C6
#define P22_C7_SPI_CS0_CTRL                                         0x22C7
#define P22_C8_SPI_CS1_CTRL                                         0x22C8
#define P22_C9_SPI_SCLK_CTRL                                        0x22C9
#define P22_CA_SPI_XRAM_TX_CTR0                                     0x22CA
#define P22_CB_SPI_CNT_H                                            0x22CB
#define P22_CC_SPI_CNT_M                                            0x22CC
#define P22_CD_SPI_CNT_L                                            0x22CD
#define P22_D9_SPI_CNT_CTRL                                         0x22D9
#define P22_DA_SPI_DEBUG_CTRL                                       0x22DA


//--------------------------------------------------
// IR-DA Module (Page 23)
//--------------------------------------------------
#define P23_A0_IR_PSR0                                              0x23A0
#define P23_A1_IR_PSR1                                              0x23A1
#define P23_A2_IR_PSR2                                              0x23A2
#define P23_A3_IR_PSR3                                              0x23A3
#define P23_A4_IR_PER0                                              0x23A4
#define P23_A5_IR_PER1                                              0x23A5
#define P23_A6_IR_PER2                                              0x23A6
#define P23_A7_IR_PER3                                              0x23A7
#define P23_A8_IR_SF0                                               0x23A8
#define P23_A9_IR_SF1                                               0x23A9
#define P23_AA_IR_SF2                                               0x23AA
#define P23_AB_IR_SF3                                               0x23AB
#define P23_AC_IR_DPIR0                                             0x23AC
#define P23_AD_IR_DPIR1                                             0x23AD
#define P23_AE_IR_DPIR2                                             0x23AE
#define P23_AF_IR_DPIR3                                             0x23AF
#define P23_B0_IR_CR0                                               0x23B0
#define P23_B1_IR_CR1                                               0x23B1
#define P23_B2_IR_CR2                                               0x23B2
#define P23_B3_IR_CR3                                               0x23B3
#define P23_B4_IR_RP0                                               0x23B4
#define P23_B5_IR_RP1                                               0x23B5
#define P23_B6_IR_RP2                                               0x23B6
#define P23_B7_IR_RP3                                               0x23B7
#define P23_B8_IR_SR0                                               0x23B8
#define P23_B9_IR_SR1                                               0x23B9
#define P23_BA_IR_SR2                                               0x23BA
#define P23_BB_IR_SR3                                               0x23BB
#define P23_BC_IR_RAW_CTR0                                          0x23BC
#define P23_BD_IR_RAW_CTR1                                          0x23BD
#define P23_BE_IR_RAW_CTR2                                          0x23BE
#define P23_BF_IR_RAW_CTR3                                          0x23BF
#define P23_C0_IR_RAW_FF0                                           0x23C0
#define P23_C1_IR_RAW_FF1                                           0x23C1
#define P23_C2_IR_RAW_FF2                                           0x23C2
#define P23_C3_IR_RAW_FF3                                           0x23C3
#define P23_C4_IR_RAW_SAMPLE_TIME0                                  0x23C4
#define P23_C5_IR_RAW_SAMPLE_TIME1                                  0x23C5
#define P23_C6_IR_RAW_SAMPLE_TIME2                                  0x23C6
#define P23_C7_IR_RAW_SAMPLE_TIME3                                  0x23C7
#define P23_C8_IR_RAW_WL0                                           0x23C8
#define P23_C9_IR_RAW_WL1                                           0x23C9
#define P23_CA_IR_RAW_WL2                                           0x23CA
#define P23_CB_IR_RAW_WL3                                           0x23CB
#define P23_CC_IR_RAW_DEB0                                          0x23CC
#define P23_CD_IR_RAW_DEB1                                          0x23CD
#define P23_CE_IR_RAW_DEB2                                          0x23CE
#define P23_CF_IR_RAW_DEB3                                          0x23CF
#define P23_D0_IR_PSR_UP0                                           0x23D0
#define P23_D1_IR_PSR_UP1                                           0x23D1
#define P23_D2_IR_PSR_UP2                                           0x23D2
#define P23_D3_IR_PSR_UP3                                           0x23D3
#define P23_D4_IR_PER_UP0                                           0x23D4
#define P23_D5_IR_PER_UP1                                           0x23D5
#define P23_D6_IR_PER_UP2                                           0x23D6
#define P23_D7_IR_PER_UP3                                           0x23D7
#define P23_D8_IR_CTRL_RC60                                         0x23D8
#define P23_D9_IR_CTRL_RC61                                         0x23D9
#define P23_DA_IR_CTRL_RC62                                         0x23DA
#define P23_DB_IR_CTRL_RC63                                         0x23DB
#define P23_DC_IR_RP2_0                                             0x23DC
#define P23_DD_IR_RP2_1                                             0x23DD
#define P23_DE_IR_RP2_2                                             0x23DE
#define P23_DF_IR_RP2_3                                             0x23DF
#define P23_E0_IR_RAW_SF0                                           0x23E0
#define P23_E1_IR_RAW_SF1                                           0x23E1
#define P23_E2_IR_RAW_SF2                                           0x23E2
#define P23_E3_IR_RAW_SF3                                           0x23E3
#define P23_F0_IR_CLK_GAT                                           0x23F0


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
#define P25_A8_RFILTER_DUMMY                                        0x25A8


//--------------------------------------------------
// D2 ECBUS APHY (Page 27)
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
#define P27_0D_ECBUS_CMU_CONTROL_0                                  0x270D
#define P27_0E_ECBUS_CMU_CONTROL_1                                  0x270E
#define P27_0F_ECBUS_CMU_CONTROL_2                                  0x270F
#define P27_10_ECBUS_CMU_CONTROL_3                                  0x2710
#define P27_11_ECBUS_CMU_CONTROL_4                                  0x2711


//--------------------------------------------------
// D2 CBUS PHY (Page 27)
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
// D2 MHL3 OCBUS MAC (Page 2A)
//--------------------------------------------------
#define P2A_00_OCBUS_CTRL_00                                        0x2A00
#define P2A_01_OCBUS_CTRL_01                                        0x2A01
#define P2A_10_OCBUS_CTRL_10                                        0x2A10
#define P2A_11_OCBUS_CTRL_11                                        0x2A11
#define P2A_12_OCBUS_CTRL_12                                        0x2A12
#define P2A_13_OCBUS_CTRL_13                                        0x2A13
#define P2A_14_OCBUS_CTRL_14                                        0x2A14
#define P2A_15_OCBUS_CTRL_15                                        0x2A15
#define P2A_16_OCBUS_CTRL_16                                        0x2A16
#define P2A_17_OCBUS_CTRL_17                                        0x2A17
#define P2A_18_OCBUS_CTRL_18                                        0x2A18
#define P2A_19_OCBUS_CTRL_19                                        0x2A19
#define P2A_1A_OCBUS_CTRL_1A                                        0x2A1A
#define P2A_1B_OCBUS_CTRL_1B                                        0x2A1B
#define P2A_1C_OCBUS_CTRL_1C                                        0x2A1C
#define P2A_1D_OCBUS_CTRL_1D                                        0x2A1D
#define P2A_1E_OCBUS_CTRL_1E                                        0x2A1E
#define P2A_1F_OCBUS_CTRL_1F                                        0x2A1F
#define P2A_20_OCBUS_CTRL_20                                        0x2A20
#define P2A_21_OCBUS_CTRL_21                                        0x2A21
#define P2A_22_OCBUS_CTRL_22                                        0x2A22
#define P2A_23_OCBUS_CTRL_23                                        0x2A23
#define P2A_24_OCBUS_CTRL_24                                        0x2A24
#define P2A_25_OCBUS_CTRL_25                                        0x2A25


//--------------------------------------------------
// D2 CBUS POWER ON MAC (Page 2A)
//--------------------------------------------------
#define P2A_A0_CBUS_CTRL_00                                         0x2AA0
#define P2A_A1_CBUS_CTRL_01                                         0x2AA1
#define P2A_A2_CBUS_CTRL_02                                         0x2AA2
#define P2A_A3_CBUS_CTRL_03                                         0x2AA3
#define P2A_A4_CBUS_CTRL_04                                         0x2AA4
#define P2A_A5_CBUS_CTRL_05                                         0x2AA5
#define P2A_A6_CBUS_CTRL_06                                         0x2AA6
#define P2A_A7_CBUS_CTRL_07                                         0x2AA7
#define P2A_A8_CBUS_CTRL_08                                         0x2AA8
#define P2A_A9_CBUS_CTRL_09                                         0x2AA9
#define P2A_AA_CBUS_CTRL_0A                                         0x2AAA


//--------------------------------------------------
// D2 CBUS POWER OFF MAC (Page 2A)
//--------------------------------------------------
#define P2A_AB_CBUS_CTRL_0B                                         0x2AAB
#define P2A_AC_CBUS_CTRL_0C                                         0x2AAC
#define P2A_AD_CBUS_CTRL_0D                                         0x2AAD
#define P2A_AE_CBUS_CTRL_0E                                         0x2AAE
#define P2A_AF_CBUS_CTRL_0F                                         0x2AAF
#define P2A_B0_CBUS_CTRL_10                                         0x2AB0
#define P2A_B1_CBUS_CTRL_11                                         0x2AB1
#define P2A_B2_CBUS_CTRL_12                                         0x2AB2
#define P2A_B3_CBUS_CTRL_13                                         0x2AB3
#define P2A_B4_CBUS_CTRL_14                                         0x2AB4
#define P2A_B5_CBUS_CTRL_15                                         0x2AB5
#define P2A_B6_CBUS_CTRL_16                                         0x2AB6
#define P2A_B7_CBUS_CTRL_17                                         0x2AB7
#define P2A_B8_CBUS_CTRL_18                                         0x2AB8
#define P2A_BA_CBUS_CTRL_1A                                         0x2ABA
#define P2A_BB_CBUS_CTRL_1B                                         0x2ABB
#define P2A_BC_CBUS_CTRL_1C                                         0x2ABC
#define P2A_BD_CBUS_CTRL_1D                                         0x2ABD
#define P2A_BE_CBUS_CTRL_1E                                         0x2ABE
#define P2A_BF_CBUS_CTRL_1F                                         0x2ABF
#define P2A_C0_CBUS_CTRL_20                                         0x2AC0
#define P2A_C1_CBUS_CTRL_21                                         0x2AC1
#define P2A_C2_CBUS_CTRL_22                                         0x2AC2
#define P2A_C3_CBUS_CTRL_23                                         0x2AC3
#define P2A_C4_CBUS_CTRL_24                                         0x2AC4
#define P2A_C5_CBUS_CTRL_25                                         0x2AC5
#define P2A_C6_CBUS_CTRL_26                                         0x2AC6
#define P2A_C8_CBUS_CTRL_28                                         0x2AC8
#define P2A_C9_CBUS_CTRL_29                                         0x2AC9
#define P2A_CA_CBUS_CTRL_2A                                         0x2ACA
#define P2A_CB_CBUS_CTRL_2B                                         0x2ACB
#define P2A_CC_CBUS_CTRL_2C                                         0x2ACC
#define P2A_CD_CBUS_CTRL_2D                                         0x2ACD
#define P2A_CE_CBUS_CTRL_2E                                         0x2ACE
#define P2A_CF_CBUS_CTRL_2F                                         0x2ACF
#define P2A_D0_CBUS_CTRL_30                                         0x2AD0
#define P2A_D1_CBUS_CTRL_31                                         0x2AD1
#define P2A_D2_CBUS_CTRL_32                                         0x2AD2
#define P2A_D3_CBUS_CTRL_33                                         0x2AD3
#define P2A_D4_CBUS_CTRL_34                                         0x2AD4
#define P2A_D5_CBUS_CTRL_35                                         0x2AD5
#define P2A_D6_CBUS_CTRL_36                                         0x2AD6
#define P2A_D7_CBUS_CTRL_37                                         0x2AD7
#define P2A_D8_CBUS_CTRL_38                                         0x2AD8
#define P2A_D9_CBUS_CTRL_39                                         0x2AD9
#define P2A_DA_CBUS_CTRL_3A                                         0x2ADA
#define P2A_DB_CBUS_CTRL_3B                                         0x2ADB
#define P2A_DC_CBUS_CTRL_3C                                         0x2ADC
#define P2A_DD_CBUS_CTRL_3D                                         0x2ADD
#define P2A_DE_CBUS_CTRL_3E                                         0x2ADE
#define P2A_DF_CBUS_CTRL_3F                                         0x2ADF
#define P2A_E0_CBUS_CTRL_40                                         0x2AE0
#define P2A_E1_CBUS_CTRL_41                                         0x2AE1
#define P2A_E2_CBUS_CTRL_42                                         0x2AE2
#define P2A_E3_CBUS_CTRL_43                                         0x2AE3
#define P2A_E4_CBUS_CTRL_44                                         0x2AE4
#define P2A_E5_CBUS_CTRL_45                                         0x2AE5
#define P2A_E6_CBUS_CTRL_46                                         0x2AE6
#define P2A_E7_CBUS_CTRL_47                                         0x2AE7
#define P2A_E8_CBUS_CTRL_48                                         0x2AE8
#define P2A_E9_CBUS_CTRL_49                                         0x2AE9
#define P2A_EA_CBUS_CTRL_4A                                         0x2AEA
#define P2A_EB_CBUS_CTRL_4B                                         0x2AEB
#define P2A_EC_CBUS_CTRL_4C                                         0x2AEC
#define P2A_ED_CBUS_CTRL_4D                                         0x2AED
#define P2A_EE_CBUS_CTRL_4E                                         0x2AEE
#define P2A_EF_CBUS_CTRL_4F                                         0x2AEF
#define P2A_F0_CBUS_CTRL_50                                         0x2AF0
#define P2A_F1_CBUS_CTRL_51                                         0x2AF1
#define P2A_F2_CBUS_CTRL_52                                         0x2AF2
#define P2A_F3_CBUS_CTRL_53                                         0x2AF3
#define P2A_F4_CBUS_CTRL_54                                         0x2AF4
#define P2A_F5_CBUS_CTRL_55                                         0x2AF5
#define P2A_F6_CBUS_CTRL_56                                         0x2AF6
#define P2A_F7_CBUS_CTRL_57                                         0x2AF7
#define P2A_F8_CBUS_CTRL_58                                         0x2AF8
#define P2A_F9_CBUS_CTRL_59                                         0x2AF9
#define P2A_FA_CBUS_CTRL_5A                                         0x2AFA
#define P2A_FB_CBUS_CTRL_5B                                         0x2AFB
#define P2A_FC_CBUS_CTRL_5C                                         0x2AFC
#define P2A_FD_CBUS_CTRL_5D                                         0x2AFD


//--------------------------------------------------
// D2 ECBUS MAC (Page 2B)
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
#define P2B_53_ECBUS_TESTOUT_RESERVE                                0x2B53
#define P2B_54_ECBUS_BIST_OPTION_0                                  0x2B54
#define P2B_55_ECBUS_BIST_OPTION_1                                  0x2B55
#define P2B_56_ECBUS_BIST_OPTION_2                                  0x2B56
#define P2B_57_ECBUS_BIST_OPTION_3                                  0x2B57
#define P2B_58_ECBUS_BIST_OPTION_4                                  0x2B58
#define P2B_59_ECBUS_BIST_OPTION_5                                  0x2B59
#define P2B_5A_ECBUS_BIST_OPTION_6                                  0x2B5A
#define P2B_5B_ECBUS_BIST_OPTION_7                                  0x2B5B
#define P2B_5C_ECBUS_BIST_OPTION_8                                  0x2B5C
#define P2B_5D_ECBUS_RESERVE_0                                      0x2B5D
#define P2B_5E_ECBUS_RESERVE_1                                      0x2B5E
#define P2B_5F_ECBUS_RESERVE_2                                      0x2B5F
#define P2B_60_ECBUS_DPHY_CAP0                                      0x2B60
#define P2B_61_ECBUS_DPHY_CAP1                                      0x2B61


//--------------------------------------------------
// D2 ECBUS DPHY (Page 2B)
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
#define P2B_CB_ECBUS_DPHY_WD0                                       0x2BCB
#define P2B_CC_ECBUS_DPHY_WD1                                       0x2BCC


//--------------------------------------------------
// D3 ECBUS MAC (Page 2C)
//--------------------------------------------------
#define P2C_00_ECBUS_STARTUP_CTRL                                   0x2C00
#define P2C_01_ECBUS_STARTUP_CONFIG                                 0x2C01
#define P2C_02_ECBUS_STARTUP_DET                                    0x2C02
#define P2C_03_ECBUS_STARTUP_RESERVE                                0x2C03
#define P2C_04_ECBUS_TDM_SYNC_CTRL                                  0x2C04
#define P2C_05_ECBUS_TDM_SYNC_CONFIG_1                              0x2C05
#define P2C_06_ECBUS_TDM_SYNC_CONFIG_2                              0x2C06
#define P2C_07_ECBUS_TDM_SYNC_DET_1                                 0x2C07
#define P2C_08_ECBUS_TDM_SYNC_DET_2                                 0x2C08
#define P2C_09_ECBUS_TDM_SYNC_TX_OFFSET                             0x2C09
#define P2C_0A_ECBUS_TDM_SYNC_RX_OFFSET                             0x2C0A
#define P2C_0B_ECBUS_TDM_SYNC_RESERVE                               0x2C0B
#define P2C_0C_ECBUS_EMSC_SYNC_CTRL                                 0x2C0C
#define P2C_0D_ECBUS_EMSC_SYNC_CONFIG_1                             0x2C0D
#define P2C_0E_ECBUS_EMSC_SYNC_CONFIG_2                             0x2C0E
#define P2C_0F_ECBUS_EMSC_SYNC_DET                                  0x2C0F
#define P2C_10_ECBUS_EMSC_SLOT_MAP_1                                0x2C10
#define P2C_11_ECBUS_EMSC_SLOT_MAP_2                                0x2C11
#define P2C_12_ECBUS_EMSC_SLOT_MAP_3                                0x2C12
#define P2C_13_ECBUS_EMSC_SOURCE_SLOT_DET_1                         0x2C13
#define P2C_14_ECBUS_EMSC_SOURCE_SLOT_DET_2                         0x2C14
#define P2C_15_ECBUS_EMSC_SOURCE_SLOT_DET_3                         0x2C15
#define P2C_16_ECBUS_EMSC_SYNC_RESERVE                              0x2C16
#define P2C_17_ECBUS_EMSC_RX_ADDR                                   0x2C17
#define P2C_18_ECBUS_EMSC_RX_DATA                                   0x2C18
#define P2C_19_ECBUS_EMSC_TX_ADDR                                   0x2C19
#define P2C_1A_ECBUS_EMSC_TX_DATA                                   0x2C1A
#define P2C_1B_ECBUS_EMSC_TX_RD_ADDR                                0x2C1B
#define P2C_1C_ECBUS_EMSC_TX_RD_DATA                                0x2C1C
#define P2C_1D_ECBUS_EMSC_TRANS_CTRL                                0x2C1D
#define P2C_1E_ECBUS_EMSC_RX_BLK_CNT                                0x2C1E
#define P2C_1F_ECBUS_EMSC_RX_WRT_PNT                                0x2C1F
#define P2C_20_ECBUS_EMSC_TX_WRT_PNT                                0x2C20
#define P2C_21_ECBUS_EMSC_RX_REQ_CNT                                0x2C21
#define P2C_22_ECBUS_EMSC_TX_REQ_CNT                                0x2C22
#define P2C_23_ECBUS_EMSC_TRANS_CONFIG_1                            0x2C23
#define P2C_24_ECBUS_EMSC_TRANS_CONFIG_2                            0x2C24
#define P2C_25_ECBUS_EMSC_TRANS_DET_1                               0x2C25
#define P2C_26_ECBUS_EMSC_TRANS_DET_2                               0x2C26
#define P2C_27_ECBUS_EMSC_TRANS_DET_3                               0x2C27
#define P2C_28_ECBUS_EMSC_TRANS_DET_4                               0x2C28
#define P2C_29_ECBUS_EMSC_TX_ERR_CODE                               0x2C29
#define P2C_2A_ECBUS_EMSC_TRANS_RESERVE                             0x2C2A
#define P2C_2B_ECBUS_EMSC_RX_CRC_1                                  0x2C2B
#define P2C_2C_ECBUS_EMSC_RX_CRC_2                                  0x2C2C
#define P2C_2D_ECBUS_EMSC_RX_CRC_3                                  0x2C2D
#define P2C_2E_ECBUS_EMSC_RX_CRC_4                                  0x2C2E
#define P2C_2F_ECBUS_EMSC_TX_CRC_1                                  0x2C2F
#define P2C_30_ECBUS_EMSC_TX_CRC_2                                  0x2C30
#define P2C_31_ECBUS_EMSC_TX_CRC_3                                  0x2C31
#define P2C_32_ECBUS_EMSC_TX_CRC_4                                  0x2C32
#define P2C_33_ECBUS_EMSC_CRC_RESERVE                               0x2C33
#define P2C_34_ECBUS_BIST_CTRL                                      0x2C34
#define P2C_35_ECBUS_BIST_CONFIG                                    0x2C35
#define P2C_36_ECBUS_BIST_FIXED8                                    0x2C36
#define P2C_37_ECBUS_BIST_RX_INIT                                   0x2C37
#define P2C_38_ECBUS_BIST_TX_INIT                                   0x2C38
#define P2C_39_ECBUS_BIST_ERR_CNT_H                                 0x2C39
#define P2C_3A_ECBUS_BIST_ERR_CNT_L                                 0x2C3A
#define P2C_3B_ECBUS_BIST_RESERVE                                   0x2C3B
#define P2C_3C_ECBUS_SRAM_BIST                                      0x2C3C
#define P2C_3D_ECBUS_SRAM_DRF_BIST                                  0x2C3D
#define P2C_3E_ECBUS_GLOBAL_CTRL                                    0x2C3E
#define P2C_3F_CBUS1_FW_CRC_B0_H                                    0x2C3F
#define P2C_40_CBUS1_FW_CRC_B0_L                                    0x2C40
#define P2C_41_CBUS1_FW_CRC_B1_H                                    0x2C41
#define P2C_42_CBUS1_FW_CRC_B1_L                                    0x2C42
#define P2C_43_CBUS1_FW_CRC_B2_H                                    0x2C43
#define P2C_44_CBUS1_FW_CRC_B2_L                                    0x2C44
#define P2C_45_CBUS1_FW_CRC_B3_H                                    0x2C45
#define P2C_46_CBUS1_FW_CRC_B3_L                                    0x2C46
#define P2C_47_CBUS1_FW_CRC_B4_H                                    0x2C47
#define P2C_48_CBUS1_FW_CRC_B4_L                                    0x2C48
#define P2C_49_ECBUS_TIMEOUT_CLK1                                   0x2C49
#define P2C_4A_ECBUS_TIMEOUT_CLK2                                   0x2C4A
#define P2C_4B_ECBUS_TIMEOUT_RESERVE                                0x2C4B
#define P2C_4C_ECBUS_HW_FSM_1                                       0x2C4C
#define P2C_4D_ECBUS_HW_FSM_2                                       0x2C4D
#define P2C_4E_ECBUS_HW_FSM_3                                       0x2C4E
#define P2C_4F_ECBUS_HW_FSM_4                                       0x2C4F
#define P2C_50_ECBUS_HW_FSM_5                                       0x2C50
#define P2C_51_ECBUS_HW_FSM_6                                       0x2C51
#define P2C_52_ECBUS_TEST_FORCE_OUT                                 0x2C52
#define P2C_53_ECBUS_TESTOUT_RESERVE                                0x2C53
#define P2C_54_ECBUS_BIST_OPTION_0                                  0x2C54
#define P2C_55_ECBUS_BIST_OPTION_1                                  0x2C55
#define P2C_56_ECBUS_BIST_OPTION_2                                  0x2C56
#define P2C_57_ECBUS_BIST_OPTION_3                                  0x2C57
#define P2C_58_ECBUS_BIST_OPTION_4                                  0x2C58
#define P2C_59_ECBUS_BIST_OPTION_5                                  0x2C59
#define P2C_5A_ECBUS_BIST_OPTION_6                                  0x2C5A
#define P2C_5B_ECBUS_BIST_OPTION_7                                  0x2C5B
#define P2C_5C_ECBUS_BIST_OPTION_8                                  0x2C5C
#define P2C_5D_ECBUS_RESERVE_0                                      0x2C5D
#define P2C_5E_ECBUS_RESERVE_1                                      0x2C5E
#define P2C_5F_ECBUS_RESERVE_2                                      0x2C5F
#define P2C_60_ECBUS_DPHY_CAP0                                      0x2C60
#define P2C_61_ECBUS_DPHY_CAP1                                      0x2C61


//--------------------------------------------------
// D3 ECBUS DPHY (Page 2C)
//--------------------------------------------------
#define P2C_A0_ECBUS_DPHY_CTRL                                      0x2CA0
#define P2C_A1_ECBUS_DPHY_EDGE_CTRL                                 0x2CA1
#define P2C_A2_ECBUS_DPHY_EDGE_RESULT                               0x2CA2
#define P2C_A3_ECBUS_DPHY_STAT_CTRL                                 0x2CA3
#define P2C_A4_ECBUS_DPHY_STAT_CONFIG_1                             0x2CA4
#define P2C_A5_ECBUS_DPHY_STAT_CONFIG_2                             0x2CA5
#define P2C_A6_ECBUS_DPHY_STAT_RESULT_1                             0x2CA6
#define P2C_A7_ECBUS_DPHY_STAT_RESULT_2                             0x2CA7
#define P2C_A8_ECBUS_DPHY_STAT_RESULT_3                             0x2CA8
#define P2C_A9_ECBUS_DPHY_CALIB_CTRL                                0x2CA9
#define P2C_AA_ECBUS_DPHY_INI_CONFIG_1                              0x2CAA
#define P2C_AB_ECBUS_DPHY_INI_CONFIG_2                              0x2CAB
#define P2C_AC_ECBUS_DPHY_INI_CONFIG_3                              0x2CAC
#define P2C_AD_ECBUS_DPHY_INI_CONFIG_4                              0x2CAD
#define P2C_AE_ECBUS_DPHY_INI_CONFIG_5                              0x2CAE
#define P2C_AF_ECBUS_DPHY_INI_RESULT_1                              0x2CAF
#define P2C_B0_ECBUS_DPHY_INI_RESULT_2                              0x2CB0
#define P2C_B1_ECBUS_DPHY_INI_RESULT_3                              0x2CB1
#define P2C_B2_ECBUS_DPHY_INI_RESULT_4                              0x2CB2
#define P2C_B3_ECBUS_DPHY_TX_PHASE_CONFIG_1                         0x2CB3
#define P2C_B4_ECBUS_DPHY_TX_PHASE_CONFIG_2                         0x2CB4
#define P2C_B5_ECBUS_DPHY_TX_PHASE_CONFIG_3                         0x2CB5
#define P2C_B6_ECBUS_DPHY_TX_PHASE_CONFIG_4                         0x2CB6
#define P2C_B7_ECBUS_DPHY_TX_PHASE_RESULT                           0x2CB7
#define P2C_B8_ECBUS_DPHY_ADAPT_CTRL                                0x2CB8
#define P2C_B9_ECBUS_DPHY_ADAPT_CONFIG_1                            0x2CB9
#define P2C_BA_ECBUS_DPHY_ADAPT_CONFIG_2                            0x2CBA
#define P2C_BB_ECBUS_DPHY_ADAPT_CONFIG_3                            0x2CBB
#define P2C_BC_ECBUS_DPHY_ADAPT_RESULT_1                            0x2CBC
#define P2C_BD_ECBUS_DPHY_ADAPT_RESULT_2                            0x2CBD
#define P2C_BE_ECBUS_DPHY_ADAPT_RESULT_3                            0x2CBE
#define P2C_BF_ECBUS_DPHY_CALIB_RESULT                              0x2CBF
#define P2C_C0_ECBUS_DPHY_CONFIG                                    0x2CC0
#define P2C_C1_ECBUS_DPHY_PATTERN_1                                 0x2CC1
#define P2C_C2_ECBUS_DPHY_PATTERN_2                                 0x2CC2
#define P2C_C3_ECBUS_DPHY_FLAG                                      0x2CC3
#define P2C_C4_ECBUS_DPHY_IRQ                                       0x2CC4
#define P2C_C5_ECBUS_DPHY_DEBUG                                     0x2CC5
#define P2C_C6_ECBUS_DPHY_RESERVE                                   0x2CC6
#define P2C_CB_ECBUS_DPHY_WD0                                       0x2CCB
#define P2C_CC_ECBUS_DPHY_WD1                                       0x2CCC


//--------------------------------------------------
// D2 TMDS AES (Page 2D)
//--------------------------------------------------
#define P2D_00_HDCP_AES_CIPHER_KEY_15                               0x2D00
#define P2D_01_HDCP_AES_CIPHER_KEY_14                               0x2D01
#define P2D_02_HDCP_AES_CIPHER_KEY_13                               0x2D02
#define P2D_03_HDCP_AES_CIPHER_KEY_12                               0x2D03
#define P2D_04_HDCP_AES_CIPHER_KEY_11                               0x2D04
#define P2D_05_HDCP_AES_CIPHER_KEY_10                               0x2D05
#define P2D_06_HDCP_AES_CIPHER_KEY_9                                0x2D06
#define P2D_07_HDCP_AES_CIPHER_KEY_8                                0x2D07
#define P2D_08_HDCP_AES_CIPHER_KEY_7                                0x2D08
#define P2D_09_HDCP_AES_CIPHER_KEY_6                                0x2D09
#define P2D_0A_HDCP_AES_CIPHER_KEY_5                                0x2D0A
#define P2D_0B_HDCP_AES_CIPHER_KEY_4                                0x2D0B
#define P2D_0C_HDCP_AES_CIPHER_KEY_3                                0x2D0C
#define P2D_0D_HDCP_AES_CIPHER_KEY_2                                0x2D0D
#define P2D_0E_HDCP_AES_CIPHER_KEY_1                                0x2D0E
#define P2D_0F_HDCP_AES_CIPHER_KEY_0                                0x2D0F
#define P2D_10_AES_DUMMY_0                                          0x2D10
#define P2D_11_AES_DUMMY_1                                          0x2D11
#define P2D_12_AES_DUMMY_2                                          0x2D12
#define P2D_13_AES_DUMMY_3                                          0x2D13


//--------------------------------------------------
// D2 HDCP 2.2 IIC Module (Page 2D)
//--------------------------------------------------
#define P2D_20_HDCP_MSG_CTRL                                        0x2D20
#define P2D_21_HDCP_MSGWAP                                          0x2D21
#define P2D_22_HDCP_MSGWDP                                          0x2D22
#define P2D_23_HDCP_MSGRAP_H                                        0x2D23
#define P2D_24_HDCP_MSGRAP_L                                        0x2D24
#define P2D_25_HDCP_MSGRDP                                          0x2D25
#define P2D_26_HDCP_I2C_CTRL_0                                      0x2D26
#define P2D_27_HDCP_I2C_CTRL_1                                      0x2D27
#define P2D_28_HDCP_I2C_CTRL_2                                      0x2D28
#define P2D_29_HDCP_I2C_CTRL_3                                      0x2D29
#define P2D_2A_HDCP_I2C_CTRL_4                                      0x2D2A
#define P2D_2B_HDCP_I2C_CTRL_5                                      0x2D2B
#define P2D_2C_HDCP_I2C_CTRL_6                                      0x2D2C
#define P2D_2D_HDCP_I2C_CTRL_RIV7                                   0x2D2D
#define P2D_2E_HDCP_I2C_CTRL_RIV6                                   0x2D2E
#define P2D_2F_HDCP_I2C_CTRL_RIV5                                   0x2D2F
#define P2D_30_HDCP_I2C_CTRL_RIV4                                   0x2D30
#define P2D_31_HDCP_I2C_CTRL_RIV3                                   0x2D31
#define P2D_32_HDCP_I2C_CTRL_RIV2                                   0x2D32
#define P2D_33_HDCP_I2C_CTRL_RIV1                                   0x2D33
#define P2D_34_HDCP_I2C_CTRL_RIV0                                   0x2D34
#define P2D_35_HDCP_I2C_CTRL_7                                      0x2D35
#define P2D_36_HDCP_I2C_CTRL_8                                      0x2D36
#define P2D_37_I2C_M0_MBIST_CTRL_0                                  0x2D37
#define P2D_38_I2C_M0_MBIST_CTRL_1                                  0x2D38
#define P2D_39_I2C_M1_MBIST_CTRL_0                                  0x2D39
#define P2D_3A_I2C_M1_MBIST_CTRL_1                                  0x2D3A
#define P2D_3B_I2C_DUMMY_0                                          0x2D3B
#define P2D_3C_I2C_DUMMY_1                                          0x2D3C
#define P2D_3D_READ_INT_ID_OPTION                                   0x2D3D
#define P2D_3E_WRITE_INT_ID_OPTION                                  0x2D3E
#define P2D_3F_ID_INT_CTRL                                          0x2D3F


//--------------------------------------------------
// D2 MHL3 DPLL (Page 2D)
//--------------------------------------------------
#define P2D_A0_MN_SCLKG_CTRL                                        0x2DA0
#define P2D_A1_MN_SCLKG_DIVM                                        0x2DA1
#define P2D_A2_MN_SCLKG_DIVN                                        0x2DA2
#define P2D_A3_MN_SCLKG_DIVS                                        0x2DA3
#define P2D_A4_MN_SCLKG_OFFS_H                                      0x2DA4
#define P2D_A5_MN_SCLKG_OFFS_M                                      0x2DA5
#define P2D_A6_MN_SCLKG_OFFS_L                                      0x2DA6
#define P2D_A7_MN_SCLKG_TRK_CTRL                                    0x2DA7
#define P2D_A8_MN_SCLKG_TRK_MN_I_H                                  0x2DA8
#define P2D_A9_MN_SCLKG_TRK_MN_I_M                                  0x2DA9
#define P2D_AA_MN_SCLKG_TRK_MN_I_L                                  0x2DAA
#define P2D_AB_MN_SCLKG_TRK_MN_P_H                                  0x2DAB
#define P2D_AC_MN_SCLKG_TRK_MN_P_M                                  0x2DAC
#define P2D_AD_MN_SCLKG_TRK_MN_P_L                                  0x2DAD
#define P2D_AE_MN_SCLKG_TRK_MN_PE                                   0x2DAE
#define P2D_AF_MN_SCLKG_TRK_MN_NLOCK                                0x2DAF
#define P2D_B0_MN_SCLKG_TRK_VS_I_H                                  0x2DB0
#define P2D_B1_MN_SCLKG_TRK_VS_I_M                                  0x2DB1
#define P2D_B2_MN_SCLKG_TRK_VS_I_L                                  0x2DB2
#define P2D_B3_MN_SCLKG_TRK_VS_P_H                                  0x2DB3
#define P2D_B4_MN_SCLKG_TRK_VS_P_M                                  0x2DB4
#define P2D_B5_MN_SCLKG_TRK_VS_P_L                                  0x2DB5
#define P2D_B6_MN_SCLKG_TRK_VS_PE                                   0x2DB6
#define P2D_B7_MN_SCLKG_TRK_VS_NLOCK                                0x2DB7
#define P2D_B8_MN_SCLKG_SDM_CTRL                                    0x2DB8
#define P2D_B9_MN_SCLKG_SDM_TEST                                    0x2DB9
#define P2D_BA_MN_SCLKG_SDM_SUMC_H                                  0x2DBA
#define P2D_BB_MN_SCLKG_SDM_SUMC_M                                  0x2DBB
#define P2D_BC_MN_SCLKG_SDM_SUMC_L                                  0x2DBC
#define P2D_BD_MN_SCLKG_PLL_PWR                                     0x2DBD
#define P2D_BE_MN_SCLKG_PLL_CHP                                     0x2DBE
#define P2D_BF_MN_SCLKG_PLL_WD                                      0x2DBF
#define P2D_C0_MN_SCLKG_PLL_INSEL                                   0x2DC0
#define P2D_C1_MN_SCLKG_PLL_RESERVE                                 0x2DC1
#define P2D_C2_HS_TRACKING_NEW_MODE1                                0x2DC2
#define P2D_C3_HS_TRACKING_NEW_MODE2                                0x2DC3
#define P2D_C4_M_CODE_ADJUST_0                                      0x2DC4
#define P2D_C5_M_CODE_ADJUST_1                                      0x2DC5
#define P2D_C6_M_CODE_ADJUST_2                                      0x2DC6
#define P2D_C7_PLL_DUMMY_3                                          0x2DC7
#define P2D_C8_PLL_DUMMY_4                                          0x2DC8
#define P2D_C9_PLL_DUMMY_5                                          0x2DC9


//--------------------------------------------------
// D3 TMDS AES (Page 2E)
//--------------------------------------------------
#define P2E_00_HDCP_AES_CIPHER_KEY_15                               0x2E00
#define P2E_01_HDCP_AES_CIPHER_KEY_14                               0x2E01
#define P2E_02_HDCP_AES_CIPHER_KEY_13                               0x2E02
#define P2E_03_HDCP_AES_CIPHER_KEY_12                               0x2E03
#define P2E_04_HDCP_AES_CIPHER_KEY_11                               0x2E04
#define P2E_05_HDCP_AES_CIPHER_KEY_10                               0x2E05
#define P2E_06_HDCP_AES_CIPHER_KEY_9                                0x2E06
#define P2E_07_HDCP_AES_CIPHER_KEY_8                                0x2E07
#define P2E_08_HDCP_AES_CIPHER_KEY_7                                0x2E08
#define P2E_09_HDCP_AES_CIPHER_KEY_6                                0x2E09
#define P2E_0A_HDCP_AES_CIPHER_KEY_5                                0x2E0A
#define P2E_0B_HDCP_AES_CIPHER_KEY_4                                0x2E0B
#define P2E_0C_HDCP_AES_CIPHER_KEY_3                                0x2E0C
#define P2E_0D_HDCP_AES_CIPHER_KEY_2                                0x2E0D
#define P2E_0E_HDCP_AES_CIPHER_KEY_1                                0x2E0E
#define P2E_0F_HDCP_AES_CIPHER_KEY_0                                0x2E0F
#define P2E_10_AES_DUMMY_0                                          0x2E10
#define P2E_11_AES_DUMMY_1                                          0x2E11
#define P2E_12_AES_DUMMY_2                                          0x2E12
#define P2E_13_AES_DUMMY_3                                          0x2E13


//--------------------------------------------------
// D3 HDCP 2.2 IIC Module (Page 2E)
//--------------------------------------------------
#define P2E_20_HDCP_MSG_CTRL                                        0x2E20
#define P2E_21_HDCP_MSGWAP                                          0x2E21
#define P2E_22_HDCP_MSGWDP                                          0x2E22
#define P2E_23_HDCP_MSGRAP_H                                        0x2E23
#define P2E_24_HDCP_MSGRAP_L                                        0x2E24
#define P2E_25_HDCP_MSGRDP                                          0x2E25
#define P2E_26_HDCP_I2C_CTRL_0                                      0x2E26
#define P2E_27_HDCP_I2C_CTRL_1                                      0x2E27
#define P2E_28_HDCP_I2C_CTRL_2                                      0x2E28
#define P2E_29_HDCP_I2C_CTRL_3                                      0x2E29
#define P2E_2A_HDCP_I2C_CTRL_4                                      0x2E2A
#define P2E_2B_HDCP_I2C_CTRL_5                                      0x2E2B
#define P2E_2C_HDCP_I2C_CTRL_6                                      0x2E2C
#define P2E_2D_HDCP_I2C_CTRL_RIV7                                   0x2E2D
#define P2E_2E_HDCP_I2C_CTRL_RIV6                                   0x2E2E
#define P2E_2F_HDCP_I2C_CTRL_RIV5                                   0x2E2F
#define P2E_30_HDCP_I2C_CTRL_RIV4                                   0x2E30
#define P2E_31_HDCP_I2C_CTRL_RIV3                                   0x2E31
#define P2E_32_HDCP_I2C_CTRL_RIV2                                   0x2E32
#define P2E_33_HDCP_I2C_CTRL_RIV1                                   0x2E33
#define P2E_34_HDCP_I2C_CTRL_RIV0                                   0x2E34
#define P2E_35_HDCP_I2C_CTRL_7                                      0x2E35
#define P2E_36_HDCP_I2C_CTRL_8                                      0x2E36
#define P2E_37_I2C_M0_MBIST_CTRL_0                                  0x2E37
#define P2E_38_I2C_M0_MBIST_CTRL_1                                  0x2E38
#define P2E_39_I2C_M1_MBIST_CTRL_0                                  0x2E39
#define P2E_3A_I2C_M1_MBIST_CTRL_1                                  0x2E3A
#define P2E_3B_I2C_DUMMY_0                                          0x2E3B
#define P2E_3C_I2C_DUMMY_1                                          0x2E3C
#define P2E_3D_READ_INT_ID_OPTION                                   0x2E3D
#define P2E_3E_WRITE_INT_ID_OPTION                                  0x2E3E
#define P2E_3F_ID_INT_CTRL                                          0x2E3F


//--------------------------------------------------
// D3 MHL3 DPLL (Page 2E)
//--------------------------------------------------
#define P2E_A0_MN_SCLKG_CTRL                                        0x2EA0
#define P2E_A1_MN_SCLKG_DIVM                                        0x2EA1
#define P2E_A2_MN_SCLKG_DIVN                                        0x2EA2
#define P2E_A3_MN_SCLKG_DIVS                                        0x2EA3
#define P2E_A4_MN_SCLKG_OFFS_H                                      0x2EA4
#define P2E_A5_MN_SCLKG_OFFS_M                                      0x2EA5
#define P2E_A6_MN_SCLKG_OFFS_L                                      0x2EA6
#define P2E_A7_MN_SCLKG_TRK_CTRL                                    0x2EA7
#define P2E_A8_MN_SCLKG_TRK_MN_I_H                                  0x2EA8
#define P2E_A9_MN_SCLKG_TRK_MN_I_M                                  0x2EA9
#define P2E_AA_MN_SCLKG_TRK_MN_I_L                                  0x2EAA
#define P2E_AB_MN_SCLKG_TRK_MN_P_H                                  0x2EAB
#define P2E_AC_MN_SCLKG_TRK_MN_P_M                                  0x2EAC
#define P2E_AD_MN_SCLKG_TRK_MN_P_L                                  0x2EAD
#define P2E_AE_MN_SCLKG_TRK_MN_PE                                   0x2EAE
#define P2E_AF_MN_SCLKG_TRK_MN_NLOCK                                0x2EAF
#define P2E_B0_MN_SCLKG_TRK_VS_I_H                                  0x2EB0
#define P2E_B1_MN_SCLKG_TRK_VS_I_M                                  0x2EB1
#define P2E_B2_MN_SCLKG_TRK_VS_I_L                                  0x2EB2
#define P2E_B3_MN_SCLKG_TRK_VS_P_H                                  0x2EB3
#define P2E_B4_MN_SCLKG_TRK_VS_P_M                                  0x2EB4
#define P2E_B5_MN_SCLKG_TRK_VS_P_L                                  0x2EB5
#define P2E_B6_MN_SCLKG_TRK_VS_PE                                   0x2EB6
#define P2E_B7_MN_SCLKG_TRK_VS_NLOCK                                0x2EB7
#define P2E_B8_MN_SCLKG_SDM_CTRL                                    0x2EB8
#define P2E_B9_MN_SCLKG_SDM_TEST                                    0x2EB9
#define P2E_BA_MN_SCLKG_SDM_SUMC_H                                  0x2EBA
#define P2E_BB_MN_SCLKG_SDM_SUMC_M                                  0x2EBB
#define P2E_BC_MN_SCLKG_SDM_SUMC_L                                  0x2EBC
#define P2E_BD_MN_SCLKG_PLL_PWR                                     0x2EBD
#define P2E_BE_MN_SCLKG_PLL_CHP                                     0x2EBE
#define P2E_BF_MN_SCLKG_PLL_WD                                      0x2EBF
#define P2E_C0_MN_SCLKG_PLL_INSEL                                   0x2EC0
#define P2E_C1_MN_SCLKG_PLL_RESERVE                                 0x2EC1
#define P2E_C2_HS_TRACKING_NEW_MODE1                                0x2EC2
#define P2E_C3_HS_TRACKING_NEW_MODE2                                0x2EC3
#define P2E_C4_M_CODE_ADJUST_0                                      0x2EC4
#define P2E_C5_M_CODE_ADJUST_1                                      0x2EC5
#define P2E_C6_M_CODE_ADJUST_2                                      0x2EC6
#define P2E_C7_PLL_DUMMY_3                                          0x2EC7
#define P2E_C8_PLL_DUMMY_4                                          0x2EC8
#define P2E_C9_PLL_DUMMY_5                                          0x2EC9


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
#define P30_B1_VGATOP_HS_PULSE_WIDTH_DB                             0x30B1


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
// Format Conversion (Page 31)
//--------------------------------------------------
#define P31_00_FC_INPUT_SEL_P01                                     0x3100
#define P31_02_FC_INPUT_DPTX_SEL                                    0x3102
#define P31_03_FC_DUAL_DVI_CTRL1                                    0x3103
#define P31_04_FC_DUAL_DVI_CTRL2                                    0x3104
#define P31_05_FC_SD_CTRL                                           0x3105
#define P31_0C_CTS_FIFO_CTRL                                        0x310C
#define P31_0D_FC_INPUT_CLK_GATING                                  0x310D
#define P31_0E_FC_SYNC_CTRL                                         0x310E
#define P31_10_FC_EXT_CTRL                                          0x3110


//--------------------------------------------------
// YUV422 to YUV444 Conversion (Page 31)
//--------------------------------------------------
#define P31_40_YUV422_TO_444_PATH0                                  0x3140
#define P31_41_YUV422_TO_444_PATH1                                  0x3141
#define P31_44_YUV422_TO_444_CTRL                                   0x3144
#define P31_50_PORCH_COLOR_CTRL                                     0x3150
#define P31_51_PORCH_COLOR_R_M1                                     0x3151
#define P31_52_PORCH_COLOR_G_M1                                     0x3152
#define P31_53_PORCH_COLOR_B_M1                                     0x3153


//--------------------------------------------------
// I Domain Double Buffer (Page 31)
//--------------------------------------------------
#define P31_A0_I_DB_CTRL0                                           0x31A0
#define P31_A1_I_DB_CTRL1                                           0x31A1


//--------------------------------------------------
// D Domain Double Buffer (Page 31)
//--------------------------------------------------
#define P31_B0_D_DB_CTRL0                                           0x31B0


//--------------------------------------------------
// IMD Domain Double Buffer (Page 31)
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
// Panel Uniformity (Page 34)
//--------------------------------------------------
#define P34_00_UN_GLOBAL_CTRL                                       0x3400
#define P34_01_UN_MULTI_LUT_CTRL                                    0x3401
#define P34_02_UN_GAIN_LUT_HOR_GRIDS                                0x3402
#define P34_03_UN_GAIN_LUT_VER_GRIDS                                0x3403
#define P34_04_UN_GAIN_LUT_HOR_OFFSET                               0x3404
#define P34_05_UN_GAIN_LUT_VER_OFFSET                               0x3405
#define P34_06_UN_GAIN_LUT_ADDR_PORT_MSB                            0x3406
#define P34_07_UN_GAIN_LUT_ADDR_PORT_LSB                            0x3407
#define P34_08_UN_GAIN_LUT_ACCESS_PORT                              0x3408
#define P34_09_UN_SRAM_BIST                                         0x3409
#define P34_0A_UN_SRAM_DRF_BIST                                     0x340A
#define P34_0B_UN_FRONT_BACK_MODE                                   0x340B
#define P34_0C_UN_GAIN_LUT_HOR_BACK_OFFSET                          0x340C
#define P34_0D_UN_OFFSET_LUT_ADDR_PORT_MSB                          0x340D
#define P34_0E_UN_OFFSET_LUT_ADDR_PORT_LSB                          0x340E
#define P34_0F_UN_OFFSET_LUT_ACCESS_PORT                            0x340F
#define P34_10_UN_OFFSET_SRAM_BIST                                  0x3410
#define P34_11_UN_OFFSET_SRAM_DRF_BIST                              0x3411
#define P34_12_UN_DECAY_LUT_ADDR_PORT_MSB                           0x3412
#define P34_13_UN_DECAY_LUT_ADDR_PORT_LSB                           0x3413
#define P34_14_UN_DECAY_LUT_ACCESS_PORT                             0x3414
#define P34_15_UN_DECAY_SRAM_BIST                                   0x3415
#define P34_16_UN_DECAY_SRAM_DRF_BIST                               0x3416
#define P34_17_UN_DUMMY                                             0x3417


//--------------------------------------------------
// I Domain Cyclic-Redundant-Check(Page 36)
//--------------------------------------------------
#define P36_00_I_CRC_CTRL                                           0x3600
#define P36_01_I_MAIN1_CRC_1                                        0x3601
#define P36_02_I_MAIN1_CRC_2                                        0x3602
#define P36_03_I_MAIN1_CRC_3                                        0x3603
#define P36_04_I_MAIN1_CRC_4                                        0x3604
#define P36_05_I_MAIN1_CRC_5                                        0x3605
#define P36_06_I_MAIN1_CRC_6                                        0x3606


//--------------------------------------------------
// D Domain Cyclic-Redundant-Check(Page 36)
//--------------------------------------------------
#define P36_2C_D_CRC_CTRL                                           0x362C
#define P36_2D_D_MAIN1_CRC_1                                        0x362D
#define P36_2E_D_MAIN1_CRC_2                                        0x362E
#define P36_2F_D_MAIN1_CRC_3                                        0x362F
#define P36_30_D_MAIN1_CRC_4                                        0x3630
#define P36_31_D_MAIN1_CRC_5                                        0x3631
#define P36_32_D_MAIN1_CRC_6                                        0x3632


//--------------------------------------------------
// M Domain Cyclic-Redundant-Check(Page 36)
//--------------------------------------------------
#define P36_40_M_CRC_CTRL                                           0x3640
#define P36_41_M_M1_CRC_1                                           0x3641
#define P36_42_M_M1_CRC_2                                           0x3642
#define P36_43_M_M1_CRC_3                                           0x3643
#define P36_44_M_M1_CRC_4                                           0x3644
#define P36_45_M_M1_CRC_5                                           0x3645
#define P36_46_M_M1_CRC_6                                           0x3646


//--------------------------------------------------
// LVDS Combo DisplayPort Tx Digital PHY CTRL (Page 38)
//--------------------------------------------------
#define P38_80_DPTX_PN_SWAP1                                        0x3880
#define P38_81_DPTX_LANE_SWAP7_6                                    0x3881
#define P38_82_DPTX_LANE_SWAP5_4                                    0x3882
#define P38_83_DPTX_LANE_SWAP3_2                                    0x3883
#define P38_84_DPTX_LANE_SWAP1_0                                    0x3884
#define P38_85_PHY0_TXBIST_00_H2                                    0x3885
#define P38_86_PHY0_TXBIST_00_H1                                    0x3886
#define P38_87_PHY0_TXBIST_00_L2                                    0x3887
#define P38_88_PHY0_TXBIST_00_L1                                    0x3888
#define P38_89_PHY0_TXBIST_01_H2                                    0x3889
#define P38_8A_PHY0_TXBIST_01_H1                                    0x388A
#define P38_8B_PHY0_TXBIST_01_L2                                    0x388B
#define P38_8C_PHY0_TXBIST_01_L1                                    0x388C
#define P38_8D_PHY0_TXBIST_02_H2                                    0x388D
#define P38_8E_PHY0_TXBIST_02_H1                                    0x388E
#define P38_8F_PHY0_TXBIST_02_L2                                    0x388F
#define P38_90_PHY0_TXBIST_02_L1                                    0x3890
#define P38_91_PHY_RST                                              0x3891


//--------------------------------------------------
// LVDS Combo DisplayPort Tx Analog PHY CTRL SSC (Page 38)
//--------------------------------------------------
#define P38_D4_DPTX_CMU4                                            0x38D4
#define P38_D5_DPTX_CMU5                                            0x38D5
#define P38_D6_DPTX_CMU6                                            0x38D6
#define P38_D7_DPTX_CMU7                                            0x38D7
#define P38_D8_DPTX_CMU8                                            0x38D8
#define P38_D9_DPTX_CMU9                                            0x38D9
#define P38_DA_DPTX_CMU10                                           0x38DA
#define P38_DB_DPTX_CMU11                                           0x38DB
#define P38_DD_DPTX_CMU12                                           0x38DD
#define P38_DE_DPTX_CMU13                                           0x38DE
#define P38_DF_DPTX_CMU14                                           0x38DF
#define P38_E0_DPTX_CMU15                                           0x38E0
#define P38_E1_DPTX_CMU16                                           0x38E1
#define P38_E2_DPTX_CMU17                                           0x38E2
#define P38_E3_DPTX_CMU18                                           0x38E3
#define P38_E4_DPTX_CMU19                                           0x38E4
#define P38_E5_DPTX_CMU20                                           0x38E5
#define P38_E6_DPTX_CMU21                                           0x38E6
#define P38_E7_DPTX_CMU22                                           0x38E7


//--------------------------------------------------
// Control for LVDS display conversion (Page 39)
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
#define P39_24_LVDS_DRF_BIST_CTRL2                                  0x3924
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
#define P39_49_D_CONV_CRC_12_H                                      0x3949
#define P39_4A_D_CONV_CRC_12_L                                      0x394A
#define P39_4B_D_CONV_CRC_13_H                                      0x394B
#define P39_4C_D_CONV_CRC_13_L                                      0x394C
#define P39_4D_D_CONV_CRC_14_H                                      0x394D
#define P39_4E_D_CONV_CRC_14_L                                      0x394E
#define P39_4F_D_CONV_CRC_15_H                                      0x394F
#define P39_50_D_CONV_CRC_15_L                                      0x3950
#define P39_51_D_CONV_CRC_16_H                                      0x3951
#define P39_52_D_CONV_CRC_16_L                                      0x3952
#define P39_53_D_CONV_CRC_17_H                                      0x3953
#define P39_54_D_CONV_CRC_17_L                                      0x3954
#define P39_55_D_CONV_CRC_18_H                                      0x3955
#define P39_56_D_CONV_CRC_18_L                                      0x3956
#define P39_57_D_CONV_CRC_19_H                                      0x3957
#define P39_58_D_CONV_CRC_19_L                                      0x3958
#define P39_59_D_CONV_CRC_20_H                                      0x3959
#define P39_5A_D_CONV_CRC_20_L                                      0x395A
#define P39_5B_D_CONV_CRC_21_H                                      0x395B
#define P39_5C_D_CONV_CRC_21_L                                      0x395C
#define P39_5D_D_CONV_CRC_22_H                                      0x395D
#define P39_5E_D_CONV_CRC_22_L                                      0x395E
#define P39_5F_D_CONV_CRC_23_H                                      0x395F
#define P39_60_D_CONV_CRC_23_L                                      0x3960


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
// GroupD Power Control (Page 40)
//--------------------------------------------------
#define P40_0A_GD_POWER_CTRL                                        0x400A
#define P40_0B_TOP_DUMMY4                                           0x400B
#define P40_0D_TOP_DUMMY5                                           0x400D


//--------------------------------------------------
// TXCD Port Control for Analog LVDS (Page 55)
//--------------------------------------------------
#define P55_00_LVDS_COMMON_AB_CTRL0                                 0x5500
#define P55_01_LVDS_COMMON_AB_CTRL1                                 0x5501
#define P55_02_LVDS_COMMON_AB_CTRL2                                 0x5502
#define P55_03_LVDS_COMMON_AB_CTRL3                                 0x5503
#define P55_04_LVDS_COMMON_AB_CTRL4                                 0x5504
#define P55_05_LVDS_COMMON_AB_CTRL5                                 0x5505
#define P55_06_LVDS_COMMON_AB_CTRL6                                 0x5506
#define P55_07_LVDS_COMMON_AB_CTRL7                                 0x5507
#define P55_08_LVDS_COMMON_AB_CTRL8                                 0x5508
#define P55_09_LVDS_COMMON_AB_CTRL9                                 0x5509
#define P55_0A_LVDS_COMMON_AB_CTRL10                                0x550A
#define P55_0B_LVDS_COMMON_AB_CTRL11                                0x550B
#define P55_0D_LVDS_COMMON_AB_CTRL13                                0x550D
#define P55_0E_LVDS_COMMON_AB_CTRL14                                0x550E
#define P55_0F_LVDS_COMMON_AB_CTRL15                                0x550F
#define P55_10_LVDS_COMMON_AB_CTRL16                                0x5510
#define P55_11_LVDS_COMMON_AB_CTRL17                                0x5511
#define P55_20_LVDS_PORTA_CTRL0                                     0x5520
#define P55_21_LVDS_PORTA_CTRL1                                     0x5521
#define P55_22_LVDS_PORTA_CTRL2                                     0x5522
#define P55_23_LVDS_PORTA_CTRL3                                     0x5523
#define P55_24_LVDS_PORTA_CTRL4                                     0x5524
#define P55_25_LVDS_PORTA_CTRL5                                     0x5525
#define P55_26_LVDS_PORTA_CTRL6                                     0x5526
#define P55_28_LVDS_PORTA_CTRL8                                     0x5528
#define P55_29_LVDS_PORTA_CTRL9                                     0x5529
#define P55_2A_LVDS_PORTA_CTRL10                                    0x552A
#define P55_2B_LVDS_PORTA_CTRL11                                    0x552B
#define P55_2C_LVDS_PORTA_CTRL12                                    0x552C
#define P55_2D_LVDS_PORTA_CTRL13                                    0x552D
#define P55_30_LVDS_PORTB_CTRL0                                     0x5530
#define P55_31_LVDS_PORTB_CTRL1                                     0x5531
#define P55_32_LVDS_PORTB_CTRL2                                     0x5532
#define P55_33_LVDS_PORTB_CTRL3                                     0x5533
#define P55_34_LVDS_PORTB_CTRL4                                     0x5534
#define P55_35_LVDS_PORTB_CTRL5                                     0x5535
#define P55_36_LVDS_PORTB_CTRL6                                     0x5536
#define P55_37_LVDS_PORTB_CTRL7                                     0x5537
#define P55_38_LVDS_PORTB_CTRL8                                     0x5538
#define P55_3A_LVDS_PORTB_CTRL10                                    0x553A
#define P55_3B_LVDS_PORTB_CTRL11                                    0x553B
#define P55_3C_LVDS_PORTB_CTRL12                                    0x553C
#define P55_3D_LVDS_PORTB_CTRL13                                    0x553D


//--------------------------------------------------
// LVDS Combo DisplayPort Tx Analog PHY CTRL (Page 55)
//--------------------------------------------------
#define P55_50_DPTX_PREEM_TXA0                                      0x5550
#define P55_51_DPTX_PREEM_TXA1                                      0x5551
#define P55_52_DPTX_PREEM_TXB3                                      0x5552
#define P55_53_DPTX_PREEM_TXB4                                      0x5553
#define P55_54_DPTX_PRE_DRIVER_COMPENSATION                         0x5554
#define P55_55_DPTX_CKDELAY                                         0x5555
#define P55_56_DPTX_DOUBLE_HALF_CURRENT                             0x5556
#define P55_57_DPTX_SWING_CURRENT_1                                 0x5557
#define P55_58_DPTX_SWING_CURRENT_2                                 0x5558
#define P55_5D_DPTX_CKRDDUTY_SPD_SEL                                0x555D
#define P55_61_DPTX_Z0_TX_1                                         0x5561
#define P55_62_DPTX_Z0_TX_2                                         0x5562
#define P55_63_DPTX_Z0_TX_3                                         0x5563
#define P55_70_DPTX_CMU0                                            0x5570
#define P55_72_DPTX_CMU2                                            0x5572
#define P55_73_DPTX_CMU3                                            0x5573


//--------------------------------------------------
// HDCP 2.2 Overview (Page 63)
//--------------------------------------------------
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
#define P63_28_HDCP_RSA_TX_FUNTION1                                 0x6328
#define P63_29_HDCP_RSA_TX_FUNTION0                                 0x6329
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


//--------------------------------------------------
// D3 ECBUS APHY (Page 67)
//--------------------------------------------------
#define P67_00_ECBUS_EN                                             0x6700
#define P67_01_ECBUS_STEP_CTRL                                      0x6701
#define P67_02_ECBUS_SWITCH_CTRL                                    0x6702
#define P67_03_ECBUS_FEEDBACK_CTRL                                  0x6703
#define P67_04_EBUS_VREF_CTRL_0                                     0x6704
#define P67_05_EBUS_VREF_CTRL_1                                     0x6705
#define P67_06_ECBUS_Z0_CTRL_0                                      0x6706
#define P67_07_ECBUS_Z0_CTRL_1                                      0x6707
#define P67_08_ECBUS_DATA_CTRL                                      0x6708
#define P67_09_ECBUS_RESERVED_0                                     0x6709
#define P67_0A_ECBUS_RESERVED_1                                     0x670A
#define P67_0B_ECBUS_RESERVED_2                                     0x670B
#define P67_0C_ECBUS_PHY_BIST                                       0x670C
#define P67_0D_ECBUS_CMU_CONTROL_0                                  0x670D
#define P67_0E_ECBUS_CMU_CONTROL_1                                  0x670E
#define P67_0F_ECBUS_CMU_CONTROL_2                                  0x670F
#define P67_10_ECBUS_CMU_CONTROL_3                                  0x6710
#define P67_11_ECBUS_CMU_CONTROL_4                                  0x6711


//--------------------------------------------------
// D3 CBUS PHY (Page 67)
//--------------------------------------------------
#define P67_A0_CBUS_EN_0                                            0x67A0
#define P67_A1_CBUS_EN_1                                            0x67A1
#define P67_A2_CBUS_RES_AUTOK_0                                     0x67A2
#define P67_A3_CBUS_RES_AUTOK_1                                     0x67A3
#define P67_A4_CBUS_RES_AUTOK_2                                     0x67A4
#define P67_A5_CBUS_RES_AUTOK_3                                     0x67A5
#define P67_A6_CBUS_INPUT_CONTROL                                   0x67A6
#define P67_A7_CBUS_OUTPUT_CONTROL_0                                0x67A7
#define P67_A8_CBUS_OUTPUT_CONTROL_1                                0x67A8


//--------------------------------------------------
// D3 MHL3 OCBUS MAC (Page 68)
//--------------------------------------------------
#define P68_00_OCBUS_CTRL_00                                        0x6800
#define P68_01_OCBUS_CTRL_01                                        0x6801
#define P68_10_OCBUS_CTRL_10                                        0x6810
#define P68_11_OCBUS_CTRL_11                                        0x6811
#define P68_12_OCBUS_CTRL_12                                        0x6812
#define P68_13_OCBUS_CTRL_13                                        0x6813
#define P68_14_OCBUS_CTRL_14                                        0x6814
#define P68_15_OCBUS_CTRL_15                                        0x6815
#define P68_16_OCBUS_CTRL_16                                        0x6816
#define P68_17_OCBUS_CTRL_17                                        0x6817
#define P68_18_OCBUS_CTRL_18                                        0x6818
#define P68_19_OCBUS_CTRL_19                                        0x6819
#define P68_1A_OCBUS_CTRL_1A                                        0x681A
#define P68_1B_OCBUS_CTRL_1B                                        0x681B
#define P68_1C_OCBUS_CTRL_1C                                        0x681C
#define P68_1D_OCBUS_CTRL_1D                                        0x681D
#define P68_1E_OCBUS_CTRL_1E                                        0x681E
#define P68_1F_OCBUS_CTRL_1F                                        0x681F
#define P68_20_OCBUS_CTRL_20                                        0x6820
#define P68_21_OCBUS_CTRL_21                                        0x6821
#define P68_22_OCBUS_CTRL_22                                        0x6822
#define P68_23_OCBUS_CTRL_23                                        0x6823
#define P68_24_OCBUS_CTRL_24                                        0x6824
#define P68_25_OCBUS_CTRL_25                                        0x6825


//--------------------------------------------------
// D3 CBUS POWER ON MAC (Page 68)
//--------------------------------------------------
#define P68_A0_CBUS_CTRL_00                                         0x68A0
#define P68_A1_CBUS_CTRL_01                                         0x68A1
#define P68_A2_CBUS_CTRL_02                                         0x68A2
#define P68_A3_CBUS_CTRL_03                                         0x68A3
#define P68_A4_CBUS_CTRL_04                                         0x68A4
#define P68_A5_CBUS_CTRL_05                                         0x68A5
#define P68_A6_CBUS_CTRL_06                                         0x68A6
#define P68_A7_CBUS_CTRL_07                                         0x68A7
#define P68_A8_CBUS_CTRL_08                                         0x68A8
#define P68_A9_CBUS_CTRL_09                                         0x68A9
#define P68_AA_CBUS_CTRL_0A                                         0x68AA


//--------------------------------------------------
// D3 CBUS POWER OFF MAC (Page 68)
//--------------------------------------------------
#define P68_AB_CBUS_CTRL_0B                                         0x68AB
#define P68_AC_CBUS_CTRL_0C                                         0x68AC
#define P68_AD_CBUS_CTRL_0D                                         0x68AD
#define P68_AE_CBUS_CTRL_0E                                         0x68AE
#define P68_AF_CBUS_CTRL_0F                                         0x68AF
#define P68_B0_CBUS_CTRL_10                                         0x68B0
#define P68_B1_CBUS_CTRL_11                                         0x68B1
#define P68_B2_CBUS_CTRL_12                                         0x68B2
#define P68_B3_CBUS_CTRL_13                                         0x68B3
#define P68_B4_CBUS_CTRL_14                                         0x68B4
#define P68_B5_CBUS_CTRL_15                                         0x68B5
#define P68_B6_CBUS_CTRL_16                                         0x68B6
#define P68_B7_CBUS_CTRL_17                                         0x68B7
#define P68_B8_CBUS_CTRL_18                                         0x68B8
#define P68_BA_CBUS_CTRL_1A                                         0x68BA
#define P68_BB_CBUS_CTRL_1B                                         0x68BB
#define P68_BC_CBUS_CTRL_1C                                         0x68BC
#define P68_BD_CBUS_CTRL_1D                                         0x68BD
#define P68_BE_CBUS_CTRL_1E                                         0x68BE
#define P68_BF_CBUS_CTRL_1F                                         0x68BF
#define P68_C0_CBUS_CTRL_20                                         0x68C0
#define P68_C1_CBUS_CTRL_21                                         0x68C1
#define P68_C2_CBUS_CTRL_22                                         0x68C2
#define P68_C3_CBUS_CTRL_23                                         0x68C3
#define P68_C4_CBUS_CTRL_24                                         0x68C4
#define P68_C5_CBUS_CTRL_25                                         0x68C5
#define P68_C6_CBUS_CTRL_26                                         0x68C6
#define P68_C8_CBUS_CTRL_28                                         0x68C8
#define P68_C9_CBUS_CTRL_29                                         0x68C9
#define P68_CA_CBUS_CTRL_2A                                         0x68CA
#define P68_CB_CBUS_CTRL_2B                                         0x68CB
#define P68_CC_CBUS_CTRL_2C                                         0x68CC
#define P68_CD_CBUS_CTRL_2D                                         0x68CD
#define P68_CE_CBUS_CTRL_2E                                         0x68CE
#define P68_CF_CBUS_CTRL_2F                                         0x68CF
#define P68_D0_CBUS_CTRL_30                                         0x68D0
#define P68_D1_CBUS_CTRL_31                                         0x68D1
#define P68_D2_CBUS_CTRL_32                                         0x68D2
#define P68_D3_CBUS_CTRL_33                                         0x68D3
#define P68_D4_CBUS_CTRL_34                                         0x68D4
#define P68_D5_CBUS_CTRL_35                                         0x68D5
#define P68_D6_CBUS_CTRL_36                                         0x68D6
#define P68_D7_CBUS_CTRL_37                                         0x68D7
#define P68_D8_CBUS_CTRL_38                                         0x68D8
#define P68_D9_CBUS_CTRL_39                                         0x68D9
#define P68_DA_CBUS_CTRL_3A                                         0x68DA
#define P68_DB_CBUS_CTRL_3B                                         0x68DB
#define P68_DC_CBUS_CTRL_3C                                         0x68DC
#define P68_DD_CBUS_CTRL_3D                                         0x68DD
#define P68_DE_CBUS_CTRL_3E                                         0x68DE
#define P68_DF_CBUS_CTRL_3F                                         0x68DF
#define P68_E0_CBUS_CTRL_40                                         0x68E0
#define P68_E1_CBUS_CTRL_41                                         0x68E1
#define P68_E2_CBUS_CTRL_42                                         0x68E2
#define P68_E3_CBUS_CTRL_43                                         0x68E3
#define P68_E4_CBUS_CTRL_44                                         0x68E4
#define P68_E5_CBUS_CTRL_45                                         0x68E5
#define P68_E6_CBUS_CTRL_46                                         0x68E6
#define P68_E7_CBUS_CTRL_47                                         0x68E7
#define P68_E8_CBUS_CTRL_48                                         0x68E8
#define P68_E9_CBUS_CTRL_49                                         0x68E9
#define P68_EA_CBUS_CTRL_4A                                         0x68EA
#define P68_EB_CBUS_CTRL_4B                                         0x68EB
#define P68_EC_CBUS_CTRL_4C                                         0x68EC
#define P68_ED_CBUS_CTRL_4D                                         0x68ED
#define P68_EE_CBUS_CTRL_4E                                         0x68EE
#define P68_EF_CBUS_CTRL_4F                                         0x68EF
#define P68_F0_CBUS_CTRL_50                                         0x68F0
#define P68_F1_CBUS_CTRL_51                                         0x68F1
#define P68_F2_CBUS_CTRL_52                                         0x68F2
#define P68_F3_CBUS_CTRL_53                                         0x68F3
#define P68_F4_CBUS_CTRL_54                                         0x68F4
#define P68_F5_CBUS_CTRL_55                                         0x68F5
#define P68_F6_CBUS_CTRL_56                                         0x68F6
#define P68_F7_CBUS_CTRL_57                                         0x68F7
#define P68_F8_CBUS_CTRL_58                                         0x68F8
#define P68_F9_CBUS_CTRL_59                                         0x68F9
#define P68_FA_CBUS_CTRL_5A                                         0x68FA
#define P68_FB_CBUS_CTRL_5B                                         0x68FB
#define P68_FC_CBUS_CTRL_5C                                         0x68FC
#define P68_FD_CBUS_CTRL_5D                                         0x68FD


//--------------------------------------------------
// ADI Global Control (Page 6F)
//--------------------------------------------------
#define P6F_00_MUX_DIG_OUT                                          0x6F00
#define P6F_01_MUX_DA_DVC_IN                                        0x6F01
#define P6F_02_MUX_DP_I2S_IN                                        0x6F02
#define P6F_03_MUX_TST_OUT                                          0x6F03
#define P6F_04_CBUS2_MAP_DDC                                        0x6F04
#define P6F_10_ADI_IRQ_CTRL                                         0x6F10


//--------------------------------------------------
// ADI Power Control (Page 6F)
//--------------------------------------------------
#define P6F_20_D0_POWER_CTRL                                        0x6F20
#define P6F_21_D1_POWER_CTRL                                        0x6F21
#define P6F_22_D2_POWER_CTRL                                        0x6F22
#define P6F_23_D3_POWER_CTRL                                        0x6F23
#define P6F_24_D4_POWER_CTRL                                        0x6F24
#define P6F_25_D5_POWER_CTRL                                        0x6F25
#define P6F_26_ADI_POWER_CTRL                                       0x6F26


//--------------------------------------------------
// D2 Port HDMI2.0 Function (Page 71)
//--------------------------------------------------
#define P71_00_HDMI_CTRL_00                                         0x7100
#define P71_01_HDMI_CTRL_01                                         0x7101
#define P71_02_HDMI_CTRL_02                                         0x7102
#define P71_03_HDMI_CTRL_03                                         0x7103
#define P71_04_HDMI_CTRL_04                                         0x7104
#define P71_05_HDMI_CTRL_05                                         0x7105
#define P71_06_HDMI_CTRL_06                                         0x7106
#define P71_07_HDMI_CTRL_07                                         0x7107
#define P71_08_HDMI_CTRL_08                                         0x7108
#define P71_0B_HDMI_CTRL_0B                                         0x710B
#define P71_0C_HDMI_CTRL_0C                                         0x710C
#define P71_0D_HDMI_CTRL_0D                                         0x710D
#define P71_0E_HDMI_CTRL_0E                                         0x710E
#define P71_0F_HDMI_CTRL_0F                                         0x710F
#define P71_10_HDMI_CTRL_10                                         0x7110
#define P71_11_HDMI_CTRL_11                                         0x7111
#define P71_12_HDMI_CTRL_12                                         0x7112
#define P71_13_HDMI_CTRL_13                                         0x7113
#define P71_14_HDMI_CTRL_14                                         0x7114
#define P71_15_HDMI_CTRL_15                                         0x7115
#define P71_16_HDMI_CTRL_16                                         0x7116
#define P71_17_HDMI_CTRL_17                                         0x7117
#define P71_18_HDMI_CTRL_18                                         0x7118
#define P71_19_HDMI_CTRL_19                                         0x7119
#define P71_1A_HDMI_CTRL_1A                                         0x711A
#define P71_1B_HDMI_CTRL_1B                                         0x711B
#define P71_1C_HDMI_CTRL_1C                                         0x711C
#define P71_1D_HDMI_CTRL_1D                                         0x711D
#define P71_1E_HDMI_CTRL_1E                                         0x711E
#define P71_1F_HDMI_CTRL_1F                                         0x711F
#define P71_20_HDMI_CTRL_20                                         0x7120
#define P71_21_HDMI_CTRL_21                                         0x7121
#define P71_22_HDMI_CTRL_22                                         0x7122
#define P71_23_HDMI_CTRL_23                                         0x7123
#define P71_24_HDMI_CTRL_24                                         0x7124
#define P71_25_HDMI_CTRL_25                                         0x7125
#define P71_26_HDMI_CTRL_26                                         0x7126
#define P71_27_HDMI_CTRL_27                                         0x7127
#define P71_28_HDMI_CTRL_28                                         0x7128
#define P71_29_HDMI_CTRL_29                                         0x7129
#define P71_2A_HDMI_CTRL_2A                                         0x712A
#define P71_2B_HDMI_CTRL_2B                                         0x712B
#define P71_2C_HDMI_CTRL_2C                                         0x712C
#define P71_2D_HDMI_CTRL_2D                                         0x712D
#define P71_2E_HDMI_CTRL_2E                                         0x712E
#define P71_38_HDMI_CTRL_38                                         0x7138
#define P71_39_HDMI_CTRL_39                                         0x7139
#define P71_3A_HDMI_CTRL_3A                                         0x713A
#define P71_40_HDMI_PCK_40                                          0x7140
#define P71_41_HDMI_PCK_41                                          0x7141
#define P71_42_HDMI_PCK_42                                          0x7142
#define P71_43_HDMI_PCK_43                                          0x7143
#define P71_44_HDMI_PCK_44                                          0x7144
#define P71_45_HDMI_PCK_45                                          0x7145
#define P71_46_HDMI_PCK_46                                          0x7146
#define P71_47_HDMI_PCK_47                                          0x7147
#define P71_48_HDMI_PCK_48                                          0x7148
#define P71_49_HDMI_20_49                                           0x7149
#define P71_50_HDMI_20_50                                           0x7150
#define P71_51_HDMI_20_51                                           0x7151


//--------------------------------------------------
// D2 Port IVHS Delay for HDMI (Page 71)
//--------------------------------------------------
#define P71_70_IVHS_CTRL_0                                          0x7170
#define P71_71_IVHS_CTRL_1                                          0x7171
#define P71_72_IVHS_CTRL_2                                          0x7172
#define P71_73_IVHS_CTRL_3                                          0x7173
#define P71_74_IVHS_CTRL_4                                          0x7174
#define P71_75_IVHS_CTRL_5                                          0x7175
#define P71_76_IVHS_CTRL_6                                          0x7176


//--------------------------------------------------
// D2 Port Overall HDMI System Function Block (Page 71)
//--------------------------------------------------
#define P71_A1_TMDS_MSR                                             0x71A1
#define P71_A2_TMDS_MRR0                                            0x71A2
#define P71_A3_TMDS_MRR1                                            0x71A3
#define P71_A4_TMDS_CTRL                                            0x71A4
#define P71_A5_TMDS_CRCOB2                                          0x71A5
#define P71_A6_TMDS_OUTCTL                                          0x71A6
#define P71_A7_TMDS_PWDCTL                                          0x71A7
#define P71_A8_TMDS_ACC0                                            0x71A8
#define P71_A9_TMDS_ABC0                                            0x71A9
#define P71_AA_TMDS_ABC1                                            0x71AA
#define P71_AB_TMDS_ACC2                                            0x71AB
#define P71_AC_TMDS_Z0CC2                                           0x71AC
#define P71_AD_TMDS_CPS                                             0x71AD
#define P71_AE_TMDS_RPS                                             0x71AE
#define P71_AF_TMDS_WDC                                             0x71AF
#define P71_B0_TMDS_CHANNEL_FIFO                                    0x71B0
#define P71_B4_TMDS_DPC0                                            0x71B4
#define P71_B5_TMDS_UDC0                                            0x71B5
#define P71_B6_TMDS_UDC1                                            0x71B6
#define P71_B7_TMDS_UDC2                                            0x71B7
#define P71_B8_TMDS_DPC1                                            0x71B8
#define P71_B9_TMDS_OUT_CTRL                                        0x71B9
#define P71_BA_TMDS_ROUT_HIGH_BYTE                                  0x71BA
#define P71_BB_TMDS_ROUT_LOW_BYTE                                   0x71BB
#define P71_BC_TMDS_GOUT_HIGH_BYTE                                  0x71BC
#define P71_BD_TMDS_GOUT_LOW_BYTE                                   0x71BD
#define P71_BE_TMDS_BOUT_HIGH_BYTE                                  0x71BE
#define P71_BF_TMDS_BOUT_LOW_BYTE                                   0x71BF
#define P71_C0_HDCP_CR                                              0x71C0
#define P71_C1_HDCP_DKAP                                            0x71C1
#define P71_C2_HDCP_PCR                                             0x71C2
#define P71_C3_HDCP_AP                                              0x71C3
#define P71_C4_HDCP_DP                                              0x71C4
#define P71_C8_HDMI_APC                                             0x71C8
#define P71_C9_HDMI_AP                                              0x71C9
#define P71_CA_HDMI_DP                                              0x71CA
#define P71_CB_HDMI_SR                                              0x71CB
#define P71_CC_HDMI_GPVS                                            0x71CC
#define P71_CD_HDMI_PSAP                                            0x71CD
#define P71_CE_HDMI_PSDP                                            0x71CE
#define P71_E0_AUX_PS_CTRL                                          0x71E0
#define P71_E1_AUX_PS_REPLY                                         0x71E1
#define P71_E6_HDMI_FREQDET_CTRL                                    0x71E6
#define P71_E7_HDMI_FREQDET_OFFSET                                  0x71E7
#define P71_E8_HDMI_FREQDET_UPPER_M                                 0x71E8
#define P71_E9_HDMI_FREQDET_UPPER_L                                 0x71E9
#define P71_EA_HDMI_FREQDET_LOWER_M                                 0x71EA
#define P71_EB_HDMI_FREQDET_LOWER_L                                 0x71EB
#define P71_EC_HDMI_FREQDET_STABLE                                  0x71EC
#define P71_ED_HDMI_FREQDET_RESULT_M                                0x71ED
#define P71_EE_HDMI_FREQDET_RESULT_L                                0x71EE
#define P71_EF_HDMI_ERROR_TH                                        0x71EF
#define P71_F6_HDMI_FREQDET_BOUND_H                                 0x71F6
#define P71_F7_HDMI_FREQDET_RESULT_H                                0x71F7


//--------------------------------------------------
// D3 Port HDMI2.0 Function (Page 72)
//--------------------------------------------------
#define P72_00_HDMI_CTRL_00                                         0x7200
#define P72_01_HDMI_CTRL_01                                         0x7201
#define P72_02_HDMI_CTRL_02                                         0x7202
#define P72_03_HDMI_CTRL_03                                         0x7203
#define P72_04_HDMI_CTRL_04                                         0x7204
#define P72_05_HDMI_CTRL_05                                         0x7205
#define P72_06_HDMI_CTRL_06                                         0x7206
#define P72_07_HDMI_CTRL_07                                         0x7207
#define P72_08_HDMI_CTRL_08                                         0x7208
#define P72_0B_HDMI_CTRL_0B                                         0x720B
#define P72_0C_HDMI_CTRL_0C                                         0x720C
#define P72_0D_HDMI_CTRL_0D                                         0x720D
#define P72_0E_HDMI_CTRL_0E                                         0x720E
#define P72_0F_HDMI_CTRL_0F                                         0x720F
#define P72_10_HDMI_CTRL_10                                         0x7210
#define P72_11_HDMI_CTRL_11                                         0x7211
#define P72_12_HDMI_CTRL_12                                         0x7212
#define P72_13_HDMI_CTRL_13                                         0x7213
#define P72_14_HDMI_CTRL_14                                         0x7214
#define P72_15_HDMI_CTRL_15                                         0x7215
#define P72_16_HDMI_CTRL_16                                         0x7216
#define P72_17_HDMI_CTRL_17                                         0x7217
#define P72_18_HDMI_CTRL_18                                         0x7218
#define P72_19_HDMI_CTRL_19                                         0x7219
#define P72_1A_HDMI_CTRL_1A                                         0x721A
#define P72_1B_HDMI_CTRL_1B                                         0x721B
#define P72_1C_HDMI_CTRL_1C                                         0x721C
#define P72_1D_HDMI_CTRL_1D                                         0x721D
#define P72_1E_HDMI_CTRL_1E                                         0x721E
#define P72_1F_HDMI_CTRL_1F                                         0x721F
#define P72_20_HDMI_CTRL_20                                         0x7220
#define P72_21_HDMI_CTRL_21                                         0x7221
#define P72_22_HDMI_CTRL_22                                         0x7222
#define P72_23_HDMI_CTRL_23                                         0x7223
#define P72_24_HDMI_CTRL_24                                         0x7224
#define P72_25_HDMI_CTRL_25                                         0x7225
#define P72_26_HDMI_CTRL_26                                         0x7226
#define P72_27_HDMI_CTRL_27                                         0x7227
#define P72_28_HDMI_CTRL_28                                         0x7228
#define P72_29_HDMI_CTRL_29                                         0x7229
#define P72_2A_HDMI_CTRL_2A                                         0x722A
#define P72_2B_HDMI_CTRL_2B                                         0x722B
#define P72_2C_HDMI_CTRL_2C                                         0x722C
#define P72_2D_HDMI_CTRL_2D                                         0x722D
#define P72_2E_HDMI_CTRL_2E                                         0x722E
#define P72_38_HDMI_CTRL_38                                         0x7238
#define P72_39_HDMI_CTRL_39                                         0x7239
#define P72_3A_HDMI_CTRL_3A                                         0x723A
#define P72_40_HDMI_PCK_40                                          0x7240
#define P72_41_HDMI_PCK_41                                          0x7241
#define P72_42_HDMI_PCK_42                                          0x7242
#define P72_43_HDMI_PCK_43                                          0x7243
#define P72_44_HDMI_PCK_44                                          0x7244
#define P72_45_HDMI_PCK_45                                          0x7245
#define P72_46_HDMI_PCK_46                                          0x7246
#define P72_47_HDMI_PCK_47                                          0x7247
#define P72_48_HDMI_PCK_48                                          0x7248
#define P72_49_HDMI_20_49                                           0x7249
#define P72_50_HDMI_20_50                                           0x7250
#define P72_51_HDMI_20_51                                           0x7251


//--------------------------------------------------
// D3 Port IVHS Delay for HDMI (Page 72)
//--------------------------------------------------
#define P72_70_IVHS_CTRL_0                                          0x7270
#define P72_71_IVHS_CTRL_1                                          0x7271
#define P72_72_IVHS_CTRL_2                                          0x7272
#define P72_73_IVHS_CTRL_3                                          0x7273
#define P72_74_IVHS_CTRL_4                                          0x7274
#define P72_75_IVHS_CTRL_5                                          0x7275
#define P72_76_IVHS_CTRL_6                                          0x7276


//--------------------------------------------------
// D3 Port Overall HDMI System Function Block (Page 72)
//--------------------------------------------------
#define P72_A1_TMDS_MSR                                             0x72A1
#define P72_A2_TMDS_MRR0                                            0x72A2
#define P72_A3_TMDS_MRR1                                            0x72A3
#define P72_A4_TMDS_CTRL                                            0x72A4
#define P72_A5_TMDS_CRCOB2                                          0x72A5
#define P72_A6_TMDS_OUTCTL                                          0x72A6
#define P72_A7_TMDS_PWDCTL                                          0x72A7
#define P72_A8_TMDS_ACC0                                            0x72A8
#define P72_A9_TMDS_ABC0                                            0x72A9
#define P72_AA_TMDS_ABC1                                            0x72AA
#define P72_AB_TMDS_ACC2                                            0x72AB
#define P72_AC_TMDS_Z0CC2                                           0x72AC
#define P72_AD_TMDS_CPS                                             0x72AD
#define P72_AE_TMDS_RPS                                             0x72AE
#define P72_AF_TMDS_WDC                                             0x72AF
#define P72_B0_TMDS_CHANNEL_FIFO                                    0x72B0
#define P72_B4_TMDS_DPC0                                            0x72B4
#define P72_B5_TMDS_UDC0                                            0x72B5
#define P72_B6_TMDS_UDC1                                            0x72B6
#define P72_B7_TMDS_UDC2                                            0x72B7
#define P72_B8_TMDS_DPC1                                            0x72B8
#define P72_B9_TMDS_OUT_CTRL                                        0x72B9
#define P72_BA_TMDS_ROUT_HIGH_BYTE                                  0x72BA
#define P72_BB_TMDS_ROUT_LOW_BYTE                                   0x72BB
#define P72_BC_TMDS_GOUT_HIGH_BYTE                                  0x72BC
#define P72_BD_TMDS_GOUT_LOW_BYTE                                   0x72BD
#define P72_BE_TMDS_BOUT_HIGH_BYTE                                  0x72BE
#define P72_BF_TMDS_BOUT_LOW_BYTE                                   0x72BF
#define P72_C0_HDCP_CR                                              0x72C0
#define P72_C1_HDCP_DKAP                                            0x72C1
#define P72_C2_HDCP_PCR                                             0x72C2
#define P72_C3_HDCP_AP                                              0x72C3
#define P72_C4_HDCP_DP                                              0x72C4
#define P72_C8_HDMI_APC                                             0x72C8
#define P72_C9_HDMI_AP                                              0x72C9
#define P72_CA_HDMI_DP                                              0x72CA
#define P72_CB_HDMI_SR                                              0x72CB
#define P72_CC_HDMI_GPVS                                            0x72CC
#define P72_CD_HDMI_PSAP                                            0x72CD
#define P72_CE_HDMI_PSDP                                            0x72CE
#define P72_E0_AUX_PS_CTRL                                          0x72E0
#define P72_E1_AUX_PS_REPLY                                         0x72E1
#define P72_E6_HDMI_FREQDET_CTRL                                    0x72E6
#define P72_E7_HDMI_FREQDET_OFFSET                                  0x72E7
#define P72_E8_HDMI_FREQDET_UPPER_M                                 0x72E8
#define P72_E9_HDMI_FREQDET_UPPER_L                                 0x72E9
#define P72_EA_HDMI_FREQDET_LOWER_M                                 0x72EA
#define P72_EB_HDMI_FREQDET_LOWER_L                                 0x72EB
#define P72_EC_HDMI_FREQDET_STABLE                                  0x72EC
#define P72_ED_HDMI_FREQDET_RESULT_M                                0x72ED
#define P72_EE_HDMI_FREQDET_RESULT_L                                0x72EE
#define P72_EF_HDMI_ERROR_TH                                        0x72EF
#define P72_F6_HDMI_FREQDET_BOUND_H                                 0x72F6
#define P72_F7_HDMI_FREQDET_RESULT_H                                0x72F7


//--------------------------------------------------
// D2 MHL3.0 MAC (Page 76)
//--------------------------------------------------
#define P76_00_MHL_EN                                               0x7600
#define P76_01_MHL_FIFO_CTRL                                        0x7601
#define P76_02_MHL_BIST_CTRL                                        0x7602
#define P76_03_MHL_BIST_CONFIG_1                                    0x7603
#define P76_04_MHL_BIST_CONFIG_2                                    0x7604
#define P76_05_MHL_BIST_ERR_CNT_H                                   0x7605
#define P76_06_MHL_BIST_ERR_CNT_L                                   0x7606
#define P76_07_MHL_DATA_ALIGN_CTRL                                  0x7607
#define P76_08_MHL_PKT_DECODE_CONFIG                                0x7608
#define P76_09_MHL_PKT_DECODE_SEED_H                                0x7609
#define P76_0A_MHL_PKT_DECODE_SEED_L                                0x760A
#define P76_0B_MHL_S2P                                              0x760B
#define P76_0C_MHL_FIFO_FLAG                                        0x760C
#define P76_0D_MHL_BIST_DURATION                                    0x760D
#define P76_0E_MHL_BIST_FIFO_FLAG2                                  0x760E
#define P76_0F_MHL_DEBOUNCE                                         0x760F
#define P76_10_REG_MHL3_OUTPUT_0                                    0x7610
#define P76_11_REG_MHL3_OUTPUT_1                                    0x7611
#define P76_12_REG_MHL3_OUTPUT_2                                    0x7612
#define P76_13_REG_MHL3_OUTPUT_3                                    0x7613
#define P76_14_REG_MHL3_OUTPUT_4                                    0x7614
#define P76_15_REG_MHL3_OUTPUT_5                                    0x7615
#define P76_16_REG_MHL3_OUTPUT_6                                    0x7616
#define P76_17_REG_MHL3_OUTPUT_7                                    0x7617
#define P76_18_REG_MHL3_OUTPUT_8                                    0x7618
#define P76_19_REG_MHL3_OUTPUT_9                                    0x7619
#define P76_1A_REG_MHL3_OUTPUT_A                                    0x761A
#define P76_1B_REG_MHL3_OUTPUT_B                                    0x761B
#define P76_1C_REG_MHL3_CP_VS_MASK_C0                               0x761C
#define P76_1D_REG_MHL3_CP_VS_MASK_C1                               0x761D
#define P76_1E_REG_MHL3_WATER_REC                                   0x761E
#define P76_20_MHL_MEASURE_0                                        0x7620
#define P76_21_MHL_MEASURE_1                                        0x7621
#define P76_22_MHL_MEASURE_2                                        0x7622
#define P76_23_MHL_MEASURE_3                                        0x7623
#define P76_24_MHL_MEASURE_4                                        0x7624
#define P76_25_MHL_MEASURE_5                                        0x7625
#define P76_26_MHL_MEASURE_6                                        0x7626
#define P76_27_MHL_MEASURE_7                                        0x7627
#define P76_28_MHL_MEASURE_8                                        0x7628
#define P76_29_MHL_MEASURE_9                                        0x7629
#define P76_2A_MHL_MEASURE_10                                       0x762A
#define P76_2B_MHL_MEASURE_11                                       0x762B
#define P76_2C_MHL_MEASURE_12                                       0x762C
#define P76_2D_MHL_MEASURE_13                                       0x762D
#define P76_2E_MHL_MEASURE_14                                       0x762E
#define P76_2F_MHL_MEASURE_15                                       0x762F
#define P76_30_MHL_MEASURE_16                                       0x7630
#define P76_31_MHL_MEASURE_17                                       0x7631
#define P76_32_MHL_MEASURE_18                                       0x7632
#define P76_33_MHL_MEASURE_19                                       0x7633
#define P76_34_MHL_MEASURE_20                                       0x7634
#define P76_35_MHL_MEASURE_21                                       0x7635
#define P76_36_MHL_MEASURE_22                                       0x7636
#define P76_37_MHL_MEASURE_23                                       0x7637
#define P76_38_MHL_MEASURE_24                                       0x7638
#define P76_39_MHL_MEASURE_27                                       0x7639
#define P76_3A_MHL_MEASURE_28                                       0x763A
#define P76_3B_MHL_MEASURE_29                                       0x763B
#define P76_3C_MHL_MEASURE_30                                       0x763C
#define P76_3D_MHL_MEASURE_31                                       0x763D
#define P76_3E_MHL_MEASURE_32                                       0x763E
#define P76_3F_MHL_MEASURE_33                                       0x763F
#define P76_40_MHL_MEASURE_34                                       0x7640
#define P76_41_DPF_CTRL_0                                           0x7641
#define P76_42_DP_OUTPUT_CTRL                                       0x7642
#define P76_43_EVBLK2VS_H                                           0x7643
#define P76_44_EVBLK2VS_M                                           0x7644
#define P76_45_EVBLK2VS_L                                           0x7645
#define P76_46_OVBLK2VS_H                                           0x7646
#define P76_47_OVBLK2VS_M                                           0x7647
#define P76_48_OVBLK2VS_L                                           0x7648
#define P76_49_BS2HS_0                                              0x7649
#define P76_4A_BS2HS_1                                              0x764A
#define P76_4B_VS_FRONT_PORCH                                       0x764B
#define P76_4C_MN_DPF_HTT_M                                         0x764C
#define P76_4D_MN_DPF_HTT_L                                         0x764D
#define P76_4E_MN_DPF_HST_M                                         0x764E
#define P76_4F_MN_DPF_HST_L                                         0x764F
#define P76_50_MN_DPF_HWD_M                                         0x7650
#define P76_51_MN_DPF_HWD_L                                         0x7651
#define P76_52_MN_DPF_HSW_M                                         0x7652
#define P76_53_MN_DPF_HSW_L                                         0x7653
#define P76_54_MN_DPF_VTT_M                                         0x7654
#define P76_55_MN_DPF_VTT_L                                         0x7655
#define P76_56_MN_DPF_VST_M                                         0x7656
#define P76_57_MN_DPF_VST_L                                         0x7657
#define P76_58_MN_DPF_VHT_M                                         0x7658
#define P76_59_MN_DPF_VHT_L                                         0x7659
#define P76_5A_MN_DPF_VSW_M                                         0x765A
#define P76_5B_MN_DPF_VSW_L                                         0x765B
#define P76_5C_INTERLACE_MODE_CONFIG                                0x765C
#define P76_5D_TEST0                                                0x765D
#define P76_5E_MHL_TEST_OUT_SEL                                     0x765E
#define P76_80_REG_MHL3_CP0                                         0x7680
#define P76_81_REG_MHL3_CP1                                         0x7681
#define P76_82_REG_MHL3_CP2                                         0x7682
#define P76_83_REG_MHL3_CP3                                         0x7683
#define P76_84_REG_MHL3_CP4                                         0x7684
#define P76_85_REG_MHL3_CP5                                         0x7685
#define P76_86_REG_MHL3_CP6                                         0x7686
#define P76_87_REG_MHL3_CP7                                         0x7687
#define P76_88_REG_MHL3_CP8                                         0x7688
#define P76_89_REG_MHL3_CP9                                         0x7689
#define P76_8A_REG_MHL3_CP10                                        0x768A
#define P76_8B_REG_MHL3_CP11                                        0x768B
#define P76_8C_REG_MHL3_CP12                                        0x768C
#define P76_8D_REG_MHL3_CP13                                        0x768D
#define P76_8E_REG_MHL3_CP14                                        0x768E
#define P76_8F_REG_MHL3_CP15                                        0x768F
#define P76_90_REG_MHL3_CP16                                        0x7690
#define P76_91_REG_MHL3_CP17                                        0x7691
#define P76_92_REG_MHL3_CP18                                        0x7692
#define P76_93_REG_MHL3_CP19                                        0x7693
#define P76_94_MHL3_SRAM_BIST_0                                     0x7694
#define P76_95_MHL3_SRAM_BIST_1                                     0x7695


//--------------------------------------------------
// D2 MHL2.0 MAC (Page 76)
//--------------------------------------------------
#define P76_A0_MHL_CTRL_00                                          0x76A0
#define P76_A1_MHL_CTRL_01                                          0x76A1
#define P76_A2_MHL_CTRL_02                                          0x76A2
#define P76_A3_MHL_CTRL_03                                          0x76A3
#define P76_A4_MHL_CTRL_04                                          0x76A4
#define P76_A5_MHL_CTRL_05                                          0x76A5
#define P76_A6_MHL_CTRL_06                                          0x76A6
#define P76_A7_MHL_CTRL_07                                          0x76A7
#define P76_A8_MHL_CTRL_08                                          0x76A8
#define P76_A9_MHL_CTRL_09                                          0x76A9
#define P76_AA_MHL_CTRL_0A                                          0x76AA
#define P76_AB_MHL_CTRL_0B                                          0x76AB
#define P76_AC_MHL_CTRL_0C                                          0x76AC
#define P76_AD_MHL_CTRL_0D                                          0x76AD
#define P76_AE_MHL_CTRL_0E                                          0x76AE
#define P76_AF_MHL_CTRL_0F                                          0x76AF
#define P76_B0_MHL_CTRL_10                                          0x76B0
#define P76_B1_MHL_CTRL_11                                          0x76B1
#define P76_B2_MHL_CTRL_12                                          0x76B2
#define P76_B3_MHL_CTRL_13                                          0x76B3
#define P76_B4_MHL_CTRL_14                                          0x76B4
#define P76_B5_MHL_CTRL_15                                          0x76B5
#define P76_B6_MHL_CTRL_16                                          0x76B6


//--------------------------------------------------
// D3 MHL3.0 MAC (Page 77)
//--------------------------------------------------
#define P77_00_MHL_EN                                               0x7700
#define P77_01_MHL_FIFO_CTRL                                        0x7701
#define P77_02_MHL_BIST_CTRL                                        0x7702
#define P77_03_MHL_BIST_CONFIG_1                                    0x7703
#define P77_04_MHL_BIST_CONFIG_2                                    0x7704
#define P77_05_MHL_BIST_ERR_CNT_H                                   0x7705
#define P77_06_MHL_BIST_ERR_CNT_L                                   0x7706
#define P77_07_MHL_DATA_ALIGN_CTRL                                  0x7707
#define P77_08_MHL_PKT_DECODE_CONFIG                                0x7708
#define P77_09_MHL_PKT_DECODE_SEED_H                                0x7709
#define P77_0A_MHL_PKT_DECODE_SEED_L                                0x770A
#define P77_0B_MHL_S2P                                              0x770B
#define P77_0C_MHL_FIFO_FLAG                                        0x770C
#define P77_0D_MHL_BIST_DURATION                                    0x770D
#define P77_0E_MHL_BIST_FIFO_FLAG2                                  0x770E
#define P77_0F_MHL_DEBOUNCE                                         0x770F
#define P77_10_REG_MHL3_OUTPUT_0                                    0x7710
#define P77_11_REG_MHL3_OUTPUT_1                                    0x7711
#define P77_12_REG_MHL3_OUTPUT_2                                    0x7712
#define P77_13_REG_MHL3_OUTPUT_3                                    0x7713
#define P77_14_REG_MHL3_OUTPUT_4                                    0x7714
#define P77_15_REG_MHL3_OUTPUT_5                                    0x7715
#define P77_16_REG_MHL3_OUTPUT_6                                    0x7716
#define P77_17_REG_MHL3_OUTPUT_7                                    0x7717
#define P77_18_REG_MHL3_OUTPUT_8                                    0x7718
#define P77_19_REG_MHL3_OUTPUT_9                                    0x7719
#define P77_1A_REG_MHL3_OUTPUT_A                                    0x771A
#define P77_1B_REG_MHL3_OUTPUT_B                                    0x771B
#define P77_1C_REG_MHL3_CP_VS_MASK_C0                               0x771C
#define P77_1D_REG_MHL3_CP_VS_MASK_C1                               0x771D
#define P77_1E_REG_MHL3_WATER_REC                                   0x771E
#define P77_20_MHL_MEASURE_0                                        0x7720
#define P77_21_MHL_MEASURE_1                                        0x7721
#define P77_22_MHL_MEASURE_2                                        0x7722
#define P77_23_MHL_MEASURE_3                                        0x7723
#define P77_24_MHL_MEASURE_4                                        0x7724
#define P77_25_MHL_MEASURE_5                                        0x7725
#define P77_26_MHL_MEASURE_6                                        0x7726
#define P77_27_MHL_MEASURE_7                                        0x7727
#define P77_28_MHL_MEASURE_8                                        0x7728
#define P77_29_MHL_MEASURE_9                                        0x7729
#define P77_2A_MHL_MEASURE_10                                       0x772A
#define P77_2B_MHL_MEASURE_11                                       0x772B
#define P77_2C_MHL_MEASURE_12                                       0x772C
#define P77_2D_MHL_MEASURE_13                                       0x772D
#define P77_2E_MHL_MEASURE_14                                       0x772E
#define P77_2F_MHL_MEASURE_15                                       0x772F
#define P77_30_MHL_MEASURE_16                                       0x7730
#define P77_31_MHL_MEASURE_17                                       0x7731
#define P77_32_MHL_MEASURE_18                                       0x7732
#define P77_33_MHL_MEASURE_19                                       0x7733
#define P77_34_MHL_MEASURE_20                                       0x7734
#define P77_35_MHL_MEASURE_21                                       0x7735
#define P77_36_MHL_MEASURE_22                                       0x7736
#define P77_37_MHL_MEASURE_23                                       0x7737
#define P77_38_MHL_MEASURE_24                                       0x7738
#define P77_39_MHL_MEASURE_27                                       0x7739
#define P77_3A_MHL_MEASURE_28                                       0x773A
#define P77_3B_MHL_MEASURE_29                                       0x773B
#define P77_3C_MHL_MEASURE_30                                       0x773C
#define P77_3D_MHL_MEASURE_31                                       0x773D
#define P77_3E_MHL_MEASURE_32                                       0x773E
#define P77_3F_MHL_MEASURE_33                                       0x773F
#define P77_40_MHL_MEASURE_34                                       0x7740
#define P77_41_DPF_CTRL_0                                           0x7741
#define P77_42_DP_OUTPUT_CTRL                                       0x7742
#define P77_43_EVBLK2VS_H                                           0x7743
#define P77_44_EVBLK2VS_M                                           0x7744
#define P77_45_EVBLK2VS_L                                           0x7745
#define P77_46_OVBLK2VS_H                                           0x7746
#define P77_47_OVBLK2VS_M                                           0x7747
#define P77_48_OVBLK2VS_L                                           0x7748
#define P77_49_BS2HS_0                                              0x7749
#define P77_4A_BS2HS_1                                              0x774A
#define P77_4B_VS_FRONT_PORCH                                       0x774B
#define P77_4C_MN_DPF_HTT_M                                         0x774C
#define P77_4D_MN_DPF_HTT_L                                         0x774D
#define P77_4E_MN_DPF_HST_M                                         0x774E
#define P77_4F_MN_DPF_HST_L                                         0x774F
#define P77_50_MN_DPF_HWD_M                                         0x7750
#define P77_51_MN_DPF_HWD_L                                         0x7751
#define P77_52_MN_DPF_HSW_M                                         0x7752
#define P77_53_MN_DPF_HSW_L                                         0x7753
#define P77_54_MN_DPF_VTT_M                                         0x7754
#define P77_55_MN_DPF_VTT_L                                         0x7755
#define P77_56_MN_DPF_VST_M                                         0x7756
#define P77_57_MN_DPF_VST_L                                         0x7757
#define P77_58_MN_DPF_VHT_M                                         0x7758
#define P77_59_MN_DPF_VHT_L                                         0x7759
#define P77_5A_MN_DPF_VSW_M                                         0x775A
#define P77_5B_MN_DPF_VSW_L                                         0x775B
#define P77_5C_INTERLACE_MODE_CONFIG                                0x775C
#define P77_5D_TEST0                                                0x775D
#define P77_5E_MHL_TEST_OUT_SEL                                     0x775E
#define P77_80_REG_MHL3_CP0                                         0x7780
#define P77_81_REG_MHL3_CP1                                         0x7781
#define P77_82_REG_MHL3_CP2                                         0x7782
#define P77_83_REG_MHL3_CP3                                         0x7783
#define P77_84_REG_MHL3_CP4                                         0x7784
#define P77_85_REG_MHL3_CP5                                         0x7785
#define P77_86_REG_MHL3_CP6                                         0x7786
#define P77_87_REG_MHL3_CP7                                         0x7787
#define P77_88_REG_MHL3_CP8                                         0x7788
#define P77_89_REG_MHL3_CP9                                         0x7789
#define P77_8A_REG_MHL3_CP10                                        0x778A
#define P77_8B_REG_MHL3_CP11                                        0x778B
#define P77_8C_REG_MHL3_CP12                                        0x778C
#define P77_8D_REG_MHL3_CP13                                        0x778D
#define P77_8E_REG_MHL3_CP14                                        0x778E
#define P77_8F_REG_MHL3_CP15                                        0x778F
#define P77_90_REG_MHL3_CP16                                        0x7790
#define P77_91_REG_MHL3_CP17                                        0x7791
#define P77_92_REG_MHL3_CP18                                        0x7792
#define P77_93_REG_MHL3_CP19                                        0x7793
#define P77_94_MHL3_SRAM_BIST_0                                     0x7794
#define P77_95_MHL3_SRAM_BIST_1                                     0x7795


//--------------------------------------------------
// D3 MHL2.0 MAC (Page 77)
//--------------------------------------------------
#define P77_A0_MHL_CTRL_00                                          0x77A0
#define P77_A1_MHL_CTRL_01                                          0x77A1
#define P77_A2_MHL_CTRL_02                                          0x77A2
#define P77_A3_MHL_CTRL_03                                          0x77A3
#define P77_A4_MHL_CTRL_04                                          0x77A4
#define P77_A5_MHL_CTRL_05                                          0x77A5
#define P77_A6_MHL_CTRL_06                                          0x77A6
#define P77_A7_MHL_CTRL_07                                          0x77A7
#define P77_A8_MHL_CTRL_08                                          0x77A8
#define P77_A9_MHL_CTRL_09                                          0x77A9
#define P77_AA_MHL_CTRL_0A                                          0x77AA
#define P77_AB_MHL_CTRL_0B                                          0x77AB
#define P77_AC_MHL_CTRL_0C                                          0x77AC
#define P77_AD_MHL_CTRL_0D                                          0x77AD
#define P77_AE_MHL_CTRL_0E                                          0x77AE
#define P77_AF_MHL_CTRL_0F                                          0x77AF
#define P77_B0_MHL_CTRL_10                                          0x77B0
#define P77_B1_MHL_CTRL_11                                          0x77B1
#define P77_B2_MHL_CTRL_12                                          0x77B2
#define P77_B3_MHL_CTRL_13                                          0x77B3
#define P77_B4_MHL_CTRL_14                                          0x77B4
#define P77_B5_MHL_CTRL_15                                          0x77B5
#define P77_B6_MHL_CTRL_16                                          0x77B6


//--------------------------------------------------
// D1 GDI PHY Power On Region (Page 7A)
//--------------------------------------------------
#define P7A_0A_DPHY_DEBUG                                           0x7A0A
#define P7A_0B_SDM_00                                               0x7A0B
#define P7A_0C_SDM_01                                               0x7A0C
#define P7A_0D_SDM_02                                               0x7A0D
#define P7A_0E_SDM_03                                               0x7A0E
#define P7A_0F_WD                                                   0x7A0F
#define P7A_10_EQEN_TIMER                                           0x7A10
#define P7A_11_DATA_TIMER                                           0x7A11
#define P7A_12_ANA_CDR                                              0x7A12
#define P7A_13_PHY_RESERVED                                         0x7A13
#define P7A_17_BANDGAP_03                                           0x7A17
#define P7A_18_IMPEDANCE_00                                         0x7A18
#define P7A_19_IMPEDANCE_01                                         0x7A19
#define P7A_1A_CMU_00                                               0x7A1A
#define P7A_1B_CMU_01                                               0x7A1B
#define P7A_1C_CMU_02                                               0x7A1C
#define P7A_1D_CMU_03                                               0x7A1D
#define P7A_1E_CMU_04                                               0x7A1E
#define P7A_1F_CMU_05                                               0x7A1F
#define P7A_20_CMU_06                                               0x7A20
#define P7A_21_CMU_07                                               0x7A21
#define P7A_22_CMU_08                                               0x7A22
#define P7A_23_CMU_09                                               0x7A23
#define P7A_24_KOFFSET_00                                           0x7A24
#define P7A_25_KOFFSET_01                                           0x7A25
#define P7A_26_KOFFSET_02                                           0x7A26
#define P7A_27_KOFFSET_03                                           0x7A27
#define P7A_28_KOFFSET_04                                           0x7A28
#define P7A_29_KOFFSET_05                                           0x7A29
#define P7A_2A_KOFFSET_06                                           0x7A2A
#define P7A_2B_KOFFSET_07                                           0x7A2B
#define P7A_2C_ANA_CDR_01                                           0x7A2C
#define P7A_2D_ANA_CDR_02                                           0x7A2D
#define P7A_2E_ANA_CDR_03                                           0x7A2E
#define P7A_2F_ANA_CDR_04                                           0x7A2F
#define P7A_30_ANA_CDR_05                                           0x7A30
#define P7A_31_ANA_CDR_06                                           0x7A31
#define P7A_32_ANA_CDR_07                                           0x7A32
#define P7A_33_ANA_CDR_08                                           0x7A33
#define P7A_34_ANA_CDR_09                                           0x7A34
#define P7A_35_ANA_CDR_10                                           0x7A35
#define P7A_36_ANA_CDR_11                                           0x7A36
#define P7A_37_ANA_CDR_12                                           0x7A37
#define P7A_38_ANA_CDR_13                                           0x7A38
#define P7A_39_ANA_CDR_14                                           0x7A39
#define P7A_3A_TMDS_RESET                                           0x7A3A
#define P7A_3B_TMDS_CONT_00                                         0x7A3B
#define P7A_3C_TMDS_CONT_01                                         0x7A3C
#define P7A_3D_TMDS_CONT_02                                         0x7A3D
#define P7A_3E_TMDS_CONT_03                                         0x7A3E
#define P7A_3F_TMDS_CONT_04                                         0x7A3F
#define P7A_40_EN_01                                                0x7A40
#define P7A_41_EN_02                                                0x7A41
#define P7A_42_EN_03                                                0x7A42
#define P7A_43_EN_04                                                0x7A43
#define P7A_44_ST_01                                                0x7A44
#define P7A_45_ST_02                                                0x7A45
#define P7A_46_ST_03                                                0x7A46
#define P7A_47_ST_04                                                0x7A47
#define P7A_48_ST_05                                                0x7A48
#define P7A_49_ST_06                                                0x7A49
#define P7A_4A_ST_07                                                0x7A4A
#define P7A_4B_ST_08                                                0x7A4B
#define P7A_4C_ST_09                                                0x7A4C
#define P7A_4D_ST_10                                                0x7A4D
#define P7A_4E_ST_11                                                0x7A4E
#define P7A_4F_PI_MANUAL                                            0x7A4F
#define P7A_50_CDR_00                                               0x7A50
#define P7A_51_CDR_01                                               0x7A51
#define P7A_52_CDR_02                                               0x7A52
#define P7A_53_CDR_03                                               0x7A53
#define P7A_54_ACC_00                                               0x7A54
#define P7A_55_ACC_01                                               0x7A55
#define P7A_56_KI_L0                                                0x7A56
#define P7A_57_KI_L1                                                0x7A57
#define P7A_58_KI_L2                                                0x7A58
#define P7A_59_KI_L3                                                0x7A59
#define P7A_5A_KP_L0                                                0x7A5A
#define P7A_5B_KP_L1                                                0x7A5B
#define P7A_5C_KP_L2                                                0x7A5C
#define P7A_5D_KP_L3                                                0x7A5D


//--------------------------------------------------
// D1 GDI DFE (Page 7A)
//--------------------------------------------------
#define P7A_A0_L0_DFE_EN_1                                          0x7AA0
#define P7A_A1_L0_DFE_EN_2                                          0x7AA1
#define P7A_A2_L0_LIMIT_INIT                                        0x7AA2
#define P7A_A3_L0_INIT_1                                            0x7AA3
#define P7A_A4_L0_INIT_2                                            0x7AA4
#define P7A_A5_L0_INIT_3                                            0x7AA5
#define P7A_A6_L0_INIT_4                                            0x7AA6
#define P7A_A7_L0_INIT_5                                            0x7AA7
#define P7A_A8_L0_INIT_6                                            0x7AA8
#define P7A_A9_L0_INIT_7                                            0x7AA9
#define P7A_AA_L0_INIT_8                                            0x7AAA
#define P7A_AB_L0_STABLE_FLAG                                       0x7AAB
#define P7A_AF_L0_GDI_DE                                            0x7AAF
#define P7A_B0_L1_DFE_EN_1                                          0x7AB0
#define P7A_B1_L1_DFE_EN_2                                          0x7AB1
#define P7A_B2_L1_LIMIT_INIT                                        0x7AB2
#define P7A_B3_L1_INIT_1                                            0x7AB3
#define P7A_B4_L1_INIT_2                                            0x7AB4
#define P7A_B5_L1_INIT_3                                            0x7AB5
#define P7A_B6_L1_INIT_4                                            0x7AB6
#define P7A_B7_L1_INIT_5                                            0x7AB7
#define P7A_B8_L1_INIT_6                                            0x7AB8
#define P7A_B9_L1_INIT_7                                            0x7AB9
#define P7A_BA_L1_INIT_8                                            0x7ABA
#define P7A_BB_L1_STABLE_FLAG                                       0x7ABB
#define P7A_BF_L1_GDI_DE                                            0x7ABF
#define P7A_C0_L2_DFE_EN_1                                          0x7AC0
#define P7A_C1_L2_DFE_EN_2                                          0x7AC1
#define P7A_C2_L2_LIMIT_INIT                                        0x7AC2
#define P7A_C3_L2_INIT_1                                            0x7AC3
#define P7A_C4_L2_INIT_2                                            0x7AC4
#define P7A_C5_L2_INIT_3                                            0x7AC5
#define P7A_C6_L2_INIT_4                                            0x7AC6
#define P7A_C7_L2_INIT_5                                            0x7AC7
#define P7A_C8_L2_INIT_6                                            0x7AC8
#define P7A_C9_L2_INIT_7                                            0x7AC9
#define P7A_CA_L2_INIT_8                                            0x7ACA
#define P7A_CB_L2_STABLE_FLAG                                       0x7ACB
#define P7A_CF_L2_GDI_DE                                            0x7ACF
#define P7A_D0_L3_DFE_EN_1                                          0x7AD0
#define P7A_D1_L3_DFE_EN_2                                          0x7AD1
#define P7A_D2_L3_LIMIT_INIT                                        0x7AD2
#define P7A_D3_L3_INIT_1                                            0x7AD3
#define P7A_D4_L3_INIT_2                                            0x7AD4
#define P7A_D5_L3_INIT_3                                            0x7AD5
#define P7A_D6_L3_INIT_4                                            0x7AD6
#define P7A_D7_L3_INIT_5                                            0x7AD7
#define P7A_D8_L3_INIT_6                                            0x7AD8
#define P7A_D9_L3_INIT_7                                            0x7AD9
#define P7A_DA_L3_INIT_8                                            0x7ADA
#define P7A_DB_L3_STABLE_FLAG                                       0x7ADB
#define P7A_DF_L3_GDI_DE                                            0x7ADF
#define P7A_E0_MODE_TIMER                                           0x7AE0
#define P7A_E1_TIMER                                                0x7AE1
#define P7A_E2_GAIN_1                                               0x7AE2
#define P7A_E3_GAIN_2                                               0x7AE3
#define P7A_E4_GAIN_3                                               0x7AE4
#define P7A_E5_GAIN_4                                               0x7AE5
#define P7A_E6_LIMIT_1                                              0x7AE6
#define P7A_E7_LIMIT_2                                              0x7AE7
#define P7A_E8_LIMIT_3                                              0x7AE8
#define P7A_E9_LIMIT_4                                              0x7AE9
#define P7A_EA_LIMIT_5                                              0x7AEA
#define P7A_EB_LIMIT_6                                              0x7AEB
#define P7A_EC_LOOP_DIV_1                                           0x7AEC
#define P7A_ED_LOOP_DIV_2                                           0x7AED
#define P7A_EE_GRAY_DEC_1                                           0x7AEE
#define P7A_EF_RESET_1                                              0x7AEF
#define P7A_F0_COEF_1                                               0x7AF0
#define P7A_F1_COEF_2                                               0x7AF1
#define P7A_F2_COEF_3                                               0x7AF2
#define P7A_F3_COEF_4                                               0x7AF3
#define P7A_F8_GRAY_DEC_2                                           0x7AF8
#define P7A_F9_LIMIT_10                                             0x7AF9
#define P7A_FA_GAIN_PREC                                            0x7AFA
#define P7A_FB_DEBUG                                                0x7AFB


//--------------------------------------------------
// D2 GDI PHY Power On Region (Page 7B)
//--------------------------------------------------
#define P7B_00_DIG_00                                               0x7B00
#define P7B_01_DIG_01                                               0x7B01
#define P7B_02_DIG_02                                               0x7B02
#define P7B_03_DIG_03                                               0x7B03
#define P7B_04_DIG_04                                               0x7B04
#define P7B_05_DIG_05                                               0x7B05
#define P7B_06_DIG_06                                               0x7B06
#define P7B_07_DIG_07                                               0x7B07
#define P7B_08_DIG_08                                               0x7B08
#define P7B_09_DIG_09                                               0x7B09
#define P7B_0A_DIG_10                                               0x7B0A
#define P7B_0B_SDM_00                                               0x7B0B
#define P7B_0C_SDM_01                                               0x7B0C
#define P7B_0D_SDM_02                                               0x7B0D
#define P7B_0E_SDM_03                                               0x7B0E
#define P7B_0F_WD                                                   0x7B0F
#define P7B_10_EQEN_TIMER                                           0x7B10
#define P7B_11_DATA_TIMER                                           0x7B11
#define P7B_12_ANA_CDR                                              0x7B12
#define P7B_13_PHY_RESERVED                                         0x7B13
#define P7B_17_BANDGAP_03                                           0x7B17
#define P7B_18_IMPEDANCE_00                                         0x7B18
#define P7B_19_IMPEDANCE_01                                         0x7B19
#define P7B_1A_CMU_00                                               0x7B1A
#define P7B_1B_CMU_01                                               0x7B1B
#define P7B_1C_CMU_02                                               0x7B1C
#define P7B_1D_CMU_03                                               0x7B1D
#define P7B_1E_CMU_04                                               0x7B1E
#define P7B_1F_CMU_05                                               0x7B1F
#define P7B_20_CMU_06                                               0x7B20
#define P7B_21_CMU_07                                               0x7B21
#define P7B_22_CMU_08                                               0x7B22
#define P7B_23_CMU_09                                               0x7B23
#define P7B_24_KOFFSET_00                                           0x7B24
#define P7B_25_KOFFSET_01                                           0x7B25
#define P7B_26_KOFFSET_02                                           0x7B26
#define P7B_27_KOFFSET_03                                           0x7B27
#define P7B_28_KOFFSET_04                                           0x7B28
#define P7B_29_KOFFSET_05                                           0x7B29
#define P7B_2A_ANA_CDR_00                                           0x7B2A
#define P7B_2B_ANA_CDR_01                                           0x7B2B
#define P7B_2C_ANA_CDR_02                                           0x7B2C
#define P7B_2D_ANA_CDR_03                                           0x7B2D
#define P7B_2E_ANA_CDR_04                                           0x7B2E
#define P7B_2F_ANA_CDR_05                                           0x7B2F
#define P7B_30_ANA_CDR_06                                           0x7B30
#define P7B_31_ANA_CDR_07                                           0x7B31
#define P7B_32_ANA_CDR_08                                           0x7B32
#define P7B_33_ANA_CDR_09                                           0x7B33
#define P7B_34_ANA_CDR_10                                           0x7B34
#define P7B_35_ANA_CDR_11                                           0x7B35
#define P7B_36_ANA_CDR_12                                           0x7B36
#define P7B_37_ANA_CDR_13                                           0x7B37
#define P7B_38_TMDS_RESET                                           0x7B38
#define P7B_39_TMDS_CONT_00                                         0x7B39
#define P7B_3A_TMDS_CONT_01                                         0x7B3A
#define P7B_3B_TMDS_CONT_02                                         0x7B3B
#define P7B_3C_TMDS_CONT_03                                         0x7B3C
#define P7B_3D_TMDS_CONT_04                                         0x7B3D
#define P7B_3E_EN_01                                                0x7B3E
#define P7B_3F_EN_02                                                0x7B3F
#define P7B_40_EN_03                                                0x7B40
#define P7B_41_ST_01                                                0x7B41
#define P7B_42_ST_02                                                0x7B42
#define P7B_43_ST_03                                                0x7B43
#define P7B_44_ST_04                                                0x7B44
#define P7B_45_ST_05                                                0x7B45
#define P7B_46_ST_06                                                0x7B46
#define P7B_47_ST_07                                                0x7B47
#define P7B_48_ST_08                                                0x7B48
#define P7B_49_ST_09                                                0x7B49
#define P7B_4A_CDR_00                                               0x7B4A
#define P7B_4B_CDR_01                                               0x7B4B
#define P7B_4C_CDR_02                                               0x7B4C
#define P7B_4D_ACC_00                                               0x7B4D
#define P7B_4E_ACC_01                                               0x7B4E
#define P7B_4F_KD                                                   0x7B4F
#define P7B_50_KI_L0                                                0x7B50
#define P7B_51_KI_L1                                                0x7B51
#define P7B_52_KI_L2                                                0x7B52
#define P7B_53_KP_L0                                                0x7B53
#define P7B_54_KP_L1                                                0x7B54
#define P7B_55_KP_L2                                                0x7B55


//--------------------------------------------------
// D2 GDI DFE (Page 7B)
//--------------------------------------------------
#define P7B_A0_L0_DFE_EN_1                                          0x7BA0
#define P7B_A1_L0_DFE_EN_2                                          0x7BA1
#define P7B_A2_L0_LIMIT_INIT                                        0x7BA2
#define P7B_A3_L0_INIT_1                                            0x7BA3
#define P7B_A4_L0_INIT_2                                            0x7BA4
#define P7B_A5_L0_INIT_3                                            0x7BA5
#define P7B_A6_L0_INIT_4                                            0x7BA6
#define P7B_A7_L0_INIT_5                                            0x7BA7
#define P7B_A8_L0_INIT_6                                            0x7BA8
#define P7B_A9_L0_INIT_7                                            0x7BA9
#define P7B_AA_L0_INIT_8                                            0x7BAA
#define P7B_AB_L0_STABLE_FLAG                                       0x7BAB
#define P7B_AF_L0_GDI_DE                                            0x7BAF
#define P7B_B0_L1_DFE_EN_1                                          0x7BB0
#define P7B_B1_L1_DFE_EN_2                                          0x7BB1
#define P7B_B2_L1_LIMIT_INIT                                        0x7BB2
#define P7B_B3_L1_INIT_1                                            0x7BB3
#define P7B_B4_L1_INIT_2                                            0x7BB4
#define P7B_B5_L1_INIT_3                                            0x7BB5
#define P7B_B6_L1_INIT_4                                            0x7BB6
#define P7B_B7_L1_INIT_5                                            0x7BB7
#define P7B_B8_L1_INIT_6                                            0x7BB8
#define P7B_B9_L1_INIT_7                                            0x7BB9
#define P7B_BA_L1_INIT_8                                            0x7BBA
#define P7B_BB_L1_STABLE_FLAG                                       0x7BBB
#define P7B_BF_L1_GDI_DE                                            0x7BBF
#define P7B_C0_L2_DFE_EN_1                                          0x7BC0
#define P7B_C1_L2_DFE_EN_2                                          0x7BC1
#define P7B_C2_L2_LIMIT_INIT                                        0x7BC2
#define P7B_C3_L2_INIT_1                                            0x7BC3
#define P7B_C4_L2_INIT_2                                            0x7BC4
#define P7B_C5_L2_INIT_3                                            0x7BC5
#define P7B_C6_L2_INIT_4                                            0x7BC6
#define P7B_C7_L2_INIT_5                                            0x7BC7
#define P7B_C8_L2_INIT_6                                            0x7BC8
#define P7B_C9_L2_INIT_7                                            0x7BC9
#define P7B_CA_L2_INIT_8                                            0x7BCA
#define P7B_CB_L2_STABLE_FLAG                                       0x7BCB
#define P7B_CF_L2_GDI_DE                                            0x7BCF
#define P7B_E0_MODE_TIMER                                           0x7BE0
#define P7B_E1_TIMER                                                0x7BE1
#define P7B_E2_GAIN_1                                               0x7BE2
#define P7B_E3_GAIN_2                                               0x7BE3
#define P7B_E4_GAIN_3                                               0x7BE4
#define P7B_E5_GAIN_4                                               0x7BE5
#define P7B_E6_LIMIT_1                                              0x7BE6
#define P7B_E7_LIMIT_2                                              0x7BE7
#define P7B_E8_LIMIT_3                                              0x7BE8
#define P7B_E9_LIMIT_4                                              0x7BE9
#define P7B_EA_LIMIT_5                                              0x7BEA
#define P7B_EB_LIMIT_6                                              0x7BEB
#define P7B_EC_LOOP_DIV_1                                           0x7BEC
#define P7B_ED_LOOP_DIV_2                                           0x7BED
#define P7B_EE_GRAY_DEC_1                                           0x7BEE
#define P7B_EF_RESET_1                                              0x7BEF
#define P7B_F0_COEF_1                                               0x7BF0
#define P7B_F1_COEF_2                                               0x7BF1
#define P7B_F2_COEF_3                                               0x7BF2
#define P7B_F3_COEF_4                                               0x7BF3
#define P7B_F8_GRAY_DEC_2                                           0x7BF8
#define P7B_F9_LIMIT_10                                             0x7BF9
#define P7B_FA_GAIN_PREC                                            0x7BFA
#define P7B_FB_DEBUG                                                0x7BFB


//--------------------------------------------------
// D3 GDI PHY Power On Region (Page 7C)
//--------------------------------------------------
#define P7C_00_DIG_00                                               0x7C00
#define P7C_01_DIG_01                                               0x7C01
#define P7C_02_DIG_02                                               0x7C02
#define P7C_03_DIG_03                                               0x7C03
#define P7C_04_DIG_04                                               0x7C04
#define P7C_05_DIG_05                                               0x7C05
#define P7C_06_DIG_06                                               0x7C06
#define P7C_07_DIG_07                                               0x7C07
#define P7C_08_DIG_08                                               0x7C08
#define P7C_09_DIG_09                                               0x7C09
#define P7C_0A_DIG_10                                               0x7C0A
#define P7C_0B_SDM_00                                               0x7C0B
#define P7C_0C_SDM_01                                               0x7C0C
#define P7C_0D_SDM_02                                               0x7C0D
#define P7C_0E_SDM_03                                               0x7C0E
#define P7C_0F_WD                                                   0x7C0F
#define P7C_10_EQEN_TIMER                                           0x7C10
#define P7C_11_DATA_TIMER                                           0x7C11
#define P7C_12_ANA_CDR                                              0x7C12
#define P7C_13_PHY_RESERVED                                         0x7C13
#define P7C_17_BANDGAP_03                                           0x7C17
#define P7C_18_IMPEDANCE_00                                         0x7C18
#define P7C_19_IMPEDANCE_01                                         0x7C19
#define P7C_1A_CMU_00                                               0x7C1A
#define P7C_1B_CMU_01                                               0x7C1B
#define P7C_1C_CMU_02                                               0x7C1C
#define P7C_1D_CMU_03                                               0x7C1D
#define P7C_1E_CMU_04                                               0x7C1E
#define P7C_1F_CMU_05                                               0x7C1F
#define P7C_20_CMU_06                                               0x7C20
#define P7C_21_CMU_07                                               0x7C21
#define P7C_22_CMU_08                                               0x7C22
#define P7C_23_CMU_09                                               0x7C23
#define P7C_24_KOFFSET_00                                           0x7C24
#define P7C_25_KOFFSET_01                                           0x7C25
#define P7C_26_KOFFSET_02                                           0x7C26
#define P7C_27_KOFFSET_03                                           0x7C27
#define P7C_28_KOFFSET_04                                           0x7C28
#define P7C_29_KOFFSET_05                                           0x7C29
#define P7C_2A_ANA_CDR_00                                           0x7C2A
#define P7C_2B_ANA_CDR_01                                           0x7C2B
#define P7C_2C_ANA_CDR_02                                           0x7C2C
#define P7C_2D_ANA_CDR_03                                           0x7C2D
#define P7C_2E_ANA_CDR_04                                           0x7C2E
#define P7C_2F_ANA_CDR_05                                           0x7C2F
#define P7C_30_ANA_CDR_06                                           0x7C30
#define P7C_31_ANA_CDR_07                                           0x7C31
#define P7C_32_ANA_CDR_08                                           0x7C32
#define P7C_33_ANA_CDR_09                                           0x7C33
#define P7C_34_ANA_CDR_10                                           0x7C34
#define P7C_35_ANA_CDR_11                                           0x7C35
#define P7C_36_ANA_CDR_12                                           0x7C36
#define P7C_37_ANA_CDR_13                                           0x7C37
#define P7C_38_TMDS_RESET                                           0x7C38
#define P7C_39_TMDS_CONT_00                                         0x7C39
#define P7C_3A_TMDS_CONT_01                                         0x7C3A
#define P7C_3B_TMDS_CONT_02                                         0x7C3B
#define P7C_3C_TMDS_CONT_03                                         0x7C3C
#define P7C_3D_TMDS_CONT_04                                         0x7C3D
#define P7C_3E_EN_01                                                0x7C3E
#define P7C_3F_EN_02                                                0x7C3F
#define P7C_40_EN_03                                                0x7C40
#define P7C_41_ST_01                                                0x7C41
#define P7C_42_ST_02                                                0x7C42
#define P7C_43_ST_03                                                0x7C43
#define P7C_44_ST_04                                                0x7C44
#define P7C_45_ST_05                                                0x7C45
#define P7C_46_ST_06                                                0x7C46
#define P7C_47_ST_07                                                0x7C47
#define P7C_48_ST_08                                                0x7C48
#define P7C_49_ST_09                                                0x7C49
#define P7C_4A_CDR_00                                               0x7C4A
#define P7C_4B_CDR_01                                               0x7C4B
#define P7C_4C_CDR_02                                               0x7C4C
#define P7C_4D_ACC_00                                               0x7C4D
#define P7C_4E_ACC_01                                               0x7C4E
#define P7C_4F_KD                                                   0x7C4F
#define P7C_50_KI_L0                                                0x7C50
#define P7C_51_KI_L1                                                0x7C51
#define P7C_52_KI_L2                                                0x7C52
#define P7C_53_KP_L0                                                0x7C53
#define P7C_54_KP_L1                                                0x7C54
#define P7C_55_KP_L2                                                0x7C55


//--------------------------------------------------
// D3 GDI DFE (Page 7C)
//--------------------------------------------------
#define P7C_A0_L0_DFE_EN_1                                          0x7CA0
#define P7C_A1_L0_DFE_EN_2                                          0x7CA1
#define P7C_A2_L0_LIMIT_INIT                                        0x7CA2
#define P7C_A3_L0_INIT_1                                            0x7CA3
#define P7C_A4_L0_INIT_2                                            0x7CA4
#define P7C_A5_L0_INIT_3                                            0x7CA5
#define P7C_A6_L0_INIT_4                                            0x7CA6
#define P7C_A7_L0_INIT_5                                            0x7CA7
#define P7C_A8_L0_INIT_6                                            0x7CA8
#define P7C_A9_L0_INIT_7                                            0x7CA9
#define P7C_AA_L0_INIT_8                                            0x7CAA
#define P7C_AB_L0_STABLE_FLAG                                       0x7CAB
#define P7C_AF_L0_GDI_DE                                            0x7CAF
#define P7C_B0_L1_DFE_EN_1                                          0x7CB0
#define P7C_B1_L1_DFE_EN_2                                          0x7CB1
#define P7C_B2_L1_LIMIT_INIT                                        0x7CB2
#define P7C_B3_L1_INIT_1                                            0x7CB3
#define P7C_B4_L1_INIT_2                                            0x7CB4
#define P7C_B5_L1_INIT_3                                            0x7CB5
#define P7C_B6_L1_INIT_4                                            0x7CB6
#define P7C_B7_L1_INIT_5                                            0x7CB7
#define P7C_B8_L1_INIT_6                                            0x7CB8
#define P7C_B9_L1_INIT_7                                            0x7CB9
#define P7C_BA_L1_INIT_8                                            0x7CBA
#define P7C_BB_L1_STABLE_FLAG                                       0x7CBB
#define P7C_BF_L1_GDI_DE                                            0x7CBF
#define P7C_C0_L2_DFE_EN_1                                          0x7CC0
#define P7C_C1_L2_DFE_EN_2                                          0x7CC1
#define P7C_C2_L2_LIMIT_INIT                                        0x7CC2
#define P7C_C3_L2_INIT_1                                            0x7CC3
#define P7C_C4_L2_INIT_2                                            0x7CC4
#define P7C_C5_L2_INIT_3                                            0x7CC5
#define P7C_C6_L2_INIT_4                                            0x7CC6
#define P7C_C7_L2_INIT_5                                            0x7CC7
#define P7C_C8_L2_INIT_6                                            0x7CC8
#define P7C_C9_L2_INIT_7                                            0x7CC9
#define P7C_CA_L2_INIT_8                                            0x7CCA
#define P7C_CB_L2_STABLE_FLAG                                       0x7CCB
#define P7C_CF_L2_GDI_DE                                            0x7CCF
#define P7C_E0_MODE_TIMER                                           0x7CE0
#define P7C_E1_TIMER                                                0x7CE1
#define P7C_E2_GAIN_1                                               0x7CE2
#define P7C_E3_GAIN_2                                               0x7CE3
#define P7C_E4_GAIN_3                                               0x7CE4
#define P7C_E5_GAIN_4                                               0x7CE5
#define P7C_E6_LIMIT_1                                              0x7CE6
#define P7C_E7_LIMIT_2                                              0x7CE7
#define P7C_E8_LIMIT_3                                              0x7CE8
#define P7C_E9_LIMIT_4                                              0x7CE9
#define P7C_EA_LIMIT_5                                              0x7CEA
#define P7C_EB_LIMIT_6                                              0x7CEB
#define P7C_EC_LOOP_DIV_1                                           0x7CEC
#define P7C_ED_LOOP_DIV_2                                           0x7CED
#define P7C_EE_GRAY_DEC_1                                           0x7CEE
#define P7C_EF_RESET_1                                              0x7CEF
#define P7C_F0_COEF_1                                               0x7CF0
#define P7C_F1_COEF_2                                               0x7CF1
#define P7C_F2_COEF_3                                               0x7CF2
#define P7C_F3_COEF_4                                               0x7CF3
#define P7C_F8_GRAY_DEC_2                                           0x7CF8
#define P7C_F9_LIMIT_10                                             0x7CF9
#define P7C_FA_GAIN_PREC                                            0x7CFA
#define P7C_FB_DEBUG                                                0x7CFB


//--------------------------------------------------
// GDI Clock Divider (Page 80)
//--------------------------------------------------
#define P80_06_GDI_CLK_DIVIDER                                      0x8006


//--------------------------------------------------
// GroupE Power Control (Page 80)
//--------------------------------------------------
#define P80_0A_GE_POWER_CTRL                                        0x800A
#define P80_0B_TOP_DUMMY6                                           0x800B
#define P80_0D_TOP_DUMMY7                                           0x800D


//--------------------------------------------------
// XTAL (Page 80)
//--------------------------------------------------
#define P80_0E_XTAL_CTRL0                                           0x800E
#define P80_0F_XTAL_CTRL1                                           0x800F


//--------------------------------------------------
// DisplayPort 1.1 Tx1 Digital PHY CTRL (Page 9C)
//--------------------------------------------------
#define P9C_00_DP_PHY_CTRL                                          0x9C00
#define P9C_01_DPTX_ML_PAT_SEL                                      0x9C01
#define P9C_0D_DPTX_PHY_CTRL                                        0x9C0D


//--------------------------------------------------
// DisplayPort 1.1 Tx1 Analog PHY CTRL (Page 9C)
//--------------------------------------------------
#define P9C_10_DPTX_SFIFO_CTRL0                                     0x9C10
#define P9C_11_DPTX_SFIFO_CTRL1                                     0x9C11
#define P9C_12_DPTX_SFIFO_LANE_SWAP0                                0x9C12
#define P9C_13_DPTX_SFIFO_LANE_SWAP1                                0x9C13
#define P9C_14_DPTX_SFIFO_INT_EN                                    0x9C14


//--------------------------------------------------
// DisplayPort 1.1 Tx1 HPD Detection (Page 9C)
//--------------------------------------------------
#define P9C_70_HPD_CTRL                                             0x9C70
#define P9C_71_HPD_IRQ                                              0x9C71
#define P9C_72_HPD_IRQ_EN                                           0x9C72
#define P9C_73_HPD_TIMER1                                           0x9C73
#define P9C_74_HPD_TIMER2                                           0x9C74
#define P9C_75_HPD_TIMER3                                           0x9C75
#define P9C_76_HPD_TIMER4                                           0x9C76
#define P9C_77_HPD_TIMER5                                           0x9C77
#define P9C_78_HPD_TIMER6                                           0x9C78
#define P9C_79_HPD_TIMER7                                           0x9C79
#define P9C_7A_HPD_LONG0                                            0x9C7A
#define P9C_7B_HPD_LONG1                                            0x9C7B
#define P9C_7C_HPD_STATE                                            0x9C7C
#define P9C_7D_RESERVED_0                                           0x9C7D
#define P9C_7E_RESERVED_1                                           0x9C7E


//--------------------------------------------------
// DisplayPort 1.1 Tx1 MAC CTRL (Page 9C)
//--------------------------------------------------
#define P9C_A0_DP_MAC_CTRL                                          0x9CA0
#define P9C_A1_DP_RESET_CTRL                                        0x9CA1
#define P9C_A2_DP_DEBUG_CTRL                                        0x9CA2
#define P9C_A3_DPTX_IRQ_CTRL                                        0x9CA3
#define P9C_A4_PG_FIFO_CTRL                                         0x9CA4
#define P9C_A5_MAX_WL                                               0x9CA5
#define P9C_A6_LFIFO_WL                                             0x9CA6
#define P9C_A7_PG_INTERRUPT_CTRL                                    0x9CA7
#define P9C_A8_MN_VID_AUTO_EN_1                                     0x9CA8
#define P9C_A9_MN_M_VID_H                                           0x9CA9
#define P9C_AA_MN_M_VID_M                                           0x9CAA
#define P9C_AB_MN_M_VID_L                                           0x9CAB
#define P9C_AC_MN_N_VID_H                                           0x9CAC
#define P9C_AD_MN_N_VID_M                                           0x9CAD
#define P9C_AE_MN_N_VID_L                                           0x9CAE
#define P9C_AF_MVID_AUTO_H                                          0x9CAF
#define P9C_B0_MVID_AUTO_M                                          0x9CB0
#define P9C_B1_MVID_AUTO_L                                          0x9CB1
#define P9C_B2_NVID_ASYNC_M                                         0x9CB2
#define P9C_B3_NVID_ASYNC_L                                         0x9CB3
#define P9C_B4_MSA_CTRL                                             0x9CB4
#define P9C_B5_MSA_MISC0                                            0x9CB5
#define P9C_B6_MN_STRM_ATTR_MISC1                                   0x9CB6
#define P9C_B7_MN_STRM_ATTR_HTT_M                                   0x9CB7
#define P9C_B8_MN_STRM_ATTR_HTT_L                                   0x9CB8
#define P9C_B9_MN_STRM_ATTR_HST_M                                   0x9CB9
#define P9C_BA_MN_STRM_ATTR_HST_L                                   0x9CBA
#define P9C_BB_MN_STRM_ATTR_HWD_M                                   0x9CBB
#define P9C_BC_MN_STRM_ATTR_HWD_L                                   0x9CBC
#define P9C_BD_MN_STRM_ATTR_HSW_M                                   0x9CBD
#define P9C_BE_MN_STRM_ATTR_HSW_L                                   0x9CBE
#define P9C_BF_MN_STRM_ATTR_VTTE_M                                  0x9CBF
#define P9C_C0_MN_STRM_ATTR_VTTE_L                                  0x9CC0
#define P9C_C1_MN_STRM_ATTR_VST_M                                   0x9CC1
#define P9C_C2_MN_STRM_ATTR_VST_L                                   0x9CC2
#define P9C_C3_MN_STRM_ATTR_VHT_M                                   0x9CC3
#define P9C_C4_MN_STRM_ATTR_VHT_L                                   0x9CC4
#define P9C_C5_MN_STRM_ATTR_VSW_M                                   0x9CC5
#define P9C_C6_MN_STRM_ATTR_VSW_L                                   0x9CC6
#define P9C_C7_VBID                                                 0x9CC7
#define P9C_C8_VBID_FW_CTL                                          0x9CC8
#define P9C_C9_ARBITER_CTRL                                         0x9CC9
#define P9C_CA_V_DATA_PER_LINE0                                     0x9CCA
#define P9C_CB_V_DATA_PER_LINE1                                     0x9CCB
#define P9C_CC_TU_SIZE                                              0x9CCC
#define P9C_CD_TU_DATA_SIZE0                                        0x9CCD
#define P9C_CE_TU_DATA_SIZE1                                        0x9CCE
#define P9C_CF_HDEALY0                                              0x9CCF
#define P9C_D0_HDEALY1                                              0x9CD0
#define P9C_D1_AUTO_HDEALY0                                         0x9CD1
#define P9C_D2_AUTO_HDEALY1                                         0x9CD2
#define P9C_D3_LFIFO_WL_SET                                         0x9CD3
#define P9C_D4_ARBITER_SEC_END_CNT_HB                               0x9CD4
#define P9C_D5_ARBITER_SEC_END_CNT_LB                               0x9CD5
#define P9C_D6_ARBITER_DEBUG                                        0x9CD6
#define P9C_D7_DPTX_CTSFIFO_CTRL                                    0x9CD7
#define P9C_D8_DPTX_CTSFIFO_RSV1                                    0x9CD8
#define P9C_D9_DPTX_TOP_CTL                                         0x9CD9
#define P9C_DA_DPTX_TOP_RSV1                                        0x9CDA
#define P9C_DB_DPTX_TOP_RSV2                                        0x9CDB
#define P9C_DC_ARBITER_MIN_H_BLANK_WIDTH_HB                         0x9CDC
#define P9C_DD_ARBITER_MIN_H_BLANK_WIDTH_LB                         0x9CDD
#define P9C_DE_ARBITER_INTERRUPT_CTRL                               0x9CDE
#define P9C_DF_VESA_FMT_REGEN                                       0x9CDF
#define P9C_E0_DPTX_CLK_GEN                                         0x9CE0
#define P9C_E1_PG_MBIST_CTRL                                        0x9CE1
#define P9C_E2_PG_DRF_MBIST_CTRL                                    0x9CE2
#define P9C_F0_DPTX_TOP_RSV3                                        0x9CF0
#define P9C_F1_DPTX_TOP_RSV4                                        0x9CF1
#define P9C_F2_DPTX_TOP_RSV5                                        0x9CF2
#define P9C_F3_DPTX_TOP_RSV6                                        0x9CF3
#define P9C_F4_DPTX_TOP_RSV7                                        0x9CF4
#define P9C_F5_DPTX_TOP_RSV8                                        0x9CF5
#define P9C_F6_DPTX_TOP_RSV9                                        0x9CF6
#define P9C_F7_DPTX_TOP_RSV10                                       0x9CF7


//--------------------------------------------------
// DisplayPort 1.1 Tx1 AUX  (Page 9D)
//--------------------------------------------------
#define P9D_60_DIG_TX_04                                            0x9D60
#define P9D_61_AUX_1                                                0x9D61
#define P9D_62_AUX_2                                                0x9D62
#define P9D_63_AUX_3                                                0x9D63
#define P9D_64_AUX_4                                                0x9D64
#define P9D_65_AUX_5                                                0x9D65
#define P9D_66_AUX_6                                                0x9D66
#define P9D_67_DIG_TX_03                                            0x9D67


//--------------------------------------------------
// DisplayPort 1.1 Tx1 AUX MAC CTRL (Page 9D)
//--------------------------------------------------
#define P9D_A0_AUX_TX_CTRL                                          0x9DA0
#define P9D_A1_AUX_TIMEOUT                                          0x9DA1
#define P9D_A2_AUX_FSM_STATUS                                       0x9DA2
#define P9D_A3_AUXTX_TRAN_CTRL                                      0x9DA3
#define P9D_A4_AUXTX_REQ_CMD                                        0x9DA4
#define P9D_A5_AUXTX_REQ_ADDR_M                                     0x9DA5
#define P9D_A6_AUXTX_REQ_ADDR_L                                     0x9DA6
#define P9D_A7_AUXTX_REQ_LEN                                        0x9DA7
#define P9D_A8_AUXTX_REQ_DATA                                       0x9DA8
#define P9D_A9_AUX_REPLY_CMD                                        0x9DA9
#define P9D_AA_AUX_REPLY_DATA                                       0x9DAA
#define P9D_AB_AUX_FIFO_CTRL                                        0x9DAB
#define P9D_AC_AUX_TX_FIFO_STATUS                                   0x9DAC
#define P9D_AD_AUX_FIFO_RD_PTR                                      0x9DAD
#define P9D_AE_AUX_FIFO_WR_PTR                                      0x9DAE
#define P9D_AF_AUX_RETRY_1                                          0x9DAF
#define P9D_B0_AUX_RETRY_2                                          0x9DB0
#define P9D_B1_AUX_IRQ_EVENT                                        0x9DB1
#define P9D_B2_AUX_IRQ_EN                                           0x9DB2
#define P9D_F0_AUX_DIG_PHY2                                         0x9DF0
#define P9D_F1_AUX_DIG_PHY3                                         0x9DF1
#define P9D_F2_AUX_DIG_PHY4                                         0x9DF2
#define P9D_F3_AUX_DIG_PHY5                                         0x9DF3
#define P9D_F4_AUX_DIG_PHY6                                         0x9DF4
#define P9D_F5_AUX_DIG_PHY7                                         0x9DF5
#define P9D_F6_AUX_DIG_PHY8                                         0x9DF6
#define P9D_F7_AUX_DIG_PHY9                                         0x9DF7
#define P9D_F8_AUX_DEBUG                                            0x9DF8


//--------------------------------------------------
// D1 Port DisplayPort 1.2 Digital PHY(Page B0)
//--------------------------------------------------
#define PB0_00_HD_DP_SEL                                            0xB000
#define PB0_01_PHY_DIG_RESET_CTRL                                   0xB001
#define PB0_02_PHY_DIG_RESET2_CTRL                                  0xB002
#define PB0_03_LANE_MUX                                             0xB003
#define PB0_04_CHANNEL_FIFO_SYNC                                    0xB004
#define PB0_05_SAMPLE_EDGE                                          0xB005
#define PB0_06_DECODE_10B8B_ERROR                                   0xB006
#define PB0_07_SCRAMBLE_CTRL                                        0xB007
#define PB0_08_BIST_PATTERN_SEL                                     0xB008
#define PB0_09_BIST_PATTERN1                                        0xB009
#define PB0_0A_BIST_PATTERN2                                        0xB00A
#define PB0_0B_BIST_PATTERN3                                        0xB00B
#define PB0_0C_BIST_PATTERN4                                        0xB00C
#define PB0_0D_BIST_SEED_0                                          0xB00D
#define PB0_0E_DESKEW_PHY                                           0xB00E
#define PB0_0F_DESKEW_PHY2                                          0xB00F
#define PB0_10_PHY_CH_FIFO_SYNC0                                    0xB010
#define PB0_11_PHY_CH_FIFO_SYNC                                     0xB011
#define PB0_12_EQ_CRC_1                                             0xB012
#define PB0_13_EQ_CRC_2                                             0xB013
#define PB0_14_EQ_CRC_3                                             0xB014
#define PB0_15_EQ_CRC_4                                             0xB015
#define PB0_16_EQ_CRC_5                                             0xB016
#define PB0_17_DP_HDCP_CONTROL                                      0xB017
#define PB0_18_DP_HDCP_DOWNLOAD_PORT                                0xB018
#define PB0_19_DP_HDCP_KEY_OUTPUT                                   0xB019
#define PB0_1A_HDCP_IRQ                                             0xB01A
#define PB0_1B_HDCP_INTGT_VRF                                       0xB01B
#define PB0_1C_HDCP_INTGT_VRF_PAT_MSB                               0xB01C
#define PB0_1D_HDCP_INTGT_VRF_PAT_LSB                               0xB01D
#define PB0_1E_HDCP_INTGT_VRF_ANS_MSB                               0xB01E
#define PB0_1F_HDCP_INTGT_VRF_ANS_LSB                               0xB01F
#define PB0_20_HDCP_DEBUG                                           0xB020
#define PB0_21_KM_BYTE_6                                            0xB021
#define PB0_22_KM_BYTE_5                                            0xB022
#define PB0_23_KM_BYTE_4                                            0xB023
#define PB0_24_KM_BYTE_3                                            0xB024
#define PB0_25_KM_BYTE_2                                            0xB025
#define PB0_26_KM_BYTE_1                                            0xB026
#define PB0_27_KM_BYTE_0                                            0xB027
#define PB0_28_M0_BYTE_7                                            0xB028
#define PB0_29_M0_BYTE_6                                            0xB029
#define PB0_2A_M0_BYTE_5                                            0xB02A
#define PB0_2B_M0_BYTE_4                                            0xB02B
#define PB0_2C_M0_BYTE_3                                            0xB02C
#define PB0_2D_M0_BYTE_2                                            0xB02D
#define PB0_2E_M0_BYTE_1                                            0xB02E
#define PB0_2F_M0_BYTE_0                                            0xB02F
#define PB0_30_SHA_CONTRL                                           0xB030
#define PB0_31_SHA_DATA1                                            0xB031
#define PB0_32_SHA_DATA2                                            0xB032
#define PB0_33_SHA_DATA3                                            0xB033
#define PB0_34_SHA_DATA4                                            0xB034
#define PB0_36_SHA_0                                                0xB036
#define PB0_37_SHA_1                                                0xB037
#define PB0_38_SHA_2                                                0xB038
#define PB0_39_SHA_3                                                0xB039
#define PB0_3A_SHA_4                                                0xB03A
#define PB0_3B_SHA_5                                                0xB03B
#define PB0_3C_SHA_6                                                0xB03C
#define PB0_3D_SHA_7                                                0xB03D
#define PB0_3E_SHA_8                                                0xB03E
#define PB0_3F_SHA_9                                                0xB03F
#define PB0_40_SHA_10                                               0xB040
#define PB0_41_SHA_11                                               0xB041
#define PB0_42_SHA_12                                               0xB042
#define PB0_43_SHA_13                                               0xB043
#define PB0_44_SHA_14                                               0xB044
#define PB0_45_SHA_15                                               0xB045
#define PB0_46_SHA_16                                               0xB046
#define PB0_47_SHA_17                                               0xB047
#define PB0_48_SHA_18                                               0xB048
#define PB0_49_SHA_19                                               0xB049
#define PB0_50_DP_SIG_DET_0                                         0xB050
#define PB0_51_DP_SIG_DET_1                                         0xB051
#define PB0_52_DP_SIG_DET_2                                         0xB052
#define PB0_53_DP_SIG_DET_3                                         0xB053
#define PB0_54_DP_SIG_DET_4                                         0xB054


//--------------------------------------------------
// D1 HDCP 2.2 Module (Page B0)
//--------------------------------------------------
#define PB0_55_RIV0                                                 0xB055
#define PB0_56_RIV1                                                 0xB056
#define PB0_57_RIV2                                                 0xB057
#define PB0_58_RIV3                                                 0xB058
#define PB0_59_RIV4                                                 0xB059
#define PB0_5A_RIV5                                                 0xB05A
#define PB0_5B_RIV6                                                 0xB05B
#define PB0_5C_RIV7                                                 0xB05C
#define PB0_60_DEBUG0                                               0xB060
#define PB0_61_DEBUG1                                               0xB061
#define PB0_62_DEBUG2                                               0xB062
#define PB0_63_HDCP_OTHER                                           0xB063
#define PB0_64_HDCP_ENC_CTRL0                                       0xB064
#define PB0_65_HDCP_ENC_CTRL1                                       0xB065
#define PB0_66_HDCP_ENC_CTRL2                                       0xB066
#define PB0_67_HDCP_ENC_CTRL3                                       0xB067
#define PB0_68_HDCP_ENC_CTRL4                                       0xB068
#define PB0_69_HDCP_ENC_CTRL5                                       0xB069
#define PB0_6A_HDCP_ENC_CTRL6                                       0xB06A
#define PB0_6B_HDCP_ENC_CTRL7                                       0xB06B
#define PB0_81_HDCP_AES_CIPHER_KEY_15                               0xB081
#define PB0_82_HDCP_AES_CIPHER_KEY_14                               0xB082
#define PB0_83_HDCP_AES_CIPHER_KEY_13                               0xB083
#define PB0_84_HDCP_AES_CIPHER_KEY_12                               0xB084
#define PB0_85_HDCP_AES_CIPHER_KEY_11                               0xB085
#define PB0_86_HDCP_AES_CIPHER_KEY_10                               0xB086
#define PB0_87_HDCP_AES_CIPHER_KEY_9                                0xB087
#define PB0_88_HDCP_AES_CIPHER_KEY_8                                0xB088
#define PB0_89_HDCP_AES_CIPHER_KEY_7                                0xB089
#define PB0_8A_HDCP_AES_CIPHER_KEY_6                                0xB08A
#define PB0_8B_HDCP_AES_CIPHER_KEY_5                                0xB08B
#define PB0_8C_HDCP_AES_CIPHER_KEY_4                                0xB08C
#define PB0_8D_HDCP_AES_CIPHER_KEY_3                                0xB08D
#define PB0_8E_HDCP_AES_CIPHER_KEY_2                                0xB08E
#define PB0_8F_HDCP_AES_CIPHER_KEY_1                                0xB08F
#define PB0_90_HDCP_AES_CIPHER_KEY_0                                0xB090
#define PB0_93_HDCP_TYPE_AES_0                                      0xB093
#define PB0_94_HDCP_TYPE_AES_1                                      0xB094
#define PB0_95_HDCP_ST_TYPE                                         0xB095
#define PB0_96_DUMMY3                                               0xB096
#define PB0_97_DUMMY4                                               0xB097


//--------------------------------------------------
// D1 Port DisplayPort 1.2 HDCP power on(Page B0)
//--------------------------------------------------
#define PB0_A0_DP_HDCP_CONTROL                                      0xB0A0
#define PB0_A1_DP_HDCP_DOWNLOAD_PORT                                0xB0A1
#define PB0_A2_DP_HDCP_KEY_OUTPUT                                   0xB0A2
#define PB0_A3_HDCP_IRQ                                             0xB0A3
#define PB0_A4_HDCP_BIST                                            0xB0A4
#define PB0_A5_HDCP_DEBUG                                           0xB0A5
#define PB0_A6_KM                                                   0xB0A6
#define PB0_AA_TEST_SEL                                             0xB0AA


//--------------------------------------------------
// D0 Port DisplayPort 1.2 Digital MAC(Page B5)
//--------------------------------------------------
#define PB5_00_MAC_DIG_RESET_CTRL                                   0xB500
#define PB5_01_STHD_CTRL_0                                          0xB501
#define PB5_02_STHD_CTRL_1                                          0xB502
#define PB5_03_STHD_CTRL_2                                          0xB503
#define PB5_04_STHD_CTRL_3                                          0xB504
#define PB5_05_STHD_CTRL_4                                          0xB505
#define PB5_06_STHD_CTRL_5                                          0xB506
#define PB5_07_STHD_CTRL_6                                          0xB507
#define PB5_08_STHD_CTRL_7                                          0xB508
#define PB5_09_STHD_CTRL_8                                          0xB509
#define PB5_0A_STHD_CTRL_9                                          0xB50A
#define PB5_0B_STHD_CTRL_10                                         0xB50B
#define PB5_0C_STHD_CTRL_11                                         0xB50C
#define PB5_0D_SOURCE_SEL_0                                         0xB50D
#define PB5_0E_SOURCE_SEL_1                                         0xB50E
#define PB5_0F_SOURCE_SEL_2                                         0xB50F
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
#define PB5_63_VIDEO_EN_CNT_0                                       0xB563
#define PB5_64_VIDEO_EN_CNT_1                                       0xB564
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
// D0 Port DisplayPort 1.2 Digital MAC PLL(Page B5)
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
#define PB5_C4_M_CODE_ADJUST_0                                      0xB5C4
#define PB5_C5_M_CODE_ADJUST_1                                      0xB5C5
#define PB5_C6_M_CODE_ADJUST_2                                      0xB5C6
#define PB5_C7_VBID_MAN_MADE                                        0xB5C7
#define PB5_C8_DUMMY_1                                              0xB5C8
#define PB5_C9_DUMMY_2                                              0xB5C9
#define PB5_CA_DUMMY_3                                              0xB5CA


//--------------------------------------------------
// D0 DisplayPort Video SEC DATA (Page B6)
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


//--------------------------------------------------
// D0 DisplayPort Audio SEC DATA (Page B6)
//--------------------------------------------------
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
// D0 DisplayPort AUD PLL (Page B6)
//--------------------------------------------------
#define PB6_D0_AUDIO_CLK_CTRL                                       0xB6D0
#define PB6_D1_MN_SCLKG_DIVM                                        0xB6D1
#define PB6_D2_MN_SCLKG_DIVN                                        0xB6D2
#define PB6_D3_MN_SCLKG_PLL_PWR                                     0xB6D3
#define PB6_D4_MN_SCLKG_PLL_CHP                                     0xB6D4
#define PB6_D5_MN_SCLKG_PLL_WD                                      0xB6D5
#define PB6_D6_MN_SCLKG_PLL_INSEL                                   0xB6D6
#define PB6_D7_MN_SCLKG_PLL_RESERVE                                 0xB6D7


//--------------------------------------------------
// D0 Port DisplayPort 1.2 AUX DownReq MSG(Page B7)
//--------------------------------------------------
#define PB7_00_AUX_RX_MSG_RX_CTRL                                   0xB700
#define PB7_01_MSG_RX_FINISH_IRQ_EN                                 0xB701
#define PB7_02_MSG_RX_FINISH                                        0xB702
#define PB7_03_MSG_RX_FLAG                                          0xB703
#define PB7_04_MSG_RX_BUF_CLR                                       0xB704
#define PB7_05_MSG_RX_DATA0                                         0xB705
#define PB7_06_MSG_RX_DATA1                                         0xB706
#define PB7_07_MSG_RX_DATA2                                         0xB707
#define PB7_08_MSG_RX_DATA3                                         0xB708
#define PB7_09_MSG_RX_DATA4                                         0xB709
#define PB7_0A_MSG_RX_DATA5                                         0xB70A
#define PB7_0B_MSG_RX_DATA6                                         0xB70B
#define PB7_0C_MSG_RX_DATA7                                         0xB70C
#define PB7_0D_MSG_RX_DATA8                                         0xB70D
#define PB7_0E_MSG_RX_DATA9                                         0xB70E
#define PB7_0F_MSG_RX_DATAA                                         0xB70F
#define PB7_10_MSG_RX_BUF0_LEN                                      0xB710
#define PB7_11_MSG_RX_BUF0_WRPTR                                    0xB711
#define PB7_12_MSG_RX_BUF0_RDPTR                                    0xB712
#define PB7_13_MSG_RX_BUF0_RD_DATA                                  0xB713
#define PB7_14_MSG_RX_BUF1_LEN                                      0xB714
#define PB7_15_MSG_RX_BUF1_WRPTR                                    0xB715
#define PB7_16_MSG_RX_BUF1_RDPTR                                    0xB716
#define PB7_17_MSG_RX_BUF1_RD_DATA                                  0xB717
#define PB7_18_MSG_BUF_DEFER_WL                                     0xB718
#define PB7_19_MSG_SRAM_BIST_CTRL0                                  0xB719
#define PB7_1A_MSG_SRAM_DRF_BIST_CTRL0                              0xB71A
#define PB7_1B_MSG_EXCEPT_CTRL0                                     0xB71B
#define PB7_1C_MSG_EXCEPT_CTRL1                                     0xB71C
#define PB7_1D_MSG_STATUS_FLAG                                      0xB71D
#define PB7_1E_MSG_CTRL_DUMMY_2                                     0xB71E
#define PB7_1F_MSG_CTRL_DUMMY_3                                     0xB71F


//--------------------------------------------------
// D0 Port DisplayPort 1.2 AUX UpRep MSG(Page B7)
//--------------------------------------------------
#define PB7_20_AUX_RX_MSG_RX_CTRL                                   0xB720
#define PB7_21_MSG_RX_FINISH_IRQ_EN                                 0xB721
#define PB7_22_MSG_RX_FINISH                                        0xB722
#define PB7_23_MSG_RX_FLAG                                          0xB723
#define PB7_24_MSG_RX_BUF_CLR                                       0xB724
#define PB7_25_MSG_RX_DATA0                                         0xB725
#define PB7_26_MSG_RX_DATA1                                         0xB726
#define PB7_27_MSG_RX_DATA2                                         0xB727
#define PB7_28_MSG_RX_DATA3                                         0xB728
#define PB7_29_MSG_RX_DATA4                                         0xB729
#define PB7_2A_MSG_RX_DATA5                                         0xB72A
#define PB7_2B_MSG_RX_DATA6                                         0xB72B
#define PB7_2C_MSG_RX_DATA7                                         0xB72C
#define PB7_2D_MSG_RX_DATA8                                         0xB72D
#define PB7_2E_MSG_RX_DATA9                                         0xB72E
#define PB7_2F_MSG_RX_DATAA                                         0xB72F
#define PB7_30_MSG_RX_BUF0_LEN                                      0xB730
#define PB7_31_MSG_RX_BUF0_WRPTR                                    0xB731
#define PB7_32_MSG_RX_BUF0_RDPTR                                    0xB732
#define PB7_33_MSG_RX_BUF0_RD_DATA                                  0xB733
#define PB7_34_MSG_RX_BUF1_LEN                                      0xB734
#define PB7_35_MSG_RX_BUF1_WRPTR                                    0xB735
#define PB7_36_MSG_RX_BUF1_RDPTR                                    0xB736
#define PB7_37_MSG_RX_BUF1_RD_DATA                                  0xB737
#define PB7_38_MSG_BUF_DEFER_WL                                     0xB738
#define PB7_3B_MSG_EXCEPT_CTRL0                                     0xB73B
#define PB7_3C_MSG_EXCEPT_CTRL1                                     0xB73C
#define PB7_3D_MSG_STATUS_FLAG                                      0xB73D
#define PB7_3E_MSG_CTRL_DUMMY_2                                     0xB73E
#define PB7_3F_MSG_CTRL_DUMMY_3                                     0xB73F


//--------------------------------------------------
// D0 Port DisplayPort 1.2 AUX UpStream MSG(Page B7)
//--------------------------------------------------
#define PB7_40_AUX_RX_MSG_TX_CTRL                                   0xB740
#define PB7_41_MSG_TX_FINISH                                        0xB741
#define PB7_42_MSG_TX_LENGTH                                        0xB742
#define PB7_43_MSG_TX_SET0                                          0xB743
#define PB7_44_MSG_TX_SET1                                          0xB744
#define PB7_45_MSG_TX_SET2                                          0xB745
#define PB7_46_MSG_TX_SET3                                          0xB746
#define PB7_47_MSG_TX_SET4                                          0xB747
#define PB7_48_MSG_TX_SET5                                          0xB748
#define PB7_49_MSG_TX_SET6                                          0xB749
#define PB7_4A_MSG_TX_SET7                                          0xB74A
#define PB7_4B_MSG_TX_SET8                                          0xB74B
#define PB7_4C_MSG_TX_SET9                                          0xB74C
#define PB7_4D_MSG_TX_ADR_SEL                                       0xB74D
#define PB7_4E_BUF_RDPTR                                            0xB74E
#define PB7_4F_BUF_CLR                                              0xB74F
#define PB7_50_BUF_FW_WRPTR                                         0xB750
#define PB7_51_BUF_FW_WR_DATA                                       0xB751
#define PB7_52_BUF_END_FLAG                                         0xB752
#define PB7_53_MSG_TX_READ_FLAG                                     0xB753


//--------------------------------------------------
// D0 Port DisplayPort 1.2 AUX Analog PHY(Page B7)
//--------------------------------------------------
#define PB7_60_DIG_TX_04                                            0xB760
#define PB7_61_AUX_1                                                0xB761
#define PB7_62_AUX_2                                                0xB762
#define PB7_63_AUX_3                                                0xB763
#define PB7_64_AUX_4                                                0xB764
#define PB7_65_AUX_5                                                0xB765
#define PB7_66_AUX_6                                                0xB766
#define PB7_67_DIG_TX_03                                            0xB767


//--------------------------------------------------
// D0 Port DisplayPort 1.2 AUX Digital PHY(Page B7)
//--------------------------------------------------
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


//--------------------------------------------------
// D0 Port DisplayPort 1.2 AUX (Page B7)
//--------------------------------------------------
#define PB7_A0_AUX_RESERVE0                                         0xB7A0
#define PB7_A1_AUX_RESERVE1                                         0xB7A1
#define PB7_A2_AUX_RESERVE2                                         0xB7A2
#define PB7_A3_AUX_RESERVE3                                         0xB7A3
#define PB7_A4_AUX_RESERVE4                                         0xB7A4
#define PB7_A5_AUX_RESERVE5                                         0xB7A5
#define PB7_B0_AUX_PAYLOAD_CLEAR                                    0xB7B0
#define PB7_B1_MST_ACT_IRQ                                          0xB7B1
#define PB7_B2_AUX_SPECIAL_IRQ_EN                                   0xB7B2
#define PB7_B3_AUX_SPECIAL_IRQ_FLAG                                 0xB7B3
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
#define PB7_F7_HDCP22_SRAM_BIST_0                                   0xB7F7
#define PB7_F8_HDCP22_SRAM_BIST_1                                   0xB7F8
#define PB7_FA_DUMMY_0                                              0xB7FA
#define PB7_FB_DUMMY_1                                              0xB7FB
#define PB7_FF_TEST_FUNCTION                                        0xB7FF


//--------------------------------------------------
// D1 Port DisplayPort 1.2 Digital MAC(Page B8)
//--------------------------------------------------
#define PB8_00_MAC_DIG_RESET_CTRL                                   0xB800
#define PB8_01_STHD_CTRL_0                                          0xB801
#define PB8_02_STHD_CTRL_1                                          0xB802
#define PB8_03_STHD_CTRL_2                                          0xB803
#define PB8_04_STHD_CTRL_3                                          0xB804
#define PB8_05_STHD_CTRL_4                                          0xB805
#define PB8_06_STHD_CTRL_5                                          0xB806
#define PB8_07_STHD_CTRL_6                                          0xB807
#define PB8_08_STHD_CTRL_7                                          0xB808
#define PB8_09_STHD_CTRL_8                                          0xB809
#define PB8_0A_STHD_CTRL_9                                          0xB80A
#define PB8_0B_STHD_CTRL_10                                         0xB80B
#define PB8_0C_STHD_CTRL_11                                         0xB80C
#define PB8_0D_SOURCE_SEL_0                                         0xB80D
#define PB8_0E_SOURCE_SEL_1                                         0xB80E
#define PB8_0F_SOURCE_SEL_2                                         0xB80F
#define PB8_20_PG_CTRL_0                                            0xB820
#define PB8_21_PG_CTRL_1                                            0xB821
#define PB8_22_PG_CTRL_2                                            0xB822
#define PB8_23_PG_CTRL_3                                            0xB823
#define PB8_24_RB422_YONLY                                          0xB824
#define PB8_25_SRAM_BIST_0                                          0xB825
#define PB8_26_SRAM_BIST_1                                          0xB826
#define PB8_30_DPF_CTRL_0                                           0xB830
#define PB8_31_DP_OUTPUT_CTRL                                       0xB831
#define PB8_32_EVBLK2VS_H                                           0xB832
#define PB8_33_EVBLK2VS_M                                           0xB833
#define PB8_34_EVBLK2VS_L                                           0xB834
#define PB8_35_OVBLK2VS_H                                           0xB835
#define PB8_36_OVBLK2VS_M                                           0xB836
#define PB8_37_OVBLK2VS_L                                           0xB837
#define PB8_38_BS2HS_0                                              0xB838
#define PB8_39_BS2HS_1                                              0xB839
#define PB8_40_VS_FRONT_PORCH                                       0xB840
#define PB8_41_MN_DPF_HTT_M                                         0xB841
#define PB8_42_MN_DPF_HTT_L                                         0xB842
#define PB8_43_MN_DPF_HST_M                                         0xB843
#define PB8_44_MN_DPF_HST_L                                         0xB844
#define PB8_45_MN_DPF_HWD_M                                         0xB845
#define PB8_46_MN_DPF_HWD_L                                         0xB846
#define PB8_47_MN_DPF_HSW_M                                         0xB847
#define PB8_48_MN_DPF_HSW_L                                         0xB848
#define PB8_49_MN_DPF_VTT_M                                         0xB849
#define PB8_4A_MN_DPF_VTT_L                                         0xB84A
#define PB8_4B_MN_DPF_VST_M                                         0xB84B
#define PB8_4C_MN_DPF_VST_L                                         0xB84C
#define PB8_4D_MN_DPF_VHT_M                                         0xB84D
#define PB8_4E_MN_DPF_VHT_L                                         0xB84E
#define PB8_4F_MN_DPF_VSW_M                                         0xB84F
#define PB8_50_MN_DPF_VSW_L                                         0xB850
#define PB8_51_MN_DPF_BG_RED_M                                      0xB851
#define PB8_52_MN_DPF_BG_RED_L                                      0xB852
#define PB8_53_MN_DPF_BG_GRN_M                                      0xB853
#define PB8_54_MN_DPF_BG_GRN_L                                      0xB854
#define PB8_55_MN_DPF_BG_BLU_M                                      0xB855
#define PB8_56_MN_DPF_BG_BLU_L                                      0xB856
#define PB8_57_INTERLACE_MODE_CONFIG                                0xB857
#define PB8_58_MN_MEAS_CTRL                                         0xB858
#define PB8_59_MN_MEAS_VLN_M                                        0xB859
#define PB8_5A_MN_MEAS_VLN_L                                        0xB85A
#define PB8_5B_MN_MEAS_HLN_M                                        0xB85B
#define PB8_5C_MN_MEAS_HLN_L                                        0xB85C
#define PB8_5D_VHEIGHT_MSB                                          0xB85D
#define PB8_5E_VHEIGHT_LSB                                          0xB85E
#define PB8_5F_VBLANK_MSB                                           0xB85F
#define PB8_60_VBLANK_LSB                                           0xB860
#define PB8_61_HBLANK_MSB                                           0xB861
#define PB8_62_HBLANK_LSB                                           0xB862
#define PB8_63_VIDEO_EN_CNT_0                                       0xB863
#define PB8_64_VIDEO_EN_CNT_1                                       0xB864
#define PB8_70_DP_CRC_CTRL                                          0xB870
#define PB8_71_DP_CRC_R_M                                           0xB871
#define PB8_72_DP_CRC_R_L                                           0xB872
#define PB8_73_DP_CRC_G_M                                           0xB873
#define PB8_74_DP_CRC_G_L                                           0xB874
#define PB8_75_DP_CRC_B_M                                           0xB875
#define PB8_76_DP_CRC_B_L                                           0xB876
#define PB8_77_DP_CRC_CB_M                                          0xB877
#define PB8_78_DP_CRC_CB_L                                          0xB878
#define PB8_E0_TEST0                                                0xB8E0
#define PB8_E1_TEST1                                                0xB8E1
#define PB8_E2_CPMODE                                               0xB8E2
#define PB8_F0_DP_RSV0                                              0xB8F0
#define PB8_F1_DP_RSV1                                              0xB8F1
#define PB8_F2_DP_RSV2                                              0xB8F2
#define PB8_F3_DP_RSV3                                              0xB8F3
#define PB8_F4_DP_RSV4                                              0xB8F4
#define PB8_F5_DP_RSV5                                              0xB8F5
#define PB8_F6_DP_RSV6                                              0xB8F6
#define PB8_F7_DP_RSV7                                              0xB8F7
#define PB8_F8_DP_RSV8                                              0xB8F8
#define PB8_F9_DP_RSV9                                              0xB8F9
#define PB8_FA_DP_RSVA                                              0xB8FA


//--------------------------------------------------
// D1 Port DisplayPort 1.2 Digital MAC PLL(Page B8)
//--------------------------------------------------
#define PB8_A0_MN_SCLKG_CTRL                                        0xB8A0
#define PB8_A1_MN_SCLKG_DIVM                                        0xB8A1
#define PB8_A2_MN_SCLKG_DIVN                                        0xB8A2
#define PB8_A3_MN_SCLKG_DIVS                                        0xB8A3
#define PB8_A4_MN_SCLKG_OFFS_H                                      0xB8A4
#define PB8_A5_MN_SCLKG_OFFS_M                                      0xB8A5
#define PB8_A6_MN_SCLKG_OFFS_L                                      0xB8A6
#define PB8_A7_MN_SCLKG_TRK_CTRL                                    0xB8A7
#define PB8_A8_MN_SCLKG_TRK_MN_I_H                                  0xB8A8
#define PB8_A9_MN_SCLKG_TRK_MN_I_M                                  0xB8A9
#define PB8_AA_MN_SCLKG_TRK_MN_I_L                                  0xB8AA
#define PB8_AB_MN_SCLKG_TRK_MN_P_H                                  0xB8AB
#define PB8_AC_MN_SCLKG_TRK_MN_P_M                                  0xB8AC
#define PB8_AD_MN_SCLKG_TRK_MN_P_L                                  0xB8AD
#define PB8_AE_MN_SCLKG_TRK_MN_PE                                   0xB8AE
#define PB8_AF_MN_SCLKG_TRK_MN_NLOCK                                0xB8AF
#define PB8_B0_MN_SCLKG_TRK_VS_I_H                                  0xB8B0
#define PB8_B1_MN_SCLKG_TRK_VS_I_M                                  0xB8B1
#define PB8_B2_MN_SCLKG_TRK_VS_I_L                                  0xB8B2
#define PB8_B3_MN_SCLKG_TRK_VS_P_H                                  0xB8B3
#define PB8_B4_MN_SCLKG_TRK_VS_P_M                                  0xB8B4
#define PB8_B5_MN_SCLKG_TRK_VS_P_L                                  0xB8B5
#define PB8_B6_MN_SCLKG_TRK_VS_PE                                   0xB8B6
#define PB8_B7_MN_SCLKG_TRK_VS_NLOCK                                0xB8B7
#define PB8_B8_MN_SCLKG_SDM_CTRL                                    0xB8B8
#define PB8_B9_MN_SCLKG_SDM_TEST                                    0xB8B9
#define PB8_BA_MN_SCLKG_SDM_SUMC_H                                  0xB8BA
#define PB8_BB_MN_SCLKG_SDM_SUMC_M                                  0xB8BB
#define PB8_BC_MN_SCLKG_SDM_SUMC_L                                  0xB8BC
#define PB8_BD_MN_SCLKG_PLL_PWR                                     0xB8BD
#define PB8_BE_MN_SCLKG_PLL_CHP                                     0xB8BE
#define PB8_BF_MN_SCLKG_PLL_WD                                      0xB8BF
#define PB8_C0_MN_SCLKG_PLL_INSEL                                   0xB8C0
#define PB8_C1_MN_SCLKG_PLL_RESERVE                                 0xB8C1
#define PB8_C2_HS_TRACKING_NEW_MODE1                                0xB8C2
#define PB8_C3_HS_TRACKING_NEW_MODE2                                0xB8C3
#define PB8_C4_M_CODE_ADJUST_0                                      0xB8C4
#define PB8_C5_M_CODE_ADJUST_1                                      0xB8C5
#define PB8_C6_M_CODE_ADJUST_2                                      0xB8C6
#define PB8_C7_VBID_MAN_MADE                                        0xB8C7
#define PB8_C8_DUMMY_1                                              0xB8C8
#define PB8_C9_DUMMY_2                                              0xB8C9
#define PB8_CA_DUMMY_3                                              0xB8CA


//--------------------------------------------------
// D1 DisplayPort Video SEC DATA (Page B9)
//--------------------------------------------------
#define PB9_00_MN_STRM_ATTR_CTRL                                    0xB900
#define PB9_01_DP_VBID                                              0xB901
#define PB9_02_MN_STRM_ATTR_MISC                                    0xB902
#define PB9_03_MN_STRM_ATTR_MISC1                                   0xB903
#define PB9_08_MSA_HTT_0                                            0xB908
#define PB9_09_MSA_HTT_1                                            0xB909
#define PB9_0A_MSA_HST_0                                            0xB90A
#define PB9_0B_MSA_HST_1                                            0xB90B
#define PB9_0C_MSA_HWD_0                                            0xB90C
#define PB9_0D_MSA_HWD_1                                            0xB90D
#define PB9_0E_MSA_HSW_0                                            0xB90E
#define PB9_0F_MSA_HSW_1                                            0xB90F
#define PB9_10_MSA_VTTE_0                                           0xB910
#define PB9_11_MSA_VTTE_1                                           0xB911
#define PB9_12_MSA_VTTO_0                                           0xB912
#define PB9_13_MSA_VTTO_1                                           0xB913
#define PB9_14_MSA_VST_0                                            0xB914
#define PB9_15_MSA_VST_1                                            0xB915
#define PB9_16_MSA_VHT_0                                            0xB916
#define PB9_17_MSA_VHT_1                                            0xB917
#define PB9_18_MSA_VSW_0                                            0xB918
#define PB9_19_MSA_VSW_1                                            0xB919
#define PB9_1A_MSA_MVID_0                                           0xB91A
#define PB9_1B_MSA_MVID_1                                           0xB91B
#define PB9_1C_MSA_MVID_2                                           0xB91C
#define PB9_1D_MSA_NVID_0                                           0xB91D
#define PB9_1E_MSA_NVID_1                                           0xB91E
#define PB9_1F_MSA_NVID_2                                           0xB91F
#define PB9_20_MSA_MAUD_0                                           0xB920
#define PB9_21_MSA_MAUD_1                                           0xB921
#define PB9_22_MSA_MAUD_2                                           0xB922
#define PB9_23_MSA_NAUD_0                                           0xB923
#define PB9_24_MSA_NAUD_1                                           0xB924
#define PB9_25_MSA_NAUD_2                                           0xB925
#define PB9_26_DP_AUD_CH_STATUS0                                    0xB926
#define PB9_27_DP_AUD_CH_STATUS1                                    0xB927
#define PB9_28_DP_AUD_CH_STATUS2                                    0xB928
#define PB9_29_DP_AUD_CH_STATUS3                                    0xB929
#define PB9_2A_DP_AUD_CH_STATUS4                                    0xB92A
#define PB9_2B_MN_RS_DEC_CTRL                                       0xB92B
#define PB9_2C_DP_INFO_FM_RSV0                                      0xB92C
#define PB9_2D_DP_INFO_FM_RSV1                                      0xB92D
#define PB9_30_DP_INFO_FM_ADR                                       0xB930
#define PB9_31_DP_INFO_FM_DAT                                       0xB931
#define PB9_32_DP_INFO_VAR_EN_M                                     0xB932
#define PB9_33_DP_INFO_VAR_EN_L                                     0xB933
#define PB9_34_DP_INFO_VAR_ST_M                                     0xB934
#define PB9_35_DP_INFO_VAR_ST_L                                     0xB935
#define PB9_36_DP_GLB_STATUS                                        0xB936
#define PB9_37_DP_AVWD_CTRL                                         0xB937
#define PB9_38_DP_VWD_CTRL                                          0xB938
#define PB9_39_DP_AWD_CTRL                                          0xB939
#define PB9_3A_DP_IRQ_CTRL0                                         0xB93A
#define PB9_3B_DP_IRQ_CTRL1                                         0xB93B
#define PB9_40_VSC0                                                 0xB940
#define PB9_41_VSC1                                                 0xB941
#define PB9_42_VSC2                                                 0xB942
#define PB9_43_VSC3                                                 0xB943
#define PB9_44_VSC4                                                 0xB944
#define PB9_45_VSC5                                                 0xB945
#define PB9_46_VSC6                                                 0xB946
#define PB9_47_VSC7                                                 0xB947
#define PB9_48_VSC8                                                 0xB948
#define PB9_49_VSC9                                                 0xB949
#define PB9_4A_VSCA                                                 0xB94A
#define PB9_4B_VSCB                                                 0xB94B
#define PB9_4C_VSCC                                                 0xB94C
#define PB9_4D_DP_LR_SEL                                            0xB94D
#define PB9_4E_SRAM_BIST_0                                          0xB94E
#define PB9_4F_SRAM_BIST_1                                          0xB94F


//--------------------------------------------------
// D1 DisplayPort Audio SEC DATA (Page B9)
//--------------------------------------------------
#define PB9_50_AUD_FREQUENY_DET_0                                   0xB950
#define PB9_51_AUD_FREQUENY_DET_1                                   0xB951
#define PB9_52_AUD_FREQUENY_TH_0                                    0xB952
#define PB9_53_AUD_FREQUENY_TH_1                                    0xB953
#define PB9_54_AUD_FREQUENY_TH_2                                    0xB954
#define PB9_55_AUD_FREQUENY_TH_3                                    0xB955
#define PB9_56_AUD_FREQUENY_TH_4                                    0xB956
#define PB9_57_AUD_FREQUENY_TH_5                                    0xB957
#define PB9_58_SCODE_0                                              0xB958
#define PB9_59_SCODE_1                                              0xB959
#define PB9_5A_SCODE_2                                              0xB95A
#define PB9_5B_DCODE_0                                              0xB95B
#define PB9_5C_DCODE_1                                              0xB95C
#define PB9_5D_DCODE_2                                              0xB95D
#define PB9_5E_DCODE_3                                              0xB95E
#define PB9_5F_DCODE_4                                              0xB95F
#define PB9_60_DCODE_5                                              0xB960
#define PB9_61_AUD_SAMPLE_CNT_0                                     0xB961
#define PB9_62_AUD_SAMPLE_CNT_1                                     0xB962
#define PB9_63_AUD_DEPTH_TRACKING_NUM_0                             0xB963
#define PB9_64_AUD_DEPTH_TRACKING_NUM_1                             0xB964
#define PB9_65_AUD_DEPTH_TRACKING_NUM_2                             0xB965
#define PB9_66_AUD_DEPTH_TRACKING_NUM_3                             0xB966
#define PB9_67_AUD_DEPTH_TRACKING_NUM_4                             0xB967
#define PB9_68_AUD_DEPTH_ICODE_0                                    0xB968
#define PB9_69_AUD_DEPTH_ICODE_1                                    0xB969
#define PB9_6A_AUD_DEPTH_ICODE_2                                    0xB96A
#define PB9_6B_AUD_DEPTH_ICODE_3                                    0xB96B
#define PB9_6C_AUD_DEPTH_ICODE_4                                    0xB96C
#define PB9_6D_AUD_DEPTH_IGAIN_0                                    0xB96D
#define PB9_6E_AUD_DEPTH_IGAIN_1                                    0xB96E
#define PB9_70_AUD_BUFFER_CTRL_0                                    0xB970
#define PB9_71_AUD_BUFFER_CTRL_1                                    0xB971
#define PB9_72_AUD_BUFFER_CTRL_2                                    0xB972
#define PB9_73_AUD_BUFFER_CTRL_3                                    0xB973
#define PB9_74_AUD_FSM_CTRL_0                                       0xB974
#define PB9_75_AUD_MAN_FSM_CTRL_1                                   0xB975
#define PB9_76_DVC_CTRL                                             0xB976
#define PB9_77_DVC_VA                                               0xB977
#define PB9_78_DVC_WINDOW_CONTROL_0                                 0xB978
#define PB9_79_DVC_WINDOW_CONTROL_1                                 0xB979
#define PB9_7A_DVC_GAIN_READ_MSB                                    0xB97A
#define PB9_7B_DVC_GAIN_READ_LSB                                    0xB97B
#define PB9_7C_AUD_FSM_CTRL_1                                       0xB97C
#define PB9_7D_AUD_FSM_CTRL_2                                       0xB97D
#define PB9_7E_DVC_WINDOW_CONTROL_FAN_OUT                           0xB97E
#define PB9_80_AUD_PS_CTRL_0                                        0xB980
#define PB9_81_AUD_BDRY_0                                           0xB981
#define PB9_82_AUD_BDRY_1                                           0xB982
#define PB9_83_AUD_BDRY_2                                           0xB983
#define PB9_84_AUD_BDRY_3                                           0xB984
#define PB9_85_AUD_BDRY_4                                           0xB985
#define PB9_86_AUD_BDRY_5                                           0xB986
#define PB9_87_AUD_DEPTH_0                                          0xB987
#define PB9_88_AUD_DEPTH_1                                          0xB988
#define PB9_89_AUD_DEPTH_2                                          0xB989
#define PB9_8A_AUD_DEPTH_5                                          0xB98A
#define PB9_8B_AUD_DEPTH_6                                          0xB98B
#define PB9_8C_AUD_MN_DEPTH                                         0xB98C
#define PB9_8D_AUD_MN_0                                             0xB98D
#define PB9_8E_AUD_MN_1                                             0xB98E
#define PB9_8F_AUD_MN_2                                             0xB98F
#define PB9_90_AUD_MN_3                                             0xB990
#define PB9_91_AUD_MN_4                                             0xB991
#define PB9_92_AUD_TRND_0                                           0xB992
#define PB9_93_AUD_TRND_1                                           0xB993
#define PB9_94_AUD_TRND_2                                           0xB994
#define PB9_95_AUD_TRND_3                                           0xB995
#define PB9_96_AUD_TRND_4                                           0xB996
#define PB9_97_AUD_TRND_5                                           0xB997
#define PB9_98_AUD_TRND_6                                           0xB998
#define PB9_99_AUD_TRND_7                                           0xB999
#define PB9_9A_AUD_TRND_8                                           0xB99A
#define PB9_9B_AUD_TRND_9                                           0xB99B
#define PB9_9C_AUD_TRND_10                                          0xB99C
#define PB9_9D_AUD_D_CODE_0                                         0xB99D
#define PB9_A0_AUD_D_CODE_1                                         0xB9A0
#define PB9_A1_AUD_SUMC_MSB                                         0xB9A1
#define PB9_A2_AUD_SUMC_LSB                                         0xB9A2
#define PB9_A9_SPDIF_TX_0                                           0xB9A9
#define PB9_AA_SPDIF_CS_0                                           0xB9AA
#define PB9_AB_SPDIF_CS_1                                           0xB9AB
#define PB9_AC_SPDIF_CS_2                                           0xB9AC
#define PB9_AD_SPDIF_CS_3                                           0xB9AD
#define PB9_AE_SPDIF_CS_4                                           0xB9AE
#define PB9_B0_DP_AUD_CTRL                                          0xB9B0
#define PB9_B1_DP_AUD_ID                                            0xB9B1
#define PB9_B2_DP_AUD_ID_DETECT                                     0xB9B2
#define PB9_B3_DP_CHANNEL_EN                                        0xB9B3
#define PB9_B4_DP_SEC_MISC                                          0xB9B4
#define PB9_B5_DP_AUD_CRC                                           0xB9B5
#define PB9_B6_DP_AUD_CRC_1                                         0xB9B6
#define PB9_B7_TEST_PIN                                             0xB9B7
#define PB9_B8_DP_I2S_CTRL                                          0xB9B8
#define PB9_B9_AUD_I2S_CRC_HB                                       0xB9B9
#define PB9_BA_AUD_I2S_CRC_LB                                       0xB9BA
#define PB9_BB_TO_DAC_CH_SEL                                        0xB9BB
#define PB9_C0_AUD_DEPTH_7                                          0xB9C0
#define PB9_C1_AUD_DEPTH_8                                          0xB9C1
#define PB9_FC_DUMMY_0                                              0xB9FC
#define PB9_FD_DUMMY_1                                              0xB9FD
#define PB9_FE_DUMMY_2                                              0xB9FE
#define PB9_FF_DUMMY_3                                              0xB9FF


//--------------------------------------------------
// D1 DisplayPort AUD PLL (Page B9)
//--------------------------------------------------
#define PB9_D0_AUDIO_CLK_CTRL                                       0xB9D0
#define PB9_D1_MN_SCLKG_DIVM                                        0xB9D1
#define PB9_D2_MN_SCLKG_DIVN                                        0xB9D2
#define PB9_D3_MN_SCLKG_PLL_PWR                                     0xB9D3
#define PB9_D4_MN_SCLKG_PLL_CHP                                     0xB9D4
#define PB9_D5_MN_SCLKG_PLL_WD                                      0xB9D5
#define PB9_D6_MN_SCLKG_PLL_INSEL                                   0xB9D6
#define PB9_D7_MN_SCLKG_PLL_RESERVE                                 0xB9D7


//--------------------------------------------------
// D1 Port DisplayPort 1.2 AUX Analog PHY(Page BA)
//--------------------------------------------------
#define PBA_60_DIG_TX_04                                            0xBA60
#define PBA_61_AUX_1                                                0xBA61
#define PBA_62_AUX_2                                                0xBA62
#define PBA_63_AUX_3                                                0xBA63
#define PBA_64_AUX_4                                                0xBA64
#define PBA_65_AUX_5                                                0xBA65
#define PBA_66_AUX_6                                                0xBA66
#define PBA_67_DIG_TX_03                                            0xBA67


//--------------------------------------------------
// D1 Port DisplayPort 1.2 AUX Digital PHY(Page BA)
//--------------------------------------------------
#define PBA_70_AUX_DIG_PHY0                                         0xBA70
#define PBA_71_AUX_DIG_PHY1                                         0xBA71
#define PBA_72_AUX_DIG_PHY2                                         0xBA72
#define PBA_73_AUX_DIG_PHY3                                         0xBA73
#define PBA_74_AUX_DIG_PHY4                                         0xBA74
#define PBA_75_AUX_DIG_PHY5                                         0xBA75
#define PBA_76_AUX_DIG_PHY6                                         0xBA76
#define PBA_77_AUX_DIG_PHY7                                         0xBA77
#define PBA_78_AUX_DIG_PHY8                                         0xBA78
#define PBA_79_AUX_DIG_PHY9                                         0xBA79
#define PBA_7A_AUX_DIG_PHYA                                         0xBA7A
#define PBA_7B_GDI_POWER_TIMER                                      0xBA7B
#define PBA_7C_GDI_POWER_FLAG                                       0xBA7C
#define PBA_7D_AUX_DELAY_TIMER                                      0xBA7D
#define PBA_7E_AUX_DELAY_FIFO                                       0xBA7E
#define PBA_7F_AUX_DEBUG                                            0xBA7F


//--------------------------------------------------
// D1 Port DisplayPort 1.2 AUX (Page BA)
//--------------------------------------------------
#define PBA_A0_AUX_RESERVE0                                         0xBAA0
#define PBA_A1_AUX_RESERVE1                                         0xBAA1
#define PBA_A2_AUX_RESERVE2                                         0xBAA2
#define PBA_A3_AUX_RESERVE3                                         0xBAA3
#define PBA_A4_AUX_RESERVE4                                         0xBAA4
#define PBA_A5_AUX_RESERVE5                                         0xBAA5
#define PBA_B0_AUX_PAYLOAD_CLEAR                                    0xBAB0
#define PBA_B1_MST_ACT_IRQ                                          0xBAB1
#define PBA_B2_AUX_SPECIAL_IRQ_EN                                   0xBAB2
#define PBA_B3_AUX_SPECIAL_IRQ_FLAG                                 0xBAB3
#define PBA_B4_AUX_IRQ_ADDR0_MSB                                    0xBAB4
#define PBA_B5_AUX_IRQ_ADDR0_MSB1                                   0xBAB5
#define PBA_B6_AUX_IRQ_ADDR0_LSB                                    0xBAB6
#define PBA_B7_AUX_IRQ_ADDR1_MSB                                    0xBAB7
#define PBA_B8_AUX_IRQ_ADDR1_MSB1                                   0xBAB8
#define PBA_B9_AUX_IRQ_ADDR1_LSB                                    0xBAB9
#define PBA_BA_AUX_IRQ_ADDR2_MSB                                    0xBABA
#define PBA_BB_AUX_IRQ_ADDR2_MSB1                                   0xBABB
#define PBA_BC_AUX_IRQ_ADDR2_LSB                                    0xBABC
#define PBA_BD_AUX_IRQ_ADDR3_MSB                                    0xBABD
#define PBA_BE_AUX_IRQ_ADDR3_MSB1                                   0xBABE
#define PBA_BF_AUX_IRQ_ADDR3_LSB                                    0xBABF
#define PBA_C0_DPCD_CTRL                                            0xBAC0
#define PBA_C1_DPCD_ADDR_PORT_H                                     0xBAC1
#define PBA_C2_DPCD_ADDR_PORT_M                                     0xBAC2
#define PBA_C3_DPCD_ADDR_PORT_L                                     0xBAC3
#define PBA_C4_DPCD_DATA_PORT                                       0xBAC4
#define PBA_C6_AUX_PHY_DIG2                                         0xBAC6
#define PBA_C7_TP1_OCCR                                             0xBAC7
#define PBA_D0_AUX_MODE_SET                                         0xBAD0
#define PBA_D1_DP_IIC_SET                                           0xBAD1
#define PBA_D2_AUX_RX_CMD                                           0xBAD2
#define PBA_D3_AUX_RX_ADDR_M                                        0xBAD3
#define PBA_D4_AUX_RX_ADDR_L                                        0xBAD4
#define PBA_D5_AUX_RXLEN                                            0xBAD5
#define PBA_D6_AUX_RX_DATA                                          0xBAD6
#define PBA_D7_AUX_TX_CMD                                           0xBAD7
#define PBA_D8_AUX_TX_LEN                                           0xBAD8
#define PBA_D9_AUX_TX_DATA                                          0xBAD9
#define PBA_DA_AUX_FIFO_RST                                         0xBADA
#define PBA_DB_AUX_STATUS                                           0xBADB
#define PBA_DC_AUX_IRQ_STATUS                                       0xBADC
#define PBA_DD_AUX_DPCD_IRQ                                         0xBADD
#define PBA_DE_AUX_DPCD_IRQ_EN                                      0xBADE
#define PBA_DF_AUX_IIC_MASTER_CTRL                                  0xBADF
#define PBA_F0_AUX_TX_TIMER                                         0xBAF0
#define PBA_F1_AUX_TX_TIMER_2                                       0xBAF1
#define PBA_F2_IIC_DEBOUNCE                                         0xBAF2
#define PBA_F3_IIC_SLAVE_ADD                                        0xBAF3
#define PBA_F4_MCUIIC                                               0xBAF4
#define PBA_F5_MCUNA_MSB_1                                          0xBAF5
#define PBA_F6_MCUNA_MSB_2                                          0xBAF6
#define PBA_F7_HDCP22_SRAM_BIST_0                                   0xBAF7
#define PBA_F8_HDCP22_SRAM_BIST_1                                   0xBAF8
#define PBA_FA_DUMMY_0                                              0xBAFA
#define PBA_FB_DUMMY_1                                              0xBAFB
#define PBA_FF_TEST_FUNCTION                                        0xBAFF


//--------------------------------------------------
// DisplayPort Tx Digital PHY CTRL (Page BB)
//--------------------------------------------------
#define PBB_00_DP_PHY_CTRL                                          0xBB00
#define PBB_01_DPTX_ML_PAT_SEL                                      0xBB01
#define PBB_02_CUSTOM_PATTERN_0                                     0xBB02
#define PBB_03_CUSTOM_PATTERN_1                                     0xBB03
#define PBB_04_CUSTOM_PATTERN_2                                     0xBB04
#define PBB_05_CUSTOM_PATTERN_3                                     0xBB05
#define PBB_06_CUSTOM_PATTERN_4                                     0xBB06
#define PBB_07_CUSTOM_PATTERN_5                                     0xBB07
#define PBB_08_CUSTOM_PATTERN_6                                     0xBB08
#define PBB_09_CUSTOM_PATTERN_7                                     0xBB09
#define PBB_0A_CUSTOM_PATTERN_8                                     0xBB0A
#define PBB_0B_CUSTOM_PATTERN_9                                     0xBB0B
#define PBB_0C_COMPLIANCE_EYE_PATTERN                               0xBB0C
#define PBB_0D_DPTX_PHY_CTRL                                        0xBB0D
#define PBB_0E_DPTX_LANE_SWAP                                       0xBB0E
#define PBB_0F_DPTX_8B10B_TST                                       0xBB0F
#define PBB_10_DPTX_PHY_DUMMY                                       0xBB10
#define PBB_11_RIV0                                                 0xBB11
#define PBB_12_RIV1                                                 0xBB12
#define PBB_13_RIV2                                                 0xBB13
#define PBB_14_RIV3                                                 0xBB14
#define PBB_15_RIV4                                                 0xBB15
#define PBB_16_RIV5                                                 0xBB16
#define PBB_17_RIV6                                                 0xBB17
#define PBB_18_RIV7                                                 0xBB18
#define PBB_30_DPTX_HDCP_CTRL1                                      0xBB30
#define PBB_31_DPTX_HDCP_CTRL2                                      0xBB31
#define PBB_32_DP_HDCP_KEY_DL_PORT                                  0xBB32
#define PBB_33_DP_HDCP_KEY_OUTPUT                                   0xBB33
#define PBB_34_AN_BYTE_7                                            0xBB34
#define PBB_35_AN_BYTE_6                                            0xBB35
#define PBB_36_AN_BYTE_5                                            0xBB36
#define PBB_37_AN_BYTE_4                                            0xBB37
#define PBB_38_AN_BYTE_3                                            0xBB38
#define PBB_39_AN_BYTE_2                                            0xBB39
#define PBB_3A_AN_BYTE_1                                            0xBB3A
#define PBB_3B_AN_BYTE_0                                            0xBB3B
#define PBB_3C_M0_BYTE_7                                            0xBB3C
#define PBB_3D_M0_BYTE_6                                            0xBB3D
#define PBB_3E_M0_BYTE_5                                            0xBB3E
#define PBB_3F_M0_BYTE_4                                            0xBB3F
#define PBB_40_M0_BYTE_3                                            0xBB40
#define PBB_41_M0_BYTE_2                                            0xBB41
#define PBB_42_M0_BYTE_1                                            0xBB42
#define PBB_43_M0_BYTE_0                                            0xBB43
#define PBB_44_KM_BYTE_6                                            0xBB44
#define PBB_45_KM_BYTE_5                                            0xBB45
#define PBB_46_KM_BYTE_4                                            0xBB46
#define PBB_47_KM_BYTE_3                                            0xBB47
#define PBB_48_KM_BYTE_2                                            0xBB48
#define PBB_49_KM_BYTE_1                                            0xBB49
#define PBB_4A_KM_BYTE_0                                            0xBB4A
#define PBB_4B_R0_BYTE_MSB                                          0xBB4B
#define PBB_4C_R0_BYTE_LSB                                          0xBB4C
#define PBB_4D_RI_BYTE_MSB                                          0xBB4D
#define PBB_4E_RI_BYTE_LSB                                          0xBB4E
#define PBB_4F_BKSV_0                                               0xBB4F
#define PBB_50_BKSV_1                                               0xBB50
#define PBB_51_BKSV_2                                               0xBB51
#define PBB_52_BKSV_3                                               0xBB52
#define PBB_53_BKSV_4                                               0xBB53
#define PBB_54_HDCP_TX_LIP_H                                        0xBB54
#define PBB_55_HDCP_TX_LIP_L                                        0xBB55
#define PBB_56_DP_HDCP_TX                                           0xBB56
#define PBB_57_DP_HDCP_BIST                                         0xBB57
#define PBB_58_DP_HDCP_AN_SEED                                      0xBB58
#define PBB_59_HDCP_IRQ_EVENT                                       0xBB59
#define PBB_5A_DPTX_HDCP_TST                                        0xBB5A
#define PBB_5B_DP_HDCP_TX_SHA_CTRL                                  0xBB5B
#define PBB_5C_DP_HDCP_TX_SHA_DATA_3                                0xBB5C
#define PBB_5D_DP_HDCP_TX_SHA_DATA_2                                0xBB5D
#define PBB_5E_DP_HDCP_TX_SHA_DATA_1                                0xBB5E
#define PBB_5F_DP_HDCP_TX_SHA_DATA_0                                0xBB5F
#define PBB_60_DP_HDCP_TX_SHA_OUT_3                                 0xBB60
#define PBB_61_DP_HDCP_TX_SHA_OUT_2                                 0xBB61
#define PBB_62_DP_HDCP_TX_SHA_OUT_1                                 0xBB62
#define PBB_63_DP_HDCP_TX_SHA_OUT_0                                 0xBB63
#define PBB_64_HDCP_ECF_BYTE0                                       0xBB64
#define PBB_65_HDCP_ECF_BYTE1                                       0xBB65
#define PBB_66_HDCP_ECF_BYTE2                                       0xBB66
#define PBB_67_HDCP_ECF_BYTE3                                       0xBB67
#define PBB_68_HDCP_ECF_BYTE4                                       0xBB68
#define PBB_69_HDCP_ECF_BYTE5                                       0xBB69
#define PBB_6A_HDCP_ECF_BYTE6                                       0xBB6A
#define PBB_6B_HDCP_ECF_BYTE7                                       0xBB6B
#define PBB_6C_DP_STREAM_1_PBN                                      0xBB6C
#define PBB_6D_DP_STREAM_2_PBN                                      0xBB6D
#define PBB_6E_DP_STREAM_3_PBN                                      0xBB6E
#define PBB_6F_DP_STREAM_4_PBN                                      0xBB6F
#define PBB_80_HDCP_AES_CIPHER_KEY_15                               0xBB80
#define PBB_81_HDCP_AES_CIPHER_KEY_14                               0xBB81
#define PBB_82_HDCP_AES_CIPHER_KEY_13                               0xBB82
#define PBB_83_HDCP_AES_CIPHER_KEY_12                               0xBB83
#define PBB_84_HDCP_AES_CIPHER_KEY_11                               0xBB84
#define PBB_85_HDCP_AES_CIPHER_KEY_10                               0xBB85
#define PBB_86_HDCP_AES_CIPHER_KEY_9                                0xBB86
#define PBB_87_HDCP_AES_CIPHER_KEY_8                                0xBB87
#define PBB_88_HDCP_AES_CIPHER_KEY_7                                0xBB88
#define PBB_89_HDCP_AES_CIPHER_KEY_6                                0xBB89
#define PBB_8A_HDCP_AES_CIPHER_KEY_5                                0xBB8A
#define PBB_8B_HDCP_AES_CIPHER_KEY_4                                0xBB8B
#define PBB_8C_HDCP_AES_CIPHER_KEY_3                                0xBB8C
#define PBB_8D_HDCP_AES_CIPHER_KEY_2                                0xBB8D
#define PBB_8E_HDCP_AES_CIPHER_KEY_1                                0xBB8E
#define PBB_8F_HDCP_AES_CIPHER_KEY_0                                0xBB8F
#define PBB_90_HDCP22_CTRL                                          0xBB90
#define PBB_91_HDCP22_TYPE_AES_0                                    0xBB91
#define PBB_92_HDCP22_TYPE_AES_1                                    0xBB92
#define PBB_9A_DUMMY_1                                              0xBB9A
#define PBB_9B_DUMMY_2                                              0xBB9B
#define PBB_9C_DUMMY_3                                              0xBB9C


//--------------------------------------------------
// DisplayPort Tx HPD Detection (Page BB)
//--------------------------------------------------
#define PBB_70_HPD_CTRL                                             0xBB70
#define PBB_71_HPD_IRQ                                              0xBB71
#define PBB_72_HPD_IRQ_EN                                           0xBB72
#define PBB_73_HPD_TIMER1                                           0xBB73
#define PBB_74_HPD_TIMER2                                           0xBB74
#define PBB_75_HPD_TIMER3                                           0xBB75
#define PBB_76_HPD_TIMER4                                           0xBB76
#define PBB_77_HPD_TIMER5                                           0xBB77
#define PBB_78_HPD_TIMER6                                           0xBB78
#define PBB_79_HPD_TIMER7                                           0xBB79
#define PBB_7A_HPD_LONG0                                            0xBB7A
#define PBB_7B_HPD_LONG1                                            0xBB7B
#define PBB_7C_HPD_STATE                                            0xBB7C
#define PBB_7D_RESERVED_0                                           0xBB7D
#define PBB_7E_RESERVED_1                                           0xBB7E


//--------------------------------------------------
// DisplayPort Tx MAC CTRL0 (Page BB)
//--------------------------------------------------
#define PBB_A0_DP_MAC_CTRL                                          0xBBA0
#define PBB_A1_DP_RESET_CTRL                                        0xBBA1
#define PBB_A2_DP_DEBUG_CTRL                                        0xBBA2
#define PBB_A3_DPTX_IRQ_CTRL                                        0xBBA3
#define PBB_A4_PG_FIFO_CTRL                                         0xBBA4
#define PBB_A5_MAX_WL                                               0xBBA5
#define PBB_A6_LFIFO_WL                                             0xBBA6
#define PBB_A7_PG_INTERRUPT_CTRL                                    0xBBA7
#define PBB_A8_MN_VID_AUTO_EN_1                                     0xBBA8
#define PBB_A9_MN_M_VID_H                                           0xBBA9
#define PBB_AA_MN_M_VID_M                                           0xBBAA
#define PBB_AB_MN_M_VID_L                                           0xBBAB
#define PBB_AC_MN_N_VID_H                                           0xBBAC
#define PBB_AD_MN_N_VID_M                                           0xBBAD
#define PBB_AE_MN_N_VID_L                                           0xBBAE
#define PBB_AF_MVID_AUTO_H                                          0xBBAF
#define PBB_B0_MVID_AUTO_M                                          0xBBB0
#define PBB_B1_MVID_AUTO_L                                          0xBBB1
#define PBB_B2_NVID_ASYNC_M                                         0xBBB2
#define PBB_B3_NVID_ASYNC_L                                         0xBBB3
#define PBB_B4_MSA_CTRL                                             0xBBB4
#define PBB_B5_MSA_MISC0                                            0xBBB5
#define PBB_B6_MN_STRM_ATTR_MISC1                                   0xBBB6
#define PBB_B7_MN_STRM_ATTR_HTT_M                                   0xBBB7
#define PBB_B8_MN_STRM_ATTR_HTT_L                                   0xBBB8
#define PBB_B9_MN_STRM_ATTR_HST_M                                   0xBBB9
#define PBB_BA_MN_STRM_ATTR_HST_L                                   0xBBBA
#define PBB_BB_MN_STRM_ATTR_HWD_M                                   0xBBBB
#define PBB_BC_MN_STRM_ATTR_HWD_L                                   0xBBBC
#define PBB_BD_MN_STRM_ATTR_HSW_M                                   0xBBBD
#define PBB_BE_MN_STRM_ATTR_HSW_L                                   0xBBBE
#define PBB_BF_MN_STRM_ATTR_VTTE_M                                  0xBBBF
#define PBB_C0_MN_STRM_ATTR_VTTE_L                                  0xBBC0
#define PBB_C1_MN_STRM_ATTR_VST_M                                   0xBBC1
#define PBB_C2_MN_STRM_ATTR_VST_L                                   0xBBC2
#define PBB_C3_MN_STRM_ATTR_VHT_M                                   0xBBC3
#define PBB_C4_MN_STRM_ATTR_VHT_L                                   0xBBC4
#define PBB_C5_MN_STRM_ATTR_VSW_M                                   0xBBC5
#define PBB_C6_MN_STRM_ATTR_VSW_L                                   0xBBC6
#define PBB_C7_VBID                                                 0xBBC7
#define PBB_C8_VBID_FW_CTL                                          0xBBC8
#define PBB_C9_ARBITER_CTRL                                         0xBBC9
#define PBB_CA_V_DATA_PER_LINE0                                     0xBBCA
#define PBB_CB_V_DATA_PER_LINE1                                     0xBBCB
#define PBB_CC_TU_SIZE                                              0xBBCC
#define PBB_CD_TU_DATA_SIZE0                                        0xBBCD
#define PBB_CE_TU_DATA_SIZE1                                        0xBBCE
#define PBB_CF_HDEALY0                                              0xBBCF
#define PBB_D0_HDEALY1                                              0xBBD0
#define PBB_D1_AUTO_HDEALY0                                         0xBBD1
#define PBB_D2_AUTO_HDEALY1                                         0xBBD2
#define PBB_D3_LFIFO_WL_SET                                         0xBBD3
#define PBB_D4_ARBITER_SEC_END_CNT_HB                               0xBBD4
#define PBB_D5_ARBITER_SEC_END_CNT_LB                               0xBBD5
#define PBB_D6_ARBITER_DEBUG                                        0xBBD6
#define PBB_D7_DPTX_CTSFIFO_CTRL                                    0xBBD7
#define PBB_D8_DPTX_CTSFIFO_RSV1                                    0xBBD8
#define PBB_D9_DPTX_TOP_CTL                                         0xBBD9
#define PBB_DA_DPTX_TOP_RSV1                                        0xBBDA
#define PBB_DB_DPTX_TOP_RSV2                                        0xBBDB
#define PBB_DC_ARBITER_MIN_H_BLANK_WIDTH_HB                         0xBBDC
#define PBB_DD_ARBITER_MIN_H_BLANK_WIDTH_LB                         0xBBDD
#define PBB_DE_ARBITER_INTERRUPT_CTRL                               0xBBDE
#define PBB_DF_VESA_FMT_REGEN                                       0xBBDF
#define PBB_E0_DPTX_CLK_GEN                                         0xBBE0
#define PBB_E1_PG_MBIST_CTRL                                        0xBBE1
#define PBB_E2_PG_DRF_MBIST_CTRL                                    0xBBE2
#define PBB_F0_ARBITER_SEC_IDLE_END_CNT                             0xBBF0
#define PBB_F8_DPTX_TOP_RSV3                                        0xBBF8
#define PBB_F9_DPTX_TOP_RSV4                                        0xBBF9
#define PBB_FA_DPTX_TOP_RSV5                                        0xBBFA
#define PBB_FB_DPTX_TOP_RSV6                                        0xBBFB
#define PBB_FC_DPTX_TOP_RSV7                                        0xBBFC
#define PBB_FD_DPTX_TOP_RSV8                                        0xBBFD
#define PBB_FE_DPTX_TOP_RSV9                                        0xBBFE
#define PBB_FF_DPTX_TOP_RSV10                                       0xBBFF


//--------------------------------------------------
// DisplayPort Tx MAC CTRL1 (Page BC)
//--------------------------------------------------
#define PBC_00_SEC_FUNCTION_CTRL                                    0xBC00
#define PBC_01_SEC_RESERVED_0                                       0xBC01
#define PBC_02_SEC_DBUF_CTRL                                        0xBC02
#define PBC_03_SEC_DEBUG                                            0xBC03
#define PBC_04_SEC_PSR_DB0                                          0xBC04
#define PBC_05_SEC_PSR_DB1                                          0xBC05
#define PBC_06_SEC_PSR_DB2                                          0xBC06
#define PBC_07_SEC_PSR_DB3                                          0xBC07
#define PBC_08_SEC_PSR_DB4                                          0xBC08
#define PBC_09_SEC_PSR_DB5                                          0xBC09
#define PBC_0A_SEC_PSR_DB6                                          0xBC0A
#define PBC_0B_SEC_PSR_DB7                                          0xBC0B
#define PBC_0C_SEC_PSR_DB8                                          0xBC0C
#define PBC_0D_SEC_PSR_DB9                                          0xBC0D
#define PBC_0E_SEC_PSR_DB10                                         0xBC0E
#define PBC_0F_SEC_PSR_DB11                                         0xBC0F
#define PBC_10_SEC_PSR_DB12                                         0xBC10
#define PBC_11_SEC_PSR_DB13                                         0xBC11
#define PBC_12_SEC_PSR_DB14                                         0xBC12
#define PBC_13_SEC_PSR_DB15                                         0xBC13
#define PBC_14_SEC_RESERVED_1                                       0xBC14
#define PBC_15_SEC_RESERVED_2                                       0xBC15
#define PBC_16_SEC_RESERVED_3                                       0xBC16
#define PBC_17_SEC_RESERVED_4                                       0xBC17
#define PBC_18_AUD_FUNCTION_CTRL1                                   0xBC18
#define PBC_19_AUD_PAYLOAD_B3                                       0xBC19
#define PBC_1A_DP_AUD_ID                                            0xBC1A
#define PBC_1B_SEC_RESERVED_6                                       0xBC1B
#define PBC_1C_AUD_FIFO_CTRL                                        0xBC1C
#define PBC_1D_AUD_LFIFO_MAX_WL                                     0xBC1D
#define PBC_1E_AUD_LFIFO_WL                                         0xBC1E
#define PBC_1F_AUD_INTERRUPT_CTRL                                   0xBC1F
#define PBC_20_AUD_TS_MAUD_H                                        0xBC20
#define PBC_21_AUD_TS_MAUD_M                                        0xBC21
#define PBC_22_AUD_TS_MAUD_L                                        0xBC22
#define PBC_23_AUD_TS_NAUD_H                                        0xBC23
#define PBC_24_AUD_TS_NAUD_M                                        0xBC24
#define PBC_25_AUD_TS_NAUD_L                                        0xBC25
#define PBC_26_SEC_INFO_AUD_DB0                                     0xBC26
#define PBC_27_SEC_INFO_AUD_DB1                                     0xBC27
#define PBC_28_SEC_INFO_AUD_DB2                                     0xBC28
#define PBC_29_SEC_INFO_AUD_DB3                                     0xBC29
#define PBC_2A_SEC_INFO_AUD_DB4                                     0xBC2A
#define PBC_2B_SEC_INFO_AUD_DB5                                     0xBC2B
#define PBC_2C_SEC_INFO_AUD_DB6                                     0xBC2C
#define PBC_2D_SEC_INFO_AUD_DB7                                     0xBC2D
#define PBC_2E_SEC_INFO_AUD_DB8                                     0xBC2E
#define PBC_2F_SEC_INFO_AUD_DB9                                     0xBC2F
#define PBC_30_SEC_INFO_AVI_DB0                                     0xBC30
#define PBC_31_SEC_INFO_AVI_DB1                                     0xBC31
#define PBC_32_SEC_INFO_AVI_DB2                                     0xBC32
#define PBC_33_SEC_INFO_AVI_DB3                                     0xBC33
#define PBC_34_SEC_INFO_AVI_DB4                                     0xBC34
#define PBC_35_SEC_INFO_AVI_DB5                                     0xBC35
#define PBC_36_SEC_INFO_AVI_DB6                                     0xBC36
#define PBC_37_SEC_INFO_AVI_DB7                                     0xBC37
#define PBC_38_SEC_INFO_AVI_DB8                                     0xBC38
#define PBC_39_SEC_INFO_AVI_DB9                                     0xBC39
#define PBC_3A_SEC_INFO_AVI_DB10                                    0xBC3A
#define PBC_3B_SEC_INFO_AVI_DB11                                    0xBC3B
#define PBC_3C_SEC_INFO_AVI_DB12                                    0xBC3C
#define PBC_3D_SEC_INFO_MPEG_DB0                                    0xBC3D
#define PBC_3E_SEC_INFO_MPEG_DB1                                    0xBC3E
#define PBC_3F_SEC_INFO_MPEG_DB2                                    0xBC3F
#define PBC_40_SEC_INFO_MPEG_DB3                                    0xBC40
#define PBC_41_SEC_INFO_MPEG_DB4                                    0xBC41
#define PBC_42_SEC_INFO_MPEG_DB5                                    0xBC42
#define PBC_43_SEC_INFO_MPEG_DB6                                    0xBC43
#define PBC_44_SEC_INFO_MPEG_DB7                                    0xBC44
#define PBC_45_SEC_INFO_MPEG_DB8                                    0xBC45
#define PBC_46_SEC_INFO_MPEG_DB9                                    0xBC46
#define PBC_47_AUD_FUNCTION_CTRL2                                   0xBC47
#define PBC_48_AUD_FUNCTION_CTRL3                                   0xBC48
#define PBC_49_MST_SEC_PKT_ID                                       0xBC49
#define PBC_4A_MST_SEC_PKT_HB3                                      0xBC4A
#define PBC_4B_SEC_RS_DECODE_CTRL                                   0xBC4B
#define PBC_4C_SEC_AUD_FREQDET_CTRL                                 0xBC4C
#define PBC_4D_SEC_AUD_XCLK_DIV                                     0xBC4D
#define PBC_4E_SEC_AUD_FREQ_TIME                                    0xBC4E
#define PBC_4F_SEC_AUD_SAMPLE_CNT_HB                                0xBC4F
#define PBC_50_SEC_AUD_SAMPLE_CNT_LB                                0xBC50
#define PBC_51_AUD_MBIST_CTRL                                       0xBC51
#define PBC_52_AUD_DRF_MBIST_CTRL                                   0xBC52
#define PBC_53_DP_INFO_FM_RSV0                                      0xBC53
#define PBC_54_DP_INFO_FM_RSV1                                      0xBC54
#define PBC_55_DP_INFO_FM_ADR                                       0xBC55
#define PBC_56_DP_INFO_FM_DAT                                       0xBC56
#define PBC_57_RESERVED_57                                          0xBC57
#define PBC_58_VSC_RX_DB0                                           0xBC58
#define PBC_59_VSC_RX_DB1                                           0xBC59
#define PBC_5A_VSC_RX_DB2                                           0xBC5A
#define PBC_5B_VSC_RX_DB3                                           0xBC5B
#define PBC_5C_VSC_RX_DB4                                           0xBC5C
#define PBC_5D_VSC_RX_DB5                                           0xBC5D
#define PBC_5E_VSC_RX_DB6                                           0xBC5E
#define PBC_5F_VSC_RX_DB7                                           0xBC5F
#define PBC_60_AUD_FREQ_TH_0                                        0xBC60
#define PBC_61_AUD_FREQ_TH_1                                        0xBC61
#define PBC_62_AUD_FREQ_TH_2                                        0xBC62
#define PBC_63_AUD_FREQ_TH_3                                        0xBC63
#define PBC_64_AUD_FREQ_TH_4                                        0xBC64
#define PBC_65_AUD_FREQ_TH_5                                        0xBC65
#define PBC_66_AUD_FREQ_TH_6                                        0xBC66
#define PBC_67_RESERVED_67                                          0xBC67
#define PBC_68_RESERVED_68                                          0xBC68
#define PBC_69_RESERVED_69                                          0xBC69
#define PBC_6A_VSC_CTRL_0                                           0xBC6A
#define PBC_6B_VSC_RX_HB0                                           0xBC6B
#define PBC_6C_VSC_RX_HB1                                           0xBC6C
#define PBC_6D_VSC_RX_HB2                                           0xBC6D
#define PBC_6E_VSC_RX_HB3                                           0xBC6E
#define PBC_70_SEC_AWD_CTRL                                         0xBC70
#define PBC_71_SEC_AWD_STATUS_0                                     0xBC71
#define PBC_72_SEC_IRQ_CTRL0                                        0xBC72
#define PBC_73_SEC_PH_HB0                                           0xBC73
#define PBC_74_SEC_PH_HB1                                           0xBC74
#define PBC_75_SEC_PH_HB2                                           0xBC75
#define PBC_76_SEC_PH_HB3                                           0xBC76
#define PBC_77_SEC_PH_PB0                                           0xBC77
#define PBC_78_SEC_PH_PB1                                           0xBC78
#define PBC_79_SEC_PH_PB2                                           0xBC79
#define PBC_7A_SEC_PH_PB3                                           0xBC7A
#define PBC_7B_SEC_PH_PACKET_TYPE                                   0xBC7B
#define PBC_80_SEC_AWD_STATUS_1                                     0xBC80
#define PBC_81_DP_INFO_VAR_EN_M                                     0xBC81
#define PBC_82_DP_INFO_VAR_EN_L                                     0xBC82
#define PBC_83_DP_INFO_VAR_ST_M                                     0xBC83
#define PBC_84_DP_INFO_VAR_ST_L                                     0xBC84
#define PBC_85_CH_STATUS_0                                          0xBC85
#define PBC_86_CH_STATUS_1                                          0xBC86
#define PBC_87_CH_STATUS_2                                          0xBC87
#define PBC_88_CH_STATUS_3                                          0xBC88
#define PBC_89_CH_STATUS_4                                          0xBC89
#define PBC_8A_DP_AVWD_CTRL0                                        0xBC8A
#define PBC_8B_RESERVED_8B                                          0xBC8B
#define PBC_8C_RESERVED_8C                                          0xBC8C
#define PBC_8D_RESERVED_8D                                          0xBC8D
#define PBC_8E_RESERVED_8E                                          0xBC8E
#define PBC_8F_DPTX_I2S_CTRL                                        0xBC8F
#define PBC_90_SEC_IRQ_CTRL1                                        0xBC90
#define PBC_95_DUMMY_95                                             0xBC95
#define PBC_96_DUMMY_96                                             0xBC96
#define PBC_97_DUMMY_97                                             0xBC97
#define PBC_98_DUMMY_98                                             0xBC98
#define PBC_99_DUMMY_99                                             0xBC99
#define PBC_9A_DUMMY_9A                                             0xBC9A
#define PBC_9B_DUMMY_9B                                             0xBC9B
#define PBC_9C_DUMMY_9C                                             0xBC9C


//--------------------------------------------------
// DisplayPort Tx Analog PHY CTRL (Page BC)
//--------------------------------------------------
#define PBC_A0_DPTX_PHY_CTRL0                                       0xBCA0
#define PBC_A1_DPTX_PHY_CTRL1                                       0xBCA1
#define PBC_A2_DPTX_RCV_DET0                                        0xBCA2
#define PBC_A3_DPTX_RCV_DET1                                        0xBCA3
#define PBC_A4_DPTX_PN_SWAP                                         0xBCA4
#define PBC_A7_DPTX_SFIFO_CTRL0                                     0xBCA7
#define PBC_A8_DPTX_SFIFO_CTRL1                                     0xBCA8
#define PBC_A9_DPTX_SFIFO_LANE_SWAP0                                0xBCA9
#define PBC_AA_DPTX_SFIFO_LANE_SWAP1                                0xBCAA
#define PBC_AB_DPTX_SFIFO_INT_EN                                    0xBCAB
#define PBC_B0_DPTX_DEEMP_EN_LANE3_0H                               0xBCB0
#define PBC_B1_DPTX_DEEMP_EN_LANE3L                                 0xBCB1
#define PBC_B2_DPTX_DEEMP_EN_LANE2L                                 0xBCB2
#define PBC_B3_DPTX_DEEMP_EN_LANE1L                                 0xBCB3
#define PBC_B4_DPTX_DEEMP_EN_LANE0L                                 0xBCB4
#define PBC_B5_DPTX_DLY_LANE3_0                                     0xBCB5
#define PBC_B6_DPTX_DRV_DAC_DAT_LANE3_2                             0xBCB6
#define PBC_B7_DPTX_DRV_DAC_DAT_LANE1_0                             0xBCB7
#define PBC_B8_DPTX_DRV_DAC_POST0_LANE3_2                           0xBCB8
#define PBC_B9_DPTX_DRV_DAC_POST0_LANE1_0                           0xBCB9
#define PBC_BA_DPTX_DRV_DAC_POST1_LANE3_2                           0xBCBA
#define PBC_BB_DPTX_DRV_DAC_POST1_LANE1_0                           0xBCBB
#define PBC_BC_DPTX_RCVDET_BIAS_PULLDN                              0xBCBC
#define PBC_BD_DPTX_CKRDDUTY_SPD_SEL                                0xBCBD
#define PBC_BE_DPTX_VCM_CTRL_LANE3_2                                0xBCBE
#define PBC_BF_DPTX_VCM_CTRL_LANE1_0                                0xBCBF
#define PBC_C0_DPTX_VREF_CTRL_LANE3_2                               0xBCC0
#define PBC_C1_DPTX_VREF_CTRL_LANE1_0                               0xBCC1
#define PBC_C2_DPTX_Z0_LANE3_2                                      0xBCC2
#define PBC_C3_DPTX_Z0_LANE1_0                                      0xBCC3
#define PBC_D0_DPTX_CMU0                                            0xBCD0
#define PBC_D1_DPTX_CMU1                                            0xBCD1
#define PBC_D2_DPTX_CMU2                                            0xBCD2
#define PBC_D3_DPTX_CMU3                                            0xBCD3
#define PBC_D4_DPTX_CMU4                                            0xBCD4
#define PBC_D5_DPTX_CMU5                                            0xBCD5
#define PBC_D6_DPTX_CMU6                                            0xBCD6
#define PBC_D7_DPTX_CMU7                                            0xBCD7
#define PBC_D8_DPTX_CMU8                                            0xBCD8
#define PBC_D9_DPTX_CMU9                                            0xBCD9
#define PBC_DA_DPTX_CMU10                                           0xBCDA
#define PBC_DB_DPTX_CMU11                                           0xBCDB
#define PBC_DD_DPTX_CMU12                                           0xBCDD
#define PBC_DE_DPTX_CMU13                                           0xBCDE
#define PBC_DF_DPTX_CMU14                                           0xBCDF
#define PBC_E0_DPTX_CMU15                                           0xBCE0
#define PBC_E1_DPTX_CMU16                                           0xBCE1
#define PBC_E2_DPTX_CMU17                                           0xBCE2
#define PBC_E3_DPTX_CMU18                                           0xBCE3
#define PBC_E4_DPTX_CMU19                                           0xBCE4
#define PBC_E5_DPTX_CMU20                                           0xBCE5
#define PBC_E6_DPTX_CMU21                                           0xBCE6
#define PBC_E7_DPTX_CMU22                                           0xBCE7


//--------------------------------------------------
// DisplayPort Tx AUX Analog PHY CTRL (Page BD)
//--------------------------------------------------
#define PBD_60_DIG_TX_04                                            0xBD60
#define PBD_61_AUX_1                                                0xBD61
#define PBD_62_AUX_2                                                0xBD62
#define PBD_63_AUX_3                                                0xBD63
#define PBD_64_AUX_4                                                0xBD64
#define PBD_65_AUX_5                                                0xBD65
#define PBD_66_AUX_6                                                0xBD66
#define PBD_67_DIG_TX_03                                            0xBD67


//--------------------------------------------------
// DisplayPort Tx AUX MAC CTRL (Page BD)
//--------------------------------------------------
#define PBD_A0_AUX_TX_CTRL                                          0xBDA0
#define PBD_A1_AUX_TIMEOUT                                          0xBDA1
#define PBD_A2_AUX_FSM_STATUS                                       0xBDA2
#define PBD_A3_AUXTX_TRAN_CTRL                                      0xBDA3
#define PBD_A4_AUXTX_REQ_CMD                                        0xBDA4
#define PBD_A5_AUXTX_REQ_ADDR_M                                     0xBDA5
#define PBD_A6_AUXTX_REQ_ADDR_L                                     0xBDA6
#define PBD_A7_AUXTX_REQ_LEN                                        0xBDA7
#define PBD_A8_AUXTX_REQ_DATA                                       0xBDA8
#define PBD_A9_AUX_REPLY_CMD                                        0xBDA9
#define PBD_AA_AUX_REPLY_DATA                                       0xBDAA
#define PBD_AB_AUX_FIFO_CTRL                                        0xBDAB
#define PBD_AC_AUX_TX_FIFO_STATUS                                   0xBDAC
#define PBD_AD_AUX_FIFO_RD_PTR                                      0xBDAD
#define PBD_AE_AUX_FIFO_WR_PTR                                      0xBDAE
#define PBD_AF_AUX_RETRY_1                                          0xBDAF
#define PBD_B0_AUX_RETRY_2                                          0xBDB0
#define PBD_B1_AUX_IRQ_EVENT                                        0xBDB1
#define PBD_B2_AUX_IRQ_EN                                           0xBDB2
#define PBD_F0_AUX_DIG_PHY2                                         0xBDF0
#define PBD_F1_AUX_DIG_PHY3                                         0xBDF1
#define PBD_F2_AUX_DIG_PHY4                                         0xBDF2
#define PBD_F3_AUX_DIG_PHY5                                         0xBDF3
#define PBD_F4_AUX_DIG_PHY6                                         0xBDF4
#define PBD_F5_AUX_DIG_PHY7                                         0xBDF5
#define PBD_F6_AUX_DIG_PHY8                                         0xBDF6
#define PBD_F7_AUX_DIG_PHY9                                         0xBDF7
#define PBD_F8_AUX_DEBUG                                            0xBDF8


//--------------------------------------------------
// DisplayPort Tx AUX MSG Write CTRL (Page BD)
//--------------------------------------------------
#define PBD_B5_MSG_WR_CTRL                                          0xBDB5
#define PBD_B6_MSG_WR_FINISH                                        0xBDB6
#define PBD_B7_MSG_WR_LENGTH                                        0xBDB7
#define PBD_B8_MSG_WR_BUR_LENGTH                                    0xBDB8
#define PBD_B9_MSG_WR_SET0                                          0xBDB9
#define PBD_BA_MSG_WR_SET1                                          0xBDBA
#define PBD_BB_MSG_WR_SET2                                          0xBDBB
#define PBD_BC_MSG_WR_SET3                                          0xBDBC
#define PBD_BD_MSG_WR_SET4                                          0xBDBD
#define PBD_BE_MSG_WR_SET5                                          0xBDBE
#define PBD_BF_MSG_WR_SET6                                          0xBDBF
#define PBD_C0_MSG_WR_SET7                                          0xBDC0
#define PBD_C1_MSG_WR_SET8                                          0xBDC1
#define PBD_C2_MSG_WR_SET9                                          0xBDC2
#define PBD_C3_MSG_WR_ADR_SEL                                       0xBDC3
#define PBD_C4_BUF_RDPTR                                            0xBDC4
#define PBD_C5_BUF_CLR                                              0xBDC5
#define PBD_C6_BUF_FW_WRPTR                                         0xBDC6
#define PBD_C7_BUF_FW_WR_DATA                                       0xBDC7
#define PBD_C8_MSG_DUMMY_0                                          0xBDC8
#define PBD_C9_MSG_DUMMY_1                                          0xBDC9


//--------------------------------------------------
// DisplayPort Tx AUX MSG Read CTRL (Page BD)
//--------------------------------------------------
#define PBD_CA_AUX_TX_MSG_RD_CTRL                                   0xBDCA
#define PBD_CB_MSG_RD_FINISH_IRQ                                    0xBDCB
#define PBD_CC_MSG_RD_FINISH                                        0xBDCC
#define PBD_CD_MSG_RD_LENGTH                                        0xBDCD
#define PBD_CE_MSG_RD_BUR_LENGTH                                    0xBDCE
#define PBD_CF_MSG_RD_DATA0                                         0xBDCF
#define PBD_D0_MSG_RD_DATA1                                         0xBDD0
#define PBD_D1_MSG_RD_DATA2                                         0xBDD1
#define PBD_D2_MSG_RD_DATA3                                         0xBDD2
#define PBD_D3_MSG_RD_DATA4                                         0xBDD3
#define PBD_D4_MSG_RD_DATA5                                         0xBDD4
#define PBD_D5_MSG_RD_DATA6                                         0xBDD5
#define PBD_D6_MSG_RD_DATA7                                         0xBDD6
#define PBD_D7_MSG_RD_DATA8                                         0xBDD7
#define PBD_D8_MSG_RD_DATA9                                         0xBDD8
#define PBD_D9_MSG_RD_DATAA                                         0xBDD9
#define PBD_DA_MSG_RD_ADR_SEL                                       0xBDDA
#define PBD_DB_MSG_RD_FLAG                                          0xBDDB
#define PBD_DC_MSG_BUF_RDPTR                                        0xBDDC
#define PBD_DD_MSG_BUF_RD_DATA                                      0xBDDD
#define PBD_DE_MSG_BUF_CLR                                          0xBDDE
#define PBD_DF_BUF_FW_WRPTR                                         0xBDDF
#define PBD_E0_MSG_SRAM_BIST_CTRL                                   0xBDE0
#define PBD_E1_MSG_SRAM_DRF_BIST_CTRL                               0xBDE1


//--------------------------------------------------
// AUDIO ADC PLL (Page BF)
//--------------------------------------------------
#define PBF_A0_MN_SCLKG_CTRL                                        0xBFA0
#define PBF_A1_MN_SCLKG_DIVM                                        0xBFA1
#define PBF_A2_MN_SCLKG_DIVN                                        0xBFA2
#define PBF_A3_MN_SCLKG_DIVS                                        0xBFA3
#define PBF_A4_MN_SCLKG_OFFS_H                                      0xBFA4
#define PBF_A5_MN_SCLKG_OFFS_M                                      0xBFA5
#define PBF_A6_MN_SCLKG_OFFS_L                                      0xBFA6
#define PBF_A7_MN_SCLKG_TRK_CTRL                                    0xBFA7
#define PBF_B8_MN_SCLKG_SDM_CTRL                                    0xBFB8
#define PBF_B9_MN_SCLKG_SDM_TEST                                    0xBFB9
#define PBF_BA_MN_SCLKG_SDM_SUMC_H                                  0xBFBA
#define PBF_BB_MN_SCLKG_SDM_SUMC_M                                  0xBFBB
#define PBF_BC_MN_SCLKG_SDM_SUMC_L                                  0xBFBC
#define PBF_BD_MN_SCLKG_PLL_PWR                                     0xBFBD
#define PBF_BE_MN_SCLKG_PLL_CHP                                     0xBFBE
#define PBF_BF_MN_SCLKG_PLL_WD                                      0xBFBF
#define PBF_C0_MN_SCLKG_PLL_INSEL                                   0xBFC0
#define PBF_C1_MN_SCLKG_PLL_RESERVE                                 0xBFC1
#define PBF_C2_DUMMY_0                                              0xBFC2
#define PBF_C3_DUMMY_1                                              0xBFC3
#define PBF_C4_DUMMY_2                                              0xBFC4
#define PBF_C5_DUMMY_3                                              0xBFC5


//--------------------------------------------------
// GroupB Power Control (Page C0)
//--------------------------------------------------
#define PC0_0A_GB_POWER_CTRL                                        0xC00A


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
