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
// ID Code      : UserCommonScalerDataExchange.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DATA_EXCHANGE__

#include "UserCommonInclude.h"

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of IIC Tx Protocol Items
//--------------------------------------------------
#define _DATA_EXCHAGNE_TX_LENGTH                                0
#define _DATA_EXCHAGNE_TX_COMMAND_TYPE                          1
#define _DATA_EXCHAGNE_TX_START_ADDR                            2

//--------------------------------------------------
// Definitions of Data Exchange Transmit Info
//--------------------------------------------------
#define GET_DATA_EXCHANGE_TX_EVENT()                            (g_stD0DataExchange.enumEvent)
#define SET_DATA_EXCHANGE_TX_EVENT(x)                           (g_stD0DataExchange.enumEvent = (x))

//--------------------------------------------------
// Definitions of Data Exchange Transmit Command Count
//--------------------------------------------------
#define GET_DATA_EXCHANGE_COMMAND_COUNT()                       (g_stD0DataExchange.ucCommandCount)
#define CLR_DATA_EXCHANGE_COMMAND_COUNT()                       (g_stD0DataExchange.ucCommandCount = 0)
#define INCREASE_DATA_EXCHANGE_COMMAND_COUNT()                  (g_stD0DataExchange.ucCommandCount++)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructDataExchange g_stD0DataExchange;
StructDataExchangeMultiOsdItems g_stMultiOsdItems;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonDataExchangeInit(void);
bit UserCommonDataExchangeInitSyncUpdevice(void);
void UserCommonDataExchangeSendInitDataItem(void);
void UserCommonDataExchangeHandler(void);
void UserCommonDataExchangeTxProc(void);
bit UserCommonDataExchangeTx(void);
bit UserCommonDataExchangeGetBusyStatus(BYTE ucTimeout);
bit UserCommonDataExchangeWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucCmd, WORD usLength, BYTE *pucWriteArray, BYTE ucOffset, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
bit UserCommonDataExchangeWriteData(BYTE ucSlaveAddr, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
bit UserCommonDataExchangeReadReply(BYTE *pucArray, BYTE ucLength);
void UserCommonDataExchangeSetEvent(EnumDataExchangeCmdType enumEvent);
EnumDataExchangeCmdType UserCommonDataExchangeGetEvent(void);
bit UserCommonDataExchangeSendDataUser(EnumDataExchangeCmdType enumCmdType, BYTE *pucWriteDataArray, BYTE ucLength);
bit UserCommonDataExchangeGetDataUser(EnumDataExchangeCmdType enumCmdType, BYTE *pucGetDataArray, BYTE ucLength);
bit UserCommonDataExchangeGetDataKernel(EnumDataExchangeCmdType enumCmdType, BYTE *pucGetDataArray, BYTE ucLength);
EnumDataExchangeItemType UserCommonDataExchangeGetItemType(void);
void UserCommonDataExchangeCommandJudge(void);
void UserCommonDataExchangeSyncMultiOsdItems(EnumDataExchangeCmdType enumCmdType);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Data Exchange Init Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDataExchangeInit(void)
{
    EnumDataExchangeCmdType enumEventCnt = 0;

    if(UserCommonDataExchangeInitSyncUpdevice() == _TRUE)
    {
        DebugMessageSystem("0. Init... Data Exchange Tx", 0);

        for(enumEventCnt = _DATA_EXCHAGNE_CMD_AC_ON_START; enumEventCnt < _DATA_EXCHAGNE_CMD_AC_ON_END; enumEventCnt++)
        {
            SET_DATA_EXCHANGE_TX_EVENT(enumEventCnt);

            DebugMessageSystem("0. Sent Init Event", enumEventCnt);

            UserCommonDataExchangeSendInitDataItem();
        }

        DebugMessageSystem("0. Init... Data Exchange Fnished", 1);
    }
}

//--------------------------------------------------
// Description  : AC On init sync Updevice
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserCommonDataExchangeInitSyncUpdevice(void)
{
    WORD usWaitSyncUpdeviceTime = 50;

    DebugMessageSystem("0. Init... Sync Updevice", 1);

    SET_DATA_EXCHANGE_TX_EVENT(_DATA_EXCHAGNE_CMD_NOTIFY_UP_DEVICE_INIT_START);

    UserCommonDataExchangeSendInitDataItem();

    // Wait Slave turn to Idle Max Time is 500ms
    while(--usWaitSyncUpdeviceTime > 0)
    {
        if(UserCommonDataExchangeGetBusyStatus(10) == _FALSE)
        {
            break;
        }

        DebugMessageSystem("Initial Sync Data Wait Time", _TRUE);

        ScalerDebug();
    }

    SET_DATA_EXCHANGE_TX_EVENT(_DATA_EXCHAGNE_CMD_NONE);

    if(usWaitSyncUpdeviceTime > 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Scaler Data Exchange Get Init Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDataExchangeSendInitDataItem(void)
{
    BYTE ucItemTimeOut = 5;

    switch(GET_DATA_EXCHANGE_TX_EVENT())
    {
        case _DATA_EXCHAGNE_CMD_NOTIFY_UP_DEVICE_INIT_START:
            g_stD0DataExchange.unionDataExchangeItem.stInitStartCheck.ucCheckCode0 = _DATA_EXCHANGE_START_CHECK_CODE0;
            g_stD0DataExchange.unionDataExchangeItem.stInitStartCheck.ucCheckCode1 = _DATA_EXCHANGE_START_CHECK_CODE1;
            break;

        case _DATA_EXCHAGNE_CMD_POWER_STATUS:
            g_stD0DataExchange.unionDataExchangeItem.stPowerStatus.b1PowerStatus = UserCommonNVRamGetSystemData(_MONITOR_POWER_STATUS);
            break;

        case _DATA_EXCHAGNE_CMD_DDC_CI_MODE:
            g_stD0DataExchange.unionDataExchangeItem.stDdcciMode.b1DdcciStatus = UserInterfaceGetDdcciMode();
            break;

        case _DATA_EXCHAGNE_CMD_DCOFF_HPD_MODE:
            g_stD0DataExchange.unionDataExchangeItem.stDcoffHpdMode.b1DPHotPlugDCOffHigh = UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH);
            break;

        case _DATA_EXCHAGNE_CMD_AUX_DIFF_MODE:
            g_stD0DataExchange.unionDataExchangeItem.stAuxDiffMode.b1DPAuxDiffMode = UserCommonNVRamGetSystemData(_DP_AUX_DIFF_MODE);
            break;

        case _DATA_EXCHAGNE_CMD_AUX_ADJR_MODE:
            g_stD0DataExchange.unionDataExchangeItem.stAuxAdjr.b4DPAuxAdjrSetting = UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING);
            break;

        case _DATA_EXCHAGNE_CMD_DP_IRQ_TIME:
            g_stD0DataExchange.unionDataExchangeItem.stIrqTime.ucDpIrqTime_10us = UserCommonNVRamGetSystemData(_DP_IRQ_TIME);
            break;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_U3_ON_OFF:
            if(UserInterfaceTypeCGetOsdU3ModeSelection(_D0_INPUT_PORT) == _TYPE_C_U3_ON)
            {
                g_stD0DataExchange.unionDataExchangeItem.stU3Mode.enumTypeCU3OnOff = _DATA_EXCHANGE_U3_ON;
            }
            else
            {
                g_stD0DataExchange.unionDataExchangeItem.stU3Mode.enumTypeCU3OnOff = _DATA_EXCHANGE_U3_OFF;
            }
            break;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_DP_FREESYNC_STATUS:
            if(UserInterfaceGetFreeSyncEnable(_D0_INPUT_PORT) == _FREESYNC_SUPPORT_ON)
            {
                g_stD0DataExchange.unionDataExchangeItem.stDpFreeSync.enumFreeSyncOnOff = _DATA_EXCHANGE_DP_FREESYNC_SUPPORT_ON;
            }
            else
            {
                g_stD0DataExchange.unionDataExchangeItem.stDpFreeSync.enumFreeSyncOnOff = _DATA_EXCHANGE_DP_FREESYNC_SUPPORT_OFF;
            }

            break;
#endif

        case _DATA_EXCHAGNE_CMD_DP_VERSION:
            switch(UserInterfaceGetDPVersion(_D0_INPUT_PORT))
            {
                case _DP_VERSION_1_0:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_0;
                    break;

                case _DP_VERSION_1_1:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_1;
                    break;

                case _DP_VERSION_1_2:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_2;
                    break;

                case _DP_VERSION_1_4:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_4;
                    break;

                default:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumVersion = _DATA_EXCHANGE_DP_VERSION_1_1;
                    break;
            }

#if(_DP_MST_SUPPORT == _ON)
            switch(UserInterfaceGetDpMSTCapablePort())
            {
                case _DP_MST_RX0_PORT:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumMstPort = _DATA_EXCHANGE_DP_MST_RX0_PORT;

                    break;

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                case _DP_MST_AUTO_PORT:

                    if(UserInterfaceGetDPVersion(_D0_INPUT_PORT) >= _DP_VERSION_1_2)
                    {
                        g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumMstPort = _DATA_EXCHANGE_DP_MST_RX0_PORT;
                    }
                    else
                    {
                        g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumMstPort = _DATA_EXCHANGE_DP_MST_NO_PORT;
                    }

                    break;
#endif

                default:
                    g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumMstPort = _DATA_EXCHANGE_DP_MST_NO_PORT;
                    break;
            }
#else
            g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumMstPort = _DATA_EXCHANGE_DP_MST_NO_PORT;
#endif

            break;

#if(_DP_MST_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_MST_ON_OFF:

            switch(UserInterfaceGetDpMSTCapablePort())
            {
                case _DP_MST_RX0_PORT:
                    g_stD0DataExchange.unionDataExchangeItem.stMstOnOff.enumMstPort = _DATA_EXCHANGE_DP_MST_RX0_PORT;

                    break;

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
                case _DP_MST_AUTO_PORT:

                    if(UserInterfaceGetDPVersion(_D0_INPUT_PORT) >= _DP_VERSION_1_2)
                    {
                        g_stD0DataExchange.unionDataExchangeItem.stMstOnOff.enumMstPort = _DATA_EXCHANGE_DP_MST_RX0_PORT;
                    }
                    else
                    {
                        g_stD0DataExchange.unionDataExchangeItem.stMstOnOff.enumMstPort = _DATA_EXCHANGE_DP_MST_NO_PORT;
                    }

                    break;
#endif
                default:
                    g_stD0DataExchange.unionDataExchangeItem.stMstOnOff.enumMstPort = _DATA_EXCHANGE_DP_MST_NO_PORT;
                    break;
            }

            break;
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_PIN_ASSIGNMENT_E_SUPPORT_ON_OFF:
            if(UserInterfaceTypeCGetOsdPinAssignmentESupportSelection(_D0_INPUT_PORT) == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
            {
                g_stD0DataExchange.unionDataExchangeItem.stPinAssignmentESupportOnOff.enumPinAssignmentESupportOnOff = _DATA_EXCHANGE_PIN_ASSIGNMENT_E_SUPPORT_ON;
            }
            else
            {
                g_stD0DataExchange.unionDataExchangeItem.stPinAssignmentESupportOnOff.enumPinAssignmentESupportOnOff = _DATA_EXCHANGE_PIN_ASSIGNMENT_E_SUPPORT_OFF;
            }
            break;
#endif
#endif

        case _DATA_EXCHAGNE_CMD_FINISHED_CHECK:
            g_stD0DataExchange.unionDataExchangeItem.stFinishedCheck.ucCheckCode0 = _DATA_EXCHANGE_FINISHED_CHECK_CODE0;
            g_stD0DataExchange.unionDataExchangeItem.stFinishedCheck.ucCheckCode1 = _DATA_EXCHANGE_FINISHED_CHECK_CODE1;
            break;

        default:
            break;
    }

    // Sync Multi Osd Item Data
    UserCommonDataExchangeSyncMultiOsdItems(GET_DATA_EXCHANGE_TX_EVENT());

    // Check Current Item Send Successful ?
    do
    {
        UserCommonDataExchangeTxProc();

        // Wait for Busy Interval
        ScalerTimerDelayXms(5);
    }
    while((GET_DATA_EXCHANGE_TX_EVENT() != _DATA_EXCHAGNE_CMD_NONE) && (--ucItemTimeOut > 0));
}

//--------------------------------------------------
// Description  : User Common Data Exchange Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDataExchangeHandler(void)
{
    UserCommonDataExchangeCommandJudge();

    UserCommonDataExchangeTxProc();
}

//--------------------------------------------------
// Description  : User Common Data Exchange Handler Tx Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDataExchangeTxProc(void)
{
    if(GET_DATA_EXCHANGE_TX_EVENT() != _DATA_EXCHAGNE_CMD_NONE)
    {
        if(UserCommonDataExchangeTx() == _TRUE)
        {
            SET_DATA_EXCHANGE_TX_EVENT(_DATA_EXCHAGNE_CMD_NONE);
            CLR_DATA_EXCHANGE_COMMAND_COUNT();
        }
    }
}

//--------------------------------------------------
// Description  : Scaler Data Exchange Handler Tx Process
// Input Value  : None
// Output Value : return _TRUE/ _FALSE
//--------------------------------------------------
bit UserCommonDataExchangeTx(void)
{
    bit bTransFlag = _TRUE;
    BYTE ucSlaveAddr = _DP_REPEATER_SLAVE_ADDR;
    BYTE *pucWriteArray = 0;
    WORD usLength = 0;
    EnumDataExchangeTypeGroup enumDataExType = _DATA_EXCHANGE_DATA_KERNEL;
    EnumDataExchangeCmdType enumCmdType = GET_DATA_EXCHANGE_TX_EVENT();

    // Check Repeater Power Status
    if(GET_PCB_TWO_CHIP_REPEATER_POW_STATUS() == _TWO_CHIP_REPEATER_POWER_OFF)
    {
        SET_DATA_EXCHANGE_TX_EVENT(_DATA_EXCHAGNE_CMD_NONE);

        return _FALSE;
    }

    if(UserCommonDataExchangeGetBusyStatus(10) == _TRUE)
    {
        return _FALSE;
    }

    pucWriteArray = BYTEPTR(g_stD0DataExchange.unionDataExchangeItem);

    switch(GET_DATA_EXCHANGE_TX_EVENT())
    {
        case _DATA_EXCHAGNE_CMD_NOTIFY_UP_DEVICE_INIT_START:
            usLength = sizeof(StructDataExchangeInitStartCheck);
            break;

        case _DATA_EXCHAGNE_CMD_POWER_STATUS:
            usLength = sizeof(StructDataExchangePowerStatus);
            break;

        case _DATA_EXCHAGNE_CMD_DDC_CI_MODE:
            usLength = sizeof(StructDataExchangeDdcciMode);
            break;

        case _DATA_EXCHAGNE_CMD_DCOFF_HPD_MODE:
            usLength = sizeof(StructDataExchangeDcoffHpdMode);
            break;

        case _DATA_EXCHAGNE_CMD_AUX_DIFF_MODE:
            usLength = sizeof(StructDataExchangeAuxDiffMode);
            break;

        case _DATA_EXCHAGNE_CMD_AUX_ADJR_MODE:
            usLength = sizeof(StructDataExchangeAuxAdjr);
            break;

        case _DATA_EXCHAGNE_CMD_DP_IRQ_TIME:
            usLength = sizeof(StructDataExchangeIrqTime);
            break;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_U3_ON_OFF:
            usLength = sizeof(StructDataExchangeU3Mode);
            break;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_DP_FREESYNC_STATUS:
            usLength = sizeof(StructDataExchangeDpFreesync);
            break;
#endif

        case _DATA_EXCHAGNE_CMD_DP_VERSION:
            usLength = sizeof(StructDataExchangeDpVersion);
            break;

#if(_DP_MST_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_MST_ON_OFF:
            usLength = sizeof(StructDataExchangeDpMstOnOff);
            break;
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_PIN_ASSIGNMENT_E_SUPPORT_ON_OFF:
            usLength = sizeof(StructDataExchangePinAssignmentESupportOnOff);
            break;
#endif
#endif

        case _DATA_EXCHAGNE_CMD_FINISHED_CHECK:
            usLength = sizeof(StructDataExchangeFinished);
            break;

        case _DATA_EXCHAGNE_CMD_ALL_DATA_RESET:
            usLength = sizeof(StructDataExchangeAllDataReset);
            break;

        case _DATA_EXCHAGNE_CMD_MULTI_ITEMS:
            pucWriteArray = BYTEPTR(g_stMultiOsdItems.stPowerStatus);
            usLength = sizeof(StructDataExchangeMultiOsdItems);
            break;

        case _DATA_EXCHAGNE_CMD_PAIRING_LT:
            usLength = 0;
            break;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_PAIRING_TYPE_C_FW_VERSION:
            usLength = 0;
            break;
#endif

        case _DATA_EXCHAGNE_CMD_USER_DEFINE:
            enumDataExType = _DATA_EXCHANGE_DATA_USER;

            // Get user define command type
            enumCmdType = g_stD0DataExchange.unionDataExchangeItem.stUserDefineCmd.pucData[0];

            // Get user data length
            usLength = g_stD0DataExchange.unionDataExchangeItem.stUserDefineCmd.pucData[1];

            // Filter user data extra header
            if(usLength >= 1)
            {
                pucWriteArray += 2;
            }

            break;

        default:
            bTransFlag = _FALSE;
            break;
    }

    if(bTransFlag == _TRUE)
    {
        if(UserCommonDataExchangeWrite(ucSlaveAddr, enumDataExType, enumCmdType, usLength, pucWriteArray, 0, _IIC_DATA_EXCHANGE, _DP_REPEATER_IIC) == _SUCCESS)
        {
            memset(BYTEPTR(pucWriteArray), 0, sizeof(UnionDataExchangeDataItem));

            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get device's busy status
// Input Value  : Max Polling Time
// Output Value : _TRUE: Slave is Busy _FALSE: Slave is Idle
//--------------------------------------------------
bit UserCommonDataExchangeGetBusyStatus(BYTE ucTimeout)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;
    BYTE ucTemp = 0;

    usPreviousTime = g_usTimerCounter;

    do
    {
        // Check Slave Status
        if(ScalerMcuHwIICRead(_DP_REPEATER_SLAVE_ADDR, 0, 0, 1, &ucTemp, _DP_REPEATER_IIC) == _SUCCESS)
        {
            // Slave Stay at Idle state
            if((ucTemp & _BIT0) == 0x00)
            {
                return _FALSE;
            }
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while(usTimeElapsed <= ucTimeout);

    DebugMessageSystem("0. Read HW IIC Slave Status Fail", ucTemp);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Write data to the DDC-CI Port by IIC
// Input Value  : usSubAddr     --> Start address of selected device
//                ucCmd         --> Command Type
//                usLength      --> Numbers of data we want to write
//                pReadArray    --> Result array
//                ucOffset      --> Transmit data start address
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonDataExchangeWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucCmd, WORD usLength, BYTE *pucWriteArray, BYTE ucOffset, BYTE ucSWIICStatus, BYTE ucHwIICPinNum)
{
    BYTE pucTempData[_DATA_EXCHAGNE_MAX_DATA_LEN + _DATA_EXCHAGNE_ADD_HEADER_LEN]; // + 3 for Length & Op Code & Data Array Start Address

    // Assign Actual Data Lenth
    usLength += _DATA_EXCHAGNE_ADD_HEADER_LEN;
    pucTempData[_DATA_EXCHAGNE_TX_LENGTH] = usLength;

    // Assign Comand Type Code
    pucTempData[_DATA_EXCHAGNE_TX_COMMAND_TYPE] = ucCmd;

    // Assign Data Structure Start Address
    pucTempData[_DATA_EXCHAGNE_TX_START_ADDR] = ucOffset;

    if(usLength > 0)
    {
        memcpy(&pucTempData[_DATA_EXCHAGNE_TX_START_ADDR + 1], pucWriteArray, (usLength - _DATA_EXCHAGNE_ADD_HEADER_LEN));
    }

    if(UserCommonDataExchangeWriteData(ucSlaveAddr, usSubAddr, usLength, pucTempData, ucSWIICStatus, ucHwIICPinNum) == _SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Write data to the DDC-CI Port by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to write
//                pReadArray   --> Result array
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonDataExchangeWriteData(BYTE ucSlaveAddr, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum)
{
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    BYTE ucTestCnt = 0;
#endif

    BYTE ucDataCnt = 0;

    ucSWIICStatus = ucSWIICStatus;

    if(usLength <= 0)
    {
        return _FAIL;
    }

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    for(ucTestCnt = 0; ucTestCnt < usLength; ucTestCnt++)
    {
        DebugMessageSystem("0. pucWriteArray[ucTestCnt]", pucWriteArray[ucTestCnt]);
    }
#endif

    while(usLength > 0)
    {
        // Transmit max effective data 32 bytes each time, DDC-CI Buffer Max Depth = 32 Bytes
        ucDataCnt = _DATA_EXCHAGNE_MAX_DATA_LEN + _DATA_EXCHAGNE_ADD_HEADER_LEN; // + 3 Include 3 BYTE Header

        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Execute Hardware IIC Write Command
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);
        #ifdef SW_IIC_REG_SECECT
            SW_IIC_REG_CONTROL_SECECT();
        #endif

            if(ScalerMcuIICWrite(ucSlaveAddr, 1, usSubAddr, ucDataCnt, pucWriteArray) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)
        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            if(ScalerMcuHwIICWrite(ucSlaveAddr, 1, usSubAddr, ucDataCnt, pucWriteArray, ucHwIICPinNum) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)
        }

        // Increase data location
        pucWriteArray += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Get Up Device Reply
// Input Value  : enumCmdType --> One Of EnumDataExchangeCmdType
//                pucArray    --> Received Data
//                ucLength    --> Data Length
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserCommonDataExchangeReadReply(BYTE *pucArray, BYTE ucLength)
{
    BYTE pucReadData[_DATA_EXCHAGNE_MAX_DATA_LEN] = {0};

    if(UserCommonDataExchangeGetBusyStatus(20) == _TRUE)
    {
        return _FAIL;
    }

    // HW IIC Read From Updevice IIC Slave Buffer
    if(ScalerMcuHwIICRead(_DP_REPEATER_SLAVE_ADDR, 0x00, 0x01, (ucLength + 1), pucReadData, _DP_REPEATER_IIC) == _SUCCESS)
    {
        memcpy(pucArray, &pucReadData[1], ucLength);

        return _SUCCESS;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Data Exchange Set Event
// Input Value  : enumEvent --> Need to do event
// Output Value : None
//--------------------------------------------------
void UserCommonDataExchangeSetEvent(EnumDataExchangeCmdType enumEvent)
{
    DebugMessageSystem("0. Set Event ~~ =", enumEvent);

    SET_DATA_EXCHANGE_TX_EVENT(enumEvent);

    UserCommonDataExchangeSyncMultiOsdItems(enumEvent);
}

//--------------------------------------------------
// Description  : Data Exchange Get Event
// Input Value  : None
// Output Value : EnumDataExchangeCmdType
//--------------------------------------------------
EnumDataExchangeCmdType UserCommonDataExchangeGetEvent(void)
{
    return GET_DATA_EXCHANGE_TX_EVENT();
}

//--------------------------------------------------
// Description  : Send Data to the External Device
// Input Value  : enumCmdType       --> Command Type, Only Select it in File: _USER_DATA_EXCHANGE_INCLUDE
//                pucWriteDataArray --> Send Data Array
//                usLength          --> Numbers of Data we want to write
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonDataExchangeSendDataUser(EnumDataExchangeCmdType enumCmdType, BYTE *pucWriteDataArray, BYTE ucLength)
{
    if(ucLength > _DATA_EXCHAGNE_MAX_DATA_LEN)
    {
        return _FAIL;
    }

    SET_DATA_EXCHANGE_TX_EVENT(_DATA_EXCHAGNE_CMD_USER_DEFINE);

    g_stD0DataExchange.unionDataExchangeItem.stUserDefineCmd.pucData[0] = enumCmdType;
    g_stD0DataExchange.unionDataExchangeItem.stUserDefineCmd.pucData[1] = ucLength;

    memcpy(BYTEPTR(&g_stD0DataExchange.unionDataExchangeItem.stUserDefineCmd.pucData[2]), pucWriteDataArray, ucLength);

    if(UserCommonDataExchangeTx() == _TRUE)
    {
        SET_DATA_EXCHANGE_TX_EVENT(_DATA_EXCHAGNE_CMD_NONE);

        return _SUCCESS;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Get data to from the external device
// Input Value  : enumCmdType     --> Command Type, Only Select it in file: _USER_DATA_EXCHANGE_INCLUDE
//                pucGetDataArray --> Get Data Array
//                usLength        --> Numbers of data we want to read
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonDataExchangeGetDataUser(EnumDataExchangeCmdType enumCmdType, BYTE *pucGetDataArray, BYTE ucLength)
{
    if(ucLength > _DATA_EXCHAGNE_MAX_DATA_LEN)
    {
        return _FAIL;
    }

    SET_DATA_EXCHANGE_TX_EVENT(_DATA_EXCHAGNE_CMD_USER_DEFINE);

    g_stD0DataExchange.unionDataExchangeItem.stUserDefineCmd.pucData[0] = enumCmdType;
    g_stD0DataExchange.unionDataExchangeItem.stUserDefineCmd.pucData[1] = 0;

    if(UserCommonDataExchangeTx() == _TRUE)
    {
        if(UserCommonDataExchangeReadReply(pucGetDataArray, ucLength) == _SUCCESS)
        {
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
            for(pData[0] = 0; pData[0] < ucLength; pData[0]++)
            {
                DebugMessageSystem("pucReadArray[ucCnt]", pucGetDataArray[pData[0]]);
            }
#endif
            SET_DATA_EXCHANGE_TX_EVENT(_DATA_EXCHAGNE_CMD_NONE);

            return _SUCCESS;
        }
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Get data to from the external device
// Input Value  : enumCmdType     --> Command Type, Only Select it from _DATA_EXCHAGNE_CMD_PAIRING_START to _DATA_EXCHAGNE_CMD_PAIRING_END
//                pucGetDataArray --> Get Data Array
//                usLength        --> Numbers of data we want to read
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonDataExchangeGetDataKernel(EnumDataExchangeCmdType enumCmdType, BYTE *pucGetDataArray, BYTE ucLength)
{
    if(ucLength > _DATA_EXCHAGNE_MAX_DATA_LEN)
    {
        return _FAIL;
    }

    SET_DATA_EXCHANGE_TX_EVENT(enumCmdType);

    if(UserCommonDataExchangeTx() == _TRUE)
    {
        if(UserCommonDataExchangeReadReply(pucGetDataArray, ucLength) == _SUCCESS)
        {
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
            for(pData[0] = 0; pData[0] < ucLength; pData[0]++)
            {
                DebugMessageSystem("pucReadArray[ucCnt]", pucGetDataArray[pData[0]]);
            }
#endif
            SET_DATA_EXCHANGE_TX_EVENT(_DATA_EXCHAGNE_CMD_NONE);

            return _SUCCESS;
        }
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Get Data Exchange Transfer Osd Item Type
// Input Value  : None
// Output Value : single/multi/None Osd item event type
//--------------------------------------------------
EnumDataExchangeItemType UserCommonDataExchangeGetItemType(void)
{
    if(GET_DATA_EXCHANGE_COMMAND_COUNT() >= 2)
    {
        return _DATA_EXCHANGE_ITEM_MULTI;
    }
    else if(GET_DATA_EXCHANGE_COMMAND_COUNT() == 1)
    {
        return _DATA_EXCHANGE_ITEM_SINGLE;
    }
    else
    {
        return _DATA_EXCHANGE_ITEM_NONE;
    }
}

//--------------------------------------------------
// Description  : Get Data Exchange Command Judge
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDataExchangeCommandJudge(void)
{
    EnumDataExchangeItemType enumItemType = UserCommonDataExchangeGetItemType();

    if(enumItemType == _DATA_EXCHANGE_ITEM_MULTI)
    {
        SET_DATA_EXCHANGE_TX_EVENT(_DATA_EXCHAGNE_CMD_MULTI_ITEMS);
    }
}

//--------------------------------------------------
// Description  : Sync Multi Osd Items
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDataExchangeSyncMultiOsdItems(EnumDataExchangeCmdType enumCmdType)
{
    if(enumCmdType == _DATA_EXCHAGNE_CMD_NONE)
    {
        return;
    }

    INCREASE_DATA_EXCHANGE_COMMAND_COUNT();

    DebugMessageSystem("Sync Item", enumCmdType);
    switch(enumCmdType)
    {
        case _DATA_EXCHAGNE_CMD_POWER_STATUS:
            g_stMultiOsdItems.stPowerStatus.b1PowerStatus = g_stD0DataExchange.unionDataExchangeItem.stPowerStatus.b1PowerStatus;
            break;

        case _DATA_EXCHAGNE_CMD_DDC_CI_MODE:
            g_stMultiOsdItems.stDdcciStatus.b1DdcciStatus = g_stD0DataExchange.unionDataExchangeItem.stDdcciMode.b1DdcciStatus;
            break;

        case _DATA_EXCHAGNE_CMD_DCOFF_HPD_MODE:
            g_stMultiOsdItems.stDcoffHpdMode.b1DPHotPlugDCOffHigh = g_stD0DataExchange.unionDataExchangeItem.stDcoffHpdMode.b1DPHotPlugDCOffHigh;
            break;

        case _DATA_EXCHAGNE_CMD_AUX_DIFF_MODE:
            g_stMultiOsdItems.stAuxDiffMode.b1DPAuxDiffMode = g_stD0DataExchange.unionDataExchangeItem.stAuxDiffMode.b1DPAuxDiffMode;
            break;

        case _DATA_EXCHAGNE_CMD_AUX_ADJR_MODE:
            g_stMultiOsdItems.stAuxAdjr.b4DPAuxAdjrSetting = g_stD0DataExchange.unionDataExchangeItem.stAuxAdjr.b4DPAuxAdjrSetting;
            break;

        case _DATA_EXCHAGNE_CMD_DP_IRQ_TIME:
            g_stMultiOsdItems.stIrqTime.ucDpIrqTime_10us = g_stD0DataExchange.unionDataExchangeItem.stIrqTime.ucDpIrqTime_10us;
            break;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_U3_ON_OFF:
            g_stMultiOsdItems.stU3Mode.enumTypeCU3OnOff = g_stD0DataExchange.unionDataExchangeItem.stU3Mode.enumTypeCU3OnOff;
            break;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_DP_FREESYNC_STATUS:
            g_stMultiOsdItems.stDpFreeSync.enumFreeSyncOnOff = g_stD0DataExchange.unionDataExchangeItem.stDpFreeSync.enumFreeSyncOnOff;
            break;
#endif

        case _DATA_EXCHAGNE_CMD_DP_VERSION:
            g_stMultiOsdItems.stDpVersion.enumVersion = g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumVersion;
            g_stMultiOsdItems.stDpVersion.enumMstPort = g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumMstPort;

#if(_DP_MST_SUPPORT == _ON)
            g_stMultiOsdItems.stMstOnOff.enumMstPort = g_stD0DataExchange.unionDataExchangeItem.stDpVersion.enumMstPort;
#endif
            break;

#if(_DP_MST_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_MST_ON_OFF:
            g_stMultiOsdItems.stMstOnOff.enumMstPort = g_stD0DataExchange.unionDataExchangeItem.stMstOnOff.enumMstPort;
            g_stMultiOsdItems.stDpVersion.enumMstPort = g_stD0DataExchange.unionDataExchangeItem.stMstOnOff.enumMstPort;
            break;
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
        case _DATA_EXCHAGNE_CMD_PIN_ASSIGNMENT_E_SUPPORT_ON_OFF:
            g_stMultiOsdItems.stPinAssignmentESupportOnOff.enumPinAssignmentESupportOnOff = g_stD0DataExchange.unionDataExchangeItem.stPinAssignmentESupportOnOff.enumPinAssignmentESupportOnOff;
            break;
#endif
#endif

        default:
            break;
    }
}
#endif // End of #if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
