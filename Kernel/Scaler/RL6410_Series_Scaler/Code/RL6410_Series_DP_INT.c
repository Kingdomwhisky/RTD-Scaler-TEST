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
// ID Code      : RL6410_Series_DP_INT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_DP_SUPPORT == _ON)

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
BYTE ScalerDpAuxJudgeHandler_EXINT0(void);
void ScalerDpIntHandler_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpWDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID);
#endif

void ScalerDpExitIntSetting_EXINT0(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpAuxJudgeHandler_EXINT0(void) using 1
{
    bit bReturnValueD0 = _FALSE;
    bit bReturnValueD1 = _FALSE;

#if(_D0_DP_EXIST == _TRUE)

    if(ScalerGetBit_EXINT(PB7_7A_AUX_DIG_PHYA, (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))
    {
        if(ScalerGetBit_EXINT(PB7_79_AUX_DIG_PHY9, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
        {
            if((MCU_FFED_MCU_CONTROL & _BIT1) == 0x00)
            {
                MCU_FFE9_MCU_CLK_CONTROL_1 = (_FLASH_CLK_PS_FAST_DIV | (MCU_FFE9_MCU_CLK_CONTROL_1 & 0xF0));
            }

            // Disable Aux INT
            ScalerSetBit_EXINT(PB7_7A_AUX_DIG_PHYA, ~_BIT4, 0x00);

            // Enable GDI BandGap
            ScalerSetBit_EXINT(P1D_14_BANDGAP_00, ~_BIT7, _BIT7);

            // Disable Aux Power Saving Mode
            ScalerSetBit_EXINT(PB7_62_AUX_2, ~_BIT1, 0x00);

            // Switch Aux PHY to GDI BandGap
            ScalerSetBit_EXINT(PB7_63_AUX_3, ~_BIT7, 0x00);

            SET_DP_RX0_PS_AUX_TOGGLE();

            IP = 0xA0;

            // DPCD 022xxh Into INT
            if(ScalerGetBit_EXINT(PB7_FB_DUMMY_1, (_BIT7 | _BIT6)) != (_BIT7 | _BIT6))
            {
                return _TRUE;
            }
        }
        else
        {
            // Clear Aux INT flag
            ScalerSetBit_EXINT(PB7_7A_AUX_DIG_PHYA, ~_BIT0, _BIT0);

            // Clear Manchester/Stop pattern/Sync_end pattern/Byte boundary check Error
            ScalerSetBit_EXINT(PB7_79_AUX_DIG_PHY9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            return _TRUE;
        }
    }

    // D0 DP Global IRQ
    if(ScalerGetBit_EXINT(PB7_DC_AUX_IRQ_STATUS, _BIT7) == _BIT7)
    {
        if((MCU_FFED_MCU_CONTROL & _BIT1) == 0x00)
        {
            MCU_FFE9_MCU_CLK_CONTROL_1 = (_FLASH_CLK_PS_FAST_DIV | (MCU_FFE9_MCU_CLK_CONTROL_1 & 0xF0));
        }

#if(_D1_DP_EXIST == _ON)
        if(ScalerGetBit_EXINT(PBA_FB_DUMMY_1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Aux Firmware Control -> Reply Defer
            SET_DP_RX1_AUX_MANUAL_MODE_EXINT();

            g_ucDpRx1AuxAddressBackup = (ScalerGetByte_EXINT(PBA_D4_AUX_RX_ADDR_L));

            // Enable Force Defer
            ScalerSetBit_EXINT(PBA_D0_AUX_MODE_SET, ~_BIT4, _BIT4);

            // Reset Aux FIFO
            ScalerSetBit_EXINT(PBA_DA_AUX_FIFO_RST, ~_BIT0, _BIT0);
        }
#endif

        if(ScalerGetBit_EXINT(PB7_FB_DUMMY_1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Aux Firmware Control -> Reply Defer
#if(_D1_DP_EXIST == _ON)
            SET_DP_RX1_AUX_MANUAL_MODE_EXINT();
#endif
            SET_DP_RX0_AUX_MANUAL_MODE_EXINT();

            g_ucDpRx0AuxAddressBackup = (ScalerGetByte_EXINT(PB7_D4_AUX_RX_ADDR_L));

            // Enable Force Defer
            ScalerSetBit_EXINT(PB7_D0_AUX_MODE_SET, ~_BIT4, _BIT4);

            // Reset Aux FIFO
            ScalerSetBit_EXINT(PB7_DA_AUX_FIFO_RST, ~_BIT0, _BIT0);
        }
        else
        {
            // Aux Firmware Control -> Reply Defer
#if(_D1_DP_EXIST == _ON)
            SET_DP_RX1_AUX_MANUAL_MODE_EXINT();
#endif
            SET_DP_RX0_AUX_MANUAL_MODE_EXINT();
        }

        g_pucDpRx0Backup[0] = ScalerGetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H);
        g_pucDpRx0Backup[1] = ScalerGetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M);
        g_pucDpRx0Backup[2] = ScalerGetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L);

        // Symbol Error Count Read IRQ
        if(ScalerGetBit_EXINT(PB7_FB_DUMMY_1, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            // Clear IRQ Flag
            ScalerSetBit_EXINT(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT1);

            if(GET_DP_RX0_SOURCE_READ_ERROR_COUNT() == _FALSE)
            {
                // Only Reply when State Machine is at Transmit Idle Standby State
                if(ScalerGetBit_EXINT(PB7_C7_TP1_OCCR, 0x07) == 0x02)
                {
                    // Reset Aux FIFO
                    ScalerSetBit_EXINT(PB7_DA_AUX_FIFO_RST, ~_BIT0, _BIT0);

                    // Reload The Length of Aux Message
                    ScalerSetByte_EXINT(PB7_D8_AUX_TX_LEN, (ScalerGetByte_EXINT(PB7_D5_AUX_RXLEN) & 0x0F));

                    // Directly Reply Aux Defer Command
                    ScalerSetBit_EXINT(PB7_D7_AUX_TX_CMD, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerDpRx0ErrorCounterUpdate_EXINT0();

                    SET_DP_RX0_SOURCE_READ_ERROR_COUNT();
                }
                else
                {
                    // Reset 8B/10B Error Counter
                    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }
            else
            {
                // Update Symbol Error Count by HW Auto Reply
                CLR_DP_RX0_SOURCE_READ_ERROR_COUNT();

                // Reset 8B/10B Error Counter
                ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            bReturnValueD0 = _TRUE;
        }
        else
        {
            // Reset Read Error Count Flag Beside Symbol Error Count 00210h ~ 00217h
            CLR_DP_RX0_SOURCE_READ_ERROR_COUNT();
        }

        // DPCD 022xxh Into INT
        if(ScalerGetBit_EXINT(PB7_FB_DUMMY_1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear Flag
            ScalerSetBit_EXINT(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);

            pData_EXINT[1] = (ScalerGetByte_EXINT(PB7_D5_AUX_RXLEN) & 0x0F) + 1;
            g_ucDpRx0AuxAddressBackup -= pData_EXINT[1];

            if(g_ucDpRx0AuxAddressBackup <= 0x0F)
            {
                if(g_ucDpRx0AuxAddressBackup == 0x00)
                {
                    ScalerSetByte_EXINT(PB7_D9_AUX_TX_DATA, g_ucDpRx0DPCD02200hValue);
                    g_ucDpRx0AuxAddressBackup++;
                    pData_EXINT[1]--;
                }

                if((pData_EXINT[1] > 0) && (g_ucDpRx0AuxAddressBackup == 0x01))
                {
                    ScalerSetByte_EXINT(PB7_D9_AUX_TX_DATA, g_ucDpRx0DPCD02201hValue);
                    g_ucDpRx0AuxAddressBackup++;
                    pData_EXINT[1]--;
                }

                if((g_ucDpRx0AuxAddressBackup + pData_EXINT[1]) > 16)
                {
                    // pData_EXINT[2] is The Address of DPCD Table
                    for(pData_EXINT[2] = g_ucDpRx0AuxAddressBackup; pData_EXINT[2] <= 0x0F; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(PB7_D9_AUX_TX_DATA, ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x00, pData_EXINT[2]));
                    }

                    // Set DPCD 02210h[3] = 1 --> VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
                    ScalerSetByte_EXINT(PB7_D9_AUX_TX_DATA, g_ucDpRx0DPCD02210hValue);

                    for(pData_EXINT[2] = pData_EXINT[2]; pData_EXINT[2] <= pData_EXINT[1]; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(PB7_D9_AUX_TX_DATA, 0x00);
                    }
                }
                else
                {
                    for(pData_EXINT[2] = 0; pData_EXINT[2] < pData_EXINT[1]; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(PB7_D9_AUX_TX_DATA, ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x00, (g_ucDpRx0AuxAddressBackup + pData_EXINT[2])));
                    }
                }
            }
            else
            {
                if(g_ucDpRx0AuxAddressBackup == 0x10)
                {
                    // Set DPCD 02210h[3] = 1 --> VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
                    ScalerSetByte_EXINT(PB7_D9_AUX_TX_DATA, g_ucDpRx0DPCD02210hValue);

                    g_ucDpRx0AuxAddressBackup++;
                    pData_EXINT[1]--;
                }

                for(pData_EXINT[2] = 0; pData_EXINT[2] < pData_EXINT[1]; pData_EXINT[2]++)
                {
                    ScalerSetByte_EXINT(PB7_D9_AUX_TX_DATA, 0x00);
                }
            }

            // Reload The Length of Aux Message
            ScalerSetByte_EXINT(PB7_D8_AUX_TX_LEN, (ScalerGetByte_EXINT(PB7_D5_AUX_RXLEN) & 0x0F));
        }

        if((ScalerGetByte_EXINT(PB7_DD_AUX_DPCD_IRQ) & (_BIT7 | _BIT6 | _BIT5)) != 0x00)  // Write Link Config Field into INT0
        {
            g_ucDpRx0TrainingPatternSet = (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x02) & 0x03);

            // Backup Source Write Continous 0x102 and 0x103
            g_ucDpRx0LTPatternSet = ScalerGetByte_EXINT(PB7_DD_AUX_DPCD_IRQ);

            // SVN Record 777
            if(((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_FAIL) ||
                (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL)) &&
               ((g_ucDpRx0LTPatternSet & (_BIT7 | _BIT6 | _BIT5)) == _BIT6) &&
               ((g_ucDpRx0LinkRate != ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x00)) ||
                (g_ucDpRx0LaneCount != (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & 0x1F))))
            {
                g_ucDpRx0TrainingPatternSet = _DP_TRAINING_PATTERN_END;

                SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);
            }

            g_ucDpRx0LinkRate = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x00);
            g_ucDpRx0LaneCount = (ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & 0x1F);

            // Clear Flag
            ScalerSetBit_EXINT(PB7_DD_AUX_DPCD_IRQ, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            switch(g_ucDpRx0TrainingPatternSet)
            {
                case _DP_TRAINING_PATTERN_1:

                    CLR_DP_RX0_BACKUP_PD_LINK_STATUS_FLG();

                    // Check Source Only Write 0x102 without 0x103~0x106
                    if((g_ucDpRx0LTPatternSet & (_BIT7 | _BIT5)) == _BIT7)
                    {
                        if((GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_PASS) &&
                           (GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_PASS) &&
                           (GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) &&
                           (GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL))
                        {
                            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0x03, 0x00);
                            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0x04, 0x00);
                            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0x05, 0x00);
                            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0x06, 0x00);

                            g_ucDpRx0LinkRequest01 = 0x00;
                            g_ucDpRx0LinkRequest23 = 0x00;

#if(_DP_HBR_RBR_LT_FORCE_MARGINAL_LINK == _ON)
                            SET_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR();
                            SET_DP_RX_D0_LANE1_MARGIN_LINK_HBR_RBR();
                            SET_DP_RX_D0_LANE2_MARGIN_LINK_HBR_RBR();
                            SET_DP_RX_D0_LANE3_MARGIN_LINK_HBR_RBR();
#endif
                            g_bDpRx0Tp1Initial = _TRUE;
                        }
                    }

                    if((GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_PASS) &&
                       (GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_PASS))
                    {
                        if(GET_DP_RX0_FAKE_LINK_TRAINING() == _FALSE)
                        {
                            if(ScalerDpRx0TrainingPattern1_EXINT0(_DP_NORMAL_LT) == _TRUE)
                            {
                                SET_DP_RX0_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_PASS);
                            }
                            else
                            {
                                SET_DP_RX0_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_FAIL);
                            }
                        }
                        else
                        {
                            if(ScalerDpRx0TrainingPattern1_EXINT0(_DP_FAKE_LT) == _TRUE)
                            {
                                SET_DP_RX0_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_1_PASS);
                            }
                            else
                            {
                                SET_DP_RX0_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_1_FAIL);
                            }
                        }
                    }

                    bReturnValueD0 = _TRUE;

                    break;

                case _DP_TRAINING_PATTERN_2:
                case _DP_TRAINING_PATTERN_3:

                    g_bDpRx0Tp1Initial = _FALSE;

                    if((GET_DP_RX0_FAKE_LINK_TRAINING() == _FALSE) &&
                       ((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                        (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL)))
                    {
                        if(ScalerDpRx0TrainingPattern2_EXINT0(_DP_NORMAL_LT) == _TRUE)
                        {
                            SET_DP_RX0_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_PASS);

                            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), 0x00);
                        }
                        else
                        {
                            SET_DP_RX0_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_FAIL);
                        }
                    }
                    else if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL))
                    {
                        if(ScalerDpRx0TrainingPattern2_EXINT0(_DP_FAKE_LT) == _TRUE)
                        {
                            SET_DP_RX0_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_2_PASS);
                        }
                        else
                        {
                            SET_DP_RX0_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_2_FAIL);
                        }
                    }

                    bReturnValueD0 = _TRUE;

                    break;

                case _DP_TRAINING_PATTERN_END:

                    g_bDpRx0Tp1Initial = _FALSE;

                    if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY))
                    {
                        ScalerDpRx0TrainingPatternEnd_EXINT0();
                    }
                    else if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_PASS))
                    {
                        ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                        if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS)
                        {
                            ScalerDpRx0TrainingPatternEnd_EXINT0();

                            SET_DP_RX0_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY);

                            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY);

                            ScalerTimerWDActivateTimerEvent_EXINT0(30, _SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY);
                        }
                        else
                        {
                            SET_DP_RX0_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
                        }

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                        {
                            CLR_DP_RX_D0_MARGIN_LINK_HBR2();
                        }
                        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                        {
                            CLR_DP_RX_D6_MARGIN_LINK_HBR2();
                        }
#else
                        CLR_DP_RX_D0_MARGIN_LINK_HBR2();
#endif
#endif
                        // Set DP Receive Port0 In Sync
                        ScalerDpRx0SinkStatusSet_EXINT0(_DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);

                        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_WD_TIMER_INT_SUPPORT == _ON))
                        ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_RX0_HDCP2_SKE);
#endif
                    }
                    else if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_FAIL) ||
                            (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_FAIL) ||
                            (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_FAIL))
                    {
                        SET_DP_RX0_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_FAIL);

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                        {
                            CLR_DP_RX_D0_MARGIN_LINK_HBR2();
                        }
                        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                        {
                            CLR_DP_RX_D6_MARGIN_LINK_HBR2();
                        }
#else
                        CLR_DP_RX_D0_MARGIN_LINK_HBR2();
#endif
#endif
                    }

                    bReturnValueD0 = _TRUE;

                    break;

                default:
                    break;
            }
        }

        ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, g_pucDpRx0Backup[0]);
        ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, g_pucDpRx0Backup[1]);
        ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, g_pucDpRx0Backup[2]);
    }

#endif

#if(_D1_DP_EXIST == _TRUE)

    if(ScalerGetBit_EXINT(PBA_7A_AUX_DIG_PHYA, (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))
    {
        if(ScalerGetBit_EXINT(PBA_79_AUX_DIG_PHY9, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
        {
            if((MCU_FFED_MCU_CONTROL & _BIT1) == 0x00)
            {
                MCU_FFE9_MCU_CLK_CONTROL_1 = (_FLASH_CLK_PS_FAST_DIV | (MCU_FFE9_MCU_CLK_CONTROL_1 & 0xF0));
            }

            // Disable Aux INT
            ScalerSetBit_EXINT(PBA_7A_AUX_DIG_PHYA, ~_BIT4, 0x00);

            // Enable GDI BandGap
            ScalerSetBit_EXINT(P1D_14_BANDGAP_00, ~_BIT7, _BIT7);

            // Disable Aux Power Saving Mode
            ScalerSetBit_EXINT(PBA_62_AUX_2, ~_BIT1, 0x00);

            // Switch Aux PHY to GDI BandGap
            ScalerSetBit_EXINT(PBA_63_AUX_3, ~_BIT7, 0x00);

            SET_DP_RX1_PS_AUX_TOGGLE();

            IP = 0xA0;

            // DPCD 022xxh Into INT
            if(ScalerGetBit_EXINT(PBA_FB_DUMMY_1, (_BIT7 | _BIT6)) != (_BIT7 | _BIT6))
            {
                return _TRUE;
            }
        }
        else
        {
            // Clear Aux INT flag
            ScalerSetBit_EXINT(PBA_7A_AUX_DIG_PHYA, ~_BIT0, _BIT0);

            // Clear Manchester/Stop pattern/Sync_end pattern/Byte boundary check Error
            ScalerSetBit_EXINT(PBA_79_AUX_DIG_PHY9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            return _TRUE;
        }
    }

    // D1 DP Global IRQ
    if(ScalerGetBit_EXINT(PBA_DC_AUX_IRQ_STATUS, _BIT7) == _BIT7)
    {
        if((MCU_FFED_MCU_CONTROL & _BIT1) == 0x00)
        {
            MCU_FFE9_MCU_CLK_CONTROL_1 = (_FLASH_CLK_PS_FAST_DIV | (MCU_FFE9_MCU_CLK_CONTROL_1 & 0xF0));
        }

        if(ScalerGetBit_EXINT(PBA_FB_DUMMY_1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            if(ScalerGetBit_EXINT(PBA_D0_AUX_MODE_SET, _BIT4) == 0x00)
            {
                // Aux Firmware Control -> Reply Defer
                SET_DP_RX1_AUX_MANUAL_MODE_EXINT();

                g_ucDpRx1AuxAddressBackup = (ScalerGetByte_EXINT(PBA_D4_AUX_RX_ADDR_L));

                // Enable Force Defer
                ScalerSetBit_EXINT(PBA_D0_AUX_MODE_SET, ~_BIT4, _BIT4);

                // Reset Aux FIFO
                ScalerSetBit_EXINT(PBA_DA_AUX_FIFO_RST, ~_BIT0, _BIT0);
            }
        }
        else
        {
            // Aux Firmware Control -> Reply Defer
            SET_DP_RX1_AUX_MANUAL_MODE_EXINT();
        }

        g_pucDpRx1Backup[0] = ScalerGetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H);
        g_pucDpRx1Backup[1] = ScalerGetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M);
        g_pucDpRx1Backup[2] = ScalerGetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L);

        // Symbol Error Count Read IRQ
        if(ScalerGetBit_EXINT(PBA_FB_DUMMY_1, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            // Clear IRQ Flag
            ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT1);

            if(GET_DP_RX1_SOURCE_READ_ERROR_COUNT() == _FALSE)
            {
                // Only Reply when State Machine is at Transmit Idle Standby State
                if(ScalerGetBit_EXINT(PBA_C7_TP1_OCCR, 0x07) == 0x02)
                {
                    // Reset Aux FIFO
                    ScalerSetBit_EXINT(PBA_DA_AUX_FIFO_RST, ~_BIT0, _BIT0);

                    // Reload The Length of Aux Message
                    ScalerSetByte_EXINT(PBA_D8_AUX_TX_LEN, (ScalerGetByte_EXINT(PBA_D5_AUX_RXLEN) & 0x0F));

                    // Directly Reply Aux Defer Command
                    ScalerSetBit_EXINT(PBA_D7_AUX_TX_CMD, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerDpRx1ErrorCounterUpdate_EXINT0();

                    SET_DP_RX1_SOURCE_READ_ERROR_COUNT();
                }
                else
                {
                    // Reset 8B/10B Error Counter
                    ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }
            else
            {
                // Update Symbol Error Count by HW Auto Reply
                CLR_DP_RX1_SOURCE_READ_ERROR_COUNT();

                // Reset 8B/10B Error Counter
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            bReturnValueD1 = _TRUE;
        }
        else
        {
            // Reset Read Error Count Flag Beside Symbol Error Count 00210h ~ 00217h
            CLR_DP_RX1_SOURCE_READ_ERROR_COUNT();
        }

        // DPCD 022xxh Into INT
        if(ScalerGetBit_EXINT(PBA_FB_DUMMY_1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);

            pData_EXINT[1] = (ScalerGetByte_EXINT(PBA_D5_AUX_RXLEN) & 0x0F) + 1;
            g_ucDpRx1AuxAddressBackup -= pData_EXINT[1];

            if(g_ucDpRx1AuxAddressBackup <= 0x0F)
            {
                if(g_ucDpRx1AuxAddressBackup == 0x00)
                {
                    ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, g_ucDpRx1DPCD02200hValue);
                    g_ucDpRx1AuxAddressBackup++;
                    pData_EXINT[1]--;
                }

                if((pData_EXINT[1] > 0) && (g_ucDpRx1AuxAddressBackup == 0x01))
                {
                    ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, g_ucDpRx1DPCD02201hValue);
                    g_ucDpRx1AuxAddressBackup++;
                    pData_EXINT[1]--;
                }

                if((g_ucDpRx1AuxAddressBackup + pData_EXINT[1]) > 16)
                {
                    // pData_EXINT[2] is The Address of DPCD Table
                    for(pData_EXINT[2] = g_ucDpRx1AuxAddressBackup; pData_EXINT[2] <= 0x0F; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x00, pData_EXINT[2]));
                    }

                    // Set DPCD 02210h[3] = 1 --> VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
                    ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, g_ucDpRx1DPCD02210hValue);

                    for(pData_EXINT[2] = pData_EXINT[2]; pData_EXINT[2] <= pData_EXINT[1]; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, 0x00);
                    }
                }
                else
                {
                    for(pData_EXINT[2] = 0; pData_EXINT[2] < pData_EXINT[1]; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x00, (g_ucDpRx1AuxAddressBackup + pData_EXINT[2])));
                    }
                }
            }
            else
            {
                if(g_ucDpRx1AuxAddressBackup == 0x10)
                {
                    // Set DPCD 02210h[3] = 1 --> VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
                    ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, g_ucDpRx1DPCD02210hValue);

                    g_ucDpRx1AuxAddressBackup++;
                    pData_EXINT[1]--;
                }

                for(pData_EXINT[2] = 0; pData_EXINT[2] < pData_EXINT[1]; pData_EXINT[2]++)
                {
                    ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, 0x00);
                }
            }

            // Reload The Length of Aux Message
            ScalerSetByte_EXINT(PBA_D8_AUX_TX_LEN, (ScalerGetByte_EXINT(PBA_D5_AUX_RXLEN) & 0x0F));
        }

        if((ScalerGetByte_EXINT(PBA_DD_AUX_DPCD_IRQ) & (_BIT7 | _BIT6 | _BIT5)) != 0x00)  // Write Link Config Field into INT0
        {
            g_ucDpRx1TrainingPatternSet = (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x02) & 0x03);

            // Backup Source Write Continous 0x102 and 0x103
            g_ucDpRx1LTPatternSet = ScalerGetByte_EXINT(PBA_DD_AUX_DPCD_IRQ);

            // SVN Record 777
            if(((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_FAIL) ||
                (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL)) &&
               ((g_ucDpRx1LTPatternSet & (_BIT7 | _BIT6 | _BIT5)) == _BIT6) &&
               ((g_ucDpRx1LinkRate != ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x00)) ||
                (g_ucDpRx1LaneCount != (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & 0x1F))))
            {
                g_ucDpRx1TrainingPatternSet = _DP_TRAINING_PATTERN_END;

                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);
            }

            g_ucDpRx1LinkRate = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x00);
            g_ucDpRx1LaneCount = (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & 0x1F);

            // Clear Flag
            ScalerSetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            switch(g_ucDpRx1TrainingPatternSet)
            {
                case _DP_TRAINING_PATTERN_1:

                    CLR_DP_RX1_BACKUP_PD_LINK_STATUS_FLG();

                    // Check Source Only Write 0x102 without 0x103~0x106
                    if((g_ucDpRx1LTPatternSet & (_BIT7 | _BIT5)) == _BIT7)
                    {
                        if((GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_PASS) &&
                           (GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_PASS) &&
                           (GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) &&
                           (GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL))
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
                    }

                    if((GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_PASS) &&
                       (GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_PASS))
                    {
                        if(GET_DP_RX1_FAKE_LINK_TRAINING() == _FALSE)
                        {
                            if(ScalerDpRx1TrainingPattern1_EXINT0(_DP_NORMAL_LT) == _TRUE)
                            {
                                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_PASS);
                            }
                            else
                            {
                                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_FAIL);
                            }
                        }
                        else
                        {
                            if(ScalerDpRx1TrainingPattern1_EXINT0(_DP_FAKE_LT) == _TRUE)
                            {
                                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_1_PASS);
                            }
                            else
                            {
                                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_1_FAIL);
                            }
                        }
                    }

                    bReturnValueD1 = _TRUE;

                    break;

                case _DP_TRAINING_PATTERN_2:
                case _DP_TRAINING_PATTERN_3:

                    g_bDpRx1Tp1Initial = _FALSE;

                    if((GET_DP_RX1_FAKE_LINK_TRAINING() == _FALSE) &&
                       ((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                        (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL)))
                    {
                        if(ScalerDpRx1TrainingPattern2_EXINT0(_DP_NORMAL_LT) == _TRUE)
                        {
                            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_PASS);

                            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), 0x00);
                        }
                        else
                        {
                            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_FAIL);
                        }
                    }
                    else if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL))
                    {
                        if(ScalerDpRx1TrainingPattern2_EXINT0(_DP_FAKE_LT) == _TRUE)
                        {
                            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_2_PASS);
                        }
                        else
                        {
                            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_2_FAIL);
                        }
                    }

                    bReturnValueD1 = _TRUE;

                    break;

                case _DP_TRAINING_PATTERN_END:

                    g_bDpRx1Tp1Initial = _FALSE;

                    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY))
                    {
                        ScalerDpRx1TrainingPatternEnd_EXINT0();
                    }
                    else if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_PASS))
                    {
                        ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                        if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS)
                        {
                            ScalerDpRx1TrainingPatternEnd_EXINT0();

                            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY);

                            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX1_DP_LINK_TRAINING_REBUILD_PHY);

                            ScalerTimerWDActivateTimerEvent_EXINT0(30, _SCALER_WD_TIMER_EVENT_RX1_DP_LINK_TRAINING_REBUILD_PHY);
                        }
                        else
                        {
                            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
                        }

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
                        CLR_DP_RX_D1_MARGIN_LINK_HBR2();
#endif
                        // Set DP Receive Port0 In Sync
                        ScalerDpRx1SinkStatusSet_EXINT0(_DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);

                        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_WD_TIMER_INT_SUPPORT == _ON))
                        ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE);
#endif
                    }
                    else if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_FAIL) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_FAIL) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_FAIL))
                    {
                        SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_FAIL);

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
                        CLR_DP_RX_D1_MARGIN_LINK_HBR2();
#endif
                    }

                    bReturnValueD1 = _TRUE;

                    break;

                default:
                    break;
            }
        }

        ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, g_pucDpRx1Backup[0]);
        ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, g_pucDpRx1Backup[1]);
        ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, g_pucDpRx1Backup[2]);
    }

#endif

    if((bReturnValueD0 == _TRUE) || (bReturnValueD1 == _TRUE))
    {
        ScalerDpExitIntSetting_EXINT0();

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpIntHandler_EXINT0(void) using 1
{
#if(_D0_DP_EXIST == _ON)
    ScalerDpRx0IntHandler_EXINT0();
#endif

#if(_D1_DP_EXIST == _ON)
    ScalerDpRx1IntHandler_EXINT0();
#endif
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Handle DP Related WD Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerDpWDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID) using 3
{
    BYTE ucTemp = 0;

    switch(enumEventID)
    {
#if(_D0_DP_EXIST == _ON)

        case _SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY:

            if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY)
            {
                ucTemp = ScalerGetByte_EXINT(PB7_D0_AUX_MODE_SET);

                if((ucTemp & _BIT1) == _BIT1)
                {
                    SET_DP_RX0_AUX_MANUAL_MODE_EXINT();
                }

                g_pucDpRx0Backup[0] = ScalerGetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H);
                g_pucDpRx0Backup[1] = ScalerGetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M);
                g_pucDpRx0Backup[2] = ScalerGetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L);

                ScalerDpRx0RebuildPhy_WDINT(ScalerDpRx0GetDpcdInfo_WDINT(0x00, 0x01, 0x00));

                SET_DP_RX0_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);
                SET_DP_RX0_NORMAL_LINK_TRAINING_SETPHY_FINISH();

                // De-Skew Circuit Reset
                ScalerSetBit_EXINT(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
                ScalerSetBit_EXINT(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

                // Mac Reset After Link Clock Stable
                ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
                ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

                // Delay Time us [150,x] Delay for Lane Alignment after Mac Reset
                DELAY_XUS_EXINT(150);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
                if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
                {
                    // Reset Daisy Chain Async-fifo
                    ScalerSetBit_EXINT(PA_00_MST2SST_RESET, ~_BIT6, _BIT6);
                    ScalerSetBit_EXINT(PA_00_MST2SST_RESET, ~_BIT6, 0x00);
                }
#endif

                ScalerDpRx0DecodeErrorCountReset_WDINT();

                ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, g_pucDpRx0Backup[0]);
                ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, g_pucDpRx0Backup[1]);
                ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, g_pucDpRx0Backup[2]);

                if((ucTemp & _BIT1) == _BIT1)
                {
                    SET_DP_RX0_AUX_AUTO_MODE_EXINT();
                }
            }

            break;
#endif

#if(_D1_DP_EXIST == _ON)

        case _SCALER_WD_TIMER_EVENT_RX1_DP_LINK_TRAINING_REBUILD_PHY:

            if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY)
            {
                ucTemp = ScalerGetByte_EXINT(PBA_D0_AUX_MODE_SET);

                if((ucTemp & _BIT1) == _BIT1)
                {
                    SET_DP_RX1_AUX_MANUAL_MODE_EXINT();
                }

                g_pucDpRx1Backup[0] = ScalerGetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H);
                g_pucDpRx1Backup[1] = ScalerGetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M);
                g_pucDpRx1Backup[2] = ScalerGetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L);

                ScalerDpRx1RebuildPhy_WDINT(ScalerDpRx1GetDpcdInfo_WDINT(0x00, 0x01, 0x00));

                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);
                SET_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH();

                // De-Skew Circuit Reset
                ScalerSetBit_EXINT(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
                ScalerSetBit_EXINT(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

                // Mac Reset After Link Clock Stable
                ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
                ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

                // Delay Time us [150,x] Delay for Lane Alignment after Mac Reset
                DELAY_XUS_EXINT(150);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
                if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
                {
                    // Reset Daisy Chain Async-fifo
                    ScalerSetBit_EXINT(PA_00_MST2SST_RESET, ~_BIT6, _BIT6);
                    ScalerSetBit_EXINT(PA_00_MST2SST_RESET, ~_BIT6, 0x00);
                }
#endif

                ScalerDpRx1DecodeErrorCountReset_WDINT();

                ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, g_pucDpRx1Backup[0]);
                ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, g_pucDpRx1Backup[1]);
                ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, g_pucDpRx1Backup[2]);

                if((ucTemp & _BIT1) == _BIT1)
                {
                    SET_DP_RX1_AUX_AUTO_MODE_EXINT();
                }
            }

            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Handle the DP settings when exiting sysint
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpExitIntSetting_EXINT0(void) using 1
{
#if(_D0_DP_EXIST == _ON)
    // Aux Hardware Control
    SET_DP_RX0_AUX_AUTO_MODE_EXINT();
#endif

#if(_D1_DP_EXIST == _ON)
    // Aux Hardware Control
    SET_DP_RX1_AUX_AUTO_MODE_EXINT();
#endif
}
#endif // #if(_DP_SUPPORT == _ON)
