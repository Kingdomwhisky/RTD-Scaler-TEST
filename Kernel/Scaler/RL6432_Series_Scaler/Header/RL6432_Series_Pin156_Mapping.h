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
// ID Code      : RL6432_Series_Pin156_Mapping.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Mapping List
//--------------------------------------------------
#define _PIN_1                                  _156PIN_PIN_82
#define _PIN_3                                  _156PIN_PIN_84
#define _PIN_53                                 _156PIN_PIN_118
#define _PIN_54                                 _156PIN_PIN_119
#define _PIN_66                                 _156PIN_PIN_131
#define _PIN_67                                 _156PIN_PIN_132
#define _PIN_68                                 _156PIN_PIN_133
#define _PIN_71                                 _156PIN_PIN_135
#define _PIN_72                                 _156PIN_PIN_136
#define _PIN_73                                 _156PIN_PIN_137
#define _PIN_74                                 _156PIN_PIN_138
#define _PIN_91                                 _156PIN_PIN_143
#define _PIN_92                                 _156PIN_PIN_144
#define _PIN_99                                 _156PIN_PIN_147
#define _PIN_100                                _156PIN_PIN_148
#define _PIN_103                                _156PIN_PIN_151
#define _PIN_104                                _156PIN_PIN_152
#define _PIN_105                                _156PIN_PIN_153
#define _PIN_106                                _156PIN_PIN_154
#define _PIN_107                                _156PIN_PIN_155
#define _PIN_173_OFF_REGION                     _156PIN_PIN_50_OFF_REGION
#define _PIN_174_OFF_REGION                     _156PIN_PIN_51_OFF_REGION
#define _PIN_175_OFF_REGION                     _156PIN_PIN_52_OFF_REGION
#define _PIN_170_OFF_REGION                     _156PIN_PIN_47_OFF_REGION
#define _PIN_171_OFF_REGION                     _156PIN_PIN_48_OFF_REGION
#define _PIN_172_OFF_REGION                     _156PIN_PIN_49_OFF_REGION
#define _PIN_178_OFF_REGION                     _156PIN_PIN_54_OFF_REGION
#define _PIN_189                                _156PIN_PIN_61
#define _PIN_192                                _156PIN_PIN_63
#define _PIN_194                                _156PIN_PIN_64
#define _PIN_195                                _156PIN_PIN_65
#define _PIN_197                                _156PIN_PIN_66
#define _PIN_198                                _156PIN_PIN_67
#define _PIN_199                                _156PIN_PIN_68
#define _PIN_200                                _156PIN_PIN_69
#define _PIN_201                                _156PIN_PIN_70
#define _PIN_202                                _156PIN_PIN_71
#define _PIN_203                                _156PIN_PIN_72
#define _PIN_204                                _156PIN_PIN_73
#define _PIN_205                                _156PIN_PIN_74
#define _PIN_209                                _156PIN_PIN_76
#define _PIN_210                                _156PIN_PIN_77
#define _PIN_211                                _156PIN_PIN_78
#define _PIN_214                                _156PIN_PIN_79
#define _PIN_215                                _156PIN_PIN_80
#define _PIN_216                                _156PIN_PIN_81
#define _PIN_141_OFF_REGION                     _156PIN_PIN_26_OFF_REGION
#define _PIN_142_OFF_REGION                     _156PIN_PIN_27_OFF_REGION
#define _PIN_143_OFF_REGION                     _156PIN_PIN_28_OFF_REGION
#define _PIN_144_OFF_REGION                     _156PIN_PIN_29_OFF_REGION
#define _PIN_145_OFF_REGION                     _156PIN_PIN_30_OFF_REGION
#define _PIN_146_OFF_REGION                     _156PIN_PIN_31_OFF_REGION
#define _PIN_147_OFF_REGION                     _156PIN_PIN_32_OFF_REGION
#define _PIN_148_OFF_REGION                     _156PIN_PIN_33_OFF_REGION
#define _PIN_152_OFF_REGION                     _156PIN_PIN_35_OFF_REGION
#define _PIN_153_OFF_REGION                     _156PIN_PIN_36_OFF_REGION
#define _PIN_154_OFF_REGION                     _156PIN_PIN_37_OFF_REGION
#define _PIN_155_OFF_REGION                     _156PIN_PIN_38_OFF_REGION
#define _PIN_156_OFF_REGION                     _156PIN_PIN_39_OFF_REGION
#define _PIN_157_OFF_REGION                     _156PIN_PIN_40_OFF_REGION
#define _PIN_158_OFF_REGION                     _156PIN_PIN_41_OFF_REGION
#define _PIN_159_OFF_REGION                     _156PIN_PIN_42_OFF_REGION
#define _PIN_160_OFF_REGION                     _156PIN_PIN_43_OFF_REGION
#define _PIN_161_OFF_REGION                     _156PIN_PIN_44_OFF_REGION

//--------------------------------------------------
// Not Bonded Pin
//--------------------------------------------------
// NC
#define _PIN_15                                 (1 & 0x0F) // Page 10-0x02[2:0]
// 0 ~ 2 (0: P1D2i<I>, 1: P1D2o<PP>, 2: P1D2o<OD> & d2_hdmi_hpd_int <I>)

// NC
#define _PIN_93                                 (1 & 0x0F) // Page 10-0x0E[2:0]
// 0 ~ 6 (0: P3D6i<I>,     1: P3D6o<PP>, 2: P3D6o<OD>, 3: a_adc2_0, 4: tcon[9],
//        5: test4b_out0 , 6:test4b_out1)

// NC
#define _PIN_94                                 (1 & 0x0F) // Page 10-0x0F[2:0]
// 0 ~ 6 (0: P3D7i<I>,     1: P3D7o<PP>, 2: P3D7o<OD>, 3: a_adc3_0, 4: tcon[10],
//        5: test4b_out2 , 6:test4b_out3)

// NC
#define _PIN_89                                 (1 & 0x0F) // Page 10-0x10[2:0]
// 0 ~ 3 (0: P4D0i<I>, 1: P4D0o<PP>, 2: P4D0o<OD>, 3: DPTX_aux_ch_p)

// NC
#define _PIN_90                                 (1 & 0x0F) // Page 10-0x11[2:0]
// 0 ~ 3 (0: P4D1i<I>, 1: P4D1o<PP>, 2: P4D1o<OD>, 3: DPTX_aux_ch_n)

// NC
#define _PIN_164_OFF_REGION                     (1 & 0x0F) // Page 10-0x1C[2:0]
// 0 ~ 6 (0: P5D4i<I>,   1: P5D4o<PP>, 2: P5D4o<OD>, 3: ws, 4: tcon[12],
//        5:test4b_out0, 6: test4b_out1)

// NC
#define _PIN_165_OFF_REGION                     (1 & 0x0F) // Page 10-0x1D[2:0]
// 0 ~ 5 (0: P5D5i<I>,    1: P5D5o<PP>, 2: P5D5o<OD>, 3: sck, 4: tcon[13] ,
//        5: test4b_out2, 6:  test4b_out3)

// NC
#define _PIN_166_OFF_REGION                     (1 & 0x0F) // Page 10-0x1E[2:0]
// 0 ~ 7 (0: P5D6i<I>,    1: P5D6o<PP>,  2: P5D6o<OD>, 3: mck, 4: test4b_out0 ,
//        5: test4b_out1, 6: test4b_out2 7: test4b_out3)

// NC
#define _PIN_167_OFF_REGION                     (1 & 0x0F) // Page 10-0x1F[2:0]
// 0 ~ 6 (0: P5D7i<I>,    1: P5D7o<PP>, 2: P5D7o<OD>, 3: spdif0, 4: sd0,
//        5: test4b_out0, 6: test4b_out1)

// NC
#define _PIN_168_OFF_REGION                     (1 & 0x0F) // Page 10-0x20[2:0]
// 0 ~ 8  (0: P6D0i<I>, 1: P6D0o<PP>, 2: P6D0o<OD>, 3: clko, 4: t0, 8: usb_spi_clk)

// NC
#define _PIN_169_OFF_REGION                     (1 & 0x0F) // Page 10-0x21[2:0]
// 0 ~ 8  (0: P6D1i<I>, 1: P6D1o<PP>, 2: P6D1o<OD>, 3: int0, 4: t1, 5: dena,
//         8: usb_spi_si )

// NC
#define _PIN_179_OFF_REGION                     (1 & 0x0F) // Page 10-0x26[2:0]
// 0 ~ 8 (0: P6D6i<I>, 1: P6D6o<PP>, 2: P6D6o<OD>, 3: TCON[6],
//        4: IHS_after_scaling_down, 8: IICSCL1)

// NC
#define _PIN_180_OFF_REGION                     (1 & 0x0F) // Page 10-0x27[2:0]
// 0 ~ 8 (0: P6D7i<I>, 1: P6D7o<PP>, 2: P6D7o<OD>, 3: tcon[7],
//        4: IVS_after_scaling_down, 8: IICSDA1)

// NC
#define _PIN_183_OFF_REGION                     (1 & 0x0F) // Page 10-0x28[2:0]
// 0 ~ 4 (0: P7D0i<I>, 1: P7D0o<PP>, 2: P7D0o<OD>, 3: tcon[5],
//        4: IENA_after_scaling_down)

// NC
#define _PIN_193                                (1 & 0x0F) // Page 10-0x2B[2:0]
// 0 ~ 7 (0: P7D3i<I>, 1: P7D3o<PP>,  2: P7D3o<OD>, 3: PWM4<PP>, 4: PWM4<OD>,
//        5: TCON[3],  6:Test4b_out2, 7: Test4b_out3)

// NC
#define _PIN_196                                (1 & 0x0F) // Page 10-0x2E[2:0]
// 0 ~ 7 (0: P7D6i<I>,    1: P7D6o<PP>,   2: P7D6o<OD>, 3: DPTX_hpd_org, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// NC
#define _PIN_208                                (1 & 0x0F) // Page 10-0x38[2:0]
// 0 ~ 7 (0: P9D0i<I>,    1: P9D0o<PP>,   2: P9D0o<OD>, 3: CEC0_line_pio_in,
//        4: Test4b_out0, 5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// NC
#define _PIN_212                                (2 & 0x0F) // Page 10-0x3C[2:0]
// 0 ~ 8 (0: P9D4i<I>, 1: Reserved, 2: P9D4o<OD>, 8: DDCSCL2)

// NC
#define _PIN_213                                (2 & 0x0F) // Page 10-0x3D[2:0]
// 0 ~ 8 (0: P9D5i<I>, 1: Reserved, 2: P9D5o<OD>, 8: DDCSDA2)

// NC
#define _PIN_139_OFF_REGION                     (2 & 0x0F) // Page 10-0x45[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD1i<I>, 2: PAD1o<PP>, 3: PAD1o<OD>, 4: TXB4+_10b)

// NC
#define _PIN_140_OFF_REGION                     (2 & 0x0F) // Page 10-0x46[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD2i<I>, 2: PAD2o<PP>, 3: PAD2o<OD>, 4: TXB4-_10b)

// NC
#define _PIN_150_OFF_REGION                     (2 & 0x0F) // Page 10-0x4F[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD3i<I>, 2: PBD3o<PP>, 3: PBD3o<OD>, 4: TXA4+_10b)

// NC
#define _PIN_151_OFF_REGION                     (2 & 0x0F) // Page 10-0x50[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD4i<I>, 2: PBD4o<PP>, 3: PBD4o<OD>, 4: TXA4+_10b)

// NC
#define _PIN_97                                 (1 & 0x0F) // Page 10-0x5B[2:0]
// 0 ~ 5 (0: PCD7i<I>, 1: PCD7o<PP>, 2: PCD7o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: PWM_out )

// NC
#define _PIN_98                                 (1 & 0x0F) // Page 10-0x5C[2:0]
// 0 ~ 3 (0: PDD0i<I>, 1: PDD0o<PP>, 2: PDD0o<OD>, 3: PWM_in)

