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
// ID Code      : RL6492_Series_GDIPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_GDIPHY__

#include "ScalerFunctionInclude.h"


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GDI_PHY_POWER_PROC_DEBUG_MESSAGE       _OFF


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
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    // D1 Port Z0 Termination to Ground
    ScalerSetBit(P1D_1F_CMU_02, ~_BIT4, _BIT4);
#else
    // D1 Port Z0 Termination to V33
    ScalerSetBit(P1D_1F_CMU_02, ~_BIT4, 0x00);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    // D2 Port Z0 Termination to Ground
    ScalerSetBit(P1D_1F_CMU_02, ~_BIT5, _BIT5);
#else
    // D2 Port Z0 Termination to V33
    ScalerSetBit(P1D_1F_CMU_02, ~_BIT5, 0x00);
#endif

    // [6:5] RBG = 2'b00 --> BG = 1.245V
    // [4] sel_bgr_bias = 1 --> Vref = VBG
    ScalerSetBit(P1D_14_BANDGAP_00, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

    // [5] EN_ENHANCE_BIAS = 1 --> Enhance Clock Lane Input Buffer Bias Current
    ScalerSetBit(P1D_15_BANDGAP_01, ~_BIT5, _BIT5);

    // Disable HDMI Clock Gating to Measure Block
    ScalerSetBit(P2_E1_AUX_PS_REPLY, ~_BIT7, _BIT7);

    // [0] en_clkdetect = 0 --> from hysteresis
    ScalerSetBit(P1D_13_CLK_DET, ~_BIT0, 0x00);

    if(bSelect == _ON)
    {
        // [7] EN_GDI_BG = 1'b1 --> GDI BG Power On
        ScalerSetBit(P1D_14_BANDGAP_00, ~_BIT7, _BIT7);
    }
    else
    {
        // [7] EN_GDI_BG = 1'b0 --> GDI BG Power Off
        ScalerSetBit(P1D_14_BANDGAP_00, ~_BIT7, 0x00);
    }
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : GDI Z0 Switch
// Input Value  : D1/D2 Port ; Z0 ON/OFF
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
                // Enable Z0
                ScalerSetBit(P1A_00_COMBO_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            }
            else
            {
                if(ScalerGetBit(P1A_00_COMBO_00, _BIT7) == _BIT7)
                {
                    // Disable Z0
                    ScalerSetBit(P1A_00_COMBO_00, ~_BIT3, 0x00);
                }

                if(ScalerGetBit(P1A_00_COMBO_00, _BIT6) == _BIT6)
                {
                    // Disable Z0
                    ScalerSetBit(P1A_00_COMBO_00, ~_BIT2, 0x00);
                }

                if(ScalerGetBit(P1A_00_COMBO_00, _BIT5) == _BIT5)
                {
                    // Disable Z0
                    ScalerSetBit(P1A_00_COMBO_00, ~_BIT1, 0x00);
                }

                if(ScalerGetBit(P1A_00_COMBO_00, _BIT4) == _BIT4)
                {
                    // Disable Z0
                    ScalerSetBit(P1A_00_COMBO_00, ~_BIT0, 0x00);
                }
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
                if(ScalerGetBit(P1D_17_IMPEDANCE_00, _BIT3) == 0x00)
                {
#if(_D1_TMDS_SUPPORT == _ON)

                    SET_TMDS_Z0_ASSERTED();

                    // Clear HDCP Flag
                    ScalerSetBit(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

                    // Initialize DDC Detection Process
                    CLR_TMDS_RX1_DDC_DETECTED();

                    // Enable DDC Toggle IRQ
#if(_D1_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
#endif

#endif // End of #if(_D0_TMDS_SUPPORT == _ON)

                    // Enable Z0
                    ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
            }
            else
            {
#if(_D1_TMDS_SUPPORT == _ON)

                // Disable DDC Toggle IRQ
#if(_D1_DDC_CHANNEL_SEL == _DDC1)
                MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif
                // Backup HDCP Type
                ScalerTMDSBackupHdcpType(_D1_INPUT_PORT);
#endif
                // Disable Z0
                ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) && (_TMDS_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_SUPPORT == _ON))
                // Reset Hdcp2 Proc
                ScalerHdcp2ResetTMDSProc(_D1_INPUT_PORT);
#endif
            }

            break;

        case _D2_INPUT_PORT:

            if(bSelect == _ON)
            {
#if(_GDI_PHY_POWER_PROC_DEBUG_MESSAGE == _ON)
                DebugMessageDigital("!!! D2 Z0 Switch ON -Flag-", 0x00);
#endif
                SET_DIGITAL_PORT_SWITCH_TO_D2();
            }
            else
            {
#if(_GDI_PHY_POWER_PROC_DEBUG_MESSAGE == _ON)
                DebugMessageDigital("!!! D2 Z0 Switch OFF -Flag-", 0x00);
#endif
                CLR_DIGITAL_PORT_SWITCH_TO_D2();
            }

            if(bSelect == _ON)
            {
                if(ScalerGetBit(P1D_19_IMPEDANCE_02, _BIT3) == 0x00)
                {
#if(_D2_TMDS_SUPPORT == _ON)

                    SET_TMDS_Z0_ASSERTED();

                    // Clear HDCP Flag
                    ScalerSetBit(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

                    // Initialize DDC Detection Process
                    CLR_TMDS_RX2_DDC_DETECTED();

                    // Enable DDC Toggle IRQ
#if(_D2_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
#endif

#endif // End of #if(_D1_TMDS_SUPPORT == _ON)

                    // Enable Z0
                    ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
            }
            else
            {
#if(_D2_TMDS_SUPPORT == _ON)

                // Disable DDC Toggle IRQ
#if(_D2_DDC_CHANNEL_SEL == _DDC1)
                MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif
                // Backup HDCP Type
                ScalerTMDSBackupHdcpType(_D2_INPUT_PORT);
#endif
                // Disable Z0
                ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) && (_TMDS_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_SUPPORT == _ON))
                // Reset Hdcp2 Proc
                ScalerHdcp2ResetTMDSProc(_D2_INPUT_PORT);
#endif
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
        case _POWER_ACTION_OFF_TO_FAKE_OFF:
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

                    // Enable Z0
                    ScalerSetBit(P1A_00_COMBO_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    break;

                case _D1_INPUT_PORT:

                    if(ScalerGetBit(P1D_17_IMPEDANCE_00, _BIT3) == _BIT3)
                    {
                        // Enable RGB Z0
                        ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
                    }

                    break;

                case _D2_INPUT_PORT:

                    if(ScalerGetBit(P1D_19_IMPEDANCE_02, _BIT3) == _BIT3)
                    {
                        // Enable RGB Z0
                        ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
                    }

                    break;

                default:
                    break;
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            ScalerGDIPhyZ0Switch(ucPortSelect, _ON);

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

                    break;

                case _D1_INPUT_PORT:

                    ScalerGDIPhyZ0Switch(_D1_INPUT_PORT, _OFF);

#if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
                    CLR_TMDS_RX1_TOGGLE_Z0();
                    CLR_TMDS_RX1_TOGGLE_Z0_EVENT();
#endif
                    break;

                case _D2_INPUT_PORT:

                    ScalerGDIPhyZ0Switch(_D2_INPUT_PORT, _OFF);

#if((_D2_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
                    CLR_TMDS_RX2_TOGGLE_Z0();
                    CLR_TMDS_RX2_TOGGLE_Z0_EVENT();
#endif
                    break;

                default:

                    break;
            }

            break;

        case _POWER_ACTION_SWITCH_INTERFACE_TO_OFF:

            ScalerGDIPhyZ0Switch(ucPortSelect, _OFF);

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


    /////////////////
    // DP --> TMDS //
    /////////////////

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    if(((_D1_INPUT_PORT_TYPE != _D1_DP_PORT) && (ucInputPort == _D1_INPUT_PORT)) ||
       ((_D2_INPUT_PORT_TYPE != _D2_DP_PORT) && (ucInputPort == _D2_INPUT_PORT)))
    {
        // Current SI at DP
        if(ScalerGetBit(P1D_16_BANDGAP_02, _BIT5) != 0x00)
        {
            // Disable Rx_En and CMU_En
            ScalerSetByte(P1D_20_CMU_03, 0x00);

            // Disable CMU PLL
            ScalerSetBit(P1D_21_CMU_04, ~_BIT7, 0x00);

            // Disable Auto K-offset
            // Disable Auto K-offset Auto Mode
            ScalerSetBit(P1D_2A_KOFFSET_04, ~(_BIT7 | _BIT6), 0x00);

            switch(ucInputPort)
            {
                case _D1_INPUT_PORT:

                    CLR_DIGITAL_PORT_SWITCH_TO_D1();

                    // Disable Port 1 Z0
                    ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                    break;

                case _D2_INPUT_PORT:

                    CLR_DIGITAL_PORT_SWITCH_TO_D2();

                    // Disable Port 2 Z0
                    ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                    break;

                default:

                    break;
            }

            // Analog Select to HDMI
            ScalerSetBit(P1D_16_BANDGAP_02, ~_BIT5, 0x00);

            // Digital PHY Select to HDMI
            ScalerSetBit(P1D_05_DIG_05, ~_BIT7, _BIT7);
        }

        // [4] PSM = 1'b1 --> Enable HDMI Clock Switch
        ScalerSetBit(P1D_15_BANDGAP_01, ~_BIT4, _BIT4);

        // Disable 200ohm
        ScalerSetBit(P1D_18_IMPEDANCE_01, ~_BIT0, 0x00);

        // Digital PHY Lane Swap Setting
        ScalerSetByte(P1D_01_DIG_01, 0xE4);

        // Digital PHY P/N Swap Setting
        ScalerSetBit(P1D_03_DIG_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Enable Clock Lane Rx_En
        ScalerSetBit(P1D_20_CMU_03, ~_BIT7, _BIT7);

        // [6:5] CMU_Refck_Sel = 2'b00 --> Lane3 Clock
        ScalerSetBit(P1D_21_CMU_04, ~(_BIT6 | _BIT5), 0x00);

        // dp_bbpd_sel[3:2] --> ACDR BBPD UP/DN from MAC Lane0
        ScalerSetBit(P1D_30_ANA_CDR_02, ~(_BIT3 | _BIT2), 0x00);
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

            // DP DPHY Select DP 1.2 Rx
            ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT1, 0x00);

            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            // DP DPHY Select DP 1.1 Rx
            ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT1, _BIT1);
#endif

            if(ScalerGetBit(P1D_16_BANDGAP_02, _BIT7) != 0x00)
            {
                // Switch to Port 1
                ScalerSetBit(P1D_16_BANDGAP_02, ~_BIT7, 0x00);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
                CLR_TMDS_PHY_SET();

                g_usTMDSClkCount = 0;

                ScalerSetBit(P2_AE_TMDS_RPS, ~(_BIT1), 0x00);
#endif
            }

            break;

        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            // DP DPHY Select DP 1.1 Rx
            ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT1, _BIT1);
#endif

            if(ScalerGetBit(P1D_16_BANDGAP_02, _BIT7) != _BIT7)
            {
                // Switch to Port 2
                ScalerSetBit(P1D_16_BANDGAP_02, ~_BIT7, _BIT7);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
                CLR_TMDS_PHY_SET();

                g_usTMDSClkCount = 0;

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
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            if(ucPortSelect != _D0_INPUT_PORT)
            {
                ///////////////////////
                ///Offset Calibration//
                ///////////////////////

                // [7] EN_FORE_OFFSET = 1'b0 --> Disable K-offset
                // [6] Disable Auto K-offset Auto Mode
                ScalerSetBit(P1D_2A_KOFFSET_04, ~(_BIT7 | _BIT6), 0x00);


                ///////////////
                ///Z0 Manual //
                ///////////////

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && ((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) || (_D1_DP_Z0_IMPEDANCE_OPTION == _U3_90_OHM)))

                // [3:0] Z0_ADJR = 4 --> Z0 Differential Impedance = level 4
                ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);

#elif(_D1_TMDS_Z0_IMPEDANCE_OPTION == _LG_90_OHM)

                // [3:0] Z0_ADJR = 3 --> Z0 Differential Impedance = level 3
                ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
#else
                // [3:0] Z0_ADJR = 6 --> Z0 Differential Impedance = level 6
                ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && ((_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) || (_D2_DP_Z0_IMPEDANCE_OPTION == _U3_90_OHM)))

                // [3:0] Z0_ADJR = 4 --> Z0 Differential Impedance = level 4
                ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);

#elif(_D2_TMDS_Z0_IMPEDANCE_OPTION == _LG_90_OHM)

                // [3:0] Z0_ADJR = 3 --> Z0 Differential Impedance = level 3
                ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
#else
                // [3:0] Z0_ADJR = 6 --> Z0 Differential Impedance = level 6
                ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
#endif
                // [3] n_channel_en = 1 --> Switch n Channel 50ohm Z0
                // [2] p_channel_en = 1 --> Switch p Channel 50ohm Z0
                ScalerSetBit(P1D_14_BANDGAP_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));


                /////////////
                //Reset PHY//
                /////////////

                // [3:0] cdr_rst_n = 4'b1111 --> Normal CDR
                ScalerSetBit(P1D_38_TMDS_RESET, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // [3:0] phy_si_reset_n = 4'b1111 --> Normal Digital PHY
                ScalerSetBit(P1D_00_DIG_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // [1] bypass_clk_rdy = 1 --> Manual Mode
                ScalerSetBit(P1D_0E_SDM_04, ~_BIT1, _BIT1);

                // [1] bypass_eqen_rdy = 1 --> Manual Mode
                ScalerSetBit(P1D_10_EQEN_TIMER, ~_BIT1, _BIT1);

                // [1] bypass_data_rdy = 1 --> Manual Mode
                ScalerSetBit(P1D_11_DATA_TIMER, ~_BIT1, _BIT1);
            }

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

            if(ucPortSelect == _D0_INPUT_PORT)
            {
                // Disable Lane_EN, Disable CDR_EN
                ScalerSetByte(P1A_22_DP_RX_02, 0x00);
            }
            else
            {
#if(_HDMI_SUPPORT == _ON)
                // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
                ScalerSetByte(P1D_20_CMU_03, 0x80);
#else
                // Disable All RX_EN and CDR_EN
                ScalerSetByte(P1D_20_CMU_03, 0x00);
#endif
                // Disable Auto k-offset
                // Disable Auto k-offset auto mode
                ScalerSetBit(P1D_2A_KOFFSET_04, ~(_BIT7 | _BIT6), 0x00);

                // [7] cmu_en = 1'b0 --> Disable CMU PLL
                ScalerSetBit(P1D_21_CMU_04, ~_BIT7, 0x00);

#if(_TMDS_Z0_POWER_SAVING_OPTION == _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS)

                switch(ucPortSelect)
                {
                    default:
                    case _D1_INPUT_PORT:

                        // Disable RGB Z0
                        ScalerSetBit(P1D_17_IMPEDANCE_00, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                        break;

                    case _D2_INPUT_PORT:

                        // Disable RGB Z0
                        ScalerSetBit(P1D_19_IMPEDANCE_02, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                        break;
                }
#endif
            }

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            if(ucPortSelect == _D0_INPUT_PORT)
            {
                if(ScalerGetBit(P1A_00_COMBO_00, _BIT7) == _BIT7)
                {
                    // Disable Lane3 Lane_EN, Disable Lane3 CDR_EN
                    ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT7 | _BIT3), 0x00);
                }

                if(ScalerGetBit(P1A_00_COMBO_00, _BIT6) == _BIT6)
                {
                    // Disable Lane2 Lane_EN, Disable Lane2 CDR_EN
                    ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT6 | _BIT2), 0x00);
                }

                if(ScalerGetBit(P1A_00_COMBO_00, _BIT5) == _BIT5)
                {
                    // Disable Lane1 Lane_EN, Disable Lane1 CDR_EN
                    ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT5 | _BIT1), 0x00);
                }

                if(ScalerGetBit(P1A_00_COMBO_00, _BIT4) == _BIT4)
                {
                    // Disable Lane0 Lane_EN, Disable Lane0 CDR_EN
                    ScalerSetBit(P1A_22_DP_RX_02, ~(_BIT4 | _BIT0), 0x00);
                }
            }
            else
            {
                // Disable R/G/B/Clock RX_EN, Disable R/G/B/Clock CDR_EN
                ScalerSetByte(P1D_20_CMU_03, 0x00);

                // Disable Auto k-offset
                // Disable Auto k-offset auto mode
                ScalerSetBit(P1D_2A_KOFFSET_04, ~(_BIT7 | _BIT6), 0x00);

                // Disable Local Bias LPF
                ScalerSetBit(P1D_15_BANDGAP_01, ~_BIT3, 0x00);

                // [7] cmu_en = 1'b0 --> Disable CMU PLL
                ScalerSetBit(P1D_21_CMU_04, ~_BIT7, 0x00);

                // [3] n_channel_en = 0 --> Switch n Channel 50ohm Z0
                // [2] p_channel_en = 0 --> Switch p Channel 50ohm Z0
                ScalerSetBit(P1D_14_BANDGAP_00, ~(_BIT3 | _BIT2), 0x00);

                // [4] PSM = 1'b0 --> Disable HDMI Clock Switch
                ScalerSetBit(P1D_15_BANDGAP_01, ~_BIT4, 0x00);
            }

            break;

        case _POWER_ACTION_SWITCH_INTERFACE_TO_OFF:
        default:

            break;
    }
}
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)
