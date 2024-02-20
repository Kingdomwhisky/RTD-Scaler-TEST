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
// ID Code      : RL6369_Series_DPRx0_INT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6369_SERIES_DPRX0_INT__

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
void ScalerDpRx0IntHandler_EXINT0(void);
void ScalerDpRx0Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx0CMUNFCodeSetting_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef, EnumDpLinkRate enumLinkRate);
void ScalerDpRx0Tp2SetPhy_EXINT0(void);
BYTE ScalerDpRx0Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
void ScalerDpRx0SetDFEInitial_EXINT0(void);
BYTE ScalerDpRx0DFECheck_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx0RebuildPhy_WDINT(BYTE ucDpLinkRate, BYTE ucDpcdLane);
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
               (ScalerDpRx0DFECheck_EXINT0() == _FALSE))
            {
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);
                ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x05, 0x00);
            }
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

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef) using 1
{
    BYTE ucD0Z0Status = 0;
    BYTE ucD1Z0Status = 0;
    BYTE ucD2Z0Status = 0;


    ////////////////////
    // Mode Select DP //
    ////////////////////

    // Backup Z0 Status
    ucD0Z0Status = ScalerGetBit_EXINT(PB_B7_IMPEDANCE_00, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ucD1Z0Status = ScalerGetBit_EXINT(PB_B9_IMPEDANCE_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ucD2Z0Status = ScalerGetBit_EXINT(PB_BB_IMPEDANCE_04, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable Z0
    ScalerSetBit_EXINT(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [5] dp_mode = 1'b1 --> Select DP Mode
    // [4] en_mhl_op = 1'b0 --> Disable MHL OP
    ScalerSetBit_EXINT(PB_B6_BANDGAP_02, ~(_BIT5 | _BIT4), _BIT5);

    // Select DP
    ScalerSetBit_EXINT(PB_00_HD_DP_SEL, ~_BIT0, 0x00);

    // [4] PSM = 1'b0 --> Disable Clock Switch
    ScalerSetBit_EXINT(PB_B5_BANDGAP_01, ~_BIT4, 0x00);

#if(_DP_PORT_DISCONNECT_TERMINATION_AT_HDMI_MODE == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)    // DP Port
    ucD0Z0Status = (_BIT3 | _BIT2 | _BIT1 | _BIT0); // Enable Z0
    SET_DIGITAL_PORT_SWITCH_TO_D0();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)    // DP Port
    ucD1Z0Status = (_BIT3 | _BIT2 | _BIT1 | _BIT0); // Enable Z0
    SET_DIGITAL_PORT_SWITCH_TO_D1();
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)    // DP Port
    ucD2Z0Status = (_BIT3 | _BIT2 | _BIT1 | _BIT0); // Enable Z0
    SET_DIGITAL_PORT_SWITCH_TO_D2();
#endif
#endif

    // Restore Z0 Status
    ScalerSetBit_EXINT(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucD0Z0Status);
    ScalerSetBit_EXINT(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucD1Z0Status);
    ScalerSetBit_EXINT(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucD2Z0Status);


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

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


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT7, 0x00);

    // Disable RX_EN, CDR_EN
    ScalerSetByte_EXINT(PB_C0_CMU_03, 0x00);

    // Rx_en All Enable (Different from RL6193)
    ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Enable Local Bias LPF
    ScalerSetBit_EXINT(PB_B5_BANDGAP_01, ~_BIT3, _BIT3);

    // Delay Time us [25,x]
    DELAY_25US_EXINT();

    switch(g_ucDpRx0LaneCount)
    {
        case _DP_ONE_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable PHY Lane0 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable PHY Lane1 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable PHY Lane2 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT2, _BIT2);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // Enable PHY Lane3 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT3, _BIT3);
            }

            // DP 1-Lane Mode
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable PHY Lane0 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable PHY Lane1 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable PHY Lane2 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT2, _BIT2);
            }
            else if(GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // Enable PHY Lane3 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT3, _BIT3);
            }

            if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
            {
                // Enable PHY Lane0 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT0, _BIT0);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
            {
                // Enable PHY Lane1 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT1, _BIT1);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
            {
                // Enable PHY Lane2 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT2, _BIT2);
            }
            else if(GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
            {
                // Enable PHY Lane3 CDR_EN
                ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT3, _BIT3);
            }

            // DP 2-Lane Mode
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            // Enable Lane0-3 CDR_EN
            ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(PB_C0_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // DP 4-Lane Mode
            ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }

    if((g_ucDpRx0LaneCount != _DP_FOUR_LANE) && (ScalerGetBit_EXINT(PB_C0_CMU_03, _BIT0) == 0x00))
    {
        // Enable Lane0 CDR_EN
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT0, _BIT0);

        // Set Lane0 EN Phase = 0x3
        ScalerSetBit_EXINT(PB_E0_EN_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

        // Enable Lane0 PI Manual Mode
        ScalerSetBit_EXINT(PB_DB_TMDS_CONT_2, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable Lane0 PI Manual Mode
        ScalerSetBit_EXINT(PB_DB_TMDS_CONT_2, ~_BIT7, 0x00);
    }


    /////////////////
    // CMU Setting //
    /////////////////

    // [2] CMU_BYPASS_PI = 1'b0 --> Fractional N PLL
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT2, 0x00);

    // [7] BYPASS_PI = 1'b0 --> Use Fractional N_F_CODE
    ScalerSetBit_EXINT(PB_AE_SDM_04, ~_BIT7, 0x00);

    // [2:0] rate_sel = 3'b001 --> 1.5~3GHz
    ScalerSetBit_EXINT(PB_DC_TMDS_CONT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [2:0] SEL_DIV = 3'b001 --> 1.5~3GHz
    ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [5:4] CMU_SELPREDIV = 2'b00 --> /1
    ScalerSetBit_EXINT(PB_C5_CMU_08, ~(_BIT5 | _BIT4), 0x00);

    // [7] CMU_SEL_CP = 1'b0 --> Cp = 1pF
    // [6:4] CMU_PI_I_SEL = 3'b011 --> 12.5uA
    // [3:0] CMU_SEL_PUMP_I = 4'b0101 --> Icp = 15uA
    ScalerSetByte_EXINT(PB_C3_CMU_06, 0x35);

    // [6:4] CMU_SEL_RI = 3'b011 --> Rs = 12KOhm
    ScalerSetBit_EXINT(PB_C4_CMU_07, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

    if(g_ucDpRx0LinkRate == _DP_LINK_HBR)
    {
        ScalerDpRx0CMUNFCodeSetting_EXINT0(enumDpNFCodeRef, _DP_LINK_HBR);
    }
    else
    {
        ScalerDpRx0CMUNFCodeSetting_EXINT0(enumDpNFCodeRef, _DP_LINK_RBR);
    }


    //////////////////
    // DCDR Setting //
    //////////////////

    // KD = 0
    ScalerSetBit_EXINT(PB_F4_CDR_05, ~(_BIT7 | _BIT3), 0x00);
    ScalerSetBit_EXINT(PB_F5_CDR_06, ~(_BIT7 | _BIT3), 0x00);

    // KI = 3'b010 --> KI = 1/8
    ScalerSetBit_EXINT(PB_F4_CDR_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));
    ScalerSetBit_EXINT(PB_F5_CDR_06, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

    if(g_ucDpRx0LinkRate == _DP_LINK_HBR)
    {
        // KP = 0x1F --> KP = 7.75
        ScalerSetByte_EXINT(PB_F6_CDR_07, 0x1F);
        ScalerSetByte_EXINT(PB_F7_CDR_08, 0x1F);
        ScalerSetByte_EXINT(PB_F8_CDR_09, 0x1F);
        ScalerSetByte_EXINT(PB_F9_CDR_10, 0x1F);
    }
    else
    {
        // KP = 0x37 --> KP = 13.75
        ScalerSetByte_EXINT(PB_F6_CDR_07, 0x37);
        ScalerSetByte_EXINT(PB_F7_CDR_08, 0x37);
        ScalerSetByte_EXINT(PB_F8_CDR_09, 0x37);
        ScalerSetByte_EXINT(PB_F9_CDR_10, 0x37);
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // Disable Comma Detection
    ScalerSetBit_EXINT(PB_05_SAMPLE_EDGE, ~_BIT4, _BIT4);

    // Disable De-Scrambling
    ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

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

    // [0] en_clkout_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB_AE_SDM_04, ~_BIT0, 0x00);

    // [0] en_eqen_manual = 0 --> Disable Eqen
    ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 0 --> Disable Dataout
    ScalerSetBit_EXINT(PB_B1_DATA_TIMER, ~_BIT0, 0x00);

    // Disable Hybrid Mode
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT7, 0x00);

    // [7:4] RST_N = 4'b0000 --> Digital Circuit Reset
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [7:4] RST_N = 4'b1111 --> Digital Circuit Normal
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));


    /////////////////
    // DFE Setting //
    /////////////////

    // Set DFE Initial
    ScalerDpRx0SetDFEInitial_EXINT0();

    if(g_ucDpRx0LinkRate == _DP_LINK_HBR)
    {
        // [7:5] LE_RLSEL = 3'b001
        // [7:5] LE_ISEL = 3'b010
        ScalerSetBit_EXINT(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
        ScalerSetBit_EXINT(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
    }
    else
    {
        // [7:5] LE_RLSEL = 3'b011
        // [7:5] LE_ISEL = 3'b000
        ScalerSetBit_EXINT(PB_CD_KOFFSET_07, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));
        ScalerSetBit_EXINT(PB_CC_KOFFSET_06, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }


    //////////////
    // K Offset //
    //////////////

    // Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(PB_C9_KOFFSET_03, ~_BIT6, 0x00);

    // [6] Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT6, _BIT6);

    // [7] Toggle Foreground Calibration
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x] Waiting for K Offset
    DELAY_XUS_EXINT(85);


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT7, _BIT7);

    // Enable Tap1/2
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // [6] reg_en_ana_cdr = 1'b0 --> Disable Analog CDR
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT6, 0x00);

    // [4] reg_acdr_l0_en = 1'b0 --> Disable Lane0 ACDR
    ScalerSetBit_EXINT(PB_B2_ANA_CDR, ~_BIT4, 0x00);

    // Enable Vth/Tap0 Adaptation
    ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x41);

    // Reset Digital CDR
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for CMU PLL Stable
    DELAY_25US_EXINT();

    // [0] en_clkout_manual = 1 --> Enable Clkout
    ScalerSetBit_EXINT(PB_AE_SDM_04, ~_BIT0, _BIT0);

    // [0] en_eqen_manual = 1 --> Enable Adapation
    ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, _BIT0);

    // Delay Time us [85,x] Waiting for DFE Adaptation
    DELAY_XUS_EXINT(85);

    // Start to Record Tap0 Max/Min
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [85,x] Waiting for DFE Adaptation
    DELAY_XUS_EXINT(85);

    // Stop To Record Tap0 Max/Min
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~_BIT0, 0x00);

    // Disable All Adapation Loop
    ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x00);

    // Read Back Tap0 Max
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    // Reload Max Value of Tap0 (Lane0)
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, ScalerGetByte_EXINT(P1D_F3_COEF_4));

    // Reload Max Value of Tap0 (Lane1)
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetByte_EXINT(P1D_B4_L1_INIT_2, ScalerGetByte_EXINT(P1D_F3_COEF_4));

    // Reload Max Value of Tap0 (Lane2)
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetByte_EXINT(P1D_C4_L2_INIT_2, ScalerGetByte_EXINT(P1D_F3_COEF_4));

    // Reload Max Value of Tap0 (Lane3)
    ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetByte_EXINT(P1D_D4_L3_INIT_2, ScalerGetByte_EXINT(P1D_F3_COEF_4));

    // Reload Tap0
    ScalerSetBit_EXINT(P1D_AA_L0_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P1D_BA_L1_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P1D_CA_L2_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P1D_DA_L3_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P1D_AA_L0_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P1D_BA_L1_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P1D_CA_L2_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P1D_DA_L3_INIT_8, ~_BIT0, 0x00);

    // [0] en_eqen_manual = 1'b0 --> Disable Adaptation for Digital CDR
    ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 1 --> Enable Dataout
    ScalerSetBit_EXINT(PB_B1_DATA_TIMER, ~_BIT0, _BIT0);

    // DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : DP CDR N.F. Code Setting
// Input Value  : Link Rate and N.F. Code Clock Ref.
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0CMUNFCodeSetting_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef, EnumDpLinkRate enumLinkRate) using 1
{
    WORD usCMUNCode = 0;
    WORD usCMUFCode = 0;
    WORD usCount = 0;
    DWORD ulFreqDetect = 0;

    if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
    {
        if(enumLinkRate == _DP_LINK_RBR)
        {
            usCMUNCode = 109;     // N_Code = 0x06D
            usCMUFCode = 591;     // F_Code = 0x24F
        }
        else  // HBR HBR2
        {
            usCMUNCode = 184;     // N_Code = 0x0B8
            usCMUFCode = 2350;    // N_Code = 0x92E
        }
    }
    else     // Ref. D10.2 Clock
    {
        // [5] ln_ck_sel = 1'b0 -> DP Raw Data
        // [3:0] DP_XTAL_CYCLE = 4'b0011 -> XTAL Counter Cycles = 1000
        ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

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

        switch(enumLinkRate)
        {
            case _DP_LINK_HBR:

                if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usCount = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

                    ulFreqDetect = (((DWORD)usCount * 2700) / 5003) * 100000;

                    usCMUNCode = ((ulFreqDetect / 14318) - 400) / 100;
                    usCMUFCode = (((ulFreqDetect / 14318) - 400) - (usCMUNCode * 100)) * 4096 / 100;
                }
                else
                {
                    usCMUNCode = 184;
                    usCMUFCode = 2350;
                }

                break;

            case _DP_LINK_RBR:
            default:

                if(ScalerGetBit_EXINT(PB_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usCount = ((((WORD)ScalerGetByte_EXINT(PB_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB_54_DP_SIG_DET_4));

                    ulFreqDetect = (((DWORD)usCount * 1620) / 3002) * 100000;

                    usCMUNCode = ((ulFreqDetect / 14318) - 400) / 100;
                    usCMUFCode = (((ulFreqDetect / 14318) - 400) - (usCMUNCode * 100)) * 4096 / 100;
                }
                else
                {
                    usCMUNCode = 109;
                    usCMUFCode = 591;
                }

                break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // [0] N_CODE[8]
    ScalerSetBit_EXINT(PB_AB_SDM_01, ~_BIT0, ((usCMUNCode >> 8) & _BIT0));

    // [7:0] N_CODE[7:0]
    ScalerSetByte_EXINT(PB_AC_SDM_02, (BYTE)usCMUNCode);

    // [4:1] F_CODE[11:8]
    ScalerSetBit_EXINT(PB_AB_SDM_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((usCMUFCode >> 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)));

    // [7:0] F_CODE[7:0]
    ScalerSetByte_EXINT(PB_AD_SDM_03, (BYTE)usCMUFCode);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0Tp2SetPhy_EXINT0(void) using 1
{
    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT7, 0x00);

    // Enable Comma Detection
    ScalerSetBit_EXINT(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    // Disable De-Scrambling
    ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

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

    // [0] en_clkout_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB_AE_SDM_04, ~_BIT0, 0x00);

    // [0] en_eqen_manual = 0 --> Disable Eqen
    ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 0 --> Disable Dataout
    ScalerSetBit_EXINT(PB_B1_DATA_TIMER, ~_BIT0, 0x00);

    // Disable Hybrid Mode
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT7, 0x00);

    // [7:4] RST_N = 4'b0000 --> Digital Circuit Reset
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [7:4] RST_N = 4'b1111 --> Digital Circuit Normal
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT7, _BIT7);

    // Enable Tap0/Vth/LE/Tap1/Tap2 Adaptation
    ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0xC7);
    ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0xC7);
    ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0xC7);
    ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0xC7);

    // Reset Digital CDR
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for CMU PLL Stable
    DELAY_25US_EXINT();

    // [0] en_clkout_manual = 1 --> Enable Clkout
    ScalerSetBit_EXINT(PB_AE_SDM_04, ~_BIT0, _BIT0);

    // [0] en_eqen_manual = 1 --> Enable Adapation
    ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, _BIT0);

    // Delay Time us [300,x] Waiting for DFE Adaptation
    DELAY_XUS_EXINT(300);

    // Only Enable Vth/Tap0 Adapation
    ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x41);

    // [0] en_data_manual = 1 --> Enable Dataout
    ScalerSetBit_EXINT(PB_B1_DATA_TIMER, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpRx0Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    BYTE pucDpPhyLinkTrainingLevel[4];
    BYTE pucDpPhyLinkTrainingRequest[4];
    BYTE ucFakeLTLaneCount = g_ucDpRx0LaneCount;

    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx0SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

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
                ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _D0_DP_LANE3 << 6);

                ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane3 Check
                if(((GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX0_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x10;
                    }
                    else if((ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F) > 4)
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
                else if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
                }

                // Read Back Lane2 Vth
                ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _D0_DP_LANE2 << 6);

                ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane2 Check
                if(((GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX0_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx0LinkStatus23 = g_ucDpRx0LinkStatus23 | 0x01;
                    }
                    else if((ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F) > 4)
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
                else if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                }

                // Read Back Lane1 Vth
                ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _D0_DP_LANE1 << 6);

                ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane1 Check
                if(((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x10;
                    }
                    else if((ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F) > 4)
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
                else if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                }

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _D0_DP_LANE0 << 6);

                ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if(((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                    }
                    else if((ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F) > 4)
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
                else if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                break;

            case _DP_TWO_LANE:

                // Read Back Lane1 Vth
                ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _D0_DP_LANE1 << 6);

                ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane1 Check
                if(((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX0_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x10;
                    }
                    else if((ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F) > 4)
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
                else if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                }

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _D0_DP_LANE0 << 6);

                ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if(((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                    }
                    else if((ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F) > 4)
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
                else if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                break;

            case _DP_ONE_LANE:
            default:

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), _D0_DP_LANE0 << 6);

                ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if(((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX0_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) == _BIT2) || ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx0LinkStatus01 = g_ucDpRx0LinkStatus01 | 0x01;
                    }
                    else if((ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F) > 4)
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

                if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
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

                if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
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

                if(((pucDpPhyLinkTrainingLevel[0] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[0] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xFC) | pucDpPhyLinkTrainingRequest[0]);
                }

                if(((pucDpPhyLinkTrainingLevel[1] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[1] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx0LinkRequest01 = ((g_ucDpRx0LinkRequest01 & 0xCF) | pucDpPhyLinkTrainingRequest[1]);
                }

                if(((pucDpPhyLinkTrainingLevel[2] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[2] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xFC) | pucDpPhyLinkTrainingRequest[2]);
                }

                if(((pucDpPhyLinkTrainingLevel[3] & _BIT2) != _BIT2) && ((pucDpPhyLinkTrainingLevel[3] & (_BIT1 | _BIT0)) < _BIT0))
                {
                    g_ucDpRx0LinkRequest23 = ((g_ucDpRx0LinkRequest23 & 0xCF) | pucDpPhyLinkTrainingRequest[3]);
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
// Description  : DP PHY DFE Initial Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0SetDFEInitial_EXINT0(void) using 1
{
    // [7] Positive Symbol-Rate Clock
    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [3] Disable Running Length Detection
    // [2] bypass Blank out Case-3 Symbol
    ScalerSetBit_EXINT(P1D_A0_L0_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P1D_B0_L1_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P1D_C0_L2_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P1D_D0_L3_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));

    // [7:6] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetByte_EXINT(P1D_E0_MODE_TIMER, 0xB2);

    // Set DFE Delay Time
    ScalerSetByte_EXINT(P1D_E1_TIMER, 0x01);

    // Tap0,Tap1 Loop Gain 1/512
    ScalerSetBit_EXINT(P1D_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap2,Tap3 Loop Gain 1/512
    ScalerSetBit_EXINT(P1D_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4,Servo Loop Gain 1/512
    ScalerSetBit_EXINT(P1D_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // LE Gain1 Loop Gain 1/256, LE Gain2 Loop Gain 0, LE Pre-Courser Gain 0
    ScalerSetBit_EXINT(P1D_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit_EXINT(P1D_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap0 Max is 21
    ScalerSetByte_EXINT(P1D_E6_LIMIT_1, 0x35);

    // Tap1 Min is 31
    ScalerSetBit_EXINT(P1D_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Tap2 Max is 6, Min is -6
    ScalerSetBit_EXINT(P1D_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(P1D_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P1D_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 0, Min is -3
    ScalerSetBit_EXINT(P1D_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 0, Min is -3
    ScalerSetBit_EXINT(P1D_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_EB_LIMIT_6, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P1D_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Tap0 Threshold
    ScalerSetBit_EXINT(P1D_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // Set Vth Max = 6, Min = 0
    ScalerSetByte_EXINT(P1D_F9_LIMIT_10, 0x60);

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetByte_EXINT(P1D_EC_LOOP_DIV_1, 0xA3);

    // Tap Divider = 10 for TP2
    ScalerSetByte_EXINT(P1D_ED_LOOP_DIV_2, 0xCA);

    // [5] servo_notrans = 1'b0 --> Servo is Effective Each Bit
    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective Each Bit
    ScalerSetBit_EXINT(P1D_F8_GRAY_DEC_2, ~(_BIT5 | _BIT4), 0x00);


    /////////////////////////
    // DFE Code Initialize //
    /////////////////////////

    // LE Max = 20, Initial = 12, Servo Initial = 16
    ScalerSetByte_EXINT(P1D_A2_L0_LIMIT_INIT, 0x4C);
    ScalerSetByte_EXINT(P1D_B2_L1_LIMIT_INIT, 0x4C);
    ScalerSetByte_EXINT(P1D_C2_L2_LIMIT_INIT, 0x4C);
    ScalerSetByte_EXINT(P1D_D2_L3_LIMIT_INIT, 0x4C);
    ScalerSetByte_EXINT(P1D_A3_L0_INIT_1, 0x90);
    ScalerSetByte_EXINT(P1D_B3_L1_INIT_1, 0x90);
    ScalerSetByte_EXINT(P1D_C3_L2_INIT_1, 0x90);
    ScalerSetByte_EXINT(P1D_D3_L3_INIT_1, 0x90);

    // Tap0 Initial Value = 12
    ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, 0x0C);
    ScalerSetByte_EXINT(P1D_B4_L1_INIT_2, 0x0C);
    ScalerSetByte_EXINT(P1D_C4_L2_INIT_2, 0x0C);
    ScalerSetByte_EXINT(P1D_D4_L3_INIT_2, 0x0C);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P1D_A5_L0_INIT_3, 0x00);
    ScalerSetByte_EXINT(P1D_B5_L1_INIT_3, 0x00);
    ScalerSetByte_EXINT(P1D_C5_L2_INIT_3, 0x00);
    ScalerSetByte_EXINT(P1D_D5_L3_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(P1D_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P1D_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P1D_C6_L2_INIT_4, 0x00);
    ScalerSetByte_EXINT(P1D_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 6
    ScalerSetByte_EXINT(P1D_A9_L0_INIT_7, 0x06);
    ScalerSetByte_EXINT(P1D_B9_L1_INIT_7, 0x06);
    ScalerSetByte_EXINT(P1D_C9_L2_INIT_7, 0x06);
    ScalerSetByte_EXINT(P1D_D9_L3_INIT_7, 0x06);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P1D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x00);
}

//--------------------------------------------------
// Description : check DFE Coef in INT0
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpRx0DFECheck_EXINT0(void) using 1
{
    switch(g_ucDpRx0LaneCount)
    {
        case _DP_FOUR_LANE:

            // Read Lane2 DFE
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane3 DFE
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P1D_F2_COEF_3, ~(_BIT7 | _BIT6), (_D0_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P1D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P1D_F1_COEF_2) & 0x1F);

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

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Rebuilding DP PHY in WD INT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx0RebuildPhy_WDINT(BYTE ucDpLinkRate, BYTE ucDpcdLane) using 3
{
    ucDpLinkRate = ucDpLinkRate;
    ucDpcdLane = ucDpcdLane;

    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT7, 0x00);

    if((ScalerDpRx0GetDpcdInfo_WDINT(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
    {
        // Disable Scrambling
        ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // Enable Scrambling
        ScalerSetBit_EXINT(PB_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
    }

    // [0] en_clkout_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB_AE_SDM_04, ~_BIT0, 0x00);

    // [0] en_eqen_manual = 0 --> Disable Eqen
    ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 0 --> Disable Dataout
    ScalerSetBit_EXINT(PB_B1_DATA_TIMER, ~_BIT0, 0x00);

    // Disable Hybrid Mode
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT7, 0x00);

    // [7:4] RST_N = 4'b0000 --> Digital Circuit Reset
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [7:4] RST_N = 4'b1111 --> Digital Circuit Normal
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));


    /////////////////
    // DFE Setting //
    /////////////////

    // Tap Divider = 10 for TP2
    ScalerSetByte_EXINT(P1D_ED_LOOP_DIV_2, 0xCA);

    // Tap0 Initial Value = 12
    ScalerSetByte_EXINT(P1D_A4_L0_INIT_2, 0x0C);
    ScalerSetByte_EXINT(P1D_B4_L1_INIT_2, 0x0C);
    ScalerSetByte_EXINT(P1D_C4_L2_INIT_2, 0x0C);
    ScalerSetByte_EXINT(P1D_D4_L3_INIT_2, 0x0C);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P1D_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P1D_DA_L3_INIT_8, 0x00);

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

    // Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(PB_C9_KOFFSET_03, ~_BIT6, 0x00);

    // [6] Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT6, _BIT6);

    // [7] Toggle Foreground Calibration
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT7, _BIT7);

    // Delay Time us [85,x] Waiting for K Offset
    DELAY_XUS_EXINT(85);


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(PB_C1_CMU_04, ~_BIT7, _BIT7);

    // Enable Tap1/2/3/4
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT3 | _BIT2 | _BIT1));

    // [6] reg_en_ana_cdr = 1'b0 --> Disable Analog CDR
    ScalerSetBit_EXINT(PB_CE_ANA_CDR_00, ~_BIT6, 0x00);

    // [4] reg_acdr_l0_en = 1'b0 --> Disable Lane0 ACDR
    ScalerSetBit_EXINT(PB_B2_ANA_CDR, ~_BIT4, 0x00);

    // Enable LE/Vth/Tap0/Tap1/Tap2
    ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0xC7);
    ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0xC7);
    ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0xC7);
    ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0xC7);

    // Reset Digital CDR
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [25,x] Waiting for CMU PLL Stable
    DELAY_25US_EXINT();

    // [0] en_clkout_manual = 1 --> Enable Clkout
    ScalerSetBit_EXINT(PB_AE_SDM_04, ~_BIT0, _BIT0);

    // [0] en_eqen_manual = 1 --> Enable Adapation
    ScalerSetBit_EXINT(PB_B0_EQEN_TIMER, ~_BIT0, _BIT0);

    // Delay Time us [300,x] Waiting for DFE Adaptation
    DELAY_XUS_EXINT(300);

    // Enable Vth/Tap0 Adaptation
    ScalerSetByte_EXINT(P1D_A1_L0_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_B1_L1_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_C1_L2_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P1D_D1_L3_DFE_EN_2, 0x41);

    // [0] en_data_manual = 1 --> Enable Dataout
    ScalerSetBit_EXINT(PB_B1_DATA_TIMER, ~_BIT0, _BIT0);

    // DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}
#endif

#endif // End of #if(_DP_SUPPORT == _ON)
