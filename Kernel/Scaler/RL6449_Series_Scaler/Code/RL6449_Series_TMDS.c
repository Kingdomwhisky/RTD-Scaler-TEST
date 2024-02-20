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
// ID Code      : RL6449_Series_TMDS.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6449_SERIES_TMDS__

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

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hdmi Handle AVMute Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHdmiAVMuteProc(void)
{
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
#if(_D2_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX2_TMDS_HDMI_PACKET_DETECT:

            ScalerTMDSRx2HdmiPacketDetectEvent();

            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
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
    bEnable = bEnable;

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
#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return _TRUE;
            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            return _TRUE;
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
        default:
            break;

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
        case _D2_INPUT_PORT:

#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
            return ScalerTMDSRx2HdcpEnabled();
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
#if(_D2_TMDS_SUPPORT == _ON)

                case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
                    return ScalerTMDSRx2TMDSStableDetect(ucSourceType);
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
#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            ScalerTMDSRx2Hdcp1p4AksvClear();
            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            ScalerTMDSRx3Hdcp1p4AksvClear();

            break;
#endif

        default:

            break;
    }
}
#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

