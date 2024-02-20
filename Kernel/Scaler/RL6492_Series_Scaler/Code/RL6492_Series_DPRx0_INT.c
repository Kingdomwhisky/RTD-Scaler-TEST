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
// ID Code      : RL6492_Series_DPRx0_INT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_DPRX0_INT__

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
#if(_USB3_RETIMER_SUPPORT == _ON)
// void ScalerDpRx0PhyInitial_EXINT0(void);
#endif
void ScalerDpRx0Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx0Tp1SetPhy4Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
WORD ScalerDpRx0SignalDetectMeasureCount_EXINT0(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
void ScalerDpRx0Tp1SetPhyUnFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx0Tp1SetPhyFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
#endif

void ScalerDpRx0Tp2SetPhy_EXINT0(void);
void ScalerDpRx0Tp2SetPhy4Lane_EXINT0(void);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
void ScalerDpRx0Tp2SetPhyUnFlip2Lane_EXINT0(void);
void ScalerDpRx0Tp2SetPhyFlip2Lane_EXINT0(void);
#endif

void ScalerDpRx0AdjustLaneFLDBand_EXINT0(BYTE ucDpRx0LaneNumber);
void ScalerDpRx0SetDFEInitial_EXINT0(EnumDpLinkRate enumDpLinkRate);
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
void ScalerDpRx0SetDFEInitialUnFlip2Lane_EXINT0(EnumDpLinkRate enumDpLinkRate);
void ScalerDpRx0SetDFEInitialFlip2Lane_EXINT0(EnumDpLinkRate enumDpLinkRate);
#endif
BYTE ScalerDpRx0DFECheck_EXINT0(void);
BYTE ScalerDpRx0SignalCheck_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx0RebuildPhy_WDINT(BYTE ucDpLinkRate, BYTE ucDpcdLane);
void ScalerDpRx0RebuildPhy4Lane_WDINT(BYTE ucDpLinkRate);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
void ScalerDpRx0RebuildPhyUnFlip2Lane_WDINT(BYTE ucDpLinkRate);
void ScalerDpRx0RebuildPhyFlip2Lane_WDINT(BYTE ucDpLinkRate);
#endif

#endif

BYTE ScalerDpRx0GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
BYTE ScalerDpRx0GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
void ScalerDpRx0SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
void ScalerDpRx0SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
void ScalerDpRx0SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
BYTE ScalerDpRx0TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType);
BYTE ScalerDpRx0TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType);
void ScalerDpRx0TrainingPatternEnd_EXINT0(void);
BYTE ScalerDpRx0CheckSourceOUI_EXINT0(EnumDpRxCheckSourceOUI enumDpRx0CheckSourceOUI);

#if(_WD_TIMER_INT_SUPPORT == _ON)
BYTE ScalerDpRx0GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
BYTE ScalerDpRx0GetDpcdBitInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
#endif
#endif

BYTE ScalerDpRx0Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
BYTE ScalerDpRx0Tp1SignalDetectCheck_EXINT0(BYTE ucDpLaneSel);
BYTE ScalerDpRx0Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
void ScalerDpRx0SetDpAltModeLaneMapping_EXINT0(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation);
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
#if(_D1_DP_EXIST == _ON)
    // _ERROR_PRONE_CODE
    // Switch to Rx0 if PS Wake up
    if((ScalerGetByte_EXINT(PBA_7A_AUX_DIG_PHYA) & 0x11) == 0x11)
    {
        return;
    }

    // Aux Firmware Control -> Reply Defer
    SET_DP_RX1_AUX_MANUAL_MODE_EXINT();
#endif

    // Aux Firmware Control -> Reply Defer
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
            if((ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0) &&
               ((ScalerDpRx0DFECheck_EXINT0() == _FALSE) && (ScalerDpRx0SignalCheck_EXINT0() == _FALSE)))
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
            }
        }

        if(ScalerGetBit_EXINT(PB7_DA_AUX_FIFO_RST, (_BIT2 | _BIT1)) == (_BIT2 | _BIT1)) // Write 68xxxh into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PB7_DA_AUX_FIFO_RST, ~_BIT1, _BIT1);

            // Clear Integrity Failure Flag
            ScalerSetBit_EXINT(PB_1B_HDCP_INTGT_VRF, ~_BIT1, _BIT1);

            if(GET_DP_RX0_FAKE_LINK_TRAINING() == _TRUE)
            {
                // DP Mac Clock Select to Xtal Clock
                ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);
            }
        }

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
        // DPCD 68028h Into INT
        if(ScalerGetBit_EXINT(PB7_FB_DUMMY_1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear Flag
            ScalerSetBit_EXINT(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);

            ScalerDpRx0HdcpHandshakeMonitorDisable_EXINT0();

            // Check if source doing HDCP handshake while HDCP capability disable
            if(ScalerDpRx0GetDpcdBitInfo_EXINT0(0x06, 0x80, 0x28, _BIT0) == 0x00)
            {
                SET_DP_RX0_HDCP_HANDSHAKE_WO_CAP();
            }
        }
#endif
        // Detect if Aksv(0x6800B) is Written by Source
        if(ScalerGetBit_EXINT(PB7_A5_AUX_RESERVE5, (_BIT6 | _BIT2)) == (_BIT6 | _BIT2))
        {
            // Clear Flag
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

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
            ScalerDpRx0HdcpHandshakeMonitorDisable_EXINT0();

            // Check if source doing HDCP handshake while HDCP capability disable
            if(ScalerDpRx0GetDpcdBitInfo_EXINT0(0x06, 0x80, 0x28, _BIT0) == 0x00)
            {
                SET_DP_RX0_HDCP_HANDSHAKE_WO_CAP();
            }
#endif
        }

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_HDCP_ARBITER_SUPPORT == _ON))
        // DPCD 6921Xh Into INT
        if(ScalerGetBit_EXINT(PB7_FB_DUMMY_1, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
        {
            // Clear Flag
            ScalerSetBit_EXINT(PB7_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT3);

            ScalerDpRx0HdcpHandshakeMonitorDisable_EXINT0();

            // Check if source doing HDCP handshake while HDCP capability disable
            if(ScalerDpRx0GetDpcdBitInfo_EXINT0(0x06, 0x92, 0x1F, _BIT1) == 0x00)
            {
                SET_DP_RX0_HDCP_HANDSHAKE_WO_CAP();
            }
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

#if(_AUDIO_SUPPORT == _ON)
        // Detect if Auido Sampling is Changed
        if(ScalerGetBit_EXINT(PB6_50_AUD_FREQUENY_DET_0, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
        {
            // Clear Auido Sampling Change Flag
            ScalerSetBit_EXINT(PB6_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);

#if(_LINE_IN_SUPPORT == _ON)
            if(ScalerAudioGetInputSource_EXINT0() == _DIGITAL_AUDIO)
#endif
            {
                // Disable Boundary Tracking Method
                ScalerSetBit_EXINT(PB6_81_AUD_BDRY_0, ~_BIT7, 0x00);

                // Disable Trend Tracking Method
                ScalerSetBit_EXINT(PB6_92_AUD_TRND_0, ~_BIT7, 0x00);

                // Reload D code
                ScalerSetBit_EXINT(PB6_7C_AUD_FSM_CTRL_1, ~_BIT7, _BIT7);
            }
        }
#endif
    }

    ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, g_pucDpRx0Backup[0]);
    ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, g_pucDpRx0Backup[1]);
    ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, g_pucDpRx0Backup[2]);
}

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Phy Initial Setting in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
/*
void ScalerDpRx0PhyInitial_EXINT0(void) using 1
{
    //////////////////
    // Misc Setting //
    //////////////////

    // [3:0] Enable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));


    /////////////////
    // DFE Initial //
    /////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    ScalerSetBit_EXINT(P17_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P17_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P17_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P17_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    // [7:6] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetByte_EXINT(P17_E0_MODE_TIMER, 0xB2);

    // Set DFE Delay Time
    ScalerSetByte_EXINT(P17_E1_TIMER, 0x01);

    // Tap0,Tap1 Loop Gain 1/512
    ScalerSetBit_EXINT(P17_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap2,Tap3 Loop Gain 1/512
    ScalerSetBit_EXINT(P17_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4,Servo Loop Gain 1/512
    ScalerSetBit_EXINT(P17_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // LE Gain1 Loop Gain 1/256, LE Gain2 Loop Gain 0, LE Pre-Courser Gain 0
    ScalerSetBit_EXINT(P17_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit_EXINT(P17_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap0 Max is 27
    ScalerSetByte_EXINT(P17_E6_LIMIT_1, 0x3B);

    // Tap1 Min is -10
    ScalerSetByte_EXINT(P17_E7_LIMIT_2, 0x0A);

    // Tap2 Max is 6, Min is -6
    ScalerSetBit_EXINT(P17_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(P17_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P17_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 3, Min is -3
    ScalerSetBit_EXINT(P17_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit_EXINT(P17_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 3, Min is -3
    ScalerSetBit_EXINT(P17_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P17_EB_LIMIT_6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit_EXINT(P17_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Tap0 Threshold = 10
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetByte_EXINT(P17_EC_LOOP_DIV_1, 0xA3);

    // [1] tap1_trans = 1'b1 --> Tap1 is Effective on Transition bit
    // [0] tap0_trans = 1'b0 --> Tap0 is Effective every Bits
    ScalerSetBit_EXINT(P17_E3_GAIN_2, ~(_BIT1 | _BIT0), _BIT1);

    // [5] servo_notrans = 1'b0 --> Servo is Effective on Every Bits
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT5, 0x00);

    // [1:0] trans_rlength = 2'b00 --> Tap0 Run Length = 2
    ScalerSetBit_EXINT(P17_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);

    // Set Vth Max = 63, Min = 12
    ScalerSetByte_EXINT(P17_F9_LIMIT_10, 0xF3);


    ////////////////
    // EQ Setting //
    ////////////////

    // reg_tap_en : DFE TAP Enable
    ScalerSetBit_EXINT(P1A_16_COMBO_RX_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1A_17_COMBO_RX_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [6:4] reg_fld_adp_time = 0.64*(6+1) us
    ScalerSetBit_EXINT(P1C_57_DP_FLD_9, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));


    /////////////////
    // CDR Setting //
    /////////////////

    // [7] en_wide_temp = 1 --> Vcp-Vcn = -0.1V
    ScalerSetBit_EXINT(P1A_04_COMBO_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] reg_en_vco_lpf = 4'b0000 --> Analog CDR Multi Band VCO's LPF Always Off
    ScalerSetBit_EXINT(P1A_2A_DP_RX_10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [1:0] reg_vcm_ctrl_rx_l0_l2 = 2'b00  --> vdd - 0.2V
    ScalerSetBit_EXINT(P1A_2C_DP_RX_12, ~(_BIT1 | _BIT0), 0x00);

    // reg_timer_en = 1 for CDR_RDY
    ScalerSetBit_EXINT(P1C_4B_READY_TIMER_0, ~_BIT0, _BIT0);

    // reg_fld_cp_adj_en = 4'b1111 Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(P1C_55_DP_FLD_7, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // reg_cdr_div_delta for FLD Lock Band Setting
    ScalerSetByte_EXINT(P1C_6D_DP_FLD_31, 0x01);
    ScalerSetByte_EXINT(P1C_6E_DP_FLD_32, 0x01);
    ScalerSetByte_EXINT(P1C_6F_DP_FLD_33, 0x01);
    ScalerSetByte_EXINT(P1C_70_DP_FLD_34, 0x01);


    ////////////////////
    // Offset Setting //
    ////////////////////

    // reg_offk_dellay = 4*Clock Period for Accuracy
    ScalerSetBit_EXINT(P1C_27_FORE_OFFSET_K_1, ~(_BIT6 | _BIT5), _BIT5);
    ScalerSetBit_EXINT(P1C_2F_FORE_OFFSET_K_9, ~(_BIT6 | _BIT5), _BIT5);
    ScalerSetBit_EXINT(P1C_37_FORE_OFFSET_K_17, ~(_BIT6 | _BIT5), _BIT5);
    ScalerSetBit_EXINT(P1C_3F_FORE_OFFSET_K_25, ~(_BIT6 | _BIT5), _BIT5);

    // reg_sel_forek = LEQ for Detecting Calibration Done
    ScalerSetBit_EXINT(P1C_28_FORE_OFFSET_K_2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P1C_30_FORE_OFFSET_K_10, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P1C_38_FORE_OFFSET_K_18, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P1C_40_FORE_OFFSET_K_26, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
}
*/
#endif

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef) using 1
{
    // [4] Disable Comma Detection
    ScalerSetBit_EXINT(PB_05_SAMPLE_EDGE, ~_BIT4, _BIT4);

    // [5] Disable De-Scrambling
    ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    // [2] Disable Enhancement Control Mode
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

    // Main-Link Lane Setting Start
    if(ScalerTypeCRx0PdGetPinAssignment_EXINT0() != _TYPE_C_PIN_ASSIGNMENT_E)
    {
        // Pin Assignment C/D PN Swap
        ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT7, _D0_DP_PCB_LANE3_PN_SWAP << 7);
        ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT6, _D0_DP_PCB_LANE2_PN_SWAP << 6);
        ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT5, _D0_DP_PCB_LANE1_PN_SWAP << 5);
        ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT4, _D0_DP_PCB_LANE0_PN_SWAP << 4);
    }
    else
    {
        // Pin Assignment E PN Swap
        ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT7, (!_D0_DP_PCB_LANE3_PN_SWAP) << 7);
        ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT6, (!_D0_DP_PCB_LANE2_PN_SWAP) << 6);
        ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT5, (!_D0_DP_PCB_LANE1_PN_SWAP) << 5);
        ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT4, (!_D0_DP_PCB_LANE0_PN_SWAP) << 4);
    }

    SET_DP_RX0_PCB_LANE0_PN_SWAP(ScalerGetBit_EXINT(PB_06_DECODE_10B8B_ERROR, _BIT7) >> 7);
    SET_DP_RX0_PCB_LANE1_PN_SWAP(ScalerGetBit_EXINT(PB_06_DECODE_10B8B_ERROR, _BIT6) >> 6);
    SET_DP_RX0_PCB_LANE2_PN_SWAP(ScalerGetBit_EXINT(PB_06_DECODE_10B8B_ERROR, _BIT5) >> 5);
    SET_DP_RX0_PCB_LANE3_PN_SWAP(ScalerGetBit_EXINT(PB_06_DECODE_10B8B_ERROR, _BIT4) >> 4);

    switch(ScalerTypeCRx0PdGetPinAssignment_EXINT0())
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE1_MAPPING << 6);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE0_MAPPING << 4);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE2_MAPPING << 2);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);

                // [1:0] DP Mac Clock Selection
                ScalerSetBit_EXINT(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE0_MAPPING << 2);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);

                // [1:0] DP Mac Clock Selection
                ScalerSetBit_EXINT(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);
            }

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            ScalerDpRx0Tp1SetPhy4Lane_EXINT0(enumDpNFCodeRef);

            break;

        case _TYPE_C_PIN_ASSIGNMENT_D:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE1_MAPPING << 6);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE0_MAPPING << 4);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE2_MAPPING << 2);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);

                SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
                SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
                SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
                SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

                // [1:0] DP Mac Clock Selection
                ScalerSetBit_EXINT(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE3_MAPPING);

                ScalerDpRx0Tp1SetPhyUnFlip2Lane_EXINT0(enumDpNFCodeRef);
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE0_MAPPING << 2);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);

                SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
                SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
                SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
                SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

                // [1:0] DP Mac Clock Selection
                ScalerSetBit_EXINT(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE1_MAPPING);

                ScalerDpRx0Tp1SetPhyFlip2Lane_EXINT0(enumDpNFCodeRef);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_E:

            if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // DP Lane Swap Setting
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE2_MAPPING << 6);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE3_MAPPING << 4);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE1_MAPPING << 2);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);

                // [1:0] DP Mac Clock Selection
                ScalerSetBit_EXINT(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);
            }
            else
            {
                // DP Lane Swap Setting
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE0_MAPPING << 6);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE1_MAPPING << 4);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE3_MAPPING << 2);
                ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE2_MAPPING);

                // [1:0] DP Mac Clock Selection
                ScalerSetBit_EXINT(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE2_MAPPING);
            }

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            ScalerDpRx0Tp1SetPhy4Lane_EXINT0(enumDpNFCodeRef);

            break;

        default:
        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            // DP Lane Swap Setting
            ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_PCB_LANE3_MAPPING << 6);
            ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_PCB_LANE2_MAPPING << 4);
            ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_PCB_LANE1_MAPPING << 2);
            ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);

            SET_DP_RX0_PCB_LANE3_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6);
            SET_DP_RX0_PCB_LANE2_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4);
            SET_DP_RX0_PCB_LANE1_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2);
            SET_DP_RX0_PCB_LANE0_MAPPING(ScalerGetBit_EXINT(PB_03_LANE_MUX, (_BIT1 | _BIT0)));

            // [1:0] DP Mac Clock Selection
            ScalerSetBit_EXINT(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);

            ScalerDpRx0Tp1SetPhy4Lane_EXINT0(enumDpNFCodeRef);

            break;
    }

#else

    // DP Lane Swap Setting
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT7 | _BIT6), _D0_DP_LANE3 << 6);
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT5 | _BIT4), _D0_DP_LANE2 << 4);
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT3 | _BIT2), _D0_DP_LANE1 << 2);
    ScalerSetBit_EXINT(PB_03_LANE_MUX, ~(_BIT1 | _BIT0), _D0_DP_LANE0);

    // DP Lane PN Swap Setting
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT7, GET_DP_RX0_PCB_LANE3_PN_SWAP() << 7);
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT6, GET_DP_RX0_PCB_LANE2_PN_SWAP() << 6);
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT5, GET_DP_RX0_PCB_LANE1_PN_SWAP() << 5);
    ScalerSetBit_EXINT(PB_06_DECODE_10B8B_ERROR, ~_BIT4, GET_DP_RX0_PCB_LANE0_PN_SWAP() << 4);

    // [1:0] DP Mac Clock Selection
    ScalerSetBit_EXINT(PB_96_DUMMY3, ~(_BIT1 | _BIT0), _D0_DP_PCB_LANE0_MAPPING);

    ScalerDpRx0Tp1SetPhy4Lane_EXINT0(enumDpNFCodeRef);

#endif
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp1SetPhy4Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef) using 1
{
    BYTE ucIcp = 0;

    // LDO_en for Lane1,3
    ScalerSetBit_EXINT(P1A_30_COMBO_USB_00, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));

    // Enable Lane1,3 1.1V LDO Tracking
    ScalerSetBit_EXINT(P1A_30_COMBO_USB_00, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

    // [7:4] LANE_EN = 4'b0000 --> Disable LANE_EN
    // [3:0] CDR_EN = 4'b0000 --> Disable CDR_EN
    ScalerSetByte_EXINT(P1A_22_DP_RX_02, 0x00);

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT2, _BIT2);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT3, _BIT3);
            }

            // [4:3] DP Mac Select One Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT2, _BIT2);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT3, _BIT3);
            }

            if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT2, _BIT2);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT3, _BIT3);
            }

            // [4:3] DP Mac Select Two Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        default:
        case _DP_FOUR_LANE:

            // [7:4] Enable Lane0~3 Rx_en
            ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // [3:0] Enable Lane0~3 CDR_en
            ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // [4:3] DP Mac Select Four Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetByte_EXINT(P1C_4C_READY_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte_EXINT(P1C_4D_READY_TIMER_2, 0x0F);

    // [4:2] reg_vcm_ctrl_op_l1 = 3'b101 --> 600mV
    ScalerSetBit_EXINT(P1A_2C_DP_RX_12, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [4:2] reg_vcm_ctrl_op_l3 = 3'b101 --> 600mV
    ScalerSetBit_EXINT(P1A_25_DP_RX_05, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [3:0] Disable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpRx0SetDFEInitial_EXINT0(g_ucDpRx0LinkRate);

    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective on Every Bits
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_HBR2:

            // [7:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 900M/v in Each Lane
            ScalerSetByte_EXINT(P1A_03_COMBO_03, 0x55);

            // [7:4] en_half_pf = 1 --> Half Rate PD for High Speed
            ScalerSetBit_EXINT(P1A_04_COMBO_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // [6:4][2:0] sel_cont3 = 3'b010 --> BBPD UP/DN Sync
            ScalerSetBit_EXINT(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // [4][0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit_EXINT(P1A_12_COMBO_RX_02, ~(_BIT4 | _BIT0), 0x00);

            // [7:5][3:1] LE_lowgain_highboost = 3'b110
            // [4][0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetByte_EXINT(P1A_14_COMBO_RX_04, 0xCC);

            // [7:6] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit_EXINT(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), 0x00);

            // [1:0] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit_EXINT(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit_EXINT(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit_EXINT(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_sel_cdr_res = 2K
            ScalerSetBit_EXINT(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Initial Band
            ScalerSetByte_EXINT(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte_EXINT(P1C_52_DP_FLD_4, 0x50);
            ScalerSetByte_EXINT(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte_EXINT(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 13.5uA in Each Lane
            ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xCC);
            ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xCC);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:0] reg_fld_xtal_en = 4'b1111 --> Using 27M Xtal
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (50/500 = 2*(27M/540M))
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0x31);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0x31);
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0x31);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0x31);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0xF4);
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0xF4);
            }
            else
            {
                // [3:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0xF3);
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0xF4);
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;

        case _DP_LINK_HBR:

            // [7:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetByte_EXINT(P1A_03_COMBO_03, 0x00);

            // [7:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit_EXINT(P1A_04_COMBO_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [6:4][2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit_EXINT(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // [4][0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit_EXINT(P1A_12_COMBO_RX_02, ~(_BIT4 | _BIT0), 0x00);

            // [7:5][3:1] LE_lowgain_highboost = 3'b100
            // [4][0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetByte_EXINT(P1A_14_COMBO_RX_04, 0x88);

            // [7:6] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit_EXINT(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT6);

            // [1:0] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit_EXINT(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit_EXINT(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit_EXINT(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 8K
            ScalerSetBit_EXINT(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Initial Band
            ScalerSetByte_EXINT(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte_EXINT(P1C_52_DP_FLD_4, 0x50);
            ScalerSetByte_EXINT(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte_EXINT(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 16.5uA in Each Lane
            ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xDD);
            ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xDD);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:0] reg_fld_xtal_en = 4'b1111 --> Using 27M Xtal
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (100/500 = 2*(27M/270M))
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0x63);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0x63);
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0x63);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0x63);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0xF4);
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0xF4);
            }
            else
            {
                // [3:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)); // ref_div_cnt set MSB=1
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0xF3);
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0xF4);
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;

        default:
        case _DP_LINK_RBR:

            // [7:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetByte_EXINT(P1A_03_COMBO_03, 0x00);

            // [7:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit_EXINT(P1A_04_COMBO_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [6:4][2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit_EXINT(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // [4][0] highboost_for_rbr = 1 --> only in rbr
            ScalerSetBit_EXINT(P1A_12_COMBO_RX_02, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

            // [7:5][3:1] LE_lowgain_highboost = 3'b000
            // [4][0] sel_dyn_std = 1 --> Std DFF
            ScalerSetByte_EXINT(P1A_14_COMBO_RX_04, 0x11);

            // [7:6] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit_EXINT(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT7);

            // [1:0] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit_EXINT(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT1);

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit_EXINT(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit_EXINT(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 6K
            ScalerSetBit_EXINT(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Initial Band
            ScalerSetByte_EXINT(P1C_51_DP_FLD_3, 0x70);
            ScalerSetByte_EXINT(P1C_52_DP_FLD_4, 0x70);
            ScalerSetByte_EXINT(P1C_53_DP_FLD_5, 0x70);
            ScalerSetByte_EXINT(P1C_54_DP_FLD_6, 0x70);

            // reg_fld_cdr_cp Icp = 19.5uA in Each Lane
            ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xEE);
            ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xEE);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:0] reg_fld_xtal_en = 4'b1111 --> Using 27M Xtal
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (50/150 = 2*(27M/162M))
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0x31);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0x31);
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0x31);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0x31);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0x96);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0x96);
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0x96);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0x96);
            }
            else
            {
                // [3:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0xF3);
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0xF4);
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;
    }

    // Backup Icp for CDR lock
    ucIcp = ScalerGetByte_EXINT(P1C_5D_DP_FLD_15);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P1C_2E_FORE_OFFSET_K_8, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_36_FORE_OFFSET_K_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_3E_FORE_OFFSET_K_24, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_46_FORE_OFFSET_K_32, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    //////////////
    // FLD Band //
    //////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetByte_EXINT(P1C_50_DP_FLD_2, 0xFF);
    ScalerSetByte_EXINT(P1C_50_DP_FLD_2, 0x0F);

    // [3:0] reg_fld_en = 4'b0000 --> Disable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Enable Vth/Tap0
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x41);

    // [3:0] reg_fld_en = 4'b1111 --> Enable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_RBR:

            // Delay Time us [170,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(170);

            break;

        case _DP_LINK_HBR:

            // Delay Time us [130,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(130);

            break;

        default:
        case _DP_LINK_HBR2:

            // Delay Time us [65,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(65);

            break;
    }

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x00);

    // Enable Foreground Offset Calibration lane
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    // Scan Auto FLD
    ScalerSetByte_EXINT(P1C_59_DP_FLD_11, ScalerGetByte_EXINT(P1C_75_DP_FLD_39));
    ScalerSetByte_EXINT(P1C_5A_DP_FLD_12, ScalerGetByte_EXINT(P1C_76_DP_FLD_40));
    ScalerSetByte_EXINT(P1C_5B_DP_FLD_13, ScalerGetByte_EXINT(P1C_77_DP_FLD_41));
    ScalerSetByte_EXINT(P1C_5C_DP_FLD_14, ScalerGetByte_EXINT(P1C_78_DP_FLD_42));

    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock for Signal Detection
    ScalerSetBit_EXINT(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_fld_cp_en_manual = 4'b0000 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetByte_EXINT(P1C_50_DP_FLD_2, 0x00);

    // [3:0] Enable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xFF);
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xFF);

    // [3:0] reg_fld_cp_en_manual = 4'b1111 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, ucIcp);
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ////////////////////////
    // FLD Target Measure //
    ////////////////////////

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            g_pusDpRx0ClockCount[_D0_DP_LANE0] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);

            // Measure Count x 4 for Default ref. Counter = 1000
            g_pusDpRx0ClockCount[_D0_DP_LANE0] = (g_pusDpRx0ClockCount[_D0_DP_LANE0] << 2);

            break;

        case _DP_TWO_LANE:

            g_pusDpRx0ClockCount[_D0_DP_LANE0] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);
            g_pusDpRx0ClockCount[_D0_DP_LANE1] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);

            // Measure Count x 4 for Default ref. Counter = 1000
            g_pusDpRx0ClockCount[_D0_DP_LANE0] = (g_pusDpRx0ClockCount[_D0_DP_LANE0] << 2);
            g_pusDpRx0ClockCount[_D0_DP_LANE1] = (g_pusDpRx0ClockCount[_D0_DP_LANE1] << 2);

            break;

        case _DP_FOUR_LANE:
        default:

            g_pusDpRx0ClockCount[_D0_DP_LANE0] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);
            g_pusDpRx0ClockCount[_D0_DP_LANE1] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);
            g_pusDpRx0ClockCount[_D0_DP_LANE2] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE2, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);
            g_pusDpRx0ClockCount[_D0_DP_LANE3] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE3, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);

            // Measure Count x 4 for Default ref. Counter = 1000
            g_pusDpRx0ClockCount[_D0_DP_LANE0] = (g_pusDpRx0ClockCount[_D0_DP_LANE0] << 2);
            g_pusDpRx0ClockCount[_D0_DP_LANE1] = (g_pusDpRx0ClockCount[_D0_DP_LANE1] << 2);
            g_pusDpRx0ClockCount[_D0_DP_LANE2] = (g_pusDpRx0ClockCount[_D0_DP_LANE2] << 2);
            g_pusDpRx0ClockCount[_D0_DP_LANE3] = (g_pusDpRx0ClockCount[_D0_DP_LANE3] << 2);

            break;
    }
}

//--------------------------------------------------
// Description : DP Signal Detection Measure
// Input Value  : DP Lane Select, Measure target, Measure Period
// Output Value : Measure Counter
//--------------------------------------------------
WORD ScalerDpRx0SignalDetectMeasureCount_EXINT0(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod) using 1
{
    WORD usDpMeasureCount = 0;

    // [1:0] freqdet_lane_sel
    ScalerSetBit_EXINT(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ucDpLaneSel & (_BIT1 | _BIT0)));

    // [5] ln_ck_sel
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT5, enumDpMeasureTarget);

    switch(enumDpMeasurePeriod)
    {
#if(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_1)
        case _DP_MEASURE_PERIOD_250_CYCLE:

            // [4:0] DP_XTAL_CYCLE = 5'b00001
            ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            break;
#endif

        case _DP_MEASURE_PERIOD_1000_CYCLE:

#if(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_1)
            // [4:0] DP_XTAL_CYCLE = 5'b00011
            ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
#elif(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_2)
            // [0] DP_XTAL_CYCLE = 1'b0
            ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT0, 0x00);
#endif
            break;

        case _DP_MEASURE_PERIOD_2000_CYCLE:
        default:

#if(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_1)
            // [4:0] DP_XTAL_CYCLE = 5'b00100
            ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
#elif(_HW_SIGNAL_MEASURE_GEN_TYPE == _SIGNAL_MEASURE_GEN_2)
            // [0] DP_XTAL_CYCLE = 1'b1
            ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT0, _BIT0);
#endif
            break;
    }

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
            usDpMeasureCount = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

            break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    return usDpMeasureCount;
}

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp1SetPhyUnFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef) using 1
{
    BYTE ucIcp = 0;

    // LDO_en for Lane3
    ScalerSetBit_EXINT(P1A_30_COMBO_USB_00, ~_BIT5, _BIT5);

    // Enable Lane3 1.1V LDO Tracking
    ScalerSetBit_EXINT(P1A_30_COMBO_USB_00, ~_BIT4, _BIT4);

    // [7:6] LANE_EN = 2'b00 --> Disable LANE_EN
    // [3:2] CDR_EN = 2'b00 --> Disable CDR_EN
    ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT2, _BIT2);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT3, _BIT3);
            }

            // [4:3] DP Mac Select One Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        default:
        case _DP_TWO_LANE:

            // [7:6] Enable Lane2/3 LANE_EN
            ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // [3:2] Enable Lane2~3 CDR_EN
            ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2), _BIT2);
            ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // [4:3] DP Mac Select Two Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:6] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:2] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit_EXINT(P1C_4C_READY_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7:6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [4:2] reg_vcm_ctrl_op_l3 = 3'b101 --> 600mV
    ScalerSetBit_EXINT(P1A_25_DP_RX_05, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [3:0] Disable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpRx0SetDFEInitialUnFlip2Lane_EXINT0(g_ucDpRx0LinkRate);

    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective on Every Bits
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_HBR2:

            // [7:4] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 900M/v in Each Lane
            ScalerSetBit_EXINT(P1A_03_COMBO_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

            // [7:6] en_half_pf = 1 --> Half Rate PD for High Speed
            ScalerSetBit_EXINT(P1A_04_COMBO_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // [6:4] sel_cont3 = 3'b010 --> BBPD UP/DN Sync
            ScalerSetBit_EXINT(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

            // [4] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit_EXINT(P1A_12_COMBO_RX_02, ~_BIT4, 0x00);

            // [7:5] LE_lowgain_highboost = 3'b110
            // [4] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit_EXINT(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

            // [1:0] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit_EXINT(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit_EXINT(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_sel_cdr_res = 2K
            ScalerSetBit_EXINT(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Initial Band
            ScalerSetByte_EXINT(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte_EXINT(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 13.5uA in Each Lane
            ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xCC);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:2] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Analog CDR Auto FLD Counter (50/500 = 2*(27M/540M))
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), 0x00);
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0x31);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0x31);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0xF4);
            }
            else
            {
                // [3:2] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;

        case _DP_LINK_HBR:

            // [7:4] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit_EXINT(P1A_03_COMBO_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [7:6] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit_EXINT(P1A_04_COMBO_04, ~(_BIT7 | _BIT6), 0x00);

            // [6:4] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit_EXINT(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

            // [4] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit_EXINT(P1A_12_COMBO_RX_02, ~_BIT4, 0x00);

            // [7:5] LE_lowgain_highboost = 3'b100
            // [4] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit_EXINT(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

            // [1:0] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit_EXINT(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit_EXINT(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 8K
            ScalerSetBit_EXINT(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Initial Band
            ScalerSetByte_EXINT(P1C_53_DP_FLD_5, 0x50);
            ScalerSetByte_EXINT(P1C_54_DP_FLD_6, 0x50);

            // reg_fld_cdr_cp Icp = 16.5uA in Each Lane
            ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xDD);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:2] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Analog CDR Auto FLD Counter (100/500 = 2*(27M/270M))
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), 0x00);
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0x63);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0x63);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0xF4);
            }
            else
            {
                // [3:2] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;

        default:
        case _DP_LINK_RBR:

            // [7:4] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit_EXINT(P1A_03_COMBO_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // [7:6] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit_EXINT(P1A_04_COMBO_04, ~(_BIT7 | _BIT6), 0x00);

            // [6:4] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit_EXINT(P1A_10_COMBO_RX_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

            // [4] highboost_for_rbr = 1 --> only in rbr
            ScalerSetBit_EXINT(P1A_12_COMBO_RX_02, ~_BIT4, _BIT4);

            // [7:5] LE_lowgain_highboost = 3'b000
            // [4] sel_dyn_std = 1 --> Std DFF
            ScalerSetBit_EXINT(P1A_14_COMBO_RX_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

            // [1:0] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit_EXINT(P1A_25_DP_RX_05, ~(_BIT1 | _BIT0), _BIT1);

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit_EXINT(P1A_26_DP_RX_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 6K
            ScalerSetBit_EXINT(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Initial Band
            ScalerSetByte_EXINT(P1C_53_DP_FLD_5, 0x70);
            ScalerSetByte_EXINT(P1C_54_DP_FLD_6, 0x70);

            // reg_fld_cdr_cp Icp = 19.5uA in Each Lane
            ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xEE);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [3:2] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Analog CDR Auto FLD Counter (50/150 = 2*(27M/162M))
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), 0x00);
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0x31);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0x31);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), 0x00);
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0x96);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0x96);
            }
            else
            {
                // [3:2] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT3 | _BIT2), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte_EXINT(P1C_65_DP_FLD_23, 0xF3);
                ScalerSetByte_EXINT(P1C_66_DP_FLD_24, 0xF3);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
                ScalerSetByte_EXINT(P1C_6A_DP_FLD_28, 0xF4);
                ScalerSetByte_EXINT(P1C_6B_DP_FLD_29, 0xF4);
            }

            break;
    }

    // Backup Icp for CDR lock
    ucIcp = ScalerGetByte_EXINT(P1C_5E_DP_FLD_16);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P1C_3E_FORE_OFFSET_K_24, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_46_FORE_OFFSET_K_32, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable Foreground Offset Calibration lane2, 3
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    //////////////
    // FLD Band //
    //////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:2] reg_fld_en = 2'b00 --> Disable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), 0x00);

    // Enable Vth/Tap0
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x41);

    // [3:2] reg_fld_en = 2'b11 --> Enable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_RBR:

            // Delay Time us [170,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(170);

            break;

        case _DP_LINK_HBR:

            // Delay Time us [130,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(130);

            break;

        default:
        case _DP_LINK_HBR2:

            // Delay Time us [65,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(65);

            break;
    }

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x00);

    // Enable Foreground Offset Calibration lane2, 3
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    // Scan Auto FLD
    ScalerSetByte_EXINT(P1C_5B_DP_FLD_13, ScalerGetByte_EXINT(P1C_77_DP_FLD_41));
    ScalerSetByte_EXINT(P1C_5C_DP_FLD_14, ScalerGetByte_EXINT(P1C_78_DP_FLD_42));

    // [3:2] reg_fld_adp_en_manual = 2'b11 --> Enable CDR Clock for Signal Detection
    ScalerSetBit_EXINT(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:2] reg_fld_cp_en_manual = 2'b00 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT3 | _BIT2), 0x00);

    // [3:0] Enable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xFF);

    // [3:2] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7:6] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ////////////////////////
    // FLD Target Measure //
    ////////////////////////

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            g_pusDpRx0ClockCount[_D0_DP_LANE0] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);

            // Measure Count x 4 for Default ref. Counter = 1000
            g_pusDpRx0ClockCount[_D0_DP_LANE0] = (g_pusDpRx0ClockCount[_D0_DP_LANE0] << 2);

            break;

        default:
        case _DP_TWO_LANE:

            g_pusDpRx0ClockCount[_D0_DP_LANE0] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);
            g_pusDpRx0ClockCount[_D0_DP_LANE1] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);

            // Measure Count x 4 for Default ref. Counter = 1000
            g_pusDpRx0ClockCount[_D0_DP_LANE0] = (g_pusDpRx0ClockCount[_D0_DP_LANE0] << 2);
            g_pusDpRx0ClockCount[_D0_DP_LANE1] = (g_pusDpRx0ClockCount[_D0_DP_LANE1] << 2);

            break;
    }
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp1SetPhyFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef) using 1
{
    BYTE ucIcp = 0;

    // LDO_en for Lane1
    ScalerSetBit_EXINT(P1A_30_COMBO_USB_00, ~_BIT1, _BIT1);

    // Enable Lane1 1.1V LDO Tracking
    ScalerSetBit_EXINT(P1A_30_COMBO_USB_00, ~_BIT0, _BIT0);

    // [5:4] LANE_EN = 2'b00 --> Disable LANE_EN
    // [1:0] CDR_EN = 2'b00 --> Disable CDR_EN
    ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~_BIT1, _BIT1);
            }

            // [4:3] DP Mac Select One Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        default:
        case _DP_TWO_LANE:

            // [7:6] Enable Lane0/1 LANE_EN
            ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

            // [3:2] Enable Lane0~1 CDR_EN
            ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(P1A_22_DP_RX_02, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // [4:3] DP Mac Select Two Lane
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [1:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit_EXINT(P1C_4C_READY_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [4:2] reg_vcm_ctrl_op_l1 = 3'b101 --> 600mV
    ScalerSetBit_EXINT(P1A_2C_DP_RX_12, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

    // [3:0] Disable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpRx0SetDFEInitialFlip2Lane_EXINT0(g_ucDpRx0LinkRate);

    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective on Every Bits
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_HBR2:

            // [3:0] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 900M/v in Each Lane
            ScalerSetBit_EXINT(P1A_03_COMBO_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // [5:4] en_half_pf = 1 --> Half Rate PD for High Speed
            ScalerSetBit_EXINT(P1A_04_COMBO_04, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

            // [2:0] sel_cont3 = 3'b010 --> BBPD UP/DN Sync
            ScalerSetBit_EXINT(P1A_10_COMBO_RX_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            // [0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit_EXINT(P1A_12_COMBO_RX_02, ~_BIT0, 0x00);

            // [3:1] LE_lowgain_highboost = 3'b110
            // [0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit_EXINT(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

            // [7:6] reg_sel_rate = 2'b00 for 5~10G
            ScalerSetBit_EXINT(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), 0x00);

            // reg_le_rlsel / reg_le_isel = 5.4GHz
            ScalerSetBit_EXINT(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            // reg_sel_cdr_res = 2K
            ScalerSetBit_EXINT(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Initial Band
            ScalerSetByte_EXINT(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte_EXINT(P1C_52_DP_FLD_4, 0x50);

            // reg_fld_cdr_cp Icp = 13.5uA in Each Lane
            ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xCC);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [1:0] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (50/500 = 2*(27M/540M))
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), 0x00);
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0x31);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0x31);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0xF4);
            }
            else
            {
                // [1:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0xF3);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0xF4);
            }

            break;

        case _DP_LINK_HBR:

            // [3:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit_EXINT(P1A_03_COMBO_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // [5:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit_EXINT(P1A_04_COMBO_04, ~(_BIT5 | _BIT4), 0x00);

            // [2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit_EXINT(P1A_10_COMBO_RX_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // [0] highboost_for_rbr = 0 --> only in rbr
            ScalerSetBit_EXINT(P1A_12_COMBO_RX_02, ~_BIT0, 0x00);

            // [3:1] LE_lowgain_highboost = 3'b100
            // [0] sel_dyn_std = 0 --> Dyn DFF
            ScalerSetBit_EXINT(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

            // [7:6] reg_sel_rate = 2'b01 for 2.5~5G
            ScalerSetBit_EXINT(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT6);

            // reg_le_rlsel / reg_le_isel = 2.7GHz
            ScalerSetBit_EXINT(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 8K
            ScalerSetBit_EXINT(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // Initial Band
            ScalerSetByte_EXINT(P1C_51_DP_FLD_3, 0x50);
            ScalerSetByte_EXINT(P1C_52_DP_FLD_4, 0x50);

            // reg_fld_cdr_cp Icp = 16.5uA in Each Lane
            ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xDD);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [1:0] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (100/500 = 2*(27M/270M))
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), 0x00);
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0x63);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0x63);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0xF4);
            }
            else
            {
                // [1:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0xF3);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0xF4);
            }

            break;

        default:
        case _DP_LINK_RBR:

            // [3:0] reg_cdr_kvco = 0 --> Analog CDR KVCO = 700M/v in Each Lane
            ScalerSetBit_EXINT(P1A_03_COMBO_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // [5:4] en_half_pf = 0 --> Full Rate PD for Low Speed
            ScalerSetBit_EXINT(P1A_04_COMBO_04, ~(_BIT5 | _BIT4), 0x00);

            // [2:0] sel_cont3 = 3'b101 --> Full Rate After 3-pulse Compression
            ScalerSetBit_EXINT(P1A_10_COMBO_RX_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // [0] highboost_for_rbr = 1 --> only in rbr
            ScalerSetBit_EXINT(P1A_12_COMBO_RX_02, ~_BIT0, _BIT0);

            // [3:1] LE_lowgain_highboost = 3'b000
            // [0] sel_dyn_std = 1 --> Std DFF
            ScalerSetBit_EXINT(P1A_14_COMBO_RX_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            // [7:6] reg_sel_rate = 2'b10 for <2.5G
            ScalerSetBit_EXINT(P1A_23_DP_RX_03, ~(_BIT7 | _BIT6), _BIT7);

            // reg_le_rlsel / reg_le_isel = 1.62GHz for DFE
            ScalerSetBit_EXINT(P1A_29_DP_RX_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            // reg_sel_cdr_res = 6K
            ScalerSetBit_EXINT(P1A_2A_DP_RX_10, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            // Initial Band
            ScalerSetByte_EXINT(P1C_51_DP_FLD_3, 0x70);
            ScalerSetByte_EXINT(P1C_52_DP_FLD_4, 0x70);

            // reg_fld_cdr_cp Icp = 19.5uA in Each Lane
            ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xEE);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // [1:0] reg_fld_xtal_en = 2'b11 --> Using 27M Xtal
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Analog CDR Auto FLD Counter (50/150 = 2*(27M/162M))
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), 0x00);
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0x31);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0x31);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), 0x00);
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0x96);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0x96);
            }
            else
            {
                // [1:0] reg_fld_xtal_en = 0 --> Using D10.2
                ScalerSetBit_EXINT(P1C_4F_DP_FLD_1, ~(_BIT1 | _BIT0), 0x00);

                // Analog CDR Auto FLD Counter
                ScalerSetBit_EXINT(P1C_67_DP_FLD_25, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_63_DP_FLD_21, 0xF3);
                ScalerSetByte_EXINT(P1C_64_DP_FLD_22, 0xF3);

                ScalerSetBit_EXINT(P1C_6C_DP_FLD_30, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte_EXINT(P1C_68_DP_FLD_26, 0xF4);
                ScalerSetByte_EXINT(P1C_69_DP_FLD_27, 0xF4);
            }

            break;
    }

    // Backup Icp for CDR lock
    ucIcp = ScalerGetByte_EXINT(P1C_5D_DP_FLD_15);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P1C_2E_FORE_OFFSET_K_8, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_36_FORE_OFFSET_K_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable Foreground Offset Calibration lane0, 1
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    //////////////
    // FLD Band //
    //////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] reg_fld_en = 2'b00 --> Disable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), 0x00);

    // Enable Vth/Tap0
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x41);

    // [1:0] reg_fld_en = 2'b11 --> Enable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_RBR:

            // Delay Time us [170,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(170);

            break;

        case _DP_LINK_HBR:

            // Delay Time us [130,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(130);

            break;

        default:
        case _DP_LINK_HBR2:

            // Delay Time us [65,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(65);

            break;
    }

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x00);

    // Enable Foreground Offset Calibration lane0, 1
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    // Scan Auto FLD
    ScalerSetByte_EXINT(P1C_59_DP_FLD_11, ScalerGetByte_EXINT(P1C_75_DP_FLD_39));
    ScalerSetByte_EXINT(P1C_5A_DP_FLD_12, ScalerGetByte_EXINT(P1C_76_DP_FLD_40));

    // [1:0] reg_fld_adp_en_manual = 2'b11 --> Enable CDR Clock for Signal Detection
    ScalerSetBit_EXINT(P1C_57_DP_FLD_9, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] reg_fld_cp_en_manual = 2'b00 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT1 | _BIT0), 0x00);

    // [3:0] Enable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xFF);

    // [1:0] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [5:4] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ////////////////////////
    // FLD Target Measure //
    ////////////////////////

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            g_pusDpRx0ClockCount[_D0_DP_LANE0] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);

            // Measure Count x 4 for Default ref. Counter = 1000
            g_pusDpRx0ClockCount[_D0_DP_LANE0] = (g_pusDpRx0ClockCount[_D0_DP_LANE0] << 2);

            break;

        default:
        case _DP_TWO_LANE:

            g_pusDpRx0ClockCount[_D0_DP_LANE0] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);
            g_pusDpRx0ClockCount[_D0_DP_LANE1] = ScalerDpRx0SignalDetectMeasureCount_EXINT0(_D0_DP_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_250_CYCLE);

            // Measure Count x 4 for Default ref. Counter = 1000
            g_pusDpRx0ClockCount[_D0_DP_LANE0] = (g_pusDpRx0ClockCount[_D0_DP_LANE0] << 2);
            g_pusDpRx0ClockCount[_D0_DP_LANE1] = (g_pusDpRx0ClockCount[_D0_DP_LANE1] << 2);

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp2SetPhy_EXINT0(void) using 1
{
    // [4] Enable Comma Detection
    ScalerSetBit_EXINT(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    if((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
    {
        // [5] Disable De-Scrambling
        ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // [5] Enable De-Scrambling
        ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
    }

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

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

    if(ScalerGetBit_EXINT(P1A_00_COMBO_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6))
    {
        ScalerDpRx0Tp2SetPhyUnFlip2Lane_EXINT0();
    }
    else if(ScalerGetBit_EXINT(P1A_00_COMBO_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        ScalerDpRx0Tp2SetPhyFlip2Lane_EXINT0();
    }
    else
#endif
    {
        ScalerDpRx0Tp2SetPhy4Lane_EXINT0();
    }
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp2SetPhy4Lane_EXINT0(void) using 1
{
    BYTE ucIcp = 0;


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetByte_EXINT(P1C_4C_READY_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte_EXINT(P1C_4D_READY_TIMER_2, 0x0F);

    // [3:0] Disable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////////
    // DFE CDR Initial Setting //
    /////////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpRx0SetDFEInitial_EXINT0(g_ucDpRx0LinkRate);

    ucIcp = ScalerGetByte_EXINT(P1C_5D_DP_FLD_15);

    // Enable Foreground Offset Calibration lane
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Initial Band
    ScalerSetByte_EXINT(P1C_51_DP_FLD_3, ScalerGetByte_EXINT(P1C_75_DP_FLD_39));
    ScalerSetByte_EXINT(P1C_52_DP_FLD_4, ScalerGetByte_EXINT(P1C_76_DP_FLD_40));
    ScalerSetByte_EXINT(P1C_53_DP_FLD_5, ScalerGetByte_EXINT(P1C_77_DP_FLD_41));
    ScalerSetByte_EXINT(P1C_54_DP_FLD_6, ScalerGetByte_EXINT(P1C_78_DP_FLD_42));

    // Reset FLD Band and Enable Auto FLD
    ScalerSetByte_EXINT(P1C_50_DP_FLD_2, 0xFF);
    ScalerSetByte_EXINT(P1C_50_DP_FLD_2, 0x0F);

    // [3:0] reg_fld_en = 4'b0000 --> Disable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // [3:0] reg_fld_en = 4'b1111 --> Enable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS_EXINT(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS_EXINT(85);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x00);

    // Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    ///////////////////////
    // FLD Band Finetune //
    ///////////////////////

    // Scan Auto FLD
    ScalerSetByte_EXINT(P1C_59_DP_FLD_11, ScalerGetByte_EXINT(P1C_75_DP_FLD_39));
    ScalerSetByte_EXINT(P1C_5A_DP_FLD_12, ScalerGetByte_EXINT(P1C_76_DP_FLD_40));
    ScalerSetByte_EXINT(P1C_5B_DP_FLD_13, ScalerGetByte_EXINT(P1C_77_DP_FLD_41));
    ScalerSetByte_EXINT(P1C_5C_DP_FLD_14, ScalerGetByte_EXINT(P1C_78_DP_FLD_42));

    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetBit_EXINT(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_fld_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetByte_EXINT(P1C_50_DP_FLD_2, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [3:0] Enable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE0);

            break;

        case _DP_TWO_LANE:

            // Lane0,1 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE0);
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE1);

            break;

        default:
        case _DP_FOUR_LANE:

            // Lane0,1,2,3 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE0);
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE1);
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE2);
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE3);

            break;
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = max for locking range
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xFF);
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xFF);

    // [3:0] reg_fld_cp_en_manual = 4'b1111 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, ucIcp);
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp2SetPhyUnFlip2Lane_EXINT0(void) using 1
{
    BYTE ucIcp = 0;


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:6] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:2] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit_EXINT(P1C_4C_READY_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7:6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:0] Disable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////////
    // DFE CDR Initial Setting //
    /////////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpRx0SetDFEInitialUnFlip2Lane_EXINT0(g_ucDpRx0LinkRate);

    ucIcp = ScalerGetByte_EXINT(P1C_5E_DP_FLD_16);

    // Enable Foreground Offset Calibration lane2, 3
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Initial Band
    ScalerSetByte_EXINT(P1C_53_DP_FLD_5, ScalerGetByte_EXINT(P1C_77_DP_FLD_41));
    ScalerSetByte_EXINT(P1C_54_DP_FLD_6, ScalerGetByte_EXINT(P1C_78_DP_FLD_42));

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Reset FLD -> Low Active Reset
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), 0x00);

    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Enable FLD and DFE Adaptation
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS_EXINT(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS_EXINT(85);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x00);

    // Enable Foreground Offset Calibration lane2, 3
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    ///////////////////////
    // FLD Band Finetune //
    ///////////////////////

    // Scan Auto FLD
    ScalerSetByte_EXINT(P1C_5B_DP_FLD_13, ScalerGetByte_EXINT(P1C_77_DP_FLD_41));
    ScalerSetByte_EXINT(P1C_5C_DP_FLD_14, ScalerGetByte_EXINT(P1C_78_DP_FLD_42));

    // [3:2] reg_fld_adp_en_manual = 2'b11 --> Enable CDR Clock
    ScalerSetBit_EXINT(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:2] reg_fld_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT3 | _BIT2), 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [3:0] Enable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE0);

            break;

        default:
        case _DP_TWO_LANE:

            // Lane0,1 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE0);
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE1);

            break;
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = max for locking range
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xFF);

    // [3:2] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7:6] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}


//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp2SetPhyFlip2Lane_EXINT0(void) using 1
{
    BYTE ucIcp = 0;


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [1:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit_EXINT(P1C_4C_READY_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [3:0] Disable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    /////////////////////////////
    // DFE CDR Initial Setting //
    /////////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpRx0SetDFEInitialFlip2Lane_EXINT0(g_ucDpRx0LinkRate);

    ucIcp = ScalerGetByte_EXINT(P1C_5D_DP_FLD_15);

    // Enable Foreground Offset Calibration lane0, 1
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Initial Band
    ScalerSetByte_EXINT(P1C_51_DP_FLD_3, ScalerGetByte_EXINT(P1C_75_DP_FLD_39));
    ScalerSetByte_EXINT(P1C_52_DP_FLD_4, ScalerGetByte_EXINT(P1C_76_DP_FLD_40));

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Reset FLD -> Low Active Reset
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), 0x00);

    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Enable FLD and DFE Adaptation
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS_EXINT(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS_EXINT(85);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x00);

    // Enable Foreground Offset Calibration lane0, 1
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,50] Waiting for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    ///////////////////////
    // FLD Band Finetune //
    ///////////////////////

    // Scan Auto FLD
    ScalerSetByte_EXINT(P1C_59_DP_FLD_11, ScalerGetByte_EXINT(P1C_75_DP_FLD_39));
    ScalerSetByte_EXINT(P1C_5A_DP_FLD_12, ScalerGetByte_EXINT(P1C_76_DP_FLD_40));

    // [1:0] reg_fld_adp_en_manual = 2'b11 --> Enable CDR Clock
    ScalerSetBit_EXINT(P1C_57_DP_FLD_9, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] reg_fld_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT1 | _BIT0), 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [3:0] Enable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            // Lane0 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE0);

            break;

        default:
        case _DP_TWO_LANE:

            // Lane0,1 VCO Adjust
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE0);
            ScalerDpRx0AdjustLaneFLDBand_EXINT0(_D0_DP_LANE1);

            break;
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = max for locking range
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xFF);

    // [1:0] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [5:4] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}
#endif

//--------------------------------------------------
// Description  : DP FLD Band Finetune
// Input Value  : LaneNumber
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0AdjustLaneFLDBand_EXINT0(BYTE ucDpRx0LaneNumber) using 1
{
    WORD usVCOAutoBandAdd4 = 0;
    BYTE ucBestVCOBand = 0;
    BYTE ucFLDBand = 0;
    BYTE ucVCOBandDiff = 0;

    g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] = 0;

    // [1:0] freqdet_lane_sel
    ScalerSetBit_EXINT(PB_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), ucDpRx0LaneNumber);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 30; g_ucDpRx0Temp++)
    {
        DELAY_5US_EXINT();

        // FLD Auto Band Measure Done
        if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            // Clock Count of Each Lane in FLD Auto Band
            g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }


    ////////////////////////
    // Fine Tune VCO Band //
    ////////////////////////

    // Scan Lane0~3 Auto FLD
    switch(ucDpRx0LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ucFLDBand = ScalerGetByte_EXINT(P1C_59_DP_FLD_11);
            ScalerSetByte_EXINT(P1C_59_DP_FLD_11, (ucFLDBand + 4));

            break;

        case _DP_SCALER_LANE1:

            ucFLDBand = ScalerGetByte_EXINT(P1C_5A_DP_FLD_12);
            ScalerSetByte_EXINT(P1C_5A_DP_FLD_12, (ucFLDBand + 4));

            break;

        case _DP_SCALER_LANE2:

            ucFLDBand = ScalerGetByte_EXINT(P1C_5B_DP_FLD_13);
            ScalerSetByte_EXINT(P1C_5B_DP_FLD_13, (ucFLDBand + 4));

            break;

        case _DP_SCALER_LANE3:

            ucFLDBand = ScalerGetByte_EXINT(P1C_5C_DP_FLD_14);
            ScalerSetByte_EXINT(P1C_5C_DP_FLD_14, (ucFLDBand + 4));

            break;
    }

    // Delay Time [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 30; g_ucDpRx0Temp++)
    {
        DELAY_5US_EXINT();

        if((g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] == 0) || (ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6))
        {
            break;
        }
    }

    // Measure Done
    if((g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] != 0) && (ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6))
    {
        usVCOAutoBandAdd4 = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

        ucVCOBandDiff = (abs(g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] - usVCOAutoBandAdd4) >> 2);
    }
    else
    {
        ucVCOBandDiff = 0;
    }


    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    if(ucVCOBandDiff != 0)
    {
        if(g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] < g_pusDpRx0ClockCount[ucDpRx0LaneNumber])
        {
            ucBestVCOBand = ucFLDBand + (((g_pusDpRx0ClockCount[ucDpRx0LaneNumber] - g_pusDpRx0ClockCount1[ucDpRx0LaneNumber]) / ucVCOBandDiff) + 1);
        }
        else
        {
            ucBestVCOBand = ucFLDBand - ((g_pusDpRx0ClockCount1[ucDpRx0LaneNumber] - g_pusDpRx0ClockCount[ucDpRx0LaneNumber]) / ucVCOBandDiff);
        }
    }
    else
    {
        ucBestVCOBand = ucFLDBand;
    }

    // Manually Reload FLD Band
    switch(ucDpRx0LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ScalerSetByte_EXINT(P1C_59_DP_FLD_11, ucBestVCOBand);

            break;

        case _DP_SCALER_LANE1:

            ScalerSetByte_EXINT(P1C_5A_DP_FLD_12, ucBestVCOBand);

            break;

        case _DP_SCALER_LANE2:

            ScalerSetByte_EXINT(P1C_5B_DP_FLD_13, ucBestVCOBand);

            break;

        case _DP_SCALER_LANE3:

            ScalerSetByte_EXINT(P1C_5C_DP_FLD_14, ucBestVCOBand);

            break;
    }
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDFEInitial_EXINT0(EnumDpLinkRate enumDpLinkRate) using 1
{
    enumDpLinkRate = enumDpLinkRate;

    if(g_ucDpRx0TrainingPatternSet == _DP_TRAINING_PATTERN_3)
    {
        // Tap Divider = 34 for TPS3
        ScalerSetByte_EXINT(P17_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte_EXINT(P17_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x00);

    // LE Max = 24, LE Initial = 16, Servo Initial = 16
    ScalerSetByte_EXINT(P17_A2_L0_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_B2_L1_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_C2_L2_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_D2_L3_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_A3_L0_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P17_B3_L1_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P17_C3_L2_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P17_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 21
    ScalerSetByte_EXINT(P17_A4_L0_INIT_2, 0x15);
    ScalerSetByte_EXINT(P17_B4_L1_INIT_2, 0x15);
    ScalerSetByte_EXINT(P17_C4_L2_INIT_2, 0x15);
    ScalerSetByte_EXINT(P17_D4_L3_INIT_2, 0x15);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P17_A5_L0_INIT_3, 0x00);
    ScalerSetByte_EXINT(P17_B5_L1_INIT_3, 0x00);
    ScalerSetByte_EXINT(P17_C5_L2_INIT_3, 0x00);
    ScalerSetByte_EXINT(P17_D5_L3_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(P17_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P17_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P17_C6_L2_INIT_4, 0x00);
    ScalerSetByte_EXINT(P17_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 28
    ScalerSetByte_EXINT(P17_A9_L0_INIT_7, 0x1C);
    ScalerSetByte_EXINT(P17_B9_L1_INIT_7, 0x1C);
    ScalerSetByte_EXINT(P17_C9_L2_INIT_7, 0x1C);
    ScalerSetByte_EXINT(P17_D9_L3_INIT_7, 0x1C);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P17_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P17_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P17_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P17_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P17_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P17_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P17_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P17_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
}

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDFEInitialUnFlip2Lane_EXINT0(EnumDpLinkRate enumDpLinkRate) using 1
{
    enumDpLinkRate = enumDpLinkRate;

    if(g_ucDpRx0TrainingPatternSet == _DP_TRAINING_PATTERN_3)
    {
        // Tap Divider = 34 for TPS3
        ScalerSetByte_EXINT(P17_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte_EXINT(P17_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x00);

    // LE Max = 24, LE Initial = 16, Servo Initial = 16
    ScalerSetByte_EXINT(P17_C2_L2_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_D2_L3_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_C3_L2_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P17_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 21
    ScalerSetByte_EXINT(P17_C4_L2_INIT_2, 0x15);
    ScalerSetByte_EXINT(P17_D4_L3_INIT_2, 0x15);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P17_C5_L2_INIT_3, 0x00);
    ScalerSetByte_EXINT(P17_D5_L3_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(P17_C6_L2_INIT_4, 0x00);
    ScalerSetByte_EXINT(P17_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 28
    ScalerSetByte_EXINT(P17_C9_L2_INIT_7, 0x1C);
    ScalerSetByte_EXINT(P17_D9_L3_INIT_7, 0x1C);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P17_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P17_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P17_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P17_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDFEInitialFlip2Lane_EXINT0(EnumDpLinkRate enumDpLinkRate) using 1
{
    enumDpLinkRate = enumDpLinkRate;

    if(g_ucDpRx0TrainingPatternSet == _DP_TRAINING_PATTERN_3)
    {
        // Tap Divider = 34 for TPS3
        ScalerSetByte_EXINT(P17_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte_EXINT(P17_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x00);

    // LE Max = 24, LE Initial = 16, Servo Initial = 16
    ScalerSetByte_EXINT(P17_A2_L0_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_B2_L1_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_A3_L0_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P17_B3_L1_INIT_1, 0xD0);

    // Tap0 Initial Value = 21
    ScalerSetByte_EXINT(P17_A4_L0_INIT_2, 0x15);
    ScalerSetByte_EXINT(P17_B4_L1_INIT_2, 0x15);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P17_A5_L0_INIT_3, 0x00);
    ScalerSetByte_EXINT(P17_B5_L1_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(P17_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P17_B6_L1_INIT_4, 0x00);

    // Vth Initial Value = 28
    ScalerSetByte_EXINT(P17_A9_L0_INIT_7, 0x1C);
    ScalerSetByte_EXINT(P17_B9_L1_INIT_7, 0x1C);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P17_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P17_BA_L1_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P17_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P17_BA_L1_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}
#endif

//--------------------------------------------------
// Description : check DFE Coef in INT0
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpRx0DFECheck_EXINT0(void) using 1
{
    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_FOUR_LANE:

            // Read Lane2 DFE
            ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0C1B)
            {
                return _FALSE;
            }

            // Read Lane3 DFE
            ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0C1B)
            {
                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0C1B)
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0C1B)
            {
                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0C1B)
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0C1B)
            {
                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0C1B)
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
// Description : Check Valid Signal in INT0
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpRx0SignalCheck_EXINT0(void) using 1
{
    // SignalCheck is added for RL6492 Rx0/Rx1 Rxdiff
    return _FALSE;
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RebuildPhy_WDINT(BYTE ucDpLinkRate, BYTE ucDpcdLane) using 3
{
    // [4] Enable Comma Detection
    ScalerSetBit_EXINT(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);

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

    if((ucDpcdLane & _BIT7) == _BIT7)
    {
        // [2] Enable Enhancement Control Mode
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // [2] Disable Enhancement Control Mode
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    if(ScalerTypeCRx0PdGetPinAssignment_WDINT() == _TYPE_C_PIN_ASSIGNMENT_D)
    {
        if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            ScalerDpRx0RebuildPhyUnFlip2Lane_WDINT(ucDpLinkRate);
        }
        else
        {
            ScalerDpRx0RebuildPhyFlip2Lane_WDINT(ucDpLinkRate);
        }
    }
    else
#endif
    {
        ScalerDpRx0RebuildPhy4Lane_WDINT(ucDpLinkRate);
    }
}


//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RebuildPhy4Lane_WDINT(BYTE ucDpLinkRate) using 3
{
    BYTE ucIcp = 0;
    BYTE pucTap0[4];

    // [7:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetByte_EXINT(P1C_4C_READY_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte_EXINT(P1C_4D_READY_TIMER_2, 0x0F);

    // [3:0] Disable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ucIcp = ScalerGetByte_EXINT(P1C_5D_DP_FLD_15);


    ///////////////
    // DFE Reset //
    ///////////////

    // Tap Divider = 10 for All Other Pattern
    ScalerSetByte_EXINT(P17_ED_LOOP_DIV_2, 0xCA);

    // LE Max = 24, LE Initial = 16, Servo Initial = 16
    ScalerSetByte_EXINT(P17_A2_L0_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_B2_L1_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_C2_L2_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_D2_L3_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_A3_L0_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P17_B3_L1_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P17_C3_L2_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P17_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 21
    ScalerSetByte_EXINT(P17_A4_L0_INIT_2, 0x15);
    ScalerSetByte_EXINT(P17_B4_L1_INIT_2, 0x15);
    ScalerSetByte_EXINT(P17_C4_L2_INIT_2, 0x15);
    ScalerSetByte_EXINT(P17_D4_L3_INIT_2, 0x15);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P17_A5_L0_INIT_3, 0x00);
    ScalerSetByte_EXINT(P17_B5_L1_INIT_3, 0x00);
    ScalerSetByte_EXINT(P17_C5_L2_INIT_3, 0x00);
    ScalerSetByte_EXINT(P17_D5_L3_INIT_3, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x00);


    ///////////////////////////
    // Foregound Calibration //
    ///////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P1C_2E_FORE_OFFSET_K_8, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_36_FORE_OFFSET_K_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_3E_FORE_OFFSET_K_24, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_46_FORE_OFFSET_K_32, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] en_fore_offset = 1 --> Enable Foreground Calibration
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Polling for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetByte_EXINT(P1C_50_DP_FLD_2, 0xFF);
    ScalerSetByte_EXINT(P1C_50_DP_FLD_2, 0x0F);

    // [3:0] reg_fld_en = 4'b0000 --> Disable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // [3:0] reg_fld_en = 4'b1111 --> Enable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_RBR:

            // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(85);

            break;

        case _DP_LINK_HBR:

            // Delay Time us [65,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(65);

            break;

        default:
        case _DP_LINK_HBR2:

            // Delay Time us [35,x] Waiting for FLD and DFE Adaptation
            DELAY_35US_EXINT();

            break;
    }

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_RBR:

            // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(85);

            break;

        case _DP_LINK_HBR:

            // Delay Time us [65,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(65);

            break;

        default:
        case _DP_LINK_HBR2:

            // Delay Time us [35,x] Waiting for FLD and DFE Adaptation
            DELAY_35US_EXINT();

            break;
    }

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x00);

    if(g_ucDpRx0LinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte_EXINT(P17_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte_EXINT(P17_A4_L0_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P17_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P17_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit_EXINT(P17_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte_EXINT(P17_B4_L1_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P17_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P17_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit_EXINT(P17_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte_EXINT(P17_C4_L2_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P17_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P17_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit_EXINT(P17_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte_EXINT(P17_D4_L3_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P17_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P17_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit_EXINT(P17_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }

    // [3:0] rstb_fore_offset --> Toggle Foreground Calibration
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Polling for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock for Signal Detection
    ScalerSetBit_EXINT(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_fld_cp_en_manual = 4'b0000 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetByte_EXINT(P1C_50_DP_FLD_2, 0x00);

    // [3:0] Enable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xFF);
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xFF);

    // [3:0] reg_fld_cp_en_manual = 4'b1111 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, ucIcp);
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7:4] reg_en_data_manual = 4b'1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

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
            g_pusDpRx0ClockCount[0] = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }

    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];
}

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT for TypeC 2/3 Lane
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RebuildPhyUnFlip2Lane_WDINT(BYTE ucDpLinkRate) using 3
{
    BYTE ucIcp = 0;
    BYTE pucTap0[2];

    // [7:6] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [3:2] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit_EXINT(P1C_4C_READY_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7:6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:0] Disable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ucIcp = ScalerGetByte_EXINT(P1C_5E_DP_FLD_16);


    ///////////////
    // DFE Reset //
    ///////////////

    // Tap Divider = 10 for All Other Pattern
    ScalerSetByte_EXINT(P17_ED_LOOP_DIV_2, 0xCA);

    // LE Max = 24, LE Initial = 16, Servo Initial = 16
    ScalerSetByte_EXINT(P17_C2_L2_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_D2_L3_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_C3_L2_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P17_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 21
    ScalerSetByte_EXINT(P17_C4_L2_INIT_2, 0x15);
    ScalerSetByte_EXINT(P17_D4_L3_INIT_2, 0x15);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P17_C5_L2_INIT_3, 0x00);
    ScalerSetByte_EXINT(P17_D5_L3_INIT_3, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x00);


    ///////////////////////////
    // Foregound Calibration //
    ///////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P1C_3E_FORE_OFFSET_K_24, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_46_FORE_OFFSET_K_32, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable Foreground Offset Calibration lane2, 3
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,50] Polling for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Reset FLD -> Low Active Reset
    // [3:2] reg_fld_en = 2'b00 --> Disable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Reset FLD -> Low Active Reset
    // [3:2] reg_fld_en = 2'b11 --> Enable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_RBR:

            // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(85);

            break;

        case _DP_LINK_HBR:

            // Delay Time us [65,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(65);

            break;

        default:
        case _DP_LINK_HBR2:

            // Delay Time us [35,x] Waiting for FLD and DFE Adaptation
            DELAY_35US_EXINT();

            break;
    }

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_RBR:

            // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(85);

            break;

        case _DP_LINK_HBR:

            // Delay Time us [65,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(65);

            break;

        default:
        case _DP_LINK_HBR2:

            // Delay Time us [35,x] Waiting for FLD and DFE Adaptation
            DELAY_35US_EXINT();

            break;
    }

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P17_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_D1_L3_DFE_EN_2, 0x00);

    if(g_ucDpRx0LinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte_EXINT(P17_F0_COEF_1, 0x01);

        // Select to Lane2
        ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[0] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[1] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(P17_C4_L2_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P17_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P17_C4_L2_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit_EXINT(P17_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(P17_D4_L3_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P17_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P17_D4_L3_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit_EXINT(P17_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }

    // Enable Foreground Offset Calibration lane2, 3
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,50] Polling for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_49_FORE_OFFSET_K_35, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_4A_FORE_OFFSET_K_36, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    // [3:2] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock for Signal Detection
    ScalerSetBit_EXINT(P1C_57_DP_FLD_9, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3:2] reg_fld_cp_en_manual = 4'b0000 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT3 | _BIT2), 0x00);

    // [3:0] Enable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, 0xFF);

    // [3:2] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte_EXINT(P1C_5E_DP_FLD_16, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7:6] reg_en_data_manual = 2b'11 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    // [1:0] freqdet_lane_sel = Lane3
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
            g_pusDpRx0ClockCount[0] = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }

    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];
}


//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT for TypeC 0/1 Lane
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RebuildPhyFlip2Lane_WDINT(BYTE ucDpLinkRate) using 3
{
    BYTE ucIcp = 0;
    BYTE pucTap0[2];

    // [5:4] reg_en_eqen_manual = 0 --> Disable DFE Ready
    // [1:0] reg_bypass_eqen_rdy = 0 --> DFE Ready Auto Mode
    ScalerSetBit_EXINT(P1C_4C_READY_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [3:0] Disable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ucIcp = ScalerGetByte_EXINT(P1C_5D_DP_FLD_15);


    ///////////////
    // DFE Reset //
    ///////////////

    // Tap Divider = 10 for All Other Pattern
    ScalerSetByte_EXINT(P17_ED_LOOP_DIV_2, 0xCA);

    // LE Max = 24, LE Initial = 16, Servo Initial = 16
    ScalerSetByte_EXINT(P17_A2_L0_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_B2_L1_LIMIT_INIT, 0x80);
    ScalerSetByte_EXINT(P17_A3_L0_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P17_B3_L1_INIT_1, 0xD0);

    // Tap0 Initial Value = 21
    ScalerSetByte_EXINT(P17_A4_L0_INIT_2, 0x15);
    ScalerSetByte_EXINT(P17_B4_L1_INIT_2, 0x15);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P17_A5_L0_INIT_3, 0x00);
    ScalerSetByte_EXINT(P17_B5_L1_INIT_3, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P17_EF_RESET_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x00);


    ///////////////////////////
    // Foregound Calibration //
    ///////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P1C_2E_FORE_OFFSET_K_8, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_36_FORE_OFFSET_K_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable Foreground Offset Calibration lane0, 1
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,50] Polling for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Reset FLD Band and Enable Auto FLD
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Reset FLD -> Low Active Reset
    // [1:0] reg_fld_en = 2'b00 --> Disable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Reset FLD -> Low Active Reset
    // [1:0] reg_fld_en = 2'b11 --> Enable FLD
    ScalerSetBit_EXINT(P1C_4E_DP_FLD_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_RBR:

            // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(85);

            break;

        case _DP_LINK_HBR:

            // Delay Time us [65,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(65);

            break;

        default:
        case _DP_LINK_HBR2:

            // Delay Time us [35,x] Waiting for FLD and DFE Adaptation
            DELAY_35US_EXINT();

            break;
    }

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(P17_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_RBR:

            // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(85);

            break;

        case _DP_LINK_HBR:

            // Delay Time us [65,x] Waiting for FLD and DFE Adaptation
            DELAY_XUS_EXINT(65);

            break;

        default:
        case _DP_LINK_HBR2:

            // Delay Time us [35,x] Waiting for FLD and DFE Adaptation
            DELAY_35US_EXINT();

            break;
    }

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P17_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P17_B1_L1_DFE_EN_2, 0x00);

    if(g_ucDpRx0LinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte_EXINT(P17_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte_EXINT(P17_A4_L0_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P17_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P17_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit_EXINT(P17_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 21)
        {
            // Reload Tap0 to 27 (max)
            ScalerSetByte_EXINT(P17_B4_L1_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P17_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P17_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit_EXINT(P17_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P17_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
    }

    // Enable Foreground Offset Calibration lane0, 1
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_26_FORE_OFFSET_K_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,50] Polling for K Offset
    for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 10; g_ucDpRx0Temp++)
    {
        if(((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_47_FORE_OFFSET_K_33, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P1A_22_DP_RX_02, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_48_FORE_OFFSET_K_34, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    // [1:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock for Signal Detection
    ScalerSetBit_EXINT(P1C_57_DP_FLD_9, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] reg_fld_cp_en_manual = 4'b0000 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(P1C_50_DP_FLD_2, ~(_BIT1 | _BIT0), 0x00);

    // [3:0] Enable Signal Detection
    ScalerSetBit_EXINT(P1A_20_DP_RX_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, 0xFF);

    // [1:0] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_58_DP_FLD_10, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetByte_EXINT(P1C_5D_DP_FLD_15, ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [5:4] reg_en_data_manual = 2b'11 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_4D_READY_TIMER_2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    // [1:0] freqdet_lane_sel = Lane1
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
            g_pusDpRx0ClockCount[0] = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }

    g_pusDpRx0ClockCount[1] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[2] = g_pusDpRx0ClockCount[0];
    g_pusDpRx0ClockCount[3] = g_pusDpRx0ClockCount[0];
}
#endif // End of TypeC PD Embedded

#endif // End of WD INT Support

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

    g_ucDpRx0Tp1PermitSwingLevel0 = ScalerDpRx0CheckSourceOUI_EXINT0(_LT_TP1_PERMIT_SWING_LEVEL_0);

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        if((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & (_BIT1 | _BIT0)) >= _BIT0)
        {
            ScalerDpRx0Tp1SetPhy_EXINT0(_DP_NF_REF_XTAL);
        }
        else
        {
#if(_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON)
            if(g_ucDpRx0Tp1PermitSwingLevel0 == _TRUE)
            {
                ScalerDpRx0Tp1SetPhy_EXINT0(_DP_NF_REF_XTAL);
            }
            else
#endif
            {
                if(g_ucDpRx0LinkRate <= _DP_LINK_HBR)
                {
#if(_DP_HBR_RBR_LT_FORCE_MARGINAL_LINK == _OFF)

                    ScalerDpRx0Tp1SetPhy_EXINT0(_DP_NF_REF_XTAL);
#endif
                }
            }
        }
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

//--------------------------------------------------
// Description  : Check DP Source OUI for Specific Action
// Input Value  : Action that Need to Check Specific Source OUI
// Output Value : Whether Specific Source OUI Hit or Not
//--------------------------------------------------
BYTE ScalerDpRx0CheckSourceOUI_EXINT0(EnumDpRxCheckSourceOUI enumDpRx0CheckSourceOUI) using 1
{
    switch(enumDpRx0CheckSourceOUI)
    {
#if(_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON)
        case _LT_TP1_PERMIT_SWING_LEVEL_0:
        {
            BYTE pucSrcIeeeOuiUser[9] = _SRC_IEEE_OUI_APPLE_2017_PRO_15INCH_IDENTIFY_STRING;

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 9; pData_EXINT[0]++)
            {
                if((ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x03, pData_EXINT[0])) != (pucSrcIeeeOuiUser[pData_EXINT[0]]))
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
#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx0GetDpcdBitInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit) using 3
{
    ScalerSetByte_EXINT(PB7_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PB7_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PB7_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetBit_EXINT(PB7_C4_DPCD_DATA_PORT, ucDpcdBit);
}
#endif
#endif

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpRx0Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    BYTE pucDpPhyLinkTrainingLevel[4];
    BYTE pucDpPhyLinkTrainingRequest[4];
    BYTE ucTP1SignalDetect = 0;
    BYTE ucTP1NormalLTSwingLevel = 2;
    BYTE ucTP1RBRHBRFakeLTSwingLevel = 1;
    BYTE ucTP1HBR2FakeLTSwingLevel = 3;
    BYTE ucFakeLTLaneCount = g_ucDpRx0LaneCount;

    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

#if(_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON)
    if(g_ucDpRx0Tp1PermitSwingLevel0 == _TRUE)
    {
        ucTP1NormalLTSwingLevel = 0;
        ucTP1RBRHBRFakeLTSwingLevel = 0;
        ucTP1HBR2FakeLTSwingLevel = 0;
    }
#endif

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        if((GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) &&
           (GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL) &&
           (g_bDpRx0Tp1Initial == _FALSE))
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

        ucTP1SignalDetect = ((ScalerDpRx0Tp1SignalDetectCheck_EXINT0(_D0_DP_LANE3) << 3) |
                             (ScalerDpRx0Tp1SignalDetectCheck_EXINT0(_D0_DP_LANE2) << 2) |
                             (ScalerDpRx0Tp1SignalDetectCheck_EXINT0(_D0_DP_LANE1) << 1) |
                             (ScalerDpRx0Tp1SignalDetectCheck_EXINT0(_D0_DP_LANE0)));

        pucDpPhyLinkTrainingLevel[0] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pucDpPhyLinkTrainingLevel[1] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pucDpPhyLinkTrainingLevel[2] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pucDpPhyLinkTrainingLevel[3] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

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

        g_ucDpRx0LinkStatus01 = 0;
        g_ucDpRx0LinkStatus23 = 0;

        switch(g_ucDpRx0LaneCount)
        {
            case _DP_FOUR_LANE:

                // Read Back Lane3 Vth
                ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE3 << 6));

                ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane2 Check
                if((((GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                    ((GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                    ((GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                    ((GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7))) &&
                   ((ucTP1SignalDetect & _BIT3) == _BIT3))
                {
                    if(g_ucDpRx0LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x10;
                        }
                        else if((ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F) > 12)
                        {
                            if((GET_DP_RX_D0_LANE3_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) >= ((g_ucDpRx0LinkRequest23 >> 4) & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x10;
                            }
                            else
                            {
                                g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                                CLR_DP_RX_D0_LANE3_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x10;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                }

                // Read Back Lane2 Vth
                ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE3 << 6));

                ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane2 Check
                if((((GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                    ((GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                    ((GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                    ((GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7))) &&
                   ((ucTP1SignalDetect & _BIT2) == _BIT2))
                {
                    if(g_ucDpRx0LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F) > 12)
                        {
                            if((GET_DP_RX_D0_LANE2_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) >= (g_ucDpRx0LinkRequest23 & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                                CLR_DP_RX_D0_LANE2_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                }

                // Read Back Lane1 Vth
                ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE1 << 6));

                ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane1 Check
                if((((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                    ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                    ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                    ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7))) &&
                   ((ucTP1SignalDetect & _BIT1) == _BIT1))
                {
                    if(g_ucDpRx0LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x10;
                        }
                        else if((ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F) > 12)
                        {
                            if((GET_DP_RX_D0_LANE1_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ((g_ucDpRx0LinkRequest01 >> 4) & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x10;
                            }
                            else
                            {
                                g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                                CLR_DP_RX_D0_LANE1_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x10;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                }

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

                ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                    ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                    ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                    ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7))) &&
                   ((ucTP1SignalDetect & _BIT0) == _BIT0))
                {
                    if(g_ucDpRx0LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F) > 12)
                        {
                            if((GET_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= (g_ucDpRx0LinkRequest01 & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                                CLR_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                break;

            case _DP_TWO_LANE:

                // Read Back Lane1 Vth
                ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE1 << 6));

                ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane1 Check
                if((((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                    ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                    ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                    ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7))) &&
                   ((ucTP1SignalDetect & _BIT1) == _BIT1))
                {
                    if(g_ucDpRx0LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x10;
                        }
                        else if((ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F) > 12)
                        {
                            if((GET_DP_RX_D0_LANE1_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ((g_ucDpRx0LinkRequest01 >> 4) & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x10;
                            }
                            else
                            {
                                g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                                CLR_DP_RX_D0_LANE1_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x10;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                }

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

                ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                    ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                    ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                    ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7))) &&
                   ((ucTP1SignalDetect & _BIT0) == _BIT0))
                {
                    if(g_ucDpRx0LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F) > 12)
                        {
                            if((GET_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= (g_ucDpRx0LinkRequest01 & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                                CLR_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                break;

            case _DP_ONE_LANE:
            default:

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P17_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

                ScalerSetBit_EXINT(P17_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if((((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                    ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                    ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                    ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7))) &&
                   ((ucTP1SignalDetect & _BIT0) == _BIT0))
                {
                    if(g_ucDpRx0LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P17_F1_COEF_2) & 0x3F) > 12)
                        {
                            if((GET_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE) &&
                               ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= (g_ucDpRx0LinkRequest01 & (_BIT1 | _BIT0))))
                            {
                                g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                                CLR_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                    else
                    {
                        if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= ucTP1NormalLTSwingLevel))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                        }
                    }
                }
                else if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
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

                if((g_ucDpRx0LinkStatus01 & _BIT0) == _BIT0)
                {
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpRx0LinkStatus01 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))
                {
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpRx0LinkStatus01 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0)) && (((g_ucDpRx0LinkStatus23 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))))
                {
                    return _TRUE;
                }

                break;
        }
    }
    else
    {
        if((GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) && (GET_DP_RX0_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL))
        {
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0x03, 0x00);
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0x04, 0x00);
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0x05, 0x00);
            ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x01, 0x06, 0x00);
        }

        pucDpPhyLinkTrainingLevel[0] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pucDpPhyLinkTrainingLevel[1] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pucDpPhyLinkTrainingLevel[2] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pucDpPhyLinkTrainingLevel[3] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

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

        g_ucDpRx0LinkRequest01 = (pucDpPhyLinkTrainingLevel[0] & 0x03) | ((pucDpPhyLinkTrainingLevel[1] << 4) & 0x30);
        g_ucDpRx0LinkRequest23 = (pucDpPhyLinkTrainingLevel[2] & 0x03) | ((pucDpPhyLinkTrainingLevel[3] << 4) & 0x30);

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

                if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }
                }
                else
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }
                }

                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx0LinkRequest01);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == (ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0)))))
                {
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x01);

                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                    }
                }
                else
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                    }
                }

                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx0LinkRequest01);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if((((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == (ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0))))) &&
                   (((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) == (ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);

                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < ucTP1HBR2FakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                    }
                }
                else
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                    }

                    if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < ucTP1RBRHBRFakeLTSwingLevel))
                    {
                        g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                    }
                }

                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx0LinkRequest01);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx0LinkRequest23);

                if((((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) == ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT1 | _BIT0)))) &&
                   (((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) == (ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x06, (_BIT5 | _BIT4)) >> 4))) &&
                   (((pucDpPhyLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) == ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x07, (_BIT1 | _BIT0)))) &&
                   (((pucDpPhyLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) == (ScalerDpRx0GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x07, (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x11);

                    return _TRUE;
                }

                break;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal Detect Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpRx0Tp1SignalDetectCheck_EXINT0(BYTE ucDpLaneSel) using 1
{
    switch(g_ucDpRx0LinkRate)
    {
        case _DP_LINK_HBR2:

            if((g_pusDpRx0ClockCount[ucDpLaneSel] > _DP_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR2_EXINT0) ||
               (g_pusDpRx0ClockCount[ucDpLaneSel] < _DP_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR2_EXINT0))
            {
                return _FALSE;
            }

            break;

        case _DP_LINK_HBR:

            if((g_pusDpRx0ClockCount[ucDpLaneSel] > _DP_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR_EXINT0) ||
               (g_pusDpRx0ClockCount[ucDpLaneSel] < _DP_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR_EXINT0))
            {
                return _FALSE;
            }

            break;

        case _DP_LINK_RBR:

            if((g_pusDpRx0ClockCount[ucDpLaneSel] > _DP_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_RBR_EXINT0) ||
               (g_pusDpRx0ClockCount[ucDpLaneSel] < _DP_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_RBR_EXINT0))
            {
                return _FALSE;
            }

            break;

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpRx0Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    BYTE ucEQCRCStatus = 0;
    BYTE ucEQCRCStatus1 = 0;
    BYTE ucEQCRCStatus2 = 0;
    BYTE ucFakeLTLaneCount = g_ucDpRx0LaneCount;

    pData_EXINT[0] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
    pData_EXINT[1] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
    pData_EXINT[2] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
    pData_EXINT[3] = ScalerDpRx0GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        g_ucDpRx0LinkRequest01 = ((pData_EXINT[0] & 0x03) |
                                  ((pData_EXINT[0] >> 1) & 0x0C) |
                                  ((pData_EXINT[1] << 4) & 0x30) |
                                  ((pData_EXINT[1] << 3) & 0xC0));

        g_ucDpRx0LinkRequest23 = ((pData_EXINT[2] & 0x03) |
                                  ((pData_EXINT[2] >> 1) & 0x0C) |
                                  ((pData_EXINT[3] << 4) & 0x30) |
                                  ((pData_EXINT[3] << 3) & 0xC0));

        // Enable EQ-CRC and Clear EQ-CRC Status(- K28.5)
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [25,x]
        DELAY_25US_EXINT();

        ucEQCRCStatus1 = ScalerGetByte_EXINT(PB_12_EQ_CRC_1);

        if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
        {
            for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 30; g_ucDpRx0Temp++)
            {
                ucEQCRCStatus1 = ucEQCRCStatus1 & ScalerGetByte_EXINT(PB_12_EQ_CRC_1);
            }
        }
        else
        {
            for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 5; g_ucDpRx0Temp++)
            {
                ucEQCRCStatus1 = ucEQCRCStatus1 & ScalerGetByte_EXINT(PB_12_EQ_CRC_1);
            }
        }

        // Disable EQ-CRC
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Enable EQ-CRC and Clear EQ-CRC Status(+ K28.5)
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [25,x]
        DELAY_25US_EXINT();

        ucEQCRCStatus2 = ScalerGetByte_EXINT(PB_12_EQ_CRC_1);

        for(g_ucDpRx0Temp = 0; g_ucDpRx0Temp <= 5; g_ucDpRx0Temp++)
        {
            ucEQCRCStatus2 = ucEQCRCStatus2 & ScalerGetByte_EXINT(PB_12_EQ_CRC_1);
        }

        // Disable EQ-CRC
        ScalerSetBit_EXINT(PB_12_EQ_CRC_1, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        ucEQCRCStatus = (ucEQCRCStatus1 | ucEQCRCStatus2);

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

        switch(g_ucDpRx0LaneCount)
        {
            case _DP_FOUR_LANE:

                if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                {
                    if((ucEQCRCStatus & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != (_BIT3 | _BIT2 | _BIT1 | _BIT0))
                    {
                        ucEQCRCStatus &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
                    }
                }

                // Lane2 EQ-CRC Check
                if((ucEQCRCStatus & _BIT2) == _BIT2)
                {
                    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[2] & _BIT2) == _BIT2) || ((pData_EXINT[2] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x07;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x07;
                    }
                }
                else
                {
                    if(((g_ucDpRx0LinkRequest23 & 0x03) + ((g_ucDpRx0LinkRequest23 >> 2) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx0LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[2] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx0LinkRequest23 = g_ucDpRx0LinkRequest23 + 0x01;
                        }
                        else if((pData_EXINT[2] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx0LinkRequest23 = g_ucDpRx0LinkRequest23 + 0x04;
                        }
                    }
                }

                // Lane3 EQ-CRC Check
                if((ucEQCRCStatus & _BIT3) == _BIT3)
                {
                    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[3] & _BIT2) == _BIT2) || ((pData_EXINT[3] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x70;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xCF) | ((pData_EXINT[3] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else
                    {
                        g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x70;
                    }
                }
                else
                {
                    if((((g_ucDpRx0LinkRequest23 >> 4) & 0x03) + ((g_ucDpRx0LinkRequest23 >> 6) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx0LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[3] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx0LinkRequest23 = g_ucDpRx0LinkRequest23 + 0x10;
                        }
                        else if((pData_EXINT[3] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx0LinkRequest23 = g_ucDpRx0LinkRequest23 + 0x40;
                        }
                    }
                }

                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x70;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else
                    {
                        g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x70;
                    }
                }
                else
                {
                    if((((g_ucDpRx0LinkRequest01 >> 4) & 0x03) + ((g_ucDpRx0LinkRequest01 >> 6) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx0LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[1] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x10;
                        }
                        else if((pData_EXINT[1] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x40;
                        }
                    }
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x07;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x07;
                    }
                }
                else
                {
                    if(((g_ucDpRx0LinkRequest01 & 0x03) + ((g_ucDpRx0LinkRequest01 >> 2) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx0LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[0] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x01;
                        }
                        else if((pData_EXINT[0] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x04;
                        }
                    }
                }

                break;

            case _DP_TWO_LANE:

                if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                {
                    if((ucEQCRCStatus & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0))
                    {
                        ucEQCRCStatus &= ~(_BIT1 | _BIT0);
                    }
                }

                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x70;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else
                    {
                        g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x70;
                    }
                }
                else
                {
                    if((((g_ucDpRx0LinkRequest01 >> 4) & 0x03) + ((g_ucDpRx0LinkRequest01 >> 6) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx0LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[1] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x10;
                        }
                        else if((pData_EXINT[1] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x40;
                        }
                    }
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x07;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x07;
                    }
                }
                else
                {
                    if(((g_ucDpRx0LinkRequest01 & 0x03) + ((g_ucDpRx0LinkRequest01 >> 2) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx0LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[0] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x01;
                        }
                        else if((pData_EXINT[0] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x04;
                        }
                    }
                }

                break;

            case _DP_ONE_LANE:
            default:

                if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                {
                    if((ucEQCRCStatus & _BIT0) != _BIT0)
                    {
                        ucEQCRCStatus &= ~_BIT0;
                    }
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x07;
                        }
                        else
                        {
                            g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x07;
                    }
                }
                else
                {
                    if(((g_ucDpRx0LinkRequest01 & 0x03) + ((g_ucDpRx0LinkRequest01 >> 2) & 0x03)) < 3)
                    {
                        if(((g_ucDpRx0LinkRate == _DP_LINK_HBR2)) && ((pData_EXINT[0] & _BIT2) != _BIT2))
                        {
                            g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x01;
                        }
                        else if((pData_EXINT[0] & _BIT5) != _BIT5)
                        {
                            g_ucDpRx0LinkRequest01 = g_ucDpRx0LinkRequest01 + 0x04;
                        }
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

                if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
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

                if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
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

                if(g_ucDpRx0LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }

                    if(((pData_EXINT[2] & _BIT2) != _BIT2) && ((pData_EXINT[2] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[3] & _BIT2) != _BIT2) && ((pData_EXINT[3] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xCF) | ((pData_EXINT[3] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }
                else
                {
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

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
//--------------------------------------------------
// Description  : Lane Swap
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDpAltModeLaneMapping_EXINT0(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation) using 1
{
    // AUX Setting
    switch(enumPinAssignment)
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:

            // Configure to DP 4 Lane
            ScalerSetBit_EXINT(P1A_00_COMBO_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // reg_usb3_sel = 0 -> DP Mode Selection for DPHY
            ScalerSetBit_EXINT(P1C_24_DPHY_2, ~_BIT4, 0x00);

            if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // Pin 17 AUX-P Pull High / Pin 15 AUX-N Pull Low
                ScalerPinshareRx0TypeCPinAssert_EXINT0(_TYPE_C_ORIENTATION_UNFLIP);

                // Disable Aux APHY Swap
                ScalerSetBit_EXINT(PB7_66_AUX_6, ~_BIT7, 0x00);
            }
            else
            {
                // Pin 17 AUX-P Pull Low / Pin 15 AUX-N Pull High
                ScalerPinshareRx0TypeCPinAssert_EXINT0(_TYPE_C_ORIENTATION_FLIP);

                // Enable Aux APHY Swap
                ScalerSetBit_EXINT(PB7_66_AUX_6, ~_BIT7, _BIT7);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_D:

            // reg_usb3_sel = 1 -> USB3 Mode Selection for DPHY
            ScalerSetBit_EXINT(P1C_24_DPHY_2, ~_BIT4, _BIT4);

            if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // Pin 17 AUX-P Pull High / Pin 15 AUX-N Pull Low
                ScalerPinshareRx0TypeCPinAssert_EXINT0(_TYPE_C_ORIENTATION_UNFLIP);

                // Disable Aux APHY Swap
                ScalerSetBit_EXINT(PB7_66_AUX_6, ~_BIT7, 0x00);

                // Configure to 2 Lane DP (Lane2/3) + 2 Lane U3 (Lane0/1)
                ScalerSetBit_EXINT(P1A_00_COMBO_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

                // reg_usb3_lane_sel = 0 -> Select Lane0 as U3
                ScalerSetBit_EXINT(P1C_24_DPHY_2, ~_BIT5, 0x00);
            }
            else
            {
                // Pin 17 AUX-P Pull Low / Pin 15 AUX-N Pull High
                ScalerPinshareRx0TypeCPinAssert_EXINT0(_TYPE_C_ORIENTATION_FLIP);

                // Enable Aux APHY Swap
                ScalerSetBit_EXINT(PB7_66_AUX_6, ~_BIT7, _BIT7);

                // Configure to 2 Lane DP (Lane0/1) + 2 Lane U3 (Lane2/3)
                ScalerSetBit_EXINT(P1A_00_COMBO_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

                // reg_usb3_lane_sel = 1 -> Select Lane1 as U3
                ScalerSetBit_EXINT(P1C_24_DPHY_2, ~_BIT5, _BIT5);
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_E:

            // Configure to DP 4 Lane
            ScalerSetBit_EXINT(P1A_00_COMBO_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // reg_usb3_sel = 0 -> DP Mode Selection for DPHY
            ScalerSetBit_EXINT(P1C_24_DPHY_2, ~_BIT4, 0x00);

            if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // Pin 17 AUX-P Pull Low / Pin 15 AUX-N Pull High
                ScalerPinshareRx0TypeCPinAssert_EXINT0(_TYPE_C_ORIENTATION_FLIP);

                // Enable Aux APHY Swap
                ScalerSetBit_EXINT(PB7_66_AUX_6, ~_BIT7, _BIT7);
            }
            else
            {
                // Pin 17 AUX-P Pull High / Pin 15 AUX-N Pull Low
                ScalerPinshareRx0TypeCPinAssert_EXINT0(_TYPE_C_ORIENTATION_UNFLIP);

                // Disable Aux APHY Swap
                ScalerSetBit_EXINT(PB7_66_AUX_6, ~_BIT7, 0x00);
            }

            break;

        default:
        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            // Configure to USB 4 Lane
            ScalerSetBit_EXINT(P1A_00_COMBO_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // reg_usb3_sel = 1 -> USB3 Mode Selection for DPHY
            ScalerSetBit_EXINT(P1C_24_DPHY_2, ~_BIT4, _BIT4);

            // Pin 15/17 AUX-P Pull/Down Disable
            ScalerPinshareRx0TypeCPinAssert_EXINT0(_TYPE_C_ORIENTATION_NONE);

            // Disable Aux APHY Swap
            ScalerSetBit_EXINT(PB7_66_AUX_6, ~_BIT7, 0x00);

            if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // reg_usb3_lane_sel = 0 -> Select Lane0 as U3
                ScalerSetBit_EXINT(P1C_24_DPHY_2, ~_BIT5, 0x00);
            }
            else
            {
                // reg_usb3_lane_sel = 1 -> Select Lane2 as U3
                ScalerSetBit_EXINT(P1C_24_DPHY_2, ~_BIT5, _BIT5);
            }

            break;
    }
}
#endif // End of #if
#endif // End of #if(_D0_DP_EXIST == _ON)
