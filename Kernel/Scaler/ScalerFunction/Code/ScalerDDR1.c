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
// ID Code      : ScalerDDR1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DDR1__

#include "ScalerFunctionInclude.h"

#if(_DDR1_PHASE_CALIBRATION == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DDR1_MCU_ALL_PHASE_CHECK               _OFF

#define _DDR1_MCU_COMMAND_NOP_FINISH            0
#define _DDR1_MCU_COMMAND_PRECHARGE             0x20
#define _DDR1_MCU_COMMAND_AUTO_REFRESH          0x40
#define _DDR1_MCU_COMMAND_LOAD_MODE_REGISTER    0x60
#define _DDR1_MCU_COMMAND_WRITE                 0x80
#define _DDR1_MCU_COMMAND_READ                  0xA0

#define _DDR1_MCU_ONLINE_START_LOOP             60
#define _DDR1_MCU_ONLINE_END_LOOP               1

#define _DDR1_ONLINE_TAP_DIFF_THRESHOLD         10

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DDR1_TX_CLK0 = 0,
    _DDR1_TX_DQS0,
    _DDR1_TX_DQS1,
    _DDR1_RX_DQS0_R,
    _DDR1_RX_DQS0_F,
    _DDR1_RX_DQS1_R,
    _DDR1_RX_DQS1_F,
} Enum1stDDR1Clk;

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
typedef enum
{
    _DDR1_TX_CLK1 = 0,
    _DDR1_TX_DQS2,
    _DDR1_TX_DQS3,
    _DDR1_RX_DQS2_R,
    _DDR1_RX_DQS2_F,
    _DDR1_RX_DQS3_R,
    _DDR1_RX_DQS3_F,
} Enum2ndDDR1Clk;
#endif


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tDDR_PATTERN[16] = {0x33, 0x33, 0x55, 0x55, 0xaa, 0xaa, 0xcc, 0xcc, 0x22, 0x22, 0x44, 0x44, 0x88, 0x88, 0xBB, 0xBB};

WORD code tDDR1_FINE_DLY_REG0[] =
{
    P4_C1_TX_CLK_DLY2,
    P4_CD_DDR_TX_DLY0,
    P4_CE_DDR_TX_DLY1,
    P4_D0_DDR_RX_DLY1,
    P4_D1_DDR_RX_DLY2,
    P4_D2_DDR_RX_DLY3,
    P4_D3_DDR_RX_DLY4,
};

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
WORD code tDDR1_FINE_DLY_REG1[] =
{
    P4_22_TX2_CLK_DLY,
    P4_25_DDR_TX2_DLY2,
    P4_26_DDR_TX2_DLY3,
    P4_30_DDR_RX2_DLY1,
    P4_31_DDR_RX2_DLY2,
    P4_32_DDR_RX2_DLY3,
    P4_33_DDR_RX2_DLY4,
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucPhaseCount;
BYTE g_pucDDR1InitialPhase[7];
BYTE g_pucDDR1DelayChain[7];
BYTE g_pucDDR1OnLineDelayChain[7];
BYTE g_ucDDR1RxIenDelayChain;

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
BYTE g_pucDDR1InitialPhase2[7];
BYTE g_pucDDR1DelayChain2[7];
BYTE g_pucDDR1OnLineDelayChain2[7];
BYTE g_ucDDR1Rx2IenDelayChain2;
#endif

//*************************************************//
//g_pucDDR1DelayChain[0] = g_ucTxClkDelayChain;
//g_pucDDR1DelayChain[1] = g_ucTxDqs0DelayChain;
//g_pucDDR1DelayChain[2] = g_ucTxDqs1DelayChain;
//g_pucDDR1DelayChain[3] = g_ucRxDqs0RiseDelayChain;
//g_pucDDR1DelayChain[4] = g_ucRxDqs0FallDelayChain;
//g_pucDDR1DelayChain[5] = g_ucRxDqs1RiseDelayChain;
//g_pucDDR1DelayChain[6] = g_ucRxDqs1FallDelayChain;
//*************************************************//

//*************************************************//
//g_pucDDR1DelayChain2[0] = g_ucTx2ClkDelayChain;
//g_pucDDR1DelayChain2[1] = g_ucTx2Dqs2DelayChain;
//g_pucDDR1DelayChain2[2] = g_ucTx2Dqs3DelayChain;
//g_pucDDR1DelayChain2[3] = g_ucRx2Dqs2RiseDelayChain;
//g_pucDDR1DelayChain2[4] = g_ucRx2Dqs2FallDelayChain;
//g_pucDDR1DelayChain2[5] = g_ucRx2Dqs3RiseDelayChain;
//g_pucDDR1DelayChain2[6] = g_ucRx2Dqs3FallDelayChain;
//*************************************************//
#endif // End of #if(_DDR1_PHASE_CALIBRATION == _ON)

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
void ScalerDDR1PowerControl(bit bOn);
void ScalerDDR1MclkGenReset(void);
void ScalerDDR1SystemInitial(void);
void ScalerDDR1PinshareInitial(void);
void ScalerDDR1ControlReset(void);
#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
void ScalerDDR1SetFRCDisplayTokenRing(EnumFunctionOnOFF enumOn);
#endif
#endif

#if(_DDR1_PHASE_CALIBRATION == _ON)
void ScalerDDR1TokenRingSet(void);
void ScalerDDR1SearchPhase(void);
void ScalerDDR1SearchPhaseCheck(void);
void ScalerDDR1TxClkSearchPhase(void);
void ScalerDDR1TxDqsSearchPhase(void);
void ScalerDDR1RxIenSearchPhase(void);
void ScalerDDR1RxDqsSearchPhase(void);
void ScalerDDR1TxClkCalibrationEnable(bit bEn);
void ScalerDDR1TxDqsCalibrationEnable(bit bEn);
void ScalerDDR1RxDqsCalibrationEnable(bit bEn);
bit ScalerDDR1McuReadWriteCheck(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL);
void ScalerDDR1WriteToFifo(void);
void ScalerDDR1ReadFromFifo(void);
void ScalerDDR1ClearFifo(void);
bit ScalerDDR1CheckCommandFinish(void);
void ScalerDDR1OnLinePhaseCntCheck(void);
void ScalerDDR1OnLinePhaseCalibration(bit bEn);
void ScalerDDR1RestoreInitialPhase(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
//--------------------------------------------------
// Description  : DDR Power On/Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1PowerControl(bit bOn)
{
    // Set MPLL CLK
    ScalerPLLSetMPLLFreq((DWORD)_MEMORY_PLL_CLOCK * 1000);

    // Set Mclk Gen Reset Align MPLL
    ScalerDDR1MclkGenReset();

    if(bOn == _ON)
    {
        // Set DDR1 Module Power Status
        ScalerDDR1PowerEnable(_ON);

        // Set DDR1 System Initial
        ScalerDDR1SystemInitial();
    }
    else
    {
        // Set DDR1 Module Power Status
        ScalerDDR1PowerEnable(_OFF);

        // Power off MPLL
        ScalerSetBit(P0_F8_MPLL_WD, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : DDR1 Mclk Gen Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1MclkGenReset(void)
{
    // Set Mclk Gen Local Reset
    ScalerSetBit(P4_A8_SDR_CLK_ALIGN, ~_BIT7, _BIT7);

    // Delay Time us [300,x] Waiting for DDR1 Mclk Reset
    DELAY_XUS(300);

    // Set Mclk Gen Local Reset
    ScalerSetBit(P4_A8_SDR_CLK_ALIGN, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : DDR1 system initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1SystemInitial(void)
{
    // Set DDR1 Pinshare Initial
    ScalerDDR1PinshareInitial();

    // Set DDR1 Module Active to Read and Write delay
    ScalerSetBit(P4_A1_SDR_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));

    // Set DDR1 Module CAS Latency
    ScalerSetBit(P4_A2_SDR_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT5 | _BIT2 | _BIT1));

    // Set DDR1 Auto Refresh Time
    ScalerSetByte(P4_A3_SDR_AREF_TIME, 0x0D);

    // Set DDR1 Precharge Duty Cycle
    ScalerSetBit(P4_A4_SDR_PRCG, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    ScalerDDR1MemoryType();

    // Set DDR1 Slew Rate DDR mode
    ScalerSetBit(P4_A6_SDR_SLEW_RATE, ~_BIT7, 0x00);

    // Set DDR1 Refresh time 15.6us
    ScalerSetByte(P4_A7_SDR_AREF_CNT, 0x0D);

#if(_DDR1_PHASE_CALIBRATION == _ON)
    ScalerDDR1TokenRingSet();
#endif

    // Set DDR1 Control Reset
    ScalerDDR1ControlReset();

    // Set DDR1 Control Reset Ready
    ScalerTimerPollingFlagProc(5, P4_B5_SDR_ABTR_STATUS1, _BIT0, _TRUE);
}

//--------------------------------------------------
// Description  : DDR1 Pinshare Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1PinshareInitial(void)
{
    ScalerSetByte(P4_01_SDDR_CLK_CTRL0, 0x80);
    ScalerSetByte(P4_02_SDDR_CLK_CTRL1, 0x55);
    ScalerSetByte(P4_03_SDDR_CDAR_CTRL, 0x50);
    ScalerSetByte(P4_04_SDDR_DQSX0_CTRL0, 0x00);
    ScalerSetByte(P4_05_SDDR_DQSX0_CTRL1, 0x55);
    ScalerSetByte(P4_06_SDDR_DQX0_CTRL0, 0x00);
    ScalerSetByte(P4_07_SDDR_DQX0_CTRL1, 0x55);
    ScalerSetByte(P4_08_SDDR_DQSX1_CTRL0, 0x00);
    ScalerSetByte(P4_09_SDDR_DQSX1_CTRL1, 0x55);
    ScalerSetByte(P4_0A_SDDR_DQX1_CTRL0, 0x00);
    ScalerSetByte(P4_0B_SDDR_DQX1_CTRL1, 0x55);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    ScalerSetByte(P4_11_SDDR_CLK_CTRL0, 0x80);
    ScalerSetByte(P4_12_SDDR_CLK_CTRL1, 0x55);
    ScalerSetByte(P4_13_SDDR_CDAR_CTRL, 0x50);
    ScalerSetByte(P4_14_SDDR_DQSX0_CTRL0, 0x00);
    ScalerSetByte(P4_15_SDDR_DQSX0_CTRL1, 0x55);
    ScalerSetByte(P4_16_SDDR_DQX0_CTRL0, 0x00);
    ScalerSetByte(P4_17_SDDR_DQX0_CTRL1, 0x55);
    ScalerSetByte(P4_18_SDDR_DQSX1_CTRL0, 0x00);
    ScalerSetByte(P4_19_SDDR_DQSX1_CTRL1, 0x55);
    ScalerSetByte(P4_1A_SDDR_DQX1_CTRL0, 0x00);
    ScalerSetByte(P4_1B_SDDR_DQX1_CTRL1, 0x55);
#endif
}

//--------------------------------------------------
// Description  : DDR1 Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1ControlReset(void)
{
    ScalerSetBit(P4_A4_SDR_PRCG, ~_BIT4, _BIT4);
    ScalerSetBit(P4_A4_SDR_PRCG, ~_BIT4, 0x00);

    // Delay Time us [300,x] Waiting for DDR1 Control Reset
    DELAY_XUS(300);

    ScalerDDR1MclkGenReset();
}

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Display Token Ring according to OD status
// Input Value  : EnumFunctionOnOFF enumOn
// Output Value : None
//--------------------------------------------------
void ScalerDDR1SetFRCDisplayTokenRing(EnumFunctionOnOFF enumOn)
{
    if((enumOn == _FUNCTION_ON) && (GET_OD_USE_BIT() != _OFF))
    {
        ScalerSetByte(P4_AE_SDR_RSC_MAIN, 0x44);
    }
    else
    {
        ScalerSetByte(P4_AE_SDR_RSC_MAIN, 0xFF);
    }
}
#endif // End of #if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)

#if(_DDR1_PHASE_CALIBRATION == _ON)
//--------------------------------------------------
// Description  : DDR1 Token Ring Set
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1TokenRingSet(void)
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
    ScalerSetByte(P4_AC_SDR_RSC_CAP1, 0xFF);
    ScalerSetByte(P4_AE_SDR_RSC_MAIN, 0xFF);

    ScalerSetByte(P4_B0_SDR_RSC_RTC_RD, 0x11);
    ScalerSetByte(P4_B1_SDR_RSC_RTC_WR, 0xAA);

#elif((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
    ScalerSetByte(P4_AC_SDR_RSC_CAP1, 0xFF);
    ScalerSetByte(P4_AE_SDR_RSC_MAIN, 0x44);

    ScalerSetByte(P4_B0_SDR_RSC_RTC_RD, 0x11);
    ScalerSetByte(P4_B1_SDR_RSC_RTC_WR, 0xAA);
#endif
}

//--------------------------------------------------
// Description  : DDR1 Search Phase
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1SearchPhase(void)
{
    // Tx Clk Search Phase
    ScalerDDR1TxClkSearchPhase();

    // Tx Dqs Search Phase
    ScalerDDR1TxDqsSearchPhase();

    // Rx Ien Search Phase
    ScalerDDR1RxIenSearchPhase();

    // Rx Dqs Search Phase
    ScalerDDR1RxDqsSearchPhase();

    // Check finish phase
    ScalerDDR1SearchPhaseCheck();
}

//--------------------------------------------------
// Description  : DDR1 Search Phase Check Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1SearchPhaseCheck(void)
{
    if((g_pucDDR1InitialPhase[0] != 0x00) ||
       ((ScalerGetByte(P4_D0_DDR_RX_DLY1) == 0x00) &&
        (ScalerGetByte(P4_D1_DDR_RX_DLY2) == 0x00) &&
        (ScalerGetByte(P4_D2_DDR_RX_DLY3) == 0x00) &&
        (ScalerGetByte(P4_D3_DDR_RX_DLY4) == 0x00)))
    {
        // Tx Clk Search Phase
        ScalerDDR1TxClkSearchPhase();

        // Tx Dqs Search Phase
        ScalerDDR1TxDqsSearchPhase();

        // Rx Ien Search Phase
        ScalerDDR1RxIenSearchPhase();

        // Rx Dqs Search Phase
        ScalerDDR1RxDqsSearchPhase();
    }

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    if((g_pucDDR1InitialPhase2[0] != 0x00) ||
       ((ScalerGetByte(P4_30_DDR_RX2_DLY1) == 0x00) &&
        (ScalerGetByte(P4_31_DDR_RX2_DLY2) == 0x00) &&
        (ScalerGetByte(P4_32_DDR_RX2_DLY3) == 0x00) &&
        (ScalerGetByte(P4_33_DDR_RX2_DLY4) == 0x00)))
    {
        // Tx Clk Search Phase
        ScalerDDR1TxClkSearchPhase();

        // Tx Dqs Search Phase
        ScalerDDR1TxDqsSearchPhase();

        // Rx Ien Search Phase
        ScalerDDR1RxIenSearchPhase();

        // Rx Dqs Search Phase
        ScalerDDR1RxDqsSearchPhase();
    }
#endif
}

//--------------------------------------------------
// Description  : DDR1 Tx Clk Search Phase
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1TxClkSearchPhase(void)
{
    BYTE ucCount = 0;
    BYTE ucInitialPhase = 0;
    BYTE ucPhase0 = _FALSE;
    BYTE ucEndPhase = 0;
    BYTE ucTempDiffPhase = 0;
    BYTE ucBestPhase = 0;
    bit bPhaseSearch = _FALSE;

    // Set Tx clk Initial Phase
    ScalerSetByte(P4_C1_TX_CLK_DLY2, 0x00);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    // Set Tx2 clk Initial Phase
    ScalerSetByte(P4_22_TX2_CLK_DLY, 0x00);
#endif

    // Enable Tx Clk Calibration Circuit
    ScalerDDR1TxClkCalibrationEnable(_ON);

    for(ucCount = 0; ucCount <= (BYTE)(g_pucDDR1DelayChain[0] * 2); ucCount++)
    {
        ScalerSetByte(P4_C1_TX_CLK_DLY2, ucCount);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
        ScalerSetByte(P4_22_TX2_CLK_DLY, ucCount);
#endif
        ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~_BIT6, _BIT6);

        ScalerDDR1ControlReset();

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

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

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;

            break;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("tx clk", g_ucPhaseCount);
#endif
    }

    if(ucPhase0 == _TRUE)
    {
        pData[3] = 0;
    }
    else
    {
        pData[3] = ucBestPhase;
    }

    g_pucDDR1InitialPhase[0] = pData[3];

    ScalerSetByte(P4_C1_TX_CLK_DLY2, pData[3]);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
//**********************************************************************************//
//**********************************TX2 Clock Phase*********************************//
//**********************************************************************************//

    ucTempDiffPhase = 0;

    for(ucCount = 0; ucCount <= (BYTE)(g_pucDDR1DelayChain2[0] * 2); ucCount++)
    {
        ScalerSetByte(P4_22_TX2_CLK_DLY, ucCount);

        ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~_BIT6, _BIT6);

        ScalerDDR1ControlReset();

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

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

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;

            break;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("tx2 clk", g_ucPhaseCount);
#endif
    }

    if(ucPhase0 == _TRUE)
    {
        pData[3] = 0;
    }
    else
    {
        pData[3] = ucBestPhase;
    }

    g_pucDDR1InitialPhase2[0] = pData[3];

    ScalerSetByte(P4_22_TX2_CLK_DLY, pData[3]);

#endif // End of #if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~_BIT6, _BIT6);

    // Enable Tx Clk Calibration Circuit
    ScalerDDR1TxClkCalibrationEnable(_OFF);
}

//--------------------------------------------------
// Description  : DDR1 Tx Dqs Search Phase
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1TxDqsSearchPhase(void)
{
    BYTE ucCount = 0;
    BYTE ucInitialPhase = 0;
    BYTE ucPhase0 = _FALSE;
    BYTE ucEndPhase = 0;
    BYTE ucTempDiffPhase = 0;
    BYTE ucBestPhase = 0;
    bit bPhaseSearch = _FALSE;

    // Enable Tx Dqs Calibration Circuit
    ScalerDDR1TxDqsCalibrationEnable(_ON);

    // Disable Tx Dqs Calibration Circuit
    ScalerDDR1TxDqsCalibrationEnable(_OFF);

//**********************************************************************************//
//**********************************TX DQS0/1 Phase*********************************//
//**********************************************************************************//

    for(ucCount = 0; ucCount <= g_pucDDR1DelayChain[1]; ucCount++)
    {
        ScalerSetByte(P4_CD_DDR_TX_DLY0, ucCount);
        ScalerSetByte(P4_CE_DDR_TX_DLY1, ucCount);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
        ScalerSetByte(P4_25_DDR_TX2_DLY2, ucCount);
        ScalerSetByte(P4_26_DDR_TX2_DLY3, ucCount);
#endif
        ScalerDDR1ControlReset();

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

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

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("tx dqs", g_ucPhaseCount);
#endif
    }

    if((ucBestPhase > (g_pucDDR1DelayChain[1] / 2)) && (ucTempDiffPhase > ((g_pucDDR1DelayChain[1] / 2) + (g_pucDDR1DelayChain[1] / 4))))
    {
        pData[3] = (ucBestPhase / 2);
    }
    else
    {
        if(ucPhase0 == _TRUE)
        {
            pData[3] = 0;
        }
        else
        {
            pData[3] = ucBestPhase;
        }
    }

    g_pucDDR1InitialPhase[1] = pData[3];
    g_pucDDR1InitialPhase[2] = pData[3];

    ScalerSetByte(P4_CD_DDR_TX_DLY0, pData[3]);
    ScalerSetByte(P4_CE_DDR_TX_DLY1, pData[3]);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
//**********************************************************************************//
//**********************************TX DQS2/3 Phase*********************************//
//**********************************************************************************//

    ucTempDiffPhase = 0;

    for(ucCount = 0; ucCount <= g_pucDDR1DelayChain2[1]; ucCount++)
    {
        ScalerSetByte(P4_25_DDR_TX2_DLY2, ucCount);
        ScalerSetByte(P4_26_DDR_TX2_DLY3, ucCount);

        ScalerDDR1ControlReset();

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

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

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("tx2 dqs", g_ucPhaseCount);
#endif
    }

    if((ucBestPhase > (g_pucDDR1DelayChain2[1] / 2)) && (ucTempDiffPhase > ((g_pucDDR1DelayChain2[1] / 2) + (g_pucDDR1DelayChain2[1] / 4))))
    {
        pData[3] = (ucBestPhase / 2);
    }
    else
    {
        if(ucPhase0 == _TRUE)
        {
            pData[3] = 0;
        }
        else
        {
            pData[3] = ucBestPhase;
        }
    }

    g_pucDDR1InitialPhase2[1] = pData[3];
    g_pucDDR1InitialPhase2[2] = pData[3];

    ScalerSetByte(P4_25_DDR_TX2_DLY2, pData[3]);
    ScalerSetByte(P4_26_DDR_TX2_DLY3, pData[3]);

#endif // End of #if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
}

//--------------------------------------------------
// Description  : DDR1 Rx Ien Search Phase
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1RxIenSearchPhase(void)
{
    BYTE ucCount = 0;
    BYTE ucInitialPhase = 0;
    BYTE ucEndPhase = 0;
    BYTE ucTempDiffPhase = 0;
    BYTE ucBestPhase = 0;
    bit bPhaseSearch = _FALSE;

//**********************************************************************************//
//**********************************RX Ien Phase************************************//
//**********************************************************************************//

    for(ucCount = 0; ucCount < 128; ucCount++)
    {
        ScalerSetByte(P4_CF_DDR_RX_DLY0, ucCount);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
        ScalerSetByte(P4_27_DDR_RX2_DLY0, ucCount);
#endif
        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

            bPhaseSearch = _ON;
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("rx ien", g_ucPhaseCount);
#endif
    }

    if(bPhaseSearch == _ON)
    {
        if((128 - ucInitialPhase) > ucBestPhase)
        {
            ucBestPhase = (128 + ucInitialPhase) / 2;
        }
    }

    // Rx Ien1 Set Best Phase 1/4T
    g_ucDDR1RxIenDelayChain = (ucBestPhase / 2);
    ScalerSetByte(P4_CF_DDR_RX_DLY0, (ucBestPhase / 2));

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
//**********************************************************************************//
//**********************************RX2 Ien Phase************************************//
//**********************************************************************************//

    ucTempDiffPhase = 0;

    for(ucCount = 0; ucCount < 128; ucCount++)
    {
        ScalerSetByte(P4_27_DDR_RX2_DLY0, ucCount);

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

            bPhaseSearch = _ON;
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("rx2 ien", g_ucPhaseCount);
#endif
    }

    if(bPhaseSearch == _ON)
    {
        if((128 - ucInitialPhase) > ucBestPhase)
        {
            ucBestPhase = (128 + ucInitialPhase) / 2;
        }
    }

    // Rx Ien2 Set Best Phase 1/4T
    g_ucDDR1Rx2IenDelayChain2 = (ucBestPhase / 2);

    ScalerSetByte(P4_27_DDR_RX2_DLY0, (ucBestPhase / 2));

#endif // End of #if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
}

//--------------------------------------------------
// Description  : DDR1 Rx Dqs Search Phse
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1RxDqsSearchPhase(void)
{
    BYTE ucCount = 0;
    BYTE ucInitialPhase = 0;
    BYTE ucEndPhase = 0;
    BYTE ucTempDiffPhase = 0;
    BYTE ucBestPhase = 0;
    bit bPhaseSearch = _FALSE;

    // Enable Rx Dqs Calibration Circuit
    ScalerDDR1RxDqsCalibrationEnable(_ON);

    // Disable Rx Dqs Calibration Circuit
    ScalerDDR1RxDqsCalibrationEnable(_OFF);

//**********************************************************************************//
//**********************************RX DQS0 Rising Phase****************************//
//**********************************************************************************//

    for(ucCount = 0; ucCount <= g_pucDDR1DelayChain[3]; ucCount++)
    {
        ScalerSetByte(P4_D0_DDR_RX_DLY1, ucCount);

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

            bPhaseSearch = _ON;
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("rx dqs0 rise", g_ucPhaseCount);
#endif
    }

    if(bPhaseSearch == _ON)
    {
        if((g_pucDDR1DelayChain[3] - ucInitialPhase) > ucBestPhase)
        {
            ucBestPhase = (g_pucDDR1DelayChain[3] + ucInitialPhase) / 2;
        }
    }

    // Best Phase >= 1/4T Position
    if(ucBestPhase >= (g_pucDDR1DelayChain[3] / 2))
    {
        ucBestPhase = (ucBestPhase / 4);
    }
    else
    {
        ucBestPhase = (ucBestPhase / 2);
    }

    g_pucDDR1InitialPhase[3] = ucBestPhase;

    ScalerSetByte(P4_D0_DDR_RX_DLY1, ucBestPhase);

//**********************************************************************************//
//*********************************RX DQS0 Falling Phase*****************************//
//**********************************************************************************//
    ucTempDiffPhase = 0;

    for(ucCount = 0; ucCount <= g_pucDDR1DelayChain[4]; ucCount++)
    {
        ScalerSetByte(P4_D1_DDR_RX_DLY2, ucCount);

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

            bPhaseSearch = _ON;
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("rx dqs0 fall", g_ucPhaseCount);
#endif
    }

    if(bPhaseSearch == _ON)
    {
        if((g_pucDDR1DelayChain[4] - ucInitialPhase) > ucBestPhase)
        {
            ucBestPhase = (g_pucDDR1DelayChain[4] + ucInitialPhase) / 2;
        }
    }

    // Best Phase >= 1/4T Position
    if(ucBestPhase >= (g_pucDDR1DelayChain[4] / 2))
    {
        ucBestPhase = (ucBestPhase / 4);
    }
    else
    {
        ucBestPhase = (ucBestPhase / 2);
    }

    g_pucDDR1InitialPhase[4] = ucBestPhase;

    ScalerSetByte(P4_D1_DDR_RX_DLY2, ucBestPhase);

//**********************************************************************************//
//**********************************RX DQS1 Rising Phase****************************//
//**********************************************************************************//
    ucTempDiffPhase = 0;

    for(ucCount = 0; ucCount <= g_pucDDR1DelayChain[5]; ucCount++)
    {
        ScalerSetByte(P4_D2_DDR_RX_DLY3, ucCount);

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

            bPhaseSearch = _ON;
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("rx dqs1 rise", g_ucPhaseCount);
#endif
    }

    if(bPhaseSearch == _ON)
    {
        if((g_pucDDR1DelayChain[5] - ucInitialPhase) > ucBestPhase)
        {
            ucBestPhase = (g_pucDDR1DelayChain[5] + ucInitialPhase) / 2;
        }
    }

    // Best Phase >= 1/4T Position
    if(ucBestPhase >= (g_pucDDR1DelayChain[5] / 2))
    {
        ucBestPhase = (ucBestPhase / 4);
    }
    else
    {
        ucBestPhase = (ucBestPhase / 2);
    }

    g_pucDDR1InitialPhase[5] = ucBestPhase;

    ScalerSetByte(P4_D2_DDR_RX_DLY3, ucBestPhase);

//**********************************************************************************//
//*********************************RX DQS1 Falling Phase****************************//
//**********************************************************************************//
    ucTempDiffPhase = 0;

    for(ucCount = 0; ucCount <= g_pucDDR1DelayChain[6]; ucCount++)
    {
        ScalerSetByte(P4_D3_DDR_RX_DLY4, ucCount);

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

            bPhaseSearch = _ON;
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("rx dqs1 fall", g_ucPhaseCount);
#endif
    }

    if(bPhaseSearch == _ON)
    {
        if((g_pucDDR1DelayChain[6] - ucInitialPhase) > ucBestPhase)
        {
            ucBestPhase = (g_pucDDR1DelayChain[6] + ucInitialPhase) / 2;
        }
    }

    // Best Phase >= 1/4T Position
    if(ucBestPhase >= (g_pucDDR1DelayChain[6] / 2))
    {
        ucBestPhase = (ucBestPhase / 4);
    }
    else
    {
        ucBestPhase = (ucBestPhase / 2);
    }

    g_pucDDR1InitialPhase[6] = ucBestPhase;

    ScalerSetByte(P4_D3_DDR_RX_DLY4, ucBestPhase);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
//**********************************************************************************//
//**********************************RX2 DQS2 Rising Phase****************************//
//**********************************************************************************//

    ucTempDiffPhase = 0;
    for(ucCount = 0; ucCount <= g_pucDDR1DelayChain2[3]; ucCount++)
    {
        ScalerSetByte(P4_30_DDR_RX2_DLY1, ucCount);

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

            bPhaseSearch = _ON;
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("rx2 dqs2 rise", g_ucPhaseCount);
#endif
    }

    if(bPhaseSearch == _ON)
    {
        if((g_pucDDR1DelayChain2[3] - ucInitialPhase) > ucBestPhase)
        {
            ucBestPhase = (g_pucDDR1DelayChain2[3] + ucInitialPhase) / 2;
        }
    }

    // Best Phase >= 1/4T Position
    if(ucBestPhase >= (g_pucDDR1DelayChain2[3] / 2))
    {
        ucBestPhase = (ucBestPhase / 4);
    }
    else
    {
        ucBestPhase = (ucBestPhase / 2);
    }

    g_pucDDR1InitialPhase2[3] = ucBestPhase;

    ScalerSetByte(P4_30_DDR_RX2_DLY1, ucBestPhase);

//**********************************************************************************//
//*********************************RX2 DQS2 Falling Phase*****************************//
//**********************************************************************************//
    ucTempDiffPhase = 0;

    for(ucCount = 0; ucCount <= g_pucDDR1DelayChain2[4]; ucCount++)
    {
        ScalerSetByte(P4_31_DDR_RX2_DLY2, ucCount);

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

            bPhaseSearch = _ON;
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("rx2 dqs2 fall", g_ucPhaseCount);
#endif
    }

    if(bPhaseSearch == _ON)
    {
        if((g_pucDDR1DelayChain2[4] - ucInitialPhase) > ucBestPhase)
        {
            ucBestPhase = (g_pucDDR1DelayChain2[4] + ucInitialPhase) / 2;
        }
    }

    // Best Phase >= 1/4T Position
    if(ucBestPhase >= (g_pucDDR1DelayChain2[4] / 2))
    {
        ucBestPhase = (ucBestPhase / 4);
    }
    else
    {
        ucBestPhase = (ucBestPhase / 2);
    }

    g_pucDDR1InitialPhase2[4] = ucBestPhase;

    ScalerSetByte(P4_31_DDR_RX2_DLY2, ucBestPhase);

//**********************************************************************************//
//**********************************RX2 DQS3 Rising Phase****************************//
//**********************************************************************************//

    ucTempDiffPhase = 0;
    for(ucCount = 0; ucCount <= g_pucDDR1DelayChain2[5]; ucCount++)
    {
        ScalerSetByte(P4_32_DDR_RX2_DLY3, ucCount);

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

            bPhaseSearch = _ON;
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("rx dqs3 rise", g_ucPhaseCount);
#endif
    }

    if(bPhaseSearch == _ON)
    {
        if((g_pucDDR1DelayChain2[5] - ucInitialPhase) > ucBestPhase)
        {
            ucBestPhase = (g_pucDDR1DelayChain2[5] + ucInitialPhase) / 2;
        }
    }

    // Best Phase >= 1/4T Position
    if(ucBestPhase >= (g_pucDDR1DelayChain2[5] / 2))
    {
        ucBestPhase = (ucBestPhase / 4);
    }
    else
    {
        ucBestPhase = (ucBestPhase / 2);
    }

    g_pucDDR1InitialPhase2[5] = ucBestPhase;

    ScalerSetByte(P4_32_DDR_RX2_DLY3, ucBestPhase);

//**********************************************************************************//
//*********************************RX2 DQS3 Falling Phase*****************************//
//**********************************************************************************//
    ucTempDiffPhase = 0;

    for(ucCount = 0; ucCount <= g_pucDDR1DelayChain2[6]; ucCount++)
    {
        ScalerSetByte(P4_33_DDR_RX2_DLY4, ucCount);

        g_ucPhaseCount = ScalerDDR1McuReadWriteCheck((ucCount >> 6), ((ucCount << 2) & 0xFC), 0x00);

        if((g_ucPhaseCount == _TRUE) && (bPhaseSearch == _FALSE))
        {
            ucInitialPhase = ucCount;

            bPhaseSearch = _ON;
        }

        if((g_ucPhaseCount == _FALSE) && (bPhaseSearch == _ON))
        {
            ucEndPhase = ucCount;

            pData[2] = ucEndPhase - ucInitialPhase;

            if(pData[2] > ucTempDiffPhase)
            {
                ucTempDiffPhase = pData[2];

                ucBestPhase = (ucInitialPhase + ucEndPhase) / 2;
            }

            bPhaseSearch = _FALSE;
        }

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("counter", ucCount);
        DebugMessageMemoryPhaseCal("rx dqs3 fall", g_ucPhaseCount);
#endif
    }

    if(bPhaseSearch == _ON)
    {
        if((g_pucDDR1DelayChain2[6] - ucInitialPhase) > ucBestPhase)
        {
            ucBestPhase = (g_pucDDR1DelayChain2[6] + ucInitialPhase) / 2;
        }
    }

    // Best Phase >= 1/4T Position
    if(ucBestPhase >= (g_pucDDR1DelayChain2[6] / 2))
    {
        ucBestPhase = (ucBestPhase / 4);
    }
    else
    {
        ucBestPhase = (ucBestPhase / 2);
    }

    g_pucDDR1InitialPhase2[6] = ucBestPhase;

    ScalerSetByte(P4_33_DDR_RX2_DLY4, ucBestPhase);

#endif // End of  #if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
}

//--------------------------------------------------
// Description  : DDR1 Tx Clk Calibration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1TxClkCalibrationEnable(bit bEn)
{
    // Set Clk Gatting Idel and Stop time
    ScalerSetByte(P4_C9_SDR_STOPCLK_CNT, 0x02);
    ScalerSetByte(P4_CA_STOP_WAIT_CNT, 0x02);

    if(bEn == _ON)
    {
        // Enable DDR1 Clk Gatting Function
        ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));

        // Enable Tx Calibration Function
        ScalerSetBit(P4_CB_TX_PHASE_CALIBRATION, ~_BIT2, _BIT2);

        // Pob Tx delay chain value of half clock cycle
        g_pucDDR1DelayChain[0] = (ScalerGetByte(P4_CC_TX_CALIBRATION_RESULT) & 0x7F);

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("Tx clk half T", g_pucDDR1DelayChain[0]);
#endif

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Enable Tx2 Calibration Function
        ScalerSetBit(P4_20_TX_PHASE_CALIBRATION_2, ~_BIT2, _BIT2);

        // Pob Tx2 delay chain value of half clock cycle
        g_pucDDR1DelayChain2[0] = (ScalerGetByte(P4_21_TX_CALIBRATION_RESULT_2) & 0x7F);

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("Tx2 clk half T", g_pucDDR1DelayChain2[0]);
#endif

#endif
    }
    else
    {
        // Disable DDR1 Clk Gatting Function
        ScalerSetBit(P4_BE_SDR_RX_PHASE_CALIBRATION, ~(_BIT5 | _BIT1), 0x00);

        // Disable Tx Calibration Function
        ScalerSetBit(P4_CB_TX_PHASE_CALIBRATION, ~_BIT2, 0x00);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Disable Tx2 Calibration Function
        ScalerSetBit(P4_20_TX_PHASE_CALIBRATION_2, ~_BIT2, 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : DDR1 Tx Dqs Calibration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1TxDqsCalibrationEnable(bit bEn)
{
    if(bEn == _ON)
    {
        // Enable Tx Dqs0 Calibration Circuit
        ScalerSetBit(P4_F6_DDR_AUTO_CALIB4, ~_BIT7, _BIT7);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Enable Tx Dqs Generation 8 dqa cycle
        ScalerSetBit(P4_20_TX_PHASE_CALIBRATION_2, ~_BIT1, _BIT1);

        // Enable Tx Dqs2 Calibration Circuit
        ScalerSetBit(P4_23_DDR_AUTO_CALIB6, ~_BIT7, _BIT7);
#endif

        for(PDATA_WORD(3) = 0; PDATA_WORD(3) < 270; PDATA_WORD(3)++)
        {
            ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT7 | _BIT6 | _BIT5), _DDR1_MCU_COMMAND_WRITE);
            ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT7 | _BIT6 | _BIT5), _DDR1_MCU_COMMAND_NOP_FINISH);
        }

        // Pob Tx Dqs0 delay chain value of half clock cycle
        g_pucDDR1DelayChain[1] = (ScalerGetByte(P4_F7_DDR_AUTO_CALIB_RLT4) & 0x7F);

        // Pob Tx Dqs1 delay chain value of half clock cycle
        g_pucDDR1DelayChain[2] = g_pucDDR1DelayChain[1];

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("Tx dqs0 half T", g_pucDDR1DelayChain[1]);
        DebugMessageMemoryPhaseCal("Tx dqs1 half T", g_pucDDR1DelayChain[2]);
#endif

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Pob Tx Dqs2 delay chain value of half clock cycle
        g_pucDDR1DelayChain2[1] = (ScalerGetByte(P4_24_DDR_AUTO_CALIB_RLT6) & 0x7F);

        // Pob Tx Dqs3 delay chain value of half clock cycle
        g_pucDDR1DelayChain2[2] = g_pucDDR1DelayChain2[1];

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("Tx dqs2 half T", g_pucDDR1DelayChain2[1]);
        DebugMessageMemoryPhaseCal("Tx dqs3 half T", g_pucDDR1DelayChain2[2]);
#endif

#endif
    }
    else
    {
        // Disable Tx Dqs0 Calibration Circuit
        ScalerSetBit(P4_F6_DDR_AUTO_CALIB4, ~_BIT7, 0x00);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Disable Tx2 Dqs Generation 8 dqa cycle
        ScalerSetBit(P4_20_TX_PHASE_CALIBRATION_2, ~_BIT1, 0x00);

        // Disable Tx Dqs2 Calibration Circuit
        ScalerSetBit(P4_23_DDR_AUTO_CALIB6, ~_BIT7, 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : DDR1 Rx Dqs Calibration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1RxDqsCalibrationEnable(bit bEn)
{
    if(bEn == _ON)
    {
#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // For 2PCS DDR1 RX Calibration Read Data of Half T
        ScalerSetByte(P4_BD_SDR_MCU_RD_LEN, 0x02);
#endif

        // Enable Rx Dqs0 Rising Calibration Circuit
        ScalerSetBit(P4_D9_DDR_AUTO_CALIB0, ~_BIT7, _BIT7);

        // Enable Rx Dqs0 Falling Calibration Circuit
        ScalerSetBit(P4_DB_DDR_AUTO_CALIB1, ~_BIT7, _BIT7);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Enable Rx Dqs2 Rising Calibration Circuit
        ScalerSetBit(P4_28_DDR_AUTO_CALIB7, ~_BIT7, _BIT7);

        // Enable Rx Dqs2 Falling Calibration Circuit
        ScalerSetBit(P4_2A_DDR_AUTO_CALIB8, ~_BIT7, _BIT7);
#endif

        for(PDATA_WORD(3) = 0; PDATA_WORD(3) < 270; PDATA_WORD(3)++)
        {
            ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT7 | _BIT6 | _BIT5), _DDR1_MCU_COMMAND_READ);
            ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT7 | _BIT6 | _BIT5), _DDR1_MCU_COMMAND_NOP_FINISH);
        }

        // Pob Rx Dqs0 Rising delay chain value of half clock cycle
        g_pucDDR1DelayChain[3] = (ScalerGetByte(P4_DA_DDR_AUTO_CALIB_RLT0) & 0x7F);

        // Pob Rx Dqs0 Falling delay chain value of half clock cycle
        g_pucDDR1DelayChain[4] = (ScalerGetByte(P4_DC_DDR_AUTO_CALIB_RLT1) & 0x7F);

        // Pob Rx Dqs1 Rising delay chain value of half clock cycle
        g_pucDDR1DelayChain[5] = g_pucDDR1DelayChain[3];

        // Pob Rx Dqs1 Falling delay chain value of half clock cycle
        g_pucDDR1DelayChain[6] = g_pucDDR1DelayChain[4];

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("Rx dqs0 half T", g_pucDDR1DelayChain[3]);
        DebugMessageMemoryPhaseCal("Rx dqs1 half T", g_pucDDR1DelayChain[4]);
        DebugMessageMemoryPhaseCal("Rx dqs2 half T", g_pucDDR1DelayChain[5]);
        DebugMessageMemoryPhaseCal("Rx dqs3 half T", g_pucDDR1DelayChain[6]);
#endif

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Pob Rx Dqs2 Rising delay chain value of half clock cycle
        g_pucDDR1DelayChain2[3] = (ScalerGetByte(P4_29_DDR_AUTO_CALIB_RLT7) & 0x7F);

        // Pob Rx Dqs2 Falling delay chain value of half clock cycle
        g_pucDDR1DelayChain2[4] = (ScalerGetByte(P4_2B_DDR_AUTO_CALIB_RLT8) & 0x7F);

        // Pob Rx Dqs3 Rising delay chain value of half clock cycle
        g_pucDDR1DelayChain2[5] = g_pucDDR1DelayChain2[3];

        // Pob Rx Dqs3 Falling delay chain value of half clock cycle
        g_pucDDR1DelayChain2[6] = g_pucDDR1DelayChain2[4];

#if(_DDR1_MCU_ALL_PHASE_CHECK == _ON)
        DebugMessageMemoryPhaseCal("Rx2 dqs0 half T", g_pucDDR1DelayChain2[3]);
        DebugMessageMemoryPhaseCal("Rx2 dqs1 half T", g_pucDDR1DelayChain2[4]);
        DebugMessageMemoryPhaseCal("Rx2 dqs2 half T", g_pucDDR1DelayChain2[5]);
        DebugMessageMemoryPhaseCal("Rx2 dqs3 half T", g_pucDDR1DelayChain2[6]);
#endif

#endif
    }
    else
    {
        // Disable Rx Dqs0 Rising Calibration Circuit
        ScalerSetBit(P4_D9_DDR_AUTO_CALIB0, ~_BIT7, 0x00);

        // Disable Rx Dqs0 Falling Calibration Circuit
        ScalerSetBit(P4_DB_DDR_AUTO_CALIB1, ~_BIT7, 0x00);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Disable Rx Dqs2 Rising Calibration Circuit
        ScalerSetBit(P4_28_DDR_AUTO_CALIB7, ~_BIT7, 0x00);

        // Disable Rx Dqs2 Falling Calibration Circuit
        ScalerSetBit(P4_2A_DDR_AUTO_CALIB8, ~_BIT7, 0x00);

        // Restore 2PCS DDR1 SRAM Length
        ScalerSetByte(P4_BD_SDR_MCU_RD_LEN, 0x01);
#endif
    }
}

//--------------------------------------------------
// Description  : DDR1 Read Write Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDDR1McuReadWriteCheck(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL)
{
    ScalerSetByte(P4_B8_SDR_ADDR_H, ucAddrH);
    ScalerSetByte(P4_B9_SDR_ADDR_M, ucAddrM);
    ScalerSetByte(P4_BA_SDR_ADDR_L, ucAddrL);

    ScalerDDR1WriteToFifo();

    ScalerDDR1ReadFromFifo();

    ScalerSetByte(P4_BB_SDR_ACCESS_CMD, 0x00);

    for(pData[14] = 0; pData[14] < sizeof(tDDR_PATTERN); pData[14]++)
    {
        if(ScalerGetByte(P4_BC_SDR_DATA_BUF) != tDDR_PATTERN[pData[14]])
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DDR1 Write Data To FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1WriteToFifo(void)
{
    ScalerDDR1ClearFifo();

    ScalerSetByte(P4_BB_SDR_ACCESS_CMD, 0x00);

    for(pData[14] = 0; pData[14] < sizeof(tDDR_PATTERN); pData[14]++)
    {
        ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[14]);
        ScalerSetByte(P4_BC_SDR_DATA_BUF, tDDR_PATTERN[pData[14]]);
    }

    ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT7 | _BIT6 | _BIT5), _DDR1_MCU_COMMAND_WRITE);

    if(ScalerDDR1CheckCommandFinish() == _FALSE)
    {
        DebugMessageMemoryPhaseCal("Write Command Fail", 0x00);
    }
}

//--------------------------------------------------
// Description  : DDR1 Write Data To FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1ReadFromFifo(void)
{
    ScalerDDR1ClearFifo();

    ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT7 | _BIT6 | _BIT5), _DDR1_MCU_COMMAND_READ);

    if(ScalerDDR1CheckCommandFinish() == _FALSE)
    {
        DebugMessageMemoryPhaseCal("Read Command Fail", 0x00);
    }
}

//--------------------------------------------------
// Description  : DDR1 Clear Fifo
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1ClearFifo(void)
{
    ScalerSetByte(P4_BB_SDR_ACCESS_CMD, 0x00);

    for(pData[14] = 0; pData[14] < 32; pData[14]++)
    {
        ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[14]);
        ScalerSetByte(P4_BC_SDR_DATA_BUF, 0x00);
    }
}

//--------------------------------------------------
// Description  : DDR1 Check Command Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDDR1CheckCommandFinish(void)
{
    if(ScalerTimerPollingFlagProc(5, P4_BB_SDR_ACCESS_CMD, (_BIT7 | _BIT6 | _BIT5), 0x00) == _FALSE)
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : DDR1 On Line Phase Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1OnLinePhaseCntCheck(void)
{
    static BYTE sucDDR1OnLineCheckLoop = _DDR1_MCU_ONLINE_START_LOOP;

    if(sucDDR1OnLineCheckLoop-- == _DDR1_MCU_ONLINE_END_LOOP)
    {
        BYTE ucRxClkIndex = 0;
        SWORD shHalfCycleTapDiff = 0;
        SWORD shCurrOneCycleTap = 0;

        // Set Loop Counter 60 times Restore
        sucDDR1OnLineCheckLoop = _DDR1_MCU_ONLINE_START_LOOP;

        ScalerDDR1OnLinePhaseCalibration(_ON);

        for(ucRxClkIndex = _DDR1_RX_DQS0_R; ucRxClkIndex <= _DDR1_RX_DQS1_F; ucRxClkIndex++)
        {
            shHalfCycleTapDiff = (SWORD)g_pucDDR1OnLineDelayChain[ucRxClkIndex] - (SWORD)g_pucDDR1DelayChain[ucRxClkIndex];

            if(abs(shHalfCycleTapDiff) > _DDR1_ONLINE_TAP_DIFF_THRESHOLD)
            {
                shCurrOneCycleTap = g_pucDDR1OnLineDelayChain[ucRxClkIndex] * 2;
                ScalerSetByte(tDDR1_FINE_DLY_REG0[ucRxClkIndex],
                              (BYTE)(((SWORD)g_pucDDR1InitialPhase[ucRxClkIndex] + shHalfCycleTapDiff / 2 + shCurrOneCycleTap) % shCurrOneCycleTap));
            }
        }

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
        for(ucRxClkIndex = _DDR1_RX_DQS2_R; ucRxClkIndex <= _DDR1_RX_DQS3_F; ucRxClkIndex++)
        {
            shHalfCycleTapDiff = (SWORD)g_pucDDR1OnLineDelayChain2[ucRxClkIndex] - (SWORD)g_pucDDR1DelayChain2[ucRxClkIndex];

            if(abs(shHalfCycleTapDiff) > _DDR1_ONLINE_TAP_DIFF_THRESHOLD)
            {
                shCurrOneCycleTap = g_pucDDR1OnLineDelayChain2[ucRxClkIndex] * 2;
                ScalerSetByte(tDDR1_FINE_DLY_REG1[ucRxClkIndex],
                              (BYTE)(((SWORD)g_pucDDR1InitialPhase2[ucRxClkIndex] + shHalfCycleTapDiff / 2 + shCurrOneCycleTap) % shCurrOneCycleTap));
            }
        }
#endif // End of  #if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        ScalerDDR1OnLinePhaseCalibration(_OFF);
    }
}
//--------------------------------------------------
// Description  : DDR1 On Line Phase Calibration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1OnLinePhaseCalibration(bit bEn)
{
    if(bEn == _ON)
    {
#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // For 2PCS DDR1 RX Calibration Read Data of Half T
        ScalerSetByte(P4_BD_SDR_MCU_RD_LEN, 0x02);
#endif
        // Enable MCU Mode Token Ring
        ScalerSetByte(P4_AB_SDR_RSC_MCU, 0x30);

        // Enable Rx Dqs0 Rising Calibration Circuit
        ScalerSetBit(P4_D9_DDR_AUTO_CALIB0, ~_BIT7, _BIT7);

        // Enable Rx Dqs0 Falling Calibration Circuit
        ScalerSetBit(P4_DB_DDR_AUTO_CALIB1, ~_BIT7, _BIT7);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Enable Rx Dqs2 Rising Calibration Circuit
        ScalerSetBit(P4_28_DDR_AUTO_CALIB7, ~_BIT7, _BIT7);

        // Enable Rx Dqs2 Falling Calibration Circuit
        ScalerSetBit(P4_2A_DDR_AUTO_CALIB8, ~_BIT7, _BIT7);
#endif

        for(PDATA_DWORD(3) = 0; PDATA_DWORD(3) < 270; PDATA_DWORD(3)++)
        {
            ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT7 | _BIT6 | _BIT5), _DDR1_MCU_COMMAND_READ);

            // Delay Time us [85,x]
            DELAY_XUS(85);

            ScalerSetBit(P4_BB_SDR_ACCESS_CMD, ~(_BIT7 | _BIT6 | _BIT5), _DDR1_MCU_COMMAND_NOP_FINISH);
        }

        // Pob Rx Dqs0 Rising delay chain value of half clock cycle
        g_pucDDR1OnLineDelayChain[3] = (ScalerGetByte(P4_DA_DDR_AUTO_CALIB_RLT0) & 0x7F);

        // Pob Rx Dqs0 Falling delay chain value of half clock cycle
        g_pucDDR1OnLineDelayChain[4] = (ScalerGetByte(P4_DC_DDR_AUTO_CALIB_RLT1) & 0x7F);

        // Pob Rx Dqs1 Rising delay chain value of half clock cycle
        g_pucDDR1OnLineDelayChain[5] = g_pucDDR1DelayChain[3];

        // Pob Rx Dqs1 Falling delay chain value of half clock cycle
        g_pucDDR1OnLineDelayChain[6] = g_pucDDR1DelayChain[4];

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Pob Rx Dqs2 Rising delay chain value of half clock cycle
        g_pucDDR1OnLineDelayChain2[3] = (ScalerGetByte(P4_29_DDR_AUTO_CALIB_RLT7) & 0x7F);

        // Pob Rx Dqs2 Falling delay chain value of half clock cycle
        g_pucDDR1OnLineDelayChain2[4] = (ScalerGetByte(P4_2B_DDR_AUTO_CALIB_RLT8) & 0x7F);

        // Pob Rx Dqs3 Rising delay chain value of half clock cycle
        g_pucDDR1OnLineDelayChain2[5] = g_pucDDR1DelayChain2[3];

        // Pob Rx Dqs3 Falling delay chain value of half clock cycle
        g_pucDDR1OnLineDelayChain2[6] = g_pucDDR1DelayChain2[4];
#endif
    }
    else
    {
        // Disable MCU Mode Token Ring
        ScalerSetByte(P4_AB_SDR_RSC_MCU, 0x00);

        // Disable Rx Dqs0 Rising Calibration Circuit
        ScalerSetBit(P4_D9_DDR_AUTO_CALIB0, ~_BIT7, 0x00);

        // Disable Rx Dqs0 Falling Calibration Circuit
        ScalerSetBit(P4_DB_DDR_AUTO_CALIB1, ~_BIT7, 0x00);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)

        // Disable Rx2 Dqs2 Rising Calibration Circuit
        ScalerSetBit(P4_28_DDR_AUTO_CALIB7, ~_BIT7, 0x00);

        // Disable Rx2 Dqs2 Falling Calibration Circuit
        ScalerSetBit(P4_2A_DDR_AUTO_CALIB8, ~_BIT7, 0x00);

        // Restore 2PCS DDR1 SRAM Length
        ScalerSetByte(P4_BD_SDR_MCU_RD_LEN, 0x01);
#endif
    }
}

//--------------------------------------------------
// Description  : DDR1 Restore Initial Phase
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1RestoreInitialPhase(void)
{
    ScalerSetByte(P4_C1_TX_CLK_DLY2, g_pucDDR1InitialPhase[0]);
    ScalerSetByte(P4_CD_DDR_TX_DLY0, g_pucDDR1InitialPhase[1]);
    ScalerSetByte(P4_CE_DDR_TX_DLY1, g_pucDDR1InitialPhase[2]);
    ScalerSetByte(P4_D0_DDR_RX_DLY1, g_pucDDR1InitialPhase[3]);
    ScalerSetByte(P4_D1_DDR_RX_DLY2, g_pucDDR1InitialPhase[4]);
    ScalerSetByte(P4_D2_DDR_RX_DLY3, g_pucDDR1InitialPhase[5]);
    ScalerSetByte(P4_D3_DDR_RX_DLY4, g_pucDDR1InitialPhase[6]);
    ScalerSetByte(P4_CF_DDR_RX_DLY0, g_ucDDR1RxIenDelayChain);

#if(_MEMORY_SIZE_CONFIG == _4M_16BIT_DDR1_2PCS)
    ScalerSetByte(P4_22_TX2_CLK_DLY, g_pucDDR1InitialPhase2[0]);
    ScalerSetByte(P4_25_DDR_TX2_DLY2, g_pucDDR1InitialPhase2[1]);
    ScalerSetByte(P4_26_DDR_TX2_DLY3, g_pucDDR1InitialPhase2[2]);
    ScalerSetByte(P4_30_DDR_RX2_DLY1, g_pucDDR1InitialPhase2[3]);
    ScalerSetByte(P4_31_DDR_RX2_DLY2, g_pucDDR1InitialPhase2[4]);
    ScalerSetByte(P4_32_DDR_RX2_DLY3, g_pucDDR1InitialPhase2[5]);
    ScalerSetByte(P4_33_DDR_RX2_DLY4, g_pucDDR1InitialPhase2[6]);
    ScalerSetByte(P4_27_DDR_RX2_DLY0, g_ucDDR1Rx2IenDelayChain2);
#endif
}

#endif  // End of #if(_DDR1_PHASE_CALIBRATION == _ON)
