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
// ID Code      : ScalerSDRAM.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_SDRAM__

#include "ScalerFunctionInclude.h"

#if(_SDRAM_PHASE_CALIBRATION == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _SDRAM_MCU_ALL_PHASE_CHECK                  _OFF

#define _SDRAM_MCU_COMMAND_NOP_FINISH               0
#define _SDRAM_MCU_COMMAND_PRECHARGE                0x20
#define _SDRAM_MCU_COMMAND_AUTO_REFRESH             0x40
#define _SDRAM_MCU_COMMAND_LOAD_MODE_REGISTER       0x60
#define _SDRAM_MCU_COMMAND_WRITE                    0x80
#define _SDRAM_MCU_COMMAND_READ                     0xA0

#define _SDRAM_MCU_ONLINE_START_LOOP                60
#define _SDRAM_MCU_ONLINE_END_LOOP                  1

#define _SDRAM_ONLINE_TAP_DIFF_THRESHOLD            10

#define _SDRAM_PHASE_CALIBRATION_OPTIMIZATION       _OFF
#define _SDRAM_PHASE_CALIBRATION_2T                 _OFF

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _SDRAM_TX = 0,
    _SDRAM_RX_H,
    _SDRAM_RX_L,
} EnumSDRAMClk;

//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tSDRAM_PATTERN[8] = {0x33, 0x33, 0x55, 0x55, 0xaa, 0xaa, 0xcc, 0xcc};

WORD code tSDRAM_FINE_DLY_REG[3] =
{
    P4_C1_TX_CLK_DLY2,
    P4_C3_SDR_RX_CLK_DLY2,
    P4_C5_SDR_RX_CLK_DLY4,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucPhaseCount;
BYTE g_ucWrPhasePoint;
BYTE g_pucSdramInitialPhase[3];
BYTE g_pucSdramDelayChain[3];
BYTE g_pucSdramOnLineDelayChain[3];

#if(_SDRAM_PHASE_CALIBRATION_OPTIMIZATION == _ON)
BYTE g_ucTempDiffPhase;
BYTE g_ucMaxDiffPhase;
BYTE g_ucTempBestPhase;
BYTE g_ucBestPhase;
BYTE g_ucTempCoarseDly;
BYTE g_ucBestCoarseDly;
BYTE g_ucTempCASLatn;
BYTE g_ucBestCASLatn;
#endif
//*************************************************//
//g_pucSdramDelayChain[0] = g_ucTxClkDelayChain;
//g_pucSdramDelayChain[1] = g_ucRxClkHDelayChain;
//g_pucSdramDelayChain[2] = g_ucRxClkLDelayChain;
//*************************************************//
#endif // End of #if(_SDRAM_PHASE_CALIBRATION == _ON)

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
void ScalerSdramPowerControl(bit bOn);
void ScalerSdramMclkGenReset(void);
void ScalerSdramSystemInitial(void);
void ScalerSdramControlReset(void);
#endif

#if(_SDRAM_PHASE_CALIBRATION == _ON)
void ScalerSdramTokenRingSet(void);
void ScalerSdramSearchPhase(void);
#if(_SDRAM_PHASE_CALIBRATION_OPTIMIZATION == _OFF)
void ScalerSdramSearchPhaseCheck(void);
#endif
void ScalerSdramTxClkSearchPhase(void);
void ScalerSdramRxClkSearchPhase(void);
void ScalerSdramTxClkCalibrationEnable(bit bEn);
void ScalerSdramRxClkCalibrationEnable(bit bEn);
bit ScalerSdramMcuReadWriteCheck(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, bit bReadSlowDown);
void ScalerSdramWriteToFifo(void);
void ScalerSdramReadFromFifo(void);
void ScalerSdramClearFifo(void);
bit ScalerSdramCheckCommandFinish(void);
void ScalerSdramOnLinePhaseCntCheck(void);
void ScalerSdramOnLinePhaseCalibration(bit bEn);
void ScalerSdramRestoreInitialPhase(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
//--------------------------------------------------
// Description  : DDR Power On/Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramPowerControl(bit bOn)
{
#if(_MPLL_STRUCT_TYPE != _MPLL_STRUCT_COMBO_M2PLL)
    // Set MPLL CLK
    ScalerPLLSetMPLLFreq((DWORD)_MEMORY_PLL_CLOCK * 1000);
#endif

    // Set Mclk Gen Reset Align MPLL
    ScalerSdramMclkGenReset();

    if(bOn == _ON)
    {
        // Set Sdram Module Power Status
        ScalerSdramPowerEnable(_ON);

        // Set Sdram System Initial
        ScalerSdramSystemInitial();
    }
    else
    {
        // Set Sdram Module Power Status
        ScalerSdramPowerEnable(_OFF);

        // Set Sdram Module Power Status
        ScalerSdramMpllPowerDown();
    }
}

//--------------------------------------------------
// Description  : SDRAM Mclk Gen Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramMclkGenReset(void)
{
    // Set Mclk Gen Local Reset
    ScalerSetBit(P4_A8_SDR_CLK_ALIGN, ~_BIT7, _BIT7);

    // Delay Time us [300,x] Waiting for SDRAM Mclk Reset
    DELAY_XUS(300);

    // Set Mclk Gen Local Reset
    ScalerSetBit(P4_A8_SDR_CLK_ALIGN, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Sdram system initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramSystemInitial(void)
{
    // Set Sdram Pinshare Initial
    ScalerSdramPinshareInitial();

    // Set Sdram Module Active to Read and Write delay
    ScalerSetBit(P4_A1_SDR_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));

    // Set Sdram Module CAS Latency
    ScalerSetBit(P4_A2_SDR_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT5 | _BIT2));

    // Set Sdram Auto Refresh Time
    ScalerSetByte(P4_A3_SDR_AREF_TIME, 0x0D);

    // Set Sdram Precharge Duty Cycle
    ScalerSetBit(P4_A4_SDR_PRCG, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set Sdram Memory Type & Control CAS Latency = 1
    ScalerSetBit(P4_A5_SDR_MEM_TYPE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

    // Set Sdram Slew Rate SDRAM mode
    ScalerSetBit(P4_A6_SDR_SLEW_RATE, ~_BIT7, _BIT7);

    // Set Sdram Refresh time 15.6us
    ScalerSetByte(P4_A7_SDR_AREF_CNT, 0x0D);

#if(_SDRAM_PHASE_CALIBRATION == _ON)
    ScalerSdramTokenRingSet();
#endif

    // Set Sdram Read SRAM Length
    ScalerSetByte(P4_BD_SDR_MCU_RD_LEN, 0x04);

    // Set Sdram Control Reset
    ScalerSdramControlReset();

    // Set Sdram Control Reset Ready
    ScalerTimerPollingFlagProc(5, P4_B5_SDR_ABTR_STATUS1, _BIT0, _TRUE);
}

//--------------------------------------------------
// Description  : Sdram Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramControlReset(void)
{
    ScalerSetBit(P4_A4_SDR_PRCG, ~_BIT4, _BIT4);
    ScalerSetBit(P4_A4_SDR_PRCG, ~_BIT4, 0x00);

    // Delay Time us [300,x] Waiting for SDRAM Control Reset
    DELAY_XUS(300);

    // Set Mclk Gen Reset Align MPLL
    ScalerSdramMclkGenReset();
}

#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)

#if(_SDRAM_PHASE_CALIBRATION == _ON)
//--------------------------------------------------
// Description  : Sdram Token Ring Set
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramTokenRingSet(void)
{
    ScalerSetByte(P4_AA_SDR_RSC_AREF, 0xFF);

#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
    ScalerSetByte(P4_AB_SDR_RSC_MCU, 0x20);
#elif(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
    ScalerSetByte(P4_AB_SDR_RSC_MCU, 0x00);
#endif

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _OFF))
    ScalerSetByte(P4_AC_SDR_RSC_CAP1, 0x00);
    ScalerSetByte(P4_AE_SDR_RSC_MAIN, 0x00);
    ScalerSetByte(P4_B0_SDR_RSC_RTC_RD, 0x44);
    ScalerSetByte(P4_B1_SDR_RSC_RTC_WR, 0x88);
#elif((_OD_SUPPORT == _OFF) && (_FRC_SUPPORT == _ON))
    ScalerSetByte(P4_AC_SDR_RSC_CAP1, 0x44);
    ScalerSetByte(P4_AE_SDR_RSC_MAIN, 0x88);
    ScalerSetByte(P4_B0_SDR_RSC_RTC_RD, 0x00);
    ScalerSetByte(P4_B1_SDR_RSC_RTC_WR, 0x00);
#elif((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
    ScalerSetByte(P4_AC_SDR_RSC_CAP1, 0x40);
    ScalerSetByte(P4_AE_SDR_RSC_MAIN, 0x80);
    ScalerSetByte(P4_B0_SDR_RSC_RTC_RD, 0x04);
    ScalerSetByte(P4_B1_SDR_RSC_RTC_WR, 0x08);
#endif
}

//--------------------------------------------------
// Description  : Sdram Search Phase
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramSearchPhase(void)
{
#if(_SDRAM_PHASE_CALIBRATION_OPTIMIZATION == _ON)
    BYTE ucTempWrPhasePoint = 0;
    BYTE ucCASLat = 0;
    BYTE ucCoarseDly = 0;

    // Tx Clk Search Phase
    for(ucTempWrPhasePoint = 0; ucTempWrPhasePoint < 2; ucTempWrPhasePoint++)
    {
        // Set CAS Num : Test CAS Latency 1 & 2
        ucCASLat = ucTempWrPhasePoint + 1;
        ScalerSetBit(P4_A5_SDR_MEM_TYPE, ~(_BIT2 | _BIT1 | _BIT0), _BIT0 << ucCASLat);
        DebugMessageMemoryPhaseCal("P4_A5_SDR_MEM_TYPE", ScalerGetByte(P4_A5_SDR_MEM_TYPE));

        // Set Rx Data Coarse Dly = 0/90/180/270
        for(ucCoarseDly = 0; ucCoarseDly < 4; ucCoarseDly++)
        {
            ScalerSetBit(P4_C2_SDR_RX_CLK_DLY1, ~(_BIT6 | _BIT5), ucCoarseDly << 5);
            ScalerSetBit(P4_C4_SDR_RX_CLK_DLY3, ~(_BIT6 | _BIT5), ucCoarseDly << 5);
            DebugMessageMemoryPhaseCal("=== Rx Phase ===", 0x00);
            DebugMessageMemoryPhaseCal("P4_C2_SDR_RX_CLK_DLY1", ScalerGetByte(P4_C2_SDR_RX_CLK_DLY1));
            DebugMessageMemoryPhaseCal("P4_C4_SDR_RX_CLK_DLY3", ScalerGetByte(P4_C4_SDR_RX_CLK_DLY3));
            DebugMessageMemoryPhaseCal("=====================", 0x00);
            ScalerSdramTxClkSearchPhase();

            if(g_ucTempDiffPhase > g_ucMaxDiffPhase)
            {
                g_ucMaxDiffPhase = g_ucTempDiffPhase;
                g_ucBestPhase = g_ucTempBestPhase;
                g_ucBestCoarseDly = g_ucTempCoarseDly;
                g_ucBestCASLatn = g_ucTempCASLatn;
            }
        }
    }

    DebugMessageMemoryPhaseCal("=== Tx Result===", 0x00);
    DebugMessageMemoryPhaseCal("g_BestCASLatn", g_ucBestCASLatn);
    DebugMessageMemoryPhaseCal("g_BestCoarseDly", g_ucBestCoarseDly);
    DebugMessageMemoryPhaseCal("g_MaxDiffPhase", g_ucMaxDiffPhase);
    DebugMessageMemoryPhaseCal("g_BestPhase", g_ucBestPhase);

    // Set Best CAS Latency
    ScalerSetByte(P4_A5_SDR_MEM_TYPE, g_ucBestCASLatn);
    // Set Best Tx Phase
    ScalerSdramTxClkCalibrationEnable(_ON);
    ScalerSetByte(P4_C1_TX_CLK_DLY2, g_ucBestPhase);
    ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~_BIT6, _BIT6);
    ScalerSdramTxClkCalibrationEnable(_OFF);
    DebugMessageMemoryPhaseCal("=====================", 0x00);

    // Rx Clk Search Phase
    ScalerSdramRxClkSearchPhase();

#else
    // Tx Clk Search Phase
    ScalerSdramTxClkSearchPhase();

    // Rx Clk Search Phase
    ScalerSdramRxClkSearchPhase();

    // Check finish phase
    ScalerSdramSearchPhaseCheck();
#endif
}

#if(_SDRAM_PHASE_CALIBRATION_OPTIMIZATION == _OFF)
//--------------------------------------------------
// Description  : Sdram Search Phase Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramSearchPhaseCheck(void)
{
    if((g_pucSdramInitialPhase[0] != 0x00) ||
       ((ScalerGetByte(P4_C3_SDR_RX_CLK_DLY2) == 0x00) &&
        (ScalerGetByte(P4_C5_SDR_RX_CLK_DLY4) == 0x00)))
    {
        // Tx Clk Search Phase
        ScalerSdramTxClkSearchPhase();

        // Rx Clk Search Phase
        ScalerSdramRxClkSearchPhase();
    }
}

#endif
//--------------------------------------------------
// Description  : Sdram Tx Clk Search Phase
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramTxClkSearchPhase(void)
{
    BYTE ucCount = 0;
    BYTE ucInitialPhase = 0;
    BYTE ucPhase0 = _FALSE;
    BYTE ucEndPhase = 0;
    BYTE ucTempDiffPhase = 0;
    BYTE ucBestPhase = 0;
    BYTE ucHalfCycle = 0;
    bit bPhaseSearch = _FALSE;

    // Set Tx Clk Initial Phase
    ScalerSetByte(P4_C1_TX_CLK_DLY2, 0x00);

    // Enable Tx Clk Calibration Circuit
    ScalerSdramTxClkCalibrationEnable(_ON);

#if(_SDRAM_PHASE_CALIBRATION_2T == _ON)
    ucHalfCycle = (g_pucSdramDelayChain[0] * 4); // Test 2T
#else
    ScalerSetBit(P4_C2_SDR_RX_CLK_DLY1, ~(_BIT6 | _BIT5), _BIT5);
    ScalerSetBit(P4_C4_SDR_RX_CLK_DLY3, ~(_BIT6 | _BIT5), _BIT5);

    ucHalfCycle = (g_pucSdramDelayChain[0] * 2); // Test 1T
#endif

    DebugMessageMemoryPhaseCal("======================", 0x00);
    DebugMessageMemoryPhaseCal("==TX Clk Serch Phase==", 0x00);
    DebugMessageMemoryPhaseCal("===Tx phase half T====", g_pucSdramDelayChain[0]);
    DebugMessageMemoryPhaseCal("======================", 0x00);

    for(ucCount = 0; ucCount < ucHalfCycle; ucCount++)
    {
        ScalerSetByte(P4_C1_TX_CLK_DLY2, ucCount);

        ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~_BIT6, _BIT6);

        ScalerSdramControlReset();

        g_ucPhaseCount = ScalerSdramMcuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00, _OFF);

        // avoid phase all pass case
        if(ucCount == (ucHalfCycle - 1))
        {
            g_ucPhaseCount = _FALSE;
        }

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;
            DebugMessageMemoryPhaseCal("ucInitialPhase", ucInitialPhase);

            bPhaseSearch = _ON;

            // Checking the Phase0 is good phase or not
            if((ucCount == 0) && (ucInitialPhase == 0))
            {
                ucPhase0 = _TRUE;
            }
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;
            DebugMessageMemoryPhaseCal("ucEndPhase", ucEndPhase);

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];
                DebugMessageMemoryPhaseCal("ucTempDiffPhase", ucTempDiffPhase);
                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
                DebugMessageMemoryPhaseCal("ucBestPhase", ucBestPhase);
#if(_SDRAM_PHASE_CALIBRATION_2T == _ON)
                // The parameters of oprmization
                g_ucTempDiffPhase = ucTempDiffPhase;
                g_ucTempBestPhase = (ucBestPhase % (g_pucSdramDelayChain[0] * 2)); // Choice midpoint of the max range
                g_ucTempCoarseDly = ScalerGetByte(P4_C2_SDR_RX_CLK_DLY1);
                g_ucTempCASLatn = ScalerGetByte(P4_A5_SDR_MEM_TYPE);
#endif
            }

            bPhaseSearch = _FALSE;
        }

#if(_SDRAM_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("Tx Clk ", g_ucPhaseCount);
#endif
    }

    if(ucPhase0 == _TRUE)
    {
        ucBestPhase = 0;
    }
    else
    {
        ucBestPhase = ucBestPhase;
    }

    g_pucSdramInitialPhase[0] = ucBestPhase;

    ScalerSetByte(P4_C1_TX_CLK_DLY2, ucBestPhase);

    ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~_BIT6, _BIT6);

    ScalerSetBit(P4_C2_SDR_RX_CLK_DLY1, ~(_BIT6 | _BIT5), 0x00);
    ScalerSetBit(P4_C4_SDR_RX_CLK_DLY3, ~(_BIT6 | _BIT5), 0x00);

    // Enable Tx Clk Calibration Circuit
    ScalerSdramTxClkCalibrationEnable(_OFF);

    DebugMessageMemoryPhaseCal("=== Tx Scan Result ===", 0x00);
    DebugMessageMemoryPhaseCal("P4_C1_TX_CLK_DLY2", ScalerGetByte(P4_C1_TX_CLK_DLY2));
    DebugMessageMemoryPhaseCal("======================", 0x00);
}

//--------------------------------------------------
// Description  : Sdram Rx Clk Search Phse
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramRxClkSearchPhase(void)
{
    BYTE ucCount = 0;
    BYTE ucInitialPhase = 0;
    BYTE ucEndPhase = 0;
    BYTE ucTempDiffPhase = 0;
    BYTE ucBestPhase = 0;
    BYTE ucTempWrPhasePoint = 0;
    bit bPhaseSearch = _FALSE;
    BYTE ucHalfCycleHigh = 0;
    BYTE ucHalfCycleLow = 0;

    // Enable Rx Dqs Calibration Circuit
    ScalerSdramRxClkCalibrationEnable(_ON);

    // Disable Rx Dqs Calibration Circuit
    ScalerSdramRxClkCalibrationEnable(_OFF);

//**********************************************************************************//
//**********************************RX Clk High Phase*******************************//
//**********************************************************************************//
    ucHalfCycleHigh = (g_pucSdramDelayChain[1] * 2); // Test 1T
    DebugMessageMemoryPhaseCal("=====================", 0x00);
    DebugMessageMemoryPhaseCal("==RX Clk High Phase==", 0x00);
    DebugMessageMemoryPhaseCal("===Rx phase half T===", g_pucSdramDelayChain[1]);
    DebugMessageMemoryPhaseCal("=====================", 0x00);

    for(ucTempWrPhasePoint = 0; ucTempWrPhasePoint < 2; ucTempWrPhasePoint++)
    {
        bPhaseSearch = _FALSE;

        // Set Wr Phase Point to Pos or Neg
        ScalerSetBit(P4_C8_MCLK_CTRL, ~_BIT2, ucTempWrPhasePoint << 2);
        DebugMessageMemoryPhaseCal("P4_C8_MCLK_CTRL", ScalerGetByte(P4_C8_MCLK_CTRL));

        for(ucCount = 0; ucCount < ucHalfCycleHigh; ucCount++)
        {
            ScalerSetByte(P4_C3_SDR_RX_CLK_DLY2, ucCount);
            ScalerSetByte(P4_C5_SDR_RX_CLK_DLY4, ucCount);

            g_ucPhaseCount = ScalerSdramMcuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00, _OFF);

            // avoid phase all pass case
            if(ucCount == (ucHalfCycleHigh - 1))
            {
                g_ucPhaseCount = _FALSE;
            }

            if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
            {
                ucInitialPhase = ucCount;
                DebugMessageMemoryPhaseCal("ucInitialPhase", ucInitialPhase);
                bPhaseSearch = _ON;
            }

            if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
            {
                ucEndPhase = ucCount;
                DebugMessageMemoryPhaseCal("ucEndPhase", ucEndPhase);
                pData[2] = ucEndPhase - ucInitialPhase;

                if(pData[2] > ucTempDiffPhase)
                {
                    ucTempDiffPhase = pData[2];
                    DebugMessageMemoryPhaseCal("ucTempDiffPhase", ucTempDiffPhase);
                    g_ucWrPhasePoint = ucTempWrPhasePoint;

                    ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
                    DebugMessageMemoryPhaseCal("ucBestPhase", ucBestPhase);
                }

                bPhaseSearch = _FALSE;
            }

#if(_SDRAM_MCU_ALL_PHASE_CHECK == _ON)
            DebugMessageMemoryPhaseCal("counter", ucCount);
            DebugMessageMemoryPhaseCal("rx Clk High", g_ucPhaseCount);
#endif
        }
    }

    if(ucBestPhase > 0)
    {
        ScalerSetBit(P4_C8_MCLK_CTRL, ~_BIT2, g_ucWrPhasePoint << 2);
    }

    g_pucSdramInitialPhase[1] = ucBestPhase;

    ScalerSetByte(P4_C3_SDR_RX_CLK_DLY2, ucBestPhase);

//**********************************************************************************//
//*********************************RX Clk Low Phase*********************************//
//**********************************************************************************//
    ucTempDiffPhase = 0;
    bPhaseSearch = _FALSE;
    ucHalfCycleLow = (g_pucSdramDelayChain[2] * 2); // Test 1T
    DebugMessageMemoryPhaseCal("=====================", 0x00);
    DebugMessageMemoryPhaseCal("===RX Clk Low Phase==", 0x00);
    DebugMessageMemoryPhaseCal("===Rx phase half T===", g_pucSdramDelayChain[2]);
    DebugMessageMemoryPhaseCal("=====================", 0x00);

    for(ucCount = 0; ucCount < ucHalfCycleLow; ucCount++)
    {
        ScalerSetByte(P4_C5_SDR_RX_CLK_DLY4, ucCount);

        g_ucPhaseCount = ScalerSdramMcuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00, _OFF);

        if(ucCount == (ucHalfCycleLow - 1))
        {
            g_ucPhaseCount = _FALSE;
        }

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;
            DebugMessageMemoryPhaseCal("ucInitialPhase", ucInitialPhase);
            bPhaseSearch = _ON;
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;
            DebugMessageMemoryPhaseCal("ucEndPhase", ucEndPhase);
            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];
                DebugMessageMemoryPhaseCal("ucTempDiffPhase", ucTempDiffPhase);

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
                DebugMessageMemoryPhaseCal("ucBestPhase", ucBestPhase);
            }

            bPhaseSearch = _FALSE;
        }

#if(_SDRAM_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("rx Clk Low", g_ucPhaseCount);
#endif
    }

    g_pucSdramInitialPhase[2] = ucBestPhase;

    ScalerSetByte(P4_C5_SDR_RX_CLK_DLY4, ucBestPhase);

    DebugMessageMemoryPhaseCal("=== Rx Scan Result ==", 0x00);
    DebugMessageMemoryPhaseCal("P4_A5_SDR_MEM_TYPE", ScalerGetByte(P4_A5_SDR_MEM_TYPE));
    DebugMessageMemoryPhaseCal("P4_C8_MCLK_CTRL", ScalerGetByte(P4_C8_MCLK_CTRL));
    DebugMessageMemoryPhaseCal("P4_C3_SDR_RX_CLK_DLY2", ScalerGetByte(P4_C3_SDR_RX_CLK_DLY2));
    DebugMessageMemoryPhaseCal("P4_C5_SDR_RX_CLK_DLY4", ScalerGetByte(P4_C5_SDR_RX_CLK_DLY4));
    DebugMessageMemoryPhaseCal("=====================", 0x00);
}

//--------------------------------------------------
// Description  : Sdram Tx Clk Calibration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramTxClkCalibrationEnable(bit bEn)
{
    // Set Clk Gatting Idel and Stop time
    ScalerSetByte(P4_C9_SDR_STOPCLK_CNT, 0x02);
    ScalerSetByte(P4_CA_STOP_WAIT_CNT, 0x02);

    if(bEn == _ON)
    {
        // Enable Sdram Clk Gatting Function
        ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));

        // Enable Tx Calibration Function
        ScalerSetBit(P4_CB_TX_PHASE_CALIBRATION, ~_BIT2, _BIT2);

        // Pob Tx delay chain value of half clock cycle
        g_pucSdramDelayChain[0] = ScalerGetByte(P4_CC_TX_CALIBRATION_RESULT);
    }
    else
    {
        // Disable Sdram Clk Gatting Function
        ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~(_BIT5 | _BIT1), 0x00);

        // Disable Tx Calibration Function
        ScalerSetBit(P4_CB_TX_PHASE_CALIBRATION, ~_BIT2, 0x00);
    }
}

//--------------------------------------------------
// Description  : Sdram Rx Dqs Calibration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramRxClkCalibrationEnable(bit bEn)
{
    if(bEn == _ON)
    {
        // Enable Rx Calibration Function
        ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~_BIT2, _BIT2);

        // Pob Rx delay chain value of half clock cycle
        g_pucSdramDelayChain[1] = (ScalerGetByte(P4_BF_SDR_RX_CALIBRATION_RESULT) & 0x7F);
        g_pucSdramDelayChain[2] = (ScalerGetByte(P4_BF_SDR_RX_CALIBRATION_RESULT) & 0x7F);

#if(_SDRAM_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("rx phase half T", g_pucSdramDelayChain[1]);
#endif
    }
    else
    {
        // Disable Rx Calibration Function
        ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~_BIT2, 0x00);
    }
}

//--------------------------------------------------
// Description  : Sdram Read Write Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerSdramMcuReadWriteCheck(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, bit bReadSlowDown)
{
    ScalerSetByte(P4_B8_SDR_ADDR_H, ucAddrH);
    ScalerSetByte(P4_B9_SDR_ADDR_M, ucAddrM);
    ScalerSetByte(P4_BA_SDR_ADDR_L, ucAddrL);

    ScalerSdramWriteToFifo();

    if(bReadSlowDown == _ON)
    {
        // mclk div 2 for read phase
        ScalerSetBit(P4_C8_MCLK_CTRL, ~(_BIT1 | _BIT0), _BIT0);

        ScalerSdramReadFromFifo();

        ScalerSetBit(P4_C8_MCLK_CTRL, ~(_BIT1 | _BIT0), 0x00);
    }
    else
    {
        ScalerSdramReadFromFifo();
    }


    ScalerSetByte(P4_BB_SDR_ACCESS_CMD, 0x00);

    for(pData[14] = 0; pData[14] < sizeof(tSDRAM_PATTERN); pData[14]++)
    {
        if(ScalerGetByte(P4_BC_SDR_DATA_BUF) != tSDRAM_PATTERN[pData[14]])
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Sdram Write Data To FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramWriteToFifo(void)
{
    ScalerSdramClearFifo();

    ScalerSetByte(P4_BB_SDR_ACCESS_CMD, 0x00);

    for(pData[14] = 0; pData[14] < sizeof(tSDRAM_PATTERN); pData[14]++)
    {
        ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[14]);
        ScalerSetByte(P4_BC_SDR_DATA_BUF, tSDRAM_PATTERN[pData[14]]);
    }

    ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT7 | _BIT6 | _BIT5), _SDRAM_MCU_COMMAND_WRITE);

    if(ScalerSdramCheckCommandFinish() == _FALSE)
    {
        DebugMessageMemoryPhaseCal("Write Command Fail", 0x00);
    }
}

//--------------------------------------------------
// Description  : Sdram Write Data To FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramReadFromFifo(void)
{
    ScalerSdramClearFifo();

    ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT7 | _BIT6 | _BIT5), _SDRAM_MCU_COMMAND_READ);

    if(ScalerSdramCheckCommandFinish() == _FALSE)
    {
        DebugMessageMemoryPhaseCal("Read Command Fail", 0x00);
    }
}

//--------------------------------------------------
// Description  : Sdram Clear Fifo
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramClearFifo(void)
{
    ScalerSetByte(P4_BB_SDR_ACCESS_CMD, 0x00);

    for(pData[14] = 0; pData[14] < 32; pData[14]++)
    {
        ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[14]);
        ScalerSetByte(P4_BC_SDR_DATA_BUF, 0x00);
    }
}

//--------------------------------------------------
// Description  : Sdram Check Command Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerSdramCheckCommandFinish(void)
{
    if(ScalerTimerPollingFlagProc(5, P4_BB_SDR_ACCESS_CMD, (_BIT7 | _BIT6 | _BIT5), 0x00) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Sdram On Line Phase Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramOnLinePhaseCntCheck(void)
{
    static BYTE sucSdramOnLineCheckLoop = _SDRAM_MCU_ONLINE_START_LOOP;

    if(sucSdramOnLineCheckLoop-- == _SDRAM_MCU_ONLINE_END_LOOP)
    {
        BYTE ucRxClkIndex = 0;
        SWORD shHalfCycleTapDiff = 0;
        SWORD shCurrOneCycleTap = 0;

        // Set Loop Counter 60 times Restore
        sucSdramOnLineCheckLoop = _SDRAM_MCU_ONLINE_START_LOOP;

        ScalerSdramOnLinePhaseCalibration(_ON);

        for(ucRxClkIndex = _SDRAM_RX_H; ucRxClkIndex <= _SDRAM_RX_L; ucRxClkIndex++)
        {
            shHalfCycleTapDiff = (SWORD)g_pucSdramOnLineDelayChain[ucRxClkIndex] - (SWORD)g_pucSdramDelayChain[ucRxClkIndex];

            if(abs(shHalfCycleTapDiff) > _SDRAM_ONLINE_TAP_DIFF_THRESHOLD)
            {
                shCurrOneCycleTap = g_pucSdramOnLineDelayChain[ucRxClkIndex] * 2;
                ScalerSetByte(tSDRAM_FINE_DLY_REG[ucRxClkIndex],
                              (BYTE)(((SWORD)g_pucSdramInitialPhase[ucRxClkIndex] + shHalfCycleTapDiff / 2 + shCurrOneCycleTap) % shCurrOneCycleTap));
            }
        }

        ScalerSdramOnLinePhaseCalibration(_OFF);
    }
}
//--------------------------------------------------
// Description  : Sdram On Line Phase Calibration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramOnLinePhaseCalibration(bit bEn)
{
    if(bEn == _ON)
    {
        // Enable MCU Mode Token Ring
        ScalerSetByte(P4_AB_SDR_RSC_MCU, 0x30);

        // Enable Rx Calibration Function
        ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~_BIT2, _BIT2);

        // Pob Rx delay chain value of half clock cycle
        g_pucSdramOnLineDelayChain[1] = (ScalerGetByte(P4_BF_SDR_RX_CALIBRATION_RESULT) & 0x7F);
        g_pucSdramOnLineDelayChain[2] = (ScalerGetByte(P4_BF_SDR_RX_CALIBRATION_RESULT) & 0x7F);
    }
    else
    {
        // Disable MCU Mode Token Ring
        ScalerSetByte(P4_AB_SDR_RSC_MCU, 0x00);

        // Disable Rx Calibration Function
        ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~_BIT2, 0x00);
    }
}

//--------------------------------------------------
// Description  : SDRAM Restore Initial Phase
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSdramRestoreInitialPhase(void)
{
    ScalerSetByte(P4_C1_TX_CLK_DLY2, g_pucSdramInitialPhase[0]);
    ScalerSetByte(P4_C3_SDR_RX_CLK_DLY2, g_pucSdramInitialPhase[1]);
    ScalerSetByte(P4_C5_SDR_RX_CLK_DLY4, g_pucSdramInitialPhase[2]);
    ScalerSetBit(P4_C8_MCLK_CTRL, ~_BIT2, ((g_ucWrPhasePoint << 2) & _BIT2));
}

#endif  // End of #if(_Sdram_PHASE_CALIBRATION == _ON)


