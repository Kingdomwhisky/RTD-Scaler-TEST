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
// ID Code      : RL6369_Series_Pin_Mapping.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#ifdef _76PIN_PIN_21

#define _USB_LV_SUPPORT                         _DISABLE

//--------------------------------------------------
// Bonded Pin Mapping Table
//--------------------------------------------------
#define _PIN_34                                 _76PIN_PIN_21
#define _PIN_35                                 _76PIN_PIN_22
#define _PIN_36                                 _76PIN_PIN_23
#define _PIN_37                                 _76PIN_PIN_24
#define _PIN_38                                 _76PIN_PIN_25
#define _PIN_42                                 _76PIN_PIN_27
#define _PIN_43                                 _76PIN_PIN_28
#define _PIN_44                                 _76PIN_PIN_29
#define _PIN_46                                 _76PIN_PIN_30
#define _PIN_47                                 _76PIN_PIN_31
#define _PIN_48                                 _76PIN_PIN_32
#define _PIN_49                                 _76PIN_PIN_33
#define _PIN_50                                 _76PIN_PIN_34
#define _PIN_63                                 _76PIN_PIN_37
#define _PIN_64                                 _76PIN_PIN_38
#define _PIN_67                                 _76PIN_PIN_39
#define _PIN_68                                 _76PIN_PIN_40
#define _PIN_69                                 _76PIN_PIN_41
#define _PIN_70                                 _76PIN_PIN_42
#define _PIN_71                                 _76PIN_PIN_43
#define _PIN_72                                 _76PIN_PIN_44
#define _PIN_73                                 _76PIN_PIN_45
#define _PIN_74                                 _76PIN_PIN_46
#define _PIN_96                                 _76PIN_PIN_58
#define _PIN_97                                 _76PIN_PIN_59
#define _PIN_98                                 _76PIN_PIN_60
#define _PIN_99                                 _76PIN_PIN_61
#define _PIN_100                                _76PIN_PIN_62
#define _PIN_101                                _76PIN_PIN_63
#define _PIN_112                                _76PIN_PIN_70
#define _PIN_113                                _76PIN_PIN_71

//--------------------------------------------------
// Not Bonded Pin
//--------------------------------------------------

//
#define _PIN_21                                 (1 & 0x0F) // Page 10-0x00[3:0]
// 0 ~ 15 (0: P1d0i <I> , 1: P1d0o <PP>, 2: P1d0o <OD>, 3: CLKO , 4~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15: Test4b_out3)

//
#define _PIN_22                                 (1 & 0x0F) // Page 10-0x01[3:0]
// 0 ~ 15 (0: P1d1i <I> , 1: P1d1o <PP>, 2: P1d1o <OD>, 3~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15: Test4b_out3)

//
#define _PIN_39                                 (1 & 0x0F) // Page 10-0x07[3:0]
// 0 ~ 15 (0: P1d7i <I> , 1: P1d7o <PP>, 2: P1d7o <OD>, 3: PWM5<PP> , 4: PWM5<OD>, 5: IIS_SD2, 6: Spdif2, 7~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_45                                 (1 & 0x0F) // Page 10-0x0B[3:0]
// 0 ~ 15 (0: P3d3i <I> , 1: P3d3o <PP>, 2: P3d3o <OD>, 3: A-adc3, 4~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_52                                 (1 & 0x0F) // Page 10-0x11[3:0]
// 0 ~ 15 (0: P4d1i <I> , 1: P4d1o <PP>, 2: P4d1o <OD>, 3: PWM0<PP>, 4: PWM0<OD>, 5: IIS_SD3, 6: Spdif3, 7~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_53                                 (1 & 0x0F) // Page 10-0x12[3:0]
// 0 ~ 15 (0: P4d2i <I> , 1: P4d2o <PP>, 2: P4d2o <OD>, 3: PWM3<PP>, 4: PWM3<OD>, 5:PWM4<PP> , 6:PWM4<OD>, 7~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_55                                 (1 & 0x0F) // Page 10-0x13[3:0]
// 0 ~ 15 (0: P4d3i <I> , 1: P4d3o <PP>, 2: P4d3o <OD>, 3: PWM0<PP>, 4: PWM0<OD>, 5: IIS_MCK, 6: Line_inl, 7~11:reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_56                                 (1 & 0x0F) // Page 10-0x14[3:0]
// 0 ~ 15 (0: P4d4i <I> , 1: P4d4o <PP>, 2: P4d4o <OD>, 3: IIS_SCK, 4: Line_inr, 5~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_57                                 (1 & 0x0F) // Page 10-0x15[3:0]
// 0 ~ 15 (0: P4d5i <I> , 1: P4d5o <PP>, 2: P4d5o <OD>, 3: IIS_WS, 4: Audio_ref, 5: Tcon[13] , 6~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_58                                 (1 & 0x0F) // Page 10-0x16[3:0]
// 0 ~ 15 (0: P4d6i <I> , 1: P4d6o <PP>, 2: P4d6o <OD>, 3: IIS_SD0, 4: Spdif0, 5: Soutl, 6~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_59                                 (1 & 0x0F) // Page 10-0x17[3:0]
// 0 ~ 15 (0: P4d7i <I> , 1: P4d7o <PP>, 2: P4d7o <OD>, 3: IIS_SD1, 4: Spdif1, 5: Soutr, 6~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_60                                 (1 & 0x0F) // Page 10-0x18[3:0]
// 0 ~ 15 (0: P5d0i <I> , 1: P5d0o <PP>, 2: P5d0o <OD>, 3: IIS_SD2, 4: Spdif2, 5: Houtl, 6: reserved, 7: IICSCL2, 8:Rxd, 9~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_61                                 (1 & 0x0F) // Page 10-0x19[3:0]
// 0 ~ 15 (0: P5d1i <I> , 1: P5d1o <PP>, 2: P5d1o <OD>, 3: IIS_SD3, 4: Spdif3, 5: Houtr, 6: reserved, 7: IICSDA2, 8: Txd, 9~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

// TXD4P
#define _PIN_65                                 (1 & 0x0F) // Page 10-0x1C[3:0]
// 0 ~ 15 (0: Hi-Z <I> , 1:P5d4i <I>, 2: P5d4o <PP>, 3: P5d4o <OD>, 4: TXO4+_10b, 5: TTL_BLU7, 6~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

// TXD4N
#define _PIN_66                                 (1 & 0x0F) // Page 10-0x1D[3:0]
// 0 ~ 15 (0: Hi-Z <I> , 1:P5d5i <I>, 2: P5d5o <PP>, 3: P5d5o <OD>, 4: TXO4-_10b, 5: TTL_BLU6, 6~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

// TXC4P
#define _PIN_77                                 (1 & 0x0F) // Page 10-0x26[3:0]
// 0 ~ 15 (0: Hi-Z <I> , 1:P6d6i <I>, 2: P6d6o <PP>, 3: P6d6o <OD>, 4: TXE4+_10b, 5: TTL_GRN5, 6~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

// TXC4N
#define _PIN_78                                 (1 & 0x0F) // Page 10-0x27[3:0]
// 0 ~ 15 (0: Hi-Z <I> , 1:P6d7i <I>, 2: P6d7o <PP>, 3: P6d7o <OD>, 4: TXE4-_10b, 5: TTL_GRN4, 6~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_110                                (1 & 0x0F) // Page 10-0x2E[3:0]
// 0 ~ 15 (0: P7d6i <I> , 1: P7d6o <PP>, 2: P7d6o <OD>, 3: PWM4<PP>, 4: PWM4<OD>, 5: Auxp, 6: reserved, 7: DDCSCL0, 8~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_111                                (1 & 0x0F) // Page 10-0x2F[3:0]
// 0 ~ 15 (0: P7d7i <I> , 1: P7d7o <PP>, 2: P7d7o <OD>, 3: PWM5<PP>, 4: PWM5<OD>, 5: Auxn, 6: reserved, 7: DDCSDA0, 8~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_114                                (1 & 0x0F) // Page 10-0x33[3:0]
// 0 ~ 15 (0: P8d3i <I> , 1: P8d3o <PP>, 2: P8d3o <OD>, 3: Auxp, 4~6: reserved, 7:  DDCSCL2, 8~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

//
#define _PIN_115                                (1 & 0x0F) // Page 10-0x32[3:0]
// 0 ~ 15 (0: P8d2i <I> , 1: P8d2o <PP>, 2: P8d2o <OD> 3: Auxn, 4~6: reserved, 7:  DDCSDA2, 8~11: reserved, 12: Test4b_out0, 13: Test4b_out1, 14: Test4b_out2, 15:Test4b_out3)

#else
//--------------------------------------------------
// USB LV SuPPLY
//--------------------------------------------------
#define _USB_LV_SUPPORT                         _ENABLE

#endif // End of #ifdef _76PIN_PIN_21
