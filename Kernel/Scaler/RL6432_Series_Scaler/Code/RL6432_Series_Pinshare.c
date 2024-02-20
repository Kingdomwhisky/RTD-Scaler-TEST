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
// ID Code      : RL6432_Series_Pinshare.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6432_SERIES_PINSHARE__

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
    ScalerSetByte(P10_00_PIN_SHARE_CTRL10, (BYTE)_PIN_1);  // Page 10-00[2:0], Pin_1
    ScalerSetByte(P10_01_PIN_SHARE_CTRL11, (BYTE)_PIN_3);  // Page 10-01[2:0], Pin_3
    ScalerSetByte(P10_02_PIN_SHARE_CTRL12, (BYTE)_PIN_15); // Page 10-02[2:0], Pin_15
    ScalerSetByte(P10_03_PIN_SHARE_CTRL13, (BYTE)_PIN_53); // Page 10-03[2:0], Pin_53
    ScalerSetByte(P10_04_PIN_SHARE_CTRL14, (BYTE)_PIN_54); // Page 10-04[2:0], Pin_54

    // Check if pin_AB7-AB6 are assigned to DDC0
#if((_PIN_66 == 8) && (_PIN_67 == 8))
    ScalerPinshareGpioDdcPinSwitch(_DDC_VGA_SWITCH_DDC);
#else
    ScalerSetBit(P10_05_PIN_SHARE_CTRL15, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_66))); // Page 10-05[2:0], Pin_66
    ScalerSetByte(P10_06_PIN_SHARE_CTRL16, (BYTE)_PIN_67); // Page 10-06[2:0], Pin_67
#endif

    ScalerSetByte(P10_07_PIN_SHARE_CTRL17, (BYTE)_PIN_68); // Page 10-07[2:0], Pin_68
    ScalerSetByte(P10_08_PIN_SHARE_CTRL30, (BYTE)_PIN_71); // Page 10-08[2:0], Pin_71
    ScalerSetByte(P10_09_PIN_SHARE_CTRL31, (BYTE)_PIN_72); // Page 10-09[2:0], Pin_72

    // Check if pin_AA7-AA6 are assigned to DDC1
#if((_PIN_73 == 8) && (_PIN_74 == 8))
    ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_DDC);
#else
    ScalerSetBit(P10_0A_PIN_SHARE_CTRL32, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_73))); // Page 10-0A[2:0], Pin_73
    ScalerSetByte(P10_0B_PIN_SHARE_CTRL33, (BYTE)_PIN_74); // Page 10-0B[2:0], Pin_74
#endif

    ScalerSetByte(P10_0C_PIN_SHARE_CTRL34, (BYTE)_PIN_91); // Page 10-0C[2:0], Pin_91
    ScalerSetByte(P10_0D_PIN_SHARE_CTRL35, (BYTE)_PIN_92); // Page 10-0D[2:0], Pin_92
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL36, (BYTE)_PIN_93); // Page 10-0E[2:0], Pin_93
    ScalerSetByte(P10_0F_PIN_SHARE_CTRL37, (BYTE)_PIN_94); // Page 10-0F[2:0], Pin_94

    ScalerSetByte(P10_10_PIN_SHARE_CTRL40, (BYTE)_PIN_89); // Page 10-10[2:0], Pin_89
    ScalerSetByte(P10_11_PIN_SHARE_CTRL41, (BYTE)_PIN_90); // Page 10-11[2:0], Pin_90
    ScalerSetByte(P10_12_PIN_SHARE_CTRL42, (BYTE)_PIN_99); // Page 10-12[2:0], Pin_99
    ScalerSetByte(P10_13_PIN_SHARE_CTRL43, (BYTE)_PIN_100); // Page 10-13[2:0], Pin_100
    ScalerSetByte(P10_14_PIN_SHARE_CTRL44, (BYTE)_PIN_103); // Page 10-14[2:0], Pin_103
    ScalerSetByte(P10_15_PIN_SHARE_CTRL45, (BYTE)_PIN_104); // Page 10-15[2:0], Pin_104
    ScalerSetByte(P10_16_PIN_SHARE_CTRL46, (BYTE)_PIN_105); // Page 10-16[2:0], Pin_105
    ScalerSetByte(P10_17_PIN_SHARE_CTRL47, (BYTE)_PIN_106); // Page 10-17[2:0], Pin_106
    ScalerSetByte(P10_18_PIN_SHARE_CTRL50, (BYTE)_PIN_107); // Page 10-18[2:0], Pin_107
    ScalerSetByte(P10_19_PIN_SHARE_CTRL51, (BYTE)_PIN_174_OFF_REGION); // Page 10-19[2:0], Pin_174
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL52, (BYTE)_PIN_175_OFF_REGION); // Page 10-1A[2:0], Pin_175
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL53, (BYTE)_PIN_173_OFF_REGION); // Page 10-1B[2:0], Pin_173
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL54, (BYTE)_PIN_164_OFF_REGION); // Page 10-1C[2:0], Pin_164
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL55, (BYTE)_PIN_165_OFF_REGION);  // Page 10-1D[2:0], Pin_165
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL56, (BYTE)_PIN_166_OFF_REGION);  // Page 10-1E[2:0], Pin_166
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57, (BYTE)_PIN_167_OFF_REGION);  // Page 10-1F[2:0], Pin_167

    // Check if pin_168-172 are assigned to USB_SPI
#if((_PIN_168_OFF_REGION == 8) && (_PIN_169_OFF_REGION == 8) && (_PIN_170_OFF_REGION == 8) && (_PIN_171_OFF_REGION == 8) && (_PIN_172_OFF_REGION == 8))
    ScalerSetBit(P10_20_PIN_SHARE_CTRL60, ~_BIT7, _BIT7);  // Enable USB_SPI
#else
    ScalerSetBit(P10_20_PIN_SHARE_CTRL60, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_168_OFF_REGION); // Page 10-20[2:0], Pin_168
    ScalerSetByte(P10_21_PIN_SHARE_CTRL61, (BYTE)_PIN_169_OFF_REGION); // Page 10-21[2:0], Pin_169
    ScalerSetByte(P10_22_PIN_SHARE_CTRL62, (BYTE)_PIN_170_OFF_REGION); // Page 10-22[2:0], Pin_170
    ScalerSetByte(P10_23_PIN_SHARE_CTRL63, (BYTE)_PIN_171_OFF_REGION); // Page 10-23[2:0], Pin_171
    ScalerSetByte(P10_24_PIN_SHARE_CTRL64, (BYTE)_PIN_172_OFF_REGION); // Page 10-24[2:0], Pin_172
#endif

    ScalerSetByte(P10_25_PIN_SHARE_CTRL65, (BYTE)_PIN_178_OFF_REGION); // Page 10-25[2:0], Pin_178

    // Check if pin 179-180 are assigned to IIC1
#if((_PIN_179_OFF_REGION == 8) && (_PIN_180_OFF_REGION == 8))
    ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~_BIT7, _BIT7);  // Enable IIC1
#else
    ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_179_OFF_REGION); // Page 10-26[2:0], Pin_179
    ScalerSetByte(P10_27_PIN_SHARE_CTRL67, (BYTE)_PIN_180_OFF_REGION); // Page 10-27[2:0], Pin_180
#endif

    ScalerSetByte(P10_28_PIN_SHARE_CTRL70, (BYTE)_PIN_183_OFF_REGION); // Page 10-28[2:0], Pin_183
    ScalerSetByte(P10_29_PIN_SHARE_CTRL71, (BYTE)_PIN_189); // Page 10-29[2:0], Pin_189
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL72, (BYTE)_PIN_192); // Page 10-2A[2:0], Pin_192
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL73, (BYTE)_PIN_193); // Page 10-2B[2:0], Pin_193
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL74, (BYTE)_PIN_194); // Page 10-2C[2:0], Pin_194
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL75, (BYTE)_PIN_195); // Page 10-2D[2:0], Pin_195
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL76, (BYTE)_PIN_196); // Page 10-2E[2:0], Pin_196
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL77, (BYTE)_PIN_197); // Page 10-2F[2:0], Pin_197

    // Check if pin 198-199 are assigned to IIC2
#if((_PIN_198 == 8) && (_PIN_199 == 8))
    ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~_BIT7, _BIT7);  // Enable IIC2
#else
    ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_198); // Page 10-30[2:0], Pin_198
    ScalerSetByte(P10_31_PIN_SHARE_CTRL81, (BYTE)_PIN_199); // Page 10-31[2:0], Pin_199
#endif

    // Check if pin 200-201 are assigned to TXD/RXD
#if((_PIN_200 == 8) && (_PIN_201 == 8))
    ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~_BIT7, _BIT7);  // Enable TXD/RXD
#else
    ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_201); // Page 10-32[2:0], Pin_201
    ScalerSetByte(P10_33_PIN_SHARE_CTRL83, (BYTE)_PIN_200); // Page 10-33[2:0], Pin_200
#endif

    ScalerSetByte(P10_34_PIN_SHARE_CTRL84, (BYTE)_PIN_202); // Page 10-34[2:0], Pin_202
    ScalerSetByte(P10_35_PIN_SHARE_CTRL85, (BYTE)_PIN_203); // Page 10-35[2:0], Pin_203
    ScalerSetByte(P10_36_PIN_SHARE_CTRL86, (BYTE)_PIN_204); // Page 10-36[2:0], Pin_204
    ScalerSetByte(P10_37_PIN_SHARE_CTRL87, (BYTE)_PIN_205); // Page 10-37[2:0], Pin_205
    ScalerSetByte(P10_38_PIN_SHARE_CTRL90, (BYTE)_PIN_208); // Page 10-38[2:0], Pin_208
    ScalerSetByte(P10_39_PIN_SHARE_CTRL91, (BYTE)_PIN_209); // Page 10-39[2:0], Pin_209

    // Check if pin 210-211 are assigned to EEIIC
#if((_PIN_210 == 8) && (_PIN_211 == 8))
    ScalerSetBit(P10_3A_PIN_SHARE_CTRL92, ~_BIT7, _BIT7);  // Enable EEIIC
#else
    ScalerSetBit(P10_3A_PIN_SHARE_CTRL92, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_210); // Page 10-3A[2:0], Pin_210
    ScalerSetByte(P10_3B_PIN_SHARE_CTRL93, (BYTE)_PIN_211); // Page 10-3B[2:0], Pin_211
#endif

    // Check if pin_212-213 are assigned to DDC2
#if((_PIN_212 == 8) && (_PIN_213 == 8))
    ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_DDC);
#else
    ScalerSetBit(P10_3C_PIN_SHARE_CTRL94, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_212))); // Page 10-3C[2:0], Pin_212
    ScalerSetByte(P10_3D_PIN_SHARE_CTRL95, (BYTE)_PIN_213); // Page 10-3D[2:0], Pin_213
#endif

    // Check if pin_214-215 are assigned to DDC3
#if((_PIN_214 == 8) && (_PIN_215 == 8))
    ScalerPinshareGpioDdcPinSwitch(_DDC3_SWITCH_DDC);
#else
    ScalerSetBit(P10_3E_PIN_SHARE_CTRL96, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_214))); // Page 10-3E[2:0], Pin_214
    ScalerSetByte(P10_3F_PIN_SHARE_CTRL97, (BYTE)_PIN_215); // Page 10-3F[2:0], Pin_215
#endif

    ScalerSetByte(P10_40_PIN_SHARE_CTRLA0, (BYTE)_PIN_216); // Page 10-40[2:0], Pin_216
    ScalerSetByte(P10_45_PIN_SHARE_CTRLA5, (BYTE)_PIN_139_OFF_REGION); // Page 10-45[2:0], Pin_139
    ScalerSetByte(P10_46_PIN_SHARE_CTRLA6, (BYTE)_PIN_140_OFF_REGION); // Page 10-46[2:0], Pin_140
    ScalerSetByte(P10_47_PIN_SHARE_CTRLA7, (BYTE)_PIN_141_OFF_REGION); // Page 10-47[2:0], Pin_141
    ScalerSetByte(P10_48_PIN_SHARE_CTRLB0, (BYTE)_PIN_142_OFF_REGION); // Page 10-48[2:0], Pin_142
    ScalerSetByte(P10_49_PIN_SHARE_CTRLB1, (BYTE)_PIN_143_OFF_REGION); // Page 10-49[2:0], Pin_143
    ScalerSetByte(P10_4A_PIN_SHARE_CTRLB2, (BYTE)_PIN_144_OFF_REGION); // Page 10-4A[2:0], Pin_144
    ScalerSetByte(P10_4B_PIN_SHARE_CTRLB3, (BYTE)_PIN_145_OFF_REGION); // Page 10-4B[2:0], Pin_145
    ScalerSetByte(P10_4C_PIN_SHARE_CTRLB4, (BYTE)_PIN_146_OFF_REGION); // Page 10-4C[2:0], Pin_146
    ScalerSetByte(P10_4D_PIN_SHARE_CTRLB5, (BYTE)_PIN_147_OFF_REGION); // Page 10-4D[2:0], Pin_147
    ScalerSetByte(P10_4E_PIN_SHARE_CTRLB6, (BYTE)_PIN_148_OFF_REGION); // Page 10-4E[2:0], Pin_148
    ScalerSetByte(P10_4F_PIN_SHARE_CTRLB7, (BYTE)_PIN_150_OFF_REGION); // Page 10-4F[2:0], Pin_150
    ScalerSetByte(P10_50_PIN_SHARE_CTRLC0, (BYTE)_PIN_151_OFF_REGION); // Page 10-50[2:0], Pin_151

    ScalerSetByte(P10_51_PIN_SHARE_CTRLC1, (BYTE)_PIN_152_OFF_REGION); // Page 10-51[2:0], Pin_152
    ScalerSetByte(P10_52_PIN_SHARE_CTRLC2, (BYTE)_PIN_153_OFF_REGION); // Page 10-52[2:0], Pin_153
    ScalerSetByte(P10_53_PIN_SHARE_CTRLC3, (BYTE)_PIN_154_OFF_REGION); // Page 10-53[2:0], Pin_154
    ScalerSetByte(P10_54_PIN_SHARE_CTRLC4, (BYTE)_PIN_155_OFF_REGION); // Page 10-54[2:0], Pin_155
    ScalerSetByte(P10_55_PIN_SHARE_CTRLC5, (BYTE)_PIN_156_OFF_REGION); // Page 10-55[2:0], Pin_156
    ScalerSetByte(P10_56_PIN_SHARE_CTRLC6, (BYTE)_PIN_157_OFF_REGION); // Page 10-56[2:0], Pin_157
    ScalerSetByte(P10_57_PIN_SHARE_CTRLC7, (BYTE)_PIN_158_OFF_REGION); // Page 10-57[2:0], Pin_158
    ScalerSetByte(P10_58_PIN_SHARE_CTRLD0, (BYTE)_PIN_159_OFF_REGION); // Page 10-58[2:0], Pin_159
    ScalerSetByte(P10_59_PIN_SHARE_CTRLD1, (BYTE)_PIN_160_OFF_REGION); // Page 10-59[2:0], Pin_160
    ScalerSetByte(P10_5A_PIN_SHARE_CTRLD2, (BYTE)_PIN_161_OFF_REGION); // Page 10-5A[2:0], Pin_161
    ScalerSetByte(P10_5B_PIN_SHARE_CTRLD3, (BYTE)_PIN_97); // Page 10-5B[2:0], Pin_97
    ScalerSetByte(P10_5C_PIN_SHARE_CTRLD4, (BYTE)_PIN_98); // Page 10-5C[2:0], Pin_98

    // DDC Driving Current Set High
    ScalerSetBit(P10_B0_PIN_DRIVING_CTRL00, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));
    ScalerSetBit(P10_B3_PIN_DRIVING_CTRL03, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

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
    ScalerSetByte(P10_19_PIN_SHARE_CTRL51, (BYTE)_PIN_174_OFF_REGION); // Page 10-19[2:0], Pin_174
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL52, (BYTE)_PIN_175_OFF_REGION); // Page 10-1A[2:0], Pin_175
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL53, (BYTE)_PIN_173_OFF_REGION); // Page 10-1B[2:0], Pin_173
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL54, (BYTE)_PIN_164_OFF_REGION); // Page 10-1C[2:0], Pin_164
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL55, (BYTE)_PIN_165_OFF_REGION);  // Page 10-1D[2:0], Pin_165
    ScalerSetByte(P10_1E_PIN_SHARE_CTRL56, (BYTE)_PIN_166_OFF_REGION);  // Page 10-1E[2:0], Pin_166
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57, (BYTE)_PIN_167_OFF_REGION);  // Page 10-1F[2:0], Pin_167

    // Check if pin_168-172 are assigned to USB_SPI
#if((_PIN_168_OFF_REGION == 8) && (_PIN_169_OFF_REGION == 8) && (_PIN_170_OFF_REGION == 8) && (_PIN_171_OFF_REGION == 8) && (_PIN_172_OFF_REGION == 8))
    ScalerSetBit(P10_20_PIN_SHARE_CTRL60, ~_BIT7, _BIT7);  // Enable USB_SPI
#else
    ScalerSetBit(P10_20_PIN_SHARE_CTRL60, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_168_OFF_REGION); // Page 10-20[2:0], Pin_168
    ScalerSetByte(P10_21_PIN_SHARE_CTRL61, (BYTE)_PIN_169_OFF_REGION); // Page 10-21[2:0], Pin_169
    ScalerSetByte(P10_22_PIN_SHARE_CTRL62, (BYTE)_PIN_170_OFF_REGION); // Page 10-22[2:0], Pin_170
    ScalerSetByte(P10_23_PIN_SHARE_CTRL63, (BYTE)_PIN_171_OFF_REGION); // Page 10-23[2:0], Pin_171
    ScalerSetByte(P10_24_PIN_SHARE_CTRL64, (BYTE)_PIN_172_OFF_REGION); // Page 10-24[2:0], Pin_172
#endif

    ScalerSetByte(P10_25_PIN_SHARE_CTRL65, (BYTE)_PIN_178_OFF_REGION); // Page 10-25[2:0], Pin_178

    // Check if pin 179-180 are assigned to IIC1
#if((_PIN_179_OFF_REGION == 8) && (_PIN_180_OFF_REGION == 8))
    ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~_BIT7, _BIT7);  // Enable IIC1
#else
    ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_179_OFF_REGION); // Page 10-26[2:0], Pin_179
    ScalerSetByte(P10_27_PIN_SHARE_CTRL67, (BYTE)_PIN_180_OFF_REGION); // Page 10-27[2:0], Pin_180
#endif

    ScalerSetByte(P10_28_PIN_SHARE_CTRL70, (BYTE)_PIN_183_OFF_REGION); // Page 10-28[2:0], Pin_183

    ScalerSetByte(P10_45_PIN_SHARE_CTRLA5, (BYTE)_PIN_139_OFF_REGION); // Page 10-45[2:0], Pin_139
    ScalerSetByte(P10_46_PIN_SHARE_CTRLA6, (BYTE)_PIN_140_OFF_REGION); // Page 10-46[2:0], Pin_140
    ScalerSetByte(P10_47_PIN_SHARE_CTRLA7, (BYTE)_PIN_141_OFF_REGION); // Page 10-47[2:0], Pin_141
    ScalerSetByte(P10_48_PIN_SHARE_CTRLB0, (BYTE)_PIN_142_OFF_REGION); // Page 10-48[2:0], Pin_142
    ScalerSetByte(P10_49_PIN_SHARE_CTRLB1, (BYTE)_PIN_143_OFF_REGION); // Page 10-49[2:0], Pin_143
    ScalerSetByte(P10_4A_PIN_SHARE_CTRLB2, (BYTE)_PIN_144_OFF_REGION); // Page 10-4A[2:0], Pin_144
    ScalerSetByte(P10_4B_PIN_SHARE_CTRLB3, (BYTE)_PIN_145_OFF_REGION); // Page 10-4B[2:0], Pin_145
    ScalerSetByte(P10_4C_PIN_SHARE_CTRLB4, (BYTE)_PIN_146_OFF_REGION); // Page 10-4C[2:0], Pin_146
    ScalerSetByte(P10_4D_PIN_SHARE_CTRLB5, (BYTE)_PIN_147_OFF_REGION); // Page 10-4D[2:0], Pin_147
    ScalerSetByte(P10_4E_PIN_SHARE_CTRLB6, (BYTE)_PIN_148_OFF_REGION); // Page 10-4E[2:0], Pin_148
    ScalerSetByte(P10_4F_PIN_SHARE_CTRLB7, (BYTE)_PIN_150_OFF_REGION); // Page 10-4F[2:0], Pin_150
    ScalerSetByte(P10_50_PIN_SHARE_CTRLC0, (BYTE)_PIN_151_OFF_REGION); // Page 10-50[2:0], Pin_151

    ScalerSetByte(P10_51_PIN_SHARE_CTRLC1, (BYTE)_PIN_152_OFF_REGION); // Page 10-51[2:0], Pin_152
    ScalerSetByte(P10_52_PIN_SHARE_CTRLC2, (BYTE)_PIN_153_OFF_REGION); // Page 10-52[2:0], Pin_153
    ScalerSetByte(P10_53_PIN_SHARE_CTRLC3, (BYTE)_PIN_154_OFF_REGION); // Page 10-53[2:0], Pin_154
    ScalerSetByte(P10_54_PIN_SHARE_CTRLC4, (BYTE)_PIN_155_OFF_REGION); // Page 10-54[2:0], Pin_155
    ScalerSetByte(P10_55_PIN_SHARE_CTRLC5, (BYTE)_PIN_156_OFF_REGION); // Page 10-55[2:0], Pin_156
    ScalerSetByte(P10_56_PIN_SHARE_CTRLC6, (BYTE)_PIN_157_OFF_REGION); // Page 10-56[2:0], Pin_157
    ScalerSetByte(P10_57_PIN_SHARE_CTRLC7, (BYTE)_PIN_158_OFF_REGION); // Page 10-57[2:0], Pin_158
    ScalerSetByte(P10_58_PIN_SHARE_CTRLD0, (BYTE)_PIN_159_OFF_REGION); // Page 10-58[2:0], Pin_159
    ScalerSetByte(P10_59_PIN_SHARE_CTRLD1, (BYTE)_PIN_160_OFF_REGION); // Page 10-59[2:0], Pin_160
    ScalerSetByte(P10_5A_PIN_SHARE_CTRLD2, (BYTE)_PIN_161_OFF_REGION); // Page 10-5A[2:0], Pin_161
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
        case _HW_IIC_PIN_179_180:

#if((_PIN_179_OFF_REGION == 8) && (_PIN_180_OFF_REGION == 8))
            ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~_BIT7, _BIT7);
#endif

#if((_PIN_198 == 8) && (_PIN_199 == 8))
            ScalerSetByte(P10_30_PIN_SHARE_CTRL80, 0x00);
            ScalerSetByte(P10_31_PIN_SHARE_CTRL81, 0x00);
#endif

#if((_PIN_210 == 8) && (_PIN_211 == 8))
            ScalerSetByte(P10_3A_PIN_SHARE_CTRL92, 0x00);
            ScalerSetByte(P10_3B_PIN_SHARE_CTRL93, 0x00);
#endif

            break;

        case _HW_IIC_PIN_198_199:

#if((_PIN_198 == 8) && (_PIN_199 == 8))
            ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~_BIT7, _BIT7);
#endif

#if((_PIN_179_OFF_REGION == 8) && (_PIN_180_OFF_REGION == 8))
            ScalerSetByte(P10_26_PIN_SHARE_CTRL66, 0x00);
            ScalerSetByte(P10_27_PIN_SHARE_CTRL67, 0x00);
#endif

#if((_PIN_210 == 8) && (_PIN_211 == 8))
            ScalerSetByte(P10_3A_PIN_SHARE_CTRL92, 0x00);
            ScalerSetByte(P10_3B_PIN_SHARE_CTRL93, 0x00);
#endif

            break;

        case _HW_IIC_PIN_210_211:

#if((_PIN_210 == 8) && (_PIN_211 == 8))
            ScalerSetBit(P10_3A_PIN_SHARE_CTRL92, ~_BIT7, _BIT7);
#endif

#if((_PIN_179_OFF_REGION == 8) && (_PIN_180_OFF_REGION == 8))
            ScalerSetByte(P10_26_PIN_SHARE_CTRL66, 0x00);
            ScalerSetByte(P10_27_PIN_SHARE_CTRL67, 0x00);
#endif

#if((_PIN_198 == 8) && (_PIN_199 == 8))
            ScalerSetByte(P10_30_PIN_SHARE_CTRL80, 0x00);
            ScalerSetByte(P10_31_PIN_SHARE_CTRL81, 0x00);
#endif

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
        case _DDC1_SWITCH_GPIO:
            ScalerSetBit(P10_0A_PIN_SHARE_CTRL32, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Page 10-0A[2:0], Pin_73
            ScalerSetByte(P10_0B_PIN_SHARE_CTRL33, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-0B[2:0], Pin_74
            break;

        case _DDC1_SWITCH_DDC:
            ScalerSetBit(P10_0A_PIN_SHARE_CTRL32, ~_BIT7, 0x00); // Page 10-0A[2:0], Pin_73
            break;

        case _DDC2_SWITCH_GPIO:
            ScalerSetBit(P10_3C_PIN_SHARE_CTRL94, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Page 10-3C[2:0], Pin_212
            ScalerSetByte(P10_3D_PIN_SHARE_CTRL95, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-3D[2:0], Pin_213
            break;

        case _DDC2_SWITCH_DDC:
            ScalerSetBit(P10_3C_PIN_SHARE_CTRL94, ~_BIT7, 0x00); // Page 10-3C[2:0], Pin_212
            break;

        case _DDC3_SWITCH_GPIO:
            ScalerSetBit(P10_3E_PIN_SHARE_CTRL96, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Page 10-3E[2:0], Pin_214
            ScalerSetByte(P10_3F_PIN_SHARE_CTRL97, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-3F[2:0], Pin_215
            break;

        case _DDC3_SWITCH_DDC:
            ScalerSetBit(P10_3E_PIN_SHARE_CTRL96, ~_BIT7, 0x00); // Page 10-3E[2:0], Pin_214
            break;

        case _DDC_VGA_SWITCH_GPIO:
            ScalerSetBit(P10_05_PIN_SHARE_CTRL15, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Page 10-05[2:0], Pin_66
            ScalerSetByte(P10_06_PIN_SHARE_CTRL16, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-06[2:0], Pin_67
            break;

        case _DDC_VGA_SWITCH_DDC:
            ScalerSetBit(P10_05_PIN_SHARE_CTRL15, ~_BIT7, 0x00); // Page 10-05[2:0], Pin_66
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
        case _CONFIG_PIN_1:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_00_PIN_SHARE_CTRL10, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_00_PIN_SHARE_CTRL10, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_00_PIN_SHARE_CTRL10, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_3:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_01_PIN_SHARE_CTRL11, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_01_PIN_SHARE_CTRL11, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_01_PIN_SHARE_CTRL11, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_15:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_02_PIN_SHARE_CTRL12, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_02_PIN_SHARE_CTRL12, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_02_PIN_SHARE_CTRL12, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_53:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_03_PIN_SHARE_CTRL13, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_03_PIN_SHARE_CTRL13, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_03_PIN_SHARE_CTRL13, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_54:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_97:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_5B_PIN_SHARE_CTRLD3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_5B_PIN_SHARE_CTRLD3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_5B_PIN_SHARE_CTRLD3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM1_PP:
                    ScalerSetBit(P10_5B_PIN_SHARE_CTRLD3, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM1_OD:
                    ScalerSetBit(P10_5B_PIN_SHARE_CTRLD3, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_169_OFF_REGION:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_21_PIN_SHARE_CTRL61, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_21_PIN_SHARE_CTRL61, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_21_PIN_SHARE_CTRL61, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_192:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM2_PP:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM2_OD:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_193:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM4_PP:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM4_OD:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_197:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM5_PP:
                    ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM5_OD:
                    ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                default:
                    break;
            }

            break;


        case _CONFIG_PIN_198:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
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
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_SPI_SI_SO_CEB:

            switch(enumFlashDriveConfig)
            {
                case _SPI_DRIVE_3_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT4 | _BIT3 | _BIT2), _BIT3);
                    break;

                case _SPI_DRIVE_3_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
                    break;

                case _SPI_DRIVE_4_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT4 | _BIT3 | _BIT2), _BIT4);
                    break;

                case _SPI_DRIVE_4_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));
                    break;

                case _SPI_DRIVE_5_0MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3));
                    break;

                case _SPI_DRIVE_5_5MA:
                    ScalerSetBit(P10_B2_PIN_DRIVING_CTRL02, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));
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
    ScalerSetBit(P10_76_PIN_SLEW_RATE_CTRL1, ~(_BIT7), (_FLASH_CLK_SLEW_RATE_CONTROL & 0x01) << 7);

    // Setting Flash SPI SI/SO/CEB Pin Slew-Rate Control
    ScalerSetBit(P10_76_PIN_SLEW_RATE_CTRL1, ~(_BIT6), (_FLASH_SI_SO_CEB_SLEW_RATE_CONTROL & 0x01) << 6);
}

//--------------------------------------------------
// Description  : Reset NHL setting when MHL nonsupport
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareCBUSPinInitialReset(void)
{
    if(ScalerGlobalGetIDCode() == _RL6432_VER_A_ID_CODE)
    {
        // Disable 3Ohm Decrease
        ScalerSetBit(P27_0C_ECBUS_PHY_BIST, ~_BIT0, 0x00);
        // Disable 3Ohm Decrease
        ScalerSetBit(P67_0C_ECBUS_PHY_BIST, ~_BIT0, 0x00);
    }
}

