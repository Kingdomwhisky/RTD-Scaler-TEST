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
// ID Code      : ScalerDPRx0_INT_ComboPhy.c No.0000
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
#if(_DP_SUPPORT == _ON)
BYTE ScalerDpRx0GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
BYTE ScalerDpRx0GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
void ScalerDpRx0SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
void ScalerDpRx0SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
void ScalerDpRx0SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
BYTE ScalerDpRx0Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
BYTE ScalerDpRx0TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType);
BYTE ScalerDpRx0TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType);
void ScalerDpRx0TrainingPatternEnd_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
BYTE ScalerDpRx0GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
#endif

#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx0GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit) using 1
{
    ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetBit_EXINT(PB7_C4_DPCD_DATA_PORT, ucDpcdBit);
}
//--------------------------------------------------
// Description  : Get DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx0GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL) using 1
{
    ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte_EXINT(PB7_C4_DPCD_DATA_PORT);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit) using 1
{
    ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetBit_EXINT(PB7_C4_DPCD_DATA_PORT, ~(~ucNotDpcdBit), ucDpcdBit);
}
//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue) using 1
{
    ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetByte_EXINT(PB7_C4_DPCD_DATA_PORT, ucDpcdValue);
}
//--------------------------------------------------
// Description  : DP Sink Status Setting in EXINT
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync) using 1
{
    if(enumInSync == _DP_SINK_IN_SYNC)
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 in Sync
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) | _BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 in Sync
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) | _BIT1));
        }
    }
    else
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 Out of Sync
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) & ~_BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 Out of Sync
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) & ~_BIT1));
        }
    }
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpRx0Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    BYTE ucEQCRCStatus = 0;
    BYTE ucDecodeStatus = 0;
    BYTE ucFakeLTLaneCount = g_ucDpRx0LaneCount;

    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        g_ucDpRx0LinkRequest01 = ((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & 0x03) |
                                  ((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) >> 1) & 0x0C) |
                                  ((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x04) << 4) & 0x30) |
                                  ((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x04) << 3) & 0xC0));

        g_ucDpRx0LinkRequest23 = ((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x05) & 0x03) |
                                  ((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x05) >> 1) & 0x0C) |
                                  ((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x06) << 4) & 0x30) |
                                  ((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x06) << 3) & 0xC0));

        // Clear 8b/10b Decode Error Flag
        ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Enable EQ-CRC and Clear EQ-CRC Status (-K28.5)
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [45,x]
        DELAY_45US_EXINT();

        ucEQCRCStatus = ScalerGetByte_EXINT(PB_12_EQ_CRC_1);

        // Disable EQ-CRC
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Enable EQ-CRC and Clear EQ-CRC Status (+K28.5)
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [45,x]
        DELAY_45US_EXINT();

        ucEQCRCStatus = (ucEQCRCStatus | ScalerGetByte_EXINT(PB_12_EQ_CRC_1));

        // Disable EQ-CRC
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        ucDecodeStatus = ScalerGetByte_EXINT(PB_06_DECODE_10B8B_ERROR);

        g_ucDpRx0EQCRC = 0x00;

        if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx0EQCRC |= (ucEQCRCStatus & 0x01);
        }
        else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x02) >> 1);
        }
        else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x04) >> 2);
        }
        else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x08) >> 3);
        }

        if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x01) << 1);
        }
        else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx0EQCRC |= (ucEQCRCStatus & 0x02);
        }
        else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x04) >> 1);
        }
        else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x08) >> 2);
        }

        if(GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x01) << 2);
        }
        else if(GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x02) << 1);
        }
        else if(GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx0EQCRC |= (ucEQCRCStatus & 0x04);
        }
        else if(GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x08) >> 1);
        }

        if(GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x01) << 3);
        }
        else if(GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x02) << 2);
        }
        else if(GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx0EQCRC |= ((ucEQCRCStatus & 0x04) << 1);
        }
        else if(GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx0EQCRC |= (ucEQCRCStatus & 0x08);
        }

        ucEQCRCStatus = g_ucDpRx0EQCRC;

        g_ucDpRx0EQCRC = 0x00;

        if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx0EQCRC |= (ucDecodeStatus & 0x01);
        }
        else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x02) >> 1);
        }
        else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x04) >> 2);
        }
        else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x08) >> 3);
        }

        if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x01) << 1);
        }
        else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx0EQCRC |= (ucDecodeStatus & 0x02);
        }
        else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x04) >> 1);
        }
        else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x08) >> 2);
        }

        if(GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x01) << 2);
        }
        else if(GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x02) << 1);
        }
        else if(GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx0EQCRC |= (ucDecodeStatus & 0x04);
        }
        else if(GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x08) >> 1);
        }

        if(GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x01) << 3);
        }
        else if(GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x02) << 2);
        }
        else if(GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx0EQCRC |= ((ucDecodeStatus & 0x04) << 1);
        }
        else if(GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx0EQCRC |= (ucDecodeStatus & 0x08);
        }

        ucDecodeStatus = g_ucDpRx0EQCRC;

        switch(g_ucDpRx0LaneCount)
        {
            case _DP_FOUR_LANE:

                // Lane2 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT2) == _BIT2) && ((ucDecodeStatus & _BIT2) == 0x00))
                {
                    g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x07;
                }
                else
                {
                    if(((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x05) & _BIT5) != _BIT5) &&
                       (((g_ucDpRx0LinkRequest23 & 0x03) + ((g_ucDpRx0LinkRequest23 >> 2) & 0x03)) < 3))
                    {
                        g_ucDpRx0LinkRequest23 = g_ucDpRx0LinkRequest23 + 0x04;
                    }
                }

                // Lane3 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT3) == _BIT3) && ((ucDecodeStatus & _BIT3) == 0x00))
                {
                    g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x70;
                }
                else
                {
                    if(((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x06) & _BIT5) != _BIT5) &&
                       ((((g_ucDpRx0LinkRequest23 >> 4) & 0x03) + ((g_ucDpRx0LinkRequest23 >> 6) & 0x03)) < 3))
                    {
                        g_ucDpRx0LinkRequest23 = g_ucDpRx0LinkRequest23 + 0x40;
                    }
                }

                // Lane1 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT1) == _BIT1) && ((ucDecodeStatus & _BIT1) == 0x00))
                {
                    g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x70;
                }
                else
                {
                    if(((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x04) & _BIT5) != _BIT5) &&
                       ((((g_ucDpRx0LinkRequest01 >> 4) & 0x03) + ((g_ucDpRx0LinkRequest01 >> 6) & 0x03)) < 3))
                    {
                        g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x40;
                    }
                }

                // Lane0 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT0) == _BIT0) && ((ucDecodeStatus & _BIT0) == 0x00))
                {
                    g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x07;
                }
                else
                {
                    if(((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & _BIT5) != _BIT5) &&
                       (((g_ucDpRx0LinkRequest01 & 0x03) + ((g_ucDpRx0LinkRequest01 >> 2) & 0x03)) < 3))
                    {
                        g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x04;
                    }
                }

                if((g_ucDpRx0LinkRequest01 & (_BIT3 | _BIT2)) < ((g_ucDpRx0LinkRequest23 & (_BIT7 | _BIT6)) >> 4))
                {
                    SET_DP_RX0_MAIN_LINK_MARGINAL();
                }

                break;

            case _DP_TWO_LANE:

                // Lane1 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT1) == _BIT1) && ((ucDecodeStatus & _BIT1) == 0x00))
                {
                    g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x70;
                }
                else
                {
                    if(((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x04) & _BIT5) != _BIT5) &&
                       ((((g_ucDpRx0LinkRequest01 >> 4) & 0x03) + ((g_ucDpRx0LinkRequest01 >> 6) & 0x03)) < 3))
                    {
                        g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x40;
                    }
                }

                // Lane0 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT0) == _BIT0) && ((ucDecodeStatus & _BIT0) == 0x00))
                {
                    g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x07;
                }
                else
                {
                    if(((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & _BIT5) != _BIT5) &&
                       (((g_ucDpRx0LinkRequest01 & 0x03) + ((g_ucDpRx0LinkRequest01 >> 2) & 0x03)) < 3))
                    {
                        g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x04;
                    }
                }

                break;

            case _DP_ONE_LANE:
            default:

                // Lane0 EQ-CRC Check
                if(((ucEQCRCStatus & _BIT0) == _BIT0) && ((ucDecodeStatus & _BIT0) == 0x00))
                {
                    g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x07;
                }
                else
                {
                    if(((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & _BIT5) != _BIT5) &&
                       (((g_ucDpRx0LinkRequest01 & 0x03) + ((g_ucDpRx0LinkRequest01 >> 2) & 0x03)) < 3))
                    {
                        g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x04;
                    }
                }

                break;
        }

        ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, g_ucDpRx0LinkStatus01);
        ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, g_ucDpRx0LinkStatus23);
        ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx0LinkRequest01);
        ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx0LinkRequest23);

        switch(g_ucDpRx0LaneCount)
        {
            case _DP_ONE_LANE:

                if((g_ucDpRx0LinkStatus01 & 0x07) == 0x07)
                {
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpRx0LinkStatus01 & 0x77) == 0x77)
                {
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpRx0LinkStatus01 & 0x77) == 0x77) && (((g_ucDpRx0LinkStatus23 & 0x77) == 0x77)))
                {
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;
        }
    }
    else
    {
        pData_EXINT[0] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pData_EXINT[1] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pData_EXINT[2] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pData_EXINT[3] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

        ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

        g_ucDpRx0LinkRequest01 = (pData_EXINT[0] & 0x03) | ((pData_EXINT[1] << 4) & 0x30);
        g_ucDpRx0LinkRequest23 = (pData_EXINT[2] & 0x03) | ((pData_EXINT[3] << 4) & 0x30);

#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
        if(g_ucDpRx0FakeLTLaneCount <= g_ucDpRx0LaneCount)
        {
            ucFakeLTLaneCount = g_ucDpRx0FakeLTLaneCount;
        }
        else
        {
            ucFakeLTLaneCount = g_ucDpRx0LaneCount;
        }
#endif
        switch(ucFakeLTLaneCount)
        {
            case _DP_ONE_LANE:

                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x01);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);

                if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                }

                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx0LinkRequest01);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if(((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0))))
                {
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x07);
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);

                if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                }

                if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                }

                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx0LinkRequest01);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if((((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[1] & _BIT5) == _BIT5) || ((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) == ((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x11);

                if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                }

                if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                }

                if(((pData_EXINT[2] & _BIT2) != _BIT2) && ((pData_EXINT[2] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                }

                if(((pData_EXINT[3] & _BIT2) != _BIT2) && ((pData_EXINT[3] & (_BIT1 | _BIT0)) < _BIT1))
                {
                    g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xCF) | ((pData_EXINT[3] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                }

                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx0LinkRequest01);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx0LinkRequest23);

                if((((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[1] & _BIT5) == _BIT5) || ((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) == ((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT5 | _BIT4)) >> 4))) &&
                   (((pData_EXINT[2] & _BIT5) == _BIT5) || ((pData_EXINT[2] & _BIT2) == _BIT2) || ((pData_EXINT[2] & (_BIT1 | _BIT0)) == (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x07) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[3] & _BIT5) == _BIT5) || ((pData_EXINT[3] & _BIT2) == _BIT2) || ((pData_EXINT[3] & (_BIT1 | _BIT0)) == ((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x07) & (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x77);
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;
        }
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpRx0TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    if(ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x0E, _BIT7) == _BIT7)
    {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _OFF)
        if(g_ucDpRx0LinkRate > _D0_DP_LINK_CLK_RATE)
#else
        if(g_ucDpRx0LinkRate > ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x22, 0x01))
#endif
        {
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

            return _FALSE;
        }
    }
    else
    {
        if(g_ucDpRx0LinkRate > ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x00, 0x01))
        {
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

            return _FALSE;
        }
    }

    ScalerDpRx0ErrorCounterDisable_EXINT0();

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        ScalerDpRx0Tp1SetPhy_EXINT0(_DP_NF_REF_XTAL);
    }

    ScalerDpRx0ErrorCounterEnable_EXINT0(enumDpLtType);

    if(ScalerDpRx0Tp1Check_EXINT0(enumDpLtType) == _TRUE)
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
BYTE ScalerDpRx0TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    ScalerDpRx0ErrorCounterDisable_EXINT0();

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        ScalerDpRx0Tp2SetPhy_EXINT0();
    }

    ScalerDpRx0ErrorCounterEnable_EXINT0(enumDpLtType);

    if(ScalerDpRx0Tp2Check_EXINT0(enumDpLtType) == _TRUE)
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
void ScalerDpRx0TrainingPatternEnd_EXINT0(void) using 1
{
    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            // Clear Lane1/2/3 Link status
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x02, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _DP_TWO_LANE:
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            // Clear Lane2/3 Link status
            ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _DP_FOUR_LANE:
        default:
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            break;
    }

    // De-Skew Circuit Reset
    ScalerSetBit_EXINT(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

    if((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // Enable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    if((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
    {
        // Disable Scrambling
        ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // Enable Scrambling
        ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
    }
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx0GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL) using 3
{
    ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte_EXINT(PB7_C4_DPCD_DATA_PORT);
}
#endif

#endif
