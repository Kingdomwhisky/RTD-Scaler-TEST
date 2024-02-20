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
// ID Code      : RL6463_Series_Mcu.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6463_SERIES_MCU__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions DDCRAM Address
//--------------------------------------------------
#define _EMBEDDED_DDCRAM_VGA_DDC_ADDRESS                    0xE000
#define _EMBEDDED_DDCRAM_DDC0_ADDRESS                       0xE080
#define _EMBEDDED_DDCRAM_DDC1_ADDRESS                       0xE180


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
BYTE xdata MCU_DDCRAM_A0[_A0_EMBEDDED_DDCRAM_MAX_SIZE]          _at_ _EMBEDDED_DDCRAM_VGA_DDC_ADDRESS;
#endif

#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D0_DDC_CHANNEL_SEL == _DDC0)
BYTE xdata MCU_DDCRAM_D0[_D0_EMBEDDED_DDCRAM_MAX_SIZE]          _at_ _EMBEDDED_DDCRAM_DDC0_ADDRESS;
#else
BYTE xdata MCU_DDCRAM_D0[_D0_EMBEDDED_DDCRAM_MAX_SIZE]          _at_ _EMBEDDED_DDCRAM_DDC1_ADDRESS;
#endif // End of _DDC_CHANNEL_FOR_D0

#endif // End of #if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D1_DDC_CHANNEL_SEL == _DDC0)
BYTE xdata MCU_DDCRAM_D1[_D1_EMBEDDED_DDCRAM_MAX_SIZE]          _at_ _EMBEDDED_DDCRAM_DDC0_ADDRESS;
#else
BYTE xdata MCU_DDCRAM_D1[_D1_EMBEDDED_DDCRAM_MAX_SIZE]          _at_ _EMBEDDED_DDCRAM_DDC1_ADDRESS;
#endif // End of _DDC_CHANNEL_FOR_D1

#endif // End of #if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

//--------------------------------------------------
// EMCU PC99 EDID (Page FD)
//--------------------------------------------------
volatile BYTE xdata MCU_FD00_ADC_DDC2_LOAD_EDID_CTRL                _at_ 0xFD00;
volatile BYTE xdata MCU_FD01_D0_LOAD_EDID_CTRL                      _at_ 0xFD01;
volatile BYTE xdata MCU_FD02_D1_LOAD_EDID_CTRL                      _at_ 0xFD02;
volatile BYTE xdata MCU_FD03_ADC_DDC2_EDID_ADDR_H                   _at_ 0xFD03;
volatile BYTE xdata MCU_FD04_ADC_DDC2_EDID_ADDR_M                   _at_ 0xFD04;
volatile BYTE xdata MCU_FD05_ADC_DDC2_EDID_ADDR_L                   _at_ 0xFD05;
volatile BYTE xdata MCU_FD06_D0_EDID_ADDR_H                         _at_ 0xFD06;
volatile BYTE xdata MCU_FD07_D0_EDID_ADDR_M                         _at_ 0xFD07;
volatile BYTE xdata MCU_FD08_D0_EDID_ADDR_L                         _at_ 0xFD08;
volatile BYTE xdata MCU_FD09_D1_EDID_ADDR_H                         _at_ 0xFD09;
volatile BYTE xdata MCU_FD0A_D1_EDID_ADDR_M                         _at_ 0xFD0A;
volatile BYTE xdata MCU_FD0B_D1_EDID_ADDR_L                         _at_ 0xFD0B;
volatile BYTE xdata MCU_FD0C_RETRY_SELECTION                        _at_ 0xFD0C;
volatile BYTE xdata MCU_FD0D_ADC_DDC2_CHECK_RESULT                  _at_ 0xFD0D;
volatile BYTE xdata MCU_FD0E_ADC_DDC2_EDID_CHECKSUM                 _at_ 0xFD0E;
volatile BYTE xdata MCU_FD0F_ADC_DDC2_FINAL_CHECKSUM_RESULT         _at_ 0xFD0F;
volatile BYTE xdata MCU_FD10_D0_CHECK_RESULT                        _at_ 0xFD10;
volatile BYTE xdata MCU_FD11_D0_EDID_CHECKSUM_0                     _at_ 0xFD11;
volatile BYTE xdata MCU_FD12_D0_FINAL_CHECKSUM_RESULT_0             _at_ 0xFD12;
volatile BYTE xdata MCU_FD13_D0_EDID_CHECKSUM_1                     _at_ 0xFD13;
volatile BYTE xdata MCU_FD14_D0_FINAL_CHECKSUM_RESULT_1             _at_ 0xFD14;
volatile BYTE xdata MCU_FD15_D1_CHECK_RESULT                        _at_ 0xFD15;
volatile BYTE xdata MCU_FD16_D1_EDID_CHECKSUM_0                     _at_ 0xFD16;
volatile BYTE xdata MCU_FD17_D1_FINAL_CHECKSUM_RESULT_0             _at_ 0xFD17;
volatile BYTE xdata MCU_FD18_D1_EDID_CHECKSUM_1                     _at_ 0xFD18;
volatile BYTE xdata MCU_FD19_D1_FINAL_CHECKSUM_RESULT_1             _at_ 0xFD19;
volatile BYTE xdata MCU_FD1A_LOAD_EDID_DONE                         _at_ 0xFD1A;
volatile BYTE xdata MCU_FD1B_LOAD_EDID_FSM                          _at_ 0xFD1B;
volatile BYTE xdata MCU_FD1C_RETRY_CNT                              _at_ 0xFD1C;
volatile BYTE xdata MCU_FD20_DUMMY                                  _at_ 0xFD20;


//--------------------------------------------------
// EMCU ADC_DDC2 (Page FD)
//--------------------------------------------------
volatile BYTE xdata MCU_FD30_ADC_DDC2_SEGMENT_ADDRESS               _at_ 0xFD30;
volatile BYTE xdata MCU_FD31_ADC_DDC2_SEGMENT_DATA                  _at_ 0xFD31;
volatile BYTE xdata MCU_FD32_ADC_DDC2_DDC_ENABLE                    _at_ 0xFD32;
volatile BYTE xdata MCU_FD33_ADC_DDC2_DDC_CONTROL_1                 _at_ 0xFD33;
volatile BYTE xdata MCU_FD34_ADC_DDC2_DDC_CONTROL_2                 _at_ 0xFD34;
volatile BYTE xdata MCU_FD35_ADC_DDC2_DDC_INDEX                     _at_ 0xFD35;
volatile BYTE xdata MCU_FD36_ADC_DDC2_DDC_ACCESS_PORT               _at_ 0xFD36;
volatile BYTE xdata MCU_FD37_ADC_DDC2_EDID_IRQ                      _at_ 0xFD37;
volatile BYTE xdata MCU_FD38_ADC_DDC2_RESERVED                      _at_ 0xFD38;


//--------------------------------------------------
// Cache Controller (Page FD)
//--------------------------------------------------
volatile BYTE xdata MCU_FDA0_CACHE_FUNCTION                         _at_ 0xFDA0;
volatile BYTE xdata MCU_FDA1_CACHE_OPTION                           _at_ 0xFDA1;
volatile BYTE xdata MCU_FDA2_CACHE_START_ADDRESS_H                  _at_ 0xFDA2;
volatile BYTE xdata MCU_FDA3_CACHE_START_ADDRESS_M                  _at_ 0xFDA3;
volatile BYTE xdata MCU_FDA4_CACHE_START_ADDRESS_L                  _at_ 0xFDA4;
volatile BYTE xdata MCU_FDA5_CACHE_END_ADDRESS_H                    _at_ 0xFDA5;
volatile BYTE xdata MCU_FDA6_CACHE_END_ADDRESS_M                    _at_ 0xFDA6;
volatile BYTE xdata MCU_FDA7_CACHE_END_ADDRESS_L                    _at_ 0xFDA7;
volatile BYTE xdata MCU_FDA8_CACHE_START_ADDRESS_H2                 _at_ 0xFDA8;
volatile BYTE xdata MCU_FDA9_CACHE_START_ADDRESS_M2                 _at_ 0xFDA9;
volatile BYTE xdata MCU_FDAA_CACHE_START_ADDRESS_L2                 _at_ 0xFDAA;
volatile BYTE xdata MCU_FDAB_CACHE_END_ADDRESS_H2                   _at_ 0xFDAB;
volatile BYTE xdata MCU_FDAC_CACHE_END_ADDRESS_M2                   _at_ 0xFDAC;
volatile BYTE xdata MCU_FDAD_CACHE_END_ADDRESS_L2                   _at_ 0xFDAD;
volatile BYTE xdata MCU_FDAE_COMMON_START_ADDRESS_H                 _at_ 0xFDAE;
volatile BYTE xdata MCU_FDAF_COMMON_START_ADDRESS_L                 _at_ 0xFDAF;
volatile BYTE xdata MCU_FDB0_COMMON_END_ADDRESS_H                   _at_ 0xFDB0;
volatile BYTE xdata MCU_FDB1_COMMON_END_ADDRESS_L                   _at_ 0xFDB1;
volatile BYTE xdata MCU_FDB2_CACHE_ADDRESS_WILD_CARD                _at_ 0xFDB2;
volatile BYTE xdata MCU_FDB3_PERFORMANCE_METER_CONTROL              _at_ 0xFDB3;
volatile BYTE xdata MCU_FDB4_PERFORMANCE_METER_INTERRUPT            _at_ 0xFDB4;
volatile BYTE xdata MCU_FDB5_PERFORMANCE_METER_STATUS               _at_ 0xFDB5;
volatile BYTE xdata MCU_FDB6_PERFORMANCE_METER_LAST_ADDRESS_H       _at_ 0xFDB6;
volatile BYTE xdata MCU_FDB7_PERFORMANCE_METER_LAST_ADDRESS_M       _at_ 0xFDB7;
volatile BYTE xdata MCU_FDB8_PERFORMANCE_METER_LAST_ADDRESS_L       _at_ 0xFDB8;
volatile BYTE xdata MCU_FDB9_PERFORMANCE_METER_REF_COUNT_H          _at_ 0xFDB9;
volatile BYTE xdata MCU_FDBA_PERFORMANCE_METER_REF_COUNT_M1         _at_ 0xFDBA;
volatile BYTE xdata MCU_FDBB_PERFORMANCE_METER_REF_COUNT_M0         _at_ 0xFDBB;
volatile BYTE xdata MCU_FDBC_PERFORMANCE_METER_REF_COUNT_L          _at_ 0xFDBC;
volatile BYTE xdata MCU_FDBD_PERFORMANCE_METER_MISS_COUNT_H         _at_ 0xFDBD;
volatile BYTE xdata MCU_FDBE_PERFORMANCE_METER_MISS_COUNT_M1        _at_ 0xFDBE;
volatile BYTE xdata MCU_FDBF_PERFORMANCE_METER_MISS_COUNT_M0        _at_ 0xFDBF;
volatile BYTE xdata MCU_FDC0_PERFORMANCE_METER_MISS_COUNT_L         _at_ 0xFDC0;
volatile BYTE xdata MCU_FDC1_PERFORMANCE_METER_MEM_RESTART_H        _at_ 0xFDC1;
volatile BYTE xdata MCU_FDC2_PERFORMANCE_METER_MEM_RESTART_M1       _at_ 0xFDC2;
volatile BYTE xdata MCU_FDC3_PERFORMANCE_METER_MEM_RESTART_M0       _at_ 0xFDC3;
volatile BYTE xdata MCU_FDC4_PERFORMANCE_METER_MEM_RESTART_L        _at_ 0xFDC4;
volatile BYTE xdata MCU_FDC5_PERFORMANCE_METER_CRC_H                _at_ 0xFDC5;
volatile BYTE xdata MCU_FDC6_PERFORMANCE_METER_CRC_L                _at_ 0xFDC6;
volatile BYTE xdata MCU_FDC7_CACHE_CONTENT_ADDRESS_H                _at_ 0xFDC7;
volatile BYTE xdata MCU_FDC8_CACHE_CONTENT_ADDRESS_L                _at_ 0xFDC8;
volatile BYTE xdata MCU_FDC9_CACHE_CONTENT_DATA                     _at_ 0xFDC9;
volatile BYTE xdata MCU_FDCA_CACHE_SRAM_BIST_CTRL                   _at_ 0xFDCA;
volatile BYTE xdata MCU_FDCB_CACHE_SRAM_DRF_BIST_CTRL               _at_ 0xFDCB;
volatile BYTE xdata MCU_FDCC_CACHE_LOAD_CTRL                        _at_ 0xFDCC;


//--------------------------------------------------
// EMCU GPIO Control (Page FE)
//--------------------------------------------------
volatile BYTE xdata MCU_FE00_PORT40_PIN_REG                         _at_ 0xFE00;
volatile BYTE xdata MCU_FE01_PORT41_PIN_REG                         _at_ 0xFE01;
volatile BYTE xdata MCU_FE02_PORT42_PIN_REG                         _at_ 0xFE02;
volatile BYTE xdata MCU_FE03_PORT43_PIN_REG                         _at_ 0xFE03;
volatile BYTE xdata MCU_FE04_PORT44_PIN_REG                         _at_ 0xFE04;
volatile BYTE xdata MCU_FE05_PORT45_PIN_REG                         _at_ 0xFE05;
volatile BYTE xdata MCU_FE06_PORT46_PIN_REG                         _at_ 0xFE06;
volatile BYTE xdata MCU_FE07_PORT47_PIN_REG                         _at_ 0xFE07;
volatile BYTE xdata MCU_FE08_PORT50_PIN_REG                         _at_ 0xFE08;
volatile BYTE xdata MCU_FE09_PORT51_PIN_REG                         _at_ 0xFE09;
volatile BYTE xdata MCU_FE0A_PORT52_PIN_REG                         _at_ 0xFE0A;
volatile BYTE xdata MCU_FE0B_PORT53_PIN_REG                         _at_ 0xFE0B;
volatile BYTE xdata MCU_FE0C_PORT54_PIN_REG                         _at_ 0xFE0C;
volatile BYTE xdata MCU_FE0D_PORT55_PIN_REG                         _at_ 0xFE0D;
volatile BYTE xdata MCU_FE0E_PORT56_PIN_REG                         _at_ 0xFE0E;
volatile BYTE xdata MCU_FE0F_PORT57_PIN_REG                         _at_ 0xFE0F;
volatile BYTE xdata MCU_FE10_PORT60_PIN_REG                         _at_ 0xFE10;
volatile BYTE xdata MCU_FE11_PORT61_PIN_REG                         _at_ 0xFE11;
volatile BYTE xdata MCU_FE12_PORT62_PIN_REG                         _at_ 0xFE12;
volatile BYTE xdata MCU_FE13_PORT63_PIN_REG                         _at_ 0xFE13;
volatile BYTE xdata MCU_FE14_PORT64_PIN_REG                         _at_ 0xFE14;
volatile BYTE xdata MCU_FE15_PORT65_PIN_REG                         _at_ 0xFE15;
volatile BYTE xdata MCU_FE16_PORT66_PIN_REG                         _at_ 0xFE16;
volatile BYTE xdata MCU_FE17_PORT67_PIN_REG                         _at_ 0xFE17;
volatile BYTE xdata MCU_FE18_PORT70_PIN_REG                         _at_ 0xFE18;
volatile BYTE xdata MCU_FE19_PORT71_PIN_REG                         _at_ 0xFE19;
volatile BYTE xdata MCU_FE1A_PORT72_PIN_REG                         _at_ 0xFE1A;
volatile BYTE xdata MCU_FE1B_PORT73_PIN_REG                         _at_ 0xFE1B;
volatile BYTE xdata MCU_FE1C_PORT74_PIN_REG                         _at_ 0xFE1C;
volatile BYTE xdata MCU_FE1D_PORT75_PIN_REG                         _at_ 0xFE1D;
volatile BYTE xdata MCU_FE1E_PORT76_PIN_REG                         _at_ 0xFE1E;
volatile BYTE xdata MCU_FE1F_PORT77_PIN_REG                         _at_ 0xFE1F;
volatile BYTE xdata MCU_FE20_PORT80_PIN_REG                         _at_ 0xFE20;
volatile BYTE xdata MCU_FE21_PORT81_PIN_REG                         _at_ 0xFE21;
volatile BYTE xdata MCU_FE22_PORT82_PIN_REG                         _at_ 0xFE22;
volatile BYTE xdata MCU_FE23_PORT83_PIN_REG                         _at_ 0xFE23;
volatile BYTE xdata MCU_FE24_PORT84_PIN_REG                         _at_ 0xFE24;
volatile BYTE xdata MCU_FE25_PORT85_PIN_REG                         _at_ 0xFE25;
volatile BYTE xdata MCU_FE26_PORT86_PIN_REG                         _at_ 0xFE26;
volatile BYTE xdata MCU_FE27_PORT87_PIN_REG                         _at_ 0xFE27;
volatile BYTE xdata MCU_FE60_PORT_READ_CONTROL                      _at_ 0xFE60;
volatile BYTE xdata MCU_FE61_DUMMY_4                                _at_ 0xFE61;


//--------------------------------------------------
// EMCU DDC-CI Part 0 (Page FE)
//--------------------------------------------------
volatile BYTE xdata MCU_FE86_IIC_1_CH_SEL                           _at_ 0xFE86;
volatile BYTE xdata MCU_FE87_IIC_1_SET_SLAVE                        _at_ 0xFE87;
volatile BYTE xdata MCU_FE88_IIC_1_SUB_IN                           _at_ 0xFE88;
volatile BYTE xdata MCU_FE89_IIC_1_DATA_IN                          _at_ 0xFE89;
volatile BYTE xdata MCU_FE8A_IIC_1_DATA_OUT                         _at_ 0xFE8A;
volatile BYTE xdata MCU_FE8B_IIC_1_STATUS                           _at_ 0xFE8B;
volatile BYTE xdata MCU_FE8C_IIC_1_IRQ_CONTROL                      _at_ 0xFE8C;
volatile BYTE xdata MCU_FE8D_IIC_1_STATUS2                          _at_ 0xFE8D;
volatile BYTE xdata MCU_FE8E_IIC_1_IRQ_CONTROL2                     _at_ 0xFE8E;
volatile BYTE xdata MCU_FE8F_IIC_1_CHANNEL_CONTROL                  _at_ 0xFE8F;
volatile BYTE xdata MCU_FE90_DDCCI_1_NULL_BYTE1                     _at_ 0xFE90;
volatile BYTE xdata MCU_FE91_DDCCI_1_NULL_BYTE2                     _at_ 0xFE91;
volatile BYTE xdata MCU_FE92_DDCCI_1_NULL_BYTE3                     _at_ 0xFE92;
volatile BYTE xdata MCU_FE93_DDCCI_1_REMAIN_DATA                    _at_ 0xFE93;


//--------------------------------------------------
// EMCU DDCRAM Settings (Page FE)
//--------------------------------------------------
volatile BYTE xdata MCU_FEB1_DDCRAM_ST_ADDRESS                      _at_ 0xFEB1;
volatile BYTE xdata MCU_FEB2_XRAM_BIST_CTRL                         _at_ 0xFEB2;
volatile BYTE xdata MCU_FEB3_XRAM_DRF_BIST_CTRL                     _at_ 0xFEB3;
volatile BYTE xdata MCU_FEB4_MCU_DUMMY2                             _at_ 0xFEB4;


//--------------------------------------------------
// EMCU Interrupt Control Part 1 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF00_IRQ_STATUS                             _at_ 0xFF00;


//--------------------------------------------------
// EMCU OSD Reorder Part 1 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF03_TRIPLE_BYTES_OPERATION                 _at_ 0xFF03;
volatile BYTE xdata MCU_FF04_SHIFT_BITS_NUMBER                      _at_ 0xFF04;
volatile BYTE xdata MCU_FF05_SHIFT_BYTE_ADDRESS                     _at_ 0xFF05;
volatile BYTE xdata MCU_FF06_INPUT_TRIPLE_BYTES                     _at_ 0xFF06;
volatile BYTE xdata MCU_FF07_RESULT_TRIPLE_BYTES                    _at_ 0xFF07;


//--------------------------------------------------
// EMCU LSADC (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF08_ADC_ACONTROL                           _at_ 0xFF08;
volatile BYTE xdata MCU_FF09_ADC_A0_CONVERT_RESULT                  _at_ 0xFF09;
volatile BYTE xdata MCU_FF0A_ADC_A1_CONVERT_RESULT                  _at_ 0xFF0A;
volatile BYTE xdata MCU_FF0B_ADC_A2_CONVERT_RESULT                  _at_ 0xFF0B;
volatile BYTE xdata MCU_FF0C_ADC_A3_CONVERT_RESULT                  _at_ 0xFF0C;
volatile BYTE xdata MCU_FF0D_ADC_CLK_DIV                            _at_ 0xFF0D;
volatile BYTE xdata MCU_FF0E_AUTO_MODE_CTRL01                       _at_ 0xFF0E;
volatile BYTE xdata MCU_FF0F_ADC0_THRESHOLD_H                       _at_ 0xFF0F;
volatile BYTE xdata MCU_FF10_ADC0_THRESHOLD_L                       _at_ 0xFF10;
volatile BYTE xdata MCU_FF11_ADC1_THRESHOLD_H                       _at_ 0xFF11;
volatile BYTE xdata MCU_FF12_ADC1_THRESHOLD_L                       _at_ 0xFF12;
volatile BYTE xdata MCU_FF13_ADC2_THRESHOLD_H                       _at_ 0xFF13;
volatile BYTE xdata MCU_FF14_ADC2_THRESHOLD_L                       _at_ 0xFF14;
volatile BYTE xdata MCU_FF15_ADC3_THRESHOLD_H                       _at_ 0xFF15;
volatile BYTE xdata MCU_FF16_ADC3_THRESHOLD_L                       _at_ 0xFF16;
volatile BYTE xdata MCU_FF17_CTRL0_WAIT_TIME_VALUE                  _at_ 0xFF17;


//--------------------------------------------------
// EMCU OSD Reorder Part 2 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF18_BYTE_ADDRESS                           _at_ 0xFF18;


//--------------------------------------------------
// EMCU DDC Part 1 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF19_ADC_SEGMENT_ADDRESS                    _at_ 0xFF19;
volatile BYTE xdata MCU_FF1A_ADC_SEGMENT_DATA                       _at_ 0xFF1A;
volatile BYTE xdata MCU_FF1B_ADC_DDC_ENABLE                         _at_ 0xFF1B;
volatile BYTE xdata MCU_FF1C_ADC_DDC_CONTROL_1                      _at_ 0xFF1C;
volatile BYTE xdata MCU_FF1D_ADC_DDC_CONTROL_2                      _at_ 0xFF1D;
volatile BYTE xdata MCU_FF1E_DDC0_DDC_ENABLE                        _at_ 0xFF1E;
volatile BYTE xdata MCU_FF1F_DDC0_DDC_CONTROL_1                     _at_ 0xFF1F;
volatile BYTE xdata MCU_FF20_DDC0_DDC_CONTROL_2                     _at_ 0xFF20;


//--------------------------------------------------
// EMCU DDC-CI Part 1 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF22_IIC_CH_SEL                             _at_ 0xFF22;
volatile BYTE xdata MCU_FF23_IIC_SET_SLAVE                          _at_ 0xFF23;
volatile BYTE xdata MCU_FF24_IIC_SUB_IN                             _at_ 0xFF24;
volatile BYTE xdata MCU_FF25_IIC_DATA_IN                            _at_ 0xFF25;
volatile BYTE xdata MCU_FF26_IIC_DATA_OUT                           _at_ 0xFF26;
volatile BYTE xdata MCU_FF27_IIC_STATUS                             _at_ 0xFF27;
volatile BYTE xdata MCU_FF28_IIC_IRQ_CONTROL                        _at_ 0xFF28;
volatile BYTE xdata MCU_FF29_IIC_STATUS2                            _at_ 0xFF29;
volatile BYTE xdata MCU_FF2A_IIC_IRQ_CONTROL2                       _at_ 0xFF2A;
volatile BYTE xdata MCU_FF2B_IIC_CHANNEL_CONTROL                    _at_ 0xFF2B;


//--------------------------------------------------
// EMCU DDC Part 2 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF2C_DDC1_DDC_ENABLE                        _at_ 0xFF2C;
volatile BYTE xdata MCU_FF2D_DDC1_DDC_CONTROL_1                     _at_ 0xFF2D;
volatile BYTE xdata MCU_FF2E_DDC1_DDC_CONTROL_2                     _at_ 0xFF2E;
volatile BYTE xdata MCU_FF2F_ADC_DDC_INDEX                          _at_ 0xFF2F;
volatile BYTE xdata MCU_FF30_ADC_DDC_ACCESS_PORT                    _at_ 0xFF30;
volatile BYTE xdata MCU_FF31_DDC0_DDC_INDEX                         _at_ 0xFF31;
volatile BYTE xdata MCU_FF32_DDC0_DDC_ACCESS_PORT                   _at_ 0xFF32;
volatile BYTE xdata MCU_FF33_DDC1_DDC_INDEX                         _at_ 0xFF33;
volatile BYTE xdata MCU_FF34_DDC1_DDC_ACCESS_PORT                   _at_ 0xFF34;
volatile BYTE xdata MCU_FF35_DDCCI_REMAIN_DATA                      _at_ 0xFF35;
volatile BYTE xdata MCU_FF36_DDC0_SEGMENT_ADDRESS                   _at_ 0xFF36;
volatile BYTE xdata MCU_FF37_DDC0_SEGMENT_DATA                      _at_ 0xFF37;
volatile BYTE xdata MCU_FF38_DDC1_SEGMENT_ADDRESS                   _at_ 0xFF38;
volatile BYTE xdata MCU_FF39_DDC1_SEGMENT_DATA                      _at_ 0xFF39;


//--------------------------------------------------
// EMCU PWM Part 1 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF3A_PWM_CK_SEL                             _at_ 0xFF3A;
volatile BYTE xdata MCU_FF3B_PWM03_M                                _at_ 0xFF3B;
volatile BYTE xdata MCU_FF3C_PWM45_M                                _at_ 0xFF3C;
volatile BYTE xdata MCU_FF3D_PWM01_N_MSB                            _at_ 0xFF3D;
volatile BYTE xdata MCU_FF3E_PWM0_N_LSB                             _at_ 0xFF3E;
volatile BYTE xdata MCU_FF3F_PWM1_N_LSB                             _at_ 0xFF3F;
volatile BYTE xdata MCU_FF40_PWM23_N_MSB                            _at_ 0xFF40;
volatile BYTE xdata MCU_FF41_PWM2_N_LSB                             _at_ 0xFF41;
volatile BYTE xdata MCU_FF42_PWM3_N_LSB                             _at_ 0xFF42;
volatile BYTE xdata MCU_FF43_PWM45_N_MSB                            _at_ 0xFF43;
volatile BYTE xdata MCU_FF44_PWM4_N_LSB                             _at_ 0xFF44;
volatile BYTE xdata MCU_FF45_PWM5_N_LSB                             _at_ 0xFF45;
volatile BYTE xdata MCU_FF46_PWML                                   _at_ 0xFF46;
volatile BYTE xdata MCU_FF47_PWM_VS_CTRL                            _at_ 0xFF47;
volatile BYTE xdata MCU_FF48_PWM_EN                                 _at_ 0xFF48;
volatile BYTE xdata MCU_FF49_PWM_CK                                 _at_ 0xFF49;
volatile BYTE xdata MCU_FF4A_PWM0H_DUT                              _at_ 0xFF4A;
volatile BYTE xdata MCU_FF4B_PWM1H_DUT                              _at_ 0xFF4B;
volatile BYTE xdata MCU_FF4C_PWM01L_DUT                             _at_ 0xFF4C;
volatile BYTE xdata MCU_FF4D_PWM2H_DUT                              _at_ 0xFF4D;
volatile BYTE xdata MCU_FF4E_PWM3H_DUT                              _at_ 0xFF4E;
volatile BYTE xdata MCU_FF4F_PWM23L_DUT                             _at_ 0xFF4F;
volatile BYTE xdata MCU_FF50_PWM4H_DUT                              _at_ 0xFF50;
volatile BYTE xdata MCU_FF51_PWM5H_DUT                              _at_ 0xFF51;
volatile BYTE xdata MCU_FF52_PWM45L_DUT                             _at_ 0xFF52;
volatile BYTE xdata MCU_FF53_PWM_DUT_TYPE                           _at_ 0xFF53;
volatile BYTE xdata MCU_FF54_PWM_CNT_MODE                           _at_ 0xFF54;


//--------------------------------------------------
// EMCU I2C Control Module (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF55_I2CM_CR0                               _at_ 0xFF55;
volatile BYTE xdata MCU_FF56_I2CM_CR1                               _at_ 0xFF56;
volatile BYTE xdata MCU_FF57_I2CM_CR2                               _at_ 0xFF57;
volatile BYTE xdata MCU_FF58_I2CM_CR3                               _at_ 0xFF58;
volatile BYTE xdata MCU_FF59_I2CM_STR0                              _at_ 0xFF59;
volatile BYTE xdata MCU_FF5A_I2CM_STR1                              _at_ 0xFF5A;
volatile BYTE xdata MCU_FF5B_I2CM_STR2                              _at_ 0xFF5B;
volatile BYTE xdata MCU_FF5C_I2CM_STR3                              _at_ 0xFF5C;
volatile BYTE xdata MCU_FF5D_I2CM_SR                                _at_ 0xFF5D;
volatile BYTE xdata MCU_FF5E_I2CM_TD                                _at_ 0xFF5E;
volatile BYTE xdata MCU_FF5F_I2CM_CCR                               _at_ 0xFF5F;


//--------------------------------------------------
// EMCU SPI-FLASH Part 1 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF60_COMMON_INST_EN                         _at_ 0xFF60;
volatile BYTE xdata MCU_FF61_COMMON_OP_CODE                         _at_ 0xFF61;
volatile BYTE xdata MCU_FF62_WREN_OP_CODE                           _at_ 0xFF62;
volatile BYTE xdata MCU_FF63_EWSR_OP_CODE                           _at_ 0xFF63;
volatile BYTE xdata MCU_FF64_FLASH_PROG_ISP0                        _at_ 0xFF64;
volatile BYTE xdata MCU_FF65_FLASH_PROG_ISP1                        _at_ 0xFF65;
volatile BYTE xdata MCU_FF66_FLASH_PROG_ISP2                        _at_ 0xFF66;
volatile BYTE xdata MCU_FF67_COMMON_INST_READ_PORT0                 _at_ 0xFF67;
volatile BYTE xdata MCU_FF68_COMMON_INST_READ_PORT1                 _at_ 0xFF68;
volatile BYTE xdata MCU_FF69_COMMON_INST_READ_PORT2                 _at_ 0xFF69;
volatile BYTE xdata MCU_FF6A_READ_OP_CODE                           _at_ 0xFF6A;
volatile BYTE xdata MCU_FF6B_FAST_READ_OP_CODE                      _at_ 0xFF6B;
volatile BYTE xdata MCU_FF6C_READ_INSTRUCTION                       _at_ 0xFF6C;
volatile BYTE xdata MCU_FF6D_PROGRAM_OP_CODE                        _at_ 0xFF6D;
volatile BYTE xdata MCU_FF6E_READ_STATUS_REGISTER_OP_CODE           _at_ 0xFF6E;
volatile BYTE xdata MCU_FF6F_PROGRAM_INSTRUCTION                    _at_ 0xFF6F;
volatile BYTE xdata MCU_FF70_PROGRAM_DATA_PORT                      _at_ 0xFF70;
volatile BYTE xdata MCU_FF71_PROGRAM_LENGTH                         _at_ 0xFF71;
volatile BYTE xdata MCU_FF72_CRC_END_ADDR0                          _at_ 0xFF72;
volatile BYTE xdata MCU_FF73_CRC_END_ADDR1                          _at_ 0xFF73;
volatile BYTE xdata MCU_FF74_CRC_END_ADDR2                          _at_ 0xFF74;
volatile BYTE xdata MCU_FF75_CRC_RESULT                             _at_ 0xFF75;
volatile BYTE xdata MCU_FF76_CEN_CTRL                               _at_ 0xFF76;
volatile BYTE xdata MCU_FF77_REV_DUMMY4                             _at_ 0xFF77;
volatile BYTE xdata MCU_FF78_ACCESS_FLASH_ADDR_0                    _at_ 0xFF78;
volatile BYTE xdata MCU_FF79_ACCESS_FLASH_ADDR_1                    _at_ 0xFF79;
volatile BYTE xdata MCU_FF7A_ACCESS_FLASH_ADDR_2                    _at_ 0xFF7A;
volatile BYTE xdata MCU_FF7B_ACCESS_FLASH_DATA_PORT                 _at_ 0xFF7B;
volatile BYTE xdata MCU_FF7C_ACCESS_FLASH_DATA_CTRL                 _at_ 0xFF7C;
volatile BYTE xdata MCU_FF80_AAI_MODE_BYTE_NUM                      _at_ 0xFF80;
volatile BYTE xdata MCU_FF81_ISP_CMD_INSERT                         _at_ 0xFF81;
volatile BYTE xdata MCU_FF82_ISP_CMD_LENGTH                         _at_ 0xFF82;


//--------------------------------------------------
// EMCU PWM Part 2 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF90_PWM01_TOTALCNT_MSB                     _at_ 0xFF90;
volatile BYTE xdata MCU_FF91_PWM0_TOTALCNT_LSB                      _at_ 0xFF91;
volatile BYTE xdata MCU_FF92_PWM1_TOTALCNT_LSB                      _at_ 0xFF92;
volatile BYTE xdata MCU_FF93_PWM23_TOTALCNT_MSB                     _at_ 0xFF93;
volatile BYTE xdata MCU_FF94_PWM2_TOTALCNT_LSB                      _at_ 0xFF94;
volatile BYTE xdata MCU_FF95_PWM3_TOTALCNT_LSB                      _at_ 0xFF95;
volatile BYTE xdata MCU_FF96_PWM45_TOTALCNT_MSB                     _at_ 0xFF96;
volatile BYTE xdata MCU_FF97_PWM4_TOTALCNT_LSB                      _at_ 0xFF97;
volatile BYTE xdata MCU_FF98_PWM5_TOTALCNT_LSB                      _at_ 0xFF98;
volatile BYTE xdata MCU_FF99_PWM_CK_SEL_HS                          _at_ 0xFF99;
volatile BYTE xdata MCU_FF9A_PWM01_CYCLE_MAX                        _at_ 0xFF9A;
volatile BYTE xdata MCU_FF9B_PWM23_CYCLE_MAX                        _at_ 0xFF9B;
volatile BYTE xdata MCU_FF9C_PWM45_CYCLE_MAX                        _at_ 0xFF9C;


//--------------------------------------------------
// EMCU Watchdog Counter Part 1 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFAA_WATCHDOG_CNT2_VALUE                    _at_ 0xFFAA;
volatile BYTE xdata MCU_FFAB_WATCHDOG_CNT23_VALUE                   _at_ 0xFFAB;
volatile BYTE xdata MCU_FFAC_WATCHDOG_CNT3_VALUE                    _at_ 0xFFAC;
volatile BYTE xdata MCU_FFAD_WATCHDOG_CNT1_VALUE                    _at_ 0xFFAD;
volatile BYTE xdata MCU_FFAE_WATCHDOG_TIMER_THRESHOLD               _at_ 0xFFAE;
volatile BYTE xdata MCU_FFAF_WATCHDOG_TIMER_THRESHOLD_MASK          _at_ 0xFFAF;
volatile BYTE xdata MCU_FFB0_WATCHDOG_TIMER_H_THRESHOLD_MASK        _at_ 0xFFB0;


//--------------------------------------------------
// EMCU DDCCI Part 2 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFB1_DDCCI_NULL_BYTE1                       _at_ 0xFFB1;
volatile BYTE xdata MCU_FFB2_DDCCI_NULL_BYTE2                       _at_ 0xFFB2;
volatile BYTE xdata MCU_FFB3_DDCCI_NULL_BYTE3                       _at_ 0xFFB3;


//--------------------------------------------------
// EMCU Interrupt Control Part 0 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFB8_EXT_INT0_CONTROL                       _at_ 0xFFB8;
volatile BYTE xdata MCU_FFB9_EXT_INT1_CONTROL                       _at_ 0xFFB9;


//--------------------------------------------------
// EMCU Test Mode (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFBB_PERI_TEST                              _at_ 0xFFBB;
volatile BYTE xdata MCU_FFBC_CYCLE_GATING                           _at_ 0xFFBC;
volatile BYTE xdata MCU_FFBD_MCU_CLK_DIV_R                          _at_ 0xFFBD;
volatile BYTE xdata MCU_FFBE_MCU_DUMMY                              _at_ 0xFFBE;


//--------------------------------------------------
// EMCU Interrupt Control Part 2 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFC2_IRQ_PRIORITY_1                         _at_ 0xFFC2;
volatile BYTE xdata MCU_FFC3_IRQ_PRIORITY_2                         _at_ 0xFFC3;
volatile BYTE xdata MCU_FFC4_IRQ_PRIORITY_3                         _at_ 0xFFC4;


//--------------------------------------------------
// EMCU SFR Access (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFE2_PORT1_PIN_REG                          _at_ 0xFFE2;
volatile BYTE xdata MCU_FFE3_PORT3_PIN_REG                          _at_ 0xFFE3;


//--------------------------------------------------
// EMCU DDC Part 3 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFE4_DDC0_EDID_IRQ                          _at_ 0xFFE4;
volatile BYTE xdata MCU_FFE5_DDC1_EDID_IRQ                          _at_ 0xFFE5;
volatile BYTE xdata MCU_FFE7_VGA_EDID_IRQ                           _at_ 0xFFE7;


//--------------------------------------------------
// EMCU In System Programming Part 1 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFE8_ISP_CONTROL                            _at_ 0xFFE8;
volatile BYTE xdata MCU_FFE9_MCU_CLK_CONTROL_1                      _at_ 0xFFE9;


//--------------------------------------------------
// EMCU Watchdog Timer Part 2 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFEA_WATCHDOG_TIMER                         _at_ 0xFFEA;
volatile BYTE xdata MCU_FFEB_WDT_TEST                               _at_ 0xFFEB;


//--------------------------------------------------
// EMCU In System Programming Part 2 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFEC_ISP_SLAVE_ADDRESS                      _at_ 0xFFEC;
volatile BYTE xdata MCU_FFED_MCU_CONTROL                            _at_ 0xFFED;
volatile BYTE xdata MCU_FFEE_MCU_CLOCK_CONTROL                      _at_ 0xFFEE;
volatile BYTE xdata MCU_FFEF_RAM_TEST                               _at_ 0xFFEF;


//--------------------------------------------------
// EMCU Xdata-SPI-FLASH Write Protect (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFF0_XDATA_SPI_FLASH_WRITE_PROTECT          _at_ 0xFFF0;
volatile BYTE xdata MCU_FFF1_SCA_WR_INTRVL                          _at_ 0xFFF1;
volatile BYTE xdata MCU_FFF2_PWM_I2C_CLOCK_STOP                     _at_ 0xFFF2;


//--------------------------------------------------
// EMCU Scalar Interface (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFF3_SCA_INF_CONTROL                        _at_ 0xFFF3;
volatile BYTE xdata MCU_FFF4_SCA_INF_ADDR                           _at_ 0xFFF4;
volatile BYTE xdata MCU_FFF5_SCA_INF_DATA                           _at_ 0xFFF5;
volatile BYTE xdata MCU_FFF6_SCA_INF_BWR_ADRH                       _at_ 0xFFF6;
volatile BYTE xdata MCU_FFF7_SCA_INF_BWR_ADRM                       _at_ 0xFFF7;
volatile BYTE xdata MCU_FFF8_SCA_INF_BWR_ADRL                       _at_ 0xFFF8;
volatile BYTE xdata MCU_FFF9_SCA_INF_BWR_COUNT_H                    _at_ 0xFFF9;
volatile BYTE xdata MCU_FFFA_SCA_INF_BWR_COUNT_L                    _at_ 0xFFFA;
volatile BYTE xdata MCU_FFFB_SCA_INF_PERIOD                         _at_ 0xFFFB;


//--------------------------------------------------
// EMCU Bankswitch (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFFC_BANK_SWICH_CONTROL                     _at_ 0xFFFC;
volatile BYTE xdata MCU_FFFD_XDATA_BANK_START                       _at_ 0xFFFD;
volatile BYTE xdata MCU_FFFE_XDATA_BANK_SEL                         _at_ 0xFFFE;
volatile BYTE xdata MCU_FFFF_PBANK_SWITCH                           _at_ 0xFFFF;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMcuMemoryZeroInit(void);
void ScalerMcuDdcDebounceSel(EnumClkSel enumClock);
void ScalerMcuDdcciSwitchPort(EnumDDCCIDebugMode enumMode, BYTE ucInputPort);
#if(_DDCCI_CODE_REDUCTION == _OFF)
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
void ScalerMcuDdcciAutoSwitchInactiveChannel(bit bEnable);
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
void ScalerMcuDdcciAutoSwitchInactiveChannel_EXINT1(bit bEnable);
#endif
#endif
#endif
void ScalerMcuGpioInitial(void);
void ScalerMcuDdcInitial(void);
void ScalerMcuDdcRamEnable(void);

void ScalerMcuDdcciInitial(void);

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
void ScalerMcuDdcciReleaseScl(void);
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
void ScalerMcuDdcciHoldScl_EXINT1(void);
#endif
#endif

void ScalerMcuSetISPChannel(WORD usISPChannel);

void ScalerMcuDdcISPChannelCtrl(BYTE ucDdcChannel, bit bEnable);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : MCU memory init in startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void ScalerMcuMemoryZeroInit(void)
{
    // Initialize data/idata to 0 in [8 : (SP + 1 - 2)]
#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER) && (_FLASH_PARTITION_RELOCATABLE_SUPPORT == _ON))
    // skip address for _BOOT_BANK_OFFSET_ADDR
    memset((volatile BYTE data *)0x08, 0, (0x30 - 0x08));
    memset((volatile BYTE data *)(0x30 + 1), 0, ((SP - 0x01) - (0x30 + 1)));
#else
    memset((volatile BYTE data *)0x08, 0, ((SP - 0x01) - 0x08));
#endif

#if(_HW_PC99_SUPPORT == _ON)

#if((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) ||\
    (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99) ||\
    (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99))

#if(_A0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
    // A0 Port Xdata Init to 0
    memset((volatile BYTE xdata *)_EMBEDDED_DDCRAM_VGA_DDC_ADDRESS, 0, 0x80);
#endif

#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
    // D0 Port Xdata Init to 0
    memset((volatile BYTE xdata *)_EMBEDDED_DDCRAM_DDC0_ADDRESS, 0, 0x100);
#endif


#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
    // D1 Port Xdata Init to 0
    memset((volatile BYTE xdata *)_EMBEDDED_DDCRAM_DDC1_ADDRESS, 0, 0x100);
#endif

    memset((volatile BYTE xdata *)(_XRAM_ADDR_START + 0x280), 0, (_XRAM_ADDR_END - (_XRAM_ADDR_START + 0x280) + 1));

#else

    // Initialize all xdata to 0
    memset((volatile BYTE xdata *)_XRAM_ADDR_START, 0, (_XRAM_ADDR_END - _XRAM_ADDR_START + 1));

#endif

#endif // End of #if(_HW_PC99_SUPPORT == _ON)

}
#pragma restore

//--------------------------------------------------
// Description  : DDC Debounce Settings
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcDebounceSel(EnumClkSel enumClock)
{
    enumClock = enumClock;

    // VGA_DDC De-bounce Reference Clock(IOSC = 28M) div by 4, latch 3 stages
    MCU_FF1C_ADC_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);

    // VGA_DDC2 De-bounce Reference Clock(IOSC = 28M) div by 4, latch 3 stages
    MCU_FD33_ADC_DDC2_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC0)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC0)))
    // DDC0 De-bounce Reference Clock(IOSC = 27M) div by 2, latch 1 stages
    MCU_FF1F_DDC0_DDC_CONTROL_1 &= ~(_BIT7);
    MCU_FF1F_DDC0_DDC_CONTROL_1 |= (_BIT6 | _BIT4);
#elif(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC0)) ||\
      ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC0)))
    // DDC0 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
    MCU_FF1F_DDC0_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC1)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC1)))
    // DDC1 De-bounce Reference Clock(IOSC = 27M) div by 2, latch 1 stages
    MCU_FF2D_DDC1_DDC_CONTROL_1 &= ~(_BIT7);
    MCU_FF2D_DDC1_DDC_CONTROL_1 |= (_BIT6 | _BIT4);
#elif(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC1)) ||\
      ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC1)))
    // DDC1 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
    MCU_FF2D_DDC1_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC2)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC2)))
    // DDC2 De-bounce Reference Clock(IOSC = 27M) div by 2, latch 1 stages
    MCU_FE65_DDC2_DDC_CONTROL_1 &= ~(_BIT7);
    MCU_FE65_DDC2_DDC_CONTROL_1 |= (_BIT6 | _BIT4);
#elif(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC2)) ||\
      ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC2)))
    // DDC2 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
    MCU_FE65_DDC2_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);
#endif
}

//--------------------------------------------------
// Description  : DDCCI switch DDC Port
// Input Value  : enumMode --> Debug or DDCCI Mode
//                ucInputPort --> Input Port Type
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciSwitchPort(EnumDDCCIDebugMode enumMode, BYTE ucInputPort)
{
#if(_AUTO_TEST_SUPPORT == _ON)
    // Set slave address for DDCCI
    MCU_FF23_IIC_SET_SLAVE = 0x3E;

    // Disable STOP_I, Enable D_IN_I, SUB_I interrupts
    MCU_FF28_IIC_IRQ_CONTROL &= ~_BIT4;
    MCU_FF28_IIC_IRQ_CONTROL |= _BIT2 | _BIT1;

    return;
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    // Force to debug mode when debug message is enable
    enumMode = _DEBUG_MODE;
#endif

    // Disable STOP_I, D_IN_I, SUB_I interrupts
    MCU_FF28_IIC_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1);

    if(enumMode == _DDCCI_MODE)
    {
        // Set slave address for DDCCI
        MCU_FF23_IIC_SET_SLAVE = 0x6E;
        // Debug Mode Change to DDCCI Mode Need Clear IRQ Flag
        if(ScalerDebugGetDDCCIDebugMode() != enumMode)
        {
            // Clear IRQ FLag
            MCU_FF27_IIC_STATUS = 0x00;
            // Read IIC Data In(0xFF25) to Clear Data In Flag
            pData[0] = MCU_FF25_IIC_DATA_IN;
            // Write IIC Data Out(0xFF26) to Clear Data Out Flag
            MCU_FF26_IIC_DATA_OUT = 0x00;
            // Clear IIC Buffer Overflow or Underflow Flag
            MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);
            // Reset IIC Buffer
            MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
        }
        // Enable D_IN_I, SUB_I interrupts
        MCU_FF28_IIC_IRQ_CONTROL |= _BIT2 | _BIT1;

        switch(ucInputPort)
        {
            case _A0_INPUT_PORT:

                if(GET_A0_DDC_CHANNEL_SEL() == _VGA_DDC2)
                {
                    // DDCCI switch to VGA_DDC2
                    MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
                    MCU_FF22_IIC_CH_SEL |= _BIT3;
                }
                else
                {
                    // DDCCI switch to VGA_DDC
                    MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
                }

                break;

            case _D0_INPUT_PORT:

                // DDCCI switch to DDC0 if D0 is assigned to DDC0
                MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
                MCU_FF22_IIC_CH_SEL |= _BIT0;

                break;

            case _D1_INPUT_PORT:

                // DDCCI switch to DDC1 if D1 is assigned to DDC1
                MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
                MCU_FF22_IIC_CH_SEL |= _BIT1;

                break;

            default:
                break;
        }
    }
    else
    {
#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
        // Return DDCCI to Normal Judge Mode
        ScalerDebugClrDdcciSwitchState();
#endif
        // Set slave address for debug tool
        MCU_FF23_IIC_SET_SLAVE = 0x6A;
        // DDCCI Mode Change to Debug Mode Need Clear IRQ Flag
        if(ScalerDebugGetDDCCIDebugMode() != enumMode)
        {
            // Clear IRQ FLag
            MCU_FF27_IIC_STATUS = 0x00;
            // Read IIC Data In(0xFF25) to Clear Data In Flag
            pData[0] = MCU_FF25_IIC_DATA_IN;
            // Write IIC Data Out(0xFF26) to Clear Data Out Flag
            MCU_FF26_IIC_DATA_OUT = 0x00;
            // Clear IIC Buffer Overflow or Underflow Flag
            MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);
            // Reset IIC Buffer
            MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
        }
        // Enable STOP_I, D_IN_I, SUB_I interrupts
        MCU_FF28_IIC_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;

#if(_DEBUG_DDC_CHANNEL_SEL == _DDC1)
        // DDC from DDC1 channel
        MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
        MCU_FF22_IIC_CH_SEL |= _BIT1;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC0)
        // DDC from DDC0 channel
        MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
        MCU_FF22_IIC_CH_SEL |= _BIT0;
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) || (_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC2))
        if(GET_A0_DDC_CHANNEL_SEL() == _VGA_DDC2)
        {
            // DDC from VGA_DDC2 channel
            MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
            MCU_FF22_IIC_CH_SEL |= _BIT3;
        }
        else
        {
            // DDC from VGA_DDC channel
            MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
        }
#endif
    }
    ScalerDebugSelectDDCCIDebugMode(enumMode);
}

#if(_DDCCI_CODE_REDUCTION == _OFF)
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DDCCI Auto Switch Channel Enable
// Input Value  : bEnable --> Status to Set
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciAutoSwitchInactiveChannel(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        switch(MCU_FF22_IIC_CH_SEL)
        {
            case _DDCCI_ADC_DDC:

                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 |= _BIT4;

                break;

            case _DDCCI_DDC0:

                MCU_FF1D_ADC_DDC_CONTROL_2 |= _BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 |= _BIT4;

                break;

            case _DDCCI_DDC1:

                MCU_FF1D_ADC_DDC_CONTROL_2 |= _BIT4;
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 |= _BIT4;

                break;

            case _DDCCI_ADC_DDC2:

                MCU_FF1D_ADC_DDC_CONTROL_2 |= _BIT4;
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT4;

                break;

            default:

                break;
        }
    }
    else
    {
        switch(MCU_FF22_IIC_CH_SEL)
        {
            case _DDCCI_ADC_DDC:

                MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 &= ~_BIT4;

                break;

            case _DDCCI_DDC0:

                MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 &= ~_BIT4;

                break;

            case _DDCCI_DDC1:

                MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 &= ~_BIT4;

                break;

            case _DDCCI_ADC_DDC2:

                MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT4;

                break;

            default:

                break;
        }
    }
}

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Set DDCCI Auto Switch Inactive Channel Disable
// Input Value  : bEnable --> Status to Set
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciAutoSwitchInactiveChannel_EXINT1(bit bEnable) using 2
{
    if(bEnable == _ENABLE)
    {
        switch(MCU_FF22_IIC_CH_SEL)
        {
            case _DDCCI_ADC_DDC:

                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 |= _BIT4;

                break;

            case _DDCCI_DDC0:

                MCU_FF1D_ADC_DDC_CONTROL_2 |= _BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 |= _BIT4;

                break;

            case _DDCCI_DDC1:

                MCU_FF1D_ADC_DDC_CONTROL_2 |= _BIT4;
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 |= _BIT4;

                break;

            case _DDCCI_ADC_DDC2:

                MCU_FF1D_ADC_DDC_CONTROL_2 |= _BIT4;
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT4;

                break;

            default:

                break;
        }
    }
    else
    {
        switch(MCU_FF22_IIC_CH_SEL)
        {
            case _DDCCI_ADC_DDC:

                MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 &= ~_BIT4;

                break;

            case _DDCCI_DDC0:

                MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 &= ~_BIT4;

                break;

            case _DDCCI_DDC1:

                MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FD34_ADC_DDC2_DDC_CONTROL_2 &= ~_BIT4;

                break;

            case _DDCCI_ADC_DDC2:

                MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT4;
                MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT4;

                break;

            default:

                break;
        }
    }
}
#endif
#endif
#endif

//--------------------------------------------------
// Description  : GPIO Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuGpioInitial(void)
{
    // Port_pin_reg_n signal is enabled (P1, P3 GPI->Bus Value)
    MCU_FFED_MCU_CONTROL |= _BIT7;

    // Source selection for P1, P3, P4, P5, P6, P7, P8, read back from bus value
    MCU_FE60_PORT_READ_CONTROL = 0xFF;

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
#else
    PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
#endif
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
#else
    PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
#endif
#endif

    PCB_A0_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
    PCB_D0_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
    PCB_D1_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

    PCB_PANEL_POWER(_PANEL_CONTROL_OFF);
    PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);
    PCB_LED_AC_ON_INITIAL();

    PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON();
    PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON();

    // Initi External Edid Gpio in AC ON Case
    PCB_MULTI_EDID_SWITCH_POWER_AC_ON();
}

//--------------------------------------------------
// Description  : DDC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcInitial(void)
{
    // Disable DDCRAM Start Addr Change to 0xE200
    MCU_FFE9_MCU_CLK_CONTROL_1 &= ~(_BIT6 | _BIT5);

    // Disable DDC Segment for VGA_DDC
    MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT2;

    // Disable DDC Segment for DDC0
    MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT2;

    // Disable DDC Segment for DDC1
    MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT2;

    // Slave address 0xA0 for VGA_DDC
    MCU_FF1B_ADC_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Slave address 0xA0 for DDC0
    MCU_FF1E_DDC0_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Slave address 0xA0 for DDC1
    MCU_FF2C_DDC1_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    MCU_FF1C_ADC_DDC_CONTROL_1 |= _BIT2;
    MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT2;
    MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT2;

    // Disable DDC Segment for VGA_DDC2
    MCU_FD34_ADC_DDC2_DDC_CONTROL_2 &= ~_BIT2;

    // Slave address 0xA0 for VGA_DDC2
    MCU_FD32_ADC_DDC2_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Force DDC to DDC2 Mode
    MCU_FD33_ADC_DDC2_DDC_CONTROL_1 |= _BIT2;

    // DDC Debounce Settings
    ScalerMcuDdcDebounceSel(_IOSC_CLK);

    // A0 DDC force Nack

    // ADC_DDC Force Nack
    MCU_FFE7_VGA_EDID_IRQ |= _BIT5;

    // ADC_DDC2 Force Nack
    MCU_FD37_ADC_DDC2_EDID_IRQ |= _BIT5;

    // D0 D1 DDC force Nack
    // DDC0 Force Nack when not embedded EDID
    MCU_FFE4_DDC0_EDID_IRQ |= _BIT5;

    // DDC1 Force Nack when not embedded EDID
    MCU_FFE5_DDC1_EDID_IRQ |= _BIT5;

/////////////////////////////////////////
// Release DDC SCL Pin force to Low /////
/////////////////////////////////////////

    // DDC1
    MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT0;

    // DDC0
    MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT0;

    // VGA DDC
    MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT0;

    // VGA_DDC2
    MCU_FD34_ADC_DDC2_DDC_CONTROL_2 &= ~_BIT0;
}

//--------------------------------------------------
// Description  : Enable DDC Ram
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcRamEnable(void)
{
    // VGA_DDC2 Debounce Enable, ADC DDC channel enable
    MCU_FD32_ADC_DDC2_DDC_ENABLE |= (_BIT1 | _BIT0);

    // VGA_DDC Debounce Enable, ADC DDC channel enable
    MCU_FF1B_ADC_DDC_ENABLE |= (_BIT1 | _BIT0);

    // DDC0 Debounce Enable, DDC0 channel enable
    MCU_FF1E_DDC0_DDC_ENABLE |= (_BIT1 | _BIT0);

    // DDC1 Debounce Enable, DDC1 channel enable
    MCU_FF2C_DDC1_DDC_ENABLE |= (_BIT1 | _BIT0);
}

//--------------------------------------------------
// Description  : DDC-CI Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciInitial(void)
{
    // Set slave address for debug tool
    MCU_FF23_IIC_SET_SLAVE = 0x6A;
    // Set DDCCI Mode for Debug Tool
    ScalerDebugSelectDDCCIDebugMode(_DEBUG_MODE);

    // Disable DDCCI 1
    MCU_FE87_IIC_1_SET_SLAVE = 0x3D;
    MCU_FE86_IIC_1_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);

#if(_DEBUG_DDC_CHANNEL_SEL == _DDC1)
    // DDC from DDC1 channel
    MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
    MCU_FF22_IIC_CH_SEL |= _BIT1;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC0)
    // DDC from DDC0 channel
    MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
    MCU_FF22_IIC_CH_SEL |= _BIT0;
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) || (_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC2))
    if(GET_A0_DDC_CHANNEL_SEL() == _VGA_DDC2)
    {
        // DDC from VGA_DDC2 channel
        MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
        MCU_FF22_IIC_CH_SEL |= _BIT3;
    }
    else
    {
        // DDC from VGA_DDC channel
        MCU_FF22_IIC_CH_SEL &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
    }
#endif

    // Assign DDC-CI interrupts to int1 (IRQ2)
    MCU_FFC4_IRQ_PRIORITY_3 &= ~(_BIT2 | _BIT1 | _BIT0);
    MCU_FFC4_IRQ_PRIORITY_3 |= _BIT0;

    // Enable DDC-CI buffer auto reset
    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT7;

    // Clear DDCCI status
    MCU_FF27_IIC_STATUS = 0x00;
    pData[0] = MCU_FF25_IIC_DATA_IN;
    MCU_FF26_IIC_DATA_OUT = 0x00;
    MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);

    // Reset IIC Buffer
    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
    // For HP case, return Null Msg if Command isn't finish
#if(HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT == _ON)
    MCU_FF2B_IIC_CHANNEL_CONTROL |= _BIT5;
#endif

    EX1 = 1;

    // Enable STOP_I, D_IN_I, SUB_I interrupts
    MCU_FF28_IIC_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;

    DebugMessageSystem("######    F/W START    ######", _OFF);
}


#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Release SCL
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuDdcciReleaseScl(void)
{
    switch(MCU_FF22_IIC_CH_SEL & (_BIT3 | _BIT2 | _BIT1 | _BIT0))
    {
        case _DDC1:
            MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT0;
            break;

        case _DDC0:
            MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT0;
            break;

        case _VGA_DDC:
            MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT0;
            break;

        case _VGA_DDC2:
            MCU_FD34_ADC_DDC2_DDC_CONTROL_2 &= ~_BIT0;
            break;

        default:

            break;
    }
}

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : hold SCL
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuDdcciHoldScl_EXINT1(void) using 2
{
    switch(MCU_FF22_IIC_CH_SEL & (_BIT3 | _BIT2 | _BIT1 | _BIT0))
    {
        case _DDC1:
            MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT0;
            break;

        case _DDC0:
            MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT0;
            break;

        case _VGA_DDC:
            MCU_FF1D_ADC_DDC_CONTROL_2 |= _BIT0;
            break;

        case _VGA_DDC2:
            MCU_FD34_ADC_DDC2_DDC_CONTROL_2 |= _BIT0;
            break;

        default:

            break;
    }
}

#endif // #if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#endif  // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))

//--------------------------------------------------
// Description  : ISP Channel Setting
// Input Value  : ISPChannel -> VGA_DDC: _BIT0; DDC0: _BIT1; DDC1: _BIT2;... DDC5: _BIT6;
//                _NO_DDC: _BIT7; VGA_DDC2: _BIT8
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuSetISPChannel(WORD usISPChannel)
{
    // VGA_DDC
    ScalerMcuDdcISPChannelCtrl(_VGA_DDC, (bit)(usISPChannel & _BIT0));
    // DDC0
    ScalerMcuDdcISPChannelCtrl(_DDC0, (bit)(usISPChannel & _BIT1));
    // DDC1
    ScalerMcuDdcISPChannelCtrl(_DDC1, (bit)(usISPChannel & _BIT2));
    // VGA_DDC2
    ScalerMcuDdcISPChannelCtrl(_VGA_DDC2, (bit)(usISPChannel & _BIT8));
}

//--------------------------------------------------
// Description  : ISP Channel Setting
// Input Value  : ucDdcChannel --> VGA_DDC...VGA_DDC2
//                bEnable --> _ENABLE: enable DDC ISP function, no protect
//                            _DISABLE: disable DDC ISP function, protect
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuDdcISPChannelCtrl(BYTE ucDdcChannel, bit bEnable)
{
    switch(ucDdcChannel)
    {
        case _VGA_DDC:
            // VGA_DDC ISP
            MCU_FF1D_ADC_DDC_CONTROL_2 = (bEnable) ? (MCU_FF1D_ADC_DDC_CONTROL_2 | _BIT3) : (MCU_FF1D_ADC_DDC_CONTROL_2 & (~_BIT3));
            break;

        case _DDC0:
            // DDC0 ISP
            MCU_FF20_DDC0_DDC_CONTROL_2 = (bEnable) ? (MCU_FF20_DDC0_DDC_CONTROL_2 | _BIT3) : (MCU_FF20_DDC0_DDC_CONTROL_2 & (~_BIT3));
            break;

        case _DDC1:
            // DDC1 ISP
            MCU_FF2E_DDC1_DDC_CONTROL_2 = (bEnable) ? (MCU_FF2E_DDC1_DDC_CONTROL_2 | _BIT3) : (MCU_FF2E_DDC1_DDC_CONTROL_2 & (~_BIT3));
            break;

        case _VGA_DDC2:
            // VGA_DDC2 ISP
            MCU_FD34_ADC_DDC2_DDC_CONTROL_2 = (bEnable) ? (MCU_FD34_ADC_DDC2_DDC_CONTROL_2 | _BIT3) : (MCU_FD34_ADC_DDC2_DDC_CONTROL_2 & (~_BIT3));
            break;

        case _NO_DDC:
        default:
            break;
    }
}
