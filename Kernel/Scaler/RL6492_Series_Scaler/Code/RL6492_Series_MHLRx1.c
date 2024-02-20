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
// ID Code      : RL6492_Series_MHLRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_MHLRX1__

#include "ScalerFunctionInclude.h"

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX1_ADOPTER_ID_DONE()            (g_bMHLRx1AdopterIDDone)
#define SET_MHL_RX1_ADOPTER_ID_DONE()            (g_bMHLRx1AdopterIDDone = _TRUE)
#define CLR_MHL_RX1_ADOPTER_ID_DONE()            (g_bMHLRx1AdopterIDDone = _FALSE)

#define GET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE()    (g_bMHLRx1CbusResetForHTCDone)
#define SET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE()    (g_bMHLRx1CbusResetForHTCDone = _TRUE)
#define CLR_MHL_RX1_CBUS_RESET_FOR_HTC_DONE()    (g_bMHLRx1CbusResetForHTCDone = _FALSE)

#define GET_MHL_RX1_SENT_MSC_DCAP_RDY()          (g_bMHLRx1SentMscDcapRdy)
#define SET_MHL_RX1_SENT_MSC_DCAP_RDY()          (g_bMHLRx1SentMscDcapRdy = _TRUE)
#define CLR_MHL_RX1_SENT_MSC_DCAP_RDY()          (g_bMHLRx1SentMscDcapRdy = _FALSE)

#define GET_MHL_RX1_MHL_VERSION()                (g_ucMHLRx1MhlVersion)
#define SET_MHL_RX1_MHL_VERSION(x)               (g_ucMHLRx1MhlVersion = (x))
#define CLR_MHL_RX1_MHL_VERSION()                (g_ucMHLRx1MhlVersion = 0x00)

#define GET_MHL_RX1_WRITE_BURST_PROCESS_DONE()   (g_bMHLRx1WriteBurstProcessDone)
#define SET_MHL_RX1_WRITE_BURST_PROCESS_DONE()   (g_bMHLRx1WriteBurstProcessDone = _TRUE)
#define CLR_MHL_RX1_WRITE_BURST_PROCESS_DONE()   (g_bMHLRx1WriteBurstProcessDone = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucMHLRx1AdopterIDH = 0xFF;
BYTE g_ucMHLRx1AdopterIDL = 0xFF;
bit g_bMHLRx1AdopterIDDone = _FALSE;
bit g_bMHLRx1CbusResetForHTCDone = _FALSE;
bit g_bMHLRx1SentMscDcapRdy = _TRUE;
StructMHLProcessInfo g_stMHLRx1Process;
BYTE g_ucMHLRx1MhlVersion;
bit g_bMHLRx1WriteBurstProcessDone = _TRUE;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMHLRx1ModeMHLSetting(void);
void ScalerMHLRx1ModeHdmiSetting(void);
void ScalerMHLRx1InitialSettings(void);
void ScalerMHLRx1CBUSPhySwitch(bit bSelect);
void ScalerMHLRx1CBUSSwitchClk(EnumClkSel enumClockSel);
void ScalerMHLRx1SetTimingRelateSetting(void);
void ScalerMHLRx1CBUSResetProc(void);
void ScalerMHLRx1DataPortInitial(void);
void ScalerMHLRx1DataPortInitial_EXINT0(void);
void ScalerMHLRx1PowerOffProc(void);
bit ScalerMHLRx1DetectClkMode(void);
BYTE ScalerMHLRx1DetectClkMode_EXINT0(void);
void ScalerMHLRx1IntHandler_EXINT0(void);
bit ScalerMHLRx1MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
bit ScalerMHLRx1MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);
bit ScalerMHLRx1MscReadDevCapabilities(EnumMHLMscOffset enumMSCOffset, BYTE *pucData, BYTE ucExtended);
BYTE ScalerMHLRx1MscFIFOSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData);
void ScalerMHLRx1MscCheckDeviceINT(void);

void ScalerMHLRx1SetDevCapReg(void);
bit ScalerMHLRx1MscHandler(BYTE ucActivePort, BYTE ucModeState);
bit ScalerMHLRx1MscRAPHandler(void);
bit ScalerMHLRx1MscRCPGetCommand(BYTE *pucKeyCode);

#if(_MHL_UCP_SUPPORT == _ON)
BYTE ScalerMHLRx1MscUCPGetCommand(BYTE *pucKeyCode);
#endif

bit ScalerMHLRx1PSPreDetect(void);
bit ScalerMHLRx1NormalPreDetect(void);
void ScalerMHLRx1TimerEventProc(EnumScalerTimerEventID enumEventID);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : TMDS Settings when MHL Mode for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1ModeMHLSetting(void)
{
}

//--------------------------------------------------
// Description  : TMDS Settings when HDMI Mode for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1ModeHdmiSetting(void)
{
}

//--------------------------------------------------
// Description  : Calibration for 1K/100K and LDO Level Adjust
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1InitialSettings(void)
{
}

//--------------------------------------------------
// Description  : Power Process for CBUS Phy for D1 Port
// Input Value  : bSelect --> _ON/_OFF
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1CBUSPhySwitch(bit bSelect)
{
    bSelect = bSelect;
}

//--------------------------------------------------
// Description  : Clock Select For MHL for D1 Port
// Input Value  : ucClockSel --> System refernce clock select.
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1CBUSSwitchClk(EnumClkSel enumClockSel)
{
    enumClockSel = enumClockSel;
}

//--------------------------------------------------
// Description  : Set Devcap Registor Values
// Input Value  : Non
// Output Value : Non
//--------------------------------------------------
void ScalerMHLRx1SetTimingRelateSetting(void)
{
}

//--------------------------------------------------
// Description  : MHL Cbus Reset Proc for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1CBUSResetProc(void)
{
}

//--------------------------------------------------
// Description  : MHL Cbus Mac Data Port Reset Proc for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1DataPortInitial(void)
{
}

//--------------------------------------------------
// Description  : MHL Cbus Mac Data Port Reset Proc for D1 Port (For Interrupt)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1DataPortInitial_EXINT0(void) using 1
{
}

//--------------------------------------------------
// Description  : MHL Power Off Process for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1PowerOffProc(void)
{
}

//--------------------------------------------------
// Description  : MHL Detect Clk Mode if 24Bit or PP Mode
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx1DetectClkMode(void)
{
    return 0;
}

//--------------------------------------------------
// Description  : MHL Detect Clk Mode if 24Bit or PP Mode (EXINT0 Only)
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
BYTE ScalerMHLRx1DetectClkMode_EXINT0(void) using 1
{
    return 0;
}

//--------------------------------------------------
// Description  : Int Process for MHL for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1IntHandler_EXINT0(void) using 1
{
}

//--------------------------------------------------
// Description  : Send MSC HPD Operation for D1 Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Fail
//--------------------------------------------------
bit ScalerMHLRx1MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue)
{
    enumMSCCommand = enumMSCCommand;
    enumMSCOffset = enumMSCOffset;
    enumMSCValue = enumMSCValue;
    return 0;
}

//--------------------------------------------------
// Description  : Send Write Burst Operation for D1 Port
// Input Value  : ucDataLength --> Data Length
//                pucData --> Data
//                ucMode --> Write Burst Mode
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
bit ScalerMHLRx1MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode)
{
    ucOffset = ucOffset;
    ucDataLength = ucDataLength;
    pucData = pucData;
    enumMode = enumMode;
    return 0;
}

//--------------------------------------------------
// Description  : Read Device Capabilities for D1 Port
// Input Value  : enumMSCOffset --> Device Capability Offset
//                pucData --> Data to be Read
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
bit ScalerMHLRx1MscReadDevCapabilities(EnumMHLMscOffset enumMSCOffset, BYTE *pucData, BYTE ucExtended)
{
    enumMSCOffset = enumMSCOffset;
    pucData = pucData;
    ucExtended = ucExtended;
    return 0;
}

//--------------------------------------------------
// Description  : Send MSC HPD Operation for D1 Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
BYTE ScalerMHLRx1MscFIFOSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData)
{
    enumMSCCommand = enumMSCCommand;
    enumMSCOffset = enumMSCOffset;
    enumMSCValue = enumMSCValue;
    ucDataLength = ucDataLength;
    pucData = pucData;
    return 0;
}

//--------------------------------------------------
// Description  : Check Write Status for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1MscCheckDeviceINT(void)
{
}

//--------------------------------------------------
// Description  : Set Devcap Registor Values
// Input Value  : Non
// Output Value : Non
//--------------------------------------------------
void ScalerMHLRx1SetDevCapReg(void)
{
}

//--------------------------------------------------
// Description  : MSC Handler for D1 Port
// Input Value  : ucActivePort --> Current Active Port
//                ucModeState --> Current Mode State
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx1MscHandler(BYTE ucActivePort, BYTE ucModeState)
{
    ucActivePort = ucActivePort;
    ucModeState = ucModeState;
    return 0;
}

//--------------------------------------------------
// Description  : RAP Process for D1 Port
// Input Value  : None
// Output Value : True or False (False if Content Off)
//--------------------------------------------------
bit ScalerMHLRx1MscRAPHandler(void)
{
    return 0;
}

//--------------------------------------------------
// Description  : Get RCP Key Code for D1 Port
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx1MscRCPGetCommand(BYTE *pucKeyCode)
{
    pucKeyCode = pucKeyCode;
    return 0;
}

#if(_MHL_UCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get UCP Key Code for D1 Port
// Input Value  : UCP Key Code
// Output Value : True or False
//--------------------------------------------------
BYTE ScalerMHLRx1MscUCPGetCommand(BYTE *pucKeyCode)
{
    pucKeyCode = pucKeyCode;
    return 0;
}
#endif  // End of #if(_MHL_UCP_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Signal PreDetection for MHL(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerMHLRx1PSPreDetect(void)
{
    return 0;
}

//--------------------------------------------------
// Description  : Signal PreDetection for MHL(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerMHLRx1NormalPreDetect(void)
{
    return 0;
}


//--------------------------------------------------
// Description  : Handle MHL Rx1 Related Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1TimerEventProc(EnumScalerTimerEventID enumEventID)
{
    enumEventID = enumEventID;
}

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

