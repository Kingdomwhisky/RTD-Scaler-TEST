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
// ID Code      : RL6492_Series_Common_RegCommonInclude.h No.0000
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
#define _P0_8E_PT_31_TEST_SIGNAL_SHIFT                              0x31


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
#define _P0_92_PT_161_WIN8_ADR5_LSB                                 0x1610
#define _P0_92_PT_161_WIN8_ADR5_MSB                                 0x1611
#define _P0_92_PT_161_WIN8_ADR5_HSB                                 0x1612
#define _P0_92_PT_162_WIN9_ADR4_LSB                                 0x1620
#define _P0_92_PT_162_WIN9_ADR4_MSB                                 0x1621
#define _P0_92_PT_162_WIN9_ADR4_HSB                                 0x1622
#define _P0_92_PT_163_WIN9_ADR5_LSB                                 0x1630
#define _P0_92_PT_163_WIN9_ADR5_MSB                                 0x1631
#define _P0_92_PT_163_WIN9_ADR5_HSB                                 0x1632
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
#define _P0_92_PT_174_WIN0_ADR6_LSB                                 0x1740
#define _P0_92_PT_174_WIN0_ADR6_MSB                                 0x1741
#define _P0_92_PT_174_WIN0_ADR6_HSB                                 0x1742
#define _P0_92_PT_176_WIN0_ADR8_LSB                                 0x1760
#define _P0_92_PT_176_WIN0_ADR8_MSB                                 0x1761
#define _P0_92_PT_176_WIN0_ADR8_HSB                                 0x1762
#define _P0_92_PT_177_WIN0_ADR9_LSB                                 0x1770
#define _P0_92_PT_177_WIN0_ADR9_MSB                                 0x1771
#define _P0_92_PT_177_WIN0_ADR9_HSB                                 0x1772
#define _P0_92_PT_178_WIN0_ADR10_LSB                                0x1780
#define _P0_92_PT_178_WIN0_ADR10_MSB                                0x1781
#define _P0_92_PT_178_WIN0_ADR10_HSB                                0x1782
#define _P0_92_PT_17E_WIN1_ADR9_LSB                                 0x17E0
#define _P0_92_PT_17E_WIN1_ADR9_MSB                                 0x17E1
#define _P0_92_PT_17E_WIN1_ADR9_HSB                                 0x17E2
#define _P0_92_PT_183_WIN2_ADR7_LSB                                 0x1830
#define _P0_92_PT_183_WIN2_ADR7_MSB                                 0x1831
#define _P0_92_PT_183_WIN2_ADR7_HSB                                 0x1832
#define _P0_92_PT_184_WIN2_ADR8_LSB                                 0x1840
#define _P0_92_PT_184_WIN2_ADR8_MSB                                 0x1841
#define _P0_92_PT_184_WIN2_ADR8_HSB                                 0x1842
#define _P0_92_PT_185_WIN2_ADR9_LSB                                 0x1850
#define _P0_92_PT_185_WIN2_ADR9_MSB                                 0x1851
#define _P0_92_PT_185_WIN2_ADR9_HSB                                 0x1852
#define _P0_92_PT_18A_WIN3_ADR7_LSB                                 0x18A0
#define _P0_92_PT_18A_WIN3_ADR7_MSB                                 0x18A1
#define _P0_92_PT_18A_WIN3_ADR7_HSB                                 0x18A2
#define _P0_92_PT_18B_WIN3_ADR8_LSB                                 0x18B0
#define _P0_92_PT_18B_WIN3_ADR8_MSB                                 0x18B1
#define _P0_92_PT_18B_WIN3_ADR8_HSB                                 0x18B2
#define _P0_92_PT_18C_WIN3_ADR9_LSB                                 0x18C0
#define _P0_92_PT_18C_WIN3_ADR9_MSB                                 0x18C1
#define _P0_92_PT_18C_WIN3_ADR9_HSB                                 0x18C2
#define _P0_92_PT_191_WIN4_ADR7_LSB                                 0x1910
#define _P0_92_PT_191_WIN4_ADR7_MSB                                 0x1911
#define _P0_92_PT_191_WIN4_ADR7_HSB                                 0x1912
#define _P0_92_PT_192_WIN4_ADR8_LSB                                 0x1920
#define _P0_92_PT_192_WIN4_ADR8_MSB                                 0x1921
#define _P0_92_PT_192_WIN4_ADR8_HSB                                 0x1922
#define _P0_92_PT_193_WIN4_ADR9_LSB                                 0x1930
#define _P0_92_PT_193_WIN4_ADR9_MSB                                 0x1931
#define _P0_92_PT_193_WIN4_ADR9_HSB                                 0x1932
#define _P0_92_PT_197_WIN5_ADR6_LSB                                 0x1970
#define _P0_92_PT_197_WIN5_ADR6_MSB                                 0x1971
#define _P0_92_PT_197_WIN5_ADR6_HSB                                 0x1972
#define _P0_92_PT_199_WIN5_ADR8_LSB                                 0x1990
#define _P0_92_PT_199_WIN5_ADR8_MSB                                 0x1991
#define _P0_92_PT_199_WIN5_ADR8_HSB                                 0x1992
#define _P0_92_PT_19A_WIN5_ADR9_LSB                                 0x19A0
#define _P0_92_PT_19A_WIN5_ADR9_MSB                                 0x19A1
#define _P0_92_PT_19A_WIN5_ADR9_HSB                                 0x19A2
#define _P0_92_PT_19B_WIN5_ADR10_LSB                                0x19B0
#define _P0_92_PT_19B_WIN5_ADR10_MSB                                0x19B1
#define _P0_92_PT_19B_WIN5_ADR10_HSB                                0x19B2
#define _P0_92_PT_19E_WIN6_ADR6_LSB                                 0x19E0
#define _P0_92_PT_19E_WIN6_ADR6_MSB                                 0x19E1
#define _P0_92_PT_19E_WIN6_ADR6_HSB                                 0x19E2
#define _P0_92_PT_1A0_WIN6_ADR8_LSB                                 0x1A00
#define _P0_92_PT_1A0_WIN6_ADR8_MSB                                 0x1A01
#define _P0_92_PT_1A0_WIN6_ADR8_HSB                                 0x1A02
#define _P0_92_PT_1A1_WIN6_ADR9_LSB                                 0x1A10
#define _P0_92_PT_1A1_WIN6_ADR9_MSB                                 0x1A11
#define _P0_92_PT_1A1_WIN6_ADR9_HSB                                 0x1A12
#define _P0_92_PT_1A5_WIN7_ADR6_LSB                                 0x1A50
#define _P0_92_PT_1A5_WIN7_ADR6_MSB                                 0x1A51
#define _P0_92_PT_1A5_WIN7_ADR6_HSB                                 0x1A52
#define _P0_92_PT_1A7_WIN7_ADR8_LSB                                 0x1A70
#define _P0_92_PT_1A7_WIN7_ADR8_MSB                                 0x1A71
#define _P0_92_PT_1A7_WIN7_ADR8_HSB                                 0x1A72
#define _P0_92_PT_1A8_WIN7_ADR9_LSB                                 0x1A80
#define _P0_92_PT_1A8_WIN7_ADR9_MSB                                 0x1A81
#define _P0_92_PT_1A8_WIN7_ADR9_HSB                                 0x1A82
#define _P0_92_PT_1AC_WIN8_ADR6_LSB                                 0x1AC0
#define _P0_92_PT_1AC_WIN8_ADR6_MSB                                 0x1AC1
#define _P0_92_PT_1AC_WIN8_ADR6_HSB                                 0x1AC2
#define _P0_92_PT_1AE_WIN8_ADR8_LSB                                 0x1AE0
#define _P0_92_PT_1AE_WIN8_ADR8_MSB                                 0x1AE1
#define _P0_92_PT_1AE_WIN8_ADR8_HSB                                 0x1AE2
#define _P0_92_PT_1AF_WIN8_ADR9_LSB                                 0x1AF0
#define _P0_92_PT_1AF_WIN8_ADR9_MSB                                 0x1AF1
#define _P0_92_PT_1AF_WIN8_ADR9_HSB                                 0x1AF2
#define _P0_92_PT_1B3_WIN9_ADR6_LSB                                 0x1B30
#define _P0_92_PT_1B3_WIN9_ADR6_MSB                                 0x1B31
#define _P0_92_PT_1B3_WIN9_ADR6_HSB                                 0x1B32
#define _P0_92_PT_1B5_WIN9_ADR8_LSB                                 0x1B50
#define _P0_92_PT_1B5_WIN9_ADR8_MSB                                 0x1B51
#define _P0_92_PT_1B5_WIN9_ADR8_HSB                                 0x1B52
#define _P0_92_PT_1B6_WIN9_ADR9_LSB                                 0x1B60
#define _P0_92_PT_1B6_WIN9_ADR9_MSB                                 0x1B61
#define _P0_92_PT_1B6_WIN9_ADR9_HSB                                 0x1B62
#define _P0_92_PT_1BD_WIN4_1_ADR9_LSB                               0x1BD0
#define _P0_92_PT_1BD_WIN4_1_ADR9_MSB                               0x1BD1
#define _P0_92_PT_1BD_WIN4_1_ADR9_HSB                               0x1BD2
#define _P0_92_PT_1BE_WIN4_1_ADR10_LSB                              0x1BE0
#define _P0_92_PT_1BE_WIN4_1_ADR10_MSB                              0x1BE1
#define _P0_92_PT_1BE_WIN4_1_ADR10_HSB                              0x1BE2
#define _P0_92_PT_1C4_WIN4_2_ADR9_LSB                               0x1C40
#define _P0_92_PT_1C4_WIN4_2_ADR9_MSB                               0x1C41
#define _P0_92_PT_1C4_WIN4_2_ADR9_HSB                               0x1C42
#define _P0_92_PT_1C5_WIN4_2_ADR10_LSB                              0x1C50
#define _P0_92_PT_1C5_WIN4_2_ADR10_MSB                              0x1C51
#define _P0_92_PT_1C5_WIN4_2_ADR10_HSB                              0x1C52
#define _P0_92_PT_1CB_WIN4_3_ADR9_LSB                               0x1CB0
#define _P0_92_PT_1CB_WIN4_3_ADR9_MSB                               0x1CB1
#define _P0_92_PT_1CB_WIN4_3_ADR9_HSB                               0x1CB2
#define _P0_92_PT_1CC_WIN4_3_ADR10_LSB                              0x1CC0
#define _P0_92_PT_1CC_WIN4_3_ADR10_MSB                              0x1CC1
#define _P0_92_PT_1CC_WIN4_3_ADR10_HSB                              0x1CC2
#define _P0_92_PT_1D2_WIN4_4_ADR9_LSB                               0x1D20
#define _P0_92_PT_1D2_WIN4_4_ADR9_MSB                               0x1D21
#define _P0_92_PT_1D2_WIN4_4_ADR9_HSB                               0x1D22
#define _P0_92_PT_1D3_WIN4_4_ADR10_LSB                              0x1D30
#define _P0_92_PT_1D3_WIN4_4_ADR10_MSB                              0x1D31
#define _P0_92_PT_1D3_WIN4_4_ADR10_HSB                              0x1D32
#define _P0_92_PT_1D9_WIN4_5_ADR9_LSB                               0x1D90
#define _P0_92_PT_1D9_WIN4_5_ADR9_MSB                               0x1D91
#define _P0_92_PT_1D9_WIN4_5_ADR9_HSB                               0x1D92
#define _P0_92_PT_1DA_WIN4_5_ADR10_LSB                              0x1DA0
#define _P0_92_PT_1DA_WIN4_5_ADR10_MSB                              0x1DA1
#define _P0_92_PT_1DA_WIN4_5_ADR10_HSB                              0x1DA2
#define _P0_92_PT_1E0_WIN4_6_ADR9_LSB                               0x1E00
#define _P0_92_PT_1E0_WIN4_6_ADR9_MSB                               0x1E01
#define _P0_92_PT_1E0_WIN4_6_ADR9_HSB                               0x1E02
#define _P0_92_PT_1E1_WIN4_6_ADR10_LSB                              0x1E10
#define _P0_92_PT_1E1_WIN4_6_ADR10_MSB                              0x1E11
#define _P0_92_PT_1E1_WIN4_6_ADR10_HSB                              0x1E12
#define _P0_92_PT_1E7_WIN4_7_ADR9_LSB                               0x1E70
#define _P0_92_PT_1E7_WIN4_7_ADR9_MSB                               0x1E71
#define _P0_92_PT_1E7_WIN4_7_ADR9_HSB                               0x1E72
#define _P0_92_PT_1E8_WIN4_7_ADR10_LSB                              0x1E80
#define _P0_92_PT_1E8_WIN4_7_ADR10_MSB                              0x1E81
#define _P0_92_PT_1E8_WIN4_7_ADR10_HSB                              0x1E82
#define _P0_92_PT_1EE_WIN4_8_ADR9_LSB                               0x1EE0
#define _P0_92_PT_1EE_WIN4_8_ADR9_MSB                               0x1EE1
#define _P0_92_PT_1EE_WIN4_8_ADR9_HSB                               0x1EE2
#define _P0_92_PT_1EF_WIN4_8_ADR10_LSB                              0x1EF0
#define _P0_92_PT_1EF_WIN4_8_ADR10_MSB                              0x1EF1
#define _P0_92_PT_1EF_WIN4_8_ADR10_HSB                              0x1EF2
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
#define _P0_92_PT_2A0_WIN5_1_ADR4_LSB                               0x2A00
#define _P0_92_PT_2A0_WIN5_1_ADR4_MSB                               0x2A01
#define _P0_92_PT_2A0_WIN5_1_ADR4_HSB                               0x2A02
#define _P0_92_PT_2A5_WIN5_1_ADR9_LSB                               0x2A50
#define _P0_92_PT_2A5_WIN5_1_ADR9_MSB                               0x2A51
#define _P0_92_PT_2A5_WIN5_1_ADR9_HSB                               0x2A52
#define _P0_92_PT_2A6_WIN5_1_ADR10_LSB                              0x2A60
#define _P0_92_PT_2A6_WIN5_1_ADR10_MSB                              0x2A61
#define _P0_92_PT_2A6_WIN5_1_ADR10_HSB                              0x2A62
#define _P0_92_PT_2AA_WIN5_2_ADR4_LSB                               0x2AA0
#define _P0_92_PT_2AA_WIN5_2_ADR4_MSB                               0x2AA1
#define _P0_92_PT_2AA_WIN5_2_ADR4_HSB                               0x2AA2
#define _P0_92_PT_2AF_WIN5_2_ADR9_LSB                               0x2AF0
#define _P0_92_PT_2AF_WIN5_2_ADR9_MSB                               0x2AF1
#define _P0_92_PT_2AF_WIN5_2_ADR9_HSB                               0x2AF2
#define _P0_92_PT_2B0_WIN5_2_ADR10_LSB                              0x2B00
#define _P0_92_PT_2B0_WIN5_2_ADR10_MSB                              0x2B01
#define _P0_92_PT_2B0_WIN5_2_ADR10_HSB                              0x2B02
#define _P0_92_PT_2B4_WIN5_3_ADR4_LSB                               0x2B40
#define _P0_92_PT_2B4_WIN5_3_ADR4_MSB                               0x2B41
#define _P0_92_PT_2B4_WIN5_3_ADR4_HSB                               0x2B42
#define _P0_92_PT_2B9_WIN5_3_ADR9_LSB                               0x2B90
#define _P0_92_PT_2B9_WIN5_3_ADR9_MSB                               0x2B91
#define _P0_92_PT_2B9_WIN5_3_ADR9_HSB                               0x2B92
#define _P0_92_PT_2BA_WIN5_3_ADR10_LSB                              0x2BA0
#define _P0_92_PT_2BA_WIN5_3_ADR10_MSB                              0x2BA1
#define _P0_92_PT_2BA_WIN5_3_ADR10_HSB                              0x2BA2
#define _P0_92_PT_2BE_WIN5_4_ADR4_LSB                               0x2BE0
#define _P0_92_PT_2BE_WIN5_4_ADR4_MSB                               0x2BE1
#define _P0_92_PT_2BE_WIN5_4_ADR4_HSB                               0x2BE2
#define _P0_92_PT_2C3_WIN5_4_ADR9_LSB                               0x2C30
#define _P0_92_PT_2C3_WIN5_4_ADR9_MSB                               0x2C31
#define _P0_92_PT_2C3_WIN5_4_ADR9_HSB                               0x2C32
#define _P0_92_PT_2C4_WIN5_4_ADR10_LSB                              0x2C40
#define _P0_92_PT_2C4_WIN5_4_ADR10_MSB                              0x2C41
#define _P0_92_PT_2C4_WIN5_4_ADR10_HSB                              0x2C42
#define _P0_92_PT_2C8_WIN5_5_ADR4_LSB                               0x2C80
#define _P0_92_PT_2C8_WIN5_5_ADR4_MSB                               0x2C81
#define _P0_92_PT_2C8_WIN5_5_ADR4_HSB                               0x2C82
#define _P0_92_PT_2CD_WIN5_5_ADR9_LSB                               0x2CD0
#define _P0_92_PT_2CD_WIN5_5_ADR9_MSB                               0x2CD1
#define _P0_92_PT_2CD_WIN5_5_ADR9_HSB                               0x2CD2
#define _P0_92_PT_2CE_WIN5_5_ADR10_LSB                              0x2CE0
#define _P0_92_PT_2CE_WIN5_5_ADR10_MSB                              0x2CE1
#define _P0_92_PT_2CE_WIN5_5_ADR10_HSB                              0x2CE2
#define _P0_92_PT_2D2_WIN5_6_ADR4_LSB                               0x2D20
#define _P0_92_PT_2D2_WIN5_6_ADR4_MSB                               0x2D21
#define _P0_92_PT_2D2_WIN5_6_ADR4_HSB                               0x2D22
#define _P0_92_PT_2D7_WIN5_6_ADR9_LSB                               0x2D70
#define _P0_92_PT_2D7_WIN5_6_ADR9_MSB                               0x2D71
#define _P0_92_PT_2D7_WIN5_6_ADR9_HSB                               0x2D72
#define _P0_92_PT_2D8_WIN5_6_ADR10_LSB                              0x2D80
#define _P0_92_PT_2D8_WIN5_6_ADR10_MSB                              0x2D81
#define _P0_92_PT_2D8_WIN5_6_ADR10_HSB                              0x2D82
#define _P0_92_PT_2DC_WIN5_7_ADR4_LSB                               0x2DC0
#define _P0_92_PT_2DC_WIN5_7_ADR4_MSB                               0x2DC1
#define _P0_92_PT_2DC_WIN5_7_ADR4_HSB                               0x2DC2
#define _P0_92_PT_2E1_WIN5_7_ADR9_LSB                               0x2E10
#define _P0_92_PT_2E1_WIN5_7_ADR9_MSB                               0x2E11
#define _P0_92_PT_2E1_WIN5_7_ADR9_HSB                               0x2E12
#define _P0_92_PT_2E2_WIN5_7_ADR10_LSB                              0x2E20
#define _P0_92_PT_2E2_WIN5_7_ADR10_MSB                              0x2E21
#define _P0_92_PT_2E2_WIN5_7_ADR10_HSB                              0x2E22
#define _P0_92_PT_2E6_WIN5_8_ADR4_LSB                               0x2E60
#define _P0_92_PT_2E6_WIN5_8_ADR4_MSB                               0x2E61
#define _P0_92_PT_2E6_WIN5_8_ADR4_HSB                               0x2E62
#define _P0_92_PT_2EB_WIN5_8_ADR9_LSB                               0x2EB0
#define _P0_92_PT_2EB_WIN5_8_ADR9_MSB                               0x2EB1
#define _P0_92_PT_2EB_WIN5_8_ADR9_HSB                               0x2EB2
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
// Overall HDMI2.0 Function SCDC Port Register (Page 2)
//--------------------------------------------------
#define _P2_3A_PT_01_PORT_PAGE02_HDMI_SCDC_01                       0x01
#define _P2_3A_PT_02_PORT_PAGE02_HDMI_SCDC_02                       0x02
#define _P2_3A_PT_10_PORT_PAGE02_HDMI_SCDC_10                       0x10
#define _P2_3A_PT_11_PORT_PAGE02_HDMI_SCDC_11                       0x11
#define _P2_3A_PT_20_PORT_PAGE02_HDMI_SCDC_20                       0x20
#define _P2_3A_PT_21_PORT_PAGE02_HDMI_SCDC_21                       0x21
#define _P2_3A_PT_30_PORT_PAGE02_HDMI_SCDC_30                       0x30
#define _P2_3A_PT_40_PORT_PAGE02_HDMI_SCDC_40                       0x40
#define _P2_3A_PT_41_PORT_PAGE02_HDMI_SCDC_41                       0x41
#define _P2_3A_PT_50_PORT_PAGE02_HDMI_SCDC_50                       0x50
#define _P2_3A_PT_51_PORT_PAGE02_HDMI_SCDC_51                       0x51
#define _P2_3A_PT_52_PORT_PAGE02_HDMI_SCDC_52                       0x52
#define _P2_3A_PT_53_PORT_PAGE02_HDMI_SCDC_53                       0x53
#define _P2_3A_PT_54_PORT_PAGE02_HDMI_SCDC_54                       0x54
#define _P2_3A_PT_55_PORT_PAGE02_HDMI_SCDC_55                       0x55
#define _P2_3A_PT_56_PORT_PAGE02_HDMI_SCDC_56                       0x56
#define _P2_3A_PT_C0_PORT_PAGE02_HDMI_SCDC_C0                       0xC0
#define _P2_3A_PT_D0_PORT_PAGE02_HDMI_SCDC_D0                       0xD0
#define _P2_3A_PT_D1_PORT_PAGE02_HDMI_SCDC_D1                       0xD1
#define _P2_3A_PT_D2_PORT_PAGE02_HDMI_SCDC_D2                       0xD2
#define _P2_3A_PT_D3_PORT_PAGE02_HDMI_SCDC_D3                       0xD3
#define _P2_3A_PT_D4_PORT_PAGE02_HDMI_SCDC_D4                       0xD4
#define _P2_3A_PT_D5_PORT_PAGE02_HDMI_SCDC_D5                       0xD5
#define _P2_3A_PT_D6_PORT_PAGE02_HDMI_SCDC_D6                       0xD6
#define _P2_3A_PT_D7_PORT_PAGE02_HDMI_SCDC_D7                       0xD7
#define _P2_3A_PT_D8_PORT_PAGE02_HDMI_SCDC_D8                       0xD8
#define _P2_3A_PT_D9_PORT_PAGE02_HDMI_SCDC_D9                       0xD9
#define _P2_3A_PT_DA_PORT_PAGE02_HDMI_SCDC_DA                       0xDA
#define _P2_3A_PT_DB_PORT_PAGE02_HDMI_SCDC_DB                       0xDB
#define _P2_3A_PT_DC_PORT_PAGE02_HDMI_SCDC_DC                       0xDC
#define _P2_3A_PT_DD_PORT_PAGE02_HDMI_SCDC_DD                       0xDD
#define _P2_3A_PT_DE_PORT_PAGE02_HDMI_SCDC_DE                       0xDE
#define _P2_3A_PT_DF_PORT_PAGE02_HDMI_SCDC_DF                       0xDF
#define _P2_3A_PT_E0_PORT_PAGE02_HDMI_SCDC_E0                       0xE0
#define _P2_3A_PT_E1_PORT_PAGE02_HDMI_SCDC_E1                       0xE1
#define _P2_3A_PT_E2_PORT_PAGE02_HDMI_SCDC_E2                       0xE2
#define _P2_3A_PT_E3_PORT_PAGE02_HDMI_SCDC_E3                       0xE3
#define _P2_3A_PT_E4_PORT_PAGE02_HDMI_SCDC_E4                       0xE4
#define _P2_3A_PT_E5_PORT_PAGE02_HDMI_SCDC_E5                       0xE5
#define _P2_3A_PT_E6_PORT_PAGE02_HDMI_SCDC_E6                       0xE6
#define _P2_3A_PT_E7_PORT_PAGE02_HDMI_SCDC_E7                       0xE7
#define _P2_3A_PT_E8_PORT_PAGE02_HDMI_SCDC_E8                       0xE8
#define _P2_3A_PT_E9_PORT_PAGE02_HDMI_SCDC_E9                       0xE9
#define _P2_3A_PT_EA_PORT_PAGE02_HDMI_SCDC_EA                       0xEA
#define _P2_3A_PT_EB_PORT_PAGE02_HDMI_SCDC_EB                       0xEB
#define _P2_3A_PT_EC_PORT_PAGE02_HDMI_SCDC_EC                       0xEC
#define _P2_3A_PT_ED_PORT_PAGE02_HDMI_SCDC_ED                       0xED
#define _P2_3A_PT_EE_PORT_PAGE02_HDMI_SCDC_EE                       0xEE
#define _P2_3A_PT_EF_PORT_PAGE02_HDMI_SCDC_EF                       0xEF
#define _P2_3A_PT_F0_PORT_PAGE02_HDMI_SCDC_F0                       0xF0
#define _P2_3A_PT_F1_PORT_PAGE02_HDMI_SCDC_F1                       0xF1
#define _P2_3A_PT_F2_PORT_PAGE02_HDMI_SCDC_F2                       0xF2
#define _P2_3A_PT_F3_PORT_PAGE02_HDMI_SCDC_F3                       0xF3
#define _P2_3A_PT_F4_PORT_PAGE02_HDMI_SCDC_F4                       0xF4
#define _P2_3A_PT_F5_PORT_PAGE02_HDMI_SCDC_F5                       0xF5
#define _P2_3A_PT_F6_PORT_PAGE02_HDMI_SCDC_F6                       0xF6
#define _P2_3A_PT_F7_PORT_PAGE02_HDMI_SCDC_F7                       0xF7
#define _P2_3A_PT_F8_PORT_PAGE02_HDMI_SCDC_F8                       0xF8
#define _P2_3A_PT_F9_PORT_PAGE02_HDMI_SCDC_F9                       0xF9
#define _P2_3A_PT_FA_PORT_PAGE02_HDMI_SCDC_FA                       0xFA
#define _P2_3A_PT_FB_PORT_PAGE02_HDMI_SCDC_FB                       0xFB
#define _P2_3A_PT_FC_PORT_PAGE02_HDMI_SCDC_FC                       0xFC
#define _P2_3A_PT_FD_PORT_PAGE02_HDMI_SCDC_FD                       0xFD
#define _P2_3A_PT_FE_PORT_PAGE02_HDMI_SCDC_FE                       0xFE
#define _P2_3A_PT_FF_PORT_PAGE02_HDMI_SCDC_FF                       0xFF


//--------------------------------------------------
// Overall HDMI System Function Block HDCP Port Register (Page 2)
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


//--------------------------------------------------
// Overall HDMI System Function Block Video Port Register (Page 2)
//--------------------------------------------------
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
#define _P2_CA_PT_A0_PORT_PAGE2_HDMI_AFIFO_SET                      0xA0
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
#define _P2_CA_PT_B9_PORT_PAGE2_HDMI_BED_FUNC_10                    0xB9
#define _P2_CA_PT_BA_PORT_PAGE2_HDMI_BED_FUNC_11                    0xBA
#define _P2_CA_PT_BB_PORT_PAGE2_HDMI_BED_FUNC_12                    0xBB


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
#define _P7_CA_PT_00_PORT_PAGE2_SRAM_INITIAL_VAL                    0x00


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
// ID code Part1 (Page 0)
//--------------------------------------------------
#define P0_00_ID_REG                                                0x0000


//--------------------------------------------------
// Chip Control Part1 (Page 0)
//--------------------------------------------------
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


//--------------------------------------------------
// ID code Part2 (Page 0)
//--------------------------------------------------
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
// Page Control (Page 0)
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
#define P1_BF_DPLL_CLK_CTRL_0                                       0x01BF
#define P1_C0_DPLL_N_F_CODE_1                                       0x01C0
#define P1_C1_DPLL_N_F_CODE_2                                       0x01C1
#define P1_C2_DPLL_N_F_CODE_3                                       0x01C2
#define P1_C3_DPLL_N_F_CODE_4                                       0x01C3
#define P1_C4_DPLL_SDM_0                                            0x01C4
#define P1_C5_DPLL_SDM_1                                            0x01C5
#define P1_C6_DPLL_SDM_2                                            0x01C6
#define P1_C7_DCLK_GATED_CTRL1                                      0x01C7
#define P1_C8_DCLK_GATED_CTRL2                                      0x01C8
#define P1_C9_DPLL_CLK_CTRL_1                                       0x01C9
#define P1_CA_DPLL_SSCG_0                                           0x01CA
#define P1_CB_DPLL_SSCG_1                                           0x01CB
#define P1_CC_DPLL_SSCG_2                                           0x01CC
#define P1_CD_DPLL_SSCG_3                                           0x01CD
#define P1_CE_DPLL_SSCG_4                                           0x01CE
#define P1_CF_DPLL_SSCG_5                                           0x01CF
#define P1_D0_DPLL_ANALOG_SETTING_0                                 0x01D0
#define P1_D1_DPLL_ANALOG_SETTING_1                                 0x01D1
#define P1_D2_DPLL_ANALOG_SETTING_2                                 0x01D2
#define P1_D3_DPLL_ANALOG_SETTING_3                                 0x01D3
#define P1_D4_DPLL_WD_0                                             0x01D4
#define P1_D5_DPLL_CLK_CTRL_2                                       0x01D5
#define P1_D6_DPLL_LINEAR_CG_0                                      0x01D6
#define P1_D7_DPLL_LINEAR_CG_1                                      0x01D7
#define P1_D8_DPLL_LINEAR_CG_2                                      0x01D8
#define P1_D9_DPLL_LINEAR_CG_3                                      0x01D9
#define P1_DA_DPLL_LINEAR_CG_4                                      0x01DA
#define P1_DB_DPLL_SSCG_6                                           0x01DB
#define P1_DC_DPLL_SSCG_7                                           0x01DC
#define P1_DD_DPLL_SSCG_8                                           0x01DD
#define P1_DE_DPLL_SSCG_9                                           0x01DE


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
// Overall HDMI2.0 Function (Page 2)
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
#define P2_49_HDMI20_TEST_PIN_OUT                                   0x0249


//--------------------------------------------------
// IVHS Delay for HDMI (Page 2)
//--------------------------------------------------
#define P2_70_IVHS_CTRL_0                                           0x0270
#define P2_71_IVHS_CTRL_1                                           0x0271
#define P2_72_IVHS_CTRL_2                                           0x0272
#define P2_73_IVHS_CTRL_3                                           0x0273
#define P2_74_IVHS_CTRL_4                                           0x0274
#define P2_75_IVHS_CTRL_5                                           0x0275
#define P2_76_IVHS_CTRL_6                                           0x0276


//--------------------------------------------------
// Overall HDMI System Function Block (Page 2)
//--------------------------------------------------
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
#define P2_B1_TMDS_DBB1                                             0x02B1
#define P2_B2_TMDS_DBB2                                             0x02B2
#define P2_B3_TMDS_DBB3                                             0x02B3
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
#define P2_F0_HDMI_DBF0                                             0x02F0
#define P2_F1_HDMI_DBF1                                             0x02F1
#define P2_F2_HDMI_DBF2                                             0x02F2
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
// SDRAM / DDR Control (Page 4)
//--------------------------------------------------
#define P4_4F_DDR_DCU_WRITE_RECOVERY                                0x044F
#define P4_A1_SDR_CTRL0                                             0x04A1
#define P4_A2_SDR_CTRL1                                             0x04A2
#define P4_A3_SDR_AREF_TIME                                         0x04A3
#define P4_A4_SDR_PRCG                                              0x04A4
#define P4_A5_SDR_MEM_TYPE                                          0x04A5
#define P4_A6_SDR_SLEW_RATE                                         0x04A6
#define P4_A7_SDR_AREF_CNT                                          0x04A7
#define P4_A8_SDR_CLK_ALIGN                                         0x04A8
#define P4_A9_DUMMY                                                 0x04A9
#define P4_AA_SDR_RSC_AREF                                          0x04AA
#define P4_AB_SDR_RSC_MCU                                           0x04AB
#define P4_AC_SDR_RSC_CAP1                                          0x04AC
#define P4_AE_SDR_RSC_MAIN                                          0x04AE
#define P4_B0_SDR_RSC_RTC_RD                                        0x04B0
#define P4_B1_SDR_RSC_RTC_WR                                        0x04B1
#define P4_B2_DUMMY                                                 0x04B2
#define P4_B3_DUMMY                                                 0x04B3
#define P4_B4_SDR_ABTR_STATUS0                                      0x04B4
#define P4_B5_SDR_ABTR_STATUS1                                      0x04B5
#define P4_B6_DUMMY                                                 0x04B6
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
#define P5_A6_IN1_WR_FIFODEP_THRESHOLD_H                            0x05A6
#define P5_A7_IN1_WR_FIFODEP_THRESHOLD_L                            0x05A7
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
#define P5_D1_DUMMY_D1                                              0x05D1
#define P5_D3_DUMMY_D3                                              0x05D3
#define P5_D6_ADC_TEST                                              0x05D6
#define P5_D8_DUMMY_D8                                              0x05D8
#define P5_DB_DUMMY_DB                                              0x05DB
#define P5_DD_DUMMY_DD                                              0x05DD
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
#define P9_A0_INPUT_GAMMA_PORT_SETA                                 0x09A0
#define P9_A1_INPUT_GAMMA_CTRL_SETA                                 0x09A1
#define P9_A2_INPUT_GAMMA_LOW_THRE_R                                0x09A2
#define P9_A3_INPUT_GAMMA_HIGH_THRE_R                               0x09A3
#define P9_A4_INPUT_GAMMA_LOW_THRE_G                                0x09A4
#define P9_A5_INPUT_GAMMA_HIGH_THRE_G                               0x09A5
#define P9_A6_INPUT_GAMMA_LOW_THRE_B                                0x09A6
#define P9_A7_INPUT_GAMMA_HIGH_THRE_B                               0x09A7
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
// D0 Port DisplayPort 1.2 Digital PHY (Page B)
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
#define PB_4A_DP_LANEX_ACCUMLATED_ERR_COUNT                         0x0B4A
#define PB_4B_DP_COMMA_DET_MANU                                     0x0B4B
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
#define PB_92_DUMMY                                                 0x0B92
#define PB_93_HDCP_TYPE_AES_0                                       0x0B93
#define PB_94_HDCP_TYPE_AES_1                                       0x0B94
#define PB_95_HDCP_ST_TYPE                                          0x0B95
#define PB_96_DUMMY3                                                0x0B96


//--------------------------------------------------
// Pin Share Register (Page 10)
//--------------------------------------------------
#define P10_00_PIN_SHARE_CTRL00__ON1                                0x1000
#define P10_01_PIN_SHARE_CTRL01__ON1                                0x1001
#define P10_02_PIN_SHARE_CTRL02__ON1                                0x1002
#define P10_03_PIN_SHARE_CTRL03__ON1                                0x1003
#define P10_04_PIN_SHARE_CTRL04__ON1                                0x1004
#define P10_05_PIN_SHARE_CTRL05__ON1                                0x1005
#define P10_06_PIN_SHARE_CTRL06__ON1                                0x1006
#define P10_07_PIN_SHARE_CTRL07__ON1                                0x1007
#define P10_08_PIN_SHARE_CTRL08__ON1                                0x1008
#define P10_09_PIN_SHARE_CTRL09__ON1                                0x1009
#define P10_0A_PIN_SHARE_CTRL0A__ON1                                0x100A
#define P10_0B_PIN_SHARE_CTRL0B__ON1                                0x100B
#define P10_0C_PIN_SHARE_CTRL0C__ON1                                0x100C
#define P10_0D_PIN_SHARE_CTRL0D__ON1                                0x100D
#define P10_0E_PIN_SHARE_CTRL0E__ON1                                0x100E
#define P10_0F_PIN_SHARE_CTRL0F__ON1                                0x100F
#define P10_10_PIN_SHARE_CTRL10__ON1                                0x1010
#define P10_11_PIN_SHARE_CTRL11__ON1                                0x1011
#define P10_12_PIN_SHARE_CTRL12__ON1                                0x1012
#define P10_13_PIN_SHARE_CTRL13__ON1                                0x1013
#define P10_14_PIN_SHARE_CTRL14__ON1                                0x1014
#define P10_15_PIN_SHARE_CTRL15__ON1                                0x1015
#define P10_16_PIN_SHARE_CTRL16__ON1                                0x1016
#define P10_17_PIN_SHARE_CTRL17__ON1                                0x1017
#define P10_18_PIN_SHARE_CTRL18__ON1                                0x1018
#define P10_19_PIN_SHARE_CTRL19__ON1                                0x1019
#define P10_1A_PIN_SHARE_CTRL1A__ON1                                0x101A
#define P10_1B_PIN_SHARE_CTRL1B__ON1                                0x101B
#define P10_1C_PIN_SHARE_CTRL1C__ON1                                0x101C
#define P10_1D_PIN_SHARE_CTRL1D__ON1                                0x101D
#define P10_1E_PIN_SHARE_CTRL1E__ON1                                0x101E
#define P10_1F_PIN_SHARE_CTRL1F__ON1                                0x101F
#define P10_20_PIN_SHARE_CTRL20__OFF1                               0x1020
#define P10_21_PIN_SHARE_CTRL21__OFF1                               0x1021
#define P10_22_PIN_SHARE_CTRL22__OFF1                               0x1022
#define P10_23_PIN_SHARE_CTRL23__OFF1                               0x1023
#define P10_24_PIN_SHARE_CTRL24__OFF1                               0x1024
#define P10_25_PIN_SHARE_CTRL25__OFF1                               0x1025
#define P10_26_PIN_SHARE_CTRL26__OFF1                               0x1026
#define P10_27_PIN_SHARE_CTRL27__OFF1                               0x1027
#define P10_28_PIN_SHARE_CTRL28__OFF1                               0x1028
#define P10_29_PIN_SHARE_CTRL29__OFF1                               0x1029
#define P10_2A_PIN_SHARE_CTRL2A__ON1                                0x102A
#define P10_2B_PIN_SHARE_CTRL2B__ON1                                0x102B
#define P10_2C_PIN_SHARE_CTRL2C__ON1                                0x102C
#define P10_2D_PIN_SHARE_CTRL2D__ON1                                0x102D
#define P10_2E_PIN_SHARE_CTRL2E__ON1                                0x102E
#define P10_2F_PIN_SHARE_CTRL2F__ON1                                0x102F
#define P10_30_PIN_SHARE_CTRL30__ON1                                0x1030
#define P10_31_PIN_SHARE_CTRL31__ON1                                0x1031
#define P10_32_PIN_SHARE_CTRL32__ON1                                0x1032
#define P10_33_PIN_SHARE_CTRL33__ON1                                0x1033
#define P10_34_PIN_SHARE_CTRL34__ON1                                0x1034
#define P10_35_PIN_SHARE_CTRL35__ON1                                0x1035
#define P10_36_PIN_SHARE_CTRL36__ON1                                0x1036
#define P10_37_PIN_SHARE_CTRL37__ON1                                0x1037
#define P10_38_PIN_SHARE_CTRL38__ON1                                0x1038
#define P10_39_PIN_SHARE_CTRL39__ON1                                0x1039
#define P10_3A_PIN_SHARE_CTRL3A__ON1                                0x103A
#define P10_3B_PIN_SHARE_CTRL3B__ON1                                0x103B
#define P10_3C_PIN_SHARE_CTRL3C__ON1                                0x103C
#define P10_3D_PIN_SHARE_CTRL3D__ON1                                0x103D
#define P10_3E_PIN_SHARE_CTRL3E__ON1                                0x103E
#define P10_3F_PIN_SHARE_CTRL3F__ON1                                0x103F
#define P10_40_PIN_SHARE_CTRL40__ON1                                0x1040
#define P10_41_PIN_SHARE_CTRL41__ON1                                0x1041
#define P10_42_DUMMY1__ON1                                          0x1042
#define P10_43_DUMMY2__ON1                                          0x1043
#define P10_44_DUMMY3__OFF1                                         0x1044
#define P10_45_HDMI_HPD_INT_SEL__ON1                                0x1045
#define P10_46_1M_TRIM_CTRL0__ON1                                   0x1046
#define P10_80_PIN_SLEW_RATE_CTRL00__ON1                            0x1080
#define P10_88_PIN_SCHMITT_CTRL00__ON1                              0x1088
#define P10_89_PIN_SCHMITT_CTRL01__ON1                              0x1089
#define P10_8A_PIN_SCHMITT_CTRL02__ON1                              0x108A
#define P10_A0_PIN_PULLUP_CTRL00__ON1                               0x10A0
#define P10_A1_PIN_PULLUP_CTRL01__ON1                               0x10A1
#define P10_A2_PIN_PULLUP_CTRL02__ON1                               0x10A2
#define P10_A3_PIN_PULLUP_CTRL03__ON1                               0x10A3
#define P10_A4_PIN_PULLUP_CTRL04__ON1                               0x10A4
#define P10_A5_PIN_PULLUP_CTRL05__ON1                               0x10A5
#define P10_A6_PIN_PULLUP_CTRL06__ON1                               0x10A6
#define P10_A7_PIN_PULLUP_CTRL07__ON1                               0x10A7
#define P10_A8_PIN_PULLUP_CTRL08__ON1                               0x10A8
#define P10_A9_PIN_PULLUP_CTRL09__ON1                               0x10A9
#define P10_AA_PIN_PULLUP_CTRL0A__ON1                               0x10AA
#define P10_AB_PIN_PULLUP_CTRL0B__ON1                               0x10AB
#define P10_AC_PIN_PULLUP_CTRL0C__ON1                               0x10AC
#define P10_C0_PIN_DRIVING_CTRL00__ON1                              0x10C0
#define P10_C1_PIN_DRIVING_CTRL01__ON1                              0x10C1
#define P10_C2_PIN_DRIVING_CTRL02__ON1                              0x10C2
#define P10_C3_PIN_DRIVING_CTRL03__ON1                              0x10C3
#define P10_C4_PIN_DRIVING_CTRL04__ON1                              0x10C4
#define P10_C5_PIN_DRIVING_CTRL05__ON1                              0x10C5
#define P10_C6_PIN_DRIVING_CTRL06__ON1                              0x10C6


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
// UFP DP1.3 combo U3 GDI DFE (Page 17)
//--------------------------------------------------
#define P17_A0_L0_DFE_EN_1                                          0x17A0
#define P17_A1_L0_DFE_EN_2                                          0x17A1
#define P17_A2_L0_LIMIT_INIT                                        0x17A2
#define P17_A3_L0_INIT_1                                            0x17A3
#define P17_A4_L0_INIT_2                                            0x17A4
#define P17_A5_L0_INIT_3                                            0x17A5
#define P17_A6_L0_INIT_4                                            0x17A6
#define P17_A7_L0_INIT_5                                            0x17A7
#define P17_A8_L0_INIT_6                                            0x17A8
#define P17_A9_L0_INIT_7                                            0x17A9
#define P17_AA_L0_INIT_8                                            0x17AA
#define P17_AB_L0_STABLE_FLAG                                       0x17AB
#define P17_AF_L0_GDI_DE                                            0x17AF
#define P17_B0_L1_DFE_EN_1                                          0x17B0
#define P17_B1_L1_DFE_EN_2                                          0x17B1
#define P17_B2_L1_LIMIT_INIT                                        0x17B2
#define P17_B3_L1_INIT_1                                            0x17B3
#define P17_B4_L1_INIT_2                                            0x17B4
#define P17_B5_L1_INIT_3                                            0x17B5
#define P17_B6_L1_INIT_4                                            0x17B6
#define P17_B7_L1_INIT_5                                            0x17B7
#define P17_B8_L1_INIT_6                                            0x17B8
#define P17_B9_L1_INIT_7                                            0x17B9
#define P17_BA_L1_INIT_8                                            0x17BA
#define P17_BB_L1_STABLE_FLAG                                       0x17BB
#define P17_BF_L1_GDI_DE                                            0x17BF
#define P17_C0_L2_DFE_EN_1                                          0x17C0
#define P17_C1_L2_DFE_EN_2                                          0x17C1
#define P17_C2_L2_LIMIT_INIT                                        0x17C2
#define P17_C3_L2_INIT_1                                            0x17C3
#define P17_C4_L2_INIT_2                                            0x17C4
#define P17_C5_L2_INIT_3                                            0x17C5
#define P17_C6_L2_INIT_4                                            0x17C6
#define P17_C7_L2_INIT_5                                            0x17C7
#define P17_C8_L2_INIT_6                                            0x17C8
#define P17_C9_L2_INIT_7                                            0x17C9
#define P17_CA_L2_INIT_8                                            0x17CA
#define P17_CB_L2_STABLE_FLAG                                       0x17CB
#define P17_CF_L2_GDI_DE                                            0x17CF
#define P17_D0_L3_DFE_EN_1                                          0x17D0
#define P17_D1_L3_DFE_EN_2                                          0x17D1
#define P17_D2_L3_LIMIT_INIT                                        0x17D2
#define P17_D3_L3_INIT_1                                            0x17D3
#define P17_D4_L3_INIT_2                                            0x17D4
#define P17_D5_L3_INIT_3                                            0x17D5
#define P17_D6_L3_INIT_4                                            0x17D6
#define P17_D7_L3_INIT_5                                            0x17D7
#define P17_D8_L3_INIT_6                                            0x17D8
#define P17_D9_L3_INIT_7                                            0x17D9
#define P17_DA_L3_INIT_8                                            0x17DA
#define P17_DB_L3_STABLE_FLAG                                       0x17DB
#define P17_DF_L3_GDI_DE                                            0x17DF
#define P17_E0_MODE_TIMER                                           0x17E0
#define P17_E1_TIMER                                                0x17E1
#define P17_E2_GAIN_1                                               0x17E2
#define P17_E3_GAIN_2                                               0x17E3
#define P17_E4_GAIN_3                                               0x17E4
#define P17_E5_GAIN_4                                               0x17E5
#define P17_E6_LIMIT_1                                              0x17E6
#define P17_E7_LIMIT_2                                              0x17E7
#define P17_E8_LIMIT_3                                              0x17E8
#define P17_E9_LIMIT_4                                              0x17E9
#define P17_EA_LIMIT_5                                              0x17EA
#define P17_EB_LIMIT_6                                              0x17EB
#define P17_EC_LOOP_DIV_1                                           0x17EC
#define P17_ED_LOOP_DIV_2                                           0x17ED
#define P17_EE_GRAY_DEC_1                                           0x17EE
#define P17_EF_RESET_1                                              0x17EF
#define P17_F0_COEF_1                                               0x17F0
#define P17_F1_COEF_2                                               0x17F1
#define P17_F2_COEF_3                                               0x17F2
#define P17_F3_COEF_4                                               0x17F3
#define P17_F4_ERRCNT0                                              0x17F4
#define P17_F5_ERRCNT1                                              0x17F5
#define P17_F6_ERRCNT2                                              0x17F6
#define P17_F8_GRAY_DEC_2                                           0x17F8
#define P17_F9_LIMIT_10                                             0x17F9
#define P17_FA_GAIN_PREC                                            0x17FA
#define P17_FB_DEBUG                                                0x17FB
#define P17_FC_PR_CTRL0                                             0x17FC
#define P17_FD_PR_CTRL1                                             0x17FD
#define P17_FE_EM_CTRL0                                             0x17FE
#define P17_FF_EM_CTRL1                                             0x17FF


//--------------------------------------------------
// UFP DP1.3 combo U3 APHY (RX) (Page 1A)
//--------------------------------------------------
#define P1A_00_COMBO_00                                             0x1A00
#define P1A_01_COMBO_01                                             0x1A01
#define P1A_02_COMBO_02                                             0x1A02
#define P1A_03_COMBO_03                                             0x1A03
#define P1A_04_COMBO_04                                             0x1A04
#define P1A_05_COMBO_05                                             0x1A05
#define P1A_06_COMBO_06                                             0x1A06
#define P1A_10_COMBO_RX_00                                          0x1A10
#define P1A_11_COMBO_RX_01                                          0x1A11
#define P1A_12_COMBO_RX_02                                          0x1A12
#define P1A_13_COMBO_RX_03                                          0x1A13
#define P1A_14_COMBO_RX_04                                          0x1A14
#define P1A_15_COMBO_RX_05                                          0x1A15
#define P1A_16_COMBO_RX_06                                          0x1A16
#define P1A_17_COMBO_RX_07                                          0x1A17
#define P1A_20_DP_RX_00                                             0x1A20
#define P1A_21_DP_RX_01                                             0x1A21
#define P1A_22_DP_RX_02                                             0x1A22
#define P1A_23_DP_RX_03                                             0x1A23
#define P1A_24_DP_RX_04                                             0x1A24
#define P1A_25_DP_RX_05                                             0x1A25
#define P1A_26_DP_RX_06                                             0x1A26
#define P1A_27_DP_RX_07                                             0x1A27
#define P1A_28_DP_RX_08                                             0x1A28
#define P1A_29_DP_RX_09                                             0x1A29
#define P1A_2A_DP_RX_10                                             0x1A2A
#define P1A_2B_DP_RX_11                                             0x1A2B
#define P1A_2C_DP_RX_12                                             0x1A2C
#define P1A_30_COMBO_USB_00                                         0x1A30
#define P1A_31_COMBO_USB_01                                         0x1A31
#define P1A_40_USB_TOP                                              0x1A40
#define P1A_50_USB_CDR_00                                           0x1A50
#define P1A_51_USB_CDR_01                                           0x1A51
#define P1A_52_USB_CDR_02                                           0x1A52
#define P1A_53_USB_OOBS_00                                          0x1A53
#define P1A_54_USB_OOBS_01                                          0x1A54
#define P1A_55_USB_OOBS_02                                          0x1A55
#define P1A_56_USB_OOBS_03                                          0x1A56
#define P1A_57_USB_RX_00                                            0x1A57
#define P1A_58_USB_RX_01                                            0x1A58
#define P1A_59_USB_RX_02                                            0x1A59
#define P1A_5B_USB_RX_04                                            0x1A5B
#define P1A_60_USB_CMU_00                                           0x1A60
#define P1A_61_USB_CMU_01                                           0x1A61
#define P1A_62_USB_CMU_02                                           0x1A62
#define P1A_63_USB_CMU_03                                           0x1A63
#define P1A_64_USB_CMU_04                                           0x1A64
#define P1A_65_USB_TX_00                                            0x1A65
#define P1A_66_USB_TX_01                                            0x1A66
#define P1A_67_USB_TX_02                                            0x1A67
#define P1A_69_USB_TX_04                                            0x1A69
#define P1A_6A_USB_TX_05                                            0x1A6A
#define P1A_6B_USB_TX_06                                            0x1A6B
#define P1A_6C_USB_TX_07                                            0x1A6C
#define P1A_6D_USB_TX_08                                            0x1A6D
#define P1A_6E_USB_TX_09                                            0x1A6E


//--------------------------------------------------
// UFP DP1.3 combo U3 DPHY (RX) (Page 1C)
//--------------------------------------------------
#define P1C_00_DMR_0                                                0x1C00
#define P1C_01_DMR_1                                                0x1C01
#define P1C_02_BACR_0                                               0x1C02
#define P1C_03_BACR_1                                               0x1C03
#define P1C_04_IER_0                                                0x1C04
#define P1C_05_IER_1                                                0x1C05
#define P1C_06_BCSR_0                                               0x1C06
#define P1C_07_BCSR_1                                               0x1C07
#define P1C_08_BPR_0                                                0x1C08
#define P1C_09_BPR_1                                                0x1C09
#define P1C_0A_BPNR2                                                0x1C0A
#define P1C_0B_BFNR                                                 0x1C0B
#define P1C_0C_BRNR2                                                0x1C0C
#define P1C_0D_BENR_0                                               0x1C0D
#define P1C_0E_BENR_1                                               0x1C0E
#define P1C_0F_REG_REV0_0                                           0x1C0F
#define P1C_10_REG_REV0_1                                           0x1C10
#define P1C_11_REG_REV1_0                                           0x1C11
#define P1C_12_REG_REV1_1                                           0x1C12
#define P1C_13_REG_REV2_0                                           0x1C13
#define P1C_14_REG_REV2_1                                           0x1C14
#define P1C_15_REG_REV3_0                                           0x1C15
#define P1C_16_REG_REV3_1                                           0x1C16
#define P1C_17_FLD_0_0                                              0x1C17
#define P1C_18_FLD_0_1                                              0x1C18
#define P1C_19_FLD_1_0                                              0x1C19
#define P1C_1A_FLD_1_1                                              0x1C1A
#define P1C_1B_ANA1F_READONLY_0                                     0x1C1B
#define P1C_1C_ANA1F_READONLY_1                                     0x1C1C
#define P1C_1D_PA1_REG10_READOUT_0                                  0x1C1D
#define P1C_1E_PA1_REG10_READOUT_1                                  0x1C1E
#define P1C_1F_PA1_REG11_READOUT_0                                  0x1C1F
#define P1C_20_PA1_REG11_READOUT_1                                  0x1C20
#define P1C_21_DPHY_0                                               0x1C21
#define P1C_22_DPHY_1                                               0x1C22
#define P1C_24_DPHY_2                                               0x1C24
#define P1C_25_DPHY_3                                               0x1C25
#define P1C_26_FORE_OFFSET_K_0                                      0x1C26
#define P1C_27_FORE_OFFSET_K_1                                      0x1C27
#define P1C_28_FORE_OFFSET_K_2                                      0x1C28
#define P1C_29_FORE_OFFSET_K_3                                      0x1C29
#define P1C_2A_FORE_OFFSET_K_4                                      0x1C2A
#define P1C_2B_FORE_OFFSET_K_5                                      0x1C2B
#define P1C_2C_FORE_OFFSET_K_6                                      0x1C2C
#define P1C_2D_FORE_OFFSET_K_7                                      0x1C2D
#define P1C_2E_FORE_OFFSET_K_8                                      0x1C2E
#define P1C_2F_FORE_OFFSET_K_9                                      0x1C2F
#define P1C_30_FORE_OFFSET_K_10                                     0x1C30
#define P1C_31_FORE_OFFSET_K_11                                     0x1C31
#define P1C_32_FORE_OFFSET_K_12                                     0x1C32
#define P1C_33_FORE_OFFSET_K_13                                     0x1C33
#define P1C_34_FORE_OFFSET_K_14                                     0x1C34
#define P1C_35_FORE_OFFSET_K_15                                     0x1C35
#define P1C_36_FORE_OFFSET_K_16                                     0x1C36
#define P1C_37_FORE_OFFSET_K_17                                     0x1C37
#define P1C_38_FORE_OFFSET_K_18                                     0x1C38
#define P1C_39_FORE_OFFSET_K_19                                     0x1C39
#define P1C_3A_FORE_OFFSET_K_20                                     0x1C3A
#define P1C_3B_FORE_OFFSET_K_21                                     0x1C3B
#define P1C_3C_FORE_OFFSET_K_22                                     0x1C3C
#define P1C_3D_FORE_OFFSET_K_23                                     0x1C3D
#define P1C_3E_FORE_OFFSET_K_24                                     0x1C3E
#define P1C_3F_FORE_OFFSET_K_25                                     0x1C3F
#define P1C_40_FORE_OFFSET_K_26                                     0x1C40
#define P1C_41_FORE_OFFSET_K_27                                     0x1C41
#define P1C_42_FORE_OFFSET_K_28                                     0x1C42
#define P1C_43_FORE_OFFSET_K_29                                     0x1C43
#define P1C_44_FORE_OFFSET_K_30                                     0x1C44
#define P1C_45_FORE_OFFSET_K_31                                     0x1C45
#define P1C_46_FORE_OFFSET_K_32                                     0x1C46
#define P1C_47_FORE_OFFSET_K_33                                     0x1C47
#define P1C_48_FORE_OFFSET_K_34                                     0x1C48
#define P1C_49_FORE_OFFSET_K_35                                     0x1C49
#define P1C_4A_FORE_OFFSET_K_36                                     0x1C4A
#define P1C_4B_READY_TIMER_0                                        0x1C4B
#define P1C_4C_READY_TIMER_1                                        0x1C4C
#define P1C_4D_READY_TIMER_2                                        0x1C4D
#define P1C_4E_DP_FLD_0                                             0x1C4E
#define P1C_4F_DP_FLD_1                                             0x1C4F
#define P1C_50_DP_FLD_2                                             0x1C50
#define P1C_51_DP_FLD_3                                             0x1C51
#define P1C_52_DP_FLD_4                                             0x1C52
#define P1C_53_DP_FLD_5                                             0x1C53
#define P1C_54_DP_FLD_6                                             0x1C54
#define P1C_55_DP_FLD_7                                             0x1C55
#define P1C_56_DP_FLD_8                                             0x1C56
#define P1C_57_DP_FLD_9                                             0x1C57
#define P1C_58_DP_FLD_10                                            0x1C58
#define P1C_59_DP_FLD_11                                            0x1C59
#define P1C_5A_DP_FLD_12                                            0x1C5A
#define P1C_5B_DP_FLD_13                                            0x1C5B
#define P1C_5C_DP_FLD_14                                            0x1C5C
#define P1C_5D_DP_FLD_15                                            0x1C5D
#define P1C_5E_DP_FLD_16                                            0x1C5E
#define P1C_5F_DP_FLD_17                                            0x1C5F
#define P1C_60_DP_FLD_18                                            0x1C60
#define P1C_61_DP_FLD_19                                            0x1C61
#define P1C_62_DP_FLD_20                                            0x1C62
#define P1C_63_DP_FLD_21                                            0x1C63
#define P1C_64_DP_FLD_22                                            0x1C64
#define P1C_65_DP_FLD_23                                            0x1C65
#define P1C_66_DP_FLD_24                                            0x1C66
#define P1C_67_DP_FLD_25                                            0x1C67
#define P1C_68_DP_FLD_26                                            0x1C68
#define P1C_69_DP_FLD_27                                            0x1C69
#define P1C_6A_DP_FLD_28                                            0x1C6A
#define P1C_6B_DP_FLD_29                                            0x1C6B
#define P1C_6C_DP_FLD_30                                            0x1C6C
#define P1C_6D_DP_FLD_31                                            0x1C6D
#define P1C_6E_DP_FLD_32                                            0x1C6E
#define P1C_6F_DP_FLD_33                                            0x1C6F
#define P1C_70_DP_FLD_34                                            0x1C70
#define P1C_71_DP_FLD_35                                            0x1C71
#define P1C_72_DP_FLD_36                                            0x1C72
#define P1C_73_DP_FLD_37                                            0x1C73
#define P1C_74_DP_FLD_38                                            0x1C74
#define P1C_75_DP_FLD_39                                            0x1C75
#define P1C_76_DP_FLD_40                                            0x1C76
#define P1C_77_DP_FLD_41                                            0x1C77
#define P1C_78_DP_FLD_42                                            0x1C78
#define P1C_79_LFPS_EQEN_0                                          0x1C79
#define P1C_7A_LFPS_EQEN_1                                          0x1C7A
#define P1C_7B_LFPS_EQEN_2                                          0x1C7B
#define P1C_7C_U3_FLD_0                                             0x1C7C
#define P1C_7D_U3_FLD_1                                             0x1C7D
#define P1C_7E_U3_FLD_2                                             0x1C7E
#define P1C_7F_U3_FLD_3                                             0x1C7F
#define P1C_80_U3_FLD_4                                             0x1C80
#define P1C_81_U3_FLD_5                                             0x1C81
#define P1C_82_U3_FLD_6                                             0x1C82
#define P1C_83_U3_FLD_7                                             0x1C83
#define P1C_84_U3_FLD_8                                             0x1C84
#define P1C_85_U3_FLD_9                                             0x1C85
#define P1C_86_U3_FLD_10                                            0x1C86
#define P1C_87_U3_FLD_11                                            0x1C87
#define P1C_88_U3_FLD_12                                            0x1C88
#define P1C_89_U3_FLD_13                                            0x1C89
#define P1C_8A_U3_FLD_14                                            0x1C8A
#define P1C_8B_U3_FLD_15                                            0x1C8B
#define P1C_8C_U3_FLD_16                                            0x1C8C
#define P1C_8D_U3_FLD_17                                            0x1C8D
#define P1C_8E_U3_FLD_18                                            0x1C8E
#define P1C_8F_U3_FLD_19                                            0x1C8F
#define P1C_90_U3_FLD_20                                            0x1C90
#define P1C_91_U3_FLD_21                                            0x1C91
#define P1C_92_U3_FLD_22                                            0x1C92
#define P1C_93_U3_FLD_23                                            0x1C93
#define P1C_94_U3_FLD_24                                            0x1C94
#define P1C_95_U3_FLD_25                                            0x1C95
#define P1C_96_U3_FLD_26                                            0x1C96
#define P1C_97_U3_FLD_27                                            0x1C97
#define P1C_98_U3_FLD_28                                            0x1C98
#define P1C_99_CMU_SSC_0                                            0x1C99
#define P1C_9A_CMU_SSC_1                                            0x1C9A
#define P1C_9B_CMU_SSC_2                                            0x1C9B
#define P1C_9C_CMU_SSC_3                                            0x1C9C
#define P1C_9D_CMU_SSC_4                                            0x1C9D
#define P1C_A0_CMU_SSC_5                                            0x1CA0
#define P1C_A1_CMU_SSC_6                                            0x1CA1
#define P1C_A2_CMU_SSC_7                                            0x1CA2
#define P1C_A3_CMU_SSC_8                                            0x1CA3
#define P1C_A4_CMU_WATCHDOG_0                                       0x1CA4
#define P1C_A5_CMU_WATCHDOG_1                                       0x1CA5
#define P1C_A6_DPHY_RESERVED_0                                      0x1CA6
#define P1C_A7_DPHY_RESERVED_1                                      0x1CA7
#define P1C_A8_DPHY_RESERVED_2                                      0x1CA8


//--------------------------------------------------
// D1_D2 GDI PHY Power On Region (Page 1D)
//--------------------------------------------------
#define P1D_00_DIG_00                                               0x1D00
#define P1D_01_DIG_01                                               0x1D01
#define P1D_02_DIG_02                                               0x1D02
#define P1D_03_DIG_03                                               0x1D03
#define P1D_04_DIG_04                                               0x1D04
#define P1D_05_DIG_05                                               0x1D05
#define P1D_06_DIG_06                                               0x1D06
#define P1D_07_DIG_07                                               0x1D07
#define P1D_08_DIG_08                                               0x1D08
#define P1D_09_DIG_09                                               0x1D09
#define P1D_0A_DIG_10                                               0x1D0A
#define P1D_0E_SDM_04                                               0x1D0E
#define P1D_0F_WD                                                   0x1D0F
#define P1D_10_EQEN_TIMER                                           0x1D10
#define P1D_11_DATA_TIMER                                           0x1D11
#define P1D_12_ANA_CDR                                              0x1D12
#define P1D_13_CLK_DET                                              0x1D13
#define P1D_14_BANDGAP_00                                           0x1D14
#define P1D_15_BANDGAP_01                                           0x1D15
#define P1D_16_BANDGAP_02                                           0x1D16
#define P1D_17_IMPEDANCE_00                                         0x1D17
#define P1D_18_IMPEDANCE_01                                         0x1D18
#define P1D_19_IMPEDANCE_02                                         0x1D19
#define P1D_1A_IMPEDANCE_03                                         0x1D1A
#define P1D_1D_CMU_00                                               0x1D1D
#define P1D_1E_CMU_01                                               0x1D1E
#define P1D_1F_CMU_02                                               0x1D1F
#define P1D_20_CMU_03                                               0x1D20
#define P1D_21_CMU_04                                               0x1D21
#define P1D_22_CMU_05                                               0x1D22
#define P1D_23_CMU_06                                               0x1D23
#define P1D_24_CMU_07                                               0x1D24
#define P1D_25_CMU_08                                               0x1D25
#define P1D_26_KOFFSET_00                                           0x1D26
#define P1D_27_KOFFSET_01                                           0x1D27
#define P1D_28_KOFFSET_02                                           0x1D28
#define P1D_29_KOFFSET_03                                           0x1D29
#define P1D_2A_KOFFSET_04                                           0x1D2A
#define P1D_2B_KOFFSET_05                                           0x1D2B
#define P1D_2C_KOFFSET_06                                           0x1D2C
#define P1D_2D_KOFFSET_07                                           0x1D2D
#define P1D_2E_ANA_CDR_00                                           0x1D2E
#define P1D_2F_ANA_CDR_01                                           0x1D2F
#define P1D_30_ANA_CDR_02                                           0x1D30
#define P1D_31_ANA_CDR_03                                           0x1D31
#define P1D_32_ANA_CDR_04                                           0x1D32
#define P1D_33_ANA_CDR_05                                           0x1D33
#define P1D_34_ANA_CDR_06                                           0x1D34
#define P1D_35_ANA_CDR_07                                           0x1D35
#define P1D_36_ANA_CDR_08                                           0x1D36
#define P1D_37_ANA_CDR_09                                           0x1D37
#define P1D_38_TMDS_RESET                                           0x1D38
#define P1D_39_TMDS_CONT_0                                          0x1D39
#define P1D_3A_TMDS_CONT_1                                          0x1D3A
#define P1D_3B_TMDS_CONT_2                                          0x1D3B
#define P1D_3C_TMDS_CONT_3                                          0x1D3C
#define P1D_3D_TMDS_CONT_4                                          0x1D3D
#define P1D_3E_TMDS_CONT_5                                          0x1D3E
#define P1D_3F_TMDS_CONT_6                                          0x1D3F
#define P1D_40_EN_00                                                0x1D40
#define P1D_41_EN_01                                                0x1D41
#define P1D_42_EN_02                                                0x1D42
#define P1D_43_EN_03                                                0x1D43
#define P1D_44_ST_00                                                0x1D44
#define P1D_45_ST_01                                                0x1D45
#define P1D_46_ST_02                                                0x1D46
#define P1D_47_ST_03                                                0x1D47
#define P1D_48_ST_04                                                0x1D48
#define P1D_49_ERROR_COUNT_0                                        0x1D49
#define P1D_4A_ERROR_COUNT_1                                        0x1D4A
#define P1D_4B_ERROR_COUNT_2                                        0x1D4B
#define P1D_4C_ERROR_COUNT_3                                        0x1D4C
#define P1D_4D_ERROR_COUNT_4                                        0x1D4D
#define P1D_4E_ERROR_COUNT_5                                        0x1D4E
#define P1D_4F_DEBUG                                                0x1D4F
#define P1D_50_CDR_01                                               0x1D50
#define P1D_51_CDR_02                                               0x1D51
#define P1D_52_CDR_03                                               0x1D52
#define P1D_56_CDR_07                                               0x1D56
#define P1D_57_CDR_08                                               0x1D57
#define P1D_58_CDR_09                                               0x1D58
#define P1D_5C_TIMER_BER_0                                          0x1D5C
#define P1D_5D_TIMER_BER_1                                          0x1D5D


//--------------------------------------------------
// D1_D2 GDI DFE (Page 1D)
//--------------------------------------------------
#define P1D_A2_L0_LIMIT_INIT                                        0x1DA2
#define P1D_A3_L0_INIT_1                                            0x1DA3
#define P1D_A4_L0_INIT_2                                            0x1DA4
#define P1D_A5_L0_INIT_3                                            0x1DA5
#define P1D_A6_L0_INIT_4                                            0x1DA6
#define P1D_AA_L0_INIT_8                                            0x1DAA
#define P1D_AB_L0_STABLE_FLAG                                       0x1DAB
#define P1D_B2_L1_LIMIT_INIT                                        0x1DB2
#define P1D_B3_L1_INIT_1                                            0x1DB3
#define P1D_B4_L1_INIT_2                                            0x1DB4
#define P1D_B5_L1_INIT_3                                            0x1DB5
#define P1D_B6_L1_INIT_4                                            0x1DB6
#define P1D_BA_L1_INIT_8                                            0x1DBA
#define P1D_BB_L1_STABLE_FLAG                                       0x1DBB
#define P1D_C2_L2_LIMIT_INIT                                        0x1DC2
#define P1D_C3_L2_INIT_1                                            0x1DC3
#define P1D_C4_L2_INIT_2                                            0x1DC4
#define P1D_C5_L2_INIT_3                                            0x1DC5
#define P1D_C6_L2_INIT_4                                            0x1DC6
#define P1D_CA_L2_INIT_8                                            0x1DCA
#define P1D_CB_L2_STABLE_FLAG                                       0x1DCB
#define P1D_D2_L3_LIMIT_INIT                                        0x1DD2
#define P1D_D3_L3_INIT_1                                            0x1DD3
#define P1D_D4_L3_INIT_2                                            0x1DD4
#define P1D_D5_L3_INIT_3                                            0x1DD5
#define P1D_D6_L3_INIT_4                                            0x1DD6
#define P1D_DA_L3_INIT_8                                            0x1DDA
#define P1D_DB_L3_STABLE_FLAG                                       0x1DDB
#define P1D_EE_GRAY_DEC                                             0x1DEE
#define P1D_F0_COEF_1                                               0x1DF0
#define P1D_F1_COEF_2                                               0x1DF1
#define P1D_F2_COEF_3                                               0x1DF2
#define P1D_F3_COEF_4                                               0x1DF3
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
#define P20_FB_ROTATION_IN_DLY_H                                    0x20FB
#define P20_FC_ROTATION_IN_DLY_L                                    0x20FC
#define P20_FE_ROTATION_CTRL1                                       0x20FE
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
// Slave EMCU Step Trace Debug Interface (Page 21)
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
#define P2D_40_HDCP_2PX_ENCRYP_STS                                  0x2D40
#define P2D_41_HDCP_2PX_FCR                                         0x2D41


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
#define P31_05_FC_SD_CTRL                                           0x3105
#define P31_0C_CTS_FIFO_CTRL                                        0x310C
#define P31_0D_FC_INPUT_CLK_GATING                                  0x310D
#define P31_0E_FC_SYNC_CTRL                                         0x310E
#define P31_10_FC_EXT_CTRL                                          0x3110


//--------------------------------------------------
// YUV422 to YUV444 Conversion (Page 31)
//--------------------------------------------------
#define P31_40_YUV422_TO_444_PATH0                                  0x3140
#define P31_41_YUV422_TO_444_CTRL                                   0x3141
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
// I Domain Cyclic-Redundant-Check (Page 36)
//--------------------------------------------------
#define P36_00_I_CRC_CTRL                                           0x3600
#define P36_01_I_MAIN1_CRC_1                                        0x3601
#define P36_02_I_MAIN1_CRC_2                                        0x3602
#define P36_03_I_MAIN1_CRC_3                                        0x3603
#define P36_04_I_MAIN1_CRC_4                                        0x3604
#define P36_05_I_MAIN1_CRC_5                                        0x3605
#define P36_06_I_MAIN1_CRC_6                                        0x3606


//--------------------------------------------------
// D Domain Cyclic-Redundant-Check (Page 36)
//--------------------------------------------------
#define P36_2C_D_CRC_CTRL                                           0x362C
#define P36_2D_D_MAIN1_CRC_1                                        0x362D
#define P36_2E_D_MAIN1_CRC_2                                        0x362E
#define P36_2F_D_MAIN1_CRC_3                                        0x362F
#define P36_30_D_MAIN1_CRC_4                                        0x3630
#define P36_31_D_MAIN1_CRC_5                                        0x3631
#define P36_32_D_MAIN1_CRC_6                                        0x3632


//--------------------------------------------------
// M Domain Cyclic-Redundant-Check (Page 36)
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
// USB3 Retimer Clock Divider (Page 40)
//--------------------------------------------------
#define P40_0E_RETIMER_CLK_DIVIDER                                  0x400E
#define P40_0F_TOP_DUMMY6                                           0x400F


//--------------------------------------------------
// TXAB Port Control for Analog LVDS (Page 55)
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
#define P55_0C_LVDS_COMMON_AB_CTRL12                                0x550C
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
#define P55_39_LVDS_PORTB_CTRL9                                     0x5539
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
// ECDSA (Page 62)
//--------------------------------------------------
#define P62_50_ECDSA_CTRL                                           0x6250
#define P62_58_DIVIDEND_BYTE00                                      0x6258
#define P62_59_DIVIDEND_BYTE01                                      0x6259
#define P62_5A_DIVIDEND_BYTE02                                      0x625A
#define P62_5B_DIVIDEND_BYTE03                                      0x625B
#define P62_5C_DIVIDEND_BYTE04                                      0x625C
#define P62_5D_DIVIDEND_BYTE05                                      0x625D
#define P62_5E_DIVIDEND_BYTE06                                      0x625E
#define P62_5F_DIVIDEND_BYTE07                                      0x625F
#define P62_60_DIVIDEND_BYTE08                                      0x6260
#define P62_61_DIVIDEND_BYTE09                                      0x6261
#define P62_62_DIVIDEND_BYTE0A                                      0x6262
#define P62_63_DIVIDEND_BYTE0B                                      0x6263
#define P62_64_DIVIDEND_BYTE0C                                      0x6264
#define P62_65_DIVIDEND_BYTE0D                                      0x6265
#define P62_66_DIVIDEND_BYTE0E                                      0x6266
#define P62_67_DIVIDEND_BYTE0F                                      0x6267
#define P62_68_DIVIDEND_BYTE10                                      0x6268
#define P62_69_DIVIDEND_BYTE11                                      0x6269
#define P62_6A_DIVIDEND_BYTE12                                      0x626A
#define P62_6B_DIVIDEND_BYTE13                                      0x626B
#define P62_6C_DIVIDEND_BYTE14                                      0x626C
#define P62_6D_DIVIDEND_BYTE15                                      0x626D
#define P62_6E_DIVIDEND_BYTE16                                      0x626E
#define P62_6F_DIVIDEND_BYTE17                                      0x626F
#define P62_70_DIVIDEND_BYTE18                                      0x6270
#define P62_71_DIVIDEND_BYTE19                                      0x6271
#define P62_72_DIVIDEND_BYTE1A                                      0x6272
#define P62_73_DIVIDEND_BYTE1B                                      0x6273
#define P62_74_DIVIDEND_BYTE1C                                      0x6274
#define P62_75_DIVIDEND_BYTE1D                                      0x6275
#define P62_76_DIVIDEND_BYTE1E                                      0x6276
#define P62_77_DIVIDEND_BYTE1F                                      0x6277
#define P62_78_DIVIDEND_BYTE20                                      0x6278
#define P62_79_DIVIDEND_BYTE21                                      0x6279
#define P62_7A_DIVIDEND_BYTE22                                      0x627A
#define P62_7B_DIVIDEND_BYTE23                                      0x627B
#define P62_7C_DIVIDEND_BYTE24                                      0x627C
#define P62_7D_DIVIDEND_BYTE25                                      0x627D
#define P62_7E_DIVIDEND_BYTE26                                      0x627E
#define P62_7F_DIVIDEND_BYTE27                                      0x627F
#define P62_80_DIVIDEND_BYTE28                                      0x6280
#define P62_81_DIVIDEND_BYTE29                                      0x6281
#define P62_82_DIVIDEND_BYTE2A                                      0x6282
#define P62_83_DIVIDEND_BYTE2B                                      0x6283
#define P62_84_DIVIDEND_BYTE2C                                      0x6284
#define P62_85_DIVIDEND_BYTE2D                                      0x6285
#define P62_86_DIVIDEND_BYTE2E                                      0x6286
#define P62_87_DIVIDEND_BYTE2F                                      0x6287
#define P62_88_DIVIDEND_BYTE30                                      0x6288
#define P62_89_DIVIDEND_BYTE31                                      0x6289
#define P62_8A_DIVIDEND_BYTE32                                      0x628A
#define P62_8B_DIVIDEND_BYTE33                                      0x628B
#define P62_8C_DIVIDEND_BYTE34                                      0x628C
#define P62_8D_DIVIDEND_BYTE35                                      0x628D
#define P62_8E_DIVIDEND_BYTE36                                      0x628E
#define P62_8F_DIVIDEND_BYTE37                                      0x628F
#define P62_90_DIVIDEND_BYTE38                                      0x6290
#define P62_91_DIVIDEND_BYTE39                                      0x6291
#define P62_92_DIVIDEND_BYTE3A                                      0x6292
#define P62_93_DIVIDEND_BYTE3B                                      0x6293
#define P62_94_DIVIDEND_BYTE3C                                      0x6294
#define P62_95_DIVIDEND_BYTE3D                                      0x6295
#define P62_96_DIVIDEND_BYTE3E                                      0x6296
#define P62_97_DIVIDEND_BYTE3F                                      0x6297
#define P62_A0_DIVISOR_BYTE00                                       0x62A0
#define P62_A1_DIVISOR_BYTE01                                       0x62A1
#define P62_A2_DIVISOR_BYTE02                                       0x62A2
#define P62_A3_DIVISOR_BYTE03                                       0x62A3
#define P62_A4_DIVISOR_BYTE04                                       0x62A4
#define P62_A5_DIVISOR_BYTE05                                       0x62A5
#define P62_A6_DIVISOR_BYTE06                                       0x62A6
#define P62_A7_DIVISOR_BYTE07                                       0x62A7
#define P62_A8_DIVISOR_BYTE08                                       0x62A8
#define P62_A9_DIVISOR_BYTE09                                       0x62A9
#define P62_AA_DIVISOR_BYTE0A                                       0x62AA
#define P62_AB_DIVISOR_BYTE0B                                       0x62AB
#define P62_AC_DIVISOR_BYTE0C                                       0x62AC
#define P62_AD_DIVISOR_BYTE0D                                       0x62AD
#define P62_AE_DIVISOR_BYTE0E                                       0x62AE
#define P62_AF_DIVISOR_BYTE0F                                       0x62AF
#define P62_B0_DIVISOR_BYTE10                                       0x62B0
#define P62_B1_DIVISOR_BYTE11                                       0x62B1
#define P62_B2_DIVISOR_BYTE12                                       0x62B2
#define P62_B3_DIVISOR_BYTE13                                       0x62B3
#define P62_B4_DIVISOR_BYTE14                                       0x62B4
#define P62_B5_DIVISOR_BYTE15                                       0x62B5
#define P62_B6_DIVISOR_BYTE16                                       0x62B6
#define P62_B7_DIVISOR_BYTE17                                       0x62B7
#define P62_B8_DIVISOR_BYTE18                                       0x62B8
#define P62_B9_DIVISOR_BYTE19                                       0x62B9
#define P62_BA_DIVISOR_BYTE1A                                       0x62BA
#define P62_BB_DIVISOR_BYTE1B                                       0x62BB
#define P62_BC_DIVISOR_BYTE1C                                       0x62BC
#define P62_BD_DIVISOR_BYTE1D                                       0x62BD
#define P62_BE_DIVISOR_BYTE1E                                       0x62BE
#define P62_BF_DIVISOR_BYTE1F                                       0x62BF
#define P62_C0_REMAINDER_BYTE00                                     0x62C0
#define P62_C1_REMAINDER_BYTE01                                     0x62C1
#define P62_C2_REMAINDER_BYTE02                                     0x62C2
#define P62_C3_REMAINDER_BYTE03                                     0x62C3
#define P62_C4_REMAINDER_BYTE04                                     0x62C4
#define P62_C5_REMAINDER_BYTE05                                     0x62C5
#define P62_C6_REMAINDER_BYTE06                                     0x62C6
#define P62_C7_REMAINDER_BYTE07                                     0x62C7
#define P62_C8_REMAINDER_BYTE08                                     0x62C8
#define P62_C9_REMAINDER_BYTE09                                     0x62C9
#define P62_CA_REMAINDER_BYTE0A                                     0x62CA
#define P62_CB_REMAINDER_BYTE0B                                     0x62CB
#define P62_CC_REMAINDER_BYTE0C                                     0x62CC
#define P62_CD_REMAINDER_BYTE0D                                     0x62CD
#define P62_CE_REMAINDER_BYTE0E                                     0x62CE
#define P62_CF_REMAINDER_BYTE0F                                     0x62CF
#define P62_D0_REMAINDER_BYTE10                                     0x62D0
#define P62_D1_REMAINDER_BYTE11                                     0x62D1
#define P62_D2_REMAINDER_BYTE12                                     0x62D2
#define P62_D3_REMAINDER_BYTE13                                     0x62D3
#define P62_D4_REMAINDER_BYTE14                                     0x62D4
#define P62_D5_REMAINDER_BYTE15                                     0x62D5
#define P62_D6_REMAINDER_BYTE16                                     0x62D6
#define P62_D7_REMAINDER_BYTE17                                     0x62D7
#define P62_D8_REMAINDER_BYTE18                                     0x62D8
#define P62_D9_REMAINDER_BYTE19                                     0x62D9
#define P62_DA_REMAINDER_BYTE1A                                     0x62DA
#define P62_DB_REMAINDER_BYTE1B                                     0x62DB
#define P62_DC_REMAINDER_BYTE1C                                     0x62DC
#define P62_DD_REMAINDER_BYTE1D                                     0x62DD
#define P62_DE_REMAINDER_BYTE1E                                     0x62DE
#define P62_DF_REMAINDER_BYTE1F                                     0x62DF


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
// Bill Board Port Control (Page 64)
//--------------------------------------------------
#define P64_00_HS_USP_CTL                                           0x6400
#define P64_04_HS_USP_STS                                           0x6404
#define P64_08_HS_USP_USTM                                          0x6408
#define P64_09_HS_USP_DSTM                                          0x6409
#define P64_10_HS_USP_CFG0                                          0x6410
#define P64_11_HS_USP_CFG1                                          0x6411
#define P64_12_HS_USP_CFG2                                          0x6412
#define P64_20_HS_USP_IRQ                                           0x6420
#define P64_21_HS_USP_IRQ_EN                                        0x6421
#define P64_30_HS_USP_LPM_CTL                                       0x6430
#define P64_40_HS_HSEOF_CFG                                         0x6440
#define P64_41_HS_FSEOF_CFG                                         0x6441
#define P64_50_HS_TT_CFG0                                           0x6450
#define P64_51_HS_TT_CFG1                                           0x6451
#define P64_52_HS_DEV_G_STA                                         0x6452
#define P64_53_HS_UP_TEST                                           0x6453
#define P64_54_HS_DEV_ADDR                                          0x6454
#define P64_55_HS_CLR_HUB                                           0x6455
#define P64_56_HS_DEV_G_CFG                                         0x6456
#define P64_57_HS_G_HUB_ST                                          0x6457
#define P64_58_HS_MTT_CFG                                           0x6458
#define P64_59_HS_DSP_CFG                                           0x6459
#define P64_60_HS_PIE_CFG                                           0x6460
#define P64_70_HS_USP_DUMMY_CELL0                                   0x6470
#define P64_71_HS_USP_DUMMY_CELL1                                   0x6471
#define P64_72_HS_TT_CFG2                                           0x6472
#define P64_73_HS_CLK2M_DIV                                         0x6473
#define P64_74_HS_USB2_RESET                                        0x6474


//--------------------------------------------------
// Bill Board USB1.1 PHY (Page 64)
//--------------------------------------------------
#define P64_A0_USB20_CTRL_0                                         0x64A0
#define P64_A1_USB20_CTRL_1                                         0x64A1
#define P64_A2_USB20_CTRL_2                                         0x64A2
#define P64_A3_USB20_CTRL_3                                         0x64A3


//--------------------------------------------------
// BB PLL Analog (Page 64)
//--------------------------------------------------
#define P64_C0_CMU480_CTRL0                                         0x64C0
#define P64_C1_CMU480_CTRL1                                         0x64C1
#define P64_C2_CMU480_CTRL2                                         0x64C2
#define P64_C3_CMU480_CTRL3                                         0x64C3


//--------------------------------------------------
// BB PLL Digital (Page 64)
//--------------------------------------------------
#define P64_C6_CMU480_PLL_DIV_CFG0                                  0x64C6
#define P64_C7_CMU480_PLL_DIV_CFG1                                  0x64C7
#define P64_C8_CMU480_PLL_DIV_CFG2                                  0x64C8
#define P64_C9_NXTAL_CFG1                                           0x64C9
#define P64_CA_NXTAL_CFG2                                           0x64CA
#define P64_CB_XTAL_CFG0                                            0x64CB
#define P64_CC_XTAL_CFG1                                            0x64CC
#define P64_CD_XTAL_CFG2                                            0x64CD
#define P64_CE_XTAL_CFG3                                            0x64CE
#define P64_CF_XTAL_CFG4                                            0x64CF
#define P64_D0_XTAL_CFG5                                            0x64D0
#define P64_D1_XTAL_CFG6                                            0x64D1
#define P64_D2_XTAL_CFG7                                            0x64D2
#define P64_D3_XTAL_CFG8                                            0x64D3


//--------------------------------------------------
// DP Rx TypeC Power Delivery Top (Page 65)
//--------------------------------------------------
#define P65_00_PHY_STATE_H                                          0x6500
#define P65_01_PHY_STATE_L                                          0x6501
#define P65_02_PD_BMC_ENABLE                                        0x6502
#define P65_03_PD_TOP_RST                                           0x6503
#define P65_05_PD_PHY_IDLE_INT                                      0x6505
#define P65_06_PD_PHY_IDLE_CFG0                                     0x6506
#define P65_07_PD_PHY_IDLE_CFG1                                     0x6507
#define P65_08_PD_PHY_INTERFRAME_CFG0                               0x6508
#define P65_09_PD_PHY_INTERFRAME_CFG1                               0x6509
#define P65_0A_PD_PHY_TRANSITION_CFG                                0x650A
#define P65_0B_PD_SYS_CLK_CFG                                       0x650B
#define P65_0C_PD_1M_CLK_CFG                                        0x650C
#define P65_0D_PD_1K_CLK_CFG0                                       0x650D
#define P65_0E_PD_1K_CLK_CFG1                                       0x650E
#define P65_10_VENDOR_SPECIFIC_KCODE_1                              0x6510
#define P65_11_VENDOR_SPECIFIC_KCODE_2                              0x6511
#define P65_12_VENDOR_SPECIFIC_KCODE_3                              0x6512
#define P65_13_VENDOR_SPECIFIC_SOP1_CFG0                            0x6513
#define P65_14_VENDOR_SPECIFIC_SOP1_CFG1                            0x6514
#define P65_15_VENDOR_SPECIFIC_SOP2_CFG0                            0x6515
#define P65_16_VENDOR_SPECIFIC_SOP2_CFG1                            0x6516
#define P65_17_VENDOR_SPECIFIC_SOP3_CFG0                            0x6517
#define P65_18_0X6518                                               0x6518
#define P65_F0_PD_BIST_CFG                                          0x65F0
#define P65_F1_PD_BIST_PATTERN                                      0x65F1
#define P65_F2_FIX_PATTERN_5BIT                                     0x65F2
#define P65_F5_PD_BIST_ERROR_CNT1                                   0x65F5
#define P65_F6_PD_BIST_ERROR_CNT0                                   0x65F6
#define P65_F7_PD_SRAM_BIST0                                        0x65F7
#define P65_F8_PD_SRAM_BIST1                                        0x65F8


//--------------------------------------------------
// DP Rx TypeC Power Delivery Rx (Page 65)
//--------------------------------------------------
#define P65_20_RX_STATE_MACHINE_H                                   0x6520
#define P65_21_RX_STATE_MACHINE_L                                   0x6521
#define P65_22_BMC_RX_CFG                                           0x6522
#define P65_23_BMC_TBIT_LOW_BND1                                    0x6523
#define P65_24_BMC_TBIT_LOW_BND0                                    0x6524
#define P65_25_BMC_TBIT_UP_BND1                                     0x6525
#define P65_26_BMC_TBIT_UP_BND0                                     0x6526
#define P65_27_BMC_RX_TBIT_CFG                                      0x6527
#define P65_28_BMC_RX_HW_HT                                         0x6528
#define P65_29_BMC_RX_HW_T1                                         0x6529
#define P65_2A_BMC_RX_HW_T0                                         0x652A
#define P65_2B_BMC_RX_FW_TBIT1                                      0x652B
#define P65_2C_BMC_RX_FW_TBIT0                                      0x652C
#define P65_2D_BMC_RX_PREAMBLE_LN                                   0x652D
#define P65_2E_RX_PHY_ERR_INT                                       0x652E
#define P65_2F_RX_PHY_RCV_TIMEOUT_CFG                               0x652F
#define P65_30_RX_MSG_ID_CNT0                                       0x6530
#define P65_31_RX_MSG_ID_CNT1                                       0x6531
#define P65_32_RX_MSG_ID_RST                                        0x6532
#define P65_34_RX_VALID_MSG_TYPE                                    0x6534
#define P65_35_RX_PORT_ROLE                                         0x6535
#define P65_36_RX_SPEC_VER                                          0x6536
#define P65_37_RX_PHY_BIT_REVERSE                                   0x6537
#define P65_38_RX_PROTOCOL_CFG                                      0x6538
#define P65_39_RX_ERROR_FIFO_CLR_CTRL                               0x6539
#define P65_3A_RX_CRC_RESPONSE_CTRL                                 0x653A
#define P65_3B_RX_HOTKEY_MSG_CFG                                    0x653B
#define P65_3C_RX_VS0_MSG_HEADER_CFG0                               0x653C
#define P65_3D_RX_VS0_MSG_HEADER_CFG1                               0x653D
#define P65_3E_RX_VS1_MSG_HEADER_CFG0                               0x653E
#define P65_3F_RX_VS1_MSG_HEADER_CFG1                               0x653F
#define P65_40_RX_FIFO_CTRL                                         0x6540
#define P65_41_RX_FIFO_EMPTY_INFO                                   0x6541
#define P65_42_RX_FIFO_GENERAL_INFO                                 0x6542
#define P65_43_RX_RCV_STATUS_INT                                    0x6543
#define P65_50_RX_FIFO0_RCV_MSG_INT                                 0x6550
#define P65_51_RX_FIFO0_RCV_ERR_INT                                 0x6551
#define P65_52_RX_FIFO0_RCV_ERR_INT_EN                              0x6552
#define P65_53_RX_FIFO0_MSG_MIS_FLAG                                0x6553
#define P65_54_RX_FIFO0_RCV_SOP                                     0x6554
#define P65_55_RX_FIFO0_KCODE_STATUS                                0x6555
#define P65_56_RX_FIFO0_MSG_HEADER0                                 0x6556
#define P65_57_RX_FIFO0_MSG_HEADER1                                 0x6557
#define P65_58_RX_FIFO0_DUMMY_CELL                                  0x6558
#define P65_59_RX_FIFO0_ADDR                                        0x6559
#define P65_5A_RX_FIFO0_DATA                                        0x655A
#define P65_5B_RX_FIFO0_DATA_LEN                                    0x655B
#define P65_60_RX_FIFO0_SP_MSG_INT                                  0x6560
#define P65_62_RX_FIFO0_MSG_INT                                     0x6562
#define P65_70_RX_FIFO1_RCV_MSG_INT                                 0x6570
#define P65_71_RX_FIFO1_RCV_ERR_INT                                 0x6571
#define P65_72_RX_FIFO1_RCV_ERR_INT_EN                              0x6572
#define P65_73_RX_FIFO1_MSG_MIS_FLAG                                0x6573
#define P65_74_RX_FIFO1_RCV_SOP                                     0x6574
#define P65_75_RX_FIFO1_KCODE_STATUS                                0x6575
#define P65_76_RX_FIFO1_MSG_HEADER0                                 0x6576
#define P65_77_RX_FIFO1_MSG_HEADER1                                 0x6577
#define P65_78_RX_FIFO1_DUMMY                                       0x6578
#define P65_79_RX_FIFO1_ADDR                                        0x6579
#define P65_7A_RX_FIFO1_DATA                                        0x657A
#define P65_7B_RX_FIFO1_DATA_LEN                                    0x657B
#define P65_80_RX_FIFO1_SP_MSG_INT                                  0x6580
#define P65_82_RX_FIFO1_MSG_INT                                     0x6582
#define P65_90_RX_FIFO2_RCV_MSG_INT                                 0x6590
#define P65_91_RX_FIFO2_RCV_ERR_INT                                 0x6591
#define P65_92_RX_FIFO2_RCV_ERR_INT_EN                              0x6592
#define P65_93_RX_FIFO2_MSG_MIS_FLAG                                0x6593
#define P65_94_RX_FIFO2_RCV_SOP                                     0x6594
#define P65_95_RX_FIFO2_KCODE_STATUS                                0x6595
#define P65_96_RX_FIFO2_MSG_HEADER0                                 0x6596
#define P65_97_RX_FIFO2_MSG_HEADER1                                 0x6597
#define P65_98_RX_FIFO2_DUMMY                                       0x6598
#define P65_99_RX_FIFO2_ADDR                                        0x6599
#define P65_9A_RX_FIFO2_DATA                                        0x659A
#define P65_9B_RX_FIFO2_DATA_LEN                                    0x659B
#define P65_A0_RX_FIFO2_SP_MSG_INT                                  0x65A0
#define P65_A2_RX_FIFO2_MSG_INT                                     0x65A2


//--------------------------------------------------
// DP Rx TypeC Power Delivery Listen Mode (Page 65)
//--------------------------------------------------
#define P65_B0_BMC_LISTEN_MODE_EN                                   0x65B0
#define P65_B1_PRE_DUMMY_BYTE1                                      0x65B1
#define P65_B2_PRE_DUMMY_BYTE2                                      0x65B2
#define P65_B3_PRE_DUMMY_BYTE3                                      0x65B3
#define P65_B4_PRE_DUMMY_4BIT                                       0x65B4
#define P65_B5_POST_DUMMY_BYTE1                                     0x65B5
#define P65_B6_POST_DUMMY_BYTE2                                     0x65B6
#define P65_B7_POST_DUMMY_BYTE3                                     0x65B7
#define P65_B8_POST_DUMMY_4BIT                                      0x65B8
#define P65_B9_BMC_LISTEN_MODE_DATA_PORT                            0x65B9
#define P65_BA_BMC_LISTEN_MODE_FIFO_LEN                             0x65BA
#define P65_BB_BMC_LISTEN_MODE_FIFO_WPTR                            0x65BB
#define P65_BC_BMC_LISTEN_MODE_FIFO_RPTR                            0x65BC
#define P65_BD_BMC_LISTEN_MODE_FIFO_CFG0                            0x65BD
#define P65_BE_BMC_LISTEN_MODE_FIFO_CFG1                            0x65BE
#define P65_BF_BMC_LISTEN_MODE_FIFO_CFG2                            0x65BF
#define P65_C0_BMC_LISTEN_MODE_IRQ_EN                               0x65C0
#define P65_C1_BMC_LISTEN_MODE_IRQ                                  0x65C1


//--------------------------------------------------
// DP Rx TypeC Power Delivery Tx (Page 65)
//--------------------------------------------------
#define P65_D0_TX_PRL_STATE_H                                       0x65D0
#define P65_D1_TX_PRL_STATE_L                                       0x65D1
#define P65_D3_BMC_TX_TBIT_CFG                                      0x65D3
#define P65_D4_BMC_TX_FW_HT                                         0x65D4
#define P65_D5_BMC_TX_FW_T1                                         0x65D5
#define P65_D6_BMC_TX_FW_T0                                         0x65D6
#define P65_D7_BMC_TX_PREAMBLE_LN                                   0x65D7
#define P65_D8_TX_BMC_HOLD_LOW_CNT                                  0x65D8
#define P65_D9_TX_BMC_START_DRIVE_CNT                               0x65D9
#define P65_DA_TX_TRANSMIT_CTRL                                     0x65DA
#define P65_DB_TX_PHY_TRANS_INT                                     0x65DB
#define P65_DC_TX_PD_MSG_INT                                        0x65DC
#define P65_DD_TX_PD_MSG_INT_EN                                     0x65DD
#define P65_E0_TX_PACKET_CFG                                        0x65E0
#define P65_E1_TX_PHY_BIT_REVERSE                                   0x65E1
#define P65_E2_TX_MSG_ID_CNT0                                       0x65E2
#define P65_E3_TX_MSG_ID_CNT1                                       0x65E3
#define P65_E4_TX_MSG_ID_RST                                        0x65E4
#define P65_E5_TX_FIFO_MSG_HEADER0                                  0x65E5
#define P65_E6_TX_FIFO_MSG_HEADER1                                  0x65E6
#define P65_E8_TX_FIFO_CTRL                                         0x65E8
#define P65_E9_TX_FIFO_ADDR                                         0x65E9
#define P65_EA_TX_FIFO_DATA                                         0x65EA
#define P65_EC_TX_PD_RTY_CNT                                        0x65EC
#define P65_EE_TX_PD_CRC_TIMER_CFG                                  0x65EE


//--------------------------------------------------
// DP Rx TypeC CC Logic (Page 66)
//--------------------------------------------------
#define P66_00_GLOBAL_CTL                                           0x6600
#define P66_01_SYS_CLK_SRC_CFG                                      0x6601
#define P66_02_1M_CLK_SRC_CFG                                       0x6602
#define P66_03_1K_CLK_SRC_CFG_0                                     0x6603
#define P66_04_1K_CLK_SRC_CFG_1                                     0x6604
#define P66_05_CC1_DGH_LV                                           0x6605
#define P66_06_CC2_DGH_LV                                           0x6606
#define P66_07_TPC_TCC_DB_TIME                                      0x6607
#define P66_08_TPC_TPD_DB_TIME                                      0x6608
#define P66_09_TPC_VS1_DB_TIME_H                                    0x6609
#define P66_0A_TPC_VS1_DB_TIME_L                                    0x660A
#define P66_0C_TPC_CC_CTRL                                          0x660C
#define P66_0D_TPC_OCP_CTRL                                         0x660D
#define P66_25_BMC_TX_RX_CFG                                        0x6625
#define P66_26_BMC_RX_SIG                                           0x6626
#define P66_27_BMC_TX_CUR                                           0x6627
#define P66_28_VTH_SEL                                              0x6628
#define P66_2A_CC_ANA_DET_R                                         0x662A
#define P66_2B_CC_DIG_DET_R                                         0x662B
#define P66_2C_CC_R_CHG_INT                                         0x662C
#define P66_2E_CC1_VTH_MUX                                          0x662E
#define P66_2F_CC2_VTH_MUX                                          0x662F
#define P66_30_CC_HW_MODE_CTRL                                      0x6630
#define P66_31_CC_HW_MODE_CFG                                       0x6631
#define P66_33_CC_HW_FSM                                            0x6633
#define P66_34_CC_HW_STATE_CTRL                                     0x6634
#define P66_35_CC_HW_STATE_TRANSIT                                  0x6635
#define P66_37_CC_HW_Z_CFG                                          0x6637
#define P66_38_CC_HW_DRP_SRC_TM                                     0x6638
#define P66_39_CC_HW_DRP_SNK_TM                                     0x6639
#define P66_3A_CC_HW_TRY_SRC_TM                                     0x663A
#define P66_3D_HW_DGH_EN                                            0x663D
#define P66_3E_HW_DGH_TH                                            0x663E
#define P66_3F_STABLE_TIMER_TH                                      0x663F
#define P66_40_CC_FW_DET_CTRL                                       0x6640
#define P66_41_CC_FW_DET_INT                                        0x6641
#define P66_42_CC_FW_DET_INT_EN                                     0x6642
#define P66_44_FW_SRC_EQ_DET_COND                                   0x6644
#define P66_45_FW_SNK_EQ_DET_COND                                   0x6645
#define P66_48_FW_CC1_EQ_DB_H                                       0x6648
#define P66_49_FW_CC1_EQ_DB_L                                       0x6649
#define P66_4A_FW_CC2_EQ_DB_H                                       0x664A
#define P66_4B_FW_CC2_EQ_DB_L                                       0x664B
#define P66_4C_FW_CC1_NEQ_DB_H                                      0x664C
#define P66_4D_FW_CC1_NEQ_DB_L                                      0x664D
#define P66_4E_FW_CC2_NEQ_DB_H                                      0x664E
#define P66_4F_FW_CC2_NEQ_DB_L                                      0x664F
#define P66_50_DBCC_DGH_EN                                          0x6650
#define P66_51_DBCC_DGH_TH                                          0x6651
#define P66_52_DBCC_SRC_DB_SEL0                                     0x6652
#define P66_53_DBCC_SRC_DB_SEL1                                     0x6653
#define P66_54_DBCC_SRC_DB_SEL2                                     0x6654
#define P66_55_DBCC_SNK_DB_SEL                                      0x6655
#define P66_56_DBCC_SRC_DET_COND0                                   0x6656
#define P66_57_DBCC_SRC_DET_COND1                                   0x6657
#define P66_58_DBCC_SNK_DET_COND                                    0x6658
#define P66_59_DBCC_R_DET                                           0x6659
#define P66_5A_CC_FW_CC1_Z_CFG                                      0x665A
#define P66_5B_CC_FW_CC2_Z_CFG                                      0x665B
#define P66_60_FRS_CTRL                                             0x6660
#define P66_61_FRS_490MV_DGH                                        0x6661
#define P66_62_FRS_VBUS_DGH                                         0x6662
#define P66_63_SRC_FRS_DRV_TM                                       0x6663
#define P66_64_SNK_FRS_DET_TM                                       0x6664
#define P66_65_SNK_FRS_VTH_MODE                                     0x6665
#define P66_66_SRC_FRS_INT                                          0x6666
#define P66_67_SNK_FRS_INT                                          0x6667
#define P66_68_FRS_BYPASS_MODE                                      0x6668
#define P66_70_ANA_OCDET                                            0x6670
#define P66_71_CC1_VCONN_OCP_INT                                    0x6671
#define P66_72_CC2_VCONN_OCP_INT                                    0x6672
#define P66_73_VCONN_OCP_TIMER1                                     0x6673
#define P66_74_VCONN_OCP_TIMER2                                     0x6674
#define P66_75_VCONN_OCP_TIMER3                                     0x6675
#define P66_76_VCONN_OCP_TIMER4                                     0x6676
#define P66_77_VCONN_OCP_TIMER5                                     0x6677
#define P66_7F_TEST_PIN_SEL                                         0x667F


//--------------------------------------------------
// DP Rx TypeC CC Logic AIF Config (Page 66)
//--------------------------------------------------
#define P66_0E_TPC_OPC_CFG_0                                        0x660E
#define P66_0F_TPC_OPC_CFG_1                                        0x660F
#define P66_10_CC1_VTH_CFG_0                                        0x6610
#define P66_11_CC1_VTH_CFG_1                                        0x6611
#define P66_12_CC1_VTH_CFG_2                                        0x6612
#define P66_13_CC1_VTH_CFG_3                                        0x6613
#define P66_14_CC2_VTH_CFG_0                                        0x6614
#define P66_15_CC2_VTH_CFG_1                                        0x6615
#define P66_16_CC2_VTH_CFG_2                                        0x6616
#define P66_17_CC2_VTH_CFG_3                                        0x6617
#define P66_18_TPC_CC1_RD_CFG                                       0x6618
#define P66_19_TPC_CC1_RP4P7K_CFG                                   0x6619
#define P66_1A_TPC_CC1_RP12K_CFG                                    0x661A
#define P66_1B_TPC_CC1_RP36K_CFG                                    0x661B
#define P66_1C_TPC_CC2_RD_CFG                                       0x661C
#define P66_1D_TPC_CC2_RP4P7K_CFG                                   0x661D
#define P66_1E_TPC_CC2_RP12K_CFG                                    0x661E
#define P66_1F_TPC_CC2_RP36K_CFG                                    0x661F
#define P66_20_BMC_RX_SNK_VTH                                       0x6620
#define P66_21_BMC_RX_SRC_VTH                                       0x6621
#define P66_22_BMC_TX_CFG                                           0x6622
#define P66_23_BMC_TX_DRV_TM                                        0x6623
#define P66_24_BMC_LPF                                              0x6624


//--------------------------------------------------
// ADI Global Control (Page 6F)
//--------------------------------------------------
#define P6F_00_MUX_DIG_OUT                                          0x6F00
#define P6F_01_MUX_DA_DVC_IN                                        0x6F01
#define P6F_03_MUX_TST_OUT                                          0x6F03
#define P6F_07_ADI_DUMMY_0                                          0x6F07
#define P6F_09_AUX_MAP_DDC                                          0x6F09
#define P6F_10_ADI_IRQ_CTRL                                         0x6F10
#define P6F_11_ADI_DUMMY_1                                          0x6F11


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
#define P6F_27_USB_TYPEC_POWER_CTRL                                 0x6F27
#define P6F_28_USB3_RETIMER_POWER_CTRL                              0x6F28
#define P6F_29_DP_U3_DPHY_POWER_CTRL                                0x6F29
#define P6F_2A_ANALOG_APHY_POWER_CTRL                               0x6F2A


//--------------------------------------------------
// USB TypeC 10 Bit ADC (Page 7F)
//--------------------------------------------------
#define P7F_00_10B_ADC_CTL                                          0x7F00
#define P7F_01_10B_ADC_CH_EN                                        0x7F01
#define P7F_02_10B_ADC_OUTPUT                                       0x7F02
#define P7F_03_10B_ADC_CLK_CLRT                                     0x7F03
#define P7F_05_10B_ADC_AVE_CTRL                                     0x7F05
#define P7F_07_10B_ADC_SW_TM0                                       0x7F07
#define P7F_08_10B_ADC_SW_TM1                                       0x7F08
#define P7F_09_10B_ADC_IDLE_TM0                                     0x7F09
#define P7F_0A_10B_ADC_IDLE_TM1                                     0x7F0A
#define P7F_0B_10B_ADC_A0_DEB_CLRT                                  0x7F0B
#define P7F_0C_10B_ADC_A1_DEB_CLRT                                  0x7F0C
#define P7F_0D_10B_ADC_A2_DEB_CLRT                                  0x7F0D
#define P7F_0E_10B_ADC_A3_DEB_CLRT                                  0x7F0E
#define P7F_0F_10B_ADC_A4_DEB_CLRT                                  0x7F0F
#define P7F_10_10B_ADC_A0_RSLT_H                                    0x7F10
#define P7F_11_10B_ADC_A0_RSLT_L                                    0x7F11
#define P7F_12_10B_ADC_A1_RSLT_H                                    0x7F12
#define P7F_13_10B_ADC_A1_RSLT_L                                    0x7F13
#define P7F_14_10B_ADC_A2_RSLT_H                                    0x7F14
#define P7F_15_10B_ADC_A2_RSLT_L                                    0x7F15
#define P7F_16_10B_ADC_A3_RSLT_H                                    0x7F16
#define P7F_17_10B_ADC_A3_RSLT_L                                    0x7F17
#define P7F_18_10B_ADC_A4_RSLT_H                                    0x7F18
#define P7F_19_10B_ADC_A4_RSLT_L                                    0x7F19
#define P7F_1A_10B_ADC_COMP_INT                                     0x7F1A
#define P7F_1B_10B_ADC_COMP_INT_EN                                  0x7F1B
#define P7F_1C_10B_ADC_COMP_THR_CTRL                                0x7F1C
#define P7F_20_10B_ADC_A0_HIGH_THR1                                 0x7F20
#define P7F_21_10B_ADC_A0_HIGH_THR2                                 0x7F21
#define P7F_22_10B_ADC_A1_HIGH_THR1                                 0x7F22
#define P7F_23_10B_ADC_A1_HIGH_THR2                                 0x7F23
#define P7F_24_10B_ADC_A2_HIGH_THR1                                 0x7F24
#define P7F_25_10B_ADC_A2_HIGH_THR2                                 0x7F25
#define P7F_26_10B_ADC_A3_HIGH_THR1                                 0x7F26
#define P7F_27_10B_ADC_A3_HIGH_THR2                                 0x7F27
#define P7F_28_10B_ADC_A4_HIGH_THR1                                 0x7F28
#define P7F_29_10B_ADC_A4_HIGH_THR2                                 0x7F29
#define P7F_30_10B_ADC_A0_LOW_THR1                                  0x7F30
#define P7F_31_10B_ADC_A0_LOW_THR2                                  0x7F31
#define P7F_32_10B_ADC_A1_LOW_THR1                                  0x7F32
#define P7F_33_10B_ADC_A1_LOW_THR2                                  0x7F33
#define P7F_34_10B_ADC_A2_LOW_THR1                                  0x7F34
#define P7F_35_10B_ADC_A2_LOW_THR2                                  0x7F35
#define P7F_36_10B_ADC_A3_LOW_THR1                                  0x7F36
#define P7F_37_10B_ADC_A3_LOW_THR2                                  0x7F37
#define P7F_38_10B_ADC_A4_LOW_THR1                                  0x7F38
#define P7F_39_10B_ADC_A4_LOW_THR2                                  0x7F39
#define P7F_3A_10B_ADC_VBUS_INT                                     0x7F3A
#define P7F_3B_10B_ADC_VBUS_INT_EN                                  0x7F3B
#define P7F_3C_10B_ADC_A0_VBUS_ON_DEB                               0x7F3C
#define P7F_3D_10B_ADC_A2_VBUS_ON_DEB                               0x7F3D
#define P7F_3E_10B_ADC_A4_VBUS_ON_DEB                               0x7F3E
#define P7F_3F_10B_ADC_A0_VBUS_OFF_DEB                              0x7F3F
#define P7F_40_10B_ADC_A2_VBUS_OFF_DEB                              0x7F40
#define P7F_41_10B_ADC_A4_VBUS_OFF_DEB                              0x7F41
#define P7F_42_10B_ADC_A0_VBUS_ON_THR1                              0x7F42
#define P7F_43_10B_ADC_A0_VBUS_ON_THR2                              0x7F43
#define P7F_44_10B_ADC_A2_VBUS_ON_THR1                              0x7F44
#define P7F_45_10B_ADC_A2_VBUS_ON_THR2                              0x7F45
#define P7F_46_10B_ADC_A4_VBUS_ON_THR1                              0x7F46
#define P7F_47_10B_ADC_A4_VBUS_ON_THR2                              0x7F47
#define P7F_48_10B_ADC_A0_VBUS_OFF_THR1                             0x7F48
#define P7F_49_10B_ADC_A0_VBUS_OFF_THR2                             0x7F49
#define P7F_4A_10B_ADC_A2_VBUS_OFF_THR1                             0x7F4A
#define P7F_4B_10B_ADC_A2_VBUS_OFF_THR2                             0x7F4B
#define P7F_4C_10B_ADC_A4_VBUS_OFF_THR1                             0x7F4C
#define P7F_4D_10B_ADC_A4_VBUS_OFF_THR2                             0x7F4D
#define P7F_70_VBUS_COMP_IRQ                                        0x7F70
#define P7F_71_VBUS_COMP0_DEB                                       0x7F71
#define P7F_72_VBUS_COMP1_DEB                                       0x7F72
#define P7F_75_FRS_SIG_CTRL_UPF                                     0x7F75
#define P7F_76_FRS_SIG_CTRL_DPF                                     0x7F76
#define P7F_77_10B_ADC_DUMMY1                                       0x7F77
#define P7F_78_10B_ADC_DUMMY2                                       0x7F78
#define P7F_79_10B_ADC_DUMMY3                                       0x7F79
#define P7F_7A_10B_ADC_DUMMY4                                       0x7F7A
#define P7F_7B_10B_ADC_DUMMY5                                       0x7F7B
#define P7F_7C_10B_ADC_DUMMY6                                       0x7F7C


//--------------------------------------------------
// USB TypeC Fast Role Swap (Page 7F)
//--------------------------------------------------
#define P7F_50_FRS_PMIC_CTRL                                        0x7F50
#define P7F_51_FRS_GPIO_TM_H                                        0x7F51
#define P7F_52_FRS_GPIO_TM_L                                        0x7F52
#define P7F_53_FRS_GPIO_A                                           0x7F53
#define P7F_54_FRS_GPIO_B                                           0x7F54


//--------------------------------------------------
// USB TypeC 10 Bit ADC Config (Page 7F)
//--------------------------------------------------
#define P7F_55_10B_ADC_LDO_CTRL                                     0x7F55
#define P7F_56_FRS_VBUS_COMP0                                       0x7F56
#define P7F_57_FRS_VBUS_COMP1                                       0x7F57
#define P7F_58_FRS_VBUS_COMP2                                       0x7F58
#define P7F_59_ADC_LPF                                              0x7F59
#define P7F_5A_ADC_DUMMY1                                           0x7F5A
#define P7F_5B_ADC_DUMMY2                                           0x7F5B


//--------------------------------------------------
// TypeC I2C Control Module (Page 7F)
//--------------------------------------------------
#define P7F_60_I2CM_CR0                                             0x7F60
#define P7F_61_I2CM_CR1                                             0x7F61
#define P7F_62_I2CM_CR2                                             0x7F62
#define P7F_63_I2CM_CR3                                             0x7F63
#define P7F_64_I2CM_STR0                                            0x7F64
#define P7F_65_I2CM_STR1                                            0x7F65
#define P7F_66_I2CM_STR2                                            0x7F66
#define P7F_67_I2CM_STR3                                            0x7F67
#define P7F_68_I2CM_SR                                              0x7F68
#define P7F_69_I2CM_TD                                              0x7F69
#define P7F_6A_I2CM_CCR                                             0x7F6A
#define P7F_6B_I2CM_FRS_SR                                          0x7F6B
#define P7F_6C_I2CM_FRS_TD                                          0x7F6C
#define P7F_6D_I2CM_FRS_WL                                          0x7F6D


//--------------------------------------------------
// GDI Clock Divider (Page 80)
//--------------------------------------------------
#define P80_06_GDI_CLK_DIVIDER                                      0x8006


//--------------------------------------------------
// GroupE Power Control (Page 80)
//--------------------------------------------------
#define P80_0A_GE_POWER_CTRL                                        0x800A
#define P80_0B_HDCP_POWER_CTRL                                      0x800B
#define P80_0D_TOP_DUMMY7                                           0x800D


//--------------------------------------------------
// XTAL (Page 80)
//--------------------------------------------------
#define P80_0E_XTAL_CTRL0                                           0x800E
#define P80_0F_XTAL_CTRL1                                           0x800F


//--------------------------------------------------
// Overall USB Retimer UFP System RTSSM (Page 81)
//--------------------------------------------------
#define P81_00_RTSSM_GLOBAL_00                                      0x8100
#define P81_01_RTSSM_GLOBAL_01                                      0x8101
#define P81_02_RTSSM_GLOBAL_02                                      0x8102
#define P81_03_RTSSM_GLOBAL_03                                      0x8103
#define P81_04_RTSSM_GLOBAL_04                                      0x8104
#define P81_05_RTSSM_GLOBAL_DUMMY_01                                0x8105
#define P81_06_RTSSM_GLOBAL_DUMMY_02                                0x8106
#define P81_07_RTSSM_CONTROL_00                                     0x8107
#define P81_08_RTSSM_CONTROL_01                                     0x8108
#define P81_09_RTSSM_FLAG_00                                        0x8109
#define P81_0A_RTSSM_CONDITION_00                                   0x810A
#define P81_0B_RTSSM_DUMMY_01                                       0x810B
#define P81_0C_RTSSM_DUMMY_02                                       0x810C
#define P81_0D_RTSSM_DUMMY_03                                       0x810D
#define P81_0E_RTSSM_DUMMY_04                                       0x810E
#define P81_0F_RTSSM_DUMMY_05                                       0x810F


//--------------------------------------------------
// Overall USB Retimer UFP System Timer Function (Page 81)
//--------------------------------------------------
#define P81_10_TIMER_DV0                                            0x8110
#define P81_11_TIMER_DV1                                            0x8111
#define P81_12_TIMER_DV2                                            0x8112
#define P81_13_TIMER_TOP                                            0x8113
#define P81_14_TIMER_GRP1_0                                         0x8114
#define P81_15_TIMER_GRP1_1                                         0x8115
#define P81_16_TIMER_GRP1_2                                         0x8116
#define P81_17_TIMER_GRP1_3                                         0x8117
#define P81_18_TIMER_GRP2_0                                         0x8118
#define P81_19_TIMER_GRP2_1                                         0x8119
#define P81_1A_TIMER_GRP2_3                                         0x811A
#define P81_1B_TIMER_GRP2_4                                         0x811B
#define P81_1C_TIMER_CNT_LIST_0                                     0x811C
#define P81_1F_TIMER_CNT_LIST_3                                     0x811F
#define P81_20_TIMER_CNT_LIST_4                                     0x8120
#define P81_21_TIMER_CNT_LIST_5                                     0x8121
#define P81_22_TIMER_CNT_LIST_6                                     0x8122
#define P81_23_TIMER_CNT_LIST_7                                     0x8123
#define P81_24_TIMER_CNT_LIST_8                                     0x8124
#define P81_25_TIMER_CNT_LIST_9                                     0x8125
#define P81_26_TIMER_CNT_LIST_10                                    0x8126
#define P81_27_TIMER_CNT_LIST_11                                    0x8127
#define P81_28_TIMER_CNT_LIST_12                                    0x8128
#define P81_29_TIMER_CNT_LIST_13                                    0x8129
#define P81_2C_TIMER_CNT_LIST_16                                    0x812C
#define P81_2D_TIMER_CNT_LIST_17                                    0x812D
#define P81_2E_TIMER_CNT_LIST_18                                    0x812E
#define P81_2F_TIMER_CNT_LIST_19                                    0x812F
#define P81_30_TIMER_CNT_LIST_20                                    0x8130
#define P81_31_TIMER_CNT_LIST_21                                    0x8131
#define P81_32_TIMER_CNT_LIST_22                                    0x8132
#define P81_33_TIMER_CNT_LIST_23                                    0x8133
#define P81_34_TIMER_CNT_LIST_24                                    0x8134
#define P81_35_TIMER_DUMMY_01                                       0x8135
#define P81_36_TIMER_DUMMY_02                                       0x8136
#define P81_37_TIMER_DUMMY_03                                       0x8137


//--------------------------------------------------
// Overall USB Retimer UFP System LFPS (Page 81)
//--------------------------------------------------
#define P81_40_LFPS_DETECT_1                                        0x8140
#define P81_41_LFPS_DETECT_2                                        0x8141
#define P81_42_LFPS_DETECT_3                                        0x8142
#define P81_43_LFPS_DETECT_4                                        0x8143
#define P81_44_LFPS_DETECT_5                                        0x8144
#define P81_45_LFPS_DETECT_6                                        0x8145
#define P81_46_LFPS_DETECT_7                                        0x8146
#define P81_47_LFPS_DETECT_8                                        0x8147
#define P81_48_LFPS_DETECT_9                                        0x8148
#define P81_49_LFPS_DETECT_10                                       0x8149
#define P81_4A_LFPS_DETECT_11                                       0x814A
#define P81_4B_LFPS_DETECT_12                                       0x814B
#define P81_4C_LFPS_DETECT_13                                       0x814C
#define P81_4D_LFPS_DETECT_14                                       0x814D
#define P81_4E_LFPS_DETECT_15                                       0x814E
#define P81_4F_LFPS_DETECT_16                                       0x814F
#define P81_50_LFPS_DETECT_17                                       0x8150
#define P81_51_LFPS_DETECT_18                                       0x8151
#define P81_52_LFPS_DETECT_19                                       0x8152
#define P81_53_LFPS_DETECT_20                                       0x8153
#define P81_54_LFPS_DETECT_21                                       0x8154
#define P81_55_LFPS_DETECT_22                                       0x8155
#define P81_56_LFPS_DETECT_23                                       0x8156
#define P81_57_LFPS_DETECT_24                                       0x8157
#define P81_58_LFPS_DETECT_25                                       0x8158
#define P81_59_LFPS_DETECT_26                                       0x8159
#define P81_5A_LFPS_DETECT_27                                       0x815A
#define P81_5B_LFPS_DETECT_28                                       0x815B
#define P81_5C_LFPS_DETECT_DUMMY_02                                 0x815C
#define P81_5D_LFPS_DETECT_DUMMY_03                                 0x815D
#define P81_5E_LFPS_DETECT_DUMMY_04                                 0x815E
#define P81_5F_LFPS_DETECT_DUMMY_05                                 0x815F
#define P81_70_LFPS_TX_CTRL_0                                       0x8170
#define P81_71_LFPS_TX_CTRL_1                                       0x8171
#define P81_72_LFPS_TX_CTRL_2                                       0x8172
#define P81_73_LFPS_TX_CTRL_3                                       0x8173
#define P81_74_LFPS_TX_CTRL_4                                       0x8174
#define P81_75_LFPS_TX_CTRL_5                                       0x8175
#define P81_76_LFPS_TX_CTRL_6                                       0x8176
#define P81_77_LFPS_TX_CTRL_7                                       0x8177
#define P81_78_LFPS_TX_CTRL_8                                       0x8178
#define P81_79_LFPS_TX_CTRL_9                                       0x8179
#define P81_7A_LFPS_TX_CTRL_10                                      0x817A
#define P81_7B_LFPS_TX_CTRL_11                                      0x817B
#define P81_7C_LFPS_TX_CTRL_DUMMY_01                                0x817C
#define P81_7D_LFPS_TX_CTRL_DUMMY_02                                0x817D
#define P81_7E_LFPS_TX_CTRL_DUMMY_03                                0x817E
#define P81_7F_LFPS_TX_CTRL_DUMMY_04                                0x817F


//--------------------------------------------------
// Overall USB Retimer UFP System Link Detect (Page 81)
//--------------------------------------------------
#define P81_90_LINK_DET_GLOBAL                                      0x8190
#define P81_91_LINK_DET_TSEQ                                        0x8191
#define P81_92_LINK_DET_TSEQ_CNT_0                                  0x8192
#define P81_93_LINK_DET_TSEQ_CNT_1                                  0x8193
#define P81_94_LINK_DET_TSEQ_CNT_2                                  0x8194
#define P81_95_LINK_DET_TSEQ_CNT_3                                  0x8195
#define P81_96_LINK_DET_POLARITY                                    0x8196
#define P81_97_LINK_DET_TS1                                         0x8197
#define P81_98_LINK_DET_TS1_FUNC                                    0x8198
#define P81_99_LINK_DET_TS1_CNT_0                                   0x8199
#define P81_9A_LINK_DET_TS1_CNT_1                                   0x819A
#define P81_9B_LINK_DET_TS2_CTL_0                                   0x819B
#define P81_9C_LINK_DET_TS2_CTL_1                                   0x819C
#define P81_9D_LINK_DET_TS2_FUNCR                                   0x819D
#define P81_A0_LINK_DET_TS2_FUNCW                                   0x81A0
#define P81_A1_LINK_DET_TS2_CNT_0                                   0x81A1
#define P81_A2_LINK_DET_TS2_CNT_1                                   0x81A2
#define P81_A3_LINK_DET_IS                                          0x81A3
#define P81_A4_LINK_DET_LCMD_0                                      0x81A4
#define P81_A5_LINK_DET_LCMD_1                                      0x81A5
#define P81_A6_LINK_DET_LCMD_2                                      0x81A6
#define P81_A7_LINK_DET_LCMD_3                                      0x81A7
#define P81_A8_LINK_DET_PKT_0                                       0x81A8
#define P81_A9_LINK_DET_PKT_1                                       0x81A9
#define P81_AA_U2_INACTIVITY_TIMER                                  0x81AA
#define P81_AB_10B8B_DEC_0                                          0x81AB
#define P81_AC_10B8B_DEC_1                                          0x81AC
#define P81_AD_10B8B_DEC_2                                          0x81AD
#define P81_AE_10B8B_DEC_3                                          0x81AE
#define P81_AF_DESCRAM_0                                            0x81AF
#define P81_B0_LINK_DET_DUMMY_01                                    0x81B0
#define P81_B1_LINK_DET_DUMMY_02                                    0x81B1
#define P81_B2_LINK_DET_DUMMY_03                                    0x81B2


//--------------------------------------------------
// Overall USB Retimer UFP System EB Buffer (Page 81)
//--------------------------------------------------
#define P81_C0_EB_GLOBAL                                            0x81C0
#define P81_C1_EB_FLAG                                              0x81C1
#define P81_C2_EB_CTRL                                              0x81C2
#define P81_C3_EB_WL_0                                              0x81C3
#define P81_C4_EB_WL_1                                              0x81C4
#define P81_C5_EB_WL_2                                              0x81C5
#define P81_C6_EB_WL_3                                              0x81C6
#define P81_C7_EB_WL_4                                              0x81C7
#define P81_C8_EB_WL_5                                              0x81C8
#define P81_C9_EB_WL_6                                              0x81C9
#define P81_CA_EB_WL_7                                              0x81CA
#define P81_CB_EB_WL_8                                              0x81CB
#define P81_CC_EB_SRAM_BIST_0                                       0x81CC
#define P81_CD_EB_SRAM_BIST_1                                       0x81CD
#define P81_CE_EB_DUMMY_01                                          0x81CE
#define P81_CF_EB_DUMMY_02                                          0x81CF


//--------------------------------------------------
// Overall USB Retimer UFP System Tx Bist (Page 81)
//--------------------------------------------------
#define P81_D0_TXBIST_PAT_SEL                                       0x81D0
#define P81_D1_TXBIST_TSX_FUNC_BYTE                                 0x81D1
#define P81_D2_TXBIST_TSEQ_NUM                                      0x81D2
#define P81_D3_TXBIST_CONFIG                                        0x81D3
#define P81_D4_TXBIST_TXDEEMP_00                                    0x81D4
#define P81_D5_TXBIST_TXDEEMP_01                                    0x81D5
#define P81_D6_TXBIST_DATASWAP                                      0x81D6
#define P81_D7_TXBIST_DUMMY_00                                      0x81D7
#define P81_D8_TXBIST_DUMMY_01                                      0x81D8


//--------------------------------------------------
// Overall USB Retimer UFP System PIPE Control (Page 81)
//--------------------------------------------------
#define P81_E0_PIPE_CTRL0                                           0x81E0
#define P81_E1_PIPE_CTRL1                                           0x81E1
#define P81_E2_PIPE_CTRL2                                           0x81E2
#define P81_E3_PIPE_CTRL3                                           0x81E3
#define P81_E4_PIPECTRL_STATUS_00                                   0x81E4
#define P81_E5_PIPECTRL_STATUS_01                                   0x81E5
#define P81_E6_PIPECTRL_DUMMY_00                                    0x81E6
#define P81_E7_PIPECTRL_DUMMY_01                                    0x81E7
#define P81_E8_PIPECTRL_DUMMY_02                                    0x81E8


//--------------------------------------------------
// Overall USB Retimer DFP System RTSSM (Page 82)
//--------------------------------------------------
#define P82_00_RTSSM_GLOBAL_DUMMY_00                                0x8200
#define P82_01_RTSSM_GLOBAL_DUMMY_01                                0x8201
#define P82_02_RTSSM_GLOBAL_DUMMY_02                                0x8202
#define P82_03_RTSSM_GLOBAL_DUMMY_03                                0x8203
#define P82_04_RTSSM_GLOBAL_DUMMY_04                                0x8204
#define P82_05_RTSSM_GLOBAL_DUMMY_05                                0x8205
#define P82_06_RTSSM_GLOBAL_DUMMY_06                                0x8206
#define P82_07_RTSSM_CONTROL_00                                     0x8207
#define P82_08_RTSSM_CONTROL_01                                     0x8208
#define P82_09_RTSSM_FLAG_00                                        0x8209
#define P82_0A_RTSSM_CONDITION_00                                   0x820A
#define P82_0B_RTSSM_DUMMY_01                                       0x820B
#define P82_0C_RTSSM_DUMMY_02                                       0x820C
#define P82_0D_RTSSM_DUMMY_03                                       0x820D
#define P82_0E_RTSSM_DUMMY_04                                       0x820E
#define P82_0F_RTSSM_DUMMY_05                                       0x820F


//--------------------------------------------------
// Overall USB Retimer DFP System Timer Function (Page 82)
//--------------------------------------------------
#define P82_10_TIMER_DV0                                            0x8210
#define P82_11_TIMER_DV1                                            0x8211
#define P82_12_TIMER_DV2                                            0x8212
#define P82_13_TIMER_TOP                                            0x8213
#define P82_14_TIMER_GRP1_0                                         0x8214
#define P82_15_TIMER_GRP1_1                                         0x8215
#define P82_16_TIMER_GRP1_2                                         0x8216
#define P82_17_TIMER_GRP1_3                                         0x8217
#define P82_18_TIMER_GRP2_0                                         0x8218
#define P82_19_TIMER_GRP2_1                                         0x8219
#define P82_1A_TIMER_GRP2_3                                         0x821A
#define P82_1B_TIMER_GRP2_4                                         0x821B
#define P82_1C_TIMER_CNT_LIST0                                      0x821C
#define P82_1D_TIMER_CNT_LIST1                                      0x821D
#define P82_1E_TIMER_CNT_LIST2                                      0x821E
#define P82_1F_TIMER_CNT_LIST3                                      0x821F
#define P82_20_TIMER_CNT_LIST4                                      0x8220
#define P82_21_TIMER_CNT_LIST5                                      0x8221
#define P82_22_TIMER_CNT_LIST6                                      0x8222
#define P82_23_TIMER_CNT_LIST7                                      0x8223
#define P82_24_TIMER_CNT_LIST8                                      0x8224
#define P82_25_TIMER_CNT_LIST9                                      0x8225
#define P82_26_TIMER_CNT_LIST10                                     0x8226
#define P82_27_TIMER_CNT_LIST11                                     0x8227
#define P82_28_TIMER_CNT_LIST12                                     0x8228
#define P82_29_TIMER_CNT_LIST13                                     0x8229
#define P82_2A_TIMER_CNT_LIST14                                     0x822A
#define P82_2B_TIMER_CNT_LIST15                                     0x822B
#define P82_2C_TIMER_CNT_LIST16                                     0x822C
#define P82_2D_TIMER_CNT_LIST17                                     0x822D
#define P82_2E_TIMER_CNT_LIST18                                     0x822E
#define P82_2F_TIMER_CNT_LIST19                                     0x822F
#define P82_30_TIMER_CNT_LIST20                                     0x8230
#define P82_31_TIMER_CNT_LIST21                                     0x8231
#define P82_32_TIMER_CNT_LIST22                                     0x8232
#define P82_33_TIMER_CNT_LIST23                                     0x8233
#define P82_34_TIMER_CNT_LIST24                                     0x8234
#define P82_35_TIMER_DUMMY_01                                       0x8235
#define P82_36_TIMER_DUMMY_02                                       0x8236
#define P82_37_TIMER_DUMMY_03                                       0x8237


//--------------------------------------------------
// Overall USB Retimer DFP System LFPS (Page 82)
//--------------------------------------------------
#define P82_40_LFPS_DETECT_1                                        0x8240
#define P82_41_LFPS_DETECT_2                                        0x8241
#define P82_42_LFPS_DETECT_3                                        0x8242
#define P82_43_LFPS_DETECT_4                                        0x8243
#define P82_44_LFPS_DETECT_5                                        0x8244
#define P82_45_LFPS_DETECT_6                                        0x8245
#define P82_46_LFPS_DETECT_7                                        0x8246
#define P82_47_LFPS_DETECT_8                                        0x8247
#define P82_48_LFPS_DETECT_9                                        0x8248
#define P82_49_LFPS_DETECT_10                                       0x8249
#define P82_4A_LFPS_DETECT_11                                       0x824A
#define P82_4B_LFPS_DETECT_12                                       0x824B
#define P82_4C_LFPS_DETECT_13                                       0x824C
#define P82_4D_LFPS_DETECT_14                                       0x824D
#define P82_4E_LFPS_DETECT_15                                       0x824E
#define P82_4F_LFPS_DETECT_16                                       0x824F
#define P82_50_LFPS_DETECT_17                                       0x8250
#define P82_51_LFPS_DETECT_18                                       0x8251
#define P82_52_LFPS_DETECT_19                                       0x8252
#define P82_53_LFPS_DETECT_20                                       0x8253
#define P82_54_LFPS_DETECT_21                                       0x8254
#define P82_55_LFPS_DETECT_22                                       0x8255
#define P82_56_LFPS_DETECT_23                                       0x8256
#define P82_57_LFPS_DETECT_24                                       0x8257
#define P82_58_LFPS_DETECT_25                                       0x8258
#define P82_59_LFPS_DETECT_26                                       0x8259
#define P82_5A_LFPS_DETECT_27                                       0x825A
#define P82_5B_LFPS_DETECT_28                                       0x825B
#define P82_5C_LFPS_DETECT_DUMMY_02                                 0x825C
#define P82_5D_LFPS_DETECT_DUMMY_03                                 0x825D
#define P82_5E_LFPS_DETECT_DUMMY_04                                 0x825E
#define P82_5F_LFPS_DETECT_DUMMY_05                                 0x825F
#define P82_70_LFPS_TX_CTRL_0                                       0x8270
#define P82_71_LFPS_TX_CTRL_1                                       0x8271
#define P82_72_LFPS_TX_CTRL_2                                       0x8272
#define P82_73_LFPS_TX_CTRL_3                                       0x8273
#define P82_74_LFPS_TX_CTRL_4                                       0x8274
#define P82_75_LFPS_TX_CTRL_5                                       0x8275
#define P82_76_LFPS_TX_CTRL_6                                       0x8276
#define P82_77_LFPS_TX_CTRL_7                                       0x8277
#define P82_78_LFPS_TX_CTRL_8                                       0x8278
#define P82_79_LFPS_TX_CTRL_9                                       0x8279
#define P82_7A_LFPS_TX_CTRL_10                                      0x827A
#define P82_7B_LFPS_TX_CTRL_11                                      0x827B
#define P82_7C_LFPS_TX_CTRL_DUMMY_01                                0x827C
#define P82_7D_LFPS_TX_CTRL_DUMMY_02                                0x827D
#define P82_7E_LFPS_TX_CTRL_DUMMY_03                                0x827E
#define P82_7F_LFPS_TX_CTRL_DUMMY_04                                0x827F


//--------------------------------------------------
// Overall USB Retimer DFP System Link Detect (Page 82)
//--------------------------------------------------
#define P82_90_LINK_DET_GLOBAL                                      0x8290
#define P82_91_LINK_DET_TSEQ                                        0x8291
#define P82_92_LINK_DET_TSEQ_CNT_0                                  0x8292
#define P82_93_LINK_DET_TSEQ_CNT_1                                  0x8293
#define P82_94_LINK_DET_TSEQ_CNT_2                                  0x8294
#define P82_95_LINK_DET_TSEQ_CNT_3                                  0x8295
#define P82_96_LINK_DET_POLARITY                                    0x8296
#define P82_97_LINK_DET_TS1                                         0x8297
#define P82_98_LINK_DET_TS1_FUNC                                    0x8298
#define P82_99_LINK_DET_TS1_CNT_0                                   0x8299
#define P82_9A_LINK_DET_TS1_CNT_1                                   0x829A
#define P82_9B_LINK_DET_TS2_CTL_0                                   0x829B
#define P82_9C_LINK_DET_TS2_CTL_1                                   0x829C
#define P82_9D_LINK_DET_TS2_FUNCR                                   0x829D
#define P82_A0_LINK_DET_TS2_FUNCW                                   0x82A0
#define P82_A1_LINK_DET_TS2_CNT_0                                   0x82A1
#define P82_A2_LINK_DET_TS2_CNT_1                                   0x82A2
#define P82_A3_LINK_DET_IS                                          0x82A3
#define P82_A4_LINK_DET_LCMD_0                                      0x82A4
#define P82_A5_LINK_DET_LCMD_1                                      0x82A5
#define P82_A6_LINK_DET_LCMD_2                                      0x82A6
#define P82_A7_LINK_DET_LCMD_3                                      0x82A7
#define P82_A8_LINK_DET_PKT_0                                       0x82A8
#define P82_A9_LINK_DET_PKT_1                                       0x82A9
#define P82_AB_10B8B_DEC0                                           0x82AB
#define P82_AC_10B8B_DEC1                                           0x82AC
#define P82_AD_10B8B_DEC2                                           0x82AD
#define P82_AE_10B8B_DEC3                                           0x82AE
#define P82_AF_DESCRAM_0                                            0x82AF
#define P82_B0_LINK_DET_DUMMY_01                                    0x82B0
#define P82_B1_LINK_DET_DUMMY_02                                    0x82B1
#define P82_B2_LINK_DET_DUMMY_03                                    0x82B2


//--------------------------------------------------
// Overall USB Retimer DFP System EB Buffer (Page 82)
//--------------------------------------------------
#define P82_C0_EB_GLOBAL                                            0x82C0
#define P82_C1_EB_FLAG                                              0x82C1
#define P82_C2_EB_CTRL                                              0x82C2
#define P82_C3_EB_WL_0                                              0x82C3
#define P82_C4_EB_WL_1                                              0x82C4
#define P82_C5_EB_WL_2                                              0x82C5
#define P82_C6_EB_WL_3                                              0x82C6
#define P82_C7_EB_WL_4                                              0x82C7
#define P82_C8_EB_WL_5                                              0x82C8
#define P82_C9_EB_WL_6                                              0x82C9
#define P82_CA_EB_WL_7                                              0x82CA
#define P82_CB_EB_WL_8                                              0x82CB
#define P82_CC_EB_SRAM_BIST_0                                       0x82CC
#define P82_CD_EB_SRAM_BIST_1                                       0x82CD
#define P82_CE_EB_DUMMY_01                                          0x82CE
#define P82_CF_EB_DUMMY_02                                          0x82CF


//--------------------------------------------------
// Overall USB Retimer DFP System Tx Bist (Page 82)
//--------------------------------------------------
#define P82_D0_TXBIST_PAT_SEL                                       0x82D0
#define P82_D1_TXBIST_TSX_FUNC_BYTE                                 0x82D1
#define P82_D2_TXBIST_TSEQ_NUM                                      0x82D2
#define P82_D3_TXBIST_CONFIG                                        0x82D3
#define P82_D4_TXBIST_TXDEEMP_00                                    0x82D4
#define P82_D5_TXBIST_TXDEEMP_01                                    0x82D5
#define P82_D6_TXBIST_DATASWAP                                      0x82D6
#define P82_D7_TXBIST_DUMMY_00                                      0x82D7
#define P82_D8_TXBIST_DUMMY_01                                      0x82D8


//--------------------------------------------------
// Overall USB Retimer DFP System PIPE Control (Page 82)
//--------------------------------------------------
#define P82_E0_PIPE_CTRL0                                           0x82E0
#define P82_E1_PIPE_CTRL1                                           0x82E1
#define P82_E2_PIPE_CTRL2                                           0x82E2
#define P82_E3_PIPE_CTRL3                                           0x82E3
#define P82_E4_PIPECTRL_STATUS_00                                   0x82E4
#define P82_E5_PIPECTRL_STATUS_01                                   0x82E5
#define P82_E6_PIPECTRL_DUMMY_00                                    0x82E6
#define P82_E7_PIPECTRL_DUMMY_01                                    0x82E7
#define P82_E8_PIPECTRL_DUMMY_02                                    0x82E8


//--------------------------------------------------
// Charging Control Registers (Page 86)
//--------------------------------------------------
#define P86_00_CHG_CFG0                                             0x8600
#define P86_04_CHG_APP_W_TIME                                       0x8604
#define P86_05_CHG_APP_D_TIME                                       0x8605
#define P86_06_CHG_DCP_W_TIME                                       0x8606
#define P86_07_CHG_DCP_D_TIME                                       0x8607
#define P86_08_CHG_CDP_D_TIME                                       0x8608
#define P86_09_CHG_ACA_DOCK                                         0x8609
#define P86_10_CHG_CTRL0                                            0x8610
#define P86_11_CHG_CTRL1                                            0x8611
#define P86_12_CHG_IRQEN                                            0x8612
#define P86_13_CHG_IRQ                                              0x8613
#define P86_14_CHG_STS                                              0x8614
#define P86_15_CHG_APP_DIV_SEL                                      0x8615


//--------------------------------------------------
// Bill Board UTMI PHY Control (Page 97)
//--------------------------------------------------
#define P97_00_HS_PHY_CFG0                                          0x9700
#define P97_01_HS_PHY_CFG1                                          0x9701
#define P97_04_HS_UTMI_SYS                                          0x9704
#define P97_05_HS_UTMI_CTL0                                         0x9705
#define P97_06_HS_UTMI_CTL1                                         0x9706
#define P97_07_HS_UTMI_CTL2                                         0x9707
#define P97_08_HS_SLB_CTL                                           0x9708
#define P97_09_HS_SLB_SEED                                          0x9709


//--------------------------------------------------
// Bill Board Class Control (Page 98)
//--------------------------------------------------
#define P98_00_HS_EP0_IRQ                                           0x9800
#define P98_01_HS_EP0_IRQ_EN                                        0x9801
#define P98_04_HS_EP0_CTRL                                          0x9804
#define P98_05_HS_EP0_RX_BC                                         0x9805
#define P98_06_HS_EP0_TX_BC                                         0x9806
#define P98_08_HS_EP0_SETUP0                                        0x9808
#define P98_09_HS_EP0_SETUP1                                        0x9809
#define P98_0A_HS_EP0_SETUP2                                        0x980A
#define P98_0B_HS_EP0_SETUP3                                        0x980B
#define P98_0C_HS_EP0_SETUP4                                        0x980C
#define P98_0D_HS_EP0_SETUP5                                        0x980D
#define P98_0E_HS_EP0_SETUP6                                        0x980E
#define P98_0F_HS_EP0_SETUP7                                        0x980F
#define P98_10_HS_DSP_INDEX                                         0x9810
#define P98_11_HS_BUF0_PRT_STS                                      0x9811
#define P98_12_HS_HW_CTRL                                           0x9812
#define P98_13_HS_HW_DSP12_N                                        0x9813
#define P98_14_HS_HW_DSP34_N                                        0x9814


//--------------------------------------------------
// Bill Board BUF0 SRAM (Page 9A)
//--------------------------------------------------
#define P9A_00_BB_BUF0_WR_ADDR                                      0x9A00
#define P9A_01_BB_BUF0_WR_DATA                                      0x9A01
#define P9A_02_BB_BUF0_RD_ADDR                                      0x9A02
#define P9A_03_BB_BUF0_RD_DATA                                      0x9A03


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
// DisplayPort 1.1 Tx1 AUX (Page 9D)
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
// D0 Port DisplayPort 1.2 Digital MAC (Page B5)
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


//--------------------------------------------------
// D0 Port DisplayPort 1.2 Digital MAC PLL (Page B5)
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
#define PB5_C7_VBID_MAN_MADE                                        0xB5C7


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
#define PB6_2E_DP_INFO_FM_IRQ                                       0xB62E
#define PB6_2F_DP_INFO_FM_STATUS                                    0xB62F
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
#define PB6_3C_DP_INFO_RST                                          0xB63C
#define PB6_3D_DP_INFO_FM_RSV2                                      0xB63D
#define PB6_3E_DP_INFO_FM_RSV_STATUS                                0xB63E
#define PB6_40_VSC0                                                 0xB640
#define PB6_41_VSC1                                                 0xB641
#define PB6_42_VSC2                                                 0xB642
#define PB6_43_VSC3                                                 0xB643
#define PB6_44_VSC4                                                 0xB644
#define PB6_45_VSC5                                                 0xB645
#define PB6_46_VSC15                                                0xB646
#define PB6_47_VSC16                                                0xB647
#define PB6_48_VSC17                                                0xB648
#define PB6_49_VSC18                                                0xB649
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
#define PB6_C0_SPDIF_CH12_CS                                        0xB6C0
#define PB6_C1_SPDIF_CH34_CS                                        0xB6C1
#define PB6_C2_SPDIF_CH56_CS                                        0xB6C2
#define PB6_C3_SPDIF_CH78_CS                                        0xB6C3
#define PB6_F0_DP_INFO_FM_RSV0_HB2                                  0xB6F0
#define PB6_F1_DP_INFO_FM_RSV0_HB3                                  0xB6F1
#define PB6_F2_DP_INFO_FM_RSV1_HB2                                  0xB6F2
#define PB6_F3_DP_INFO_FM_RSV1_HB3                                  0xB6F3
#define PB6_F4_DP_INFO_FM_RSV2_HB2                                  0xB6F4
#define PB6_F5_DP_INFO_FM_RSV2_HB3                                  0xB6F5
#define PB6_F6_DP_AUD_CH12_CS                                       0xB6F6
#define PB6_F7_DP_AUD_CH34_CS                                       0xB6F7
#define PB6_F8_DP_AUD_CH56_CS                                       0xB6F8
#define PB6_F9_DP_AUD_CH78_CS                                       0xB6F9
#define PB6_FC_DUMMY_0                                              0xB6FC
#define PB6_FD_DUMMY_1                                              0xB6FD
#define PB6_FE_DUMMY_2                                              0xB6FE
#define PB6_FF_DUMMY_3                                              0xB6FF


//--------------------------------------------------
// D0 Port DisplayPort 1.2 AUX Analog PHY (Page B7)
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
// D0 Port DisplayPort 1.2 AUX Digital PHY (Page B7)
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
#define PB7_CA_AUX_IRQ_ADDR4_MSB                                    0xB7CA
#define PB7_CB_AUX_IRQ_ADDR4_MSB1                                   0xB7CB
#define PB7_CC_AUX_IRQ_ADDR4_LSB                                    0xB7CC
#define PB7_CD_AUX_IRQ_ADDR5_MSB                                    0xB7CD
#define PB7_CE_AUX_IRQ_ADDR5_MSB1                                   0xB7CE
#define PB7_CF_AUX_IRQ_ADDR5_LSB                                    0xB7CF
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
#define PB7_FC_DUMMY_2                                              0xB7FC
#define PB7_FF_TEST_FUNCTION                                        0xB7FF


//--------------------------------------------------
// D1 Port DisplayPort 1.2 AUX Analog PHY (Page BA)
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
// D1 Port DisplayPort 1.2 AUX Digital PHY (Page BA)
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
#define PBA_CA_AUX_IRQ_ADDR4_MSB                                    0xBACA
#define PBA_CB_AUX_IRQ_ADDR4_MSB1                                   0xBACB
#define PBA_CC_AUX_IRQ_ADDR4_LSB                                    0xBACC
#define PBA_CD_AUX_IRQ_ADDR5_MSB                                    0xBACD
#define PBA_CE_AUX_IRQ_ADDR5_MSB1                                   0xBACE
#define PBA_CF_AUX_IRQ_ADDR5_LSB                                    0xBACF
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
#define PBA_FC_DUMMY_2                                              0xBAFC
#define PBA_FF_TEST_FUNCTION                                        0xBAFF


//--------------------------------------------------
// GroupB Power Control (Page C0)
//--------------------------------------------------
#define PC0_0A_GB_POWER_CTRL                                        0xC00A


//--------------------------------------------------
// M1 Scan FIFO Frequency (Page C0)
//--------------------------------------------------
#define PC0_0D_M1_SCAN_FIFO_CLOCK_SELECT                            0xC00D


//--------------------------------------------------
// DFP USB3 APHY (RX) (Page C1)
//--------------------------------------------------
#define PC1_00_USB_TOP                                              0xC100
#define PC1_01_USB_RSV_00                                           0xC101
#define PC1_10_CDR_00                                               0xC110
#define PC1_11_CDR_01                                               0xC111
#define PC1_12_CDR_02                                               0xC112
#define PC1_13_OOBS_00                                              0xC113
#define PC1_14_OOBS_01                                              0xC114
#define PC1_15_OOBS_02                                              0xC115
#define PC1_17_RX_00                                                0xC117
#define PC1_18_RX_01                                                0xC118
#define PC1_19_RX_02                                                0xC119
#define PC1_1A_RX_03                                                0xC11A
#define PC1_1B_RX_04                                                0xC11B
#define PC1_20_CMU_00                                               0xC120
#define PC1_21_CMU_01                                               0xC121
#define PC1_22_CMU_02                                               0xC122
#define PC1_23_CMU_03                                               0xC123
#define PC1_25_TX_00                                                0xC125
#define PC1_26_TX_01                                                0xC126
#define PC1_27_TX_02                                                0xC127
#define PC1_29_TX_04                                                0xC129
#define PC1_2A_TX_05                                                0xC12A
#define PC1_2B_TX_06                                                0xC12B
#define PC1_2C_TX_07                                                0xC12C
#define PC1_2D_TX_08                                                0xC12D


//--------------------------------------------------
// DFP USB3 DPHY (RX) (Page C2)
//--------------------------------------------------
#define PC2_00_DMR_0                                                0xC200
#define PC2_01_DMR_1                                                0xC201
#define PC2_02_BACR_0                                               0xC202
#define PC2_03_BACR_1                                               0xC203
#define PC2_04_IER_0                                                0xC204
#define PC2_05_IER_1                                                0xC205
#define PC2_06_BCSR_0                                               0xC206
#define PC2_07_BCSR_1                                               0xC207
#define PC2_08_BPR_0                                                0xC208
#define PC2_09_BPR_1                                                0xC209
#define PC2_0A_BPNR2                                                0xC20A
#define PC2_0B_BFNR                                                 0xC20B
#define PC2_0C_BRNR2                                                0xC20C
#define PC2_0D_BENR_0                                               0xC20D
#define PC2_0E_BENR_1                                               0xC20E
#define PC2_0F_REG_REV0_0                                           0xC20F
#define PC2_10_REG_REV0_1                                           0xC210
#define PC2_11_REG_REV1_0                                           0xC211
#define PC2_12_REG_REV1_1                                           0xC212
#define PC2_13_REG_REV2_0                                           0xC213
#define PC2_14_REG_REV2_1                                           0xC214
#define PC2_15_REG_REV3_0                                           0xC215
#define PC2_16_REG_REV3_1                                           0xC216
#define PC2_17_FLD_0_0                                              0xC217
#define PC2_18_FLD_0_1                                              0xC218
#define PC2_19_FLD_1_0                                              0xC219
#define PC2_1A_FLD_1_1                                              0xC21A
#define PC2_1B_ANA1F_READONLY_0                                     0xC21B
#define PC2_1C_ANA1F_READONLY_1                                     0xC21C
#define PC2_1D_PA1_REG10_READOUT_0                                  0xC21D
#define PC2_1E_PA1_REG10_READOUT_1                                  0xC21E
#define PC2_1F_PA1_REG11_READOUT_0                                  0xC21F
#define PC2_20_PA1_REG11_READOUT_1                                  0xC220
#define PC2_21_DPHY_0                                               0xC221
#define PC2_22_DPHY_1                                               0xC222
#define PC2_23_DPHY_2                                               0xC223
#define PC2_24_FORE_OFFSET_K_0                                      0xC224
#define PC2_25_FORE_OFFSET_K_1                                      0xC225
#define PC2_26_FORE_OFFSET_K_2                                      0xC226
#define PC2_27_FORE_OFFSET_K_3                                      0xC227
#define PC2_28_FORE_OFFSET_K_4                                      0xC228
#define PC2_29_FORE_OFFSET_K_5                                      0xC229
#define PC2_2A_FORE_OFFSET_K_6                                      0xC22A
#define PC2_2B_CDR_FLD_0                                            0xC22B
#define PC2_2C_CDR_FLD_1                                            0xC22C
#define PC2_2D_CDR_FLD_2                                            0xC22D
#define PC2_2E_CDR_FLD_3                                            0xC22E
#define PC2_2F_CDR_FLD_4                                            0xC22F
#define PC2_30_CDR_FLD_5                                            0xC230
#define PC2_31_CDR_FLD_6                                            0xC231
#define PC2_32_CDR_FLD_7                                            0xC232
#define PC2_33_CDR_FLD_8                                            0xC233
#define PC2_34_CDR_FLD_9                                            0xC234
#define PC2_35_CDR_FLD_10                                           0xC235
#define PC2_36_CDR_FLD_11                                           0xC236
#define PC2_37_CDR_FLD_12                                           0xC237
#define PC2_38_CDR_FLD_13                                           0xC238
#define PC2_39_CDR_FLD_14                                           0xC239
#define PC2_3A_CDR_FLD_15                                           0xC23A
#define PC2_3B_CDR_FLD_16                                           0xC23B
#define PC2_3C_CDR_FLD_17                                           0xC23C
#define PC2_3D_CDR_FLD_18                                           0xC23D
#define PC2_3E_CDR_FLD_19                                           0xC23E
#define PC2_3F_CDR_FLD_20                                           0xC23F
#define PC2_40_CDR_FLD_21                                           0xC240
#define PC2_41_CDR_FLD_22                                           0xC241
#define PC2_42_CDR_FLD_23                                           0xC242
#define PC2_43_CDR_FLD_24                                           0xC243
#define PC2_44_CDR_FLD_25                                           0xC244
#define PC2_45_CDR_FLD_26                                           0xC245
#define PC2_46_CDR_FLD_27                                           0xC246
#define PC2_47_CDR_FLD_28                                           0xC247
#define PC2_48_CDR_FLD_29                                           0xC248
#define PC2_49_CDR_FLD_30                                           0xC249
#define PC2_4A_CDR_FLD_31                                           0xC24A
#define PC2_4B_CDR_FLD_32                                           0xC24B
#define PC2_4C_CDR_FLD_33                                           0xC24C
#define PC2_4D_CMU_SSC_0                                            0xC24D
#define PC2_4E_CMU_SSC_1                                            0xC24E
#define PC2_4F_CMU_SSC_2                                            0xC24F
#define PC2_50_CMU_SSC_3                                            0xC250
#define PC2_51_CMU_SSC_4                                            0xC251
#define PC2_52_CMU_SSC_5                                            0xC252
#define PC2_53_CMU_SSC_6                                            0xC253
#define PC2_54_CMU_SSC_7                                            0xC254
#define PC2_55_CMU_SSC_8                                            0xC255
#define PC2_56_CMU_WATCHDOG_0                                       0xC256
#define PC2_57_CMU_WATCHDOG_1                                       0xC257
#define PC2_58_DPHY_RESERVED_0                                      0xC258
#define PC2_59_DPHY_RESERVED_1                                      0xC259


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
