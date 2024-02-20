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
// ID Code      : ScalerMHLRx3_SeptPhy.c No.0000
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
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
void ScalerMHLRx3DataPortInitial(void);
void ScalerMHLRx3DataPortInitial_EXINT0(void);
bit ScalerMHLRx3MscRCPGetCommand(BYTE *pucKeyCode);
void ScalerMHLRx3SetDevCapReg(void);
void ScalerMHLRx3SetTimingRelateSetting(void);
void ScalerMHLRx3TimerEventProc(EnumScalerTimerEventID enumEventID);

#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
//--------------------------------------------------
// Description  : MHL Cbus Mac Data Port Reset Proc for D3 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3DataPortInitial(void)
{
    // MSC channel manual mode enable
    ScalerSetBit(P68_C8_CBUS_CTRL_28, ~_BIT7, _BIT7);

    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, 0x00);
    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_DCHANGE_INT, 0x00);
    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_CONNECTED_RDY, 0x00);
    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_LINK_MODE, 0x00);
    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_STAT, 0x00);

    // MSC channel manual mode disable
    ScalerSetBit(P68_C8_CBUS_CTRL_28, ~_BIT7, 0x00);
}
//--------------------------------------------------
// Description  : MHL Cbus Mac Data Port Reset Proc for D3 Port (For Interrupt)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3DataPortInitial_EXINT0(void) using 1
{
    // MSC channel manual mode enable
    ScalerSetBit_EXINT(P68_C8_CBUS_CTRL_28, ~_BIT7, _BIT7);

    pData_EXINT[0] = ScalerGetByte_EXINT(P68_AB_CBUS_CTRL_0B);

    // Disable Port Auto-Inc
    ScalerSetBit_EXINT(P68_AB_CBUS_CTRL_0B, ~_BIT0, 0x00);

    // Reset _MSC_RCHANGE_INT
    ScalerSetByte_EXINT(P68_AC_CBUS_CTRL_0C, 0x20);
    ScalerSetByte_EXINT(P68_AD_CBUS_CTRL_0D, 0x00);

    // Reset _MSC_DCHANGE_INT
    ScalerSetByte_EXINT(P68_AC_CBUS_CTRL_0C, 0x21);
    ScalerSetByte_EXINT(P68_AD_CBUS_CTRL_0D, 0x00);

    // Reset _MSC_CONNECTED_READY
    ScalerSetByte_EXINT(P68_AC_CBUS_CTRL_0C, 0x30);
    ScalerSetByte_EXINT(P68_AD_CBUS_CTRL_0D, 0x00);

    // Reset _MSC_LINK_MODE
    ScalerSetByte_EXINT(P68_AC_CBUS_CTRL_0C, 0x31);
    ScalerSetByte_EXINT(P68_AD_CBUS_CTRL_0D, 0x00);

    // Reset _MSC_MHL_VERSION_STAT
    ScalerSetByte_EXINT(P68_AC_CBUS_CTRL_0C, 0x32);
    ScalerSetByte_EXINT(P68_AD_CBUS_CTRL_0D, 0x00);

    // Enable Port Auto-Inc
    ScalerSetByte_EXINT(P68_AB_CBUS_CTRL_0B, pData_EXINT[0]);

    // MSC channel manual mode disable
    ScalerSetBit_EXINT(P68_C8_CBUS_CTRL_28, ~_BIT7, 0x00);
}
//--------------------------------------------------
// Description  : Get RCP Key Code for D3 Port
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx3MscRCPGetCommand(BYTE *pucKeyCode)
{
    // Check RCP Command
    if((bit)ScalerGetBit(P68_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
    {
        // Clear Flag
        ScalerSetByte(P68_D4_CBUS_CTRL_34, (BYTE)_BIT6);

        pucKeyCode[0] = ScalerGetByte(P68_D9_CBUS_CTRL_39);

        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Set Devcap Registor Values
// Input Value  : Non
// Output Value : Non
//--------------------------------------------------
void ScalerMHLRx3SetDevCapReg(void)
{
    // ---------------------- DEV CAP Reg Setting ------------------------- //

    // Modify Device Capabilities according to MHL Version
    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _D3_MHL_VERSION);

    // Set POWLIM DEVCAP Reg.
    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_DEV_CAT_02, 0x31);

    // Adopter ID
    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_ADOPTER_ID_H_03, (BYTE)(((WORD)_MHL2_ADOPTER_ID >> 8) & 0x00FF));
    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_ADOPTER_ID_L_04, (BYTE)(_MHL2_ADOPTER_ID & 0x00FF));

    // Modify Packed Pixel Mode (2.0) and 16 Bits Mode (3.0) Support according to MHL Version
    ScalerSetDataPortBit(P68_AC_CBUS_CTRL_0C, _MSC_VID_LINK_MODE_05, ~_BIT3, (BYTE)_MHL2_PP_MODE_SUPPORT << 3);

    // Modify Audio Link Mode and High-Bitrate Support according to MHL Version
    ScalerSetDataPortBit(P68_AC_CBUS_CTRL_0C, _MSC_AUD_LINK_MODE_06, ~(_BIT1 | _BIT0), _MHL2_AUD_CHANNEL);

    // Display Support
    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_LOG_DEV_MAP_08, 0x01);

    // Modify RAP/RCP/UCP/RBP/XVYCC Support according to MHL Version
    ScalerSetDataPortBit(P68_AC_CBUS_CTRL_0C, _MSC_FEATURE_FLAG_0A, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (((BYTE)_MHL2_UCP_SUPPORT << 4) | (_MHL2_UCP_SUPPORT << 3) | (_BIT2 | _BIT1 | _BIT0)));

    // Device ID
    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_DEVICE_ID_H_0B, (BYTE)(((WORD)_MHL2_DEVICE_ID >> 8) & 0x00FF));
    ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_DEVICE_ID_L_0C, (BYTE)(_MHL2_DEVICE_ID & 0x00FF));
}
//--------------------------------------------------
// Description  : Set Devcap Registor Values
// Input Value  : Non
// Output Value : Non
//--------------------------------------------------
void ScalerMHLRx3SetTimingRelateSetting(void)
{
    // ------------- Re-Set Timing Related Setting After oCBUS -> eCBUS Switch ---------- //

    // Gate CBUS System Clk First (In Case of Digital Clk Glitch)
    ScalerSetBit(P68_A0_CBUS_CTRL_00, ~_BIT5, 0x00);

    // MHL System Clk select to IOSC (Bypass GDI Clk)
    ScalerSetBit(P68_A0_CBUS_CTRL_00, ~_BIT4, _BIT4);
    ScalerSetBit(P68_A2_CBUS_CTRL_02, ~_BIT2, 0x00);

    // Clear Wake Up Pulses Flag
    ScalerSetBit(P68_A0_CBUS_CTRL_00, ~_BIT3, _BIT3);

    // Sys Clk Divider
    ScalerSetBit(P68_A1_CBUS_CTRL_01, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Disable Debounce For Core Function
    ScalerSetBit(P68_A2_CBUS_CTRL_02, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Enable oCBUS Priority Option for MHL2.2 CTS
    ScalerSetBit(P68_AB_CBUS_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6));

    // Upper Bound of SYNC Pulse Low Time Period
    ScalerSetByte(P68_AF_CBUS_CTRL_0F, 0x35);

    // Lower Bound of SYNC Pulse Low Time Period
    ScalerSetByte(P68_B0_CBUS_CTRL_10, 0x20);

    // Upper Bound of SYNC Pulse High Time Period
    ScalerSetByte(P68_B1_CBUS_CTRL_11, 0x14);

    // Lower Bound of SYNC Pulse High Time Period
    ScalerSetByte(P68_B2_CBUS_CTRL_12, 0x09);

    // Absolute Threshold Time
    ScalerSetByte(P68_B4_CBUS_CTRL_14, 0x15);

    // Parity Bit Time
    ScalerSetByte(P68_B5_CBUS_CTRL_15, 0x1C);

    // Parity Error Limit
    ScalerSetBit(P68_B6_CBUS_CTRL_16, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

    // Ack Bit Initial Falling Edge
    ScalerSetBit(P68_B7_CBUS_CTRL_17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

    // Ack Bit Drive Low Time
    ScalerSetBit(P68_B8_CBUS_CTRL_18, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0D);

    // Requester Bit Time
    ScalerSetByte(P68_BA_CBUS_CTRL_1A, 0x1C);

    // Check Received Ack Bit's Falling Edge
    ScalerSetBit(P68_BC_CBUS_CTRL_1C, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x1C);

    // Check Received Ack Bit's Driving Low Period Upper Bound
    ScalerSetBit(P68_BD_CBUS_CTRL_1D, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x12);

    // Check Received Ack Bit's Driving Low Period Lower Bound
    ScalerSetBit(P68_BE_CBUS_CTRL_1E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x05);

    // Actively Driving High Time for CBUS
    ScalerSetBit(P68_C0_CBUS_CTRL_20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // CBUS Requester Transmit Opportunity after Arbitration
    ScalerSetByte(P68_C2_CBUS_CTRL_22, 0x1C);

    // CBUS Requester Continue After Ack
    ScalerSetByte(P68_C3_CBUS_CTRL_23, 0x0D);

    // Link Layer Timeout
    ScalerSetBit(P68_C5_CBUS_CTRL_25, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // Set Global MEC Packe TMOUT -> 192ms
    ScalerSetBit(P68_C5_CBUS_CTRL_25, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Set IIC SCL Clock Frequency
    ScalerSetByte(P68_F9_CBUS_CTRL_59, 0x03);

    // Enable CBUS System Clk
    ScalerSetBit(P68_A0_CBUS_CTRL_00, ~_BIT5, _BIT5);
}
//--------------------------------------------------
// Description  : Handle MHL Rx3 Related Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3TimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _SCALER_TIMER_EVENT_MHL_RX3_READY_TO_TRANSMIT:

            SET_MHL_RX3_READY_TO_TRANSMIT();

            break;

        case _SCALER_TIMER_EVENT_MHL_RX3_RECONNECT_1K:

            if((((ScalerGetByte(P68_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x01) ||
               (((ScalerGetByte(P68_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x02))
            {
                ScalerSetBit(P68_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                ScalerTimerDelayXms(52);
                ScalerSetBit(P68_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);
            }

            break;

        case _SCALER_TIMER_EVENT_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE:

            SET_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE();

            break;

        default:
            break;
    }
}

#endif
