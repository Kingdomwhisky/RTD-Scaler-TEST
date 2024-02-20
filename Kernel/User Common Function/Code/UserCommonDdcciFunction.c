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
// ID Code      : UserCommonDdcciFunction.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DDCCI_FUNCTION__

#include "UserCommonInclude.h"

#if(_DDCCI_CODE_REDUCTION == _OFF)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of DDCCI Capabilities Request
//--------------------------------------------------
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
// I2C Speed = 20k, DDCCI Buffer = _DDCCI_RXBUF_LENGTH
// (1/20K)*_DDCCI_RXBUF_LENGTH*8
#define _CLR_DDCCI_CMD_RECEIVE_NOT_FINISH_TIMEOUT       (((_DDCCI_RXBUF_LENGTH * 9) / 20) + 1)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _OFF)
#if(_VGA_PORT_EXIST == _ON)
BYTE code tCP_STRING_DSUB[] =
{
    _CAPABILITIES_STRING_VGA
};
#endif

#if(_DVI_PORT_EXIST == _ON)
BYTE code tCP_STRING_DVI[] =
{
    _CAPABILITIES_STRING_DVI
};
#endif

#if(_HDMI_PORT_EXIST == _ON)
BYTE code tCP_STRING_HDMI[] =
{
    _CAPABILITIES_STRING_HDMI
};
#endif

#if(_DP_PORT_EXIST == _ON)
BYTE code tCP_STRING_DP[] =
{
    _CAPABILITIES_STRING_DP
};
#endif
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

#if(_SUPPORT_GET_LUT == _ON)
WORD g_ucLUTCheckSum = 0;
BYTE g_ucLUTReadyFlag = 0;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonDdcciHandler(void);
void UserCommonDdcciInitTx(void);
void UserCommonDdcciInitRx(void);
BYTE UserCommonDdcciCalCheckSum(void);
void UserCommonDdcciSetVCPReplyValue(BYTE ucTypeOpcode, WORD usMax, WORD usPresent);
void UserCommonDdcciGetTimingReport(void);
void UserCommonDdcciGetCapabilitiesRequest(void);
void UserCommonDdcciGetCpStringData(BYTE *pucDest, EnumInputPortType enumPortType, WORD usStartIndex, WORD usLength);
WORD UserCommonDdcciGetCpStringSize(EnumInputPortType enumPortType);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : User Common DDC Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciHandler(void)
{
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
    if(GET_RUN_DDCCI_COMMAND() == _FAIL)
    {
        if(GET_RECEIVE_DDCCI_CMD_NOT_FINISH() == _SUCCESS)
        {
            // Polling User Ddcci Cmd Finished
            ScalerTimerActiveTimerEvent(_CLR_DDCCI_CMD_RECEIVE_NOT_FINISH_TIMEOUT, _SYSTEM_TIMER_EVENT_CLR_DDCCI_RECEIVE_COMMAND_NOT_FINISH);
        }
        else
        {
            if(GET_DDCCI_AUTO_SWITCH() == _FALSE)
            {
                // Enable DDCCI Channel Auto Switch
                SET_DDCCI_AUTO_SWITCH();

                // Set Other DDC Enable
                ScalerMcuDdcciAutoSwitchInactiveChannel(_ENABLE);
            }
        }
    }
#endif

    UserDdcciHandler();
}
//--------------------------------------------------
// Description  : Initial TX variables and Send Null-Message
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciInitTx(void)
{
    // Send Null-Message
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG;
    g_pucDdcciTxBuf[_DDCCI_COMMAND] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
}

//--------------------------------------------------
// Description  : Initial RX variables
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciInitRx(void)
{
    // Clear buffer for new message
    memset(g_pucDdcciRxBuf, 0, _DDCCI_RXBUF_LENGTH);
}

//--------------------------------------------------
// Description  : Caculate checksum
// Input Value  : None
// Output Value : ucSum --> Checksum value
//--------------------------------------------------
BYTE UserCommonDdcciCalCheckSum(void)
{
    BYTE ucCount = 0;
    BYTE ucCheckLen = 0;
    BYTE ucSum = _DDCCI_VIRTUAL_HOST_ADDRESS;

    ucCheckLen = (g_pucDdcciTxBuf[_DDCCI_LENGTH] & 0x7F) + 2;

    for(ucCount = 0; ucCount < ucCheckLen; ucCount++)
    {
        ucSum = ucSum ^ g_pucDdcciTxBuf[ucCount];
    }

    return ucSum;
}

#if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE != Gamma_default))    
//--------------------------------------------------
// Description  : Caculate checksum
// Input Value  : None
// Output Value : ucSum --> Checksum value
//--------------------------------------------------
BYTE UserCommonDdcciCalRxCheckSum(void)
{
    BYTE ucCount = 0;
    BYTE ucCheckLen = 0;
    BYTE ucSum = _DDCCI_DEST_ADDRESS;

    ucCheckLen = (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) + 2;

    for(ucCount = 0; ucCount < ucCheckLen; ucCount++)
    {
        ucSum = ucSum ^ g_pucDdcciRxBuf[ucCount];
    }

    return ucSum;
}
#endif

//--------------------------------------------------
// Description  : DDCCI VCP Feature Reply Max and Present Value
// Input Value  : ucOpcode --> OPCODE
//                  usMax --> Maximum Value
//                  usPresent --> Present Value
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciSetVCPReplyValue(BYTE ucTypeOpcode, WORD usMax, WORD usPresent)
{
    g_pucDdcciTxBuf[_DDCCI_TYPE_CODE] = ucTypeOpcode;
    g_pucDdcciTxBuf[_DDCCI_MAX_HIGH_BYTE] = HIBYTE(usMax);
    g_pucDdcciTxBuf[_DDCCI_MAX_LOW_BYTE] = LOBYTE(usMax);
    g_pucDdcciTxBuf[_DDCCI_PRESENT_HIGH_BYTE] = HIBYTE(usPresent);
    g_pucDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE] = LOBYTE(usPresent);
}

//--------------------------------------------------
// Description  : DDCCI Get and Reply Timing Report
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciGetTimingReport(void)
{
    BYTE ucPolarity = 0;

    ucPolarity = (GET_INPUT_TIMING_H_POLARITY() | (GET_INPUT_TIMING_V_POLARITY() << 1));

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_TIMING_MSG_COMMAND] = _DDCCI_CMD_REPLY_TIMING_MESSAGE;
    g_pucDdcciTxBuf[_DDCCI_TIMING_MSG_OPCODE] = _DDCCI_OPCODE_TIMING_MSG;
    g_pucDdcciTxBuf[_DDCCI_TIMING_STATUS] = 0x00;

    // H sync pol :Bit 1 = 1:positive H-sync polarity
    if((bit)(ucPolarity & _BIT0) == _TRUE)
    {
        g_pucDdcciTxBuf[_DDCCI_TIMING_STATUS] |= _BIT1;
    }

    // V sync pol :Bit 0 = 1:positive V-sync polarity
    if((bit)(ucPolarity & _BIT1) == _TRUE)
    {
        g_pucDdcciTxBuf[_DDCCI_TIMING_STATUS] |= _BIT0;
    }

    g_pucDdcciTxBuf[_DDCCI_TIMING_HFREQ_HBYTE] = HIBYTE(GET_INPUT_TIMING_HFREQ() * 10);
    g_pucDdcciTxBuf[_DDCCI_TIMING_HFREQ_LBYTE] = LOBYTE(GET_INPUT_TIMING_HFREQ() * 10);
    g_pucDdcciTxBuf[_DDCCI_TIMING_VFREQ_HBYTE] = HIBYTE(GET_INPUT_TIMING_VFREQ() * 10);
    g_pucDdcciTxBuf[_DDCCI_TIMING_VFREQ_LBYTE] = LOBYTE(GET_INPUT_TIMING_VFREQ() * 10);
    g_pucDdcciTxBuf[_DDCCI_TIMING_VFREQ_LBYTE + 1] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
}

//--------------------------------------------------
// Description  : DDCCI Capabilities Request & Reply
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciGetCapabilitiesRequest(void)
{
    WORD usOffset = 0;
    BYTE ucSendLen = 0;
    EnumInputPortType enumPortType = GET_PORT_TYPE(SysSourceGetInputPortType(ScalerMcuDdcciGetInputPort()));

    WORD usCreqLen = UserCommonDdcciGetCpStringSize(enumPortType);

    usOffset = ((((WORD)g_pucDdcciRxBuf[_DDCCI_OFS_HIGH_BYTE]) << 8) & 0xFF00) | (g_pucDdcciRxBuf[_DDCCI_OFS_LOW_BYTE]);

    if(usOffset >= usCreqLen)
    {
        ucSendLen = 0;
    }
    else if(usCreqLen > (usOffset + ScalerMcuDdcciGetBufferSize() - 6))
    {
        ucSendLen = ScalerMcuDdcciGetBufferSize() - 6;
    }
    else
    {
        ucSendLen = usCreqLen - usOffset;
    }

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | (ucSendLen + 3);
    g_pucDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_CAPABILITIES_REQUEST_REPLY;
    g_pucDdcciTxBuf[_DDCCI_OFS_HIGH_BYTE] = g_pucDdcciRxBuf[_DDCCI_OFS_HIGH_BYTE];
    g_pucDdcciTxBuf[_DDCCI_OFS_LOW_BYTE] = g_pucDdcciRxBuf[_DDCCI_OFS_LOW_BYTE];

    UserCommonDdcciGetCpStringData(&g_pucDdcciTxBuf[_DDCCI_OFS_LOW_BYTE + 1], enumPortType, usOffset, ucSendLen);

    g_pucDdcciTxBuf[_DDCCI_OFS_LOW_BYTE + 1 + ucSendLen] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
}

//--------------------------------------------------
// Description  : Get capability string data
// Input Value  : pucDest -> destination
//                enumPortType -> port type
//                usStartIndex -> data offset
//                usLength -> data length
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciGetCpStringData(BYTE *pucDest, EnumInputPortType enumPortType, WORD usStartIndex, WORD usLength)
{
#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _ON)

    UserInterfaceDdcciGetCpStringData(pucDest, enumPortType, usStartIndex, usLength);

#else

    switch(enumPortType)
    {
#if(_VGA_PORT_EXIST == _ON)
        case _PORT_VGA:
            memcpy(pucDest, &tCP_STRING_DSUB[usStartIndex], usLength);
            break;
#endif

#if(_DVI_PORT_EXIST == _ON)
        case _PORT_DVI:
        case _PORT_DUAL_DVI:
            memcpy(pucDest, &tCP_STRING_DVI[usStartIndex], usLength);
            break;
#endif

#if(_HDMI_PORT_EXIST == _ON)
        case _PORT_HDMI:
        case _PORT_MHL:
        case _PORT_HDMI20:
            memcpy(pucDest, &tCP_STRING_HDMI[usStartIndex], usLength);
            break;
#endif

#if(_DP_PORT_EXIST == _ON)
        case _PORT_DP:
            memcpy(pucDest, &tCP_STRING_DP[usStartIndex], usLength);
            break;
#endif

        default:
            break;
    }

#endif
}

//--------------------------------------------------
// Description  : Get capability string size
// Input Value  : enumPortType -> port type
// Output Value : size
//--------------------------------------------------
WORD UserCommonDdcciGetCpStringSize(EnumInputPortType enumPortType)
{
#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _ON)

    return UserInterfaceDdcciGetCpStringSize(enumPortType);

#else

    switch(enumPortType)
    {
#if(_VGA_PORT_EXIST == _ON)
        case _PORT_VGA:
            return (sizeof(tCP_STRING_DSUB) - 1);
#endif

#if(_DVI_PORT_EXIST == _ON)
        case _PORT_DVI:
        case _PORT_DUAL_DVI:
            return (sizeof(tCP_STRING_DVI) - 1);
#endif

#if(_HDMI_PORT_EXIST == _ON)
        case _PORT_HDMI:
        case _PORT_MHL:
        case _PORT_HDMI20:
            return (sizeof(tCP_STRING_HDMI) - 1);
#endif

#if(_DP_PORT_EXIST == _ON)
        case _PORT_DP:
            return (sizeof(tCP_STRING_DP) - 1);
#endif

        default:
            return 0;
    }

#endif
}

#endif  // #if(_DDCCI_CODE_REDUCTION == _OFF)
