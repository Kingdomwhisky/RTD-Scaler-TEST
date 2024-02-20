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
// ID Code      : RL6449_Series_DDR2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// DDR2 Data Rate
//--------------------------------------------------
#define _DDR2_DATA_RATE_1066M                               1066
#define _DDR2_DATA_RATE_800M                                800
#define _DDR2_DATA_RATE_667M                                667
#define _DDR2_DATA_RATE_533M                                533

// Total num of theoretical PLL PI(combination of PI & WRLVL)
#define _TOT_THEO_PI_NUM                                    128

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
// Default DDRPLL Phase
StructDDR2PLLPI code tDDR2_PLL_PHASE[2] =
{
    // CLK,  CMD, DQS0, DQS1,  DQ0,  DQ1
    {0x3A, 0x40, 0x3A, 0x3A, 0x4C, 0x4C},
    {0x3A, 0x40, 0x3A, 0x3A, 0x4C, 0x4C}
};

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDDR2PowerControl(bit bOn);
void ScalerDDR2DCSysInitial(void);
void ScalerDDR2DCPHYInitial(void);
DWORD ScalerDDR2CalcWrlvlConfig(StructDDR2PLLPI code *pstDDR2PLLPhase);
#if(_MEMORY_SIZE_CONFIG == _16M_16BIT_DDR2_2PCS)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
void ScalerDDR2RotationSetClientMux(void);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DDR Power On/Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR2PowerControl(bit bOn)
{
    if(bOn == _ON)
    {
        // Set MPLL CLK
        ScalerPLLSetMPLLFreq((DWORD)_MEMORY_PLL_CLOCK * 1000);

        // Set DDR PLL CLK
        ScalerPLLSetDDR2PLLFreq((DWORD)_MEMORY_DATA_RATE_SPEED * 1000);

        //------------------------------
        // DC Sys Initial
        //------------------------------
        ScalerDDR2DCSysInitial();

        //------------------------------
        // DC PHY Initial
        //------------------------------
        ScalerDDR2DCPHYInitial();
    }
    else
    {
        // Disable CLK output, Reset PLL, Disable PLL
        ScalerPLLDDR2PLLOutputCtrl(_DISABLE);
        ScalerPLLDDR2PLLCtrl(_DISABLE);

        // Power down MPLL
        ScalerSetBit(P0_F8_MPLL_WD, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : DC Sys initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR2DCSysInitial(void)
{
    BYTE ucDDRSel = 0;

    for(ucDDRSel = _DDR2_DEV_SEQ_BEGIN; ucDDRSel < _DDR2_DEV_SEQ_END; ucDDRSel++)
    {
        // (_BIT1 | _BIT0): Page size selection: 00=512bytes, 01=1024bytes, 10=2048bytes, 11=4096bytes
        ScalerSetDWord(DDR2_GET_REG(P8A_04_DC_SYS_MISC3, ucDDRSel), 0x00010100);

        // Set DDR2 M1 Client Priority Counter
        // Cleint0 M1 FRC Capature
        ScalerSetDWord(DDR2_GET_REG(P8A_80_DC_DEBUG3, ucDDRSel), 0x0010002F);

        // Cleint2 M1 FRC Display
        ScalerSetDWord(DDR2_GET_REG(P8A_88_DC_PRIORITY3_CTRL2, ucDDRSel), 0x0020003F);

        // Cleint4 M1 OD Write
        ScalerSetDWord(DDR2_GET_REG(P8A_90_DC_PRIORITY3_CTRL4, ucDDRSel), 0x0040005F);

        // Cleint6 M1 OD Read
        ScalerSetDWord(DDR2_GET_REG(P8A_98_DC_PRIORITY3_CTRL6, ucDDRSel), 0x0050006F);

        // Set DDR2 M2 Client Priority Counter
        // Cleint1 M2 FRC Capature
        ScalerSetDWord(DDR2_GET_REG(P8A_84_DC_PRIORITY3_CTRL1, ucDDRSel), 0x0010002F);

        // Cleint3 M2 FRC Display
        ScalerSetDWord(DDR2_GET_REG(P8A_8C_DC_PRIORITY3_CTRL3, ucDDRSel), 0x0020003F);

        // Cleint5 M2 OD Write
        ScalerSetDWord(DDR2_GET_REG(P8A_94_DC_PRIORITY3_CTRL5, ucDDRSel), 0x0040005F);

        // Cleint8 M2 OD Read
        ScalerSetDWord(DDR2_GET_REG(P8A_A0_DC_PRIORITY3_CTRL8, ucDDRSel), 0x0050006F);

        // CleintB MCU Read/Write
        ScalerSetDWord(DDR2_GET_REG(P8A_AC_DC_PRIORITY3_CTRLB, ucDDRSel), 0x009F009F);
    }

#if(_MEMORY_SIZE_CONFIG == _16M_16BIT_DDR2_1PC)

    // Set DDR2 Clint Mux
    ScalerSetByte(P37_B0_M_DOMAIN_CLIENT_MUX_CTRL0, ((_DDR2_PRIMARY_DEVICE == _DDR2_A) ? 0x00 : 0x33));
    ScalerSetByte(P37_B1_M_DOMAIN_CLIENT_MUX_CTRL1, ((_DDR2_PRIMARY_DEVICE == _DDR2_A) ? 0x00 : 0x33));

#elif(_MEMORY_SIZE_CONFIG == _16M_16BIT_DDR2_2PCS)

    // Set DDR2 Clint Mux
    ScalerSetByte(P37_B0_M_DOMAIN_CLIENT_MUX_CTRL0, 0x22);
    ScalerSetByte(P37_B1_M_DOMAIN_CLIENT_MUX_CTRL1, 0x22);
#endif
}

//--------------------------------------------------
// Description  : DC Phy initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR2DCPHYInitial(void)
{
    BYTE ucDDRSel = 0;

    for(ucDDRSel = _DDR2_DEV_SEQ_BEGIN; ucDDRSel < _DDR2_DEV_SEQ_END; ucDDRSel++)
    {
        //==============================
        // DLL Setting
        //==============================
        // PHY & MAC Frequency Ratio 1:2
        ScalerSetDWord(DDR2_GET_REG(P8F_D8_BIST_2TO1_0_3, ucDDRSel), 0xB0000000);

        // One cycele command output delay, RDQS gen mode: PUPD3, enable 3-point cal, fw_set_mode = 'b10.
        ScalerSetDWord(DDR2_GET_REG(P8F_7C_DPI_CTRL0_3, ucDDRSel), 0x01EF2056);

        // Enable CS Output One cycle Delay and Initial DQS/DQ Mux table
        ScalerSetDWord(DDR2_GET_REG(P8E_28_WRLVL_CTRL_3, ucDDRSel), 0x20000FF0);
        ScalerSetDWord(DDR2_GET_REG(P8E_28_WRLVL_CTRL_3, ucDDRSel), ((0x20000FF0 & 0xFFFCCCCF) | (~0xFFFCCCCF & ScalerDDR2CalcWrlvlConfig(&(tDDR2_PLL_PHASE[ucDDRSel])))));

        //------------------------------
        // RDQS Enable
        //------------------------------
        // RDQS enable latency
        ScalerSetDWord(DDR2_GET_REG(P8E_54_READ_CTRL0_SET0_3, ucDDRSel), 0x0000000B); // slice_0: DQS_0
        ScalerSetDWord(DDR2_GET_REG(P8E_58_READ_CTRL0_SET1_3, ucDDRSel), 0x0000000B); // slice_1: DQS_1
        // Apply read delay setting
        ScalerSetDWord(DDR2_GET_REG(P8F_80_DPI_CTRL1_3, ucDDRSel), 0x0000000C);

        //------------------------------
        // Read DQ delay tap
        //------------------------------
        // RDQ delay tap - rising
        ScalerSetDWord(DDR2_GET_REG(P8E_B8_DQS_IN_DLY0_SET0_3, ucDDRSel), 0x05050505); // slice_0: DQ_03~DQ_00
        ScalerSetDWord(DDR2_GET_REG(P8E_BC_DQS_IN_DLY0_SET1_3, ucDDRSel), 0x05050505); // slice_1: DQ_11~DQ_08
        ScalerSetDWord(DDR2_GET_REG(P8E_C8_DQS_IN_DLY1_SET0_3, ucDDRSel), 0x05050505); // slice_0: DQ_07~DQ_04
        ScalerSetDWord(DDR2_GET_REG(P8E_CC_DQS_IN_DLY1_SET1_3, ucDDRSel), 0x05050505); // slice_1: DQ_15~DQ_12
        // RDQ delay tap - falling
        ScalerSetDWord(DDR2_GET_REG(P8E_D8_DQS_IN_DLY2_SET0_3, ucDDRSel), 0x05050505); // slice_0: DQ_03~DQ_00
        ScalerSetDWord(DDR2_GET_REG(P8E_DC_DQS_IN_DLY2_SET1_3, ucDDRSel), 0x05050505); // slice_1: DQ_11~DQ_08
        ScalerSetDWord(DDR2_GET_REG(P8E_E8_DQS_IN_DLY3_SET0_3, ucDDRSel), 0x05050505); // slice_0: DQ_07~DQ_04
        ScalerSetDWord(DDR2_GET_REG(P8E_EC_DQS_IN_DLY3_SET1_3, ucDDRSel), 0x05050505); // slice_1: DQ_15~DQ_12
        // Apply read delay setting
        ScalerSetDWord(DDR2_GET_REG(P8F_80_DPI_CTRL1_3, ucDDRSel), 0x0000000C);

        //------------------------------
        // Rx FIFO latency
        //------------------------------
        ScalerSetDWord(DDR2_GET_REG(P8E_64_READ_CTRL1_3, ucDDRSel), 0x0001000A);
        // Apply read delay setting
        ScalerSetDWord(DDR2_GET_REG(P8F_80_DPI_CTRL1_3, ucDDRSel), 0x0000000C);

        // Set fw_set_mode = 'b01
        ScalerSetDWord(DDR2_GET_REG(P8F_7C_DPI_CTRL0_3, ucDDRSel), 0x01EF2055);

        //------------------------------
        // Controller IO pad driving/ODT
        //------------------------------

        // Set IO Pad Driving
        ScalerSetDWord(DDR2_GET_REG(P8F_24_PAD_CK_CTRL_3, ucDDRSel), 0x00C000C0);
        ScalerSetDWord(DDR2_GET_REG(P8F_28_PAD_CA_CTRL_3, ucDDRSel), 0xC0C0C0C0);
        // Set unbalanced DQS ODT for PUPD3
        ScalerSetDWord(DDR2_GET_REG(P8F_2C_PAD_DQS01_CTRL_3, ucDDRSel), 0x00609080);
        ScalerSetDWord(DDR2_GET_REG(P8F_34_PAD_DQ_CTRL_3, ucDDRSel), 0x50800080);

        // Set ODT enable interval
        ScalerSetDWord(DDR2_GET_REG(P8E_68_READ_CTRL2_SET0_3, ucDDRSel), 0x000000FC);
        ScalerSetDWord(DDR2_GET_REG(P8E_6C_READ_CTRL2_SET1_3, ucDDRSel), 0x000000FC);


        //==============================
        // DC PHY Setting
        //==============================
        //------------------------------
        // DDR timing setting
        //------------------------------
#if(_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_1066M)
        // DDR data rate: 1200 MHz
        ScalerSetDWord(DDR2_GET_REG(PA0_00_DC_PHY_TMCTRL0_0, ucDDRSel), 0x000F0A04);        // tRAS, CL, CWL(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_04_DC_PHY_TMCTRL1_0, ucDDRSel), 0x040A0822);        // tRRD, tRP, tRCDrd, tRC
        ScalerSetDWord(DDR2_GET_REG(PA0_08_DC_PHY_TMCTRL2_0, ucDDRSel), 0x00040912);        // tCCD, tRTP, tWTR, tWR
        ScalerSetDWord(DDR2_GET_REG(PA0_0C_DC_PHY_TMCTRL3_0, ucDDRSel), 0x16094015);        // tFAW, tREFI, tRFC
        ScalerSetDWord(DDR2_GET_REG(PA0_10_DC_PHY_TMCTRL4_0, ucDDRSel), 0x00000A02);        // tMOD, tMRD
        ScalerSetDWord(DDR2_GET_REG(PA0_14_DC_PHY_TMCTRL5_0, ucDDRSel), 0x00200400);        // tZQoper(N/A), tZQinit(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_18_DC_PHY_TMCTRL6_0, ucDDRSel), 0x00240080);        // tDLLK(N/A), tZQCS(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_44_DC_PHY_MOD_REG_0, ucDDRSel), 0x00420073);        // EMR1, MRS
        ScalerSetDWord(DDR2_GET_REG(PA0_48_DC_PHY_MOD23_REG_0, ucDDRSel), 0x00000080);      // EMR3, EMR2
        ScalerSetDWord(DDR2_GET_REG(PA0_38_DC_PHY_DC_MISC_0, ucDDRSel), 0x00000000);
        ScalerSetDWord(DDR2_GET_REG(PA0_2C_DC_PHY_DC_MIS_0, ucDDRSel), 0x00060008);         // tRCDwr, ddr2_odt_dly, ddr_type = ddr2
        ScalerSetDWord(DDR2_GET_REG(PA3_90_DC_PHY_WEIGHT_BANK_0, ucDDRSel), 0x00081F38);    // Outstand reorder: bank weighting

#elif(_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_800M)
        // DDR data rate: 1066 MHz
        ScalerSetDWord(DDR2_GET_REG(PA0_00_DC_PHY_TMCTRL0_0, ucDDRSel), 0x000D0A04);        // tRAS, CL, CWL(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_04_DC_PHY_TMCTRL1_0, ucDDRSel), 0x0308061E);        // tRRD, tRP, tRCDrd, tRC
        ScalerSetDWord(DDR2_GET_REG(PA0_08_DC_PHY_TMCTRL2_0, ucDDRSel), 0x00040710);        // tCCD, tRTP, tWTR, tWR
        ScalerSetDWord(DDR2_GET_REG(PA0_0C_DC_PHY_TMCTRL3_0, ucDDRSel), 0x1208100F);        // tFAW, tREFI, tRFC
        ScalerSetDWord(DDR2_GET_REG(PA0_10_DC_PHY_TMCTRL4_0, ucDDRSel), 0x00000A02);        // tMOD, tMRD
        ScalerSetDWord(DDR2_GET_REG(PA0_14_DC_PHY_TMCTRL5_0, ucDDRSel), 0x00200400);        // tZQoper(N/A), tZQinit(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_18_DC_PHY_TMCTRL6_0, ucDDRSel), 0x00240080);        // tDLLK(N/A), tZQCS(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_44_DC_PHY_MOD_REG_0, ucDDRSel), 0x00420E73);        // EMR1, MRS
        ScalerSetDWord(DDR2_GET_REG(PA0_48_DC_PHY_MOD23_REG_0, ucDDRSel), 0x00000080);      // EMR3, EMR2
        ScalerSetDWord(DDR2_GET_REG(PA0_38_DC_PHY_DC_MISC_0, ucDDRSel), 0x00000000);
        ScalerSetDWord(DDR2_GET_REG(PA0_2C_DC_PHY_DC_MIS_0, ucDDRSel), 0x00060008);         // tRCDwr, ddr2_odt_dly, ddr_type = ddr2
        ScalerSetDWord(DDR2_GET_REG(PA3_90_DC_PHY_WEIGHT_BANK_0, ucDDRSel), 0x00081F38);    // Outstand reorder: bank weighting

#elif((_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_667M) && (_MEMORY_DATA_RATE_SPEED <= _DDR2_DATA_RATE_800M))
        ScalerSetDWord(DDR2_GET_REG(PA0_00_DC_PHY_TMCTRL0_0, ucDDRSel), 0x000D0A04);        // tRAS, CL, CWL(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_04_DC_PHY_TMCTRL1_0, ucDDRSel), 0x0308061E);        // tRRD, tRP, tRCDrd, tRC
        ScalerSetDWord(DDR2_GET_REG(PA0_08_DC_PHY_TMCTRL2_0, ucDDRSel), 0x00040710);        // tCCD, tRTP, tWTR, tWR
        ScalerSetDWord(DDR2_GET_REG(PA0_0C_DC_PHY_TMCTRL3_0, ucDDRSel), 0x1204000F);        // tFAW, tREFI, tRFC
        ScalerSetDWord(DDR2_GET_REG(PA0_10_DC_PHY_TMCTRL4_0, ucDDRSel), 0x00000A02);        // tMOD, tMRD
        ScalerSetDWord(DDR2_GET_REG(PA0_14_DC_PHY_TMCTRL5_0, ucDDRSel), 0x00200400);        // tZQoper(N/A), tZQinit(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_18_DC_PHY_TMCTRL6_0, ucDDRSel), 0x00240080);        // tDLLK(N/A), tZQCS(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_44_DC_PHY_MOD_REG_0, ucDDRSel), 0x00420E73);        // EMR1, MRS
        ScalerSetDWord(DDR2_GET_REG(PA0_48_DC_PHY_MOD23_REG_0, ucDDRSel), 0x00000080);      // EMR3, EMR2
        ScalerSetDWord(DDR2_GET_REG(PA0_38_DC_PHY_DC_MISC_0, ucDDRSel), 0x00000000);
        ScalerSetDWord(DDR2_GET_REG(PA0_2C_DC_PHY_DC_MIS_0, ucDDRSel), 0x00060008);         // tRCDwr, ddr2_odt_dly, ddr_type = ddr2
        ScalerSetDWord(DDR2_GET_REG(PA3_90_DC_PHY_WEIGHT_BANK_0, ucDDRSel), 0x00081F38);    // Outstand reorder: bank weighting

#elif((_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_533M) && (_MEMORY_DATA_RATE_SPEED <= _DDR2_DATA_RATE_667M))
        ScalerSetDWord(DDR2_GET_REG(PA0_00_DC_PHY_TMCTRL0_0, ucDDRSel), 0x000D0A04);        // tRAS, CL, CWL(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_04_DC_PHY_TMCTRL1_0, ucDDRSel), 0x0308061E);        // tRRD, tRP, tRCDrd, tRC
        ScalerSetDWord(DDR2_GET_REG(PA0_08_DC_PHY_TMCTRL2_0, ucDDRSel), 0x00040710);        // tCCD, tRTP, tWTR, tWR
        ScalerSetDWord(DDR2_GET_REG(PA0_0C_DC_PHY_TMCTRL3_0, ucDDRSel), 0x1204000F);        // tFAW, tREFI, tRFC
        ScalerSetDWord(DDR2_GET_REG(PA0_10_DC_PHY_TMCTRL4_0, ucDDRSel), 0x00000A02);        // tMOD, tMRD
        ScalerSetDWord(DDR2_GET_REG(PA0_14_DC_PHY_TMCTRL5_0, ucDDRSel), 0x00200400);        // tZQoper(N/A), tZQinit(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_18_DC_PHY_TMCTRL6_0, ucDDRSel), 0x00240080);        // tDLLK(N/A), tZQCS(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_44_DC_PHY_MOD_REG_0, ucDDRSel), 0x00420E73);        // EMR1, MRS
        ScalerSetDWord(DDR2_GET_REG(PA0_48_DC_PHY_MOD23_REG_0, ucDDRSel), 0x00000080);      // EMR3, EMR2
        ScalerSetDWord(DDR2_GET_REG(PA0_38_DC_PHY_DC_MISC_0, ucDDRSel), 0x00000000);
        ScalerSetDWord(DDR2_GET_REG(PA0_2C_DC_PHY_DC_MIS_0, ucDDRSel), 0x00060008);         // tRCDwr, ddr2_odt_dly, ddr_type = ddr2
        ScalerSetDWord(DDR2_GET_REG(PA3_90_DC_PHY_WEIGHT_BANK_0, ucDDRSel), 0x00081F38);    // Outstand reorder: bank weighting

#else
        ScalerSetDWord(DDR2_GET_REG(PA0_00_DC_PHY_TMCTRL0_0, ucDDRSel), 0x000D0A04);        // tRAS, CL, CWL(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_04_DC_PHY_TMCTRL1_0, ucDDRSel), 0x0308061E);        // tRRD, tRP, tRCDrd, tRC
        ScalerSetDWord(DDR2_GET_REG(PA0_08_DC_PHY_TMCTRL2_0, ucDDRSel), 0x00040710);        // tCCD, tRTP, tWTR, tWR
        ScalerSetDWord(DDR2_GET_REG(PA0_0C_DC_PHY_TMCTRL3_0, ucDDRSel), 0x1204000F);        // tFAW, tREFI, tRFC
        ScalerSetDWord(DDR2_GET_REG(PA0_10_DC_PHY_TMCTRL4_0, ucDDRSel), 0x00000A02);        // tMOD, tMRD
        ScalerSetDWord(DDR2_GET_REG(PA0_14_DC_PHY_TMCTRL5_0, ucDDRSel), 0x00200400);        // tZQoper(N/A), tZQinit(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_18_DC_PHY_TMCTRL6_0, ucDDRSel), 0x00240080);        // tDLLK(N/A), tZQCS(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA0_44_DC_PHY_MOD_REG_0, ucDDRSel), 0x00420E73);        // EMR1, MRS
        ScalerSetDWord(DDR2_GET_REG(PA0_48_DC_PHY_MOD23_REG_0, ucDDRSel), 0x00000080);      // EMR3, EMR2
        ScalerSetDWord(DDR2_GET_REG(PA0_38_DC_PHY_DC_MISC_0, ucDDRSel), 0x00000000);
        ScalerSetDWord(DDR2_GET_REG(PA0_2C_DC_PHY_DC_MIS_0, ucDDRSel), 0x00060008);         // tRCDwr, ddr2_odt_dly, ddr_type = ddr2
        ScalerSetDWord(DDR2_GET_REG(PA3_90_DC_PHY_WEIGHT_BANK_0, ucDDRSel), 0x00081F38);    // Outstand reorder: bank weighting
#endif

        //------------------------------
        // Other DDR setting
        //------------------------------
#if(_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_1066M)
        // Disable Auto Precharge Function
        ScalerSetDWord(DDR2_GET_REG(PA0_40_DC_PHY_DC_DDR3_CTL_0, ucDDRSel), 0xC00C0000);        // Disable 8-bank support
#else
        // Enable Auto Precharge Function
        ScalerSetDWord(DDR2_GET_REG(PA0_40_DC_PHY_DC_DDR3_CTL_0, ucDDRSel), 0x000C0000);        // Disable 8-bank support
#endif

        ScalerSetDWord(DDR2_GET_REG(PA0_C0_DC_PHY_DUMMY_REG_0, ucDDRSel), 0x80000048);          // DDR2 pin mux, DDR FSM refresh cmd mask win
        // DDR die initialization
        ScalerSetDWord(DDR2_GET_REG(PA1_40_SYS_CMP_FAIL_READ_0_0, ucDDRSel), 0x00000048);
        ScalerSetDWord(DDR2_GET_REG(PA0_28_DC_PHY_DC_MIS2_0, ucDDRSel), 0x00000010);

        // Delay Time us [5,x] Waiting for DDR setting
        DELAY_5US();

        ScalerSetDWord(DDR2_GET_REG(PA6_00_DC_PHY_FIFO_ARB_0_0, ucDDRSel), 0x00000040);         // cmdq_fifo
        ScalerSetDWord(DDR2_GET_REG(PA6_F8_DC_PHY_CS_CTRL_0, ucDDRSel), 0x00000000);            // 2 pcs DDR setting(N/A)
        ScalerSetDWord(DDR2_GET_REG(PA1_54_SYS_STS_1_0, ucDDRSel), 0x00000001);
        ScalerSetDWord(DDR2_GET_REG(PA4_98_DC_PHY_DC_SYS2_CTRL_0, ucDDRSel), 0x00000005);

        // Outstand Reorder Setting
        ScalerSetDWord(DDR2_GET_REG(PA3_80_DC_PHY_WEIGHT_ENABLE_0, ucDDRSel), 0x0000001D);      // Outstand reorder enable
        ScalerSetDWord(DDR2_GET_REG(PA3_88_DC_PHY_WEIGHT_DIERECTION_0, ucDDRSel), 0x00008200);  // Outstand reorder: direction weighting
    }
}

//--------------------------------------------------
// Description  : Calculate write level config
// Input Value  : pstDDR2PLLPhase
// Output Value : DWORD (32bit) of register setting
//--------------------------------------------------
DWORD ScalerDDR2CalcWrlvlConfig(StructDDR2PLLPI code *pstDDR2PLLPhase)
{
    StructDDR2PLLPI stTheoPI;
    DWORD ulWrlvlConfig = 0;

    stTheoPI.ucDQS0 = pstDDR2PLLPhase->ucDQS0 % _TOT_THEO_PI_NUM;
    stTheoPI.ucDQS1 = pstDDR2PLLPhase->ucDQS1 % _TOT_THEO_PI_NUM;
    stTheoPI.ucDQ0 = pstDDR2PLLPhase->ucDQ0 % _TOT_THEO_PI_NUM;
    stTheoPI.ucDQ1 = pstDDR2PLLPhase->ucDQ1 % _TOT_THEO_PI_NUM;

    // DQS0
    ulWrlvlConfig |= ((stTheoPI.ucDQS0 < (53 + 0)) ? 0x00000000 :
                      ((stTheoPI.ucDQS0 < (21 + 64)) ? 0x00000010 :
                       ((stTheoPI.ucDQS0 < (53 + 64)) ? 0x00001000 : 0x00001010)));
    // DQS1
    ulWrlvlConfig |= ((stTheoPI.ucDQS1 < (53 + 0)) ? 0x00000000 :
                      ((stTheoPI.ucDQS1 < (21 + 64)) ? 0x00000020 :
                       ((stTheoPI.ucDQS1 < (53 + 64)) ? 0x00002000 : 0x00002020)));
    // DQ0
    ulWrlvlConfig |= ((stTheoPI.ucDQ0 < (53 + 0)) ? 0x00000000 :
                      ((stTheoPI.ucDQ0 < (21 + 64)) ? 0x00000100 :
                       ((stTheoPI.ucDQ0 < (53 + 64)) ? 0x00010000 : 0x00010100)));
    // DQ1
    ulWrlvlConfig |= ((stTheoPI.ucDQ1 < (53 + 0)) ? 0x00000000 :
                      ((stTheoPI.ucDQ1 < (21 + 64)) ? 0x00000200 :
                       ((stTheoPI.ucDQ1 < (53 + 64)) ? 0x00020000 : 0x00020200)));

    return ulWrlvlConfig;
}

#if(_MEMORY_SIZE_CONFIG == _16M_16BIT_DDR2_2PCS)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch display client mux for rotation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR2RotationSetClientMux(void)
{
    switch(GET_ROT_TYPE())
    {
        case _ROT_CW180:
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _ROT_VER_MIRROR:
#endif
            // _ROT_CW180, _ROT_VER_MIRROR: set disp client mux different from cap client
            // M1
            ScalerSetBit(P37_B0_M_DOMAIN_CLIENT_MUX_CTRL0, ~_BIT4, ((ScalerGetBit(P37_B0_M_DOMAIN_CLIENT_MUX_CTRL0, _BIT0) == _BIT0) ? 0x00 : _BIT4));
            // M2
            ScalerSetBit(P37_B0_M_DOMAIN_CLIENT_MUX_CTRL0, ~_BIT5, ((ScalerGetBit(P37_B0_M_DOMAIN_CLIENT_MUX_CTRL0, _BIT1) == _BIT1) ? 0x00 : _BIT5));
            break;

        default:
            // Other cases: set disp client mux as cap client
            // M1
            ScalerSetBit(P37_B0_M_DOMAIN_CLIENT_MUX_CTRL0, ~_BIT4, ((ScalerGetBit(P37_B0_M_DOMAIN_CLIENT_MUX_CTRL0, _BIT0) == _BIT0) ? _BIT4 : 0x00));
            // M2
            ScalerSetBit(P37_B0_M_DOMAIN_CLIENT_MUX_CTRL0, ~_BIT5, ((ScalerGetBit(P37_B0_M_DOMAIN_CLIENT_MUX_CTRL0, _BIT1) == _BIT1) ? _BIT5 : 0x00));
            break;
    }
}
#endif
#endif
#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
