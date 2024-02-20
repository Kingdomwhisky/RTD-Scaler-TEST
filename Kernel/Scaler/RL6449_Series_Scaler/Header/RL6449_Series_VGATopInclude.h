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
// ID Code      : RL6449_Series_VGATopInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_VGA_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions of HS Phase Delay Calibration
//--------------------------------------------------
#define _HS_DELAY_DVTOTAL                           (100UL) // line
#define _HS_DELAY_TARGET_DHFREQ                     (3600UL) // 0.1KHz
#define _HS_DELAY_DHTOTAL                           ((WORD)(GET_D_CLK_FREQ() * 10 / _HS_DELAY_TARGET_DHFREQ)) // pixel
#define _HS_DELAY_REAL_DHFREQ                       ((WORD)(GET_D_CLK_FREQ() * 10 / _HS_DELAY_DHTOTAL)) // 0.1kHz
#define _HS_DELAY_ICLK_RATE                         (200UL) // MHz
#define _HS_DELAY_IHTOTAL                           ((DWORD)_HS_DELAY_DHTOTAL * 1000 * _HS_DELAY_ICLK_RATE / GET_D_CLK_FREQ())

#define SET_HS_DELAY_LATCH_EDGE()                   {\
                                                        ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~_BIT3, 0x00);\
                                                    }

#define SAVE_HS_DELAY_SETTING(pucBackup)            {\
                                                        ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, 3, (pucBackup), _AUTOINC);\
                                                        (pucBackup)[3] = ScalerGetByte(P1_C6_DCLK_SPREAD_SPECTRUM);\
                                                        ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, 4, &((pucBackup)[4]), _AUTOINC);\
                                                    }

#define LOAD_HS_DELAY_SETTING(pucBackup)            {\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, (pucBackup)[0]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_01_DISPLAY_HOR_TOTAL_L, (pucBackup)[1]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END, (pucBackup)[2]);\
                                                        ScalerSetByte(P1_C6_DCLK_SPREAD_SPECTRUM, (pucBackup)[3]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, (pucBackup)[4]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_31_FIXED_DVTOTAL_LSB, (pucBackup)[5]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB, (pucBackup)[6]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_33_FIXED_LAST_LINE_LSB, (pucBackup)[7]);\
                                                    }

//--------------------------------------------------
// HS delay Time
//--------------------------------------------------
#define _PHASE_DELAY_TIME_VALUE_SHORT_PATH          (282) // 249 = 64 * 4.40 (Unit: ns)
#define _PHASE_DELAY_TIME_VALUE_LONG_PATH           (523) // 523 = 64 * 8.17 (Unit: ns)
#define _PHASE_DELAY_HALF_PERIOD_SHIFT              ((ScalerGetBit(P0_BC_ADC_CK_OUT_CTRL, _BIT5) == _BIT5) ? 32 : 0)

//--------------------------------------------------
// VGATOP auto-function V start offset
//--------------------------------------------------
#define _VGATOP_VSTART_OFFSET                       (0)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#endif
