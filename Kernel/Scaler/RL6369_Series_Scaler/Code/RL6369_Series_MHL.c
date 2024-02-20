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
// ID Code      : RL6369_Series_MHL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MHL__

#include "ScalerFunctionInclude.h"

#if(_MHL_SUPPORT == _ON)

#if(_MHL_CBUS_CTS_MODE == _ON)
#warning "MHL CBUS CTS Mode is Enabled!! Only Used for RL6193-D and Earlier Ver IC when CTS Test!!!"
#endif

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#define GET_MHL_RX0_ADOPTER_ID_DONE()                   (g_bMHLRx0AdopterIDDone)
#define SET_MHL_RX0_ADOPTER_ID_DONE()                   (g_bMHLRx0AdopterIDDone = _TRUE)
#define CLR_MHL_RX0_ADOPTER_ID_DONE()                   (g_bMHLRx0AdopterIDDone = _FALSE)

#define GET_MHL_RX0_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx0CbusResetForHTCDone)
#define SET_MHL_RX0_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx0CbusResetForHTCDone = _TRUE)
#define CLR_MHL_RX0_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx0CbusResetForHTCDone = _FALSE)

#define GET_MHL_RX0_SENT_MSC_DCAP_RDY()                 (g_bMHLRx0SentMscDcapRdy)
#define SET_MHL_RX0_SENT_MSC_DCAP_RDY()                 (g_bMHLRx0SentMscDcapRdy = _TRUE)
#define CLR_MHL_RX0_SENT_MSC_DCAP_RDY()                 (g_bMHLRx0SentMscDcapRdy = _FALSE)

#define GET_MHL_RX0_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx0WriteBurstProcessDone)
#define SET_MHL_RX0_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx0WriteBurstProcessDone = _TRUE)
#define CLR_MHL_RX0_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx0WriteBurstProcessDone = _FALSE)

#define GET_MHL_RX0_MHL_VERSION()                       (g_ucMHLRx0MhlVersion)
#define SET_MHL_RX0_MHL_VERSION(x)                      (g_ucMHLRx0MhlVersion = (x))
#define CLR_MHL_RX0_MHL_VERSION()                       (g_ucMHLRx0MhlVersion = 0x00)
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#define GET_MHL_RX1_ADOPTER_ID_DONE()                   (g_bMHLRx1AdopterIDDone)
#define SET_MHL_RX1_ADOPTER_ID_DONE()                   (g_bMHLRx1AdopterIDDone = _TRUE)
#define CLR_MHL_RX1_ADOPTER_ID_DONE()                   (g_bMHLRx1AdopterIDDone = _FALSE)

#define GET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx1CbusResetForHTCDone)
#define SET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx1CbusResetForHTCDone = _TRUE)
#define CLR_MHL_RX1_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx1CbusResetForHTCDone = _FALSE)

#define GET_MHL_RX1_SENT_MSC_DCAP_RDY()                 (g_bMHLRx1SentMscDcapRdy)
#define SET_MHL_RX1_SENT_MSC_DCAP_RDY()                 (g_bMHLRx1SentMscDcapRdy = _TRUE)
#define CLR_MHL_RX1_SENT_MSC_DCAP_RDY()                 (g_bMHLRx1SentMscDcapRdy = _FALSE)

#define GET_MHL_RX1_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx1WriteBurstProcessDone)
#define SET_MHL_RX1_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx1WriteBurstProcessDone = _TRUE)
#define CLR_MHL_RX1_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx1WriteBurstProcessDone = _FALSE)

#define GET_MHL_RX1_MHL_VERSION()                       (g_ucMHLRx1MhlVersion)
#define SET_MHL_RX1_MHL_VERSION(x)                      (g_ucMHLRx1MhlVersion = (x))
#define CLR_MHL_RX1_MHL_VERSION()                       (g_ucMHLRx1MhlVersion = 0x00)
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#define GET_MHL_RX2_ADOPTER_ID_DONE()                   (g_bMHLRx2AdopterIDDone)
#define SET_MHL_RX2_ADOPTER_ID_DONE()                   (g_bMHLRx2AdopterIDDone = _TRUE)
#define CLR_MHL_RX2_ADOPTER_ID_DONE()                   (g_bMHLRx2AdopterIDDone = _FALSE)

#define GET_MHL_RX2_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx2CbusResetForHTCDone)
#define SET_MHL_RX2_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx2CbusResetForHTCDone = _TRUE)
#define CLR_MHL_RX2_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx2CbusResetForHTCDone = _FALSE)

#define GET_MHL_RX2_SENT_MSC_DCAP_RDY()                 (g_bMHLRx2SentMscDcapRdy)
#define SET_MHL_RX2_SENT_MSC_DCAP_RDY()                 (g_bMHLRx2SentMscDcapRdy = _TRUE)
#define CLR_MHL_RX2_SENT_MSC_DCAP_RDY()                 (g_bMHLRx2SentMscDcapRdy = _FALSE)

#define GET_MHL_RX2_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx2WriteBurstProcessDone)
#define SET_MHL_RX2_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx2WriteBurstProcessDone = _TRUE)
#define CLR_MHL_RX2_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx2WriteBurstProcessDone = _FALSE)

#define GET_MHL_RX2_MHL_VERSION()                       (g_ucMHLRx2MhlVersion)
#define SET_MHL_RX2_MHL_VERSION(x)                      (g_ucMHLRx2MhlVersion = (x))
#define CLR_MHL_RX2_MHL_VERSION()                       (g_ucMHLRx2MhlVersion = 0x00)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
BYTE g_ucMHLRx0AdopterIDH = 0xFF;
BYTE g_ucMHLRx0AdopterIDL = 0xFF;
BYTE g_ucMHLRx0MhlVersion;
bit g_bMHLRx0AdopterIDDone = _FALSE;
bit g_bMHLRx0CbusResetForHTCDone = _FALSE;
bit g_bMHLRx0SentMscDcapRdy = _TRUE;
bit g_bMHLRx0WriteBurstProcessDone = _TRUE;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
BYTE g_ucMHLRx1AdopterIDH = 0xFF;
BYTE g_ucMHLRx1AdopterIDL = 0xFF;
BYTE g_ucMHLRx1MhlVersion;
bit g_bMHLRx1AdopterIDDone = _FALSE;
bit g_bMHLRx1CbusResetForHTCDone = _FALSE;
bit g_bMHLRx1SentMscDcapRdy = _TRUE;
bit g_bMHLRx1WriteBurstProcessDone = _TRUE;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
BYTE g_ucMHLRx2AdopterIDH = 0xFF;
BYTE g_ucMHLRx2AdopterIDL = 0xFF;
BYTE g_ucMHLRx2MhlVersion;
bit g_bMHLRx2AdopterIDDone = _FALSE;
bit g_bMHLRx2CbusResetForHTCDone = _FALSE;
bit g_bMHLRx2SentMscDcapRdy = _TRUE;
bit g_bMHLRx2WriteBurstProcessDone = _TRUE;
#endif

StructMHLProcessInfo g_pstMHLProcess[_MHL_PORT_VALID];
BYTE g_ucMHLPortActive;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMHLModeMHLSetting(BYTE ucInputPort);
void ScalerMHLModeHdmiSetting(BYTE ucInputPort);
void ScalerMHLInitialSettings(void);
void ScalerMHLCBUSPhySwitch(BYTE ucPortSelect, bit bSelect);
void ScalerMHLCBUSSwitchClk(EnumClkSel enumClockSel);
void ScalerMHLSetTimingRelateSetting(void);
void ScalerMHLCBUSResetProc(BYTE ucInputPort);
void ScalerMHLPowerOffProc(BYTE ucInputPort);
bit ScalerMHLDetectClkMode(void);
BYTE ScalerMHLDetectClkMode_EXINT0(void);
void ScalerMHLIntHandler_EXINT0(void);
bit ScalerMHLMscSendCommand(BYTE ucInputPort, EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
bit ScalerMHLMscSendWriteBurst(BYTE ucInputPort, BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);
bit ScalerMHLMscReadDevCapabilities(BYTE ucInputPort, EnumMHLMscOffset enumMSCOffset, BYTE *pucData, BYTE ucExtended);
BYTE ScalerMHLMscFIFOSendCommand(BYTE ucInputPort, EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData);
void ScalerMHLMscCheckDeviceINT(BYTE ucInputPort);

#if((_D0_CBUS_CHANNEL_SEL == _CBUS0) || (_D1_CBUS_CHANNEL_SEL == _CBUS0) || (_D2_CBUS_CHANNEL_SEL == _CBUS0))
void ScalerMHLMscCheckDeviceINTCBUS0(BYTE ucInputPort);
#endif

#if((_D0_CBUS_CHANNEL_SEL == _CBUS1) || (_D1_CBUS_CHANNEL_SEL == _CBUS1) || (_D2_CBUS_CHANNEL_SEL == _CBUS1))
void ScalerMHLMscCheckDeviceINTCBUS1(BYTE ucInputPort);
#endif
void ScalerMHLSetDevCapReg(void);
bit ScalerMHLMscHandler(BYTE ucInputPort, BYTE ucActivePort, BYTE ucModeState);
bit ScalerMHLMscRAPHandler(BYTE ucInputPort);
bit ScalerMHLMscRCPGetCommand(BYTE ucInputPort, BYTE *pucKeyCode);

#if(_MHL_UCP_SUPPORT == _ON)
BYTE ScalerMHLMscUCPGetCommand(BYTE ucInputPort, BYTE *pucKeyCode);
#endif

bit ScalerMHLPSPreDetect(BYTE ucInputPort);
bit ScalerMHLNormalPreDetect(BYTE ucInputPort);
void ScalerMHLTimerEventProc(EnumScalerTimerEventID enumEventID);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : TMDS Settings when MHL Mode for D0 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLModeMHLSetting(BYTE ucInputPort)
{
    // Disable Auto K-offset Auto Mode   /** RL6369 Reg. Mapping **/
    ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT6, 0x00);

    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            // Clear CBUS Reset Flag for HTC Butterfly Debug
            CLR_MHL_RX0_CBUS_RESET_FOR_HTC_DONE();

            // Clear CBUS Re-Sent DEVCAP_RDY Flag for HTC M8
            CLR_MHL_RX0_SENT_MSC_DCAP_RDY();

            // Clear CBUS Reset Flag for Other Port Discovery Done
            SET_MHL_SWITCH_PORT_DISCOVERY_DONE(0, _FALSE);

            PCB_D0_HDMI_MHL_SWITCH(_TMDS_SWITCH_MHL_CBUS);
            PCB_D0_MHL_VBUS_SWITCH(_MHL_VBUS_ON);

            // Port 0 Z0 Disable   /** RL6369 Reg. Mapping **/
            ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            CLR_DIGITAL_PORT_SWITCH_TO_D0();

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)
            // GPIO Select to CBUS
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, 0x00);
#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)
            // GPIO Select to CBUS
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, 0x00);
#endif // End of #if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

#if(_D0_DDC_CHANNEL_SEL == _DDC0)
            // Disable DDC0 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC0_SWITCH_GPIO);

            // Switch DDCRAM To MHL EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT0;

            // DDC0 Disable Force Nack and disable DDC Toggle IRQ
            MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
            // Disable DDC1 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_GPIO);

            // Switch DDCRAM To MHL EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT1;

            // DDC1 Disable Force Nack and disable DDC Toggle IRQ
            MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
            // Disable DDC2 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_GPIO);

            // Switch DDCRAM To MHL EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT2;

            // DDC2 Disable Force Nack and disable DDC Toggle IRQ
            MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#endif
            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            // Clear CBUS Reset Flag for HTC Butterfly Debug
            CLR_MHL_RX1_CBUS_RESET_FOR_HTC_DONE();

            // Clear CBUS Re-Sent DEVCAP_RDY Flag for HTC M8
            CLR_MHL_RX1_SENT_MSC_DCAP_RDY();

            // Clear CBUS Reset Flag for Other Port Discovery Done
            SET_MHL_SWITCH_PORT_DISCOVERY_DONE(1, _FALSE);

            PCB_D1_HDMI_MHL_SWITCH(_TMDS_SWITCH_MHL_CBUS);
            PCB_D1_MHL_VBUS_SWITCH(_MHL_VBUS_ON);

            // Port 1 Z0 Disable   /** RL6369 Reg. Mapping **/
            ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            CLR_DIGITAL_PORT_SWITCH_TO_D1();

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
            // GPIO Select to CBUS
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, 0x00);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
            // GPIO Select to CBUS
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, 0x00);
#endif // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

#if(_D1_DDC_CHANNEL_SEL == _DDC0)
            // Disable DDC0 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC0_SWITCH_GPIO);

            // Switch DDCRAM To MHL EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT0;

            // DDC0 Disable Force Nack and disable DDC Toggle IRQ
            MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
            // Disable DDC1 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_GPIO);

            // Switch DDCRAM To MHL EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT1;

            // DDC1 Disable Force Nack and disable DDC Toggle IRQ
            MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
            // Disable DDC2 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_GPIO);

            // Switch DDCRAM To MHL EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT2;

            // DDC2 Disable Force Nack and disable DDC Toggle IRQ
            MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#endif
            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            // Clear CBUS Reset Flag for HTC Butterfly Debug
            CLR_MHL_RX2_CBUS_RESET_FOR_HTC_DONE();

            // Clear CBUS Re-Sent DEVCAP_RDY Flag for HTC M8
            CLR_MHL_RX2_SENT_MSC_DCAP_RDY();

            // Clear CBUS Reset Flag for Other Port Discovery Done
            SET_MHL_SWITCH_PORT_DISCOVERY_DONE(2, _FALSE);

            PCB_D2_HDMI_MHL_SWITCH(_TMDS_SWITCH_MHL_CBUS);
            PCB_D2_MHL_VBUS_SWITCH(_MHL_VBUS_ON);

            // Port 2 Z0 Disable   /** RL6369 Reg. Mapping **/
            ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            CLR_DIGITAL_PORT_SWITCH_TO_D2();

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)
            // GPIO Select to CBUS
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, 0x00);
#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)
            // GPIO Select to CBUS
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, 0x00);
#endif // End of #if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

#if(_D2_DDC_CHANNEL_SEL == _DDC0)
            // Disable DDC0 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC0_SWITCH_GPIO);

            // Switch DDCRAM To MHL EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT0;

            // DDC0 Disable Force Nack and disable DDC Toggle IRQ
            MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
            // Disable DDC1 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_GPIO);

            // Switch DDCRAM To MHL EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT1;

            // DDC1 Disable Force Nack and disable DDC Toggle IRQ
            MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
            // Disable DDC2 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_GPIO);

            // Switch DDCRAM To MHL EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT2;

            // DDC2 Disable Force Nack and disable DDC Toggle IRQ
            MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#endif
            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Settings when HDMI Mode for D0 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLModeHdmiSetting(BYTE ucInputPort)
{
    ScalerMHLCBUSPhySwitch(ucInputPort, _OFF);

    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

            PCB_D0_HDMI_MHL_SWITCH(_TMDS_SWITCH_HDMI_HPD);
            PCB_D0_MHL_VBUS_SWITCH(_MHL_VBUS_OFF);

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)
            // GPIO Select to Hot Plug
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, _BIT2);
#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)
            // GPIO Select to Hot Plug
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, _BIT3);
#endif  // End of #if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

#if(_D0_DDC_CHANNEL_SEL == _DDC0)
            // Enable DDC0 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC0_SWITCH_DDC);

            // Switch DDCRAM To HDMI EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT0;

#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
            // DDC0 Enable Force Nack
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT5;
#endif

#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
            // Enable DDC1 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_DDC);

            // Switch DDCRAM To HDMI EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT1;

#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
            // DDC1 Enable Force Nack
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT5;
#endif

#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
            // Enable DDC2 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_DDC);

            // Switch DDCRAM To HDMI EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT2;

#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
            // DDC2 Enable Force Nack
            MCU_FE69_DDC2_EDID_IRQ |= _BIT5;
#endif

#endif // End of #if(_D0_DDC_CHANNEL_SEL == _DDC0)

            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

            PCB_D1_HDMI_MHL_SWITCH(_TMDS_SWITCH_HDMI_HPD);
            PCB_D1_MHL_VBUS_SWITCH(_MHL_VBUS_OFF);

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
            // GPIO Select to Hot Plug
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, _BIT2);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
            // GPIO Select to Hot Plug
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, _BIT3);
#endif  // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

#if(_D1_DDC_CHANNEL_SEL == _DDC0)
            // Enable DDC0 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC0_SWITCH_DDC);

            // Switch DDCRAM To HDMI EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT0;

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
            // DDC0 Enable Force Nack
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT5;
#endif

#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
            // Enable DDC1 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_DDC);

            // Switch DDCRAM To HDMI EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT1;

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
            // DDC1 Enable Force Nack
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT5;
#endif

#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
            // Enable DDC2 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_DDC);

            // Switch DDCRAM To HDMI EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT2;

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
            // DDC2 Enable Force Nack
            MCU_FE69_DDC2_EDID_IRQ |= _BIT5;
#endif

#endif // End of #if(_D1_DDC_CHANNEL_SEL == _DDC0)

            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

            PCB_D2_HDMI_MHL_SWITCH(_TMDS_SWITCH_HDMI_HPD);
            PCB_D2_MHL_VBUS_SWITCH(_MHL_VBUS_OFF);

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)
            // GPIO Select to Hot Plug
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, _BIT2);
#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)
            // GPIO Select to Hot Plug
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, _BIT3);
#endif  // End of #if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

#if(_D2_DDC_CHANNEL_SEL == _DDC0)
            // Enable DDC0 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC0_SWITCH_DDC);

            // Switch DDCRAM To HDMI EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT0;

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
            // DDC0 Enable Force Nack
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT5;
#endif

#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
            // Enable DDC1 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_DDC);

            // Switch DDCRAM To HDMI EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT1;

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
            // DDC1 Enable Force Nack
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT5;
#endif

#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
            // Enable DDC2 Channel
            ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_DDC);

            // Switch DDCRAM To HDMI EDID
            MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT2;

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
            // DDC2 Enable Force Nack
            MCU_FE69_DDC2_EDID_IRQ |= _BIT5;
#endif

#endif // End of #if(_D2_DDC_CHANNEL_SEL == _DDC0)

            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Calibration for 1K/100K and LDO Level Adjust
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLInitialSettings(void)
{
    // Adjust CBUS Input Comparator VIH = 0.9V and VIL = 0.7V
    ScalerSetByte(P27_A6_CBUS_INPUT_CONTROL, 0x09);

    // Set CBUS Min Vih
    ScalerSetBit(P27_A6_CBUS_INPUT_CONTROL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

#if(_MHL_CBUS_LDO_HIGH == _ENABLE)
    // Set CBUS Max Driving Strength, Set LDO to 1.75V Level
    ScalerSetBit(P27_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
#else
    // Set CBUS Max Driving Strength, Set LDO to 1.60V Level
    ScalerSetBit(P27_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
#endif

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)
    // DDC0 CBUS Swap Settings
    ScalerSetBit(P6F_04_CBUS0_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)
    // DDC0 CBUS Swap Settings
    ScalerSetBit(P6F_05_CBUS1_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_04_CBUS0_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_05_CBUS1_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);
#endif

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)
    // DDC2 CBUS Swap Settings
    ScalerSetBit(P6F_04_CBUS0_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x02);
#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)
    // DDC2 CBUS Swap Settings
    ScalerSetBit(P6F_05_CBUS1_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x02);
#endif

    // Discovery Function Power Down and System Clk Gated
    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2), _BIT6);
    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2), _BIT6);

    // Set MHL 1MHz Clk Divider
    ScalerSetBit(P28_A1_CBUS_CTRL_01, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT3 | _BIT2));
    ScalerSetBit(P29_A1_CBUS_CTRL_01, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT3 | _BIT2));

    // Set MHL 1KHz Clk Divider and Set Stuck Low Time to 150us
    ScalerSetBit(P28_A2_CBUS_CTRL_02, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), _BIT0);
    ScalerSetByte(P28_A3_CBUS_CTRL_03, 0xE2);
    ScalerSetBit(P29_A2_CBUS_CTRL_02, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), _BIT0);
    ScalerSetByte(P29_A3_CBUS_CTRL_03, 0xE2);

    // Set HW Bypass Wake Up Pulses Mode
    ScalerSetBit(P28_A4_CBUS_CTRL_04, ~(_BIT7 | _BIT1), _BIT7);
    ScalerSetBit(P29_A4_CBUS_CTRL_04, ~(_BIT7 | _BIT1), _BIT7);

    // Set MHL Wake pulse boundary 14~26
    ScalerSetBit(P28_A4_CBUS_CTRL_04, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT3));
    ScalerSetBit(P29_A4_CBUS_CTRL_04, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT3));

    // Set Discovery Upper/Lower Bound
    ScalerSetBit(P28_A5_CBUS_CTRL_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x5A);
    ScalerSetBit(P29_A5_CBUS_CTRL_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x5A);

    // Set Wake Up Pulse Number to 4
    ScalerSetBit(P28_A6_CBUS_CTRL_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
    ScalerSetBit(P29_A6_CBUS_CTRL_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    // Set CBUS (PHY) Power Saving Mode to Manual Mode
    ScalerSetByte(P28_A9_CBUS_CTRL_09, 0x00);
    ScalerSetByte(P29_A9_CBUS_CTRL_09, 0x00);

    ScalerMHLSetTimingRelateSetting();

    // Disable eCBUS APHY 50 Ohm at Initial
    ScalerSetBit(P27_06_ECBUS_Z0_CTRL_0, ~(_BIT3 | _BIT2), 0x00);
}

//--------------------------------------------------
// Description  : Power Process for CBUS Phy for D0 Port
// Input Value  : bSelect --> _ON/_OFF
// Output Value : None
//--------------------------------------------------
void ScalerMHLCBUSPhySwitch(BYTE ucPortSelect, bit bSelect)
{
    switch(ucPortSelect)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            if(bSelect == _ON)
            {
#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

                if(ScalerGetBit(P28_A8_CBUS_CTRL_08, _BIT5) == 0x00)
                {
                    // GPIO Select to CBUS
                    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, 0x00);

                    // Enable CBUS Phy, LDO, Input Comparator and Output Driver
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

                    // Discovery Function Power On and Enable System Clk
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT5);

                    // Enable Discovery IRQ
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

                    // MHL Attached
                    ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);

                    // Internal IRQ Enable (Global)
                    ScalerGlobalIRQControl(_ENABLE);

                    EX0 = 1;
                }
#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

                if(ScalerGetBit(P29_A8_CBUS_CTRL_08, _BIT5) == 0x00)
                {
                    // GPIO Select to CBUS
                    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, 0x00);

                    // Enable CBUS Phy, LDO, Input Comparator and Output Driver
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), (_BIT7 | _BIT5 | _BIT3 | _BIT1));

                    // Discovery Function Power On and Enable System Clk
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT5);

                    // Enable Discovery IRQ
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

                    // MHL Attached
                    ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);

                    // Internal IRQ Enable (Global)
                    ScalerGlobalIRQControl(_ENABLE);

                    EX0 = 1;
                }
#endif
            }
            else
            {
#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

                if(ScalerGetBit(P28_A8_CBUS_CTRL_08, _BIT5) == _BIT5)
                {
                    // Disable CBUS Phy, LDO, Input Comparator
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), 0x00);

                    // Discovery Function Power Down and System Clk Gated
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT6);

                    // Disable Discovery IRQ
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), _BIT2);

                    // MHL Unattached
                    ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                }
#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)
                if(ScalerGetBit(P29_A8_CBUS_CTRL_08, _BIT5) == _BIT5)
                {
                    // Disable CBUS Phy, LDO, Input Comparator
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), 0x00);

                    // Discovery Function Power Down and System Clk Gated
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT6);

                    // Disable Discovery IRQ
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), _BIT2);

                    // MHL Unattached
                    ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                }
#endif
            }

            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            if(bSelect == _ON)
            {
#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

                if(ScalerGetBit(P28_A8_CBUS_CTRL_08, _BIT5) == 0x00)
                {
                    // GPIO Select to CBUS
                    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, 0x00);

                    // Enable CBUS Phy, LDO, Input Comparator and Output Driver
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

                    // Discovery Function Power On and Enable System Clk
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT5);

                    // Enable Discovery IRQ
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

                    // MHL Attached
                    ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);

                    // Internal IRQ Enable (Global)
                    ScalerGlobalIRQControl(_ENABLE);

                    EX0 = 1;
                }
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

                if(ScalerGetBit(P29_A8_CBUS_CTRL_08, _BIT5) == 0x00)
                {
                    // GPIO Select to CBUS
                    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, 0x00);

                    // Enable CBUS Phy, LDO, Input Comparator and Output Driver
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), (_BIT7 | _BIT5 | _BIT3 | _BIT1));

                    // Discovery Function Power On and Enable System Clk
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT5);

                    // Enable Discovery IRQ
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

                    // MHL Attached
                    ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);

                    // Internal IRQ Enable (Global)
                    ScalerGlobalIRQControl(_ENABLE);

                    EX0 = 1;
                }
#endif
            }
            else
            {
#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

                if(ScalerGetBit(P28_A8_CBUS_CTRL_08, _BIT5) == _BIT5)
                {
                    // Disable CBUS Phy, LDO, Input Comparator
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), 0x00);

                    // Discovery Function Power Down and System Clk Gated
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT6);

                    // Disable Discovery IRQ
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), _BIT2);

                    // MHL Unattached
                    ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                }
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
                if(ScalerGetBit(P29_A8_CBUS_CTRL_08, _BIT5) == _BIT5)
                {
                    // Disable CBUS Phy, LDO, Input Comparator
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), 0x00);

                    // Discovery Function Power Down and System Clk Gated
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT6);

                    // Disable Discovery IRQ
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), _BIT2);

                    // MHL Unattached
                    ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                }
#endif
            }

            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            if(bSelect == _ON)
            {
#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

                if(ScalerGetBit(P28_A8_CBUS_CTRL_08, _BIT5) == 0x00)
                {
                    // GPIO Select to CBUS
                    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, 0x00);

                    // Enable CBUS Phy, LDO, Input Comparator and Output Driver
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

                    // Discovery Function Power On and Enable System Clk
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT5);

                    // Enable Discovery IRQ
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

                    // MHL Attached
                    ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);

                    // Internal IRQ Enable (Global)
                    ScalerGlobalIRQControl(_ENABLE);

                    EX0 = 1;
                }
#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

                if(ScalerGetBit(P29_A8_CBUS_CTRL_08, _BIT5) == 0x00)
                {
                    // GPIO Select to CBUS
                    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, 0x00);

                    // Enable CBUS Phy, LDO, Input Comparator and Output Driver
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), (_BIT7 | _BIT5 | _BIT3 | _BIT1));

                    // Discovery Function Power On and Enable System Clk
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT5);

                    // Enable Discovery IRQ
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

                    // MHL Attached
                    ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);

                    // Internal IRQ Enable (Global)
                    ScalerGlobalIRQControl(_ENABLE);

                    EX0 = 1;
                }
#endif
            }
            else
            {
#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

                if(ScalerGetBit(P28_A8_CBUS_CTRL_08, _BIT5) == _BIT5)
                {
                    // Disable CBUS Phy, LDO, Input Comparator
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), 0x00);

                    // Discovery Function Power Down and System Clk Gated
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT6);

                    // Disable Discovery IRQ
                    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), _BIT2);

                    // MHL Unattached
                    ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                }
#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)
                if(ScalerGetBit(P29_A8_CBUS_CTRL_08, _BIT5) == _BIT5)
                {
                    // Disable CBUS Phy, LDO, Input Comparator
                    ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), 0x00);

                    // Discovery Function Power Down and System Clk Gated
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT6);

                    // Disable Discovery IRQ
                    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), _BIT2);

                    // MHL Unattached
                    ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                }
#endif
            }

            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clock Select For MHL for D0 Port
// Input Value  : ucClockSel --> System refernce clock select.
// Output Value : None
//--------------------------------------------------
void ScalerMHLCBUSSwitchClk(EnumClkSel enumClockSel)
{
    enumClockSel = enumClockSel;

#if(_HDCP_2_2_SUPPORT == _ON)
    // Check when MHL3 Hard Marco Isolation OFF (Power Normal)
    if(ScalerGetBit(P40_0A_GDI_2_POWER_CTRL, _BIT1) == 0x00)
    {
        // Set MHL3 w/ HDCP2.2 Frame Number Mode to Frame_Mun - 1
        // (Reg. at Off Region, Re-Set Whenever Power Normal)
        ScalerSetByte(P26_93_REG_MHL3_CP19, 0x80);
    }
#endif
}


//--------------------------------------------------
// Description  : Set Devcap Registor Values
// Input Value  : Non
// Output Value : Non
//--------------------------------------------------
void ScalerMHLSetTimingRelateSetting(void)
{
    // ------------- Re-Set Timing Related Setting After oCBUS -> eCBUS Switch ---------- //

    // Gate CBUS System Clk First (In Case of Digital Clk Glitch)
    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~_BIT5, 0x00);
    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT5, 0x00);

    // MHL System Clk select to IOSC (Bypass GDI Clk)
    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~_BIT4, _BIT4);
    ScalerSetBit(P28_A2_CBUS_CTRL_02, ~_BIT2, 0x00);
    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT4, _BIT4);
    ScalerSetBit(P29_A2_CBUS_CTRL_02, ~_BIT2, 0x00);

    // Clear Wake Up Pulses Flag
    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~_BIT3, _BIT3);
    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT3, _BIT3);

    // Sys Clk Divider
    ScalerSetBit(P28_A1_CBUS_CTRL_01, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    ScalerSetBit(P29_A1_CBUS_CTRL_01, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Disable Debounce For Core Function
    ScalerSetBit(P28_A2_CBUS_CTRL_02, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    ScalerSetBit(P29_A2_CBUS_CTRL_02, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Enable oCBUS Priority Option for MHL2.2 CTS
    ScalerSetBit(P28_AB_CBUS_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6));
    ScalerSetBit(P29_AB_CBUS_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6));

    // Upper Bound of SYNC Pulse Low Time Period
    ScalerSetByte(P28_AF_CBUS_CTRL_0F, 0x35);
    ScalerSetByte(P29_AF_CBUS_CTRL_0F, 0x35);

    // Lower Bound of SYNC Pulse Low Time Period
    ScalerSetByte(P28_B0_CBUS_CTRL_10, 0x20);
    ScalerSetByte(P29_B0_CBUS_CTRL_10, 0x20);

    // Upper Bound of SYNC Pulse High Time Period
    ScalerSetByte(P28_B1_CBUS_CTRL_11, 0x14);
    ScalerSetByte(P29_B1_CBUS_CTRL_11, 0x14);

    // Lower Bound of SYNC Pulse High Time Period
    ScalerSetByte(P28_B2_CBUS_CTRL_12, 0x09);
    ScalerSetByte(P29_B2_CBUS_CTRL_12, 0x09);

    // Absolute Threshold Time
    ScalerSetByte(P28_B4_CBUS_CTRL_14, 0x15);
    ScalerSetByte(P29_B4_CBUS_CTRL_14, 0x15);

    // Parity Bit Time
    ScalerSetByte(P28_B5_CBUS_CTRL_15, 0x1C);
    ScalerSetByte(P29_B5_CBUS_CTRL_15, 0x1C);

    // Parity Error Limit
    ScalerSetBit(P28_B6_CBUS_CTRL_16, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
    ScalerSetBit(P29_B6_CBUS_CTRL_16, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

    // Ack Bit Initial Falling Edge
    ScalerSetBit(P28_B7_CBUS_CTRL_17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);
    ScalerSetBit(P29_B7_CBUS_CTRL_17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

    // Ack Bit Drive Low Time
    ScalerSetBit(P28_B8_CBUS_CTRL_18, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0D);
    ScalerSetBit(P29_B8_CBUS_CTRL_18, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0D);

    // Requester Bit Time
    ScalerSetByte(P28_BA_CBUS_CTRL_1A, 0x1C);
    ScalerSetByte(P29_BA_CBUS_CTRL_1A, 0x1C);

    // Check Received Ack Bit's Falling Edge
    ScalerSetBit(P28_BC_CBUS_CTRL_1C, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x1C);
    ScalerSetBit(P29_BC_CBUS_CTRL_1C, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x1C);

    // Check Received Ack Bit's Driving Low Period Upper Bound
    ScalerSetBit(P28_BD_CBUS_CTRL_1D, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x12);
    ScalerSetBit(P29_BD_CBUS_CTRL_1D, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x12);

    // Check Received Ack Bit's Driving Low Period Lower Bound
    ScalerSetBit(P28_BE_CBUS_CTRL_1E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x05);
    ScalerSetBit(P29_BE_CBUS_CTRL_1E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x05);

    // Actively Driving High Time for CBUS
    ScalerSetBit(P28_C0_CBUS_CTRL_20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P29_C0_CBUS_CTRL_20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // CBUS Requester Transmit Opportunity after Arbitration
    ScalerSetByte(P28_C2_CBUS_CTRL_22, 0x1C);
    ScalerSetByte(P29_C2_CBUS_CTRL_22, 0x1C);

    // CBUS Requester Continue After Ack
    ScalerSetByte(P28_C3_CBUS_CTRL_23, 0x0D);
    ScalerSetByte(P29_C3_CBUS_CTRL_23, 0x0D);

    // Link Layer Timeout
    ScalerSetBit(P28_C5_CBUS_CTRL_25, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));
    ScalerSetBit(P29_C5_CBUS_CTRL_25, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // Set Global MEC Packe TMOUT -> 192ms
    ScalerSetBit(P28_C5_CBUS_CTRL_25, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P29_C5_CBUS_CTRL_25, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Set IIC SCL Clock Frequency
    ScalerSetByte(P28_F9_CBUS_CTRL_59, 0x03);
    ScalerSetByte(P29_F9_CBUS_CTRL_59, 0x03);

    // Enable CBUS System Clk
    ScalerSetBit(P28_A0_CBUS_CTRL_00, ~_BIT5, _BIT5);
    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT5, _BIT5);
}

//--------------------------------------------------
// Description  : MHL Cbus Reset Proc for D0 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLCBUSResetProc(BYTE ucInputPort)
{
    if(ucInputPort == _D0_INPUT_PORT)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        // Port 0 Z0 Disable   /** RL6369 Reg. Mapping **/
        ScalerSetBit(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable Auto K-offset Auto Mode   /** RL6369 Reg. Mapping **/
        ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT6, 0x00);

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit(P28_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Manual Enable CBUS PHY PSM
        ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT0, _BIT0);

        // Force CBUS Floating
        ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT7, _BIT7);

        // Enable Discovery Debounce
        ScalerSetBit(P28_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit(P28_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif

        // Reset CBUS Core Function
        ScalerSetBit(P28_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit(P28_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Manual Enable CBUS PHY PSM
        ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT1, _BIT1);

        // Force CBUS Floating
        ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT7, _BIT7);

        // Enable Discovery Debounce
        ScalerSetBit(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit(P29_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif

        // Reset CBUS Core Function
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

#endif  // End of #if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

        CLR_MHL_RX0_MHL_VERSION();
        SET_MHL_PROCESS_STATE(0, _MHL_STATE_INITIAL);
        CLR_MHL_RX0_ADOPTER_ID_HBYTE();
        CLR_MHL_RX0_ADOPTER_ID_LBYTE();
        CLR_MHL_RX0_ADOPTER_ID_DONE();
        CLR_MHL_RX0_CBUS_RESET_FOR_HTC_DONE();
        CLR_MHL_RX0_SENT_MSC_DCAP_RDY();
        SET_MHL_SWITCH_PORT_DISCOVERY_DONE(0, _FALSE);
        SET_MHL_RX0_WRITE_BURST_PROCESS_DONE();

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        // Port 1 Z0 Disable   /** RL6369 Reg. Mapping **/
        ScalerSetBit(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable Auto K-offset Auto Mode   /** RL6369 Reg. Mapping **/
        ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT6, 0x00);

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit(P28_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Manual Enable CBUS PHY PSM
        ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT0, _BIT0);

        // Force CBUS Floating
        ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT7, _BIT7);

        // Enable Discovery Debounce
        ScalerSetBit(P28_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit(P28_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif

        // Reset CBUS Core Function
        ScalerSetBit(P28_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit(P28_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Manual Enable CBUS PHY PSM
        ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT1, _BIT1);

        // Force CBUS Floating
        ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT7, _BIT7);

        // Enable Discovery Debounce
        ScalerSetBit(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit(P29_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif

        // Reset CBUS Core Function
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

#endif  // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

        CLR_MHL_RX1_MHL_VERSION();
        SET_MHL_PROCESS_STATE(1, _MHL_STATE_INITIAL);
        CLR_MHL_RX1_ADOPTER_ID_HBYTE();
        CLR_MHL_RX1_ADOPTER_ID_LBYTE();
        CLR_MHL_RX1_ADOPTER_ID_DONE();
        CLR_MHL_RX1_CBUS_RESET_FOR_HTC_DONE();
        CLR_MHL_RX1_SENT_MSC_DCAP_RDY();
        SET_MHL_SWITCH_PORT_DISCOVERY_DONE(1, _FALSE);
        SET_MHL_RX1_WRITE_BURST_PROCESS_DONE();

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

    }
    else if(ucInputPort == _D2_INPUT_PORT)
    {
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        // Port 2 Z0 Disable   /** RL6369 Reg. Mapping **/
        ScalerSetBit(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable Auto K-offset Auto Mode   /** RL6369 Reg. Mapping **/
        ScalerSetBit(PB_CA_KOFFSET_04, ~_BIT6, 0x00);

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit(P28_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Manual Enable CBUS PHY PSM
        ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT0, _BIT0);

        // Force CBUS Floating
        ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT7, _BIT7);

        // Enable Discovery Debounce
        ScalerSetBit(P28_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit(P28_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif

        // Reset CBUS Core Function
        ScalerSetBit(P28_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit(P28_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Manual Enable CBUS PHY PSM
        ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT1, _BIT1);

        // Force CBUS Floating
        ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT7, _BIT7);

        // Enable Discovery Debounce
        ScalerSetBit(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit(P29_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif

        // Reset CBUS Core Function
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

#endif  // End of #if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

        CLR_MHL_RX2_MHL_VERSION();
        SET_MHL_PROCESS_STATE(2, _MHL_STATE_INITIAL);
        CLR_MHL_RX2_ADOPTER_ID_HBYTE();
        CLR_MHL_RX2_ADOPTER_ID_LBYTE();
        CLR_MHL_RX2_ADOPTER_ID_DONE();
        CLR_MHL_RX2_CBUS_RESET_FOR_HTC_DONE();
        CLR_MHL_RX2_SENT_MSC_DCAP_RDY();
        SET_MHL_SWITCH_PORT_DISCOVERY_DONE(2, _FALSE);
        SET_MHL_RX2_WRITE_BURST_PROCESS_DONE();

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

    }

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
    // Reset Hdcp2 Proc
    ScalerHdcp2ResetTMDSProc(_D0_INPUT_PORT);
#endif
}


//--------------------------------------------------
// Description  : MHL Power Off Process for D0 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLPowerOffProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX0_READY_TO_TRANSMIT);
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX0_RECONNECT_1K);
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX0_SWITCH_PORT_DISCOVERY_DONE);

            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT);
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX1_RECONNECT_1K);
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE);

            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX2_READY_TO_TRANSMIT);
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX2_RECONNECT_1K);
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX2_SWITCH_PORT_DISCOVERY_DONE);

            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : MHL Detect Clk Mode if 24Bit or PP Mode
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLDetectClkMode(void)
{
    WORD usTemp = 250;

    // Clear Error Flag and Start Detection
    ScalerSetBit(P26_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P26_A7_MHL_CTRL_07, ~_BIT0, _BIT0);

    // Wait until detection is done(1ms) or timeout(1.5ms)
    while((ScalerGetBit(P26_A7_MHL_CTRL_07, _BIT0) == _BIT0) && (--usTemp != 0))
    {
        DELAY_5US();
    }

    if(((bit)ScalerGetBit(P26_B3_MHL_CTRL_13, _BIT0) == _TRUE) ||
       ((bit)ScalerGetBit(P26_A7_MHL_CTRL_07, _BIT7) != (GET_TMDS_RX0_CLK_MODE() & _BIT0)))
    {
        ScalerSetBit(P26_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);

        if(GET_TMDS_RX0_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
        {
            usTemp = 500;

            // Wait until RGB detection is done or timeout(3ms)
            while((ScalerGetBit(P2_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) != (_BIT7 | _BIT6 | _BIT5)) &&
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
BYTE ScalerMHLDetectClkMode_EXINT0(void) using 1
{
    WORD usTemp = 250;

    // Clear Error Flag and Start Detection
    ScalerSetBit_EXINT(P26_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P26_A7_MHL_CTRL_07, ~_BIT0, _BIT0);

    // Wait until detection is done(1ms) or timeout(1.5ms)
    while((ScalerGetBit_EXINT(P26_A7_MHL_CTRL_07, _BIT0) == _BIT0) && (--usTemp != 0))
    {
        DELAY_5US_EXINT();
    }

    if(((bit)ScalerGetBit_EXINT(P26_B3_MHL_CTRL_13, _BIT0) == _TRUE) ||
       ((bit)ScalerGetBit_EXINT(P26_A7_MHL_CTRL_07, _BIT7) != (GET_TMDS_RX0_CLK_MODE() & _BIT0)))
    {
        ScalerSetBit_EXINT(P26_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);

        if(GET_TMDS_RX0_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
        {
            usTemp = 500;

            // Wait until RGB detection is done or timeout(3ms)
            while((ScalerGetBit_EXINT(P2_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) != (_BIT7 | _BIT6 | _BIT5)) &&
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
// Description  : Int Process for MHL for D0 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLIntHandler_EXINT0(void) using 1
{
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

    // Check Discovery Pulse
    if(ScalerGetBit_EXINT(P28_A0_CBUS_CTRL_00, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0))
    {
        // Disable Discovery Done IRQ and Clear Discovery Flags
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2));

        // Disable Discovery Debounce
        ScalerSetBit_EXINT(P28_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Stuck Low IRQ and Clear Flag
        ScalerSetBit_EXINT(P28_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(ScalerGetBit_EXINT(PB_B7_IMPEDANCE_00, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)    /** RL6369 Reg. Mapping **/
        {
            // Suspend Key Calculation before load key
            ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, 0x00);
        }

        // Enable GDI BandGap
        ScalerSetBit_EXINT(PB_B4_BANDGAP_00, ~_BIT7, _BIT7);

        // Manual Disable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT0, 0x00);

        // Enable RX_EN    /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT7, _BIT7);

        // Port 0 Z0 Enable   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Clear HDCP Flags
        ScalerSetBit_EXINT(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

        SET_MHL_PROCESS_STATE(0, _MHL_STATE_DISCOVERY_DONE);
        SET_MHL_READY_TO_TRANSMIT(0, _TRUE);
    }

    // Check Stuck Low Flag
    if(ScalerGetBit_EXINT(P28_A4_CBUS_CTRL_04, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit_EXINT(P28_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        CLR_DIGITAL_PORT_SWITCH_TO_D0();

        // Port 0 Z0 Disable    /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable Auto K-offset Auto Mode   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT6, 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Reset Authenticated FSM
        ScalerSetByte_EXINT(P63_A2_HDCP_I2C_CTRL_A2, 0x01);
        ScalerSetBit_EXINT(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT6, _BIT6);

        // Cancel HDCP 2.2 Re-Auth Timer Event
        if(CHECK_TMDS_DPHY_SWITCH(_D0_INPUT_PORT) == _TRUE)
        {
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX0_HDCP2_REAUTH);
        }
#endif

        // Manual Enable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT0, _BIT0);

        // Enable Discovery Debounce
        ScalerSetBit_EXINT(P28_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit_EXINT(P28_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif
        // Reset CBUS Core Function
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        CLR_MHL_RX0_MHL_VERSION();
        SET_MHL_PROCESS_STATE(0, _MHL_STATE_INITIAL);
        CLR_MHL_RX0_ADOPTER_ID_HBYTE();
        CLR_MHL_RX0_ADOPTER_ID_LBYTE();
        CLR_MHL_RX0_ADOPTER_ID_DONE();
        CLR_MHL_RX0_CBUS_RESET_FOR_HTC_DONE();
        CLR_MHL_RX0_SENT_MSC_DCAP_RDY();
        SET_MHL_SWITCH_PORT_DISCOVERY_DONE(0, _FALSE);
        SET_MHL_RX0_WRITE_BURST_PROCESS_DONE();
    }

#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

    // Check Discovery Pulse
    if(ScalerGetBit_EXINT(P29_A0_CBUS_CTRL_00, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0))
    {
        // Disable Discovery Done IRQ and Clear Discovery Flags
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), _BIT2);

        // Disable Discovery Debounce
        ScalerSetBit_EXINT(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Stuck Low IRQ and Clear Flag
        ScalerSetBit_EXINT(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(ScalerGetBit_EXINT(PB_B7_IMPEDANCE_00, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)    /** RL6369 Reg. Mapping **/
        {
            // Suspend Key Calculation before load key
            ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, 0x00);
        }

        // Enable GDI BandGap
        ScalerSetBit_EXINT(PB_B4_BANDGAP_00, ~_BIT7, _BIT7);

        // Manual Disable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT1, 0x00);

        // Enable RX_EN    /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT7, _BIT7);

        // Port 0 Z0 Enable   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Clear HDCP Flags
        ScalerSetBit_EXINT(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

        SET_MHL_PROCESS_STATE(0, _MHL_STATE_DISCOVERY_DONE);
        SET_MHL_READY_TO_TRANSMIT(0, _TRUE);
    }

    // Check Stuck Low Flag
    if(ScalerGetBit_EXINT(P29_A4_CBUS_CTRL_04, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit_EXINT(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        CLR_DIGITAL_PORT_SWITCH_TO_D0();

        // Port 0 Z0 Disable    /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_B7_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable Auto K-offset Auto Mode   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT6, 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Reset Authenticated FSM
        ScalerSetByte_EXINT(P63_A2_HDCP_I2C_CTRL_A2, 0x01);
        ScalerSetBit_EXINT(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT6, _BIT6);

        // Cancel HDCP 2.2 Re-Auth Timer Event
        if(CHECK_TMDS_DPHY_SWITCH(_D0_INPUT_PORT) == _TRUE)
        {
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX0_HDCP2_REAUTH);
        }
#endif

        // Manual Enable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT1, _BIT1);

        // Enable Discovery Debounce
        ScalerSetBit_EXINT(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit_EXINT(P29_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif
        // Reset CBUS Core Function
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        CLR_MHL_RX0_MHL_VERSION();
        SET_MHL_PROCESS_STATE(0, _MHL_STATE_INITIAL);
        CLR_MHL_RX0_ADOPTER_ID_HBYTE();
        CLR_MHL_RX0_ADOPTER_ID_LBYTE();
        CLR_MHL_RX0_ADOPTER_ID_DONE();
        CLR_MHL_RX0_CBUS_RESET_FOR_HTC_DONE();
        CLR_MHL_RX0_SENT_MSC_DCAP_RDY();
        SET_MHL_SWITCH_PORT_DISCOVERY_DONE(0, _FALSE);
        SET_MHL_RX0_WRITE_BURST_PROCESS_DONE();
    }

#endif // End of #if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

    // Check Discovery Pulse
    if(ScalerGetBit_EXINT(P28_A0_CBUS_CTRL_00, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0))
    {
        // Disable Discovery Done IRQ and Clear Discovery Flags
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2));

        // Disable Discovery Debounce
        ScalerSetBit_EXINT(P28_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Stuck Low IRQ and Clear Flag
        ScalerSetBit_EXINT(P28_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(ScalerGetBit_EXINT(PB_B9_IMPEDANCE_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)    /** RL6369 Reg. Mapping **/
        {
            // Suspend Key Calculation before load key
            ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, 0x00);
        }

        // Enable GDI BandGap
        ScalerSetBit_EXINT(PB_B4_BANDGAP_00, ~_BIT7, _BIT7);

        // Manual Disable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT0, 0x00);

        // Enable RX_EN    /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT7, _BIT7);

        // Port 1 Z0 Enable   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Clear HDCP Flags
        ScalerSetBit_EXINT(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

        SET_MHL_PROCESS_STATE(1, _MHL_STATE_DISCOVERY_DONE);
        SET_MHL_READY_TO_TRANSMIT(1, _TRUE);
    }

    // Check Stuck Low Flag
    if(ScalerGetBit_EXINT(P28_A4_CBUS_CTRL_04, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit_EXINT(P28_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        CLR_DIGITAL_PORT_SWITCH_TO_D1();

        // Port 1 Z0 Disable   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable Auto K-offset Auto Mode   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT6, 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Reset Authenticated FSM
        ScalerSetByte_EXINT(P63_A2_HDCP_I2C_CTRL_A2, 0x01);
        ScalerSetBit_EXINT(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT6, _BIT6);

        // Cancel HDCP 2.2 Re-Auth Timer Event
        if(CHECK_TMDS_DPHY_SWITCH(_D1_INPUT_PORT) == _TRUE)
        {
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX1_HDCP2_REAUTH);
        }
#endif

        // Manual Enable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT0, _BIT0);

        // Enable Discovery Debounce
        ScalerSetBit_EXINT(P28_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit_EXINT(P28_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif
        // Reset CBUS Core Function
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        CLR_MHL_RX1_MHL_VERSION();
        SET_MHL_PROCESS_STATE(1, _MHL_STATE_INITIAL);
        CLR_MHL_RX1_ADOPTER_ID_HBYTE();
        CLR_MHL_RX1_ADOPTER_ID_LBYTE();
        CLR_MHL_RX1_ADOPTER_ID_DONE();
        CLR_MHL_RX1_CBUS_RESET_FOR_HTC_DONE();
        CLR_MHL_RX1_SENT_MSC_DCAP_RDY();
        SET_MHL_SWITCH_PORT_DISCOVERY_DONE(1, _FALSE);
        SET_MHL_RX1_WRITE_BURST_PROCESS_DONE();
    }

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

    // Check Discovery Pulse
    if(ScalerGetBit_EXINT(P29_A0_CBUS_CTRL_00, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0))
    {
        // Disable Discovery Done IRQ and Clear Discovery Flags
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), _BIT2);

        // Disable Discovery Debounce
        ScalerSetBit_EXINT(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Stuck Low IRQ and Clear Flag
        ScalerSetBit_EXINT(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(ScalerGetBit_EXINT(PB_B9_IMPEDANCE_02, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)    /** RL6369 Reg. Mapping **/
        {
            // Suspend Key Calculation before load key
            ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, 0x00);
        }

        // Enable GDI BandGap
        ScalerSetBit_EXINT(PB_B4_BANDGAP_00, ~_BIT7, _BIT7);

        // Manual Disable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT1, 0x00);

        // Enable RX_EN    /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT7, _BIT7);

        // Port 1 Z0 Enable   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Clear HDCP Flags
        ScalerSetBit_EXINT(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

        SET_MHL_PROCESS_STATE(1, _MHL_STATE_DISCOVERY_DONE);
        SET_MHL_READY_TO_TRANSMIT(1, _TRUE);
    }

    // Check Stuck Low Flag
    if(ScalerGetBit_EXINT(P29_A4_CBUS_CTRL_04, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit_EXINT(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        CLR_DIGITAL_PORT_SWITCH_TO_D1();

        // Port 1 Z0 Disable   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_B9_IMPEDANCE_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable Auto K-offset Auto Mode   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT6, 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Reset Authenticated FSM
        ScalerSetByte_EXINT(P63_A2_HDCP_I2C_CTRL_A2, 0x01);
        ScalerSetBit_EXINT(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT6, _BIT6);

        // Cancel HDCP 2.2 Re-Auth Timer Event
        if(CHECK_TMDS_DPHY_SWITCH(_D1_INPUT_PORT) == _TRUE)
        {
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX1_HDCP2_REAUTH);
        }
#endif

        // Manual Enable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT1, _BIT1);

        // Enable Discovery Debounce
        ScalerSetBit_EXINT(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit_EXINT(P29_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif
        // Reset CBUS Core Function
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        CLR_MHL_RX1_MHL_VERSION();
        SET_MHL_PROCESS_STATE(1, _MHL_STATE_INITIAL);
        CLR_MHL_RX1_ADOPTER_ID_HBYTE();
        CLR_MHL_RX1_ADOPTER_ID_LBYTE();
        CLR_MHL_RX1_ADOPTER_ID_DONE();
        CLR_MHL_RX1_CBUS_RESET_FOR_HTC_DONE();
        CLR_MHL_RX1_SENT_MSC_DCAP_RDY();
        SET_MHL_SWITCH_PORT_DISCOVERY_DONE(1, _FALSE);
        SET_MHL_RX1_WRITE_BURST_PROCESS_DONE();
    }

#endif // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

    // Check Discovery Pulse
    if(ScalerGetBit_EXINT(P28_A0_CBUS_CTRL_00, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0))
    {
        // Disable Discovery Done IRQ and Clear Discovery Flags
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2));

        // Disable Discovery Debounce
        ScalerSetBit_EXINT(P28_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Stuck Low IRQ and Clear Flag
        ScalerSetBit_EXINT(P28_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(ScalerGetBit_EXINT(PB_BB_IMPEDANCE_04, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)    /** RL6369 Reg. Mapping **/
        {
            // Suspend Key Calculation before load key
            ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, 0x00);
        }

        // Enable GDI BandGap
        ScalerSetBit_EXINT(PB_B4_BANDGAP_00, ~_BIT7, _BIT7);

        // Manual Disable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT0, 0x00);

        // Enable RX_EN    /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT7, _BIT7);

        // Port 0 Z0 Enable   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Clear HDCP Flags
        ScalerSetBit_EXINT(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

        SET_MHL_PROCESS_STATE(2, _MHL_STATE_DISCOVERY_DONE);
        SET_MHL_READY_TO_TRANSMIT(2, _TRUE);
    }

    // Check Stuck Low Flag
    if(ScalerGetBit_EXINT(P28_A4_CBUS_CTRL_04, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit_EXINT(P28_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        CLR_DIGITAL_PORT_SWITCH_TO_D2();

        // Port 2 Z0 Disable   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable Auto K-offset Auto Mode   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT6, 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Reset Authenticated FSM
        ScalerSetByte_EXINT(P63_A2_HDCP_I2C_CTRL_A2, 0x01);
        ScalerSetBit_EXINT(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT6, _BIT6);

        // Cancel HDCP 2.2 Re-Auth Timer Event
        if(CHECK_TMDS_DPHY_SWITCH(_D2_INPUT_PORT) == _TRUE)
        {
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH);
        }
#endif

        // Manual Enable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT0, _BIT0);

        // Enable Discovery Debounce
        ScalerSetBit_EXINT(P28_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit_EXINT(P28_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif
        // Reset CBUS Core Function
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P28_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        CLR_MHL_RX2_MHL_VERSION();
        SET_MHL_PROCESS_STATE(2, _MHL_STATE_INITIAL);
        CLR_MHL_RX2_ADOPTER_ID_HBYTE();
        CLR_MHL_RX2_ADOPTER_ID_LBYTE();
        CLR_MHL_RX2_ADOPTER_ID_DONE();
        CLR_MHL_RX2_CBUS_RESET_FOR_HTC_DONE();
        CLR_MHL_RX2_SENT_MSC_DCAP_RDY();
        SET_MHL_SWITCH_PORT_DISCOVERY_DONE(2, _FALSE);
        SET_MHL_RX2_WRITE_BURST_PROCESS_DONE();
    }

#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

    // Check Discovery Pulse
    if(ScalerGetBit_EXINT(P29_A0_CBUS_CTRL_00, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0))
    {
        // Disable Discovery Done IRQ and Clear Discovery Flags
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), _BIT2);

        // Disable Discovery Debounce
        ScalerSetBit_EXINT(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Stuck Low IRQ and Clear Flag
        ScalerSetBit_EXINT(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(ScalerGetBit_EXINT(PB_BB_IMPEDANCE_04, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)    /** RL6369 Reg. Mapping **/
        {
            // Suspend Key Calculation before load key
            ScalerSetBit_EXINT(P2_AE_TMDS_RPS, ~_BIT1, 0x00);
        }

        // Enable GDI BandGap
        ScalerSetBit_EXINT(PB_B4_BANDGAP_00, ~_BIT7, _BIT7);

        // Manual Disable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT1, 0x00);

        // Enable RX_EN    /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_C0_CMU_03, ~_BIT7, _BIT7);

        // Port 0 Z0 Enable   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Clear HDCP Flags
        ScalerSetBit_EXINT(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5));

        SET_MHL_PROCESS_STATE(2, _MHL_STATE_DISCOVERY_DONE);
        SET_MHL_READY_TO_TRANSMIT(2, _TRUE);
    }

    // Check Stuck Low Flag
    if(ScalerGetBit_EXINT(P29_A4_CBUS_CTRL_04, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit_EXINT(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        CLR_DIGITAL_PORT_SWITCH_TO_D2();

        // Port 2 Z0 Disable   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_BB_IMPEDANCE_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Disable Auto K-offset Auto Mode   /** RL6369 Reg. Mapping **/
        ScalerSetBit_EXINT(PB_CA_KOFFSET_04, ~_BIT6, 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Reset Authenticated FSM
        ScalerSetByte_EXINT(P63_A2_HDCP_I2C_CTRL_A2, 0x01);
        ScalerSetBit_EXINT(P63_A3_HDCP_I2C_CTRL_A3, ~_BIT6, _BIT6);

        // Cancel HDCP 2.2 Re-Auth Timer Event
        if(CHECK_TMDS_DPHY_SWITCH(_D2_INPUT_PORT) == _TRUE)
        {
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH);
        }
#endif

        // Manual Enable CBUS PHY PSM
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT1, _BIT1);

        // Enable Discovery Debounce
        ScalerSetBit_EXINT(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit_EXINT(P29_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif
        // Reset CBUS Core Function
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        CLR_MHL_RX2_MHL_VERSION();
        SET_MHL_PROCESS_STATE(2, _MHL_STATE_INITIAL);
        CLR_MHL_RX2_ADOPTER_ID_HBYTE();
        CLR_MHL_RX2_ADOPTER_ID_LBYTE();
        CLR_MHL_RX2_ADOPTER_ID_DONE();
        CLR_MHL_RX2_CBUS_RESET_FOR_HTC_DONE();
        CLR_MHL_RX2_SENT_MSC_DCAP_RDY();
        SET_MHL_SWITCH_PORT_DISCOVERY_DONE(2, _FALSE);
        SET_MHL_RX2_WRITE_BURST_PROCESS_DONE();
    }

#endif // End of #if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
}

//--------------------------------------------------
// Description  : Send MSC HPD Operation for D0 Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Fail
//--------------------------------------------------
bit ScalerMHLMscSendCommand(BYTE ucInputPort, EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue)
{
    BYTE ucResultPacket = 0;

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
    DebugMessageMHL("MSC Send Command", enumMSCCommand);
    DebugMessageMHL("Offset", enumMSCOffset);
    DebugMessageMHL("Data", enumMSCValue);
#endif

    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
        case _D0_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(0);
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        case _D1_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(1);
            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
        case _D2_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(2);
            break;
#endif

        default:
            break;
    }

    if(GET_MHL_READY_TO_TRANSMIT(GET_MHL_PORT_ACTIVE()) == _TRUE)
    {
        ucResultPacket = ScalerMHLMscFIFOSendCommand(ucInputPort, enumMSCCommand, enumMSCOffset, enumMSCValue, 0, _NULL_POINTER);

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                SET_MHL_READY_TO_TRANSMIT(GET_MHL_PORT_ACTIVE(), _TRUE);

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("MSC MHL_SUCCESS", ScalerGetByte(P28_D2_CBUS_CTRL_32));
#endif
                return _SUCCESS;
                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

                SET_MHL_READY_TO_TRANSMIT(GET_MHL_PORT_ACTIVE(), _FALSE);

                switch(ucInputPort)
                {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    case _D0_INPUT_PORT:
                        ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX0_READY_TO_TRANSMIT);
                        break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    case _D1_INPUT_PORT:
                        ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT);
                        break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    case _D2_INPUT_PORT:
                        ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX2_READY_TO_TRANSMIT);
                        break;
#endif
                    default:
                        break;
                }

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("MSC MHL_ABORT_FAIL", ScalerGetByte(P28_D2_CBUS_CTRL_32));
#endif
                return _FAIL;
                break;

            case _MHL_PROTOCOL_ERROR: // Source Reply Data Packet Instead of Control Packet

                ScalerMHLMscFIFOSendCommand(ucInputPort, _MSC_ABORT, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE, 0, _NULL_POINTER);

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("MSC MHL_PROTOCOL_ERROR", ScalerGetByte(P28_D2_CBUS_CTRL_32));
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
// Description  : Send Write Burst Operation for D0 Port
// Input Value  : ucDataLength --> Data Length
//                pucData --> Data
//                ucMode --> Write Burst Mode
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
bit ScalerMHLMscSendWriteBurst(BYTE ucInputPort, BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode)
{
    BYTE ucResultPacket = 0;

    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
        case _D0_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(0);
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        case _D1_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(1);
            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
        case _D2_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(2);
            break;
#endif

        default:
            break;
    }

    if(enumMode == _MHL_WRITE_BURST_WITH_REQ)
    {
        switch(ucInputPort)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

            case _D0_INPUT_PORT:

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

                // Clear Grant To Write Flag
                ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT);

                // Send Request to Write
                ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT);

                // Disable Access Port Auto Increase
                ScalerSetBit(P28_AB_CBUS_CTRL_0B, ~_BIT0, 0x00);

                // Polling Grant to Write
                ScalerSetByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT);
                ScalerTimerPollingFlagProc(100, P28_AD_CBUS_CTRL_0D, _MSC_GRT_WRT, _TRUE);

                // Enable Access Port Auto Increase
                ScalerSetBit(P28_AB_CBUS_CTRL_0B, ~_BIT0, _BIT0);

#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

                // Clear Grant To Write Flag
                ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT);

                // Send Request to Write
                ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT);

                // Disable Access Port Auto Increase
                ScalerSetBit(P29_AB_CBUS_CTRL_0B, ~_BIT0, 0x00);

                // Polling Grant to Write
                ScalerSetByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT);
                ScalerTimerPollingFlagProc(100, P28_AD_CBUS_CTRL_0D, _MSC_GRT_WRT, _TRUE);

                // Enable Access Port Auto Increase
                ScalerSetBit(P29_AB_CBUS_CTRL_0B, ~_BIT0, _BIT0);

#endif // End of #if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

                break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

            case _D1_INPUT_PORT:

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

                // Clear Grant To Write Flag
                ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT);

                // Send Request to Write
                ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT);

                // Disable Access Port Auto Increase
                ScalerSetBit(P28_AB_CBUS_CTRL_0B, ~_BIT0, 0x00);

                // Polling Grant to Write
                ScalerSetByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT);
                ScalerTimerPollingFlagProc(100, P28_AD_CBUS_CTRL_0D, _MSC_GRT_WRT, _TRUE);

                // Enable Access Port Auto Increase
                ScalerSetBit(P28_AB_CBUS_CTRL_0B, ~_BIT0, _BIT0);

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

                // Clear Grant To Write Flag
                ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT);

                // Send Request to Write
                ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT);

                // Disable Access Port Auto Increase
                ScalerSetBit(P29_AB_CBUS_CTRL_0B, ~_BIT0, 0x00);

                // Polling Grant to Write
                ScalerSetByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT);
                ScalerTimerPollingFlagProc(100, P28_AD_CBUS_CTRL_0D, _MSC_GRT_WRT, _TRUE);

                // Enable Access Port Auto Increase
                ScalerSetBit(P29_AB_CBUS_CTRL_0B, ~_BIT0, _BIT0);

#endif // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

                break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

            case _D2_INPUT_PORT:

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

                // Clear Grant To Write Flag
                ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT);

                // Send Request to Write
                ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT);

                // Disable Access Port Auto Increase
                ScalerSetBit(P28_AB_CBUS_CTRL_0B, ~_BIT0, 0x00);

                // Polling Grant to Write
                ScalerSetByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT);
                ScalerTimerPollingFlagProc(100, P28_AD_CBUS_CTRL_0D, _MSC_GRT_WRT, _TRUE);

                // Enable Access Port Auto Increase
                ScalerSetBit(P28_AB_CBUS_CTRL_0B, ~_BIT0, _BIT0);

#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

                // Clear Grant To Write Flag
                ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT);

                // Send Request to Write
                ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT);

                // Disable Access Port Auto Increase
                ScalerSetBit(P29_AB_CBUS_CTRL_0B, ~_BIT0, 0x00);

                // Polling Grant to Write
                ScalerSetByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT);
                ScalerTimerPollingFlagProc(100, P28_AD_CBUS_CTRL_0D, _MSC_GRT_WRT, _TRUE);

                // Enable Access Port Auto Increase
                ScalerSetBit(P29_AB_CBUS_CTRL_0B, ~_BIT0, _BIT0);

#endif // End of #if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

                break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

            default:
                break;
        }
    }

    if(GET_MHL_READY_TO_TRANSMIT(GET_MHL_PORT_ACTIVE()) == _TRUE)
    {
        ucResultPacket = ScalerMHLMscFIFOSendCommand(ucInputPort, _MSC_WRITE_BURST, ucOffset, 0x00, ucDataLength, pucData);

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                // Send Device Scratchpad Change
                ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_DSCR_CHG);

                return _SUCCESS;

                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

                SET_MHL_READY_TO_TRANSMIT(GET_MHL_PORT_ACTIVE(), _FALSE);

                switch(ucInputPort)
                {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    case _D0_INPUT_PORT:
                        ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX0_READY_TO_TRANSMIT);
                        break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    case _D1_INPUT_PORT:
                        ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT);
                        break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    case _D2_INPUT_PORT:
                        ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX2_READY_TO_TRANSMIT);
                        break;
#endif
                    default:
                        break;
                }

                return _FAIL;
                break;

            case _MHL_PROTOCOL_ERROR: // Source Reply Data Packet Instead of Control Packet

                ScalerMHLMscFIFOSendCommand(ucInputPort, _MSC_ABORT, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE, 0, _NULL_POINTER);

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
// Description  : Read Device Capabilities for D0 Port
// Input Value  : enumMSCOffset --> Device Capability Offset
//                pucData --> Data to be Read
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
bit ScalerMHLMscReadDevCapabilities(BYTE ucInputPort, EnumMHLMscOffset enumMSCOffset, BYTE *pucData, BYTE ucExtended)
{
    BYTE ucResultPacket = 0;

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
    DebugMessageMHL("ReadDev at Offset", enumMSCOffset);
#endif

    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
        case _D0_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(0);
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        case _D1_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(1);
            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
        case _D2_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(2);
            break;
#endif

        default:
            break;
    }

    if(GET_MHL_READY_TO_TRANSMIT(GET_MHL_PORT_ACTIVE()) == _TRUE)
    {
        if(ucExtended == _MSC_READ_XDEVCAP)
        {
            ucResultPacket = ScalerMHLMscFIFOSendCommand(ucInputPort, _MSC_READ_XDEVCAP, enumMSCOffset, _MSC_NULL_VALUE, 0, pucData);
        }
        else
        {
            ucResultPacket = ScalerMHLMscFIFOSendCommand(ucInputPort, _MSC_READ_DEVCAP, enumMSCOffset, _MSC_NULL_VALUE, 0, pucData);
        }

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                SET_MHL_READY_TO_TRANSMIT(GET_MHL_PORT_ACTIVE(), _TRUE);

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("ReadDev MHL_SUCCESS", ScalerGetByte(P28_D2_CBUS_CTRL_32));
#endif
                return _SUCCESS;

                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

                SET_MHL_READY_TO_TRANSMIT(GET_MHL_PORT_ACTIVE(), _FALSE);

                switch(ucInputPort)
                {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    case _D0_INPUT_PORT:
                        ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX0_READY_TO_TRANSMIT);
                        break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    case _D1_INPUT_PORT:
                        ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT);
                        break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    case _D2_INPUT_PORT:
                        ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX2_READY_TO_TRANSMIT);
                        break;
#endif
                    default:
                        break;
                }

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("ReadDev MHL_ABORT_FAIL", ScalerGetByte(P28_D2_CBUS_CTRL_32));
#endif
                return _FAIL;
                break;

            case _MHL_PROTOCOL_ERROR: // Source Reply Data Packet Instead of Control Packet

                ScalerMHLMscFIFOSendCommand(ucInputPort, _MSC_ABORT, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE, 0, _NULL_POINTER);

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
                DebugMessageMHL("ReadDev MHL_PROTOCOL_ERROR", ScalerGetByte(P28_D2_CBUS_CTRL_32));
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
// Description  : Send MSC HPD Operation for D0 Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
BYTE ScalerMHLMscFIFOSendCommand(BYTE ucInputPort, EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData)
{
    BYTE ucTimeOut = 100;
    BYTE ucSendType = 0;
    BYTE ucWaitType = 0;
    BYTE ucI = 0;

    ucInputPort = ucInputPort;

#if(_MHL_MSC_COMMAND_POLLING_MESSAGE == _ON)
    DebugMessageMHL("GET_MHL_READY_TO_TRANSMIT", GET_MHL_PORT_ACTIVE());
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

    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

            // Check If Source Has Sent An ABORT Packet
            if(ScalerGetBit(P28_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
            {
                ScalerSetByte(P28_CF_CBUS_CTRL_2F, _BIT2);

                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX0_READY_TO_TRANSMIT);

                SET_MHL_READY_TO_TRANSMIT(0, _FALSE);

                return _MHL_FAIL;
            }

            // Clear FIFO and Send Command Only
            ScalerSetByte(P28_DE_CBUS_CTRL_3E, (_BIT6 | ucSendType));

            // Set MSC Command
            ScalerSetByte(P28_DF_CBUS_CTRL_3F, enumMSCCommand);

            // Set MSC Offset
            ScalerSetByte(P28_E1_CBUS_CTRL_41, enumMSCOffset);

            if(enumMSCCommand == _MSC_WRITE_BURST)
            {
                // Set MSC Last Command
                ScalerSetByte(P28_E0_CBUS_CTRL_40, _MSC_EOF_PACKET);

                // Set MSC Data
                for(ucI = 0; ucI < ucDataLength; ucI++)
                {
                    ScalerSetByte(P28_E2_CBUS_CTRL_42, pucData[ucI]);
                }
            }
            else if((enumMSCCommand != _MSC_READ_DEVCAP) && (enumMSCCommand != _MSC_READ_XDEVCAP))
            {
                // Set MSC Value
                ScalerSetByte(P28_E2_CBUS_CTRL_42, enumMSCValue);
            }

            // MSC Packet and Wait Type
            ScalerSetBit(P28_E3_CBUS_CTRL_43, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), ((_MSC_PACKET << 6) | ucWaitType));

            // Send Request
            ScalerSetBit(P28_DE_CBUS_CTRL_3E, ~(_BIT7), _BIT7);

            // Check if Process is finished
            while(--ucTimeOut != 0)
            {
                if(ScalerGetBit(P28_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
                {
                    // Clear Flag
                    ScalerSetBit(P28_CF_CBUS_CTRL_2F, ~_BIT2, _BIT2);

                    return _MHL_ABORT_FAIL;
                }
                else if((ScalerGetBit(P28_F6_CBUS_CTRL_56, _BIT7) == _BIT7) && (ScalerGetBit(P28_F7_CBUS_CTRL_57, _BIT7) == 0x00))
                {
                    // Clear Flag
                    ScalerSetBit(P28_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);

                    if(ucWaitType == _MSC_WAIT_NULL)
                    {
                        return _MHL_SUCCESS;
                    }
                    else
                    {
                        // Check ACK Packet
                        if(ScalerGetByte(P28_E4_CBUS_CTRL_44) == _MSC_ACK_PACKET)
                        {
                            if((enumMSCCommand == _MSC_READ_DEVCAP) || (enumMSCCommand == _MSC_READ_XDEVCAP))
                            {
                                *pucData = ScalerGetByte(P28_E5_CBUS_CTRL_45);
                            }

                            return _MHL_SUCCESS;
                        }
                        else
                        {
                            return _MHL_FAIL;
                        }
                    }
                }
                else if((ScalerGetBit(P28_F7_CBUS_CTRL_57, _BIT7) == _BIT7) && (ScalerGetByte(P28_D2_CBUS_CTRL_32) == _MSC_PROTOCOL_ERROR))
                {
                    // Clear Flags
                    ScalerSetBit(P28_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
                    ScalerSetBit(P28_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);

                    return _MHL_PROTOCOL_ERROR;
                }

                ScalerTimerDelayXms(1);
            }

            // Clear Flag
            ScalerSetBit(P28_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
            ScalerSetBit(P28_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);

#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

            // Check If Source Has Sent An ABORT Packet
            if(ScalerGetBit(P29_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
            {
                ScalerSetByte(P29_CF_CBUS_CTRL_2F, _BIT2);

                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX0_READY_TO_TRANSMIT);

                SET_MHL_READY_TO_TRANSMIT(0, _FALSE);

                return _MHL_FAIL;
            }

            // Clear FIFO and Send Command Only
            ScalerSetByte(P29_DE_CBUS_CTRL_3E, (_BIT6 | ucSendType));

            // Set MSC Command
            ScalerSetByte(P29_DF_CBUS_CTRL_3F, enumMSCCommand);

            // Set MSC Offset
            ScalerSetByte(P29_E1_CBUS_CTRL_41, enumMSCOffset);

            if(enumMSCCommand == _MSC_WRITE_BURST)
            {
                // Set MSC Last Command
                ScalerSetByte(P29_E0_CBUS_CTRL_40, _MSC_EOF_PACKET);

                // Set MSC Data
                for(ucI = 0; ucI < ucDataLength; ucI++)
                {
                    ScalerSetByte(P29_E2_CBUS_CTRL_42, pucData[ucI]);
                }
            }
            else if((enumMSCCommand != _MSC_READ_DEVCAP) && (enumMSCCommand != _MSC_READ_XDEVCAP))
            {
                // Set MSC Value
                ScalerSetByte(P29_E2_CBUS_CTRL_42, enumMSCValue);
            }

            // MSC Packet and Wait Type
            ScalerSetBit(P29_E3_CBUS_CTRL_43, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), ((_MSC_PACKET << 6) | ucWaitType));

            // Send Request
            ScalerSetBit(P29_DE_CBUS_CTRL_3E, ~(_BIT7), _BIT7);

            // Check if Process is finished
            while(--ucTimeOut != 0)
            {
                if(ScalerGetBit(P29_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
                {
                    // Clear Flag
                    ScalerSetBit(P29_CF_CBUS_CTRL_2F, ~_BIT2, _BIT2);

                    return _MHL_ABORT_FAIL;
                }
                else if((ScalerGetBit(P29_F6_CBUS_CTRL_56, _BIT7) == _BIT7) && (ScalerGetBit(P29_F7_CBUS_CTRL_57, _BIT7) == 0x00))
                {
                    // Clear Flag
                    ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);

                    if(ucWaitType == _MSC_WAIT_NULL)
                    {
                        return _MHL_SUCCESS;
                    }
                    else
                    {
                        // Check ACK Packet
                        if(ScalerGetByte(P29_E4_CBUS_CTRL_44) == _MSC_ACK_PACKET)
                        {
                            if((enumMSCCommand == _MSC_READ_DEVCAP) || (enumMSCCommand == _MSC_READ_XDEVCAP))
                            {
                                *pucData = ScalerGetByte(P29_E5_CBUS_CTRL_45);
                            }

                            return _MHL_SUCCESS;
                        }
                        else
                        {
                            return _MHL_FAIL;
                        }
                    }
                }
                else if((ScalerGetBit(P29_F7_CBUS_CTRL_57, _BIT7) == _BIT7) && (ScalerGetByte(P29_D2_CBUS_CTRL_32) == _MSC_PROTOCOL_ERROR))
                {
                    // Clear Flags
                    ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
                    ScalerSetBit(P29_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);

                    return _MHL_PROTOCOL_ERROR;
                }

                ScalerTimerDelayXms(1);
            }

            // Clear Flag
            ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
            ScalerSetBit(P29_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);
#endif
            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

            // Check If Source Has Sent An ABORT Packet
            if(ScalerGetBit(P28_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
            {
                ScalerSetByte(P28_CF_CBUS_CTRL_2F, _BIT2);

                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT);

                SET_MHL_READY_TO_TRANSMIT(1, _FALSE);

                return _MHL_FAIL;
            }

            // Clear FIFO and Send Command Only
            ScalerSetByte(P28_DE_CBUS_CTRL_3E, (_BIT6 | ucSendType));

            // Set MSC Command
            ScalerSetByte(P28_DF_CBUS_CTRL_3F, enumMSCCommand);

            // Set MSC Offset
            ScalerSetByte(P28_E1_CBUS_CTRL_41, enumMSCOffset);

            if(enumMSCCommand == _MSC_WRITE_BURST)
            {
                // Set MSC Last Command
                ScalerSetByte(P28_E0_CBUS_CTRL_40, _MSC_EOF_PACKET);

                // Set MSC Data
                for(ucI = 0; ucI < ucDataLength; ucI++)
                {
                    ScalerSetByte(P28_E2_CBUS_CTRL_42, pucData[ucI]);
                }
            }
            else if((enumMSCCommand != _MSC_READ_DEVCAP) && (enumMSCCommand != _MSC_READ_XDEVCAP))
            {
                // Set MSC Value
                ScalerSetByte(P28_E2_CBUS_CTRL_42, enumMSCValue);
            }

            // MSC Packet and Wait Type
            ScalerSetBit(P28_E3_CBUS_CTRL_43, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), ((_MSC_PACKET << 6) | ucWaitType));

            // Send Request
            ScalerSetBit(P28_DE_CBUS_CTRL_3E, ~(_BIT7), _BIT7);

            // Check if Process is finished
            while(--ucTimeOut != 0)
            {
                if(ScalerGetBit(P28_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
                {
                    // Clear Flag
                    ScalerSetBit(P28_CF_CBUS_CTRL_2F, ~_BIT2, _BIT2);

                    return _MHL_ABORT_FAIL;
                }
                else if((ScalerGetBit(P28_F6_CBUS_CTRL_56, _BIT7) == _BIT7) && (ScalerGetBit(P28_F7_CBUS_CTRL_57, _BIT7) == 0x00))
                {
                    // Clear Flag
                    ScalerSetBit(P28_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);

                    if(ucWaitType == _MSC_WAIT_NULL)
                    {
                        return _MHL_SUCCESS;
                    }
                    else
                    {
                        // Check ACK Packet
                        if(ScalerGetByte(P28_E4_CBUS_CTRL_44) == _MSC_ACK_PACKET)
                        {
                            if((enumMSCCommand == _MSC_READ_DEVCAP) || (enumMSCCommand == _MSC_READ_XDEVCAP))
                            {
                                *pucData = ScalerGetByte(P28_E5_CBUS_CTRL_45);
                            }

                            return _MHL_SUCCESS;
                        }
                        else
                        {
                            return _MHL_FAIL;
                        }
                    }
                }
                else if((ScalerGetBit(P28_F7_CBUS_CTRL_57, _BIT7) == _BIT7) && (ScalerGetByte(P28_D2_CBUS_CTRL_32) == _MSC_PROTOCOL_ERROR))
                {
                    // Clear Flags
                    ScalerSetBit(P28_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
                    ScalerSetBit(P28_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);

                    return _MHL_PROTOCOL_ERROR;
                }

                ScalerTimerDelayXms(1);
            }

            // Clear Flag
            ScalerSetBit(P28_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
            ScalerSetBit(P28_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

            // Check If Source Has Sent An ABORT Packet
            if(ScalerGetBit(P29_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
            {
                ScalerSetByte(P29_CF_CBUS_CTRL_2F, _BIT2);

                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT);

                SET_MHL_READY_TO_TRANSMIT(1, _FALSE);

                return _MHL_FAIL;
            }

            // Clear FIFO and Send Command Only
            ScalerSetByte(P29_DE_CBUS_CTRL_3E, (_BIT6 | ucSendType));

            // Set MSC Command
            ScalerSetByte(P29_DF_CBUS_CTRL_3F, enumMSCCommand);

            // Set MSC Offset
            ScalerSetByte(P29_E1_CBUS_CTRL_41, enumMSCOffset);

            if(enumMSCCommand == _MSC_WRITE_BURST)
            {
                // Set MSC Last Command
                ScalerSetByte(P29_E0_CBUS_CTRL_40, _MSC_EOF_PACKET);

                // Set MSC Data
                for(ucI = 0; ucI < ucDataLength; ucI++)
                {
                    ScalerSetByte(P29_E2_CBUS_CTRL_42, pucData[ucI]);
                }
            }
            else if((enumMSCCommand != _MSC_READ_DEVCAP) && (enumMSCCommand != _MSC_READ_XDEVCAP))
            {
                // Set MSC Value
                ScalerSetByte(P29_E2_CBUS_CTRL_42, enumMSCValue);
            }

            // MSC Packet and Wait Type
            ScalerSetBit(P29_E3_CBUS_CTRL_43, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), ((_MSC_PACKET << 6) | ucWaitType));

            // Send Request
            ScalerSetBit(P29_DE_CBUS_CTRL_3E, ~(_BIT7), _BIT7);

            // Check if Process is finished
            while(--ucTimeOut != 0)
            {
                if(ScalerGetBit(P29_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
                {
                    // Clear Flag
                    ScalerSetBit(P29_CF_CBUS_CTRL_2F, ~_BIT2, _BIT2);

                    return _MHL_ABORT_FAIL;
                }
                else if((ScalerGetBit(P29_F6_CBUS_CTRL_56, _BIT7) == _BIT7) && (ScalerGetBit(P29_F7_CBUS_CTRL_57, _BIT7) == 0x00))
                {
                    // Clear Flag
                    ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);

                    if(ucWaitType == _MSC_WAIT_NULL)
                    {
                        return _MHL_SUCCESS;
                    }
                    else
                    {
                        // Check ACK Packet
                        if(ScalerGetByte(P29_E4_CBUS_CTRL_44) == _MSC_ACK_PACKET)
                        {
                            if((enumMSCCommand == _MSC_READ_DEVCAP) || (enumMSCCommand == _MSC_READ_XDEVCAP))
                            {
                                *pucData = ScalerGetByte(P29_E5_CBUS_CTRL_45);
                            }

                            return _MHL_SUCCESS;
                        }
                        else
                        {
                            return _MHL_FAIL;
                        }
                    }
                }
                else if((ScalerGetBit(P29_F7_CBUS_CTRL_57, _BIT7) == _BIT7) && (ScalerGetByte(P29_D2_CBUS_CTRL_32) == _MSC_PROTOCOL_ERROR))
                {
                    // Clear Flags
                    ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
                    ScalerSetBit(P29_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);

                    return _MHL_PROTOCOL_ERROR;
                }

                ScalerTimerDelayXms(1);
            }

            // Clear Flag
            ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
            ScalerSetBit(P29_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);
#endif
            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

            // Check If Source Has Sent An ABORT Packet
            if(ScalerGetBit(P28_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
            {
                ScalerSetByte(P28_CF_CBUS_CTRL_2F, _BIT2);

                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX2_READY_TO_TRANSMIT);

                SET_MHL_READY_TO_TRANSMIT(2, _FALSE);

                return _MHL_FAIL;
            }

            // Clear FIFO and Send Command Only
            ScalerSetByte(P28_DE_CBUS_CTRL_3E, (_BIT6 | ucSendType));

            // Set MSC Command
            ScalerSetByte(P28_DF_CBUS_CTRL_3F, enumMSCCommand);

            // Set MSC Offset
            ScalerSetByte(P28_E1_CBUS_CTRL_41, enumMSCOffset);

            if(enumMSCCommand == _MSC_WRITE_BURST)
            {
                // Set MSC Last Command
                ScalerSetByte(P28_E0_CBUS_CTRL_40, _MSC_EOF_PACKET);

                // Set MSC Data
                for(ucI = 0; ucI < ucDataLength; ucI++)
                {
                    ScalerSetByte(P28_E2_CBUS_CTRL_42, pucData[ucI]);
                }
            }
            else if((enumMSCCommand != _MSC_READ_DEVCAP) && (enumMSCCommand != _MSC_READ_XDEVCAP))
            {
                // Set MSC Value
                ScalerSetByte(P28_E2_CBUS_CTRL_42, enumMSCValue);
            }

            // MSC Packet and Wait Type
            ScalerSetBit(P28_E3_CBUS_CTRL_43, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), ((_MSC_PACKET << 6) | ucWaitType));

            // Send Request
            ScalerSetBit(P28_DE_CBUS_CTRL_3E, ~(_BIT7), _BIT7);

            // Check if Process is finished
            while(--ucTimeOut != 0)
            {
                if(ScalerGetBit(P28_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
                {
                    // Clear Flag
                    ScalerSetBit(P28_CF_CBUS_CTRL_2F, ~_BIT2, _BIT2);

                    return _MHL_ABORT_FAIL;
                }
                else if((ScalerGetBit(P28_F6_CBUS_CTRL_56, _BIT7) == _BIT7) && (ScalerGetBit(P28_F7_CBUS_CTRL_57, _BIT7) == 0x00))
                {
                    // Clear Flag
                    ScalerSetBit(P28_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);

                    if(ucWaitType == _MSC_WAIT_NULL)
                    {
                        return _MHL_SUCCESS;
                    }
                    else
                    {
                        // Check ACK Packet
                        if(ScalerGetByte(P28_E4_CBUS_CTRL_44) == _MSC_ACK_PACKET)
                        {
                            if((enumMSCCommand == _MSC_READ_DEVCAP) || (enumMSCCommand == _MSC_READ_XDEVCAP))
                            {
                                *pucData = ScalerGetByte(P28_E5_CBUS_CTRL_45);
                            }

                            return _MHL_SUCCESS;
                        }
                        else
                        {
                            return _MHL_FAIL;
                        }
                    }
                }
                else if((ScalerGetBit(P28_F7_CBUS_CTRL_57, _BIT7) == _BIT7) && (ScalerGetByte(P28_D2_CBUS_CTRL_32) == _MSC_PROTOCOL_ERROR))
                {
                    // Clear Flags
                    ScalerSetBit(P28_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
                    ScalerSetBit(P28_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);

                    return _MHL_PROTOCOL_ERROR;
                }

                ScalerTimerDelayXms(1);
            }

            // Clear Flag
            ScalerSetBit(P28_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
            ScalerSetBit(P28_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);

#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

            // Check If Source Has Sent An ABORT Packet
            if(ScalerGetBit(P29_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
            {
                ScalerSetByte(P29_CF_CBUS_CTRL_2F, _BIT2);

                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX2_READY_TO_TRANSMIT);

                SET_MHL_READY_TO_TRANSMIT(2, _FALSE);

                return _MHL_FAIL;
            }

            // Clear FIFO and Send Command Only
            ScalerSetByte(P29_DE_CBUS_CTRL_3E, (_BIT6 | ucSendType));

            // Set MSC Command
            ScalerSetByte(P29_DF_CBUS_CTRL_3F, enumMSCCommand);

            // Set MSC Offset
            ScalerSetByte(P29_E1_CBUS_CTRL_41, enumMSCOffset);

            if(enumMSCCommand == _MSC_WRITE_BURST)
            {
                // Set MSC Last Command
                ScalerSetByte(P29_E0_CBUS_CTRL_40, _MSC_EOF_PACKET);

                // Set MSC Data
                for(ucI = 0; ucI < ucDataLength; ucI++)
                {
                    ScalerSetByte(P29_E2_CBUS_CTRL_42, pucData[ucI]);
                }
            }
            else if((enumMSCCommand != _MSC_READ_DEVCAP) && (enumMSCCommand != _MSC_READ_XDEVCAP))
            {
                // Set MSC Value
                ScalerSetByte(P29_E2_CBUS_CTRL_42, enumMSCValue);
            }

            // MSC Packet and Wait Type
            ScalerSetBit(P29_E3_CBUS_CTRL_43, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), ((_MSC_PACKET << 6) | ucWaitType));

            // Send Request
            ScalerSetBit(P29_DE_CBUS_CTRL_3E, ~(_BIT7), _BIT7);

            // Check if Process is finished
            while(--ucTimeOut != 0)
            {
                if(ScalerGetBit(P29_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
                {
                    // Clear Flag
                    ScalerSetBit(P29_CF_CBUS_CTRL_2F, ~_BIT2, _BIT2);

                    return _MHL_ABORT_FAIL;
                }
                else if((ScalerGetBit(P29_F6_CBUS_CTRL_56, _BIT7) == _BIT7) && (ScalerGetBit(P29_F7_CBUS_CTRL_57, _BIT7) == 0x00))
                {
                    // Clear Flag
                    ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);

                    if(ucWaitType == _MSC_WAIT_NULL)
                    {
                        return _MHL_SUCCESS;
                    }
                    else
                    {
                        // Check ACK Packet
                        if(ScalerGetByte(P29_E4_CBUS_CTRL_44) == _MSC_ACK_PACKET)
                        {
                            if((enumMSCCommand == _MSC_READ_DEVCAP) || (enumMSCCommand == _MSC_READ_XDEVCAP))
                            {
                                *pucData = ScalerGetByte(P29_E5_CBUS_CTRL_45);
                            }

                            return _MHL_SUCCESS;
                        }
                        else
                        {
                            return _MHL_FAIL;
                        }
                    }
                }
                else if((ScalerGetBit(P29_F7_CBUS_CTRL_57, _BIT7) == _BIT7) && (ScalerGetByte(P29_D2_CBUS_CTRL_32) == _MSC_PROTOCOL_ERROR))
                {
                    // Clear Flags
                    ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
                    ScalerSetBit(P29_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);

                    return _MHL_PROTOCOL_ERROR;
                }

                ScalerTimerDelayXms(1);
            }

            // Clear Flag
            ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
            ScalerSetBit(P29_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);
#endif
            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }

    return _MHL_FAIL;
}

//--------------------------------------------------
// Description  : Check Write Status for D0 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLMscCheckDeviceINT(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

            ScalerMHLMscCheckDeviceINTCBUS0(ucInputPort);

#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

            ScalerMHLMscCheckDeviceINTCBUS1(ucInputPort);

#endif // End of #if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

            ScalerMHLMscCheckDeviceINTCBUS0(ucInputPort);

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

            ScalerMHLMscCheckDeviceINTCBUS1(ucInputPort);

#endif // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

            ScalerMHLMscCheckDeviceINTCBUS0(ucInputPort);

#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

            ScalerMHLMscCheckDeviceINTCBUS1(ucInputPort);

#endif // End of #if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }
}

#if((_D0_CBUS_CHANNEL_SEL == _CBUS0) || (_D1_CBUS_CHANNEL_SEL == _CBUS0) || (_D2_CBUS_CHANNEL_SEL == _CBUS0))
//--------------------------------------------------
// Description  : Check Write Status for CBUS0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLMscCheckDeviceINTCBUS0(BYTE ucInputPort)
{
    WORD usTmp = 0;
    BYTE ucBirstLength = 0;
    BYTE pucWriteBurstTmp[16];

    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:


            /***************************************************************/
            /************* Get MSC_MSG(0x68) Invalid Command ***************/
            /***************************************************************/

            if(((bit)ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT3) == _TRUE) && ((bit)ScalerGetBit(P28_D4_CBUS_CTRL_34, _BIT1) == _TRUE))
            {
                if(ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_MSGE, _MSCE_INVALID_SUB_CMD) == _TRUE)
                {
                    // Clear Falgs
                    ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
                    ScalerSetBit(P28_D4_CBUS_CTRL_34, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
                }
            }


            /**************************************************************/
            /******** Get MSC Command WRITE_STAT or SET_INT(0x60) *********/
            /**************************************************************/

            if((bit)ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT7) == _TRUE)
            {
                //----------------------------------------------------------//
                //-------- Check DevCap Ready (DCAP_RDY, DCAP_CHG) ---------//
                //----------------------------------------------------------//
                if((((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY) == _TRUE) ||
                    ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)))
                {
                    if(GET_MHL_RX0_MHL_VERSION() == _MHL_VERSION_NULL)
                    {
                        // Read Source Device MHL Version
                        if(ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_MHL_VERSION_01, &g_ucMHLRx0MhlVersion, _MSC_READ_DEVCAP) == _TRUE)
                        {
                            if((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)
                            {
                                // Write 1 Clear DevCap_Chg Flag
                                ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG);
                            }

                            // Clear Flag
                            ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                        }
                    }

                    // Read Source Adopter ID
                    if((GET_MHL_RX0_ADOPTER_ID_DONE() == _FALSE) && (GET_MHL_READY_TO_TRANSMIT(0) == _TRUE))
                    {
                        if((ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_H_03, &g_ucMHLRx0AdopterIDH, _MSC_READ_DEVCAP) == _TRUE) &&
                           (ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_L_04, &g_ucMHLRx0AdopterIDL, _MSC_READ_DEVCAP) == _TRUE))
                        {
                            DebugMessageMHL("D0 MHL Adopter IDH", g_ucMHLRx0AdopterIDH);
                            DebugMessageMHL("D0 MHL Adopter IDL", g_ucMHLRx0AdopterIDL);

                            SET_MHL_RX0_ADOPTER_ID_DONE();

                            // Clear Flag
                            ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
                        }
                    }
                }


                //----------------------------------------------//
                //------ Check Request To Write (REQ_WRT) ------//
                //----------------------------------------------//
                if(((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _TRUE) && (GET_MHL_RX0_WRITE_BURST_PROCESS_DONE() == _TRUE))
                {
                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_GRT_WRT) == _SUCCESS)
                    {
                        CLR_MHL_RX0_WRITE_BURST_PROCESS_DONE();

                        // Clear Flag
                        ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

                        // Clear _MSC_REQ_WRT Flag
                        ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT);
                    }
                }


                //-----------------------------------------------------------//
                //-- Check 3D Request and Reply No Support For All Timings --//
                //-----------------------------------------------------------//
                if((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ) == _TRUE)
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

                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                    {
                        usTmp = 400;

                        while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                        {
                            ScalerTimerDelayXms(5);
                        }

                        if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[0], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                        {
                            if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                            {
                                usTmp = 400;

                                while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                                {
                                    ScalerTimerDelayXms(5);
                                }

                                if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[6], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                                {
                                    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ);

                                    // Clear Flag
                                    ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                                }
                            }
                        }
                    }
                }
            }

            /****************************************************************/
            /********* Source Device Reading Sink MSC Error Code ************/
            /****************************************************************/

            if((bit)ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT0) == _TRUE)
            {
                // Clear Flag
                ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }

            // Sent Command to Triger VBUS for HTC M8
            if(((GET_MHL_RX0_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX0_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX0_SENT_MSC_DCAP_RDY() == _FALSE) && (GET_MHL_PROCESS_STATE(0) == _MHL_STATE_SET_DEV_CAP_DONE))
            {
                ScalerMHLMscSendCommand(0, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);
                DebugMessageRx0("D0 MHL Sent Devies Capabilitly Ready", 0);
                SET_MHL_RX0_SENT_MSC_DCAP_RDY();
            }

#if(_D0_MHL_VERSION < _MHL_VERSION_3_0)

            if(((GET_MHL_RX0_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX0_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX0_MHL_VERSION() >= _MHL_VERSION_3_0) && (GET_MHL_RX0_CBUS_RESET_FOR_HTC_DONE() == _FALSE))
            {
                ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _MHL_VERSION_1_2);

                ScalerMHLMscSendCommand(ucInputPort, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);

                SET_MHL_RX0_CBUS_RESET_FOR_HTC_DONE();
            }

#endif // End of #if(_D0_MHL_VERSION < _MHL_VERSION_3_0)

#if(_MHL_CBUS_CTS_MODE == _ON)

            if(ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT5) == _BIT5)
            {
                ScalerSetBit(P28_C8_CBUS_CTRL_28, ~_BIT6, _BIT6);

                ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT5);
            }

            if(ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT4) == _BIT4)
            {
                ScalerSetBit(P28_C8_CBUS_CTRL_28, ~_BIT6, 0x00);

                ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
            }

#endif // Enf of #if(_MHL_CBUS_CTS_MODE == _ON)

            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:


            /***************************************************************/
            /************* Get MSC_MSG(0x68) Invalid Command ***************/
            /***************************************************************/

            if(((bit)ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT3) == _TRUE) && ((bit)ScalerGetBit(P28_D4_CBUS_CTRL_34, _BIT1) == _TRUE))
            {
                if(ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_MSGE, _MSCE_INVALID_SUB_CMD) == _TRUE)
                {
                    // Clear Falgs
                    ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
                    ScalerSetBit(P28_D4_CBUS_CTRL_34, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
                }
            }


            /**************************************************************/
            /******** Get MSC Command WRITE_STAT or SET_INT(0x60) *********/
            /**************************************************************/

            if((bit)ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT7) == _TRUE)
            {
                //----------------------------------------------------------//
                //-------- Check DevCap Ready (DCAP_RDY, DCAP_CHG) ---------//
                //----------------------------------------------------------//
                if((((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY) == _TRUE) ||
                    ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)))
                {
                    if(GET_MHL_RX1_MHL_VERSION() == _MHL_VERSION_NULL)
                    {
                        // Read Source Device MHL Version
                        if(ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_MHL_VERSION_01, &g_ucMHLRx1MhlVersion, _MSC_READ_DEVCAP) == _TRUE)
                        {
                            if((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)
                            {
                                // Write 1 Clear DevCap_Chg Flag
                                ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG);
                            }

                            // Clear Flag
                            ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                        }
                    }

                    // Read Source Adopter ID
                    if((GET_MHL_RX1_ADOPTER_ID_DONE() == _FALSE) && (GET_MHL_READY_TO_TRANSMIT(1) == _TRUE))
                    {
                        if((ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_H_03, &g_ucMHLRx1AdopterIDH, _MSC_READ_DEVCAP) == _TRUE) &&
                           (ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_L_04, &g_ucMHLRx1AdopterIDL, _MSC_READ_DEVCAP) == _TRUE))
                        {
                            DebugMessageMHL("D1 MHL Adopter IDH", g_ucMHLRx1AdopterIDH);
                            DebugMessageMHL("D1 MHL Adopter IDL", g_ucMHLRx1AdopterIDL);

                            SET_MHL_RX1_ADOPTER_ID_DONE();

                            // Clear Flag
                            ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
                        }
                    }
                }

                //----------------------------------------------//
                //------ Check Request To Write (REQ_WRT) ------//
                //----------------------------------------------//
                if(((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _TRUE) && (GET_MHL_RX1_WRITE_BURST_PROCESS_DONE() == _TRUE))
                {
                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_GRT_WRT) == _SUCCESS)
                    {
                        CLR_MHL_RX1_WRITE_BURST_PROCESS_DONE();

                        // Clear Flag
                        ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

                        // Clear _MSC_REQ_WRT Flag
                        ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT);
                    }
                }


                //-----------------------------------------------------------//
                //-- Check 3D Request and Reply No Support For All Timings --//
                //-----------------------------------------------------------//
                if((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ) == _TRUE)
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

                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                    {
                        usTmp = 400;

                        while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                        {
                            ScalerTimerDelayXms(5);
                        }

                        if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[0], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                        {
                            if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                            {
                                usTmp = 400;

                                while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                                {
                                    ScalerTimerDelayXms(5);
                                }

                                if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[ucBirstLength], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                                {
                                    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ);

                                    // Clear Flag
                                    ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                                }
                            }
                        }
                    }
                }
            }
            /****************************************************************/
            /********* Source Device Reading Sink MSC Error Code ************/
            /****************************************************************/

            if((bit)ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT0) == _TRUE)
            {
                // Clear Flag
                ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }

            // Sent Command to Triger VBUS for HTC M8
            if(((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX1_SENT_MSC_DCAP_RDY() == _FALSE) && (GET_MHL_PROCESS_STATE(1) == _MHL_STATE_SET_DEV_CAP_DONE))
            {
                ScalerMHLMscSendCommand(1, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);
                DebugMessageRx1("D1 MHL Sent Devies Capabilitly Ready", 0);
                SET_MHL_RX1_SENT_MSC_DCAP_RDY();
            }

#if(_D1_MHL_VERSION < _MHL_VERSION_3_0)

            if(((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX1_MHL_VERSION() >= _MHL_VERSION_3_0) && (GET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE() == _FALSE))
            {
                ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _MHL_VERSION_1_2);

                ScalerMHLMscSendCommand(ucInputPort, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);

                SET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE();
            }

#endif // End of #if(_D1_MHL_VERSION < _MHL_VERSION_3_0)

#if(_MHL_CBUS_CTS_MODE == _ON)

            if(ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT5) == _BIT5)
            {
                ScalerSetBit(P28_C8_CBUS_CTRL_28, ~_BIT6, _BIT6);

                ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT5);
            }

            if(ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT4) == _BIT4)
            {
                ScalerSetBit(P28_C8_CBUS_CTRL_28, ~_BIT6, 0x00);

                ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
            }

#endif // Enf of #if(_MHL_CBUS_CTS_MODE == _ON)

            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:


            /***************************************************************/
            /************* Get MSC_MSG(0x68) Invalid Command ***************/
            /***************************************************************/

            if(((bit)ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT3) == _TRUE) && ((bit)ScalerGetBit(P28_D4_CBUS_CTRL_34, _BIT1) == _TRUE))
            {
                if(ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_MSGE, _MSCE_INVALID_SUB_CMD) == _TRUE)
                {
                    // Clear Falgs
                    ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
                    ScalerSetBit(P28_D4_CBUS_CTRL_34, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
                }
            }


            /**************************************************************/
            /******** Get MSC Command WRITE_STAT or SET_INT(0x60) *********/
            /**************************************************************/

            if((bit)ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT7) == _TRUE)
            {
                //----------------------------------------------------------//
                //-------- Check DevCap Ready (DCAP_RDY, DCAP_CHG) ---------//
                //----------------------------------------------------------//
                if((((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY) == _TRUE) ||
                    ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)))
                {
                    if(GET_MHL_RX2_MHL_VERSION() == _MHL_VERSION_NULL)
                    {
                        // Read Source Device MHL Version
                        if(ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_MHL_VERSION_01, &g_ucMHLRx2MhlVersion, _MSC_READ_DEVCAP) == _TRUE)
                        {
                            if((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)
                            {
                                // Write 1 Clear DevCap_Chg Flag
                                ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG);
                            }

                            // Clear Flag
                            ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                        }
                    }

                    // Read Source Adopter ID
                    if((GET_MHL_RX2_ADOPTER_ID_DONE() == _FALSE) && (GET_MHL_READY_TO_TRANSMIT(2) == _TRUE))
                    {
                        if((ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_H_03, &g_ucMHLRx2AdopterIDH, _MSC_READ_DEVCAP) == _TRUE) &&
                           (ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_L_04, &g_ucMHLRx2AdopterIDL, _MSC_READ_DEVCAP) == _TRUE))
                        {
                            DebugMessageMHL("D2 MHL Adopter IDH", g_ucMHLRx2AdopterIDH);
                            DebugMessageMHL("D2 MHL Adopter IDL", g_ucMHLRx2AdopterIDL);

                            SET_MHL_RX2_ADOPTER_ID_DONE();

                            // Clear Flag
                            ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
                        }
                    }
                }


                //----------------------------------------------//
                //------ Check Request To Write (REQ_WRT) ------//
                //----------------------------------------------//
                if(((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _TRUE) && (GET_MHL_RX2_WRITE_BURST_PROCESS_DONE() == _TRUE))
                {
                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_GRT_WRT) == _SUCCESS)
                    {
                        CLR_MHL_RX2_WRITE_BURST_PROCESS_DONE();

                        // Clear Flag
                        ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

                        // Clear _MSC_REQ_WRT Flag
                        ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT);
                    }
                }


                //-----------------------------------------------------------//
                //-- Check 3D Request and Reply No Support For All Timings --//
                //-----------------------------------------------------------//
                if((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ) == _TRUE)
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

                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                    {
                        usTmp = 400;

                        while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                        {
                            ScalerTimerDelayXms(5);
                        }

                        if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[0], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                        {
                            if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                            {
                                usTmp = 400;

                                while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                                {
                                    ScalerTimerDelayXms(5);
                                }

                                if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[ucBirstLength], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                                {
                                    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ);

                                    // Clear Flag
                                    ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                                }
                            }
                        }
                    }
                }
            }

            /****************************************************************/
            /********* Source Device Reading Sink MSC Error Code ************/
            /****************************************************************/

            if((bit)ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT0) == _TRUE)
            {
                // Clear Flag
                ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }

            // Sent Command to Triger VBUS for HTC M8
            if(((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX2_SENT_MSC_DCAP_RDY() == _FALSE) && (GET_MHL_PROCESS_STATE(2) == _MHL_STATE_SET_DEV_CAP_DONE))
            {
                ScalerMHLMscSendCommand(2, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);
                DebugMessageRx2("D2 MHL Sent Devies Capabilitly Ready", 0);
                SET_MHL_RX2_SENT_MSC_DCAP_RDY();
            }

#if(_D2_MHL_VERSION < _MHL_VERSION_3_0)

            if(((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX2_MHL_VERSION() >= _MHL_VERSION_3_0) && (GET_MHL_RX2_CBUS_RESET_FOR_HTC_DONE() == _FALSE))
            {
                ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _MHL_VERSION_1_2);

                ScalerMHLMscSendCommand(ucInputPort, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);

                SET_MHL_RX2_CBUS_RESET_FOR_HTC_DONE();
            }

#endif // End of #if(_D2_MHL_VERSION < _MHL_VERSION_3_0)

#if(_MHL_CBUS_CTS_MODE == _ON)

            if(ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT5) == _BIT5)
            {
                ScalerSetBit(P28_C8_CBUS_CTRL_28, ~_BIT6, _BIT6);

                ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT5);
            }

            if(ScalerGetBit(P28_CE_CBUS_CTRL_2E, _BIT4) == _BIT4)
            {
                ScalerSetBit(P28_C8_CBUS_CTRL_28, ~_BIT6, 0x00);

                ScalerSetBit(P28_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
            }

#endif // Enf of #if(_MHL_CBUS_CTS_MODE == _ON)

            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }
}
#endif

#if((_D0_CBUS_CHANNEL_SEL == _CBUS1) || (_D1_CBUS_CHANNEL_SEL == _CBUS1) || (_D2_CBUS_CHANNEL_SEL == _CBUS1))
//--------------------------------------------------
// Description  : Check Write Status for CBUS0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLMscCheckDeviceINTCBUS1(BYTE ucInputPort)
{
    WORD usTmp = 0;
    BYTE ucBirstLength = 0;
    BYTE pucWriteBurstTmp[16];

    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:


            /***************************************************************/
            /************* Get MSC_MSG(0x68) Invalid Command ***************/
            /***************************************************************/

            if(((bit)ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT3) == _TRUE) && ((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT1) == _TRUE))
            {
                if(ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_MSGE, _MSCE_INVALID_SUB_CMD) == _TRUE)
                {
                    // Clear Falgs
                    ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
                    ScalerSetBit(P29_D4_CBUS_CTRL_34, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
                }
            }


            /**************************************************************/
            /******** Get MSC Command WRITE_STAT or SET_INT(0x60) *********/
            /**************************************************************/

            if((bit)ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT7) == _TRUE)
            {
                //----------------------------------------------------------//
                //-------- Check DevCap Ready (DCAP_RDY, DCAP_CHG) ---------//
                //----------------------------------------------------------//
                if((((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY) == _TRUE) ||
                    ((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)))
                {
                    if(GET_MHL_RX0_MHL_VERSION() == _MHL_VERSION_NULL)
                    {
                        // Read Source Device MHL Version
                        if(ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_MHL_VERSION_01, &g_ucMHLRx0MhlVersion, _MSC_READ_DEVCAP) == _TRUE)
                        {
                            if((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)
                            {
                                // Write 1 Clear DevCap_Chg Flag
                                ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG);
                            }

                            // Clear Flag
                            ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                        }
                    }

                    // Read Source Adopter ID
                    if((GET_MHL_RX0_ADOPTER_ID_DONE() == _FALSE) && (GET_MHL_READY_TO_TRANSMIT(0) == _TRUE))
                    {
                        if((ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_H_03, &g_ucMHLRx0AdopterIDH, _MSC_READ_DEVCAP) == _TRUE) &&
                           (ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_L_04, &g_ucMHLRx0AdopterIDL, _MSC_READ_DEVCAP) == _TRUE))
                        {
                            DebugMessageMHL("D0 MHL Adopter IDH", g_ucMHLRx0AdopterIDH);
                            DebugMessageMHL("D0 MHL Adopter IDL", g_ucMHLRx0AdopterIDL);

                            SET_MHL_RX0_ADOPTER_ID_DONE();

                            if((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)
                            {
                                // Write 1 Clear DevCap_Chg Flag
                                ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG);
                            }

                            // Clear Flag
                            ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
                        }
                    }
                }


                //----------------------------------------------//
                //------ Check Request To Write (REQ_WRT) ------//
                //----------------------------------------------//
                if(((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _TRUE) && (GET_MHL_RX0_WRITE_BURST_PROCESS_DONE() == _TRUE))
                {
                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_GRT_WRT) == _SUCCESS)
                    {
                        CLR_MHL_RX0_WRITE_BURST_PROCESS_DONE();

                        // Clear _MSC_REQ_WRT Flag
                        ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT);

                        // Clear Flag
                        ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                    }
                }


                //-----------------------------------------------------------//
                //-- Check 3D Request and Reply No Support For All Timings --//
                //-----------------------------------------------------------//
                if((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ) == _TRUE)
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

                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                    {
                        usTmp = 400;

                        while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                        {
                            ScalerTimerDelayXms(5);
                        }

                        if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[0], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                        {
                            if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                            {
                                usTmp = 400;

                                while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                                {
                                    ScalerTimerDelayXms(5);
                                }

                                if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[ucBirstLength], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                                {
                                    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ);

                                    // Clear Flag
                                    ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                                }
                            }
                        }
                    }
                }
            }


            /****************************************************************/
            /********* Source Device Reading Sink MSC Error Code ************/
            /****************************************************************/

            if((bit)ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT0) == _TRUE)
            {
                // Clear Error Code
                ScalerSetByte(P29_D2_CBUS_CTRL_32, 0xFF);

                // Clear Flag
                ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }

            // Sent Command to Triger VBUS for HTC M8
            if(((GET_MHL_RX0_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX0_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX0_SENT_MSC_DCAP_RDY() == _FALSE) && (GET_MHL_PROCESS_STATE(0) == _MHL_STATE_SET_DEV_CAP_DONE))
            {
                ScalerMHLMscSendCommand(0, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);
                DebugMessageRx0("D0 MHL Sent Devies Capabilitly Ready", 0);
                SET_MHL_RX0_SENT_MSC_DCAP_RDY();
            }

#if(_D0_MHL_VERSION < _MHL_VERSION_3_0)

            if(((GET_MHL_RX0_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX0_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX0_MHL_VERSION() >= _MHL_VERSION_3_0) && (GET_MHL_RX0_CBUS_RESET_FOR_HTC_DONE() == _FALSE))
            {
                ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _MHL_VERSION_1_2);

                ScalerMHLMscSendCommand(ucInputPort, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);

                SET_MHL_RX0_CBUS_RESET_FOR_HTC_DONE();
            }

#endif // End of #if(_D0_MHL_VERSION < _MHL_VERSION_3_0)

#if(_MHL_CBUS_CTS_MODE == _ON)

            if(ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT5) == _BIT5)
            {
                ScalerSetBit(P29_C8_CBUS_CTRL_28, ~_BIT6, _BIT6);

                ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT5);
            }

            if(ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT4) == _BIT4)
            {
                ScalerSetBit(P29_C8_CBUS_CTRL_28, ~_BIT6, 0x00);

                ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
            }

#endif // Enf of #if(_MHL_CBUS_CTS_MODE == _ON)

            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:


            /***************************************************************/
            /************* Get MSC_MSG(0x68) Invalid Command ***************/
            /***************************************************************/

            if(((bit)ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT3) == _TRUE) && ((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT1) == _TRUE))
            {
                if(ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_MSGE, _MSCE_INVALID_SUB_CMD) == _TRUE)
                {
                    // Clear Falgs
                    ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
                    ScalerSetBit(P29_D4_CBUS_CTRL_34, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
                }
            }


            /**************************************************************/
            /******** Get MSC Command WRITE_STAT or SET_INT(0x60) *********/
            /**************************************************************/

            if((bit)ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT7) == _TRUE)
            {
                //----------------------------------------------------------//
                //-------- Check DevCap Ready (DCAP_RDY, DCAP_CHG) ---------//
                //----------------------------------------------------------//
                if((((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY) == _TRUE) ||
                    ((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)))
                {
                    if(GET_MHL_RX1_MHL_VERSION() == _MHL_VERSION_NULL)
                    {
                        // Read Source Device MHL Version
                        if(ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_MHL_VERSION_01, &g_ucMHLRx1MhlVersion, _MSC_READ_DEVCAP) == _TRUE)
                        {
                            // Write 1 Clear DevCap_Chg Flag
                            ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG);

                            // Clear Flag
                            ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                        }
                    }

                    // Read Source Adopter ID
                    if((GET_MHL_RX1_ADOPTER_ID_DONE() == _FALSE) && (GET_MHL_READY_TO_TRANSMIT(1) == _TRUE))
                    {
                        if((ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_H_03, &g_ucMHLRx1AdopterIDH, _MSC_READ_DEVCAP) == _TRUE) &&
                           (ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_L_04, &g_ucMHLRx1AdopterIDL, _MSC_READ_DEVCAP) == _TRUE))
                        {
                            DebugMessageMHL("D1 MHL Adopter IDH", g_ucMHLRx1AdopterIDH);
                            DebugMessageMHL("D1 MHL Adopter IDL", g_ucMHLRx1AdopterIDL);

                            SET_MHL_RX1_ADOPTER_ID_DONE();

                            // Clear Flag
                            ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
                        }
                    }
                }


                //----------------------------------------------//
                //------ Check Request To Write (REQ_WRT) ------//
                //----------------------------------------------//
                if(((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _TRUE) && (GET_MHL_RX1_WRITE_BURST_PROCESS_DONE() == _TRUE))
                {
                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_GRT_WRT) == _SUCCESS)
                    {
                        CLR_MHL_RX1_WRITE_BURST_PROCESS_DONE();

                        // Clear Flag
                        ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

                        // Clear _MSC_REQ_WRT Flag
                        ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT);
                    }
                }


                //-----------------------------------------------------------//
                //-- Check 3D Request and Reply No Support For All Timings --//
                //-----------------------------------------------------------//
                if((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ) == _TRUE)
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

                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                    {
                        usTmp = 400;

                        while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                        {
                            ScalerTimerDelayXms(5);
                        }

                        if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[0], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                        {
                            if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                            {
                                usTmp = 400;

                                while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                                {
                                    ScalerTimerDelayXms(5);
                                }

                                if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[ucBirstLength], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                                {
                                    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ);

                                    // Clear Flag
                                    ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                                }
                            }
                        }
                    }
                }
            }


            /****************************************************************/
            /********* Source Device Reading Sink MSC Error Code ************/
            /****************************************************************/

            if((bit)ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT0) == _TRUE)
            {
                // Clear Error Code
                ScalerSetByte(P29_D2_CBUS_CTRL_32, 0xFF);

                // Clear Flag
                ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }

            // Sent Command to Triger VBUS for HTC M8
            if(((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX1_SENT_MSC_DCAP_RDY() == _FALSE) && (GET_MHL_PROCESS_STATE(1) == _MHL_STATE_SET_DEV_CAP_DONE))
            {
                ScalerMHLMscSendCommand(1, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);
                DebugMessageRx1("D1 MHL Sent Devies Capabilitly Ready", 0);
                SET_MHL_RX1_SENT_MSC_DCAP_RDY();
            }

#if(_D1_MHL_VERSION < _MHL_VERSION_3_0)

            if(((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX1_MHL_VERSION() >= _MHL_VERSION_3_0) && (GET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE() == _FALSE))
            {
                ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _MHL_VERSION_1_2);

                ScalerMHLMscSendCommand(ucInputPort, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);

                SET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE();
            }

#endif // End of #if(_D1_MHL_VERSION < _MHL_VERSION_3_0)

#if(_MHL_CBUS_CTS_MODE == _ON)

            if(ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT5) == _BIT5)
            {
                ScalerSetBit(P29_C8_CBUS_CTRL_28, ~_BIT6, _BIT6);

                ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT5);
            }

            if(ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT4) == _BIT4)
            {
                ScalerSetBit(P29_C8_CBUS_CTRL_28, ~_BIT6, 0x00);

                ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
            }

#endif // Enf of #if(_MHL_CBUS_CTS_MODE == _ON)

            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:


            /***************************************************************/
            /************* Get MSC_MSG(0x68) Invalid Command ***************/
            /***************************************************************/

            if(((bit)ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT3) == _TRUE) && ((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT1) == _TRUE))
            {
                if(ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_MSGE, _MSCE_INVALID_SUB_CMD) == _TRUE)
                {
                    // Clear Falgs
                    ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
                    ScalerSetBit(P29_D4_CBUS_CTRL_34, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
                }
            }


            /**************************************************************/
            /******** Get MSC Command WRITE_STAT or SET_INT(0x60) *********/
            /**************************************************************/

            if((bit)ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT7) == _TRUE)
            {
                //----------------------------------------------------------//
                //-------- Check DevCap Ready (DCAP_RDY, DCAP_CHG) ---------//
                //----------------------------------------------------------//
                if((((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY) == _TRUE) ||
                    ((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)))
                {
                    if(GET_MHL_RX2_MHL_VERSION() == _MHL_VERSION_NULL)
                    {
                        // Read Source Device MHL Version
                        if(ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_MHL_VERSION_01, &g_ucMHLRx2MhlVersion, _MSC_READ_DEVCAP) == _TRUE)
                        {
                            // Write 1 Clear DevCap_Chg Flag
                            ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG);

                            // Clear Flag
                            ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                        }
                    }

                    // Read Source Adopter ID
                    if((GET_MHL_RX2_ADOPTER_ID_DONE() == _FALSE) && (GET_MHL_READY_TO_TRANSMIT(2) == _TRUE))
                    {
                        if((ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_H_03, &g_ucMHLRx2AdopterIDH, _MSC_READ_DEVCAP) == _TRUE) &&
                           (ScalerMHLMscReadDevCapabilities(ucInputPort, _MSC_ADOPTER_ID_L_04, &g_ucMHLRx2AdopterIDL, _MSC_READ_DEVCAP) == _TRUE))
                        {
                            DebugMessageMHL("D2 MHL Adopter IDH", g_ucMHLRx2AdopterIDH);
                            DebugMessageMHL("D2 MHL Adopter IDL", g_ucMHLRx2AdopterIDL);

                            SET_MHL_RX2_ADOPTER_ID_DONE();

                            // Clear Flag
                            ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
                        }
                    }
                }


                //----------------------------------------------//
                //------ Check Request To Write (REQ_WRT) ------//
                //----------------------------------------------//
                if(((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _TRUE) && (GET_MHL_RX2_WRITE_BURST_PROCESS_DONE() == _TRUE))
                {
                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_GRT_WRT) == _SUCCESS)
                    {
                        CLR_MHL_RX2_WRITE_BURST_PROCESS_DONE();

                        // Clear _MSC_REQ_WRT Flag
                        ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT);

                        // Clear Flag
                        ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                    }
                }


                //-----------------------------------------------------------//
                //-- Check 3D Request and Reply No Support For All Timings --//
                //-----------------------------------------------------------//
                if((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ) == _TRUE)
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

                    if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                    {
                        usTmp = 400;

                        while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                        {
                            ScalerTimerDelayXms(5);
                        }

                        if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[0], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                        {
                            if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                            {
                                usTmp = 400;

                                while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                                {
                                    ScalerTimerDelayXms(5);
                                }

                                if(ScalerMHLMscSendWriteBurst(ucInputPort, 0x40, ucBirstLength, &pucWriteBurstTmp[ucBirstLength], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                                {
                                    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ);

                                    // Clear Flag
                                    ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                                }
                            }
                        }
                    }
                }
            }


            /****************************************************************/
            /********* Source Device Reading Sink MSC Error Code ************/
            /****************************************************************/

            if((bit)ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT0) == _TRUE)
            {
                // Clear Error Code
                ScalerSetByte(P29_D2_CBUS_CTRL_32, 0xFF);

                // Clear Flag
                ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }

            // Sent Command to Triger VBUS for HTC M8
            if(((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX2_SENT_MSC_DCAP_RDY() == _FALSE) && (GET_MHL_PROCESS_STATE(2) == _MHL_STATE_SET_DEV_CAP_DONE))
            {
                ScalerMHLMscSendCommand(2, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);
                DebugMessageRx2("D2 MHL Sent Devies Capabilitly Ready", 0);
                SET_MHL_RX2_SENT_MSC_DCAP_RDY();
            }

#if(_D2_MHL_VERSION < _MHL_VERSION_3_0)

            if(((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE)) &&
               (GET_MHL_RX2_MHL_VERSION() >= _MHL_VERSION_3_0) && (GET_MHL_RX2_CBUS_RESET_FOR_HTC_DONE() == _FALSE))
            {
                ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _MHL_VERSION_1_2);

                ScalerMHLMscSendCommand(ucInputPort, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);

                SET_MHL_RX2_CBUS_RESET_FOR_HTC_DONE();
            }

#endif // End of #if(_D2_MHL_VERSION < _MHL_VERSION_3_0)

#if(_MHL_CBUS_CTS_MODE == _ON)

            if(ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT5) == _BIT5)
            {
                ScalerSetBit(P29_C8_CBUS_CTRL_28, ~_BIT6, _BIT6);

                ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT5);
            }

            if(ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT4) == _BIT4)
            {
                ScalerSetBit(P29_C8_CBUS_CTRL_28, ~_BIT6, 0x00);

                ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
            }

#endif // Enf of #if(_MHL_CBUS_CTS_MODE == _ON)

            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Set Devcap Registor Values
// Input Value  : Non
// Output Value : Non
//--------------------------------------------------
void ScalerMHLSetDevCapReg(void)
{
    // ---------------------- DEV CAP Reg Setting ------------------------- //

    // Modify Device Capabilities according to MHL Version
#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)
    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _D0_MHL_VERSION);
#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)
    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _D0_MHL_VERSION);
#endif

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _D1_MHL_VERSION);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _D1_MHL_VERSION);
#endif

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)
    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _D2_MHL_VERSION);
#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)
    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _D2_MHL_VERSION);
#endif

    // Set POWLIM DEVCAP Reg.
    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_DEV_CAT_02, 0x31);
    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_DEV_CAT_02, 0x31);

    // Adopter ID

    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_ADOPTER_ID_H_03, (BYTE)(((WORD)_MHL2_ADOPTER_ID >> 8) & 0x00FF));
    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_ADOPTER_ID_L_04, (BYTE)(_MHL2_ADOPTER_ID & 0x00FF));
    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_ADOPTER_ID_H_03, (BYTE)(((WORD)_MHL2_ADOPTER_ID >> 8) & 0x00FF));
    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_ADOPTER_ID_L_04, (BYTE)(_MHL2_ADOPTER_ID & 0x00FF));

    // Modify Packed Pixel Mode (2.0) and 16 Bits Mode (3.0) Support according to MHL Version
    ScalerSetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_VID_LINK_MODE_05, ~_BIT3, (BYTE)_MHL2_PP_MODE_SUPPORT << 3);

    ScalerSetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_VID_LINK_MODE_05, ~_BIT3, (BYTE)_MHL2_PP_MODE_SUPPORT << 3);

    // Modify Audio Link Mode and High-Bitrate Support according to MHL Version
    ScalerSetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_AUD_LINK_MODE_06, ~(_BIT1 | _BIT0), _MHL2_AUD_CHANNEL);
    ScalerSetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_AUD_LINK_MODE_06, ~(_BIT1 | _BIT0), _MHL2_AUD_CHANNEL);

    // Display Support
    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_LOG_DEV_MAP_08, 0x01);
    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_LOG_DEV_MAP_08, 0x01);

    // Modify RAP/RCP/UCP/RBP/XVYCC Support according to MHL Version
    ScalerSetDataPortBit(P28_AC_CBUS_CTRL_0C, _MSC_FEATURE_FLAG_0A, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (((BYTE)_MHL2_UCP_SUPPORT << 4) | (_MHL2_UCP_SUPPORT << 3) | (_BIT2 | _BIT1 | _BIT0)));

    ScalerSetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_FEATURE_FLAG_0A, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (((BYTE)_MHL2_UCP_SUPPORT << 4) | (_MHL2_UCP_SUPPORT << 3) | (_BIT2 | _BIT1 | _BIT0)));

    // Device ID
    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_DEVICE_ID_H_0B, (BYTE)(((WORD)_MHL2_DEVICE_ID >> 8) & 0x00FF));
    ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_DEVICE_ID_L_0C, (BYTE)(_MHL2_DEVICE_ID & 0x00FF));
    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_DEVICE_ID_H_0B, (BYTE)(((WORD)_MHL2_DEVICE_ID >> 8) & 0x00FF));
    ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_DEVICE_ID_L_0C, (BYTE)(_MHL2_DEVICE_ID & 0x00FF));
}

//--------------------------------------------------
// Description  : MSC Handler for D0 Port
// Input Value  : ucActivePort --> Current Active Port
//                ucModeState --> Current Mode State
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLMscHandler(BYTE ucInputPort, BYTE ucActivePort, BYTE ucModeState)
{
    bit bMHLActive = _FALSE;

    if(((ucInputPort == _D0_INPUT_PORT) && (ucActivePort == _D0_INPUT_PORT)) ||
       ((ucInputPort == _D1_INPUT_PORT) && (ucActivePort == _D1_INPUT_PORT)) ||
       ((ucInputPort == _D2_INPUT_PORT) && (ucActivePort == _D2_INPUT_PORT)))
    {
        bMHLActive = _TRUE;
    }

    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(0);
            break;

        case _D1_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(1);
            break;

        case _D2_INPUT_PORT:

            SET_MHL_PORT_ACTIVE(2);
            break;

        default:
            break;
    }

    // Check if Discovery State is done and send HPD & Device Capabilities Ready
    switch(GET_MHL_PROCESS_STATE(GET_MHL_PORT_ACTIVE()))
    {
        case _MHL_STATE_INITIAL:

            switch(ucInputPort)
            {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                case _D0_INPUT_PORT:
                    ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_MHL_RX0_RECONNECT_1K);
                    break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                case _D1_INPUT_PORT:
                    ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_MHL_RX1_RECONNECT_1K);
                    break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                case _D2_INPUT_PORT:
                    ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_MHL_RX2_RECONNECT_1K);
                    break;
#endif
                default:
                    break;
            }

            return _FALSE;
            break;

        case _MHL_STATE_DISCOVERY_DONE:

            switch(ucInputPort)
            {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                case _D0_INPUT_PORT:
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX0_RECONNECT_1K);
                    break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                case _D1_INPUT_PORT:
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX1_RECONNECT_1K);
                    break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                case _D2_INPUT_PORT:
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX2_RECONNECT_1K);
                    break;
#endif
                default:
                    break;
            }

            ScalerMHLSetDevCapReg();

            switch(ucInputPort)
            {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                case _D0_INPUT_PORT:
                    ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_MHL_RX0_SWITCH_PORT_DISCOVERY_DONE);
                    break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                case _D1_INPUT_PORT:
                    ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE);
                    break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                case _D2_INPUT_PORT:
                    ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_MHL_RX2_SWITCH_PORT_DISCOVERY_DONE);
                    break;
#endif
                default:
                    break;
            }

            DebugMessageMHL("1) MHL Discovery Done", GET_MHL_PORT_ACTIVE());
            SET_MHL_PROCESS_STATE(GET_MHL_PORT_ACTIVE(), _MHL_STATE_SET_DEV_CAP_DONE);

            break;

        default:
            break;
    }

    // Send HPD, PATH_EN and Device Capabilities Ready For Source
    if((bMHLActive == _TRUE) && (ucModeState != _MODE_STATUS_INITIAL) && (ucModeState != _MODE_STATUS_POWER_OFF))
    {
        switch(GET_MHL_PROCESS_STATE(GET_MHL_PORT_ACTIVE()))
        {
            case _MHL_STATE_SET_DEV_CAP_DONE:

                if(ScalerMHLMscSendCommand(ucInputPort, _MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY) == _SUCCESS)
                {
                    DebugMessageMHL("2) MHL Dev Cap RDY", 0x00);
                    SET_MHL_PROCESS_STATE(GET_MHL_PORT_ACTIVE(), _MHL_STATE_DEV_CAP_RDY);
                }

                return _TRUE;
                break;

            case _MHL_STATE_DEV_CAP_RDY:

                ScalerTimerDelayXms(150);

                if(ScalerMHLMscSendCommand(ucInputPort, _MSC_SET_HPD, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE) == _SUCCESS)
                {
                    DebugMessageMHL("3) MHL HPD Done", (0x40 | GET_MHL_PORT_ACTIVE()));
                    SET_MHL_PROCESS_STATE(GET_MHL_PORT_ACTIVE(), _MHL_STATE_HPD_DONE);
                }

                return _TRUE;
                break;

            case _MHL_STATE_HPD_DONE:

                switch(ucInputPort)
                {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    case _D0_INPUT_PORT:
                        if((GET_MHL_RX0_ADOPTER_ID_HBYTE() == _ZTE_NUBIA_Z5_ADOPTER_ID_HBYTE) &&
                           (GET_MHL_RX0_ADOPTER_ID_LBYTE() == _ZTE_NUBIA_Z5_ADOPTER_ID_LBYTE))
                        {
                            ScalerTimerDelayXms(50);
                        }
                        break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    case _D1_INPUT_PORT:
                        if((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _ZTE_NUBIA_Z5_ADOPTER_ID_HBYTE) &&
                           (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _ZTE_NUBIA_Z5_ADOPTER_ID_LBYTE))
                        {
                            ScalerTimerDelayXms(50);
                        }
                        break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    case _D2_INPUT_PORT:
                        if((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _ZTE_NUBIA_Z5_ADOPTER_ID_HBYTE) &&
                           (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _ZTE_NUBIA_Z5_ADOPTER_ID_LBYTE))
                        {
                            ScalerTimerDelayXms(50);
                        }
                        break;
#endif

                    default:
                        break;
                }

                if(ScalerMHLMscSendCommand(ucInputPort, _MSC_WRITE_STAT, _MSC_LINK_MODE, _MSC_PATH_EN) == _SUCCESS)
                {
                    DebugMessageMHL("4) MHL Path Enabled", 0x20 | GET_MHL_PORT_ACTIVE());
                    SET_MHL_PROCESS_STATE(GET_MHL_PORT_ACTIVE(), _MHL_STATE_PATH_EN_DONE);

                    switch(ucInputPort)
                    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                        case _D0_INPUT_PORT:
                            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX0_SWITCH_PORT_DISCOVERY_DONE);
                            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                        case _D1_INPUT_PORT:
                            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE);
                            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                        case _D2_INPUT_PORT:
                            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX2_SWITCH_PORT_DISCOVERY_DONE);
                            break;
#endif
                        default:
                            break;
                    }
                }


                return _TRUE;
                break;

            case _MHL_STATE_PATH_EN_DONE:

                if(GET_TMDS_PHY_SET() == _TRUE)
                {
                    DebugMessageMHL("5) MHL CBUS Done", GET_MHL_PORT_ACTIVE());
                    SET_MHL_PROCESS_STATE(GET_MHL_PORT_ACTIVE(), _MHL_STATE_DONE);
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
// Description  : RAP Process for D0 Port
// Input Value  : None
// Output Value : True or False (False if Content Off)
//--------------------------------------------------
bit ScalerMHLMscRAPHandler(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

            // Check RAP Command
            if((bit)ScalerGetBit(P28_D4_CBUS_CTRL_34, _BIT3) == _TRUE)
            {
                switch(ScalerGetByte(P28_DC_CBUS_CTRL_3C))
                {
                    case _MSC_RAP_POLL:
                    case _MSC_RAP_CONTENT_ON:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;

                    case _MSC_RAP_CONTENT_OFF:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _FALSE;
                        break;

                    default:

                        // Reply RAPK and Ineffective Code
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_UNRECOGNIZE_CODE);

                        // Clear Flag
                        ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;
                }
            }

#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

            // Check RAP Command
            if((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT3) == _TRUE)
            {
                switch(ScalerGetByte(P29_DC_CBUS_CTRL_3C))
                {
                    case _MSC_RAP_POLL:
                    case _MSC_RAP_CONTENT_ON:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;

                    case _MSC_RAP_CONTENT_OFF:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _FALSE;
                        break;

                    default:

                        // Reply RAPK and Ineffective Code
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_UNRECOGNIZE_CODE);

                        // Clear Flag
                        ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;
                }
            }
#endif // End of #if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

            return _TRUE;
            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

            // Check RAP Command
            if((bit)ScalerGetBit(P28_D4_CBUS_CTRL_34, _BIT3) == _TRUE)
            {
                switch(ScalerGetByte(P28_DC_CBUS_CTRL_3C))
                {
                    case _MSC_RAP_POLL:
                    case _MSC_RAP_CONTENT_ON:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;

                    case _MSC_RAP_CONTENT_OFF:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _FALSE;
                        break;

                    default:

                        // Reply RAPK and Ineffective Code
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_UNRECOGNIZE_CODE);

                        // Clear Flag
                        ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;
                }
            }

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

            // Check RAP Command
            if((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT3) == _TRUE)
            {
                switch(ScalerGetByte(P29_DC_CBUS_CTRL_3C))
                {
                    case _MSC_RAP_POLL:
                    case _MSC_RAP_CONTENT_ON:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;

                    case _MSC_RAP_CONTENT_OFF:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _FALSE;
                        break;

                    default:

                        // Reply RAPK and Ineffective Code
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_UNRECOGNIZE_CODE);

                        // Clear Flag
                        ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;
                }
            }
#endif // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

            return _TRUE;
            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

            // Check RAP Command
            if((bit)ScalerGetBit(P28_D4_CBUS_CTRL_34, _BIT3) == _TRUE)
            {
                switch(ScalerGetByte(P28_DC_CBUS_CTRL_3C))
                {
                    case _MSC_RAP_POLL:
                    case _MSC_RAP_CONTENT_ON:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;

                    case _MSC_RAP_CONTENT_OFF:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _FALSE;
                        break;

                    default:

                        // Reply RAPK and Ineffective Code
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_UNRECOGNIZE_CODE);

                        // Clear Flag
                        ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;
                }
            }

#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

            // Check RAP Command
            if((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT3) == _TRUE)
            {
                switch(ScalerGetByte(P29_DC_CBUS_CTRL_3C))
                {
                    case _MSC_RAP_POLL:
                    case _MSC_RAP_CONTENT_ON:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;

                    case _MSC_RAP_CONTENT_OFF:

                        // Reply RAPK and No Error
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);

                        // Clear Flag
                        ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _FALSE;
                        break;

                    default:

                        // Reply RAPK and Ineffective Code
                        ScalerMHLMscSendCommand(ucInputPort, _MSC_MSG, _MSC_RAPK, _MSC_RAPK_UNRECOGNIZE_CODE);

                        // Clear Flag
                        ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT3);

                        return _TRUE;
                        break;
                }
            }
#endif // End of #if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

            return _TRUE;
            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:

            return _TRUE;
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get RCP Key Code for D0 Port
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLMscRCPGetCommand(BYTE ucInputPort, BYTE *pucKeyCode)
{
    if(ucInputPort == _D0_INPUT_PORT)
    {
#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

        // Check RCP Command
        if((bit)ScalerGetBit(P28_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
        {
            // Clear Flag
            ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT6);

            pucKeyCode[0] = ScalerGetByte(P28_D9_CBUS_CTRL_39);

            return _TRUE;
        }
#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

        // Check RCP Command
        if((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
        {
            // Clear Flag
            ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT6);

            pucKeyCode[0] = ScalerGetByte(P29_D9_CBUS_CTRL_39);

            return _TRUE;
        }
#endif
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

        // Check RCP Command
        if((bit)ScalerGetBit(P28_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
        {
            // Clear Flag
            ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT6);

            pucKeyCode[0] = ScalerGetByte(P28_D9_CBUS_CTRL_39);

            return _TRUE;
        }

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

        // Check RCP Command
        if((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
        {
            // Clear Flag
            ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT6);

            pucKeyCode[0] = ScalerGetByte(P29_D9_CBUS_CTRL_39);

            return _TRUE;
        }
#endif
    }
    else if(ucInputPort == _D2_INPUT_PORT)
    {
#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

        // Check RCP Command
        if((bit)ScalerGetBit(P28_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
        {
            // Clear Flag
            ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT6);

            pucKeyCode[0] = ScalerGetByte(P28_D9_CBUS_CTRL_39);

            return _TRUE;
        }

#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

        // Check RCP Command
        if((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
        {
            // Clear Flag
            ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT6);

            pucKeyCode[0] = ScalerGetByte(P29_D9_CBUS_CTRL_39);

            return _TRUE;
        }
#endif
    }

    return _FALSE;
}

#if(_MHL_UCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get UCP Key Code for D0 Port
// Input Value  : UCP Key Code
// Output Value : True or False
//--------------------------------------------------
BYTE ScalerMHLMscUCPGetCommand(BYTE ucInputPort, BYTE *pucKeyCode)
{
    if(ucInputPort == _D0_INPUT_PORT)
    {
#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

        // Check UCP Command
        if((bit)ScalerGetBit(P28_12_OCBUS_CTRL_12, _BIT4) == _TRUE)
        {
            // Clear Flag
            ScalerSetBit(P28_12_OCBUS_CTRL_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

            pucKeyCode[0] = ScalerGetByte(P28_19_OCBUS_CTRL_19);

            return _TRUE;
        }
#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

        // Check RCP Command
        if((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
        {
            // Clear Flag
            ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT6);

            pucKeyCode[0] = ScalerGetByte(P29_D9_CBUS_CTRL_39);

            return _TRUE;
        }
#endif
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

        // Check UCP Command
        if((bit)ScalerGetBit(P28_12_OCBUS_CTRL_12, _BIT4) == _TRUE)
        {
            // Clear Flag
            ScalerSetBit(P28_12_OCBUS_CTRL_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

            pucKeyCode[0] = ScalerGetByte(P28_19_OCBUS_CTRL_19);

            return _TRUE;
        }
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

        // Check RCP Command
        if((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
        {
            // Clear Flag
            ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT6);

            pucKeyCode[0] = ScalerGetByte(P29_D9_CBUS_CTRL_39);

            return _TRUE;
        }
#endif
    }
    else if(ucInputPort == _D2_INPUT_PORT)
    {
#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

        // Check UCP Command
        if((bit)ScalerGetBit(P28_12_OCBUS_CTRL_12, _BIT4) == _TRUE)
        {
            // Clear Flag
            ScalerSetBit(P28_12_OCBUS_CTRL_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

            pucKeyCode[0] = ScalerGetByte(P28_19_OCBUS_CTRL_19);

            return _TRUE;
        }
#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

        // Check RCP Command
        if((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
        {
            // Clear Flag
            ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT6);

            pucKeyCode[0] = ScalerGetByte(P29_D9_CBUS_CTRL_39);

            return _TRUE;
        }
#endif
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
bit ScalerMHLPSPreDetect(BYTE ucInputPort)
{
    //---------------------------------------//
    //-------- Check RAP Content OFF --------//
    //---------------------------------------//
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)
            if(ScalerGetByte(P28_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }

#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

            if(ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }
#endif
            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

            if(ScalerGetByte(P28_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

            if(ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }
#endif
            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

            if(ScalerGetByte(P28_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }

#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

            if(ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }
#endif
            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }


    //------------------------------------------------------------//
    //-------- PSM --> PNM While Wake Up Pulses Received ---------//
    //------------------------------------------------------------//
    if(((ucInputPort == _D0_INPUT_PORT) && (_D0_CBUS_CHANNEL_SEL == _CBUS0)) ||
       ((ucInputPort == _D1_INPUT_PORT) && (_D1_CBUS_CHANNEL_SEL == _CBUS0)) ||
       ((ucInputPort == _D2_INPUT_PORT) && (_D2_CBUS_CHANNEL_SEL == _CBUS0)))
    {
        if(ScalerGetBit(P28_A0_CBUS_CTRL_00, (_BIT5 | _BIT3)) == (_BIT5 | _BIT3))
        {
            return _TRUE;
        }
    }
    else if(((ucInputPort == _D0_INPUT_PORT) && (_D0_CBUS_CHANNEL_SEL == _CBUS1)) ||
            ((ucInputPort == _D1_INPUT_PORT) && (_D1_CBUS_CHANNEL_SEL == _CBUS1)) ||
            ((ucInputPort == _D2_INPUT_PORT) && (_D2_CBUS_CHANNEL_SEL == _CBUS1)))
    {
        if(ScalerGetBit(P29_A0_CBUS_CTRL_00, (_BIT5 | _BIT3)) == (_BIT5 | _BIT3))
        {
            return _TRUE;
        }
    }


    //------------------------------------------------------------//
    //------- Pre-Detect True By Switch Back to MHL Port ---------//
    //------------------------------------------------------------//
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            if(GET_MHL_SWITCH_PORT_DISCOVERY_DONE(0) == _TRUE)
            {
                SET_MHL_SWITCH_PORT_DISCOVERY_DONE(0, _FALSE);
                return _TRUE;
            }

            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            if(GET_MHL_SWITCH_PORT_DISCOVERY_DONE(1) == _TRUE)
            {
                SET_MHL_SWITCH_PORT_DISCOVERY_DONE(1, _FALSE);
                return _TRUE;
            }

            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            if(GET_MHL_SWITCH_PORT_DISCOVERY_DONE(2) == _TRUE)
            {
                SET_MHL_SWITCH_PORT_DISCOVERY_DONE(2, _FALSE);
                return _TRUE;
            }

            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }

    //------------------------------------------------------------//
    //-------- Pre-Detect True By MHL Clk Measure Stable ---------//
    //------------------------------------------------------------//

    // Reset Freq. Detect Counter(Toggle) & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear Freq. Stable Flag
    ScalerSetBit(P2_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear Unstable Flag
    ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 5 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P2_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P2_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P2_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
    }

    switch(GET_MHL_PROCESS_STATE(GET_MHL_PORT_ACTIVE()))
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
bit ScalerMHLNormalPreDetect(BYTE ucInputPort)
{
    //---------------------------------------//
    //-------- Check RAP Content OFF --------//
    //---------------------------------------//
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

            if(ScalerGetByte(P28_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }

#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

            if(ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }
#endif
            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

            if(ScalerGetByte(P28_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

            if(ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }
#endif
            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

            if(ScalerGetByte(P28_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }

#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

            if(ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
            {
                return _FAIL;
            }
#endif
            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }


    //------------------------------------------------------------//
    //------- Pre-Detect True By Switch Back to MHL Port ---------//
    //------------------------------------------------------------//
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            if(GET_MHL_SWITCH_PORT_DISCOVERY_DONE(0) == _TRUE)
            {
                SET_MHL_SWITCH_PORT_DISCOVERY_DONE(0, _FALSE);
                return _TRUE;
            }

            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            if(GET_MHL_SWITCH_PORT_DISCOVERY_DONE(1) == _TRUE)
            {
                SET_MHL_SWITCH_PORT_DISCOVERY_DONE(1, _FALSE);
                return _TRUE;
            }

            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            if(GET_MHL_SWITCH_PORT_DISCOVERY_DONE(2) == _TRUE)
            {
                SET_MHL_SWITCH_PORT_DISCOVERY_DONE(2, _FALSE);
                return _TRUE;
            }

            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }

    ScalerTimerDelayXms(6);

    if(GET_TMDS_PHY_SET() == _TRUE)
    {
        return _SUCCESS;
    }

    switch(GET_MHL_PROCESS_STATE(GET_MHL_PORT_ACTIVE()))
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


//--------------------------------------------------
// Description  : Handle MHL Related Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerMHLTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX0_READY_TO_TRANSMIT:

            SET_MHL_READY_TO_TRANSMIT(0, _TRUE);

            break;

        case _SCALER_TIMER_EVENT_MHL_RX0_RECONNECT_1K:

#if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

            if((((ScalerGetByte(P28_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x01) ||
               (((ScalerGetByte(P28_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x02))
            {
                ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                ScalerTimerDelayXms(52);
                ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);
            }

#elif(_D0_CBUS_CHANNEL_SEL == _CBUS1)

            if((((ScalerGetByte(P29_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x01) ||
               (((ScalerGetByte(P29_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x02))
            {
                ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                ScalerTimerDelayXms(52);
                ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);
            }

#endif // End of #if(_D0_CBUS_CHANNEL_SEL == _CBUS0)

            break;

        case _SCALER_TIMER_EVENT_MHL_RX0_SWITCH_PORT_DISCOVERY_DONE:

            SET_MHL_SWITCH_PORT_DISCOVERY_DONE(0, _TRUE);

            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT:

            SET_MHL_READY_TO_TRANSMIT(1, _TRUE);

            break;

        case _SCALER_TIMER_EVENT_MHL_RX1_RECONNECT_1K:

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

            if((((ScalerGetByte(P28_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x01) ||
               (((ScalerGetByte(P28_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x02))
            {
                ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                ScalerTimerDelayXms(52);
                ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);
            }

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)

            if((((ScalerGetByte(P29_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x01) ||
               (((ScalerGetByte(P29_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x02))
            {
                ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                ScalerTimerDelayXms(52);
                ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);
            }

#endif // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

            break;

        case _SCALER_TIMER_EVENT_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE:

            SET_MHL_SWITCH_PORT_DISCOVERY_DONE(1, _TRUE);

            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX2_READY_TO_TRANSMIT:

            SET_MHL_READY_TO_TRANSMIT(2, _TRUE);

            break;

        case _SCALER_TIMER_EVENT_MHL_RX2_RECONNECT_1K:

#if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

            if((((ScalerGetByte(P28_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x01) ||
               (((ScalerGetByte(P28_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x02))
            {
                ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                ScalerTimerDelayXms(52);
                ScalerSetBit(P28_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);
            }

#elif(_D2_CBUS_CHANNEL_SEL == _CBUS1)

            if((((ScalerGetByte(P29_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x01) ||
               (((ScalerGetByte(P29_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x02))
            {
                ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                ScalerTimerDelayXms(52);
                ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);
            }

#endif // End of #if(_D2_CBUS_CHANNEL_SEL == _CBUS0)

            break;

        case _SCALER_TIMER_EVENT_MHL_RX2_SWITCH_PORT_DISCOVERY_DONE:

            SET_MHL_SWITCH_PORT_DISCOVERY_DONE(2, _TRUE);

            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        default:
            break;
    }
}

#endif  // End of #if(_MHL_SUPPORT == _ON)


