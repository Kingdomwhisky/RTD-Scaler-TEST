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
// ID Code      : RL6463_Series_GDIPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6463_SERIES_GDIPHY__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GDI_PHY_POWER_PROC_DEBUG_MESSAGE       _OFF

#define _MHL_1K                                 7
#define _MHL_100K                               8

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
void ScalerGDIPhyBandgap(bit bSelect);

#if(_DIGITAL_PORT_SUPPORT == _ON)
void ScalerGDIPhyZ0Switch(BYTE ucPortSelect, bit bSelect);
void ScalerGDIPhyPowerProc(BYTE ucPortSelect, EnumPowerAction enumPowerAction);
void ScalerGDIPhyDigitalPhySwitch(BYTE ucInputPort);
void ScalerGDIPhy2DSwitch(BYTE ucPortSelect);
void ScalerGDIPhyPower(BYTE ucPortSelect, EnumPowerAction enumPowerAction);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : GDI Bandgap Power On/Off
// Input Value  : On/Off
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyBandgap(bit bSelect)
{
    // [5] EN_ENHANCE_BIAS = 1 --> Enhance Clock Lane Input Buffer Bias Current
    ScalerSetBit(PB_B5_BANDGAP_01, ~_BIT5, _BIT5);

    // [0] en_clkdetect = 0 --> from hysteresis
    ScalerSetBit(PB_B3_CLK_DET, ~_BIT0, 0x00);

    if(bSelect == _ON)
    {
        ////////////////
        // BangGap EN //
        ////////////////

        // [7] EN_GDI_BG = 1'b1 --> GDI BG Power On
        // [6:5] RBG = 2'b00 --> BG = 1.245V
        ScalerSetBit(PB_B4_BANDGAP_00, ~(_BIT6 | _BIT5), 0x00);
        ScalerSetBit(PB_B4_BANDGAP_00, ~_BIT7, _BIT7);

        // [3] Always Set to 1 for PFD Deglitch Function Bug
        ScalerSetBit(PB_C1_CMU_04, ~_BIT3, _BIT3);

        // HDMI Clock Gating to Measure Block
        ScalerSetBit(P2_E1_AUX_PS_REPLY, ~_BIT7, _BIT7);

        // [4] sel_bgr_bias = 1 --> Vref = VBG
        ScalerSetBit(PB_B4_BANDGAP_00, ~_BIT4, _BIT4);
    }
    else
    {
        // [7] EN_GDI_BG = 1'b0 --> GDI BG Power Off
        ScalerSetBit(PB_B4_BANDGAP_00, ~_BIT7, 0x00);
    }
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : GDI Z0 Switch
// Input Value  : D0/D1 Port ; Z0 ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyZ0Switch(BYTE ucPortSelect, bit bSelect)
{
    switch(ucPortSelect)
    {
        case _D0_INPUT_PORT:

            if(bSelect == _ON)
            {
#if(_GDI_PHY_POWER_PROC_DEBUG_MESSAGE == _ON)
                DebugMessageDigital("!!! D0 Z0 Switch ON -Flag-", 0x00);
#endif
                SET_DIGITAL_PORT_SWITCH_TO_D0();
            }
            else
            {
#if(_GDI_PHY_POWER_PROC_DEBUG_MESSAGE == _ON)
                DebugMessageDigital("!!! D0 Z0 Switch OFF -Flag-", 0x00);
#endif
                CLR_DIGITAL_PORT_SWITCH_TO_D0();
            }

            if(bSelect == _ON)
            {
                if(ScalerGetBit(PB_B7_IMPEDANCE_00, _BIT3) == 0x00)
                {
#if(_D0_TMDS_SUPPORT == _ON)

                    SET_TMDS_Z0_ASSERTED();

                    // Clear HDCP Flag
                    ScalerSetBit(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

                    // Initialize DDC Detection Process
                    CLR_TMDS_RX0_DDC_DETECTED();

                    // Enable DDC Toggle IRQ
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
                    MCU_FFE4_DDC0_EDID_IRQ |= _BIT3;

#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;
#endif

#endif // End of #if(_D0_TMDS_SUPPORT == _ON)

                    // Enable Z0
                    ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
            }
            else
            {
#if(_D0_TMDS_SUPPORT == _ON)

                // Disable DDC Toggle IRQ
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif

#endif
                // Disable Z0
                ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        case _D1_INPUT_PORT:

            if(bSelect == _ON)
            {
#if(_GDI_PHY_POWER_PROC_DEBUG_MESSAGE == _ON)
                DebugMessageDigital("!!! D1 Z0 Switch ON -Flag-", 0x00);
#endif
                SET_DIGITAL_PORT_SWITCH_TO_D1();
            }
            else
            {
#if(_GDI_PHY_POWER_PROC_DEBUG_MESSAGE == _ON)
                DebugMessageDigital("!!! D1 Z0 Switch OFF -Flag-", 0x00);
#endif
                CLR_DIGITAL_PORT_SWITCH_TO_D1();
            }

            if(bSelect == _ON)
            {
                if(ScalerGetBit(PB_B9_IMPEDANCE_02, _BIT3) == 0x00)
                {
#if(_D1_TMDS_SUPPORT == _ON)

                    SET_TMDS_Z0_ASSERTED();

                    // Clear HDCP Flag
                    ScalerSetBit(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

                    // Initialize DDC Detection Process
                    CLR_TMDS_RX1_DDC_DETECTED();

                    // Enable DDC Toggle IRQ
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
                    MCU_FFE4_DDC0_EDID_IRQ |= _BIT3;

#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;
#endif

#endif // End of #if(_D1_TMDS_SUPPORT == _ON)

                    // Enable Z0
                    ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
            }
            else
            {
#if(_D1_TMDS_SUPPORT == _ON)

                // Disable DDC Toggle IRQ
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif

#endif
                // Disable Z0
                ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

            break;

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : GDI Rx0 Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyPowerProc(BYTE ucPortSelect, EnumPowerAction enumPowerAction)
{
#if(_GDI_PHY_POWER_PROC_DEBUG_MESSAGE == _ON)
    switch(enumPowerAction)
    {
        case _POWER_ACTION_OFF_TO_NORMAL:
            DebugMessageDigital("!!! GDI PHY Power Proc OFF_TO_NORMAL", ucPortSelect);
            break;

        case _POWER_ACTION_PS_TO_NORMAL:
            DebugMessageDigital("!!! GDI PHY Power Proc PS_TO_NORMAL", ucPortSelect);
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
            DebugMessageDigital("!!! GDI PHY Power Proc NORMAL_TO_OFF", ucPortSelect);
            break;

        case _POWER_ACTION_NORMAL_TO_PS:
            DebugMessageDigital("!!! GDI PHY Power Proc NORMAL_TO_PS", ucPortSelect);
            break;

        default:
            DebugMessageDigital("!!! GDI PHY Power Proc Other", enumPowerAction);
            break;
    }
#endif  // End of #if(_GDI_PHY_POWER_PROC_DEBUG_MESSAGE == _ON)

    ScalerGDIPhyPower(ucPortSelect, enumPowerAction);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

            switch(ucPortSelect)
            {
                case _D0_INPUT_PORT:

                    if(ScalerGetBit(PB_B7_IMPEDANCE_00, _BIT3) == _BIT3)
                    {
                        // Enable RGB Z0
                        ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
                    }

                    break;

                case _D1_INPUT_PORT:

                    if(ScalerGetBit(PB_B9_IMPEDANCE_02, _BIT3) == _BIT3)
                    {
                        // Enable RGB Z0
                        ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
                    }

                    break;

                default:
                    break;
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            switch(ucPortSelect)
            {
                case _D0_INPUT_PORT:

                    ScalerGDIPhyZ0Switch(_D0_INPUT_PORT, _ON);

                    break;

                case _D1_INPUT_PORT:

                    ScalerGDIPhyZ0Switch(_D1_INPUT_PORT, _ON);

                    break;

                default:

                    break;
            }

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
            ScalerTMDSPowerSavingProc(ucPortSelect);
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
            ScalerTMDSPowerOffProc();
#endif
            switch(ucPortSelect)
            {
                case _D0_INPUT_PORT:

                    ScalerGDIPhyZ0Switch(_D0_INPUT_PORT, _OFF);

#if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
                    CLR_TMDS_RX0_TOGGLE_Z0();
                    CLR_TMDS_RX0_TOGGLE_Z0_EVENT();
#endif
                    break;

                case _D1_INPUT_PORT:

                    ScalerGDIPhyZ0Switch(_D1_INPUT_PORT, _OFF);

#if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
                    CLR_TMDS_RX1_TOGGLE_Z0();
                    CLR_TMDS_RX1_TOGGLE_Z0_EVENT();
#endif
                    break;

                default:
                    break;
            }

            break;

        case _POWER_ACTION_SWITCH_INTERFACE_TO_OFF:

            switch(ucPortSelect)
            {
                case _D0_INPUT_PORT:

                    ScalerGDIPhyZ0Switch(_D0_INPUT_PORT, _OFF);

                    break;

                case _D1_INPUT_PORT:

                    ScalerGDIPhyZ0Switch(_D1_INPUT_PORT, _OFF);

                    break;

                default:
                    break;
            }

            break;

        default:

            break;
    }
}


//-------------------------------------------------------------
// Description  : GDI Digital PHY Switch (DP to TMDS; HDMI/MHL)
// Input Value  : InputPortType
// Output Value : None
//-------------------------------------------------------------
void ScalerGDIPhyDigitalPhySwitch(BYTE ucInputPort)
{
    ScalerGDIPhy2DSwitch(ucInputPort);

    // remove Z0 always enable due to version-C solve interference
    if(ScalerGlobalGetIDCode() < _RL6463_VER_C_ID_CODE)
    {
        // RL6463 DP/HDMI has interference issue, need turn on another port's Z0.
        switch(ucInputPort)
        {
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            case _D0_INPUT_PORT:

                // Enable Port 1 Z0
                ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            case _D1_INPUT_PORT:
                // Enable Port 0 Z0
                ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                break;
#endif

            default:
                break;
        }
    }


    /////////////////
    // DP --> TMDS //
    /////////////////

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    if(((_D0_INPUT_PORT_TYPE != _D0_DP_PORT) && (ucInputPort == _D0_INPUT_PORT)) ||
       ((_D1_INPUT_PORT_TYPE != _D1_DP_PORT) && (ucInputPort == _D1_INPUT_PORT)))
    {
        // Current SI at DP
        if(ScalerGetBit(PB_B6_BANDGAP_02, _BIT5) != 0x00)
        {
            // Disable Rx_En and CMU_En
            ScalerSetByte(PB_C0_CMU_03, 0x00);

            // Disable CMU PLL
            ScalerSetBit(PB_C1_CMU_04, ~_BIT7, 0x00);

            // Disable Auto K-offset
            // Disable Auto K-offset Auto Mode
            ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT7 | _BIT6), 0x00);

            switch(ucInputPort)
            {
                case _D0_INPUT_PORT:

                    CLR_DIGITAL_PORT_SWITCH_TO_D0();

                    // Disable Port 0 Z0
                    ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                    break;

                case _D1_INPUT_PORT:

                    CLR_DIGITAL_PORT_SWITCH_TO_D1();

                    // Disable Port 1 Z0
                    ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                    break;

                default:

                    break;
            }

            // Analog Select to HDMI
            ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT5, 0x00);

            // Termination to VDD
            ScalerSetBit(PB_BF_CMU_02, ~(_BIT5 | _BIT4), 0x00);

            // Digital PHY Select to HDMI
            ScalerSetBit(PB_A5_DIG_05, ~_BIT7, _BIT7);
            ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT0, _BIT0);
        }

        // [4] PSM = 1'b1 --> Enable HDMI Clock Switch
        ScalerSetBit(PB_B5_BANDGAP_01, ~_BIT4, _BIT4);

        // Disable 200ohm
        ScalerSetBit(PB_B8_IMPEDANCE_01, ~_BIT0, 0x00);

        // Digital PHY Lane Swap Setting
        ScalerSetByte(PB_A1_DIG_01, 0xE4);

        // Digital PHY P/N Swap Setting
        ScalerSetBit(PB_A3_DIG_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Enable Clock Lane Rx_En
        ScalerSetBit(PB_C0_CMU_03, ~_BIT7, _BIT7);

        // [6:5] CMU_Refck_Sel = 2'b00 --> Lane3 Clock
        ScalerSetBit(PB_C1_CMU_04, ~(_BIT6 | _BIT5), 0x00);

        // dp_bbpd_sel[3:2] --> ACDR BBPD UP/DN from MAC Lane0
        ScalerSetBit(PB_D0_ANA_CDR_02, ~(_BIT3 | _BIT2), 0x00);
    }
#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
}


//--------------------------------------------------
// Description  : GDI 2D Switch
// Input Value  : D0/D1 Port Select
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhy2DSwitch(BYTE ucPortSelect)
{
    switch(ucPortSelect)
    {
        case _D0_INPUT_PORT:

            if(ScalerGetBit(PB_B6_BANDGAP_02, _BIT7) != 0x00)
            {
                // Switch to Port 0
                ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT7, 0x00);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
                CLR_TMDS_PHY_SET();

                g_usTMDSClkCount = 0;

                // SET KEY ready bit 0
                ScalerSetBit(P2_AE_TMDS_RPS, ~(_BIT1), 0x00);
#endif
            }

            break;

        case _D1_INPUT_PORT:

            if(ScalerGetBit(PB_B6_BANDGAP_02, _BIT7) != _BIT7)
            {
                // Switch to Port 1
                ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT7, _BIT7);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
                CLR_TMDS_PHY_SET();

                g_usTMDSClkCount = 0;

                // SET KEY ready bit 0
                ScalerSetBit(P2_AE_TMDS_RPS, ~(_BIT1), 0x00);
#endif
            }

            break;

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : GDI Power On/Off
// Input Value  : PowerAction (Normal/PS/OFF)
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyPower(BYTE ucPortSelect, EnumPowerAction enumPowerAction)
{
    ucPortSelect = ucPortSelect;

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            ///////////////////////
            ///Offset Calibration//
            ///////////////////////

            // [7] EN_FORE_OFFSET = 1'b0 --> Disable K-offset
            // [6] Disable Auto K-offset Auto Mode
            ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT7 | _BIT6), 0x00);


            ///////////////
            ///Z0 Manual //
            ///////////////

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && ((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) || (_D0_DP_Z0_IMPEDANCE_OPTION == _U3_90_OHM)))

            // [3:0] Z0_ADJR = 6 --> Z0 Differential Impedance = level 6
            ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

#elif(_D0_TMDS_Z0_IMPEDANCE_OPTION == _LG_90_OHM)

            // [3:0] Z0_ADJR = 5 --> Z0 Differential Impedance = level 5
            ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
#else
            // [3:0] Z0_ADJR = 8 --> Z0 Differential Impedance = level 8
            ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && ((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) || (_D1_DP_Z0_IMPEDANCE_OPTION == _U3_90_OHM)))

            // [3:0] Z0_ADJR = 6 --> Z0 Differential Impedance = level 6
            ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

#elif(_D1_TMDS_Z0_IMPEDANCE_OPTION == _LG_90_OHM)

            // [3:0] Z0_ADJR = 5 --> Z0 Differential Impedance = level 5
            ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
#else
            // [3:0] Z0_ADJR = 8 --> Z0 Differential Impedance = level 8
            ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);
#endif
            // [3] n_channel_en = 1 --> Switch n Channel 50ohm Z0
            // [2] p_channel_en = 1 --> Switch p Channel 50ohm Z0
            ScalerSetBit(PB_B4_BANDGAP_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));


            /////////////
            //Reset PHY//
            /////////////

            // [3:0] cdr_rst_n = 4'b1111 --> Normal CDR
            ScalerSetBit(PB_D8_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // [3:0] phy_si_reset_n = 4'b1111 --> Normal Digital PHY
            ScalerSetBit(PB_A0_DIG_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // [1] bypass_clk_rdy = 1 --> Manual Mode
            ScalerSetBit(PB_AE_SDM_04, ~_BIT1, _BIT1);

            // [1] bypass_eqen_rdy = 1 --> Manual Mode
            ScalerSetBit(PB_B0_EQEN_TIMER, ~_BIT1, _BIT1);

            // [1] bypass_data_rdy = 1 --> Manual Mode
            ScalerSetBit(PB_B1_DATA_TIMER, ~_BIT1, _BIT1);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

#if(_HDMI_SUPPORT == _ON)
            // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetByte(PB_C0_CMU_03, 0x80);
#else
            // Disable All RX_EN and CDR_EN
            ScalerSetByte(PB_C0_CMU_03, 0x00);
#endif
            // Disable Auto k-offset
            // Disable Auto k-offset auto mode
            ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT7 | _BIT6), 0x00);

            // [7] cmu_en = 1'b0 --> Disable CMU PLL
            ScalerSetBit(PB_C1_CMU_04, ~_BIT7, 0x00);

#if(_TMDS_Z0_POWER_SAVING_OPTION == _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS)

            switch(ucPortSelect)
            {
                default:
                case _D0_INPUT_PORT:

                    // Disable RGB Z0
                    ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    break;

                case _D1_INPUT_PORT:

                    // Disable RGB Z0
                    ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    break;
            }
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            // Disable R/G/B/Clock RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetByte(PB_C0_CMU_03, 0x00);

            // Disable Auto k-offset
            // Disable Auto k-offset auto mode
            ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT7 | _BIT6), 0x00);

            // Disable Local Bias LPF
            ScalerSetBit(PB_B5_BANDGAP_01, ~_BIT3, 0x00);

            // [7] cmu_en = 1'b0 --> Disable CMU PLL
            ScalerSetBit(PB_C1_CMU_04, ~_BIT7, 0x00);

            // [3] n_channel_en = 0 --> Switch n Channel 50ohm Z0
            // [2] p_channel_en = 0 --> Switch p Channel 50ohm Z0
            ScalerSetBit(PB_B4_BANDGAP_00, ~(_BIT3 | _BIT2), 0x00);

            // [4] PSM = 1'b0 --> Disable HDMI Clock Switch
            ScalerSetBit(PB_B5_BANDGAP_01, ~_BIT4, 0x00);

            break;

        case _POWER_ACTION_SWITCH_INTERFACE_TO_OFF:
        default:

            break;
    }
}
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)
