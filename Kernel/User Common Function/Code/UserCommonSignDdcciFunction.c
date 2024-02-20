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
// ID Code      : UserCommonSignDdcciFunction.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_SIGN_DDCCI_FUNCTION__

#include "UserCommonInclude.h"

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tISP_ADDRESS_N[] =
{
    0x00, _SIGNATURE_INTERNAL_ISP_START_BANK, 0x00, 0x00
};

BYTE code tISP_ADDRESS_M[] =
{
    0x00, (_SIGNATURE_INTERNAL_ISP_START_BANK + _SIGNATURE_INTERNAL_BIN_BANK_SIZE), 0x00, 0x00
};
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonSignDdcciHandler(void);
void UserCommonSignDdcciGetISPInfo(BYTE *pucArray);
BYTE UserCommonSignDdcciGetSignStatus(void);
void UserCommonSignDdcciSetSwitchCode(void);
BYTE UserCommonSignDdcciCalCheckSum(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Digital Signature DDCCI CMD Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonSignDdcciHandler(void)
{
    BYTE ucLength = 0;
    BYTE ucIndex = 0;
    BYTE pucArray[8];
    memset(pucArray, 0, sizeof(pucArray));

    if(GET_RUN_DDCCI_COMMAND() == _SUCCESS)
    {
        if(g_pucDdcciRxBuf[_DDCCI_SIGN_SUB_ADDR] != _DDCCI_SIGN_TEST_SUB_ADDR)
        {
            return;
        }

        if(g_pucDdcciRxBuf[_DDCCI_SIGN_CMD_TYPE] != _DDCCI_SIGN_TEST_CMD_TYPE)
        {
            return;
        }

        g_pucDdcciTxBuf[_DDCCI_SIGN_SUB_ADDR] = _DDCCI_DEST_ADDRESS;
        g_pucDdcciTxBuf[_DDCCI_SIGN_CMD_TYPE] = _DDCCI_SIGN_TEST_CMD_TYPE;

        switch(g_pucDdcciRxBuf[_DDCCI_SIGN_OPCODE])
        {
            case _DDCCI_OPCODE_SIGN_GET_ISP_STATUS_REQ:

                ucLength = 0x0A;
                UserCommonSignDdcciGetISPInfo(pucArray);
                g_pucDdcciTxBuf[_DDCCI_SIGN_LENGTH] = ucLength;
                g_pucDdcciTxBuf[_DDCCI_SIGN_OPCODE] = _DDCCI_OPCODE_SIGN_GET_ISP_STATUS_REPLY;
                memcpy(&g_pucDdcciTxBuf[_DDCCI_SIGN_DATAOUT], pucArray, 8);
                g_pucDdcciTxBuf[2 + ucLength] = UserCommonSignDdcciCalCheckSum();

                break;

            case _DDCCI_OPCODE_SIGN_GET_SIGN_STATUS_REQ:

                ucLength = 0x03;
                g_pucDdcciTxBuf[_DDCCI_SIGN_LENGTH] = ucLength;
                g_pucDdcciTxBuf[_DDCCI_SIGN_OPCODE] = _DDCCI_OPCODE_SIGN_GET_SIGN_STATUS_REPLY;
                g_pucDdcciTxBuf[_DDCCI_SIGN_DATAOUT] = UserCommonSignDdcciGetSignStatus();
                g_pucDdcciTxBuf[2 + ucLength] = UserCommonSignDdcciCalCheckSum();

                break;

            case _DDCCI_OPCODE_SIGN_SET_SWITCH_CODE_REQ:

                UserCommonSignDdcciSetSwitchCode();

                break;

            case _DDCCI_OPCODE_SIGN_GET_READY_STATUS_REQ:
                ucLength = 0x03;
                g_pucDdcciTxBuf[_DDCCI_SIGN_LENGTH] = ucLength;
                g_pucDdcciTxBuf[_DDCCI_SIGN_OPCODE] = _DDCCI_OPCODE_SIGN_GET_READY_STATUS_REPLY;
                g_pucDdcciTxBuf[_DDCCI_SIGN_DATAOUT] = _SCALER_READY_STATUS;
                g_pucDdcciTxBuf[2 + ucLength] = UserCommonSignDdcciCalCheckSum();

                break;

            case _DDCCI_OPCODE_SIGN_HANDSHAKE_CHECK_REQ:
                ucLength = 0x03;
                g_pucDdcciTxBuf[_DDCCI_SIGN_LENGTH] = ucLength;
                g_pucDdcciTxBuf[_DDCCI_SIGN_OPCODE] = _DDCCI_OPCODE_SIGN_HANDSHAKE_CHECK_REPLY;
                g_pucDdcciTxBuf[_DDCCI_SIGN_DATAOUT] = _DDCCI_SIGN_HANDSHAKE_CHECK_PASS;
                g_pucDdcciTxBuf[2 + ucLength] = UserCommonSignDdcciCalCheckSum();
                break;

            case _DDCCI_OPCODE_SIGN_HANDSHAKE_ENABLE_ISP_REQ:
                ucLength = 0x03;
                ucIndex = _DDCCI_SIGN_OPCODE;
                if((g_pucDdcciRxBuf[ucIndex + 3] == 'R') &&
                   (g_pucDdcciRxBuf[ucIndex + 6] == 'E') &&
                   (g_pucDdcciRxBuf[ucIndex + 9] == 'A') &&
                   (g_pucDdcciRxBuf[ucIndex + 12] == 'L') &&
                   (g_pucDdcciRxBuf[ucIndex + 15] == 'T') &&
                   (g_pucDdcciRxBuf[ucIndex + 18] == 'E') &&
                   (g_pucDdcciRxBuf[ucIndex + 21] == 'C') &&
                   (g_pucDdcciRxBuf[ucIndex + 24] == 'H'))
                {
                    g_pucDdcciTxBuf[_DDCCI_SIGN_LENGTH] = ucLength;
                    g_pucDdcciTxBuf[_DDCCI_SIGN_OPCODE] = _DDCCI_OPCODE_SIGN_HANDSHAKE_ENABLE_ISP_REPLY;
                    g_pucDdcciTxBuf[_DDCCI_SIGN_DATAOUT] = _DDCCI_SIGN_HANDSHAKE_ENABLE_ISP_PASS;
                    g_pucDdcciTxBuf[2 + ucLength] = UserCommonSignDdcciCalCheckSum();

                    // Enable selected ISP channels
                    ScalerMcuSetISPChannel(_CODE_DIGITAL_SIGNATURE_ISP_SEL_EN);

                    // Set Right ISP Slave Address
                    ScalerMcuSetISPSlaveAddr(_ENABLE);
                }
                break;

            case _DDCCI_OPCODE_SIGN_CHANGE_TO_DEBUG_MODE:
                // Return DDCCI to Normal Judge Mode
                ScalerDebugClrDdcciSwitchState();
                // Switch DDCCI to Debug Mode, No Matter Which Port as Auto-Switch
                ScalerMcuDdcciSwitchPort(_DEBUG_MODE, _A0_INPUT_PORT);
                break;

            default:
                return;
        }

        ScalerMcuDdcciSendData(g_pucDdcciTxBuf);

        UserCommonDdcciInitRx();

        SET_RUN_DDCCI_COMMAND(_FAIL);
    }
}

//--------------------------------------------------
// Description  : Get ISP Info
// Input Value  : None
// Output Value : *pucArray
//--------------------------------------------------
void UserCommonSignDdcciGetISPInfo(BYTE *pucArray)
{
    BYTE ucSwitchFlagN = 0;
    BYTE ucRunPriN = 0;
    BYTE ucSwitchFlagM = 0;
    BYTE ucRunPriM = 0;
    WORD usInfoDataPage = 0;
    BYTE code *pucISPAddress = tISP_ADDRESS_N;

    // read N's Switch code status
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SWITCH_TAG_OFFSET_ADDR), 1, &ucSwitchFlagN);

    // read M's Switch code status
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _SWITCH_TAG_OFFSET_ADDR), 1, &ucSwitchFlagM);

    // user code all OK, judge run priority
    if((ucSwitchFlagN == _SWITCH_OK_TAG) && (ucSwitchFlagM == _SWITCH_OK_TAG))
    {
        // read N's run priority
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _RUN_PRI_OFFSET_ADDR), 1, &ucRunPriN);

        // read M's run priority
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _RUN_PRI_OFFSET_ADDR), 1, &ucRunPriM);

        // N priority higher, so return M ISP address & N FW version(at M info block)
        if((ucRunPriN > ucRunPriM) || ((ucRunPriN == 0x00) && (ucRunPriM == 0xFF)))
        {
            usInfoDataPage = _INFO_DATA_M_PAGE;
            pucISPAddress = tISP_ADDRESS_M;
        }
        else if((ucRunPriM > ucRunPriN) || ((ucRunPriM == 0x00) && (ucRunPriN == 0xFF)))
        {
            usInfoDataPage = _INFO_DATA_N_PAGE;
            pucISPAddress = tISP_ADDRESS_N;
        }
    }
    // only one usercode OK, return OK's FW version & opposite ISP address
    else if((ucSwitchFlagN == _SWITCH_OK_TAG) || (ucSwitchFlagM == _SWITCH_OK_TAG))
    {
        if(ucSwitchFlagN == _SWITCH_OK_TAG)
        {
            usInfoDataPage = _INFO_DATA_M_PAGE;
            pucISPAddress = tISP_ADDRESS_M;
        }
        else
        {
            usInfoDataPage = _INFO_DATA_N_PAGE;
            pucISPAddress = tISP_ADDRESS_N;
        }
    }
    // all usercode not OK, mean bootcode, return N ISP address & bootcode FW version
    else
    {
        usInfoDataPage = _INFO_DATA_N_PAGE;
        pucISPAddress = tISP_ADDRESS_N;
    }

    // get FW version of bootcode from N info block
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(usInfoDataPage << 12) + _FW_VERSION_OFFSET_ADDR), 4, pucArray);

    // get N ISP address
    memcpy(&pucArray[4], pucISPAddress, 4);
}

//--------------------------------------------------
// Description  : Get Signature Status
// Input Value  : None
// Output Value : _SIGN_PASS or _SIGN_FAIL
//--------------------------------------------------
BYTE UserCommonSignDdcciGetSignStatus(void)
{
    BYTE ucSwitchFlagN = 0;
    BYTE ucSignFlagN = 0;
    BYTE ucSwitchFlagM = 0;
    BYTE ucSignFlagM = 0;

    // read N's Switch code status
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SWITCH_TAG_OFFSET_ADDR), 1, &ucSwitchFlagN);
    // read M's Switch code status
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _SWITCH_TAG_OFFSET_ADDR), 1, &ucSwitchFlagM);

    // user code all switch OK, invaild read Sign status CMD
    if((ucSwitchFlagN == _SWITCH_OK_TAG) && (ucSwitchFlagM == _SWITCH_OK_TAG))
    {
        return _SIGN_INVAILD_TAG;
    }
    // only one usercode switch OK, return opposite Sign Status
    else if((ucSwitchFlagN == _SWITCH_OK_TAG) || (ucSwitchFlagM == _SWITCH_OK_TAG))
    {
        // N has working usercode, return M tag sign status
        if(ucSwitchFlagN == _SWITCH_OK_TAG)
        {
            // read M's sign status
            UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _SIGN_TAG_OFFSET_ADDR), 1, &ucSignFlagM);
            if(ucSignFlagM == _SIGN_PASS_TAG)
            {
                return _SIGN_PASS_TAG;
            }
            else if(ucSignFlagM == _SIGN_FAIL_TAG)
            {
                return _SIGN_FAIL_TAG;
            }
            else
            {
                return _SIGN_INVAILD_TAG;
            }
        }
        // M has working usercode, return N tag sign status
        else
        {
            // read N's Sign status
            UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SIGN_TAG_OFFSET_ADDR), 1, &ucSignFlagN);
            if(ucSignFlagN == _SIGN_PASS_TAG)
            {
                return _SIGN_PASS_TAG;
            }
            else if(ucSignFlagN == _SIGN_FAIL_TAG)
            {
                return _SIGN_FAIL_TAG;
            }
            else
            {
                return _SIGN_INVAILD_TAG;
            }
        }
    }
    // all usercode switch not OK, mean first ISP, return N tag of Sign status
    else
    {
        // read N's Sign status
        UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SIGN_TAG_OFFSET_ADDR), 1, &ucSignFlagN);
        if(ucSignFlagN == _SIGN_PASS_TAG)
        {
            return _SIGN_PASS_TAG;
        }
        else if(ucSignFlagN == _SIGN_FAIL_TAG)
        {
            return _SIGN_FAIL_TAG;
        }
        else
        {
            return _SIGN_INVAILD_TAG;
        }
    }
}

//--------------------------------------------------
// Description  : Set Switch code Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonSignDdcciSetSwitchCode(void)
{
    BYTE ucSwitchFlagN = 0;
    BYTE ucSignFlagN = 0;
    BYTE ucSwitchFlagM = 0;
    BYTE ucSignFlagM = 0;
    BYTE ucTemp = _SWITCH_OK_TAG;

    // read N's Switch code status
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SWITCH_TAG_OFFSET_ADDR), 1, &ucSwitchFlagN);
    // read N's Sign status
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SIGN_TAG_OFFSET_ADDR), 1, &ucSignFlagN);

    // read M's Switch code status
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _SWITCH_TAG_OFFSET_ADDR), 1, &ucSwitchFlagM);
    // read M's sign status
    UserCommonFlashRead(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _SIGN_TAG_OFFSET_ADDR), 1, &ucSignFlagM);

    // all usercode switch OK, return
    if((ucSwitchFlagN == _SWITCH_OK_TAG) && (ucSwitchFlagM == _SWITCH_OK_TAG))
    {
        return;
    }
    // only one usercode switch OK,
    else if((ucSwitchFlagN == _SWITCH_OK_TAG) || (ucSwitchFlagM == _SWITCH_OK_TAG))
    {
        // N switch OK, if M Sign Pass, set M Switch OK
        if((ucSwitchFlagN == _SWITCH_OK_TAG) && (ucSignFlagM == _SIGN_PASS_TAG))
        {
            UserCommonFlashWrite(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_M_PAGE << 12) + _SWITCH_TAG_OFFSET_ADDR), 1, &ucTemp);
        }
        // M switch OK, if N Sign Pass, set N Switch OK
        else if((ucSwitchFlagM == _SWITCH_OK_TAG) && (ucSignFlagN == _SIGN_PASS_TAG))
        {
            UserCommonFlashWrite(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SWITCH_TAG_OFFSET_ADDR), 1, &ucTemp);
        }
        // other case return
        else
        {
            return;
        }
    }
    // none usercode ever switch OK, mean in bootcode, then default judge N
    else
    {
        if(ucSignFlagN == _SIGN_PASS_TAG)
        {
            UserCommonFlashWrite(_SIGN_PROTECT_DATA_BANK, ((WORD)(_TAG_FLAG_N_PAGE << 12) + _SWITCH_TAG_OFFSET_ADDR), 1, &ucTemp);
        }
        else
        {
            return;
        }
    }
}

//--------------------------------------------------
// Description  : Caculate checksum
// Input Value  : None
// Output Value : ucSum --> Checksum value
//--------------------------------------------------
BYTE UserCommonSignDdcciCalCheckSum(void)
{
    BYTE ucCount = 0;
    BYTE ucCheckLen = 0;
    BYTE ucSum = _DDCCI_SIGN_VIRTUAL_HOST_ADDRESS;

    ucCheckLen = (g_pucDdcciTxBuf[_DDCCI_SIGN_LENGTH] & 0x7F) + 2;

    for(ucCount = 0; ucCount < ucCheckLen; ucCount++)
    {
        ucSum = ucSum ^ g_pucDdcciTxBuf[ucCount];
    }

    return ucSum;
}
#endif // #if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
