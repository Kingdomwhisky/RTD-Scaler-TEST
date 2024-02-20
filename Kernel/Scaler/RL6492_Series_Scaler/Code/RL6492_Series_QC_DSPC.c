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
// ID Code      : RL6492_Series_QC_DSPC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_QC_DSPC__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

#if(_PCB_TYPE == _RL6492_QA_156PIN_1A1H1TC1DP_LVDS_eDP)

#define _SIMPLE                                 0
#define _COMPLEX                                1

#define _DSPC_FPGA_CONTENT                      _COMPLEX
#define _DSPC_FPGA_TEST                         _DISABLE   // Jeyu_test
#define _DPSC_CRC_NUM                           22

// edptx start
#define pin36                                   (P1_7)
BYTE GPIO_RESULT = 0x00;
BYTE GPIO_RESULT_VBY1_A = 0x00;
BYTE GPIO_RESULT_VBY1_B = 0x00;
// edptx end

//--------------------------------------------------
// Macro of FPGA IIC
//--------------------------------------------------
#define bSWIIC_FPGA_SCL                         (_PIN_38_MCU_REG) // Pin38, P4.7
#define bSWIIC_FPGA_SDA                         (_PIN_37_MCU_REG) // Pin37, P4.6

#define FPGA_SW_IIC_SDA_SET()                   {\
                                                    bSWIIC_FPGA_SDA = _TRUE;                                                         \
}

#define FPGA_SW_IIC_SDA_CLR()                   {\
                                                    bSWIIC_FPGA_SDA = _FALSE;                                                        \
}

#define FPGA_SW_IIC_SDA_CHK(x)                  {\
                                                    x = bSWIIC_FPGA_SDA;                                                             \
}

#define FPGA_SW_IIC_SCL_SET()                   {\
                                                    bSWIIC_FPGA_SCL = _TRUE;                                                         \
}

#define FPGA_SW_IIC_SCL_CLR()                   {\
                                                    bSWIIC_FPGA_SCL = _FALSE;                                                        \
}

#define FPGA_SW_IIC_SCL_CHK(x)                  {\
                                                    x = bSWIIC_FPGA_SCL;                                                             \
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
4, _NON_AUTOINC, 0x20, 0x04,
4, _NON_AUTOINC, 0x21, 0x04,
4, _NON_AUTOINC, 0x22, 0x04,
4, _NON_AUTOINC, 0x23, 0x04,
4, _NON_AUTOINC, 0x24, 0x04,
4, _NON_AUTOINC, 0x25, 0x04,
4, _NON_AUTOINC, 0x26, 0x04,
4, _NON_AUTOINC, 0x27, 0x04,
4, _NON_AUTOINC, 0x28, 0x04,
4, _NON_AUTOINC, 0x29, 0x04,

//*************************************************************************
//  Pll Parameters Setting
//  Vref = Crystal = 14.318M
//  Target Clock = 170M
//*************************************************************************

//---------PLL VCO Setting---------
4,    _NON_AUTOINC,    0x9F,    0x01,     // page 1 (PLL)

//---------DPLL Reset---------
4,    _NON_AUTOINC,    0xD2,    0x22,     // Disable LDO
4,    _NON_AUTOINC,    0xD1,    0x01,     // DPLL Power down
4,    _NON_AUTOINC,    0xC1,    0x20,     // Reset N Code[3:0], F Code[19:16]
4,    _NON_AUTOINC,    0xC2,    0x00,     // Reset F Code[15:8]
4,    _NON_AUTOINC,    0xC3,    0x00,     // Reset F Code[7:0]
4,    _NON_AUTOINC,    0xC0,    0x82,     // Reset N Code[7:4]

//---------DPLL Setting---------
4,    _NON_AUTOINC,    0xD0,    0x18,     // VCO Band
4,    _NON_AUTOINC,    0xD3,    0x4B,     // Icp, Rp
4,    _NON_AUTOINC,    0xD2,    0x42,     // PI Control
4,    _NON_AUTOINC,    0xD1,    0x00,     // Power On
4,    _NON_AUTOINC,    0xD2,    0x46,     // Enable LDO
4,    _NON_AUTOINC,    0xBF,    0x18,     // VCO Div2

4,    _NON_AUTOINC,    0xC1,    0x5B,     // Set N Code[3:0], F Code[19:16]
4,    _NON_AUTOINC,    0xC2,    0xF0,     // Set F Code[15:8]
4,    _NON_AUTOINC,    0xC3,    0xFB,     // Set F Code[7:0]
4,    _NON_AUTOINC,    0xC0,    0xA1,     // Set N Code[7:4] and N.F Code Double Buffer


//*************************************************************************
//  LVDS Digital Parameters Setting
//  LVDS Output Port: 2 Port LVDS
//  LVDS Clock = 85M = 170M / 2
//  LVDS Output Resolution: 8bit LVDS
//  LVDS Bitmap Reverse: Enable
//*************************************************************************

//---------Display Conversion-------------
4, _NON_AUTOINC, 0x9F, 0x39,  // page 39 (Display Conversion)
4, _NON_AUTOINC, 0x00, 0x01,  // LVDS mode
4, _NON_AUTOINC, 0x01, 0x42,  // 2Port LVDS, 8bit
4, _NON_AUTOINC, 0x06, 0x08,


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
5, _NON_AUTOINC, 0x2B, 0x00, 0x28,  // Hori bkg start = 40
4, _AUTOINC,     0x2A, 0x05,
5, _NON_AUTOINC, 0x2B, 0x00, 0x28,  // Hori act start = 40
4, _AUTOINC,     0x2A, 0x07,
5, _NON_AUTOINC, 0x2B, 0x04, 0x28,  // Hori act end = 1064
4, _AUTOINC,     0x2A, 0x09,
5, _NON_AUTOINC, 0x2B, 0x04, 0x28,  // Hori bkg end = 1064
4, _AUTOINC,     0x2A, 0x0B,
5, _NON_AUTOINC, 0x2B, 0x04, 0x0A,  // DVTotal = 1034
4, _AUTOINC,     0x2A, 0x0D,
4, _NON_AUTOINC, 0x2B, 0x03,        // Vs End = 3
4, _AUTOINC,     0x2A, 0x0E,
5, _NON_AUTOINC, 0x2B, 0x00, 0x06,  // Vert bkg start = 6
4, _AUTOINC,     0x2A, 0x10,
5, _NON_AUTOINC, 0x2B, 0x00, 0x06,  // Vert act start = 6
4, _AUTOINC,     0x2A, 0x12,
5, _NON_AUTOINC, 0x2B, 0x04, 0x06,  // Vert act end = 1030
4, _AUTOINC,     0x2A, 0x14,
5, _NON_AUTOINC, 0x2B, 0x04, 0x06,  // Vert bkg end = 1030

4, _AUTOINC,     0x2A, 0x20,
4, _AUTOINC,     0x2B, 0x00,        // DCLK Polarity Non-inverted

//---------Fixed Last Line for Free Run Mode---------
4, _NON_AUTOINC, 0x2A, 0x30,
7, _NON_AUTOINC, 0x2B, 0x04, 0x0A, 0x04, 0x64,

//---------Free Run Mode---------
4, _NON_AUTOINC, 0x28, 0x83,        // Free Run Mode, Force Enable


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


//*************************************************************************
//  LVDS Analog Parameters Setting
//  LVDS Output Port: 2 Port LVDS Power
//  LVDS BW Setting
//*************************************************************************

//---------Power on LVDS Power---------
4, _NON_AUTOINC, 0x9F, 0x55,  // Page 55 (AB Port)
4, _NON_AUTOINC, 0x00, 0xE0,  // [7] LVDS IBGen [6] LVDS Port A Power [5] LVDS Port B Power
4, _NON_AUTOINC, 0x01, 0x6A,
4, _NON_AUTOINC, 0x02, 0x02,
4, _NON_AUTOINC, 0x03, 0x65,  // [4] CK_PIXEL: Falling Edge
4, _NON_AUTOINC, 0x0D, 0xAB,
4, _NON_AUTOINC, 0x0E, 0xFD,
4, _NON_AUTOINC, 0x0F, 0x04,  // VCO = 1.5~3 GHz, Phy range = 375~750 MHz, Freq_band = div4
4, _NON_AUTOINC, 0x21, 0x80,
4, _NON_AUTOINC, 0x26, 0x00,
4, _NON_AUTOINC, 0x30, 0x08,  // TXAC current 2x
4, _NON_AUTOINC, 0x31, 0x80,
4, _NON_AUTOINC, 0x36, 0x00,

//---------Power on LVDS Power and PLL---------
4, _NON_AUTOINC, 0x9F, 0x55,  // Page 55 (AB Port)
4, _NON_AUTOINC, 0x00, 0xE8,  // [7] LVDS IBGen [6] LVDS Port A Power [5] LVDS Port B Power [3] LVDS PLL Power

// Start Pair CRC
4,	_AUTOINC,	   0x9F,	0x39,
4,	_AUTOINC,	   0x30,	0x08,  // Start LVDS CRC
};

BYTE code tQCLVDS_QA_ENVIRONMENT[] =
{
//*************************************************************************
//  LVDS Digital Parameters For QA Environment Setting
//  LVDS PN Swap
//  LVDS Port Swap
//*************************************************************************

//---------Display Conversion-------------
4, _NON_AUTOINC, 0x9F, 0x39,  // page 39 (Display Conversion)
4, _NON_AUTOINC, 0x02, 0x01,
//4, _NON_AUTOINC, 0x06, 0x18,
4, _NON_AUTOINC, 0x30, 0x08,


//*************************************************************************
//  LVDS Analog Parameters Setting
//  LVDS Trace Skew Correction
//*************************************************************************

//---------LVDS Phase Interpolation---------
4, _NON_AUTOINC, 0x9F, 0x55,  // Page 55 (CD Port)
4, _NON_AUTOINC, 0x07, 0x37,  // CK7X_PI1: 3-PI
4, _NON_AUTOINC, 0x24, 0x05,  // TXA0/TXA1: CK7X_PI1
4, _NON_AUTOINC, 0x25, 0x44,  // TXA2/TXA3: CK7X_PI1
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

    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON1, 0x00); // Pin37

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

    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON1, 0x01); // Pin37

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

    ScalerQCFPGASetByte(0x00, 0x1C);
    ScalerQCFPGASetByte(0x10, 0x11);
    ScalerQCFPGASetByte(0x0F, 0xC6);
    ScalerQCFPGASetByte(0x20, 0x11);
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
    BYTE ucLVDSTxPort[2];

    ScalerQCFPGARead(0xFC, &ucCheck[0]);
    ScalerQCFPGARead(0xFD, &ucCheck[1]);
    ScalerQCFPGARead(0xFE, &ucCheck[2]);
    ScalerQCFPGARead(0xFF, &ucCheck[3]);

    if((ucCheck[0] == 0x20) && (ucCheck[1] == 0x14) && (ucCheck[2] == 0x09) && (ucCheck[3] == 0x05))
    {
        ScalerRead(P39_31_D_CONV_CRC_0_H, _DPSC_CRC_NUM, &ucScalerCRC, _AUTOINC);

        //------LVDS QA Environment Setting------//
        ScalerBurstWrite(tQCLVDS_QA_ENVIRONMENT, sizeof(tQCLVDS_QA_ENVIRONMENT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        //------Reset FPGA Setting------//
        ScalerQCFPGATable();

        ScalerTimerDelayXms(200);

        ScalerQCFPGARead(0x81, &ucCheck[0]);    // TXE0 H
        ScalerQCFPGARead(0x82, &ucCheck[1]);    // TXE0 L
        ScalerQCFPGARead(0x83, &ucCheck[2]);    // TXE1 H
        ScalerQCFPGARead(0x84, &ucCheck[3]);    // TXE1 L
        ScalerQCFPGARead(0x85, &ucCheck[4]);    // TXE2 H
        ScalerQCFPGARead(0x86, &ucCheck[5]);    // TXE2 L
        ScalerQCFPGARead(0x87, &ucCheck[6]);    // TXECk H Ignore
        ScalerQCFPGARead(0x88, &ucCheck[7]);    // TXECk L Ignore
        ScalerQCFPGARead(0x89, &ucCheck[8]);    // TXE3 H
        ScalerQCFPGARead(0x8A, &ucCheck[9]);    // TXE3 L
        ScalerQCFPGARead(0x8B, &ucCheck[10]);   // TXE4 H (x)
        ScalerQCFPGARead(0x8C, &ucCheck[11]);   // TXE4 L (x)
        ScalerQCFPGARead(0x8D, &ucCheck[12]);   // TXO0 H
        ScalerQCFPGARead(0x8E, &ucCheck[13]);   // TXO0 L
        ScalerQCFPGARead(0x8F, &ucCheck[14]);   // TXO1 H
        ScalerQCFPGARead(0x90, &ucCheck[15]);   // TXO1 L
        ScalerQCFPGARead(0x91, &ucCheck[16]);   // TXO2 H
        ScalerQCFPGARead(0x92, &ucCheck[17]);   // TXO2 L
        ScalerQCFPGARead(0x93, &ucCheck[18]);   // TXOCk H Ignore
        ScalerQCFPGARead(0x94, &ucCheck[19]);   // TXOCk L Ignore
        ScalerQCFPGARead(0x95, &ucCheck[20]);   // TXO3 H
        ScalerQCFPGARead(0x96, &ucCheck[21]);   // TXO3 L

        if((ucCheck[0] == ucScalerCRC[0]) && (ucCheck[1] == ucScalerCRC[1]) && (ucCheck[2] == ucScalerCRC[2]) && (ucCheck[3] == ucScalerCRC[3]) &&
           (ucCheck[4] == ucScalerCRC[4]) && (ucCheck[5] == ucScalerCRC[5]) && (ucCheck[8] == ucScalerCRC[8]) && (ucCheck[9] == ucScalerCRC[9]))
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

            if((ucCheck[0] != ucScalerCRC[0]) || (ucCheck[1] != ucScalerCRC[1]))
            {
                DebugMessageQC("5. LVDS TXA0 Fail", 0x00);
            }

            if((ucCheck[2] != ucScalerCRC[2]) || (ucCheck[3] != ucScalerCRC[3]))
            {
                DebugMessageQC("5. LVDS TXA1 Fail", 0x00);
            }

            if((ucCheck[4] != ucScalerCRC[4]) || (ucCheck[5] != ucScalerCRC[5]))
            {
                DebugMessageQC("5. LVDS TXA2 Fail", 0x00);
            }

            if((ucCheck[8] != ucScalerCRC[8]) || (ucCheck[9] != ucScalerCRC[9]))
            {
                DebugMessageQC("5. LVDS TXA3 Fail", 0x00);
            }

            DebugMessageQC("5. //----LVDS TXA Fail End----//", 0x00);
#endif
        }

        if((ucCheck[12] == ucScalerCRC[12]) && (ucCheck[13] == ucScalerCRC[13]) && (ucCheck[14] == ucScalerCRC[14]) && (ucCheck[15] == ucScalerCRC[15]) &&
           (ucCheck[16] == ucScalerCRC[16]) && (ucCheck[17] == ucScalerCRC[17]) && (ucCheck[20] == ucScalerCRC[20]) && (ucCheck[21] == ucScalerCRC[21]))
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

            if((ucCheck[12] != ucScalerCRC[12]) || (ucCheck[13] != ucScalerCRC[13]))
            {
                DebugMessageQC("5. LVDS TXB0 Fail", 0x00);
            }

            if((ucCheck[14] != ucScalerCRC[14]) || (ucCheck[15] != ucScalerCRC[15]))
            {
                DebugMessageQC("5. LVDS TXB1 Fail", 0x00);
            }

            if((ucCheck[16] != ucScalerCRC[16]) || (ucCheck[17] != ucScalerCRC[17]))
            {
                DebugMessageQC("5. LVDS TXB2 Fail", 0x00);
            }

            if((ucCheck[20] != ucScalerCRC[20]) || (ucCheck[21] != ucScalerCRC[21]))
            {
                DebugMessageQC("5. LVDS TXB3 Fail", 0x00);
            }

            DebugMessageQC("5. //----LVDS TXB Fail End----//", 0x00);
#endif
        }

        if((ucLVDSTxPort[0] == _TEST_PASS) && (ucLVDSTxPort[1] == _TEST_PASS))
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

    // Switch to LVDS output
    PCB_SET_LVDS_DPTX_SWITCH(_LVDS_PANEL_OUTPUT);

    ucSCL = ScalerGetByte(P10_17_PIN_SHARE_CTRL17__ON1); // Pin38
    ucSDA = ScalerGetByte(P10_16_PIN_SHARE_CTRL16__ON1); // Pin37

    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON1, 0x01); // Pin37 SCL (Push-pull)
    ScalerSetByte(P10_17_PIN_SHARE_CTRL17__ON1, 0x01); // Pin38 SDA (Push-pull)

    ScalerTimerDelayXms(2);

#if(_DSPC_FPGA_TEST == _ENABLE)
    while(1)
    {
        //------LVDS 2_Port 85MHz------//
        ScalerBurstWrite(tQCLVDS_FT, sizeof(tQCLVDS_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        ScalerTimerDelayXms(100);

        ScalerQCFPGAContent(&ucResult);

        while(test < 250)
        {
            ScalerDebug();

            test += 1;
        }
        test = 0;
    }

#else
    //------LVDS 2_Port 85MHz------//
    ScalerBurstWrite(tQCLVDS_FT, sizeof(tQCLVDS_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    ScalerTimerDelayXms(100);

    ScalerQCFPGAContent(&ucResult);

#endif // End of #if(_DSPC_FPGA_TEST == _ENABLE)

    ScalerSetByte(P10_17_PIN_SHARE_CTRL17__ON1, ucSCL); // Pin38 SCL (Push-pull)
    ScalerSetByte(P10_16_PIN_SHARE_CTRL16__ON1, ucSDA); // Pin37 SDA (Push-pull)

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

//************************************************//
//--------------------------------------------------
// Description  : QC eDP Tx Test
// Input Value  : None
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCeDPTXTest(void)
{
    BYTE ucResult0 = 0x00;

    // Switch to eDPTX output
    PCB_SET_LVDS_DPTX_SWITCH(_DPTX_PANEL_OUTPUT);

    // Set Video Stream parameter
    ScalerDisplayDPTx1VideoStreamOutput(_ENABLE);

    ScalerSetByte(P6_C0_REG_DAC_POWER0, 0x00);
    ScalerSetByte(P6_C1_REG_DAC_POWER1, 0x00);

    ScalerSetByte(P10_2A_PIN_SHARE_CTRL2A__ON1, 0x01);   //Pin36 Push-Pull  --Pin69
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL2B__ON1, 0x00);   //Pin37 GPI        --Pin70
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL2D__ON1, 0x01);   //Pin38 Push-Pull  --Pin72
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL2E__ON1, 0x00);   //Pin42 GPI        --Pin73
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL2F__ON1, 0x01);   //Pin43 Push-Pull  --Pin74
    ScalerSetByte(P10_30_PIN_SHARE_CTRL30__ON1, 0x01);   //Pin44 Push-Pull  --PIn75

    // switch
    //ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__ON1, 0x01);   //P4.3  Test DPTX Connector
    //MCU_FE0C_PORT54_PIN_REG = 1;    //p4.3

    ScalerSetByte(P10_1C_PIN_SHARE_CTRL1C__ON1, 0x01);   //P4.3  Test DPTX eQC
    MCU_FE0C_PORT54_PIN_REG = 0;    //p4.3


    ScalerSetByte(P10_1D_PIN_SHARE_CTRL1D__ON1, 0x01);   //P4.4
    MCU_FE0D_PORT55_PIN_REG= 1;    //p4.4


    ScalerBurstWrite(tQCLVDS_EDPTX_HBR_FT, sizeof(tQCLVDS_EDPTX_HBR_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    // For DP HBR2
    MCU_FE1A_PORT72_PIN_REG = 1;    //PIN36
    MCU_FE1D_PORT75_PIN_REG = 0;    //PIN38

    ScalerTimerDelayXms(10);

    // For DP TX TEST
    MCU_FE1F_PORT77_PIN_REG = 0;    //Pin43
    MCU_FE20_PORT80_PIN_REG = 1;    //Pin44

    // For DP HBR
    MCU_FE1A_PORT72_PIN_REG = 0;    //PIN36
    MCU_FE1D_PORT75_PIN_REG = 1;    //PIN38

    ScalerTimerDelayXms(100);

    GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE1B_PORT73_PIN_REG) << 1) | ((BYTE)(MCU_FE1E_PORT76_PIN_REG));   // Pin37,Pin42

    DebugMessageQC("pin37", MCU_FE1B_PORT73_PIN_REG);
    DebugMessageQC("pin42", MCU_FE1E_PORT76_PIN_REG);
    DebugMessageQC("pin36 ==0", MCU_FE1A_PORT72_PIN_REG);
    DebugMessageQC("pin38 ==1", MCU_FE1D_PORT75_PIN_REG);

    DebugMessageQC("pin43 ==0", MCU_FE1F_PORT77_PIN_REG);
    DebugMessageQC("pin44 ==1", MCU_FE20_PORT80_PIN_REG);


    if(GET_GPIO_RESULT() == 0x00)
    {
        DebugMessageQC("5. LVDS_Combo_DP HBR: PASS 1", 0);

    }
    else
    {
        DebugMessageQC("5. LVDS_Combo_DP HBR: TEST 2", 0);

        // For DP HBR2
        MCU_FE1A_PORT72_PIN_REG = 1;    //PIN36
        MCU_FE1D_PORT75_PIN_REG = 0;    //PIN38

        ScalerTimerDelayXms(10);

        ScalerBurstWrite(tQCLVDS_EDPTX_HBR_FT, sizeof(tQCLVDS_EDPTX_HBR_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        // For DP HBR
        MCU_FE1A_PORT72_PIN_REG = 0;    //PIN36
        MCU_FE1D_PORT75_PIN_REG = 1;    //PIN38

        ScalerTimerDelayXms(100);

        GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE1B_PORT73_PIN_REG) << 1) | ((BYTE)(MCU_FE1E_PORT76_PIN_REG));   // Pin37,Pin42


        if(GET_GPIO_RESULT() == 0x00)
        {
            DebugMessageQC("5. LVDS_Combo_DP HBR: PASS 2", 0);

        }
        else
        {
            DebugMessageQC("6. LVDS_Combo_DP HBR: FAIL", 0);

            return _TEST_FAIL;
        }
    }

    ScalerTimerDelayXms(50);

    ScalerBurstWrite(tQCLVDS_EDPTX_RBR_FT, sizeof(tQCLVDS_EDPTX_RBR_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    // For DP TX TEST
    MCU_FE1F_PORT77_PIN_REG = 0;    //Pin43
    MCU_FE20_PORT80_PIN_REG = 1;    //Pin44

    // For DP RBR
    MCU_FE1A_PORT72_PIN_REG = 0;    //PIN36
    MCU_FE1D_PORT75_PIN_REG = 0;    //PIN38

    ScalerTimerDelayXms(100);

    GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE1B_PORT73_PIN_REG) << 1) | ((BYTE)(MCU_FE1E_PORT76_PIN_REG));   // Pin37,Pin42

    DebugMessageQC("pin37", MCU_FE1B_PORT73_PIN_REG);
    DebugMessageQC("pin42", MCU_FE1E_PORT76_PIN_REG);
    DebugMessageQC("pin36 ==0", MCU_FE1A_PORT72_PIN_REG);
    DebugMessageQC("pin38 ==0", MCU_FE1D_PORT75_PIN_REG);
    DebugMessageQC("pin43 ==0", MCU_FE1F_PORT77_PIN_REG);
    DebugMessageQC("pin44 ==1", MCU_FE20_PORT80_PIN_REG);

    if(GET_GPIO_RESULT() == 0x00)
    {
        DebugMessageQC("5. LVDS_Combo_DP RBR: PASS 1", 0);
        DebugMessageQC("6. LVDS_Combo_DP PASS ", 0);

        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("5. LVDS_Combo_DP RBR: TEST 2", 0);
        // For DP HBR
        MCU_FE1A_PORT72_PIN_REG = 0;    //PIN36
        MCU_FE1D_PORT75_PIN_REG = 1;    //PIN38

        ScalerTimerDelayXms(10);

        ScalerBurstWrite(tQCLVDS_EDPTX_RBR_FT, sizeof(tQCLVDS_EDPTX_RBR_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        // For DP RBR
        MCU_FE1A_PORT72_PIN_REG = 0;    //PIN36
        MCU_FE1D_PORT75_PIN_REG = 0;    //PIN38

        ScalerTimerDelayXms(100);

        GPIO_RESULT = 0x00  | ((BYTE)(MCU_FE1B_PORT73_PIN_REG) << 1) | ((BYTE)(MCU_FE1E_PORT76_PIN_REG));   // Pin37,Pin42

        if(GET_GPIO_RESULT() == 0x00)
        {
           DebugMessageQC("5. LVDS_Combo_DP RBR: PASS 2", 0);
           DebugMessageQC("6. LVDS_Combo_DP PASS ", 0);

           return _TEST_PASS;

        }
        else
        {
           DebugMessageQC("6. LVDS_Combo_DP RBR: FAIL", 0);

           return _TEST_FAIL;
        }

    }

    return 0;
}

#endif // End of #if(_PCB_TYPE == _RL6492_QA_156PIN_1A1H1TC1DP_LVDS_eDP)
#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)
