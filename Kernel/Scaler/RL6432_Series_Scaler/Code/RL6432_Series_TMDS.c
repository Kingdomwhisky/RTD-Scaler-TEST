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
// ID Code      : RL6432_Series_TMDS.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6432_SERIES_TMDS__

#include "ScalerFunctionInclude.h"

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

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
void ScalerTMDSInitial(BYTE ucInputPort);
void ScalerTMDSInterruptInitial(BYTE ucInputPort);
void ScalerTMDSIntHandler_EXINT0(void);
void ScalerTMDSPSIntHandler_EXINT0(void);
void ScalerTMDSVideoDetectEvent(EnumScalerTimerEventID enumEventID);
void ScalerTMDSResetProc(void);

#if(_UNDERSCAN_SUPPORT == _ON)
void ScalerTMDSSetPorchColor(BYTE ucInputPort, EnumColorSpace enumColorFormat);
#endif

#if(_HDMI_SUPPORT == _ON)

void ScalerTMDSHdmiAVMuteProc(void);
void ScalerTMDSHdmiWatchDog(BYTE ucWDType, bit bEnable);
void ScalerTMDSHdmiPacketDetectEvent(EnumScalerTimerEventID enumEventID);

#if(_HDMI_2_0_SUPPORT == _ON)
void ScalerTMDSHdmiReadRequestTimerEnable_WDINT(bit bEnable);
void ScalerTMDSHdmi2FormatResetEvent(EnumScalerTimerEventID enumEventID);
#endif

bit ScalerTMDSYUV420SupportCheck(BYTE ucInputPort);

#endif

void ScalerTMDSFreqDetectDisable(void);
void ScalerTMDSFirstActiveProc(BYTE ucInputPort, BYTE ucSourceType);
bit ScalerTMDSHdcpEnabled(BYTE ucInputPort);

bit ScalerTMDSPSPreDetect(BYTE ucInputPort);
bit ScalerTMDSNormalPreDetect(BYTE ucInputPort);
BYTE ScalerTMDSScanInputPort(BYTE ucInputPort, BYTE ucInputType);

bit ScalerTMDSStableDetect(BYTE ucInputPort, BYTE ucSourceType);
void ScalerTMDSHotPlugEvent(BYTE ucPortSelect);
void ScalerTMDSBeforeHotPlugEventProc(BYTE ucPortSelect);
void ScalerTMDSHotPlugLowProc(BYTE ucPortSelect);
void ScalerTMDSHotPlugHighProc(BYTE ucPortSelect, WORD usHpdTime);
void ScalerTMDSAfterHotPlugEventProc(BYTE ucPortSelect);
void ScalerTMDSHdcp1p4AksvClear(BYTE ucInputPort);

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
void ScalerTMDSClkLaneZ0StartToggle(void);
void ScalerTMDSClkLaneZ0LowProc(void);
void ScalerTMDSClkLaneZ0HighProc(void);
void ScalerTMDSClkLaneZ0StopToggle(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initialize TMDS setting for search
// Input Value  : Current Search Port
// Output Value : None
//--------------------------------------------------
void ScalerTMDSInitial(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D1_TMDS_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            ScalerTMDSRx1Initial();

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)

        case _D2_INPUT_PORT:

            ScalerTMDSRx2Initial();

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)

        case _D3_INPUT_PORT:

            ScalerTMDSRx3Initial();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Initialize TMDS Interrupt Required Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSInterruptInitial(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D1_TMDS_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            ScalerTMDSRx1InterruptInitial();

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)

        case _D2_INPUT_PORT:

            ScalerTMDSRx2InterruptInitial();

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)

        case _D3_INPUT_PORT:

            ScalerTMDSRx3InterruptInitial();

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
void ScalerTMDSIntHandler_EXINT0(void) using 1
{
#if(_D1_TMDS_SUPPORT == _ON)
    ScalerTMDSRx1IntHandler_EXINT0();
#endif

#if(_D2_TMDS_SUPPORT == _ON)
    ScalerTMDSRx2IntHandler_EXINT0();
#endif

#if(_D3_TMDS_SUPPORT == _ON)
    ScalerTMDSRx3IntHandler_EXINT0();
#endif
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process In PS/PD State(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSPSIntHandler_EXINT0(void) using 1
{
#if(_D1_TMDS_SUPPORT == _ON)
    ScalerTMDSRx1PSIntHandler_EXINT0();
#endif

#if(_D2_TMDS_SUPPORT == _ON)
    ScalerTMDSRx2PSIntHandler_EXINT0();
#endif

#if(_D3_TMDS_SUPPORT == _ON)
    ScalerTMDSRx3PSIntHandler_EXINT0();
#endif
}

//--------------------------------------------------
// Description  : TMDS video Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSVideoDetectEvent(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX1_TMDS_VIDEO_DETECT:

            ScalerTMDSRx1TMDSVideoDetectEvent();

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX2_TMDS_VIDEO_DETECT:

            ScalerTMDSRx2TMDSVideoDetectEvent();

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_TMDS_VIDEO_DETECT:

            ScalerTMDSRx3TMDSVideoDetectEvent();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSResetProc(void)
{
#if(_D1_TMDS_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX1_TMDS_VIDEO_DETECT);
#if(_D1_HDMI_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX1_TMDS_HDMI_PACKET_DETECT);
#if(_D1_HDMI_2_0_SUPPORT == _ON)
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX1_HDMI_RR_RETRY);
#endif
#endif // End of #if(_D1_HDMI_SUPPORT == _ON)
#endif // End of #if(_D1_TMDS_SUPPORT == _ON)

#if(_D2_TMDS_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX2_TMDS_VIDEO_DETECT);
#if(_D2_HDMI_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX2_TMDS_HDMI_PACKET_DETECT);
#if(_D2_HDMI_2_0_SUPPORT == _ON)
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX2_HDMI_RR_RETRY);
#endif
#endif // End of #if(_D2_HDMI_SUPPORT == _ON)
#endif // End of #if(_D2_TMDS_SUPPORT == _ON)

#if(_D3_TMDS_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX3_TMDS_VIDEO_DETECT);
#if(_D3_HDMI_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX3_TMDS_HDMI_PACKET_DETECT);
#if(_D3_HDMI_2_0_SUPPORT == _ON)
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX3_HDMI_RR_RETRY);
#endif
#endif // End of #if(_D3_HDMI_SUPPORT == _ON)
#endif // End of #if(_D3_TMDS_SUPPORT == _ON)
}

#if(_UNDERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Back Ground Color
// Input Value  : InputPort and Current Color Space
// Output Value : None
//--------------------------------------------------
void ScalerTMDSSetPorchColor(BYTE ucInputPort, EnumColorSpace enumColorFormat)
{
    switch(ucInputPort)
    {
#if(_D1_TMDS_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            ScalerTMDSRx1SetPorchColor(enumColorFormat);

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)

        case _D2_INPUT_PORT:

            ScalerTMDSRx2SetPorchColor(enumColorFormat);

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)

        case _D3_INPUT_PORT:

            ScalerTMDSRx3SetPorchColor(enumColorFormat);

            break;
#endif

        default:

            break;
    }
}
#endif

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hdmi Handle AVMute Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHdmiAVMuteProc(void)
{
#if(_D1_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
    {
        ScalerTMDSRx1HdmiAVMuteProc();
    }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
    {
        ScalerTMDSRx2HdmiAVMuteProc();
    }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
    {
        ScalerTMDSRx3HdmiAVMuteProc();
    }
#endif
}

//--------------------------------------------------
// Description  : Hdmi Enable Watch Dog
// Input Value  : ucWDType => Watch Dog type, bEnable => Enable watch dog flag
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHdmiWatchDog(BYTE ucWDType, bit bEnable)
{
#if(_D1_HDMI_SUPPORT == _ON)
    ScalerTMDSRx1HdmiWatchDog(ucWDType, bEnable);
#endif // End of #if(_D1_HDMI_SUPPORT == _ON)

#if(_D2_HDMI_SUPPORT == _ON)
    ScalerTMDSRx2HdmiWatchDog(ucWDType, bEnable);
#endif // End of #if(_D2_HDMI_SUPPORT == _ON)

#if(_D3_HDMI_SUPPORT == _ON)
    ScalerTMDSRx3HdmiWatchDog(ucWDType, bEnable);
#endif // End of #if(_D3_HDMI_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHdmiPacketDetectEvent(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX1_TMDS_HDMI_PACKET_DETECT:

            ScalerTMDSRx1HdmiPacketDetectEvent();

            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX2_TMDS_HDMI_PACKET_DETECT:

            ScalerTMDSRx2HdmiPacketDetectEvent();

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_TMDS_HDMI_PACKET_DETECT:

            ScalerTMDSRx3HdmiPacketDetectEvent();

            break;
#endif

        default:

            break;
    }
}

#if(_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hdmi Enable RR Timer
// Input Value  : bEnable => Enable RR Timer flag
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHdmiReadRequestTimerEnable_WDINT(bit bEnable) using 3
{
#if(_D1_HDMI_2_0_SUPPORT == _ON)
    ScalerTMDSRx1ReadRequestTimerEventEnable_WDINT(bEnable);
#endif

#if(_D2_HDMI_2_0_SUPPORT == _ON)
    ScalerTMDSRx2ReadRequestTimerEventEnable_WDINT(bEnable);
#endif

#if(_D3_HDMI_2_0_SUPPORT == _ON)
    ScalerTMDSRx3ReadRequestTimerEventEnable_WDINT(bEnable);
#endif
}

//--------------------------------------------------
// Description  : TMDS Format Reset Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHdmi2FormatResetEvent(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_D1_HDMI_2_0_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX1_HDMI2_FORMAT_RESET_WAIT:
            ScalerTMDSRx1Hdmi2FormatResetEvent();
            break;
#endif

#if(_D2_HDMI_2_0_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX2_HDMI2_FORMAT_RESET_WAIT:
            ScalerTMDSRx2Hdmi2FormatResetEvent();
            break;
#endif

#if(_D3_HDMI_2_0_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_HDMI2_FORMAT_RESET_WAIT:
            ScalerTMDSRx3Hdmi2FormatResetEvent();
            break;
#endif
        default:
            break;
    }
}
#endif // End of #if(_HDMI_2_0_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS 420 Color Space Support Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerTMDSYUV420SupportCheck(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(ScalerColorGetColorSpace() == _COLOR_SPACE_YCBCR420)
            {
                return _FALSE;
            }

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(ScalerColorGetColorSpace() == _COLOR_SPACE_YCBCR420)
            {
                return _FALSE;
            }

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            if(ScalerColorGetColorSpace() == _COLOR_SPACE_YCBCR420)
            {
                return _FALSE;
            }

            break;
#endif
        default:
            break;
    }

    return _TRUE;
}
#endif // End of #if(_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS Freq. Detection IRQ Disable and Clear Clock Counter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSFreqDetectDisable(void)
{
#if(_D1_TMDS_SUPPORT == _ON)
    ScalerTMDSRx1FreqDetectDisable();
#endif

#if(_D2_TMDS_SUPPORT == _ON)
    ScalerTMDSRx2FreqDetectDisable();
#endif

#if(_D3_TMDS_SUPPORT == _ON)
    ScalerTMDSRx3FreqDetectDisable();
#endif
}

//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerTMDSFirstActiveProc(BYTE ucInputPort, BYTE ucSourceType)
{
    ucSourceType = ucSourceType;

    switch(ucInputPort)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            ScalerTMDSRx1FirstActiveProc(ucSourceType);
            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            ScalerTMDSRx2FirstActiveProc(ucSourceType);
            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            ScalerTMDSRx3FirstActiveProc(ucSourceType);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerTMDSHdcpEnabled(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D1_INPUT_PORT:

#if((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
            return ScalerTMDSRx1HdcpEnabled();
#endif

            break;

        case _D2_INPUT_PORT:

#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
            return ScalerTMDSRx2HdcpEnabled();
#elif(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            return ScalerTMDSRx3HdcpEnabled();
#endif

            break;

        case _D3_INPUT_PORT:

#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
            return ScalerTMDSRx3HdcpEnabled();
#endif

            break;

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal Detection for TMDS(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSPSPreDetect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D1_INPUT_PORT:

#if(_D1_TMDS_SUPPORT == _ON)
            return ScalerTMDSRx1TMDSPSPreDetect();
#endif

            break;

        case _D2_INPUT_PORT:

#if((_D2_TMDS_SUPPORT == _ON) && (_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT))
            return ScalerTMDSRx2TMDSPSPreDetect();
#endif

            break;

        case _D3_INPUT_PORT:

#if((_D3_TMDS_SUPPORT == _ON) &&\
    (_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT) &&\
    (_D3_INPUT_PORT_TYPE != _D3_NO_PORT))
            return ScalerTMDSRx3TMDSPSPreDetect();
#endif

            break;

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal PreDetection for TMDS(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSNormalPreDetect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D1_INPUT_PORT:

#if(_D1_TMDS_SUPPORT == _ON)
            return ScalerTMDSRx1TMDSNormalPreDetect();
#endif

            break;

        case _D2_INPUT_PORT:

#if((_D2_TMDS_SUPPORT == _ON) && (_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT))
            return ScalerTMDSRx2TMDSNormalPreDetect();
#endif

            break;

        case _D3_INPUT_PORT:

#if((_D3_TMDS_SUPPORT == _ON) &&\
    (_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT) &&\
    (_D3_INPUT_PORT_TYPE != _D3_NO_PORT))
            return ScalerTMDSRx3TMDSNormalPreDetect();
#endif

            break;

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Port Source/Sync Scanning and Setting
// Input Value  : Input Port
// Output Value : Source DVI --> DVI Format
//                Source HDMI --> HDMI Format
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerTMDSScanInputPort(BYTE ucInputPort, BYTE ucInputType)
{ 
    ucInputType = ucInputType;

    switch(ucInputPort)
    {
        case _D1_INPUT_PORT:

#if(_D1_TMDS_SUPPORT == _ON)
            return ScalerTMDSRx1TMDSScanInputPort(ucInputType);
#endif

            break;

        case _D2_INPUT_PORT:

#if((_D2_TMDS_SUPPORT == _ON) && (_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT))
            return ScalerTMDSRx2TMDSScanInputPort(ucInputType);
#endif

            break;

        case _D3_INPUT_PORT:

#if((_D3_TMDS_SUPPORT == _ON) &&\
    (_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT) &&\
    (_D3_INPUT_PORT_TYPE != _D3_NO_PORT))
            return ScalerTMDSRx3TMDSScanInputPort(ucInputType);
#endif

            break;

        default:

            break;
    }

    return _SOURCE_NONE;
}

//--------------------------------------------------
// Description  : On Line Check TMDS stability
// Input Value  : ucSourceType --> Source Type
// Output Value : True --> TMDS Stable
//                False --> TMDS Unstable
//--------------------------------------------------
bit ScalerTMDSStableDetect(BYTE ucInputPort, BYTE ucSourceType)
{
    switch(ucSourceType)
    {
        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            switch(ucInputPort)
            {
#if(_D1_TMDS_SUPPORT == _ON)

                case _D1_INPUT_PORT:
                    return ScalerTMDSRx1TMDSStableDetect(ucSourceType);
#endif

#if(_D2_TMDS_SUPPORT == _ON)

                case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
                    return ScalerTMDSRx2TMDSStableDetect(ucSourceType);
#else
                    if(ScalerDualLinkDVIGetDualDVIMode(_D2_INPUT_PORT) == _TRUE)
                    {
                        return ((ScalerTMDSRx2TMDSStableDetect(ucSourceType) == _TRUE) &&
                                (ScalerTMDSRx3TMDSStableDetect(ucSourceType) == _TRUE));
                    }
                    else
                    {
                        return ScalerTMDSRx3TMDSStableDetect(ucSourceType);
                    }
#endif

#endif

#if(_D3_TMDS_SUPPORT == _ON)

                case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
                    return ScalerTMDSRx3TMDSStableDetect(ucSourceType);
#endif

#endif
                default:
                    break;
            }

            break;

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Hot Plug Event
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerTMDSHotPlugEvent(BYTE ucPortSelect)
{
    switch(ucPortSelect)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            ScalerTMDSRx1HotPlugEvent();

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            ScalerTMDSRx2HotPlugEvent();

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            ScalerTMDSRx3HotPlugEvent();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Before Hot Plug Event Process
// Input Value  : ucPortSelect
// Output Value : Hot Plug time
//--------------------------------------------------
void ScalerTMDSBeforeHotPlugEventProc(BYTE ucPortSelect)
{
    switch(ucPortSelect)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            ScalerTMDSRx1BeforeHotPlugEventProc();

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            ScalerTMDSRx2BeforeHotPlugEventProc();

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            ScalerTMDSRx3BeforeHotPlugEventProc();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Hot Plug Low Process
// Input Value  : ucPortSelect
// Output Value :
//--------------------------------------------------
void ScalerTMDSHotPlugLowProc(BYTE ucPortSelect)
{
    switch(ucPortSelect)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            ScalerTMDSRx1HotPlugLowProc();

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            ScalerTMDSRx2HotPlugLowProc();

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            ScalerTMDSRx3HotPlugLowProc();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : TMDS Hot Plug High Process
// Input Value  : ucPortSelect, usHpdTime
// Output Value :
//--------------------------------------------------
void ScalerTMDSHotPlugHighProc(BYTE ucPortSelect, WORD usHpdTime)
{
    switch(ucPortSelect)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            ScalerTMDSRx1HotPlugHighProc(usHpdTime);

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            ScalerTMDSRx2HotPlugHighProc(usHpdTime);

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            ScalerTMDSRx3HotPlugHighProc(usHpdTime);

            break;
#endif

        default:

            break;
    }
}
//--------------------------------------------------
// Description  : TMDS After Hot Plug Event Process
// Input Value  : ucPortSelect
// Output Value :
//--------------------------------------------------
void ScalerTMDSAfterHotPlugEventProc(BYTE ucPortSelect)
{
    switch(ucPortSelect)
    {
#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            ScalerTMDSRx1AfterHotPlugEventProc();

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            ScalerTMDSRx2AfterHotPlugEventProc();

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            ScalerTMDSRx3AfterHotPlugEventProc();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : ScalerTMDSHdcp1p4AksvClear
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerTMDSHdcp1p4AksvClear(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_TMDS_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            break;
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            if(CHECK_TMDS_DPHY_SWITCH(_D1_INPUT_PORT) == _TRUE)
            {
                ScalerTMDSRx1Hdcp1p4AksvClear();
            }
            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            if(CHECK_TMDS_DPHY_SWITCH(_D2_INPUT_PORT) == _TRUE)
            {
                ScalerTMDSRx2Hdcp1p4AksvClear();
            }

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            if(CHECK_TMDS_DPHY_SWITCH(_D3_INPUT_PORT) == _TRUE)
            {
                ScalerTMDSRx3Hdcp1p4AksvClear();
            }
            break;
#endif

        default:

            break;
    }
}

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CLK Lane Z0 Start Toggle for Eizo
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSClkLaneZ0StartToggle(void)
{
    // Activate Timer for High Duty
    ScalerTimerActiveTimerEvent(_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY, _SCALER_TIMER_EVENT_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY);
}

//--------------------------------------------------
// Description  : CLK Lane Z0 Low in power saving for Eizo
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSClkLaneZ0LowProc(void)
{
#if(_D1_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
    {
        // Disable CLK Lane Z0
        ScalerSetBit(P7A_18_IMPEDANCE_00, ~_BIT7, 0x00);
    }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
    {
        // Disable CLK Lane Z0
        ScalerSetBit(P7B_18_IMPEDANCE_00, ~_BIT7, 0x00);
    }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
    {
        // Disable CLK Lane Z0
        ScalerSetBit(P7C_18_IMPEDANCE_00, ~_BIT7, 0x00);
    }
#endif

    // Activate Timer for Low Duty
    ScalerTimerActiveTimerEvent(_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY, _SCALER_TIMER_EVENT_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY);
}

//--------------------------------------------------
// Description  : CLK Lane Z0 High in power saving for Eizo
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSClkLaneZ0HighProc(void)
{
#if(_D1_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
    {
        // Disable CLK Lane Z0
        ScalerSetBit(P7A_18_IMPEDANCE_00, ~_BIT7, _BIT7);
    }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
    {
        // Disable CLK Lane Z0
        ScalerSetBit(P7B_18_IMPEDANCE_00, ~_BIT7, _BIT7);
    }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
    {
        // Disable CLK Lane Z0
        ScalerSetBit(P7C_18_IMPEDANCE_00, ~_BIT7, _BIT7);
    }
#endif

    // Activate Timer for High Duty
    ScalerTimerActiveTimerEvent(_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY, _SCALER_TIMER_EVENT_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY);
}

//--------------------------------------------------
// Description  : CLK Lane Z0 Stop Toggle for Eizo
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSClkLaneZ0StopToggle(void)
{
#if(_D1_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
    {
        // Enable CLK Lane Z0
        ScalerSetBit(P7A_18_IMPEDANCE_00, ~_BIT7, _BIT7);
    }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
    {
        // Enable CLK Lane Z0
        ScalerSetBit(P7B_18_IMPEDANCE_00, ~_BIT7, _BIT7);
    }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
    {
        // Enable CLK Lane Z0
        ScalerSetBit(P7C_18_IMPEDANCE_00, ~_BIT7, _BIT7);
    }
#endif

    // Cancel Timer Event
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY);
}

#endif // End of #if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
