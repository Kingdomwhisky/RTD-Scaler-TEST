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
// ID Code      : RL6463_Series_Pin_Mapping.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef _PCB_NEW_MODE_SUPPORT
#define _PCB_NEW_MODE_SUPPORT                   _OFF
#endif

#ifdef _76PIN_PIN_21
#define _PCB_PINSHARE_MAPPING                   _ON
#else
#define _PCB_PINSHARE_MAPPING                   _OFF
#endif

////////////////////
// Pinshare enums //
////////////////////
#if((_PCB_NEW_MODE_SUPPORT == _OFF) || (_PCB_PINSHARE_MAPPING == _ON))
//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1000
// MCU Ctrl : 0xFFE2[0] at _PIN_21_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_21_GPI = 0x00,
    _PIN_21_GPO_PP = 0x01,
    _PIN_21_GPO_OD = 0x02,
    _PIN_21_TEST4B_OUT0 = 0x0C,
    _PIN_21_TEST4B_OUT1 = 0x0D,
    _PIN_21_TEST4B_OUT2 = 0x0E,
    _PIN_21_TEST4B_OUT3 = 0x0F,
    _PIN_21_NC = _PIN_21_GPO_PP,
} EnumPinshareInfoPIN21;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1001
// MCU Ctrl : 0xFFE2[1] at _PIN_22_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_22_GPI = 0x00,
    _PIN_22_GPO_PP = 0x01,
    _PIN_22_GPO_OD = 0x02,
    _PIN_22_TEST4B_OUT0 = 0x0C,
    _PIN_22_TEST4B_OUT1 = 0x0D,
    _PIN_22_TEST4B_OUT2 = 0x0E,
    _PIN_22_TEST4B_OUT3 = 0x0F,
    _PIN_22_NC = _PIN_22_GPO_PP,
} EnumPinshareInfoPIN22;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1002
// MCU Ctrl : 0xFFE2[2] at _PIN_34_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_34_GPI = 0x00,
    _PIN_34_GPO_PP = 0x01,
    _PIN_34_GPO_OD = 0x02,
    _PIN_34_PWM0_PP = 0x03,
    _PIN_34_PWM0_OD = 0x04,
    _PIN_34_MCK = 0x05,
    _PIN_34_CLKO = 0x06,
    _PIN_34_TEST4B_OUT0 = 0x0C,
    _PIN_34_TEST4B_OUT1 = 0x0D,
    _PIN_34_TEST4B_OUT2 = 0x0E,
    _PIN_34_TEST4B_OUT3 = 0x0F,
    _PIN_34_NC = _PIN_34_GPO_PP,
} EnumPinshareInfoPIN34;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1003
// MCU Ctrl : 0xFFE2[3] at _PIN_35_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_35_GPI = 0x00,
    _PIN_35_GPO_PP = 0x01,
    _PIN_35_GPO_OD = 0x02,
    _PIN_35_PWM1_PP = 0x03,
    _PIN_35_PWM1_OD = 0x04,
    _PIN_35_SCK = 0x05,
    _PIN_35_IRQB = 0x06,
    _PIN_35_TCON13 = 0x07,
    _PIN_35_TEST4B_OUT0 = 0x0C,
    _PIN_35_TEST4B_OUT1 = 0x0D,
    _PIN_35_TEST4B_OUT2 = 0x0E,
    _PIN_35_TEST4B_OUT3 = 0x0F,
    _PIN_35_NC = _PIN_35_GPO_PP,
} EnumPinshareInfoPIN35;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1004
// MCU Ctrl : 0xFFE2[4] at _PIN_36_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_36_GPI = 0x00,
    _PIN_36_GPO_PP = 0x01,
    _PIN_36_GPO_OD = 0x02,
    _PIN_36_PWM2_PP = 0x03,
    _PIN_36_PWM2_OD = 0x04,
    _PIN_36_WS = 0x05,
    _PIN_36_TCON13 = 0x06,
    _PIN_36_TEST4B_OUT0 = 0x0C,
    _PIN_36_TEST4B_OUT1 = 0x0D,
    _PIN_36_TEST4B_OUT2 = 0x0E,
    _PIN_36_TEST4B_OUT3 = 0x0F,
    _PIN_36_NC = _PIN_36_GPO_PP,
} EnumPinshareInfoPIN36;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1005
// MCU Ctrl : 0xFFE2[5] at _PIN_37_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_37_GPI = 0x00,
    _PIN_37_GPO_PP = 0x01,
    _PIN_37_GPO_OD = 0x02,
    _PIN_37_PWM3_PP = 0x03,
    _PIN_37_PWM3_OD = 0x04,
    _PIN_37_SD0 = 0x05,
    _PIN_37_SPDIF0 = 0x06,
    _PIN_37_TEST4B_OUT0 = 0x0C,
    _PIN_37_TEST4B_OUT1 = 0x0D,
    _PIN_37_TEST4B_OUT2 = 0x0E,
    _PIN_37_TEST4B_OUT3 = 0x0F,
    _PIN_37_IICSCL0 = 0x40,
    _PIN_37_RXD0 = 0x80,
    _PIN_37_NC = _PIN_37_GPO_PP,
} EnumPinshareInfoPIN37;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1006
// MCU Ctrl : 0xFFE2[6] at _PIN_38_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_38_GPI = 0x00,
    _PIN_38_GPO_PP = 0x01,
    _PIN_38_GPO_OD = 0x02,
    _PIN_38_TEST4B_OUT0 = 0x0C,
    _PIN_38_TEST4B_OUT1 = 0x0D,
    _PIN_38_TEST4B_OUT2 = 0x0E,
    _PIN_38_TEST4B_OUT3 = 0x0F,
    _PIN_38_IICSDA0 = 0x40,
    _PIN_38_TXD0 = 0x80,
    _PIN_38_NC = _PIN_38_GPO_PP,
} EnumPinshareInfoPIN38;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1007
// MCU Ctrl : 0xFFE2[7] at _PIN_39_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_39_GPI = 0x00,
    _PIN_39_GPO_PP = 0x01,
    _PIN_39_GPO_OD = 0x02,
    _PIN_39_TEST4B_OUT0 = 0x0C,
    _PIN_39_TEST4B_OUT1 = 0x0D,
    _PIN_39_TEST4B_OUT2 = 0x0E,
    _PIN_39_TEST4B_OUT3 = 0x0F,
    _PIN_39_NC = _PIN_39_GPO_PP,
} EnumPinshareInfoPIN39;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1008
// MCU Ctrl : 0xFFE3[0] at _PIN_42_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_42_GPI = 0x00,
    _PIN_42_GPO_PP = 0x01,
    _PIN_42_GPO_OD = 0x02,
    _PIN_42_A_ADC0 = 0x03,
    _PIN_42_TEST4B_OUT0 = 0x0C,
    _PIN_42_TEST4B_OUT1 = 0x0D,
    _PIN_42_TEST4B_OUT2 = 0x0E,
    _PIN_42_TEST4B_OUT3 = 0x0F,
    _PIN_42_NC = _PIN_42_GPO_PP,
} EnumPinshareInfoPIN42;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1009
// MCU Ctrl : 0xFFE3[1] at _PIN_43_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_43_GPI = 0x00,
    _PIN_43_GPO_PP = 0x01,
    _PIN_43_GPO_OD = 0x02,
    _PIN_43_A_ADC1 = 0x03,
    _PIN_43_TEST4B_OUT0 = 0x0C,
    _PIN_43_TEST4B_OUT1 = 0x0D,
    _PIN_43_TEST4B_OUT2 = 0x0E,
    _PIN_43_TEST4B_OUT3 = 0x0F,
    _PIN_43_NC = _PIN_43_GPO_PP,
} EnumPinshareInfoPIN43;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100A
// MCU Ctrl : 0xFFE3[2] at _PIN_44_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_44_GPI = 0x00,
    _PIN_44_GPO_PP = 0x01,
    _PIN_44_GPO_OD = 0x02,
    _PIN_44_A_ADC2 = 0x03,
    _PIN_44_TEST4B_OUT0 = 0x0C,
    _PIN_44_TEST4B_OUT1 = 0x0D,
    _PIN_44_TEST4B_OUT2 = 0x0E,
    _PIN_44_TEST4B_OUT3 = 0x0F,
    _PIN_44_NC = _PIN_44_GPO_PP,
} EnumPinshareInfoPIN44;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100B
// MCU Ctrl : 0xFFE3[3] at _PIN_45_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_45_GPI = 0x00,
    _PIN_45_GPO_PP = 0x01,
    _PIN_45_GPO_OD = 0x02,
    _PIN_45_A_ADC3 = 0x03,
    _PIN_45_TEST4B_OUT0 = 0x0C,
    _PIN_45_TEST4B_OUT1 = 0x0D,
    _PIN_45_TEST4B_OUT2 = 0x0E,
    _PIN_45_TEST4B_OUT3 = 0x0F,
    _PIN_45_NC = _PIN_45_GPO_PP,
} EnumPinshareInfoPIN45;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100C
// MCU Ctrl : 0xFFE3[4] at _PIN_46_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_46_GPI = 0x00,
    _PIN_46_GPO_PP = 0x01,
    _PIN_46_GPO_OD = 0x02,
    _PIN_46_PWM1_PP = 0x03,
    _PIN_46_PWM1_OD = 0x04,
    _PIN_46_TCON7 = 0x05,
    _PIN_46_TCON13 = 0x06,
    _PIN_46_TEST4B_OUT0 = 0x0C,
    _PIN_46_TEST4B_OUT1 = 0x0D,
    _PIN_46_TEST4B_OUT2 = 0x0E,
    _PIN_46_TEST4B_OUT3 = 0x0F,
    _PIN_46_NC = _PIN_46_GPO_PP,
} EnumPinshareInfoPIN46;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100D
// MCU Ctrl : 0xFFE3[5] at _PIN_47_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_47_GPI = 0x00,
    _PIN_47_GPO_PP = 0x01,
    _PIN_47_GPO_OD = 0x02,
    _PIN_47_TCON8 = 0x03,
    _PIN_47_TCON12 = 0x04,
    _PIN_47_TEST4B_OUT0 = 0x0C,
    _PIN_47_TEST4B_OUT1 = 0x0D,
    _PIN_47_TEST4B_OUT2 = 0x0E,
    _PIN_47_TEST4B_OUT3 = 0x0F,
    _PIN_47_IICSCL1 = 0x40,
    _PIN_47_IICSCL_AUX = 0x80,
    _PIN_47_NC = _PIN_47_GPO_PP,
} EnumPinshareInfoPIN47;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100E
// MCU Ctrl : 0xFFE3[6] at _PIN_48_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_48_GPI = 0x00,
    _PIN_48_GPO_PP = 0x01,
    _PIN_48_GPO_OD = 0x02,
    _PIN_48_TEST4B_OUT0 = 0x0C,
    _PIN_48_TEST4B_OUT1 = 0x0D,
    _PIN_48_TEST4B_OUT2 = 0x0E,
    _PIN_48_TEST4B_OUT3 = 0x0F,
    _PIN_48_IICSDA1 = 0x40,
    _PIN_48_IICSDA_AUX = 0x80,
    _PIN_48_NC = _PIN_48_GPO_PP,
} EnumPinshareInfoPIN48;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100F
// MCU Ctrl : 0xFFE3[7] at _PIN_49_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_49_GPI = 0x40,
    _PIN_49_GPO_PP = 0x41,
    _PIN_49_GPO_OD = 0x42,
    _PIN_49_TEST4B_OUT0 = 0x4C,
    _PIN_49_TEST4B_OUT1 = 0x4D,
    _PIN_49_TEST4B_OUT2 = 0x4E,
    _PIN_49_TEST4B_OUT3 = 0x4F,
    _PIN_49_DDCSCLVGA0 = 0x00,
    _PIN_49_DDCCSL_MUX_SWAP_PIN_43 = 0x20,
    _PIN_49_RXD1 = 0x80,
    _PIN_49_NC = _PIN_49_GPO_PP,
} EnumPinshareInfoPIN49;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1010
// MCU Ctrl : 0xFE00 at _PIN_50_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_50_GPI = 0x00,
    _PIN_50_GPO_PP = 0x01,
    _PIN_50_GPO_OD = 0x02,
    _PIN_50_TCON11 = 0x03,
    _PIN_50_TCON13 = 0x04,
    _PIN_50_TEST4B_OUT0 = 0x0C,
    _PIN_50_TEST4B_OUT1 = 0x0D,
    _PIN_50_TEST4B_OUT2 = 0x0E,
    _PIN_50_TEST4B_OUT3 = 0x0F,
    _PIN_50_DDCSDAVGA0 = 0x00,
    _PIN_50_DDCSDA_MUX_SWAP_PIN_44 = 0x20,
    _PIN_50_TXD1 = 0x80,
    _PIN_50_NC = _PIN_50_GPO_PP,
} EnumPinshareInfoPIN50;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1011
// MCU Ctrl : 0xFE01 at _PIN_52_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_52_GPI = 0x00,
    _PIN_52_GPO_PP = 0x01,
    _PIN_52_GPO_OD = 0x02,
    _PIN_52_PWM0_PP = 0x03,
    _PIN_52_PWM0_OD = 0x04,
    _PIN_52_TEST4B_OUT0 = 0x0C,
    _PIN_52_TEST4B_OUT1 = 0x0D,
    _PIN_52_TEST4B_OUT2 = 0x0E,
    _PIN_52_TEST4B_OUT3 = 0x0F,
    _PIN_52_NC = _PIN_52_GPO_PP,
} EnumPinshareInfoPIN52;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1012
// MCU Ctrl : 0xFE02 at _PIN_53_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_53_GPI = 0x00,
    _PIN_53_GPO_PP = 0x01,
    _PIN_53_GPO_OD = 0x02,
    _PIN_53_PWM3_PP = 0x03,
    _PIN_53_PWM3_OD = 0x04,
    _PIN_53_TEST4B_OUT0 = 0x0C,
    _PIN_53_TEST4B_OUT1 = 0x0D,
    _PIN_53_TEST4B_OUT2 = 0x0E,
    _PIN_53_TEST4B_OUT3 = 0x0F,
    _PIN_53_NC = _PIN_53_GPO_PP,
} EnumPinshareInfoPIN53;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1013
// MCU Ctrl : 0xFE03 at _PIN_55_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_55_GPI = 0x00,
    _PIN_55_GPO_PP = 0x01,
    _PIN_55_GPO_OD = 0x02,
    _PIN_55_PWM0_PP = 0x03,
    _PIN_55_PWM0_OD = 0x04,
    _PIN_55_MCK = 0x05,
    _PIN_55_LINE_INL = 0x06,
    _PIN_55_TEST4B_OUT0 = 0x0C,
    _PIN_55_TEST4B_OUT1 = 0x0D,
    _PIN_55_TEST4B_OUT2 = 0x0E,
    _PIN_55_TEST4B_OUT3 = 0x0F,
    _PIN_55_NC = _PIN_55_GPO_PP,
} EnumPinshareInfoPIN55;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1014
// MCU Ctrl : 0xFE04 at _PIN_56_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_56_GPI = 0x00,
    _PIN_56_GPO_PP = 0x01,
    _PIN_56_GPO_OD = 0x02,
    _PIN_56_SCK = 0x03,
    _PIN_56_LINE_INR = 0x04,
    _PIN_56_TEST4B_OUT0 = 0x0C,
    _PIN_56_TEST4B_OUT1 = 0x0D,
    _PIN_56_TEST4B_OUT2 = 0x0E,
    _PIN_56_TEST4B_OUT3 = 0x0F,
    _PIN_56_NC = _PIN_56_GPO_PP,
} EnumPinshareInfoPIN56;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1015
// MCU Ctrl : 0xFE05 at _PIN_57_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_57_GPI = 0x00,
    _PIN_57_GPO_PP = 0x01,
    _PIN_57_GPO_OD = 0x02,
    _PIN_57_WS = 0x03,
    _PIN_57_AUDIO_REF = 0x04,
    _PIN_57_TCON13 = 0x05,
    _PIN_57_TEST4B_OUT0 = 0x0C,
    _PIN_57_TEST4B_OUT1 = 0x0D,
    _PIN_57_TEST4B_OUT2 = 0x0E,
    _PIN_57_TEST4B_OUT3 = 0x0F,
    _PIN_57_NC = _PIN_57_GPO_PP,
} EnumPinshareInfoPIN57;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1016
// MCU Ctrl : 0xFE06 at _PIN_58_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_58_GPI = 0x00,
    _PIN_58_GPO_PP = 0x01,
    _PIN_58_GPO_OD = 0x02,
    _PIN_58_SD0 = 0x03,
    _PIN_58_SPDIF0 = 0x04,
    _PIN_58_SOUTL = 0x05,
    _PIN_58_TEST4B_OUT0 = 0x0C,
    _PIN_58_TEST4B_OUT1 = 0x0D,
    _PIN_58_TEST4B_OUT2 = 0x0E,
    _PIN_58_TEST4B_OUT3 = 0x0F,
    _PIN_58_NC = _PIN_58_GPO_PP,
} EnumPinshareInfoPIN58;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1017
// MCU Ctrl : 0xFE07 at _PIN_59_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_59_GPI = 0x00,
    _PIN_59_GPO_PP = 0x01,
    _PIN_59_GPO_OD = 0x02,
    _PIN_59_SOUTR = 0x03,
    _PIN_59_TEST4B_OUT0 = 0x0C,
    _PIN_59_TEST4B_OUT1 = 0x0D,
    _PIN_59_TEST4B_OUT2 = 0x0E,
    _PIN_59_TEST4B_OUT3 = 0x0F,
    _PIN_59_NC = _PIN_59_GPO_PP,
} EnumPinshareInfoPIN59;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1018
// MCU Ctrl : 0xFE08 at _PIN_60_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_60_GPI = 0x00,
    _PIN_60_GPO_PP = 0x01,
    _PIN_60_GPO_OD = 0x02,
    _PIN_60_HOUTL = 0x03,
    _PIN_60_TEST4B_OUT0 = 0x0C,
    _PIN_60_TEST4B_OUT1 = 0x0D,
    _PIN_60_TEST4B_OUT2 = 0x0E,
    _PIN_60_TEST4B_OUT3 = 0x0F,
    _PIN_60_IICSCL2 = 0x40,
    _PIN_60_RXD2 = 0x80,
    _PIN_60_NC = _PIN_60_GPO_PP,
} EnumPinshareInfoPIN60;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1019
// MCU Ctrl : 0xFE09 at _PIN_61_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_61_GPI = 0x00,
    _PIN_61_GPO_PP = 0x01,
    _PIN_61_GPO_OD = 0x02,
    _PIN_61_HOUTR = 0x03,
    _PIN_61_TEST4B_OUT0 = 0x0C,
    _PIN_61_TEST4B_OUT1 = 0x0D,
    _PIN_61_TEST4B_OUT2 = 0x0E,
    _PIN_61_TEST4B_OUT3 = 0x0F,
    _PIN_61_IICSDA2 = 0x40,
    _PIN_61_TXD2 = 0x80,
    _PIN_61_NC = _PIN_61_GPO_PP,
} EnumPinshareInfoPIN61;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101A
// MCU Ctrl : 0xFE0A at _PIN_63_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_63_GPI = 0x00,
    _PIN_63_GPO_PP = 0x01,
    _PIN_63_GPO_OD = 0x02,
    _PIN_63_PWM0_PP = 0x03,
    _PIN_63_PWM0_OD = 0x04,
    _PIN_63_PWM3_PP = 0x05,
    _PIN_63_PWM3_OD = 0x06,
    _PIN_63_TCON7 = 0x07,
    _PIN_63_INT1 = 0x08,
    _PIN_63_T2 = 0x09,
    _PIN_63_IHS_AFTER_SCALING_DOWN = 0x0A,
    _PIN_63_TEST4B_OUT0 = 0x0C,
    _PIN_63_TEST4B_OUT1 = 0x0D,
    _PIN_63_TEST4B_OUT2 = 0x0E,
    _PIN_63_TEST4B_OUT3 = 0x0F,
    _PIN_63_NC = _PIN_63_GPO_PP,
} EnumPinshareInfoPIN63;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101B
// MCU Ctrl : 0xFE0B at _PIN_64_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_64_GPI = 0x00,
    _PIN_64_GPO_PP = 0x01,
    _PIN_64_GPO_OD = 0x02,
    _PIN_64_PWM2_PP = 0x03,
    _PIN_64_PWM2_OD = 0x04,
    _PIN_64_TCON8 = 0x05,
    _PIN_64_INT0 = 0x06,
    _PIN_64_IENA_AFTER_SCALING_DOWN = 0x08,
    _PIN_64_CLKO = 0x09,
    _PIN_64_TEST4B_OUT0 = 0x0C,
    _PIN_64_TEST4B_OUT1 = 0x0D,
    _PIN_64_TEST4B_OUT2 = 0x0E,
    _PIN_64_TEST4B_OUT3 = 0x0F,
    _PIN_64_NC = _PIN_64_GPO_PP,
} EnumPinshareInfoPIN64;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101C
// MCU Ctrl : 0xFE0C at _PIN_65_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_65_GPI = 0x00,
    _PIN_65_GPO_PP = 0x01,
    _PIN_65_GPO_OD = 0x02,
    _PIN_65_TEST4B_OUT0 = 0x0C,
    _PIN_65_TEST4B_OUT1 = 0x0D,
    _PIN_65_TEST4B_OUT2 = 0x0E,
    _PIN_65_TEST4B_OUT3 = 0x0F,
    _PIN_65_NC = _PIN_65_GPO_PP,
} EnumPinshareInfoPIN65;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101D
// MCU Ctrl : 0xFE0D at _PIN_67_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_67_HI_Z = 0x00,
    _PIN_67_GPI = 0x01,
    _PIN_67_GPO_PP = 0x02,
    _PIN_67_GPO_OD = 0x03,
    _PIN_67_TXO3P_8B = 0x04,
    _PIN_67_TEST4B_OUT0 = 0x0C,
    _PIN_67_TEST4B_OUT1 = 0x0D,
    _PIN_67_TEST4B_OUT2 = 0x0E,
    _PIN_67_TEST4B_OUT3 = 0x0F,
    _PIN_67_NC = _PIN_67_GPO_PP,
} EnumPinshareInfoPIN67;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101E
// MCU Ctrl : 0xFE0E at _PIN_68_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_68_HI_Z = 0x00,
    _PIN_68_GPI = 0x01,
    _PIN_68_GPO_PP = 0x02,
    _PIN_68_GPO_OD = 0x03,
    _PIN_68_TXO3N_8B = 0x04,
    _PIN_68_TEST4B_OUT0 = 0x0C,
    _PIN_68_TEST4B_OUT1 = 0x0D,
    _PIN_68_TEST4B_OUT2 = 0x0E,
    _PIN_68_TEST4B_OUT3 = 0x0F,
    _PIN_68_NC = _PIN_68_GPO_PP,
} EnumPinshareInfoPIN68;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101F
// MCU Ctrl : 0xFE0F at _PIN_69_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_69_HI_Z = 0x00,
    _PIN_69_GPI = 0x01,
    _PIN_69_GPO_PP = 0x02,
    _PIN_69_GPO_OD = 0x03,
    _PIN_69_TXO2P_8B = 0x04,
    _PIN_69_TEST4B_OUT0 = 0x0C,
    _PIN_69_TEST4B_OUT1 = 0x0D,
    _PIN_69_TEST4B_OUT2 = 0x0E,
    _PIN_69_TEST4B_OUT3 = 0x0F,
    _PIN_69_NC = _PIN_69_GPO_PP,
} EnumPinshareInfoPIN69;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1020
// MCU Ctrl : 0xFE10 at _PIN_70_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_70_HI_Z = 0x00,
    _PIN_70_GPI = 0x01,
    _PIN_70_GPO_PP = 0x02,
    _PIN_70_GPO_OD = 0x03,
    _PIN_70_TXO2N_8B = 0x04,
    _PIN_70_TEST4B_OUT0 = 0x0C,
    _PIN_70_TEST4B_OUT1 = 0x0D,
    _PIN_70_TEST4B_OUT2 = 0x0E,
    _PIN_70_TEST4B_OUT3 = 0x0F,
    _PIN_70_NC = _PIN_70_GPO_PP,
} EnumPinshareInfoPIN70;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1021
// MCU Ctrl : 0xFE11 at _PIN_71_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_71_HI_Z = 0x00,
    _PIN_71_GPI = 0x01,
    _PIN_71_GPO_PP = 0x02,
    _PIN_71_GPO_OD = 0x03,
    _PIN_71_TXO1P_8B = 0x04,
    _PIN_71_TEST4B_OUT0 = 0x0C,
    _PIN_71_TEST4B_OUT1 = 0x0D,
    _PIN_71_TEST4B_OUT2 = 0x0E,
    _PIN_71_TEST4B_OUT3 = 0x0F,
    _PIN_71_NC = _PIN_71_GPO_PP,
} EnumPinshareInfoPIN71;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1022
// MCU Ctrl : 0xFE12 at _PIN_72_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_72_HI_Z = 0x00,
    _PIN_72_GPI = 0x01,
    _PIN_72_GPO_PP = 0x02,
    _PIN_72_GPO_OD = 0x03,
    _PIN_72_TXO1N_8B = 0x04,
    _PIN_72_TEST4B_OUT0 = 0x0C,
    _PIN_72_TEST4B_OUT1 = 0x0D,
    _PIN_72_TEST4B_OUT2 = 0x0E,
    _PIN_72_TEST4B_OUT3 = 0x0F,
    _PIN_72_NC = _PIN_72_GPO_PP,
} EnumPinshareInfoPIN72;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1023
// MCU Ctrl : 0xFE13 at _PIN_73_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_73_HI_Z = 0x00,
    _PIN_73_GPI = 0x01,
    _PIN_73_GPO_PP = 0x02,
    _PIN_73_GPO_OD = 0x03,
    _PIN_73_TXO0P_8B = 0x04,
    _PIN_73_TEST4B_OUT0 = 0x0C,
    _PIN_73_TEST4B_OUT1 = 0x0D,
    _PIN_73_TEST4B_OUT2 = 0x0E,
    _PIN_73_TEST4B_OUT3 = 0x0F,
    _PIN_73_NC = _PIN_73_GPO_PP,
} EnumPinshareInfoPIN73;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1024
// MCU Ctrl : 0xFE14 at _PIN_74_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_74_HI_Z = 0x00,
    _PIN_74_GPI = 0x01,
    _PIN_74_GPO_PP = 0x02,
    _PIN_74_GPO_OD = 0x03,
    _PIN_74_TXO0N_8B = 0x04,
    _PIN_74_TEST4B_OUT0 = 0x0C,
    _PIN_74_TEST4B_OUT1 = 0x0D,
    _PIN_74_TEST4B_OUT2 = 0x0E,
    _PIN_74_TEST4B_OUT3 = 0x0F,
    _PIN_74_NC = _PIN_74_GPO_PP,
} EnumPinshareInfoPIN74;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1025
// MCU Ctrl : 0xFE15 at _PIN_90_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_90_GPI = 0x00,
    _PIN_90_GPO_PP = 0x01,
    _PIN_90_GPO_OD = 0x02,
    _PIN_90_TEST4B_OUT0 = 0x0C,
    _PIN_90_TEST4B_OUT1 = 0x0D,
    _PIN_90_TEST4B_OUT2 = 0x0E,
    _PIN_90_TEST4B_OUT3 = 0x0F,
    _PIN_90_NC = _PIN_90_GPO_PP,
} EnumPinshareInfoPIN90;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1026
// MCU Ctrl : 0xFE16 at _PIN_91_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_91_GPI = 0x00,
    _PIN_91_GPO_PP = 0x01,
    _PIN_91_GPO_OD = 0x02,
    _PIN_91_TEST4B_OUT0 = 0x0C,
    _PIN_91_TEST4B_OUT1 = 0x0D,
    _PIN_91_TEST4B_OUT2 = 0x0E,
    _PIN_91_TEST4B_OUT3 = 0x0F,
    _PIN_91_NC = _PIN_91_GPO_PP,
} EnumPinshareInfoPIN91;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1027
// MCU Ctrl : 0xFE17 at _PIN_92_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_92_GPI = 0x00,
    _PIN_92_GPO_PP = 0x01,
    _PIN_92_GPO_OD = 0x02,
    _PIN_92_PWM3_PP = 0x03,
    _PIN_92_PWM3_OD = 0x04,
    _PIN_92_TEST4B_OUT0 = 0x0C,
    _PIN_92_TEST4B_OUT1 = 0x0D,
    _PIN_92_TEST4B_OUT2 = 0x0E,
    _PIN_92_TEST4B_OUT3 = 0x0F,
    _PIN_92_NC = _PIN_92_GPO_PP,
} EnumPinshareInfoPIN92;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1028
// MCU Ctrl : 0xFE18 at _PIN_93_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_93_GPI = 0x00,
    _PIN_93_GPO_PP = 0x01,
    _PIN_93_GPO_OD = 0x02,
    _PIN_93_PWM2_PP = 0x03,
    _PIN_93_PWM2_OD = 0x04,
    _PIN_93_TEST4B_OUT0 = 0x0C,
    _PIN_93_TEST4B_OUT1 = 0x0D,
    _PIN_93_TEST4B_OUT2 = 0x0E,
    _PIN_93_TEST4B_OUT3 = 0x0F,
    _PIN_93_NC = _PIN_93_GPO_PP,
} EnumPinshareInfoPIN93;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1029
// MCU Ctrl : 0xFE19 at _PIN_94_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_94_GPI = 0x00,
    _PIN_94_GPO_PP = 0x01,
    _PIN_94_GPO_OD = 0x02,
    _PIN_94_PWM1_PP = 0x03,
    _PIN_94_PWM1_OD = 0x04,
    _PIN_94_TEST4B_OUT0 = 0x0C,
    _PIN_94_TEST4B_OUT1 = 0x0D,
    _PIN_94_TEST4B_OUT2 = 0x0E,
    _PIN_94_TEST4B_OUT3 = 0x0F,
    _PIN_94_NC = _PIN_94_GPO_PP,
} EnumPinshareInfoPIN94;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102A
// MCU Ctrl : 0xFE1A at _PIN_96_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_96_GPI = 0x00,
    _PIN_96_GPO_PP = 0x01,
    _PIN_96_GPO_OD = 0x02,
    _PIN_96_INT0 = 0x03,
    _PIN_96_TEST4B_OUT0 = 0x0C,
    _PIN_96_TEST4B_OUT1 = 0x0D,
    _PIN_96_TEST4B_OUT2 = 0x0E,
    _PIN_96_TEST4B_OUT3 = 0x0F,
    _PIN_96_NC = _PIN_96_GPO_PP,
} EnumPinshareInfoPIN96;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102B
// MCU Ctrl : 0xFE1B at _PIN_97_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_97_GPI = 0x00,
    _PIN_97_GPO_PP = 0x01,
    _PIN_97_GPO_OD = 0x02,
    _PIN_97_INT1 = 0x03,
    _PIN_97_TCON11 = 0x04,
    _PIN_97_IVS_AFTER_SCALING_DOWN = 0x06,
    _PIN_97_TEST4B_OUT0 = 0x0C,
    _PIN_97_TEST4B_OUT1 = 0x0D,
    _PIN_97_TEST4B_OUT2 = 0x0E,
    _PIN_97_TEST4B_OUT3 = 0x0F,
    _PIN_97_NC = _PIN_97_GPO_PP,
} EnumPinshareInfoPIN97;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102C
// MCU Ctrl : 0xFE1C at _PIN_98_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_98_GPI = 0x00,
    _PIN_98_GPO_PP = 0x01,
    _PIN_98_GPO_OD = 0x02,
    _PIN_98_T0 = 0x03,
    _PIN_98_DENA = 0x04,
    _PIN_98_TCON9 = 0x05,
    _PIN_98_TEST4B_OUT0 = 0x0C,
    _PIN_98_TEST4B_OUT1 = 0x0D,
    _PIN_98_TEST4B_OUT2 = 0x0E,
    _PIN_98_TEST4B_OUT3 = 0x0F,
    _PIN_98_NC = _PIN_98_GPO_PP,
} EnumPinshareInfoPIN98;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102D
// MCU Ctrl : 0xFE1D at _PIN_99_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_99_GPI = 0x00,
    _PIN_99_GPO_PP = 0x01,
    _PIN_99_GPO_OD = 0x02,
    _PIN_99_PWM2_PP = 0x03,
    _PIN_99_PWM2_OD = 0x04,
    _PIN_99_PWM3_PP = 0x05,
    _PIN_99_PWM3_OD = 0x06,
    _PIN_99_T1 = 0x07,
    _PIN_99_DHS = 0x08,
    _PIN_99_TCON13 = 0x09,
    _PIN_99_TEST4B_OUT0 = 0x0C,
    _PIN_99_TEST4B_OUT1 = 0x0D,
    _PIN_99_TEST4B_OUT2 = 0x0E,
    _PIN_99_TEST4B_OUT3 = 0x0F,
    _PIN_99_NC = _PIN_99_GPO_PP,
} EnumPinshareInfoPIN99;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102E
// MCU Ctrl : 0xFE1E at _PIN_100_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_100_GPI = 0x80,
    _PIN_100_GPO_PP = 0x81,
    _PIN_100_GPO_OD = 0x82,
    _PIN_100_AUX_D2 = 0x83,
    _PIN_100_DCLK = 0x84,
    _PIN_100_TCON8 = 0x85,
    _PIN_100_PWM_IN = 0x86,
    _PIN_100_T2EX = 0x87,
    _PIN_100_TEST4B_OUT0 = 0x8C,
    _PIN_100_TEST4B_OUT1 = 0x8D,
    _PIN_100_TEST4B_OUT2 = 0x8E,
    _PIN_100_TEST4B_OUT3 = 0x8F,
    _PIN_100_DDCSCLVGA1 = 0x00,
    _PIN_100_NC = _PIN_100_GPO_PP,
} EnumPinshareInfoPIN100;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102F
// MCU Ctrl : 0xFE1F at _PIN_101_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_101_GPI = 0x00,
    _PIN_101_GPO_PP = 0x01,
    _PIN_101_GPO_OD = 0x02,
    _PIN_101_AUX_D1 = 0x03,
    _PIN_101_DVS = 0x04,
    _PIN_101_TCON7 = 0x05,
    _PIN_101_PWM_OUT = 0x06,
    _PIN_101_PWM1_PP = 0x07,
    _PIN_101_PWM1_OD = 0x08,
    _PIN_101_TEST4B_OUT0 = 0x0C,
    _PIN_101_TEST4B_OUT1 = 0x0D,
    _PIN_101_TEST4B_OUT2 = 0x0E,
    _PIN_101_TEST4B_OUT3 = 0x0F,
    _PIN_101_DDCSDAVGA1 = 0x00,
    _PIN_101_NC = _PIN_101_GPO_PP,
} EnumPinshareInfoPIN101;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1030
// MCU Ctrl : 0xFE20 at _PIN_102_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_102_GPI = 0x00,
    _PIN_102_GPO_PP = 0x01,
    _PIN_102_GPO_OD = 0x02,
    _PIN_102_TEST4B_OUT0 = 0x0C,
    _PIN_102_TEST4B_OUT1 = 0x0D,
    _PIN_102_TEST4B_OUT2 = 0x0E,
    _PIN_102_TEST4B_OUT3 = 0x0F,
    _PIN_102_NC = _PIN_102_GPO_PP,
} EnumPinshareInfoPIN102;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1031
// MCU Ctrl : 0xFE21 at _PIN_108_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_108_GPI = 0x00,
    _PIN_108_GPO_PP = 0x01,
    _PIN_108_GPO_OD = 0x02,
    _PIN_108_PWM3_PP = 0x03,
    _PIN_108_PWM3_OD = 0x04,
    _PIN_108_TEST4B_OUT0 = 0x0C,
    _PIN_108_TEST4B_OUT1 = 0x0D,
    _PIN_108_TEST4B_OUT2 = 0x0E,
    _PIN_108_TEST4B_OUT3 = 0x0F,
    _PIN_108_NC = _PIN_108_GPO_PP,
} EnumPinshareInfoPIN108;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1032
// MCU Ctrl : 0xFE22 at _PIN_110_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_110_GPI = 0x80,
    _PIN_110_GPO_PP = 0x81,
    _PIN_110_GPO_OD = 0x82,
    _PIN_110_AUXP0 = 0x85,
    _PIN_110_TEST4B_OUT0 = 0x8C,
    _PIN_110_TEST4B_OUT1 = 0x8D,
    _PIN_110_TEST4B_OUT2 = 0x8E,
    _PIN_110_TEST4B_OUT3 = 0x8F,
    _PIN_110_DDCSCL0 = 0x00,
    _PIN_110_NC = _PIN_110_GPO_PP,
} EnumPinshareInfoPIN110;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1033
// MCU Ctrl : 0xFE23 at _PIN_111_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_111_GPI = 0x00,
    _PIN_111_GPO_PP = 0x01,
    _PIN_111_GPO_OD = 0x02,
    _PIN_111_AUXN0 = 0x05,
    _PIN_111_TEST4B_OUT0 = 0x0C,
    _PIN_111_TEST4B_OUT1 = 0x0D,
    _PIN_111_TEST4B_OUT2 = 0x0E,
    _PIN_111_TEST4B_OUT3 = 0x0F,
    _PIN_111_DDCSDA0 = 0x00,
    _PIN_111_NC = _PIN_111_GPO_PP,
} EnumPinshareInfoPIN111;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1034
// MCU Ctrl : 0xFE24 at _PIN_112_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_112_GPI = 0x80,
    _PIN_112_GPO_PP = 0x81,
    _PIN_112_GPO_OD = 0x82,
    _PIN_112_AUXP1 = 0x83,
    _PIN_112_TEST4B_OUT0 = 0x8C,
    _PIN_112_TEST4B_OUT1 = 0x8D,
    _PIN_112_TEST4B_OUT2 = 0x8E,
    _PIN_112_TEST4B_OUT3 = 0x8F,
    _PIN_112_DDCSCL1 = 0x00,
    _PIN_112_NC = _PIN_112_GPO_PP,
} EnumPinshareInfoPIN112;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1035
// MCU Ctrl : 0xFE25 at _PIN_113_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_113_GPI = 0x00,
    _PIN_113_GPO_PP = 0x01,
    _PIN_113_GPO_OD = 0x02,
    _PIN_113_AUXN1 = 0x03,
    _PIN_113_TEST4B_OUT0 = 0x0C,
    _PIN_113_TEST4B_OUT1 = 0x0D,
    _PIN_113_TEST4B_OUT2 = 0x0E,
    _PIN_113_TEST4B_OUT3 = 0x0F,
    _PIN_113_DDCSDA1 = 0x00,
    _PIN_113_NC = _PIN_113_GPO_PP,
} EnumPinshareInfoPIN113;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1036
// MCU Ctrl : 0xFE26 at _PIN_114_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_114_GPI = 0x00,
    _PIN_114_GPO_PP = 0x01,
    _PIN_114_GPO_OD = 0x02,
    _PIN_114_PWM2_PP = 0x03,
    _PIN_114_PWM2_OD = 0x04,
    _PIN_114_TEST4B_OUT0 = 0x0C,
    _PIN_114_TEST4B_OUT1 = 0x0D,
    _PIN_114_TEST4B_OUT2 = 0x0E,
    _PIN_114_TEST4B_OUT3 = 0x0F,
    _PIN_114_NC = _PIN_114_GPO_PP,
} EnumPinshareInfoPIN114;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1037
// MCU Ctrl : 0xFE27 at _PIN_115_MCU_REG
//---------------------------------------------------------------------------
typedef enum
{
    _PIN_115_GPI = 0x00,
    _PIN_115_GPO_PP = 0x01,
    _PIN_115_GPO_OD = 0x02,
    _PIN_115_PWM1_PP = 0x03,
    _PIN_115_PWM1_OD = 0x04,
    _PIN_115_TEST4B_OUT0 = 0x0C,
    _PIN_115_TEST4B_OUT1 = 0x0D,
    _PIN_115_TEST4B_OUT2 = 0x0E,
    _PIN_115_TEST4B_OUT3 = 0x0F,
    _PIN_115_NC = _PIN_115_GPO_PP,
} EnumPinshareInfoPIN115;

#endif // End of #if((_PCB_NEW_MODE_SUPPORT == _OFF) || (_PCB_PINSHARE_MAPPING == _ON))


///////////////////////////
// RL6463_76_PIN mapping //
///////////////////////////
#if(_PCB_PINSHARE_MAPPING == _ON)

#if(_PCB_NEW_MODE_SUPPORT == _OFF)
//---------------------------------------------------------------------------
// Function : _76PIN_PIN_21
// Pinshare : 0x1002
// MCU Ctrl : 0xFFE2[2] at _PIN_34_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_34                                 (_76PIN_PIN_21)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_22
// Pinshare : 0x1003
// MCU Ctrl : 0xFFE2[3] at _PIN_35_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_35                                 (_76PIN_PIN_22)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_23
// Pinshare : 0x1004
// MCU Ctrl : 0xFFE2[4] at _PIN_36_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_36                                 (_76PIN_PIN_23)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_24
// Pinshare : 0x1005
// MCU Ctrl : 0xFFE2[5] at _PIN_37_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_37                                 (_76PIN_PIN_24)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_27
// Pinshare : 0x1008
// MCU Ctrl : 0xFFE3[0] at _PIN_42_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_42                                 (_76PIN_PIN_27)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_28
// Pinshare : 0x1009
// MCU Ctrl : 0xFFE3[1] at _PIN_43_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_43                                 (_76PIN_PIN_28)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_29
// Pinshare : 0x100A
// MCU Ctrl : 0xFFE3[2] at _PIN_44_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_44                                 (_76PIN_PIN_29)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_30
// Pinshare : 0x100C
// MCU Ctrl : 0xFFE3[4] at _PIN_46_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_46                                 (_76PIN_PIN_30)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_31
// Pinshare : 0x100D
// MCU Ctrl : 0xFFE3[5] at _PIN_47_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_47                                 (_76PIN_PIN_31)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_32
// Pinshare : 0x100E
// MCU Ctrl : 0xFFE3[6] at _PIN_48_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_48                                 (_76PIN_PIN_32)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_33
// Pinshare : 0x100F
// MCU Ctrl : 0xFFE3[7] at _PIN_49_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_49                                 (_76PIN_PIN_33)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_34
// Pinshare : 0x1010
// MCU Ctrl : 0xFE00 at _PIN_50_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_50                                 (_76PIN_PIN_34)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_36
// Pinshare : 0x1012
// MCU Ctrl : 0xFE02 at _PIN_53_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_53                                 (_76PIN_PIN_36)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_37
// Pinshare : 0x101A
// MCU Ctrl : 0xFE0A at _PIN_63_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_63                                 (_76PIN_PIN_37)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_38
// Pinshare : 0x101B
// MCU Ctrl : 0xFE0B at _PIN_64_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_64                                 (_76PIN_PIN_38)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_39_OFF_REGION
// Pinshare : 0x101D
// MCU Ctrl : 0xFE0D at _PIN_67_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_67_OFF_REGION                      (_76PIN_PIN_39_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_40_OFF_REGION
// Pinshare : 0x101E
// MCU Ctrl : 0xFE0E at _PIN_68_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_68_OFF_REGION                      (_76PIN_PIN_40_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_41_OFF_REGION
// Pinshare : 0x101F
// MCU Ctrl : 0xFE0F at _PIN_69_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_69_OFF_REGION                      (_76PIN_PIN_41_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_42_OFF_REGION
// Pinshare : 0x1020
// MCU Ctrl : 0xFE10 at _PIN_70_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_70_OFF_REGION                      (_76PIN_PIN_42_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_43_OFF_REGION
// Pinshare : 0x1021
// MCU Ctrl : 0xFE11 at _PIN_71_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_71_OFF_REGION                      (_76PIN_PIN_43_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_44_OFF_REGION
// Pinshare : 0x1022
// MCU Ctrl : 0xFE12 at _PIN_72_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_72_OFF_REGION                      (_76PIN_PIN_44_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_45_OFF_REGION
// Pinshare : 0x1023
// MCU Ctrl : 0xFE13 at _PIN_73_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_73_OFF_REGION                      (_76PIN_PIN_45_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_46_OFF_REGION
// Pinshare : 0x1024
// MCU Ctrl : 0xFE14 at _PIN_74_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_74_OFF_REGION                      (_76PIN_PIN_46_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_58
// Pinshare : 0x102A
// MCU Ctrl : 0xFE1A at _PIN_96_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_96                                 (_76PIN_PIN_58)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_59
// Pinshare : 0x102B
// MCU Ctrl : 0xFE1B at _PIN_97_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_97                                 (_76PIN_PIN_59)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_60
// Pinshare : 0x102C
// MCU Ctrl : 0xFE1C at _PIN_98_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_98                                 (_76PIN_PIN_60)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_61
// Pinshare : 0x102D
// MCU Ctrl : 0xFE1D at _PIN_99_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_99                                 (_76PIN_PIN_61)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_62
// Pinshare : 0x102E
// MCU Ctrl : 0xFE1E at _PIN_100_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_100                                (_76PIN_PIN_62)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_63
// Pinshare : 0x102F
// MCU Ctrl : 0xFE1F at _PIN_101_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_101                                (_76PIN_PIN_63)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_70
// Pinshare : 0x1034
// MCU Ctrl : 0xFE24 at _PIN_112_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_112                                (_76PIN_PIN_70)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_71
// Pinshare : 0x1035
// MCU Ctrl : 0xFE25 at _PIN_113_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_113                                (_76PIN_PIN_71)

#else

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_21
// Pinshare : 0x1002
// MCU Ctrl : 0xFFE2[2] at _PIN_34_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_34                                 (EnumPinshareInfoPIN34)(_76PIN_PIN_21)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_22
// Pinshare : 0x1003
// MCU Ctrl : 0xFFE2[3] at _PIN_35_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_35                                 (EnumPinshareInfoPIN35)(_76PIN_PIN_22)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_23
// Pinshare : 0x1004
// MCU Ctrl : 0xFFE2[4] at _PIN_36_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_36                                 (EnumPinshareInfoPIN36)(_76PIN_PIN_23)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_24
// Pinshare : 0x1005
// MCU Ctrl : 0xFFE2[5] at _PIN_37_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_37                                 (EnumPinshareInfoPIN37)(_76PIN_PIN_24)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_27
// Pinshare : 0x1008
// MCU Ctrl : 0xFFE3[0] at _PIN_42_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_42                                 (EnumPinshareInfoPIN42)(_76PIN_PIN_27)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_28
// Pinshare : 0x1009
// MCU Ctrl : 0xFFE3[1] at _PIN_43_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_43                                 (EnumPinshareInfoPIN43)(_76PIN_PIN_28)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_29
// Pinshare : 0x100A
// MCU Ctrl : 0xFFE3[2] at _PIN_44_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_44                                 (EnumPinshareInfoPIN44)(_76PIN_PIN_29)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_30
// Pinshare : 0x100C
// MCU Ctrl : 0xFFE3[4] at _PIN_46_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_46                                 (EnumPinshareInfoPIN46)(_76PIN_PIN_30)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_31
// Pinshare : 0x100D
// MCU Ctrl : 0xFFE3[5] at _PIN_47_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_47                                 (EnumPinshareInfoPIN47)(_76PIN_PIN_31)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_32
// Pinshare : 0x100E
// MCU Ctrl : 0xFFE3[6] at _PIN_48_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_48                                 (EnumPinshareInfoPIN48)(_76PIN_PIN_32)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_33
// Pinshare : 0x100F
// MCU Ctrl : 0xFFE3[7] at _PIN_49_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_49                                 (EnumPinshareInfoPIN49)(_76PIN_PIN_33)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_34
// Pinshare : 0x1010
// MCU Ctrl : 0xFE00 at _PIN_50_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_50                                 (EnumPinshareInfoPIN50)(_76PIN_PIN_34)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_36
// Pinshare : 0x1012
// MCU Ctrl : 0xFE02 at _PIN_53_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_53                                 (EnumPinshareInfoPIN53)(_76PIN_PIN_36)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_37
// Pinshare : 0x101A
// MCU Ctrl : 0xFE0A at _PIN_63_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_63                                 (EnumPinshareInfoPIN63)(_76PIN_PIN_37)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_38
// Pinshare : 0x101B
// MCU Ctrl : 0xFE0B at _PIN_64_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_64                                 (EnumPinshareInfoPIN64)(_76PIN_PIN_38)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_39_OFF_REGION
// Pinshare : 0x101D
// MCU Ctrl : 0xFE0D at _PIN_67_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_67_OFF_REGION                      (EnumPinshareInfoPIN67)(_76PIN_PIN_39_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_40_OFF_REGION
// Pinshare : 0x101E
// MCU Ctrl : 0xFE0E at _PIN_68_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_68_OFF_REGION                      (EnumPinshareInfoPIN68)(_76PIN_PIN_40_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_41_OFF_REGION
// Pinshare : 0x101F
// MCU Ctrl : 0xFE0F at _PIN_69_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_69_OFF_REGION                      (EnumPinshareInfoPIN69)(_76PIN_PIN_41_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_42_OFF_REGION
// Pinshare : 0x1020
// MCU Ctrl : 0xFE10 at _PIN_70_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_70_OFF_REGION                      (EnumPinshareInfoPIN70)(_76PIN_PIN_42_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_43_OFF_REGION
// Pinshare : 0x1021
// MCU Ctrl : 0xFE11 at _PIN_71_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_71_OFF_REGION                      (EnumPinshareInfoPIN71)(_76PIN_PIN_43_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_44_OFF_REGION
// Pinshare : 0x1022
// MCU Ctrl : 0xFE12 at _PIN_72_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_72_OFF_REGION                      (EnumPinshareInfoPIN72)(_76PIN_PIN_44_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_45_OFF_REGION
// Pinshare : 0x1023
// MCU Ctrl : 0xFE13 at _PIN_73_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_73_OFF_REGION                      (EnumPinshareInfoPIN73)(_76PIN_PIN_45_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_46_OFF_REGION
// Pinshare : 0x1024
// MCU Ctrl : 0xFE14 at _PIN_74_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_74_OFF_REGION                      (EnumPinshareInfoPIN74)(_76PIN_PIN_46_OFF_REGION)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_58
// Pinshare : 0x102A
// MCU Ctrl : 0xFE1A at _PIN_96_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_96                                 (EnumPinshareInfoPIN96)(_76PIN_PIN_58)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_59
// Pinshare : 0x102B
// MCU Ctrl : 0xFE1B at _PIN_97_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_97                                 (EnumPinshareInfoPIN97)(_76PIN_PIN_59)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_60
// Pinshare : 0x102C
// MCU Ctrl : 0xFE1C at _PIN_98_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_98                                 (EnumPinshareInfoPIN98)(_76PIN_PIN_60)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_61
// Pinshare : 0x102D
// MCU Ctrl : 0xFE1D at _PIN_99_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_99                                 (EnumPinshareInfoPIN99)(_76PIN_PIN_61)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_62
// Pinshare : 0x102E
// MCU Ctrl : 0xFE1E at _PIN_100_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_100                                (EnumPinshareInfoPIN100)(_76PIN_PIN_62)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_63
// Pinshare : 0x102F
// MCU Ctrl : 0xFE1F at _PIN_101_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_101                                (EnumPinshareInfoPIN101)(_76PIN_PIN_63)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_70
// Pinshare : 0x1034
// MCU Ctrl : 0xFE24 at _PIN_112_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_112                                (EnumPinshareInfoPIN112)(_76PIN_PIN_70)

//---------------------------------------------------------------------------
// Function : _76PIN_PIN_71
// Pinshare : 0x1035
// MCU Ctrl : 0xFE25 at _PIN_113_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_113                                (EnumPinshareInfoPIN113)(_76PIN_PIN_71)

#endif // End of #if(_PCB_NEW_MODE_SUPPORT == _OFF)
#endif // End of #if(_PCB_PINSHARE_MAPPING == _ON)


///////////////////
// NC PINs       //
///////////////////
#if(_PCB_PINSHARE_MAPPING == _ON)
//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1000
// MCU Ctrl : 0xFFE2[0] at _PIN_21_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_21                                 (_PIN_21_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1001
// MCU Ctrl : 0xFFE2[1] at _PIN_22_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_22                                 (_PIN_22_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1006
// MCU Ctrl : 0xFFE2[6] at _PIN_38_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_38                                 (_PIN_38_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1007
// MCU Ctrl : 0xFFE2[7] at _PIN_39_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_39                                 (_PIN_39_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100B
// MCU Ctrl : 0xFFE3[3] at _PIN_45_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_45                                 (_PIN_45_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1011
// MCU Ctrl : 0xFE01 at _PIN_52_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_52                                 (_PIN_52_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1013
// MCU Ctrl : 0xFE03 at _PIN_55_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_55                                 (_PIN_55_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1014
// MCU Ctrl : 0xFE04 at _PIN_56_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_56                                 (_PIN_56_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1015
// MCU Ctrl : 0xFE05 at _PIN_57_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_57                                 (_PIN_57_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1016
// MCU Ctrl : 0xFE06 at _PIN_58_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_58                                 (_PIN_58_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1017
// MCU Ctrl : 0xFE07 at _PIN_59_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_59                                 (_PIN_59_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1018
// MCU Ctrl : 0xFE08 at _PIN_60_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_60                                 (_PIN_60_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1019
// MCU Ctrl : 0xFE09 at _PIN_61_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_61                                 (_PIN_61_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101C
// MCU Ctrl : 0xFE0C at _PIN_65_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_65                                 (_PIN_65_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1025
// MCU Ctrl : 0xFE15 at _PIN_90_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_90                                 (_PIN_90_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1026
// MCU Ctrl : 0xFE16 at _PIN_91_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_91                                 (_PIN_91_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1027
// MCU Ctrl : 0xFE17 at _PIN_92_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_92                                 (_PIN_92_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1028
// MCU Ctrl : 0xFE18 at _PIN_93_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_93                                 (_PIN_93_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1029
// MCU Ctrl : 0xFE19 at _PIN_94_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_94                                 (_PIN_94_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1030
// MCU Ctrl : 0xFE20 at _PIN_102_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_102                                (_PIN_102_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1031
// MCU Ctrl : 0xFE21 at _PIN_108_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_108                                (_PIN_108_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1032
// MCU Ctrl : 0xFE22 at _PIN_110_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_110                                (_PIN_110_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1033
// MCU Ctrl : 0xFE23 at _PIN_111_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_111                                (_PIN_111_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1036
// MCU Ctrl : 0xFE26 at _PIN_114_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_114                                (_PIN_114_NC)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1037
// MCU Ctrl : 0xFE27 at _PIN_115_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_115                                (_PIN_115_NC)

#endif // End of #if(_PCB_PINSHARE_MAPPING == _ON)


//////////////////////////
// NEW/OLD MODE MAPPING //
//////////////////////////
#if(_PCB_NEW_MODE_SUPPORT == _OFF)

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1005
// MCU Ctrl : 0xFFE2[5] at _PIN_37_MCU_REG
//---------------------------------------------------------------------------
#ifndef _PIN_37_MAPPED
#if(_PIN_37 == 8)
#undef _PIN_37
#define _PIN_37                                 _PIN_37_IICSCL0
#define _PIN_37_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_37_MAPPED
#if(_PIN_37 == 9)
#undef _PIN_37
#define _PIN_37                                 _PIN_37_RXD0
#define _PIN_37_MAPPED                          _ON
#endif
#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1006
// MCU Ctrl : 0xFFE2[6] at _PIN_38_MCU_REG
//---------------------------------------------------------------------------
#if(_PCB_PINSHARE_MAPPING == _OFF)

#ifndef _PIN_38_MAPPED
#if(_PIN_38 == 8)
#undef _PIN_38
#define _PIN_38                                 _PIN_38_IICSDA0
#define _PIN_38_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_38_MAPPED
#if(_PIN_38 == 9)
#undef _PIN_38
#define _PIN_38                                 _PIN_38_TXD0
#define _PIN_38_MAPPED                          _ON
#endif
#endif

#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100D
// MCU Ctrl : 0xFFE3[5] at _PIN_47_MCU_REG
//---------------------------------------------------------------------------
#ifndef _PIN_47_MAPPED
#if(_PIN_47 == 8)
#undef _PIN_47
#define _PIN_47                                 _PIN_47_IICSCL1
#define _PIN_47_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_47_MAPPED
#if(_PIN_47 == 9)
#undef _PIN_47
#define _PIN_47                                 _PIN_47_IICSCL_AUX
#define _PIN_47_MAPPED                          _ON
#endif
#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100E
// MCU Ctrl : 0xFFE3[6] at _PIN_48_MCU_REG
//---------------------------------------------------------------------------
#ifndef _PIN_48_MAPPED
#if(_PIN_48 == 8)
#undef _PIN_48
#define _PIN_48                                 _PIN_48_IICSDA1
#define _PIN_48_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_48_MAPPED
#if(_PIN_48 == 9)
#undef _PIN_48
#define _PIN_48                                 _PIN_48_IICSDA_AUX
#define _PIN_48_MAPPED                          _ON
#endif
#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100F
// MCU Ctrl : 0xFFE3[7] at _PIN_49_MCU_REG
//---------------------------------------------------------------------------
#ifndef _PIN_49_MAPPED
#if(_PIN_49 == 0)
#undef _PIN_49
#define _PIN_49                                 _PIN_49_GPI
#define _PIN_49_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_49_MAPPED
#if(_PIN_49 == 1)
#undef _PIN_49
#define _PIN_49                                 _PIN_49_GPO_PP
#define _PIN_49_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_49_MAPPED
#if(_PIN_49 == 2)
#undef _PIN_49
#define _PIN_49                                 _PIN_49_GPO_OD
#define _PIN_49_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_49_MAPPED
#if(_PIN_49 == 7)
#undef _PIN_49
#define _PIN_49                                 _PIN_49_DDCCSL_MUX_SWAP_PIN_43
#define _PIN_49_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_49_MAPPED
#if(_PIN_49 == 8)
#undef _PIN_49
#define _PIN_49                                 _PIN_49_DDCSCLVGA0
#define _PIN_49_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_49_MAPPED
#if(_PIN_49 == 9)
#undef _PIN_49
#define _PIN_49                                 _PIN_49_RXD1
#define _PIN_49_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_49_MAPPED
#if(_PIN_49 == 0x0C)
#undef _PIN_49
#define _PIN_49                                 _PIN_49_TEST4B_OUT0
#define _PIN_49_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_49_MAPPED
#if(_PIN_49 == 0x0D)
#undef _PIN_49
#define _PIN_49                                 _PIN_49_TEST4B_OUT1
#define _PIN_49_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_49_MAPPED
#if(_PIN_49 == 0x0E)
#undef _PIN_49
#define _PIN_49                                 _PIN_49_TEST4B_OUT2
#define _PIN_49_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_49_MAPPED
#if(_PIN_49 == 0x0F)
#undef _PIN_49
#define _PIN_49                                 _PIN_49_TEST4B_OUT3
#define _PIN_49_MAPPED                          _ON
#endif
#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1010
// MCU Ctrl : 0xFE00 at _PIN_50_MCU_REG
//---------------------------------------------------------------------------
#ifndef _PIN_50_MAPPED
#if(_PIN_50 == 7)
#undef _PIN_50
#define _PIN_50                                 _PIN_50_DDCSDA_MUX_SWAP_PIN_44
#define _PIN_50_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_50_MAPPED
#if(_PIN_50 == 8)
#undef _PIN_50
#define _PIN_50                                 _PIN_50_DDCSDAVGA0
#define _PIN_50_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_50_MAPPED
#if(_PIN_50 == 9)
#undef _PIN_50
#define _PIN_50                                 _PIN_50_TXD1
#define _PIN_50_MAPPED                          _ON
#endif
#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1018
// MCU Ctrl : 0xFE08 at _PIN_60_MCU_REG
//---------------------------------------------------------------------------
#if(_PCB_PINSHARE_MAPPING == _OFF)

#ifndef _PIN_60_MAPPED
#if(_PIN_60 == 8)
#undef _PIN_60
#define _PIN_60                                 _PIN_60_IICSCL2
#define _PIN_60_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_60_MAPPED
#if(_PIN_60 == 9)
#undef _PIN_60
#define _PIN_60                                 _PIN_60_RXD2
#define _PIN_60_MAPPED                          _ON
#endif
#endif

#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1019
// MCU Ctrl : 0xFE09 at _PIN_61_MCU_REG
//---------------------------------------------------------------------------
#if(_PCB_PINSHARE_MAPPING == _OFF)

#ifndef _PIN_61_MAPPED
#if(_PIN_61 == 8)
#undef _PIN_61
#define _PIN_61                                 _PIN_61_IICSDA2
#define _PIN_61_MAPPED                          _ON
#endif
#endif

#ifndef _PIN_61_MAPPED
#if(_PIN_61 == 9)
#undef _PIN_61
#define _PIN_61                                 _PIN_61_TXD2
#define _PIN_61_MAPPED                          _ON
#endif
#endif

#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102E
// MCU Ctrl : 0xFE1E at _PIN_100_MCU_REG
//---------------------------------------------------------------------------
#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 0)
#undef _PIN_100
#define _PIN_100                                _PIN_100_GPI
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 1)
#undef _PIN_100
#define _PIN_100                                _PIN_100_GPO_PP
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 2)
#undef _PIN_100
#define _PIN_100                                _PIN_100_GPO_OD
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 3)
#undef _PIN_100
#define _PIN_100                                _PIN_100_AUX_D2
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 4)
#undef _PIN_100
#define _PIN_100                                _PIN_100_DCLK
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 5)
#undef _PIN_100
#define _PIN_100                                _PIN_100_TCON8
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 6)
#undef _PIN_100
#define _PIN_100                                _PIN_100_PWM_IN
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 7)
#undef _PIN_100
#define _PIN_100                                _PIN_100_T2EX
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 8)
#undef _PIN_100
#define _PIN_100                                _PIN_100_DDCSCLVGA1
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 0x0C)
#undef _PIN_100
#define _PIN_100                                _PIN_100_TEST4B_OUT0
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 0x0D)
#undef _PIN_100
#define _PIN_100                                _PIN_100_TEST4B_OUT1
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 0x0E)
#undef _PIN_100
#define _PIN_100                                _PIN_100_TEST4B_OUT2
#define _PIN_100_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_100_MAPPED
#if(_PIN_100 == 0x0F)
#undef _PIN_100
#define _PIN_100                                _PIN_100_TEST4B_OUT3
#define _PIN_100_MAPPED                         _ON
#endif
#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102F
// MCU Ctrl : 0xFE1F at _PIN_101_MCU_REG
//---------------------------------------------------------------------------
#ifndef _PIN_101_MAPPED
#if(_PIN_101 == 8)
#undef _PIN_101
#define _PIN_101                                _PIN_101_DDCSDAVGA1
#define _PIN_101_MAPPED                         _ON
#endif
#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1032
// MCU Ctrl : 0xFE22 at _PIN_110_MCU_REG
//---------------------------------------------------------------------------
#if(_PCB_PINSHARE_MAPPING == _OFF)

#ifndef _PIN_110_MAPPED
#if(_PIN_110 == 0)
#undef _PIN_110
#define _PIN_110                                _PIN_110_GPI
#define _PIN_110_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_110_MAPPED
#if(_PIN_110 == 1)
#undef _PIN_110
#define _PIN_110                                _PIN_110_GPO_PP
#define _PIN_110_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_110_MAPPED
#if(_PIN_110 == 2)
#undef _PIN_110
#define _PIN_110                                _PIN_110_GPO_OD
#define _PIN_110_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_110_MAPPED
#if(_PIN_110 == 5)
#undef _PIN_110
#define _PIN_110                                _PIN_110_AUXP0
#define _PIN_110_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_110_MAPPED
#if(_PIN_110 == 8)
#undef _PIN_110
#define _PIN_110                                _PIN_110_DDCSCL0
#define _PIN_110_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_110_MAPPED
#if(_PIN_110 == 0x0C)
#undef _PIN_110
#define _PIN_110                                _PIN_110_TEST4B_OUT0
#define _PIN_110_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_110_MAPPED
#if(_PIN_110 == 0x0D)
#undef _PIN_110
#define _PIN_110                                _PIN_110_TEST4B_OUT1
#define _PIN_110_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_110_MAPPED
#if(_PIN_110 == 0x0E)
#undef _PIN_110
#define _PIN_110                                _PIN_110_TEST4B_OUT2
#define _PIN_110_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_110_MAPPED
#if(_PIN_110 == 0x0F)
#undef _PIN_110
#define _PIN_110                                _PIN_110_TEST4B_OUT3
#define _PIN_110_MAPPED                         _ON
#endif
#endif

#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1033
// MCU Ctrl : 0xFE23 at _PIN_111_MCU_REG
//---------------------------------------------------------------------------
#if(_PCB_PINSHARE_MAPPING == _OFF)

#ifndef _PIN_111_MAPPED
#if(_PIN_111 == 8)
#undef _PIN_111
#define _PIN_111                                _PIN_111_DDCSDA0
#define _PIN_111_MAPPED                         _ON
#endif
#endif

#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1034
// MCU Ctrl : 0xFE24 at _PIN_112_MCU_REG
//---------------------------------------------------------------------------
#ifndef _PIN_112_MAPPED
#if(_PIN_112 == 0)
#undef _PIN_112
#define _PIN_112                                _PIN_112_GPI
#define _PIN_112_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_112_MAPPED
#if(_PIN_112 == 1)
#undef _PIN_112
#define _PIN_112                                _PIN_112_GPO_PP
#define _PIN_112_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_112_MAPPED
#if(_PIN_112 == 2)
#undef _PIN_112
#define _PIN_112                                _PIN_112_GPO_OD
#define _PIN_112_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_112_MAPPED
#if(_PIN_112 == 3)
#undef _PIN_112
#define _PIN_112                                _PIN_112_AUXP1
#define _PIN_112_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_112_MAPPED
#if(_PIN_112 == 8)
#undef _PIN_112
#define _PIN_112                                _PIN_112_DDCSCL1
#define _PIN_112_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_112_MAPPED
#if(_PIN_112 == 0x0C)
#undef _PIN_112
#define _PIN_112                                _PIN_112_TEST4B_OUT0
#define _PIN_112_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_112_MAPPED
#if(_PIN_112 == 0x0D)
#undef _PIN_112
#define _PIN_112                                _PIN_112_TEST4B_OUT1
#define _PIN_112_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_112_MAPPED
#if(_PIN_112 == 0x0E)
#undef _PIN_112
#define _PIN_112                                _PIN_112_TEST4B_OUT2
#define _PIN_112_MAPPED                         _ON
#endif
#endif

#ifndef _PIN_112_MAPPED
#if(_PIN_112 == 0x0F)
#undef _PIN_112
#define _PIN_112                                _PIN_112_TEST4B_OUT3
#define _PIN_112_MAPPED                         _ON
#endif
#endif

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1035
// MCU Ctrl : 0xFE25 at _PIN_113_MCU_REG
//---------------------------------------------------------------------------
#ifndef _PIN_113_MAPPED
#if(_PIN_113 == 8)
#undef _PIN_113
#define _PIN_113                                _PIN_113_DDCSDA1
#define _PIN_113_MAPPED                         _ON
#endif
#endif

#endif // End of #if(_PCB_NEW_MODE_SUPPORT == _OFF)

