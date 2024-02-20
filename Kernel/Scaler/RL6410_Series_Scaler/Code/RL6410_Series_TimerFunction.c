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
// ID Code      : RL6410_Series_TimerFunction.c No.0000
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
void ScalerTimerClrEventStatus(EnumWaitEventType enumEvent);
void ScalerTimerClrEventStatusbyReg(EnumWaitEventType enumEvent);

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
void ScalerTimerClrEventStatusbyFlag(EnumWaitEventType enumEvent);
#endif

BYTE ScalerTimerGetEventStatus(EnumWaitEventType enumEvent);
BYTE ScalerTimerGetEventStatusbyReg(EnumWaitEventType enumEvent);

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
BYTE ScalerTimerGetEventStatusbyFlag(EnumWaitEventType enumEvent);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Clear Event Status
// Input Value  : enumEvent   --> Specified event
// Output Value : None
//--------------------------------------------------
void ScalerTimerClrEventStatus(EnumWaitEventType enumEvent)
{
    switch(enumEvent)
    {
        case _EVENT_IVS:
        case _EVENT_IEN_STOP:
        case _EVENT_DEN_STOP:
        case _EVENT_ALL:
        default:
            ScalerTimerClrEventStatusbyReg(enumEvent);
            break;

        case _EVENT_DEN_START:
            // Total
#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
            if(ScalerGetBit(P0_05_IRQ_CTRL1, _BIT3) == _BIT3)
            {
                ScalerTimerClrEventStatusbyFlag(enumEvent);
            }
            else
#endif
            {
                ScalerTimerClrEventStatusbyReg(enumEvent);
            }

            break;
    }
}

//--------------------------------------------------
// Description  : Clear Register Event Status
// Input Value  : enumEvent   --> Specified event
// Output Value : None
//--------------------------------------------------
void ScalerTimerClrEventStatusbyReg(EnumWaitEventType enumEvent)
{
    switch(enumEvent)
    {
        case _EVENT_IVS:
        case _EVENT_IEN_STOP:
            // M2
            ScalerSetByte(P40_03_M2_STATUS1, enumEvent);
            break;

        case _EVENT_DEN_START:
            // Total
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT2);
            break;

        case _EVENT_DEN_STOP:
            // Total
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT4);
            break;

        case _EVENT_ALL:
            ScalerSetByte(P40_03_M2_STATUS1, (_BIT2 | _BIT0));
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), (_BIT4 | _BIT2));
            ScalerSetByte(P0_03_STATUS1, (_BIT7 | _BIT6 | _BIT3 | _BIT1));
            break;

        default:
            ScalerSetByte(P0_03_STATUS1, enumEvent);
            break;
    }
}

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Clear Flag Event Status
// Input Value  : enumEvent   --> Specified event
// Output Value : None
//--------------------------------------------------
void ScalerTimerClrEventStatusbyFlag(EnumWaitEventType enumEvent)
{
    switch(enumEvent)
    {
#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
        case _EVENT_DEN_START:
            SET_EVENT_DEN_START_INT(_FALSE);
            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
BYTE ScalerTimerGetEventStatus(EnumWaitEventType enumEvent)
{
    switch(enumEvent)
    {
        case _EVENT_IVS:
        case _EVENT_IEN_STOP:
        case _EVENT_DEN_STOP:
        case _EVENT_ALL:
        default:
            return ScalerTimerGetEventStatusbyReg(enumEvent);

        case _EVENT_DEN_START:
            // Total
#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
            if(ScalerGetBit(P0_05_IRQ_CTRL1, _BIT3) == _BIT3)
            {
                return ScalerTimerGetEventStatusbyFlag(enumEvent);
            }
            else
#endif
            {
                return ScalerTimerGetEventStatusbyReg(enumEvent);
            }
    }
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs by register
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
BYTE ScalerTimerGetEventStatusbyReg(EnumWaitEventType enumEvent)
{
    switch(enumEvent)
    {
        case _EVENT_IVS:
        case _EVENT_IEN_STOP:
            // M2
            return (ScalerGetByte(P40_03_M2_STATUS1) & enumEvent);

        case _EVENT_DEN_START:
            // Total
            return ((ScalerGetByte(P0_05_IRQ_CTRL1) & _BIT2) << 2);

        case _EVENT_DEN_STOP:
            // Total
            return ((ScalerGetByte(P0_05_IRQ_CTRL1) & _BIT4) << 1);

        case _EVENT_ALL:
            return ((ScalerGetByte(P40_03_M2_STATUS1) & (_BIT2 | _BIT0)) | ((ScalerGetByte(P0_05_IRQ_CTRL1) & _BIT2) << 2) |
                    ((ScalerGetByte(P0_05_IRQ_CTRL1) & _BIT4) << 1) | (ScalerGetByte(P0_03_STATUS1) & (_BIT7 | _BIT6 | _BIT3 | _BIT1)));

        default:
            return (ScalerGetByte(P0_03_STATUS1) & enumEvent);
    }
}

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Hold until the specified event occurs by flag
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
BYTE ScalerTimerGetEventStatusbyFlag(EnumWaitEventType enumEvent)
{
    switch(enumEvent)
    {
        case _EVENT_DEN_START:
            // Total
            return GET_EVENT_DEN_START_INT();

        default:
            return _FALSE;
    }
}
#endif

