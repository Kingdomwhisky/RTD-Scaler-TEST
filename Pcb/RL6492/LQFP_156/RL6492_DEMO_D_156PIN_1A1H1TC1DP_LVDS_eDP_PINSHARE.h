/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2016>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/
//----------------------------------------------------------------------------------------------------
// ID Code      : RL6492_DEMO_D_156PIN_1A1H1TC1DP_LVDS_eDP_PINSHARE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


/////////////////////////////////
// RL6492 Series 156 Pin Share //
/////////////////////////////////

//---------------------------------------------------------------------------
// Function : SBU2
// Pinshare : 0x1000
// MCU Ctrl : 0xFFE2[0] at _PIN_7_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_7                                  (_PIN_7_AUXP0)

typedef enum
{
    _PIN_7_GPI = 0x00,
    _PIN_7_GPO_PP = 0x01,
    _PIN_7_GPO_OD = 0x02,
    _PIN_7_AUXP0 = 0x03,
    _PIN_7_NC = _PIN_7_GPO_PP,
} EnumPinshareInfoPIN7;

//---------------------------------------------------------------------------
// Function : SBU1
// Pinshare : 0x1001
// MCU Ctrl : 0xFFE2[1] at _PIN_8_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_8                                  (_PIN_8_AUXN0)

typedef enum
{
    _PIN_8_GPI = 0x00,
    _PIN_8_GPO_PP = 0x01,
    _PIN_8_GPO_OD = 0x02,
    _PIN_8_AUXN0 = 0x03,
    _PIN_8_NC = _PIN_8_GPO_PP,
} EnumPinshareInfoPIN8;

//---------------------------------------------------------------------------
// Function : VGA_CABLE_DET
// Pinshare : 0x1002
// MCU Ctrl : 0xFFE2[2] at _PIN_9_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_9                                  (_PIN_9_GPI)

typedef enum
{
    _PIN_9_GPI = 0x00,
    _PIN_9_GPO_PP = 0x01,
    _PIN_9_GPO_OD = 0x02,
    _PIN_9_PWM2_PP = 0x03,
    _PIN_9_PWM2_OD = 0x04,
    _PIN_9_M1_IDOMAIN_HS_OUT = 0x05,
    _PIN_9_PWM_OUT = 0x06,
    _PIN_9_NC = _PIN_9_GPO_PP,
} EnumPinshareInfoPIN9;

//---------------------------------------------------------------------------
// Function : DDCSCL_VGA
// Pinshare : 0x1003
// MCU Ctrl : 0xFFE2[3] at _PIN_10_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_10                                 (_PIN_10_DDCSCLVGA)

typedef enum
{
    _PIN_10_GPI = 0x80,
    _PIN_10_GPO_PP = 0x81,
    _PIN_10_GPO_OD = 0x82,
    _PIN_10_DDCSCLVGA = 0x00,
    _PIN_10_NC = _PIN_10_GPO_PP,
} EnumPinshareInfoPIN10;

//---------------------------------------------------------------------------
// Function : DDCSDA_VGA
// Pinshare : 0x1004
// MCU Ctrl : 0xFFE2[4] at _PIN_11_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_11                                 (_PIN_11_DDCSDAVGA)

typedef enum
{
    _PIN_11_GPI = 0x00,
    _PIN_11_GPO_PP = 0x01,
    _PIN_11_GPO_OD = 0x02,
    _PIN_11_DDCSDAVGA = 0x00,
    _PIN_11_NC = _PIN_11_GPO_PP,
} EnumPinshareInfoPIN11;

//---------------------------------------------------------------------------
// Function : SPWR_DET
// Pinshare : 0x1006
// MCU Ctrl : 0xFFE2[6] at _PIN_14_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_14                                 (_PIN_14_GPO_OD)

typedef enum
{
    _PIN_14_GPI = 0x00,
    _PIN_14_GPO_PP = 0x01,
    _PIN_14_GPO_OD = 0x02,
    _PIN_14_PWM5_PP = 0x03,
    _PIN_14_PWM5_OD = 0x04,
    _PIN_14_INT1 = 0x05,
    _PIN_14_PWM_OUT = 0x06,
    _PIN_14_NC = _PIN_14_GPO_PP,
} EnumPinshareInfoPIN14;

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_N0
// Pinshare : 0x1007
// MCU Ctrl : 0xFFE2[7] at _PIN_15_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_15                                 (_PIN_15_GPI)

typedef enum
{
    _PIN_15_GPI = 0x00,
    _PIN_15_GPO_PP = 0x01,
    _PIN_15_GPO_OD = 0x02,
    _PIN_15_M1_IDOMAIN_VS_OUT = 0x03,
    _PIN_15_TEST4B_OUT0 = 0x04,
    _PIN_15_TEST4B_OUT1 = 0x05,
    _PIN_15_TEST4B_OUT2 = 0x06,
    _PIN_15_TEST4B_OUT3 = 0x07,
    _PIN_15_NC = _PIN_15_GPO_PP,
} EnumPinshareInfoPIN15;

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_P0
// Pinshare : 0x1008
// MCU Ctrl : 0xFFE3[0] at _PIN_16_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_16                                 (_PIN_16_GPI)

typedef enum
{
    _PIN_16_GPI = 0x00,
    _PIN_16_GPO_PP = 0x01,
    _PIN_16_GPO_OD = 0x02,
    _PIN_16_TCON13 = 0x03,
    _PIN_16_TEST4B_OUT0 = 0x04,
    _PIN_16_TEST4B_OUT1 = 0x05,
    _PIN_16_TEST4B_OUT2 = 0x06,
    _PIN_16_TEST4B_OUT3 = 0x07,
    _PIN_16_NC = _PIN_16_GPO_PP,
} EnumPinshareInfoPIN16;

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_P2
// Pinshare : 0x1009
// MCU Ctrl : 0xFFE3[1] at _PIN_17_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_17                                 (_PIN_17_GPI)

typedef enum
{
    _PIN_17_GPI = 0x00,
    _PIN_17_GPO_PP = 0x01,
    _PIN_17_GPO_OD = 0x02,
    _PIN_17_TCON9 = 0x03,
    _PIN_17_M1_IDOMAIN_DEN_OUT = 0x04,
    _PIN_17_TEST4B_OUT0 = 0x05,
    _PIN_17_TEST4B_OUT1 = 0x06,
    _PIN_17_TEST4B_OUT2 = 0x07,
    _PIN_17_NC = _PIN_17_GPO_PP,
} EnumPinshareInfoPIN17;

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_N2
// Pinshare : 0x100A
// MCU Ctrl : 0xFFE3[2] at _PIN_18_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_18                                 (_PIN_18_GPI)

typedef enum
{
    _PIN_18_GPI = 0x00,
    _PIN_18_GPO_PP = 0x01,
    _PIN_18_GPO_OD = 0x02,
    _PIN_18_TCON8 = 0x03,
    _PIN_18_TEST4B_OUT0 = 0x04,
    _PIN_18_TEST4B_OUT1 = 0x05,
    _PIN_18_TEST4B_OUT2 = 0x06,
    _PIN_18_TEST4B_OUT3 = 0x07,
    _PIN_18_TXD = 0x80,
    _PIN_18_NC = _PIN_18_GPO_PP,
} EnumPinshareInfoPIN18;

//---------------------------------------------------------------------------
// Function : HDMI_CABLE_DETECT_1
// Pinshare : 0x100B
// MCU Ctrl : 0xFFE3[3] at _PIN_19_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_19                                 (_PIN_19_GPI)

typedef enum
{
    _PIN_19_GPI = 0x00,
    _PIN_19_GPO_PP = 0x01,
    _PIN_19_GPO_OD = 0x02,
    _PIN_19_TCON7 = 0x03,
    _PIN_19_TEST4B_OUT0 = 0x04,
    _PIN_19_TEST4B_OUT1 = 0x05,
    _PIN_19_TEST4B_OUT2 = 0x06,
    _PIN_19_TEST4B_OUT3 = 0x07,
    _PIN_19_RXD = 0x80,
    _PIN_19_NC = _PIN_19_GPO_PP,
} EnumPinshareInfoPIN19;

//---------------------------------------------------------------------------
// Function : HDMI_HPD_1
// Pinshare : 0x100C
// MCU Ctrl : 0xFFE3[4] at _PIN_20_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_20                                 (_PIN_20_GPO_OD)

typedef enum
{
    _PIN_20_GPI = 0x00,
    _PIN_20_GPO_PP = 0x01,
    _PIN_20_GPO_OD = 0x02,
    _PIN_20_PWM4_PP = 0x03,
    _PIN_20_PWM4_OD = 0x04,
    _PIN_20_INT0 = 0x05,
    _PIN_20_TEST4B_OUT0 = 0x06,
    _PIN_20_TEST4B_OUT1 = 0x07,
    _PIN_20_IICSCL2 = 0x80,
    _PIN_20_NC = _PIN_20_GPO_PP,
} EnumPinshareInfoPIN20;

//---------------------------------------------------------------------------
// Function : BPWR_DET
// Pinshare : 0x100D
// MCU Ctrl : 0xFFE3[5] at _PIN_21_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_21                                 (_PIN_21_GPO_PP)

typedef enum
{
    _PIN_21_GPI = 0x00,
    _PIN_21_GPO_PP = 0x01,
    _PIN_21_GPO_OD = 0x02,
    _PIN_21_TCON6 = 0x03,
    _PIN_21_SD0 = 0x04,
    _PIN_21_TEST4B_OUT1 = 0x05,
    _PIN_21_TEST4B_OUT2 = 0x06,
    _PIN_21_TEST4B_OUT3 = 0x07,
    _PIN_21_IICSDA2 = 0x80,
    _PIN_21_NC = _PIN_21_GPO_PP,
} EnumPinshareInfoPIN21;

//---------------------------------------------------------------------------
// Function : PD_EN
// Pinshare : 0x100E
// MCU Ctrl : 0xFFE3[6] at _PIN_22_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_22                                 (_PIN_22_GPO_PP)

typedef enum
{
    _PIN_22_GPI = 0x00,
    _PIN_22_GPO_PP = 0x01,
    _PIN_22_GPO_OD = 0x02,
    _PIN_22_PWM3_PP = 0x03,
    _PIN_22_PWM3_OD = 0x04,
    _PIN_22_IRDA_IN = 0x05,
    _PIN_22_FRS_GPIO7_PP = 0x06,
    _PIN_22_FRS_GPIO7_OD = 0x07,
    _PIN_22_NC = _PIN_22_GPO_PP,
} EnumPinshareInfoPIN22;

//---------------------------------------------------------------------------
// Function : PD_GPIO2
// Pinshare : 0x100F
// MCU Ctrl : 0xFFE3[7] at _PIN_23_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_23                                 (_PIN_23_GPO_PP)

typedef enum
{
    _PIN_23_GPI = 0x00,
    _PIN_23_GPO_PP = 0x01,
    _PIN_23_GPO_OD = 0x02,
    _PIN_23_SD2 = 0x03,
    _PIN_23_SPDIF2 = 0x04,
    _PIN_23_TCON5 = 0x05,
    _PIN_23_FRS_GPIO6_PP = 0x06,
    _PIN_23_FRS_GPIO6_OD = 0x07,
    _PIN_23_NC = _PIN_23_GPO_PP,
} EnumPinshareInfoPIN23;

//---------------------------------------------------------------------------
// Function : PD_INT#
// Pinshare : 0x1010
// MCU Ctrl : 0xFE00 at _PIN_24_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_24                                 (_PIN_24_GPI)

typedef enum
{
    _PIN_24_GPI = 0x00,
    _PIN_24_GPO_PP = 0x01,
    _PIN_24_GPO_OD = 0x02,
    _PIN_24_SD3 = 0x03,
    _PIN_24_SPDIF3 = 0x04,
    _PIN_24_FRS_GPIO5_PP = 0x05,
    _PIN_24_FRS_GPIO5_OD = 0x06,
    _PIN_24_PWM_IN = 0x07,
    _PIN_24_NC = _PIN_24_GPO_PP,
} EnumPinshareInfoPIN24;

//---------------------------------------------------------------------------
// Function : FLASH_WP
// Pinshare : 0x1012
// MCU Ctrl : 0xFE02 at _PIN_29_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_29                                 (_PIN_29_GPO_PP)

typedef enum
{
    _PIN_29_GPI = 0x00,
    _PIN_29_GPO_PP = 0x01,
    _PIN_29_GPO_OD = 0x02,
    _PIN_29_NC = _PIN_29_GPO_PP,
} EnumPinshareInfoPIN29;

//---------------------------------------------------------------------------
// Function : SDA_HUB (Temporarily not used)
// Pinshare : 0x1013
// MCU Ctrl : 0xFE03 at _PIN_30_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_30                                 (_PIN_30_GPI)

typedef enum
{
    _PIN_30_GPI = 0x00,
    _PIN_30_GPO_PP = 0x01,
    _PIN_30_GPO_OD = 0x02,
    _PIN_30_PWM4_PP = 0x03,
    _PIN_30_PWM4_OD = 0x04,
    _PIN_30_TCON11 = 0x05,
    _PIN_30_T0 = 0x06,
    _PIN_30_CLKO = 0x07,
    _PIN_30_USB_SPI_CLK = 0x80,
    _PIN_30_NC = _PIN_30_GPO_PP,
} EnumPinshareInfoPIN30;

//---------------------------------------------------------------------------
// Function : SCL_HUB (Temporarily not used)
// Pinshare : 0x1014
// MCU Ctrl : 0xFE04 at _PIN_32_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_32                                 (_PIN_32_GPI)

typedef enum
{
    _PIN_32_GPI = 0x00,
    _PIN_32_GPO_PP = 0x01,
    _PIN_32_GPO_OD = 0x02,
    _PIN_32_TCON0 = 0x03,
    _PIN_32_T1 = 0x04,
    _PIN_32_TTL_DEN = 0x05,
    _PIN_32_TEST4B_OUT0 = 0x06,
    _PIN_32_TEST4B_OUT1 = 0x07,
    _PIN_32_USB_SPI_SI = 0x80,
    _PIN_32_NC = _PIN_32_GPO_PP,
} EnumPinshareInfoPIN32;

//---------------------------------------------------------------------------
// Function : VCCK_OFF_EN
// Pinshare : 0x1015
// MCU Ctrl : 0xFE05 at _PIN_33_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_33                                 (_PIN_33_GPO_OD)

typedef enum
{
    _PIN_33_GPI = 0x00,
    _PIN_33_GPO_PP = 0x01,
    _PIN_33_GPO_OD = 0x02,
    _PIN_33_PWM3_PP = 0x03,
    _PIN_33_PWM3_OD = 0x04,
    _PIN_33_TCON10 = 0x05,
    _PIN_33_T2 = 0x06,
    _PIN_33_DCLK = 0x07,
    _PIN_33_USB_SPI_SO = 0x80,
    _PIN_33_NC = _PIN_33_GPO_PP,
} EnumPinshareInfoPIN33;

//---------------------------------------------------------------------------
// Function : PD_GPIO1
// Pinshare : 0x1016
// MCU Ctrl : 0xFE06 at _PIN_37_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_37                                 (_PIN_37_GPO_PP)

typedef enum
{
    _PIN_37_GPI = 0x00,
    _PIN_37_GPO_PP = 0x01,
    _PIN_37_GPO_OD = 0x02,
    _PIN_37_PWM5_PP = 0x03,
    _PIN_37_PWM5_OD = 0x04,
    _PIN_37_TCON12 = 0x05,
    _PIN_37_IRQB = 0x06,
    _PIN_37_TTL_DVS = 0x07,
    _PIN_37_USB_SPI_CEB0 = 0x80,
    _PIN_37_NC = _PIN_37_GPO_PP,
} EnumPinshareInfoPIN37;

//---------------------------------------------------------------------------
// Function : Source_control_2
// Pinshare : 0x1017
// MCU Ctrl : 0xFE07 at _PIN_38_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_38                                 (_PIN_38_GPO_PP)

typedef enum
{
    _PIN_38_GPI = 0x00,
    _PIN_38_GPO_PP = 0x01,
    _PIN_38_GPO_OD = 0x02,
    _PIN_38_TCON1 = 0x03,
    _PIN_38_T2EX = 0x04,
    _PIN_38_TTL_DHS = 0x05,
    _PIN_38_INT0 = 0x06,
    _PIN_38_USB_SPI_CEB1 = 0x80,
    _PIN_38_NC = _PIN_38_GPO_PP,
} EnumPinshareInfoPIN38;

//---------------------------------------------------------------------------
// Function : EEPROM_WP
// Pinshare : 0x1018
// MCU Ctrl : 0xFE08 at _PIN_39_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_39                                 (_PIN_39_GPO_OD)

typedef enum
{
    _PIN_39_GPI = 0x00,
    _PIN_39_GPO_PP = 0x01,
    _PIN_39_GPO_OD = 0x02,
    _PIN_39_TCON12 = 0x03,
    _PIN_39_TEST4B_OUT0 = 0x04,
    _PIN_39_TEST4B_OUT1 = 0x05,
    _PIN_39_TEST4B_OUT2 = 0x06,
    _PIN_39_TEST4B_OUT3 = 0x07,
    _PIN_39_NC = _PIN_39_GPO_PP,
} EnumPinshareInfoPIN39;

//---------------------------------------------------------------------------
// Function : EESCL
// Pinshare : 0x1019
// MCU Ctrl : 0xFE09 at _PIN_40_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_40                                 (_PIN_40_EEIICSCL)

typedef enum
{
    _PIN_40_GPI = 0x00,
    _PIN_40_GPO_PP = 0x01,
    _PIN_40_GPO_OD = 0x02,
    _PIN_40_TCON11 = 0x03,
    _PIN_40_TEST4B_OUT0 = 0x04,
    _PIN_40_TEST4B_OUT1 = 0x05,
    _PIN_40_TEST4B_OUT2 = 0x06,
    _PIN_40_TEST4B_OUT3 = 0x07,
    _PIN_40_EEIICSCL = 0x80,
    _PIN_40_NC = _PIN_40_GPO_PP,
} EnumPinshareInfoPIN40;

//---------------------------------------------------------------------------
// Function : EESDA
// Pinshare : 0x101A
// MCU Ctrl : 0xFE0A at _PIN_41_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_41                                 (_PIN_41_EEIICSDA)

typedef enum
{
    _PIN_41_GPI = 0x00,
    _PIN_41_GPO_PP = 0x01,
    _PIN_41_GPO_OD = 0x02,
    _PIN_41_TCON10 = 0x03,
    _PIN_41_TEST4B_OUT0 = 0x04,
    _PIN_41_TEST4B_OUT1 = 0x05,
    _PIN_41_TEST4B_OUT2 = 0x06,
    _PIN_41_TEST4B_OUT3 = 0x07,
    _PIN_41_EEIICSDA = 0x80,
    _PIN_41_NC = _PIN_41_GPO_PP,
} EnumPinshareInfoPIN41;

//---------------------------------------------------------------------------
// Function : FRS_EN
// Pinshare : 0x101B
// MCU Ctrl : 0xFE0B at _PIN_42_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_42                                 (_PIN_42_GPO_PP)

typedef enum
{
    _PIN_42_GPI = 0x00,
    _PIN_42_GPO_PP = 0x01,
    _PIN_42_GPO_OD = 0x02,
    _PIN_42_WS = 0x03,
    _PIN_42_TCON4 = 0x04,
    _PIN_42_FRS_GPIO2_PP = 0x05,
    _PIN_42_FRS_GPIO2_OD = 0x06,
    _PIN_42_INT1 = 0x07,
    _PIN_42_NC = _PIN_42_GPO_PP,
} EnumPinshareInfoPIN42;

//---------------------------------------------------------------------------
// Function : GPU_SEL
// Pinshare : 0x101C
// MCU Ctrl : 0xFE0C at _PIN_43_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_43                                 (_PIN_43_GPO_OD)

typedef enum
{
    _PIN_43_GPI = 0x00,
    _PIN_43_GPO_PP = 0x01,
    _PIN_43_GPO_OD = 0x02,
    _PIN_43_SCK = 0x03,
    _PIN_43_PWM1_PP = 0x04,
    _PIN_43_PWM1_OD = 0x05,
    _PIN_43_FRS_GPIO1_PP = 0x06,
    _PIN_43_FRS_GPIO1_OD = 0x07,
    _PIN_43_NC = _PIN_43_GPO_PP,
} EnumPinshareInfoPIN43;

//---------------------------------------------------------------------------
// Function : CLIND
// Pinshare : 0x101D
// MCU Ctrl : 0xFE0D at _PIN_44_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_44                                 (_PIN_44_GPI)

typedef enum
{
    _PIN_44_GPI = 0x00,
    _PIN_44_GPO_PP = 0x01,
    _PIN_44_GPO_OD = 0x02,
    _PIN_44_MCK = 0x03,
    _PIN_44_TCON3 = 0x04,
    _PIN_44_FRS_GPIO0_PP = 0x05,
    _PIN_44_FRS_GPIO0_OD = 0x06,
    _PIN_44_NC = _PIN_44_GPO_PP,
} EnumPinshareInfoPIN44;

//---------------------------------------------------------------------------
// Function : PD_SCL
// Pinshare : 0x101E
// MCU Ctrl : 0xFE0E at _PIN_45_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_45                                 (_PIN_45_IICSCL_TPC)

typedef enum
{
    _PIN_45_GPI = 0x00,
    _PIN_45_GPO_PP = 0x01,
    _PIN_45_GPO_OD = 0x02,
    _PIN_45_SD0 = 0x03,
    _PIN_45_SPDIF0 = 0x04,
    _PIN_45_PWM0_PP = 0x05,
    _PIN_45_PWM0_OD = 0x06,
    _PIN_45_TCON13 = 0x07,
    _PIN_45_IICSCL_TPC = 0x80,
    _PIN_45_NC = _PIN_45_GPO_PP,
} EnumPinshareInfoPIN45;

//---------------------------------------------------------------------------
// Function : PD_SDA
// Pinshare : 0x101F
// MCU Ctrl : 0xFE0F at _PIN_46_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_46                                 (_PIN_46_IICSDA_TPC)

typedef enum
{
    _PIN_46_GPI = 0x00,
    _PIN_46_GPO_PP = 0x01,
    _PIN_46_GPO_OD = 0x02,
    _PIN_46_SD1 = 0x03,
    _PIN_46_SPDIF1 = 0x04,
    _PIN_46_TCON2 = 0x05,
    _PIN_46_TEST4B_OUT0 = 0x06,
    _PIN_46_TEST4B_OUT1 = 0x07,
    _PIN_46_IICSDA_TPC = 0x80,
    _PIN_46_NC = _PIN_46_GPO_PP,
} EnumPinshareInfoPIN46;

//---------------------------------------------------------------------------
// Function : TXC3P
// Pinshare : 0x1020
// MCU Ctrl : 0xFE10 at _PIN_58_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_58_OFF_REGION                      (_PIN_58_TXA3P_8B)

typedef enum
{
    _PIN_58_HI_Z = 0x00,
    _PIN_58_GPI = 0x01,
    _PIN_58_GPO_PP = 0x02,
    _PIN_58_GPO_OD = 0x03,
    _PIN_58_TXA3P_8B = 0x04,
    _PIN_58_NC = _PIN_58_GPO_PP,
} EnumPinshareInfoPIN58;

//---------------------------------------------------------------------------
// Function : TXC3N
// Pinshare : 0x1021
// MCU Ctrl : 0xFE11 at _PIN_59_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_59_OFF_REGION                      (_PIN_59_TXA3N_8B)

typedef enum
{
    _PIN_59_HI_Z = 0x00,
    _PIN_59_GPI = 0x01,
    _PIN_59_GPO_PP = 0x02,
    _PIN_59_GPO_OD = 0x03,
    _PIN_59_TXA3N_8B = 0x04,
    _PIN_59_NC = _PIN_59_GPO_PP,
} EnumPinshareInfoPIN59;

//---------------------------------------------------------------------------
// Function : TXCCP
// Pinshare : 0x1022
// MCU Ctrl : 0xFE12 at _PIN_60_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_60_OFF_REGION                      (_PIN_60_TXACP_8B)

typedef enum
{
    _PIN_60_HI_Z = 0x00,
    _PIN_60_GPI = 0x01,
    _PIN_60_GPO_PP = 0x02,
    _PIN_60_GPO_OD = 0x03,
    _PIN_60_TXACP_8B = 0x04,
    _PIN_60_NC = _PIN_60_GPO_PP,
} EnumPinshareInfoPIN60;

//---------------------------------------------------------------------------
// Function : TXCCN
// Pinshare : 0x1023
// MCU Ctrl : 0xFE13 at _PIN_61_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_61_OFF_REGION                      (_PIN_61_TXACN_8B)

typedef enum
{
    _PIN_61_HI_Z = 0x00,
    _PIN_61_GPI = 0x01,
    _PIN_61_GPO_PP = 0x02,
    _PIN_61_GPO_OD = 0x03,
    _PIN_61_TXACN_8B = 0x04,
    _PIN_61_NC = _PIN_61_GPO_PP,
} EnumPinshareInfoPIN61;

//---------------------------------------------------------------------------
// Function : TXC2P
// Pinshare : 0x1024
// MCU Ctrl : 0xFE14 at _PIN_62_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_62_OFF_REGION                      (_PIN_62_TXA2P_8B)

typedef enum
{
    _PIN_62_HI_Z = 0x00,
    _PIN_62_GPI = 0x01,
    _PIN_62_GPO_PP = 0x02,
    _PIN_62_GPO_OD = 0x03,
    _PIN_62_TXA2P_8B = 0x04,
    _PIN_62_NC = _PIN_62_GPO_PP,
} EnumPinshareInfoPIN62;

//---------------------------------------------------------------------------
// Function : TXC2N
// Pinshare : 0x1025
// MCU Ctrl : 0xFE15 at _PIN_63_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_63_OFF_REGION                      (_PIN_63_TXA2N_8B)

typedef enum
{
    _PIN_63_HI_Z = 0x00,
    _PIN_63_GPI = 0x01,
    _PIN_63_GPO_PP = 0x02,
    _PIN_63_GPO_OD = 0x03,
    _PIN_63_TXA2N_8B = 0x04,
    _PIN_63_NC = _PIN_63_GPO_PP,
} EnumPinshareInfoPIN63;

//---------------------------------------------------------------------------
// Function : TXC1P
// Pinshare : 0x1026
// MCU Ctrl : 0xFE16 at _PIN_64_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_64_OFF_REGION                      (_PIN_64_TXA1P_8B)

typedef enum
{
    _PIN_64_HI_Z = 0x00,
    _PIN_64_GPI = 0x01,
    _PIN_64_GPO_PP = 0x02,
    _PIN_64_GPO_OD = 0x03,
    _PIN_64_TXA1P_8B = 0x04,
    _PIN_64_NC = _PIN_64_GPO_PP,
} EnumPinshareInfoPIN64;

//---------------------------------------------------------------------------
// Function : TXC1N
// Pinshare : 0x1027
// MCU Ctrl : 0xFE17 at _PIN_65_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_65_OFF_REGION                      (_PIN_65_TXA1N_8B)

typedef enum
{
    _PIN_65_HI_Z = 0x00,
    _PIN_65_GPI = 0x01,
    _PIN_65_GPO_PP = 0x02,
    _PIN_65_GPO_OD = 0x03,
    _PIN_65_TXA1N_8B = 0x04,
    _PIN_65_NC = _PIN_65_GPO_PP,
} EnumPinshareInfoPIN65;

//---------------------------------------------------------------------------
// Function : TXC0P
// Pinshare : 0x1028
// MCU Ctrl : 0xFE18 at _PIN_66_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_66_OFF_REGION                      (_PIN_66_TXA0P_8B)

typedef enum
{
    _PIN_66_HI_Z = 0x00,
    _PIN_66_GPI = 0x01,
    _PIN_66_GPO_PP = 0x02,
    _PIN_66_GPO_OD = 0x03,
    _PIN_66_TXA0P_8B = 0x04,
    _PIN_66_NC = _PIN_66_GPO_PP,
} EnumPinshareInfoPIN66;

//---------------------------------------------------------------------------
// Function : TXC0N
// Pinshare : 0x1029
// MCU Ctrl : 0xFE19 at _PIN_67_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_67_OFF_REGION                      (_PIN_67_TXA0N_8B)

typedef enum
{
    _PIN_67_HI_Z = 0x00,
    _PIN_67_GPI = 0x01,
    _PIN_67_GPO_PP = 0x02,
    _PIN_67_GPO_OD = 0x03,
    _PIN_67_TXA0N_8B = 0x04,
    _PIN_67_NC = _PIN_67_GPO_PP,
} EnumPinshareInfoPIN67;

//---------------------------------------------------------------------------
// Function : LINE_INL
// Pinshare : 0x102A
// MCU Ctrl : 0xFE1A at _PIN_69_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_69                                 (_PIN_69_LINE_INL)

typedef enum
{
    _PIN_69_GPI = 0x00,
    _PIN_69_GPO_PP = 0x01,
    _PIN_69_GPO_OD = 0x02,
    _PIN_69_LINE_INL = 0x03,
    _PIN_69_MCK = 0x04,
    _PIN_69_NC = _PIN_69_GPO_PP,
} EnumPinshareInfoPIN69;

//---------------------------------------------------------------------------
// Function : LINE_INR
// Pinshare : 0x102B
// MCU Ctrl : 0xFE1B at _PIN_70_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_70                                 (_PIN_70_LINE_INR)

typedef enum
{
    _PIN_70_GPI = 0x00,
    _PIN_70_GPO_PP = 0x01,
    _PIN_70_GPO_OD = 0x02,
    _PIN_70_LINE_INR = 0x03,
    _PIN_70_SCK = 0x04,
    _PIN_70_NC = _PIN_70_GPO_PP,
} EnumPinshareInfoPIN70;

//---------------------------------------------------------------------------
// Function : AUDIO_GND
// Pinshare : 0x102C
// MCU Ctrl : 0xFE1C at _PIN_71_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_71                                 (_PIN_71_AUDIO_REF)

typedef enum
{
    _PIN_71_GPI = 0x00,
    _PIN_71_GPO_PP = 0x01,
    _PIN_71_GPO_OD = 0x02,
    _PIN_71_AUDIO_REF = 0x03,
    _PIN_71_WS = 0x04,
    _PIN_71_NC = _PIN_71_GPO_PP,
} EnumPinshareInfoPIN71;

//---------------------------------------------------------------------------
// Function : AUDIO_SOUTL
// Pinshare : 0x102D
// MCU Ctrl : 0xFE1D at _PIN_72_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_72                                 (_PIN_72_AUDIO_SOUTL)

typedef enum
{
    _PIN_72_GPI = 0x00,
    _PIN_72_GPO_PP = 0x01,
    _PIN_72_GPO_OD = 0x02,
    _PIN_72_AUDIO_SOUTL = 0x03,
    _PIN_72_SD0 = 0x04,
    _PIN_72_SPDIF0 = 0x05,
    _PIN_72_NC = _PIN_72_GPO_PP,
} EnumPinshareInfoPIN72;

//---------------------------------------------------------------------------
// Function : AUDIO_SOUTR
// Pinshare : 0x102E
// MCU Ctrl : 0xFE1E at _PIN_73_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_73                                 (_PIN_73_AUDIO_SOUTR)

typedef enum
{
    _PIN_73_GPI = 0x00,
    _PIN_73_GPO_PP = 0x01,
    _PIN_73_GPO_OD = 0x02,
    _PIN_73_AUDIO_SOUTR = 0x03,
    _PIN_73_SD1 = 0x04,
    _PIN_73_SPDIF1 = 0x05,
    _PIN_73_NC = _PIN_73_GPO_PP,
} EnumPinshareInfoPIN73;

//---------------------------------------------------------------------------
// Function : AUDIO_HOUTL
// Pinshare : 0x102F
// MCU Ctrl : 0xFE1F at _PIN_74_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_74                                 (_PIN_74_AUDIO_HOUTL)

typedef enum
{
    _PIN_74_GPI = 0x00,
    _PIN_74_GPO_PP = 0x01,
    _PIN_74_GPO_OD = 0x02,
    _PIN_74_AUDIO_HOUTL = 0x03,
    _PIN_74_SD2 = 0x04,
    _PIN_74_SPDIF2 = 0x05,
    _PIN_74_NC = _PIN_74_GPO_PP,
} EnumPinshareInfoPIN74;

//---------------------------------------------------------------------------
// Function : AUDIO_HOUTR
// Pinshare : 0x1030
// MCU Ctrl : 0xFE20 at _PIN_75_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_75                                 (_PIN_75_AUDIO_HOUTR)

typedef enum
{
    _PIN_75_GPI = 0x00,
    _PIN_75_GPO_PP = 0x01,
    _PIN_75_GPO_OD = 0x02,
    _PIN_75_AUDIO_HOUTR = 0x03,
    _PIN_75_SD3 = 0x04,
    _PIN_75_SPDIF3 = 0x05,
    _PIN_75_NC = _PIN_75_GPO_PP,
} EnumPinshareInfoPIN75;

//---------------------------------------------------------------------------
// Function : Panel_ON
// Pinshare : 0x1031
// MCU Ctrl : 0xFE21 at _PIN_78_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_78                                 (_PIN_78_GPO_PP)

typedef enum
{
    _PIN_78_GPI = 0x00,
    _PIN_78_GPO_PP = 0x01,
    _PIN_78_GPO_OD = 0x02,
    _PIN_78_TCON0 = 0x03,
    _PIN_78_TEST4B_OUT0 = 0x04,
    _PIN_78_TEST4B_OUT1 = 0x05,
    _PIN_78_TEST4B_OUT2 = 0x06,
    _PIN_78_TEST4B_OUT3 = 0x07,
    _PIN_78_NC = _PIN_78_GPO_PP,
} EnumPinshareInfoPIN78;

//---------------------------------------------------------------------------
// Function : ADJBACKLITE
// Pinshare : 0x1032
// MCU Ctrl : 0xFE22 at _PIN_80_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_80                                 (_PIN_80_PWM0_PP)

typedef enum
{
    _PIN_80_GPI = 0x00,
    _PIN_80_GPO_PP = 0x01,
    _PIN_80_GPO_OD = 0x02,
    _PIN_80_PWM0_PP = 0x03,
    _PIN_80_PWM0_OD = 0x04,
    _PIN_80_TEST4B_OUT0 = 0x05,
    _PIN_80_TEST4B_OUT1 = 0x06,
    _PIN_80_TEST4B_OUT2 = 0x07,
    _PIN_80_IICSCL1 = 0x80,
    _PIN_80_NC = _PIN_80_GPO_PP,
} EnumPinshareInfoPIN80;

//---------------------------------------------------------------------------
// Function : onBACKLITE
// Pinshare : 0x1033
// MCU Ctrl : 0xFE23 at _PIN_79_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_79                                 (_PIN_79_GPO_OD)

typedef enum
{
    _PIN_79_GPI = 0x00,
    _PIN_79_GPO_PP = 0x01,
    _PIN_79_GPO_OD = 0x02,
    _PIN_79_TCON1 = 0x03,
    _PIN_79_TEST4B_OUT0 = 0x04,
    _PIN_79_TEST4B_OUT1 = 0x05,
    _PIN_79_TEST4B_OUT2 = 0x06,
    _PIN_79_TEST4B_OUT3 = 0x07,
    _PIN_79_IICSDA1 = 0x80,
    _PIN_79_NC = _PIN_79_GPO_PP,
} EnumPinshareInfoPIN79;

//---------------------------------------------------------------------------
// Function : EDID_WP
// Pinshare : 0x1034
// MCU Ctrl : 0xFE24 at _PIN_81_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_81                                 (_PIN_81_GPO_OD)

typedef enum
{
    _PIN_81_GPI = 0x00,
    _PIN_81_GPO_PP = 0x01,
    _PIN_81_GPO_OD = 0x02,
    _PIN_81_PWM1_PP = 0x03,
    _PIN_81_PWM1_OD = 0x04,
    _PIN_81_FRS_GPIO3_PP = 0x05,
    _PIN_81_FRS_GPIO3_OD = 0x06,
    _PIN_81_NC = _PIN_81_GPO_PP,
} EnumPinshareInfoPIN81;

//---------------------------------------------------------------------------
// Function : DP_HOT_PLUG_2
// Pinshare : 0x1035
// MCU Ctrl : 0xFE25 at _PIN_82_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_82                                 (_PIN_82_GPO_PP)

typedef enum
{
    _PIN_82_GPI = 0x00,
    _PIN_82_GPO_PP = 0x01,
    _PIN_82_GPO_OD = 0x02,
    _PIN_82_TCON5 = 0x03,
    _PIN_82_TEST4B_OUT0 = 0x04,
    _PIN_82_TEST4B_OUT1 = 0x05,
    _PIN_82_TEST4B_OUT2 = 0x06,
    _PIN_82_TEST4B_OUT3 = 0x07,
    _PIN_82_NC = _PIN_82_GPO_PP,
} EnumPinshareInfoPIN82;

//---------------------------------------------------------------------------
// Function : DPTX_AUX_P_2
// Pinshare : 0x1036
// MCU Ctrl : 0xFE26 at _PIN_83_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_83                                 (_PIN_83_DPTX_AUX_CH_P_1)

typedef enum
{
    _PIN_83_GPI = 0x00,
    _PIN_83_GPO_PP = 0x01,
    _PIN_83_GPO_OD = 0x02,
    _PIN_83_DPTX_AUX_CH_P_1 = 0x03,
    _PIN_83_TCON3 = 0x04,
    _PIN_83_TEST4B_OUT0 = 0x05,
    _PIN_83_TEST4B_OUT1 = 0x06,
    _PIN_83_TEST4B_OUT2 = 0x07,
    _PIN_83_NC = _PIN_83_GPO_PP,
} EnumPinshareInfoPIN83;

//---------------------------------------------------------------------------
// Function : DPTX_AUX_N_2
// Pinshare : 0x1037
// MCU Ctrl : 0xFE27 at _PIN_84_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_84                                 (_PIN_84_DPTX_AUX_CH_N_1)

typedef enum
{
    _PIN_84_GPI = 0x00,
    _PIN_84_GPO_PP = 0x01,
    _PIN_84_GPO_OD = 0x02,
    _PIN_84_DPTX_AUX_CH_N_1 = 0x03,
    _PIN_84_TCON4 = 0x04,
    _PIN_84_TEST4B_OUT0 = 0x05,
    _PIN_84_TEST4B_OUT1 = 0x06,
    _PIN_84_TEST4B_OUT2 = 0x07,
    _PIN_84_NC = _PIN_84_GPO_PP,
} EnumPinshareInfoPIN84;

//---------------------------------------------------------------------------
// Function : TX2_HPD_2
// Pinshare : 0x1038
// MCU Ctrl : 0xFE28 at _PIN_85_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_85                                 (_PIN_85_DPTX_HPD1_ORG)

typedef enum
{
    _PIN_85_GPI = 0x00,
    _PIN_85_GPO_PP = 0x01,
    _PIN_85_GPO_OD = 0x02,
    _PIN_85_DPTX_HPD1_ORG = 0x03,
    _PIN_85_TCON2 = 0x04,
    _PIN_85_TEST4B_OUT0 = 0x05,
    _PIN_85_TEST4B_OUT1 = 0x06,
    _PIN_85_TEST4B_OUT2 = 0x07,
    _PIN_85_NC = _PIN_85_GPO_PP,
} EnumPinshareInfoPIN85;

//---------------------------------------------------------------------------
// Function : DP_CABLE_DET_2
// Pinshare : 0x1039
// MCU Ctrl : 0xFE29 at _PIN_91_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_91                                 (_PIN_91_GPI)

typedef enum
{
    _PIN_91_GPI = 0x00,
    _PIN_91_GPO_PP = 0x01,
    _PIN_91_GPO_OD = 0x02,
    _PIN_91_PWM2_PP = 0x03,
    _PIN_91_PWM2_OD = 0x04,
    _PIN_91_FRS_GPIO4_PP = 0x05,
    _PIN_91_FRS_GPIO4_OD = 0x06,
    _PIN_91_NC = _PIN_91_GPO_PP,
} EnumPinshareInfoPIN91;

//---------------------------------------------------------------------------
// Function : ADC_KEY1
// Pinshare : 0x103A
// MCU Ctrl : 0xFE2A at _PIN_86_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_86                                 (_PIN_86_A_ADC0)

typedef enum
{
    _PIN_86_GPI = 0x00,
    _PIN_86_GPO_PP = 0x01,
    _PIN_86_GPO_OD = 0x02,
    _PIN_86_A_ADC0 = 0x03,
    _PIN_86_TCON6 = 0x04,
    _PIN_86_INT0 = 0x05,
    _PIN_86_NC = _PIN_86_GPO_PP,
} EnumPinshareInfoPIN86;

//---------------------------------------------------------------------------
// Function : ADC_KEY2
// Pinshare : 0x103B
// MCU Ctrl : 0xFE2B at _PIN_87_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_87                                 (_PIN_87_A_ADC1)

typedef enum
{
    _PIN_87_GPI = 0x00,
    _PIN_87_GPO_PP = 0x01,
    _PIN_87_GPO_OD = 0x02,
    _PIN_87_A_ADC1 = 0x03,
    _PIN_87_TCON7 = 0x04,
    _PIN_87_INT1 = 0x05,
    _PIN_87_NC = _PIN_87_GPO_PP,
} EnumPinshareInfoPIN87;

//---------------------------------------------------------------------------
// Function : LED1
// Pinshare : 0x103C
// MCU Ctrl : 0xFE2C at _PIN_88_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_88                                 (_PIN_88_GPO_PP)

typedef enum
{
    _PIN_88_GPI = 0x00,
    _PIN_88_GPO_PP = 0x01,
    _PIN_88_GPO_OD = 0x02,
    _PIN_88_A_ADC2 = 0x03,
    _PIN_88_TCON8 = 0x04,
    _PIN_88_NC = _PIN_88_GPO_PP,
} EnumPinshareInfoPIN88;

//---------------------------------------------------------------------------
// Function : LED2
// Pinshare : 0x103D
// MCU Ctrl : 0xFE2D at _PIN_89_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_89                                 (_PIN_89_GPO_PP)

typedef enum
{
    _PIN_89_GPI = 0x00,
    _PIN_89_GPO_PP = 0x01,
    _PIN_89_GPO_OD = 0x02,
    _PIN_89_A_ADC3 = 0x03,
    _PIN_89_TCON9 = 0x04,
    _PIN_89_NC = _PIN_89_GPO_PP,
} EnumPinshareInfoPIN89;

//---------------------------------------------------------------------------
// Function : AUX_CHP_2
// Pinshare : 0x103E
// MCU Ctrl : 0xFE2E at _PIN_97_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_97                                 (_PIN_97_AUXP2)

typedef enum
{
    _PIN_97_GPI = 0x80,
    _PIN_97_GPO_OD = 0x82,
    _PIN_97_AUXP2 = 0x83,
    _PIN_97_DDCSCL2 = 0x00,
    _PIN_97_NC = _PIN_97_GPI,
} EnumPinshareInfoPIN97;

//---------------------------------------------------------------------------
// Function : AUX_CHN_2
// Pinshare : 0x103F
// MCU Ctrl : 0xFE2F at _PIN_98_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_98                                 (_PIN_98_AUXN2)

typedef enum
{
    _PIN_98_GPI = 0x00,
    _PIN_98_GPO_OD = 0x02,
    _PIN_98_AUXN2 = 0x03,
    _PIN_98_DDCSDA2 = 0x00,
    _PIN_98_NC = _PIN_98_GPI,
} EnumPinshareInfoPIN98;

//---------------------------------------------------------------------------
// Function : DDCSCL_1
// Pinshare : 0x1040
// MCU Ctrl : 0xFE30 at _PIN_99_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_99                                 (_PIN_99_DDCSCL1)

typedef enum
{
    _PIN_99_GPI = 0x80,
    _PIN_99_GPO_OD = 0x82,
    _PIN_99_AUXP1 = 0x83,
    _PIN_99_DDCSCL1 = 0x00,
    _PIN_99_NC = _PIN_99_GPI,
} EnumPinshareInfoPIN99;

//---------------------------------------------------------------------------
// Function : DDCSDA_1
// Pinshare : 0x1041
// MCU Ctrl : 0xFE31 at _PIN_100_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_100                                (_PIN_100_DDCSDA1)

typedef enum
{
    _PIN_100_GPI = 0x00,
    _PIN_100_GPO_OD = 0x02,
    _PIN_100_AUXN1 = 0x03,
    _PIN_100_DDCSDA1 = 0x00,
    _PIN_100_NC = _PIN_100_GPI,
} EnumPinshareInfoPIN100;
