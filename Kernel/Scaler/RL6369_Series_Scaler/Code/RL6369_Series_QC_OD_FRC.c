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
// ID Code      : RL6369_Series_QC_OD_FRC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6369_SERIES_QC__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//--------------------------------------------------
// Code Tables of FRC CRC
//--------------------------------------------------
BYTE code tFRC_CRCTable[] = {
    0x8D, 0xB1, 0x8A, 0x00, 0x00, 0x00,
};

//--------------------------------------------------
// Code Tables of OD Setting and CRC
//--------------------------------------------------
BYTE code tQC_OD_8BIT_TABLE[] =
{
    0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x04, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x09, 0x05, 0x00, 0x01, 0x00, 0x02, 0x06, 0x03, 0x06, 0x06, 0x06, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x0B, 0x07, 0x04, 0x00, 0x01, 0x04, 0x04, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x10,
    0x11, 0x0F, 0x09, 0x04, 0x00, 0x03, 0x06, 0x05, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0F, 0x13, 0x19, 0x1C,
    0x1B, 0x14, 0x0D, 0x08, 0x03, 0x00, 0x03, 0x06, 0x0D, 0x0D, 0x0D, 0x10, 0x12, 0x17, 0x1C, 0x23, 0x26,
    0x15, 0x18, 0x12, 0x0D, 0x08, 0x04, 0x00, 0x03, 0x08, 0x0D, 0x0F, 0x12, 0x17, 0x1B, 0x1E, 0x2A, 0x2C,
    0x17, 0x1C, 0x1B, 0x14, 0x0F, 0x0A, 0x05, 0x00, 0x04, 0x08, 0x0D, 0x11, 0x17, 0x1D, 0x1F, 0x2A, 0x32,
    0x1B, 0x21, 0x20, 0x1E, 0x16, 0x12, 0x0D, 0x07, 0x00, 0x04, 0x09, 0x0F, 0x15, 0x1D, 0x21, 0x2B, 0x34,
    0x1F, 0x20, 0x20, 0x21, 0x1B, 0x1B, 0x14, 0x0E, 0x08, 0x00, 0x06, 0x0D, 0x14, 0x1E, 0x22, 0x2A, 0x35,
    0x24, 0x1F, 0x1F, 0x21, 0x1E, 0x1E, 0x1B, 0x15, 0x0F, 0x08, 0x00, 0x06, 0x10, 0x1B, 0x22, 0x2A, 0x34,
    0x22, 0x1A, 0x1B, 0x20, 0x21, 0x1F, 0x1B, 0x18, 0x12, 0x0F, 0x08, 0x00, 0x09, 0x17, 0x21, 0x29, 0x30,
    0x1A, 0x18, 0x19, 0x1E, 0x20, 0x20, 0x1E, 0x19, 0x15, 0x10, 0x0D, 0x08, 0x00, 0x0D, 0x1F, 0x24, 0x2C,
    0x16, 0x16, 0x15, 0x16, 0x16, 0x16, 0x17, 0x16, 0x16, 0x14, 0x12, 0x0D, 0x09, 0x00, 0x0D, 0x1C, 0x23,
    0x13, 0x10, 0x12, 0x11, 0x12, 0x12, 0x12, 0x12, 0x11, 0x11, 0x10, 0x0D, 0x0A, 0x09, 0x00, 0x10, 0x1A,
    0x11, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0B, 0x0B, 0x0B, 0x0A, 0x09, 0x08, 0x00, 0x0F,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00,
};

BYTE code tQC_OD_CRC_TABLE_0[] =
{
    0xC9, 0x2B, 0xEB, 0xC3, 0x29, 0xA9, // M1

    0xAB, 0xE1, 0xD8, 0x02, 0xE8, 0x51, // M1
};


BYTE code tQC_OD_CRC_TABLE_1[] =
{
    0xB7, 0x42, 0x87, 0xF6, 0x79, 0xCA, // M1

    0x46, 0x1D, 0xD9, 0xF6, 0x79, 0xCA, // M1
};

BYTE code tQC_OD_CRC_TABLE_2[] =
{
    0x39, 0xAE, 0xE2, 0x12, 0x5D, 0x7C, // M1

    0x46, 0x1D, 0xD9, 0xF6, 0x79, 0xCA, // M1
};

BYTE code tQC_OD_CRC_TABLE_3[] =
{
    0xAE, 0x6E, 0x12, 0xB2, 0x36, 0xF3, // M1

    0xCF, 0x8A, 0xA0, 0x21, 0x99, 0xD0, // M1
};

BYTE code tQC_OD_CRC_TABLE_4[] =
{
    0x5C, 0x1E, 0x1C, 0x06, 0x70, 0x6B, // M1

    0x46, 0x1D, 0xD9, 0xF6, 0x79, 0xCA, // M1
};

BYTE code tQC_OD_CRC_TABLE_5[] =
{
    0x65, 0xEE, 0x43, 0x86, 0x12, 0xB0, // M1

    0x46, 0x1D, 0xD9, 0xF6, 0x79, 0xCA, // M1
};

BYTE code tQC_OD_CRC_TABLE_6[] =
{
    0x45, 0x08, 0x0C, 0x3C, 0xAB, 0x2D, // M1

    0x26, 0x54, 0x7F, 0xD1, 0xCC, 0x56, // M1
};

BYTE code tQC_OD_CRC_TABLE_7[] =
{
    0xDB, 0x66, 0x5A, 0x17, 0x8F, 0x43, // M1

    0x30, 0xF2, 0xED, 0xF0, 0x9F, 0x83, // M1
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
typedef enum
{
    _DISPLAY_MODE_1P,
    _DISPLAY_MODE_PIP,
    _DISPLAY_MODE_PBP_LR,
    _DISPLAY_MODE_PBP_TB,
    _DISPLAY_MODE_4P,
} EnumDisplayMode;



#define _REG_PAGE_OFFSET                (0x4000)

#if(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_2PCS)
//#define _FRC_CAP_M1_1ST_BLOCK_STA_ADDR                    ((DWORD)0x000000)
#define _FRC_CAP_M1_2ND_BLOCK_STA_ADDR                    ((DWORD)512 << 12)   // 0x20 0000
#define _FRC_CAP_M2_1ST_BLOCK_STA_ADDR                    ((DWORD)1024 << 12)  // 0x40 0000
#define _FRC_CAP_M2_2ND_BLOCK_STA_ADDR                    ((DWORD)1536 << 12)  // 0x60 0000
#define _FRC_CAP_S1_1ST_BLOCK_STA_ADDR                    ((DWORD)2048 << 12)  // 0x80 0000
#define _FRC_CAP_S1_2ND_BLOCK_STA_ADDR                    ((DWORD)2560 << 12)  // 0xA0 0000
#define _FRC_CAP_S2_1ST_BLOCK_STA_ADDR                    ((DWORD)2304 << 12)  // 0x90 0000
#define _FRC_CAP_S2_2ND_BLOCK_STA_ADDR                    ((DWORD)2816 << 12)  // 0xB0 0000
#elif(_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_1PC)
//#define _FRC_CAP_M1_1ST_BLOCK_STA_ADDR                    ((DWORD)0x000000)
#define _FRC_CAP_M1_2ND_BLOCK_STA_ADDR                    ((DWORD)512 << 11)   // 0x10 0000
#define _FRC_CAP_M2_1ST_BLOCK_STA_ADDR                    ((DWORD)1024 << 11)  // 0x20 0000
#define _FRC_CAP_M2_2ND_BLOCK_STA_ADDR                    ((DWORD)1536 << 11)  // 0x30 0000
#define _FRC_CAP_S1_1ST_BLOCK_STA_ADDR                    ((DWORD)2048 << 11)  // 0x40 0000
#define _FRC_CAP_S1_2ND_BLOCK_STA_ADDR                    ((DWORD)2560 << 11)  // 0x50 0000
#define _FRC_CAP_S2_1ST_BLOCK_STA_ADDR                    ((DWORD)2304 << 11)  // 0x48 0000
#define _FRC_CAP_S2_2ND_BLOCK_STA_ADDR                    ((DWORD)2816 << 11)  // 0x58 0000
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerQCFRCRecoverSetting(void);
bit ScalerQCFRCTest(void);
void ScalerQCODDDomainPattern1(void);
void ScalerQCODDDomainPattern2(void);
bit ScalerQCODTest(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//****************************************************************************
// Description  : Recover FRC setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCFRCRecoverSetting(void)
{
    // FRC off & Frame Sync mode
    ScalerSetByte(P5_CF_MN_DISP_CTRL, 0x05);

    // Double buffer enable
    ScalerSetByte(P5_D0_MN_SDR_STATUS, 0x10);

    ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    ScalerTimerDelayXms(30);

    // Wait double buffer
    ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P5_D0_MN_SDR_STATUS, _BIT4, 0);

    ScalerTimerWaitForEvent(_EVENT_IVS);

    // Disable random gen.
   // ScalerQCIDomainRandomGenOff();
}

//--------------------------------------------------
// Description  : Scale Down Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCFRCTest(void)
{
    BYTE ucData = 0;
    DebugMessageScaler("5. FRC Start", 0x00);

    //-----------------------------------
    // Set Random Generator
    //-----------------------------------
    ScalerQCIDomainRandomGenOn(_MASS);
    ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), 0x00);

    // Input : 1280x1024, Frame mode, Single buffer
    ScalerSetByte(P5_A8_IN1_WATER_LEVEL, 0xA0);
    ScalerSetByte(P5_A9_IN1_WR_NUM_H, 0x0B);
    ScalerSetByte(P5_AA_IN1_WR_NUM_L, 0xFF);
    ScalerSetByte(P5_AB_IN1_WR_LEN, 0xA0);
    ScalerSetByte(P5_AC_IN1_WR_REMAIN, 0xA0);
    ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, 0x00);
    ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, 0x00);
    ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, 0x00);

    ScalerSetByte(P5_B0_IN1_LINE_STEP_H, 0x03);
    ScalerSetByte(P5_B1_IN1_LINE_STEP_L, 0x3E);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_1PC)

    ScalerSetByte(P5_B2_IN1_BLOCK_STEP_H, 0x07);
    ScalerSetByte(P5_B3_IN1_BLOCK_STEP_L, 0x80);
    ScalerSetByte(P5_B4_IN1_BL2_ADDR_H, 0x3C);
    ScalerSetByte(P5_B5_IN1_BL2_ADDR_M, 0x00);
    ScalerSetByte(P5_B6_IN1_BL2_ADDR_L, 0x00);
#else

    ScalerSetByte(P5_B2_IN1_BLOCK_STEP_H, 0x0F);
    ScalerSetByte(P5_B3_IN1_BLOCK_STEP_L, 0x00);
    ScalerSetByte(P5_B4_IN1_BL2_ADDR_H, 0x78);
    ScalerSetByte(P5_B5_IN1_BL2_ADDR_M, 0x00);
    ScalerSetByte(P5_B6_IN1_BL2_ADDR_L, 0x00);
#endif

    ScalerSetByte(P5_B7_IN1_LINE_NUM_H, 0x54);
    ScalerSetByte(P5_B8_IN1_LINE_NUM_L, 0x00);
    ScalerSetByte(P5_B9_IN1_SDR_CTRL, 0x82);
    //ScalerSetByte(P5_B9_IN1_SDR_CTRL, 0xA2);

    // Display : 1280x1024, Frame mode, Single buffer
    ScalerSetByte(P5_BC_MN_PRRD_VST_H, 0x00);
    ScalerSetByte(P5_BD_MN_PRRD_VST_L, 0x03);
    ScalerSetByte(P5_BE_MN_PXL_NUM_H, 0x05);
    ScalerSetByte(P5_BF_MN_PXL_NUM_L, 0x00);

    ScalerSetByte(P5_C0_MN_WTLVL, 0xFC);
    ScalerSetByte(P5_C2_MN_READ_NUM_H, 0x07);
    ScalerSetByte(P5_C3_MN_READ_NUM_L, 0x9E);
    ScalerSetByte(P5_C4_MN_READ_LEN, 0xFC);
    ScalerSetByte(P5_C5_MN_READ_REMAIN, 0x78);
    ScalerSetByte(P5_C6_MN_READ_ADDR_H, 0x00);
    ScalerSetByte(P5_C7_MN_READ_ADDR_M, 0x00);
    ScalerSetByte(P5_C8_MN_READ_ADDR_L, 0x00);
    ScalerSetByte(P5_C9_MN_LINE_STEP_H, 0x03);
    ScalerSetByte(P5_CA_MN_LINE_STEP_L, 0x3E);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_1PC)
    ScalerSetByte(P5_CB_MN_BLOCK_STEP_H, 0x07);    // Block step[22:19]
    ScalerSetByte(P5_CC_MN_BLOCK_STEP_L, 0x80);    // Block step[18:11]
#else
    ScalerSetByte(P5_CB_MN_BLOCK_STEP_H, 0x0F);    // Block step[22:19]
    ScalerSetByte(P5_CC_MN_BLOCK_STEP_L, 0x00);    // Block step[18:11]
#endif

    ScalerSetByte(P5_CD_MN_LINE_NUM_H, 0x14);
    ScalerSetByte(P5_CE_MN_LINE_NUM_L, 0x00);
    ScalerSetByte(P5_CF_MN_DISP_CTRL, 0x01);

    ScalerSetByte(P5_D0_MN_SDR_STATUS, 0x10); // Set Double buffer

    // Wait double buffer
    ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P5_D0_MN_SDR_STATUS, _BIT4, 0);

    ScalerTimerWaitForEvent(_EVENT_IVS);

    //-----------------------------------
    // Check CRC
    //-----------------------------------
    ScalerSetByte(P5_F3_MN_TEST, 0x01);
    ucData = (ucData | ((BYTE)ScalerQCCRCCompare( _M_CRC_AFTER_FIFO, tFRC_CRCTable, 1) << 0));
    ScalerSetByte(P5_F3_MN_TEST, 0x00);

    DebugMessageScaler("5. Mode_1", ucData);

    //-----------------------------------
    // Recover FRC Setting
    //-----------------------------------
    ScalerQCFRCRecoverSetting();
    ScalerQCIDomainRandomGenOff();
   // ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    DebugMessageScaler("5. FRC End", 0x00);

    if(ucData == 0x00)
    {
        DebugMessageQC("6. FRC PASS", 0x00);
        return 0;
    }
    else
    {
        DebugMessageQC("6. FRC Mode", 0x01);
        DebugMessageQC("6. FRC FAIL", 0x00);
        return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : Enable D Domain Pattern1 for OD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCODDDomainPattern1(void)
{
    ScalerSetByte(P7_F0_DISP_PG_R_CTRL, 0xCD);
    ScalerSetByte(P7_F1_DISP_PG_G_CTRL, 0x0D);
    ScalerSetByte(P7_F2_DISP_PG_B_CTRL, 0x0D);
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, 0x00);
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, 0x00);
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, 0x00);
    ScalerSetByte(P7_F6_DISP_PG_PIXEL_DELTA_H, 0x09);
    ScalerSetByte(P7_F7_DISP_PG_LINE_DELTA_H, 0x13);
    ScalerSetByte(P7_F9_DISP_PG_LINE_STEP_H, 0x10);

    ScalerSetByte(P7_FB_D_PG_CTRL_0, 0x40);
    ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L, 0x15);
    ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL, 0x00);
}


//--------------------------------------------------
// Description  : Enable D Domain Pattern2 for OD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCODDDomainPattern2(void)
{
    ScalerSetByte(P7_F0_DISP_PG_R_CTRL, 0xCD);
    ScalerSetByte(P7_F1_DISP_PG_G_CTRL, 0x0D);
    ScalerSetByte(P7_F2_DISP_PG_B_CTRL, 0x0D);
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, 0x01);
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, 0x01);
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, 0x01);
    ScalerSetByte(P7_F6_DISP_PG_PIXEL_DELTA_H, 0x09);
    ScalerSetByte(P7_F7_DISP_PG_LINE_DELTA_H, 0x13);
    ScalerSetByte(P7_F9_DISP_PG_LINE_STEP_H, 0x10);

    ScalerSetByte(P7_FB_D_PG_CTRL_0, 0x40);
    ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L, 0x15);
    ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL, 0x00);
}


//--------------------------------------------------
// Description  : OD Test
// Input Value  : None
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCODTest(void)
{
    BYTE ucData = 0;
    BYTE ucODLUTWriteStatus = 0;

    DebugMessageQC("5. OD Start", 0x00);

    //==================================================
    // Enable token ring OD client arbitration
    //==================================================
    ScalerSetByte(P4_B0_SDR_RSC_RTC_RD, 0xAA);
    ScalerSetByte(P4_B1_SDR_RSC_RTC_WR, 0x55);

    //==================================================
    // Load 8-bit OD LUT Table
    //==================================================
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7), 0x00);
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7), _BIT7);
    ScalerBurstWrite(tQC_OD_8BIT_TABLE, sizeof(tQC_OD_8BIT_TABLE), GET_CURRENT_BANK_NUMBER(), P3_C0_LS_LUT_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    ScalerRead(P3_BF_LS_LUT_CTRL, 1, &ucODLUTWriteStatus, _NON_AUTOINC);

    if((ucODLUTWriteStatus & 0x02) != 0x00)
    {
        DebugMessageQC("5. 3.OD Write 8-bit LUT Fail", 0x00);
    }

    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7), 0x00);

    ucODLUTWriteStatus = 0x00;


    // Memory Start Address and R/W FIFO Setting
    ScalerSetByte(P3_D1_LS_DDR_FIFO_WTLVL_W_L, 0x30);
    ScalerSetByte(P3_D3_LS_DDR_FIFO_WTLVL_R_L, 0x60);
    ScalerSetByte(P3_D7_LS_DDR_FIFO_RW_LEN_L, 0x60);
    ScalerSetByte(P3_DB_LS_DDR_START_ADDR_H, 0x00);
    ScalerSetByte(P3_DC_LS_DDR_START_ADDR_M, 0x00);
    ScalerSetByte(P3_DD_LS_DDR_START_ADDR_L, 0x00);

    // DPG On
    ScalerQCDDomainRandomGenOn(_MASS);

    //==================================================
    // Pattern 0:
    // RGBtoYUV
    // YUV444
    // Src Res: prev->4bit+UV round, curr->6bit+UV round
    // YUVtoRGB
    // Lvl Est: est_gain=9, est_value=1, asymmetric
    // NR: RGB related mode, nr_thd=1
    // HLW: full mode
    // Delta Gain: 93/64
    //==================================================
    DebugMessageQC("5. Mode_0", 0x00);

    // R/W num & remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x08);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0xF8);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x54);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, (_BIT4 | _BIT3));
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x5D);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT5));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT5 | _BIT1));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT6 | _BIT5 | _BIT4));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, 0x09);
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6 | 0x01));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), 0x00);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_CRC_AFTER_OD, tQC_OD_CRC_TABLE_0, 2) << 0);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 1:
    // RGBtoYUV (Simp.)
    // Comp: YUV444to422, drop Mode, uv type 0
    // Src Res: prev->5bit+UV round, curr->4bit
    // Decomp: interp. mode
    // YUVtoRGB (Simp.)
    // Lvl Est: est_gain=15, est_value=3, est_range=8_pixels
    // NR: RGB indep. mode, nr_thd=9
    // HLW: full mode
    // Delta Gain: 1/64
    //==================================================
    DebugMessageQC("5. Mode_1", 0x00);

    // R/W num & remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x0A);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x17);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | _BIT3 | _BIT1));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, (_BIT5 | _BIT4));
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x01);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT6 | _BIT5 | _BIT4));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (_BIT4 | 0x0F));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (0x03));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), 0x00);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_CRC_AFTER_OD, tQC_OD_CRC_TABLE_1, 2) << 1);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 2:
    // RGBtoYUV
    // Comp: YUV444to411, drop Mode
    // Src Res: prev->6bit, curr->8bit
    // Decomp: dup. mode
    // Lvl Est: est_gain=6, est_value=2, est_range=32_pixels, asymmetric
    // NR: RGB indep. mode, nr_thd=2
    // HLW: full mode
    // Delta Gain: 64/64
    //==================================================
    DebugMessageQC("5. Mode_2", 0x00);

    // R/W num & remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x0A);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x79);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x08);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | _BIT3 | _BIT0));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, (_BIT4 | 0x01));
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x40);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT6 | _BIT5 | _BIT4 | 0x02));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT6 | _BIT3 | _BIT2));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, 0x00);
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (_BIT5 | _BIT4 | 0x06));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6 | 0x02));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), 0x00);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_CRC_AFTER_OD, tQC_OD_CRC_TABLE_2, 2) << 2);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 3:
    // Comp: SP1x2, average Mode
    // Src Res: prev->6bit, curr->5bit
    // Decomp: dup. mode
    // Bypass current frame
    // Lvl Est: est_gain=1, est_value=1, est_range=16_pixels, asymmetric
    // NR: RGB related mode, nr_thd=2
    // HLW: full mode
    // Delta Gain: 255/64
    //==================================================
    DebugMessageQC("5. Mode_3", 0x00);

    // R/W num & remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x0A);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0xA7);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x34);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | _BIT3 | _BIT0));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, (_BIT4 | _BIT3 | 0x01));
    ScalerSetByte(P3_A3_DELTA_GAIN, 0xFF);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT7 | _BIT4 | 0x04));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT6 | _BIT3 | _BIT2));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT7));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (_BIT5 | 0x01));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6 | 0x01));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), 0x00);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_CRC_AFTER_OD, tQC_OD_CRC_TABLE_3, 2) << 3);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 4:
    // Comp: SP1x3, average Mode
    // Src Res: prev->6bit, curr->6bit
    // Decomp: interp. mode
    // YUVtoRGB
    // Lvl Est: est_gain=14, est_value=0, est_range=16_pixels, asymmetric
    // NR: RGB indep. mode, nr_thd=1
    // HLW: full mode
    // Delta Gain: 99/64
    //==================================================
    DebugMessageQC("5. Mode_4", 0x00);

    // R/W num & remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x0A);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0xA7);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x34);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | _BIT3 | _BIT0));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, (_BIT4));
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x63);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT4 | 0x06));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT6));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (_BIT5 | 0x0E));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), _BIT0);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_CRC_AFTER_OD, tQC_OD_CRC_TABLE_4, 2) << 4);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 5:
    // RGBtoYUV
    // Comp: SP1x4, average Mode
    // Src Res: prev->8bit, curr->6bit
    // Decomp: interp. mode
    // YUVtoRGB
    // Lvl Est: est_gain=8, est_value=1, est_range=8_pixels
    // HLW: full mode
    //==================================================
    DebugMessageQC("5. Mode_5", 0x00);

    // R/W num & remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x07);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0xD9);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x4C);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, 0x00);
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x40);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT5 | _BIT4 | 0x08));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT6));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (_BIT4 | 0x08));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (0x01));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), _BIT0);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_CRC_AFTER_OD, tQC_OD_CRC_TABLE_5, 2) << 5);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 6:
    // RGBtoYUV
    // Comp: YUV444to422, average Mode, uv type 1
    // Src Res: prev->4bit+UV round, curr->8bit
    // Decomp: interp. mode
    // Lvl Est: est_gain=8, est_value=2, asymmetric
    // HLW: inside HLW
    //==================================================
    DebugMessageQC("5. Mode_6", 0x00);

    ScalerQCHighlightWindowOn();

    // R/W num & remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x06);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0xBA);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x40);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | 0x03));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, 0x00);
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x40);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT5 | _BIT4 | _BIT0));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT3));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT4));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (0x08));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6 | 0x02));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), _BIT0);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_CRC_AFTER_OD, tQC_OD_CRC_TABLE_6, 2) << 6);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    //==================================================
    // Pattern 7:
    // RGBtoYUV
    // Comp: YUV444to422, average Mode, uv type 1
    // Src Res: prev->4bit+UV round, curr->8bit
    // Decomp: interp. mode
    // Lvl Est: est_gain=8, est_value=2, asymmetric
    // HLW: outside HLW
    //==================================================
    DebugMessageQC("5. Mode_7", 0x00);

    ScalerQCHighlightWindowOn();

    // R/W num & remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x06);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0xBA);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x40);

    ScalerSetBit(P3_A1_LS_CTRL0, 0x00, (_BIT5 | 0x03));
    ScalerSetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_10_HLW_CONTROL3, ~(_BIT5 | _BIT4), _BIT5);
    ScalerSetBit(P3_A2_LS_CTRL1, 0x00, 0x00);
    ScalerSetByte(P3_A3_DELTA_GAIN, 0x40);
    ScalerSetBit(P3_B0_LS_FRAME0, 0x00, (_BIT5 | _BIT4 | _BIT0));
    ScalerSetBit(P3_B1_LS_FRAME1, 0x00, (_BIT7 | _BIT3));
    ScalerSetBit(P3_B2_LS_FRAME2, 0x00, (_BIT4));
    ScalerSetBit(P3_B3_LS_FRAME4, 0x00, (0x08));
    ScalerSetBit(P3_B4_LS_FRAME5, 0x00, (_BIT6 | 0x02));
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT0), _BIT0);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern1();
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerQCODDDomainPattern2();
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_CRC_AFTER_OD, tQC_OD_CRC_TABLE_7, 2) << 7);

    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    ScalerQCHighlightWindowOff();
    ScalerQCDDomainPatternGenOff();

    DebugMessageQC("5. OD End", 0x00);

    if(ucData == 0x00)
    {
        DebugMessageQC("6. OD PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. Fail Mode", ucData);
        DebugMessageQC("6. OD FAIL", 0x00);
        return _TEST_FAIL;
    }
}

#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)
