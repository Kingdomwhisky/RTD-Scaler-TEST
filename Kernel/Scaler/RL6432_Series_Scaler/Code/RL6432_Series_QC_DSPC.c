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
// ID Code      : RL6432_Series_QC_DSPC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6432_SERIES_QC_DSPC__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

#if(_PCB_TYPE == _RL6432_QA_B_1A2MHL2DP_DPTX_LVDS_eDP)

#define _SIMPLE                                 0
#define _COMPLEX                                1

#define _DSPC_FPGA_CONTENT                      _COMPLEX
#define _DSPC_FPGA_TEST                         _DISABLE   // Jeyu_test
#define _DPSC_CRC_NUM                           48

// Fred_add_start
#define pin36                                   (P1_7)
BYTE GPIO_RESULT = 0x00;
BYTE GPIO_RESULT_VBY1_A = 0x00;
BYTE GPIO_RESULT_VBY1_B = 0x00;
// Fred_add_end

//--------------------------------------------------
// Macro of FPGA IIC
//--------------------------------------------------
#define bSWIIC_FPGA_SCL                         (MCU_FE0C_PORT54_PIN_REG) // Pin164, P5.4
#define bSWIIC_FPGA_SDA                         (MCU_FE0F_PORT57_PIN_REG) // Pin167, P5.7

#define FPGA_SW_IIC_SDA_SET()                   {\
                                                    bSWIIC_FPGA_SDA = _TRUE;         \
                                                }

#define FPGA_SW_IIC_SDA_CLR()                   {\
                                                    bSWIIC_FPGA_SDA = _FALSE;        \
                                                }

#define FPGA_SW_IIC_SDA_CHK(x)                  {\
                                                    x = bSWIIC_FPGA_SDA;             \
                                                }

#define FPGA_SW_IIC_SCL_SET()                   {\
                                                    bSWIIC_FPGA_SCL = _TRUE;         \
                                                }

#define FPGA_SW_IIC_SCL_CLR()                   {\
                                                    bSWIIC_FPGA_SCL = _FALSE;        \
                                                }

#define FPGA_SW_IIC_SCL_CHK(x)                  {\
                                                    x = bSWIIC_FPGA_SCL;             \
                                                }

//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// LVDS Common TABLE
//--------------------------------------------------
BYTE code tQCLVDS_FT[] =
{
//////////////////////////////////////////
// Enable ADC Bandgap (0x00C6[3])
//////////////////////////////////////////

4, _NON_AUTOINC, 0x9F, 0x00,   // Page 00
4, _NON_AUTOINC, 0xC6, 0x08,

//////////////////////////////////////////
// Enable GDI Bandgap (0x01D14[7])
//////////////////////////////////////////

4,	_NON_AUTOINC, 0x9F, 0x1D,  // Page 1D
4, 	_NON_AUTOINC, 0x14, 0x9B,  // Enable GDI Bandgap & Set GDI bandgap ouput voltage to 1.245V

//*************************************************************************
// End Define Setting
//*************************************************************************

// Power on LVDS Analog
4, _NON_AUTOINC, 0x9F, 0x15,  // Page 15
4, _NON_AUTOINC, 0x00, 0xE0,  // [7] LVDS IBGen [6] LVDS Port A Power [5] LVDS Port B Power

4, _NON_AUTOINC, 0x9F, 0x55,  // Page 55
4, _NON_AUTOINC, 0x00, 0xE0,  // [7] LVDS IBGen [6] LVDS Port C Power [5] LVDS Port D Power
4, _NON_AUTOINC, 0x73, 0xB0,  // Set CMU: LVDS Mode, CMU Referenced Clk: From Dpll Clk
4, _NON_AUTOINC, 0x72, 0x00,  // Divider for Postdivider of CMU and Pre-divder of CMU
4, _NON_AUTOINC, 0x0E, 0xFC,  // LDO voltage Setting
4, _NON_AUTOINC, 0x5D, 0xF8,  // CLKRD duty set to 4'b1111 @0638 as AMlee suggests. Good Phase setting H/L = 4/6

4, _NON_AUTOINC, 0x9F, 0x38,  // Page 38
4, _NON_AUTOINC, 0xD6, 0x20,  // Enable N.F Set By FW
4, _NON_AUTOINC, 0xD7, 0x50,  // DPN = N + 2, N = 5

4, _NON_AUTOINC, 0x9F, 0x10,  // Select to Page 10
4, _NON_AUTOINC, 0x45, 0x04,
4, _NON_AUTOINC, 0x46, 0x04,
4, _NON_AUTOINC, 0x47, 0x04,
4, _NON_AUTOINC, 0x48, 0x04,
4, _NON_AUTOINC, 0x49, 0x04,
4, _NON_AUTOINC, 0x4A, 0x04,
4, _NON_AUTOINC, 0x4B, 0x04,
4, _NON_AUTOINC, 0x4C, 0x04,
4, _NON_AUTOINC, 0x4D, 0x04,
4, _NON_AUTOINC, 0x4E, 0x04,
4, _NON_AUTOINC, 0x4F, 0x04,
4, _NON_AUTOINC, 0x50, 0x04,
4, _NON_AUTOINC, 0x51, 0x04,
4, _NON_AUTOINC, 0x52, 0x04,
4, _NON_AUTOINC, 0x53, 0x04,
4, _NON_AUTOINC, 0x54, 0x04,
4, _NON_AUTOINC, 0x55, 0x04,
4, _NON_AUTOINC, 0x56, 0x04,
4, _NON_AUTOINC, 0x57, 0x04,
4, _NON_AUTOINC, 0x58, 0x04,
4, _NON_AUTOINC, 0x59, 0x04,
4, _NON_AUTOINC, 0x5A, 0x04,

//*************************************************************************
//  Pll Parameters Setting
//  Vref = Crystal = 14.318M
//  Target Clock = 170M
//  Target Clock = 168.143M = 14.318M * 47 / 2 / 1 / 2
//*************************************************************************

//---------PLL VCO Setting---------
4,	_AUTOINC,	0x9F,	0x01,     // page 1 (PLL)

// DPLL Reset
4,	_AUTOINC,	0xC2,	0x19,     // DPLL Power down
4,	_AUTOINC,	0xBF,	0x00,     // Reset M code
4,	_AUTOINC,	0xC0,	0x00,     // Reset N code
4,	_AUTOINC,	0xC3,	0xA1,     // VCOMD=2'b10, DPLL Bypass Calibration
4,	_AUTOINC,	0xCA,	0x01,     // [2] test enable "[0]: 1 => Enable DDS Spread Spectrum output function"

//---------DPLL Setting---------
4,	_AUTOINC,	0xC3,	0x81,     // Set VCOMD=2'b10, Auto Calibration
4,	_AUTOINC,	0xBF,	0x2D,     // M = 0x2D, DPM = 47, VCO: 340MHz
4,	_AUTOINC,	0xC0,	0x00,     // N = 00 => div 2, O_code = 0 => div 1
4,	_AUTOINC,	0xC1,	0x7B,     // [7:5] loop filter resiter  [4:3] capacitor  [3:0] charger pump current
4,	_AUTOINC,	0xDA,	0x00,     // [1:0] pixel clk divider: DIV_B = 1
4,	_AUTOINC,	0xC2,	0x08,     // DPLL Power ON

//---------Calibration Start---------
//DELAY(14300) // loop1 = 1000us
4,	_AUTOINC,	0xC3,	0x85, 	// CMP enable	// 1000us -> 200us

//DELAY(1430)  // loop2 = 100us
4,	_AUTOINC,	0xC3,	0x8D, 	// latchca libration	// 1100us -> 201us

//DELAY(1430)  // loop3 = 100us
4,	_AUTOINC,	0xC3,	0x9D, 	// calibration valid	// 1200us -> 202us
//---------Calibration End---------

//*************************************************************************
//  LVDS Digital Parameters Setting
//  LVDS Output Port: 2 Port LVDS (i.e: CD Port copy AB Port)
//  LVDS Clock = 84.118M = 168.237M / 2
//  LVDS Output Resolution: 10bit LVDS
//  LVDS Bitmap Reverse: Enable
//*************************************************************************

//---------Display Conversion-------------
4, _NON_AUTOINC, 0x9F, 0x39,  // page 39 (Display Conversion)
4, _NON_AUTOINC, 0x00, 0x01,  // LVDS mode
4, _NON_AUTOINC, 0x01, 0x4C,  // 2port LVDS
4, _NON_AUTOINC, 0x03, 0x01,  // CD Port copy AB Port
4, _NON_AUTOINC, 0x06, 0x08,
4, _NON_AUTOINC, 0x30, 0x08,

//*************************************************************************
//  Display Timing Setting
//  Timing: 1024 x 1024
//  DCLK Polarity Inverted
//  LVDS Output DC Signal
//*************************************************************************

//---------DisplayTimingGen-------------
4, _NON_AUTOINC, 0x9F, 0x00,        // page 00
4, _AUTOINC,     0x28, 0x08,        // Frame Sync

4, _AUTOINC,     0x2A, 0x00,
5, _NON_AUTOINC, 0x2B, 0x04, 0x64,  // DHTotal = 1128
4, _AUTOINC,     0x2A, 0x02,
4, _NON_AUTOINC, 0x2B, 0x08,        // Hs End
4, _AUTOINC,     0x2A, 0x03,
5, _NON_AUTOINC, 0x2B, 0x00, 0x28,  // Hori bkg start
4, _AUTOINC,     0x2A, 0x05,
5, _NON_AUTOINC, 0x2B, 0x00, 0x28,  // Hori act start
4, _AUTOINC,     0x2A, 0x07,
5, _NON_AUTOINC, 0x2B, 0x04, 0x28,  // Hori act end
4, _AUTOINC,     0x2A, 0x09,
5, _NON_AUTOINC, 0x2B, 0x04, 0x28,  // Hori bkg end
4, _AUTOINC,     0x2A, 0x0B,
5, _NON_AUTOINC, 0x2B, 0x04, 0x0A,  // DVTotal = 1034
4, _AUTOINC,     0x2A, 0x0D,
4, _NON_AUTOINC, 0x2B, 0x03,        // Vs End
4, _AUTOINC,     0x2A, 0x0E,
5, _NON_AUTOINC, 0x2B, 0x00, 0x06,  // Vert bkg start
4, _AUTOINC,     0x2A, 0x10,
5, _NON_AUTOINC, 0x2B, 0x00, 0x06,  // Vert act start
4, _AUTOINC,     0x2A, 0x12,
5, _NON_AUTOINC, 0x2B, 0x04, 0x06,  // Vert act start
4, _AUTOINC,     0x2A, 0x14,
5, _NON_AUTOINC, 0x2B, 0x04, 0x06,  // Vert bkg end
4, _AUTOINC,     0x2A, 0x16,
5, _NON_AUTOINC, 0x2B, 0x00, 0x00,
4, _AUTOINC,     0x2A, 0x18,
5, _NON_AUTOINC, 0x2B, 0x00, 0x00,
4, _AUTOINC,     0x2A, 0x1A,
5, _NON_AUTOINC, 0x2B, 0x00, 0x00,
4, _AUTOINC,     0x2A, 0x1C,
5, _NON_AUTOINC, 0x2B, 0x00, 0x00,

4, _AUTOINC,     0x2A, 0x20,
4, _AUTOINC,     0x2B, 0x00,        // DCLK Polarity Non-inverted

//---------Fixed Last Line for Free Run Mode---------
4, _NON_AUTOINC, 0x2A, 0x30,
7, _NON_AUTOINC, 0x2B, 0x04, 0x0A, 0x04, 0x64,

//---------Free Run Mode---------
4,	_AUTOINC,	   0x28,	0x83,       // Free Run Mode, Force Enable

//*************************************************************************
//  D Domain Pattern Generator
//  Pixel/Line Increase Enable
//*************************************************************************
//---------DPG-------------
4, _NON_AUTOINC, 0x9F, 0x07,        // Page7 (Dpg)
4, _NON_AUTOINC, 0xF0, 0x85,
4, _NON_AUTOINC, 0xF1, 0x05,
4, _NON_AUTOINC, 0xF2, 0x05,
4, _NON_AUTOINC, 0xF4, 0x01,
4, _NON_AUTOINC, 0xF5, 0x02,
4, _NON_AUTOINC, 0xF6, 0x01,
4, _NON_AUTOINC, 0xF7, 0x01,
4, _NON_AUTOINC, 0xFC, 0x00,
4, _NON_AUTOINC, 0x9F, 0x87,
4, _NON_AUTOINC, 0xF0, 0x41,
4, _NON_AUTOINC, 0xF1, 0x01,
4, _NON_AUTOINC, 0xF2, 0x01,
4, _NON_AUTOINC, 0xF6, 0x01,
4, _NON_AUTOINC, 0xF7, 0x01,

//*************************************************************************
//  LVDS Analog Parameters Setting
//  LVDS Output Port: 4 Port LVDS Power (i.e: CD Port copy AB Port)
//  LVDS BW Setting
//*************************************************************************

//---------Power on LVDS Power---------
4, _NON_AUTOINC, 0x9F, 0x15,  // Page 15 (AB Port)
4, _NON_AUTOINC, 0x00, 0xE0,  // [7] LVDS IBGen [6] LVDS Port A Power [5] LVDS Port B Power
4, _NON_AUTOINC, 0x01, 0x6A,
4, _NON_AUTOINC, 0x02, 0x02,
4, _NON_AUTOINC, 0x03, 0x65,  // [4] CK_PIXEL: Falling Edge
4, _NON_AUTOINC, 0x0D, 0xAB,
4, _NON_AUTOINC, 0x0E, 0xFD,
4, _NON_AUTOINC, 0x21, 0x80,
4, _NON_AUTOINC, 0x26, 0x00,
4, _NON_AUTOINC, 0x30, 0x08,  // TXAC current 2x
4, _NON_AUTOINC, 0x31, 0x80,
4, _NON_AUTOINC, 0x36, 0x00,

4, _NON_AUTOINC, 0x9F, 0x55,  // Page 55 (CD Port)
4, _NON_AUTOINC, 0x00, 0xE0,  // [7] LVDS IBGen [6] LVDS Port C Power [5] LVDS Port D Power
4, _NON_AUTOINC, 0x01, 0x6A,
4, _NON_AUTOINC, 0x02, 0x02,
4, _NON_AUTOINC, 0x03, 0x65,  // [4] CK_PIXEL: Falling Edge
4, _NON_AUTOINC, 0x0D, 0xAB,
4, _NON_AUTOINC, 0x0E, 0xFD,
4, _NON_AUTOINC, 0x0F, 0x04,  // VCO = 1.5~3 GHz, Phy range = 375~750 MHz, Freq_band = div4
4, _NON_AUTOINC, 0x21, 0x80,
4, _NON_AUTOINC, 0x26, 0x00,
4, _NON_AUTOINC, 0x30, 0x08,  // TXCC current 2x
4, _NON_AUTOINC, 0x31, 0x80,
4, _NON_AUTOINC, 0x36, 0x00,

//---------Power on LVDS Power and PLL---------
4, _NON_AUTOINC, 0x9F, 0x15,  // Page 15 (AB Port)
4, _NON_AUTOINC, 0x00, 0xF8,  // [7] LVDS IBGen [6] LVDS Port A Power [5] LVDS Port B Power [4] LVDS PLL LDO [3] LVDS PLL Power

4, _NON_AUTOINC, 0x9F, 0x55,  // Page 55 (CD Port)
4, _NON_AUTOINC, 0x00, 0xE8,  // [7] LVDS IBGen [6] LVDS Port C Power [5] LVDS Port D Power [3] LVDS PLL Power

// Start Pair CRC
4,	_AUTOINC,	   0x9F,	0x39,
4,	_AUTOINC,	   0x30,	0x08,  // Start LVDS CRC
};

BYTE code tQCLVDS_QA_ENVIRONMENT[] =
{
//---------PLL VCO Setting---------
4,	_AUTOINC,	0x9F,	0x01,     // page 1 (PLL)
4,	_AUTOINC,	0xC4,	0x10,     // Offset = 0
4,	_AUTOINC,	0xC5,	0x00,     // Offset = 0
4,	_AUTOINC,	0xC6,	0x04,

//*************************************************************************
//  LVDS Digital Parameters For QA Environment Setting
//  LVDS PN Swap
//  LVDS Port Swap
//*************************************************************************

//---------Display Conversion-------------
4, _NON_AUTOINC, 0x9F, 0x39,  // page 39 (Display Conversion)
4, _NON_AUTOINC, 0x02, 0x01,
4, _NON_AUTOINC, 0x03, 0x01,
//4, _NON_AUTOINC, 0x06, 0x18,
4, _NON_AUTOINC, 0x30, 0x08,

//*************************************************************************
//  LVDS Analog Parameters Setting
//  LVDS Trace Skew Correction
//*************************************************************************

//---------LVDS Phase Interpolation---------
4, _NON_AUTOINC, 0x9F, 0x15,  // Page 15 (AB Port)
4, _NON_AUTOINC, 0x07, 0x31,  // CK7X_PI1: 1-PI
4, _NON_AUTOINC, 0x09, 0x68,  // CK7X_PI2: 7-PI
4, _NON_AUTOINC, 0x0B, 0xC0,  // CK7X_PI3: 8-PI
4, _NON_AUTOINC, 0x35, 0x05,  // TXA3/TXA4: CK7X_PI1
4, _NON_AUTOINC, 0x24, 0x0A,  // TXB0/TXB1: CK7X_PI2
4, _NON_AUTOINC, 0x25, 0x8F,  // TXB2     : CK7X_PI2
                              // TXB3/TXB4: CK7X_PI3

4, _NON_AUTOINC, 0x9F, 0x55,  // Page 55 (CD Port)
4, _NON_AUTOINC, 0x07, 0x31,  // CK7X_PI1: 1-PI
4, _NON_AUTOINC, 0x09, 0x33,  // CK7X_PI2: 2-PI
4, _NON_AUTOINC, 0x0B, 0xC1,  // CK7X_PI3: 9-PI
4, _NON_AUTOINC, 0x34, 0x05,  // TXC0/TXC1: CK7X_PI1
4, _NON_AUTOINC, 0x35, 0x4A,  // TXC2     : CK7X_PI1
                              // TXC3/TXC4: CK7X_PI2

4, _NON_AUTOINC, 0x24, 0x0F,  // TXD0/TXD1: CK7X_PI3
4, _NON_AUTOINC, 0x25, 0xCF,  // TXD2/TXD3/TXD4: CK7X_PI3
};

BYTE code tQCDPMST_HBR2_21_FT[] =
{

    //////////////////////////////////////////
    // Enable ADC Bandgap (0x00C6[3])
    //////////////////////////////////////////
    4,    _NON_AUTOINC,    0x9F,    0x00,        // Page 00
    4,    _NON_AUTOINC,    0xC6,    0x08,

    //////////////////////////////////////////
    // Enable GDI Bandgap (0x0BB4[7])
    //////////////////////////////////////////
    4,    _NON_AUTOINC,    0x9F,    0x0B,        // Page 0B
    4, 	  _NON_AUTOINC,	   0xB4,    0xA0,        // Enable GDI Bandgap & Set GDI bandgap ouput voltage to 1.21V

// DPTX Power ON and CMU Enable
4,	_AUTOINC,	0x9F,   0xBC,
4,	_AUTOINC,	0xA0,   0x90,
4,	_AUTOINC,	0xA2,   0x00,

// Divider for Postdivider of CMU and Pre-divder of CMU
4,	_AUTOINC,	0xD2,   0x00,

// LDO Voltage Setting
4,	_AUTOINC,	0xD3,   0x77,

// DP Mode
4,	_AUTOINC,	0xA9,   0x80,

// Enable Fifo
4,	_AUTOINC,	0xA7,   0x80,

//CLKRD duty Setting
4,	_AUTOINC,	0xBD,   0xF0,

///////////////////////////////////////////////////
// HBR2

// VCO 750MHz~6GHz
4,	_AUTOINC,	0xBD,   0xF0,

// KVCO,Icp,Rs
4,	_AUTOINC,	0xD0,   0x73,
4,	_AUTOINC,	0xD1,   0x7E,

// N.F Code
4,	_AUTOINC,	0xDF,   0x2E,
4,	_AUTOINC,	0xDE,   0x89,
4,	_AUTOINC,	0xDD,   0x8B,
4,	_AUTOINC,	0xDD,   0x8B,

// Toggle CMU Power toggle Bit4
4,	_AUTOINC,	0xA0,   0x80,
4,	_AUTOINC,	0xA0,   0x90,

// Swing,Pre-emphasis
4,	_AUTOINC,	0xB0,   0x00,
4,	_AUTOINC,	0xB1,   0xE0,
4,	_AUTOINC,	0xB2,   0xE0,
4,	_AUTOINC,	0xB3,   0xE0,
4,	_AUTOINC,	0xB4,   0xE0,
4,	_AUTOINC,	0xB6,   0xBB,
4,	_AUTOINC,	0xB7,   0xBB,
4,	_AUTOINC,	0xB8,   0xFF,
4,	_AUTOINC,	0xB9,   0xFF,
4,	_AUTOINC,	0xBA,   0xFF,
4,	_AUTOINC,	0xBB,   0xFF,

// Idle Pattern
4,	_AUTOINC,	0x9F,   0xBB,
4,	_AUTOINC,	0x00,   0xFC,
4,	_AUTOINC,	0x01,   0x21,
4,	_AUTOINC,	0x01,   0x21,

// Inter-pair skew enable
4,	_AUTOINC,	0x0D,   0x04,

// Output data
4,	_AUTOINC,	0x9F,   0xBC,
4,	_AUTOINC,	0xA0,   0x9F,
4,	_AUTOINC,	0xA1,   0x00,
};

BYTE code tQCDPMST_HBR2_FT[] =
{
    //////////////////////////////////////////
    // Enable ADC Bandgap (0x00C6[3])
    //////////////////////////////////////////
    4,    _NON_AUTOINC,    0x9F,    0x00,        // Page 00
    4,    _NON_AUTOINC,    0xC6,    0x08,

    //////////////////////////////////////////
    // Enable GDI Bandgap (0x0BB4[7])
    //////////////////////////////////////////
    4,    _NON_AUTOINC,    0x9F,    0x0B,        // Page 0B
    4, 	  _NON_AUTOINC,	   0xB4,    0xA0,        // Enable GDI Bandgap & Set GDI bandgap ouput voltage to 1.21V

// DPTX Power ON and CMU Enable
4,	_AUTOINC,	0x9F,   0xBC,
4,	_AUTOINC,	0xA0,   0x90,
4,	_AUTOINC,	0xA2,   0x00,

// Divider for Postdivider of CMU and Pre-divder of CMU
4,	_AUTOINC,	0xD2,   0x00,

// LDO Voltage Setting
4,	_AUTOINC,	0xD3,   0x77,

// DP Mode
4,	_AUTOINC,	0xA9,   0x80,

// Enable Fifo
4,	_AUTOINC,	0xA7,   0x80,

//CLKRD duty Setting
4,	_AUTOINC,	0xBD,   0xF0,

///////////////////////////////////////////////////
// HBR2

// VCO 750MHz~6GHz
4,	_AUTOINC,	0xBD,   0xF0,

// KVCO,Icp,Rs
4,	_AUTOINC,	0xD0,   0x73,
4,	_AUTOINC,	0xD1,   0x7E,

// N.F Code
4,	_AUTOINC,	0xDF,   0x2E,
4,	_AUTOINC,	0xDE,   0x89,
4,	_AUTOINC,	0xDD,   0x8B,
4,	_AUTOINC,	0xDD,   0x8B,

// Toggle CMU Power toggle Bit4
4,	_AUTOINC,	0xA0,   0x80,
4,	_AUTOINC,	0xA0,   0x90,

// Swing,Pre-emphasis
4,	_AUTOINC,	0xB0,   0x00,
4,	_AUTOINC,	0xB1,   0x00,
4,	_AUTOINC,	0xB2,   0x00,
4,	_AUTOINC,	0xB3,   0x00,
4,	_AUTOINC,	0xB4,   0x00,
4,	_AUTOINC,	0xB6,   0x77,
4,	_AUTOINC,	0xB7,   0x77,
4,	_AUTOINC,	0xB8,   0x55,
4,	_AUTOINC,	0xB9,   0x55,
4,	_AUTOINC,	0xBA,   0x44,
4,	_AUTOINC,	0xBB,   0x44,

// Idle Pattern
4,	_AUTOINC,	0x9F,   0xBB,
4,	_AUTOINC,	0x00,   0xFC,
4,	_AUTOINC,	0x01,   0x21,
4,	_AUTOINC,	0x01,   0x21,

// Inter-pair skew enable
4,	_AUTOINC,	0x0D,   0x04,

// Output data
4,	_AUTOINC,	0x9F,   0xBC,
4,	_AUTOINC,	0xA0,   0x9F,
4,	_AUTOINC,	0xA1,   0x00,
};

BYTE code tQCDPMST_HBR_21_FT[] =
{
//////////////////////////////////////////
// Enable ADC Bandgap (0x00C6[3])
//////////////////////////////////////////
4,    _NON_AUTOINC,    0x9F,    0x00,        // Page 00
4,    _NON_AUTOINC,    0xC6,    0x08,

//////////////////////////////////////////
// Enable GDI Bandgap (0x0BB4[7])
//////////////////////////////////////////
4,    _NON_AUTOINC,    0x9F,    0x0B,        // Page 0B
4, 	  _NON_AUTOINC,	   0xB4,    0xA0,        // Enable GDI Bandgap & Set GDI bandgap ouput voltage to 1.21V

// DPTX Power ON and CMU Enable
4,	_AUTOINC,	0x9F,   0xBC,
4,	_AUTOINC,	0xA0,   0x90,
4,	_AUTOINC,	0xA2,   0x00,

// Divider for Postdivider of CMU and Pre-divder of CMU
4,	_AUTOINC,	0xD2,   0x00,

// LDO Voltage Setting
4,	_AUTOINC,	0xD3,   0x77,

// DP Mode
4,	_AUTOINC,	0xA9,   0x80,

// Enable Fifo
4,	_AUTOINC,	0xA7,   0x80,

//CLKRD duty Setting
4,	_AUTOINC,	0xBD,   0xF0,

///////////////////////////////////////////////////
// HBR

// VCO 1.5GHz~3GHz
4,	_AUTOINC,	0xBD,   0xF1,

// KVCO,Icp,Rs
4,	_AUTOINC,	0xD0,   0x73,
4,	_AUTOINC,	0xD1,   0x7E,

// N.F Code
4,	_AUTOINC,	0xDF,   0x2E,
4,	_AUTOINC,	0xDE,   0x89,
4,	_AUTOINC,	0xDD,   0x8B,
4,	_AUTOINC,	0xDD,   0x8B,

// Toggle CMU Power toggle Bit4
4,	_AUTOINC,	0xA0,   0x80,
4,	_AUTOINC,	0xA0,   0x90,

// Swing,Pre-emphasis
4,	_AUTOINC,	0xB0,   0x00,
4,	_AUTOINC,	0xB1,   0x1C,
4,	_AUTOINC,	0xB2,   0x1C,
4,	_AUTOINC,	0xB3,   0x1C,
4,	_AUTOINC,	0xB4,   0x1C,
4,	_AUTOINC,	0xB6,   0xFF,
4,	_AUTOINC,	0xB7,   0xFF,
4,	_AUTOINC,	0xB8,   0xFF,
4,	_AUTOINC,	0xB9,   0xFF,
4,	_AUTOINC,	0xBA,   0xAA,
4,	_AUTOINC,	0xBB,   0xAA,

///////////////////////////////////////////////////

// Idle Pattern
4,	_AUTOINC,	0x9F,   0xBB,
4,	_AUTOINC,	0x00,   0xFC,
4,	_AUTOINC,	0x01,   0x21,
4,	_AUTOINC,	0x01,   0x21,

// Inter-pair skew enable
4,	_AUTOINC,	0x0D,   0x04,

// Output data
4,	_AUTOINC,	0x9F,   0xBC,
4,	_AUTOINC,	0xA0,   0x9F,
4,	_AUTOINC,	0xA1,   0x00,
};

BYTE code tQCDPMST_HBR_FT[] =
{
//////////////////////////////////////////
// Enable ADC Bandgap (0x00C6[3])
//////////////////////////////////////////
4,    _NON_AUTOINC,    0x9F,    0x00,        // Page 00
4,    _NON_AUTOINC,    0xC6,    0x08,

//////////////////////////////////////////
// Enable GDI Bandgap (0x0BB4[7])
//////////////////////////////////////////
4,    _NON_AUTOINC,    0x9F,    0x0B,        // Page 0B
4, 	  _NON_AUTOINC,	   0xB4,    0xA0,        // Enable GDI Bandgap & Set GDI bandgap ouput voltage to 1.21V

// DPTX Power ON and CMU Enable
4,	_AUTOINC,	0x9F,   0xBC,
4,	_AUTOINC,	0xA0,   0x90,
4,	_AUTOINC,	0xA2,   0x00,

// Divider for Postdivider of CMU and Pre-divder of CMU
4,	_AUTOINC,	0xD2,   0x00,

// LDO Voltage Setting
4,	_AUTOINC,	0xD3,   0x77,

// DP Mode
4,	_AUTOINC,	0xA9,   0x80,

// Enable Fifo
4,	_AUTOINC,	0xA7,   0x80,

//CLKRD duty Setting
4,	_AUTOINC,	0xBD,   0xF0,

///////////////////////////////////////////////////
// HBR

// VCO 1.5GHz~3GHz
4,	_AUTOINC,	0xBD,   0xF1,

// KVCO,Icp,Rs
4,	_AUTOINC,	0xD0,   0x73,
4,	_AUTOINC,	0xD1,   0x7E,

// N.F Code
4,	_AUTOINC,	0xDF,   0x2E,
4,	_AUTOINC,	0xDE,   0x89,
4,	_AUTOINC,	0xDD,   0x8B,
4,	_AUTOINC,	0xDD,   0x8B,

// Toggle CMU Power toggle Bit4
4,	_AUTOINC,	0xA0,   0x80,
4,	_AUTOINC,	0xA0,   0x90,

// Swing,Pre-emphasis
4,	_AUTOINC,	0xB0,   0x00,
4,	_AUTOINC,	0xB1,   0x04,
4,	_AUTOINC,	0xB2,   0x04,
4,	_AUTOINC,	0xB3,   0x04,
4,	_AUTOINC,	0xB4,   0x04,
4,	_AUTOINC,	0xB6,   0xCC,
4,	_AUTOINC,	0xB7,   0xCC,
4,	_AUTOINC,	0xB8,   0xAA,
4,	_AUTOINC,	0xB9,   0xAA,
4,	_AUTOINC,	0xBA,   0x22,
4,	_AUTOINC,	0xBB,   0x22,

///////////////////////////////////////////////////
// Idle Pattern
4,	_AUTOINC,	0x9F,   0xBB,
4,	_AUTOINC,	0x00,   0xFC,
4,	_AUTOINC,	0x01,   0x21,
4,	_AUTOINC,	0x01,   0x21,

// Inter-pair skew enable
4,	_AUTOINC,	0x0D,   0x04,

// Output data
4,	_AUTOINC,	0x9F,   0xBC,
4,	_AUTOINC,	0xA0,   0x9F,
4,	_AUTOINC,	0xA1,   0x00,
};

BYTE code tQCDPMST_RBR_21_FT[] =
{
//////////////////////////////////////////
// Enable ADC Bandgap (0x00C6[3])
//////////////////////////////////////////
4,    _NON_AUTOINC,    0x9F,    0x00,        // Page 00
4,    _NON_AUTOINC,    0xC6,    0x08,

//////////////////////////////////////////
// Enable GDI Bandgap (0x0BB4[7])
//////////////////////////////////////////
4,    _NON_AUTOINC,    0x9F,    0x0B,        // Page 0B
4,    _NON_AUTOINC,    0xB4,    0xA0,        // Enable GDI Bandgap & Set GDI bandgap ouput voltage to 1.21V

// DPTX Power ON and CMU Enable
4,    _AUTOINC,    0x9F,   0xBC,
4,    _AUTOINC,    0xA0,   0x90,
4,    _AUTOINC,    0xA2,   0x00,

// Divider for Postdivider of CMU and Pre-divder of CMU
4,    _AUTOINC,    0xD2,   0x00,

// LDO Voltage Setting
4,    _AUTOINC,    0xD3,   0x77,

// DP Mode
4,    _AUTOINC,    0xA9,   0x80,

// Enable Fifo
4,    _AUTOINC,    0xA7,   0x80,

//CLKRD duty Setting
4,    _AUTOINC,    0xBD,   0xF0,

///////////////////////////////////////////////////
// RBR
// VCO 1.5GHz~3GHz
4,    _AUTOINC,    0xBD,   0xF1,

// KVCO,Icp,Rs
4,    _AUTOINC,    0xD0,   0x73,
4,    _AUTOINC,    0xD1,   0x14,

// N.F Code
4,    _AUTOINC,    0xDF,   0x4F,
4,    _AUTOINC,    0xDE,   0xD2,
4,    _AUTOINC,    0xDD,   0x86,
4,    _AUTOINC,    0xDD,   0x86,

// Toggle CMU Power toggle Bit4
4,    _AUTOINC,    0xA0,   0x80,
4,    _AUTOINC,    0xA0,   0x90,

// Swing,Pre-emphasis
4,    _AUTOINC,    0xB0,   0x00,
4,    _AUTOINC,    0xB1,   0x1C,
4,    _AUTOINC,    0xB2,   0x1C,
4,    _AUTOINC,    0xB3,   0x1C,
4,    _AUTOINC,    0xB4,   0x1C,
4,    _AUTOINC,    0xB6,   0xFF,
4,    _AUTOINC,    0xB7,   0xFF,
4,    _AUTOINC,    0xB8,   0xFF,
4,    _AUTOINC,    0xB9,   0xFF,
4,    _AUTOINC,    0xBA,   0xAA,
4,    _AUTOINC,    0xBB,   0xAA,

///////////////////////////////////////////////////

// Idle Pattern
4,    _AUTOINC,    0x9F,   0xBB,
4,    _AUTOINC,    0x00,   0xFC,
4,    _AUTOINC,    0x01,   0x01,
4,    _AUTOINC,    0x01,   0x01,

// Inter-pair skew enable
4,    _AUTOINC,    0x0D,   0x04,

// Output data
4,    _AUTOINC,    0x9F,   0xBC,
4,    _AUTOINC,    0xA0,   0x9F,
4,    _AUTOINC,    0xA1,   0x00,
};


BYTE code tQCDPMST_RBR_FT[] =
{
//////////////////////////////////////////
// Enable ADC Bandgap (0x00C6[3])
//////////////////////////////////////////
4,    _NON_AUTOINC,    0x9F,    0x00,        // Page 00
4,    _NON_AUTOINC,    0xC6,    0x08,

//////////////////////////////////////////
// Enable GDI Bandgap (0x0BB4[7])
//////////////////////////////////////////
4,    _NON_AUTOINC,    0x9F,    0x0B,        // Page 0B
4,       _NON_AUTOINC,       0xB4,    0xA0,        // Enable GDI Bandgap & Set GDI bandgap ouput voltage to 1.21V

// DPTX Power ON and CMU Enable
4,    _AUTOINC,    0x9F,   0xBC,
4,    _AUTOINC,    0xA0,   0x90,
4,    _AUTOINC,    0xA2,   0x00,

// Divider for Postdivider of CMU and Pre-divder of CMU
4,    _AUTOINC,    0xD2,   0x00,

// LDO Voltage Setting
4,    _AUTOINC,    0xD3,   0x77,

// DP Mode
4,    _AUTOINC,    0xA9,   0x80,

// Enable Fifo
4,    _AUTOINC,    0xA7,   0x80,

//CLKRD duty Setting
4,    _AUTOINC,    0xBD,   0xF0,

///////////////////////////////////////////////////
// RBR
// VCO 1.5GHz~3GHz
4,    _AUTOINC,    0xBD,   0xF1,

// KVCO,Icp,Rs
4,    _AUTOINC,    0xD0,   0x73,
4,    _AUTOINC,    0xD1,   0x14,

// N.F Code
4,    _AUTOINC,    0xDF,   0x4F,
4,    _AUTOINC,    0xDE,   0xD2,
4,    _AUTOINC,    0xDD,   0x86,
4,    _AUTOINC,    0xDD,   0x86,

// Toggle CMU Power toggle Bit4
4,    _AUTOINC,    0xA0,   0x80,
4,    _AUTOINC,    0xA0,   0x90,

// Swing,Pre-emphasis
4,    _AUTOINC,    0xB0,   0x00,
4,    _AUTOINC,    0xB1,   0x04,
4,    _AUTOINC,    0xB2,   0x04,
4,    _AUTOINC,    0xB3,   0x04,
4,    _AUTOINC,    0xB4,   0x04,
4,    _AUTOINC,    0xB6,   0xCC,
4,    _AUTOINC,    0xB7,   0xCC,
4,    _AUTOINC,    0xB8,   0xAA,
4,    _AUTOINC,    0xB9,   0xAA,
4,    _AUTOINC,    0xBA,   0x22,
4,    _AUTOINC,    0xBB,   0x22,
///////////////////////////////////////////////////
// Idle Pattern
4,    _AUTOINC,    0x9F,   0xBB,
4,    _AUTOINC,    0x00,   0xFC,
4,    _AUTOINC,    0x01,   0x01,
4,    _AUTOINC,    0x01,   0x01,

// Inter-pair skew enable
4,    _AUTOINC,    0x0D,   0x04,

// Output data
4,    _AUTOINC,    0x9F,   0xBC,
4,    _AUTOINC,    0xA0,   0x9F,
4,    _AUTOINC,    0xA1,   0x00,
};

BYTE code tQCLVDS_EDPTX_HBR_FT[] =
{
//////////////////////////////////////////
// Enable GDI Bandgap (0x01D14[7])
//////////////////////////////////////////

4,	_NON_AUTOINC,	0x9F,	0x1D,       // Page 1D
4, 	_NON_AUTOINC,	0x14, 0x9B,       // Enable GDI Bandgap & Set GDI bandgap ouput voltage to 1.245V

// Set DISP mode is Dp Tx
4,_AUTOINC,	0x9F,   0x39,
4,_AUTOINC,	0x00,   0x04,

// Set Dp Tx Common Mode Voltage
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x01,   0x02,

// Set Dp Tx Major Current Control
4,_AUTOINC,	0x02,   0x0F,

// Disable Weakly Pull Down
4,_AUTOINC,	0x26,   0x00,
4,_AUTOINC,	0x36,   0x00,

// Power Up Dp Tx Analog Block
4,_AUTOINC,	0x00,   0xE0,

// Enable Dp Tx LDO Power
4,_AUTOINC,	0x73,   0x71,

// Enable Vby1 and DPTx Clock
4,_AUTOINC,	0x9F,   0x01,
4,_AUTOINC,	0xDC,   0x7F,

// Power Up Dp Tx Vby1 PLL
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x00,   0xE0,

// Set Dp Tx Digital Phy
4,_AUTOINC,	0x9F,   0x38,
4,_AUTOINC,	0x91,   0x01,

// Enable Digital Phy output
4,_AUTOINC,	0x8E,   0x0F,

// Enable Z0
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x61,   0x0F,
4,_AUTOINC,	0x62,   0x88,
4,_AUTOINC,	0x63,   0x88,

// Set CMU: DPTX Mode
// Set CMU Referenced Clk: Xtal Clk
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x73,   0x71,

// Disable N.F Set By FW
4,_AUTOINC,	0x9F,   0x38,
4,_AUTOINC,	0xD6,   0x01,

// Set Down SSC, Disable SSC
4,_AUTOINC,	0xD5,   0x00,

// Divider for Postdivider of CMU and Pre-divder of CMU
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x72,   0x00,

// LDO voltage Setting
4,_AUTOINC,	0x0E,   0xFC,

// CLKRD duty set to 4'b1111 @0638 as AMlee suggests.
4,_AUTOINC,	0x5D,   0xF8,

// Set CCO MODE,Normal Kvco
4,_AUTOINC,	0x03,   0x50,

// CMU_BYPASS R2
4,_AUTOINC,	0x0F,   0x01,

// Use PI, PI_current
4,_AUTOINC,	0x70,   0x01,

// CMU_Icp,Rs
4,_AUTOINC,	0x0D,   0x5C,

// N.F Code
4,_AUTOINC,	0x9F,   0x38,
4,_AUTOINC,	0xDE,   0xA4,
4,_AUTOINC,	0xDF,   0x97,
4,_AUTOINC,	0xDD,   0x85,
4,_AUTOINC,	0xDD,   0x85,	// Double buffer

// Enable CMU power
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x00,   0xE8,

// Swing/Pre-emphasis
4,_AUTOINC,	0x50,   0x00,
4,_AUTOINC,	0x51,   0x00,
4,_AUTOINC,	0x52,   0x00,
4,_AUTOINC,	0x53,   0x00,
4,_AUTOINC,	0x56,   0xFF,
4,_AUTOINC,	0x57,   0xCC,
4,_AUTOINC,	0x58,   0xCC,

// PN Swap
4,_AUTOINC,	0x9F,   0x38,
4,_AUTOINC,	0x80,   0x0F,
4,_AUTOINC,	0x83,   0x10,
4,_AUTOINC,	0x84,   0x32,
4,_AUTOINC,	0x85,   0xC2,   //fred add
4,_AUTOINC,	0x86,   0x98,
4,_AUTOINC,	0x88,   0x86,
4,_AUTOINC,	0x89,   0x62,
};

BYTE code tQCLVDS_EDPTX_RBR_FT[] =
{
//////////////////////////////////////////
// Enable GDI Bandgap (0x01D14[7])
//////////////////////////////////////////

4,	_NON_AUTOINC,	0x9F, 0x1D,       // Page 1D
4, 	_NON_AUTOINC,	0x14, 0x9B,       // Enable GDI Bandgap & Set GDI bandgap ouput voltage to 1.245V

// Set DISP mode is Dp Tx
4,_AUTOINC,	0x9F,   0x39,
4,_AUTOINC,	0x00,   0x04,

// Set Dp Tx Common Mode Voltage
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x01,   0x02,

// Set Dp Tx Major Current Control
4,_AUTOINC,	0x02,   0x0F,

// Disable Weakly Pull Down
4,_AUTOINC,	0x26,   0x00,
4,_AUTOINC,	0x36,   0x00,

// Power Up Dp Tx Analog Block
4,_AUTOINC,	0x00,   0xE0,

// Enable Dp Tx LDO Power
4,_AUTOINC,	0x73,   0x71,

// Enable Vby1 and DPTx Clock
4,_AUTOINC,	0x9F,   0x01,
4,_AUTOINC,	0xDC,   0x7F,

// Power Up Dp Tx Vby1 PLL
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x00,   0xE0,

// Set Dp Tx Digital Phy
4,_AUTOINC,	0x9F,   0x38,
4,_AUTOINC,	0x91,   0x01,

// Enable Digital Phy output
4,_AUTOINC,	0x8E,   0x0F,

// Enable Z0
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x61,   0x0F,
4,_AUTOINC,	0x62,   0x88,
4,_AUTOINC,	0x63,   0x88,

// Set CMU: DPTX Mode
// Set CMU Referenced Clk: Xtal Clk
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x73,   0x71,

// Disable N.F Set By FW
4,_AUTOINC,	0x9F,   0x38,
4,_AUTOINC,	0xD6,   0x01,

// Set Down SSC, Disable SSC
4,_AUTOINC,	0xD5,   0x00,

// Divider for Postdivider of CMU and Pre-divder of CMU
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x72,   0x00,

// LDO voltage Setting
4,_AUTOINC,	0x0E,   0xFC,

// CLKRD duty set to 4'b1111 @0638 as AMlee suggests.
4,_AUTOINC,	0x5D,   0xF8,

// Set CCO MODE,Normal Kvco
4,_AUTOINC,	0x03,   0x50,

// CMU_BYPASS R2
4,_AUTOINC,	0x0F,   0x01,

// Use PI, PI_current
4,_AUTOINC,	0x70,   0x01,

// CMU_Icp,Rs
4,_AUTOINC,	0x0D,   0x38,

// N.F Code
4,_AUTOINC,	0x9F,   0x38,
4,_AUTOINC,	0xDE,   0x49,
4,_AUTOINC,	0xDF,   0x27,
4,_AUTOINC,	0xDD,   0x83,
4,_AUTOINC,	0xDD,   0x83,	// Double buffer

// Enable CMU power
4,_AUTOINC,	0x9F,   0x55,
4,_AUTOINC,	0x00,   0xE8,
4,_AUTOINC,	0x02,   0x04,   //fred add

// Swing/Pre-emphasis
4,_AUTOINC,	0x50,   0x00,
4,_AUTOINC,	0x51,   0x00,
4,_AUTOINC,	0x52,   0x00,
4,_AUTOINC,	0x53,   0x00,
4,_AUTOINC,	0x56,   0xFF,
4,_AUTOINC,	0x57,   0xCC,
4,_AUTOINC,	0x58,   0xCC,

// PN Swap
4,_AUTOINC,	0x9F,   0x38,
4,_AUTOINC,	0x80,   0x0F,
4,_AUTOINC,	0x83,   0x10,
4,_AUTOINC,	0x84,   0x32,
4,_AUTOINC,	0x85,   0xC2,   //FRED ADD
4,_AUTOINC,	0x86,   0x98,
4,_AUTOINC,	0x88,   0x86,
4,_AUTOINC,	0x89,   0x62,
};

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerQCIICSDA(bit ucset);
void ScalerQCFPGASetSCLK(void);
void ScalerQCFPGACLRSCLK(void);
void ScalerQCFPGASendByte(BYTE ucValue);
void ScalerQCFPGASendAddr(BYTE ucAddr, bit ucReadWrite, bit ucAutoInc);
void ScalerQCFPGAReadStop(void);
void ScalerQCFPGAWriteStop(void);
void ScalerQCFPGASetByte(BYTE ucAddr, BYTE ucValue);
BYTE ScalerQCFPGAGetByte(void);
void ScalerQCFPGARead(BYTE ucAddr, BYTE *pucArray);

void ScalerQCFPGATable(void);
void ScalerQCFPGAContent(BYTE *pucpass);

bit ScalerQCDSPCTest(void);
bit ScalerQCDPMSTTest(void);    //FRED ADD
bit ScalerQCeDPTXTest(void);    //FRED ADD

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#define GET_GPIO_RESULT()                        (GPIO_RESULT)          //FRED ADD
#define GET_GPIO_RESULT_VBY1_A()                 (GPIO_RESULT_VBY1_A)   //FRED ADD
#define GET_GPIO_RESULT_VBY1_B()                 (GPIO_RESULT_VBY1_B)   //FRED ADD

//--------------------------------------------------
// Description  : Setting data with IIC_SDA_I
// Input Value  : bset  -->  Set bit of IIC_SDA_I
// Output Value : None
//--------------------------------------------------
void ScalerQCIICSDA(bit ucset)
{
    if(ucset == _HIGH)
    {
        FPGA_SW_IIC_SDA_SET();
    }

    else
    {
        FPGA_SW_IIC_SDA_CLR();
    }
}

//--------------------------------------------------
// Description  : Setting CLK of IIC_SCL_I
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCFPGASetSCLK(void)
{
    FPGA_SW_IIC_SCL_SET();
    FPGA_SW_IIC_SCL_SET();
    FPGA_SW_IIC_SCL_SET();
    FPGA_SW_IIC_SCL_SET();
    FPGA_SW_IIC_SCL_SET();
}

//--------------------------------------------------
// Description  : Clear CLK with IIC_SCL_I
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCFPGACLRSCLK(void)
{
    FPGA_SW_IIC_SCL_CLR();
    FPGA_SW_IIC_SCL_CLR();
    FPGA_SW_IIC_SCL_CLR();
    FPGA_SW_IIC_SCL_CLR();
    FPGA_SW_IIC_SCL_CLR();
}

//--------------------------------------------------
// Description  : Send the data to FPGA register
// Input Value  : ucValue  --> The data of FPGA register where you want to write
// Output Value : None
//--------------------------------------------------
void ScalerQCFPGASendByte(BYTE ucValue)
{
    ScalerQCIICSDA((bit)(ucValue & _BIT0));
    FPGA_SW_IIC_SCL_CLR();

    ScalerQCIICSDA((bit)(ucValue & _BIT1));
    FPGA_SW_IIC_SCL_SET();

    ScalerQCIICSDA((bit)(ucValue & _BIT2));
    FPGA_SW_IIC_SCL_CLR();

    ScalerQCIICSDA((bit)(ucValue & _BIT3));
    FPGA_SW_IIC_SCL_SET();

    ScalerQCIICSDA((bit)(ucValue & _BIT4));
    FPGA_SW_IIC_SCL_CLR();

    ScalerQCIICSDA((bit)(ucValue & _BIT5));
    FPGA_SW_IIC_SCL_SET();

    ScalerQCIICSDA((bit)(ucValue & _BIT6));
    FPGA_SW_IIC_SCL_CLR();

    ScalerQCIICSDA((bit)(ucValue & _BIT7));
    FPGA_SW_IIC_SCL_SET();
}

//--------------------------------------------------
// Description  : The address of the FPGA register
// Input Value  : ucAddr      --> Start address of register
//                bReadWrite  --> Setting the read/write command to FPGA
//                bAutoInc    --> Setting the auto/non-auto increase command to FPGA
// Output Value : None
//--------------------------------------------------
void ScalerQCFPGASendAddr(BYTE ucAddr, bit ucReadWrite, bit ucAutoInc)
{
    FPGA_SW_IIC_SCL_SET();
    ScalerQCIICSDA(_HIGH);
    ScalerQCIICSDA(_LOW);
    ScalerQCIICSDA(_HIGH);

    ScalerQCFPGASendByte(ucAddr);

    ScalerQCIICSDA(ucReadWrite);
    FPGA_SW_IIC_SCL_CLR();
    ScalerQCIICSDA(ucAutoInc);
    FPGA_SW_IIC_SCL_SET();
    ScalerQCIICSDA(_HIGH);
}

//--------------------------------------------------
// Description  : Stop reading the FPGA register
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCFPGAReadStop(void)
{
    ScalerQCIICSDA(_HIGH);
    ScalerQCIICSDA(_LOW);
    ScalerQCIICSDA(_HIGH);
    FPGA_SW_IIC_SCL_SET();
}

//--------------------------------------------------
// Description  : Stop writting the FPGA register
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCFPGAWriteStop(void)
{
    FPGA_SW_IIC_SCL_CLR();
    FPGA_SW_IIC_SCL_SET();
    ScalerQCIICSDA(_HIGH);
    ScalerQCIICSDA(_LOW);
    ScalerQCIICSDA(_HIGH);
}

//--------------------------------------------------
// Description  : Write a data array into registers of scaler (FPGA)
// Input Value  : ucAddr    --> Start address of register
//                ucValue   --> Pointer of the writing data array
// Output Value : None
//--------------------------------------------------
void ScalerQCFPGASetByte(BYTE ucAddr, BYTE ucValue)
{
    ScalerQCFPGASendAddr(ucAddr, _WRITE, _NON_AUTOINC);
    ScalerQCFPGASendByte(ucValue);
    ScalerQCFPGAWriteStop();
}

//--------------------------------------------------
// Description  : Get the data of FPGA register
// Input Value  : None
// Output Value : Data of FPGA register
//--------------------------------------------------
BYTE ScalerQCFPGAGetByte(void)
{
    BYTE ucValue = 0;
    BYTE ucChk = 0;

    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57, 0x00); // Pin167

    ScalerQCFPGACLRSCLK();
    FPGA_SW_IIC_SDA_CHK(ucChk);
    if(ucChk)
    {
        ucValue |= _BIT0;
    }

    ScalerQCFPGASetSCLK();
    FPGA_SW_IIC_SDA_CHK(ucChk);
    if(ucChk)
    {
        ucValue |= _BIT1;
    }

    ScalerQCFPGACLRSCLK();
    FPGA_SW_IIC_SDA_CHK(ucChk);
    if(ucChk)
    {
        ucValue |= _BIT2;
    }

    ScalerQCFPGASetSCLK();
    FPGA_SW_IIC_SDA_CHK(ucChk);
    if(ucChk)
    {
        ucValue |= _BIT3;
    }

    ScalerQCFPGACLRSCLK();
    FPGA_SW_IIC_SDA_CHK(ucChk);
    if(ucChk)
    {
        ucValue |= _BIT4;
    }

    ScalerQCFPGASetSCLK();
    FPGA_SW_IIC_SDA_CHK(ucChk);
    if(ucChk)
    {
        ucValue |= _BIT5;
    }

    ScalerQCFPGACLRSCLK();
    FPGA_SW_IIC_SDA_CHK(ucChk);
    if(ucChk)
    {
        ucValue |= _BIT6;
    }

    ScalerQCFPGASetSCLK();
    FPGA_SW_IIC_SDA_CHK(ucChk);
    if(ucChk)
    {
        ucValue |= _BIT7;
    }

    ScalerQCFPGACLRSCLK();

    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57, 0x01); // Pin167
    return ucValue;
}

//--------------------------------------------------
// Description  : Read data from registers of scaler and put it into an reading data array (FPGA)
// Input Value  : ucAddr    --> Start address of register
//                pArray    --> Pointer of the reading data array
// Output Value : None
//--------------------------------------------------
void ScalerQCFPGARead(BYTE ucAddr, BYTE *pucArray)
{
    ScalerQCFPGASendAddr(ucAddr, _READ, _NON_AUTOINC);
    *pucArray = ScalerQCFPGAGetByte();
    ScalerQCFPGAReadStop();
}

//--------------------------------------------------
// Description  : FPGA for LVDS configuration setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCFPGATable(void)
{
    ScalerQCFPGASetByte(0x00, 0x00);
    ScalerTimerDelayXms(2);

    ScalerQCFPGASetByte(0x00, 0x7E);
}

//--------------------------------------------------
// Description  : The content of FPGA setting
// Input Value  : check  --> checking the FPGA register
// Output Value : None
//--------------------------------------------------
void ScalerQCFPGAContent(BYTE *pucPass)
{
    BYTE ucCheck[_DPSC_CRC_NUM];
    BYTE ucScalerCRC[_DPSC_CRC_NUM];
    BYTE ucLVDSTxPort[4];

    ScalerQCFPGARead(0xFC, &ucCheck[0]);
    ScalerQCFPGARead(0xFD, &ucCheck[1]);
    ScalerQCFPGARead(0xFE, &ucCheck[2]);
    ScalerQCFPGARead(0xFF, &ucCheck[3]);

    if((ucCheck[0] == 0x20) && (ucCheck[1] == 0x14) && (ucCheck[2] == 0x05) && (ucCheck[3] == 0x26))
    {
        ScalerRead(P39_31_D_CONV_CRC_0_H, _DPSC_CRC_NUM, &ucScalerCRC, _AUTOINC);

        //------LVDS QA Environment Setting------//
        ScalerBurstWrite(tQCLVDS_QA_ENVIRONMENT, sizeof(tQCLVDS_QA_ENVIRONMENT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        //------Reset FPGA Setting------//
        ScalerQCFPGATable();

        ScalerTimerDelayXms(200);

        if((ucCheck[0] != 0x20) || (ucCheck[1] != 0x14) || (ucCheck[2] != 0x05) || (ucCheck[3] != 0x26))
        {
            DebugMessageQC("5. FPGA Flash Code Error!!", 0x00);

            *pucPass |= _TEST_FAIL;
        }
        else
        {
            ScalerQCFPGARead(0x20, &ucCheck[0]);
            ScalerQCFPGARead(0x21, &ucCheck[1]);
            ScalerQCFPGARead(0x22, &ucCheck[2]);
            ScalerQCFPGARead(0x23, &ucCheck[3]);
            ScalerQCFPGARead(0x24, &ucCheck[4]);
            ScalerQCFPGARead(0x25, &ucCheck[5]);
            ScalerQCFPGARead(0x26, &ucCheck[6]);
            ScalerQCFPGARead(0x27, &ucCheck[7]);
            ScalerQCFPGARead(0x28, &ucCheck[8]);
            ScalerQCFPGARead(0x29, &ucCheck[9]);
            ScalerQCFPGARead(0x2A, &ucCheck[10]);
            ScalerQCFPGARead(0x2B, &ucCheck[11]);
            ScalerQCFPGARead(0x2C, &ucCheck[12]);
            ScalerQCFPGARead(0x2D, &ucCheck[13]);
            ScalerQCFPGARead(0x2E, &ucCheck[14]);
            ScalerQCFPGARead(0x2F, &ucCheck[15]);
            ScalerQCFPGARead(0x30, &ucCheck[16]);
            ScalerQCFPGARead(0x31, &ucCheck[17]);
            ScalerQCFPGARead(0x32, &ucCheck[18]);
            ScalerQCFPGARead(0x33, &ucCheck[19]);
            ScalerQCFPGARead(0x34, &ucCheck[20]);
            ScalerQCFPGARead(0x35, &ucCheck[21]);
            ScalerQCFPGARead(0x36, &ucCheck[22]);
            ScalerQCFPGARead(0x37, &ucCheck[23]);
            ScalerQCFPGARead(0x38, &ucCheck[24]);
            ScalerQCFPGARead(0x39, &ucCheck[25]);
            ScalerQCFPGARead(0x3A, &ucCheck[26]);
            ScalerQCFPGARead(0x3B, &ucCheck[27]);
            ScalerQCFPGARead(0x3C, &ucCheck[28]);
            ScalerQCFPGARead(0x3D, &ucCheck[29]);
            ScalerQCFPGARead(0x3E, &ucCheck[30]);
            ScalerQCFPGARead(0x3F, &ucCheck[31]);
            ScalerQCFPGARead(0x40, &ucCheck[32]);
            ScalerQCFPGARead(0x41, &ucCheck[33]);
            ScalerQCFPGARead(0x42, &ucCheck[34]);
            ScalerQCFPGARead(0x43, &ucCheck[35]);
            ScalerQCFPGARead(0x44, &ucCheck[36]);
            ScalerQCFPGARead(0x45, &ucCheck[37]);
            ScalerQCFPGARead(0x46, &ucCheck[38]);
            ScalerQCFPGARead(0x47, &ucCheck[39]);
            ScalerQCFPGARead(0x48, &ucCheck[40]);
            ScalerQCFPGARead(0x49, &ucCheck[41]);
            ScalerQCFPGARead(0x4A, &ucCheck[42]);
            ScalerQCFPGARead(0x4B, &ucCheck[43]);
            ScalerQCFPGARead(0x4C, &ucCheck[44]);
            ScalerQCFPGARead(0x4D, &ucCheck[45]);
            ScalerQCFPGARead(0x4E, &ucCheck[46]);
            ScalerQCFPGARead(0x4F, &ucCheck[47]);

            if((ucCheck[24] == ucScalerCRC[24]) && (ucCheck[25] == ucScalerCRC[25]) && (ucCheck[26] == ucScalerCRC[26]) && (ucCheck[27] == ucScalerCRC[27]) && (ucCheck[28] == ucScalerCRC[28]) && (ucCheck[29] == ucScalerCRC[29]) &&
               (ucCheck[30] == ucScalerCRC[30]) && (ucCheck[31] == ucScalerCRC[31]) && (ucCheck[32] == ucScalerCRC[32]) && (ucCheck[33] == ucScalerCRC[33]) && (ucCheck[34] == ucScalerCRC[34]) && (ucCheck[35] == ucScalerCRC[35]))
            {
                ucLVDSTxPort[0] = _TEST_PASS;
                DebugMessageQC("5. //----LVDS TXA Pass----//", 0x00);
            }
            else
            {
                ucLVDSTxPort[0] = _TEST_FAIL;

#if(_DSPC_FPGA_CONTENT == _SIMPLE)

                DebugMessageQC("5. //----LVDS TXA Fail----//", 0x00);

#elif(_DSPC_FPGA_CONTENT == _COMPLEX)

                DebugMessageQC("5. //----LVDS TXA Fail Start----//", 0x00);

                if((ucCheck[24] != ucScalerCRC[24]) || (ucCheck[25] != ucScalerCRC[25]))
                {
                    DebugMessageQC("5. LVDS TXA0 Fail", ucCheck[24]);
                }

                if((ucCheck[26] != ucScalerCRC[26]) || (ucCheck[27] != ucScalerCRC[27]))
                {
                    DebugMessageQC("5. LVDS TXA1 Fail", ucCheck[26]);
                }

                if((ucCheck[28] != ucScalerCRC[28]) || (ucCheck[29] != ucScalerCRC[29]))
                {
                    DebugMessageQC("5. LVDS TXA2 Fail", ucCheck[28]);
                }

                if((ucCheck[30] != ucScalerCRC[30]) || (ucCheck[31] != ucScalerCRC[31]))
                {
                    DebugMessageQC("5. LVDS TXACK Fail", ucCheck[30]);
                }

                if((ucCheck[32] != ucScalerCRC[32]) || (ucCheck[33] != ucScalerCRC[33]))
                {
                    DebugMessageQC("5. LVDS TXA3 Fail", ucCheck[32]);
                }

                if((ucCheck[34] != ucScalerCRC[34]) || (ucCheck[35] != ucScalerCRC[35]))
                {
                    DebugMessageQC("5. LVDS TXA4 Fail", ucCheck[34]);
                }

                DebugMessageQC("5. //----LVDS TXA Fail End----//", 0x00);
#endif
            }

            if((ucCheck[36] == ucScalerCRC[36]) && (ucCheck[37] == ucScalerCRC[37]) && (ucCheck[38] == ucScalerCRC[38]) && (ucCheck[39] == ucScalerCRC[39]) && (ucCheck[40] == ucScalerCRC[40]) && (ucCheck[41] == ucScalerCRC[41]) &&
               (ucCheck[44] == ucScalerCRC[44]) && (ucCheck[45] == ucScalerCRC[45]) && (ucCheck[46] == ucScalerCRC[46]) && (ucCheck[47] == ucScalerCRC[47]))
               //(ucCheck[42] == ucScalerCRC[42]) && (ucCheck[43] == ucScalerCRC[43]) && (ucCheck[44] == ucScalerCRC[44]) && (ucCheck[45] == ucScalerCRC[45]) && (ucCheck[46] == ucScalerCRC[46]) && (ucCheck[47] == ucScalerCRC[47]))
            {
                ucLVDSTxPort[1] = _TEST_PASS;
                DebugMessageQC("5. //----LVDS TXB Pass----//", 0x00);
            }
            else
            {
                ucLVDSTxPort[1] = _TEST_FAIL;

#if(_DSPC_FPGA_CONTENT == _SIMPLE)

                DebugMessageQC("5. //----LVDS TXB Fail----//", 0x00);

#elif(_DSPC_FPGA_CONTENT == _COMPLEX)

                DebugMessageQC("5. //----LVDS TXB Fail Strat----//", 0x00);

                if((ucCheck[36] != ucScalerCRC[36]) || (ucCheck[37] != ucScalerCRC[37]))
                {
                    DebugMessageQC("5. LVDS TXB0 Fail", ucCheck[36]);
                }

                if((ucCheck[38] != ucScalerCRC[38]) || (ucCheck[39] != ucScalerCRC[39]))
                {
                    DebugMessageQC("5. LVDS TXB1 Fail", ucCheck[38]);
                }

                if((ucCheck[40] != ucScalerCRC[40]) || (ucCheck[41] != ucScalerCRC[41]))
                {
                    DebugMessageQC("5. LVDS TXB2 Fail", ucCheck[40]);
                }

                /*
                if((ucCheck[42] != ucScalerCRC[42]) || (ucCheck[43] != ucScalerCRC[43]))
                {
                    DebugMessageQC("5. LVDS TXBCK Fail", ucCheck[42]);
                }
                */

                if((ucCheck[44] != ucScalerCRC[44]) || (ucCheck[45] != ucScalerCRC[45]))
                {
                    DebugMessageQC("5. LVDS TXB3 Fail", ucCheck[44]);
                }

                if((ucCheck[46] != ucScalerCRC[46]) || (ucCheck[47] != ucScalerCRC[47]))
                {
                    DebugMessageQC("5. LVDS TXB4 Fail", ucCheck[46]);
                }

                DebugMessageQC("5. //----LVDS TXB Fail End----//", 0x00);
#endif
            }

            if((ucCheck[0] == ucScalerCRC[0]) && (ucCheck[1] == ucScalerCRC[1]) && (ucCheck[2] == ucScalerCRC[2]) && (ucCheck[3] == ucScalerCRC[3]) && (ucCheck[4] == ucScalerCRC[4]) && (ucCheck[5] == ucScalerCRC[5]) &&
            (ucCheck[6] == ucScalerCRC[6]) && (ucCheck[7] == ucScalerCRC[7]) && (ucCheck[8] == ucScalerCRC[8]) && (ucCheck[9] == ucScalerCRC[9]) && (ucCheck[10] == ucScalerCRC[10]) && (ucCheck[11] == ucScalerCRC[11]))
            {
                ucLVDSTxPort[2] = _TEST_PASS;
                DebugMessageQC("5. //----LVDS TXC Pass----//", 0x00);
            }
            else
            {
                ucLVDSTxPort[2] = _TEST_FAIL;

#if(_DSPC_FPGA_CONTENT == _SIMPLE)

                DebugMessageQC("5. //----LVDS TXC Fail Start----//", 0x00);

#elif(_DSPC_FPGA_CONTENT == _COMPLEX)

                DebugMessageQC("5. //----LVDS TXC Fail----//", 0x00);

                if((ucCheck[0] != ucScalerCRC[0]) || (ucCheck[1] != ucScalerCRC[1]))
                {
                    DebugMessageQC("5. LVDS TXC0 Fail", ucCheck[0]);
                }

                if((ucCheck[2] != ucScalerCRC[2]) || (ucCheck[3] != ucScalerCRC[3]))
                {
                    DebugMessageQC("5. LVDS TXC1 Fail", ucCheck[2]);
                }

                if((ucCheck[4] != ucScalerCRC[4]) || (ucCheck[5] != ucScalerCRC[5]))
                {
                    DebugMessageQC("5. LVDS TXC2 Fail", ucCheck[4]);
                }

                if((ucCheck[6] != ucScalerCRC[6]) || (ucCheck[7] != ucScalerCRC[7]))
                {
                    DebugMessageQC("5. LVDS TXCCK Fail", ucCheck[6]);
                }

                if((ucCheck[8] != ucScalerCRC[8]) || (ucCheck[9] != ucScalerCRC[9]))
                {
                    DebugMessageQC("5. LVDS TXC3 Fail", ucCheck[8]);
                }

                if((ucCheck[10] != ucScalerCRC[10]) || (ucCheck[11] != ucScalerCRC[11]))
                {
                    DebugMessageQC("5. LVDS TXC4 Fail", ucCheck[10]);
                }

                DebugMessageQC("5. //----LVDS TXC Fail End----//", 0x00);
#endif
            }

            if((ucCheck[12] == ucScalerCRC[12]) && (ucCheck[13] == ucScalerCRC[13]) && (ucCheck[14] == ucScalerCRC[14]) && (ucCheck[15] == ucScalerCRC[15]) && (ucCheck[16] == ucScalerCRC[16]) && (ucCheck[17] == ucScalerCRC[17]) &&
            (ucCheck[20] == ucScalerCRC[20]) && (ucCheck[21] == ucScalerCRC[21]) && (ucCheck[22] == ucScalerCRC[22]) && (ucCheck[23] == ucScalerCRC[23]))
            //(ucCheck[18] == ucScalerCRC[18]) && (ucCheck[19] == ucScalerCRC[19]) && (ucCheck[20] == ucScalerCRC[20]) && (ucCheck[21] == ucScalerCRC[21]) && (ucCheck[22] == ucScalerCRC[22]) && (ucCheck[23] == ucScalerCRC[23]))
            {
                ucLVDSTxPort[3] = _TEST_PASS;
                DebugMessageQC("5. //----LVDS TXD Pass----//", 0x00);
            }
            else
            {
                ucLVDSTxPort[3] = _TEST_FAIL;

#if(_DSPC_FPGA_CONTENT == _SIMPLE)

                DebugMessageQC("5. //----LVDS TXD Fail----//", 0x00);

#elif(_DSPC_FPGA_CONTENT == _COMPLEX)

                DebugMessageQC("5. //----LVDS TXD Fail Start----//", 0x00);

                if((ucCheck[12] != ucScalerCRC[12]) || (ucCheck[13] != ucScalerCRC[13]))
                {
                    DebugMessageQC("5. LVDS TXD0 Fail", ucCheck[12]);
                }

                if((ucCheck[14] != ucScalerCRC[14]) || (ucCheck[15] != ucScalerCRC[15]))
                {
                    DebugMessageQC("5. LVDS TXD1 Fail", ucCheck[14]);
                }

                if((ucCheck[16] != ucScalerCRC[16]) || (ucCheck[17] != ucScalerCRC[17]))
                {
                    DebugMessageQC("5. LVDS TXD2 Fail", ucCheck[16]);
                }

                if((ucCheck[20] != ucScalerCRC[20]) || (ucCheck[21] != ucScalerCRC[21]))
                {
                    DebugMessageQC("5. LVDS TXD3 Fail", ucCheck[20]);
                }

                if((ucCheck[22] != ucScalerCRC[22]) || (ucCheck[23] != ucScalerCRC[23]))
                {
                    DebugMessageQC("5. LVDS TXD4 Fail", ucCheck[22]);
                }

                DebugMessageQC("5. //----LVDS TXD Fail End----//", 0x00);
#endif
            }
        }

        if((ucLVDSTxPort[0] == _TEST_PASS) && (ucLVDSTxPort[1] == _TEST_PASS) && (ucLVDSTxPort[2] == _TEST_PASS) && (ucLVDSTxPort[3] == _TEST_PASS))
        {
            DebugMessageQC("5. FPGA Content Pass", 0x00);
            *pucPass |= _TEST_PASS;
        }
        else
        {
            DebugMessageQC("5. FPGA Content Fail", 0x00);
            *pucPass |= _TEST_FAIL;
        }
    }
    else
    {
        DebugMessageQC("5. FPGA Environment Fail", 0x00);
        *pucPass |= _TEST_FAIL;
    }
}

//************************************************//
//--------------------------------------------------
// Description  : QC DPMST Test
// Input Value  : None
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCDPMSTTest(void)
{
    BYTE ucResult = _TEST_PASS;

    ScalerSetByte(P6_C0_REG_DAC_POWER0, 0x00);
    ScalerSetByte(P6_C1_REG_DAC_POWER1, 0x00);

    ScalerSetByte(P10_07_PIN_SHARE_CTRL17, 0x01);   //Pin36 Push-Pull
    ScalerSetByte(P10_10_PIN_SHARE_CTRL40, 0x00);   //Pin37 GPI
    ScalerSetByte(P10_11_PIN_SHARE_CTRL41, 0x01);   //Pin38 Push-Pull
    ScalerSetByte(P10_5B_PIN_SHARE_CTRLD3, 0x00);   //Pin42 GPI
    ScalerSetByte(P10_5C_PIN_SHARE_CTRLD4, 0x01);   //Pin43 Push-Pull
    ScalerSetByte(P10_18_PIN_SHARE_CTRL50, 0x01);   //Pin44 Push-Pull

    ScalerBurstWrite(tQCDPMST_HBR2_FT, sizeof(tQCDPMST_HBR2_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    // For DP HBR
    pin36 = 0;    //PIN36
    MCU_FE01_PORT41_PIN_REG = 1;    //PIN38

    ScalerTimerDelayXms(10);

    // For DP HBR2
    pin36 = 1;  //Pin36
    MCU_FE01_PORT41_PIN_REG = 0;  //Pin38

    ScalerTimerDelayXms(10);

    // For DP TX TEST
    MCU_FE48_PORTD0_PIN_REG = 0;    //Pin43
    MCU_FE08_PORT50_PIN_REG = 1;    //Pin44

    ScalerTimerDelayXms(100);

    GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE00_PORT40_PIN_REG) << 1) | ((BYTE)(MCU_FE47_PORTC7_PIN_REG));   // Pin37,Pin42

    DebugMessageQC("pin37", MCU_FE00_PORT40_PIN_REG);
    DebugMessageQC("pin42", MCU_FE47_PORTC7_PIN_REG);
    DebugMessageQC("pin36 ==1", pin36);
    DebugMessageQC("pin38 ==0", MCU_FE01_PORT41_PIN_REG);

    if(GET_GPIO_RESULT() == 0x00)
    {
        DebugMessageQC("DP HBR2: PASS 1", 0);

    }
    else
    {
        // For DP HBR
        pin36 = 0;    //PIN36
        MCU_FE01_PORT41_PIN_REG = 1;    //PIN38

        ScalerTimerDelayXms(10);

        ScalerBurstWrite(tQCDPMST_HBR2_21_FT, sizeof(tQCDPMST_HBR2_21_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        // For DP HBR2
        pin36 = 1;    //PIN36
        MCU_FE01_PORT41_PIN_REG = 0;    //PIN38

        ScalerTimerDelayXms(100);

        GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE00_PORT40_PIN_REG) << 1) | ((BYTE)(MCU_FE47_PORTC7_PIN_REG));   // Pin37,Pin42

         if(GET_GPIO_RESULT() == 0x00)
         {
            DebugMessageQC("DP HBR2: PASS 2", 0);

         }
         else
         {
            DebugMessageQC("DP HBR2: FAIL", 0);
         }

    }

    ScalerTimerDelayXms(50);

    ScalerBurstWrite(tQCDPMST_HBR_FT, sizeof(tQCDPMST_HBR_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    // For DP TX TEST
    MCU_FE48_PORTD0_PIN_REG = 0;    //Pin43
    MCU_FE08_PORT50_PIN_REG = 1;    //Pin44

    // For DP HBR
    pin36 = 0;    //PIN36
    MCU_FE01_PORT41_PIN_REG = 1;    //PIN38

    ScalerTimerDelayXms(100);

    GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE00_PORT40_PIN_REG) << 1) | ((BYTE)(MCU_FE47_PORTC7_PIN_REG));   // Pin37,Pin42

    DebugMessageQC("pin37", MCU_FE00_PORT40_PIN_REG);
    DebugMessageQC("pin42", MCU_FE47_PORTC7_PIN_REG);
    DebugMessageQC("pin36 ==0", pin36);
    DebugMessageQC("pin38 ==1", MCU_FE01_PORT41_PIN_REG);

    if(GET_GPIO_RESULT() == 0x00)
    {
        DebugMessageQC("DP HBR: PASS 1", 0);

    }
    else
    {
        DebugMessageQC("DP HBR: TEST 2", 0);
        // For DP HBR2
        pin36 = 1;    //PIN36
        MCU_FE01_PORT41_PIN_REG = 0;    //PIN38

        ScalerTimerDelayXms(10);

        ScalerBurstWrite(tQCDPMST_HBR_21_FT, sizeof(tQCDPMST_HBR_21_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

         // For DP HBR
        pin36 = 0;    //PIN36
        MCU_FE01_PORT41_PIN_REG = 1;    //PIN38


        ScalerTimerDelayXms(100);

        GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE00_PORT40_PIN_REG) << 1) | ((BYTE)(MCU_FE47_PORTC7_PIN_REG));   // Pin37,Pin42

         if(GET_GPIO_RESULT() == 0x00)
         {
            DebugMessageQC("DP HBR: PASS 2", 0);

         }
         else
         {
            DebugMessageQC("DP HBR: FAIL", 0);
         }
    }

    ScalerTimerDelayXms(50);

    ScalerBurstWrite(tQCDPMST_RBR_FT, sizeof(tQCDPMST_RBR_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    // For DP TX TEST
    MCU_FE48_PORTD0_PIN_REG = 0;    //Pin43
    MCU_FE08_PORT50_PIN_REG = 1;    //Pin44

    // For DP RBR
    pin36 = 0;    //PIN36
    MCU_FE01_PORT41_PIN_REG = 0;    //PIN38

    ScalerTimerDelayXms(100);

    GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE00_PORT40_PIN_REG) << 1) | ((BYTE)(MCU_FE47_PORTC7_PIN_REG));   // Pin37,Pin42

    DebugMessageQC("pin37", MCU_FE00_PORT40_PIN_REG);
    DebugMessageQC("pin42", MCU_FE47_PORTC7_PIN_REG);
    DebugMessageQC("pin36 ==0", pin36);
    DebugMessageQC("pin38 ==0", MCU_FE01_PORT41_PIN_REG);

    if(GET_GPIO_RESULT() == 0x00)
    {
        DebugMessageQC("DP RBR: PASS 1", 0);

        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("DP RBR: TEST 2", 0);
        // For DP HBR
        pin36 = 0;    //PIN36
        MCU_FE01_PORT41_PIN_REG = 1;    //PIN38

        ScalerTimerDelayXms(10);

        ScalerBurstWrite(tQCDPMST_RBR_21_FT, sizeof(tQCDPMST_RBR_21_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        // For DP RBR
        pin36 = 0;    //PIN36
        MCU_FE01_PORT41_PIN_REG = 0;    //PIN38

        ScalerTimerDelayXms(100);

        GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE00_PORT40_PIN_REG) << 1) | ((BYTE)(MCU_FE47_PORTC7_PIN_REG));   // Pin37,Pin42

         if(GET_GPIO_RESULT() == 0x00)
         {
            DebugMessageQC("DP RBR: PASS 2", 0);

            return _TEST_PASS;
         }
         else
         {
            DebugMessageQC("DP RBR: FAIL", 0);
         }

        return _TEST_FAIL;
    }
}


//************************************************//
//--------------------------------------------------
// Description  : QC eDP Tx Test
// Input Value  : None
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCeDPTXTest(void)
{
    BYTE ucResult = _TEST_PASS;

    // Switch to eDPTX output
    PCB_SET_LVDS_DPTX_SWITCH(_DPTX_PANEL_OUTPUT);

    // Set Video Stream parameter
    ScalerDisplayDPTx1VideoStreamOutput(_ENABLE);

    ScalerSetByte(P6_C0_REG_DAC_POWER0, 0x00);
    ScalerSetByte(P6_C1_REG_DAC_POWER1, 0x00);

    ScalerSetByte(P10_12_PIN_SHARE_CTRL42, 0x01);   //Pin36 Push-Pull
    ScalerSetByte(P10_13_PIN_SHARE_CTRL43, 0x00);   //Pin37 GPI
    ScalerSetByte(P10_14_PIN_SHARE_CTRL44, 0x01);   //Pin38 Push-Pull
    ScalerSetByte(P10_15_PIN_SHARE_CTRL45, 0x00);   //Pin42 GPI
    ScalerSetByte(P10_16_PIN_SHARE_CTRL46, 0x01);   //Pin43 Push-Pull
    ScalerSetByte(P10_17_PIN_SHARE_CTRL47, 0x01);   //Pin44 Push-Pull

    ScalerBurstWrite(tQCLVDS_EDPTX_HBR_FT, sizeof(tQCLVDS_EDPTX_HBR_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    // For DP HBR2
    MCU_FE02_PORT42_PIN_REG = 1;    //PIN36
    MCU_FE04_PORT44_PIN_REG = 0;    //PIN38

    ScalerTimerDelayXms(10);

    // For DP TX TEST
    MCU_FE06_PORT46_PIN_REG = 0;    //Pin43
    MCU_FE07_PORT47_PIN_REG = 1;    //Pin44

    // For DP HBR
    MCU_FE02_PORT42_PIN_REG = 0;    //PIN36
    MCU_FE04_PORT44_PIN_REG = 1;    //PIN38

    ScalerTimerDelayXms(100);

    GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE03_PORT43_PIN_REG) << 1) | ((BYTE)(MCU_FE05_PORT45_PIN_REG));   // Pin37,Pin42

    DebugMessageQC("pin37", MCU_FE03_PORT43_PIN_REG);
    DebugMessageQC("pin42", MCU_FE05_PORT45_PIN_REG);
    DebugMessageQC("pin36 ==0", MCU_FE02_PORT42_PIN_REG);
    DebugMessageQC("pin38 ==1", MCU_FE04_PORT44_PIN_REG);

    if(GET_GPIO_RESULT() == 0x00)
    {
        DebugMessageQC("LVDS_Combo_DP HBR: PASS 1", 0);

    }
    else
    {
        DebugMessageQC("LVDS_Combo_DP HBR: TEST 2", 0);
        // For DP HBR2
        MCU_FE02_PORT42_PIN_REG = 1;    //PIN36
        MCU_FE04_PORT44_PIN_REG = 0;    //PIN38

        ScalerTimerDelayXms(10);

        ScalerBurstWrite(tQCLVDS_EDPTX_HBR_FT, sizeof(tQCLVDS_EDPTX_HBR_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        // For DP HBR
        MCU_FE02_PORT42_PIN_REG = 0;    //PIN36
        MCU_FE04_PORT44_PIN_REG = 1;    //PIN38

        ScalerTimerDelayXms(100);

        GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE03_PORT43_PIN_REG) << 1) | ((BYTE)(MCU_FE28_PORT90_PIN_REG));   // Pin37,Pin42


        if(GET_GPIO_RESULT() == 0x00)
        {
            DebugMessageQC("LVDS_Combo_DP HBR: PASS 2", 0);

        }
        else
        {
            DebugMessageQC("LVDS_Combo_DP HBR: FAIL", 0);
        }
    }

    ScalerTimerDelayXms(50);

    ScalerBurstWrite(tQCLVDS_EDPTX_RBR_FT, sizeof(tQCLVDS_EDPTX_RBR_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    // For DP TX TEST
    MCU_FE06_PORT46_PIN_REG = 0;    //Pin43
    MCU_FE07_PORT47_PIN_REG = 1;    //Pin44

    // For DP RBR
    MCU_FE02_PORT42_PIN_REG = 0;    //PIN36
    MCU_FE04_PORT44_PIN_REG = 0;    //PIN38

    ScalerTimerDelayXms(100);

    GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE03_PORT43_PIN_REG) << 1) | ((BYTE)(MCU_FE05_PORT45_PIN_REG));   // Pin37,Pin42

    DebugMessageQC("pin37", MCU_FE03_PORT43_PIN_REG);
    DebugMessageQC("pin42", MCU_FE05_PORT45_PIN_REG);
    DebugMessageQC("pin36 ==0", MCU_FE02_PORT42_PIN_REG);
    DebugMessageQC("pin38 ==0", MCU_FE04_PORT44_PIN_REG);

    if(GET_GPIO_RESULT() == 0x00)
    {
        DebugMessageQC("LVDS_Combo_DP RBR: PASS 1", 0);

        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("LVDS_Combo_DP RBR: TEST 2", 0);
        // For DP HBR
        MCU_FE02_PORT42_PIN_REG = 0;    //PIN36
        MCU_FE04_PORT44_PIN_REG = 1;    //PIN38

        ScalerTimerDelayXms(10);

        ScalerBurstWrite(tQCLVDS_EDPTX_RBR_FT, sizeof(tQCLVDS_EDPTX_RBR_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        // For DP RBR
        MCU_FE02_PORT42_PIN_REG = 0;    //PIN36
        MCU_FE04_PORT44_PIN_REG = 0;    //PIN38

        ScalerTimerDelayXms(100);

        GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE03_PORT43_PIN_REG) << 1) | ((BYTE)(MCU_FE05_PORT45_PIN_REG));   // Pin37,Pin42

        if(GET_GPIO_RESULT() == 0x00)
        {
           DebugMessageQC("LVDS_Combo_DP RBR: PASS 2", 0);

           return _TEST_PASS;

        }
        else
        {
           DebugMessageQC("LVDS_Combo_DP RBR: FAIL", 0);
        }

        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : QC DSPC Test
// Input Value  : None
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCDSPCTest(void)
{
    BYTE ucResult = _TEST_PASS;
    BYTE ucSCL = 0x00;
    BYTE ucSDA = 0x00;
    BYTE test = 0;

    // Group A power block power cut off
    if((ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT4) == _BIT4) || (ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT1) == _BIT1))
    {
        // Group A Power Cut block Reset
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT0, _BIT0);

        // Wait for DDR stable, can't delete
        ScalerTimerDelayXms(10);

        PCB_VCCK_OFF_POWER(_VCCK_OFF_POWER_ON);

        // Wait for 1.1V stable, can't delete
        ScalerTimerDelayXms(10);

        // Group A power block power isolation off
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT1, 0x00);
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT4, 0x00);

        // Group A Power Cut block Relase
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT0, 0x00);
    }

    // Switch to LVDS output
    PCB_SET_LVDS_DPTX_SWITCH(_LVDS_PANEL_OUTPUT);

    ucSCL = ScalerGetByte(P10_1C_PIN_SHARE_CTRL54);
    ucSDA = ScalerGetByte(P10_1F_PIN_SHARE_CTRL57);

    ScalerSetByte(P10_1C_PIN_SHARE_CTRL54, 0x01); // Pin164 SCL (Push-pull)
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57, 0x01); // Pin167 SDA (Push-pull)
    ScalerTimerDelayXms(2);

#if(_DSPC_FPGA_TEST == _ENABLE)
    while(1)
    {
        //------LVDS 4_Port 85MHz------//
        ScalerBurstWrite(tQCLVDS_FT, sizeof(tQCLVDS_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        ScalerTimerDelayXms(200);

        ScalerQCFPGAContent(&ucResult);

        while(test < 250)
        {
            ScalerDebug();

            test += 1;
        }
        test = 0;
    }

#else
    //------LVDS 4_Port 85MHz------//
    ScalerBurstWrite(tQCLVDS_FT, sizeof(tQCLVDS_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    ScalerTimerDelayXms(200);

    ScalerQCFPGAContent(&ucResult);

#endif // End of #if(_DSPC_FPGA_TEST == _ENABLE)

    ScalerSetByte(P10_1C_PIN_SHARE_CTRL54, ucSCL); // Pin164 SCL (Push-pull)
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57, ucSDA); // Pin167 SDA (Push-pull)

    // Switch to eDPTX output
    PCB_SET_LVDS_DPTX_SWITCH(_DPTX_PANEL_OUTPUT);

    if(ucResult == _TEST_PASS)
    {
        DebugMessageQC("6. Display Conversion PASS", ucResult);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Display Conversion FAIL", ucResult);
        return _TEST_FAIL;
    }
}
#endif // End of #if(_PCB_TYPE == _RL6432_QA_B_1A1H4MHL1DP_DPTX_LVDS_eDP)
#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)
