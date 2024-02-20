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
// ID Code      : RL6492_Series_MHLRx2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_MHLRX2__

#include "ScalerFunctionInclude.h"

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX2_ADOPTER_ID_DONE()            (g_bMHLRx2AdopterIDDone)
#define SET_MHL_RX2_ADOPTER_ID_DONE()            (g_bMHLRx2AdopterIDDone = _TRUE)
#define CLR_MHL_RX2_ADOPTER_ID_DONE()            (g_bMHLRx2AdopterIDDone = _FALSE)

#define GET_MHL_RX2_CBUS_RESET_FOR_HTC_DONE()    (g_bMHLRx2CbusResetForHTCDone)
#define SET_MHL_RX2_CBUS_RESET_FOR_HTC_DONE()    (g_bMHLRx2CbusResetForHTCDone = _TRUE)
#define CLR_MHL_RX2_CBUS_RESET_FOR_HTC_DONE()    (g_bMHLRx2CbusResetForHTCDone = _FALSE)

#define GET_MHL_RX2_SENT_MSC_DCAP_RDY()          (g_bMHLRx2SentMscDcapRdy)
#define SET_MHL_RX2_SENT_MSC_DCAP_RDY()          (g_bMHLRx2SentMscDcapRdy = _TRUE)
#define CLR_MHL_RX2_SENT_MSC_DCAP_RDY()          (g_bMHLRx2SentMscDcapRdy = _FALSE)

#define GET_MHL_RX2_MHL_VERSION()                (g_ucMHLRx2MhlVersion)
#define SET_MHL_RX2_MHL_VERSION(x)               (g_ucMHLRx2MhlVersion = (x))
#define CLR_MHL_RX2_MHL_VERSION()                (g_ucMHLRx2MhlVersion = 0x00)

#define GET_MHL_RX2_WRITE_BURST_PROCESS_DONE()   (g_bMHLRx2WriteBurstProcessDone)
#define SET_MHL_RX2_WRITE_BURST_PROCESS_DONE()   (g_bMHLRx2WriteBurstProcessDone = _TRUE)
#define CLR_MHL_RX2_WRITE_BURST_PROCESS_DONE()   (g_bMHLRx2WriteBurstProcessDone = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucMHLRx2AdopterIDH = 0xFF;
BYTE g_ucMHLRx2AdopterIDL = 0xFF;
bit g_bMHLRx2AdopterIDDone = _FALSE;
bit g_bMHLRx2CbusResetForHTCDone = _FALSE;
bit g_bMHLRx2SentMscDcapRdy = _TRUE;
StructMHLProcessInfo g_stMHLRx2Process;
BYTE g_ucMHLRx2MhlVersion;
bit g_bMHLRx2WriteBurstProcessDone = _TRUE;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMHLRx2ModeMHLSetting(void);
void ScalerMHLRx2ModeHdmiSetting(void);
void ScalerMHLRx2InitialSettings(void);
void ScalerMHLRx2CBUSPhySwitch(bit bSelect);
void ScalerMHLRx2CBUSSwitchClk(EnumClkSel enumClockSel);
void ScalerMHLRx2CBUSResetProc(void);
void ScalerMHLRx2PowerOffProc(void);
bit ScalerMHLRx2DetectClkMode(void);
BYTE ScalerMHLRx2DetectClkMode_EXINT0(void);
void ScalerMHLRx2IntHandler_EXINT0(void);
bit ScalerMHLRx2MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
bit ScalerMHLRx2MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);
bit ScalerMHLRx2MscReadDevCapabilities(EnumMHLMscOffset enumMSCOffset, BYTE *pucData, BYTE ucExtended);
BYTE ScalerMHLRx2MscFIFOSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData);
void ScalerMHLRx2MscCheckDeviceINT(void);

bit ScalerMHLRx2MscHandler(BYTE ucActivePort, BYTE ucModeState);
bit ScalerMHLRx2MscRAPHandler(void);

#if(_MHL_UCP_SUPPORT == _ON)
BYTE ScalerMHLRx2MscUCPGetCommand(BYTE *pucKeyCode);
#endif

bit ScalerMHLRx2PSPreDetect(void);
bit ScalerMHLRx2NormalPreDetect(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : TMDS Settings when MHL Mode for D2 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx2ModeMHLSetting(void)
{
}

//--------------------------------------------------
// Description  : TMDS Settings when HDMI Mode for D2 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx2ModeHdmiSetting(void)
{
}

//--------------------------------------------------
// Description  : Calibration for 1K/100K and LDO Level Adjust
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx2InitialSettings(void)
{
}

//--------------------------------------------------
// Description  : Power Process for CBUS Phy for D2 Port
// Input Value  : bSelect --> _ON/_OFF
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx2CBUSPhySwitch(bit bSelect)
{
    bSelect = bSelect;
}

//--------------------------------------------------
// Description  : Clock Select For MHL for D2 Port
// Input Value  : ucClockSel --> System refernce clock select.
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx2CBUSSwitchClk(EnumClkSel enumClockSel)
{
    enumClockSel = enumClockSel;
}

//--------------------------------------------------
// Description  : MHL Cbus Reset Proc for D2 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx2CBUSResetProc(void)
{
}

//--------------------------------------------------
// Description  : MHL Power Off Process for D2 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx2PowerOffProc(void)
{
}

//--------------------------------------------------
// Description  : MHL Detect Clk Mode if 24Bit or PP Mode
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx2DetectClkMode(void)
{
    return 0;
}

//--------------------------------------------------
// Description  : MHL Detect Clk Mode if 24Bit or PP Mode (EXINT0 Only)
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
BYTE ScalerMHLRx2DetectClkMode_EXINT0(void) using 1
{
    return 0;
}

//--------------------------------------------------
// Description  : Int Process for MHL for D2 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx2IntHandler_EXINT0(void) using 1
{
}

//--------------------------------------------------
// Description  : Send MSC HPD Operation for D2 Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Fail
//--------------------------------------------------
bit ScalerMHLRx2MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue)
{
    enumMSCCommand = enumMSCCommand;
    enumMSCOffset = enumMSCOffset;
    enumMSCValue = enumMSCValue;
    return 0;
}

//--------------------------------------------------
// Description  : Send Write Burst Operation for D2 Port
// Input Value  : ucDataLength --> Data Length
//                pucData --> Data
//                ucMode --> Write Burst Mode
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
bit ScalerMHLRx2MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode)
{
    ucOffset = ucOffset;
    ucDataLength = ucDataLength;
    pucData = pucData;
    enumMode = enumMode;
    return 0;
}

//--------------------------------------------------
// Description  : Read Device Capabilities for D2 Port
// Input Value  : enumMSCOffset --> Device Capability Offset
//                pucData --> Data to be Read
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
bit ScalerMHLRx2MscReadDevCapabilities(EnumMHLMscOffset enumMSCOffset, BYTE *pucData, BYTE ucExtended)
{
    enumMSCOffset = enumMSCOffset;
    pucData = pucData;
    ucExtended = ucExtended;
    return 0;
}

//--------------------------------------------------
// Description  : Send MSC HPD Operation for D2 Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
BYTE ScalerMHLRx2MscFIFOSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData)
{
    enumMSCCommand = enumMSCCommand;
    enumMSCOffset = enumMSCOffset;
    enumMSCValue = enumMSCValue;
    ucDataLength = ucDataLength;
    pucData = pucData;
    return 0;
}

//--------------------------------------------------
// Description  : Check Write Status for D2 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx2MscCheckDeviceINT(void)
{
}

//--------------------------------------------------
// Description  : MSC Handler for D2 Port
// Input Value  : ucActivePort --> Current Active Port
//                ucModeState --> Current Mode State
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx2MscHandler(BYTE ucActivePort, BYTE ucModeState)
{
    ucActivePort = ucActivePort;
    ucModeState = ucModeState;
    return 0;
}

//--------------------------------------------------
// Description  : RAP Process for D2 Port
// Input Value  : None
// Output Value : True or False (False if Content Off)
//--------------------------------------------------
bit ScalerMHLRx2MscRAPHandler(void)
{
    return 0;
}

#if(_MHL_UCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get UCP Key Code for D2 Port
// Input Value  : UCP Key Code
// Output Value : True or False
//--------------------------------------------------
BYTE ScalerMHLRx2MscUCPGetCommand(BYTE *pucKeyCode)
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
bit ScalerMHLRx2PSPreDetect(void)
{
    return 0;
}

//--------------------------------------------------
// Description  : Signal PreDetection for MHL(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerMHLRx2NormalPreDetect(void)
{
    return 0;
}
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

