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
// ID Code      : RL6463_Series_Pinshare.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __RL6463_SERIES_PINSHARE__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GPIO_OPEN_DRAIN                        2

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerPinshareInitial(void);
void ScalerPinsharePowerOnReset(void);

#if(_HW_IIC_SUPPORT == _ON)
void ScalerPinshareHwIICPin(BYTE ucHwIICPinNum);
#endif

void ScalerPinshareGpioDdcPinSwitch(BYTE ucPinType);
void ScalerPinshareAdjustConfig(EnumConfigPin enumConfigPin, EnumPinConfigType enumConfigType);
void ScalerPinshareAdjustFlashDrive(EnumConfigSPIPinType enumConfigFlashDrive, EnumFlashDriveConfigType enumFlashDriveConfig);
void ScalerPinshareAdjustFlashSlewRate(void);
void ScalerPinshareCBUSPinInitialReset(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Pinshare Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareInitial(void)
{
    ScalerSetByte(P10_00_PIN_SHARE_CTRL10___ON, _PIN_21);
    ScalerSetByte(P10_01_PIN_SHARE_CTRL11___ON, _PIN_22);
    ScalerSetByte(P10_02_PIN_SHARE_CTRL12___ON, _PIN_34);
    ScalerSetByte(P10_03_PIN_SHARE_CTRL13___ON, _PIN_35);
    ScalerSetByte(P10_04_PIN_SHARE_CTRL14___ON, _PIN_36);
    ScalerSetByte(P10_05_PIN_SHARE_CTRL15___ON, _PIN_37);
    ScalerSetByte(P10_06_PIN_SHARE_CTRL16___ON, _PIN_38);
    ScalerSetByte(P10_07_PIN_SHARE_CTRL17___ON, _PIN_39);
    ScalerSetByte(P10_08_PIN_SHARE_CTRL30___ON, _PIN_42);
    ScalerSetByte(P10_09_PIN_SHARE_CTRL31___ON, _PIN_43);
    ScalerSetByte(P10_0A_PIN_SHARE_CTRL32___ON, _PIN_44);
    ScalerSetByte(P10_0B_PIN_SHARE_CTRL33___ON, _PIN_45);
    ScalerSetByte(P10_0C_PIN_SHARE_CTRL34___ON, _PIN_46);
    ScalerSetByte(P10_0D_PIN_SHARE_CTRL35___ON, _PIN_47);
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL36___ON, _PIN_48);
    ScalerSetByte(P10_0F_PIN_SHARE_CTRL37___ON, _PIN_49);
    ScalerSetByte(P10_10_PIN_SHARE_CTRL40___ON, _PIN_50);
    ScalerSetByte(P10_11_PIN_SHARE_CTRL41___ON, _PIN_52);
    ScalerSetByte(P10_12_PIN_SHARE_CTRL42___ON, _PIN_53);
    ScalerSetByte(P10_13_PIN_SHARE_CTRL43___ON, _PIN_55);
    ScalerSetByte(P10_14_PIN_SHARE_CTRL44___ON, _PIN_56);
    ScalerSetByte(P10_15_PIN_SHARE_CTRL45___ON, _PIN_57);
    ScalerSetByte(P10_16_PIN_SHARE_CTRL46___ON, _PIN_58);
    ScalerSetByte(P10_17_PIN_SHARE_CTRL47___ON, _PIN_59);
    ScalerSetByte(P10_18_PIN_SHARE_CTRL50___ON, _PIN_60);
    ScalerSetByte(P10_19_PIN_SHARE_CTRL51___ON, _PIN_61);
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL52___ON, _PIN_63);
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL53___ON, _PIN_64);
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL54___ON, _PIN_65);
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL55___LVDS, _PIN_67_OFF_REGION);
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL56___LVDS, _PIN_68_OFF_REGION);
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57___LVDS, _PIN_69_OFF_REGION);
    ScalerSetByte(P10_20_PIN_SHARE_CTRL60___LVDS, _PIN_70_OFF_REGION);
    ScalerSetByte(P10_21_PIN_SHARE_CTRL61___LVDS, _PIN_71_OFF_REGION);
    ScalerSetByte(P10_22_PIN_SHARE_CTRL62___LVDS, _PIN_72_OFF_REGION);
    ScalerSetByte(P10_23_PIN_SHARE_CTRL63___LVDS, _PIN_73_OFF_REGION);
    ScalerSetByte(P10_24_PIN_SHARE_CTRL64___LVDS, _PIN_74_OFF_REGION);
    ScalerSetByte(P10_25_PIN_SHARE_CTRL65___ON, _PIN_90);
    ScalerSetByte(P10_26_PIN_SHARE_CTRL66___ON, _PIN_91);
    ScalerSetByte(P10_27_PIN_SHARE_CTRL67___ON, _PIN_92);
    ScalerSetByte(P10_28_PIN_SHARE_CTRL70___ON, _PIN_93);
    ScalerSetByte(P10_29_PIN_SHARE_CTRL71___ON, _PIN_94);
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL72___ON, _PIN_96);
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL73___ON, _PIN_97);
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL74___ON, _PIN_98);
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL75___ON, _PIN_99);
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL76___PC99, _PIN_100);
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL77___PC99, _PIN_101);
    ScalerSetByte(P10_30_PIN_SHARE_CTRL80___PC99, _PIN_102);
    ScalerSetByte(P10_31_PIN_SHARE_CTRL81___PC99, _PIN_108);
    ScalerSetByte(P10_32_PIN_SHARE_CTRL82___PC99, _PIN_110);
    ScalerSetByte(P10_33_PIN_SHARE_CTRL83___PC99, _PIN_111);
    ScalerSetByte(P10_34_PIN_SHARE_CTRL84___PC99, _PIN_112);
    ScalerSetByte(P10_35_PIN_SHARE_CTRL85___PC99, _PIN_113);
    ScalerSetByte(P10_36_PIN_SHARE_CTRL86___PC99, _PIN_114);
    ScalerSetByte(P10_37_PIN_SHARE_CTRL87___PC99, _PIN_115);

    // Set Pin configure to AC ON
    ScalerPinshareConfig(_POWER_STATUS_AC_ON);

    // Pin Config adjust sample (this is a ineffective configuration example aviod uncall worning)
    ScalerPinshareAdjustConfig(_CONFIG_PIN_START, _GPI);
    ScalerPinshareGpioDdcPinSwitch(0xFF);
}

//--------------------------------------------------
// Description  : Pinshare Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinsharePowerOnReset(void)
{
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL55___LVDS, _PIN_67_OFF_REGION);
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL56___LVDS, _PIN_68_OFF_REGION);
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57___LVDS, _PIN_69_OFF_REGION);
    ScalerSetByte(P10_20_PIN_SHARE_CTRL60___LVDS, _PIN_70_OFF_REGION);
    ScalerSetByte(P10_21_PIN_SHARE_CTRL61___LVDS, _PIN_71_OFF_REGION);
    ScalerSetByte(P10_22_PIN_SHARE_CTRL62___LVDS, _PIN_72_OFF_REGION);
    ScalerSetByte(P10_23_PIN_SHARE_CTRL63___LVDS, _PIN_73_OFF_REGION);
    ScalerSetByte(P10_24_PIN_SHARE_CTRL64___LVDS, _PIN_74_OFF_REGION);
}

#if(_HW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set HW IIC Pin Out
// Input Value  : ucHwIICPinNum --> Pin37_38/47_48/60_61
// Output Value : None
//--------------------------------------------------
void ScalerPinshareHwIICPin(BYTE ucHwIICPinNum)
{
    // Set the selected HwIICPinNum to IIC output
    // Set the others as GPI
    switch(ucHwIICPinNum)
    {
        case _HW_IIC_PIN_37_38:

            if((_PIN_37 == _PIN_37_IICSCL0) && (_PIN_38 == _PIN_38_IICSDA0))
            {
                ScalerSetByte(P10_05_PIN_SHARE_CTRL15___ON, _PIN_37_IICSCL0);
            }

            if((_PIN_47 == _PIN_47_IICSCL1) && (_PIN_48 == _PIN_48_IICSDA1))
            {
                ScalerSetByte(P10_0D_PIN_SHARE_CTRL35___ON, _PIN_47_GPI);
                ScalerSetByte(P10_0E_PIN_SHARE_CTRL36___ON, _PIN_48_GPI);
            }

            if((_PIN_60 == _PIN_60_IICSCL2) && (_PIN_61 == _PIN_61_IICSDA2))
            {
                ScalerSetByte(P10_18_PIN_SHARE_CTRL50___ON, _PIN_60_GPI);
                ScalerSetByte(P10_19_PIN_SHARE_CTRL51___ON, _PIN_61_GPI);
            }
            break;

        case _HW_IIC_PIN_47_48:

            if((_PIN_47 == _PIN_47_IICSCL1) && (_PIN_48 == _PIN_48_IICSDA1))
            {
                ScalerSetByte(P10_0D_PIN_SHARE_CTRL35___ON, _PIN_47_IICSCL1);
            }

            if((_PIN_37 == _PIN_37_IICSCL0) && (_PIN_38 == _PIN_38_IICSDA0))
            {
                ScalerSetByte(P10_05_PIN_SHARE_CTRL15___ON, _PIN_37_GPI);
                ScalerSetByte(P10_06_PIN_SHARE_CTRL16___ON, _PIN_38_GPI);
            }

            if((_PIN_60 == _PIN_60_IICSCL2) && (_PIN_61 == _PIN_61_IICSDA2))
            {
                ScalerSetByte(P10_18_PIN_SHARE_CTRL50___ON, _PIN_60_GPI);
                ScalerSetByte(P10_19_PIN_SHARE_CTRL51___ON, _PIN_61_GPI);
            }

            break;

        case _HW_IIC_PIN_60_61:

            if((_PIN_60 == _PIN_60_IICSCL2) && (_PIN_61 == _PIN_61_IICSDA2))
            {
                ScalerSetByte(P10_18_PIN_SHARE_CTRL50___ON, _PIN_60_IICSCL2);
            }

            if((_PIN_37 == _PIN_37_IICSCL0) && (_PIN_38 == _PIN_38_IICSDA0))
            {
                ScalerSetByte(P10_05_PIN_SHARE_CTRL15___ON, _PIN_37_GPI);
                ScalerSetByte(P10_06_PIN_SHARE_CTRL16___ON, _PIN_38_GPI);
            }

            if((_PIN_47 == _PIN_47_IICSCL1) && (_PIN_48 == _PIN_48_IICSDA1))
            {
                ScalerSetByte(P10_0D_PIN_SHARE_CTRL35___ON, _PIN_47_GPI);
                ScalerSetByte(P10_0E_PIN_SHARE_CTRL36___ON, _PIN_48_GPI);
            }

            break;

        default:

            break;
    }
}
#endif  // End of #if(_HW_IIC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Switch DDC pin to GPIO or viceversa
// Input Value  : ucPinType --> _PIN_58/59-121/122-123/124_GPIO/DDC
// Output Value : None
//--------------------------------------------------
void ScalerPinshareGpioDdcPinSwitch(BYTE ucPinType)
{
    switch(ucPinType)
    {
        case _DDC_VGA_SWITCH_GPIO:
            if(GET_A0_DDC_CHANNEL_SEL() == _VGA_DDC2)
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL76___PC99, _PIN_100_GPO_OD);
                ScalerSetByte(P10_2F_PIN_SHARE_CTRL77___PC99, _PIN_101_GPO_OD);
            }
            else
            {
                ScalerSetByte(P10_0F_PIN_SHARE_CTRL37___ON, _PIN_49_GPO_OD);
                ScalerSetByte(P10_10_PIN_SHARE_CTRL40___ON, _PIN_50_GPO_OD);
            }

            break;

        case _DDC_VGA_SWITCH_DDC:
            if(GET_A0_DDC_CHANNEL_SEL() == _VGA_DDC2)
            {
                ScalerSetByte(P10_2E_PIN_SHARE_CTRL76___PC99, _PIN_100_DDCSCLVGA1);
            }
            else
            {
                ScalerSetByte(P10_0F_PIN_SHARE_CTRL37___ON, _PIN_49_DDCSCLVGA0);
            }

            break;

        case _DDC0_SWITCH_GPIO:

            ScalerSetByte(P10_32_PIN_SHARE_CTRL82___PC99, _PIN_110_GPO_OD);
            ScalerSetByte(P10_33_PIN_SHARE_CTRL83___PC99, _PIN_111_GPO_OD);

            break;

        case _DDC0_SWITCH_DDC:

            ScalerSetByte(P10_32_PIN_SHARE_CTRL82___PC99, _PIN_110_DDCSCL0);

            break;

        case _DDC1_SWITCH_GPIO:

            ScalerSetByte(P10_34_PIN_SHARE_CTRL84___PC99, _PIN_112_GPO_OD);
            ScalerSetByte(P10_35_PIN_SHARE_CTRL85___PC99, _PIN_113_GPO_OD);

            break;

        case _DDC1_SWITCH_DDC:

            ScalerSetByte(P10_34_PIN_SHARE_CTRL84___PC99, _PIN_112_DDCSCL1);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust pin share config
// Input Value  : enumConfigPin  --> Pin num
//                enumConfigTyte --> Pin type(GPIO/PWM..Etc.)
// Output Value : None
//--------------------------------------------------
void ScalerPinshareAdjustConfig(EnumConfigPin enumConfigPin, EnumPinConfigType enumConfigType)
{
    switch(enumConfigPin)
    {
        case _CONFIG_PIN_21:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetByte(P10_00_PIN_SHARE_CTRL10___ON, _PIN_21_GPI);
                    break;

                case _GPO_PP:
                    ScalerSetByte(P10_00_PIN_SHARE_CTRL10___ON, _PIN_21_GPO_PP);
                    break;

                case _GPO_OD:
                    ScalerSetByte(P10_00_PIN_SHARE_CTRL10___ON, _PIN_21_GPO_OD);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_52:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetByte(P10_11_PIN_SHARE_CTRL41___ON, _PIN_52_GPI);
                    break;

                case _GPO_PP:
                    ScalerSetByte(P10_11_PIN_SHARE_CTRL41___ON, _PIN_52_GPO_PP);
                    break;

                case _GPO_OD:
                    ScalerSetByte(P10_11_PIN_SHARE_CTRL41___ON, _PIN_52_GPO_OD);
                    break;

                case _PWM0_PP:
                    ScalerSetByte(P10_11_PIN_SHARE_CTRL41___ON, _PIN_52_PWM0_PP);
                    break;

                case _PWM0_OD:
                    ScalerSetByte(P10_11_PIN_SHARE_CTRL41___ON, _PIN_52_PWM0_OD);
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust Flash SPI Drive config
// Input Value  : enumConfigPin  --> Pin num
//                enumConfigFlashDrive --> Drine Current
// Output Value : None
//--------------------------------------------------
void ScalerPinshareAdjustFlashDrive(EnumConfigSPIPinType enumConfigFlashDrive, EnumFlashDriveConfigType enumFlashDriveConfig)
{
    switch(enumConfigFlashDrive)
    {
        case _CONFIG_PIN_SPI_CLK:

            switch(enumFlashDriveConfig)
            {
                case _SPI_DRIVE_3_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT5 | _BIT4 | _BIT3), _BIT4 | _BIT3);
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT3);
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT4);
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT4 | _BIT3);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_SPI_SI_SO_CEB:

            switch(enumFlashDriveConfig)
            {
                case _SPI_DRIVE_3_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT2 | _BIT1 | _BIT0), _BIT1 | _BIT0);
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT0);
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02___PC99, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1 | _BIT0);
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust Flash SPI Slew-Rate Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareAdjustFlashSlewRate(void)
{
    // Setting Flash SPI Clk Pin Slew-Rate Control
    ScalerSetBit(P10_75_PIN_SLEW_RATE_CTRL0___PC99, ~(_BIT5), (_FLASH_CLK_SLEW_RATE_CONTROL & 0x01) << 5);

    // Setting Flash SPI SI/SO/CEB Pin Slew-Rate Control
    ScalerSetBit(P10_75_PIN_SLEW_RATE_CTRL0___PC99, ~(_BIT4), (_FLASH_SI_SO_CEB_SLEW_RATE_CONTROL & 0x01) << 4);
}

//--------------------------------------------------
// Description  : Reset MHL setting when MHL nonsupport
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareCBUSPinInitialReset(void)
{
    return;
}

