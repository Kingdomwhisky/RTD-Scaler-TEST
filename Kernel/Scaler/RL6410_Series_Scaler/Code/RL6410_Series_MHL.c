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
// ID Code      : RL6410_Series_MHL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6410_SERIES_MHL__

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
void ScalerMHLIntHandler_EXINT0(void);
bit ScalerMHLMscSendCommand(BYTE ucInputPort, EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
void ScalerMHLMscCheckDeviceINT(BYTE ucInputPort);
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
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            ScalerMHLRx0ModeMHLSetting();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            ScalerMHLRx1ModeMHLSetting();

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            ScalerMHLRx2ModeMHLSetting();

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            ScalerMHLRx3ModeMHLSetting();

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            ScalerMHLRx4ModeMHLSetting();

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            ScalerMHLRx5ModeMHLSetting();

            break;
#endif

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : TMDS Settings when HDMI Mode for Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLModeHdmiSetting(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            ScalerMHLRx0ModeHdmiSetting();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            ScalerMHLRx1ModeHdmiSetting();

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            ScalerMHLRx2ModeHdmiSetting();

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            ScalerMHLRx3ModeHdmiSetting();

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            ScalerMHLRx4ModeHdmiSetting();

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            ScalerMHLRx5ModeHdmiSetting();

            break;
#endif

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
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
    ScalerMHLRx0InitialSettings();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    ScalerMHLRx1InitialSettings();
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    ScalerMHLRx2InitialSettings();
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
    ScalerMHLRx3InitialSettings();
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    ScalerMHLRx4InitialSettings();
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    ScalerMHLRx5InitialSettings();
#endif
}


//--------------------------------------------------
// Description  : Power Process for CBUS Phy for Port
// Input Value  : bSelect --> _ON/_OFF
// Output Value : None
//--------------------------------------------------
void ScalerMHLCBUSPhySwitch(BYTE ucPortSelect, bit bSelect)
{
    switch(ucPortSelect)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            ScalerMHLRx0CBUSPhySwitch(bSelect);

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            ScalerMHLRx1CBUSPhySwitch(bSelect);

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            ScalerMHLRx2CBUSPhySwitch(bSelect);

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            ScalerMHLRx3CBUSPhySwitch(bSelect);

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            ScalerMHLRx4CBUSPhySwitch(bSelect);

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            ScalerMHLRx5CBUSPhySwitch(bSelect);

            break;
#endif

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : Clock Select For MHL for Port
// Input Value  : ucClockSel --> System refernce clock select.
// Output Value : None
//--------------------------------------------------
void ScalerMHLCBUSSwitchClk(EnumClkSel enumClockSel)
{
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
    ScalerMHLRx0CBUSSwitchClk(enumClockSel);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    ScalerMHLRx1CBUSSwitchClk(enumClockSel);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    ScalerMHLRx2CBUSSwitchClk(enumClockSel);
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
    ScalerMHLRx3CBUSSwitchClk(enumClockSel);
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    ScalerMHLRx4CBUSSwitchClk(enumClockSel);
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    ScalerMHLRx5CBUSSwitchClk(enumClockSel);
#endif
}

//--------------------------------------------------
// Description  : MHL Cbus Reset Proc for Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLCBUSResetProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            ScalerMHLRx0CBUSResetProc();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            ScalerMHLRx1CBUSResetProc();

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            ScalerMHLRx2CBUSResetProc();

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            ScalerMHLRx3CBUSResetProc();

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            ScalerMHLRx4CBUSResetProc();

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            ScalerMHLRx5CBUSResetProc();

            break;
#endif

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : MHL Power Off Process for Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLPowerOffProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            ScalerMHLRx0PowerOffProc();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            ScalerMHLRx1PowerOffProc();

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            ScalerMHLRx2PowerOffProc();

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            ScalerMHLRx3PowerOffProc();

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            ScalerMHLRx4PowerOffProc();

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            ScalerMHLRx5PowerOffProc();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLIntHandler_EXINT0(void) using 1
{
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
    ScalerMHLRx0IntHandler_EXINT0();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    ScalerMHLRx1IntHandler_EXINT0();
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    ScalerMHLRx2IntHandler_EXINT0();
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
    ScalerMHLRx3IntHandler_EXINT0();
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    ScalerMHLRx4IntHandler_EXINT0();
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    ScalerMHLRx5IntHandler_EXINT0();
#endif
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
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            return ScalerMHLRx0MscSendCommand(enumMSCCommand, enumMSCOffset, enumMSCValue);

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            return ScalerMHLRx1MscSendCommand(enumMSCCommand, enumMSCOffset, enumMSCValue);

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            return ScalerMHLRx2MscSendCommand(enumMSCCommand, enumMSCOffset, enumMSCValue);

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            return ScalerMHLRx3MscSendCommand(enumMSCCommand, enumMSCOffset, enumMSCValue);

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            return ScalerMHLRx4MscSendCommand(enumMSCCommand, enumMSCOffset, enumMSCValue);

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            return ScalerMHLRx5MscSendCommand(enumMSCCommand, enumMSCOffset, enumMSCValue);

            break;
#endif

        default:

            return _FAIL;
            break;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Check Write Status for Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLMscCheckDeviceINT(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            ScalerMHLRx0MscCheckDeviceINT();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            ScalerMHLRx1MscCheckDeviceINT();

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            ScalerMHLRx2MscCheckDeviceINT();

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            ScalerMHLRx3MscCheckDeviceINT();

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            ScalerMHLRx4MscCheckDeviceINT();

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            ScalerMHLRx5MscCheckDeviceINT();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : MSC Handler for Port
// Input Value  : ucActivePort --> Current Active Port
//                ucModeState --> Current Mode State
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLMscHandler(BYTE ucInputPort, BYTE ucActivePort, BYTE ucModeState)
{
    switch(ucInputPort)
    {
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            return ScalerMHLRx2MscHandler(ucActivePort, ucModeState);

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            return ScalerMHLRx3MscHandler(ucActivePort, ucModeState);

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            return ScalerMHLRx4MscHandler(ucActivePort, ucModeState);

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            return ScalerMHLRx5MscHandler(ucActivePort, ucModeState);

            break;
#endif

        default:

            return _FALSE;
            break;
    }

    return _FAIL;
}


//--------------------------------------------------
// Description  : RAP Process for Port
// Input Value  : None
// Output Value : True or False (False if Content Off)
//--------------------------------------------------
bit ScalerMHLMscRAPHandler(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            return ScalerMHLRx0MscRAPHandler();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            return ScalerMHLRx1MscRAPHandler();

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            return ScalerMHLRx2MscRAPHandler();

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            return ScalerMHLRx3MscRAPHandler();

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            return ScalerMHLRx4MscRAPHandler();

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            return ScalerMHLRx5MscRAPHandler();

            break;
#endif

        default:

            return _FALSE;
            break;
    }

    return _FAIL;
}


//--------------------------------------------------
// Description  : Get RCP Key Code for Port
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLMscRCPGetCommand(BYTE ucInputPort, BYTE *pucKeyCode)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            return ScalerMHLRx0MscRCPGetCommand(pucKeyCode);

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            return ScalerMHLRx1MscRCPGetCommand(pucKeyCode);

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            return ScalerMHLRx2MscRCPGetCommand(pucKeyCode);

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            return ScalerMHLRx3MscRCPGetCommand(pucKeyCode);

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            return ScalerMHLRx4MscRCPGetCommand(pucKeyCode);

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            return ScalerMHLRx5MscRCPGetCommand(pucKeyCode);

            break;
#endif

        default:

            return _FALSE;
            break;
    }

    return _FAIL;
}


#if(_MHL_UCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get UCP Key Code for Port
// Input Value  : UCP Key Code
// Output Value : True or False
//--------------------------------------------------
BYTE ScalerMHLMscUCPGetCommand(BYTE ucInputPort, BYTE *pucKeyCode)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            return ScalerMHLRx0MscUCPGetCommand(pucKeyCode);

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            return ScalerMHLRx1MscUCPGetCommand(pucKeyCode);

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            return ScalerMHLRx2MscUCPGetCommand(pucKeyCode);

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            return ScalerMHLRx3MscUCPGetCommand(pucKeyCode);

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            return ScalerMHLRx4MscUCPGetCommand(pucKeyCode);

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            return ScalerMHLRx5MscUCPGetCommand(pucKeyCode);

            break;
#endif

        default:

            return _FALSE;
            break;
    }
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
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            return ScalerMHLRx0PSPreDetect();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            return ScalerMHLRx1PSPreDetect();

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            return ScalerMHLRx2PSPreDetect();

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            return ScalerMHLRx3PSPreDetect();

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            return ScalerMHLRx4PSPreDetect();

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            return ScalerMHLRx5PSPreDetect();

            break;
#endif

        default:

            return _FALSE;
            break;
    }

    return _FAIL;
}


//--------------------------------------------------
// Description  : Signal PreDetection for MHL(Power Normal)
// Input Value  : Input Port(HDMI or DVI)
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerMHLNormalPreDetect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _D0_INPUT_PORT:

            return ScalerMHLRx0NormalPreDetect();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _D1_INPUT_PORT:

            return ScalerMHLRx1NormalPreDetect();

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _D2_INPUT_PORT:

            return ScalerMHLRx2NormalPreDetect();

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _D3_INPUT_PORT:

            return ScalerMHLRx3NormalPreDetect();

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _D4_INPUT_PORT:

            return ScalerMHLRx4NormalPreDetect();

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _D5_INPUT_PORT:

            return ScalerMHLRx5NormalPreDetect();

            break;
#endif

        default:

            return _FALSE;
            break;
    }

    return _FAIL;
}


//--------------------------------------------------
// Description  : Handle MHL ports Related Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerMHLTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX0_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX0_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX0_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLRx0TimerEventProc(enumEventID);

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX1_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLRx1TimerEventProc(enumEventID);

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX2_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX2_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX2_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLRx2TimerEventProc(enumEventID);

            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX3_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX3_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLRx3TimerEventProc(enumEventID);

            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX4_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX4_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLRx4TimerEventProc(enumEventID);

            break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX5_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX5_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX5_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLRx5TimerEventProc(enumEventID);

            break;
#endif

        default:
            break;
    }
}

#endif // End of #if(_MHL_SUPPORT == _ON)

