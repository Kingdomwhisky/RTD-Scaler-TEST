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
// ID Code      : RL6449_Series_Pin156_Mapping.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Mapping List
//--------------------------------------------------
#define _PIN_1                                  _156PIN_PIN_4
#define _PIN_14                                 _156PIN_PIN_17
#define _PIN_65                                 _156PIN_PIN_45
#define _PIN_66                                 _156PIN_PIN_46
#define _PIN_67                                 _156PIN_PIN_47
#define _PIN_68                                 _156PIN_PIN_48
#define _PIN_69                                 _156PIN_PIN_49
#define _PIN_70                                 _156PIN_PIN_50
#define _PIN_71                                 _156PIN_PIN_51
#define _PIN_74                                 _156PIN_PIN_54
#define _PIN_75                                 _156PIN_PIN_55
#define _PIN_76                                 _156PIN_PIN_56
#define _PIN_77                                 _156PIN_PIN_57
#define _PIN_91                                 _156PIN_PIN_62
#define _PIN_92                                 _156PIN_PIN_63
#define _PIN_94                                 _156PIN_PIN_65
#define _PIN_95                                 _156PIN_PIN_66
#define _PIN_96                                 _156PIN_PIN_67
#define _PIN_97                                 _156PIN_PIN_68
#define _PIN_109_OFF_REGION                     _156PIN_PIN_79_OFF_REGION
#define _PIN_110_OFF_REGION                     _156PIN_PIN_80_OFF_REGION
#define _PIN_113_OFF_REGION                     _156PIN_PIN_83_OFF_REGION
#define _PIN_114_OFF_REGION                     _156PIN_PIN_84_OFF_REGION
#define _PIN_115_OFF_REGION                     _156PIN_PIN_85_OFF_REGION
#define _PIN_116_OFF_REGION                     _156PIN_PIN_86_OFF_REGION
#define _PIN_117_OFF_REGION                     _156PIN_PIN_87_OFF_REGION
#define _PIN_143_OFF_REGION                     _156PIN_PIN_103_OFF_REGION
#define _PIN_144_OFF_REGION                     _156PIN_PIN_104_OFF_REGION
#define _PIN_145_OFF_REGION                     _156PIN_PIN_105_OFF_REGION
#define _PIN_146_OFF_REGION                     _156PIN_PIN_106_OFF_REGION
#define _PIN_147_OFF_REGION                     _156PIN_PIN_107_OFF_REGION
#define _PIN_148_OFF_REGION                     _156PIN_PIN_108_OFF_REGION
#define _PIN_149_OFF_REGION                     _156PIN_PIN_109_OFF_REGION
#define _PIN_150_OFF_REGION                     _156PIN_PIN_110_OFF_REGION
#define _PIN_151_OFF_REGION                     _156PIN_PIN_111_OFF_REGION
#define _PIN_152_OFF_REGION                     _156PIN_PIN_112_OFF_REGION
#define _PIN_153_OFF_REGION                     _156PIN_PIN_113_OFF_REGION
#define _PIN_154_OFF_REGION                     _156PIN_PIN_114_OFF_REGION
#define _PIN_155_OFF_REGION                     _156PIN_PIN_115_OFF_REGION
#define _PIN_156_OFF_REGION                     _156PIN_PIN_116_OFF_REGION
#define _PIN_157_OFF_REGION                     _156PIN_PIN_117_OFF_REGION
#define _PIN_158_OFF_REGION                     _156PIN_PIN_118_OFF_REGION
#define _PIN_159_OFF_REGION                     _156PIN_PIN_119_OFF_REGION
#define _PIN_160_OFF_REGION                     _156PIN_PIN_120_OFF_REGION
#define _PIN_161_OFF_REGION                     _156PIN_PIN_121_OFF_REGION
#define _PIN_179                                _156PIN_PIN_135
#define _PIN_181                                _156PIN_PIN_136
#define _PIN_185                                _156PIN_PIN_138
#define _PIN_190                                _156PIN_PIN_143
#define _PIN_194                                _156PIN_PIN_146
#define _PIN_195                                _156PIN_PIN_147
#define _PIN_199                                _156PIN_PIN_148
#define _PIN_202                                _156PIN_PIN_149
#define _PIN_203                                _156PIN_PIN_150
#define _PIN_209                                _156PIN_PIN_152
#define _PIN_210                                _156PIN_PIN_153
#define _PIN_211                                _156PIN_PIN_154
#define _PIN_212                                _156PIN_PIN_155
#define _PIN_213                                _156PIN_PIN_156
#define _PIN_214                                _156PIN_PIN_1
#define _PIN_215                                _156PIN_PIN_2


//--------------------------------------------------
// Not Bonded Pin
//--------------------------------------------------
// NC
#define _PIN_163_OFF_REGION                     (1 & 0x0F) // Page 10-0x2D[2:0]
// 0 ~ 5 (0: P7D5i<I>, 1: P7D5o<PP>, 2: P7D5o<OD>, 3: tcon[5], 4: spdif1,
//        5: sd1)

// NC
#define _PIN_164_OFF_REGION                     (1 & 0x0F) // Page 10-0x2E[2:0]
// 0 ~ 6 (0: P7D6i<I>, 1: P7D6o<PP>, 2: P7D6o<OD>, 3: tcon[1], 4: spdif2,
//        5: sd2, 6: cryclk)

// NC
#define _PIN_165_OFF_REGION                     (1 & 0x0F) // Page 10-0x2F[2:0]
// 0 ~ 7 (0: P7D7i<I>, 1: P7D7o<PP>, 2: P7D7o<OD>, 3: tcon[6], 4: spdif3, 5: sd3,
//        6: disp_frame_start_in, 7: disp_frame_start_out)

// NC
#define _PIN_166_OFF_REGION                     (1 & 0x0F) // Page 10-0x30[2:0]
// 0 ~ 6 (0: P8D0i<I>, 1: P8D0o<PP>, 2: P8D0o<OD>, 3: PWM3<PP>, 4: PWM3<OD>,
//        5: TCON[8], 6: m1_idomain_vs_out)

// MHL_5V_EN
#define _PIN_180                                (1 & 0x0F) // Page 10-0x32[2:0]
// 0 ~ 7 (0: P8D2i<I>, 1: P8D2o<PP>, 2: P8D2o<OD>, 3: ttl_den, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// LED1
#define _PIN_184                                (1 & 0x0F) // Page 10-0x34[2:0]
// 0 ~ 6 (0: P8D4i<I>, 1: P8D4o<PP>, 2: P8D4o<OD>, 3: pwm0<PP>, 4: pwm0<OD>,
//        5: tcon[11], 6: clko)

// NC
#define _PIN_193                                (1 & 0x0F) // Page 10-0x37[2:0]
// 0 ~ 7 (0: P8D7i<I>, 1: P8D7o<PP>, 2: P8D7o<OD>, 3: Reserved,
//        4: Test4b_out0, 5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// HDMI_MHL_SEL_3
#define _PIN_196                                (1 & 0x0F) // Page 10-0x3A[2:0]
// 0 ~ 7 (0: P9D2i<I>, 1: P9D2o<PP>, 2: P9D2o<OD>, 3: tcon[5], 4: test4b_out0
//        5: test4b_out1, 6:test4b_out2, 7:test4b_out3)

// HDMI_MHL_SEL_2
#define _PIN_197                                (1 & 0x0F) // Page 10-0x3B[2:0]
// 0 ~ 7 (0: P9D3i<I>, 1: P9D3o<PP>, 2: P9D3o<OD>, 3: tcon[4], 4: test4b_out0
//        5: test4b_out1, 6:test4b_out2, 7:test4b_out3)

// HDMI_CABLE_DETECT_3
#define _PIN_198                                (1 & 0x0F) // Page 10-0x3C[2:0]
// 0 ~ 7 (0: P9D4i<I>, 1: P9D4o<PP>, 2: P9D4o<OD>, 3: m1_idomain_hs_out, 4: test4b_out0
//        5: test4b_out1, 6:test4b_out2, 7:test4b_out3)

// DDR_PW_EN
#define _PIN_200                                (1 & 0x0F) // Page 10-0x3E[2:0]
// 0 ~ 8 (0: P9D6i<I>, 1: P9D6o<PP>, 2: P9D6o<OD>, 3: pwm4<PP>, 4: pwm4<OD>
//        5: tcon[11], 8: iicscl2)

// VBUS_EN_3
#define _PIN_201                                (1 & 0x0F) // Page 10-0x3F[2:0]
// 0 ~ 8 (0: P9D7i<I>, 1: P9D7o<PP>, 2: P9D7o<OD>, 3: pwm3<PP>, 4: pwm3<OD>
//        5: tcon[0], 8: iicsda2)

// HDMI_CABLE_DETECT_2
#define _PIN_204                                (1 & 0x0F) // Page 10-0x42[2:0]
// 0 ~ 7 (0: PAD2i<I>, 1: PAD2o<PP>, 2: PAD2o<OD>, 3: tcon[13], 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3)

// DP_SINK_ASS_N1
#define _PIN_206                                (1 & 0x0F) // Page 10-0x43[2:0]
// 0 ~ 7 (0: PAD3i<I>, 1: PAD3o<PP>, 2: PAD3o<OD>, 3: tcon[12], 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3)

// DP_SINK_ASS_P1
#define _PIN_207                                (1 & 0x0F) // Page 10-0x44[2:0]
// 0 ~ 7 (0: PAD4i<I>, 1: PAD4o<PP>, 2: PAD4o<OD>, 3: tcon[10], 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3)

// DP_CABLE_DET_1
#define _PIN_208                                (1 & 0x0F) // Page 10-0x45[2:0]
// 0 ~ 7 (0: PAD5i<I>, 1: PAD5o<PP>, 2: PAD5o<OD>, 3: tcon[9], 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3)

