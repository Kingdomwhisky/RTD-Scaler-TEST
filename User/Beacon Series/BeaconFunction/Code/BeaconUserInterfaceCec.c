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
// ID Code      : BeaconUserInterfaceCec.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_CEC__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_OSD)
#if(_HDMI_CEC_SUPPORT == _ON)
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
StructCecRxReceivedInfo g_stUserCecRxStruct;
StructCecTxTransmitInfo g_stUserCecTxStruct;

bit g_bCecTxNeedSend;
WORD g_pusPhysicalAddr[15]; // 0~14
bit g_bCecLaPollingStart;
bit g_bCecLaPollingContinue;
BYTE g_ucCecLaCnt;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit UserInterfaceCecGetCecActive(void);
void UserInterfaceCecReceivedNotify(StructCecRxReceivedInfo *pstCecRxInfo);
bit UserInterfaceCecTransmitInfoPrepare(StructCecTxTransmitInfo *pstCecTxInfo);
void UserInterfaceCecHighLevelFlow(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get CEC Fx Enable from user behavior
// Input Value  : NA
// Output Value : _TRUE: Enable CEC Fx
//--------------------------------------------------
bit UserInterfaceCecGetCecActive(void)
{
    return _TRUE;
}

//--------------------------------------------------
// Description  : Reload data from CEC RX
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceCecReceivedNotify(StructCecRxReceivedInfo *pstCecRxInfo)
{
    // LOAD CEC Rx Info to user's Cec Rx sturct
    memcpy(&g_stUserCecRxStruct, pstCecRxInfo, sizeof(StructCecRxReceivedInfo));
}

//--------------------------------------------------
// Description  : Prepare data need to send out
// Input Value  : pstCecRxInfo
// Output Value : _TRUE: Data need to Send out   _FALSE: no data need to send
//--------------------------------------------------
bit UserInterfaceCecTransmitInfoPrepare(StructCecTxTransmitInfo *pstCecTxInfo)
{
    // Load CEC TX data to Kernel struct
    if(g_bCecTxNeedSend == 1)
    {
        memcpy(pstCecTxInfo, &g_stUserCecTxStruct, sizeof(StructCecTxTransmitInfo));

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : User CEC High Level Flow Process
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserInterfaceCecHighLevelFlow(void)
{
    // --------------------------------------------
    // Part 1: Check Tx Send Task is done?
    // --------------------------------------------
    if((g_bCecTxNeedSend == 1) && (ScalerCecGetTxState() == _CEC_TX_IDLE_STATE))
    {
        g_bCecTxNeedSend = 0;
    }

    // --------------------------------------------
    // Part 2: Action & Reply CEC Message
    // use when ScalerCecRxGetMsgAnalyzingFlag() == _TRUE (means the CEC Message is received)
    // After User handle the incoming CEC Message, shall ScalerCecRxClrMsgAnalyzingFlag()
    // --------------------------------------------
    if((ScalerCecRxGetMsgAnalyzingFlag() == _TRUE) && (g_stUserCecRxStruct.ucDbLength > 0))
    {
        // Check incoming msg is not <Polling Message>
        if(g_stUserCecRxStruct.ucDbLength > 0)
        {
            switch(g_stUserCecRxStruct.pucReceivedDb[0])
            {
                case _CEC_OPCODE_GIVE_DEVICE_POWER_STATUS:

                    // Reset cec tx strucrt
                    memset(&g_stUserCecTxStruct, 0, sizeof(g_stUserCecTxStruct));

                    // Packing <Report Power Status>
                    g_stUserCecTxStruct.ucTransmitHb = ((_CEC_LA_TV << 4) | ((g_stUserCecRxStruct.ucReceivedHb & 0xF0) >> 4))  ;
                    g_stUserCecTxStruct.pucTransmitDb[0] = _CEC_OPCODE_REPORT_POWER_STATUS;

                    if(SysPowerGetPowerStatus() != _POWER_STATUS_NORMAL)
                    {
                        // set "Standby"
                        g_stUserCecTxStruct.pucTransmitDb[1]= 0x01;
                    }
                    else
                    {
                        // set "On"
                        g_stUserCecTxStruct.pucTransmitDb[1] = 0x00;
                    }

                    g_stUserCecTxStruct.ucDbLength = 2;
                    g_stUserCecTxStruct.b3RetryCnt = 3;

                    g_bCecTxNeedSend = 1;

                    break;

                case _CEC_OPCODE_REPORT_PHYSICAL_ADDRESS:

                    // Record PA of LA
                    g_pusPhysicalAddr[g_ucCecLaCnt] = ((g_stUserCecTxStruct.pucTransmitDb[1] << 8) | g_stUserCecTxStruct.pucTransmitDb[2]);

                    g_bCecLaPollingContinue = 1;
                    break;

                case _CEC_OPCODE_SET_OSD_STRING:

                    // OSD Need to Print String

                    break;

                case _CEC_OPCODE_STANDBY:

                    // Need to standby

                    break;

                // TODO: add for opcode need to respose but no support
                case _CEC_OPCODE_ABORT_MESSAGE:
                case _CEC_OPCODE_REPORT_SHORT_AUDIO_DESCRIPTOR:

                    // Reset cec tx strucrt
                    memset(&g_stUserCecTxStruct, 0, sizeof(g_stUserCecTxStruct));

                    // Packing <Feater Abort>
                    g_stUserCecTxStruct.ucTransmitHb = (_CEC_LA_TV << 4 | ((g_stUserCecRxStruct.ucReceivedHb & 0xF0) >> 4));
                    g_stUserCecTxStruct.pucTransmitDb[0] = _CEC_OPCODE_FEATURE_ABORT;
                    g_stUserCecTxStruct.pucTransmitDb[1] = _CEC_OPCODE_ABORT_MESSAGE;
                    g_stUserCecTxStruct.pucTransmitDb[2] = 0x00; // unrecognized opcode

                    g_stUserCecTxStruct.ucDbLength = 3;
                    g_stUserCecTxStruct.b3RetryCnt = 3;

                    g_bCecTxNeedSend = 1;

                    break;

                default:

                    break;
            }
        }

        ScalerCecRxClrIMsgAnalyzingFlag();
    }

    // --------------------------------------------
    // Part 3: Active CEC TX Send task by user behavior
    // Trigger by end user behavior or Topology build by scan LA
    // --------------------------------------------
    // CEC TX Task Trigger by end user behavior
#if 1
    if((ScalerGetByte(0x000D) == 0xFF) && (g_bCecTxNeedSend == 0))
    {
        // Reset cec tx strucrt
        memset(&g_stUserCecTxStruct, 0, sizeof(g_stUserCecTxStruct));

        // Packing <Give Device Vendor ID>
        // g_stUserCecTxStruct.ucTransmitHb = (_CEC_LA_TV << 4 | ((g_stUserCecRxStruct.ucReceivedHb & 0xF0) >> 4));
        g_stUserCecTxStruct.ucTransmitHb = 0x04;
        g_stUserCecTxStruct.pucTransmitDb[0] = _CEC_OPCODE_GIVE_DEVICE_VENDOR_ID;

        g_stUserCecTxStruct.ucDbLength = 1;
        g_stUserCecTxStruct.b3RetryCnt = 3;

        g_bCecTxNeedSend = 1;
        ScalerSetByte(0x000D, 0x00);
    }
    else if((ScalerGetByte(0x000D) == 0x1F) && (g_bCecTxNeedSend == 0))
    {
        // Reset cec tx strucrt
        memset(&g_stUserCecTxStruct, 0, sizeof(g_stUserCecTxStruct));

        // Packing <Standby>
        g_stUserCecTxStruct.ucTransmitHb = 0x04;
        g_stUserCecTxStruct.pucTransmitDb[0] = _CEC_OPCODE_STANDBY;

        g_stUserCecTxStruct.ucDbLength = 1;
        g_stUserCecTxStruct.b3RetryCnt = 3;

        g_bCecTxNeedSend = 1;
        ScalerSetByte(0x000D, 0x00);
    }
    else if((ScalerGetByte(0x000D) == 0x7F) && (g_bCecTxNeedSend == 0))
    {
        // Reset cec tx strucrt
        memset(&g_stUserCecTxStruct, 0, sizeof(g_stUserCecTxStruct));

        // Packing <Cec Ver>
        g_stUserCecTxStruct.ucTransmitHb = 0x04;
        g_stUserCecTxStruct.pucTransmitDb[0] = _CEC_OPCODE_GET_CEC_VERSION;

        g_stUserCecTxStruct.ucDbLength = 1;
        g_stUserCecTxStruct.b3RetryCnt = 3;

        g_bCecTxNeedSend = 1;
        ScalerSetByte(0x000D, 0x00);
    }
    else if((ScalerGetByte(0x000D) == 0x3F) && (g_bCecTxNeedSend == 0))
    {
        // Reset cec tx strucrt
        memset(&g_stUserCecTxStruct, 0, sizeof(g_stUserCecTxStruct));

        // Packing <Give Power Status>
        g_stUserCecTxStruct.ucTransmitHb = 0x04;
        g_stUserCecTxStruct.pucTransmitDb[0] = _CEC_OPCODE_GIVE_DEVICE_POWER_STATUS;

        g_stUserCecTxStruct.ucDbLength = 1;
        g_stUserCecTxStruct.b3RetryCnt = 3;

        g_bCecTxNeedSend = 1;
        ScalerSetByte(0x000D, 0x00);
    }
    else if((ScalerGetByte(0x000D) == 0x5F) && (g_bCecTxNeedSend == 0))
    {
        // Reset cec tx strucrt
        memset(&g_stUserCecTxStruct, 0, sizeof(g_stUserCecTxStruct));

        // Packing <Give Physical Address>
        g_stUserCecTxStruct.ucTransmitHb = 0x04;
        g_stUserCecTxStruct.pucTransmitDb[0] = _CEC_OPCODE_GIVE_PHYSICAL_ADDRESS;

        g_stUserCecTxStruct.ucDbLength = 1;
        g_stUserCecTxStruct.b3RetryCnt = 2;

        g_bCecTxNeedSend = 1;
        ScalerSetByte(0x000D, 0x00);
    }
#endif

#if 1
    // Topology build by scan LA
    if(g_bCecLaPollingStart == 1)
    {
        if(g_bCecTxNeedSend == 0)
        {
            if((g_ucCecLaCnt == 0) || (g_bCecLaPollingContinue == 1)) // Active or Reactive LA Polling task
            {
                // scan LA from LA = 1
                g_ucCecLaCnt++;
                g_bCecLaPollingContinue = 0;

                if(g_ucCecLaCnt != 15)
                {
                    // Reset cec tx strucrt
                    memset(&g_stUserCecTxStruct, 0, sizeof(g_stUserCecTxStruct));

                    // Packing <Polling Message>
                    g_stUserCecTxStruct.ucTransmitHb = (_CEC_LA_TV << 4 | g_ucCecLaCnt);
                    g_stUserCecTxStruct.ucDbLength = 0;
                    g_stUserCecTxStruct.b3RetryCnt = 2;

                    g_bCecTxNeedSend = 1;
                }
            }
            else if((ScalerCecTxGetTransmitResult() == _CEC_TX_SENT_EVENT) && (g_stUserCecTxStruct.ucDbLength == 0x00))  // No deivce matxh LA
            {
                // Reset cec tx strucrt
                memset(&g_stUserCecTxStruct, 0, sizeof(g_stUserCecTxStruct));

                // Packing <Give Physical Address>
                g_stUserCecTxStruct.ucTransmitHb = (_CEC_LA_TV << 4 | g_ucCecLaCnt);
                g_stUserCecTxStruct.pucTransmitDb[0] = _CEC_OPCODE_GIVE_PHYSICAL_ADDRESS;

                g_stUserCecTxStruct.ucDbLength = 1;
                g_stUserCecTxStruct.b3RetryCnt = 2;

                g_bCecTxNeedSend = 1;
            }
            else if((ScalerCecTxGetTransmitResult() == _CEC_TX_HB_NACK_EVENT) && (g_stUserCecTxStruct.ucDbLength == 0x00)) // No deivce matxh LA
            {
                g_ucCecLaCnt++;

                if(g_ucCecLaCnt != 15)
                {
                    // Reset cec tx strucrt
                    memset(&g_stUserCecTxStruct, 0, sizeof(g_stUserCecTxStruct));

                    // Packing <Polling Message>
                    g_stUserCecTxStruct.ucTransmitHb = (_CEC_LA_TV << 4 | g_ucCecLaCnt);
                    g_stUserCecTxStruct.ucDbLength = 0;
                    g_stUserCecTxStruct.b3RetryCnt = 2;

                    g_bCecTxNeedSend = 1;
                }
            }
        }

        if(g_ucCecLaCnt == 15)
        {
            g_bCecLaPollingStart = 0;
        }
    }
    else if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_CEC_LA_POLLING) == _FALSE)
    {
        ScalerTimerActiveTimerEvent(SEC(30), _USER_TIMER_EVENT_CEC_LA_POLLING);
    }
#endif
}
#endif
#endif // End of #if(_OSD_TYPE == _BEACON_OSD)
