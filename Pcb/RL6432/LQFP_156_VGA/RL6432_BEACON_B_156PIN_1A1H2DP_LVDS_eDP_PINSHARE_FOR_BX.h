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
// ID Code      : RL6432_QA_B_156PIN_1A1MHL2DP_LVDS_eDP_PINSHARE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


/////////////////////////////
// RL6432 Series Pin Share //
/////////////////////////////

//--------------------------------------------------
//  RL6432 156 Pin Share
//--------------------------------------------------
// HDMI_CABLE_DETECT_3
#define _156PIN_PIN_82                          (0 & 0x0F) // Page 10-0x00[2:0]
// 0 ~ 6 (0: P1D0i<I>,    1: P1D0o<PP>,   2: P1D0o<OD>, 3: test4b_out0,
//        4: test4b_out1, 5: test4b_out2, 6: test4b_out3)

// CBUS/HDMI_HPD_3
#define _156PIN_PIN_84                          (1 & 0x0F) // Page 10-0x01[2:0]
// 0 ~ 2 (0: P1D1i<I>, 1: P1D1o<PP>, 2: P1D1o<OD> & d3_hdmi_hpd_int<I>)

// DP_CABLE_DET_0
#define _156PIN_PIN_118                         (0 & 0x0F) // Page 10-0x03[2:0]
// 0 ~ 7 (0: P1D3i<I>,    1: P1D3o<PP>,   2: P1D3o<OD>, 3: tcon[0], 4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

// DP_CABLE_DET_1
#define _156PIN_PIN_119                         (0 & 0x0F) // Page 10-0x04[2:0]
// 0 ~ 7 (0: P1D4i<I>,    1: P1D4o<PP>,   2: P1D4o<OD>, 3: tcon[8],  4: test4b_out0,
//        5: test4b_out1, 6: test4b_out2, 7: test4b_out3)

// DDCSCL_VGA
#define _156PIN_PIN_131                         (8 & 0x0F) // Page 10-0x05[2:0]
// 0 ~ 8 (0: P1D5i<I>, 1: P1D5o<PP>, 2: P1D5o<OD>, 8: DDCSCLVGA)

// DDCSDA_VGA
#define _156PIN_PIN_132                         (8 & 0x0F) // Page 10-0x06[2:0]
// 0 ~ 8 (0: P1D6i<I>, 1: P1D6o<PP>, 2: P1D6o<OD>, 8: DDCSDAVGA)

// VGA_CABLE_DET
#define _156PIN_PIN_133                         (0 & 0x0F) // Page 10-0x07[2:0]
// 0 ~ 2 (0: P1D7i<I>, 1: P1D7o<PP>,   2: P1D7o<OD>, 3: pwm0 <PP>,  4: pwm0 <OD>,
//        5: tcon[4],  6: test4b_out2, 7: test4b_out3)

// AUX_CHP_0
#define _156PIN_PIN_135                         (3 & 0x0F) // Page 10-0x08[2:0]
// 0 ~ 3 (0: P3D0i<I>, 1: Reserved, 2: P3D0o<OD>, 3: AUXp0)

// AUX_CHN_0
#define _156PIN_PIN_136                         (3 & 0x0F) // Page 10-0x09[2:0]
// 0 ~ 3 (0: P3D1i<I>, 1: Reserved, 2: P3D1o<OD>, 3: AUXn0)

// AUX_CHP_1
#define _156PIN_PIN_137                         (3 & 0x0F) // Page 10-0x0A[2:0]
// 0 ~ 8 (0: P3D2i<I>, 1: Reserved, 2: P3D2o<OD>, 3: AUXp1, 8:DDCSCL1)

// AUX_CHN_1
#define _156PIN_PIN_138                         (3 & 0x0F) // Page 10-0x0B[2:0]
// 0 ~ 8 (0: P3D3i<I>, 1: Reserved, 2: P3D3o<OD>, 3: AUXn1, 8: DDSSDA1)

// ADC_KEY1
#define _156PIN_PIN_143                         (3 & 0x0F) // Page 10-0x0C[2:0]
// 0 ~ 6 (0: P3D4i<I>,     1: P3D4o<PP>, 2: P3D4o<OD>, 3: a_adc0_0, 4: int0,
//        5: test4b_out0 , 6:test4b_out1)

// ADC_KEY2
#define _156PIN_PIN_144                         (3 & 0x0F) // Page 10-0x0D[2:0]
// 0 ~ 6 (0: P3D5i<I>,     1: P3D5o<PP>, 2: P3D5o<OD>, 3: a_adc1_0, 4: int1,
//        5: test4b_out2 , 6:test4b_out3)

// NC(AUDIO_HOUTL)
#define _156PIN_PIN_147                         (1 & 0x0F) // Page 10-0x12[2:0]
// 0 ~ 5 (0: P4D2i<I>, 1: P4D2o<PP>, 2: P4D2o<OD>, 3: Audio_houtl, 4: sd2, 5: spdif2)

// NC(AUDIO_HOUTR)
#define _156PIN_PIN_148                         (1 & 0x0F) // Page 10-0x13[2:0]
// 0 ~ 5 (0: P4D3i<I>, 1: P4D3o<PP>, 2: P4D3o<OD>, 3: Audio_houtr, 4: sd3, 5: spdif3)

// LED1
#define _156PIN_PIN_151                         (2 & 0x0F) // Page 10-0x14[2:0]
// 0 ~ 4 (0: P4D4i<I>, 1: P4D4o<PP>, 2: P4D4o<OD>, 3: line_inl, 4: ws)

// LED2
#define _156PIN_PIN_152                         (2 & 0x0F) // Page 10-0x15[2:0]
// 0 ~ 4 (0: P4D5i<I>, 1: P4D5o<PP>, 2: P4D5o<OD>, 3: line_inr, 4: sck)

// NC(AUDIO_REF)
#define _156PIN_PIN_153                         (1 & 0x0F) // Page 10-0x16[2:0]
// 0 ~ 4 (0: P4D6i<I>, 1: P4D6o<PP>, 2: P4D6o<OD>, 3: Audio_ref, 4: mck)

// LED4
#define _156PIN_PIN_154                         (1 & 0x0F) // Page 10-0x17[2:0]
// 0 ~ 5 (0: P4D7i<I>, 1: P4D7o<PP>, 2: P4D7o<OD>, 3: Audio_soutl, 4: sd0,
//        5: spdif0)

// LED5
#define _156PIN_PIN_155                         (1 & 0x0F) // Page 10-0x18[2:0]
// 0 ~ 5 (0: P5D0i<I>, 1: P5D0o<PP>, 2: P5D0o<OD>, 3: Audio_soutr, 4: sd1,
//        5: spdif1)

// DPTX_AUX_P_2
// CFG2 (CUSTOMER PCB BX)
#define _156PIN_PIN_51_OFF_REGION               (1 & 0x0F) // Page 10-0x19[2:0]
// 0 ~ 6 (0: P5D1i<I>, 1: P5D1o<PP>, 2: P5D1o<OD>, 3: PWM3<PP>, 4: PWM3<OD>,
//        5: tcon[6],  6: DPTX_aux_ch_p_1)

// BACKLIGHT_12V_ONOFF
#define _156PIN_PIN_52_OFF_REGION               (1 & 0x0F) // Page 10-0x1A[2:0]
// 0 ~ 6 (0: P5D2i<I>, 1: P5D2o<PP>, 2: P5D2o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[7],  6: DPTX_aux_ch_n_1)

//TX2_HPD_2
//CFG1 (CUSTOMER PCB BX)
#define _156PIN_PIN_50_OFF_REGION               (1 & 0x0F) // Page 10-0x1B[2:0]
// 0 ~ 4 (0: P5D3i<I>, 1: P5D3o<PP>, 2: P5D3o<OD>, 3: DPTX_hpd1_org, 4:  tcon[8])

// Panel_ON
#define _156PIN_PIN_47_OFF_REGION               (1 & 0x0F) // Page 10-0x22[2:0]
// 0 ~ 8  (0: P6D2i<I>, 1: P6D2o<PP>, 2: P6D2o<OD>, 3: int1, 4: t2, 5: DCLK,
//         8: usb_spi_so)

// GPU_SEL
#define _156PIN_PIN_48_OFF_REGION               (2 & 0x0F) // Page 10-0x23[2:0]
// 0 ~ 8  (0: P6D3i<I>, 1: P6D3o<PP>, 2: P6D3o<OD>, 3: IRQB, 4: DVS,
//         8: usb_spi_ceb0)

//onBACKLITE
// EN_D(Beacon) 
#define _156PIN_PIN_49_OFF_REGION               (1 & 0x0F) // Page 10-0x24[2:0]
// 0 ~ 8 (0: P6D4i<I>, 1: P6D4o<PP>, 2: P6D4o<OD>, 3: T2ex, 4: DHS,
//        8: usb_spi_ceb1)

// ADJBACKLITE
#define _156PIN_PIN_54_OFF_REGION               (3 & 0x0F) // Page 10-0x25[2:0]
// 0 ~ 7 (0: P6D5i<I>, 1: P6D5o<PP>,   2: P6D5o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[2],  6: test4b_out0, 7: test4b_out1)

// FLASH_WP
#define _156PIN_PIN_61                          (1 & 0x0F) // Page 10-0x29[2:0]
// 0 ~ 2 (0: P7D1i<I>, 1: P7D1o<PP>, 2: P7D1o<OD>)

// VBUS_EN_3
// Panel Power(Beacon) 
#define _156PIN_PIN_63                          (1 & 0x0F) // Page 10-0x2A[2:0]
// 0 ~ 6 (0: P7D2i<I>, 1: P7D2o<PP>, 2: P7D2o<OD>, 3: PWM2<PP>, 4: PWM2<OD>,
//        5: TCON[1],  6: IRDA_in )

// HDMI_MHL_SEL_3
// BackLight En(Beacon) 
#define _156PIN_PIN_64                          (2 & 0x0F) // Page 10-0x2C[2:0]
// 0 ~ 7 (0: P7D4i<I>, 1: P7D4o<PP>, 2: P7D4o<OD>, 3: tcon[5], 4: pwm_out,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// MHL_DETECT_3
#define _156PIN_PIN_65                          (0 & 0x0F) // Page 10-0x2D[2:0]
// 0 ~ 7 (0: P7D5i<I>,    1: P7D5o<PP>,   2: P7D5o<OD>, 3: tcon[4], 4: pwm_in,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// NC (DDR_PW_EN)
#define _156PIN_PIN_66                          (0 & 0x0F) // Page 10-0x2F[2:0]
// 0 ~ 5 (0: P7D7i<I>, 1: P7D7o<PP>, 2: P7D7o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[11])

// VCCK_OFF_EN
#define _156PIN_PIN_67                          (1 & 0x0F) // Page 10-0x30[2:0]
// 0 ~ 8 (0: P8D0i<I>, 1: P8D0o<PP>, 2: P8D0o<OD>, 3: PWM4<PP>, 4: PWM4<OD>,
//        5: TCON[11], 8: IICSCL2)

// EDID_WP
#define _156PIN_PIN_68                          (1 & 0x0F) // Page 10-0x31[2:0]
// 0 ~ 8 (0: P8D1i<I>, 1: P8D1o<PP>, 2: P8D1o<OD>, 3: PWM3<PP>, 4: PWM3<OD>,
//        5: TCON[0],  8: IICSDA2)

// DP_SINK_ASS_P1
#define _156PIN_PIN_70                          (0 & 0x0F) // Page 10-0x32[2:0]
// 0 ~ 8 (0: P8D2i<I>,    1: P8D2o<PP>,   2: P8D2o<OD>,   3: int0, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3, 8: TXD)

// DP_HOT_PLUG_1
#define _156PIN_PIN_69                          (1 & 0x0F) // Page 10-0x33[2:0]
// 0 ~ 8 (0: P8D3i<I>,    1: P8D3o<PP>,   2: P8D3o<OD>,   3: int1, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3, 8: RXD)

// DP_SINK_ASS_N1
#define _156PIN_PIN_71                          (0 & 0x0F) // Page 10-0x34[2:0]
// 0 ~ 7 (0: P8D4i<I>,    1: P8D4o<PP>,   2: P8D4o<OD>, 3: tcon[13], 4: sd0,
//        5: spdif0, 6: Test4b_out2, 7: Test4b_out3)

// DDC_DET
#define _156PIN_PIN_72                          (0 & 0x0F) // Page 10-0x35[2:0]
// 0 ~ 7 (0: P8D5i<I>,    1: P8D5o<PP>,   2: P8D5o<OD>, 3: tcon[12], 4: mck,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// LED_2(Beacon)  
#define _156PIN_PIN_73                          (1 & 0x0F) // Page 10-0x36[2:0]
// 0 ~ 7 (0: P8D6i<I>,    1: P8D6o<PP>,   2: P8D6o<OD>, 3:  tcon[10], 4: sck,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// LED_1(Beacon) 
#define _156PIN_PIN_74                          (1 & 0x0F) // Page 10-0x37[2:0]
// 0 ~ 7 (0: P8D7i<I>,    1: P8D7o<PP>,   2: P8D7o<OD>, 3: tcon[9] , 4: ws,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// EEPROM_WP
#define _156PIN_PIN_76                          (1 & 0x0F) // Page 10-0x39[2:0]
// 0 ~ 5 (0: P9D1i<I>, 1: P9D1o<PP>, 2: P9D1o<OD>, 3: PWM2<PP>, 4: PWM2<OD>
//        5: TCON[3])

// EESCL
#define _156PIN_PIN_77                          (2 & 0x0F) // Page 10-0x3A[2:0]
// 0 ~ 8 (0: P9D2i<I>, 1: P9D2o<PP>, 2: P9D2o<OD>, 3: PWM0<PP>, 4: PWM0<OD>
//        5: TCON[1],  8: EEIICSCL)

// EESDA
#define _156PIN_PIN_78                          (2 & 0x0F) // Page 10-0x3B[2:0]
// 0 ~ 8 (0: P9D3i<I>, 1: P9D3o<PP>, 2: P9D3o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[2],  8:EEIICSDA)

// DDCSCL_3
#define _156PIN_PIN_79                          (8 & 0x0F) // Page 10-0x3E[2:0]
// 0 ~ 8 (0: P9D6i<I>, 1: Reserved, 2: P9D6o<OD>, 8: DDCSCL3)

// DDCSDA_3
#define _156PIN_PIN_80                          (8 & 0x0F) // Page 10-0x3F[2:0]
// 0 ~ 8 (0: P9D7i<I>, 1: Reserved, 2: P9D7o<OD>, 8: DDCSDA3)

// DP5V_ON
#define _156PIN_PIN_81                          (0 & 0x0F) // Page 10-0x40[2:0]
// 0 ~ 6 (0: PAD0i<I>,    1: PAD0o<PP>, 2: PAD0o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// TXB3P
#define _156PIN_PIN_26_OFF_REGION               (4 & 0x0F) // Page 10-0x47[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD3i<I>, 2: PAD3o<PP>, 3: PAD3o<OD>, 4: TXB3+_10b)

// TXB3N
#define _156PIN_PIN_27_OFF_REGION               (4 & 0x0F) // Page 10-0x48[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD4i<I>, 2: PAD4o<PP>, 3: PAD4o<OD>, 4: TXB3-_10b)

// TXB2P
#define _156PIN_PIN_28_OFF_REGION               (4 & 0x0F) // Page 10-0x49[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD5i<I>, 2: PAD5o<PP>, 3: PAD5o<OD>, 4: TXB2+_10b)

// TXB2N
#define _156PIN_PIN_29_OFF_REGION               (4 & 0x0F) // Page 10-0x4A[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD6i<I>, 2: PAD6o<PP>, 3: PAD6o<OD>, 4: TXB2-_10b)

// TXB1P
#define _156PIN_PIN_30_OFF_REGION               (4 & 0x0F) // Page 10-0x4B[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PAD7i<I>, 2: PAD7o<PP>, 3: PAD7o<OD>, 4: TXB1+_10b)

// TXB1N
#define _156PIN_PIN_31_OFF_REGION               (4 & 0x0F) // Page 10-0x4C[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD0i<I>, 2: PBD0o<PP>, 3: PBD0o<OD>, 4: TXB1-_10b)

// TXB0P
#define _156PIN_PIN_32_OFF_REGION               (4 & 0x0F) // Page 10-0x4D[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD1i<I>, 2: PBD1o<PP>, 3: PBD1o<OD>, 4: TXB0+_10b)

// TXB0N
#define _156PIN_PIN_33_OFF_REGION               (4 & 0x0F) // Page 10-0x4E[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD2i<I>, 2: PBD2o<PP>, 3: PBD2o<OD>, 4: TXB0-_10b)

// TXA3P
#define _156PIN_PIN_35_OFF_REGION               (4 & 0x0F) // Page 10-0x51[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD5i<I>, 2: PBD5o<PP>, 3: PBD5o<OD>, 4: TXA3+_10b)

// TXA3N
#define _156PIN_PIN_36_OFF_REGION               (4 & 0x0F) // Page 10-0x52[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD6i<I>, 2: PBD6o<PP>, 3: PBD6o<OD>, 4: TXA3-_10b)

// TXACP
#define _156PIN_PIN_37_OFF_REGION               (4 & 0x0F) // Page 10-0x53[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PBD7i<I>, 2: PBD7o<PP>, 3: PBD7o<OD>, 4: TXAC+_10b)

// TXACN
#define _156PIN_PIN_38_OFF_REGION               (4 & 0x0F) // Page 10-0x54[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD0i<I>, 2: PCD0o<PP>, 3: PCD0o<OD>, 4: TXAC-_10b)

// TXA2P
#define _156PIN_PIN_39_OFF_REGION               (4 & 0x0F) // Page 10-0x55[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD1i<I>, 2: PCD1o<PP>, 3: PCD1o<OD>, 4: TXA2+_10b)

// TXA2N
#define _156PIN_PIN_40_OFF_REGION               (4 & 0x0F) // Page 10-0x56[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD2i<I>, 2: PCD2o<PP>, 3: PCD2o<OD>, 4: TXA2-_10b)

// TXA1P
#define _156PIN_PIN_41_OFF_REGION               (1 & 0x0F) // Page 10-0x57[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD3i<I>, 2: PCD3o<PP>, 3: PCD3o<OD>, 4: TXA1+_10b)

// TXA1N
#define _156PIN_PIN_42_OFF_REGION               (1 & 0x0F) // Page 10-0x58[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD4i<I>, 2: PCD4o<PP>, 3: PCD4o<OD>, 4: TXA1-_10b)

// TXA0P
#define _156PIN_PIN_43_OFF_REGION               (1 & 0x0F) // Page 10-0x59[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD5i<I>, 2: PCD5o<PP>, 3: PCD5o<OD>, 4: TXA0+_10b)

// TXA0N
#define _156PIN_PIN_44_OFF_REGION               (1 & 0x0F) // Page 10-5A[2:0]
// 0 ~ 5 (0: Hi-Z, 1: PCD6i<I>, 2: PCD6o<PP>, 3: PCD6o<OD>, 4: TXA0-_10b)

