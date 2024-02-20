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
// ID Code      : RL6492_Series_DisplayDPTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_PANEL_STYLE == _PANEL_DPTX)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DISPLAY_DP_TX_SKEW_LANE0                   0
#define _DISPLAY_DP_TX_SKEW_LANE1                   2
#define _DISPLAY_DP_TX_SKEW_LANE2                   4
#define _DISPLAY_DP_TX_SKEW_LANE3                   6

//--------------------------------------------------
// Definations of DP1.1 DPLL VCO Target
//--------------------------------------------------
#define _DP_DPLL_TARGET_FREQ                        216000 // kHz

//--------------------------------------------------
// Definations of DPTX DPLL Range
//--------------------------------------------------
#define _DP_DPLL_BOUNDRY_0                          600000
#define _DP_DPLL_BOUNDRY_1                          1200000
#define _DP_DPLL_BOUNDRY_2                          2400000

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tDPTX_RBR_DRV_TABLE[32] =
{
    // Pre-emphasis->      0                    1                    2                   3
    // VoltageSwing
    /*    0    */      0x50, 0x00,         0x80, 0x08,         0xC0, 0x0E,         0xC0, 0x11,
    /*    1    */      0x80, 0x00,         0xC0, 0x08,         0xC0, 0x08,         0xC0, 0x0A,
    /*    2    */      0xC0, 0x04,         0xC0, 0x04,         0xC0, 0x04,         0xC0, 0x04,
    /*    3    */      0xC0, 0x04,         0xC0, 0x04,         0xC0, 0x04,         0xC0, 0x04,
};

BYTE code tDPTX_HBR_DRV_TABLE[32] =
{
    // Pre-emphasis->      0                    1                    2                   3
    // VoltageSwing
    /*    0    */      0x50, 0x00,         0x80, 0x0C,         0xC0, 0x11,         0xC0, 0x11,
    /*    1    */      0x80, 0x00,         0xC0, 0x0A,         0xC0, 0x0A,         0xC0, 0x0A,
    /*    2    */      0xC0, 0x04,         0xC0, 0x04,         0xC0, 0x04,         0xC0, 0x04,
    /*    3    */      0xC0, 0x04,         0xC0, 0x04,         0xC0, 0x04,         0xC0, 0x04,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDisplayDPTxPollingHotPlug(WORD usNum);
bit ScalerDisplayDPTxLinkSequence(void);
void ScalerDisplayDPTxLinkConfigCheck(void);
void ScalerDisplayDPTxCheckSSC(void);
void ScalerDisplayDPTxStreamHanlder(bit bOutput);

#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
void ScalerDisplayDPTxLinkSignalForceOutput(void);
#endif

void ScalerDisplayDPTxPowerSequenceProc(bit bLevel);
void ScalerDisplayDPTxPhyInitial(void);
void ScalerDisplayDPTxSSCSet(bit bSscEn);
void ScalerDisplayDPTxPhy(bit bOn);
void ScalerDisplayDPTxPLL(bit bOn);
void ScalerDisplayDPTxPower(bit bOn);
void ScalerDisplayDPTxSetLinkRate(void);
void ScalerDisplayDPTxSetZ0(void);

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
void ScalerDisplayDPTx1AuxPHYSet(BYTE ucMode);
void ScalerDisplayDPTx1SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
void ScalerDisplayDPTx1SignalInitialSetting(void);
EnumDisplayDPTxTrainPattern ScalerDisplayDPTx1SetTp2PatternType(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Wait for Dp Tx Htpdn
// Input Value  : WORD usNum
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxPollingHotPlug(WORD usNum)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;
    bit bHPCheck = _FALSE;
    usPreviousTime = g_usTimerCounter;

    do
    {
        bHPCheck = _SUCCESS;

        if(ScalerGetBit(P9C_70_HPD_CTRL, _BIT2) == _BIT2)
        {
            bHPCheck &= _SUCCESS;

            PCB_DPTX1_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_HPD_ON);
        }
        else
        {
            bHPCheck &= _FALSE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while((usTimeElapsed <= usNum) && (bHPCheck != _SUCCESS));

    DebugMessageCheck("eDP HPD Time", usTimeElapsed);
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Link Sequence
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDisplayDPTxLinkSequence(void)
{
    bit bLTCheck = _SUCCESS;
    BYTE ucLTRetryNum = 0;

    do
    {
        bLTCheck = _SUCCESS;

        // Check DPTx Link Config
        ScalerDisplayDPTxLinkConfigCheck();

        // Check DPTx SSCG Status
        ScalerDisplayDPTxCheckSSC();

        // Set Dptx1 Link Training
        ScalerDisplayDPTx1LinkTraining();

        if(GET_DISPLAY_DP_TX1_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PASS)
        {
            bLTCheck &= _SUCCESS;
        }
        else
        {
            bLTCheck &= _FALSE;
        }

        ucLTRetryNum += 1;

        ScalerTimerDelayXms(5);
    }
    while((ucLTRetryNum < 5) && (bLTCheck != _SUCCESS));

#if(_PANEL_DPTX_AUX_SET_TP_END_SEQUENCE == _TRAIN_PATTERN_END_AFTER_IDEL_PATTERN)
    // Training Pattern End For Link Training
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x02, 1, pData);
#endif // End of #if(_PANEL_DPTX_AUX_SET_TP_END_SEQUENCE == _TRAIN_PATTERN_END_AFTER_IDEL_PATTERN)

    return bLTCheck;
}

//--------------------------------------------------
// Description  : Check for Dp Tx Link Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxLinkConfigCheck(void)
{
    SET_DISPLAY_DP_TX1_LINK_CONFIG(ScalerDisplayDPTx1LinkConfig());
}

//--------------------------------------------------
// Description  : Setting for eDp Tx SSCG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxCheckSSC(void)
{
    bit bDpTxSscEn = _ENABLE;

    bDpTxSscEn &= GET_DISPLAY_DP_TX1_DOWN_SPREAD();

    bDpTxSscEn = (_PANEL_DPTX_SPREAD_RANGE != 0) ? bDpTxSscEn : _DISABLE;

    SET_DISPLAY_DP_TX_SSCG_CONFIG(bDpTxSscEn);
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Stream Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxStreamHanlder(bit bOutput)
{
    ScalerDisplayDPTx1VideoStreamOutput(bOutput);
}

#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Link TSignal Force Output
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxLinkSignalForceOutput(void)
{
    ScalerDisplayDPTx1LinkForceOutput();

#if(_PANEL_DPTX_AUX_SET_TP_END_SEQUENCE == _TRAIN_PATTERN_END_AFTER_IDEL_PATTERN)
    // Training Pattern End For Link Training
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x02, 1, pData);
#endif // End of #if(_PANEL_DPTX_AUX_SET_TP_END_SEQUENCE == _TRAIN_PATTERN_END_AFTER_IDEL_PATTERN)
}
#endif

//--------------------------------------------------
// Description  : DP Tx Power Sequence Process
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxPowerSequenceProc(bit bLevel)
{
    bLevel = bLevel;

    PCB_DPTX1_POWER_SEQUENCE(bLevel);
}

//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxPhyInitial(void)
{
    // Set DISP mode is Dp Tx
    ScalerSetBit(P39_00_LVDS_DISP_TYPE, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // Set Dp Tx Digital Phy Initial
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

    // Set Dp Tx Common Mode Voltage
    ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

    // Set Dp Tx Driving Current
    ScalerSetByte(P55_57_DPTX_SWING_CURRENT_1, 0x44);
    ScalerSetByte(P55_58_DPTX_SWING_CURRENT_2, 0x44);

    // Set Dp Tx IB2X Control
    ScalerSetByte(P55_56_DPTX_DOUBLE_HALF_CURRENT, 0xFF);

    // Enable Vby1 Phy power
    ScalerDisplayDPTxAnalogPhyConrol(_ENABLE);

    // Initial Z0 for DPTx
    ScalerDisplayDPTxSetZ0();

    // Lane Skew Setting
    ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((_DISPLAY_DP_TX_SKEW_LANE0 << 3) | _DISPLAY_DP_TX_SKEW_LANE1));
    ScalerSetBit(P38_86_PHY0_TXBIST_00_H1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((_DISPLAY_DP_TX_SKEW_LANE2 << 5) | (_DISPLAY_DP_TX_SKEW_LANE3 << 2)));

    // Waiting for PHY initial
    ScalerTimerDelayXms(10);
}

//--------------------------------------------------
// Description  : Dp Tx SSC Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxSSCSet(bit bSscEn)
{
    if(bSscEn == _ENABLE)
    {
        PDATA_WORD(0) = (WORD)((ScalerGetBit(P38_DD_DPTX_CMU12, 0x1F) << 4) | (ScalerGetByte(P38_DE_DPTX_CMU13) >> 4));
        PDATA_WORD(1) = (WORD)((ScalerGetBit(P38_DE_DPTX_CMU13, 0x0F) << 8) | ScalerGetByte(P38_DF_DPTX_CMU14));

        // Calculate SSC Frequency = 30~33k
        PDATA_WORD(3) = (((_EXT_XTAL / _DISPLAY_DP_TX_SSC_FREQ) + 2) & 0xFFFC);

        // Calculate SSC downspread
        PDATA_WORD(2) = ((((DWORD)PDATA_WORD(0) + 4) * 4096 + PDATA_WORD(1))) * 16 / 200 / PDATA_WORD(3) / 15 * _PANEL_DPTX_SPREAD_RANGE;

        // Set SSC Frequency = 30~33k
        ScalerSetByte(P38_E1_DPTX_CMU16, (BYTE)(PDATA_WORD(3) >> 8));
        ScalerSetByte(P38_E2_DPTX_CMU17, (BYTE)PDATA_WORD(3));

        // Set SSC downspread
        ScalerSetByte(P38_E3_DPTX_CMU18, (BYTE)(PDATA_WORD(2) >> 8));
        ScalerSetByte(P38_E4_DPTX_CMU19, (BYTE)PDATA_WORD(2));

        // [5] 1: Enable SSC, 0: disable
        // [4] 0: 1st Order SDM, 1:2nd Order SDM
        // [3] 0: Triangular wave, 1: Square wave
        ScalerSetBit(P38_D5_DPTX_CMU5, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
    }
    else
    {
        // Disable SSC
        ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Digital Phy
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxPhy(bit bOn)
{
    if(bOn == _ON)
    {
        // Set Dp Tx Digital Phy
        ScalerSetBit(P38_91_PHY_RST, ~_BIT0, _BIT0);

        // Enable Digital Phy output
        ScalerSetByte(P38_8E_PHY0_TXBIST_02_H1, 0x0F);
    }

    else
    {
        // Disable Digital Phy output
        ScalerSetByte(P38_8E_PHY0_TXBIST_02_H1, 0x00);

        // Reset Dp Tx Digital Phy
        ScalerSetBit(P38_91_PHY_RST, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Dp Tx PLL Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxPLL(bit bOn)
{
    if(bOn == _ON)
    {
        // Enable eDPTx Clock
        ScalerSetBit(P1_C8_DCLK_GATED_CTRL2, ~_BIT1, _BIT1);

        // Power Up Dp Tx Vby1 PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~_BIT3, _BIT3);
    }

    else
    {
        // Power Down Dp Tx Vby PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~_BIT3, 0x00);

        // Disable eDPTx Clock
        ScalerSetBit(P1_C8_DCLK_GATED_CTRL2, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Dp Tx Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxPower(bit bOn)
{
    if(bOn == _ON)
    {
        // Disable Weakly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, 0x00);

        // Power Up Dp Tx Analog Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable Dp Tx LDO Power
        ScalerSetBit(P55_73_DPTX_CMU3, ~_BIT6, _BIT6);
    }

    else
    {
        // Disable Dp Tx LDO Power
        ScalerSetBit(P55_73_DPTX_CMU3, ~_BIT6, 0x00);

        // Power Down Dp Tx Analog Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6), 0x00);

        // Enable Weakly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : Settings for Dp Tx VBy1 Link Rate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxSetLinkRate(void)
{
    pData[0] = GET_DISPLAY_DP_TX1_LINK_RATE();
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Z0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxSetZ0(void)
{
    // Set Dptx Z0
    ScalerSetBit(P55_61_DPTX_Z0_TX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetByte(P55_62_DPTX_Z0_TX_2, 0x88);
    ScalerSetByte(P55_63_DPTX_Z0_TX_3, 0x88);
}

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
//--------------------------------------------------
// Description  : Dp Tx Aux PHY Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1AuxPHYSet(BYTE ucMode)
{
    if(ucMode == _DISPLAY_DP_TX_AUX_SINGLE_MODE)
    {
        // Set Aux Tx LDO
        ScalerSetBit(P9D_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_PANEL_DPTX_AUX_SWING_LEVEL << 4));

        // Set ADJR P
        ScalerSetBit(P9D_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Single End Mode and Enlarge Z0-P
        ScalerSetBit(P9D_62_AUX_2, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

        // Enable Enlarge Z0-N and Set ADJR-N = 0
        ScalerSetBit(P9D_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

        // Set TX ADJR-P and ADJR-N
        ScalerSetByte(P9D_67_DIG_TX_03, 0x00);
    }
    else
    {
        // Set Aux Tx LDO
        ScalerSetBit(P9D_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_PANEL_DPTX_AUX_SWING_LEVEL << 4));

        // Set ADJR P
        ScalerSetBit(P9D_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

        // Disable Single End Mode and Enlarge Z0-P
        ScalerSetBit(P9D_62_AUX_2, ~(_BIT5 | _BIT0), 0x00);

        // Disable Enlarge Z0-N and Set ADJR N
        ScalerSetBit(P9D_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

        // TX Z0 hand mode setting
        ScalerSetByte(P9D_67_DIG_TX_03, 0x88);
    }
}

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis)
{
    BYTE ucIndex = 0x00;
    BYTE *pucTable = 0;
    BYTE ucEfuseDriv = 0;
    WORD usTempDriv = 0;

#if(_PANEL_DPTX_SET_LT_SIGNAL_LEVEL_MODE == _PANEL_DPTX_LT_MANUAL_MODE)
    ucVoltageSwing = _PANEL_DPTX_SWING_LEVEL;
    ucPreEmphasis = _PANEL_DPTX_PREEMPHASIS_LEVEL;
#endif

    pucTable = (_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR) ? tDPTX_HBR_DRV_TABLE : tDPTX_RBR_DRV_TABLE;

    ucIndex = (ucVoltageSwing * 4 + ucPreEmphasis) * 2;

    // load LVDS driving from efuse
    ScalerEfuseGetData(_EFUSE_LVDS_DRIV, 1, &ucEfuseDriv);

    switch(enumLaneX)
    {
        case _DISPLAY_DP_TX_LANE_0: // LVDS_TXB0: Analog TXA0

            // Pre-emphasis
            ScalerSetBit(P55_52_DPTX_PREEM_TXB3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pucTable[ucIndex + 1] & 0x1F));

            // Calculate driving current
            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * pucTable[ucIndex + 0] / 98) : (pucTable[ucIndex + 0]);

            break;

        case _DISPLAY_DP_TX_LANE_1: // LVDS_TXB1: Analog TXA1

            // Pre-emphasis
            ScalerSetBit(P55_53_DPTX_PREEM_TXB4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pucTable[ucIndex + 1] & 0x1F));

            // Calculate driving current
            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * pucTable[ucIndex + 0] / 98) : (pucTable[ucIndex + 0]);

            break;

        case _DISPLAY_DP_TX_LANE_2: // LVDS_TXB2: Analog TXA2

            // Pre-emphasis
            ScalerSetBit(P55_50_DPTX_PREEM_TXA0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pucTable[ucIndex + 1] & 0x1F));

            // Calculate driving current
            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * pucTable[ucIndex + 0] / 98) : (pucTable[ucIndex + 0]);

            break;

        case _DISPLAY_DP_TX_LANE_3: // LVDS_TXB3: Analog TXA3

            // Pre-emphasis
            ScalerSetBit(P55_51_DPTX_PREEM_TXA1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pucTable[ucIndex + 1] & 0x1F));

            // Calculate driving current
            usTempDriv = (ucEfuseDriv != 0) ? ((DWORD)ucEfuseDriv * pucTable[ucIndex + 0] / 98) : (pucTable[ucIndex + 0]);

            break;

        default:

            break;
    }

    // Set Dp Tx Major Current Control
    ScalerSetByte(P55_0C_LVDS_COMMON_AB_CTRL12, ((usTempDriv < 0xFF) ? usTempDriv : 0xFF));
}

//--------------------------------------------------
// Description  : Dp Tx Main Link Power on
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1SignalInitialSetting(void)
{
#if (_PANEL_DPTX_LANE_PN_SWAP == _ENABLE)
    // Set Swap For Lane PN
    ScalerSetBit(P38_80_DPTX_PN_SWAP1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
    // Set No Swap For Lane PN
    ScalerSetBit(P38_80_DPTX_PN_SWAP1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

#if (_PANEL_DPTX_LANE_SWAP == _ENABLE)
    // Set TX1 DPHY to APHY mux from MAC0
    ScalerSetByte(P38_83_DPTX_LANE_SWAP3_2, 0x01);
    ScalerSetByte(P38_84_DPTX_LANE_SWAP1_0, 0x23);
#else
    // Set TX1 DPHY to APHY mux from MAC0
    ScalerSetByte(P38_83_DPTX_LANE_SWAP3_2, 0x32);
    ScalerSetByte(P38_84_DPTX_LANE_SWAP1_0, 0x10);
#endif // End of #if(_PANEL_DPTX_LANE_SWAP ==  _ENABLE)

    // Set Lane Non-Swap for MAC0
    ScalerSetByte(P9C_13_DPTX_SFIFO_LANE_SWAP1, 0x1B);

    // Set Voltage Swing and pre-emphasis level 0
    ScalerDisplayDPTx1SignalReset();

    // Initial bist mode
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT3 | _BIT2), _BIT2);

    // Disable scrambling
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT1, _BIT1);

    // Disable Digital PHY Enhancement
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT3, 0x00);

    // Enable Enhancement
    ScalerSetBit(P9C_A0_DP_MAC_CTRL, ~_BIT2, (GET_DISPLAY_DP_TX1_ENHANCE_FRAMING() << 2));

    // DPTX power on TX driver and Enable output
    switch(GET_DISPLAY_DP_TX1_LANE_NUM())
    {
        case _DP_ONE_LANE:

            // Set Mac 1 Lane
            ScalerSetBit(P9C_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT0);

            // Dig PHY Set
            ScalerSetBit(P9C_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            break;

        case _DP_TWO_LANE:

            // Set Mac 2 Lane
            ScalerSetBit(P9C_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT1);

            // Dig PHY Set
            ScalerSetBit(P9C_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            break;

        case _DP_FOUR_LANE:

            // Set Mac 4 Lane
            ScalerSetBit(P9C_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Dig PHY Set
            ScalerSetBit(P9C_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set TP2 Pattern Type
// Input Value  : None
// Output Value : _DISPLAY_DP_TX_TP_2 or _DISPLAY_DP_TX_TP_3
//--------------------------------------------------
EnumDisplayDPTxTrainPattern ScalerDisplayDPTx1SetTp2PatternType(void)
{
    // Main Link Switch to TPS2 Pattern
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT5, 0x00);

    return _DISPLAY_DP_TX_TP_2;
}
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)
