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
// ID Code      : RTD2014UserTypeCInterface.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_TYPECINTERFACE__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Usb Hub Polling Par
//--------------------------------------------------
#define _USB_D0_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_D1_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_D2_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_D6_HUB_POLLING_DEVICE_STEP         500 // Unit: ms
#define _USB_DX_HUB_POLLING_DEVICE_STEP         500 // Unit: ms

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
StructTypeCLenovoDockEventQueue g_stDockEventQueue;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
StructTypeCAcerUserEvent g_stUsbTypeCAcerUserEvent;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
StructTypeCHpUserEvent g_stUsbTypeCHpUserEvent;
#endif
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
EnumTypeCU3ModeType UserInterfaceTypeCGetOsdU3ModeSelection(BYTE ucInputPort);
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
EnumTypeCPinAssignmentESupportStatus UserInterfaceTypeCGetOsdPinAssignmentESupportSelection(BYTE ucInputPort);
#endif

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
bit UserInterfaceTypeCHubProcSupport(BYTE ucInputPort);
void UserInterfaceTypeCOsdHubProc(BYTE ucInputPort);
WORD UserInterfaceTypeCUsbHubSetPollingStep(BYTE ucInputPort);
bit UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(BYTE ucInputPort);
bit UserInterfaceTypeCUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
EnumHubDspDetectStatus UserInterfaceTypeCUsbHubDetectDFPStatus(BYTE ucInputPort);
#if(_BILLBOARD_HUB_SUPPORT == _ON)
void UserInterfaceTypeCUsbHubBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion);
#endif
#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))
EnumTypeCAttachStatus UserInterfaceTypeCGetPortControllerCcAttach(BYTE ucInputPort);
EnumTypeCAltModeStatus UserInterfaceTypeCGetPortControllerAltModeReady(BYTE ucInputPort);
#endif  // End of #if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
#if(_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER)
EnumTypeCOrientation UserInterfaceTypeCGetPortControllerOrientation(BYTE ucInputPort);
#endif
EnumTypeCPowerRole UserInterfaceTypeCPortControllerGetUserPowerRole(BYTE ucInputPort);
bit UserInterfaceTypeCPortControllerReconnect(BYTE ucInputPort);
bit UserInterfaceTypeCPortControllerConfigUserPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment);
bit UserInterfaceTypeCPortControllerConfigUserMultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction);
EnumTypeCUserPortCtrlFailureType UserInterfaceTypeCGetPinCfgType(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinCfgtype);
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
EnumTypeCLenovoAltModeStatus UserInterfaceTypeCPortControllerGetUserLenovoAltModeReady(BYTE ucInputPort);
EnumTypeCLenovoDeviceType UserInterfaceTypeCPortControllerGetUserLenovoDeviceType(BYTE ucInputPort);
void UserInterfaceTypeCPortControllerSetUserLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
StructTypeCLenovoSysEvent UserInterfaceTypeCPortControllerGetUserLenovoSystemEvent(BYTE ucInputPort);
bit UserInterfaceTypeCPortControllerCheckUserLenovoDockingEventBusy(BYTE ucInputPort);
#endif
#endif // End of #if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
EnumTypeCPinCfgCapType UserInterfaceTypeCGetPinConfigType(BYTE ucInputPort, EnumTypeCU3ModeType enumU3ModeSel, EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportSel);
void UserInterfaceTypeCPinAssignSuccessProc(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment);
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
void UserInterfaceTypeCGetLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent *pstLenovoDockEvent);
void UserInterfaceTypeCLenovoAltModeHandler(BYTE ucInputPort, StructTypeCLenovoSysEvent stLenovoSysEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
void UserInterfaceTypeCGetAcerUserEvent(BYTE ucInputPort, StructTypeCAcerUserEvent *pstAcerUserEvent);
void UserInterfaceTypeCAcerAltModeHandler(BYTE ucInputPort, StructTypeCAcerSysEvent stAcerSysEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
void UserInterfaceTypeCGetHpUserEvent(BYTE ucInputPort, StructTypeCHpUserEvent *pstHpUserEvent);
void UserInterfaceTypeCHpAltModeHandler(BYTE ucInputPort, StructTypeCHpSysEvent stHpSysEvent);
#endif
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
EnumTypeCEmbPdoReference UserInterfaceTypeCPdoReference(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
EnumTypeCEmbRdoReference UserInterfaceTypeCRdoReference(BYTE ucInputPort);
WORD UserInterfaceTypeCGetMaxPower(BYTE ucInputPort);
EnumTypeCPdoNumber UserInterfaceTypeCGetPdoCount(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
void UserInterfaceTypeCGetSrcPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserSrcPdo);
void UserInterfaceTypeCGetSnkPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserSnkPdo);
void UserInterfaceTypeCGetRdoInfo(BYTE ucInputPort, StructTypeCUserRDO *pstTypeCUserRdo);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
void UserInterfaceTypeCGetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo *pstTypeCUserProtectInfo);
#endif
#if(_DP_USB_HUB_SUPPORT == _ON)
EnumHubInputPort UserInterfaceTypeCHubInputPort(BYTE ucInputPort);
#endif
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)

#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
EnumTypeCPortCtrlReconnectSupport UserInterfaceTypeCPortControllerReconnectSupport(BYTE ucInputPort);
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
EnumTypeCPortCtrlReconnectStatus UserInterfaceTypeCPortControllerGetPowerOnReconnectStatus(EnumPowerAction enumSwitch);
#endif
#endif // End of #if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get OSD Type-C U3 Mode Selection
// Input Value  : ucInputPort --> Input Port
// Output Value : Return Type-C U3 Mode Selection
//--------------------------------------------------
EnumTypeCU3ModeType UserInterfaceTypeCGetOsdU3ModeSelection(BYTE ucInputPort)
{
    EnumTypeCU3ModeType enumTypeCMode = _TYPE_C_U3_OFF;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            enumTypeCMode = GET_OSD_D0_TYPE_C_U3_MODE();
            break;
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            enumTypeCMode = GET_OSD_D1_TYPE_C_U3_MODE();
            break;
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:
            enumTypeCMode = GET_OSD_D6_TYPE_C_U3_MODE();
            break;
#endif
        default:
            break;
    }

    return enumTypeCMode;
}

#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Decide Type-C Pin Assignment E Support or Not
// Input Value  : enumInputPort
// Output Value : _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON / _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF
//--------------------------------------------------
EnumTypeCPinAssignmentESupportStatus UserInterfaceTypeCGetOsdPinAssignmentESupportSelection(BYTE ucInputPort)
{
    EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportStatus = _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            enumPinAssignmentESupportStatus = GET_OSD_D0_TYPE_C_PIN_ASSIGNMENT_E_SELECT();
            break;
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            enumPinAssignmentESupportStatus = GET_OSD_D1_TYPE_C_PIN_ASSIGNMENT_E_SELECT();
            break;
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:
            enumPinAssignmentESupportStatus = GET_OSD_D6_TYPE_C_PIN_ASSIGNMENT_E_SELECT();
            break;
#endif
        default:
            break;
    }

    return enumPinAssignmentESupportStatus;
}
#endif

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Decide Wether Support USB Hub
// Input Value  : ucInputPort --> Input Port
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserInterfaceTypeCHubProcSupport(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(GET_OSD_D0_TYPE_C_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
            break;
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            if(GET_OSD_D1_TYPE_C_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
            break;
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            if(GET_OSD_D6_TYPE_C_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User decided how many lanes to switch
// Input Value  : ucInputPort --> Input Port
//                _BIT0 : 1 --> Hub Port0 U3 Device Plug In,  0 --> Hub Port0 U3 Device Plug off
//                _BIT1 : 1 --> Hub Port1 U3 Device Plug In,  0 --> Hub Port1 U3 Device Plug off
//                _BIT2 : 1 --> Hub Port2 U3 Device Plug In,  0 --> Hub Port2 U3 Device Plug off
//                _BIT3 : 1 --> Hub Port3 U3 Device Plug In,  0 --> Hub Port3 U3 Device Plug off
//                _BIT4 ~ _BIT7 : Useless
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCOsdHubProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            // Here: User Can Use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create Draw Notice U3 Device Menu Event
            break;

        case _D1_INPUT_PORT:
            // Here: User Can Use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create Draw Notice U3 Device Menu Event
            break;

        case _D6_INPUT_PORT:
            // Here: User Can Use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create Draw Notice U3 Device Menu Event
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : User Set Usb Hub Polling SS Device Step
// Input Value  : ucInputPort --> Input Port
// Output Value : Usb Hub Polling Step Par.
//--------------------------------------------------
WORD UserInterfaceTypeCUsbHubSetPollingStep(BYTE ucInputPort)
{
    if(ucInputPort == _D0_INPUT_PORT)
    {
        return _USB_D0_HUB_POLLING_DEVICE_STEP;
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
        return _USB_D1_HUB_POLLING_DEVICE_STEP;
    }
    else if(ucInputPort == _D2_INPUT_PORT)
    {
        return _USB_D2_HUB_POLLING_DEVICE_STEP;
    }
    else if(ucInputPort == _D6_INPUT_PORT)
    {
        return _USB_D6_HUB_POLLING_DEVICE_STEP;
    }
    else
    {
        return _USB_DX_HUB_POLLING_DEVICE_STEP;
    }
}

//--------------------------------------------------
// Description  : Usb Hub RTS5400 Series User Flow Support
// Input Value  : ucInputPort --> Input Port
// Output Value : _TRUE: User Flow, _FALSE: Kernal Flow
//--------------------------------------------------
bit UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return _FALSE;

            break;
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            return _FALSE;

            break;
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            return _FALSE;

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set Usb Hub into SS Mode
// Input Value  : None
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserInterfaceTypeCUsbHubSetSSMode(BYTE ucInputPort, bit bEn)
{
    ucInputPort = ucInputPort;
    bEn = bEn;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Detect Usb Hub SS Device Plug In
// Input Value  : ucInputPort --> Input Port
// Output Value : Return SS Device Info.
//                _BIT0 : 1 --> Hub Port0 U3 Device Plug In,  0 --> Hub Port0 U3 Device Plug off
//                _BIT1 : 1 --> Hub Port1 U3 Device Plug In,  0 --> Hub Port1 U3 Device Plug off
//                _BIT2 : 1 --> Hub Port2 U3 Device Plug In,  0 --> Hub Port2 U3 Device Plug off
//                _BIT3 : 1 --> Hub Port3 U3 Device Plug In,  0 --> Hub Port3 U3 Device Plug off
//                _BIT4 ~ _BIT7 : Useless
//--------------------------------------------------
EnumHubDspDetectStatus UserInterfaceTypeCUsbHubDetectDFPStatus(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return _HUB_DSP_DEVICE_NO_CHANGE;
}

#if(_BILLBOARD_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hub Billboard Control
// Input Value  : _TYPE_C_BB_DISABLE / _TYPE_C_BB_ENABLE
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCUsbHubBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion)
{
    enumAtion = enumAtion;

    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            // Here: User Enable / Disable Hub Billboard
            break;

        case _D1_INPUT_PORT:
            // Here: User Enable / Disable Hub Billboard
            break;

        case _D6_INPUT_PORT:
            // Here: User Enable / Disable Hub Billboard
            break;

        default:
            break;
    }
}
#endif // End of #if(_BILLBOARD_HUB_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))
//--------------------------------------------------
// Description  : Type-C Port Controller CC Attach Detectd By User Define
// Input Value  : enumSourcePort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : _TYPE_C_ATTACH / _TYPE_C_UNATTACH
//--------------------------------------------------
EnumTypeCAttachStatus UserInterfaceTypeCGetPortControllerCcAttach(BYTE ucInputPort)
{
    EnumTypeCAttachStatus enumCcAttachResult = _TYPE_C_UNATTACH;

    // User Can Use Their Own Way to Decide Port Controller CC Attach or Not, For Example
    // enumCcAttachResult = (GPIO == HIGH) ? _TYPE_C_UNATTACH : _TYPE_C_ATTACH;

    switch(ucInputPort)
    {
#if(((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D0_INPUT_PORT:
#endif
#if(((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D1_INPUT_PORT:
#endif
#if(((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D6_INPUT_PORT:
#endif
        default:

            enumCcAttachResult = _TYPE_C_UNATTACH;

            break;
    }

    return enumCcAttachResult;
}

//--------------------------------------------------
// Description  : Type-C Port Controller Alt Mode Ready Detectd By User Define
// Input Value  : enumSourcePort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : _TYPE_C_ALT_MODE_READY / _TYPE_C_ALT_MODE_NOT_READY
//--------------------------------------------------
EnumTypeCAltModeStatus UserInterfaceTypeCGetPortControllerAltModeReady(BYTE ucInputPort)
{
    EnumTypeCAltModeStatus enumAltModeReadyResult = _TYPE_C_ALT_MODE_NOT_READY;

    // User Can Use Their Own Way to Decide Port Controller Alt Mode Ready or Not, For Example
    // enumCcAttachResult = (GPIO == HIGH) ? _TYPE_C_ALT_MODE_NOT_READY : _TYPE_C_ALT_MODE_READY;

    switch(ucInputPort)
    {
#if(((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D0_INPUT_PORT:
#endif
#if(((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D1_INPUT_PORT:
#endif
#if(((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN))
        case _D6_INPUT_PORT:
#endif
        default:

            enumAltModeReadyResult = _TYPE_C_ALT_MODE_NOT_READY;

            break;
    }

    return enumAltModeReadyResult;
}
#endif  // End of #if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
#if(_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER)
//--------------------------------------------------
// Description  : Ext Port Controller Orientation Info
// Input Value  : ucInputPort --> Input Port
// Output Value : Orientation (_TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP)
//--------------------------------------------------
EnumTypeCOrientation UserInterfaceTypeCGetPortControllerOrientation(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // User Can Use Their Own Way to Decide Port Controller Orientation, For Example
    // EnumTypeCOrientation = (GPIO == HIGH) ? _TYPE_C_ORIENTATION_UNFLIP : _TYPE_C_ORIENTATION_FLIP;
    return _TYPE_C_ORIENTATION_UNFLIP;
}
#endif  // End of #if(_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER)

//--------------------------------------------------
// Description  : Get User Port Controller Power Role
// Input Value  : ucInputPort --> Input Port
// Output Value : EnumTypeCPowerRole (_TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC / _TYPE_C_POWER_ROLE_NONE)
//--------------------------------------------------
EnumTypeCPowerRole UserInterfaceTypeCPortControllerGetUserPowerRole(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // User Can Use Their Own Way to Decide Port Controller Power Role
    return _TYPE_C_POWER_SNK;
}

//--------------------------------------------------
// Description  : Port Controller Reconnect
// Input Value  : ucInputPort --> Input Port
// Output Value : return _TRUE / _FALSE
//--------------------------------------------------
bit UserInterfaceTypeCPortControllerReconnect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return _TRUE;
}

//--------------------------------------------------
// Description  : For User to Config Port Controller Pin Assignment
// Input Value  : ucInputPort --> Input Port, enumPinAssignment
// Output Value : return _TRUE / _FALSE
//--------------------------------------------------
bit UserInterfaceTypeCPortControllerConfigUserPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment)
{
    ucInputPort = ucInputPort;
    enumPinAssignment = enumPinAssignment;

    // Kernel Ask User to Config User Port Controller's Pin Assignment when U3 Mode and Current Pin Assignment are inconsistency.

    return _TRUE;
}

//--------------------------------------------------
// Description  : Port Controller Reconnect
// Input Value  : ucInputPort --> Input Port, enumMultiFunction
// Output Value : return _TRUE / _FALSE
//--------------------------------------------------
bit UserInterfaceTypeCPortControllerConfigUserMultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction)
{
    ucInputPort = ucInputPort;
    enumMultiFunction = enumMultiFunction;

    // Kernel Ask User to Config User Port Controller's Multi-Function Bit when U3 Mode and Current Pin Assignment are inconsistency.

    return _TRUE;
}

//--------------------------------------------------
// Description  : Port Controller Config Type
// Input Value  : ucInputPort --> Input Port
//                penumPinCfgtype --> Pin Assignment Type
// Output Value : return failure type
//--------------------------------------------------
EnumTypeCUserPortCtrlFailureType UserInterfaceTypeCGetPinCfgType(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinCfgtype)
{
    ucInputPort = ucInputPort; // Avoiding Warning
    *penumPinCfgtype = _TYPE_C_PIN_ASSIGNMENT_C;

    // Example:
    /*
        if(UserGetPortcontrollerConfigPinAssignmentTypeFunc(penumPinCfgtype) == _TRUE)
        {
            return _TYPE_C_USER_PORT_CTRL_COMMUNICATION_SUCCESS;
        }
        else
        {
            return _TYPE_C_USER_PORT_CTRL_COMMUNICATION_FAIL;
        }
    */

    return _TYPE_C_USER_PORT_CTRL_COMMUNICATION_FAIL;
}

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
//--------------------------------------------------
// Description  : Get User Port Controller Lenovo Alt Mode Ready Info
// Input Value  : ucInputPort --> Inputput
// Output Value : Lenovo Alt Mode Ready Status (_TYPE_C_LENOVO_ALT_MODE_READY / _TYPE_C_LENOVO_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCLenovoAltModeStatus UserInterfaceTypeCPortControllerGetUserLenovoAltModeReady(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // User Can Use Their Own Way to Decide Port Controller Lenovo Alt Mode Ready or Not, For Example
    // Lenovo Alt Mode Entered ? _TYPE_C_LENOVO_ALT_MODE_READY : _TYPE_C_LENOVO_ALT_MODE_NOT_READY;

    return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
}

//--------------------------------------------------
// Description  : Get Port Partner Lenovo Device Type from User Port Controller
// Input Value  : ucInputPort --> Inputput
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType UserInterfaceTypeCPortControllerGetUserLenovoDeviceType(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Set Docking Event
// Input Value  : ucInputPort, stLenovoDockEvent
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCPortControllerSetUserLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    ucInputPort = ucInputPort;
    stLenovoDockEvent = stLenovoDockEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event (Including System Acknowledge)
// Input Value  : ucInputPort
// Output Value : StructTypeCLenovoSysEvent
//--------------------------------------------------
StructTypeCLenovoSysEvent UserInterfaceTypeCPortControllerGetUserLenovoSystemEvent(BYTE ucInputPort)
{
    StructTypeCLenovoSysEvent stLenovoSysEvent;
    ucInputPort = ucInputPort;

    // Reset Default Value to Lenovo System Event
    stLenovoSysEvent.enumSystemPowerMode = _TYPE_C_LENOVO_SYS_DC_MODE;
    stLenovoSysEvent.enumSystemState = _TYPE_C_LENOVO_SYS_STATE_NONE;
    stLenovoSysEvent.b1SystemEvent = _FALSE;
    stLenovoSysEvent.b3SystemReserved = 0x00;
    stLenovoSysEvent.ucSystemAcknowlegde = 0x00;

    return stLenovoSysEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : ucInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserInterfaceTypeCPortControllerCheckUserLenovoDockingEventBusy(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return _FALSE;
}
#endif // End of #if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#endif // End of #if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Decide Sink Pin Config Type
// Input Value  : ucInputPort --> Input Port
//                enumU3ModeSel --> _TYPE_C_U3_ON / _TYPE_C_U3_OFF
//                enumPinAssignmentESupportSel --> _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON / _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF
// Output Value : Pin Config Capability Type
//--------------------------------------------------
EnumTypeCPinCfgCapType UserInterfaceTypeCGetPinConfigType(BYTE ucInputPort, EnumTypeCU3ModeType enumU3ModeSel, EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportSel)
{
    EnumTypeCPinCfgCapType enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_DEFAULT;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+D+E if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    // Use Pin Assignment C+D if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig =  _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+E if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    // Use Pin Assignment C if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }

            break;
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+D+E if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    // Use Pin Assignment C+D if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+E if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    // Use Pin Assignment C if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }

            break;
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+D+E if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    // Use Pin Assignment C+D if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+E if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    // Use Pin Assignment C if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }

            break;
#endif

        default:
            break;
    }

    return enumPinAssignmentConfig;
}

//--------------------------------------------------
// Description  : Switch DP EDID Process by User
// Input Value  : ucInputPort --> Inputput, enumPinAssignment Pin Assignment
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCPinAssignSuccessProc(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment)
{
    ucInputPort = ucInputPort;
    enumPinAssignment = enumPinAssignment;
}

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : TypeC Lenovo Alt Mode Get Docking Event
// Input Value  : ucInputPort --> Input Port
//                stLenovoDockEvent --> Lenovo Docking Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCGetLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent *pstLenovoDockEvent)
{
    pstLenovoDockEvent = pstLenovoDockEvent;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            // Check if Docking Event Queue is Empty
            if(GET_D0_TYPE_C_DOCK_EVENT_CNT() > 0)
            {
                // Update Docking Event Struct For Kernal Usage
                memcpy(pstLenovoDockEvent, &GET_D0_TYPE_C_DOCK_EVENT_QUEUE(GET_D0_TYPE_C_DOCK_EVENT_HEAD()), sizeof(StructTypeCLenovoDockEvent));

                CLR_D0_TYPE_C_DOCK_EVENT_QUEUE();
                ADD_D0_TYPE_C_DOCK_EVENT_HEAD();
                SUB_D0_TYPE_C_DOCK_EVENT_CNT();
            }
            else
            {
                // Reset Default Value to Lenovo Docking Event
                pstLenovoDockEvent->b4DockingReserved = 0x00;
                pstLenovoDockEvent->enumDockingPowerSwitch = _TYPE_C_LENOVO_DOCK_POWER_SWITCH_NONE;
                pstLenovoDockEvent->b1DockingWolRequest = _FALSE;
                pstLenovoDockEvent->b1DockingEvent = _FALSE;
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TypeC Lenovo Alt Mode System Event or System Acknowledge Handler Process
// Input Value  : ucInputPort --> Input Port
//                stLenovoSysEvent --> Lenovo System Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCLenovoAltModeHandler(BYTE ucInputPort, StructTypeCLenovoSysEvent stLenovoSysEvent)
{
    stLenovoSysEvent = stLenovoSysEvent;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            // User can Change its behavior corresponding to System Event
            // User can Retry Last Dock Event or Send Next Dock Event corresponding to System Acknowledge
            break;
#endif

        default:
            break;
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : TypeC Acer Alt Mode Get User Event
// Input Value  : ucInputPort --> Input Port
//                pstAcerUserEvent --> Acer User Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCGetAcerUserEvent(BYTE ucInputPort, StructTypeCAcerUserEvent *pstAcerUserEvent)
{
    // 1. User Can Update User Event Macro Whenever Monitor Status Changes
    // 2. Kernel will Get Acer User Event in this Function and send to Port Ctrl

    BYTE ucVdoDataIndex = 0x00;

    pstAcerUserEvent = pstAcerUserEvent;
    ucVdoDataIndex = ucVdoDataIndex;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            /* Example :
            if(Monitor Status Change)
            {
                SET_D0_TYPE_C_ACER_USER_EVENT(_TYPE_C_ACER_USER_EVENT_ATTENTION);   // Ask Kenel Send Attention
                SET_D0_TYPE_C_ACER_USER_VDM_CNT( N );   // Set Number of VDO (Not include VDM Header)
                SET_D0_TYPE_C_ACER_USER_VDM_DATA(0, VDO_0[31:24]);
                SET_D0_TYPE_C_ACER_USER_VDM_DATA(1, VDO_0[23:16]);
                SET_D0_TYPE_C_ACER_USER_VDM_DATA(2, VDO_0[15:8]);
                SET_D0_TYPE_C_ACER_USER_VDM_DATA(3, VDO_0[7:0]);
            }
            */

            // Check Acer User Event
            if(GET_D0_TYPE_C_ACER_USER_EVENT() != _TYPE_C_ACER_USER_EVENT_NONE)
            {
                // Update Acer User Event to Kernel
                pstAcerUserEvent->enumEvent = GET_D0_TYPE_C_ACER_USER_EVENT();
                pstAcerUserEvent->b3VdmCnt = GET_D0_TYPE_C_ACER_USER_VDM_CNT();

                for(ucVdoDataIndex = 0; ucVdoDataIndex < (GET_D0_TYPE_C_ACER_USER_VDM_CNT() * 4); ucVdoDataIndex++)
                {
                    pstAcerUserEvent->pucVdmData[ucVdoDataIndex] = GET_D0_TYPE_C_ACER_USER_VDM_DATA(ucVdoDataIndex);
                }

                // Clear Acer User Evnet in User
                CLR_D0_TYPE_C_ACER_USER_EVENT(_TYPE_C_ACER_USER_EVENT_ALL);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TypeC Acer Alt Mode System Event Process
// Input Value  : ucInputPort --> Input Port
//                stAcerSysEvent --> Acer System Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCAcerAltModeHandler(BYTE ucInputPort, StructTypeCAcerSysEvent stAcerSysEvent)
{
    stAcerSysEvent = stAcerSysEvent;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            // User can Change its behavior corresponding to System Event
            // stAcerSysEvent.b3VdmCnt : Number of VDO from System
            // stAcerSysEvent.pucVdmData[0] : VDO_0[31:24], pucVdmData[1] : VDO_0[23:16]...
            break;
#endif

        default:
            break;
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : TypeC Hp Alt Mode Get User Event
// Input Value  : ucInputPort --> Input Port
//                pstHpUserEvent --> Hp User Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCGetHpUserEvent(BYTE ucInputPort, StructTypeCHpUserEvent *pstHpUserEvent)
{
    // 1. User Can Update User Event Macro Whenever Monitor Status Changes
    // 2. Kernel will Get Hp User Event in this Function and send to Port Ctrl

    BYTE ucVdoDataIndex = 0x00;

    pstHpUserEvent = pstHpUserEvent;
    ucVdoDataIndex = ucVdoDataIndex;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            /* Example :
            if(Monitor Status Change)
            {
                SET_D0_TYPE_C_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTENTION);   // Ask Kenel Send Attention
                SET_D0_TYPE_C_HP_USER_VDM_CNT( N );   // Set Number of VDO (Not include VDM Header)
                SET_D0_TYPE_C_HP_USER_VDM_DATA(0, VDO_0[31:24]);
                SET_D0_TYPE_C_HP_USER_VDM_DATA(1, VDO_0[23:16]);
                SET_D0_TYPE_C_HP_USER_VDM_DATA(2, VDO_0[15:8]);
                SET_D0_TYPE_C_HP_USER_VDM_DATA(3, VDO_0[7:0]);
            }
            */

            // Check Hp User Event
            if(GET_D0_TYPE_C_HP_USER_EVENT() != _TYPE_C_HP_USER_EVENT_NONE)
            {
                if(GET_D0_TYPE_C_HP_USER_VDM_CNT() > 5)
                {
                    SET_D0_TYPE_C_HP_USER_VDM_CNT(5);
                }

                // Update Hp User Event to Kernel
                pstHpUserEvent->enumEvent = GET_D0_TYPE_C_HP_USER_EVENT();
                pstHpUserEvent->b3VdmCnt = GET_D0_TYPE_C_HP_USER_VDM_CNT();

                for(ucVdoDataIndex = 0; ucVdoDataIndex < (GET_D0_TYPE_C_HP_USER_VDM_CNT() * 4); ucVdoDataIndex++)
                {
                    pstHpUserEvent->pucVdmData[ucVdoDataIndex] = GET_D0_TYPE_C_HP_USER_VDM_DATA(ucVdoDataIndex);
                }

                // Clear Hp User Evnet in User
                CLR_D0_TYPE_C_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ALL);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TypeC Hp Alt Mode System Event Process
// Input Value  : ucInputPort --> Input Port
//                stHpSysEvent --> Hp System Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCHpAltModeHandler(BYTE ucInputPort, StructTypeCHpSysEvent stHpSysEvent)
{
    stHpSysEvent = stHpSysEvent;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            // User can Change its behavior corresponding to System Event
            // stHpSysEvent.b3VdmCnt : Number of VDO from System
            // stHpSysEvent.pucVdmData[0] : VDO_0[31:24], pucVdmData[1] : VDO_0[23:16]...
            break;
#endif

        default:
            break;
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TypeC PDO From User / Kernel
// Input Value  : ucInputPort --> Input Port
//              : enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : return PDO from USER / KERNEL
//--------------------------------------------------
EnumTypeCEmbPdoReference UserInterfaceTypeCPdoReference(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(enumPowerRole == _TYPE_C_POWER_SRC)
            {
                // Source Capability Default Defined By User
                return _TYPE_C_PDO_FROM_USER;
            }
            else if(enumPowerRole == _TYPE_C_POWER_SNK)
            {
                // Sink Capability Default Difined By Kernel
                return _TYPE_C_PDO_FROM_KERNEL;
            }

            break;
#endif

        default:
            break;
    }
    return _TYPE_C_PDO_FROM_KERNEL;
}

//--------------------------------------------------
// Description  : Get TypeC RDO From User / Kernel
// Input Value  : ucInputPort --> Input Port
// Output Value : return PDO from USER / KERNEL
//--------------------------------------------------
EnumTypeCEmbRdoReference UserInterfaceTypeCRdoReference(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            // Kernel Default Request 5V @ 500mA
            return _TYPE_C_RDO_FROM_KERNEL;

            break;
#endif

        default:
            break;
    }
    return _TYPE_C_RDO_FROM_KERNEL;
}

//--------------------------------------------------
// Description  : Embedded Port Controller Max Power
// Input Value  : ucInputPort --> Input Port
// Output Value : return Max Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserInterfaceTypeCGetMaxPower(BYTE ucInputPort)
{
    // Max Power Range From 0 ~ 100W
    WORD usEmbTypeCMaxPower = 0;

    // User can use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create ucHubDeviceCnt logic

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            // User Can Define Different Max Power According to Device Count
            // Default Max Power = 270 * 0.1 = 27W
            usEmbTypeCMaxPower = 270;

            break;
#endif

        default:

            // Default Max Power = 270 * 0.1 = 27W
            usEmbTypeCMaxPower = 270;

            break;
    }

    return usEmbTypeCMaxPower;
}

//--------------------------------------------------
// Description  : Embedded Port Controller PDO Count
// Input Value  : ucInputPort --> Input Port
//              : enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : return Number of PDOs
//--------------------------------------------------
EnumTypeCPdoNumber UserInterfaceTypeCGetPdoCount(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    // User can use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create ucHubDeviceCnt logic

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            if(enumPowerRole == _TYPE_C_POWER_SRC)
            {
                // Set Number of Source PDOs
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                // PPS Support : Default 2 Fix + 1 PPS PDO = 3 PDOs
                return _TYPE_C_PDO_NUM_3;
#else
                // No PPS Support : Default 2 Fix PDO
                return _TYPE_C_PDO_NUM_2;
#endif
            }
            else if(enumPowerRole == _TYPE_C_POWER_SNK)
            {
                // Set Number of Sink PDOs, Example : 2 Sink PDOs
                return _TYPE_C_PDO_NUM_2;
            }

            break;
#endif

        default:
            break;
    }

    return _TYPE_C_PDO_NUM_2;
}

//--------------------------------------------------
// Description  : Kernel Get Embedded Port Controller Source PDO Info
// Input Value  : ucInputPort --> Input Port
//                ucPdoIndex --> PDO Index
//                *pstTypeCUserSrcPdo --> Source PDO Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCGetSrcPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserSrcPdo)
{
    ucPdoIndex = ucPdoIndex;
    pstTypeCUserSrcPdo = pstTypeCUserSrcPdo;

    // User can use "UserCommonUsbHubGetDspInfo()" to Create ucHubDeviceCnt logic

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            switch(ucPdoIndex)
            {
                // =============================== WARNING ===============================
                // 1st PDO Must Be Fix Supply PDO @ 5V
                // ALL PDO Type Must Be In Order : Fix -> PPS
                // ALL PDO Voltage in Same Type Must Be In Order : Lowest To Highest
                // User Can Define Different PDO According to Device Count
                // =======================================================================

                case _TYPE_C_PDO_NUM_1:

                    // -------------------- 1st Source PDO --------------------
                    // PDO Type = Fix Supply PDO, Must Be 5V (Max = 5A)
                    // Max Voltage (Unit = 100mV) : 50 * 100mV = 5V
                    // Max Current (Unit = 50mA)  : 60 *  50mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSrcPdo->ucMaxVoltage = 50;
                    pstTypeCUserSrcPdo->ucMaxCurrent = 60;

                    break;

                case _TYPE_C_PDO_NUM_2:

                    // -------------------- 2nd Source PDO --------------------
                    // PDO Type = Fix Supply PDO (Max = 20V / 5A)
                    // Max Voltage (Unit = 100mV) : 90 * 100mV = 9V
                    // Max Current (Unit = 50mA)  : 60 *  50mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSrcPdo->ucMaxVoltage = 90;
                    pstTypeCUserSrcPdo->ucMaxCurrent = 60;

                    break;

                case _TYPE_C_PDO_NUM_3:

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    // ----------- 3rd Source PDO (PPS PDO Example) -----------
                    // PDO Type = Fix Supply PDO (Max = 20V / 5A)
                    // Spec 9V Prog PDO = 3~11V @ 3A
                    // Min Voltage (Unit = 100mV) : 30 * 100mV = 3V
                    // Max Voltage (Unit = 100mV) : 90 * 100mV = 9V
                    // Max Current (Unit = 50mA)  : 60 *  50mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_3_PROGRAMMABLE_PDO;
                    pstTypeCUserSrcPdo->ucMinVoltage = 30;
                    pstTypeCUserSrcPdo->ucMaxVoltage = 90;
                    pstTypeCUserSrcPdo->ucMaxCurrent = 60;
#endif
                    break;

                case _TYPE_C_PDO_NUM_4:
                case _TYPE_C_PDO_NUM_5:
                case _TYPE_C_PDO_NUM_6:
                case _TYPE_C_PDO_NUM_7:
                default:

                    break;
            }


            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Kernel Get Embedded Port Controller Sink PDO Info
// Input Value  : ucInputPort --> Input Port
//                ucPdoIndex --> PDO Index
//                *pstTypeCUserSnkPdo --> Sink PDO Info (Sink Capability)
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCGetSnkPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserSnkPdo)
{
    ucPdoIndex = ucPdoIndex;
    pstTypeCUserSnkPdo = pstTypeCUserSnkPdo;

    // Example : 2 Sink PDOs (5V@2A / 9V@2A)

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            switch(ucPdoIndex)
            {
                // =============================== WARNING ===============================
                // 1st PDO Must Be Fix Supply PDO @ 5V
                // ALL PDO Type Must Be In Order : Fix -> PPS
                // ALL PDO Voltage in Same Type Must Be In Order : Lowest To Highest
                // User Can Define Different PDO According to Device Count
                // =======================================================================

                case _TYPE_C_PDO_NUM_1:

                    // -------------------- 1st Sink PDO ----------------------
                    // PDO Type = Fix Supply PDO, Must Be 5V (Max = 5A)
                    // Max Voltage (Unit = 100mV) : 50 * 100mV = 5V
                    // Max Current (Unit = 50mA)  : 40 *  50mA = 2A
                    // --------------------------------------------------------
                    pstTypeCUserSnkPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSnkPdo->ucMaxVoltage = 50;
                    pstTypeCUserSnkPdo->ucMaxCurrent = 40;

                    break;

                case _TYPE_C_PDO_NUM_2:

                    // -------------------- 2nd Sink PDO ----------------------
                    // PDO Type = Fix Supply PDO (Max = 20V / 5A)
                    // Max Voltage (Unit = 100mV) : 90 * 100mV = 9V
                    // Max Current (Unit = 50mA)  : 40 *  50mA = 2A
                    // --------------------------------------------------------
                    pstTypeCUserSnkPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSnkPdo->ucMaxVoltage = 90;
                    pstTypeCUserSnkPdo->ucMaxCurrent = 40;

                    break;

                case _TYPE_C_PDO_NUM_3:
                case _TYPE_C_PDO_NUM_4:
                case _TYPE_C_PDO_NUM_5:
                case _TYPE_C_PDO_NUM_6:
                case _TYPE_C_PDO_NUM_7:
                default:

                    break;
            }


            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Kernel Get Embedded Port Controller Request Info
// Input Value  : ucInputPort --> Input Port
//                *pstTypeCUserRdo --> Request Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCGetRdoInfo(BYTE ucInputPort, StructTypeCUserRDO *pstTypeCUserRdo)
{
    // ============================== EXAMPLE ================================
    // User can Use "SysTypeCGetPartnerPdoCnt" to Get Num of PDO Source Provided
    // User can Use "SysTypeCGetPartnerPdo" to Read Each PDO Info
    // User can Use "SysTypeCGetPdoStatus" to Get Current PDO Status
    // 1. If 9V @ 2A Exist, Request 9V @ 2A
    // 2. If 9V Exist, But Current < 2A, Request 9V @ Max Cur Source can Provide
    // 3. If 9V Not Exist (or Not Receive Src cAP), Request 5V @ 500mA
    // =======================================================================

    BYTE ucPartnerPdoCnt = 0x00;
    BYTE ucPdoIndex = 0x00;
    StructTypeCUserPDO stTypeCPartnerPdo;

    pstTypeCUserRdo = pstTypeCUserRdo;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            ucPartnerPdoCnt = SysTypeCGetPartnerPdoCnt(_D0_INPUT_PORT, _TYPE_C_POWER_SRC);

            // Set Default Request 5V @ 500mA
            pstTypeCUserRdo->enumObjPos = _TYPE_C_PDO_NUM_1; // 1st PDO Must Be 5V Fix
            pstTypeCUserRdo->usReqInfo1 = 50;                // Fix PDO : Op. Cur in 10mA / PPS PDO : Vol in 20mV
            pstTypeCUserRdo->usReqInfo2 = 50;                // Fix PDO : Max. Cur in 10mA / PPS PDO : Op.Cur in 50mA

            if(ucPartnerPdoCnt != 0x00)
            {
                // If PDO Count NOT 0 (Already Receive PDO from Source), Check PDO Info
                for(ucPdoIndex = 1; ucPdoIndex <= ucPartnerPdoCnt; ucPdoIndex++)
                {
                    // Get Partner Source PDO Info (enumPdoType = PDO Type, ucMaxVoltage = Vol in 100mV, ucMaxCurrent = Cur in 50mA)
                    stTypeCPartnerPdo = SysTypeCGetPartnerPdo(_D0_INPUT_PORT, _TYPE_C_POWER_SRC, ucPdoIndex);

                    // Search if Any PDO Match Fix Supply 9V (90 * 100mV)
                    if((stTypeCPartnerPdo.enumPdoType == _PD_FIX_SUPPLY_PDO) && (stTypeCPartnerPdo.ucMaxVoltage == 90))
                    {
                        // Set Obj Pos to 9V PDO
                        pstTypeCUserRdo->enumObjPos = ucPdoIndex;

                        // Check if Current Meet 2A (40 * 50mA)
                        if(stTypeCPartnerPdo.ucMaxVoltage >= 40)
                        {
                            // Set Request Op. Cur and Max. Cur = 200 * 10mA = 2A
                            pstTypeCUserRdo->usReqInfo1 = 200;
                            pstTypeCUserRdo->usReqInfo2 = 200;
                        }
                        else
                        {
                            // Set Request Op. Cur and Max. Cur to Source Max Current in 9V PDO
                            pstTypeCUserRdo->usReqInfo1 = stTypeCPartnerPdo.ucMaxVoltage * 5;
                            pstTypeCUserRdo->usReqInfo2 = stTypeCPartnerPdo.ucMaxVoltage * 5;
                        }
                    }
                }
            }

            // Set Capability Mismatch if Not Able to Meet Target Request (9V @ 2A)
            if((pstTypeCUserRdo->enumObjPos == _TYPE_C_PDO_NUM_1) || (pstTypeCUserRdo->usReqInfo1 != 200))
            {
                pstTypeCUserRdo->b1CapMismatch = _TRUE;
            }
            else
            {
                pstTypeCUserRdo->b1CapMismatch = _FALSE;
            }

            break;
#endif

        default:
            break;
    }
}

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
//--------------------------------------------------
// Description  : Embedded Port Controller Protect Info
// Input Value  : ucInputPort --> Input Port
//                ucPdoIndex --> PDO Index
//                *pstTypeCUserProtectInfo --> Protect Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCGetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo *pstTypeCUserProtectInfo)
{
    pstTypeCUserProtectInfo = pstTypeCUserProtectInfo;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:

            switch(ucPdoIndex)
            {
                case _TYPE_C_PDO_NUM_1:

                    pstTypeCUserProtectInfo->ucOcpCurRatio = 105;

                    break;

                case _TYPE_C_PDO_NUM_2:

                    pstTypeCUserProtectInfo->ucOcpCurRatio = 105;

                    break;

                case _TYPE_C_PDO_NUM_3:

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    pstTypeCUserProtectInfo->ucOcpCurRatio = 105;
#endif
                    break;

                case _TYPE_C_PDO_NUM_4:
                case _TYPE_C_PDO_NUM_5:
                case _TYPE_C_PDO_NUM_6:
                case _TYPE_C_PDO_NUM_7:
                default:

                    break;
            }

            break;
#endif

        default:
            break;
    }
}
#endif

#if(_DP_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return Hub Input Port to Kernel
// Input Value  : ucInputPort
// Output Value : EnumHubInputPort
//--------------------------------------------------
EnumHubInputPort UserInterfaceTypeCHubInputPort(BYTE ucInputPort)
{
    EnumHubInputPort enumHubInputPort = _HUB_UFP_TYPE_C_INPUT_PORT;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
        case _D0_INPUT_PORT:

            if(GET_USER_USB_HUB_UFP_SWITCH() == _HUB_UFP_TYPE_C_INPUT_PORT)
            {
                enumHubInputPort = _HUB_UFP_TYPE_C_INPUT_PORT;
            }
            else
            {
                enumHubInputPort = _HUB_UFP_NOT_TYPE_C_INPUT_PORT;
            }

            break;
#endif

        default:

            break;
    }

    return enumHubInputPort;
}
#endif
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)

#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Check User Reconnect Support after Config Pin Assignment
// Input Value  : ucInputPort --> Input Port
// Output Value : return _TYPE_C_PORT_CTRL_RECONNECT_SUPPORT / _TYPE_C_PORT_CTRL_RECONNECT_NOT_SUPPORT
//--------------------------------------------------
EnumTypeCPortCtrlReconnectSupport UserInterfaceTypeCPortControllerReconnectSupport(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    return _TYPE_C_PORT_CTRL_RECONNECT_SUPPORT;
}

#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
//--------------------------------------------------
// Description  : Get Power Off Flag to set Capability Change Flag
// Input Value  : enumSwitch
// Output Value : return _TYPE_C_PORT_CTRL_NO_RECONNECT / _TYPE_C_PORT_CTRL_RECONNECT
//--------------------------------------------------
EnumTypeCPortCtrlReconnectStatus UserInterfaceTypeCPortControllerGetPowerOnReconnectStatus(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            if(GET_TYPE_C_PORT_CTRL_POWER_OFF_FLG() == _TRUE)
            {
                return _TYPE_C_PORT_CTRL_RECONNECT;
            }
            else
            {
                return _TYPE_C_PORT_CTRL_NO_RECONNECT;
            }

            break;

        default:

            return _TYPE_C_PORT_CTRL_NO_RECONNECT;

            break;
    }

    return _TYPE_C_PORT_CTRL_NO_RECONNECT;
}
#endif
#endif // End of #if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
