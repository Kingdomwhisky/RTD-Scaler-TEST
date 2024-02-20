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
// ID Code      : RL6449_Series_DPRx0_INT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6449_SERIES_DPRX0_INT__

#include "ScalerFunctionInclude.h"

#if(_D0_DP_EXIST == _ON)

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
void ScalerDpRx0IntHandler_EXINT0(void);
void ScalerDpRx0Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx0Tp2SetPhy_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx0RebuildPhy_WDINT(BYTE ucDpLinkRate);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0IntHandler_EXINT0(void) using 1
{
    // _ERROR_PRONE_CODE
    // Aux Firmware Control -> Reply Defer
#if(_D1_DP_EXIST == _ON)
    SET_DP_RX1_AUX_MANUAL_MODE_EXINT();
#endif
    SET_DP_RX0_AUX_MANUAL_MODE_EXINT();

    g_pucDpRx0Backup[0] = ScalerGetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H);
    g_pucDpRx0Backup[1] = ScalerGetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M);
    g_pucDpRx0Backup[2] = ScalerGetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L);

    // DP Global IRQ Flag
    if(ScalerGetBit_EXINT(PB7_DC_AUX_IRQ_STATUS, _BIT7) == _BIT7)
    {
        // Fifo overflow/ underflow IRQ & flag
        if((ScalerGetBit_EXINT(PB6_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) != 0x00) && (ScalerGetBit_EXINT(PB5_21_PG_CTRL_1, (_BIT4 | _BIT2)) != 0x00))
        {
            // Disable fifo overflwo/ underflwo IRQ
            ScalerSetBit_EXINT(PB6_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

            // Set free run & force to BG
            ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT5 | _BIT3), _BIT5);

#if(_AUDIO_SUPPORT == _ON)
            // Disable Audio Channel
            ScalerAudioDpAudioEnable_EXINT0(_DISABLE, _D0_INPUT_PORT);
#endif

            // Disable VB-ID[3] Change IRQ
            ScalerSetBit_EXINT(PB6_3B_DP_IRQ_CTRL1, ~_BIT4, 0x00);

            // Set DP Receive Port0 Out of Sync
            ScalerDpRx0SinkStatusSet_EXINT0(_DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);

            // The Judge Handler take much time, It lead to MacBook 720P @50 <---> @60 Timing changing Issue
            if(((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x11) & _BIT0) == 0x00) &&
               (ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0) &&
               (ScalerDpRx0DFECheck_EXINT0() == _FALSE))
            {
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x05, 0x00);
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
        if((ScalerGetBit_EXINT(PB6_3B_DP_IRQ_CTRL1, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(PB6_36_DP_GLB_STATUS, _BIT6) == _BIT6))
        {
            // Disable VB-ID[3] Change IRQ
            ScalerSetBit_EXINT(PB6_3B_DP_IRQ_CTRL1, ~_BIT4, 0x00);

            // Clear VB-ID[3] Change Flag
            ScalerSetBit_EXINT(PB6_36_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

            if(ScalerGetBit_EXINT(PB6_01_DP_VBID, _BIT3) == _BIT3)
            {
                // Set DP Receive Port0 Out of Sync
                ScalerDpRx0SinkStatusSet_EXINT0(_DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);
            }
        }

        if(ScalerGetBit_EXINT(PB7_DD_AUX_DPCD_IRQ, _BIT0) == _BIT0) // Write 00600h into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PB7_DD_AUX_DPCD_IRQ, ~_BIT0, _BIT0);

            if((ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
               (ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
            {
                // DP Power Down
                SET_DP_RX0_BACKUP_PD_LINK_STATUS_FLG();

                g_pucDpRx0LinkStatusBackup_INT[0] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x02);
                g_pucDpRx0LinkStatusBackup_INT[1] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x02, 0x03);
                g_pucDpRx0LinkStatusBackup_INT[2] = ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x04, _BIT0);

                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
                ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT0), _BIT7);

#if(_DP_MST_SUPPORT == _ON)
                CLR_DP_RX0_SOURCE_WRITE_POWER_UP();
#endif
            }
            else if(ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
            {
                // DP Power Normal
                if(GET_DP_RX0_BACKUP_PD_LINK_STATUS_FLG() == _TRUE)
                {
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, g_pucDpRx0LinkStatusBackup_INT[0]);
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, g_pucDpRx0LinkStatusBackup_INT[1]);
                    ScalerDpRx0SetDpcdBitValue_EXINT0(0x00, 0x02, 0x04, ~(_BIT7 | _BIT0), (_BIT7 | g_pucDpRx0LinkStatusBackup_INT[2]));
                }

                CLR_DP_RX0_BACKUP_PD_LINK_STATUS_FLG();
                g_pucDpRx0LinkStatusBackup_INT[0] = 0x00;
                g_pucDpRx0LinkStatusBackup_INT[1] = 0x00;
                g_pucDpRx0LinkStatusBackup_INT[2] = 0x00;

#if(_DP_MST_SUPPORT == _ON)
                SET_DP_RX0_SOURCE_WRITE_POWER_UP(_DP_SOURCE_WRITE_POWER_UP_TRIGGERED);
#endif
            }
        }

        if(ScalerGetBit_EXINT(PB7_DA_AUX_FIFO_RST, (_BIT2 | _BIT1)) == (_BIT2 | _BIT1)) // Write 68xxxh into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PB7_DA_AUX_FIFO_RST, ~_BIT1, _BIT1);

            // Clear Integrity Failure Flag
            ScalerSetBit_EXINT(PB_1B_HDCP_INTGT_VRF, ~_BIT1, _BIT1);

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
            if(ScalerGetBit_EXINT(PB7_FA_DUMMY_0, _BIT3) == _BIT3)
            {
                // Detect if V'(0x68027) is read by Source
                if((ScalerGetByte_EXINT(PB7_D3_AUX_RX_ADDR_M) == 0x80) && (ScalerGetByte_EXINT(PB7_D4_AUX_RX_ADDR_L) == 0x28))
                {
                    ScalerDpRx0HDCPResetKsvFifoToFirst_EXINT0();
                }
            }
#endif
            if(GET_DP_RX0_FAKE_LINK_TRAINING() == _TRUE)
            {
                // DP Mac Clock Select to Xtal Clock
                ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);
            }
        }

        // Detect if Aksv(0x6800B) is Written by Source
        if(ScalerGetBit_EXINT(PB7_A5_AUX_RESERVE5, (_BIT6 | _BIT2)) == (_BIT6 | _BIT2))
        {
            ScalerSetBit_EXINT(PB7_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Switch HDCP to 1.4 Module from 2.2 Module as receiving AKsv
            if(GET_DP_RX0_HDCP_MODE_EXINT() == _HDCP_22)
            {
                // Select to HDCP 1.4 Module
                SET_DP_RX0_HDCP_MODE_EXINT(_HDCP_14);

                // Calculate R0' by manual toggle HDCP 1.4 Module
                ScalerSetBit_EXINT(PB_63_HDCP_OTHER, ~_BIT7, _BIT7);
                ScalerSetBit_EXINT(PB_63_HDCP_OTHER, ~_BIT7, 0x00);
            }

#if(_WD_TIMER_INT_SUPPORT == _ON)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_RX0_HDCP2_SKE);
#endif
#endif

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
            ScalerDpRx0HDCPResetDpcdInfo_EXINT0();

            SET_DP_RX0_HDCP_AUTH_AKSV_WRITTEN();
#endif
        }

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
        // Read 6803A into INT0
        if(ScalerGetBit_EXINT(PB7_FA_DUMMY_0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            ScalerSetBit_EXINT(PB7_FA_DUMMY_0, ~_BIT0, _BIT0);

            ScalerDpRx0HDCPSetKsvFifo_EXINT0();
        }
#endif
        if(ScalerGetBit_EXINT(PB7_DD_AUX_DPCD_IRQ, _BIT2) == _BIT2) // Write 00270h into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PB7_DD_AUX_DPCD_IRQ, ~_BIT2, _BIT2);

            if(ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT0) == _BIT0)
            {
                SET_DP_RX0_CRC_CALCULATE();
            }

            // Clear TEST_CRC_COUNT
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x46, 0x20);
        }

#if(_DP_MST_SUPPORT == _ON)

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
        ScalerDpRx0MstAutoSwitch_EXINT0();
#endif

        if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
        {
            ScalerDpRxMstIntHandle_EXINT0();
        }
#endif

#if(_AUDIO_SUPPORT == _ON)
        // Detect if Auido Sampling is Changed
        if(ScalerGetBit_EXINT(PB6_50_AUD_FREQUENY_DET_0, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
        {
            // Clear Auido Sampling Change Flag
            ScalerSetBit_EXINT(PB6_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);

            // Disable Boundary Tracking Method
            ScalerSetBit_EXINT(PB6_81_AUD_BDRY_0, ~_BIT7, 0x00);

            // Disable Trend Tracking Method
            ScalerSetBit_EXINT(PB6_92_AUD_TRND_0, ~_BIT7, 0x00);

            // Reload D code
            ScalerSetBit_EXINT(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);
        }
#endif
    }

    ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, g_pucDpRx0Backup[0]);
    ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, g_pucDpRx0Backup[1]);
    ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, g_pucDpRx0Backup[2]);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef) using 1
{
    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

    // DP Lane Swap Setting
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_LANE3 << 6);
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_LANE2 << 4);
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_LANE1 << 2);
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // [1:0] DP Mac Clock Selection
    ScalerSetBit_EXINT(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // DP Lane PN Swap Setting
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT7, GET_DP_RX0_PCB_LANE3_PN_SWAP() << 7);
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT6, GET_DP_RX0_PCB_LANE2_PN_SWAP() << 6);
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT5, GET_DP_RX0_PCB_LANE1_PN_SWAP() << 5);
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT4, GET_DP_RX0_PCB_LANE0_PN_SWAP() << 4);


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

    // Digital PHY Block Power Normal
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF)

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(P1D_1B_CMU_01, ~_BIT7, 0x00);

    // [7:4] Rx_en = 4'b0000 -> Disable RX_EN
    // [3:0] CDR_en = 4'b0000 -> Disable CDR_EN
    ScalerSetByte_EXINT(P1D_1A_CMU_00, 0x00);

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT0, _BIT0);

                // [7:6] reg_en_ana_cdr = 4'b0001 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), 0x00);
                ScalerSetBit_EXINT(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), _BIT6);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT1, _BIT1);

                // [7:6] reg_en_ana_cdr = 4'b0010 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), 0x00);
                ScalerSetBit_EXINT(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), _BIT7);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT2, _BIT2);

                // [7:6] reg_en_ana_cdr = 4'b0100 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), _BIT6);
                ScalerSetBit_EXINT(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), 0x00);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT3, _BIT3);

                // [7:6] reg_en_ana_cdr = 4'b1000 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), _BIT7);
                ScalerSetBit_EXINT(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), 0x00);
            }

            // [4:3] DP Mac Select One Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT0, _BIT0);

                // [6] reg_en_ana_cdr[0] = 1 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P1D_2B_KOFFSET_07, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT1, _BIT1);

                // [7] reg_en_ana_cdr[1] = 1 --> Enable Lane1 Analog CDR
                ScalerSetBit_EXINT(P1D_2B_KOFFSET_07, ~_BIT7, _BIT7);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT2, _BIT2);

                // [6] reg_en_ana_cdr[2] = 1 --> Enable Lane2 Analog CDR
                ScalerSetBit_EXINT(P1D_2A_KOFFSET_06, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT3, _BIT3);

                // [7] reg_en_ana_cdr[3] = 1 --> Enable Lane3 Analog CDR
                ScalerSetBit_EXINT(P1D_2A_KOFFSET_06, ~_BIT7, _BIT7);
            }

            if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT0, _BIT0);

                // [6] reg_en_ana_cdr[0] = 1 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P1D_2B_KOFFSET_07, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT1, _BIT1);

                // [7] reg_en_ana_cdr[1] = 1 --> Enable Lane1 Analog CDR
                ScalerSetBit_EXINT(P1D_2B_KOFFSET_07, ~_BIT7, _BIT7);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT2, _BIT2);

                // [6] reg_en_ana_cdr[2] = 1 --> Enable Lane2 Analog CDR
                ScalerSetBit_EXINT(P1D_2A_KOFFSET_06, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P1D_1A_CMU_00, ~_BIT3, _BIT3);

                // [7] reg_en_ana_cdr[3] = 1 --> Enable Lane3 Analog CDR
                ScalerSetBit_EXINT(P1D_2A_KOFFSET_06, ~_BIT7, _BIT7);
            }

            // [4:3] DP Mac Select Two Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            // [7:4] Enable Lane0~3 Rx_en
            ScalerSetBit_EXINT(P1D_1A_CMU_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // [3:0] Enable Lane0~3 CDR_en
            ScalerSetBit_EXINT(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit_EXINT(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P1D_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // [7:6] reg_en_ana_cdr = 4'b1111 --> Enable Lane0~3 Analog CDR
            ScalerSetBit_EXINT(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerSetBit_EXINT(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // [4:3] DP Mac Select Four Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }
#else
    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            // [4:3] DP MAC Select One Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            // [4:3] DP MAC Select Four Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }
#endif

    ///////////////////////
    // Frequency Setting //
    ///////////////////////

    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
    {
        // [7:5] rate_sel = 3'b000 --> 3~6GHz
        ScalerSetBit_EXINT(P1D_44_ST_01, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [2:0] SEL_DIV = 3'b000 --> 3~6GHz
        ScalerSetBit_EXINT(P1D_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // [7:5] rate_sel = 3'b001 --> 1.5~3GHz
        ScalerSetBit_EXINT(P1D_44_ST_01, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // [2:0] SEL_DIV = 3'b001 --> 1.5~3GHz
        ScalerSetBit_EXINT(P1D_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
    {
        // [3] reg_xtal_en = 1'b1 --> Using 27M Xtal
        ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~_BIT3, _BIT3);

        if(g_ucDpRx0LinkRate == _DP_LINK_RBR)
        {
            // Analog CDR Auto FLD Counter
            // 0x2D[1] 0x2E --> ref_conuter = 25
            // 0x2D[0] 0x2F --> cdr_counter = 300
            // 25/300 = 1/12 = 5*(27M/1.62G)
            ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(P1D_2E_ANA_CDR_03, 0x18);
            ScalerSetByte_EXINT(P1D_2F_ANA_CDR_04, 0x2B);
        }
        else
        {
            // Analog CDR Auto FLD Counter
            // 0x2D[1] 0x2E --> ref_conuter = 25
            // 0x2D[0] 0x2F --> cdr_counter = 500
            // 25/500 = 1/20 = 5*(27M/2.7G)
            ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(P1D_2E_ANA_CDR_03, 0x18);
            ScalerSetByte_EXINT(P1D_2F_ANA_CDR_04, 0xF3);
        }
    }
    else
    {
        // [3] reg_xtal_en = 1'b0 --> Using D10.2 Clock
        ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~_BIT3, 0x00);

        // Analog CDR Auto FLD Counter
        // ref_conuter = 125
        // cdr_counter = 250
        // 250/500 = 1/2 = 5*(D10.2_clock / data_rate)
        ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_2E_ANA_CDR_03, 0x7C);
        ScalerSetByte_EXINT(P1D_2F_ANA_CDR_04, 0xF9);
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [4] Disable Comma Detection
    ScalerSetBit_EXINT(PB_05_SAMPLE_EDGE, ~_BIT4, _BIT4);

    // [5] Disable De-Scrambling
    ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    if((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // [2] Enable Enhancement Control Mode
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // [2] Disable Enhancement Control Mode
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

    // [7:4] RST_N = 4'b0000 = 4'b1111 --> Digital Circuit Reset Toggle
    // [3:0] CDR_RST_N = 4'b0000 --> Disable DCDR
    ScalerSetByte_EXINT(P1D_3A_TMDS_RESET, 0x00);
    ScalerSetByte_EXINT(P1D_3A_TMDS_RESET, 0xF0);


    //////////////////
    // ACDR Setting //
    //////////////////

    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
    {
        // [7] reg_sel_CDR_cp = 0 --> Disable CDR Loop's CP (1nF)
        // [6:4] reg_sel_cdr_res = 3'b010 --> Analog CDR Rs = 1.5K
        // [3:0] reg_cdr_cp_in = 4'b0010 --> Analog CDR Icp = 7.5uA
        ScalerSetByte_EXINT(P1D_31_ANA_CDR_06, 0x22);

        // [0] Half_PD = 1 --> Half Rate PD
        ScalerSetBit_EXINT(P1D_39_ANA_CDR_14, ~_BIT7, _BIT7);
    }
    else
    {
        // [7] reg_sel_CDR_cp = 0 --> Disable CDR Loop's CP (1nF)
        // [6:4] reg_sel_cdr_res = 3'b100 --> Analog CDR Rs = 4K
        // [3:0] reg_cdr_cp_in = 4'b0101 --> Analog CDR Icp = 16.5uA
        ScalerSetByte_EXINT(P1D_31_ANA_CDR_06, 0x45);

        // [0] Half_PD = 0 --> Full Rate PD
        ScalerSetBit_EXINT(P1D_39_ANA_CDR_14, ~_BIT7, 0x00);
    }


    /////////////////
    // DFE Setting //
    /////////////////

    // [7:3] Tap_EN = 5'b11111 --> Enable Tap0~4
    ScalerSetBit_EXINT(P1D_21_CMU_07, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

    // Set DFE Initial
    ScalerDpRx0SetDFEInitial_EXINT0();

    // [4] en_sumamp_highgain = 0 --> Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(P1D_1D_CMU_03, ~_BIT4, 0x00);

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_HBR2:

            // LE Peaking = 3GHz
            // [7:5] LE_RLSEL = 3'b000
            // [4:2] LE_ISEL = 3'b011
            ScalerSetBit_EXINT(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

            break;

        case _DP_LINK_HBR:

            // LE Peaking = 1.7GHz
            // [7:5] LE_RLSEL = 3'b001
            // [4:2] LE_ISEL = 3'b010
            ScalerSetBit_EXINT(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            break;

        case _DP_LINK_RBR:
        default:

            // LE Peaking = 900MHz
            // [7:5] LE_RLSEL = 3'b011
            // [4:2] LE_ISEL = 3'b000
            ScalerSetBit_EXINT(P1D_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            break;
    }


    //////////////
    // K Offset //
    //////////////

    // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT5, _BIT5);

    // [6] en_fore_offset --> Toggle Foreground Calibration
    ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, 0x00);
    ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);

    // Delay Time us [85,x] Waiting for K Offset
    DELAY_XUS_EXINT(85);


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(P1D_1B_CMU_01, ~_BIT7, _BIT7);

    // [7] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

    // [2] reg_rstb_fsm --> FLD Reset
    ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~_BIT2, 0x00);

    // [1] reg_en_eqen_manual_l0 = 1'b1
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT1, _BIT1);

    // Enable Vth/Tap0 Adaptation
    ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x41);

    // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
    ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~_BIT2, _BIT2);

    // Delay Time us [85,x] Waiting for FLD Lock Band
    DELAY_XUS_EXINT(85);

    // Start to Record Tap0 Max/Min
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [85,x] Waiting for DFE Adaptation
    DELAY_XUS_EXINT(85);

    // Stop To Record Tap0 Max/Min
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~_BIT0, 0x00);

    // [1] reg_en_eqen_manual_l0 = 1'b0 --> DFE Adaptation Off
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT1, 0x00);

    // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
    ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~_BIT4, _BIT4);

    // Disable All Adapation Loop
    ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x00);

    // Read Back Tap0 Max
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    // Reload Max Value of Tap0 (Lane0)
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane1)
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetByte_EXINT(P1D_B4_L1_INIT_2, (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane2)
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetByte_EXINT(P1D_C4_L2_INIT_2, (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane3)
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetByte_EXINT(P1D_D4_L3_INIT_2, (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F));

    // Reload Tap0
    ScalerSetBit_EXINT(P1D_AA_L0_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P1D_BA_L1_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P1D_CA_L2_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P1D_DA_L3_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P1D_AA_L0_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P1D_BA_L1_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P1D_CA_L2_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P1D_DA_L3_INIT_8, ~_BIT0, 0x00);

    // [3] reg_en_data_manual_l0 = 1'b1 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    /////////////////////////
    // D10.2 Clock Measure //
    /////////////////////////

    // [7:4] reg_en_sigdet_lane = 4'b1111 --> Enable Signal Detection for D10.2
    ScalerSetBit_EXINT(P1D_19_IMPEDANCE_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [5] ln_ck_sel = 1'b0 -> DP Raw Data
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit_EXINT(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 30; g_ucDpRx0Temp++)
    {
        DELAY_5US_EXINT();

        if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            break;
        }
    }

    if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        g_pusDpRx0ClockCount[0] = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));
    }
    else
    {
        switch(g_ucDpRx0LinkRate)
        {
            case _DP_LINK_HBR2:

                g_pusDpRx0ClockCount[0] = 0x2710;

                break;

            case _DP_LINK_HBR:

                g_pusDpRx0ClockCount[0] = 0x1388;

                break;

            default:
            case _DP_LINK_RBR:

                g_pusDpRx0ClockCount[0] = 0xBB8;

                break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp2SetPhy_EXINT0(void) using 1
{
    WORD usVCOBandDiff = 0;
    WORD usVCOBandScan = 0;
    BYTE ucIcp = (ScalerGetByte_EXINT(P1D_31_ANA_CDR_06) & 0x0F);

    /////////////
    // Rx Misc //
    /////////////

    // Digital PHY Block Power Normal
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(P1D_1B_CMU_01, ~_BIT7, 0x00);

    // [4] Enable Comma Detection
    ScalerSetBit_EXINT(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    // [5] Disable De-Scrambling
    ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    if((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // [2] Enable Enhancement Control Mode
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // [2] Disable Enhancement Control Mode
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

    // [7:4] RST_N = 4'b0000 = 4'b1111 -->Digital Circuit Reset Toggle
    // [3:0] CDR_RST_N = 4'b0000 --> Disable DCDR
    ScalerSetByte_EXINT(P1D_3A_TMDS_RESET, 0x00);
    ScalerSetByte_EXINT(P1D_3A_TMDS_RESET, 0xF0);

    // [4] en_sumamp_highgain = 0 --> Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(P1D_1D_CMU_03, ~_BIT4, 0x00);

    // Set DFE Initial
    ScalerDpRx0SetDFEInitial_EXINT0();


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(P1D_1B_CMU_01, ~_BIT7, _BIT7);

    // [7] reg_auto_mode = 1'b1 --> FLD Auto Mode
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

    // [2] reg_rstb_fsm --> FLD Reset
    ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~_BIT2, 0x00);

    // [1] reg_en_eqen_manual_l0 = 1'b1 --> DFE Adaptation Enable
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT1, _BIT1);

    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
    {
        // Enable Vth/LE/Tap0~4
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0xDF);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [150,x] Waiting for FLD Lock Band
        DELAY_XUS_EXINT(150);

        // [1] reg_en_eqen_manual_l0 = 1'b0 --> DFE Adaptation Off
        ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT1, 0x00);

        // Disable LE/Vth/Tap0~4
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x00);

        // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
        ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~_BIT4, _BIT4);


        //////////////
        // K Offset //
        //////////////

        // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
        ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT5, _BIT5);

        // [6] en_fore_offset --> Toggle Foreground Calibration
        ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);
        ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, 0x00);
        ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);

        // Delay Time us [85,x] Waiting for DFE Adaptation
        DELAY_XUS_EXINT(85);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0xC7);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [300,x] Waiting for FLD Lock Band
        DELAY_XUS_EXINT(300);

        // Disable Adapation
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x00);
    }


    /////////////////////
    // FLD Manual Mode //
    /////////////////////

    // [6] reg_adp_en_manual = 1'b0 --> CDR Open Loop
    // [5] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~(_BIT6 | _BIT5), 0x00);

    // Scan Auto FLD + 4
    ScalerSetBit_EXINT(P1D_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P1D_36_ANA_CDR_11) & 0x7F) + 4));
    ScalerSetBit_EXINT(P1D_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P1D_37_ANA_CDR_12) & 0x7F) + 4));
    ScalerSetBit_EXINT(P1D_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P1D_38_ANA_CDR_13) & 0x7F) + 4));
    ScalerSetBit_EXINT(P1D_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P1D_39_ANA_CDR_14) & 0x7F) + 4));

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    // [6] reg_adp_en_manual = 1'b1 --> Enable VCO Clock Out
    ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~(_BIT7 | _BIT6), _BIT6);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();


    /////////////////////////
    // Scan Auto Band + 4  //
    /////////////////////////

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit_EXINT(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 30; g_ucDpRx0Temp++)
    {
        DELAY_5US_EXINT();

        if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            usVCOBandScan = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }


    /////////////////////////
    // VCO Band Difference //
    /////////////////////////

    // Scan Auto FLD
    ScalerSetBit_EXINT(P1D_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P1D_36_ANA_CDR_11) & 0x7F));
    ScalerSetBit_EXINT(P1D_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P1D_37_ANA_CDR_12) & 0x7F));
    ScalerSetBit_EXINT(P1D_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P1D_38_ANA_CDR_13) & 0x7F));
    ScalerSetBit_EXINT(P1D_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P1D_39_ANA_CDR_14) & 0x7F));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 30; g_ucDpRx0Temp++)
    {
        DELAY_5US_EXINT();

        // FLD + 4 Measure Fail or Measure Done
        if((usVCOBandScan == 0) || (ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6))
        {
            break;
        }
    }

    // Measure Done
    if((usVCOBandScan != 0) && (ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6))
    {
        g_pusDpRx0ClockCount1[_D0_DP_LANE0] = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

        usVCOBandDiff = (abs(usVCOBandScan - g_pusDpRx0ClockCount1[_D0_DP_LANE0]) >> 2);
    }
    else
    {
        usVCOBandDiff = 0;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    if(usVCOBandDiff != 0)
    {
        switch(g_ucDpRx0LaneCount)
        {
            case _DP_FOUR_LANE:

                // Lane3 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE3, usVCOBandDiff);

                // Lane2 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE2, usVCOBandDiff);

                // Lane1 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE1, usVCOBandDiff);

                // Lane0 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE0, usVCOBandDiff);

                break;

            case _DP_TWO_LANE:

                // Lane1 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE1, usVCOBandDiff);

                // Lane0 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE0, usVCOBandDiff);

                break;

            default:
            case _DP_ONE_LANE:

                // Lane0 VCO Adjust
                ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE0, usVCOBandDiff);

                break;
        }
    }

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [5] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~_BIT5, _BIT5);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US_EXINT();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit_EXINT(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US_EXINT();

    if(g_ucDpRx0LinkRate <= _DP_LINK_HBR)
    {
        // Set Vth Min = 0
        ScalerSetBit_EXINT(P1D_F9_LIMIT_10, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Only Enable Vth/Tap0 Adapation
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x41);
    }

    // [3] reg_en_data_manual_l0 = 1'b1 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT3, _BIT3);
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RebuildPhy_WDINT(BYTE ucDpLinkRate) using 3
{
    BYTE pucTap0[4];
    BYTE ucIcp = 0;


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(P1D_1B_CMU_01, ~_BIT7, 0x00);

    if((ScalerDpRx0GetDpcdInfo_WDINT(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
    {
        // [5] Disable De-Scrambling
        ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // [5] Enable De-Scrambling
        ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
    }

    // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

    // [7:4] RST_N = 4'b0000 = 4'b1111 --> Digital Circuit Reset Toggle
    // [3:0] CDR_RST_N = 4'b0000 --> Disable DCDR
    ScalerSetByte_EXINT(P1D_3A_TMDS_RESET, 0x00);
    ScalerSetByte_EXINT(P1D_3A_TMDS_RESET, 0xF0);

    ucIcp = (ScalerGetByte_EXINT(P1D_31_ANA_CDR_06) & 0x0F);


    /////////////////
    // DFE Setting //
    /////////////////

    // Tap Divider = 10 for TP2
    ScalerSetByte_EXINT(P1D_ED_LOOP_DIV_2, 0xCA);

    if(ucDpLinkRate == _DP_LINK_HBR2)
    {
        // Set Vth Max = 6, Min = 4
        ScalerSetByte_EXINT(P1D_F9_LIMIT_10, 0x64);
    }
    else
    {
        // Set Vth Max = 6, Min = 2
        ScalerSetByte_EXINT(P1D_F9_LIMIT_10, 0x62);
    }

    // LE Max = 20, Initial = 16, Servo Initial = 16
    ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x40);
    ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x40);
    ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x40);
    ScalerSetByte_EXINT(P1D_D2_L3_LIMIT_INIT, 0x40);
    ScalerSetByte_EXINT(P1D_A3_L0_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P1D_B3_L1_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P1D_C3_L2_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P1D_D3_L3_INIT_1, 0xD0);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P1D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x00);


    //////////////
    // K Offset //
    //////////////

    // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT5, _BIT5);

    // [6] en_fore_offset --> Toggle Foreground Calibration
    ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, 0x00);
    ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);

    // Delay Time us [85,x] Waiting for K Offset
    DELAY_XUS_EXINT(85);


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(P1D_1B_CMU_01, ~_BIT7, _BIT7);

    // [7] reg_auto_mode = 1'b1 --> FLD Auto Mode
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

    if(ucDpLinkRate == _DP_LINK_HBR2)
    {
        // [2] reg_rstb_fsm --> FLD Reset
        ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~_BIT2, 0x00);

        // [1] reg_eqen_manual = 1'b1 --> Enable Adaptation
        ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT1, _BIT1);

        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0xDF);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [85,x] Waiting for DFE Adaptation
        DELAY_XUS_EXINT(85);

        // Start to Record Max/Min
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~_BIT0, _BIT0);

        // Delay Time us [85,x] Waiting for DFE Adaptation
        DELAY_XUS_EXINT(85);

        // Stop To Record Max/Min
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~_BIT0, 0x00);

        // Select to Lane0
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

        // Read Back LE Max
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[0] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[0] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

        // Select to Lane1
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

        // Read Back LE Max
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[1] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[1] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

        // Select to Lane2
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

        // Read Back LE Max
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[2] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[2] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

        // Select to Lane3
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Read Back LE Max
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx0LEMax[3] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx0Tap1Max[3] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

        g_pucDpRx0LEBound[0] = 20;
        g_pucDpRx0LEBound[1] = 20;
        g_pucDpRx0LEBound[2] = 20;
        g_pucDpRx0LEBound[3] = 20;

        while(((g_pucDpRx0LEMax[0] > 15) && (g_pucDpRx0Tap1Max[0] < 4) && (g_pucDpRx0LEBound[0] > 15)) ||
              ((g_pucDpRx0LEMax[1] > 15) && (g_pucDpRx0Tap1Max[1] < 4) && (g_pucDpRx0LEBound[1] > 15)) ||
              ((g_pucDpRx0LEMax[2] > 15) && (g_pucDpRx0Tap1Max[2] < 4) && (g_pucDpRx0LEBound[2] > 15)) ||
              ((g_pucDpRx0LEMax[3] > 15) && (g_pucDpRx0Tap1Max[3] < 4) && (g_pucDpRx0LEBound[3] > 15)))
        {
            if(g_pucDpRx0Tap1Max[0] < 4)
            {
                g_pucDpRx0LEBound[0]--;
                ScalerSetBit_EXINT(P1D_A2_L0_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit_EXINT(P1D_A3_L0_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[0] & _BIT4) << 3));
            }

            if(g_pucDpRx0Tap1Max[1] < 4)
            {
                g_pucDpRx0LEBound[1]--;
                ScalerSetBit_EXINT(P1D_B2_L1_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[1] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit_EXINT(P1D_B3_L1_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[1] & _BIT4) << 3));
            }

            if(g_pucDpRx0Tap1Max[2] < 4)
            {
                g_pucDpRx0LEBound[2]--;
                ScalerSetBit_EXINT(P1D_C2_L2_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[2] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit_EXINT(P1D_C3_L2_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[2] & _BIT4) << 3));
            }

            if(g_pucDpRx0Tap1Max[3] < 4)
            {
                g_pucDpRx0LEBound[3]--;
                ScalerSetBit_EXINT(P1D_D2_L3_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx0LEBound[3] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit_EXINT(P1D_D3_L3_INIT_1, ~_BIT7, ((g_pucDpRx0LEBound[3] & _BIT4) << 3));
            }

            // Start to Record Tap0 Max/Min
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~_BIT0, _BIT0);

            // Delay Time us [85,x] Waiting for DFE Adaptation
            DELAY_XUS_EXINT(85);

            // Stop To Record Tap0 Max/Min
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~_BIT0, 0x00);

            // Select to Lane0
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

            // Read Back LE Max
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[0] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[0] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

            // Select to Lane1
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

            // Read Back LE Max
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[1] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[1] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

            // Select to Lane2
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

            // Read Back LE Max
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[2] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[2] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

            // Select to Lane3
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Read Back LE Max
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx0LEMax[3] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx0Tap1Max[3] = (ScalerGetByte_EXINT(P1D_F3_COEF_4) & 0x1F);
        }

        // Disable DFE Adapt
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x00);

        // [1] reg_eqen_manual = 1'b0 --> Disable Adaptation
        ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT1, 0x00);

        // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
        ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~_BIT4, _BIT4);

        // Read Back Tap0
        ScalerSetByte_EXINT(P1D_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, 0x15);
            ScalerSetBit_EXINT(P1D_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P1D_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit_EXINT(P1D_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P1D_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte_EXINT(P1D_B4_L1_INIT_2, 0x15);
            ScalerSetBit_EXINT(P1D_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P1D_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P1D_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit_EXINT(P1D_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P1D_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte_EXINT(P1D_C4_L2_INIT_2, 0x15);
            ScalerSetBit_EXINT(P1D_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P1D_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P1D_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit_EXINT(P1D_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P1D_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte_EXINT(P1D_D4_L3_INIT_2, 0x15);
            ScalerSetBit_EXINT(P1D_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P1D_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P1D_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit_EXINT(P1D_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P1D_DA_L3_INIT_8, ~_BIT0, 0x00);
        }


        //////////////
        // K Offset //
        //////////////

        // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
        ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT5, _BIT5);

        // [6] en_fore_offset --> Toggle Foreground Calibration
        ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);
        ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, 0x00);
        ScalerSetBit_EXINT(P1D_24_KOFFSET_00, ~_BIT6, _BIT6);

        // Delay Time us [85,x] Waiting for K Offset
        DELAY_XUS_EXINT(85);
    }
    else
    {
        // [2] reg_rstb_fsm = 1'b0 --> FLD Reset
        ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~_BIT2, 0x00);

        // [1] reg_eqen_manual = 1'b1 --> Enable Adaptation
        ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT1, _BIT1);

        // Enable LE/Vth/Tap0/Tap1/Tap2
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0xC7);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit_EXINT(P1D_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [300,x] Waiting for DFE Adaptation
        DELAY_XUS_EXINT(300);

        // Disable Adaptation
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x00);
    }

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    // [6] reg_adp_en_manual = 1'b1 --> Enable CDR Clock
    // [5] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit_EXINT(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [5] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit_EXINT(P1D_2C_ANA_CDR_01, ~_BIT5, _BIT5);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US_EXINT();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit_EXINT(P1D_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US_EXINT();

    if(ucDpLinkRate <= _DP_LINK_HBR)
    {
        // Set Vth Min = 0
        ScalerSetBit_EXINT(P1D_F9_LIMIT_10, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Vth/Tap0 Adaptation
        ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x41);
    }

    // [3] reg_en_data_manual_l0 = 1'b1 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1D_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    g_pusDpRx0ClockCount[0] = 0;
    g_pusDpRx0ClockCount[1] = 0;
    g_pusDpRx0ClockCount[2] = 0;
    g_pusDpRx0ClockCount[3] = 0;

    // [5] ln_ck_sel = 1'b1 -> DP CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit_EXINT(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 30; g_ucDpRx0Temp++)
    {
        DELAY_5US_EXINT();

        if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            break;
        }
    }

    if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        g_pusDpRx0ClockCount[0] = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));
    }
    else
    {
        switch(ucDpLinkRate)
        {
            case _DP_LINK_HBR2:

                g_pusDpRx0ClockCount[0] = 0x2710;

                break;

            case _DP_LINK_HBR:

                g_pusDpRx0ClockCount[0] = 0x1388;

                break;

            default:
            case _DP_LINK_RBR:

                g_pusDpRx0ClockCount[0] = 0xBB8;

                break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
}
#endif

#endif // End of #if(_D0_DP_EXIST == _ON)
