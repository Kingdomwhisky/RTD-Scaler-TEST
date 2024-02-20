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
// ID Code      : RL6492_Series_QC_OD_FRC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_QC__

#include "ScalerFunctionInclude.h"

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
StructMemoryLineBlockStep ScalerQCMemoryCalculateLineStepAndBlockStep(DWORD ulHorSize, WORD usVerSize);

typedef enum
{
    _DISPLAY_MODE_1P,
    _DISPLAY_MODE_PIP,
    _DISPLAY_MODE_PBP_LR,
    _DISPLAY_MODE_PBP_TB,
    _DISPLAY_MODE_4P,
} EnumDisplayMode;

//****************************************************************************
// CODE TABLES
//****************************************************************************

//--------------------------------------------------
// Code Tables of FRC CRC
//--------------------------------------------------
BYTE code tFRC_CRCTable[] = {
    0x4B, 0xA1, 0xEB, 0x00, 0x00, 0x00, // M1
};

//--------------------------------------------------
// Code Tables of Rotation CRC
//--------------------------------------------------
BYTE code tRotation_CRCTable[] = {
    0x88, 0x89, 0xC7, 0x00, 0x00, 0x00, // M1
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
    0x2B, 0x8E, 0x74, 0x1B, 0x6B, 0x88, // M1
    0x4A, 0xCB, 0x05, 0x88, 0x8C, 0x92, // M1
    0x82, 0x90, 0x0C, 0x3A, 0x7D, 0x69, // M1
};

BYTE code tQC_OD_CRC_TABLE_1[] =
{
    0x2B, 0x8E, 0x74, 0x1B, 0x6B, 0x88, // M1
    0x9A, 0x22, 0x04, 0x15, 0xAC, 0xD2, // M1
    0x25, 0x4E, 0xEE, 0x87, 0x20, 0x36, // M1
};

BYTE code tQC_OD_CRC_TABLE_2[] =
{
    0x2B, 0x8E, 0x74, 0x1B, 0x6B, 0x88, // M1
    0xA3, 0xDF, 0x0A, 0x56, 0x6F, 0xD9, // M1
    0x4B, 0x3D, 0x2D, 0x3E, 0x07, 0xD4, // M1
};

BYTE code tQC_OD_CRC_TABLE_3[] =
{
    0x2B, 0x8E, 0x74, 0x1B, 0x6B, 0x88, // M1
    0xCD, 0x01, 0x4D, 0xA2, 0xA7, 0x8B, // M1
    0x0F, 0x19, 0x63, 0x39, 0x5D, 0x32, // M1
};

BYTE code tQC_OD_CRC_TABLE_4[] =
{
    0x2B, 0x8E, 0x74, 0x1B, 0x6B, 0x88, // M1
    0x11, 0x60, 0x84, 0x0C, 0x37, 0x23, // M1
    0x1E, 0x10, 0x3B, 0x23, 0xD1, 0x39, // M1
};

BYTE code tQC_OD_CRC_TABLE_5[] =
{
    0x2B, 0x8E, 0x74, 0x1B, 0x6B, 0x88, // M1
    0x39, 0x8E, 0x08, 0x3E, 0xA3, 0x07, // M1
    0xA6, 0x65, 0x80, 0xB2, 0xD6, 0xC2, // M1
};

BYTE code tQC_OD_CRC_TABLE_6[] =
{
    0xD6, 0x66, 0xEA, 0x34, 0x70, 0x39, // M1
    0x24, 0x91, 0x90, 0xD8, 0x59, 0x42, // M1
    0xA1, 0xE7, 0xFE, 0x19, 0xF0, 0x2E, // M1
};

BYTE code tQC_OD_CRC_TABLE_7[] =
{
    0xD6, 0x66, 0xEA, 0x34, 0x70, 0x39, // M1
    0x4A, 0x23, 0x7A, 0x00, 0x1F, 0x61, // M1
    0x8F, 0x41, 0xAD, 0x69, 0x58, 0x74, // M1
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
StructDdr1MemorySizeInfo g_stDdr1MemorySizeInfo;
#endif

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
bit ScalerQCFRCTest(void);
bit ScalerQCRotationTest(void);
void ScalerQCFRCControl(const StructSDRAMDataInfo *pstFIFOSize);
void ScalerQCFRCInputCtrl(WORD usHorSize, WORD usVerSize);
void ScalerQCFRCDisplayCtrl(WORD usHorSize, WORD usVerSize);
void ScalerQCFRCCompareIHFandDHF(WORD usVerSize);
void ScalerQCFRCAdjustIVS2DVSDelay(WORD usFRCVerSize);
void ScalerQCRotationControl(const StructSDRAMDataInfo *pstFIFOSize);
WORD ScalerQCFRCCalculatePreReadLine(WORD usFRCVerSize);
DWORD ScalerQCMemoryCalculateNumberAndRemain(DWORD ulTotalSize, WORD usLength, bit bDummy);

void ScalerQCODDDomainPatternInit(void);
bit ScalerQCODTest(void);

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
    bit ScalerQCDDRTest(void);
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
    bit ScalerQCSDRAMTest(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Scale Down Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCFRCTest(void)
{
    BYTE ucData = 0;
    StructSDRAMDataInfo stFIFOSize;

    stFIFOSize.usInputHWidth = 1280;
    stFIFOSize.usInputVHeight = 1024;
    stFIFOSize.usOutputHWidth = 1280;
    stFIFOSize.usOutputVHeight = 1024;

    ScalerMemorySetFIFOFreq(_SCALER_FIFO_FREQ_MPLL);

    DebugMessageQC("5. FRC Start", 0x00);

    ScalerQCIDomainRandomGenOn(_GRAY);
    ScalerFRCControl(&stFIFOSize);
    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_M_DOMAIN_CRC, _IMD_CRC_M_AFTER_FIFO, _M1, tFRC_CRCTable, 1));

    ScalerQCIDomainRandomGenOff();

    DebugMessageQC("5. FRC End", 0x00);
    if(ucData == 0x00)
    {
        DebugMessageQC("6. FRC PASS", 0x00);
        return _TEST_PASS;
    }
    else
    {
        DebugMessageQC("6. FRC Mode", 0x01);
        DebugMessageQC("6. FRC FAIL", 0x00);
       return _TEST_FAIL;
    }
}

//--------------------------------------------------
// Description  : Scale Down Test
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCRotationTest(void)
{
    BYTE ucData = 0;
    StructSDRAMDataInfo stFIFOSize;

    stFIFOSize.usInputHWidth = 1280;
    stFIFOSize.usInputVHeight = 1024;
    stFIFOSize.usOutputHWidth = 1280;
    stFIFOSize.usOutputVHeight = 1024;

    DebugMessageQC("5. rotation Start", 0x00);
    SET_ROT_TYPE(_ROT_CW180);

    ScalerQCIDomainRandomGenOn(_GRAY);

    ScalerQCRotationControl(&stFIFOSize);

    ucData = (ucData | (BYTE)ScalerQCCRCCompare(_M_DOMAIN_CRC, _IMD_CRC_M_AFTER_FIFO, _M1, tRotation_CRCTable, 1));

    ScalerQCIDomainRandomGenOff();

    SET_ROT_TYPE(_ROT_DISABLE);

    ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7 | _BIT1 | _BIT0), 0x00);

    DebugMessageQC("5. Rotation End", 0x00);

    if(ucData == 0x00)
    {
        DebugMessageQC("6. Rotation PASS", 0x00);
        return 0;
    }
    else
    {
        DebugMessageQC("6. Rotation Mode", 0x01);
        DebugMessageQC("6. Rotation FAIL", 0x00);
        return 1;
    }
}


//--------------------------------------------------
// Description  : FRC control
// Input Value  : stFIFOSize --> FIFO size
// Output Value : None
//--------------------------------------------------
void ScalerQCFRCControl(const StructSDRAMDataInfo *pstFIFOSize)
{
    // -----------------------
    // Set FRC IVS2DVSDelay
    // -----------------------
    ScalerQCFRCAdjustIVS2DVSDelay(pstFIFOSize->usInputVHeight);

    // -----------------------
    // Consider Input Faster Or Slower
    // -----------------------
    ScalerQCFRCCompareIHFandDHF(pstFIFOSize->usInputVHeight);

    // -----------------------
    // Set Up FRC Capture
    // -----------------------
    ScalerQCFRCInputCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // -----------------------
    // Set Up FRC Display
    // -----------------------
    ScalerQCFRCDisplayCtrl(pstFIFOSize->usInputHWidth, pstFIFOSize->usInputVHeight);

    // Wait I-domain Stable Before FRC enable
    if(ScalerGlobalGetDBStatus() == _DISABLE)
    {
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);
    }

    // -----------------------
    // Enable FRC
    // -----------------------
    ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT0, _BIT0);

    // Enable Display double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

    // Wait _EVENT_IVS For FRC Run In Single Frame Buffer
    if(ScalerGlobalGetDBStatus() == _DISABLE)
    {
        ScalerTimerWaitForEvent(_EVENT_IVS);
        ScalerTimerWaitForEvent(_EVENT_IVS);
    }

    // -----------------------
    // Set Double / Single Frame Buffer
    // -----------------------
    // Wait _EVENT_IEN_START Before Double Frame Buffer Setting
    if(ScalerGlobalGetDBStatus() == _DISABLE)
    {
        ScalerTimerWaitForEvent(_EVENT_IEN_START);
    }

    // Set 3 Buffer Enable,and 2 Buffer Enable
    ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~_BIT7, 0x00);
    ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~_BIT7, 0x00);

    // Ser 1 frame
    ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0), 0x00);
    ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Enable Display double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

    if(ScalerGlobalGetDBStatus() == _DISABLE)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }

    if(GET_ROT_TYPE() == _ROT_CW180)
    {
        // Set Rotation DB enable
        ScalerSetBit(P5_F2_IN1_TEST, ~_BIT1, _BIT1);

        // Set CW180 Enable
        ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : IN1 FIFO Setting for FRC Mode
// Input Value  : ucHorSize --> Horizontal size
//                ucVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerQCFRCInputCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep_rot;
    StructMemoryLineBlockStep stStep;
    DWORD ulHorSize = 0;

    memset(&stStep, 0, sizeof(StructMemoryLineBlockStep));
    memset(&stStep_rot, 0, sizeof(StructMemoryLineBlockStep));

    if(GET_ROT_TYPE() == _ROT_CW180)
    {
        // Line mode
        ulHorSize = ScalerMemoryCalculateFrameLineTotalPixel(_LINE_MODE, usHorSize, usVerSize);

        // Set Line mode
        ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~_BIT4, 0x00);

        // Calculate Line Step And Block Step
        ScalerMemoryCalculateLineStepAndBlockStep(ulHorSize, usVerSize, &stStep);
        ScalerMemoryCalculateLineStepAndBlockStep(ulHorSize, usVerSize - 1, &stStep_rot);

        // One Line total pixel for MEMORY (unit : 64 bits)
        ulHorSize = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() % 64) ?
                    (((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
                    ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64);
    }
    else
    {
        // Frame mode
        ulHorSize = ScalerMemoryCalculateFrameLineTotalPixel(_FRAME_MODE, usHorSize, usVerSize);

        // Set Frame mode
        ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~_BIT4, _BIT4);

        stStep.ulBlockStep = ScalerMemoryAddressConversion(ulHorSize);

        // One Frame total pixel for MEMORY (unit : 64 bits)
        ulHorSize = ((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() % 64) ?
                    (((DWORD)usHorSize * usVerSize  * GET_MEMORY_DATA_BIT() / 64) + 1) :
                    ((DWORD)usHorSize * usVerSize  * GET_MEMORY_DATA_BIT() / 64);
    }

    // Double buffer, Block Step cannot have column and bank address.
    if((WORD)(stStep.ulBlockStep & 0x7FF) > 0)
    {
        stStep.ulBlockStep = ((((stStep.ulBlockStep >> 11) + 1) << 11) & 0xFFFFF800);
    }

    // Calculate Number, Length, and Remain
    PDATA_DWORD(0) = ScalerQCMemoryCalculateNumberAndRemain(ulHorSize, _FRC_ACCESS_WRITE_LENGTH, 1);
    // Set Water Level
    ScalerSetByte(P5_A8_IN1_WATER_LEVEL, _FRC_ACCESS_WRITE_LENGTH);

    // Set Number, Length, Remain (size = number x length +remain)
    ScalerSetByte(P5_A9_IN1_WR_NUM_H, pData[2]);
    ScalerSetByte(P5_AA_IN1_WR_NUM_L, pData[3]);
    ScalerSetByte(P5_AB_IN1_WR_LEN, _FRC_ACCESS_WRITE_LENGTH);
    ScalerSetByte(P5_AC_IN1_WR_REMAIN, pData[1]);

    // Set Capture addresss count = 0
    ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);

    if(GET_ROT_TYPE() == _ROT_CW180)
    {
        // Set Positive Order Address
        PDATA_DWORD(0) = 0x00;
        ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);
        ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
        ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
        ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
        DebugMessageFRC("-CW180 W_PoAddr1", PDATA_DWORD(0));

        // Set Reverse Order Address
        PDATA_DWORD(0) = stStep_rot.ulBlockStep; // last line address
        ScalerSetBit(P5_BA_IN1_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT2);
        ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, pData[1]);
        ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, pData[2]);
        ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, pData[3]);
        DebugMessageFRC("-CW180 W_RvAddr1", PDATA_DWORD(0));
    }
    else
    {
        // Set Address
        ScalerSetByte(P5_AD_IN1_MEM_ADDR_H, 0x00);
        ScalerSetByte(P5_AE_IN1_MEM_ADDR_M, 0x00);
        ScalerSetByte(P5_AF_IN1_MEM_ADDR_L, 0x00);
    }

    // Set Block Step
    ScalerSetByte(P5_B2_IN1_BLOCK_STEP_H, HIBYTE((WORD)(stStep.ulBlockStep >> 11)));
    ScalerSetByte(P5_B3_IN1_BLOCK_STEP_L, LOBYTE((WORD)(stStep.ulBlockStep >> 11)));

    // Set Line Step
    ScalerSetByte(P5_B0_IN1_LINE_STEP_H, HIBYTE(stStep.ulLineStep));
    ScalerSetByte(P5_B1_IN1_LINE_STEP_L, LOBYTE(stStep.ulLineStep));

    // Set line number
    ScalerSetBit(P5_B7_IN1_LINE_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usVerSize >> 8) & 0x0F);
    ScalerSetByte(P5_B8_IN1_LINE_NUM_L, LOBYTE(usVerSize));

    // disable freeze mode
    ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT2), 0x00);

    // Use IVS as synchronous reset
    ScalerSetBit(P5_B9_IN1_SDR_CTRL, ~(_BIT1), _BIT1);
}

//--------------------------------------------------
// Description  : MAIN FIFO Setting for FRC Mode
// Input Value  : usHorSize --> Horizontal size
//                usVerSize --> Vertical Size
// Output Value : None
//--------------------------------------------------
void ScalerQCFRCDisplayCtrl(WORD usHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep_rot;

    StructMemoryLineBlockStep stStep;
    DWORD ulHorSize = 0;
    WORD usPreReadLine = 0;

    memset(&stStep_rot, 0, sizeof(StructMemoryLineBlockStep));
    memset(&stStep, 0, sizeof(StructMemoryLineBlockStep));

    // Calculate Pre-read
    usPreReadLine = ScalerQCFRCCalculatePreReadLine(usVerSize);

    if(GET_ROT_TYPE() == _ROT_CW180)
    {
        // Line mode
        ulHorSize = ScalerMemoryCalculateFrameLineTotalPixel(_LINE_MODE, usHorSize, usVerSize);

        // Set Line mode
        ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~_BIT4, 0x00);

        // Calculate line step and block step
        ScalerMemoryCalculateLineStepAndBlockStep(ulHorSize, usVerSize, &stStep);
        ScalerMemoryCalculateLineStepAndBlockStep(ulHorSize, usVerSize - 1, &stStep_rot);

        // One Line total pixel for MEMORY (unit : 64 bits)
        ulHorSize = ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() % 64) ?
                    (((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
                    ((DWORD)usHorSize * GET_MEMORY_DATA_BIT() / 64);
    }
    else
    {
        // Frame mode
        ulHorSize = ScalerMemoryCalculateFrameLineTotalPixel(_FRAME_MODE, usHorSize, usVerSize);

        // Set Frame mode
        ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~_BIT4, _BIT4);

        stStep.ulBlockStep = ScalerMemoryAddressConversion(ulHorSize);

        // One Frame total pixel for MEMORY (unit : 64 bits)
        ulHorSize = ((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() % 64) ?
                    (((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() / 64) + 1) :
                    ((DWORD)usHorSize * usVerSize * GET_MEMORY_DATA_BIT() / 64);
    }

    // Double buffer, Block Step cannot have column and bank address.
    if((WORD)(stStep.ulBlockStep & 0x7FF) > 0)
    {
        stStep.ulBlockStep = ((((stStep.ulBlockStep >> 11) + 1) << 11) & 0xFFFFF800);
    }

    // Calculate Number, Length, and Remain
    PDATA_DWORD(0) = ScalerQCMemoryCalculateNumberAndRemain(ulHorSize, _FRC_ACCESS_READ_LENGTH, 0);

    // Set Block step
    ScalerSetByte(P5_CB_MN_BLOCK_STEP_H, HIBYTE((WORD)(stStep.ulBlockStep >> 11) & 0xFFFF));
    ScalerSetByte(P5_CC_MN_BLOCK_STEP_L, LOBYTE((WORD)(stStep.ulBlockStep >> 11) & 0xFFFF));

    // Set Pre-read
    ScalerSetByte(P5_BC_MN_PRRD_VST_H, HIBYTE(usPreReadLine));
    ScalerSetByte(P5_BD_MN_PRRD_VST_L, LOBYTE(usPreReadLine));

    // Set Pixel number
    ScalerSetBit(P5_BE_MN_PXL_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHorSize) & 0x0F));
    ScalerSetByte(P5_BF_MN_PXL_NUM_L, LOBYTE(usHorSize));

    // Set Water Level
    ScalerSetByte(P5_C0_MN_WTLVL, _FRC_ACCESS_READ_LENGTH);

    // Set Number, Length, Remain ( size = number x length +remain)
    ScalerSetByte(P5_C2_MN_READ_NUM_H, pData[2]);
    ScalerSetByte(P5_C3_MN_READ_NUM_L, pData[3]);
    ScalerSetByte(P5_C4_MN_READ_LEN, _FRC_ACCESS_READ_LENGTH);
    ScalerSetByte(P5_C5_MN_READ_REMAIN, pData[1]);

    if(GET_ROT_TYPE() == _ROT_CW180)
    {
        // Set Positive Order Address
        PDATA_DWORD(0) = 0x00;
        ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);
        ScalerSetByte(P5_C6_MN_READ_ADDR_H, pData[1]);
        ScalerSetByte(P5_C7_MN_READ_ADDR_M, pData[2]);
        ScalerSetByte(P5_C8_MN_READ_ADDR_L, pData[3]);
        DebugMessageFRC("-CW180 R_PoAddr1", PDATA_DWORD(0));

        // Set Reverse Order Address
        PDATA_DWORD(0) = stStep_rot.ulBlockStep; // last line address
        PDATA_DWORD(0) = (((PDATA_DWORD(0) & 0xFFFFFE00) >> 1) | (PDATA_DWORD(0) & 0x000000FF));
        ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), _BIT2);
        ScalerSetByte(P5_C6_MN_READ_ADDR_H, pData[1]);
        ScalerSetByte(P5_C7_MN_READ_ADDR_M, pData[2]);
        ScalerSetByte(P5_C8_MN_READ_ADDR_L, pData[3]);
        DebugMessageFRC("-CW180 R_RvAddr1", PDATA_DWORD(0));

        // Set Line step
        ScalerSetByte(P5_C9_MN_LINE_STEP_H, HIBYTE(stStep.ulLineStep));
        ScalerSetByte(P5_CA_MN_LINE_STEP_L, LOBYTE(stStep.ulLineStep));
    }
    else
    {
        // Set Display addresss count = 0
    ScalerSetBit(P5_C1_MN_MADDR_TOG_CTL, ~(_BIT3 | _BIT2), 0x00);

    // Set Read address
    ScalerSetByte(P5_C6_MN_READ_ADDR_H, 0x00);
    ScalerSetByte(P5_C7_MN_READ_ADDR_M, 0x00);
    ScalerSetByte(P5_C8_MN_READ_ADDR_L, 0x00);

    // Set Line step
    ScalerSetByte(P5_C9_MN_LINE_STEP_H, HIBYTE(stStep.ulLineStep));
    ScalerSetByte(P5_CA_MN_LINE_STEP_L, LOBYTE(stStep.ulLineStep));
    }

    // Set Line number
    ScalerSetBit(P5_CD_MN_LINE_NUM_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (usVerSize >> 8) & 0x0F);
    ScalerSetByte(P5_CE_MN_LINE_NUM_L, LOBYTE(usVerSize));

    // Use information from Capture
    ScalerSetBit(P5_CF_MN_DISP_CTRL, ~(_BIT2 | _BIT1), 0x00);

    // Set input slower than display
    ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT3, 0x00);

    // Enable Display double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

    // Wait double buffer
    if(ScalerGlobalGetDBStatus() == _DISABLE)
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : Compare which one of IHF and DHF is bigger, and see if they are too similar
// Input Value  : stFIFOSize    --> FIFO size
// Output Value : output is true when they are too similar
//--------------------------------------------------
void ScalerQCFRCCompareIHFandDHF(WORD usVerSize)
{
    usVerSize = usVerSize;

    // Set Input Slower Than Display
    ScalerSetBit(P5_CF_MN_DISP_CTRL, ~_BIT3, 0x00);

    // Write in double buffer
    ScalerSetBit(P5_D0_MN_SDR_STATUS, ~_BIT4, _BIT4);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    // Set Frame sync when FRC
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

}

//--------------------------------------------------
// Description  : Adjust IVS2DVS Delay for Aspect Ratio Function
// Input Value  : usFRCVerSize : FRC Veritcal Size
// Output Value : None
//--------------------------------------------------
void ScalerQCFRCAdjustIVS2DVSDelay(WORD usFRCVerSize)
{
    WORD usPreReadLine = ScalerFRCCalculatePreReadLine(usFRCVerSize);
    BYTE ucMargin = ScalerFRCIVS2DVSDelayMargin();
    DWORD ulIVStoDVSPixels = 0;

    PDATA_WORD(2) = (g_stMDomainInputData.usVHeight);

    PDATA_WORD(3) = ((DWORD)_MEASURE_CLK * 10 * PDATA_WORD(2) / g_ulInputActiveRegionBackUp * 10) +
                    (((DWORD)_MEASURE_CLK * 10 * PDATA_WORD(2)) % g_ulInputActiveRegionBackUp * 10 / g_ulInputActiveRegionBackUp) +
                    ((DWORD)_MEASURE_CLK * 100 / g_ulInputActiveRegionBackUp) -
                    ((DWORD)_MEASURE_CLK * 10 * (g_stMDomainInputData.usHTotal - g_stMDomainInputData.usHWidth) / g_ulInputActiveRegionBackUp / g_stMDomainInputData.usHTotal * 10);

    // DHFreq, unit: 0.01kHz
    PDATA_WORD(2) = ((DWORD)GET_D_CLK_FREQ() * 100 / g_stMDomainOutputData.usHTotal);

    // IVS2DVS line skip disable
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT3, _BIT3);

    if(GET_ROT_TYPE() == _ROT_CW180)
    {
        // Consider IDEN period and (DDEN + pre-read) period
        if(g_stMDomainInputData.usVHeight >= ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight - usPreReadLine) * PDATA_WORD(3) / PDATA_WORD(2)))
        {
            // Roundup: (IVS2DVS_delay_min + IVS2DVS_delay_max) / 2
            PDATA_WORD(0) = ((g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight) + g_stMDomainInputData.usVTotal);
            PDATA_WORD(0) = (PDATA_WORD(0) >> 1) + (PDATA_WORD(0) % 2);
        }
        else
        {
            // IVS2DVS delay max
            PDATA_WORD(0) = g_stMDomainInputData.usVTotal + g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight -
                            ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight) * PDATA_WORD(3) / PDATA_WORD(2)) -
                            ((((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight) * PDATA_WORD(3) % PDATA_WORD(2)) != 0x00) ? 1 : 0);

            // Rounddown: (IVS2DVS_delay_min + IVS2DVS_delay_max) / 2
            PDATA_WORD(0) = (((g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight) + PDATA_WORD(0)) / 2);
        }

        PDATA_WORD(0) -= ((DWORD)usPreReadLine * PDATA_WORD(3) / PDATA_WORD(2));
    }
    else
    {
        // Consider IDEN period and (DDEN + pre-read) period
        if(g_stMDomainInputData.usVHeight >= ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight - usPreReadLine) * PDATA_WORD(3) / PDATA_WORD(2)))
        {
            // (IVStart + IDEN) Period
            PDATA_WORD(0) = (g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight);

            // (DVStart + DDEN) Period
            PDATA_WORD(1) = ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight) * PDATA_WORD(3) / PDATA_WORD(2));
        }
        else
        {
            // IVStart Period
            PDATA_WORD(0) = g_stMDomainInputData.usVStart;

            // FRC_Display pre-read Period
            PDATA_WORD(1) = (DWORD)usPreReadLine * PDATA_WORD(3) / PDATA_WORD(2);
        }

        if(PDATA_WORD(0) > PDATA_WORD(1))
        {
            PDATA_WORD(0) = PDATA_WORD(0) - PDATA_WORD(1) + ucMargin;
        }
        else
        {
            PDATA_WORD(0) = ucMargin;
        }

        PDATA_WORD(1) = ((g_stMDomainInputData.usVStart + ucMargin) > ((DWORD)usPreReadLine * PDATA_WORD(3) / PDATA_WORD(2))) ? ((g_stMDomainInputData.usVStart + ucMargin) - ((DWORD)usPreReadLine * PDATA_WORD(3) / PDATA_WORD(2))) : 0;

        if(PDATA_WORD(1) > PDATA_WORD(0))
        {
            PDATA_WORD(0) = PDATA_WORD(1);
        }
    }
    if((PDATA_WORD(0) > 0xF00) || (PDATA_WORD(0) == 0))
    {
        PDATA_WORD(0) = 0x01;
    }

    // Disable Frame Sync Fine Tune
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);

    ulIVStoDVSPixels = (DWORD)PDATA_WORD(0) * g_stMDomainInputData.usHTotal;
    PDATA_WORD(2) = (ulIVStoDVSPixels / g_stMDomainInputData.usHTotal);
    PDATA_WORD(3) = (ulIVStoDVSPixels - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> 4;
    PDATA_WORD(4) = 0x0000;

    pData[10] = ulIVStoDVSPixels - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << 4);
    pData[11] = 0x00;

    //-------------------------------------------------
    // Apply updated Delay
    //-------------------------------------------------
    // IVS2DVS line delay, unit: line
    ScalerSetByte(P0_3E_IVS2DVS_DLY_LINE_H, (pData[4] & 0x1F));
    ScalerSetByte(P0_40_IVS2DVS_DLY_LINE_L, pData[5]);

    // IVS2DVS 16iclk1 delay, unit: 16 pixel
    PDATA_WORD(3) -= (PDATA_WORD(3) >= 1) ? 1 : 0;
    SET_IVS2DVS_DELAY_16ICLK1(PDATA_WORD(3));

    // IVS2DVS 16iclk2 delay, unit: 16 pixel
    PDATA_WORD(4) -= (PDATA_WORD(4) >= 1) ? 1 : 0;
    SET_IVS2DVS_DELAY_16ICLK2(PDATA_WORD(4));

    // IVS2DVS iclk1 delay, unit: 1 pixel
    ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0xF0, ((pData[10] & 0x0F) << 4));

    // IVS2DVS iclk2 delay, unit: 1 pixel
    ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0x0F, (pData[11] & 0x0F));
}

//--------------------------------------------------
// Description  : FRC control
// Input Value  : stFIFOSize --> FIFO size
// Output Value : None
//--------------------------------------------------
void ScalerQCRotationControl(const StructSDRAMDataInfo *pstFIFOSize)
{
    // Set Roation Enable
    // Set Clock Gating
    ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set Rotation Enable
    ScalerSetBit(P20_F0_ROTATION_CTRL0, ~(_BIT7), _BIT7);

    // Set Rotation Source Pixel Number
    ScalerSetBit(P20_F1_ROTATION_IN_WID_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pstFIFOSize->usInputHWidth >> 8) & 0x0F);
    ScalerSetByte(P20_F2_ROTATION_IN_WID_L, (pstFIFOSize->usInputHWidth & 0xFF));

    // input faster than display
    ScalerSetBit(P5_F3_MN_TEST, ~_BIT1, _BIT1);

    ScalerQCFRCControl(pstFIFOSize);
}

//--------------------------------------------------
// Description  : Calculate FRC Pre-read Line
// Input Value  : usFRCVerSize --> FRC Output Vertical Size
// Output Value : The line after DVS that FRC display start to access
//--------------------------------------------------
WORD ScalerQCFRCCalculatePreReadLine(WORD usFRCVerSize)
{
    // preread = den_start - _PRE_READ_MEMORY x VSU factor - 1
    // VSU >= 1
    usFRCVerSize = (((DWORD)g_stMDomainOutputData.usVHeight * 10) / usFRCVerSize) * _PRE_READ_MEMORY + 1;
    usFRCVerSize = ((usFRCVerSize % 10) ? (usFRCVerSize / 10 + 1) : (usFRCVerSize / 10));

    return ((g_stMDomainOutputData.usVStart > usFRCVerSize) ? ((g_stMDomainOutputData.usVStart - usFRCVerSize)) : (0));
}

//--------------------------------------------------
// Description  : Calculate the number and remain
// Input Value  : ulTotalSize --> Image total size
//                ucLength --> Length of SDRAM access
// Output Value : Number and Remain
//--------------------------------------------------
DWORD ScalerQCMemoryCalculateNumberAndRemain(DWORD ulTotalSize, WORD usLength, bit bDummy)
{
    if(bDummy)
    {
        /// In 6432, System Bridge data bus is 128 bits,
        ///   but its burst length and address unit is still 64 bits.
        ///   So NUM, LEN, and REM must be a multiple of 4.
        if((ulTotalSize & 0x03) != 0x00)
        {
            (ulTotalSize += 4 - (ulTotalSize & 0x03));
        }
    }

    if((ulTotalSize % usLength) != 0)
    {
        PDATA_WORD(0) = ulTotalSize / usLength; // Number
        PDATA_WORD(1) = ulTotalSize % usLength; // Remain
    }
    else
    {
        ulTotalSize = ulTotalSize - usLength;
        PDATA_WORD(0) = ulTotalSize / usLength; // Number
        PDATA_WORD(1) = usLength;               // Remain
    }

    return (((DWORD)PDATA_WORD(1) << 16) | PDATA_WORD(0));
}


/*
//--------------------------------------------------
// Description  : Calculate the Line Step and Block Step
// Input Value  : usHorSize --> Horizontal size (unit : 64 bits)
//                usVerSize --> Vertical size
// Output Value : Line Step and Block Step
//--------------------------------------------------
StructMemoryLineBlockStep ScalerQCMemoryCalculateLineStepAndBlockStep(DWORD ulHorSize, WORD usVerSize)
{
    StructMemoryLineBlockStep stStep;

    stStep.ulLineStep = ulHorSize;

    if((stStep.ulLineStep & 0x03) != 0x00)
    {
        stStep.ulLineStep += (4 - (stStep.ulLineStep & 0x03));
    }

#if((_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_2PCS) || (_MEMORY_SIZE_CONFIG == _2G_16BIT_GDDR3_2PCS))
    // 1024column x 32bit = 512 x 64bit. (64bit : FRC access unit)
    PDATA_WORD(0) = stStep.ulLineStep / 512;  // Row, Bank
    PDATA_WORD(1) = stStep.ulLineStep % 512;  // Column
    stStep.ulLineStep = (((DWORD)PDATA_WORD(0) << 9) | PDATA_WORD(1));
#elif((_MEMORY_SIZE_CONFIG == _1G_16BIT_DDR3_1PC) || (_MEMORY_SIZE_CONFIG == _2G_16BIT_GDDR3_1PC))
    // 1024column x 16bit = 256 x 64bit (64bit : FRC access unit)
    PDATA_WORD(0) = stStep.ulLineStep / 256;  // Row, Bank
    PDATA_WORD(1) = stStep.ulLineStep % 256;  // Column
    stStep.ulLineStep = (((DWORD)PDATA_WORD(0) << 8) | PDATA_WORD(1));
#else
    stStep.ulLineStep = stStep.ulLineStep * 64 / _MEMORY_BUS_WIDTH;
#endif

    stStep.ulBlockStep = (DWORD)usVerSize * stStep.ulLineStep;

    stStep.ulLineStep = ScalerMemoryAddressConversion(stStep.ulLineStep);
    stStep.ulBlockStep = ScalerMemoryAddressConversion(stStep.ulBlockStep);

    return stStep;
}

*/

//--------------------------------------------------
// Description  : Initialize DPG Pattern for OD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerQCODDDomainPatternInit(void)
{
    ScalerSetByte(P7_F0_DISP_PG_R_CTRL, 0xC1);
    ScalerSetByte(P7_F1_DISP_PG_G_CTRL, 0x01);
    ScalerSetByte(P7_F2_DISP_PG_B_CTRL, 0x01);
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, 0x00);
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, 0x00);
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, 0x00);
    ScalerSetByte(P7_F6_DISP_PG_PIXEL_DELTA_H, 0x01);
    ScalerSetByte(P7_F7_DISP_PG_LINE_DELTA_H, 0x01);

    ScalerSetByte(P7_FB_D_PG_CTRL_0, 0x40);
    ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L, 0x15);
    ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL, 0x00);
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x00);
}

//--------------------------------------------------
// Description  : OD Test
// Input Value  : None
// Output Value : _TEST_PASS or _TEST_FAIL
//--------------------------------------------------
bit ScalerQCODTest(void)
{
    BYTE ucData = 0;

    DebugMessageQC("5. OD Start", 0x00);

    //==================================================
    // OD QC Preprocess
    //==================================================
    // Disable token ring FRC client arbitration
    ScalerSetByte(P4_AC_SDR_RSC_CAP1, 0x00);
    ScalerSetByte(P4_AE_SDR_RSC_MAIN, 0x00);

    // Enable token ring OD client arbitration
    ScalerSetByte(P4_B0_SDR_RSC_RTC_RD, 0xAA);
    ScalerSetByte(P4_B1_SDR_RSC_RTC_WR, 0x55);

    // Load OD LUT Table
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7), 0x00);
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7), _BIT7);
    ScalerBurstWrite(tQC_OD_8BIT_TABLE, sizeof(tQC_OD_8BIT_TABLE), GET_CURRENT_BANK_NUMBER(), P3_C0_LS_LUT_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    if(ScalerGetBit(P3_BF_LS_LUT_CTRL, _BIT1) != 0x00)
    {
        DebugMessageQC("5. 3.OD Write LUT Fail", 0x00);
    }

    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7), 0x00);

    // Memory Start Address and R/W FIFO Setting
    ScalerSetByte(P3_D1_LS_DDR_FIFO_WTLVL_W_L, 0x30);
    ScalerSetByte(P3_D3_LS_DDR_FIFO_WTLVL_R_L, 0x60);
    ScalerSetByte(P3_D7_LS_DDR_FIFO_RW_LEN_L, 0x60);
    ScalerSetByte(P3_DB_LS_DDR_START_ADDR_H, 0x00);
    ScalerSetByte(P3_DC_LS_DDR_START_ADDR_M, 0x00);
    ScalerSetByte(P3_DD_LS_DDR_START_ADDR_L, 0x00);

    // DPG On
    ScalerQCDDomainRandomGenOn(_MASS, _BIT_MODE_10);

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
    //
    // Memory usage: 8 bit/pixel
    //==================================================
    DebugMessageQC("5. Mode_0", 0x00);

    // Initialize DPG
    ScalerQCODDDomainPatternInit();

    // Memory R/W Num & Remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x12);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0xBF);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // OD Setting
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

    ScalerTimerWaitForEvent(_EVENT_DEN_START);

    // Enable OD (DB effective when DVS falling occurs)
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Set DPG pattern reset frame num = 4
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x03);

    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1, tQC_OD_CRC_TABLE_0, 3) << 0);

    // Set DPG pattern reset frame num = 1
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x00);
    // Disable OD
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
    ScalerTimerWaitForEvent(_EVENT_DVS);

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
    //
    // Memory usage: 9 bit/pixel
    //==================================================
    DebugMessageQC("5. Mode_1", 0x00);

    // Initialize DPG
    ScalerQCODDDomainPatternInit();

    // Memory R/W Num & Remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x15);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x17);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // OD Setting
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

    ScalerTimerWaitForEvent(_EVENT_DEN_START);

    // Set DPG pattern reset frame num = 4
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x03);

    // Enable OD (DB effective when DVS falling occurs)
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1, tQC_OD_CRC_TABLE_1, 3) << 0);

    // Set DPG pattern reset frame num = 1
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x00);
    // Disable OD
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
    ScalerTimerWaitForEvent(_EVENT_DVS);

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
    //
    // Memory usage: 9.25 bit/pixel
    //==================================================
    DebugMessageQC("5. Mode_2", 0x00);

    // Initialize DPG
    ScalerQCODDDomainPatternInit();

    // Memory R/W Num & Remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x15);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0xAD);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // OD Setting
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

    ScalerTimerWaitForEvent(_EVENT_DEN_START);

    // Set DPG pattern reset frame num = 4
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x03);

    // Enable OD (DB effective when DVS falling occurs)
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1, tQC_OD_CRC_TABLE_2, 3) << 0);

    // Set DPG pattern reset frame num = 1
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x00);
    // Disable OD
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
    ScalerTimerWaitForEvent(_EVENT_DVS);

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
    //
    // Memory usage: 9.5 bit/pixel
    //==================================================
    DebugMessageQC("5. Mode_3", 0x00);

    // Initialize DPG
    ScalerQCODDDomainPatternInit();

    // Memory R/W Num & Remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x16);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x43);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // OD Setting
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

    ScalerTimerWaitForEvent(_EVENT_DEN_START);

    // Set DPG pattern reset frame num = 4
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x03);

    // Enable OD (DB effective when DVS falling occurs)
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1, tQC_OD_CRC_TABLE_3, 3) << 0);

    // Set DPG pattern reset frame num = 1
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x00);
    // Disable OD
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
    ScalerTimerWaitForEvent(_EVENT_DVS);

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
    //
    // Memory usage: 9.5 bit/pixel
    //==================================================
    DebugMessageQC("5. Mode_4", 0x00);

    // Initialize DPG
    ScalerQCODDDomainPatternInit();

    // Memory R/W Num & Remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x16);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x43);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // OD Setting
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

    ScalerTimerWaitForEvent(_EVENT_DEN_START);

    // Set DPG pattern reset frame num = 4
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x03);

    // Enable OD (DB effective when DVS falling occurs)
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1, tQC_OD_CRC_TABLE_4, 3) << 0);

    // Set DPG pattern reset frame num = 1
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x00);
    // Disable OD
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    //==================================================
    // Pattern 5:
    // RGBtoYUV
    // Comp: SP1x4, average Mode
    // Src Res: prev->8bit, curr->6bit
    // Decomp: interp. mode
    // YUVtoRGB
    // Lvl Est: est_gain=8, est_value=1, est_range=8_pixels
    // HLW: full mode
    //
    // Memory usage: 7 bit/pixel
    //==================================================
    DebugMessageQC("5. Mode_5", 0x00);

    // Initialize DPG
    ScalerQCODDDomainPatternInit();

    // Memory R/W Num & Remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x10);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x67);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // OD Setting
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

    ScalerTimerWaitForEvent(_EVENT_DEN_START);

    // Set DPG pattern reset frame num = 4
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x03);

    // Enable OD (DB effective when DVS falling occurs)
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1, tQC_OD_CRC_TABLE_5, 3) << 0);

    // Set DPG pattern reset frame num = 1
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x00);
    // Disable OD
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    //==================================================
    // Pattern 6:
    // RGBtoYUV
    // Comp: YUV444to422, average Mode, uv type 1
    // Src Res: prev->4bit+UV round, curr->8bit
    // Decomp: interp. mode
    // Lvl Est: est_gain=8, est_value=2, asymmetric
    // HLW: inside HLW
    //
    // Memory usage: 6 bit/pixel
    //==================================================
    DebugMessageQC("5. Mode_6", 0x00);

    ScalerQCHighlightWindowOn();

    // Initialize DPG
    ScalerQCODDDomainPatternInit();

    // Memory R/W Num & Remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x0E);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x0F);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // OD Setting
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

    ScalerTimerWaitForEvent(_EVENT_DEN_START);

    // Set DPG pattern reset frame num = 4
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x03);

    // Enable OD (DB effective when DVS falling occurs)
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1, tQC_OD_CRC_TABLE_6, 3) << 0);

    // Set DPG pattern reset frame num = 1
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x00);
    // Disable OD
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    //==================================================
    // Pattern 7:
    // RGBtoYUV
    // Comp: YUV444to422, average Mode, uv type 1
    // Src Res: prev->4bit+UV round, curr->8bit
    // Decomp: interp. mode
    // Lvl Est: est_gain=8, est_value=2, asymmetric
    // HLW: outside HLW
    //
    // Memory usage: 6 bit/pixel
    //==================================================
    DebugMessageQC("5. Mode_7", 0x00);

    ScalerQCHighlightWindowOn();

    // Initialize DPG
    ScalerQCODDDomainPatternInit();

    // Memory R/W Num & Remain
    ScalerSetByte(P3_D4_LS_DDR_FIFO_RW_NUM_H, 0x0E);
    ScalerSetByte(P3_D5_LS_DDR_FIFO_RW_NUM_L, 0x0F);
    ScalerSetByte(P3_D9_LS_DDR_FIFO_RW_REMAIN_L, 0x60);
    // OD Setting
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

    ScalerTimerWaitForEvent(_EVENT_DEN_START);

    // Set DPG pattern reset frame num = 4
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x03);

    // Enable OD (DB effective when DVS falling occurs)
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ucData |= ((BYTE)ScalerQCCRCCompare(_D_DOMAIN_CRC, _IMD_CRC_D_AFTER_OD, _M1, tQC_OD_CRC_TABLE_7, 3) << 0);

    // Set DPG pattern reset frame num = 1
    ScalerSetByte(P7_FF_D_PATTERN_RESET, 0x00);
    // Disable OD
    ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
    ScalerTimerWaitForEvent(_EVENT_DVS);
    ScalerTimerWaitForEvent(_EVENT_DVS);

    ScalerQCHighlightWindowOff();
    ScalerQCDDomainPatternGenOff();

    //==================================================
    // OD QC Postprocess
    //==================================================
    // Enable token ring FRC client arbitration
    ScalerSetByte(P4_AC_SDR_RSC_CAP1, 0x44);
    ScalerSetByte(P4_AE_SDR_RSC_MAIN, 0x88);

    // Disable token ring OD client arbitration
    ScalerSetByte(P4_B0_SDR_RSC_RTC_RD, 0x00);
    ScalerSetByte(P4_B1_SDR_RSC_RTC_WR, 0x00);


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

    return _TEST_PASS;
}

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
//--------------------------------------------------
// Description  : DDR1 FT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCDDRTest(void)
{
    BYTE ucCount = 0;

//*************************************************//
//g_pucDDR1DelayChain[0] = g_ucTxClkDelayChain;         //7
//g_pucDDR1DelayChain[1] = g_ucTxDqsDelayChain;         //7
//g_pucDDR1DelayChain[2] = g_ucRxIenDelayChain;         //18
//g_pucDDR1DelayChain[3] = g_ucRxDqs0RiseDelayChain;    //9
//g_pucDDR1DelayChain[4] = g_ucRxDqs0FallDelayChain;    //9
//g_pucDDR1DelayChain[5] = g_ucRxDqs1RiseDelayChain;    //9
//g_pucDDR1DelayChain[6] = g_ucRxDqs1FallDelayChain;    //9
//*************************************************//

    DebugMessageQC("QC DDR1 Phase Test Start", 0);

    ScalerTimerDelayXms(20);

    for(ucCount = 0; ucCount <= 6; ucCount++)
    {
        DebugMessageQC("Test Phase", g_ucDDR1_QC_GOOD_PHASE_COUNT_1PC[ucCount]);
        
        if(g_ucDDR1_QC_GOOD_PHASE_COUNT_1PC[ucCount] == 0)
        {
            DebugMessageQC("QC DDR1 Phase Test Fail", ucCount);
            return _TEST_FAIL;
        }
    }

    DebugMessageQC("QC DDR1 Phase Test PASS", 0);
    return _TEST_PASS;
}
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
//--------------------------------------------------
// Description  : SDRM FT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerQCSDRAMTest(void)
{
    BYTE ucCount = 0;

//*************************************************//
//g_pucSdramDelayChain[0] = g_ucTxClkDelayChain;
//g_pucSdramDelayChain[1] = g_ucRxClkHDelayChain;
//g_pucSdramDelayChain[2] = g_ucRxClkLDelayChain;
//*************************************************//

    DebugMessageQC("QC SDR Phase Test Start", 0);

    for(ucCount = 0; ucCount <= 2; ucCount++)
    {
        DebugMessageQC("Test Phase", g_ucSDR_QC_GOOD_PHASE_COUNT[ucCount]);
        
        if(g_ucSDR_QC_GOOD_PHASE_COUNT[ucCount] == 0)
        {
            DebugMessageQC("QC SDR Phase Test Fail", 0);
            return _TEST_FAIL;
        }
    }

    DebugMessageQC("QC SDR Phase Test PASS", 0);
    return _TEST_PASS;
    
}
#endif
#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)

