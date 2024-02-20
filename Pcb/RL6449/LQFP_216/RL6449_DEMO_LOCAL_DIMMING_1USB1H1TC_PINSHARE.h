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
// ID Code      : RL6449_DEMO_LOCAL_DIMMING_1USB1H1TC_PINSHARE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


/////////////////////////////
// RL6449 Series Pin Share //
/////////////////////////////

//--------------------------------------------------
//  RL6449 216 Pin Share
//--------------------------------------------------
// HDMI1_HPD_CPU
#define _PIN_1                                  (2 & 0x0F) // Page 10-0x00[2:0]
// 0 ~ 2 (0: P1D0i<I>, 1: P1D0o<PP>, 2: P1D0o<OD> & d3_hdmi_hpd_int<I>)

// NC
#define _PIN_14                                 (1 & 0x0F) // Page 10-0x01[2:0]
// 0 ~ 2 (0: P1D1i<I>, 1: P1D1o<PP>, 2: P1D1o<OD> & d2_hdmi_hpd_int<I>)

// I2C_SCL_ISP
#define _PIN_65                                 (8 & 0x0F) // Page 10-0x02[2:0]
// 0 ~ 8 (0: P1D2i<I>, 1: P1D2o<PP>, 2: P1D2o<OD>, 8: ddcsclvga<OD>)

// I2C_SDA_ISP
#define _PIN_66                                 (8 & 0x0F) // Page 10-0x03[2:0]
// 0 ~ 8 (0: P1D3i<I>, 1: P1D3o<PP>, 2: P1D3o<OD>, 8: ddcsdavga<I>)

// GPIO_67_CPU_KEY_POWER
#define _PIN_67                                 (0 & 0x0F) // Page 10-0x04[2:0]
// 0 ~ 7 (0: P1D4i<I>, 1: P1D4o<PP>, 2: P1D4o<OD>, 3: tcon[1],
//        4: test4b_out0, 5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

// DP_SINK_CPU_N
#define _PIN_68                                 (0 & 0x0F) // Page 10-0x05[2:0]
// 0 ~ 7 (0: P1D5i<I>, 1: P1D5o<PP>, 2: P1D5o<OD>,  3: tcon[3], 4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

// C_CABLE_DET_GPIO
#define _PIN_69                                 (0 & 0x0F) // Page 10-0x06[2:0]
// 0 ~ 7 (0: P1D6i<I>, 1: P1D6o<PP>, 2: P1D6o<OD>, 3: tcon[0], 4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

// DP_SINK_CPU_P
#define _PIN_70                                 (0 & 0x0F) // Page 10-0x07[2:0]
// 0 ~ 7 (0: P1D7i<I>, 1: P1D7o<PP>, 2: P1D7o<OD>, 3: tcon[8], 4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

// NC
#define _PIN_71                                 (1 & 0x0F) // Page 10-0x08[2:0]
// 0 ~ 4 (0: P3D0i<I>, 1:P3D0o<PP>, 2: P3D0o<OD>, 3: tcon[4], 4: dptx_hpd_org<I>

// AUX_CHP_0
#define _PIN_74                                 (3 & 0x0F) // Page 10-0x09[2:0]
// 0 ~ 3 (0: P3D1i<I>, 1: Reserved, 2: P3D1o<OD>, 3: auxp0)

// AUX_CHN_0
#define _PIN_75                                 (3 & 0x0F) // Page 10-0x0A[2:0]
// 0 ~ 3 (0: P3D2i<I>, 1: Reserved, 2: P3D2o<OD>, 3: auxn0)

// NC
#define _PIN_76                                 (1 & 0x0F) // Page 10-0x0B[2:0]
// 0 ~ 3 (0: P3D3i<I>, 1: Reserved, 2: P3D3o<OD>, 3: auxp1)

// USBC_2LANE_DP_EVENT
#define _PIN_77                                 (0 & 0x0F) // Page 10-0x0C[2:0]
// 0 ~ 3 (0: P3D4i<I>, 1: Reserved, 2: P3D4o<OD>, 3: auxn1)

// I2C_1_SCL_EC
#define _PIN_91                                 (2 & 0x0F) // Page 10-0x0D[2:0]
// 0 ~ 3 (0: P3D5i<I>, 1: P3D5o<PP>, 2: P3D5o<OD>, 3: dptx_aux_ch_p)

// I2C_1_SDA_EC
#define _PIN_92                                 (2 & 0x0F) // Page 10-0x0E[2:0]
// 0 ~ 3 (0: P3D6i<I>, 1: P3D6o<PP>, 2: P3D6o<OD>, 3: dptx_aux_ch_n)

// GPIO_94_CPU_KEY1
#define _PIN_94                                 (3 & 0x0F) // Page 10-0x0F[2:0]
// 0 ~ 6 (0: P3D7i<I>, 1: P3D7o<PP>, 2: P3D7o<OD>, 3: a_adc0_0, 4: int0,
//        5: test4b_out0 , 6:test4b_out1)

// GPIO_95_CPU_KEY2
#define _PIN_95                                 (3 & 0x0F) // Page 10-0x10[2:0]
// 0 ~ 6 (0: P4D0i<I>, 1: P4D0o<PP>, 2: P4D0o<OD>, 3: a_adc1_0, 4: int1,
//        5: test4b_out2 , 6:test4b_out3)

// DP_HPD_CPU
#define _PIN_96                                 (1 & 0x0F) // Page 10-0x11[2:0]
// 0 ~ 6 (0: P4D1i<I>, 1: P4D1o<PP>, 2: P4D1o<OD>,  3: a_adc2_0, 4: tcon[9],
//        5: test4b_out0 , 6:test4b_out1)

// GPIO_97_CPU_BL3D3V_EN( BACKLIGHT 3.3V ENABLE)
#define _PIN_97                                 (1 & 0x0F) // Page 10-0x12[2:0]
// 0 ~ 6 (0: P4D2i<I>, 1: P4D2o<PP>, 2: P4D2o<OD>, 3: a_adc3_0, 4: tcon[10],
//        5: test4b_out2 , 6:test4b_out3)

// NC
#define _PIN_109_OFF_REGION                     (1 & 0x0F) // Page 10-0x13[2:0]
// 0 ~ 5 (0: P4D3i<I>, 1: P4D3o<PP>, 2: P4D3o<OD>, 3: audio_houtl, 4: sd2, 5: spdif2)

// NC
#define _PIN_110_OFF_REGION                     (1 & 0x0F) // Page 10-0x14[2:0]
// 0 ~ 5 (0: P4D4i<I>, 1: P4D4o<PP>, 2: P4D4o<OD>, 3: audio_houtr, 4: sd3, 5: spdif3)

// NC
#define _PIN_113_OFF_REGION                     (1 & 0x0F) // Page 10-0x15[2:0]
// 0 ~ 4 (0: P4D5i<I>, 1: P4D5o<PP>, 2: P4D5o<OD>, 3: line_inl, 4: ws)

// NC
#define _PIN_114_OFF_REGION                     (1 & 0x0F) // Page 10-0x16[2:0]
// 0 ~ 4 (0: P4D6i<I>, 1: P4D6o<PP>, 2: P4D6o<OD>, 3: line_inr, 4: sck)

// AUDIO_REF
#define _PIN_115_OFF_REGION                     (3 & 0x0F) // Page 10-0x17[2:0]
// 0 ~ 4 (0: P4D7i<I>, 1: P4D7o<PP>, 2: P4D7o<OD>, 3: audio_ref, 4: mck)

// ANA_AUDOUT_AMP_L
#define _PIN_116_OFF_REGION                     (3 & 0x0F) // Page 10-0x18[2:0]
// 0 ~ 5 (0: P5D0i<I>, 1: P5D0o<PP>, 2: P5D0o<OD>, 3: audio_soutl, 4: sd0, 5: spdif0)

// ANA_AUDOUT_AMP_R
#define _PIN_117_OFF_REGION                     (3 & 0x0F) // Page 10-0x19[2:0]
// 0 ~ 5 (0: P5D1i<I>, 1: P5D1o<PP>, 2: P5D1o<OD>, 3: audio_soutr, 4: sd1, 5: spdif1)

// NC
#define _PIN_143_OFF_REGION                     (1 & 0x0F) // Page 10-0x1A[2:0]
// 0 ~ 3 (0: P5D2i<I>, 1: P5D2o<PP>, 2: P5D2o<OD>, 3: dptx_aux_ch_p_2

// NC
#define _PIN_144_OFF_REGION                     (1 & 0x0F) // Page 10-0x1B[2:0]
// 0 ~ 3 (0: P5D3i<I>, 1: P5D3o<PP>, 2: P5D3o<OD>, 3: dptx_aux_ch_n_2

// NC
#define _PIN_145_OFF_REGION                     (1 & 0x0F) // Page 10-0x1C[2:0]
// 0 ~ 4 (0: P5D4i<I>, 1: P5D4o<PP>, 2: P5D4o<OD>, 3: dptx_hpd2_org, 4: vb1_lock_n,

// eDP_AUX_CPU_P
#define _PIN_146_OFF_REGION                     (3 & 0x0F) // Page 10-0x1D[2:0]
// 0 ~ 3 (0: P5D5i<I>, 1: P5D5o<PP>, 2: P5D5o<OD>, 3: dptx_aux_ch_p_1

// eDP_AUX_CPU_N
#define _PIN_147_OFF_REGION                     (3 & 0x0F) // Page 10-0x1E[2:0]
// 0 ~ 3 (0: P5D6i<I>, 1: P5D6o<PP>,  2: P5D6o<OD>, 3: dptx_aux_ch_n_1)

// eDP_HPD_CPU
#define _PIN_148_OFF_REGION                     (3 & 0x0F) // Page 10-0x1F[2:0]
// 0 ~ 4 (0: P5D7i<I>, 1: P5D7o<PP>, 2: P5D7o<OD>, 3: dptx_hpd1_org,
//        4: vb1_htpd_n)

// NC
#define _PIN_149_OFF_REGION                     (1 & 0x0F) // Page 10-0x20[2:0]
// 0 ~ 8 (0: P6D0i<I>, 1: P6D0o<PP>, 2: P6D0o<OD>, 3: tcon[2], 8: iicscl1

// NC
#define _PIN_150_OFF_REGION                     (1 & 0x0F) // Page 10-0x21[2:0]
// 0 ~ 8 (0: P6D1i<I>, 1: P6D1o<PP>, 2: P6D1o<OD>, 3: pwm1<PP>, 4: pwm1<OD>,
//        8: iicsda1)

// NC
#define _PIN_151_OFF_REGION                     (1 & 0x0F) // Page 10-0x22[2:0]
// 0 ~ 5 (0: P6D2i<I>, 1: P6D2o<PP>, 2: P6D2o<OD>, 3: pwm2<PP>, 4: pwm2<OD>,
//        5: tcon[3])

// LOCAL_DIMMING_VSYNC
#define _PIN_152_OFF_REGION                     (3 & 0x0F) // Page 10-0x23[2:0]
// 0 ~ 7 (0: P6D3i<I>, 1: P6D3o<PP>, 2: P6D3o<OD>, 3: pwm5<PP>, 4: pwm5<OD>,
//        5: tcon[2],  6:test4b_out0, 7: test4b_out1)

// LOCAL_DIMMING_SPI_CLK
#define _PIN_153_OFF_REGION                     (8 & 0x0F) // Page 10-0x24[2:0]
// 0 ~ 8 (0: P6D4i<I>, 1: P6D4o<PP>, 2: P6D4o<OD>, 3: t0, 8: usb_spi_clk)

// LOCAL_DIMMING_SPI_SI
#define _PIN_154_OFF_REGION                     (8 & 0x0F) // Page 10-0x25[2:0]
// 0 ~ 8 (0: P6D5i<I>, 1: P6D5o<PP>, 2: P6D5o<OD>, 3: int0, 4: t1, 8: usb_spi_si)

// LOCAL_DIMMING_SPI_SO
#define _PIN_155_OFF_REGION                     (8 & 0x0F) // Page 10-0x26[2:0]
// 0 ~ 8 (0: P6D6i<I>, 1: P6D6o<PP>, 2: P6D6o<OD>, 3: int1, 4: t2, 8: usb_spi_so)

// LOCAL_DIMMING_SPI_CE
#define _PIN_156_OFF_REGION                     (8 & 0x0F) // Page 10-0x27[2:0]
// 0 ~ 8 (0: P6D7i<I>, 1: P6D7o<PP>, 2: P6D7o<OD>, 3: irqb, 4: ttl_dvs,
//        8: usb_spi_ceb0)

// NC
#define _PIN_157_OFF_REGION                     (8 & 0x0F) // Page 10-0x28[2:0]
// 0 ~ 8 (0: P7D0i<I>, 1: P7D0o<PP>, 2: P7D0o<OD>, 3: t2ex, 8: usb_spi_ceb1)

// GPIO_158_CPU_PANELVCC_EN
#define _PIN_158_OFF_REGION                     (1 & 0x0F) // Page 10-0x29[2:0]
// 0 ~ 6 (0: P7D1i<I>, 1: P7D1o<PP>, 2: P7D1o<OD>, 3:ws, 4: tcon[12], 5:test4b_out0
//        6: test4b_out1)

// NC
#define _PIN_159_OFF_REGION                     (1 & 0x0F) // Page 10-0x2A[2:0]
// 0 ~ 6 (0: P7D2i<I>, 1: P7D2o<PP>, 2: P7D2o<OD>, 3: sck, 4: tcon[13],
//        5: test4b_out2, 6: test4b_out3)

// NC
#define _PIN_160_OFF_REGION                     (1 & 0x0F) // Page 10-0x2B[2:0]
// 0 ~ 7 (0: P7D3i<I>, 1: P7D3o<PP>, 2: P7D3o<OD>, 3: mck, 4: test4b_out0,
//        5: test4b_out1, 6:test4b_out2, 7:test4b_out3)

// NC
#define _PIN_161_OFF_REGION                     (1 & 0x0F) // Page 10-0x2C[2:0]
// 0 ~ 6 (0: P7D4i<I>, 1: P7D4o<PP>, 2: P7D4o<OD>, 3: pwm0<PP>, 4: pwm0<OD>,
//        5: spdif0, 6: sd0)

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

// 1D1V_OFF_EN_CPU VCCK_OFF_EN
#define _PIN_179                                (2 & 0x0F) // Page 10-0x31[2:0]
// 0 ~ 7 (0: P8D1i<I>, 1: P8D1o<PP>, 2: P8D1o<OD>, 3: ttl_dhs, 4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7:test4b_out3)

// GPIO_180_CPU_USB_EN
#define _PIN_180                                (1 & 0x0F) // Page 10-0x32[2:0]
// 0 ~ 7 (0: P8D2i<I>, 1: P8D2o<PP>, 2: P8D2o<OD>, 3: ttl_den, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// DDC_WPn_CPU
#define _PIN_181                                (1 & 0x0F) // Page 10-0x33[2:0]
// 0 ~ 7 (0: P8D3i<I>, 1: P8D3o<PP>, 2: P8D3o<OD>, 3: dclk, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// GPIO_184_CPU_LED_WHITE
#define _PIN_184                                (3 & 0x0F) // Page 10-0x34[2:0]
// 0 ~ 6 (0: P8D4i<I>, 1: P8D4o<PP>, 2: P8D4o<OD>, 3: pwm0<PP>, 4: pwm0<OD>,
//        5: tcon[11], 6: clko)

// GPIO_185_CPU_BLEN
#define _PIN_185                                (1 & 0x0F) // Page 10-0x35[2:0]
// 0 ~ 6 (0: P8D5i<I>, 1: P8D5o<PP>, 2: P8D5o<OD>, 3: pwm1<PP>, 4: pwm1<OD>,
//        5: tcon[7], 6: m1_idomain_den_out)

// SPI_WP_CPU
#define _PIN_190                                (1 & 0x0F) // Page 10-0x36[2:0]
// 0 ~ 2 (0: P8D6i<I>, 1: P8D6o<PP>, 2: P8D6o<OD>)

// GPIO_193_CPU_BLVCC_EN (BACKLIGHT 19V ENABLE)
#define _PIN_193                                (1 & 0x0F) // Page 10-0x37[2:0]
// 0 ~ 7 (0: P8D7i<I>, 1: P8D7o<PP>, 2: P8D7o<OD>, 3: Reserved,
//        4: Test4b_out0, 5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// GPIO_194_CPU_PD_EN
#define _PIN_194                                (1 & 0x0F) // Page 10-0x38[2:0]
// 0 ~ 6 (0: P9D0i<I>, 1: P9D0o<PP>, 2: P9D0o<OD>, 3: pwm2<PP>, 4: pwm2<PP>,
//        5: tcon[6], 6: irda_in)

// NC
#define _PIN_195                                (1 & 0x0F) // Page 10-0x39[2:0]
// 0 ~ 6 (0: P9D1i<I>, 1: P9D1o<PP>, 2: P9D1o<OD>, 3: PWM4<PP>, 4: PWM4<OD>
//        5: tcon[7], 6: pwm_out)

// NC
#define _PIN_196                                (1 & 0x0F) // Page 10-0x3A[2:0]
// 0 ~ 7 (0: P9D2i<I>, 1: P9D2o<PP>, 2: P9D2o<OD>, 3: tcon[5], 4: test4b_out0
//        5: test4b_out1, 6:test4b_out2, 7:test4b_out3)

// NC
#define _PIN_197                                (1 & 0x0F) // Page 10-0x3B[2:0]
// 0 ~ 7 (0: P9D3i<I>, 1: P9D3o<PP>, 2: P9D3o<OD>, 3: tcon[4], 4: test4b_out0
//        5: test4b_out1, 6:test4b_out2, 7:test4b_out3)

// HDMI1_EDID_HDR_E2
#define _PIN_198                                (1 & 0x0F) // Page 10-0x3C[2:0]
// 0 ~ 7 (0: P9D4i<I>, 1: P9D4o<PP>, 2: P9D4o<OD>, 3: m1_idomain_hs_out, 4: test4b_out0
//        5: test4b_out1, 6:test4b_out2, 7:test4b_out3)

// GPIO_199_CPU_MUTEN
#define _PIN_199                                (2 & 0x0F) // Page 10-0x3D[2:0]
// 0 ~ 5 (0: P9D5i<I>, 1: P9D5o<PP>, 2: P9D5o<OD>, 3: pwm5<PP>, 4: pwm5<OD>,
//        5: pwm_in)

// 1D8V_EN_CPU DDR_PW_EN
#define _PIN_200                                (2 & 0x0F) // Page 10-0x3E[2:0]
// 0 ~ 8 (0: P9D6i<I>, 1: P9D6o<PP>, 2: P9D6o<OD>, 3: pwm4<PP>, 4: pwm4<OD>
//        5: tcon[11], 8: iicscl2)

// CDP_AUTO
#define _PIN_201                                (2 & 0x0F) // Page 10-0x3F[2:0]
// 0 ~ 8 (0: P9D7i<I>, 1: P9D7o<PP>, 2: P9D7o<OD>, 3: pwm3<PP>, 4: pwm3<OD>
//        5: tcon[0], 8: iicsda2)

// BC_CHAR_EN
#define _PIN_202                                (2 & 0x0F) // Page 10-0x40[2:0]
// 0 ~ 8 (0: PAD0i<I>, 1: PAD0o<PP>, 2: PAD0o<OD>, 3: int0, 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3, 8: txd)

// PSID_DET
#define _PIN_203                                (2 & 0x0F) // Page 10-0x41[2:0]
// 0 ~ 8 (0: PAD1i<I>, 1: PAD1o<PP>, 2: PAD1o<OD>, 3: int1, 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3, 8: rxd)

// HDMI1_DET_CPU
#define _PIN_204                                (0 & 0x0F) // Page 10-0x42[2:0]
// 0 ~ 7 (0: PAD2i<I>, 1: PAD2o<PP>, 2: PAD2o<OD>, 3: tcon[13], 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3)

// 3D3V_USB_EN
#define _PIN_206                                (2 & 0x0F) // Page 10-0x43[2:0]
// 0 ~ 7 (0: PAD3i<I>, 1: PAD3o<PP>, 2: PAD3o<OD>, 3: tcon[12], 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3)

// TYPE_C_IRQ1
#define _PIN_207                                (0 & 0x0F) // Page 10-0x44[2:0]
// 0 ~ 7 (0: PAD4i<I>, 1: PAD4o<PP>, 2: PAD4o<OD>, 3: tcon[10], 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3)

// GPIO_208_CPU_AUDIO_DET
#define _PIN_208                                (0 & 0x0F) // Page 10-0x45[2:0]
// 0 ~ 7 (0: PAD5i<I>, 1: PAD5o<PP>, 2: PAD5o<OD>, 3: tcon[9], 4: test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7:test4b_out3)

// EEPROM_WPn_CPU
#define _PIN_209                                (2 & 0x0F) // Page 10-0x46[2:0]
// 0 ~ 2 (0: PAD6i<I>, 1: PAD6o<PP>, 2: PAD6o<OD>)

// EEPROM_SCL_CPU
#define _PIN_210                                (8 & 0x0F) // Page 10-0x47[2:0]
// 0 ~ 8 (0: PAD7i<I>, 1: PAD7o<PP>, 2: PAD7o<OD>, 8: eeiicscl)

// EEPROM_SDA_CPU
#define _PIN_211                                (8 & 0x0F) // Page 10-0x48[2:0]
// 0 ~ 8 (0: PBD0i<I>, 1: PBD0o<PP>, 2: PBD0o<OD>, 8: eeiicsda)

// I2C_DEBUG_SCL
#define _PIN_212                                (8 & 0x0F) // Page 10-0x49[2:0]
// 0 ~ 8 (0: PBD1i<I>, 1: Reserved, 2: PBD1o<OD>, 8: ddcscl2)

// I2C_DEBUG_SDA
#define _PIN_213                                (8 & 0x0F) // Page 10-0x4A[2:0]
// 0 ~ 8 (0: PBD2i<I>, 1: Reserved, 2: PBD2o<OD>, 8: ddcsda2)

// HDMI1_SCL_CPU
#define _PIN_214                                (8 & 0x0F) // Page 10-0x4B[2:0]
// 0 ~ 8 (0: PBD3i<I>, 1: Reserved, 2: PBD3o<OD>, 8: ddcscl3)

// HDMI1_SDA_CPU
#define _PIN_215                                (8 & 0x0F) // Page 10-0x4C[2:0]
// 0 ~ 8 (0: PBD4i<I>, 1: Reserved, 2: PBD4o<OD>, 8: ddcsda3 )
