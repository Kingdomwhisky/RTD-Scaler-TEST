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
// ID Code      : ScalerCommonTypeC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
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
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
bit g_bTypeC5400LenovoAltModeUrgentEvent = _FALSE;
#endif
#endif

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
#if((_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY) && ((_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_POWER_BANK_CC) || (_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_POWER_BANK_PD)))
#warning "Type-C Port Role = SNK-Only and DC Off Option = Power Bank CC/PD will force CC as SRC-Only when DC Off !!!!"
#endif
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTypeCHandler(BYTE ucInputPort, BYTE ucModeState);
EnumTypeCAttachStatus ScalerTypeCGetCcAttach(BYTE ucInputPort);
#if(_USB3_RETIMER_SUPPORT == _ON)
EnumTypeCAttachStatus ScalerTypeCSearchCcAttach(void);
#endif
EnumTypeCAltModeStatus ScalerTypeCGetAltModeReady(BYTE ucInputPort);
EnumTypeCOrientation ScalerTypeCGetOrientation(BYTE ucInputPort);
bit ScalerTypeCGetPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment);
EnumTypeCPowerRole ScalerTypeCGetPowerRole(BYTE ucInputPort);
bit ScalerTypeCReconnect(BYTE ucInputPort);
bit ScalerTypeCUpdateConfig(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap);
void ScalerTypeCIntHandler_EXINT0(void);
void ScalerTypeCPowerSwitch(EnumPowerAction enumPowerAction);
void ScalerTypeCSetPdoByKernel(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
void ScalerTypeCSetMaxPower(BYTE ucInputPort, WORD usMaxPower);
void ScalerTypeCSetPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
BYTE ScalerTypeCGetPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
#endif
BYTE ScalerTypeCGetPartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
EnumPdoCheck ScalerTypeCCheckPdoCountChange(BYTE ucInputPort, BYTE ucPdoCount);
EnumPdoCheck ScalerTypeCCheckPdoChange(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo);
void ScalerTypeCSetFixPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucVoltage, BYTE ucMaxCur);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
void ScalerTypeCSetPpsPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucMinVol, BYTE ucMaxVol, BYTE ucMaxCur);
#endif
void ScalerTypeCSetRdo(BYTE ucInputPort, StructTypeCUserRDO stTypeCUserRdo);
StructTypeCUserPDO ScalerTypeCGetPartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
void ScalerTypeCSetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo stTypeCUserProtectInfo);
#endif
bit ScalerTypeCGetPdoStatus(BYTE ucInputPort, BYTE *pucVoltage, BYTE *pucCurrent);
void ScalerTypeCSetPdSystemEvent(BYTE ucInputPort, EnumPDSysEvent enumPdSysEvent);
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
EnumTypeCLenovoAltModeStatus ScalerTypeCGetLenovoAltModeReady(BYTE ucInputPort);
EnumTypeCLenovoDeviceType ScalerTypeCGetLenovoDeviceType(BYTE ucInputPort);
StructTypeCLenovoSysEvent ScalerTypeCGetLenovoSystemEvent(BYTE ucInputPort);
void ScalerTypeCSetLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
bit ScalerTypeCCheckLenovoDockingEventBusy(BYTE ucInputPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
EnumTypeCAcerAltModeStatus ScalerTypeCGetAcerAltModeReady(BYTE ucInputPort);
StructTypeCAcerSysEvent ScalerTypeCGetAcerSystemEvent(BYTE ucInputPort);
void ScalerTypeCSetAcerUserEvent(BYTE ucInputPort, StructTypeCAcerUserEvent stAcerUserEvent);
EnumTypeCAcerBusyStatus ScalerTypeCCheckAcerUserEventBusy(BYTE ucInputPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
EnumTypeCHpAltModeStatus ScalerTypeCGetHpAltModeReady(BYTE ucInputPort);
StructTypeCHpSysEvent ScalerTypeCGetHpSystemEvent(BYTE ucInputPort);
void ScalerTypeCSetHpUserEvent(BYTE ucInputPort, StructTypeCHpUserEvent stHpUserEvent);
EnumTypeCHpBusyStatus ScalerTypeCCheckHpUserEventBusy(BYTE ucInputPort);
#endif
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Type C Handler Process
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void ScalerTypeCHandler(BYTE ucInputPort, BYTE ucModeState)
{
    ucModeState = ucModeState;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0CcHandler(ucModeState);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Return Port Controller CC Attach Status to SysTypeC
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus ScalerTypeCGetCcAttach(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            return GET_CC_RX0_ATTACHED();
#endif

        default:

            return _TYPE_C_UNATTACH;
    }
}

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return Port Controller Alt Mode Ready Status to SysTypeC
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus ScalerTypeCSearchCcAttach(void)
{
    EnumTypeCAttachStatus enumCcAttach = _TYPE_C_UNATTACH;

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

    enumCcAttach = (enumCcAttach | GET_CC_RX0_ATTACHED());

#endif

    return enumCcAttach;
}
#endif

//--------------------------------------------------
// Description  : Return Port Controller DP Alt Mode Ready Status to SysTypeC
// Input Value  : None
// Output Value : DP Alt Mode Ready Status (_TYPE_C_ALT_MODE_READY / _TYPE_C_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCAltModeStatus ScalerTypeCGetAltModeReady(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetAltModeReady() == _TRUE)
            {
                return _TYPE_C_ALT_MODE_READY;
            }
            else
            {
                return _TYPE_C_ALT_MODE_NOT_READY;
            }
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Return Port Controller Orientation to SysTypeC
// Input Value  : None
// Output Value : _TYPE_C_ORIENTATION_NONE / _TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP
//--------------------------------------------------
EnumTypeCOrientation ScalerTypeCGetOrientation(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            return GET_CC_RX0_ORIENTATION();
#endif

        default:

            return _TYPE_C_ORIENTATION_NONE;
    }
}

//--------------------------------------------------
// Description  : Return Port Controller Alt Mode Pin Assignment to SysTypeC
// Input Value  : None
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCGetPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            *penumPinAssignment = ScalerTypeCRx0PdGetPinAssignment();
            return _SUCCESS;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D1_INPUT_PORT:

            return _SUCCESS;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D6_INPUT_PORT:

            return _SUCCESS;
#endif

        default:

            return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Return Port Controller Power Role to SysTypeC
// Input Value  : ucInputPort
// Output Value : EnumTypeCPowerRole (_TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC / _TYPE_C_POWER_ROLE_NONE)
//--------------------------------------------------
EnumTypeCPowerRole ScalerTypeCGetPowerRole(BYTE ucInputPort)
{
    EnumTypeCPowerRole enumTypeCPowerRole = _TYPE_C_POWER_ROLE_NONE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetPowerRole() == _PD_POWER_SRC)
            {
                enumTypeCPowerRole = _TYPE_C_POWER_SRC;
            }
            else
            {
                enumTypeCPowerRole = _TYPE_C_POWER_SNK;
            }

            break;
#endif

        default:

            break;
    }

    return enumTypeCPowerRole;
}

//--------------------------------------------------
// Description  : Type C Reconnect Process
// Input Value  : ucInputPort
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCReconnect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            SET_TYPE_C_ERROR_RECOVERY();

            return _SUCCESS;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D1_INPUT_PORT:

            return _SUCCESS;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D6_INPUT_PORT:

            return _SUCCESS;
#endif

        default:

            return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type C Configuration Update
// Input Value  : ucInputPort
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCUpdateConfig(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetPinAssignmentCapability(enumPinAssignmentCap);
            ScalerTypeCRx0PdSetMultiFunctionBit(enumMultiFunc);

            return _SUCCESS;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D1_INPUT_PORT:

            return _SUCCESS;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D6_INPUT_PORT:

            return _SUCCESS;
#endif

        default:

            return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type C Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCIntHandler_EXINT0(void) using 1
{
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    ScalerTypeCPowerIntHandler_EXINT0();
    ScalerTypeCRx0CcIntHandler_EXINT0();
    ScalerTypeCRx0PdIntHandler_EXINT0();

    if((ScalerTypeCRx0CcIntClrCheck_EXINT0() == _TRUE) && (ScalerTypeCRx0PdIntClrCheck_EXINT0() == _TRUE))
    {
        MCU_FD29_UFP_DPF_IRQ_STATUS |= _BIT7;

        // Toggle Type C IRQ En to Prevent from IRQ Miss
        ScalerSetBit_EXINT(P6F_10_ADI_IRQ_CTRL, ~_BIT1, 0x00);
        ScalerSetBit_EXINT(P6F_10_ADI_IRQ_CTRL, ~_BIT1, _BIT1);
    }
#endif
}


//--------------------------------------------------
// Description  : Type C Power Switch Process
// Input Value  : enumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCPowerSwitch(EnumPowerAction enumPowerAction)
{
    enumPowerAction = enumPowerAction;

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    ScalerTypeCRx0CcPowerSwitch(enumPowerAction);
    ScalerTypeCRx0PdPowerSwitch(enumPowerAction);
#endif
}

//--------------------------------------------------
// Description  : Type C Set PDO By Kernel
// Input Value  : ucInputPort --> Inputput
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPdoByKernel(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetPdoByKernel(enumPowerRole);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Set Source Max Supply Power
// Input Value  : ucInputPort, usMaxPower in 0.1W
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetMaxPower(BYTE ucInputPort, WORD usMaxPower)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetMaxPower(usMaxPower);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Set Number of PDO Counts
// Input Value  : ucInputPort, Number of PDO Counts (1~7)
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt)
{
    enumPowerRole = enumPowerRole;
    ucPdoCnt = ucPdoCnt;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetPdoCnt(enumPowerRole, ucPdoCnt);

            break;
#endif

        default:

            break;
    }
}

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
//--------------------------------------------------
// Description  : Get Number of PDOs in PD FW (May Be User/Kernel-Defined)
// Input Value  : ucInputPort
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
BYTE ScalerTypeCGetPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCnt = 0;
    enumPowerRole = enumPowerRole;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ucPdoCnt = ScalerTypeCRx0PdGetPdoCnt(enumPowerRole);

            break;
#endif

        default:

            break;
    }

    return ucPdoCnt;
}
#endif  // End of #if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)

//--------------------------------------------------
// Description  : Get Number of Partner Src/Snk PDOs
// Input Value  : ucInputPort
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
BYTE ScalerTypeCGetPartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCnt = 0x00;
    enumPowerRole = enumPowerRole;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ucPdoCnt = ScalerTypeCRx0PdGetPartnerPdoCnt(enumPowerRole);

            break;
#endif

        default:

            break;
    }

    return ucPdoCnt;
}

//--------------------------------------------------
// Description  : Type C Check PDO Count Change
// Input Value  : ucInputPort, ucPdoCount
// Output Value : EnumPdoCheck
//--------------------------------------------------
EnumPdoCheck ScalerTypeCCheckPdoCountChange(BYTE ucInputPort, BYTE ucPdoCount)
{
    EnumPdoCheck enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumSrcCapPdoChange = ScalerTypeCRx0PdCheckPdoCountChange(ucPdoCount);

            break;
#endif

        default:

            enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

            break;
    }

    return enumSrcCapPdoChange;
}

//--------------------------------------------------
// Description  : Type C Check PDO Change
// Input Value  : ucInputPort, ucPdoIndex, stTypeCUserPdo
// Output Value : EnumPdoCheck
//--------------------------------------------------
EnumPdoCheck ScalerTypeCCheckPdoChange(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo)
{
    EnumPdoCheck enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumSrcCapPdoChange = ScalerTypeCRx0PdCheckPdoChange(ucPdoIndex, stTypeCUserPdo);

            break;
#endif

        default:

            enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;

            break;
    }

    return enumSrcCapPdoChange;
}

//--------------------------------------------------
// Description  : Type C Set Fix Supply PDO
// Input Value  : ucInputPort, ucPdoIndex, ucVoltage(100mV), ucMaxCur(50mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetFixPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucVoltage, BYTE ucMaxCur)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetFixPdo(enumPowerRole, ucPdoIndex, (WORD)ucVoltage, (WORD)ucMaxCur);

            break;
#endif

        default:

            break;
    }
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type C Set PPS PDO
// Input Value  : ucInputPort, ucPdoIndex, ucVoltage(100mV), ucMaxCur(50mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPpsPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, BYTE ucMinVol, BYTE ucMaxVol, BYTE ucMaxCur)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetArgumentedPdo(enumPowerRole, ucPdoIndex, ucMinVol, ucMaxVol, ucMaxCur);

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Set Request Content to Kernel
// Input Value  : StructTypeCUserRDO(Object Position, ReqInfo1, ReqInfo2, Cap Mismatch)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetRdo(BYTE ucInputPort, StructTypeCUserRDO stTypeCUserRdo)
{
    stTypeCUserRdo = stTypeCUserRdo;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetRdo(stTypeCUserRdo);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Partner Source/Sink PDO Info
// Input Value  : ucInputPort, enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 50mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeCGetPartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPartnerPdo;

    // Reset Default Value to Fix PDO w/ 0V @ 0A
    stTypeCPartnerPdo.enumPdoType = _PD_FIX_SUPPLY_PDO;
    stTypeCPartnerPdo.ucMaxVoltage = 0;
    stTypeCPartnerPdo.ucMinVoltage = 0;
    stTypeCPartnerPdo.ucMaxCurrent = 0;

    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            stTypeCPartnerPdo = ScalerTypeCRx0PdGetPartnerPdo(enumPowerRole, ucPdoIndex);

            break;
#endif

        default:

            break;
    }

    return stTypeCPartnerPdo;
}

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
//--------------------------------------------------
// Description  : Type C Set Protect Info
// Input Value  : ucInputPort, ucPdoIndex, StructTypeCUserProtectInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo stTypeCUserProtectInfo)
{
    ucPdoIndex = ucPdoIndex;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetProtectInfo(ucPdoIndex, stTypeCUserProtectInfo);

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get TypeC Negotiated Voltage / Current
// Input Value  : ucInputPort, Voltage (100mV) / Current (50mA)
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerTypeCGetPdoStatus(BYTE ucInputPort, BYTE *pucVoltage, BYTE *pucCurrent)
{
    ucInputPort = ucInputPort;
    *pucVoltage = *pucVoltage;
    *pucCurrent = *pucCurrent;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetPdoStatus(pucVoltage, pucCurrent) == _FAIL)
            {
                return _FAIL;
            }

            return _SUCCESS;
#endif

        default:

            return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type C Set Source Capability Change Flag
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetPdSystemEvent(BYTE ucInputPort, EnumPDSysEvent enumPdSysEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetSystemEvent(enumPdSysEvent);

            break;
#endif

        default:

            break;
    }
}

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : Return Port Controller Lenovo Alt Mode Ready Status to SysTypeC
// Input Value  : ucInputPort
// Output Value : Lenovo Alt Mode Ready Status (_TYPE_C_LENOVO_ALT_MODE_READY / _TYPE_C_LENOVO_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCLenovoAltModeStatus ScalerTypeCGetLenovoAltModeReady(BYTE ucInputPort)
{
    EnumTypeCLenovoAltModeStatus enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_NOT_READY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetLenovoAltModeReady() == _TRUE)
            {
                enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_READY;
            }
            else
            {
                enumLenovoAltModeStatus = _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }

            break;
#endif

        default:

            break;
    }

    return enumLenovoAltModeStatus;
}

//--------------------------------------------------
// Description  : Return Port Controller Partner Lenovo Device Type
// Input Value  : ucInputPort
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType ScalerTypeCGetLenovoDeviceType(BYTE ucInputPort)
{
    EnumTypeCLenovoDeviceType enumLenovoDeviceType = _TYPE_C_LENOVO_DEVICE_TYPE_NONE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumLenovoDeviceType = ScalerTypeCRx0PdGetLenovoDeviceType();

            break;
#endif

        default:

            break;
    }

    return enumLenovoDeviceType;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event
// Input Value  : ucInputPort
// Output Value : StructTypeCLenovoSysEvent
//--------------------------------------------------
StructTypeCLenovoSysEvent ScalerTypeCGetLenovoSystemEvent(BYTE ucInputPort)
{
    StructTypeCLenovoSysEvent stLenovoSysEvent = {_TYPE_C_LENOVO_SYS_DC_MODE, _TYPE_C_LENOVO_SYS_STATE_NONE, _FALSE, 0x00, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            stLenovoSysEvent = ScalerTypeCRx0PdGetLenovoSystemEvent();

            break;
#endif

        default:

            break;
    }

    return stLenovoSysEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Set Docking Event
// Input Value  : ucInputPort, stLenovoDockEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetLenovoDockingEvent(stLenovoDockEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : ucInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeCCheckLenovoDockingEventBusy(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            return ScalerTypeCRx0PdCheckLenovoDockingEventBusy();

            break;
#endif

        default:

            return _FALSE;

            break;
    }

    return _FALSE;
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : Return Embedded Port Controller Acer Alt Mode Ready Status
// Input Value  : ucInputPort
// Output Value : Acer Alt Mode Ready Status (_TYPE_C_ACER_ALT_MODE_READY / _TYPE_C_ACER_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCAcerAltModeStatus ScalerTypeCGetAcerAltModeReady(BYTE ucInputPort)
{
    EnumTypeCAcerAltModeStatus enumAcerAltModeStatus = _TYPE_C_ACER_ALT_MODE_NOT_READY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetAcerAltModeReady() == _TRUE)
            {
                enumAcerAltModeStatus = _TYPE_C_ACER_ALT_MODE_READY;
            }
            else
            {
                enumAcerAltModeStatus = _TYPE_C_ACER_ALT_MODE_NOT_READY;
            }

            break;
#endif

        default:

            break;
    }

    return enumAcerAltModeStatus;
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Get System Event
// Input Value  : ucInputPort
// Output Value : StructTypeCAcerSysEvent
//--------------------------------------------------
StructTypeCAcerSysEvent ScalerTypeCGetAcerSystemEvent(BYTE ucInputPort)
{
    StructTypeCAcerSysEvent stAcerSysEvent = {_TYPE_C_ACER_SYS_EVENT_NONE, {0x00}, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            stAcerSysEvent = ScalerTypeCRx0PdGetAcerSystemEvent();

            break;
#endif

        default:

            break;
    }

    return stAcerSysEvent;
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Set User Event
// Input Value  : ucInputPort, stAcerUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetAcerUserEvent(BYTE ucInputPort, StructTypeCAcerUserEvent stAcerUserEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetAcerUserEvent(stAcerUserEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Check if Last User Event has been Sent
// Input Value  : ucInputPort
// Output Value : User Event Busy Status (_TYPE_C_ACER_USER_EVENT_BUSY / _TYPE_C_ACER_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCAcerBusyStatus ScalerTypeCCheckAcerUserEventBusy(BYTE ucInputPort)
{
    EnumTypeCAcerBusyStatus enumCheckBusyResult = _TYPE_C_ACER_USER_EVENT_NOT_BUSY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumCheckBusyResult = ScalerTypeCRx0PdCheckAcerUserEventBusy();

            break;
#endif

        default:

            break;
    }

    return enumCheckBusyResult;
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : Return Embedded Port Ctrl Hp Alt Mode Ready Status
// Input Value  : ucInputPort
// Output Value : Hp Alt Mode Ready Status (_TYPE_C_HP_ALT_MODE_READY / _TYPE_C_HP_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCHpAltModeStatus ScalerTypeCGetHpAltModeReady(BYTE ucInputPort)
{
    EnumTypeCHpAltModeStatus enumHpAltModeStatus = _TYPE_C_HP_ALT_MODE_NOT_READY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(ScalerTypeCRx0PdGetHpAltModeReady() == _TRUE)
            {
                enumHpAltModeStatus = _TYPE_C_HP_ALT_MODE_READY;
            }
            else
            {
                enumHpAltModeStatus = _TYPE_C_HP_ALT_MODE_NOT_READY;
            }

            break;
#endif

        default:

            break;
    }

    return enumHpAltModeStatus;
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Get System Event
// Input Value  : ucInputPort
// Output Value : StructTypeCHpSysEvent
//--------------------------------------------------
StructTypeCHpSysEvent ScalerTypeCGetHpSystemEvent(BYTE ucInputPort)
{
    StructTypeCHpSysEvent stHpSysEvent = {_TYPE_C_HP_SYS_EVENT_NONE, {0x00}, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            stHpSysEvent = ScalerTypeCRx0PdGetHpSystemEvent();

            break;
#endif

        default:

            break;
    }

    return stHpSysEvent;
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Set User Event
// Input Value  : ucInputPort, stHpUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCSetHpUserEvent(BYTE ucInputPort, StructTypeCHpUserEvent stHpUserEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ScalerTypeCRx0PdSetHpUserEvent(stHpUserEvent);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Check if Last User Event has been Sent
// Input Value  : ucInputPort
// Output Value : User Event Busy Status (_TYPE_C_HP_USER_EVENT_BUSY / _TYPE_C_HP_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCHpBusyStatus ScalerTypeCCheckHpUserEventBusy(BYTE ucInputPort)
{
    EnumTypeCHpBusyStatus enumCheckBusyResult = _TYPE_C_HP_USER_EVENT_NOT_BUSY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            enumCheckBusyResult = ScalerTypeCRx0PdCheckHpUserEventBusy();

            break;
#endif

        default:

            break;
    }

    return enumCheckBusyResult;
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
