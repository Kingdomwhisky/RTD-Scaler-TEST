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
// ID Code      : ScalerTimerFunction.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TIMERFUNCTION__

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
bit ScalerTimerWaitForEvent(EnumWaitEventType enumEvent);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit ScalerTimerWaitForEvent(EnumWaitEventType enumEvent)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;

    switch(enumEvent)
    {
        case _EVENT_DVS:
        case _EVENT_DEN_START:
        case _EVENT_DEN_STOP:
            // Check if D-domain events do occur
            if((ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT0) == 0x00) ||
               (GET_DPLL_POWER_STATUS() == _FALSE))
            {
                return _FALSE;
            }
            break;

        case _EVENT_IEN_START:
        case _EVENT_IEN_STOP:
            // Check if I-domain events do occur
            if(ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT0) == 0x00)
            {
                return _FALSE;
            }
            break;

        default:
            break;
    }

    // Clear status (status register will be cleared after write)
    ScalerTimerClrEventStatus(enumEvent);

    usPreviousTime = g_usTimerCounter;

    do
    {
        if(ScalerTimerGetEventStatus(enumEvent) == enumEvent)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while(usTimeElapsed <= _TIMER_WAIT_EVENT_TIMEOUT);

    return _FALSE;
}

