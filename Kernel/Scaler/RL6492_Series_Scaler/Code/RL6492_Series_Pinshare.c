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
// ID Code      : RL6492_Series_Pinshare.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_PINSHARE__

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

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
void ScalerPinshareTYCPinResistorTrimmingControl(void);
#endif

#if(_D0_DP_EXIST == _ON)
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
void ScalerPinshareRx0TypeCPinAssert(EnumTypeCOrientation enumTypeCOrientation);
void ScalerPinshareRx0TypeCPinAssert_EXINT0(EnumTypeCOrientation enumTypeCOrientation);
#endif
#endif
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
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_EMBEDDED)
    ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, (BYTE)_PIN_7);
    ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, (BYTE)_PIN_8);
#else
    // TC Config Port Need Input Mode for PIN7/8
    ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, _PIN_7_GPI);
    ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, _PIN_7_GPI);
#endif
    ScalerSetByte(P10_02_PIN_SHARE_CTRL02__ON1, (BYTE)_PIN_9);
    ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, (BYTE)_PIN_10);
    ScalerSetByte(P10_04_PIN_SHARE_CTRL04__ON1, (BYTE)_PIN_11);
    ScalerSetByte(P10_06_PIN_SHARE_CTRL06__ON1, (BYTE)_PIN_14);
    ScalerSetByte(P10_07_PIN_SHARE_CTRL07__ON1, (BYTE)_PIN_15);
    ScalerSetByte(P10_08_PIN_SHARE_CTRL08__ON1, (BYTE)_PIN_16);
    ScalerSetByte(P10_09_PIN_SHARE_CTRL09__ON1, (BYTE)_PIN_17);
    ScalerSetByte(P10_0A_PIN_SHARE_CTRL0A__ON1, (BYTE)_PIN_18);
    ScalerSetByte(P10_0B_PIN_SHARE_CTRL0B__ON1, (BYTE)_PIN_19);
    ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON1, (BYTE)_PIN_20);
    ScalerSetByte(P10_0D_PIN_SHARE_CTRL0D__ON1, (BYTE)_PIN_21);
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL0E__ON1, (BYTE)_PIN_22);
    ScalerSetByte(P10_0F_PIN_SHARE_CTRL0F__ON1, (BYTE)_PIN_23);
    ScalerSetByte(P10_10_PIN_SHARE_CTRL10__ON1, (BYTE)_PIN_24);
    ScalerSetByte(P10_12_PIN_SHARE_CTRL12__ON1, (BYTE)_PIN_29);
    ScalerSetByte(P10_13_PIN_SHARE_CTRL13__ON1, (BYTE)_PIN_30);
    ScalerSetByte(P10_14_PIN_SHARE_CTRL14__ON1, (BYTE)_PIN_32);
    ScalerSetByte(P10_15_PIN_SHARE_CTRL15__ON1, (BYTE)_PIN_33);
    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON1, (BYTE)_PIN_37);
    ScalerSetByte(P10_17_PIN_SHARE_CTRL17__ON1, (BYTE)_PIN_38);
    ScalerSetByte(P10_18_PIN_SHARE_CTRL18__ON1, (BYTE)_PIN_39);
    ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON1, (BYTE)_PIN_40);
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL1A__ON1, (BYTE)_PIN_41);
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL1B__ON1, (BYTE)_PIN_42);
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__ON1, (BYTE)_PIN_43);
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL1D__ON1, (BYTE)_PIN_44);
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL1E__ON1, (BYTE)_PIN_45);
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL1F__ON1, (BYTE)_PIN_46);
    ScalerSetByte(P10_20_PIN_SHARE_CTRL20__OFF1, (BYTE)_PIN_58_OFF_REGION);
    ScalerSetByte(P10_21_PIN_SHARE_CTRL21__OFF1, (BYTE)_PIN_59_OFF_REGION);
    ScalerSetByte(P10_22_PIN_SHARE_CTRL22__OFF1, (BYTE)_PIN_60_OFF_REGION);
    ScalerSetByte(P10_23_PIN_SHARE_CTRL23__OFF1, (BYTE)_PIN_61_OFF_REGION);
    ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF1, (BYTE)_PIN_62_OFF_REGION);
    ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF1, (BYTE)_PIN_63_OFF_REGION);
    ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF1, (BYTE)_PIN_64_OFF_REGION);
    ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF1, (BYTE)_PIN_65_OFF_REGION);
    ScalerSetByte(P10_28_PIN_SHARE_CTRL28__OFF1, (BYTE)_PIN_66_OFF_REGION);
    ScalerSetByte(P10_29_PIN_SHARE_CTRL29__OFF1, (BYTE)_PIN_67_OFF_REGION);
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__ON1, (BYTE)_PIN_69);
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__ON1, (BYTE)_PIN_70);
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL2C__ON1, (BYTE)_PIN_71);
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL2D__ON1, (BYTE)_PIN_72);
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__ON1, (BYTE)_PIN_73);
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__ON1, (BYTE)_PIN_74);
    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__ON1, (BYTE)_PIN_75);
    ScalerSetByte(P10_31_PIN_SHARE_CTRL31__ON1, (BYTE)_PIN_78);
    ScalerSetByte(P10_32_PIN_SHARE_CTRL32__ON1, (BYTE)_PIN_80);
    ScalerSetByte(P10_33_PIN_SHARE_CTRL33__ON1, (BYTE)_PIN_79);
    ScalerSetByte(P10_34_PIN_SHARE_CTRL34__ON1, (BYTE)_PIN_81);
    ScalerSetByte(P10_35_PIN_SHARE_CTRL35__ON1, (BYTE)_PIN_82);
    ScalerSetByte(P10_36_PIN_SHARE_CTRL36__ON1, (BYTE)_PIN_83);
    ScalerSetByte(P10_37_PIN_SHARE_CTRL37__ON1, (BYTE)_PIN_84);
    ScalerSetByte(P10_38_PIN_SHARE_CTRL38__ON1, (BYTE)_PIN_85);
    ScalerSetByte(P10_39_PIN_SHARE_CTRL39__ON1, (BYTE)_PIN_91);
    ScalerSetByte(P10_3A_PIN_SHARE_CTRL3A__ON1, (BYTE)_PIN_86);
    ScalerSetByte(P10_3B_PIN_SHARE_CTRL3B__ON1, (BYTE)_PIN_87);
    ScalerSetByte(P10_3C_PIN_SHARE_CTRL3C__ON1, (BYTE)_PIN_88);
    ScalerSetByte(P10_3D_PIN_SHARE_CTRL3D__ON1, (BYTE)_PIN_89);
    ScalerSetByte(P10_3E_PIN_SHARE_CTRL3E__ON1, (BYTE)_PIN_97);
    ScalerSetByte(P10_3F_PIN_SHARE_CTRL3F__ON1, (BYTE)_PIN_98);
    ScalerSetByte(P10_40_PIN_SHARE_CTRL40__ON1, (BYTE)_PIN_99);
    ScalerSetByte(P10_41_PIN_SHARE_CTRL41__ON1, (BYTE)_PIN_100);

    // Set Pin configure to AC ON
    ScalerPinshareConfig(_POWER_STATUS_AC_ON);

    // Pin Config adjust sample (this is a ineffective configuration example aviod uncall worning)
    ScalerPinshareAdjustConfig(_CONFIG_PIN_START, _GPI);
    ScalerPinshareGpioDdcPinSwitch(0xFF);

    // Set Bounding Option Pin12/36 Initial Push-Pull Mode
    ScalerSetByte(P10_05_PIN_SHARE_CTRL05__ON1, 0x01);
    ScalerSetByte(P10_11_PIN_SHARE_CTRL11__ON1, 0x01);

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
    ScalerPinshareTYCPinResistorTrimmingControl();
#endif

#ifdef _PINSHARE_IO_TOGGLE_SUPPORT
    ScalerPinshareIOToggle();
#endif
}

//--------------------------------------------------
// Description  : Pinshare Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinsharePowerOnReset(void)
{
    ScalerSetByte(P10_20_PIN_SHARE_CTRL20__OFF1, (BYTE)_PIN_58_OFF_REGION);
    ScalerSetByte(P10_21_PIN_SHARE_CTRL21__OFF1, (BYTE)_PIN_59_OFF_REGION);
    ScalerSetByte(P10_22_PIN_SHARE_CTRL22__OFF1, (BYTE)_PIN_60_OFF_REGION);
    ScalerSetByte(P10_23_PIN_SHARE_CTRL23__OFF1, (BYTE)_PIN_61_OFF_REGION);
    ScalerSetByte(P10_24_PIN_SHARE_CTRL24__OFF1, (BYTE)_PIN_62_OFF_REGION);
    ScalerSetByte(P10_25_PIN_SHARE_CTRL25__OFF1, (BYTE)_PIN_63_OFF_REGION);
    ScalerSetByte(P10_26_PIN_SHARE_CTRL26__OFF1, (BYTE)_PIN_64_OFF_REGION);
    ScalerSetByte(P10_27_PIN_SHARE_CTRL27__OFF1, (BYTE)_PIN_65_OFF_REGION);
    ScalerSetByte(P10_28_PIN_SHARE_CTRL28__OFF1, (BYTE)_PIN_66_OFF_REGION);
    ScalerSetByte(P10_29_PIN_SHARE_CTRL29__OFF1, (BYTE)_PIN_67_OFF_REGION);
}

#if(_HW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set HW IIC Pin Out
// Input Value  : ucHwIICPinNum --> Pin26_27/39_40/52_53/60_61/62_63
// Output Value : None
//--------------------------------------------------
void ScalerPinshareHwIICPin(BYTE ucHwIICPinNum)
{
    // Set the selected HwIICPinNum to IIC output
    // Set the others as GPI
    switch(ucHwIICPinNum)
    {
        case _HW_IIC_PIN_20_21:

            if((_PIN_20 == _PIN_20_IICSCL2) && (_PIN_21 == _PIN_21_IICSDA2))
            {
                ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON1, _PIN_20_IICSCL2);
            }
            if((_PIN_40 == _PIN_40_EEIICSCL) && (_PIN_41 == _PIN_41_EEIICSDA))
            {
                ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON1, _PIN_40_GPI);
                ScalerSetByte(P10_1A_PIN_SHARE_CTRL1A__ON1, _PIN_41_GPI);
            }
            if((_PIN_80 == _PIN_80_IICSCL1) && (_PIN_79 == _PIN_79_IICSDA1))
            {
                ScalerSetByte(P10_32_PIN_SHARE_CTRL32__ON1, _PIN_80_GPI);
                ScalerSetByte(P10_33_PIN_SHARE_CTRL33__ON1, _PIN_79_GPI);
            }
            break;

        case _HW_IIC_PIN_40_41:

            if((_PIN_40 == _PIN_40_EEIICSCL) && (_PIN_41 == _PIN_41_EEIICSDA))
            {
                ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON1, _PIN_40_EEIICSCL);
            }
            if((_PIN_20 == _PIN_20_IICSCL2) && (_PIN_21 == _PIN_21_IICSDA2))
            {
                ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON1, _PIN_20_GPI);
                ScalerSetByte(P10_0D_PIN_SHARE_CTRL0D__ON1, _PIN_21_GPI);
            }
            if((_PIN_80 == _PIN_80_IICSCL1) && (_PIN_79 == _PIN_79_IICSDA1))
            {
                ScalerSetByte(P10_32_PIN_SHARE_CTRL32__ON1, _PIN_80_GPI);
                ScalerSetByte(P10_33_PIN_SHARE_CTRL33__ON1, _PIN_79_GPI);
            }
            break;

        case _HW_IIC_PIN_80_79:

            if((_PIN_80 == _PIN_80_IICSCL1) && (_PIN_79 == _PIN_79_IICSDA1))
            {
                ScalerSetByte(P10_32_PIN_SHARE_CTRL32__ON1, _PIN_80_IICSCL1);
            }
            if((_PIN_20 == _PIN_20_IICSCL2) && (_PIN_21 == _PIN_21_IICSDA2))
            {
                ScalerSetByte(P10_0C_PIN_SHARE_CTRL0C__ON1, _PIN_20_GPI);
                ScalerSetByte(P10_0D_PIN_SHARE_CTRL0D__ON1, _PIN_21_GPI);
            }
            if((_PIN_40 == _PIN_40_EEIICSCL) && (_PIN_41 == _PIN_41_EEIICSDA))
            {
                ScalerSetByte(P10_19_PIN_SHARE_CTRL19__ON1, _PIN_40_GPI);
                ScalerSetByte(P10_1A_PIN_SHARE_CTRL1A__ON1, _PIN_41_GPI);
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
            ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, _PIN_10_GPO_OD);
            ScalerSetByte(P10_04_PIN_SHARE_CTRL04__ON1, _PIN_11_GPO_OD);
            break;

        case _DDC_VGA_SWITCH_DDC:
            ScalerSetByte(P10_03_PIN_SHARE_CTRL03__ON1, _PIN_10_DDCSCLVGA);
            break;

        case _DDC2_SWITCH_GPIO:
            ScalerSetByte(P10_3E_PIN_SHARE_CTRL3E__ON1, _PIN_97_GPO_OD);
            ScalerSetByte(P10_3F_PIN_SHARE_CTRL3F__ON1, _PIN_98_GPO_OD);
            break;

        case _DDC2_SWITCH_DDC:
            ScalerSetByte(P10_3E_PIN_SHARE_CTRL3E__ON1, _PIN_97_DDCSCL2);
            break;

        case _DDC1_SWITCH_GPIO:
            ScalerSetByte(P10_40_PIN_SHARE_CTRL40__ON1, _PIN_99_GPO_OD);
            ScalerSetByte(P10_41_PIN_SHARE_CTRL41__ON1, _PIN_100_GPO_OD);
            break;

        case _DDC1_SWITCH_DDC:
            ScalerSetByte(P10_40_PIN_SHARE_CTRL40__ON1, _PIN_99_DDCSCL1);
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
    enumConfigPin = enumConfigPin;
    enumConfigType = enumConfigType;
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
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT5 | _BIT4 | _BIT3), _BIT4 | _BIT3);
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT3);
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT4);
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT4 | _BIT3);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_SPI_SI_SO_CEB:

            switch(enumFlashDriveConfig)
            {
                case _SPI_DRIVE_3_0MA:
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT2 | _BIT1 | _BIT0), _BIT1 | _BIT0);
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT0);
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ON1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1 | _BIT0);
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
    ScalerSetBit(P10_80_PIN_SLEW_RATE_CTRL00__ON1, ~(_BIT7), (_FLASH_CLK_SLEW_RATE_CONTROL & 0x01) << 7);

    // Setting Flash SPI SI/SO/CEB Pin Slew-Rate Control
    ScalerSetBit(P10_80_PIN_SLEW_RATE_CTRL00__ON1, ~(_BIT6), (_FLASH_SI_SO_CEB_SLEW_RATE_CONTROL & 0x01) << 6);
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

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Pinshare TYPE C 1M ohm Trimming control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareTYCPinResistorTrimmingControl(void)
{
    BYTE ucEfuseDriv = 0;

    // load TYPEC Pin 1M Ohm Trimming
    ScalerEfuseGetData(_EFUSE_TYPE_C_1M_OHM_RESISTOR, 1, &ucEfuseDriv);
    ScalerSetByte(P10_46_1M_TRIM_CTRL0__ON1, ucEfuseDriv);
}
#endif

#if(_D0_DP_EXIST == _ON)
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
//--------------------------------------------------
// Description  : Lane Swap
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerPinshareRx0TypeCPinAssert(EnumTypeCOrientation enumTypeCOrientation)
{
    // AUX Setting
    switch(enumTypeCOrientation)
    {
        case _TYPE_C_ORIENTATION_NONE:

            // Pin 7 Pinshare Config : Input Mode
            ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, _PIN_7_GPI);

            // Pin 8 Pinshare Config : Input Mode
            ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, _PIN_8_GPI);

            // Pin 15 AUX-P Pull/Down Disable
            ScalerSetBit(P10_A1_PIN_PULLUP_CTRL01__ON1, ~(_BIT1 | _BIT0), 0x00);

            // Pin 16 AUX-N Pull/Down Disable
            ScalerSetBit(P10_A2_PIN_PULLUP_CTRL02__ON1, ~(_BIT7 | _BIT6), 0x00);

            break;

        case _TYPE_C_ORIENTATION_UNFLIP:

            // Pin 7 Pinshare Config : AUX Mode
            ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, _PIN_7_AUXP0);

            // Pin 8 Pinshare Config : AUX Mode
            ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, _PIN_8_AUXN0);

            // Pin 15 AUX-P Pull Low
            ScalerSetBit(P10_A1_PIN_PULLUP_CTRL01__ON1, ~(_BIT1 | _BIT0), _BIT1);

            // Pin 16 AUX-N Pull High
            ScalerSetBit(P10_A2_PIN_PULLUP_CTRL02__ON1, ~(_BIT7 | _BIT6), _BIT6);

            break;

        case _TYPE_C_ORIENTATION_FLIP:

            // Pin 7 Pinshare Config : AUX Mode
            ScalerSetByte(P10_00_PIN_SHARE_CTRL00__ON1, _PIN_7_AUXP0);

            // Pin 8 Pinshare Config : AUX Mode
            ScalerSetByte(P10_01_PIN_SHARE_CTRL01__ON1, _PIN_8_AUXN0);

            // Pin 15 AUX-P Pull High
            ScalerSetBit(P10_A1_PIN_PULLUP_CTRL01__ON1, ~(_BIT1 | _BIT0), _BIT0);

            // Pin 16 AUX-N Pull Low
            ScalerSetBit(P10_A2_PIN_PULLUP_CTRL02__ON1, ~(_BIT7 | _BIT6), _BIT7);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Lane Swap
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerPinshareRx0TypeCPinAssert_EXINT0(EnumTypeCOrientation enumTypeCOrientation) using 1
{
    // AUX Setting
    switch(enumTypeCOrientation)
    {
        case _TYPE_C_ORIENTATION_NONE:

            // Pin 7 Pinshare Config : Input Mode
            ScalerSetByte_EXINT(P10_00_PIN_SHARE_CTRL00__ON1, _PIN_7_GPI);

            // Pin 8 Pinshare Config : Input Mode
            ScalerSetByte_EXINT(P10_01_PIN_SHARE_CTRL01__ON1, _PIN_8_GPI);

            // Pin 15 AUX-P Pull/Down Disable
            ScalerSetBit_EXINT(P10_A1_PIN_PULLUP_CTRL01__ON1, ~(_BIT1 | _BIT0), 0x00);

            // Pin 16 AUX-N Pull/Down Disable
            ScalerSetBit_EXINT(P10_A2_PIN_PULLUP_CTRL02__ON1, ~(_BIT7 | _BIT6), 0x00);

            break;

        case _TYPE_C_ORIENTATION_UNFLIP:

            // Pin 7 Pinshare Config : Input Mode
            ScalerSetByte_EXINT(P10_00_PIN_SHARE_CTRL00__ON1, _PIN_7_AUXP0);

            // Pin 8 Pinshare Config : Input Mode
            ScalerSetByte_EXINT(P10_01_PIN_SHARE_CTRL01__ON1, _PIN_8_AUXN0);

            // Pin 15 AUX-P Pull Low
            ScalerSetBit_EXINT(P10_A1_PIN_PULLUP_CTRL01__ON1, ~(_BIT1 | _BIT0), _BIT1);

            // Pin 16 AUX-N Pull High
            ScalerSetBit_EXINT(P10_A2_PIN_PULLUP_CTRL02__ON1, ~(_BIT7 | _BIT6), _BIT6);

            break;

        case _TYPE_C_ORIENTATION_FLIP:

            // Pin 7 Pinshare Config : Input Mode
            ScalerSetByte_EXINT(P10_00_PIN_SHARE_CTRL00__ON1, _PIN_7_AUXP0);

            // Pin 8 Pinshare Config : Input Mode
            ScalerSetByte_EXINT(P10_01_PIN_SHARE_CTRL01__ON1, _PIN_8_AUXN0);

            // Pin 15 AUX-P Pull High
            ScalerSetBit_EXINT(P10_A1_PIN_PULLUP_CTRL01__ON1, ~(_BIT1 | _BIT0), _BIT0);

            // Pin 16 AUX-N Pull Low
            ScalerSetBit_EXINT(P10_A2_PIN_PULLUP_CTRL02__ON1, ~(_BIT7 | _BIT6), _BIT7);

            break;

        default:
            break;
    }
}
#endif
#endif

