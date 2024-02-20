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
// ID Code      : RL6463_QA_128PIN_1A1H1DP_PINSHARE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


///////////////
// PCB Mode  //
///////////////

//---------------------------------------------------------------------------
// PCB Rule Select
//---------------------------------------------------------------------------
#define _PCB_NEW_MODE_SUPPORT                   _ON


////////////////////////////////
// RL6463 Series 76 Pin Share //
////////////////////////////////

//---------------------------------------------------------------------------
// Function : ADJBACKLITE
// Pinshare : 0x1002
// MCU Ctrl : 0xFFE2[2] at _76PIN_PIN_21_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_21                           (_76PIN_PIN_21_PWM0_PP)

typedef enum
{
    _76PIN_PIN_21_GPI = 0x00,
    _76PIN_PIN_21_GPO_PP = 0x01,
    _76PIN_PIN_21_GPO_OD = 0x02,
    _76PIN_PIN_21_PWM0_PP = 0x03,
    _76PIN_PIN_21_PWM0_OD = 0x04,
    _76PIN_PIN_21_MCK = 0x05,
    _76PIN_PIN_21_CLKO = 0x06,
    _76PIN_PIN_21_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_21_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_21_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_21_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_21_NC = _76PIN_PIN_21_GPO_PP,
} EnumPinshareInfo76PIN_PIN_21;

//---------------------------------------------------------------------------
// Function : onBACKLITE
// Pinshare : 0x1003
// MCU Ctrl : 0xFFE2[3] at _76PIN_PIN_22_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_22                           (_76PIN_PIN_22_GPO_OD)

typedef enum
{
    _76PIN_PIN_22_GPI = 0x00,
    _76PIN_PIN_22_GPO_PP = 0x01,
    _76PIN_PIN_22_GPO_OD = 0x02,
    _76PIN_PIN_22_PWM1_PP = 0x03,
    _76PIN_PIN_22_PWM1_OD = 0x04,
    _76PIN_PIN_22_SCK = 0x05,
    _76PIN_PIN_22_IRQB = 0x06,
    _76PIN_PIN_22_TCON13 = 0x07,
    _76PIN_PIN_22_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_22_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_22_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_22_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_22_NC = _76PIN_PIN_22_GPO_PP,
} EnumPinshareInfo76PIN_PIN_22;

//---------------------------------------------------------------------------
// Function : VGA_CABLE_DET
// Pinshare : 0x1004
// MCU Ctrl : 0xFFE2[4] at _76PIN_PIN_23_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_23                           (_76PIN_PIN_23_GPI)

typedef enum
{
    _76PIN_PIN_23_GPI = 0x00,
    _76PIN_PIN_23_GPO_PP = 0x01,
    _76PIN_PIN_23_GPO_OD = 0x02,
    _76PIN_PIN_23_PWM2_PP = 0x03,
    _76PIN_PIN_23_PWM2_OD = 0x04,
    _76PIN_PIN_23_WS = 0x05,
    _76PIN_PIN_23_TCON13 = 0x06,
    _76PIN_PIN_23_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_23_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_23_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_23_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_23_NC = _76PIN_PIN_23_GPO_PP,
} EnumPinshareInfo76PIN_PIN_23;

//---------------------------------------------------------------------------
// Function : DP_CABLE_DET_1
// Pinshare : 0x1005
// MCU Ctrl : 0xFFE2[5] at _76PIN_PIN_24_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_24                           (_76PIN_PIN_24_GPI)

typedef enum
{
    _76PIN_PIN_24_GPI = 0x00,
    _76PIN_PIN_24_GPO_PP = 0x01,
    _76PIN_PIN_24_GPO_OD = 0x02,
    _76PIN_PIN_24_PWM3_PP = 0x03,
    _76PIN_PIN_24_PWM3_OD = 0x04,
    _76PIN_PIN_24_SD0 = 0x05,
    _76PIN_PIN_24_SPDIF0 = 0x06,
    _76PIN_PIN_24_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_24_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_24_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_24_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_24_IICSCL0 = 0x40,
    _76PIN_PIN_24_RXD0 = 0x80,
    _76PIN_PIN_24_NC = _76PIN_PIN_24_GPO_PP,
} EnumPinshareInfo76PIN_PIN_24;

//---------------------------------------------------------------------------
// Function : ADC_KEY1
// Pinshare : 0x1008
// MCU Ctrl : 0xFFE3[0] at _76PIN_PIN_27_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_27                           (_76PIN_PIN_27_A_ADC0)

typedef enum
{
    _76PIN_PIN_27_GPI = 0x00,
    _76PIN_PIN_27_GPO_PP = 0x01,
    _76PIN_PIN_27_GPO_OD = 0x02,
    _76PIN_PIN_27_A_ADC0 = 0x03,
    _76PIN_PIN_27_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_27_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_27_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_27_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_27_NC = _76PIN_PIN_27_GPO_PP,
} EnumPinshareInfo76PIN_PIN_27;

//---------------------------------------------------------------------------
// Function : ADC_KEY2
// Pinshare : 0x1009
// MCU Ctrl : 0xFFE3[1] at _76PIN_PIN_28_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_28                           (_76PIN_PIN_28_A_ADC1)

typedef enum
{
    _76PIN_PIN_28_GPI = 0x00,
    _76PIN_PIN_28_GPO_PP = 0x01,
    _76PIN_PIN_28_GPO_OD = 0x02,
    _76PIN_PIN_28_A_ADC1 = 0x03,
    _76PIN_PIN_28_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_28_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_28_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_28_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_28_NC = _76PIN_PIN_28_GPO_PP,
} EnumPinshareInfo76PIN_PIN_28;

//---------------------------------------------------------------------------
// Function : LED4
// Pinshare : 0x100A
// MCU Ctrl : 0xFFE3[2] at _76PIN_PIN_29_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_29                           (_76PIN_PIN_29_GPO_PP)

typedef enum
{
    _76PIN_PIN_29_GPI = 0x00,
    _76PIN_PIN_29_GPO_PP = 0x01,
    _76PIN_PIN_29_GPO_OD = 0x02,
    _76PIN_PIN_29_A_ADC2 = 0x03,
    _76PIN_PIN_29_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_29_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_29_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_29_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_29_NC = _76PIN_PIN_29_GPO_PP,
} EnumPinshareInfo76PIN_PIN_29;

//---------------------------------------------------------------------------
// Function : EEPROM_WP
// Pinshare : 0x100C
// MCU Ctrl : 0xFFE3[4] at _76PIN_PIN_30_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_30                           (_76PIN_PIN_30_GPO_OD)

typedef enum
{
    _76PIN_PIN_30_GPI = 0x00,
    _76PIN_PIN_30_GPO_PP = 0x01,
    _76PIN_PIN_30_GPO_OD = 0x02,
    _76PIN_PIN_30_PWM1_PP = 0x03,
    _76PIN_PIN_30_PWM1_OD = 0x04,
    _76PIN_PIN_30_TCON7 = 0x05,
    _76PIN_PIN_30_TCON13 = 0x06,
    _76PIN_PIN_30_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_30_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_30_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_30_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_30_NC = _76PIN_PIN_30_GPO_PP,
} EnumPinshareInfo76PIN_PIN_30;

//---------------------------------------------------------------------------
// Function : EESCL
// Pinshare : 0x100D
// MCU Ctrl : 0xFFE3[5] at _76PIN_PIN_31_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_31                           (_76PIN_PIN_31_IICSCL1)

typedef enum
{
    _76PIN_PIN_31_GPI = 0x00,
    _76PIN_PIN_31_GPO_PP = 0x01,
    _76PIN_PIN_31_GPO_OD = 0x02,
    _76PIN_PIN_31_TCON8 = 0x03,
    _76PIN_PIN_31_TCON12 = 0x04,
    _76PIN_PIN_31_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_31_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_31_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_31_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_31_IICSCL1 = 0x40,
    _76PIN_PIN_31_IICSCL_AUX = 0x80,
    _76PIN_PIN_31_NC = _76PIN_PIN_31_GPO_PP,
} EnumPinshareInfo76PIN_PIN_31;

//---------------------------------------------------------------------------
// Function : EESDA
// Pinshare : 0x100E
// MCU Ctrl : 0xFFE3[6] at _76PIN_PIN_32_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_32                           (_76PIN_PIN_32_IICSDA1)

typedef enum
{
    _76PIN_PIN_32_GPI = 0x00,
    _76PIN_PIN_32_GPO_PP = 0x01,
    _76PIN_PIN_32_GPO_OD = 0x02,
    _76PIN_PIN_32_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_32_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_32_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_32_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_32_IICSDA1 = 0x40,
    _76PIN_PIN_32_IICSDA_AUX = 0x80,
    _76PIN_PIN_32_NC = _76PIN_PIN_32_GPO_PP,
} EnumPinshareInfo76PIN_PIN_32;

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_N1
// Pinshare : 0x100F
// MCU Ctrl : 0xFFE3[7] at _76PIN_PIN_33_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_33                           (_76PIN_PIN_33_GPI)

typedef enum
{
    _76PIN_PIN_33_GPI = 0x40,
    _76PIN_PIN_33_GPO_PP = 0x41,
    _76PIN_PIN_33_GPO_OD = 0x42,
    _76PIN_PIN_33_TEST4B_OUT0 = 0x4C,
    _76PIN_PIN_33_TEST4B_OUT1 = 0x4D,
    _76PIN_PIN_33_TEST4B_OUT2 = 0x4E,
    _76PIN_PIN_33_TEST4B_OUT3 = 0x4F,
    _76PIN_PIN_33_DDCSCLVGA0 = 0x00,
    _76PIN_PIN_33_DDCCSL_MUX_SWAP_PIN_43 = 0x20,
    _76PIN_PIN_33_RXD1 = 0x80,
    _76PIN_PIN_33_NC = _76PIN_PIN_33_GPO_PP,
} EnumPinshareInfo76PIN_PIN_33;

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_P1
// Pinshare : 0x1010
// MCU Ctrl : 0xFE00 at _76PIN_PIN_34_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_34                           (_76PIN_PIN_34_GPI)

typedef enum
{
    _76PIN_PIN_34_GPI = 0x00,
    _76PIN_PIN_34_GPO_PP = 0x01,
    _76PIN_PIN_34_GPO_OD = 0x02,
    _76PIN_PIN_34_TCON11 = 0x03,
    _76PIN_PIN_34_TCON13 = 0x04,
    _76PIN_PIN_34_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_34_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_34_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_34_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_34_DDCSDAVGA0 = 0x00,
    _76PIN_PIN_34_DDCSDA_MUX_SWAP_PIN_44 = 0x20,
    _76PIN_PIN_34_TXD1 = 0x80,
    _76PIN_PIN_34_NC = _76PIN_PIN_34_GPO_PP,
} EnumPinshareInfo76PIN_PIN_34;

//---------------------------------------------------------------------------
// Function : DP_HOT_PLUG
// Pinshare : 0x1012
// MCU Ctrl : 0xFE02 at _76PIN_PIN_36_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_36                           (_76PIN_PIN_36_GPO_PP)

typedef enum
{
    _76PIN_PIN_36_GPI = 0x00,
    _76PIN_PIN_36_GPO_PP = 0x01,
    _76PIN_PIN_36_GPO_OD = 0x02,
    _76PIN_PIN_36_PWM3_PP = 0x03,
    _76PIN_PIN_36_PWM3_OD = 0x04,
    _76PIN_PIN_36_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_36_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_36_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_36_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_36_NC = _76PIN_PIN_36_GPO_PP,
} EnumPinshareInfo76PIN_PIN_36;

//---------------------------------------------------------------------------
// Function : LED1
// Pinshare : 0x101A
// MCU Ctrl : 0xFE0A at _76PIN_PIN_37_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_37                           (_76PIN_PIN_37_GPO_PP)

typedef enum
{
    _76PIN_PIN_37_GPI = 0x00,
    _76PIN_PIN_37_GPO_PP = 0x01,
    _76PIN_PIN_37_GPO_OD = 0x02,
    _76PIN_PIN_37_PWM0_PP = 0x03,
    _76PIN_PIN_37_PWM0_OD = 0x04,
    _76PIN_PIN_37_PWM3_PP = 0x05,
    _76PIN_PIN_37_PWM3_OD = 0x06,
    _76PIN_PIN_37_TCON7 = 0x07,
    _76PIN_PIN_37_INT1 = 0x08,
    _76PIN_PIN_37_T2 = 0x09,
    _76PIN_PIN_37_IHS_AFTER_SCALING_DOWN = 0x0A,
    _76PIN_PIN_37_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_37_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_37_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_37_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_37_NC = _76PIN_PIN_37_GPO_PP,
} EnumPinshareInfo76PIN_PIN_37;

//---------------------------------------------------------------------------
// Function : LED5
// Pinshare : 0x101B
// MCU Ctrl : 0xFE0B at _76PIN_PIN_38_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_38                           (_76PIN_PIN_38_GPO_PP)

typedef enum
{
    _76PIN_PIN_38_GPI = 0x00,
    _76PIN_PIN_38_GPO_PP = 0x01,
    _76PIN_PIN_38_GPO_OD = 0x02,
    _76PIN_PIN_38_PWM2_PP = 0x03,
    _76PIN_PIN_38_PWM2_OD = 0x04,
    _76PIN_PIN_38_TCON8 = 0x05,
    _76PIN_PIN_38_INT0 = 0x06,
    _76PIN_PIN_38_IENA_AFTER_SCALING_DOWN = 0x08,
    _76PIN_PIN_38_CLKO = 0x09,
    _76PIN_PIN_38_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_38_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_38_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_38_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_38_NC = _76PIN_PIN_38_GPO_PP,
} EnumPinshareInfo76PIN_PIN_38;

//---------------------------------------------------------------------------
// Function : TXD3P
// Pinshare : 0x101D
// MCU Ctrl : 0xFE0D at _76PIN_PIN_39_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_39_OFF_REGION                (_76PIN_PIN_39_TXO3P_8B)

typedef enum
{
    _76PIN_PIN_39_HI_Z = 0x00,
    _76PIN_PIN_39_GPI = 0x01,
    _76PIN_PIN_39_GPO_PP = 0x02,
    _76PIN_PIN_39_GPO_OD = 0x03,
    _76PIN_PIN_39_TXO3P_8B = 0x04,
    _76PIN_PIN_39_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_39_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_39_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_39_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_39_NC = _76PIN_PIN_39_GPO_PP,
} EnumPinshareInfo76PIN_PIN_39;

//---------------------------------------------------------------------------
// Function : TXD3N
// Pinshare : 0x101E
// MCU Ctrl : 0xFE0E at _76PIN_PIN_40_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_40_OFF_REGION                (_76PIN_PIN_40_TXO3N_8B)

typedef enum
{
    _76PIN_PIN_40_HI_Z = 0x00,
    _76PIN_PIN_40_GPI = 0x01,
    _76PIN_PIN_40_GPO_PP = 0x02,
    _76PIN_PIN_40_GPO_OD = 0x03,
    _76PIN_PIN_40_TXO3N_8B = 0x04,
    _76PIN_PIN_40_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_40_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_40_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_40_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_40_NC = _76PIN_PIN_40_GPO_PP,
} EnumPinshareInfo76PIN_PIN_40;

//---------------------------------------------------------------------------
// Function : TXD2P
// Pinshare : 0x101F
// MCU Ctrl : 0xFE0F at _76PIN_PIN_41_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_41_OFF_REGION                (_76PIN_PIN_41_TXO2P_8B)

typedef enum
{
    _76PIN_PIN_41_HI_Z = 0x00,
    _76PIN_PIN_41_GPI = 0x01,
    _76PIN_PIN_41_GPO_PP = 0x02,
    _76PIN_PIN_41_GPO_OD = 0x03,
    _76PIN_PIN_41_TXO2P_8B = 0x04,
    _76PIN_PIN_41_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_41_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_41_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_41_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_41_NC = _76PIN_PIN_41_GPO_PP,
} EnumPinshareInfo76PIN_PIN_41;

//---------------------------------------------------------------------------
// Function : TXD2N
// Pinshare : 0x1020
// MCU Ctrl : 0xFE10 at _76PIN_PIN_42_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_42_OFF_REGION                (_76PIN_PIN_42_TXO2N_8B)

typedef enum
{
    _76PIN_PIN_42_HI_Z = 0x00,
    _76PIN_PIN_42_GPI = 0x01,
    _76PIN_PIN_42_GPO_PP = 0x02,
    _76PIN_PIN_42_GPO_OD = 0x03,
    _76PIN_PIN_42_TXO2N_8B = 0x04,
    _76PIN_PIN_42_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_42_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_42_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_42_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_42_NC = _76PIN_PIN_42_GPO_PP,
} EnumPinshareInfo76PIN_PIN_42;

//---------------------------------------------------------------------------
// Function : TXD1P
// Pinshare : 0x1021
// MCU Ctrl : 0xFE11 at _76PIN_PIN_43_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_43_OFF_REGION                (_76PIN_PIN_43_TXO1P_8B)

typedef enum
{
    _76PIN_PIN_43_HI_Z = 0x00,
    _76PIN_PIN_43_GPI = 0x01,
    _76PIN_PIN_43_GPO_PP = 0x02,
    _76PIN_PIN_43_GPO_OD = 0x03,
    _76PIN_PIN_43_TXO1P_8B = 0x04,
    _76PIN_PIN_43_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_43_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_43_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_43_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_43_NC = _76PIN_PIN_43_GPO_PP,
} EnumPinshareInfo76PIN_PIN_43;

//---------------------------------------------------------------------------
// Function : TXD1N
// Pinshare : 0x1022
// MCU Ctrl : 0xFE12 at _76PIN_PIN_44_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_44_OFF_REGION                (_76PIN_PIN_44_TXO1N_8B)

typedef enum
{
    _76PIN_PIN_44_HI_Z = 0x00,
    _76PIN_PIN_44_GPI = 0x01,
    _76PIN_PIN_44_GPO_PP = 0x02,
    _76PIN_PIN_44_GPO_OD = 0x03,
    _76PIN_PIN_44_TXO1N_8B = 0x04,
    _76PIN_PIN_44_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_44_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_44_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_44_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_44_NC = _76PIN_PIN_44_GPO_PP,
} EnumPinshareInfo76PIN_PIN_44;

//---------------------------------------------------------------------------
// Function : TXD0P
// Pinshare : 0x1023
// MCU Ctrl : 0xFE13 at _76PIN_PIN_45_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_45_OFF_REGION                (_76PIN_PIN_45_TXO0P_8B)

typedef enum
{
    _76PIN_PIN_45_HI_Z = 0x00,
    _76PIN_PIN_45_GPI = 0x01,
    _76PIN_PIN_45_GPO_PP = 0x02,
    _76PIN_PIN_45_GPO_OD = 0x03,
    _76PIN_PIN_45_TXO0P_8B = 0x04,
    _76PIN_PIN_45_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_45_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_45_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_45_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_45_NC = _76PIN_PIN_45_GPO_PP,
} EnumPinshareInfo76PIN_PIN_45;

//---------------------------------------------------------------------------
// Function : TXD0N
// Pinshare : 0x1024
// MCU Ctrl : 0xFE14 at _76PIN_PIN_46_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_46_OFF_REGION                (_76PIN_PIN_46_TXO0N_8B)

typedef enum
{
    _76PIN_PIN_46_HI_Z = 0x00,
    _76PIN_PIN_46_GPI = 0x01,
    _76PIN_PIN_46_GPO_PP = 0x02,
    _76PIN_PIN_46_GPO_OD = 0x03,
    _76PIN_PIN_46_TXO0N_8B = 0x04,
    _76PIN_PIN_46_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_46_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_46_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_46_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_46_NC = _76PIN_PIN_46_GPO_PP,
} EnumPinshareInfo76PIN_PIN_46;

//---------------------------------------------------------------------------
// Function : FLASH_WP
// Pinshare : 0x102A
// MCU Ctrl : 0xFE1A at _76PIN_PIN_58_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_58                           (_76PIN_PIN_58_GPO_OD)

typedef enum
{
    _76PIN_PIN_58_GPI = 0x00,
    _76PIN_PIN_58_GPO_PP = 0x01,
    _76PIN_PIN_58_GPO_OD = 0x02,
    _76PIN_PIN_58_INT0 = 0x03,
    _76PIN_PIN_58_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_58_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_58_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_58_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_58_NC = _76PIN_PIN_58_GPO_PP,
} EnumPinshareInfo76PIN_PIN_58;

//---------------------------------------------------------------------------
// Function : Panel_ON
// Pinshare : 0x102B
// MCU Ctrl : 0xFE1B at _76PIN_PIN_59_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_59                           (_76PIN_PIN_59_GPO_PP)

typedef enum
{
    _76PIN_PIN_59_GPI = 0x00,
    _76PIN_PIN_59_GPO_PP = 0x01,
    _76PIN_PIN_59_GPO_OD = 0x02,
    _76PIN_PIN_59_INT1 = 0x03,
    _76PIN_PIN_59_TCON11 = 0x04,
    _76PIN_PIN_59_IVS_AFTER_SCALING_DOWN = 0x06,
    _76PIN_PIN_59_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_59_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_59_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_59_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_59_NC = _76PIN_PIN_59_GPO_PP,
} EnumPinshareInfo76PIN_PIN_59;

//---------------------------------------------------------------------------
// Function : LED2
// Pinshare : 0x102C
// MCU Ctrl : 0xFE1C at _76PIN_PIN_60_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_60                           (_76PIN_PIN_60_GPO_PP)

typedef enum
{
    _76PIN_PIN_60_GPI = 0x00,
    _76PIN_PIN_60_GPO_PP = 0x01,
    _76PIN_PIN_60_GPO_OD = 0x02,
    _76PIN_PIN_60_T0 = 0x03,
    _76PIN_PIN_60_DENA = 0x04,
    _76PIN_PIN_60_TCON9 = 0x05,
    _76PIN_PIN_60_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_60_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_60_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_60_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_60_NC = _76PIN_PIN_60_GPO_PP,
} EnumPinshareInfo76PIN_PIN_60;

//---------------------------------------------------------------------------
// Function : LED3
// Pinshare : 0x102D
// MCU Ctrl : 0xFE1D at _76PIN_PIN_61_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_61                           (_76PIN_PIN_61_GPO_PP)

typedef enum
{
    _76PIN_PIN_61_GPI = 0x00,
    _76PIN_PIN_61_GPO_PP = 0x01,
    _76PIN_PIN_61_GPO_OD = 0x02,
    _76PIN_PIN_61_PWM2_PP = 0x03,
    _76PIN_PIN_61_PWM2_OD = 0x04,
    _76PIN_PIN_61_PWM3_PP = 0x05,
    _76PIN_PIN_61_PWM3_OD = 0x06,
    _76PIN_PIN_61_T1 = 0x07,
    _76PIN_PIN_61_DHS = 0x08,
    _76PIN_PIN_61_TCON13 = 0x09,
    _76PIN_PIN_61_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_61_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_61_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_61_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_61_NC = _76PIN_PIN_61_GPO_PP,
} EnumPinshareInfo76PIN_PIN_61;

//---------------------------------------------------------------------------
// Function : DDCSCL_VGA
// Pinshare : 0x102E
// MCU Ctrl : 0xFE1E at _76PIN_PIN_62_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_62                           (_76PIN_PIN_62_DDCSCLVGA1)

typedef enum
{
    _76PIN_PIN_62_GPI = 0x80,
    _76PIN_PIN_62_GPO_PP = 0x81,
    _76PIN_PIN_62_GPO_OD = 0x82,
    _76PIN_PIN_62_AUX_D2 = 0x83,
    _76PIN_PIN_62_DCLK = 0x84,
    _76PIN_PIN_62_TCON8 = 0x85,
    _76PIN_PIN_62_PWM_IN = 0x86,
    _76PIN_PIN_62_T2EX = 0x87,
    _76PIN_PIN_62_TEST4B_OUT0 = 0x8C,
    _76PIN_PIN_62_TEST4B_OUT1 = 0x8D,
    _76PIN_PIN_62_TEST4B_OUT2 = 0x8E,
    _76PIN_PIN_62_TEST4B_OUT3 = 0x8F,
    _76PIN_PIN_62_DDCSCLVGA1 = 0x00,
    _76PIN_PIN_62_NC = _76PIN_PIN_62_GPO_PP,
} EnumPinshareInfo76PIN_PIN_62;

//---------------------------------------------------------------------------
// Function : DDCSDA_VGA
// Pinshare : 0x102F
// MCU Ctrl : 0xFE1F at _76PIN_PIN_63_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_63                           (_76PIN_PIN_63_DDCSDAVGA1)

typedef enum
{
    _76PIN_PIN_63_GPI = 0x00,
    _76PIN_PIN_63_GPO_PP = 0x01,
    _76PIN_PIN_63_GPO_OD = 0x02,
    _76PIN_PIN_63_AUX_D1 = 0x03,
    _76PIN_PIN_63_DVS = 0x04,
    _76PIN_PIN_63_TCON7 = 0x05,
    _76PIN_PIN_63_PWM_OUT = 0x06,
    _76PIN_PIN_63_PWM1_PP = 0x07,
    _76PIN_PIN_63_PWM1_OD = 0x08,
    _76PIN_PIN_63_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_63_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_63_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_63_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_63_DDCSDAVGA1 = 0x00,
    _76PIN_PIN_63_NC = _76PIN_PIN_63_GPO_PP,
} EnumPinshareInfo76PIN_PIN_63;

//---------------------------------------------------------------------------
// Function : AUX_CHP
// Pinshare : 0x1034
// MCU Ctrl : 0xFE24 at _76PIN_PIN_70_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_70                           (_76PIN_PIN_70_AUXP1)

typedef enum
{
    _76PIN_PIN_70_GPI = 0x80,
    _76PIN_PIN_70_GPO_PP = 0x81,
    _76PIN_PIN_70_GPO_OD = 0x82,
    _76PIN_PIN_70_AUXP1 = 0x83,
    _76PIN_PIN_70_TEST4B_OUT0 = 0x8C,
    _76PIN_PIN_70_TEST4B_OUT1 = 0x8D,
    _76PIN_PIN_70_TEST4B_OUT2 = 0x8E,
    _76PIN_PIN_70_TEST4B_OUT3 = 0x8F,
    _76PIN_PIN_70_DDCSCL1 = 0x00,
    _76PIN_PIN_70_NC = _76PIN_PIN_70_GPO_PP,
} EnumPinshareInfo76PIN_PIN_70;

//---------------------------------------------------------------------------
// Function : AUX_CHN
// Pinshare : 0x1035
// MCU Ctrl : 0xFE25 at _76PIN_PIN_71_MCU_REG
//---------------------------------------------------------------------------
#define _76PIN_PIN_71                           (_76PIN_PIN_71_AUXN1)

typedef enum
{
    _76PIN_PIN_71_GPI = 0x00,
    _76PIN_PIN_71_GPO_PP = 0x01,
    _76PIN_PIN_71_GPO_OD = 0x02,
    _76PIN_PIN_71_AUXN1 = 0x03,
    _76PIN_PIN_71_TEST4B_OUT0 = 0x0C,
    _76PIN_PIN_71_TEST4B_OUT1 = 0x0D,
    _76PIN_PIN_71_TEST4B_OUT2 = 0x0E,
    _76PIN_PIN_71_TEST4B_OUT3 = 0x0F,
    _76PIN_PIN_71_DDCSDA1 = 0x00,
    _76PIN_PIN_71_NC = _76PIN_PIN_71_GPO_PP,
} EnumPinshareInfo76PIN_PIN_71;
