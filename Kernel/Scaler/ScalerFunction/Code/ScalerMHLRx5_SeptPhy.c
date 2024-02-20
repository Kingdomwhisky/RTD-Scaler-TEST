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
// ID Code      : ScalerMHLRx5_SeptPhy.c No.0000
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
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
bit ScalerMHLRx5MscRCPGetCommand(BYTE *pucKeyCode);
void ScalerMHLRx5TimerEventProc(EnumScalerTimerEventID enumEventID);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
//--------------------------------------------------
// Description  : Get RCP Key Code for D5 Port
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx5MscRCPGetCommand(BYTE *pucKeyCode)
{
    // Check RCP Command
    if((bit)ScalerGetBit(P6A_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
    {
        // Clear Flag
        ScalerSetByte(P6A_D4_CBUS_CTRL_34, (BYTE)_BIT6);

        pucKeyCode[0] = ScalerGetByte(P6A_D9_CBUS_CTRL_39);

        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Handle MHL Rx5 Related Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx5TimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _SCALER_TIMER_EVENT_MHL_RX5_READY_TO_TRANSMIT:

            SET_MHL_RX5_READY_TO_TRANSMIT();

            break;

        case _SCALER_TIMER_EVENT_MHL_RX5_RECONNECT_1K:

            if((((ScalerGetByte(P6A_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x01) ||
               (((ScalerGetByte(P6A_A7_CBUS_CTRL_07) & 0x38) >> 3) == 0x02))
            {
                ScalerSetBit(P6A_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
                ScalerTimerDelayXms(52);
                ScalerSetBit(P6A_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);
            }

            break;

        case _SCALER_TIMER_EVENT_MHL_RX5_SWITCH_PORT_DISCOVERY_DONE:

            SET_MHL_RX5_SWITCH_PORT_DISCOVERY_DONE();

            break;

        default:
            break;
    }
}
#endif
