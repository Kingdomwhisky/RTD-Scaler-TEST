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
// ID Code      : RL6449_Series_Pinshare.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6449_SERIES_PINSHARE__

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
    ScalerSetByte(P10_00_PIN_SHARE_CTRL10__ADION, (BYTE)_PIN_1);
    ScalerSetByte(P10_01_PIN_SHARE_CTRL11__ADION, (BYTE)_PIN_14);

    // Check if pin_65-66 are assigned to DDCVGA
#if((_PIN_65 == 8) && (_PIN_66 == 8))
    ScalerPinshareGpioDdcPinSwitch(_DDC_VGA_SWITCH_DDC);
#else
    ScalerSetBit(P10_02_PIN_SHARE_CTRL12__ADION, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_65)));
    ScalerSetByte(P10_03_PIN_SHARE_CTRL13__ADION, (BYTE)_PIN_66);
#endif

    ScalerSetByte(P10_04_PIN_SHARE_CTRL14__ADION, (BYTE)_PIN_67);
    ScalerSetByte(P10_05_PIN_SHARE_CTRL15__ADION, (BYTE)_PIN_68);
    ScalerSetByte(P10_06_PIN_SHARE_CTRL16__ADION, (BYTE)_PIN_69);
    ScalerSetByte(P10_07_PIN_SHARE_CTRL17__ADION, (BYTE)_PIN_70);
    ScalerSetByte(P10_08_PIN_SHARE_CTRL30__ADION, (BYTE)_PIN_71);
    ScalerSetByte(P10_09_PIN_SHARE_CTRL31__ADION, (BYTE)_PIN_74);
    ScalerSetByte(P10_0A_PIN_SHARE_CTRL32__ADION, (BYTE)_PIN_75);
    ScalerSetByte(P10_0B_PIN_SHARE_CTRL33__ADION, (BYTE)_PIN_76);
    ScalerSetByte(P10_0C_PIN_SHARE_CTRL34__ADION, (BYTE)_PIN_77);
    ScalerSetByte(P10_0D_PIN_SHARE_CTRL35__ADION, (BYTE)_PIN_91);
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL36__ADION, (BYTE)_PIN_92);
    ScalerSetByte(P10_0F_PIN_SHARE_CTRL37__ADION, (BYTE)_PIN_94);

    ScalerSetByte(P10_10_PIN_SHARE_CTRL40__ADION, (BYTE)_PIN_95);
    ScalerSetByte(P10_11_PIN_SHARE_CTRL41__ADION, (BYTE)_PIN_96);
    ScalerSetByte(P10_12_PIN_SHARE_CTRL42__ADION, (BYTE)_PIN_97);
    ScalerSetByte(P10_13_PIN_SHARE_CTRL43__TOPOFF, (BYTE)_PIN_109_OFF_REGION);
    ScalerSetByte(P10_14_PIN_SHARE_CTRL44__TOPOFF, (BYTE)_PIN_110_OFF_REGION);
    ScalerSetByte(P10_15_PIN_SHARE_CTRL45__TOPOFF, (BYTE)_PIN_113_OFF_REGION);
    ScalerSetByte(P10_16_PIN_SHARE_CTRL46__TOPOFF, (BYTE)_PIN_114_OFF_REGION);
    ScalerSetByte(P10_17_PIN_SHARE_CTRL47__TOPOFF, (BYTE)_PIN_115_OFF_REGION);
    ScalerSetByte(P10_18_PIN_SHARE_CTRL50__TOPOFF, (BYTE)_PIN_116_OFF_REGION);
    ScalerSetByte(P10_19_PIN_SHARE_CTRL51__TOPOFF, (BYTE)_PIN_117_OFF_REGION);
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL52__TOPOFF, (BYTE)_PIN_143_OFF_REGION);
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL53__TOPOFF, (BYTE)_PIN_144_OFF_REGION);
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL54__TOPOFF, (BYTE)_PIN_145_OFF_REGION);
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL55__TOPOFF, (BYTE)_PIN_146_OFF_REGION);
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL56__TOPOFF, (BYTE)_PIN_147_OFF_REGION);
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57__TOPOFF, (BYTE)_PIN_148_OFF_REGION);

    // Check if pin 149-150 are assigned to IIC1
#if((_PIN_149_OFF_REGION == 8) && (_PIN_150_OFF_REGION == 8))
    ScalerSetBit(P10_20_PIN_SHARE_CTRL60__TOPOFF, ~_BIT7, _BIT7);  // Enable IIC1
#else
    ScalerSetBit(P10_20_PIN_SHARE_CTRL60__TOPOFF, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_149_OFF_REGION);
    ScalerSetByte(P10_21_PIN_SHARE_CTRL61__TOPOFF, (BYTE)_PIN_150_OFF_REGION);
#endif

    ScalerSetByte(P10_22_PIN_SHARE_CTRL62__TOPOFF, (BYTE)_PIN_151_OFF_REGION);
    ScalerSetByte(P10_23_PIN_SHARE_CTRL63__TOPOFF, (BYTE)_PIN_152_OFF_REGION);

    // Check if pin153-157 are assigned to USB_SPI
#if((_PIN_153_OFF_REGION == 8) && (_PIN_154_OFF_REGION == 8) && (_PIN_155_OFF_REGION == 8) && (_PIN_156_OFF_REGION == 8) && (_PIN_157_OFF_REGION == 8))
    ScalerSetBit(P10_24_PIN_SHARE_CTRL64__TOPOFF, ~_BIT7, _BIT7); // Enable USB_IIC
#else
    ScalerSetBit(P10_24_PIN_SHARE_CTRL64__TOPOFF, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_153_OFF_REGION);
    ScalerSetByte(P10_25_PIN_SHARE_CTRL65__TOPOFF, (BYTE)_PIN_154_OFF_REGION);
    ScalerSetByte(P10_26_PIN_SHARE_CTRL66__TOPOFF, (BYTE)_PIN_155_OFF_REGION);
    ScalerSetByte(P10_27_PIN_SHARE_CTRL67__TOPOFF, (BYTE)_PIN_156_OFF_REGION);
    ScalerSetByte(P10_28_PIN_SHARE_CTRL70__TOPOFF, (BYTE)_PIN_157_OFF_REGION);
#endif

    ScalerSetByte(P10_29_PIN_SHARE_CTRL71__TOPOFF, (BYTE)_PIN_158_OFF_REGION);
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL72__TOPOFF, (BYTE)_PIN_159_OFF_REGION);
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL73__TOPOFF, (BYTE)_PIN_160_OFF_REGION);
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL74__TOPOFF, (BYTE)_PIN_161_OFF_REGION);
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL75__TOPOFF, (BYTE)_PIN_163_OFF_REGION);
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL76__TOPOFF, (BYTE)_PIN_164_OFF_REGION);
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL77__TOPOFF, (BYTE)_PIN_165_OFF_REGION);

    ScalerSetByte(P10_30_PIN_SHARE_CTRL80__TOPOFF, (BYTE)_PIN_166_OFF_REGION);
    ScalerSetByte(P10_31_PIN_SHARE_CTRL81__TOPON, (BYTE)_PIN_179);
    ScalerSetByte(P10_32_PIN_SHARE_CTRL82__TOPON, (BYTE)_PIN_180);
    ScalerSetByte(P10_33_PIN_SHARE_CTRL83__TOPON, (BYTE)_PIN_181);
    ScalerSetByte(P10_34_PIN_SHARE_CTRL84__TOPON, (BYTE)_PIN_184);
    ScalerSetByte(P10_35_PIN_SHARE_CTRL85__TOPON, (BYTE)_PIN_185);
    ScalerSetByte(P10_36_PIN_SHARE_CTRL86__TOPON, (BYTE)_PIN_190);
    ScalerSetByte(P10_37_PIN_SHARE_CTRL87__ADION, (BYTE)_PIN_193);
    ScalerSetByte(P10_38_PIN_SHARE_CTRL90__ADION, (BYTE)_PIN_194);
    ScalerSetByte(P10_39_PIN_SHARE_CTRL91__ADION, (BYTE)_PIN_195);
    ScalerSetByte(P10_3A_PIN_SHARE_CTRL92__ADION, (BYTE)_PIN_196);
    ScalerSetByte(P10_3B_PIN_SHARE_CTRL93__ADION, (BYTE)_PIN_197);
    ScalerSetByte(P10_3C_PIN_SHARE_CTRL94__ADION, (BYTE)_PIN_198);
    ScalerSetByte(P10_3D_PIN_SHARE_CTRL95__ADION, (BYTE)_PIN_199);

    // Check if pin 200-201 are assigned to EEIIC2
#if((_PIN_200 == 8) && (_PIN_201 == 8))
    ScalerSetBit(P10_3E_PIN_SHARE_CTRL96__ADION, ~_BIT7, _BIT7); // Enable IIC2
#else
    ScalerSetBit(P10_3E_PIN_SHARE_CTRL96__ADION, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_200);
    ScalerSetByte(P10_3F_PIN_SHARE_CTRL97__ADION, (BYTE)_PIN_201);
#endif

    // Check if pin 202-203 are assigned to TXD/RXD
#if((_PIN_202 == 8) && (_PIN_203 == 8))
    ScalerSetBit(P10_40_PIN_SHARE_CTRLA0__ADION, ~_BIT7, _BIT7); // Enable TXD/RXD
#else
    ScalerSetBit(P10_40_PIN_SHARE_CTRLA0__ADION, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_202);
    ScalerSetByte(P10_41_PIN_SHARE_CTRLA1__ADION, (BYTE)_PIN_203);
#endif

    ScalerSetByte(P10_42_PIN_SHARE_CTRLA2__ADION, (BYTE)_PIN_204);
    ScalerSetByte(P10_43_PIN_SHARE_CTRLA3__ADION, (BYTE)_PIN_206);
    ScalerSetByte(P10_44_PIN_SHARE_CTRLA4__ADION, (BYTE)_PIN_207);
    ScalerSetByte(P10_45_PIN_SHARE_CTRLA5__ADION, (BYTE)_PIN_208);
    ScalerSetByte(P10_46_PIN_SHARE_CTRLA6__ADION, (BYTE)_PIN_209);

    // Check if pin 210-211 are assigned to EEIIC1
#if((_PIN_210 == 8) && (_PIN_211 == 8))
    ScalerSetBit(P10_47_PIN_SHARE_CTRLA7__ADION, ~_BIT7, _BIT7); // Enable IIC1
#else
    ScalerSetBit(P10_47_PIN_SHARE_CTRLA7__ADION, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_210);
    ScalerSetByte(P10_48_PIN_SHARE_CTRLB0__ADION, (BYTE)_PIN_211);
#endif

    // Check if pin_212-213 are assigned to DDC2
#if((_PIN_212 == 8) && (_PIN_213 == 8))
    ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_DDC);
#else
    ScalerSetBit(P10_49_PIN_SHARE_CTRLB1__ADION, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_212)));
    ScalerSetByte(P10_4A_PIN_SHARE_CTRLB2__ADION, (BYTE)_PIN_213);
#endif

    // Check if pin_214-215 are assigned to DDC3
#if((_PIN_214 == 8) && (_PIN_215 == 8))
    ScalerPinshareGpioDdcPinSwitch(_DDC3_SWITCH_DDC);
#else
    ScalerSetBit(P10_4B_PIN_SHARE_CTRLB3__ADION, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_214)));
    ScalerSetByte(P10_4C_PIN_SHARE_CTRLB4__ADION, (BYTE)_PIN_215);
#endif

    // All DDC Channel Driving Current Set High
    ScalerSetBit(P10_C0_PIN_DRIVING_CTRL00__ADION, ~_BIT7, _BIT7);
    ScalerSetBit(P10_C3_PIN_DRIVING_CTRL03__ADION, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // Set Pin configure to AC ON
    ScalerPinshareConfig(_POWER_STATUS_AC_ON);

    // Pin Config adjust sample (this is a ineffective configuration example aviod uncall worning)
    ScalerPinshareAdjustConfig(_CONFIG_PIN_START, _GPI);
}

//--------------------------------------------------
// Description  : Pinshare OFF zone Settings in Power On
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinsharePowerOnReset(void)
{
    ScalerSetByte(P10_13_PIN_SHARE_CTRL43__TOPOFF, (BYTE)_PIN_109_OFF_REGION);
    ScalerSetByte(P10_14_PIN_SHARE_CTRL44__TOPOFF, (BYTE)_PIN_110_OFF_REGION);
    ScalerSetByte(P10_15_PIN_SHARE_CTRL45__TOPOFF, (BYTE)_PIN_113_OFF_REGION);
    ScalerSetByte(P10_16_PIN_SHARE_CTRL46__TOPOFF, (BYTE)_PIN_114_OFF_REGION);
    ScalerSetByte(P10_17_PIN_SHARE_CTRL47__TOPOFF, (BYTE)_PIN_115_OFF_REGION);
    ScalerSetByte(P10_18_PIN_SHARE_CTRL50__TOPOFF, (BYTE)_PIN_116_OFF_REGION);
    ScalerSetByte(P10_19_PIN_SHARE_CTRL51__TOPOFF, (BYTE)_PIN_117_OFF_REGION);
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL52__TOPOFF, (BYTE)_PIN_143_OFF_REGION);
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL53__TOPOFF, (BYTE)_PIN_144_OFF_REGION);
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL54__TOPOFF, (BYTE)_PIN_145_OFF_REGION);
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL55__TOPOFF, (BYTE)_PIN_146_OFF_REGION);
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL56__TOPOFF, (BYTE)_PIN_147_OFF_REGION);
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57__TOPOFF, (BYTE)_PIN_148_OFF_REGION);

    // Check if pin 149-150 are assigned to IIC1
#if((_PIN_149_OFF_REGION == 8) && (_PIN_150_OFF_REGION == 8))
    ScalerSetBit(P10_20_PIN_SHARE_CTRL60__TOPOFF, ~_BIT7, _BIT7);  // Enable IIC1
#else
    ScalerSetBit(P10_20_PIN_SHARE_CTRL60__TOPOFF, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_149_OFF_REGION);
    ScalerSetByte(P10_21_PIN_SHARE_CTRL61__TOPOFF, (BYTE)_PIN_150_OFF_REGION);
#endif
    ScalerSetByte(P10_22_PIN_SHARE_CTRL62__TOPOFF, (BYTE)_PIN_151_OFF_REGION);
    ScalerSetByte(P10_23_PIN_SHARE_CTRL63__TOPOFF, (BYTE)_PIN_152_OFF_REGION);

    // Check if pin153-157 are assigned to USB_SPI
#if((_PIN_153_OFF_REGION == 8) && (_PIN_154_OFF_REGION == 8) && (_PIN_155_OFF_REGION == 8) && (_PIN_156_OFF_REGION == 8) && (_PIN_157_OFF_REGION == 8))
    ScalerSetBit(P10_24_PIN_SHARE_CTRL64__TOPOFF, ~_BIT7, _BIT7); // Enable USB_IIC
#else
    ScalerSetBit(P10_24_PIN_SHARE_CTRL64__TOPOFF, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_153_OFF_REGION);
    ScalerSetByte(P10_25_PIN_SHARE_CTRL65__TOPOFF, (BYTE)_PIN_154_OFF_REGION);
    ScalerSetByte(P10_26_PIN_SHARE_CTRL66__TOPOFF, (BYTE)_PIN_155_OFF_REGION);
    ScalerSetByte(P10_27_PIN_SHARE_CTRL67__TOPOFF, (BYTE)_PIN_156_OFF_REGION);
    ScalerSetByte(P10_28_PIN_SHARE_CTRL70__TOPOFF, (BYTE)_PIN_157_OFF_REGION);
#endif
    ScalerSetByte(P10_29_PIN_SHARE_CTRL71__TOPOFF, (BYTE)_PIN_158_OFF_REGION);
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL72__TOPOFF, (BYTE)_PIN_159_OFF_REGION);
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL73__TOPOFF, (BYTE)_PIN_160_OFF_REGION);
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL74__TOPOFF, (BYTE)_PIN_161_OFF_REGION);
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL75__TOPOFF, (BYTE)_PIN_163_OFF_REGION);
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL76__TOPOFF, (BYTE)_PIN_164_OFF_REGION);
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL77__TOPOFF, (BYTE)_PIN_165_OFF_REGION);
    ScalerSetByte(P10_30_PIN_SHARE_CTRL80__TOPOFF, (BYTE)_PIN_166_OFF_REGION);
}

#if(_HW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set HW IIC Pin Out
// Input Value  : ucHwIICPinNum --> Pin149_150/200_201/210_211
// Output Value : None
//--------------------------------------------------
void ScalerPinshareHwIICPin(BYTE ucHwIICPinNum)
{
    // Set the selected HwIICPinNum to IIC output
    // Set the others as GPI
    switch(ucHwIICPinNum)
    {
        case _HW_IIC_PIN_149_150:

#if((_PIN_149_OFF_REGION == 8) && (_PIN_150_OFF_REGION == 8))
            ScalerSetBit(P10_20_PIN_SHARE_CTRL60__TOPOFF, ~_BIT7, _BIT7);
#endif

#if((_PIN_200 == 8) && (_PIN_201 == 8))
            ScalerSetByte(P10_3E_PIN_SHARE_CTRL96__ADION, 0x00);
            ScalerSetByte(P10_3F_PIN_SHARE_CTRL97__ADION, 0x00);
#endif

#if((_PIN_210 == 8) && (_PIN_211 == 8))
            ScalerSetByte(P10_47_PIN_SHARE_CTRLA7__ADION, 0x00);
            ScalerSetByte(P10_48_PIN_SHARE_CTRLB0__ADION, 0x00);
#endif

            break;

        case _HW_IIC_PIN_200_201:

#if((_PIN_200 == 8) && (_PIN_201 == 8))
            ScalerSetBit(P10_3E_PIN_SHARE_CTRL96__ADION, ~_BIT7, _BIT7);
#endif

#if((_PIN_149_OFF_REGION == 8) && (_PIN_150_OFF_REGION == 8))
            ScalerSetByte(P10_20_PIN_SHARE_CTRL60__TOPOFF, 0x00);
            ScalerSetByte(P10_21_PIN_SHARE_CTRL61__TOPOFF, 0x00);
#endif

#if((_PIN_210 == 8) && (_PIN_211 == 8))
            ScalerSetByte(P10_47_PIN_SHARE_CTRLA7__ADION, 0x00);
            ScalerSetByte(P10_48_PIN_SHARE_CTRLB0__ADION, 0x00);
#endif

            break;

        case _HW_IIC_PIN_210_211:

#if((_PIN_210 == 8) && (_PIN_211 == 8))
            ScalerSetBit(P10_47_PIN_SHARE_CTRLA7__ADION, ~_BIT7, _BIT7);
#endif

#if((_PIN_149_OFF_REGION == 8) && (_PIN_150_OFF_REGION == 8))
            ScalerSetByte(P10_20_PIN_SHARE_CTRL60__TOPOFF, 0x00);
            ScalerSetByte(P10_21_PIN_SHARE_CTRL61__TOPOFF, 0x00);
#endif

#if((_PIN_200 == 8) && (_PIN_201 == 8))
            ScalerSetByte(P10_3E_PIN_SHARE_CTRL96__ADION, 0x00);
            ScalerSetByte(P10_3F_PIN_SHARE_CTRL97__ADION, 0x00);
#endif

            break;

        default:

            break;
    }
}
#endif  // End of #if(_HW_IIC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Switch DDC pin to GPIO or viceversa
// Input Value  : ucPinType -->
//                PIN65-65/212-213/214-215 for GPIO/DDC
// Output Value : None
//--------------------------------------------------
void ScalerPinshareGpioDdcPinSwitch(BYTE ucPinType)
{
    switch(ucPinType)
    {
        case _DDC_VGA_SWITCH_GPIO:
            ScalerSetBit(P10_02_PIN_SHARE_CTRL12__ADION, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Pin_65
            ScalerSetByte(P10_03_PIN_SHARE_CTRL13__ADION, (BYTE)_GPIO_OPEN_DRAIN); // Pin_66
            break;

        case _DDC_VGA_SWITCH_DDC:
            ScalerSetBit(P10_02_PIN_SHARE_CTRL12__ADION, ~_BIT7, 0x00); // Pin_65-66, DDCVGA
            break;

        case _DDC2_SWITCH_GPIO:
            ScalerSetBit(P10_49_PIN_SHARE_CTRLB1__ADION, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Pin_212
            ScalerSetByte(P10_4A_PIN_SHARE_CTRLB2__ADION, (BYTE)_GPIO_OPEN_DRAIN); // Pin_213
            break;

        case _DDC2_SWITCH_DDC:
            ScalerSetBit(P10_49_PIN_SHARE_CTRLB1__ADION, ~_BIT7, 0x00); // Pin_212/213, DDC2
            break;

        case _DDC3_SWITCH_GPIO:
            ScalerSetBit(P10_4B_PIN_SHARE_CTRLB3__ADION, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Pin_214
            ScalerSetByte(P10_4C_PIN_SHARE_CTRLB4__ADION, (BYTE)_GPIO_OPEN_DRAIN); // Pin_215
            break;

        case _DDC3_SWITCH_DDC:
            ScalerSetBit(P10_4B_PIN_SHARE_CTRLB3__ADION, ~_BIT7, 0x00); // Pin_214/215, DDC3
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust Pinshare config
// Input Value  : enumConfigPin  --> Pin num
//                enumConfigTyte --> Pin type(GPIO/PWM..Etc.)
// Output Value : None
//--------------------------------------------------
void ScalerPinshareAdjustConfig(EnumConfigPin enumConfigPin, EnumPinConfigType enumConfigType)
{
    switch(enumConfigPin)
    {
        case _CONFIG_PIN_1:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_00_PIN_SHARE_CTRL10__ADION, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_00_PIN_SHARE_CTRL10__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_00_PIN_SHARE_CTRL10__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_14:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_01_PIN_SHARE_CTRL11__ADION, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_01_PIN_SHARE_CTRL11__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_01_PIN_SHARE_CTRL11__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_67:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14__ADION, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_68:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_05_PIN_SHARE_CTRL15__ADION, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_05_PIN_SHARE_CTRL15__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_05_PIN_SHARE_CTRL15__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_69:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_06_PIN_SHARE_CTRL16__ADION, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_06_PIN_SHARE_CTRL16__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_06_PIN_SHARE_CTRL16__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }
            break;

        case _CONFIG_PIN_150_OFF_REGION:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_21_PIN_SHARE_CTRL61__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_21_PIN_SHARE_CTRL61__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_21_PIN_SHARE_CTRL61__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM1_PP:
                    ScalerSetBit(P10_21_PIN_SHARE_CTRL61__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1 | _BIT0);
                    break;

                case _PWM1_OD:
                    ScalerSetBit(P10_21_PIN_SHARE_CTRL61__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                default:
                    break;
            }
            break;

        case _CONFIG_PIN_151_OFF_REGION:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_22_PIN_SHARE_CTRL62__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_22_PIN_SHARE_CTRL62__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_22_PIN_SHARE_CTRL62__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM2_PP:
                    ScalerSetBit(P10_22_PIN_SHARE_CTRL62__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1 | _BIT0);
                    break;

                case _PWM2_OD:
                    ScalerSetBit(P10_22_PIN_SHARE_CTRL62__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                default:
                    break;
            }
            break;

        case _CONFIG_PIN_152_OFF_REGION:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_23_PIN_SHARE_CTRL63__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_23_PIN_SHARE_CTRL63__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_23_PIN_SHARE_CTRL63__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM5_PP:
                    ScalerSetBit(P10_23_PIN_SHARE_CTRL63__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1 | _BIT0);
                    break;

                case _PWM5_OD:
                    ScalerSetBit(P10_23_PIN_SHARE_CTRL63__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                default:
                    break;
            }
            break;

        case _CONFIG_PIN_153_OFF_REGION:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_24_PIN_SHARE_CTRL64__TOPOFF, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_24_PIN_SHARE_CTRL64__TOPOFF, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_24_PIN_SHARE_CTRL64__TOPOFF, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }
            break;

        case _CONFIG_PIN_158_OFF_REGION:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_29_PIN_SHARE_CTRL71__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_29_PIN_SHARE_CTRL71__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_29_PIN_SHARE_CTRL71__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _WS:
                    ScalerSetBit(P10_29_PIN_SHARE_CTRL71__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1 | _BIT0);
                    break;

                default:
                    break;
            }
            break;

        case _CONFIG_PIN_159_OFF_REGION:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _SCK:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1 | _BIT0);
                    break;

                default:
                    break;
            }
            break;

        case _CONFIG_PIN_160_OFF_REGION:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _MCK:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1 | _BIT0);
                    break;

                default:
                    break;
            }
            break;

        case _CONFIG_PIN_161_OFF_REGION:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2C_PIN_SHARE_CTRL74__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2C_PIN_SHARE_CTRL74__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2C_PIN_SHARE_CTRL74__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _SD0:
                    ScalerSetBit(P10_2C_PIN_SHARE_CTRL74__TOPOFF, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);
                    break;

                default:
                    break;
            }
            break;

        case _CONFIG_PIN_184:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_34_PIN_SHARE_CTRL84__TOPON, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_34_PIN_SHARE_CTRL84__TOPON, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_34_PIN_SHARE_CTRL84__TOPON, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM0_PP:
                    ScalerSetBit(P10_34_PIN_SHARE_CTRL84__TOPON, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM0_OD:
                    ScalerSetBit(P10_34_PIN_SHARE_CTRL84__TOPON, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                case _TCON_11:
                    ScalerSetBit(P10_34_PIN_SHARE_CTRL84__TOPON, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT0);
                    break;

                default:
                    break;
            }
            break;

        case _CONFIG_PIN_195:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_39_PIN_SHARE_CTRL91__ADION, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_39_PIN_SHARE_CTRL91__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_39_PIN_SHARE_CTRL91__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM4_PP:
                    ScalerSetBit(P10_39_PIN_SHARE_CTRL91__ADION, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM4_OD:
                    ScalerSetBit(P10_39_PIN_SHARE_CTRL91__ADION, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
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
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT7 | _BIT6 | _BIT5), _BIT6 | _BIT5);
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT7 | _BIT6 | _BIT5), _BIT7 | _BIT5);
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT7 | _BIT6 | _BIT5), _BIT7 | _BIT6);
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT7 | _BIT6 | _BIT5), _BIT7 | _BIT6 | _BIT5);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_SPI_SI_SO_CEB:

            switch(enumFlashDriveConfig)
            {
                case _SPI_DRIVE_3_0MA:
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT4 | _BIT3 | _BIT2), _BIT3);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT4 | _BIT3 | _BIT2), _BIT3 | _BIT2);
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT4 | _BIT3 | _BIT2), _BIT4);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT4 | _BIT3 | _BIT2), _BIT4 | _BIT2);
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT4 | _BIT3 | _BIT2), _BIT4 | _BIT3);
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_C2_PIN_DRIVING_CTRL02__TOPON, ~(_BIT4 | _BIT3 | _BIT2), _BIT4 | _BIT3 | _BIT2);
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
    ScalerSetBit(P10_81_PIN_SLEW_RATE_CTRL1__TOPON, ~(_BIT7), (_FLASH_CLK_SLEW_RATE_CONTROL & 0x01) << 7);

    // Setting Flash SPI SI/SO/CEB Pin Slew-Rate Control
    ScalerSetBit(P10_81_PIN_SLEW_RATE_CTRL1__TOPON, ~(_BIT6), (_FLASH_SI_SO_CEB_SLEW_RATE_CONTROL & 0x01) << 6);
}

//--------------------------------------------------
// Description  : Reset NHL setting when MHL nonsupport
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareCBUSPinInitialReset(void)
{
    return;
}
