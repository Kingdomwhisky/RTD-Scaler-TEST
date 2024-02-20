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
// ID Code      : ScalerMHLRx4_SeptPhy.c No.0000
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
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
bit ScalerMHLRx4MscRCPGetCommand(BYTE *pucKeyCode);
void ScalerMHLRx4TimerEventProc(EnumScalerTimerEventID enumEventID);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
//--------------------------------------------------
// Description  : Get RCP Key Code for D4 Port
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx4MscRCPGetCommand(BYTE *pucKeyCode)
{
    // Check RCP Command
    if((bit)ScalerGetBit(P69_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
    {
        // Clear Flag
        ScalerSetByte(P69_D4_CBUS_CTRL_34, (BYTE)_BIT6);

        pucKeyCode[0] = ScalerGetByte(P69_D9_CBUS_CTRL_39);

        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Handle MHL Rx4 Related Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx4TimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _SCALER_TIMER_EVENT_MHL_RX4_READY_TO_TRANSMIT:

            SET_MHL_RX4_READY_TO_TRANSMIT();

            break;

        case _SCALER_TIMER_EVENT_MHL_RX4_RECONNECT_1K:

            if((((ScalerGetByte(P69_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x01) ||
               (((ScalerGetByte(P69_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x02))
            {
                ScalerSetBit(P69_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                ScalerTimerDelayXms(52);
                ScalerSetBit(P69_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);
            }

            break;

        case _SCALER_TIMER_EVENT_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE:

            SET_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE();

            break;

        default:
            break;
    }
}
#endif
