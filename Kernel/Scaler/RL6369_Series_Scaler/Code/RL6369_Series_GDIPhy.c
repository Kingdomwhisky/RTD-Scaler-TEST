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
// ID Code      : RL6369_Series_GDIPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6369_SERIES_GDIPHY__

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
void ScalerGDIPhy3DSwitch(BYTE ucPortSelect);
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


        //////////////
        // Z0 AutoK //
        //////////////

        // [4] ibhx_ref_sel = 0 --> Vref = VBG
        // [1] Z0_AUTOK = 1 --> Z0 Auto K
        ScalerSetBit(PB_B4_BANDGAP_00, ~(_BIT4 | _BIT1), _BIT1);

        // [0] Z0_rstb = 1 -> 0 -> 1 --> 50ohm Auto Calibration
        ScalerSetBit(PB_B4_BANDGAP_00, ~_BIT0, _BIT0);
        ScalerSetBit(PB_B4_BANDGAP_00, ~_BIT0, 0x00);
        ScalerSetBit(PB_B4_BANDGAP_00, ~_BIT0, _BIT0);

        // Delay Time us [150,x] Waiting for Calibration
        DELAY_XUS(150);

        // Set 1k Manual Code
        ScalerSetByte(P27_A2_CBUS_RES_AUTOK_0, _MHL_1K);

        // Set 100k Manual Code
        ScalerSetByte(P27_A3_CBUS_RES_AUTOK_1, _MHL_100K);

        // Set 1k/100k Manual Mode
        ScalerSetBit(PB_B5_BANDGAP_01, ~(_BIT2 | _BIT1), 0x00);
    }
    else
    {
#if(_MHL_SUPPORT == _ON)
        // Check All CBUS Mac are not in Active State
        if((ScalerGetBit(P28_A4_CBUS_CTRL_04, _BIT0) == 0x00) && (ScalerGetBit(P29_A4_CBUS_CTRL_04, _BIT0) == 0x00))
#endif
        {
            // [7] EN_GDI_BG = 1'b0 --> GDI BG Power Off
            ScalerSetBit(PB_B4_BANDGAP_00, ~_BIT7, 0x00);
        }
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

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)    // MHL <--> HDMI

            if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                if(bSelect == _ON)
                {
#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                    // Enable Z0
                    ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif
                }
                else
                {
                    if((ScalerGetBit(PB_B7_IMPEDANCE_00, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT2 | _BIT1 | _BIT0)) &&
                       (GET_MHL_PROCESS_STATE(0) >= _MHL_STATE_SET_DEV_CAP_DONE))
                    {
                        if((GET_MHL_RX0_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX0_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))
                        {
                            SET_MHL_SWITCH_PORT_DISCOVERY_DONE(0, _TRUE);
                        }
                        else
                        {
                            // Reset D0 CBUS While Non-NoteII
                            ScalerMHLCBUSResetProc(_D0_INPUT_PORT);
                        }
                    }
                }
            }
            else
            {
                ScalerMHLCBUSPhySwitch(_D0_INPUT_PORT, _OFF);

                if(bSelect == _ON)
                {
                    if(ScalerGetBit(PB_B7_IMPEDANCE_00, _BIT3) == 0x00)
                    {
                        SET_TMDS_Z0_ASSERTED();

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                        CLR_D0_HDMI_PS_WAKEUP();
#endif
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

#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                        MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
#endif

                        // Enable Z0
                        ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }
                else
                {
                    // Disable DDC Toggle IRQ
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif

                    // Disable Z0
                    ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                    // Reset Hdcp2 Proc
                    ScalerHdcp2ResetTMDSProc(_D0_INPUT_PORT);
#endif
                }
            }
#else // Else of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

            if(bSelect == _ON)
            {
                // Disable MHL Mode
                ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT4, 0x00);

                if(ScalerGetBit(PB_B7_IMPEDANCE_00, _BIT3) == 0x00)
                {
#if(_D0_TMDS_SUPPORT == _ON)

                    SET_TMDS_Z0_ASSERTED();

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                    CLR_D0_HDMI_PS_WAKEUP();
#endif
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

#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
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

#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif

#endif
                // Disable Z0
                ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON) && (_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT))
                // Reset Hdcp2 Proc
                ScalerHdcp2ResetTMDSProc(_D0_INPUT_PORT);
#endif
            }
#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

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

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

            if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                if(bSelect == _ON)
                {
#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                    // Enable Z0
                    ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif
                }
                else
                {
                    if((ScalerGetBit(PB_B9_IMPEDANCE_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT2 | _BIT1 | _BIT0)) &&
                       (GET_MHL_PROCESS_STATE(1) >= _MHL_STATE_SET_DEV_CAP_DONE))
                    {
                        if((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))
                        {
                            SET_MHL_SWITCH_PORT_DISCOVERY_DONE(1, _TRUE);
                        }
                        else
                        {
                            // Reset D1 CBUS While Non-NoteII
                            ScalerMHLCBUSResetProc(_D1_INPUT_PORT);
                        }
                    }
                }
            }
            else
            {
                ScalerMHLCBUSPhySwitch(_D1_INPUT_PORT, _OFF);

                if(bSelect == _ON)
                {
                    if(ScalerGetBit(PB_B9_IMPEDANCE_02, _BIT3) == 0x00)
                    {
                        SET_TMDS_Z0_ASSERTED();

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                        CLR_D1_HDMI_PS_WAKEUP();
#endif
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

#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                        MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
#endif

                        // Enable Z0
                        ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }
                else
                {
                    // Disable DDC Toggle IRQ
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif

                    // Disable Z0
                    ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                    // Reset Hdcp2 Proc
                    ScalerHdcp2ResetTMDSProc(_D1_INPUT_PORT);
#endif
                }
            }
#else // Else of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

            if(bSelect == _ON)
            {
                // Disable MHL Mode
                ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT4, 0x00);

                if(ScalerGetBit(PB_B9_IMPEDANCE_02, _BIT3) == 0x00)
                {
#if(_D1_TMDS_SUPPORT == _ON)

                    SET_TMDS_Z0_ASSERTED();

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                    CLR_D1_HDMI_PS_WAKEUP();
#endif
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

#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
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

#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif

#endif
                // Disable Z0
                ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT))
                // Reset Hdcp2 Proc
                ScalerHdcp2ResetTMDSProc(_D1_INPUT_PORT);
#endif
            }
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

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

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

            if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                if(bSelect == _ON)
                {
#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                    // Enable Z0
                    ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif
                }
                else
                {
                    if((ScalerGetBit(PB_BB_IMPEDANCE_04, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT2 | _BIT1 | _BIT0)) &&
                       (GET_MHL_PROCESS_STATE(2) >= _MHL_STATE_SET_DEV_CAP_DONE))
                    {
                        if((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))
                        {
                            SET_MHL_SWITCH_PORT_DISCOVERY_DONE(2, _TRUE);
                        }
                        else
                        {
                            // Reset D2 CBUS While Non-NoteII
                            ScalerMHLCBUSResetProc(_D2_INPUT_PORT);
                        }
                    }
                }
            }
            else
            {
                ScalerMHLCBUSPhySwitch(_D2_INPUT_PORT, _OFF);

                if(bSelect == _ON)
                {
                    if(ScalerGetBit(PB_BB_IMPEDANCE_04, _BIT3) == 0x00)
                    {
                        SET_TMDS_Z0_ASSERTED();

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                        CLR_D2_HDMI_PS_WAKEUP();
#endif
                        // Clear HDCP Flag
                        ScalerSetBit(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

                        // Initialize DDC Detection Process
                        CLR_TMDS_RX2_DDC_DETECTED();

                        // Enable DDC Toggle IRQ
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                        MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
                        MCU_FFE4_DDC0_EDID_IRQ |= _BIT3;

#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
                        MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                        MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                        MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
#endif

                        // Enable Z0
                        ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }
                else
                {
                    // Disable DDC Toggle IRQ
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif

                    // Disable Z0
                    ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                    // Reset Hdcp2 Proc
                    ScalerHdcp2ResetTMDSProc(_D2_INPUT_PORT);
#endif
                }
            }
#else // Else of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

            if(bSelect == _ON)
            {
                // Disable MHL Mode
                ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT4, 0x00);

                if(ScalerGetBit(PB_BB_IMPEDANCE_04, _BIT3) == 0x00)
                {
#if(_D2_TMDS_SUPPORT == _ON)

                    SET_TMDS_Z0_ASSERTED();

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
                    CLR_D2_HDMI_PS_WAKEUP();
#endif
                    // Clear HDCP Flag
                    ScalerSetBit(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

                    // Initialize DDC Detection Process
                    CLR_TMDS_RX2_DDC_DETECTED();

                    // Enable DDC Toggle IRQ
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
                    MCU_FFE4_DDC0_EDID_IRQ |= _BIT3;

#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
#endif

#endif // End of #if(_D2_TMDS_SUPPORT == _ON)

                    // Enable Z0
                    ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
            }
            else
            {
#if(_D2_TMDS_SUPPORT == _ON)

                // Disable DDC Toggle IRQ
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
                MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT3 | _BIT1);

#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif

#endif
                // Disable Z0
                ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON) && (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT))
                // Reset Hdcp2 Proc
                ScalerHdcp2ResetTMDSProc(_D2_INPUT_PORT);
#endif
            }
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

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

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                        if((GET_MHL_PROCESS_STATE(0) >= _MHL_STATE_SET_DEV_CAP_DONE) &&
                           (((GET_MHL_RX0_ADOPTER_ID_HBYTE() == _CHROMA_MHL_ADOPTER_ID_HBYTE) && (GET_MHL_RX0_ADOPTER_ID_LBYTE() == _CHROMA_MHL_ADOPTER_ID_LBYTE)) ||
                            ((GET_MHL_RX0_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX0_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
                        {
                            // Reset D0 CBUS
                            ScalerMHLCBUSResetProc(_D0_INPUT_PORT);
                        }
#endif
                    }

                    break;

                case _D1_INPUT_PORT:

                    if(ScalerGetBit(PB_B9_IMPEDANCE_02, _BIT3) == _BIT3)
                    {
                        // Enable RGB Z0
                        ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                        if((GET_MHL_PROCESS_STATE(1) >= _MHL_STATE_SET_DEV_CAP_DONE) &&
                           (((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _CHROMA_MHL_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _CHROMA_MHL_ADOPTER_ID_LBYTE)) ||
                            ((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
                        {
                            // Reset D1 CBUS
                            ScalerMHLCBUSResetProc(_D1_INPUT_PORT);
                        }
#endif
                    }

                    break;

                case _D2_INPUT_PORT:

                    if(ScalerGetBit(PB_BB_IMPEDANCE_04, _BIT3) == _BIT3)
                    {
                        // Enable RGB Z0
                        ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                        if((GET_MHL_PROCESS_STATE(2) >= _MHL_STATE_SET_DEV_CAP_DONE) &&
                           (((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _CHROMA_MHL_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _CHROMA_MHL_ADOPTER_ID_LBYTE)) ||
                            ((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
                        {
                            // Reset D2 CBUS
                            ScalerMHLCBUSResetProc(_D2_INPUT_PORT);
                        }
#endif
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

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    if((GET_D0_TMDS_MODE() == _TMDS_MHL_MODE) && (GET_MHL_SWITCH_PORT_DISCOVERY_DONE(0) == _TRUE) &&
                       (ScalerGetBit(PB_B7_IMPEDANCE_00, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT2 | _BIT1 | _BIT0)) &&
                       (GET_MHL_PROCESS_STATE(0) >= _MHL_STATE_SET_DEV_CAP_DONE) &&
                       (((GET_MHL_RX0_ADOPTER_ID_HBYTE() == _HUAWEI_D2_ADOPTER_ID_HBYTE) && (GET_MHL_RX0_ADOPTER_ID_LBYTE() == _HUAWEI_D2_ADOPTER_ID_LBYTE)) ||
                        ((GET_MHL_RX0_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX0_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
                    {
                        // Reset CBUS
                        ScalerMHLCBUSResetProc(_D0_INPUT_PORT);
                    }
#endif

#if(_DP_PORT_DISCONNECT_TERMINATION_AT_HDMI_MODE == _OFF)
                    ScalerGDIPhyZ0Switch(_D0_INPUT_PORT, _ON);
#elif(_D0_INPUT_PORT_TYPE != _D0_DP_PORT)
                    ScalerGDIPhyZ0Switch(_D0_INPUT_PORT, _ON);
#endif
                    break;

                case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    if((GET_D1_TMDS_MODE() == _TMDS_MHL_MODE) && (GET_MHL_SWITCH_PORT_DISCOVERY_DONE(1) == _TRUE) &&
                       (ScalerGetBit(PB_B9_IMPEDANCE_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT2 | _BIT1 | _BIT0)) &&
                       (GET_MHL_PROCESS_STATE(1) >= _MHL_STATE_SET_DEV_CAP_DONE) &&
                       (((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _HUAWEI_D2_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _HUAWEI_D2_ADOPTER_ID_LBYTE)) ||
                        ((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
                    {
                        // Reset CBUS
                        ScalerMHLCBUSResetProc(_D1_INPUT_PORT);
                    }
#endif

#if(_DP_PORT_DISCONNECT_TERMINATION_AT_HDMI_MODE == _OFF)
                    ScalerGDIPhyZ0Switch(_D1_INPUT_PORT, _ON);
#elif(_D1_INPUT_PORT_TYPE != _D1_DP_PORT)
                    ScalerGDIPhyZ0Switch(_D1_INPUT_PORT, _ON);
#endif
                    break;

                case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    if((GET_D2_TMDS_MODE() == _TMDS_MHL_MODE) && (GET_MHL_SWITCH_PORT_DISCOVERY_DONE(2) == _TRUE) &&
                       (ScalerGetBit(PB_BB_IMPEDANCE_04, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT2 | _BIT1 | _BIT0)) &&
                       (GET_MHL_PROCESS_STATE(2) >= _MHL_STATE_SET_DEV_CAP_DONE) &&
                       (((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _HUAWEI_D2_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _HUAWEI_D2_ADOPTER_ID_LBYTE)) ||
                        ((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
                    {
                        // Reset CBUS
                        ScalerMHLCBUSResetProc(_D2_INPUT_PORT);
                    }
#endif

#if(_DP_PORT_DISCONNECT_TERMINATION_AT_HDMI_MODE == _OFF)
                    ScalerGDIPhyZ0Switch(_D2_INPUT_PORT, _ON);
#elif(_D2_INPUT_PORT_TYPE != _D2_DP_PORT)
                    ScalerGDIPhyZ0Switch(_D2_INPUT_PORT, _ON);
#endif
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

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    // MHL Power Off Process
                    ScalerMHLPowerOffProc(_D0_INPUT_PORT);
#endif
                    ScalerGDIPhyZ0Switch(_D0_INPUT_PORT, _OFF);

#if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
                    CLR_TMDS_RX0_TOGGLE_Z0();
                    CLR_TMDS_RX0_TOGGLE_Z0_EVENT();
#endif
                    break;

                case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    // MHL Power Off Process
                    ScalerMHLPowerOffProc(_D1_INPUT_PORT);
#endif
                    ScalerGDIPhyZ0Switch(_D1_INPUT_PORT, _OFF);

#if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
                    CLR_TMDS_RX1_TOGGLE_Z0();
                    CLR_TMDS_RX1_TOGGLE_Z0_EVENT();
#endif
                    break;

                case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    // MHL Power Off Process
                    ScalerMHLPowerOffProc(_D2_INPUT_PORT);
#endif
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

            switch(ucPortSelect)
            {
                case _D0_INPUT_PORT:

                    ScalerGDIPhyZ0Switch(_D0_INPUT_PORT, _OFF);

                    break;

                case _D1_INPUT_PORT:

                    ScalerGDIPhyZ0Switch(_D1_INPUT_PORT, _OFF);

                    break;

                case _D2_INPUT_PORT:

                    ScalerGDIPhyZ0Switch(_D2_INPUT_PORT, _OFF);

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
    ScalerGDIPhy3DSwitch(ucInputPort);

    /////////////////
    // DP --> TMDS //
    /////////////////

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    if(((_D0_INPUT_PORT_TYPE != _D0_DP_PORT) && (ucInputPort == _D0_INPUT_PORT)) ||
       ((_D1_INPUT_PORT_TYPE != _D1_DP_PORT) && (ucInputPort == _D1_INPUT_PORT)) ||
       ((_D2_INPUT_PORT_TYPE != _D2_DP_PORT) && (ucInputPort == _D2_INPUT_PORT)))
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

#if(_DP_PORT_DISCONNECT_TERMINATION_AT_HDMI_MODE == _OFF)

            switch(ucInputPort)
            {
                case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
                    {
                        // Reset CBUS
                        ScalerMHLCBUSResetProc(_D0_INPUT_PORT);
                    }
                    else
#endif
                    {
                        CLR_DIGITAL_PORT_SWITCH_TO_D0();

                        // Disable Port 0 Z0
                        ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    }

                    break;

                case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
                    {
                        // Reset CBUS
                        ScalerMHLCBUSResetProc(_D1_INPUT_PORT);
                    }
                    else
#endif
                    {
                        CLR_DIGITAL_PORT_SWITCH_TO_D1();

                        // Disable Port 1 Z0
                        ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    }

                    break;

                case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
                    {
                        // Reset CBUS
                        ScalerMHLCBUSResetProc(_D2_INPUT_PORT);
                    }
                    else
#endif
                    {
                        CLR_DIGITAL_PORT_SWITCH_TO_D2();

                        // Disable Port 2 Z0
                        ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    }

                    break;

                default:

                    break;
            }

#else

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
            if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                // Reset CBUS
                ScalerMHLCBUSResetProc(_D0_INPUT_PORT);
            }
            else
#endif
            {
                CLR_DIGITAL_PORT_SWITCH_TO_D0();

                // Disable Port 0 Z0
                ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                // Reset CBUS
                ScalerMHLCBUSResetProc(_D1_INPUT_PORT);
            }
            else
#endif
            {
                CLR_DIGITAL_PORT_SWITCH_TO_D1();

                // Disable Port 1 Z0
                ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                // Reset CBUS
                ScalerMHLCBUSResetProc(_D2_INPUT_PORT);
            }
            else
#endif
            {
                CLR_DIGITAL_PORT_SWITCH_TO_D2();

                // Disable Port 2 Z0
                ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            }
#endif

            // Analog Select to HDMI
            ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT5, 0x00);

            // Digital PHY Select to HDMI
            ScalerSetBit(PB_A5_DIG_05, ~_BIT7, _BIT7);
            ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT0, _BIT0);
        }

        // [4] PSM = 1'b1 --> Enable HDMI Clock Switch
        ScalerSetBit(PB_B5_BANDGAP_01, ~_BIT4, _BIT4);

        // Digital PHY Lane Swap Setting
        ScalerSetByte(PB_A1_DIG_01, 0xE4);

        // Digital PHY P/N Swap Setting
        ScalerSetBit(PB_A3_DIG_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Enable Clock Lane Rx_En
        ScalerSetBit(PB_C0_CMU_03, ~_BIT7, _BIT7);

        if(((ucInputPort == _D0_INPUT_PORT) && ((_D0_INPUT_PORT_TYPE != _D0_MHL_PORT) || (GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE))) ||
           ((ucInputPort == _D1_INPUT_PORT) && ((_D1_INPUT_PORT_TYPE != _D1_MHL_PORT) || (GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE))) ||
           ((ucInputPort == _D2_INPUT_PORT) && ((_D2_INPUT_PORT_TYPE != _D2_MHL_PORT) || (GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE))))
        {
            // Disable MHL Mode
            ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT4, 0x00);

            // [6:5] CMU_Refck_Sel = 2'b00 --> Lane3 Clock
            // [4] Disable MHL OP
            ScalerSetBit(PB_C1_CMU_04, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        }
        else
        {
            // Enable MHL Mode
            ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT4, _BIT4);

            // [6:5] CMU_Refck_Sel = 2'b00 --> Lane3 Clock
            // [4] Enable MHL OP
            ScalerSetBit(PB_C1_CMU_04, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
        }
    }
#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
}


//--------------------------------------------------
// Description  : GDI 3D Switch
// Input Value  : D0/D1 Port Select
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhy3DSwitch(BYTE ucPortSelect)
{
    switch(ucPortSelect)
    {
        case _D0_INPUT_PORT:

            if(ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) != 0x00)
            {
                // Switch to Port 0
                ScalerSetBit(PB_B6_BANDGAP_02, ~(_BIT7 | _BIT6), 0x00);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
                CLR_TMDS_PHY_SET();

                g_usTMDSClkCount = 0;

                // SET KEY ready bit 0
                ScalerSetBit(P2_AE_TMDS_RPS, ~(_BIT1), 0x00);
#endif
            }

            break;

        case _D1_INPUT_PORT:

            if(ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) != _BIT6)
            {
                // Switch to Port 1
                ScalerSetBit(PB_B6_BANDGAP_02, ~(_BIT7 | _BIT6), _BIT6);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
                CLR_TMDS_PHY_SET();

                g_usTMDSClkCount = 0;


                // SET KEY ready bit 0
                ScalerSetBit(P2_AE_TMDS_RPS, ~(_BIT1), 0x00);
#endif
            }

            break;

        case _D2_INPUT_PORT:

            if(ScalerGetBit(PB_B6_BANDGAP_02, (_BIT7 | _BIT6)) != _BIT7)
            {
                // Switch to Port 2
                ScalerSetBit(PB_B6_BANDGAP_02, ~(_BIT7 | _BIT6), _BIT7);

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

            ////////////
            ///LDO EN //
            ////////////

            // [7] CMU_LDO_EN = 1 --> Enable CMU's LDO
            // [6:4] CMU_VSEL_LDO_D[2:0] = 3'b011 --> CMU's LDO_D Output Voltage = 1.8V
            // [3:1] CMU_VSEL_LDO_A[2:0] = 3'b011 --> CMU's LDO_A Output Voltage = 1.8V
            ScalerSetBit(PB_BC_CMU_LDO, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT5 | _BIT4 | _BIT2 | _BIT1));
            ScalerSetBit(PB_BC_CMU_LDO, ~_BIT7, _BIT7);


            ///////////////////////
            ///Offset Calibration//
            ///////////////////////

            // [7] EN_FORE_OFFSET = 1'b0 --> Disable K-offset
            // [6] Disable Auto K-offset Auto Mode
            // [5] EN_BACK_OFFSET = 1'b1 --> Enable Background Offset Calibration
            ScalerSetBit(PB_CA_KOFFSET_04, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);


            //////////////
            ///Z0 AutoK //
            //////////////

            // [3] Z0_manual_P0 = 0 --> Port0 50ohm Manual Mode
            // [3] Z0_manual_P1 = 0 --> Port0 50ohm Manual Mode
            // [3] Z0_manual_P2 = 0 --> Port0 50ohm Manual Mode
            ScalerSetBit(PB_B6_BANDGAP_02, ~_BIT3, _BIT3);
            ScalerSetBit(PB_B8_IMPEDANCE_01, ~_BIT3, _BIT3);
            ScalerSetBit(PB_BA_IMPEDANCE_03, ~_BIT3, _BIT3);

            // Z0 Common Impedance = 4
            ScalerSetBit(PB_B6_BANDGAP_02, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit(PB_B8_IMPEDANCE_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit(PB_BA_IMPEDANCE_03, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

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

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && ((_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) || (_D2_DP_Z0_IMPEDANCE_OPTION == _U3_90_OHM)))

            // [3:0] Z0_ADJR = 6 --> Z0 Differential Impedance = level 6
            ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

#elif(_D2_TMDS_Z0_IMPEDANCE_OPTION == _LG_90_OHM)

            // [3:0] Z0_ADJR = 5 --> Z0 Differential Impedance = level 5
            ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
#else
            // [3:0] Z0_ADJR = 8 --> Z0 Differential Impedance = level 8
            ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);
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

            // [7] CMU_LDO_EN = 1'b0 --> Disable CMU's LDO
            ScalerSetBit(PB_BC_CMU_LDO, ~_BIT7, 0x00);

            // [7] cmu_en = 1'b0 --> Disable CMU PLL
            ScalerSetBit(PB_C1_CMU_04, ~_BIT7, 0x00);

#if(_TMDS_Z0_POWER_SAVING_OPTION == _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS)

            switch(ucPortSelect)
            {
                default:
                case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                    {
                        // Disable RGB Z0
                        ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    }

                    break;

                case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                    {
                        // Disable RGB Z0
                        ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    }

                    break;

                case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                    {
                        // Disable RGB Z0
                        ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    }

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

            // [6] CMU_LDO_EN = 1'b0 --> Disable CMU's LDO
            ScalerSetBit(PB_BC_CMU_LDO, ~_BIT7, 0x00);

            // [7] cmu_en = 1'b0 --> Disable CMU PLL
            ScalerSetBit(PB_C1_CMU_04, ~_BIT7, 0x00);

            break;

        case _POWER_ACTION_SWITCH_INTERFACE_TO_OFF:
        default:

            break;
    }
}
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)
