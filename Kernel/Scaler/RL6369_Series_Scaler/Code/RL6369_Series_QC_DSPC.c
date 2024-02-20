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
// ID Code      : RL6369_Series_QC_DSPC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6369_SERIES_QC_DSPC__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

#if(_PCB_TYPE == _RL6369_QA_1A2MHL1DP)

#define _SIMPLE                                 0
#define _COMPLEX                                1

#define _DSPC_FPGA_CONTENT                      _COMPLEX
#define _DSPC_FPGA_TEST                         _DISABLE

//--------------------------------------------------
// Macro of FPGA IIC
//--------------------------------------------------
#define bSWIIC_FPGA_SCL                         (P3_1) // Pin43, P3.1
#define bSWIIC_FPGA_SDA                         (P3_0) // Pin42, P3.0

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
// Software Reset Whole Chip (0x0001[0])
//////////////////////////////////////////
/*
4, _NON_AUTOINC, 0x9F, 0x00,   // Page 00
4, _NON_AUTOINC, 0x01, 0x01,
//DELAY(20)
4, _NON_AUTOINC, 0x01, 0x00,
*/
////////////////////////////////
// RL6369 LVDS DC0 CP Pattern //
////////////////////////////////

//////////////////////////////////////////
// Enable ADC Bandgap (0x00C6[3])
//////////////////////////////////////////

4, _NON_AUTOINC, 0x9F, 0x00,   // Page 00
4, _NON_AUTOINC, 0xC6, 0x08,

//////////////////////////////////////////
// Enable GDI Bandgap (0x0BB4[7])
//////////////////////////////////////////

4, _NON_AUTOINC, 0x9F, 0x0B,   // Page 0B
4, _NON_AUTOINC, 0xB4, 0xA0,  // Enable GDI Bandgap & Set GDI bandgap ouput voltage to 1.21V

//*************************************************************************
// End Define Setting
//*************************************************************************

// Power on LVDS Analog
4, _NON_AUTOINC, 0x9F, 0x15,  // Page 15
4, _NON_AUTOINC, 0x00, 0xE0,  // [7] LVDS IBGen [6] LVDS Port A Power [5] LVDS Port B Power

//*************************************************************************
//  Pll Parameters Setting
//  Vref = Crystal = 14.318M
//  Target Clock = 340M
//  Target Clock = 336.473M = 14.318M * 47 / 2
//*************************************************************************

//---------PLL VCO Setting---------
4,    _AUTOINC,    0x9F,    0x01,     // page 1 (PLL)

// DPLL Reset
4,    _AUTOINC,    0xC2,    0x19,     // DPLL Power down
4,    _AUTOINC,    0xBF,    0x00,     // Reset M code
4,    _AUTOINC,    0xC0,    0x00,     // Reset N code
4,    _AUTOINC,    0xC3,    0xA1,     // VCOMD=2'b10, DPLL Bypass Calibration
4,    _AUTOINC,    0xCA,    0x01,     // [2] test enable "[0]: 1 => Enable DDS Spread Spectrum output function"

//---------DPLL Setting---------
4,    _AUTOINC,    0xC3,    0x61,     // Set VCOMD=2'b10, Auto Calibration
4,    _AUTOINC,    0xBF,    0x2D,     // M = 0x2D, DPM = 45, VCO: 340MHz
4,    _AUTOINC,    0xC0,    0x00,     // N = 00 => div 2, O_code = 0 => div 1
4,    _AUTOINC,    0xC1,    0x7C,     // [7:5] loop filter resiter  [4:3] capacitor  [3:0] charger pump current
4,    _AUTOINC,    0xDA,    0x00,     // [1:0] pixel clk divider
4,    _AUTOINC,    0xC2,    0x08,     // DPLL Power ON


//*************************************************************************
//  LVDS Digital Parameters Setting
//  LVDS Output Port: 4 Port LVDS (i.e: E~H Port copy A~D Port)
//  LVDS Clock = 84.118M = 336.473M / 4
//  LVDS Output Resolution: 10bit LVDS
//  LVDS Bitmap Reverse: Enable
//*************************************************************************

//---------Display Conversion-------------
4, _NON_AUTOINC, 0x9F, 0x39,  // page 39 (Display Conversion)
4, _NON_AUTOINC, 0x00, 0x01,  // LVDS mode
4, _NON_AUTOINC, 0x01, 0x4C,
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
4, _AUTOINC,     0x2B, 0x00,        // DCLK Polarity not inverted

//---------Fixed Last Line for Free Run Mode---------
4, _NON_AUTOINC, 0x2A, 0x30,
7, _NON_AUTOINC, 0x2B, 0x04, 0x0A, 0x04, 0x64,

//---------Free Run Mode---------
4,    _AUTOINC,       0x28,    0x83,       // Free Run Mode, Force Enable


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
//  LVDS Output Port: 8 Port LVDS Power (i.e: E~H Port copy A~D Port)
//  LVDS BW Setting
//*************************************************************************

//---------Power on LVDS Power---------
4, _NON_AUTOINC, 0x9F, 0x15,  // Page 15 (AB Port)
4, _NON_AUTOINC, 0x00, 0xE0,  // [7] LVDS IBGen [6] LVDS Port A Power [5] LVDS Port B Power
4, _NON_AUTOINC, 0x01, 0x6B,
4, _NON_AUTOINC, 0x02, 0x03,
4, _NON_AUTOINC, 0x03, 0x65,
4, _NON_AUTOINC, 0x0D, 0xAB,
4, _NON_AUTOINC, 0x0E, 0xFD,
4, _NON_AUTOINC, 0x21, 0x80,
4, _NON_AUTOINC, 0x26, 0x00,
4, _NON_AUTOINC, 0x31, 0x80,
4, _NON_AUTOINC, 0x36, 0x00,

//---------Power on LVDS Power and PLL---------
4, _NON_AUTOINC, 0x9F, 0x15,  // Page 15 (AB Port)
4, _NON_AUTOINC, 0x00, 0xF8,  // [7] LVDS IBGen [6] LVDS Port A Power [5] LVDS Port B Power [4] LVDS PLL LDO [3] LVDS PLL Power

// Start Pair CRC
4,    _AUTOINC,       0x9F,    0x39,
4,    _AUTOINC,       0x30,    0x08,  // Start LVDS CRC
};

BYTE code tQCLVDS_QA_ENVIRONMENT[] =
{
//---------Display Conversion CRC Start-------------
4, _NON_AUTOINC, 0x30, 0x08,

//*************************************************************************
//  LVDS Analog Parameters Setting
//  LVDS Trace Skew Correction
//*************************************************************************

//---------LVDS Phase Interpolation---------
4, _NON_AUTOINC, 0x9F, 0x15,  // Page 15 (AB Port)
4, _NON_AUTOINC, 0x07, 0x6E,  // CK7X_PI1: 5-PI
4, _NON_AUTOINC, 0x24, 0x05,  // TXO0/TXO1     : CK7X_PI1
4, _NON_AUTOINC, 0x25, 0x45,  // TXO2/TXO3/TXO4: CK7X_PI1
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

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

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
// Description  : Send the data to FPGA_I's register
// Input Value  : ucValue  --> The data of FPGA_I's register where you want to write
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
// Description  : The address of the FPGA_I's register
// Input Value  : ucAddr      --> Start address of register
//                bReadWrite  --> Setting the read/write command to FPGA_I
//                bAutoInc    --> Setting the auto/non-auto increase command to FPGA_I
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
// Description  : Stop reading the FPGA_I's register
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
// Description  : Stop writting the FPGA_I's register
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
// Description  : Write a data array into registers of scaler (FPGA_I)
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
// Description  : Get the data of FPGA_I's register
// Input Value  : None
// Output Value : Data of FPGA_I's register
//--------------------------------------------------
BYTE ScalerQCFPGAGetByte(void)
{
    BYTE ucValue = 0;
    BYTE ucChk = 0;

    ScalerSetByte(P10_08_PIN_SHARE_CTRL30, 0x00); // Page 10-08 Pin 42

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

    ScalerSetByte(P10_08_PIN_SHARE_CTRL30, 0x01); // Page 10-21 Pin H29
    return ucValue;
}

//--------------------------------------------------
// Description  : Read data from registers of scaler and put it into an reading data array (FPGA_I)
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
// Description  : FPGA_I for LVDS configuration setting
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
// Description  : The content of FPGA's setting
// Input Value  : check  --> checking the FPGA_I's register
// Output Value : None
//--------------------------------------------------
void ScalerQCFPGAContent(BYTE *pucPass)
{
    BYTE ucCheck[24];
    BYTE ucScalerCRC[24];
    BYTE ucLVDSTxPort[2];

    ScalerQCFPGARead(0xFC, &ucCheck[0]);
    ScalerQCFPGARead(0xFD, &ucCheck[1]);
    ScalerQCFPGARead(0xFE, &ucCheck[2]);
    ScalerQCFPGARead(0xFF, &ucCheck[3]);

    if((ucCheck[0] == 0x20) && (ucCheck[1] == 0x14) && (ucCheck[2] == 0x09) && (ucCheck[3] == 0x05))
    {
        ScalerRead(P39_31_D_CONV_CRC_0_H, 24, &ucScalerCRC, _AUTOINC);

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
        ScalerQCFPGARead(0x8B, &ucCheck[10]);   // TXE4 H
        ScalerQCFPGARead(0x8C, &ucCheck[11]);   // TXE4 L
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
        ScalerQCFPGARead(0x97, &ucCheck[22]);   // TXO4 H
        ScalerQCFPGARead(0x98, &ucCheck[23]);   // TXO4 L

        if((ucCheck[0] == ucScalerCRC[0]) && (ucCheck[1] == ucScalerCRC[1]) && (ucCheck[2] == ucScalerCRC[2]) && (ucCheck[3] == ucScalerCRC[3]) && (ucCheck[4] == ucScalerCRC[4]) && (ucCheck[5] == ucScalerCRC[5]) &&
           (ucCheck[8] == ucScalerCRC[8]) && (ucCheck[9] == ucScalerCRC[9]) && (ucCheck[10] == ucScalerCRC[10]) && (ucCheck[11] == ucScalerCRC[11]))
        {
            ucLVDSTxPort[0] = _TEST_PASS;
            DebugMessageQC("5. //----LVDS TXE Pass----//", 0x00);
        }
        else
        {
            ucLVDSTxPort[0] = _TEST_FAIL;

#if(_DSPC_FPGA_CONTENT == _SIMPLE)

            DebugMessageQC("5. //----LVDS TXE Fail----//", 0x00);

#elif(_DSPC_FPGA_CONTENT == _COMPLEX)

            DebugMessageQC("5. //----LVDS TXE Fail Start----//", 0x00);

            if((ucCheck[0] != ucScalerCRC[0]) || (ucCheck[1] != ucScalerCRC[1]))
            {
                DebugMessageQC("5. LVDS TXE0 Fail", 0x00);
            }

            if((ucCheck[2] != ucScalerCRC[2]) || (ucCheck[3] != ucScalerCRC[3]))
            {
                DebugMessageQC("5. LVDS TXE1 Fail", 0x00);
            }

            if((ucCheck[4] != ucScalerCRC[4]) || (ucCheck[5] != ucScalerCRC[5]))
            {
                DebugMessageQC("5. LVDS TXE2 Fail", 0x00);
            }

            if((ucCheck[8] != ucScalerCRC[8]) || (ucCheck[9] != ucScalerCRC[9]))
            {
                DebugMessageQC("5. LVDS TXE3 Fail", 0x00);
            }

            if((ucCheck[10] != ucScalerCRC[10]) || (ucCheck[11] != ucScalerCRC[11]))
            {
                DebugMessageQC("5. LVDS TXE4 Fail", 0x00);
            }

            DebugMessageQC("5. //----LVDS TXE Fail End----//", 0x00);
#endif
        }

        if((ucCheck[12] == ucScalerCRC[12]) && (ucCheck[13] == ucScalerCRC[13]) && (ucCheck[14] == ucScalerCRC[14]) && (ucCheck[15] == ucScalerCRC[15]) && (ucCheck[16] == ucScalerCRC[16]) && (ucCheck[17] == ucScalerCRC[17]) &&
           (ucCheck[20] == ucScalerCRC[20]) && (ucCheck[21] == ucScalerCRC[21]) && (ucCheck[22] == ucScalerCRC[22]) && (ucCheck[23] == ucScalerCRC[23]))
        {
            ucLVDSTxPort[1] = _TEST_PASS;
            DebugMessageQC("5. //----LVDS TXO Pass----//", 0x00);
        }
        else
        {
            ucLVDSTxPort[1] = _TEST_FAIL;

#if(_DSPC_FPGA_CONTENT == _SIMPLE)

            DebugMessageQC("5. //----LVDS TXO Fail----//", 0x00);

#elif(_DSPC_FPGA_CONTENT == _COMPLEX)

            DebugMessageQC("5. //----LVDS TXO Fail Strat----//", 0x00);

            if((ucCheck[12] != ucScalerCRC[12]) || (ucCheck[13] != ucScalerCRC[13]))
            {
                DebugMessageQC("5. LVDS TXO0 Fail", 0x00);
            }

            if((ucCheck[14] != ucScalerCRC[14]) || (ucCheck[15] != ucScalerCRC[15]))
            {
                DebugMessageQC("5. LVDS TXO1 Fail", 0x00);
            }

            if((ucCheck[16] != ucScalerCRC[16]) || (ucCheck[17] != ucScalerCRC[17]))
            {
                DebugMessageQC("5. LVDS TXO2 Fail", 0x00);
            }

            if((ucCheck[20] != ucScalerCRC[20]) || (ucCheck[21] != ucScalerCRC[21]))
            {
                DebugMessageQC("5. LVDS TXO3 Fail", 0x00);
            }

            if((ucCheck[22] != ucScalerCRC[22]) || (ucCheck[23] != ucScalerCRC[23]))
            {
                DebugMessageQC("5. LVDS TXO4 Fail", 0x00);
            }

            DebugMessageQC("5. //----LVDS TXO Fail End----//", 0x00);
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
    BYTE test = 0;

    DebugMessageQC("5. DSPC test Start", 0x00);
/*
    // Whole chip reset
    ScalerSetBit(P0_01_HOST_CTRL, ~_BIT0, _BIT0);

    // For Delay 10 ms
    ScalerTimerDelayXms(10);

    // Clear to 0
    ScalerSetBit(P0_01_HOST_CTRL, ~_BIT0, 0x00);
*/
    // Group A power block power cut off
    if((ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT4) == _BIT4) || (ScalerGetBit(P0_09_TOP_POWER_CTRL, _BIT1) == _BIT1))
    {
        // Group A Power Cut block Reset
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT0, _BIT0);

        // Weak power on
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT4, _BIT4);

        // Wait for weak power on flag
        pData[0] = 200;

        while((ScalerGetBit(P0_09_TOP_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0));

        // Strong power on
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT5, _BIT5);

        // Wait for strong power on flag
        pData[0] = 200;

        while((ScalerGetBit(P0_09_TOP_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0));

        // Group A power block power isolation off
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT1, 0x00);
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT4, 0x00);

        // Group A Power Cut block Relase
        ScalerSetBit(P0_09_TOP_POWER_CTRL, ~_BIT0, 0x00);
    }

    ScalerSetByte(P10_08_PIN_SHARE_CTRL30, 0x01); // Pin42 SDA (Push-pull)
    ScalerSetByte(P10_09_PIN_SHARE_CTRL31, 0x01); // Pin43 SCL (Push-pull)
    ScalerSetBit(P10_0F_PIN_SHARE_CTRL37, ~_BIT5, 0x00); // Set DDC pin mux swap normal
    ScalerTimerDelayXms(2);

#if(_DSPC_FPGA_TEST == _ENABLE)
    while(1)
    {
        //------LVDS 2_Port 85MHz------//
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
    //------LVDS 2_Port 85MHz------//
    ScalerBurstWrite(tQCLVDS_FT, sizeof(tQCLVDS_FT), GET_CURRENT_BANK_NUMBER(), 0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    ScalerTimerDelayXms(200);

    ScalerQCFPGAContent(&ucResult);

#endif // End of #if(_DSPC_FPGA_TEST == _ENABLE)

    if(ucResult == _TEST_PASS)
    {
        DebugMessageQC("6. Display Conversion PASS", ucResult);
        DebugMessageQC("5. DSPC test End", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Display Conversion FAIL", ucResult);
        DebugMessageQC("5. DSPC test End", 0x00);
        return _TEST_FAIL;
    }
}
#endif // End of #if(_PCB_TYPE == _RL6369_QA_1A2MHL1DP_LVDS)
#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)

