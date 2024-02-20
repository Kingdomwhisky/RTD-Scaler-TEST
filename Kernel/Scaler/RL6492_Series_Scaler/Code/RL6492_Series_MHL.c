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
// ID Code      : RL6492_Series_MHL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6492_SERIES_MHL__

#include "ScalerFunctionInclude.h"

#if(_MHL_SUPPORT == _ON)

#if(_MHL_CBUS_CTS_MODE == _ON)
#warning "MHL CBUS CTS Mode is Enabled!! Only Used for CTS!!!"
#endif

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
void ScalerMHLModeMHLSetting(BYTE ucInputPort);
void ScalerMHLModeHdmiSetting(BYTE ucInputPort);
void ScalerMHLInitialSettings(void);
void ScalerMHLCBUSPhySwitch(BYTE ucPortSelect, bit bSelect);
void ScalerMHLCBUSSwitchClk(EnumClkSel enumClockSel);
void ScalerMHLCBUSResetProc(BYTE ucInputPort);
void ScalerMHLPowerOffProc(BYTE ucInputPort);
bit ScalerMHLMscSendCommand(BYTE ucInputPort, EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
void ScalerMHLMscCheckDeviceINT(BYTE ucInputPort);

void ScalerMHLIntHandler_EXINT0(void);
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
// Description  : TMDS Settings when MHL Mode for Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLModeMHLSetting(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
}


//--------------------------------------------------
// Description  : TMDS Settings when HDMI Mode for Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLModeHdmiSetting(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
}


//--------------------------------------------------
// Description  : Calibration for 1K/100K and LDO Level Adjust
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLInitialSettings(void)
{
}


//--------------------------------------------------
// Description  : Power Process for CBUS Phy for Port
// Input Value  : bSelect --> _ON/_OFF
// Output Value : None
//--------------------------------------------------
void ScalerMHLCBUSPhySwitch(BYTE ucPortSelect, bit bSelect)
{
    ucPortSelect = ucPortSelect;
    bSelect = bSelect;
}


//--------------------------------------------------
// Description  : Clock Select For MHL for Port
// Input Value  : ucClockSel --> System refernce clock select.
// Output Value : None
//--------------------------------------------------
void ScalerMHLCBUSSwitchClk(EnumClkSel enumClockSel)
{
    enumClockSel = enumClockSel;
}

//--------------------------------------------------
// Description  : MHL Cbus Reset Proc for Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLCBUSResetProc(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
}


//--------------------------------------------------
// Description  : MHL Power Off Process for Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLPowerOffProc(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
}


//--------------------------------------------------
// Description  : Send MSC HPD Operation for Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Fail
//--------------------------------------------------
bit ScalerMHLMscSendCommand(BYTE ucInputPort, EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue)
{
    ucInputPort = ucInputPort;
    enumMSCCommand = enumMSCCommand;
    enumMSCOffset = enumMSCOffset;
    enumMSCValue = enumMSCValue;
    return 0;
}



//--------------------------------------------------
// Description  : Check Write Status for Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLMscCheckDeviceINT(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLIntHandler_EXINT0(void) using 1
{
}


//--------------------------------------------------
// Description  : MSC Handler for Port
// Input Value  : ucActivePort --> Current Active Port
//                ucModeState --> Current Mode State
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLMscHandler(BYTE ucInputPort, BYTE ucActivePort, BYTE ucModeState)
{
    ucInputPort = ucInputPort;
    ucActivePort = ucActivePort;
    ucModeState = ucModeState;
    return 0;
}


//--------------------------------------------------
// Description  : RAP Process for Port
// Input Value  : None
// Output Value : True or False (False if Content Off)
//--------------------------------------------------
bit ScalerMHLMscRAPHandler(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
    return 0;
}


//--------------------------------------------------
// Description  : Get RCP Key Code for Port
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLMscRCPGetCommand(BYTE ucInputPort, BYTE *pucKeyCode)
{
    ucInputPort = ucInputPort;
    pucKeyCode = pucKeyCode;
    return 0;
}


#if(_MHL_UCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get UCP Key Code for Port
// Input Value  : UCP Key Code
// Output Value : True or False
//--------------------------------------------------
BYTE ScalerMHLMscUCPGetCommand(BYTE ucInputPort, BYTE *pucKeyCode)
{
    ucInputPort = ucInputPort;
    pucKeyCode = pucKeyCode;
    return 0;
}
#endif  // End of #if(_MHL_UCP_SUPPORT == _ON)


//--------------------------------------------------
// Description  : Signal PreDetection for MHL(Power Saving)
// Input Value  : Input Port(HDMI or DVI)
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerMHLPSPreDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
    return 0;
}


//--------------------------------------------------
// Description  : Signal PreDetection for MHL(Power Normal)
// Input Value  : Input Port(HDMI or DVI)
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerMHLNormalPreDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
    return 0;
}


//--------------------------------------------------
// Description  : Handle MHL ports Related Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerMHLTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    enumEventID = enumEventID;
}

#endif // End of #if(_MHL_SUPPORT == _ON)
