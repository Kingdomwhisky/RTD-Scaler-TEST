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
// ID Code      : RL6410_DEMO_B_1A4MHL1DP1mDP_DPTX_LVDS_eDP_PINSHARE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


/////////////////////////////
// RL6410 Series Pin Share //
/////////////////////////////

//--------------------------------------------------
//  RL6410 BGA Pin Share
//--------------------------------------------------
// AUX_CHP_1
#define _PIN_Y6                                 (3 & 0x07) // Page 10-0x00[2:0]
// 0 ~ 4 (0: P1D0i<I>, 1: reserved, 2: P1D0o<OD>, 3: AUX_P1)

// AUX_CHN_1
#define _PIN_Y5                                 (3 & 0x07) // Page 10-0x01[2:0]
// 0 ~ 4 (0: P1D1i<I>, 1: reserved, 2: P1D1o<OD>, 3: AUX_N1)

// AUX_CHP_0
#define _PIN_AA6                                (3 & 0x07) // Page 10-0x02[2:0]
// 0 ~ 4 (0: P1D2i<I>, 1: reserved, 2: P1D2o<OD>, 3: AUX_P0)

// AUX_CHN_0
#define _PIN_AA5                                (3 & 0x07) // Page 10-0x03[2:0]
// 0 ~ 4 (0: P1D3i<I>, 1: reserved, 2: P1D3o<OD>, 3: AUX_N0)

// CBUS/HDMI_HPD_2
#define _PIN_L4                                 (2 & 0x07) // Page 10-0x04[2:0]
// 0 ~ 2 (0: P1D4i<I>, 1: P1D4o<PP>, 2: P1D4o<OD>)

// MHL_DETECT_2
#define _PIN_W6                                 (0 & 0x07) // Page 10-0x05[2:0]
// 0 ~ 2 (0: P1D5i<I>, 1: P1D5o<PP>, 2: P1D5o<OD>)

// CBUS/HDMI_HPD_3
#define _PIN_F4                                 (2 & 0x07) // Page 10-0x06[2:0]
// 0 ~ 2 (0: P1D6i<I>, 1: P1D6o<PP>, 2: P1D6o<OD>)

// MHL_DETECT_3
#define _PIN_W5                                 (0 & 0x07) // Page 10-0x07[2:0]
// 0 ~ 2 (0: P1D7i<I>, 1: P1D7o<PP>, 2: P1D7o<OD>)

// NC
#define _PIN_AJ3                                (1 & 0x07) // Page 10-0x08[2:0]
// 0 ~ 6 (0: P3D0i<I>, 1: P3D0o<PP>, 2: P3D0o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// NC
#define _PIN_AJ1                                (1 & 0x07) // Page 10-0x09[2:0]
// 0 ~ 6 (0: P3D1i<I>, 1: P3D1o<PP>, 2: P3D1o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// NC
#define _PIN_AJ2                                (1 & 0x07) // Page 10-0x0A[2:0]
// 0 ~ 6 (0: P3D2i<I>, 1: P3D2o<PP>, 2: P3D2o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// NC
#define _PIN_AK3                                (1 & 0x07) // Page 10-0x0B[2:0]
// 0 ~ 6 (0: P3D3i<I>, 1: P3D3o<PP>, 2: P3D3o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// NC
#define _PIN_AK2                                (1 & 0x07) // Page 10-0x0C[2:0]
// 0 ~ 6 (0: P3D4i<I>, 1: P3D4o<PP>, 2: P3D4o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// NC
#define _PIN_AL3                                (1 & 0x07) // Page 10-0x0D[2:0]
// 0 ~ 6 (0: P3D5i<I>, 1: P3D5o<PP>, 2: P3D5o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// NC
#define _PIN_AL2                                (1 & 0x07) // Page 10-0x0E[2:0]
// 0 ~ 6 (0: P3D6i<I>, 1: P3D6o<PP>, 2: P3D6o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// DP5V_ON
#define _PIN_AL1                                (0 & 0x07) // Page 10-0x0F[2:0]
// 0 ~ 6 (0: P3D7i<I>, 1: P3D7o<PP>, 2: P3D7o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// NC
#define _PIN_AM1                                (1 & 0x07) // Page 10-0x10[2:0]
// 0 ~ 6 (0: P4D0i<I>, 1: P4D0o<PP>, 2: P4D0o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

// KEY1
#define _PIN_AH9                                (3 & 0x07) // Page 10-0x11[2:0]
// 0 ~ 4 (0: P4D1i<I>, 1: P4D1o<PP>, 2: P4D1o<OD>, 3: A-adc0_0, 4: Int0)

// KEY2
#define _PIN_AH8                                (3 & 0x07) // Page 10-0x12[2:0]
// 0 ~ 4 (0: P4D2i<I>, 1: P4D2o<PP>, 2: P4D2o<OD>, 3: A-adc1_0, 4: INT1)

// LED1
#define _PIN_AJ9                                (1 & 0x07) // Page 10-0x13[2:0]
// 0 ~ 3 (0: P4D3i<I>, 1: P4D3o<PP>, 2: P4D3o<OD>, 3: A-adc2_0)

// LED2
#define _PIN_AJ8                                (1 & 0x07) // Page 10-0x14[2:0]
// 0 ~ 3 (0: P4D4i<I>, 1: P4D4o<PP>, 2: P4D4o<OD>, 3: A-adc3_0)

// DDCSCL_VGA
#define _PIN_AL5                                (3 & 0x07) // Page 10-0x15[2:0]
// 0 ~ 3 (0: P4D5i<I>, 1: P4D5o<PP>, 2: P4D5o<OD>, 3: Ddcsclvga)

// DDCSDA_VGA
#define _PIN_AK5                                (3 & 0x07) // Page 10-0x16[2:0]
// 0 ~ 3 (0: P4D6i<I>, 1: P4D6o<PP>, 2: P4D6o<OD>, 3: Ddcsdavga)

// VGA_CABLE_DET
#define _PIN_AJ5                                (0 & 0x07) // Page 10-0x17[2:0]
// 0 ~ 5 (0: P4D7i<I>, 1: P4D7o<PP>, 2: P4D7o<OD>, 3: PWM0<PP>, 4: PWM0<OD>,
//        5: TCON[4])

// NC
#define _PIN_AK4                                (1 & 0x07) // Page 10-0x18[2:0]
// 0 ~ 6 (0: P5D0i<I>, 1: P5D0o<PP>, 2: P5D0o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[5], 6: INT0)

// NC
#define _PIN_AL4                                (1 & 0x07) // Page 10-0x19[2:0]
// 0 ~ 5 (0: P5D1i<I>, 1: P5D1o<PP>, 2: P5D1o<OD>, 3: PWM2<PP>, 4: PWM2<OD>,
//        5: TCON[7])

// NC
#define _PIN_AM4                                (1 & 0x07) // Page 10-0x1A[2:0]
// 0 ~ 5 (0: P5D2i<I>, 1: P5D2o<PP>, 2: P5D2o<OD>, 3: PWM3<PP>, 4: PWM3<OD>,
//        5: TCON[8])

// NC
#define _PIN_AM2                                (1 & 0x07) // Page 10-0x1B[2:0]
// 0 ~ 7 (0: P5D3i<I>, 1: P5D3o<PP>, 2: P5D3o<OD>, 3: PWM4<PP>, 4: PWM4<OD>,
//        5: TCON[10], 6: INT1, 7: PWM_IN)

// Panel_ON
#define _PIN_AM3                                (1 & 0x07) // Page 10-0x1C[2:0]
// 0 ~ 6 (0: P5D4i<I>, 1: P5D4o<PP>, 2: P5D4o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[12], 6: PWM_OUT)

// EEPROM_WP
#define _PIN_G7                                 (2 & 0x07) // Page 10-0x1D[2:0]
// 0 ~ 5 (0: P5D5i<I>, 1: P5D5o<PP>, 2: P5D5o<OD>, 3: PWM2<PP>, 4: PWM2<OD>,
//        5: TCON[3])

// EESCL
#define _PIN_J7                                 (6 & 0x07) // Page 10-0x1E[2:0]
// 0 ~ 6 (0: P5D6i<I>, 1: P5D6o<PP>, 2: P5D6o<OD>, 3: PWM0<PP>, 4: PWM0<OD>,
//        5: TCON[1], 6: EEIICSCL)

// EESDA
#define _PIN_H6                                 (6 & 0x07) // Page 10-0x1F[2:0]
// 0 ~ 6 (0: P5D7i<I>, 1: P5D7o<PP>, 2: P5D7o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[2], 6: EEIICSDA)

// NC
#define _PIN_AD28                               (1 & 0x0F) // Page 10-0x24[2:0]
// 0 ~ 8 (0: P6D4i<I>, 1: P6D4o<PP>, 2: P6D4o<OD>, 3: TCON[4], 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3, 8: IICSCL1)

// NC
#define _PIN_AH27                               (1 & 0x0F) // Page 10-0x25[2:0]
// 0 ~ 8 (0: P6D5i<I>, 1: P6D5o<PP>, 2: P6D5o<OD>, 3: TCON[5], 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3, 8: IICSDA1)

// DPTX_AUX_P_1
#define _PIN_N29_OFF_REGION                     (6 & 0x07) // Page 10-0x26[2:0]
// 0 ~ 6 (0: P6D6i<I>, 1: P6D6o<PP>, 2: P6D6o<OD>, 3: PWM0<PP>, 4: PWM0<OD>,
//        5: TCON[6], 6: Dptx_aux_ch_p_1)

// DPTX_AUX_N_1
#define _PIN_N28_OFF_REGION                     (6 & 0x07) // Page 10-0x27[2:0]
// 0 ~ 6 (0: P6D7i<I>, 1: P6D7o<PP>, 2: P6D7o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[7], 6: Dptx_aux_ch_n_1)

// DPTX_AUX_P_2
#define _PIN_M29_OFF_REGION                     (6 & 0x07) // Page 10-0x28[2:0]
// 0 ~ 6 (0: P7D0i<I>, 1: P7D0o<PP>, 2: P7D0o<OD>, 3: PWM2<PP>, 4: PWM3<OD>,
//        5: TCON[8], 6: Dptx_aux_ch_p_2)

// DPTX_AUX_N_2
#define _PIN_M28_OFF_REGION                     (6 & 0x07) // Page 10-0x29[2:0]
// 0 ~ 6 (0: P7D1i<I>, 1: P7D1o<PP>, 2: P7D1o<OD>, 3: PWM3<PP>, 4: PWM3<OD>,
//        5: TCON[9], 6: Dptx_aux_ch_n_2)

// NC
#define _PIN_J29_OFF_REGION                     (1 & 0x07) // Page 10-0x2A[2:0]
// 0 ~ 7 (0: P7D2i<I>, 1: P7D2o<PP>, 2: P7D2o<OD>, 3: PWM4<PP>, 4: PWM4<OD>,
//        5: TCON[10], 6: Disp_frame_start_in, 7: Disp_frame_start_out)

// ADJBACKLITE
#define _PIN_AJ28                               (3 & 0x07) // Page 10-0x2B[2:0]
// 0 ~ 6 (0: P7D3i<I>, 1: P7D3o<PP>, 2: P7D3o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[11], 6: Cryclk)

// NC
#define _PIN_N27_OFF_REGION                     (1 & 0x07) // Page 10-0x2C[2:0]
// 0 ~ 6 (0: P7D4i<I>, 1: P7D4o<PP>, 2: P7D4o<OD>, 3: Ws, 4: TCON[12],
//        5: Test4b_out0, 6: Test4b_out1)

// NC
#define _PIN_K27_OFF_REGION                     (1 & 0x07) // Page 10-0x2D[2:0]
// 0 ~ 6 (0: P7D5i<I>, 1: P7D5o<PP>, 2: P7D5o<OD>, 3: Sck, 4: TCON[13],
//        5: Test4b_out2, 6: Test4b_out3)

// NC
#define _PIN_M27_OFF_REGION                     (1 & 0x07) // Page 10-0x2E[2:0]
// 0 ~ 7 (0: P7D6i<I>, 1: P7D6o<PP>, 2: P7D6o<OD>, 3: Mck, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// NC (DP_AUDIO_SDO)
#define _PIN_K29_OFF_REGION                     (0 & 0x07) // Page 10-0x2F[2:0]
// 0 ~ 6 (0: P7D7i<I>, 1: P7D7o<PP>, 2: P7D7o<OD>, 3: Spdif0, 4: Sd0,
//        5: Test4b_out0, 6: Test4b_out1, 7: TCON[0])

// NC
#define _PIN_J28_OFF_REGION                     (1 & 0x07) // Page 10-0x30[2:0]
// 0 ~ 6 (0: P8D0i<I>, 1: P8D0o<PP>, 2: P8D0o<OD>, 3: Spdif1, 4: Sd1,
//        5: Test4b_out2, 6: Test4b_out3,  7: TCON[1])

// NC
#define _PIN_J27_OFF_REGION                     (1 & 0x07) // Page 10-0x31[2:0]
// 0 ~ 6 (0: P8D1i<I>, 1: P8D1o<PP>, 2: P8D1o<OD>, 3: Spdif2, 4: Sd2,
//        5: Test4b_out0, 6: Test4b_out1,  7: TCON[2])

// NC
#define _PIN_K28_OFF_REGION                     (1 & 0x07) // Page 10-0x32[2:0]
// 0 ~ 6 (0: P8D2i<I>, 1: P8D2o<PP>, 2: P8D2o<OD>, 3: Spdif3, 4: Sd3,
//        5: Test4b_out2, 6: Test4b_out3,  7: TCON[3])

// VCCK_OFF_EN
#define _PIN_AH21                               (2 & 0x07) // Page 10-0x33[2:0]
// 0 ~ 4 (0: P8D3i<I>, 1: P8D3o<PP>, 2: P8D3o<OD>, 3: CLKO, 4: Usb_spi_clk)

// DDR_PW_EN
#define _PIN_AK21                               (2 & 0x07) // Page 10-0x34[2:0]
// 0 ~ 4 (0: P8D4i<I>, 1: P8D4o<PP>, 2: P8D4o<OD>, 3: INT0, 4: Usb_spi_si)

// MY_DP_EN
#define _PIN_AJ21                               (1 & 0x07) // Page 10-0x35[2:0]
// 0 ~ 4 (0: P8D5i<I>, 1: P8D5o<PP>, 2: P8D5o<OD>, 3: INT1, 4: Usb_spi_so)

// MUTE
#define _PIN_AJ20                               (1 & 0x07) // Page 10-0x36[2:0]
// 0 ~ 4 (0: P8D6i<I>, 1: P8D6o<PP>, 2: P8D6o<OD>, 3: IRQB, 4: Usb_spi_ceb0)

// NC
#define _PIN_AH20                               (1 & 0x07) // Page 10-0x37[2:0]
// 0 ~ 4 (0: P8D7i<I>, 1: P8D7o<PP>, 2: P8D7o<OD>, 3: T2ex , 4: Usb_spi_ceb1)

// FLASH_WP
#define _PIN_AL21                               (2 & 0x07) // Page 10-0x38[2:0]
// 0 ~ 2 (0: P9D0i<I>, 1: P9D0o<PP>, 2: P9D0o<OD>)

// VTX_PLL_LOCK
#define _PIN_AA29                               (4 & 0x07) // Page 10-0x39[2:0]
// 0 ~ 4 (0: P9D1i<I>, 1: P9D1o<PP>, 2: P9D1o<OD>, 3: Vb1_lock_n, 4: Dptx_hpd2_org)

// VTX_HPD
#define _PIN_AA28                               (4 & 0x07) // Page 10-0x3A[2:0]
// 0 ~ 4 (0: P9D2i<I>, 1: P9D2o<PP>, 2: P9D2o<OD>, 3: Vb1_htpd_n, 4: Dptx_hpd1_org)

// VBUS_EN_2
#define _PIN_AG25                               (1 & 0x07) // Page 10-0x3B[2:0]
// 0 ~ 6 (0: P9D3i<I>, 1: P9D3o<PP>, 2: P9D3o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[7], 6:T0)

// VBUS_EN_3
#define _PIN_AH26                               (1 & 0x07) // Page 10-0x3C[2:0]
// 0 ~ 6 (0: P9D4i<I>, 1: P9D4o<PP>, 2: P9D4o<OD>, 3: PWM4<PP>, 4: PWM4<OD>,
//        5: TCON[6], 6:T1)

// VBUS_EN_4
#define _PIN_AG26                               (1 & 0x07) // Page 10-0x3D[2:0]
// 0 ~ 6 (0: P9D5i<I>, 1: P9D5o<PP>, 2: P9D5o<OD>, 3: PWM3<PP>, 4: PWM3<OD>,
//        5: TCON[5], 6:T2)

// IR_IN
#define _PIN_AJ26                               (6 & 0x07) // Page 10-0x3E[2:0]
// 0 ~ 6 (0: P9D6i<I>, 1: P9D6o<PP>, 2: P9D6o<OD>, 3: PWM2<PP>, 4: PWM2<OD>,
//        5: TCON[4], 6:Irda_in)

// VBUS_EN_5
#define _PIN_AF28                               (1 & 0x07) // Page 10-0x3F[2:0]
// 0 ~ 7 (0: P9D7i<I>, 1: P9D7o<PP>, 2: P9D7o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[3], 6: Test4b_out2, 7: Test4b_out3)

// EDID_WP
#define _PIN_AG24                               (2 & 0x07) // Page 10-0x40[2:0]
// 0 ~ 7 (0: PAD0i<I>, 1: PAD0o<PP>, 2: PAD0o<OD>, 3: PWM0<PP>, 4: PWM0<OD>,
//        5: TCON[2], 6: Test4b_out0, 7: Test4b_out1)

// NC
#define _PIN_AE28                               (0 & 0x0F) // Page 10-0x41[2:0]
// 0 ~ 8 (0: PAD1i<I>, 1: PAD1o<PP>, 2: PAD1o<OD>, 3: TCON[1], 4: reserved,
//        5: reserved, 6: Test4b_out2, 7: Test4b_out3, 8: RXD)

// onBACKLITE
#define _PIN_AJ27                               (2 & 0x0F) // Page 10-0x42[2:0]
// 0 ~ 8 (0: PAD2i<I>, 1: PAD2o<PP>, 2: PAD2o<OD>, 3: TCON[0], 4: Test4b_out0,
//        5: Test4b_out1, 6:reserved, 7: reserved, 8: TXD)

// DP_SINK_ASS_P0
#define _PIN_AG29                               (0 & 0x07) // Page 10-0x43[2:0]
// 0 ~ 7 (0: PAD3i<I>, 1: PAD3o<PP>, 2: PAD3o<OD>, 3: TCON[13], 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// DP_SINK_ASS_N0
#define _PIN_AH25                               (0 & 0x07) // Page 10-0x44[2:0]
// 0 ~ 5 (0: PAD4i<I>, 1: PAD4o<PP>, 2: PAD4o<OD>, 3: TCON[12], 4: Sd3,
//        5: Spdif3)

// DP_CABLE_DET_0
#define _PIN_AF29                               (0 & 0x07) // Page 10-0x45[2:0]
// 0 ~ 5 (0: PAD5i<I>, 1: PAD5o<PP>, 2: PAD5o<OD>, 3: TCON[11], 4: Sd2,
//        5: Spdif2)

// DP_SINK_ASS_P1
#define _PIN_AJ25                               (0 & 0x07) // Page 10-0x46[2:0]
// 0 ~ 5 (0: PAD6i<I>, 1: PAD6o<PP>, 2: PAD6o<OD>, 3: TCON[10], 4: Sd1,
//        5: Spdif1)

// DP_SINK_ASS_N1
#define _PIN_AG28                               (0 & 0x07) // Page 10-0x47[2:0]
// 0 ~ 5 (0: PAD7i<I>, 1: PAD7o<PP>, 2: PAD7o<OD>, 3: TCON[9], 4: Sd0,
//        5: Spdif0)

// DP_CABLE_DET_1
#define _PIN_AH24                               (0 & 0x07) // Page 10-0x48[2:0]
// 0 ~ 7 (0: PBD0i<I>, 1: PBD0o<PP>, 2: PBD0o<OD>, 3: TCON[8], 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

// HDMI_CABLE_DETECT_5
#define _PIN_AF27                               (0 & 0x07) // Page 10-0x49[2:0]
// 0 ~ 7 (0: PBD1i<I>, 1: PBD1o<PP>, 2: PBD1o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3, 7: Mck)

// HDMI_CABLE_DETECT_4
#define _PIN_AJ24                               (0 & 0x07) // Page 10-0x4A[2:0]
// 0 ~ 7 (0: PBD2i<I>, 1: PBD2o<PP>, 2: PBD2o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3, 7: Sck)

// HDMI_CABLE_DETECT_3
#define _PIN_AG27                               (0 & 0x07) // Page 10-0x4B[2:0]
// 0 ~ 7 (0: PBD3i<I>, 1: PBD3o<PP>, 2: PBD3o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3, 7: Ws)

// LINE_INL
#define _PIN_AJ18                               (3 & 0x07) // Page 10-0x4C[2:0]
// 0 ~ 4 (0: PBD4i<I>, 1: PBD4o<PP>, 2: PBD4o<OD>, 3: Line_inl, 4: Ws)

// LINE_INR
#define _PIN_AK18                               (3 & 0x07) // Page 10-0x4D[2:0]
// 0 ~ 4 (0: PBD5i<I>, 1: PBD5o<PP>, 2: PBD5o<OD>, 3: Line_inr, 4: Sck)

// Audio_REF
#define _PIN_AE20                               (3 & 0x07) // Page 10-0x4E[2:0]
// 0 ~ 4 (0: PBD6i<I>, 1: PBD6o<PP>, 2: PBD6o<OD>, 3: Audio_ref, 4: Mck)

// AUDIO_SOUTL
#define _PIN_AL18                               (3 & 0x07) // Page 10-0x4F[2:0]
// 0 ~ 5 (0: PBD7i<I>, 1: PBD7o<PP>, 2: PBD7o<OD>, 3: Audio_soutl, 4: Sdo,
//        5: Spdif0)

// AUDIO_SOUTR
#define _PIN_AM18                               (3 & 0x07) // Page 10-0x50[2:0]
// 0 ~ 5 (0: PCD0i<I>, 1: PCD0o<PP>, 2: PCD0o<OD>, 3: Audio_soutr, 4: Sd1,
//        5: Spdif1)

// AUDIO_HOUTL
#define _PIN_AL19                               (3 & 0x07) // Page 10-0x51[2:0]
// 0 ~ 5 (0: PCD1i<I>, 1: PCD1o<PP>, 2: PCD1o<OD>, 3: Audio_houtl, 4: Sd2,
//        5: Spdif2)

// AUDIO_HOUTR
#define _PIN_AM19                               (3 & 0x07) // Page 10-0x52[2:0]
// 0 ~ 5 (0: PCD2i<I>, 1: PCD2o<PP>, 2: PCD2o<OD>, 3: Audio_houtr, 4: Sd3,
//        5: Spdif3)

// DPTX_AUX_P
#define _PIN_AJ11                               (3 & 0x07) // Page 10-0x53[2:0]
// 0 ~ 3 (0: PCD3i<I>, 1: PCD3o<PP>, 2: PCD3o<OD>, 3: Dptx_aux_ch_p)

// DPTX_AUX_N
#define _PIN_AJ12                               (3 & 0x07) // Page 10-0x54[2:0]
// 0 ~ 3 (0: PCD4i<I>, 1: PCD4o<PP>, 2: PCD4o<OD>, 3: Dptx_aux_ch_n)

// DPTX_HPD
#define _PIN_AG6                                (3 & 0x07) // Page 10-0x55[2:0]
// 0 ~ 3 (0: PCD5i<I>, 1: PCD5o<PP>, 2: PCD5o<OD>, 3: Dptx_hpd_org)

// HDMI_CABLE_DETECT_2
#define _PIN_AJ4                                (0 & 0x07) // Page 10-0x56[2:0]
// 0 ~ 2 (0: PCD6i<I>, 1: PCD6o<PP>, 2: PCD6o<OD>)

// HDMI_MHL_SEL_5
#define _PIN_AF7                                (2 & 0x07) // Page 10-0x57[2:0]
// 0 ~ 2 (0: PCD7i<I>, 1: PCD7o<PP>, 2: PCD7o<OD>)

// HDMI_MHL_SEL_4
#define _PIN_AF6                                (2 & 0x07) // Page 10-0x58[2:0]
// 0 ~ 2 (0: PDD0i<I>, 1: PDD0o<PP>, 2: PDD0o<OD>)

// HDMI_MHL_SEL_3
#define _PIN_AG7                                (2 & 0x07) // Page 10-0x59[2:0]
// 0 ~ 2 (0: PDD1i<I>, 1: PDD1o<PP>, 2: PDD1o<OD>)

// HDMI_MHL_SEL_2
#define _PIN_AH7                                (2 & 0x07) // Page 10-0x5A[2:0]
// 0 ~ 2 (0: PDD2i<I>, 1: PDD2o<PP>, 2: PDD2o<OD>)

// DP_HOT_PLUG_1
#define _PIN_AH6                                (1 & 0x07) // Page 10-0x5B[2:0]
// 0 ~ 2 (0: PDD3i<I>, 1: PDD3o<PP>, 2: PDD3o<OD>)

// DP_HOT_PLUG_0
#define _PIN_AH5                                (1 & 0x07) // Page 10-0x5C[2:0]
// 0 ~ 2 (0: PDD4i<I>, 1: PDD4o<PP>, 2: PDD4o<OD>)

// AUDIO_SCL
#define _PIN_AG8                                (6 & 0x07) // Page 10-0x5D[2:0]
// 0 ~ 6 (0: PDD5i<I>, 1: PDD5o<PP>, 2: PDD5o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5:TCON[7], 6:IICSCL2)

// AUDIO_SDA
#define _PIN_AG9                                (6 & 0x07) // Page 10-0x5E[2:0]
// 0 ~ 6 (0: PDD6i<I>, 1: PDD6o<PP>, 2: PDD6o<OD>, 3: PWM0<PP>, 4: PWM0<OD>,
//        5:TCON[3], 6:IICSDA2)

// DDCSCL_5
#define _PIN_J6                                 (3 & 0x07) // Page 10-0x5F[2:0]
// 0 ~ 3 (0: PDD7i<I>, 1: reserved, 2: PDD7o<OD>, 3: DDCSCL5)

// DDCSDA_5
#define _PIN_J5                                 (3 & 0x07) // Page 10-0x60[2:0]
// 0 ~ 3 (0: PED0i<I>, 1: reserved, 2: PED0o<OD>, 3: DDCSDA5)

// DDCSCL_4
#define _PIN_K6                                 (3 & 0x07) // Page 10-0x61[2:0]
// 0 ~ 3 (0: PED1i<I>, 1: reserved, 2: PED1o<OD>, 3: DDCSCL4)

// DDCSDA_4
#define _PIN_K5                                 (3 & 0x07) // Page 10-0x62[2:0]
// 0 ~ 3 (0: PED2i<I>, 1: reserved, 2: PED2o<OD>, 3: DDCSDA4)

// DDCSCL_3
#define _PIN_L6                                 (3 & 0x07) // Page 10-0x63[2:0]
// 0 ~ 3 (0: PED3i<I>, 1: reserved, 2: PED3o<OD>, 3: DDCSCL3)

// DDCSDA_3
#define _PIN_L5                                 (3 & 0x07) // Page 10-0x64[2:0]
// 0 ~ 3 (0: PED4i<I>, 1: reserved, 2: PED4o<OD>, 3: DDCSDA3)

// DDCSCL_2
#define _PIN_M6                                 (3 & 0x07) // Page 10-0x65[2:0]
// 0 ~ 3 (0: PED5i<I>, 1: reserved, 2: PED5o<OD>, 3: DDCSCL2)

// DDCSDA_2
#define _PIN_M5                                 (3 & 0x07) // Page 10-0x66[2:0]
// 0 ~ 3 (0: PED6i<I>, 1: reserved, 2: PED6o<OD>, 3: DDCSDA2)

// NC
#define _PIN_H7                                 (1 & 0x07) // Page 10-0x67[2:0]
// 0 ~ 3 (0: PED7i<I>, 1: PED7o<PP>, 2: PED7o<OD>)

// NC
#define _PIN_K7                                 (0 & 0x07) // Page 10-0x68[2:0]
// 0     (0: PFD0i<I>)

// CBUS3/HDMI_HPD_5
#define _PIN_C8                                 (2 & 0x07) // Page 10-0x69[2:0]
// 0 ~ 2 (0: PFD1i<I>, 1: PFD1o<PP>, 2: PFD1o<OD>)

// MHL_DETECT_5
#define _PIN_N6                                 (0 & 0x07) // Page 10-0x6A[2:0]
// 0 ~ 2 (0: PFD2i<I>, 1: PFD2o<PP>, 2: PFD2o<OD>)

// CBUS2/HDMI_HPD_4
#define _PIN_C6                                 (2 & 0x07) // Page 10-0x6B[2:0]
// 0 ~ 2 (0: PFD3i<I>, 1: PFD3o<PP>, 2: PFD3o<OD>)

// MHL_DETECT_4
#define _PIN_N5                                 (0 & 0x07) // Page 10-0x6C[2:0]
// 0 ~ 2 (0: PFD4i<I>, 1: PFD4o<PP>, 2: PFD4o<OD>)
