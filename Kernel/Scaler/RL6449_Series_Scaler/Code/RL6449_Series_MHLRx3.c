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
// ID Code      : RL6449_Series_MHLRx3.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6449_SERIES_MHLRX3__

#include "ScalerFunctionInclude.h"

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX3_ADOPTER_ID_DONE()            (g_bMHLRx3AdopterIDDone)
#define SET_MHL_RX3_ADOPTER_ID_DONE()            (g_bMHLRx3AdopterIDDone = _TRUE)
#define CLR_MHL_RX3_ADOPTER_ID_DONE()            (g_bMHLRx3AdopterIDDone = _FALSE)

#define GET_MHL_RX3_CBUS_RESET_FOR_HTC_DONE()    (g_bMHLRx3CbusResetForHTCDone)
#define SET_MHL_RX3_CBUS_RESET_FOR_HTC_DONE()    (g_bMHLRx3CbusResetForHTCDone = _TRUE)
#define CLR_MHL_RX3_CBUS_RESET_FOR_HTC_DONE()    (g_bMHLRx3CbusResetForHTCDone = _FALSE)

#define GET_MHL_RX3_SENT_MSC_DCAP_RDY()          (g_bMHLRx3SentMscDcapRdy)
#define SET_MHL_RX3_SENT_MSC_DCAP_RDY()          (g_bMHLRx3SentMscDcapRdy = _TRUE)
#define CLR_MHL_RX3_SENT_MSC_DCAP_RDY()          (g_bMHLRx3SentMscDcapRdy = _FALSE)

#define GET_MHL_RX3_MHL_VERSION()                (g_ucMHLRx3MhlVersion)
#define SET_MHL_RX3_MHL_VERSION(x)               (g_ucMHLRx3MhlVersion = (x))
#define CLR_MHL_RX3_MHL_VERSION()                (g_ucMHLRx3MhlVersion = 0x00)

#define GET_MHL_RX3_WRITE_BURST_PROCESS_DONE()   (g_bMHLRx3WriteBurstProcessDone)
#define SET_MHL_RX3_WRITE_BURST_PROCESS_DONE()   (g_bMHLRx3WriteBurstProcessDone = _TRUE)
#define CLR_MHL_RX3_WRITE_BURST_PROCESS_DONE()   (g_bMHLRx3WriteBurstProcessDone = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucMHLRx3AdopterIDH = 0xFF;
BYTE g_ucMHLRx3AdopterIDL = 0xFF;
bit g_bMHLRx3AdopterIDDone = _FALSE;
bit g_bMHLRx3CbusResetForHTCDone = _FALSE;
bit g_bMHLRx3SentMscDcapRdy = _TRUE;
StructMHLProcessInfo g_stMHLRx3Process;
BYTE g_ucMHLRx3MhlVersion;
bit g_bMHLRx3WriteBurstProcessDone = _TRUE;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMHLRx3ModeMHLSetting(void);
void ScalerMHLRx3ModeHdmiSetting(void);
void ScalerMHLRx3InitialSettings(void);
void ScalerMHLRx3CBUSPhySwitch(bit bSelect);
void ScalerMHLRx3CBUSSwitchClk(EnumClkSel enumClockSel);
void ScalerMHLRx3CBUSResetProc(void);
void ScalerMHLRx3PowerOffProc(void);
bit ScalerMHLRx3DetectClkMode(void);
BYTE ScalerMHLRx3DetectClkMode_EXINT0(void);
void ScalerMHLRx3IntHandler_EXINT0(void);
bit ScalerMHLRx3MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
bit ScalerMHLRx3MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);
bit ScalerMHLRx3MscReadDevCapabilities(EnumMHLMscOffset enumMSCOffset, BYTE *pucData, BYTE ucExtended);
BYTE ScalerMHLRx3MscFIFOSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData);
void ScalerMHLRx3MscCheckDeviceINT(void);

bit ScalerMHLRx3MscHandler(BYTE ucActivePort, BYTE ucModeState);
bit ScalerMHLRx3MscRAPHandler(void);

#if(_MHL_UCP_SUPPORT == _ON)
BYTE ScalerMHLRx3MscUCPGetCommand(BYTE *pucKeyCode);
#endif

bit ScalerMHLRx3PSPreDetect(void);
bit ScalerMHLRx3NormalPreDetect(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : TMDS Settings when MHL Mode for D3 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3ModeMHLSetting(void)
{
    CLR_DIGITAL_PORT_SWITCH_TO_D3();

    // Clear CBUS Reset Flag for HTC Butterfly Debug
    CLR_MHL_RX3_CBUS_RESET_FOR_HTC_DONE();

    // Clear CBUS Re-Sent DEVCAP_RDY Flag for HTC M8
    CLR_MHL_RX3_SENT_MSC_DCAP_RDY();

    // Clear CBUS Reset Flag for Other Port Discovery Done
    CLR_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE();

    PCB_D3_HDMI_MHL_SWITCH(_TMDS_SWITCH_MHL_CBUS);
    PCB_D3_MHL_VBUS_SWITCH(_MHL_VBUS_ON);

    // Port 3 Z0 Disable
    ScalerSetBit(P7C_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Disable Auto K-offset Auto Mode
    ScalerSetBit(P7C_24_KOFFSET_00, ~_BIT5, 0x00);

    // [1] Enable MHL Mode
    ScalerSetBit(P7C_17_BANDGAP_03, ~_BIT1, _BIT1);

    // Enable MHL OP
    ScalerSetBit(P7C_1B_CMU_01, ~_BIT4, _BIT4);

    // GPIO Select to CBUS
    ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT2, 0x00);

    // Disable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC3_SWITCH_GPIO);

    // Switch DDCRAM To MHL EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT3;

    // DDC3 Disable Auto Switch DDCRAM Start Address when Write Segment Data
    MCU_FFD4_DDCRAM3_CONTROL &= ~_BIT7;

    // DDC3 Disable Force Nack and disable DDC Toggle IRQ
    MCU_FE72_DDC3_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
}

//--------------------------------------------------
// Description  : TMDS Settings when HDMI Mode for D3 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3ModeHdmiSetting(void)
{
    ScalerMHLRx3CBUSPhySwitch(_OFF);

    PCB_D3_HDMI_MHL_SWITCH(_TMDS_SWITCH_HDMI_HPD);
    PCB_D3_MHL_VBUS_SWITCH(_MHL_VBUS_OFF);

    // [1] Disable MHL Mode
    ScalerSetBit(P7C_17_BANDGAP_03, ~_BIT1, 0x00);

    // Disable MHL OP
    ScalerSetBit(P7C_1B_CMU_01, ~_BIT4, 0x00);

    // GPIO Select to Hot Plug
    ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT2, _BIT2);

#if(_D3_DDC_CHANNEL_SEL == _DDC3)
    // Enable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC3_SWITCH_DDC);

    // Switch DDCRAM To HDMI EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT3;

    // DDC3 Enable Auto Switch DDCRAM Start Address when Write Segment Data
    MCU_FFD4_DDCRAM3_CONTROL |= _BIT7;

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
    // DDC3 Enable Force Nack
    MCU_FE72_DDC3_EDID_IRQ |= _BIT5;
#endif

#else
#warning "D3 MHL Port Use Not DDC3"
#endif // End of #if(_D3_DDC_CHANNEL_SEL == _DDC3)
}

//--------------------------------------------------
// Description  : Calibration for 1K/100K and LDO Level Adjust
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3InitialSettings(void)
{
    // Adjust CBUS Input Comparator VIH = 0.9V and VIL = 0.7V
    ScalerSetByte(P67_A6_CBUS_INPUT_CONTROL, 0x09);

    // Set CBUS Min Vih
    ScalerSetBit(P67_A6_CBUS_INPUT_CONTROL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

#if(_MHL_CBUS_LDO_HIGH == _ENABLE)
    // Set CBUS Max Driving Strength, Set LDO to 1.80V Level
    ScalerSetBit(P67_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    // Set CBUS Max Driving Strength, Set LDO to 1.65V Level
    ScalerSetBit(P67_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));
#endif

    // Discovery Function Power Down and System Clk Gated
    ScalerSetBit(P68_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2), _BIT6);

    // Set MHL 1MHz Clk Divider
    ScalerSetBit(P68_A1_CBUS_CTRL_01, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT3 | _BIT2));

    // Set MHL 1KHz Clk Divider and Set Stuck Low Time to 150us
    ScalerSetBit(P68_A2_CBUS_CTRL_02, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), _BIT0);
    ScalerSetByte(P68_A3_CBUS_CTRL_03, 0xE2);

    // Set HW Bypass Wake Up Pulses Mode
    ScalerSetBit(P68_A4_CBUS_CTRL_04, ~_BIT7, _BIT7);

    // Set MHL Wake pulse boundary 14~26
    ScalerSetBit(P68_A4_CBUS_CTRL_04, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3));

    // Set Discovery Upper/Lower Bound
    ScalerSetBit(P68_A5_CBUS_CTRL_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x5A);

    // Set Wake Up Pulse Number to 4
    ScalerSetBit(P68_A6_CBUS_CTRL_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    // Set CBUS (PHY) Power Saving Mode to Manual Mode
    ScalerSetByte(P68_A9_CBUS_CTRL_09, 0x00);

    ScalerMHLRx3SetTimingRelateSetting();

    // Disable eCBUS APHY 50 Ohm at Initial
    ScalerSetBit(P67_06_ECBUS_Z0_CTRL_0, ~(_BIT3 | _BIT2), 0x00);
}

//--------------------------------------------------
// Description  : Power Process for CBUS Phy for D3 Port
// Input Value  : bSelect --> _ON/_OFF
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3CBUSPhySwitch(bit bSelect)
{
    if(bSelect == _ON)
    {
        if(ScalerGetBit(P68_A8_CBUS_CTRL_08, _BIT5) == 0x00)
        {
            // GPIO Select to CBUS
            ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT2, 0x00);

            // Enable CBUS Phy, LDO, Input Comparator and Output Driver
            ScalerSetBit(P67_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // Discovery Function Power On and Enable System Clk
            ScalerSetBit(P68_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT5);

            // Enable Discovery IRQ
            ScalerSetBit(P68_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

            // MHL Attached
            ScalerSetBit(P68_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);

            // Internal IRQ Enable (Global)
            ScalerGlobalIRQControl(_ENABLE);

            EX0 = 1;
        }
    }
    else
    {
        if(ScalerGetBit(P68_A8_CBUS_CTRL_08, _BIT5) == _BIT5)
        {
            // Disable CBUS Phy, LDO, Input Comparator
            ScalerSetBit(P67_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), 0x00);

            // Discovery Function Power Down and System Clk Gated
            ScalerSetBit(P68_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT6);

            // Disable Discovery IRQ
            ScalerSetBit(P68_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), _BIT2);

            // MHL Unattached
            ScalerSetBit(P68_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Clock Select For MHL for D3 Port
// Input Value  : ucClockSel --> System refernce clock select.
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3CBUSSwitchClk(EnumClkSel enumClockSel)
{
    enumClockSel = enumClockSel;

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    // Check when MHL3 Hard Marco Isolation OFF (Power Normal)
    if((ScalerGetBit(P0_F1_VCCKOFF_CONTROL1, _BIT3) == 0x00) && (ScalerGetBit(P6F_23_D3_POWER_CTRL, _BIT1) == 0x00))
    {
        // Set MHL3 w/ HDCP2.2 Frame Number Mode to Frame_Mun - 1
        // (Reg. at Off Region, Re-Set Whenever Power Normal)
        ScalerSetByte(P77_93_REG_MHL3_CP19, 0x80);
    }
#endif
}

//--------------------------------------------------
// Description  : MHL Cbus Reset Proc for D3 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3CBUSResetProc(void)
{
    // Disable Stuck Low IRQ and Clear Stuck Low Flags
    ScalerSetBit(P68_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

    // Port 3 Z0 Disable
    ScalerSetBit(P7C_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Disable Auto K-offset Auto Mode
    ScalerSetBit(P7C_24_KOFFSET_00, ~_BIT5, 0x00);

    // Manual Enable CBUS PHY PSM
    ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT0, _BIT0);

    // Force CBUS Floating
    ScalerSetBit(P68_A8_CBUS_CTRL_08, ~_BIT7, _BIT7);

    // Enable Discovery Debounce
    ScalerSetBit(P68_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
    // Disable DDC Manual
    ScalerSetBit(P68_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif

    // Reset CBUS Core Function
    ScalerSetBit(P68_A0_CBUS_CTRL_00, ~(_BIT7), _BIT7);
    ScalerSetBit(P68_A0_CBUS_CTRL_00, ~(_BIT7), 0x00);

    CLR_MHL_RX3_MHL_VERSION();
    SET_MHL_RX3_PROCESS_STATE(_MHL_STATE_INITIAL);
    CLR_MHL_RX3_ADOPTER_ID_HBYTE();
    CLR_MHL_RX3_ADOPTER_ID_LBYTE();
    CLR_MHL_RX3_ADOPTER_ID_DONE();
    CLR_MHL_RX3_CBUS_RESET_FOR_HTC_DONE();
    CLR_MHL_RX3_SENT_MSC_DCAP_RDY();
    CLR_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE();
    SET_MHL_RX3_WRITE_BURST_PROCESS_DONE();

    ScalerMHLRx3DataPortInitial();

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
    // Reset Hdcp2 Proc
    ScalerHdcp2ResetTMDSProc(_D3_INPUT_PORT);
#endif

    // Enable Discovery Done IRQ and Clear Flag
    ScalerSetBit(P68_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));
}

//--------------------------------------------------
// Description  : MHL Power Off Process for D3 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3PowerOffProc(void)
{
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX3_READY_TO_TRANSMIT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX3_RECONNECT_1K);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE);
}

//--------------------------------------------------
// Description  : MHL Detect Clk Mode if 24Bit or PP Mode
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx3DetectClkMode(void)
{
    WORD usTemp = 250;

    // Clear Error Flag and Start Detection
    ScalerSetBit(P77_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P77_A7_MHL_CTRL_07, ~_BIT0, _BIT0);

    // Wait until detection is done(1ms) or timeout(1.5ms)
    while((ScalerGetBit(P77_A7_MHL_CTRL_07, _BIT0) == _TRUE) && (--usTemp != 0))
    {
        DELAY_5US();
    }

    if(((bit)ScalerGetBit(P77_B3_MHL_CTRL_13, _BIT0) == _TRUE) ||
       ((bit)ScalerGetBit(P77_A7_MHL_CTRL_07, _BIT7) != GET_TMDS_RX3_CLK_MODE()))
    {
        ScalerSetBit(P77_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);

        if(GET_TMDS_RX3_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
        {
            usTemp = 500;

            // Wait until RGB detection is done or timeout(3ms)
            while((ScalerGetBit(P72_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) != (_BIT7 | _BIT6 | _BIT5)) &&
                  (--usTemp != 0))
            {
                DELAY_5US();
            }

            if(usTemp == 0)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : MHL Detect Clk Mode if 24Bit or PP Mode (EXINT0 Only)
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
BYTE ScalerMHLRx3DetectClkMode_EXINT0(void) using 1
{
    WORD usTemp = 250;

    // Clear Error Flag and Start Detection
    ScalerSetBit_EXINT(P77_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P77_A7_MHL_CTRL_07, ~_BIT0, _BIT0);

    // Wait until detection is done(1ms) or timeout(1.5ms)
    while((ScalerGetBit_EXINT(P77_A7_MHL_CTRL_07, _BIT0) == _TRUE) && (--usTemp != 0))
    {
        DELAY_5US_EXINT();
    }

    if(((bit)ScalerGetBit_EXINT(P77_B3_MHL_CTRL_13, _BIT0) == _TRUE) ||
       ((bit)ScalerGetBit_EXINT(P77_A7_MHL_CTRL_07, _BIT7) != GET_TMDS_RX3_CLK_MODE()))
    {
        ScalerSetBit_EXINT(P77_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);

        if(GET_TMDS_RX3_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
        {
            usTemp = 500;

            // Wait until RGB detection is done or timeout(3ms)
            while((ScalerGetBit_EXINT(P72_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) != (_BIT7 | _BIT6 | _BIT5)) &&
                  (--usTemp != 0))
            {
                DELAY_5US_EXINT();
            }

            if(usTemp == 0)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Int Process for MHL for D3 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3IntHandler_EXINT0(void) using 1
{
    // Check Discovery Pulse
    if(ScalerGetBit_EXINT(P68_A0_CBUS_CTRL_00, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0))
    {
        // Disable Discovery Done IRQ and Clear Discovery Flags
        ScalerSetBit_EXINT(P68_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2));

        // Disable Discovery Debounce
        ScalerSetBit_EXINT(P68_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Stuck Low IRQ and Clear Flag
        ScalerSetBit_EXINT(P68_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(ScalerGetBit_EXINT(P7C_18_IMPEDANCE_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
        {
            // Suspend Key Calculation before load key
            ScalerSetBit_EXINT(P72_AE_TMDS_RPS, ~_BIT1, 0x00);
        }

        // Enable GDI BandGap
        ScalerSetBit_EXINT(P1D_14_BANDGAP_00, ~_BIT7, _BIT7);

        // Manual Disable CBUS PHY PSM
        ScalerSetBit_EXINT(P67_A1_CBUS_EN_1, ~_BIT0, 0x00);

        // Enable RX_EN
        ScalerSetBit_EXINT(P7C_1A_CMU_00, ~_BIT7, _BIT7);

        // Port 3 Z0 Enable
        ScalerSetBit_EXINT(P7C_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Clear HDCP Flags
        ScalerSetBit_EXINT(P72_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

        SET_MHL_RX3_PROCESS_STATE(_MHL_STATE_DISCOVERY_DONE);
        SET_MHL_RX3_READY_TO_TRANSMIT();
    }

    // Check Stuck Low Flag
    if(ScalerGetBit_EXINT(P68_A4_CBUS_CTRL_04, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit_EXINT(P68_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit_EXINT(P68_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        CLR_DIGITAL_PORT_SWITCH_TO_D3();

        // Port 3 Z0 Disable
        ScalerSetBit_EXINT(P7C_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Disable Auto K-offset Auto Mode
        ScalerSetBit_EXINT(P7C_24_KOFFSET_00, ~_BIT5, 0x00);

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)))
        // Reset Authenticated FSM
        ScalerSetByte_EXINT(P2E_28_HDCP_I2C_CTRL_2, 0x01);
        ScalerSetBit_EXINT(P2E_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);

        // Cancel HDCP 2.2 Re-Auth Timer Event
        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX3_HDCP2_REAUTH);
#endif
        // Manual Enable CBUS PHY PSM
        ScalerSetBit_EXINT(P67_A1_CBUS_EN_1, ~_BIT0, _BIT0);

        // Enable Discovery Debounce
        ScalerSetBit_EXINT(P68_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit_EXINT(P68_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif
        // Reset CBUS Core Function
        ScalerSetBit_EXINT(P68_A0_CBUS_CTRL_00, ~(_BIT7), _BIT7);
        ScalerSetBit_EXINT(P68_A0_CBUS_CTRL_00, ~(_BIT7), 0x00);

        CLR_MHL_RX3_MHL_VERSION();
        SET_MHL_RX3_PROCESS_STATE(_MHL_STATE_INITIAL);
        CLR_MHL_RX3_ADOPTER_ID_HBYTE();
        CLR_MHL_RX3_ADOPTER_ID_LBYTE();
        CLR_MHL_RX3_ADOPTER_ID_DONE();
        CLR_MHL_RX3_CBUS_RESET_FOR_HTC_DONE();
        CLR_MHL_RX3_SENT_MSC_DCAP_RDY();
        CLR_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE();
        SET_MHL_RX3_WRITE_BURST_PROCESS_DONE();

        ScalerMHLRx3DataPortInitial_EXINT0();
    }
}

//--------------------------------------------------
// Description  : Send MSC HPD Operation for D3 Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Fail
//--------------------------------------------------
bit ScalerMHLRx3MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue)
{
    BYTE ucResultPacket = 0;

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
    DebugMessageMHL("MSC Send Command", enumMSCCommand);
    DebugMessageMHL("Offset", enumMSCOffset);
    DebugMessageMHL("Data", enumMSCValue);
#endif

    if(GET_MHL_RX3_READY_TO_TRANSMIT() == _TRUE)
    {
        ucResultPacket = ScalerMHLRx3MscFIFOSendCommand(enumMSCCommand, enumMSCOffset, enumMSCValue, 0, _NULL_POINTER);

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                SET_MHL_RX3_READY_TO_TRANSMIT();

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("Rx3 MSC MHL_SUCCESS", ScalerGetByte(P68_D2_CBUS_CTRL_32));
#endif
                return _SUCCESS;
                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

                CLR_MHL_RX3_READY_TO_TRANSMIT();
                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX3_READY_TO_TRANSMIT);

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("Rx3 MSC MHL_ABORT_FAIL", ScalerGetByte(P68_D2_CBUS_CTRL_32));
#endif
                return _FAIL;
                break;

            case _MHL_PROTOCOL_ERROR: // Source Reply Data Packet Instead of Control Packet

                ScalerMHLRx3MscFIFOSendCommand(_MSC_ABORT, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE, 0, _NULL_POINTER);

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("Rx3 MSC MHL_PROTOCOL_ERROR", ScalerGetByte(P68_D2_CBUS_CTRL_32));
#endif
                return _FAIL;
                break;

            default: // Source Reply No Packet(Timeout) or NACK

                return _FAIL;
                break;
        }
    }
    else
    {
        return _FAIL;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Send Write Burst Operation for D3 Port
// Input Value  : ucDataLength --> Data Length
//                pucData --> Data
//                ucMode --> Write Burst Mode
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
bit ScalerMHLRx3MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode)
{
    BYTE ucResultPacket = 0;

    if(enumMode == _MHL_WRITE_BURST_WITH_REQ)
    {
        // Clear Grant To Write Flag
        ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT);

        // Send Request to Write
        ScalerMHLRx3MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT);

        // Disable Access Port Auto Increase
        ScalerSetBit(P68_AB_CBUS_CTRL_0B, ~_BIT0, 0x00);

        // Polling Grant to Write
        ScalerSetByte(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT);
        ScalerTimerPollingFlagProc(100, P68_AD_CBUS_CTRL_0D, _MSC_GRT_WRT, _TRUE);

        // Enable Access Port Auto Increase
        ScalerSetBit(P68_AB_CBUS_CTRL_0B, ~_BIT0, _BIT0);
    }

    if(GET_MHL_RX3_READY_TO_TRANSMIT() == _TRUE)
    {
        ucResultPacket = ScalerMHLRx3MscFIFOSendCommand(_MSC_WRITE_BURST, ucOffset, 0x00, ucDataLength, pucData);

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                // Send Device Scratchpad Change
                ScalerMHLRx3MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_DSCR_CHG);

                return _SUCCESS;

                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

                CLR_MHL_RX3_READY_TO_TRANSMIT();
                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX3_READY_TO_TRANSMIT);

                return _FAIL;
                break;

            case _MHL_PROTOCOL_ERROR: // Source Reply Data Packet Instead of Control Packet

                ScalerMHLRx3MscFIFOSendCommand(_MSC_ABORT, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE, 0, _NULL_POINTER);

                return _FAIL;
                break;

            default: // Source Reply No Packet(Timeout) or NACK

                return _FAIL;
                break;
        }
    }
    else
    {
        return _FAIL;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Read Device Capabilities for D3 Port
// Input Value  : enumMSCOffset --> Device Capability Offset
//                pucData --> Data to be Read
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
bit ScalerMHLRx3MscReadDevCapabilities(EnumMHLMscOffset enumMSCOffset, BYTE *pucData, BYTE ucExtended)
{
    BYTE ucResultPacket = 0;

    ucExtended = ucExtended;

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
    DebugMessageMHL("ReadDev at Offset", enumMSCOffset);
#endif

    if(GET_MHL_RX3_READY_TO_TRANSMIT() == _TRUE)
    {
        ucResultPacket = ScalerMHLRx3MscFIFOSendCommand(_MSC_READ_DEVCAP, enumMSCOffset, _MSC_NULL_VALUE, 0, pucData);

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                SET_MHL_RX3_READY_TO_TRANSMIT();

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("Rx3 ReadDev MHL_SUCCESS", ScalerGetByte(P68_D2_CBUS_CTRL_32));
#endif
                return _SUCCESS;

                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

                CLR_MHL_RX3_READY_TO_TRANSMIT();
                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX3_READY_TO_TRANSMIT);

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("Rx3 ReadDev MHL_ABORT_FAIL", ScalerGetByte(P68_D2_CBUS_CTRL_32));
#endif
                return _FAIL;
                break;

            case _MHL_PROTOCOL_ERROR: // Source Reply Data Packet Instead of Control Packet

                ScalerMHLRx3MscFIFOSendCommand(_MSC_ABORT, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE, 0, _NULL_POINTER);

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("Rx3 ReadDev MHL_PROTOCOL_ERROR", ScalerGetByte(P68_D2_CBUS_CTRL_32));
#endif
                return _FAIL;
                break;

            default: // Source Reply No Packet(Timeout) or NACK

                return _FAIL;
                break;
        }
    }
    else
    {
        return _FAIL;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Send MSC HPD Operation for D3 Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
BYTE ScalerMHLRx3MscFIFOSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData)
{
    BYTE ucTimeOut = 100;
    BYTE ucSendType = 0;
    BYTE ucWaitType = 0;
    BYTE ucI = 0;

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
    DebugMessageMHL("RX3_MHL_READY_TO_TRANSMIT", 0x02);
#endif

    switch(enumMSCCommand)
    {
        case _MSC_SET_INT:
        case _MSC_MSG:
        case _MSC_WRITE_XSTAT:

            ucSendType = _MSC_SEND_COM_OFF_DAT;
            ucWaitType = _MSC_WAIT_COMMAND;
            break;

        case _MSC_READ_DEVCAP:
        case _MSC_READ_XDEVCAP:

            ucSendType = _MSC_SEND_COM_OFF;
            ucWaitType = _MSC_WAIT_COM_DAT;
            break;

        case _MSC_SET_HPD:

            ucSendType = _MSC_SEND_COMMAND;
            ucWaitType = _MSC_WAIT_COMMAND;
            break;

        case _MSC_ABORT:

            ucSendType = _MSC_SEND_COMMAND;
            ucWaitType = _MSC_WAIT_NULL;
            break;

        case _MSC_WRITE_BURST:

            ucSendType = _MSC_SEND_COM_OFF_DAT_COM;
            ucWaitType = _MSC_WAIT_COMMAND;
            break;

        default:

            break;
    }

    // Check If Source Has Sent An ABORT Packet
    if(ScalerGetBit(P68_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
    {
        ScalerSetByte(P68_CF_CBUS_CTRL_2F, _BIT2);

        ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX3_READY_TO_TRANSMIT);

        CLR_MHL_RX3_READY_TO_TRANSMIT();

        return _MHL_FAIL;
    }

    // Clear FIFO and Send Command Only
    ScalerSetByte(P68_DE_CBUS_CTRL_3E, (_BIT6 | ucSendType));

    // Set MSC Command
    ScalerSetByte(P68_DF_CBUS_CTRL_3F, enumMSCCommand);

    // Set MSC Offset
    ScalerSetByte(P68_E1_CBUS_CTRL_41, enumMSCOffset);

    if(enumMSCCommand == _MSC_WRITE_BURST)
    {
        // Set MSC Last Command
        ScalerSetByte(P68_E0_CBUS_CTRL_40, _MSC_EOF_PACKET);

        // Set MSC Data
        for(ucI = 0; ucI < ucDataLength; ucI++)
        {
            ScalerSetByte(P68_E2_CBUS_CTRL_42, pucData[ucI]);
        }
    }
    else if((enumMSCCommand != _MSC_READ_DEVCAP) && (enumMSCCommand != _MSC_READ_XDEVCAP))
    {
        // Set MSC Value
        ScalerSetByte(P68_E2_CBUS_CTRL_42, enumMSCValue);
    }

    // MSC Packet and Wait Type
    ScalerSetBit(P68_E3_CBUS_CTRL_43, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), ((_MSC_PACKET << 6) | ucWaitType));

    // Send Request
    ScalerSetBit(P68_DE_CBUS_CTRL_3E, ~(_BIT7), _BIT7);

    // Check if Process is finished
    while(--ucTimeOut != 0)
    {
        if(ScalerGetBit(P68_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
        {
            // Clear Flag
            ScalerSetBit(P68_CF_CBUS_CTRL_2F, ~_BIT2, _BIT2);

            return _MHL_ABORT_FAIL;
        }
        else if((ScalerGetBit(P68_F6_CBUS_CTRL_56, _BIT7) == _BIT7) && (ScalerGetBit(P68_F7_CBUS_CTRL_57, _BIT7) == 0x00))
        {
            // Clear Flag
            ScalerSetBit(P68_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);

            if(ucWaitType == _MSC_WAIT_NULL)
            {
                return _MHL_SUCCESS;
            }
            else
            {
                // Check ACK Packet
                if(ScalerGetByte(P68_E4_CBUS_CTRL_44) == _MSC_ACK_PACKET)
                {
                    if((enumMSCCommand == _MSC_READ_DEVCAP) || (enumMSCCommand == _MSC_READ_XDEVCAP))
                    {
                        *pucData = ScalerGetByte(P68_E5_CBUS_CTRL_45);
                    }

                    return _MHL_SUCCESS;
                }
                else
                {
                    return _MHL_FAIL;
                }
            }
        }
        else if((ScalerGetBit(P68_F7_CBUS_CTRL_57, _BIT7) == _BIT7) && (ScalerGetByte(P68_D2_CBUS_CTRL_32) == _MSC_PROTOCOL_ERROR))
        {
            // Clear Flags
            ScalerSetBit(P68_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
            ScalerSetBit(P68_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);

            return _MHL_PROTOCOL_ERROR;
        }

        ScalerTimerDelayXms(1);
    }

    // Clear Flag
    ScalerSetBit(P68_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
    ScalerSetBit(P68_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);

    return _MHL_FAIL;
}

//--------------------------------------------------
// Description  : Check Write Status for D3 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx3MscCheckDeviceINT(void)
{
    WORD usTmp = 0;
    BYTE ucBirstLength = 0;
    BYTE pucWriteBurstTmp[16];

    /***************************************************************/
    /************* Get MSC_MSG(0x68) Invalid Command ***************/
    /***************************************************************/

    if(((bit)ScalerGetBit(P68_CE_CBUS_CTRL_2E, _BIT3) == _TRUE) && ((bit)ScalerGetBit(P68_D4_CBUS_CTRL_34, _BIT1) == _TRUE))
    {
        if(ScalerMHLRx3MscSendCommand(_MSC_MSG, _MSC_MSGE, _MSCE_INVALID_SUB_CMD) == _TRUE)
        {
            // Clear Falgs
            ScalerSetBit(P68_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
            ScalerSetBit(P68_D4_CBUS_CTRL_34, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
        }
    }


    /**************************************************************/
    /******** Get MSC Command WRITE_STAT or SET_INT(0x60) *********/
    /**************************************************************/

    if((bit)ScalerGetBit(P68_CE_CBUS_CTRL_2E, _BIT7) == _TRUE)
    {
        //----------------------------------------------------------//
        //-------- Check DevCap Ready (DCAP_RDY, DCAP_CHG) ---------//
        //----------------------------------------------------------//
        if((((bit)ScalerGetDataPortBit(P68_AC_CBUS_CTRL_0C, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY) == _TRUE) ||
            ((bit)ScalerGetDataPortBit(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)))
        {
            if(GET_MHL_RX3_MHL_VERSION() == _MHL_VERSION_NULL)
            {
                // Read Source Device MHL Version
                if(ScalerMHLRx3MscReadDevCapabilities(_MSC_MHL_VERSION_01, &g_ucMHLRx3MhlVersion, _MSC_READ_DEVCAP) == _TRUE)
                {
                    if((bit)ScalerGetDataPortBit(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)
                    {
                        // Write 1 Clear DevCap_Chg Flag
                        ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG);
                    }

                    // Clear Flag
                    ScalerSetBit(P68_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                }
            }

            // Read Source Adopter ID
            if((GET_MHL_RX3_ADOPTER_ID_DONE() == _FALSE) && (GET_MHL_RX3_READY_TO_TRANSMIT() == _TRUE))
            {
                if((ScalerMHLRx3MscReadDevCapabilities(_MSC_ADOPTER_ID_H_03, &g_ucMHLRx3AdopterIDH, _MSC_READ_DEVCAP) == _TRUE) &&
                   (ScalerMHLRx3MscReadDevCapabilities(_MSC_ADOPTER_ID_L_04, &g_ucMHLRx3AdopterIDL, _MSC_READ_DEVCAP) == _TRUE))
                {
                    DebugMessageMHL("D3 MHL Adopter IDH", g_ucMHLRx3AdopterIDH);
                    DebugMessageMHL("D3 MHL Adopter IDL", g_ucMHLRx3AdopterIDL);

                    SET_MHL_RX3_ADOPTER_ID_DONE();

                    if((bit)ScalerGetDataPortBit(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)
                    {
                        // Write 1 Clear DevCap_Chg Flag
                        ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG);
                    }

                    // Clear Flag
                    ScalerSetBit(P68_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
                }
            }
        }

        //----------------------------------------------//
        //------ Check Request To Write (REQ_WRT) ------//
        //----------------------------------------------//
        if(((bit)ScalerGetDataPortBit(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _TRUE) && (GET_MHL_RX3_WRITE_BURST_PROCESS_DONE() == _TRUE))
        {
            if(ScalerMHLRx3MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_GRT_WRT) == _SUCCESS)
            {
                CLR_MHL_RX3_WRITE_BURST_PROCESS_DONE();

                // Clear Flag
                ScalerSetBit(P68_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

                // Clear _MSC_REQ_WRT Flag
                ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT);
            }
        }

        //-----------------------------------------------------------//
        //-- Check 3D Request and Reply No Support For All Timings --//
        //-----------------------------------------------------------//
        if((bit)ScalerGetDataPortBit(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ) == _TRUE)
        {
            // 3D_VIC Header
            pucWriteBurstTmp[0] = _MHL_3D_VIC_HB;
            pucWriteBurstTmp[1] = _MHL_3D_VIC_LB;

            // Total Entries -> 0
            pucWriteBurstTmp[3] = 0x00;

            // SEQ -> 1
            pucWriteBurstTmp[4] = 0x01;

            // NUM_ENT -> 0
            pucWriteBurstTmp[5] = 0x00;

            // Checksum -> 256 - Sum{pucWriteBurstTmp[i]}
            pucWriteBurstTmp[2] = 256 - (pucWriteBurstTmp[0] + pucWriteBurstTmp[1] + pucWriteBurstTmp[3] + pucWriteBurstTmp[4] + pucWriteBurstTmp[5]);

            // 3D_DTD Header
            pucWriteBurstTmp[6] = _MHL_3D_DTD_HB;
            pucWriteBurstTmp[7] = _MHL_3D_DTD_LB;

            // Total Entries -> 0
            pucWriteBurstTmp[9] = 0x00;

            // SEQ -> 1
            pucWriteBurstTmp[10] = 0x01;

            // NUM_ENT -> 0
            pucWriteBurstTmp[11] = 0x00;

            // Checksum -> 256 - Sum{pucWriteBurstTmp[i]}
            pucWriteBurstTmp[8] = 256 - (pucWriteBurstTmp[6] + pucWriteBurstTmp[7] + pucWriteBurstTmp[9] + pucWriteBurstTmp[10] + pucWriteBurstTmp[11]);

            ucBirstLength = 6;

            if(ScalerMHLRx3MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
            {
                usTmp = 400;

                while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                {
                    ScalerTimerDelayXms(5);
                }

                if(ScalerMHLRx3MscSendWriteBurst(0x40, ucBirstLength, &pucWriteBurstTmp[0], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                {
                    if(ScalerMHLRx3MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                    {
                        usTmp = 400;

                        while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                        {
                            ScalerTimerDelayXms(5);
                        }

                        if(ScalerMHLRx3MscSendWriteBurst(0x40, ucBirstLength, &pucWriteBurstTmp[ucBirstLength], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                        {
                            ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ);

                            // Clear Flag
                            ScalerSetBit(P68_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                        }
                    }
                }
            }
        }
    }

    /****************************************************************/
    /********* Source Device Reading Sink MSC Error Code ************/
    /****************************************************************/

    if((bit)ScalerGetBit(P68_CE_CBUS_CTRL_2E, _BIT0) == _TRUE)
    {
        // Clear Flag
        ScalerSetBit(P68_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    // Sent Command to Triger VBUS for HTC M8
    if(((GET_MHL_RX3_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX3_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) &&
       (GET_MHL_RX3_SENT_MSC_DCAP_RDY() == _FALSE) && (GET_MHL_RX3_PROCESS_STATE() == _MHL_STATE_SET_DEV_CAP_DONE))
    {
        ScalerMHLRx3MscSendCommand(_MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);
        DebugMessageRx3("D3 MHL Sent Devies Capabilitly Ready", 0);
        SET_MHL_RX3_SENT_MSC_DCAP_RDY();
    }

#if(_D3_MHL_VERSION < _MHL_VERSION_3_0)

    // MHL Version Switch to 1.2 For Samsung Note4
    if(((GET_MHL_RX3_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX3_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE)) &&
       (GET_MHL_RX3_MHL_VERSION() >= _MHL_VERSION_3_0) && (GET_MHL_RX3_CBUS_RESET_FOR_HTC_DONE() == _FALSE))
    {
        ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _MHL_VERSION_1_2);

        ScalerMHLRx3MscSendCommand(_MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);

        SET_MHL_RX3_CBUS_RESET_FOR_HTC_DONE();
    }

#endif // End of #if(_D3_MHL_VERSION < _MHL_VERSION_3_0)

#if(_MHL_CBUS_CTS_MODE == _ON)

    if(ScalerGetBit(P68_CE_CBUS_CTRL_2E, _BIT5) == _BIT5)
    {
        ScalerSetByte(P68_C8_CBUS_CTRL_28, _BIT6);

        ScalerSetByte(P68_CE_CBUS_CTRL_2E, _BIT5);
    }

    if(ScalerGetBit(P68_CE_CBUS_CTRL_2E, _BIT4) == _BIT4)
    {
        ScalerSetByte(P68_C8_CBUS_CTRL_28, 0x00);

        ScalerSetByte(P68_CE_CBUS_CTRL_2E, _BIT4);
    }

#endif // Enf of #if(_MHL_CBUS_CTS_MODE == _ON)
}

//--------------------------------------------------
// Description  : MSC Handler for D3 Port
// Input Value  : ucActivePort --> Current Active Port
//                ucModeState --> Current Mode State
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx3MscHandler(BYTE ucActivePort, BYTE ucModeState)
{
    // Check if Discovery State is done and send HPD & Device Capabilities Ready
    switch(GET_MHL_RX3_PROCESS_STATE())
    {
        case _MHL_STATE_INITIAL:

            ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_MHL_RX3_RECONNECT_1K);

            return _FALSE;
            break;

        case _MHL_STATE_DISCOVERY_DONE:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX3_RECONNECT_1K);

            ScalerMHLRx3SetDevCapReg();

            ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE);

            DebugMessageMHL("D3 MHL Discovery Done", 0x00);

            SET_MHL_RX3_PROCESS_STATE(_MHL_STATE_SET_DEV_CAP_DONE);

            break;

        default:
            break;
    }

    // Send HPD, PATH_EN and Device Capabilities Ready For Source
    if((ucActivePort == _D3_INPUT_PORT) && (ucModeState != _MODE_STATUS_INITIAL) && (ucModeState != _MODE_STATUS_POWER_OFF))
    {
        switch(GET_MHL_RX3_PROCESS_STATE())
        {
            case _MHL_STATE_SET_DEV_CAP_DONE:

                if(ScalerMHLRx3MscSendCommand(_MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY) == _SUCCESS)
                {
                    DebugMessageMHL("D3 MHL Dev Cap RDY", 0x30);

                    SET_MHL_RX3_PROCESS_STATE(_MHL_STATE_DEV_CAP_RDY);
                }

                return _TRUE;
                break;

            case _MHL_STATE_DEV_CAP_RDY:

                ScalerTimerDelayXms(150);

                if(ScalerMHLRx3MscSendCommand(_MSC_SET_HPD, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE) == _SUCCESS)
                {
                    DebugMessageMHL("D3 MHL HPD Done", 0x30);

                    SET_MHL_RX3_PROCESS_STATE(_MHL_STATE_HPD_DONE);
                }

                return _TRUE;
                break;

            case _MHL_STATE_HPD_DONE:

                if((GET_MHL_RX3_ADOPTER_ID_HBYTE() == _ZTE_NUBIA_Z5_ADOPTER_ID_HBYTE) && (GET_MHL_RX3_ADOPTER_ID_LBYTE() == _ZTE_NUBIA_Z5_ADOPTER_ID_LBYTE))
                {
                    ScalerTimerDelayXms(50);
                }

                if(ScalerMHLRx3MscSendCommand(_MSC_WRITE_STAT, _MSC_LINK_MODE, _MSC_PATH_EN) == _SUCCESS)
                {
                    DebugMessageMHL("D3 MHL Path Enabled", 0x20);

                    SET_MHL_RX3_PROCESS_STATE(_MHL_STATE_PATH_EN_DONE);

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE);
                }

                return _TRUE;
                break;

            case _MHL_STATE_PATH_EN_DONE:

                if(GET_TMDS_RX3_PHY_SET() == _TRUE)
                {
                    DebugMessageMHL("D3 MHL CBUS Done", 0x00);

                    SET_MHL_RX3_PROCESS_STATE(_MHL_STATE_DONE);
                }

                return _TRUE;
                break;

            case _MHL_STATE_DONE:
            default:

                return _TRUE;
                break;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : RAP Process for D3 Port
// Input Value  : None
// Output Value : True or False (False if Content Off)
//--------------------------------------------------
bit ScalerMHLRx3MscRAPHandler(void)
{
    // Check RAP Command
    if((bit)ScalerGetBit(P68_D4_CBUS_CTRL_34, _BIT3) == _TRUE)
    {
        switch(ScalerGetByte(P68_DC_CBUS_CTRL_3C))
        {
            case _MSC_RAP_POLL:
            case _MSC_RAP_CONTENT_ON:

                // Reply RAPK and No Error
                ScalerMHLRx3MscSendCommand(_MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                // Clear Flag
                ScalerSetByte(P68_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                return _TRUE;
                break;

            case _MSC_RAP_CONTENT_OFF:

                // Reply RAPK and No Error
                ScalerMHLRx3MscSendCommand(_MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                // Clear Flag
                ScalerSetByte(P68_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                return _FALSE;
                break;

            default:

                // Reply RAPK and Ineffective Code
                ScalerMHLRx3MscSendCommand(_MSC_MSG, _MSC_RAPK, _MSC_RAPK_UNRECOGNIZE_CODE);

                // Clear Flag
                ScalerSetByte(P68_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                return _TRUE;
                break;
        }
    }

    return _TRUE;
}

#if(_MHL_UCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get UCP Key Code for D3 Port
// Input Value  : UCP Key Code
// Output Value : True or False
//--------------------------------------------------
BYTE ScalerMHLRx3MscUCPGetCommand(BYTE *pucKeyCode)
{
    // Check UCP Command
    if(((bit)ScalerGetBit(P68_12_OCBUS_CTRL_12, _BIT4) == _TRUE) && (ScalerGetByte(P68_D6_CBUS_CTRL_36) == _MSC_UCP))
    {
        // Clear Flag
        ScalerSetByte(P68_12_OCBUS_CTRL_12, (BYTE)_BIT4);

        pucKeyCode[0] = ScalerGetByte(P68_19_OCBUS_CTRL_19);

        return _TRUE;
    }

    return _FALSE;
}
#endif  // End of #if(_MHL_UCP_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Signal PreDetection for MHL(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerMHLRx3PSPreDetect(void)
{
    //---------------------------------------//
    //-------- Check RAP Content OFF --------//
    //---------------------------------------//
    if(ScalerGetByte(P68_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
    {
        return _FAIL;
    }

    //------------------------------------------------------------//
    //-------- PSM --> PNM While Wake Up Pulses Received ---------//
    //------------------------------------------------------------//
    if(ScalerGetBit(P68_A0_CBUS_CTRL_00, (_BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4 | _BIT3))
    {
        return _TRUE;
    }

    //------------------------------------------------------------//
    //------- Pre-Detect True By Switch Back to MHL Port ---------//
    //------------------------------------------------------------//
    if(GET_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE() == _TRUE)
    {
        CLR_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE();

        return _TRUE;
    }

    //------------------------------------------------------------//
    //-------- Pre-Detect True By MHL Clk Measure Stable ---------//
    //------------------------------------------------------------//

    // Reset Freq. Detect Counter(Toggle)
    ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear Freq. Stable Flag
    ScalerSetBit(P72_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear Unstable Flag
    ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 5 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P72_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P72_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
    }

    switch(GET_MHL_RX3_PROCESS_STATE())
    {
        case _MHL_STATE_INITIAL:
        case _MHL_STATE_PATH_EN_DONE:
        case _MHL_STATE_DONE:

            return _FAIL;
            break;

        default:

            return _SUCCESS;
            break;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Signal PreDetection for MHL(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerMHLRx3NormalPreDetect(void)
{
    //---------------------------------------//
    //-------- Check RAP Content OFF --------//
    //---------------------------------------//
    if(ScalerGetByte(P68_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
    {
        return _FAIL;
    }

    //------------------------------------------------------------//
    //------- Pre-Detect True By Switch Back to MHL Port ---------//
    //------------------------------------------------------------//
    if(GET_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE() == _TRUE)
    {
        CLR_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE();

        return _TRUE;
    }

    ScalerTimerDelayXms(6);

    if(GET_TMDS_RX3_PHY_SET() == _TRUE)
    {
        return _SUCCESS;
    }

    switch(GET_MHL_RX3_PROCESS_STATE())
    {
        case _MHL_STATE_INITIAL:
        case _MHL_STATE_PATH_EN_DONE:

            return _FAIL;
            break;

        default:

            return _SUCCESS;
            break;
    }

    return _FAIL;
}
#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
