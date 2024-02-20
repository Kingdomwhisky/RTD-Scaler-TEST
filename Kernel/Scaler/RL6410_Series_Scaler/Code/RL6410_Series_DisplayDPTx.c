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
// ID Code      : RL6410_Series_DisplayDPTx.c No.0000
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

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tDISPLAY_DPTX_DRV_RBR_HBR_TABLE[48] =
{
    // Pre-emphasis->        0                    1                    2                    3
    // VoltageSwing
    /*    0    */      0x00, 0x04, 0x40,    0x03, 0x06, 0x42,    0x85, 0x0A, 0x36,    0x0F, 0x0F, 0xF5,
    /*    1    */      0x00, 0x06, 0x42,    0x21, 0x0E, 0x24,    0x1C, 0x0F, 0xFF,    0x1C, 0x0F, 0xFF,
    /*    2    */      0x00, 0x0E, 0x42,    0x1C, 0x0F, 0xFA,    0x1C, 0x0F, 0xFA,    0x1C, 0x0F, 0xFA,
    /*    3    */      0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,
};

BYTE code tDISPLAY_DPTX_DRV_HBR2_TABLE[48] =
{
    // Pre-emphasis->        0                    1                    2                    3
    // VoltageSwing
    /*    0    */      0x00, 0x03, 0x22,    0x0F, 0x0B, 0x61,    0x0F, 0x0C, 0x5A,    0x63, 0x0F, 0xBE,
    /*    1    */      0x00, 0x05, 0x33,    0x23, 0x0E, 0x67,    0xE0, 0x0F, 0x7F,    0xE0, 0x0F, 0x7F,
    /*    2    */      0x00, 0x07, 0x55,    0xE0, 0x0B, 0xFF,    0xE0, 0x0B, 0xFF,    0xE0, 0x0B, 0xFF,
    /*    3    */      0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,
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
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
void ScalerDisplayDPTx2SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
EnumDisplayDPTxTrainPattern ScalerDisplayDPTx2SetTp2PatternType(void);
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

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

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_1 == _ON)

        if(ScalerGetBit(P9C_70_HPD_CTRL, _BIT2) == _BIT2)
        {
            bHPCheck &= _SUCCESS;

            // Panel DPTx Power Sequence Check Point
            PCB_DPTX1_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_HPD_ON);
        }
        else
        {
#if(((_PANEL_DPTX_VENDOR_SPECIFIC_TYPE & _PANEL_DPTX_VENDOR_SPECIFIC_004F1H) == _PANEL_DPTX_VENDOR_SPECIFIC_004F1H) &&\
    (_DISPLAY_DP_TX_PORT_2 == _ON))

            pData[0] = 0x01;
            ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x04, 0xF1, 1, pData);
#endif

            bHPCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)

        if(ScalerGetBit(P9E_70_HPD_CTRL, _BIT2) == _BIT2)
        {
            bHPCheck &= _SUCCESS;

            // Panel DPTx Power Sequence Check Point
            PCB_DPTX2_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_HPD_ON);
        }
        else
        {
#if(((_PANEL_DPTX_VENDOR_SPECIFIC_TYPE & _PANEL_DPTX_VENDOR_SPECIFIC_004F1H) == _PANEL_DPTX_VENDOR_SPECIFIC_004F1H) &&\
    (_DISPLAY_DP_TX_PORT_1 == _ON))
            pData[0] = 0x01;
            ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x04, 0xF1, 1, pData);
#endif

            bHPCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)
#else
#if(_DISPLAY_DP_TX_PORT_2 == _ON)

        if(ScalerGetBit(P9E_70_HPD_CTRL, _BIT2) == _BIT2)
        {
            bHPCheck &= _SUCCESS;

            // Panel DPTx Power Sequence Check Point
            PCB_DPTX2_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_HPD_ON);
        }
        else
        {
#if(((_PANEL_DPTX_VENDOR_SPECIFIC_TYPE & _PANEL_DPTX_VENDOR_SPECIFIC_004F1H) == _PANEL_DPTX_VENDOR_SPECIFIC_004F1H) &&\
    (_DISPLAY_DP_TX_PORT_1 == _ON))
            ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x04, 0xF1, 1, 0x01);
#endif

            bHPCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

#if(_DISPLAY_DP_TX_PORT_1 == _ON)

        if(ScalerGetBit(P9C_70_HPD_CTRL, _BIT2) == _BIT2)
        {
            bHPCheck &= _SUCCESS;

            // Panel DPTx Power Sequence Check Point
            PCB_DPTX1_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_HPD_ON);
        }
        else
        {
#if(((_PANEL_DPTX_VENDOR_SPECIFIC_TYPE & _PANEL_DPTX_VENDOR_SPECIFIC_004F1H) == _PANEL_DPTX_VENDOR_SPECIFIC_004F1H) &&\
    (_DISPLAY_DP_TX_PORT_2 == _ON))
            ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x04, 0xF1, 1, 0x01);
#endif

            bHPCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

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

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_1 == _ON)

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
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)

        // Set Dptx2 Link Training
        ScalerDisplayDPTx2LinkTraining();

        if(GET_DISPLAY_DP_TX2_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PASS)
        {
            bLTCheck &= _SUCCESS;
        }
        else
        {
            bLTCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)
#else
#if(_DISPLAY_DP_TX_PORT_2 == _ON)

        // Set Dptx2 Link Training
        ScalerDisplayDPTx2LinkTraining();

        if(GET_DISPLAY_DP_TX2_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PASS)
        {
            bLTCheck &= _SUCCESS;
        }
        else
        {
            bLTCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

#if(_DISPLAY_DP_TX_PORT_1 == _ON)

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
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
        ucLTRetryNum += 1;

        ScalerTimerDelayXms(5);
    }
    while((ucLTRetryNum < 5) && (bLTCheck != _SUCCESS));

#if(_PANEL_DPTX_AUX_SET_TP_END_SEQUENCE == _TRAIN_PATTERN_END_AFTER_IDEL_PATTERN)
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    // Training Pattern End For Link Training
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x02, 1, pData);
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    // Training Pattern End For Link Training
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x02, 1, pData);
#endif
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
#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    SET_DISPLAY_DP_TX1_LINK_CONFIG(ScalerDisplayDPTx1LinkConfig());
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    SET_DISPLAY_DP_TX2_LINK_CONFIG(ScalerDisplayDPTx2LinkConfig());
#endif
#else
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    SET_DISPLAY_DP_TX2_LINK_CONFIG(ScalerDisplayDPTx2LinkConfig());
#endif

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    SET_DISPLAY_DP_TX1_LINK_CONFIG(ScalerDisplayDPTx1LinkConfig());
#endif
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
}

//--------------------------------------------------
// Description  : Setting for eDp Tx SSCG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxCheckSSC(void)
{
    bit bDpTxSscEn = _ENABLE;

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    bDpTxSscEn &= GET_DISPLAY_DP_TX1_DOWN_SPREAD();
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    bDpTxSscEn &= GET_DISPLAY_DP_TX2_DOWN_SPREAD();
#endif
#else
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    bDpTxSscEn &= GET_DISPLAY_DP_TX2_DOWN_SPREAD();
#endif

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    bDpTxSscEn &= GET_DISPLAY_DP_TX1_DOWN_SPREAD();
#endif
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

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
#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    ScalerDisplayDPTx1VideoStreamOutput(bOutput);
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    ScalerDisplayDPTx2VideoStreamOutput(bOutput);
#endif
#else
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    ScalerDisplayDPTx2VideoStreamOutput(bOutput);
#endif

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    ScalerDisplayDPTx1VideoStreamOutput(bOutput);
#endif
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
}

#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Link TSignal Force Output
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxLinkSignalForceOutput(void)
{
#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    ScalerDisplayDPTx1LinkForceOutput();
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    ScalerDisplayDPTx2LinkForceOutput();
#endif
#else
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    ScalerDisplayDPTx2LinkForceOutput();
#endif

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    ScalerDisplayDPTx1LinkForceOutput();
#endif
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

#if(_PANEL_DPTX_AUX_SET_TP_END_SEQUENCE == _TRAIN_PATTERN_END_AFTER_IDEL_PATTERN)
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    // Training Pattern End For Link Training
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x02, 1, pData);
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    // Training Pattern End For Link Training
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x02, 1, pData);
#endif
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

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    PCB_DPTX1_POWER_SEQUENCE(bLevel);
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    PCB_DPTX2_POWER_SEQUENCE(bLevel);
#endif
#else
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    PCB_DPTX2_POWER_SEQUENCE(bLevel);
#endif

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    PCB_DPTX1_POWER_SEQUENCE(bLevel);
#endif
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
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

    // Set Link Clk Source Selection of CKRD
    ScalerSetBit(P38_2A_VBY1_LCLK_SOURCE_CTRL, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

    // Set Link Clk Source
    ScalerSetBit(P38_2A_VBY1_LCLK_SOURCE_CTRL, ~_BIT0, _BIT0);

    // Set Dptx Digital Phy Initial
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

    // Set eDP mode
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    // Enable Vby1 Phy power
    ScalerDisplayDPTxAnalogPhyConrol(_ENABLE);

    // Initial Z0 for DPTx
    ScalerDisplayDPTxSetZ0();

    // Lane Skew Setting for 8 Lane
    ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((_DISPLAY_DP_TX_SKEW_LANE0 << 3) | _DISPLAY_DP_TX_SKEW_LANE1));
    ScalerSetByte(P38_86_PHY0_TXBIST_00_H1, ((_DISPLAY_DP_TX_SKEW_LANE2 << 5) | (_DISPLAY_DP_TX_SKEW_LANE3 << 2) | (_DISPLAY_DP_TX_SKEW_LANE0 >> 1)));
    ScalerSetByte(P38_87_PHY0_TXBIST_00_L2, ((_DISPLAY_DP_TX_SKEW_LANE0 << 7) | (_DISPLAY_DP_TX_SKEW_LANE1 << 4) | (_DISPLAY_DP_TX_SKEW_LANE2 << 1) | (_DISPLAY_DP_TX_SKEW_LANE3 >> 2)));
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT7 | _BIT6), (_DISPLAY_DP_TX_SKEW_LANE3 << 6));

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
        PDATA_WORD(0) = (WORD)((ScalerGetBit(P38_DC_DPTX_CMU12, 0x1F) << 4) | (ScalerGetByte(P38_DD_DPTX_CMU13) >> 4));
        PDATA_WORD(1) = (WORD)((ScalerGetBit(P38_DD_DPTX_CMU13, 0x0F) << 8) | ScalerGetByte(P38_DE_DPTX_CMU14));

        // Calculate SSC Frequency = 30~33k
        PDATA_WORD(3) = (((_EXT_XTAL / _DISPLAY_DP_TX_SSC_FREQ) + 2) & 0xFFFC);

        // Calculate SSC downspread
        PDATA_WORD(2) = ((((DWORD)PDATA_WORD(0) + 4) * 4096 + PDATA_WORD(1))) * 16 / 200 / PDATA_WORD(3) / 15 * _PANEL_DPTX_SPREAD_RANGE;

        // Set SSC Frequency = 30~33k
        ScalerSetByte(P38_E0_DPTX_CMU16, (BYTE)(PDATA_WORD(3) >> 8));
        ScalerSetByte(P38_E1_DPTX_CMU17, (BYTE)PDATA_WORD(3));

        // Set SSC downspread
        ScalerSetByte(P38_E2_DPTX_CMU18, (BYTE)(PDATA_WORD(2) >> 8));
        ScalerSetByte(P38_E3_DPTX_CMU19, (BYTE)PDATA_WORD(2));

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
        ScalerSetBit(P38_00_VIDEO_FORMAT_H, ~_BIT4, _BIT4);

        // Enable Digital Phy output
        ScalerSetByte(P38_8E_PHY0_TXBIST_02_H1, 0xFF);
    }

    else
    {
        // Disable Digital Phy output
        ScalerSetByte(P38_8E_PHY0_TXBIST_02_H1, 0x00);

        // Reset Dp Tx Digital Phy
        ScalerSetBit(P38_00_VIDEO_FORMAT_H, ~_BIT4, 0x00);
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
        // Enable Vby1 and DPTx Clock
        ScalerSetBit(P1_DC_DCLK_GATED_CTRL2, ~_BIT1, _BIT1);

        // Power Up Dp Tx PLL for LCLK
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT6, _BIT6);
    }

    else
    {
        // Power Down Dp Tx PLL for LCLK
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT6, 0x00);

        // Disable Vby1 and DPTx Clock
        ScalerSetBit(P1_DC_DCLK_GATED_CTRL2, ~_BIT1, 0x00);
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
        ScalerSetByte(P38_C1_DPTX_RCVDET_BIAS_PULLDN1, 0x00);

        // Power Up Dptx Digital Block: reg_en
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT7, _BIT7);

        // Disable Dptx Power Down Mode
        ScalerSetByte(P38_A3_DPTX_PHY_CTRL3, 0x00);
    }

    else
    {
        // Power Down Dptx Analog Block
        ScalerSetByte(P38_A1_DPTX_PHY_CTRL1, 0x00);

        // Enable Dptx Power Down Mode
        ScalerSetByte(P38_A3_DPTX_PHY_CTRL3, 0xFF);

        // Power Down Vby1 Digital Block
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT7, 0x00);

        // Enable Weakly Pull Down
        ScalerSetByte(P38_C1_DPTX_RCVDET_BIAS_PULLDN1, 0xFF);
    }
}

//--------------------------------------------------
// Description  : Settings for Dp Tx VBy1 Link Rate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxSetLinkRate(void)
{
#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    pData[0] = GET_DISPLAY_DP_TX1_LINK_RATE();
#else
    pData[0] = GET_DISPLAY_DP_TX2_LINK_RATE();
#endif
#else
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    pData[0] = GET_DISPLAY_DP_TX2_LINK_RATE();
#else
    pData[0] = GET_DISPLAY_DP_TX1_LINK_RATE();
#endif
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

}
//--------------------------------------------------
// Description  : Settings for Dp Tx Z0 Tunning
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxSetZ0(void)
{
    // Set Vby1 Z0 Value
    ScalerSetByte(P38_CC_DPTX_Z0_LANE7_6, 0x88);
    ScalerSetByte(P38_CD_DPTX_Z0_LANE5_4, 0x88);
    ScalerSetByte(P38_CE_DPTX_Z0_LANE3_2, 0x88);
    ScalerSetByte(P38_CF_DPTX_Z0_LANE1_0, 0x88);
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
        ScalerSetBit(P9D_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), (_PANEL_DPTX_AUX_SWING_LEVEL << 5));

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
        ScalerSetBit(P9D_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), (_PANEL_DPTX_AUX_SWING_LEVEL << 5));

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
    BYTE *pucTable = 0x00;

#if(_PANEL_DPTX_SET_LT_SIGNAL_LEVEL_MODE == _PANEL_DPTX_LT_MANUAL_MODE)
    ucVoltageSwing = _PANEL_DPTX_SWING_LEVEL;
    ucPreEmphasis = _PANEL_DPTX_PREEMPHASIS_LEVEL;
#endif

    ucIndex = (ucVoltageSwing * 4 + ucPreEmphasis) * 3;

    if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
    {
        pucTable = tDISPLAY_DPTX_DRV_HBR2_TABLE;
    }
    else
    {
        pucTable = tDISPLAY_DPTX_DRV_RBR_HBR_TABLE;
    }

    switch(enumLaneX)
    {
        case _DISPLAY_DP_TX_LANE_0: // VTX_lane0

            // De-emphasis [9:8]
            ScalerSetBit(P38_AD_DPTX_DEEMP_EN_LANE3_0H, ~(_BIT1 | _BIT0), (((pucTable[ucIndex + 1] & 0xF0) >> 4)));

            // De-emphasis [7:0]
            ScalerSetByte(P38_B1_DPTX_DEEMP_EN_LANE0L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(P38_B7_DPTX_DRV_DAC_DAT_LANE1_0, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));

            // Post1 [3:0]
            ScalerSetBit(P38_BF_DPTX_DRV_DAC_POST1_LANE1_0, ~0x0F, ((pucTable[ucIndex + 2] & 0xF0) >> 4));

            // Post0 [3:0]
            ScalerSetBit(P38_BB_DPTX_DRV_DAC_POST0_LANE1_0, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));

            break;

        case _DISPLAY_DP_TX_LANE_1: // VTX_lane1

            // De-emphasis [9:8]
            ScalerSetBit(P38_AD_DPTX_DEEMP_EN_LANE3_0H, ~(_BIT3 | _BIT2), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 2));

            // De-emphasis [7:0]
            ScalerSetByte(P38_B0_DPTX_DEEMP_EN_LANE1L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(P38_B7_DPTX_DRV_DAC_DAT_LANE1_0, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));

            // Post1 [3:0]
            ScalerSetBit(P38_BF_DPTX_DRV_DAC_POST1_LANE1_0, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));

            // Post0 [3:0]
            ScalerSetBit(P38_BB_DPTX_DRV_DAC_POST0_LANE1_0, ~0xF0, ((pucTable[ucIndex + 2] & 0x0F) << 4));

            break;

        case _DISPLAY_DP_TX_LANE_2: // VTX_lane2

            // De-emphasis [9:8]
            ScalerSetBit(P38_AD_DPTX_DEEMP_EN_LANE3_0H, ~(_BIT5 | _BIT4), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 4));

            // De-emphasis [7:0]
            ScalerSetByte(P38_AF_DPTX_DEEMP_EN_LANE2L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(P38_B6_DPTX_DRV_DAC_DAT_LANE3_2, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));

            // Post1 [3:0]
            ScalerSetBit(P38_BE_DPTX_DRV_DAC_POST1_LANE3_2, ~0x0F, ((pucTable[ucIndex + 2] & 0xF0) >> 4));

            // Post0 [3:0]
            ScalerSetBit(P38_BA_DPTX_DRV_DAC_POST0_LANE3_2, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));

            break;

        case _DISPLAY_DP_TX_LANE_3: // VTX_lane3

            // De-emphasis [9:8]
            ScalerSetBit(P38_AD_DPTX_DEEMP_EN_LANE3_0H, ~(_BIT7 | _BIT6), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 6));

            // De-emphasis [7:0]
            ScalerSetByte(P38_AE_DPTX_DEEMP_EN_LANE3L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(P38_B6_DPTX_DRV_DAC_DAT_LANE3_2, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));

            // Post1 [3:0]
            ScalerSetBit(P38_BE_DPTX_DRV_DAC_POST1_LANE3_2, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));

            // Post0 [3:0]
            ScalerSetBit(P38_BA_DPTX_DRV_DAC_POST0_LANE3_2, ~0xF0, ((pucTable[ucIndex + 2] & 0x0F) << 4));

            break;

        default:

            break;
    }
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

    // DPTX power on TX driver and Enable output
    switch(GET_DISPLAY_DP_TX1_LANE_NUM())
    {
        case _DP_ONE_LANE: // VTX Lane0

            // Set Mac 1 Lane
            ScalerSetBit(P9C_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT0);

            // Dig PHY Set
            ScalerSetBit(P9C_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            // Lane:0 power on
            ScalerSetBit(P38_A1_DPTX_PHY_CTRL1, ~_BIT0, _BIT0);

            break;

        case _DP_TWO_LANE: // VTX Lane0~1

            // Set Mac 2 Lane
            ScalerSetBit(P9C_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT1);

            // Dig PHY Set
            ScalerSetBit(P9C_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            // Lane:0-1 power on
            ScalerSetBit(P38_A1_DPTX_PHY_CTRL1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;

        case _DP_FOUR_LANE: // VTX Lane0~3

            // Set Mac 4 Lane
            ScalerSetBit(P9C_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Dig PHY Set
            ScalerSetBit(P9C_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            // Lane:0-3 power on
            ScalerSetBit(P38_A1_DPTX_PHY_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

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
    // Check TP3 Supported
    if((ScalerGlobalGetIDCode() >= _RL6410_VER_B_ID_CODE) && (GET_DISPLAY_DP_TX1_TP3_SUPPORT() == _TRUE))
    {
        // Ser Repeat Bist Pattern
        ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~_BIT7, _BIT7);

        // Set Packet Length
        ScalerSetByte(P38_8B_PHY0_TXBIST_01_L2, 0x20);

        // Main Link Switch to TPS3 Pattern
        ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT7, _BIT7);

        // Set 8 Bits Mode
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT3 | _BIT2), _BIT3);

        return _DISPLAY_DP_TX_TP_3;
    }
    else
    {
        // Set 10 Bits Mode
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT3 | _BIT2), _BIT2);

        // Main Link Switch to TPS2 Pattern
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT5, 0x00);

        return _DISPLAY_DP_TX_TP_2;
    }
}
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
//--------------------------------------------------

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis)
{
    BYTE ucIndex = 0x00;
    BYTE *pucTable = 0x00;

#if(_PANEL_DPTX_SET_LT_SIGNAL_LEVEL_MODE == _PANEL_DPTX_LT_MANUAL_MODE)
    ucVoltageSwing = _PANEL_DPTX_SWING_LEVEL;
    ucPreEmphasis = _PANEL_DPTX_PREEMPHASIS_LEVEL;
#endif

    ucIndex = (ucVoltageSwing * 4 + ucPreEmphasis) * 3;

    if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
    {
        pucTable = tDISPLAY_DPTX_DRV_HBR2_TABLE;
    }
    else
    {
        pucTable = tDISPLAY_DPTX_DRV_RBR_HBR_TABLE;
    }

    switch(enumLaneX)
    {
        case _DISPLAY_DP_TX_LANE_0: // VTX_lane4

            // De-emphasis [9:8]
            ScalerSetBit(P38_A8_DPTX_DEEMP_EN_LANE7_4H, ~(_BIT1 | _BIT0), (((pucTable[ucIndex + 1] & 0xF0) >> 4)));

            // De-emphasis [7:0]
            ScalerSetByte(P38_AC_DPTX_DEEMP_EN_LANE4L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(P38_B5_DPTX_DRV_DAC_DAT_LANE5_4, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));

            // Post1 [3:0]
            ScalerSetBit(P38_BD_DPTX_DRV_DAC_POST1_LANE5_4, ~0x0F, ((pucTable[ucIndex + 2] & 0xF0) >> 4));

            // Post0 [3:0]
            ScalerSetBit(P38_B9_DPTX_DRV_DAC_POST0_LANE5_4, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));

            break;

        case _DISPLAY_DP_TX_LANE_1: // VTX_lane5

            // De-emphasis [9:8]
            ScalerSetBit(P38_A8_DPTX_DEEMP_EN_LANE7_4H, ~(_BIT3 | _BIT2), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 2));

            // De-emphasis [7:0]
            ScalerSetByte(P38_AB_DPTX_DEEMP_EN_LANE5L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(P38_B5_DPTX_DRV_DAC_DAT_LANE5_4, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));

            // Post1 [3:0]
            ScalerSetBit(P38_BD_DPTX_DRV_DAC_POST1_LANE5_4, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));

            // Post0 [3:0]
            ScalerSetBit(P38_B9_DPTX_DRV_DAC_POST0_LANE5_4, ~0xF0, ((pucTable[ucIndex + 2] & 0x0F) << 4));

            break;

        case _DISPLAY_DP_TX_LANE_2: // VTX_lane6

            // De-emphasis [9:8]
            ScalerSetBit(P38_A8_DPTX_DEEMP_EN_LANE7_4H, ~(_BIT5 | _BIT4), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 4));

            // De-emphasis [7:0]
            ScalerSetByte(P38_AA_DPTX_DEEMP_EN_LANE6L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(P38_B4_DPTX_DRV_DAC_DAT_LANE7_6, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));

            // Post1 [3:0]
            ScalerSetBit(P38_BC_DPTX_DRV_DAC_POST1_LANE7_6, ~0x0F, ((pucTable[ucIndex + 2] & 0xF0) >> 4));

            // Post0 [3:0]
            ScalerSetBit(P38_B8_DPTX_DRV_DAC_POST0_LANE7_6, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));

            break;

        case _DISPLAY_DP_TX_LANE_3: // VTX_lane7

            // De-emphasis [9:8]
            ScalerSetBit(P38_A8_DPTX_DEEMP_EN_LANE7_4H, ~(_BIT7 | _BIT6), (((pucTable[ucIndex + 1] & 0xF0) >> 4) << 6));

            // De-emphasis [7:0]
            ScalerSetByte(P38_A9_DPTX_DEEMP_EN_LANE7L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(P38_B4_DPTX_DRV_DAC_DAT_LANE7_6, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));

            // Post1 [3:0]
            ScalerSetBit(P38_BC_DPTX_DRV_DAC_POST1_LANE7_6, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));

            // Post0 [3:0]
            ScalerSetBit(P38_B8_DPTX_DRV_DAC_POST0_LANE7_6, ~0xF0, ((pucTable[ucIndex + 2] & 0x0F) << 4));

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
EnumDisplayDPTxTrainPattern ScalerDisplayDPTx2SetTp2PatternType(void)
{
    // Check TP3 Supported
    if((ScalerGlobalGetIDCode() >= _RL6410_VER_B_ID_CODE) && (GET_DISPLAY_DP_TX2_TP3_SUPPORT() == _TRUE))
    {
        // Ser Repeat Bist Pattern
        ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~_BIT7, _BIT7);

        // Set Packet Length
        ScalerSetByte(P38_8B_PHY0_TXBIST_01_L2, 0x20);

        // Main Link Switch to TPS3 Pattern
        ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT7, _BIT7);

        // Switch APHY1 mux to DPHY0 port
        ScalerDisplayDPTx2SetTps3PatternMux(_ON);

        // Set 8 Bits Mode
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT3 | _BIT2), _BIT3);

        return _DISPLAY_DP_TX_TP_3;
    }
    else
    {
        // Set 10 Bits Mode
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT3 | _BIT2), _BIT2);

        // Main Link Switch to TPS2 Pattern
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT5, 0x00);

        return _DISPLAY_DP_TX_TP_2;
    }
}
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)
