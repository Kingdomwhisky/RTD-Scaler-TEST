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
// ID Code      : RL6369_Series_Pinshare.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __RL6369_SERIES_PINSHARE__

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
    ScalerSetByte(P10_00_PIN_SHARE_CTRL10, (BYTE)_PIN_21); // Page 10-00[3:0], Pin21
    ScalerSetByte(P10_01_PIN_SHARE_CTRL11, (BYTE)_PIN_22); // Page 10-01[3:0], Pin22
    ScalerSetByte(P10_02_PIN_SHARE_CTRL12, (BYTE)_PIN_34); // Page 10-02[3:0], Pin34
    ScalerSetByte(P10_03_PIN_SHARE_CTRL13, (BYTE)_PIN_35); // Page 10-03[3:0], Pin35
    ScalerSetByte(P10_04_PIN_SHARE_CTRL14, (BYTE)_PIN_36); // Page 10-04[3:0], Pin36

//Check if pin_37-38 are assigned to IIC0 or UART
#if((_PIN_37 == 7) && (_PIN_38 == 7)) // Check if  assigned to IIC0
    ScalerSetBit(P10_05_PIN_SHARE_CTRL15, ~(_BIT7 | _BIT6), (_BIT6));   // Enable IIC0
#elif((_PIN_37 == 8) && (_PIN_38 == 8)) // Check if  assigned to UART
    ScalerSetBit(P10_05_PIN_SHARE_CTRL15, ~(_BIT7 | _BIT6), (_BIT7));  // Enable UART
#else
    ScalerSetBit(P10_05_PIN_SHARE_CTRL15, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_37); // Page 10-05[3:0], Pin_37
    ScalerSetByte(P10_06_PIN_SHARE_CTRL16, (BYTE)_PIN_38); // Page 10-06[3:0], Pin_38
#endif

    ScalerSetByte(P10_07_PIN_SHARE_CTRL17, (BYTE)_PIN_39); // Page 10-07[3:0], Pin39
    ScalerSetByte(P10_08_PIN_SHARE_CTRL30, (BYTE)_PIN_42); // Page 10-08[3:0], Pin42
    ScalerSetByte(P10_09_PIN_SHARE_CTRL31, (BYTE)_PIN_43); // Page 10-09[3:0], Pin43
    ScalerSetByte(P10_0A_PIN_SHARE_CTRL32, (BYTE)_PIN_44); // Page 10-0A[3:0], Pin44
    ScalerSetByte(P10_0B_PIN_SHARE_CTRL33, (BYTE)_PIN_45); // Page 10-0B[3:0], Pin45
    ScalerSetByte(P10_0C_PIN_SHARE_CTRL34, (BYTE)_PIN_46); // Page 10-0C[3:0], Pin46

//Check if pin_47-48 are assigned to IIC1 or IICAUX
#if((_PIN_47 == 7) && (_PIN_48 == 7)) // Check if  assigned to IIC1
    ScalerSetBit(P10_0D_PIN_SHARE_CTRL35, ~(_BIT7 | _BIT6), (_BIT6));     // Enable IIC1
#elif((_PIN_47 == 8) && (_PIN_48 == 8)) // Check if  assigned to IIC AUX
    ScalerSetBit(P10_0D_PIN_SHARE_CTRL35, ~(_BIT7 | _BIT6), (_BIT7));  // Enable IIC AUX
#else
    ScalerSetBit(P10_0D_PIN_SHARE_CTRL35, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_47); // Page 10-0D[3:0], Pin_48
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL36, (BYTE)_PIN_48); // Page 10-0E[3:0], Pin_48
#endif

//Check if pin_49-50 are assigned to DDCVGA or UART
#if((_PIN_49 == 7) && (_PIN_50 == 7)) // Check if  assigned to DDCVGA
    ScalerPinshareGpioDdcPinSwitch(_DDC_VGA_SWITCH_DDC);// Enable DDCVGA
#elif((_PIN_49 == 8) && (_PIN_50 == 8)) // Check if  assigned to UART
    ScalerSetBit(P10_0F_PIN_SHARE_CTRL37, ~(_BIT7 | _BIT6), (_BIT7));  // Enable UART
#else
    ScalerSetBit(P10_0F_PIN_SHARE_CTRL37, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_49); // Page 10-0F[3:0], Pin_49
    ScalerSetByte(P10_10_PIN_SHARE_CTRL40, (BYTE)_PIN_50); // Page 10-10[3:0], Pin_50
#endif

    ScalerSetByte(P10_11_PIN_SHARE_CTRL41, (BYTE)_PIN_52); // Page 10-11[3:0], Pin52
    ScalerSetByte(P10_12_PIN_SHARE_CTRL42, (BYTE)_PIN_53); // Page 10-12[3:0], Pin53
    ScalerSetByte(P10_13_PIN_SHARE_CTRL43, (BYTE)_PIN_55); // Page 10-13[3:0], Pin55
    ScalerSetByte(P10_14_PIN_SHARE_CTRL44, (BYTE)_PIN_56); // Page 10-14[3:0], Pin56
    ScalerSetByte(P10_15_PIN_SHARE_CTRL45, (BYTE)_PIN_57); // Page 10-15[3:0], Pin57
    ScalerSetByte(P10_16_PIN_SHARE_CTRL46, (BYTE)_PIN_58); // Page 10-16[3:0], Pin58
    ScalerSetByte(P10_17_PIN_SHARE_CTRL47, (BYTE)_PIN_59); // Page 10-17[3:0], Pin59

//Check if pin_60-61 are assigned to IICSCL2 or UART
#if((_PIN_60 == 7) && (_PIN_61 == 7)) // Check if  assigned to IICSCL2
    ScalerSetBit(P10_18_PIN_SHARE_CTRL50, ~(_BIT7 | _BIT6), (_BIT6));     // Enable IICSCL2
#elif((_PIN_60 == 8) && (_PIN_61 == 8)) // Check if assigned to UART
    ScalerSetBit(P10_18_PIN_SHARE_CTRL50, ~(_BIT7 | _BIT6), (_BIT7));  // Enable UART
#else
    ScalerSetBit(P10_18_PIN_SHARE_CTRL50, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_60); // Page 10-18[3:0], Pin_60
    ScalerSetByte(P10_19_PIN_SHARE_CTRL51, (BYTE)_PIN_61); // Page 10-19[3:0], Pin_61
#endif

    ScalerSetByte(P10_1A_PIN_SHARE_CTRL52, (BYTE)_PIN_64); // Page 10-1A[3:0], Pin64
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL53, (BYTE)_PIN_63); // Page 10-1B[3:0], Pin63
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL54, (BYTE)_PIN_65); // Page 10-1C[3:0], Pin65
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL55, (BYTE)_PIN_66); // Page 10-1D[3:0], Pin66
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL56, (BYTE)_PIN_67); // Page 10-1E[3:0], Pin67
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57, (BYTE)_PIN_68); // Page 10-1F[3:0], Pin68
    ScalerSetByte(P10_20_PIN_SHARE_CTRL60, (BYTE)_PIN_69); // Page 10-20[3:0], Pin69
    ScalerSetByte(P10_21_PIN_SHARE_CTRL61, (BYTE)_PIN_70); // Page 10-21[3:0], Pin70
    ScalerSetByte(P10_22_PIN_SHARE_CTRL62, (BYTE)_PIN_71); // Page 10-22[3:0], Pin71
    ScalerSetByte(P10_23_PIN_SHARE_CTRL63, (BYTE)_PIN_72); // Page 10-23[3:0], Pin72
    ScalerSetByte(P10_24_PIN_SHARE_CTRL64, (BYTE)_PIN_73); // Page 10-24[3:0], Pin73
    ScalerSetByte(P10_25_PIN_SHARE_CTRL65, (BYTE)_PIN_74); // Page 10-25[3:0], Pin74
    ScalerSetByte(P10_26_PIN_SHARE_CTRL66, (BYTE)_PIN_77); // Page 10-26[3:0], Pin77
    ScalerSetByte(P10_27_PIN_SHARE_CTRL67, (BYTE)_PIN_78); // Page 10-27[3:0], Pin78
    ScalerSetByte(P10_28_PIN_SHARE_CTRL70, (BYTE)_PIN_96); // Page 10-28[3:0], Pin96
    ScalerSetByte(P10_29_PIN_SHARE_CTRL71, (BYTE)_PIN_97); // Page 10-29[3:0], Pin97
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL72, (BYTE)_PIN_98); // Page 10-2A[3:0], Pin98
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL73, (BYTE)_PIN_99); // Page 10-2B[3:0], Pin99
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL74, (BYTE)_PIN_100); // Page 10-2C[3:0], Pin100
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL75, (BYTE)_PIN_101); // Page 10-2D[3:0], Pin101

//Check if pin_110-111 are assigned to DDC0
#if((_PIN_110 == 7) && (_PIN_111 == 7)) // Check if assigned to DDC0
    ScalerPinshareGpioDdcPinSwitch(_DDC0_SWITCH_DDC);// Enable DDC0
#else
    ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_110); // Page 10-2E[3:0], Pin_110
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL77, (BYTE)_PIN_111); // Page 10-2F[3:0], Pin_111
#endif

//Check if pin_112-113 are assigned to DDC1
#if((_PIN_112 == 7) && (_PIN_113 == 7)) // Check if assigned to DDC1
    ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_DDC);// Enable DDC1
#else
    ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_112); // Page 10-30[3:0], Pin_112
    ScalerSetByte(P10_31_PIN_SHARE_CTRL81, (BYTE)_PIN_113); // Page 10-31[3:0], Pin_113
#endif

//Check if pin_114-115 are assigned to DDC2
#if((_PIN_114 == 7) && (_PIN_115 == 7)) // Check if assigned to DDC2
    ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_DDC);// Enable DDC2
#else
    ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_115); // Page 10-32[3:0], Pin_115
    ScalerSetByte(P10_33_PIN_SHARE_CTRL83, (BYTE)_PIN_114); // Page 10-31[3:0], Pin_114
#endif

    // Set Pin configure to AC ON
    ScalerPinshareConfig(_POWER_STATUS_AC_ON);

    // Pin Config adjust sample (this is a ineffective configuration example aviod uncall worning)
    ScalerPinshareAdjustConfig(_CONFIG_PIN_START, _GPI);
}

//--------------------------------------------------
// Description  : Pinshare Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinsharePowerOnReset(void)
{
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL54, (BYTE)_PIN_65); // Page 10-1C[3:0], Pin65
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL55, (BYTE)_PIN_66); // Page 10-1D[3:0], Pin66
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL56, (BYTE)_PIN_67); // Page 10-1E[3:0], Pin67
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57, (BYTE)_PIN_68); // Page 10-1F[3:0], Pin68
    ScalerSetByte(P10_20_PIN_SHARE_CTRL60, (BYTE)_PIN_69); // Page 10-20[3:0], Pin69
    ScalerSetByte(P10_21_PIN_SHARE_CTRL61, (BYTE)_PIN_70); // Page 10-21[3:0], Pin70
    ScalerSetByte(P10_22_PIN_SHARE_CTRL62, (BYTE)_PIN_71); // Page 10-22[3:0], Pin71
    ScalerSetByte(P10_23_PIN_SHARE_CTRL63, (BYTE)_PIN_72); // Page 10-23[3:0], Pin72
    ScalerSetByte(P10_24_PIN_SHARE_CTRL64, (BYTE)_PIN_73); // Page 10-24[3:0], Pin73
    ScalerSetByte(P10_25_PIN_SHARE_CTRL65, (BYTE)_PIN_74); // Page 10-25[3:0], Pin74
    ScalerSetByte(P10_26_PIN_SHARE_CTRL66, (BYTE)_PIN_77); // Page 10-26[3:0], Pin77
    ScalerSetByte(P10_27_PIN_SHARE_CTRL67, (BYTE)_PIN_78); // Page 10-27[3:0], Pin78
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

#if((_PIN_37 == 7) || (_PIN_38 == 7))
            ScalerSetBit(P10_05_PIN_SHARE_CTRL15, ~(_BIT7 | _BIT6), _BIT6);
#endif

#if((_PIN_47 == 7) && (_PIN_48 == 7))
            ScalerSetByte(P10_0D_PIN_SHARE_CTRL35, 0x00);
            ScalerSetByte(P10_0E_PIN_SHARE_CTRL36, 0x00);
#endif

#if((_PIN_60 == 7) && (_PIN_61 == 7))
            ScalerSetByte(P10_18_PIN_SHARE_CTRL50, 0x00);
            ScalerSetByte(P10_19_PIN_SHARE_CTRL51, 0x00);
#endif

            break;

        case _HW_IIC_PIN_47_48:

#if((_PIN_47 == 7) && (_PIN_48 == 7))
            ScalerSetBit(P10_0D_PIN_SHARE_CTRL35, ~(_BIT7 | _BIT6), _BIT6);
#endif

#if((_PIN_37 == 7) && (_PIN_38 == 7))
            ScalerSetByte(P10_05_PIN_SHARE_CTRL15, 0x00);
            ScalerSetByte(P10_06_PIN_SHARE_CTRL16, 0x00);
#endif

#if((_PIN_60 == 7) && (_PIN_61 == 7))
            ScalerSetByte(P10_18_PIN_SHARE_CTRL50, 0x00);
            ScalerSetByte(P10_19_PIN_SHARE_CTRL51, 0x00);
#endif

            break;

        case _HW_IIC_PIN_60_61:

#if((_PIN_60 == 7) && (_PIN_61 == 7))
            ScalerSetBit(P10_18_PIN_SHARE_CTRL50, ~(_BIT7 | _BIT6), _BIT6);
#endif

#if((_PIN_37 == 7) && (_PIN_38 == 7))
            ScalerSetByte(P10_05_PIN_SHARE_CTRL15, 0x00);
            ScalerSetByte(P10_06_PIN_SHARE_CTRL16, 0x00);
#endif

#if((_PIN_47 == 7) && (_PIN_48 == 7))
            ScalerSetByte(P10_0D_PIN_SHARE_CTRL35, 0x00);
            ScalerSetByte(P10_0E_PIN_SHARE_CTRL36, 0x00);
#endif

            break;

        default:

            break;
    }
}
#endif  // End of #if(_HW_IIC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Switch DDC pin to GPIO or viceversa
// Input Value  : ucPinType --> _PIN_110/111-112/113-49/50_GPIO/DDC
// Output Value : None
//--------------------------------------------------
void ScalerPinshareGpioDdcPinSwitch(BYTE ucPinType)
{
    switch(ucPinType)
    {
        case _DDC0_SWITCH_GPIO:
            ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((BYTE)_GPIO_OPEN_DRAIN)); // Page 10-2E[3:0], Pin_110
            ScalerSetByte(P10_2F_PIN_SHARE_CTRL77, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-2F[3:0], Pin_111
            break;

        case _DDC0_SWITCH_DDC:
            ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~_BIT7, _BIT7); // Page 10-2E[3:0], Pin_110
            break;


        case _DDC1_SWITCH_GPIO:
            ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((BYTE)_GPIO_OPEN_DRAIN)); // Page 10-30[3:0], Pin_112
            ScalerSetByte(P10_31_PIN_SHARE_CTRL81, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-31[3:0], Pin_113
            break;

        case _DDC1_SWITCH_DDC:
            ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~_BIT7, _BIT7); // Page 10-30[3:0], Pin_112
            break;


        case _DDC2_SWITCH_GPIO:
            ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), ((BYTE)_GPIO_OPEN_DRAIN)); // Page 10-32[3:0], Pin_115
            ScalerSetByte(P10_33_PIN_SHARE_CTRL83, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-33[3:0], Pin_114
            break;

        case _DDC2_SWITCH_DDC:
            ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~_BIT7, _BIT7); // Page 10-32[3:0], Pin_115
            break;

        case _DDC_VGA_SWITCH_GPIO:
            ScalerSetBit(P10_0F_PIN_SHARE_CTRL37, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((BYTE)_GPIO_OPEN_DRAIN)); // Page 10-0F[3:0], Pin_49
            ScalerSetByte(P10_10_PIN_SHARE_CTRL40, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-10[3:0], Pin_50
            break;

        case _DDC_VGA_SWITCH_DDC:
            ScalerSetBit(P10_0F_PIN_SHARE_CTRL37, ~(_BIT7 | _BIT6), _BIT6); // Page 10-0F[3:0], Pin_49
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
                    ScalerSetBit(P10_00_PIN_SHARE_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_00_PIN_SHARE_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_00_PIN_SHARE_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_36:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM2_PP:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM2_OD:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_46:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_0C_PIN_SHARE_CTRL34, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_0C_PIN_SHARE_CTRL34, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_0C_PIN_SHARE_CTRL34, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM1_PP:
                    ScalerSetBit(P10_0C_PIN_SHARE_CTRL34, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM1_OD:
                    ScalerSetBit(P10_0C_PIN_SHARE_CTRL34, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                case _PWM5_PP:
                    ScalerSetBit(P10_0C_PIN_SHARE_CTRL34, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
                    break;

                case _PWM5_OD:
                    ScalerSetBit(P10_0C_PIN_SHARE_CTRL34, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_52:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_11_PIN_SHARE_CTRL41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_11_PIN_SHARE_CTRL41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_11_PIN_SHARE_CTRL41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM0_PP:
                    ScalerSetBit(P10_11_PIN_SHARE_CTRL41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM0_OD:
                    ScalerSetBit(P10_11_PIN_SHARE_CTRL41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_99:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM2_PP:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM2_OD:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                case _PWM3_PP:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
                    break;

                case _PWM3_OD:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
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
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT4 | _BIT3);
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT3);
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT4);
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT5 | _BIT4 | _BIT3), _BIT5 | _BIT4 | _BIT3);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_SPI_SI_SO_CEB:

            switch(enumFlashDriveConfig)
            {
                case _SPI_DRIVE_3_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT1 | _BIT0);
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT0);
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1 | _BIT0);
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
    ScalerSetBit(P10_75_PIN_SLEW_RATE_CTRL0, ~(_BIT5), (_FLASH_CLK_SLEW_RATE_CONTROL & 0x01) << 5);

    // Setting Flash SPI SI/SO/CEB Pin Slew-Rate Control
    ScalerSetBit(P10_75_PIN_SLEW_RATE_CTRL0, ~(_BIT4), (_FLASH_SI_SO_CEB_SLEW_RATE_CONTROL & 0x01) << 4);
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

