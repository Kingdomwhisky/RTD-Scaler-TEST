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
// ID Code      : RL6449_PCB_EXAMPLE_PINSHARE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


/////////////////////////////
// RL6449 Series Pin Share //
/////////////////////////////

//--------------------------------------------------
//  RL6449 156 Pin Share
//--------------------------------------------------
#define _156PIN_PIN_4                           (1 & 0x0F) // Page 10-0x00[2:0]
// 0 ~ 2 (0: P1D0i<I>, 1: P1D0o<PP>, 2: P1D0o<OD> & d3_hdmi_hpd_int<I>)

#define _156PIN_PIN_17                          (1 & 0x0F) // Page 10-0x01[2:0]
// 0 ~ 2 (0: P1D1i<I>, 1: P1D1o<PP>, 2: P1D1o<OD> & d2_hdmi_hpd_int<I>)

#define _156PIN_PIN_45                          (1 & 0x0F) // Page 10-0x02[2:0]
// 0 ~ 8 (0: P1D2i<I>, 1: P1D2o<PP>, 2: P1D2o<OD>, 8: ddcsclvga<OD>)

#define _156PIN_PIN_46                          (1 & 0x0F) // Page 10-0x03[2:0]
// 0 ~ 8 (0: P1D3i<I>, 1: P1D3o<PP>, 2: P1D3o<OD>, 8: ddcsdavga<I>)

#define _156PIN_PIN_47                          (1 & 0x0F) // Page 10-0x04[2:0]
// 0 ~ 7 (0: P1D4i<I>, 1: P1D4o<PP>, 2: P1D4o<OD>, 3: tcon[1],
//        4: test4b_out0, 5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

#define _156PIN_PIN_48                          (1 & 0x0F) // Page 10-0x05[2:0]
// 0 ~ 7 (0: P1D5i<I>, 1: P1D5o<PP>, 2: P1D5o<OD>,  3: tcon[3], 4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

#define _156PIN_PIN_49                          (1 & 0x0F) // Page 10-0x06[2:0]
// 0 ~ 7 (0: P1D6i<I>, 1: P1D6o<PP>, 2: P1D6o<OD>, 3: tcon[0], 4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

#define _156PIN_PIN_50                          (1 & 0x0F) // Page 10-0x07[2:0]
// 0 ~ 7 (0: P1D7i<I>, 1: P1D7o<PP>, 2: P1D7o<OD>, 3: tcon[8], 4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

#define _156PIN_PIN_51                          (1 & 0x0F) // Page 10-0x08[2:0]
// 0 ~ 4 (0: P3D0i<I>, 1:P3D0o<PP>, 2: P3D0o<OD>, 3: tcon[4], 4: dptx_hpd_org<I>

#define _156PIN_PIN_54                          (0 & 0x0F) // Page 10-0x09[2:0]
// 0 ~ 3 (0: P3D1i<I>, 1: Reserved, 2: P3D1o<OD>, 3: auxp0)

#define _156PIN_PIN_55                          (0 & 0x0F) // Page 10-0x0A[2:0]
// 0 ~ 3 (0: P3D2i<I>, 1: Reserved, 2: P3D2o<OD>, 3: auxn0)

#define _156PIN_PIN_56                          (0 & 0x0F) // Page 10-0x0B[2:0]
// 0 ~ 3 (0: P3D3i<I>, 1: Reserved, 2: P3D3o<OD>, 3: auxp1)

#define _156PIN_PIN_57                          (0 & 0x0F) // Page 10-0x0C[2:0]
// 0 ~ 3 (0: P3D4i<I>, 1: Reserved, 2: P3D4o<OD>, 3: auxn1)

#define _156PIN_PIN_62                          (1 & 0x0F) // Page 10-0x0D[2:0]
// 0 ~ 3 (0: P3D5i<I>, 1: P3D5o<PP>, 2: P3D5o<OD>, 3: dptx_aux_ch_p)

#define _156PIN_PIN_63                          (1 & 0x0F) // Page 10-0x0E[2:0]
// 0 ~ 3 (0: P3D6i<I>, 1: P3D6o<PP>, 2: P3D6o<OD>, 3: dptx_aux_ch_n)

#define _156PIN_PIN_65                          (1 & 0x0F) // Page 10-0x0F[2:0]
// 0 ~ 6 (0: P3D7i<I>, 1: P3D7o<PP>, 2: P3D7o<OD>, 3: a_adc0_0, 4: int0,
//        5: test4b_out0 , 6:test4b_out1)

#define _156PIN_PIN_66                          (1 & 0x0F) // Page 10-0x10[2:0]
// 0 ~ 6 (0: P4D0i<I>, 1: P4D0o<PP>, 2: P4D0o<OD>, 3: a_adc1_0, 4: int1,
//        5: test4b_out2 , 6:test4b_out3)

#define _156PIN_PIN_67                          (1 & 0x0F) // Page 10-0x11[2:0]
// 0 ~ 6 (0: P4D1i<I>, 1: P4D1o<PP>, 2: P4D1o<OD>,  3: a_adc2_0, 4: tcon[9],
//        5: test4b_out0 , 6:test4b_out1)

#define _156PIN_PIN_68                          (1 & 0x0F) // Page 10-0x12[2:0]
// 0 ~ 6 (0: P4D2i<I>, 1: P4D2o<PP>, 2: P4D2o<OD>, 3: a_adc3_0, 4: tcon[10],
//        5: test4b_out2 , 6:test4b_out3)

#define _156PIN_PIN_79_OFF_REGION               (1 & 0x0F) // Page 10-0x13[2:0]
// 0 ~ 5 (0: P4D3i<I>, 1: P4D3o<PP>, 2: P4D3o<OD>, 3: audio_houtl, 4: sd2, 5: spdif2)

#define _156PIN_PIN_80_OFF_REGION               (1 & 0x0F) // Page 10-0x14[2:0]
// 0 ~ 5 (0: P4D4i<I>, 1: P4D4o<PP>, 2: P4D4o<OD>, 3: audio_houtr, 4: sd3, 5: spdif3)

#define _156PIN_PIN_83_OFF_REGION               (1 & 0x0F) // Page 10-0x15[2:0]
// 0 ~ 4 (0: P4D5i<I>, 1: P4D5o<PP>, 2: P4D5o<OD>, 3: line_inl, 4: ws)

#define _156PIN_PIN_84_OFF_REGION               (1 & 0x0F) // Page 10-0x16[2:0]
// 0 ~ 4 (0: P4D6i<I>, 1: P4D6o<PP>, 2: P4D6o<OD>, 3: line_inr, 4: sck)

#define _156PIN_PIN_85_OFF_REGION               (1 & 0x0F) // Page 10-0x17[2:0]
// 0 ~ 4 (0: P4D7i<I>, 1: P4D7o<PP>, 2: P4D7o<OD>, 3: audio_ref, 4: mck)

#define _156PIN_PIN_86_OFF_REGION               (1 & 0x0F) // Page 10-0x18[2:0]
// 0 ~ 5 (0: P5D0i<I>, 1: P5D0o<PP>, 2: P5D0o<OD>, 3: audio_soutl, 4: sd0, 5: spdif0)

#define _156PIN_PIN_87_OFF_REGION               (1 & 0x0F) // Page 10-0x19[2:0]
// 0 ~ 5 (0: P5D1i<I>, 1: P5D1o<PP>, 2: P5D1o<OD>, 3: audio_soutr, 4: sd1, 5: spdif1)

#define _156PIN_PIN_103_OFF_REGION              (1 & 0x0F) // Page 10-0x1A[2:0]
// 0 ~ 3 (0: P5D2i<I>, 1: P5D2o<PP>, 2: P5D2o<OD>, 3: dptx_aux_ch_p_2

#define _156PIN_PIN_104_OFF_REGION              (1 & 0x0F) // Page 10-0x1B[2:0]
// 0 ~ 3 (0: P5D3i<I>, 1: P5D3o<PP>, 2: P5D3o<OD>, 3: dptx_aux_ch_n_2

#define _156PIN_PIN_105_OFF_REGION              (1 & 0x0F) // Page 10-0x1C[2:0]
// 0 ~ 4 (0: P5D4i<I>, 1: P5D4o<PP>, 2: P5D4o<OD>, 3: dptx_hpd2_org, 4: vb1_lock_n,

#define _156PIN_PIN_106_OFF_REGION              (1 & 0x0F) // Page 10-0x1D[2:0]
// 0 ~ 3 (0: P5D5i<I>, 1: P5D5o<PP>, 2: P5D5o<OD>, 3: dptx_aux_ch_p_1

#define _156PIN_PIN_107_OFF_REGION              (1 & 0x0F) // Page 10-0x1E[2:0]
// 0 ~ 3 (0: P5D6i<I>, 1: P5D6o<PP>,  2: P5D6o<OD>, 3: dptx_aux_ch_n_1)

#define _156PIN_PIN_108_OFF_REGION              (1 & 0x0F) // Page 10-0x1F[2:0]
// 0 ~ 4 (0: P5D7i<I>, 1: P5D7o<PP>, 2: P5D7o<OD>, 3: dptx_hpd1_org,
//        4: vb1_htpd_n)

#define _156PIN_PIN_109_OFF_REGION              (1 & 0x0F) // Page 10-0x20[2:0]
// 0 ~ 8 (0: P6D0i<I>, 1: P6D0o<PP>, 2: P6D0o<OD>, 3: tcon[2], 8: iicscl1

#define _156PIN_PIN_110_OFF_REGION              (1 & 0x0F) // Page 10-0x21[2:0]
// 0 ~ 8 (0: P6D1i<I>, 1: P6D1o<PP>, 2: P6D1o<OD>, 3: pwm1<PP>, 4: pwm1<OD>,
//        8: iicsda1)

#define _156PIN_PIN_111_OFF_REGION              (1 & 0x0F) // Page 10-0x22[2:0]
// 0 ~ 5 (0: P6D2i<I>, 1: P6D2o<PP>, 2: P6D2o<OD>, 3: pwm2<PP>, 4: pwm2<OD>,
//        5: tcon[3])

#define _156PIN_PIN_112_OFF_REGION              (1 & 0x0F) // Page 10-0x23[2:0]
// 0 ~ 7 (0: P6D3i<I>, 1: P6D3o<PP>, 2: P6D3o<OD>, 3: pwm5<PP>, 4: pwm5<OD>,
//        5: tcon[2],  6:test4b_out0, 7: test4b_out1)

#define _156PIN_PIN_113_OFF_REGION              (1 & 0x0F) // Page 10-0x24[2:0]
// 0 ~ 8 (0: P6D4i<I>, 1: P6D4o<PP>, 2: P6D4o<OD>, 3: t0, 8: usb_spi_clk)

#define _156PIN_PIN_114_OFF_REGION              (1 & 0x0F) // Page 10-0x25[2:0]
// 0 ~ 8 (0: P6D5i<I>, 1: P6D5o<PP>, 2: P6D5o<OD>, 3: int0, 4: t1, 8: usb_spi_si)

#define _156PIN_PIN_115_OFF_REGION              (1 & 0x0F) // Page 10-0x26[2:0]
// 0 ~ 8 (0: P6D6i<I>, 1: P6D6o<PP>, 2: P6D6o<OD>, 3: int1, 4: t2, 8: usb_spi_so)

#define _156PIN_PIN_116_OFF_REGION              (1 & 0x0F) // Page 10-0x27[2:0]
// 0 ~ 8 (0: P6D7i<I>, 1: P6D7o<PP>, 2: P6D7o<OD>, 3: irqb, 4: ttl_dvs,
//        8: usb_spi_ceb0)

#define _156PIN_PIN_117_OFF_REGION              (1 & 0x0F) // Page 10-0x28[2:0]
// 0 ~ 8 (0: P7D0i<I>, 1: P7D0o<PP>, 2: P7D0o<OD>, 3: t2ex, 8: usb_spi_ceb1)

#define _156PIN_PIN_118_OFF_REGION              (1 & 0x0F) // Page 10-0x29[2:0]
// 0 ~ 6 (0: P7D1i<I>, 1: P7D1o<PP>, 2: P7D1o<OD>, 3:ws, 4: tcon[12], 5:test4b_out0
//        6: test4b_out1)

#define _156PIN_PIN_119_OFF_REGION              (1 & 0x0F) // Page 10-0x2A[2:0]
// 0 ~ 6 (0: P7D2i<I>, 1: P7D2o<PP>, 2: P7D2o<OD>, 3: sck, 4: tcon[13],
//        5: test4b_out2, 6: test4b_out3)

#define _156PIN_PIN_120_OFF_REGION              (1 & 0x0F) // Page 10-0x2B[2:0]
// 0 ~ 7 (0: P7D3i<I>, 1: P7D3o<PP>, 2: P7D3o<OD>, 3: mck, 4: test4b_out0,
//        5: test4b_out1, 6:test4b_out2, 7:test4b_out3)

#define _156PIN_PIN_121_OFF_REGION              (1 & 0x0F) // Page 10-0x2C[2:0]
// 0 ~ 6 (0: P7D4i<I>, 1: P7D4o<PP>, 2: P7D4o<OD>, 3: pwm0<PP>, 4: pwm0<OD>,
//        5: spdif0, 6: sd0)

#define _156PIN_PIN_135                         (1 & 0x0F) // Page 10-0x31[2:0]
// 0 ~ 7 (0: P8D1i<I>, 1: P8D1o<PP>, 2: P8D1o<OD>, 3: ttl_dhs, 4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7:test4b_out3)

#define _156PIN_PIN_136                         (1 & 0x0F) // Page 10-0x33[2:0]
// 0 ~ 7 (0: P8D3i<I>, 1: P8D3o<PP>, 2: P8D3o<OD>, 3: dclk, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

#define _156PIN_PIN_138                         (1 & 0x0F) // Page 10-0x35[2:0]
// 0 ~ 6 (0: P8D5i<I>, 1: P8D5o<PP>, 2: P8D5o<OD>, 3: pwm1<PP>, 4: pwm1<OD>,
//        5: tcon[7], 6: m1_idomain_den_out)

#define _156PIN_PIN_143                         (1 & 0x0F) // Page 10-0x36[2:0]
// 0 ~ 2 (0: P8D6i<I>, 1: P8D6o<PP>, 2: P8D6o<OD>)

#define _156PIN_PIN_146                         (1 & 0x0F) // Page 10-0x38[2:0]
// 0 ~ 6 (0: P9D0i<I>, 1: P9D0o<PP>, 2: P9D0o<OD>, 3: pwm2<PP>, 4: pwm2<PP>,
//        5: tcon[6], 6: irda_in)

#define _156PIN_PIN_147                         (1 & 0x0F) // Page 10-0x39[2:0]
// 0 ~ 6 (0: P9D1i<I>, 1: P9D1o<PP>, 2: P9D1o<OD>, 3: PWM4<PP>, 4: PWM4<OD>
//        5: tcon[7], 6: pwm_out)

#define _156PIN_PIN_148                         (1 & 0x0F) // Page 10-0x3D[2:0]
// 0 ~ 5 (0: P9D5i<I>, 1: P9D5o<PP>, 2: P9D5o<OD>, 3: pwm5<PP>, 4: pwm5<OD>,
//        5: pwm_in)

#define _156PIN_PIN_149                         (1 & 0x0F) // Page 10-0x40[2:0]
// 0 ~ 8 (0: PAD0i<I>, 1: PAD0o<PP>, 2: PAD0o<OD>, 3: int0, 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3, 8: txd)

#define _156PIN_PIN_150                         (1 & 0x0F) // Page 10-0x41[2:0]
// 0 ~ 8 (0: PAD1i<I>, 1: PAD1o<PP>, 2: PAD1o<OD>, 3: int1, 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3, 8: rxd)

#define _156PIN_PIN_152                         (1 & 0x0F) // Page 10-0x46[2:0]
// 0 ~ 2 (0: PAD6i<I>, 1: PAD6o<PP>, 2: PAD6o<OD>)

#define _156PIN_PIN_153                         (1 & 0x0F) // Page 10-0x47[2:0]
// 0 ~ 8 (0: PAD7i<I>, 1: PAD7o<PP>, 2: PAD7o<OD>, 8: eeiicscl)

#define _156PIN_PIN_154                         (1 & 0x0F) // Page 10-0x48[2:0]
// 0 ~ 8 (0: PBD0i<I>, 1: PBD0o<PP>, 2: PBD0o<OD>, 8: eeiicsda)

#define _156PIN_PIN_155                         (0 & 0x0F) // Page 10-0x49[2:0]
// 0 ~ 8 (0: PBD1i<I>, 1: Reserved, 2: PBD1o<OD>, 8: ddcscl2)

#define _156PIN_PIN_156                         (0 & 0x0F) // Page 10-0x4A[2:0]
// 0 ~ 8 (0: PBD2i<I>, 1: Reserved, 2: PBD2o<OD>, 8: ddcsda2)

#define _156PIN_PIN_1                           (0 & 0x0F) // Page 10-0x4B[2:0]
// 0 ~ 8 (0: PBD3i<I>, 1: Reserved, 2: PBD3o<OD>, 8: ddcscl3)

#define _156PIN_PIN_2                           (0 & 0x0F) // Page 10-0x4C[2:0]
// 0 ~ 8 (0: PBD4i<I>, 1: Reserved, 2: PBD4o<OD>, 8: ddcsda3 )

