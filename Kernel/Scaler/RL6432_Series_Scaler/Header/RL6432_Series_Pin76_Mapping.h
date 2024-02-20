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
// ID Code      : RL6432_Series_Pin76_Mapping.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Mapping List
//--------------------------------------------------
#define _PIN_53                                 _76PIN_PIN_16
#define _PIN_54                                 _76PIN_PIN_17
#define _PIN_58                                 _76PIN_PIN_21
#define _PIN_59                                 _76PIN_PIN_22
#define _PIN_60                                 _76PIN_PIN_23
#define _PIN_61                                 _76PIN_PIN_24
#define _PIN_62                                 _76PIN_PIN_25
#define _PIN_64                                 _76PIN_PIN_27
#define _PIN_65                                 _76PIN_PIN_28
#define _PIN_66                                 _76PIN_PIN_29
#define _PIN_67                                 _76PIN_PIN_30
#define _PIN_68                                 _76PIN_PIN_31
#define _PIN_70                                 _76PIN_PIN_32
#define _PIN_73                                 _76PIN_PIN_33
#define _PIN_74                                 _76PIN_PIN_34
#define _PIN_86                                 _76PIN_PIN_36
#define _PIN_87                                 _76PIN_PIN_37
#define _PIN_91                                 _76PIN_PIN_39
#define _PIN_92                                 _76PIN_PIN_38
#define _PIN_95                                 _76PIN_PIN_40
#define _PIN_109                                _76PIN_PIN_41
#define _PIN_111                                _76PIN_PIN_42
#define _PIN_119                                _76PIN_PIN_43
#define _PIN_120                                _76PIN_PIN_44
#define _PIN_121                                _76PIN_PIN_45
#define _PIN_122                                _76PIN_PIN_46
#define _PIN_173_OFF_REGION                     _76PIN_PIN_56_OFF_REGION
#define _PIN_174_OFF_REGION                     _76PIN_PIN_58_OFF_REGION
#define _PIN_175_OFF_REGION                     _76PIN_PIN_57_OFF_REGION
#define _PIN_182                                _76PIN_PIN_59
#define _PIN_185                                _76PIN_PIN_61
#define _PIN_186                                _76PIN_PIN_62
#define _PIN_187                                _76PIN_PIN_63
#define _PIN_189                                _76PIN_PIN_65
#define _PIN_191                                _76PIN_PIN_60
#define _PIN_192                                _76PIN_PIN_66
#define _PIN_198                                _76PIN_PIN_68
#define _PIN_199                                _76PIN_PIN_69
#define _PIN_200                                _76PIN_PIN_67
#define _PIN_201                                _76PIN_PIN_70
#define _PIN_202                                _76PIN_PIN_71
#define _PIN_203                                _76PIN_PIN_72
#define _PIN_204                                _76PIN_PIN_73
#define _PIN_205                                _76PIN_PIN_74
#define _PIN_209                                _76PIN_PIN_75
#define _PIN_210                                _76PIN_PIN_76
#define _PIN_211                                _76PIN_PIN_1

//--------------------------------------------------
// Not Bonded Pin
//--------------------------------------------------
// NC
#define _PIN_1                                  (1 & 0x0F) // Page 10-0x00[2:0]
// 0 ~ 6 (0: P1D0i<I>,    1: P1D0o<PP>,   2: P1D0o<OD>, 3: test4b_out0,
//        4: test4b_out1, 5: test4b_out2, 6: test4b_out3)

// NC
#define _PIN_3                                  (1 & 0x0F) // Page 10-0x01[2:0]
// 0 ~ 2 (0: P1D1i<I>, 1: P1D1o<PP>, 2: P1D1o<OD> & d3_hdmi_hpd_int<I>)

// NC
#define _PIN_15                                 (1 & 0x0F) // Page 10-0x02[2:0]
// 0 ~ 2 (0: P1D2i<I>, 1: P1D2o<PP>, 2: P1D2o<OD> & d2_hdmi_hpd_int <I>)

// NC
#define _PIN_71                                 (2 & 0x0F) // Page 10-0x08[2:0]
// 0 ~ 3 (0: P3D0i<I>, 1: Reserved, 2: P3D0o<OD>, 3: AUXp0)

// NC
#define _PIN_72                                 (2 & 0x0F) // Page 10-0x09[2:0]
// 0 ~ 3 (0: P3D1i<I>, 1: Reserved, 2: P3D1o<OD>, 3: AUXn0)

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
#define _PIN_99                                 (1 & 0x0F) // Page 10-0x12[2:0]
// 0 ~ 5 (0: P4D2i<I>, 1: P4D2o<PP>, 2: P4D2o<OD>, 3: Audio_houtl, 4: sd2, 5: spdif2)

// NC
#define _PIN_100                                (1 & 0x0F) // Page 10-0x13[2:0]
// 0 ~ 5 (0: P4D3i<I>, 1: P4D3o<PP>, 2: P4D3o<OD>, 3: Audio_houtr, 4: sd3, 5: spdif3)

// NC
#define _PIN_103                                (1 & 0x0F) // Page 10-0x14[2:0]
// 0 ~ 4 (0: P4D4i<I>, 1: P4D4o<PP>, 2: P4D4o<OD>, 3: line_inl, 4: ws)

// NC
#define _PIN_104                                (1 & 0x0F) // Page 10-0x15[2:0]
// 0 ~ 4 (0: P4D5i<I>, 1: P4D5o<PP>, 2: P4D5o<OD>, 3: line_inr, 4: sck)

// NC
#define _PIN_105                                (1 & 0x0F) // Page 10-0x16[2:0]
// 0 ~ 4 (0: P4D6i<I>, 1: P4D6o<PP>, 2: P4D6o<OD>, 3: Audio_ref, 4: mck)

// NC
#define _PIN_106                                (1 & 0x0F) // Page 10-0x17[2:0]
// 0 ~ 5 (0: P4D7i<I>, 1: P4D7o<PP>, 2: P4D7o<OD>, 3: Audio_soutl, 4: sd0,
//        5: spdif0)

// NC
#define _PIN_107                                (1 & 0x0F) // Page 10-0x18[2:0]
// 0 ~ 5 (0: P5D0i<I>, 1: P5D0o<PP>, 2: P5D0o<OD>, 3: Audio_soutr, 4: sd1,
//        5: spdif1)

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
#define _PIN_170_OFF_REGION                     (1 & 0x0F) // Page 10-0x22[2:0]
// 0 ~ 8  (0: P6D2i<I>, 1: P6D2o<PP>, 2: P6D2o<OD>, 3: int1, 4: t2, 5: DCLK,
//         8: usb_spi_so)

// NC
#define _PIN_171_OFF_REGION                     (1 & 0x0F) // Page 10-0x23[2:0]
// 0 ~ 8  (0: P6D3i<I>, 1: P6D3o<PP>, 2: P6D3o<OD>, 3: IRQB, 4: DVS,
//         8: usb_spi_ceb0)

// NC
#define _PIN_172_OFF_REGION                     (1 & 0x0F) // Page 10-0x24[2:0]
// 0 ~ 8 (0: P6D4i<I>, 1: P6D4o<PP>, 2: P6D4o<OD>, 3: T2ex, 4: DHS,
//        8: usb_spi_ceb1)

// NC
#define _PIN_178_OFF_REGION                     (1 & 0x0F) // Page 10-0x25[2:0]
// 0 ~ 7 (0: P6D5i<I>, 1: P6D5o<PP>,   2: P6D5o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[2],  6: test4b_out0, 7: test4b_out1)

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
#define _PIN_194                                (1 & 0x0F) // Page 10-0x2C[2:0]
// 0 ~ 7 (0: P7D4i<I>, 1: P7D4o<PP>, 2: P7D4o<OD>, 3: tcon[5], 4: pwm_out,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// NC
#define _PIN_195                                (1 & 0x0F) // Page 10-0x2D[2:0]
// 0 ~ 7 (0: P7D5i<I>,    1: P7D5o<PP>,   2: P7D5o<OD>, 3: tcon[4], 4: pwm_in,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// NC
#define _PIN_196                                (1 & 0x0F) // Page 10-0x2E[2:0]
// 0 ~ 7 (0: P7D6i<I>,    1: P7D6o<PP>,   2: P7D6o<OD>, 3: DPTX_hpd_org, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// NC (DDR_PW_EN)
#define _PIN_197                                (1 & 0x0F) // Page 10-0x2F[2:0]
// 0 ~ 5 (0: P7D7i<I>, 1: P7D7o<PP>, 2: P7D7o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[11])

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
#define _PIN_214                                (2 & 0x0F) // Page 10-0x3E[2:0]
// 0 ~ 8 (0: P9D6i<I>, 1: Reserved, 2: P9D6o<OD>, 8: DDCSCL3)

// NC
#define _PIN_215                                (2 & 0x0F) // Page 10-0x3F[2:0]
// 0 ~ 8 (0: P9D7i<I>, 1: Reserved, 2: P9D7o<OD>, 8: DDCSDA3)

// NC
#define _PIN_216                                (1 & 0x0F) // Page 10-0x40[2:0]
// 0 ~ 6 (0: PAD0i<I>,    1: PAD0o<PP>, 2: PAD0o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// NC
#define _PIN_139_OFF_REGION                     (2 & 0x0F) // Page 10-0x45[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD1i<I>, 2: PAD1o<PP>, 3: PAD1o<OD>, 4: TXB4+_10b)

// NC
#define _PIN_140_OFF_REGION                     (2 & 0x0F) // Page 10-0x46[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD2i<I>, 2: PAD2o<PP>, 3: PAD2o<OD>, 4: TXB4-_10b)

// NC
#define _PIN_141_OFF_REGION                     (2 & 0x0F) // Page 10-0x47[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD3i<I>, 2: PAD3o<PP>, 3: PAD3o<OD>, 4: TXB3+_10b)

// NC
#define _PIN_142_OFF_REGION                     (2 & 0x0F) // Page 10-0x48[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD4i<I>, 2: PAD4o<PP>, 3: PAD4o<OD>, 4: TXB3-_10b)

// NC
#define _PIN_143_OFF_REGION                     (2 & 0x0F) // Page 10-0x49[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD5i<I>, 2: PAD5o<PP>, 3: PAD5o<OD>, 4: TXB2+_10b)

// NC
#define _PIN_144_OFF_REGION                     (2 & 0x0F) // Page 10-0x4A[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD6i<I>, 2: PAD6o<PP>, 3: PAD6o<OD>, 4: TXB2-_10b)

// NC
#define _PIN_145_OFF_REGION                     (2 & 0x0F) // Page 10-0x4B[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD7i<I>, 2: PAD7o<PP>, 3: PAD7o<OD>, 4: TXB1+_10b)

// NC
#define _PIN_146_OFF_REGION                     (2 & 0x0F) // Page 10-0x4C[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD0i<I>, 2: PBD0o<PP>, 3: PBD0o<OD>, 4: TXB1-_10b)

// NC
#define _PIN_147_OFF_REGION                     (2 & 0x0F) // Page 10-0x4D[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD1i<I>, 2: PBD1o<PP>, 3: PBD1o<OD>, 4: TXB0+_10b)

// NC
#define _PIN_148_OFF_REGION                     (2 & 0x0F) // Page 10-0x4E[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD2i<I>, 2: PBD2o<PP>, 3: PBD2o<OD>, 4: TXB0-_10b)

// NC
#define _PIN_150_OFF_REGION                     (2 & 0x0F) // Page 10-0x4F[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD3i<I>, 2: PBD3o<PP>, 3: PBD3o<OD>, 4: TXA4+_10b)

// NC
#define _PIN_151_OFF_REGION                     (2 & 0x0F) // Page 10-0x50[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD4i<I>, 2: PBD4o<PP>, 3: PBD4o<OD>, 4: TXA4+_10b)

// NC
#define _PIN_152_OFF_REGION                     (2 & 0x0F) // Page 10-0x51[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD5i<I>, 2: PBD5o<PP>, 3: PBD5o<OD>, 4: TXA3+_10b)

// NC
#define _PIN_153_OFF_REGION                     (2 & 0x0F) // Page 10-0x52[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD6i<I>, 2: PBD6o<PP>, 3: PBD6o<OD>, 4: TXA3-_10b)

// NC
#define _PIN_154_OFF_REGION                     (2 & 0x0F) // Page 10-0x53[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD7i<I>, 2: PBD7o<PP>, 3: PBD7o<OD>, 4: TXAC+_10b)

// NC
#define _PIN_155_OFF_REGION                     (2 & 0x0F) // Page 10-0x54[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD0i<I>, 2: PCD0o<PP>, 3: PCD0o<OD>, 4: TXAC-_10b)

// NC
#define _PIN_156_OFF_REGION                     (2 & 0x0F) // Page 10-0x55[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD1i<I>, 2: PCD1o<PP>, 3: PCD1o<OD>, 4: TXA2+_10b)

// NC
#define _PIN_157_OFF_REGION                     (2 & 0x0F) // Page 10-0x56[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD2i<I>, 2: PCD2o<PP>, 3: PCD2o<OD>, 4: TXA2-_10b)

// NC
#define _PIN_158_OFF_REGION                     (2 & 0x0F) // Page 10-0x57[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD3i<I>, 2: PCD3o<PP>, 3: PCD3o<OD>, 4: TXA1+_10b)

// NC
#define _PIN_159_OFF_REGION                     (2 & 0x0F) // Page 10-0x58[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD4i<I>, 2: PCD4o<PP>, 3: PCD4o<OD>, 4: TXA1-_10b)

// NC
#define _PIN_160_OFF_REGION                     (2 & 0x0F) // Page 10-0x59[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD5i<I>, 2: PCD5o<PP>, 3: PCD5o<OD>, 4: TXA0+_10b)

// NC
#define _PIN_161_OFF_REGION                     (2 & 0x0F) // Page 10-5A[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD6i<I>, 2: PCD6o<PP>, 3: PCD6o<OD>, 4: TXA0-_10b)

// NC
#define _PIN_97                                 (1 & 0x0F) // Page 10-0x5B[2:0]
// 0 ~ 5 (0: PCD7i<I>, 1: PCD7o<PP>, 2: PCD7o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: PWM_out )

// NC
#define _PIN_98                                 (1 & 0x0F) // Page 10-0x5C[2:0]
// 0 ~ 3 (0: PDD0i<I>, 1: PDD0o<PP>, 2: PDD0o<OD>, 3: PWM_in)

