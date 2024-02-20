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
// ID Code      : RL6449_Series_DPRx1_INT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6449_SERIES_DPRX1_INT__

#include "ScalerFunctionInclude.h"

#if(_D1_DP_EXIST == _ON)

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
void ScalerDpRx1Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx1Tp2SetPhy_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx1RebuildPhy_WDINT(BYTE ucDpLinkRate);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef) using 1
{
    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

    // DP Lane Swap Setting
    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), _D1_DP_LANE3 << 6);
    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), _D1_DP_LANE2 << 4);
    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), _D1_DP_LANE1 << 2);
    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

    // [1:0] DP Mac Clock Selection
    ScalerSetBit_EXINT(PB0_96_DUMMY3, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

    // DP Lane PN Swap Setting
    ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~_BIT7, GET_DP_RX1_PCB_LANE3_PN_SWAP() << 7);
    ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~_BIT6, GET_DP_RX1_PCB_LANE2_PN_SWAP() << 6);
    ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~_BIT5, GET_DP_RX1_PCB_LANE1_PN_SWAP() << 5);
    ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~_BIT4, GET_DP_RX1_PCB_LANE0_PN_SWAP() << 4);


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

    // Digital PHY Block Power Normal
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF)

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(P7A_1B_CMU_01, ~_BIT7, 0x00);

    // [7:4] Rx_en = 4'b0000 -> Disable RX_EN
    // [3:0] CDR_en = 4'b0000 -> Disable CDR_EN
    ScalerSetByte_EXINT(P7A_1A_CMU_00, 0x00);

    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT0, _BIT0);

                // [7:6] reg_en_ana_cdr = 4'b0001 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~(_BIT7 | _BIT6), 0x00);
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~(_BIT7 | _BIT6), _BIT6);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT1, _BIT1);

                // [7:6] reg_en_ana_cdr = 4'b0010 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~(_BIT7 | _BIT6), 0x00);
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~(_BIT7 | _BIT6), _BIT7);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT2, _BIT2);

                // [7:6] reg_en_ana_cdr = 4'b0100 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~(_BIT7 | _BIT6), _BIT6);
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~(_BIT7 | _BIT6), 0x00);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT3, _BIT3);

                // [7:6] reg_en_ana_cdr = 4'b1000 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~(_BIT7 | _BIT6), _BIT7);
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~(_BIT7 | _BIT6), 0x00);
            }

            // [4:3] DP Mac Select One Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT0, _BIT0);

                // [6] reg_en_ana_cdr[0] = 1 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT1, _BIT1);

                // [7] reg_en_ana_cdr[1] = 1 --> Enable Lane1 Analog CDR
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~_BIT7, _BIT7);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT2, _BIT2);

                // [6] reg_en_ana_cdr[2] = 1 --> Enable Lane2 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT3, _BIT3);

                // [7] reg_en_ana_cdr[3] = 1 --> Enable Lane3 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~_BIT7, _BIT7);
            }

            if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT0, _BIT0);

                // [6] reg_en_ana_cdr[0] = 1 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT1, _BIT1);

                // [7] reg_en_ana_cdr[1] = 1 --> Enable Lane1 Analog CDR
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~_BIT7, _BIT7);
            }
            else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT2, _BIT2);

                // [6] reg_en_ana_cdr[2] = 1 --> Enable Lane2 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT3, _BIT3);

                // [7] reg_en_ana_cdr[3] = 1 --> Enable Lane3 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~_BIT7, _BIT7);
            }

            // [4:3] DP Mac Select Two Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            // [7:4] Enable Lane0~3 Rx_en
            ScalerSetBit_EXINT(P7A_1A_CMU_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // [3:0] Enable Lane0~3 CDR_en
            ScalerSetBit_EXINT(P7A_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(P7A_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit_EXINT(P7A_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P7A_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // [7:6] reg_en_ana_cdr = 4'b1111 --> Enable Lane0~3 Analog CDR
            ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // [4:3] DP Mac Select Four Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }
#else
    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            // [4:3] DP MAC Select One Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            // [4:3] DP MAC Select Four Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }
#endif

    ///////////////////////
    // Frequency Setting //
    ///////////////////////

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // [7:5] rate_sel = 3'b000 --> 3~6GHz
        ScalerSetBit_EXINT(P7A_44_ST_01, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [2:0] SEL_DIV = 3'b000 --> 3~6GHz
        ScalerSetBit_EXINT(P7A_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // [7:5] rate_sel = 3'b001 --> 1.5~3GHz
        ScalerSetBit_EXINT(P7A_44_ST_01, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // [2:0] SEL_DIV = 3'b001 --> 1.5~3GHz
        ScalerSetBit_EXINT(P7A_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
    {
        // [3] reg_xtal_en = 1'b1 --> Using 27M Xtal
        ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT3, _BIT3);

        if(g_ucDpRx1LinkRate == _DP_LINK_RBR)
        {
            // Analog CDR Auto FLD Counter
            // 0x2D[1] 0x2E --> ref_conuter = 25
            // 0x2D[0] 0x2F --> cdr_counter = 300
            // 25/300 = 1/12 = 5*(27M/1.62G)
            ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(P7A_2E_ANA_CDR_03, 0x18);
            ScalerSetByte_EXINT(P7A_2F_ANA_CDR_04, 0x2B);
        }
        else
        {
            // Analog CDR Auto FLD Counter
            // 0x2D[1] 0x2E --> ref_conuter = 25
            // 0x2D[0] 0x2F --> cdr_counter = 500
            // 25/500 = 1/20 = 5*(27M/2.7G)
            ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(P7A_2E_ANA_CDR_03, 0x18);
            ScalerSetByte_EXINT(P7A_2F_ANA_CDR_04, 0xF3);
        }
    }
    else
    {
        // [3] reg_xtal_en = 1'b0 --> Using D10.2 Clock
        ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT3, 0x00);

        // Analog CDR Auto FLD Counter
        // ref_conuter = 125
        // cdr_counter = 250
        // 250/500 = 1/2 = 5*(D10.2_clock / data_rate)
        ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_2E_ANA_CDR_03, 0x7C);
        ScalerSetByte_EXINT(P7A_2F_ANA_CDR_04, 0xF9);
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [4] Disable Comma Detection
    ScalerSetBit_EXINT(PB0_05_SAMPLE_EDGE, ~_BIT4, _BIT4);

    // [5] Disable De-Scrambling
    ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // [2] Enable Enhancement Control Mode
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // [2] Disable Enhancement Control Mode
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

    // [7:4] RST_N = 4'b0000 = 4'b1111 --> Digital Circuit Reset Toggle
    // [3:0] CDR_RST_N = 4'b0000 --> Disable DCDR
    ScalerSetByte_EXINT(P7A_3A_TMDS_RESET, 0x00);
    ScalerSetByte_EXINT(P7A_3A_TMDS_RESET, 0xF0);


    //////////////////
    // ACDR Setting //
    //////////////////

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // [7] reg_sel_CDR_cp = 0 --> Disable CDR Loop's CP (1nF)
        // [6:4] reg_sel_cdr_res = 3'b010 --> Analog CDR Rs = 1.5K
        // [3:0] reg_cdr_cp_in = 4'b0010 --> Analog CDR Icp = 7.5uA
        ScalerSetByte_EXINT(P7A_31_ANA_CDR_06, 0x22);

        // [0] Half_PD = 1 --> Half Rate PD
        ScalerSetBit_EXINT(P7A_39_ANA_CDR_14, ~_BIT7, _BIT7);
    }
    else
    {
        // [7] reg_sel_CDR_cp = 0 --> Disable CDR Loop's CP (1nF)
        // [6:4] reg_sel_cdr_res = 3'b100 --> Analog CDR Rs = 4K
        // [3:0] reg_cdr_cp_in = 4'b0101 --> Analog CDR Icp = 16.5uA
        ScalerSetByte_EXINT(P7A_31_ANA_CDR_06, 0x45);

        // [0] Half_PD = 0 --> Full Rate PD
        ScalerSetBit_EXINT(P7A_39_ANA_CDR_14, ~_BIT7, 0x00);
    }


    /////////////////
    // DFE Setting //
    /////////////////

    // [7:3] Tap_EN = 5'b11111 --> Enable Tap0~4
    ScalerSetBit_EXINT(P7A_21_CMU_07, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

    // Set DFE Initial
    ScalerDpRx1SetDFEInitial_EXINT0();

    // [4] en_sumamp_highgain = 0 --> Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(P7A_1D_CMU_03, ~_BIT4, 0x00);

    switch(g_ucDpRx1LinkRate)
    {
        case _DP_LINK_HBR2:

            // LE Peaking = 3GHz
            // [7:5] LE_RLSEL = 3'b000
            // [4:2] LE_ISEL = 3'b011
            ScalerSetBit_EXINT(P7A_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

            break;

        case _DP_LINK_HBR:

            // LE Peaking = 1.7GHz
            // [7:5] LE_RLSEL = 3'b001
            // [4:2] LE_ISEL = 3'b010
            ScalerSetBit_EXINT(P7A_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            break;

        case _DP_LINK_RBR:
        default:

            // LE Peaking = 900MHz
            // [7:5] LE_RLSEL = 3'b011
            // [4:2] LE_ISEL = 3'b000
            ScalerSetBit_EXINT(P7A_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            break;
    }


    //////////////
    // K Offset //
    //////////////

    // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT5, _BIT5);

    // [6] en_fore_offset --> Toggle Foreground Calibration
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, 0x00);
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);

    // Delay Time us [85,x] Waiting for K Offset
    DELAY_XUS_EXINT(85);


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(P7A_1B_CMU_01, ~_BIT7, _BIT7);

    // [7] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

    // [2] reg_rstb_fsm --> FLD Reset
    ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, 0x00);

    // [1] reg_en_eqen_manual_l0 = 1'b1
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT1, _BIT1);

    // Enable Vth/Tap0 Adaptation
    ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x41);

    // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
    ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, _BIT2);

    // Delay Time us [85,x] Waiting for FLD Lock Band
    DELAY_XUS_EXINT(85);

    // Start to Record Tap0 Max/Min
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [85,x] Waiting for DFE Adaptation
    DELAY_XUS_EXINT(85);

    // Stop To Record Tap0 Max/Min
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

    // [1] reg_en_eqen_manual_l0 = 1'b0 --> DFE Adaptation Off
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT1, 0x00);

    // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT4, _BIT4);

    // Disable All Adapation Loop
    ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);

    // Read Back Tap0 Max
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    // Reload Max Value of Tap0 (Lane0)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane1)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane2)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane3)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetByte_EXINT(P7A_D4_L3_INIT_2, (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F));

    // Reload Tap0
    ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, 0x00);

    // [3] reg_en_data_manual_l0 = 1'b1 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    /////////////////////////
    // D10.2 Clock Measure //
    /////////////////////////

    // [7:4] reg_en_sigdet_lane = 4'b1111 --> Enable Signal Detection for D10.2
    ScalerSetBit_EXINT(P7A_19_IMPEDANCE_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [5] ln_ck_sel = 1'b0 -> DP Raw Data
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit_EXINT(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

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
        g_pusDpRx1ClockCount[0] = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));
    }
    else
    {
        switch(g_ucDpRx1LinkRate)
        {
            case _DP_LINK_HBR2:

                g_pusDpRx1ClockCount[0] = 0x2710;

                break;

            case _DP_LINK_HBR:

                g_pusDpRx1ClockCount[0] = 0x1388;

                break;

            default:
            case _DP_LINK_RBR:

                g_pusDpRx1ClockCount[0] = 0xBB8;

                break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    g_pusDpRx1ClockCount[3] = g_pusDpRx1ClockCount[0];
    g_pusDpRx1ClockCount[2] = g_pusDpRx1ClockCount[0];
    g_pusDpRx1ClockCount[1] = g_pusDpRx1ClockCount[0];
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Tp2SetPhy_EXINT0(void) using 1
{
    WORD usVCOBandDiff = 0;
    WORD usVCOBandScan = 0;
    BYTE ucIcp = (ScalerGetByte_EXINT(P7A_31_ANA_CDR_06) & 0x0F);

    /////////////
    // Rx Misc //
    /////////////

    // Digital PHY Block Power Normal
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(P7A_1B_CMU_01, ~_BIT7, 0x00);

    // [4] Enable Comma Detection
    ScalerSetBit_EXINT(PB0_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    // [5] Disable De-Scrambling
    ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // [2] Enable Enhancement Control Mode
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // [2] Disable Enhancement Control Mode
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

    // [7:4] RST_N = 4'b0000 = 4'b1111 -->Digital Circuit Reset Toggle
    // [3:0] CDR_RST_N = 4'b0000 --> Disable DCDR
    ScalerSetByte_EXINT(P7A_3A_TMDS_RESET, 0x00);
    ScalerSetByte_EXINT(P7A_3A_TMDS_RESET, 0xF0);

    // [4] en_sumamp_highgain = 0 --> Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(P7A_1D_CMU_03, ~_BIT4, 0x00);

    // Set DFE Initial
    ScalerDpRx1SetDFEInitial_EXINT0();


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(P7A_1B_CMU_01, ~_BIT7, _BIT7);

    // [7] reg_auto_mode = 1'b1 --> FLD Auto Mode
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

    // [2] reg_rstb_fsm --> FLD Reset
    ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, 0x00);

    // [1] reg_en_eqen_manual_l0 = 1'b1 --> DFE Adaptation Enable
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT1, _BIT1);

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // Enable Vth/LE/Tap0~4
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0xDF);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [150,x] Waiting for FLD Lock Band
        DELAY_XUS_EXINT(150);

        // [1] reg_en_eqen_manual_l0 = 1'b0 --> DFE Adaptation Off
        ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT1, 0x00);

        // Disable LE/Vth/Tap0~4
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);

        // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
        ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT4, _BIT4);


        //////////////
        // K Offset //
        //////////////

        // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT5, _BIT5);

        // [6] en_fore_offset --> Toggle Foreground Calibration
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, 0x00);
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);

        // Delay Time us [85,x] Waiting for DFE Adaptation
        DELAY_XUS_EXINT(85);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0xC7);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [300,x] Waiting for FLD Lock Band
        DELAY_XUS_EXINT(300);

        // Disable Adapation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);
    }


    /////////////////////
    // FLD Manual Mode //
    /////////////////////

    // [6] reg_adp_en_manual = 1'b0 --> CDR Open Loop
    // [5] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~(_BIT6 | _BIT5), 0x00);

    // Scan Auto FLD + 4
    ScalerSetBit_EXINT(P7A_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P7A_36_ANA_CDR_11) & 0x7F) + 4));
    ScalerSetBit_EXINT(P7A_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P7A_37_ANA_CDR_12) & 0x7F) + 4));
    ScalerSetBit_EXINT(P7A_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P7A_38_ANA_CDR_13) & 0x7F) + 4));
    ScalerSetBit_EXINT(P7A_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P7A_39_ANA_CDR_14) & 0x7F) + 4));

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    // [6] reg_adp_en_manual = 1'b1 --> Enable VCO Clock Out
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~(_BIT7 | _BIT6), _BIT6);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();


    /////////////////////////
    // Scan Auto Band + 4  //
    /////////////////////////

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit_EXINT(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

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
            usVCOBandScan = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }


    /////////////////////////
    // VCO Band Difference //
    /////////////////////////

    // Scan Auto FLD
    ScalerSetBit_EXINT(P7A_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P7A_36_ANA_CDR_11) & 0x7F));
    ScalerSetBit_EXINT(P7A_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P7A_37_ANA_CDR_12) & 0x7F));
    ScalerSetBit_EXINT(P7A_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P7A_38_ANA_CDR_13) & 0x7F));
    ScalerSetBit_EXINT(P7A_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P7A_39_ANA_CDR_14) & 0x7F));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 30; g_ucDpRx1Temp++)
    {
        DELAY_5US_EXINT();

        // FLD + 4 Measure Fail or Measure Done
        if((usVCOBandScan == 0) || (ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6))
        {
            break;
        }
    }

    // Measure Done
    if((usVCOBandScan != 0) && (ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6))
    {
        g_pusDpRx1ClockCount1[_D1_DP_LANE0] = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));

        usVCOBandDiff = (abs(usVCOBandScan - g_pusDpRx1ClockCount1[_D1_DP_LANE0]) >> 2);
    }
    else
    {
        usVCOBandDiff = 0;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    if(usVCOBandDiff != 0)
    {
        switch(g_ucDpRx1LaneCount)
        {
            case _DP_FOUR_LANE:

                // Lane3 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE3, usVCOBandDiff);

                // Lane2 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE2, usVCOBandDiff);

                // Lane1 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE1, usVCOBandDiff);

                // Lane0 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE0, usVCOBandDiff);

                break;

            case _DP_TWO_LANE:

                // Lane1 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE1, usVCOBandDiff);

                // Lane0 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE0, usVCOBandDiff);

                break;

            default:
            case _DP_ONE_LANE:

                // Lane0 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE0, usVCOBandDiff);

                break;
        }
    }

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit_EXINT(P7A_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit_EXINT(P7A_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [5] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT5, _BIT5);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US_EXINT();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit_EXINT(P7A_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US_EXINT();

    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
    {
        // Set Vth Min = 0
        ScalerSetBit_EXINT(P7A_F9_LIMIT_10, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Only Enable Vth/Tap0 Adapation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x41);
    }

    // [3] reg_en_data_manual_l0 = 1'b1 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT3, _BIT3);
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1RebuildPhy_WDINT(BYTE ucDpLinkRate) using 3
{
    BYTE pucTap0[4];
    BYTE ucIcp = 0;


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(P7A_1B_CMU_01, ~_BIT7, 0x00);

    if((ScalerDpRx1GetDpcdInfo_WDINT(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
    {
        // [5] Disable De-Scrambling
        ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // [5] Enable De-Scrambling
        ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
    }

    // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

    // [7:4] RST_N = 4'b0000 = 4'b1111 --> Digital Circuit Reset Toggle
    // [3:0] CDR_RST_N = 4'b0000 --> Disable DCDR
    ScalerSetByte_EXINT(P7A_3A_TMDS_RESET, 0x00);
    ScalerSetByte_EXINT(P7A_3A_TMDS_RESET, 0xF0);

    ucIcp = (ScalerGetByte_EXINT(P7A_31_ANA_CDR_06) & 0x0F);


    /////////////////
    // DFE Setting //
    /////////////////

    // Tap Divider = 10 for TP2
    ScalerSetByte_EXINT(P7A_ED_LOOP_DIV_2, 0xCA);

    if(ucDpLinkRate == _DP_LINK_HBR2)
    {
        // Set Vth Max = 6, Min = 4
        ScalerSetByte_EXINT(P7A_F9_LIMIT_10, 0x64);
    }
    else
    {
        // Set Vth Max = 6, Min = 2
        ScalerSetByte_EXINT(P7A_F9_LIMIT_10, 0x62);
    }

    // LE Max = 20, Initial = 16, Servo Initial = 16
    ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0x40);
    ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0x40);
    ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0x40);
    ScalerSetByte_EXINT(P7A_D2_L3_LIMIT_INIT, 0x40);
    ScalerSetByte_EXINT(P7A_A3_L0_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P7A_B3_L1_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P7A_C3_L2_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P7A_D3_L3_INIT_1, 0xD0);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);


    //////////////
    // K Offset //
    //////////////

    // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT5, _BIT5);

    // [6] en_fore_offset --> Toggle Foreground Calibration
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, 0x00);
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);

    // Delay Time us [85,x] Waiting for K Offset
    DELAY_XUS_EXINT(85);


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(P7A_1B_CMU_01, ~_BIT7, _BIT7);

    // [7] reg_auto_mode = 1'b1 --> FLD Auto Mode
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

    if(ucDpLinkRate == _DP_LINK_HBR2)
    {
        // [2] reg_rstb_fsm --> FLD Reset
        ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, 0x00);

        // [1] reg_eqen_manual = 1'b1 --> Enable Adaptation
        ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT1, _BIT1);

        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0xDF);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [85,x] Waiting for DFE Adaptation
        DELAY_XUS_EXINT(85);

        // Start to Record Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Delay Time us [85,x] Waiting for DFE Adaptation
        DELAY_XUS_EXINT(85);

        // Stop To Record Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Select to Lane0
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx1LEMax[0] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx1Tap1Max[0] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

        // Select to Lane1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx1LEMax[1] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx1Tap1Max[1] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

        // Select to Lane2
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx1LEMax[2] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx1Tap1Max[2] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

        // Select to Lane3
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        g_pucDpRx1LEMax[3] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
        g_pucDpRx1Tap1Max[3] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

        g_pucDpRx1LEBound[0] = 20;
        g_pucDpRx1LEBound[1] = 20;
        g_pucDpRx1LEBound[2] = 20;
        g_pucDpRx1LEBound[3] = 20;

        while(((g_pucDpRx1LEMax[0] > 15) && (g_pucDpRx1Tap1Max[0] < 4) && (g_pucDpRx1LEBound[0] > 15)) ||
              ((g_pucDpRx1LEMax[1] > 15) && (g_pucDpRx1Tap1Max[1] < 4) && (g_pucDpRx1LEBound[1] > 15)) ||
              ((g_pucDpRx1LEMax[2] > 15) && (g_pucDpRx1Tap1Max[2] < 4) && (g_pucDpRx1LEBound[2] > 15)) ||
              ((g_pucDpRx1LEMax[3] > 15) && (g_pucDpRx1Tap1Max[3] < 4) && (g_pucDpRx1LEBound[3] > 15)))
        {
            if(g_pucDpRx1Tap1Max[0] < 4)
            {
                g_pucDpRx1LEBound[0]--;
                ScalerSetBit_EXINT(P7A_A2_L0_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx1LEBound[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit_EXINT(P7A_A3_L0_INIT_1, ~_BIT7, ((g_pucDpRx1LEBound[0] & _BIT4) << 3));
            }

            if(g_pucDpRx1Tap1Max[1] < 4)
            {
                g_pucDpRx1LEBound[1]--;
                ScalerSetBit_EXINT(P7A_B2_L1_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx1LEBound[1] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit_EXINT(P7A_B3_L1_INIT_1, ~_BIT7, ((g_pucDpRx1LEBound[1] & _BIT4) << 3));
            }

            if(g_pucDpRx1Tap1Max[2] < 4)
            {
                g_pucDpRx1LEBound[2]--;
                ScalerSetBit_EXINT(P7A_C2_L2_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx1LEBound[2] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit_EXINT(P7A_C3_L2_INIT_1, ~_BIT7, ((g_pucDpRx1LEBound[2] & _BIT4) << 3));
            }

            if(g_pucDpRx1Tap1Max[3] < 4)
            {
                g_pucDpRx1LEBound[3]--;
                ScalerSetBit_EXINT(P7A_D2_L3_LIMIT_INIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_pucDpRx1LEBound[3] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
                ScalerSetBit_EXINT(P7A_D3_L3_INIT_1, ~_BIT7, ((g_pucDpRx1LEBound[3] & _BIT4) << 3));
            }

            // Start to Record Tap0 Max/Min
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

            // Delay Time us [85,x] Waiting for DFE Adaptation
            DELAY_XUS_EXINT(85);

            // Stop To Record Tap0 Max/Min
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

            // Select to Lane0
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

            // Read Back LE Max
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx1LEMax[0] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx1Tap1Max[0] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

            // Select to Lane1
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

            // Read Back LE Max
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx1LEMax[1] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx1Tap1Max[1] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

            // Select to Lane2
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

            // Read Back LE Max
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx1LEMax[2] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx1Tap1Max[2] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

            // Select to Lane3
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Read Back LE Max
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);
            g_pucDpRx1LEMax[3] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);

            // Read Back Tap1 Max
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);
            g_pucDpRx1Tap1Max[3] = (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F);
        }

        // Disable DFE Adapt
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);

        // [1] reg_eqen_manual = 1'b0 --> Disable Adaptation
        ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT1, 0x00);

        // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
        ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT4, _BIT4);

        // Read Back Tap0
        ScalerSetByte_EXINT(P7A_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, 0x15);
            ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, 0x15);
            ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, 0x15);
            ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 15)
        {
            // Reload Tap0 to 21 (Max)
            ScalerSetByte_EXINT(P7A_D4_L3_INIT_2, 0x15);
            ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P7A_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, 0x00);
        }


        //////////////
        // K Offset //
        //////////////

        // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT5, _BIT5);

        // [6] en_fore_offset --> Toggle Foreground Calibration
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, 0x00);
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);

        // Delay Time us [85,x] Waiting for K Offset
        DELAY_XUS_EXINT(85);
    }
    else
    {
        // [2] reg_rstb_fsm = 1'b0 --> FLD Reset
        ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, 0x00);

        // [1] reg_eqen_manual = 1'b1 --> Enable Adaptation
        ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT1, _BIT1);

        // Enable LE/Vth/Tap0/Tap1/Tap2
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0xC7);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Delay Time us [300,x] Waiting for DFE Adaptation
        DELAY_XUS_EXINT(300);

        // Disable Adaptation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);
    }

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    // [6] reg_adp_en_manual = 1'b1 --> Enable CDR Clock
    // [5] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit_EXINT(P7A_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit_EXINT(P7A_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [5] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT5, _BIT5);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US_EXINT();

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit_EXINT(P7A_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [45,x] Waiting for CDR Close Loop
    DELAY_45US_EXINT();

    if(ucDpLinkRate <= _DP_LINK_HBR)
    {
        // Set Vth Min = 0
        ScalerSetBit_EXINT(P7A_F9_LIMIT_10, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Vth/Tap0 Adaptation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x41);
    }

    // [3] reg_en_data_manual_l0 = 1'b1 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    g_pusDpRx1ClockCount[0] = 0;
    g_pusDpRx1ClockCount[1] = 0;
    g_pusDpRx1ClockCount[2] = 0;
    g_pusDpRx1ClockCount[3] = 0;

    // [5] ln_ck_sel = 1'b1 -> DP CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit_EXINT(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

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
        g_pusDpRx1ClockCount[0] = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));
    }
    else
    {
        switch(ucDpLinkRate)
        {
            case _DP_LINK_HBR2:

                g_pusDpRx1ClockCount[0] = 0x2710;

                break;

            case _DP_LINK_HBR:

                g_pusDpRx1ClockCount[0] = 0x1388;

                break;

            default:
            case _DP_LINK_RBR:

                g_pusDpRx1ClockCount[0] = 0xBB8;

                break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    g_pusDpRx1ClockCount[3] = g_pusDpRx1ClockCount[0];
    g_pusDpRx1ClockCount[2] = g_pusDpRx1ClockCount[0];
    g_pusDpRx1ClockCount[1] = g_pusDpRx1ClockCount[0];
}
#endif

#endif // End of #if(_D1_DP_EXIST == _ON)
