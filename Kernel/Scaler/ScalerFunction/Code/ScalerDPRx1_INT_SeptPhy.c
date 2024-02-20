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
// ID Code      : ScalerDPRx1_INT_SeptPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_D1_DP_EXIST == _ON)
BYTE ScalerDpRx1GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
BYTE ScalerDpRx1GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
void ScalerDpRx1SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
void ScalerDpRx1SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
void ScalerDpRx1SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
BYTE ScalerDpRx1TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType);
BYTE ScalerDpRx1TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType);
void ScalerDpRx1TrainingPatternEnd_EXINT0(void);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
void ScalerDpRx1HDCPResetDpcdInfo_EXINT0(void);
void ScalerDpRx1HDCPResetKsvFifoToFirst_EXINT0(void);
void ScalerDpRx1HDCPSetKsvFifo_EXINT0(void);
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
BYTE ScalerDpRx1GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
BYTE ScalerDpRx1GetDpcdBitInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
#endif
#endif

BYTE ScalerDpRx1Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
BYTE ScalerDpRx1Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);

void ScalerDpRx1AdjustLaneFLDBand_EXINT0(BYTE ucDpRx1LaneNumber, WORD usVCOBandDiff);
BYTE ScalerDpRx1DFECheck_EXINT0(void);
void ScalerDpRx1IntHandler_EXINT0(void);
void ScalerDpRx1SetDFEInitial_EXINT0(void);
BYTE ScalerDpRx1CheckSourceOUI_EXINT0(EnumDpRxCheckSourceOUI enumDpRx1CheckSourceOUI);

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
void ScalerDpRx1MstAutoSwitch_EXINT0(void);
#if(_D0_DP_EXIST == _ON)
void ScalerDpRx1SetHotPlugEvent_EXINT0(EnumDpHotPlugAssertType enumHpdType);
#endif
#endif

#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D1_DP_EXIST == _ON)
//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetBit_EXINT(PBA_C4_DPCD_DATA_PORT, ucDpcdBit);
}
//--------------------------------------------------
// Description  : Get DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte_EXINT(PBA_C4_DPCD_DATA_PORT);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetBit_EXINT(PBA_C4_DPCD_DATA_PORT, ~(~ucNotDpcdBit), ucDpcdBit);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, ucDpcdValue);
}
//--------------------------------------------------
// Description  : DP Sink Status Setting in EXINT
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync) using 1
{
    if(enumInSync == _DP_SINK_IN_SYNC)
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 in Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) | _BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 in Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) | _BIT1));
        }
    }
    else
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 Out of Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) & ~_BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 Out of Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) & ~_BIT1));
        }
    }
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpRx1TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x0E, _BIT7) == _BIT7)
    {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _OFF)
        if(g_ucDpRx1LinkRate > _D1_DP_LINK_CLK_RATE)
#else
        if(g_ucDpRx1LinkRate > ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x22, 0x01))
#endif
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

            return _FALSE;
        }
    }
    else
    {
        if(g_ucDpRx1LinkRate > ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x00, 0x01))
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

            return _FALSE;
        }
    }

    ScalerDpRx1ErrorCounterDisable_EXINT0();

    g_ucDpRx1Tp1PermitSwingLevel0 = ScalerDpRx1CheckSourceOUI_EXINT0(_LT_TP1_PERMIT_SWING_LEVEL_0);

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & (_BIT1 | _BIT0)) >= _BIT0)
        {
            ScalerDpRx1Tp1SetPhy_EXINT0(_DP_NF_REF_XTAL);
        }
        else
        {
#if(_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON)
            if(g_ucDpRx1Tp1PermitSwingLevel0 == _TRUE)
            {
                ScalerDpRx1Tp1SetPhy_EXINT0(_DP_NF_REF_XTAL);
            }
            else
#endif
            {
                if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                {
#if(_DP_HBR_RBR_LT_FORCE_MARGINAL_LINK == _OFF)

                    ScalerDpRx1Tp1SetPhy_EXINT0(_DP_NF_REF_XTAL);
#endif
                }
            }
        }
    }

    ScalerDpRx1ErrorCounterEnable_EXINT0(enumDpLtType);

    if(ScalerDpRx1Tp1Check_EXINT0(enumDpLtType) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpRx1TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    ScalerDpRx1ErrorCounterDisable_EXINT0();

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        ScalerDpRx1Tp2SetPhy_EXINT0();
    }

    ScalerDpRx1ErrorCounterEnable_EXINT0(enumDpLtType);

    if(ScalerDpRx1Tp2Check_EXINT0(enumDpLtType) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Settings after Link Training Pass
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1TrainingPatternEnd_EXINT0(void) using 1
{
    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            // Clear Lane1/2/3 Link status
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x02, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _DP_TWO_LANE:
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            // Clear Lane2/3 Link status
            ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _DP_FOUR_LANE:
        default:
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            break;
    }

    // De-Skew Circuit Reset
    ScalerSetBit_EXINT(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // Enable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
    {
        // Disable Scrambling
        ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // Enable Scrambling
        ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
    }
}

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Reset Dp Rx HDCP info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPResetDpcdInfo_EXINT0(void) using 1
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Clear RxStatus REAUTH_REQ and Link Intergrity Failure for HDCP 2.2
    ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x94, 0x93) & 0xE0));
#endif

    // Check if nead to clear HDCP dpcd info
    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x80, 0x2A) != 0x00) || (ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x80, 0x2B) != 0x00))
    {
        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, 0x29, 0x00);
        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, 0x2A, 0x00);
        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, 0x2B, 0x00);

        for(pData_EXINT[0] = 0; pData_EXINT[0] < 20; pData_EXINT[0]++)
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, (0x14 + pData_EXINT[0]), 0x00);
        }

        for(pData_EXINT[0] = 0; pData_EXINT[0] < 15; pData_EXINT[0]++)
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, (0x2C + pData_EXINT[0]), 0x00);
        }

        // Delay Time us [200,x] Waiting for R0 Calculate Finish
        DELAY_XUS_EXINT(200);

        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, 0x29, 0x02);
    }
}
//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPResetKsvFifoToFirst_EXINT0(void) using 1
{
    for(g_usDpRx1HdcpKsvFifoOffset = 0; g_usDpRx1HdcpKsvFifoOffset < 15; g_usDpRx1HdcpKsvFifoOffset++)
    {
        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, (0x2C + g_usDpRx1HdcpKsvFifoOffset), g_pucDpTxHdcpKsvFifo[g_usDpRx1HdcpKsvFifoOffset]);
    }
}
//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPSetKsvFifo_EXINT0(void) using 1
{
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 15; pData_EXINT[0]++)
    {
        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, (0x2C + pData_EXINT[0]), g_pucDpTxHdcpKsvFifo[g_usDpRx1HdcpKsvFifoOffset + pData_EXINT[0]]);
    }

    g_usDpRx1HdcpKsvFifoOffset += pData_EXINT[0];
}

#endif // End of #if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL) using 3
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte_EXINT(PBA_C4_DPCD_DATA_PORT);
}
#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdBitInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit) using 3
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetBit_EXINT(PBA_C4_DPCD_DATA_PORT, ucDpcdBit);
}
#endif
#endif

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpRx1Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    BYTE pucDpPhyLinkTrainingLevel[4];
    BYTE pucDpPhyLinkTrainingRequest[4];
    BYTE ucTP1NormalLTSwingLevel = 2;
    BYTE ucTP1RBRHBRFakeLTSwingLevel = 1;
    BYTE ucTP1HBR2FakeLTSwingLevel = 3;
    BYTE ucFakeLTLaneCount = g_ucDpRx1LaneCount;

    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

#if(_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON)
    if(g_ucDpRx1Tp1PermitSwingLevel0 == _TRUE)
    {
        ucTP1NormalLTSwingLevel = 0;
        ucTP1RBRHBRFakeLTSwingLevel = 0;
        ucTP1HBR2FakeLTSwingLevel = 0;
    }
#endif

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        if((GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) &&
           (GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL) &&
           (g_bDpRx1Tp1Initial == _FALSE))
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x04, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x05, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x06, 0x00);

            g_ucDpRx1LinkRequest01 = 0x00;
            g_ucDpRx1LinkRequest23 = 0x00;

#if(_DP_HBR_RBR_LT_FORCE_MARGINAL_LINK == _ON)
            SET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
            SET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR();
            SET_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR();
            SET_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR();
#endif
            g_bDpRx1Tp1Initial = _TRUE;
        }

        pucDpPhyLinkTrainingLevel[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pucDpPhyLinkTrainingLevel[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pucDpPhyLinkTrainingLevel[2] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pucDpPhyLinkTrainingLevel[3] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

        for(pData_EXINT[0] = 0; pData_EXINT[0] <= 1; pData_EXINT[0]++)
        {
            if((pucDpPhyLinkTrainingLevel[2 * pData_EXINT[0]] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = 0x02;
#else
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = (pucDpPhyLinkTrainingLevel[2 * pData_EXINT[0]] & (_BIT1 | _BIT0)) + 0x01;
#endif
            }
            else
            {
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = 0x03;
            }

            if((pucDpPhyLinkTrainingLevel[(2 * pData_EXINT[0]) + 1] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = 0x20;
#else
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = ((pucDpPhyLinkTrainingLevel[(2 * pData_EXINT[0]) + 1] << 4) & (_BIT5 | _BIT4)) + 0x10;
#endif
            }
            else
            {
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = 0x30;
            }
        }

        g_ucDpRx1LinkStatus01 = 0;
        g_ucDpRx1LinkStatus23 = 0;

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_FOUR_LANE:

                // Read Back Lane3 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE3 << 6));

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane3 Check
                if(((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x10;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if((GET_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) >= ((g_ucDpRx1LinkRequest23 >> 4) & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x10;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                                CLR_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x10;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                }

                // Read Back Lane2 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE2 << 6));

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane2 Check
                if(((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if((GET_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) >= (g_ucDpRx1LinkRequest23 & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                                CLR_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                }

                // Read Back Lane1 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane1 Check
                if(((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if((GET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ((g_ucDpRx1LinkRequest01 >> 4) & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                                CLR_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                }

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if((GET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= (g_ucDpRx1LinkRequest01 & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                                CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                break;

            case _DP_TWO_LANE:

                // Read Back Lane1 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane1 Check
                if(((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if((GET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ((g_ucDpRx1LinkRequest01 >> 4) & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                                CLR_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                }

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if((GET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= (g_ucDpRx1LinkRequest01 & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                                CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                break;

            case _DP_ONE_LANE:
            default:

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if((GET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= (g_ucDpRx1LinkRequest01 & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                                CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                break;
        }

        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, g_ucDpRx1LinkStatus01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, g_ucDpRx1LinkStatus23);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_ONE_LANE:

                if((g_ucDpRx1LinkStatus01 & _BIT0) == _BIT0)
                {
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpRx1LinkStatus01 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))
                {
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpRx1LinkStatus01 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0)) && (((g_ucDpRx1LinkStatus23 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))))
                {
                    return _TRUE;
                }

                break;
        }
    }
    else
    {
        if((GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) && (GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL))
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x04, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x05, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x06, 0x00);
        }

        pucDpPhyLinkTrainingLevel[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pucDpPhyLinkTrainingLevel[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pucDpPhyLinkTrainingLevel[2] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pucDpPhyLinkTrainingLevel[3] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

        for(pData_EXINT[0] = 0; pData_EXINT[0] <= 1; pData_EXINT[0]++)
        {
            if((pucDpPhyLinkTrainingLevel[2 * pData_EXINT[0]] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = 0x02;
#else
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = (pucDpPhyLinkTrainingLevel[2 * pData_EXINT[0]] & (_BIT1 | _BIT0)) + 0x01;
#endif
            }
            else
            {
                pucDpPhyLinkTrainingRequest[2 * pData_EXINT[0]] = 0x03;
            }

            if((pucDpPhyLinkTrainingLevel[(2 * pData_EXINT[0]) + 1] & (_BIT1 | _BIT0)) < 2)
            {
#if(_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON)
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = 0x20;
#else
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = ((pucDpPhyLinkTrainingLevel[(2 * pData_EXINT[0]) + 1] << 4) & (_BIT5 | _BIT4)) + 0x10;
#endif
            }
            else
            {
                pucDpPhyLinkTrainingRequest[(2 * pData_EXINT[0]) + 1] = 0x30;
            }
        }

        g_ucDpRx1LinkRequest01 = (pucDpPhyLinkTrainingLevel[0] & 0x03) | ((pucDpPhyLinkTrainingLevel[1] << 4) & 0x30);
        g_ucDpRx1LinkRequest23 = (pucDpPhyLinkTrainingLevel[2] & 0x03) | ((pucDpPhyLinkTrainingLevel[3] << 4) & 0x30);

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
        if(g_ucDpRx1FakeLTLaneCount <= g_ucDpRx1LaneCount)
        {
            ucFakeLTLaneCount = g_ucDpRx1FakeLTLaneCount;
        }
        else
        {
            ucFakeLTLaneCount = g_ucDpRx1LaneCount;
        }
#endif
        switch(ucFakeLTLaneCount)
        {
            case _DP_ONE_LANE:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }
                }
                else
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0)))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x01);

                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                    }
                }
                else
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if((((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0))))) &&
                   (((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);

                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                    }
                }
                else
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

                if((((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0)))) &&
                   (((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT5 | _BIT4)) >> 4))) &&
                   (((pucDpPhyLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) == ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x07, (_BIT1 | _BIT0)))) &&
                   (((pucDpPhyLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x07, (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x11);

                    return _TRUE;
                }

                break;
        }
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpRx1Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    BYTE ucEQCRCStatus = 0;
    BYTE ucEQCRCStatus1 = 0;
    BYTE ucEQCRCStatus2 = 0;
    BYTE ucFakeLTLaneCount = g_ucDpRx1LaneCount;

    pData_EXINT[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
    pData_EXINT[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
    pData_EXINT[2] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
    pData_EXINT[3] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        g_ucDpRx1LinkRequest01 = ((pData_EXINT[0] & 0x03) |
                                  ((pData_EXINT[0] >> 1) & 0x0C) |
                                  ((pData_EXINT[1] << 4) & 0x30) |
                                  ((pData_EXINT[1] << 3) & 0xC0));

        g_ucDpRx1LinkRequest23 = ((pData_EXINT[2] & 0x03) |
                                  ((pData_EXINT[2] >> 1) & 0x0C) |
                                  ((pData_EXINT[3] << 4) & 0x30) |
                                  ((pData_EXINT[3] << 3) & 0xC0));

        // Enable EQ-CRC and Clear EQ-CRC Status(- K28.5)
        ScalerSetBit_EXINT(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [25,x]
        DELAY_25US_EXINT();

        ucEQCRCStatus1 = ScalerGetByte_EXINT(PB0_12_EQ_CRC_1);

        if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
        {
            for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 30; g_ucDpRx1Temp++)
            {
                ucEQCRCStatus1 = ucEQCRCStatus1 & ScalerGetByte_EXINT(PB0_12_EQ_CRC_1);
            }
        }
        else
        {
            for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 5; g_ucDpRx1Temp++)
            {
                ucEQCRCStatus1 = ucEQCRCStatus1 & ScalerGetByte_EXINT(PB0_12_EQ_CRC_1);
            }
        }

        // Disable EQ-CRC
        ScalerSetBit_EXINT(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Enable EQ-CRC and Clear EQ-CRC Status(+ K28.5)
        ScalerSetBit_EXINT(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [25,x]
        DELAY_25US_EXINT();

        ucEQCRCStatus2 = ScalerGetByte_EXINT(PB0_12_EQ_CRC_1);

        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 5; g_ucDpRx1Temp++)
        {
            ucEQCRCStatus2 = ucEQCRCStatus2 & ScalerGetByte_EXINT(PB0_12_EQ_CRC_1);
        }

        // Disable EQ-CRC
        ScalerSetBit_EXINT(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        ucEQCRCStatus = (ucEQCRCStatus1 | ucEQCRCStatus2);

        g_ucDpRx1EQCRC = 0x00;

        if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x01);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x02) >> 1);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x04) >> 2);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x08) >> 3);
        }

        if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x01) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x02);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x04) >> 1);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x08) >> 2);
        }

        if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x01) << 2);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x02) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x04);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x08) >> 1);
        }

        if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x01) << 3);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x02) << 2);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x04) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x08);
        }

        ucEQCRCStatus = g_ucDpRx1EQCRC;

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_FOUR_LANE:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if((ucEQCRCStatus & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != (_BIT3 | _BIT2 | _BIT1 | _BIT0))
                    {
                        ucEQCRCStatus &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
                    }
                }

                // Lane2 EQ-CRC Check
                if((ucEQCRCStatus & _BIT2) == _BIT2)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[2] & _BIT2) == _BIT2) || ((pData_EXINT[2] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x07;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x07;
                    }
                }
                else
                {
                    if(((g_ucDpRx1LinkRequest23 & 0x03) + ((g_ucDpRx1LinkRequest23 >> 2) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx1LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[2] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx1LinkRequest23 = g_ucDpRx1LinkRequest23 + 0x01;
                        }
                        else if((pData_EXINT[2] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx1LinkRequest23 = g_ucDpRx1LinkRequest23 + 0x04;
                        }
                    }
                }

                // Lane3 EQ-CRC Check
                if((ucEQCRCStatus & _BIT3) == _BIT3)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[3] & _BIT2) == _BIT2) || ((pData_EXINT[3] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x70;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x70;
                    }
                }
                else
                {
                    if((((g_ucDpRx1LinkRequest23 >> 4) & 0x03) + ((g_ucDpRx1LinkRequest23 >> 6) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx1LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[3] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx1LinkRequest23 = g_ucDpRx1LinkRequest23 + 0x10;
                        }
                        else if((pData_EXINT[3] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx1LinkRequest23 = g_ucDpRx1LinkRequest23 + 0x40;
                        }
                    }
                }

                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x70;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x70;
                    }
                }
                else
                {
                    if((((g_ucDpRx1LinkRequest01 >> 4) & 0x03) + ((g_ucDpRx1LinkRequest01 >> 6) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx1LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[1] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x10;
                        }
                        else if((pData_EXINT[1] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x40;
                        }
                    }
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                    }
                }
                else
                {
                    if(((g_ucDpRx1LinkRequest01 & 0x03) + ((g_ucDpRx1LinkRequest01 >> 2) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx1LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[0] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x01;
                        }
                        else if((pData_EXINT[0] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x04;
                        }
                    }
                }

                break;

            case _DP_TWO_LANE:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if((ucEQCRCStatus & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0))
                    {
                        ucEQCRCStatus &= ~(_BIT1 | _BIT0);
                    }
                }

                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x70;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x70;
                    }
                }
                else
                {
                    if((((g_ucDpRx1LinkRequest01 >> 4) & 0x03) + ((g_ucDpRx1LinkRequest01 >> 6) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx1LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[1] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x10;
                        }
                        else if((pData_EXINT[1] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x40;
                        }
                    }
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                    }
                }
                else
                {
                    if(((g_ucDpRx1LinkRequest01 & 0x03) + ((g_ucDpRx1LinkRequest01 >> 2) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx1LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[0] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x01;
                        }
                        else if((pData_EXINT[0] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x04;
                        }
                    }
                }

                break;

            case _DP_ONE_LANE:
            default:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if((ucEQCRCStatus & _BIT0) != _BIT0)
                    {
                        ucEQCRCStatus &= ~_BIT0;
                    }
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                    }
                }
                else
                {
                    if(((g_ucDpRx1LinkRequest01 & 0x03) + ((g_ucDpRx1LinkRequest01 >> 2) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx1LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[0] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x01;
                        }
                        else if((pData_EXINT[0] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x04;
                        }
                    }
                }

                break;
        }

        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, g_ucDpRx1LinkStatus01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, g_ucDpRx1LinkStatus23);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_ONE_LANE:

                if((g_ucDpRx1LinkStatus01 & 0x07) == 0x07)
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpRx1LinkStatus01 & 0x77) == 0x77)
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpRx1LinkStatus01 & 0x77) == 0x77) && (((g_ucDpRx1LinkStatus23 & 0x77) == 0x77)))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;
        }
    }
    else
    {
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

        g_ucDpRx1LinkRequest01 = (pData_EXINT[0] & 0x03) | ((pData_EXINT[1] << 4) & 0x30);
        g_ucDpRx1LinkRequest23 = (pData_EXINT[2] & 0x03) | ((pData_EXINT[3] << 4) & 0x30);

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
        if(g_ucDpRx1FakeLTLaneCount <= g_ucDpRx1LaneCount)
        {
            ucFakeLTLaneCount = g_ucDpRx1FakeLTLaneCount;
        }
        else
        {
            ucFakeLTLaneCount = g_ucDpRx1LaneCount;
        }
#endif
        switch(ucFakeLTLaneCount)
        {
            case _DP_ONE_LANE:

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if(((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x07);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if((((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[1] & _BIT5) == _BIT5) || ((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x11);

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }

                    if(((pData_EXINT[2] & _BIT2) != _BIT2) && ((pData_EXINT[2] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[3] & _BIT2) != _BIT2) && ((pData_EXINT[3] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }

                    if(((pData_EXINT[2] & _BIT2) != _BIT2) && ((pData_EXINT[2] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[3] & _BIT2) != _BIT2) && ((pData_EXINT[3] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

                if((((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[1] & _BIT5) == _BIT5) || ((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT5 | _BIT4)) >> 4))) &&
                   (((pData_EXINT[2] & _BIT5) == _BIT5) || ((pData_EXINT[2] & _BIT2) == _BIT2) || ((pData_EXINT[2] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x07) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[3] & _BIT5) == _BIT5) || ((pData_EXINT[3] & _BIT2) == _BIT2) || ((pData_EXINT[3] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x07) & (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x77);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP FLD Band Finetune
// Input Value  : LaneNumber
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AdjustLaneFLDBand_EXINT0(BYTE ucDpRx1LaneNumber, WORD usVCOBandDiff) using 1
{
    BYTE ucBestVCOBand = 0;
    BYTE ucAutoVCOBand = 0;

    switch(ucDpRx1LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ucAutoVCOBand = (ScalerGetByte_EXINT(P7A_36_ANA_CDR_11) & 0x7F);

            break;

        case _DP_SCALER_LANE1:

            ucAutoVCOBand = (ScalerGetByte_EXINT(P7A_37_ANA_CDR_12) & 0x7F);

            break;

        case _DP_SCALER_LANE2:

            ucAutoVCOBand = (ScalerGetByte_EXINT(P7A_38_ANA_CDR_13) & 0x7F);

            break;

        case _DP_SCALER_LANE3:

            ucAutoVCOBand = (ScalerGetByte_EXINT(P7A_39_ANA_CDR_14) & 0x7F);

            break;
    }

    // [1:0] freqdet_lane_sel
    ScalerSetBit_EXINT(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), ucDpRx1LaneNumber);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 30; g_ucDpRx1Temp++)
    {
        DELAY_5US_EXINT();

        if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            break;
        }
    }

    if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        g_pusDpRx1ClockCount1[ucDpRx1LaneNumber] = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));

        if(g_pusDpRx1ClockCount1[ucDpRx1LaneNumber] < g_pusDpRx1ClockCount[ucDpRx1LaneNumber])
        {
            ucBestVCOBand = ucAutoVCOBand + (((g_pusDpRx1ClockCount[ucDpRx1LaneNumber] - g_pusDpRx1ClockCount1[ucDpRx1LaneNumber]) / usVCOBandDiff) + 1);
        }
        else
        {
            ucBestVCOBand = ucAutoVCOBand - ((g_pusDpRx1ClockCount1[ucDpRx1LaneNumber] - g_pusDpRx1ClockCount[ucDpRx1LaneNumber]) / usVCOBandDiff);
        }
    }
    else
    {
        ucBestVCOBand = ucAutoVCOBand;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // Manually Reload FLD Band
    switch(ucDpRx1LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ScalerSetBit_EXINT(P7A_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE1:

            ScalerSetBit_EXINT(P7A_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE2:

            ScalerSetBit_EXINT(P7A_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE3:

            ScalerSetBit_EXINT(P7A_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;
    }
}
//--------------------------------------------------
// Description : check DFE Coef in INT0
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpRx1DFECheck_EXINT0(void) using 1
{
    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(g_ucDpRx1LaneCount)
    {
        case _DP_FOUR_LANE:

            // Read Lane2 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane3 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1IntHandler_EXINT0(void) using 1
{
    // Aux Firmware Control -> Reply Defer
    SET_DP_RX1_AUX_MANUAL_MODE_EXINT();

    g_pucDpRx1Backup[0] = ScalerGetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H);
    g_pucDpRx1Backup[1] = ScalerGetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M);
    g_pucDpRx1Backup[2] = ScalerGetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L);

    // DP Global IRQ Flag
    if(ScalerGetBit_EXINT(PBA_DC_AUX_IRQ_STATUS, _BIT7) == _BIT7)
    {
        // Fifo overflow/ underflow IRQ & flag
        if((ScalerGetBit_EXINT(PB9_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) != 0x00) && (ScalerGetBit_EXINT(PB8_21_PG_CTRL_1, (_BIT4 | _BIT2)) != 0x00))
        {
            // Disable fifo overflwo/ underflwo IRQ
            ScalerSetBit_EXINT(PB9_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

            // Set free run & force to BG
            ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT5 | _BIT3), _BIT5);

#if(_AUDIO_SUPPORT == _ON)
            // Disable Audio Channel
            ScalerAudioDpAudioEnable_EXINT0(_DISABLE, _D1_INPUT_PORT);
#endif

            // Disable VB-ID[3] Change IRQ
            ScalerSetBit_EXINT(PB9_3B_DP_IRQ_CTRL1, ~_BIT4, 0x00);

            // Set DP Receive Port0 Out of Sync
            ScalerDpRx1SinkStatusSet_EXINT0(_DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);

            // The Judge Handler take much time, It lead to MacBook 720P @50 <---> @60 Timing changing Issue
            if(((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x11) & _BIT0) == 0x00) &&
               (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0) &&
               (ScalerDpRx1DFECheck_EXINT0() == _FALSE))
            {
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, 0x00);
            }

#if((_DP_TX_SUPPORT == _ON) || (_EMBEDDED_DP_TX_SUPPORT == _ON))
            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
            {
                // Set DPTx Force Output Idle Pattern
                ScalerDpTxForceIdlePattern_EXINT0();
            }
#endif
        }

        // LLCTS 7.2.1.3 Sink Status
        if((ScalerGetBit_EXINT(PB9_3B_DP_IRQ_CTRL1, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(PB9_36_DP_GLB_STATUS, _BIT6) == _BIT6))
        {
            // Disable VB-ID[3] Change IRQ
            ScalerSetBit_EXINT(PB9_3B_DP_IRQ_CTRL1, ~_BIT4, 0x00);

            // Clear VB-ID[3] Change Flag
            ScalerSetBit_EXINT(PB9_36_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

            if(ScalerGetBit_EXINT(PB9_01_DP_VBID, _BIT3) == _BIT3)
            {
                // Set DP Receive Port0 Out of Sync
                ScalerDpRx1SinkStatusSet_EXINT0(_DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);
            }
        }

        if(ScalerGetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, _BIT0) == _BIT0) // Write 00600h into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, ~_BIT0, _BIT0);

            if((ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
               (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
            {
                // DP Power Down
                SET_DP_RX1_BACKUP_PD_LINK_STATUS_FLG();

                g_pucDpRx1LinkStatusBackup_INT[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x02);
                g_pucDpRx1LinkStatusBackup_INT[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x03);
                g_pucDpRx1LinkStatusBackup_INT[2] = ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x04, _BIT0);

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
                ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT0), _BIT7);

#if(_DP_MST_SUPPORT == _ON)
                CLR_DP_RX1_SOURCE_WRITE_POWER_UP();
#endif
            }
            else if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
            {
                // DP Power Normal
                if(GET_DP_RX1_BACKUP_PD_LINK_STATUS_FLG() == _TRUE)
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, g_pucDpRx1LinkStatusBackup_INT[0]);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, g_pucDpRx1LinkStatusBackup_INT[1]);
                    ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT0), (_BIT7 | g_pucDpRx1LinkStatusBackup_INT[2]));
                }

                CLR_DP_RX1_BACKUP_PD_LINK_STATUS_FLG();
                g_pucDpRx1LinkStatusBackup_INT[0] = 0x00;
                g_pucDpRx1LinkStatusBackup_INT[1] = 0x00;
                g_pucDpRx1LinkStatusBackup_INT[2] = 0x00;

#if(_DP_MST_SUPPORT == _ON)
                SET_DP_RX1_SOURCE_WRITE_POWER_UP(_DP_SOURCE_WRITE_POWER_UP_TRIGGERED);
#endif
            }
        }

        if(ScalerGetBit_EXINT(PBA_DA_AUX_FIFO_RST, (_BIT2 | _BIT1)) == (_BIT2 | _BIT1)) // Write 68xxxh into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_DA_AUX_FIFO_RST, ~_BIT1, _BIT1);

            // Clear Integrity Failure Flag
            ScalerSetBit_EXINT(PB0_1B_HDCP_INTGT_VRF, ~_BIT1, _BIT1);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
            if(ScalerGetBit_EXINT(PBA_FA_DUMMY_0, _BIT3) == _BIT3)
            {
                // Detect if V'(0x68027) is read by Source
                if((ScalerGetByte_EXINT(PBA_D3_AUX_RX_ADDR_M) == 0x80) && (ScalerGetByte_EXINT(PBA_D4_AUX_RX_ADDR_L) == 0x28))
                {
                    ScalerDpRx1HDCPResetKsvFifoToFirst_EXINT0();
                }
            }
#endif
            if(GET_DP_RX1_FAKE_LINK_TRAINING() == _TRUE)
            {
                // DP Mac Clock Select to Xtal Clock
                ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);
            }
        }

        // Detect if Aksv(0x6800B) is Written by Source
        if(ScalerGetBit_EXINT(PBA_A5_AUX_RESERVE5, (_BIT6 | _BIT2)) == (_BIT6 | _BIT2))
        {
            ScalerSetBit_EXINT(PBA_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Switch HDCP to 1.4 Module from 2.2 Module as receiving AKsv
            if(GET_DP_RX1_HDCP_MODE_EXINT() == _HDCP_22)
            {
                // Select to HDCP 1.4 Module
                SET_DP_RX1_HDCP_MODE_EXINT(_HDCP_14);

                // Calculate R0' by manual toggle HDCP 1.4 Module
                ScalerSetBit_EXINT(PB0_63_HDCP_OTHER, ~_BIT7, _BIT7);
                ScalerSetBit_EXINT(PB0_63_HDCP_OTHER, ~_BIT7, 0x00);
            }

#if(_WD_TIMER_INT_SUPPORT == _ON)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE);
#endif
#endif

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
            ScalerDpRx1HDCPResetDpcdInfo_EXINT0();

            SET_DP_RX1_HDCP_AUTH_AKSV_WRITTEN();
#endif
        }

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        // Read 6803A into INT0
        if(ScalerGetBit_EXINT(PBA_FA_DUMMY_0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            ScalerSetBit_EXINT(PBA_FA_DUMMY_0, ~_BIT0, _BIT0);

            ScalerDpRx1HDCPSetKsvFifo_EXINT0();
        }
#endif
        if(ScalerGetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, _BIT2) == _BIT2) // Write 00270h into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, ~_BIT2, _BIT2);

            if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT0) == _BIT0)
            {
                SET_DP_RX1_CRC_CALCULATE();
            }

            // Clear TEST_CRC_COUNT
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x46, 0x20);
        }

#if(_DP_MST_SUPPORT == _ON)

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
        ScalerDpRx1MstAutoSwitch_EXINT0();
#endif

        if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
        {
            ScalerDpRxMstIntHandle_EXINT0();
        }
#endif

#if(_AUDIO_SUPPORT == _ON)
        // Detect if Auido Sampling is Changed
        if(ScalerGetBit_EXINT(PB9_50_AUD_FREQUENY_DET_0, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
        {
            // Clear Auido Sampling Change Flag
            ScalerSetBit_EXINT(PB9_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);

            // Disable Boundary Tracking Method
            ScalerSetBit_EXINT(PB9_81_AUD_BDRY_0, ~_BIT7, 0x00);

            // Disable Trend Tracking Method
            ScalerSetBit_EXINT(PB9_92_AUD_TRND_0, ~_BIT7, 0x00);

            // Reload D code
            ScalerSetBit_EXINT(PB9_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);
        }
#endif
    }

    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, g_pucDpRx1Backup[0]);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, g_pucDpRx1Backup[1]);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, g_pucDpRx1Backup[2]);
}
//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDFEInitial_EXINT0(void) using 1
{
    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [3] Disable Running Length Detection
    // [2] bypass Blank out Case-3 Symbol
    ScalerSetBit_EXINT(P7A_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7A_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7A_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7A_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

    // [7:6] adapt_mode[1:0] = 2'b11 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 3)
    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetByte_EXINT(P7A_E0_MODE_TIMER, 0xF2);

    // Set DFE Delay Time
    ScalerSetByte_EXINT(P7A_E1_TIMER, 0x01);

    // Tap0,Tap1 Loop Gain 1/512
    ScalerSetBit_EXINT(P7A_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap2,Tap3 Loop Gain 1/512
    ScalerSetBit_EXINT(P7A_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4,Servo Loop Gain 1/512
    ScalerSetBit_EXINT(P7A_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // LE Gain1 Loop Gain 1/256, LE Gain2 Loop Gain 0, LE Pre-Courser Gain 0
    ScalerSetBit_EXINT(P7A_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit_EXINT(P7A_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap0 Max is 21
    ScalerSetByte_EXINT(P7A_E6_LIMIT_1, 0x35);

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // Tap1 Min is 49
        ScalerSetBit_EXINT(P7A_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));
    }
    else
    {
        // Tap1 Min is 51
        ScalerSetBit_EXINT(P7A_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
    }

    // Tap2 Max is 6, Min is -6
    ScalerSetBit_EXINT(P7A_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(P7A_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P7A_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 0, Min is -3
    ScalerSetBit_EXINT(P7A_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 0, Min is -3
    ScalerSetBit_EXINT(P7A_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_EB_LIMIT_6, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P7A_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Tap0 Threshold = 10
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // Set Vth Max = 6, Min = 4
        ScalerSetByte_EXINT(P7A_F9_LIMIT_10, 0x64);
    }
    else
    {
        // Set Vth Max = 6, Min = 2
        ScalerSetByte_EXINT(P7A_F9_LIMIT_10, 0x62);
    }

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetByte_EXINT(P7A_EC_LOOP_DIV_1, 0xA3);

    if(g_ucDpRx1TrainingPatternSet == _DP_TRAINING_PATTERN_3)
    {
        // Tap Divider = 34 for TP3
        ScalerSetByte_EXINT(P7A_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for TP2
        ScalerSetByte_EXINT(P7A_ED_LOOP_DIV_2, 0xCA);
    }

    // [1] tap1_trans = 1'b0 --> Tap1 is Effective every bit
    // [0] tap0_trans = 1'b0 --> Tap0 is Effective every bit
    ScalerSetBit_EXINT(P7A_E3_GAIN_2, ~(_BIT1 | _BIT0), 0x00);

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // [1:0] trans_rlength = 2'b01 --> Tap0 Run Length = 3
        ScalerSetBit_EXINT(P7A_E4_GAIN_3, ~(_BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // [1:0] trans_rlength = 2'b00 --> Tap0 Run Length = 2
        ScalerSetBit_EXINT(P7A_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);
    }

    // [5] servo_notrans = 1'b0 --> Servo is Effective every bit
    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective every bit
    ScalerSetBit_EXINT(P7A_F8_GRAY_DEC_2, ~(_BIT5 | _BIT4), 0x00);


    /////////////////////////
    // DFE Code Initialize //
    /////////////////////////

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // LE Max = 18, Initial = 16, Servo Initial = 16
        ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0x20);
        ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0x20);
        ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0x20);
        ScalerSetByte_EXINT(P7A_D2_L3_LIMIT_INIT, 0x20);
        ScalerSetByte_EXINT(P7A_A3_L0_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_B3_L1_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_C3_L2_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_D3_L3_INIT_1, 0xD0);
    }
    else
    {
        // LE Max = 20, Initial = 16, Servo Initial = 16
        ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0x40);
        ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0x40);
        ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0x40);
        ScalerSetByte_EXINT(P7A_D2_L3_LIMIT_INIT, 0x40);
        ScalerSetByte_EXINT(P7A_A3_L0_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_B3_L1_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_C3_L2_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_D3_L3_INIT_1, 0xD0);
    }

    // Tap0 Initial Value = 18
    ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, 0x12);
    ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, 0x12);
    ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, 0x12);
    ScalerSetByte_EXINT(P7A_D4_L3_INIT_2, 0x12);

    // Tap1 Initial Value = 15
    ScalerSetByte_EXINT(P7A_A5_L0_INIT_3, 0x0F);
    ScalerSetByte_EXINT(P7A_B5_L1_INIT_3, 0x0F);
    ScalerSetByte_EXINT(P7A_C5_L2_INIT_3, 0x0F);
    ScalerSetByte_EXINT(P7A_D5_L3_INIT_3, 0x0F);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(P7A_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7A_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7A_C6_L2_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7A_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 4
    ScalerSetByte_EXINT(P7A_A9_L0_INIT_7, 0x04);
    ScalerSetByte_EXINT(P7A_B9_L1_INIT_7, 0x04);
    ScalerSetByte_EXINT(P7A_C9_L2_INIT_7, 0x04);
    ScalerSetByte_EXINT(P7A_D9_L3_INIT_7, 0x04);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P7A_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7A_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7A_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7A_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P7A_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7A_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7A_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7A_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);
}

//--------------------------------------------------
// Description  : Check DP Source OUI for Specific Action
// Input Value  : Action that Need to Check Specific Source OUI
// Output Value : Whether Specific Source OUI Hit or Not
//--------------------------------------------------
BYTE ScalerDpRx1CheckSourceOUI_EXINT0(EnumDpRxCheckSourceOUI enumDpRx1CheckSourceOUI) using 1
{
    switch(enumDpRx1CheckSourceOUI)
    {
#if(_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON)
        case _LT_TP1_PERMIT_SWING_LEVEL_0:
        {
            BYTE pucSrcIeeeOuiUser[9] = _SRC_IEEE_OUI_APPLE_2017_PRO_15INCH_IDENTIFY_STRING;

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 9; pData_EXINT[0]++)
            {
                if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x03, pData_EXINT[0])) != (pucSrcIeeeOuiUser[pData_EXINT[0]]))
                {
                    return _FALSE;
                }
            }

            return _TRUE;
        }
#endif
        default:

            return _FALSE;
    }
}

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Mst Auto Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstAutoSwitch_EXINT0(void) using 1
{
    // DPCD Write 111h
    if((ScalerGetBit_EXINT(PBA_B2_AUX_SPECIAL_IRQ_EN, _BIT7) == _BIT7) &&
       (ScalerGetBit_EXINT(PBA_B3_AUX_SPECIAL_IRQ_FLAG, _BIT7) == _BIT7))
    {
        if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x21, _BIT0) == 0x00)
        {
            // Rx1 Disable DPCD 111/1C2 IRQ
            ScalerSetBit_EXINT(PBA_B2_AUX_SPECIAL_IRQ_EN, ~(_BIT7 | _BIT4), 0x00);

            return;
        }

        // 00111h Is Set
        if((ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x01, 0x11, _BIT1) == _BIT1) ||
           (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x01, 0x11, _BIT0) == _BIT0))
        {
            if(g_enumDpMSTCapablePort == _DP_MST_NO_PORT)
            {
                // Rx1 gets MST use right
                ScalerDpRxMstInitial_EXINT0(_DP_MST_RX1_PORT);

#if(_ERROR_PRONE_CODE == _TRUE)
#if(_D0_DP_EXIST == _ON)
                // Disable other ports' capabilities
                ScalerDpRxMstCapabilitySwitch_EXINT0(_D0_INPUT_PORT, _DISABLE);
#endif
#endif
            }
        }
        // 00111h Is Cleared
        else if((ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x01, 0x11, _BIT1) == 0x00) &&
                (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x01, 0x11, _BIT0) == 0x00))
        {
            ScalerSetBit_EXINT(PBA_B3_AUX_SPECIAL_IRQ_FLAG, ~(_BIT7 | _BIT4 | _BIT3), _BIT7);

            if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
            {
                // Rx1 loses MST use right
                ScalerDpRxMstInitial_EXINT0(_DP_MST_NO_PORT);
            }
        }
    }

    // 1000h is written while 111h[1] has been cleared unexpectedly
    if((GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE_EXINT() == _TRUE) && (GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN_EXINT() == _TRUE))
    {
        if(GET_REG_DP_RX_DOWN_REQUEST_MSG_D1_SUPPORT_ENABLE_EXINT() == _TRUE)
        {
            if(g_enumDpMSTCapablePort == _DP_MST_NO_PORT)
            {
                // Recover 111h[1]
                ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x01, 0x11, ~_BIT1, _BIT1);

                ScalerDpRxMstInitial_EXINT0(_DP_MST_RX1_PORT);

#if(_ERROR_PRONE_CODE == _TRUE)
#if(_D0_DP_EXIST == _ON)
                // Disable other ports' capabilities
                ScalerDpRxMstCapabilitySwitch_EXINT0(_D0_INPUT_PORT, _DISABLE);
#endif
#endif
            }

            CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE_EXINT();
        }
    }
}

#if(_ERROR_PRONE_CODE == _TRUE)
#if(_D0_DP_EXIST == _ON)
//--------------------------------------------------
// Description  : Set Dp HotPlug Event
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetHotPlugEvent_EXINT0(EnumDpHotPlugAssertType enumHpdType) using 1
{
    // If the priority of enumHpdType is higher
    if(enumHpdType < GET_DP_RX1_HOTPLUG_ASSERT_TYPE_EXINT())
    {
        SET_DP_RX1_HOTPLUG_ASSERT_TYPE_EXINT(enumHpdType);
    }
}
#endif
#endif
#endif // End of #if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)

#endif // End of #if(_D1_DP_EXIST == _ON)

